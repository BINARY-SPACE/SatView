// SIMULATOR.CPP : SatView Simulator Application.
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
* 2010/10/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Simulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// CSimulatorApp
CSimulatorApp  cSimulatorApp;


static UINT BASED_CODE  nMenuIDs[] =
{
	ID_APP_EXIT,IDM_HELP
};

static UINT BASED_CODE nIODeviceToolBarButtons[] =
{
	IDM_IODEVICELABEL,
	IDM_IODEVICE,
	IDM_IODEVICECONFIGURATION,
	ID_SEPARATOR,
	IDM_IODEVICERELOAD,
	ID_SEPARATOR,
	IDM_IODEVICESTART,
	IDM_IODEVICESUSPEND,
	IDM_IODEVICESTOP
};

static UINT BASED_CODE nStatusBarIndicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};



/////////////////////////////////////////////////////////////////////////////
// CIODeviceToolBarComboBoxButton

IMPLEMENT_SERIAL(CIODeviceToolBarComboBoxButton, CMFCToolBarComboBoxButton, TRUE)

CIODeviceToolBarComboBoxButton::CIODeviceToolBarComboBoxButton()
{
	return;
}
CIODeviceToolBarComboBoxButton::CIODeviceToolBarComboBoxButton(UINT uiID, int iImage, DWORD dwStyle, int iWidth) : CMFCToolBarComboBoxButton(uiID, iImage, dwStyle, iWidth)
{
	return;
}

CString CIODeviceToolBarComboBoxButton::ConvertText(LPCTSTR pszText) CONST
{
	INT  nPos[2];
	CString  szText(pszText);

	for (nPos[0] = 0; (nPos[1] = szText.Mid(nPos[0]).Find(STRING(IDS_DEVICENAME_SPECIALCHAR))) >= 0; nPos[0] += nPos[1] + 1)
	{
		szText = szText.Left(nPos[0] + nPos[1] + 1) + STRING(IDS_DEVICENAME_SPECIALCHAR) + szText.Mid(nPos[0] + nPos[1] + 1);
		nPos[1]++;
	}
	return szText;
}

void CIODeviceToolBarComboBoxButton::OnDraw(CDC *pDC, const CRect &rect, CMFCToolBarImages *pImages, BOOL bHorz, BOOL bCustomizeMode, BOOL bHighlight, BOOL bDrawBorder, BOOL bGrayDisabledButtons)
{
	CString  szItem;

	m_strEdit = ConvertText((szItem = m_strEdit));
	CMFCToolBarComboBoxButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);
	m_strEdit = szItem;
}


/////////////////////////////////////////////////////////////////////////////
// CIODevicesToolBar

IMPLEMENT_DYNAMIC(CIODevicesToolBar, CMFCToolBar)

CIODevicesToolBar::CIODevicesToolBar() : CMFCToolBar()
{
	return;
}

CIODevicesToolBar::~CIODevicesToolBar()
{
	INT  nLabel;
	INT  nLabels;
	CWnd  *pLabel;

	for (nLabel = 0, nLabels = (INT)m_pwndLabels.GetSize(), m_nLabelIDs.RemoveAll(); nLabel < nLabels; nLabel++)
	{
		if ((pLabel = (CWnd *)m_pwndLabels.GetAt(nLabel)))
		{
			pLabel->DestroyWindow();
			delete pLabel;
		}
	}
	m_pwndLabels.RemoveAll();
}

INT CIODevicesToolBar::EnumIODevices(CStringArray &szDevices) CONST
{
	INT  nItem;
	INT  nItems;
	CMFCToolBarComboBoxButton  *pComboBox;

	for (szDevices.RemoveAll(); (pComboBox = (CMFCToolBarComboBoxButton *)GetButton(CommandToIndex(IDM_IODEVICE))); )
	{
		for (nItem = 0, nItems = (INT)pComboBox->GetCount(); nItem < nItems; nItem++)
		{
			szDevices.Add(pComboBox->GetItem(nItem));
			continue;
		}
		break;
	}
	return((INT)szDevices.GetSize());
}

BOOL CIODevicesToolBar::SetIODevice(LPCTSTR pszDevice, BOOL bAdd)
{
	INT  nIndex;
	CMFCToolBarComboBoxButton  *pComboBox;

	if ((pComboBox = (CMFCToolBarComboBoxButton *)GetButton(CommandToIndex(IDM_IODEVICE))))
	{
		if ((nIndex = pComboBox->FindItem(pszDevice)) >= 0 || !bAdd)
		{
			pComboBox->SelectItem(nIndex);
			return(nIndex >= 0);
		}
		return((pComboBox->AddItem(pszDevice) >= 0) ? TRUE : FALSE);
	}
	return FALSE;
}

CString CIODevicesToolBar::GetIODevice() CONST
{
	CMFCToolBarComboBoxButton  *pComboBox;

	return(((pComboBox = (CMFCToolBarComboBoxButton *)GetButton(CommandToIndex(IDM_IODEVICE)))) ? pComboBox->GetItem(pComboBox->GetCurSel()) : EMPTYSTRING);
}

INT CIODevicesToolBar::FindIODevice(LPCTSTR pszDevice) CONST
{
	CMFCToolBarComboBoxButton  *pComboBox;

	return(((pComboBox = (CMFCToolBarComboBoxButton *)GetButton(CommandToIndex(IDM_IODEVICE)))) ? pComboBox->FindItem(pszDevice) : -1);
}

BOOL CIODevicesToolBar::Customize()
{
	INT  nLabel;
	INT  nLabels;
	INT  nWidth;
	CWnd  *pLabel;
	CRect  rLabel;
	CRect  rButton;
	CRect  rToolBar;
	CMFCToolBarComboBoxButton  *pComboBox;

	m_nLabelIDs.RemoveAll();
	m_nLabelIDs.Add(CommandToIndex(IDM_IODEVICELABEL));
	for (nLabel = 0, nLabels = (INT)m_nLabelIDs.GetSize(); nLabel < nLabels; nLabel++)
	{
		if ((pLabel = new CWnd) != (CWnd *)NULL)
		{
			if (m_nLabelIDs.GetAt(nLabel) != (UINT)-1)
			{
				GetItemRect(m_nLabelIDs.GetAt(nLabel), rLabel);
				if (pLabel->CreateEx(WS_EX_TRANSPARENT, AfxRegisterWndClass(CS_NOCLOSE, GetSimulatorApp()->LoadStandardCursor(IDC_ARROW)), EMPTYSTRING, WS_CHILD | WS_VISIBLE, rLabel, this, -1))
				{
					m_pwndLabels.Add(pLabel);
					continue;
				}
			}
			delete pLabel;
		}
		break;
	}
	if ((pComboBox = (CMFCToolBarComboBoxButton *)GetButton(CommandToIndex(IDM_IODEVICE))))
	{
		GetWindowRect(rToolBar);
		GetParent()->ScreenToClient(rToolBar);
		GetItemRect(CommandToIndex(IDM_IODEVICE), rButton);
		ReplaceButton(IDM_IODEVICE, CIODeviceToolBarComboBoxButton(IDM_IODEVICE, -1, CBS_DROPDOWNLIST, (nWidth = 12 * rButton.Height())));
		MoveWindow(CRect(rToolBar.left, rToolBar.top, rToolBar.right + nWidth - rButton.Width() + 1, rToolBar.bottom));
		MoveWindow(CRect(rToolBar.left, rToolBar.top, rToolBar.right + nWidth - rButton.Width(), rToolBar.bottom));
		UpdateButton(CommandToIndex(IDM_IODEVICE));
		return((nLabel == nLabels) ? TRUE : FALSE);
	}
	return FALSE;
}

CSize CIODevicesToolBar::CalcSize(BOOL bVertDock)
{
	INT  nLabel;
	INT  nLabels;
	CWnd  *pLabel;
	CRect  rLabel;

	for (nLabel = 0, nLabels = (INT)m_pwndLabels.GetSize(); nLabel < nLabels; nLabel++)
	{
		if ((pLabel = (CWnd *)m_pwndLabels.GetAt(nLabel)))
		{
			GetItemRect(m_nLabelIDs.GetAt(nLabel), rLabel);
			pLabel->MoveWindow(rLabel);
		}
	}
	return CMFCToolBar::CalcSize(bVertDock);
}

BEGIN_MESSAGE_MAP(CIODevicesToolBar, CMFCToolBar)
	//{{AFX_MSG_MAP(CIODevicesToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIODevicesToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainWnd

IMPLEMENT_DYNCREATE(CMainWnd, CLocaleMDIFrameWnd)

CMainWnd::CMainWnd()
{
	m_nExitID = 0;
	m_nIODeviceTimerID = 0;
	m_pwndMessages = (CSimulatorMessagesConsoleWnd *)NULL;
	m_pCriticalSection = new CCriticalSection;
}

CMainWnd::~CMainWnd()
{
	delete m_pCriticalSection;
}

VOID CMainWnd::Initialize(LPCTSTR pszSpacecraft, LPCTSTR pszDevice)
{
	INT  nDevice;
	INT  nDevices;
	CString  szExit;
	CString  szDevice;
	CString  szMessage;
	CString  szFileName;
	CString  szSpacecraft;
	CIODevice  *pIODevice;
	CDisplayWnd  *pDisplayWnd;
	CVersionInfo  cVersionInfo;

	for (szSpacecraft = pszSpacecraft, szDevice = pszDevice, szExit.Format(STRING(IDS_APPLICATIONINFO_COMMANDTERMINATION_SIMULATOR), (LPCTSTR)cVersionInfo.QueryProductName()), m_nExitID = RegisterWindowMessage(szExit); szDevice.IsEmpty(); )
	{
		szDevice = STRING(IDS_DEVICENAME_DEFAULT);
		break;
	}
	for (nDevice = 0, nDevices = (!szSpacecraft.IsEmpty()) ? (INT)m_pIODevices.GetSize() : -1; nDevice < nDevices; nDevice++)
	{
		if ((pIODevice = m_pIODevices.GetAt(nDevice)) && !pIODevice->GetDeviceName().Compare(szDevice) && SetIODevice(pIODevice->GetDeviceBrand())) break;
		continue;
	}
	for (szFileName = (nDevice < nDevices) ? FindSatelliteData(szSpacecraft) : EMPTYSTRING, UpdateWindow(); !szFileName.IsEmpty(); )
	{
		if ((pDisplayWnd = (GetSimulatorApp()->OpenDocumentFile(szFileName)) ? (CDisplayWnd *)MDIGetActive() : (CDisplayWnd *)NULL))
		{
			pDisplayWnd->Start();
			return;
		}
		szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE), (LPCTSTR)szSpacecraft);
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
		break;
	}
	if (nDevice == nDevices)
	{
		szMessage.Format(STRING(IDS_DEVICEERROR_FIND), (LPCTSTR)szDevice);
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), szMessage);
	}
	if (szFileName.IsEmpty() && !szSpacecraft.IsEmpty())
	{
		szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE), (LPCTSTR)szSpacecraft);
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
	}
}

VOID CMainWnd::UpdateTitle(LPCTSTR pszDocument)
{
	CString  szTitle;

	for (szTitle.Format(STRING(IDS_SIMULATOR_TITLE), pszDocument, (LPCTSTR)GetAppTitle()); !lstrlen(pszDocument); )
	{
		szTitle = GetAppTitle();
		break;
	}
	SetWindowText(szTitle);
}

BOOL CMainWnd::SetIODevice(CONST CIODevice *pDevice)
{
	INT  nDevice;
	INT  nDevices;
	CIODevice  *pIODevice;

	for (nDevice = 0, nDevices = (INT)m_pIODevices.GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pIODevice = m_pIODevices.GetAt(nDevice)) && pIODevice->GetDeviceBrand() == pDevice->GetDeviceBrand() && pIODevice->Copy(pDevice)) break;
		continue;
	}
	return((nDevice < nDevices) ? TRUE : FALSE);
}
BOOL CMainWnd::SetIODevice(LPCTSTR pszDevice)
{
	return m_wndIODevicesToolBar.SetIODevice(pszDevice);
}

BOOL CMainWnd::GetIODevice(CIODevice *pDevice) CONST
{
	INT  nDevice;
	INT  nDevices;
	CIODevice  *pIODevice;

	for (nDevice = 0, nDevices = (INT)m_pIODevices.GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pIODevice = m_pIODevices.GetAt(nDevice)) && pIODevice->GetDeviceBrand() == GetIODevice() && pDevice->Copy(pIODevice))
		{
			pDevice->SetDeviceModule(m_szIODevices.GetAt(m_wndIODevicesToolBar.FindIODevice(m_wndIODevicesToolBar.GetIODevice())));
			break;
		}
	}
	return((nDevice < nDevices) ? TRUE : FALSE);
}
CString CMainWnd::GetIODevice() CONST
{
	return m_wndIODevicesToolBar.GetIODevice();
}

INT CMainWnd::EnumIODevices(CStringArray &szDevices) CONST
{
	return m_wndIODevicesToolBar.EnumIODevices(szDevices);
}

VOID CMainWnd::ShowMessage(LPCTSTR pszMessage)
{
	if (IsSameThread())
	{
		m_pwndMessages->ShowMessage(pszMessage);
		return;
	}
	AddMessageToBuffer(pszMessage);
}
VOID CMainWnd::ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage)
{
	if (IsSameThread())
	{
		m_pwndMessages->ShowMessage(pszType, pszMessage);
		return;
	}
	AddMessageToBuffer(pszType, pszMessage);
}
VOID CMainWnd::ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage)
{
	if (IsSameThread())
	{
		m_pwndMessages->ShowMessage(pszType, pszSource, pszMessage);
		return;
	}
	AddMessageToBuffer(pszType, pszSource, pszMessage);
}

VOID CALLBACK CMainWnd::ShowIODeviceStatus(LPCTSTR pszStatus, UINT nStatus)
{
	return;
}

VOID CALLBACK CMainWnd::ShowIODeviceMessage(LPCTSTR pszMessage, UINT nMessageType)
{
	GetSimulatorApp()->ShowMessage(TranslateMessageType(nMessageType), STRING(IDS_MESSAGESOURCE_DATACONSOLE), pszMessage);
}

BOOL CMainWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd *pParentWnd, CCreateContext *pContext)
{
	INT  nIndex;
	INT  nCount;
	CMFCToolBarImages  *pImages;
	CByteArray  nDevicesData;
	CProfile  cProfile;

	if (CLocaleMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle | WS_HSCROLL | WS_VSCROLL, pParentWnd, pContext) && m_wndIODevicesToolBar.Customize())
	{
		for (; cProfile.GetIODevicesData(nDevicesData); )
		{
			m_pIODevices.Unmap(nDevicesData);
			break;
		}
		for (EnumIODevices(); (m_pwndMessages = new CSimulatorMessagesConsoleWnd); )
		{
			if (m_pwndMessages->Create(AfxRegisterWndClass(CS_NOCLOSE | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW), STRING(IDS_MESSAGESWINDOW_TITLE), WS_CHILD | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE, rectDefault, this))
			{
				if ((pImages = CMFCToolBar::GetImages()) && pImages->Load(IDB_MAINFRAMESMALLIMAGES, (HINSTANCE)NULL, TRUE))
				{
					for (nIndex = 0, nCount = sizeof(nMenuIDs) / sizeof(UINT); nIndex < nCount; nIndex++)
					{
						GetCmdMgr()->SetCmdImage(nMenuIDs[nIndex], pImages->GetCount() - nCount + nIndex, FALSE);
						continue;
					}
				}
				return TRUE;
			}
			delete m_pwndMessages;
			break;
		}
	}
	return FALSE;
}

VOID CMainWnd::EnumIODevices()
{
	INT  nDevice;
	INT  nDevices;
	CString  szDevice;
	CIODevice  *pDevice;
	CFileFindEx  cFileFind;
	TCHAR  szFileName[MAX_PATH];

	if (GetModuleFileName((HMODULE)NULL, szFileName, sizeof(szFileName) / sizeof(TCHAR)) > 0)
	{
		if (cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile())
		{
			EnumIODevices(cFileFind.GetRoot());
			cFileFind.Close();
		}
	}
	for (nDevice = 0, nDevices = (INT)m_pIODevices.GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = m_pIODevices.GetAt(nDevice)) != (CIODevice *)NULL)
		{
			if (m_wndIODevicesToolBar.FindIODevice(pDevice->GetDeviceBrand()) < 0)
			{
				m_pIODevices.RemoveAt(nDevice);
				delete pDevice;
				nDevices--;
				nDevice--;
				continue;
			}
			szDevice = (szDevice.IsEmpty()) ? pDevice->GetDeviceBrand() : szDevice;
		}
	}
	m_wndIODevicesToolBar.SetIODevice(szDevice);
}
VOID CMainWnd::EnumIODevices(LPCTSTR pszDirectory)
{
	BOOL  bFound;
	CFileFind  cFileFind;

	if (cFileFind.FindFile(CString(pszDirectory) + STRING(IDS_FILESEARCH_ALL)))
	{
		for (bFound = cFileFind.FindNextFile(); TRUE; bFound = cFileFind.FindNextFile())
		{
			if (!cFileFind.IsDots())
			{
				if (!cFileFind.IsDirectory())
				{
					if (!cFileFind.GetFileName().Right(cFileFind.GetFileName().GetLength() - cFileFind.GetFileTitle().GetLength()).CompareNoCase(CString(STRING(IDS_FILESEARCH_DLL)).Mid(lstrlen(STRING(IDS_FILESEARCH_DLL)) / 2 - 1))) EnumIODevices(cFileFind.GetRoot(), cFileFind.GetFileName());
					if (bFound) continue;
					break;
				}
				EnumIODevices(cFileFind.GetFilePath());
			}
			if (!bFound) break;
		}
		cFileFind.Close();
	}
}
VOID CMainWnd::EnumIODevices(LPCTSTR pszDirectory, LPCTSTR pszFileName)
{
	INT  nDevice[2];
	INT  nDevices[2];
	LPTSTR  *pIODevices;
	CString  szFileName;
	CString  szIODevices;
	CIODevice  *pDevice[2];
	HINSTANCE  hIODevices;
	INT(*pEnumIODevices)(LPTSTR *ppszProducts, INT nCount);

	for (szFileName = pszDirectory, szFileName += pszFileName; !m_szIODevices.GetSize() || m_szIODevices.GetAt(m_szIODevices.GetUpperBound()).CompareNoCase(szFileName) != 0; )
	{
		if ((hIODevices = AfxLoadLibrary(szFileName)))
		{
#ifndef UNICODE
			szIODevices = STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS);
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS), -1, (LPSTR)szIODevices.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS))), lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szIODevices.ReleaseBuffer();
#endif
			if ((pEnumIODevices = (INT(__cdecl *)(LPTSTR *ppszProducts, INT nCount)) GetProcAddress(hIODevices, (LPCSTR)(LPCTSTR)szIODevices)))
			{
				if ((nDevices[0] = (*pEnumIODevices)((LPTSTR *)NULL, 0)) > 0)
				{
					if ((pIODevices = (LPTSTR *)GlobalAlloc(GPTR, nDevices[0] * sizeof(LPTSTR))))
					{
						for (nDevice[0] = 0, nDevices[0] = (*pEnumIODevices)(pIODevices, nDevices[0]); nDevice[0] < nDevices[0]; nDevice[0]++)
						{
							if (m_wndIODevicesToolBar.FindIODevice(pIODevices[nDevice[0]]) < 0)
							{
								for (nDevice[1] = 0, nDevices[1] = (INT)m_pIODevices.GetSize(); nDevice[1] < nDevices[1]; nDevice[1]++)
								{
									if ((pDevice[0] = m_pIODevices.GetAt(nDevice[1])) && !pDevice[0]->GetDeviceBrand().CompareNoCase(pIODevices[nDevice[0]])) break;
									continue;
								}
								for (; nDevice[1] == nDevices[1]; )
								{
									if ((pDevice[1] = new CIODevice))
									{
										if (pDevice[1]->Open(szFileName, pIODevices[nDevice[0]]))
										{
											if (pDevice[1]->Initialize(IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_DATASERVICE_TRANSFERFRAMES, 0, 0, ShowIODeviceStatus, (IODEVICEDATASTATUSPROCEDURE)NULL, ShowIODeviceMessage))
											{
												pDevice[1]->SetDeviceName(STRING(IDS_DEVICENAME_DEFAULT));
												if (m_pIODevices.Add(pDevice[1]) >= 0)
												{
													pDevice[1]->Close();
													break;
												}
											}
											pDevice[1]->Close();
										}
										delete pDevice[1];
									}
									nDevices[1] = -1;
									break;
								}
								for (; nDevice[1] < nDevices[1]; )
								{
									if ((pDevice[1] = m_pIODevices.GetAt(nDevice[1])))
									{
										if (pDevice[1]->Open(szFileName, pIODevices[nDevice[0]]))
										{
											if (pDevice[1]->Initialize(IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_DATASERVICE_TRANSFERFRAMES, 0, 0, ShowIODeviceStatus, (IODEVICEDATASTATUSPROCEDURE)NULL, ShowIODeviceMessage))
											{
												pDevice[1]->Close();
												nDevice[1] = nDevices[1];
												break;
											}
											pDevice[1]->Close();
										}
									}
									m_pIODevices.RemoveAt(nDevice[1]);
									delete pDevice[1];
									nDevices[1]--;
									nDevice[1]--;
									break;
								}
								if (nDevice[1] == nDevices[1])
								{
									m_wndIODevicesToolBar.SetIODevice(pIODevices[nDevice[0]], TRUE);
									m_szIODevices.Add(szFileName);
								}
							}
						}
						for (nDevice[0] = 0; nDevice[0] < nDevices[0]; nDevice[0]++)
						{
							GlobalFree(pIODevices[nDevice[0]]);
							continue;
						}
						GlobalFree(pIODevices);
					}
				}
			}
			AfxFreeLibrary(hIODevices);
		}
		break;
	}
}

BOOL CMainWnd::AddMessageToBuffer(LPCTSTR pszMessage)
{
	return AddMessageToBuffer(EMPTYSTRING, EMPTYSTRING, pszMessage);
}
BOOL CMainWnd::AddMessageToBuffer(LPCTSTR pszType, LPCTSTR pszMessage)
{
	return AddMessageToBuffer(pszType, EMPTYSTRING, pszMessage);
}
BOOL CMainWnd::AddMessageToBuffer(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_szIODeviceMessages.Add(EncodeMessage(pszType, pszSource, pszMessage)); !m_nIODeviceTimerID; ) return(((m_nIODeviceTimerID = SetTimer(0, 0, NULL)) != 0) ? TRUE : FALSE);
	return TRUE;
}

BOOL CMainWnd::RemoveMessageFromBuffer(CString &szMessage)
{
	CString  szType;
	CString  szSource;

	return RemoveMessageFromBuffer(szType, szSource, szMessage);
}
BOOL CMainWnd::RemoveMessageFromBuffer(CString &szType, CString &szMessage)
{
	CString  szSource;

	return RemoveMessageFromBuffer(szType, szSource, szMessage);
}
BOOL CMainWnd::RemoveMessageFromBuffer(CString &szType, CString &szSource, CString &szMessage)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_szIODeviceMessages.GetSize() > 0)
	{
		if (DecodeMessage(m_szIODeviceMessages.GetAt(0), szType, szSource, szMessage))
		{
			m_szIODeviceMessages.RemoveAt(0);
			return TRUE;
		}
		m_szIODeviceMessages.RemoveAt(0);
	}
	return FALSE;
}

CString CMainWnd::EncodeMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage) CONST
{
	CString  szText(pszMessage);

	return(szText + TAB + pszType + TAB + pszSource);
}

BOOL CMainWnd::DecodeMessage(LPCTSTR pszItem, CString &szType, CString &szSource, CString &szMessage) CONST
{
	INT  nPos;
	CString  szText(pszItem);

	for (szType.Empty(), szSource.Empty(), szMessage.Empty(); lstrlen(pszItem) > 0; )
	{
		for (; (nPos = szText.Find(TAB)) >= 0; )
		{
			szMessage = szText.Left(nPos);
			break;
		}
		for (szText = (nPos >= 0) ? szText.Mid(nPos + 1) : EMPTYSTRING; (nPos = szText.Find(TAB)) >= 0; )
		{
			szType = szText.Left(nPos);
			break;
		}
		szSource = (nPos >= 0) ? szText.Mid(nPos + 1) : EMPTYSTRING;
		return TRUE;
	}
	return FALSE;
}

CString CMainWnd::FindSatelliteData(LPCTSTR pszSatellite) CONST
{
	CModuleToken  cModuleToken;

	return FindSatelliteData(cModuleToken.GetModuleFileRoot(), pszSatellite);
}
CString CMainWnd::FindSatelliteData(LPCTSTR pszDirectory, LPCTSTR pszSatellite) CONST
{
	INT  nPos;
	BOOL  bFound;
	CFile  cFile;
	DWORD  cbData;
	LPBYTE  pszData;
	CString  szFileName;
	CString  szFileData;
	CString  szSatellite;
	CString  szSearchedFiles;
	CLogicalDrives  cDrives;
	CFileFindEx  cFileFind;

	for (szSearchedFiles = (!(szSearchedFiles = pszDirectory).IsEmpty() && szSearchedFiles.GetAt(szSearchedFiles.GetLength() - 1) == cDrives.GetPathDelimiter()) ? szSearchedFiles.Left(szSearchedFiles.GetLength() - 1) : szSearchedFiles, szSearchedFiles += STRING(IDS_FILESEARCH_TXT); cFileFind.FindFile(szSearchedFiles); )
	{
		for (bFound = cFileFind.FindNextFile(); TRUE; bFound = cFileFind.FindNextFile())
		{
			if (!cFileFind.IsDirectory() && !cFileFind.IsDots())
			{
				if (cFile.Open(cFileFind.GetFilePath(), CFile::modeRead | CFile::shareDenyWrite))
				{
					if ((pszData = (LPBYTE)GlobalAlloc(GPTR, (SIZE_T)(cFile.GetLength() + 1))))
					{
						if (ReadFile(cFile.m_hFile, pszData, (DWORD)cFile.GetLength(), &cbData, (LPOVERLAPPED)NULL))
						{
#ifndef UNICODE
							if (IsTextUnicode((LPCVOID)(szFileData = (LPCSTR)pszData), (INT)cFile.GetLength(), (LPINT)NULL))
							{
								WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pszData, -1, (LPSTR)szFileData.GetBufferSetLength((INT)wcslen((LPCWSTR)pszData)), (INT)wcslen((LPCWSTR)pszData), (LPCSTR)NULL, (LPBOOL)NULL);
								szFileData.ReleaseBuffer();
							}
#else
							if (!IsTextUnicode((LPCVOID)(szFileData = (LPCWSTR)pszData), (INT)cFile.GetLength(), (LPINT)NULL))
							{
								MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pszData, -1, (LPWSTR)szFileData.GetBufferSetLength((INT)strlen((LPCSTR)pszData)), (INT)strlen((LPCSTR)pszData));
								szFileData.ReleaseBuffer();
							}
#endif
							if ((nPos = szFileData.Find(STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE))) >= 0 && szFileData.Find(STRING(IDS_DEVICEDATA_KEYWORD_TYPE)) >= 0 && szFileData.Find(STRING(IDS_DEVICEDATA_KEYWORD_FORMAT)) >= 0 && szFileData.Find(STRING(IDS_DEVICEDATA_KEYWORD_OBRT)) >= 0)
							{
								for (nPos += lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE)), szSatellite.Empty(); nPos < szFileData.GetLength(); nPos++)
								{
									if (szFileData.GetAt(nPos) == CR || szFileData.GetAt(nPos) == EOL) break;
									if (_istspace(szFileData.GetAt(nPos)) && szSatellite.IsEmpty()) continue;
									if (!_istspace(szFileData.GetAt(nPos)))
									{
										szSatellite += szFileData.GetAt(nPos);
										continue;
									}
								}
								if (!szSatellite.CompareNoCase(pszSatellite))
								{
									szFileName = cFileFind.GetFilePath();
									GlobalFree(pszData);
									cFileFind.Close();
									return szFileName;
								}
							}
						}
						GlobalFree(pszData);
					}
					cFile.Close();
				}
			}
			if (!bFound) break;
			continue;
		}
		cFileFind.Close();
		break;
	}
	for (szSearchedFiles = (!(szSearchedFiles = pszDirectory).IsEmpty() && szSearchedFiles.GetAt(szSearchedFiles.GetLength() - 1) == cDrives.GetPathDelimiter()) ? szSearchedFiles.Left(szSearchedFiles.GetLength() - 1) : szSearchedFiles, szSearchedFiles += STRING(IDS_FILESEARCH_ALL); cFileFind.FindFile(szSearchedFiles); )
	{
		for (bFound = cFileFind.FindNextFile(), szFileName.Empty(); szFileName.IsEmpty(); bFound = cFileFind.FindNextFile())
		{
			if (cFileFind.IsDirectory() && !cFileFind.IsDots()) szFileName = FindSatelliteData(cFileFind.GetFilePath(), pszSatellite);
			if (!bFound) break;
		}
		cFileFind.Close();
		return szFileName;
	}
	return EMPTYSTRING;
}

HMENU CMainWnd::GetWindowMenuPopup(HMENU hMenuBar)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CMenu  cMenu;
	CMenu  *pSubMenu;

	if (cMenu.Attach(hMenuBar))
	{
		for (nItem = 0, nItems = cMenu.GetMenuItemCount(); nItem < nItems; nItem++)
		{
			if ((pSubMenu = cMenu.GetSubMenu(nItem)) != (CMenu *)NULL)
			{
				for (nIndex = pSubMenu->GetMenuItemCount(); nIndex >= 0; nIndex--)
				{
					if (pSubMenu->GetMenuItemID(nIndex) >= AFX_IDM_WINDOW_FIRST  &&  pSubMenu->GetMenuItemID(nIndex) <= AFX_IDM_WINDOW_LAST) break;
					continue;
				}
				if (nIndex >= 0)
				{
					cMenu.Detach();
					return pSubMenu->GetSafeHmenu();
				}
			}
		}
		cMenu.Detach();
	}
	return((HMENU)NULL);
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

void CMainWnd::GetMessageString(UINT nID, CString &rMessage) const
{
	if (nID == (UINT)-1) return;
	if (nID >= IDM_FIRSTIODEVICE  &&  nID <= IDM_LASTIODEVICE)
	{
		rMessage = STRING(IDS_STATUSBAR_DEVICES);
		return;
	}
	CLocaleMDIFrameWnd::GetMessageString(nID, rMessage);
}

BOOL CMainWnd::IsSameThread() CONST
{
	return(GetWindowThreadProcessId(GetSafeHwnd(), (LPDWORD)NULL) == GetCurrentThreadId());
}

CString CMainWnd::TranslateMessageType(UINT nMessageType)
{
	return((nMessageType == IODEVICE_MESSAGETYPE_ERROR) ? STRING(IDS_MESSAGETYPE_ERROR) : ((nMessageType == IODEVICE_MESSAGETYPE_WARNING) ? STRING(IDS_MESSAGETYPE_WARNING) : ((nMessageType == IODEVICE_MESSAGETYPE_SUCCESS) ? STRING(IDS_MESSAGETYPE_SUCCESS) : ((nMessageType == IODEVICE_MESSAGETYPE_INFORMATIONAL) ? STRING(IDS_MESSAGETYPE_INFORMATIONAL) : STRING(IDS_MESSAGETYPE_NONE)))));
}

BOOL CALLBACK CMainWnd::EnumDisplayWindows(HWND hWnd, LPARAM lParam)
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(hWnd)) && pDisplayWnd->IsKindOf(RUNTIME_CLASS(CSimulatorDataConsoleWnd))) pDisplayWnd->Stop();
	return TRUE;
}

LRESULT CMainWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == m_nExitID)
	{
		EnumChildWindows(GetSafeHwnd(), EnumDisplayWindows, (LPARAM)NULL);
		PostMessage(WM_CLOSE);
		return TRUE;
	}
	return CLocaleMDIFrameWnd::WindowProc(message, wParam, lParam);
}

BEGIN_MESSAGE_MAP(CMainWnd, CLocaleMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_CREATE()
	ON_WM_INITMENUPOPUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND(IDM_IODEVICECONFIGURATION, OnDeviceConfiguration)
	ON_COMMAND(IDM_IODEVICERELOAD, OnDeviceReload)
	ON_COMMAND(IDM_IODEVICESTART, OnDeviceStart)
	ON_COMMAND(IDM_IODEVICESUSPEND, OnDeviceSuspend)
	ON_COMMAND(IDM_IODEVICESTOP, OnDeviceStop)
	ON_COMMAND(IDM_VIEW_TOOLBARS, OnViewToolbars)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_UPDATE_COMMAND_UI(IDM_IODEVICELABEL, OnUpdateDeviceLabel)
	ON_UPDATE_COMMAND_UI(IDM_IODEVICE, OnUpdateDevice)
	ON_UPDATE_COMMAND_UI(IDM_IODEVICECONFIGURATION, OnUpdateDeviceConfiguration)
	ON_UPDATE_COMMAND_UI(IDM_IODEVICERELOAD, OnUpdateDeviceReload)
	ON_UPDATE_COMMAND_UI(IDM_IODEVICESTART, OnUpdateDeviceStart)
	ON_UPDATE_COMMAND_UI(IDM_IODEVICESUSPEND, OnUpdateDeviceSuspend)
	ON_UPDATE_COMMAND_UI(IDM_IODEVICESTOP, OnUpdateDeviceStop)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_TOOLBARS, OnUpdateViewToolbars)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, OnUpdateNewWindow)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_CASCADE, OnUpdateCascadeWindow)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_TILE_HORZ, OnUpdateTileWindow)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_ARRANGE, OnUpdateArrangeWindow)
	ON_UPDATE_COMMAND_UI(IDM_HELP, OnUpdateHelp)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTIODEVICE, IDM_LASTIODEVICE, OnUpdateIODevices)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWnd message handlers

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect  rBar;

	for (CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7)); CLocaleMDIFrameWnd::OnCreate(lpCreateStruct) != -1; )
	{
		if (m_wndMenuBar.Create(this) && m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_CONTROLBAR_FIRST) && m_wndToolBar.LoadToolBar(IDR_MAINFRAME) && m_wndIODevicesToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_CONTROLBAR_LAST) && m_wndIODevicesToolBar.LoadToolBar(IDR_IODEVICETOOLBAR) && m_wndStatusBar.Create(this) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, sizeof(nStatusBarIndicators) / sizeof(UINT)))
		{
			for (EnableDocking(CBRS_ALIGN_ANY), EnableAutoHidePanes(CBRS_ALIGN_ANY), m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY), m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY), m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY), m_wndToolBar.SetWindowText(STRING(IDS_TOOLBAR_TITLE)), m_wndIODevicesToolBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM), m_wndIODevicesToolBar.SetWindowText(STRING(IDS_DEVICESTOOLBAR_TITLE)), m_wndStatusBar.GetWindowRect(rBar); rBar.Height() > 0; )
			{
				m_wndStatusBar.SetPaneStyle(m_wndStatusBar.CommandToIndex(ID_SEPARATOR), SBPS_NOBORDERS | SBPS_STRETCH);
				m_wndStatusBar.SetPaneWidth(m_wndStatusBar.CommandToIndex(ID_SEPARATOR), 2 * rBar.Height());
				break;
			}
			DockPane(&m_wndMenuBar);
			DockPane(&m_wndToolBar);
			DockPane(&m_wndIODevicesToolBar);
			CDockingManager::SetDockingMode(DT_SMART);
			CMFCPopupMenu::SetForceMenuFocus(FALSE);
			return 0;
		}
		break;
	}
	return -1;
}

LRESULT CMainWnd::OnToolbarReset(WPARAM wParam, LPARAM lParam)
{
	INT  nID;
	INT  nIDs;

	for (nID = 0, nIDs = sizeof(nIODeviceToolBarButtons) / sizeof(nIODeviceToolBarButtons[0]); nID < nIDs; nID++)
	{
		if (nIODeviceToolBarButtons[nID] == IDM_IODEVICELABEL  &&  nID < m_wndIODevicesToolBar.GetCount() && m_wndIODevicesToolBar.GetItemID(nID) != 0)
		{
			m_wndIODevicesToolBar.ReplaceButton(nIODeviceToolBarButtons[nID], CMFCToolBarButton(nIODeviceToolBarButtons[nID], -1, STRING(IDS_DEVICESTOOLBAR_LABEL), TRUE));
			continue;
		}
		if (nIODeviceToolBarButtons[nID] == IDM_IODEVICE  &&  nID < m_wndIODevicesToolBar.GetCount() && m_wndIODevicesToolBar.GetItemID(nID) != 0)
		{
			m_wndIODevicesToolBar.ReplaceButton(nIODeviceToolBarButtons[nID], CIODeviceToolBarComboBoxButton(nIODeviceToolBarButtons[nID], -1));
			continue;
		}
		if (nIODeviceToolBarButtons[nID] == IDM_IODEVICECONFIGURATION  &&  nID < m_wndIODevicesToolBar.GetCount() && m_wndIODevicesToolBar.GetItemID(nID) != 0)
		{
			m_wndIODevicesToolBar.ReplaceButton(nIODeviceToolBarButtons[nID], CMFCToolBarButton(nIODeviceToolBarButtons[nID], -1, STRING(IDS_DEVICESTOOLBAR_CONFIGURATION), TRUE));
			continue;
		}
		if (nIODeviceToolBarButtons[nID] == IDM_IODEVICERELOAD  &&  nID < m_wndIODevicesToolBar.GetCount() && m_wndIODevicesToolBar.GetItemID(nID) != 0)
		{
			m_wndIODevicesToolBar.ReplaceButton(nIODeviceToolBarButtons[nID], CMFCToolBarButton(nIODeviceToolBarButtons[nID], -1, STRING(IDS_DEVICESTOOLBAR_RELOAD), TRUE));
			continue;
		}
	}
	return TRUE;
}

void CMainWnd::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UINT  nItem;
	UINT  nItems;
	UINT  nItemID;
	CMenu  *pSubMenu;
	CString  szMenuItem[2];
	CStringArray  szDevices;
	MENUITEMINFO  sMenuItemInfo;
	CVersionInfo  cVersionInfo;

	for (nItem = 0, nItems = (pPopupMenu->GetMenuItemID(0) == IDM_FIRSTIODEVICE) ? EnumIODevices(szDevices) : 0; nItem < nItems; nItem++)
	{
		if ((nItemID = pPopupMenu->GetMenuItemID(nItem)) >= IDM_FIRSTIODEVICE  &&  nItemID <= IDM_LASTIODEVICE)
		{
			pPopupMenu->ModifyMenu(nItem, MF_BYPOSITION | MF_STRING | MF_ENABLED, nItemID, szDevices.GetAt(nItem));
			continue;
		}
		pPopupMenu->AppendMenu(MF_STRING, IDM_FIRSTIODEVICE + nItem, szDevices.GetAt(nItem));
		continue;
	}
	while (nItems < (UINT)pPopupMenu->GetMenuItemCount() && nItems > 0)
	{
		if (!pPopupMenu->DeleteMenu(nItems, MF_BYPOSITION)) break;
		continue;
	}
	for (nItem = 0, nItems = pPopupMenu->GetMenuItemCount(); nItem < nItems && !bSysMenu; nItem++)
	{
		if ((pSubMenu = pPopupMenu->GetSubMenu(nItem)))
		{
			OnInitMenuPopup(pSubMenu, nItem, bSysMenu);
			pPopupMenu->EnableMenuItem(nItem, MF_BYPOSITION | GetSubMenuState(pSubMenu));
			continue;
		}
	}
	for (sMenuItemInfo.cbSize = sizeof(sMenuItemInfo), sMenuItemInfo.fMask = MIIM_ID; pPopupMenu->GetMenuItemInfo(IDM_ABOUT, &sMenuItemInfo); )
	{
		if (pPopupMenu->GetMenuString(IDM_ABOUT, szMenuItem[0], MF_BYCOMMAND))
		{
			szMenuItem[1].Format(szMenuItem[0], (LPCTSTR)GetAppTitle());
			pPopupMenu->ModifyMenu(IDM_ABOUT, MF_BYCOMMAND | MF_STRING, IDM_ABOUT, szMenuItem[1]);
		}
		break;
	}
	CLocaleMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

BOOL CMainWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CStringArray  szDevices;

	if (wParam >= IDM_FIRSTIODEVICE  &&  wParam <= IDM_LASTIODEVICE  &&  wParam - IDM_FIRSTIODEVICE < (WPARAM)EnumIODevices(szDevices)) SetIODevice(szDevices.GetAt(wParam - IDM_FIRSTIODEVICE));
	return CLocaleMDIFrameWnd::OnCommand(wParam, lParam);
}

void CMainWnd::OnDeviceConfiguration()
{
	INT  nIndex;
	INT  nDevice;
	INT  nDevices;
	CString  szDevice;
	CString  szMessage;
	CIODevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)m_pIODevices.GetSize(), nIndex = m_wndIODevicesToolBar.FindIODevice((szDevice = m_wndIODevicesToolBar.GetIODevice())); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = m_pIODevices.GetAt(nDevice)) && pDevice->GetDeviceBrand() == szDevice) break;
		continue;
	}
	if ((pDevice = m_pIODevices.GetAt(nDevice)))
	{
		if (pDevice->Open(m_szIODevices.GetAt(nIndex), szDevice))
		{
			pDevice->Configure(this);
			pDevice->Close();
			return;
		}
		szMessage.Format(STRING(IDS_DEVICEERROR_OPEN), (LPCTSTR)pDevice->GetDeviceName());
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), pDevice->GetDeviceBrand(), szMessage);
		return;
	}
	if ((pDevice = new CIODevice))
	{
		if (pDevice->Open(m_szIODevices.GetAt(nIndex), szDevice))
		{
			for (pDevice->SetDeviceName(STRING(IDS_DEVICENAME_DEFAULT)); pDevice->Initialize(IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_DATASERVICE_TRANSFERFRAMES, 0, 0, ShowIODeviceStatus, (IODEVICEDATASTATUSPROCEDURE)NULL, ShowIODeviceMessage); )
			{
				for (pDevice->Configure(this); m_pIODevices.Add(pDevice) >= 0; )
				{
					pDevice->Close();
					return;
				}
				break;
			}
			pDevice->Close();
		}
		delete pDevice;
	}
	ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), szDevice, STRING(IDS_DEVICEERROR_CONFIGURATION));
}

void CMainWnd::OnDeviceReload()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->Reload();
		return;
	}
}

void CMainWnd::OnDeviceStart()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->Start();
		return;
	}
}

void CMainWnd::OnDeviceSuspend()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->Suspend();
		return;
	}
}

void CMainWnd::OnDeviceStop()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->Stop();
		return;
	}
}

void CMainWnd::OnViewToolbars()
{
	m_wndToolBar.ShowPane(!m_wndToolBar.IsVisible(), FALSE, FALSE);
	m_wndIODevicesToolBar.ShowPane(!m_wndIODevicesToolBar.IsVisible(), FALSE, FALSE);
}

void CMainWnd::OnTimer(UINT_PTR nTimerID)
{
	CString  szType;
	CString  szSource;
	CString  szMessage;

	if (!nTimerID)
	{
		for (KillTimer(0), m_nIODeviceTimerID = 0; RemoveMessageFromBuffer(szType, szSource, szMessage); )
		{
			if (szType.IsEmpty() && szSource.IsEmpty())
			{
				ShowMessage(szMessage);
				continue;
			}
			if (szSource.IsEmpty())
			{
				ShowMessage(szType, szMessage);
				continue;
			}
			ShowMessage(szType, szSource, szMessage);
		}
	}
}

void CMainWnd::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowHelp();
}

void CMainWnd::OnDestroy()
{
	CProfile  cProfile;
	CByteArray  nDevicesData;
	CHourglassCursor  cCursor;

	if (m_nIODeviceTimerID != 0)
	{
		m_nIODeviceTimerID = 0;
		KillTimer(0);
	}
	for (ShowMessage(STRING(IDS_MESSAGETYPE_INFORMATIONAL), STRING(IDS_MESSAGE_GOODBYE)); m_pIODevices.Map(nDevicesData); )
	{
		cProfile.SetIODevicesData(nDevicesData);
		break;
	}
	m_pwndMessages->DestroyWindow();
	CLocaleMDIFrameWnd::OnDestroy();
}

void CMainWnd::OnUpdateDeviceLabel(CCmdUI *pCmdUI)
{
	CStringArray  szDevices;

	pCmdUI->Enable(m_wndIODevicesToolBar.EnumIODevices(szDevices) > 0);
}

void CMainWnd::OnUpdateDevice(CCmdUI *pCmdUI)
{
	CStringArray  szDevices;

	pCmdUI->Enable(m_wndIODevicesToolBar.EnumIODevices(szDevices) > 0);
}

void CMainWnd::OnUpdateDeviceConfiguration(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_wndIODevicesToolBar.GetIODevice().IsEmpty());
}

void CMainWnd::OnUpdateDeviceReload(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && m_pIODevices.GetSize() > 0) ? pDisplayWnd->CanReload() : FALSE);
}

void CMainWnd::OnUpdateDeviceStart(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && m_pIODevices.GetSize() > 0) ? pDisplayWnd->CanStart() : FALSE);
}

void CMainWnd::OnUpdateDeviceSuspend(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && m_pIODevices.GetSize() > 0) ? pDisplayWnd->CanSuspend() : FALSE);
}

void CMainWnd::OnUpdateDeviceStop(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && m_pIODevices.GetSize() > 0) ? pDisplayWnd->CanStop() : FALSE);
}

void CMainWnd::OnUpdateIODevices(CCmdUI *pCmdUI)
{
	INT  nItem;
	INT  nItems;
	CString  szDevice;
	CStringArray  szDevices;

	for (nItem = 0, nItems = EnumIODevices(szDevices); nItem < nItems; nItem++)
	{
		if (szDevices.GetAt(nItem) == GetIODevice()) break;
		continue;
	}
	pCmdUI->Enable(nItems > 0);
	pCmdUI->SetCheck(pCmdUI->m_nID == IDM_FIRSTIODEVICE + nItem);
}

void CMainWnd::OnUpdateViewToolbars(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndToolBar.IsVisible() || m_wndIODevicesToolBar.IsVisible());
}

void CMainWnd::OnUpdateNewWindow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->IsKindOf(RUNTIME_CLASS(CSimulatorDataConsoleWnd)) : FALSE);
}

void CMainWnd::OnUpdateCascadeWindow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->IsKindOf(RUNTIME_CLASS(CSimulatorDataConsoleWnd)) : FALSE);
}

void CMainWnd::OnUpdateTileWindow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->IsKindOf(RUNTIME_CLASS(CSimulatorDataConsoleWnd)) : FALSE);
}

void CMainWnd::OnUpdateArrangeWindow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->IsKindOf(RUNTIME_CLASS(CSimulatorDataConsoleWnd)) : FALSE);
}

void CMainWnd::OnUpdateHelp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsHelpAvailable());
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorAppCommandLineInfo

CSimulatorAppCommandLineInfo::CSimulatorAppCommandLineInfo() : CCommandLineInfo()
{
	m_bSpacecraft = FALSE;
	m_bDevice = FALSE;
}

CString CSimulatorAppCommandLineInfo::GetSpacecraft() CONST
{
	return m_szSpacecraft;
}

CString CSimulatorAppCommandLineInfo::GetDevice() CONST
{
	return m_szDevice;
}

BOOL CSimulatorAppCommandLineInfo::IsValid() CONST
{
	return !m_szSpacecraft.IsEmpty() && !m_szDevice.IsEmpty();
}

void CSimulatorAppCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast)
{
	INT  nPos;
	CString  szFlag[2];

	for (szFlag[0] = pszParam, szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_SPACECRAFT); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (m_szSpacecraft = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !m_szSpacecraft.IsEmpty() && m_szSpacecraft.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			m_szSpacecraft = m_szSpacecraft.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bSpacecraft = TRUE;
			break;
		}
		if (!m_szSpacecraft.IsEmpty() && m_szSpacecraft.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bSpacecraft)
		{
			m_szSpacecraft = m_szSpacecraft.Left(m_szSpacecraft.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bSpacecraft = FALSE;
		}
		m_bDevice = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_DEVICE); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (m_szDevice = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !m_szDevice.IsEmpty() && m_szDevice.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			m_szDevice = m_szDevice.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bDevice = TRUE;
			break;
		}
		if (!m_szDevice.IsEmpty() && m_szDevice.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bDevice)
		{
			m_szDevice = m_szDevice.Left(m_szDevice.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bDevice = FALSE;
		}
		m_bSpacecraft = FALSE;
		return;
	}
	if (szFlag[0].GetLength() > lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)) && szFlag[0].Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))
	{
		m_szSpacecraft += (m_bSpacecraft) ? (SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : EMPTYSTRING;
		m_szDevice += (m_bDevice) ? (SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : EMPTYSTRING;
		m_bSpacecraft = m_bDevice = FALSE;
	}
	CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorApp

IMPLEMENT_DYNAMIC(CSimulatorApp, CAccountsApp)

CSimulatorApp::CSimulatorApp() : CAccountsApp()
{
	return;
}

BOOL CSimulatorApp::InitInstance()
{
	CMainWnd  *pMainWnd;
	CMFCToolTipInfo  ttParams;
	CMultiDocTemplate  *pDocTemplate;
	CSimulatorAppCommandLineInfo  cStartupInfo;

	if (CAccountsApp::InitInstance())
	{
		for (InitCommonControls(), AfxSocketInit(), ParseCommandLine(cStartupInfo), EnableHtmlHelp(), ttParams.m_bVislManagerTheme = TRUE, GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams); (pDocTemplate = new CMultiDocTemplate(IDR_SIMULATORDATACONSOLE, RUNTIME_CLASS(CSimulatorDataConsoleDocument), RUNTIME_CLASS(CSimulatorDataConsoleWnd), RUNTIME_CLASS(CSimulatorDataConsoleView))); )
		{
			for (AddDocTemplate(pDocTemplate); (m_pMainWnd = (CWnd *)(pMainWnd = new CMainWnd)) && pMainWnd->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW); )
			{
				ShowMessage(STRING(IDS_MESSAGETYPE_INFORMATIONAL), STRING(IDS_MESSAGE_WELCOME));
				pMainWnd->Initialize(cStartupInfo.GetSpacecraft(), cStartupInfo.GetDevice());
				pMainWnd->ShowWindow(m_nCmdShow);
				pMainWnd->UpdateWindow();
				return TRUE;
			}
			m_pMainWnd = (CWnd *)NULL;
			break;
		}
	}
	return FALSE;
}

BOOL CSimulatorApp::SetIODevice(LPCTSTR pszDevice)
{
	return GetMainWnd()->SetIODevice(pszDevice);
}

CString CSimulatorApp::GetIODevice() CONST
{
	return GetMainWnd()->GetIODevice();
}

INT CSimulatorApp::EnumIODevices(CStringArray &szDevices) CONST
{
	return GetMainWnd()->EnumIODevices(szDevices);
}

VOID CSimulatorApp::ShowMessage(LPCTSTR pszMessage)
{
	GetMainWnd()->ShowMessage(pszMessage);
}
VOID CSimulatorApp::ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage)
{
	GetMainWnd()->ShowMessage(pszType, pszMessage);
}
VOID CSimulatorApp::ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage)
{
	GetMainWnd()->ShowMessage(pszType, pszSource, pszMessage);
}

BOOL CSimulatorApp::ShowHelp(LPCTSTR pszTopic)
{
	if (IsHelpAvailable())
	{
		HtmlHelp((DWORD_PTR)pszTopic, HH_DISPLAY_TOPIC);
		return TRUE;
	}
	return FALSE;
}

BOOL CSimulatorApp::IsHelpAvailable() CONST
{
	CFileFindEx  cFileFind;

	if (cFileFind.FindFile(GetHelpFileName()))
	{
		cFileFind.Close();
		return TRUE;
	}
	return FALSE;
}

CMainWnd *CSimulatorApp::GetMainWnd() CONST
{
	return((CMainWnd *)m_pMainWnd);
}

BEGIN_MESSAGE_MAP(CSimulatorApp, CAccountsApp)
	//{{AFX_MSG_MAP(CSimulatorApp)
	ON_COMMAND(IDM_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, OnFilePrintSetup)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorApp message handlers

void CSimulatorApp::OnAppAbout()
{
	CAboutDialog  cAboutDialog;

	cAboutDialog.DoModal();
}

void CSimulatorApp::OnFileOpen()
{
	CHourglassCursor  cCursor;

	CAccountsApp::OnFileOpen();
}

void CSimulatorApp::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	CMainWnd  *pMainWnd;

	pCmdUI->Enable(((pMainWnd = GetMainWnd()) && !pMainWnd->GetIODevice().IsEmpty()) ? TRUE : FALSE);
}

void CSimulatorApp::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	CMainWnd  *pMainWnd;

	pCmdUI->Enable(((pMainWnd = GetMainWnd()) && !pMainWnd->GetIODevice().IsEmpty()) ? TRUE : FALSE);
}
