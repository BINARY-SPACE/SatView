// DEVICES.CPP : Devices Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the devices related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CIODevice

IMPLEMENT_DYNCREATE(CIODevice, CObject)

CIODevice::CIODevice() : CObject()
{
	m_szIODeviceStatus.Empty();
	m_nIODeviceStatus = 0;
	m_nOperationsType = 0;
	m_nOperationsLoginsMask = 0;
	m_nOperationsDataStreamMask = 0;
	m_tOperationsDataDrop[0] = 0;
	m_tOperationsDataDrop[1] = 0;
	m_tOperationsDataDelay[0] = 0;
	m_tOperationsDataDelay[1] = 0;
	m_pOperationsLoginsData = (LPVOID)NULL;
	m_pOperationsDataStreamData = (LPVOID)NULL;
	m_hIODevice = (HINSTANCE)NULL;
	m_pIODevice = (CIODevice *)NULL;
	m_pIODeviceLoginsProcedure = (IODEVICELOGINSPROCEDURE)NULL;
	m_pIODeviceStatusProcedure = (IODEVICESTATUSPROCEDURE)NULL;
	m_pIODeviceMessageProcedure = (IODEVICEMESSAGEPROCEDURE)NULL;
	m_pIODeviceDataStreamProcedure = (IODEVICEDATASTREAMPROCEDURE)NULL;
	m_pIODeviceDataStatusProcedure = (IODEVICEDATASTATUSPROCEDURE)NULL;
	m_pCriticalSection = new CCriticalSection;
}

CIODevice::~CIODevice()
{
	Close();
	delete m_pCriticalSection;
}

BOOL CIODevice::Open()
{
	return Open(m_szIODevice[2], m_szIODevice[0]);
}
BOOL CIODevice::Open(LPCTSTR pszName, LPCTSTR pszDeviceBrand)
{
	CString  szIODevice;
	CIODevice *(__cdecl *pIODevice)(VOID);

	if (IsOpen())
	{
		if (GetDeviceBrand() == pszDeviceBrand)
		{
			Synchronize();
			return TRUE;
		}
		Close();
	}
	if ((m_hIODevice = AfxLoadLibrary(pszName)))
	{
#ifndef UNICODE
		szIODevice = STRING(IDS_EXPORTINTERFACE_IODEVICEENGINE);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_IODEVICEENGINE), -1, (LPSTR)szIODevice.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_IODEVICEENGINE))), lstrlen(STRING(IDS_EXPORTINTERFACE_IODEVICEENGINE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szIODevice.ReleaseBuffer();
#endif
		if ((pIODevice = (CIODevice *(__cdecl *)(VOID)) GetProcAddress(m_hIODevice, (LPCSTR)(LPCTSTR)szIODevice)))
		{
			if ((m_pIODevice = pIODevice()))
			{
				m_szIODevice[0] = pszDeviceBrand;
				m_szIODevice[2] = pszName;
				Synchronize();
				return TRUE;
			}
		}
		Close();
	}
	return FALSE;
}

BOOL CIODevice::IsOpen() CONST
{
	return((m_pIODevice != (CIODevice *)NULL  &&  m_pIODevice != this) ? TRUE : FALSE);
}

VOID CIODevice::Close()
{
	CIODevice  *pIODevice;

	if ((pIODevice = m_pIODevice))
	{
		m_pIODevice = (CIODevice *)NULL;
		pIODevice->Stop();
		delete pIODevice;
	}
	if (m_hIODevice != (HINSTANCE)NULL)
	{
		AfxFreeLibrary(m_hIODevice);
		m_hIODevice = (HINSTANCE)NULL;
	}
}

VOID CIODevice::SetDeviceBrand(LPCTSTR pszDeviceBrand)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_szIODevice[0] = pszDeviceBrand; IsOpen(); )
	{
		m_pIODevice->m_szIODevice[0] = pszDeviceBrand;
		break;
	}
}

CString CIODevice::GetDeviceBrand() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szIODevice[0];
}

VOID CIODevice::SetDeviceName(LPCTSTR pszDeviceName)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_szIODevice[1] = pszDeviceName; IsOpen(); )
	{
		m_pIODevice->m_szIODevice[1] = pszDeviceName;
		break;
	}
}

CString CIODevice::GetDeviceName() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szIODevice[1];
}

VOID CIODevice::SetDeviceModule(LPCTSTR pszDeviceModule)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_szIODevice[2] = pszDeviceModule; IsOpen(); )
	{
		m_pIODevice->m_szIODevice[2] = pszDeviceModule;
		break;
	}
}

CString CIODevice::GetDeviceModule() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szIODevice[2];
}

VOID CIODevice::SetDeviceProperties(CONST CByteArray &nDeviceData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_nIODeviceData.Copy(nDeviceData); IsOpen(); )
	{
		m_pIODevice->m_nIODeviceData.Copy(nDeviceData);
		break;
	}
}

INT CIODevice::GetDeviceProperties(CByteArray &nDeviceData) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	nDeviceData.Copy(m_nIODeviceData);
	return((INT)nDeviceData.GetSize());
}

VOID CIODevice::SetDeviceSecurity(CONST CStringArray &szUsers, CONST CUIntArray &nCodes, CONST CTimeKeyArray &tStartTimes, CONST CTimeKeyArray &tStopTimes)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_szSecurityUsers.Copy(szUsers), m_nSecurityCodes.Copy(nCodes), m_tSecurityStartTimes.Copy(tStartTimes), m_tSecurityStopTimes.Copy(tStopTimes); IsOpen(); )
	{
		m_pIODevice->m_szSecurityUsers.Copy(szUsers);
		m_pIODevice->m_nSecurityCodes.Copy(nCodes);
		m_pIODevice->m_tSecurityStartTimes.Copy(tStartTimes);
		m_pIODevice->m_tSecurityStopTimes.Copy(tStopTimes);
		break;
	}
}

INT CIODevice::GetDeviceSecurity(CStringArray &szUsers, CUIntArray &nCodes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	nCodes.Copy(m_nSecurityCodes);
	szUsers.Copy(m_szSecurityUsers);
	tStartTimes.Copy(m_tSecurityStartTimes);
	tStopTimes.Copy(m_tSecurityStopTimes);
	return((INT)nCodes.GetSize());
}

BOOL CIODevice::MonitorDeviceLogins(UINT nMask, IODEVICELOGINSPROCEDURE pLoginProcedure, LPVOID pData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_nOperationsType & IODEVICE_TYPE_SERVER)
	{
		for (m_nOperationsLoginsMask = nMask, m_pIODeviceLoginsProcedure = pLoginProcedure, m_pOperationsLoginsData = pData; IsOpen(); )
		{
			m_pIODevice->m_nOperationsLoginsMask = nMask;
			m_pIODevice->m_pOperationsLoginsData = pData;
			m_pIODevice->m_pIODeviceLoginsProcedure = pLoginProcedure;
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CIODevice::MonitorDeviceDataStream(UINT nMask, CONST CTimeSpan &tInterval, IODEVICEDATASTREAMPROCEDURE pDataStreamProcedure, LPVOID pData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((m_nOperationsType & (IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM)) == (IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM))
	{
		for (m_nOperationsDataStreamMask = (nMask != 0) ? (m_nOperationsDataStreamMask | nMask) : 0, m_pIODeviceDataStreamProcedure = pDataStreamProcedure, m_pOperationsDataStreamData = pData; nMask & IODEVICE_DATASTREAM_DROP; )
		{
			m_tOperationsDataDrop[1] = tInterval;
			break;
		}
		for (; nMask & IODEVICE_DATASTREAM_DELAYED; )
		{
			m_tOperationsDataDelay[1] = tInterval;
			break;
		}
		if (!nMask)
		{
			m_tOperationsDataDrop[1] = 0;
			m_tOperationsDataDelay[1] = 0;
			m_pOperationsDataStreamData = (LPVOID)NULL;
		}
		if (IsOpen())
		{
			m_pIODevice->m_tOperationsDataDrop[1] = m_tOperationsDataDrop[1];
			m_pIODevice->m_tOperationsDataDelay[1] = m_tOperationsDataDelay[1];
			m_pIODevice->m_pOperationsDataStreamData = m_pOperationsDataStreamData;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CIODevice::MonitorDeviceDataBuffers(HANDLE &hInBuffer, HANDLE &hOutBuffer)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	hOutBuffer = (IsOpen()) ? m_pIODevice->m_cIODeviceData[0] : m_cIODeviceData[0];
	hInBuffer = (IsOpen()) ? m_pIODevice->m_cIODeviceData[1] : m_cIODeviceData[1];
	return((hInBuffer != (HANDLE)NULL  &&  hOutBuffer != (HANDLE)NULL) ? TRUE : FALSE);
}

BOOL CIODevice::ShowDeviceStatus(LPCTSTR pszStatus, UINT nStatus)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pIODeviceStatusProcedure != (IODEVICESTATUSPROCEDURE)NULL)
	{
		(*m_pIODeviceStatusProcedure)(pszStatus, nStatus);
		return TRUE;
	}
	return FALSE;
}

BOOL CIODevice::ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pIODeviceMessageProcedure != (IODEVICEMESSAGEPROCEDURE)NULL)
	{
		(*m_pIODeviceMessageProcedure)(pszMessage, nMessageType);
		return TRUE;
	}
	return FALSE;
}

BOOL CIODevice::Synchronize()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (IsOpen())
	{
		m_pIODevice->m_szIODevice[0] = m_szIODevice[0];
		m_pIODevice->m_szIODevice[1] = m_szIODevice[1];
		m_pIODevice->m_szIODevice[2] = m_szIODevice[2];
		m_pIODevice->m_nIODeviceData.Copy(m_nIODeviceData);
		m_pIODevice->m_szIODeviceStatus = m_szIODeviceStatus;
		m_pIODevice->m_nIODeviceStatus = m_nIODeviceStatus;
		m_pIODevice->m_nOperationsType = m_nOperationsType;
		m_pIODevice->m_nOperationsLoginsMask = m_nOperationsLoginsMask;
		m_pIODevice->m_nOperationsDataStreamMask = m_nOperationsDataStreamMask;
		m_pIODevice->m_tOperationsDataDrop[0] = m_tOperationsDataDrop[0];
		m_pIODevice->m_tOperationsDataDrop[1] = m_tOperationsDataDrop[1];
		m_pIODevice->m_tOperationsDataDelay[0] = m_tOperationsDataDelay[0];
		m_pIODevice->m_tOperationsDataDelay[1] = m_tOperationsDataDelay[1];
		m_pIODevice->m_pOperationsLoginsData = m_pOperationsLoginsData;
		m_pIODevice->m_pOperationsDataStreamData = m_pOperationsDataStreamData;
		m_pIODevice->m_szSecurityUsers.Copy(m_szSecurityUsers);
		m_pIODevice->m_nSecurityCodes.Copy(m_nSecurityCodes);
		m_pIODevice->m_tSecurityStartTimes.Copy(m_tSecurityStartTimes);
		m_pIODevice->m_tSecurityStopTimes.Copy(m_tSecurityStopTimes);
		m_pIODevice->m_pIODeviceLoginsProcedure = m_pIODeviceLoginsProcedure;
		m_pIODevice->m_pIODeviceStatusProcedure = m_pIODeviceStatusProcedure;
		m_pIODevice->m_pIODeviceMessageProcedure = m_pIODeviceMessageProcedure;
		m_pIODevice->m_pIODeviceDataStreamProcedure = m_pIODeviceDataStreamProcedure;
		m_pIODevice->m_pIODeviceDataStatusProcedure = m_pIODeviceDataStatusProcedure;
		return TRUE;
	}
	return FALSE;
}

CIODevice *CIODevice::GetIODevice() CONST
{
	return m_pIODevice;
}

BOOL CIODevice::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CIODevice::Unlock()
{
	return m_pCriticalSection->Unlock();
}

BOOL CIODevice::Start()
{
	if (IsOpen())
	{
		if (m_pIODevice->Start())
		{
			Copy(m_pIODevice);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CIODevice::Suspend()
{
	return((IsOpen()) ? m_pIODevice->Suspend() : FALSE);
}

BOOL CIODevice::IsSuspended() CONST
{
	return((IsOpen()) ? m_pIODevice->IsSuspended() : FALSE);
}

BOOL CIODevice::Resume()
{
	return((IsOpen()) ? m_pIODevice->Resume() : FALSE);
}

BOOL CIODevice::Stop()
{
	return((IsOpen()) ? m_pIODevice->Stop() : FALSE);
}

BOOL CIODevice::Initialize(UINT nFlags)
{
	if (IsOpen())
	{
		if (m_pIODevice->Initialize(nFlags))
		{
			Copy(m_pIODevice);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CIODevice::Initialize(UINT nFlags, CONST CTimeSpan &tDataDrop, CONST CTimeSpan &tDataDelay, IODEVICESTATUSPROCEDURE pStatusProcedure, IODEVICEDATASTATUSPROCEDURE pDataStatusProcedure, IODEVICEMESSAGEPROCEDURE pMessageProcedure)
{
	if (IsOpen())
	{
		if (m_pIODevice->Initialize(nFlags, tDataDrop, tDataDelay, pStatusProcedure, pDataStatusProcedure, pMessageProcedure))
		{
			Copy(m_pIODevice);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CIODevice::Configure(CWnd *pParentWnd, UINT nAllowedTypes, BOOL bReadOnly)
{
	if (IsOpen())
	{
		if (m_pIODevice->Configure(pParentWnd, nAllowedTypes, bReadOnly))
		{
			Copy(m_pIODevice);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CIODevice::Update(CONST CIODevice *pDevice, BOOL &bRestart)
{
	if (IsOpen())
	{
		if (m_pIODevice->Update(pDevice, bRestart))
		{
			Copy(m_pIODevice);
			return TRUE;
		}
	}
	return FALSE;
}

INT CIODevice::Send(CONST CByteArray &nData)
{
	return((IsOpen()) ? m_pIODevice->Send(nData) : -1);
}
INT CIODevice::Send(CONST CTMUnit &cTMUnit)
{
	return((IsOpen()) ? m_pIODevice->Send(cTMUnit) : -1);
}
INT CIODevice::Send(CONST CTMTransferUnit &cTMTransferUnit)
{
	return((IsOpen()) ? m_pIODevice->Send(cTMTransferUnit) : -1);
}
INT CIODevice::Send(CONST CTCUnit &cTCUnit)
{
	return((IsOpen()) ? m_pIODevice->Send(cTCUnit) : -1);
}
INT CIODevice::Send(CONST CTCTransferUnit &cTCTransferUnit)
{
	return((IsOpen()) ? m_pIODevice->Send(cTCTransferUnit) : -1);
}

BOOL CIODevice::Receive(CByteArray &nData)
{
	return((IsOpen()) ? m_pIODevice->Receive(nData) : FALSE);
}
BOOL CIODevice::Receive(CTMUnit &cTMUnit)
{
	return((IsOpen()) ? m_pIODevice->Receive(cTMUnit) : FALSE);
}
BOOL CIODevice::Receive(CTMTransferUnit &cTMTransferUnit)
{
	return((IsOpen()) ? m_pIODevice->Receive(cTMTransferUnit) : FALSE);
}
BOOL CIODevice::Receive(CTCUnit &cTCUnit)
{
	return((IsOpen()) ? m_pIODevice->Receive(cTCUnit) : FALSE);
}
BOOL CIODevice::Receive(CTCTransferUnit &cTCTransferUnit)
{
	return((IsOpen()) ? m_pIODevice->Receive(cTCTransferUnit) : FALSE);
}

BOOL CIODevice::Clear(BOOL bAll)
{
	return((IsOpen()) ? m_pIODevice->Clear(bAll) : FALSE);
}

BOOL CIODevice::SetStatus(LPCTSTR pszStatus)
{
	m_szIODeviceStatus = pszStatus;
	return((IsOpen()) ? m_pIODevice->SetStatus(pszStatus) : TRUE);
}

CString CIODevice::GetStatus() CONST
{
	return((IsOpen()) ? m_pIODevice->GetStatus() : m_szIODeviceStatus);
}

BOOL CIODevice::SetStatusIndication(UINT nStatus)
{
	m_nIODeviceStatus = nStatus;
	return((IsOpen()) ? m_pIODevice->SetStatusIndication(nStatus) : TRUE);
}

UINT CIODevice::GetStatusIndication() CONST
{
	return((IsOpen()) ? m_pIODevice->m_nIODeviceStatus : m_nIODeviceStatus);
}

UINT CIODevice::GetCapabilities() CONST
{
	return((IsOpen()) ? m_pIODevice->GetCapabilities() : 0);
}

CString CIODevice::GetDetails() CONST
{
	return((IsOpen()) ? m_pIODevice->GetDetails() : EMPTYSTRING);
}

INT CIODevice::EnumConnections(CStringArray &szComputers) CONST
{
	return((IsOpen()) ? m_pIODevice->EnumConnections(szComputers) : -1);
}
INT CIODevice::EnumConnections(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST
{
	return((IsOpen()) ? m_pIODevice->EnumConnections(szComputers, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes) : -1);
}

BOOL CIODevice::AbortConnection(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime)
{
	return((IsOpen()) ? m_pIODevice->AbortConnection(pszComputer, tConnectTime) : FALSE);
}

BOOL CIODevice::IsLocal() CONST
{
	return((IsOpen()) ? m_pIODevice->IsLocal() : FALSE);
}

BOOL CIODevice::Copy(CONST CIODevice *pDevice)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szIODevice[0] = pDevice->m_szIODevice[0];
	m_szIODevice[1] = pDevice->m_szIODevice[1];
	m_szIODevice[2] = pDevice->m_szIODevice[2];
	m_nIODeviceData.Copy(pDevice->m_nIODeviceData);
	m_szIODeviceStatus = pDevice->m_szIODeviceStatus;
	m_nIODeviceStatus = pDevice->m_nIODeviceStatus;
	m_nOperationsType = pDevice->m_nOperationsType;
	m_nOperationsLoginsMask = pDevice->m_nOperationsLoginsMask;
	m_nOperationsDataStreamMask = pDevice->m_nOperationsDataStreamMask;
	m_tOperationsDataDrop[0] = pDevice->m_tOperationsDataDrop[0];
	m_tOperationsDataDrop[1] = pDevice->m_tOperationsDataDrop[1];
	m_tOperationsDataDelay[0] = pDevice->m_tOperationsDataDelay[0];
	m_tOperationsDataDelay[1] = pDevice->m_tOperationsDataDelay[1];
	m_pOperationsLoginsData = pDevice->m_pOperationsLoginsData;
	m_pOperationsDataStreamData = pDevice->m_pOperationsDataStreamData;
	m_szSecurityUsers.Copy(pDevice->m_szSecurityUsers);
	m_nSecurityCodes.Copy(pDevice->m_nSecurityCodes);
	m_tSecurityStartTimes.Copy(pDevice->m_tSecurityStartTimes);
	m_tSecurityStopTimes.Copy(pDevice->m_tSecurityStopTimes);
	m_pIODeviceLoginsProcedure = pDevice->m_pIODeviceLoginsProcedure;
	m_pIODeviceStatusProcedure = pDevice->m_pIODeviceStatusProcedure;
	m_pIODeviceMessageProcedure = pDevice->m_pIODeviceMessageProcedure;
	m_pIODeviceDataStreamProcedure = pDevice->m_pIODeviceDataStreamProcedure;
	m_pIODeviceDataStatusProcedure = pDevice->m_pIODeviceDataStatusProcedure;
	Synchronize();
	return TRUE;
}

BOOL CIODevice::Compare(CONST CIODevice *pDevice) CONST
{
	INT  nUser;
	INT  nUsers;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nUser = 0, nUsers = (pDevice->m_szIODevice[0] == m_szIODevice[0] && pDevice->m_szIODevice[1] == m_szIODevice[1] && pDevice->m_szIODevice[2] == m_szIODevice[2] && pDevice->m_nIODeviceData.GetSize() == m_nIODeviceData.GetSize() && !memcmp(pDevice->m_nIODeviceData.GetData(), m_nIODeviceData.GetData(), m_nIODeviceData.GetSize()) && pDevice->m_szIODeviceStatus == m_szIODeviceStatus && pDevice->m_nIODeviceStatus == m_nIODeviceStatus && pDevice->m_nOperationsType == m_nOperationsType && pDevice->m_nOperationsLoginsMask == m_nOperationsLoginsMask && pDevice->m_nOperationsDataStreamMask == m_nOperationsDataStreamMask && pDevice->m_tOperationsDataDrop[0] == m_tOperationsDataDrop[0] && pDevice->m_tOperationsDataDrop[1] == m_tOperationsDataDrop[1] && pDevice->m_tOperationsDataDelay[0] == m_tOperationsDataDelay[0] && pDevice->m_tOperationsDataDelay[1] == m_tOperationsDataDelay[1] && pDevice->m_pOperationsLoginsData == m_pOperationsLoginsData && pDevice->m_pOperationsDataStreamData == m_pOperationsDataStreamData && pDevice->m_szSecurityUsers.GetSize() == m_szSecurityUsers.GetSize() && pDevice->m_nSecurityCodes.GetSize() == m_nSecurityCodes.GetSize() && pDevice->m_tSecurityStartTimes.GetSize() == m_tSecurityStartTimes.GetSize() && pDevice->m_tSecurityStopTimes.GetSize() == m_tSecurityStopTimes.GetSize() && pDevice->m_pIODeviceLoginsProcedure == m_pIODeviceLoginsProcedure && pDevice->m_pIODeviceStatusProcedure == m_pIODeviceStatusProcedure && pDevice->m_pIODeviceMessageProcedure == m_pIODeviceMessageProcedure && pDevice->m_pIODeviceDataStreamProcedure == m_pIODeviceDataStreamProcedure && pDevice->m_pIODeviceDataStatusProcedure == m_pIODeviceDataStatusProcedure) ? (INT)m_szSecurityUsers.GetSize() : -1; nUser < nUsers; nUser++)
	{
		if (pDevice->m_szSecurityUsers.GetAt(nUser) != m_szSecurityUsers.GetAt(nUser) || pDevice->m_nSecurityCodes.GetAt(nUser) != m_nSecurityCodes.GetAt(nUser) || pDevice->m_tSecurityStartTimes.GetAt(nUser) != m_tSecurityStartTimes.GetAt(nUser) || pDevice->m_tSecurityStopTimes.GetAt(nUser) != m_tSecurityStopTimes.GetAt(nUser)) break;
		continue;
	}
	return((nUser == nUsers) ? TRUE : FALSE);
}

BOOL CIODevice::Map(CByteArray &nInfo) CONST
{
	INT  nUser;
	INT  nUsers;
	INT  cbData;
	DATA  sData;
	CByteArray  nUsersInfo[4];

	for (nUser = 0, nUsers = (INT)m_szSecurityUsers.GetSize(); nUser < nUsers; nUser++)
	{
		nUsersInfo[0].SetSize((cbData = (INT)nUsersInfo[0].GetSize()) + (m_szSecurityUsers.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nUsersInfo[0].GetData() + cbData, (LPCTSTR)m_szSecurityUsers.GetAt(nUser), nUsersInfo[0].GetSize() - cbData);
	}
	for (nUsersInfo[1].SetSize(m_nSecurityCodes.GetSize()*sizeof(UINT)), CopyMemory(nUsersInfo[1].GetData(), m_nSecurityCodes.GetData(), nUsersInfo[1].GetSize()); m_tSecurityStartTimes.Map(nUsersInfo[2]) >= 0 && m_tSecurityStopTimes.Map(nUsersInfo[3]) >= 0; )
	{
		for (nInfo.SetSize((sData.cbSize = (INT)(sizeof(DATA) + (sData.cbIODevice[0] = (m_szIODevice[0].GetLength() + 1)*sizeof(TCHAR)) + (sData.cbIODevice[1] = (m_szIODevice[1].GetLength() + 1)*sizeof(TCHAR)) + (sData.cbIODeviceData = (INT)m_nIODeviceData.GetSize()) + (sData.cbSecurityUsers = (INT)nUsersInfo[0].GetSize()) + (sData.cbSecurityCodes = (INT)nUsersInfo[1].GetSize()) + (sData.cbSecurityTimes[0] = (INT)nUsersInfo[2].GetSize()) + (sData.cbSecurityTimes[1] = (INT)nUsersInfo[3].GetSize())))); nInfo.GetSize() == sData.cbSize; )
		{
			CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
			CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szIODevice[0], sData.cbIODevice[0]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbIODevice[0]), (LPCTSTR)m_szIODevice[1], sData.cbIODevice[1]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbIODevice[1]), m_nIODeviceData.GetData(), sData.cbIODeviceData);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbIODeviceData), nUsersInfo[0].GetData(), sData.cbSecurityUsers);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSecurityUsers), nUsersInfo[1].GetData(), sData.cbSecurityCodes);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSecurityCodes), nUsersInfo[2].GetData(), sData.cbSecurityTimes[0]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSecurityTimes[0]), nUsersInfo[3].GetData(), sData.cbSecurityTimes[1]);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CIODevice::Unmap(CONST CByteArray &nInfo)
{
	INT  cbUser;
	INT  cbUsers;
	INT  cbData;
	DATA  sData;
	CByteArray  nUsersInfo[4];

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbIODevice[0] + sData.cbIODevice[1] + sData.cbIODeviceData + sData.cbSecurityUsers + sData.cbSecurityCodes + sData.cbSecurityTimes[0] + sData.cbSecurityTimes[1] && sData.cbIODevice[0] > 0 && sData.cbIODevice[1] > 0 && sData.cbIODeviceData >= 0 && sData.cbSecurityUsers >= 0 && sData.cbSecurityCodes >= 0 && sData.cbSecurityTimes[0] >= 0 && sData.cbSecurityTimes[1] >= 0; )
	{
		for (nUsersInfo[0].SetSize(sData.cbSecurityUsers), nUsersInfo[1].SetSize(sData.cbSecurityCodes), nUsersInfo[2].SetSize(sData.cbSecurityTimes[0]), nUsersInfo[3].SetSize(sData.cbSecurityTimes[1]), m_nIODeviceData.SetSize(sData.cbIODeviceData), CopyMemory(m_szIODevice[0].GetBufferSetLength(STRINGCHARS(sData.cbIODevice[0])), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbIODevice[0])), CopyMemory(m_szIODevice[1].GetBufferSetLength(STRINGCHARS(sData.cbIODevice[1])), nInfo.GetData() + (cbData = cbData + sData.cbIODevice[0]), STRINGBYTES(sData.cbIODevice[1])), CopyMemory(m_nIODeviceData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbIODevice[1]), sData.cbIODeviceData), CopyMemory(nUsersInfo[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbIODeviceData), sData.cbSecurityUsers), CopyMemory(nUsersInfo[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSecurityUsers), sData.cbSecurityCodes), CopyMemory(nUsersInfo[2].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSecurityCodes), sData.cbSecurityTimes[0]), CopyMemory(nUsersInfo[3].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSecurityTimes[0]), sData.cbSecurityTimes[1]), m_szSecurityUsers.RemoveAll(), m_nSecurityCodes.RemoveAll(), m_tSecurityStartTimes.RemoveAll(), m_tSecurityStopTimes.RemoveAll(), cbUsers = 0; cbUsers < sData.cbSecurityUsers; cbUsers += (cbUser = (INT)((m_szSecurityUsers.GetAt(m_szSecurityUsers.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR))))
		{
			m_szSecurityUsers.Add((LPCTSTR)(nUsersInfo[0].GetData() + cbUsers));
			continue;
		}
		for (m_nSecurityCodes.SetSize(nUsersInfo[1].GetSize() / sizeof(UINT)), CopyMemory(m_nSecurityCodes.GetData(), nUsersInfo[1].GetData(), nUsersInfo[1].GetSize()); m_tSecurityStartTimes.Unmap(nUsersInfo[2]) && m_tSecurityStopTimes.Unmap(nUsersInfo[3]); )
		{
			Synchronize();
			return TRUE;
		}
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CIODevices

CIODevices::CIODevices() : CPtrArray()
{
	return;
}

CIODevices::~CIODevices()
{
	RemoveAll();
}

INT CIODevices::Add(CIODevice *pIODevice)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pIODevice->GetDeviceBrand(), pIODevice->GetDeviceName(), TRUE)) >= 0) InsertAt(nIndex, pIODevice, 1);
	return nIndex;
}

INT CIODevices::Find(LPCTSTR pszDeviceBrand, LPCTSTR pszDeviceName) CONST
{
	return FindIndex(pszDeviceBrand, pszDeviceName);
}

CIODevice *CIODevices::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CIODevice *)CPtrArray::GetAt(nIndex) : (CIODevice *)NULL);
}

CIODevice *CIODevices::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CIODevice *)CPtrArray::GetAt(nIndex) : (CIODevice *)NULL);
}

VOID CIODevices::RemoveAll()
{
	INT  nDevice;
	INT  nDevices;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		delete GetAt(nDevice);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CIODevices::Copy(CONST CIODevices *pIODevices)
{
	INT  nDevice;
	INT  nDevices;
	CIODevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)pIODevices->GetSize(), RemoveAll(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = new CIODevice) != (CIODevice *)NULL)
		{
			pDevice->Copy(pIODevices->GetAt(nDevice));
			InsertAt(nDevice, pDevice, 1);
			continue;
		}
		break;
	}
	return((nDevice == nDevices) ? TRUE : FALSE);
}

BOOL CIODevices::Compare(CONST CIODevices *pIODevices) CONST
{
	INT  nDevice;
	INT  nDevices;
	CIODevice  *pDevice;

	for (nDevice = 0, nDevices = (pIODevices->GetSize() == GetSize()) ? (INT)GetSize() : -1; nDevice < nDevices; nDevice++)
	{
		if ((pDevice = pIODevices->GetAt(nDevice)) && Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName()) >= 0 && pDevice->Compare(GetAt(Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())))) continue;
		break;
	}
	return((nDevice == nDevices) ? TRUE : FALSE);
}

BOOL CIODevices::Map(CByteArray &nInfo) CONST
{
	INT  nDevice;
	INT  nDevices;
	CByteArray  nDeviceData;
	CIODevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)GetSize(), nInfo.RemoveAll(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice)) && pDevice->Map(nDeviceData) && nInfo.Append(nDeviceData) >= 0) continue;
		break;
	}
	return((nDevice == nDevices) ? TRUE : FALSE);
}

BOOL CIODevices::Unmap(CONST CByteArray &nInfo)
{
	INT  cbDevice;
	INT  cbDevices;
	CByteArray  nDeviceData;
	CIODevice  *pDevice;

	for (cbDevices = 0; cbDevices < nInfo.GetSize(); cbDevices += cbDevice)
	{
		for (CopyMemory(&cbDevice, nInfo.GetData() + cbDevices, sizeof(cbDevice)), nDeviceData.SetSize(max(min(cbDevice, nInfo.GetSize() - cbDevices), 0)); nDeviceData.GetSize() >= 0; )
		{
			CopyMemory(nDeviceData.GetData(), nInfo.GetData() + cbDevices, nDeviceData.GetSize());
			break;
		}
		if ((pDevice = new CIODevice))
		{
			if (pDevice->Unmap(nDeviceData) && Add(pDevice) >= 0) continue;
			delete pDevice;
		}
		break;
	}
	return((cbDevices == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CIODevices::FindIndex(LPCTSTR pszDeviceBrand, LPCTSTR pszDeviceName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CString  szDevice;
	CIODevice  *pDevice;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2, szDevice = ConstructFullName(pszDeviceBrand, pszDeviceName); nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pDevice = GetAt(nIndex[0]))) ? ((nIndex[1] = (ConstructFullName(pDevice) <= szDevice)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pDevice = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && ConstructFullName(pDevice) == szDevice) || (bInsert && (((pDevice = GetAt(max(nIndex[0] - 1, 0))) && ConstructFullName(pDevice) != szDevice && (pDevice = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && ConstructFullName(pDevice) != szDevice) || !GetSize()))) && lstrlen(pszDeviceBrand) > 0) ? nIndex[0] : -1);
}

CString CIODevices::ConstructFullName(LPCTSTR pszDeviceBrand, LPCTSTR pszDeviceName) CONST
{
	return(CString(pszDeviceBrand) + TAB + pszDeviceName);
}
CString CIODevices::ConstructFullName(CONST CIODevice *pDevice) CONST
{
	return ConstructFullName(pDevice->GetDeviceBrand(), pDevice->GetDeviceName());
}
