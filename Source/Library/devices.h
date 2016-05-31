// DEVICES.H : Devices Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the devices related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DEVICES_H__
#define __DEVICES_H__

#include "event.h"
#include "ttcprocess.h"


/////////////////////////////////////////////////////////////////////////////
// CIODevice

// Specify the device related flags
#define IODEVICE_TYPE_SERVER   (1<<0)
#define IODEVICE_TYPE_CLIENT   (1<<1)
#define IODEVICE_SERVICE_TM   (1<<2)
#define IODEVICE_SERVICE_TC   (1<<3)
#define IODEVICE_DATASERVICE_RAW   (1<<4)
#define IODEVICE_DATASERVICE_SOURCEPACKETS   (1<<5)
#define IODEVICE_DATASERVICE_TRANSFERFRAMES   (1<<6)
#define IODEVICE_PROTOCOL_PFLP   (1<<7)
// Specify the device security related codes
#define IODEVICE_SECURITY_UNLIMITEDACCESS   (1<<0)
#define IODEVICE_SECURITY_RESTRICTEDACCESS   (1<<1)
#define IODEVICE_SECURITY_DENIEDACCESS   (1<<2)
#define IODEVICE_SECURITY_AUDITACCESS   (1<<3)
// Specify the device status indication codes
#define IODEVICE_STATUS_GOOD   (1<<0)
#define IODEVICE_STATUS_WARNING   (1<<1)
#define IODEVICE_STATUS_ERROR   (1<<2)
#define IODEVICE_STATUS_CONNECTED   (1<<3)
#define IODEVICE_STATUS_NOTCONNECTED   (1<<4)
#define IODEVICE_STATUS_ONLINE   (1<<5)
#define IODEVICE_STATUS_OFFLINE   (1<<6)
#define IODEVICE_STATUS_CLOSED   (1<<7)
// Specify the device login related flags
#define IODEVICE_LOGIN_SUCCESS   (1<<0)
#define IODEVICE_LOGIN_FAILURE   (1<<1)
#define IODEVICE_LOGOUT_SUCCESS   (1<<2)
#define IODEVICE_LOGINOUT_AUDIT   (1<<3)
// Specify the device data stream related flags
#define IODEVICE_DATASTREAM_DROP   (1<<0)
#define IODEVICE_DATASTREAM_RECONNECTED   (1<<1)
#define IODEVICE_DATASTREAM_DELAYED   (1<<2)
#define IODEVICE_DATASTREAM_BACKINTIME   (1<<3)
// Specify the device data status related flags
#define IODEVICE_DATASTATUS_SENT   (1<<0)
#define IODEVICE_DATASTATUS_PROCESSED   (1<<1)
// Specify the device messages related types
#define IODEVICE_MESSAGETYPE_INFORMATIONAL   EVENT_TYPE_INFORMATIONAL
#define IODEVICE_MESSAGETYPE_SUCCESS   EVENT_TYPE_SUCCESS
#define IODEVICE_MESSAGETYPE_WARNING   EVENT_TYPE_WARNING
#define IODEVICE_MESSAGETYPE_ERROR   EVENT_TYPE_ERROR
// Define the device related callback procedure types
typedef VOID(CALLBACK *IODEVICELOGINSPROCEDURE)(UINT nFlags, LPCTSTR pszClient, TIMETAG tConnectTime, LPVOID pData);
typedef VOID(CALLBACK *IODEVICESTATUSPROCEDURE)(LPCTSTR pszStatus, UINT nStatus);
typedef VOID(CALLBACK *IODEVICEMESSAGEPROCEDURE)(LPCTSTR pszMessage, UINT nMessageType);
typedef VOID(CALLBACK *IODEVICEDATASTREAMPROCEDURE)(UINT nFlags, TIMEKEY tInterval, LPVOID pData);
typedef VOID(CALLBACK *IODEVICEDATASTATUSPROCEDURE)(INT nDataID, UINT nStatus, BOOL bSuccess);

class AFX_EXT_CLASS CIODevice : public CObject
{
	DECLARE_DYNCREATE(CIODevice)

	// Construction
public:
	CIODevice();
	~CIODevice();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbIODevice[2];
		INT  cbIODeviceData;
		INT  cbSecurityUsers;
		INT  cbSecurityCodes;
		INT  cbSecurityTimes[2];
		UINT  nOperationsCode;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szIODevice[3];
	HINSTANCE  m_hIODevice;
	CIODevice  *m_pIODevice;
	CByteArray  m_nIODeviceData;
	CEvent  m_cIODeviceData[2];
	CString  m_szIODeviceStatus;
	UINT  m_nIODeviceStatus;
protected:
	UINT  m_nOperationsType;
	UINT  m_nOperationsCode;
	UINT  m_nOperationsLoginsMask;
	UINT  m_nOperationsDataStreamMask;
	LPVOID  m_pOperationsLoginsData;
	LPVOID  m_pOperationsDataStreamData;
	CTimeSpan  m_tOperationsDataDrop[2];
	CTimeSpan  m_tOperationsDataDelay[2];
	CUIntArray  m_nSecurityCodes;
	CStringArray  m_szSecurityUsers;
	CTimeKeyArray  m_tSecurityStartTimes;
	CTimeKeyArray  m_tSecurityStopTimes;
protected:
	IODEVICELOGINSPROCEDURE  m_pIODeviceLoginsProcedure;
	IODEVICESTATUSPROCEDURE  m_pIODeviceStatusProcedure;
	IODEVICEMESSAGEPROCEDURE  m_pIODeviceMessageProcedure;
	IODEVICEDATASTREAMPROCEDURE  m_pIODeviceDataStreamProcedure;
	IODEVICEDATASTATUSPROCEDURE  m_pIODeviceDataStatusProcedure;
protected:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Open();
	BOOL Open(LPCTSTR pszName, LPCTSTR pszDeviceBrand);
	BOOL IsOpen() CONST;
	VOID Close();

	VOID SetDeviceBrand(LPCTSTR pszDeviceBrand);
	CString GetDeviceBrand() CONST;
	VOID SetDeviceName(LPCTSTR pszDeviceName);
	CString GetDeviceName() CONST;
	VOID SetDeviceModule(LPCTSTR pszDeviceModule);
	CString GetDeviceModule() CONST;
	VOID SetDeviceProperties(CONST CByteArray &nDeviceData);
	INT GetDeviceProperties(CByteArray &nDeviceData) CONST;
	VOID SetDeviceSecurity(CONST CStringArray &szUsers, CONST CUIntArray &nCodes, CONST CTimeKeyArray &tStartTimes, CONST CTimeKeyArray &tStopTimes);
	INT GetDeviceSecurity(CStringArray &szUsers, CUIntArray &nCodes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST;

	BOOL MonitorDeviceLogins(UINT nMask = 0, IODEVICELOGINSPROCEDURE pLoginProcedure = NULL, LPVOID pData = NULL);
	BOOL MonitorDeviceDataStream(UINT nMask = 0, CONST CTimeSpan &tInterval = 0, IODEVICEDATASTREAMPROCEDURE pDataStreamProcedure = NULL, LPVOID pData = NULL);
	BOOL MonitorDeviceDataBuffers(HANDLE &hInBuffer, HANDLE &hOutBuffer);

	BOOL ShowDeviceStatus(LPCTSTR pszStatus, UINT nStatus);
	BOOL ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType = IODEVICE_MESSAGETYPE_ERROR);

	CIODevice *GetIODevice() CONST;

	BOOL Lock();
	BOOL Unlock();

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

	virtual BOOL Map(CByteArray &nInfo) CONST;
	virtual BOOL Unmap(CONST CByteArray &nInfo);

private:
	BOOL Synchronize();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CIODevices

class AFX_EXT_CLASS CIODevices : public CPtrArray
{
	// Construction
public:
	CIODevices();
	~CIODevices();

	// Attributes
public:

	// Operations
public:
	INT Add(CIODevice *pIODevice);

	INT Find(LPCTSTR pszDeviceBrand, LPCTSTR pszDeviceName) CONST;

	CIODevice *GetAt(INT nIndex) CONST;
	CIODevice *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CIODevices *pIODevices);
	BOOL Compare(CONST CIODevices *pIODevices) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

protected:
	INT FindIndex(LPCTSTR pszDeviceBrand, LPCTSTR pszDeviceName, BOOL bInsert = FALSE) CONST;

	CString ConstructFullName(LPCTSTR pszDeviceBrand, LPCTSTR pszDeviceName) CONST;
	CString ConstructFullName(CONST CIODevice *pDevice) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DEVICES_H__
