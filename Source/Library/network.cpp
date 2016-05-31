// NETWORK.CPP : Network Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the network related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/03/06 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CNetworkInfo

CNetworkInfo::CNetworkInfo()
{
	return;
}

BOOL CNetworkInfo::EnumNetworkResources(CStringArray &szComputers, CStringArray &szPrinters, CStringArray &szDisks) CONST
{
	INT  nDisk;
	INT  nDisks;
	INT  nComputer;
	INT  nComputers;
	CString  szDisk[2];
	CString  szComputer;
	CVersionInfo  cVersionInfo;
	CComputerToken  cComputerToken;

	for (szComputers.RemoveAll(), szPrinters.RemoveAll(), szDisks.RemoveAll(); EnumNetworkResources((LPNETRESOURCE)NULL, szComputers, szPrinters, szDisks); )
	{
		for (nComputer = 0, nComputers = (INT)szComputers.GetSize(), szComputer = cComputerToken.GetComputerName(); nComputer < nComputers; nComputer++)
		{
			if (!szComputers.GetAt(nComputer).CompareNoCase(szComputer)) break;
			continue;
		}
		if (nComputer == nComputers)
		{
			szComputers.InsertAt(0, szComputer);
		}
		for (nDisk = 0, nDisks = (INT)szDisks.GetSize(), szDisk[0] = cVersionInfo.QueryInternalName(); nDisk < nDisks && nDisks > 1; nDisk++)
		{
			if (szDisk[0].GetLength() <= (szDisk[1] = szDisks.GetAt(nDisk)).GetLength() && !szDisk[1].Right(szDisk[0].GetLength()).CompareNoCase(szDisk[0]))
			{
				szDisks.InsertAt(0, szDisk[1]);
				szDisks.RemoveAt(nDisk + 1);
			}
		}
		return TRUE;
	}
	return FALSE;
}

INT CNetworkInfo::EnumNetworkComputers(CStringArray &szComputers) CONST
{
	CStringArray  szDisks;
	CStringArray  szPrinters;

	return((EnumNetworkResources(szComputers, szPrinters, szDisks)) ? (INT)szComputers.GetSize() : 0);
}

INT CNetworkInfo::EnumNetworkPrinters(CStringArray &szPrinters) CONST
{
	CStringArray  szDisks;
	CStringArray  szComputers;

	return((EnumNetworkResources(szComputers, szPrinters, szDisks)) ? (INT)szPrinters.GetSize() : 0);
}

INT CNetworkInfo::EnumNetworkDisks(CStringArray &szDisks) CONST
{
	CStringArray  szPrinters;
	CStringArray  szComputers;

	return((EnumNetworkResources(szComputers, szPrinters, szDisks)) ? (INT)szDisks.GetSize() : 0);
}

BOOL CNetworkInfo::IsComputerOnNetwork(LPCTSTR pszComputerName) CONST
{
	INT  nComputer;
	INT  nComputers;
	CStringArray  szComputers;

	for (nComputer = 0, nComputers = EnumNetworkComputers(szComputers); nComputer < nComputers; nComputer++)
	{
		if (!szComputers.GetAt(nComputer).CompareNoCase(pszComputerName)) break;
		continue;
	}
	return((nComputer < nComputers) ? TRUE : FALSE);
}

BOOL CNetworkInfo::IsPrinterOnNetwork(LPCTSTR pszPrinterName) CONST
{
	INT  nPrinter;
	INT  nPrinters;
	CStringArray  szPrinters;

	for (nPrinter = 0, nPrinters = EnumNetworkPrinters(szPrinters); nPrinter < nPrinters; nPrinter++)
	{
		if (!szPrinters.GetAt(nPrinter).CompareNoCase(pszPrinterName)) break;
		continue;
	}
	return((nPrinter < nPrinters) ? TRUE : FALSE);
}

BOOL CNetworkInfo::IsDiskOnNetwork(LPCTSTR pszDiskName) CONST
{
	INT  nDisk;
	INT  nDisks;
	CStringArray  szDisks;

	for (nDisk = 0, nDisks = EnumNetworkDisks(szDisks); nDisk < nDisks; nDisk++)
	{
		if (!szDisks.GetAt(nDisk).CompareNoCase(pszDiskName)) break;
		continue;
	}
	return((nDisk < nDisks) ? TRUE : FALSE);
}

BOOL CNetworkInfo::EnumNetworkResources(LPNETRESOURCE pInfo, CStringArray &szComputers, CStringArray &szPrinters, CStringArray &szDisks) CONST
{
	INT  nIndex;
	INT  nCount;
	DWORD  dwResource;
	DWORD  dwResources;
	DWORD  cbResources;
	HANDLE  hNetwork;
	CString  szDisk;
	CString  szPrinter;
	CString  szComputer;
	NETRESOURCE  sResources[1024];

	if (WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, pInfo, &hNetwork) == NO_ERROR)
	{
		if (WNetEnumResource(hNetwork, &(dwResources = -1), &sResources, &(cbResources = sizeof(sResources))) == NO_ERROR)
		{
			for (dwResource = 0; dwResource < dwResources; dwResource++)
			{
				if (sResources[dwResource].dwUsage & RESOURCEUSAGE_CONTAINER)
				{
					if (sResources[dwResource].dwDisplayType == RESOURCEDISPLAYTYPE_SERVER)
					{
						for (nIndex = 0, nCount = (INT)szComputers.GetSize(), szComputer = (!_tcsncmp((szComputer = sResources[dwResource].lpRemoteName), STRING(IDS_LOCALNET_DELIMITER), lstrlen(STRING(IDS_LOCALNET_DELIMITER)))) ? szComputer.Mid(lstrlen(STRING(IDS_LOCALNET_DELIMITER))) : szComputer; nIndex < nCount; nIndex++)
						{
							if (!szComputers.GetAt(nIndex).CompareNoCase(szComputer)) break;
							continue;
						}
						if (nIndex == nCount) szComputers.Add(szComputer);
					}
					EnumNetworkResources(&sResources[dwResource], szComputers, szPrinters, szDisks);
					continue;
				}
				if (sResources[dwResource].dwDisplayType == RESOURCEDISPLAYTYPE_SHARE)
				{
					if (sResources[dwResource].dwType == RESOURCETYPE_PRINT)
					{
						for (nIndex = 0, nCount = (INT)szPrinters.GetSize(), szPrinter = sResources[dwResource].lpRemoteName; nIndex < nCount; nIndex++)
						{
							if (!szPrinters.GetAt(nIndex).CompareNoCase(szPrinter)) break;
							continue;
						}
						if (nIndex == nCount) szPrinters.Add(szPrinter);
						continue;
					}
					if (sResources[dwResource].dwType == RESOURCETYPE_DISK)
					{
						for (nIndex = 0, nCount = (INT)szDisks.GetSize(), szDisk = sResources[dwResource].lpRemoteName; nIndex < nCount; nIndex++)
						{
							if (!szDisks.GetAt(nIndex).CompareNoCase(szDisk)) break;
							continue;
						}
						if (nIndex == nCount) szDisks.Add(szDisk);
						continue;
					}
				}
			}
			WNetCloseEnum(hNetwork);
			return TRUE;
		}
		WNetCloseEnum(hNetwork);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CNetworkComputerInfo

CNetworkComputerInfo::CNetworkComputerInfo() : CComputerToken()
{
	return;
}
CNetworkComputerInfo::CNetworkComputerInfo(LPCTSTR pszComputerName) : CComputerToken(pszComputerName)
{
	return;
}

INT CNetworkComputerInfo::EnumNetworkComputerPrinters(CStringArray &szPrinters) CONST
{
	CString  szComputerName;
	NETRESOURCE  sInfo = { RESOURCE_GLOBALNET,RESOURCETYPE_ANY,RESOURCEDISPLAYTYPE_SERVER,RESOURCEUSAGE_CONTAINER };

	for (szPrinters.RemoveAll(); lstrlen((sInfo.lpRemoteName = (LPTSTR)(LPCTSTR)(szComputerName = GetComputerUNCName()))) > 0; )
	{
		EnumNetworkComputerResources(RESOURCETYPE_PRINT, &sInfo, szPrinters);
		break;
	}
	return((INT)szPrinters.GetSize());
}

INT CNetworkComputerInfo::EnumNetworkComputerDisks(CStringArray &szDisks) CONST
{
	INT  nDisk;
	INT  nDisks;
	CString  szDisk[2];
	CString  szComputerName;
	CVersionInfo  cVersionInfo;
	NETRESOURCE  sInfo = { RESOURCE_GLOBALNET,RESOURCETYPE_ANY,RESOURCEDISPLAYTYPE_SERVER,RESOURCEUSAGE_CONTAINER };

	for (szDisks.RemoveAll(); lstrlen((sInfo.lpRemoteName = (LPTSTR)(LPCTSTR)(szComputerName = GetComputerUNCName()))) > 0; )
	{
		for (nDisk = 0, nDisks = EnumNetworkComputerResources(RESOURCETYPE_DISK, &sInfo, szDisks), szDisk[0] = cVersionInfo.QueryInternalName(); nDisk < nDisks && nDisks > 1; nDisk++)
		{
			if (szDisk[0].GetLength() <= (szDisk[1] = szDisks.GetAt(nDisk)).GetLength() && !szDisk[1].Right(szDisk[0].GetLength()).CompareNoCase(szDisk[0]))
			{
				szDisks.InsertAt(0, szDisk[1]);
				szDisks.RemoveAt(nDisk + 1);
			}
		}
		break;
	}
	return((INT)szDisks.GetSize());
}

BOOL CNetworkComputerInfo::IsPrinterOnComputer(LPCTSTR pszPrinterName) CONST
{
	INT  nPrinter;
	INT  nPrinters;
	CStringArray  szPrinters;

	for (nPrinter = 0, nPrinters = EnumNetworkComputerPrinters(szPrinters); nPrinter < nPrinters; nPrinter++)
	{
		if (!szPrinters.GetAt(nPrinter).CompareNoCase(pszPrinterName)) break;
		continue;
	}
	return((nPrinter < nPrinters) ? TRUE : FALSE);
}

BOOL CNetworkComputerInfo::IsDiskOnComputer(LPCTSTR pszDiskName) CONST
{
	INT  nDisk;
	INT  nDisks;
	CStringArray  szDisks;

	for (nDisk = 0, nDisks = EnumNetworkComputerDisks(szDisks); nDisk < nDisks; nDisk++)
	{
		if (!szDisks.GetAt(nDisk).CompareNoCase(pszDiskName)) break;
		continue;
	}
	return((nDisk < nDisks) ? TRUE : FALSE);
}

INT CNetworkComputerInfo::EnumNetworkComputerResources(DWORD dwType, LPNETRESOURCE pInfo, CStringArray &szResources) CONST
{
	DWORD  dwResource;
	DWORD  dwResources;
	DWORD  cbResources;
	HANDLE  hNetwork;
	NETRESOURCE  sResources[1024];

	if (WNetOpenEnum(RESOURCE_GLOBALNET, dwType, 0, pInfo, &hNetwork) == NO_ERROR)
	{
		if (WNetEnumResource(hNetwork, &(dwResources = -1), &sResources, &(cbResources = sizeof(sResources))) == NO_ERROR)
		{
			for (dwResource = 0; dwResource < dwResources; dwResource++)
			{
				if (sResources[dwResource].dwType == dwType)
				{
					if (sResources[dwResource].dwDisplayType == RESOURCEDISPLAYTYPE_SHARE) szResources.Add(sResources[dwResource].lpRemoteName);
					continue;
				}
			}
		}
		WNetCloseEnum(hNetwork);
	}
	return((INT)szResources.GetSize());
}


/////////////////////////////////////////////////////////////////////////////
// CNetworkBrowseService

IMPLEMENT_DYNCREATE(CNetworkBrowseService, CThread)

CStringArray  CNetworkBrowseService::m_szHostAddresses;
CUIntArray  CNetworkBrowseService::m_nIPAddressFlags;

CNetworkBrowseService::CNetworkBrowseService() : CThread()
{
	m_hInitialized = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, TRUE, FALSE, (LPCTSTR)NULL);
	m_bInitialized = FALSE;
}

CNetworkBrowseService::~CNetworkBrowseService()
{
	for (Stop(); m_hInitialized; )
	{
		CloseHandle(m_hInitialized);
		break;
	}
}

BOOL CNetworkBrowseService::InitInstance()
{
	if (Initialize())
	{
		if (m_hInitialized)
		{
			SetEvent(m_hInitialized);
			return CThread::InitInstance();
		}
		return FALSE;
	}
	if (m_hInitialized)
	{
		SetEvent(m_hInitialized);
	}
	return FALSE;
}

BOOL CNetworkBrowseService::Start()
{
	return CreateThread();
}

BOOL CNetworkBrowseService::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CNetworkBrowseService::Run()
{
	CStringArray  szDisks;
	CStringArray  szPrinters;
	CStringArray  szComputers;
	CNetworkInfo  cNetworkInfo;

	do
	{
		if (cNetworkInfo.EnumNetworkResources(szComputers, szPrinters, szDisks))
		{
			CSingleLock  cLock(m_pCriticalSection, TRUE);
			m_szComputers.Copy(szComputers);
			m_szPrinters.Copy(szPrinters);
			m_szDisks.Copy(szDisks);
			m_bInitialized = TRUE;
		}
	} while (Wait(1000 * NETWORKBROWSE_DEFAULT_INTERVAL) == WAIT_TIMEOUT);
	return 0;
}

INT CNetworkBrowseService::EnumNetworkComputers(CStringArray &szComputers) CONST
{
	CComputerToken  cComputerInfo;
	HANDLE  hEvents[2] = { m_hObject,m_hInitialized };

	for (szComputers.RemoveAll(), szComputers.Add(cComputerInfo.GetComputerName()); WaitForMultipleObjects(sizeof(hEvents) / sizeof(HANDLE), hEvents, FALSE, INFINITE) == WAIT_OBJECT_0 + 1; )
	{
		if (m_bInitialized)
		{
			CSingleLock  cLock(m_pCriticalSection, TRUE);
			szComputers.Copy(m_szComputers);
		}
		break;
	}
	return((INT)szComputers.GetSize());
}

INT CNetworkBrowseService::EnumNetworkPrinters(CStringArray &szPrinters) CONST
{
	CNetworkComputerInfo  cComputerInfo;
	HANDLE  hEvents[2] = { m_hObject,m_hInitialized };

	for (szPrinters.RemoveAll(), cComputerInfo.EnumNetworkComputerPrinters(szPrinters); WaitForMultipleObjects(sizeof(hEvents) / sizeof(HANDLE), hEvents, FALSE, INFINITE) == WAIT_OBJECT_0 + 1; )
	{
		if (m_bInitialized)
		{
			CSingleLock  cLock(m_pCriticalSection, TRUE);
			szPrinters.Copy(m_szPrinters);
		}
		break;
	}
	return((INT)szPrinters.GetSize());
}

INT CNetworkBrowseService::EnumNetworkDisks(CStringArray &szDisks) CONST
{
	CNetworkComputerInfo  cComputerInfo;
	HANDLE  hEvents[2] = { m_hObject,m_hInitialized };

	for (szDisks.RemoveAll(), cComputerInfo.EnumNetworkComputerPrinters(szDisks); WaitForMultipleObjects(sizeof(hEvents) / sizeof(HANDLE), hEvents, FALSE, INFINITE) == WAIT_OBJECT_0 + 1; )
	{
		if (m_bInitialized)
		{
			CSingleLock  cLock(m_pCriticalSection, TRUE);
			szDisks.Copy(m_szDisks);
		}
		break;
	}
	return((INT)szDisks.GetSize());
}

BOOL CNetworkBrowseService::IsComputerOnNetwork(LPCTSTR pszComputerName) CONST
{
	INT  nComputer;
	INT  nComputers;
	CStringArray  szComputers;

	for (nComputer = 0, nComputers = EnumNetworkComputers(szComputers); nComputer < nComputers; nComputer++)
	{
		if (!szComputers.GetAt(nComputer).CompareNoCase(pszComputerName)) break;
		continue;
	}
	return((nComputer < nComputers) ? TRUE : FALSE);
}

BOOL CNetworkBrowseService::IsPrinterOnNetwork(LPCTSTR pszPrinterName) CONST
{
	INT  nPrinter;
	INT  nPrinters;
	CStringArray  szPrinters;

	for (nPrinter = 0, nPrinters = EnumNetworkPrinters(szPrinters); nPrinter < nPrinters; nPrinter++)
	{
		if (!szPrinters.GetAt(nPrinter).CompareNoCase(pszPrinterName)) break;
		continue;
	}
	return((nPrinter < nPrinters) ? TRUE : FALSE);
}

BOOL CNetworkBrowseService::IsDiskOnNetwork(LPCTSTR pszDiskName) CONST
{
	INT  nDisk;
	INT  nDisks;
	CStringArray  szDisks;

	for (nDisk = 0, nDisks = EnumNetworkDisks(szDisks); nDisk < nDisks; nDisk++)
	{
		if (!szDisks.GetAt(nDisk).CompareNoCase(pszDiskName)) break;
		continue;
	}
	return((nDisk < nDisks) ? TRUE : FALSE);
}

INT CNetworkBrowseService::EnumHostAddresses(CStringArray &szAddresses, INT nFamily, BOOL bLoopback)
{
	INT  nAddress;
	INT  nAddresses;
	CString  szLoopback[3];

	for (nAddress = 0, nAddresses = (INT)m_szHostAddresses.GetSize(), szLoopback[0] = STRING(IDS_INTERNET_LOOPBACK_IPV4), szLoopback[1] = STRING(IDS_INTERNET_LOOPBACK_IPV6), szLoopback[2] = szLoopback[1].GetAt(1) + szLoopback[1].Right(2), szAddresses.RemoveAll(); nAddress < nAddresses; nAddress++)
	{
		if (nFamily == m_nIPAddressFlags.GetAt(nAddress) || nFamily == AF_UNSPEC)
		{
			if (bLoopback)
			{
				szAddresses.Add(m_szHostAddresses.GetAt(nAddress));
				continue;
			}
			if ((m_nIPAddressFlags.GetAt(nAddress) == AF_INET && m_szHostAddresses.GetAt(nAddress) != szLoopback[0]) || (m_nIPAddressFlags.GetAt(nAddress) == AF_INET6 && m_szHostAddresses.GetAt(nAddress) != szLoopback[1] && m_szHostAddresses.GetAt(nAddress) != szLoopback[2]))
			{
				szAddresses.Add(m_szHostAddresses.GetAt(nAddress));
				continue;
			}
		}
	}
	return((INT)szAddresses.GetSize());
}

BOOL CNetworkBrowseService::IsHost(LPCTSTR pszAddress)
{
	INT  nAddress;
	INT  nAddresses;
	CStringArray  szAddresses;

	for (nAddress = 0, nAddresses = EnumHostAddresses(szAddresses); nAddress < nAddresses; nAddress++)
	{
		if (!szAddresses.GetAt(nAddress).CompareNoCase(pszAddress)) break;
	}
	return(nAddress < nAddresses);
}
BOOL CNetworkBrowseService::IsHost(PSOCKADDR pAddress)
{
	CString  szAddress;
	SOCKADDR_IN  *pIP4Address;
	SOCKADDR_IN6  *pIP6Address;

	if (pAddress->sa_family == AF_INET)
	{
		if ((pIP4Address = (SOCKADDR_IN *)pAddress))
		{
			if (InetNtop(pAddress->sa_family, &pIP4Address->sin_addr, szAddress.GetBufferSetLength(4 * sizeof(pAddress->sa_data)), 4 * sizeof(pAddress->sa_data) + 1))
			{
				szAddress.ReleaseBuffer();
				return IsHost(szAddress);
			}
		}
		return FALSE;
	}
	if (pAddress->sa_family == AF_INET6)
	{
		if ((pIP6Address = (SOCKADDR_IN6 *)pAddress))
		{
			if (InetNtop(pAddress->sa_family, &pIP6Address->sin6_addr, szAddress.GetBufferSetLength(4 * sizeof(pAddress->sa_data)), 4 * sizeof(pAddress->sa_data) + 1))
			{
				szAddress.ReleaseBuffer();
				return IsHost(szAddress);
			}
		}
	}
	return FALSE;
}

USHORT CNetworkBrowseService::IsValidAddress(LPCTSTR pszAddress)
{
	SOCKADDR  sAddress;

	return((IsValidAddress(pszAddress, &sAddress)) ? sAddress.sa_family : AF_UNSPEC);
}
BOOL CNetworkBrowseService::IsValidAddress(LPCTSTR pszAddress, PSOCKADDR pAddress)
{
	SOCKADDR_IN  sIP4Address[2];
	SOCKADDR_IN6  sIP6Address[2];

	for (ZeroMemory(pAddress, sizeof(SOCKADDR)), ZeroMemory(&sIP4Address[0], sizeof(sIP4Address[0])), ZeroMemory(&sIP4Address[1], sizeof(sIP4Address[1])), ZeroMemory(&sIP6Address[0], sizeof(sIP6Address[0])), ZeroMemory(&sIP6Address[1], sizeof(sIP6Address[1])); InetPton((sIP4Address[0].sin_family = AF_INET), pszAddress, &sIP4Address[0].sin_addr) > 0; )
	{
		CopyMemory(pAddress, &sIP4Address[0], sizeof(sIP4Address[0]));
		return(memcmp(&sIP4Address[0].sin_addr, &sIP4Address[1].sin_addr, sizeof(IN_ADDR)) != 0);
	}
	if (InetPton((sIP6Address[0].sin6_family = AF_INET6), pszAddress, &sIP6Address[0].sin6_addr) > 0)
	{
		CopyMemory(pAddress, &sIP6Address[0], sizeof(sIP6Address[0]));
		return(memcmp(&sIP6Address[0].sin6_addr, &sIP6Address[1].sin6_addr, sizeof(IN6_ADDR)) != 0);
	}
	return FALSE;
}

BOOL CNetworkBrowseService::Initialize()
{
	CString  szAddress;
	ADDRINFOT  *pAddress;
	SOCKADDR_IN  *pIP4Address;
	SOCKADDR_IN6  *pIP6Address;
	CSocketAddr  cSocketAddress;
	CHAR  szHostName[MAX_HOSTNAME_LEN];

	if (!gethostname(szHostName, sizeof(szHostName) / sizeof(CHAR)))
	{
		if (!cSocketAddress.FindAddr(CString(szHostName), 0, AI_PASSIVE, 0, 0, 0))
		{
			for ((pAddress = cSocketAddress.GetAddrInfoList()); pAddress; pAddress = pAddress->ai_next)
			{
				if (pAddress->ai_family == AF_INET)
				{
					if ((pIP4Address = (SOCKADDR_IN *)pAddress->ai_addr))
					{
						if (InetNtop(pAddress->ai_family, &pIP4Address->sin_addr, szAddress.GetBufferSetLength(4 * (INT)pAddress->ai_addrlen), 4 * (INT)pAddress->ai_addrlen + 1))
						{
							szAddress.ReleaseBuffer();
							m_szHostAddresses.Add(szAddress);
							m_nIPAddressFlags.Add(pAddress->ai_family);
						}
					}
				}
				if (pAddress->ai_family == AF_INET6)
				{
					if ((pIP6Address = (SOCKADDR_IN6 *)pAddress->ai_addr))
					{
						if (InetNtop(pAddress->ai_family, &pIP6Address->sin6_addr, szAddress.GetBufferSetLength(4 * (INT)pAddress->ai_addrlen), 4 * (INT)pAddress->ai_addrlen + 1))
						{
							szAddress.ReleaseBuffer();
							m_szHostAddresses.Add(szAddress);
							m_nIPAddressFlags.Add(pAddress->ai_family);
						}
					}
				}
			}
			return(m_szHostAddresses.GetSize() > 0);
		}
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CNetworkBrowseService, CThread)
	//{{AFX_MSG_MAP(CNetworkBrowseService)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkBrowseService message handlers
