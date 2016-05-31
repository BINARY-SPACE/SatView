// DEVICE.H : Device Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the device related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DEVICE_H__
#define __DEVICE_H__


/////////////////////////////////////////////////////////////////////////////
// CPFLPCDSTimeCode

// Specify the PFLP CDS time code default epoch
#define PFLP_CDSTIMECODE_EPOCH_YEAR   1958
#define PFLP_CDSTIMECODE_EPOCH_MONTH   January
#define PFLP_CDSTIMECODE_EPOCH_DAY   1
#define PFLP_CDSTIMECODE_EPOCH_HOUR   0
#define PFLP_CDSTIMECODE_EPOCH_MINUTE   0
#define PFLP_CDSTIMECODE_EPOCH_SECOND   0
#define PFLP_CDSTIMECODE_EPOCH_MILLISECOND   0

class CPFLPCDSTimeCode : public CTimeTag
{
	// Construction
public:
	CPFLPCDSTimeCode();
	CPFLPCDSTimeCode(TIMETAG tTimeTag);
	CPFLPCDSTimeCode(CONST CTimeKey &tTimeTag);
	CPFLPCDSTimeCode(CONST CTimeTag &tTimeTag);
	CPFLPCDSTimeCode(CONST FILETIME &tTimeTag);
	CPFLPCDSTimeCode(CONST SYSTEMTIME &tTimeTag);
	CPFLPCDSTimeCode(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond);
	CPFLPCDSTimeCode(INT nYear, INT nDayofYear, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond);
	CPFLPCDSTimeCode(WORD wDay, DWORD dwMilliSeconds, WORD wMicroSeconds);

	// Attributes
private:
	FILETIME  m_tEpoch;

	// Operations
public:
	BOOL SetCDSTime(WORD wDay, DWORD dwMilliSeconds, WORD wMicroSeconds);
	BOOL GetCDSTime(WORD &wDay, DWORD &dwMilliSeconds, WORD &wMicroSeconds) CONST;

	BOOL SetEpoch();
	BOOL SetEpoch(CONST SYSTEMTIME *pTime);
	BOOL GetEpoch(SYSTEMTIME *pTime) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPMessageHeader

// Specify the PFLP message identifier codes
#define PFLP_SERVICE   0x00
#define PFLP_SERVICEREQUEST   0x10
#define PFLP_SERVICEREQUESTRESPONSE   0x11
#define PFLP_SERVICEENDREQUEST   0x60
#define PFLP_SERVICEENDREQUESTRESPONSE   0x61
#define PFLP_DATADISTRIBUTIONREQUEST   0x20
#define PFLP_DATADISTRIBUTIONREQUESTRESPONSE   0x21
#define PFLP_DATADISTRIBUTIONSTOPREQUEST   0x22
#define PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE   0x23
#define PFLP_ACKNOWLEDGMENTMESSAGE   0x42
#define PFLP_STATUSMESSAGE   0x57
#define PFLP_SOURCEPACKET   0x52
#define PFLP_TRANSFERFRAME   0x53
// Specify the PFLP message fixed field codes
#define PFLP_MESSAGEID   0x00
#define PFLP_MESSAGETRAILER   0x00
#define PFLP_MESSAGETRAILEROFFSET   0x00
#define PFLP_MESSAGEVERSION   0x10
#define PFLP_MESSAGENOACKNOWLEDGMENT   0x00
#define PFLP_MESSAGEACKNOWLEDGMENT   0x01
#define PFLP_MESSAGEEPOCHCODE   0x41
#define PFLP_MESSAGEENDIANCODE   0x01020304
// Specify the PFLP message identification length
#define PFLP_MESSAGEIDLENGTH   4
#define PFLP_MESSAGEHEADERLENGTH   24
#define PFLP_MESSAGEPACKETLENGTH   65518
// Specify the PFLP message sequence quality codes
#define PFLP_SEQUENCE_NONE   0xFF
#define PFLP_SEQUENCE_CORRECT   0x00
#define PFLP_SEQUENCE_ERROR   0x10

class CPFLPMessageHeader : public CObject
{
	// Construction
public:
	CPFLPMessageHeader();
	CPFLPMessageHeader(BYTE nID, UINT nLength, BOOL bRequest, BOOL bTrailer = FALSE, UINT nTrailerOffset = 0, BOOL bAcknowledgment = FALSE);

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPCDSTIMECODE {
		WORD  wDay;
		DWORD  dwMilliSeconds;
		WORD  wMicroSeconds;
	} PFLPCDSTIMECODE, *PPFLPCDSTIMECODE, *LPPLFPCDSTIMECODE;
public:
	typedef struct tagPFLPMESSAGEHEADER {
		BYTE  nMessageID;
		BYTE  nMessageLength[3];
		BYTE  bTrailer;
		BYTE  nTrailerOffset[3];
		BYTE  nVersion;
		BYTE  nSystemID;
		WORD  wSequence;
		BYTE  nDataQuality;
		BYTE  nSequenceQuality;
		BYTE  nAcknowledgeRequest;
		BYTE  nReserved;
		PFLPCDSTIMECODE  tTimeCode;
	} PFLPMESSAGEHEADER, *PPFLPMESSAGEHEADER, *LPPFLPMESSAGEHEADER;
#pragma pack(pop)
protected:
	PFLPMESSAGEHEADER  m_sHeader;

	// Operations
public:
	BOOL SetMessageID(BYTE nID);
	BYTE GetMessageID() CONST;
	BOOL SetMessageLength(UINT nLength);
	UINT GetMessageLength() CONST;
	BOOL SetTrailerFlag(BOOL bPresent);
	BOOL GetTrailerFlag() CONST;
	BOOL SetTrailerOffset(UINT nOffset);
	UINT GetTrailerOffset() CONST;
	BOOL SetVersion(BYTE nVersion);
	BYTE GetVersion() CONST;
	BOOL SetSystemID(BYTE nSystemID);
	BYTE GetSystemID() CONST;
	BOOL SetSequenceCount(WORD wCount);
	WORD GetSequenceCount() CONST;
	BOOL SetDataQuality(BYTE nQuality);
	BYTE GetDataQuality() CONST;
	BOOL SetSequenceQuality(BYTE nQuality);
	BYTE GetSequenceQuality() CONST;
	BOOL SetAcknowledgmentFlag(BOOL bPresent);
	BOOL GetAcknowledgmentFlag() CONST;
	BOOL SetEpochCode(BYTE nCode);
	BYTE GetEpochCode() CONST;
	BOOL SetTimeCode(CONST CPFLPCDSTimeCode &tTimeCode);
	BOOL GetTimeCode(CPFLPCDSTimeCode &tTimeCode) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBigEndian = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBigEndian = TRUE);

protected:
	VOID SwapFieldBytes(LPBYTE pData, INT cbData, BOOL bSwap = TRUE) CONST;
	VOID SwapFieldBytes(LPBYTE pData, CONST BYTE *pValue, INT cbData, BOOL bSwap = TRUE) CONST;

	UINT CalcFieldOffset(LPCVOID pBase, LPCVOID pField) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceRequest

// Specify the PFLP service codes
#define PFLP_SERVICE_TM   0x0010
#define PFLP_SERVICE_TC   0x0020

class CPFLPServiceRequest : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPServiceRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPSERVICEREQUEST {
		PFLPMESSAGEHEADER  sHeader;
		CHAR  szClientName[16];
		WORD  wServiceCode;
		DWORD  dwEndianity;
	} PFLPSERVICEREQUEST, *PPFLPSERVICEREQUEST, *LPPFLPSERVICEREQUEST;
#pragma pack(pop)
private:
	PFLPSERVICEREQUEST  m_sData;

	// Operations
public:
	BOOL SetClientName(LPCTSTR pszName);
	CString GetClientName() CONST;
	BOOL SetServiceCode(WORD wCode);
	WORD GetServiceCode() CONST;
	BOOL SetEndianity(DWORD dwEndianity);
	DWORD GetEndianity() CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBigEndian = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBigEndian = TRUE);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceRequestResponse

// Specify the PFLP service codes
#define PFLP_SERVICE_GRANTED   0x0000
#define PFLP_SERVICE_NOTALLOWED   0x0010
#define PFLP_SERVICE_ILLEGALENDIANITY   0x0030
#define PFLP_SERVICE_PROTOCOLERROR   0x0050

class CPFLPServiceRequestResponse : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPServiceRequestResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPSERVICEREQUESTRESPONSE {
		PFLPMESSAGEHEADER  sHeader;
		CHAR  szServerName[16];
		WORD  wServiceCode;
		DWORD  dwEndianity;
	} PFLPSERVICEREQUESTRESPONSE, *PPFLPSERVICEREQUESTRESPONSE, *LPPFLPSERVICEREQUESTRESPONSE;
#pragma pack(pop)
private:
	PFLPSERVICEREQUESTRESPONSE  m_sData;

	// Operations
public:
	BOOL SetServerName(LPCTSTR pszName);
	CString GetServerName() CONST;
	BOOL SetServiceCode(WORD wCode);
	WORD GetServiceCode() CONST;
	BOOL SetEndianity(DWORD dwEndianity);
	DWORD GetEndianity() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceEndRequest

class CPFLPServiceEndRequest : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPServiceEndRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPSERVICEENDREQUEST {
		PFLPMESSAGEHEADER  sHeader;
		WORD  wReason;
	} PFLPSERVICEENDREQUEST, *PPFLPSERVICEENDREQUEST, *LPPFLPSERVICEENDREQUEST;
#pragma pack(pop)
private:
	PFLPSERVICEENDREQUEST  m_sData;

	// Operations
public:
	BOOL SetReason(WORD wReason);
	WORD GetReason() CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBigEndian = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBigEndian = TRUE);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceEndRequestResponse

// Specify the PFLP service codes
#define PFLP_SERVICE_COMPLETED   0x0000
#define PFLP_SERVICE_SYSTEMERROR   0x0010
#define PFLP_SERVICE_REJECTED   0x0020

class CPFLPServiceEndRequestResponse : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPServiceEndRequestResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPSERVICEENDREQUESTRESPONSE {
		PFLPMESSAGEHEADER  sHeader;
		WORD  wResult;
	} PFLPSERVICEENDREQUESTRESPONSE, *PPFLPSERVICEENDREQUESTRESPONSE, *LPPFLPSERVICEENDREQUESTRESPONSE;
#pragma pack(pop)
private:
	PFLPSERVICEENDREQUESTRESPONSE  m_sData;

	// Operations
public:
	BOOL SetResult(WORD wResult);
	WORD GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionRequest

// Specify the PFLP data distribution codes
#define PFLP_DATADISTRIBUTION_REQUESTCODE   0x0001
// Specify the PFLP data distribution level codes
#define PFLP_DATADISTRIBUTION_SOURCEPACKET   0x0000
#define PFLP_DATADISTRIBUTION_TRANSFERFRAME   0x0020
// Specify the PFLP data distribution filter codes
#define PFLP_DATADISTRIBUTION_FILTERCOUNT   0x0001
#define PFLP_DATADISTRIBUTION_FILTER_APID   0x01
#define PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID   0x02
#define PFLP_DATADISTRIBUTION_FILTER_VCID   0x03
#define PFLP_DATADISTRIBUTION_FILTER_NONE   0x04

class CPFLPDataDistributionRequest : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPDataDistributionRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPDATADISTRIBUTIONREQUEST {
		PFLPMESSAGEHEADER  sHeader;
		WORD  wRequest;
		WORD  wLevel;
		WORD  wFilterCount;
		BYTE  nFilterManipulationCode;
		BYTE  nFilterGroupIdentifier;
		WORD  wFilterDataIdentifier;
	} PFLPDATADISTRIBUTIONREQUEST, *PPFLPDATADISTRIBUTIONREQUEST, *LPPFLPDATADISTRIBUTIONREQUEST;
#pragma pack(pop)
private:
	PFLPDATADISTRIBUTIONREQUEST  m_sData;

	// Operations
public:
	BOOL SetRequest(WORD wRequest);
	WORD GetRequest() CONST;
	BOOL SetLevel(WORD wLevel);
	WORD GetLevel() CONST;
	BOOL SetFilterCount(WORD wCount);
	WORD GetFilterCount() CONST;
	BOOL SetFilterManipulationCode(BYTE wCode);
	BYTE GetFilterManipulationCode() CONST;
	BOOL SetFilterGroupIdentifier(BYTE nVCID);
	BYTE GetFilterGroupIdentifier() CONST;
	BOOL SetFilterDataIdentifier(WORD wAPID);
	WORD GetFilterDataIdentifier() CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBigEndian = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBigEndian = TRUE);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionRequestResponse

// Specify the PFLP data distribution codes
#define PFLP_DATADISTRIBUTION_REQUESTCODE   0x0001
// Specify the PFLP data distribution result codes
#define PFLP_DATADISTRIBUTION_REQUESTACCEPTED   0x0000
#define PFLP_DATADISTRIBUTION_REQUESTREJECTED   0x0010
// Specify the PFLP data distribution reason codes
#define PFLP_DATADISTRIBUTION_NOERROR   0x0000
#define PFLP_DATADISTRIBUTION_NOTREADY   0x0010
#define PFLP_DATADISTRIBUTION_NOTSUPPORTED   0x0020
#define PFLP_DATADISTRIBUTION_ILLEGALLEVEL   0x0030
#define PFLP_DATADISTRIBUTION_ILLEGALFILTER   0x0040
#define PFLP_DATADISTRIBUTION_BADREQUEST  0x0050

class CPFLPDataDistributionRequestResponse : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPDataDistributionRequestResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPDATADISTRIBUTIONREQUESTRESPONSE {
		PFLPMESSAGEHEADER  sHeader;
		WORD  wRequest;
		WORD  wResult;
		WORD  wReason;
	} PFLPDATADISTRIBUTIONREQUESTRESPONSE, *PPFLPDATADISTRIBUTIONREQUESTRESPONSE, *LPPFLPDATADISTRIBUTIONREQUESTRESPONSE;
#pragma pack(pop)
private:
	PFLPDATADISTRIBUTIONREQUESTRESPONSE  m_sData;

	// Operations
public:
	BOOL SetRequest(WORD wRequest);
	WORD GetRequest() CONST;
	BOOL SetResult(WORD wResult);
	WORD GetResult() CONST;
	BOOL SetReason(WORD wReason);
	WORD GetReason() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionStopRequest

class CPFLPDataDistributionStopRequest : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPDataDistributionStopRequest();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPDATADISTRIBUTIONSTOPREQUEST {
		PFLPMESSAGEHEADER  sHeader;
		WORD  wReason;
	} PFLPDATADISTRIBUTIONSTOPREQUEST, *PPFLPDATADISTRIBUTIONSTOPREQUEST, *LPPFLPDATADISTRIBUTIONSTOPREQUEST;
#pragma pack(pop)
private:
	PFLPDATADISTRIBUTIONSTOPREQUEST  m_sData;

	// Operations
public:
	BOOL SetReason(WORD wReason);
	WORD GetReason() CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBigEndian = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBigEndian = TRUE);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionStopRequestResponse

// Specify the PFLP data distribution codes
#define PFLP_DATADISTRIBUTION_COMPLETED   0x0000

class CPFLPDataDistributionStopRequestResponse : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPDataDistributionStopRequestResponse();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE {
		PFLPMESSAGEHEADER  sHeader;
		WORD  wResult;
	} PFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE, *PPFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE, *LPPFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE;
#pragma pack(pop)
private:
	PFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE  m_sData;

	// Operations
public:
	BOOL SetResult(WORD wResult);
	WORD GetResult() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPAcknowledgmentMessage

// Specify the PFLP acknowledgment message codes
#define PFLP_MESSAGEACKNOWLEDGMENT_CODE   0xAA55

class CPFLPAcknowledgmentMessage : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPAcknowledgmentMessage();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPACKNOWLEDGMENTMESSAGE {
		PFLPMESSAGEHEADER  sHeader;
		WORD  wCode;
	} PFLPACKNOWLEDGMENTMESSAGE, *PPFLPACKNOWLEDGMENTMESSAGE, *LPPFLPACKNOWLEDGMENTMESSAGE;
#pragma pack(pop)
private:
	PFLPACKNOWLEDGMENTMESSAGE  m_sData;

	// Operations
public:
	BOOL SetCode(WORD wCode);
	WORD GetCode() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPStatusMessage

class CPFLPStatusMessage : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPStatusMessage();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPSTATUSMESSAGE {
		PFLPMESSAGEHEADER  sHeader;
	} PFLPSTATUSMESSAGE, *PPFLPSTATUSMESSAGE, *LPPFLPSTATUSMESSAGE;
#pragma pack(pop)
private:
	PFLPSTATUSMESSAGE  m_sData;

	// Operations
public:
	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPSourcePacket

class CPFLPSourcePacket : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPSourcePacket();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPSOURCEPACKET {
		PFLPMESSAGEHEADER  sHeader;
	} PFLPSOURCEPACKET, *PPFLPSOURCEPACKET, *LPPFLPSOURCEPACKET;
#pragma pack(pop)
private:
	PFLPSOURCEPACKET  m_sData;
	CByteArray  m_nData;

	// Operations
public:
	BOOL SetData(CONST CByteArray &nData);
	INT GetData(CByteArray &nData) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPTransferFrame

class CPFLPTransferFrame : public CPFLPMessageHeader
{
	// Construction
public:
	CPFLPTransferFrame();

	// Attributes
private:
#pragma pack(push,1)
	typedef struct tagPFLPTRANSFERFRAME {
		PFLPMESSAGEHEADER  sHeader;
	} PFLPTRANSFERFRAME, *PPFLPTRANSFERFRAME, *LPPFLPTRANSFERFRAME;
#pragma pack(pop)
private:
	PFLPTRANSFERFRAME  m_sData;
	CByteArray  m_nData;

	// Operations
public:
	BOOL SetData(CONST CByteArray &nData);
	INT GetData(CByteArray &nData) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Check() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServerSocket command target

// Specify the PFLP server socket related timer identifiers
#define PFLPSERVERSOCKET_TIMERID   100
#define PFLPSERVERSOCKET_TIMEOUT   1000

class CPFLPServerSocket : public CSocket
{
	DECLARE_DYNCREATE(CPFLPServerSocket)

	// Construction
public:
	CPFLPServerSocket();
	~CPFLPServerSocket();

	// Attributes
private:
	UINT  m_nPort;
	UINT  m_nPhase;
	WORD  m_wSequence;
	CString  m_szPeer[2];
	CTimeTag  m_tConnect;
	CTimeTag  m_tLastUse;
	UINT_PTR  m_nTimerID[2];
	DWORDLONG  m_cbInBytes;
	DWORDLONG  m_cbOutBytes;
	CPFLPConnection  m_cConnection;
private:
	class CENERTECDevice *m_pDevice;

	// Operations
public:
	BOOL Open(class CENERTECDevice *pDevice);
	BOOL IsOpen() CONST;
	virtual void Close();

	BOOL Abort(LPCTSTR pszAddress, CONST CTimeTag &tConnectTime);

	INT Send(CONST CByteArray &nData);
	INT Send(CONST CByteArray &nData, CONST CTimeSpan &tTimeout);
	INT Receive(CByteArray &nData);
	INT Receive(CByteArray &nData, CONST CTimeSpan &tTimeout);

	BOOL Update(INT nDataID, CONST CByteArray &nData);
	BOOL Update(INT nDataID, CONST CTMUnit &cTMUnit);
	BOOL Update(INT nDataID, CONST CTMTransferUnit &cTMTransferUnit);

	BOOL GetConnectionProperties(CString &szPeerName, CString &szPeerAddress, CTimeTag &tConnectTime, CTimeTag &tLastUseTime, DWORD &cbInBytes, DWORD &cbOutBytes) CONST;

private:
	BOOL Parse(CONST CByteArray &nData, CByteArray &nAcknowledgeData, CByteArray &nResponseData);

	BOOL AdjustClockEpoch(CPFLPCDSTimeCode &tTimeCode);

	CString IdentifyClient();

	BOOL SetPhase(UINT nPhase);
	UINT GetPhase() CONST;

	// Overrides
public:
	virtual BOOL OnMessagePending();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServerSockets

class CPFLPServerSockets : public CPtrArray
{
	// Construction
public:
	CPFLPServerSockets();
	~CPFLPServerSockets();

	// Attributes
public:

	// Operations
public:
	BOOL Add(CPFLPServerSocket *pSocket);

	INT Enum(CStringArray &szComputers) CONST;
	INT Enum(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST;
	VOID Update(INT nDataID, CONST CByteArray &nData);
	VOID Update(INT nDataID, CONST CTMUnit &cTMUnit);
	VOID Update(INT nDataID, CONST CTMTransferUnit &cTMTransferUnit);

	CPFLPServerSocket *GetAt(INT nIndex) CONST;
	CPFLPServerSocket *operator[](INT nIndex) CONST;

	BOOL Abort(LPCTSTR pszAddress, CONST CTimeTag &tConnectTime);

	VOID RemoveAll();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPClientSocket command target

// Specify the PFLP client socket related timer identifiers
#define PFLPCLIENTSOCKET_TIMERID   101
#define PFLPCLIENTSOCKET_TIMEOUT   1000

class CPFLPClientSocket : public CSocket
{
	DECLARE_DYNCREATE(CPFLPClientSocket)

	// Construction
public:
	CPFLPClientSocket();

	// Attributes
private:
	UINT  m_nPort;
	UINT  m_nPhase;
	WORD  m_wSequence;
	BOOL  m_bSession[2];
	CString  m_szPeer[2];
	CTimeTag  m_tConnect;
	CTimeTag  m_tLastUse;
	UINT_PTR  m_nTimerID[2];
	DWORDLONG  m_cbInBytes;
	DWORDLONG  m_cbOutBytes;
	CByteArray  m_nData;
private:
	CTimeTag  m_tClockAdjustment[4];
	CTimeSpan  m_tClockInterval;
private:
	class CENERTECDevice *m_pDevice;

	// Operations
public:
	BOOL Open(class CENERTECDevice *pDevice);
	BOOL IsOpen() CONST;
	virtual void Close();

	BOOL Connect(LPCTSTR pszAddress, UINT nPort, CONST CTimeSpan &tTimeout);
	BOOL Abort(LPCTSTR pszAddress, CONST CTimeTag &tConnectTime);

	INT Send(CONST CByteArray &nData);
	INT Send(CONST CByteArray &nData, CONST CTimeSpan &tTimeout);
	INT Receive(CByteArray &nData);
	INT Receive(CByteArray &nData, CONST CTimeSpan &tTimeout, BOOL bSession = FALSE);

	BOOL Update(INT nDataID, CONST CTCUnit &cTCUnit);
	BOOL Update(INT nDataID, CONST CTCTransferUnit &cTCTransferUnit);

	BOOL GetConnectionProperties(CString &szPeerName, CString &szPeerAddress, CTimeTag &tConnectTime, CTimeTag &tLastUseTime, DWORD &cbInBytes, DWORD &cbOutBytes) CONST;

private:
	BOOL StartDataService(CONST CTimeSpan &tTimeout);
	BOOL StopDataService(CONST CTimeSpan &tTimeout);
	BOOL StartDataDistribution(CONST CTimeSpan &tTimeout, WORD nLevel = PFLP_DATADISTRIBUTION_SOURCEPACKET);
	BOOL StopDataDistribution(CONST CTimeSpan &tTimeout);

	BOOL Parse(CByteArray &nData);

	VOID AdjustClockTime();
	BOOL AdjustClockTime(CONST CPFLPCDSTimeCode &tTimeCode);
	BOOL AdjustClockTime(CONST CTimeTag &tTimeCode);
	BOOL AdjustClockDeviation(CONST CTimeTag &tTimeCode);
	BOOL AdjustClockEpoch(CPFLPCDSTimeCode &tTimeCode);

	BOOL CheckDataStreamDrop(TIMETAG tInterval) CONST;
	BOOL CheckDataStreamDelay(TIMETAG tDelay, TIMETAG tInterval) CONST;

	BOOL SetPhase(UINT nPhase);
	UINT GetPhase() CONST;

	// Overrides
public:
	virtual BOOL OnMessagePending();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPClientSockets

class CPFLPClientSockets : public CPtrArray
{
	// Construction
public:
	CPFLPClientSockets();
	~CPFLPClientSockets();

	// Attributes
public:

	// Operations
public:
	BOOL Add(CPFLPClientSocket *pSocket);

	INT Enum(CStringArray &szComputers) CONST;
	INT Enum(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST;

	VOID Update(INT nDataID, CONST CTCUnit &cTCUnit);
	VOID Update(INT nDataID, CONST CTCTransferUnit &cTCTransferUnit);

	CPFLPClientSocket *GetAt(INT nIndex) CONST;
	CPFLPClientSocket *operator[](INT nIndex) CONST;

	BOOL Abort(LPCTSTR pszAddress, CONST CTimeTag &tConnectTime);

	VOID RemoveAll();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceSocket command target

class CPFLPServiceSocket : public CSocket
{
	DECLARE_DYNCREATE(CPFLPServiceSocket)

	// Construction
public:
	CPFLPServiceSocket();

	// Attributes
private:
	CPFLPServerSockets  m_pServerSockets;
	CPFLPClientSockets  m_pClientSockets;
private:
	class CENERTECDevice *m_pDevice;

	// Operations
public:
	BOOL Open(class CENERTECDevice *pDevice, UINT nPort);
	BOOL IsOpen() CONST;
	virtual VOID Close();

	INT EnumConnections(CStringArray &szComputers) CONST;
	INT EnumConnections(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST;
	BOOL UpdateConnections(INT nDataID, CONST CByteArray &nData);
	BOOL UpdateConnections(INT nDataID, CONST CTMUnit &cTMUnit);
	BOOL UpdateConnections(INT nDataID, CONST CTMTransferUnit &cTMTransferUnit);
	VOID UpdateConnections(INT nDataID, CONST CTCUnit &cTCUnit);
	VOID UpdateConnections(INT nDataID, CONST CTCTransferUnit &cTCTransferUnit);

	BOOL AddConnection(CPFLPServerSocket *pSocket);
	BOOL AddConnection(CPFLPClientSocket *pSocket);

	BOOL AbortConnection(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime);

	// Overrides
public:
	virtual void OnAccept(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceThread

class CENERTECDeviceThread : public CThread
{
	DECLARE_DYNCREATE(CENERTECDeviceThread)

	// Construction
public:
	CENERTECDeviceThread();
	~CENERTECDeviceThread();

	// Attributes
private:
	CENERTECDevice  *m_pIODevice[2];
	HANDLE  m_hIODeviceData[2];
	CEvent  m_cIODeviceEvent;
	DWORD  m_dwIODevice;
private:
	CPtrArray  m_pIODeviceData[2];
	CTMUnits  m_pIODeviceTMUnits[2];
	CTCUnits  m_pIODeviceTCUnits[2];
	CTMTransferUnits  m_pIODeviceTMTransferUnits[2];
	CTCTransferUnits  m_pIODeviceTCTransferUnits[2];
	CUIntArray  m_nIODeviceDataIDs[5];
	INT  m_nIODeviceDataID;
private:
	CStringArray  m_szAbortConnections;
	CTimeTagArray  m_tAbortConnections;
private:
	CPFLPServiceSocket  m_cPFLPServiceSocket;

	// Operations
public:
	BOOL Start(CENERTECDevice *pDevice);
	BOOL Suspend();
	BOOL IsSuspended() CONST;
	BOOL Resume();
	BOOL Stop();

	BOOL Configure(CONST CENERTECDevice *pDevice);

	INT EnumConnections(CStringArray &szComputers) CONST;
	INT EnumConnections(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST;
	BOOL AbortConnection(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime);

	INT AddData(CONST CByteArray &nData, BOOL bInData = TRUE);
	INT AddData(CONST CTMUnit &cTMUnit, BOOL bInData = TRUE);
	INT AddData(CONST CTMTransferUnit &cTMTransferUnit, BOOL bInData = TRUE);
	INT AddData(CONST CTCUnit &cTCUnit, BOOL bInData = TRUE);
	INT AddData(CONST CTCTransferUnit &cTCTransferUnit, BOOL bInData = TRUE);
	INT RemoveData(CByteArray &nData, BOOL bInData = TRUE);
	INT RemoveData(CTMUnit &cTMUnit, BOOL bInData = TRUE);
	INT RemoveData(CTMTransferUnit &cTMTransferUnit, BOOL bInData = TRUE);
	INT RemoveData(CTCUnit &cTCUnit, BOOL bInData = TRUE);
	INT RemoveData(CTCTransferUnit &cTCTransferUnit, BOOL bInData = TRUE);
	BOOL ClearData(BOOL bInData = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CENERTECDeviceThread)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CENERTECDeviceThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CENERTECDevice

// Specify the ENERTEC device configuration related identifiers
#define ENERTECDEVICE_MINIMUMID   1
#define ENERTECDEVICE_MAXIMUMID   255
#define ENERTECDEVICE_DEFAULTID   1
#define ENERTECDEVICE_MINIMUMPORT   1024
#define ENERTECDEVICE_MAXIMUMPORT   65535
#define ENERTECDEVICE_DEFAULTPORT   3021
#define ENERTECDEVICE_MINIMUMBUFFER   1
#define ENERTECDEVICE_MAXIMUMBUFFER   256
#define ENERTECDEVICE_DEFAULTBUFFER   32
#define ENERTECDEVICE_MINIMUMTIMEOUT   1
#define ENERTECDEVICE_MAXIMUMTIMEOUT   SECONDSPERMINUTE
#define ENERTECDEVICE_DEFAULTTIMEOUT   2
#define ENERTECDEVICE_MINIMUMAPIDFILTER   0
#define ENERTECDEVICE_MAXIMUMAPIDFILTER   2047
#define ENERTECDEVICE_DEFAULTAPIDFILTER   1
#define ENERTECDEVICE_MINIMUMVCIDFILTER   0
#define ENERTECDEVICE_MAXIMUMVCIDFILTER   255
#define ENERTECDEVICE_DEFAULTVCIDFILTER   1
#define ENERTECDEVICE_MINIMUMTIMEERROR   -2147483647
#define ENERTECDEVICE_MAXIMUMTIMEERROR   2147483647
#define ENERTECDEVICE_DEFAULTTIMEERROR   0
#define ENERTECDEVICE_MINIMUMTIMEDELTA   -2147483647
#define ENERTECDEVICE_MAXIMUMTIMEDELTA   2147483647
#define ENERTECDEVICE_DEFAULTTIMEDELTA   0
#define ENERTECDEVICE_MINIMUMEPOCHYEAR   1900
#define ENERTECDEVICE_MAXIMUMEPOCHYEAR   2000
#define ENERTECDEVICE_DEFAULTEPOCHYEAR   1958
#define ENERTECDEVICE_MINIMUMCLOCKADJUSTMENTINTERVAL   1
#define ENERTECDEVICE_MAXIMUMCLOCKADJUSTMENTINTERVAL   MINUTESPERHOUR
#define ENERTECDEVICE_DEFAULTCLOCKADJUSTMENTINTERVAL   5
#define ENERTECDEVICE_MINIMUMSTATUSMESSAGEINTERVAL   1
#define ENERTECDEVICE_MAXIMUMSTATUSMESSAGEINTERVAL   SECONDSPERHOUR
#define ENERTECDEVICE_DEFAULTSTATUSMESSAGEINTERVAL   10
// Specify the ENERTEC device status codes related identifiers
#define ENERTECDEVICE_DATAQUALITY_NONE   ((BYTE) (0<<0))
#define ENERTECDEVICE_PMDEMODULATOR_LOCKED   ((BYTE) (1<<7))
#define ENERTECDEVICE_PSKDEMODULATOR_LOCKED   ((BYTE) (1<<6))
#define ENERTECDEVICE_BITSYNCHRONIZER_LOCKED   ((BYTE) (1<<5))
#define ENERTECDEVICE_VITDECODER_LOCKED   ((BYTE) (1<<4))
#define ENERTECDEVICE_FRAMESYNCHRONIZER_SEARCH   ((BYTE) (0<<2))
#define ENERTECDEVICE_FRAMESYNCHRONIZER_CONTROL   ((BYTE) (1<<2))
#define ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED   ((BYTE) (3<<2))
#define ENERTECDEVICE_REEDCRC_CRCERRORS   ((BYTE) (0<<0))
#define ENERTECDEVICE_REEDCRC_NOERRORS   ((BYTE) (1<<0))
#define ENERTECDEVICE_REEDCRC_REEDERRORS   ((BYTE) (2<<0))
#define ENERTECDEVICE_REEDCRC_CORRERRORS   ((BYTE) (3<<0))
#define ENERTECDEVICE_SEQUENCEQUALITY_NONE   (1<<8)
#define ENERTECDEVICE_SEQUENCEQUALITY_GOOD   (1<<9)
#define ENERTECDEVICE_SEQUENCEQUALITY_BAD   (1<<10)
// Specify the ENERTEC device related timer identifiers
#define ENERTECDEVICE_DATASTREAMDROP_TIMERID   102
#define ENERTECDEVICE_DATASTREAMDROP_TIMEOUT   1000

class CENERTECDevice : public CIODevice
{
	DECLARE_DYNCREATE(CENERTECDevice)

	// Construction
public:
	CENERTECDevice();
	~CENERTECDevice();

	// Attributes
private:
	typedef struct tagDATA {
		BYTE  nDeviceID;
		UINT  nDeviceMode;
		UINT  nBufferSize;
		WORD  wDataFilter[2];
		LONG  tCorrelationError;
		LONG  tCorrelationDelta;
		SOCKADDR_IN  sIPAddress;
		SYSTEMTIME  tEpochTime;
		TIMEKEY  tTimeout;
		TIMEKEY  tClockAdjustment;
		TIMEKEY  tStatusMessageInterval;
	} DATA, *PDATA, *LPDATA;
private:
	WORD  m_wIODataStatus;
	BOOL  m_bDelayedIOData;
	CTimeKey  m_tIODataDrop;
private:
	CStringArray  m_szLogins;
	CTimeTagArray  m_tLogins;
private:
	CENERTECDeviceThread  *m_pIOThread;
private:
	static CPtrArray  m_pIODevices;
	static CPtrArray  m_nIODeviceTimerIDs;

	// Operations
public:
	VOID SetDeviceID(BYTE nID);
	BOOL GetDeviceID(BYTE &nID) CONST;
	VOID SetDeviceMode(UINT nFlags);
	BOOL GetDeviceMode(UINT &nFlags) CONST;
	BOOL SetIPAddress(LPCTSTR pszAddress, UINT nPort);
	VOID SetIPAddress(CONST SOCKADDR_IN *pAddress);
	BOOL GetIPAddress(CString &szAddress, UINT &nPort) CONST;
	BOOL GetIPAddress(SOCKADDR_IN *pAddress) CONST;
	VOID SetTimeout(CONST CTimeSpan &tInterval);
	BOOL GetTimeout(CTimeSpan &tInterval) CONST;
	VOID SetBufferSize(UINT nSize);
	BOOL GetBufferSize(UINT &nSize) CONST;
	VOID SetVCIDFilter(WORD wVCID);
	BOOL GetVCIDFilter(WORD &wVCID) CONST;
	VOID SetAPIDFilter(WORD wAPID);
	BOOL GetAPIDFilter(WORD &wAPID) CONST;
	BOOL SetTimeEpoch(CONST SYSTEMTIME *pTime);
	BOOL GetTimeEpoch(SYSTEMTIME *pTime) CONST;
	VOID SetTimeCorrelation(LONG tError, LONG tDelta);
	BOOL GetTimeCorrelation(LONG &tError, LONG &tDelta) CONST;
	VOID SetClockAdjustmentInterval(CONST CTimeSpan &tInterval);
	BOOL GetClockAdjustmentInterval(CTimeSpan &tInterval) CONST;
	VOID SetStatusMessageInterval(CONST CTimeSpan &tInterval);
	BOOL GetStatusMessageInterval(CTimeSpan &tInterval) CONST;
	CTimeSpan GetDataStreamDropInterval() CONST;
	CTimeSpan GetDataStreamDelayInterval() CONST;

	BOOL AddClient(LPCTSTR pszClient, CONST CTimeTag &tConnectTime);
	BOOL RemoveClient(LPCTSTR pszClient, CONST CTimeTag &tConnectTime);
	BOOL AuthorizeClient(LPCTSTR pszClient, BOOL bAudit = TRUE);
	VOID AuthorizeAllClients(BOOL bAudit = TRUE);

	INT AddData(CONST CByteArray &nData, BOOL bInData = TRUE);
	INT AddData(CONST CTMUnit &cTMUnit, BOOL bInData = TRUE);
	INT AddData(CONST CTMTransferUnit &cTMTransferUnit, BOOL bInData = TRUE);
	INT AddData(CONST CTCUnit &cTCUnit, BOOL bInData = TRUE);
	INT AddData(CONST CTCTransferUnit &cTCTransferUnit, BOOL bInData = TRUE);
	BOOL RemoveData(CByteArray &nData, BOOL bInData = TRUE);
	BOOL RemoveData(CTMUnit &cTMUnit, BOOL bInData = TRUE);
	BOOL RemoveData(CTMTransferUnit &cTMTransferUnit, BOOL bInData = TRUE);
	BOOL RemoveData(CTCUnit &cTCUnit, BOOL bInData = TRUE);
	BOOL RemoveData(CTCTransferUnit &cTCTransferUnit, BOOL bInData = TRUE);
	BOOL ClearData(BOOL bAll = TRUE);

	BOOL UpdateStatus(WORD wStatus);
	BOOL UpdateStatus(BYTE nDataQuality, BYTE nSequenceQuality);
	BOOL TranslateStatus(CString &szStatus, UINT &nStatus) CONST;
	BOOL TranslateStatus(CString &szStatus) CONST;

	BOOL UpdateDataStatus(INT nDataID, UINT nStatus, BOOL bSuccess);

private:
	VOID AllocateData();
	VOID FreeData();

	VOID TrackData();
	VOID TrackData(CONST CTimeTag &tLastIOData);

	LPDATA GetData() CONST;

private:
	static VOID CALLBACK TrackDataDropProcedure(HWND hWnd, UINT nMsg, UINT_PTR nEventID, DWORD dwTime);

public:
	virtual BOOL Start();
	virtual BOOL Suspend();
	virtual BOOL IsSuspended() CONST;
	virtual BOOL Resume();
	virtual BOOL Stop();

	virtual BOOL Initialize(UINT nFlags);
	virtual BOOL Initialize(UINT nFlags, CONST CTimeSpan &tDataDrop, CONST CTimeSpan &tDataDelay, IODEVICESTATUSPROCEDURE pStatusProcedure = NULL, IODEVICEDATASTATUSPROCEDURE pDataStatusProcedure = NULL, IODEVICEMESSAGEPROCEDURE pMessageProcedure = NULL);
	virtual BOOL Configure(CWnd *pParentWnd = NULL, UINT nAllowedTypes = IODEVICE_TYPE_SERVER | IODEVICE_TYPE_CLIENT, BOOL bReadOnly = FALSE);
	virtual BOOL Update(CONST CIODevice *pDevice, BOOL &bRestart);

	virtual INT Send(CONST CByteArray &nData);
	virtual INT Send(CONST CTMUnit &cTMUnit);
	virtual INT Send(CONST CTMTransferUnit &cTMTransferUnit);
	virtual INT Send(CONST CTCUnit &cTCUnit);
	virtual INT Send(CONST CTCTransferUnit &cTCTransferUnit);
	virtual BOOL Receive(CByteArray &nData);
	virtual BOOL Receive(CTMUnit &cTMUnit);
	virtual BOOL Receive(CTMTransferUnit &cTMTransferUnit);
	virtual BOOL Receive(CTCUnit &cTCUnit);
	virtual BOOL Receive(CTCTransferUnit &cTCTransferUnit);
	virtual BOOL Clear(BOOL bAll = TRUE);

	virtual BOOL SetStatus(LPCTSTR pszStatus);
	virtual CString GetStatus() CONST;
	virtual BOOL SetStatusIndication(UINT nStatus);
	virtual UINT GetStatusIndication() CONST;

	virtual UINT GetCapabilities() CONST;
	virtual CString GetDetails() CONST;

	virtual INT EnumConnections(CStringArray &szComputers) CONST;
	virtual INT EnumConnections(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST;
	virtual BOOL AbortConnection(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime);

	virtual BOOL IsLocal() CONST;

	virtual BOOL Copy(CONST CIODevice *pDevice);
	virtual BOOL Compare(CONST CIODevice *pDevice) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DEVICE_H__
