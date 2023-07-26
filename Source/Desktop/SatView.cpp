// SATVIEW.CPP : SatView Desktop Application.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the application related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/02 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#include <initguid.h>
#include "MimicsIIDs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// CDesktopApp
CDesktopApp  cDesktopApp;


static UINT BASED_CODE  nFloatingMenuIDs[] =
{
	IDM_EVENTBOXALLEVENTS,IDM_EVENTBOXSINGLEEVENT,IDM_EVENTBOXUPTOEVENT,IDM_EVENTBOXFROMEVENT,
	IDM_TCMANUALSTACKPROPERTIES,IDM_TCMANUALSTACKMOVEUP,IDM_TCMANUALSTACKMOVEDOWN,IDM_TCMANUALSTACKCOPY,IDM_TCMANUALSTACKPASTE,IDM_TCMANUALSTACKDELETE,IDM_TCMANUALSTACKACKNOWLEDGE,IDM_TCAUTOMATICSTACKPROPERTIES,IDM_TCAUTOMATICSTACKCOPY,IDM_TCAUTOMATICSTACKPASTE,IDM_TCAUTOMATICSTACKDELETE,IDM_TCAUTOMATICSTACKACKNOWLEDGE,
	IDM_TCONBOARDBUFFERQUEUESDETAILS,IDM_TCONBOARDMEMORYIMAGESTRANSACT,IDM_TCONBOARDMEMORYIMAGESDELETE,IDM_TCONBOARDMEMORYIMAGESIMPORT,IDM_TCONBOARDMEMORYIMAGESEXPORT,IDM_TCONBOARDMEMORYIMAGESINSERTTABLEROWABOVE,IDM_TCONBOARDMEMORYIMAGESINSERTTABLEROWBELOW,IDM_TCONBOARDMEMORYIMAGESINSERTTABLECOLUMNBEFORE,IDM_TCONBOARDMEMORYIMAGESINSERTTABLECOLUMNAFTER,IDM_TCONBOARDMEMORYIMAGESDELETETABLEROW,IDM_TCONBOARDMEMORYIMAGESDELETETABLECOLUMN,IDM_TCONBOARDMEMORYIMAGESCOPYTABLEROW,IDM_TCONBOARDMEMORYIMAGESPASTETABLEROW,IDM_TCONBOARDMEMORYIMAGESDISCARDTABLE,IDM_TCONBOARDMEMORYIMAGESRESETTABLE,IDM_TCONBOARDMEMORYIMAGESPRINTTABLE
};

static UINT BASED_CODE  nStatusBarIndicators[] =
{
	ID_STATUSBAR_MESSAGEPANE,
	ID_STATUSBAR_NETWORKPANE,
	ID_STATUSBAR_TELEMETRYPANE,
	ID_STATUSBAR_TELECOMMANDPANE,
	ID_STATUSBAR_ARCHIVINGPANE,
	ID_STATUSBAR_CPUPERFORMANCEPANE,
	ID_STATUSBAR_CLOCKPANE
};



/////////////////////////////////////////////////////////////////////////////
// CMainRibbonBar

IMPLEMENT_DYNCREATE(CMainRibbonBar, CMFCRibbonBar)

CMainRibbonBar::CMainRibbonBar() : CMFCRibbonBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CMainRibbonBar, CMFCRibbonBar)
	//{{AFX_MSG_MAP(CMainRibbonBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainRibbonBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainRibbonButton

IMPLEMENT_DYNCREATE(CMainRibbonButton, CMFCRibbonButton)

CMainRibbonButton::CMainRibbonButton(UINT nID, LPCTSTR pszText, HICON hIcon, HICON hSmallIcon) : CMFCRibbonButton(nID, pszText, hIcon, FALSE, hSmallIcon, FALSE, TRUE)
{
	m_hIcon[0] = hIcon;
	m_hIcon[1] = hSmallIcon;
}

CMainRibbonButton::~CMainRibbonButton()
{
	if (m_hIcon[0] != (HICON)NULL) DestroyIcon(m_hIcon[0]);
	if (m_hIcon[1] != (HICON)NULL) DestroyIcon(m_hIcon[1]);
}

CSize CMainRibbonButton::GetImageSize(RibbonImageType type) const
{
	return CMFCRibbonButton::GetImageSize(RibbonImageSmall);
}

CSize CMainRibbonButton::GetIntermediateSize(CDC *pDC)
{
	CSize  size;

	size = CMFCRibbonButton::GetIntermediateSize(pDC);
	size.cx += GetSystemMetrics(SM_CXFRAME);
	return size;
}

BOOL CMainRibbonButton::HasLargeMode() const
{
	return FALSE;
}

void CMainRibbonButton::OnUpdateCmdUI(CMFCRibbonCmdUI *pCmdUI, CFrameWnd *pTarget, BOOL bDisableIfNoHndler)
{
	INT  nItem;
	INT  nItems;
	BOOL  bDisabled;
	CMFCRibbonButton  *pItem;

	for (nItem = 0, nItems = (INT)GetSubItems().GetCount(), bDisabled = TRUE; nItem < nItems; nItem++)
	{
		if ((pItem = (CMFCRibbonButton *)GetSubItems().GetAt(nItem)) && pItem->GetID() != (UINT)-1 && pItem->GetID() != 0)
		{
			for (pCmdUI->m_pUpdated = pItem, pCmdUI->m_nID = pItem->GetID(), pCmdUI->DoUpdate(pTarget, bDisableIfNoHndler); !pItem->IsDisabled(); )
			{
				bDisabled = FALSE;
				break;
			}
			pCmdUI->m_pUpdated = NULL;
		}
	}
	if (nItems > 0)
	{
		m_bIsDisabled = bDisabled;
		return;
	}
	CMFCRibbonButton::OnUpdateCmdUI(pCmdUI, pTarget, bDisableIfNoHndler);
}


/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarClockThread

IMPLEMENT_DYNCREATE(CMainStatusBarClockThread, CThread)

BOOL CMainStatusBarClockThread::Start(CMainStatusBar *pStatusBar)
{
	return CreateThread(pStatusBar);
}

BOOL CMainStatusBarClockThread::Stop()
{
	return((DestroyThread(FALSE) >= 0) ? TRUE : FALSE);
}

int CMainStatusBarClockThread::Run()
{
	DWORD  dwInterval;
	CMainStatusBar  *pStatusBar = (CMainStatusBar *)GetThreadInfo();

	for (dwInterval = 0; Wait(MAINSTATUSBARCLOCK_UPDATE_INTERVAL) == WAIT_TIMEOUT; dwInterval += MAINSTATUSBARCLOCK_UPDATE_INTERVAL)
	{
		for (pStatusBar->UpdateClockPane(); dwInterval > STATUSBAR_CPUPERFORMANCEPANE_UPDATE_INTERVAL; )
		{
			pStatusBar->UpdateCPUPerformancePane();
			dwInterval = 0;
			break;
		}
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CMainStatusBarClockThread, CThread)
	//{{AFX_MSG_MAP(CMainStatusBarClockThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarClockThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarToolTipCtrl

IMPLEMENT_DYNCREATE(CMainStatusBarToolTipCtrl, CToolTipCtrl)

BOOL CMainStatusBarToolTipCtrl::UpdateTipText(LPCTSTR pszText, CWnd *pWnd, UINT nToolID)
{
	m_szText = pszText;
	m_sInfo.uFlags = 0;
	m_sInfo.uId = nToolID;
	m_sInfo.cbSize = sizeof(m_sInfo);
	m_sInfo.hwnd = pWnd->GetSafeHwnd();
	m_sInfo.lpszText = (LPTSTR)(LPCTSTR)m_szText;
	return((IsWindow(GetSafeHwnd())) ? SendNotifyMessage(TTM_UPDATETIPTEXT, 0, (LPARAM)&m_sInfo) : FALSE);
}

BEGIN_MESSAGE_MAP(CMainStatusBarToolTipCtrl, CToolTipCtrl)
	//{{AFX_MSG_MAP(CMainStatusBarToolTipCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarToolTipCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainStatusBar

IMPLEMENT_DYNCREATE(CMainStatusBar, CMFCStatusBar)

CMainStatusBar::CMainStatusBar() : CMFCStatusBar()
{
	m_bBackupStatus = FALSE;
	m_bArchiveStatus = FALSE;
	m_nBackupFreeSpace = 0;
	m_nArchiveFreeSpace = 0;
	m_nCPUPerformanceValueCount = 0;
	m_fCPUPerformanceValueAverage = 0.0;
	m_nNetworkState = (RASCONNSTATE)0;
	m_szTMDevice[0] = STRING(IDS_TELEMETRYPROVIDERDEVICE_NONE);
	m_szTCDevice[0] = STRING(IDS_TELECOMMANDUPLINKDEVICE_NONE);
	m_szCPUPerformanceStatus = EMPTYSTRING;
	m_rCPUPerformancePane.SetRectEmpty();
	m_rTelecommandPane.SetRectEmpty();
	m_rTelemetryPane.SetRectEmpty();
	m_rArchivingPane.SetRectEmpty();
	m_rNetworkPane.SetRectEmpty();
	m_rClockPane.SetRectEmpty();
	m_bPanes[0] = FALSE;
	m_bPanes[1] = FALSE;
	m_bPanes[2] = FALSE;
	m_bPanes[3] = FALSE;
	m_bPanes[4] = FALSE;
	m_bPanes[5] = FALSE;
	m_pCriticalSection = new CCriticalSection;
}

CMainStatusBar::~CMainStatusBar()
{
	delete m_pCriticalSection;
}

BOOL CMainStatusBar::Create(CWnd *pParentWnd, DWORD dwStyle, UINT nID)
{
	return CMFCStatusBar::Create(pParentWnd, dwStyle, nID);
}

BOOL CMainStatusBar::SetIndicators()
{
	INT  nIndex;
	INT  nCount;
	CUIntArray  nIndicators;

	if (Lock())
	{
		for (nIndex = 0, nCount = (INT)m_nPaneIDs.GetSize(); nIndex < nCount; nIndex++)
		{
			if (m_nPaneIDs.GetAt(nIndex) == ID_STATUSBAR_MESSAGEPANE)
			{
				nIndicators.Add(m_nPaneIDs.GetAt(nIndex));
				continue;
			}
			if (m_nPaneIDs.GetAt(nIndex) == ID_STATUSBAR_NETWORKPANE)
			{
				if (GetRASService()->GetState() == RASCS_Connected)
				{
					nIndicators.Add(m_nPaneIDs.GetAt(nIndex));
					continue;
				}
			}
			if (m_nPaneIDs.GetAt(nIndex) == ID_STATUSBAR_TELEMETRYPANE)
			{
				nIndicators.Add(m_nPaneIDs.GetAt(nIndex));
				continue;
			}
			if (m_nPaneIDs.GetAt(nIndex) == ID_STATUSBAR_TELECOMMANDPANE)
			{
				nIndicators.Add(m_nPaneIDs.GetAt(nIndex));
				continue;
			}
			if (m_nPaneIDs.GetAt(nIndex) == ID_STATUSBAR_ARCHIVINGPANE)
			{
				nIndicators.Add(m_nPaneIDs.GetAt(nIndex));
				continue;
			}
			if (m_nPaneIDs.GetAt(nIndex) == ID_STATUSBAR_CPUPERFORMANCEPANE)
			{
				if (m_cCPUPerformanceMonitor.IsAvailable(CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME))
				{
					nIndicators.Add(m_nPaneIDs.GetAt(nIndex));
					continue;
				}
			}
			if (m_nPaneIDs.GetAt(nIndex) == ID_STATUSBAR_CLOCKPANE)
			{
				nIndicators.Add(m_nPaneIDs.GetAt(nIndex));
				continue;
			}
		}
		Unlock();
	}
	return SetIndicators(nIndicators.GetData(), (INT)nIndicators.GetSize());
}
BOOL CMainStatusBar::SetIndicators(CONST UINT *pID, INT nSize)
{
	UINT  nID;
	UINT  nStyle;
	INT  nIndex;
	INT  nCount;
	INT  nWidth[6];
	CRect  rPane[6];
	CString  szPane;
	CToolInfo  cToolInfo;

	if (Lock())
	{
		for (szPane = ((nIndex = CommandToIndex(ID_STATUSBAR_MESSAGEPANE)) >= 0) ? GetPaneText(nIndex) : EMPTYSTRING; CMFCStatusBar::SetIndicators(pID, (nCount = (TestAccount()) ? nSize : 1)); )
		{
			for (nIndex = 0; nIndex < nCount; nIndex++)
			{
				for (; pID[nIndex] == ID_STATUSBAR_MESSAGEPANE; )
				{
					SetPaneStyle(nIndex, (nIndex == nCount - 1 || pID[nIndex + 1] != ID_STATUSBAR_PROGRESSPANE) ? (SBPS_NOBORDERS | SBPS_STRETCH) : SBPS_NOBORDERS);
					break;
				}
				if (pID[nIndex] == ID_STATUSBAR_PROGRESSPANE)
				{
					SetPaneInfo(nIndex, ID_STATUSBAR_PROGRESSPANE, SBPS_NOBORDERS, STATUSBAR_PROGRESSPANE_WIDTH);
					SetPaneStyle(nIndex + 1, SBPS_NOBORDERS | SBPS_STRETCH);
				}
				if (pID[nIndex] == ID_STATUSBAR_NETWORKPANE)
				{
					GetPaneInfo(nIndex, nID, nStyle, nWidth[0]);
					SetPaneInfo(nIndex, nID, nStyle, (nWidth[0] = CalcNetworkPaneWidth()));
					if (!IsWindow(m_wndToolTip[0].GetSafeHwnd()))
					{
						m_wndToolTip[0].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
						SetClassLongPtr(m_wndToolTip[0].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[0].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_TELEMETRYPANE)
				{
					GetPaneInfo(nIndex, nID, nStyle, nWidth[1]);
					SetPaneInfo(nIndex, nID, nStyle, (nWidth[1] = CalcTelemetryPaneWidth()));
					if (!IsWindow(m_wndToolTip[1].GetSafeHwnd()))
					{
						m_wndToolTip[1].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
						SetClassLongPtr(m_wndToolTip[1].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[1].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_TELECOMMANDPANE)
				{
					GetPaneInfo(nIndex, nID, nStyle, nWidth[2]);
					SetPaneInfo(nIndex, nID, nStyle, (nWidth[2] = CalcTelecommandPaneWidth()));
					if (!IsWindow(m_wndToolTip[2].GetSafeHwnd()))
					{
						m_wndToolTip[2].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
						SetClassLongPtr(m_wndToolTip[2].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[2].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_ARCHIVINGPANE)
				{
					GetPaneInfo(nIndex, nID, nStyle, nWidth[3]);
					SetPaneInfo(nIndex, nID, nStyle, (nWidth[3] = CalcArchivingPaneWidth()));
					if (!IsWindow(m_wndToolTip[3].GetSafeHwnd()))
					{
						m_wndToolTip[3].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
						SetClassLongPtr(m_wndToolTip[3].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[3].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_CPUPERFORMANCEPANE)
				{
					GetPaneInfo(nIndex, nID, nStyle, nWidth[4]);
					SetPaneInfo(nIndex, nID, nStyle, (nWidth[4] = CalcCPUPerformancePaneWidth()));
					if (!IsWindow(m_wndToolTip[4].GetSafeHwnd()))
					{
						m_wndToolTip[4].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
						SetClassLongPtr(m_wndToolTip[4].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[4].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_CLOCKPANE)
				{
					GetPaneInfo(nIndex, nID, nStyle, nWidth[5]);
					SetPaneInfo(nIndex, nID, nStyle, (nWidth[5] = CalcClockPaneWidth()));
					if (!IsWindow(m_wndToolTip[5].GetSafeHwnd()))
					{
						m_wndToolTip[5].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
						SetClassLongPtr(m_wndToolTip[5].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[5].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
					}
				}
			}
			for (nIndex = 0; nIndex < nCount; nIndex++)
			{
				if (pID[nIndex] == ID_STATUSBAR_NETWORKPANE)
				{
					if (IsWindow(m_wndToolTip[0].GetSafeHwnd()))
					{
						for (GetItemRect(nIndex, rPane[0]); !m_wndToolTip[0].GetToolInfo(cToolInfo, this, ID_STATUSBAR_NETWORKPANE); )
						{
							m_wndToolTip[0].AddTool(this, LPSTR_TEXTCALLBACK, rPane[0], ID_STATUSBAR_NETWORKPANE);
							m_wndToolTip[0].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
							m_wndToolTip[0].Activate(TRUE);
							break;
						}
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_TELEMETRYPANE)
				{
					if (IsWindow(m_wndToolTip[1].GetSafeHwnd()))
					{
						for (GetItemRect(nIndex, rPane[1]); !m_wndToolTip[1].GetToolInfo(cToolInfo, this, ID_STATUSBAR_TELEMETRYPANE); )
						{
							m_wndToolTip[1].AddTool(this, LPSTR_TEXTCALLBACK, rPane[1], ID_STATUSBAR_TELEMETRYPANE);
							m_wndToolTip[1].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
							m_wndToolTip[1].Activate(TRUE);
							break;
						}
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_TELECOMMANDPANE)
				{
					if (IsWindow(m_wndToolTip[2].GetSafeHwnd()))
					{
						for (GetItemRect(nIndex, rPane[2]); !m_wndToolTip[2].GetToolInfo(cToolInfo, this, ID_STATUSBAR_TELECOMMANDPANE); )
						{
							m_wndToolTip[2].AddTool(this, LPSTR_TEXTCALLBACK, rPane[2], ID_STATUSBAR_TELECOMMANDPANE);
							m_wndToolTip[2].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
							m_wndToolTip[2].Activate(TRUE);
							break;
						}
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_ARCHIVINGPANE)
				{
					if (IsWindow(m_wndToolTip[3].GetSafeHwnd()))
					{
						for (GetItemRect(nIndex, rPane[3]); !m_wndToolTip[3].GetToolInfo(cToolInfo, this, ID_STATUSBAR_ARCHIVINGPANE); )
						{
							m_wndToolTip[3].AddTool(this, LPSTR_TEXTCALLBACK, rPane[3], ID_STATUSBAR_ARCHIVINGPANE);
							m_wndToolTip[3].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
							m_wndToolTip[3].Activate(TRUE);
							break;
						}
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_CPUPERFORMANCEPANE)
				{
					if (IsWindow(m_wndToolTip[4].GetSafeHwnd()))
					{
						for (GetItemRect(nIndex, rPane[4]); !m_wndToolTip[4].GetToolInfo(cToolInfo, this, ID_STATUSBAR_CPUPERFORMANCEPANE); )
						{
							m_wndToolTip[4].AddTool(this, LPSTR_TEXTCALLBACK, rPane[4], ID_STATUSBAR_CPUPERFORMANCEPANE);
							m_wndToolTip[4].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
							m_wndToolTip[4].Activate(TRUE);
							break;
						}
					}
				}
				if (pID[nIndex] == ID_STATUSBAR_CLOCKPANE)
				{
					if (IsWindow(m_wndToolTip[5].GetSafeHwnd()))
					{
						for (GetItemRect(nIndex, rPane[5]); !m_wndToolTip[5].GetToolInfo(cToolInfo, this, ID_STATUSBAR_CLOCKPANE); )
						{
							m_wndToolTip[5].AddTool(this, LPSTR_TEXTCALLBACK, rPane[5], ID_STATUSBAR_CLOCKPANE);
							m_wndToolTip[5].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
							m_wndToolTip[5].Activate(TRUE);
							break;
						}
					}
				}
			}
			if ((nIndex = CommandToIndex(ID_STATUSBAR_NETWORKPANE)) < 0)
			{
				m_rNetworkPane.SetRectEmpty();
				m_wndToolTip[0].DestroyWindow();
			}
			if ((nIndex = CommandToIndex(ID_STATUSBAR_TELEMETRYPANE)) < 0)
			{
				m_rTelemetryPane.SetRectEmpty();
				m_wndToolTip[1].DestroyWindow();
			}
			if ((nIndex = CommandToIndex(ID_STATUSBAR_TELECOMMANDPANE)) < 0)
			{
				m_rTelecommandPane.SetRectEmpty();
				m_wndToolTip[2].DestroyWindow();
			}
			if ((nIndex = CommandToIndex(ID_STATUSBAR_ARCHIVINGPANE)) < 0)
			{
				m_rArchivingPane.SetRectEmpty();
				m_wndToolTip[3].DestroyWindow();
			}
			if ((nIndex = CommandToIndex(ID_STATUSBAR_CPUPERFORMANCEPANE)) < 0)
			{
				m_rCPUPerformancePane.SetRectEmpty();
				m_wndToolTip[4].DestroyWindow();
			}
			if ((nIndex = CommandToIndex(ID_STATUSBAR_CLOCKPANE)) < 0)
			{
				m_rClockPane.SetRectEmpty();
				m_wndToolTip[5].DestroyWindow();
			}
			SetPaneText(CommandToIndex(ID_STATUSBAR_MESSAGEPANE), szPane);
			RedrawWindow();
			Unlock();
			return TRUE;
		}
		Unlock();
	}
	return FALSE;
}
VOID CMainStatusBar::SetIndicators(CONST CUIntArray &nPaneIDs)
{
	for (m_nPaneIDs.Copy(nPaneIDs); !nPaneIDs.GetSize(); )
	{
		m_nPaneIDs.SetSize(sizeof(nStatusBarIndicators) / sizeof(nStatusBarIndicators[0]));
		CopyMemory(m_nPaneIDs.GetData(), nStatusBarIndicators, m_nPaneIDs.GetSize()*sizeof(UINT));
		break;
	}
}

INT CMainStatusBar::GetIndicators(CUIntArray &nPaneIDs) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	nPaneIDs.Copy(m_nPaneIDs);
	return((INT)nPaneIDs.GetSize());
}

VOID CMainStatusBar::UpdateNetworkPane()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetRASService()->GetState() == RASCS_Connected  &&  !GetRASService()->IsAborting())
	{
		UpdateNetworkPane((GetRASService()->CheckCall() != (RASCONNSTATE)0) ? GetAccountRASServer() : m_szNetworkServer, GetRASService()->CheckCall());
	}
}
VOID CMainStatusBar::UpdateNetworkPane(LPCTSTR pszServer, RASCONNSTATE nState)
{
	CDC  *pDC;
	CString  szDetails;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (szDetails = GetRASService()->GetDetails(); m_szNetworkServer != pszServer || m_nNetworkState != nState; )
	{
		for (m_szNetworkServer = pszServer, m_nNetworkState = nState; nState == (RASCONNSTATE)0 && lstrlen(szDetails) > 0; )
		{
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szDetails);
			break;
		}
		if ((pDC = GetDC()))
		{
			if (m_rNetworkPane.Width() == CalcNetworkPaneWidth()) DrawNetworkStatus(pDC);
			ReleaseDC(pDC);
		}
		for (RedrawWindow(m_rNetworkPane, (CRgn *)NULL, RDW_INVALIDATE); nState == (RASCONNSTATE)0 && !szDetails.IsEmpty(); )
		{
			ScheduleRASService(nState);
			break;
		}
		break;
	}
}

VOID CMainStatusBar::UpdateTelemetryPane()
{
	CTMProviderDevice  cDevice;

	GetTMService()->GetActiveTMProviderDevice(&cDevice);
	UpdateTelemetryPane(&cDevice);
}
VOID CMainStatusBar::UpdateTelemetryPane(CONST CTMProviderDevice *pDevice)
{
	CDC  *pDC;
	CString  szMessage;
	CTMProviderDevice  cDevice;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (cDevice.Copy(pDevice); m_szTMDevice[0] != cDevice.GetDeviceName() || m_szTMDevice[1] != cDevice.GetStatus() || m_nTMDeviceStatus != cDevice.GetStatusIndication(); )
	{
		if (m_szTMDevice[0] != cDevice.GetDeviceName() && !cDevice.GetDeviceName().IsEmpty())
		{
			szMessage.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUSMESSAGE_ACTIVE), (LPCTSTR)cDevice.GetDeviceName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		if (m_szTMDevice[1] != cDevice.GetStatus() && !cDevice.GetDeviceName().IsEmpty() && !cDevice.GetStatus().IsEmpty())
		{
			szMessage.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUSMESSAGE_CHANGED), (LPCTSTR)cDevice.GetDeviceName(), (LPCTSTR)cDevice.GetStatus());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		for (m_szTMDevice[0] = cDevice.GetDeviceName(), m_szTMDevice[1] = cDevice.GetStatus(), m_nTMDeviceStatus = cDevice.GetStatusIndication(); (pDC = GetDC()); )
		{
			if (m_rTelemetryPane.Width() == CalcTelemetryPaneWidth())
			{
				DrawTelemetryStatus(pDC);
				ReleaseDC(pDC);
				return;
			}
			ReleaseDC(pDC);
			break;
		}
		RedrawWindow(m_rTelemetryPane, (CRgn *)NULL, RDW_INVALIDATE);
		break;
	}
}

VOID CMainStatusBar::UpdateTelecommandPane()
{
	CTCUplinkDevice  cDevice;

	GetTCService()->GetActiveTCUplinkDevice(&cDevice);
	UpdateTelecommandPane(&cDevice);
}
VOID CMainStatusBar::UpdateTelecommandPane(CONST CTCUplinkDevice *pDevice)
{
	CDC  *pDC;
	CString  szMessage;
	CTCUplinkDevice  cDevice;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (cDevice.Copy(pDevice); m_szTCDevice[0] != cDevice.GetDeviceName() || m_szTCDevice[1] != cDevice.GetCommandHandler() + TAB + cDevice.GetStatus() || m_nTCDeviceStatus != cDevice.GetStatusIndication(); )
	{
		if (m_szTCDevice[0] != cDevice.GetDeviceName() && !cDevice.GetDeviceName().IsEmpty())
		{
			szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUSMESSAGE_ACTIVE), (LPCTSTR)cDevice.GetDeviceName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		if (m_szTCDevice[1] != cDevice.GetCommandHandler() + TAB + cDevice.GetStatus() && !cDevice.GetDeviceName().IsEmpty() && !cDevice.GetStatus().IsEmpty() && m_szTCDevice[1].Right(min(cDevice.GetStatus().GetLength(), m_szTCDevice[1].GetLength())) != cDevice.GetStatus())
		{
			szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUSMESSAGE_CHANGED), (LPCTSTR)cDevice.GetDeviceName(), (LPCTSTR)cDevice.GetStatus());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		if ((m_szTCDevice[1].Left(min(cDevice.GetCommandHandler().GetLength(), m_szTCDevice[1].GetLength())) != cDevice.GetCommandHandler() && m_szTCDevice[1].Find(TAB) > 0) || ((m_nTCDeviceStatus & TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD) && (cDevice.GetCommandHandlerState() & TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD) != TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUSMESSAGE_DISCONNECTED), (LPCTSTR)m_szTCDevice[1].Left(m_szTCDevice[1].Find(TAB)));
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		if ((m_szTCDevice[1].Left(min(cDevice.GetCommandHandler().GetLength(), m_szTCDevice[1].GetLength())) != cDevice.GetCommandHandler() && !cDevice.GetCommandHandler().IsEmpty()) || ((m_nTCDeviceStatus & TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD) && (cDevice.GetCommandHandlerState() & TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD)))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUSMESSAGE_CONNECTED), (LPCTSTR)cDevice.GetCommandHandler());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		for (m_szTCDevice[0] = cDevice.GetDeviceName(), m_szTCDevice[1] = cDevice.GetCommandHandler() + TAB + cDevice.GetStatus(), m_nTCDeviceStatus = cDevice.GetCommandHandlerState(); (pDC = GetDC()); )
		{
			if (m_rTelecommandPane.Width() == CalcTelecommandPaneWidth())
			{
				DrawTelecommandStatus(pDC);
				ReleaseDC(pDC);
				return;
			}
			ReleaseDC(pDC);
			break;
		}
		RedrawWindow(m_rTelecommandPane, (CRgn *)NULL, RDW_INVALIDATE);
		break;
	}
}

VOID CMainStatusBar::UpdateArchivingPane()
{
	BOOL  bStatus[2];
	UINT  nFreeSpace[2];
	CString  szFileName[2];

	GetTMService()->GetTMHistoryFilesDetails(szFileName[0], nFreeSpace[0], bStatus[0], szFileName[1], nFreeSpace[1], bStatus[1]);
	UpdateArchivingPane(szFileName[0], nFreeSpace[0], bStatus[0], szFileName[1], nFreeSpace[1], bStatus[1]);
}
VOID CMainStatusBar::UpdateArchivingPane(LPCTSTR pszArchiveFile, UINT nArchiveFreeSpace, BOOL bArchiveStatus, LPCTSTR pszBackupDirectory, UINT nBackupFreeSpace, BOOL bBackupStatus)
{
	CDC  *pDC;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_szArchiveFile != pszArchiveFile || m_szBackupDirectory != pszBackupDirectory || m_nArchiveFreeSpace != nArchiveFreeSpace || m_nBackupFreeSpace != nBackupFreeSpace || m_bArchiveStatus != bArchiveStatus || m_bBackupStatus != bBackupStatus)
	{
		for (m_szArchiveFile = pszArchiveFile, m_nArchiveFreeSpace = nArchiveFreeSpace, m_bArchiveStatus = bArchiveStatus, m_szBackupDirectory = pszBackupDirectory, m_nBackupFreeSpace = nBackupFreeSpace, m_bBackupStatus = bBackupStatus; m_rArchivingPane.Width() == CalcArchivingPaneWidth(); )
		{
			if (pDC = GetDC())
			{
				DrawArchivingStatus(pDC);
				ReleaseDC(pDC);
				return;
			}
			break;
		}
		RedrawWindow(m_rArchivingPane, (CRgn *)NULL, RDW_INVALIDATE);
	}
}

VOID CMainStatusBar::UpdateCPUPerformancePane()
{
	CDC  *pDC;
	double  fCPU[2];
	CStringTools  cStringTools;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME, fCPU[0]) && m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_TOTALPROCESSORTIME, fCPU[1]))
	{
		for (m_fCPUPerformanceValueAverage = (m_nCPUPerformanceValueCount*m_fCPUPerformanceValueAverage + min(fCPU[1], 100.0)) / (m_nCPUPerformanceValueCount + 1), m_nCPUPerformanceValueCount = min(m_nCPUPerformanceValueCount + 1, STATUSBAR_CPUPERFORMANCEPANEAVERAGE_SAMPLES), m_nCPUPerformanceValues.Add((UINT)fCPU[0]); m_nCPUPerformanceValues.GetSize() > STATUSBAR_CPUPERFORMANCEPANEAVERAGE_SAMPLES + 1; )
		{
			m_nCPUPerformanceValues.RemoveAt(0);
			break;
		}
		if ((pDC = GetDC()))
		{
			for (m_szCPUPerformanceStatus = cStringTools.ConvertUIntToString((UINT)fCPU[0]); m_rCPUPerformancePane.Width() == CalcCPUPerformancePaneWidth(); )
			{
				DrawCPUPerformanceStatus(pDC);
				ReleaseDC(pDC);
				return;
			}
			ReleaseDC(pDC);
		}
		RedrawWindow(m_rCPUPerformancePane, (CRgn *)NULL, RDW_INVALIDATE);
	}
}

VOID CMainStatusBar::UpdateClockPane()
{
	CDC  *pDC;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pDC = GetDC()))
	{
		if (m_rClockPane.Width() == CalcClockPaneWidth())
		{
			DrawClockTime(pDC);
			ReleaseDC(pDC);
			return;
		}
		ReleaseDC(pDC);
	}
	RedrawWindow(m_rClockPane, (CRgn *)NULL, RDW_INVALIDATE);
}

VOID CMainStatusBar::UpdateAllPanes()
{
	UpdateNetworkPane();
	UpdateTelemetryPane();
	UpdateTelecommandPane();
	UpdateArchivingPane();
	UpdateCPUPerformancePane();
	UpdateClockPane();
}

BOOL CMainStatusBar::ShowPane(UINT nPaneID, BOOL bVisible)
{
	INT  nPane;
	INT  nPanes;
	INT  nIndex;
	INT  nCount;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nPane = 0, nPanes = (INT)m_nPaneIDs.GetSize(); nPane < nPanes; nPane++)
	{
		if (m_nPaneIDs.GetAt(nPane) == nPaneID) break;
		continue;
	}
	if (bVisible  &&  nPane == nPanes)
	{
		for (nIndex = 0, nCount = (INT)(sizeof(nStatusBarIndicators) / sizeof(nStatusBarIndicators[0])); nIndex < nCount; nIndex++)
		{
			if (nStatusBarIndicators[nIndex] == nPaneID) break;
			continue;
		}
		if (nIndex < nCount)
		{
			m_nPaneIDs.InsertAt(nIndex, nPaneID);
			SetIndicators();
			return TRUE;
		}
		return FALSE;
	}
	if (!bVisible  &&  nPane < nPanes)
	{
		m_nPaneIDs.RemoveAt(nPane);
		SetIndicators();
	}
	return TRUE;
}

BOOL CMainStatusBar::IsPaneVisible(UINT nPaneID) CONST
{
	return((nPaneID == ID_STATUSBAR_MESSAGEPANE || (nPaneID == ID_STATUSBAR_NETWORKPANE  &&  !m_rNetworkPane.IsRectEmpty()) || (nPaneID == ID_STATUSBAR_TELEMETRYPANE  &&  !m_rTelemetryPane.IsRectEmpty()) || (nPaneID == ID_STATUSBAR_TELECOMMANDPANE  &&  !m_rTelecommandPane.IsRectEmpty()) || (nPaneID == ID_STATUSBAR_ARCHIVINGPANE  &&  !m_rArchivingPane.IsRectEmpty()) || (nPaneID == ID_STATUSBAR_CPUPERFORMANCEPANE  &&  !m_rCPUPerformancePane.IsRectEmpty()) || (nPaneID == ID_STATUSBAR_CLOCKPANE  &&  !m_rClockPane.IsRectEmpty())) ? TRUE : FALSE);
}

BOOL CMainStatusBar::IsPaneAvailable(UINT nPaneID) CONST
{
	return((nPaneID == ID_STATUSBAR_MESSAGEPANE || nPaneID == ID_STATUSBAR_NETWORKPANE || nPaneID == ID_STATUSBAR_TELEMETRYPANE || nPaneID == ID_STATUSBAR_TELECOMMANDPANE || nPaneID == ID_STATUSBAR_ARCHIVINGPANE || (nPaneID == ID_STATUSBAR_CPUPERFORMANCEPANE  &&  m_cCPUPerformanceMonitor.IsAvailable(CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME)) || nPaneID == ID_STATUSBAR_CLOCKPANE) ? TRUE : FALSE);
}

BOOL CMainStatusBar::SetPaneText(int nIndex, LPCTSTR lpszNewText, BOOL bUpdate)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((nIndex != CommandToIndex(ID_STATUSBAR_MESSAGEPANE) || lstrcmp(lpszNewText, STRING(IDS_STATUSBAR_READY)) || !IsShowingProgress()) ? CMFCStatusBar::SetPaneText(nIndex, lpszNewText, bUpdate) : FALSE);
}

BOOL CMainStatusBar::SetProgressIndicator(LPCTSTR pszMessage)
{
	CDC  *pDC;
	INT  nPane;
	INT  nPanes;
	CFont  *pOldFont;
	CUIntArray  nIndicators;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			for (nPane = 0, nPanes = (lstrlen(pszMessage) > 0) ? GetCount() : -1; nPane < nPanes; nPane++)
			{
				for (nIndicators.Add(GetItemID(nPane)); GetItemID(nPane) == ID_STATUSBAR_MESSAGEPANE && (nPane == nPanes - 1 || GetItemID(nPane + 1) != ID_STATUSBAR_PROGRESSPANE); )
				{
					nIndicators.Add(ID_STATUSBAR_PROGRESSPANE);
					nIndicators.Add(ID_STATUSBAR_SEPARATORPANE);
					break;
				}
				if (nIndicators.GetAt(nIndicators.GetUpperBound()) == ID_STATUSBAR_SEPARATORPANE) break;
			}
			if (nPanes > 0)
			{
				if (SetIndicators(nIndicators.GetData(), (INT)nIndicators.GetSize()))
				{
					SetPaneWidth(CommandToIndex(ID_STATUSBAR_MESSAGEPANE), pDC->GetTextExtent(pszMessage, lstrlen(pszMessage)).cx);
					EnablePaneProgressBar(CommandToIndex(ID_STATUSBAR_PROGRESSPANE));
					SetPaneProgress(CommandToIndex(ID_STATUSBAR_PROGRESSPANE), 0);
					pDC->SelectObject(pOldFont);
					ReleaseDC(pDC);
					return TRUE;
				}
			}
			if (SetIndicators(nStatusBarIndicators, 1))
			{
				pDC->SelectObject(pOldFont);
				ReleaseDC(pDC);
				return TRUE;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
	return FALSE;
}

BOOL CMainStatusBar::ShowProgress(INT nPercent)
{
	if (IsShowingProgress())
	{
		SetPaneProgress(CommandToIndex(ID_STATUSBAR_PROGRESSPANE), nPercent);
		return TRUE;
	}
	return FALSE;
}

BOOL CMainStatusBar::IsShowingProgress() CONST
{
	return((CommandToIndex(ID_STATUSBAR_PROGRESSPANE) >= 0) ? TRUE : FALSE);
}

VOID CMainStatusBar::DrawPanes()
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		DrawNetworkStatus(pDC);
		DrawTelemetryStatus(pDC);
		DrawTelecommandStatus(pDC);
		DrawArchivingStatus(pDC);
		DrawCPUPerformanceStatus(pDC);
		DrawClockTime(pDC);
		ReleaseDC(pDC);
	}
}

VOID CMainStatusBar::DrawNetworkStatus(CDC *pDC)
{
	CDC  cDC;
	CRect  rGrid;
	CRect  rPane[2];
	CFont  *pOldFont;
	CSize  sizeText;
	CSize  sizeSymbol;
	CString  szStatus;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_rNetworkPane.IsRectEmpty())
	{
		for (GetClientRect(rGrid); !GetParent()->IsZoomed(); )
		{
			pDC->ExcludeClipRect(rGrid.right - rGrid.Height(), rGrid.top, rGrid.right, rGrid.bottom);
			break;
		}
		if (cDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap.CreateCompatibleBitmap(pDC, m_rNetworkPane.Width(), m_rNetworkPane.Height()))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
				{
					if ((pOldFont = cDC.SelectObject(&m_cPanesFont)))
					{
						sizeText = cDC.GetTextExtent((szStatus = FormatNetworkStatus()));
						sizeSymbol.cx = m_cNetwork[m_nNetworkState != RASCS_Connected].GetWidth();
						sizeSymbol.cy = m_cNetwork[m_nNetworkState != RASCS_Connected].GetHeight();
						rPane[0].SetRect(0, (m_rNetworkPane.Height() - sizeSymbol.cy + 1) / 2, sizeSymbol.cx, (m_rNetworkPane.Height() - sizeSymbol.cy + 1) / 2 + sizeSymbol.cy);
						rPane[1].SetRect(sizeSymbol.cx, (m_rNetworkPane.Height() - sizeText.cy) / 2, m_rNetworkPane.Width(), (m_rNetworkPane.Height() - sizeText.cy) / 2 + sizeText.cy);
						cDC.FillSolidRect(CRect(0, 0, m_rNetworkPane.Width(), m_rNetworkPane.Height()), GetSysColor(COLOR_3DFACE));
						m_cNetwork[m_nNetworkState != RASCS_Connected].Draw(cDC.GetSafeHdc(), rPane[0].TopLeft());
						cDC.DrawText(szStatus, rPane[1], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
						pDC->BitBlt(m_rNetworkPane.left, m_rNetworkPane.top, m_rNetworkPane.Width(), m_rNetworkPane.Height(), &cDC, 0, 0, SRCCOPY);
						cDC.SelectObject(pOldFont);
					}
					cDC.SelectObject(pOldBitmap);
				}
				cBitmap.DeleteObject();
			}
			cDC.DeleteDC();
		}
	}
}

VOID CMainStatusBar::DrawTelemetryStatus(CDC *pDC)
{
	CDC  cDC;
	INT  nPos;
	CRect  rGrid;
	CRect  rPane[3];
	CFont  *pOldFont;
	CSize  sizeText[2];
	CSize  sizeSymbol;
	CString  szStatus;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_rTelemetryPane.IsRectEmpty())
	{
		for (GetClientRect(rGrid); !GetParent()->IsZoomed(); )
		{
			pDC->ExcludeClipRect(rGrid.right - rGrid.Height(), rGrid.top, rGrid.right, rGrid.bottom);
			break;
		}
		if (cDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap.CreateCompatibleBitmap(pDC, m_rTelemetryPane.Width(), m_rTelemetryPane.Height()))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
				{
					if ((pOldFont = cDC.SelectObject(&m_cPanesFont)))
					{
						if ((nPos = (szStatus = FormatTelemetryStatus()).Find(TAB)) >= 0)
						{
							sizeText[0] = cDC.GetTextExtent(szStatus.Left(nPos));
							sizeText[1] = cDC.GetTextExtent(szStatus.Mid(nPos + 1));
							sizeSymbol.cx = m_cLamps[0][TranslateTMDeviceStatus(m_nTMDeviceStatus)].GetWidth();
							sizeSymbol.cy = m_cLamps[0][TranslateTMDeviceStatus(m_nTMDeviceStatus)].GetHeight();
							rPane[0].SetRect(0, (m_rTelemetryPane.Height() - sizeText[0].cy) / 2, m_rTelemetryPane.Width(), (m_rTelemetryPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							rPane[1].SetRect(sizeText[0].cx, (m_rTelemetryPane.Height() - sizeSymbol.cy + 1) / 2, m_rTelemetryPane.Width(), (m_rTelemetryPane.Height() - sizeSymbol.cy + 1) / 2 + sizeSymbol.cy);
							rPane[2].SetRect(sizeText[0].cx + sizeSymbol.cx, (m_rTelemetryPane.Height() - sizeText[0].cy) / 2, m_rTelemetryPane.Width(), (m_rTelemetryPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							cDC.FillSolidRect(CRect(0, 0, m_rTelemetryPane.Width(), m_rTelemetryPane.Height()), GetSysColor(COLOR_3DFACE));
							cDC.DrawText(szStatus.Left(nPos), rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
							cDC.DrawText(szStatus.Mid(nPos + 1), rPane[2], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
							m_cLamps[0][TranslateTMDeviceStatus(m_nTMDeviceStatus)].Draw(cDC.GetSafeHdc(), rPane[1].TopLeft());
						}
						else
						{
							sizeText[0] = cDC.GetTextExtent(szStatus);
							rPane[0].SetRect(0, (m_rTelemetryPane.Height() - sizeText[0].cy) / 2, m_rTelemetryPane.Width(), (m_rTelemetryPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							cDC.FillSolidRect(CRect(0, 0, m_rTelemetryPane.Width(), m_rTelemetryPane.Height()), GetSysColor(COLOR_3DFACE));
							cDC.DrawText(szStatus, rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
						}
						pDC->BitBlt(m_rTelemetryPane.left, m_rTelemetryPane.top, m_rTelemetryPane.Width(), m_rTelemetryPane.Height(), &cDC, 0, 0, SRCCOPY);
						cDC.SelectObject(pOldFont);
					}
					cDC.SelectObject(pOldBitmap);
				}
				cBitmap.DeleteObject();
			}
			cDC.DeleteDC();
		}
	}
}

VOID CMainStatusBar::DrawTelecommandStatus(CDC *pDC)
{
	CDC  cDC;
	INT  nPos;
	CRect  rGrid;
	CRect  rPane[3];
	CFont  *pOldFont;
	CSize  sizeText[2];
	CSize  sizeSymbol;
	CString  szStatus;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_rTelecommandPane.IsRectEmpty())
	{
		for (GetClientRect(rGrid); !GetParent()->IsZoomed(); )
		{
			pDC->ExcludeClipRect(rGrid.right - rGrid.Height(), rGrid.top, rGrid.right, rGrid.bottom);
			break;
		}
		if (cDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap.CreateCompatibleBitmap(pDC, m_rTelecommandPane.Width(), m_rTelecommandPane.Height()))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
				{
					if ((pOldFont = cDC.SelectObject(&m_cPanesFont)))
					{
						if ((nPos = (szStatus = FormatTelecommandStatus()).Find(TAB)) >= 0)
						{
							sizeText[0] = cDC.GetTextExtent(szStatus.Left(nPos));
							sizeText[1] = cDC.GetTextExtent(szStatus.Mid(nPos + 1));
							sizeSymbol.cx = m_cLamps[1][TranslateTCDeviceStatus(m_nTCDeviceStatus)].GetWidth();
							sizeSymbol.cy = m_cLamps[1][TranslateTCDeviceStatus(m_nTCDeviceStatus)].GetHeight();
							rPane[0].SetRect(0, (m_rTelecommandPane.Height() - sizeText[0].cy) / 2, m_rTelecommandPane.Width(), (m_rTelecommandPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							rPane[1].SetRect(sizeText[0].cx, (m_rTelecommandPane.Height() - sizeSymbol.cy + 1) / 2, m_rTelecommandPane.Width(), (m_rTelecommandPane.Height() - sizeSymbol.cy + 1) / 2 + sizeSymbol.cy);
							rPane[2].SetRect(sizeText[0].cx + sizeSymbol.cx, (m_rTelecommandPane.Height() - sizeText[0].cy) / 2, m_rTelecommandPane.Width(), (m_rTelecommandPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							cDC.FillSolidRect(CRect(0, 0, m_rTelecommandPane.Width(), m_rTelecommandPane.Height()), GetSysColor(COLOR_3DFACE));
							cDC.DrawText(szStatus.Left(nPos), rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
							cDC.DrawText(szStatus.Mid(nPos + 1), rPane[2], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
							m_cLamps[1][TranslateTCDeviceStatus(m_nTCDeviceStatus)].Draw(cDC.GetSafeHdc(), rPane[1].TopLeft());
						}
						else
						{
							sizeText[0] = cDC.GetTextExtent(szStatus);
							rPane[0].SetRect(0, (m_rTelecommandPane.Height() - sizeText[0].cy) / 2, m_rTelecommandPane.Width(), (m_rTelecommandPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							cDC.FillSolidRect(CRect(0, 0, m_rTelecommandPane.Width(), m_rTelecommandPane.Height()), GetSysColor(COLOR_3DFACE));
							cDC.DrawText(szStatus, rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
						}
						pDC->BitBlt(m_rTelecommandPane.left, m_rTelecommandPane.top, m_rTelecommandPane.Width(), m_rTelecommandPane.Height(), &cDC, 0, 0, SRCCOPY);
						cDC.SelectObject(pOldFont);
					}
					cDC.SelectObject(pOldBitmap);
				}
				cBitmap.DeleteObject();
			}
			cDC.DeleteDC();
		}
	}
}

VOID CMainStatusBar::DrawArchivingStatus(CDC *pDC)
{
	CDC  cDC;
	INT  nPos[2];
	CRect  rGrid;
	CRect  rPane[5];
	CFont  *pOldFont;
	CSize  sizeText[3];
	CSize  sizeSymbol[2];
	CString  szStatus;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_rArchivingPane.IsRectEmpty())
	{
		for (GetClientRect(rGrid); !GetParent()->IsZoomed(); )
		{
			pDC->ExcludeClipRect(rGrid.right - rGrid.Height(), rGrid.top, rGrid.right, rGrid.bottom);
			break;
		}
		if (cDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap.CreateCompatibleBitmap(pDC, m_rArchivingPane.Width(), m_rArchivingPane.Height()))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
				{
					if ((pOldFont = cDC.SelectObject(&m_cPanesFont)))
					{
						if ((nPos[0] = (szStatus = FormatArchivingStatus()).Find(TAB)) >= 0)
						{
							if ((nPos[1] = szStatus.Mid(nPos[0] + 1).Find(TAB)) >= 0)
							{
								sizeText[0] = cDC.GetTextExtent(szStatus.Left(nPos[0]));
								sizeText[1] = cDC.GetTextExtent(szStatus.Mid(nPos[0] + 1, nPos[1]));
								sizeText[2] = cDC.GetTextExtent(szStatus.Mid(nPos[0] + 1 + nPos[1] + 1));
								sizeSymbol[0].cx = m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].GetWidth();
								sizeSymbol[0].cy = m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].GetHeight();
								sizeSymbol[1].cx = m_cDisks[TranslateArchivingStatus(m_nBackupFreeSpace)].GetWidth();
								sizeSymbol[1].cy = m_cDisks[TranslateArchivingStatus(m_nBackupFreeSpace)].GetHeight();
								rPane[0].SetRect(0, (m_rArchivingPane.Height() - sizeText[0].cy) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
								rPane[1].SetRect(sizeText[0].cx, (m_rArchivingPane.Height() - sizeSymbol[0].cy + 1) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeSymbol[0].cy + 1) / 2 + sizeSymbol[0].cy);
								rPane[2].SetRect(sizeText[0].cx + sizeSymbol[0].cx, (m_rArchivingPane.Height() - sizeText[1].cy) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeText[1].cy) / 2 + sizeText[1].cy);
								rPane[3].SetRect(sizeText[0].cx + sizeSymbol[0].cx + sizeText[1].cx, (m_rArchivingPane.Height() - sizeSymbol[1].cy + 1) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeSymbol[1].cy + 1) / 2 + sizeSymbol[1].cy);
								rPane[4].SetRect(sizeText[0].cx + sizeSymbol[0].cx + sizeText[1].cx + sizeSymbol[1].cx, (m_rArchivingPane.Height() - sizeText[2].cy) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeText[2].cy) / 2 + sizeText[2].cy);
								cDC.FillSolidRect(CRect(0, 0, m_rArchivingPane.Width(), m_rArchivingPane.Height()), GetSysColor(COLOR_3DFACE));
								cDC.DrawText(szStatus.Left(nPos[0]), rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
								cDC.DrawText(szStatus.Mid(nPos[0] + 1, nPos[1]), rPane[2], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
								cDC.DrawText(szStatus.Mid(nPos[0] + 1 + nPos[1] + 1), rPane[4], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
								m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].Draw(cDC.GetSafeHdc(), rPane[1].TopLeft());
								m_cDisks[TranslateArchivingStatus(m_nBackupFreeSpace)].Draw(cDC.GetSafeHdc(), rPane[3].TopLeft());
							}
							else
							{
								sizeText[0] = cDC.GetTextExtent(szStatus.Left(nPos[0]));
								sizeText[1] = cDC.GetTextExtent(szStatus.Mid(nPos[0] + 1));
								sizeSymbol[0].cx = m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].GetWidth();
								sizeSymbol[0].cy = m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].GetHeight();
								rPane[0].SetRect(0, (m_rArchivingPane.Height() - sizeText[0].cy) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
								rPane[1].SetRect(sizeText[0].cx, (m_rArchivingPane.Height() - sizeSymbol[0].cy + 1) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeSymbol[0].cy + 1) / 2 + sizeSymbol[0].cy);
								rPane[2].SetRect(sizeText[0].cx + sizeSymbol[0].cx, (m_rArchivingPane.Height() - sizeText[1].cy) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeText[1].cy) / 2 + sizeText[1].cy);
								cDC.FillSolidRect(CRect(0, 0, m_rArchivingPane.Width(), m_rArchivingPane.Height()), GetSysColor(COLOR_3DFACE));
								cDC.DrawText(szStatus.Left(nPos[0]), rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
								cDC.DrawText(szStatus.Mid(nPos[0] + 1), rPane[2], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
								m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].Draw(cDC.GetSafeHdc(), rPane[1].TopLeft());
							}
						}
						else
						{
							sizeText[0] = cDC.GetTextExtent(szStatus);
							rPane[0].SetRect(0, (m_rArchivingPane.Height() - sizeText[0].cy) / 2, m_rArchivingPane.Width(), (m_rArchivingPane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							cDC.FillSolidRect(CRect(0, 0, m_rArchivingPane.Width(), m_rArchivingPane.Height()), GetSysColor(COLOR_3DFACE));
							cDC.DrawText(szStatus, rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
						}
						pDC->BitBlt(m_rArchivingPane.left, m_rArchivingPane.top, m_rArchivingPane.Width(), m_rArchivingPane.Height(), &cDC, 0, 0, SRCCOPY);
						cDC.SelectObject(pOldFont);
					}
					cDC.SelectObject(pOldBitmap);
				}
				cBitmap.DeleteObject();
			}
			cDC.DeleteDC();
		}
	}
}

VOID CMainStatusBar::DrawCPUPerformanceStatus(CDC *pDC)
{
	CDC  cDC;
	INT  nPos;
	INT  nSample;
	INT  nSamples;
	CPen  cPen[2];
	CPen  *pOldPen;
	CRgn  rgnClip;
	CRect  rGrid;
	CRect  rPane[3];
	CFont  *pOldFont;
	CSize  sizeText[2];
	CSize  sizeSymbol;
	POINT  *ptSamples;
	CBrush  cBrush;
	CBrush  *pOldBrush;
	CString  szStatus;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	COLORREF  nBrushColor;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_rCPUPerformancePane.IsRectEmpty())
	{
		for (GetClientRect(rGrid); !GetParent()->IsZoomed(); )
		{
			pDC->ExcludeClipRect(rGrid.right - rGrid.Height(), rGrid.top, rGrid.right, rGrid.bottom);
			break;
		}
		if (cDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap.CreateCompatibleBitmap(pDC, m_rCPUPerformancePane.Width(), m_rCPUPerformancePane.Height()))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
				{
					if ((pOldFont = cDC.SelectObject(&m_cPanesFont)))
					{
						if ((nPos = (szStatus = FormatCPUPerformanceStatus()).Find(TAB)) >= 0)
						{
							sizeText[0] = cDC.GetTextExtent(szStatus.Left(nPos));
							sizeText[1] = cDC.GetTextExtent(szStatus.Mid(nPos + 1));
							sizeSymbol.cx = m_cCPUChart.GetWidth();
							sizeSymbol.cy = m_cCPUChart.GetHeight();
							rPane[0].SetRect(0, (m_rCPUPerformancePane.Height() - sizeText[0].cy) / 2, m_rCPUPerformancePane.Width(), (m_rCPUPerformancePane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							rPane[1].SetRect(sizeText[0].cx, (m_rCPUPerformancePane.Height() - sizeSymbol.cy) / 2, m_rCPUPerformancePane.Width(), (m_rCPUPerformancePane.Height() - sizeSymbol.cy) / 2 + sizeSymbol.cy);
							rPane[2].SetRect(m_rCPUPerformancePane.Width() - sizeText[1].cx - pDC->GetTextExtent(SPACE).cx, (m_rCPUPerformancePane.Height() - sizeText[0].cy) / 2, m_rCPUPerformancePane.Width(), (m_rCPUPerformancePane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							cDC.FillSolidRect(CRect(0, 0, m_rCPUPerformancePane.Width(), m_rCPUPerformancePane.Height()), GetSysColor(COLOR_3DFACE));
							cDC.DrawText(szStatus.Left(nPos), rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
							cDC.DrawText(szStatus.Mid(nPos + 1), rPane[2], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
							m_cCPUChart.Draw(cDC.GetSafeHdc(), rPane[1].left, rPane[1].top, sizeSymbol.cx, sizeSymbol.cy);
							if ((ptSamples = (m_nCPUPerformanceValues.GetSize() > 0 && rgnClip.CreateRectRgn(rPane[1].left + GetSystemMetrics(SM_CXEDGE), rPane[1].top + GetSystemMetrics(SM_CYBORDER), rPane[1].left + sizeSymbol.cx - GetSystemMetrics(SM_CXEDGE), rPane[1].top + sizeSymbol.cy - GetSystemMetrics(SM_CYBORDER))) ? (LPPOINT)GlobalAlloc(GPTR, (m_nCPUPerformanceValues.GetSize() + 2)*sizeof(POINT)) : (LPPOINT)NULL))
							{
								for (nSample = 0, nSamples = (INT)min(m_nCPUPerformanceValues.GetSize(), STATUSBAR_CPUPERFORMANCEPANE_SAMPLES), ptSamples[0].x = (LONG)(rPane[1].left + GetSystemMetrics(SM_CXEDGE) + ((m_nCPUPerformanceValues.GetSize() - 1)*(sizeSymbol.cx - 2 * GetSystemMetrics(SM_CXEDGE))) / STATUSBAR_CPUPERFORMANCEPANE_SAMPLES), ptSamples[0].y = rPane[1].top + sizeSymbol.cy - GetSystemMetrics(SM_CYBORDER) - 1, ptSamples[1].x = rPane[1].left + GetSystemMetrics(SM_CXEDGE), ptSamples[1].y = ptSamples[0].y; nSample < nSamples; nSample++)
								{
									ptSamples[nSample + 2].x = rPane[1].left + GetSystemMetrics(SM_CXEDGE) + (nSample*(sizeSymbol.cx - 2 * GetSystemMetrics(SM_CXEDGE))) / STATUSBAR_CPUPERFORMANCEPANE_SAMPLES;
									ptSamples[nSample + 2].y = rPane[1].top + sizeSymbol.cy - GetSystemMetrics(SM_CYBORDER) - (m_nCPUPerformanceValues.GetAt(nSample + max(m_nCPUPerformanceValues.GetSize() - STATUSBAR_CPUPERFORMANCEPANE_SAMPLES, 0))*(sizeSymbol.cy - 2 * GetSystemMetrics(SM_CYBORDER))) / 100 - 1;
								}
								if (cBrush.CreateSolidBrush((nBrushColor = (m_nCPUPerformanceValueCount == STATUSBAR_CPUPERFORMANCEPANEAVERAGE_SAMPLES) ? ((m_fCPUPerformanceValueAverage > 60) ? ((m_fCPUPerformanceValueAverage > 80) ? RGB(184, 9, 6) : RGB(221, 176, 13)) : RGB(53, 136, 4)) : RGB(53, 136, 4))))
								{
									if (cPen[0].CreatePen(PS_SOLID, 1, (m_nCPUPerformanceValueCount == STATUSBAR_CPUPERFORMANCEPANEAVERAGE_SAMPLES) ? ((m_fCPUPerformanceValueAverage > 60) ? ((m_fCPUPerformanceValueAverage > 80) ? RGB(255, 151, 148) : RGB(254, 233, 144)) : RGB(173, 228, 135)) : RGB(173, 228, 135)))
									{
										if (cPen[1].CreatePen(PS_SOLID, 1, nBrushColor))
										{
											if ((pOldBrush = cDC.SelectObject(&cBrush)))
											{
												if (cDC.SelectClipRgn(&rgnClip) != ERROR)
												{
													if ((pOldPen = cDC.SelectObject(&cPen[0])))
													{
														cDC.Polygon(ptSamples, nSamples + 2);
														cDC.SelectObject(pOldPen);
													}
													if ((pOldPen = cDC.SelectObject(&cPen[1])))
													{
														cDC.MoveTo(ptSamples[1]);
														cDC.LineTo(ptSamples[0]);
														cDC.SelectObject(pOldPen);
													}
												}
												cDC.SelectObject(pOldBrush);
											}
											cPen[1].DeleteObject();
										}
										cPen[0].DeleteObject();
									}
									cBrush.DeleteObject();
								}
								rgnClip.DeleteObject();
								GlobalFree(ptSamples);
							}
						}
						else
						{
							sizeText[0] = cDC.GetTextExtent(szStatus);
							rPane[0].SetRect(0, (m_rCPUPerformancePane.Height() - sizeText[0].cy) / 2, m_rCPUPerformancePane.Width(), (m_rCPUPerformancePane.Height() - sizeText[0].cy) / 2 + sizeText[0].cy);
							cDC.FillSolidRect(CRect(0, 0, m_rCPUPerformancePane.Width(), m_rCPUPerformancePane.Height()), GetSysColor(COLOR_3DFACE));
							cDC.DrawText(szStatus, rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
						}
						pDC->BitBlt(m_rCPUPerformancePane.left, m_rCPUPerformancePane.top, m_rCPUPerformancePane.Width(), m_rCPUPerformancePane.Height(), &cDC, 0, 0, SRCCOPY);
						cDC.SelectObject(pOldFont);
					}
					cDC.SelectObject(pOldBitmap);
				}
				cBitmap.DeleteObject();
			}
			cDC.DeleteDC();
		}
	}
}

VOID CMainStatusBar::DrawClockTime(CDC *pDC)
{
	CRect  rGrid;
	CRect  rPane[2];
	CFont  *pOldFont;
	CSize  sizeText;
	CString  szTime;
	COLORREF  nOldBkColor;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_rClockPane.IsRectEmpty())
	{
		for (GetClientRect(rGrid); !GetParent()->IsZoomed(); )
		{
			pDC->ExcludeClipRect(rGrid.right - rGrid.Height(), rGrid.top, rGrid.right, rGrid.bottom);
			break;
		}
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			nOldBkColor = pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
			sizeText = pDC->GetTextExtent((szTime = FormatClockTime()));
			rPane[0].SetRect(m_rClockPane.left, m_rClockPane.top + (m_rClockPane.Height() - sizeText.cy) / 2, m_rClockPane.right, m_rClockPane.top + (m_rClockPane.Height() - sizeText.cy) / 2 + sizeText.cy);
			pDC->DrawText(szTime, (rPane[1] = rPane[0]), DT_LEFT | DT_CALCRECT | DT_SINGLELINE | DT_NOPREFIX);
			pDC->DrawText(szTime, rPane[0], DT_LEFT | DT_SINGLELINE | DT_NOPREFIX);
			pDC->ExcludeClipRect(rPane[1].left, rPane[1].top, rPane[1].right, rPane[1].bottom);
			pDC->FillSolidRect(m_rClockPane, GetSysColor(COLOR_3DFACE));
			pDC->SetBkColor(nOldBkColor);
			pDC->SelectObject(pOldFont);
		}
	}
}

CString CMainStatusBar::FormatNetworkStatus() CONST
{
	CString  szStatus;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((szStatus = m_szNetworkServer).Find(TAB) >= 0) ? (SPACE + szStatus.Left(szStatus.Find(TAB)) + SPACE) : (SPACE + szStatus + SPACE));
}

CString CMainStatusBar::FormatTelemetryStatus() CONST
{
	CString  szStatus;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	szStatus.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_FORMAT), (m_szTMDevice[0] != STRING(IDS_TELEMETRYPROVIDERDEVICE_NONE) && !m_szTMDevice[0].IsEmpty()) ? (LPCTSTR)m_szTMDevice[1] : STRING(IDS_TELEMETRYPROVIDERDEVICE_NONE));
	return(szStatus + SPACE);
}

CString CMainStatusBar::FormatTelecommandStatus() CONST
{
	CString  szFormat;
	CString  szStatus[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (szStatus[0].Format((szFormat = (m_nTCDeviceStatus & TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD) ? STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_CONNECTED) : ((m_nTCDeviceStatus & TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD) ? STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_DISCONNECTED) : STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_NOTCONNECTED))), (m_szTCDevice[1].Find(TAB) >= 0 && m_szTCDevice[1].Find(TAB) < m_szTCDevice[1].GetLength() - 1) ? (LPCTSTR)m_szTCDevice[1].Mid(m_szTCDevice[1].Find(TAB) + 1) : STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_UNKNOWN)); m_szTCDevice[0] == STRING(IDS_TELECOMMANDUPLINKDEVICE_NONE) || m_szTCDevice[0].IsEmpty(); )
	{
		for (szStatus[0].Format(szFormat, STRING(IDS_TELECOMMANDUPLINKDEVICE_NONE)); m_szTCDevice[1] == TAB || m_szTCDevice[1].IsEmpty(); )
		{
			szStatus[0] = STRING(IDS_TELECOMMANDUPLINKDEVICE_NONE);
			break;
		}
		break;
	}
	szStatus[1].Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_FORMAT), (LPCTSTR)szStatus[0]);
	return(szStatus[1] + SPACE);
}

CString CMainStatusBar::FormatArchivingStatus() CONST
{
	INT  nPos[2];
	CString  szStatus;
	CString  szDisk[2];
	CStringTools  cStringTools;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (szDisk[0].Format(STRING(IDS_TELEMETRYARCHIVES_STATUS_ARCHIVESPACE), m_nArchiveFreeSpace), szDisk[1].Format(STRING(IDS_TELEMETRYARCHIVES_STATUS_BACKUPSPACE), m_nBackupFreeSpace), szStatus.Format(STRING(IDS_TELEMETRYARCHIVES_STATUS_FORMAT), (!m_szArchiveFile.IsEmpty()) ? (LPCTSTR)szDisk[0] : STRING(IDS_TELEMETRYARCHIVES_STATUS_NOARCHIVE), (!m_szArchiveFile.IsEmpty()) ? ((!m_bArchiveStatus) ? STRING(IDS_TELEMETRYARCHIVES_STATUS_ARCHIVEOFF) : EMPTYSTRING) : EMPTYSTRING, (!m_szBackupDirectory.IsEmpty()) ? (LPCTSTR)szDisk[1] : STRING(IDS_TELEMETRYARCHIVES_STATUS_NOBACKUP), (!m_szBackupDirectory.IsEmpty()) ? ((!m_bBackupStatus) ? STRING(IDS_TELEMETRYARCHIVES_STATUS_BACKUPOFF) : EMPTYSTRING) : EMPTYSTRING), nPos[0] = szStatus.Find(TAB), nPos[1] = nPos[0] + szStatus.Mid(nPos[0] + 1).Find(TAB) + 1; nPos[0] >= 0 && nPos[1] >= 0 && m_szArchiveFile.IsEmpty(); )
	{
		szStatus = szStatus.Left(nPos[0]) + szStatus.Mid(nPos[0] + 1 + 1);
		nPos[1]--;
		nPos[1]--;
		break;
	}
	for (; nPos[0] >= 0 && nPos[1] >= 0 && m_szBackupDirectory.IsEmpty(); )
	{
		szStatus = szStatus.Left(nPos[1]) + szStatus.Mid(nPos[1] + 1 + 1);
		break;
	}
	return(szStatus + SPACE);
}

CString CMainStatusBar::FormatCPUPerformanceStatus() CONST
{
	CString  szStatus;
	CStringTools  cStringTools;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	szStatus.Format(STRING(IDS_CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME_STATUS), (!m_szCPUPerformanceStatus.IsEmpty()) ? (LPCTSTR)m_szCPUPerformanceStatus : cStringTools.ConvertIntToString(0));
	return(szStatus + SPACE);
}

CString CMainStatusBar::FormatClockDate() CONST
{
	CTimeKey  tTime;

	return tTime.FormatGmt(STRING(IDS_STATUSBAR_DATEFORMAT));
}

CString CMainStatusBar::FormatClockTime() CONST
{
	CTimeKey  tTime;

	return(tTime.FormatGmt(STRING(IDS_STATUSBAR_TIMEFORMAT)) + SPACE);
}

INT CMainStatusBar::CalcNetworkPaneWidth()
{
	CDC  *pDC;
	CFont  *pOldFont;
	CSize  sizeStatus;
	CString  szStatus;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			sizeStatus = pDC->GetTextExtent((szStatus = FormatNetworkStatus()));
			sizeStatus.cx += m_cNetwork[m_nNetworkState != RASCS_Connected].GetWidth();
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeStatus.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CMainStatusBar::CalcTelemetryPaneWidth()
{
	CDC  *pDC;
	INT  nPos;
	CFont  *pOldFont;
	CSize  sizeStatus;
	CString  szStatus;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			for (sizeStatus = pDC->GetTextExtent((szStatus = FormatTelemetryStatus())); (nPos = szStatus.Find(TAB)) >= 0; )
			{
				sizeStatus.cx = pDC->GetTextExtent(szStatus.Left(nPos)).cx + m_cLamps[0][TranslateTMDeviceStatus(m_nTMDeviceStatus)].GetWidth() + pDC->GetTextExtent(szStatus.Mid(nPos + 1)).cx;
				break;
			}
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeStatus.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CMainStatusBar::CalcTelecommandPaneWidth()
{
	CDC  *pDC;
	INT  nPos;
	CFont  *pOldFont;
	CSize  sizeStatus;
	CString  szStatus;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			for (sizeStatus = pDC->GetTextExtent((szStatus = FormatTelecommandStatus())); (nPos = szStatus.Find(TAB)) >= 0; )
			{
				sizeStatus.cx = pDC->GetTextExtent(szStatus.Left(nPos)).cx + m_cLamps[1][TranslateTCDeviceStatus(m_nTCDeviceStatus)].GetWidth() + pDC->GetTextExtent(szStatus.Mid(nPos + 1)).cx;
				break;
			}
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeStatus.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CMainStatusBar::CalcArchivingPaneWidth()
{
	CDC  *pDC;
	INT  nPos[2];
	CFont  *pOldFont;
	CSize  sizeStatus;
	CString  szStatus;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			for (sizeStatus = pDC->GetTextExtent((szStatus = FormatArchivingStatus())); (nPos[0] = szStatus.Find(TAB)) >= 0; )
			{
				if ((nPos[1] = szStatus.Mid(nPos[0] + 1).Find(TAB)) >= 0)
				{
					sizeStatus = pDC->GetTextExtent(szStatus.Left(nPos[0]));
					sizeStatus.cx += m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].GetWidth();
					sizeStatus.cx += pDC->GetTextExtent(szStatus.Mid(nPos[0] + 1, nPos[1])).cx;
					sizeStatus.cx += m_cDisks[TranslateArchivingStatus(m_nBackupFreeSpace)].GetWidth();
					sizeStatus.cx += pDC->GetTextExtent(szStatus.Mid(nPos[0] + 1 + nPos[1] + 1)).cx;
				}
				else
				{
					sizeStatus = pDC->GetTextExtent(szStatus.Left(nPos[0]));
					sizeStatus.cx += m_cDisks[TranslateArchivingStatus(m_nArchiveFreeSpace)].GetWidth();
					sizeStatus.cx += pDC->GetTextExtent(szStatus.Mid(nPos[0] + 1)).cx;
				}
				break;
			}
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeStatus.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CMainStatusBar::CalcCPUPerformancePaneWidth()
{
	CDC  *pDC;
	INT  nPos;
	CFont  *pOldFont;
	CSize  sizeStatus;
	CString  szStatus;
	CStringTools  cStringTools;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			for (szStatus.Format(STRING(IDS_CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME_STATUS), (LPCTSTR)cStringTools.ConvertUIntToString(100)), sizeStatus = pDC->GetTextExtent((szStatus = SPACE + szStatus)); (nPos = szStatus.Find(TAB)) >= 0; )
			{
				sizeStatus = pDC->GetTextExtent(szStatus.Left(nPos));
				sizeStatus.cx += m_cCPUChart.GetWidth();
				sizeStatus.cx += pDC->GetTextExtent(szStatus.Mid(nPos + 1)).cx;
				break;
			}
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeStatus.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CMainStatusBar::CalcClockPaneWidth()
{
	CDC  *pDC;
	CFont  *pOldFont;
	CSize  sizeTime;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			sizeTime = pDC->GetTextExtent(FormatClockTime());
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeTime.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CMainStatusBar::TranslateTMDeviceStatus(UINT nStatus) CONST
{
	UINT  nLampID;

	if (!m_szTMDevice[0].IsEmpty())
	{
		nLampID = (nStatus & IODEVICE_STATUS_GOOD) ? IDP_TMDEVICELAMPGOOD : IDP_TMDEVICELAMP;
		nLampID = (nStatus & IODEVICE_STATUS_WARNING) ? IDP_TMDEVICELAMPWARNING : nLampID;
		nLampID = (nStatus & IODEVICE_STATUS_ERROR) ? IDP_TMDEVICELAMPBAD : nLampID;
		nLampID = (nStatus & IODEVICE_STATUS_OFFLINE) ? IDP_TMDEVICELAMP : nLampID;
		return(nLampID - FIRSTTMDEVICELAMPID);
	}
	return(IDP_TMDEVICELAMPBAD - FIRSTTMDEVICELAMPID);
}

INT CMainStatusBar::TranslateTCDeviceStatus(UINT nStatus) CONST
{
	UINT  nLampID;

	if (!m_szTCDevice[0].IsEmpty())
	{
		nLampID = (nStatus & IODEVICE_STATUS_GOOD) ? IDP_TCDEVICELAMPGOOD : IDP_TCDEVICELAMP;
		nLampID = (nStatus & IODEVICE_STATUS_WARNING) ? IDP_TCDEVICELAMPWARNING : nLampID;
		nLampID = (nStatus & IODEVICE_STATUS_ERROR) ? IDP_TCDEVICELAMPBAD : nLampID;
		nLampID = (nStatus & IODEVICE_STATUS_OFFLINE) ? IDP_TCDEVICELAMP : nLampID;
		return(nLampID - FIRSTTCDEVICELAMPID);
	}
	return(IDP_TCDEVICELAMPBAD - FIRSTTCDEVICELAMPID);
}

INT CMainStatusBar::TranslateArchivingStatus(UINT nStatus) CONST
{
	UINT  nDiskID;

	nDiskID = (nStatus >= 95) ? IDP_ARCHIVEDISKALLFREE : 0;
	nDiskID = (nStatus < 95 && nStatus >= 85) ? IDP_ARCHIVEDISKALMOSTALLFREE : nDiskID;
	nDiskID = (nStatus < 85 && nStatus >= 75) ? IDP_ARCHIVEDISKQUITEALLFREE : nDiskID;
	nDiskID = (nStatus < 75 && nStatus >= 65) ? IDP_ARCHIVEDISKMUCHMORETHANHALFFREE : nDiskID;
	nDiskID = (nStatus < 65 && nStatus >= 55) ? IDP_ARCHIVEDISKMORETHANHALFFREE : nDiskID;
	nDiskID = (nStatus < 55 && nStatus >= 45) ? IDP_ARCHIVEDISKHALFFREE : nDiskID;
	nDiskID = (nStatus < 45 && nStatus >= 35) ? IDP_ARCHIVEDISKLESSTHANHALFFREE : nDiskID;
	nDiskID = (nStatus < 35 && nStatus >= 25) ? IDP_ARCHIVEDISKMUCHLESSTHANHALFFREE : nDiskID;
	nDiskID = (nStatus < 25 && nStatus >= 15) ? IDP_ARCHIVEDISKQUITEEMPTY : nDiskID;
	nDiskID = (nStatus < 15 && nStatus >= 5) ? IDP_ARCHIVEDISKALMOSTEMPTY : nDiskID;
	nDiskID = (nStatus < 5) ? IDP_ARCHIVEDISKEMPTY : nDiskID;
	return(nDiskID - FIRSTARCHIVEDISKSTATUSID);
}

VOID CMainStatusBar::RecalcPanes()
{
	INT  nIndex;
	INT  nWidth;
	UINT  nID;
	UINT  nStyle;
	CRect  rPane;
	CRect  rBar;

	for (GetClientRect(rBar); (nIndex = (!IsShowingProgress()) ? CommandToIndex(ID_STATUSBAR_MESSAGEPANE) : -1) >= 0;)
	{
		SetPaneWidth(nIndex, 2 * rBar.Height());
		break;
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_NETWORKPANE)) >= 0)
	{
		for (GetItemRect(nIndex, rPane), GetPaneInfo(nIndex, nID, nStyle, nWidth); (nWidth = CalcNetworkPaneWidth()) != rPane.Width() && !m_bPanes[0]; )
		{
			m_bPanes[0] = TRUE; SetPaneInfo(nIndex, nID, nStyle, nWidth); m_bPanes[0] = FALSE;
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_TELEMETRYPANE)) >= 0)
	{
		for (GetItemRect(nIndex, rPane), GetPaneInfo(nIndex, nID, nStyle, nWidth); (nWidth = CalcTelemetryPaneWidth()) != rPane.Width() && !m_bPanes[1]; )
		{
			m_bPanes[1] = TRUE; SetPaneInfo(nIndex, nID, nStyle, nWidth); m_bPanes[1] = FALSE;
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_TELECOMMANDPANE)) >= 0)
	{
		for (GetItemRect(nIndex, rPane), GetPaneInfo(nIndex, nID, nStyle, nWidth); (nWidth = CalcTelecommandPaneWidth()) != rPane.Width() && !m_bPanes[2]; )
		{
			m_bPanes[2] = TRUE; SetPaneInfo(nIndex, nID, nStyle, nWidth); m_bPanes[2] = FALSE;
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_ARCHIVINGPANE)) >= 0)
	{
		for (GetItemRect(nIndex, rPane), GetPaneInfo(nIndex, nID, nStyle, nWidth); (nWidth = CalcArchivingPaneWidth()) != rPane.Width() && !m_bPanes[3]; )
		{
			m_bPanes[3] = TRUE; SetPaneInfo(nIndex, nID, nStyle, nWidth); m_bPanes[3] = FALSE;
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_CPUPERFORMANCEPANE)) >= 0)
	{
		for (GetItemRect(nIndex, rPane), GetPaneInfo(nIndex, nID, nStyle, nWidth); (nWidth = CalcCPUPerformancePaneWidth()) != rPane.Width() && !m_bPanes[4]; )
		{
			m_bPanes[4] = TRUE; SetPaneInfo(nIndex, nID, nStyle, nWidth); m_bPanes[4] = FALSE;
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_CLOCKPANE)) >= 0)
	{
		for (GetItemRect(nIndex, rPane), GetPaneInfo(nIndex, nID, nStyle, nWidth); (nWidth = CalcClockPaneWidth()) != rPane.Width() && !m_bPanes[5]; )
		{
			m_bPanes[5] = TRUE; SetPaneInfo(nIndex, nID, nStyle, nWidth); m_bPanes[5] = FALSE;
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_NETWORKPANE)) >= 0)
	{
		for (GetItemRect(nIndex, m_rNetworkPane); !m_rNetworkPane.IsRectEmpty(); )
		{
			m_rNetworkPane.DeflateRect((m_rNetworkPane.Width() - CalcNetworkPaneWidth()) / 2, 0);
			m_rNetworkPane.right = min(rBar.right - rBar.Height(), m_rNetworkPane.right);
			m_rNetworkPane.right = max(m_rNetworkPane.left, m_rNetworkPane.right);
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_TELEMETRYPANE)) >= 0)
	{
		for (GetItemRect(nIndex, m_rTelemetryPane); !m_rTelemetryPane.IsRectEmpty(); )
		{
			m_rTelemetryPane.DeflateRect((m_rTelemetryPane.Width() - CalcTelemetryPaneWidth()) / 2, 0);
			m_rTelemetryPane.right = min(rBar.right - rBar.Height(), m_rTelemetryPane.right);
			m_rTelemetryPane.right = max(m_rTelemetryPane.left, m_rTelemetryPane.right);
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_TELECOMMANDPANE)) >= 0)
	{
		for (GetItemRect(nIndex, m_rTelecommandPane); !m_rTelecommandPane.IsRectEmpty(); )
		{
			m_rTelecommandPane.DeflateRect((m_rTelecommandPane.Width() - CalcTelecommandPaneWidth()) / 2, 0);
			m_rTelecommandPane.right = min(rBar.right - rBar.Height(), m_rTelecommandPane.right);
			m_rTelecommandPane.right = max(m_rTelecommandPane.left, m_rTelecommandPane.right);
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_ARCHIVINGPANE)) >= 0)
	{
		for (GetItemRect(nIndex, m_rArchivingPane); !m_rArchivingPane.IsRectEmpty(); )
		{
			m_rArchivingPane.DeflateRect((m_rArchivingPane.Width() - CalcArchivingPaneWidth()) / 2, 0);
			m_rArchivingPane.right = min(rBar.right - rBar.Height(), m_rArchivingPane.right);
			m_rArchivingPane.right = max(m_rArchivingPane.left, m_rArchivingPane.right);
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_CPUPERFORMANCEPANE)) >= 0)
	{
		for (GetItemRect(nIndex, m_rCPUPerformancePane); !m_rCPUPerformancePane.IsRectEmpty(); )
		{
			m_rCPUPerformancePane.DeflateRect((m_rCPUPerformancePane.Width() - CalcCPUPerformancePaneWidth()) / 2, 0);
			m_rCPUPerformancePane.right = min(rBar.right - rBar.Height(), m_rCPUPerformancePane.right);
			m_rCPUPerformancePane.right = max(m_rCPUPerformancePane.left, m_rCPUPerformancePane.right);
			break;
		}
	}
	if ((nIndex = CommandToIndex(ID_STATUSBAR_CLOCKPANE)) >= 0)
	{
		for (GetItemRect(nIndex, m_rClockPane); !m_rClockPane.IsRectEmpty(); )
		{
			m_rClockPane.DeflateRect((m_rClockPane.Width() - CalcClockPaneWidth()) / 2, 0);
			m_rClockPane.right = min(rBar.right - rBar.Height(), m_rClockPane.right);
			m_rClockPane.right = max(m_rClockPane.left, m_rClockPane.right);
			break;
		}
	}
}

BOOL CMainStatusBar::LoadSymbols()
{
	INT  nSymbol[4];
	INT  nSymbols[4];
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	for (nSymbol[0] = 0, nSymbols[0] = sizeof(m_cNetwork) / sizeof(m_cNetwork[0]); nSymbol[0] < nSymbols[0]; nSymbol[0]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), MAKEINTRESOURCE(FIRSTNETWORKSTATUSID + nSymbol[0]), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_cNetwork[nSymbol[0]].Load(pIStream)))
							{
								pIStream->Release();
								continue;
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		break;
	}
	for (nSymbol[1] = 0, nSymbols[1] = sizeof(m_cLamps) / sizeof(m_cLamps[0]); nSymbol[1] < nSymbols[1]; nSymbol[1]++)
	{
		for (nSymbol[2] = 0, nSymbols[2] = sizeof(m_cLamps[0]) / sizeof(m_cLamps[0][0]); nSymbol[2] < nSymbols[2]; nSymbol[2]++)
		{
			if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (!nSymbol[1]) ? MAKEINTRESOURCE(FIRSTTMDEVICELAMPID + nSymbol[2]) : MAKEINTRESOURCE(FIRSTTCDEVICELAMPID + nSymbol[2]), STRING(IDS_RESOURCETYPE_PICTURE))))
			{
				if ((hMemResource[0] = LoadResource(hModule, hResource)))
				{
					if ((pResource = LockResource(hMemResource[0])))
					{
						if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
						{
							if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
							{
								if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_cLamps[nSymbol[1]][nSymbol[2]].Load(pIStream)))
								{
									pIStream->Release();
									continue;
								}
								pIStream->Release();
							}
						}
					}
				}
			}
			break;
		}
		if (nSymbol[2] < nSymbols[2]) break;
	}
	for (nSymbol[2] = 0, nSymbols[2] = sizeof(m_cDisks) / sizeof(m_cDisks[0]); nSymbol[2] < nSymbols[2]; nSymbol[2]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), MAKEINTRESOURCE(FIRSTARCHIVEDISKSTATUSID + nSymbol[2]), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_cDisks[nSymbol[2]].Load(pIStream)))
							{
								pIStream->Release();
								continue;
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		break;
	}
	for (nSymbol[3] = 0, nSymbols[3] = sizeof(m_cCPUChart) / sizeof(CImage); nSymbol[3] < nSymbols[3]; nSymbol[3]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), MAKEINTRESOURCE(FIRSTCPUCHARTID + nSymbol[3]), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_cCPUChart.Load(pIStream)))
							{
								pIStream->Release();
								continue;
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		break;
	}
	return((nSymbol[0] == nSymbols[0] && nSymbol[1] == nSymbols[1] && nSymbol[2] == nSymbols[2] && nSymbol[3] == nSymbols[3]) ? TRUE : FALSE);
}

VOID CMainStatusBar::FreeSymbols()
{
	INT  nSymbol[2];
	INT  nSymbols[2];

	for (nSymbol[0] = 0, nSymbols[0] = sizeof(m_cNetwork) / sizeof(m_cNetwork[0]); nSymbol[0] < nSymbols[0]; nSymbol[0]++)
	{
		m_cNetwork[nSymbol[0]].Destroy();
		continue;
	}
	for (nSymbol[0] = 0, nSymbols[0] = sizeof(m_cLamps) / sizeof(m_cLamps[0]); nSymbol[0] < nSymbols[0]; nSymbol[0]++)
	{
		for (nSymbol[1] = 0, nSymbols[1] = sizeof(m_cLamps[0]) / sizeof(m_cLamps[0][0]); nSymbol[1] < nSymbols[1]; nSymbol[1]++)
		{
			m_cLamps[nSymbol[0]][nSymbol[1]].Destroy();
			continue;
		}
	}
	for (nSymbol[0] = 0, nSymbols[0] = sizeof(m_cDisks) / sizeof(m_cDisks[0]); nSymbol[0] < nSymbols[0]; nSymbol[0]++)
	{
		m_cDisks[nSymbol[0]].Destroy();
		continue;
	}
	for (nSymbol[0] = 0, nSymbols[0] = sizeof(m_cCPUChart) / sizeof(CImage); nSymbol[0] < nSymbols[0]; nSymbol[0]++)
	{
		m_cCPUChart.Destroy();
		continue;
	}
}

BOOL CMainStatusBar::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CMainStatusBar::Unlock()
{
	return m_pCriticalSection->Unlock();
}

void CMainStatusBar::PostNcDestroy()
{
	FreeSymbols();
	CMFCStatusBar::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMainStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CMainStatusBar)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBar message handlers

int CMainStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFont  *pFont;
	LOGFONT  lfFont;

	if (CMFCStatusBar::OnCreate(lpCreateStruct) != -1)
	{
		if ((pFont = (LoadSymbols()) ? GetFont() : (CFont *)NULL) && pFont->GetLogFont(&lfFont) > 0 && m_cPanesFont.CreateFontIndirect(&lfFont))
		{
			if (SetTimer(STATUSBAR_TIMERID, STATUSBAR_TIMEOUT, NULL))
			{
				if (m_cClockThread.Start(this))
				{
					m_cCPUPerformanceMonitor.Start();
					EnableToolTips();
					return 0;
				}
				KillTimer(STATUSBAR_TIMERID);
			}
		}
	}
	return -1;
}

BOOL CMainStatusBar::OnEraseBkgnd(CDC *pDC)
{
	if (Lock())
	{
		for (RecalcPanes(); CommandToIndex(ID_STATUSBAR_NETWORKPANE) >= 0; )
		{
			pDC->ExcludeClipRect(m_rNetworkPane);
			break;
		}
		if (CommandToIndex(ID_STATUSBAR_TELEMETRYPANE) >= 0) pDC->ExcludeClipRect(m_rTelemetryPane);
		if (CommandToIndex(ID_STATUSBAR_TELECOMMANDPANE) >= 0) pDC->ExcludeClipRect(m_rTelecommandPane);
		if (CommandToIndex(ID_STATUSBAR_ARCHIVINGPANE) >= 0) pDC->ExcludeClipRect(m_rArchivingPane);
		if (CommandToIndex(ID_STATUSBAR_CPUPERFORMANCEPANE) >= 0) pDC->ExcludeClipRect(m_rCPUPerformancePane);
		if (CommandToIndex(ID_STATUSBAR_CLOCKPANE) >= 0) pDC->ExcludeClipRect(m_rClockPane);
		Unlock();
	}
	return CMFCStatusBar::OnEraseBkgnd(pDC);
}

void CMainStatusBar::OnPaint()
{
	CToolInfo  cToolInfo;

	if (Lock())
	{
		for (RecalcPanes(), DrawPanes(); CommandToIndex(ID_STATUSBAR_NETWORKPANE) >= 0; )
		{
			ValidateRect(m_rNetworkPane);
			break;
		}
		if (CommandToIndex(ID_STATUSBAR_TELEMETRYPANE) >= 0) ValidateRect(m_rTelemetryPane);
		if (CommandToIndex(ID_STATUSBAR_TELECOMMANDPANE) >= 0) ValidateRect(m_rTelecommandPane);
		if (CommandToIndex(ID_STATUSBAR_ARCHIVINGPANE) >= 0) ValidateRect(m_rArchivingPane);
		if (CommandToIndex(ID_STATUSBAR_CPUPERFORMANCEPANE) >= 0) ValidateRect(m_rCPUPerformancePane);
		if (CommandToIndex(ID_STATUSBAR_CLOCKPANE) >= 0) ValidateRect(m_rClockPane);
		Unlock();
	}
	if (CommandToIndex(ID_STATUSBAR_NETWORKPANE) >= 0 && IsWindow(m_wndToolTip[0].GetSafeHwnd()))
	{
		for (m_wndToolTip[0].GetToolInfo(cToolInfo, this, ID_STATUSBAR_NETWORKPANE); !m_rNetworkPane.EqualRect(&cToolInfo.rect); )
		{
			SetRect(&cToolInfo.rect, m_rNetworkPane.left, m_rNetworkPane.top, m_rNetworkPane.right, m_rNetworkPane.bottom);
			m_wndToolTip[0].SetToolInfo(&cToolInfo);
			break;
		}
	}
	if (CommandToIndex(ID_STATUSBAR_TELEMETRYPANE) >= 0 && IsWindow(m_wndToolTip[1].GetSafeHwnd()))
	{
		for (m_wndToolTip[1].GetToolInfo(cToolInfo, this, ID_STATUSBAR_TELEMETRYPANE); !m_rTelemetryPane.EqualRect(&cToolInfo.rect); )
		{
			SetRect(&cToolInfo.rect, m_rTelemetryPane.left, m_rTelemetryPane.top, m_rTelemetryPane.right, m_rTelemetryPane.bottom);
			m_wndToolTip[1].SetToolInfo(&cToolInfo);
			break;
		}
	}
	if (CommandToIndex(ID_STATUSBAR_TELECOMMANDPANE) >= 0 && IsWindow(m_wndToolTip[2].GetSafeHwnd()))
	{
		for (m_wndToolTip[2].GetToolInfo(cToolInfo, this, ID_STATUSBAR_TELECOMMANDPANE); !m_rTelecommandPane.EqualRect(&cToolInfo.rect); )
		{
			SetRect(&cToolInfo.rect, m_rTelecommandPane.left, m_rTelecommandPane.top, m_rTelecommandPane.right, m_rTelecommandPane.bottom);
			m_wndToolTip[2].SetToolInfo(&cToolInfo);
			break;
		}
	}
	if (CommandToIndex(ID_STATUSBAR_ARCHIVINGPANE) >= 0 && IsWindow(m_wndToolTip[3].GetSafeHwnd()))
	{
		for (m_wndToolTip[3].GetToolInfo(cToolInfo, this, ID_STATUSBAR_ARCHIVINGPANE); !m_rArchivingPane.EqualRect(&cToolInfo.rect); )
		{
			SetRect(&cToolInfo.rect, m_rArchivingPane.left, m_rArchivingPane.top, m_rArchivingPane.right, m_rArchivingPane.bottom);
			m_wndToolTip[3].SetToolInfo(&cToolInfo);
			break;
		}
	}
	if (CommandToIndex(ID_STATUSBAR_CPUPERFORMANCEPANE) >= 0 && IsWindow(m_wndToolTip[4].GetSafeHwnd()))
	{
		for (m_wndToolTip[4].GetToolInfo(cToolInfo, this, ID_STATUSBAR_CPUPERFORMANCEPANE); !m_rCPUPerformancePane.EqualRect(&cToolInfo.rect); )
		{
			SetRect(&cToolInfo.rect, m_rCPUPerformancePane.left, m_rCPUPerformancePane.top, m_rCPUPerformancePane.right, m_rCPUPerformancePane.bottom);
			m_wndToolTip[4].SetToolInfo(&cToolInfo);
			break;
		}
	}
	if (CommandToIndex(ID_STATUSBAR_CLOCKPANE) >= 0 && IsWindow(m_wndToolTip[5].GetSafeHwnd()))
	{
		for (m_wndToolTip[5].GetToolInfo(cToolInfo, this, ID_STATUSBAR_CLOCKPANE); !m_rClockPane.EqualRect(&cToolInfo.rect); )
		{
			SetRect(&cToolInfo.rect, m_rClockPane.left, m_rClockPane.top, m_rClockPane.right, m_rClockPane.bottom);
			m_wndToolTip[5].SetToolInfo(&cToolInfo);
			break;
		}
	}
	CMFCStatusBar::OnPaint();
}

void CMainStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;
	INT  nToolTip;
	INT  nToolTips;

	for (nToolTip = 0, nToolTips = (INT)(sizeof(m_wndToolTip) / sizeof(CMainStatusBarToolTipCtrl)), CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG)); nToolTip < nToolTips; nToolTip++)
	{
		if (IsWindow(m_wndToolTip[nToolTip].GetSafeHwnd()))
		{
			m_wndToolTip[nToolTip].RelayEvent(&sMsg);
			continue;
		}
	}
	CMFCStatusBar::OnMouseMove(nFlags, point);
}

void CMainStatusBar::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint  ptMenu;
	CLocaleMenu  cMenu;
	CMFCPopupMenu  *pFloatingMenu;

	for (ClientToScreen(&(ptMenu = point)); (pFloatingMenu = (cMenu.LoadMenu(IDR_STATUSBARFLOATINGMENU)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL); )
	{
		pFloatingMenu->Create(GetParent(), ptMenu.x, ptMenu.y, cMenu.Detach());
		break;
	}
	CMFCStatusBar::OnRButtonDown(nFlags, point);
}

BOOL CMainStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	CTCUplinkDevice  cTCDevice;
	CTMProviderDevice  cTMDevice;
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_STATUSBAR_NETWORKPANE:
	{ m_szToolTipText[0] = GetRASService()->GetDetails();
	pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[0];
	return TRUE;
	}
	case ID_STATUSBAR_TELEMETRYPANE:
	{ if (GetTMService()->GetActiveTMProviderDevice(&cTMDevice))
	{
		for (pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)(m_szToolTipText[1] = cTMDevice.GetToolTipText()); Lock(); )
		{
			pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[1];
			Unlock();
			break;
		}
		return !m_szToolTipText[1].IsEmpty();
	}
	break;
	}
	case ID_STATUSBAR_TELECOMMANDPANE:
	{ if (GetTCService()->GetActiveTCUplinkDevice(&cTCDevice))
	{
		for (pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)(m_szToolTipText[2] = cTCDevice.GetToolTipText()); Lock(); )
		{
			pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[2];
			Unlock();
			break;
		}
		return !m_szToolTipText[2].IsEmpty();
	}
	break;
	}
	case ID_STATUSBAR_ARCHIVINGPANE:
	{ if (GetTMService()->GetTMHistoryFilesDetails(m_szToolTipText[3]))
	{
		pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[3];
		return TRUE;
	}
	break;
	}
	case ID_STATUSBAR_CPUPERFORMANCEPANE:
	{ for (m_szToolTipText[4] = (m_cCPUPerformanceMonitor.IsAvailable(CPUPERFORMANCEMONITOR_COUNTER_POOLNONPAGEDBYTES)) ? m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_POOLNONPAGEDBYTES) : EMPTYSTRING; m_cCPUPerformanceMonitor.IsAvailable(CPUPERFORMANCEMONITOR_COUNTER_POOLPAGEDBYTES); )
	{
		m_szToolTipText[4] += (!m_szToolTipText[4].IsEmpty()) ? (CString(EOL) + m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_POOLPAGEDBYTES)) : m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_POOLPAGEDBYTES);
		break;
	}
	if (m_cCPUPerformanceMonitor.IsAvailable(CPUPERFORMANCEMONITOR_COUNTER_PRIVATEBYTES)) m_szToolTipText[4] += (!m_szToolTipText[4].IsEmpty()) ? (CString(EOL) + m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_PRIVATEBYTES)) : m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_PRIVATEBYTES);
	if (m_cCPUPerformanceMonitor.IsAvailable(CPUPERFORMANCEMONITOR_COUNTER_VIRTUALBYTES)) m_szToolTipText[4] += (!m_szToolTipText[4].IsEmpty()) ? (CString(EOL) + m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_VIRTUALBYTES)) : m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_VIRTUALBYTES);
	if (m_cCPUPerformanceMonitor.IsAvailable(CPUPERFORMANCEMONITOR_COUNTER_THREADCOUNT)) m_szToolTipText[4] += (!m_szToolTipText[4].IsEmpty()) ? (CString(EOL) + m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_THREADCOUNT)) : m_cCPUPerformanceMonitor.Measure(CPUPERFORMANCEMONITOR_COUNTER_THREADCOUNT);
	pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[4];
	return TRUE;
	break;
	}
	case ID_STATUSBAR_CLOCKPANE:
	{ m_szToolTipText[5] = FormatClockDate();
	pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[5];
	return TRUE;
	break;
	}
	}
	return FALSE;
}

LRESULT CMainStatusBar::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	CFont  cFont;
	LOGFONT  lfFont;
	LRESULT  lResult;

	for (lResult = Default(); wParam != (WPARAM)NULL; )
	{
		if (GetObject((HGDIOBJ)wParam, sizeof(LOGFONT), &lfFont) > 0 && cFont.CreateFontIndirect(&lfFont))
		{
			m_cPanesFont.DeleteObject();
			m_cPanesFont.Attach(cFont.Detach());
		}
		break;
	}
	return lResult;
}

void CMainStatusBar::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == STATUSBAR_TIMERID) UpdateNetworkPane();
	CMFCStatusBar::OnTimer(nEventID);
}

void CMainStatusBar::OnDestroy()
{
	m_cClockThread.Stop();
	m_cCPUPerformanceMonitor.Stop();
	KillTimer(STATUSBAR_TIMERID);
	CMFCStatusBar::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CMainWnd

IMPLEMENT_DYNCREATE(CMainWnd, CLocaleMDIFrameWnd)

CMainWnd::CMainWnd() : CLocaleMDIFrameWnd()
{
	m_pDisplayArea = new CDisplayArea;
	m_pDisplayFrame = new CDisplayFrame;
	m_pCLCWToolWnd = (CCLCWToolWnd *)NULL;
	m_pReportWnd = (CEventBoxWnd *)NULL;
	m_pLogoWnd = (CLogoWnd *)NULL;
	m_bBattery = FALSE;
	m_nExitID = 0;
}

CMainWnd::~CMainWnd()
{
	delete m_pDisplayFrame;
	delete m_pDisplayArea;
}

BOOL CMainWnd::Create()
{
	if (LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL))
	{
		ShowMessage(IDS_STATUSBAR_INITIALIZING);
		UpdateWindow();
		UpdateTitle();
		UpdateMenus();
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWnd::PreCreateWindow(CREATESTRUCT &cs)
{
	CSize  size;
	CRect  rPosition;
	APPBARDATA  sBarData = { sizeof(sBarData) };

	SHAppBarMessage(ABM_GETTASKBARPOS, &sBarData);
	size.cx = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	size.cy = GetSystemMetrics(SM_CYVIRTUALSCREEN) - (sBarData.rc.bottom - sBarData.rc.top);
	rPosition.SetRect(0, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + 1) : 0, size.cx, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + size.cy) : size.cy);
	cs.x = rPosition.left;
	cs.y = rPosition.top;
	cs.cx = rPosition.Width();
	cs.cy = rPosition.Height();
	return CLocaleMDIFrameWnd::PreCreateWindow(cs);
}

VOID CMainWnd::SaveLayout(UINT nCode)
{
	CHourglassCursor  cCursor;

	ShowMessage((nCode != CDesktopApp::Reset) ? IDS_STATUSBAR_SAVING : IDS_STATUSBAR_RESETTING);
	ReportMessage((nCode != CDesktopApp::Reset) ? IDS_STATUSBAR_SAVING : IDS_STATUSBAR_RESETTING);
	ReportEvent((m_pDisplayArea->CheckDisplays(TRUE) && (nCode == CDesktopApp::Reset || !m_pDisplayArea->SaveDisplays(FALSE)) && nCode != CDesktopApp::Reset) ? SYSTEM_WARNING_SPACECRAFT_PROFILE_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((m_pDisplayArea->CheckDisplays(TRUE) && (nCode  &&  !m_pDisplayArea->StopDisplays(FALSE)) && nCode != CDesktopApp::Reset) ? SYSTEM_WARNING_DISPLAY_STOP_FAILURE : SYSTEM_NOERROR);
	m_pDisplayArea->DestroyDisplays(nCode, TRUE);
}

BOOL CMainWnd::LoadLayout()
{
	BOOL  bSuccess;
	CHourglassCursor  cCursor;

	for (ShowMessage(IDS_STATUSBAR_LOADING), UpdateTitle(); m_pDisplayArea->Create(this, &m_wndRibbonBar); )
	{
		if (SetReportDisplay(((bSuccess = m_pDisplayArea->LoadDisplays(FALSE)) || !bSuccess) ? (CEventBoxWnd *)m_pDisplayArea->FindDisplay(DISPLAY_TYPE_EVENTBOX) : (CEventBoxWnd *)NULL))
		{
			if (m_pDisplayArea->CheckDisplays(FALSE) && m_pDisplayArea->StartDisplays(FALSE))
			{
				for (ReportMessage(IDS_STATUSBAR_LOADING); !bSuccess; )
				{
					ReportEvent(SYSTEM_WARNING_SPACECRAFT_PROFILE_LOAD_FAILURE);
					break;
				}
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

VOID CMainWnd::SaveDisplays(UINT nCode)
{
	CHourglassCursor  cCursor;

	ShowMessage((m_pDisplayArea->CheckDisplays(TRUE) && nCode != CDesktopApp::Reset) ? IDS_STATUSBAR_SAVING_DISPLAYS : 0);
	ReportMessage((m_pDisplayArea->CheckDisplays(TRUE) && nCode != CDesktopApp::Reset) ? IDS_STATUSBAR_SAVING_DISPLAYS : 0);
	ReportEvent((m_pDisplayArea->CheckDisplays(TRUE) && (nCode == CDesktopApp::Reset || !m_pDisplayArea->SaveDisplays(TRUE)) && nCode != CDesktopApp::Reset) ? SYSTEM_WARNING_DISPLAYS_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((m_pDisplayArea->CheckDisplays(TRUE) && (nCode == CDesktopApp::Reset || !SaveTemporaryDisplays()) && nCode != CDesktopApp::Reset) ? SYSTEM_WARNING_TEMPORARYDISPLAYS_SAVE_FAILURE : SYSTEM_NOERROR);
	m_pDisplayArea->DestroyDisplays(nCode, FALSE);
}

BOOL CMainWnd::LoadDisplays()
{
	BOOL  bSuccess[2];
	CHourglassCursor  cCursor;

	ShowMessage((m_pDisplayArea->CheckDisplays(FALSE)) ? IDS_STATUSBAR_LOADING_DISPLAYS : 0);
	ReportMessage((m_pDisplayArea->CheckDisplays(FALSE)) ? IDS_STATUSBAR_LOADING_DISPLAYS : 0);
	ReportEvent((!(bSuccess[0] = (!m_pDisplayArea->CheckDisplays(FALSE) || LoadTemporaryDisplays()))) ? SYSTEM_WARNING_TEMPORARYDISPLAYS_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!(bSuccess[1] = (!m_pDisplayArea->CheckDisplays(FALSE) || m_pDisplayArea->LoadDisplays(TRUE)))) ? SYSTEM_WARNING_DISPLAYS_LOAD_FAILURE : SYSTEM_NOERROR);
	return(bSuccess[0] && bSuccess[1]);
}

BOOL CMainWnd::CheckDisplays() CONST
{
	return m_pDisplayArea->CheckDisplays(TRUE);
}

VOID CMainWnd::SaveUser(UINT nCode)
{
	CHourglassCursor  cCursor;

	ShowMessage((nCode != CDesktopApp::Reset) ? IDS_STATUSBAR_SAVING_USER : 0);
	ReportMessage((nCode != CDesktopApp::Reset) ? IDS_STATUSBAR_SAVING_USER : 0);
	ReportEvent((!StopCLCWPanel()) ? SYSTEM_WARNING_CLCWPANEL_STOP_FAILURE : SYSTEM_NOERROR);
}

BOOL CMainWnd::LoadUser()
{
	CHourglassCursor  cCursor;

	ShowMessage(IDS_STATUSBAR_LOADING_USER);
	ReportMessage(IDS_STATUSBAR_LOADING_USER);
	ReportEvent((!StartCLCWPanel()) ? SYSTEM_WARNING_CLCWPANEL_START_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

VOID CMainWnd::StartDisplays()
{
	ReportEvent((!m_pDisplayArea->StartDisplays(TRUE)) ? SYSTEM_WARNING_DISPLAY_START_FAILURE : SYSTEM_NOERROR);
}

VOID CMainWnd::StopDisplays()
{
	ReportEvent((!m_pDisplayArea->StopDisplays(TRUE)) ? SYSTEM_WARNING_DISPLAY_STOP_FAILURE : SYSTEM_NOERROR);
}

BOOL CMainWnd::StartAssistant()
{
	return FALSE;
}

VOID CMainWnd::StopAssistant()
{
	return;
}

VOID CMainWnd::UpdateTitle()
{
	CString  szTitle;

	if (TestAccount())
	{
		szTitle.Format(STRING(IDS_DESKTOP_TITLE), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetAppTitle());
		SetWindowText(szTitle);
		return;
	}
	SetWindowText(GetAppTitle());
}

VOID CMainWnd::UpdateLayout()
{
	UINT  nShow;
	CSize  size;
	CRect  rPosition;
	CUIntArray  nPaneIDs;
	APPBARDATA  sBarData;
	CProfile  cProfile;

	if (cProfile.GetState(nShow) && cProfile.GetPosition(rPosition))
	{
		for (sBarData.cbSize = sizeof(sBarData), SHAppBarMessage(ABM_GETTASKBARPOS, &sBarData), size.cx = GetSystemMetrics(SM_CXVIRTUALSCREEN), size.cy = GetSystemMetrics(SM_CYVIRTUALSCREEN) - (sBarData.rc.bottom - sBarData.rc.top); rPosition.left < 0 || rPosition.top < 0 || (rPosition.top >= sBarData.rc.top && rPosition.top <= sBarData.rc.bottom) || rPosition.right > GetSystemMetrics(SM_CXVIRTUALSCREEN) || rPosition.bottom > GetSystemMetrics(SM_CYVIRTUALSCREEN) || (rPosition.bottom >= sBarData.rc.top && rPosition.bottom <= sBarData.rc.bottom) || rPosition.Width() > size.cx || rPosition.Height() > size.cy; )
		{
			rPosition.SetRect(0, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + 1) : 0, size.cx, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + size.cy) : size.cy);
			break;
		}
		for (SetWindowPos((CONST CWnd *) NULL, rPosition.left, rPosition.top, rPosition.Width(), rPosition.Height(), SWP_SHOWWINDOW | SWP_NOZORDER); nShow != SW_SHOWMINIMIZED; )
		{
			ShowWindow(nShow);
			break;
		}
	}
	else
	{
		ShowWindow(SW_SHOWNORMAL);
	}
	if (!cProfile.GetStatusBarState(nPaneIDs))
	{
		nPaneIDs.RemoveAll();
	}
	m_wndStatusBar.SetIndicators(nPaneIDs);
}

VOID CMainWnd::UpdateStatusBar()
{
	for (m_wndStatusBar.SetIndicators(); !IsLogginginTMService(); )
	{
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE), STRING(IDS_STATUSBAR_READY));
		break;
	}
	m_wndStatusBar.UpdateAllPanes();
}

VOID CMainWnd::UpdateDisplays()
{
	m_pDisplayArea->UpdateDisplays();
}

VOID CMainWnd::UpdateMenus()
{
	INT  nID;
	INT  nIDs;
	INT  nPage;
	INT  nPages;
	INT  nItem;
	INT  nItems;
	INT  nElement;
	INT  nElements;
	UINT  nMenuID;
	BOOL  bPage;
	CMenu  *pMenu;
	CString  szPage;
	CString  szItem[2];
	CPtrArray  pDisplays;
	CImageList  cImages[2];
	CUIntArray  nImageIDs;
	CStringArray  szPages;
	CLocaleMenu  cDisplayMenu;
	CDisplayWnd  *pDisplayWnd;
	CMFCRibbonPanel  *pPanel;
	CMFCRibbonButton  *pButton[3];
	CMFCRibbonCategory  *pCategory;
	CMFCRibbonSeparator  *pSeparator;
	CMFCRibbonBaseElement  *pElement[3];
	CArray<CMFCRibbonBaseElement *, CMFCRibbonBaseElement *>  cElements;

	if ((pPanel = ((pCategory = ((pElement[0] = (GetDisplayArea()) ? m_wndRibbonBar.FindByID(IDM_PRINTSETUP) : (CMFCRibbonBaseElement *)NULL)) ? pElement[0]->GetParentCategory() : (CMFCRibbonCategory *)NULL)) ? pCategory->GetPanel(0) : (CMFCRibbonPanel *)NULL))
	{
		for (nElement = 0, pPanel->GetElements(cElements), nElements = (INT)cElements.GetSize(); nElement < nElements; cElements.RemoveAll(), pPanel->GetElements(cElements), nElements = (INT)cElements.GetSize())
		{
			if ((pElement[1] = cElements.GetAt(nElement)) && pElement[1]->GetID() != IDM_PRINTSETUP)
			{
				pPanel->Remove(pPanel->GetIndex(pElement[1]));
				continue;
			}
			break;
		}
		if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->QueryDefaultMenu(cDisplayMenu, cImages[0], nImageIDs))
		{
			for (nItem = 0, nItems = (cDisplayMenu.GetSafeHmenu()) ? cDisplayMenu.GetMenuItemCount() : 0; nItem < nItems; nItem++)
			{
				if ((nMenuID = cDisplayMenu.GetMenuItemID(nItem)) != 0 && nMenuID != (UINT)-1)
				{
					if (cDisplayMenu.GetMenuString(nMenuID, szItem[0], MF_BYCOMMAND) > 0)
					{
						for (nID = 0, nIDs = (INT)nImageIDs.GetSize(); nID < nIDs; nID++)
						{
							if (nMenuID == nImageIDs.GetAt(nID)) break;
							continue;
						}
						if (nID < nIDs)
						{
							if ((pButton[0] = new CMainRibbonButton(nMenuID, szItem[0], cImages[0].ExtractIcon(nID), cImages[0].ExtractIcon(nID))))
							{
								if (pPanel->Insert(pButton[0], nItem)) continue;
								delete pButton[0];
							}
							continue;
						}
						if (cImages[1].Create(IDB_DIRECTORYIMAGE, pCategory->GetImageSize(FALSE).cx, 1, RGB(0, 0, 0)))
						{
							if ((pButton[0] = new CMainRibbonButton(nMenuID, szItem[0], cImages[1].ExtractIcon(0), cImages[1].ExtractIcon(0))))
							{
								if (pPanel->Insert(pButton[0], nItem))
								{
									cImages[1].DeleteImageList();
									continue;
								}
								delete pButton[0];
							}
							cImages[1].DeleteImageList();
						}
					}
					continue;
				}
				if (!nMenuID)
				{
					if ((pSeparator = new CMFCRibbonSeparator(TRUE)))
					{
						if (pPanel->Insert(pSeparator, nItem)) continue;
						delete pSeparator;
					}
					continue;
				}
				if (cDisplayMenu.GetMenuString(nItem, szItem[0], MF_BYPOSITION) > 0)
				{
					if (cImages[1].Create(IDB_DIRECTORYIMAGE, pCategory->GetImageSize(FALSE).cx, 1, RGB(0, 0, 0)))
					{
						if ((pButton[0] = new CMainRibbonButton(0, szItem[0], cImages[1].ExtractIcon(0), cImages[1].ExtractIcon(0))))
						{
							if (ConstructSubMenu(cDisplayMenu.GetSubMenu(nItem), pButton[0], cImages[0], cImages[1], nImageIDs) && pPanel->Insert(pButton[0], nItem))
							{
								cImages[1].DeleteImageList();
								continue;
							}
							delete pButton[0];
						}
						cImages[1].DeleteImageList();
					}
				}
			}
		}
	}
	if ((pButton[0] = (GetDisplayArea()) ? (CMFCRibbonButton *)(pElement[0] = m_wndRibbonBar.FindByID(IDM_WINDOWS)) : (CMFCRibbonButton *)NULL))
	{
		for (nElement = 0, nElements = (INT)pButton[0]->GetSubItems().GetCount(); nElement < nElements; nElements--)
		{
			if ((pElement[1] = pButton[0]->GetSubItems().GetAt(nElements - 1)) && pElement[1]->GetID() != IDM_LOCK)
			{
				if (!pButton[0]->RemoveSubItem(nElements - 1)) break;
				continue;
			}
			break;
		}
		for (nID = IDM_FIRSTDISPLAYWINDOW; GetDisplayArea()->GetType() == DISPLAYAREA_TYPE_STANDARD; )
		{
			for (nItem = 1, nItems = GetDisplayArea()->EnumDisplays(pDisplays, TRUE), nItems = min(IDM_LASTDISPLAYWINDOWS - IDM_FIRSTDISPLAYWINDOWS + 1, nItems); nItem <= nItems; nItem++)
			{
				if ((pDisplayWnd = (CDisplayWnd*)pDisplays.GetAt(nItem - 1)))
				{
					for (szItem[0].Empty(); pDisplayWnd->Check(); )
					{
						pDisplayWnd->GetWindowText(szItem[0]);
						szItem[1].Format((nItem < 10) ? STRING(IDS_WINDOW_MENUITEM) : STRING(IDS_WINDOW_EXTENDEDMENUITEM), nItem, (LPCTSTR)szItem[0]);
						break;
					}
					if ((pButton[1] = (!szItem[0].IsEmpty()) ? new CMainRibbonButton(nID, szItem[1]) : (CMFCRibbonButton*)NULL))
					{
						if (nID == IDM_FIRSTDISPLAYWINDOW)
						{
							if ((pSeparator = new CMFCRibbonSeparator(TRUE)))
							{
								pButton[0]->AddSubItem(pSeparator);
							}
						}
						pButton[0]->AddSubItem(pButton[1]);
						nID = nID + 1;
						continue;
					}
				}
			}
			if ((pButton[1] = (nItems > 0) ? new CMainRibbonButton(IDM_DISPLAYWINDOWS, STRING(IDS_WINDOW_MENUITEM_WINDOWS)) : (CMFCRibbonButton*)NULL))
			{
				pButton[0]->AddSubItem(pButton[1]);
			}
			break;
		}
		if (GetDisplayArea()->GetType() == DISPLAYAREA_TYPE_FOLDER)
		{
			for (nPage = 1, nPages = GetDisplayArea()->EnumPages(szPages), nPages = min(IDM_LASTDISPLAYPAGE - IDM_FIRSTDISPLAYPAGE + 1, nPages), bPage = FALSE; nPage <= nPages; nPage++)
			{
				szPage.Format((nPage < 10) ? STRING(IDS_WINDOW_MENUITEM) : STRING(IDS_WINDOW_EXTENDEDMENUITEM), nPage, (LPCTSTR)szPages.GetAt(nPage - 1));
				if ((pButton[1] = (!szPages.GetAt(nPage - 1).IsEmpty()) ? new CMainRibbonButton(0, szPage) : (CMFCRibbonButton*)NULL) != (CMFCRibbonButton*)NULL)
				{
					for (nItem = 1, nItems = GetDisplayArea()->EnumDisplays(nPage - 1, pDisplays, TRUE), nItems = min(IDM_LASTDISPLAYWINDOWS - IDM_FIRSTDISPLAYWINDOWS + 1, nItems); nItem <= nItems; nItem++)
					{
						if ((pDisplayWnd = (CDisplayWnd*)pDisplays.GetAt(nItem - 1)))
						{
							for (szItem[0].Empty(); pDisplayWnd->Check(); )
							{
								pDisplayWnd->GetWindowText(szItem[0]);
								szItem[1].Format((nItem < 10) ? STRING(IDS_WINDOW_MENUITEM) : STRING(IDS_WINDOW_EXTENDEDMENUITEM), nItem, (LPCTSTR)szItem[0]);
								break;
							}
							if ((pButton[2] = (!szItem[0].IsEmpty()) ? new CMainRibbonButton(nID, szItem[1]) : (CMFCRibbonButton*)NULL))
							{
								pButton[1]->AddSubItem(pButton[2]);
								nID = nID + 1;
								continue;
							}
						}
					}
					for (nID += (INT)(pDisplays.GetSize() - nItems); (pButton[2] = new CMainRibbonButton(IDM_DISPLAYWINDOWS + nPage - 1, STRING(IDS_WINDOW_MENUITEM_WINDOWS))); )
					{
						pButton[1]->AddSubItem(pButton[2]);
						break;
					}
					if (!bPage)
					{
						if ((pSeparator = new CMFCRibbonSeparator(TRUE)))
						{
							pButton[0]->AddSubItem(pSeparator);
						}
						bPage = TRUE;
					}
					pButton[0]->AddSubItem(pButton[1]);
				}
			}
			if ((pButton[1] = (nPages > 0) ? new CMainRibbonButton(IDM_DISPLAYPAGES, STRING(IDS_WINDOW_MENUITEM_PAGES)) : (CMFCRibbonButton*)NULL))
			{
				pButton[0]->AddSubItem(pButton[1]);
			}
		}
	}
	if ((pMenu = GetSystemMenu(FALSE)))
	{
		pMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | ((!TestAccount() || !CheckDisplays() || CheckAccountPrivilege(PRIVILEGE_EXIT)) ? MF_ENABLED : MF_GRAYED));
	}
}

VOID CMainWnd::UpdateNetworkStatus()
{
	m_wndStatusBar.UpdateNetworkPane();
}
VOID CMainWnd::UpdateNetworkStatus(LPCTSTR pszServer, RASCONNSTATE nState)
{
	m_wndStatusBar.UpdateNetworkPane(pszServer, nState);
}

VOID CMainWnd::UpdateTelemetryStatus()
{
	m_wndStatusBar.UpdateTelemetryPane();
}
VOID CMainWnd::UpdateTelemetryStatus(CONST CTMProviderDevice *pDevice)
{
	m_wndStatusBar.UpdateTelemetryPane(pDevice);
}

VOID CMainWnd::UpdateTelecommandStatus()
{
	m_wndStatusBar.UpdateTelecommandPane();
}
VOID CMainWnd::UpdateTelecommandStatus(CONST CTCUplinkDevice *pDevice)
{
	m_wndStatusBar.UpdateTelecommandPane(pDevice);
}

VOID CMainWnd::UpdateArchivingStatus()
{
	m_wndStatusBar.UpdateArchivingPane();
}
VOID CMainWnd::UpdateArchivingStatus(LPCTSTR pszArchiveFile, UINT nArchiveFreeSpace, BOOL bArchiveStatus, LPCTSTR pszBackupDirectory, UINT nBackupFreeSpace, BOOL bBackupStatus)
{
	m_wndStatusBar.UpdateArchivingPane(pszArchiveFile, nArchiveFreeSpace, bArchiveStatus, pszBackupDirectory, nBackupFreeSpace, bBackupStatus);
}

BOOL CMainWnd::ShowProgress(INT nProgress)
{
	return m_wndStatusBar.ShowProgress(nProgress);
}

BOOL CMainWnd::ShowMessage(INT nMessageID)
{
	CString  szServer;
	CString  szMessage;

	if (nMessageID == IDS_STATUSBAR_INITIALIZING || nMessageID == IDS_STATUSBAR_INITIALIZING_PARAMETERS || nMessageID == IDS_STATUSBAR_RESETTING)
	{
		m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1);
		szMessage = STRING(nMessageID);
	}
	if (nMessageID == IDS_STATUSBAR_SAVING || nMessageID == IDS_STATUSBAR_LOADING || nMessageID == IDS_STATUSBAR_SAVING_DISPLAYS || nMessageID == IDS_STATUSBAR_LOADING_DISPLAYS)
	{
		szMessage.Format(STRING(nMessageID), (LPCTSTR)GetAccountSpacecraftName());
		m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1);
	}
	if (nMessageID == IDS_STATUSBAR_SAVING_USER || nMessageID == IDS_STATUSBAR_LOADING_USER)
	{
		szMessage.Format(STRING(nMessageID), (LPCTSTR)GetAccountUserName());
		m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1);
	}
	if (nMessageID == IDS_STATUSBAR_READY)
	{
		UpdateStatusBar();
		return TRUE;
	}
	if (nMessageID > 0)
	{
		if (m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE), (nMessageID != IDS_STATUSBAR_INITIALIZING  &&  nMessageID != IDS_STATUSBAR_RESETTING  &&  nMessageID != IDS_STATUSBAR_SAVING  &&  nMessageID != IDS_STATUSBAR_LOADING  &&  nMessageID != IDS_STATUSBAR_SAVING_DISPLAYS  &&  nMessageID != IDS_STATUSBAR_LOADING_DISPLAYS  &&  nMessageID != IDS_STATUSBAR_SAVING_USER  &&  nMessageID != IDS_STATUSBAR_LOADING_USER  &&  nMessageID != IDS_STATUSBAR_INITIALIZING_PARAMETERS) ? STRING(nMessageID) : (LPCTSTR)szMessage))
		{
			m_wndStatusBar.SetProgressIndicator((((nMessageID == IDS_STATUSBAR_SAVING || nMessageID == IDS_STATUSBAR_SAVING_DISPLAYS) && CheckDisplays()) || nMessageID == IDS_STATUSBAR_LOADING || nMessageID == IDS_STATUSBAR_LOADING_DISPLAYS || nMessageID == IDS_STATUSBAR_INITIALIZING_PARAMETERS) ? (LPCTSTR)szMessage : EMPTYSTRING);
			m_wndStatusBar.UpdateWindow();
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CMainWnd::ShowMessage(LPCTSTR pszMessage)
{
	if (!lstrcmp(pszMessage, STRING(IDS_STATUSBAR_READY)))
	{
		UpdateStatusBar();
		return TRUE;
	}
	if ((m_wndStatusBar.GetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE)).Compare(pszMessage) && m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE), pszMessage)) || !m_wndStatusBar.GetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE)).Compare(pszMessage))
	{
		m_wndStatusBar.SetProgressIndicator(EMPTYSTRING);
		m_wndStatusBar.UpdateWindow();
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWnd::ReportMessage(INT nMessageID)
{
	CString  szMessage;

	if (nMessageID == IDS_STATUSBAR_SAVING || nMessageID == IDS_STATUSBAR_LOADING || nMessageID == IDS_STATUSBAR_SAVING_DISPLAYS || nMessageID == IDS_STATUSBAR_LOADING_DISPLAYS)
	{
		szMessage.Format(STRING(nMessageID), (LPCTSTR)GetAccountSpacecraftName());
		return ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
	}
	if (nMessageID == IDS_STATUSBAR_SAVING_USER || nMessageID == IDS_STATUSBAR_LOADING_USER)
	{
		szMessage.Format(STRING(nMessageID), (LPCTSTR)GetAccountUserName());
		return ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
	}
	return((nMessageID == IDS_STATUSBAR_INITIALIZING || nMessageID == IDS_STATUSBAR_RESETTING || nMessageID == IDS_STATUSBAR_INITIALIZING_PARAMETERS) ? ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, STRING(nMessageID), FALSE) : FALSE);
}

BOOL CMainWnd::ReportEvent(UINT nFlags, LPCTSTR pszEvent, BOOL bAudition)
{
	CEventBoxWnd  *pEventBoxWnd;

	return(((pEventBoxWnd = GetReportDisplay()) && pEventBoxWnd->ShowEvent(nFlags, pszEvent, bAudition)) ? TRUE : FALSE);
}
BOOL CMainWnd::ReportEvent(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition)
{
	CEventBoxWnd  *pEventBoxWnd;

	return(((pEventBoxWnd = GetReportDisplay()) && pEventBoxWnd->ShowEvent(sEvent, bAudition)) ? TRUE : FALSE);
}
BOOL CMainWnd::ReportEvent(CEventObject *pEvent)
{
	CEventBoxWnd  *pEventBoxWnd;

	if ((pEventBoxWnd = GetReportDisplay()) && pEventBoxWnd->ShowEvent(pEvent)) return TRUE;
	delete pEvent;
	return FALSE;
}

BOOL CMainWnd::SetReportDisplay(CEventBoxWnd *pEventBoxWnd)
{
	return((IsWindow((m_pReportWnd = pEventBoxWnd)->GetSafeHwnd())) ? TRUE : FALSE);
}

CEventBoxWnd *CMainWnd::GetReportDisplay() CONST
{
	return((IsWindow(m_pReportWnd->GetSafeHwnd()) && m_pReportWnd->IsInitialized()) ? m_pReportWnd : (CEventBoxWnd *)NULL);
}

CDisplayFrame *CMainWnd::GetDisplayFrame() CONST
{
	return((IsWindow(m_pDisplayFrame->GetSafeHwnd())) ? m_pDisplayFrame : (CDisplayFrame *)NULL);
}

CDisplayArea *CMainWnd::GetDisplayArea() CONST
{
	return((IsWindow(m_pDisplayArea->GetSafeHwnd())) ? m_pDisplayArea : (CDisplayArea *)NULL);
}

CDisplayWnd *CMainWnd::GetGlobalDisplay(INT nType) CONST
{
	return m_pDisplayArea->FindDisplay(nType);
}

CDisplayWnd *CMainWnd::GetActiveDisplay() CONST
{
	return m_pDisplayArea->GetActiveDisplay();
}

CCLCWToolWnd *CMainWnd::GetCLCWToolWnd() CONST
{
	return((IsWindow(m_pCLCWToolWnd->GetSafeHwnd())) ? m_pCLCWToolWnd : (CCLCWToolWnd *)NULL);
}

BOOL CMainWnd::CreateLogo()
{
	return(((m_pLogoWnd = new CLogoWnd)) ? m_pLogoWnd->Create(this, GetLogo()) : FALSE);
}

BOOL CMainWnd::CreateRibbonBar()
{
	return((m_wndRibbonBar.Create(this) && m_wndRibbonBar.LoadFromResource(IDR_MAINFRAME)) ? TRUE : FALSE);
}

BOOL CMainWnd::CreateStatusBar()
{
	return m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1);
}

BOOL CMainWnd::StartCLCWPanel()
{
	return(((m_pCLCWToolWnd = new CCLCWToolWnd)) ? m_pCLCWToolWnd->Create(this, &m_wndRibbonBar) : FALSE);
}

BOOL CMainWnd::StopCLCWPanel()
{
	if (m_pCLCWToolWnd != (CCLCWToolWnd *)NULL)
	{
		m_pCLCWToolWnd->Destroy();
		delete m_pCLCWToolWnd;
		m_pCLCWToolWnd = (CCLCWToolWnd *)NULL;
	}
	return TRUE;
}

BOOL CMainWnd::ConstructSubMenu(CMenu *pMenu, CMFCRibbonButton *pButton, CImageList &cImages, CImageList &cSpecialImages, CUIntArray &nImageIDs)
{
	INT  nID;
	INT  nIDs;
	INT  nItem;
	INT  nItems;
	UINT  nMenuID;
	CString  szItem;
	CMFCRibbonButton  *pItem;
	CMFCRibbonSeparator  *pSeparator;

	for (nItem = 0, nItems = pMenu->GetMenuItemCount(); nItem < nItems; nItem++)
	{
		if ((nMenuID = pMenu->GetMenuItemID(nItem)) != 0 && nMenuID != (UINT)-1)
		{
			if (pMenu->GetMenuString(nMenuID, szItem, MF_BYCOMMAND) > 0)
			{
				for (nID = 0, nIDs = (INT)nImageIDs.GetSize(); nID < nIDs; nID++)
				{
					if (nMenuID == nImageIDs.GetAt(nID)) break;
					continue;
				}
				if (nID < nIDs)
				{
					if ((pItem = new CMainRibbonButton(nMenuID, szItem, cImages.ExtractIcon(nID), cImages.ExtractIcon(nID))))
					{
						pButton->AddSubItem(pItem, nItem);
						continue;
					}
					break;
				}
				if ((pItem = new CMainRibbonButton(nMenuID, szItem, cSpecialImages.ExtractIcon(0), cSpecialImages.ExtractIcon(0))))
				{
					pButton->AddSubItem(pItem, nItem);
					continue;
				}
			}
			break;
		}
		if (!nMenuID)
		{
			if ((pSeparator = new CMFCRibbonSeparator(TRUE)))
			{
				pButton->AddSubItem(pSeparator, nItem);
				continue;
			}
			break;
		}
		if (pMenu->GetMenuString(nItem, szItem, MF_BYPOSITION) > 0)
		{
			if ((pItem = new CMainRibbonButton(0, szItem, cSpecialImages.ExtractIcon(0), cSpecialImages.ExtractIcon(0))))
			{
				if (ConstructSubMenu(pMenu->GetSubMenu(nItem), pItem, cImages, cSpecialImages, nImageIDs))
				{
					pButton->AddSubItem(pItem, nItem);
					continue;
				}
				delete pItem;
			}
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

UINT CMainWnd::GetSubMenuState(CMenu *pMenu) CONST
{
	UINT  nItem;
	UINT  nItems;
	CMenu  *pSubMenu;

	for (nItem = 0, nItems = pMenu->GetMenuItemCount(); nItem < nItems; nItem++)
	{
		if ((pSubMenu = pMenu->GetSubMenu(nItem)) && !(GetSubMenuState(pSubMenu) & MF_GRAYED)) break;
		if (!pSubMenu  &&  pMenu->GetMenuItemID(nItem) && !(pMenu->GetMenuState(nItem, MF_BYPOSITION) & MF_GRAYED)) break;
	}
	return((nItem < nItems) ? MF_ENABLED : MF_GRAYED);
}

VOID CMainWnd::PrintServerAddressBook(PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	INT  nPage;
	INT  nPages;
	INT  nToPage;
	INT  nFromPage;
	BOOL  bPage[1];
	CRect  rPage[3];
	DOCINFO  sJobInfo;
	CString  szJobName;
	CTimeKey  tJobTime;
	LPDEVMODE  pDevMode;
	LPDEVNAMES  pDevNames;
	CUIntArray  nPaging;
	PAGESETUPDLG  cPageInfo;
	CVersionInfo  cVersionInfo;
	CServerProfiles  pServerAddresses;
	CServerAddressBook  cServerAddressBook;

	if (cServerAddressBook.GetServerAddressBook(pServerAddresses))
	{
		if (pServerAddresses.GetSize() > 0)
		{
			sJobInfo.cbSize = sizeof(DOCINFO);
			sJobInfo.fwType = (DWORD)NULL;
			sJobInfo.lpszOutput = (LPCTSTR)NULL;
			sJobInfo.lpszDatatype = (LPCTSTR)NULL;
			if (GetDefaultPrinterInfo(&cPageInfo))
			{
				if ((pDevNames = (LPDEVNAMES)GlobalLock(pPrintInfo->hDevNames)))
				{
					if ((pDevMode = (LPDEVMODE)GlobalLock(pPrintInfo->hDevMode)))
					{
						for (szJobName.Format(STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_JOBTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_TITLE)), sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobName, nFromPage = (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, nToPage = (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, cDC.Attach(pPrintInfo->hDC); cDC.StartDoc(&sJobInfo) >= 0; )
						{
							for (rPage[0] = rPage[1] = rPage[2] = CalcAddressBookPrintDocPageExtent(cDC, cPageInfo.rtMargin, ((cPageInfo.Flags & PSD_INTHOUSANDTHSOFINCHES) != PSD_INTHOUSANDTHSOFINCHES) ? TRUE : FALSE), nPage = 1, nPages = (DrawAddressBookPrintDocPageFrame(cDC, STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_TITLE), cServerAddressBook.GetComputerName(), cVersionInfo.QueryComments(), tJobTime, (LPCTSTR)pDevMode->dmDeviceName, 1, 1, rPage[2]), TRUE) ? CalcServerAddressBookPrintDocExtent(cDC, pServerAddresses, rPage[2], nPaging) : -1; nPage <= nPages; nPage++, rPage[1] = rPage[0])
							{
								if ((bPage[0] = ((nFromPage > 0 && nToPage > 0 && nPage >= nFromPage  &&  nPage <= nToPage) || (!nFromPage  &&  !nToPage))) && cDC.StartPage() >= 0 && DrawAddressBookPrintDocPageFrame(cDC, STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_TITLE), cServerAddressBook.GetComputerName(), cVersionInfo.QueryComments(), tJobTime, (LPCTSTR)pDevMode->dmDeviceName, nPages, nPage, rPage[1]) && DrawServerAddressBookPrintDocContents(cDC, pServerAddresses, CRect(rPage[1].left, rPage[1].top, rPage[1].right, (nPage > 1) ? (rPage[1].top + nPaging.GetAt(nPage - 1) - nPaging.GetAt((nPage - 1) - 1)) : (rPage[1].top + nPaging.GetAt(nPage - 1))), nPaging.GetAt(nPages - 1), (nPage > 1) ? nPaging.GetAt((nPage - 1) - 1) : 0) && cDC.EndPage() >= 0)
								{
									cDC.SelectClipRgn((CRgn *)NULL);
									continue;
								}
								if (bPage[0]) break;
							}
							if (nPage > nPages)
							{
								GlobalUnlock(pPrintInfo->hDevNames);
								GlobalUnlock(pPrintInfo->hDevMode);
								GlobalFree(cPageInfo.hDevNames);
								GlobalFree(cPageInfo.hDevMode);
								cDC.EndDoc();
								return;
							}
							cDC.AbortDoc();
							break;
						}
						GlobalFree(cPageInfo.hDevNames);
						GlobalFree(cPageInfo.hDevMode);
						GlobalUnlock(pPrintInfo->hDevNames);
						GlobalUnlock(pPrintInfo->hDevMode);
						ReportEvent(SYSTEM_WARNING_SERVERADDRESSBOOK_PRINT_FAILURE);
						return;
					}
					GlobalUnlock(pPrintInfo->hDevNames);
				}
				GlobalFree(cPageInfo.hDevNames);
				GlobalFree(cPageInfo.hDevMode);
			}
		}
		else
		{
			DeleteDC(pPrintInfo->hDC);
			return;
		}
	}
	for (ReportEvent(SYSTEM_WARNING_SERVERADDRESSBOOK_PRINT_FAILURE); pPrintInfo->hDC != (HDC)NULL; )
	{
		DeleteDC(pPrintInfo->hDC);
		break;
	}
}

VOID CMainWnd::PrintUserAddressBook(PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	INT  nPage;
	INT  nPages;
	INT  nToPage;
	INT  nFromPage;
	BOOL  bPage[1];
	CRect  rPage[3];
	DOCINFO  sJobInfo;
	CString  szJobName;
	CTimeKey  tJobTime;
	LPDEVMODE  pDevMode;
	LPDEVNAMES  pDevNames;
	CUIntArray  nPaging;
	PAGESETUPDLG  cPageInfo;
	CVersionInfo  cVersionInfo;
	CUserProfiles  pUserAddresses;
	CUserAddressBook  cUserAddressBook;

	if (cUserAddressBook.GetUserAddressBook(pUserAddresses))
	{
		if (pUserAddresses.GetSize() > 0)
		{
			sJobInfo.cbSize = sizeof(DOCINFO);
			sJobInfo.fwType = (DWORD)NULL;
			sJobInfo.lpszOutput = (LPCTSTR)NULL;
			sJobInfo.lpszDatatype = (LPCTSTR)NULL;
			if (GetDefaultPrinterInfo(&cPageInfo))
			{
				if ((pDevNames = (LPDEVNAMES)GlobalLock(pPrintInfo->hDevNames)))
				{
					if ((pDevMode = (LPDEVMODE)GlobalLock(pPrintInfo->hDevMode)))
					{
						for (szJobName.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_JOBTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), STRING(IDS_USERADDRESSBOOK_PRINTDOC_TITLE)), sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobName, nFromPage = (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, nToPage = (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, cDC.Attach(pPrintInfo->hDC); cDC.StartDoc(&sJobInfo) >= 0; )
						{
							for (rPage[0] = rPage[1] = rPage[2] = CalcAddressBookPrintDocPageExtent(cDC, cPageInfo.rtMargin, ((cPageInfo.Flags & PSD_INTHOUSANDTHSOFINCHES) != PSD_INTHOUSANDTHSOFINCHES) ? TRUE : FALSE), nPage = 1, nPages = (DrawAddressBookPrintDocPageFrame(cDC, STRING(IDS_USERADDRESSBOOK_PRINTDOC_TITLE), cUserAddressBook.GetComputerName(), cVersionInfo.QueryComments(), tJobTime, (LPCTSTR)pDevMode->dmDeviceName, 1, 1, rPage[2]), TRUE) ? CalcUserAddressBookPrintDocExtent(cDC, pUserAddresses, rPage[2], nPaging) : -1; nPage <= nPages; nPage++, rPage[1] = rPage[0])
							{
								if ((bPage[0] = ((nFromPage > 0 && nToPage > 0 && nPage >= nFromPage  &&  nPage <= nToPage) || (!nFromPage  &&  !nToPage))) && cDC.StartPage() >= 0 && DrawAddressBookPrintDocPageFrame(cDC, STRING(IDS_USERADDRESSBOOK_PRINTDOC_TITLE), cUserAddressBook.GetComputerName(), cVersionInfo.QueryComments(), tJobTime, (LPCTSTR)pDevMode->dmDeviceName, nPages, nPage, rPage[1]) && DrawUserAddressBookPrintDocContents(cDC, pUserAddresses, CRect(rPage[1].left, rPage[1].top, rPage[1].right, (nPage > 1) ? (rPage[1].top + nPaging.GetAt(nPage - 1) - nPaging.GetAt((nPage - 1) - 1)) : (rPage[1].top + nPaging.GetAt(nPage - 1))), nPaging.GetAt(nPages - 1), (nPage > 1) ? nPaging.GetAt((nPage - 1) - 1) : 0) && cDC.EndPage() >= 0)
								{
									cDC.SelectClipRgn((CRgn *)NULL);
									continue;
								}
								if (bPage[0]) break;
							}
							if (nPage > nPages)
							{
								GlobalUnlock(pPrintInfo->hDevNames);
								GlobalUnlock(pPrintInfo->hDevMode);
								GlobalFree(cPageInfo.hDevNames);
								GlobalFree(cPageInfo.hDevMode);
								cDC.EndDoc();
								return;
							}
							cDC.AbortDoc();
							break;
						}
						GlobalFree(cPageInfo.hDevNames);
						GlobalFree(cPageInfo.hDevMode);
						GlobalUnlock(pPrintInfo->hDevNames);
						GlobalUnlock(pPrintInfo->hDevMode);
						ReportEvent(SYSTEM_WARNING_USERADDRESSBOOK_PRINT_FAILURE);
						return;
					}
					GlobalUnlock(pPrintInfo->hDevNames);
				}
				GlobalFree(cPageInfo.hDevNames);
				GlobalFree(cPageInfo.hDevMode);
			}
		}
		else
		{
			DeleteDC(pPrintInfo->hDC);
			return;
		}
	}
	for (ReportEvent(SYSTEM_WARNING_USERADDRESSBOOK_PRINT_FAILURE); pPrintInfo->hDC != (HDC)NULL; )
	{
		DeleteDC(pPrintInfo->hDC);
		break;
	}
}

BOOL CMainWnd::DrawServerAddressBookPrintDocContents(CDC &cDC, CONST CServerProfiles &pServers, CONST CRect &rPage, INT nTotalHeight, INT nPageOffset) CONST
{
	INT  x;
	INT  y;
	INT  nIndex;
	INT  nCount;
	INT  nHeight;
	INT  nMargin;
	INT  nNumber;
	INT  nNumbers;
	INT  nAddress;
	INT  nAddresses;
	INT  nOldBkMode;
	CPen  cPen[2];
	CPen  *pOldPen;
	CFont  cFont[3];
	CFont  *pOldFont[2];
	CRect  rAddressBook;
	CString  szDevice[3];
	COLORREF  nOldColor;
	COLORREF  nOldBkColor;
	CUIntArray  nWidths;
	TEXTMETRIC  tmFont[3];
	CStringArray  szNumbers;
	CServerProfileInfo  *pServerInfo;

	if (CalcServerAddressBookPrintDocContentFonts(cDC, pServers, rPage.right - rPage.left, cFont[0], cFont[1], cFont[2]))
	{
		if (CalcServerAddressBookPrintDocColumnWidths(cDC, pServers, &cFont[0], &cFont[1], &cFont[2], nWidths, nMargin))
		{
			for (nIndex = 0, nCount = (nWidths.GetAt(nWidths.GetUpperBound()) < (UINT)(rPage.right - rPage.left)) ? (INT)nWidths.GetSize() : 0, rAddressBook.SetRect(rPage.left, rPage.top - nPageOffset, rPage.right, rPage.top - nPageOffset + nTotalHeight), nHeight = CalcAddressBookPrintDocTitleHeight(cDC, &cFont[0]); nIndex < nCount; nIndex++)
			{
				nWidths.SetAt(nIndex, nWidths.GetAt(nIndex) + (rPage.right - rPage.left - nWidths.GetAt(nWidths.GetUpperBound())));
				continue;
			}
			if (cDC.IntersectClipRect(rPage) != ERROR)
			{
				if ((pOldFont[0] = cDC.SelectObject(&cFont[0])))
				{
					if (cPen[0].CreatePen(PS_SOLID, nMargin, VGA_COLOR_BLACK))
					{
						if (cPen[1].CreatePen(PS_SOLID, nMargin / 3, VGA_COLOR_BLACK))
						{
							if ((pOldPen = (cDC.GetTextMetrics(&tmFont[0])) ? cDC.SelectObject(&cPen[0]) : (CPen *)NULL))
							{
								nOldBkColor = cDC.GetBkColor();
								cDC.FillSolidRect(rAddressBook.left, rAddressBook.top, rAddressBook.Width(), nHeight, VGA_COLOR_LTGRAY);
								cDC.MoveTo(rAddressBook.left + nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.top + nHeight);
								cDC.LineTo(rAddressBook.left + nMargin / 2, rAddressBook.top + nHeight);
								cDC.LineTo(rAddressBook.left + nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.LineTo(rAddressBook.left + nMargin / 2, rAddressBook.bottom - nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.bottom - nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.SetBkColor(nOldBkColor);
								cDC.SelectObject(pOldPen);
							}
							if ((pOldPen = cDC.SelectObject(&cPen[1])))
							{
								cDC.MoveTo(rAddressBook.left + nWidths.GetAt(0), rAddressBook.top);
								cDC.LineTo(rAddressBook.left + nWidths.GetAt(0), rAddressBook.bottom);
								cDC.MoveTo(rAddressBook.left + nWidths.GetAt(1), rAddressBook.top);
								cDC.LineTo(rAddressBook.left + nWidths.GetAt(1), rAddressBook.bottom);
								cDC.SelectObject(pOldPen);
							}
							nOldBkMode = cDC.SetBkMode(TRANSPARENT);
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							cDC.TextOut(rAddressBook.left + 2 * nMargin, rAddressBook.top + (nHeight - tmFont[0].tmHeight) / 2, STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_COLUMNSERVER));
							cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, rAddressBook.top + (nHeight - tmFont[0].tmHeight) / 2, STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_COLUMNPHONENUMBERS));
							cDC.TextOut(rAddressBook.left + nWidths.GetAt(1) + nMargin, rAddressBook.top + (nHeight - tmFont[0].tmHeight) / 2, STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_COLUMNCALLBACK));
							cDC.SetTextColor(nOldColor);
							cDC.SetBkMode(nOldBkMode);
							cPen[1].DeleteObject();
						}
						cPen[0].DeleteObject();
					}
					cDC.SelectObject(pOldFont[0]);
				}
				if ((pOldFont[0] = cDC.SelectObject(&cFont[1])))
				{
					if (cPen[0].CreatePen(PS_SOLID, nMargin / 3, VGA_COLOR_BLACK))
					{
						if ((pOldPen = (cDC.GetTextMetrics(&tmFont[1])) ? cDC.SelectObject(&cPen[0]) : (CPen *)NULL))
						{
							for (nAddress = 0, nAddresses = (INT)pServers.GetSize(), x = rAddressBook.left + 2 * nMargin, y = rAddressBook.top + nHeight + tmFont[1].tmHeight / 2, nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK), tmFont[2].tmHeight = 0; nAddress < nAddresses; nAddress++, y += max(tmFont[1].tmHeight + tmFont[2].tmHeight, nNumbers*tmFont[1].tmHeight) + tmFont[1].tmHeight, tmFont[2].tmHeight = 0)
							{
								if ((pServerInfo = pServers.GetAt(nAddress)))
								{
									cDC.TextOut(x, y, pServerInfo->GetName());
									if ((pOldFont[1] = cDC.SelectObject(&cFont[2])))
									{
										pServerInfo->GetDeviceInfo(szDevice[0], szDevice[1]);
										szDevice[2].Format(STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_DEVICEDETAILS), (LPCTSTR)szDevice[0], (LPCTSTR)szDevice[1]);
										cDC.TextOut(x, y + tmFont[1].tmHeight, (cDC.GetTextMetrics(&tmFont[2])) ? (LPCTSTR)szDevice[2] : EMPTYSTRING);
										cDC.SelectObject(pOldFont[1]);
									}
									for (nNumber = 0, nNumbers = pServerInfo->GetPhoneNumbers(szNumbers); nNumber < nNumbers; nNumber++)
									{
										cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y + nNumber*tmFont[1].tmHeight, szNumbers.GetAt(nNumber));
										continue;
									}
									cDC.TextOut(rAddressBook.left + nWidths.GetAt(1) + nMargin, y, pServerInfo->GetCallbackNumber());
									cDC.MoveTo(rAddressBook.left, max(y + tmFont[1].tmHeight + tmFont[2].tmHeight, y + nNumber*tmFont[1].tmHeight) + tmFont[1].tmHeight / 2);
									cDC.LineTo(rAddressBook.right, max(y + tmFont[1].tmHeight + tmFont[2].tmHeight, y + nNumber*tmFont[1].tmHeight) + tmFont[1].tmHeight / 2);
								}
							}
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldPen);
						}
						cPen[0].DeleteObject();
					}
					cDC.SelectObject(pOldFont[0]);
				}
				cFont[0].DeleteObject();
				cFont[1].DeleteObject();
				cFont[2].DeleteObject();
				return TRUE;
			}
		}
		cFont[0].DeleteObject();
		cFont[1].DeleteObject();
		cFont[2].DeleteObject();
	}
	return FALSE;
}

BOOL CMainWnd::DrawUserAddressBookPrintDocContents(CDC &cDC, CONST CUserProfiles &pUsers, CONST CRect &rPage, INT nTotalHeight, INT nPageOffset) CONST
{
	INT  x;
	INT  y;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nPos[2];
	INT  nHeight;
	INT  nMargin;
	INT  nAddress;
	INT  nAddresses;
	INT  nOldBkMode;
	CPen  cPen[2];
	CPen  *pOldPen;
	CFont  cFont[3];
	CFont  *pOldFont[2];
	CRect  rAddressBook;
	CRect  rAddressBookCell;
	CString  szName;
	CString  szTitle;
	COLORREF  nOldColor;
	COLORREF  nOldBkColor;
	CUIntArray  nWidths;
	TEXTMETRIC  tmFont[3];
	CStringArray  szDetails;
	CStringArray  szAddress;
	CStringArray  szNumbers;
	CUserProfileInfo  *pUserInfo;

	if (CalcUserAddressBookPrintDocContentFonts(cDC, pUsers, rPage.right - rPage.left, cFont[0], cFont[1], cFont[2]))
	{
		if (CalcUserAddressBookPrintDocColumnWidths(cDC, pUsers, &cFont[0], &cFont[1], &cFont[2], nWidths, nMargin))
		{
			for (nIndex = 0, nCount = (nWidths.GetAt(nWidths.GetUpperBound()) < (UINT)(rPage.right - rPage.left)) ? (INT)nWidths.GetSize() : 0, rAddressBook.SetRect(rPage.left, rPage.top - nPageOffset, rPage.right, rPage.top - nPageOffset + nTotalHeight), nHeight = CalcAddressBookPrintDocTitleHeight(cDC, &cFont[0]); nIndex < nCount; nIndex++)
			{
				nWidths.SetAt(nIndex, nWidths.GetAt(nIndex) + (rPage.right - rPage.left - nWidths.GetAt(nWidths.GetUpperBound())));
				continue;
			}
			if (cDC.IntersectClipRect(rPage) != ERROR)
			{
				if ((pOldFont[0] = cDC.SelectObject(&cFont[0])))
				{
					if (cPen[0].CreatePen(PS_SOLID, nMargin, VGA_COLOR_BLACK))
					{
						if (cPen[1].CreatePen(PS_SOLID, nMargin / 3, VGA_COLOR_BLACK))
						{
							if ((pOldPen = (cDC.GetTextMetrics(&tmFont[0])) ? cDC.SelectObject(&cPen[0]) : (CPen *)NULL))
							{
								nOldBkColor = cDC.GetBkColor();
								cDC.FillSolidRect(rAddressBook.left, rAddressBook.top, rAddressBook.Width(), nHeight, VGA_COLOR_LTGRAY);
								cDC.MoveTo(rAddressBook.left + nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.top + nHeight);
								cDC.LineTo(rAddressBook.left + nMargin / 2, rAddressBook.top + nHeight);
								cDC.LineTo(rAddressBook.left + nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.LineTo(rAddressBook.left + nMargin / 2, rAddressBook.bottom - nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.bottom - nMargin / 2);
								cDC.LineTo(rAddressBook.right - nMargin / 2, rAddressBook.top + nMargin / 2);
								cDC.SetBkColor(nOldBkColor);
								cDC.SelectObject(pOldPen);
							}
							if ((pOldPen = cDC.SelectObject(&cPen[1])))
							{
								cDC.MoveTo(rAddressBook.left + nWidths.GetAt(0), rAddressBook.top);
								cDC.LineTo(rAddressBook.left + nWidths.GetAt(0), rAddressBook.bottom);
								cDC.MoveTo(rAddressBook.left + nWidths.GetAt(1), rAddressBook.top + nHeight);
								cDC.LineTo(rAddressBook.left + nWidths.GetAt(1), rAddressBook.bottom);
								cDC.SelectObject(pOldPen);
							}
							nOldBkMode = cDC.SetBkMode(TRANSPARENT);
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							cDC.TextOut(rAddressBook.left + 2 * nMargin, rAddressBook.top + (nHeight - tmFont[0].tmHeight) / 2, STRING(IDS_USERADDRESSBOOK_PRINTDOC_COLUMNUSER));
							cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, rAddressBook.top + (nHeight - tmFont[0].tmHeight) / 2, STRING(IDS_USERADDRESSBOOK_PRINTDOC_COLUMNDETAILS));
							cDC.SetTextColor(nOldColor);
							cDC.SetBkMode(nOldBkMode);
							cPen[1].DeleteObject();
						}
						cPen[0].DeleteObject();
					}
					cDC.SelectObject(pOldFont[0]);
				}
				if ((pOldFont[0] = cDC.SelectObject(&cFont[1])))
				{
					cDC.GetTextMetrics(&tmFont[1]);
					cDC.SelectObject(pOldFont[0]);
				}
				if ((pOldFont[0] = cDC.SelectObject(&cFont[2])))
				{
					cDC.GetTextMetrics(&tmFont[2]);
					cDC.SelectObject(pOldFont[0]);
				}
				for (; tmFont[1].tmHeight != tmFont[2].tmHeight; )
				{
					tmFont[1].tmHeight = tmFont[2].tmHeight = max(tmFont[1].tmHeight, tmFont[2].tmHeight);
					break;
				}
				if ((pOldFont[0] = cDC.SelectObject(&cFont[1])))
				{
					if (cPen[0].CreatePen(PS_SOLID, nMargin / 3, VGA_COLOR_BLACK))
					{
						if ((pOldPen = cDC.SelectObject(&cPen[0])) != (CPen *)NULL)
						{
							for (nAddress = 0, nAddresses = (INT)pUsers.GetSize(), x = rAddressBook.left + 2 * nMargin, y = rAddressBook.top + nHeight + tmFont[1].tmHeight / 2, nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK); nAddress < nAddresses; nAddress++, y += tmFont[1].tmHeight / 2)
							{
								if ((pUserInfo = pUsers.GetAt(nAddress)))
								{
									cDC.TextOut(x, y, pUserInfo->GetFullName());
									cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y, STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHOFFICE));
									if ((pOldFont[1] = (CFont *)cDC.SelectObject(&cFont[2])) != (CFont *)NULL)
									{
										for (nItem = 0, nItems = CalcUserAddressBookNameInfo(pUserInfo, szName, szDetails), rAddressBookCell.SetRect(x, y + tmFont[1].tmHeight, rAddressBook.left + nWidths.GetAt(0) - nMargin, y + tmFont[1].tmHeight); nItem < nItems; nItem++)
										{
											for (nPos[0] = 0, nPos[1] = -1; nPos[0] < lstrlen(szDetails.GetAt(nItem)); nPos[0]++)
											{
												if (_istspace(szDetails.GetAt(nItem).GetAt(nPos[0])))
												{
													nPos[1] = nPos[0];
													continue;
												}
												if (cDC.GetTextExtent(szDetails.GetAt(nItem).Left(nPos[0])).cx > rAddressBookCell.Width() && nPos[1] >= 0)
												{
													cDC.TextOut(rAddressBookCell.left, rAddressBookCell.top, szDetails.GetAt(nItem).Left(nPos[1]));
													szDetails.SetAt(nItem, szDetails.GetAt(nItem).Mid(nPos[1] + 1));
													nPos[0] = 0;
													nItem--;
													break;
												}
											}
											for (; nPos[0] == lstrlen(szDetails.GetAt(nItem)) && nPos[0] > 0; )
											{
												cDC.DrawText(szDetails.GetAt(nItem), CRect(rAddressBookCell.left, rAddressBookCell.top, rAddressBookCell.right, rAddressBookCell.top + tmFont[2].tmHeight), DT_LEFT | DT_TOP | DT_NOPREFIX | DT_SINGLELINE);
												break;
											}
											rAddressBookCell.OffsetRect(0, tmFont[2].tmHeight);
										}
										for (nItem = 0, nItems = (CalcUserAddressBookOfficeInfo(pUserInfo, szTitle, szAddress, szNumbers) > 0) ? (INT)szAddress.GetSize() : 0; nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szAddress.GetAt(nItem));
											continue;
										}
										for (nItem = 0, nItems = (INT)szNumbers.GetSize(); nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(1) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szNumbers.GetAt(nItem));
											continue;
										}
										cDC.MoveTo(rAddressBook.left + nWidths.GetAt(0), (y = y + tmFont[1].tmHeight + (LONG)max(szAddress.GetSize(), szNumbers.GetSize())*tmFont[2].tmHeight + tmFont[1].tmHeight / 2));
										cDC.LineTo(rAddressBook.right, y);
										cDC.SelectObject(pOldFont[1]);
									}
									y += tmFont[1].tmHeight / 2;
									cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y, STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHHOME));
									if ((pOldFont[1] = (CFont *)cDC.SelectObject(&cFont[2])) != (CFont *)NULL)
									{
										for (nItem = 0, nItems = (CalcUserAddressBookHomeInfo(pUserInfo, szTitle, szAddress, szNumbers) > 0) ? (INT)szAddress.GetSize() : 0; nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szAddress.GetAt(nItem));
											continue;
										}
										for (nItem = 0, nItems = (INT)szNumbers.GetSize(); nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(1) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szNumbers.GetAt(nItem));
											continue;
										}
										cDC.MoveTo(rAddressBook.left + nWidths.GetAt(0), (y = y + tmFont[1].tmHeight + (LONG)max(szAddress.GetSize(), szNumbers.GetSize())*tmFont[2].tmHeight + tmFont[1].tmHeight / 2));
										cDC.LineTo(rAddressBook.right, y);
										cDC.SelectObject(pOldFont[1]);
									}
									y += tmFont[1].tmHeight / 2;
									cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y, STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHMISSION));
									if ((pOldFont[1] = (CFont *)cDC.SelectObject(&cFont[2])) != (CFont *)NULL)
									{
										for (nItem = 0, nItems = (CalcUserAddressBookMissionInfo(pUserInfo, szTitle, szAddress, szNumbers) > 0) ? (INT)szAddress.GetSize() : 0; nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szAddress.GetAt(nItem));
											continue;
										}
										for (nItem = 0, nItems = (INT)szNumbers.GetSize(); nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(1) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szNumbers.GetAt(nItem));
											continue;
										}
										cDC.MoveTo(rAddressBook.left + nWidths.GetAt(0), (y = y + tmFont[1].tmHeight + (LONG)max(szAddress.GetSize(), szNumbers.GetSize())*tmFont[2].tmHeight + tmFont[1].tmHeight / 2));
										cDC.LineTo(rAddressBook.right, y);
										cDC.SelectObject(pOldFont[1]);
									}
									y += tmFont[1].tmHeight / 2;
									cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y, STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHHOLIDAY));
									if ((pOldFont[1] = (CFont *)cDC.SelectObject(&cFont[2])) != (CFont *)NULL)
									{
										for (nItem = 0, nItems = (CalcUserAddressBookHolidayInfo(pUserInfo, szTitle, szAddress, szNumbers) > 0) ? (INT)szAddress.GetSize() : 0; nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(0) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szAddress.GetAt(nItem));
											continue;
										}
										for (nItem = 0, nItems = (INT)szNumbers.GetSize(); nItem < nItems; nItem++)
										{
											cDC.TextOut(rAddressBook.left + nWidths.GetAt(1) + nMargin, y + tmFont[1].tmHeight + nItem*tmFont[2].tmHeight, szNumbers.GetAt(nItem));
											continue;
										}
										cDC.MoveTo(rAddressBook.left, (y = max(y + tmFont[1].tmHeight + (LONG)max(szAddress.GetSize(), szNumbers.GetSize())*tmFont[2].tmHeight, rAddressBookCell.bottom) + tmFont[1].tmHeight / 2));
										cDC.LineTo(rAddressBook.right, y);
										cDC.SelectObject(pOldFont[1]);
										continue;
									}
								}
								break;
							}
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldPen);
						}
						cPen[0].DeleteObject();
					}
					cDC.SelectObject(pOldFont[0]);
				}
				cFont[0].DeleteObject();
				cFont[1].DeleteObject();
				cFont[2].DeleteObject();
				return TRUE;
			}
		}
		cFont[0].DeleteObject();
		cFont[1].DeleteObject();
		cFont[2].DeleteObject();
	}
	return FALSE;
}

BOOL CMainWnd::DrawAddressBookPrintDocPageFrame(CDC &cDC, LPCTSTR pszTitle, LPCTSTR pszSubTitle, LPCTSTR pszNotice, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage, CRect &rPage, BOOL bCalc) CONST
{
	return((cDC.IntersectClipRect(rPage) != ERROR) ? (DrawAddressBookPrintDocPageTitle(cDC, pszTitle, rPage, bCalc) && DrawAddressBookPrintDocPageSubTitle(cDC, pszSubTitle, rPage, bCalc) && DrawAddressBookPrintDocPageNotice(cDC, pszNotice, rPage, bCalc) && DrawAddressBookPrintDocPageFooter(cDC, tTime, pszPrinterName, nPages, nPage, rPage, bCalc)) : FALSE);
}

BOOL CMainWnd::DrawAddressBookPrintDocPageTitle(CDC &cDC, LPCTSTR pszTitle, CRect &rPage, BOOL bCalc) CONST
{
	CRect  rText;
	CFont  cFont;
	CFont  *pOldFont;

	if (CalcAddressBookPrintDocTitleFont(cDC, rPage.Width(), cFont))
	{
		if ((pOldFont = cDC.SelectObject(&cFont)) != (CFont *)NULL)
		{
			cDC.DrawText(pszTitle, (rText = CRect(0, 0, rPage.Width(), 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
			cDC.DrawText(pszTitle, (!bCalc) ? rPage : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
			rPage.DeflateRect(0, rText.Height(), 0, 0);
			cDC.SelectObject(pOldFont);
			cFont.DeleteObject();
			return TRUE;
		}
		cFont.DeleteObject();
	}
	return FALSE;
}

BOOL CMainWnd::DrawAddressBookPrintDocPageSubTitle(CDC &cDC, LPCTSTR pszSubTitle, CRect &rPage, BOOL bCalc) CONST
{
	CRect  rText;
	CFont  cFont;
	CFont  *pOldFont;

	if (CalcAddressBookPrintDocSubTitleFont(cDC, rPage.Width(), cFont))
	{
		if ((pOldFont = cDC.SelectObject(&cFont)) != (CFont *)NULL)
		{
			cDC.DrawText(pszSubTitle, (rText = CRect(0, 0, rPage.Width(), 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
			cDC.DrawText(pszSubTitle, (!bCalc) ? rPage : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
			rPage.DeflateRect(0, 3 * rText.Height(), 0, 0);
			cDC.SelectObject(pOldFont);
			cFont.DeleteObject();
			return TRUE;
		}
		cFont.DeleteObject();
	}
	return FALSE;
}

BOOL CMainWnd::DrawAddressBookPrintDocPageNotice(CDC &cDC, LPCTSTR pszNotice, CRect &rPage, BOOL bCalc) CONST
{
	INT  nPos;
	CFont  cFont[2];
	CFont  *pOldFont[2];
	CSize  sizeNotice[3];
	CString  szNotice[3];
	CString  szCompanyNotice;
	CVersionInfo  cVersionInfo;

	for (szCompanyNotice = pszNotice; (pOldFont[0] = (CalcAddressBookPrintDocNoticeFonts(cDC, rPage.Width(), cFont[0], cFont[1])) ? cDC.SelectObject(&cFont[0]) : (CFont *)NULL); )
	{
		for (szNotice[0] = ((nPos = szCompanyNotice.Find((szNotice[2] = cVersionInfo.QueryCompanyName()))) >= 0) ? szCompanyNotice.Left(nPos) : szCompanyNotice, szNotice[1] = (nPos >= 0) ? szCompanyNotice.Mid(nPos + szNotice[2].GetLength()) : EMPTYSTRING, sizeNotice[0] = cDC.GetTextExtent(szNotice[0]), sizeNotice[1] = cDC.GetTextExtent(szNotice[1]); (pOldFont[1] = cDC.SelectObject(&cFont[1])); )
		{
			sizeNotice[2] = cDC.GetTextExtent(szNotice[2]);
			cDC.SelectObject(pOldFont[1]);
			break;
		}
		for (cDC.TextOut(rPage.left, rPage.bottom - sizeNotice[0].cy, (!bCalc) ? (LPCTSTR)szNotice[0] : EMPTYSTRING), cDC.TextOut(rPage.left + sizeNotice[0].cx + sizeNotice[2].cx, rPage.bottom - sizeNotice[1].cy, (!bCalc) ? (LPCTSTR)szNotice[1] : EMPTYSTRING); (pOldFont[1] = cDC.SelectObject(&cFont[1])); )
		{
			cDC.TextOut(rPage.left + sizeNotice[0].cx, rPage.bottom - sizeNotice[2].cy, (!bCalc) ? (LPCTSTR)szNotice[2] : EMPTYSTRING);
			cDC.SelectObject(pOldFont[1]);
			break;
		}
		rPage.DeflateRect(0, 0, 0, max(sizeNotice[0].cy, sizeNotice[2].cy));
		cDC.SelectObject(pOldFont[0]);
		cFont[0].DeleteObject();
		cFont[1].DeleteObject();
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWnd::DrawAddressBookPrintDocPageFooter(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage, CRect &rPage, BOOL bCalc) CONST
{
	CRect  rText;
	CFont  cFont;
	CFont  *pOldFont;
	CString  szFooter;

	if (CalcAddressBookPrintDocFooterFont(cDC, rPage.Width(), cFont))
	{
		if ((pOldFont = cDC.SelectObject(&cFont)) != (CFont *)NULL)
		{
			szFooter.Format(STRING(IDS_ADDRESSBOOKS_PRINTDOC_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
			cDC.DrawText(szFooter, (rText = CRect(0, 0, rPage.Width(), 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
			cDC.DrawText(szFooter, (!bCalc) ? CRect(rPage.left, rPage.bottom - rText.Height(), rPage.right, rPage.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
			rPage.DeflateRect(0, 0, 0, 3 * rText.Height());
			cDC.SelectObject(pOldFont);
			cFont.DeleteObject();
			return TRUE;
		}
		cFont.DeleteObject();
	}
	return FALSE;
}

BOOL CMainWnd::CalcAddressBookPrintDocTitleFont(CDC &cDC, INT nWidth, CFont &cFont) CONST
{
	return cFont.CreateFont(-(INT)(((((double)nWidth*(double)cDC.GetDeviceCaps(HORZSIZE)) / (40.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMainWnd::CalcAddressBookPrintDocSubTitleFont(CDC &cDC, INT nWidth, CFont &cFont) CONST
{
	return cFont.CreateFont(-(INT)(((((double)nWidth*(double)cDC.GetDeviceCaps(HORZSIZE)) / (50.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMainWnd::CalcAddressBookPrintDocFooterFont(CDC &cDC, INT nWidth, CFont &cFont) CONST
{
	return cFont.CreateFont(-(INT)(((((double)nWidth*(double)cDC.GetDeviceCaps(HORZSIZE)) / (80.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMainWnd::CalcAddressBookPrintDocNoticeFonts(CDC &cDC, INT nWidth, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(-(INT)(((((double)nWidth*(double)cDC.GetDeviceCaps(HORZSIZE)) / (96.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(-(INT)(((((double)nWidth*(double)cDC.GetDeviceCaps(HORZSIZE)) / (96.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

CRect CMainWnd::CalcAddressBookPrintDocPageExtent(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rPage;

	rPage.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rPage.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return rPage;
}

INT CMainWnd::CalcAddressBookPrintDocTitleHeight(CDC &cDC, CFont *pTitleFont) CONST
{
	INT  nHeight;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pOldFont = cDC.SelectObject(pTitleFont)))
	{
		if (cDC.GetTextMetrics(&tmFont))
		{
			nHeight = 2 * tmFont.tmHeight;
			cDC.SelectObject(pOldFont);
			return nHeight;
		}
		cDC.SelectObject(pOldFont);
	}
	return 0;
}

INT CMainWnd::CalcServerAddressBookPrintDocExtent(CDC &cDC, CONST CServerProfiles &pServers, CONST RECT &rPage, CUIntArray &nPaging) CONST
{
	INT  nSpace;
	INT  nNumber;
	INT  nNumbers;
	INT  nAddress;
	INT  nAddresses;
	INT  nHeight[3];
	CFont  cFont[3];
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;
	CStringArray  szNumbers;
	CServerProfileInfo  *pServerInfo;

	for (nHeight[0] = nHeight[1] = nHeight[2] = 0, nSpace = 0, nPaging.RemoveAll(); CalcServerAddressBookPrintDocContentFonts(cDC, pServers, rPage.right - rPage.left, cFont[0], cFont[1], cFont[2]); )
	{
		for (nHeight[0] = CalcAddressBookPrintDocTitleHeight(cDC, &cFont[0]); (pOldFont = cDC.SelectObject(&cFont[1])); )
		{
			nHeight[1] = (cDC.GetTextMetrics(&tmFont)) ? tmFont.tmHeight : 0;
			cDC.SelectObject(pOldFont);
			break;
		}
		if ((pOldFont = cDC.SelectObject(&cFont[2])))
		{
			nHeight[2] = (cDC.GetTextMetrics(&tmFont)) ? tmFont.tmHeight : 0;
			cDC.SelectObject(pOldFont);
		}
		for (nAddress = 0, nAddresses = (INT)pServers.GetSize(); nAddress < nAddresses; nAddress++)
		{
			if ((pServerInfo = (CServerProfileInfo *)pServers.GetAt(nAddress)) != (CServerProfileInfo *)NULL)
			{
				if ((nHeight[0] + nSpace) % (rPage.bottom - rPage.top) + 2 * nHeight[1] + nHeight[2] > rPage.bottom - rPage.top)
				{
					if ((!nPaging.GetSize() || nPaging.GetAt(nPaging.GetUpperBound()) < (UINT)nHeight[0]) && 2 * nHeight[1] + nHeight[2] < rPage.bottom - rPage.top)
					{
						nSpace += rPage.bottom - rPage.top - (nHeight[0] + nSpace) % (rPage.bottom - rPage.top);
						nPaging.Add(nHeight[0]);
						nAddress--;
						continue;
					}
					break;
				}
				for (nNumber = 0, nNumbers = pServerInfo->GetPhoneNumbers(szNumbers), nHeight[0] += (!nNumbers) ? (nHeight[1] + nHeight[2]) : 0, nHeight[0] += (nNumbers == 1) ? (nHeight[1] / 2 + nHeight[2]) : 0, nHeight[0] += (nNumbers > 1) ? (nHeight[1] / 2) : 0; nNumber < nNumbers; nNumber++)
				{
					if ((nHeight[0] + nSpace) % (rPage.bottom - rPage.top) + nHeight[1] > rPage.bottom - rPage.top)
					{
						nSpace += rPage.bottom - rPage.top - (nHeight[0] + nSpace) % (rPage.bottom - rPage.top);
						nPaging.Add(nHeight[0]);
						nNumber--;
						continue;
					}
					nHeight[0] += nHeight[1];
				}
				if (nNumbers > 0)
				{
					if ((nHeight[0] + nSpace) % (rPage.bottom - rPage.top) + nHeight[1] / 2 > rPage.bottom - rPage.top)
					{
						nSpace += rPage.bottom - rPage.top - (nHeight[0] + nSpace) % (rPage.bottom - rPage.top);
						nPaging.Add(nHeight[0]);
					}
					nHeight[0] += nHeight[1] / 2;
				}
				continue;
			}
			break;
		}
		if (nAddress == nAddresses)
		{
			nPaging.Add(nHeight[0]);
			cFont[0].DeleteObject();
			cFont[1].DeleteObject();
			cFont[2].DeleteObject();
			return((INT)nPaging.GetSize());
		}
		cFont[0].DeleteObject();
		cFont[1].DeleteObject();
		cFont[2].DeleteObject();
		nPaging.RemoveAll();
		break;
	}
	return 0;
}

INT CMainWnd::CalcUserAddressBookPrintDocExtent(CDC &cDC, CONST CUserProfiles &pUsers, CONST RECT &rPage, CUIntArray &nPaging) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nSpace;
	INT  nAddress;
	INT  nAddresses;
	INT  nCount[2];
	INT  nHeight[3];
	CFont  cFont[3];
	CFont  *pOldFont;
	CString  szName;
	CString  szTitle;
	TEXTMETRIC  tmFont;
	CStringArray  szDetails;
	CStringArray  szAddress;
	CStringArray  szNumbers;
	CUserProfileInfo  *pUserInfo;

	for (nHeight[0] = nHeight[1] = nHeight[2] = 0, nSpace = 0, nPaging.RemoveAll(); CalcUserAddressBookPrintDocContentFonts(cDC, pUsers, rPage.right - rPage.left, cFont[0], cFont[1], cFont[2]); )
	{
		for (nHeight[0] = CalcAddressBookPrintDocTitleHeight(cDC, &cFont[0]); (pOldFont = cDC.SelectObject(&cFont[1])); )
		{
			nHeight[1] = (cDC.GetTextMetrics(&tmFont)) ? tmFont.tmHeight : 0;
			cDC.SelectObject(pOldFont);
			break;
		}
		if ((pOldFont = cDC.SelectObject(&cFont[2])))
		{
			nHeight[2] = (cDC.GetTextMetrics(&tmFont)) ? tmFont.tmHeight : 0;
			cDC.SelectObject(pOldFont);
		}
		for (nAddress = 0, nAddresses = (INT)pUsers.GetSize(), nHeight[1] = nHeight[2] = max(nHeight[1], nHeight[2]); nAddress < nAddresses; nAddress++)
		{
			if ((pUserInfo = (CUserProfileInfo *)pUsers.GetAt(nAddress)) != (CUserProfileInfo *)NULL)
			{
				nCount[0] = CalcUserAddressBookNameInfo(pUserInfo, szName, szDetails) + 1;
				nCount[1] = CalcUserAddressBookOfficeInfo(pUserInfo, szTitle, szAddress, szNumbers) + 1;
				nCount[1] += (CalcUserAddressBookHomeInfo(pUserInfo, szTitle, szAddress, szNumbers) + 1) + 1;
				nCount[1] += (CalcUserAddressBookMissionInfo(pUserInfo, szTitle, szAddress, szNumbers) + 1) + 1;
				nCount[1] += (CalcUserAddressBookHolidayInfo(pUserInfo, szTitle, szAddress, szNumbers) + 1) + 1;
				for (nItem = 0, nItems = 1 + max(nCount[0], nCount[1]) + 1; nItem < nItems; nItem = nItem + 1)
				{
					if (((!nItem || nItem == nItems - 1) && (nHeight[0] + nSpace) % (rPage.bottom - rPage.top) + nHeight[1] / 2 > rPage.bottom - rPage.top) || (nItem > 0 && nItem < nItems - 1 && (nHeight[0] + nSpace) % (rPage.bottom - rPage.top) + nHeight[2] > rPage.bottom - rPage.top))
					{
						nSpace += rPage.bottom - rPage.top - (nHeight[0] + nSpace) % (rPage.bottom - rPage.top);
						nPaging.Add(nHeight[0]);
						nItem = nItem - 1;
						continue;
					}
					nHeight[0] += (!nItem || nItem == nItems - 1) ? (nHeight[1] / 2) : nHeight[2];
				}
				continue;
			}
			break;
		}
		if (nAddress == nAddresses)
		{
			nPaging.Add(nHeight[0]);
			cFont[0].DeleteObject();
			cFont[1].DeleteObject();
			cFont[2].DeleteObject();
			return((INT)nPaging.GetSize());
		}
		cFont[0].DeleteObject();
		cFont[1].DeleteObject();
		cFont[2].DeleteObject();
		nPaging.RemoveAll();
		break;
	}
	return 0;
}

BOOL CMainWnd::CalcServerAddressBookPrintDocContentFonts(CDC &cDC, CONST CServerProfiles &pServers, INT nWidth, CFont &cTitleFont, CFont &cItemsFont, CFont &cDetailsFont) CONST
{
	INT  nHeight;
	INT  nMargin;
	CFont  cFont[3];
	CUIntArray  nWidths;

	for (nHeight = -(INT)(((((double)nWidth*(double)cDC.GetDeviceCaps(HORZSIZE)) / (50.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), nMargin = 0; nHeight < 0; nHeight++, nMargin = 0)
	{
		if (cFont[0].CreateFont(nHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL))
		{
			if (cFont[1].CreateFont((4 * nHeight) / 5, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL))
			{
				if (cFont[2].CreateFont((4 * nHeight) / 5, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL))
				{
					if (CalcServerAddressBookPrintDocColumnWidths(cDC, pServers, &cFont[0], &cFont[1], &cFont[2], nWidths, nMargin))
					{
						if (nWidths.GetAt(nWidths.GetUpperBound()) <= (UINT)nWidth)
						{
							cTitleFont.Attach(cFont[0].Detach());
							cItemsFont.Attach(cFont[1].Detach());
							cDetailsFont.Attach(cFont[2].Detach());
							return TRUE;
						}
						cFont[0].DeleteObject();
						cFont[1].DeleteObject();
						cFont[2].DeleteObject();
						continue;
					}
					cFont[2].DeleteObject();
				}
				cFont[1].DeleteObject();
			}
			cFont[0].DeleteObject();
		}
		break;
	}
	return FALSE;
}

BOOL CMainWnd::CalcUserAddressBookPrintDocContentFonts(CDC &cDC, CONST CUserProfiles &pUsers, INT nWidth, CFont &cTitleFont, CFont &cParagraphFont, CFont &cItemsFont) CONST
{
	INT  nHeight;
	INT  nMargin;
	CFont  cFont[3];
	CUIntArray  nWidths;

	for (nHeight = -(INT)(((((double)nWidth*(double)cDC.GetDeviceCaps(HORZSIZE)) / (50.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), nMargin = 0; nHeight < 0; nHeight++, nMargin = 0)
	{
		if (cFont[0].CreateFont(nHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL))
		{
			if (cFont[1].CreateFont((4 * nHeight) / 5, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL))
			{
				if (cFont[2].CreateFont((4 * nHeight) / 5, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL))
				{
					if (CalcUserAddressBookPrintDocColumnWidths(cDC, pUsers, &cFont[0], &cFont[1], &cFont[2], nWidths, nMargin))
					{
						if (nWidths.GetAt(nWidths.GetUpperBound()) <= (UINT)nWidth)
						{
							cTitleFont.Attach(cFont[0].Detach());
							cParagraphFont.Attach(cFont[1].Detach());
							cItemsFont.Attach(cFont[2].Detach());
							return TRUE;
						}
						cFont[0].DeleteObject();
						cFont[1].DeleteObject();
						cFont[2].DeleteObject();
						continue;
					}
					cFont[2].DeleteObject();
				}
				cFont[1].DeleteObject();
			}
			cFont[0].DeleteObject();
		}
		break;
	}
	return FALSE;
}

BOOL CMainWnd::CalcServerAddressBookPrintDocColumnWidths(CDC &cDC, CONST CServerProfiles &pServers, CFont *pTitleFont, CFont *pItemsFont, CFont *pDetailsFont, CUIntArray &nWidths, INT &nMargin) CONST
{
	INT  nNumber;
	INT  nNumbers;
	INT  nAddress;
	INT  nAddresses;
	INT  nColumn[3];
	CFont  *pOldFont;
	CString  szDevice[3];
	TEXTMETRIC  tmFont;
	CStringArray  szPhoneNumbers;
	CServerProfileInfo  *pServerInfo;

	for (nMargin = 0, nColumn[0] = nColumn[1] = nColumn[2] = 0; (pOldFont = cDC.SelectObject(pTitleFont)); )
	{
		nColumn[0] = cDC.GetTextExtent(STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_COLUMNSERVER)).cx;
		nColumn[1] = cDC.GetTextExtent(STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_COLUMNPHONENUMBERS)).cx;
		nColumn[2] = cDC.GetTextExtent(STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_COLUMNCALLBACK)).cx;
		nMargin = (cDC.GetTextMetrics(&tmFont)) ? tmFont.tmAveCharWidth / 2 : 0;
		cDC.SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		for (nAddress = 0, nAddresses = (INT)pServers.GetSize(); nAddress < nAddresses; nAddress++)
		{
			if ((pServerInfo = (CServerProfileInfo *)pServers.GetAt(nAddress)) != (CServerProfileInfo *)NULL)
			{
				for (nNumber = 0, nNumbers = pServerInfo->GetPhoneNumbers(szPhoneNumbers); nNumber < nNumbers; nNumber++)
				{
					nColumn[1] = max(cDC.GetTextExtent(szPhoneNumbers.GetAt(nNumber)).cx + nMargin, nColumn[1]);
					continue;
				}
				nColumn[0] = max(cDC.GetTextExtent(pServerInfo->GetName()).cx, nColumn[0]);
				nColumn[2] = max(cDC.GetTextExtent(pServerInfo->GetCallbackNumber()).cx + nMargin, nColumn[2]);
			}
		}
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = cDC.SelectObject(pDetailsFont)))
	{
		for (nAddress = 0, nAddresses = (INT)pServers.GetSize(); nAddress < nAddresses; nAddress++)
		{
			if ((pServerInfo = pServers.GetAt(nAddress)))
			{
				pServerInfo->GetDeviceInfo(szDevice[0], szDevice[1]);
				szDevice[2].Format(STRING(IDS_SERVERADDRESSBOOK_PRINTDOC_DEVICEDETAILS), (LPCTSTR)szDevice[0], (LPCTSTR)szDevice[1]);
				nColumn[0] = max(cDC.GetTextExtent(szDevice[2]).cx, nColumn[0]);
			}
		}
		cDC.SelectObject(pOldFont);
	}
	for (nWidths.RemoveAll(); nMargin > 0 && nColumn[0] > 0 && nColumn[1] > 0 && nColumn[2] > 0; )
	{
		nWidths.Add(3 * nMargin + nColumn[0]);
		nWidths.Add(nWidths.GetAt(0) + 2 * nMargin + nColumn[1]);
		nWidths.Add(nWidths.GetAt(1) + 2 * nMargin + nColumn[2]);
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWnd::CalcUserAddressBookPrintDocColumnWidths(CDC &cDC, CONST CUserProfiles &pUsers, CFont *pTitleFont, CFont *pParagraphFont, CFont *pItemsFont, CUIntArray &nWidths, INT &nMargin) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nAddress;
	INT  nAddresses;
	INT  nColumn[3];
	CFont  *pOldFont;
	CString  szTitle;
	TEXTMETRIC  tmFont;
	CStringArray  szAddress;
	CStringArray  szNumbers;
	CUserProfileInfo  *pUserInfo;

	for (nMargin = 0, nColumn[0] = nColumn[1] = nColumn[2] = 0; (pOldFont = cDC.SelectObject(pTitleFont)); )
	{
		nColumn[0] = cDC.GetTextExtent(STRING(IDS_USERADDRESSBOOK_PRINTDOC_COLUMNUSER)).cx;
		nColumn[1] = cDC.GetTextExtent(STRING(IDS_USERADDRESSBOOK_PRINTDOC_COLUMNDETAILS)).cx;
		nColumn[2] = cDC.GetTextExtent(STRING(IDS_USERADDRESSBOOK_PRINTDOC_COLUMNDETAILS)).cx;
		nMargin = (cDC.GetTextMetrics(&tmFont)) ? tmFont.tmAveCharWidth / 2 : 0;
		cDC.SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = cDC.SelectObject(pParagraphFont)))
	{
		nColumn[1] = max(cDC.GetTextExtent(STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHOFFICE)).cx, nColumn[1]);
		nColumn[1] = max(cDC.GetTextExtent(STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHHOME)).cx, nColumn[1]);
		nColumn[1] = max(cDC.GetTextExtent(STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHMISSION)).cx, nColumn[1]);
		nColumn[1] = max(cDC.GetTextExtent(STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHHOLIDAY)).cx, nColumn[1]);
		cDC.SelectObject(pOldFont);
	}
	for (nAddress = 0, nAddresses = (INT)pUsers.GetSize(); nAddress < nAddresses; nAddress++)
	{
		if ((pUserInfo = (CUserProfileInfo *)pUsers.GetAt(nAddress)) != (CUserProfileInfo *)NULL)
		{
			if ((pOldFont = (CFont *)cDC.SelectObject(pParagraphFont)) != (CFont *)NULL)
			{
				nColumn[0] = max(cDC.GetTextExtent(pUserInfo->GetFullName()).cx, nColumn[0]);
				cDC.SelectObject(pOldFont);
			}
			if ((pOldFont = cDC.SelectObject(pItemsFont)))
			{
				for (nItem = 0, nItems = CalcUserAddressBookOfficeInfo(pUserInfo, szTitle, szAddress, szNumbers), nColumn[0] = max(cDC.GetTextExtent(pUserInfo->GetProfession()).cx, nColumn[0]); nItem < nItems; nItem++)
				{
					nColumn[1] = max(cDC.GetTextExtent((nItem < szAddress.GetSize()) ? (LPCTSTR)szAddress.GetAt(nItem) : EMPTYSTRING).cx, nColumn[1]);
					nColumn[2] = max(cDC.GetTextExtent((nItem < szNumbers.GetSize()) ? (LPCTSTR)szNumbers.GetAt(nItem) : EMPTYSTRING).cx, nColumn[2]);
				}
				for (nItem = 0, nItems = CalcUserAddressBookHomeInfo(pUserInfo, szTitle, szAddress, szNumbers); nItem < nItems; nItem++)
				{
					nColumn[1] = max(cDC.GetTextExtent((nItem < szAddress.GetSize()) ? (LPCTSTR)szAddress.GetAt(nItem) : EMPTYSTRING).cx, nColumn[1]);
					nColumn[2] = max(cDC.GetTextExtent((nItem < szNumbers.GetSize()) ? (LPCTSTR)szNumbers.GetAt(nItem) : EMPTYSTRING).cx, nColumn[2]);
				}
				for (nItem = 0, nItems = CalcUserAddressBookMissionInfo(pUserInfo, szTitle, szAddress, szNumbers); nItem < nItems; nItem++)
				{
					nColumn[1] = max(cDC.GetTextExtent((nItem < szAddress.GetSize()) ? (LPCTSTR)szAddress.GetAt(nItem) : EMPTYSTRING).cx, nColumn[1]);
					nColumn[2] = max(cDC.GetTextExtent((nItem < szNumbers.GetSize()) ? (LPCTSTR)szNumbers.GetAt(nItem) : EMPTYSTRING).cx, nColumn[2]);
				}
				for (nItem = 0, nItems = CalcUserAddressBookHolidayInfo(pUserInfo, szTitle, szAddress, szNumbers); nItem < nItems; nItem++)
				{
					nColumn[1] = max(cDC.GetTextExtent((nItem < szAddress.GetSize()) ? (LPCTSTR)szAddress.GetAt(nItem) : EMPTYSTRING).cx, nColumn[1]);
					nColumn[2] = max(cDC.GetTextExtent((nItem < szNumbers.GetSize()) ? (LPCTSTR)szNumbers.GetAt(nItem) : EMPTYSTRING).cx, nColumn[2]);
				}
				cDC.SelectObject(pOldFont);
			}
		}
	}
	for (nWidths.RemoveAll(); nMargin > 0 && nColumn[0] > 0 && nColumn[1] > 0 && nColumn[2] > 0; )
	{
		nWidths.Add(3 * nMargin + nColumn[0]);
		nWidths.Add(nWidths.GetAt(0) + 2 * nMargin + nColumn[1]);
		nWidths.Add(nWidths.GetAt(1) + 3 * nMargin + nColumn[2]);
		return TRUE;
	}
	return FALSE;
}

INT CMainWnd::CalcUserAddressBookNameInfo(CONST CUserProfileInfo *pUserInfo, CString &szName, CStringArray &szDetails) CONST
{
	for (szName = pUserInfo->GetFullName(), szDetails.RemoveAll(); lstrlen(pUserInfo->GetProfession()) > 0; )
	{
		szDetails.Add(EMPTYSTRING);
		szDetails.Add(pUserInfo->GetProfession());
		break;
	}
	for (; lstrlen(pUserInfo->GetNotes()) > 0; )
	{
		szDetails.Add(EMPTYSTRING);
		ExtractUserAddressBookInfo(pUserInfo->GetNotes(), szDetails);
		break;
	}
	return((INT)szDetails.GetSize());
}

INT CMainWnd::CalcUserAddressBookOfficeInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST
{
	INT  nLine;
	INT  nLines;
	UINT  nDays;
	CString  szInfo;
	CTimeKey  tTime;
	CTimeSpan  tHours[2];

	for (szTitle = STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHOFFICE), szAddress.RemoveAll(); lstrlen(pUserInfo->GetOfficeCompany()) > 0; )
	{
		szAddress.Add(pUserInfo->GetOfficeCompany());
		break;
	}
	for (; lstrlen(pUserInfo->GetOfficeDepartment()) > 0; )
	{
		szAddress.Add(pUserInfo->GetOfficeDepartment());
		break;
	}
	for (ExtractUserAddressBookInfo(pUserInfo->GetOfficeStreet(), szAddress); lstrlen(pUserInfo->GetOfficeCity()) > 0; )
	{
		szAddress.Add((!pUserInfo->GetOfficeZipCode().IsEmpty()) ? (pUserInfo->GetOfficeZipCode() + SPACE + pUserInfo->GetOfficeCity()) : pUserInfo->GetOfficeCity());
		break;
	}
	for (; lstrlen(pUserInfo->GetOfficeCountry()) > 0; )
	{
		szAddress.Add(pUserInfo->GetOfficeCountry());
		break;
	}
	for (szNumbers.RemoveAll(); lstrlen(pUserInfo->GetOfficeComputer()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMCOMPUTER), (LPCTSTR)pUserInfo->GetOfficeComputer());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetOfficePhone()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMPHONE), (LPCTSTR)pUserInfo->GetOfficePhone());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetOfficePager()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMPAGER), (LPCTSTR)pUserInfo->GetOfficePager());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetOfficeFAX()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMFAX), (LPCTSTR)pUserInfo->GetOfficeFAX());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetOfficeEMail()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMEMAIL), (LPCTSTR)pUserInfo->GetOfficeEMail());
		szNumbers.Add(szInfo);
		break;
	}
	for (; pUserInfo->GetOfficeHours(nDays, tHours[0], tHours[1]) && nDays != 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_DAILYHOURS), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tHours[0].GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tHours[1].GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT));
		for (nLine = 0, nLines = (INT)(szNumbers.GetSize() - (szAddress.GetSize() + 1) - 1 - 1); nLine < nLines; nLine++)
		{
			szAddress.Add(EMPTYSTRING);
			continue;
		}
		for (szAddress.Add(EMPTYSTRING), szAddress.Add(szInfo); tTime.GetDayOfWeek() != Monday; )
		{
			tTime += SECONDSPERDAY;
			continue;
		}
		szInfo = (nDays & USERPROFILE_WORKDAY_MONDAY) ? (LPCTSTR)tTime.Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC)) : EMPTYSTRING;
		szInfo = (nDays & USERPROFILE_WORKDAY_TUESDAY) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (nDays & USERPROFILE_WORKDAY_WEDNESDAY) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 2 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 2 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (nDays & USERPROFILE_WORKDAY_THURSDAY) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 3 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 3 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (nDays & USERPROFILE_WORKDAY_FRIDAY) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 4 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 4 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (nDays & USERPROFILE_WORKDAY_SATURDAY) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 5 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 5 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (nDays & USERPROFILE_WORKDAY_SUNDAY) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 6 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 6 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szAddress.Add(szInfo);
		break;
	}
	return((INT)max(szAddress.GetSize(), szNumbers.GetSize()));
}

INT CMainWnd::CalcUserAddressBookHomeInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST
{
	INT  nLine;
	INT  nLines;
	BOOL  bDays;
	CString  szInfo;
	CTimeKey  tTime;
	CTimeSpan  tHours[2];

	for (szTitle = STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHHOME), szAddress.RemoveAll(); lstrlen(pUserInfo->GetHomeFamilyName()) > 0; )
	{
		szAddress.Add(pUserInfo->GetHomeFamilyName());
		break;
	}
	for (ExtractUserAddressBookInfo(pUserInfo->GetHomeStreet(), szAddress); lstrlen(pUserInfo->GetHomeCity()) > 0; )
	{
		szAddress.Add((!pUserInfo->GetHomeZipCode().IsEmpty()) ? (pUserInfo->GetHomeZipCode() + SPACE + pUserInfo->GetHomeCity()) : pUserInfo->GetHomeCity());
		break;
	}
	for (; lstrlen(pUserInfo->GetHomeCountry()) > 0; )
	{
		szAddress.Add(pUserInfo->GetHomeCountry());
		break;
	}
	for (szNumbers.RemoveAll(); lstrlen(pUserInfo->GetHomeComputer()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMCOMPUTER), (LPCTSTR)pUserInfo->GetHomeComputer());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetHomePhone()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMPHONE), (LPCTSTR)pUserInfo->GetHomePhone());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetHomeFAX()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMFAX), (LPCTSTR)pUserInfo->GetHomeFAX());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetHomeEMail()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMEMAIL), (LPCTSTR)pUserInfo->GetHomeEMail());
		szNumbers.Add(szInfo);
		break;
	}
	for (; pUserInfo->GetHomeHours(tHours[0], tHours[1], bDays); )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_DAILYHOURS), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tHours[0].GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tHours[1].GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT));
		for (nLine = 0, nLines = (INT)(szNumbers.GetSize() - (szAddress.GetSize() + 1) - 1 - 1); nLine < nLines; nLine++)
		{
			szAddress.Add(EMPTYSTRING);
			continue;
		}
		for (szAddress.Add(EMPTYSTRING), szAddress.Add(szInfo); tTime.GetDayOfWeek() != Monday; )
		{
			tTime += SECONDSPERDAY;
			continue;
		}
		szInfo = (bDays) ? (LPCTSTR)tTime.Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC)) : EMPTYSTRING;
		szInfo = (bDays) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (bDays) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 2 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 2 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (bDays) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 3 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 3 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (bDays) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 4 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 4 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (!bDays) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 5 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 5 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szInfo = (!bDays) ? ((!szInfo.IsEmpty()) ? (szInfo + SPACE + CTimeKey(tTime.GetTime() + 6 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : CTimeKey(tTime.GetTime() + 6 * SECONDSPERDAY).Format(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC))) : szInfo;
		szAddress.Add(szInfo);
		break;
	}
	return((INT)max(szAddress.GetSize(), szNumbers.GetSize()));
}

INT CMainWnd::CalcUserAddressBookMissionInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST
{
	INT  nLine;
	INT  nLines;
	CString  szInfo;
	CTimeKey  tTime[2];

	for (szTitle = STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHMISSION), szAddress.RemoveAll(); lstrlen(pUserInfo->GetMissionCompany()) > 0; )
	{
		szAddress.Add(pUserInfo->GetMissionCompany());
		break;
	}
	for (; lstrlen(pUserInfo->GetMissionDepartment()) > 0; )
	{
		szAddress.Add(pUserInfo->GetMissionDepartment());
		break;
	}
	for (ExtractUserAddressBookInfo(pUserInfo->GetMissionStreet(), szAddress); lstrlen(pUserInfo->GetMissionCity()) > 0; )
	{
		szAddress.Add((!pUserInfo->GetMissionZipCode().IsEmpty()) ? (pUserInfo->GetMissionZipCode() + SPACE + pUserInfo->GetMissionCity()) : pUserInfo->GetMissionCity());
		break;
	}
	for (; lstrlen(pUserInfo->GetMissionCountry()) > 0; )
	{
		szAddress.Add(pUserInfo->GetMissionCountry());
		break;
	}
	for (szNumbers.RemoveAll(); lstrlen(pUserInfo->GetMissionComputer()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMCOMPUTER), (LPCTSTR)pUserInfo->GetMissionComputer());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetMissionPhone()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMPHONE), (LPCTSTR)pUserInfo->GetMissionPhone());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetMissionMobile()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMPAGER), (LPCTSTR)pUserInfo->GetMissionMobile());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetMissionFAX()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMFAX), (LPCTSTR)pUserInfo->GetMissionFAX());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetMissionEMail()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMEMAIL), (LPCTSTR)pUserInfo->GetMissionEMail());
		szNumbers.Add(szInfo);
		break;
	}
	for (; pUserInfo->GetMission(tTime[0], tTime[1]); )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ABSENCEPERIOD), (LPCTSTR)tTime[0].FormatGmt(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ABSENCEPERIODFORMAT)), (LPCTSTR)tTime[1].FormatGmt(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ABSENCEPERIODFORMAT)));
		for (nLine = 0, nLines = (INT)(szNumbers.GetSize() - (szAddress.GetSize() + 1) - 1); nLine < nLines; nLine++)
		{
			szAddress.Add(EMPTYSTRING);
			continue;
		}
		szAddress.Add(EMPTYSTRING);
		szAddress.Add(szInfo);
		break;
	}
	return((INT)max(szAddress.GetSize(), szNumbers.GetSize()));
}

INT CMainWnd::CalcUserAddressBookHolidayInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST
{
	INT  nLine;
	INT  nLines;
	CString  szInfo;
	CTimeKey  tTime[2];

	for (szTitle = STRING(IDS_USERADDRESSBOOK_PRINTDOC_PARAGRAPHHOLIDAY), szAddress.RemoveAll(); lstrlen(pUserInfo->GetHolidayHotel()) > 0; )
	{
		szAddress.Add(pUserInfo->GetHolidayHotel());
		break;
	}
	for (; lstrlen(pUserInfo->GetHolidayApartment()) > 0; )
	{
		szAddress.Add(pUserInfo->GetHolidayApartment());
		break;
	}
	for (ExtractUserAddressBookInfo(pUserInfo->GetHolidayStreet(), szAddress); lstrlen(pUserInfo->GetHolidayCity()) > 0; )
	{
		szAddress.Add((!pUserInfo->GetHolidayZipCode().IsEmpty()) ? (pUserInfo->GetHolidayZipCode() + SPACE + pUserInfo->GetHolidayCity()) : pUserInfo->GetHolidayCity());
		break;
	}
	for (; lstrlen(pUserInfo->GetHolidayCountry()) > 0; )
	{
		szAddress.Add(pUserInfo->GetHolidayCountry());
		break;
	}
	for (szNumbers.RemoveAll(); lstrlen(pUserInfo->GetHolidayComputer()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMCOMPUTER), (LPCTSTR)pUserInfo->GetHolidayComputer());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetHolidayPhone()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMPHONE), (LPCTSTR)pUserInfo->GetHolidayPhone());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetHolidayFAX()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMFAX), (LPCTSTR)pUserInfo->GetHolidayFAX());
		szNumbers.Add(szInfo);
		break;
	}
	for (; lstrlen(pUserInfo->GetHolidayEMail()) > 0; )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ITEMEMAIL), (LPCTSTR)pUserInfo->GetHolidayEMail());
		szNumbers.Add(szInfo);
		break;
	}
	for (; pUserInfo->GetHoliday(tTime[0], tTime[1]); )
	{
		szInfo.Format(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ABSENCEPERIOD), (LPCTSTR)tTime[0].FormatGmt(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ABSENCEPERIODFORMAT)), (LPCTSTR)tTime[1].FormatGmt(STRING(IDS_USERADDRESSBOOK_PRINTDOC_ABSENCEPERIODFORMAT)));
		for (nLine = 0, nLines = (INT)(szNumbers.GetSize() - (szAddress.GetSize() + 1) - 1); nLine < nLines; nLine++)
		{
			szAddress.Add(EMPTYSTRING);
			continue;
		}
		szAddress.Add(EMPTYSTRING);
		szAddress.Add(szInfo);
		break;
	}
	return((INT)max(szAddress.GetSize(), szNumbers.GetSize()));
}

INT CMainWnd::ExtractUserAddressBookInfo(LPCTSTR pszInfo, CStringArray &szDetails) CONST
{
	INT  nPos;
	CString  szInfo;
	CString  szLine;

	for (nPos = 0; nPos < lstrlen((szInfo = pszInfo)); nPos++)
	{
		if (szInfo.Mid(nPos, lstrlen(CString(CR) + EOL)) == CString(CR) + EOL)
		{
			szDetails.Add(szLine);
			szLine.Empty();
			nPos = nPos + 1;
			continue;
		}
		if (szInfo.GetAt(nPos) == EOL)
		{
			szDetails.Add(szLine);
			szLine.Empty();
			continue;
		}
		szLine += szInfo.GetAt(nPos);
	}
	if (!szLine.IsEmpty())
	{
		szDetails.Add(szLine);
		szLine.Empty();
	}
	return((INT)szDetails.GetSize());
}

void CMainWnd::RecalcLayout(BOOL bNotify)
{
	for (CLocaleMDIFrameWnd::RecalcLayout(bNotify); IsWindow(m_pDisplayArea->GetSafeHwnd()); )
	{
		m_pDisplayArea->RecalcLayout();
		break;
	}
}

LRESULT CMainWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == AFX_WM_ON_RIBBON_CUSTOMIZE)
	{
		SetTimer(message, 0, NULL);
		return TRUE;
	}
	if (message == m_nExitID)
	{
		PostMessage(WM_CLOSE);
		return TRUE;
	}
	return CLocaleMDIFrameWnd::WindowProc(message, wParam, lParam);
}

BEGIN_MESSAGE_MAP(CMainWnd, CLocaleMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_INITMENUPOPUP()
	ON_WM_ENTERIDLE()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_QUERYENDSESSION()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SETTINGCHANGE, OnSystemSettingsChange)
	ON_MESSAGE(WM_SETMESSAGESTRING, OnSetMessageString)
	ON_MESSAGE(WM_POWERBROADCAST, OnBatteryCondition)
	ON_MESSAGE(WM_USER + 1, OnCheckSystemHealth)
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_ACCOUNTS, OnAccounts)
	ON_COMMAND(IDM_ACCOUNTPRIVILEGES, OnAccountPrivileges)
	ON_COMMAND(IDM_ACCOUNTCHANGE, OnAccountChange)
	ON_COMMAND(IDM_TELEMETRYSETTINGS, OnTelemetrySettings)
	ON_COMMAND(IDM_TELECOMMANDSETTINGS, OnTelecommandSettings)
	ON_COMMAND(IDM_SIMULATORSSETTINGS, OnSimulatorsSettings)
	ON_COMMAND(IDM_SCOESSETTINGS, OnSCOEsSettings)
	ON_COMMAND(IDM_SYSTEMALERTS, OnSystemAlerts)
	ON_COMMAND(IDM_AUTOMATIONSERVICE, OnAutomationService)
	ON_COMMAND(IDM_MEMORYDUMPSETTINGS, OnMemoryDumpSettings)
	ON_COMMAND(IDM_MEMORYDUMPIMPORT, OnMemoryDumpImport)
	ON_COMMAND(IDM_MEMORYDUMPEXPORT, OnMemoryDumpExport)
	ON_COMMAND(IDM_TMEVENTSSETTINGS, OnTelemetryEventsSettings)
	ON_COMMAND(IDM_TMEVENTSIMPORT, OnTelemetryEventsImport)
	ON_COMMAND(IDM_TMEVENTSEXPORT, OnTelemetryEventsExport)
	ON_COMMAND(IDM_TMREPORTSSETTINGS, OnTelemetryReportsSettings)
	ON_COMMAND(IDM_TMREPORTSRETRIEVALS, OnTelemetryReportsRetrievals)
	ON_COMMAND(IDM_TMREPORTSIMPORT, OnTelemetryReportsImport)
	ON_COMMAND(IDM_TMREPORTSEXPORT, OnTelemetryReportsExport)
	ON_COMMAND(IDM_TMPARAMETERS, OnTelemetryParameters)
	ON_COMMAND(IDM_TMARCHIVESSETTINGS, OnTelemetryArchivesSettings)
	ON_COMMAND(IDM_TMARCHIVESEXTRACTIONSIMPORT, OnTelemetryArchivesExtractionsImport)
	ON_COMMAND(IDM_TMARCHIVESEXTRACTIONSEXPORT, OnTelemetryArchivesExtractionsExport)
	ON_COMMAND(IDM_AND, OnAND)
	ON_COMMAND(IDM_GRD, OnGRD)
	ON_COMMAND(IDM_HEX, OnHEX)
	ON_COMMAND(IDM_OOL, OnOOL)
	ON_COMMAND(IDM_MMD, OnMMD)
	ON_COMMAND(IDM_POD, OnPOD)
	ON_COMMAND(IDM_SATELLITETRACKINGTOOL, OnSatelliteTrackingTool)
	ON_COMMAND(IDM_EVENTBOX, OnEventBox)
	ON_COMMAND(IDM_MAILBOX, OnMailBox)
	ON_COMMAND(IDM_LOGBOOK, OnLogBook)
	ON_COMMAND(IDM_ANDIMPORT, OnANDImport)
	ON_COMMAND(IDM_GRDIMPORT, OnGRDImport)
	ON_COMMAND(IDM_PODIMPORT, OnPODImport)
	ON_COMMAND(IDM_ANDEXPORT, OnANDExport)
	ON_COMMAND(IDM_GRDEXPORT, OnGRDExport)
	ON_COMMAND(IDM_PODEXPORT, OnPODExport)
	ON_COMMAND(IDM_TCMANUALSTACK, OnTCManualStack)
	ON_COMMAND(IDM_TCAUTOMATICSTACK, OnTCAutomaticStack)
	ON_COMMAND(IDM_TCPROCEDURESMONITOR, OnTCProceduresMonitor)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMP, OnTCDiagnosticsOversamplingDump)
	ON_COMMAND(IDM_TCONBOARDBUFFERQUEUES, OnTCOnBoardBufferQueues)
	ON_COMMAND(IDM_TCONBOARDMEMORYIMAGES, OnTCOnBoardMemoryImages)
	ON_COMMAND(IDM_TCHISTORY, OnTCHistory)
	ON_COMMAND(IDM_TCPARAMETERS, OnTelecommandParameters)
	ON_COMMAND(IDM_TCOPTIONS, OnTelecommandOptions)
	ON_COMMAND(IDM_PFLPSERVICE, OnPFLPService)
	ON_COMMAND(IDM_PFLPCLIENTS, OnPFLPClients)
	ON_COMMAND(IDM_TPEPSERVICE, OnTPEPService)
	ON_COMMAND(IDM_TPEPCONNECT, OnTPEPConnect)
	ON_COMMAND(IDM_TPEPCLIENTS, OnTPEPClients)
	ON_COMMAND(IDM_TPEPVIEW, OnTPEPView)
	ON_COMMAND(IDM_SERVERADDRESSBOOK, OnServerAddressBook)
	ON_COMMAND(IDM_USERADDRESSBOOK, OnUserAddressBook)
	ON_COMMAND(IDM_DOWNLOADS, OnToolsDownloads)
	ON_COMMAND(IDM_CUSTOMIZATIONS, OnToolsOptions)
	ON_COMMAND(IDM_PRINTSETUP, OnPrintSetup)
	ON_COMMAND(IDM_PRINTDISPLAY, OnPrint)
	ON_COMMAND(IDM_PRINTSERVERADDRESSBOOK, OnPrintServerAddressBook)
	ON_COMMAND(IDM_PRINTUSERADDRESSBOOK, OnPrintUserAddressBook)
	ON_COMMAND(IDM_DISPLAYREDUCEFONTS, OnDisplayReduceFonts)
	ON_COMMAND(IDM_DISPLAYRESTOREFONTS, OnDisplayRestoreFonts)
	ON_COMMAND(IDM_WINDOWS, OnWindows)
	ON_COMMAND(IDM_NEXTWINDOW, OnNextWindow)
	ON_COMMAND(IDM_PREVIOUSWINDOW, OnPreviousWindow)
	ON_COMMAND(IDM_CLOSEWINDOW, OnCloseWindow)
	ON_COMMAND(IDM_CLOSEALLWINDOWS, OnCloseAllWindows)
	ON_COMMAND(IDM_LOCK, OnLock)
	ON_COMMAND(IDM_ASSISTANTSUPPORTDATECONVERSIONS, OnAssistantSupportDateConversions)
	ON_COMMAND(IDM_ASSISTANTLISTEN, OnAssistantListen)
	ON_COMMAND(IDM_STATUSBARTELEMETRYSTATUS, OnStatusBarTelemetryStatus)
	ON_COMMAND(IDM_STATUSBARTELECOMMANDSTATUS, OnStatusBarTelecommandStatus)
	ON_COMMAND(IDM_STATUSBARARCHIVINGSTATUS, OnStatusBarArchivingStatus)
	ON_COMMAND(IDM_STATUSBARCPUPERFORMANCESTATUS, OnStatusBarCPUPerformanceStatus)
	ON_COMMAND(IDM_STATUSBARCLOCK, OnStatusBarClock)
	ON_COMMAND(IDM_STATUSBARHELP, OnStatusBarHelp)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_HELP, OnHelp)
#ifdef SATELLITETRACKING
	ON_COMMAND_RANGE(MINSPACEENGINEMENUID, MAXSPACEENGINEMENUID, OnMenuID)
#endif
	ON_UPDATE_COMMAND_UI(IDM_SETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_ACCOUNTS, OnUpdateAccounts)
	ON_UPDATE_COMMAND_UI(IDM_ACCOUNTPRIVILEGES, OnUpdateAccountPrivileges)
	ON_UPDATE_COMMAND_UI(IDM_ACCOUNTCHANGE, OnUpdateAccountChange)
	ON_UPDATE_COMMAND_UI(IDM_TELEMETRYEQUIPMENT, OnUpdateTelemetryEquipment)
	ON_UPDATE_COMMAND_UI(IDM_TELEMETRYSETTINGS, OnUpdateTelemetrySettings)
	ON_UPDATE_COMMAND_UI(IDM_TELECOMMANDEQUIPMENT, OnUpdateTelecommandEquipment)
	ON_UPDATE_COMMAND_UI(IDM_TELECOMMANDSETTINGS, OnUpdateTelecommandSettings)
	ON_UPDATE_COMMAND_UI(IDM_SIMULATORSEQUIPMENT, OnUpdateSimulatorsEquipment)
	ON_UPDATE_COMMAND_UI(IDM_SIMULATORSSETTINGS, OnUpdateSimulatorsSettings)
	ON_UPDATE_COMMAND_UI(IDM_SCOESEQUIPMENT, OnUpdateSCOEsEquipment)
	ON_UPDATE_COMMAND_UI(IDM_SCOESSETTINGS, OnUpdateSCOEsSettings)
	ON_UPDATE_COMMAND_UI(IDM_SYSTEMALERTS, OnUpdateSystemAlerts)
	ON_UPDATE_COMMAND_UI(IDM_AUTOMATIONSERVICE, OnUpdateAutomationService)
	ON_UPDATE_COMMAND_UI(IDM_MEMORYDUMPSETTINGS, OnUpdateMemoryDumpSettings)
	ON_UPDATE_COMMAND_UI(IDM_MEMORYDUMPIMPORT, OnUpdateMemoryDumpImport)
	ON_UPDATE_COMMAND_UI(IDM_MEMORYDUMPEXPORT, OnUpdateMemoryDumpExport)
	ON_UPDATE_COMMAND_UI(IDM_TMEVENTSSETTINGS, OnUpdateTelemetryEventsSettings)
	ON_UPDATE_COMMAND_UI(IDM_TMEVENTSIMPORT, OnUpdateTelemetryEventsImport)
	ON_UPDATE_COMMAND_UI(IDM_TMEVENTSEXPORT, OnUpdateTelemetryEventsExport)
	ON_UPDATE_COMMAND_UI(IDM_TMREPORTSSETTINGS, OnUpdateTelemetryReportsSettings)
	ON_UPDATE_COMMAND_UI(IDM_TMREPORTSRETRIEVALS, OnUpdateTelemetryReportsRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_TMREPORTSIMPORT, OnUpdateTelemetryReportsImport)
	ON_UPDATE_COMMAND_UI(IDM_TMREPORTSEXPORT, OnUpdateTelemetryReportsExport)
	ON_UPDATE_COMMAND_UI(IDM_TMPARAMETERS, OnUpdateTelemetryParameters)
	ON_UPDATE_COMMAND_UI(IDM_TMARCHIVESSETTINGS, OnUpdateTelemetryArchivesSettings)
	ON_UPDATE_COMMAND_UI(IDM_TMARCHIVESEXTRACTIONSIMPORT, OnUpdateTelemetryArchivesExtractionsImport)
	ON_UPDATE_COMMAND_UI(IDM_TMARCHIVESEXTRACTIONSEXPORT, OnUpdateTelemetryArchivesExtractionsExport)
	ON_UPDATE_COMMAND_UI(IDM_AND, OnUpdateAND)
	ON_UPDATE_COMMAND_UI(IDM_GRD, OnUpdateGRD)
	ON_UPDATE_COMMAND_UI(IDM_HEX, OnUpdateHEX)
	ON_UPDATE_COMMAND_UI(IDM_OOL, OnUpdateOOL)
	ON_UPDATE_COMMAND_UI(IDM_MMD, OnUpdateMMD)
	ON_UPDATE_COMMAND_UI(IDM_POD, OnUpdatePOD)
	ON_UPDATE_COMMAND_UI(IDM_SATELLITETRACKINGTOOL, OnUpdateSatelliteTrackingTool)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOX, OnUpdateEventBox)
	ON_UPDATE_COMMAND_UI(IDM_MAILBOX, OnUpdateMailBox)
	ON_UPDATE_COMMAND_UI(IDM_LOGBOOK, OnUpdateLogBook)
	ON_UPDATE_COMMAND_UI(IDM_ANDIMPORT, OnUpdateANDImport)
	ON_UPDATE_COMMAND_UI(IDM_GRDIMPORT, OnUpdateGRDImport)
	ON_UPDATE_COMMAND_UI(IDM_PODIMPORT, OnUpdatePODImport)
	ON_UPDATE_COMMAND_UI(IDM_ANDEXPORT, OnUpdateANDExport)
	ON_UPDATE_COMMAND_UI(IDM_GRDEXPORT, OnUpdateGRDExport)
	ON_UPDATE_COMMAND_UI(IDM_PODEXPORT, OnUpdatePODExport)
	ON_UPDATE_COMMAND_UI(IDM_TCMANUALSTACK, OnUpdateTCManualStack)
	ON_UPDATE_COMMAND_UI(IDM_TCAUTOMATICSTACK, OnUpdateTCAutomaticStack)
	ON_UPDATE_COMMAND_UI(IDM_TCPROCEDURESMONITOR, OnUpdateTCProceduresMonitor)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMP, OnUpdateTCDiagnosticsOversamplingDump)
	ON_UPDATE_COMMAND_UI(IDM_TCONBOARDBUFFERQUEUES, OnUpdateTCOnBoardBufferQueues)
	ON_UPDATE_COMMAND_UI(IDM_TCONBOARDMEMORYIMAGES, OnUpdateTCOnBoardMemoryImages)
	ON_UPDATE_COMMAND_UI(IDM_TCHISTORY, OnUpdateTCHistory)
	ON_UPDATE_COMMAND_UI(IDM_TCPARAMETERS, OnUpdateTelecommandParameters)
	ON_UPDATE_COMMAND_UI(IDM_TCOPTIONS, OnUpdateTelecommandOptions)
	ON_UPDATE_COMMAND_UI(IDM_PFLPSERVICE, OnUpdatePFLPService)
	ON_UPDATE_COMMAND_UI(IDM_PFLPCLIENTS, OnUpdatePFLPClients)
	ON_UPDATE_COMMAND_UI(IDM_TPEPSERVICE, OnUpdateTPEPService)
	ON_UPDATE_COMMAND_UI(IDM_TPEPCONNECT, OnUpdateTPEPConnect)
	ON_UPDATE_COMMAND_UI(IDM_TPEPCLIENTS, OnUpdateTPEPClients)
	ON_UPDATE_COMMAND_UI(IDM_TPEPVIEW, OnUpdateTPEPView)
	ON_UPDATE_COMMAND_UI(IDM_SERVERADDRESSBOOK, OnUpdateServerAddressBook)
	ON_UPDATE_COMMAND_UI(IDM_USERADDRESSBOOK, OnUpdateUserAddressBook)
	ON_UPDATE_COMMAND_UI(IDM_DOWNLOADS, OnUpdateToolsDownloads)
	ON_UPDATE_COMMAND_UI(IDM_CUSTOMIZATIONS, OnUpdateToolsOptions)
	ON_UPDATE_COMMAND_UI(IDM_PRINTSETUP, OnUpdatePrintSetup)
	ON_UPDATE_COMMAND_UI(IDM_PRINTDISPLAY, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(IDM_PRINTSERVERADDRESSBOOK, OnUpdatePrintServerAddressBook)
	ON_UPDATE_COMMAND_UI(IDM_PRINTUSERADDRESSBOOK, OnUpdatePrintUserAddressBook)
	ON_UPDATE_COMMAND_UI(IDM_DISPLAYREDUCEFONTS, OnUpdateDisplayReduceFonts)
	ON_UPDATE_COMMAND_UI(IDM_DISPLAYRESTOREFONTS, OnUpdateDisplayRestoreFonts)
	ON_UPDATE_COMMAND_UI(IDM_WINDOWS, OnUpdateWindows)
	ON_UPDATE_COMMAND_UI(IDM_NEXTWINDOW, OnUpdateNextWindow)
	ON_UPDATE_COMMAND_UI(IDM_PREVIOUSWINDOW, OnUpdatePreviousWindow)
	ON_UPDATE_COMMAND_UI(IDM_CLOSEWINDOW, OnUpdateCloseWindow)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_CASCADE, OnUpdateCascadeWindows)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_HORZ, OnUpdateTileHorzWindows)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_VERT, OnUpdateTileVertWindows)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_ARRANGE, OnUpdateArrangeWindows)
	ON_UPDATE_COMMAND_UI(IDM_CLOSEALLWINDOWS, OnUpdateCloseAllWindows)
	ON_UPDATE_COMMAND_UI(IDM_LOCK, OnUpdateLock)
	ON_UPDATE_COMMAND_UI(IDM_DISPLAYPAGES, OnUpdateDisplayPages)
	ON_UPDATE_COMMAND_UI(IDM_ASSISTANTSUPPORTDATECONVERSIONS, OnUpdateAssistantSupportDateConversions)
	ON_UPDATE_COMMAND_UI(IDM_ASSISTANTLISTEN, OnUpdateAssistantListen)
	ON_UPDATE_COMMAND_UI(IDM_STATUSBARTELEMETRYSTATUS, OnUpdateStatusBarTelemetryStatus)
	ON_UPDATE_COMMAND_UI(IDM_STATUSBARTELECOMMANDSTATUS, OnUpdateStatusBarTelecommandStatus)
	ON_UPDATE_COMMAND_UI(IDM_STATUSBARARCHIVINGSTATUS, OnUpdateStatusBarArchivingStatus)
	ON_UPDATE_COMMAND_UI(IDM_STATUSBARCPUPERFORMANCESTATUS, OnUpdateStatusBarCPUPerformanceStatus)
	ON_UPDATE_COMMAND_UI(IDM_STATUSBARCLOCK, OnUpdateStatusBarClock)
	ON_UPDATE_COMMAND_UI(IDM_STATUSBARHELP, OnUpdateStatusBarHelp)
	ON_UPDATE_COMMAND_UI(IDM_ABOUT, OnUpdateAbout)
	ON_UPDATE_COMMAND_UI(IDM_HELP, OnUpdateHelp)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateExit)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTDISPLAYWINDOWS, IDM_LASTDISPLAYWINDOWS, OnUpdateDisplayWindows)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTDISPLAYWINDOW, IDM_LASTDISPLAYWINDOW, OnUpdateDisplayWindow)
#ifdef SATELLITETRACKING
	ON_UPDATE_COMMAND_UI_RANGE(MINSPACEENGINEMENUID, MAXSPACEENGINEMENUID, OnUpdateMenuID)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWnd message handlers

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CLocaleMDIFrameWnd::OnCreate(lpCreateStruct) != -1 && CreateLogo() && CreateRibbonBar() && CreateStatusBar()) ? 0 : -1);
}

BOOL CMainWnd::OnCreateClient(LPCREATESTRUCT pcs, CCreateContext *pContext)
{
	CString  szExit;
	CVersionInfo  cVersionInfo;
	SCROLLINFO  sScrollInfo = { sizeof(SCROLLINFO),SIF_ALL };

	for (m_bDoSubclass = FALSE; CLocaleMDIFrameWnd::OnCreateClient(pcs, pContext); )
	{
		for (szExit.Format(STRING(IDS_APPLICATIONINFO_COMMANDTERMINATION_DESKTOP), (LPCTSTR)cVersionInfo.QueryProductName()), m_nExitID = RegisterWindowMessage(szExit); m_pDisplayFrame->Create(this); )
		{
			m_pDisplayFrame->SetScrollInfo(SB_HORZ, &sScrollInfo);
			m_pDisplayFrame->SetScrollInfo(SB_VERT, &sScrollInfo);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
	for (CLocaleMDIFrameWnd::OnSize(nType, cx, cy); IsIconic(); )
	{
		m_pDisplayArea->RecalcLayout();
		break;
	}
}

BOOL CMainWnd::OnEraseBkgnd(CDC *pDC)
{
	CRect  rArea;
	CBrush  cBrush;

	for (GetClientRect(rArea); cBrush.CreateSolidBrush(GetSysColor(COLOR_APPWORKSPACE)); )
	{
		pDC->FillRect(rArea, &cBrush);
		cBrush.DeleteObject();
		return TRUE;
	}
	return CLocaleMDIFrameWnd::OnEraseBkgnd(pDC);
}

void CMainWnd::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UINT  nItem;
	UINT  nItems;
	CMenu  *pSubMenu;

	for (nItem = 0, nItems = pPopupMenu->GetMenuItemCount(); nItem < nItems && !bSysMenu; nItem++)
	{
		if ((pSubMenu = pPopupMenu->GetSubMenu(nItem)))
		{
			OnInitMenuPopup(pSubMenu, nItem, bSysMenu);
			pPopupMenu->EnableMenuItem(nItem, MF_BYPOSITION | GetSubMenuState(pSubMenu));
			continue;
		}
	}
	CLocaleMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

void CMainWnd::OnEnterIdle(UINT nType, CWnd *pWnd)
{
	for (; nType == MSGF_DIALOGBOX; )
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CLoginDialog)))
		{
			ShowMessage(IDS_STATUSBAR_LOGGING);
			break;
		}
		if (pWnd->IsKindOf(RUNTIME_CLASS(CPasswordDialog)))
		{
			ShowMessage(IDS_STATUSBAR_PASSWORD);
			break;
		}
		break;
	}
	CLocaleMDIFrameWnd::OnEnterIdle(nType, pWnd);
}

BOOL CMainWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDM_DISPLAYPAGES)
	{
		CDisplayPagesDialog  cDisplayPagesDialog;
		cDisplayPagesDialog.DoModal();
		return TRUE;
	}
	if (LOWORD(wParam) >= IDM_FIRSTDISPLAYWINDOWS  &&  LOWORD(wParam) <= IDM_LASTDISPLAYWINDOWS)
	{
		CDisplayWindowsDialog  cDisplayWindowsDialog;
		cDisplayWindowsDialog.DoModal(LOWORD(wParam) - IDM_DISPLAYWINDOWS);
		return TRUE;
	}
	if (LOWORD(wParam) >= IDM_FIRSTDISPLAYWINDOW  &&  LOWORD(wParam) <= IDM_LASTDISPLAYWINDOW)
	{
		m_pDisplayArea->ActivateDisplay((UINT)(LOWORD(wParam) - IDM_FIRSTDISPLAYWINDOW));
		return TRUE;
	}
	return CLocaleMDIFrameWnd::OnCommand(wParam, lParam);
}

void CMainWnd::OnTimer(UINT_PTR nEventID)
{
	CWnd  *pWnd;
	CString  szMessage;
	CUserInterfaceDialog  *pUserInterfaceDialog;

	if (nEventID == TOOLSDATABASESERVICE_BEHAVIOR_TIMERID)
	{
		if ((pWnd = GetWindow(GW_ENABLEDPOPUP)) != (CWnd *)NULL)
		{
			pWnd->SendMessage(WM_SYSCOMMAND, SC_CLOSE);
			return;
		}
		for (ShowWaitCursor(), KillTimer(nEventID), szMessage.Empty(); ReloadAccount(CDesktopApp::ReloadDatabase); )
		{
			szMessage.Format(STRING(IDS_TOOLSOPTIONSDATABASE_UPDATE_MESSAGE_SUCCESS), (LPCTSTR)GetAccountDatabase());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			break;
		}
		if (szMessage.IsEmpty())
		{
			szMessage.Format(STRING(IDS_TOOLSOPTIONSDATABASE_UPDATE_MESSAGE_FAILURE), (LPCTSTR)GetAccountDatabase());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
		}
		StopWaitCursor();
	}
	if (nEventID == AFX_WM_ON_RIBBON_CUSTOMIZE)
	{
		for (KillTimer(nEventID); (pUserInterfaceDialog = new CUserInterfaceDialog(this, &m_wndRibbonBar)); )
		{
			pUserInterfaceDialog->DoModal();
			delete pUserInterfaceDialog;
			break;
		}
	}
	CLocaleMDIFrameWnd::OnTimer(nEventID);
}

BOOL CMainWnd::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	if (IsShowingWaitCursor())
	{
		RestoreWaitCursor();
		SetCapture();
		return TRUE;
	}
	if (m_wndStatusBar.IsShowingProgress())
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
		return TRUE;
	}
	return CLocaleMDIFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CMainWnd::OnSystemSettingsChange(WPARAM wParam, LPARAM lParam)
{
	InitializeDefaultPrinter();
	return Default();
}

LRESULT CMainWnd::OnSetMessageString(WPARAM wParam, LPARAM lParam)
{
	if (wParam == AFX_IDS_MDICHILD) return FALSE;
	return((!IsWindow(m_pLogoWnd->GetSafeHwnd()) || !m_pLogoWnd->IsWindowVisible()) ? CLocaleMDIFrameWnd::OnSetMessageString(wParam, lParam) : FALSE);
}

LRESULT CMainWnd::OnBatteryCondition(WPARAM wParam, LPARAM lParam)
{
	SYSTEM_POWER_STATUS  sPowerStatus;

	if (wParam == PBT_APMPOWERSTATUSCHANGE)
	{
		for (; GetSystemPowerStatus(&sPowerStatus); )
		{
			if ((((sPowerStatus.BatteryFlag & BATTERY_FLAG_LOW) || (sPowerStatus.BatteryFlag & BATTERY_FLAG_CRITICAL)) && (sPowerStatus.BatteryFlag & BATTERY_FLAG_CHARGING) != BATTERY_FLAG_CHARGING) && !m_bBattery)
			{
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, STRING(IDS_POWER_BATTERYLOW));
				m_bBattery = TRUE;
				break;
			}
			m_bBattery = (sPowerStatus.BatteryFlag & (BATTERY_FLAG_LOW | BATTERY_FLAG_CRITICAL)) ? m_bBattery : FALSE;
			break;
		}
	}
	return Default();
}

LRESULT CMainWnd::OnCheckSystemHealth(WPARAM wParam, LPARAM lParam)
{
	return GetTMService()->IsHealthy() && GetTCService()->IsHealthy();
}

BOOL CMainWnd::OnQueryEndSession()
{
	return CLocaleMDIFrameWnd::OnQueryEndSession() && FALSE;
}

void CMainWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	m_dlgSettings.DoModal();
}

void CMainWnd::OnAccounts()
{
	CUserAccounts  cUserAccounts;
	CAccountToken  cAccountToken;
	CHourglassCursor  cCursor;

	if (m_dlgUserAccounts.DoModal() == IDOK)
	{
		if (ValidateAccount())
		{
			UpdateStatusBar();
			UpdateDisplays();
			UpdateMenus();
			return;
		}
		if (CDesktopApp::ValidateAccounts())
		{
			if (cUserAccounts.GetActiveAccount(&cAccountToken) && cUserAccounts.ReadAccount(&cAccountToken))
			{
				if (m_dlgAccountChange.DoModal(&cAccountToken) == IDOK)
				{
					ShowWaitCursor();
					StartAccount(&cAccountToken);
					StopWaitCursor();
					return;
				}
			}
		}
		for (ShowWaitCursor(); TRUE; )
		{
			ResetAccount(SYSTEM_NOERROR);
			break;
		}
		StopWaitCursor();
	}
}

void CMainWnd::OnAccountPrivileges()
{
	CAccountToken  cAccountToken;
	CHourglassCursor  cCursor;

	for (GetAccount(&cAccountToken); m_dlgUserPrivileges.DoModal(&cAccountToken) == IDOK; )
	{
		SetAccount(&cAccountToken);
		UpdateDisplays();
		UpdateMenus();
		break;
	}
}

void CMainWnd::OnAccountChange()
{
	CAccountToken  cAccountToken[2];
	CHourglassCursor  cCursor;

	for (GetAccount(&cAccountToken[0]), GetAccount(&cAccountToken[1]); m_dlgAccountChange.DoModal(&cAccountToken[0]) == IDOK; )
	{
		for (ShowWaitCursor(); !cAccountToken[0].Compare(&cAccountToken[1]); )
		{
			StartAccount(&cAccountToken[0]);
			break;
		}
		StopWaitCursor();
		break;
	}
}

void CMainWnd::OnTelemetrySettings()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryService.DoModal();
}

void CMainWnd::OnTelecommandSettings()
{
	CHourglassCursor  cCursor;

	m_dlgTelecommandService.DoModal();
}

void CMainWnd::OnSimulatorsSettings()
{
}

void CMainWnd::OnSCOEsSettings()
{
}

void CMainWnd::OnSystemAlerts()
{
	CHourglassCursor  cCursor;

	m_dlgSystemAlerts.DoModal();
}

void CMainWnd::OnAutomationService()
{
	CHourglassCursor  cCursor;

	m_dlgAutomationService.DoModal();
}

void CMainWnd::OnMemoryDumpSettings()
{
	CHourglassCursor  cCursor;

	m_dlgMemoryDumpsService.DoModal();
}

void CMainWnd::OnMemoryDumpImport()
{
	CHourglassCursor  cCursor;

	m_dlgMemoryDumpsImport.DoModal();
}

void CMainWnd::OnMemoryDumpExport()
{
	CHourglassCursor  cCursor;

	m_dlgMemoryDumpsExport.DoModal();
}

void CMainWnd::OnTelemetryEventsSettings()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryEvents.DoModal();
}

void CMainWnd::OnTelemetryEventsImport()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryEventsImport.DoModal();
}

void CMainWnd::OnTelemetryEventsExport()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryEventsExport.DoModal();
}

void CMainWnd::OnTelemetryReportsSettings()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryReports.DoModal();
}

void CMainWnd::OnTelemetryReportsRetrievals()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryReportsRetrievals.DoModal();
}

void CMainWnd::OnTelemetryReportsImport()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryReportsImport.DoModal();
}

void CMainWnd::OnTelemetryReportsExport()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryReportsExport.DoModal();
}

void CMainWnd::OnTelemetryParameters()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryParameters.DoModal();
}

void CMainWnd::OnTelemetryArchivesSettings()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryArchives.DoModal();
}

void CMainWnd::OnTelemetryArchivesExtractionsImport()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryArchivesExtractionsImport.DoModal();
}

void CMainWnd::OnTelemetryArchivesExtractionsExport()
{
	CHourglassCursor  cCursor;

	m_dlgTelemetryArchivesExtractionsExport.DoModal();
}

void CMainWnd::OnAND()
{
	CANDWnd  *pANDWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pANDWnd = new CANDWnd) || !m_pDisplayArea->AddDisplay(pANDWnd)) ? SYSTEM_WARNING_AND_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnGRD()
{
	CGRDWnd  *pGRDWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pGRDWnd = new CGRDWnd) || !m_pDisplayArea->AddDisplay(pGRDWnd)) ? SYSTEM_WARNING_GRD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnHEX()
{
	CHEXWnd  *pHEXWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pHEXWnd = new CHEXWnd) || !m_pDisplayArea->AddDisplay(pHEXWnd)) ? SYSTEM_WARNING_HEX_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOOL()
{
	COOLWnd  *pOOLWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pOOLWnd = new COOLWnd) || !m_pDisplayArea->AddDisplay(pOOLWnd)) ? SYSTEM_WARNING_OOL_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnMMD()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pMMDWnd = new CMMDWnd) || !m_pDisplayArea->AddDisplay(pMMDWnd)) ? SYSTEM_WARNING_MMD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnPOD()
{
	CPODWnd  *pPODWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pPODWnd = new CPODWnd) || !m_pDisplayArea->AddDisplay(pPODWnd)) ? SYSTEM_WARNING_POD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnSatelliteTrackingTool()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)))
	{
		pDisplayWnd->ActivateFrame((!pDisplayWnd->IsWindowVisible()) ? SW_SHOWNORMAL : SW_HIDE);
	}
}

void CMainWnd::OnEventBox()
{
	CEventBoxWnd  *pEventBoxWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pEventBoxWnd = new CEventBoxWnd) || !m_pDisplayArea->AddDisplay(pEventBoxWnd)) ? SYSTEM_WARNING_EVENTBOX_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnMailBox()
{
	return;
}

void CMainWnd::OnLogBook()
{
	return;
}

void CMainWnd::OnANDImport()
{
	CHourglassCursor  cCursor;

	m_dlgANDImport.DoModal();
}

void CMainWnd::OnGRDImport()
{
	CHourglassCursor  cCursor;

	m_dlgGRDImport.DoModal();
}

void CMainWnd::OnPODImport()
{
	CHourglassCursor  cCursor;

	m_dlgPODImport.DoModal();
}

void CMainWnd::OnANDExport()
{
	CHourglassCursor  cCursor;

	m_dlgANDExport.DoModal();
}

void CMainWnd::OnGRDExport()
{
	CHourglassCursor  cCursor;

	m_dlgGRDExport.DoModal();
}

void CMainWnd::OnPODExport()
{
	CHourglassCursor  cCursor;

	m_dlgPODExport.DoModal();
}

void CMainWnd::OnTCManualStack()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCMANUALSTACK)))
	{
		pDisplayWnd->ActivateFrame((!pDisplayWnd->IsWindowVisible()) ? SW_SHOWNORMAL : SW_HIDE);
	}
}

void CMainWnd::OnTCAutomaticStack()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK)))
	{
		pDisplayWnd->ActivateFrame((!pDisplayWnd->IsWindowVisible()) ? SW_SHOWNORMAL : SW_HIDE);
	}
}

void CMainWnd::OnTCProceduresMonitor()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR)))
	{
		pDisplayWnd->ActivateFrame((!pDisplayWnd->IsWindowVisible()) ? SW_SHOWNORMAL : SW_HIDE);
	}
}

void CMainWnd::OnTCDiagnosticsOversamplingDump()
{
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pTCDiagnosticsOversamplingDumpWnd = new CTCDiagnosticsOversamplingDumpWnd) || !m_pDisplayArea->AddDisplay(pTCDiagnosticsOversamplingDumpWnd)) ? SYSTEM_WARNING_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnTCOnBoardBufferQueues()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES)))
	{
		pDisplayWnd->ActivateFrame((!pDisplayWnd->IsWindowVisible()) ? SW_SHOWNORMAL : SW_HIDE);
	}
}

void CMainWnd::OnTCOnBoardMemoryImages()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)))
	{
		pDisplayWnd->ActivateFrame((!pDisplayWnd->IsWindowVisible()) ? SW_SHOWNORMAL : SW_HIDE);
	}
}

void CMainWnd::OnTCHistory()
{
	CTCHistoryWnd  *pTCHistoryWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pTCHistoryWnd = new CTCHistoryWnd) || !m_pDisplayArea->AddDisplay(pTCHistoryWnd)) ? SYSTEM_WARNING_TCHISTORY_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnTelecommandParameters()
{
	CHourglassCursor  cCursor;

	m_dlgTelecommandParameters.DoModal();
}

void CMainWnd::OnTelecommandOptions()
{
	CHourglassCursor  cCursor;

	m_dlgTelecommandOptions.DoModal();
}

void CMainWnd::OnPFLPService()
{
	CHourglassCursor  cCursor;

	m_dlgPFLPService.DoModal();
}

void CMainWnd::OnPFLPClients()
{
	CHourglassCursor  cCursor;

	m_dlgPFLPClients.DoModal();
}

void CMainWnd::OnTPEPService()
{
	CHourglassCursor  cCursor;

	m_dlgTPEPService.DoModal();
}

void CMainWnd::OnTPEPConnect()
{
	CHourglassCursor  cCursor;

	m_dlgTPEPConnect.DoModal();
}

void CMainWnd::OnTPEPClients()
{
	CHourglassCursor  cCursor;

	m_dlgTPEPClients.DoModal();
}

void CMainWnd::OnTPEPView()
{
	CTPEPWnd  *pTPEPWnd;
	CHourglassCursor  cCursor;

	ReportEvent((!(pTPEPWnd = new CTPEPWnd) || !m_pDisplayArea->AddDisplay(pTPEPWnd)) ? SYSTEM_WARNING_TPEP_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnServerAddressBook()
{
	CHourglassCursor  cCursor;

	m_dlgServerAddressBook.DoModal();
}

void CMainWnd::OnUserAddressBook()
{
	CHourglassCursor  cCursor;

	m_dlgUserAddressBook.DoModal();
}

void CMainWnd::OnToolsDownloads()
{
	CHourglassCursor  cCursor;

	m_dlgToolsDownloads.DoModal();
}

void CMainWnd::OnToolsOptions()
{
	CHourglassCursor  cCursor;

	m_dlgToolsOptions.DoModal();
}

void CMainWnd::OnPrintSetup()
{
	CHourglassCursor  cCursor;

	m_dlgPrintPageSetup.DoModal();
}

void CMainWnd::OnPrint()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetActiveDisplay()) && m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		ReportEvent((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd)) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
	}
}

void CMainWnd::OnPrintServerAddressBook()
{
	CHourglassCursor  cCursor;

	if (m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		PrintServerAddressBook(&m_dlgPrintPagePrepare.m_pd);
	}
}

void CMainWnd::OnPrintUserAddressBook()
{
	CHourglassCursor  cCursor;

	if (m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		PrintUserAddressBook(&m_dlgPrintPagePrepare.m_pd);
	}
}

void CMainWnd::OnDisplayReduceFonts()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetActiveDisplay()))
	{
		pDisplayWnd->ReduceFonts(FALSE);
	}
}

void CMainWnd::OnDisplayRestoreFonts()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetActiveDisplay()))
	{
		pDisplayWnd->ReduceFonts(TRUE);
	}
}

void CMainWnd::OnWindows()
{
	CHourglassCursor  cCursor;

	if (GetDisplayArea()->GetType() == DISPLAYAREA_TYPE_FOLDER)
	{
		CDisplayPagesDialog  cDisplayPagesDialog;

		cDisplayPagesDialog.DoModal();
	}
}

void CMainWnd::OnNextWindow()
{
	m_pDisplayArea->ActivateDisplay(TRUE);
}

void CMainWnd::OnPreviousWindow()
{
	m_pDisplayArea->ActivateDisplay(FALSE);
}

void CMainWnd::OnCloseWindow()
{
	m_pDisplayArea->CloseDisplay();
}

void CMainWnd::OnCloseAllWindows()
{
	m_pDisplayArea->CloseDisplays();
}

void CMainWnd::OnLock()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = GetActiveDisplay()))
	{
		pDisplayWnd->DoProtect();
	}
}

void CMainWnd::OnAssistantSupportDateConversions()
{
	CAssistantSupportDateConversionsDialog  cDateConversionDialog(this);

	cDateConversionDialog.DoModal();
}

void CMainWnd::OnAssistantListen()
{
}

void CMainWnd::OnStatusBarTelemetryStatus()
{
	m_wndStatusBar.ShowPane(ID_STATUSBAR_TELEMETRYPANE, !m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_TELEMETRYPANE));
}

void CMainWnd::OnStatusBarTelecommandStatus()
{
	m_wndStatusBar.ShowPane(ID_STATUSBAR_TELECOMMANDPANE, !m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_TELECOMMANDPANE));
}

void CMainWnd::OnStatusBarArchivingStatus()
{
	m_wndStatusBar.ShowPane(ID_STATUSBAR_ARCHIVINGPANE, !m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_ARCHIVINGPANE));
}

void CMainWnd::OnStatusBarCPUPerformanceStatus()
{
	m_wndStatusBar.ShowPane(ID_STATUSBAR_CPUPERFORMANCEPANE, !m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_CPUPERFORMANCEPANE));
}

void CMainWnd::OnStatusBarClock()
{
	m_wndStatusBar.ShowPane(ID_STATUSBAR_CLOCKPANE, !m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_CLOCKPANE));
}

void CMainWnd::OnStatusBarHelp()
{
	ShowHelp(STRING(IDS_ONLINEHELP_STATUSBARPANES_TOPIC));
}

void CMainWnd::OnMenuID(UINT nID)
{
#ifdef SATELLITETRACKING

	CSatelliteTrackingToolWnd  *pSatelliteTrackingToolWnd;

	if (nID >= MINSPACEENGINEMENUID && nID <= MAXSPACEENGINEMENUID)
	{
		if ((pSatelliteTrackingToolWnd = (CSatelliteTrackingToolWnd *)GetGlobalDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)))
		{
			pSatelliteTrackingToolWnd->OnMenuID(nID);
		}
	}

#endif
}

void CMainWnd::OnAbout()
{
	CHourglassCursor  cCursor;

	m_dlgAbout.DoModal();
}

void CMainWnd::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowHelp();
}

void CMainWnd::OnClose()
{
	INT  nPage;
	INT  nPages;
	INT  nDisplay;
	INT  nDisplays;
	UINT  nAreaType;
	CPtrArray  pDisplays;
	CStringArray  szPages;
	CDisplayWnd  *pDisplayWnd;
	CDisplayArea  *pDisplayArea;
	CHourglassCursor  cCursor;

	for (SwitchOperatingMode(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_STANDBY), FALSE), SaveConfigurationData(); StopAccount(); )
	{
		for (nPage = 0, nPages = ((nAreaType = (pDisplayArea = GetDisplayArea()) ? pDisplayArea->GetType() : 0) == DISPLAYAREA_TYPE_FOLDER) ? GetDisplayArea()->EnumPages(szPages) : 0, StopCLCWPanel(), StopAssistant(), ShowWindow(SW_HIDE), ShowOwnedPopups(FALSE), SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); nPage < nPages || (!nPage && nAreaType == DISPLAYAREA_TYPE_STANDARD); nPage++)
		{
			for (nDisplay = 0, nDisplays = (nAreaType == DISPLAYAREA_TYPE_FOLDER) ? GetDisplayArea()->EnumDisplays(nPage, pDisplays) : GetDisplayArea()->EnumDisplays(pDisplays); nDisplay < nDisplays; nDisplay++)
			{
				if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)))
				{
					pDisplayWnd->DestroyWindow();
					continue;
				}
			}
		}
		CLocaleMDIFrameWnd::OnClose();
		break;
	}
}

void CMainWnd::OnDestroy()
{
	CUIntArray  nPaneIDs;
	WINDOWPLACEMENT  wndPlacement;
	CProfile  cProfile;

	for (ZeroMemory(&wndPlacement, sizeof(WINDOWPLACEMENT)), wndPlacement.length = sizeof(WINDOWPLACEMENT); GetWindowPlacement(&wndPlacement); )
	{
		cProfile.SetPosition(&wndPlacement.rcNormalPosition);
		cProfile.SetState(wndPlacement.showCmd);
		break;
	}
	if (IsWindow(m_wndStatusBar.GetSafeHwnd()))
	{
		m_wndStatusBar.GetIndicators(nPaneIDs);
		cProfile.SetStatusBarState(nPaneIDs);
	}
	delete m_pLogoWnd;
	m_pLogoWnd = (CLogoWnd *)NULL;
	CLocaleMDIFrameWnd::OnDestroy();
}

void CMainWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_DISPLAYAREA_BROWSE) || CheckAccountPrivilege(PRIVILEGE_DISPLAYAREA_CHANGE) || CheckAccountPrivilege(PRIVILEGE_EVENTLOGS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_EVENTLOGS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_EVENTLOGS_REMOTEBROWSE) || CheckAccountPrivilege(PRIVILEGE_EVENTLOGS_REMOTECHANGE) || CheckAccountPrivilege(PRIVILEGE_EVENTLOGNAME_CHANGE) || CheckAccountPrivilege(PRIVILEGE_EVENTLOGPOLICY_CHANGE) || CheckAccountPrivilege(PRIVILEGE_EVENTLOGSIZE_CHANGE) || CheckAccountPrivilege(PRIVILEGE_PRINTPROFILES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_PRINTPROFILES_CHANGE) || CheckAccountPrivilege(PRIVILEGE_AUDITIONPROFILES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_AUDITIONPROFILES_CHANGE) || CheckAccountPrivilege(PRIVILEGE_NOTIFICATIONPROFILES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_NOTIFICATIONPROFILES_CHANGE) || CheckAccountPrivilege(PRIVILEGE_MISCELLANEOUS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_MISCELLANEOUS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CMainWnd::OnUpdateAccounts(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_REMOTEBROWSE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_REMOTECHANGE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTRIGHTS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTPASSWORD_CHANGE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTVALIDITY_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgUserAccounts.GetSafeHwnd()));
}

void CMainWnd::OnUpdateAccountPrivileges(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_ACCOUNTRIGHTS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgUserPrivileges.GetSafeHwnd()));
}

void CMainWnd::OnUpdateAccountChange(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount());
	pCmdUI->SetCheck(IsWindow(m_dlgAccountChange.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryEquipment(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TELEMETRYSERVICE_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYSERVICE_CHANGE)) && CheckDisplays());
}

void CMainWnd::OnUpdateTelemetrySettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetTMService()->HasTMProviderDevices(TRUE) && (CheckAccountPrivilege(PRIVILEGE_TELEMETRYSERVICE_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYSERVICE_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryService.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelecommandEquipment(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TELECOMMANDSERVICE_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELECOMMANDSERVICE_CHANGE)) && CheckDisplays());
}

void CMainWnd::OnUpdateTelecommandSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetTCService()->HasTCUplinkDevices(TRUE) && (CheckAccountPrivilege(PRIVILEGE_TELECOMMANDSERVICE_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELECOMMANDSERVICE_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelecommandService.GetSafeHwnd()));
}

void CMainWnd::OnUpdateSimulatorsEquipment(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateSimulatorsSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateSCOEsEquipment(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateSCOEsSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateSystemAlerts(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_SYSTEMALERTS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_SYSTEMALERTS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgSystemAlerts.GetSafeHwnd()));
}

void CMainWnd::OnUpdateAutomationService(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_AUTOMATIONSERVICE_BROWSE) || CheckAccountPrivilege(PRIVILEGE_AUTOMATIONSERVICE_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgAutomationService.GetSafeHwnd()));
}

void CMainWnd::OnUpdateMemoryDumpSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetMemoryDumpsService()->IsAvailable() && (CheckAccountPrivilege(PRIVILEGE_MEMORYDUMPS_SETUPVIEW) || CheckAccountPrivilege(PRIVILEGE_MEMORYDUMPS_SETUPCHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgMemoryDumpsService.GetSafeHwnd()));
}

void CMainWnd::OnUpdateMemoryDumpImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetMemoryDumpsService()->IsAvailable() && CheckAccountPrivilege(PRIVILEGE_MEMORYDUMPS_IMPORT) && CheckDisplays());
}

void CMainWnd::OnUpdateMemoryDumpExport(CCmdUI *pCmdUI)
{
	CMemoryDumps  pDumps;

	pCmdUI->Enable(TestAccount() && GetMemoryDumpsService()->IsAvailable() && GetMemoryDumpsService()->GetMemoryDumps(pDumps) && pDumps.GetSize() > 0 && CheckAccountPrivilege(PRIVILEGE_MEMORYDUMPS_EXPORT) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgMemoryDumpsExport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryEventsSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TELEMETRYEVENTS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYEVENTS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryEvents.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryEventsImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_TELEMETRYEVENTS_IMPORT) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryEventsImport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryEventsExport(CCmdUI *pCmdUI)
{
	CTelemetryEvents  pEvents;

	pCmdUI->Enable(TestAccount() && GetTelemetryEvents(pEvents) && pEvents.GetSize() > 0 && CheckAccountPrivilege(PRIVILEGE_TELEMETRYEVENTS_EXPORT) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryEventsExport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryReportsSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TELEMETRYREPORTS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYREPORTS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryReports.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryReportsRetrievals(CCmdUI *pCmdUI)
{
	CTelemetryReports  pReports;

	pCmdUI->Enable(TestAccount() && GetTelemetryReports(pReports) && pReports.GetSize() > 0 && (CheckAccountPrivilege(PRIVILEGE_TELEMETRYREPORTS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYREPORTS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryReportsRetrievals.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryReportsImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_TELEMETRYREPORTS_IMPORT) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryReportsImport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryReportsExport(CCmdUI *pCmdUI)
{
	CTelemetryReports  pReports;

	pCmdUI->Enable(TestAccount() && GetTelemetryReports(pReports) && pReports.GetSize() > 0 && CheckAccountPrivilege(PRIVILEGE_TELEMETRYREPORTS_EXPORT) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryReportsExport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryParameters(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TELEMETRYPARAMETERS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYPARAMETERS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryParameters.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryArchivesSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESARCHIVALS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESARCHIVALS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESBACKUPS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESBACKUPS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESTOOLS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESTOOLS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryArchives.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryArchivesExtractionsImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_CHANGE) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryArchivesExtractionsImport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelemetryArchivesExtractionsExport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_CHANGE) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelemetryArchivesExtractionsExport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_AND_USE) && CheckDisplays());
}

void CMainWnd::OnUpdateGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_GRD_USE) && CheckDisplays());
}

void CMainWnd::OnUpdateHEX(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_HEX_USE) && CheckDisplays());
}

void CMainWnd::OnUpdateOOL(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_OOL_USE) && CheckDisplays());
}

void CMainWnd::OnUpdateMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_MMD_USE) && CheckDisplays());
}

void CMainWnd::OnUpdatePOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_POD_USE) && CheckDisplays());
}

void CMainWnd::OnUpdateSatelliteTrackingTool(CCmdUI *pCmdUI)
{
	CSatelliteTrackingToolWnd  *pSatelliteTrackingToolWnd;

	if ((pSatelliteTrackingToolWnd = (CSatelliteTrackingToolWnd *)GetGlobalDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)))
	{
		pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_SATELLITETRACKINGTOOL_USE) && CheckDisplays() && pSatelliteTrackingToolWnd->IsEnabled());
		pCmdUI->SetCheck(pSatelliteTrackingToolWnd->IsWindowVisible());
		return;
	}
	pCmdUI->Enable(FALSE);
	pCmdUI->SetCheck(FALSE);
}

void CMainWnd::OnUpdateEventBox(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_EVENTBOX_USE) && CheckDisplays());
}

void CMainWnd::OnUpdateMailBox(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_MAILBOX_USE) && CheckDisplays() && FALSE);
}

void CMainWnd::OnUpdateLogBook(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_LOGBOOK_USE) && CheckDisplays() && FALSE);
}

void CMainWnd::OnUpdateANDImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_AND_IMPORT) && CheckDisplays());
}

void CMainWnd::OnUpdateGRDImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_GRD_IMPORT) && CheckDisplays());
}

void CMainWnd::OnUpdatePODImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && CheckAccountPrivilege(PRIVILEGE_POD_IMPORT) && CheckDisplays());
}

void CMainWnd::OnUpdateANDExport(CCmdUI *pCmdUI)
{
	CANDLayouts  pLayouts;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && EnumTemporaryANDs(pLayouts) > 0 && CheckAccountPrivilege(PRIVILEGE_AND_EXPORT) && CheckDisplays());
}

void CMainWnd::OnUpdateGRDExport(CCmdUI *pCmdUI)
{
	CGRDLayouts  pLayouts;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && EnumTemporaryGRDs(pLayouts) > 0 && CheckAccountPrivilege(PRIVILEGE_GRD_EXPORT) && CheckDisplays());
}

void CMainWnd::OnUpdatePODExport(CCmdUI *pCmdUI)
{
	CPODLayouts  pLayouts;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && EnumTemporaryPODs(pLayouts) > 0 && CheckAccountPrivilege(PRIVILEGE_POD_EXPORT) && CheckDisplays());
}

void CMainWnd::OnUpdateTCManualStack(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TCMANUALSTACK_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCMANUALSTACK_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCMANUALSTACK)) && pDisplayWnd->IsWindowVisible()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateTCAutomaticStack(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TCAUTOMATICSTACK_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCAUTOMATICSTACK_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK)) && pDisplayWnd->IsWindowVisible()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateTCProceduresMonitor(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR)) && pDisplayWnd->IsWindowVisible()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateTCDiagnosticsOversamplingDump(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE)) && CheckDisplays());
}

void CMainWnd::OnUpdateTCOnBoardBufferQueues(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TCONBOARDSOFTWARESERVICES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCONBOARDSOFTWARESERVICES_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES)) && pDisplayWnd->IsWindowVisible()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateTCOnBoardMemoryImages(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TCONBOARDSOFTWARESERVICES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCONBOARDSOFTWARESERVICES_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(((pDisplayWnd = GetGlobalDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)) && pDisplayWnd->IsWindowVisible()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateTCHistory(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TCHISTORY_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCHISTORY_CHANGE)) && CheckDisplays());
}

void CMainWnd::OnUpdateTelecommandParameters(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && GetDatabase()->IsInitialized() && (CheckAccountPrivilege(PRIVILEGE_TELECOMMANDPARAMETERS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELECOMMANDPARAMETERS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelecommandParameters.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTelecommandOptions(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TELECOMMANDOPTIONS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TELECOMMANDOPTIONS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgTelecommandOptions.GetSafeHwnd()));
}

void CMainWnd::OnUpdatePFLPService(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_PFLP_SETUPVIEW) || CheckAccountPrivilege(PRIVILEGE_PFLP_SETUPCHANGE)) && CheckDisplays() && GetPFLPService()->IsAvailable());
	pCmdUI->SetCheck(IsWindow(m_dlgPFLPService.GetSafeHwnd()));
}

void CMainWnd::OnUpdatePFLPClients(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_PFLP_CLIENTSVIEW) || CheckAccountPrivilege(PRIVILEGE_PFLP_CLIENTSCHANGE)) && CheckDisplays() && GetPFLPService()->IsAvailable() && GetPFLPService()->HasConnections());
	pCmdUI->SetCheck(IsWindow(m_dlgPFLPClients.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTPEPService(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TPEP_SETUPVIEW) || CheckAccountPrivilege(PRIVILEGE_TPEP_SETUPCHANGE)) && CheckDisplays() && GetTPEPService()->IsAvailable());
	pCmdUI->SetCheck(IsWindow(m_dlgTPEPService.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTPEPConnect(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_TPEP_CONNECT) && CheckDisplays() && GetTPEPService()->IsAvailable());
	pCmdUI->SetCheck(IsWindow(m_dlgTPEPConnect.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTPEPClients(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TPEP_CLIENTSVIEW) || CheckAccountPrivilege(PRIVILEGE_TPEP_CLIENTSCHANGE)) && CheckDisplays() && GetTPEPService()->IsAvailable() && (GetTPEPService()->HasClientConnections() || GetTPEPService()->HasServerConnections()));
	pCmdUI->SetCheck(IsWindow(m_dlgTPEPClients.GetSafeHwnd()));
}

void CMainWnd::OnUpdateTPEPView(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_TPEP_VIEW) && CheckDisplays() && GetTPEPService()->IsAvailable() && (GetTPEPService()->HasClientConnections() || GetTPEPService()->HasServerConnections()));
}

void CMainWnd::OnUpdateServerAddressBook(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_SERVERADDRESSBOOK_BROWSE) || CheckAccountPrivilege(PRIVILEGE_SERVERADDRESSBOOK_CHANGE) || CheckAccountPrivilege(PRIVILEGE_SERVERADDRESSBOOK_REMOTEBROWSE) || CheckAccountPrivilege(PRIVILEGE_SERVERADDRESSBOOK_REMOTECHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgServerAddressBook.GetSafeHwnd()));
}

void CMainWnd::OnUpdateUserAddressBook(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_USERADDRESSBOOK_BROWSE) || CheckAccountPrivilege(PRIVILEGE_USERADDRESSBOOK_CHANGE) || CheckAccountPrivilege(PRIVILEGE_USERADDRESSBOOK_REMOTEBROWSE) || CheckAccountPrivilege(PRIVILEGE_USERADDRESSBOOK_REMOTECHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgUserAddressBook.GetSafeHwnd()));
}

void CMainWnd::OnUpdateToolsDownloads(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TOOLSDOWNLOADPROFILES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TOOLSDOWNLOADPROFILES_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgToolsDownloads.GetSafeHwnd()));
}

void CMainWnd::OnUpdateToolsOptions(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && (CheckAccountPrivilege(PRIVILEGE_TOOLSDATABASEOPTIONS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TOOLSDATABASEOPTIONS_CHANGE) || CheckAccountPrivilege(PRIVILEGE_TOOLSEMAILOPTIONS_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TOOLSEMAILOPTIONS_CHANGE)) && CheckDisplays());
	pCmdUI->SetCheck(IsWindow(m_dlgToolsOptions.GetSafeHwnd()));
}

void CMainWnd::OnUpdatePrintSetup(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckAccountPrivilege(PRIVILEGE_PRINTER_CHANGE) && CheckDisplays() && IsDefaultPrinterAvailable());
	pCmdUI->SetCheck(IsWindow(m_dlgPrintPageSetup.GetSafeHwnd()));
}

void CMainWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (TestAccount() && CheckAccountPrivilege(PRIVILEGE_PRINTER_CHANGE) && CheckDisplays() && IsDefaultPrinterAvailable()) ? GetActiveDisplay() : (CDisplayWnd *)NULL)) ? pDisplayWnd->CanPrint() : FALSE);
}

void CMainWnd::OnUpdatePrintServerAddressBook(CCmdUI *pCmdUI)
{
	CServerAddressBook  cServerAddressBook;

	pCmdUI->Enable(TestAccount() && !cServerAddressBook.IsEmpty() && CheckDisplays());
}

void CMainWnd::OnUpdatePrintUserAddressBook(CCmdUI *pCmdUI)
{
	CUserAddressBook  cUserAddressBook;

	pCmdUI->Enable(TestAccount() && !cUserAddressBook.IsEmpty() && CheckDisplays());
}

void CMainWnd::OnUpdateDisplayReduceFonts(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable((pDisplayWnd = (TestAccount() && CheckDisplays()) ? GetActiveDisplay() : (CDisplayWnd *)NULL) && pDisplayWnd->CanReduceFonts(FALSE));
}

void CMainWnd::OnUpdateDisplayRestoreFonts(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable((pDisplayWnd = (TestAccount() && CheckDisplays()) ? GetActiveDisplay() : (CDisplayWnd *)NULL) && pDisplayWnd->CanReduceFonts(TRUE));
}

void CMainWnd::OnUpdateWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMainWnd::OnUpdateNextWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays())) ? TRUE : FALSE);
}

void CMainWnd::OnUpdatePreviousWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays())) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateCloseWindow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays())) ? GetActiveDisplay() : (CDisplayWnd *)NULL)) ? !pDisplayWnd->IsProtected() : FALSE);
}

void CMainWnd::OnUpdateCascadeWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays()));
}

void CMainWnd::OnUpdateTileHorzWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays()));
}

void CMainWnd::OnUpdateTileVertWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays()));
}

void CMainWnd::OnUpdateArrangeWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays()));
}

void CMainWnd::OnUpdateCloseAllWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays()));
}

void CMainWnd::OnUpdateLock(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (TestAccount() && CheckDisplays() && HIWORD(m_pDisplayArea->QueryDisplays())) ? GetActiveDisplay() : (CDisplayWnd *)NULL)) ? pDisplayWnd->CanProtect() : FALSE);
}

void CMainWnd::OnUpdateDisplayPages(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays());
}

void CMainWnd::OnUpdateDisplayWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays() && LOWORD(m_pDisplayArea->QueryDisplays()));
}

void CMainWnd::OnUpdateDisplayWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && CheckDisplays() && LOWORD(m_pDisplayArea->QueryDisplays()));
	pCmdUI->SetCheck(m_pDisplayArea->IsActiveDisplay(pCmdUI->m_nID - IDM_FIRSTDISPLAYWINDOW));
}

void CMainWnd::OnUpdateAssistantSupportDateConversions(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMainWnd::OnUpdateAssistantListen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMainWnd::OnUpdateStatusBarTelemetryStatus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((TestAccount()) ? m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_TELEMETRYPANE) : FALSE);
	pCmdUI->SetCheck(m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_TELEMETRYPANE) && m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_TELEMETRYPANE));
}

void CMainWnd::OnUpdateStatusBarTelecommandStatus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((TestAccount()) ? m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_TELECOMMANDPANE) : FALSE);
	pCmdUI->SetCheck(m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_TELECOMMANDPANE) && m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_TELECOMMANDPANE));
}

void CMainWnd::OnUpdateStatusBarArchivingStatus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((TestAccount()) ? m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_ARCHIVINGPANE) : FALSE);
	pCmdUI->SetCheck(m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_ARCHIVINGPANE) && m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_ARCHIVINGPANE));
}

void CMainWnd::OnUpdateStatusBarCPUPerformanceStatus(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((TestAccount()) ? m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_CPUPERFORMANCEPANE) : FALSE);
	pCmdUI->SetCheck(m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_CPUPERFORMANCEPANE) && m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_CPUPERFORMANCEPANE));
}

void CMainWnd::OnUpdateStatusBarClock(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((TestAccount()) ? m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_CLOCKPANE) : FALSE);
	pCmdUI->SetCheck(m_wndStatusBar.IsPaneAvailable(ID_STATUSBAR_CLOCKPANE) && m_wndStatusBar.IsPaneVisible(ID_STATUSBAR_CLOCKPANE));
}

void CMainWnd::OnUpdateStatusBarHelp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount());
}

void CMainWnd::OnUpdateMenuID(CCmdUI *pCmdUI)
{
#ifdef SATELLITETRACKING

	CSatelliteTrackingToolWnd  *pSatelliteTrackingToolWnd;

	if (pCmdUI->m_nID >= MINSPACEENGINEMENUID && pCmdUI->m_nID <= MAXSPACEENGINEMENUID)
	{
		if ((pSatelliteTrackingToolWnd = (CSatelliteTrackingToolWnd *)GetGlobalDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)))
		{
			pSatelliteTrackingToolWnd->OnUpdateMenuID(pCmdUI);
		}
	}

#endif
}

void CMainWnd::OnUpdateAbout(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount());
}

void CMainWnd::OnUpdateHelp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount() && IsHelpAvailable());
}

void CMainWnd::OnUpdateExit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!TestAccount() || !CheckDisplays() || CheckAccountPrivilege(PRIVILEGE_EXIT));
}


/////////////////////////////////////////////////////////////////////////////
// CDesktopAppCommandLineInfo

CDesktopAppCommandLineInfo::CDesktopAppCommandLineInfo() : CCommandLineInfo()
{
	m_bSpacecraft = FALSE;
	m_bDatabase = FALSE;
	m_bPassword = FALSE;
	m_bUser = FALSE;
}

CString CDesktopAppCommandLineInfo::GetSpacecraft() CONST
{
	return m_cAccountToken.GetSpacecraftName();
}

CString CDesktopAppCommandLineInfo::GetDatabase() CONST
{
	return m_cAccountToken.GetDatabase();
}

CString CDesktopAppCommandLineInfo::GetPassword() CONST
{
	return m_cAccountToken.GetPassword();
}

CString CDesktopAppCommandLineInfo::GetUser() CONST
{
	return m_cAccountToken.GetUserName();
}

BOOL CDesktopAppCommandLineInfo::IsValid() CONST
{
	return !m_cAccountToken.GetSpacecraftName().IsEmpty() && !m_cAccountToken.GetUserName().IsEmpty() && !m_cAccountToken.GetDatabase().IsEmpty();
}

void CDesktopAppCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast)
{
	INT  nPos;
	CString  szUser;
	CString  szFlag[2];
	CString  szDatabase;
	CString  szPassword;
	CString  szSpacecraft;

	for (szFlag[0] = pszParam, szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_SPACECRAFT); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szSpacecraft = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szSpacecraft.IsEmpty() && szSpacecraft.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szSpacecraft = szSpacecraft.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bSpacecraft = TRUE;
			break;
		}
		if (!szSpacecraft.IsEmpty() && szSpacecraft.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bSpacecraft)
		{
			szSpacecraft = szSpacecraft.Left(szSpacecraft.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bSpacecraft = FALSE;
		}
		m_cAccountToken.SetSpacecraftName(szSpacecraft);
		m_bUser = m_bDatabase = m_bPassword = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_USER); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szUser = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szUser.IsEmpty() && szUser.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szUser = szUser.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bUser = TRUE;
			break;
		}
		if (!szUser.IsEmpty() && szUser.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bUser)
		{
			szUser = szUser.Left(szUser.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bUser = FALSE;
		}
		m_cAccountToken.SetUserName(szUser);
		m_bSpacecraft = m_bDatabase = m_bPassword = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_DATABASE); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szDatabase = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szDatabase.IsEmpty() && szDatabase.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szDatabase = szDatabase.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bDatabase = TRUE;
			break;
		}
		if (!szDatabase.IsEmpty() && szDatabase.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bDatabase)
		{
			szDatabase = szDatabase.Left(szDatabase.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bDatabase = FALSE;
		}
		m_cAccountToken.SetDatabase(szDatabase);
		m_bSpacecraft = m_bUser = m_bPassword = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_PASSWORD); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szPassword = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szPassword.IsEmpty() && szPassword.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szPassword = szPassword.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bPassword = TRUE;
			break;
		}
		if (!szPassword.IsEmpty() && szPassword.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bPassword)
		{
			szPassword = szPassword.Left(szPassword.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bPassword = FALSE;
		}
		m_cAccountToken.SetPassword(szPassword);
		m_bSpacecraft = m_bUser = m_bDatabase = FALSE;
		return;
	}
	if (szFlag[0].GetLength() > lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)) && szFlag[0].Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))
	{
		m_cAccountToken.SetSpacecraftName((m_bSpacecraft) ? (m_cAccountToken.GetSpacecraftName() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetSpacecraftName());
		m_cAccountToken.SetUserName((m_bUser) ? (m_cAccountToken.GetUserName() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetUserName());
		m_cAccountToken.SetDatabase((m_bDatabase) ? (m_cAccountToken.GetDatabase() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetDatabase());
		m_cAccountToken.SetPassword((m_bPassword) ? (m_cAccountToken.GetPassword() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetPassword());
		m_bSpacecraft = m_bUser = m_bDatabase = m_bPassword = FALSE;
	}
	CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}


/////////////////////////////////////////////////////////////////////////////
// CDesktopApp

IMPLEMENT_DYNAMIC(CDesktopApp, CAccountsApp)

CDesktopApp::CDesktopApp() : CAccountsApp(), CThread()
{
	m_pDatabase = new CDatabaseEngine;
	m_pTMService = new CTMService;
	m_pTCService = new CTCService;
	m_pRASService = new CRASService;
	m_pPFLPService = new CPFLPService;
	m_pTPEPService = new CTPEPService;
	m_pAutomationService = new CAutomationService;
	m_pMemoryDumpsService = new CMemoryDumpsService;
	m_pTelemetryReportsService = new CTelemetryReportsService;
	m_pNotificationService = new CNotificationService;
	m_pToolsDatabaseService = new CToolsDatabaseService;
	m_pToolsDownloadService = new CToolsDownloadService;
	m_pNetworkBrowseService = new CNetworkBrowseService;
	m_pPFLPServiceEngine = new CPFLPServiceEngine;
	m_pTPEPServiceEngine = new CTPEPServiceEngine;
	m_pMemoryDumpsServiceEngine = new CMemoryDumpsServiceEngine;
	m_pArchivesExtractionProfiles = new CArchivesExtractionProfiles;
	m_pToolsDownloadProfiles = new CToolsDownloadProfiles;
	m_pNotificationProfiles = new CNotificationProfiles;
	m_pAuditionProfiles = new CAuditionProfiles;
	m_pPrintProfiles = new CPrintProfiles;
	m_pSystemAlerts = new CSystemAlerts;
	m_pTelemetryEvents = new CTelemetryEvents;
	m_pTelemetryReports = new CTelemetryReports;
	m_pTelemetryHistoricalReports = new CTelemetryHistoricalReports;
	m_pEMailSystem = new CEMailSystem;
	m_pLoginInfo = new CLoginInfo;
	m_pLoginOptions = new CLoginOptions;
	m_pLoginAccount = new CAccountToken;
	m_pLoginServerInfo = new CServerProfileInfo;
	m_hLoginMutex = (HANDLE)NULL;
	m_bOperatingMode = FALSE;
	m_bTMService = FALSE;
	m_bTCService = FALSE;
	m_nTimerID[0] = 0;
	m_nTimerID[1] = 0;
	m_nTimerID[2] = 0;
	m_nWaitID = 0;
	m_nExitID = 0;
	CAccountsApp::m_pMainWnd = (CMainWnd *)NULL;
}

CDesktopApp::~CDesktopApp()
{
	delete m_pDatabase;
	delete m_pTMService;
	delete m_pTCService;
	delete m_pRASService;
	delete m_pPFLPService;
	delete m_pTPEPService;
	delete m_pAutomationService;
	delete m_pMemoryDumpsService;
	delete m_pTelemetryReportsService;
	delete m_pNotificationService;
	delete m_pToolsDatabaseService;
	delete m_pToolsDownloadService;
	delete m_pNetworkBrowseService;
	delete m_pPFLPServiceEngine;
	delete m_pTPEPServiceEngine;
	delete m_pMemoryDumpsServiceEngine;
	delete m_pArchivesExtractionProfiles;
	delete m_pToolsDownloadProfiles;
	delete m_pNotificationProfiles;
	delete m_pAuditionProfiles;
	delete m_pPrintProfiles;
	delete m_pSystemAlerts;
	delete m_pTelemetryEvents;
	delete m_pTelemetryReports;
	delete m_pTelemetryHistoricalReports;
	delete m_pEMailSystem;
	delete m_pLoginInfo;
	delete m_pLoginOptions;
	delete m_pLoginAccount;
	delete m_pLoginServerInfo;
}

BOOL CDesktopApp::InitInstance()
{
	INT  nResultCode;
	CMainWnd  *pMainWnd;
	CEventLog  cEventLog;
	CStringArray  szLogs;
	CVersionInfo  cVersionInfo;
	CDesktopAppCommandLineInfo  cStartupInfo;
	CHourglassCursor  cCursor;

	if (CAccountsApp::InitInstance())
	{
		if ((nResultCode = RegisterApp()) > 0)
		{
			if ((CAccountsApp::m_pMainWnd = pMainWnd = new CMainWnd) && pMainWnd->Create())
			{
				for (ParseCommandLine(cStartupInfo), ValidateAccounts(), LoadAccount(); StartAccount(cStartupInfo); )
				{
					StartServices();
					return TRUE;
				}
				pMainWnd->DestroyWindow();
				CAccountsApp::m_pMainWnd = (CWnd *)NULL;
				return FALSE;
			}
		}
		if (nResultCode >= 0)
		{
			szLogs.Add(cVersionInfo.QueryComments());
			szLogs.Add(cVersionInfo.QueryLegalCopyright());
			cEventLog.Report(SYSTEM_CRITICAL_INITIALIZATION_FAILURE, szLogs);
		}
		CAccountsApp::m_pMainWnd = (CWnd *)NULL;
	}
	return FALSE;
}

int CDesktopApp::ExitInstance()
{
	CHourglassCursor  cCursor;

	StopServices();
	UnregisterApp();
	return CAccountsApp::ExitInstance();
}

BOOL CDesktopApp::StartAccount()
{
	CDesktopAppCommandLineInfo  cStartupInfo;

	return StartAccount(cStartupInfo);
}
BOOL CDesktopApp::StartAccount(CONST CDesktopAppCommandLineInfo &cStartupInfo)
{
	HANDLE  hMutex;
	CString  szMessage;
	CLoginDialog  cLoginDialog;
	CAccountToken  cAccountToken;

	for (GetMainWnd()->UpdateLayout(); cStartupInfo.IsValid(); )
	{
		for (ShowWaitCursor(); EvaluateAccount(cStartupInfo, &cAccountToken); )
		{
			for (hMutex = (HANDLE)NULL; !cAccountToken.IsUnique() || ((hMutex = CreateMutex((LPSECURITY_ATTRIBUTES)NULL, FALSE, STRING(IDS_MUTEXTYPE_GLOBALPREFIX) + cAccountToken.GetSpacecraftName() + TAB + cAccountToken.GetUserName())) && GetLastError() != ERROR_ALREADY_EXISTS); )
			{
				StartAccount(&cAccountToken);
				SetLoginData(hMutex);
				StopWaitCursor();
				return TRUE;
			}
			if (hMutex != (HANDLE)NULL) CloseHandle(hMutex);
			break;
		}
		StopWaitCursor();
		return FALSE;
	}
	for (Wait(GetLogo(), FALSE); cLoginDialog.DoModal() == IDOK; )
	{
		for (ShowWaitCursor(), GetAccount(&cAccountToken); cAccountToken.HasOwner(); )
		{
			for (hMutex = (HANDLE)NULL; !cAccountToken.IsUnique() || ((hMutex = CreateMutex((LPSECURITY_ATTRIBUTES)NULL, FALSE, STRING(IDS_MUTEXTYPE_GLOBALPREFIX) + cAccountToken.GetSpacecraftName() + TAB + cAccountToken.GetUserName())) && GetLastError() != ERROR_ALREADY_EXISTS); )
			{
				StartAccount(&cAccountToken);
				SetLoginData(hMutex);
				StopWaitCursor();
				return TRUE;
			}
			for (StopWaitCursor(), szMessage.Format(STRING(IDS_APPLICATIONINFO_LAUNCHMESSAGE_DENIEDACCOUNT), (LPCTSTR)GetAccountUserName()); hMutex != (HANDLE)NULL; )
			{
				CloseHandle(hMutex);
				break;
			}
			AfxMessageBox(szMessage, MB_ICONINFORMATION);
			return FALSE;
		}
		StopWaitCursor();
		break;
	}
	return FALSE;
}
BOOL CDesktopApp::StartAccount(CAccountToken *pAccountToken)
{
	CAccountToken  cAccountToken;

	for (GetAccount(&cAccountToken); TestAccount() && !IsAccountActivated() && CompareAccount(pAccountToken); )
	{
		if (ActivateAccount(&cAccountToken))
		{
			if (LoadSpacecraftLibrary())
			{
				if (LoadLayout())
				{
					LoadDatabase();
					LoadDisplays();
					LoadUser();
					StartTMService();
					StartTCService();
					StartDisplays();
					LoginTMService();
				}
				else
				{
					ResetAccount(SYSTEM_WARNING_SPACECRAFT_PROFILE_LOAD_FAILURE);
					return FALSE;
				}
			}
			else
			{
				ResetAccount(SYSTEM_WARNING_SPACECRAFT_LOAD_FAILURE);
				return FALSE;
			}
		}
		else
		{
			ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
			return FALSE;
		}
		ShowAccountStatus();
		return TRUE;
	}
	if (StopAccount(pAccountToken))
	{
		if (TestAccount() && CompareAccount(pAccountToken))
		{
			if (CompareAccountDatabase(pAccountToken))
			{
				if (CompareAccountServer(pAccountToken))
				{
					if (CompareAccountMode(pAccountToken))
					{
						if (!ActivateAccount(pAccountToken))
						{
							ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
							return FALSE;
						}
					}
					else
					{
						if (!ActivateAccount(pAccountToken))
						{
							ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
							return FALSE;
						}
						UpdateTMService();
					}
				}
				else
				{
					if (!ActivateAccount(pAccountToken))
					{
						ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
						return FALSE;
					}
					LoginTMService();
				}
			}
			else
			{
				if (CompareAccountServer(pAccountToken))
				{
					if (!ActivateAccount(pAccountToken))
					{
						ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
						return FALSE;
					}
					LoadLayout();
					LoadDatabase();
					LoadDisplays();
					StartTMService();
					StartTCService();
					StartDisplays();
				}
				else
				{
					if (!ActivateAccount(pAccountToken))
					{
						ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
						return FALSE;
					}
					LoadLayout();
					LoadDatabase();
					LoadDisplays();
					StartTMService();
					StartTCService();
					StartDisplays();
					LoginTMService();
				}
			}
			ShowAccountStatus();
			return TRUE;
		}
		if (!CompareAccountSpacecraft(pAccountToken))
		{
			if (CompareAccountServer(pAccountToken))
			{
				if (!ActivateAccount(pAccountToken))
				{
					ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
					return FALSE;
				}
				if (LoadSpacecraftLibrary())
				{
					if (LoadLayout())
					{
						LoadDatabase();
						LoadDisplays();
						LoadUser();
						StartTMService();
						StartTCService();
						StartDisplays();
					}
					else
					{
						ResetAccount(SYSTEM_WARNING_SPACECRAFT_PROFILE_LOAD_FAILURE);
						return FALSE;
					}
				}
				else
				{
					ResetAccount(SYSTEM_WARNING_SPACECRAFT_LOAD_FAILURE);
					return FALSE;
				}
			}
			else
			{
				if (!ActivateAccount(pAccountToken))
				{
					ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
					return FALSE;
				}
				if (LoadSpacecraftLibrary())
				{
					if (LoadLayout())
					{
						LoadDatabase();
						LoadDisplays();
						LoadUser();
						StartTMService();
						StartTCService();
						StartDisplays();
						LoginTMService();
					}
					else
					{
						ResetAccount(SYSTEM_WARNING_SPACECRAFT_PROFILE_LOAD_FAILURE);
						return FALSE;
					}
				}
				else
				{
					ResetAccount(SYSTEM_WARNING_SPACECRAFT_LOAD_FAILURE);
					return FALSE;
				}
			}
			ShowAccountStatus();
			return TRUE;
		}
		if (!CompareAccountUser(pAccountToken))
		{
			if (CompareAccountDatabase(pAccountToken))
			{
				if (CompareAccountServer(pAccountToken))
				{
					if (CompareAccountMode(pAccountToken))
					{
						if (!ActivateAccount(pAccountToken))
						{
							ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
							return FALSE;
						}
						LoadLayout();
						LoadDisplays();
						LoadUser();
						StartTMService();
						StartTCService();
						StartDisplays();
					}
					else
					{
						if (!ActivateAccount(pAccountToken))
						{
							ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
							return FALSE;
						}
						LoadLayout();
						LoadDisplays();
						LoadUser();
						StartTMService();
						StartTCService();
						StartDisplays();
						UpdateTMService();
					}
				}
				else
				{
					if (!ActivateAccount(pAccountToken))
					{
						ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
						return FALSE;
					}
					LoadLayout();
					LoadDisplays();
					LoadUser();
					StartTMService();
					StartTCService();
					StartDisplays();
					LoginTMService();
				}
			}
			else
			{
				if (CompareAccountServer(pAccountToken))
				{
					if (!ActivateAccount(pAccountToken))
					{
						ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
						return FALSE;
					}
					LoadLayout();
					LoadDatabase();
					LoadDisplays();
					LoadUser();
					StartTMService();
					StartTCService();
					StartDisplays();
				}
				else
				{
					if (!ActivateAccount(pAccountToken))
					{
						ResetAccount(SYSTEM_WARNING_ACCOUNT_INITIALIZATION_FAILURE);
						return FALSE;
					}
					LoadLayout();
					LoadDatabase();
					LoadDisplays();
					LoadUser();
					StartTMService();
					StartTCService();
					StartDisplays();
					LoginTMService();
				}
			}
			ShowAccountStatus();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::StopAccount(CAccountToken *pAccountToken)
{
	EVENT_DESCRIPTOR  sEvent;

	if (TestAccount())
	{
		if (CompareAccount(pAccountToken))
		{
			if (CompareAccountDatabase(pAccountToken))
			{
				if (CompareAccountServer(pAccountToken))
				{
					if (CompareAccountMode(pAccountToken))
					{
						if (!pAccountToken)
						{
							if (!TestAccountStatus(sEvent))
							{
								ReportEvent(sEvent);
								return FALSE;
							}
							StopDisplays();
							StopTCService();
							StopTMService();
							LogoutTMService();
							FreeUser(Exit);
							FreeDisplays(Exit);
							FreeDatabase(Exit);
							FreeLayout(Exit);
							FreeSpacecraftLibrary(Exit);
						}
					}
				}
				else  LogoutTMService();
			}
			else
			{
				if (!TestAccountStatus(sEvent))
				{
					ReportEvent(sEvent);
					return FALSE;
				}
				if (CompareAccountServer(pAccountToken))
				{
					StopDisplays();
					StopTCService();
					StopTMService();
				}
				else
				{
					StopDisplays();
					StopTCService();
					StopTMService();
					LogoutTMService();
				}
				FreeDisplays(ChangeDatabase);
				FreeDatabase(ChangeDatabase);
				FreeLayout(ChangeDatabase);
			}
			return TRUE;
		}
		if (!CompareAccountSpacecraft(pAccountToken))
		{
			if (!TestAccountStatus(sEvent))
			{
				ReportEvent(sEvent);
				return FALSE;
			}
			if (CompareAccountServer(pAccountToken))
			{
				StopDisplays();
				StopTCService();
				StopTMService();
			}
			else
			{
				StopDisplays();
				StopTCService();
				StopTMService();
				LogoutTMService();
			}
			FreeUser(ChangeDatabase);
			FreeDisplays(ChangeDatabase);
			FreeDatabase(ChangeDatabase);
			FreeLayout(ChangeDatabase);
			FreeSpacecraftLibrary(ChangeDatabase);
			return TRUE;
		}
		if (!CompareAccountUser(pAccountToken))
		{
			if (CompareAccountDatabase(pAccountToken))
			{
				if (CompareAccountServer(pAccountToken))
				{
					StopDisplays();
					StopTCService();
					StopTMService();
					FreeUser(ChangeUser);
					FreeDisplays(ChangeUser);
					FreeLayout(ChangeUser);
					return TRUE;
				}
				StopDisplays();
				StopTCService();
				StopTMService();
				LogoutTMService();
				FreeUser(ChangeUser);
				FreeDisplays(ChangeUser);
				FreeLayout(ChangeUser);
			}
			else
			{
				if (!TestAccountStatus(sEvent))
				{
					ReportEvent(sEvent);
					return FALSE;
				}
				if (CompareAccountServer(pAccountToken))
				{
					StopDisplays();
					StopTCService();
					StopTMService();
				}
				else
				{
					StopDisplays();
					StopTCService();
					StopTMService();
					LogoutTMService();
				}
				FreeUser(ChangeDatabase);
				FreeDisplays(ChangeDatabase);
				FreeDatabase(ChangeDatabase);
				FreeLayout(ChangeDatabase);
				FreeSpacecraftLibrary(ChangeDatabase);
			}
		}
	}
	return TRUE;
}

BOOL CDesktopApp::ReloadAccount(UINT nCode)
{
	if (nCode == ChangeArea)
	{
		for (GetTMService()->UpdateTMDisplays(FALSE), GetTCService()->UpdateTCDisplays(FALSE), StopDisplays(), FreeDisplays(nCode), FreeLayout(nCode); LoadLayout(); )
		{
			LoadDisplays();
			StartDisplays();
			GetTMService()->UpdateTMDisplays(TRUE);
			GetTCService()->UpdateTCDisplays(TRUE);
			ShowAccountStatus();
			return TRUE;
		}
	}
	if (nCode == ReloadDatabase)
	{
		for (StopDisplays(), StopTCService(), StopTMService(), FreeDisplays(nCode), FreeDatabase(nCode), FreeLayout(ReloadDatabase); LoadLayout() && LoadDatabase(); )
		{
			LoadDisplays();
			StartTMService();
			StartTCService();
			StartDisplays();
			ShowAccountStatus();
			return TRUE;
		}
		ResetAccount(SYSTEM_NOERROR);
	}
	return FALSE;
}

VOID CDesktopApp::ResetAccount(CONST EVENT_DESCRIPTOR sEvent)
{
	ReportEvent(sEvent);
	SetLoginData();
	StopDisplays();
	StopTCService();
	StopTMService();
	LogoutTMService();
	FreeUser(Reset);
	FreeDisplays(Reset);
	FreeDatabase(Reset);
	FreeLayout(Reset);
	FreeSpacecraftLibrary(Reset);
	ValidateAccount(FALSE);
	ShowAccountStatus();
}

BOOL CDesktopApp::ValidateAccounts()
{
	INT  nSubKey;
	INT  nSubKeys;
	INT  nAccount;
	INT  nAccounts;
	CString  szSubKey;
	CString  szFileName;
	CEventLog  cEventLog;
	CFileFindEx  cFileFind;
	CStringArray  szSubKeys;
	CVersionInfo  cVersionInfo;
	CUserAccounts  cUserAccounts;
	CAccountToken  *pAccountToken;
	CAccountTokens  pAccountTokens;
	CProfile  cProfile;

	for (nAccount = 0, nAccounts = cUserAccounts.EnumAccounts(pAccountTokens, TRUE); nAccount < nAccounts; nAccount++)
	{
		for (cUserAccounts.RemoveAccount((pAccountToken = pAccountTokens.GetAt(nAccount))); cEventLog.SetOwner(pAccountToken); )
		{
			if (cEventLog.QueryUserLogFileName(szFileName) && cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile())
			{
				DeleteFile(cFileFind.GetFilePath());
				RemoveDirectory(cFileFind.GetRoot());
				cFileFind.Close();
			}
			break;
		}
	}
	for (nSubKey = 0, nSubKeys = cProfile.EnumUserSubKeys((szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + cVersionInfo.QueryProductName() + cVersionInfo.QueryFileDescription().Mid(cVersionInfo.QueryInternalName().GetLength())), szSubKeys); nSubKey < nSubKeys; nSubKey++)
	{
		for (nAccount = 0, nAccounts = cUserAccounts.EnumAccounts(pAccountTokens); nAccount < nAccounts; nAccount++)
		{
			if ((pAccountToken = pAccountTokens.GetAt(nAccount)) && pAccountToken->GetUserName() == szSubKeys.GetAt(nSubKey)) break;
			continue;
		}
		if (nAccount == nAccounts) cProfile.DeleteSubKey(szSubKey + STRING(IDS_REG_SUBKEYPART_DELIMITER) + szSubKeys.GetAt(nSubKey));
		pAccountTokens.RemoveAll();
	}
	if (!cUserAccounts.EnumAccounts())
	{
		cUserAccounts.DeleteAccounts();
		cProfile.DeleteAllInfo();
		return FALSE;
	}
	return TRUE;
}

VOID CDesktopApp::SaveConfigurationData()
{
	ReportEvent((!SaveLoginOptions()) ? SYSTEM_WARNING_LOGINOPTIONS_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SaveSystemAlerts()) ? SYSTEM_WARNING_SYSTEMALERTS_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SaveTelemetryEvents()) ? SYSTEM_WARNING_TELEMETRYEVENTS_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SaveTelemetryReports() || !SaveTelemetryHistoricalReports()) ? SYSTEM_WARNING_TELEMETRYREPORTS_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SavePrintProfiles()) ? SYSTEM_WARNING_PRINTPROFILES_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SaveAuditionProfiles()) ? SYSTEM_WARNING_AUDITIONPROFILES_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SaveNotificationProfiles()) ? SYSTEM_WARNING_NOTIFICATIONPROFILES_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SaveToolsDownloadProfiles()) ? SYSTEM_WARNING_TOOLSDOWNLOADPROFILES_SAVE_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!SaveToolsEMailSettings()) ? SYSTEM_WARNING_TOOLSEMAILSETTINGS_SAVE_FAILURE : SYSTEM_NOERROR);
}

VOID CDesktopApp::LoadConfigurationData()
{
	ReportEvent((!LoadLoginOptions()) ? SYSTEM_WARNING_LOGINOPTIONS_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadSystemAlerts()) ? SYSTEM_WARNING_SYSTEMALERTS_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadTelemetryEvents()) ? SYSTEM_WARNING_TELEMETRYEVENTS_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadTelemetryReports() || !LoadTelemetryHistoricalReports()) ? SYSTEM_WARNING_TELEMETRYREPORTS_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadPrintProfiles()) ? SYSTEM_WARNING_PRINTPROFILES_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadAuditionProfiles()) ? SYSTEM_WARNING_AUDITIONPROFILES_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadNotificationProfiles()) ? SYSTEM_WARNING_NOTIFICATIONPROFILES_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadToolsDownloadProfiles()) ? SYSTEM_WARNING_TOOLSDOWNLOADPROFILES_LOAD_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!LoadToolsEMailSettings()) ? SYSTEM_WARNING_TOOLSEMAILSETTINGS_LOAD_FAILURE : SYSTEM_NOERROR);
}

VOID CDesktopApp::SetLoginData(HANDLE hMutex)
{
	if (m_hLoginMutex)
	{
		if (m_hLoginMutex != hMutex)
		{
			CloseHandle(m_hLoginMutex);
			m_hLoginMutex = (HANDLE)NULL;
		}
	}
	m_hLoginMutex = hMutex;
}

HANDLE CDesktopApp::GetLoginData() CONST
{
	return m_hLoginMutex;
}

BOOL CDesktopApp::SetLoginOptions(CONST CLoginOptions &pOptions)
{
	if (m_pLoginOptions->Lock())
	{
		m_pLoginOptions->Copy(&pOptions);
		m_pLoginOptions->Unlock();
		return LoginScheduler();
	}
	return FALSE;
}

BOOL CDesktopApp::GetLoginOptions(CLoginOptions &pOptions) CONST
{
	if (m_pLoginOptions->Lock())
	{
		pOptions.Copy(m_pLoginOptions);
		m_pLoginOptions->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateLoginOptions()
{
	return SaveLoginOptions();
}

BOOL CDesktopApp::SetPrintProfiles(CONST CPrintProfiles &pProfiles)
{
	if (m_pPrintProfiles->Lock())
	{
		m_pPrintProfiles->Copy(&pProfiles);
		m_pPrintProfiles->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::GetPrintProfiles(CPrintProfiles &pProfiles) CONST
{
	if (m_pPrintProfiles->Lock())
	{
		pProfiles.Copy(m_pPrintProfiles);
		m_pPrintProfiles->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::EnumPrintProfiles(CStringArray &szProfiles) CONST
{
	if (m_pPrintProfiles->Lock())
	{
		m_pPrintProfiles->Enum(szProfiles);
		m_pPrintProfiles->Unlock();
		return((szProfiles.GetSize() > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CDesktopApp::UpdatePrintProfiles()
{
	return SavePrintProfiles();
}

BOOL CDesktopApp::SetAuditionProfiles(CONST CAuditionProfiles &pProfiles)
{
	if (m_pAuditionProfiles->Lock())
	{
		m_pAuditionProfiles->Copy(&pProfiles);
		m_pAuditionProfiles->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::GetAuditionProfiles(CAuditionProfiles &pProfiles) CONST
{
	if (m_pAuditionProfiles->Lock())
	{
		pProfiles.Copy(m_pAuditionProfiles);
		m_pAuditionProfiles->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::EnumAuditionProfiles(CStringArray &szProfiles) CONST
{
	if (m_pAuditionProfiles->Lock())
	{
		m_pAuditionProfiles->Enum(szProfiles);
		m_pAuditionProfiles->Unlock();
		return((szProfiles.GetSize() > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateAuditionProfiles()
{
	return SaveAuditionProfiles();
}

BOOL CDesktopApp::SetNotificationProfiles(CONST CNotificationProfiles &pProfiles)
{
	if (m_pNotificationProfiles->Lock())
	{
		m_pNotificationProfiles->Copy(&pProfiles);
		m_pNotificationProfiles->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::GetNotificationProfiles(CNotificationProfiles &pProfiles) CONST
{
	if (m_pNotificationProfiles->Lock())
	{
		pProfiles.Copy(m_pNotificationProfiles);
		m_pNotificationProfiles->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::EnumNotificationProfiles(CStringArray &szProfiles) CONST
{
	if (m_pNotificationProfiles->Lock())
	{
		m_pNotificationProfiles->Enum(szProfiles);
		m_pNotificationProfiles->Unlock();
		return((szProfiles.GetSize() > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateNotificationProfiles()
{
	return SaveNotificationProfiles();
}

BOOL CDesktopApp::DoNotification(LPCTSTR pszProfile, LPCTSTR pszMessage)
{
	CString  szMessage;
	CNotificationProfileInfo  *pProfileInfo;

	if (m_pNotificationProfiles->Lock())
	{
		if ((pProfileInfo = m_pNotificationProfiles->GetAt(m_pNotificationProfiles->Find(pszProfile))))
		{
			if (GetNotificationService()->Update(pProfileInfo, pszMessage))
			{
				m_pNotificationProfiles->Unlock();
				return TRUE;
			}
			szMessage.Format(STRING(IDS_NOTIFICATION_UNEXECUTABLE), pszProfile);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
			m_pNotificationProfiles->Unlock();
			return FALSE;
		}
		if (lstrlen(pszProfile) > 0)
		{
			szMessage.Format(STRING(IDS_NOTIFICATION_UNKNOWN), pszProfile);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		}
		m_pNotificationProfiles->Unlock();
	}
	return FALSE;
}
BOOL CDesktopApp::DoNotification(LPCTSTR pszProfile, LPCTSTR pszMessage, INT nAlertType, CONST CStringArray &szRecipients)
{
	INT  nUser[2];
	INT  nUsers[2];
	CString  szMessage;
	CStringArray  szUsers;
	CNotificationProfileInfo  *pProfileInfo;

	if (m_pNotificationProfiles->Lock())
	{
		if ((pProfileInfo = m_pNotificationProfiles->GetAt(m_pNotificationProfiles->Find(pszProfile))))
		{
			if (pProfileInfo->GetType() == nAlertType  &&  pProfileInfo->GetRecipients(szUsers) == szRecipients.GetSize())
			{
				for (nUser[0] = 0, nUsers[0] = (INT)szRecipients.GetSize(); nUser[0] < nUsers[0]; nUser[0]++)
				{
					for (nUser[1] = 0, nUsers[1] = (INT)szUsers.GetSize(); nUser[1] < nUsers[1]; nUser[1]++)
					{
						if (!szRecipients.GetAt(nUser[0]).CompareNoCase(szUsers.GetAt(nUser[1]))) break;
						continue;
					}
					if (nUser[1] == nUsers[1]) break;
				}
				if (nUser[0] == nUsers[0])
				{
					if (GetNotificationService()->Update(pProfileInfo, pszMessage))
					{
						m_pNotificationProfiles->Unlock();
						return TRUE;
					}
					szMessage.Format(STRING(IDS_NOTIFICATION_UNEXECUTABLE), pszProfile);
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
					m_pNotificationProfiles->Unlock();
					return FALSE;
				}
			}
			if (pProfileInfo->GetType() == nAlertType)
			{
				if (pProfileInfo->GetOptions() == NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING)
				{
					szMessage.Format(STRING(IDS_NOTIFICATION_RECIPIENTS_CHANGED), (LPCTSTR)pszProfile);
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				}
				if (GetNotificationService()->Update(pProfileInfo, pszMessage))
				{
					m_pNotificationProfiles->Unlock();
					return TRUE;
				}
				szMessage.Format(STRING(IDS_NOTIFICATION_UNEXECUTABLE), pszProfile);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
				m_pNotificationProfiles->Unlock();
				return FALSE;
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				szMessage.Format(STRING(IDS_NOTIFICATION_UNEXECUTABLE), (LPCTSTR)pszProfile);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
			}
			m_pNotificationProfiles->Unlock();
			return FALSE;
		}
		if (lstrlen(pszProfile) > 0)
		{
			szMessage.Format(STRING(IDS_NOTIFICATION_UNKNOWN), pszProfile);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		}
		m_pNotificationProfiles->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::SetSystemAlerts(CONST CSystemAlerts &pAlerts)
{
	if (m_pSystemAlerts->Lock())
	{
		if (m_pSystemAlerts->Copy(&pAlerts))
		{
			GetTMService()->TrackSystemAlerts(pAlerts);
			m_pSystemAlerts->Unlock();
			return TRUE;
		}
		m_pSystemAlerts->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::GetSystemAlerts(CSystemAlerts &pAlerts) CONST
{
	INT  nAlert;
	INT  nAlerts;
	CSystemAlertInfo  *pAlertInfo;

	if (m_pSystemAlerts->Lock())
	{
		for (nAlert = 0, nAlerts = (m_pSystemAlerts->GetSize() != MAXSYSTEMALERTSNAMES - MINSYSTEMALERTSNAMES + 1) ? (MAXSYSTEMALERTSNAMES - MINSYSTEMALERTSNAMES) : 0; nAlert <= nAlerts; nAlert++)
		{
			if ((pAlertInfo = new CSystemAlertInfo))
			{
				pAlertInfo->SetName(STRING(MINSYSTEMALERTSNAMES + nAlert));
				pAlertInfo->SetMessage(STRING(MINSYSTEMALERTSMESSAGES + nAlert));
				pAlertInfo->SetDescription(STRING(MINSYSTEMALERTSDESCRIPTIONS + nAlert));
				if (m_pSystemAlerts->Find(pAlertInfo->GetName()) < 0 && m_pSystemAlerts->Add(pAlertInfo) >= 0) continue;
				delete pAlertInfo;
			}
		}
		pAlerts.Copy(m_pSystemAlerts);
		m_pSystemAlerts->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateSystemAlerts()
{
	return SaveSystemAlerts();
}

BOOL CDesktopApp::SetTelemetryEvents(CONST CTelemetryEvents &pEvents)
{
	if (m_pTelemetryEvents->Lock())
	{
		if (m_pTelemetryEvents->Copy(&pEvents))
		{
			GetTMService()->TrackTelemetryEvents(pEvents);
			m_pTelemetryEvents->Unlock();
			return TRUE;
		}
		m_pTelemetryEvents->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::GetTelemetryEvents(CTelemetryEvents &pEvents) CONST
{
	if (m_pTelemetryEvents->Lock())
	{
		if (pEvents.Copy(m_pTelemetryEvents))
		{
			m_pTelemetryEvents->Unlock();
			return TRUE;
		}
		m_pTelemetryEvents->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateTelemetryEvents()
{
	return SaveTelemetryEvents();
}

BOOL CDesktopApp::SetTelemetryReports(CONST CTelemetryReports &pReports)
{
	if (m_pTelemetryReports->Lock())
	{
		if (m_pTelemetryReports->Copy(&pReports))
		{
			GetTelemetryReportsService()->Update(pReports);
			m_pTelemetryReports->Unlock();
			return TRUE;
		}
		m_pTelemetryReports->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::GetTelemetryReports(CTelemetryReports &pReports) CONST
{
	if (m_pTelemetryReports->Lock())
	{
		if (pReports.Copy(m_pTelemetryReports))
		{
			GetTelemetryReportsService()->Refresh(pReports);
			m_pTelemetryReports->Unlock();
			return TRUE;
		}
		m_pTelemetryReports->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateTelemetryReports()
{
	return SaveTelemetryReports();
}

BOOL CDesktopApp::SetTelemetryHistoricalReports(CONST CTelemetryHistoricalReports &pHistoricalReports)
{
	if (m_pTelemetryHistoricalReports->Lock())
	{
		m_pTelemetryHistoricalReports->Copy(&pHistoricalReports);
		m_pTelemetryHistoricalReports->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::GetTelemetryHistoricalReports(CTelemetryHistoricalReports &pHistoricalReports) CONST
{
	if (m_pTelemetryHistoricalReports->Lock())
	{
		pHistoricalReports.Copy(m_pTelemetryHistoricalReports);
		m_pTelemetryHistoricalReports->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateTelemetryHistoricalReports()
{
	return SaveTelemetryHistoricalReports();
}

BOOL CDesktopApp::DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo)
{
	CTimeTag  tMessage;
	CAutomationScript  *pScript;
	CAutomationScripts  pScripts;

	if ((pReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_DISABLED) != TELEMETRYREPORTINFO_OPTION_DISABLED)
	{
		if ((pScript = (GetDatabase()->EnumScripts(pScripts) > 0) ? pScripts.GetAt(pScripts.Find(pReportInfo->GetScript())) : (CAutomationScript *)NULL))
		{
			for (pScript->SetInputFileName(pReportInfo->GetInputFileName()), pScript->SetOutputFileName(pReportInfo->GetOutputFileName()); m_cScriptsExecutor.Run(pReportInfo->GetName(), pScript, EMPTYSTRING, EMPTYSTRING, EMPTYSTRING, EMPTYSTRING, tMessage); ) return TRUE;
			return FALSE;
		}
		return m_cScriptsExecutor.Run(pReportInfo->GetName(), pReportInfo->GetOutputFileName(), tMessage.FormatGmt() + CR + EOL);
	}
	return TRUE;
}
BOOL CDesktopApp::DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo, CONST CSystemAlertInfo *pAlertInfo)
{
	CTimeTag  tMessage;
	CAutomationScript  *pScript;
	CAutomationScripts  pScripts;

	if ((pReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_DISABLED) != TELEMETRYREPORTINFO_OPTION_DISABLED)
	{
		if ((pScript = (GetDatabase()->EnumScripts(pScripts) > 0) ? pScripts.GetAt(pScripts.Find(pReportInfo->GetScript())) : (CAutomationScript *)NULL))
		{
			for (pScript->SetInputFileName(pReportInfo->GetInputFileName()), pScript->SetOutputFileName(pReportInfo->GetOutputFileName()); m_cScriptsExecutor.Run(pReportInfo->GetName(), pScript, pAlertInfo->GetName(), EMPTYSTRING, pAlertInfo->GetMessage(), pAlertInfo->GetExtraInfo(), (pAlertInfo->GetTime() > 0) ? pAlertInfo->GetTime() : tMessage); ) return TRUE;
			return FALSE;
		}
		return m_cScriptsExecutor.Run(pReportInfo->GetName(), pReportInfo->GetOutputFileName(), (pAlertInfo->GetTime() > 0) ? (pAlertInfo->GetTime().FormatGmt() + TAB + pAlertInfo->GetMessage() + CR + EOL) : (tMessage.FormatGmt() + TAB + pAlertInfo->GetMessage() + CR + EOL));
	}
	return TRUE;
}
BOOL CDesktopApp::DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo, CONST CTelemetryEventInfo *pEventInfo)
{
	CTimeTag  tMessage;
	CAutomationScript  *pScript;
	CAutomationScripts  pScripts;

	if ((pReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_DISABLED) != TELEMETRYREPORTINFO_OPTION_DISABLED)
	{
		if ((pScript = (GetDatabase()->EnumScripts(pScripts) > 0) ? pScripts.GetAt(pScripts.Find(pReportInfo->GetScript())) : (CAutomationScript *)NULL))
		{
			for (pScript->SetInputFileName(pReportInfo->GetInputFileName()), pScript->SetOutputFileName(pReportInfo->GetOutputFileName()); m_cScriptsExecutor.Run(pReportInfo->GetName(), pScript, EMPTYSTRING, pEventInfo->GetName(), pEventInfo->GetMessage(), EMPTYSTRING, (pEventInfo->GetTime() > 0) ? pEventInfo->GetTime() : tMessage); ) return TRUE;
			return FALSE;
		}
		return m_cScriptsExecutor.Run(pReportInfo->GetName(), pReportInfo->GetOutputFileName(), (pEventInfo->GetTime() > 0) ? (pEventInfo->GetTime().FormatGmt() + TAB + pEventInfo->GetMessage() + CR + EOL) : (tMessage.FormatGmt() + TAB + pEventInfo->GetMessage() + CR + EOL));
	}
	return TRUE;
}

BOOL CDesktopApp::SetToolsDownloadProfiles(CONST CToolsDownloadProfiles &pProfiles)
{
	if (m_pToolsDownloadProfiles->Lock())
	{
		if (m_pToolsDownloadProfiles->Copy(&pProfiles))
		{
			GetToolsDownloadService()->Update(pProfiles);
			m_pToolsDownloadProfiles->Unlock();
			return TRUE;
		}
		m_pToolsDownloadProfiles->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::GetToolsDownloadProfiles(CToolsDownloadProfiles &pProfiles) CONST
{
	if (m_pToolsDownloadProfiles->Lock())
	{
		if (pProfiles.Copy(m_pToolsDownloadProfiles))
		{
			GetToolsDownloadService()->Refresh(pProfiles);
			m_pToolsDownloadProfiles->Unlock();
			return TRUE;
		}
		m_pToolsDownloadProfiles->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::EnumToolsDownloadProfiles(CStringArray &szProfiles) CONST
{
	if (m_pToolsDownloadProfiles->Lock())
	{
		m_pToolsDownloadProfiles->Enum(szProfiles);
		m_pToolsDownloadProfiles->Unlock();
		return((szProfiles.GetSize() > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CDesktopApp::UpdateToolsDownloadProfiles()
{
	return SaveToolsDownloadProfiles();
}

BOOL CDesktopApp::SaveTemporaryDisplays()
{
	CByteArray  nANDs;
	CByteArray  nGRDs;
	CByteArray  nPODs;
	CByteArray  nDisplays;
	CProfile  cProfile;

	if (!SaveTemporaryANDs(nANDs) || !cProfile.SetDisplayAreaTemporaryANDs(nANDs))
	{
		cProfile.SetDisplayAreaTemporaryANDs(nDisplays);
		return FALSE;
	}
	if (!SaveTemporaryGRDs(nGRDs) || !cProfile.SetDisplayAreaTemporaryGRDs(nGRDs))
	{
		cProfile.SetDisplayAreaTemporaryGRDs(nDisplays);
		return FALSE;
	}
	if (!SaveTemporaryPODs(nPODs) || !cProfile.SetDisplayAreaTemporaryPODs(nPODs))
	{
		cProfile.SetDisplayAreaTemporaryPODs(nDisplays);
		return FALSE;
	}
	return TRUE;
}

BOOL CDesktopApp::LoadTemporaryDisplays()
{
	CByteArray  nANDs;
	CByteArray  nGRDs;
	CByteArray  nPODs;
	CProfile  cProfile;

	return((cProfile.GetDisplayAreaTemporaryANDs(nANDs) && LoadTemporaryANDs(nANDs) && cProfile.GetDisplayAreaTemporaryGRDs(nGRDs) && LoadTemporaryGRDs(nGRDs) && cProfile.GetDisplayAreaTemporaryPODs(nPODs) && LoadTemporaryPODs(nPODs)) ? TRUE : FALSE);
}

BOOL CDesktopApp::AddTemporaryAND(LPCTSTR pszName, CONST CANDLayout &cLayout)
{
	CANDLayout  *pLayout;

	if ((pLayout = m_pTemporaryANDs.GetAt(m_pTemporaryANDs.Find(pszName))))
	{
		if (pLayout->Copy(&cLayout)) return TRUE;
		return FALSE;
	}
	if ((pLayout = new CANDLayout))
	{
		if (pLayout->Copy(&cLayout) && m_pTemporaryANDs.Add(pLayout) >= 0) return TRUE;
		delete pLayout;
	}
	return FALSE;
}

BOOL CDesktopApp::AddTemporaryGRD(LPCTSTR pszName, CONST CGRDLayout &cLayout)
{
	CGRDLayout  *pLayout;

	if ((pLayout = m_pTemporaryGRDs.GetAt(m_pTemporaryGRDs.Find(pszName))))
	{
		if (pLayout->Copy(&cLayout)) return TRUE;
		return FALSE;
	}
	if ((pLayout = new CGRDLayout))
	{
		if (pLayout->Copy(&cLayout) && m_pTemporaryGRDs.Add(pLayout) >= 0) return TRUE;
		delete pLayout;
	}
	return FALSE;
}

BOOL CDesktopApp::AddTemporaryPOD(LPCTSTR pszName, CONST CPODLayout &cLayout)
{
	CPODLayout  *pLayout;

	if ((pLayout = m_pTemporaryPODs.GetAt(m_pTemporaryPODs.Find(pszName))))
	{
		if (pLayout->Copy(&cLayout)) return TRUE;
		return FALSE;
	}
	if ((pLayout = new CPODLayout))
	{
		if (pLayout->Copy(&cLayout) && m_pTemporaryPODs.Add(pLayout) >= 0) return TRUE;
		delete pLayout;
	}
	return FALSE;
}

BOOL CDesktopApp::LoadTemporaryAND(LPCTSTR pszName, CANDLayout &cLayout) CONST
{
	CANDLayout  *pLayout;

	return((pLayout = m_pTemporaryANDs.GetAt(m_pTemporaryANDs.Find(pszName))) ? cLayout.Copy(pLayout) : FALSE);
}

BOOL CDesktopApp::LoadTemporaryGRD(LPCTSTR pszName, CGRDLayout &cLayout) CONST
{
	CGRDLayout  *pLayout;

	return((pLayout = m_pTemporaryGRDs.GetAt(m_pTemporaryGRDs.Find(pszName))) ? cLayout.Copy(pLayout) : FALSE);
}

BOOL CDesktopApp::LoadTemporaryPOD(LPCTSTR pszName, CPODLayout &cLayout) CONST
{
	CPODLayout  *pLayout;

	return(((pLayout = m_pTemporaryPODs.GetAt(m_pTemporaryPODs.Find(pszName)))) ? cLayout.Copy(pLayout) : FALSE);
}

INT CDesktopApp::EnumTemporaryANDs(CANDLayouts &pLayouts) CONST
{
	INT  nLayout;
	INT  nLayouts;
	INT  nParameter;
	INT  nParameters;
	CANDLayout  *pLayout;
	CANDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nLayout = 0, nLayouts = (INT)m_pTemporaryANDs.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = new CANDLayout) && pLayout->Copy(m_pTemporaryANDs.GetAt(nLayout)))
		{
			for (nParameter = 0, nParameters = (INT)pLayout->GetSize(); nParameter < nParameters; nParameter++)
			{
				if ((pDatabaseTMParameter = ((pParameter = pLayout->GetAt(nParameter)) && !pParameter->IsLabel() && !pParameter->GetDigits()) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName())) : (CDatabaseTMParameter *)NULL) && pDatabaseTMParameter->GetDecimalDigits() > 0)
				{
					pParameter->SetDigits(pDatabaseTMParameter->GetDecimalDigits());
					continue;
				}
			}
			if (pLayouts.Add(pLayout) >= 0) continue;
		}
		delete pLayout;
	}
	return((INT)pLayouts.GetSize());
}

INT CDesktopApp::EnumTemporaryGRDs(CGRDLayouts &pLayouts) CONST
{
	INT  nLayout;
	INT  nLayouts;
	INT  nParameter;
	INT  nParameters;
	CGRDLayout  *pLayout;
	CGRDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nLayout = 0, nLayouts = (INT)m_pTemporaryGRDs.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = new CGRDLayout) && pLayout->Copy(m_pTemporaryGRDs.GetAt(nLayout)))
		{
			for (nParameter = 0, nParameters = (INT)pLayout->GetSize(); nParameter < nParameters; nParameter++)
			{
				if ((pDatabaseTMParameter = ((pParameter = pLayout->GetAt(nParameter)) && !pParameter->GetDigits()) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName())) : (CDatabaseTMParameter *)NULL) && pDatabaseTMParameter->GetDecimalDigits() > 0)
				{
					pParameter->SetDigits(pDatabaseTMParameter->GetDecimalDigits());
					continue;
				}
			}
			if (pLayouts.Add(pLayout) >= 0) continue;
		}
		delete pLayout;
	}
	return((INT)pLayouts.GetSize());
}

INT CDesktopApp::EnumTemporaryPODs(CPODLayouts &pLayouts) CONST
{
	INT  nLayout;
	INT  nLayouts;
	CPODLayout  *pLayout;

	for (nLayout = 0, nLayouts = (INT)m_pTemporaryPODs.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = new CPODLayout) && pLayout->Copy(m_pTemporaryPODs.GetAt(nLayout)) && pLayouts.Add(pLayout) >= 0) continue;
		delete pLayout;
	}
	return((INT)pLayouts.GetSize());
}

BOOL CDesktopApp::RemoveTemporaryAND(LPCTSTR pszName)
{
	INT  nLayout;

	if ((nLayout = m_pTemporaryANDs.Find(pszName)) >= 0)
	{
		delete m_pTemporaryANDs.GetAt(nLayout);
		m_pTemporaryANDs.RemoveAt(nLayout);
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::RemoveTemporaryGRD(LPCTSTR pszName)
{
	INT  nLayout;

	if ((nLayout = m_pTemporaryGRDs.Find(pszName)) >= 0)
	{
		delete m_pTemporaryGRDs.GetAt(nLayout);
		m_pTemporaryGRDs.RemoveAt(nLayout);
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::RemoveTemporaryPOD(LPCTSTR pszName)
{
	INT  nLayout;

	if ((nLayout = m_pTemporaryPODs.Find(pszName)) >= 0)
	{
		delete m_pTemporaryPODs.GetAt(nLayout);
		m_pTemporaryPODs.RemoveAt(nLayout);
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData)
{
	return GetTMService()->InitializeTMUnit(cTMUnit, bBadData);
}
BOOL CDesktopApp::InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData)
{
	return GetTMService()->InitializeTMUnit(pszTag, cTMUnit, bBadData);
}

BOOL CDesktopApp::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return GetTMService()->InitializeTMData(pTMParameters, bBadData);
}
BOOL CDesktopApp::InitializeTMData(COolParameters &pOolParameters, BOOL bBadData)
{
	return GetTMService()->InitializeTMData(pOolParameters, bBadData);
}

BOOL CDesktopApp::InitializeTMDump(CMemoryDump &pDump, BOOL bBadData)
{
	return GetTMService()->InitializeTMDump(pDump, bBadData);
}

BOOL CDesktopApp::UpdateTMParameters(CONST CTMParameters &pTMParameters)
{
	return GetTMService()->UpdateTMParameters(pTMParameters);
}

VOID CDesktopApp::UpdateNetworkStatus()
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateNetworkStatus();
}
VOID CDesktopApp::UpdateNetworkStatus(LPCTSTR pszServer, RASCONNSTATE nState)
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateNetworkStatus(pszServer, nState);
}

VOID CDesktopApp::UpdateTelemetryStatus()
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateTelemetryStatus();
}
VOID CDesktopApp::UpdateTelemetryStatus(CONST CTMProviderDevice *pDevice)
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateTelemetryStatus(pDevice);
}

VOID CDesktopApp::UpdateTelecommandStatus()
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateTelecommandStatus();
}
VOID CDesktopApp::UpdateTelecommandStatus(CONST CTCUplinkDevice *pDevice)
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateTelecommandStatus(pDevice);
}

VOID CDesktopApp::UpdateArchivingStatus()
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateArchivingStatus();
}
VOID CDesktopApp::UpdateArchivingStatus(LPCTSTR pszArchiveFile, UINT nArchiveFreeSpace, BOOL bArchiveStatus, LPCTSTR pszBackupDirectory, UINT nBackupFreeSpace, BOOL bBackupStatus)
{
	CMainWnd  *pMainWnd;

	if ((pMainWnd = GetMainWnd())) pMainWnd->UpdateArchivingStatus(pszArchiveFile, nArchiveFreeSpace, bArchiveStatus, pszBackupDirectory, nBackupFreeSpace, bBackupStatus);
}

BOOL CDesktopApp::InitializeDefaultPrinter()
{
	return m_cDefaultPrinter.Initialize();
}

BOOL CDesktopApp::IsDefaultPrinterAvailable() CONST
{
	return m_cDefaultPrinter.IsAvailable();
}

BOOL CDesktopApp::SetDefaultPrinterInfo(CONST PAGESETUPDLG *pPrinterInfo)
{
	INT  nIndex;
	CPrintProfileInfo  *pProfileInfo;

	if (m_pPrintProfiles->Lock())
	{
		if ((nIndex = m_pPrintProfiles->Find(STRING(IDS_PRINTPROFILE_DEFAULTNAME))) >= 0)
		{
			if ((pProfileInfo = m_pPrintProfiles->GetAt(nIndex)) && pProfileInfo->SetDeviceInfo(pPrinterInfo->hDevNames, pPrinterInfo->hDevMode))
			{
				pProfileInfo->SetPaperInfo(CSize(pPrinterInfo->ptPaperSize.x, pPrinterInfo->ptPaperSize.y), pPrinterInfo->rtMargin, pPrinterInfo->rtMinMargin, (pPrinterInfo->Flags & PSD_INHUNDREDTHSOFMILLIMETERS) ? TRUE : FALSE);
				m_pPrintProfiles->Unlock();
				return TRUE;
			}
			delete m_pPrintProfiles->GetAt(nIndex);
			m_pPrintProfiles->RemoveAt(nIndex);
		}
		if ((pProfileInfo = new CPrintProfileInfo))
		{
			pProfileInfo->SetName(STRING(IDS_PRINTPROFILE_DEFAULTNAME));
			pProfileInfo->SetDeviceInfo(pPrinterInfo->hDevNames, pPrinterInfo->hDevMode);
			pProfileInfo->SetPaperInfo(CSize(pPrinterInfo->ptPaperSize.x, pPrinterInfo->ptPaperSize.y), pPrinterInfo->rtMargin, pPrinterInfo->rtMinMargin, (pPrinterInfo->Flags & PSD_INHUNDREDTHSOFMILLIMETERS) ? TRUE : FALSE);
			m_pPrintProfiles->Add(pProfileInfo);
			m_pPrintProfiles->Unlock();
			return TRUE;
		}
		m_pPrintProfiles->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::GetDefaultPrinterInfo(PAGESETUPDLG *pPrinterInfo) CONST
{
	INT  nIndex;
	BOOL  bMetric;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	HANDLE  hDevMode;
	HANDLE  hDevNames;
	CPrintProfileInfo  *pProfileInfo;

	if (m_pPrintProfiles->Lock())
	{
		if ((nIndex = m_pPrintProfiles->Find(STRING(IDS_PRINTPROFILE_DEFAULTNAME))) >= 0)
		{
			if ((pProfileInfo = m_pPrintProfiles->GetAt(nIndex)) && pProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric) && pProfileInfo->GetDeviceInfo(hDevNames, hDevMode))
			{
				pPrinterInfo->ptPaperSize.x = ptPaperSize.cx;
				pPrinterInfo->ptPaperSize.y = ptPaperSize.cy;
				CopyMemory(&pPrinterInfo->rtMargin, &rtMargin[0], sizeof(RECT));
				CopyMemory(&pPrinterInfo->rtMinMargin, &rtMargin[1], sizeof(RECT));
				pPrinterInfo->Flags |= (bMetric) ? (PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS | PSD_NOWARNING) : (PSD_MARGINS | PSD_INTHOUSANDTHSOFINCHES | PSD_NOWARNING);
				pPrinterInfo->hDevNames = hDevNames;
				pPrinterInfo->hDevMode = hDevMode;
				m_pPrintProfiles->Unlock();
				return TRUE;
			}
		}
		pPrinterInfo->Flags = (pPrinterInfo->Flags | PSD_NOWARNING) & ~(PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS | PSD_INTHOUSANDTHSOFINCHES);
		m_pPrintProfiles->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::CreatePrinterDC(CDC &cDC)
{
	return CreatePrinterDC(STRING(IDS_PRINTPROFILE_DEFAULTNAME), cDC);
}
BOOL CDesktopApp::CreatePrinterDC(LPCTSTR pszProfile, CDC &cDC)
{
	CPrintProfileInfo  *pProfileInfo;

	if (m_pPrintProfiles->Lock())
	{
		if ((pProfileInfo = m_pPrintProfiles->GetAt(m_pPrintProfiles->Find(pszProfile))))
		{
			if (CreatePrinterDC(pProfileInfo, cDC))
			{
				m_pPrintProfiles->Unlock();
				return TRUE;
			}
		}
		m_pPrintProfiles->Unlock();
	}
	return FALSE;
}
BOOL CDesktopApp::CreatePrinterDC(CONST CPrintProfileInfo *pProfileInfo, CDC &cDC)
{
	HANDLE  hDevMode;
	HANDLE  hDevNames;

	if (pProfileInfo->GetDeviceInfo(hDevNames, hDevMode))
	{
		if (CreatePrinterDC(hDevNames, hDevMode, cDC))
		{
			GlobalFree(hDevNames);
			GlobalFree(hDevMode);
			return TRUE;
		}
		GlobalFree(hDevNames);
		GlobalFree(hDevMode);
	}
	return FALSE;
}
BOOL CDesktopApp::CreatePrinterDC(HANDLE hDevNames, HANDLE hDevMode, CDC &cDC)
{
	HDC  hDC;

	if ((hDC = AfxCreateDC(hDevNames, hDevMode)))
	{
		for (cDC.DeleteDC(); !cDC.Attach(hDC); )
		{
			DeleteDC(hDC);
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CDesktopApp::LoginTMService()
{
	INT  nServer;
	INT  nServers;
	CString  szServer;
	CServerProfiles  pServers;
	CServerProfileInfo  *pServerInfo;
	CServerAddressBook  cServerAddressBook;

	for (szServer = GetAccountRASServer(); !szServer.IsEmpty(); )
	{
		for (nServer = 0, nServers = (cServerAddressBook.GetServerAddressBook(pServers)) ? (INT)pServers.GetSize() : -1; nServer < nServers; nServer++)
		{
			if ((pServerInfo = pServers.GetAt(nServer)) && szServer == pServerInfo->GetName())
			{
				m_pLoginServerInfo->Copy(pServerInfo);
				LoginTMService(pServerInfo);
				return;
			}
		}
		for (nServer = 0; nServer < nServers; nServer++)
		{
			if ((pServerInfo = pServers.GetAt(nServer)) && szServer == pServerInfo->GetName() + TAB)
			{
				m_pLoginServerInfo->Copy(pServerInfo);
				LoginTMService(pServerInfo);
				return;
			}
		}
		ReportEvent(SYSTEM_WARNING_REMOTENETWORK_LOGIN_FAILURE);
		break;
	}
}
VOID CDesktopApp::LoginTMService(CONST CServerProfileInfo *pServerInfo)
{
	CString  szNumber;
	CString  szServer[2];
	CString  szMessage[2];
	CString  szDeviceName;
	CString  szDeviceType;
	RASENTRY  sConnectionEntry;
	RASDIALPARAMS  sConnectionInfo;
	RASDIALEXTENSIONS  sConnectionExt;
	CStringArray  szNumbers;

	for (szServer[0] = pServerInfo->GetName(), szServer[1].Format(STRING(IDS_RAS_PHONEBOOKENTRY_FORMAT), (LPCTSTR)pServerInfo->GetName()), pServerInfo->GetDeviceInfo(szDeviceName, szDeviceType), szNumber = (pServerInfo->GetMode() & SERVERPROFILE_BEHAVIOR_CALLBACK) ? pServerInfo->GetCallbackNumber() : EMPTYSTRING, ZeroMemory(&sConnectionEntry, sizeof(RASENTRY)), ZeroMemory(&sConnectionInfo, sizeof(sConnectionInfo)), ZeroMemory(&sConnectionExt, sizeof(sConnectionExt)), sConnectionEntry.dwSize = sizeof(sConnectionEntry), sConnectionInfo.dwSize = sizeof(sConnectionInfo), sConnectionExt.dwSize = sizeof(sConnectionExt); pServerInfo->GetPhoneNumbers(szNumbers) > 0; )
	{
		for (sConnectionEntry.dwType = (pServerInfo->GetMode() & SERVERPROFILE_ACCESS_VPN) ? RASET_Vpn : RASET_Phone, sConnectionEntry.dwfOptions = (pServerInfo->GetMode() & SERVERPROFILE_ACCESS_PHONE) ? (RASEO_IpHeaderCompression | RASEO_SwCompression | RASEO_ModemLights | RASEO_SecureLocalFiles | RASEO_SharedPhoneNumbers | RASEO_ShowDialingProgress | RASEO_RequirePAP | RASEO_RequireCHAP | RASEO_RequireMsCHAP2) : (RASEO_IpHeaderCompression | RASEO_SwCompression | RASEO_SecureLocalFiles | RASEO_ShowDialingProgress), sConnectionEntry.dwfOptions2 = (pServerInfo->GetMode() & SERVERPROFILE_ACCESS_VPN) ? (RASEO2_DisableNbtOverIP | RASEO2_ReconnectIfDropped | RASEO2_Internet | RASEO2_SecureFileAndPrint | RASEO2_DontNegotiateMultilink | RASEO2_SharePhoneNumbers) : (RASEO2_SecureFileAndPrint | RASEO2_DontNegotiateMultilink | RASEO2_SharePhoneNumbers), sConnectionEntry.dwVpnStrategy = (pServerInfo->GetMode() & SERVERPROFILE_ACCESS_VPN) ? VS_Default : 0, sConnectionEntry.dwfNetProtocols = RASNP_Ip | RASNP_Ipv6, sConnectionEntry.dwEncryptionType = ET_Optional, sConnectionEntry.dwFramingProtocol = RASFP_Ppp, _tcscpy_s(sConnectionEntry.szLocalPhoneNumber, sizeof(sConnectionEntry.szLocalPhoneNumber) / sizeof(TCHAR), szNumbers.GetAt(szNumbers.GetSize() - szNumbers.GetUpperBound() - 1)), _tcscpy_s(sConnectionEntry.szDeviceName, sizeof(sConnectionEntry.szDeviceName) / sizeof(TCHAR), ((pServerInfo->GetMode() & SERVERPROFILE_ACCESS_VPN) != SERVERPROFILE_ACCESS_VPN) ? szDeviceName : EMPTYSTRING), _tcscpy_s(sConnectionEntry.szDeviceType, sizeof(sConnectionEntry.szDeviceType) / sizeof(TCHAR), szDeviceType), _tcscpy_s(sConnectionInfo.szDomain, sizeof(sConnectionInfo.szDomain) / sizeof(TCHAR), EMPTYSTRING), _tcscpy_s(sConnectionInfo.szEntryName, sizeof(sConnectionInfo.szEntryName) / sizeof(TCHAR), szServer[1]), _tcscpy_s(sConnectionInfo.szCallbackNumber, sizeof(sConnectionInfo.szCallbackNumber) / sizeof(TCHAR), szNumber), _tcscpy_s(sConnectionInfo.szPhoneNumber, sizeof(sConnectionInfo.szPhoneNumber) / sizeof(TCHAR), szNumbers.GetAt(szNumbers.GetSize() - szNumbers.GetUpperBound() - 1)), _tcscpy_s(sConnectionInfo.szUserName, sizeof(sConnectionInfo.szUserName) / sizeof(TCHAR), GetAccountRASUserName()), _tcscpy_s(sConnectionInfo.szPassword, sizeof(sConnectionInfo.szPassword) / sizeof(TCHAR), GetAccountRASPassword()), sConnectionExt.dwfOptions = (pServerInfo->GetMode() & SERVERPROFILE_BEHAVIOR_MODEMSPEAKER) ? (RDEOPT_IgnoreModemSpeaker | RDEOPT_SetModemSpeaker) : RDEOPT_IgnoreModemSpeaker, sConnectionExt.dwfOptions |= (pServerInfo->GetMode() & SERVERPROFILE_BEHAVIOR_SOFTWARECOMPRESSION) ? (RDEOPT_IgnoreSoftwareCompression | RDEOPT_SetSoftwareCompression) : RDEOPT_IgnoreSoftwareCompression, szMessage[0].Format(STRING(IDS_RAS_MESSAGE_DIALINGCALLBACK), (LPCTSTR)szNumbers.GetAt(szNumbers.GetSize() - szNumbers.GetUpperBound() - 1), (LPCTSTR)szNumber), szMessage[1].Format((pServerInfo->GetMode() & SERVERPROFILE_ACCESS_PHONE) ? STRING(IDS_RAS_MESSAGE_DIALINGIN) : STRING(IDS_RAS_MESSAGE_VPNCONNECTING), (LPCTSTR)szNumbers.GetAt(szNumbers.GetSize() - szNumbers.GetUpperBound() - 1)), ShowMessage(((pServerInfo->GetMode() & SERVERPROFILE_BEHAVIOR_CALLBACK) && !szNumber.IsEmpty()) ? szMessage[0] : szMessage[1]), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, ((pServerInfo->GetMode() & SERVERPROFILE_BEHAVIOR_CALLBACK) && !szNumber.IsEmpty()) ? szMessage[0] : szMessage[1], FALSE); GetRASService()->MakeCall(&sConnectionEntry, &sConnectionExt, &sConnectionInfo); )
		{
			if ((m_nTimerID[2] = SetTimer((HWND)NULL, 0, 100 * (SECONDSPERMINUTE / 60), LoginState)) == 0) break;
			return;
		}
		break;
	}
	ReportEvent(SYSTEM_WARNING_REMOTENETWORK_LOGIN_FAILURE);
}

BOOL CDesktopApp::IsLogginginTMService() CONST
{
	return GetRASService()->IsCalling();
}

VOID CDesktopApp::LogoutTMService()
{
	BOOL  bCalling;
	RASCONNSTATE  nState;
	CAccountToken  cAccount;

	if ((nState = GetRASService()->CheckCall()) == RASCS_Connected || nState > RASCS_Disconnected)
	{
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, STRING(IDS_RAS_MESSAGE_LINEDISCONNECTING), FALSE);
		ShowMessage(STRING(IDS_RAS_MESSAGE_LINEDISCONNECTING));
	}
	for (GetAccount(&cAccount); cAccount.SetRASServer(EMPTYSTRING) && cAccount.SetRASUserName(EMPTYSTRING) && cAccount.SetRASPassword(EMPTYSTRING); )
	{
		SetAccount(&cAccount);
		break;
	}
	for (bCalling = FALSE; GetRASService()->IsCalling(); )
	{
		ShowWaitCursor();
		bCalling = TRUE;
		break;
	}
	for (GetRASService()->StopCall(); m_nTimerID[2] != 0; )
	{
		KillTimer((HWND)NULL, m_nTimerID[2]);
		m_nTimerID[2] = 0;
		break;
	}
	if (bCalling)
	{
		StopWaitCursor();
		bCalling = FALSE;
	}
	ShowAccountStatus();
}

BOOL CDesktopApp::StartRASScheduler()
{
	return(((m_nTimerID[0] = SetTimer((HWND)NULL, 0, 0, LoginScheduler)) != 0) ? TRUE : FALSE);
}

BOOL CDesktopApp::ScheduleRASService(RASCONNSTATE nState)
{
	CAccountToken  cAccount;

	if (m_pLoginOptions->Lock())
	{
		if (nState == (RASCONNSTATE)0)
		{
			for (GetRASService()->StopCall(); m_nTimerID[2] != 0; )
			{
				KillTimer((HWND)NULL, m_nTimerID[2]);
				m_nTimerID[2] = 0;
				break;
			}
			for (GetAccount(&cAccount), m_pLoginAccount->Copy(&cAccount); cAccount.SetRASServer(EMPTYSTRING) && cAccount.SetRASUserName(EMPTYSTRING) && cAccount.SetRASPassword(EMPTYSTRING); )
			{
				SetAccount(&cAccount);
				break;
			}
			if (m_pLoginOptions->GetOptions() & LOGIN_OPTION_RECONNECT)
			{
				for (; m_nTimerID[1] != 0; )
				{
					KillTimer((HWND)NULL, m_nTimerID[1]);
					m_nTimerID[1] = 0;
					break;
				}
				m_nTimerID[1] = SetTimer((HWND)NULL, 0, 0, Login);
			}
			m_pLoginOptions->Unlock();
			return TRUE;
		}
		if (nState == RASCS_Connected)
		{
			for (; m_nTimerID[1] != 0; )
			{
				KillTimer((HWND)NULL, m_nTimerID[1]);
				m_nTimerID[1] = 0;
				break;
			}
			m_pLoginOptions->SetRetentionRetries(0);
		}
		m_pLoginOptions->Unlock();
	}
	return FALSE;
}

BOOL CDesktopApp::StopRASScheduler()
{
	if (m_nTimerID[0] > 0) m_nTimerID[0] = (!KillTimer((HWND)NULL, m_nTimerID[0])) ? m_nTimerID[0] : 0;
	if (m_nTimerID[1] > 0) m_nTimerID[1] = (!KillTimer((HWND)NULL, m_nTimerID[1])) ? m_nTimerID[1] : 0;
	if (m_nTimerID[2] > 0) m_nTimerID[2] = (!KillTimer((HWND)NULL, m_nTimerID[2])) ? m_nTimerID[2] : 0;
	return((!m_nTimerID[0] && !m_nTimerID[1] && !m_nTimerID[2]) ? TRUE : FALSE);
}

BOOL CDesktopApp::SwitchOperatingMode(LPCTSTR pszMode, BOOL bReport)
{
	DWORD  dwFlags;
	CString  szMessage;
	CString  szCommandLine;
	STARTUPINFO  sStartupInfo;
	PROCESS_INFORMATION  sProcessInfo;

	for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ACTION_FORMAT), STRING(IDS_AUTOMATIONSERVICE_NAME_OPERATINGMODES_CHANGES)); bReport; )
	{
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		break;
	}
	if (m_szOperatingMode.CompareNoCase(pszMode))
	{
		if (!m_szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_STANDBY)))
		{
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_ACTIVE)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_PASSIVE)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_MAINTENANCE)))
			{
				for (GetTMService()->EnableTestMode(TRUE), GetTCService()->EnableTestMode(TRUE), szCommandLine = STRING(IDS_APPLICATIONINFO_COMMANDLINEARGUMENT_SIMULATOR), szCommandLine += SPACE, szCommandLine += STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_SPACECRAFT) + (STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) + GetAccountSpacecraftName() + STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)), ZeroMemory(&sStartupInfo, sizeof(sStartupInfo)), ZeroMemory(&sProcessInfo, sizeof(sProcessInfo)), sStartupInfo.cb = sizeof(sStartupInfo); CreateProcess((LPCTSTR)NULL, szCommandLine.GetBufferSetLength(szCommandLine.GetLength()), (LPSECURITY_ATTRIBUTES)NULL, (LPSECURITY_ATTRIBUTES)NULL, FALSE, 0, (LPVOID)NULL, (LPCTSTR)NULL, &sStartupInfo, &sProcessInfo); )
				{
					for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
					{
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
						break;
					}
					m_bOperatingMode = TRUE;
					return TRUE;
				}
				GetTMService()->EnableTestMode(FALSE);
				GetTCService()->EnableTestMode(FALSE);
			}
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_FINAL)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				GetMainWnd()->PostMessage(WM_CLOSE);
				return TRUE;
			}
		}
		if (!m_szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_ACTIVE)))
		{
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_STANDBY)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_PASSIVE)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
		}
		if (!m_szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_PASSIVE)))
		{
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_STANDBY)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_ACTIVE)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
		}
		if (!m_szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_MAINTENANCE)))
		{
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_STANDBY)))
			{
				for (dwFlags = BSM_APPLICATIONS; !m_bOperatingMode || BroadcastSystemMessage(BSF_IGNORECURRENTTASK, &dwFlags, m_nExitID, (WPARAM)NULL, (LPARAM)NULL) >= 0; )
				{
					for (GetTMService()->EnableTestMode(FALSE), GetTCService()->EnableTestMode(FALSE), szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); !szMessage.IsEmpty() && bReport; )
					{
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
						break;
					}
					m_bOperatingMode = FALSE;
					return TRUE;
				}
			}
		}
		if (m_szOperatingMode.IsEmpty())
		{
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_STANDBY)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
			if (!_tcscmp(pszMode, STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_ACTIVE)))
			{
				for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_SUCCESSFUL), (m_szOperatingMode = pszMode)); bReport; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					break;
				}
				return TRUE;
			}
		}
		for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_FAILED), pszMode); bReport; )
		{
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
			break;
		}
		return FALSE;
	}
	for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_CHANGEOPERATINGMODE_OK), pszMode); bReport; )
	{
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		break;
	}
	return TRUE;
}

BOOL CDesktopApp::SaveRegistryData(CONST CStringArray &szSubSystems)
{
	INT  nSubSystem;
	INT  nSubSystems;
	BOOL  bSubSystem;
	CString  szMessage;
	CString  szSubSystem;
	CString  szSubSystemList;
	CStringArray  szFailedSubSystems;

	for (nSubSystem = 0, nSubSystems = (INT)szSubSystems.GetSize(), szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ACTION_FORMAT), STRING(IDS_AUTOMATIONSERVICE_NAME_CONFIGURATIONSETTINGS_SAVE)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE); nSubSystem < nSubSystems || !nSubSystems; nSubSystem++)
	{
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_LOGINSCHEDULE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_LOGINSCHEDULE)))
		{
			for (ReportEvent((!(bSubSystem = SaveLoginOptions())) ? SYSTEM_WARNING_LOGINOPTIONS_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetTMService()->UpdateServiceInfo(TRUE)) ? SYSTEM_WARNING_TELEMETRYSERVICE_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELECOMMANDSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELECOMMANDSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetTCService()->UpdateServiceInfo(TRUE)) ? SYSTEM_WARNING_TELECOMMANDSERVICE_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_MEMORYDUMPSSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_MEMORYDUMPSSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetMemoryDumpsService()->UpdateServiceInfo(TRUE)) ? SYSTEM_WARNING_MEMORYDUMPSSERVICE_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TPEPSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TPEPSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetTPEPService()->UpdateServiceInfo(TRUE)) ? SYSTEM_WARNING_TPEP_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PFLPSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PFLPSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetPFLPService()->UpdateServiceInfo(TRUE)) ? SYSTEM_WARNING_PFLP_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUTOMATIONSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUTOMATIONSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetAutomationService()->UpdateServiceInfo(TRUE)) ? SYSTEM_WARNING_AUTOMATIONSERVICE_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_SYSTEMALERTS)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_SYSTEMALERTS)))
		{
			for (ReportEvent((!(bSubSystem = SaveSystemAlerts())) ? SYSTEM_WARNING_SYSTEMALERTS_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYEVENTS)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYEVENTS)))
		{
			for (ReportEvent((!(bSubSystem = SaveTelemetryEvents())) ? SYSTEM_WARNING_TELEMETRYEVENTS_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYREPORTS)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYREPORTS)))
		{
			for (ReportEvent((!(bSubSystem = (SaveTelemetryReports() && SaveTelemetryHistoricalReports()))) ? SYSTEM_WARNING_TELEMETRYREPORTS_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PRINTPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PRINTPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = SavePrintProfiles())) ? SYSTEM_WARNING_PRINTPROFILES_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUDITIONPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUDITIONPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = SaveAuditionProfiles())) ? SYSTEM_WARNING_AUDITIONPROFILES_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_NOTIFICATIONPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_NOTIFICATIONPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = SaveNotificationProfiles())) ? SYSTEM_WARNING_NOTIFICATIONPROFILES_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_DOWNLOADPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_DOWNLOADPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = SaveToolsDownloadProfiles())) ? SYSTEM_WARNING_TOOLSDOWNLOADPROFILES_SAVE_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		break;
	}
	if (szFailedSubSystems.GetSize() > 0)
	{
		for (nSubSystem = 0, nSubSystems = (INT)szFailedSubSystems.GetSize(); nSubSystem < nSubSystems; nSubSystem++)
		{
			szSubSystem.Format(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_QUOTATION), (LPCTSTR)szFailedSubSystems.GetAt(nSubSystem));
			szSubSystemList += (!szSubSystemList.IsEmpty()) ? (STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_SEPARATOR) + szSubSystem) : szSubSystem;
		}
		szMessage.Format(STRING(IDS_AUTOMATIONSERVIVE_MESSAGE_SAVECONFIGURATIONSETTINGS_FAILED), (LPCTSTR)szSubSystemList);
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		return FALSE;
	}
	ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_SUCCESS, STRING(IDS_AUTOMATIONSERVIVE_MESSAGE_SAVECONFIGURATIONSETTINGS_SUCCESSFUL), FALSE);
	return TRUE;
}

BOOL CDesktopApp::LoadRegistryData(CONST CStringArray &szSubSystems)
{
	INT  nSubSystem;
	INT  nSubSystems;
	BOOL  bSubSystem;
	CString  szMessage;
	CString  szSubSystem;
	CString  szSubSystemList;
	CStringArray  szFailedSubSystems;

	for (nSubSystem = 0, nSubSystems = (INT)szSubSystems.GetSize(), szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ACTION_FORMAT), STRING(IDS_AUTOMATIONSERVICE_NAME_CONFIGURATIONSETTINGS_LOAD)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE); nSubSystem < nSubSystems || !nSubSystems; nSubSystem++)
	{
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_LOGINSCHEDULE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_LOGINSCHEDULE)))
		{
			for (ReportEvent((!(bSubSystem = LoadLoginOptions())) ? SYSTEM_WARNING_LOGINOPTIONS_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetTMService()->UpdateServiceInfo(FALSE)) ? SYSTEM_WARNING_TELEMETRYSERVICE_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELECOMMANDSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELECOMMANDSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetTCService()->UpdateServiceInfo(FALSE)) ? SYSTEM_WARNING_TELECOMMANDSERVICE_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_MEMORYDUMPSSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_MEMORYDUMPSSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetMemoryDumpsService()->UpdateServiceInfo(FALSE)) ? SYSTEM_WARNING_MEMORYDUMPSSERVICE_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TPEPSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TPEPSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetTPEPService()->UpdateServiceInfo(FALSE)) ? SYSTEM_WARNING_TPEP_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PFLPSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PFLPSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetPFLPService()->UpdateServiceInfo(FALSE)) ? SYSTEM_WARNING_PFLP_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUTOMATIONSERVICE)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUTOMATIONSERVICE)))
		{
			for (ReportEvent(!(bSubSystem = GetAutomationService()->UpdateServiceInfo(FALSE)) ? SYSTEM_WARNING_AUTOMATIONSERVICE_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_SYSTEMALERTS)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_SYSTEMALERTS)))
		{
			for (ReportEvent((!(bSubSystem = LoadSystemAlerts())) ? SYSTEM_WARNING_SYSTEMALERTS_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYEVENTS)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYEVENTS)))
		{
			for (ReportEvent((!(bSubSystem = LoadTelemetryEvents())) ? SYSTEM_WARNING_TELEMETRYEVENTS_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYREPORTS)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_TELEMETRYREPORTS)))
		{
			for (ReportEvent((!(bSubSystem = LoadTelemetryReports() && LoadTelemetryHistoricalReports())) ? SYSTEM_WARNING_TELEMETRYREPORTS_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PRINTPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_PRINTPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = LoadPrintProfiles())) ? SYSTEM_WARNING_PRINTPROFILES_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUDITIONPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_AUDITIONPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = LoadAuditionProfiles())) ? SYSTEM_WARNING_AUDITIONPROFILES_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_NOTIFICATIONPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_NOTIFICATIONPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = LoadNotificationProfiles())) ? SYSTEM_WARNING_NOTIFICATIONPROFILES_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		if ((!_tcscmp(STRING(MINAUTOMATIONSERVICESUBSYSTEM + nSubSystem), STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_DOWNLOADPROFILES)) && !nSubSystems) || (nSubSystems > 0 && szSubSystems.GetAt(nSubSystem) == STRING(IDS_AUTOMATIONSERVICE_SUBSYSTEM_DOWNLOADPROFILES)))
		{
			for (ReportEvent((!(bSubSystem = LoadToolsDownloadProfiles())) ? SYSTEM_WARNING_TOOLSDOWNLOADPROFILES_LOAD_FAILURE : SYSTEM_NOERROR); !bSubSystem; )
			{
				szFailedSubSystems.Add(szSubSystems.GetAt(nSubSystem));
				break;
			}
			continue;
		}
		break;
	}
	if (szFailedSubSystems.GetSize() > 0)
	{
		for (nSubSystem = 0, nSubSystems = (INT)szFailedSubSystems.GetSize(); nSubSystem < nSubSystems; nSubSystem++)
		{
			szSubSystem.Format(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_QUOTATION), (LPCTSTR)szFailedSubSystems.GetAt(nSubSystem));
			szSubSystemList += (!szSubSystemList.IsEmpty()) ? (STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_SEPARATOR) + szSubSystem) : szSubSystem;
		}
		szMessage.Format(STRING(IDS_AUTOMATIONSERVIVE_MESSAGE_LOADCONFIGURATIONSETTINGS_FAILED), (LPCTSTR)szSubSystemList);
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		return FALSE;
	}
	ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_SUCCESS, STRING(IDS_AUTOMATIONSERVIVE_MESSAGE_LOADCONFIGURATIONSETTINGS_SUCCESSFUL), FALSE);
	return TRUE;
}

BOOL CDesktopApp::CheckSystemHealth() CONST
{
	DWORD_PTR  dwResult;

	return(SendMessageTimeout(GetMainWnd()->GetSafeHwnd(), WM_USER + 1, (WPARAM)NULL, (LPARAM)NULL, SMTO_ABORTIFHUNG | SMTO_NOTIMEOUTIFNOTHUNG, 0, &dwResult) > 0 && dwResult != 0);
}

BOOL CDesktopApp::ShowMessage(INT nMessageID)
{
	CMainWnd  *pMainWnd;

	return(((pMainWnd = GetMainWnd()) && pMainWnd->ShowMessage(nMessageID)) ? TRUE : FALSE);
}
BOOL CDesktopApp::ShowMessage(LPCTSTR pszMessage)
{
	CMainWnd  *pMainWnd;

	return(((pMainWnd = GetMainWnd()) && pMainWnd->ShowMessage(pszMessage)) ? TRUE : FALSE);
}

BOOL CDesktopApp::ReportMessage(INT nMessageID)
{
	CMainWnd  *pMainWnd;

	return(((pMainWnd = GetMainWnd()) && pMainWnd->ReportMessage(nMessageID)) ? TRUE : FALSE);
}

BOOL CDesktopApp::ReportEvent(CONST CSystemAlertInfo *pAlertInfo)
{
	INT  nAlert;
	INT  nAlerts;
	INT  nReport;
	INT  nReports;
	WORD  wAge;
	WORD  wGender;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szSpeaker;
	CString  szMessage;
	CString  szAudition;
	CString  szNotification;
	CEventObject  *pEvent;
	CStringArray  szAlerts;
	CStringArray  szNotifications;
	CAuditionProfiles  pAuditionProfiles;
	CTelemetryReports  pTelemetryReports;
	CAuditionProfileInfo  *pAuditionProfileInfo;
	CTelemetryReportInfo  *pTelemetryReportInfo;

	for (; lstrlen((szAudition = pAlertInfo->GetAudition())) > 0; )
	{
		if ((pAuditionProfileInfo = (GetAuditionProfiles(pAuditionProfiles)) ? pAuditionProfiles.GetAt(pAuditionProfiles.Find(szAudition)) : (CAuditionProfileInfo *)NULL))
		{
			if ((pEvent = new CEventObject))
			{
				pEvent->SetCategory(pAlertInfo->GetCategory());
				pEvent->SetType((pAlertInfo->GetType() == EVENT_TYPE_SUCCESS) ? STRING(IDS_EVENTTYPE_SUCCESS) : ((pAlertInfo->GetType() == EVENT_TYPE_INFORMATIONAL) ? STRING(IDS_EVENTTYPE_INFORMATIONAL) : ((pAlertInfo->GetType() == EVENT_TYPE_WARNING) ? STRING(IDS_EVENTTYPE_WARNING) : ((pAlertInfo->GetType() == EVENT_TYPE_ERROR) ? STRING(IDS_EVENTTYPE_ERROR) : EMPTYSTRING))));
				pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pAuditionProfileInfo->GetVoiceSound(szSpeaker, wGender, wAge);
				pEvent->SetAudition(pAuditionProfileInfo->GetAudition());
				pEvent->SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pEvent->SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
				pEvent->SetAuditWave(pAuditionProfileInfo->GetWaveSound());
				pEvent->SetAuditVoice(szSpeaker, wGender, wAge);
				pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime());
				pEvent->SetMessage(pAlertInfo->GetMessage());
				pEvent->SetAuditColor(VGA_COLOR_BLACK);
				pEvent->SetUser(GetAccountUserName());
				pEvent->Acknowledge(FALSE);
				pEvent->Show(TRUE);
				ReportEvent(pEvent);
				break;
			}
		}
		szMessage.Format(STRING(IDS_SYSTEMALERTS_AUDITION_FAILURE), (LPCTSTR)szAudition);
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		break;
	}
	for (pAlertInfo->GetNotifications(szNotifications); szNotifications.GetSize() > 0; szNotifications.RemoveAt(0))
	{
		if (!DoNotification((szNotification = szNotifications.GetAt(0)), pAlertInfo->GetMessage()))
		{
			szMessage.Format(STRING(IDS_SYSTEMALERTS_NOTIFICATION_FAILURE), (LPCTSTR)szNotification);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		}
	}
	for (nReport = 0, nReports = (GetTelemetryReports(pTelemetryReports)) ? (INT)pTelemetryReports.GetSize() : 0; nReport < nReports; nReport++)
	{
		if ((pTelemetryReportInfo = pTelemetryReports.GetAt(nReport)) && (pTelemetryReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_DISABLED) != TELEMETRYREPORTINFO_OPTION_DISABLED)
		{
			for (nAlert = 0, nAlerts = pTelemetryReportInfo->GetAlerts(szAlerts); nAlert < nAlerts; nAlert++)
			{
				if (pAlertInfo->TranslateName(pAlertInfo->GetName()) == szAlerts.GetAt(nAlert))
				{
					DoUpdateReport(pTelemetryReportInfo, pAlertInfo);
					break;
				}
			}
		}
	}
	return szMessage.IsEmpty();
}
BOOL CDesktopApp::ReportEvent(CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nEvent;
	INT  nEvents;
	INT  nReport;
	INT  nReports;
	WORD  wAge;
	WORD  wGender;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szError;
	CString  szAdapter;
	CString  szSpeaker;
	CString  szMessage;
	CString  szAudition;
	CString  szNotification;
	CEventObject  *pEvent;
	CStringArray  szEvents;
	CAuditionProfiles  pAuditionProfiles;
	CTelemetryReports  pTelemetryReports;
	CAuditionProfileInfo  *pAuditionProfileInfo;
	CTelemetryReportInfo  *pTelemetryReportInfo;

	for (; lstrlen((szAudition = pEventInfo->GetAudition())) > 0; )
	{
		if ((pAuditionProfileInfo = (GetAuditionProfiles(pAuditionProfiles)) ? pAuditionProfiles.GetAt(pAuditionProfiles.Find(szAudition)) : (CAuditionProfileInfo *)NULL))
		{
			if ((pEvent = new CEventObject))
			{
				pEvent->SetCategory(EVENT_CATEGORY_SPACECRAFT);
				pEvent->SetType(STRING(IDS_EVENTTYPE_INFORMATIONAL));
				pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pAuditionProfileInfo->GetVoiceSound(szSpeaker, wGender, wAge);
				pEvent->SetAudition(pAuditionProfileInfo->GetAudition());
				pEvent->SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pEvent->SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
				pEvent->SetAuditWave(pAuditionProfileInfo->GetWaveSound());
				pEvent->SetAuditVoice(szSpeaker, wGender, wAge);
				pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime());
				pEvent->SetMessage(pEventInfo->GetMessage());
				pEvent->SetAuditColor(VGA_COLOR_BLACK);
				pEvent->SetUser(GetAccountUserName());
				pEvent->Acknowledge(FALSE);
				pEvent->Show(TRUE);
				ReportEvent(pEvent);
				break;
			}
		}
		szMessage.Format(STRING(IDS_TELEMETRYEVENTS_AUDITION_FAILURE), (LPCTSTR)szAudition);
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		break;
	}
	if (lstrlen((szNotification = pEventInfo->GetNotification())) > 0)
	{
		if (!DoNotification(szNotification, pEventInfo->GetMessage()))
		{
			szMessage.Format(STRING(IDS_TELEMETRYEVENTS_NOTIFICATION_FAILURE), (LPCTSTR)szNotification);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
		}
	}
	for (nReport = 0, nReports = (GetTelemetryReports(pTelemetryReports)) ? (INT)pTelemetryReports.GetSize() : 0; nReport < nReports; nReport++)
	{
		if ((pTelemetryReportInfo = pTelemetryReports.GetAt(nReport)) && (pTelemetryReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_DISABLED) != TELEMETRYREPORTINFO_OPTION_DISABLED)
		{
			for (nEvent = 0, nEvents = pTelemetryReportInfo->GetEvents(szEvents); nEvent < nEvents; nEvent++)
			{
				if (pEventInfo->GetName() == szEvents.GetAt(nEvent))
				{
					DoUpdateReport(pTelemetryReportInfo, pEventInfo);
					break;
				}
			}
		}
	}
	return szMessage.IsEmpty();
}
BOOL CDesktopApp::ReportEvent(UINT nFlags, LPCTSTR pszEvent, BOOL bAudition)
{
	CMainWnd  *pMainWnd;

	return(((pMainWnd = GetMainWnd()) && pMainWnd->ReportEvent(nFlags, pszEvent, bAudition)) ? TRUE : FALSE);
}
BOOL CDesktopApp::ReportEvent(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition)
{
	CMainWnd  *pMainWnd;

	return(((pMainWnd = GetMainWnd()) && pMainWnd->ReportEvent(sEvent, bAudition)) ? TRUE : m_cEventLog.Report(sEvent));
}
BOOL CDesktopApp::ReportEvent(CEventObject *pEvent)
{
	CMainWnd  *pMainWnd;

	return(((pMainWnd = GetMainWnd()) && pMainWnd->ReportEvent(pEvent)) ? TRUE : FALSE);
}

BOOL CDesktopApp::ShowProgress(INT nProgress)
{
	CIdle  cIdle;
	CMainWnd  *pMainWnd;

	return(((pMainWnd = GetMainWnd()) && pMainWnd->ShowProgress(nProgress)) ? TRUE : FALSE);
}

BOOL CDesktopApp::ShowHelp(LPCTSTR pszTopic)
{
	if (IsHelpAvailable())
	{
		HtmlHelp((DWORD_PTR)pszTopic, HH_DISPLAY_TOPIC);
		return TRUE;
	}
	return FALSE;
}

BOOL CDesktopApp::IsHelpAvailable() CONST
{
	CFileFindEx  cFileFind;

	if (cFileFind.FindFile(GetHelpFileName()))
	{
		cFileFind.Close();
		return TRUE;
	}
	return FALSE;
}

HANDLE CDesktopApp::GetLogo() CONST
{
	return m_bLogo;
}

CDatabaseEngine *CDesktopApp::GetDatabase() CONST
{
	return m_pDatabase;
}

CTMService *CDesktopApp::GetTMService() CONST
{
	return m_pTMService;
}

CTCService *CDesktopApp::GetTCService() CONST
{
	return m_pTCService;
}

CRASService *CDesktopApp::GetRASService() CONST
{
	return m_pRASService;
}

CPFLPService *CDesktopApp::GetPFLPService() CONST
{
	return m_pPFLPService;
}

CTPEPService *CDesktopApp::GetTPEPService() CONST
{
	return m_pTPEPService;
}

CAutomationService *CDesktopApp::GetAutomationService() CONST
{
	return m_pAutomationService;
}

CMemoryDumpsService *CDesktopApp::GetMemoryDumpsService() CONST
{
	return m_pMemoryDumpsService;
}

CNotificationService *CDesktopApp::GetNotificationService() CONST
{
	return m_pNotificationService;
}

CTelemetryReportsService *CDesktopApp::GetTelemetryReportsService() CONST
{
	return m_pTelemetryReportsService;
}

CToolsDatabaseService *CDesktopApp::GetToolsDatabaseService() CONST
{
	return m_pToolsDatabaseService;
}

CToolsDownloadService *CDesktopApp::GetToolsDownloadService() CONST
{
	return m_pToolsDownloadService;
}

CNetworkBrowseService *CDesktopApp::GetNetworkBrowseService() CONST
{
	return m_pNetworkBrowseService;
}

CPFLPServiceEngine *CDesktopApp::GetPFLPServiceSupport() CONST
{
	return m_pPFLPServiceEngine->GetPFLPServiceEngine();
}

CTPEPServiceEngine *CDesktopApp::GetTPEPServiceSupport() CONST
{
	return m_pTPEPServiceEngine->GetTPEPServiceEngine();
}

CMemoryDumpsServiceEngine *CDesktopApp::GetMemoryDumpsServiceSupport() CONST
{
	return m_pMemoryDumpsServiceEngine->GetMemoryDumpsServiceEngine();
}

CEMailSystem *CDesktopApp::GetEMailSystem() CONST
{
	return m_pEMailSystem;
}

CDisplayFrame *CDesktopApp::GetDisplayFrame() CONST
{
	return GetMainWnd()->GetDisplayFrame();
}

CDisplayArea *CDesktopApp::GetDisplayArea() CONST
{
	return GetMainWnd()->GetDisplayArea();
}

CMainWnd *CDesktopApp::GetMainWnd() CONST
{
	return((CMainWnd *)CAccountsApp::m_pMainWnd);
}

INT CDesktopApp::RegisterApp()
{
	INT  nIndex;
	INT  nCount;
	CImage  cImage;
	HANDLE  hMutex;
	CString  szExit;
	CVersionInfo  cVersionInfo;
	CMFCToolBarImages  *pImages;
	CMFCToolTipInfo  cToolTipInfo;
	CWelcomeDialog  cWelcomeDialog;

	for (CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7)), InitCommonControls(), InitContextMenuManager(), InitKeyboardManager(), InitTooltipManager(), AfxOleInit(), AfxSocketInit(), AfxInitRichEdit(), AfxEnableControlContainer(), EnableTaskbarInteraction(FALSE), EnableHtmlHelp(), cToolTipInfo.m_bVislManagerTheme = TRUE, GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &cToolTipInfo); !(hMutex = CreateMutex((LPSECURITY_ATTRIBUTES)NULL, FALSE, cVersionInfo.QueryFileDescription())) || GetLastError() == ERROR_ALREADY_EXISTS; )
	{
		for (EnumWindows(EnumTopLevelWindows, (LPARAM)(LPCTSTR)GetAppTitle()); hMutex != (HANDLE)NULL; )
		{
			CloseHandle(hMutex);
			break;
		}
		return -1;
	}
	if ((IsInitialized() || cWelcomeDialog.DoModal() == IDOK) && CAccountsApp::RegisterApp())
	{
		for (RegisterCustomControls(), RegisterMimicsControls(), InitializeDefaultPrinter(), AfxRegisterWndClass(0), szExit.Format(STRING(IDS_APPLICATIONINFO_COMMANDTERMINATION_SIMULATOR), (LPCTSTR)cVersionInfo.QueryProductName()), m_nExitID = RegisterWindowMessage(szExit); (pImages = CMFCToolBar::GetImages()); )
		{
			for (cImage.LoadFromResource(GetModuleHandle((LPCTSTR)NULL), IDB_FLOATINGMENUSIMAGELIST), pImages->SetImageSize(CSize(cImage.GetWidth() / (sizeof(nFloatingMenuIDs) / sizeof(UINT)), cImage.GetHeight())); pImages->Load(IDB_FLOATINGMENUSIMAGELIST, (HINSTANCE)NULL, TRUE);)
			{
				for (nIndex = 0, nCount = sizeof(nFloatingMenuIDs) / sizeof(UINT); nIndex < nCount; nIndex++)
				{
					GetCmdMgr()->SetCmdImage(nFloatingMenuIDs[nIndex], nIndex, FALSE);
					continue;
				}
				return TRUE;
			}
			break;
		}
	}
	return FALSE;
}

BOOL CDesktopApp::UnregisterApp()
{
	SetLoginData();
	UnregisterCustomControls();
	m_cEventLog.UnregisterSource(EVENTLOG_CATEGORY_ALL, FALSE);
	return CAccountsApp::UnregisterApp();
}

BOOL CDesktopApp::EvaluateAccount(CONST CDesktopAppCommandLineInfo &cStartupInfo, CAccountToken *pAccountToken)
{
	INT  nUser;
	INT  nUsers;
	INT  nAccount;
	INT  nAccounts;
	INT  nDatabase;
	INT  nDatabases;
	CDatabases  cDatabases;
	CStringArray  szUsers;
	CUserAccounts  cUserAccounts;
	CAccountTokens  pAccountTokens;
	CDatabaseProfiles  pDatabaseProfiles;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	for (nAccount = 0, nAccounts = cUserAccounts.EnumAccounts(pAccountTokens); nAccount < nAccounts; nAccount++)
	{
		if (!pAccountTokens.GetAt(nAccount)->GetSpacecraftName().CompareNoCase(cStartupInfo.GetSpacecraft()) && !pAccountTokens.GetAt(nAccount)->GetUserName().Compare(cStartupInfo.GetUser()) && !pAccountTokens.GetAt(nAccount)->GetPassword().Compare(cStartupInfo.GetPassword()))
		{
			for (nDatabase = 0, nDatabases = (cDatabases.GetDatabases(pDatabaseProfiles)) ? (INT)pDatabaseProfiles.GetSize() : -1, pAccountToken->Copy(pAccountTokens.GetAt(nAccount)); nDatabase < nDatabases; nDatabase++)
			{
				if ((pDatabaseProfileInfo = pDatabaseProfiles.GetAt(nDatabase)) && !pDatabaseProfileInfo->GetName().Compare(cStartupInfo.GetDatabase()) && !pDatabaseProfileInfo->GetSpacecraft().CompareNoCase(cStartupInfo.GetSpacecraft()))
				{
					for (nUser = 0, nUsers = pDatabaseProfileInfo->GetUsers(szUsers); nUser < nUsers; nUser++)
					{
						if (!szUsers.GetAt(nUser).Compare(cStartupInfo.GetUser())) break;
						continue;
					}
					if (nUser < nUsers) break;
				}
			}
			if (nDatabase < nDatabases)
			{
				pAccountToken->SetDatabase(cStartupInfo.GetDatabase());
				SetAccount(pAccountToken);
				break;
			}
			nAccount = nAccounts;
			break;
		}
	}
	return((nAccount < nAccounts) ? TRUE : FALSE);
}

BOOL CDesktopApp::ActivateAccount()
{
	return((!GetMainWnd()->GetReportDisplay() || GetMainWnd()->GetReportDisplay()->ActivateAccount()) ? SaveAccount() : FALSE);
}
BOOL CDesktopApp::ActivateAccount(CAccountToken *pAccountToken)
{
	for (SetAccount(pAccountToken), GetMainWnd()->UpdateLayout(); !CompareAccount(pAccountToken); )
	{
		if (m_cEventLog.SetOwner(pAccountToken) && m_cEventLog.RegisterSource()) return ActivateAccount();
		return FALSE;
	}
	return m_cEventLog.SetOwner(pAccountToken) && m_cEventLog.RegisterSource();
}

BOOL CDesktopApp::IsAccountActivated() CONST
{
	return((TestAccount() && GetMainWnd()->CheckDisplays()) ? TRUE : FALSE);
}

VOID CDesktopApp::ShowAccountStatus()
{
	GetMainWnd()->UpdateTitle();
	GetMainWnd()->UpdateStatusBar();
	GetMainWnd()->UpdateDisplays();
	GetMainWnd()->UpdateMenus();
}

BOOL CDesktopApp::TestAccountStatus(EVENT_DESCRIPTOR &sEvent)
{
	for (sEvent = SYSTEM_NOERROR; (GetTCService()->GetCommandHandlerOptions() & TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT) != TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT && (GetTCService()->GetCommandHandlerState() & TCSERVICE_COMMANDHANDLERSTATE_EMPTY) != TCSERVICE_COMMANDHANDLERSTATE_EMPTY; )
	{
		sEvent = SYSTEM_WARNING_ACCOUNT_TERMINATION_FAILURE;
		return FALSE;
	}
	return TRUE;
}

BOOL CDesktopApp::CompareAccount(CAccountToken *pAccountToken) CONST
{
	return((!AfxIsValidAddress(pAccountToken, sizeof(CAccountToken)) || CheckAccountOwner(pAccountToken)) ? TRUE : FALSE);
}

BOOL CDesktopApp::CompareAccountSpacecraft(CAccountToken *pAccountToken) CONST
{
	return((!AfxIsValidAddress(pAccountToken, sizeof(CAccountToken)) || (pAccountToken->GetSpacecraftName() == GetAccountSpacecraftName())) ? TRUE : FALSE);
}

BOOL CDesktopApp::CompareAccountUser(CAccountToken *pAccountToken) CONST
{
	return((!AfxIsValidAddress(pAccountToken, sizeof(CAccountToken)) || (pAccountToken->GetUserName() == GetAccountUserName())) ? TRUE : FALSE);
}

BOOL CDesktopApp::CompareAccountMode(CAccountToken *pAccountToken) CONST
{
	return((!AfxIsValidAddress(pAccountToken, sizeof(CAccountToken)) || (pAccountToken->GetMode() == GetAccountMode())) ? TRUE : FALSE);
}

BOOL CDesktopApp::CompareAccountDatabase(CAccountToken *pAccountToken) CONST
{
	return((!AfxIsValidAddress(pAccountToken, sizeof(CAccountToken)) || (pAccountToken->GetDatabase() == GetAccountDatabase())) ? TRUE : FALSE);
}

BOOL CDesktopApp::CompareAccountServer(CAccountToken *pAccountToken) CONST
{
	return((!AfxIsValidAddress(pAccountToken, sizeof(CAccountToken)) || (pAccountToken->GetRASServer() == GetAccountRASServer())) ? TRUE : FALSE);
}

BOOL CDesktopApp::LoadSpacecraftLibrary()
{
	return m_pMemoryDumpsServiceEngine->Open(GetAccountSpacecraftName()) && m_pPFLPServiceEngine->Open(GetAccountSpacecraftName()) && m_pTPEPServiceEngine->Open(GetAccountSpacecraftName());
}

VOID CDesktopApp::FreeSpacecraftLibrary(UINT nCode)
{
	m_pMemoryDumpsServiceEngine->Close();
	m_pPFLPServiceEngine->Close();
	m_pTPEPServiceEngine->Close();
}

BOOL CDesktopApp::LoadLayout()
{
	return GetMainWnd()->LoadLayout();
}

VOID CDesktopApp::FreeLayout(UINT nCode)
{
	GetMainWnd()->SaveLayout(nCode);
}

BOOL CDesktopApp::LoadDatabase()
{
	INT  nError;
	INT  nErrors;
	INT  nDatabase;
	INT  nDatabases;
	BOOL  bDatabase;
	UINT  nMessageCode;
	CString  szMessage;
	CString  szParameter;
	CStringArray  szErrors;
	CDatabases  cDatabases;
	CDatabaseProfiles  cDatabaseProfiles;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CAccountToken  cAccountToken;

	if (GetDatabase()->GetName() != GetAccountDatabase())
	{
		if (cDatabases.GetDatabases(cDatabaseProfiles, TRUE))
		{
			for (nDatabase = 0, nDatabases = (INT)cDatabaseProfiles.GetSize(); nDatabase < nDatabases; nDatabase++)
			{
				if ((pDatabaseProfileInfo = cDatabaseProfiles.GetAt(nDatabase))->GetName() == GetAccountDatabase())
				{
					for (szMessage.Format(STRING(IDS_DATABASE_LOADING), (LPCTSTR)pDatabaseProfileInfo->GetSpacecraft()), ShowMessage(szMessage), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE); (bDatabase = GetDatabase()->Open(pDatabaseProfileInfo, FALSE)); )
					{
						if ((nMessageCode = GetDatabase()->Load(DATABASE_COMPONENTS_ALL | DATABASE_SUBCOMPONENTS_ALL, FALSE)) == (UINT)-1)
						{
							szMessage.Format(STRING(IDS_DATABASE_SAVING), (LPCTSTR)pDatabaseProfileInfo->GetSpacecraft());
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
						}
						if (!nMessageCode)
						{
							for (szMessage.Format(STRING(IDS_DATABASE_LOAD_FAILURE), (LPCTSTR)pDatabaseProfileInfo->GetSpacecraft()), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage), GetAccount(&cAccountToken); cAccountToken.SetDatabase(EMPTYSTRING); )
							{
								SetAccount(&cAccountToken);
								break;
							}
							GetDatabase()->Close();
							FreeDatabase();
							return FALSE;
						}
						if (GetDatabase()->LoadLibrary(szErrors))
						{
							for (nError = 0, nErrors = (INT)szErrors.GetSize(), szMessage = STRING(IDS_DATABASE_DERIVEDPARAMETERS_INITIALIZATION_FAILURE); nError < nErrors; nError++)
							{
								szParameter.Format((!nError) ? STRING(IDS_DATABASE_DERIVEDPARAMETERS_PARAMETER_FAILURE) : STRING(IDS_DATABASE_DERIVEDPARAMETERS_PARAMETERS_FAILURE), (LPCTSTR)szErrors.GetAt(nError));
								szMessage += szParameter;
							}
							ReportEvent((nErrors > 0)*(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR), szMessage);
							break;
						}
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, STRING(IDS_DATABASE_DERIVEDPARAMETERS_FAILURE));
						bDatabase = FALSE;
						break;
					}
					if (!bDatabase)
					{
						for (szMessage.Format(STRING(IDS_DATABASE_LOAD_FAILURE), (LPCTSTR)pDatabaseProfileInfo->GetSpacecraft()), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage), GetAccount(&cAccountToken); cAccountToken.SetDatabase(EMPTYSTRING); )
						{
							SetAccount(&cAccountToken);
							break;
						}
						FreeDatabase();
						return FALSE;
					}
					break;
				}
			}
			if (nDatabase == nDatabases)
			{
				for (ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, STRING(IDS_DATABASE_LOAD_NONE), FALSE), GetAccount(&cAccountToken); cAccountToken.SetDatabase(EMPTYSTRING); )
				{
					SetAccount(&cAccountToken);
					break;
				}
				FreeDatabase();
				return FALSE;
			}
			return TRUE;
		}
		for (szMessage.Format(STRING(IDS_DATABASE_LOAD_FAILURE), (LPCTSTR)GetAccountSpacecraftName()); !GetAccountSpacecraftName().IsEmpty(); )
		{
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
			break;
		}
		GetAccount(&cAccountToken);
		cAccountToken.SetDatabase(EMPTYSTRING);
		SetAccount(&cAccountToken);
		FreeDatabase();
		return FALSE;
	}
	return TRUE;
}

VOID CDesktopApp::FreeDatabase(UINT nCode)
{
	GetDatabase()->FreeLibrary();
	GetDatabase()->Detach();
	GetDatabase()->Close();
}

BOOL CDesktopApp::LoadDisplays()
{
	return GetMainWnd()->LoadDisplays();
}

VOID CDesktopApp::FreeDisplays(UINT nCode)
{
	GetMainWnd()->SaveDisplays(nCode);
}

BOOL CDesktopApp::LoadUser()
{
	SetRegistryBase(GetAccountUserName() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + STRING(IDS_REG_SUBKEYPART_WORKSPACE));
	LoadConfigurationData();
	StartAssistant();
	return GetMainWnd()->LoadUser();
}

VOID CDesktopApp::FreeUser(UINT nCode)
{
	StopAssistant();
	SaveConfigurationData();
	GetMainWnd()->SaveUser(nCode);
}

BOOL CDesktopApp::SaveLoginOptions()
{
	CByteArray  nOptionsInfo;
	CProfile  cProfile;

	return m_pLoginOptions->Map(nOptionsInfo) && cProfile.SetLoginOptions(nOptionsInfo);
}

BOOL CDesktopApp::LoadLoginOptions()
{
	CByteArray  nOptionsInfo;
	CProfile  cProfile;

	return cProfile.GetLoginOptions(nOptionsInfo) && m_pLoginOptions->Unmap(nOptionsInfo);
}

BOOL CDesktopApp::SavePrintProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return m_pPrintProfiles->Map(nProfilesInfo) && cProfile.SetPrintProfilesInfo(nProfilesInfo);
}

BOOL CDesktopApp::LoadPrintProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return cProfile.GetPrintProfilesInfo(nProfilesInfo) && m_pPrintProfiles->Unmap(nProfilesInfo);
}

BOOL CDesktopApp::SaveAuditionProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return m_pAuditionProfiles->Map(nProfilesInfo) && cProfile.SetAuditionProfilesInfo(nProfilesInfo);
}

BOOL CDesktopApp::LoadAuditionProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return cProfile.GetAuditionProfilesInfo(nProfilesInfo) && m_pAuditionProfiles->Unmap(nProfilesInfo);
}

BOOL CDesktopApp::SaveNotificationProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return m_pNotificationProfiles->Map(nProfilesInfo) && cProfile.SetNotificationProfilesInfo(nProfilesInfo);
}

BOOL CDesktopApp::LoadNotificationProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return cProfile.GetNotificationProfilesInfo(nProfilesInfo) && m_pNotificationProfiles->Unmap(nProfilesInfo);
}

BOOL CDesktopApp::SaveToolsDownloadProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return m_pToolsDownloadProfiles->Map(nProfilesInfo) && cProfile.SetToolsDownloadProfilesInfo(nProfilesInfo);
}

BOOL CDesktopApp::LoadToolsDownloadProfiles()
{
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return cProfile.GetToolsDownloadProfilesInfo(nProfilesInfo) && m_pToolsDownloadProfiles->Unmap(nProfilesInfo);
}

BOOL CDesktopApp::SaveSystemAlerts()
{
	CByteArray  nAlertsInfo;
	CSystemAlerts  pAlerts;
	CProfile  cProfile;

	return GetSystemAlerts(pAlerts) && pAlerts.Map(nAlertsInfo) && cProfile.SetSystemAlertsInfo(nAlertsInfo);
}

BOOL CDesktopApp::LoadSystemAlerts()
{
	CByteArray  nAlertsInfo;
	CSystemAlerts  pAlerts;
	CProfile  cProfile;

	return cProfile.GetSystemAlertsInfo(nAlertsInfo) && pAlerts.Unmap(nAlertsInfo) && SetSystemAlerts(pAlerts);
}

BOOL CDesktopApp::SaveTelemetryEvents()
{
	CByteArray  nEventsInfo;
	CTelemetryEvents  pEvents;
	CProfile  cProfile;

	return GetTelemetryEvents(pEvents) && pEvents.Map(nEventsInfo) && cProfile.SetTelemetryEventsInfo(nEventsInfo);
}

BOOL CDesktopApp::LoadTelemetryEvents()
{
	CByteArray  nEventsInfo;
	CTelemetryEvents  pEvents;
	CProfile  cProfile;

	return cProfile.GetTelemetryEventsInfo(nEventsInfo) && pEvents.Unmap(nEventsInfo) && SetTelemetryEvents(pEvents);
}

BOOL CDesktopApp::SaveTelemetryReports()
{
	CByteArray  nReportsInfo;
	CTelemetryReports  pReports;
	CProfile  cProfile;

	return GetTelemetryReports(pReports) && pReports.Map(nReportsInfo) && cProfile.SetTelemetryReportsInfo(nReportsInfo);
}

BOOL CDesktopApp::LoadTelemetryReports()
{
	CByteArray  nReportsInfo;
	CTelemetryReports  pReports;
	CProfile  cProfile;

	return cProfile.GetTelemetryReportsInfo(nReportsInfo) && pReports.Unmap(nReportsInfo) && SetTelemetryReports(pReports);
}

BOOL CDesktopApp::SaveTelemetryHistoricalReports()
{
	CByteArray  nHistoricalReportsInfo;
	CProfile  cProfile;

	return m_pTelemetryHistoricalReports->Map(nHistoricalReportsInfo) && cProfile.SetTelemetryHistoricalReportsInfo(nHistoricalReportsInfo);
}

BOOL CDesktopApp::LoadTelemetryHistoricalReports()
{
	CByteArray  nHistoricalReportsInfo;
	CProfile  cProfile;

	return cProfile.GetTelemetryHistoricalReportsInfo(nHistoricalReportsInfo) && m_pTelemetryHistoricalReports->Unmap(nHistoricalReportsInfo);
}

BOOL CDesktopApp::SaveToolsEMailSettings()
{
	CByteArray  nEMailSettingsInfo;
	CProfile  cProfile;

	return m_pEMailSystem->Map(nEMailSettingsInfo) && cProfile.SetToolsEMailSettingsInfo(nEMailSettingsInfo);
}

BOOL CDesktopApp::LoadToolsEMailSettings()
{
	CByteArray  nEMailSettingsInfo;
	CProfile  cProfile;

	return cProfile.GetToolsEMailSettingsInfo(nEMailSettingsInfo) && m_pEMailSystem->Unmap(nEMailSettingsInfo);
}

BOOL CDesktopApp::SaveTemporaryANDs(CByteArray &nANDs)
{
	return m_pTemporaryANDs.Map(nANDs);
}

BOOL CDesktopApp::SaveTemporaryGRDs(CByteArray &nGRDs)
{
	return m_pTemporaryGRDs.Map(nGRDs);
}

BOOL CDesktopApp::SaveTemporaryPODs(CByteArray &nPODs)
{
	return m_pTemporaryPODs.Map(nPODs);
}

BOOL CDesktopApp::LoadTemporaryANDs(CONST CByteArray &nANDs)
{
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	INT  nParameter;
	INT  nParameters;
	CANDLayout  *pLayout;
	CANDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nLayout = 0, nLayouts = (m_pTemporaryANDs.Unmap(nANDs)) ? (INT)m_pTemporaryANDs.GetSize() : -1; nLayout < nLayouts; nLayout++)
	{
		for (nParameter = 0, nParameters = ((pLayout = m_pTemporaryANDs.GetAt(nLayout))) ? (INT)pLayout->GetSize() : 0; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = ((pParameter = pLayout->GetAt(nParameter))) ? GetDatabase()->GetTMParameters()->GetAt((nIndex = GetDatabase()->GetTMParameters()->Find(pParameter->GetName()))) : (CDatabaseTMParameter *)NULL))
			{
				pParameter->SetAttributes(((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_INTERPRETATION_FULL | TMPARAMETER_INTERPRETATION_EXTRAPOLATE | TMPARAMETER_FLAG_BIGENDIAN | TMPARAMETER_FLAG_LITTLEENDIAN)) != (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_INTERPRETATION_FULL | TMPARAMETER_INTERPRETATION_EXTRAPOLATE | TMPARAMETER_FLAG_BIGENDIAN | TMPARAMETER_FLAG_LITTLEENDIAN))) ? pDatabaseTMParameter->GetAttributes() : pParameter->GetAttributes());
				pParameter->SetRef(nIndex);
			}
		}
	}
	return((nLayout == nLayouts) ? TRUE : FALSE);
}

BOOL CDesktopApp::LoadTemporaryGRDs(CONST CByteArray &nGRDs)
{
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	INT  nParameter;
	INT  nParameters;
	CGRDLayout  *pLayout;
	CGRDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nLayout = 0, nLayouts = (m_pTemporaryGRDs.Unmap(nGRDs)) ? (INT)m_pTemporaryGRDs.GetSize() : -1; nLayout < nLayouts; nLayout++)
	{
		for (nParameter = 0, nParameters = ((pLayout = m_pTemporaryGRDs.GetAt(nLayout))) ? (INT)pLayout->GetSize() : 0; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = ((pParameter = pLayout->GetAt(nParameter))) ? GetDatabase()->GetTMParameters()->GetAt((nIndex = GetDatabase()->GetTMParameters()->Find(pParameter->GetName()))) : (CDatabaseTMParameter *)NULL))
			{
				pParameter->SetAttributes(((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_INTERPRETATION_FULL | TMPARAMETER_INTERPRETATION_EXTRAPOLATE | TMPARAMETER_FLAG_BIGENDIAN | TMPARAMETER_FLAG_LITTLEENDIAN)) != (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_INTERPRETATION_FULL | TMPARAMETER_INTERPRETATION_EXTRAPOLATE | TMPARAMETER_FLAG_BIGENDIAN | TMPARAMETER_FLAG_LITTLEENDIAN))) ? pDatabaseTMParameter->GetAttributes() : pParameter->GetAttributes());
				pParameter->SetRef(nIndex);
			}
		}
	}
	return((nLayout == nLayouts) ? TRUE : FALSE);
}

BOOL CDesktopApp::LoadTemporaryPODs(CONST CByteArray &nPODs)
{
	return m_pTemporaryPODs.Unmap(nPODs);
}

BOOL CDesktopApp::SaveState(LPCTSTR lpszSectionName, CFrameImpl *pFrameImpl)
{
	return TRUE;
}

BOOL CDesktopApp::LoadState(LPCTSTR lpszSectionName, CFrameImpl *pFrameImpl)
{
	return TRUE;
}

VOID CDesktopApp::StartServices()
{
	ReportEvent((!GetAutomationService()->Start()) ? SYSTEM_WARNING_AUTOMATIONSERVICE_START_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetNotificationService()->Start()) ? SYSTEM_WARNING_NOTIFICATIONSERVICE_START_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetNetworkBrowseService()->Start()) ? SYSTEM_WARNING_NETWORKBROWSESERVICE_START_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetToolsDownloadService()->Start()) ? SYSTEM_WARNING_TOOLSDOWNLOADSERVICE_START_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetToolsDatabaseService()->Start()) ? SYSTEM_WARNING_TOOLSDATABASESERVICE_START_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!StartRASScheduler()) ? SYSTEM_WARNING_REMOTENETWORK_LOGINSCHEDULER_FAILURE : SYSTEM_NOERROR);
}

VOID CDesktopApp::StopServices()
{
	ReportEvent((!StopRASScheduler()) ? SYSTEM_WARNING_REMOTENETWORK_LOGOUTSCHEDULER_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetAutomationService()->Stop()) ? SYSTEM_WARNING_AUTOMATIONSERVICE_STOP_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetNotificationService()->Stop()) ? SYSTEM_WARNING_NOTIFICATIONSERVICE_STOP_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetNetworkBrowseService()->Stop()) ? SYSTEM_WARNING_NETWORKBROWSESERVICE_STOP_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetToolsDownloadService()->Stop()) ? SYSTEM_WARNING_TOOLSDOWNLOADSERVICE_STOP_FAILURE : SYSTEM_NOERROR);
	ReportEvent((!GetToolsDatabaseService()->Stop()) ? SYSTEM_WARNING_TOOLSDATABASESERVICE_STOP_FAILURE : SYSTEM_NOERROR);
}

VOID CDesktopApp::StartTMService()
{
	CAccountToken  cAccountToken;

	for (GetAccount(&cAccountToken), m_cAccountToken.Copy(&cAccountToken); !GetTMService()->Start(GetAccountSpacecraftName()); )
	{
		if (cAccountToken.SetMode(ACCOUNT_MODE_OFFLINE)) SetAccount(&cAccountToken);
		UpdateTelemetryStatus();
		break;
	}
	ReportEvent((!GetTelemetryReportsService()->Start(&m_cScriptsExecutor)) ? SYSTEM_WARNING_TELEMETRYREPORTSSERVICE_START_FAILURE : SYSTEM_NOERROR);
	m_bTMService = TRUE;
}

VOID CDesktopApp::UpdateTMService()
{
	if (GetAccountMode() == ACCOUNT_MODE_OFFLINE)
	{
		GetTMService()->Suspend();
		return;
	}
	if (GetAccountMode() == ACCOUNT_MODE_ONLINE)
	{
		GetTMService()->Resume();
		return;
	}
}

VOID CDesktopApp::StopTMService()
{
	if (m_bTMService)
	{
		ReportEvent((!GetTelemetryReportsService()->Stop(&m_cScriptsExecutor)) ? SYSTEM_WARNING_TELEMETRYREPORTSSERVICE_STOP_FAILURE : SYSTEM_NOERROR);
		GetTMService()->Stop();
		m_bTMService = FALSE;
	}
}

VOID CDesktopApp::StartTCService()
{
	GetTCService()->Start(GetAccountSpacecraftName());
	m_bTCService = TRUE;
}

VOID CDesktopApp::UpdateTCService()
{
	return;
}

VOID CDesktopApp::StopTCService()
{
	if (m_bTCService)
	{
		GetTCService()->Stop();
		m_bTCService = FALSE;
	}
}

VOID CDesktopApp::StartDisplays()
{
	GetMainWnd()->StartDisplays();
}

VOID CDesktopApp::StopDisplays()
{
	GetMainWnd()->StopDisplays();
}

VOID CDesktopApp::StartAssistant()
{
	GetMainWnd()->StartAssistant();
}

VOID CDesktopApp::StopAssistant()
{
	GetMainWnd()->StopAssistant();
}

VOID CDesktopApp::ShowWaitCursor()
{
	if (!m_nWaitID  &&  ++m_nWaitID > 0)
	{
		CAccountsApp::BeginWaitCursor();
		GetMainWnd()->SetCapture();
		return;
	}
	m_nWaitID++;
}

BOOL CDesktopApp::IsShowingWaitCursor() CONST
{
	return((m_nWaitID > 0) ? TRUE : FALSE);
}

VOID CDesktopApp::StopWaitCursor()
{
	if (m_nWaitID > 0 && --m_nWaitID == 0)
	{
		CAccountsApp::EndWaitCursor();
		ReleaseCapture();
	}
}

VOID CALLBACK CDesktopApp::Login(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime)
{
	UINT  nCount[2];
	CTimeKey  tTime[3];
	CTimeSpan  tInterval;

	if (cDesktopApp.m_pLoginOptions->Lock())
	{
		if (!cDesktopApp.GetRASService()->IsCalling())
		{
			for (cDesktopApp.GetRASService()->StopCall(); cDesktopApp.m_nTimerID[2] != 0; )
			{
				KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[2]);
				cDesktopApp.m_nTimerID[2] = 0;
				break;
			}
			for (cDesktopApp.ShowAccountStatus(); ((!cDesktopApp.m_pLoginInfo->GetServer().IsEmpty() && cDesktopApp.m_pLoginInfo->GetTimeRange(tTime[0], tTime[1]) && tTime[0] <= tTime[2] && tTime[1] > tTime[2]) || cDesktopApp.m_pLoginInfo->GetServer().IsEmpty()); )
			{
				if (cDesktopApp.m_pLoginOptions->GetOptions() & LOGIN_OPTION_RECONNECT)
				{
					if (cDesktopApp.m_pLoginOptions->GetRetention(tInterval, nCount[0]))
					{
						if ((nCount[1] = cDesktopApp.m_pLoginOptions->GetRetentionRetries()) < nCount[0] || !nCount[0])
						{
							for (; nCount[1] < nCount[0] && nCount[0] > 0 && nCount[1] >= 0; )
							{
								cDesktopApp.m_pLoginOptions->SetRetentionRetries(nCount[1] + 1);
								break;
							}
							if (cDesktopApp.m_nTimerID[1] != 0)
							{
								KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[1]);
								cDesktopApp.m_nTimerID[1] = 0;
							}
							if ((cDesktopApp.m_nTimerID[1] = SetTimer((HWND)NULL, 0, (!tInterval.GetTotalSeconds()) ? (UINT)(1000 * RASSERVICE_DEFAULT_TIMEOUT) : (UINT)(1000 * tInterval.GetTotalSeconds()), Login)) != 0)
							{
								cDesktopApp.SetAccount(cDesktopApp.m_pLoginAccount);
								cDesktopApp.m_pLoginOptions->Unlock();
								cDesktopApp.LoginTMService();
								return;
							}
						}
						break;
					}
					cDesktopApp.SetAccount(cDesktopApp.m_pLoginAccount);
					cDesktopApp.LoginTMService();
				}
				break;
			}
			if (cDesktopApp.m_nTimerID[1] != 0)
			{
				KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[1]);
				cDesktopApp.m_nTimerID[1] = 0;
			}
		}
		cDesktopApp.m_pLoginOptions->Unlock();
	}
}

BOOL CALLBACK CDesktopApp::LoginScheduler()
{
	LoginScheduler((HWND)NULL, 0, (UINT_PTR)-1, 0);
	return TRUE;
}
VOID CALLBACK CDesktopApp::LoginScheduler(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime)
{
	INT  nItem;
	INT  nItems;
	DWORD  dwTimeout;
	CTimeKey  tTime[3];
	CLoginInfo  *pLoginInfo;
	CAccountToken  cAccountToken;

	if (cDesktopApp.m_pLoginOptions->Lock())
	{
		for (nItem = 0, nItems = (cDesktopApp.m_nTimerID[0] != 0) ? (INT)cDesktopApp.m_pLoginOptions->GetSize() : -1, cDesktopApp.GetAccount(&cAccountToken), dwTimeout = 1000 * SECONDSPERDAY; nItem < nItems; nItem++)
		{
			if ((pLoginInfo = cDesktopApp.m_pLoginOptions->GetAt(nItem)) && pLoginInfo->GetTimeRange(tTime[0], tTime[1]) && tTime[1] <= tTime[2])
			{
				cDesktopApp.m_pLoginOptions->RemoveAt(nItem);
				delete pLoginInfo;
				nItems--;
				nItem--;
				continue;
			}
			if ((pLoginInfo = cDesktopApp.m_pLoginOptions->GetAt(nItem)) && pLoginInfo->GetTimeRange(tTime[0], tTime[1]) && tTime[0] <= tTime[2] && tTime[1] > tTime[2])
			{
				if (cDesktopApp.m_pLoginInfo->Compare(pLoginInfo))
				{
					dwTimeout = (DWORD)(tTime[1].GetTime() - tTime[2].GetTime());
					dwTimeout = 1000 * min(dwTimeout, SECONDSPERDAY);
					break;
				}
			}
			if ((pLoginInfo = cDesktopApp.m_pLoginOptions->GetAt(nItem)) && pLoginInfo->GetTimeRange(tTime[0], tTime[1]) && tTime[1] > tTime[2])
			{
				if ((dwTimeout = (DWORD)(1000 * min(max(tTime[0].GetTime(), tTime[2].GetTime()) - tTime[2].GetTime(), SECONDSPERDAY))) == 0)
				{
					if (cAccountToken.GetRASServer() != pLoginInfo->GetServer() + TAB || cAccountToken.GetRASUserName() != pLoginInfo->GetUser() || cAccountToken.GetRASPassword() != pLoginInfo->GetPassword())
					{
						cAccountToken.SetRASServer(pLoginInfo->GetServer() + TAB);
						cAccountToken.SetRASPassword(pLoginInfo->GetPassword());
						cAccountToken.SetRASUserName(pLoginInfo->GetUser());
						cDesktopApp.m_pLoginInfo->Copy(pLoginInfo);
						cDesktopApp.StartAccount(&cAccountToken);
						break;
					}
					cDesktopApp.m_pLoginInfo->Copy(pLoginInfo);
					break;
				}
				if (cAccountToken.GetRASServer() == cDesktopApp.m_pLoginInfo->GetServer() + TAB)
				{
					for (cDesktopApp.m_pLoginInfo->SetServer(EMPTYSTRING), cDesktopApp.m_pLoginInfo->SetPassword(EMPTYSTRING), cDesktopApp.m_pLoginInfo->SetUser(EMPTYSTRING), cAccountToken.SetRASServer(EMPTYSTRING), cAccountToken.SetRASUserName(EMPTYSTRING), cAccountToken.SetRASPassword(EMPTYSTRING); cDesktopApp.m_nTimerID[1] != 0; )
					{
						KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[1]);
						cDesktopApp.m_nTimerID[1] = 0;
						break;
					}
					cDesktopApp.StartAccount(&cAccountToken);
				}
				break;
			}
			cDesktopApp.m_pLoginOptions->RemoveAt(nItem);
			delete pLoginInfo;
			nItems--;
			nItem--;
		}
		for (; !nItems; )
		{
			if (cAccountToken.GetRASServer() == cDesktopApp.m_pLoginInfo->GetServer() + TAB)
			{
				for (cDesktopApp.m_pLoginInfo->SetServer(EMPTYSTRING), cDesktopApp.m_pLoginInfo->SetPassword(EMPTYSTRING), cDesktopApp.m_pLoginInfo->SetUser(EMPTYSTRING), cAccountToken.SetRASServer(EMPTYSTRING), cAccountToken.SetRASUserName(EMPTYSTRING), cAccountToken.SetRASPassword(EMPTYSTRING); cDesktopApp.m_nTimerID[1] != 0; )
				{
					KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[1]);
					cDesktopApp.m_nTimerID[1] = 0;
					break;
				}
				cDesktopApp.StartAccount(&cAccountToken);
				break;
			}
			if (cDesktopApp.m_nTimerID[1] != 0)
			{
				KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[1]);
				cDesktopApp.m_nTimerID[1] = 0;
			}
			break;
		}
		for (; nItems >= 0; )
		{
			cDesktopApp.ReportEvent(((cDesktopApp.m_nTimerID[0] = (KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[0])) ? SetTimer((HWND)NULL, 0, dwTimeout, LoginScheduler) : 0) == 0) ? SYSTEM_WARNING_REMOTENETWORK_LOGINOUTSCHEDULER_FAILURE : SYSTEM_NOERROR);
			break;
		}
		cDesktopApp.m_pLoginOptions->Unlock();
	}
}

VOID CALLBACK CDesktopApp::LoginState(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime)
{
	INT  nNumber;
	INT  nNumbers;
	TCHAR  szError[512];
	CString  szServer;
	CString  szNumber;
	CString  szMessage;
	CTimeKey  tConnectTime;
	RAS_STATS  sStatistics;
	CStringArray  szNumbers;
	CStringTools  cStringTools;
	RASCONNSTATE  nConnectionState;

	if (!cDesktopApp.GetRASService()->IsAborting() && cDesktopApp.GetRASService()->GetDetails(szServer, szNumber, tConnectTime))
	{
		if ((nConnectionState = cDesktopApp.GetRASService()->GetState()) == RASCS_ConnectDevice)
		{
			szMessage.Format(STRING(IDS_RAS_STATE_CONNECTING), (LPCTSTR)szServer);
			cDesktopApp.ShowMessage(szMessage);
		}
		for (; nConnectionState == RASCS_Authenticate || nConnectionState == RASCS_ReAuthenticate; )
		{
			cDesktopApp.ShowMessage(STRING(IDS_RAS_STATE_AUTHENTICATING));
			break;
		}
		for (; nConnectionState == RASCS_PrepareForCallback; )
		{
			cDesktopApp.ShowMessage(STRING(IDS_RAS_STATE_PREPARINGFORCALLBACK));
			break;
		}
		for (; nConnectionState == RASCS_WaitForCallback; )
		{
			cDesktopApp.ShowMessage(STRING(IDS_RAS_STATE_WAITINGFORCALLBACK));
			break;
		}
		if (nConnectionState == RASCS_Connected)
		{
			for (szMessage.Format(STRING(IDS_RAS_STATE_COMPLETED), (LPCTSTR)szServer), cDesktopApp.ShowMessage(szMessage), cDesktopApp.ScheduleRASService(nConnectionState); cDesktopApp.GetRASService()->GetDetails(&sStatistics); )
			{
				for (szMessage.Format(STRING(IDS_RAS_MESSAGE_LINECONNECTED), (LPCTSTR)szServer, (LPCTSTR)cStringTools.ConvertUIntToStructuredString(sStatistics.dwBps)), cDesktopApp.ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE); sStatistics.dwBps <= 33600; )
				{
					cDesktopApp.ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, STRING(IDS_RAS_MESSAGE_LINECONNECTIONSPEEDINFO), FALSE);
					break;
				}
				break;
			}
			szMessage.Format(STRING(IDS_RAS_MESSAGE_LOGIN), (LPCTSTR)szServer);
			cDesktopApp.ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		if (nConnectionState == RASCS_Disconnected)
		{
			szMessage.Format(STRING(IDS_RAS_STATE_DISCONNECTED), (LPCTSTR)szServer);
			cDesktopApp.ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		if (nConnectionState > RASCS_Disconnected)
		{
			if (RasGetErrorString(nConnectionState - RASCS_Disconnected, szError, sizeof(szError) / sizeof(TCHAR)) == ERROR_SUCCESS) cDesktopApp.ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError, FALSE);
			szMessage.Format(STRING(IDS_RAS_STATE_FAILED), (LPCTSTR)szServer);
			cDesktopApp.ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		if (nConnectionState == (RASCONNSTATE)-1)
		{
			szMessage.Format(STRING(IDS_RAS_STATE_FAILED), (LPCTSTR)szServer);
			cDesktopApp.ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		if ((CTime::GetCurrentTime().GetTime() - tConnectTime.GetTime() > RASSERVICE_DEFAULT_TIMEOUT  &&  tConnectTime > 0 && nConnectionState < RASCS_Authenticate) || nConnectionState == RASCS_Connected || nConnectionState >= RASCS_Disconnected || nConnectionState == (RASCONNSTATE)-1)
		{
			for (KillTimer((HWND)NULL, cDesktopApp.m_nTimerID[2]), cDesktopApp.m_nTimerID[2] = 0; nConnectionState != RASCS_Connected; )
			{
				cDesktopApp.GetRASService()->StopCall();
				break;
			}
			if (nConnectionState != RASCS_Connected && (nConnectionState <= RASCS_Disconnected || nConnectionState == (RASCONNSTATE)-1))
			{
				if ((cDesktopApp.m_pLoginServerInfo->GetMode() & SERVERPROFILE_BEHAVIOR_TRYALLNUMBERS) == SERVERPROFILE_BEHAVIOR_TRYALLNUMBERS)
				{
					for (nNumber = 0, nNumbers = cDesktopApp.m_pLoginServerInfo->GetPhoneNumbers(szNumbers); nNumber < nNumbers; nNumber++)
					{
						if (!szNumbers.GetAt(nNumber).Compare(szNumber))
						{
							szNumbers.RemoveAt(nNumber);
							break;
						}
					}
					for (cDesktopApp.m_pLoginServerInfo->SetPhoneNumbers(szNumbers); szNumbers.GetSize() > 0; )
					{
						cDesktopApp.LoginTMService(cDesktopApp.m_pLoginServerInfo);
						return;
					}
				}
			}
			if (nConnectionState != RASCS_Connected)
			{
				cDesktopApp.ReportEvent(SYSTEM_WARNING_REMOTENETWORK_LOGIN_FAILURE);
				cDesktopApp.LogoutTMService();
			}
			cDesktopApp.ShowAccountStatus();
		}
	}
}

BOOL CALLBACK CDesktopApp::EnumTopLevelWindows(HWND hWnd, LPARAM lParam)
{
	CWnd  *pWnd;
	CString  szText;
	CString  szTitle;

	for (GetWindowText(hWnd, szTitle.GetBufferSetLength(GetWindowTextLength(hWnd)), GetWindowTextLength(hWnd) + 1), szTitle.ReleaseBuffer(), szText = (LPCTSTR)lParam; szTitle.Right(szText.GetLength()) == szText; )
	{
		if ((pWnd = CWnd::FromHandle(GetLastActivePopup(hWnd))))
		{
			for (; pWnd->IsIconic(); )
			{
				ShowWindow(hWnd, SW_RESTORE);
				break;
			}
			pWnd->SetForegroundWindow();
		}
		return FALSE;
	}
	return TRUE;
}

void *CDesktopApp::operator new(size_t cbObject)
{
	return CAccountsApp::operator new(cbObject);
}

void CDesktopApp::operator delete(void *pObject)
{
	CAccountsApp::operator delete(pObject);
}

BEGIN_MESSAGE_MAP(CDesktopApp, CAccountsApp)
	//{{AFX_MSG_MAP(CDesktopApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesktopApp message handlers

BOOL CDesktopApp::PreTranslateMessage(MSG *pMsg)
{
	CString  szServer;
	CString  szNumber;
	CString  szMessage;
	CTimeKey  tDialinTime;

	if (IsWindow(GetMainWnd()->GetSafeHwnd()))
	{
		if (pMsg->message == WM_KEYDOWN  &&  pMsg->wParam == VK_ESCAPE)
		{
			if (GetRASService()->GetDetails(szServer, szNumber, tDialinTime))
			{
				for (szMessage.Format(STRING(IDS_RAS_STATE_CANCELLED), (LPCTSTR)szServer); GetRASService()->IsCalling() && !GetRASService()->IsAborting(); )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					ShowMessage(szMessage);
					LogoutTMService();
					break;
				}
				return TRUE;
			}
		}
	}
	return CAccountsApp::PreTranslateMessage(pMsg);
}
