// NETWORK.H : Network Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the network related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/03/06 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "token.h"
#include "thread.h"


/////////////////////////////////////////////////////////////////////////////
// CNetworkInfo

class AFX_EXT_CLASS CNetworkInfo : public CObject
{
	// Construction
public:
	CNetworkInfo();

	// Attributes
public:

	// Operations
public:
	BOOL EnumNetworkResources(CStringArray &szComputers, CStringArray &szPrinters, CStringArray &szDisks) CONST;
	INT EnumNetworkComputers(CStringArray &szComputers) CONST;
	INT EnumNetworkPrinters(CStringArray &szPrinters) CONST;
	INT EnumNetworkDisks(CStringArray &szDisks) CONST;

	BOOL IsComputerOnNetwork(LPCTSTR pszComputerName) CONST;
	BOOL IsPrinterOnNetwork(LPCTSTR pszPrinterName) CONST;
	BOOL IsDiskOnNetwork(LPCTSTR pszDiskName) CONST;

private:
	BOOL EnumNetworkResources(LPNETRESOURCE pInfo, CStringArray &szComputers, CStringArray &szPrinters, CStringArray &szDisks) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNetworkComputerInfo

class AFX_EXT_CLASS CNetworkComputerInfo : public CComputerToken
{
	// Construction
public:
	CNetworkComputerInfo();
	CNetworkComputerInfo(LPCTSTR pszComputerName);

	// Attributes
public:

	// Operations
public:
	INT EnumNetworkComputerPrinters(CStringArray &szPrinters) CONST;
	INT EnumNetworkComputerDisks(CStringArray &szDisks) CONST;

	BOOL IsPrinterOnComputer(LPCTSTR pszPrinterName) CONST;
	BOOL IsDiskOnComputer(LPCTSTR pszDiskName) CONST;

private:
	INT EnumNetworkComputerResources(DWORD dwType, LPNETRESOURCE pInfo, CStringArray &szResources) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNetworkBrowseService

// Specify the default network browse interval
#define NETWORKBROWSE_DEFAULT_INTERVAL   SECONDSPERMINUTE

class AFX_EXT_CLASS CNetworkBrowseService : public CThread
{
	DECLARE_DYNCREATE(CNetworkBrowseService)

	// Construction
public:
	CNetworkBrowseService();
	~CNetworkBrowseService();

	// Attributes
private:
	static CStringArray  m_szHostAddresses;
	static CUIntArray  m_nIPAddressFlags;
private:
	CStringArray  m_szComputers;
	CStringArray  m_szPrinters;
	CStringArray  m_szDisks;
private:
	HANDLE  m_hInitialized;
	BOOL  m_bInitialized;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	INT EnumNetworkComputers(CStringArray &szComputers) CONST;
	INT EnumNetworkPrinters(CStringArray &szPrinters) CONST;
	INT EnumNetworkDisks(CStringArray &szDisks) CONST;

	BOOL IsComputerOnNetwork(LPCTSTR pszComputerName) CONST;
	BOOL IsPrinterOnNetwork(LPCTSTR pszPrinterName) CONST;
	BOOL IsDiskOnNetwork(LPCTSTR pszDiskName) CONST;

public:
	static INT EnumHostAddresses(CStringArray &szAddresses, INT nFamily = AF_UNSPEC, BOOL bLoopback = TRUE);

	static BOOL IsHost(LPCTSTR pszAddress);
	static BOOL IsHost(PSOCKADDR pAddress);

	static USHORT IsValidAddress(LPCTSTR pszAddress);
	static BOOL IsValidAddress(LPCTSTR pszAddress, PSOCKADDR pAddress);

private:
	static BOOL Initialize();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetworkBrowseService)
public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetworkBrowseService)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __NETWORK_H__
