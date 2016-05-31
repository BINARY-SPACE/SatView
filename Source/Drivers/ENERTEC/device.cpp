// DEVICE.CPP : Device Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the device related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#define LIBRARYENVIRONMENT
#define USEENERTECDEVICESTRINGS

#include "ENERTEC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CPFLPCDSTimeCode

CPFLPCDSTimeCode::CPFLPCDSTimeCode() : CTimeTag()
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(TIMETAG tTimeTag) : CTimeTag(tTimeTag)
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(CONST CTimeKey &tTimeTag) : CTimeTag(tTimeTag)
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(CONST CTimeTag &tTimeTag) : CTimeTag(tTimeTag)
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(CONST FILETIME &tTimeTag) : CTimeTag(tTimeTag)
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(CONST SYSTEMTIME &tTimeTag) : CTimeTag(tTimeTag)
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond) : CTimeTag(nYear, nMonth, nDay, nHour, nMinute, nSecond, nMilliSecond, nMicroSecond)
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(INT nYear, INT nDayofYear, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond) : CTimeTag(nYear, nDayofYear, nHour, nMinute, nSecond, nMilliSecond, nMicroSecond)
{
	SetEpoch();
}
CPFLPCDSTimeCode::CPFLPCDSTimeCode(WORD wDay, DWORD dwMilliSeconds, WORD wMicroSeconds) : CTimeTag()
{
	SetEpoch();
	SetCDSTime(wDay, dwMilliSeconds, wMicroSeconds);
}

BOOL CPFLPCDSTimeCode::SetCDSTime(WORD wDay, DWORD dwMilliSeconds, WORD wMicroSeconds)
{
	TIMETAG  tTime;
	FILETIME  fTime;
	SYSTEMTIME  sTime;
	CTimeKey  tTimeKey[2] = { MIN_TIMEKEY,MAX_TIMEKEY };

	for (fTime.dwLowDateTime = (DWORD)(tTime = (TIMETAG)m_tEpoch.dwLowDateTime + ((TIMETAG)m_tEpoch.dwHighDateTime << 32) + (TIMETAG)(wDay - 1)*SECONDSPERDAY * 1000 * 1000 * 10 + (TIMETAG)dwMilliSeconds * 1000 * 10 + (TIMETAG)wMicroSeconds * 10), fTime.dwHighDateTime = (DWORD)(tTime >> 32); FileTimeToSystemTime(&fTime, &sTime); )
	{
		if (sTime.wYear < tTimeKey[0].GetYear())
		{
			SetTime(tTimeKey[0]);
			return FALSE;
		}
		if (sTime.wYear >= tTimeKey[1].GetYear())
		{
			SetTime(tTimeKey[1]);
			return FALSE;
		}
		SetTime(fTime);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPCDSTimeCode::GetCDSTime(WORD &wDay, DWORD &dwMilliSeconds, WORD &wMicroSeconds) CONST
{
	TIMETAG  tTime[3];
	FILETIME  fTime;

	GetTime(fTime);
	tTime[0] = (TIMETAG)fTime.dwLowDateTime + ((TIMETAG)fTime.dwHighDateTime << 32);
	tTime[1] = (TIMETAG)m_tEpoch.dwLowDateTime + ((TIMETAG)m_tEpoch.dwHighDateTime << 32);
	tTime[2] = (tTime[0] >= tTime[1]) ? (tTime[0] - tTime[1]) : 0;
	wDay = (WORD)(tTime[2] / ((TIMETAG)SECONDSPERDAY * 1000 * 1000 * 10)) + 1;
	dwMilliSeconds = (DWORD)((tTime[2] % ((TIMETAG)SECONDSPERDAY * 1000 * 1000 * 10)) / (1000 * 10));
	wMicroSeconds = (WORD)((tTime[2] % (1000 * 10)) / 10);
	return((tTime[0] >= tTime[1]) ? TRUE : FALSE);
}

BOOL CPFLPCDSTimeCode::SetEpoch()
{
	SYSTEMTIME  sTime;

	sTime.wYear = PFLP_CDSTIMECODE_EPOCH_YEAR;
	sTime.wMonth = PFLP_CDSTIMECODE_EPOCH_MONTH;
	sTime.wDay = PFLP_CDSTIMECODE_EPOCH_DAY;
	sTime.wHour = PFLP_CDSTIMECODE_EPOCH_HOUR;
	sTime.wMinute = PFLP_CDSTIMECODE_EPOCH_MINUTE;
	sTime.wSecond = PFLP_CDSTIMECODE_EPOCH_SECOND;
	sTime.wMilliseconds = PFLP_CDSTIMECODE_EPOCH_MILLISECOND;
	return SetEpoch(&sTime);
}
BOOL CPFLPCDSTimeCode::SetEpoch(CONST SYSTEMTIME *pTime)
{
	return SystemTimeToFileTime(pTime, &m_tEpoch);
}

BOOL CPFLPCDSTimeCode::GetEpoch(SYSTEMTIME *pTime) CONST
{
	return FileTimeToSystemTime(&m_tEpoch, pTime);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPMessageHeader

CPFLPMessageHeader::CPFLPMessageHeader() : CObject()
{
	m_sHeader.nMessageID = 0;
	m_sHeader.nMessageLength[0] = 0;
	m_sHeader.nMessageLength[1] = 0;
	m_sHeader.nMessageLength[2] = 0;
	m_sHeader.bTrailer = FALSE;
	m_sHeader.nTrailerOffset[0] = 0;
	m_sHeader.nTrailerOffset[1] = 0;
	m_sHeader.nTrailerOffset[2] = 0;
	m_sHeader.nVersion = PFLP_MESSAGEVERSION;
	m_sHeader.nSystemID = 0;
	m_sHeader.wSequence = 0;
	m_sHeader.nDataQuality = 0;
	m_sHeader.nSequenceQuality = 0;
	m_sHeader.nAcknowledgeRequest = 0;
	m_sHeader.nReserved = 0;
	m_sHeader.tTimeCode.wDay = 0;
	m_sHeader.tTimeCode.dwMilliSeconds = 0;
	m_sHeader.tTimeCode.wMicroSeconds = 0;
}
CPFLPMessageHeader::CPFLPMessageHeader(BYTE nID, UINT nLength, BOOL bRequest, BOOL bTrailer, UINT nTrailerOffset, BOOL bAcknowledgment) : CObject()
{
	SetMessageID(nID);
	SetMessageLength(nLength);
	SetTrailerFlag(bTrailer);
	SetTrailerOffset(nTrailerOffset);
	SetAcknowledgmentFlag(bAcknowledgment);
	m_sHeader.nVersion = PFLP_MESSAGEVERSION;
	m_sHeader.nSystemID = 0;
	m_sHeader.wSequence = 0;
	m_sHeader.nDataQuality = 0;
	m_sHeader.nSequenceQuality = 0;
	m_sHeader.tTimeCode.wDay = 0;
	m_sHeader.tTimeCode.dwMilliSeconds = 0;
	m_sHeader.tTimeCode.wMicroSeconds = 0;
	m_sHeader.nReserved = (!bRequest) ? PFLP_MESSAGEEPOCHCODE : 0;
}

BOOL CPFLPMessageHeader::SetMessageID(BYTE nID)
{
	if (nID == PFLP_SERVICEREQUEST || nID == PFLP_SERVICEREQUESTRESPONSE || nID == PFLP_SERVICEENDREQUEST || nID == PFLP_SERVICEENDREQUESTRESPONSE || nID == PFLP_DATADISTRIBUTIONREQUEST || nID == PFLP_DATADISTRIBUTIONREQUESTRESPONSE || nID == PFLP_DATADISTRIBUTIONSTOPREQUEST || nID == PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE || nID == PFLP_ACKNOWLEDGMENTMESSAGE || nID == PFLP_STATUSMESSAGE || nID == PFLP_SOURCEPACKET || nID == PFLP_TRANSFERFRAME)
	{
		m_sHeader.nMessageID = nID;
		return TRUE;
	}
	return FALSE;
}

BYTE CPFLPMessageHeader::GetMessageID() CONST
{
	return m_sHeader.nMessageID;
}

BOOL CPFLPMessageHeader::SetMessageLength(UINT nLength)
{
	if (nLength >= sizeof(m_sHeader) - PFLP_MESSAGEIDLENGTH)
	{
		CopyMemory(m_sHeader.nMessageLength, &nLength, sizeof(m_sHeader.nMessageLength));
		return TRUE;
	}
	return FALSE;
}

UINT CPFLPMessageHeader::GetMessageLength() CONST
{
	UINT  nLength = 0;

	CopyMemory(&nLength, m_sHeader.nMessageLength, sizeof(m_sHeader.nMessageLength));
	return nLength;
}

BOOL CPFLPMessageHeader::SetTrailerFlag(BOOL bPresent)
{
	if (!bPresent)
	{
		m_sHeader.bTrailer = PFLP_MESSAGETRAILER;
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPMessageHeader::GetTrailerFlag() CONST
{
	return((m_sHeader.bTrailer != PFLP_MESSAGETRAILER) ? TRUE : FALSE);
}

BOOL CPFLPMessageHeader::SetTrailerOffset(UINT nOffset)
{
	if (nOffset == 0)
	{
		CopyMemory(m_sHeader.nTrailerOffset, &nOffset, sizeof(m_sHeader.nTrailerOffset));
		return TRUE;
	}
	return FALSE;
}

UINT CPFLPMessageHeader::GetTrailerOffset() CONST
{
	UINT  nOffset = 0;

	CopyMemory(&nOffset, m_sHeader.nTrailerOffset, sizeof(m_sHeader.nTrailerOffset));
	return nOffset;
}

BOOL CPFLPMessageHeader::SetVersion(BYTE nVersion)
{
	if (nVersion == PFLP_MESSAGEVERSION)
	{
		m_sHeader.nVersion = nVersion;
		return TRUE;
	}
	return FALSE;
}

BYTE CPFLPMessageHeader::GetVersion() CONST
{
	return m_sHeader.nVersion;
}

BOOL CPFLPMessageHeader::SetSystemID(BYTE nSystemID)
{
	m_sHeader.nSystemID = nSystemID;
	return TRUE;
}

BYTE CPFLPMessageHeader::GetSystemID() CONST
{
	return m_sHeader.nSystemID;
}

BOOL CPFLPMessageHeader::SetSequenceCount(WORD wCount)
{
	m_sHeader.wSequence = wCount;
	return TRUE;
}

WORD CPFLPMessageHeader::GetSequenceCount() CONST
{
	return m_sHeader.wSequence;
}

BOOL CPFLPMessageHeader::SetDataQuality(BYTE nQuality)
{
	m_sHeader.nDataQuality = nQuality;
	return TRUE;
}

BYTE CPFLPMessageHeader::GetDataQuality() CONST
{
	return m_sHeader.nDataQuality;
}

BOOL CPFLPMessageHeader::SetSequenceQuality(BYTE nQuality)
{
	m_sHeader.nSequenceQuality = nQuality;
	return TRUE;
}

BYTE CPFLPMessageHeader::GetSequenceQuality() CONST
{
	return m_sHeader.nSequenceQuality;
}

BOOL CPFLPMessageHeader::SetAcknowledgmentFlag(BOOL bPresent)
{
	m_sHeader.nAcknowledgeRequest = (bPresent) ? PFLP_MESSAGEACKNOWLEDGMENT : PFLP_MESSAGENOACKNOWLEDGMENT;
	return TRUE;
}

BOOL CPFLPMessageHeader::GetAcknowledgmentFlag() CONST
{
	return((m_sHeader.nAcknowledgeRequest == PFLP_MESSAGEACKNOWLEDGMENT) ? TRUE : FALSE);
}

BOOL CPFLPMessageHeader::SetEpochCode(BYTE nCode)
{
	if (nCode == PFLP_MESSAGEEPOCHCODE)
	{
		m_sHeader.nReserved = nCode;
		return TRUE;
	}
	return FALSE;
}

BYTE CPFLPMessageHeader::GetEpochCode() CONST
{
	return m_sHeader.nReserved;
}

BOOL CPFLPMessageHeader::SetTimeCode(CONST CPFLPCDSTimeCode &tTimeCode)
{
	WORD  wDay;
	WORD  wMicroSeconds;
	DWORD  dwMilliSeconds;

	if (tTimeCode.GetCDSTime(wDay, dwMilliSeconds, wMicroSeconds))
	{
		m_sHeader.tTimeCode.dwMilliSeconds = dwMilliSeconds;
		m_sHeader.tTimeCode.wMicroSeconds = wMicroSeconds;
		m_sHeader.tTimeCode.wDay = wDay;
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPMessageHeader::GetTimeCode(CPFLPCDSTimeCode &tTimeCode) CONST
{
	return tTimeCode.SetCDSTime(m_sHeader.tTimeCode.wDay, m_sHeader.tTimeCode.dwMilliSeconds, m_sHeader.tTimeCode.wMicroSeconds);
}

BOOL CPFLPMessageHeader::Map(CByteArray &nInfo, BOOL bBigEndian) CONST
{
	for (nInfo.SetSize(max(nInfo.GetSize(), sizeof(m_sHeader))), CopyMemory(nInfo.GetData(), &m_sHeader, sizeof(m_sHeader)); TRUE; )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nMessageID), sizeof(m_sHeader.nMessageID), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nMessageLength[0]), sizeof(m_sHeader.nMessageLength), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.bTrailer), sizeof(m_sHeader.bTrailer), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nTrailerOffset[0]), sizeof(m_sHeader.nTrailerOffset), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nVersion), sizeof(m_sHeader.nVersion), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nSystemID), sizeof(m_sHeader.nSystemID), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.wSequence), sizeof(m_sHeader.wSequence), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nDataQuality), sizeof(m_sHeader.nDataQuality), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nSequenceQuality), sizeof(m_sHeader.nSequenceQuality), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nAcknowledgeRequest), sizeof(m_sHeader.nAcknowledgeRequest), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.tTimeCode.wDay), sizeof(m_sHeader.tTimeCode.wDay), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.tTimeCode.dwMilliSeconds), sizeof(m_sHeader.tTimeCode.dwMilliSeconds), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.tTimeCode.wMicroSeconds), sizeof(m_sHeader.tTimeCode.wMicroSeconds), bBigEndian);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPMessageHeader::Unmap(CONST CByteArray &nInfo, BOOL bBigEndian)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() >= sizeof(m_sHeader); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nMessageID), sizeof(m_sHeader.nMessageID), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nMessageLength[0]), sizeof(m_sHeader.nMessageLength), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.bTrailer), sizeof(m_sHeader.bTrailer), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nTrailerOffset[0]), sizeof(m_sHeader.nTrailerOffset), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nVersion), sizeof(m_sHeader.nVersion), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nSystemID), sizeof(m_sHeader.nSystemID), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.wSequence), sizeof(m_sHeader.wSequence), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nDataQuality), sizeof(m_sHeader.nDataQuality), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nSequenceQuality), sizeof(m_sHeader.nSequenceQuality), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.nAcknowledgeRequest), sizeof(m_sHeader.nAcknowledgeRequest), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.tTimeCode.wDay), sizeof(m_sHeader.tTimeCode.wDay), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.tTimeCode.dwMilliSeconds), sizeof(m_sHeader.tTimeCode.dwMilliSeconds), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sHeader, &m_sHeader.tTimeCode.wMicroSeconds), sizeof(m_sHeader.tTimeCode.wMicroSeconds), bBigEndian);
		CopyMemory(&m_sHeader, nData.GetData(), sizeof(m_sHeader));
		return TRUE;
	}
	return FALSE;
}

VOID CPFLPMessageHeader::SwapFieldBytes(LPBYTE pData, INT cbData, BOOL bSwap) CONST
{
	SwapFieldBytes(pData, pData, cbData, bSwap);
}
VOID CPFLPMessageHeader::SwapFieldBytes(LPBYTE pData, CONST BYTE *pValue, INT cbData, BOOL bSwap) CONST
{
	INT  nByte;
	INT  nBytes;
	BYTE  nData[4];

	CopyMemory(nData, pValue, min(cbData, sizeof(nData)));
	for (nByte = 0, nBytes = (cbData <= sizeof(nData)) ? cbData : 0; nByte < nBytes; nByte++)
	{
		pData[cbData - nByte - 1] = (!bSwap) ? nData[cbData - nByte - 1] : nData[nByte];
		continue;
	}
}

UINT CPFLPMessageHeader::CalcFieldOffset(LPCVOID pBase, LPCVOID pField) CONST
{
	return((UINT)(((CONST BYTE *) pField >= (CONST BYTE *) pBase) ? ((CONST BYTE *) pField - (CONST BYTE *) pBase) : 0));
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceRequest

CPFLPServiceRequest::CPFLPServiceRequest() : CPFLPMessageHeader(PFLP_SERVICEREQUEST, sizeof(PFLPSERVICEREQUEST) - PFLP_MESSAGEIDLENGTH, TRUE)
{
	m_sData.wServiceCode = PFLP_SERVICE_TM;
	m_sData.dwEndianity = PFLP_MESSAGEENDIANCODE;
	ZeroMemory(m_sData.szClientName, sizeof(m_sData.szClientName));
}

BOOL CPFLPServiceRequest::SetClientName(LPCTSTR pszName)
{
	if (lstrlen(pszName) < sizeof(m_sData.szClientName) - 1)
	{
#ifndef UNICODE
		strcpy_s(m_sData.szClientName, sizeof(m_sData.szClientName) / sizeof(CHAR), pszName);
		return TRUE;
#else
		WideCharToMultiByte(CP_ACP, 0, pszName, -1, m_sData.szClientName, sizeof(m_sData.szClientName), (LPCSTR)NULL, (LPBOOL)NULL);
		return TRUE;
#endif
	}
	return FALSE;
}

CString CPFLPServiceRequest::GetClientName() CONST
{
#ifdef UNICODE
	TCHAR  szClientName[sizeof(m_sData.szClientName)];
#endif

#ifndef UNICODE
	return m_sData.szClientName;
#else
	MultiByteToWideChar(CP_ACP, 0, m_sData.szClientName, -1, szClientName, sizeof(m_sData.szClientName));
	return szClientName;
#endif
}

BOOL CPFLPServiceRequest::SetServiceCode(WORD wCode)
{
	if (wCode == PFLP_SERVICE_TM || wCode == PFLP_SERVICE_TC)
	{
		m_sData.wServiceCode = wCode;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPServiceRequest::GetServiceCode() CONST
{
	return m_sData.wServiceCode;
}

BOOL CPFLPServiceRequest::SetEndianity(DWORD dwEndianity)
{
	if (dwEndianity == PFLP_MESSAGEENDIANCODE)
	{
		m_sData.dwEndianity = dwEndianity;
		return TRUE;
	}
	return FALSE;
}

DWORD CPFLPServiceRequest::GetEndianity() CONST
{
	return m_sData.dwEndianity;
}

BOOL CPFLPServiceRequest::Map(CByteArray &nInfo, BOOL bBigEndian) CONST
{
	for (nInfo.SetSize(sizeof(PFLPSERVICEREQUEST)); CPFLPMessageHeader::Map(nInfo, bBigEndian); )
	{
		CopyMemory(nInfo.GetData() + CalcFieldOffset(&m_sData, m_sData.szClientName), m_sData.szClientName, strlen(m_sData.szClientName));
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wServiceCode), (CONST BYTE *) &m_sData.wServiceCode, sizeof(m_sData.wServiceCode), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.dwEndianity), (CONST BYTE *) &m_sData.dwEndianity, sizeof(m_sData.dwEndianity), bBigEndian);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPServiceRequest::Unmap(CONST CByteArray &nInfo, BOOL bBigEndian)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPSERVICEREQUEST) && CPFLPMessageHeader::Unmap(nData, bBigEndian); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wServiceCode), sizeof(m_sData.wServiceCode), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.dwEndianity), sizeof(m_sData.dwEndianity), bBigEndian);
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPServiceRequest::Check() CONST
{
	return((GetMessageID() == PFLP_SERVICEREQUEST  &&  GetMessageLength() == sizeof(PFLPSERVICEREQUEST) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION && (GetServiceCode() == PFLP_SERVICE_TM || GetServiceCode() == PFLP_SERVICE_TC) && GetEndianity() == PFLP_MESSAGEENDIANCODE) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceRequestResponse

CPFLPServiceRequestResponse::CPFLPServiceRequestResponse() : CPFLPMessageHeader(PFLP_SERVICEREQUESTRESPONSE, sizeof(PFLPSERVICEREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	m_sData.wServiceCode = 0;
	m_sData.dwEndianity = PFLP_MESSAGEENDIANCODE;
	ZeroMemory(m_sData.szServerName, sizeof(m_sData.szServerName));
}

BOOL CPFLPServiceRequestResponse::SetServerName(LPCTSTR pszName)
{
	if (lstrlen(pszName) < sizeof(m_sData.szServerName) - 1)
	{
#ifndef UNICODE
		strcpy_s(m_sData.szServerName, sizeof(m_sData.szServerName) / sizeof(CHAR), pszName);
		return TRUE;
#else
		WideCharToMultiByte(CP_ACP, 0, pszName, -1, m_sData.szServerName, sizeof(m_sData.szServerName), (LPCSTR)NULL, (LPBOOL)NULL);
		return TRUE;
#endif
	}
	return FALSE;
}

CString CPFLPServiceRequestResponse::GetServerName() CONST
{
#ifdef UNICODE
	TCHAR  szServerName[sizeof(m_sData.szServerName)];
#endif

#ifndef UNICODE
	return m_sData.szServerName;
#else
	MultiByteToWideChar(CP_ACP, 0, m_sData.szServerName, -1, szServerName, sizeof(m_sData.szServerName));
	return szServerName;
#endif
}

BOOL CPFLPServiceRequestResponse::SetServiceCode(WORD wCode)
{
	if (wCode == PFLP_SERVICE_GRANTED || wCode == PFLP_SERVICE_NOTALLOWED || wCode == PFLP_SERVICE_ILLEGALENDIANITY || wCode == PFLP_SERVICE_PROTOCOLERROR)
	{
		m_sData.wServiceCode = wCode;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPServiceRequestResponse::GetServiceCode() CONST
{
	return m_sData.wServiceCode;
}

BOOL CPFLPServiceRequestResponse::SetEndianity(DWORD dwEndianity)
{
	if (dwEndianity == PFLP_MESSAGEENDIANCODE)
	{
		m_sData.dwEndianity = dwEndianity;
		return TRUE;
	}
	return FALSE;
}

DWORD CPFLPServiceRequestResponse::GetEndianity() CONST
{
	return m_sData.dwEndianity;
}

BOOL CPFLPServiceRequestResponse::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(sizeof(PFLPSERVICEREQUESTRESPONSE)); CPFLPMessageHeader::Map(nInfo); )
	{
		CopyMemory(nInfo.GetData() + CalcFieldOffset(&m_sData, m_sData.szServerName), m_sData.szServerName, strlen(m_sData.szServerName));
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wServiceCode), (CONST BYTE *) &m_sData.wServiceCode, sizeof(m_sData.wServiceCode));
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.dwEndianity), (CONST BYTE *) &m_sData.dwEndianity, sizeof(m_sData.dwEndianity));
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPServiceRequestResponse::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPSERVICEREQUESTRESPONSE) && CPFLPMessageHeader::Unmap(nData); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wServiceCode), sizeof(m_sData.wServiceCode));
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.dwEndianity), sizeof(m_sData.dwEndianity));
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPServiceRequestResponse::Check() CONST
{
	return((GetMessageID() == PFLP_SERVICEREQUESTRESPONSE  &&  GetMessageLength() == sizeof(PFLPSERVICEREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION  &&  !GetDataQuality() && !GetSequenceQuality() && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE && (GetServiceCode() == PFLP_SERVICE_GRANTED || GetServiceCode() == PFLP_SERVICE_NOTALLOWED || GetServiceCode() == PFLP_SERVICE_ILLEGALENDIANITY || GetServiceCode() == PFLP_SERVICE_PROTOCOLERROR) && GetEndianity() == PFLP_MESSAGEENDIANCODE) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceEndRequest

CPFLPServiceEndRequest::CPFLPServiceEndRequest() : CPFLPMessageHeader(PFLP_SERVICEENDREQUEST, sizeof(PFLPSERVICEENDREQUEST) - PFLP_MESSAGEIDLENGTH, TRUE)
{
	m_sData.wReason = 0;
}

BOOL CPFLPServiceEndRequest::SetReason(WORD wReason)
{
	m_sData.wReason = wReason;
	return TRUE;
}

WORD CPFLPServiceEndRequest::GetReason() CONST
{
	return m_sData.wReason;
}

BOOL CPFLPServiceEndRequest::Map(CByteArray &nInfo, BOOL bBigEndian) CONST
{
	for (nInfo.SetSize(sizeof(PFLPSERVICEENDREQUEST)); CPFLPMessageHeader::Map(nInfo, bBigEndian); )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wReason), (CONST BYTE *) &m_sData.wReason, sizeof(m_sData.wReason), bBigEndian);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPServiceEndRequest::Unmap(CONST CByteArray &nInfo, BOOL bBigEndian)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPSERVICEENDREQUEST) && CPFLPMessageHeader::Unmap(nData, bBigEndian); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wReason), sizeof(m_sData.wReason), bBigEndian);
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPServiceEndRequest::Check() CONST
{
	return((GetMessageID() == PFLP_SERVICEENDREQUEST  &&  GetMessageLength() == sizeof(PFLPSERVICEENDREQUEST) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceEndRequestResponse

CPFLPServiceEndRequestResponse::CPFLPServiceEndRequestResponse() : CPFLPMessageHeader(PFLP_SERVICEENDREQUESTRESPONSE, sizeof(PFLPSERVICEENDREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	m_sData.wResult = 0;
}

BOOL CPFLPServiceEndRequestResponse::SetResult(WORD wResult)
{
	if (wResult == PFLP_SERVICE_COMPLETED || wResult == PFLP_SERVICE_SYSTEMERROR || wResult == PFLP_SERVICE_REJECTED)
	{
		m_sData.wResult = wResult;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPServiceEndRequestResponse::GetResult() CONST
{
	return m_sData.wResult;
}

BOOL CPFLPServiceEndRequestResponse::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(sizeof(PFLPSERVICEENDREQUESTRESPONSE)); CPFLPMessageHeader::Map(nInfo); )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wResult), (CONST BYTE *) &m_sData.wResult, sizeof(m_sData.wResult));
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPServiceEndRequestResponse::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPSERVICEENDREQUESTRESPONSE) && CPFLPMessageHeader::Unmap(nData); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wResult), sizeof(m_sData.wResult));
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPServiceEndRequestResponse::Check() CONST
{
	return((GetMessageID() == PFLP_SERVICEENDREQUESTRESPONSE  &&  GetMessageLength() == sizeof(PFLPSERVICEENDREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION  &&  !GetDataQuality() && !GetSequenceQuality() && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE && (GetResult() == PFLP_SERVICE_COMPLETED || GetResult() == PFLP_SERVICE_SYSTEMERROR || GetResult() == PFLP_SERVICE_REJECTED)) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionRequest

CPFLPDataDistributionRequest::CPFLPDataDistributionRequest() : CPFLPMessageHeader(PFLP_DATADISTRIBUTIONREQUEST, sizeof(PFLPDATADISTRIBUTIONREQUEST) - PFLP_MESSAGEIDLENGTH, TRUE)
{
	m_sData.wRequest = PFLP_DATADISTRIBUTION_REQUESTCODE;
	m_sData.wLevel = PFLP_DATADISTRIBUTION_SOURCEPACKET;
	m_sData.nFilterManipulationCode = PFLP_DATADISTRIBUTION_FILTER_NONE;
	m_sData.nFilterGroupIdentifier = 0;
	m_sData.wFilterDataIdentifier = 0;
	m_sData.wFilterCount = 1;
}

BOOL CPFLPDataDistributionRequest::SetRequest(WORD wRequest)
{
	if (wRequest == PFLP_DATADISTRIBUTION_REQUESTCODE)
	{
		m_sData.wRequest = wRequest;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPDataDistributionRequest::GetRequest() CONST
{
	return m_sData.wRequest;
}

BOOL CPFLPDataDistributionRequest::SetLevel(WORD wLevel)
{
	if (wLevel == PFLP_DATADISTRIBUTION_SOURCEPACKET || wLevel == PFLP_DATADISTRIBUTION_TRANSFERFRAME)
	{
		m_sData.wLevel = wLevel;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPDataDistributionRequest::GetLevel() CONST
{
	return m_sData.wLevel;
}

BOOL CPFLPDataDistributionRequest::SetFilterCount(WORD wCount)
{
	if (wCount == PFLP_DATADISTRIBUTION_FILTERCOUNT)
	{
		m_sData.wFilterCount = wCount;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPDataDistributionRequest::GetFilterCount() CONST
{
	return m_sData.wFilterCount;
}

BOOL CPFLPDataDistributionRequest::SetFilterManipulationCode(BYTE wCode)
{
	if (wCode == PFLP_DATADISTRIBUTION_FILTER_NONE || wCode == PFLP_DATADISTRIBUTION_FILTER_APID || wCode == PFLP_DATADISTRIBUTION_FILTER_VCID || wCode == PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID)
	{
		m_sData.nFilterManipulationCode = wCode;
		return TRUE;
	}
	return FALSE;
}

BYTE CPFLPDataDistributionRequest::GetFilterManipulationCode() CONST
{
	return m_sData.nFilterManipulationCode;
}

BOOL CPFLPDataDistributionRequest::SetFilterGroupIdentifier(BYTE nVCID)
{
	m_sData.nFilterGroupIdentifier = nVCID;
	return TRUE;
}

BYTE CPFLPDataDistributionRequest::GetFilterGroupIdentifier() CONST
{
	return m_sData.nFilterGroupIdentifier;
}

BOOL CPFLPDataDistributionRequest::SetFilterDataIdentifier(WORD wAPID)
{
	m_sData.wFilterDataIdentifier = wAPID;
	return TRUE;
}

WORD CPFLPDataDistributionRequest::GetFilterDataIdentifier() CONST
{
	return m_sData.wFilterDataIdentifier;
}

BOOL CPFLPDataDistributionRequest::Map(CByteArray &nInfo, BOOL bBigEndian) CONST
{
	for (nInfo.SetSize(sizeof(PFLPDATADISTRIBUTIONREQUEST)); CPFLPMessageHeader::Map(nInfo, bBigEndian); )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wRequest), (CONST BYTE *) &m_sData.wRequest, sizeof(m_sData.wRequest), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wLevel), (CONST BYTE *) &m_sData.wLevel, sizeof(m_sData.wLevel), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wFilterCount), (CONST BYTE *) &m_sData.wFilterCount, sizeof(m_sData.wFilterCount), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.nFilterManipulationCode), (CONST BYTE *) &m_sData.nFilterManipulationCode, sizeof(m_sData.nFilterManipulationCode), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.nFilterGroupIdentifier), (CONST BYTE *) &m_sData.nFilterGroupIdentifier, sizeof(m_sData.nFilterGroupIdentifier), bBigEndian);
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wFilterDataIdentifier), (CONST BYTE *) &m_sData.wFilterDataIdentifier, sizeof(m_sData.wFilterDataIdentifier), bBigEndian);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPDataDistributionRequest::Unmap(CONST CByteArray &nInfo, BOOL bBigEndian)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPDATADISTRIBUTIONREQUEST) && CPFLPMessageHeader::Unmap(nData, bBigEndian); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wRequest), sizeof(m_sData.wRequest), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wLevel), sizeof(m_sData.wLevel), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wFilterCount), sizeof(m_sData.wFilterCount), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.nFilterManipulationCode), sizeof(m_sData.nFilterManipulationCode), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.nFilterGroupIdentifier), sizeof(m_sData.nFilterGroupIdentifier), bBigEndian);
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wFilterDataIdentifier), sizeof(m_sData.wFilterDataIdentifier), bBigEndian);
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPDataDistributionRequest::Check() CONST
{
	return((GetMessageID() == PFLP_DATADISTRIBUTIONREQUEST  &&  GetMessageLength() == sizeof(PFLPDATADISTRIBUTIONREQUEST) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION  &&  GetRequest() == PFLP_DATADISTRIBUTION_REQUESTCODE && (GetLevel() == PFLP_DATADISTRIBUTION_SOURCEPACKET || GetLevel() == PFLP_DATADISTRIBUTION_TRANSFERFRAME) && GetFilterCount() == PFLP_DATADISTRIBUTION_FILTERCOUNT && (GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_NONE || GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APID || GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_VCID || GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID)) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionRequestResponse

CPFLPDataDistributionRequestResponse::CPFLPDataDistributionRequestResponse() : CPFLPMessageHeader(PFLP_DATADISTRIBUTIONREQUESTRESPONSE, sizeof(PFLPDATADISTRIBUTIONREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	m_sData.wRequest = PFLP_DATADISTRIBUTION_REQUESTCODE;
	m_sData.wResult = 0;
	m_sData.wReason = 0;
}

BOOL CPFLPDataDistributionRequestResponse::SetRequest(WORD wRequest)
{
	if (wRequest == PFLP_DATADISTRIBUTION_REQUESTCODE)
	{
		m_sData.wRequest = wRequest;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPDataDistributionRequestResponse::GetRequest() CONST
{
	return m_sData.wRequest;
}

BOOL CPFLPDataDistributionRequestResponse::SetResult(WORD wResult)
{
	if (wResult == PFLP_DATADISTRIBUTION_REQUESTACCEPTED || wResult == PFLP_DATADISTRIBUTION_REQUESTREJECTED)
	{
		m_sData.wResult = wResult;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPDataDistributionRequestResponse::GetResult() CONST
{
	return m_sData.wResult;
}

BOOL CPFLPDataDistributionRequestResponse::SetReason(WORD wReason)
{
	if (wReason == PFLP_DATADISTRIBUTION_NOERROR || wReason == PFLP_DATADISTRIBUTION_NOTREADY || wReason == PFLP_DATADISTRIBUTION_NOTSUPPORTED || wReason == PFLP_DATADISTRIBUTION_ILLEGALLEVEL || wReason == PFLP_DATADISTRIBUTION_ILLEGALFILTER || wReason == PFLP_DATADISTRIBUTION_BADREQUEST)
	{
		m_sData.wReason = wReason;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPDataDistributionRequestResponse::GetReason() CONST
{
	return m_sData.wReason;
}

BOOL CPFLPDataDistributionRequestResponse::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(sizeof(PFLPDATADISTRIBUTIONREQUESTRESPONSE)); CPFLPMessageHeader::Map(nInfo); )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wRequest), (CONST BYTE *) &m_sData.wRequest, sizeof(m_sData.wRequest));
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wResult), (CONST BYTE *) &m_sData.wResult, sizeof(m_sData.wResult));
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wReason), (CONST BYTE *) &m_sData.wReason, sizeof(m_sData.wReason));
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPDataDistributionRequestResponse::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPDATADISTRIBUTIONREQUESTRESPONSE) && CPFLPMessageHeader::Unmap(nData); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wRequest), sizeof(m_sData.wRequest));
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wResult), sizeof(m_sData.wResult));
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wReason), sizeof(m_sData.wReason));
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPDataDistributionRequestResponse::Check() CONST
{
	return((GetMessageID() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE  &&  GetMessageLength() == sizeof(PFLPDATADISTRIBUTIONREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION  &&  !GetDataQuality() && !GetSequenceQuality() && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE  &&  GetRequest() == PFLP_DATADISTRIBUTION_REQUESTCODE && (GetResult() == PFLP_DATADISTRIBUTION_REQUESTACCEPTED || GetResult() == PFLP_DATADISTRIBUTION_REQUESTREJECTED) && (GetReason() == PFLP_DATADISTRIBUTION_NOERROR || GetReason() == PFLP_DATADISTRIBUTION_NOTREADY || GetReason() == PFLP_DATADISTRIBUTION_NOTSUPPORTED || GetReason() == PFLP_DATADISTRIBUTION_ILLEGALLEVEL || GetReason() == PFLP_DATADISTRIBUTION_ILLEGALFILTER || GetReason() == PFLP_DATADISTRIBUTION_BADREQUEST)) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionStopRequest

CPFLPDataDistributionStopRequest::CPFLPDataDistributionStopRequest() : CPFLPMessageHeader(PFLP_DATADISTRIBUTIONSTOPREQUEST, sizeof(PFLPDATADISTRIBUTIONSTOPREQUEST) - PFLP_MESSAGEIDLENGTH, TRUE)
{
	m_sData.wReason = 0;
}

BOOL CPFLPDataDistributionStopRequest::SetReason(WORD wReason)
{
	m_sData.wReason = wReason;
	return TRUE;
}

WORD CPFLPDataDistributionStopRequest::GetReason() CONST
{
	return m_sData.wReason;
}

BOOL CPFLPDataDistributionStopRequest::Map(CByteArray &nInfo, BOOL bBigEndian) CONST
{
	for (nInfo.SetSize(sizeof(PFLPDATADISTRIBUTIONSTOPREQUEST)); CPFLPMessageHeader::Map(nInfo, bBigEndian); )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wReason), (CONST BYTE *) &m_sData.wReason, sizeof(m_sData.wReason), bBigEndian);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPDataDistributionStopRequest::Unmap(CONST CByteArray &nInfo, BOOL bBigEndian)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPDATADISTRIBUTIONSTOPREQUEST) && CPFLPMessageHeader::Unmap(nData, bBigEndian); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wReason), sizeof(m_sData.wReason), bBigEndian);
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPDataDistributionStopRequest::Check() CONST
{
	return((GetMessageID() == PFLP_DATADISTRIBUTIONSTOPREQUEST  &&  GetMessageLength() == sizeof(PFLPDATADISTRIBUTIONSTOPREQUEST) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPDataDistributionStopRequestResponse

CPFLPDataDistributionStopRequestResponse::CPFLPDataDistributionStopRequestResponse() : CPFLPMessageHeader(PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE, sizeof(PFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	m_sData.wResult = 0;
}

BOOL CPFLPDataDistributionStopRequestResponse::SetResult(WORD wResult)
{
	if (wResult == PFLP_DATADISTRIBUTION_COMPLETED)
	{
		m_sData.wResult = wResult;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPDataDistributionStopRequestResponse::GetResult() CONST
{
	return m_sData.wResult;
}

BOOL CPFLPDataDistributionStopRequestResponse::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(sizeof(PFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE)); CPFLPMessageHeader::Map(nInfo); )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wResult), (CONST BYTE *) &m_sData.wResult, sizeof(m_sData.wResult));
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPDataDistributionStopRequestResponse::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE) && CPFLPMessageHeader::Unmap(nData); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wResult), sizeof(m_sData.wResult));
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPDataDistributionStopRequestResponse::Check() CONST
{
	return((GetMessageID() == PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE  &&  GetMessageLength() == sizeof(PFLPDATADISTRIBUTIONSTOPREQUESTRESPONSE) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION  &&  !GetDataQuality() && !GetSequenceQuality() && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE  &&  GetResult() == PFLP_DATADISTRIBUTION_COMPLETED) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPAcknowledgmentMessage

CPFLPAcknowledgmentMessage::CPFLPAcknowledgmentMessage() : CPFLPMessageHeader(PFLP_MESSAGEACKNOWLEDGMENT, sizeof(PFLPACKNOWLEDGMENTMESSAGE) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	SetDataQuality(0);
	SetSequenceQuality(0);
	SetCode(PFLP_MESSAGEACKNOWLEDGMENT_CODE);
}

BOOL CPFLPAcknowledgmentMessage::SetCode(WORD wCode)
{
	if (wCode == PFLP_MESSAGEACKNOWLEDGMENT_CODE)
	{
		m_sData.wCode = wCode;
		return TRUE;
	}
	return FALSE;
}

WORD CPFLPAcknowledgmentMessage::GetCode() CONST
{
	return m_sData.wCode;
}

BOOL CPFLPAcknowledgmentMessage::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(sizeof(PFLPACKNOWLEDGMENTMESSAGE)); CPFLPMessageHeader::Map(nInfo); )
	{
		SwapFieldBytes(nInfo.GetData() + CalcFieldOffset(&m_sData, &m_sData.wCode), (CONST BYTE *) &m_sData.wCode, sizeof(m_sData.wCode));
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPAcknowledgmentMessage::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() == sizeof(PFLPACKNOWLEDGMENTMESSAGE) && CPFLPMessageHeader::Unmap(nData); )
	{
		SwapFieldBytes(nData.GetData() + CalcFieldOffset(&m_sData, &m_sData.wCode), sizeof(m_sData.wCode));
		CopyMemory((LPBYTE)&m_sData + sizeof(m_sHeader), nData.GetData() + sizeof(m_sHeader), sizeof(m_sData) - sizeof(m_sHeader));
		return Check();
	}
	return FALSE;
}

BOOL CPFLPAcknowledgmentMessage::Check() CONST
{
	return((GetMessageID() == PFLP_ACKNOWLEDGMENTMESSAGE  &&  GetMessageLength() == sizeof(PFLPACKNOWLEDGMENTMESSAGE) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION  &&  !GetDataQuality() && !GetSequenceQuality() && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE  &&  GetCode() == PFLP_MESSAGEACKNOWLEDGMENT_CODE) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPStatusMessage

CPFLPStatusMessage::CPFLPStatusMessage() : CPFLPMessageHeader(PFLP_STATUSMESSAGE, sizeof(PFLPSTATUSMESSAGE) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	return;
}

BOOL CPFLPStatusMessage::Map(CByteArray &nInfo) CONST
{
	nInfo.SetSize(sizeof(PFLPSTATUSMESSAGE));
	return CPFLPMessageHeader::Map(nInfo);
}

BOOL CPFLPStatusMessage::Unmap(CONST CByteArray &nInfo)
{
	return((nInfo.GetSize() == sizeof(PFLPSTATUSMESSAGE)) ? (CPFLPMessageHeader::Unmap(nInfo) && Check()) : FALSE);
}

BOOL CPFLPStatusMessage::Check() CONST
{
	return((GetMessageID() == PFLP_STATUSMESSAGE  &&  GetMessageLength() == sizeof(PFLPSTATUSMESSAGE) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION && (GetSequenceQuality() == PFLP_SEQUENCE_NONE || GetSequenceQuality() == PFLP_SEQUENCE_CORRECT || GetSequenceQuality() == PFLP_SEQUENCE_ERROR) && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPSourcePacket

CPFLPSourcePacket::CPFLPSourcePacket() : CPFLPMessageHeader(PFLP_SOURCEPACKET, sizeof(PFLPMESSAGEHEADER) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	return;
}

BOOL CPFLPSourcePacket::SetData(CONST CByteArray &nData)
{
	SetMessageLength((UINT)(sizeof(PFLPMESSAGEHEADER) - PFLP_MESSAGEIDLENGTH + nData.GetSize()));
	m_nData.Copy(nData);
	return TRUE;
}

INT CPFLPSourcePacket::GetData(CByteArray &nData) CONST
{
	nData.Copy(m_nData);
	return((INT)nData.GetSize());
}

BOOL CPFLPSourcePacket::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(sizeof(PFLPMESSAGEHEADER) + m_nData.GetSize()); CPFLPMessageHeader::Map(nInfo); )
	{
		CopyMemory(nInfo.GetData() + sizeof(PFLPMESSAGEHEADER), m_nData.GetData(), m_nData.GetSize());
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPSourcePacket::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() >= sizeof(PFLPMESSAGEHEADER); )
	{
		for (m_nData.SetSize(nData.GetSize() - sizeof(PFLPMESSAGEHEADER)); CPFLPMessageHeader::Unmap(nData); )
		{
			CopyMemory(m_nData.GetData(), nData.GetData() + sizeof(PFLPMESSAGEHEADER), m_nData.GetSize());
			return Check();
		}
		break;
	}
	return FALSE;
}

BOOL CPFLPSourcePacket::Check() CONST
{
	return((GetMessageID() == PFLP_SOURCEPACKET  &&  GetMessageLength() >= sizeof(PFLPSOURCEPACKET) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION && (GetSequenceQuality() == PFLP_SEQUENCE_CORRECT || GetSequenceQuality() == PFLP_SEQUENCE_ERROR) && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE  &&  GetMessageLength() == (INT)(sizeof(PFLPSOURCEPACKET) + m_nData.GetSize() - PFLP_MESSAGEIDLENGTH)) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPTransferFrame

CPFLPTransferFrame::CPFLPTransferFrame() : CPFLPMessageHeader(PFLP_TRANSFERFRAME, sizeof(PFLPMESSAGEHEADER) - PFLP_MESSAGEIDLENGTH, FALSE)
{
	return;
}

BOOL CPFLPTransferFrame::SetData(CONST CByteArray &nData)
{
	SetMessageLength((UINT)(sizeof(PFLPMESSAGEHEADER) - PFLP_MESSAGEIDLENGTH + nData.GetSize()));
	m_nData.Copy(nData);
	return TRUE;
}

INT CPFLPTransferFrame::GetData(CByteArray &nData) CONST
{
	nData.Copy(m_nData);
	return((INT)nData.GetSize());
}

BOOL CPFLPTransferFrame::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(sizeof(PFLPMESSAGEHEADER) + m_nData.GetSize()); CPFLPMessageHeader::Map(nInfo); )
	{
		CopyMemory(nInfo.GetData() + sizeof(PFLPMESSAGEHEADER), m_nData.GetData(), m_nData.GetSize());
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPTransferFrame::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nData;

	for (nData.Copy(nInfo); nData.GetSize() >= sizeof(PFLPMESSAGEHEADER); )
	{
		for (m_nData.SetSize(nData.GetSize() - sizeof(PFLPMESSAGEHEADER)); CPFLPMessageHeader::Unmap(nData); )
		{
			CopyMemory(m_nData.GetData(), nData.GetData() + sizeof(PFLPMESSAGEHEADER), m_nData.GetSize());
			return Check();
		}
		break;
	}
	return FALSE;
}

BOOL CPFLPTransferFrame::Check() CONST
{
	return((GetMessageID() == PFLP_TRANSFERFRAME  &&  GetMessageLength() >= sizeof(PFLPTRANSFERFRAME) - PFLP_MESSAGEIDLENGTH  &&  !GetTrailerFlag() && !GetTrailerOffset() && GetVersion() == PFLP_MESSAGEVERSION && (GetSequenceQuality() == PFLP_SEQUENCE_CORRECT || GetSequenceQuality() == PFLP_SEQUENCE_ERROR) && !GetAcknowledgmentFlag() && GetEpochCode() == PFLP_MESSAGEEPOCHCODE  &&  GetMessageLength() == (INT)(sizeof(PFLPTRANSFERFRAME) + m_nData.GetSize() - PFLP_MESSAGEIDLENGTH)) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServerSocket

IMPLEMENT_DYNCREATE(CPFLPServerSocket, CSocket)

CPFLPServerSocket::CPFLPServerSocket() : CSocket()
{
	m_nPort = 0;
	m_nPhase = 0;
	m_wSequence = 0;
	m_cbInBytes = 0;
	m_cbOutBytes = 0;
	m_tConnect = 0;
	m_tLastUse = 0;
	m_nTimerID[0] = 0;
	m_nTimerID[1] = 0;
	m_pDevice = (CENERTECDevice *)NULL;
}

CPFLPServerSocket::~CPFLPServerSocket()
{
	Close();
}

BOOL CPFLPServerSocket::Open(CENERTECDevice *pDevice)
{
	m_nPhase = 0;
	m_wSequence = 0;
	return(((m_pDevice = pDevice)) ? TRUE : FALSE);
}

BOOL CPFLPServerSocket::IsOpen() CONST
{
	return((m_pDevice != (CENERTECDevice *)NULL  &&  m_hSocket != (SOCKET)INVALID_SOCKET) ? TRUE : FALSE);
}

void CPFLPServerSocket::Close()
{
	if (!IsOpen()) return;
	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		m_pDevice->RemoveClient(m_szPeer[0] + EOL + m_szPeer[1], m_tConnect);
		m_pDevice = (CENERTECDevice *)NULL;
	}
	CSocket::Close();
}

BOOL CPFLPServerSocket::Abort(LPCTSTR pszAddress, CONST CTimeTag &tConnectTime)
{
	CString  szAddress(pszAddress);

	if (IsOpen())
	{
		if (!szAddress.CompareNoCase(m_szPeer[0] + EOL + m_szPeer[1]) && (m_tConnect == tConnectTime || tConnectTime == 0))
		{
			Close();
			return TRUE;
		}
	}
	return FALSE;
}

INT CPFLPServerSocket::Send(CONST CByteArray &nData)
{
	INT  cbData;
	UINT  cbBuffer;

	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		for (m_pDevice->GetBufferSize(cbBuffer), SetSockOpt(SO_SNDBUF, &cbBuffer, sizeof(cbBuffer)); (cbData = CSocket::Send(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			m_cbOutBytes += (m_cbOutBytes + cbData > m_cbOutBytes) ? cbData : 0;
			m_tLastUse = CTimeTag().GetTime();
			return cbData;
		}
		return((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0);
	}
	return SOCKET_ERROR;
}
INT CPFLPServerSocket::Send(CONST CByteArray &nData, CONST CTimeSpan &tTimeout)
{
	INT  cbData;

	for (cbData = ((m_nTimerID[0] = SetTimer((HWND)NULL, PFLPSERVERSOCKET_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), PFLPSERVERSOCKET_TIMEOUT), NULL)) != 0) ? Send(nData) : SOCKET_ERROR; m_nTimerID[0] != 0; )
	{
		KillTimer((HWND)NULL, m_nTimerID[0]);
		m_nTimerID[0] = 0;
		break;
	}
	return cbData;
}

INT CPFLPServerSocket::Receive(CByteArray &nData)
{
	INT  cbData;
	UINT  cbBuffer;

	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		for (m_pDevice->GetBufferSize(cbBuffer), SetSockOpt(SO_RCVBUF, &cbBuffer, sizeof(cbBuffer)), nData.SetSize(cbBuffer); (cbData = CSocket::Receive(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			m_cbInBytes += (m_cbInBytes + cbData > m_cbInBytes) ? cbData : 0;
			m_tLastUse = CTimeTag().GetTime();
			nData.SetSize(cbData);
			return cbData;
		}
		return((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0);
	}
	return SOCKET_ERROR;
}
INT CPFLPServerSocket::Receive(CByteArray &nData, CONST CTimeSpan &tTimeout)
{
	INT  cbData;

	for (cbData = ((m_nTimerID[1] = SetTimer((HWND)NULL, PFLPSERVERSOCKET_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), PFLPSERVERSOCKET_TIMEOUT), NULL)) != 0) ? Receive(nData) : SOCKET_ERROR; m_nTimerID[1] != 0; )
	{
		KillTimer((HWND)NULL, m_nTimerID[1]);
		m_nTimerID[1] = 0;
		break;
	}
	return cbData;
}

BOOL CPFLPServerSocket::Update(INT nDataID, CONST CByteArray &nData)
{
	return((m_pDevice) ? m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, FALSE) : FALSE);
}
BOOL CPFLPServerSocket::Update(INT nDataID, CONST CTMUnit &cTMUnit)
{
	BYTE  nDeviceID;
	CByteArray  nData;
	CTMPacket  cTMPacket;
	CPFLPSourcePacket  cPFLPSourcePacket;

	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		if (m_pDevice->AuthorizeClient(IdentifyClient()))
		{
			for (cTMPacket.Copy(&cTMUnit); !HIBYTE(cTMUnit.GetQuality()); )
			{
				cTMPacket.SetQuality(MAKEWORD(LOBYTE(cTMUnit.GetQuality()), ENERTECDEVICE_PMDEMODULATOR_LOCKED | ENERTECDEVICE_PSKDEMODULATOR_LOCKED | ENERTECDEVICE_BITSYNCHRONIZER_LOCKED | ENERTECDEVICE_VITDECODER_LOCKED | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED | ENERTECDEVICE_REEDCRC_NOERRORS));
				break;
			}
			if (m_cConnection.GetLevel() == PFLP_LEVEL_SOURCEPACKETS)
			{
				if (m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_NONE || m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_VCID || ((m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_APID || m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_APIDANDVCID) && cTMPacket.GetAPID() == (INT)m_cConnection.GetFilterDataIdentifier()))
				{
					if (cPFLPSourcePacket.SetSystemID((m_pDevice->GetDeviceID(nDeviceID)) ? nDeviceID : 0) && cPFLPSourcePacket.SetSequenceCount(m_wSequence) && cPFLPSourcePacket.SetDataQuality(HIBYTE(cTMPacket.GetQuality())) && cPFLPSourcePacket.SetSequenceQuality((LOBYTE(cTMPacket.GetQuality()) & TMUNIT_SEQUENCEQUALITY_GOOD) ? PFLP_SEQUENCE_CORRECT : PFLP_SEQUENCE_ERROR) && cPFLPSourcePacket.SetTimeCode(cTMPacket.GetTimeTag().GetTime()) && cTMPacket.GetData(nData) >= 0 && cPFLPSourcePacket.SetData(nData) && cPFLPSourcePacket.Map(nData) && Send(nData) != SOCKET_ERROR)
					{
						m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED, TRUE);
						m_wSequence++;
						return TRUE;
					}
					m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, FALSE);
					return FALSE;
				}
				m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED, TRUE);
				return TRUE;
			}
			m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, FALSE);
			return FALSE;
		}
		m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, FALSE);
		Close();
	}
	return FALSE;
}
BOOL CPFLPServerSocket::Update(INT nDataID, CONST CTMTransferUnit &cTMTransferUnit)
{
	BYTE  nDeviceID;
	CByteArray  nData;
	CTMPacket  cTMPacket;
	CTMTransferFrame  cTMTransferFrame;
	CPFLPTransferFrame  cPFLPTransferFrame;

	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		if (m_pDevice->AuthorizeClient(IdentifyClient()))
		{
			for (cTMTransferFrame.Copy(&cTMTransferUnit); !HIBYTE(cTMTransferUnit.GetQuality()); )
			{
				cTMTransferFrame.SetQuality(MAKEWORD(LOBYTE(cTMTransferUnit.GetQuality()), ENERTECDEVICE_PMDEMODULATOR_LOCKED | ENERTECDEVICE_PSKDEMODULATOR_LOCKED | ENERTECDEVICE_BITSYNCHRONIZER_LOCKED | ENERTECDEVICE_VITDECODER_LOCKED | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED | ENERTECDEVICE_REEDCRC_NOERRORS));
				break;
			}
			if (m_cConnection.GetLevel() == PFLP_LEVEL_TRANSFERFRAMES)
			{
				if (m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_NONE || m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_VCID || ((m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_APID || m_cConnection.GetFilterManipulationCode() == PFLP_FILTER_APIDANDVCID) && cTMTransferFrame.GetFrameData(&cTMPacket) && cTMPacket.GetAPID() == (INT)m_cConnection.GetFilterDataIdentifier()))
				{
					if (cPFLPTransferFrame.SetSystemID((m_pDevice->GetDeviceID(nDeviceID)) ? nDeviceID : 0) && cPFLPTransferFrame.SetSequenceCount(m_wSequence) && cPFLPTransferFrame.SetDataQuality(HIBYTE(cTMTransferFrame.GetQuality())) && cPFLPTransferFrame.SetSequenceQuality((LOBYTE(cTMTransferFrame.GetQuality()) & TMUNIT_SEQUENCEQUALITY_GOOD) ? PFLP_SEQUENCE_CORRECT : PFLP_SEQUENCE_ERROR) && cPFLPTransferFrame.SetTimeCode(cTMTransferFrame.GetTimeTag().GetTime()) && cTMTransferFrame.GetData(nData) >= 0 && cPFLPTransferFrame.SetData(nData) && cPFLPTransferFrame.Map(nData) && Send(nData) != SOCKET_ERROR)
					{
						m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED, TRUE);
						m_wSequence++;
						return TRUE;
					}
					m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, FALSE);
					return FALSE;
				}
				m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED, TRUE);
				return TRUE;
			}
			m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, FALSE);
			return FALSE;
		}
		m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, FALSE);
		Close();
	}
	return FALSE;
}

BOOL CPFLPServerSocket::GetConnectionProperties(CString &szPeerName, CString &szPeerAddress, CTimeTag &tConnectTime, CTimeTag &tLastUseTime, DWORD &cbInBytes, DWORD &cbOutBytes) CONST
{
	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		szPeerName = m_szPeer[0];
		szPeerAddress = m_szPeer[1];
		tConnectTime = m_tConnect;
		tLastUseTime = m_tLastUse;
		cbInBytes = (DWORD)(m_cbInBytes / 1024);
		cbOutBytes = (DWORD)(m_cbOutBytes / 1024);
		return !szPeerName.IsEmpty();
	}
	return FALSE;
}

BOOL CPFLPServerSocket::Parse(CONST CByteArray &nData, CByteArray &nAcknowledgeData, CByteArray &nResponseData)
{
	BYTE  nDeviceID;
	BYTE  nMessageID;
	UINT  nDeviceMode;
	CPFLPCDSTimeCode  tTimeCode;
	CPFLPServiceRequest  cPFLPServiceRequest;
	CPFLPServiceEndRequest  cPFLPServiceEndRequest;
	CPFLPServiceRequestResponse  cPFLPServiceRequestResponse;
	CPFLPServiceEndRequestResponse  cPFLPServiceEndRequestResponse;
	CPFLPDataDistributionRequest  cPFLPDataDistributionRequest;
	CPFLPDataDistributionStopRequest  cPFLPDataDistributionStopRequest;
	CPFLPDataDistributionRequestResponse  cPFLPDataDistributionRequestResponse;
	CPFLPDataDistributionStopRequestResponse  cPFLPDataDistributionStopRequestResponse;
	CPFLPAcknowledgmentMessage  cPFLPAcknowledgmentMessage;

	for (m_pDevice->GetDeviceID(nDeviceID), m_pDevice->GetDeviceMode(nDeviceMode); (nMessageID = nData.GetAt(PFLP_MESSAGEID)) == PFLP_SERVICEREQUEST; )
	{
		if (cPFLPServiceRequestResponse.SetSystemID(nDeviceID) && cPFLPServiceRequestResponse.SetSequenceCount((m_wSequence = 0)) && AdjustClockEpoch(tTimeCode) && cPFLPServiceRequestResponse.SetTimeCode(tTimeCode) && cPFLPServiceRequestResponse.SetServerName(STRING(IDS_DEVICE_NAME)) && cPFLPServiceRequestResponse.SetServiceCode((((m_cConnection.SetEndian(PFLP_ENDIAN_BIG) && cPFLPServiceRequest.Unmap(nData, TRUE)) || (m_cConnection.SetEndian(PFLP_ENDIAN_LITTLE) && cPFLPServiceRequest.Unmap(nData, FALSE)))) ? ((cPFLPServiceRequest.GetServiceCode() == PFLP_SERVICE_TM) ? ((cPFLPServiceRequest.GetEndianity() == PFLP_MESSAGEENDIANCODE) ? PFLP_SERVICE_GRANTED : PFLP_SERVICE_ILLEGALENDIANITY) : PFLP_SERVICE_NOTALLOWED) : PFLP_SERVICE_PROTOCOLERROR) && (!cPFLPServiceRequest.GetAcknowledgmentFlag() || (cPFLPAcknowledgmentMessage.SetSystemID(nDeviceID) && cPFLPAcknowledgmentMessage.SetSequenceCount(0) && cPFLPAcknowledgmentMessage.SetTimeCode(tTimeCode) && cPFLPAcknowledgmentMessage.Map(nAcknowledgeData) && cPFLPServiceRequestResponse.SetSequenceCount(++m_wSequence))) && cPFLPServiceRequestResponse.Map(nResponseData))
		{
			for (m_szPeer[0] = cPFLPServiceRequest.GetClientName(); cPFLPServiceRequestResponse.GetServiceCode() == PFLP_SERVICE_GRANTED; )
			{
				m_cConnection.SetType((cPFLPServiceRequest.GetServiceCode() == PFLP_SERVICE_TM) ? PFLP_TYPE_TM : PFLP_TYPE_TC);
				SetPhase(PFLP_SERVICEREQUESTRESPONSE);
				m_wSequence++;
				break;
			}
			return TRUE;
		}
		break;
	}
	if (nMessageID == PFLP_SERVICEENDREQUEST)
	{
		if (cPFLPServiceEndRequestResponse.SetSystemID(nDeviceID) && cPFLPServiceEndRequestResponse.SetSequenceCount(m_wSequence) && AdjustClockEpoch(tTimeCode) && cPFLPServiceEndRequestResponse.SetTimeCode(tTimeCode) && cPFLPServiceEndRequestResponse.SetResult(((GetPhase() == PFLP_SERVICEREQUESTRESPONSE || GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE) && cPFLPServiceEndRequest.Unmap(nData, (m_cConnection.GetEndian() == PFLP_ENDIAN_BIG) ? TRUE : FALSE)) ? PFLP_SERVICE_COMPLETED : PFLP_SERVICE_REJECTED) && (!cPFLPServiceEndRequest.GetAcknowledgmentFlag() || (cPFLPAcknowledgmentMessage.SetSystemID(nDeviceID) && cPFLPAcknowledgmentMessage.SetSequenceCount(m_wSequence) && cPFLPAcknowledgmentMessage.SetTimeCode(tTimeCode) && cPFLPAcknowledgmentMessage.Map(nAcknowledgeData) && cPFLPServiceEndRequestResponse.SetSequenceCount(++m_wSequence))) && cPFLPServiceEndRequestResponse.Map(nResponseData))
		{
			if (cPFLPServiceEndRequestResponse.GetResult() == PFLP_SERVICE_COMPLETED) SetPhase(PFLP_SERVICE);
			return TRUE;
		}
	}
	if (nMessageID == PFLP_DATADISTRIBUTIONREQUEST)
	{
		if (cPFLPDataDistributionRequestResponse.SetSystemID(nDeviceID) && cPFLPDataDistributionRequestResponse.SetSequenceCount(m_wSequence) && AdjustClockEpoch(tTimeCode) && cPFLPDataDistributionRequestResponse.SetTimeCode(tTimeCode) && cPFLPDataDistributionRequestResponse.SetRequest(PFLP_DATADISTRIBUTION_REQUESTCODE) && cPFLPDataDistributionRequestResponse.SetResult((GetPhase() == PFLP_SERVICEREQUESTRESPONSE  &&  cPFLPDataDistributionRequest.Unmap(nData, (m_cConnection.GetEndian() == PFLP_ENDIAN_BIG) ? TRUE : FALSE) && cPFLPDataDistributionRequest.GetRequest() == PFLP_DATADISTRIBUTION_REQUESTCODE && (((nDeviceMode & IODEVICE_DATASERVICE_SOURCEPACKETS) && cPFLPDataDistributionRequest.GetLevel() == PFLP_DATADISTRIBUTION_SOURCEPACKET) || ((nDeviceMode & IODEVICE_DATASERVICE_TRANSFERFRAMES) && cPFLPDataDistributionRequest.GetLevel() == PFLP_DATADISTRIBUTION_TRANSFERFRAME)) && cPFLPDataDistributionRequest.GetFilterCount() == PFLP_DATADISTRIBUTION_FILTERCOUNT && (cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_NONE || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APID || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_VCID || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID)) ? PFLP_DATADISTRIBUTION_REQUESTACCEPTED : PFLP_DATADISTRIBUTION_REQUESTREJECTED) && cPFLPDataDistributionRequestResponse.SetReason((GetPhase() == PFLP_SERVICEREQUESTRESPONSE) ? ((cPFLPDataDistributionRequest.GetRequest() == PFLP_DATADISTRIBUTION_REQUESTCODE) ? ((((nDeviceMode & IODEVICE_DATASERVICE_SOURCEPACKETS) && cPFLPDataDistributionRequest.GetLevel() == PFLP_DATADISTRIBUTION_SOURCEPACKET) || ((nDeviceMode & IODEVICE_DATASERVICE_TRANSFERFRAMES) && cPFLPDataDistributionRequest.GetLevel() == PFLP_DATADISTRIBUTION_TRANSFERFRAME)) ? ((cPFLPDataDistributionRequest.GetFilterCount() == PFLP_DATADISTRIBUTION_FILTERCOUNT && (cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_NONE || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APID || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_VCID || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID)) ? ((cPFLPDataDistributionRequestResponse.GetResult() == PFLP_DATADISTRIBUTION_REQUESTACCEPTED) ? PFLP_DATADISTRIBUTION_NOERROR : PFLP_DATADISTRIBUTION_NOTREADY) : PFLP_DATADISTRIBUTION_ILLEGALFILTER) : PFLP_DATADISTRIBUTION_ILLEGALLEVEL) : PFLP_DATADISTRIBUTION_BADREQUEST) : ((m_cConnection.GetType() != PFLP_TYPE_TC) ? PFLP_DATADISTRIBUTION_NOTREADY : PFLP_DATADISTRIBUTION_NOTSUPPORTED)) && (!cPFLPDataDistributionRequest.GetAcknowledgmentFlag() || (cPFLPAcknowledgmentMessage.SetSystemID(nDeviceID) && cPFLPAcknowledgmentMessage.SetSequenceCount(m_wSequence) && cPFLPAcknowledgmentMessage.SetTimeCode(tTimeCode) && cPFLPAcknowledgmentMessage.Map(nAcknowledgeData) && cPFLPDataDistributionRequestResponse.SetSequenceCount(++m_wSequence))) && cPFLPDataDistributionRequestResponse.Map(nResponseData))
		{
			if (cPFLPDataDistributionRequestResponse.GetResult() == PFLP_DATADISTRIBUTION_REQUESTACCEPTED)
			{
				m_cConnection.SetLevel((cPFLPDataDistributionRequest.GetLevel() == PFLP_DATADISTRIBUTION_SOURCEPACKET) ? PFLP_LEVEL_SOURCEPACKETS : PFLP_LEVEL_TRANSFERFRAMES);
				m_cConnection.SetFilterManipulationCode((cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APID) ? PFLP_FILTER_APID : ((cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_VCID) ? PFLP_FILTER_VCID : ((cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID) ? PFLP_FILTER_APIDANDVCID : PFLP_FILTER_NONE)));
				m_cConnection.SetFilterGroupIdentifier((cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_VCID || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID) ? cPFLPDataDistributionRequest.GetFilterGroupIdentifier() : 0);
				m_cConnection.SetFilterDataIdentifier((cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APID || cPFLPDataDistributionRequest.GetFilterManipulationCode() == PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID) ? cPFLPDataDistributionRequest.GetFilterDataIdentifier() : 0);
				m_cConnection.SetFilterCount(PFLP_FILTER_COUNT);
				SetPhase(PFLP_DATADISTRIBUTIONREQUESTRESPONSE);
			}
			m_wSequence++;
			return TRUE;
		}
	}
	if (nMessageID == PFLP_DATADISTRIBUTIONSTOPREQUEST)
	{
		if (cPFLPDataDistributionStopRequestResponse.SetSystemID(nDeviceID) && cPFLPDataDistributionStopRequestResponse.SetSequenceCount(m_wSequence) && AdjustClockEpoch(tTimeCode) && cPFLPDataDistributionStopRequestResponse.SetTimeCode(tTimeCode) && cPFLPDataDistributionStopRequestResponse.SetResult((cPFLPDataDistributionStopRequest.Unmap(nData, (m_cConnection.GetEndian() == PFLP_ENDIAN_BIG) ? TRUE : FALSE)) ? PFLP_DATADISTRIBUTION_COMPLETED : PFLP_DATADISTRIBUTION_COMPLETED) && (!cPFLPDataDistributionStopRequest.GetAcknowledgmentFlag() || (cPFLPAcknowledgmentMessage.SetSystemID(nDeviceID) && cPFLPAcknowledgmentMessage.SetSequenceCount(m_wSequence) && cPFLPAcknowledgmentMessage.SetTimeCode(tTimeCode) && cPFLPAcknowledgmentMessage.Map(nAcknowledgeData) && cPFLPDataDistributionStopRequestResponse.SetSequenceCount(++m_wSequence))) && cPFLPDataDistributionStopRequestResponse.Map(nResponseData))
		{
			if (GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE) SetPhase(PFLP_SERVICEREQUESTRESPONSE);
			m_wSequence++;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPFLPServerSocket::AdjustClockEpoch(CPFLPCDSTimeCode &tTimeCode)
{
	SYSTEMTIME  tEpoch;

	return((m_pDevice->GetTimeEpoch(&tEpoch)) ? tTimeCode.SetEpoch(&tEpoch) : FALSE);
}

CString CPFLPServerSocket::IdentifyClient()
{
	UINT  nPort;
	CHAR  szNode[256];
	CHAR  szService[16];
	TCHAR  szAddress[64];
	DWORD  cbAddress;
	CString  szClient;
	CStringTools  cStringTools;
	struct addrinfo  *pIPAddressInfo[2];

	if (m_szPeer[1].IsEmpty())
	{
		for (m_tConnect = m_tLastUse = 0, m_cbInBytes = m_cbOutBytes = 0; GetPeerNameEx(szClient, nPort) >= 0 && !szClient.IsEmpty(); )
		{
			if ((pIPAddressInfo[0] = (struct addrinfo *) GlobalAlloc(GPTR, sizeof(struct addrinfo))))
			{
#ifndef UNICODE
				strcpy_s(szNode, sizeof(szNode) / sizeof(CHAR), szClient);
				strcpy_s(szService, sizeof(szService) / sizeof(CHAR), cStringTools.ConvertUIntToString(nPort));
#else
				WideCharToMultiByte(CP_ACP, 0, szClient, -1, szNode, sizeof(szNode) / sizeof(CHAR), (LPCSTR)NULL, (LPBOOL)NULL);
				WideCharToMultiByte(CP_ACP, 0, cStringTools.ConvertUIntToString(nPort), -1, szService, sizeof(szService) / sizeof(CHAR), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
				for (pIPAddressInfo[0]->ai_family = AF_INET, pIPAddressInfo[0]->ai_socktype = SOCK_STREAM, pIPAddressInfo[0]->ai_protocol = IPPROTO_TCP; !getaddrinfo(szNode, szService, pIPAddressInfo[0], &pIPAddressInfo[1]); )
				{
					if (!WSAAddressToString(pIPAddressInfo[1]->ai_addr, sizeof(sockaddr), (LPWSAPROTOCOL_INFO)NULL, szAddress, &(cbAddress = (DWORD)(sizeof(szAddress) / sizeof(TCHAR)))))
					{
						for (; lstrlen(szAddress) > (INT)strlen(szService) + 1; )
						{
							szAddress[lstrlen(szAddress) - strlen(szService) - 1] = EOS;
							break;
						}
						m_nPort = nPort;
						m_szPeer[1] = szAddress;
						m_tConnect = m_tLastUse = CTimeTag().GetTime();
					}
					freeaddrinfo(pIPAddressInfo[1]);
					break;
				}
				GlobalFree(pIPAddressInfo[0]);
			}
			break;
		}
	}
	return m_szPeer[1];
}

BOOL CPFLPServerSocket::SetPhase(UINT nPhase)
{
	if (nPhase == PFLP_SERVICE || nPhase == PFLP_SERVICEREQUEST || nPhase == PFLP_SERVICEREQUESTRESPONSE || nPhase == PFLP_DATADISTRIBUTIONREQUEST || nPhase == PFLP_DATADISTRIBUTIONREQUESTRESPONSE || nPhase == PFLP_DATADISTRIBUTIONSTOPREQUEST || nPhase == PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE || nPhase == PFLP_SERVICEENDREQUEST || nPhase == PFLP_SERVICEENDREQUESTRESPONSE)
	{
		m_nPhase = nPhase;
		return TRUE;
	}
	return FALSE;
}

UINT CPFLPServerSocket::GetPhase() CONST
{
	return m_nPhase;
}

/////////////////////////////////////////////////////////////////////////////
// CPFLPServerSocket member functions

BOOL CPFLPServerSocket::OnMessagePending()
{
	MSG  sMsg;

	while (PeekMessage(&sMsg, (HWND)NULL, WM_TIMER, WM_TIMER, PM_REMOVE))
	{
		if (m_nTimerID[0] != (UINT_PTR)sMsg.wParam  &&  m_nTimerID[1] != (UINT_PTR)sMsg.wParam)
		{
			if (!AfxPreTranslateMessage(&sMsg))
			{
				TranslateMessage(&sMsg);
				DispatchMessage(&sMsg);
			}
			continue;
		}
		if (m_nTimerID[0] == (UINT_PTR)sMsg.wParam)
		{
			KillTimer((HWND)NULL, m_nTimerID[0]);
			m_nTimerID[0] = 0;
		}
		else
		{
			KillTimer((HWND)NULL, m_nTimerID[1]);
			m_nTimerID[1] = 0;
		}
		CancelBlockingCall();
	}
	return CSocket::OnMessagePending();
}

void CPFLPServerSocket::OnReceive(int nErrorCode)
{
	INT  cbData;
	CByteArray  nData;
	CByteArray  nResponseData[2];

	if ((cbData = Receive(nData)) <= 0)
	{
		if (cbData < 0 && m_pDevice != (CENERTECDevice *)NULL) m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_SOCKET_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
		Close();
		return;
	}
	for (; nData.GetSize() > 0; )
	{
		if (m_pDevice != (CENERTECDevice *)NULL)
		{
			if (m_pDevice->AuthorizeClient(IdentifyClient()))
			{
				if (Parse(nData, nResponseData[0], nResponseData[1]))
				{
					if ((nResponseData[0].GetSize() > 0 && Send(nResponseData[0]) == SOCKET_ERROR) || (nResponseData[1].GetSize() > 0 && Send(nResponseData[1]) == SOCKET_ERROR))
					{
						m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_SOCKET_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
						Close();
						return;
					}
					m_pDevice->AddClient(m_szPeer[0] + EOL + m_szPeer[1], m_tConnect);
					break;
				}
				m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_GENERAL_FAILURE), IODEVICE_MESSAGETYPE_ERROR);
			}
		}
		Close();
		return;
	}
	CSocket::OnReceive(nErrorCode);
}

void CPFLPServerSocket::OnClose(int nErrorCode)
{
	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		m_pDevice->RemoveClient(m_szPeer[0] + EOL + m_szPeer[1], m_tConnect);
		m_pDevice = (CENERTECDevice *)NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServerSockets

CPFLPServerSockets::CPFLPServerSockets() : CPtrArray()
{
	return;
}

CPFLPServerSockets::~CPFLPServerSockets()
{
	RemoveAll();
}

BOOL CPFLPServerSockets::Add(CPFLPServerSocket *pSocket)
{
	INT  nConnection;
	INT  nConnections;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if (!GetAt(nConnection)->IsOpen())
		{
			delete GetAt(nConnection);
			RemoveAt(nConnection);
			nConnections--;
			nConnection--;
		}
	}
	return((CPtrArray::Add(pSocket) >= 0) ? TRUE : FALSE);
}

INT CPFLPServerSockets::Enum(CStringArray &szComputers) CONST
{
	INT  nConnection;
	INT  nConnections;
	DWORD  cbInData;
	DWORD  cbOutData;
	CString  szPeer[2];
	CTimeTag  tConnectTime;
	CTimeTag  tLastUseTime;
	CPFLPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(), szComputers.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->GetConnectionProperties(szPeer[0], szPeer[1], tConnectTime, tLastUseTime, cbInData, cbOutData))
		{
			szComputers.Add(szPeer[0] + EOL + szPeer[1]);
			continue;
		}
	}
	return((INT)szComputers.GetSize());
}
INT CPFLPServerSockets::Enum(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST
{
	INT  nConnection;
	INT  nConnections;
	DWORD  cbInData;
	DWORD  cbOutData;
	CString  szPeer[2];
	CTimeTag  tConnectTime;
	CTimeTag  tLastUseTime;
	CPFLPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(), szComputers.RemoveAll(), tConnectTimes.RemoveAll(), tLastUseTimes.RemoveAll(), cbInBytes.RemoveAll(), cbOutBytes.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->GetConnectionProperties(szPeer[0], szPeer[1], tConnectTime, tLastUseTime, cbInData, cbOutData))
		{
			szComputers.Add(szPeer[0] + EOL + szPeer[1]);
			tConnectTimes.Add(tConnectTime);
			tLastUseTimes.Add(tLastUseTime);
			cbInBytes.Add(cbInData);
			cbOutBytes.Add(cbOutData);
		}
	}
	return((INT)szComputers.GetSize());
}

VOID CPFLPServerSockets::Update(INT nDataID, CONST CByteArray &nData)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->IsOpen())
		{
			pSocket->Update(nDataID, nData);
			continue;
		}
	}
}
VOID CPFLPServerSockets::Update(INT nDataID, CONST CTMUnit &cTMUnit)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->IsOpen())
		{
			pSocket->Update(nDataID, cTMUnit);
			continue;
		}
	}
}
VOID CPFLPServerSockets::Update(INT nDataID, CONST CTMTransferUnit &cTMTransferUnit)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->IsOpen())
		{
			pSocket->Update(nDataID, cTMTransferUnit);
			continue;
		}
	}
}

CPFLPServerSocket *CPFLPServerSockets::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPServerSocket *)CPtrArray::GetAt(nIndex) : (CPFLPServerSocket *)NULL);
}

CPFLPServerSocket *CPFLPServerSockets::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPServerSocket *)CPtrArray::GetAt(nIndex) : (CPFLPServerSocket *)NULL);
}

BOOL CPFLPServerSockets::Abort(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->Abort(pszComputer, tConnectTime))
		{
			RemoveAt(nConnection);
			delete pSocket;
			break;
		}
	}
	return((nConnection < nConnections) ? TRUE : FALSE);
}

VOID CPFLPServerSockets::RemoveAll()
{
	INT  nConnection;
	INT  nConnections;
	CPFLPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)))
		{
			delete pSocket;
			continue;
		}
	}
	CPtrArray::RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPClientSocket

IMPLEMENT_DYNCREATE(CPFLPClientSocket, CSocket)

CPFLPClientSocket::CPFLPClientSocket() : CSocket()
{
	m_nPort = 0;
	m_nPhase = 0;
	m_wSequence = 0;
	m_cbInBytes = 0;
	m_cbOutBytes = 0;
	m_tConnect = 0;
	m_tLastUse = 0;
	m_nTimerID[0] = 0;
	m_nTimerID[1] = 0;
	m_tClockAdjustment[0] = 0;
	m_tClockAdjustment[1] = 0;
	m_tClockAdjustment[2] = 0;
	m_tClockAdjustment[3] = 0;
	m_tClockInterval = 0;
	m_bSession[0] = FALSE;
	m_bSession[1] = FALSE;
	m_pDevice = (CENERTECDevice *)NULL;
}

BOOL CPFLPClientSocket::Open(CENERTECDevice *pDevice)
{
	UINT  nLevel;
	UINT  cbBuffer;
	CTimeTag  tTime;
	CTimeSpan  tTimeout;

	if (Create())
	{
		for ((m_pDevice = pDevice)->GetIPAddress(m_szPeer[1], m_nPort), pDevice->GetBufferSize(cbBuffer), pDevice->GetTimeout(tTimeout), m_tClockInterval = (pDevice->GetClockAdjustmentInterval(m_tClockInterval)) ? m_tClockInterval : 0, m_bSession[0] = FALSE; Connect(m_szPeer[1], m_nPort, tTimeout); )
		{
			for (SetSockOpt(SO_SNDBUF, &cbBuffer, sizeof(cbBuffer)), SetSockOpt(SO_RCVBUF, &cbBuffer, sizeof(cbBuffer)), m_cbInBytes = m_cbOutBytes = 0, m_tConnect = m_tLastUse = tTime, m_nData.RemoveAll(), AdjustClockTime(); StartDataService(tTimeout) && (((pDevice->GetCapabilities() & IODEVICE_DATASERVICE_SOURCEPACKETS) && StartDataDistribution(tTimeout, (nLevel = PFLP_DATADISTRIBUTION_SOURCEPACKET))) || ((pDevice->GetCapabilities() & IODEVICE_DATASERVICE_TRANSFERFRAMES) && StartDataDistribution(tTimeout, (nLevel = PFLP_DATADISTRIBUTION_TRANSFERFRAME)))); )
			{
				m_pDevice->Initialize((nLevel == PFLP_DATADISTRIBUTION_SOURCEPACKET) ? ((pDevice->GetCapabilities() & ~IODEVICE_DATASERVICE_TRANSFERFRAMES) | IODEVICE_DATASERVICE_SOURCEPACKETS) : ((pDevice->GetCapabilities() & ~IODEVICE_DATASERVICE_SOURCEPACKETS) | IODEVICE_DATASERVICE_TRANSFERFRAMES));
				return TRUE;
			}
			break;
		}
		Close();
	}
	return FALSE;
}

BOOL CPFLPClientSocket::IsOpen() CONST
{
	return((m_pDevice != (CENERTECDevice *)NULL  &&  m_hSocket != (SOCKET)INVALID_SOCKET) ? TRUE : FALSE);
}

void CPFLPClientSocket::Close()
{
	CTimeSpan  tTimeout;

	if (!IsOpen()) return;
	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		for (m_bSession[0] = TRUE, StopDataDistribution((tTimeout = (m_pDevice->GetTimeout(tTimeout)) ? tTimeout : 0)), StopDataService(tTimeout); m_nTimerID[0] != 0; )
		{
			KillTimer((HWND)NULL, m_nTimerID[0]);
			m_nTimerID[0] = 0;
			break;
		}
		if (m_nTimerID[1] != 0)
		{
			KillTimer((HWND)NULL, m_nTimerID[1]);
			m_nTimerID[1] = 0;
		}
	}
	CSocket::Close();
}

BOOL CPFLPClientSocket::Connect(LPCTSTR pszAddress, UINT nPort, CONST CTimeSpan &tTimeout)
{
	BOOL  bSuccess;

	for (bSuccess = ((m_nTimerID[0] = SetTimer((HWND)NULL, PFLPCLIENTSOCKET_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), PFLPCLIENTSOCKET_TIMEOUT), NULL)) != 0) ? CSocket::Connect(pszAddress, nPort) : FALSE; m_nTimerID[0] != 0; )
	{
		KillTimer((HWND)NULL, m_nTimerID[0]);
		m_nTimerID[0] = 0;
		break;
	}
	return bSuccess;
}

BOOL CPFLPClientSocket::Abort(LPCTSTR pszAddress, CONST CTimeTag &tConnectTime)
{
	if (IsOpen())
	{
		if (!m_szPeer[1].CompareNoCase(pszAddress) && (m_tConnect == tConnectTime || tConnectTime == 0))
		{
			Close();
			return TRUE;
		}
	}
	return FALSE;
}

INT CPFLPClientSocket::Send(CONST CByteArray &nData)
{
	INT  cbData;
	UINT  cbBuffer;

	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		for (m_pDevice->GetBufferSize(cbBuffer), SetSockOpt(SO_SNDBUF, &cbBuffer, sizeof(cbBuffer)); (cbData = CSocket::Send(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			m_cbOutBytes += (m_cbOutBytes + cbData > m_cbOutBytes) ? cbData : 0;
			m_tLastUse = CTimeTag().GetTime();
			return cbData;
		}
		return((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0);
	}
	return SOCKET_ERROR;
}
INT CPFLPClientSocket::Send(CONST CByteArray &nData, CONST CTimeSpan &tTimeout)
{
	INT  cbData;

	for (cbData = ((m_nTimerID[0] = SetTimer((HWND)NULL, PFLPCLIENTSOCKET_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), PFLPCLIENTSOCKET_TIMEOUT), NULL)) != 0) ? Send(nData) : SOCKET_ERROR; m_nTimerID[0] != 0; )
	{
		KillTimer((HWND)NULL, m_nTimerID[0]);
		m_nTimerID[0] = 0;
		break;
	}
	return cbData;
}

INT CPFLPClientSocket::Receive(CByteArray &nData)
{
	INT  cbData;
	UINT  cbBuffer;

	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		for (m_pDevice->GetBufferSize(cbBuffer), SetSockOpt(SO_RCVBUF, &cbBuffer, sizeof(cbBuffer)), nData.SetSize(cbBuffer); (cbData = CSocket::Receive(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			m_cbInBytes += (m_cbInBytes + cbData > m_cbInBytes) ? cbData : 0;
			m_tLastUse = CTimeTag().GetTime();
			nData.SetSize(cbData);
			return cbData;
		}
		return((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0);
	}
	return SOCKET_ERROR;
}
INT CPFLPClientSocket::Receive(CByteArray &nData, CONST CTimeSpan &tTimeout, BOOL bSession)
{
	INT  cbData;

	while (bSession)
	{
		for (m_nTimerID[1] = SetTimer((HWND)NULL, PFLPCLIENTSOCKET_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), PFLPCLIENTSOCKET_TIMEOUT), NULL), m_bSession[1] = FALSE; (cbData = Receive(nData)) > 0; )
		{
			for (Parse(nData); m_bSession[1]; )
			{
				if (m_nTimerID[1] != 0)
				{
					KillTimer((HWND)NULL, m_nTimerID[1]);
					m_nTimerID[1] = 0;
				}
				nData.Copy(m_nData);
				m_nData.RemoveAll();
				return((INT)nData.GetSize());
			}
		}
		return cbData;
	}
	for (cbData = ((m_nTimerID[1] = SetTimer((HWND)NULL, PFLPCLIENTSOCKET_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), PFLPCLIENTSOCKET_TIMEOUT), NULL)) != 0) ? Receive(nData) : SOCKET_ERROR; m_nTimerID[1] != 0; )
	{
		KillTimer((HWND)NULL, m_nTimerID[1]);
		m_nTimerID[1] = 0;
		break;
	}
	return cbData;
}

BOOL CPFLPClientSocket::Update(INT nDataID, CONST CTCUnit &cTCUnit)
{
	if (m_pDevice != (CENERTECDevice *)NULL)
	{ /* Send telecommand data to ground station equipment */
		m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, TRUE);
		/* Simulate ground station equipment uplink status via a timer */
		Sleep(1000);
		m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_PROCESSED, TRUE);
		return TRUE;
	}
	return FALSE;
}
BOOL CPFLPClientSocket::Update(INT nDataID, CONST CTCTransferUnit &cTCTransferUnit)
{
	if (m_pDevice != (CENERTECDevice *)NULL)
	{ /* Send telecommand data to ground station equipment */
		m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_SENT, TRUE);
		/* Simulate ground station equipment uplink status via a timer */
		Sleep(1000);
		m_pDevice->UpdateDataStatus(nDataID, IODEVICE_DATASTATUS_PROCESSED, TRUE);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPClientSocket::GetConnectionProperties(CString &szPeerName, CString &szPeerAddress, CTimeTag &tConnectTime, CTimeTag &tLastUseTime, DWORD &cbInBytes, DWORD &cbOutBytes) CONST
{
	if (m_pDevice != (CENERTECDevice *)NULL)
	{
		szPeerName = m_szPeer[0];
		szPeerAddress = m_szPeer[1];
		tConnectTime = m_tConnect;
		tLastUseTime = m_tLastUse;
		cbInBytes = (DWORD)(m_cbInBytes / 1024);
		cbOutBytes = (DWORD)(m_cbOutBytes / 1024);
		return !szPeerAddress.IsEmpty();
	}
	return FALSE;
}

BOOL CPFLPClientSocket::StartDataService(CONST CTimeSpan &tTimeout)
{
	CByteArray  nData;
	CComputerToken  cComputerToken;
	CPFLPServiceRequest  cPFLPServiceRequest;
	CPFLPServiceRequestResponse  cPFLPServiceRequestResponse;

	return((GetPhase() == PFLP_SERVICE || GetPhase() == PFLP_SERVICEREQUEST) ? (cPFLPServiceRequest.SetServiceCode(PFLP_SERVICE_TM) && cPFLPServiceRequest.SetClientName(cComputerToken.GetComputerName()) && cPFLPServiceRequest.Map(nData) && Send(nData, tTimeout) != SOCKET_ERROR  &&  SetPhase(PFLP_SERVICEREQUEST) && Receive(nData, tTimeout, TRUE) != SOCKET_ERROR  &&  cPFLPServiceRequestResponse.Unmap(nData) && cPFLPServiceRequestResponse.GetServiceCode() == PFLP_SERVICE_GRANTED  &&  SetPhase(PFLP_SERVICEREQUESTRESPONSE)) : FALSE);
}

BOOL CPFLPClientSocket::StopDataService(CONST CTimeSpan &tTimeout)
{
	CByteArray  nData;
	CPFLPServiceEndRequest  cPFLPServiceEndRequest;
	CPFLPServiceEndRequestResponse  cPFLPServiceEndRequestResponse;

	if (GetPhase() == PFLP_SERVICEREQUESTRESPONSE || GetPhase() == PFLP_DATADISTRIBUTIONREQUEST || GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE)
	{
		for (SetPhase(PFLP_SERVICEREQUESTRESPONSE); cPFLPServiceEndRequest.Map(nData) && Send(nData, tTimeout) != SOCKET_ERROR && Receive(nData, tTimeout, TRUE) != SOCKET_ERROR && cPFLPServiceEndRequestResponse.Unmap(nData) && cPFLPServiceEndRequestResponse.GetResult() == PFLP_SERVICE_COMPLETED; )
		{
			SetPhase(PFLP_SERVICE);
			return TRUE;
		}
		return FALSE;
	}
	return((GetPhase() == PFLP_SERVICE || GetPhase() == PFLP_SERVICEREQUEST) ? TRUE : FALSE);
}

BOOL CPFLPClientSocket::StartDataDistribution(CONST CTimeSpan &tTimeout, WORD nLevel)
{
	WORD  wFilter[2];
	CByteArray  nData;
	CPFLPDataDistributionRequest  cPFLPDataDistributionRequest;
	CPFLPDataDistributionRequestResponse  cPFLPDataDistributionRequestResponse;

	if (GetPhase() == PFLP_SERVICEREQUESTRESPONSE || GetPhase() == PFLP_DATADISTRIBUTIONREQUEST)
	{
		if (cPFLPDataDistributionRequest.SetRequest(PFLP_DATADISTRIBUTION_REQUESTCODE) && cPFLPDataDistributionRequest.SetLevel(nLevel) && cPFLPDataDistributionRequest.SetFilterCount(PFLP_DATADISTRIBUTION_FILTERCOUNT) && cPFLPDataDistributionRequest.SetFilterManipulationCode(((wFilter[0] = (m_pDevice->GetVCIDFilter(wFilter[0])) ? wFilter[0] : (WORD)-1) != (WORD)-1) ? (((wFilter[1] = (m_pDevice->GetAPIDFilter(wFilter[1])) ? wFilter[1] : (WORD)-1) != (WORD)-1) ? PFLP_DATADISTRIBUTION_FILTER_APIDANDVCID : PFLP_DATADISTRIBUTION_FILTER_VCID) : (((wFilter[1] = (m_pDevice->GetAPIDFilter(wFilter[1])) ? wFilter[1] : (WORD)-1) != (WORD)-1) ? PFLP_DATADISTRIBUTION_FILTER_APID : PFLP_DATADISTRIBUTION_FILTER_NONE)) && cPFLPDataDistributionRequest.SetFilterGroupIdentifier((wFilter[0] != (WORD)-1) ? wFilter[0] : 0) && cPFLPDataDistributionRequest.SetFilterDataIdentifier((wFilter[1] != (UINT)-1) ? wFilter[1] : 0) && cPFLPDataDistributionRequest.Map(nData) && Send(nData, tTimeout) != SOCKET_ERROR  &&  SetPhase(PFLP_DATADISTRIBUTIONREQUEST) && Receive(nData, tTimeout, TRUE) != SOCKET_ERROR  &&  cPFLPDataDistributionRequestResponse.Unmap(nData) && cPFLPDataDistributionRequestResponse.GetResult() == PFLP_DATADISTRIBUTION_REQUESTACCEPTED  &&  SetPhase(PFLP_DATADISTRIBUTIONREQUESTRESPONSE))
		{
			m_wSequence = cPFLPDataDistributionRequestResponse.GetSequenceCount();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CPFLPClientSocket::StopDataDistribution(CONST CTimeSpan &tTimeout)
{
	CByteArray  nData;
	CPFLPDataDistributionStopRequest  cPFLPDataDistributionStopRequest;
	CPFLPDataDistributionStopRequestResponse  cPFLPDataDistributionStopRequestResponse;

	return((GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE) ? (cPFLPDataDistributionStopRequest.Map(nData) && Send(nData, tTimeout) != SOCKET_ERROR  &&  Receive(nData, tTimeout, TRUE) != SOCKET_ERROR  &&  cPFLPDataDistributionStopRequestResponse.Unmap(nData) && cPFLPDataDistributionStopRequestResponse.GetResult() == PFLP_DATADISTRIBUTION_COMPLETED  &&  SetPhase(PFLP_SERVICEREQUESTRESPONSE)) : (GetPhase() == PFLP_SERVICE || GetPhase() == PFLP_SERVICEREQUEST || GetPhase() == PFLP_SERVICEREQUESTRESPONSE || GetPhase() == PFLP_DATADISTRIBUTIONREQUEST));
}

BOOL CPFLPClientSocket::Parse(CByteArray &nData)
{
	BOOL  bBadTimestamp;
	BYTE  nDataMessageID;
	LONG  tTimestampError;
	LONG  tTimestampDelta;
	UINT  nDataDeviceStatus;
	UINT  nDataMessageLength[2];
	CString  szDataDeviceStatus;
	CByteArray  nSourcePacketData;
	CByteArray  nTransferFrameData;
	CPFLPCDSTimeCode  tPFLPCDSTimeCode;
	CPFLPSourcePacket  cPFLPSourcePacket;
	CPFLPTransferFrame  cPFLPTransferFrame;
	CPFLPMessageHeader  cPFLPMessageHeader;
	CPFLPStatusMessage  cPFLPStatusMessage;
	CPFLPAcknowledgmentMessage  cPFLPAcknowledgmentMessage;
	CTMTransferFrame  cTMTransferFrame;
	CTMUnit  cTMUnit;

	if (nData.GetSize() > 0)
	{
		if (!m_nData.GetSize())
		{
			switch (nData.GetAt(PFLP_MESSAGEID))
			{
			case PFLP_SERVICEREQUESTRESPONSE:
			case PFLP_SERVICEENDREQUESTRESPONSE:
			case PFLP_DATADISTRIBUTIONREQUESTRESPONSE:
			case PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE:
			case PFLP_ACKNOWLEDGMENTMESSAGE:
			case PFLP_STATUSMESSAGE:
			case PFLP_SOURCEPACKET:
			case PFLP_TRANSFERFRAME:
			{ if (cPFLPMessageHeader.Unmap(nData))
			{
				if ((nDataMessageLength[0] = PFLP_MESSAGEIDLENGTH + cPFLPMessageHeader.GetMessageLength()) <= (UINT)(PFLP_MESSAGEHEADERLENGTH + PFLP_MESSAGEPACKETLENGTH))
				{
					if (nDataMessageLength[0] > (UINT)nData.GetSize())
					{
						m_nData.Copy(nData);
						nData.RemoveAll();
						return TRUE;
					}
					if (nDataMessageLength[0] > 0)
					{
						m_nData.SetSize(nDataMessageLength[0]);
						CopyMemory(m_nData.GetData(), nData.GetData(), nDataMessageLength[0]);
						nData.RemoveAt(0, nDataMessageLength[0]);
						break;
					}
				}
				for (nData.RemoveAll(); GetPhase() != PFLP_SERVICE; )
				{
					m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
					break;
				}
				return FALSE;
			}
			if (nData.GetSize() < PFLP_MESSAGEHEADERLENGTH)
			{
				m_nData.Copy(nData);
				nData.RemoveAll();
				return TRUE;
			}
			}
			default:
			{ for (nData.RemoveAll(); GetPhase() != PFLP_SERVICE; )
			{
				m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
				break;
			}
			return FALSE;
			}
			}
		}
		else
		{
			if (cPFLPMessageHeader.Unmap(m_nData))
			{
				if ((nDataMessageLength[0] = PFLP_MESSAGEIDLENGTH + cPFLPMessageHeader.GetMessageLength()) <= (UINT)(PFLP_MESSAGEHEADERLENGTH + PFLP_MESSAGEPACKETLENGTH))
				{
					if ((nDataMessageLength[1] = (UINT)m_nData.GetSize()) + nData.GetSize() < nDataMessageLength[0])
					{
						m_nData.Append(nData);
						nData.RemoveAll();
						return TRUE;
					}
					if (nDataMessageLength[0] > nDataMessageLength[1])
					{
						m_nData.SetSize((INT_PTR)nDataMessageLength[0]);
						CopyMemory(m_nData.GetData() + nDataMessageLength[1], nData.GetData(), nDataMessageLength[0] - nDataMessageLength[1]);
						nData.RemoveAt(0, nDataMessageLength[0] - nDataMessageLength[1]);
					}
					else
					{
						for (m_nData.RemoveAll(); GetPhase() != PFLP_SERVICE; )
						{
							m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
							break;
						}
						return FALSE;
					}
				}
				else
				{
					for (m_nData.RemoveAll(); GetPhase() != PFLP_SERVICE; )
					{
						m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
						break;
					}
					return FALSE;
				}
			}
			else
			{
				if (m_nData.GetSize() < PFLP_MESSAGEHEADERLENGTH)
				{
					m_nData.Append(nData);
					nData.Copy(m_nData);
					m_nData.RemoveAll();
					return TRUE;
				}
				for (m_nData.RemoveAll(); GetPhase() != PFLP_SERVICE; )
				{
					m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
					break;
				}
				return FALSE;
			}
		}
		if (m_nData.GetSize() > 0)
		{
			if ((nDataMessageID = m_nData.GetAt(PFLP_MESSAGEID)) == PFLP_SERVICEREQUESTRESPONSE || nDataMessageID == PFLP_SERVICEENDREQUESTRESPONSE || nDataMessageID == PFLP_DATADISTRIBUTIONREQUESTRESPONSE || nDataMessageID == PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE)
			{
				if ((GetPhase() == PFLP_SERVICEREQUEST  &&  nDataMessageID != PFLP_SERVICEREQUESTRESPONSE) || (GetPhase() == PFLP_DATADISTRIBUTIONREQUEST  &&  nDataMessageID != PFLP_DATADISTRIBUTIONREQUESTRESPONSE) || (GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE  &&  nDataMessageID != PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE) || (GetPhase() == PFLP_SERVICEREQUESTRESPONSE  &&  nDataMessageID != PFLP_SERVICEENDREQUESTRESPONSE))
				{
					m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
					m_nData.RemoveAll();
					m_bSession[1] = TRUE;
					return FALSE;
				}
				m_bSession[1] = TRUE;
				return TRUE;
			}
			if (nDataMessageID == PFLP_ACKNOWLEDGMENTMESSAGE)
			{
				if (cPFLPAcknowledgmentMessage.Unmap(m_nData) && cPFLPAcknowledgmentMessage.GetCode() == PFLP_MESSAGEACKNOWLEDGMENT_CODE)
				{
					m_wSequence = cPFLPAcknowledgmentMessage.GetSequenceCount();
					m_nData.RemoveAll();
					return TRUE;
				}
				for (m_nData.RemoveAll(); GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE; )
				{
					m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
					return FALSE;
				}
				return TRUE;
			}
			if (nDataMessageID == PFLP_STATUSMESSAGE)
			{
				if (cPFLPStatusMessage.Unmap(m_nData) && AdjustClockEpoch(tPFLPCDSTimeCode) && cPFLPStatusMessage.GetTimeCode(tPFLPCDSTimeCode))
				{
					for (m_wSequence = cPFLPStatusMessage.GetSequenceCount(); !m_pDevice->UpdateStatus(cPFLPStatusMessage.GetDataQuality(), cPFLPStatusMessage.GetSequenceQuality()); )
					{
						if (!m_bSession[0] && m_pDevice->TranslateStatus(szDataDeviceStatus, nDataDeviceStatus) >= 0) m_pDevice->ShowDeviceStatus(szDataDeviceStatus, nDataDeviceStatus);
						break;
					}
					m_nData.RemoveAll();
					return TRUE;
				}
				for (m_nData.RemoveAll(); GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE; )
				{
					m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
					return FALSE;
				}
				return TRUE;
			}
			if (nDataMessageID == PFLP_SOURCEPACKET)
			{
				if (cPFLPSourcePacket.Unmap(m_nData) && AdjustClockEpoch(tPFLPCDSTimeCode) && cPFLPSourcePacket.GetTimeCode(tPFLPCDSTimeCode) && cPFLPSourcePacket.GetData(nSourcePacketData) > 0)
				{
					for (m_wSequence++; !m_pDevice->UpdateStatus(cPFLPSourcePacket.GetDataQuality(), (cPFLPSourcePacket.GetSequenceCount() == m_wSequence) ? cPFLPSourcePacket.GetSequenceQuality() : PFLP_SEQUENCE_ERROR); )
					{
						if (!m_bSession[0] && m_pDevice->TranslateStatus(szDataDeviceStatus, nDataDeviceStatus) >= 0) m_pDevice->ShowDeviceStatus(szDataDeviceStatus, nDataDeviceStatus);
						break;
					}
					for (bBadTimestamp = (!AdjustClockTime(CTimeTag(tPFLPCDSTimeCode.GetTime())) || AdjustClockDeviation(tPFLPCDSTimeCode)); bBadTimestamp; )
					{
						m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_TIME_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
						break;
					}
					for (m_pDevice->GetTimeCorrelation(tTimestampError, tTimestampDelta), cTMUnit.SetQuality(MAKEWORD(((cPFLPSourcePacket.GetDataQuality() == (ENERTECDEVICE_PMDEMODULATOR_LOCKED | ENERTECDEVICE_PSKDEMODULATOR_LOCKED | ENERTECDEVICE_BITSYNCHRONIZER_LOCKED | ENERTECDEVICE_VITDECODER_LOCKED | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED | ENERTECDEVICE_REEDCRC_NOERRORS) && !bBadTimestamp) ? TMUNIT_DATAQUALITY_GOOD : TMUNIT_DATAQUALITY_BAD) | ((cPFLPSourcePacket.GetSequenceQuality() == PFLP_SEQUENCE_CORRECT) ? TMUNIT_SEQUENCEQUALITY_GOOD : TMUNIT_SEQUENCEQUALITY_BAD), cPFLPSourcePacket.GetDataQuality())), cTMUnit.SetTimeTag((!bBadTimestamp && m_tClockAdjustment[2] > 0) ? (tPFLPCDSTimeCode.GetTime() - tTimestampError + tTimestampDelta) : (tPFLPCDSTimeCode = CTimeTag().GetTime())), cTMUnit.SetData(nSourcePacketData), m_wSequence = cPFLPSourcePacket.GetSequenceCount(); !bBadTimestamp; )
					{
						AdjustClockTime(tPFLPCDSTimeCode);
						break;
					}
					if (!m_bSession[0] && m_pDevice->AddData(m_nData) < 0 && m_pDevice->AddData(cTMUnit) < 0)
					{
						m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_GENERAL_FAILURE), IODEVICE_MESSAGETYPE_ERROR);
						m_nData.RemoveAll();
						return FALSE;
					}
					m_nData.RemoveAll();
					return TRUE;
				}
				for (m_nData.RemoveAll(); GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE; )
				{
					m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
					return FALSE;
				}
				return TRUE;
			}
			if (nDataMessageID == PFLP_TRANSFERFRAME)
			{
				if (cPFLPTransferFrame.Unmap(m_nData) && AdjustClockEpoch(tPFLPCDSTimeCode) && cPFLPTransferFrame.GetTimeCode(tPFLPCDSTimeCode) && cPFLPTransferFrame.GetData(nTransferFrameData) > 0)
				{
					for (m_wSequence++; !m_pDevice->UpdateStatus(cPFLPTransferFrame.GetDataQuality(), (cPFLPTransferFrame.GetSequenceCount() == m_wSequence) ? cPFLPTransferFrame.GetSequenceQuality() : PFLP_SEQUENCE_ERROR); )
					{
						if (!m_bSession[0] && m_pDevice->TranslateStatus(szDataDeviceStatus, nDataDeviceStatus) >= 0) m_pDevice->ShowDeviceStatus(szDataDeviceStatus, nDataDeviceStatus);
						break;
					}
					for (bBadTimestamp = (!AdjustClockTime(CTimeTag(tPFLPCDSTimeCode.GetTime())) || AdjustClockDeviation(tPFLPCDSTimeCode)); bBadTimestamp; )
					{
						m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_TIME_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
						break;
					}
					for (m_pDevice->GetTimeCorrelation(tTimestampError, tTimestampDelta), cTMTransferFrame.SetQuality(MAKEWORD(((cPFLPTransferFrame.GetDataQuality() == (ENERTECDEVICE_PMDEMODULATOR_LOCKED | ENERTECDEVICE_PSKDEMODULATOR_LOCKED | ENERTECDEVICE_BITSYNCHRONIZER_LOCKED | ENERTECDEVICE_VITDECODER_LOCKED | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED | ENERTECDEVICE_REEDCRC_NOERRORS) && !bBadTimestamp) ? TMUNIT_DATAQUALITY_GOOD : TMUNIT_DATAQUALITY_BAD) | ((cPFLPTransferFrame.GetSequenceQuality() == PFLP_SEQUENCE_CORRECT) ? TMUNIT_SEQUENCEQUALITY_GOOD : TMUNIT_SEQUENCEQUALITY_BAD), cPFLPTransferFrame.GetDataQuality())), cTMTransferFrame.SetTimeTag((!bBadTimestamp && m_tClockAdjustment[2] > 0) ? (tPFLPCDSTimeCode.GetTime() - tTimestampError + tTimestampDelta) : (tPFLPCDSTimeCode = CTimeTag().GetTime())), cTMTransferFrame.SetData(nTransferFrameData), m_wSequence = cPFLPTransferFrame.GetSequenceCount(); !bBadTimestamp; )
					{
						AdjustClockTime(tPFLPCDSTimeCode);
						break;
					}
					if (!m_bSession[0] && m_pDevice->AddData(m_nData) < 0 && m_pDevice->AddData(cTMTransferFrame) < 0)
					{
						m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_GENERAL_FAILURE), IODEVICE_MESSAGETYPE_ERROR);
						m_nData.RemoveAll();
						return FALSE;
					}
					m_nData.RemoveAll();
					return TRUE;
				}
				for (m_nData.RemoveAll(); GetPhase() == PFLP_DATADISTRIBUTIONREQUESTRESPONSE; )
				{
					m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
					return FALSE;
				}
				return TRUE;
			}
			m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_DATA_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
			m_nData.RemoveAll();
		}
	}
	return FALSE;
}

VOID CPFLPClientSocket::AdjustClockTime()
{
	CTimeTag  tTimeTag;

	m_tClockAdjustment[0] = tTimeTag;
	m_tClockAdjustment[1] = 0;
	m_tClockAdjustment[2] = 0;
	m_tClockAdjustment[3] = 0;
}
BOOL CPFLPClientSocket::AdjustClockTime(CONST CPFLPCDSTimeCode &tTimeCode)
{
	FILETIME  tTime;
	SYSTEMTIME  sTime;
	CTimeTag  tTimeTag;

	if (m_tClockInterval > 0 && (tTimeTag.GetTime() - m_tClockAdjustment[0].GetTime()) / (1000000 * m_tClockInterval.GetTotalSeconds()) != 0)
	{
		if (tTimeCode.GetTime(tTime) && FileTimeToSystemTime(&tTime, &sTime))
		{
			if (tTimeCode >= m_tClockAdjustment[1] && m_tClockAdjustment[2] > 0)
			{
				for (m_tClockAdjustment[0] = tTimeTag; SetSystemTime(&sTime); )
				{
					m_tClockAdjustment[3] = tTimeTag;
					break;
				}
			}
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}
BOOL CPFLPClientSocket::AdjustClockTime(CONST CTimeTag &tTimeCode)
{
	TIMETAG  tDelta;
	CTimeTag  tTimeTag;
	CTimeSpan  tTimeout;

	if (!m_tClockAdjustment[1].GetTime())
	{
		m_tClockAdjustment[0] = tTimeTag;
		m_tClockAdjustment[1] = tTimeCode;
		return TRUE;
	}
	if (!m_tClockAdjustment[2].GetTime())
	{
		if (!CheckDataStreamDrop(tTimeCode.GetTime() - m_tClockAdjustment[1].GetTime()) && !CheckDataStreamDelay(max(tTimeCode.GetTime() - m_tClockAdjustment[1].GetTime(), m_tClockAdjustment[1].GetTime() - tTimeCode.GetTime()), 0))
		{
			for (m_tClockAdjustment[1] = max(tTimeCode, m_tClockAdjustment[1]); CheckDataStreamDelay(tTimeTag.GetTime() - m_tClockAdjustment[0].GetTime(), 0); )
			{
				m_tClockAdjustment[2] = tTimeTag;
				break;
			}
			return TRUE;
		}
		if (!CheckDataStreamDelay(max(tTimeCode.GetTime() - m_tClockAdjustment[1].GetTime(), m_tClockAdjustment[1].GetTime() - tTimeCode.GetTime()), 0))
		{
			m_tClockAdjustment[0] = tTimeTag;
			m_tClockAdjustment[1] = tTimeCode;
			return TRUE;
		}
		m_tClockAdjustment[0] = tTimeTag;
		m_tClockAdjustment[1] = 0;
		return TRUE;
	}
	if (CheckDataStreamDrop(max(tTimeTag.GetTime() - m_tClockAdjustment[2].GetTime(), m_tClockAdjustment[2].GetTime() - tTimeTag.GetTime())))
	{
		m_tClockAdjustment[0] = tTimeTag;
		m_tClockAdjustment[1] = tTimeCode;
		m_tClockAdjustment[2] = 0;
		return TRUE;
	}
	if (tTimeCode >= m_tClockAdjustment[1])
	{
		for (tTimeout = (m_pDevice->GetTimeout(tTimeout)) ? tTimeout : ENERTECDEVICE_DEFAULTTIMEOUT; (tDelta = (tTimeCode.GetTime() - m_tClockAdjustment[1].GetTime() - max(tTimeTag.GetTime() - m_tClockAdjustment[2].GetTime(), 0))) / (1000000 * min(tTimeout.GetTotalSeconds(), SECONDSPERDAY)) == 0 || !CheckDataStreamDrop(tTimeCode.GetTime() - m_tClockAdjustment[1].GetTime()); )
		{
			m_tClockAdjustment[1] = tTimeCode;
			m_tClockAdjustment[2] = tTimeTag;
			return TRUE;
		}
		m_tClockAdjustment[2] = 0;
		return FALSE;
	}
	if (!CheckDataStreamDelay(m_tClockAdjustment[1].GetTime() - tTimeCode.GetTime(), 0))
	{
		m_tClockAdjustment[2] = tTimeTag;
		return TRUE;
	}
	m_tClockAdjustment[2] = 0;
	return FALSE;
}

BOOL CPFLPClientSocket::AdjustClockDeviation(CONST CTimeTag &tTimeCode)
{
	CTimeTag  tTimeTag;

	return(((tTimeTag >= m_tClockAdjustment[3] && tTimeTag.GetTimeInSeconds() - m_tClockAdjustment[3].GetTimeInSeconds() < SECONDSPERDAY) || (tTimeTag < m_tClockAdjustment[3] && m_tClockAdjustment[3].GetTimeInSeconds() - tTimeTag.GetTimeInSeconds() < SECONDSPERDAY)) ? (((tTimeCode >= tTimeTag  &&  m_tClockInterval.GetTotalSeconds() > 0 && tTimeCode.GetTimeInSeconds() - tTimeTag.GetTimeInSeconds() > max(m_tClockInterval.GetTotalSeconds(), SECONDSPERMINUTE)) || (tTimeCode < tTimeTag  &&  m_tClockInterval.GetTotalSeconds() > 0 && tTimeTag.GetTimeInSeconds() - tTimeCode.GetTimeInSeconds() > max(m_tClockInterval.GetTotalSeconds(), SECONDSPERMINUTE))) ? TRUE : FALSE) : FALSE);
}

BOOL CPFLPClientSocket::AdjustClockEpoch(CPFLPCDSTimeCode &tTimeCode)
{
	SYSTEMTIME  tEpoch;

	return((m_pDevice->GetTimeEpoch(&tEpoch)) ? tTimeCode.SetEpoch(&tEpoch) : FALSE);
}

BOOL CPFLPClientSocket::CheckDataStreamDrop(TIMETAG tInterval) CONST
{
	return((tInterval >= 1000000 * m_pDevice->GetDataStreamDropInterval().GetTotalSeconds()) ? TRUE : FALSE);
}

BOOL CPFLPClientSocket::CheckDataStreamDelay(TIMETAG tDelay, TIMETAG tInterval) CONST
{
	return((tDelay >= max(1000000 * m_pDevice->GetDataStreamDelayInterval().GetTotalSeconds(), tInterval)) ? TRUE : FALSE);
}

BOOL CPFLPClientSocket::SetPhase(UINT nPhase)
{
	if (nPhase == PFLP_SERVICE || nPhase == PFLP_SERVICEREQUEST || nPhase == PFLP_SERVICEREQUESTRESPONSE || nPhase == PFLP_DATADISTRIBUTIONREQUEST || nPhase == PFLP_DATADISTRIBUTIONREQUESTRESPONSE || nPhase == PFLP_DATADISTRIBUTIONSTOPREQUEST || nPhase == PFLP_DATADISTRIBUTIONSTOPREQUESTRESPONSE || nPhase == PFLP_SERVICEENDREQUEST || nPhase == PFLP_SERVICEENDREQUESTRESPONSE)
	{
		m_nPhase = nPhase;
		return TRUE;
	}
	return FALSE;
}

UINT CPFLPClientSocket::GetPhase() CONST
{
	return m_nPhase;
}

/////////////////////////////////////////////////////////////////////////////
// CPFLPClientSocket member functions

BOOL CPFLPClientSocket::OnMessagePending()
{
	MSG  sMsg;

	while (PeekMessage(&sMsg, (HWND)NULL, WM_TIMER, WM_TIMER, PM_REMOVE))
	{
		if (m_nTimerID[0] != (UINT_PTR)sMsg.wParam  &&  m_nTimerID[1] != (UINT_PTR)sMsg.wParam)
		{
			if (!AfxPreTranslateMessage(&sMsg))
			{
				TranslateMessage(&sMsg);
				DispatchMessage(&sMsg);
			}
			continue;
		}
		if (m_nTimerID[0] == (UINT_PTR)sMsg.wParam)
		{
			KillTimer((HWND)NULL, m_nTimerID[0]);
			m_nTimerID[0] = 0;
		}
		else
		{
			KillTimer((HWND)NULL, m_nTimerID[1]);
			m_nTimerID[1] = 0;
		}
		CancelBlockingCall();
	}
	return CSocket::OnMessagePending();
}

void CPFLPClientSocket::OnReceive(int nErrorCode)
{
	INT  cbData;
	CByteArray  nData;

	if ((cbData = Receive(nData)) <= 0)
	{
		if (cbData < 0 && m_pDevice != (CENERTECDevice *)NULL) m_pDevice->ShowDeviceMessage(STRING(IDS_ENERTECDEVICE_MESSAGE_PFLP_SOCKET_FAILURE), IODEVICE_MESSAGETYPE_WARNING);
		Close();
		return;
	}
	while (nData.GetSize() > 0)
	{
		if (m_pDevice != (CENERTECDevice *)NULL)
		{
			for (Parse(nData); m_nTimerID[1] != 0; )
			{
				KillTimer((HWND)NULL, m_nTimerID[1]);
				m_nTimerID[1] = 0;
				break;
			}
			continue;
		}
		Close();
		break;
	}
	CSocket::OnReceive(nErrorCode);
}

void CPFLPClientSocket::OnClose(int nErrorCode)
{
	UINT  nStatus;
	CString  szStatus;

	for (SetPhase(PFLP_SERVICE); m_pDevice != (CENERTECDevice *)NULL; )
	{
		m_pDevice->UpdateStatus(0);
		m_pDevice->TranslateStatus(szStatus, nStatus);
		m_pDevice->ShowDeviceStatus(szStatus, nStatus);
		m_pDevice = (CENERTECDevice *)NULL;
		break;
	}
	CSocket::OnClose(nErrorCode);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPClientSockets

CPFLPClientSockets::CPFLPClientSockets() : CPtrArray()
{
	return;
}

CPFLPClientSockets::~CPFLPClientSockets()
{
	RemoveAll();
}

BOOL CPFLPClientSockets::Add(CPFLPClientSocket *pSocket)
{
	INT  nConnection;
	INT  nConnections;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if (!GetAt(nConnection)->IsOpen())
		{
			delete GetAt(nConnection);
			RemoveAt(nConnection);
			nConnections--;
			nConnection--;
		}
	}
	return((CPtrArray::Add(pSocket) >= 0) ? TRUE : FALSE);
}

INT CPFLPClientSockets::Enum(CStringArray &szComputers) CONST
{
	INT  nConnection;
	INT  nConnections;
	DWORD  cbInData;
	DWORD  cbOutData;
	CString  szPeer[2];
	CTimeTag  tConnectTime;
	CTimeTag  tLastUseTime;
	CPFLPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(), szComputers.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->GetConnectionProperties(szPeer[0], szPeer[1], tConnectTime, tLastUseTime, cbInData, cbOutData))
		{
			szComputers.Add(szPeer[0] + EOL + szPeer[1]);
			continue;
		}
	}
	return((INT)szComputers.GetSize());
}
INT CPFLPClientSockets::Enum(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST
{
	INT  nConnection;
	INT  nConnections;
	DWORD  cbInData;
	DWORD  cbOutData;
	CString  szPeer[2];
	CTimeTag  tConnectTime;
	CTimeTag  tLastUseTime;
	CPFLPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(), szComputers.RemoveAll(), tConnectTimes.RemoveAll(), tLastUseTimes.RemoveAll(), cbInBytes.RemoveAll(), cbOutBytes.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->GetConnectionProperties(szPeer[0], szPeer[1], tConnectTime, tLastUseTime, cbInData, cbOutData))
		{
			szComputers.Add(szPeer[0] + EOL + szPeer[1]);
			tConnectTimes.Add(tConnectTime);
			tLastUseTimes.Add(tLastUseTime);
			cbInBytes.Add(cbInData);
			cbOutBytes.Add(cbOutData);
		}
	}
	return((INT)szComputers.GetSize());
}

VOID CPFLPClientSockets::Update(INT nDataID, CONST CTCUnit &cTCUnit)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->IsOpen())
		{
			pSocket->Update(nDataID, cTCUnit);
			continue;
		}
	}
}
VOID CPFLPClientSockets::Update(INT nDataID, CONST CTCTransferUnit &cTCTransferUnit)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->IsOpen())
		{
			pSocket->Update(nDataID, cTCTransferUnit);
			continue;
		}
	}
}

CPFLPClientSocket *CPFLPClientSockets::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPClientSocket *)CPtrArray::GetAt(nIndex) : (CPFLPClientSocket *)NULL);
}

CPFLPClientSocket *CPFLPClientSockets::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPClientSocket *)CPtrArray::GetAt(nIndex) : (CPFLPClientSocket *)NULL);
}

BOOL CPFLPClientSockets::Abort(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime)
{
	INT  nConnection;
	INT  nConnections;
	CPFLPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->Abort(pszComputer, tConnectTime))
		{
			RemoveAt(nConnection);
			delete pSocket;
			break;
		}
	}
	return((nConnection < nConnections) ? TRUE : FALSE);
}

VOID CPFLPClientSockets::RemoveAll()
{
	INT  nConnection;
	INT  nConnections;
	CPFLPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)))
		{
			pSocket->Close();
			delete pSocket;
		}
	}
	CPtrArray::RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceSocket

IMPLEMENT_DYNCREATE(CPFLPServiceSocket, CSocket)

CPFLPServiceSocket::CPFLPServiceSocket() : CSocket()
{
	m_pDevice = (CENERTECDevice *)NULL;
}

BOOL CPFLPServiceSocket::Open(CENERTECDevice *pDevice, UINT nPort)
{
	for (m_pDevice = pDevice; Create(nPort); )
	{
		if (Listen()) return TRUE;
		Close();
		break;
	}
	return FALSE;
}

BOOL CPFLPServiceSocket::IsOpen() CONST
{
	return((m_hSocket != (SOCKET)INVALID_SOCKET) ? TRUE : FALSE);
}

VOID CPFLPServiceSocket::Close()
{
	for (m_pServerSockets.RemoveAll(), m_pClientSockets.RemoveAll(); IsOpen(); )
	{
		CSocket::Close();
		break;
	}
}

INT CPFLPServiceSocket::EnumConnections(CStringArray &szComputers) CONST
{
	return((IsOpen()) ? m_pServerSockets.Enum(szComputers) : m_pClientSockets.Enum(szComputers));
}
INT CPFLPServiceSocket::EnumConnections(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST
{
	return((IsOpen()) ? m_pServerSockets.Enum(szComputers, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes) : m_pClientSockets.Enum(szComputers, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes));
}

BOOL CPFLPServiceSocket::UpdateConnections(INT nDataID, CONST CByteArray &nData)
{
	if (IsOpen())
	{
		m_pServerSockets.Update(nDataID, nData);
		return TRUE;
	}
	return FALSE;
}
BOOL CPFLPServiceSocket::UpdateConnections(INT nDataID, CONST CTMUnit &cTMUnit)
{
	if (IsOpen())
	{
		m_pServerSockets.Update(nDataID, cTMUnit);
		return TRUE;
	}
	return FALSE;
}
BOOL CPFLPServiceSocket::UpdateConnections(INT nDataID, CONST CTMTransferUnit &cTMTransferUnit)
{
	if (IsOpen())
	{
		m_pServerSockets.Update(nDataID, cTMTransferUnit);
		return TRUE;
	}
	return FALSE;
}
VOID CPFLPServiceSocket::UpdateConnections(INT nDataID, CONST CTCUnit &cTCUnit)
{
	m_pClientSockets.Update(nDataID, cTCUnit);
}
VOID CPFLPServiceSocket::UpdateConnections(INT nDataID, CONST CTCTransferUnit &cTCTransferUnit)
{
	m_pClientSockets.Update(nDataID, cTCTransferUnit);
}

BOOL CPFLPServiceSocket::AddConnection(CPFLPServerSocket *pSocket)
{
	return m_pServerSockets.Add(pSocket);
}
BOOL CPFLPServiceSocket::AddConnection(CPFLPClientSocket *pSocket)
{
	return m_pClientSockets.Add(pSocket);
}

BOOL CPFLPServiceSocket::AbortConnection(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime)
{
	return((IsOpen()) ? m_pServerSockets.Abort(pszComputer, tConnectTime) : m_pClientSockets.Abort(pszComputer, tConnectTime));
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceSocket member functions

void CPFLPServiceSocket::OnAccept(int nErrorCode)
{
	CPFLPServerSocket  *pSocket;

	if ((pSocket = new CPFLPServerSocket))
	{
		if (pSocket->Open(m_pDevice) && Accept(*pSocket) && AddConnection(pSocket)) return;
		pSocket->Close();
		delete pSocket;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceThread

IMPLEMENT_DYNCREATE(CENERTECDeviceThread, CThread)

CENERTECDeviceThread::CENERTECDeviceThread() : CThread()
{
	m_pIODevice[0] = (CENERTECDevice *)NULL;
	m_pIODevice[1] = new CENERTECDevice;
	m_hIODeviceData[0] = (HANDLE)NULL;
	m_hIODeviceData[1] = (HANDLE)NULL;
	m_nIODeviceDataID = 0;
	m_dwIODevice = 0;
}

CENERTECDeviceThread::~CENERTECDeviceThread()
{
	Stop();
	delete m_pIODevice[1];
}

BOOL CENERTECDeviceThread::InitInstance()
{
	return((AfxOleInit() && AfxSocketInit()) ? CThread::InitInstance() : FALSE);
}

int CENERTECDeviceThread::ExitInstance()
{
	return CThread::ExitInstance();
}

BOOL CENERTECDeviceThread::Start(CENERTECDevice *pDevice)
{
	CEvent  cEvent[2];

	for ((m_pIODevice[0] = pDevice)->MonitorDeviceDataBuffers(m_hIODeviceData[0], m_hIODeviceData[1]), m_pIODevice[1]->Copy(pDevice), ResetEvent(m_hIODeviceData[0]), ResetEvent(m_hIODeviceData[1]); CreateThread(cEvent, THREAD_PRIORITY_ABOVE_NORMAL); )
	{
		if (Wait(cEvent, sizeof(cEvent) / sizeof(cEvent[0]), FALSE, INFINITE, FALSE) == WAIT_OBJECT_0 + 1) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CENERTECDeviceThread::Suspend()
{
	DWORD  dwCount;

	if (GetThreadID() != 0)
	{
		if ((dwCount = SuspendThread()) != (DWORD)-1)
		{
			m_dwIODevice = dwCount + 1;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CENERTECDeviceThread::IsSuspended() CONST
{
	return((GetThreadID() != 0 && m_dwIODevice > 0) ? TRUE : FALSE);
}

BOOL CENERTECDeviceThread::Resume()
{
	DWORD  dwCount;

	if (GetThreadID() != 0)
	{
		if ((dwCount = ResumeThread()) != (DWORD)-1)
		{
			m_dwIODevice = dwCount - 1;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CENERTECDeviceThread::Stop()
{
	return((DestroyThread() != (DWORD)-1) ? TRUE : FALSE);
}

BOOL CENERTECDeviceThread::Configure(CONST CENERTECDevice *pDevice)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pIODevice[1] != pDevice) ? ((m_pIODevice[1]->Copy(pDevice)) ? m_cIODeviceEvent.SetEvent() : FALSE) : TRUE);
}

INT CENERTECDeviceThread::EnumConnections(CStringArray &szComputers) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_cPFLPServiceSocket.EnumConnections(szComputers);
}
INT CENERTECDeviceThread::EnumConnections(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_cPFLPServiceSocket.EnumConnections(szComputers, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes);
}

BOOL CENERTECDeviceThread::AbortConnection(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime)
{
	INT  nConnection;
	INT  nConnections;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nConnection = 0, nConnections = (INT)m_szAbortConnections.GetSize(); nConnection < nConnections; nConnection++)
	{
		if (!m_szAbortConnections.GetAt(nConnection).CompareNoCase(pszComputer) && (m_tAbortConnections.GetAt(nConnection) == tConnectTime || tConnectTime == 0)) break;
		continue;
	}
	if (nConnection == nConnections)
	{
		m_szAbortConnections.Add(pszComputer);
		m_tAbortConnections.Add(tConnectTime);
		return m_cIODeviceEvent.SetEvent();
	}
	return TRUE;
}

INT CENERTECDeviceThread::AddData(CONST CByteArray &nData, BOOL bInData)
{
	INT  nIndex;
	CByteArray  *pData;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pData = new CByteArray))
	{
		for (pData->Copy(nData), m_pIODeviceData[bInData].InsertAt((nIndex = (INT)m_pIODeviceData[bInData].GetSize()), pData, 1); !bInData; )
		{
			m_nIODeviceDataIDs[0].SetAtGrow(nIndex, (m_nIODeviceDataID = (++m_nIODeviceDataID > 0) ? m_nIODeviceDataID : 0));
			break;
		}
		return((SetEvent(m_hIODeviceData[bInData])) ? ((!bInData) ? m_nIODeviceDataID : TRUE) : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::AddData(CONST CTMUnit &cTMUnit, BOOL bInData)
{
	INT  nIndex;
	CTMUnit  *pTMUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMUnit = new CTMUnit))
	{
		for (pTMUnit->Copy(&cTMUnit), m_pIODeviceTMUnits[bInData].InsertAt((nIndex = (INT)m_pIODeviceTMUnits[bInData].GetSize()), pTMUnit, 1); !bInData; )
		{
			m_nIODeviceDataIDs[1].SetAtGrow(nIndex, (m_nIODeviceDataID = (++m_nIODeviceDataID > 0) ? m_nIODeviceDataID : 0));
			break;
		}
		return((SetEvent(m_hIODeviceData[bInData])) ? ((!bInData) ? m_nIODeviceDataID : TRUE) : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::AddData(CONST CTMTransferUnit &cTMTransferUnit, BOOL bInData)
{
	INT  nIndex;
	CTMTransferUnit  *pTMTransferUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMTransferUnit = new CTMTransferUnit))
	{
		for (pTMTransferUnit->Copy(&cTMTransferUnit), m_pIODeviceTMTransferUnits[bInData].InsertAt((nIndex = (INT)m_pIODeviceTMTransferUnits[bInData].GetSize()), pTMTransferUnit, 1); !bInData; )
		{
			m_nIODeviceDataIDs[2].SetAtGrow(nIndex, (m_nIODeviceDataID = (++m_nIODeviceDataID > 0) ? m_nIODeviceDataID : 0));
			break;
		}
		return((SetEvent(m_hIODeviceData[bInData])) ? ((!bInData) ? m_nIODeviceDataID : TRUE) : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::AddData(CONST CTCUnit &cTCUnit, BOOL bInData)
{
	INT  nIndex;
	CTCUnit  *pTCUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTCUnit = new CTCUnit))
	{
		for (pTCUnit->Copy(&cTCUnit), m_pIODeviceTCUnits[bInData].InsertAt((nIndex = (INT)m_pIODeviceTCUnits[bInData].GetSize()), pTCUnit, 1); !bInData; )
		{
			m_nIODeviceDataIDs[3].SetAtGrow(nIndex, (m_nIODeviceDataID = (++m_nIODeviceDataID > 0) ? m_nIODeviceDataID : 0));
			break;
		}
		return((SetEvent(m_hIODeviceData[bInData])) ? ((!bInData) ? m_nIODeviceDataID : TRUE) : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::AddData(CONST CTCTransferUnit &cTCTransferUnit, BOOL bInData)
{
	INT  nIndex;
	CTCTransferUnit  *pTCTransferUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTCTransferUnit = new CTCTransferUnit))
	{
		for (pTCTransferUnit->Copy(&cTCTransferUnit), m_pIODeviceTCTransferUnits[bInData].InsertAt((nIndex = (INT)m_pIODeviceTCTransferUnits[bInData].GetSize()), pTCTransferUnit, 1); !bInData; )
		{
			m_nIODeviceDataIDs[4].SetAtGrow(nIndex, (m_nIODeviceDataID = (++m_nIODeviceDataID > 0) ? m_nIODeviceDataID : 0));
			break;
		}
		return((SetEvent(m_hIODeviceData[bInData])) ? ((!bInData) ? m_nIODeviceDataID : TRUE) : -1);
	}
	return -1;
}

INT CENERTECDeviceThread::RemoveData(CByteArray &nData, BOOL bInData)
{
	INT  nIndex;
	INT  nDataID;
	CByteArray  *pData;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pData = (m_pIODeviceData[bInData].GetSize() > 0) ? (CByteArray *)m_pIODeviceData[bInData].GetAt((nIndex = 0)) : (CByteArray *)NULL))
	{
		for (nDataID = (!bInData) ? m_nIODeviceDataIDs[0].GetAt(nIndex) : TRUE, nData.Copy(*pData), m_pIODeviceData[bInData].RemoveAt(nIndex); !bInData; )
		{
			m_nIODeviceDataIDs[0].RemoveAt(nIndex);
			break;
		}
		delete pData;
		return((!m_pIODeviceData[bInData].GetSize() || SetEvent(m_hIODeviceData[bInData])) ? nDataID : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::RemoveData(CTMUnit &cTMUnit, BOOL bInData)
{
	INT  nIndex;
	INT  nDataID;
	CTMUnit  *pTMUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMUnit = m_pIODeviceTMUnits[bInData].GetAt((nIndex = 0))))
	{
		for (nDataID = (!bInData) ? m_nIODeviceDataIDs[1].GetAt(nIndex) : TRUE, cTMUnit.Copy(pTMUnit), m_pIODeviceTMUnits[bInData].RemoveAt(nIndex); !bInData; )
		{
			m_nIODeviceDataIDs[1].RemoveAt(nIndex);
			break;
		}
		delete pTMUnit;
		return((!m_pIODeviceTMUnits[bInData].GetSize() || SetEvent(m_hIODeviceData[bInData])) ? nDataID : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::RemoveData(CTMTransferUnit &cTMTransferUnit, BOOL bInData)
{
	INT  nIndex;
	INT  nDataID;
	CTMTransferUnit  *pTMTransferUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMTransferUnit = m_pIODeviceTMTransferUnits[bInData].GetAt((nIndex = 0))))
	{
		for (nDataID = (!bInData) ? m_nIODeviceDataIDs[2].GetAt(nIndex) : TRUE, cTMTransferUnit.Copy(pTMTransferUnit), m_pIODeviceTMTransferUnits[bInData].RemoveAt(nIndex); !bInData; )
		{
			m_nIODeviceDataIDs[2].RemoveAt(nIndex);
			break;
		}
		delete pTMTransferUnit;
		return((!m_pIODeviceTMTransferUnits[bInData].GetSize() || SetEvent(m_hIODeviceData[bInData])) ? nDataID : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::RemoveData(CTCUnit &cTCUnit, BOOL bInData)
{
	INT  nIndex;
	INT  nDataID;
	CTCUnit  *pTCUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTCUnit = m_pIODeviceTCUnits[bInData].GetAt((nIndex = 0))))
	{
		for (nDataID = (!bInData) ? m_nIODeviceDataIDs[3].GetAt(nIndex) : TRUE, cTCUnit.Copy(pTCUnit), m_pIODeviceTCUnits[bInData].RemoveAt(nIndex); !bInData; )
		{
			m_nIODeviceDataIDs[3].RemoveAt(nIndex);
			break;
		}
		delete pTCUnit;
		return((!m_pIODeviceTCUnits[bInData].GetSize() || SetEvent(m_hIODeviceData[bInData])) ? nDataID : -1);
	}
	return -1;
}
INT CENERTECDeviceThread::RemoveData(CTCTransferUnit &cTCTransferUnit, BOOL bInData)
{
	INT  nIndex;
	INT  nDataID;
	CTCTransferUnit  *pTCTransferUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTCTransferUnit = m_pIODeviceTCTransferUnits[bInData].GetAt((nIndex = 0))))
	{
		for (nDataID = (!bInData) ? m_nIODeviceDataIDs[4].GetAt(nIndex) : TRUE, cTCTransferUnit.Copy(pTCTransferUnit), m_pIODeviceTCTransferUnits[bInData].RemoveAt(nIndex); !bInData; )
		{
			m_nIODeviceDataIDs[4].RemoveAt(nIndex);
			break;
		}
		delete pTCTransferUnit;
		return((!m_pIODeviceTCTransferUnits[bInData].GetSize() || SetEvent(m_hIODeviceData[bInData])) ? nDataID : -1);
	}
	return -1;
}

BOOL CENERTECDeviceThread::ClearData(BOOL bInData)
{
	INT  nIndex;
	INT  nCount;
	CByteArray  *pData;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nIndex = 0, nCount = (INT)m_pIODeviceData[bInData].GetSize(); nIndex < nCount; nIndex++)
	{
		if ((pData = (CByteArray *)m_pIODeviceData[bInData].GetAt(nIndex))) delete pData;
		continue;
	}
	m_pIODeviceData[bInData].RemoveAll();
	m_pIODeviceTMUnits[bInData].RemoveAll();
	m_pIODeviceTCUnits[bInData].RemoveAll();
	m_pIODeviceTMTransferUnits[bInData].RemoveAll();
	m_pIODeviceTCTransferUnits[bInData].RemoveAll();
	return ResetEvent(m_hIODeviceData[bInData]);
}

int CENERTECDeviceThread::Run()
{
	INT  nUser;
	INT  nUsers;
	INT  nIndex;
	INT  nCount;
	INT  nDataID;
	UINT  nMode;
	UINT  nPort;
	BOOL  bRestart;
	DWORD  dwResult;
	DWORD  dwTimeout;
	CEvent  *pEvent;
	CTMUnit  cTMUnit;
	CTCUnit  cTCUnit;
	CString  szAddress;
	CTimeKey  tUpdate;
	CTimeSpan  tInterval;
	CByteArray  nData;
	CUIntArray  nCodes;
	CStringArray  szUsers[2];
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CTMTransferUnit  cTMTransferUnit;
	CTCTransferUnit  cTCTransferUnit;
	CPFLPClientSocket  *pSocket;
	HANDLE  hIODevice[2] = { m_cIODeviceEvent.m_hObject,m_hIODeviceData[0] };

	for (pEvent = (CEvent *)GetThreadInfo(), m_pIODevice[0]->GetDeviceMode(nMode), m_pIODevice[0]->GetIPAddress(szAddress, nPort), dwTimeout = 0; nMode & IODEVICE_TYPE_SERVER; )
	{
		if (m_cPFLPServiceSocket.Open(m_pIODevice[0], nPort))
		{
			pEvent[0].SetEvent();
			break;
		}
		pEvent[1].SetEvent();
		return 0;
	}
	for (; nMode & IODEVICE_TYPE_CLIENT; )
	{
		if ((pSocket = new CPFLPClientSocket))
		{
			if (pSocket->Open(m_pIODevice[0]))
			{
				if (m_cPFLPServiceSocket.AddConnection(pSocket))
				{
					pEvent[0].SetEvent();
					break;
				}
				pSocket->Close();
			}
			delete pSocket;
		}
		pEvent[1].SetEvent();
		return 0;
	}
	while (((dwResult = Wait(hIODevice, sizeof(hIODevice) / sizeof(HANDLE), FALSE, dwTimeout)) > WAIT_OBJECT_0  &&  dwResult <= WAIT_OBJECT_0 + sizeof(hIODevice) / sizeof(HANDLE)) || dwResult == WAIT_TIMEOUT)
	{
		if (dwResult == WAIT_OBJECT_0 + sizeof(hIODevice) / sizeof(HANDLE))
		{
			if ((nDataID = RemoveData(nData, FALSE)) >= 0)
			{
				m_cPFLPServiceSocket.UpdateConnections(nDataID, nData);
				continue;
			}
			if ((nDataID = RemoveData(cTMUnit, FALSE)) >= 0)
			{
				m_cPFLPServiceSocket.UpdateConnections(nDataID, cTMUnit);
				continue;
			}
			if ((nDataID = RemoveData(cTMTransferUnit, FALSE)) >= 0)
			{
				m_cPFLPServiceSocket.UpdateConnections(nDataID, cTMTransferUnit);
				continue;
			}
			if ((nDataID = RemoveData(cTCUnit, FALSE)) >= 0)
			{
				m_cPFLPServiceSocket.UpdateConnections(nDataID, cTCUnit);
				continue;
			}
			if ((nDataID = RemoveData(cTCTransferUnit, FALSE)) >= 0)
			{
				m_cPFLPServiceSocket.UpdateConnections(nDataID, cTCTransferUnit);
				continue;
			}
		}
		if (dwResult == WAIT_OBJECT_0 + 1)
		{
			for (m_pIODevice[0]->Lock(), Lock(), m_pIODevice[0]->Update(m_pIODevice[1], (bRestart = TRUE)); m_szAbortConnections.GetSize() > 0; m_szAbortConnections.RemoveAt(0), m_tAbortConnections.RemoveAt(0))
			{
				m_cPFLPServiceSocket.AbortConnection(m_szAbortConnections.GetAt(0), m_tAbortConnections.GetAt(0));
				continue;
			}
			Unlock();
			m_pIODevice[0]->Unlock();
		}
		if (dwResult == WAIT_TIMEOUT)
		{
			for (nUser = 0, nUsers = m_pIODevice[0]->GetDeviceSecurity(szUsers[0], nCodes, tStartTimes, tStopTimes), m_cPFLPServiceSocket.EnumConnections(szUsers[1]), tUpdate = CTime::GetCurrentTime().GetTime(); nUser < nUsers; nUser++)
			{
				for (nIndex = 0, nCount = ((nCodes.GetAt(nUser) & IODEVICE_SECURITY_RESTRICTEDACCESS) && (tUpdate < tStartTimes.GetAt(nUser) || tUpdate >= tStopTimes.GetAt(nUser))) ? (INT)szUsers[1].GetSize() : 0; nIndex < nCount; nIndex++)
				{
					if (!szUsers[1].GetAt(nIndex).CompareNoCase(szUsers[0].GetAt(nUser)))
					{
						m_cPFLPServiceSocket.AbortConnection(szUsers[0].GetAt(nUser), 0);
						break;
					}
				}
			}
		}
		if (dwResult == WAIT_OBJECT_0 + 1 || dwResult == WAIT_TIMEOUT)
		{
			for (nUser = 0, nUsers = m_pIODevice[0]->GetDeviceSecurity(szUsers[0], nCodes, tStartTimes, tStopTimes), tUpdate = CTime::GetCurrentTime().GetTime(), tInterval = 0; nUser < nUsers; nUser++)
			{
				if ((nCodes.GetAt(nUser) & IODEVICE_SECURITY_RESTRICTEDACCESS) && tUpdate < tStopTimes.GetAt(nUser).GetTime())
				{
					if (tStopTimes.GetAt(nUser).GetTime() - tUpdate.GetTime() < tInterval.GetTotalSeconds() || tInterval == 0)
					{
						tInterval = tStopTimes.GetAt(nUser).GetTime() - tUpdate.GetTime();
						continue;
					}
				}
			}
			dwTimeout = (tInterval > 0) ? (DWORD)(1000 * min(tInterval.GetTotalSeconds(), SECONDSPERDAY)) : INFINITE;
		}
	}
	m_cPFLPServiceSocket.Close();
	return 0;
}

BEGIN_MESSAGE_MAP(CENERTECDeviceThread, CThread)
	//{{AFX_MSG_MAP(CENERTECDeviceThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CENERTECDevice

IMPLEMENT_DYNCREATE(CENERTECDevice, CIODevice)

CPtrArray  CENERTECDevice::m_pIODevices;
CPtrArray  CENERTECDevice::m_nIODeviceTimerIDs;

CENERTECDevice::CENERTECDevice() : CIODevice()
{
	Initialize(IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_DATASERVICE_TRANSFERFRAMES);
	m_pIOThread = (CENERTECDeviceThread *)NULL;
}

CENERTECDevice::~CENERTECDevice()
{
	Stop();
	FreeData();
}

VOID CENERTECDevice::SetDeviceID(BYTE nID)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->nDeviceID = nID;
}

BOOL CENERTECDevice::GetDeviceID(BYTE &nID) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((nID = GetData()->nDeviceID) != 0) ? TRUE : FALSE);
}

VOID CENERTECDevice::SetDeviceMode(UINT nFlags)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->nDeviceMode = nFlags;
}

BOOL CENERTECDevice::GetDeviceMode(UINT &nFlags) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((nFlags = GetData()->nDeviceMode) != 0) ? TRUE : FALSE);
}

BOOL CENERTECDevice::SetIPAddress(LPCTSTR pszAddress, UINT nPort)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (InetPton(AF_INET, pszAddress, &GetData()->sIPAddress.sin_addr))
	{
		GetData()->sIPAddress.sin_family = AF_INET;
		GetData()->sIPAddress.sin_port = nPort;
		return TRUE;
	}
	return FALSE;
}
VOID CENERTECDevice::SetIPAddress(CONST SOCKADDR_IN *pAddress)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	CopyMemory(&GetData()->sIPAddress, pAddress, sizeof(SOCKADDR_IN));
}

BOOL CENERTECDevice::GetIPAddress(CString &szAddress, UINT &nPort) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (InetNtop(AF_INET, &GetData()->sIPAddress.sin_addr, szAddress.GetBufferSetLength(4 * sizeof(GetData()->sIPAddress.sin_addr)), 4 * sizeof(GetData()->sIPAddress.sin_addr)))
	{
		nPort = GetData()->sIPAddress.sin_port;
		szAddress.ReleaseBuffer();
		return TRUE;
	}
	szAddress.ReleaseBuffer();
	return FALSE;
}
BOOL CENERTECDevice::GetIPAddress(SOCKADDR_IN *pAddress) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetData()->sIPAddress.sin_family == AF_INET)
	{
		CopyMemory(pAddress, &GetData()->sIPAddress, sizeof(SOCKADDR_IN));
		return TRUE;
	}
	return FALSE;
}

VOID CENERTECDevice::SetTimeout(CONST CTimeSpan &tInterval)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->tTimeout = tInterval.GetTotalSeconds();
}

BOOL CENERTECDevice::GetTimeout(CTimeSpan &tInterval) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((tInterval = GetData()->tTimeout) > 0) ? TRUE : FALSE);
}

VOID CENERTECDevice::SetBufferSize(UINT nSize)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->nBufferSize = nSize;
}

BOOL CENERTECDevice::GetBufferSize(UINT &nSize) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((nSize = GetData()->nBufferSize) > 0) ? TRUE : FALSE);
}

VOID CENERTECDevice::SetVCIDFilter(WORD wVCID)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->wDataFilter[0] = wVCID;
}

BOOL CENERTECDevice::GetVCIDFilter(WORD &wVCID) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((wVCID = GetData()->wDataFilter[0]) != (WORD)-1) ? TRUE : FALSE);
}

VOID CENERTECDevice::SetAPIDFilter(WORD wAPID)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->wDataFilter[1] = wAPID;
}

BOOL CENERTECDevice::GetAPIDFilter(WORD &wAPID) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((wAPID = GetData()->wDataFilter[1]) != (WORD)-1) ? TRUE : FALSE);
}

BOOL CENERTECDevice::SetTimeEpoch(CONST SYSTEMTIME *pTime)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (pTime->wYear > 0 && pTime->wMonth > 0 && pTime->wDay > 0 && pTime->wHour >= 0 && pTime->wMinute >= 0 && pTime->wSecond >= 0 && pTime->wMilliseconds >= 0)
	{
		CopyMemory(&GetData()->tEpochTime, pTime, sizeof(SYSTEMTIME));
		return TRUE;
	}
	return FALSE;
}

BOOL CENERTECDevice::GetTimeEpoch(SYSTEMTIME *pTime) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetData()->tEpochTime.wYear > 0 && GetData()->tEpochTime.wMonth > 0 && GetData()->tEpochTime.wDay > 0 && GetData()->tEpochTime.wHour >= 0 && GetData()->tEpochTime.wMinute >= 0 && GetData()->tEpochTime.wSecond >= 0 && GetData()->tEpochTime.wMilliseconds >= 0)
	{
		CopyMemory(pTime, &GetData()->tEpochTime, sizeof(SYSTEMTIME));
		return TRUE;
	}
	return FALSE;
}

VOID CENERTECDevice::SetTimeCorrelation(LONG tError, LONG tDelta)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->tCorrelationError = tError;
	GetData()->tCorrelationDelta = tDelta;
}

BOOL CENERTECDevice::GetTimeCorrelation(LONG &tError, LONG &tDelta) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	tError = GetData()->tCorrelationError;
	tDelta = GetData()->tCorrelationDelta;
	return((tError != 0 || tDelta != 0) ? TRUE : FALSE);
}

VOID CENERTECDevice::SetClockAdjustmentInterval(CONST CTimeSpan &tInterval)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->tClockAdjustment = tInterval.GetTotalSeconds();
}

BOOL CENERTECDevice::GetClockAdjustmentInterval(CTimeSpan &tInterval) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((tInterval = GetData()->tClockAdjustment) > 0) ? TRUE : FALSE);
}

VOID CENERTECDevice::SetStatusMessageInterval(CONST CTimeSpan &tInterval)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	GetData()->tStatusMessageInterval = tInterval.GetTotalSeconds();
}

BOOL CENERTECDevice::GetStatusMessageInterval(CTimeSpan &tInterval) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((tInterval = GetData()->tStatusMessageInterval) > 0) ? TRUE : FALSE);
}

CTimeSpan CENERTECDevice::GetDataStreamDropInterval() CONST
{
	return m_tOperationsDataDrop[0];
}

CTimeSpan CENERTECDevice::GetDataStreamDelayInterval() CONST
{
	return m_tOperationsDataDelay[0];
}

BOOL CENERTECDevice::AddClient(LPCTSTR pszClient, CONST CTimeTag &tConnectTime)
{
	INT  nPos;
	INT  nIndex;
	INT  nCount;
	INT  nClient;
	INT  nClients;
	UINT  nLoginsMask;
	LPVOID  pLoginsData;
	CUIntArray  nAccessCodes;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	IODEVICELOGINSPROCEDURE  pLoginsProcedure;

	for (Lock(), nIndex = 0, nCount = (INT)m_szLogins.GetSize(), pLoginsProcedure = m_pIODeviceLoginsProcedure, pLoginsData = m_pOperationsLoginsData, nLoginsMask = m_nOperationsLoginsMask; nIndex < nCount; nIndex++)
	{
		if (!m_szLogins.GetAt(nIndex).CompareNoCase(pszClient) && m_tLogins.GetAt(nIndex) == tConnectTime) break;
		continue;
	}
	if (nIndex == nCount)
	{
		for (nClient = 0, nClients = (pLoginsProcedure != (IODEVICELOGINSPROCEDURE)NULL && (nLoginsMask & IODEVICE_LOGIN_SUCCESS)) ? GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes) : 0, m_szLogins.Add(pszClient), m_tLogins.Add(tConnectTime), Unlock(); nClient < nClients; nClient++)
		{
			if ((((nPos = szClients.GetAt(nClient).Find(EOL)) >= 0 && !szClients.GetAt(nClient).Mid(nPos + 1).CompareNoCase(pszClient)) || !szClients.GetAt(nClient).CompareNoCase(pszClient)) || (szClients.GetAt(nClient).IsEmpty() && (nAccessCodes.GetAt(nClient) & IODEVICE_SECURITY_UNLIMITEDACCESS)))
			{
				(*pLoginsProcedure)(IODEVICE_LOGIN_SUCCESS | ((nAccessCodes.GetAt(nClient) & IODEVICE_SECURITY_AUDITACCESS) ? IODEVICE_LOGINOUT_AUDIT : 0), pszClient, tConnectTime.GetTime(), pLoginsData);
				break;
			}
		}
		return TRUE;
	}
	Unlock();
	return FALSE;
}

BOOL CENERTECDevice::RemoveClient(LPCTSTR pszClient, CONST CTimeTag &tConnectTime)
{
	INT  nPos;
	INT  nIndex;
	INT  nCount;
	INT  nClient;
	INT  nClients;
	UINT  nLoginsMask;
	LPVOID  pLoginsData;
	CUIntArray  nAccessCodes;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	IODEVICELOGINSPROCEDURE  pLoginsProcedure;

	for (Lock(), nIndex = 0, nCount = (INT)m_szLogins.GetSize(), pLoginsProcedure = m_pIODeviceLoginsProcedure, pLoginsData = m_pOperationsLoginsData, nLoginsMask = m_nOperationsLoginsMask; nIndex < nCount; nIndex++)
	{
		if (!m_szLogins.GetAt(nIndex).CompareNoCase(pszClient) && m_tLogins.GetAt(nIndex) == tConnectTime) break;
		continue;
	}
	if (nIndex < nCount)
	{
		for (nClient = 0, nClients = (pLoginsProcedure != (IODEVICELOGINSPROCEDURE)NULL && (nLoginsMask & IODEVICE_LOGOUT_SUCCESS)) ? GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes) : 0, m_szLogins.RemoveAt(nIndex), m_tLogins.RemoveAt(nIndex), Unlock(); nClient < nClients; nClient++)
		{
			if ((((nPos = szClients.GetAt(nClient).Find(EOL)) >= 0 && !szClients.GetAt(nClient).Mid(nPos + 1).CompareNoCase(pszClient)) || !szClients.GetAt(nClient).CompareNoCase(pszClient)) || (szClients.GetAt(nClient).IsEmpty() && (nAccessCodes.GetAt(nClient) & IODEVICE_SECURITY_UNLIMITEDACCESS)))
			{
				(*pLoginsProcedure)(IODEVICE_LOGOUT_SUCCESS | ((nAccessCodes.GetAt(nClient) & IODEVICE_SECURITY_AUDITACCESS) ? IODEVICE_LOGINOUT_AUDIT : 0), pszClient, tConnectTime.GetTime(), pLoginsData);
				break;
			}
		}
		return TRUE;
	}
	Unlock();
	return FALSE;
}

BOOL CENERTECDevice::AuthorizeClient(LPCTSTR pszClient, BOOL bAudit)
{
	INT  nPos;
	INT  nIndex;
	INT  nCount;
	INT  nClient;
	INT  nClients;
	UINT  nAccessCode;
	CTimeKey  tAccessTime;
	CUIntArray  nAccessCodes;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nClient = 0, nClients = GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes); nClient < nClients; nClient++)
	{
		if ((nPos = szClients.GetAt(nClient).Find(EOL)) >= 0 && !szClients.GetAt(nClient).Mid(nPos + 1).CompareNoCase(pszClient))
		{
			if (((nAccessCode = nAccessCodes.GetAt(nClient)) & IODEVICE_SECURITY_DENIEDACCESS) || ((nAccessCode & IODEVICE_SECURITY_RESTRICTEDACCESS) && (tAccessTime < tStartTimes.GetAt(nClient) || tAccessTime > tStopTimes.GetAt(nClient))))
			{
				for (nIndex = 0, nCount = (bAudit) ? (INT)m_szLogins.GetSize() : 0; nIndex < nCount; nIndex++)
				{
					if (!m_szLogins.GetAt(nIndex).CompareNoCase(szClients.GetAt(nClient)))
					{
						m_szLogins.RemoveAt(nIndex);
						break;
					}
				}
				for (; m_pIODeviceLoginsProcedure != (IODEVICELOGINSPROCEDURE)NULL && (m_nOperationsLoginsMask & IODEVICE_LOGIN_FAILURE) && bAudit; )
				{
					(*m_pIODeviceLoginsProcedure)(IODEVICE_LOGIN_FAILURE | ((nAccessCode & IODEVICE_SECURITY_AUDITACCESS) ? IODEVICE_LOGINOUT_AUDIT : 0), szClients.GetAt(nClient), 0, m_pOperationsLoginsData);
					break;
				}
				return FALSE;
			}
			return TRUE;
		}
		if (szClients.GetAt(nClient).IsEmpty() && (nAccessCodes.GetAt(nClient) & IODEVICE_SECURITY_UNLIMITEDACCESS) && lstrlen(pszClient) > 0) return TRUE;
	}
	for (nIndex = 0, nCount = (bAudit) ? (INT)m_szLogins.GetSize() : 0; nIndex < nCount; nIndex++)
	{
		if (!m_szLogins.GetAt(nIndex).CompareNoCase(pszClient))
		{
			m_szLogins.RemoveAt(nIndex);
			break;
		}
	}
	for (; m_pIODeviceLoginsProcedure != (IODEVICELOGINSPROCEDURE)NULL && (m_nOperationsLoginsMask & IODEVICE_LOGIN_FAILURE) && lstrlen(pszClient) > 0 && bAudit; )
	{
		(*m_pIODeviceLoginsProcedure)(IODEVICE_LOGIN_FAILURE | IODEVICE_LOGINOUT_AUDIT, pszClient, 0, m_pOperationsLoginsData);
		break;
	}
	return FALSE;
}

VOID CENERTECDevice::AuthorizeAllClients(BOOL bAudit)
{
	INT  nPos;
	INT  nIndex;
	INT  nCount;
	CString  szClient;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nIndex = 0, nCount = (INT)m_szLogins.GetSize(); nIndex < nCount; nIndex++)
	{
		if ((nPos = (szClient = m_szLogins.GetAt(nIndex)).Find(EOL)) >= 0)
		{
			if (!AuthorizeClient(szClient.Mid(nPos + 1), bAudit) && !bAudit)
			{
				AbortConnection(m_szLogins.GetAt(nIndex), 0);
				continue;
			}
		}
	}
}

INT CENERTECDevice::AddData(CONST CByteArray &nData, BOOL bInData)
{
	INT  nID;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((m_nOperationsType & (IODEVICE_SERVICE_TM | IODEVICE_SERVICE_TC)) && (m_nOperationsType & IODEVICE_DATASERVICE_RAW))
	{
		if ((nID = (m_pIOThread) ? m_pIOThread->AddData(nData, bInData) : -1) >= 0)
		{
			if ((m_nOperationsType & IODEVICE_SERVICE_TM) && bInData) TrackData();
			return nID;
		}
	}
	return -1;
}
INT CENERTECDevice::AddData(CONST CTMUnit &cTMUnit, BOOL bInData)
{
	INT  nID;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((m_nOperationsType & IODEVICE_SERVICE_TM) && (m_nOperationsType & IODEVICE_DATASERVICE_SOURCEPACKETS))
	{
		if ((nID = (m_pIOThread) ? m_pIOThread->AddData(cTMUnit, bInData) : -1) >= 0)
		{
			if (bInData) TrackData();
			return nID;
		}
	}
	return -1;
}
INT CENERTECDevice::AddData(CONST CTMTransferUnit &cTMTransferUnit, BOOL bInData)
{
	INT  nID;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((m_nOperationsType & IODEVICE_SERVICE_TM) && (m_nOperationsType & IODEVICE_DATASERVICE_TRANSFERFRAMES))
	{
		if ((nID = (m_pIOThread) ? m_pIOThread->AddData(cTMTransferUnit, bInData) : -1) >= 0)
		{
			if (bInData) TrackData();
			return nID;
		}
	}
	return -1;
}
INT CENERTECDevice::AddData(CONST CTCUnit &cTCUnit, BOOL bInData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pIOThread != (CENERTECDeviceThread *)NULL && (m_nOperationsType & IODEVICE_SERVICE_TC) && (m_nOperationsType & IODEVICE_DATASERVICE_SOURCEPACKETS)) ? m_pIOThread->AddData(cTCUnit, bInData) : -1);
}
INT CENERTECDevice::AddData(CONST CTCTransferUnit &cTCTransferUnit, BOOL bInData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pIOThread != (CENERTECDeviceThread *)NULL && (m_nOperationsType & IODEVICE_SERVICE_TC) && (m_nOperationsType & IODEVICE_DATASERVICE_TRANSFERFRAMES)) ? m_pIOThread->AddData(cTCTransferUnit, bInData) : -1);
}

BOOL CENERTECDevice::RemoveData(CByteArray &nData, BOOL bInData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((m_nOperationsType & (IODEVICE_SERVICE_TM | IODEVICE_SERVICE_TC)) && (m_nOperationsType & IODEVICE_DATASERVICE_RAW))
	{
		if (m_pIOThread != (CENERTECDeviceThread *)NULL  &&  m_pIOThread->RemoveData(nData, bInData) >= 0)
		{
			if ((m_nOperationsType & IODEVICE_SERVICE_TM) && bInData) TrackData(CTimeTag());
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CENERTECDevice::RemoveData(CTMUnit &cTMUnit, BOOL bInData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((m_nOperationsType & IODEVICE_SERVICE_TM) && (m_nOperationsType & IODEVICE_DATASERVICE_SOURCEPACKETS))
	{
		if (m_pIOThread != (CENERTECDeviceThread *)NULL  &&  m_pIOThread->RemoveData(cTMUnit, bInData) >= 0)
		{
			if (bInData) TrackData(cTMUnit.GetTimeTag());
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CENERTECDevice::RemoveData(CTMTransferUnit &cTMTransferUnit, BOOL bInData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((m_nOperationsType & IODEVICE_SERVICE_TM) && (m_nOperationsType & IODEVICE_DATASERVICE_TRANSFERFRAMES))
	{
		if (m_pIOThread != (CENERTECDeviceThread *)NULL  &&  m_pIOThread->RemoveData(cTMTransferUnit, bInData) >= 0)
		{
			if (bInData) TrackData(cTMTransferUnit.GetTimeTag());
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CENERTECDevice::RemoveData(CTCUnit &cTCUnit, BOOL bInData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(m_pIOThread != (CENERTECDeviceThread *)NULL && (m_nOperationsType & IODEVICE_SERVICE_TC) && (m_nOperationsType & IODEVICE_DATASERVICE_SOURCEPACKETS) && m_pIOThread->RemoveData(cTCUnit, bInData) >= 0);
}
BOOL CENERTECDevice::RemoveData(CTCTransferUnit &cTCTransferUnit, BOOL bInData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(m_pIOThread != (CENERTECDeviceThread *)NULL && (m_nOperationsType & IODEVICE_SERVICE_TC) && (m_nOperationsType & IODEVICE_DATASERVICE_TRANSFERFRAMES) && m_pIOThread->RemoveData(cTCTransferUnit, bInData) >= 0);
}

BOOL CENERTECDevice::ClearData(BOOL bAll)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pIOThread != (CENERTECDeviceThread *)NULL && (((GetData()->nDeviceMode & IODEVICE_TYPE_SERVER) != IODEVICE_TYPE_SERVER  &&  !bAll) || m_pIOThread->ClearData(FALSE)) && (((GetData()->nDeviceMode & IODEVICE_TYPE_CLIENT) != IODEVICE_TYPE_CLIENT  &&  !bAll) || m_pIOThread->ClearData(TRUE))));
}

BOOL CENERTECDevice::UpdateStatus(WORD wStatus)
{
	if (m_wIODataStatus != wStatus)
	{
		m_wIODataStatus = wStatus;
		TranslateStatus(m_szIODeviceStatus, m_nIODeviceStatus);
		return TRUE;
	}
	return FALSE;
}
BOOL CENERTECDevice::UpdateStatus(BYTE nDataQuality, BYTE nSequenceQuality)
{
	WORD  wStatus;

	wStatus = nDataQuality;
	wStatus |= (nSequenceQuality != PFLP_SEQUENCE_CORRECT  &&  nSequenceQuality != PFLP_SEQUENCE_ERROR) ? ENERTECDEVICE_SEQUENCEQUALITY_NONE : 0;
	wStatus |= (nSequenceQuality == PFLP_SEQUENCE_CORRECT) ? ENERTECDEVICE_SEQUENCEQUALITY_GOOD : 0;
	wStatus |= (nSequenceQuality == PFLP_SEQUENCE_ERROR) ? ENERTECDEVICE_SEQUENCEQUALITY_BAD : 0;
	return UpdateStatus(wStatus);
}

BOOL CENERTECDevice::TranslateStatus(CString &szStatus, UINT &nStatus) CONST
{
	BOOL  bStatus;

	for (bStatus = (m_wIODataStatus & ENERTECDEVICE_PMDEMODULATOR_LOCKED) ? TRUE : FALSE, bStatus &= (m_wIODataStatus & ENERTECDEVICE_PSKDEMODULATOR_LOCKED) ? TRUE : FALSE, bStatus &= (m_wIODataStatus & ENERTECDEVICE_BITSYNCHRONIZER_LOCKED) ? TRUE : FALSE, bStatus &= ((m_wIODataStatus & (ENERTECDEVICE_FRAMESYNCHRONIZER_SEARCH | ENERTECDEVICE_FRAMESYNCHRONIZER_CONTROL | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED)) == ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED) ? TRUE : FALSE, bStatus &= ((m_wIODataStatus & (ENERTECDEVICE_REEDCRC_CRCERRORS | ENERTECDEVICE_REEDCRC_REEDERRORS | ENERTECDEVICE_REEDCRC_NOERRORS | ENERTECDEVICE_REEDCRC_CORRERRORS)) != ENERTECDEVICE_REEDCRC_CRCERRORS) ? TRUE : FALSE, bStatus &= ((m_wIODataStatus & (ENERTECDEVICE_REEDCRC_CRCERRORS | ENERTECDEVICE_REEDCRC_REEDERRORS | ENERTECDEVICE_REEDCRC_NOERRORS | ENERTECDEVICE_REEDCRC_CORRERRORS)) != ENERTECDEVICE_REEDCRC_REEDERRORS) ? TRUE : FALSE, bStatus &= (m_wIODataStatus & ENERTECDEVICE_SEQUENCEQUALITY_GOOD) ? TRUE : FALSE, nStatus = m_nIODeviceStatus & (IODEVICE_STATUS_ONLINE | IODEVICE_STATUS_OFFLINE); !m_wIODataStatus; )
	{
		szStatus = STRING(IDS_ENERTECDEVICE_STATUS_NOTREADY);
		nStatus |= IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED;
		return bStatus;
	}
	if (m_wIODataStatus & ENERTECDEVICE_SEQUENCEQUALITY_NONE)
	{
		szStatus = (nStatus & IODEVICE_STATUS_ONLINE) ? STRING(IDS_ENERTECDEVICE_STATUS_READY) : STRING(IDS_ENERTECDEVICE_STATUS_OFFLINE);
		nStatus |= IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED;
		return bStatus;
	}
	if ((m_wIODataStatus & ENERTECDEVICE_PMDEMODULATOR_LOCKED) != ENERTECDEVICE_PMDEMODULATOR_LOCKED)
	{
		szStatus = (nStatus & IODEVICE_STATUS_ONLINE) ? STRING(IDS_ENERTECDEVICE_STATUS_PMDEMODULATOR_FAILURE) : STRING(IDS_ENERTECDEVICE_STATUS_OFFLINE);
		nStatus |= IODEVICE_STATUS_ERROR | IODEVICE_STATUS_CONNECTED;
		return bStatus;
	}
	if ((m_wIODataStatus & ENERTECDEVICE_PSKDEMODULATOR_LOCKED) != ENERTECDEVICE_PSKDEMODULATOR_LOCKED)
	{
		szStatus = (nStatus & IODEVICE_STATUS_ONLINE) ? STRING(IDS_ENERTECDEVICE_STATUS_PSKDEMODULATOR_FAILURE) : STRING(IDS_ENERTECDEVICE_STATUS_OFFLINE);
		nStatus |= IODEVICE_STATUS_ERROR | IODEVICE_STATUS_CONNECTED;
		return bStatus;
	}
	if ((m_wIODataStatus & ENERTECDEVICE_BITSYNCHRONIZER_LOCKED) != ENERTECDEVICE_BITSYNCHRONIZER_LOCKED)
	{
		szStatus = (nStatus & IODEVICE_STATUS_ONLINE) ? STRING(IDS_ENERTECDEVICE_STATUS_BITSYNCHRONIZER_FAILURE) : STRING(IDS_ENERTECDEVICE_STATUS_OFFLINE);
		nStatus |= IODEVICE_STATUS_ERROR | IODEVICE_STATUS_CONNECTED;
		return bStatus;
	}
	if ((m_wIODataStatus & (ENERTECDEVICE_FRAMESYNCHRONIZER_SEARCH | ENERTECDEVICE_FRAMESYNCHRONIZER_CONTROL | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED)) == ENERTECDEVICE_FRAMESYNCHRONIZER_SEARCH)
	{
		szStatus = (nStatus & IODEVICE_STATUS_ONLINE) ? STRING(IDS_ENERTECDEVICE_STATUS_FRAMESYNCHRONIZER_SEARCH) : STRING(IDS_ENERTECDEVICE_STATUS_OFFLINE);
		nStatus |= IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED;
		return bStatus;
	}
	if ((m_wIODataStatus & (ENERTECDEVICE_FRAMESYNCHRONIZER_SEARCH | ENERTECDEVICE_FRAMESYNCHRONIZER_CONTROL | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED)) == ENERTECDEVICE_FRAMESYNCHRONIZER_CONTROL)
	{
		szStatus = (nStatus & IODEVICE_STATUS_ONLINE) ? STRING(IDS_ENERTECDEVICE_STATUS_FRAMESYNCHRONIZER_CONTROL) : STRING(IDS_ENERTECDEVICE_STATUS_OFFLINE);
		nStatus |= IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED;
		return bStatus;
	}
	if ((m_wIODataStatus & (ENERTECDEVICE_FRAMESYNCHRONIZER_SEARCH | ENERTECDEVICE_FRAMESYNCHRONIZER_CONTROL | ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED)) == ENERTECDEVICE_FRAMESYNCHRONIZER_LOCKED)
	{
		if ((m_wIODataStatus & (ENERTECDEVICE_REEDCRC_CRCERRORS | ENERTECDEVICE_REEDCRC_REEDERRORS | ENERTECDEVICE_REEDCRC_NOERRORS | ENERTECDEVICE_REEDCRC_CORRERRORS)) != ENERTECDEVICE_REEDCRC_CRCERRORS && (m_wIODataStatus & (ENERTECDEVICE_REEDCRC_CRCERRORS | ENERTECDEVICE_REEDCRC_REEDERRORS | ENERTECDEVICE_REEDCRC_NOERRORS | ENERTECDEVICE_REEDCRC_CORRERRORS)) != ENERTECDEVICE_REEDCRC_REEDERRORS)
		{
			if ((m_wIODataStatus & ENERTECDEVICE_SEQUENCEQUALITY_GOOD) == ENERTECDEVICE_SEQUENCEQUALITY_GOOD)
			{
				szStatus = STRING(IDS_ENERTECDEVICE_STATUS_FRAMESYNCHRONIZER_LOCKED);
				nStatus |= IODEVICE_STATUS_GOOD | IODEVICE_STATUS_CONNECTED;
				return bStatus;
			}
			szStatus = STRING(IDS_ENERTECDEVICE_STATUS_SEQUENCE_FAILURE);
			nStatus |= IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED;
			return bStatus;
		}
		szStatus = STRING(IDS_ENERTECDEVICE_STATUS_GENERAL_ERROR);
		nStatus |= IODEVICE_STATUS_ERROR | IODEVICE_STATUS_CONNECTED;
		return bStatus;
	}
	szStatus = STRING(IDS_ENERTECDEVICE_STATUS_FAILURE);
	nStatus |= IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED;
	return FALSE;
}
BOOL CENERTECDevice::TranslateStatus(CString &szStatus) CONST
{
	UINT  nPort;
	UINT  nBufferSize;
	CString  szAddress;
	CTimeSpan  tTimeout;

	for (szStatus.Empty(); !GetDeviceName().IsEmpty() && GetIPAddress(szAddress, nPort) && GetBufferSize(nBufferSize) && GetTimeout(tTimeout); )
	{
		szStatus.Format(STRING(IDS_ENERTECDEVICE_DETAILS_FORMAT), (LPCTSTR)GetDeviceName(), (LPCTSTR)GetDeviceBrand(), (LPCTSTR)szAddress, nPort, nBufferSize / 1024, tTimeout.GetTotalSeconds());
		return TRUE;
	}
	return FALSE;
}

BOOL CENERTECDevice::UpdateDataStatus(INT nDataID, UINT nStatus, BOOL bSuccess)
{
	if (m_pIODeviceDataStatusProcedure)
	{
		(*m_pIODeviceDataStatusProcedure)(nDataID, nStatus, bSuccess);
		return TRUE;
	}
	return FALSE;
}

VOID CENERTECDevice::AllocateData()
{
	m_nIODeviceData.SetSize(sizeof(DATA));
}

VOID CENERTECDevice::FreeData()
{
	INT  nDevice;
	INT  nDevices;

	for (nDevice = 0, nDevices = (INT)m_pIODevices.GetSize(); nDevice < nDevices; nDevice++)
	{
		if (m_pIODevices.GetAt(nDevice) == (LPVOID) this)
		{
			m_nIODeviceTimerIDs.RemoveAt(nDevice);
			m_pIODevices.RemoveAt(nDevice);
			break;
		}
	}
	m_nIODeviceData.RemoveAll();
}

VOID CENERTECDevice::TrackData()
{
	INT  nDevice;
	INT  nDevices;
	WORD  wFilter[2];
	CTimeKey  tTime;

	if (!GetVCIDFilter(wFilter[0]) && !GetAPIDFilter(wFilter[1]))
	{
		for (nDevice = 0, nDevices = (INT)m_pIODevices.GetSize(); nDevice < nDevices; nDevice++)
		{
			if (m_pIODevices.GetAt(nDevice) == (LPVOID) this)
			{
				KillTimer((HWND)NULL, (UINT_PTR)m_nIODeviceTimerIDs.GetAt(nDevice));
				m_nIODeviceTimerIDs.RemoveAt(nDevice);
				m_pIODevices.RemoveAt(nDevice);
				break;
			}
		}
		if (m_tOperationsDataDrop[1] > 0)
		{
			m_nIODeviceTimerIDs.Add((LPVOID)SetTimer((HWND)NULL, (UINT_PTR)NULL, (DWORD)(1000 * m_tOperationsDataDrop[1].GetTotalSeconds()), TrackDataDropProcedure));
			m_pIODevices.Add(this);
		}
	}
	if (m_tIODataDrop > 0)
	{
		if (m_pIODeviceDataStreamProcedure != (IODEVICEDATASTREAMPROCEDURE)NULL && (m_nOperationsDataStreamMask & IODEVICE_DATASTREAM_RECONNECTED)) (*m_pIODeviceDataStreamProcedure)(IODEVICE_DATASTREAM_RECONNECTED, max(tTime.GetTime() - m_tIODataDrop.GetTime(), 0), m_pOperationsDataStreamData);
		m_tIODataDrop = 0;
	}
}
VOID CENERTECDevice::TrackData(CONST CTimeTag &tLastIOData)
{
	CTimeKey  tTime;

	if (tTime.GetTime() - tLastIOData.GetTime() >= m_tOperationsDataDelay[1].GetTotalSeconds())
	{
		if (m_pIODeviceDataStreamProcedure != (IODEVICEDATASTREAMPROCEDURE)NULL && (m_nOperationsDataStreamMask & IODEVICE_DATASTREAM_DELAYED) && !m_bDelayedIOData) (*m_pIODeviceDataStreamProcedure)(IODEVICE_DATASTREAM_DELAYED, tTime.GetTime() - tLastIOData.GetTime(), m_pOperationsDataStreamData);
		m_bDelayedIOData = TRUE;
		return;
	}
	if (m_pIODeviceDataStreamProcedure != (IODEVICEDATASTREAMPROCEDURE)NULL && (m_nOperationsDataStreamMask & IODEVICE_DATASTREAM_BACKINTIME) && m_bDelayedIOData) (*m_pIODeviceDataStreamProcedure)(IODEVICE_DATASTREAM_BACKINTIME, max(tTime.GetTime() - tLastIOData.GetTime(), 0), m_pOperationsDataStreamData);
	m_bDelayedIOData = FALSE;
}

CENERTECDevice::LPDATA CENERTECDevice::GetData() CONST
{
	return((LPDATA)(LPCVOID)m_nIODeviceData.GetData());
}

BOOL CENERTECDevice::Start()
{
	if ((m_pIOThread = (!GetDeviceName().IsEmpty() && !m_pIOThread) ? new CENERTECDeviceThread : (CENERTECDeviceThread *)NULL))
	{
		if (m_pIOThread->Start(this)) return TRUE;
		delete m_pIOThread;
	}
	m_pIOThread = (CENERTECDeviceThread *)NULL;
	return FALSE;
}

BOOL CENERTECDevice::Suspend()
{
	return((m_pIOThread) ? m_pIOThread->Suspend() : FALSE);
}

BOOL CENERTECDevice::IsSuspended() CONST
{
	return((m_pIOThread) ? m_pIOThread->IsSuspended() : FALSE);
}

BOOL CENERTECDevice::Resume()
{
	if (IsSuspended())
	{
		Clear(TRUE);
		return m_pIOThread->Resume();
	}
	return FALSE;
}

BOOL CENERTECDevice::Stop()
{
	if (m_pIOThread)
	{
		for (Clear(); IsSuspended(); )
		{
			Resume();
			continue;
		}
		m_pIOThread->Stop();
		delete m_pIOThread;
		m_pIOThread = (CENERTECDeviceThread *)NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CENERTECDevice::Initialize(UINT nFlags)
{
	LPDATA  pDeviceData;

	if ((pDeviceData = GetData()))
	{
		pDeviceData->nDeviceMode = m_nOperationsType = nFlags;
		return TRUE;
	}
	return FALSE;
}
BOOL CENERTECDevice::Initialize(UINT nFlags, CONST CTimeSpan &tDataDrop, CONST CTimeSpan &tDataDelay, IODEVICESTATUSPROCEDURE pStatusProcedure, IODEVICEDATASTATUSPROCEDURE pDataStatusProcedure, IODEVICEMESSAGEPROCEDURE pMessageProcedure)
{
	BOOL  bInit;
	CHAR  szNode[256];
	CHAR  szService[16];
	LPDATA  pDeviceData;
	CStringTools  cStringTools;
	struct addrinfo  *pIPAddressInfo[3];

	for (bInit = FALSE; !m_nIODeviceData.GetSize(); )
	{
		for (AllocateData(); (pDeviceData = GetData()); )
		{
			pDeviceData->nDeviceID = ENERTECDEVICE_DEFAULTID;
			pDeviceData->tTimeout = ENERTECDEVICE_DEFAULTTIMEOUT;
			pDeviceData->nBufferSize = 1024 * ENERTECDEVICE_DEFAULTBUFFER;
			pDeviceData->wDataFilter[0] = pDeviceData->wDataFilter[1] = (WORD)-1;
			pDeviceData->tEpochTime.wYear = ENERTECDEVICE_DEFAULTEPOCHYEAR;
			pDeviceData->tEpochTime.wMonth = January;
			pDeviceData->tEpochTime.wDay = 1;
			pDeviceData->tEpochTime.wDayOfWeek = 0;
			pDeviceData->tEpochTime.wHour = pDeviceData->tEpochTime.wMinute = pDeviceData->tEpochTime.wSecond = pDeviceData->tEpochTime.wMilliseconds = 0;
			pDeviceData->tClockAdjustment = (nFlags & IODEVICE_TYPE_CLIENT) ? (SECONDSPERMINUTE*ENERTECDEVICE_DEFAULTCLOCKADJUSTMENTINTERVAL) : 0;
			pDeviceData->tCorrelationError = pDeviceData->tCorrelationDelta = 0;
			pDeviceData->tStatusMessageInterval = 0;
			bInit = TRUE;
			break;
		}
		break;
	}
	if ((pDeviceData = GetData()))
	{
		for (pDeviceData->nDeviceMode = m_nOperationsType = nFlags, m_tOperationsDataDrop[0] = tDataDrop, m_tOperationsDataDelay[0] = tDataDelay, m_pIODeviceStatusProcedure = pStatusProcedure, m_pIODeviceDataStatusProcedure = pDataStatusProcedure, m_pIODeviceMessageProcedure = pMessageProcedure, m_tIODataDrop = 0, m_bDelayedIOData = FALSE, m_szIODeviceStatus = STRING(IDS_ENERTECDEVICE_STATUS_NOTREADY), m_nIODeviceStatus = IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_ONLINE, m_wIODataStatus = ENERTECDEVICE_DATAQUALITY_NONE; (pIPAddressInfo[0] = (struct addrinfo *) GlobalAlloc(GPTR, sizeof(struct addrinfo))); )
		{
			if (bInit)
			{
#ifndef UNICODE
				strcpy_s(szNode, sizeof(szNode) / sizeof(CHAR), STRING(IDS_DEVICEPROTOCOL_LOCALHOSTNAME));
				strcpy_s(szService, sizeof(szService) / sizeof(CHAR), cStringTools.ConvertUIntToString(ENERTECDEVICE_DEFAULTPORT));
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_DEVICEPROTOCOL_LOCALHOSTNAME), -1, szNode, sizeof(szNode) / sizeof(CHAR), (LPCSTR)NULL, (LPBOOL)NULL);
				WideCharToMultiByte(CP_ACP, 0, cStringTools.ConvertUIntToString(ENERTECDEVICE_DEFAULTPORT), -1, szService, sizeof(szService) / sizeof(CHAR), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
				for (SetIPAddress(STRING(IDS_DEVICEPROTOCOL_LOCALHOSTADDRESS), ENERTECDEVICE_DEFAULTPORT), pIPAddressInfo[0]->ai_family = AF_INET, pIPAddressInfo[0]->ai_socktype = SOCK_STREAM, pIPAddressInfo[0]->ai_protocol = IPPROTO_TCP; !getaddrinfo(szNode, szService, pIPAddressInfo[0], &pIPAddressInfo[1]); )
				{
					for (pIPAddressInfo[2] = pIPAddressInfo[1]; pIPAddressInfo[2] != (struct addrinfo *) NULL; pIPAddressInfo[2] = pIPAddressInfo[2]->ai_next)
					{
						if (pIPAddressInfo[2]->ai_family == pIPAddressInfo[0]->ai_family  &&  pIPAddressInfo[2]->ai_socktype == pIPAddressInfo[0]->ai_socktype  &&  pIPAddressInfo[2]->ai_protocol == pIPAddressInfo[0]->ai_protocol)
						{
							GetData()->sIPAddress.sin_addr = ((sockaddr_in *)pIPAddressInfo[2]->ai_addr)->sin_addr;
							GetData()->sIPAddress.sin_family = pIPAddressInfo[2]->ai_family;
							GetData()->sIPAddress.sin_port = ENERTECDEVICE_DEFAULTPORT;
							break;
						}
					}
					freeaddrinfo(pIPAddressInfo[1]);
					break;
				}
				GlobalFree(pIPAddressInfo[0]);
			}
			return(((nFlags & (IODEVICE_TYPE_SERVER | IODEVICE_TYPE_CLIENT)) != 0 && (nFlags & (IODEVICE_TYPE_SERVER | IODEVICE_TYPE_CLIENT)) != (IODEVICE_TYPE_SERVER | IODEVICE_TYPE_CLIENT) && (nFlags & (IODEVICE_SERVICE_TM | IODEVICE_SERVICE_TC)) != 0 && (nFlags & (IODEVICE_SERVICE_TM | IODEVICE_SERVICE_TC)) != (IODEVICE_SERVICE_TM | IODEVICE_SERVICE_TC) && (GetCapabilities() & nFlags) == nFlags) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CENERTECDevice::Configure(CWnd *pParentWnd, UINT nAllowedTypes, BOOL bReadOnly)
{
	BOOL  bRestart;
	CENERTECDevice  cDevice;
	CENERTECDeviceDialog  cDeviceDialog(pParentWnd);

	for (cDevice.Copy(this), bRestart = FALSE; cDeviceDialog.DoModal(&cDevice, nAllowedTypes, bReadOnly) == IDOK; ) return Update(&cDevice, bRestart);
	return FALSE;
}

BOOL CENERTECDevice::Update(CONST CIODevice *pDevice, BOOL &bRestart)
{
	BOOL  bDevice[2];
	CENERTECDevice  *pENERTECDevice;

	if ((pENERTECDevice = (CENERTECDevice *)pDevice))
	{
		if (pENERTECDevice->GetDeviceBrand() != GetDeviceBrand() || pENERTECDevice->GetDeviceName() != GetDeviceName() || pENERTECDevice->GetData()->nDeviceMode != GetData()->nDeviceMode || memcmp(&pENERTECDevice->GetData()->sIPAddress, &GetData()->sIPAddress, sizeof(SOCKADDR_IN)) != 0 || (pDevice->GetStatusIndication() & IODEVICE_STATUS_CLOSED))
		{
			for (bDevice[0] = Stop(), bDevice[1] = IsOpen(), Close(); Copy(pDevice); )
			{
				for (m_szLogins.RemoveAll(); pDevice->GetStatusIndication() & IODEVICE_STATUS_CLOSED; )
				{
					SetStatusIndication(GetStatusIndication() & ~IODEVICE_STATUS_CLOSED);
					return TRUE;
				}
				if (!bRestart)
				{
					bRestart = bDevice[0] || bDevice[1];
					return TRUE;
				}
				if (!bDevice[0] || (Open() && (!bDevice[1] || Start())))
				{
					bRestart = FALSE;
					return TRUE;
				}
				break;
			}
			m_szLogins.RemoveAll();
			return FALSE;
		}
		if (Copy(pDevice))
		{
			AuthorizeAllClients(FALSE);
			return TRUE;
		}
	}
	return FALSE;
}

INT CENERTECDevice::Send(CONST CByteArray &nData)
{
	return AddData(nData, FALSE);
}
INT CENERTECDevice::Send(CONST CTMUnit &cTMUnit)
{
	return AddData(cTMUnit, FALSE);
}
INT CENERTECDevice::Send(CONST CTMTransferUnit &cTMTransferUnit)
{
	return AddData(cTMTransferUnit, FALSE);
}
INT CENERTECDevice::Send(CONST CTCUnit &cTCUnit)
{
	return AddData(cTCUnit, FALSE);
}
INT CENERTECDevice::Send(CONST CTCTransferUnit &cTCTransferUnit)
{
	return AddData(cTCTransferUnit, FALSE);
}

BOOL CENERTECDevice::Receive(CByteArray &nData)
{
	return RemoveData(nData);
}
BOOL CENERTECDevice::Receive(CTMUnit &cTMUnit)
{
	return RemoveData(cTMUnit);
}
BOOL CENERTECDevice::Receive(CTMTransferUnit &cTMTransferUnit)
{
	return RemoveData(cTMTransferUnit);
}
BOOL CENERTECDevice::Receive(CTCUnit &cTCUnit)
{
	return RemoveData(cTCUnit);
}
BOOL CENERTECDevice::Receive(CTCTransferUnit &cTCTransferUnit)
{
	return RemoveData(cTCTransferUnit);
}

BOOL CENERTECDevice::Clear(BOOL bAll)
{
	return ClearData(bAll);
}

BOOL CENERTECDevice::SetStatus(LPCTSTR pszStatus)
{
	m_szIODeviceStatus = pszStatus;
	return TRUE;
}

CString CENERTECDevice::GetStatus() CONST
{
	UINT  nStatus;
	CString  szStatus;

	TranslateStatus(szStatus, nStatus);
	return szStatus;
}

BOOL CENERTECDevice::SetStatusIndication(UINT nStatus)
{
	m_nIODeviceStatus = nStatus;
	return TRUE;
}

UINT CENERTECDevice::GetStatusIndication() CONST
{
	UINT  nStatus;
	CString  szStatus;

	TranslateStatus(szStatus, nStatus);
	return nStatus;
}

UINT CENERTECDevice::GetCapabilities() CONST
{
	return((GetDeviceBrand() == STRING(IDS_DEVICE_BRANDNAME)) ? (IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_DATASERVICE_TRANSFERFRAMES | IODEVICE_PROTOCOL_PFLP) : (IODEVICE_TYPE_SERVER | IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_DATASERVICE_TRANSFERFRAMES | IODEVICE_PROTOCOL_PFLP));
}

CString CENERTECDevice::GetDetails() CONST
{
	CString  szStatus;

	return((TranslateStatus(szStatus)) ? szStatus : EMPTYSTRING);
}

INT CENERTECDevice::EnumConnections(CStringArray &szComputers) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pIOThread) ? m_pIOThread->EnumConnections(szComputers) : 0);
}
INT CENERTECDevice::EnumConnections(CStringArray &szComputers, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pIOThread) ? m_pIOThread->EnumConnections(szComputers, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes) : 0);
}

BOOL CENERTECDevice::AbortConnection(LPCTSTR pszComputer, CONST CTimeTag &tConnectTime)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pIOThread) ? m_pIOThread->AbortConnection(pszComputer, tConnectTime) : FALSE);
}

BOOL CENERTECDevice::IsLocal() CONST
{
	UINT  nPort;
	DWORD  cbAddress;
	CString  szAddress[2];
	PADDRINFOT  pAddressInfo;
	CStringTools  cStringTools;
	CComputerToken  cComputerToken;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetIPAddress(szAddress[0], nPort) && GetAddrInfo(cComputerToken.GetComputerName(), cStringTools.ConvertUIntToString(nPort), (const ADDRINFOT *)NULL, &pAddressInfo) == NO_ERROR)
	{
		if (!szAddress[0].Compare(STRING(IDS_DEVICEPROTOCOL_LOCALHOSTADDRESS)))
		{
			return TRUE;
		}
		do
		{
			if (pAddressInfo->ai_family == AF_INET)
			{
				if (!WSAAddressToString(pAddressInfo->ai_addr, (DWORD)pAddressInfo->ai_addrlen, (LPWSAPROTOCOL_INFO)NULL, szAddress[1].GetBufferSetLength((INT)(pAddressInfo->ai_addrlen + cStringTools.ConvertUIntToString(nPort).GetLength() + 1)), &(cbAddress = (DWORD)(pAddressInfo->ai_addrlen + cStringTools.ConvertUIntToString(nPort).GetLength() + 1))))
				{
					for (szAddress[1].ReleaseBuffer(); szAddress[0].GetLength() + cStringTools.ConvertUIntToString(nPort).GetLength() == szAddress[1].GetLength() - 1 && !szAddress[1].Left(szAddress[0].GetLength()).Compare(szAddress[0]); ) return TRUE;
					continue;
				}
			}
		} while ((pAddressInfo = pAddressInfo->ai_next));
	}
	return FALSE;
}

BOOL CENERTECDevice::Copy(CONST CIODevice *pDevice)
{
	CENERTECDevice  *pENERTECDevice;

	if ((pENERTECDevice = (CENERTECDevice *)pDevice)) m_wIODataStatus = pENERTECDevice->m_wIODataStatus;
	return((CIODevice::Copy(pDevice)) ? (!m_pIOThread || m_pIOThread->Configure(pENERTECDevice)) : FALSE);
}

BOOL CENERTECDevice::Compare(CONST CIODevice *pDevice) CONST
{
	CENERTECDevice  *pENERTECDevice;

	return(((pENERTECDevice = (CENERTECDevice *)pDevice) && pENERTECDevice->m_wIODataStatus == m_wIODataStatus) ? CIODevice::Compare(pDevice) : CIODevice::Compare(pDevice));
}

VOID CALLBACK CENERTECDevice::TrackDataDropProcedure(HWND hWnd, UINT nMsg, UINT_PTR nEventID, DWORD dwTime)
{
	INT  nDevice;
	INT  nDevices;
	CENERTECDevice  *pENERTECDevice;

	for (nDevice = 0, nDevices = (INT)m_nIODeviceTimerIDs.GetSize(); nDevice < nDevices; nDevice++)
	{
		if (m_nIODeviceTimerIDs.GetAt(nDevice) == (LPVOID)nEventID) break;
		continue;
	}
	if ((pENERTECDevice = (nDevice < nDevices) ? (CENERTECDevice *)m_pIODevices.GetAt(nDevice) : (CENERTECDevice *)NULL))
	{
		for (KillTimer((HWND)NULL, (UINT_PTR)m_nIODeviceTimerIDs.GetAt(nDevice)); pENERTECDevice->m_pIODeviceDataStreamProcedure != (IODEVICEDATASTREAMPROCEDURE)NULL && (pENERTECDevice->m_nOperationsDataStreamMask & IODEVICE_DATASTREAM_DROP); )
		{
			(*pENERTECDevice->m_pIODeviceDataStreamProcedure)(IODEVICE_DATASTREAM_DROP, pENERTECDevice->m_tOperationsDataDrop[1].GetTotalSeconds(), pENERTECDevice->m_pOperationsDataStreamData);
			break;
		}
		pENERTECDevice->m_tIODataDrop = CTime::GetCurrentTime().GetTime();
		m_nIODeviceTimerIDs.RemoveAt(nDevice);
		m_pIODevices.RemoveAt(nDevice);
	}
}
