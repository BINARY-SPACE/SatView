// TM.H : Telemetry Data Processing Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telemetry data processing related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/22 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TM_H__
#define __TM_H__

#include "jcode.h"
#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CAutomationClientInfo

class CAutomationClientInfo : public CObject
{
	// Construction
public:
	CAutomationClientInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbUserName;
		INT  cbPassword;
		INT  cbPermissions;
		BOOL  bEncryption;
		BOOL  bBanned;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szUserName;
	CString  m_szPassword;
	CUIntArray  m_nPermissions;
	BOOL  m_bEncryption;
	BOOL  m_bBanned;

	// Operations
public:
	VOID SetUserName(LPCTSTR pszName);
	CString GetUserName() CONST;
	VOID SetPassword(LPCTSTR pszPassword);
	CString GetPassword() CONST;
	VOID SetPermissions(CONST CUIntArray &nPermissions);
	INT GetPermissions(CUIntArray &nPermissions) CONST;
	BOOL HasPermission(LPCTSTR pszPermission) CONST;

	VOID Encrypt(BOOL bEnable = TRUE);
	BOOL UsesEncryption() CONST;

	VOID Ban(BOOL bBan = TRUE);
	BOOL IsBanned() CONST;

	VOID Copy(CONST CAutomationClientInfo *pClientInfo);
	BOOL Compare(CONST CAutomationClientInfo *pClientInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationClients

class CAutomationClients : public CPtrArray
{
	// Construction
public:
	CAutomationClients();
	~CAutomationClients();

	// Attributes
public:

	// Operations
public:
	INT Add(CAutomationClientInfo *pClientInfo);

	INT Find(LPCTSTR pszName) CONST;

	CAutomationClientInfo *GetAt(INT nIndex) CONST;
	CAutomationClientInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CAutomationClients *pClients);
	BOOL Compare(CONST CAutomationClients *pClients) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationTaskSocket command target

// Specify the automation task socket related timer identifiers
#define AUTOMATIONTASKSOCKET_DATASTREAM_TIMERID   10000
#define AUTOMATIONTASKSOCKET_DATASTREAM_TIMEOUT   1000

class CAutomationTaskSocket : public CSocket
{
	DECLARE_DYNCREATE(CAutomationTaskSocket)

	// Construction
public:
	CAutomationTaskSocket();

	// Attributes
private:
	BOOL  m_bSendData;
	UINT_PTR  m_nTimerID;
	CByteArray  m_nData;

	// Operations
public:
	BOOL Open();
	BOOL IsOpen() CONST;
	virtual void Close();

	INT Send(CONST CByteArray &nData);
	INT Receive(CByteArray &nData);

private:
	BOOL ParseRequest(CONST CByteArray &nData);
	BOOL ReplyRequest(LPCTSTR pszServiceName, LPCTSTR pszAcceptance, LPCTSTR pszMessage, BOOL bUnicode);

	CString ExtractParameterValue(LPCTSTR pszServiceBlock, LPCTSTR pszValueName, CString &szMessage) CONST;
	INT EnumParameterValue(LPCTSTR pszParameterValue, CStringArray &szValues) CONST;

	VOID SkipSpaces(LPCTSTR pszText, INT &nPos) CONST;

	// Overrides
public:
	virtual BOOL OnMessagePending();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationTaskSockets

class CAutomationTaskSockets : public CPtrArray
{
	// Construction
public:
	CAutomationTaskSockets();
	~CAutomationTaskSockets();

	// Attributes
public:

	// Operations
public:
	BOOL Add(CAutomationTaskSocket *pSocket);

	CAutomationTaskSocket *GetAt(INT nIndex) CONST;
	CAutomationTaskSocket *operator[](INT nIndex) CONST;

	VOID RemoveAll();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationServiceSocket command target

class CAutomationServiceSocket : public CSocket
{
	DECLARE_DYNCREATE(CAutomationServiceSocket)

	// Construction
public:

	// Attributes
private:
	CAutomationTaskSockets  m_pTaskSockets;

	// Operations
public:
	BOOL Open();
	virtual VOID Close();

	// Overrides
public:
	virtual void OnAccept(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationServiceThread thread

class CAutomationServiceThread : public CThread
{
	DECLARE_DYNCREATE(CAutomationServiceThread)

	friend class CAutomationService;

	// Construction
public:
	CAutomationServiceThread();

	// Attributes
private:
	CAutomationServiceSocket  m_cSocket;
private:
	CEvent  m_bInitialization[2];
	CEvent  m_bUpdate;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL Update();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutomationServiceThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAutomationServiceThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationService

// Specify the automation service ports
#define AUTOMATION_SERVICE_FIRSTPORT   1024
#define AUTOMATION_SERVICE_LASTPORT   65535
#define AUTOMATION_SERVICE_DEFAULTPORT   50000
// Specify the automation service buffer sizes
#define AUTOMATION_SERVICE_MINIMUMBUFFERSIZE   (16*1024)
#define AUTOMATION_SERVICE_MAXIMUMBUFFERSIZE   (256*1024)
#define AUTOMATION_SERVICE_DEFAULTBUFFERSIZE   (32*1024)
// Specify the automation service timeouts
#define AUTOMATION_SERVICE_MINIMUMTIMEOUT   1
#define AUTOMATION_SERVICE_MAXIMUMTIMEOUT   SECONDSPERMINUTE
#define AUTOMATION_SERVICE_DEFAULTTIMEOUT   2

class CAutomationService : public CObject
{
	// Construction
public:
	CAutomationService();

	// Attributes
private:
	typedef struct tagSERVICEINFO {
		INT  cbSize;
		INT  cbClients;
		UINT  nPort;
		UINT  nBufferSize;
		TIMEKEY  tTimeout;
		BOOL  bEnabled;
	} SERVICEINFO, *PSERVICEINFO, *LPSERVICEINFO;
private:
	UINT  m_nPort;
	UINT  m_nBufferSize;
	CTimeSpan  m_tTimeout;
	CAutomationClients  m_pClients;
	BOOL  m_bEnabled;
private:
	CAutomationServiceThread  m_cServiceThread;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL SetPort(UINT nPort);
	BOOL GetPort(UINT &nPort) CONST;
	UINT GetPort() CONST;
	BOOL SetBufferSize(UINT nSize);
	BOOL GetBufferSize(UINT &nSize) CONST;
	UINT GetBufferSize() CONST;
	BOOL SetTimeout(CONST CTimeSpan &tTimeout);
	BOOL GetTimeout(CTimeSpan &tTimeout) CONST;
	CTimeSpan GetTimeout() CONST;

	BOOL SetClients(CONST CAutomationClients &pClients);
	INT GetClients(CAutomationClients &pClients) CONST;

	BOOL SetServiceInfo(CONST CByteArray &nInfo);
	BOOL GetServiceInfo(CByteArray &nInfo) CONST;
	BOOL UpdateServiceInfo(BOOL bSave = TRUE);

	VOID Enable(BOOL bEnable = TRUE);
	BOOL IsEnabled() CONST;

	BOOL Lock();
	BOOL Unlock();

private:
	BOOL SaveServiceInfo();
	BOOL LoadServiceInfo();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsServiceThread thread

class CMemoryDumpsServiceThread : public CThread
{
	DECLARE_DYNCREATE(CMemoryDumpsServiceThread)

	friend class CMemoryDumpsService;

	// Construction
public:
	CMemoryDumpsServiceThread();

	// Attributes
private:
	CMemoryDumps  m_pMemoryDumps;
	BOOL  m_bAvailable;

	// Operations
public:
	BOOL Start(HANDLE bUpdate);
	BOOL Stop();

	BOOL DoFTPTransfer(CONST CMemoryDump *pDump);

	BOOL ResetFTPQueue();

private:
	DWORD FTPTransfers();

	INT EnumFTPRecipients(CONST CMemoryDump *pDump, CStringArray &szServers, CStringArray &szDirectories, CStringArray &szUsers, CStringArray &szPasswords) CONST;
	INT ExtractFTPRecipientsData(LPCTSTR pszData, CStringArray &szData) CONST;

	CString ExtractFTPDirectory(LPCTSTR pszPathName) CONST;
	CString ExtractFTPFileName(LPCTSTR pszPathName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsServiceThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMemoryDumpsServiceThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsService

// Specify the memory dumps service charsets
#define MEMORYDUMPS_SERVICE_UNICODECHARSET   1
#define MEMORYDUMPS_SERVICE_ASCIICHARSET   2
// Specify the memory dumps service availability codes
#define MEMORYDUMPS_SERVICE_UNLIMITEDAVAILABILITY   (1<<0)
#define MEMORYDUMPS_SERVICE_DAILYAVAILABILITY   (1<<1)
#define MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY   (1<<2)
#define MEMORYDUMPS_SERVICE_NOAVAILABILITY   (1<<3)
#define MEMORYDUMPS_SERVICE_AUDITAVAILABILITY   (1<<4)
// Specify the memory dumps service error codes
#define MEMORYDUMPS_SERVICE_SUCCESS   (1<<0)
#define MEMORYDUMPS_SERVICE_NOTAVAILABLE   (1<<1)
#define MEMORYDUMPS_SERVICE_ERROR   (1<<2)

class CMemoryDumpsService : public CObject
{
	// Construction
public:
	CMemoryDumpsService();

	// Attributes
private:
	typedef struct tagSERVICEINFO {
		INT  cbSize;
		INT  cbDumps;
		UINT  nCode;
		UINT  nCharset;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} SERVICEINFO, *PSERVICEINFO, *LPSERVICEINFO;
private:
	UINT  m_nCode;
	UINT  m_nCharset;
	CTimeSpan  m_tStartTime;
	CTimeSpan  m_tStopTime;
	CMemoryDumps  m_pMemoryDumps;
	CMemoryDumpsServiceThread  m_cServiceThread;
private:
	CEvent  m_bUpdate;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL SetCharset(UINT nCharset);
	BOOL GetCharset(UINT &nCharset) CONST;
	UINT GetCharset() CONST;
	BOOL SetAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetMemoryDumps(CONST CMemoryDumps &pMemoryDumps);
	BOOL GetMemoryDumps(CMemoryDumps &pMemoryDumps) CONST;

	UINT Update(CTMEnvironment *pTMEnvironment);
	UINT Update(CTMEnvironment *pTMEnvironment, CMemoryDumps &pMemoryDumps);

	VOID Alert(CONST CMemoryDump *pDump, BOOL bSuccess);

	BOOL SetServiceInfo(CONST CByteArray &nInfo);
	BOOL GetServiceInfo(CByteArray &nInfo) CONST;
	BOOL UpdateServiceInfo(BOOL bSave = TRUE);

	BOOL ResetFTPQueue();

	BOOL IsAvailable() CONST;

	BOOL Lock();
	BOOL Unlock();

private:
	BOOL SaveServiceInfo();
	BOOL LoadServiceInfo();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPDataProfile

class CTPEPDataProfile : public CObject
{
	// Construction
public:

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbIDs;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CStringArray  m_szIDs;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetIDs(CONST CStringArray &szIDs);
	INT GetIDs(CStringArray &szIDs);

	VOID Reset();

	VOID Copy(CONST CTPEPDataProfile *pProfile);
	BOOL Compare(CONST CTPEPDataProfile *pProfile);

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPDataProfiles

class CTPEPDataProfiles : public CPtrArray
{
	// Construction
public:
	CTPEPDataProfiles();
	~CTPEPDataProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CTPEPDataProfile *pProfile);

	INT Find(LPCTSTR pszName) CONST;

	CTPEPDataProfile *GetAt(INT nIndex) CONST;
	CTPEPDataProfile *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTPEPDataProfiles *pProfiles);
	BOOL Compare(CONST CTPEPDataProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServerThread thread

// Specify the TPEP retrieve random data generation intervals
#define TPEPSERVERTHREAD_RANDOMDATA_MINIMUMINTERVAL   200
#define TPEPSERVERTHREAD_RANDOMDATA_MAXIMUMINTERVAL   1000

class CTPEPServerThread : public CThread
{
	DECLARE_DYNCREATE(CTPEPServerThread)

	// Construction
public:
	CTPEPServerThread();
	~CTPEPServerThread();

	// Attributes
private:
	CTMEnvironment  m_cTMEnvironment;
	CHistoryTMProcessEngine  m_cTMProcessEngine;
private:
	CTPEPConnection  m_cConnection;
private:
	CEvent  m_bFlag;

	// Operations
public:
	BOOL Start(CONST CTPEPConnection *pConnection);
	BOOL Stop();

private:
	BOOL PrepareRandomData(CStringArray &szSamples);
	BOOL GenerateRandomData(LPCTSTR pszSample, CTMEnvironment *pTMEnvironment);

	BOOL Update(CTMEnvironment *pTMEnvironment, UINT nError = 0, BOOL bCache = FALSE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPServerThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPServerThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServerSocket command target

// Specify the TPEP server socket related timer identifiers
#define TPEPSERVERSOCKET_DATASTREAM_TIMERID   10001
#define TPEPSERVERSOCKET_DATASTREAM_TIMEOUT   1000

class CTPEPServerSocket : public CSocket
{
	DECLARE_DYNCREATE(CTPEPServerSocket)

	// Construction
public:
	CTPEPServerSocket();

	// Attributes
private:
	UINT  m_nCharset;
	UINT  m_nSequence;
	BOOL  m_bSendData[2];
	BOOL  m_bReset;
	CString  m_szLogin;
	UINT_PTR  m_nTimerID;
	CPtrArray  m_pDisplays;
	CTPEPConnection  m_cConnection;
	CTPEPServerThread  m_cServerThread;
private:
	CTMUnitCache  m_pTMUnits;
	CTMParameters  m_pTMParameters;

	// Operations
public:
	BOOL Open();
	BOOL IsOpen() CONST;
	virtual void Close();

	VOID Reset();
	VOID ShutDown();

	BOOL IsInitialized() CONST;

	BOOL GetClient(CString &szClient) CONST;
	BOOL GetAddress(CString &szAddress) CONST;
	BOOL GetSecurityInfo(UINT &nCode, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetConnectionInfo(CString &szClient, CTPEPConnection *pConnection) CONST;
	BOOL GetProperties(CString &szClient, CString &szAddress, UINT &nCode, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	VOID UpdateConnection();
	BOOL UpdateConnection(CONST CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError);
	BOOL AuthorizeConnection();
	BOOL AuthorizeConnection(CTimeSpan &tDelay);
	BOOL AuthorizeConnection(DWORD dwContext);

	INT Send(CONST CByteArray &nData);
	INT Receive(CByteArray &nData);

	BOOL Attach(CDisplayWnd *pDisplayWnd);
	BOOL Detach(CDisplayWnd *pDisplayWnd);

private:
	UINT ParsePacket(CONST CByteArray &nData);
	BOOL ParseTimeKey(LPCTSTR pszString, INT &nPos, CTimeKey &tTimeKey);

	BOOL CheckServiceAvailability() CONST;
	INT CheckServiceAvailability(CString &szError) CONST;
	BOOL CheckServiceSecurity() CONST;
	INT CheckServiceSecurity(CString &szError) CONST;
	BOOL CheckServiceSecurity(CTimeSpan &tDelay) CONST;
	INT CheckServiceSecurity(CTimeSpan &tDelay, CString &szError) CONST;

	VOID UpdateCharset(CONST CByteArray &nData);

	BOOL ConstructPacket(UINT nError, CByteArray &nData);
	BOOL ConstructPacket(CONST CTMUnit *pTMUnit, CONST CTMParameters *pTMParameters, CByteArray &nData, BOOL bFilter = TRUE);
	CString ConstructPIE(CONST CTMUnit *pTMUnit, CONST CTMParameters *pTMParameters, LPCTSTR pszParameter, UINT nPIEType, UINT nSampleLimit = 0, BOOL bUnchanged = FALSE);

	VOID ConvertPacket(CONST CByteArray &nData, CString &szPacket) CONST;
	BOOL ConvertPacket(LPCTSTR pszPacket, CByteArray &nData) CONST;

	INT SkipSpaces(LPCTSTR pszString, INT &nPos) CONST;
	INT SkipNumber(LPCTSTR pszString, INT &nPos) CONST;

	VOID ShowLoginMessage();
	VOID ShowLogoutMessage();

	VOID Alert(LPCTSTR pszAlert);

	BOOL UpdateStatistics(INT cbData = 0);

	VOID UpdateDisplays();

	// Overrides
public:
	virtual BOOL OnMessagePending();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServerSockets

class CTPEPServerSockets : public CPtrArray
{
	// Construction
public:
	CTPEPServerSockets();
	~CTPEPServerSockets();

	// Attributes
public:

	// Operations
public:
	BOOL AddConnection(CTPEPServerSocket *pSocket);
	BOOL AttachConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL RemoveConnection(LPCTSTR pszClient, CTPEPConnection *pConnection);

	INT EnumConnections(CStringArray &szClients, CTPEPConnections &pConnections) CONST;

	VOID UpdateConnections(CTimeSpan &tDelay);
	BOOL UpdateConnections(CONST CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError);

	CTPEPServerSocket *GetAt(INT nIndex) CONST;
	CTPEPServerSocket *operator[](INT nIndex) CONST;

	VOID RemoveAll();

private:
	INT FindConnection(LPCTSTR pszClient, CONST CTPEPConnection *pConnection, INT nIndex = 0) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPClientSocket command target

// Specify the TPEP client socket related timer identifiers
#define TPEPCLIENTSOCKET_CONNECTION_TIMERID   10002
#define TPEPCLIENTSOCKET_CONNECTION_TIMEOUT   1000

class CTPEPClientSocket : public CSocket
{
	DECLARE_DYNCREATE(CTPEPClientSocket)

	// Construction
public:
	CTPEPClientSocket();

	// Attributes
private:
	CString  m_szData;
	CString  m_szServer;
	UINT_PTR  m_nTimerID;
	CPtrArray  m_pDisplays;
	CTPEPConnection  m_cConnection;

	// Operations
public:
	BOOL Open(LPCTSTR pszServer, CONST CTPEPConnection *pConnection);
	BOOL IsOpen() CONST;
	virtual void Close();

	BOOL Connect(LPCTSTR pszAddress, UINT nPort, CONST CTimeSpan &tTimeout);

	VOID Reset();

	BOOL IsInitialized() CONST;

	VOID SetProperties(LPCTSTR pszServer, CONST CTPEPConnection *pConnection);
	BOOL GetProperties(CString &szServer, CTPEPConnection *pConnection) CONST;

	INT Send(CONST CByteArray &nData);
	INT Receive(CByteArray &nData);

	BOOL Attach(CDisplayWnd *pDisplayWnd);
	BOOL Detach(CDisplayWnd *pDisplayWnd);

private:
	BOOL ConstructPacket(CONST CTPEPConnection *pConnection, CByteArray &nData) CONST;

	VOID ConvertPacket(CONST CByteArray &nData, CString &szData) CONST;
	BOOL ConvertPacket(LPCTSTR pszData, CByteArray &nData) CONST;

	BOOL UpdateStatistics(INT cbData = 0);

	// Overrides
public:
	virtual BOOL OnMessagePending();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPClientSockets

class CTPEPClientSockets : public CPtrArray
{
	// Construction
public:
	CTPEPClientSockets();
	~CTPEPClientSockets();

	// Attributes
public:

	// Operations
public:
	BOOL AddConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL AttachConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL RemoveConnection(LPCTSTR pszServer, CTPEPConnection *pConnection);

	INT EnumConnections(CStringArray &szServers, CTPEPConnections &pConnections) CONST;

	VOID UpdateConnections();

	CTPEPClientSocket *GetAt(INT nIndex) CONST;
	CTPEPClientSocket *operator[](INT nIndex) CONST;

	VOID RemoveAll();

private:
	INT FindConnection(LPCTSTR pszServer, CONST CTPEPConnection *pConnection, INT nIndex = 0) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceSocket command target

class CTPEPServiceSocket : public CSocket
{
	DECLARE_DYNCREATE(CTPEPServiceSocket)

	// Construction
public:

	// Attributes
private:
	CTPEPClientSockets  m_pClientSockets;
	CTPEPServerSockets  m_pServerSockets;

	// Operations
public:
	BOOL Open();
	virtual VOID Close();

	BOOL AddClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL AttachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL RemoveClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection);

	BOOL AddServerConnection(CTPEPServerSocket *pSocket);
	BOOL AttachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL RemoveServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection);

	INT EnumClientConnections(CStringArray &szServers, CTPEPConnections &pConnections) CONST;
	INT EnumServerConnections(CStringArray &szClients, CTPEPConnections &pConnections) CONST;

	VOID UpdateClientConnections();
	VOID UpdateServerConnections(CTimeSpan &tDelay);
	BOOL UpdateConnections(CONST CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError);

	// Overrides
public:
	virtual void OnAccept(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceStackElement

class CTPEPServiceStackElement : public CObject
{
	// Construction
public:
	CTPEPServiceStackElement();

	// Attributes
public:
	enum TPEPAction {
		NONE = 0,
		ADDCLIENTCONNECTION,
		ATTACHSERVERCONNECTION,
		ATTACHCLIENTCONNECTION,
		DETACHSERVERCONNECTION,
		DETACHCLIENTCONNECTION,
		REMOVESERVERCONNECTION,
		REMOVECLIENTCONNECTION,
		UPDATECONNECTIONS
	};
private:
	UINT  m_nError;
	UINT  m_nStatus;
	UINT  m_nResultCode;
	DWORD  m_dwContext;
	HANDLE  m_hDoneFlag;
	CString  m_szServer;
	CString  m_szClient;
	TPEPAction  m_nAction;
	CTPEPConnection  m_cConnection;
	CTMEnvironment  *m_pTMEnvironment;
	CDisplayWnd  *m_pDisplay;
public:
	CEvent  m_cEvent;

	// Operations
public:
	VOID SetAction(TPEPAction nAction);
	TPEPAction GetAction() CONST;
	VOID SetResult(UINT nCode);
	UINT GetResult() CONST;
	VOID SetStatus(UINT nStatus);
	UINT GetStatus() CONST;

	VOID SetServer(LPCTSTR pszServer);
	CString GetServer() CONST;
	VOID SetClient(LPCTSTR pszClient);
	CString GetClient() CONST;
	VOID SetConnection(CONST CTPEPConnection *pConnection);
	BOOL GetConnection(CTPEPConnection *pConnection) CONST;
	VOID SetData(CTMEnvironment *pTMEnvironment);
	CTMEnvironment *GetData() CONST;
	VOID SetDisplay(CDisplayWnd *pDisplayWnd);
	CDisplayWnd *GetDisplay() CONST;
	VOID SetContext(DWORD dwContext);
	DWORD GetContext() CONST;
	VOID SetError(UINT nError);
	UINT GetError() CONST;
	VOID SetFlag(HANDLE hFlag);
	HANDLE GetFlag() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceStack

class CTPEPServiceStack : public CPtrArray
{
	// Construction
public:
	CTPEPServiceStack();
	~CTPEPServiceStack();

	// Attributes
public:

	// Operations
public:
	INT Add(CTPEPServiceStackElement *pElement);

	INT Find(CONST CTPEPServiceStackElement *pElement) CONST;

	CTPEPServiceStackElement *GetAt(INT nIndex) CONST;
	CTPEPServiceStackElement *operator[](INT nIndex) CONST;

	VOID RemoveAll();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceThread thread

class CTPEPServiceThread : public CThread
{
	DECLARE_DYNCREATE(CTPEPServiceThread)

	friend class CTPEPService;

	// Construction
public:
	CTPEPServiceThread();

	// Attributes
private:
	CTPEPServiceStack  m_cTPEPServiceStack;
	CTPEPServiceSocket  m_cSocket;
private:
	CEvent  m_bInitialization[2];
	CEvent  m_bUpdate;
	BOOL  m_bAvailable;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL Update();

	BOOL AddClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL AttachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL AttachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL RemoveServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection);
	BOOL RemoveClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection);

	BOOL UpdateConnections(CTMEnvironment *pTMEnvironment, HANDLE hFlag, DWORD dwContext, UINT nError);
	BOOL UpdateConnections(CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError);

private:
	UINT WaitResult(CONST CTPEPServiceStackElement *pElement);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPServiceThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPServiceThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPService

// Specify the TPEP service ports
#define TPEP_SERVICE_FIRSTPORT   1024
#define TPEP_SERVICE_LASTPORT   65535
#define TPEP_SERVICE_DEFAULTPORT   50001
// Specify the TPEP service buffer sizes
#define TPEP_SERVICE_MINIMUMBUFFERSIZE   (16*1024)
#define TPEP_SERVICE_MAXIMUMBUFFERSIZE   (256*1024)
#define TPEP_SERVICE_DEFAULTBUFFERSIZE   (32*1024)
// Specify the TPEP service timeouts
#define TPEP_SERVICE_MINIMUMTIMEOUT   1
#define TPEP_SERVICE_MAXIMUMTIMEOUT   SECONDSPERMINUTE
#define TPEP_SERVICE_DEFAULTTIMEOUT   2
// Specify the TPEP service charsets
#define TPEP_SERVICE_DEFAULTCHARSET   0
#define TPEP_SERVICE_UNICODECHARSET   1
#define TPEP_SERVICE_ASCIICHARSET   2
// Specify the TPEP service availability codes
#define TPEP_SERVICE_UNLIMITEDAVAILABILITY   (1<<0)
#define TPEP_SERVICE_DAILYAVAILABILITY   (1<<1)
#define TPEP_SERVICE_WORKINGDAYSAVAILABILITY   (1<<2)
#define TPEP_SERVICE_NOAVAILABILITY   (1<<3)
#define TPEP_SERVICE_AUDITAVAILABILITY   (1<<4)
// Specify the TPEP service access codes
#define TPEP_SERVICE_UNLIMITEDACCESS   (1<<0)
#define TPEP_SERVICE_RESTRICTEDACCESS   (1<<1)
#define TPEP_SERVICE_DENIEDACCESS   (1<<2)
#define TPEP_SERVICE_AUDITACCESS   (1<<3)
// Specify the TPEP synchronization status codes
#define TPEP_SYNCSTATUS_GOOD   MAKELONG(0,0)
#define TPEP_SYNCSTATUS_BAD   MAKELONG(1,1)
#define TPEP_SYNCSTATUS_NONE   MAKELONG(2,2)
// Specify the TPEP data quality codes
#define TPEP_DATAQUALITY_UNCHANGED   0
#define TPEP_DATAQUALITY_UPDATED   1
#define TPEP_DATAQUALITY_CHANGED   2
#define TPEP_DATAQUALITY_BAD   3
#define TPEP_DATAQUALITY_NONE   4
// Specify the TPEP data status codes
#define TPEP_DATASTATUS_NOLIMIT   (1<<0)
#define TPEP_DATASTATUS_SOFTLIMIT   (1<<1)
#define TPEP_DATASTATUS_HARDLIMIT   (1<<2)
#define TPEP_DATASTATUS_DELTALIMIT   (1<<3)
#define TPEP_DATASTATUS_CONSISTENCYLIMIT   (1<<4)
#define TPEP_DATASTATUS_VALID   (1<<5)
#define TPEP_DATASTATUS_INVALID   (1<<6)
// Specify the TPEP error codes
#define TPEP_ERROR_NONE   MAKELONG(0,0)
#define TPEP_ERROR_ILLEGALSYNTAX   MAKELONG(100,1)
#define TPEP_ERROR_ILLEGALMESSAGEID   MAKELONG(101,2)
#define TPEP_ERROR_ILLEGALSPACECRAFTID   MAKELONG(102,3)
#define TPEP_ERROR_ILLEGALNUMBEROFPACKETS   MAKELONG(103,4)
#define TPEP_ERROR_ILLEGALNUMBEROFPARAMETERS   MAKELONG(104,5)
#define TPEP_ERROR_ILLEGALPACKETID   MAKELONG(105,6)
#define TPEP_ERROR_ILLEGALPARAMETERID   MAKELONG(106,7)
#define TPEP_ERROR_ILLEGALDATAMODE   MAKELONG(107,8)
#define TPEP_ERROR_ILLEGALDATALINK   MAKELONG(108,9)
#define TPEP_ERROR_ILLEGALDATATYPE   MAKELONG(109,10)
#define TPEP_ERROR_ILLEGALTRIGGERMODE   MAKELONG(110,11)
#define TPEP_ERROR_ILLEGALSAMPLELIMIT   MAKELONG(111,12)
#define TPEP_ERROR_ILLEGALRETRIEVESTARTTIME   MAKELONG(112,13)
#define TPEP_ERROR_ILLEGALRETRIEVESTOPTIME   MAKELONG(113,14)
#define TPEP_ERROR_ILLEGALRETRIEVESPEED   MAKELONG(114,15)
#define TPEP_ERROR_BADDATA   MAKELONG(200,16)
#define TPEP_ERROR_NODATA   MAKELONG(300,17)
#define TPEP_ERROR_NOSERVICE   MAKELONG(400,18)
#define TPEP_ERROR_NOACCESS   MAKELONG(500,19)
#define TPEP_ERROR_SHUTDOWN   MAKELONG(600,20)
#define TPEP_ERROR_FAILURE   MAKELONG(700,21)

class CTPEPService : public CObject
{
	// Construction
public:
	CTPEPService();

	// Attributes
private:
	typedef struct tagSERVICEINFO {
		INT  cbSize;
		INT  cbUsers;
		INT  cbAccessCodes;
		INT  cbStartTimes;
		INT  cbStopTimes;
		INT  cbProfiles[2];
		UINT  nPort;
		UINT  nCode;
		UINT  nCharset;
		UINT  nBufferSize;
		TIMEKEY  tTimeout;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} SERVICEINFO, *PSERVICEINFO, *LPSERVICEINFO;
private:
	UINT  m_nCode;
	UINT  m_nPort;
	UINT  m_nCharset;
	UINT  m_nBufferSize;
	CTimeSpan  m_tTimeout;
	CTimeSpan  m_tStartTime;
	CTimeSpan  m_tStopTime;
	CUIntArray  m_nAccessCodes;
	CStringArray  m_szServers;
	CStringArray  m_szClients;
	CStringArray  m_szUsers;
	CTimeKeyArray  m_tStartTimes;
	CTimeKeyArray  m_tStopTimes;
	CTPEPConnections  m_pServerConnections;
	CTPEPConnections  m_pClientConnections;
	CTPEPDataProfiles  m_pPacketProfiles;
	CTPEPDataProfiles  m_pParameterProfiles;
private:
	CTPEPServiceThread  m_cServiceThread;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL SetPort(UINT nPort);
	BOOL GetPort(UINT &nPort) CONST;
	UINT GetPort() CONST;
	BOOL SetBufferSize(UINT nSize);
	BOOL GetBufferSize(UINT &nSize) CONST;
	UINT GetBufferSize() CONST;
	BOOL SetTimeout(CONST CTimeSpan &tTimeout);
	BOOL GetTimeout(CTimeSpan &tTimeout) CONST;
	CTimeSpan GetTimeout() CONST;
	BOOL SetCharset(UINT nCharset);
	BOOL GetCharset(UINT &nCharset) CONST;
	UINT GetCharset() CONST;
	BOOL SetAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetSecurityInfo(CONST CStringArray &szUsers, CONST CUIntArray &nCodes, CONST CTimeKeyArray &tStartTimes, CONST CTimeKeyArray &tStopTimes);
	BOOL GetSecurityInfo(CStringArray &szUsers, CUIntArray &nCodes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST;
	BOOL SetPacketProfiles(CONST CTPEPDataProfiles *pPacketProfiles);
	BOOL GetPacketProfiles(CTPEPDataProfiles *pPacketProfiles) CONST;
	BOOL SetParameterProfiles(CONST CTPEPDataProfiles *pParameterProfiles);
	BOOL GetParameterProfiles(CTPEPDataProfiles *pParameterProfiles) CONST;

	BOOL SetServerConnections(CONST CStringArray &szClients, CONST CTPEPConnections &pConnections);
	INT GetServerConnections(CStringArray &szClients, CTPEPConnections &pConnections) CONST;
	BOOL HasServerConnections() CONST;
	BOOL AttachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL UpdateServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, BOOL bDelete = FALSE);
	BOOL RemoveServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection);
	BOOL SetClientConnections(CONST CStringArray &szServers, CONST CTPEPConnections &pConnections);
	INT GetClientConnections(CStringArray &szServers, CTPEPConnections &pConnections) CONST;
	BOOL HasClientConnections() CONST;
	BOOL AddClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd = NULL);
	BOOL AttachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL DetachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd);
	BOOL UpdateClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, BOOL bDelete = FALSE);
	BOOL RemoveClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection);

	BOOL Update(CTMEnvironment *pTMEnvironment, HANDLE hFlag, DWORD dwContext = -1, UINT nError = 0);
	BOOL Update(CTMEnvironment *pTMEnvironment, DWORD dwContext = -1, UINT nError = 0);

	BOOL SetServiceInfo(CONST CByteArray &nInfo);
	BOOL GetServiceInfo(CByteArray &nInfo) CONST;
	BOOL UpdateServiceInfo(BOOL bSave = TRUE);

	BOOL IsAvailable() CONST;

	BOOL Lock();
	BOOL Unlock();

private:
	BOOL SaveServiceInfo();
	BOOL LoadServiceInfo();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMProviderDevice

// Specify the telemetry provider device schedule options
#define TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS   (1<<0)
#define TELEMETRYPROVIDERDEVICE_SCHEDULE_DAILY   (1<<1)
#define TELEMETRYPROVIDERDEVICE_SCHEDULE_INTERVAL   (1<<2)
#define TELEMETRYPROVIDERDEVICE_SCHEDULE_PERIODIC   (1<<3)
#define TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED   (1<<4)
#define TELEMETRYPROVIDERDEVICE_SCHEDULE_AUDIT   (1<<5)
// Specify the telemetry provider device backup options
#define TELEMETRYPROVIDERDEVICE_BACKUP_CONTINOUSLY  (1<<0)
#define TELEMETRYPROVIDERDEVICE_BACKUP_RETRIES   (1<<1)
#define TELEMETRYPROVIDERDEVICE_BACKUP_USEDEVICE   (1<<2)
#define TELEMETRYPROVIDERDEVICE_BACKUP_USEANYDEVICE   (1<<3)
#define TELEMETRYPROVIDERDEVICE_BACKUP_AUDITFAILURES   (1<<4)

class CTMProviderDevice : public CIODevice
{
	// Constrution
public:
	CTMProviderDevice();
	CTMProviderDevice(CTMProviderDevice *pDevice);

	// Attributes
protected:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbDevice;
		INT  cbBackupDevice;
		TIMEKEY  tScheduleStartTime;
		TIMEKEY  tScheduleStopTime;
		TIMEKEY  tPeriodicStartTime;
		TIMEKEY  tPeriodicInterval[2];
		TIMEKEY  tDailyStartTime;
		TIMEKEY  tDailyStopTime;
		TIMEKEY  tBackupTimeout;
		UINT  nBackupOptions;
		UINT  nBackupRetry[2];
		UINT  nScheduleOptions;
	} DATA, *PDATA, *LPDATA;
protected:
	CTimeKey  m_tScheduleStartTime;
	CTimeKey  m_tScheduleStopTime;
	CTimeKey  m_tPeriodicStartTime;
	CTimeSpan  m_tPeriodicInterval[2];
	CTimeSpan  m_tDailyStartTime;
	CTimeSpan  m_tDailyStopTime;
	CTimeSpan  m_tBackupTimeout;
	CString  m_szBackupDevice;
	UINT  m_nBackupOptions;
	UINT  m_nBackupRetry[2];
	UINT  m_nScheduleOptions;
protected:
	static UINT  m_nDeviceStatus;
	static BOOL  m_bDeviceStatus;
	static CPtrArray  m_pDataStreamDevices;
	static CPtrArray  m_nDataStreamTimerIDs;
	static CUIntArray  m_nDataStreamEventIDs;

	// Operations
public:
	virtual BOOL Initialize(UINT nFlags = IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS, CONST CTimeSpan &tDataDrop = 0, CONST CTimeSpan &tDataDelay = 0, IODEVICESTATUSPROCEDURE pStatusProcedure = NULL, IODEVICEMESSAGEPROCEDURE pMessageProcedure = NULL);

public:
	VOID SetScheduleOptions(UINT nOptions);
	UINT GetScheduleOptions() CONST;
	VOID SetScheduleDaily(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetScheduleDaily(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	VOID SetScheduleInterval(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetScheduleInterval(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	VOID SetSchedulePeriodic(CONST CTimeKey &tStartTime, CONST CTimeSpan &tPeriod, CONST CTimeSpan &tInterval);
	BOOL GetSchedulePeriodic(CTimeKey &tStartTime, CTimeSpan &tPeriod, CTimeSpan &tInterval) CONST;
	VOID SetBackupDevice(LPCTSTR pszDevice);
	BOOL GetBackupDevice(CString &szDevice) CONST;
	VOID SetBackupOptions(UINT nOptions);
	UINT GetBackupOptions() CONST;
	VOID SetBackupRetries(UINT nRetries);
	BOOL GetBackupRetries(UINT &nRetries) CONST;
	VOID SetBackupRetryCount(UINT nCount);
	BOOL GetBackupRetryCount(UINT &nCount) CONST;
	VOID SetBackupTimeout(CONST CTimeSpan &tTimeout);
	BOOL GetBackupTimeout(CTimeSpan &tTimeout) CONST;

	CString GetToolTipText() CONST;

	BOOL IsStandBy(CTimeSpan &tPeriod) CONST;
	BOOL IsStandBy() CONST;

	BOOL Copy(CONST CTMProviderDevice *pDevice);
	BOOL Compare(CONST CTMProviderDevice *pDevice) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	static VOID CALLBACK TrackDeviceDataStream(UINT nFlags, TIMEKEY tInterval, LPVOID pData);
	static VOID CALLBACK TrackDeviceDataDrops(HWND hwnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime);
	static VOID CALLBACK UpdateDeviceStatus(LPCTSTR pszStatus, UINT nStatus);
	static VOID CALLBACK ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMProviderDevices

class CTMProviderDevices : public CIODevices
{
	// Construction
public:
	CTMProviderDevices();
	~CTMProviderDevices();

	// Attributes
protected:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbDevice[2];
		INT  cbDevicesData;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szDevice[2];
	CStringArray  m_szDevicePathNames[2];

	// Operations
public:
	INT EnumDevices(UINT nFlags = IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS);

	INT EnumStandByDevices(CTMProviderDevices &pDevices) CONST;
	INT EnumBackupDevices(CONST CTMProviderDevice *pDevice, CTMProviderDevices &pDevices) CONST;

	BOOL HasAvailableDevices(BOOL bSupported = FALSE) CONST;

	BOOL SetActiveDevice(CONST CTMProviderDevice *pDevice);
	BOOL GetActiveDevice(CTMProviderDevice *pDevice) CONST;
	BOOL SetDefaultDevice(CONST CTMProviderDevice *pDevice);
	BOOL GetDefaultDevice(CTMProviderDevice *pDevice) CONST;
	CString GetActiveDeviceBrand() CONST;
	CString GetActiveDeviceName() CONST;
	CString GetDefaultDeviceBrand() CONST;
	CString GetDefaultDeviceName() CONST;

	CTMProviderDevice *GetAt(INT nIndex) CONST;
	CTMProviderDevice *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTMProviderDevices *pDevices, BOOL bAll = TRUE);
	BOOL Compare(CONST CTMProviderDevices *pDevices, BOOL bAll = TRUE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	VOID EnumDevices(UINT nFlags, LPCTSTR pszDirectory);
	VOID EnumDevices(UINT nFlags, LPCTSTR pszDirectory, LPCTSTR pszFileName);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceDevice

class CPFLPServiceDevice : public CTMProviderDevice
{
	// Constrution
public:

	// Attributes
private:
	static CStringArray  m_szClients[2];
	static CTimeTagArray  m_tClients[2];

	// Operations
public:
	virtual BOOL Initialize(UINT nFlags = IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_PROTOCOL_PFLP, CONST CTimeSpan &tDataDrop = 0, CONST CTimeSpan &tDataDelay = 0, IODEVICESTATUSPROCEDURE pStatusProcedure = NULL, IODEVICEMESSAGEPROCEDURE pMessageProcedure = NULL);

private:
	static VOID CALLBACK ShowDeviceLogins(UINT nFlags, LPCTSTR pszClient, TIMETAG tConnectTime, LPVOID pData);
	static VOID CALLBACK ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceDevices

class CPFLPServiceDevices : public CTMProviderDevices
{
	// Construction
public:
	CPFLPServiceDevices();
	~CPFLPServiceDevices();

	// Attributes
public:

	// Operations
public:
	INT EnumDevices(UINT nFlags = IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_PROTOCOL_PFLP);

	INT Add(CPFLPServiceDevice *pDevice);

	CPFLPServiceDevice *GetAt(INT nIndex) CONST;
	CPFLPServiceDevice *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CPFLPServiceDevices *pDevices);
	BOOL Compare(CONST CPFLPServiceDevices *pDevices) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceThread thread

class CPFLPServiceThread : public CThread
{
	DECLARE_DYNCREATE(CPFLPServiceThread)

	friend class CPFLPService;

	// Construction
public:
	CPFLPServiceThread();

	// Attributes
private:
	CPFLPServiceDevice  m_cDevice[2];
private:
	CEvent  m_bUpdate;

	// Operations
public:
	BOOL Start(CONST CPFLPServiceDevices &pDevices);
	BOOL Stop();

	BOOL Update();
	BOOL Update(CONST CPFLPServiceDevice *pDevice);
	BOOL Update(CONST CTMUnit *pTMUnit);

	INT EnumClients(CStringArray &szClients) CONST;
	INT EnumClients(CStringArray &szClients, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST;
	BOOL AbortClient(LPCTSTR pszClient, CONST CTimeTag &tConnectTime);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPFLPServiceThread)
public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPFLPServiceThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPService

// Specify the PFLP service availability codes
#define PFLP_SERVICE_UNLIMITEDAVAILABILITY   (1<<0)
#define PFLP_SERVICE_DAILYAVAILABILITY   (1<<1)
#define PFLP_SERVICE_WORKINGDAYSAVAILABILITY   (1<<2)
#define PFLP_SERVICE_NOAVAILABILITY   (1<<3)
#define PFLP_SERVICE_AUDITAVAILABILITY   (1<<4)

class CPFLPService : public CObject
{
	// Construction
public:
	CPFLPService();

	// Attributes
private:
	typedef struct tagSERVICEINFO {
		INT  cbSize;
		INT  cbDevices;
		UINT  nCode;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} SERVICEINFO, *PSERVICEINFO, *LPSERVICEINFO;
private:
	UINT  m_nCode;
	CTimeSpan  m_tStartTime;
	CTimeSpan  m_tStopTime;
	CPFLPServiceDevices  m_pDevices;
private:
	CPFLPServiceThread  m_cServiceThread;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL SetDevices(CONST CPFLPServiceDevices &pDevices);
	INT GetDevices(CPFLPServiceDevices &pDevices) CONST;
	BOOL SetAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;

	BOOL SetConnections(CONST CStringArray &szClients, CONST CPFLPConnections &pConnections);
	INT GetConnections(CStringArray &szClients, CPFLPConnections &pConnections) CONST;
	BOOL HasConnections() CONST;

	BOOL Update(CONST CTMEnvironment *pTMEnvironment);

	BOOL SetServiceInfo(CONST CByteArray &nInfo);
	BOOL GetServiceInfo(CByteArray &nInfo) CONST;
	BOOL UpdateServiceInfo(BOOL bSave = TRUE);

	BOOL IsAvailable() CONST;

	BOOL Lock();
	BOOL Unlock();

private:
	BOOL SaveServiceInfo();
	BOOL LoadServiceInfo();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSystemAlertInfo

class CSystemAlertInfo : public CObject
{
	// Construction
public:
	CSystemAlertInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbMessage;
		INT  cbDescription;
		INT  cbAudition;
		INT  cbNotifications;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szMessage;
	CString  m_szExtraInfo;
	CString  m_szDescription;
	CString  m_szAudition;
	CStringArray  m_szNotifications;
	CTimeTag  m_tTime;
	DWORD  m_dwTimeout;
	INT  m_nCategory;
	INT  m_nType;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	CString TranslateName(LPCTSTR pszName) CONST;
	VOID SetCategory(INT nCategory);
	INT GetCategory() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetMessage(LPCTSTR pszMessage);
	CString GetMessage() CONST;
	VOID SetExtraInfo(LPCTSTR pszInfo);
	CString GetExtraInfo() CONST;
	VOID SetTime(CONST CTimeTag &tTime);
	CTimeTag GetTime() CONST;
	VOID SetTimeout(DWORD dwTimeout);
	DWORD GetTimeout() CONST;
	VOID SetAudition(LPCTSTR pszAudition);
	CString GetAudition() CONST;
	VOID SetNotifications(CONST CStringArray &szNotifications);
	INT GetNotifications(CStringArray &szNotifications) CONST;

	VOID Copy(CONST CSystemAlertInfo *pAlertInfo);
	BOOL Compare(CONST CSystemAlertInfo *pAlertInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSystemAlerts

class CSystemAlerts : public CMutexArray
{
	// Construction
public:
	CSystemAlerts();
	~CSystemAlerts();

	// Attributes
public:

	// Operations
public:
	INT Add(CSystemAlertInfo *pAlertInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CSystemAlertInfo *GetAt(INT nIndex) CONST;
	CSystemAlertInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CSystemAlerts *pAlerts);
	BOOL Compare(CONST CSystemAlerts *pAlerts) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryEventExpression

class CTelemetryEventExpression : public CObject
{
	// Construction
public:
	CTelemetryEventExpression();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbFunction;
		INT  cbOperator;
		INT  cbParameter;
		INT  nNumberFlag;
		INT  nParameterSample;
		BOOL  bParameterCode;
		double  fNumber;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szParameter;
	CString  m_szFunction;
	CString  m_szOperator;
	BOOL  m_bParameterCode;
	INT  m_nParameterSample;
	INT  m_nNumberFlag;
	double  m_fNumber;

	// Operations
public:
	VOID SetFunction(LPCTSTR pszFunction);
	CString GetFunction() CONST;
	BOOL IsFunction() CONST;

	VOID SetOperator(LPCTSTR pszOperator);
	CString GetOperator() CONST;
	BOOL IsOperator() CONST;

	VOID SetParameter(LPCTSTR pszParameter);
	VOID SetParameter(LPCTSTR pszParameter, INT nSample, BOOL bCode);
	BOOL GetParameter(CString &szParameter, INT &nSample, BOOL &bCode) CONST;
	CString GetParameter() CONST;
	BOOL IsParameter() CONST;

	VOID SetNumber(double fNumber, BOOL bPoint = FALSE);
	double GetNumber() CONST;
	CString GetNumberAsText() CONST;
	BOOL IsNumber() CONST;

	BOOL IsEmpty() CONST;

	VOID Copy(CONST CTelemetryEventExpression *pExpression);
	BOOL Compare(CONST CTelemetryEventExpression *pExpression) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryEventInfo

#define TELEMETRYEVENTINFO_RESULT_NONE   0
#define TELEMETRYEVENTINFO_RESULT_BELOWZERO   1
#define TELEMETRYEVENTINFO_RESULT_EQUALZERO   2
#define TELEMETRYEVENTINFO_RESULT_ABOVEZERO   3
#define TELEMETRYEVENTINFO_RESULT_UNEQUALZERO   4
#define TELEMETRYEVENTINFO_RESULT_BELOWEQUALZERO   5
#define TELEMETRYEVENTINFO_RESULT_ABOVEEQUALZERO   6

class CTelemetryEventInfo : public CPtrArray
{
	// Construction
public:
	CTelemetryEventInfo();
	~CTelemetryEventInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbMessage;
		INT  cbAudition;
		INT  cbNotification;
		INT  cbExpressions;
		UINT  nResultCode;
		BOOL  bData[3];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szMessage;
	CString  m_szAudition;
	CString  m_szNotification;
	CTimeTag  m_tTime;
	UINT  m_nResultCode;
	BOOL  m_bData[3];

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetMessage(LPCTSTR pszMessage);
	CString GetMessage() CONST;
	VOID SetTime(CONST CTimeTag &tTime);
	CTimeTag GetTime() CONST;
	VOID SetAudition(LPCTSTR pszAudition);
	CString GetAudition() CONST;
	VOID SetNotification(LPCTSTR pszNotification);
	CString GetNotification() CONST;
	VOID SetResultCode(UINT nCode);
	UINT GetResultCode() CONST;

	VOID SetInvalidDataMode(BOOL bEnable);
	BOOL IsInvalidDataModeEnabled() CONST;
	VOID SetBadDataMode(BOOL bEnable);
	BOOL IsBadDataModeEnabled() CONST;
	VOID SetDisabledDataMode(BOOL bEnable);
	BOOL IsDisabledDataModeEnabled() CONST;

	INT Add(CTelemetryEventExpression *pExpression);

	INT Find(LPCTSTR pszExpression, INT nIndex = -1) CONST;

	CTelemetryEventExpression *GetAt(INT nIndex) CONST;
	CTelemetryEventExpression *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelemetryEventInfo *pEventInfo);
	BOOL Compare(CONST CTelemetryEventInfo *pEventInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryEvents

class CTelemetryEvents : public CMutexArray
{
	// Construction
public:
	CTelemetryEvents();
	~CTelemetryEvents();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelemetryEventInfo *pEventInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTelemetryEventInfo *GetAt(INT nIndex) CONST;
	CTelemetryEventInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelemetryEvents *pEvents);
	BOOL Compare(CONST CTelemetryEvents *pEvents) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFileTriggerInfo

// Specify the telemetry report file trigger track attributes
#define TELEMETRYREPORT_FILETRIGGER_TRACKMODE_NONE   0
#define TELEMETRYREPORT_FILETRIGGER_TRACKMODE_DISABLED   (1<<0)
#define TELEMETRYREPORT_FILETRIGGER_TRACKMODE_NEWFILES   (1<<1)
#define TELEMETRYREPORT_FILETRIGGER_TRACKMODE_UPDATEDFILES   (1<<2)
#define TELEMETRYREPORT_FILETRIGGER_TRACKMODE_DELETEDFILES   (1<<3)
#define TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_ALLFILES   (1<<4)
#define TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_SELECTEDFILES   (1<<5)

class CTelemetryReportFileTriggerInfo : public CObject
{
	// Construction
public:
	CTelemetryReportFileTriggerInfo();
	CTelemetryReportFileTriggerInfo(CTelemetryReportFileTriggerInfo *pTriggerInfo);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbDirectory;
		INT  cbFilteredFiles;
		INT  cbFileAttributes;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szDirectory;
	CStringArray  m_szFilteredFiles;
	CStringArray  m_szFileListings[2];
	CUIntArray  m_nFileAttributes;
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetDirectory(LPCTSTR pszDirectory);
	CString GetDirectory() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetFilteredFiles(CONST CStringArray &szFiles, CONST CUIntArray &nFileAttributes);
	INT GetFilteredFiles(CStringArray &szFiles, CUIntArray &nFileAttributes) CONST;

	BOOL SetFileListing(LPCTSTR pszListing, LPCTSTR pszTime);
	BOOL SetFileListing(INT nIndex, LPCTSTR pszListing, LPCTSTR pszTime);
	BOOL GetFileListing(CString &szListing, CString &szTime) CONST;
	BOOL GetFileListing(INT nIndex, CString &szListing, CString &szTime) CONST;

	VOID Copy(CONST CTelemetryReportFileTriggerInfo *pTriggerInfo);
	BOOL Compare(CONST CTelemetryReportFileTriggerInfo *pTriggerInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFileTriggers

class CTelemetryReportFileTriggers : public CPtrArray
{
	// Construction
public:
	CTelemetryReportFileTriggers();
	~CTelemetryReportFileTriggers();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelemetryReportFileTriggerInfo *pTriggerInfo);

	INT Find(LPCTSTR pszDirectory) CONST;

	CTelemetryReportFileTriggerInfo *GetAt(INT nIndex) CONST;
	CTelemetryReportFileTriggerInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelemetryReportFileTriggers *pTriggers);
	BOOL Compare(CONST CTelemetryReportFileTriggers *pTriggers) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszDirectory, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFTPRecipientInfo

// Specify the telemetry report FTP recipients audition codes
#define TELEMETRYREPORT_FTPRECIPIENT_AUDITION_NONE   0
#define TELEMETRYREPORT_FTPRECIPIENT_AUDITION_ALL   1
#define TELEMETRYREPORT_FTPRECIPIENT_AUDITION_FAILURES   2

class CTelemetryReportFTPRecipientInfo : public CObject
{
	// Construction
public:
	CTelemetryReportFTPRecipientInfo();
	CTelemetryReportFTPRecipientInfo(CTelemetryReportFTPRecipientInfo *pRecipientInfo);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbLocation;
		INT  cbUserName;
		INT  cbPassword;
		BOOL  bSend;
		UINT  nPort;
		UINT  nAudition;
		UINT  nRetryCount[2];
		TIMEKEY  tRetryInterval;
		TIMEKEY  tRetryTime;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szLocation;
	CString  m_szUserName;
	CString  m_szPassword;
	CTimeKey  m_tRetryTime;
	CTimeSpan  m_tRetryInterval;
	UINT  m_nRetryCount[2];
	UINT  m_nAudition;
	UINT  m_nPort;
	BOOL  m_bSend;

	// Operations
public:
	VOID SetLocation(LPCTSTR pszLocation);
	CString GetLocation() CONST;
	VOID SetUserName(LPCTSTR pszUserName);
	CString GetUserName() CONST;
	VOID SetPassword(LPCTSTR pszPassword);
	CString GetPassword() CONST;
	VOID SetPort(UINT nPort);
	UINT GetPort() CONST;

	VOID SetRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval);
	BOOL GetRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST;
	VOID SetRetryTime(CTimeKey &tTime);
	CTimeKey GetRetryTime() CONST;
	VOID SetRetryCount(UINT nCount);
	UINT GetRetryCount() CONST;
	VOID SetAudition(UINT nAudition);
	UINT GetAudition() CONST;

	VOID Enable(BOOL bSend = TRUE);
	BOOL IsEnabled() CONST;

	VOID Copy(CONST CTelemetryReportFTPRecipientInfo *pRecipientInfo);
	BOOL Compare(CONST CTelemetryReportFTPRecipientInfo *pRecipientInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFTPRecipients

class CTelemetryReportFTPRecipients : public CPtrArray
{
	// Construction
public:
	CTelemetryReportFTPRecipients();
	~CTelemetryReportFTPRecipients();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelemetryReportFTPRecipientInfo *pRecipientInfo);

	INT Find(LPCTSTR pszLocation, LPCTSTR pszUserName) CONST;

	CTelemetryReportFTPRecipientInfo *GetAt(INT nIndex) CONST;
	CTelemetryReportFTPRecipientInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelemetryReportFTPRecipients *pRecipients);
	BOOL Compare(CONST CTelemetryReportFTPRecipients *pRecipients) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszLocation, LPCTSTR pszUserName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportInfo

// Specify the telemetry report options
#define TELEMETRYREPORTINFO_OPTION_DISABLED   (1<<0)
#define TELEMETRTREPORTINFO_OPTION_KEEPALLFILES   (1<<1)
#define TELEMETRYREPORTINFO_OPTION_KEEPINPUTFILES   (1<<2)
#define TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE   (1<<3)
#define TELEMETRYREPORTINFO_OPTION_MAILDAILY   (1<<4)
#define TELEMETRYREPORTINFO_OPTION_MAILWEEKLY   (1<<5)
#define TELEMETRYREPORTINFO_OPTION_SCHEDULED   (1<<6)
#define TELEMETRYREPORTINFO_OPTION_HISTORICAL   (1<<7)
// Specify the telemetry report status codes
#define TELEMETRYREPORTINFO_STATUS_EXECUTING   1
#define TELEMETRYREPORTINFO_STATUS_QUEUED   2

class CTelemetryReportInfo : public CObject
{
	// Construction
public:
	CTelemetryReportInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbLinkData;
		INT  cbSource;
		INT  cbEvents;
		INT  cbAlerts;
		INT  cbScript;
		INT  cbInputFileName;
		INT  cbOutputFileName;
		INT  cbMailFileName;
		INT  cbMailRecipients[2];
		INT  cbFileTriggers;
		UINT  nOptions;
		TIMEKEY  tMailTime[2];
		TIMEKEY  tMailInterval;
		TIMEKEY  tPeriodicalTime[2];
		TIMEKEY  tPeriodicalInterval;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szSource;
	CString  m_szScript;
	CString  m_szInputFileName;
	CString  m_szOutputFileName;
	CString  m_szMailFileName;
	CByteArray  m_nLinkData;
	CStringArray  m_szEvents;
	CStringArray  m_szAlerts;
	CStringArray  m_szMailRecipients;
	CTelemetryReportFTPRecipients  m_pMailRecipients;
	CTelemetryReportFileTriggers  m_pFileTriggers;
	CTimeSpan  m_tPeriodicalInterval;
	CTimeSpan  m_tMailInterval;
	CTimeKey  m_tExecutionTime;
	CTimeKey  m_tPeriodicalTime[2];
	CTimeKey  m_tMailTime[2];
	UINT  m_nOptions;
	UINT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;
	VOID SetLink(CONST CByteArray &nData);
	INT GetLink(CByteArray &nData) CONST;
	VOID SetHistoricalSource(LPCTSTR pszSource);
	CString GetHistoricalSource() CONST;
	BOOL SetHistoricalPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tInterval);
	BOOL GetHistoricalPeriod(CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tInterval) CONST;
	BOOL SetScheduledPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tInterval);
	BOOL GetScheduledPeriod(CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tInterval) CONST;
	BOOL SetFileTriggers(CONST CTelemetryReportFileTriggers &pTriggers);
	INT GetFileTriggers(CTelemetryReportFileTriggers &pTriggers) CONST;
	VOID SetLastExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetLastExecutionTime() CONST;
	VOID SetEvents(CONST CStringArray &szEvents);
	INT GetEvents(CStringArray &szEvents) CONST;
	VOID SetAlerts(CONST CStringArray &szAlerts);
	INT GetAlerts(CStringArray &szAlerts) CONST;
	VOID SetScript(LPCTSTR pszScript);
	CString GetScript() CONST;
	VOID SetInputFileName(LPCTSTR pszFileName);
	CString GetInputFileName() CONST;
	VOID SetOutputFileName(LPCTSTR pszFileName);
	CString GetOutputFileName() CONST;
	VOID SetMailFileName(LPCTSTR pszFileName);
	CString GetMailFileName() CONST;
	VOID SetMailTime(CONST CTimeKey &tTime);
	CTimeKey GetMailTime() CONST;
	VOID SetLastMailTime(CONST CTimeKey &tTime);
	CTimeKey GetLastMailTime() CONST;
	VOID SetMailTimeInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetMailTimeInterval() CONST;
	VOID SetMailRecipients(CONST CStringArray &szRecipients);
	VOID SetMailRecipients(CONST CTelemetryReportFTPRecipients &pRecipients);
	INT GetMailRecipients(CStringArray &szRecipients) CONST;
	INT GetMailRecipients(CTelemetryReportFTPRecipients &pRecipients) CONST;
	VOID SetStatus(UINT nStatus);
	UINT GetStatus() CONST;

	VOID Copy(CONST CTelemetryReportInfo *pReportInfo);
	BOOL Compare(CONST CTelemetryReportInfo *pReportInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReports

class CTelemetryReports : public CMutexArray
{
	// Construction
public:
	CTelemetryReports();
	~CTelemetryReports();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelemetryReportInfo *pReportInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTelemetryReportInfo *GetAt(INT nIndex) CONST;
	CTelemetryReportInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelemetryReports *pReports);
	BOOL Compare(CONST CTelemetryReports *pReports) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryHistoricalReportInfo

// Specify the telemetry historical report time range modes
#define TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL   1
#define TELEMETRYHISTORICALREPORTINFO_RANGE_DAILY   2
#define TELEMETRYHISTORICALREPORTINFO_RANGE_COMPLETEINTERVAL   3
#define TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL   4
#define TELEMETRYHISTORICALREPORTINFO_RANGE_TRIGGEREDINTERVAL   5
// Specify the telemetry historical report execution modes
#define TELEMETRYHISTORICALREPORTINFO_EXECUTION_IMMEDIATELY   1
#define TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME   2
#define TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATDAILYTIME   3
#define TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL   4
#define TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATEVENT   5

class CTelemetryHistoricalReportInfo : public CObject
{
	// Construction
public:
	CTelemetryHistoricalReportInfo();
	~CTelemetryHistoricalReportInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbReport;
		INT  cbSource;
		INT  cbInputFiles;
		INT  cbOutputFile;
		INT  cbExecutionEvent;
		INT  cbInputDirectory;
		INT  cbInputFTPLocation;
		INT  cbInputFTPUserName;
		INT  cbInputFTPPassword;
		INT  cbMailRecipients[2];
		UINT  nModes[2];
		UINT  nOptions;
		UINT  nCycleCount;
		UINT  nInputFTPPort;
		TIMEKEY  tRange[2];
		TIMEKEY  tDailyRange[2];
		TIMEKEY  tIntervalRange[3];
		TIMEKEY  tIntervalExecution;
		TIMEKEY  tExecution[3];
		TIMEKEY  tLastExecution;
		TIMEKEY  tDailyExecution;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szReport;
	CString  m_szSource;
	CString  m_szInputFiles;
	CString  m_szOutputFile;
	CString  m_szExecutionEvent;
	CString  m_szInputDirectory;
	CString  m_szInputFTPLocation;
	CString  m_szInputFTPUserName;
	CString  m_szInputFTPPassword;
	CStringArray  m_szMailRecipients;
	CTelemetryReportFTPRecipients  m_pMailRecipients;
	CTimeSpan  m_tIntervalExecution;
	CTimeSpan  m_tIntervalRange[3];
	CTimeSpan  m_tDailyExecution;
	CTimeSpan  m_tDailyRange[2];
	CTimeKey  m_tLastExecution;
	CTimeKey  m_tExecution[3];
	CTimeKey  m_tRange[2];
	UINT  m_nInputFTPPort;
	UINT  m_nCycleCount;
	UINT  m_nModes[2];
	UINT  m_nOptions;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetReport(LPCTSTR pszReport);
	CString GetReport() CONST;
	VOID SetSource(LPCTSTR pszSource);
	CString GetSource() CONST;

	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;

	VOID SetTimeRangeMode(UINT nMode);
	UINT GetTimeRangeMode() CONST;
	VOID SetTimeRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetTimeRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	VOID SetDailyTimeRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetDailyTimeRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	VOID SetPeriodicalInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetPeriodicalInterval() CONST;
	VOID SetTriggeredInterval(CONST CTimeSpan &tInterval, BOOL bBefore = TRUE);
	CTimeSpan GetTriggeredInterval(BOOL bBefore = TRUE) CONST;
	VOID SetRangeInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetRangeInterval() CONST;

	VOID SetExecutionMode(UINT nMode);
	UINT GetExecutionMode() CONST;
	VOID SetExecutionCycle(UINT nCycle);
	UINT GetExecutionCycle() CONST;
	VOID SetExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetExecutionTime() CONST;
	VOID SetDailyExecutionTime(CONST CTimeSpan &tTime);
	CTimeSpan GetDailyExecutionTime() CONST;
	VOID SetPeriodicalExecutionTime(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetPeriodicalExecutionTime(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	VOID SetTriggeredExecution(LPCTSTR pszEvent);
	CString GetTriggeredExecution() CONST;
	VOID SetLastExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetLastExecutionTime() CONST;

	VOID SetInputFiles(CString &szFiles);
	CString GetInputFiles() CONST;
	VOID SetInputDirectory(LPCTSTR pszDirectory);
	CString GetInputDirectory() CONST;
	VOID SetInputFTPLocation(LPCTSTR pszLocation);
	CString GetInputFTPLocation() CONST;
	VOID SetInputFTPUserName(LPCTSTR pszUserName);
	CString GetInputFTPUserName() CONST;
	VOID SetInputFTPPassword(LPCTSTR pszPassword);
	CString GetInputFTPPassword() CONST;
	VOID SetInputFTPPort(UINT nPort);
	UINT GetInputFTPPort() CONST;

	VOID SetOutputFile(LPCTSTR pszFileName);
	CString GetOutputFile() CONST;

	VOID SetMailRecipients(CONST CStringArray &szRecipients);
	VOID SetMailRecipients(CONST CTelemetryReportFTPRecipients &pRecipients);
	INT GetMailRecipients(CStringArray &szRecipients) CONST;
	INT GetMailRecipients(CTelemetryReportFTPRecipients &pRecipients) CONST;

	VOID Copy(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo);
	BOOL Compare(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryHistoricalReports

class CTelemetryHistoricalReports : public CMutexArray
{
	// Construction
public:
	CTelemetryHistoricalReports();
	~CTelemetryHistoricalReports();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelemetryHistoricalReportInfo *pHistoricalReportInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CTelemetryHistoricalReportInfo *GetAt(INT nIndex) CONST;
	CTelemetryHistoricalReportInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelemetryHistoricalReports *pHistoricalReports);
	BOOL Compare(CONST CTelemetryHistoricalReports *pHistoricalReports) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsFileTriggersThread thread

class CTelemetryReportsFileTriggersThread : public CThread
{
	DECLARE_DYNCREATE(CTelemetryReportsFileTriggersThread)

	// Construction
public:
	CTelemetryReportsFileTriggersThread();
	~CTelemetryReportsFileTriggersThread();

	// Attributes
private:
	CString  m_szName;
	CTelemetryReportFileTriggers  m_pTriggers;
private:
	CPtrArray  m_pEvents;

	// Operations
public:
	BOOL Start(LPCTSTR pszName, CONST CTelemetryReportFileTriggers &pTriggers);
	BOOL Stop(LPCTSTR pszName);

	BOOL Update();
	BOOL Update(LPCTSTR pszName, CONST CTelemetryReportFileTriggers &pTriggers);

private:
	BOOL CollectTriggerFiles(CTelemetryReportFileTriggerInfo *pTriggerInfo) CONST;
	BOOL CollectTriggerFiles(LPCTSTR pszDirectory, LPCTSTR pszFilter, CString &szFiles, CString &szTimes) CONST;
	BOOL IsTriggeredByFiles(CTelemetryReportFileTriggerInfo *pTriggerInfo) CONST;
	BOOL IsTriggeredByFiles(LPCTSTR pszNewFileListing, LPCTSTR pszOldFileListing, BOOL bNewFiles = TRUE) CONST;

public:
	operator LPCTSTR() { return((LPCTSTR)m_szName); }

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsFileTriggersThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsFileTriggersThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsFileTriggersThreads

class CTelemetryReportsFileTriggersThreads : public CPtrArray
{
	// Construction
public:
	CTelemetryReportsFileTriggersThreads();
	~CTelemetryReportsFileTriggersThreads();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelemetryReportsFileTriggersThread *pFileTriggersThread);

	INT Find(LPCTSTR pszName) CONST;

	CTelemetryReportsFileTriggersThread *GetAt(INT nIndex) CONST;
	CTelemetryReportsFileTriggersThread *operator[](INT nIndex) CONST;

	VOID RemoveAll();

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsService

class CTelemetryReportsService : public CThread
{
	DECLARE_DYNCREATE(CTelemetryReportsService)

	// Construction
public:
	CTelemetryReportsService();
	~CTelemetryReportsService();

	// Attributes
private:
	CUIntArray  m_nReportIDs;
	CTelemetryReports  *m_pReports[3];
	CTelemetryHistoricalReports  *m_pHistoricalReports;
	CTelemetryReportsFileTriggersThreads  m_pTriggerThreads;
	UINT_PTR  m_nReportTimerID;
private:
	CStringArray  m_szAlerts;
	CStringArray  m_szErrors;
private:
	CEvent  m_bUpdate;
	CEvent  m_bAbort;
	BOOL  m_bExit;

	// Operations
public:
	BOOL Start(CJScriptCodeExecutor *pExecutor);
	BOOL Stop(CJScriptCodeExecutor *pExecutor);

	BOOL Update();
	BOOL Update(LPCTSTR pszReport);
	BOOL Update(CONST CTelemetryReportInfo *pReport);
	BOOL Update(CONST CTelemetryHistoricalReportInfo *pReport);
	BOOL Update(CONST CTelemetryReports &pReports);
	BOOL Update(CONST CTelemetryReports &pReports, CONST CUIntArray &nIDs, CONST CStringArray &szErrors);
	BOOL Refresh(CTelemetryReports &pReports);

	BOOL EnumReports(CTelemetryReports &pReports) CONST;
	BOOL AbortReports(CONST CTelemetryReports &pReports);

private:
	BOOL DoHistoricalReport(CTelemetryReportInfo *pReportInfo);
	BOOL DoNotifyByEMail(CTelemetryReportInfo *pReportInfo);
	BOOL DoNotifyByFTP(CTelemetryReportInfo *pReportInfo);
	INT DoFTPMessageTransfer(CONST CTelemetryReportInfo *pReportInfo, LPCTSTR pszUserName, LPCTSTR pszAddress, LPCTSTR pszPassword, UINT nPort);
	VOID DoPrepareInputFiles(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CTelemetryReportInfo *pReportInfo);
	VOID DoPrepareOutputFile(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CTelemetryReportInfo *pReportInfo);
	BOOL DoDeleteOutputFile(CONST CTelemetryReportInfo *pReportInfo);
	BOOL DoDeleteMailFile(CONST CTelemetryReportInfo *pReportInfo);

	BOOL DoTrack(CTMEnvironment *pTMEnvironment);
	BOOL DoUpdate(CONST CTMEnvironment *pTMEnvironment, CONST CTelemetryReportInfo *pReportInfo, BOOL bReset = FALSE);
	VOID DoAlert(CONST CTMEnvironment *pTMEnvironment, CONST CTelemetryReportInfo *pReportInfo, CONST CTelemetryEventInfo *pEventInfo);
	BOOL DoConvert(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CTelemetryReportInfo *pReportInfo) CONST;
	VOID DoReset(BOOL bReset = TRUE);
	BOOL IsAborted() CONST;

	BOOL Wait(DWORD dwTimeout = INFINITE);

	VOID ShowErrors(CONST CStringArray &szErrors);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsService)
public:
	virtual int ExitInstance();
	virtual int Run();
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsService)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNotificationPhoneCallMonitorSink

class CNotificationPhoneCallMonitorSink : public ITTAPIEventNotification
{
	// Construction
public:
	CNotificationPhoneCallMonitorSink();

	// Attributes
private:
	CALL_STATE  m_nCallState;
	CString  m_szCallDigits;
private:
	LONG  m_lRefCount;

	// Operations
public:
	VOID SetCallState(CALL_STATE nState);
	CALL_STATE GetCallState() CONST;
	VOID SetCallDigits(LPCTSTR pszDigits);
	CString GetCallDigits() CONST;

	HRESULT STDMETHODCALLTYPE Event(TAPI_EVENT nEvent, IDispatch *pEvent);

public:
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppvObject);

	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNotificationService

class CNotificationService : public CThread
{
	DECLARE_DYNCREATE(CNotificationService)

	// Construction
public:
	CNotificationService();

	// Attributes
private:
	BOOL  m_bFAXCall;
	BOOL  m_bPhoneCall;
	BOOL  m_bPagerCall;
	LONG  m_lPhoneCallID;
	ULONG  m_ulPhoneCallAdvise;
private:
	ITTAPI2  *m_pIPhoneCallInterface;
	ITAddress  *m_pIPhoneCallAddress;
	CComPtr<ISpVoice>  m_cIPhoneVoice;
	CComPtr<ISpMMSysAudio>  m_cIPhoneVoiceAudioIn;
	CComPtr<ISpMMSysAudio>  m_cIPhoneVoiceAudioOut;
	CComPtr<ISpRecognizer>  m_cIPhoneVoiceRecognizer;
	CComPtr<ISpRecoContext>  m_cIPhoneVoiceRecognizerContext;
	CComPtr<ISpRecoGrammar>  m_cIPhoneVoiceRecognizerGrammar;
	CNotificationPhoneCallMonitorSink  *m_pPhoneCallMonitor;
private:
	CNotificationProfiles  m_pProfiles;
private:
	CEvent  m_bUpdate;
	CEvent  m_bAbort;
	BOOL  m_bExit;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL EnumNotifications(CNotificationProfiles &pProfiles) CONST;
	BOOL AbortNotifications(CONST CNotificationProfiles &pProfiles);

	BOOL Update(CONST CNotificationProfileInfo *pProfileInfo, LPCTSTR pszMessage);

private:
	BOOL DoNotification(CNotificationProfileInfo *pProfileInfo);
	BOOL DoNotifyByEMail(CNotificationProfileInfo *pProfileInfo);
	BOOL DoNotifyByFax(CNotificationProfileInfo *pProfileInfo);
	BOOL DoNotifyByPhoneCall(CNotificationProfileInfo *pProfileInfo);
	BOOL DoNotifyByPagerCall(CNotificationProfileInfo *pProfileInfo);
	BOOL DoNotifyByFTPMessage(CNotificationProfileInfo *pProfileInfo);
	BOOL DoNotifyByPrinterMessage(CNotificationProfileInfo *pProfileInfo);

	BOOL DoFaxTransmission(CONST CNotificationProfileInfo *pProfileInfo, FAX_CONTEXT_INFO *pFAXContext);

	BOOL DoPhoneCallConversation(CONST CNotificationProfileInfo *pProfileInfo, CONST CUserProfileInfo *pUserInfo, ITLegacyCallMediaControl2 *pLegacyCallMediaControl);
	BOOL DoAudioOutForPhoneCall(ITLegacyCallMediaControl2 *pLegacyCallMediaControl);
	BOOL DoAudioInForPhoneCall(ITLegacyCallMediaControl2 *pLegacyCallMediaControl);
	BOOL DoSpeakOnPhoneCallLine(LPCTSTR pszText);
	BOOL DoWaitForPhoneCallLineAnswer(DWORD dwTimeout);
	BOOL DoListenToPhoneCallLineAnswer(CString &szAnswer);
	BOOL IsPhoneCallLineConnected() CONST;

	BOOL DoPagerCallConnection(CONST CNotificationProfileInfo *pProfileInfo, CONST CUserProfileInfo *pUserInfo);

	BOOL DoFTPMessageTransfer(CONST CNotificationProfileInfo *pProfileInfo, LPCTSTR pszUserName, LPCTSTR pszAddress, LPCTSTR pszPassword, UINT nPort);

	BOOL DoPrinterMessageOutput(CONST CNotificationProfileInfo *pProfileInfo, LPCTSTR pszPrintProfile);

	CString TranslateToPhoneticWord(LPCTSTR pszWord) CONST;

	HANDLE DoInitializeFaxService();
	VOID UninitializeFaxService(HANDLE hDevice);
	BOOL DoInitializePSTNService(CONST CNotificationProfileInfo *pProfileInfo);
	VOID UninitializePSTNService();

	BOOL IsEMailServiceAvailable() CONST;
	BOOL IsFaxServiceAvailable() CONST;
	BOOL IsPhoneCallServiceAvailable() CONST;
	BOOL IsPagerCallServiceAvailable() CONST;
	BOOL IsFTPMessageServiceAvailable() CONST;
	BOOL IsPrinterMessageServiceAvailable() CONST;

	BOOL IsAborted() CONST;

	BOOL Wait(DWORD dwTimeout = INFINITE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotificationService)
public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotificationService)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadProfileInfo

// Specify the tools download related options
#define TOOLSDOWNLOADINFO_OPTION_DISABLED   (1<<0)
#define TOOLSDOWNLOADINFO_OPTION_AUDITION   (1<<1)
#define TOOLSDOWNLOADINFO_OPTION_TRANSFERASASCII   (1<<2)
#define TOOLSDOWNLOADINFO_OPTION_TRANSFERASBINARY   (1<<3)
#define TOOLSDOWNLOADINFO_OPTION_DELETEFILES   (1<<4)
// Specify the tools download execution modes
#define TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY   1
#define TOOLSDOWNLOADINFO_EXECUTION_ATTIME   2
#define TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME   3
#define TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL   4
#define TOOLSDOWNLOADINFO_EXECUTION_ATEVENT   5

class CToolsDownloadProfileInfo : public CObject
{
	// Construction
public:
	CToolsDownloadProfileInfo();
	~CToolsDownloadProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbFiles;
		INT  cbDirectory;
		INT  cbFTPLocation;
		INT  cbFTPUserName;
		INT  cbFTPPassword;
		INT  cbExecutionEvent;
		UINT  nMode;
		UINT  nOptions;
		UINT  nFTPPort;
		UINT  nCycleCount;
		TIMEKEY  tIntervalExecution;
		TIMEKEY  tExecution[3];
		TIMEKEY  tLastExecution;
		TIMEKEY  tDailyExecution;
		TIMEKEY  tExecutionDelay;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szFiles;
	CString  m_szDirectory;
	CString  m_szFTPLocation;
	CString  m_szFTPUserName;
	CString  m_szFTPPassword;
	CString  m_szExecutionEvent;
	CTimeSpan  m_tIntervalExecution;
	CTimeSpan  m_tExecutionDelay;
	CTimeSpan  m_tDailyExecution;
	CTimeKey  m_tLastExecution;
	CTimeKey  m_tExecution[3];
	UINT  m_nCycleCount;
	UINT  m_nFTPPort;
	UINT  m_nOptions;
	UINT  m_nMode;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;

	VOID SetExecutionMode(UINT nMode);
	UINT GetExecutionMode() CONST;
	VOID SetExecutionCycle(UINT nCycle);
	UINT GetExecutionCycle() CONST;
	VOID SetExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetExecutionTime() CONST;
	VOID SetDailyExecutionTime(CONST CTimeSpan &tTime);
	CTimeSpan GetDailyExecutionTime() CONST;
	VOID SetPeriodicalExecutionTime(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetPeriodicalExecutionTime(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	VOID SetTriggeredExecution(LPCTSTR pszEvent, CONST CTimeSpan &tDelay);
	CString GetTriggeredExecution(CTimeSpan &tDelay) CONST;
	VOID SetLastExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetLastExecutionTime() CONST;

	VOID SetFiles(CString &szFiles);
	CString GetFiles() CONST;
	VOID SetDirectory(LPCTSTR pszDirectory);
	CString GetDirectory() CONST;
	VOID SetFTPLocation(LPCTSTR pszLocation);
	CString GetFTPLocation() CONST;
	VOID SetFTPUserName(LPCTSTR pszUserName);
	CString GetFTPUserName() CONST;
	VOID SetFTPPassword(LPCTSTR pszPassword);
	CString GetFTPPassword() CONST;
	VOID SetFTPPort(UINT nPort);
	UINT GetFTPPort() CONST;

	VOID Copy(CONST CToolsDownloadProfileInfo *pProfileInfo);
	BOOL Compare(CONST CToolsDownloadProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadProfiles

class CToolsDownloadProfiles : public CMutexArray
{
	// Construction
public:
	CToolsDownloadProfiles();
	~CToolsDownloadProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CToolsDownloadProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CToolsDownloadProfileInfo *GetAt(INT nIndex) CONST;
	CToolsDownloadProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CToolsDownloadProfiles *pProfiles);
	BOOL Compare(CONST CToolsDownloadProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadService

class CToolsDownloadService : public CThread
{
	DECLARE_DYNCREATE(CToolsDownloadService)

	// Construction
public:
	CToolsDownloadService();

	// Attributes
private:
	CToolsDownloadProfiles  m_pProfiles;
private:
	CEvent  m_bUpdate;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL Update(CONST CToolsDownloadProfiles &pProfiles);
	BOOL Update(CONST CToolsDownloadProfileInfo *pProfileInfo);

	BOOL Refresh(CToolsDownloadProfiles &pProfiles);

private:
	VOID Download(CONST CToolsDownloadProfileInfo *pProfileInfo);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsDownloadService)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolsDownloadService)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDatabaseService

// Specify the tools database service related options
#define TOOLSDATABASESERVICE_OPTION_DONOTHING   0
#define TOOLSDATABASESERVICE_OPTION_INFORMBYEVENT   1
#define TOOLSDATABASESERVICE_OPTION_UPDATEIMMEDIATELY   2
#define TOOLSDATABASESERVICE_OPTION_UPDATEATTIME   3
// Specify the tools database service related timer identifiers
#define TOOLSDATABASESERVICE_BEHAVIOR_TIMERID   10003
#define TOOLSDATABASESERVICE_BEHAVIOR_TIMEOUT   0

class CToolsDatabaseService : public CThread
{
	DECLARE_DYNCREATE(CToolsDatabaseService)

	// Construction
public:
	CToolsDatabaseService();

	// Attributes
private:
	UINT  m_nOption;
	CTimeKey  m_tStartTime;
	CTimeKey  m_tEndTime;
private:
	CEvent  m_bUpdate;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL SetUpdateBehavior(UINT nOption, CONST CTimeKey &tStartTime, CONST CTimeKey &tEndTime);
	BOOL GetUpdateBehavior(UINT &nOption, CTimeKey &tStartTime, CTimeKey &tEndTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsDatabaseService)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolsDatabaseService)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRASService

// Specify the RAS service related identifiers
#define RASSERVICE_DEFAULT_TIMEOUT   (2*SECONDSPERMINUTE)

class CRASService : public CThread
{
	DECLARE_DYNCREATE(CRASService)

	// Construction
public:
	CRASService();
	~CRASService();

	// Attributes
private:
	HRASCONN  m_hConnection;
	RASENTRY  m_cConnectionEntry;
	RASCONNSTATE  m_nConnectionState;
	RASDIALPARAMS  m_cConnectionInfo;
	RASDIALEXTENSIONS  m_cConnectionExt;
	CTimeKey  m_tConnectionTimeKey;
	CString  m_szConnectionServer;
	CString  m_szConnectionNumber;
private:
	LONG  m_bCalling;
	LONG  m_bAborting;

	// Operations
public:
	BOOL MakeCall(CONST RASENTRY *pConnectionEntry, CONST RASDIALEXTENSIONS *pConnectionExt, CONST RASDIALPARAMS *pConnectionInfo);
	RASCONNSTATE CheckCall() CONST;
	BOOL StopCall();

	BOOL SetState(RASCONNSTATE nState, DWORD dwError = 0);
	RASCONNSTATE GetState() CONST;

	BOOL GetDetails(RAS_STATS *pDetails) CONST;
	BOOL GetDetails(CString &szServer, CString &szNumber, CTimeKey &tTime) CONST;
	CString GetDetails() CONST;

	BOOL IsCalling() CONST;
	BOOL IsAborting() CONST;

public:
	static void CALLBACK DialupCallback(UINT nMsg, RASCONNSTATE nState, DWORD dwError);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRASService)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRASService)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCLCWToolWndPanel dialog

#define IDC_CLCWTOOLWINDOW_PANEL_VIRTUALCHANNEL_STATIC   1000
#define IDC_CLCWTOOLWINDOW_PANEL_VIRTUALCHANNEL   1001
#define IDC_CLCWTOOLWINDOW_PANEL_NORFAVAILABLE_STATIC   1002
#define IDC_CLCWTOOLWINDOW_PANEL_NORFAVAILABLE   1003
#define IDC_CLCWTOOLWINDOW_PANEL_NOBITLOCK_STATIC   1004
#define IDC_CLCWTOOLWINDOW_PANEL_NOBITLOCK   1005
#define IDC_CLCWTOOLWINDOW_PANEL_LOCKOUT_STATIC   1006
#define IDC_CLCWTOOLWINDOW_PANEL_LOCKOUT   1007
#define IDC_CLCWTOOLWINDOW_PANEL_WAIT_STATIC   1008
#define IDC_CLCWTOOLWINDOW_PANEL_WAIT   1009
#define IDC_CLCWTOOLWINDOW_PANEL_RETRANSMIT_STATIC   1010
#define IDC_CLCWTOOLWINDOW_PANEL_RETRANSMIT   1011
#define IDC_CLCWTOOLWINDOW_PANEL_FARMCOUNTER_STATIC   1012
#define IDC_CLCWTOOLWINDOW_PANEL_FARMCOUNTER   1013
#define IDC_CLCWTOOLWINDOW_PANEL_REPORTVALUE_STATIC   1014
#define IDC_CLCWTOOLWINDOW_PANEL_REPORTVALUE   1015
#define IDC_CLCWTOOLWINDOW_PANEL_SEQUENCENUMBER_STATIC   1016
#define IDC_CLCWTOOLWINDOW_PANEL_SEQUENCENUMBER   1017
#define IDC_CLCWTOOLWINDOW_PANEL_RAWVALUE_STATIC   1018
#define IDC_CLCWTOOLWINDOW_PANEL_RAWVALUE   1019

// Specify the CLCW bit mask related identifiers
#define CLCWBITMASK_VIRTUALCHANNEL   0x00FC0000
#define CLCWBITMASK_NORFAVAILABLE   0x00008000
#define CLCWBITMASK_NOBITLOCK   0x00004000
#define CLCWBITMASK_LOCKOUT   0x00002000
#define CLCWBITMASK_WAIT   0x00001000
#define CLCWBITMASK_RETRANSMIT   0x00000800
#define CLCWBITMASK_FARMBCOUNTER   0x00000600
#define CLCWBITMASK_REPORTVALUE   0x000000FF
#define MAKECLCWVIRTUALCHANNEL(x)   ((x & CLCWBITMASK_VIRTUALCHANNEL) >> 18)
#define MAKECLCWFARMCOUNTER(x)   ((x & CLCWBITMASK_FARMBCOUNTER) >> 9)
#define MAKECLCWREPORTVALUE(x)   (x & CLCWBITMASK_REPORTVALUE)

class CCLCWToolWndPanel : public CLocaleDialog
{
	DECLARE_DYNCREATE(CCLCWToolWndPanel)

	// Construction
public:
	CCLCWToolWndPanel(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	DWORD  m_dwCLCW;
	CImage  m_cLamps[4];
	CUIntArray  m_nLampIDs;
	CUIntArray  m_nNumberIDs;
private:
	CFont  m_cFont;
	CBasePane  *m_pPanesBar;

	// Dialog Data
	//{{AFX_DATA(CCLCWToolWndPanel)
	enum { IDD = IDD_CLCWTOOLWINDOW_PANEL_DIALOG };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(UINT nID, CWnd *pParentWnd, CBasePane *pBar);

	VOID SetCLCW(DWORD dwCLCW);
	DWORD GetCLCW() CONST;

private:
	VOID UpdateCodes();

	VOID UpdateLamps();
	VOID DrawLamps(CDC *pDC);
	VOID DrawLamp(CDC *pDC, UINT nID);
	VOID DrawLamp(CDC *pDC, LPCRECT pRect, UINT nLampID);
	BOOL LoadLamps();

	VOID UpdateButtons();

	VOID DrawBackground(CDC *pDC, LPCRECT pRect);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCLCWToolWndPanel)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCLCWToolWndPanel)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnDestroy();
	afx_msg void OnCorrelate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCLCWToolWnd window

class CCLCWToolWnd : public CWnd
{
	DECLARE_DYNCREATE(CCLCWToolWnd)

	// Construction
public:
	CCLCWToolWnd();

	// Attributes
public:
	CCLCWToolWndPanel  *m_pwndPanel;
private:
	BOOL  m_bRedraw;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CBasePane *pBar);
	BOOL Destroy();

	VOID SetCLCW(DWORD dwCLCW);
	DWORD GetCLCW() CONST;

private:
	VOID RedrawLayout(BOOL bRedraw = TRUE);
	BOOL IsRequiringRedraw() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCLCWToolWnd)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCLCWToolWnd)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMExtractionThread thread

class CTMExtractionThread : public CThread
{
	DECLARE_DYNCREATE(CTMExtractionThread)

	// Construction
public:
	CTMExtractionThread();

	// Attributes
private:
	UINT  m_nCharset;
	UINT  m_nTimeFormat;
	CString  m_szDelimiters[3];
	CPtrArray  m_nTimerIDs;
	CUIntArray  m_nProfileIDs;
	CUIntArray  m_nParameterIDs;
	CUIntArray  m_nParameterFormats;
	CUIntArray  m_nParameterTriggers;
	CStringArray  m_szParameterRows;
	CTimeTagArray  m_tParameterTimes;
	CArchivesExtractionProfiles  m_pProfiles;
	CArchivesExtractionProfiles  m_pFTPQueue;
	CArchivesExtractionProfileInfo  m_cProfileInfo;
private:
	CStringArray  m_szErrors;
private:
	CTMEnvironment  m_cTMEnvironment;
	CHistoryTMProcessEngine  m_cTMProcessEngine;
private:
	CEvent  m_bUpdate;
	CEvent  m_bAbort;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL Update(CArchivesExtractionProfileInfo *pProfileInfo);
	BOOL Update(CONST CArchivesExtractionProfiles &pProfiles, CONST CUIntArray &nIDs, CONST CStringArray &szErrors);

	BOOL EnumExtractions(CArchivesExtractionProfiles &pProfiles) CONST;
	BOOL AbortExtractions(CONST CArchivesExtractionProfiles &pProfiles);

private:
	BOOL Extract(CArchivesExtractionProfileInfo *pProfileInfo);
	BOOL Extract(CArchivesExtractionProfileInfo *pProfileInfo, CTMEnvironment *pTMEnvironment, CFile &cFile, BOOL bExtract = TRUE);
	BOOL Extract(CFile &cFile);

	VOID Automate(CArchivesExtractionProfileInfo *pProfileInfo);
	VOID Transfer(CONST CArchivesExtractionProfileInfo *pProfileInfo);
	VOID Alert(CONST CArchivesExtractionProfileInfo *pProfileInfo, BOOL bSuccess);

	INT EnumFTPUsers(CONST CArchivesExtractionProfileInfo *pProfileInfo, CStringArray &szLocations, CStringArray &szUsers, CStringArray &szPasswords) CONST;
	INT ExtractFTPUsersData(LPCTSTR pszData, CStringArray &szData) CONST;

	BOOL TestDirectory(LPCTSTR pszFileName) CONST;

	VOID ShowErrors(CONST CStringArray &szErrors);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMExtractionThread)
public:
	virtual int Run();
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTMExtractionThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMHistoryFileExtractionThread thread

class CTMHistoryFileExtractionThread : public CThread
{
	DECLARE_DYNCREATE(CTMHistoryFileExtractionThread)

	// Construction
public:
	CTMHistoryFileExtractionThread();

	// Attributes
private:
	CHistoryFileExtractionProfiles  m_pProfiles;
private:
	CEvent  m_bUpdate;
	CEvent  m_bAbort;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL Update(CHistoryFileExtractionProfileInfo *pProfileInfo);

	BOOL EnumExtractions(CHistoryFileExtractionProfiles &pProfiles) CONST;
	BOOL AbortExtractions(CONST CHistoryFileExtractionProfiles &pProfiles);

private:
	CString DetermineSourceFile(CONST CHistoryFileExtractionProfileInfo *pProfileInfo, LPCTSTR pszUnitTag, CTimeKey &tUnitTime, CStringArray &szMessages) CONST;
	VOID RemoveSourceFile(CHistoryFileExtractionProfileInfo *pProfileInfo, LPCTSTR pszFileName) CONST;

	CString ConstructFileName(CONST CHistoryFileExtractionProfileInfo *pProfileInfo, CONST CTMEnvironment *pTMEnvironment) CONST;
	BOOL FilterFileData(CONST CHistoryFileExtractionProfileInfo *pProfileInfo, CONST CTMEnvironment *pTMEnvironment) CONST;
	BOOL ConvertFileData(CONST CHistoryFileExtractionProfileInfo *pProfileInfo, CONST CTMEnvironment *pTMEnvironment, CByteArray &nData) CONST;

	VOID CheckMessage(LPCTSTR pszMessage, CONST CStringArray &szErrors, CStringArray &szMessages) CONST;

	VOID Alert(CONST CHistoryFileExtractionProfileInfo *pProfileInfo, BOOL bSuccess);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMHistoryFileExtractionThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTMHistoryFileExtractionThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMArchivesBackupThread thread

// Specify the telemetry archives backup delay interval
#define TELEMETRYARCHIVESBACKUP_DELAY_INTERVAL   SECONDSPERMINUTE
// Specify the telemetry archives backup copy buffer size
#define TELEMETRYARCHIVESBACKUP_COPY_BUFFER   4096

class CTMArchivesBackupThread : public CThread
{
	DECLARE_DYNCREATE(CTMArchivesBackupThread)

	// Construction
public:

	// Attributes
private:
	HANDLE  m_hSync;
	HANDLE  m_bQuit;
	CString  m_szFileName[3];
	CHistoryStoreFile  m_cFile;

	// Operations
public:
	BOOL Start(CONST CHistoryStoreFile *pFile, BOOL bDelayed, HANDLE hSync, HANDLE bQuit);
	BOOL Stop();

private:
	VOID Alert(CONST CHistoryStoreFile *pFile, BOOL bSuccess);

	BOOL TestDirectory(LPCTSTR pszFileName) CONST;

	BOOL DelayBackup();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMArchivesBackupThread)
public:
	virtual int Run();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTMArchivesBackupThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMProcessThread thread

// Specify the telemetry process device related identifiers
#define TMPROCESSTHREAD_DEVICE_TIMEOUT   1000
// Specify the telemetry process thread related timer identifiers
#define TMPROCESSTHREAD_ARCHIVES_TIMERID   10004
#define TMPROCESSTHREAD_ARCHIVES_TIMEOUT   1000

class CTMProcessThread : public CThread
{
	DECLARE_DYNCREATE(CTMProcessThread)

	friend class CTMService;

	// Construction
public:
	CTMProcessThread();
	~CTMProcessThread();

	// Attributes
private:
	CTMEnvironment  *m_pTMEnvironment;
	CTMProcessEngine  *m_pTMProcessEngine;
private:
	CTMProviderDevice  m_cTMDevice;
	CTMProviderDevices  m_pTMDevices;
private:
	CDatabaseTMPacketStreams  m_pTMStreams;
	CTimeTagArray  m_tTMStreams;
	CByteArray  m_bTMStreams;
	CTimeTag  m_tTMStream;
private:
	CStringArray  m_szAlerts;
private:
	UINT_PTR  m_nArchiveBufferTimerID;
	CMutex  m_cArchiveBackupFiles;
	BOOL  m_bArchiveBufferFlash;
private:
	BOOL  m_bDatabaseValidity;
private:
	CEvent  m_cUpdate[4];
	HANDLE  m_hUpdate;
	BOOL  m_bUpdate;
private:
	BOOL  m_bTestMode;

	// Operations
public:
	BOOL Start(LPCTSTR pszName);
	BOOL Suspend();
	BOOL IsSuspended() CONST;
	BOOL Resume();
	VOID Stop();

	BOOL Update();

public:
	INT EnumTMSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	UINT TranslateTMSubSystemToID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToTMSubSystem(UINT nSubSystemID) CONST;

	BOOL SetTMProviderDevices(CONST CTMProviderDevices &pDevices);
	INT GetTMProviderDevices(CTMProviderDevices &pDevices) CONST;
	BOOL HasTMProviderDevices(BOOL bSupported = FALSE) CONST;
	BOOL SetActiveTMProviderDevice(CONST CTMProviderDevice *pDevice);
	BOOL GetActiveTMProviderDevice(CTMProviderDevice *pDevice) CONST;
	BOOL StopActiveTMProviderDevice(HANDLE hDevice = NULL);

	BOOL InitializeTMHistoryStore(CONST CHistoryStoreOptions &pOptions);
	BOOL InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE);
	BOOL InitializeTMData(COolParameters &pOolParameters, BOOL bBadData = FALSE);
	BOOL InitializeTMDump(CMemoryDump &pDump, BOOL bBadData = FALSE);

	BOOL IsTMDump(CONST CTMEnvironment *pTMEnvironment) CONST;

	BOOL UpdateTMDisplays(BOOL bProcessData = TRUE);
	BOOL UpdateTMParameters(CONST CTMParameters &pTMParameters);
	BOOL ResetTMParameters();

	double GetTotalTMBandwidth() CONST;
	double GetAvailableTMBandwidth() CONST;
	double GetMaxDiagnosticTMBandwidth() CONST;
	double GetAvailableDiagnosticTMBandwidth() CONST;
	CTimeTag GetLastTMBandwidthMeasurementTime() CONST;

	BOOL UpdateTMStream();
	BOOL CheckTMStreamInterruption() CONST;
	BOOL CheckTMStreamInterruption(TIMETAG tInterval) CONST;
	BOOL CheckTMStreamCorrelation() CONST;

	BOOL TrackSystemAlerts();
	BOOL TrackSystemAlerts(CONST CSystemAlerts &pAlerts);
	BOOL TrackTelemetryEvents();
	BOOL TrackTelemetryEvents(CONST CTelemetryEvents &pEvents);
	BOOL CheckTelemetryEvent(LPCTSTR pszEvent) CONST;

	BOOL EnableTestMode(BOOL bEnable = TRUE);
	BOOL IsTestModeEnabled() CONST;

private:
	BOOL Initialize();
	BOOL Uninitialize();

	BOOL SetDevice(CONST CTMProviderDevice *pDevice);
	BOOL GetDevice(CTMProviderDevice *pDevice) CONST;
	BOOL StartDevice(CTMProviderDevice *pDevice);
	BOOL StartDevice();
	VOID StopDevice();

	VOID UpdateDisplays();
	VOID UpdateArchives();
	VOID UpdateTCService();
	VOID UpdateOolAlerts();
	VOID UpdateTelemetryEvents();
	VOID UpdateMemoryDumps();
	VOID UpdatePFLPClients();
	VOID UpdateTPEPClients();
	VOID UpdateOOBData();

	VOID Update(CONST CByteArray &nData);
	VOID Update(CONST CTMUnit &cTMUnit);
	VOID Update(CONST CTMTransferUnit &cTMTransferUnit);

	VOID Alert(LPCTSTR pszFileName);
	VOID Alert(LPCTSTR pszStreamName, DWORD dwTimeout);
	VOID Alert(CONST CTelemetryEventInfo *pEventInfo);
	BOOL Evaluate(CONST CTelemetryEventInfo *pEventInfo) CONST;

	VOID DoPrintouts(CONST CTelemetryEventInfo *pEventInfo);
	VOID DoDownloads(CONST CTelemetryEventInfo *pEventInfo);
	VOID DoHistoryFileExtractions(CONST CTelemetryEventInfo *pEventInfo);
	VOID DoHistoricalTelemetryReports(CONST CTelemetryEventInfo *pEventInfo);
	VOID DoUpdateTelecommandSources(CONST CTelemetryEventInfo *pEventInfo);

	BOOL DoBackup(CONST CHistoryStoreFile *pFile, BOOL bDelayed = TRUE);

	BOOL CheckDatabaseValidity(CONST CTMUnit &cTMUnit) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMProcessThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTMProcessThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMService

class CTMService : public CObject
{
	// Construction
public:
	CTMService();

	// Attributes
private:
	typedef struct tagSERVICEINFO {
		INT  cbSize;
		INT  cbServiceInfo;
		INT  cbArchivesSettingsInfo;
		INT  cbArchivesExtractionsInfo;
	} SERVICEINFO, *PSERVICEINFO, *LPSERVICEINFO;
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbDevicesData;
	} DATA, *PDATA, *LPDATA;
private:
	CTMProcessThread  m_cTMProcessThread;
	CTMExtractionThread  m_cTMExtractionThread;
	CTMHistoryFileExtractionThread  m_cTMHistoryFileExtractionThread;
private:
	CHistoryStore  m_cTMHistoryStore;
	CArchivesExtractionProfiles  m_pTMHistoryExtractionProfiles;
private:
	CTimeKey  m_tLastTMRetrieveTime;

	// Operations
public:
	BOOL Start(LPCTSTR pszName);
	BOOL Suspend();
	BOOL IsSuspended() CONST;
	BOOL Resume();
	VOID Stop();

	BOOL Update();

public:
	INT EnumTMSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	UINT TranslateTMSubSystemToID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToTMSubSystem(UINT nSubSystemID) CONST;

	BOOL SetTMProviderDevices(CONST CTMProviderDevices &pDevices);
	INT GetTMProviderDevices(CTMProviderDevices &pDevices) CONST;
	BOOL HasTMProviderDevices(BOOL bSupported = FALSE) CONST;
	BOOL SetActiveTMProviderDevice(CONST CTMProviderDevice *pDevice);
	BOOL GetActiveTMProviderDevice(CTMProviderDevice *pDevice) CONST;
	BOOL StopActiveTMProviderDevice(HANDLE hDevice = NULL);

	BOOL SetTMHistoryFiles(UINT nType, CONST CHistoryStoreFiles &pFiles);
	INT GetTMHistoryFiles(UINT nType, CHistoryStoreFiles &pFiles) CONST;
	INT UpdateTMHistoryFiles(CONST CTMEnvironment *pTMEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors);
	INT UpdateTMHistoryFiles(CHistoryStoreFiles &pFiles, CUIntArray &nErrors);
	BOOL HasTMHistoryFiles(UINT nType) CONST;
	BOOL SetDefaultTMHistoryFile(UINT nType, CONST CHistoryStoreFile &cFile);
	BOOL GetDefaultTMHistoryFile(UINT nType, CHistoryStoreFile &cFile) CONST;
	BOOL SetTMHistoryFilesOptions(CONST CHistoryStoreOptions &pOptions);
	BOOL GetTMHistoryFilesOptions(CHistoryStoreOptions &pOptions) CONST;
	BOOL SetTMHistoryFilesBrowseOptions(CONST CUIntArray &nOptions, CONST CStringArray &szDirectories);
	BOOL GetTMHistoryFilesBrowseOptions(CUIntArray &nOptions, CStringArray &szDirectories) CONST;
	BOOL GetTMHistoryFilesDetails(CString &szArchiveFile, UINT &nArchiveFreeSpace, BOOL &bArchiveStatus, CString &szBackupDirectory, UINT &nBackupFreeSpace, BOOL &bBackupStatus) CONST;
	BOOL GetTMHistoryFilesDetails(CString &szArchiveFile, DWORDLONG &dwArchiveFreeSpace, UINT &nArchiveFreeSpace, BOOL &bArchiveStatus, CString &szBackupDirectory, DWORDLONG &dwBackupFreeSpace, UINT &nBackupFreeSpace, CTimeKey &tBackupTime, BOOL &bBackupStatus) CONST;
	BOOL GetTMHistoryFilesDetails(CString &szDetails) CONST;
	BOOL SetTMHistoryFileExtractionProfiles(CONST CArchivesExtractionProfiles &pProfiles);
	BOOL SetTMHistoryFileExtractionProfiles(CONST CHistoryFileExtractionProfiles &pProfiles);
	BOOL GetTMHistoryFileExtractionProfiles(CArchivesExtractionProfiles &pProfiles) CONST;
	BOOL GetTMHistoryFileExtractionProfiles(CHistoryFileExtractionProfiles &pProfiles) CONST;
	BOOL EnumTMHistoryFileExtractions(CArchivesExtractionProfiles &pProfiles) CONST;
	BOOL EnumTMHistoryFileExtractions(CHistoryFileExtractionProfiles &pProfiles) CONST;
	BOOL ExecuteTMHistoryFileExtraction(CArchivesExtractionProfileInfo *pProfileInfo);
	BOOL ExecuteTMHistoryFileExtraction(CHistoryFileExtractionProfileInfo *pProfileInfo);
	BOOL UpdateTMHistoryFileExtractions(CONST CArchivesExtractionProfiles &pProfiles, CONST CUIntArray &nIDs, CONST CStringArray &szErrors);
	BOOL AbortTMHistoryFileExtractions(CONST CArchivesExtractionProfiles &pProfiles);
	BOOL AbortTMHistoryFileExtractions(CONST CHistoryFileExtractionProfiles &pProfiles);

	BOOL SetRecentTMHistoryTimeKey(CONST CTimeKey &tTime);
	BOOL GetRecentTMHistoryTimeKey(CTimeKey &tTime) CONST;

	BOOL InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE);
	BOOL InitializeTMData(COolParameters &pOolParameters, BOOL bBadData = FALSE);
	BOOL InitializeTMDump(CMemoryDump &pDump, BOOL bBadData = FALSE);

	BOOL IsTMDump(CONST CTMEnvironment *pTMEnvironment) CONST;

	BOOL UpdateTMDisplays(BOOL bProcessData = TRUE);
	BOOL UpdateTMParameters(CONST CTMParameters &pTMParameters);
	BOOL ResetTMParameters();

	double GetTotalTMBandwidth() CONST;
	double GetAvailableTMBandwidth() CONST;
	double GetMaxDiagnosticTMBandwidth() CONST;
	double GetAvailableDiagnosticTMBandwidth() CONST;
	CTimeTag GetLastTMBandwidthMeasurementTime() CONST;

	BOOL UpdateTMStream();
	BOOL CheckTMStreamInterruption() CONST;
	BOOL CheckTMStreamInterruption(TIMETAG tInterval) CONST;
	BOOL CheckTMStreamCorrelation() CONST;

	BOOL TrackSystemAlerts(CONST CSystemAlerts &pAlerts);
	BOOL TrackTelemetryEvents(CONST CTelemetryEvents &pEvents);
	BOOL CheckTelemetryEvent(LPCTSTR pszEvent) CONST;

	BOOL EnableTestMode(BOOL bEnable = TRUE);
	BOOL IsTestModeEnabled() CONST;

	BOOL IsHealthy() CONST;

public:
	BOOL SetServiceInfo(CONST CByteArray &nInfo);
	BOOL GetServiceInfo(CByteArray &nInfo) CONST;
	BOOL UpdateServiceInfo(BOOL bSave = TRUE);

	BOOL Lock();
	BOOL Unlock();

private:
	BOOL SaveServiceInfo();
	BOOL LoadServiceInfo();

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TM_H__
