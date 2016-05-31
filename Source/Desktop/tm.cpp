// TM.CPP : Telemetry Data Processing Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telemetry data
// processing related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/22 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAutomationClientInfo

CAutomationClientInfo::CAutomationClientInfo() : CObject()
{
	m_bEncryption = FALSE;
	m_bBanned = FALSE;
}

VOID CAutomationClientInfo::SetUserName(LPCTSTR pszName)
{
	m_szUserName = pszName;
}

CString CAutomationClientInfo::GetUserName() CONST
{
	return m_szUserName;
}

VOID CAutomationClientInfo::SetPassword(LPCTSTR pszPassword)
{
	m_szPassword = pszPassword;
}

CString CAutomationClientInfo::GetPassword() CONST
{
	return m_szPassword;
}

VOID CAutomationClientInfo::SetPermissions(CONST CUIntArray &nPermissions)
{
	m_nPermissions.Copy(nPermissions);
}

INT CAutomationClientInfo::GetPermissions(CUIntArray &nPermissions) CONST
{
	nPermissions.Copy(m_nPermissions);
	return((INT)nPermissions.GetSize());
}

BOOL CAutomationClientInfo::HasPermission(LPCTSTR pszPermission) CONST
{
	INT  nPermission;
	INT  nPermissions;

	for (nPermission = 0, nPermissions = (INT)m_nPermissions.GetSize(); nPermission < nPermissions; nPermission++)
	{
		if (!_tcscmp(pszPermission, STRING(MINAUTOMATIONSERVICEPERMISSION + m_nPermissions.GetAt(nPermission)))) break;
		continue;
	}
	return((nPermission < nPermissions) ? TRUE : FALSE);
}

VOID CAutomationClientInfo::Encrypt(BOOL bEnable)
{
	m_bEncryption = bEnable;
}

BOOL CAutomationClientInfo::UsesEncryption() CONST
{
	return m_bEncryption;
}

VOID CAutomationClientInfo::Ban(BOOL bBan)
{
	m_bBanned = bBan;
}

BOOL CAutomationClientInfo::IsBanned() CONST
{
	return m_bBanned;
}

VOID CAutomationClientInfo::Copy(CONST CAutomationClientInfo *pClientInfo)
{
	m_szUserName = pClientInfo->m_szUserName;
	m_szPassword = pClientInfo->m_szPassword;
	m_bEncryption = pClientInfo->m_bEncryption;
	m_bBanned = pClientInfo->m_bBanned;
	m_nPermissions.Copy(pClientInfo->m_nPermissions);
}

BOOL CAutomationClientInfo::Compare(CONST CAutomationClientInfo *pClientInfo) CONST
{
	INT  nPermission[2];
	INT  nPermissions[2];

	for (nPermission[0] = 0, nPermissions[0] = (!pClientInfo->m_szUserName.CompareNoCase(m_szUserName) && !pClientInfo->m_szPassword.Compare(m_szPassword) && pClientInfo->m_bEncryption == m_bEncryption && pClientInfo->m_bBanned == m_bBanned && pClientInfo->m_nPermissions.GetSize() == m_nPermissions.GetSize()) ? (INT)pClientInfo->m_nPermissions.GetSize() : -1; nPermission[0] < nPermissions[0]; nPermission[0]++)
	{
		for (nPermission[1] = 0, nPermissions[1] = nPermissions[0]; nPermission[1] < nPermissions[1]; nPermission[1]++)
		{
			if (pClientInfo->m_nPermissions.GetAt(nPermission[0]) == m_nPermissions.GetAt(nPermission[1])) break;
			continue;
		}
		if (nPermission[1] == nPermissions[1]) break;
	}
	return((nPermission[0] == nPermissions[0]) ? TRUE : FALSE);
}

BOOL CAutomationClientInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;

	sData.cbUserName = (m_szUserName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbPassword = (m_szPassword.GetLength() + 1)*sizeof(TCHAR);
	sData.cbPermissions = (INT)(m_nPermissions.GetSize()*sizeof(UINT));
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbUserName + sData.cbPassword + sData.cbPermissions, sData.bEncryption = m_bEncryption, sData.bBanned = m_bBanned)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szUserName, sData.cbUserName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbUserName), (LPCTSTR)m_szPassword, sData.cbPassword);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbPassword), m_nPermissions.GetData(), sData.cbPermissions);
		return TRUE;
	}
	return FALSE;
}

BOOL CAutomationClientInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbUserName + sData.cbPassword + sData.cbPermissions && sData.cbUserName > 0 && sData.cbPassword > 0 && sData.cbPermissions >= 0; )
	{
		for (m_nPermissions.SetSize(sData.cbPermissions / sizeof(UINT)); m_nPermissions.GetSize() == sData.cbPermissions / sizeof(UINT); )
		{
			CopyMemory(m_szUserName.GetBufferSetLength(STRINGCHARS(sData.cbUserName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbUserName));
			CopyMemory(m_szPassword.GetBufferSetLength(STRINGCHARS(sData.cbPassword)), nInfo.GetData() + (cbData = cbData + sData.cbUserName), STRINGBYTES(sData.cbPassword));
			CopyMemory(m_nPermissions.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbPassword), sData.cbPermissions);
			m_bEncryption = sData.bEncryption;
			m_bBanned = sData.bBanned;
			m_szUserName.ReleaseBuffer();
			m_szPassword.ReleaseBuffer();
			return TRUE;
		}
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CAutomationClients

CAutomationClients::CAutomationClients() : CPtrArray()
{
	return;
}

CAutomationClients::~CAutomationClients()
{
	RemoveAll();
}

INT CAutomationClients::Add(CAutomationClientInfo *pClientInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pClientInfo->GetUserName(), TRUE)) >= 0) InsertAt(nIndex, pClientInfo, 1);
	return nIndex;
}

INT CAutomationClients::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CAutomationClientInfo *CAutomationClients::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAutomationClientInfo *)CPtrArray::GetAt(nIndex) : (CAutomationClientInfo *)NULL);
}

CAutomationClientInfo *CAutomationClients::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAutomationClientInfo *)CPtrArray::GetAt(nIndex) : (CAutomationClientInfo *)NULL);
}

VOID CAutomationClients::RemoveAll()
{
	INT  nClient;
	INT  nClients;
	CAutomationClientInfo  *pClientInfo;

	for (nClient = 0, nClients = (INT)GetSize(); nClient < nClients; nClient++)
	{
		if ((pClientInfo = GetAt(nClient))) delete pClientInfo;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CAutomationClients::Copy(CONST CAutomationClients *pClients)
{
	INT  nClient;
	INT  nClients;
	CAutomationClientInfo  *pClientInfo;

	for (nClient = 0, nClients = (INT)pClients->GetSize(), RemoveAll(); nClient < nClients; nClient++)
	{
		if ((pClientInfo = new CAutomationClientInfo))
		{
			pClientInfo->Copy(pClients->GetAt(nClient));
			InsertAt(nClient, pClientInfo, 1);
			continue;
		}
		break;
	}
	return((nClient == nClients) ? TRUE : FALSE);
}

BOOL CAutomationClients::Compare(CONST CAutomationClients *pClients) CONST
{
	INT  nClient;
	INT  nClients;

	for (nClient = 0, nClients = (pClients->GetSize() == GetSize()) ? (INT)GetSize() : -1; nClient < nClients; nClient++)
	{
		if (!pClients->GetAt(nClient)->Compare(GetAt(nClient))) break;
		continue;
	}
	return((nClient == nClients) ? TRUE : FALSE);
}

BOOL CAutomationClients::Map(CByteArray &nInfo) CONST
{
	INT  nClient;
	INT  nClients;
	CByteArray  nClientData;
	CAutomationClientInfo  *pClientInfo;

	for (nClient = 0, nClients = (INT)GetSize(), nInfo.RemoveAll(); nClient < nClients; nClient++)
	{
		if ((pClientInfo = GetAt(nClient)) && pClientInfo->Map(nClientData) && nInfo.Append(nClientData) >= 0) continue;
		break;
	}
	return((nClient == nClients) ? TRUE : FALSE);
}

BOOL CAutomationClients::Unmap(CONST CByteArray &nInfo)
{
	INT  cbClient;
	INT  cbClients;
	CByteArray  nClientData;
	CAutomationClientInfo  *pClientInfo;

	for (cbClients = 0, RemoveAll(); cbClients < nInfo.GetSize(); cbClients += cbClient)
	{
		for (CopyMemory(&cbClient, nInfo.GetData() + cbClients, sizeof(cbClient)), nClientData.SetSize(max(min(cbClient, nInfo.GetSize() - cbClients), 0)); nClientData.GetSize() >= 0; )
		{
			CopyMemory(nClientData.GetData(), nInfo.GetData() + cbClients, nClientData.GetSize());
			break;
		}
		if ((pClientInfo = new CAutomationClientInfo))
		{
			if (pClientInfo->Unmap(nClientData) && Add(pClientInfo) >= 0) continue;
			delete pClientInfo;
		}
		break;
	}
	return((cbClients == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CAutomationClients::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CAutomationClientInfo  *pClientInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pClientInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pClientInfo->GetUserName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pClientInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pClientInfo->GetUserName() == pszName) || (bInsert && (((pClientInfo = GetAt(max(nIndex[0] - 1, 0))) && pClientInfo->GetUserName() != pszName && (pClientInfo = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pClientInfo->GetUserName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CAutomationTaskSocket

IMPLEMENT_DYNCREATE(CAutomationTaskSocket, CSocket)

CAutomationTaskSocket::CAutomationTaskSocket() : CSocket()
{
	m_bSendData = FALSE;
	m_nTimerID = 0;
}

BOOL CAutomationTaskSocket::Open()
{
	return TRUE;
}

BOOL CAutomationTaskSocket::IsOpen() CONST
{
	return((m_hSocket != (SOCKET)INVALID_SOCKET) ? TRUE : FALSE);
}

VOID CAutomationTaskSocket::Close()
{
	m_nData.RemoveAll();
	CSocket::Close();
}

INT CAutomationTaskSocket::Send(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbBuffer;

	for (SetSockOpt(SO_SNDBUF, &(cbBuffer = GetAutomationService()->GetBufferSize()), sizeof(cbBuffer)), m_nTimerID = SetTimer((HWND)NULL, AUTOMATIONTASKSOCKET_DATASTREAM_TIMERID, (UINT)max(1000 * GetAutomationService()->GetTimeout().GetTotalSeconds(), AUTOMATIONTASKSOCKET_DATASTREAM_TIMEOUT), NULL); (cbData = CSocket::Send(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
	{
		KillTimer((HWND)NULL, m_nTimerID);
		m_bSendData = FALSE;
		m_nTimerID = 0;
		return cbData;
	}
	if (GetLastError() != WSAECONNABORTED)
	{
		KillTimer((HWND)NULL, m_nTimerID);
		m_bSendData = FALSE;
		m_nTimerID = 0;
		return SOCKET_ERROR;
	}
	KillTimer((HWND)NULL, m_nTimerID);
	m_bSendData = FALSE;
	m_nTimerID = 0;
	return 0;
}

INT CAutomationTaskSocket::Receive(CByteArray &nData)
{
	INT  cbData;
	INT  cbBuffer;

	for (nData.SetSize(GetAutomationService()->GetBufferSize()); nData.GetSize() == GetTPEPService()->GetBufferSize(); )
	{
		for (SetSockOpt(SO_RCVBUF, &(cbBuffer = GetAutomationService()->GetBufferSize()), sizeof(cbBuffer)); (cbData = CSocket::Receive(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			nData.SetSize(cbData);
			return cbData;
		}
		break;
	}
	return((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0);
}

BOOL CAutomationTaskSocket::ParseRequest(CONST CByteArray &nData)
{
	INT  nID;
	INT  nIDs;
	INT  nIndex;
	INT  nCount;
	INT  nPos[2];
	BYTE  nCode[3];
	BOOL  bUnicode;
	TCHAR  szDigit;
	CString  szValue;
	CString  szValues;
	CString  szRequest;
	CString  szMessage;
	CString  szSubSystem;
	CString  szClientName;
	CString  szClientBlock;
	CString  szPassword[2];
	CString  szServiceName;
	CString  szServiceBlock;
	CString  szParametersBlock;
	CString  szOperatingMode;
	CString  szDeviceType;
	CByteArray  nPasswordData;
	CStringTools  cStringTools;
	CStringArray  szSubSystems;
	CTCUplinkDevice  cTCDevice;
	CTMProviderDevice  cTMDevice;
	CAutomationClients  pClients;
	CAutomationClientInfo  *pClientInfo;
	CCryptographyTools  cCryptographyTools;

#ifndef UNICODE
	bUnicode = FALSE;
#else
	bUnicode = TRUE;
#endif
	for (m_nData.Append(nData), CopyMemory(szRequest.GetBufferSetLength((INT)(m_nData.GetSize() / sizeof(TCHAR))), m_nData.GetData(), m_nData.GetSize()), szRequest.ReleaseBuffer(); szRequest.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUEST_BEGIN)) < 0; )
	{
#ifndef UNICODE
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)m_nData.GetData(), (INT)m_nData.GetSize(), szRequest.GetBufferSetLength((INT)m_nData.GetSize()), (INT)m_nData.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
		szRequest.ReleaseBuffer();
		bUnicode = TRUE;
#else
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)m_nData.GetData(), (INT)m_nData.GetSize(), szRequest.GetBufferSetLength((INT)m_nData.GetSize()), (INT)m_nData.GetSize());
		szRequest.ReleaseBuffer();
		bUnicode = FALSE;
#endif
		break;
	}
	if (GetAutomationService()->IsEnabled())
	{
		if ((nPos[0] = szRequest.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUEST_BEGIN))) >= 0 && (nPos[1] = szRequest.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUEST_END))) >= 0)
		{
			for (szRequest = szRequest.Mid(nPos[0], nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUEST_END))), m_nData.RemoveAt(0, bUnicode*(nPos[0] + nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUEST_END))) + nPos[0] + nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUEST_END))); (nPos[0] = szRequest.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_BEGIN))) >= 0 && (nPos[1] = szRequest.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))) >= 0; )
			{
				for (szServiceBlock = szRequest.Mid(nPos[0], nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))); (nPos[0] = szServiceBlock.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))) >= 0 && (nPos[1] = szServiceBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_END))) >= 0; )
				{
					for (szServiceName = szServiceBlock.Mid(nPos[0] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN)), nPos[1] - lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))); (nPos[0] = szRequest.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENT_BEGIN))) >= 0 && (nPos[1] = szRequest.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENT_END))) >= 0; )
					{
						for (szClientBlock = szRequest.Mid(nPos[0], nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENT_END))); (nPos[0] = szClientBlock.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTNAME_BEGIN))) && (nPos[1] = szClientBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTNAME_END))); )
						{
							if ((pClientInfo = (GetAutomationService()->GetClients(pClients) > 0) ? pClients.GetAt(pClients.Find((szClientName = szClientBlock.Mid(nPos[0] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTNAME_BEGIN)), nPos[1] - lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTNAME_BEGIN)))))) : (CAutomationClientInfo *)NULL) && !pClientInfo->IsBanned())
							{
								if ((nPos[0] = szClientBlock.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTPASSWORD_BEGIN))) >= 0 && (nPos[1] = szClientBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTPASSWORD_END))) >= 0)
								{
									for (szPassword[0] = szClientBlock.Mid(nPos[0] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTPASSWORD_BEGIN)), nPos[1] - lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTCLIENTPASSWORD_BEGIN))); pClientInfo->UsesEncryption(); )
									{
										for (nIndex = 0, nCount = szPassword[0].GetLength(), szPassword[0].MakeUpper(), nPasswordData.RemoveAll(), nCode[0] = 0, nCode[1] = __toascii(cStringTools.ConvertIntToString(0).GetAt(0)), nCode[2] = __toascii(cStringTools.ConvertIntToString(10, 16).GetAt(0)); nIndex < nCount; nIndex++)
										{
											for (nCode[0] = (_istdigit((szDigit = szPassword[0].GetAt(nIndex)))) ? (16 * nCode[0] + __toascii(szDigit) - nCode[1]) : ((_istxdigit(szDigit)) ? (16 * nCode[0] + __toascii(szDigit) - nCode[2] + 10) : 0); nIndex % 2 == 1; )
											{
												nPasswordData.Add(nCode[0]);
												nCode[0] = 0;
												break;
											}
											if (!_istxdigit(szDigit)) break;
										}
										if (nIndex == nCount)
										{
											cCryptographyTools.SetBaseData(pClientInfo->GetPassword());
											if (cCryptographyTools.DecryptText(nPasswordData, szPassword[1])) break;
										}
										szPassword[0].Empty();
										szPassword[1].Empty();
										break;
									}
									if ((!pClientInfo->UsesEncryption() && pClientInfo->GetPassword() == szPassword[0]) || (pClientInfo->UsesEncryption() && pClientInfo->GetPassword() == szPassword[1]))
									{
										if (!szServiceName.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_NAME_CONFIGURATIONSETTINGS_SAVE)) || !szServiceName.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_NAME_CONFIGURATIONSETTINGS_LOAD)))
										{
											for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_DENIEDSERVICE), (LPCTSTR)szServiceName, (LPCTSTR)szClientName); !pClientInfo->HasPermission(szServiceName); )
											{
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_DENIED), szMessage, bUnicode);
												return FALSE;
											}
											for (nIndex = 0, nCount = EnumParameterValue(ExtractParameterValue(szServiceBlock, STRING(IDS_AUTOMATIONSERVICE_PARAMETERNAME_SUBSYSTEMS), szMessage), szSubSystems), szValues.Empty(); nIndex < nCount; nIndex++)
											{
												for (nID = MINAUTOMATIONSERVICESUBSYSTEM, nIDs = MAXAUTOMATIONSERVICESUBSYSTEM; nID <= nIDs; nID++)
												{
													if (!szSubSystems.GetAt(nIndex).CompareNoCase(STRING(nID))) break;
													continue;
												}
												if (nID > nIDs)
												{
													szSubSystem.Format(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_QUOTATION), (LPCTSTR)szSubSystems.GetAt(nIndex));
													szValues += (!szValues.IsEmpty()) ? (STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_SEPARATOR) + szSubSystem) : szSubSystem;
													szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ILLEGALSERVICESUBSYSTEMSPARAMETER), (LPCTSTR)szValues);
												}
											}
											if (!szMessage.IsEmpty())
											{
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), szMessage, bUnicode);
												return FALSE;
											}
											ReplyRequest(szServiceName, ((!szServiceName.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_NAME_CONFIGURATIONSETTINGS_SAVE)) && SaveRegistryData(szSubSystems)) || (!szServiceName.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_NAME_CONFIGURATIONSETTINGS_LOAD)) && LoadRegistryData(szSubSystems))) ? STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_SUCCESSFUL) : STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), EMPTYSTRING, bUnicode);
											return TRUE;
										}
										if (szServiceName == STRING(IDS_AUTOMATIONSERVICE_NAME_OPERATINGMODES_CHANGES))
										{
											for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_DENIEDSERVICE), (LPCTSTR)szServiceName, (LPCTSTR)szClientName); !pClientInfo->HasPermission(szServiceName); )
											{
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_DENIED), szMessage, bUnicode);
												return FALSE;
											}
											if (!(szOperatingMode = ExtractParameterValue(szServiceBlock, STRING(IDS_AUTOMATIONSERVICE_PARAMETERNAME_OPERATINGMODE), szMessage)).CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_STANDBY)) || !szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_ACTIVE)) || !szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_PASSIVE)) || !szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_MAINTENANCE)) || !szOperatingMode.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_OPERATINGMODE_FINAL)))
											{
												ReplyRequest(szServiceName, (SwitchOperatingMode(szOperatingMode)) ? STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_SUCCESSFUL) : STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), EMPTYSTRING, bUnicode);
												return TRUE;
											}
											if (!szMessage.IsEmpty())
											{
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), szMessage, bUnicode);
												return FALSE;
											}
											szValue.Format(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_QUOTATION), (LPCTSTR)szOperatingMode);
											szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ILLEGALSERVICEOPERATINGMODEPARAMETER), (LPCTSTR)szValue);
											ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), szMessage, bUnicode);
											return FALSE;
										}
										if (szServiceName == STRING(IDS_AUTOMATIONSERVICE_NAME_SYSTEMHEALTH_CHECK))
										{
											for (szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_DENIEDSERVICE), (LPCTSTR)szServiceName, (LPCTSTR)szClientName); !pClientInfo->HasPermission(szServiceName); )
											{
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_DENIED), szMessage, bUnicode);
												return FALSE;
											}
											for (szDeviceType = ExtractParameterValue(szServiceBlock, STRING(IDS_AUTOMATIONSERVICE_PARAMETERNAME_DEVICETYPE), szMessage); !szMessage.IsEmpty(); )
											{
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), szMessage, bUnicode);
												return FALSE;
											}
											if (!szDeviceType.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_DEVICETYPE_TM)))
											{
												if (GetTMService()->GetActiveTMProviderDevice(&cTMDevice) && !cTMDevice.GetDeviceName().IsEmpty())
												{
													ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_SUCCESSFUL), cTMDevice.GetStatus(), bUnicode);
													return TRUE;
												}
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), (cTMDevice.GetDeviceName().IsEmpty()) ? STRING(IDS_TELEMETRYPROVIDERDEVICE_NONE) : EMPTYSTRING, bUnicode);
												return FALSE;
											}
											if (!szDeviceType.CompareNoCase(STRING(IDS_AUTOMATIONSERVICE_DEVICETYPE_TC)))
											{
												if (GetTCService()->GetActiveTCUplinkDevice(&cTCDevice) && !cTCDevice.GetDeviceName().IsEmpty())
												{
													ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_SUCCESSFUL), cTCDevice.GetStatus(), bUnicode);
													return TRUE;
												}
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), (cTCDevice.GetDeviceName().IsEmpty()) ? STRING(IDS_TELECOMMANDUPLINKDEVICE_NONE) : EMPTYSTRING, bUnicode);
												return FALSE;
											}
											if (szDeviceType.IsEmpty())
											{
												ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_SUCCESSFUL), (CheckSystemHealth()) ? STRING(IDS_AUTOMATIONSERVICE_SYSTEMHEALTH_GOOD) : STRING(IDS_AUTOMATIONSERVICE_SYSTEMHEALTH_BAD), bUnicode);
												return TRUE;
											}
											szValue.Format(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_QUOTATION), (LPCTSTR)szDeviceType);
											szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ILLEGALSERVICEDEVICETYPEPARAMETER), (LPCTSTR)szValue);
											ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), szMessage, bUnicode);
											return FALSE;
										}
										ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ILLEGALSERVICENAME), bUnicode);
										return FALSE;
									}
									ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_DENIED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ILLEGALCLIENTPASSWORD), bUnicode);
									return FALSE;
								}
								ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGCLIENTPASSWORDTAG), bUnicode);
								return FALSE;
							}
							for (szMessage = STRING(IDS_AUTOMATIONSERVICE_MESSAGE_ILLEGALCLIENTNAME); !szClientName.IsEmpty(); )
							{
								szMessage.Format(STRING(IDS_AUTOMATIONSERVICE_MESSAGE_DENIEDCLIENT), (LPCTSTR)szClientName);
								break;
							}
							ReplyRequest(szServiceName, (!szClientName.IsEmpty()) ? STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_DENIED) : STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), szMessage, bUnicode);
							return FALSE;
						}
						ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGCLIENTNAMETAG), bUnicode);
						return FALSE;
					}
					ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGCLIENTTAG), bUnicode);
					return FALSE;
				}
				ReplyRequest(szServiceName, STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGSERVICENAMETAG), bUnicode);
				return FALSE;
			}
			ReplyRequest((szServiceName = ((szServiceBlock = ((nPos[0] = szRequest.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_BEGIN))) >= 0 && (nPos[1] = szRequest.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))) >= 0) ? szRequest.Mid(nPos[0], nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))) : EMPTYSTRING).GetLength() > 0) ? (((nPos[0] = szServiceBlock.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))) >= 0 && (nPos[1] = szServiceBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_END))) >= 0) ? szServiceBlock.Mid(nPos[0] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN)), nPos[1] - lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))) : EMPTYSTRING) : EMPTYSTRING), STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGSERVICETAG), bUnicode);
			return FALSE;
		}
		ReplyRequest((szServiceName = ((szServiceBlock = ((nPos[0] = szRequest.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_BEGIN))) >= 0 && (nPos[1] = szRequest.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))) >= 0) ? szRequest.Mid(nPos[0], nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))) : EMPTYSTRING).GetLength() > 0) ? (((nPos[0] = szServiceBlock.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))) >= 0 && (nPos[1] = szServiceBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_END))) >= 0) ? szServiceBlock.Mid(nPos[0] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN)), nPos[1] - lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))) : EMPTYSTRING) : EMPTYSTRING), STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGREQUESTTAG), bUnicode);
		m_nData.RemoveAll();
		return FALSE;
	}
	ReplyRequest((szServiceName = ((szServiceBlock = ((nPos[0] = szRequest.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_BEGIN))) >= 0 && (nPos[1] = szRequest.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))) >= 0) ? szRequest.Mid(nPos[0], nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICE_END))) : EMPTYSTRING).GetLength() > 0) ? (((nPos[0] = szServiceBlock.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))) >= 0 && (nPos[1] = szServiceBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_END))) >= 0) ? szServiceBlock.Mid(nPos[0] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN)), nPos[1] - lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICENAME_BEGIN))) : EMPTYSTRING) : EMPTYSTRING), STRING(IDS_AUTOMATIONSERVICE_STATUS_REQUESTACCEPTANCE_FAILED), STRING(IDS_AUTOMATIONSERVICE_MESSAGE_DISABLEDSERVICE), bUnicode);
	m_nData.RemoveAll();
	return FALSE;
}

BOOL CAutomationTaskSocket::ReplyRequest(LPCTSTR pszServiceName, LPCTSTR pszAcceptance, LPCTSTR pszMessage, BOOL bUnicode)
{
	CString  szReply;
	CString  szNewLine;
	CString  szIndent;
	CByteArray  nData;

	for (szReply = STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSE_BEGIN) + (szNewLine = CString(CR) + CString(EOL)) + (szIndent = CString(TAB)) + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICE_BEGIN) + szNewLine + szIndent + szIndent + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICENAME_BEGIN) + pszServiceName + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICENAME_END) + szNewLine + szIndent + szIndent + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICEACCEPTANCE_BEGIN) + szNewLine + szIndent + szIndent + szIndent + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICEACCEPTANCESTATUS_BEGIN) + pszAcceptance + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICEACCEPTANCESTATUS_END), szReply += (lstrlen(pszMessage) > 0) ? (szNewLine + szIndent + szIndent + szIndent + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICEACCEPTANCEMESSAGE_BEGIN) + CString(pszMessage) + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICEACCEPTANCEMESSAGE_END)) : EMPTYSTRING, szReply += szNewLine + szIndent + szIndent + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICEACCEPTANCE_END) + szNewLine + szIndent + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSESERVICE_END) + szNewLine + STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTRESPONSE_END); !bUnicode; )
	{
		nData.SetSize(szReply.GetLength());
#ifndef UNICODE
		CopyMemory(nData.GetData(), szReply, nData.GetSize());
#else
		WideCharToMultiByte(CP_ACP, 0, szReply, -1, (LPSTR)nData.GetData(), szReply.GetLength(), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
		break;
	}
	if (bUnicode)
	{
		nData.SetSize(szReply.GetLength()*sizeof(WCHAR));
#ifndef UNICODE
		MultiByteToWideChar(CP_ACP, 0, szReply, -1, (LPWSTR)nData.GetData(), szReply.GetLength());
#else
		CopyMemory(nData.GetData(), szReply, nData.GetSize());
#endif
	}
	return(Send(nData) == nData.GetSize());
}

CString CAutomationTaskSocket::ExtractParameterValue(LPCTSTR pszServiceBlock, LPCTSTR pszValueName, CString &szMessage) CONST
{
	INT  nID;
	INT  nIDs;
	INT  nPos[2];
	CString  szServiceBlock;
	CString  szParameterValue;
	CString  szParametersBlock;

	for (szServiceBlock = pszServiceBlock, szMessage.Empty(), nPos[0] = nPos[1] = -1; (nPos[0] = szServiceBlock.Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICEPARAMETERS_BEGIN))) >= 0 && (nPos[1] = szServiceBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICEPARAMETERS_END))) >= 0; )
	{
		for (szParametersBlock = szServiceBlock.Mid(nPos[0], nPos[1] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICEPARAMETERS_END))), SkipSpaces(szParametersBlock, (nPos[0] = lstrlen(STRING(IDS_AUTOMATIONSERVICE_TAG_REQUESTSERVICEPARAMETERS_BEGIN)))); !szParametersBlock.Mid(nPos[0]).Find(pszValueName); )
		{
			for (SkipSpaces(szParametersBlock, (nPos[0] = nPos[0] + lstrlen(pszValueName))); !szParametersBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_ASSIGNMENT)); )
			{
				for (SkipSpaces(szParametersBlock, (nPos[0] = nPos[0] + lstrlen(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_ASSIGNMENT)))); !szParametersBlock.Mid(nPos[0]).Find(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_DELIMITER)); )
				{
					for (nPos[0] += lstrlen(STRING(IDS_AUTOMATIONSERVICE_STRINGVALUE_DELIMITER)); nPos[0] < szParametersBlock.GetLength(); nPos[0]++)
					{
						if (szParametersBlock.GetAt(nPos[0]) != STRINGCHAR(IDS_AUTOMATIONSERVICE_STRINGVALUE_DELIMITER))
						{
							szParameterValue += szParametersBlock.GetAt(nPos[0]);
							continue;
						}
						break;
					}
					return szParameterValue;
				}
				szMessage = STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGSERVICEPARAMETERVALUEDELIMITERSYMBOL);
				return EMPTYSTRING;
			}
			szMessage = STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGSERVICEPARAMETERVALUEASSIGNMENTSYMBOL);
			return EMPTYSTRING;
		}
		for (nID = MINAUTOMATIONSERVICEPARAMETERNAME, nIDs = MAXAUTOMATIONSERVICEPARAMETERNAME; nID <= nIDs; nID++)
		{
			if (!_tcscmp(pszValueName, STRING(nID))) break;
			continue;
		}
		szMessage = (nID <= nIDs) ? STRING(MINAUTOMATIONSERVICEMESSAGEMISSINGPARAMETERNAME + nID - MINAUTOMATIONSERVICEPARAMETERNAME) : EMPTYSTRING;
		return EMPTYSTRING;
	}
	szMessage = (nPos[0] >= 0 || nPos[1] >= 0) ? STRING(IDS_AUTOMATIONSERVICE_MESSAGE_MISSINGSERVICEPARAMETERSTAG) : EMPTYSTRING;
	return EMPTYSTRING;
}

INT CAutomationTaskSocket::EnumParameterValue(LPCTSTR pszParameterValue, CStringArray &szValues) CONST
{
	INT  nPos;
	CString  szValue;
	CString  szParameterValue;

	for (nPos = 0, szParameterValue = pszParameterValue, szValues.RemoveAll(); nPos < szParameterValue.GetLength(); nPos++)
	{
		if (szParameterValue.GetAt(nPos) != STRINGCHAR(IDS_AUTOMATIONSERVICE_STRINGVALUE_SEPARATOR))
		{
			szValue += szParameterValue.GetAt(nPos);
			continue;
		}
		if (!szValue.IsEmpty())
		{
			szValues.Add(szValue);
			szValue.Empty();
		}
	}
	if (!szValue.IsEmpty()) szValues.Add(szValue);
	return((INT)szValues.GetSize());
}

VOID CAutomationTaskSocket::SkipSpaces(LPCTSTR pszText, INT &nPos) CONST
{
	CString  szText;

	for (szText = pszText; nPos < lstrlen(pszText); nPos++)
	{
		if (!_istspace(szText.GetAt(nPos))) break;
		continue;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAutomationTaskSocket member functions

BOOL CAutomationTaskSocket::OnMessagePending()
{
	MSG  sMsg;

	while (PeekMessage(&sMsg, (HWND)NULL, WM_TIMER, WM_TIMER, PM_REMOVE))
	{
		if (m_nTimerID == (UINT_PTR)sMsg.wParam  &&  m_bSendData)
		{
			KillTimer((HWND)NULL, m_nTimerID);
			CancelBlockingCall();
			m_nTimerID = 0;
		}
	}
	return CSocket::OnMessagePending();
}

void CAutomationTaskSocket::OnReceive(int nErrorCode)
{
	INT  cbData;
	CByteArray  nData;

	switch (Receive(nData))
	{
	case SOCKET_ERROR:
	{ ReportEvent(SYSTEM_WARNING_AUTOMATIONSERVICE_GENERAL_FAILURE);
	Close();
	break;
	}
	case 0:
	{ Close();
	break;
	}
	default:
	{ do
	{
		for (cbData = (INT)m_nData.GetSize(); !ParseRequest(nData); )
		{
			ReportEvent(SYSTEM_WARNING_AUTOMATIONSERVICE_ILLEGAL_REQUEST);
			if (cbData == m_nData.GetSize()) break;
		}
		nData.RemoveAll();
	} while (m_nData.GetSize() > 0);
	Close();
	break;
	}
	}
	CSocket::OnReceive(nErrorCode);
}

void CAutomationTaskSocket::OnClose(int nErrorCode)
{
	Close();
}


/////////////////////////////////////////////////////////////////////////////
// CAutomationTaskSockets

CAutomationTaskSockets::CAutomationTaskSockets() : CPtrArray()
{
	return;
}

CAutomationTaskSockets::~CAutomationTaskSockets()
{
	RemoveAll();
}

BOOL CAutomationTaskSockets::Add(CAutomationTaskSocket *pSocket)
{
	INT  nSocket;
	INT  nSockets;

	for (nSocket = 0, nSockets = (INT)GetSize(); nSocket < nSockets; nSocket++)
	{
		if (!GetAt(nSocket)->IsOpen())
		{
			delete GetAt(nSocket);
			RemoveAt(nSocket);
			nSockets--;
			nSocket--;
		}
	}
	return((CPtrArray::Add(pSocket) >= 0) ? TRUE : FALSE);
}

CAutomationTaskSocket *CAutomationTaskSockets::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAutomationTaskSocket *)CPtrArray::GetAt(nIndex) : (CAutomationTaskSocket *)NULL);
}

CAutomationTaskSocket *CAutomationTaskSockets::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAutomationTaskSocket *)CPtrArray::GetAt(nIndex) : (CAutomationTaskSocket *)NULL);
}

VOID CAutomationTaskSockets::RemoveAll()
{
	INT  nSocket;
	INT  nSockets;
	CAutomationTaskSocket  *pSocket;

	for (nSocket = 0, nSockets = (INT)GetSize(); nSocket < nSockets; nSocket++)
	{
		if ((pSocket = GetAt(nSocket)))
		{
			pSocket->Close();
			delete pSocket;
		}
	}
	CPtrArray::RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CAutomationServiceSocket

IMPLEMENT_DYNCREATE(CAutomationServiceSocket, CSocket)

BOOL CAutomationServiceSocket::Open()
{
	if (Create(GetAutomationService()->GetPort()))
	{
		if (Listen()) return TRUE;
		Close();
	}
	return FALSE;
}

VOID CAutomationServiceSocket::Close()
{
	m_pTaskSockets.RemoveAll();
	CSocket::Close();
}

/////////////////////////////////////////////////////////////////////////////
// CAutomationServiceSocket member functions

void CAutomationServiceSocket::OnAccept(int nErrorCode)
{
	CAutomationTaskSocket  *pSocket;

	if ((pSocket = new CAutomationTaskSocket))
	{
		if (pSocket->Open() && Accept(*pSocket))
		{
			m_pTaskSockets.Add(pSocket);
			return;
		}
		pSocket->Close();
		delete pSocket;
	}
	ReportEvent(SYSTEM_WARNING_AUTOMATIONSERVICE_GENERAL_FAILURE);
}


/////////////////////////////////////////////////////////////////////////////
// CAutomationServiceThread thread

IMPLEMENT_DYNCREATE(CAutomationServiceThread, CThread)

CAutomationServiceThread::CAutomationServiceThread() : CThread()
{
	return;
}

BOOL CAutomationServiceThread::Start()
{
	HANDLE  hEvents[2];

	for (Stop(), hEvents[0] = m_bInitialization[0], hEvents[1] = m_bInitialization[1]; CreateThread(); )
	{
		if (WaitForMultipleObjects(sizeof(hEvents) / sizeof(hEvents[0]), hEvents, FALSE, INFINITE) == WAIT_OBJECT_0  &&  Update()) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CAutomationServiceThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CAutomationServiceThread::Update()
{
	return m_bUpdate.SetEvent();
}

BOOL CAutomationServiceThread::InitInstance()
{
	if (AfxSocketInit())
	{
		if (m_cSocket.Open())
		{
			m_bInitialization[0].SetEvent();
			return TRUE;
		}
	}
	m_bInitialization[1].SetEvent();
	return FALSE;
}

int CAutomationServiceThread::ExitInstance()
{
	m_cSocket.Close();
	return CThread::ExitInstance();
}

int CAutomationServiceThread::Run()
{
	Wait();
	return ExitInstance();
}

BEGIN_MESSAGE_MAP(CAutomationServiceThread, CThread)
	//{{AFX_MSG_MAP(CAutomationServiceThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutomationServiceThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CAutomationService

CAutomationService::CAutomationService() : CObject()
{
	m_nPort = AUTOMATION_SERVICE_DEFAULTPORT;
	m_nBufferSize = AUTOMATION_SERVICE_DEFAULTBUFFERSIZE;
	m_tTimeout = AUTOMATION_SERVICE_DEFAULTTIMEOUT;
	m_bEnabled = TRUE;
}

BOOL CAutomationService::Start()
{
	CByteArray  nClients;
	CProfile  cProfile;

	if (cProfile.GetAutomationServiceSettingsInfo(m_nPort, m_nBufferSize, m_tTimeout, m_bEnabled) && cProfile.GetAutomationServiceClientsInfo(nClients) && m_pClients.Unmap(nClients))
	{
		if (GetSystemMetrics(SM_REMOTESESSION) || !m_cServiceThread.Start()) ReportEvent(SYSTEM_INFORMATIONAL_AUTOMATIONSERVICE_NOT_AVAILABLE, !GetSystemMetrics(SM_REMOTESESSION));
		return TRUE;
	}
	ReportEvent(SYSTEM_WARNING_AUTOMATIONSERVICE_LOAD_FAILURE);
	return FALSE;
}

BOOL CAutomationService::Stop()
{
	CByteArray  nClients;
	CProfile  cProfile;

	for (m_cServiceThread.Stop(); cProfile.SetAutomationServiceSettingsInfo(m_nPort, m_nBufferSize, m_tTimeout, m_bEnabled) && m_pClients.Map(nClients) && cProfile.SetAutomationServiceClientsInfo(nClients); ) return TRUE;
	ReportEvent(SYSTEM_WARNING_AUTOMATIONSERVICE_SAVE_FAILURE);
	return FALSE;
}

BOOL CAutomationService::SetPort(UINT nPort)
{
	for (Lock(); nPort >= AUTOMATION_SERVICE_FIRSTPORT && nPort <= AUTOMATION_SERVICE_LASTPORT; )
	{
		if (m_nPort != nPort)
		{
			m_nPort = nPort;
			Unlock();
			return m_cServiceThread.Start();
		}
		Unlock();
		return TRUE;
	}
	Unlock();
	return FALSE;
}

BOOL CAutomationService::GetPort(UINT &nPort) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nPort = m_nPort;
	return TRUE;
}
UINT CAutomationService::GetPort() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_nPort;
}

BOOL CAutomationService::SetBufferSize(UINT nSize)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nSize >= AUTOMATION_SERVICE_MINIMUMBUFFERSIZE  &&  nSize <= AUTOMATION_SERVICE_MAXIMUMBUFFERSIZE)
	{
		m_nBufferSize = nSize;
		return TRUE;
	}
	return FALSE;
}

BOOL CAutomationService::GetBufferSize(UINT &nSize) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nSize = m_nBufferSize;
	return TRUE;
}
UINT CAutomationService::GetBufferSize() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_nBufferSize;
}

BOOL CAutomationService::SetTimeout(CONST CTimeSpan &tTimeout)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	m_tTimeout = tTimeout;
	return TRUE;
}

BOOL CAutomationService::GetTimeout(CTimeSpan &tTimeout) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	tTimeout = m_tTimeout;
	return TRUE;
}
CTimeSpan CAutomationService::GetTimeout() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_tTimeout;
}

BOOL CAutomationService::SetClients(CONST CAutomationClients &pClients)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_pClients.Copy(&pClients);
}

INT CAutomationService::GetClients(CAutomationClients &pClients) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((pClients.Copy(&m_pClients)) ? (INT)pClients.GetSize() : 0);
}

BOOL CAutomationService::SetServiceInfo(CONST CByteArray &nInfo)
{
	CByteArray  nServiceInfo;
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nInfo.GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nInfo.GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbClients && sServiceInfo.cbClients >= 0; )
		{
			for (nServiceInfo.SetSize(sServiceInfo.cbClients), CopyMemory(nServiceInfo.GetData(), nInfo.GetData() + sizeof(SERVICEINFO), sServiceInfo.cbClients); m_pClients.Unmap(nServiceInfo); )
			{
				m_nPort = sServiceInfo.nPort;
				m_nBufferSize = sServiceInfo.nBufferSize;
				m_tTimeout = sServiceInfo.tTimeout;
				m_bEnabled = sServiceInfo.bEnabled;
				return TRUE;
			}
			break;
		}
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CAutomationService::GetServiceInfo(CByteArray &nInfo) CONST
{
	CByteArray  nServiceInfo;
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (m_pClients.Map(nServiceInfo))
	{
		nInfo.SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbClients = (INT)nServiceInfo.GetSize()))));
		sServiceInfo.nPort = m_nPort;
		sServiceInfo.nBufferSize = m_nBufferSize;
		sServiceInfo.tTimeout = m_tTimeout.GetTotalSeconds();
		sServiceInfo.bEnabled = m_bEnabled;
		CopyMemory(nInfo.GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO), nServiceInfo.GetData(), nServiceInfo.GetSize());
		return TRUE;
	}
	return FALSE;
}

BOOL CAutomationService::UpdateServiceInfo(BOOL bSave)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((bSave  &&  SaveServiceInfo()) || (!bSave  &&  LoadServiceInfo()));
}

VOID CAutomationService::Enable(BOOL bEnable)
{
	m_bEnabled = bEnable;
}

BOOL CAutomationService::IsEnabled() CONST
{
	return m_bEnabled;
}

BOOL CAutomationService::SaveServiceInfo()
{
	CByteArray  nServiceInfo[2];
	SERVICEINFO  sServiceInfo;
	CProfile  cProfile;

	if (GetServiceInfo(nServiceInfo[0]) && nServiceInfo[0].GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nServiceInfo[0].GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbClients && sServiceInfo.cbClients >= 0; )
		{
			nServiceInfo[1].SetSize(sServiceInfo.cbClients);
			CopyMemory(nServiceInfo[1].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO), sServiceInfo.cbClients);
			return cProfile.SetAutomationServiceSettingsInfo(sServiceInfo.nPort, sServiceInfo.nBufferSize, sServiceInfo.tTimeout, sServiceInfo.bEnabled) && cProfile.SetAutomationServiceClientsInfo(nServiceInfo[1]);
		}
	}
	return FALSE;
}

BOOL CAutomationService::LoadServiceInfo()
{
	UINT  nPort;
	UINT  nBufferSize;
	BOOL  bEnabled;
	CTimeSpan  tTimeout;
	CByteArray  nServiceInfo[2];
	SERVICEINFO  sServiceInfo;
	CProfile  cProfile;

	if (cProfile.GetAutomationServiceSettingsInfo(nPort, nBufferSize, tTimeout, bEnabled) && cProfile.GetAutomationServiceClientsInfo(nServiceInfo[1]))
	{
		nServiceInfo[0].SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbClients = (INT)nServiceInfo[1].GetSize()))));
		sServiceInfo.nPort = m_nPort;
		sServiceInfo.nBufferSize = m_nBufferSize;
		sServiceInfo.tTimeout = m_tTimeout.GetTotalSeconds();
		sServiceInfo.bEnabled = m_bEnabled;
		CopyMemory(nServiceInfo[0].GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO), nServiceInfo[1].GetData(), nServiceInfo[1].GetSize());
		return SetServiceInfo(nServiceInfo[0]);
	}
	return FALSE;
}

BOOL CAutomationService::Lock()
{
	return m_cServiceThread.m_pCriticalSection->Lock();
}

BOOL CAutomationService::Unlock()
{
	return m_cServiceThread.m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsServiceThread

IMPLEMENT_DYNCREATE(CMemoryDumpsServiceThread, CThread)

CMemoryDumpsServiceThread::CMemoryDumpsServiceThread() : CThread()
{
	m_bAvailable = TRUE;
}

BOOL CMemoryDumpsServiceThread::Start(HANDLE bUpdate)
{
	CByteArray  nQueueInfo;
	CProfile  cProfile;

	if (Lock())
	{
		ReportEvent((!cProfile.GetMemoryDumpsServiceFTPQueueInfo(nQueueInfo) || !m_pMemoryDumps.Unmap(nQueueInfo)) ? SYSTEM_WARNING_MEMORYDUMPSSERVICE_FTPQUEUE_LOAD_FAILURE : SYSTEM_NOERROR);
		Unlock();
	}
	return CreateThread(bUpdate);
}

BOOL CMemoryDumpsServiceThread::Stop()
{
	INT  nDump;
	INT  nDumps;
	CByteArray  nDumpData;
	CMemoryDump  *pMemoryDump;
	CProfile  cProfile;

	if (Lock())
	{
		for (nDump = 0, nDumps = (INT)m_pMemoryDumps.GetSize(); nDump < nDumps; nDump++)
		{
			if ((pMemoryDump = m_pMemoryDumps.GetAt(nDump)) && !pMemoryDump->GetFTPQueueFlag())
			{
				m_pMemoryDumps.RemoveAt(nDump);
				delete pMemoryDump;
				nDumps--;
				nDump--;
			}
		}
		ReportEvent((!m_pMemoryDumps.Map(nDumpData) || !cProfile.SetMemoryDumpsServiceFTPQueueInfo(nDumpData)) ? SYSTEM_WARNING_MEMORYDUMPSSERVICE_FTPQUEUE_SAVE_FAILURE : SYSTEM_NOERROR);
		Unlock();
	}
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CMemoryDumpsServiceThread::DoFTPTransfer(CONST CMemoryDump *pDump)
{
	INT  nDump;
	INT  nDumps;
	CMemoryDump  *pMemoryDump;
	CStringArray  szRecipients[4];
	HANDLE  bUpdate = (HANDLE)GetThreadInfo();
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nDump = 0, nDumps = EnumFTPRecipients(pDump, szRecipients[0], szRecipients[1], szRecipients[2], szRecipients[3]); nDump < nDumps; nDump++)
	{
		if ((pMemoryDump = new CMemoryDump))
		{
			pMemoryDump->Copy(pDump, TRUE);
			pMemoryDump->SetFTPServer(szRecipients[0].GetAt(nDump));
			pMemoryDump->SetFTPDirectory(szRecipients[1].GetAt(nDump));
			pMemoryDump->SetFTPUserName(szRecipients[2].GetAt(nDump));
			pMemoryDump->SetFTPPassword(szRecipients[3].GetAt(nDump));
			m_pMemoryDumps.InsertAt(m_pMemoryDumps.GetSize(), pMemoryDump, 1);
			continue;
		}
		break;
	}
	if (nDump < nDumps)
	{
		for (; nDump > 0; nDump--)
		{
			if ((pMemoryDump = m_pMemoryDumps.GetAt((INT)m_pMemoryDumps.GetUpperBound())))
			{
				m_pMemoryDumps.RemoveAt(m_pMemoryDumps.GetUpperBound());
				delete pMemoryDump;
			}
		}
		return FALSE;
	}
	return SetEvent(bUpdate);
}

BOOL CMemoryDumpsServiceThread::ResetFTPQueue()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pMemoryDumps.RemoveAll();
	return TRUE;
}

DWORD CMemoryDumpsServiceThread::FTPTransfers()
{
	INT  nDump;
	INT  nDumps;
	UINT  nPort;
	UINT  nAudition;
	UINT  nFormats[2];
	UINT  nRetries[2];
	DWORD  dwWait[2];
	LPSTR  pszDumpData;
	LPWSTR  pszData;
	CString  szName;
	CString  szServer;
	CString  szError[2];
	CString  szUserName;
	CString  szPassword;
	CString  szPathName;
	CString  szFileName;
	CString  szDumpData;
	CString  szDirectory;
	CTimeKey  tRetryTime;
	CTimeSpan  tRetryInterval;
	CMemoryDump  *pMemoryDump;
	CMemoryDumps  cMemoryDumps;
	CInternetFile  *pInternetFile;
	CFtpConnection  *pFtpConnection;
	CInternetSession  cInternetSession;

	for (nDump = nDumps = 0, dwWait[0] = INFINITE; Lock(); )
	{
		nDumps = (cMemoryDumps.Copy(&m_pMemoryDumps, TRUE)) ? (INT)cMemoryDumps.GetSize() : -1;
		Unlock();
		break;
	}
	for (nFormats[0] = 0; nDump < nDumps; nDump++, nFormats[0] = 0)
	{
		if ((pMemoryDump = cMemoryDumps.GetAt(nDump)))
		{
			szName = pMemoryDump->GetName();
			nPort = pMemoryDump->GetFTPPort();
			szServer = pMemoryDump->GetFTPServer();
			szUserName = pMemoryDump->GetFTPUserName();
			szPassword = pMemoryDump->GetFTPPassword();
			tRetryTime = pMemoryDump->GetFTPRetryTime();
			pMemoryDump->GetFTPRetryInfo(nRetries[0], tRetryInterval);
			nRetries[1] = pMemoryDump->GetFTPRetryCount();
			nAudition = pMemoryDump->GetFTPAudition();
			if (((nFormats[1] = pMemoryDump->GetNotificationsFileFormats()) & MEMORYDUMP_FILEFORMAT_NORMAL) || (nFormats[1] & MEMORYDUMP_FILEFORMAT_DESCRIPTIVE) || (nFormats[1] & MEMORYDUMP_FILEFORMAT_DELIMITED))
			{
				if ((nRetries[0] > 0 && (nRetries[0] == nRetries[1] || (nRetries[0] > nRetries[1] && tRetryTime <= CTime::GetCurrentTime()))) || !nRetries[0])
				{
					try
					{
						pFtpConnection = cInternetSession.GetFtpConnection(szServer, szUserName, szPassword, (!nPort) ? INTERNET_INVALID_PORT_NUMBER : nPort);
					}
					catch (CInternetException *pException)
					{
						if (nRetries[0] > 0 && nRetries[1] > 0)
						{
							pMemoryDump->SetFTPRetryCount((nRetries[1] != (UINT)-1) ? (nRetries[1] - 1) : nRetries[1]);
							pMemoryDump->SetFTPRetryTime(CTime::GetCurrentTime().GetTime() + tRetryInterval.GetTotalSeconds());
							dwWait[0] = (dwWait[0] > (DWORD)(1000 * tRetryInterval.GetTotalSeconds()) || dwWait[0] == INFINITE) ? (DWORD)(1000 * tRetryInterval.GetTotalSeconds()) : dwWait[0];
						}
						else
						{
							if (nAudition == MEMORYDUMP_AUDITION_ALL || nAudition == MEMORYDUMP_AUDITION_FAILURES)
							{
								szError[0].Format(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_CONNECTION_FAILURE), (LPCTSTR)szServer, (LPCTSTR)szName);
								szError[1].Format(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_CONNECTION_RETRIES_FAILURE), (LPCTSTR)szServer, nRetries[0], (LPCTSTR)szName);
								ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, (!nRetries[0]) ? szError[0] : szError[1], FALSE);
							}
							cMemoryDumps.RemoveAt(nDump);
							delete pMemoryDump;
							nDumps--;
							nDump--;
						}
						pException->Delete();
						continue;
					}
					if (nFormats[1] & MEMORYDUMP_FILEFORMAT_NORMAL)
					{
						try
						{
							for (szDirectory = ExtractFTPDirectory((szPathName = GetMemoryDumpsServiceSupport()->GetMemoryDumpFTPFileName(pMemoryDump, MEMORYDUMP_FILEFORMAT_NORMAL))); !szDirectory.IsEmpty(); )
							{
								pFtpConnection->SetCurrentDirectory(szDirectory);
								break;
							}
							pInternetFile = pFtpConnection->OpenFile((szFileName = ExtractFTPFileName(szPathName)), GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII);
						}
						catch (CInternetException *pException)
						{
							szPathName = EMPTYSTRING;
							pException->Delete();
						}
						if (!szPathName.IsEmpty())
						{
							try
							{
								szDumpData = GetMemoryDumpsServiceSupport()->FormatMemoryDumpData(pMemoryDump, MEMORYDUMP_FILEFORMAT_NORMAL);
								if (GetMemoryDumpsService()->GetCharset() == MEMORYDUMPS_SERVICE_ASCIICHARSET)
								{
									if ((pszDumpData = (LPSTR)GlobalAlloc(GPTR, (szDumpData.GetLength() + 1)*sizeof(CHAR))))
									{
#ifndef UNICODE
										strcpy_s(pszDumpData, szDumpData.GetLength() + 1, szDumpData);
#else
										WideCharToMultiByte(CP_ACP, 0, szDumpData, -1, pszDumpData, szDumpData.GetLength() + 1, (LPSTR)NULL, (LPBOOL)NULL);
#endif
										pInternetFile->Write(pszDumpData, (UINT)(strlen(pszDumpData)*sizeof(CHAR)));
										pInternetFile->Close();
										GlobalFree(pszDumpData);
										delete pInternetFile;
										nFormats[0] |= MEMORYDUMP_FILEFORMAT_NORMAL;
									}
									else
									{
										pFtpConnection->Remove(szFileName);
										pInternetFile->Close();
										delete pInternetFile;
									}
								}
								else
								{
									if ((pszData = (LPWSTR)GlobalAlloc(GPTR, (szDumpData.GetLength() + 1)*sizeof(WCHAR))))
									{
#ifndef UNICODE
										MultiByteToWideChar(CP_ACP, 0, szDumpData, -1, pszData, szDumpData.GetLength() + 1);
#else
										wcscpy_s(pszData, szDumpData.GetLength() + 1, szDumpData);
#endif
										pInternetFile->Write(pszData, (UINT)(wcslen(pszData)*sizeof(WCHAR)));
										pInternetFile->Close();
										GlobalFree(pszData);
										delete pInternetFile;
										nFormats[0] |= MEMORYDUMP_FILEFORMAT_NORMAL;
									}
									else
									{
										pFtpConnection->Remove(szFileName);
										pInternetFile->Close();
										delete pInternetFile;
									}
								}
							}
							catch (CInternetException *pException)
							{
								pInternetFile->Close();
								pFtpConnection->Remove(szFileName);
								delete pInternetFile;
								pException->Delete();
							}
						}
					}
					if (nFormats[1] & MEMORYDUMP_FILEFORMAT_DESCRIPTIVE)
					{
						try
						{
							for (szDirectory = ExtractFTPDirectory((szPathName = GetMemoryDumpsServiceSupport()->GetMemoryDumpFTPFileName(pMemoryDump, MEMORYDUMP_FILEFORMAT_DESCRIPTIVE))); !szDirectory.IsEmpty(); )
							{
								pFtpConnection->SetCurrentDirectory(szDirectory);
								break;
							}
							pInternetFile = pFtpConnection->OpenFile((szFileName = ExtractFTPFileName(szPathName)), GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII);
						}
						catch (CInternetException *pException)
						{
							szPathName = EMPTYSTRING;
							pException->Delete();
						}
						if (!szPathName.IsEmpty())
						{
							try
							{
								szDumpData = GetMemoryDumpsServiceSupport()->FormatMemoryDumpData(pMemoryDump, MEMORYDUMP_FILEFORMAT_DESCRIPTIVE);
								if (GetMemoryDumpsService()->GetCharset() == MEMORYDUMPS_SERVICE_ASCIICHARSET)
								{
									if ((pszDumpData = (LPSTR)GlobalAlloc(GPTR, (szDumpData.GetLength() + 1)*sizeof(CHAR))))
									{
#ifndef UNICODE
										strcpy_s(pszDumpData, szDumpData.GetLength() + 1, szDumpData);
#else
										WideCharToMultiByte(CP_ACP, 0, szDumpData, -1, pszDumpData, szDumpData.GetLength() + 1, (LPSTR)NULL, (LPBOOL)NULL);
#endif
										pInternetFile->Write(pszDumpData, (UINT)(strlen(pszDumpData)*sizeof(CHAR)));
										pInternetFile->Close();
										GlobalFree(pszDumpData);
										delete pInternetFile;
										nFormats[0] |= MEMORYDUMP_FILEFORMAT_DESCRIPTIVE;
									}
									else
									{
										pFtpConnection->Remove(szFileName);
										pInternetFile->Close();
										delete pInternetFile;
									}
								}
								else
								{
									if ((pszData = (LPWSTR)GlobalAlloc(GPTR, (szDumpData.GetLength() + 1)*sizeof(WCHAR))))
									{
#ifndef UNICODE
										MultiByteToWideChar(CP_ACP, 0, szDumpData, -1, pszData, szDumpData.GetLength() + 1);
#else
										wcscpy_s(pszData, szDumpData.GetLength() + 1, szDumpData);
#endif
										pInternetFile->Write(pszData, (UINT)(wcslen(pszData)*sizeof(WCHAR)));
										pInternetFile->Close();
										GlobalFree(pszData);
										delete pInternetFile;
										nFormats[0] |= MEMORYDUMP_FILEFORMAT_DESCRIPTIVE;
									}
									else
									{
										pFtpConnection->Remove(szFileName);
										pInternetFile->Close();
										delete pInternetFile;
									}
								}
							}
							catch (CInternetException *pException)
							{
								pInternetFile->Close();
								pFtpConnection->Remove(szFileName);
								delete pInternetFile;
								pException->Delete();
							}
						}
					}
					if (nFormats[1] & MEMORYDUMP_FILEFORMAT_DELIMITED)
					{
						try
						{
							for (szDirectory = ExtractFTPDirectory((szPathName = GetMemoryDumpsServiceSupport()->GetMemoryDumpFTPFileName(pMemoryDump, MEMORYDUMP_FILEFORMAT_DELIMITED))); !szDirectory.IsEmpty(); )
							{
								pFtpConnection->SetCurrentDirectory(szDirectory);
								break;
							}
							pInternetFile = pFtpConnection->OpenFile((szFileName = ExtractFTPFileName(szPathName)), GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII);
						}
						catch (CInternetException *pException)
						{
							szPathName = EMPTYSTRING;
							pException->Delete();
						}
						if (!szPathName.IsEmpty())
						{
							try
							{
								szDumpData = GetMemoryDumpsServiceSupport()->FormatMemoryDumpData(pMemoryDump, MEMORYDUMP_FILEFORMAT_DELIMITED);
								if (GetMemoryDumpsService()->GetCharset() == MEMORYDUMPS_SERVICE_ASCIICHARSET)
								{
									if ((pszDumpData = (LPSTR)GlobalAlloc(GPTR, (szDumpData.GetLength() + 1)*sizeof(CHAR))))
									{
#ifndef UNICODE
										strcpy_s(pszDumpData, szDumpData.GetLength() + 1, szDumpData);
#else
										WideCharToMultiByte(CP_ACP, 0, szDumpData, -1, pszDumpData, szDumpData.GetLength() + 1, (LPSTR)NULL, (LPBOOL)NULL);
#endif
										pInternetFile->Write(pszDumpData, (UINT)(strlen(pszDumpData)*sizeof(CHAR)));
										pInternetFile->Close();
										GlobalFree(pszDumpData);
										delete pInternetFile;
										nFormats[0] |= MEMORYDUMP_FILEFORMAT_DELIMITED;
									}
									else
									{
										pFtpConnection->Remove(szFileName);
										pInternetFile->Close();
										delete pInternetFile;
									}
								}
								else
								{
									if ((pszData = (LPWSTR)GlobalAlloc(GPTR, (szDumpData.GetLength() + 1)*sizeof(WCHAR))))
									{
#ifndef UNICODE
										MultiByteToWideChar(CP_ACP, 0, szDumpData, -1, pszData, szDumpData.GetLength() + 1);
#else
										wcscpy_s(pszData, szDumpData.GetLength() + 1, szDumpData);
#endif
										pInternetFile->Write(pszData, (UINT)(wcslen(pszData)*sizeof(WCHAR)));
										pInternetFile->Close();
										GlobalFree(pszData);
										delete pInternetFile;
										nFormats[0] |= MEMORYDUMP_FILEFORMAT_DELIMITED;
									}
									else
									{
										pFtpConnection->Remove(szFileName);
										pInternetFile->Close();
										delete pInternetFile;
									}
								}
							}
							catch (CInternetException *pException)
							{
								pInternetFile->Close();
								pFtpConnection->Remove(szFileName);
								delete pInternetFile;
								pException->Delete();
							}
						}
					}
					if (nFormats[0] == nFormats[1])
					{
						if (nAudition == MEMORYDUMP_AUDITION_ALL)
						{
							szError[0].Format(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_SUCCESS), (LPCTSTR)szName, (LPCTSTR)szServer);
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
						}
						cMemoryDumps.RemoveAt(nDump);
						pFtpConnection->Close();
						delete pFtpConnection;
						delete pMemoryDump;
						nDumps--;
						nDump--;
						continue;
					}
					if (nRetries[0] > 0 && nRetries[1] > 0)
					{
						pMemoryDump->SetNotificationsFileFormats(nFormats[1] & ~nFormats[0]);
						pMemoryDump->SetFTPRetryCount((nRetries[1] != (UINT)-1) ? (nRetries[1] - 1) : nRetries[1]);
						pMemoryDump->SetFTPRetryTime(CTime::GetCurrentTime().GetTime() + tRetryInterval.GetTotalSeconds());
						dwWait[0] = (dwWait[0] > (DWORD)(1000 * tRetryInterval.GetTotalSeconds()) || dwWait[0] == INFINITE) ? (DWORD)(1000 * tRetryInterval.GetTotalSeconds()) : dwWait[0];
					}
					else
					{
						if (nAudition == MEMORYDUMP_AUDITION_ALL || nAudition == MEMORYDUMP_AUDITION_FAILURES)
						{
							szError[0].Format(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_DELIVERY_FAILURE), (LPCTSTR)szName, (LPCTSTR)szServer);
							szError[1].Format(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_DELIVERY_RETRIES_FAILURE), (LPCTSTR)szName, (LPCTSTR)szServer, nRetries[0]);
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, (!nRetries[0]) ? szError[0] : szError[1], FALSE);
						}
						cMemoryDumps.RemoveAt(nDump);
						delete pMemoryDump;
						nDumps--;
						nDump--;
					}
					pFtpConnection->Close();
					delete pFtpConnection;
					continue;
				}
				if (nRetries[0] > 0 && nRetries[0] > nRetries[1] && tRetryTime > CTime::GetCurrentTime())
				{
					dwWait[1] = (DWORD)(1000 * (tRetryTime.GetTime() - CTime::GetCurrentTime().GetTime()));
					dwWait[0] = (dwWait[0] <= dwWait[1] && dwWait[0] != INFINITE) ? dwWait[0] : dwWait[1];
				}
				continue;
			}
		}
		cMemoryDumps.RemoveAt(nDump);
		delete pMemoryDump;
		nDumps--;
		nDump--;
	}
	if (Lock())
	{
		if (nDumps >= 0)
		{
			m_pMemoryDumps.Copy(&cMemoryDumps, TRUE);
			Unlock();
			return dwWait[0];
		}
		Unlock();
	}
	return INFINITE;
}

INT CMemoryDumpsServiceThread::EnumFTPRecipients(CONST CMemoryDump *pDump, CStringArray &szServers, CStringArray &szDirectories, CStringArray &szUsers, CStringArray &szPasswords) CONST
{
	for (ExtractFTPRecipientsData(pDump->GetFTPServer(), szServers), ExtractFTPRecipientsData(pDump->GetFTPDirectory(), szDirectories), ExtractFTPRecipientsData(pDump->GetFTPUserName(), szUsers), ExtractFTPRecipientsData(pDump->GetFTPPassword(), szPasswords); szServers.GetSize() != szDirectories.GetSize() || szServers.GetSize() != szUsers.GetSize() || szServers.GetSize() != szPasswords.GetSize(); )
	{
		szDirectories.SetSize(szServers.GetSize());
		szPasswords.SetSize(szServers.GetSize());
		szUsers.SetSize(szServers.GetSize());
		break;
	}
	return((INT)szServers.GetSize());
}

INT CMemoryDumpsServiceThread::ExtractFTPRecipientsData(LPCTSTR pszData, CStringArray &szData) CONST
{
	INT  nPos[2];
	CString  szInfo;

	for (szInfo = pszData, szData.RemoveAll(); !szInfo.IsEmpty(); )
	{
		nPos[0] = szInfo.Find(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_RECIPIENTS_SEPARATOR_SEMICOLON));
		nPos[1] = szInfo.Find(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_RECIPIENTS_SEPARATOR_COMMA));
		if ((nPos[0] < nPos[1] || nPos[1] < 0) && nPos[0] >= 0)
		{
			szData.Add(szInfo.Left(nPos[0]));
			szInfo = szInfo.Mid(nPos[0]);
			szInfo = szInfo.Mid(lstrlen(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_RECIPIENTS_SEPARATOR_SEMICOLON)));
			continue;
		}
		if ((nPos[0] >= nPos[1] || nPos[0] < 0) && nPos[1] >= 0)
		{
			szData.Add(szInfo.Left(nPos[1]));
			szInfo = szInfo.Mid(nPos[1]);
			szInfo = szInfo.Mid(lstrlen(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_RECIPIENTS_SEPARATOR_COMMA)));
			continue;
		}
		szData.Add(szInfo);
		szInfo.Empty();
	}
	return((INT)szData.GetSize());
}

CString CMemoryDumpsServiceThread::ExtractFTPDirectory(LPCTSTR pszPathName) CONST
{
	INT  nPos;
	CString  szDirectory;

	for (nPos = lstrlen(pszPathName) - 1, szDirectory = pszPathName; nPos >= 0; nPos--)
	{
		if (pszPathName[nPos] == STRINGCHAR(IDS_INTERNET_DELIMITER)) break;
		continue;
	}
	for (szDirectory = szDirectory.Left(max(nPos, 0)); szDirectory.GetLength() > lstrlen(STRING(IDS_INTERNET_DELIMITER)) && szDirectory.Left(lstrlen(STRING(IDS_INTERNET_DELIMITER))) == STRING(IDS_INTERNET_DELIMITER); )
	{
		szDirectory = szDirectory.Mid(lstrlen(STRING(IDS_INTERNET_DELIMITER)));
		break;
	}
	return szDirectory;
}

CString CMemoryDumpsServiceThread::ExtractFTPFileName(LPCTSTR pszPathName) CONST
{
	INT  nPos;
	CString  szFileName;

	for (nPos = lstrlen(pszPathName) - 1, szFileName = pszPathName; nPos >= 0; nPos--)
	{
		if (pszPathName[nPos] == STRINGCHAR(IDS_INTERNET_DELIMITER)) break;
		continue;
	}
	szFileName = (nPos >= 0) ? szFileName.Mid(nPos + lstrlen(STRING(IDS_INTERNET_DELIMITER))) : szFileName;
	return szFileName;
}

int CMemoryDumpsServiceThread::Run()
{
	UINT  nCode;
	DWORD  dwWait[2];
	DWORD  dwResult;
	CString  szText;
	CTimeKey  tTime[2];
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	HANDLE  bUpdate = (HANDLE)GetThreadInfo();

	do
	{
		if (GetMemoryDumpsService()->GetAvailabilityInfo(nCode, tStartTime, tStopTime))
		{
			tTime[0] = tTime[1] = CTime::GetCurrentTime().GetTime();
			tTime[1] = tTime[1].GetTime() + tTime[1].GetBias();
			if (nCode & MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY)
			{
				if (tTime[1].GetDayOfWeek() != Monday  &&  tTime[1].GetDayOfWeek() != Tuesday  &&  tTime[1].GetDayOfWeek() != Wednesday  &&  tTime[1].GetDayOfWeek() != Thursday  &&  tTime[1].GetDayOfWeek() != Friday)
				{
					ReportEvent((m_bAvailable && (nCode & MEMORYDUMPS_SERVICE_AUDITAVAILABILITY)) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, (m_bAvailable && (nCode & MEMORYDUMPS_SERVICE_AUDITAVAILABILITY)) ? STRING(IDS_MEMORYDUMPS_SCHEDULE_INACTIVEWEEKDAYS) : EMPTYSTRING, FALSE);
					dwWait[0] = (DWORD)(1000 * (SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY + 1) - tTime[0].GetTime()));
					m_bAvailable = FALSE;
					continue;
				}
				dwWait[0] = (DWORD)(1000 * (SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY + 1) - tTime[0].GetTime()));
			}
			if (nCode & MEMORYDUMPS_SERVICE_DAILYAVAILABILITY)
			{
				if (tTime[0].GetTime() % SECONDSPERDAY < tStartTime.GetTotalSeconds() || tTime[0].GetTime() % SECONDSPERDAY > tStopTime.GetTotalSeconds())
				{
					szText.Format(STRING(IDS_MEMORYDUMPS_SCHEDULE_INACTIVEDAILY), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY) + tStartTime.GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY) + tStopTime.GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT));
					ReportEvent((m_bAvailable && (nCode & MEMORYDUMPS_SERVICE_AUDITAVAILABILITY)) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, (m_bAvailable && (nCode & MEMORYDUMPS_SERVICE_AUDITAVAILABILITY)) ? (LPCTSTR)szText : EMPTYSTRING, FALSE);
					dwWait[0] = (tTime[0].GetTime() % SECONDSPERDAY > tStopTime.GetTotalSeconds()) ? (DWORD)(1000 * (SECONDSPERDAY - tTime[0].GetTime() % SECONDSPERDAY + tStartTime.GetTotalSeconds())) : (DWORD)(1000 * (tStartTime.GetTotalSeconds() - tTime[0].GetTime() % SECONDSPERDAY));
					m_bAvailable = FALSE;
					continue;
				}
				dwWait[0] = (DWORD)(1000 * (tStopTime.GetTotalSeconds() - tTime[0].GetTime() % SECONDSPERDAY));
			}
			if ((nCode & MEMORYDUMPS_SERVICE_DAILYAVAILABILITY) || (nCode & MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY))
			{
				ReportEvent((!m_bAvailable && (nCode & MEMORYDUMPS_SERVICE_AUDITAVAILABILITY)) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, (!m_bAvailable && (nCode & MEMORYDUMPS_SERVICE_AUDITAVAILABILITY)) ? STRING(IDS_MEMORYDUMPS_SCHEDULE_ACTIVATED) : EMPTYSTRING, FALSE);
				m_bAvailable = TRUE;
			}
			dwWait[1] = FTPTransfers();
			dwWait[0] = ((nCode & MEMORYDUMPS_SERVICE_DAILYAVAILABILITY) || (nCode & MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY)) ? ((dwWait[0] < dwWait[1] || dwWait[1] == INFINITE) ? dwWait[0] : dwWait[1]) : dwWait[1];
			continue;
		}
		break;
	} while ((dwResult = Wait(bUpdate, FALSE, dwWait[0])) == WAIT_TIMEOUT || dwResult == WAIT_OBJECT_0 + 1);
	return 0;
}

BEGIN_MESSAGE_MAP(CMemoryDumpsServiceThread, CThread)
	//{{AFX_MSG_MAP(CMemoryDumpsServiceThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsServiceThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsService

CMemoryDumpsService::CMemoryDumpsService() : CObject()
{
	m_nCode = MEMORYDUMPS_SERVICE_UNLIMITEDAVAILABILITY;
	m_nCharset = MEMORYDUMPS_SERVICE_ASCIICHARSET;
	m_tStartTime = 0;
	m_tStopTime = 0;
}

BOOL CMemoryDumpsService::Start()
{
	CByteArray  nDumps;
	CMemoryDumpsServiceEngine  *pMemoryDumpsServiceSupport;
	CProfile  cProfile;

	if ((pMemoryDumpsServiceSupport = GetMemoryDumpsServiceSupport()) && pMemoryDumpsServiceSupport->IsServiceSupported())
	{
		if (cProfile.GetMemoryDumpsServiceSettingsInfo(m_nCharset) && cProfile.GetMemoryDumpsServiceAvailabilityInfo(m_nCode, m_tStartTime, m_tStopTime) && cProfile.GetMemoryDumpsServiceDumpInfo(nDumps) && m_pMemoryDumps.Unmap(nDumps))
		{
			if (m_cServiceThread.Start(m_bUpdate))
			{
				m_bUpdate.SetEvent();
				return TRUE;
			}
		}
		ReportEvent(SYSTEM_WARNING_MEMORYDUMPSSERVICE_LOAD_FAILURE);
	}
	return FALSE;
}

BOOL CMemoryDumpsService::Stop()
{
	CByteArray  nDumps;
	CMemoryDumpsServiceEngine  *pMemoryDumpsServiceSupport;
	CProfile  cProfile;

	if ((pMemoryDumpsServiceSupport = GetMemoryDumpsServiceSupport()) && pMemoryDumpsServiceSupport->IsServiceSupported())
	{
		for (m_cServiceThread.Stop(); m_pMemoryDumps.Map(nDumps) && cProfile.SetMemoryDumpsServiceSettingsInfo(m_nCharset) && cProfile.SetMemoryDumpsServiceAvailabilityInfo(m_nCode, m_tStartTime, m_tStopTime) && cProfile.SetMemoryDumpsServiceDumpInfo(nDumps); ) return TRUE;
		ReportEvent(SYSTEM_WARNING_MEMORYDUMPSSERVICE_SAVE_FAILURE);
	}
	return FALSE;
}

BOOL CMemoryDumpsService::SetCharset(UINT nCharset)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nCharset == MEMORYDUMPS_SERVICE_ASCIICHARSET || nCharset == MEMORYDUMPS_SERVICE_UNICODECHARSET)
	{
		m_nCharset = nCharset;
		return TRUE;
	}
	return FALSE;
}

BOOL CMemoryDumpsService::GetCharset(UINT &nCharset) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nCharset = m_nCharset;
	return TRUE;
}
UINT CMemoryDumpsService::GetCharset() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_nCharset;
}

BOOL CMemoryDumpsService::SetAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nCode & MEMORYDUMPS_SERVICE_NOAVAILABILITY)
	{
		m_nCode = MEMORYDUMPS_SERVICE_NOAVAILABILITY;
		m_tStartTime = 0;
		m_tStopTime = 0;
		return m_bUpdate.SetEvent();
	}
	if (nCode & MEMORYDUMPS_SERVICE_UNLIMITEDAVAILABILITY)
	{
		m_nCode = nCode & (MEMORYDUMPS_SERVICE_UNLIMITEDAVAILABILITY | MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY | MEMORYDUMPS_SERVICE_AUDITAVAILABILITY);
		m_tStartTime = 0;
		m_tStopTime = 0;
		return m_bUpdate.SetEvent();
	}
	if ((nCode & MEMORYDUMPS_SERVICE_DAILYAVAILABILITY) && tStartTime < tStopTime)
	{
		m_nCode = nCode & (MEMORYDUMPS_SERVICE_DAILYAVAILABILITY | MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY | MEMORYDUMPS_SERVICE_AUDITAVAILABILITY);
		m_tStartTime = tStartTime;
		m_tStopTime = tStopTime;
		return m_bUpdate.SetEvent();
	}
	return FALSE;
}

BOOL CMemoryDumpsService::GetAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nCode = m_nCode;
	tStartTime = m_tStartTime;
	tStopTime = m_tStopTime;
	return TRUE;
}

BOOL CMemoryDumpsService::SetMemoryDumps(CONST CMemoryDumps &pMemoryDumps)
{
	INT  nDump[2];
	INT  nDumps[2];
	CMemoryDump  *pMemoryDump[2];
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	for (nDump[0] = 0, nDumps[0] = (INT)pMemoryDumps.GetSize(); nDump[0] < nDumps[0]; nDump[0]++)
	{
		if ((pMemoryDump[0] = (CMemoryDump *)pMemoryDumps.GetAt(nDump[0])) != (CMemoryDump *)NULL)
		{
			if ((pMemoryDump[1] = m_pMemoryDumps.GetAt(m_pMemoryDumps.Find(pMemoryDump[0]->GetName()))))
			{
				pMemoryDump[1]->Copy(pMemoryDump[0]);
				continue;
			}
			if ((pMemoryDump[1] = new CMemoryDump))
			{
				pMemoryDump[1]->SetName(pMemoryDump[0]->GetName());
				if (m_pMemoryDumps.Add(pMemoryDump[1]) >= 0)
				{
					pMemoryDump[1]->Copy(pMemoryDump[0]);
					continue;
				}
				delete pMemoryDump[1];
			}
		}
		break;
	}
	for (nDump[1] = 0, nDumps[1] = (INT)m_pMemoryDumps.GetSize(); nDump[1] < nDumps[1]; nDump[1]++)
	{
		if ((pMemoryDump[1] = m_pMemoryDumps.GetAt(nDump[1])))
		{
			if (pMemoryDumps.Find(pMemoryDump[1]->GetName()) < 0)
			{
				m_pMemoryDumps.RemoveAt(nDump[1]);
				delete pMemoryDump[1];
				nDumps[1]--;
				nDump[1]--;
			}
		}
	}
	return((nDump[0] == nDumps[0]) ? TRUE : FALSE);
}

BOOL CMemoryDumpsService::GetMemoryDumps(CMemoryDumps &pMemoryDumps) CONST
{
	CByteArray  nDumps;
	CProfile  cProfile;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((m_pMemoryDumps.GetSize() > 0) ? pMemoryDumps.Copy(&m_pMemoryDumps) : (m_cServiceThread.IsThreadActive() || (cProfile.GetMemoryDumpsServiceDumpInfo(nDumps) && pMemoryDumps.Unmap(nDumps))));
}

UINT CMemoryDumpsService::Update(CTMEnvironment *pTMEnvironment)
{
	return Update(pTMEnvironment, m_pMemoryDumps);
}
UINT CMemoryDumpsService::Update(CTMEnvironment *pTMEnvironment, CMemoryDumps &pMemoryDumps)
{
	INT  nDump[2];
	INT  nDumps[2];
	INT  nCount[2];
	UINT  nAddress[2][2][2];
	CString  szAudit;
	CString  szDumps;
	CString  szError;
	CTimeKey  tTime[2];
	CMemoryDump  *pMemoryDump[2];
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (pTMEnvironment->Lock())
	{
		for (tTime[0] = tTime[0].GetTime() + tTime[0].GetBias(); (m_nCode & MEMORYDUMPS_SERVICE_NOAVAILABILITY) != MEMORYDUMPS_SERVICE_NOAVAILABILITY && ((m_nCode & MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY) != MEMORYDUMPS_SERVICE_WORKINGDAYSAVAILABILITY || tTime[0].GetDayOfWeek() == Monday || tTime[0].GetDayOfWeek() == Tuesday || tTime[0].GetDayOfWeek() == Wednesday || tTime[0].GetDayOfWeek() == Thursday || tTime[0].GetDayOfWeek() == Friday) && ((m_nCode & MEMORYDUMPS_SERVICE_DAILYAVAILABILITY) != MEMORYDUMPS_SERVICE_DAILYAVAILABILITY || (tTime[1].GetTime() % SECONDSPERDAY >= m_tStartTime.GetTotalSeconds() && tTime[1].GetTime() % SECONDSPERDAY <= m_tStopTime.GetTotalSeconds())); )
		{
			for (nDump[0] = 0, nDumps[0] = (INT)pTMEnvironment->GetMemoryDumps()->GetSize(), szDumps.Empty(); nDump[0] < nDumps[0]; nDump[0] = nDump[0] + 1)
			{
				if ((pMemoryDump[0] = pTMEnvironment->GetMemoryDumps()->GetAt(nDump[0])) && pMemoryDump[0]->GetName().Find(TAB) < 0 && pMemoryDump[0]->GetDumpStatus() == MEMORYDUMP_STATUS_COLLECTING)
				{
					if (pTMEnvironment->GetTMUnit()->GetTimeTag().GetTimeInSeconds() > pMemoryDump[0]->GetDumpTime(FALSE).GetTimeInSeconds() + (GetMemoryDumpsServiceSupport()->GetMemoryDumpInterval(pMemoryDump[0]->GetDataSource(), pMemoryDump[0]->GetDataSourceSubSystem()).GetTotalSeconds()*(GetMemoryDumpsServiceSupport()->GetMemoryDumpIntervalTolerance(pMemoryDump[0]->GetDataSource(), pMemoryDump[0]->GetDataSourceSubSystem()) + 100)) / 100)
					{
						for (nDump[1] = 0, nDumps[1] = nDumps[0]; nDump[1] < nDumps[1]; nDump[1]++)
						{
							if ((pMemoryDump[1] = pTMEnvironment->GetMemoryDumps()->GetAt(nDump[1])))
							{
								if (pMemoryDump[0]->GetDataSourceSubSystem() == pMemoryDump[1]->GetDataSourceSubSystem())
								{
									if (pMemoryDump[0]->GetDataAddressRange(nAddress[0][0][0], nAddress[0][0][1], nAddress[0][1][0], nAddress[0][1][1]) && pMemoryDump[1]->GetDataAddressRange(nAddress[1][0][0], nAddress[1][0][1], nAddress[1][1][0], nAddress[1][1][1]) && nAddress[0][0][0] == nAddress[1][0][0] && nAddress[0][0][1] == nAddress[1][0][1] && (nAddress[0][1][0] > nAddress[1][1][0] || (nAddress[0][1][0] == nAddress[1][1][0] && nAddress[0][1][1] > nAddress[1][1][1])))
									{
										pMemoryDump[0]->SetDumpInfo(MEMORYDUMP_STATUS_EMPTY);
										break;
									}
								}
							}
						}
						if (nDump[1] == nDumps[1])
						{
							if (pMemoryDump[0]->SetDumpInfo(MEMORYDUMP_STATUS_INCOMPLETE))
							{
								GetMemoryDumpsServiceSupport()->ProcessTMDump(pMemoryDump[0], (m_nCharset == MEMORYDUMPS_SERVICE_UNICODECHARSET) ? TRUE : FALSE);
								szDumps += TAB + pMemoryDump[0]->GetName() + TAB;
							}
						}
					}
				}
			}
			for (nDump[0] = 0, nDumps[0] = (GetTMService()->IsTMDump(pTMEnvironment)) ? nDumps[0] : -1; nDump[0] < nDumps[0]; nDump[0]++)
			{
				if ((pMemoryDump[0] = pTMEnvironment->GetMemoryDumps()->GetAt(nDump[0])) != (CMemoryDump *)NULL)
				{
					if ((pMemoryDump[1] = pMemoryDumps.GetAt(pMemoryDumps.Find(pMemoryDump[0]->GetName()))) && !pMemoryDump[1]->Compare(pMemoryDump[0]))
					{
						if (pMemoryDump[0]->GetDataAddressRange(nAddress[0][0][0], nAddress[0][0][1], nAddress[0][1][0], nAddress[0][1][1]) && pMemoryDump[1]->GetDataAddressRange(nAddress[1][0][0], nAddress[1][0][1], nAddress[1][1][0], nAddress[1][1][1]))
						{
							if (pMemoryDump[0]->GetDataSource() == pMemoryDump[1]->GetDataSource() && nAddress[0][0][0] == nAddress[1][0][0] && nAddress[0][0][1] == nAddress[1][0][1] && nAddress[0][1][0] == nAddress[1][1][0] && nAddress[0][1][1] == nAddress[1][1][1])
							{
								pMemoryDump[0]->Copy(pMemoryDump[1]);
								continue;
							}
							pMemoryDump[0]->SetDumpInfo(pMemoryDump[1], MEMORYDUMP_STATUS_EMPTY);
						}
					}
					continue;
				}
				pTMEnvironment->GetMemoryDumps()->RemoveAt(nDump[0]);
				delete pMemoryDump[0];
				nDumps[0]--;
				nDump[0]--;
			}
			for (nDump[0] = 0, nDumps[0] = (nDumps[0] >= 0) ? ((GetMemoryDumpsServiceSupport()->ProcessTMUnit(pTMEnvironment, pMemoryDumps, (m_nCharset == MEMORYDUMPS_SERVICE_UNICODECHARSET) ? TRUE : FALSE) >= 0) ? nDumps[0] : 0) : (INT)(!szDumps.IsEmpty()*pTMEnvironment->GetMemoryDumps()->GetSize()); nDump[0] < nDumps[0]; nDump[0]++)
			{
				if ((pMemoryDump[0] = pTMEnvironment->GetMemoryDumps()->GetAt(nDump[0])) != (CMemoryDump *)NULL)
				{
					if ((pMemoryDump[1] = pMemoryDumps.GetAt(pMemoryDumps.Find(pMemoryDump[0]->GetName()))))
					{
						if (pMemoryDump[0]->GetDumpStatus() == MEMORYDUMP_STATUS_COMPLETE || pMemoryDump[0]->GetDumpStatus() == MEMORYDUMP_STATUS_INCOMPLETE)
						{
							if (pMemoryDump[0]->GetDumpTag() != pMemoryDump[1]->GetDumpTag() || pMemoryDump[0]->GetDumpTime().GetTime() != pMemoryDump[1]->GetDumpTime().GetTime() || pMemoryDump[0]->GetDumpStatus() != pMemoryDump[1]->GetDumpStatus())
							{
								if (pMemoryDump[0]->GetArchivingRetentionOptions() & MEMORYDUMP_RETENTION_ENABLED)
								{
									if (pMemoryDump[0]->GetArchivingRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYCOUNT)
									{
										for (nCount[0] = pMemoryDump[0]->GetArchivingRetentionCount(); nCount[0] >= 0; )
										{
											pMemoryDump[1]->SetArchivingRetentionCount(nCount[0]);
											break;
										}
									}
									if (((pMemoryDump[0]->GetArchivingRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYCOUNT) && !pMemoryDump[0]->GetArchivingRetentionCount()) || ((pMemoryDump[0]->GetArchivingRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYTIME) && pMemoryDump[0]->GetArchivingRetentionByTime() < tTime[1]))
									{
										pMemoryDump[0]->SetArchivingRetentionOptions(0);
										pMemoryDump[1]->SetArchivingRetentionOptions(0);
										pMemoryDump[0]->SetArchivingRetentionByCount(0);
										pMemoryDump[1]->SetArchivingRetentionByCount(0);
										pMemoryDump[0]->SetArchivingRetentionByTime(0);
										pMemoryDump[1]->SetArchivingRetentionByTime(0);
									}
								}
								for (Alert(pMemoryDump[0], (pMemoryDump[0]->GetDumpStatus() == MEMORYDUMP_STATUS_COMPLETE) ? TRUE : FALSE); pMemoryDump[1]->GetAuditionFlag(); )
								{
									szAudit.Format((pMemoryDump[0]->GetDumpStatus() == MEMORYDUMP_STATUS_COMPLETE) ? STRING(IDS_MEMORYDUMPS_AUDITION_SUCCESS) : ((szDumps.Find(TAB + pMemoryDump[0]->GetName() + TAB) >= 0) ? STRING(IDS_MEMORYDUMPS_AUDITION_TIMEOUT) : STRING(IDS_MEMORYDUMPS_AUDITION_FAILURE)), (LPCTSTR)pMemoryDump[0]->GetName());
									ReportEvent(EVENT_CATEGORY_SPACECRAFT | EVENT_TYPE_INFORMATIONAL, szAudit, FALSE);
									break;
								}
								if (pMemoryDump[0]->GetNotificationsRetentionOptions() & MEMORYDUMP_RETENTION_ENABLED)
								{
									if ((pMemoryDump[0]->GetNotificationsRetentionOptions() & (MEMORYDUMP_RETENTION_STOPBYCOUNT | MEMORYDUMP_RETENTION_STOPBYTIME)) == 0 || ((pMemoryDump[0]->GetNotificationsRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYCOUNT) && pMemoryDump[0]->GetNotificationsRetentionCount() > 0) || ((pMemoryDump[0]->GetNotificationsRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYTIME) && pMemoryDump[0]->GetNotificationsRetentionByTime() >= tTime[1]))
									{
										if (!m_cServiceThread.DoFTPTransfer(pMemoryDump[0]) && (pMemoryDump[1]->GetFTPAudition() == MEMORYDUMP_AUDITION_ALL || pMemoryDump[1]->GetFTPAudition() == MEMORYDUMP_AUDITION_FAILURES))
										{
											szError.Format(STRING(IDS_MEMORYDUMPS_FTPTRANSFER_FAILURE), (LPCTSTR)pMemoryDump[0]->GetName());
											ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
											continue;
										}
										if (pMemoryDump[0]->GetNotificationsRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYCOUNT)
										{
											if ((nCount[1] = pMemoryDump[0]->GetNotificationsRetentionCount()) > 0)
											{
												pMemoryDump[0]->SetNotificationsRetentionCount(nCount[1] - 1);
												pMemoryDump[1]->SetNotificationsRetentionCount(nCount[1] - 1);
											}
										}
									}
									if (((pMemoryDump[0]->GetNotificationsRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYCOUNT) && !pMemoryDump[0]->GetNotificationsRetentionCount()) || ((pMemoryDump[0]->GetNotificationsRetentionOptions() & MEMORYDUMP_RETENTION_STOPBYTIME) && pMemoryDump[0]->GetNotificationsRetentionByTime() < tTime[1]))
									{
										pMemoryDump[0]->SetNotificationsRetentionOptions(0);
										pMemoryDump[1]->SetNotificationsRetentionOptions(0);
										pMemoryDump[0]->SetNotificationsRetentionByCount(0);
										pMemoryDump[1]->SetNotificationsRetentionByCount(0);
										pMemoryDump[0]->SetNotificationsRetentionByTime(0);
										pMemoryDump[1]->SetNotificationsRetentionByTime(0);
									}
								}
							}
							pMemoryDump[1]->SetDumpInfo(pMemoryDump[0], -1);
							continue;
						}
						if (pMemoryDump[0]->GetDumpStatus() == MEMORYDUMP_STATUS_COLLECTING)
						{
							pMemoryDump[1]->SetDumpInfo(pMemoryDump[0], -1);
							continue;
						}
					}
				}
			}
			for (pTMEnvironment->Unlock(), Unlock(); nDump[0] != nDumps[0]; )
			{
				ReportEvent(SYSTEM_WARNING_MEMORYDUMPSSERVICE_GENERAL_FAILURE);
				return MEMORYDUMPS_SERVICE_ERROR;
			}
			return MEMORYDUMPS_SERVICE_SUCCESS;
		}
		pTMEnvironment->Unlock();
		return MEMORYDUMPS_SERVICE_NOTAVAILABLE;
	}
	return MEMORYDUMPS_SERVICE_ERROR;
}

VOID CMemoryDumpsService::Alert(CONST CMemoryDump *pDump, BOOL bSuccess)
{
	CString  szMessage[2];
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
	{
		if ((pAlertInfo[1] = (bSuccess) ? pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_MEMORY_DUMPS_PROCESSING_SUCCESS))) : pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_MEMORY_DUMPS_PROCESSING_FAILURE)))))
		{
			szMessage[0].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_MEMORY_DUMPS_PROCESSING_SUCCESS), (LPCTSTR)pDump->GetName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)cComputerToken.GetComputerName());
			szMessage[1].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_MEMORY_DUMPS_PROCESSING_FAILURE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)pDump->GetName());
			if (pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_MEMORY_DUMPS_PROCESSING_SUCCESS) && pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_MEMORY_DUMPS_PROCESSING_FAILURE))
			{
				szMessage[0] = pAlertInfo[1]->GetMessage();
				szMessage[1] = pAlertInfo[1]->GetMessage();
			}
			pAlertInfo[0]->Copy(pAlertInfo[1]);
			pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
			pAlertInfo[0]->SetType((bSuccess) ? EVENT_TYPE_SUCCESS : EVENT_TYPE_WARNING);
			pAlertInfo[0]->SetMessage((bSuccess) ? szMessage[0] : szMessage[1]);
			pAlertInfo[0]->SetExtraInfo(pDump->GetOutputFiles());
			ReportEvent(pAlertInfo[0]);
		}
		delete pAlertInfo[0];
	}
}

BOOL CMemoryDumpsService::SetServiceInfo(CONST CByteArray &nInfo)
{
	CByteArray  nServiceInfo;
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nInfo.GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nInfo.GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbDumps && sServiceInfo.cbDumps >= 0; )
		{
			for (nServiceInfo.SetSize(sServiceInfo.cbDumps), CopyMemory(nServiceInfo.GetData(), nInfo.GetData() + sizeof(SERVICEINFO), sServiceInfo.cbDumps); m_pMemoryDumps.Unmap(nServiceInfo); )
			{
				m_tStartTime = sServiceInfo.tStartTime;
				m_tStopTime = sServiceInfo.tStopTime;
				m_nCharset = sServiceInfo.nCharset;
				m_nCode = sServiceInfo.nCode;
				return TRUE;
			}
			break;
		}
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CMemoryDumpsService::GetServiceInfo(CByteArray &nInfo) CONST
{
	CByteArray  nServiceInfo;
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (m_pMemoryDumps.Map(nServiceInfo))
	{
		nInfo.SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbDumps = (INT)nServiceInfo.GetSize()))));
		sServiceInfo.nCode = m_nCode;
		sServiceInfo.nCharset = m_nCharset;
		sServiceInfo.tStartTime = m_tStartTime.GetTotalSeconds();
		sServiceInfo.tStopTime = m_tStopTime.GetTotalSeconds();
		CopyMemory(nInfo.GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO), nServiceInfo.GetData(), nServiceInfo.GetSize());
		return TRUE;
	}
	return FALSE;
}

BOOL CMemoryDumpsService::UpdateServiceInfo(BOOL bSave)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((bSave  &&  SaveServiceInfo()) || (!bSave  &&  LoadServiceInfo()));
}

BOOL CMemoryDumpsService::ResetFTPQueue()
{
	return m_cServiceThread.ResetFTPQueue();
}

BOOL CMemoryDumpsService::IsAvailable() CONST
{
	CMemoryDumpsServiceEngine  *pMemoryDumpsServiceSupport;

	return(((pMemoryDumpsServiceSupport = GetMemoryDumpsServiceSupport()) && pMemoryDumpsServiceSupport->IsServiceSupported()) ? TRUE : FALSE);
}

BOOL CMemoryDumpsService::SaveServiceInfo()
{
	CByteArray  nServiceInfo[2];
	SERVICEINFO  sServiceInfo;
	CProfile  cProfile;

	if (GetServiceInfo(nServiceInfo[0]) && nServiceInfo[0].GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nServiceInfo[0].GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbDumps && sServiceInfo.cbDumps >= 0; )
		{
			nServiceInfo[1].SetSize(sServiceInfo.cbDumps);
			CopyMemory(nServiceInfo[1].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO), sServiceInfo.cbDumps);
			return cProfile.SetMemoryDumpsServiceSettingsInfo(sServiceInfo.nCharset) && cProfile.SetMemoryDumpsServiceAvailabilityInfo(sServiceInfo.nCode, sServiceInfo.tStartTime, sServiceInfo.tStopTime) && cProfile.SetMemoryDumpsServiceDumpInfo(nServiceInfo[1]);
		}
	}
	return FALSE;
}

BOOL CMemoryDumpsService::LoadServiceInfo()
{
	UINT  nCode;
	UINT  nCharset;
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	CByteArray  nServiceInfo[2];
	SERVICEINFO  sServiceInfo;
	CProfile  cProfile;

	if (cProfile.GetMemoryDumpsServiceSettingsInfo(nCharset) && cProfile.GetMemoryDumpsServiceAvailabilityInfo(nCode, tStartTime, tStopTime) && cProfile.GetMemoryDumpsServiceDumpInfo(nServiceInfo[1]))
	{
		nServiceInfo[0].SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbDumps = (INT)nServiceInfo[1].GetSize()))));
		sServiceInfo.nCode = nCode;
		sServiceInfo.nCharset = nCharset;
		sServiceInfo.tStartTime = tStartTime.GetTotalSeconds();
		sServiceInfo.tStopTime = tStopTime.GetTotalSeconds();
		CopyMemory(nServiceInfo[0].GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO), nServiceInfo[1].GetData(), nServiceInfo[1].GetSize());
		return SetServiceInfo(nServiceInfo[0]);
	}
	return FALSE;
}

BOOL CMemoryDumpsService::Lock()
{
	return m_cServiceThread.m_pCriticalSection->Lock();
}

BOOL CMemoryDumpsService::Unlock()
{
	return m_cServiceThread.m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPDataProfile

VOID CTPEPDataProfile::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTPEPDataProfile::GetName() CONST
{
	return m_szName;
}

VOID CTPEPDataProfile::SetIDs(CONST CStringArray &szIDs)
{
	m_szIDs.Copy(szIDs);
}

INT CTPEPDataProfile::GetIDs(CStringArray &szIDs)
{
	szIDs.Copy(m_szIDs);
	return((INT)szIDs.GetSize());
}

VOID CTPEPDataProfile::Reset()
{
	m_szName.Empty();
	m_szIDs.RemoveAll();
}

VOID CTPEPDataProfile::Copy(CONST CTPEPDataProfile *pProfile)
{
	m_szName = pProfile->m_szName;
	m_szIDs.Copy(pProfile->m_szIDs);
}

BOOL CTPEPDataProfile::Compare(CONST CTPEPDataProfile *pProfile)
{
	INT  nID[2];
	INT  nIDs[2];

	for (nID[0] = 0, nIDs[0] = (pProfile->m_szName == m_szName && pProfile->m_szIDs.GetSize() == m_szIDs.GetSize()) ? (INT)m_szIDs.GetSize() : -1; nID[0] < nIDs[0]; nID[0]++)
	{
		for (nID[1] = 0, nIDs[1] = (INT)pProfile->m_szIDs.GetSize(); nID[1] < nIDs[1]; nID[1]++)
		{
			if (pProfile->m_szIDs.GetAt(nID[0]) == m_szIDs.GetAt(nID[1])) break;
			continue;
		}
		if (nID[1] == nIDs[1]) break;
	}
	return((nID[0] == nIDs[0]) ? TRUE : FALSE);
}

BOOL CTPEPDataProfile::Map(CByteArray &nInfo) CONST
{
	INT  nID;
	INT  nIDs;
	INT  cbData;
	DATA  sData;
	CByteArray  nIDData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	for (nID = 0, nIDs = (INT)m_szIDs.GetSize(), sData.cbIDs = 0; nID < nIDs; nID++, sData.cbIDs += cbData)
	{
		nIDData.SetSize(sData.cbIDs + (cbData = (m_szIDs.GetAt(nID).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nIDData.GetData() + sData.cbIDs, (LPCTSTR)m_szIDs.GetAt(nID), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbIDs)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), nIDData.GetData(), sData.cbIDs);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataProfile::Unmap(CONST CByteArray &nInfo)
{
	INT  cbID;
	INT  cbIDs;
	INT  cbData;
	DATA  sData;
	CByteArray  nIDData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbIDs && sData.cbName > 0 && sData.cbIDs >= 0; )
	{
		for (CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), nIDData.SetSize(sData.cbIDs), CopyMemory(nIDData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbName), sData.cbIDs), m_szName.ReleaseBuffer(), m_szIDs.RemoveAll(), cbID = cbIDs = 0; cbIDs < sData.cbIDs; cbIDs += (cbID = (m_szIDs.GetAt(m_szIDs.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szIDs.Add((LPCTSTR)(nIDData.GetData() + cbIDs));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPDataProfiles

CTPEPDataProfiles::CTPEPDataProfiles() : CPtrArray()
{
	return;
}

CTPEPDataProfiles::~CTPEPDataProfiles()
{
	RemoveAll();
}

INT CTPEPDataProfiles::Add(CTPEPDataProfile *pProfile)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfile->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfile, 1);
	return nIndex;
}

INT CTPEPDataProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CTPEPDataProfile *CTPEPDataProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPDataProfile *)CPtrArray::GetAt(nIndex) : (CTPEPDataProfile *)NULL);
}

CTPEPDataProfile *CTPEPDataProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPDataProfile *)CPtrArray::GetAt(nIndex) : (CTPEPDataProfile *)NULL);
}

VOID CTPEPDataProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;
	CTPEPDataProfile  *pProfile;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfile = GetAt(nProfile))) delete pProfile;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTPEPDataProfiles::Copy(CONST CTPEPDataProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CTPEPDataProfile  *pProfile;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfile = new CTPEPDataProfile))
		{
			pProfile->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfile, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CTPEPDataProfiles::Compare(CONST CTPEPDataProfiles *pProfiles) CONST
{
	INT  nProfile[2];
	INT  nProfiles[2];

	for (nProfile[0] = 0, nProfiles[0] = (INT)GetSize(), nProfiles[1] = (INT)pProfiles->GetSize(); nProfile[0] < nProfiles[0] && nProfiles[0] == nProfiles[1]; nProfile[0]++)
	{
		for (nProfile[1] = 0; nProfile[1] < nProfiles[1]; nProfile[1] = nProfile[1] + 1)
		{
			if (pProfiles->GetAt(nProfile[0])->Compare(GetAt(nProfile[1]))) break;
			continue;
		}
		if (nProfile[1] == nProfiles[1]) break;
	}
	return((nProfile[0] == nProfiles[0] && nProfiles[0] == nProfiles[1]) ? TRUE : FALSE);
}

BOOL CTPEPDataProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfileData;
	CTPEPDataProfile  *pProfile;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfile = GetAt(nProfile)) && pProfile->Map(nProfileData) && nInfo.Append(nProfileData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CTPEPDataProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfileData;
	CTPEPDataProfile  *pProfile;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfileData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfileData.GetSize() >= 0; )
		{
			CopyMemory(nProfileData.GetData(), nInfo.GetData() + cbProfiles, nProfileData.GetSize());
			break;
		}
		if ((pProfile = new CTPEPDataProfile))
		{
			if (pProfile->Unmap(nProfileData) && Add(pProfile) >= 0) continue;
			delete pProfile;
		}
		break;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTPEPDataProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTPEPDataProfile  *pProfile;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfile = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfile->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfile = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfile->GetName() == pszName) || (bInsert && (((pProfile = GetAt(max(nIndex[0] - 1, 0))) && pProfile->GetName() != pszName && (pProfile = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pProfile->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPServerThread

IMPLEMENT_DYNCREATE(CTPEPServerThread, CThread)

CTPEPServerThread::CTPEPServerThread() : CThread()
{
	return;
}

CTPEPServerThread::~CTPEPServerThread()
{
	DestroyThread();
}

BOOL CTPEPServerThread::Start(CONST CTPEPConnection *pConnection)
{
	if (CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL, TRUE))
	{
		m_cConnection.Copy(pConnection);
		ResumeThread();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPServerThread::Stop()
{
	return SetEvent(m_hObject);
}

int CTPEPServerThread::Run()
{
	INT  nSample;
	INT  nSamples;
	UINT  nResult;
	DWORD  dwResult;
	CTimeKey  tTimeKey;
	CString  szFileName;
	CStringArray  szSamples;
	CHistoryStoreFile  cFile;

	if (m_cTMEnvironment.Create(GetDatabase()))
	{
		if (m_cConnection.GetDataMode() == TPEP_DATAMODE_HISTORY)
		{
			if (m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), (GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile)) ? (LPCTSTR)cFile.GetFileName() : EMPTYSTRING, &m_cTMEnvironment))
			{
				if (((nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = m_cConnection.GetRetrieveStartTime()))) & HISTORYFILE_SUCCESS) == HISTORYFILE_SUCCESS)
				{
					if (((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) && Update(&m_cTMEnvironment, 0, TRUE) && m_cConnection.GetDataLink() == TPEP_DATALINK_HOT  &&  m_cConnection.GetRetrieveStopTime() >= tTimeKey)
					{
						for (; (dwResult = Wait(10 * (10 - m_cConnection.GetRetrieveSpeed())*(10 - m_cConnection.GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
						{
							if ((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)
							{
								if ((nResult & HISTORYFILE_TMUNIT) && m_cConnection.GetRetrieveStopTime() >= tTimeKey)
								{
									if (!Update(&m_cTMEnvironment)) break;
									continue;
								}
								if ((nResult & HISTORYFILE_TMPARAMETERS) && m_cConnection.GetRetrieveStopTime() >= tTimeKey) continue;
							}
							break;
						}
					}
				}
				if ((nResult & HISTORYFILE_SUCCESS) || (nResult & HISTORYFILE_DATA_NONE))
				{
					for (; (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS) && m_cConnection.GetRetrieveStopTime() >= tTimeKey) || (nResult & HISTORYFILE_DATA_NONE); )
					{
						Update(&m_cTMEnvironment, TPEP_ERROR_NODATA);
						break;
					}
					m_cTMProcessEngine.Close();
					m_cTMEnvironment.Destroy();
					Update(&m_cTMEnvironment);
					return 0;
				}
				m_cTMProcessEngine.Close();
			}
			m_cTMEnvironment.Destroy();
			Update(&m_cTMEnvironment, TPEP_ERROR_FAILURE);
			Update(&m_cTMEnvironment);
			return 0;
		}
		if (m_cConnection.GetDataMode() == TPEP_DATAMODE_RANDOM)
		{
			for (nSample = 0, nSamples = (PrepareRandomData(szSamples)) ? (INT)szSamples.GetSize() : -1; nSample < nSamples; nSample++)
			{
				if (GenerateRandomData(szSamples.GetAt(nSample), &m_cTMEnvironment))
				{
					if (m_cConnection.GetType() == TPEP_TYPE_PARAMETERS  &&  nSample > 0) break;
					if (!Update(&m_cTMEnvironment)) break;
					continue;
				}
				nSamples = -1;
				break;
			}
			if (m_cConnection.GetDataLink() == TPEP_DATALINK_HOT)
			{
				for (nSample = 0; ((dwResult = Wait(rand() % (TPEPSERVERTHREAD_RANDOMDATA_MAXIMUMINTERVAL - TPEPSERVERTHREAD_RANDOMDATA_MINIMUMINTERVAL) + TPEPSERVERTHREAD_RANDOMDATA_MINIMUMINTERVAL)) == WAIT_TIMEOUT) && nSamples > 0; nSample = max((nSample + 1) % nSamples, 1))
				{
					if (GenerateRandomData(szSamples.GetAt(rand() % nSamples), &m_cTMEnvironment))
					{
						if (!Update(&m_cTMEnvironment)) break;
						continue;
					}
					nSamples = -1;
					break;
				}
			}
			if (nSamples > 0)
			{
				m_cTMEnvironment.Destroy();
				Update(&m_cTMEnvironment);
				return 0;
			}
			Update(&m_cTMEnvironment, TPEP_ERROR_FAILURE);
		}
		m_cTMEnvironment.Destroy();
	}
	Update(&m_cTMEnvironment);
	return 0;
}

BOOL CTPEPServerThread::PrepareRandomData(CStringArray &szSamples)
{
	CStringArray  szParameters;

	switch (m_cConnection.GetType())
	{
	case TPEP_TYPE_PACKETS:
	{ return((m_cConnection.GetPackets(szSamples) > 0) ? TRUE : FALSE);
	break;
	}
	case TPEP_TYPE_PARAMETERS:
	{ return((m_cConnection.GetParameters(szParameters) > 0) ? ((GetTPEPServiceSupport()->EnumTPEPTMUnits(GetDatabase(), szParameters, szSamples) > 0) ? TRUE : FALSE) : FALSE);
	break;
	}
	}
	return FALSE;
}

BOOL CTPEPServerThread::GenerateRandomData(LPCTSTR pszSample, CTMEnvironment *pTMEnvironment)
{
	pTMEnvironment->GetTMUnit()->SetTag(pszSample);
	pTMEnvironment->GetTMUnit()->SetTimeTag(CTimeTag().GetTime() + 1000 * (GetTickCount() % 1000));
	return GetTPEPServiceSupport()->GenerateTPEPRandomData(GetDatabase(), &m_cConnection, pTMEnvironment);
}

BOOL CTPEPServerThread::Update(CTMEnvironment *pTMEnvironment, UINT nError, BOOL bCache)
{
	INT  nIndex;
	INT  nPacket;
	INT  nPackets;
	CTMUnit  cTMUnit;
	CTMUnit  *pTMUnit;
	CTMUnitCache  cTMUnits;
	CStringArray  szPackets;

	if (m_cConnection.GetType() == TPEP_TYPE_PACKETS)
	{
		for (nPacket = 0, nPackets = (bCache) ? m_cConnection.GetPackets(szPackets) : 0; nPacket < nPackets; nPacket++)
		{
			if (pTMEnvironment->Initialize(szPackets.GetAt(nPacket), cTMUnit, TRUE))
			{
				if ((pTMUnit = new CTMUnit))
				{
					pTMUnit->Copy(&cTMUnit);
					if (cTMUnits.Add(pTMUnit) < 0) delete pTMUnit;
				}
			}
		}
		if (bCache)
		{
			if (cTMUnits.GetSize() > 0)
			{
				for (m_bFlag.ResetEvent(); cTMUnits.GetSize() > 0; m_bFlag.ResetEvent())
				{
					for (nPacket = 0, nPackets = (INT)cTMUnits.GetSize(), nIndex = 0; nPacket < nPackets; nPacket++)
					{
						if (cTMUnits.GetAt(nPacket)->GetTimeTag() < cTMUnits.GetAt(nIndex)->GetTimeTag() || !nPacket)
						{
							pTMEnvironment->GetTMUnit()->Copy(cTMUnits.GetAt((nIndex = nPacket)));
							continue;
						}
					}
					if (GetTPEPService()->Update(pTMEnvironment, m_bFlag, GetThreadID()))
					{
						if (Wait(m_bFlag, FALSE) == WAIT_OBJECT_0 + 1)
						{
							delete cTMUnits.GetAt(nIndex);
							cTMUnits.RemoveAt(nIndex);
							continue;
						}
						cTMUnits.RemoveAll();
					}
					break;
				}
			}
			return((!cTMUnits.GetSize()) ? TRUE : FALSE);
		}
	}
	for (m_bFlag.ResetEvent(); GetTPEPService()->Update(pTMEnvironment, m_bFlag, GetThreadID(), nError); )
	{
		Wait(m_bFlag, FALSE);
		return TRUE;
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CTPEPServerThread, CThread)
	//{{AFX_MSG_MAP(CTPEPServerThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPServerThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTPEPServerSocket

IMPLEMENT_DYNCREATE(CTPEPServerSocket, CSocket)

CTPEPServerSocket::CTPEPServerSocket() : CSocket()
{
	m_nCharset = TPEP_SERVICE_DEFAULTCHARSET;
	m_bSendData[0] = FALSE;
	m_bSendData[1] = FALSE;
	m_nTimerID = 0;
	m_bReset = TRUE;
}

BOOL CTPEPServerSocket::Open()
{
	m_nSequence = 1;
	return TRUE;
}

BOOL CTPEPServerSocket::IsOpen() CONST
{
	return((m_hSocket != (SOCKET)INVALID_SOCKET) ? TRUE : FALSE);
}

VOID CTPEPServerSocket::Close()
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szClient;
	CTPEPWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CTPEPWnd *)m_pDisplays.GetAt(nDisplay)) && pDisplayWnd->IsRetrievingData())
		{
			pDisplayWnd->StopRetrieveData();
			continue;
		}
	}
	if (GetClient(szClient))
	{
		GetTPEPService()->UpdateServerConnection(szClient, &m_cConnection, TRUE);
		ShowLogoutMessage();
	}
	Reset();
	m_szLogin.Empty();
	m_cConnection.Reset();
	m_pDisplays.RemoveAll();
	CSocket::Close();
}

VOID CTPEPServerSocket::Reset()
{
	m_cServerThread.Stop();
	m_pTMUnits.RemoveAll();
	m_pTMParameters.RemoveAll();
	m_bSendData[0] = FALSE;
	m_bSendData[1] = FALSE;
	m_nSequence = 1;
	m_bReset = TRUE;
}

VOID CTPEPServerSocket::ShutDown()
{
	CByteArray  nData;

	if (IsOpen())
	{
		if (ConstructPacket(TPEP_ERROR_SHUTDOWN, nData))
		{
			ReportEvent((Send(nData) == SOCKET_ERROR) ? SYSTEM_WARNING_TPEP_SEND_FAILURE : SYSTEM_NOERROR);
			Close();
			return;
		}
		ReportEvent(SYSTEM_WARNING_TPEP_GENERAL_FAILURE);
		Close();
	}
}

BOOL CTPEPServerSocket::IsInitialized() CONST
{
	return((m_cConnection.IsInitialized()) ? !m_bReset : FALSE);
}

BOOL CTPEPServerSocket::GetClient(CString &szClient) CONST
{
	UINT  nCode;
	CString  szAddress;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	return GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime);
}

BOOL CTPEPServerSocket::GetAddress(CString &szAddress) CONST
{
	UINT  nCode;
	CString  szClient;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	return GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime);
}

BOOL CTPEPServerSocket::GetSecurityInfo(UINT &nCode, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CString  szClient;
	CString  szAddress;

	return GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime);
}

BOOL CTPEPServerSocket::GetConnectionInfo(CString &szClient, CTPEPConnection *pConnection) CONST
{
	if (GetClient(szClient))
	{
		pConnection->Copy(&m_cConnection, TRUE);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPServerSocket::GetProperties(CString &szClient, CString &szAddress, UINT &nCode, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	INT  nPos;
	INT  nClient;
	INT  nClients;
	INT  cbAddress;
	IN_ADDR  sClientAddress;
	SOCKADDR_IN  sAddress;
	CUIntArray  nAccessCodes;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;

	if (GetTPEPService()->GetSecurityInfo(szClients, nAccessCodes, tStartTimes, tStopTimes))
	{
		if (!getpeername(m_hSocket, (SOCKADDR *)&sAddress, &(cbAddress = sizeof(sAddress))))
		{
			for (nClient = 0, nClients = (INT)szClients.GetSize(); nClient < nClients; nClient++)
			{
				if ((nPos = szClients.GetAt(nClient).Find(EOL)) >= 0)
				{
#ifndef UNICODE
					szAddress = szClients.GetAt(nClient).Mid(nPos + 1);
#else
					WideCharToMultiByte(CP_ACP, 0, szClients.GetAt(nClient).Mid(nPos + 1), -1, (LPSTR)szAddress.GetBufferSetLength(szClients.GetAt(nClient).Mid(nPos + 1).GetLength()), szClients.GetAt(nClient).Mid(nPos + 1).GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
					szAddress.ReleaseBuffer();
#endif
					if (InetPton(AF_INET, szClients.GetAt(nClient).Mid(nPos + 1), &sClientAddress) > 0 && sClientAddress.S_un.S_addr == sAddress.sin_addr.S_un.S_addr) break;
				}
			}
			if (nClient < nClients)
			{
				if (InetNtop(AF_INET, &sAddress.sin_addr, szAddress.GetBufferSetLength(4 * sizeof(sAddress.sin_addr.S_un.S_addr)), 4 * sizeof(sAddress.sin_addr.S_un.S_addr)))
				{
					szClient = szClients.GetAt(nClient).Left(nPos);
					tStartTime = tStartTimes.GetAt(nClient);
					tStopTime = tStopTimes.GetAt(nClient);
					nCode = nAccessCodes.GetAt(nClient);
					szAddress.ReleaseBuffer();
					return TRUE;
				}
				szAddress.ReleaseBuffer();
			}
		}
	}
	return FALSE;
}

VOID CTPEPServerSocket::UpdateConnection()
{
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	CTMUnit  cTMUnit;
	CByteArray  nData;
	CStringArray  szPackets;
	CStringArray  szParameters;
	CTMParameter  *pTMParameter;
	CTMParameters  cTMParameters;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if (IsInitialized())
	{
		if (m_cConnection.GetType() == TPEP_TYPE_PACKETS)
		{
			if (m_cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME)
			{
				for (nPacket = 0, nPackets = m_cConnection.GetPackets(szPackets); nPacket < nPackets; nPacket++)
				{
					for (nParameter = 0, nParameters = (InitializeTMUnit(szPackets.GetAt(nPacket), cTMUnit, TRUE)) ? ((m_cConnection.GetDataType() != TPEP_DATATYPE_RAW) ? GetTPEPServiceSupport()->EnumTPEPTMUnitParameters(GetDatabase(), &cTMUnit, &m_cConnection, FALSE, szParameters) : 0) : 0; nParameter < nParameters; nParameter++)
					{
						if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
						{
							if ((pTMParameter = new CTMParameter))
							{
								pTMParameter->SetTag(pDatabaseTMParameter->GetTag());
								pTMParameter->SetAttributes(pDatabaseTMParameter->GetAttributes());
								cTMParameters.Add(pTMParameter);
								continue;
							}
						}
						break;
					}
					if (nParameter == nParameters)
					{
						if (InitializeTMUnit(szPackets.GetAt(nPacket), cTMUnit, TRUE) && InitializeTMData(cTMParameters, TRUE))
						{
							if (ConstructPacket(&cTMUnit, &cTMParameters, nData, FALSE))
							{
								if (Send(nData) != SOCKET_ERROR)
								{
									m_nSequence++;
									continue;
								}
								ReportEvent(SYSTEM_WARNING_TPEP_SEND_FAILURE);
								Close();
								break;
							}
						}
						else continue;
					}
					ReportEvent(SYSTEM_WARNING_TPEP_GENERAL_FAILURE);
					Close();
					break;
				}
				if (nPacket == nPackets)
				{
					if (m_cConnection.GetDataLink() == TPEP_DATALINK_COLD)
					{
						if (m_nSequence > 1)
						{
							Reset();
							return;
						}
					}
					if (m_nSequence == 1)
					{
						if (ConstructPacket(&cTMUnit, &cTMParameters, nData, FALSE))
						{
							if (Send(nData) != SOCKET_ERROR)
							{
								if (m_cConnection.GetDataLink() == TPEP_DATALINK_HOT)
								{
									m_nSequence++;
									return;
								}
								Reset();
								return;
							}
							ReportEvent(SYSTEM_WARNING_TPEP_SEND_FAILURE);
							Close();
							return;
						}
						ReportEvent(SYSTEM_WARNING_TPEP_GENERAL_FAILURE);
						Close();
					}
				}
			}
		}
		if (m_cConnection.GetType() == TPEP_TYPE_PARAMETERS)
		{
			if (m_cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME)
			{
				for (nParameter = 0, nParameters = m_cConnection.GetParameters(szParameters); nParameter < nParameters; nParameter++)
				{
					if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
					{
						if ((pTMParameter = new CTMParameter))
						{
							pTMParameter->SetTag(pDatabaseTMParameter->GetTag());
							pTMParameter->SetAttributes(pDatabaseTMParameter->GetAttributes());
							cTMParameters.Add(pTMParameter);
							continue;
						}
					}
					break;
				}
				if (nParameter == nParameters)
				{
					if (InitializeTMData(cTMParameters, TRUE))
					{
						if (ConstructPacket(&cTMUnit, &cTMParameters, nData))
						{
							if (Send(nData) != SOCKET_ERROR)
							{
								if (m_cConnection.GetDataLink() == TPEP_DATALINK_HOT)
								{
									m_nSequence++;
									return;
								}
								Reset();
								return;
							}
							ReportEvent(SYSTEM_WARNING_TPEP_SEND_FAILURE);
							Close();
							return;
						}
					}
				}
				ReportEvent(SYSTEM_WARNING_TPEP_GENERAL_FAILURE);
				Close();
			}
		}
	}
}
BOOL CTPEPServerSocket::UpdateConnection(CONST CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError)
{
	CByteArray  nData;

	if (IsInitialized())
	{
		if (AuthorizeConnection(dwContext))
		{
			if ((pTMEnvironment->GetTMUnit() != (CTMUnit *)NULL  &&  pTMEnvironment->GetTMParameters() != (CTMParameters *)NULL) || nError > 0)
			{
				if ((!nError  &&  ConstructPacket(pTMEnvironment->GetTMUnit(), pTMEnvironment->GetTMParameters(), nData)) || (nError > 0 && ConstructPacket(nError, nData)))
				{
					if (!nData.GetSize() || Send(nData) != SOCKET_ERROR)
					{
						if (nData.GetSize() > 0)
						{
							if (nError == 0)
							{
								m_nSequence++;
								return TRUE;
							}
							Close();
							return FALSE;
						}
						return TRUE;
					}
					ReportEvent(SYSTEM_WARNING_TPEP_SEND_FAILURE);
					Close();
					return FALSE;
				}
				ReportEvent(SYSTEM_WARNING_TPEP_GENERAL_FAILURE);
				Close();
				return FALSE;
			}
			if (m_cConnection.GetDataLink() == TPEP_DATALINK_COLD)
			{
				Reset();
				return FALSE;
			}
			Close();
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CTPEPServerSocket::AuthorizeConnection()
{
	CTimeSpan  tDelay;

	return AuthorizeConnection(tDelay);
}
BOOL CTPEPServerSocket::AuthorizeConnection(CTimeSpan &tDelay)
{
	CByteArray  nData;

	if (IsInitialized())
	{
		if (!CheckServiceAvailability())
		{
			ReportEvent((ConstructPacket(TPEP_ERROR_NOSERVICE, nData) && Send(nData) == SOCKET_ERROR) ? SYSTEM_WARNING_TPEP_SEND_FAILURE : SYSTEM_NOERROR);
			tDelay = INFINITE;
			Close();
			return FALSE;
		}
		if (!CheckServiceSecurity(tDelay))
		{
			ReportEvent((ConstructPacket(TPEP_ERROR_NOACCESS, nData) && Send(nData) == SOCKET_ERROR) ? SYSTEM_WARNING_TPEP_SEND_FAILURE : SYSTEM_NOERROR);
			tDelay = INFINITE;
			Close();
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPServerSocket::AuthorizeConnection(DWORD dwContext)
{
	return((IsInitialized() && ((m_cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME  &&  dwContext == (DWORD)-1) || ((m_cConnection.GetDataMode() == TPEP_DATAMODE_HISTORY || m_cConnection.GetDataMode() == TPEP_DATAMODE_RANDOM) && m_cServerThread.GetThreadID() == dwContext))) ? TRUE : FALSE);
}

INT CTPEPServerSocket::Send(CONST CByteArray &nData)
{
	INT  nPos;
	INT  cbData;
	INT  cbBuffer;
	INT  nDisplay;
	INT  nDisplays;
	CString  szData;
	CDisplayWnd  *pDisplayWnd;

	for (ConvertPacket(nData, szData); (nPos = szData.Find(EOL)) >= 0; )
	{
		for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays.GetAt(nDisplay)))
			{
				pDisplayWnd->Update(szData.Left(nPos));
				continue;
			}
		}
		szData = szData.Mid(nPos + 1);
	}
	if (!m_bSendData[1])
	{
		for (SetSockOpt(SO_SNDBUF, &(cbBuffer = GetTPEPService()->GetBufferSize()), sizeof(cbBuffer)), m_nTimerID = SetTimer((HWND)NULL, TPEPSERVERSOCKET_DATASTREAM_TIMERID, (UINT)max(1000 * GetTPEPService()->GetTimeout().GetTotalSeconds(), TPEPSERVERSOCKET_DATASTREAM_TIMEOUT), NULL), m_bSendData[0] = TRUE; (cbData = CSocket::Send(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			KillTimer((HWND)NULL, m_nTimerID);
			UpdateStatistics(cbData);
			m_bSendData[0] = FALSE;
			m_nTimerID = 0;
			return cbData;
		}
		if (GetLastError() != WSAECONNABORTED)
		{
			KillTimer((HWND)NULL, m_nTimerID);
			m_bSendData[0] = FALSE;
			m_nTimerID = 0;
			return SOCKET_ERROR;
		}
		KillTimer((HWND)NULL, m_nTimerID);
		m_bSendData[0] = FALSE;
		m_nTimerID = 0;
	}
	return 0;
}

INT CTPEPServerSocket::Receive(CByteArray &nData)
{
	INT  cbData;
	INT  cbBuffer;

	for (nData.SetSize(GetTPEPService()->GetBufferSize()); nData.GetSize() == GetTPEPService()->GetBufferSize(); )
	{
		for (SetSockOpt(SO_RCVBUF, &(cbBuffer = GetTPEPService()->GetBufferSize()), sizeof(cbBuffer)); (cbData = CSocket::Receive(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			nData.SetSize(cbData);
			return cbData;
		}
		break;
	}
	return((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0);
}

BOOL CTPEPServerSocket::Attach(CDisplayWnd *pDisplayWnd)
{
	INT  nDisplay;
	INT  nDisplays;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if (m_pDisplays.GetAt(nDisplay) == (LPVOID)pDisplayWnd) break;
		continue;
	}
	return((nDisplay < nDisplays || !pDisplayWnd || m_pDisplays.Add(pDisplayWnd) >= 0) ? TRUE : FALSE);
}

BOOL CTPEPServerSocket::Detach(CDisplayWnd *pDisplayWnd)
{
	INT  nDisplay;
	INT  nDisplays;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if (m_pDisplays.GetAt(nDisplay) == (LPVOID)pDisplayWnd) break;
		continue;
	}
	if (nDisplay < nDisplays)
	{
		m_pDisplays.RemoveAt(nDisplay);
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPServerSocket::ParsePacket(CONST CByteArray &nData)
{
	INT  nPos;
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	UINT  nDataMode;
	UINT  nDataLink;
	UINT  nDataType;
	UINT  nSampleLimit;
	UINT  nTriggerMode;
	UINT  nSpacecraftID;
	UINT  nRetrieveSpeed;
	CString  szPacket;
	CString  szParameter;
	CString  szRequestPacket;
	CStringArray  szPackets;
	CStringArray  szParameters;
	CTimeKey  tRetrieveStartTime;
	CTimeKey  tRetrieveStopTime;

	Reset();
	ConvertPacket(nData, szRequestPacket);
	if (szRequestPacket.Mid((nPos = 0), lstrlen(STRING(IDS_TPEP_REQUEST_PACKETS_ID))) == STRING(IDS_TPEP_REQUEST_PACKETS_ID))
	{
		if (!(GetTPEPServiceSupport()->GetTPEPSupport() & TPEP_TYPE_PACKETS) || !m_cConnection.SetType(TPEP_TYPE_PACKETS)) return TPEP_ERROR_ILLEGALMESSAGEID;
		if (!_istspace(szRequestPacket[(nPos = nPos + lstrlen(STRING(IDS_TPEP_REQUEST_PACKETS_ID)))])) return TPEP_ERROR_ILLEGALSYNTAX;
		if ((nSpacecraftID = _ttoi(CString(szRequestPacket[SkipSpaces(szRequestPacket, nPos)]))) != GetTPEPServiceSupport()->GetTPEPSpacecraftID() || !m_cConnection.SetSpacecraftID(nSpacecraftID)) return TPEP_ERROR_ILLEGALSPACECRAFTID;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if ((nPackets = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))) <= 0) return TPEP_ERROR_ILLEGALNUMBEROFPACKETS;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		for (nPacket = 0; nPacket < nPackets; nPacket++)
		{
			szPacket = szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos), GetDatabase()->GetTMPacketTagLength());
			szPacket = (szPacket.Find(SPACE) > 0) ? szPacket.Left(szPacket.Find(SPACE)) : szPacket;
			if (!GetDatabase()->CheckTMPacketTag(szPacket) || GetDatabase()->GetTMPackets()->Find(szPacket) < 0) return TPEP_ERROR_ILLEGALPACKETID;
			if (!_istspace(szRequestPacket[(nPos = nPos + szPacket.GetLength())])) return TPEP_ERROR_ILLEGALSYNTAX;
			szPackets.Add(szPacket);
		}
		if (!m_cConnection.SetDataMode((nDataMode = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))))) return TPEP_ERROR_ILLEGALDATAMODE;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetDataLink((nDataLink = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))))) return TPEP_ERROR_ILLEGALDATALINK;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetDataType((nDataType = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))))) return TPEP_ERROR_ILLEGALDATATYPE;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetTriggerMode((nTriggerMode = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos))))) || (nTriggerMode == TPEP_TRIGGERMODE_CHANGE && ((nDataMode != TPEP_DATAMODE_REALTIME  &&  nDataMode != TPEP_DATAMODE_HISTORY) || nDataLink != TPEP_DATALINK_HOT || nDataType == TPEP_DATATYPE_RAW))) return TPEP_ERROR_ILLEGALTRIGGERMODE;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetSampleLimit((nSampleLimit = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos))))) || (nDataType == TPEP_DATATYPE_RAW  &&  nSampleLimit > 0)) return TPEP_ERROR_ILLEGALSAMPLELIMIT;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!ParseTimeKey(szRequestPacket, (nPos = SkipSpaces(szRequestPacket, nPos)), tRetrieveStartTime) || (nDataMode != TPEP_DATAMODE_HISTORY  &&  tRetrieveStartTime != 0) || (nDataMode == TPEP_DATAMODE_HISTORY  &&  tRetrieveStartTime <= 0)) return TPEP_ERROR_ILLEGALRETRIEVESTARTTIME;
		if (!_istspace(szRequestPacket[nPos])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!ParseTimeKey(szRequestPacket, (nPos = SkipSpaces(szRequestPacket, nPos)), tRetrieveStopTime) || (nDataMode != TPEP_DATAMODE_HISTORY  &&  tRetrieveStopTime != 0) || (nDataMode == TPEP_DATAMODE_HISTORY && (tRetrieveStopTime <= 0 || tRetrieveStartTime > tRetrieveStopTime))) return TPEP_ERROR_ILLEGALRETRIEVESTOPTIME;
		if (!_istspace(szRequestPacket[nPos])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetRetrieveSpeed((nRetrieveSpeed = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos))))) || ((nDataMode != TPEP_DATAMODE_HISTORY || nDataLink != TPEP_DATALINK_HOT) && nRetrieveSpeed != 0) || (nDataMode == TPEP_DATAMODE_HISTORY  &&  nDataLink == TPEP_DATALINK_HOT  &&  !nRetrieveSpeed)) return TPEP_ERROR_ILLEGALRETRIEVESPEED;
		if (szRequestPacket.GetLength() != SkipNumber(szRequestPacket, nPos) + 1 || szRequestPacket[nPos] != EOL) return TPEP_ERROR_ILLEGALSYNTAX;
		m_cConnection.SetRetrieveStartTime(tRetrieveStartTime);
		m_cConnection.SetRetrieveStopTime(tRetrieveStopTime);
		m_cConnection.SetPackets(szPackets);
		m_nSequence = 1;
		m_bReset = FALSE;
		return TPEP_ERROR_NONE;
	}
	if (szRequestPacket.Mid(nPos, lstrlen(STRING(IDS_TPEP_REQUEST_PARAMETERS_ID))) == STRING(IDS_TPEP_REQUEST_PARAMETERS_ID))
	{
		if (!m_cConnection.SetType(TPEP_TYPE_PARAMETERS) || !(GetTPEPServiceSupport()->GetTPEPSupport() & TPEP_TYPE_PARAMETERS)) return TPEP_ERROR_ILLEGALMESSAGEID;
		if (!_istspace(szRequestPacket[(nPos = nPos + lstrlen(STRING(IDS_TPEP_REQUEST_PARAMETERS_ID)))])) return TPEP_ERROR_ILLEGALSYNTAX;
		if ((nSpacecraftID = _ttoi(CString(szRequestPacket[SkipSpaces(szRequestPacket, nPos)]))) != GetTPEPServiceSupport()->GetTPEPSpacecraftID() || !m_cConnection.SetSpacecraftID(nSpacecraftID)) return TPEP_ERROR_ILLEGALSPACECRAFTID;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if ((nParameters = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))) <= 0) return TPEP_ERROR_ILLEGALNUMBEROFPARAMETERS;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		for (nParameter = 0; nParameter < nParameters; nParameter++)
		{
			szParameter = szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos), GetDatabase()->GetTMParameterTagLength());
			szParameter = (szParameter.Find(SPACE) > 0) ? szParameter.Left(szParameter.Find(SPACE)) : szParameter;
			if (!GetDatabase()->CheckTMParameterTag(szParameter) || GetDatabase()->GetTMParameters()->Find(szParameter) < 0) return TPEP_ERROR_ILLEGALPARAMETERID;
			if (!_istspace(szRequestPacket[(nPos = nPos + szParameter.GetLength())])) return TPEP_ERROR_ILLEGALSYNTAX;
			szParameters.Add(szParameter);
		}
		if (!m_cConnection.SetDataMode((nDataMode = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))))) return TPEP_ERROR_ILLEGALDATAMODE;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetDataLink((nDataLink = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))))) return TPEP_ERROR_ILLEGALDATALINK;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetDataType((nDataType = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos))))) || nDataType == TPEP_DATATYPE_RAW) return TPEP_ERROR_ILLEGALDATATYPE;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetTriggerMode((nTriggerMode = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos))))) || (nTriggerMode == TPEP_TRIGGERMODE_CHANGE && ((nDataMode != TPEP_DATAMODE_REALTIME  &&  nDataMode != TPEP_DATAMODE_HISTORY) || nDataLink != TPEP_DATALINK_HOT))) return TPEP_ERROR_ILLEGALTRIGGERMODE;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetSampleLimit((nSampleLimit = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos)))))) return TPEP_ERROR_ILLEGALSAMPLELIMIT;
		if (!_istspace(szRequestPacket[SkipNumber(szRequestPacket, nPos)])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!ParseTimeKey(szRequestPacket, (nPos = SkipSpaces(szRequestPacket, nPos)), tRetrieveStartTime) || (nDataMode != TPEP_DATAMODE_HISTORY  &&  tRetrieveStartTime != 0) || (nDataMode == TPEP_DATAMODE_HISTORY  &&  tRetrieveStartTime <= 0)) return TPEP_ERROR_ILLEGALRETRIEVESTARTTIME;
		if (!_istspace(szRequestPacket[nPos])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!ParseTimeKey(szRequestPacket, (nPos = SkipSpaces(szRequestPacket, nPos)), tRetrieveStopTime) || (nDataMode != TPEP_DATAMODE_HISTORY  &&  tRetrieveStopTime != 0) || (nDataMode == TPEP_DATAMODE_HISTORY && (tRetrieveStopTime <= 0 || tRetrieveStartTime > tRetrieveStopTime))) return TPEP_ERROR_ILLEGALRETRIEVESTOPTIME;
		if (!_istspace(szRequestPacket[nPos])) return TPEP_ERROR_ILLEGALSYNTAX;
		if (!m_cConnection.SetRetrieveSpeed((nRetrieveSpeed = _ttoi(szRequestPacket.Mid(SkipSpaces(szRequestPacket, nPos))))) || ((nDataMode != TPEP_DATAMODE_HISTORY || nDataLink != TPEP_DATALINK_HOT) && nRetrieveSpeed != 0) || (nDataMode == TPEP_DATAMODE_HISTORY  &&  nDataLink == TPEP_DATALINK_HOT  &&  !nRetrieveSpeed)) return TPEP_ERROR_ILLEGALRETRIEVESPEED;
		if (szRequestPacket.GetLength() != SkipNumber(szRequestPacket, nPos) + 1 || szRequestPacket[nPos] != EOL) return TPEP_ERROR_ILLEGALSYNTAX;
		m_cConnection.SetRetrieveStartTime(tRetrieveStartTime);
		m_cConnection.SetRetrieveStopTime(tRetrieveStopTime);
		m_cConnection.SetParameters(szParameters);
		m_nSequence = 1;
		m_bReset = FALSE;
		return TPEP_ERROR_NONE;
	}
	return TPEP_ERROR_ILLEGALMESSAGEID;
}

BOOL CTPEPServerSocket::ParseTimeKey(LPCTSTR pszString, INT &nPos, CTimeKey &tTimeKey)
{
	TIMEKEY  tTime;
	CString  szFormat;
	CStringTools  cStringTools;

	if ((tTime = tTimeKey.ParseGmt(&pszString[nPos], (szFormat = GetTPEPServiceSupport()->GetTPEPRetrieveTimeKeyFormat()))) >= 0)
	{
		nPos += (tTimeKey = tTime).FormatGmt(szFormat).GetLength();
		return((nPos < lstrlen(pszString)) ? TRUE : FALSE);
	}
	if (cStringTools.ConvertIntToString(0).GetAt(0) == pszString[nPos])
	{
		tTimeKey = 0;
		nPos++;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPServerSocket::CheckServiceAvailability() CONST
{
	CString  szError;

	return((CheckServiceAvailability(szError) > 0) ? TRUE : FALSE);
}
INT CTPEPServerSocket::CheckServiceAvailability(CString &szError) CONST
{
	UINT  nCode;
	CTimeKey  tTime[2];
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;

	if (GetTPEPService()->GetAvailabilityInfo(nCode, tStartTime, tStopTime))
	{
		if (nCode & TPEP_SERVICE_NOAVAILABILITY)
		{
			szError.Empty();
			return FALSE;
		}
		if (nCode & TPEP_SERVICE_WORKINGDAYSAVAILABILITY)
		{
			if ((tTime[1] = tTime[1].GetTime() + tTime[1].GetBias()).GetDayOfWeek() != Monday  &&  tTime[1].GetDayOfWeek() != Tuesday  &&  tTime[1].GetDayOfWeek() != Wednesday  &&  tTime[1].GetDayOfWeek() != Thursday  &&  tTime[1].GetDayOfWeek() != Friday)
			{
				szError = STRING(IDS_TPEP_SCHEDULE_INACTIVEWEEKDAYS);
				return((nCode & TPEP_SERVICE_AUDITAVAILABILITY) ? -TRUE : FALSE);
			}
		}
		if (nCode & TPEP_SERVICE_DAILYAVAILABILITY)
		{
			if (tTime[0].GetTime() % SECONDSPERDAY < tStartTime.GetTotalSeconds() || tTime[0].GetTime() % SECONDSPERDAY >= tStopTime.GetTotalSeconds())
			{
				szError.Format(STRING(IDS_TPEP_SCHEDULE_INACTIVEDAILY), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY) + tStartTime.GetTotalSeconds()).FormatGmt(GetTPEPServiceSupport()->GetTPEPTimeKeyFormat()), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY) + tStopTime.GetTotalSeconds()).FormatGmt(GetTPEPServiceSupport()->GetTPEPTimeKeyFormat()));
				return((nCode & TPEP_SERVICE_AUDITAVAILABILITY) ? -TRUE : FALSE);
			}
		}
		szError.Empty();
		return TRUE;
	}
	szError.Empty();
	return FALSE;
}

BOOL CTPEPServerSocket::CheckServiceSecurity() CONST
{
	CString  szError;

	return((CheckServiceSecurity(szError) > 0) ? TRUE : FALSE);
}
INT CTPEPServerSocket::CheckServiceSecurity(CString &szError) CONST
{
	CTimeSpan tDelay;

	return CheckServiceSecurity(tDelay, szError);
}
BOOL CTPEPServerSocket::CheckServiceSecurity(CTimeSpan &tDelay) CONST
{
	CString  szError;

	return((CheckServiceSecurity(tDelay, szError) > 0) ? TRUE : FALSE);
}
INT CTPEPServerSocket::CheckServiceSecurity(CTimeSpan &tDelay, CString &szError) CONST
{
	UINT  nCode;
	CString  szClient;
	CString  szAddress;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeKey  tTime;

	if (GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime))
	{
		if ((nCode & TPEP_SERVICE_DENIEDACCESS) || ((nCode & TPEP_SERVICE_RESTRICTEDACCESS) && (tTime < tStartTime || tTime > tStopTime)))
		{
			szError.Format(STRING(IDS_TPEP_SECURITY_ILLEGALLOGIN), (!szClient.IsEmpty()) ? (LPCTSTR)szClient : STRING(IDS_TPEP_SECURITY_UNKNOWNLOGIN), (LPCTSTR)szAddress);
			return((nCode & TPEP_SERVICE_AUDITACCESS) ? -TRUE : FALSE);
		}
		tDelay = (nCode & TPEP_SERVICE_RESTRICTEDACCESS) ? max(tStopTime.GetTime() - tTime.GetTime(), 0) : INFINITE;
		return TRUE;
	}
	return FALSE;
}

VOID CTPEPServerSocket::UpdateCharset(CONST CByteArray &nData)
{
	CTimeKey  tTime;
	CByteArray  nDataBlock;

	for (nDataBlock.Copy(nData), nDataBlock.InsertAt(nDataBlock.GetSize(), 0, 1), m_nCharset = (GetTPEPService()->GetCharset() == TPEP_SERVICE_DEFAULTCHARSET) ? ((nData.GetSize() != (INT)strlen((LPCSTR)nDataBlock.GetData())) ? TPEP_SERVICE_UNICODECHARSET : TPEP_SERVICE_ASCIICHARSET) : GetTPEPService()->GetCharset(), m_cConnection.Reset(); TRUE; )
	{
		m_cConnection.SetStatistics(tTime, tTime, 0);
		break;
	}
}

BOOL CTPEPServerSocket::ConstructPacket(UINT nError, CByteArray &nData)
{
	CString  szError;
	CString  szPacket;
	CString  szStatus;
	CStringTools  cStringTools;

	szError.Format(STRING(HIWORD(nError) + IDS_TPEP_ERROR_NONE - TPEP_ERROR_NONE), LOWORD(nError));
	szStatus.Format(STRING(HIWORD(TPEP_SYNCSTATUS_NONE) + IDS_TPEP_SYNCSTATUS_GOOD - TPEP_SYNCSTATUS_GOOD), LOWORD(TPEP_SYNCSTATUS_NONE));
	szPacket = (m_cConnection.GetType() == TPEP_TYPE_PACKETS) ? STRING(IDS_TPEP_DATA_PACKETS_ID) : (m_cConnection.GetType() == TPEP_TYPE_PARAMETERS) ? STRING(IDS_TPEP_DATA_PARAMETERS_ID) : STRING(IDS_TPEP_DATA_UNKNOWN_ID);
	szPacket += SPACE + cStringTools.ConvertUIntToString(m_nSequence) + SPACE + szError + SPACE + szStatus + CString(EOL);
	return ConvertPacket(szPacket, nData);
}
BOOL CTPEPServerSocket::ConstructPacket(CONST CTMUnit *pTMUnit, CONST CTMParameters *pTMParameters, CByteArray &nData, BOOL bFilter)
{
	INT  nPos;
	INT  nPIEs;
	INT  nItem;
	INT  nItems;
	INT  nByte;
	INT  nBytes;
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	UINT  nError;
	UINT  nStatus;
	CString  szPIE;
	CString  szPIEs;
	CString  szByte;
	CString  szTime;
	CString  szError;
	CString  szPacket;
	CString  szStatus;
	CByteArray  nPacketData;
	CStringArray  szPackets;
	CStringArray  szContents;
	CStringArray  szParameters;
	CStringTools  cStringTools;
	CTMProviderDevice  cDevice;
	CTMParameter  *pTMParameter;
	CTMUnit  *pTMData;

	if (m_cConnection.GetType() == TPEP_TYPE_PACKETS)
	{
		if ((pTMData = m_pTMUnits.GetAt(m_pTMUnits.Find(pTMUnit->GetTag()))))
		{
			if (pTMData->GetTimeTag() == pTMUnit->GetTimeTag())
			{
				nData.RemoveAll();
				return TRUE;
			}
		}
		if (pTMUnit->IsValid())
		{
			if (m_pTMUnits.Find(pTMUnit->GetTag()) < 0)
			{
				if ((pTMData = new CTMUnit))
				{
					pTMData->Copy(pTMUnit);
					m_pTMUnits.Add(pTMData);
				}
			}
			for (nPacket = 0, nPackets = m_cConnection.GetPackets(szPackets); nPacket < nPackets; nPacket++)
			{
				if (pTMUnit->GetTag() == szPackets.GetAt(nPacket) && GetTPEPServiceSupport()->EnumTPEPTMUnitParameters(GetDatabase(), pTMUnit, &m_cConnection, FALSE, szParameters) >= 0) break;
				continue;
			}
			if (nPacket == nPackets)
			{
				nData.RemoveAll();
				return TRUE;
			}
			if (m_cConnection.GetDataType() != TPEP_DATATYPE_RAW  &&  m_cConnection.GetTriggerMode() == TPEP_TRIGGERMODE_CHANGE)
			{
				for (nParameter = 0, nParameters = (bFilter) ? (INT)szParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
				{
					if ((pTMParameter = pTMParameters->GetAt(pTMParameters->Find(szParameters.GetAt(nParameter)))))
					{
						if (pTMParameter->GetLastChangeTMUnit() == pTMUnit->GetTag() && pTMParameter->GetLastChangeTime() == pTMUnit->GetTimeTag()) break;
						continue;
					}
				}
				if (nParameter == nParameters)
				{
					nData.RemoveAll();
					return TRUE;
				}
			}
		}
		szPacket = STRING(IDS_TPEP_DATA_PACKETS_ID);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(m_nSequence);
		szPacket += SPACE;
		nError = (pTMUnit->IsValid()) ? ((!pTMUnit->HasBadData()) ? TPEP_ERROR_NONE : TPEP_ERROR_BADDATA) : TPEP_ERROR_NODATA;
		szError.Format(STRING(HIWORD(nError) + IDS_TPEP_ERROR_NONE - TPEP_ERROR_NONE), LOWORD(nError));
		szPacket += szError;
		szPacket += SPACE;
		nStatus = (m_cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME) ? ((GetTMService()->GetActiveTMProviderDevice(&cDevice) && (cDevice.GetStatusIndication() & (IODEVICE_STATUS_GOOD | IODEVICE_STATUS_CONNECTED)) == (IODEVICE_STATUS_GOOD | IODEVICE_STATUS_CONNECTED)) ? TPEP_SYNCSTATUS_GOOD : TPEP_SYNCSTATUS_BAD) : TPEP_SYNCSTATUS_NONE;
		szStatus.Format(STRING(HIWORD(nStatus) + IDS_TPEP_SYNCSTATUS_GOOD - TPEP_SYNCSTATUS_GOOD), LOWORD(nStatus));
		szPacket += szStatus;
		if (pTMUnit->IsValid())
		{
			szPacket += SPACE;
			szPacket += pTMUnit->GetTag();
			szPacket += SPACE;
			szPacket += pTMUnit->GetTimeTag().FormatGmt(GetTPEPServiceSupport()->GetTPEPTimeKeyFormat());
			szPacket += SPACE;
			szPacket += (pTMUnit->GetUnitID() != (UINT)-1) ? (LPCTSTR)cStringTools.ConvertUIntToString(pTMUnit->GetUnitID()) : STRING(IDS_TPEP_PACKET_UNITID_NONE);
			szPacket += SPACE;
			szPacket += cStringTools.ConvertUIntToString(m_cConnection.GetDataType());
			szPacket += SPACE;
			szPacket += cStringTools.ConvertUIntToString((m_cConnection.GetDataType() == TPEP_DATATYPE_RAW) ? (INT)pTMUnit->GetSize() : (INT)szParameters.GetSize());
			if (m_cConnection.GetDataType() == TPEP_DATATYPE_RAW)
			{
				for (nByte = 0, nBytes = pTMUnit->GetData(nPacketData); nByte < nBytes; nByte++)
				{
					szByte = cStringTools.ConvertIntToPaddedString(nPacketData.GetAt(nByte), 2, 16);
					szPacket += (!(nByte % 2)) ? (SPACE + szByte) : szByte;
				}
				return ConvertPacket(szPacket + EOL, nData);
			}
			for (nParameter = 0, nParameters = (INT)szParameters.GetSize(); nParameter < nParameters; nParameter++)
			{
				szPIE = ConstructPIE(pTMUnit, pTMParameters, szParameters.GetAt(nParameter), m_cConnection.GetDataType(), m_cConnection.GetSampleLimit());
				szPacket += szPIE;
			}
		}
		return ConvertPacket(szPacket + EOL, nData);
	}
	if (m_cConnection.GetType() == TPEP_TYPE_PARAMETERS)
	{
		for (nParameter = 0, nParameters = (pTMUnit->IsValid()) ? GetTPEPServiceSupport()->EnumTPEPTMUnitParameters(GetDatabase(), pTMUnit, &m_cConnection, TRUE, szParameters) : m_cConnection.GetParameters(szParameters); nParameter < nParameters; nParameter++)
		{
			for (nItem = 0, nItems = m_cConnection.GetParameters(szContents); nItem < nItems; nItem++)
			{
				if (szParameters.GetAt(nParameter) == szContents.GetAt(nItem)) break;
				continue;
			}
			if (nItem == nItems)
			{
				szParameters.RemoveAt(nParameter);
				nParameters--;
				nParameter--;
			}
		}
		if (!szParameters.GetSize())
		{
			nData.RemoveAll();
			return TRUE;
		}
		for (nParameter = 0, nParameters = (pTMUnit->IsValid()) ? (INT)szParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter = m_pTMParameters.GetAt(m_pTMParameters.Find(szParameters.GetAt(nParameter)))) != (CTMParameter *)NULL)
			{
				if (pTMParameter->GetLastUpdateTMUnit() == pTMUnit->GetTag() && pTMParameter->GetLastUpdateTime() == pTMUnit->GetTimeTag())
				{
					szParameters.RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
			}
		}
		if (!szParameters.GetSize())
		{
			nData.RemoveAll();
			return TRUE;
		}
		for (nParameter = 0, nParameters = (pTMUnit->IsValid()) ? (INT)szParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter = pTMParameters->GetAt(pTMParameters->Find(szParameters.GetAt(nParameter)))) != (CTMParameter *)NULL)
			{
				if ((m_cConnection.GetTriggerMode() == TPEP_TRIGGERMODE_UPDATE && (pTMParameter->GetLastUpdateTMUnit() != pTMUnit->GetTag() || pTMParameter->GetLastUpdateTime() != pTMUnit->GetTimeTag())) || (m_cConnection.GetTriggerMode() == TPEP_TRIGGERMODE_CHANGE && (pTMParameter->GetLastChangeTMUnit() != pTMUnit->GetTag() || pTMParameter->GetLastChangeTime() != pTMUnit->GetTimeTag())))
				{
					szParameters.RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
			}
		}
		if (!szParameters.GetSize())
		{
			nData.RemoveAll();
			return TRUE;
		}
		for (nItem = 0, nItems = (INT)szContents.GetSize(), nPIEs = 0; nItem < nItems; nItem++)
		{
			for (nParameter = 0, nParameters = (INT)szParameters.GetSize(); nParameter < nParameters; nParameter++)
			{
				if (szParameters.GetAt(nParameter) == szContents.GetAt(nItem)) break;
				continue;
			}
			if ((szPIE = ConstructPIE(pTMUnit, pTMParameters, szContents.GetAt(nItem), m_cConnection.GetDataType(), m_cConnection.GetSampleLimit(), (!pTMUnit->IsValid() || nParameter == nParameters) ? TRUE : FALSE)).GetLength() > 0)
			{
				if ((pTMParameter = m_pTMParameters.GetAt(m_pTMParameters.Find(szContents.GetAt(nItem)))))
				{
					pTMParameter->Copy(pTMParameters->GetAt(pTMParameters->Find(szContents.GetAt(nItem))));
					szPIEs += szPIE;
					nPIEs++;
					continue;
				}
				if ((pTMParameter = new CTMParameter))
				{
					pTMParameter->Copy(pTMParameters->GetAt(pTMParameters->Find(szContents.GetAt(nItem))));
					m_pTMParameters.Add(pTMParameter);
				}
				szPIEs += szPIE;
				nPIEs++;
			}
		}
		szPacket = STRING(IDS_TPEP_DATA_PARAMETERS_ID);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(m_nSequence);
		szPacket += SPACE;
		nError = (!pTMUnit->IsValid() || !pTMUnit->HasBadData()) ? TPEP_ERROR_NONE : TPEP_ERROR_BADDATA;
		szError.Format(STRING(HIWORD(nError) + IDS_TPEP_ERROR_NONE - TPEP_ERROR_NONE), LOWORD(nError));
		szPacket += szError;
		szPacket += SPACE;
		nStatus = (m_cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME) ? ((GetTMService()->GetActiveTMProviderDevice(&cDevice) && (cDevice.GetStatusIndication() & (IODEVICE_STATUS_GOOD | IODEVICE_STATUS_CONNECTED)) == (IODEVICE_STATUS_GOOD | IODEVICE_STATUS_CONNECTED)) ? TPEP_SYNCSTATUS_GOOD : TPEP_SYNCSTATUS_BAD) : TPEP_SYNCSTATUS_NONE;
		szStatus.Format(STRING(HIWORD(nStatus) + IDS_TPEP_SYNCSTATUS_GOOD - TPEP_SYNCSTATUS_GOOD), LOWORD(nStatus));
		szPacket += szStatus;
		szPacket += SPACE;
		szPacket += (pTMUnit->IsValid()) ? (LPCTSTR)pTMUnit->GetTag() : STRING(IDS_TPEP_PACKET_NONE);
		szPacket += SPACE;
		szTime = pTMUnit->GetTimeTag().FormatGmt(GetTPEPServiceSupport()->GetTPEPTimeKeyFormat());
		szPacket += (pTMUnit->IsValid()) ? (LPCTSTR)szTime : STRING(IDS_TPEP_PACKET_TIMETAG_NONE);
		for (nPos = (pTMUnit->IsValid()) ? szTime.GetLength() : 0; nPos < szTime.GetLength(); nPos++)
		{
			szPacket += (_istspace(szTime[nPos])) ? (LPCTSTR)(CString(SPACE) + STRING(IDS_TPEP_PACKET_TIMETAG_NONE)) : EMPTYSTRING;
			continue;
		}
		szPacket += SPACE;
		szPacket += (pTMUnit->IsValid() && pTMUnit->GetUnitID() != (UINT)-1) ? (LPCTSTR)cStringTools.ConvertUIntToString(pTMUnit->GetUnitID()) : STRING(IDS_TPEP_PACKET_UNITID_NONE);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(m_cConnection.GetDataType());
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(nPIEs) + szPIEs;
		return ConvertPacket(szPacket + EOL, nData);
	}
	return FALSE;
}

CString CTPEPServerSocket::ConstructPIE(CONST CTMUnit *pTMUnit, CONST CTMParameters *pTMParameters, LPCTSTR pszParameter, UINT nPIEType, UINT nSampleLimit, BOOL bUnchanged)
{
	INT  nSample;
	INT  nSamples;
	UINT  nStatus;
	CString  szPIE;
	CString  szValue[2];
	ULONGLONG  nValue;
	CStringTools  cStringTools;
	CTMParameter  *pTMParameter;

	if ((pTMParameter = pTMParameters->GetAt(pTMParameters->Find(pszParameter))))
	{
		if (!pTMParameter->GetValueCount())
		{
			szPIE = SPACE;
			szPIE += pTMParameter->GetTag();
			szPIE += SPACE;
			szPIE += cStringTools.ConvertUIntToString(TPEP_DATAQUALITY_NONE);
			return szPIE;
		}
		for (nSample = 0, nSamples = (nPIEType == TPEP_DATATYPE_PIE1 || nPIEType == TPEP_DATATYPE_PIE2 || nPIEType == TPEP_DATATYPE_PIE3) ? pTMParameter->GetValueCount() : 0, nSamples = (nSampleLimit) ? min(nSamples, (INT)nSampleLimit) : nSamples; nSample < nSamples; nSample++)
		{
			if (pTMParameter->GetRawValue(nSample, nValue, nStatus) && pTMParameter->GetValueAsText(GetDatabase(), nSample, szValue[0]) && pTMParameter->GetValueAsText(GetDatabase(), nSample, (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE, szValue[1]))
			{
				szPIE = SPACE;
				szPIE += pTMParameter->GetTag();
				szPIE += SPACE;
				szPIE += cStringTools.ConvertUIntToString((nStatus != TMPARAMETER_STATUS_NONE) ? ((!(nStatus & TMPARAMETER_STATUS_BAD)) ? ((!bUnchanged) ? ((pTMParameter->GetLastChangeTMUnit() != pTMUnit->GetTag() || pTMParameter->GetLastChangeTime() != pTMUnit->GetTimeTag()) ? TPEP_DATAQUALITY_UPDATED : TPEP_DATAQUALITY_CHANGED) : TPEP_DATAQUALITY_UNCHANGED) : TPEP_DATAQUALITY_BAD) : TPEP_DATAQUALITY_NONE);
				szPIE += SPACE;
				szPIE += (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS  &&  szValue[0] != szValue[1]) ? (STRING(IDS_TPEP_DATA_DELIMITER) + szValue[0] + STRING(IDS_TPEP_DATA_DELIMITER)) : szValue[0];
				if (nPIEType == TPEP_DATATYPE_PIE2)
				{
					szPIE += SPACE;
					szPIE += cStringTools.ConvertUIntToString(((!(nStatus & TMPARAMETER_STATUS_NOLIMIT)) ? ((!(nStatus & TMPARAMETER_STATUS_SOFTLIMIT)) ? ((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? TPEP_DATASTATUS_DELTALIMIT : TPEP_DATASTATUS_HARDLIMIT) : TPEP_DATASTATUS_SOFTLIMIT) : TPEP_DATASTATUS_NOLIMIT) | ((nStatus & TMPARAMETER_STATUS_VALID) ? TPEP_DATASTATUS_VALID : TPEP_DATASTATUS_INVALID));
				}
				if (nPIEType == TPEP_DATATYPE_PIE3)
				{
					szPIE += SPACE;
					szPIE += szValue[1];
					szPIE += SPACE;
					szPIE += cStringTools.ConvertUIntToString(((!(nStatus & TMPARAMETER_STATUS_NOLIMIT)) ? ((!(nStatus & TMPARAMETER_STATUS_SOFTLIMIT)) ? ((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? TPEP_DATASTATUS_DELTALIMIT : TPEP_DATASTATUS_HARDLIMIT) : TPEP_DATASTATUS_SOFTLIMIT) : TPEP_DATASTATUS_NOLIMIT) | ((nStatus & TMPARAMETER_STATUS_VALID) ? TPEP_DATASTATUS_VALID : TPEP_DATASTATUS_INVALID));
					szPIE += SPACE;
					szPIE += pTMParameter->GetLastChangeTMUnit();
					szPIE += SPACE;
					szPIE += pTMParameter->GetLastChangeTime().FormatGmt(GetTPEPServiceSupport()->GetTPEPTimeKeyFormat());
					szPIE += SPACE;
					szPIE += pTMParameter->GetLastUpdateTMUnit();
					szPIE += SPACE;
					szPIE += pTMParameter->GetLastUpdateTime().FormatGmt(GetTPEPServiceSupport()->GetTPEPTimeKeyFormat());
				}
			}
		}
	}
	return szPIE;
}

VOID CTPEPServerSocket::ConvertPacket(CONST CByteArray &nData, CString &szPacket) CONST
{
	CByteArray  nDataBlock;

	nDataBlock.Copy(nData);
	nDataBlock.InsertAt(nDataBlock.GetSize(), 0, 1);
	if (nData.GetSize() != (INT)strlen((LPCSTR)nDataBlock.GetData()))
	{
#ifndef UNICODE
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(WCHAR)), szPacket.GetBufferSetLength((INT)(nData.GetSize() / sizeof(WCHAR))), (INT)(nData.GetSize() / sizeof(WCHAR) + 1), (LPCSTR)NULL, (LPBOOL)NULL);
		szPacket.ReleaseBuffer();
#else
		CopyMemory(szPacket.GetBufferSetLength((INT)(nData.GetSize() / sizeof(WCHAR))), nData.GetData(), (INT)nData.GetSize());
		szPacket.ReleaseBuffer();
#endif
	}
	else
	{
#ifndef UNICODE
		CopyMemory(szPacket.GetBufferSetLength((INT)(nData.GetSize() / sizeof(CHAR))), nData.GetData(), nData.GetSize());
		szPacket.ReleaseBuffer();
#else
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(CHAR)), szPacket.GetBufferSetLength((INT)(nData.GetSize() / sizeof(CHAR))), (INT)(nData.GetSize() / sizeof(CHAR) + 1));
		szPacket.ReleaseBuffer();
#endif
	}
}
BOOL CTPEPServerSocket::ConvertPacket(LPCTSTR pszPacket, CByteArray &nData) CONST
{
#ifndef UNICODE
	if (m_nCharset == TPEP_SERVICE_ASCIICHARSET)
	{
		nData.SetSize(lstrlen(pszPacket)*sizeof(CHAR));
		if (nData.GetSize() == lstrlen(pszPacket)*(INT) sizeof(CHAR))
		{
			CopyMemory(nData.GetData(), pszPacket, nData.GetSize());
			return TRUE;
		}
		return FALSE;
	}
	if (m_nCharset == TPEP_SERVICE_UNICODECHARSET)
	{
		nData.SetSize(lstrlen(pszPacket)*sizeof(WCHAR));
		if (nData.GetSize() == lstrlen(pszPacket)*(INT) sizeof(WCHAR))
		{
			MultiByteToWideChar(CP_ACP, 0, pszPacket, -1, (LPWSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(WCHAR)));
			return TRUE;
		}
	}
	if (m_nCharset == TPEP_SERVICE_DEFAULTCHARSET)
	{
		nData.RemoveAll();
		return TRUE;
	}
	return FALSE;
#else
	if (m_nCharset == TPEP_SERVICE_UNICODECHARSET)
	{
		nData.SetSize(lstrlen(pszPacket)*sizeof(WCHAR));
		if (nData.GetSize() == lstrlen(pszPacket)*(INT) sizeof(WCHAR))
		{
			CopyMemory(nData.GetData(), pszPacket, nData.GetSize());
			return TRUE;
		}
		return FALSE;
	}
	if (m_nCharset == TPEP_SERVICE_ASCIICHARSET)
	{
		nData.SetSize(lstrlen(pszPacket)*sizeof(CHAR));
		if (nData.GetSize() == lstrlen(pszPacket)*(INT) sizeof(CHAR))
		{
			WideCharToMultiByte(CP_ACP, 0, pszPacket, -1, (LPSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(CHAR)), (LPCSTR)NULL, (LPBOOL)NULL);
			return TRUE;
		}
	}
	if (m_nCharset == TPEP_SERVICE_DEFAULTCHARSET)
	{
		nData.RemoveAll();
		return TRUE;
	}
	return FALSE;
#endif
}

INT CTPEPServerSocket::SkipSpaces(LPCTSTR pszString, INT &nPos) CONST
{
	while (nPos < lstrlen(pszString) && _istspace(pszString[nPos])) nPos++;
	return nPos;
}

INT CTPEPServerSocket::SkipNumber(LPCTSTR pszString, INT &nPos) CONST
{
	while (nPos < lstrlen(pszString) && _istdigit(pszString[nPos])) nPos++;
	return nPos;
}

VOID CTPEPServerSocket::ShowLoginMessage()
{
	UINT  nCode;
	CString  szClient;
	CString  szAddress;
	CString  szMessage[2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if (GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime))
	{
		for (szMessage[0].Format(STRING(IDS_TPEP_SECURITY_LOGIN), (LPCTSTR)szClient, (LPCTSTR)szAddress); m_szLogin != szMessage[0]; )
		{
			if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
			{
				if ((pAlertInfo[1] = pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_TPEP_SECURITY_LOGIN)))))
				{
					for (szMessage[1].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TPEP_SECURITY_LOGIN), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)szClient, (LPCTSTR)szAddress); pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TPEP_SECURITY_LOGIN); )
					{
						szMessage[1] = pAlertInfo[1]->GetMessage();
						break;
					}
					pAlertInfo[0]->Copy(pAlertInfo[1]);
					pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
					pAlertInfo[0]->SetType(EVENT_TYPE_INFORMATIONAL);
					pAlertInfo[0]->SetExtraInfo(szClient + TAB + szAddress);
					pAlertInfo[0]->SetMessage(szMessage[1]);
					pAlertInfo[0]->SetTime(tAlertTime);
					ReportEvent(pAlertInfo[0]);
				}
				delete pAlertInfo[0];
			}
			ReportEvent((nCode & TPEP_SERVICE_AUDITACCESS) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, (m_szLogin = szMessage[0]), FALSE);
			break;
		}
	}
}

VOID CTPEPServerSocket::ShowLogoutMessage()
{
	UINT  nCode;
	UINT  nCount;
	CString  szClient;
	CString  szAddress;
	CString  szMessage[5];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeKey  tTime[3];
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	for (m_cConnection.GetStatistics(tTime[0], tTime[1], nCount); GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime); )
	{
		for (szMessage[0].Format(STRING(IDS_TPEP_SECURITY_LOGIN), (LPCTSTR)szClient, (LPCTSTR)szAddress), szMessage[1].Format(STRING(IDS_TPEP_SECURITY_LOGOUT), (LPCTSTR)szClient, (LPCTSTR)szAddress, max(tTime[2].GetTime() - tTime[0].GetTime(), 0) / SECONDSPERMINUTE), szMessage[2].Format(STRING(IDS_TPEP_SECURITY_LOGOUTQUICKLY), (LPCTSTR)szClient, (LPCTSTR)szAddress); m_szLogin == szMessage[0]; )
		{
			if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
			{
				if ((pAlertInfo[1] = pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_TPEP_SECURITY_LOGOUT)))))
				{
					for (szMessage[3].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TPEP_SECURITY_LOGOUT), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)szClient, (LPCTSTR)szAddress, max(tTime[2].GetTime() - tTime[0].GetTime(), 0) / SECONDSPERMINUTE), szMessage[4].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TPEP_SECURITY_LOGOUTQUICKLY), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)szClient, (LPCTSTR)szAddress); pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TPEP_SECURITY_LOGOUT); )
					{
						szMessage[3] = pAlertInfo[1]->GetMessage();
						szMessage[4] = pAlertInfo[1]->GetMessage();
						break;
					}
					pAlertInfo[0]->Copy(pAlertInfo[1]);
					pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
					pAlertInfo[0]->SetType(EVENT_TYPE_INFORMATIONAL);
					pAlertInfo[0]->SetExtraInfo(szClient + TAB + szAddress);
					pAlertInfo[0]->SetMessage(((tTime[2].GetTime() - tTime[0].GetTime()) / SECONDSPERMINUTE > 1) ? szMessage[3] : szMessage[4]);
					pAlertInfo[0]->SetTime(tAlertTime);
					ReportEvent(pAlertInfo[0]);
				}
				delete pAlertInfo[0];
			}
			ReportEvent((nCode & TPEP_SERVICE_AUDITACCESS) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, ((tTime[2].GetTime() - tTime[0].GetTime()) / SECONDSPERMINUTE > 1) ? szMessage[1] : szMessage[2], FALSE);
			break;
		}
		m_szLogin.Empty();
		break;
	}
}

VOID CTPEPServerSocket::Alert(LPCTSTR pszAlert)
{
	UINT  nCode;
	CString  szClient;
	CString  szAddress;
	CString  szMessage;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if (GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime) && lstrlen(pszAlert) > 0)
	{
		if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
		{
			if ((pAlertInfo[1] = pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_TPEP_SECURITY_ACCESSVIOLATION)))))
			{
				for (szMessage.Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TPEP_SECURITY_ACCESSVIOLATION), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)szClient, (LPCTSTR)szAddress); pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TPEP_SECURITY_ACCESSVIOLATION); )
				{
					szMessage = pAlertInfo[1]->GetMessage();
					break;
				}
				pAlertInfo[0]->Copy(pAlertInfo[1]);
				pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
				pAlertInfo[0]->SetType(EVENT_TYPE_INFORMATIONAL);
				pAlertInfo[0]->SetExtraInfo(szClient + TAB + szAddress);
				pAlertInfo[0]->SetMessage(szMessage);
				pAlertInfo[0]->SetTime(tAlertTime);
				ReportEvent(pAlertInfo[0]);
			}
			delete pAlertInfo[0];
		}
	}
}

BOOL CTPEPServerSocket::UpdateStatistics(INT cbData)
{
	UINT  nCount;
	CString  szClient;
	CTimeKey  tTime[3];

	for (m_cConnection.GetStatistics(tTime[0], tTime[1], nCount); cbData > 0; )
	{
		m_cConnection.SetStatistics((tTime[0] = (!tTime[0].GetTime()) ? tTime[2] : tTime[0]), (tTime[1] = tTime[2]), (nCount = (nCount + 1 > nCount) ? (nCount + 1) : nCount));
		break;
	}
	return((IsInitialized() && GetClient(szClient)) ? GetTPEPService()->UpdateServerConnection(szClient, &m_cConnection) : TRUE);
}

VOID CTPEPServerSocket::UpdateDisplays()
{
	INT  nDisplay;
	INT  nDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays.GetAt(nDisplay)))
		{
			pDisplayWnd->Update(&m_cConnection);
			continue;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTPEPServerSocket member functions

BOOL CTPEPServerSocket::OnMessagePending()
{
	MSG  sMsg;
	UINT  nCode;
	CString  szClient;
	CString  szAddress;
	CString  szMessage;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	while (PeekMessage(&sMsg, (HWND)NULL, WM_TIMER, WM_TIMER, PM_REMOVE))
	{
		if (IsInitialized() && m_nTimerID == (UINT_PTR)sMsg.wParam  &&  m_bSendData[0])
		{
			for (CancelBlockingCall(); GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime) && !m_bSendData[1]; )
			{
				szMessage.Format(STRING(IDS_TPEP_ALERT_LOWBANDWIDTH), (LPCTSTR)szClient, (LPCTSTR)szAddress);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				break;
			}
			KillTimer((HWND)NULL, m_nTimerID);
			m_bSendData[1] = TRUE;
			m_nTimerID = 0;
		}
	}
	return CSocket::OnMessagePending();
}

void CTPEPServerSocket::OnSend(int nErrorCode)
{
	UINT  nCode;
	CString  szClient;
	CString  szAddress;
	CString  szMessage;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	if (m_bSendData[1])
	{
		if (GetProperties(szClient, szAddress, nCode, tStartTime, tStopTime))
		{
			szMessage.Format(STRING(IDS_TPEP_ALERT_NORMALBANDWIDTH), (LPCTSTR)szClient, (LPCTSTR)szAddress);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		m_bSendData[1] = FALSE;
	}
	CSocket::OnSend(nErrorCode);
}

void CTPEPServerSocket::OnReceive(int nErrorCode)
{
	INT  nCode;
	UINT  nError;
	CString  szCode;
	CByteArray  nData;

	switch (Receive(nData))
	{
	case SOCKET_ERROR:
	{ ReportEvent(SYSTEM_WARNING_TPEP_RECEIVE_FAILURE);
	Close();
	break;
	}
	case 0:
	{ Close();
	break;
	}
	default:
	{ UpdateCharset(nData);
	if (!CheckServiceAvailability())
	{
		if (ConstructPacket(TPEP_ERROR_NOSERVICE, nData))
		{
			ReportEvent((Send(nData) == SOCKET_ERROR) ? SYSTEM_WARNING_TPEP_SEND_FAILURE : SYSTEM_NOERROR);
			Close();
			break;
		}
		ReportEvent(SYSTEM_WARNING_TPEP_REQUEST_FAILURE);
		Close();
		break;
	}
	if ((nCode = CheckServiceSecurity(szCode)) <= 0)
	{
		if (ConstructPacket(TPEP_ERROR_NOACCESS, nData))
		{
			ReportEvent((Send(nData) == SOCKET_ERROR) ? SYSTEM_WARNING_TPEP_SEND_FAILURE : SYSTEM_NOERROR);
			ReportEvent((!szCode.IsEmpty() && nCode < 0) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szCode, FALSE);
			Alert(szCode);
			Close();
			break;
		}
		ReportEvent(SYSTEM_WARNING_TPEP_REQUEST_FAILURE);
		Alert(szCode);
		Close();
		break;
	}
	if ((nError = ParsePacket(nData)))
	{
		if (ConstructPacket(nError, nData))
		{
			if (Send(nData) == SOCKET_ERROR)
			{
				ReportEvent(SYSTEM_WARNING_TPEP_SEND_FAILURE);
				Close();
			}
			else
			{
				m_cConnection.Reset();
				m_cConnection.SetStatistics(CTime::GetCurrentTime().GetTime(), CTime::GetCurrentTime().GetTime(), 0);
				Reset();
			}
		}
		else
		{
			ReportEvent(SYSTEM_WARNING_TPEP_REQUEST_FAILURE);
			Close();
		}
		break;
	}
	if (m_cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME)
	{
		ShowLoginMessage();
		UpdateStatistics();
		UpdateConnection();
		UpdateDisplays();
		break;
	}
	if (m_cConnection.GetDataMode() == TPEP_DATAMODE_HISTORY || m_cConnection.GetDataMode() == TPEP_DATAMODE_RANDOM)
	{
		if (!m_cServerThread.Start(&m_cConnection))
		{
			if (ConstructPacket(TPEP_ERROR_FAILURE, nData))
			{
				if (Send(nData) == SOCKET_ERROR)
				{
					ReportEvent(SYSTEM_WARNING_TPEP_SEND_FAILURE);
					Close();
					break;
				}
				Reset();
				break;
			}
			ReportEvent(SYSTEM_WARNING_TPEP_REQUEST_FAILURE);
			Close();
			break;
		}
		ShowLoginMessage();
		UpdateStatistics();
		UpdateDisplays();
	}
	break;
	}
	}
	CSocket::OnReceive(nErrorCode);
}

void CTPEPServerSocket::OnClose(int nErrorCode)
{
	Close();
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPServerSockets

CTPEPServerSockets::CTPEPServerSockets() : CPtrArray()
{
	return;
}

CTPEPServerSockets::~CTPEPServerSockets()
{
	RemoveAll();
}

BOOL CTPEPServerSockets::AddConnection(CTPEPServerSocket *pSocket)
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
	return((Add(pSocket) >= 0) ? TRUE : FALSE);
}

BOOL CTPEPServerSockets::AttachConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	CTPEPServerSocket  *pSocket;

	return(((pSocket = GetAt(FindConnection(pszClient, pConnection))) && pSocket->Attach(pDisplayWnd)) ? TRUE : FALSE);
}

BOOL CTPEPServerSockets::DetachConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	INT  nConnection;
	INT  nConnections;
	CTPEPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(FindConnection(pszClient, pConnection, nConnection))) && pSocket->Detach(pDisplayWnd)) break;
		if ((pSocket = GetAt(nConnection)) && pSocket->Detach(pDisplayWnd)) break;
	}
	return((nConnection < nConnections) ? TRUE : FALSE);
}

BOOL CTPEPServerSockets::RemoveConnection(LPCTSTR pszClient, CTPEPConnection *pConnection)
{
	CTPEPServerSocket  *pSocket;

	if ((pSocket = GetAt(FindConnection(pszClient, pConnection))))
	{
		RemoveAt(FindConnection(pszClient, pConnection));
		pSocket->Close();
		delete pSocket;
		return TRUE;
	}
	return FALSE;
}

INT CTPEPServerSockets::EnumConnections(CStringArray &szClients, CTPEPConnections &pConnections) CONST
{
	INT  nConnection;
	INT  nConnections;
	CString  szClient;
	CTPEPConnection  *pConnection;
	CTPEPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(), szClients.RemoveAll(), pConnections.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) != (CTPEPServerSocket *)NULL)
		{
			if ((pConnection = new CTPEPConnection) != (CTPEPConnection *)NULL)
			{
				if (pSocket->GetConnectionInfo(szClient, pConnection))
				{
					pConnections.Add(pConnection);
					szClients.Add(szClient);
					continue;
				}
				delete pConnection;
			}
		}
	}
	return((INT)szClients.GetSize());
}

VOID CTPEPServerSockets::UpdateConnections(CTimeSpan &tDelay)
{
	INT  nConnection;
	INT  nConnections;
	CTimeSpan  tConnection;
	CTPEPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(), tDelay = INFINITE; nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) != (CTPEPServerSocket *)NULL)
		{
			if (pSocket->AuthorizeConnection(tConnection))
			{
				if (tConnection != INFINITE)
				{
					if (tDelay == INFINITE)
					{
						tDelay = tConnection;
						continue;
					}
					tDelay = min(tConnection, tDelay);
				}
			}
		}
	}
}
BOOL CTPEPServerSockets::UpdateConnections(CONST CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError)
{
	INT  nConnection;
	INT  nConnections;
	CTPEPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (dwContext == (DWORD)-1) ? (INT)GetSize() : 0; nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->AuthorizeConnection(dwContext))
		{
			pSocket->UpdateConnection(pTMEnvironment, dwContext, nError);
			continue;
		}
	}
	for (nConnection = 0, nConnections = (dwContext != (DWORD)-1) ? (INT)GetSize() : 0; nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->AuthorizeConnection(dwContext)) break;
		continue;
	}
	return(((dwContext == (DWORD)-1 && nConnection == nConnections) || (dwContext != (DWORD)-1 && nConnection < nConnections  &&  pSocket->UpdateConnection(pTMEnvironment, dwContext, nError))) ? TRUE : FALSE);
}

CTPEPServerSocket *CTPEPServerSockets::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPServerSocket *)CPtrArray::GetAt(nIndex) : (CTPEPServerSocket *)NULL);
}

CTPEPServerSocket *CTPEPServerSockets::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPServerSocket *)CPtrArray::GetAt(nIndex) : (CTPEPServerSocket *)NULL);
}

VOID CTPEPServerSockets::RemoveAll()
{
	INT  nConnection;
	INT  nConnections;
	CTPEPServerSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)))
		{
			pSocket->ShutDown();
			delete pSocket;
		}
	}
	CPtrArray::RemoveAll();
}

INT CTPEPServerSockets::FindConnection(LPCTSTR pszClient, CONST CTPEPConnection *pConnection, INT nIndex) CONST
{
	INT  nConnection;
	INT  nConnections;
	CString  szClient;
	CTPEPConnection  cConnection;
	CTPEPServerSocket  *pSocket;

	for (nConnection = nIndex, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->GetConnectionInfo(szClient, &cConnection))
		{
			if (!szClient.CompareNoCase(pszClient) && cConnection.Compare(pConnection)) break;
			continue;
		}
	}
	return((nConnection < nConnections) ? nConnection : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPClientSocket

IMPLEMENT_DYNCREATE(CTPEPClientSocket, CSocket)

CTPEPClientSocket::CTPEPClientSocket() : CSocket()
{
	m_nTimerID = 0;
}

BOOL CTPEPClientSocket::Open(LPCTSTR pszServer, CONST CTPEPConnection *pConnection)
{
	INT  cbBuffer;
	CByteArray  nData;

	if (Create())
	{
		if (Connect(pszServer, GetTPEPService()->GetPort(), GetTPEPService()->GetTimeout()))
		{
			if (SetSockOpt(SO_SNDBUF, &(cbBuffer = GetTPEPService()->GetBufferSize()), sizeof(cbBuffer)) && SetSockOpt(SO_RCVBUF, &(cbBuffer = GetTPEPService()->GetBufferSize()), sizeof(cbBuffer)))
			{
				if (ConstructPacket(pConnection, nData) && Send(nData) != SOCKET_ERROR)
				{
					SetProperties(pszServer, pConnection);
					UpdateStatistics();
					return TRUE;
				}
			}
		}
		Close();
	}
	return FALSE;
}

BOOL CTPEPClientSocket::IsOpen() CONST
{
	return((m_hSocket != (SOCKET)INVALID_SOCKET) ? TRUE : FALSE);
}

VOID CTPEPClientSocket::Close()
{
	INT  nDisplay;
	INT  nDisplays;
	CTPEPWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CTPEPWnd *)m_pDisplays.GetAt(nDisplay)) && pDisplayWnd->IsRetrievingData())
		{
			pDisplayWnd->StopRetrieveData();
			continue;
		}
	}
	for (GetTPEPService()->UpdateClientConnection(m_szServer, &m_cConnection, TRUE); TRUE; )
	{
		Reset();
		break;
	}
	CSocket::Close();
}

BOOL CTPEPClientSocket::Connect(LPCTSTR pszAddress, UINT nPort, CONST CTimeSpan &tTimeout)
{
	if ((m_nTimerID = SetTimer((HWND)NULL, TPEPCLIENTSOCKET_CONNECTION_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), TPEPCLIENTSOCKET_CONNECTION_TIMEOUT), NULL)))
	{
		if (CSocket::Connect(pszAddress, nPort)) return TRUE;
		KillTimer((HWND)NULL, m_nTimerID);
		m_nTimerID = 0;
	}
	return FALSE;
}

VOID CTPEPClientSocket::Reset()
{
	INT  nDisplay;
	INT  nDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays.GetAt(nDisplay)))
		{
			pDisplayWnd->Update(EMPTYSTRING);
			continue;
		}
	}
	m_szData.Empty();
	m_szServer.Empty();
	m_cConnection.Reset();
	m_pDisplays.RemoveAll();
}

BOOL CTPEPClientSocket::IsInitialized() CONST
{
	return((m_cConnection.IsInitialized()) ? TRUE : FALSE);
}

VOID CTPEPClientSocket::SetProperties(LPCTSTR pszServer, CONST CTPEPConnection *pConnection)
{
	CTimeKey  tTime;

	m_szServer = pszServer;
	m_cConnection.Copy(pConnection);
	m_cConnection.SetStatistics(tTime, tTime, 0);
}

BOOL CTPEPClientSocket::GetProperties(CString &szServer, CTPEPConnection *pConnection) CONST
{
	szServer = m_szServer;
	pConnection->Copy(&m_cConnection, TRUE);
	return !szServer.IsEmpty();
}

INT CTPEPClientSocket::Send(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbBuffer;

	SetSockOpt(SO_SNDBUF, &(cbBuffer = GetTPEPService()->GetBufferSize()), sizeof(cbBuffer));
	return(((cbData = CSocket::Send(nData.GetData(), (INT)nData.GetSize())) == SOCKET_ERROR) ? ((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0) : cbData);
}

INT CTPEPClientSocket::Receive(CByteArray &nData)
{
	INT  cbData;
	INT  cbBuffer;

	for (nData.SetSize(GetTPEPService()->GetBufferSize()); nData.GetSize() == GetTPEPService()->GetBufferSize(); )
	{
		for (SetSockOpt(SO_RCVBUF, &(cbBuffer = GetTPEPService()->GetBufferSize()), sizeof(cbBuffer)); (cbData = CSocket::Receive(nData.GetData(), (INT)nData.GetSize())) != SOCKET_ERROR; )
		{
			UpdateStatistics(cbData);
			nData.SetSize(cbData);
			return cbData;
		}
		break;
	}
	return((GetLastError() != WSAECONNABORTED) ? SOCKET_ERROR : 0);
}

BOOL CTPEPClientSocket::Attach(CDisplayWnd *pDisplayWnd)
{
	INT  nDisplay;
	INT  nDisplays;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if (m_pDisplays.GetAt(nDisplay) == (LPVOID)pDisplayWnd) break;
		continue;
	}
	if (nDisplay == nDisplays  &&  pDisplayWnd != (CDisplayWnd *)NULL)
	{
		if (m_pDisplays.Add(pDisplayWnd) >= 0)
		{
			pDisplayWnd->Update(m_szData);
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CTPEPClientSocket::Detach(CDisplayWnd *pDisplayWnd)
{
	INT  nDisplay;
	INT  nDisplays;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if (m_pDisplays.GetAt(nDisplay) == (LPVOID)pDisplayWnd) break;
		continue;
	}
	if (nDisplay < nDisplays)
	{
		m_pDisplays.RemoveAt(nDisplay);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPClientSocket::ConstructPacket(CONST CTPEPConnection *pConnection, CByteArray &nData) CONST
{
	INT  nID;
	INT  nIDs;
	UINT  nPIE;
	UINT  nType;
	UINT  nMode;
	UINT  nLink;
	UINT  nSpeed;
	UINT  nTrigger;
	UINT  nSamples;
	CString  szPacket;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CStringArray  szIDs;
	CStringTools  cStringTools;

	if (((nType = pConnection->GetType()) == TPEP_TYPE_PACKETS  &&  pConnection->GetPackets(szIDs) > 0) || (nType == TPEP_TYPE_PARAMETERS  &&  pConnection->GetParameters(szIDs) > 0))
	{
		nMode = pConnection->GetDataMode();
		nLink = pConnection->GetDataLink();
		nPIE = pConnection->GetDataType();
		nTrigger = pConnection->GetTriggerMode();
		nSamples = pConnection->GetSampleLimit();
		tStartTime = pConnection->GetRetrieveStartTime();
		tStopTime = pConnection->GetRetrieveStopTime();
		nSpeed = pConnection->GetRetrieveSpeed();
		szPacket = (nType == TPEP_TYPE_PACKETS) ? STRING(IDS_TPEP_REQUEST_PACKETS_ID) : STRING(IDS_TPEP_REQUEST_PARAMETERS_ID);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(GetTPEPServiceSupport()->GetTPEPSpacecraftID());
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString((INT)szIDs.GetSize());
		for (nID = 0, nIDs = (INT)szIDs.GetSize(); nID < nIDs; nID++)
		{
			szPacket += SPACE;
			szPacket += szIDs.GetAt(nID);
		}
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(nMode);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(nLink);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(nPIE);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(nTrigger);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(nSamples);
		szPacket += SPACE;
		szPacket += (nMode == TPEP_DATAMODE_HISTORY) ? tStartTime.FormatGmt(GetTPEPServiceSupport()->GetTPEPRetrieveTimeKeyFormat()) : cStringTools.ConvertUIntToString(0);
		szPacket += SPACE;
		szPacket += (nMode == TPEP_DATAMODE_HISTORY) ? tStopTime.FormatGmt(GetTPEPServiceSupport()->GetTPEPRetrieveTimeKeyFormat()) : cStringTools.ConvertUIntToString(0);
		szPacket += SPACE;
		szPacket += cStringTools.ConvertUIntToString(nSpeed) + EOL;
		return ConvertPacket(szPacket, nData);
	}
	return FALSE;
}

VOID CTPEPClientSocket::ConvertPacket(CONST CByteArray &nData, CString &szData) CONST
{
	CByteArray  nDataBlock;

	nDataBlock.Copy(nData);
	nDataBlock.InsertAt(nDataBlock.GetSize(), 0, 1);
	if (nData.GetSize() != (INT)strlen((LPCSTR)nDataBlock.GetData()))
	{
#ifndef UNICODE
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(WCHAR)), szData.GetBufferSetLength((INT)(nData.GetSize() / sizeof(WCHAR))), (INT)(nData.GetSize() / sizeof(WCHAR) + 1), (LPCSTR)NULL, (LPBOOL)NULL);
		szData.ReleaseBuffer();
#else
		CopyMemory(szData.GetBufferSetLength((INT)(nData.GetSize() / sizeof(WCHAR))), nData.GetData(), (INT)nData.GetSize());
		szData.ReleaseBuffer();
#endif
	}
	else
	{
#ifndef UNICODE
		CopyMemory(szData.GetBufferSetLength((INT)(nData.GetSize() / sizeof(CHAR))), nData.GetData(), nData.GetSize());
		szData.ReleaseBuffer();
#else
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(CHAR)), szData.GetBufferSetLength((INT)(nData.GetSize() / sizeof(CHAR))), (INT)(nData.GetSize() / sizeof(CHAR) + 1));
		szData.ReleaseBuffer();
#endif
	}
}
BOOL CTPEPClientSocket::ConvertPacket(LPCTSTR pszData, CByteArray &nData) CONST
{
#ifndef UNICODE
	if (GetTPEPService()->GetCharset() != TPEP_SERVICE_UNICODECHARSET)
	{
		nData.SetSize(lstrlen(pszData)*sizeof(CHAR));
		if (nData.GetSize() == lstrlen(pszData)*(INT) sizeof(CHAR))
		{
			CopyMemory(nData.GetData(), pszData, nData.GetSize());
			return TRUE;
		}
		return FALSE;
	}
	nData.SetSize(lstrlen(pszData)*sizeof(WCHAR));
	if (nData.GetSize() == lstrlen(pszData)*(INT) sizeof(WCHAR))
	{
		MultiByteToWideChar(CP_ACP, 0, pszData, -1, (LPWSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(WCHAR)));
		return TRUE;
	}
	return FALSE;
#else
	if (GetTPEPService()->GetCharset() != TPEP_SERVICE_ASCIICHARSET)
	{
		nData.SetSize(lstrlen(pszData)*sizeof(WCHAR));
		if (nData.GetSize() == lstrlen(pszData)*(INT) sizeof(WCHAR))
		{
			CopyMemory(nData.GetData(), pszData, nData.GetSize());
			return TRUE;
		}
		return FALSE;
	}
	nData.SetSize(lstrlen(pszData)*sizeof(CHAR));
	if (nData.GetSize() == lstrlen(pszData)*(INT) sizeof(CHAR))
	{
		WideCharToMultiByte(CP_ACP, 0, pszData, -1, (LPSTR)nData.GetData(), (INT)(nData.GetSize() / sizeof(CHAR)), (LPCSTR)NULL, (LPBOOL)NULL);
		return TRUE;
	}
	return FALSE;
#endif
}

BOOL CTPEPClientSocket::UpdateStatistics(INT cbData)
{
	UINT  nCount;
	CTimeKey  tTime[3];

	for (m_cConnection.GetStatistics(tTime[0], tTime[1], nCount); cbData > 0; )
	{
		m_cConnection.SetStatistics((tTime[0] = (!tTime[0].GetTime()) ? tTime[2] : tTime[0]), (tTime[1] = tTime[2]), (nCount = (nCount + 1 > nCount) ? (nCount + 1) : nCount));
		break;
	}
	return((IsInitialized()) ? GetTPEPService()->UpdateClientConnection(m_szServer, &m_cConnection) : TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// CTPEPClientSocket member functions

BOOL CTPEPClientSocket::OnMessagePending()
{
	MSG  sMsg;

	while (PeekMessage(&sMsg, (HWND)NULL, WM_TIMER, WM_TIMER, PM_REMOVE))
	{
		if (m_nTimerID == (UINT_PTR)sMsg.wParam)
		{
			for (; !IsInitialized(); )
			{
				CancelBlockingCall();
				break;
			}
			KillTimer((HWND)NULL, m_nTimerID);
			m_nTimerID = 0;
			continue;
		}
		if (!AfxPreTranslateMessage(&sMsg))
		{
			TranslateMessage(&sMsg);
			DispatchMessage(&sMsg);
		}
	}
	return CSocket::OnMessagePending();
}

void CTPEPClientSocket::OnReceive(int nErrorCode)
{
	INT  nPos;
	INT  nDisplay;
	INT  nDisplays;
	CString  szData;
	CByteArray  nData;
	CDisplayWnd  *pDisplayWnd;

	switch (Receive(nData))
	{
	case SOCKET_ERROR:
	{ ReportEvent(SYSTEM_WARNING_TPEP_RECEIVE_FAILURE);
	Close();
	break;
	}
	case 0:
	{ Close();
	break;
	}
	default:
	{ for (ConvertPacket(nData, szData); (nPos = szData.Find(EOL)) >= 0; )
	{
		for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays.GetAt(nDisplay)))
			{
				pDisplayWnd->Update(szData.Left(nPos));
				continue;
			}
		}
		for (; nPos == szData.GetLength() - 1; )
		{
			m_szData = szData.Left(nPos);
			break;
		}
		szData = szData.Mid(nPos + 1);
	}
	break;
	}
	}
	CSocket::OnReceive(nErrorCode);
}

void CTPEPClientSocket::OnClose(int nErrorCode)
{
	Close();
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPClientSockets

CTPEPClientSockets::CTPEPClientSockets() : CPtrArray()
{
	return;
}

CTPEPClientSockets::~CTPEPClientSockets()
{
	RemoveAll();
}

BOOL CTPEPClientSockets::AddConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	CTPEPClientSocket  *pSocket;

	if ((pSocket = new CTPEPClientSocket))
	{
		if (pSocket->Open(pszServer, pConnection) && pSocket->Attach(pDisplayWnd))
		{
			Add(pSocket);
			return TRUE;
		}
		delete pSocket;
	}
	return FALSE;
}

BOOL CTPEPClientSockets::AttachConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	CTPEPClientSocket  *pSocket;

	return(((pSocket = GetAt(FindConnection(pszServer, pConnection))) && pSocket->Attach(pDisplayWnd)) ? TRUE : FALSE);
}

BOOL CTPEPClientSockets::DetachConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	INT  nConnection;
	INT  nConnections;
	CTPEPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(FindConnection(pszServer, pConnection, nConnection))) && pSocket->Detach(pDisplayWnd)) break;
		continue;
	}
	return((nConnection < nConnections) ? TRUE : FALSE);
}

BOOL CTPEPClientSockets::RemoveConnection(LPCTSTR pszServer, CTPEPConnection *pConnection)
{
	CTPEPClientSocket  *pSocket;

	if ((pSocket = GetAt(FindConnection(pszServer, pConnection))))
	{
		RemoveAt(FindConnection(pszServer, pConnection));
		pSocket->Close();
		delete pSocket;
		return TRUE;
	}
	return FALSE;
}

INT CTPEPClientSockets::EnumConnections(CStringArray &szServers, CTPEPConnections &pConnections) CONST
{
	INT  nConnection;
	INT  nConnections;
	CString  szServer;
	CTPEPConnection  *pConnection;
	CTPEPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(), szServers.RemoveAll(), pConnections.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) != (CTPEPClientSocket *)NULL)
		{
			if ((pConnection = new CTPEPConnection) != (CTPEPConnection *)NULL)
			{
				if (pSocket->GetProperties(szServer, pConnection))
				{
					pConnections.Add(pConnection);
					szServers.Add(szServer);
					continue;
				}
				delete pConnection;
			}
		}
	}
	return((INT)szServers.GetSize());
}

VOID CTPEPClientSockets::UpdateConnections()
{
	INT  nConnection;
	INT  nConnections;
	CTPEPClientSocket  *pSocket;

	for (nConnection = 0, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)))
		{
			if (!pSocket->IsOpen())
			{
				RemoveAt(nConnection);
				delete pSocket;
				nConnections--;
				nConnection--;
			}
		}
	}
}

CTPEPClientSocket *CTPEPClientSockets::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPClientSocket *)CPtrArray::GetAt(nIndex) : (CTPEPClientSocket *)NULL);
}

CTPEPClientSocket *CTPEPClientSockets::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPClientSocket *)CPtrArray::GetAt(nIndex) : (CTPEPClientSocket *)NULL);
}

VOID CTPEPClientSockets::RemoveAll()
{
	INT  nConnection;
	INT  nConnections;
	CTPEPClientSocket  *pSocket;

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

INT CTPEPClientSockets::FindConnection(LPCTSTR pszServer, CONST CTPEPConnection *pConnection, INT nIndex) CONST
{
	INT  nConnection;
	INT  nConnections;
	CString  szServer;
	CTPEPConnection  cConnection;
	CTPEPClientSocket  *pSocket;

	for (nConnection = nIndex, nConnections = (INT)GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pSocket = GetAt(nConnection)) && pSocket->GetProperties(szServer, &cConnection))
		{
			if (!szServer.CompareNoCase(pszServer) && cConnection.Compare(pConnection)) break;
			continue;
		}
	}
	return((nConnection < nConnections) ? nConnection : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceSocket

IMPLEMENT_DYNCREATE(CTPEPServiceSocket, CSocket)

BOOL CTPEPServiceSocket::Open()
{
	if (Create(GetTPEPService()->GetPort()))
	{
		if (Listen()) return TRUE;
		Close();
	}
	return FALSE;
}

VOID CTPEPServiceSocket::Close()
{
	m_pServerSockets.RemoveAll();
	m_pClientSockets.RemoveAll();
	CSocket::Close();
}

BOOL CTPEPServiceSocket::AddClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_pClientSockets.AddConnection(pszServer, pConnection, pDisplayWnd);
}

BOOL CTPEPServiceSocket::AttachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_pClientSockets.AttachConnection(pszServer, pConnection, pDisplayWnd);
}

BOOL CTPEPServiceSocket::DetachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_pClientSockets.DetachConnection(pszServer, pConnection, pDisplayWnd);
}

BOOL CTPEPServiceSocket::RemoveClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection)
{
	return m_pClientSockets.RemoveConnection(pszServer, pConnection);
}

BOOL CTPEPServiceSocket::AddServerConnection(CTPEPServerSocket *pSocket)
{
	return m_pServerSockets.AddConnection(pSocket);
}

BOOL CTPEPServiceSocket::AttachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_pServerSockets.AttachConnection(pszClient, pConnection, pDisplayWnd);
}

BOOL CTPEPServiceSocket::DetachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_pServerSockets.DetachConnection(pszClient, pConnection, pDisplayWnd);
}

BOOL CTPEPServiceSocket::RemoveServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection)
{
	return m_pServerSockets.RemoveConnection(pszClient, pConnection);
}

INT CTPEPServiceSocket::EnumClientConnections(CStringArray &szServers, CTPEPConnections &pConnections) CONST
{
	return m_pClientSockets.EnumConnections(szServers, pConnections);
}

INT CTPEPServiceSocket::EnumServerConnections(CStringArray &szClients, CTPEPConnections &pConnections) CONST
{
	return m_pServerSockets.EnumConnections(szClients, pConnections);
}

VOID CTPEPServiceSocket::UpdateClientConnections()
{
	m_pClientSockets.UpdateConnections();
}

VOID CTPEPServiceSocket::UpdateServerConnections(CTimeSpan &tDelay)
{
	m_pServerSockets.UpdateConnections(tDelay);
}

BOOL CTPEPServiceSocket::UpdateConnections(CONST CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError)
{
	return m_pServerSockets.UpdateConnections(pTMEnvironment, dwContext, nError);
}

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceSocket member functions

void CTPEPServiceSocket::OnAccept(int nErrorCode)
{
	CTPEPServerSocket  *pSocket;

	if ((pSocket = new CTPEPServerSocket))
	{
		if (pSocket->Open() && Accept(*pSocket))
		{
			AddServerConnection(pSocket);
			return;
		}
		pSocket->Close();
		delete pSocket;
	}
	ReportEvent(SYSTEM_WARNING_TPEP_CONNECT_FAILURE);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceStackElement

CTPEPServiceStackElement::CTPEPServiceStackElement() : CObject()
{
	m_nAction = NONE;
	m_nError = 0;
	m_nStatus = 0;
	m_dwContext = 0;
	m_nResultCode = 0;
	m_hDoneFlag = (HANDLE)NULL;
	m_pTMEnvironment = (CTMEnvironment *)NULL;
	m_pDisplay = (CDisplayWnd *)NULL;
}

VOID CTPEPServiceStackElement::SetAction(CTPEPServiceStackElement::TPEPAction nAction)
{
	m_nAction = nAction;
}

CTPEPServiceStackElement::TPEPAction CTPEPServiceStackElement::GetAction() CONST
{
	return m_nAction;
}

VOID CTPEPServiceStackElement::SetResult(UINT nCode)
{
	m_nResultCode = nCode;
}

UINT CTPEPServiceStackElement::GetResult() CONST
{
	return m_nResultCode;
}

VOID CTPEPServiceStackElement::SetStatus(UINT nStatus)
{
	for (m_nStatus = nStatus; nStatus; )
	{
		m_cEvent.SetEvent();
		break;
	}
}

UINT CTPEPServiceStackElement::GetStatus() CONST
{
	return m_nStatus;
}

VOID CTPEPServiceStackElement::SetServer(LPCTSTR pszServer)
{
	m_szServer = pszServer;
}

CString CTPEPServiceStackElement::GetServer() CONST
{
	return m_szServer;
}

VOID CTPEPServiceStackElement::SetClient(LPCTSTR pszClient)
{
	m_szClient = pszClient;
}

CString CTPEPServiceStackElement::GetClient() CONST
{
	return m_szClient;
}

VOID CTPEPServiceStackElement::SetConnection(CONST CTPEPConnection *pConnection)
{
	m_cConnection.Copy(pConnection);
}

BOOL CTPEPServiceStackElement::GetConnection(CTPEPConnection *pConnection) CONST
{
	pConnection->Copy(&m_cConnection);
	return((pConnection->GetType() == TPEP_TYPE_PACKETS || pConnection->GetType() == TPEP_TYPE_PARAMETERS) ? TRUE : FALSE);
}

VOID CTPEPServiceStackElement::SetData(CTMEnvironment *pTMEnvironment)
{
	m_pTMEnvironment = pTMEnvironment;
}

CTMEnvironment *CTPEPServiceStackElement::GetData() CONST
{
	return m_pTMEnvironment;
}

VOID CTPEPServiceStackElement::SetDisplay(CDisplayWnd *pDisplayWnd)
{
	m_pDisplay = pDisplayWnd;
}

CDisplayWnd *CTPEPServiceStackElement::GetDisplay() CONST
{
	return m_pDisplay;
}

VOID CTPEPServiceStackElement::SetContext(DWORD dwContext)
{
	m_dwContext = dwContext;
}

DWORD CTPEPServiceStackElement::GetContext() CONST
{
	return m_dwContext;
}

VOID CTPEPServiceStackElement::SetError(UINT nError)
{
	m_nError = nError;
}

UINT CTPEPServiceStackElement::GetError() CONST
{
	return m_nError;
}

VOID CTPEPServiceStackElement::SetFlag(HANDLE hFlag)
{
	m_hDoneFlag = hFlag;
}

HANDLE CTPEPServiceStackElement::GetFlag() CONST
{
	return m_hDoneFlag;
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceStack

CTPEPServiceStack::CTPEPServiceStack() : CPtrArray()
{
	return;
}

CTPEPServiceStack::~CTPEPServiceStack()
{
	RemoveAll();
}

INT CTPEPServiceStack::Add(CTPEPServiceStackElement *pElement)
{
	return((INT)CPtrArray::Add(pElement));
}

INT CTPEPServiceStack::Find(CONST CTPEPServiceStackElement *pElement) CONST
{
	INT  nElement;
	INT  nElements;

	for (nElement = 0, nElements = (INT)GetSize(); nElement < nElements; nElement++)
	{
		if (GetAt(nElement) == pElement) break;
		continue;
	}
	return((nElement < nElements) ? nElement : -1);
}

CTPEPServiceStackElement *CTPEPServiceStack::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPServiceStackElement *)CPtrArray::GetAt(nIndex) : (CTPEPServiceStackElement *)NULL);
}

CTPEPServiceStackElement *CTPEPServiceStack::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPServiceStackElement *)CPtrArray::GetAt(nIndex) : (CTPEPServiceStackElement *)NULL);
}

VOID CTPEPServiceStack::RemoveAll()
{
	INT  nElement;
	INT  nElements;

	for (nElement = 0, nElements = (INT)GetSize(); nElement < nElements; nElement++)
	{
		delete GetAt(nElement);
		continue;
	}
	CPtrArray::RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceThread

IMPLEMENT_DYNCREATE(CTPEPServiceThread, CThread)

CTPEPServiceThread::CTPEPServiceThread() : CThread()
{
	m_bAvailable = TRUE;
}

BOOL CTPEPServiceThread::Start()
{
	HANDLE  hEvents[2];

	for (Stop(), hEvents[0] = m_bInitialization[0], hEvents[1] = m_bInitialization[1]; CreateThread() && WaitForMultipleObjects(sizeof(hEvents) / sizeof(hEvents[0]), hEvents, FALSE, INFINITE) == WAIT_OBJECT_0; )
	{
		if (Update()) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CTPEPServiceThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::Update()
{
	return m_bUpdate.SetEvent();
}

BOOL CTPEPServiceThread::InitInstance()
{
	if (AfxSocketInit() && m_cSocket.Open())
	{
		m_bInitialization[0].SetEvent();
		return TRUE;
	}
	m_bInitialization[1].SetEvent();
	return FALSE;
}

int CTPEPServiceThread::ExitInstance()
{
	m_cSocket.Close();
	return CThread::ExitInstance();
}

BOOL CTPEPServiceThread::AddClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::ADDCLIENTCONNECTION);
			pElement->SetServer(pszServer);
			pElement->SetConnection(pConnection);
			pElement->SetDisplay(pDisplayWnd);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::AttachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::ATTACHSERVERCONNECTION);
			pElement->SetClient(pszClient);
			pElement->SetConnection(pConnection);
			pElement->SetDisplay(pDisplayWnd);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::AttachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::ATTACHCLIENTCONNECTION);
			pElement->SetServer(pszServer);
			pElement->SetConnection(pConnection);
			pElement->SetDisplay(pDisplayWnd);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::DetachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::DETACHSERVERCONNECTION);
			pElement->SetClient(pszClient);
			pElement->SetConnection(pConnection);
			pElement->SetDisplay(pDisplayWnd);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::DetachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::DETACHCLIENTCONNECTION);
			pElement->SetServer(pszServer);
			pElement->SetConnection(pConnection);
			pElement->SetDisplay(pDisplayWnd);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::RemoveServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::REMOVESERVERCONNECTION);
			pElement->SetClient(pszClient);
			pElement->SetConnection(pConnection);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::RemoveClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::REMOVECLIENTCONNECTION);
			pElement->SetServer(pszServer);
			pElement->SetConnection(pConnection);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

BOOL CTPEPServiceThread::UpdateConnections(CTMEnvironment *pTMEnvironment, HANDLE hFlag, DWORD dwContext, UINT nError)
{
	CTPEPServiceStackElement  *pElement;

	if (Lock())
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::UPDATECONNECTIONS);
			pElement->SetData(pTMEnvironment);
			pElement->SetContext(dwContext);
			pElement->SetFlag(hFlag);
			pElement->SetError(nError);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Update();
				Unlock();
				return TRUE;
			}
			delete pElement;
		}
		Unlock();
	}
	return FALSE;
}
BOOL CTPEPServiceThread::UpdateConnections(CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError)
{
	UINT  nResult;
	CTPEPServiceStackElement  *pElement;

	for (; Lock(); )
	{
		if ((pElement = (IsThreadActive()) ? new CTPEPServiceStackElement : (CTPEPServiceStackElement *)NULL))
		{
			pElement->SetAction(CTPEPServiceStackElement::UPDATECONNECTIONS);
			pElement->SetData(pTMEnvironment);
			pElement->SetContext(dwContext);
			pElement->SetError(nError);
			if (m_cTPEPServiceStack.Add(pElement) >= 0)
			{
				Unlock();
				break;
			}
			delete pElement;
		}
		Unlock();
		return FALSE;
	}
	return(((nResult = WaitResult(pElement)) > 0 && nResult != (UINT)-1) ? TRUE : FALSE);
}

UINT CTPEPServiceThread::WaitResult(CONST CTPEPServiceStackElement *pElement)
{
	INT  nIndex;
	UINT  nResult;
	HANDLE  hObjects[2];
	CTPEPConnection  cConnection;

	if (IsThreadActive())
	{
		for (; GetThreadID() == GetCurrentThreadId(); )
		{
			if (pElement->GetAction() == CTPEPServiceStackElement::ADDCLIENTCONNECTION)
			{
				nResult = (pElement->GetConnection(&cConnection)) ? m_cSocket.AddClientConnection(pElement->GetServer(), &cConnection, pElement->GetDisplay()) : FALSE;
				break;
			}
			if (pElement->GetAction() == CTPEPServiceStackElement::ATTACHSERVERCONNECTION)
			{
				nResult = (pElement->GetConnection(&cConnection)) ? m_cSocket.AttachServerConnection(pElement->GetClient(), &cConnection, pElement->GetDisplay()) : FALSE;
				break;
			}
			if (pElement->GetAction() == CTPEPServiceStackElement::ATTACHCLIENTCONNECTION)
			{
				nResult = (pElement->GetConnection(&cConnection)) ? m_cSocket.AttachClientConnection(pElement->GetServer(), &cConnection, pElement->GetDisplay()) : FALSE;
				break;
			}
			if (pElement->GetAction() == CTPEPServiceStackElement::DETACHSERVERCONNECTION)
			{
				nResult = (pElement->GetConnection(&cConnection)) ? m_cSocket.DetachServerConnection(pElement->GetClient(), &cConnection, pElement->GetDisplay()) : FALSE;
				break;
			}
			if (pElement->GetAction() == CTPEPServiceStackElement::DETACHCLIENTCONNECTION)
			{
				nResult = (pElement->GetConnection(&cConnection)) ? m_cSocket.DetachClientConnection(pElement->GetServer(), &cConnection, pElement->GetDisplay()) : FALSE;
				break;
			}
			if (pElement->GetAction() == CTPEPServiceStackElement::REMOVESERVERCONNECTION)
			{
				nResult = (pElement->GetConnection(&cConnection)) ? m_cSocket.RemoveServerConnection(pElement->GetClient(), &cConnection) : FALSE;
				break;
			}
			if (pElement->GetAction() == CTPEPServiceStackElement::REMOVECLIENTCONNECTION)
			{
				nResult = (pElement->GetConnection(&cConnection)) ? m_cSocket.RemoveClientConnection(pElement->GetServer(), &cConnection) : FALSE;
				break;
			}
			if (pElement->GetAction() == CTPEPServiceStackElement::UPDATECONNECTIONS)
			{
				nResult = m_cSocket.UpdateConnections(pElement->GetData(), pElement->GetContext(), pElement->GetError());
				break;
			}
			nResult = (UINT)-1;
			break;
		}
		if (GetThreadID() != GetCurrentThreadId())
		{
			for (hObjects[0] = m_hObject, hObjects[1] = pElement->m_cEvent, nResult = (UINT)-1; Update() && WaitForMultipleObjects(sizeof(hObjects) / sizeof(hObjects[0]), hObjects, FALSE, INFINITE) == WAIT_OBJECT_0 + 1; )
			{
				nResult = pElement->GetResult();
				break;
			}
		}
		if (Lock())
		{
			if ((nIndex = m_cTPEPServiceStack.Find(pElement)) >= 0)
			{
				m_cTPEPServiceStack.RemoveAt(nIndex);
				delete pElement;
			}
			Unlock();
			return nResult;
		}
	}
	return((UINT)-1);
}

int CTPEPServiceThread::Run()
{
	INT  nItem;
	INT  nItems;
	UINT  nCode;
	DWORD  dwWait;
	DWORD  dwResult;
	CString  szText;
	CTimeKey  tTime[2];
	CTimeSpan  tDelay;
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	CTPEPConnection  cConnection;
	CTPEPServiceStackElement  *pElement;

	do
	{
		if (Lock())
		{
			for (nItem = 0, nItems = (INT)m_cTPEPServiceStack.GetSize(), m_cSocket.UpdateServerConnections(tDelay), m_cSocket.UpdateClientConnections(); nItem < nItems; nItem++)
			{
				if ((pElement = m_cTPEPServiceStack.GetAt(nItem)) && !pElement->GetStatus())
				{
					if (pElement->GetAction() == CTPEPServiceStackElement::ADDCLIENTCONNECTION)
					{
						pElement->SetResult((pElement->GetConnection(&cConnection)) ? m_cSocket.AddClientConnection(pElement->GetServer(), &cConnection, pElement->GetDisplay()) : FALSE);
						pElement->SetStatus(TRUE);
					}
					if (pElement->GetAction() == CTPEPServiceStackElement::ATTACHSERVERCONNECTION)
					{
						pElement->SetResult((pElement->GetConnection(&cConnection)) ? m_cSocket.AttachServerConnection(pElement->GetClient(), &cConnection, pElement->GetDisplay()) : FALSE);
						pElement->SetStatus(TRUE);
					}
					if (pElement->GetAction() == CTPEPServiceStackElement::ATTACHCLIENTCONNECTION)
					{
						pElement->SetResult((pElement->GetConnection(&cConnection)) ? m_cSocket.AttachClientConnection(pElement->GetServer(), &cConnection, pElement->GetDisplay()) : FALSE);
						pElement->SetStatus(TRUE);
					}
					if (pElement->GetAction() == CTPEPServiceStackElement::DETACHSERVERCONNECTION)
					{
						pElement->SetResult((pElement->GetConnection(&cConnection)) ? m_cSocket.DetachServerConnection(pElement->GetClient(), &cConnection, pElement->GetDisplay()) : FALSE);
						pElement->SetStatus(TRUE);
					}
					if (pElement->GetAction() == CTPEPServiceStackElement::DETACHCLIENTCONNECTION)
					{
						pElement->SetResult((pElement->GetConnection(&cConnection)) ? m_cSocket.DetachClientConnection(pElement->GetServer(), &cConnection, pElement->GetDisplay()) : FALSE);
						pElement->SetStatus(TRUE);
					}
					if (pElement->GetAction() == CTPEPServiceStackElement::REMOVESERVERCONNECTION)
					{
						pElement->SetResult((pElement->GetConnection(&cConnection)) ? m_cSocket.RemoveServerConnection(pElement->GetClient(), &cConnection) : FALSE);
						pElement->SetStatus(TRUE);
					}
					if (pElement->GetAction() == CTPEPServiceStackElement::REMOVECLIENTCONNECTION)
					{
						pElement->SetResult((pElement->GetConnection(&cConnection)) ? m_cSocket.RemoveClientConnection(pElement->GetServer(), &cConnection) : FALSE);
						pElement->SetStatus(TRUE);
					}
					if (pElement->GetAction() == CTPEPServiceStackElement::UPDATECONNECTIONS)
					{
						for (pElement->SetResult(m_cSocket.UpdateConnections(pElement->GetData(), pElement->GetContext(), pElement->GetError())), pElement->SetStatus(TRUE); pElement->GetFlag() != (HANDLE)NULL; )
						{
							SetEvent(pElement->GetFlag());
							m_cTPEPServiceStack.RemoveAt(nItem);
							delete pElement;
							nItems--;
							nItem--;
							break;
						}
					}
				}
			}
			if (GetTPEPService()->GetAvailabilityInfo(nCode, tStartTime, tStopTime))
			{
				tTime[0] = tTime[1] = CTime::GetCurrentTime().GetTime();
				tTime[1] = tTime[1].GetTime() + tTime[1].GetBias();
				if (nCode & TPEP_SERVICE_WORKINGDAYSAVAILABILITY)
				{
					if (tTime[1].GetDayOfWeek() != Monday  &&  tTime[1].GetDayOfWeek() != Tuesday  &&  tTime[1].GetDayOfWeek() != Wednesday  &&  tTime[1].GetDayOfWeek() != Thursday  &&  tTime[1].GetDayOfWeek() != Friday)
					{
						ReportEvent((m_bAvailable && (nCode & TPEP_SERVICE_AUDITAVAILABILITY)) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, (m_bAvailable && (nCode & TPEP_SERVICE_AUDITAVAILABILITY)) ? STRING(IDS_TPEP_SCHEDULE_INACTIVEWEEKDAYS) : EMPTYSTRING, FALSE);
						dwWait = (DWORD)(1000 * (SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY + 1) - tTime[0].GetTime()));
						dwWait = (tDelay != INFINITE) ? (DWORD)(1000 * min(tDelay.GetTotalSeconds(), (INT)(dwWait / 1000))) : dwWait;
						m_bAvailable = FALSE;
						Unlock();
						continue;
					}
					dwWait = (DWORD)(1000 * (SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY + 1) - tTime[0].GetTime()));
					dwWait = (tDelay != INFINITE) ? (DWORD)(1000 * min(tDelay.GetTotalSeconds(), (INT)(dwWait / 1000))) : dwWait;
				}
				if (nCode & TPEP_SERVICE_DAILYAVAILABILITY)
				{
					if (tTime[0].GetTime() % SECONDSPERDAY < tStartTime.GetTotalSeconds() || tTime[0].GetTime() % SECONDSPERDAY > tStopTime.GetTotalSeconds())
					{
						szText.Format(STRING(IDS_TPEP_SCHEDULE_INACTIVEDAILY), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY) + tStartTime.GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tTime[0].GetTime() / SECONDSPERDAY) + tStopTime.GetTotalSeconds()).FormatGmt(IDS_TIMEKEY_TIMEFORMAT));
						ReportEvent((m_bAvailable && (nCode & TPEP_SERVICE_AUDITAVAILABILITY)) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, (m_bAvailable && (nCode & TPEP_SERVICE_AUDITAVAILABILITY)) ? (LPCTSTR)szText : EMPTYSTRING, FALSE);
						dwWait = (tTime[0].GetTime() % SECONDSPERDAY > tStopTime.GetTotalSeconds()) ? (DWORD)(1000 * (SECONDSPERDAY - tTime[0].GetTime() % SECONDSPERDAY + tStartTime.GetTotalSeconds())) : (DWORD)(1000 * (tStartTime.GetTotalSeconds() - tTime[0].GetTime() % SECONDSPERDAY));
						dwWait = (tDelay != INFINITE) ? (DWORD)(1000 * min(tDelay.GetTotalSeconds(), (INT)(dwWait / 1000))) : dwWait;
						m_bAvailable = FALSE;
						Unlock();
						continue;
					}
					dwWait = (DWORD)(1000 * (tStopTime.GetTotalSeconds() - tTime[0].GetTime() % SECONDSPERDAY));
					dwWait = (tDelay != INFINITE) ? (DWORD)(1000 * min(tDelay.GetTotalSeconds(), (INT)(dwWait / 1000))) : dwWait;
				}
				if ((nCode & TPEP_SERVICE_DAILYAVAILABILITY) || (nCode & TPEP_SERVICE_WORKINGDAYSAVAILABILITY))
				{
					ReportEvent((!m_bAvailable && (nCode & TPEP_SERVICE_AUDITAVAILABILITY)) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, (!m_bAvailable && (nCode & TPEP_SERVICE_AUDITAVAILABILITY)) ? STRING(IDS_TPEP_SCHEDULE_ACTIVATED) : EMPTYSTRING, FALSE);
					m_bAvailable = TRUE;
					Unlock();
					continue;
				}
				dwWait = (tDelay != INFINITE) ? (DWORD)(1000 * min(tDelay.GetTotalSeconds(), SECONDSPERDAY)) : INFINITE;
				m_bAvailable = TRUE;
				Unlock();
				continue;
			}
			Unlock();
		}
		break;
	} while ((dwResult = Wait(m_bUpdate, FALSE, dwWait)) == WAIT_TIMEOUT || dwResult == WAIT_OBJECT_0 + 1);
	return ExitInstance();
}

BEGIN_MESSAGE_MAP(CTPEPServiceThread, CThread)
	//{{AFX_MSG_MAP(CTPEPServiceThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTPEPService

CTPEPService::CTPEPService() : CObject()
{
	m_nPort = TPEP_SERVICE_DEFAULTPORT;
	m_nCode = TPEP_SERVICE_UNLIMITEDAVAILABILITY;
	m_nBufferSize = TPEP_SERVICE_DEFAULTBUFFERSIZE;
	m_tTimeout = TPEP_SERVICE_DEFAULTTIMEOUT;
	m_nCharset = TPEP_SERVICE_DEFAULTCHARSET;
	m_tStartTime = 0;
	m_tStopTime = 0;
}

BOOL CTPEPService::Start()
{
	CByteArray  nProfilesInfo[2];
	CTPEPServiceEngine  *pTPEPServiceSupport;
	CProfile  cProfile;

	if ((pTPEPServiceSupport = GetTPEPServiceSupport()) && pTPEPServiceSupport->GetTPEPSupport())
	{
		if (cProfile.GetTPEPServiceSettingsInfo(m_nPort, m_nBufferSize, m_nCharset, m_tTimeout) && cProfile.GetTPEPServiceAvailabilityInfo(m_nCode, m_tStartTime, m_tStopTime) && cProfile.GetTPEPServiceSecurityInfo(m_szUsers, m_nAccessCodes, m_tStartTimes, m_tStopTimes) && cProfile.GetTPEPServiceProfileInfo(nProfilesInfo[0], nProfilesInfo[1]) && m_pPacketProfiles.Unmap(nProfilesInfo[0]) && m_pParameterProfiles.Unmap(nProfilesInfo[1]))
		{
			if (GetSystemMetrics(SM_REMOTESESSION) || !m_cServiceThread.Start()) ReportEvent(SYSTEM_INFORMATIONAL_TPEP_NOT_AVAILABLE, !GetSystemMetrics(SM_REMOTESESSION));
			return TRUE;
		}
		ReportEvent(SYSTEM_WARNING_TPEP_LOAD_FAILURE);
	}
	return FALSE;
}

BOOL CTPEPService::Stop()
{
	CByteArray  nProfilesInfo[2];
	CTPEPServiceEngine  *pTPEPServiceSupport;
	CProfile  cProfile;

	if ((pTPEPServiceSupport = GetTPEPServiceSupport()) && pTPEPServiceSupport->GetTPEPSupport())
	{
		for (m_cServiceThread.Stop(); cProfile.SetTPEPServiceSettingsInfo(m_nPort, m_nBufferSize, m_nCharset, m_tTimeout) && cProfile.SetTPEPServiceAvailabilityInfo(m_nCode, m_tStartTime, m_tStopTime) && cProfile.SetTPEPServiceSecurityInfo(m_szUsers, m_nAccessCodes, m_tStartTimes, m_tStopTimes) && m_pPacketProfiles.Map(nProfilesInfo[0]) && m_pParameterProfiles.Map(nProfilesInfo[1]) && cProfile.SetTPEPServiceProfileInfo(nProfilesInfo[0], nProfilesInfo[1]); ) return TRUE;
		ReportEvent(SYSTEM_WARNING_TPEP_SAVE_FAILURE);
	}
	return FALSE;
}

BOOL CTPEPService::SetPort(UINT nPort)
{
	for (Lock(); nPort >= TPEP_SERVICE_FIRSTPORT && nPort <= TPEP_SERVICE_LASTPORT; )
	{
		if (!GetTPEPServiceSupport()->GetTPEPSupport() || m_nPort == nPort)
		{
			m_nPort = nPort;
			Unlock();
			return TRUE;
		}
		m_nPort = nPort;
		Unlock();
		return m_cServiceThread.Start();
	}
	Unlock();
	return FALSE;
}

BOOL CTPEPService::GetPort(UINT &nPort) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nPort = m_nPort;
	return TRUE;
}
UINT CTPEPService::GetPort() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_nPort;
}

BOOL CTPEPService::SetBufferSize(UINT nSize)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nSize >= TPEP_SERVICE_MINIMUMBUFFERSIZE  &&  nSize <= TPEP_SERVICE_MAXIMUMBUFFERSIZE)
	{
		m_nBufferSize = nSize;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPService::GetBufferSize(UINT &nSize) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nSize = m_nBufferSize;
	return TRUE;
}
UINT CTPEPService::GetBufferSize() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_nBufferSize;
}

BOOL CTPEPService::SetTimeout(CONST CTimeSpan &tTimeout)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	m_tTimeout = tTimeout;
	return TRUE;
}

BOOL CTPEPService::GetTimeout(CTimeSpan &tTimeout) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	tTimeout = m_tTimeout;
	return TRUE;
}
CTimeSpan CTPEPService::GetTimeout() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_tTimeout;
}

BOOL CTPEPService::SetCharset(UINT nCharset)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nCharset == TPEP_SERVICE_DEFAULTCHARSET || nCharset == TPEP_SERVICE_ASCIICHARSET || nCharset == TPEP_SERVICE_UNICODECHARSET)
	{
		m_nCharset = nCharset;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPService::GetCharset(UINT &nCharset) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nCharset = m_nCharset;
	return TRUE;
}
UINT CTPEPService::GetCharset() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_nCharset;
}

BOOL CTPEPService::SetAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nCode & TPEP_SERVICE_NOAVAILABILITY)
	{
		m_nCode = nCode;
		m_tStartTime = 0;
		m_tStopTime = 0;
		return m_cServiceThread.Update();
	}
	if (nCode & TPEP_SERVICE_UNLIMITEDAVAILABILITY)
	{
		m_nCode = nCode & (TPEP_SERVICE_UNLIMITEDAVAILABILITY | TPEP_SERVICE_WORKINGDAYSAVAILABILITY | TPEP_SERVICE_AUDITAVAILABILITY);
		m_tStartTime = 0;
		m_tStopTime = 0;
		return m_cServiceThread.Update();
	}
	if ((nCode & TPEP_SERVICE_DAILYAVAILABILITY) && tStartTime < tStopTime)
	{
		m_nCode = nCode & (TPEP_SERVICE_DAILYAVAILABILITY | TPEP_SERVICE_WORKINGDAYSAVAILABILITY | TPEP_SERVICE_AUDITAVAILABILITY);
		m_tStartTime = tStartTime;
		m_tStopTime = tStopTime;
		return m_cServiceThread.Update();
	}
	return FALSE;
}

BOOL CTPEPService::GetAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nCode = m_nCode;
	tStartTime = m_tStartTime;
	tStopTime = m_tStopTime;
	return TRUE;
}

BOOL CTPEPService::SetSecurityInfo(CONST CStringArray &szUsers, CONST CUIntArray &nCodes, CONST CTimeKeyArray &tStartTimes, CONST CTimeKeyArray &tStopTimes)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (szUsers.GetSize() == nCodes.GetSize() && szUsers.GetSize() == tStartTimes.GetSize() && tStartTimes.GetSize() == tStopTimes.GetSize())
	{
		m_szUsers.Copy(szUsers);
		m_nAccessCodes.Copy(nCodes);
		m_tStartTimes.Copy(tStartTimes);
		m_tStopTimes.Copy(tStopTimes);
		return m_cServiceThread.Update();
	}
	return FALSE;
}

BOOL CTPEPService::GetSecurityInfo(CStringArray &szUsers, CUIntArray &nCodes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	szUsers.Copy(m_szUsers);
	nCodes.Copy(m_nAccessCodes);
	tStartTimes.Copy(m_tStartTimes);
	tStopTimes.Copy(m_tStopTimes);
	return TRUE;
}

BOOL CTPEPService::SetPacketProfiles(CONST CTPEPDataProfiles *pPacketProfiles)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_pPacketProfiles.Copy(pPacketProfiles);
}

BOOL CTPEPService::GetPacketProfiles(CTPEPDataProfiles *pPacketProfiles) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return pPacketProfiles->Copy(&m_pPacketProfiles);
}

BOOL CTPEPService::SetParameterProfiles(CONST CTPEPDataProfiles *pParameterProfiles)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return m_pParameterProfiles.Copy(pParameterProfiles);
}

BOOL CTPEPService::GetParameterProfiles(CTPEPDataProfiles *pParameterProfiles) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return pParameterProfiles->Copy(&m_pParameterProfiles);
}

BOOL CTPEPService::SetServerConnections(CONST CStringArray &szClients, CONST CTPEPConnections &pConnections)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	m_szClients.Copy(szClients);
	m_pServerConnections.Copy(&pConnections, TRUE);
	return TRUE;
}

INT CTPEPService::GetServerConnections(CStringArray &szClients, CTPEPConnections &pConnections) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	szClients.Copy(m_szClients);
	pConnections.Copy(&m_pServerConnections, TRUE);
	return((INT)szClients.GetSize());
}

BOOL CTPEPService::HasServerConnections() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((m_pServerConnections.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CTPEPService::AttachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_cServiceThread.AttachServerConnection(pszClient, pConnection, pDisplayWnd);
}

BOOL CTPEPService::DetachServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_cServiceThread.DetachServerConnection(pszClient, pConnection, pDisplayWnd);
}

BOOL CTPEPService::UpdateServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection, BOOL bDelete)
{
	INT  nClient;
	INT  nClients;
	UINT  nCount;
	CTimeKey  tConnect;
	CTimeKey  tLastUse;
	CComputerToken  cComputerToken;
	CTPEPConnection  *pServerConnection;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	for (nClient = 0, nClients = (INT)m_szClients.GetSize(), pConnection->GetStatistics(tConnect, tLastUse, nCount); nClient < nClients; nClient++)
	{
		if (!m_szClients.GetAt(nClient).CompareNoCase(pszClient) && m_pServerConnections.GetAt(nClient)->Compare(pConnection))
		{
			if (tConnect.GetTime() < tLastUse.GetTime() || nCount > 0 || bDelete)
			{
				m_pServerConnections.GetAt(nClient)->Copy(pConnection, TRUE);
				break;
			}
		}
	}
	if (!bDelete)
	{
		if (nClient == nClients)
		{
			if (cComputerToken == pszClient || GetNetworkBrowseService()->IsComputerOnNetwork(pszClient))
			{
				if ((pServerConnection = new CTPEPConnection))
				{
					pServerConnection->Copy(pConnection, TRUE);
					m_pServerConnections.Add(pServerConnection);
					m_szClients.Add(pszClient);
					return TRUE;
				}
			}
			return FALSE;
		}
		return TRUE;
	}
	if (nClient < nClients)
	{
		delete m_pServerConnections.GetAt(nClient);
		m_pServerConnections.RemoveAt(nClient);
		m_szClients.RemoveAt(nClient);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPService::RemoveServerConnection(LPCTSTR pszClient, CTPEPConnection *pConnection)
{
	return m_cServiceThread.RemoveServerConnection(pszClient, pConnection);
}

BOOL CTPEPService::SetClientConnections(CONST CStringArray &szServers, CONST CTPEPConnections &pConnections)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	m_szServers.Copy(szServers);
	m_pClientConnections.Copy(&pConnections, TRUE);
	return TRUE;
}

INT CTPEPService::GetClientConnections(CStringArray &szServers, CTPEPConnections &pConnections) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	szServers.Copy(m_szServers);
	pConnections.Copy(&m_pClientConnections, TRUE);
	return((INT)szServers.GetSize());
}

BOOL CTPEPService::HasClientConnections() CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((m_pClientConnections.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CTPEPService::AddClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_cServiceThread.AddClientConnection(pszServer, pConnection, pDisplayWnd);
}

BOOL CTPEPService::AttachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_cServiceThread.AttachClientConnection(pszServer, pConnection, pDisplayWnd);
}

BOOL CTPEPService::DetachClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, CDisplayWnd *pDisplayWnd)
{
	return m_cServiceThread.DetachClientConnection(pszServer, pConnection, pDisplayWnd);
}

BOOL CTPEPService::UpdateClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection, BOOL bDelete)
{
	INT  nServer;
	INT  nServers;
	UINT  nCount;
	CTimeKey  tConnect;
	CTimeKey  tLastUse;
	CComputerToken  cComputerToken;
	CTPEPConnection  *pClientConnection;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	for (nServer = 0, nServers = (INT)m_szServers.GetSize(), pConnection->GetStatistics(tConnect, tLastUse, nCount); nServer < nServers; nServer++)
	{
		if (!m_szServers.GetAt(nServer).CompareNoCase(pszServer) && m_pClientConnections.GetAt(nServer)->Compare(pConnection))
		{
			if (tConnect.GetTime() < tLastUse.GetTime() || nCount > 0 || bDelete)
			{
				m_pClientConnections.GetAt(nServer)->Copy(pConnection, TRUE);
				break;
			}
		}
	}
	if (!bDelete)
	{
		if (nServer == nServers)
		{
			if (cComputerToken == pszServer || GetNetworkBrowseService()->IsComputerOnNetwork(pszServer))
			{
				if ((pClientConnection = new CTPEPConnection))
				{
					pClientConnection->Copy(pConnection, TRUE);
					m_pClientConnections.Add(pClientConnection);
					m_szServers.Add(pszServer);
					return TRUE;
				}
			}
			return FALSE;
		}
		return TRUE;
	}
	if (nServer < nServers)
	{
		delete m_pClientConnections.GetAt(nServer);
		m_pClientConnections.RemoveAt(nServer);
		m_szServers.RemoveAt(nServer);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPService::RemoveClientConnection(LPCTSTR pszServer, CTPEPConnection *pConnection)
{
	return m_cServiceThread.RemoveClientConnection(pszServer, pConnection);
}

BOOL CTPEPService::Update(CTMEnvironment *pTMEnvironment, HANDLE hFlag, DWORD dwContext, UINT nError)
{
	return m_cServiceThread.UpdateConnections(pTMEnvironment, hFlag, dwContext, nError);
}
BOOL CTPEPService::Update(CTMEnvironment *pTMEnvironment, DWORD dwContext, UINT nError)
{
	return m_cServiceThread.UpdateConnections(pTMEnvironment, dwContext, nError);
}

BOOL CTPEPService::SetServiceInfo(CONST CByteArray &nInfo)
{
	INT  cbUser;
	INT  cbUsers;
	CByteArray  nServiceInfo[6];
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nInfo.GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nInfo.GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes + sServiceInfo.cbStopTimes + sServiceInfo.cbProfiles[0] + sServiceInfo.cbProfiles[1] && sServiceInfo.cbUsers >= 0 && sServiceInfo.cbAccessCodes >= 0 && sServiceInfo.cbStartTimes >= 0 && sServiceInfo.cbStopTimes >= 0 && sServiceInfo.cbProfiles[0] >= 0 && sServiceInfo.cbProfiles[1] >= 0; )
		{
			nServiceInfo[0].SetSize(sServiceInfo.cbUsers);
			nServiceInfo[1].SetSize(sServiceInfo.cbAccessCodes);
			nServiceInfo[2].SetSize(sServiceInfo.cbStartTimes);
			nServiceInfo[3].SetSize(sServiceInfo.cbStopTimes);
			nServiceInfo[4].SetSize(sServiceInfo.cbProfiles[0]);
			nServiceInfo[5].SetSize(sServiceInfo.cbProfiles[1]);
			CopyMemory(nServiceInfo[0].GetData(), nInfo.GetData() + sizeof(SERVICEINFO), sServiceInfo.cbUsers);
			CopyMemory(nServiceInfo[1].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers, sServiceInfo.cbAccessCodes);
			CopyMemory(nServiceInfo[2].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes, sServiceInfo.cbStartTimes);
			CopyMemory(nServiceInfo[3].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes, sServiceInfo.cbStopTimes);
			CopyMemory(nServiceInfo[4].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes + sServiceInfo.cbStopTimes, sServiceInfo.cbProfiles[0]);
			CopyMemory(nServiceInfo[5].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes + sServiceInfo.cbStopTimes + sServiceInfo.cbProfiles[0], sServiceInfo.cbProfiles[1]);
			for (cbUsers = 0, m_szUsers.RemoveAll(); cbUsers < nServiceInfo[0].GetSize(); cbUsers += cbUser)
			{
				m_szUsers.Add((LPCTSTR)(nServiceInfo[0].GetData() + cbUsers));
				cbUser = (m_szUsers.GetAt(m_szUsers.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
			}
			for (m_nAccessCodes.SetSize(nServiceInfo[1].GetSize() / sizeof(UINT)), CopyMemory(m_nAccessCodes.GetData(), nServiceInfo[1].GetData(), m_nAccessCodes.GetSize()*sizeof(UINT)); m_tStartTimes.Unmap(nServiceInfo[2]) && m_tStopTimes.Unmap(nServiceInfo[3]) && m_pPacketProfiles.Unmap(nServiceInfo[4]) && m_pParameterProfiles.Unmap(nServiceInfo[5]); )
			{
				m_nCode = sServiceInfo.nCode;
				m_nPort = sServiceInfo.nPort;
				m_nCharset = sServiceInfo.nCharset;
				m_nBufferSize = sServiceInfo.nBufferSize;
				m_tTimeout = sServiceInfo.tTimeout;
				m_tStartTime = sServiceInfo.tStartTime;
				m_tStopTime = sServiceInfo.tStopTime;
				return TRUE;
			}
			break;
		}
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CTPEPService::GetServiceInfo(CByteArray &nInfo) CONST
{
	INT  nUser;
	INT  nUsers;
	INT  cbUser;
	INT  cbUsers;
	CByteArray  nServiceInfo[6];
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	for (nUser = 0, nUsers = (INT)m_szUsers.GetSize(), cbUsers = 0; nUser < nUsers; nUser++, cbUsers += cbUser)
	{
		nServiceInfo[0].SetSize(cbUsers + (cbUser = (m_szUsers.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nServiceInfo[0].GetData() + cbUsers, m_szUsers.GetAt(nUser), cbUser);
	}
	for (nServiceInfo[1].SetSize(m_nAccessCodes.GetSize()*sizeof(UINT)), CopyMemory(nServiceInfo[1].GetData(), m_nAccessCodes.GetData(), m_nAccessCodes.GetSize()*sizeof(UINT)); m_tStartTimes.Map(nServiceInfo[2]) >= 0 && m_tStopTimes.Map(nServiceInfo[3]) >= 0 && m_pPacketProfiles.Map(nServiceInfo[4]) && m_pParameterProfiles.Map(nServiceInfo[5]); )
	{
		nInfo.SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbUsers = (INT)nServiceInfo[0].GetSize()) + (sServiceInfo.cbAccessCodes = (INT)nServiceInfo[1].GetSize()) + (sServiceInfo.cbStartTimes = (INT)nServiceInfo[2].GetSize()) + (sServiceInfo.cbStopTimes = (INT)nServiceInfo[3].GetSize()) + (sServiceInfo.cbProfiles[0] = (INT)nServiceInfo[4].GetSize()) + (sServiceInfo.cbProfiles[1] = (INT)nServiceInfo[5].GetSize()))));
		sServiceInfo.nCode = m_nCode;
		sServiceInfo.nPort = m_nPort;
		sServiceInfo.nCharset = m_nCharset;
		sServiceInfo.nBufferSize = m_nBufferSize;
		sServiceInfo.tTimeout = m_tTimeout.GetTotalSeconds();
		sServiceInfo.tStartTime = m_tStartTime.GetTotalSeconds();
		sServiceInfo.tStopTime = m_tStopTime.GetTotalSeconds();
		CopyMemory(nInfo.GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO), nServiceInfo[0].GetData(), nServiceInfo[0].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize(), nServiceInfo[1].GetData(), nServiceInfo[1].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize() + nServiceInfo[1].GetSize(), nServiceInfo[2].GetData(), nServiceInfo[2].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize() + nServiceInfo[1].GetSize() + nServiceInfo[2].GetSize(), nServiceInfo[3].GetData(), nServiceInfo[3].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize() + nServiceInfo[1].GetSize() + nServiceInfo[2].GetSize() + nServiceInfo[3].GetSize(), nServiceInfo[4].GetData(), nServiceInfo[4].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize() + nServiceInfo[1].GetSize() + nServiceInfo[2].GetSize() + nServiceInfo[3].GetSize() + nServiceInfo[4].GetSize(), nServiceInfo[5].GetData(), nServiceInfo[5].GetSize());
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPService::UpdateServiceInfo(BOOL bSave)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((bSave  &&  SaveServiceInfo()) || (!bSave  &&  LoadServiceInfo()));
}

BOOL CTPEPService::IsAvailable() CONST
{
	CTPEPServiceEngine  *pTPEPServiceSupport;

	return(((pTPEPServiceSupport = GetTPEPServiceSupport()) && pTPEPServiceSupport->GetTPEPSupport()) ? TRUE : FALSE);
}

BOOL CTPEPService::SaveServiceInfo()
{
	CUIntArray  nCodes;
	CStringArray  szUsers;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	SERVICEINFO  sServiceInfo;
	CByteArray  nServiceInfo[7];
	CProfile  cProfile;

	if (GetServiceInfo(nServiceInfo[0]) && nServiceInfo[0].GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nServiceInfo[0].GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes + sServiceInfo.cbStopTimes + sServiceInfo.cbProfiles[0] + sServiceInfo.cbProfiles[1] && sServiceInfo.cbUsers >= 0 && sServiceInfo.cbAccessCodes >= 0 && sServiceInfo.cbStartTimes >= 0 && sServiceInfo.cbStopTimes >= 0 && sServiceInfo.cbProfiles[0] >= 0 && sServiceInfo.cbProfiles[1] >= 0; )
		{
			nServiceInfo[1].SetSize(sServiceInfo.cbUsers);
			nServiceInfo[2].SetSize(sServiceInfo.cbAccessCodes);
			nServiceInfo[3].SetSize(sServiceInfo.cbStartTimes);
			nServiceInfo[4].SetSize(sServiceInfo.cbStopTimes);
			nServiceInfo[5].SetSize(sServiceInfo.cbProfiles[0]);
			nServiceInfo[6].SetSize(sServiceInfo.cbProfiles[1]);
			CopyMemory(nServiceInfo[1].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO), sServiceInfo.cbUsers);
			CopyMemory(nServiceInfo[2].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers, sServiceInfo.cbAccessCodes);
			CopyMemory(nServiceInfo[3].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes, sServiceInfo.cbStartTimes);
			CopyMemory(nServiceInfo[4].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes, sServiceInfo.cbStopTimes);
			CopyMemory(nServiceInfo[5].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes + sServiceInfo.cbStopTimes, sServiceInfo.cbProfiles[0]);
			CopyMemory(nServiceInfo[6].GetData(), nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbUsers + sServiceInfo.cbAccessCodes + sServiceInfo.cbStartTimes + sServiceInfo.cbStopTimes + sServiceInfo.cbProfiles[0], sServiceInfo.cbProfiles[1]);
			for (; nServiceInfo[1].GetSize() > 0; nServiceInfo[1].RemoveAt(0, (szUsers.GetAt(szUsers.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
			{
				szUsers.Add((LPCTSTR)nServiceInfo[1].GetData());
				continue;
			}
			if (nServiceInfo[2].GetSize() > 0)
			{
				nCodes.SetSize(nCodes.GetSize() + 1);
				CopyMemory(nCodes.GetData() + nCodes.GetUpperBound(), nServiceInfo[2].GetData(), sizeof(UINT));
				nServiceInfo[2].RemoveAt(0, sizeof(UINT));
			}
			return((tStartTimes.Unmap(nServiceInfo[3]) && tStopTimes.Unmap(nServiceInfo[4])) ? (cProfile.SetTPEPServiceSettingsInfo(sServiceInfo.nPort, sServiceInfo.nBufferSize, sServiceInfo.nCharset, sServiceInfo.tTimeout) && cProfile.SetTPEPServiceAvailabilityInfo(sServiceInfo.nCode, sServiceInfo.tStartTime, sServiceInfo.tStopTime) && cProfile.SetTPEPServiceSecurityInfo(szUsers, nCodes, tStartTimes, tStopTimes) && cProfile.SetTPEPServiceProfileInfo(nServiceInfo[5], nServiceInfo[6])) : FALSE);
		}
	}
	return FALSE;
}

BOOL CTPEPService::LoadServiceInfo()
{
	INT  nUser;
	INT  nUsers;
	INT  cbUser;
	INT  cbUsers;
	UINT  nPort;
	UINT  nCode;
	UINT  nCharset;
	UINT  nBufferSize;
	CTimeSpan  tTimeout;
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	CUIntArray  nCodes;
	CStringArray  szUsers;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	SERVICEINFO  sServiceInfo;
	CByteArray  nServiceInfo[7];
	CProfile  cProfile;

	if (cProfile.GetTPEPServiceSettingsInfo(nPort, nBufferSize, nCharset, tTimeout) && cProfile.GetTPEPServiceAvailabilityInfo(nCode, tStartTime, tStopTime) && cProfile.GetTPEPServiceSecurityInfo(szUsers, nCodes, tStartTimes, tStopTimes) && cProfile.GetTPEPServiceProfileInfo(nServiceInfo[5], nServiceInfo[6]))
	{
		for (nUser = 0, nUsers = (INT)szUsers.GetSize(), cbUsers = 0; nUser < nUsers; nUser++, cbUsers += cbUser)
		{
			nServiceInfo[1].SetSize(cbUsers + (cbUser = (szUsers.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR)));
			CopyMemory(nServiceInfo[1].GetData() + cbUsers, szUsers.GetAt(nUser), cbUser);
		}
		for (nServiceInfo[2].SetSize(nCodes.GetSize()*sizeof(UINT)), CopyMemory(nServiceInfo[2].GetData(), nCodes.GetData(), nCodes.GetSize()*sizeof(UINT)); tStartTimes.Map(nServiceInfo[3]) >= 0 && tStopTimes.Map(nServiceInfo[4]) >= 0; )
		{
			nServiceInfo[0].SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbUsers = (INT)nServiceInfo[1].GetSize()) + (sServiceInfo.cbAccessCodes = (INT)nServiceInfo[2].GetSize()) + (sServiceInfo.cbStartTimes = (INT)nServiceInfo[3].GetSize()) + (sServiceInfo.cbStopTimes = (INT)nServiceInfo[4].GetSize()) + (sServiceInfo.cbProfiles[0] = (INT)nServiceInfo[5].GetSize()) + (sServiceInfo.cbProfiles[1] = (INT)nServiceInfo[6].GetSize()))));
			sServiceInfo.nCode = nCode;
			sServiceInfo.nPort = nPort;
			sServiceInfo.nCharset = nCharset;
			sServiceInfo.nBufferSize = nBufferSize;
			sServiceInfo.tTimeout = tTimeout.GetTotalSeconds();
			sServiceInfo.tStartTime = tStartTime.GetTotalSeconds();
			sServiceInfo.tStopTime = tStopTime.GetTotalSeconds();
			CopyMemory(nServiceInfo[0].GetData(), &sServiceInfo, sizeof(SERVICEINFO));
			CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO), nServiceInfo[1].GetData(), nServiceInfo[1].GetSize());
			CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + nServiceInfo[1].GetSize(), nServiceInfo[2].GetData(), nServiceInfo[2].GetSize());
			CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + nServiceInfo[1].GetSize() + nServiceInfo[2].GetSize(), nServiceInfo[3].GetData(), nServiceInfo[3].GetSize());
			CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + nServiceInfo[1].GetSize() + nServiceInfo[2].GetSize() + nServiceInfo[3].GetSize(), nServiceInfo[4].GetData(), nServiceInfo[4].GetSize());
			CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + nServiceInfo[1].GetSize() + nServiceInfo[2].GetSize() + nServiceInfo[3].GetSize() + nServiceInfo[4].GetSize(), nServiceInfo[5].GetData(), nServiceInfo[5].GetSize());
			CopyMemory(nServiceInfo[0].GetData() + sizeof(SERVICEINFO) + nServiceInfo[1].GetSize() + nServiceInfo[2].GetSize() + nServiceInfo[3].GetSize() + nServiceInfo[4].GetSize() + nServiceInfo[5].GetSize(), nServiceInfo[6].GetData(), nServiceInfo[6].GetSize());
			return SetServiceInfo(nServiceInfo[0]);
		}
	}
	return FALSE;
}

BOOL CTPEPService::Lock()
{
	return m_cServiceThread.m_pCriticalSection->Lock();
}

BOOL CTPEPService::Unlock()
{
	return m_cServiceThread.m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTMProviderDevice

UINT CTMProviderDevice::m_nDeviceStatus;
BOOL CTMProviderDevice::m_bDeviceStatus;
CPtrArray  CTMProviderDevice::m_pDataStreamDevices;
CPtrArray  CTMProviderDevice::m_nDataStreamTimerIDs;
CUIntArray  CTMProviderDevice::m_nDataStreamEventIDs;

CTMProviderDevice::CTMProviderDevice() : CIODevice()
{
	m_nDeviceStatus = 0;
	m_bDeviceStatus = FALSE;
	m_szIODeviceStatus = STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_NOTREADY);
	m_nIODeviceStatus = IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_ONLINE;
	m_nScheduleOptions = TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS;
	m_nBackupOptions = TELEMETRYPROVIDERDEVICE_BACKUP_USEANYDEVICE;
	m_tScheduleStartTime = 0;
	m_tScheduleStopTime = 0;
	m_tDailyStartTime = 0;
	m_tDailyStopTime = 0;
	m_tPeriodicStartTime = 0;
	m_tPeriodicInterval[0] = 0;
	m_tPeriodicInterval[1] = 0;
	m_nBackupRetry[0] = 0;
	m_nBackupRetry[1] = 0;
	m_tBackupTimeout = 0;
}
CTMProviderDevice::CTMProviderDevice(CTMProviderDevice *pDevice) : CIODevice()
{
	Copy(pDevice);
}

BOOL CTMProviderDevice::Initialize(UINT nFlags, CONST CTimeSpan &tDataDrop, CONST CTimeSpan &tDataDelay, IODEVICESTATUSPROCEDURE pStatusProcedure, IODEVICEMESSAGEPROCEDURE pMessageProcedure)
{
	if (CIODevice::Initialize(nFlags, tDataDrop, tDataDelay, UpdateDeviceStatus, (IODEVICEDATASTATUSPROCEDURE)NULL, ShowDeviceMessage))
	{
		MonitorDeviceDataStream(IODEVICE_DATASTREAM_DROP | IODEVICE_DATASTREAM_RECONNECTED, tDataDrop, TrackDeviceDataStream, this);
		MonitorDeviceDataStream(IODEVICE_DATASTREAM_DELAYED | IODEVICE_DATASTREAM_BACKINTIME, tDataDelay, TrackDeviceDataStream, this);
		return TRUE;
	}
	return FALSE;
}

VOID CTMProviderDevice::SetScheduleOptions(UINT nOptions)
{
	m_nScheduleOptions = nOptions;
}

UINT CTMProviderDevice::GetScheduleOptions() CONST
{
	return m_nScheduleOptions;
}

VOID CTMProviderDevice::SetScheduleDaily(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	m_tDailyStartTime = (tStartTime < tStopTime) ? tStartTime : 0;
	m_tDailyStopTime = (tStartTime < tStopTime) ? tStopTime : 0;
}

BOOL CTMProviderDevice::GetScheduleDaily(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nScheduleOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_DAILY)
	{
		tStartTime = m_tDailyStartTime;
		tStopTime = m_tDailyStopTime;
		return TRUE;
	}
	return FALSE;
}

VOID CTMProviderDevice::SetScheduleInterval(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	m_tScheduleStartTime = (tStartTime < tStopTime) ? tStartTime : 0;
	m_tScheduleStopTime = (tStartTime < tStopTime) ? tStopTime : 0;
}

BOOL CTMProviderDevice::GetScheduleInterval(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nScheduleOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_INTERVAL)
	{
		tStartTime = m_tScheduleStartTime;
		tStopTime = m_tScheduleStopTime;
		return TRUE;
	}
	return FALSE;
}

VOID CTMProviderDevice::SetSchedulePeriodic(CONST CTimeKey &tStartTime, CONST CTimeSpan &tPeriod, CONST CTimeSpan &tInterval)
{
	m_tPeriodicStartTime = tStartTime;
	m_tPeriodicInterval[0] = tPeriod;
	m_tPeriodicInterval[1] = tInterval;
}

BOOL CTMProviderDevice::GetSchedulePeriodic(CTimeKey &tStartTime, CTimeSpan &tPeriod, CTimeSpan &tInterval) CONST
{
	if (m_nScheduleOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_PERIODIC)
	{
		tStartTime = m_tPeriodicStartTime;
		tPeriod = m_tPeriodicInterval[0];
		tInterval = m_tPeriodicInterval[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTMProviderDevice::SetBackupDevice(LPCTSTR pszDevice)
{
	m_szBackupDevice = pszDevice;
}

BOOL CTMProviderDevice::GetBackupDevice(CString &szDevice) CONST
{
	if (m_nBackupOptions & TELEMETRYPROVIDERDEVICE_BACKUP_USEDEVICE)
	{
		szDevice = m_szBackupDevice;
		return TRUE;
	}
	return FALSE;
}

VOID CTMProviderDevice::SetBackupOptions(UINT nOptions)
{
	m_nBackupOptions = nOptions;
}

UINT CTMProviderDevice::GetBackupOptions() CONST
{
	return m_nBackupOptions;
}

VOID CTMProviderDevice::SetBackupRetries(UINT nRetries)
{
	m_nBackupRetry[0] = nRetries;
	m_nBackupRetry[1] = 0;
}

BOOL CTMProviderDevice::GetBackupRetries(UINT &nRetries) CONST
{
	if (m_nBackupOptions & TELEMETRYPROVIDERDEVICE_BACKUP_RETRIES)
	{
		nRetries = m_nBackupRetry[0];
		return TRUE;
	}
	return FALSE;
}

VOID CTMProviderDevice::SetBackupRetryCount(UINT nCount)
{
	m_nBackupRetry[1] = nCount;
}

BOOL CTMProviderDevice::GetBackupRetryCount(UINT &nCount) CONST
{
	if (m_nBackupOptions & TELEMETRYPROVIDERDEVICE_BACKUP_RETRIES)
	{
		nCount = m_nBackupRetry[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTMProviderDevice::SetBackupTimeout(CONST CTimeSpan &tTimeout)
{
	m_tBackupTimeout = tTimeout;
}

BOOL CTMProviderDevice::GetBackupTimeout(CTimeSpan &tTimeout) CONST
{
	return(((tTimeout = m_tBackupTimeout) >= 0) ? TRUE : FALSE);
}

CString CTMProviderDevice::GetToolTipText() CONST
{
	CString  szDetails;
	CTMProviderDevice  cDevice;

	for (cDevice.Copy(this); cDevice.Open(); )
	{
		szDetails = cDevice.GetDetails();
		cDevice.Close();
		return szDetails;
	}
	return EMPTYSTRING;
}

BOOL CTMProviderDevice::IsStandBy(CTimeSpan &tPeriod) CONST
{
	UINT  nOptions;
	CTimeKey  tTime;
	CTimeKey  tRange[2];
	CTimeKey  tStartTime;
	CTimeSpan  tDaily[2];
	CTimeSpan  tInterval[2];

	if (((nOptions = GetScheduleOptions()) & TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED) != TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED)
	{
		if (nOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS)
		{
			tPeriod = SECONDSPERDAY;
			return TRUE;
		}
		if (nOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_DAILY)
		{
			if (GetScheduleDaily(tDaily[0], tDaily[1]) && tTime.GetTime() % SECONDSPERDAY >= tDaily[0].GetTotalSeconds() && tTime.GetTime() % SECONDSPERDAY <= tDaily[1].GetTotalSeconds())
			{
				tPeriod = tDaily[1].GetTotalSeconds() - tTime.GetTime() % SECONDSPERDAY;
				return TRUE;
			}
		}
		if (nOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_INTERVAL)
		{
			if (GetScheduleInterval(tRange[0], tRange[1]) && tTime >= tRange[0] && tTime <= tRange[1])
			{
				tPeriod = min(tRange[1].GetTime() - tTime.GetTime(), SECONDSPERDAY);
				return TRUE;
			}
		}
		if (nOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_PERIODIC)
		{
			if (GetSchedulePeriodic(tStartTime, tInterval[0], tInterval[1]) && tTime >= tStartTime && (tTime.GetTime() - tStartTime.GetTime()) % (tInterval[0].GetTotalSeconds() + tInterval[1].GetTotalSeconds()) < tInterval[0].GetTotalSeconds())
			{
				tPeriod = min(tInterval[0].GetTotalSeconds() - (tTime.GetTime() - tStartTime.GetTime()) % (tInterval[0].GetTotalSeconds() + tInterval[1].GetTotalSeconds()), SECONDSPERDAY);
				return TRUE;
			}
		}
	}
	tPeriod = 0;
	return FALSE;
}
BOOL CTMProviderDevice::IsStandBy() CONST
{
	CTimeSpan  tPeriod;

	return IsStandBy(tPeriod);
}

BOOL CTMProviderDevice::Copy(CONST CTMProviderDevice *pDevice)
{
	m_nScheduleOptions = pDevice->m_nScheduleOptions;
	m_tScheduleStartTime = pDevice->m_tScheduleStartTime;
	m_tScheduleStopTime = pDevice->m_tScheduleStopTime;
	m_tDailyStartTime = pDevice->m_tDailyStartTime;
	m_tDailyStopTime = pDevice->m_tDailyStopTime;
	m_tPeriodicStartTime = pDevice->m_tPeriodicStartTime;
	m_tPeriodicInterval[0] = pDevice->m_tPeriodicInterval[0];
	m_tPeriodicInterval[1] = pDevice->m_tPeriodicInterval[1];
	m_szBackupDevice = pDevice->m_szBackupDevice;
	m_nBackupOptions = pDevice->m_nBackupOptions;
	m_nBackupRetry[0] = pDevice->m_nBackupRetry[0];
	m_nBackupRetry[1] = pDevice->m_nBackupRetry[1];
	m_tBackupTimeout = pDevice->m_tBackupTimeout;
	return CIODevice::Copy(pDevice);
}

BOOL CTMProviderDevice::Compare(CONST CTMProviderDevice *pDevice) CONST
{
	return((pDevice->m_nScheduleOptions == m_nScheduleOptions && (!(m_nScheduleOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_DAILY) || (pDevice->m_tDailyStartTime == m_tDailyStartTime  &&  pDevice->m_tDailyStopTime == m_tDailyStopTime)) && (!(m_nScheduleOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_INTERVAL) || (pDevice->m_tScheduleStartTime == m_tScheduleStartTime  &&  pDevice->m_tScheduleStopTime == m_tScheduleStopTime)) && (!(m_nScheduleOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_PERIODIC) || (pDevice->m_tPeriodicStartTime == m_tPeriodicStartTime  &&  pDevice->m_tPeriodicInterval[0] == m_tPeriodicInterval[0] && pDevice->m_tPeriodicInterval[1] == m_tPeriodicInterval[1])) && pDevice->m_nBackupOptions == m_nBackupOptions && (!(m_nBackupOptions & TELEMETRYPROVIDERDEVICE_BACKUP_USEDEVICE) || pDevice->m_szBackupDevice == m_szBackupDevice) && (!(m_nBackupOptions & TELEMETRYPROVIDERDEVICE_BACKUP_RETRIES) || pDevice->m_nBackupRetry[0] == m_nBackupRetry[0]) && pDevice->m_tBackupTimeout == m_tBackupTimeout) ? CIODevice::Compare(pDevice) : FALSE);
}

BOOL CTMProviderDevice::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDeviceData;

	sData.cbBackupDevice = (m_szBackupDevice.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDevice = (CIODevice::Map(nDeviceData)) ? (INT)nDeviceData.GetSize() : -1;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + max(sData.cbDevice, 0) + sData.cbBackupDevice)), sData.nScheduleOptions = m_nScheduleOptions, sData.tScheduleStartTime = m_tScheduleStartTime.GetTime(), sData.tScheduleStopTime = m_tScheduleStopTime.GetTime(), sData.tDailyStartTime = m_tDailyStartTime.GetTotalSeconds(), sData.tDailyStopTime = m_tDailyStopTime.GetTotalSeconds(), sData.tPeriodicStartTime = m_tPeriodicStartTime.GetTime(), sData.tPeriodicInterval[0] = m_tPeriodicInterval[0].GetTotalSeconds(), sData.tPeriodicInterval[1] = m_tPeriodicInterval[1].GetTotalSeconds(), sData.nBackupOptions = m_nBackupOptions, sData.nBackupRetry[0] = m_nBackupRetry[0], sData.nBackupRetry[1] = m_nBackupRetry[1], sData.tBackupTimeout = m_tBackupTimeout.GetTotalSeconds(); nInfo.GetSize() == sData.cbSize && sData.cbDevice >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szBackupDevice, sData.cbBackupDevice);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbBackupDevice), nDeviceData.GetData(), sData.cbDevice);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMProviderDevice::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDeviceData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDevice + sData.cbBackupDevice && sData.cbDevice > 0 && sData.cbBackupDevice > 0; )
	{
		for (nDeviceData.SetSize(sData.cbDevice), CopyMemory(m_szBackupDevice.GetBufferSetLength(STRINGCHARS(sData.cbBackupDevice)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbBackupDevice)), CopyMemory(nDeviceData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbBackupDevice), sData.cbDevice), m_nScheduleOptions = sData.nScheduleOptions, m_tScheduleStartTime = sData.tScheduleStartTime, m_tScheduleStopTime = sData.tScheduleStopTime, m_tDailyStartTime = sData.tDailyStartTime, m_tDailyStopTime = sData.tDailyStopTime, m_tPeriodicStartTime = sData.tPeriodicStartTime, m_tPeriodicInterval[0] = sData.tPeriodicInterval[0], m_tPeriodicInterval[1] = sData.tPeriodicInterval[1], m_nBackupOptions = sData.nBackupOptions, m_nBackupRetry[0] = sData.nBackupRetry[0], m_nBackupRetry[1] = sData.nBackupRetry[1], m_tBackupTimeout = sData.tBackupTimeout, m_szBackupDevice.ReleaseBuffer(); CIODevice::Unmap(nDeviceData); ) return TRUE;
		break;
	}
	return FALSE;
}

VOID CALLBACK CTMProviderDevice::TrackDeviceDataStream(UINT nFlags, TIMEKEY tInterval, LPVOID pData)
{
	INT  nIndex;
	INT  nCount;
	CString  szMessage;
	CTimeKey  tAlertTime;
	CTimeSpan  tTimeout;
	CStringArray  szAlerts;
	CSystemAlerts  pAlerts;
	CSystemAlertInfo  *pAlertInfo[2];
	CComputerToken  cComputerToken;
	CTMProviderDevice  *pDevice = (CTMProviderDevice *)pData;

	if (GetSystemAlerts(pAlerts))
	{
		if (nFlags & IODEVICE_DATASTREAM_DROP)
		{
			if ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_VERYSHORT_FAILURE)))) && (!pAlertInfo[0] -> GetAudition().IsEmpty() || pAlertInfo[0] -> GetNotifications(szAlerts) > 0))
			{
				m_nDataStreamTimerIDs.Add((LPVOID)SetTimer((HWND)NULL, (UINT_PTR)NULL, (DWORD)(1000 * max(SECONDSPERMINUTE / 12 - pDevice->m_tOperationsDataDrop[0].GetTotalSeconds(), 0)), TrackDeviceDataDrops));
				m_nDataStreamEventIDs.Add(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_VERYSHORT_FAILURE);
				m_pDataStreamDevices.Add(pDevice);
			}
			else if ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_SHORT_FAILURE)))) && (!pAlertInfo[0] -> GetAudition().IsEmpty() || pAlertInfo[0] -> GetNotifications(szAlerts) > 0))
			{
				m_nDataStreamTimerIDs.Add((LPVOID)SetTimer((HWND)NULL, (UINT_PTR)NULL, (DWORD)(1000 * max(SECONDSPERMINUTE / 2 - pDevice->m_tOperationsDataDrop[0].GetTotalSeconds(), 0)), TrackDeviceDataDrops));
				m_nDataStreamEventIDs.Add(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_SHORT_FAILURE);
				m_pDataStreamDevices.Add(pDevice);
			}
			else if ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_LONG_FAILURE)))) && (!pAlertInfo[0] -> GetAudition().IsEmpty() || pAlertInfo[0] -> GetNotifications(szAlerts) > 0))
			{
				m_nDataStreamTimerIDs.Add((LPVOID)SetTimer((HWND)NULL, (UINT_PTR)NULL, (DWORD)(1000 * max(SECONDSPERMINUTE - pDevice->m_tOperationsDataDrop[0].GetTotalSeconds(), 0)), TrackDeviceDataDrops));
				m_nDataStreamEventIDs.Add(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_LONG_FAILURE);
				m_pDataStreamDevices.Add(pDevice);
			}
			else if ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_VERYLONG_FAILURE)))) && (!pAlertInfo[0] -> GetAudition().IsEmpty() || pAlertInfo[0] -> GetNotifications(szAlerts) > 0))
			{
				m_nDataStreamTimerIDs.Add((LPVOID)SetTimer((HWND)NULL, (UINT_PTR)NULL, (DWORD)(1000 * max(5 * SECONDSPERMINUTE - pDevice->m_tOperationsDataDrop[0].GetTotalSeconds(), 0)), TrackDeviceDataDrops));
				m_nDataStreamEventIDs.Add(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_VERYLONG_FAILURE);
				m_pDataStreamDevices.Add(pDevice);
			}
			for (pDevice->SetStatus(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_READY)), pDevice->SetStatusIndication((pDevice->GetStatusIndication() | IODEVICE_STATUS_WARNING) & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_ERROR)); pDevice->GetBackupTimeout(tTimeout) && tTimeout > 0; )
			{
				m_nDataStreamTimerIDs.Add((LPVOID)SetTimer((HWND)NULL, (UINT_PTR)NULL, (DWORD)(1000 * tTimeout.GetTotalSeconds()), TrackDeviceDataDrops));
				m_nDataStreamEventIDs.Add(IDS_TELEMETRYPROVIDERDEVICE_BACKUPMESSAGE_INACTIVITY);
				m_pDataStreamDevices.Add(pDevice);
				break;
			}
			GetTMService()->SetActiveTMProviderDevice(pDevice);
			return;
		}
		if (nFlags & IODEVICE_DATASTREAM_RECONNECTED)
		{
			if ((pAlertInfo[1] = ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_SUCCESS))))) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
			{
				for (szMessage.Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_SUCCESS), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)cComputerToken.GetComputerName()); pAlertInfo[0]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_SUCCESS); )
				{
					szMessage = pAlertInfo[0]->GetMessage();
					break;
				}
				pAlertInfo[1]->Copy(pAlertInfo[0]);
				pAlertInfo[1]->SetCategory(EVENT_CATEGORY_SYSTEM);
				pAlertInfo[1]->SetType(EVENT_TYPE_INFORMATIONAL);
				pAlertInfo[1]->SetMessage(szMessage);
				ReportEvent(pAlertInfo[1]);
				delete pAlertInfo[1];
			}
			for (nIndex = 0, nCount = (INT)m_pDataStreamDevices.GetSize(); nIndex < nCount; nIndex++)
			{
				if (pDevice == (CTMProviderDevice *)m_pDataStreamDevices.GetAt(nIndex))
				{
					KillTimer((HWND)NULL, (UINT_PTR)m_nDataStreamTimerIDs.GetAt(nIndex));
					m_nDataStreamTimerIDs.RemoveAt(nIndex);
					m_nDataStreamEventIDs.RemoveAt(nIndex);
					m_pDataStreamDevices.RemoveAt(nIndex);
					nCount--;
					nIndex--;
				}
			}
			return;
		}
		if (nFlags & IODEVICE_DATASTREAM_DELAYED)
		{
			if ((pAlertInfo[1] = ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DELAY_FAILURE))))) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
			{
				for (szMessage.Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DELAY_FAILURE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT))); pAlertInfo[0]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DELAY_FAILURE); )
				{
					szMessage = pAlertInfo[0]->GetMessage();
					break;
				}
				pAlertInfo[1]->Copy(pAlertInfo[0]);
				pAlertInfo[1]->SetCategory(EVENT_CATEGORY_SYSTEM);
				pAlertInfo[1]->SetType(EVENT_TYPE_WARNING);
				pAlertInfo[1]->SetMessage(szMessage);
				ReportEvent(pAlertInfo[1]);
				delete pAlertInfo[1];
			}
			return;
		}
		if (nFlags & IODEVICE_DATASTREAM_BACKINTIME)
		{
			if ((pAlertInfo[1] = ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DELAY_SUCCESS))))) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
			{
				for (szMessage.Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DELAY_SUCCESS), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)cComputerToken.GetComputerName()); pAlertInfo[0]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DELAY_SUCCESS); )
				{
					szMessage = pAlertInfo[0]->GetMessage();
					break;
				}
				pAlertInfo[1]->Copy(pAlertInfo[0]);
				pAlertInfo[1]->SetCategory(EVENT_CATEGORY_SYSTEM);
				pAlertInfo[1]->SetType(EVENT_TYPE_INFORMATIONAL);
				pAlertInfo[1]->SetMessage(szMessage);
				ReportEvent(pAlertInfo[1]);
				delete pAlertInfo[1];
			}
			return;
		}
	}
}

VOID CALLBACK CTMProviderDevice::TrackDeviceDataDrops(HWND hwnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime)
{
	INT  nIndex;
	INT  nCount;
	UINT  nMessageID;
	CString  szMessage;
	CTimeKey  tAlertTime;
	CTimeSpan  tTimeout;
	CSystemAlerts  pAlerts;
	CSystemAlertInfo  *pAlertInfo[2];
	CTMProviderDevice  *pDevice[2];
	CTMProviderDevices  pDevices;
	CComputerToken  cComputerToken;
	CStringTools  cStringTools;

	for (nIndex = 0, nCount = (INT)m_nDataStreamTimerIDs.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_nDataStreamTimerIDs.GetAt(nIndex) == (LPVOID)nEventID) break;
		continue;
	}
	if (nIndex < nCount)
	{
		if (!_tcscmp(STRING(m_nDataStreamEventIDs.GetAt(nIndex)), STRING(IDS_TELEMETRYPROVIDERDEVICE_BACKUPMESSAGE_INACTIVITY)))
		{
			if ((pDevice[1] = ((pDevice[0] = (GetTMService()->GetTMProviderDevices(pDevices) > 0) ? (CTMProviderDevice *)m_pDataStreamDevices.GetAt(nIndex) : (CTMProviderDevice *)NULL)) ? pDevices.GetAt(pDevices.Find(pDevice[0]->GetDeviceBrand(), pDevice[0]->GetDeviceName())) : (CTMProviderDevice *)NULL) && pDevice[1]->GetBackupTimeout(tTimeout) && tTimeout > 0)
			{
				for (szMessage.Format(STRING(m_nDataStreamEventIDs.GetAt(nIndex)), (LPCTSTR)pDevice[1]->GetDeviceName(), (LPCTSTR)cStringTools.ConvertLongUIntToStructuredString(tTimeout.GetTotalSeconds())); pDevice[1]->GetBackupOptions() & TELEMETRYPROVIDERDEVICE_BACKUP_AUDITFAILURES; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
					break;
				}
				pDevice[1]->SetStatus(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_NOTREADY));
				pDevice[1]->SetStatusIndication((pDevice[1]->GetStatusIndication() | IODEVICE_STATUS_WARNING | IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_CLOSED) & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_ERROR | IODEVICE_STATUS_CONNECTED));
				GetTMService()->SetActiveTMProviderDevice(pDevice[1]);
			}
		}
		else
		{
			if (GetSystemAlerts(pAlerts))
			{
				if ((pAlertInfo[1] = ((pAlertInfo[0] = pAlerts.GetAt(pAlerts.Find(STRING(m_nDataStreamEventIDs.GetAt(nIndex)))))) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
				{
					for (szMessage.Format((m_nDataStreamEventIDs.GetAt(nIndex) == IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_VERYSHORT_FAILURE) ? STRING((nMessageID = IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_VERYSHORT_FAILURE)) : ((m_nDataStreamEventIDs.GetAt(nIndex) == IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_SHORT_FAILURE) ? STRING((nMessageID = IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_SHORT_FAILURE)) : ((m_nDataStreamEventIDs.GetAt(nIndex) == IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_LONG_FAILURE) ? STRING((nMessageID = IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_LONG_FAILURE)) : ((m_nDataStreamEventIDs.GetAt(nIndex) == IDS_SYSTEMALERTS_NAME_TELEMETRY_DROP_VERYLONG_FAILURE) ? STRING((nMessageID = IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_VERYLONG_FAILURE)) : STRING((nMessageID = IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_FAILURE))))), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT))); pAlertInfo[0]->GetMessage() != STRING(nMessageID) && nMessageID != IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DROP_FAILURE; )
					{
						szMessage = pAlertInfo[0]->GetMessage();
						break;
					}
					pAlertInfo[1]->Copy(pAlertInfo[0]);
					pAlertInfo[1]->SetCategory(EVENT_CATEGORY_SYSTEM);
					pAlertInfo[1]->SetType(EVENT_TYPE_WARNING);
					pAlertInfo[1]->SetMessage(szMessage);
					ReportEvent(pAlertInfo[1]);
					delete pAlertInfo[1];
				}
			}
		}
		m_nDataStreamTimerIDs.RemoveAt(nIndex);
		m_nDataStreamEventIDs.RemoveAt(nIndex);
		m_pDataStreamDevices.RemoveAt(nIndex);
	}
	KillTimer((HWND)NULL, nEventID);
}

VOID CALLBACK CTMProviderDevice::UpdateDeviceStatus(LPCTSTR pszStatus, UINT nStatus)
{
	HWND  hWnd;
	BOOL  bDeviceStatus;
	CTMProviderDevice  cDevice;

	for (bDeviceStatus = FALSE; GetTMService()->GetActiveTMProviderDevice(&cDevice); )
	{
		if (cDevice.GetStatus() != pszStatus || cDevice.GetStatusIndication() != nStatus)
		{
			cDevice.SetStatus(pszStatus);
			cDevice.SetStatusIndication(nStatus);
			GetTMService()->SetActiveTMProviderDevice(&cDevice);
			bDeviceStatus = TRUE;
		}
		break;
	}
	if ((hWnd = FindWindow(STRING(IDS_SCREENSAVER_WINDOWCLASS_NAME), (LPCTSTR)NULL)))
	{
		if (!m_bDeviceStatus || bDeviceStatus) SendNotifyMessage(hWnd, WM_USER, MAKEWPARAM(MAKEWORD(TRUE, (nStatus & IODEVICE_STATUS_GOOD) ? TRUE : FALSE), 0), (LPARAM)NULL);
		m_bDeviceStatus = TRUE;
		return;
	}
	m_bDeviceStatus = FALSE;
}

VOID CALLBACK CTMProviderDevice::ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType)
{
	ReportEvent(EVENT_CATEGORY_SYSTEM | nMessageType, pszMessage, FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTMProviderDevices

CTMProviderDevices::CTMProviderDevices() : CIODevices()
{
	return;
}

CTMProviderDevices::~CTMProviderDevices()
{
	RemoveAll();
}

INT CTMProviderDevices::EnumDevices(UINT nFlags)
{
	INT  nDevice;
	INT  nDevices;
	CFileFindEx  cFileFind;
	CTMProviderDevice  *pDevice;
	TCHAR  szFileName[MAX_PATH];

	if (GetModuleFileName((HMODULE)NULL, szFileName, sizeof(szFileName) / sizeof(TCHAR)) > 0)
	{
		for (m_szDevicePathNames[0].RemoveAll(), m_szDevicePathNames[1].RemoveAll(); cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
		{
			EnumDevices(nFlags, cFileFind.GetRoot());
			cFileFind.Close();
			break;
		}
		for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
		{
			if ((pDevice = GetAt(nDevice)))
			{
				if (pDevice->Open())
				{
					if (pDevice->GetCapabilities() & IODEVICE_SERVICE_TM)
					{
						pDevice->Close();
						continue;
					}
					pDevice->Close();
				}
			}
			RemoveAt(nDevice);
			delete pDevice;
			nDevices--;
			nDevice--;
		}
	}
	return((INT)GetSize());
}

INT CTMProviderDevices::EnumStandByDevices(CTMProviderDevices &pDevices) CONST
{
	INT  nDevice;
	INT  nDevices;
	CTMProviderDevice  *pDevice;

	for (nDevice = 0, nDevices = (pDevices.Copy(this)) ? (INT)pDevices.GetSize() : 0; nDevice < nDevices; nDevice++)
	{
		if ((pDevice = pDevices.GetAt(nDevice)) && pDevice->IsStandBy()) continue;
		pDevices.RemoveAt(nDevice);
		delete pDevice;
		nDevices--;
		nDevice--;
	}
	return((INT)pDevices.GetSize());
}

INT CTMProviderDevices::EnumBackupDevices(CONST CTMProviderDevice *pDevice, CTMProviderDevices &pDevices) CONST
{
	INT  nIndex;
	INT  nCount;
	CString  szDevice;

	if (pDevice->GetBackupOptions() & (TELEMETRYPROVIDERDEVICE_BACKUP_CONTINOUSLY | TELEMETRYPROVIDERDEVICE_BACKUP_RETRIES))
	{
		pDevices.RemoveAll();
		return 0;
	}
	if ((nIndex = (EnumStandByDevices(pDevices) > 0) ? pDevices.Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName()) : -1) >= 0)
	{
		delete pDevices.GetAt(nIndex);
		pDevices.RemoveAt(nIndex);
	}
	for (nIndex = 0, nCount = ((pDevice->GetBackupOptions() & TELEMETRYPROVIDERDEVICE_BACKUP_USEDEVICE) && pDevice->GetBackupDevice(szDevice) && pDevices.Find(pDevice->GetDeviceBrand(), szDevice) >= 0) ? (INT)pDevices.GetSize() : 0; nIndex < nCount; nIndex++)
	{
		if (pDevices.GetAt(nIndex)->GetDeviceBrand() != pDevice->GetDeviceBrand() || pDevices.GetAt(nIndex)->GetDeviceName() != szDevice)
		{
			delete pDevices.GetAt(nIndex);
			pDevices.RemoveAt(nIndex);
			nCount--;
			nIndex--;
		}
	}
	return((INT)pDevices.GetSize());
}

BOOL CTMProviderDevices::HasAvailableDevices(BOOL bSupported) CONST
{
	INT  nDevice;
	INT  nDevices;
	CTMProviderDevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice)) && !pDevice->GetDeviceName().IsEmpty()) break;
		continue;
	}
	return(((!bSupported  &&  nDevice < nDevices) || (bSupported  &&  nDevices > 0)) ? TRUE : FALSE);
}

BOOL CTMProviderDevices::SetActiveDevice(CONST CTMProviderDevice *pDevice)
{
	INT  nIndex;
	CTMProviderDevice  cDevice;

	if ((nIndex = Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())) >= 0)
	{
		m_szDevice[0] = ConstructFullName(pDevice);
		return(cDevice.Copy(pDevice) && GetAt(nIndex)->Copy(&cDevice));
	}
	return FALSE;
}

BOOL CTMProviderDevices::GetActiveDevice(CTMProviderDevice *pDevice) CONST
{
	INT  nDevice;
	INT  nDevices;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if (m_szDevice[0] == ConstructFullName(GetAt(nDevice)))
		{
			pDevice->Copy(GetAt(nDevice));
			break;
		}
	}
	return((nDevice < nDevices) ? TRUE : FALSE);
}

BOOL CTMProviderDevices::SetDefaultDevice(CONST CTMProviderDevice *pDevice)
{
	INT  nIndex;
	CTMProviderDevice  cDevice;

	if ((nIndex = Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())) >= 0)
	{
		m_szDevice[1] = ConstructFullName(pDevice);
		return(cDevice.Copy(pDevice) && GetAt(nIndex)->Copy(&cDevice));
	}
	return FALSE;
}

BOOL CTMProviderDevices::GetDefaultDevice(CTMProviderDevice *pDevice) CONST
{
	INT  nDevice;
	INT  nDevices;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if (m_szDevice[1] == ConstructFullName(GetAt(nDevice)))
		{
			pDevice->Copy(GetAt(nDevice));
			break;
		}
	}
	return((nDevice < nDevices) ? TRUE : FALSE);
}

CString CTMProviderDevices::GetActiveDeviceBrand() CONST
{
	CTMProviderDevice  cDevice;

	return((GetActiveDevice(&cDevice)) ? cDevice.GetDeviceBrand() : EMPTYSTRING);
}

CString CTMProviderDevices::GetActiveDeviceName() CONST
{
	CTMProviderDevice  cDevice;

	return((GetActiveDevice(&cDevice)) ? cDevice.GetDeviceName() : EMPTYSTRING);
}

CString CTMProviderDevices::GetDefaultDeviceBrand() CONST
{
	CTMProviderDevice  cDevice;

	return((GetDefaultDevice(&cDevice)) ? cDevice.GetDeviceBrand() : EMPTYSTRING);
}

CString CTMProviderDevices::GetDefaultDeviceName() CONST
{
	CTMProviderDevice  cDevice;

	return((GetDefaultDevice(&cDevice)) ? cDevice.GetDeviceName() : EMPTYSTRING);
}

CTMProviderDevice *CTMProviderDevices::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMProviderDevice *)CPtrArray::GetAt(nIndex) : (CTMProviderDevice *)NULL);
}

CTMProviderDevice *CTMProviderDevices::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTMProviderDevice *)CPtrArray::GetAt(nIndex) : (CTMProviderDevice *)NULL);
}

VOID CTMProviderDevices::RemoveAll()
{
	INT  nDevice;
	INT  nDevices;
	CTMProviderDevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)GetSize(), m_szDevicePathNames[0].RemoveAll(), m_szDevicePathNames[1].RemoveAll(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice))) delete pDevice;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTMProviderDevices::Copy(CONST CTMProviderDevices *pDevices, BOOL bAll)
{
	INT  nDevice;
	INT  nDevices;
	CTMProviderDevice  *pDevice;

	if (bAll)
	{
		m_szDevice[0] = pDevices->m_szDevice[0];
		m_szDevice[1] = pDevices->m_szDevice[1];
		m_szDevicePathNames[0].Copy(pDevices->m_szDevicePathNames[0]);
		m_szDevicePathNames[1].Copy(pDevices->m_szDevicePathNames[1]);
	}
	for (nDevice = 0, nDevices = (INT)pDevices->GetSize(), RemoveAll(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = new CTMProviderDevice))
		{
			pDevice->Copy(pDevices->GetAt(nDevice));
			InsertAt(nDevice, pDevice, 1);
			continue;
		}
		break;
	}
	return((nDevice == nDevices) ? TRUE : FALSE);
}

BOOL CTMProviderDevices::Compare(CONST CTMProviderDevices *pDevices, BOOL bAll) CONST
{
	INT  nDevice;
	INT  nDevices;
	INT  nModule[2];
	INT  nModules[2];
	CTMProviderDevice  *pDevice;

	for (nDevice = 0, nDevices = ((!bAll || (pDevices->m_szDevice[0] == m_szDevice[0] && pDevices->m_szDevice[1] == m_szDevice[1])) && pDevices->GetSize() == GetSize()) ? (INT)GetSize() : -1; nDevice < nDevices; nDevice++)
	{
		if ((pDevice = pDevices->GetAt(nDevice)) && Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName()) >= 0 && pDevice->Compare(GetAt(Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())))) continue;
		break;
	}
	for (nModule[0] = 0, nModules[0] = (bAll) ? ((pDevices->m_szDevicePathNames[0].GetSize() == m_szDevicePathNames[0].GetSize()) ? (INT)m_szDevicePathNames[0].GetSize() : -1) : 0; nModule[0] < nModules[0]; nModule[0]++)
	{
		if (pDevices->m_szDevicePathNames[0].GetAt(nModule[0]).CompareNoCase(m_szDevicePathNames[0].GetAt(nModule[0]))) break;
		continue;
	}
	for (nModule[1] = 0, nModules[1] = (bAll) ? ((pDevices->m_szDevicePathNames[1].GetSize() == m_szDevicePathNames[1].GetSize()) ? (INT)m_szDevicePathNames[1].GetSize() : -1) : 0; nModule[1] < nModules[1]; nModule[1]++)
	{
		if (pDevices->m_szDevicePathNames[1].GetAt(nModule[1]).CompareNoCase(m_szDevicePathNames[1].GetAt(nModule[1]))) break;
		continue;
	}
	return((nDevice == nDevices  &&  nModule[0] == nModules[0] && nModule[1] == nModules[1]) ? TRUE : FALSE);
}

BOOL CTMProviderDevices::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nDevice;
	INT  nDevices;
	CByteArray  nDevicesData[2];
	CTMProviderDevice  *pDevice;

	sData.cbDevice[0] = (m_szDevice[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbDevice[1] = (m_szDevice[1].GetLength() + 1)*sizeof(TCHAR);
	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice)) && pDevice->Map(nDevicesData[1]) && nDevicesData[0].Append(nDevicesData[1]) >= 0) continue;
		break;
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbDevice[0] + sData.cbDevice[1] + (sData.cbDevicesData = (INT)(nDevicesData[0].GetSize()*sizeof(BYTE))))); nInfo.GetSize() == sData.cbSize && nDevice == nDevices; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szDevice[0], sData.cbDevice[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice[0]), (LPCTSTR)m_szDevice[1], sData.cbDevice[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice[1]), nDevicesData[0].GetData(), sData.cbDevicesData);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMProviderDevices::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbDevice;
	INT  cbDevices;
	CByteArray  nDevicesData[2];
	CTMProviderDevice  *pDevice;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDevice[0] + sData.cbDevice[1] + sData.cbDevicesData && sData.cbDevice[0] > 0 && sData.cbDevice[1] > 0 && sData.cbDevicesData >= 0; )
	{
		for (nDevicesData[0].SetSize(sData.cbDevicesData), CopyMemory(m_szDevice[0].GetBufferSetLength(STRINGCHARS(sData.cbDevice[0])), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbDevice[0])), CopyMemory(m_szDevice[1].GetBufferSetLength(STRINGCHARS(sData.cbDevice[1])), nInfo.GetData() + (cbData = cbData + sData.cbDevice[0]), STRINGBYTES(sData.cbDevice[1])), CopyMemory(nDevicesData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDevice[1]), sData.cbDevicesData), m_szDevice[0].ReleaseBuffer(), m_szDevice[1].ReleaseBuffer(), RemoveAll(), cbDevices = 0; cbDevices < (INT)nDevicesData[0].GetSize(); cbDevices += cbDevice)
		{
			for (CopyMemory(&cbDevice, nDevicesData[0].GetData() + cbDevices, sizeof(cbDevice)), nDevicesData[1].SetSize(max(min(cbDevice, nDevicesData[0].GetSize() - cbDevices), 0)); nDevicesData[1].GetSize() >= 0; )
			{
				CopyMemory(nDevicesData[1].GetData(), nDevicesData[0].GetData() + cbDevices, nDevicesData[1].GetSize());
				break;
			}
			if ((pDevice = new CTMProviderDevice))
			{
				if (pDevice->Unmap(nDevicesData[1]) && Add(pDevice) >= 0) continue;
				delete pDevice;
			}
			break;
		}
		return((cbDevices == sData.cbDevicesData) ? TRUE : FALSE);
	}
	return FALSE;
}

VOID CTMProviderDevices::EnumDevices(UINT nFlags, LPCTSTR pszDirectory)
{
	BOOL  bFound;
	CFileFind  cFileFind;

	if (cFileFind.FindFile(CString(pszDirectory) + STRING(IDS_FILENAME_ALL)))
	{
		for (bFound = cFileFind.FindNextFile(); TRUE; bFound = cFileFind.FindNextFile())
		{
			if (!cFileFind.IsDots())
			{
				if (!cFileFind.IsDirectory())
				{
					if (!cFileFind.GetFileName().Right(cFileFind.GetFileName().GetLength() - cFileFind.GetFileTitle().GetLength()).CompareNoCase(CString(STRING(IDS_FILENAME_DLL)).Mid(lstrlen(STRING(IDS_FILENAME_DLL)) / 2 - 1))) EnumDevices(nFlags, cFileFind.GetRoot(), cFileFind.GetFileName());
					if (bFound) continue;
					break;
				}
				EnumDevices(nFlags, cFileFind.GetFilePath());
			}
			if (!bFound) break;
		}
		cFileFind.Close();
	}
}
VOID CTMProviderDevices::EnumDevices(UINT nFlags, LPCTSTR pszDirectory, LPCTSTR pszFileName)
{
	INT  nIndex;
	INT  nCount;
	INT  nDevice[2];
	INT  nDevices[2];
	LPTSTR  *pIODevices;
	CString  szFileName;
	CString  szIODevices;
	HINSTANCE  hIODevices;
	CTMProviderDevice  *pDevice[2];
	INT(*pEnumDevices)(LPTSTR *ppszProducts, INT nCount);

	for (szFileName = pszDirectory, szFileName += pszFileName; ((pDevice[0] = GetAt((INT)GetUpperBound())) && pDevice[0]->GetDeviceModule().CompareNoCase(szFileName) != 0) || !GetSize(); )
	{
		for (nIndex = 0, nCount = (INT)m_szDevicePathNames[1].GetSize(); nIndex < nCount; nIndex++)
		{
			if (!m_szDevicePathNames[1].GetAt(nIndex).CompareNoCase(szFileName)) break;
			continue;
		}
		if (nIndex == nCount)
		{
			if ((hIODevices = AfxLoadLibrary(szFileName)))
			{
#ifndef UNICODE
				szIODevices = STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS);
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS), -1, (LPSTR)szIODevices.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS))), lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szIODevices.ReleaseBuffer();
#endif
				if ((pEnumDevices = (INT(__cdecl *)(LPTSTR *ppszProducts, INT nCount)) GetProcAddress(hIODevices, (LPCSTR)(LPCTSTR)szIODevices)))
				{
					if ((nDevices[0] = (*pEnumDevices)((LPTSTR *)NULL, 0)) > 0)
					{
						if ((pIODevices = (LPTSTR *)GlobalAlloc(GPTR, nDevices[0] * sizeof(LPTSTR))))
						{
							for (nDevice[0] = 0, nDevices[0] = (*pEnumDevices)(pIODevices, nDevices[0]); nDevice[0] < nDevices[0]; nDevice[0]++)
							{
								for (nDevice[1] = 0, nDevices[1] = (INT)GetSize(); nDevice[1] < nDevices[1]; nDevice[1] = nDevice[1] + 1)
								{
									if ((pDevice[0] = GetAt(nDevice[1])) && !pDevice[0]->GetDeviceBrand().CompareNoCase(pIODevices[nDevice[0]]))
									{
										pDevice[0]->SetDeviceModule(szFileName);
										continue;
									}
								}
								for (nDevice[1] = 0; nDevice[1] < nDevices[1]; nDevice[1]++)
								{
									if ((pDevice[0] = GetAt(nDevice[1])) && !pDevice[0]->GetDeviceBrand().CompareNoCase(pIODevices[nDevice[0]])) break;
									continue;
								}
								for (; nDevice[1] == nDevices[1]; )
								{
									if ((pDevice[1] = new CTMProviderDevice))
									{
										if (pDevice[1]->Open(szFileName, pIODevices[nDevice[0]]))
										{
											if (pDevice[1]->GetCapabilities() & IODEVICE_SERVICE_TM)
											{
												pDevice[1]->SetDeviceName(EMPTYSTRING);
												pDevice[1]->SetDeviceModule(szFileName);
												if (pDevice[1]->Initialize(nFlags) && Add(pDevice[1]) >= 0)
												{
													m_szDevicePathNames[0].Add(szFileName);
													pDevice[1]->Close();
													break;
												}
											}
											pDevice[1]->Close();
										}
										delete pDevice[1];
									}
									break;
								}
								for (nIndex = 0, nCount = (nDevice[1] < nDevices[1]) ? (INT)m_szDevicePathNames[0].GetSize() : -1; nIndex < nCount; nIndex++)
								{
									if (!m_szDevicePathNames[0].GetAt(nIndex).CompareNoCase(szFileName)) break;
									continue;
								}
								if (nIndex == nCount)
								{
									m_szDevicePathNames[0].Add(szFileName);
									continue;
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
				m_szDevicePathNames[1].Add(szFileName);
				AfxFreeLibrary(hIODevices);
			}
		}
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceDevice

CStringArray  CPFLPServiceDevice::m_szClients[2];
CTimeTagArray  CPFLPServiceDevice::m_tClients[2];

BOOL CPFLPServiceDevice::Initialize(UINT nFlags, CONST CTimeSpan &tDataDrop, CONST CTimeSpan &tDataDelay, IODEVICESTATUSPROCEDURE pStatusProcedure, IODEVICEMESSAGEPROCEDURE pMessageProcedure)
{
	if (CIODevice::Initialize((nFlags | IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TM | IODEVICE_DATASERVICE_SOURCEPACKETS | IODEVICE_PROTOCOL_PFLP) & ~(IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TC | IODEVICE_DATASERVICE_RAW | IODEVICE_DATASERVICE_TRANSFERFRAMES), 0, 0, (IODEVICESTATUSPROCEDURE)NULL, (IODEVICEDATASTATUSPROCEDURE)NULL, ShowDeviceMessage))
	{
		MonitorDeviceLogins(IODEVICE_LOGIN_SUCCESS | IODEVICE_LOGIN_FAILURE | IODEVICE_LOGOUT_SUCCESS, ShowDeviceLogins, this);
		return TRUE;
	}
	return FALSE;
}

VOID CALLBACK CPFLPServiceDevice::ShowDeviceLogins(UINT nFlags, LPCTSTR pszClient, TIMETAG tConnectTime, LPVOID pData)
{
	INT  nPos;
	INT  nClient;
	INT  nClients;
	CString  szClient;
	CString  szAddress;
	CString  szMessage;
	CTimeTag  tDisconnectTime;

	for (szClient = ((nPos = (szClient = pszClient).Find(EOL)) >= 0) ? szClient.Left(nPos) : szClient, szAddress = ((nPos = (szAddress = pszClient).Find(EOL)) >= 0) ? szAddress.Mid(nPos + 1) : EMPTYSTRING; nFlags & IODEVICE_LOGIN_SUCCESS; )
	{
		for (szMessage.Format(STRING(IDS_PFLP_SECURITY_LOGIN), (!szClient.IsEmpty()) ? (LPCTSTR)szClient : STRING(IDS_PFLP_SECURITY_UNKNOWNLOGIN), (!szAddress.IsEmpty()) ? (LPCTSTR)szAddress : STRING(IDS_PFLP_SECURITY_UNKNOWNLOGIN)); nFlags & IODEVICE_LOGINOUT_AUDIT; )
		{
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			break;
		}
		for (nClient = 0, nClients = (INT)m_szClients[0].GetSize(); nClient < nClients; nClient++)
		{
			if (!m_szClients[0].GetAt(nClient).CompareNoCase(pszClient) && m_tClients[0].GetAt(nClient) == tConnectTime) break;
			continue;
		}
		if (nClient == nClients)
		{
			m_szClients[0].Add(pszClient);
			m_tClients[0].Add(tConnectTime);
		}
		for (nClient = 0, nClients = (INT)m_szClients[1].GetSize(); nClient < nClients; nClient++)
		{
			if (!m_szClients[1].GetAt(nClient).CompareNoCase(pszClient))
			{
				m_szClients[1].RemoveAt(nClient);
				m_tClients[1].RemoveAt(nClient);
			}
		}
		return;
	}
	if (nFlags & IODEVICE_LOGIN_FAILURE)
	{
		for (szMessage.Format(STRING(IDS_PFLP_SECURITY_ILLEGALLOGIN), (!szClient.IsEmpty()) ? (LPCTSTR)szClient : STRING(IDS_PFLP_SECURITY_UNKNOWNLOGIN), (!szAddress.IsEmpty()) ? (LPCTSTR)szAddress : STRING(IDS_PFLP_SECURITY_UNKNOWNLOGIN)); nFlags & IODEVICE_LOGINOUT_AUDIT; )
		{
			for (nClient = 0, nClients = (INT)m_szClients[1].GetSize(); nClient < nClients; nClient++)
			{
				if (!m_szClients[1].GetAt(nClient).CompareNoCase(pszClient)) break;
				continue;
			}
			if (nClient == nClients)
			{
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				m_szClients[1].Add(pszClient);
				m_tClients[1].Add(tConnectTime);
			}
			break;
		}
		for (nClient = 0, nClients = (INT)m_szClients[0].GetSize(); nClient < nClients; nClient++)
		{
			if (!m_szClients[0].GetAt(nClient).CompareNoCase(pszClient) && m_tClients[0].GetAt(nClient) == tConnectTime)
			{
				m_szClients[0].RemoveAt(nClient);
				m_tClients[0].RemoveAt(nClient);
				break;
			}
		}
		return;
	}
	if (nFlags & IODEVICE_LOGOUT_SUCCESS)
	{
		for (nClient = 0, nClients = (INT)m_szClients[0].GetSize(); nClient < nClients; nClient++)
		{
			if (!m_szClients[0].GetAt(nClient).CompareNoCase(pszClient) && m_tClients[0].GetAt(nClient) == tConnectTime) break;
			continue;
		}
		if (nClient < nClients)
		{
			for (szMessage.Format((tDisconnectTime.GetTime() - m_tClients[0].GetAt(nClient).GetTime() >= 2 * (TIMETAG)1000000 * (TIMETAG)SECONDSPERMINUTE) ? STRING(IDS_PFLP_SECURITY_LOGOUT) : STRING(IDS_PFLP_SECURITY_LOGOUTQUICKLY), (!szClient.IsEmpty()) ? (LPCTSTR)szClient : STRING(IDS_PFLP_SECURITY_UNKNOWNLOGIN), (!szAddress.IsEmpty()) ? (LPCTSTR)szAddress : STRING(IDS_PFLP_SECURITY_UNKNOWNLOGIN), (INT)max((tDisconnectTime.GetTime() - m_tClients[0].GetAt(nClient).GetTime()) / ((TIMETAG)1000000 * (TIMETAG)SECONDSPERMINUTE), 1)); nFlags & IODEVICE_LOGINOUT_AUDIT; )
			{
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				break;
			}
			m_szClients[0].RemoveAt(nClient);
			m_tClients[0].RemoveAt(nClient);
		}
		for (nClient = 0, nClients = (INT)m_szClients[1].GetSize(); nClient < nClients; nClient++)
		{
			if (!m_szClients[1].GetAt(nClient).CompareNoCase(pszClient))
			{
				m_szClients[1].RemoveAt(nClient);
				m_tClients[1].RemoveAt(nClient);
			}
		}
		return;
	}
}

VOID CALLBACK CPFLPServiceDevice::ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType)
{
	ReportEvent(EVENT_CATEGORY_SYSTEM | nMessageType, pszMessage, FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceDevices

CPFLPServiceDevices::CPFLPServiceDevices() : CTMProviderDevices()
{
	return;
}

CPFLPServiceDevices::~CPFLPServiceDevices()
{
	RemoveAll();
}

INT CPFLPServiceDevices::EnumDevices(UINT nFlags)
{
	return CTMProviderDevices::EnumDevices(nFlags);
}

INT CPFLPServiceDevices::Add(CPFLPServiceDevice *pDevice)
{
	return CTMProviderDevices::Add(pDevice);
}

CPFLPServiceDevice *CPFLPServiceDevices::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPServiceDevice *)CPtrArray::GetAt(nIndex) : (CPFLPServiceDevice *)NULL);
}

CPFLPServiceDevice *CPFLPServiceDevices::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPFLPServiceDevice *)CPtrArray::GetAt(nIndex) : (CPFLPServiceDevice *)NULL);
}

VOID CPFLPServiceDevices::RemoveAll()
{
	INT  nDevice;
	INT  nDevices;
	CPFLPServiceDevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice))) delete pDevice;
		RemoveAt(nDevice);
		nDevices--;
		nDevice--;
	}
	CTMProviderDevices::RemoveAll();
}

BOOL CPFLPServiceDevices::Copy(CONST CPFLPServiceDevices *pDevices)
{
	INT  nDevice;
	INT  nDevices;
	CPFLPServiceDevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)pDevices->GetSize(), RemoveAll(), m_szDevice[0] = pDevices->m_szDevice[0], m_szDevice[1] = pDevices->m_szDevice[1], m_szDevicePathNames[0].Copy(pDevices->m_szDevicePathNames[0]), m_szDevicePathNames[1].Copy(pDevices->m_szDevicePathNames[1]); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = new CPFLPServiceDevice))
		{
			pDevice->Copy(pDevices->GetAt(nDevice));
			InsertAt(nDevice, pDevice, 1);
			continue;
		}
		break;
	}
	return((nDevice == nDevices) ? TRUE : FALSE);
}

BOOL CPFLPServiceDevices::Compare(CONST CPFLPServiceDevices *pDevices) CONST
{
	INT  nDevice;
	INT  nDevices;
	INT  nModule[2];
	INT  nModules[2];
	CPFLPServiceDevice  *pDevice;

	for (nDevice = 0, nDevices = (pDevices->m_szDevice[0] == m_szDevice[0] && pDevices->m_szDevice[1] == m_szDevice[1] && pDevices->GetSize() == GetSize()) ? (INT)GetSize() : -1; nDevice < nDevices; nDevice++)
	{
		if ((pDevice = pDevices->GetAt(nDevice)) && Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName()) >= 0 && pDevice->Compare(GetAt(Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())))) continue;
		break;
	}
	for (nModule[0] = 0, nModules[0] = (pDevices->m_szDevicePathNames[0].GetSize() == m_szDevicePathNames[0].GetSize()) ? (INT)m_szDevicePathNames[0].GetSize() : -1; nModule[0] < nModules[0]; nModule[0]++)
	{
		if (pDevices->m_szDevicePathNames[0].GetAt(nModule[0]).CompareNoCase(m_szDevicePathNames[0].GetAt(nModule[0]))) break;
		continue;
	}
	for (nModule[1] = 0, nModules[1] = (pDevices->m_szDevicePathNames[1].GetSize() == m_szDevicePathNames[1].GetSize()) ? (INT)m_szDevicePathNames[1].GetSize() : -1; nModule[1] < nModules[1]; nModule[1]++)
	{
		if (pDevices->m_szDevicePathNames[1].GetAt(nModule[1]).CompareNoCase(m_szDevicePathNames[1].GetAt(nModule[1]))) break;
		continue;
	}
	return((nDevice == nDevices  &&  nModule[0] == nModules[0] && nModule[1] == nModules[1]) ? TRUE : FALSE);
}

BOOL CPFLPServiceDevices::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nDevice;
	INT  nDevices;
	CByteArray  nDevicesData[2];
	CPFLPServiceDevice  *pDevice;

	sData.cbDevice[0] = (m_szDevice[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbDevice[1] = (m_szDevice[1].GetLength() + 1)*sizeof(TCHAR);
	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice)) && pDevice->Map(nDevicesData[1]) && nDevicesData[0].Append(nDevicesData[1]) >= 0) continue;
		break;
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbDevice[0] + sData.cbDevice[1] + (sData.cbDevicesData = (INT)(nDevicesData[0].GetSize()*sizeof(BYTE))))); nInfo.GetSize() == sData.cbSize && nDevice == nDevices; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szDevice[0], sData.cbDevice[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice[0]), (LPCTSTR)m_szDevice[1], sData.cbDevice[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice[1]), nDevicesData[0].GetData(), sData.cbDevicesData);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPServiceDevices::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbDevice;
	INT  cbDevices;
	CByteArray  nDevicesData[2];
	CPFLPServiceDevice  *pDevice;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDevice[0] + sData.cbDevice[1] + sData.cbDevicesData && sData.cbDevice[0] > 0 && sData.cbDevice[1] > 0 && sData.cbDevicesData >= 0; )
	{
		for (nDevicesData[0].SetSize(sData.cbDevicesData), CopyMemory(m_szDevice[0].GetBufferSetLength(STRINGCHARS(sData.cbDevice[0])), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbDevice[0])), CopyMemory(m_szDevice[1].GetBufferSetLength(STRINGCHARS(sData.cbDevice[1])), nInfo.GetData() + (cbData = cbData + sData.cbDevice[0]), STRINGBYTES(sData.cbDevice[1])), CopyMemory(nDevicesData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDevice[1]), sData.cbDevicesData), m_szDevice[0].ReleaseBuffer(), m_szDevice[1].ReleaseBuffer(), RemoveAll(), cbDevices = 0; cbDevices < (INT)nDevicesData[0].GetSize(); cbDevices += cbDevice)
		{
			for (CopyMemory(&cbDevice, nDevicesData[0].GetData() + cbDevices, sizeof(cbDevice)), nDevicesData[1].SetSize(max(min(cbDevice, nDevicesData[0].GetSize() - cbDevices), 0)); nDevicesData[1].GetSize() >= 0; )
			{
				CopyMemory(nDevicesData[1].GetData(), nDevicesData[0].GetData() + cbDevices, nDevicesData[1].GetSize());
				break;
			}
			if ((pDevice = new CPFLPServiceDevice))
			{
				if (pDevice->Unmap(nDevicesData[1]) && Add(pDevice) >= 0) continue;
				delete pDevice;
			}
			break;
		}
		return((cbDevices == sData.cbDevicesData) ? TRUE : FALSE);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceThread

IMPLEMENT_DYNCREATE(CPFLPServiceThread, CThread)

CPFLPServiceThread::CPFLPServiceThread() : CThread()
{
	return;
}

BOOL CPFLPServiceThread::Start(CONST CPFLPServiceDevices &pDevices)
{
	return((pDevices.GetActiveDevice(&m_cDevice[0]) || (pDevices.GetSize() > 0 && m_cDevice[0].Copy(pDevices.GetAt(0)))) ? CreateThread() : FALSE);
}

BOOL CPFLPServiceThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CPFLPServiceThread::Update()
{
	return m_bUpdate.SetEvent();
}
BOOL CPFLPServiceThread::Update(CONST CPFLPServiceDevice *pDevice)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_cDevice[1].Copy(pDevice)) ? m_bUpdate.SetEvent() : FALSE);
}
BOOL CPFLPServiceThread::Update(CONST CTMUnit *pTMUnit)
{
	CTMUnit  cTMUnit;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	cTMUnit.Copy(pTMUnit);
	return((cTMUnit.IsValid()) ? (m_cDevice[0].Send(cTMUnit) >= 0) : FALSE);
}

INT CPFLPServiceThread::EnumClients(CStringArray &szClients) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_cDevice[0].EnumConnections(szClients);
}
INT CPFLPServiceThread::EnumClients(CStringArray &szClients, CTimeTagArray &tConnectTimes, CTimeTagArray &tLastUseTimes, CDWordArray &cbInBytes, CDWordArray &cbOutBytes) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_cDevice[0].EnumConnections(szClients, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes);
}

BOOL CPFLPServiceThread::AbortClient(LPCTSTR pszClient, CONST CTimeTag &tConnectTime)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_cDevice[0].AbortConnection(pszClient, tConnectTime);
}

BOOL CPFLPServiceThread::InitInstance()
{
	return AfxSocketInit();
}

int CPFLPServiceThread::Run()
{
	UINT  nCode;
	BOOL  bDevice[2];
	DWORD  dwResult;
	DWORD  dwTimeout;
	CString  szMessage[2];
	CTimeKey  tUpdate[2];
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;

	for (dwTimeout = 0; (dwResult = Wait(m_bUpdate, FALSE, dwTimeout)) == WAIT_OBJECT_0 + 1 || dwResult == WAIT_TIMEOUT; )
	{
		for (Lock(), bDevice[0] = TRUE; m_cDevice[1].GetDeviceBrand().IsEmpty() || m_cDevice[1].GetDeviceName().IsEmpty(); )
		{
			if (!m_cDevice[0].Open() || !m_cDevice[0].Initialize())
			{
				ReportEvent(SYSTEM_INFORMATIONAL_PFLP_NOT_AVAILABLE);
				bDevice[0] = FALSE;
			}
			m_cDevice[0].Close();
			break;
		}
		for (; dwResult == WAIT_OBJECT_0 + 1; )
		{
			if (m_cDevice[0].IsOpen())
			{
				if (m_cDevice[1].Open() && m_cDevice[1].Initialize())
				{
					for (bDevice[0] = m_cDevice[0].Update(&m_cDevice[1], (bDevice[1] = FALSE)); !bDevice[0]; )
					{
						ReportEvent(SYSTEM_INFORMATIONAL_PFLP_NOT_AVAILABLE);
						break;
					}
					if (!bDevice[0] || bDevice[1]) m_cDevice[0].Close();
				}
				break;
			}
			if (m_cDevice[0].Open())
			{
				if (m_cDevice[1].Open() && m_cDevice[1].Initialize())
				{
					for (bDevice[0] = m_cDevice[0].Update(&m_cDevice[1], (bDevice[1] = FALSE)); !bDevice[0]; )
					{
						ReportEvent(SYSTEM_INFORMATIONAL_PFLP_NOT_AVAILABLE);
						break;
					}
				}
				m_cDevice[1].Close();
				m_cDevice[0].Close();
			}
			break;
		}
		for (tUpdate[0] = tUpdate[1] = CTime::GetCurrentTime().GetTime(), tUpdate[1] += tUpdate[1].GetBias(), dwTimeout = INFINITE; GetPFLPService()->GetAvailabilityInfo(nCode, tStartTime, tStopTime); )
		{
			if (((nCode & PFLP_SERVICE_UNLIMITEDAVAILABILITY) || ((nCode & PFLP_SERVICE_DAILYAVAILABILITY) && tUpdate[0].GetTime() % SECONDSPERDAY >= tStartTime.GetTotalSeconds() && tUpdate[0].GetTime() % SECONDSPERDAY <= tStopTime.GetTotalSeconds())) && ((nCode & PFLP_SERVICE_WORKINGDAYSAVAILABILITY) != PFLP_SERVICE_WORKINGDAYSAVAILABILITY || tUpdate[1].GetDayOfWeek() == Monday || tUpdate[1].GetDayOfWeek() == Tuesday || tUpdate[1].GetDayOfWeek() == Wednesday || tUpdate[1].GetDayOfWeek() == Thursday || tUpdate[1].GetDayOfWeek() == Friday))
			{
				for (szMessage[1] = STRING(IDS_PFLP_SCHEDULE_ACTIVATED); nCode & PFLP_SERVICE_DAILYAVAILABILITY; )
				{
					dwTimeout = (DWORD)(1000 * (tStopTime.GetTotalSeconds() - tUpdate[0].GetTime() % SECONDSPERDAY));
					break;
				}
				for (dwTimeout = ((nCode & PFLP_SERVICE_WORKINGDAYSAVAILABILITY) && dwTimeout > (DWORD)(1000 * (SECONDSPERDAY - tUpdate[0].GetTime() % SECONDSPERDAY))) ? (DWORD)(1000 * (SECONDSPERDAY - tUpdate[0].GetTime() % SECONDSPERDAY)) : dwTimeout; !m_cDevice[0].IsOpen() && (!m_cDevice[0].Open() || !m_cDevice[0].Start()); )
				{
					ReportEvent((bDevice[0]) ? SYSTEM_INFORMATIONAL_PFLP_NOT_AVAILABLE : SYSTEM_NOERROR);
					bDevice[0] = FALSE;
					break;
				}
			}
			else
			{
				if (nCode & PFLP_SERVICE_DAILYAVAILABILITY)
				{
					szMessage[1].Format(STRING(IDS_PFLP_SCHEDULE_INACTIVEDAILY), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tUpdate[0].GetTime() / SECONDSPERDAY) + tStartTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)), (LPCTSTR)CTimeKey(SECONDSPERDAY*(tUpdate[0].GetTime() / SECONDSPERDAY) + tStopTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
					dwTimeout = (DWORD)((tUpdate[0].GetTime() % SECONDSPERDAY > tStopTime.GetTotalSeconds()) ? (1000 * (SECONDSPERDAY - tUpdate[0].GetTime() % SECONDSPERDAY + tStartTime.GetTotalSeconds())) : (1000 * (tStartTime.GetTotalSeconds() - tUpdate[0].GetTime() % SECONDSPERDAY)));
				}
				if (nCode & PFLP_SERVICE_WORKINGDAYSAVAILABILITY)
				{
					if (dwTimeout > (DWORD)(1000 * (SECONDSPERDAY - tUpdate[0].GetTime() % SECONDSPERDAY)))
					{
						dwTimeout = (DWORD)(SECONDSPERDAY - tUpdate[0].GetTime() % SECONDSPERDAY);
						szMessage[1] = STRING(IDS_PFLP_SCHEDULE_INACTIVEWEEKDAYS);
					}
				}
				m_cDevice[0].Stop();
				m_cDevice[0].Close();
			}
			if (szMessage[0] != szMessage[1] && !szMessage[1].IsEmpty())
			{
				if ((nCode & PFLP_SERVICE_AUDITAVAILABILITY) && bDevice[0]) ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage[1], FALSE);
				szMessage[0] = szMessage[1];
			}
			break;
		}
		Unlock();
	}
	m_cDevice[0].Stop();
	m_cDevice[0].Close();
	return 0;
}

BEGIN_MESSAGE_MAP(CPFLPServiceThread, CThread)
	//{{AFX_MSG_MAP(CPFLPServiceThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CPFLPService

CPFLPService::CPFLPService() : CObject()
{
	m_nCode = PFLP_SERVICE_UNLIMITEDAVAILABILITY;
	m_tStartTime = 0;
	m_tStopTime = 0;
}

BOOL CPFLPService::Start()
{
	CByteArray  nInfo;
	CPFLPServiceEngine  *pPFLPServiceSupport;
	CProfile  cProfile;

	if ((pPFLPServiceSupport = GetPFLPServiceSupport()) && pPFLPServiceSupport->IsServiceSupported())
	{
		if (cProfile.GetPFLPServiceSettingsInfo(nInfo) && SetServiceInfo(nInfo))
		{
			if (GetSystemMetrics(SM_REMOTESESSION) || !m_cServiceThread.Start(m_pDevices)) ReportEvent(SYSTEM_INFORMATIONAL_PFLP_NOT_AVAILABLE, !GetSystemMetrics(SM_REMOTESESSION));
			return TRUE;
		}
		ReportEvent(SYSTEM_WARNING_PFLP_LOAD_FAILURE);
	}
	return FALSE;
}

BOOL CPFLPService::Stop()
{
	CByteArray  nInfo;
	CPFLPServiceEngine  *pPFLPServiceSupport;
	CProfile  cProfile;

	if ((pPFLPServiceSupport = GetPFLPServiceSupport()) && pPFLPServiceSupport->IsServiceSupported())
	{
		for (m_cServiceThread.Stop(); GetServiceInfo(nInfo) && cProfile.SetPFLPServiceSettingsInfo(nInfo); ) return TRUE;
		ReportEvent(SYSTEM_WARNING_PFLP_SAVE_FAILURE);
	}
	return FALSE;
}

BOOL CPFLPService::SetDevices(CONST CPFLPServiceDevices &pDevices)
{
	CPFLPServiceDevice  cDevice;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((m_pDevices.Copy(&pDevices) && m_pDevices.GetActiveDevice(&cDevice)) ? m_cServiceThread.Update(&cDevice) : FALSE);
}

INT CPFLPService::GetDevices(CPFLPServiceDevices &pDevices) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((pDevices.Copy(&m_pDevices)) ? (INT)pDevices.GetSize() : 0);
}

BOOL CPFLPService::SetAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	if (nCode & PFLP_SERVICE_NOAVAILABILITY)
	{
		if ((m_nCode & PFLP_SERVICE_NOAVAILABILITY) != (nCode & PFLP_SERVICE_NOAVAILABILITY))
		{
			m_nCode = nCode;
			m_tStartTime = 0;
			m_tStopTime = 0;
			return m_cServiceThread.Update();
		}
		return TRUE;
	}
	if (nCode & PFLP_SERVICE_UNLIMITEDAVAILABILITY)
	{
		if ((m_nCode & (PFLP_SERVICE_UNLIMITEDAVAILABILITY | PFLP_SERVICE_WORKINGDAYSAVAILABILITY)) != (nCode & (PFLP_SERVICE_UNLIMITEDAVAILABILITY | PFLP_SERVICE_WORKINGDAYSAVAILABILITY)))
		{
			m_nCode = nCode & (PFLP_SERVICE_UNLIMITEDAVAILABILITY | PFLP_SERVICE_WORKINGDAYSAVAILABILITY | PFLP_SERVICE_AUDITAVAILABILITY);
			m_tStartTime = 0;
			m_tStopTime = 0;
			return m_cServiceThread.Update();
		}
		return TRUE;
	}
	if ((nCode & PFLP_SERVICE_DAILYAVAILABILITY) && tStartTime < tStopTime)
	{
		if ((m_nCode & (PFLP_SERVICE_DAILYAVAILABILITY | PFLP_SERVICE_WORKINGDAYSAVAILABILITY)) != (nCode & (PFLP_SERVICE_DAILYAVAILABILITY | PFLP_SERVICE_WORKINGDAYSAVAILABILITY)) || m_tStartTime != tStartTime || m_tStopTime != tStopTime)
		{
			m_nCode = nCode & (PFLP_SERVICE_DAILYAVAILABILITY | PFLP_SERVICE_WORKINGDAYSAVAILABILITY | PFLP_SERVICE_AUDITAVAILABILITY);
			m_tStartTime = tStartTime;
			m_tStopTime = tStopTime;
			return m_cServiceThread.Update();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPService::GetAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	nCode = m_nCode;
	tStartTime = m_tStartTime;
	tStopTime = m_tStopTime;
	return TRUE;
}

BOOL CPFLPService::SetConnections(CONST CStringArray &szClients, CONST CPFLPConnections &pConnections)
{
	INT  nUser;
	INT  nUsers;
	INT  nClient;
	INT  nClients;
	DWORDLONG  cbBytes;
	CTimeTag  tConnectTime;
	CTimeTag  tLastUseTime;
	CDWordArray  cbInBytes;
	CDWordArray  cbOutBytes;
	CStringArray  szUsers;
	CTimeTagArray  tConnectTimes;
	CTimeTagArray  tLastUseTimes;
	CPFLPConnection  *pConnectionInfo;

	for (nUser = 0, nUsers = m_cServiceThread.EnumClients(szUsers, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes); nUser < nUsers; nUser++)
	{
		for (nClient = 0, nClients = (INT)szClients.GetSize(); nClient < nClients; nClient++)
		{
			if ((pConnectionInfo = pConnections.GetAt(nClient)) != (CPFLPConnection *)NULL)
			{
				pConnectionInfo->GetStatistics(tConnectTime, tLastUseTime, cbBytes);
				if (!szUsers.GetAt(nUser).CompareNoCase(szClients.GetAt(nClient)) && tConnectTimes.GetAt(nUser) == tConnectTime) break;
			}
		}
		if (nClient == nClients)
		{
			ReportEvent((!m_cServiceThread.AbortClient(szUsers.GetAt(nUser), tConnectTimes.GetAt(nUser))) ? SYSTEM_WARNING_PFLP_CLOSE_FAILURE : SYSTEM_NOERROR);
			continue;
		}
	}
	return TRUE;
}

INT CPFLPService::GetConnections(CStringArray &szClients, CPFLPConnections &pConnections) CONST
{
	INT  nClient;
	INT  nClients;
	DWORDLONG  cbBytes;
	CDWordArray  cbInBytes;
	CDWordArray  cbOutBytes;
	CTimeTagArray  tConnectTimes;
	CTimeTagArray  tLastUseTimes;
	CPFLPConnection  *pConnectionInfo;

	for (nClient = 0, nClients = m_cServiceThread.EnumClients(szClients, tConnectTimes, tLastUseTimes, cbInBytes, cbOutBytes), pConnections.RemoveAll(); nClient < nClients; nClient++)
	{
		for (cbBytes = cbInBytes.GetAt(nClient), cbBytes = (cbBytes << 32) + cbOutBytes.GetAt(nClient); (pConnectionInfo = new CPFLPConnection); )
		{
			pConnectionInfo->SetType(PFLP_TYPE_TM);
			pConnectionInfo->SetLevel(PFLP_LEVEL_SOURCEPACKETS);
			pConnectionInfo->SetEndian(PFLP_ENDIAN_LITTLE);
			pConnectionInfo->SetStatistics(tConnectTimes.GetAt(nClient), tLastUseTimes.GetAt(nClient), cbBytes);
			if (pConnections.Add(pConnectionInfo) >= 0) break;
			delete pConnectionInfo;
			break;
		}
	}
	return((INT)szClients.GetSize());
}

BOOL CPFLPService::HasConnections() CONST
{
	CStringArray  szClients;

	return((m_cServiceThread.EnumClients(szClients) > 0) ? TRUE : FALSE);
}

BOOL CPFLPService::Update(CONST CTMEnvironment *pTMEnvironment)
{
	CTimeKey  tUpdate;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((((m_nCode & PFLP_SERVICE_NOAVAILABILITY) != PFLP_SERVICE_NOAVAILABILITY) && (((m_nCode & PFLP_SERVICE_UNLIMITEDAVAILABILITY) || ((m_nCode & PFLP_SERVICE_DAILYAVAILABILITY) && tUpdate.GetTime() % SECONDSPERDAY >= m_tStartTime.GetTotalSeconds() && tUpdate.GetTime() % SECONDSPERDAY <= m_tStopTime.GetTotalSeconds())) && ((m_nCode & PFLP_SERVICE_WORKINGDAYSAVAILABILITY) != PFLP_SERVICE_WORKINGDAYSAVAILABILITY || tUpdate.GetDayOfWeek() == Monday || tUpdate.GetDayOfWeek() == Tuesday || tUpdate.GetDayOfWeek() == Wednesday || tUpdate.GetDayOfWeek() == Thursday || tUpdate.GetDayOfWeek() == Friday))) ? m_cServiceThread.Update(pTMEnvironment->GetTMUnit()) : FALSE);
}

BOOL CPFLPService::SetServiceInfo(CONST CByteArray &nInfo)
{
	CByteArray  nDevicesInfo;
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	for (CopyMemory(&sServiceInfo, nInfo.GetData(), (nInfo.GetSize() >= sizeof(SERVICEINFO)) ? sizeof(SERVICEINFO) : 0); sServiceInfo.cbSize == (INT)nInfo.GetSize() && sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbDevices && sServiceInfo.cbDevices >= 0; )
	{
		for (nDevicesInfo.SetSize(sServiceInfo.cbDevices), CopyMemory(nDevicesInfo.GetData(), nInfo.GetData() + sizeof(SERVICEINFO), sServiceInfo.cbDevices), m_nCode = sServiceInfo.nCode, m_tStartTime = sServiceInfo.tStartTime, m_tStopTime = sServiceInfo.tStopTime; m_pDevices.Unmap(nDevicesInfo) && m_pDevices.EnumDevices() >= 0; ) return TRUE;
		break;
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CPFLPService::GetServiceInfo(CByteArray &nInfo) CONST
{
	CByteArray  nDevicesInfo;
	SERVICEINFO  sServiceInfo;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	for (sServiceInfo.nCode = m_nCode, sServiceInfo.tStartTime = m_tStartTime.GetTotalSeconds(), sServiceInfo.tStopTime = m_tStopTime.GetTotalSeconds(), sServiceInfo.cbDevices = (m_pDevices.Map(nDevicesInfo)) ? (INT)nDevicesInfo.GetSize() : -1, nInfo.SetSize((sServiceInfo.cbSize = sizeof(SERVICEINFO) + max(sServiceInfo.cbDevices, 0))); nInfo.GetSize() == sServiceInfo.cbSize && sServiceInfo.cbDevices >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO), nDevicesInfo.GetData(), sServiceInfo.cbDevices);
		return TRUE;
	}
	return FALSE;
}

BOOL CPFLPService::UpdateServiceInfo(BOOL bSave)
{
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return((bSave  &&  SaveServiceInfo()) || (!bSave  &&  LoadServiceInfo()));
}

BOOL CPFLPService::IsAvailable() CONST
{
	CPFLPServiceEngine  *pPFLPServiceSupport;
	CSingleLock  cLock(m_cServiceThread.m_pCriticalSection, TRUE);

	return(((pPFLPServiceSupport = GetPFLPServiceSupport()) && pPFLPServiceSupport->IsServiceSupported()) ? (m_pDevices.GetSize() > 0) : FALSE);
}

BOOL CPFLPService::SaveServiceInfo()
{
	CByteArray  nInfo;
	CProfile  cProfile;

	return((GetServiceInfo(nInfo)) ? cProfile.SetPFLPServiceSettingsInfo(nInfo) : FALSE);
}

BOOL CPFLPService::LoadServiceInfo()
{
	CByteArray  nInfo;
	CProfile  cProfile;

	return((cProfile.GetPFLPServiceSettingsInfo(nInfo)) ? SetServiceInfo(nInfo) : FALSE);
}

BOOL CPFLPService::Lock()
{
	return m_cServiceThread.m_pCriticalSection->Lock();
}

BOOL CPFLPService::Unlock()
{
	return m_cServiceThread.m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CSystemAlertInfo

CSystemAlertInfo::CSystemAlertInfo() : CObject()
{
	m_nType = 0;
	m_tTime = 0;
	m_nCategory = 0;
	m_dwTimeout = 0;
}

VOID CSystemAlertInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSystemAlertInfo::GetName() CONST
{
	return m_szName;
}

CString CSystemAlertInfo::TranslateName(LPCTSTR pszName) CONST
{
	INT  nID[2];
	INT  nIDs[2];

	for (nID[0] = 0, nIDs[0] = MAXSYSTEMALERTSNAMES - MINSYSTEMALERTSNAMES; nID[0] <= nIDs[0]; nID[0]++)
	{
		if (!lstrcmp(pszName, STRING(MINSYSTEMALERTSNAMES + nID[0]))) break;
		continue;
	}
	for (nID[1] = 0, nIDs[1] = MAXSYSTEMALERTSSHORTNAMES - MINSYSTEMALERTSSHORTNAMES; nID[0] == nIDs[0] && nID[1] <= nIDs[1]; nID[1]++)
	{
		if (!lstrcmp(pszName, STRING(MINSYSTEMALERTSSHORTNAMES + nID[1]))) break;
		continue;
	}
	return((nID[0] <= nIDs[0]) ? STRING(MINSYSTEMALERTSSHORTNAMES + nID[0]) : ((nID[1] <= nIDs[1]) ? STRING(MINSYSTEMALERTSNAMES + nID[1]) : EMPTYSTRING));
}

VOID CSystemAlertInfo::SetCategory(INT nCategory)
{
	m_nCategory = nCategory;
}

INT CSystemAlertInfo::GetCategory() CONST
{
	return m_nCategory;
}

VOID CSystemAlertInfo::SetType(INT nType)
{
	m_nType = nType;
}

INT CSystemAlertInfo::GetType() CONST
{
	return m_nType;
}

VOID CSystemAlertInfo::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CSystemAlertInfo::GetDescription() CONST
{
	return m_szDescription;
}

VOID CSystemAlertInfo::SetMessage(LPCTSTR pszMessage)
{
	m_szMessage = pszMessage;
}

CString CSystemAlertInfo::GetMessage() CONST
{
	return m_szMessage;
}

VOID CSystemAlertInfo::SetExtraInfo(LPCTSTR pszInfo)
{
	m_szExtraInfo = pszInfo;
}

CString CSystemAlertInfo::GetExtraInfo() CONST
{
	return m_szExtraInfo;
}

VOID CSystemAlertInfo::SetTime(CONST CTimeTag &tTime)
{
	m_tTime = tTime;
}

CTimeTag CSystemAlertInfo::GetTime() CONST
{
	return m_tTime;
}

VOID CSystemAlertInfo::SetTimeout(DWORD dwTimeout)
{
	m_dwTimeout = dwTimeout;
}

DWORD CSystemAlertInfo::GetTimeout() CONST
{
	INT  nPos;
	CString  szName;
	CString  szFormat;

	if (!m_dwTimeout)
	{
		for (szName = m_szName, szName.MakeLower(), szFormat = STRING(IDS_SYSTEMALERTS_TIMEOUT_SECONDS_FORMAT), szFormat.MakeLower(); (nPos = szName.Find(szFormat)) == szName.GetLength() - szFormat.GetLength(); )
		{
			while (--nPos >= 0 && _istdigit(szName.GetAt(nPos))) continue;
			return 1000 * _ttoi(szName.Mid(nPos + 1));
		}
		for (szFormat = STRING(IDS_SYSTEMALERTS_TIMEOUT_SECOND_FORMAT), szFormat.MakeLower(); (nPos = szName.Find(szFormat)) == szName.GetLength() - szFormat.GetLength(); )
		{
			while (--nPos >= 0 && _istdigit(szName.GetAt(nPos))) continue;
			return 1000 * _ttoi(szName.Mid(nPos + 1));
		}
		for (szFormat = STRING(IDS_SYSTEMALERTS_TIMEOUT_MINUTES_FORMAT), szFormat.MakeLower(); (nPos = szName.Find(szFormat)) == szName.GetLength() - szFormat.GetLength(); )
		{
			while (--nPos >= 0 && _istdigit(szName.GetAt(nPos))) continue;
			return 1000 * SECONDSPERMINUTE*_ttoi(szName.Mid(nPos + 1));
		}
		for (szFormat = STRING(IDS_SYSTEMALERTS_TIMEOUT_MINUTE_FORMAT), szFormat.MakeLower(); (nPos = szName.Find(szFormat)) == szName.GetLength() - szFormat.GetLength(); )
		{
			while (--nPos >= 0 && _istdigit(szName.GetAt(nPos))) continue;
			return 1000 * SECONDSPERMINUTE*_ttoi(szName.Mid(nPos + 1));
		}
		for (szFormat = STRING(IDS_SYSTEMALERTS_TIMEOUT_HOURS_FORMAT), szFormat.MakeLower(); (nPos = szName.Find(szFormat)) == szName.GetLength() - szFormat.GetLength(); )
		{
			while (--nPos >= 0 && _istdigit(szName.GetAt(nPos))) continue;
			return 1000 * SECONDSPERHOUR*_ttoi(szName.Mid(nPos + 1));
		}
		for (szFormat = STRING(IDS_SYSTEMALERTS_TIMEOUT_HOUR_FORMAT), szFormat.MakeLower(); (nPos = szName.Find(szFormat)) == szName.GetLength() - szFormat.GetLength(); )
		{
			while (--nPos >= 0 && _istdigit(szName.GetAt(nPos))) continue;
			return 1000 * SECONDSPERHOUR*_ttoi(szName.Mid(nPos + 1));
		}
	}
	return m_dwTimeout;
}

VOID CSystemAlertInfo::SetAudition(LPCTSTR pszAudition)
{
	m_szAudition = pszAudition;
}

CString CSystemAlertInfo::GetAudition() CONST
{
	return m_szAudition;
}

VOID CSystemAlertInfo::SetNotifications(CONST CStringArray &szNotifications)
{
	m_szNotifications.Copy(szNotifications);
}

INT CSystemAlertInfo::GetNotifications(CStringArray &szNotifications) CONST
{
	szNotifications.Copy(m_szNotifications);
	return((INT)szNotifications.GetSize());
}

VOID CSystemAlertInfo::Copy(CONST CSystemAlertInfo *pAlertInfo)
{
	m_szName = pAlertInfo->m_szName;
	m_szMessage = pAlertInfo->m_szMessage;
	m_szAudition = pAlertInfo->m_szAudition;
	m_szExtraInfo = pAlertInfo->m_szExtraInfo;
	m_szDescription = pAlertInfo->m_szDescription;
	m_szNotifications.Copy(pAlertInfo->m_szNotifications);
	m_dwTimeout = pAlertInfo->m_dwTimeout;
	m_nCategory = pAlertInfo->m_nCategory;
	m_nType = pAlertInfo->m_nType;
	m_tTime = pAlertInfo->m_tTime;
}

BOOL CSystemAlertInfo::Compare(CONST CSystemAlertInfo *pAlertInfo) CONST
{
	INT  nNotification;
	INT  nNotifications;

	for (nNotification = 0, nNotifications = (pAlertInfo->m_szName == m_szName && pAlertInfo->m_szDescription == m_szDescription && pAlertInfo->m_szMessage == m_szMessage && pAlertInfo->m_szExtraInfo == m_szExtraInfo && pAlertInfo->m_szAudition == m_szAudition && pAlertInfo->m_szNotifications.GetSize() == m_szNotifications.GetSize() && pAlertInfo->m_dwTimeout == m_dwTimeout && pAlertInfo->m_nCategory == m_nCategory && pAlertInfo->m_nType == m_nType && pAlertInfo->m_tTime == m_tTime) ? (INT)m_szNotifications.GetSize() : -1; nNotification < nNotifications; nNotification++)
	{
		if (pAlertInfo->m_szNotifications.GetAt(nNotification) != m_szNotifications.GetAt(nNotification)) break;
		continue;
	}
	return((nNotification == nNotifications) ? TRUE : FALSE);
}

BOOL CSystemAlertInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nNotification;
	INT  nNotifications;
	CByteArray  nNotificationData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMessage = (m_szMessage.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAudition = (m_szAudition.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDescription = (m_szDescription.GetLength() + 1)*sizeof(TCHAR);
	for (nNotification = 0, nNotifications = (INT)m_szNotifications.GetSize(), sData.cbNotifications = 0; nNotification < nNotifications; nNotification++, sData.cbNotifications += cbData)
	{
		nNotificationData.SetSize(sData.cbNotifications + (cbData = (m_szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nNotificationData.GetData() + sData.cbNotifications, (LPCTSTR)m_szNotifications.GetAt(nNotification), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbDescription + sData.cbMessage + sData.cbAudition + sData.cbNotifications)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szDescription, sData.cbDescription);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDescription), (LPCTSTR)m_szMessage, sData.cbMessage);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMessage), (LPCTSTR)m_szAudition, sData.cbAudition);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAudition), nNotificationData.GetData(), sData.cbNotifications);
		return TRUE;
	}
	return FALSE;
}

BOOL CSystemAlertInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbNotification;
	INT  cbNotifications;
	CByteArray  nNotificationData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbDescription + sData.cbMessage + sData.cbAudition + sData.cbNotifications && sData.cbName > 0 && sData.cbDescription > 0 && sData.cbMessage > 0 && sData.cbAudition > 0 && sData.cbNotifications >= 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szDescription.GetBufferSetLength(STRINGCHARS(sData.cbDescription)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbDescription));
		CopyMemory(m_szMessage.GetBufferSetLength(STRINGCHARS(sData.cbMessage)), nInfo.GetData() + (cbData = cbData + sData.cbDescription), STRINGBYTES(sData.cbMessage));
		CopyMemory(m_szAudition.GetBufferSetLength(STRINGCHARS(sData.cbAudition)), nInfo.GetData() + (cbData = cbData + sData.cbMessage), STRINGBYTES(sData.cbAudition));
		for (nNotificationData.SetSize(sData.cbNotifications), CopyMemory(nNotificationData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbAudition), sData.cbNotifications), m_szName.ReleaseBuffer(), m_szDescription.ReleaseBuffer(), m_szMessage.ReleaseBuffer(), m_szAudition.ReleaseBuffer(), m_szNotifications.RemoveAll(), cbNotification = cbNotifications = 0; cbNotifications < sData.cbNotifications; cbNotifications += (cbNotification = (m_szNotifications.GetAt(m_szNotifications.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szNotifications.Add((LPCTSTR)(nNotificationData.GetData() + cbNotifications));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CSystemAlerts

CSystemAlerts::CSystemAlerts() : CMutexArray()
{
	return;
}

CSystemAlerts::~CSystemAlerts()
{
	RemoveAll();
}

INT CSystemAlerts::Add(CSystemAlertInfo *pAlertInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pAlertInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pAlertInfo, 1);
	return nIndex;
}

INT CSystemAlerts::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CSystemAlerts::Enum(CStringArray &szNames) CONST
{
	INT  nAlert;
	INT  nAlerts;
	CSystemAlertInfo  *pAlertInfo;

	for (nAlert = 0, nAlerts = (INT)GetSize(), szNames.RemoveAll(); nAlert < nAlerts; nAlert++)
	{
		if ((pAlertInfo = GetAt(nAlert)) != (CSystemAlertInfo *)NULL)
		{
			szNames.Add(pAlertInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CSystemAlertInfo *CSystemAlerts::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CSystemAlertInfo *)CMutexArray::GetAt(nIndex) : (CSystemAlertInfo *)NULL);
}
CSystemAlertInfo *CSystemAlerts::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CSystemAlertInfo *)CMutexArray::GetAt(nIndex) : (CSystemAlertInfo *)NULL);
}

VOID CSystemAlerts::RemoveAll()
{
	INT  nAlert;
	INT  nAlerts;
	CSystemAlertInfo  *pAlertInfo;

	for (nAlert = 0, nAlerts = (INT)GetSize(); nAlert < nAlerts; nAlert++)
	{
		if ((pAlertInfo = GetAt(nAlert))) delete pAlertInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CSystemAlerts::Copy(CONST CSystemAlerts *pAlerts)
{
	INT  nAlert;
	INT  nAlerts;
	CSystemAlertInfo  *pAlertInfo;

	for (nAlert = 0, nAlerts = (INT)pAlerts->GetSize(), RemoveAll(); nAlert < nAlerts; nAlert++)
	{
		if ((pAlertInfo = new CSystemAlertInfo))
		{
			pAlertInfo->Copy(pAlerts->GetAt(nAlert));
			InsertAt(nAlert, pAlertInfo, 1);
			continue;
		}
		break;
	}
	return((nAlert == nAlerts) ? TRUE : FALSE);
}

BOOL CSystemAlerts::Compare(CONST CSystemAlerts *pAlerts) CONST
{
	INT  nAlert;
	INT  nAlerts;

	for (nAlert = 0, nAlerts = (pAlerts->GetSize() == GetSize()) ? (INT)GetSize() : -1; nAlert < nAlerts; nAlert++)
	{
		if (!pAlerts->GetAt(nAlert)->Compare(GetAt(nAlert))) break;
		continue;
	}
	return((nAlert == nAlerts) ? TRUE : FALSE);
}

BOOL CSystemAlerts::Map(CByteArray &nInfo) CONST
{
	INT  nAlert;
	INT  nAlerts;
	CByteArray  nAlertData;
	CSystemAlertInfo  *pAlertInfo;

	for (nAlert = 0, nAlerts = (INT)GetSize(), nInfo.RemoveAll(); nAlert < nAlerts; nAlert++)
	{
		if ((pAlertInfo = GetAt(nAlert)) && pAlertInfo->Map(nAlertData) && nInfo.Append(nAlertData) >= 0) continue;
		break;
	}
	return((nAlert == nAlerts) ? TRUE : FALSE);
}

BOOL CSystemAlerts::Unmap(CONST CByteArray &nInfo)
{
	INT  cbAlert;
	INT  cbAlerts;
	CByteArray  nAlertData;
	CSystemAlertInfo  *pAlertInfo;

	for (cbAlerts = 0, RemoveAll(); cbAlerts < nInfo.GetSize(); cbAlerts += cbAlert)
	{
		for (CopyMemory(&cbAlert, nInfo.GetData() + cbAlerts, sizeof(cbAlert)), nAlertData.SetSize(max(min(cbAlert, nInfo.GetSize() - cbAlerts), 0)); nAlertData.GetSize() >= 0; )
		{
			CopyMemory(nAlertData.GetData(), nInfo.GetData() + cbAlerts, nAlertData.GetSize());
			break;
		}
		if ((pAlertInfo = new CSystemAlertInfo))
		{
			if (pAlertInfo->Unmap(nAlertData) && Add(pAlertInfo) >= 0) continue;
			delete pAlertInfo;
		}
		break;
	}
	return((cbAlerts == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CSystemAlerts::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CSystemAlertInfo  *pAlertInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pAlertInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pAlertInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pAlertInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pAlertInfo->GetName() == pszName) || (bInsert && (((pAlertInfo = GetAt(max(nIndex[0] - 1, 0))) && pAlertInfo->GetName() != pszName && (pAlertInfo = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pAlertInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryEventExpression

CTelemetryEventExpression::CTelemetryEventExpression() : CObject()
{
	m_szFunction.Empty();
	m_szOperator.Empty();
	m_szParameter.Empty();
	m_bParameterCode = FALSE;
	m_nParameterSample = 0;
	m_nNumberFlag = 0;
	m_fNumber = 0.0;
}

VOID CTelemetryEventExpression::SetFunction(LPCTSTR pszFunction)
{
	m_szFunction = pszFunction;
	m_szParameter.Empty();
	m_szOperator.Empty();
	m_nNumberFlag = 0;
	m_fNumber = 0.0;
}

CString CTelemetryEventExpression::GetFunction() CONST
{
	return m_szFunction;
}

BOOL CTelemetryEventExpression::IsFunction() CONST
{
	return !m_szFunction.IsEmpty();
}

VOID CTelemetryEventExpression::SetOperator(LPCTSTR pszOperator)
{
	m_szOperator = pszOperator;
	m_szParameter.Empty();
	m_szFunction.Empty();
	m_nNumberFlag = 0;
	m_fNumber = 0.0;
}

CString CTelemetryEventExpression::GetOperator() CONST
{
	return m_szOperator;
}

BOOL CTelemetryEventExpression::IsOperator() CONST
{
	return !m_szOperator.IsEmpty();
}

VOID CTelemetryEventExpression::SetParameter(LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
	m_bParameterCode = FALSE;
	m_nParameterSample = 0;
	m_szFunction.Empty();
	m_szOperator.Empty();
	m_nNumberFlag = 0;
	m_fNumber = 0.0;
}
VOID CTelemetryEventExpression::SetParameter(LPCTSTR pszParameter, INT nSample, BOOL bCode)
{
	m_szParameter = pszParameter;
	m_nParameterSample = nSample;
	m_bParameterCode = bCode;
	m_szFunction.Empty();
	m_szOperator.Empty();
	m_nNumberFlag = 0;
	m_fNumber = 0.0;
}

BOOL CTelemetryEventExpression::GetParameter(CString &szParameter, INT &nSample, BOOL &bCode) CONST
{
	if (IsParameter())
	{
		szParameter = m_szParameter;
		nSample = m_nParameterSample;
		bCode = m_bParameterCode;
		return TRUE;
	}
	return FALSE;
}
CString CTelemetryEventExpression::GetParameter() CONST
{
	return m_szParameter;
}

BOOL CTelemetryEventExpression::IsParameter() CONST
{
	return !m_szParameter.IsEmpty();
}

VOID CTelemetryEventExpression::SetNumber(double fNumber, BOOL bPoint)
{
	m_szFunction.Empty();
	m_szOperator.Empty();
	m_szParameter.Empty();
	m_nNumberFlag = (floor(fNumber) != fNumber || !bPoint) ? TRUE : -1;
	m_fNumber = fNumber;
}

double CTelemetryEventExpression::GetNumber() CONST
{
	return m_fNumber;
}

CString CTelemetryEventExpression::GetNumberAsText() CONST
{
	CString  szNumber;
	CStringTools  cStringTools;

	if (floor(m_fNumber) == m_fNumber  &&  m_nNumberFlag > 0)
	{
		if (m_fNumber >= 0.0  &&  m_fNumber == (double)(ULONGLONG)m_fNumber)
		{
			szNumber = cStringTools.ConvertLongUIntToString((ULONGLONG)m_fNumber);
			return szNumber;
		}
		if (m_fNumber < 0.0  &&  m_fNumber == (double)(LONGLONG)m_fNumber)
		{
			szNumber = cStringTools.ConvertLongIntToString((LONGLONG)m_fNumber);
			return szNumber;
		}
	}
	if (floor(m_fNumber) == m_fNumber  &&  m_nNumberFlag < 0)
	{
		szNumber = cStringTools.ConvertFloatToString(m_fNumber);
		return szNumber.Left(szNumber.GetLength() - 1);
	}
	return cStringTools.ConvertFloatToString(m_fNumber);
}

BOOL CTelemetryEventExpression::IsNumber() CONST
{
	return((m_nNumberFlag != 0) ? TRUE : FALSE);
}

BOOL CTelemetryEventExpression::IsEmpty() CONST
{
	return((m_szFunction.IsEmpty() && m_szOperator.IsEmpty() && m_szParameter.IsEmpty() && !m_nNumberFlag) ? TRUE : FALSE);
}

VOID CTelemetryEventExpression::Copy(CONST CTelemetryEventExpression *pExpression)
{
	m_szFunction = pExpression->m_szFunction;
	m_szOperator = pExpression->m_szOperator;
	m_szParameter = pExpression->m_szParameter;
	m_bParameterCode = pExpression->m_bParameterCode;
	m_nParameterSample = pExpression->m_nParameterSample;
	m_nNumberFlag = pExpression->m_nNumberFlag;
	m_fNumber = pExpression->m_fNumber;
}

BOOL CTelemetryEventExpression::Compare(CONST CTelemetryEventExpression *pExpression) CONST
{
	return((pExpression->m_szFunction == m_szFunction  &&  pExpression->m_szOperator == m_szOperator && ((pExpression->m_szParameter.IsEmpty() && m_szParameter.IsEmpty()) || (pExpression->m_szParameter == m_szParameter  &&  pExpression->m_bParameterCode == m_bParameterCode  &&  pExpression->m_nParameterSample == m_nParameterSample)) && ((!pExpression->m_nNumberFlag  &&  !m_nNumberFlag) || (pExpression->m_nNumberFlag == m_nNumberFlag  &&  pExpression->m_fNumber == m_fNumber))) ? TRUE : FALSE);
}

BOOL CTelemetryEventExpression::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbFunction = (m_szFunction.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOperator = (m_szOperator.GetLength() + 1)*sizeof(TCHAR);
	sData.cbParameter = (m_szParameter.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbFunction + sData.cbOperator + sData.cbParameter)), sData.nNumberFlag = m_nNumberFlag, sData.fNumber = m_fNumber, sData.bParameterCode = m_bParameterCode, sData.nParameterSample = m_nParameterSample; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szFunction, sData.cbFunction);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFunction), (LPCTSTR)m_szOperator, sData.cbOperator);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOperator), (LPCTSTR)m_szParameter, sData.cbParameter);
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryEventExpression::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbFunction + sData.cbOperator + sData.cbParameter && sData.cbFunction > 0 && sData.cbOperator > 0 && sData.cbParameter > 0; )
	{
		CopyMemory(m_szFunction.GetBufferSetLength(STRINGCHARS(sData.cbFunction)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbFunction));
		CopyMemory(m_szOperator.GetBufferSetLength(STRINGCHARS(sData.cbOperator)), nInfo.GetData() + (cbData = cbData + sData.cbFunction), STRINGBYTES(sData.cbOperator));
		CopyMemory(m_szParameter.GetBufferSetLength(STRINGCHARS(sData.cbParameter)), nInfo.GetData() + (cbData = cbData + sData.cbOperator), STRINGBYTES(sData.cbParameter));
		m_fNumber = sData.fNumber;
		m_nNumberFlag = sData.nNumberFlag;
		m_bParameterCode = sData.bParameterCode;
		m_nParameterSample = sData.nParameterSample;
		m_szFunction.ReleaseBuffer();
		m_szOperator.ReleaseBuffer();
		m_szParameter.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryEventInfo

CTelemetryEventInfo::CTelemetryEventInfo() : CPtrArray()
{
	m_tTime = 0;
	m_nResultCode = 0;
	m_bData[0] = FALSE;
	m_bData[1] = FALSE;
	m_bData[2] = FALSE;
}

CTelemetryEventInfo::~CTelemetryEventInfo()
{
	RemoveAll();
}

VOID CTelemetryEventInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTelemetryEventInfo::GetName() CONST
{
	return m_szName;
}

VOID CTelemetryEventInfo::SetMessage(LPCTSTR pszMessage)
{
	m_szMessage = pszMessage;
}

CString CTelemetryEventInfo::GetMessage() CONST
{
	return m_szMessage;
}

VOID CTelemetryEventInfo::SetTime(CONST CTimeTag &tTime)
{
	m_tTime = tTime;
}

CTimeTag CTelemetryEventInfo::GetTime() CONST
{
	return m_tTime;
}

VOID CTelemetryEventInfo::SetAudition(LPCTSTR pszAudition)
{
	m_szAudition = pszAudition;
}

CString CTelemetryEventInfo::GetAudition() CONST
{
	return m_szAudition;
}

VOID CTelemetryEventInfo::SetNotification(LPCTSTR pszNotification)
{
	m_szNotification = pszNotification;
}

CString CTelemetryEventInfo::GetNotification() CONST
{
	return m_szNotification;
}

VOID CTelemetryEventInfo::SetResultCode(UINT nCode)
{
	m_nResultCode = nCode;
}

UINT CTelemetryEventInfo::GetResultCode() CONST
{
	return m_nResultCode;
}

VOID CTelemetryEventInfo::SetInvalidDataMode(BOOL bEnable)
{
	m_bData[0] = bEnable;
}

BOOL CTelemetryEventInfo::IsInvalidDataModeEnabled() CONST
{
	return m_bData[0];
}

VOID CTelemetryEventInfo::SetBadDataMode(BOOL bEnable)
{
	m_bData[1] = bEnable;
}

BOOL CTelemetryEventInfo::IsBadDataModeEnabled() CONST
{
	return m_bData[1];
}

VOID CTelemetryEventInfo::SetDisabledDataMode(BOOL bEnable)
{
	m_bData[2] = bEnable;
}

BOOL CTelemetryEventInfo::IsDisabledDataModeEnabled() CONST
{
	return m_bData[2];
}

INT CTelemetryEventInfo::Add(CTelemetryEventExpression *pExpression)
{
	return((INT)CPtrArray::Add(pExpression));
}

INT CTelemetryEventInfo::Find(LPCTSTR pszExpression, INT nIndex) CONST
{
	INT  nExpression;
	INT  nExpressions;
	CTelemetryEventExpression  *pExpression;

	for (nExpression = max(nIndex, 0), nExpressions = (INT)GetSize(); nExpression < nExpressions; nExpression++)
	{
		if ((pExpression = GetAt(nExpression)) && ((pExpression->IsFunction() && pExpression->GetFunction() == pszExpression) || (pExpression->IsOperator() && pExpression->GetOperator() == pszExpression) || (pExpression->IsParameter() && pExpression->GetParameter() == pszExpression))) break;
		continue;
	}
	return((nExpression < nExpressions) ? nExpression : -1);
}

CTelemetryEventExpression *CTelemetryEventInfo::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryEventExpression *)CPtrArray::GetAt(nIndex) : (CTelemetryEventExpression *)NULL);
}

CTelemetryEventExpression *CTelemetryEventInfo::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryEventExpression *)CPtrArray::GetAt(nIndex) : (CTelemetryEventExpression *)NULL);
}

VOID CTelemetryEventInfo::RemoveAll()
{
	INT  nExpression;
	INT  nExpressions;
	CTelemetryEventExpression  *pExpression;

	for (nExpression = 0, nExpressions = (INT)GetSize(); nExpression < nExpressions; nExpression++)
	{
		if ((pExpression = GetAt(nExpression))) delete pExpression;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTelemetryEventInfo::Copy(CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nExpression;
	INT  nExpressions;
	CTelemetryEventExpression  *pExpression;

	for (nExpression = 0, nExpressions = (INT)pEventInfo->GetSize(), RemoveAll(), m_szName = pEventInfo->m_szName, m_szMessage = pEventInfo->m_szMessage, m_szAudition = pEventInfo->m_szAudition, m_szNotification = pEventInfo->m_szNotification, m_nResultCode = pEventInfo->m_nResultCode, m_tTime = pEventInfo->m_tTime, m_bData[0] = pEventInfo->m_bData[0], m_bData[1] = pEventInfo->m_bData[1], m_bData[2] = pEventInfo->m_bData[2]; nExpression < nExpressions; nExpression++)
	{
		if ((pExpression = new CTelemetryEventExpression))
		{
			pExpression->Copy(pEventInfo->GetAt(nExpression));
			InsertAt(nExpression, pExpression, 1);
			continue;
		}
		break;
	}
	return((nExpression == nExpressions) ? TRUE : FALSE);
}

BOOL CTelemetryEventInfo::Compare(CONST CTelemetryEventInfo *pEventInfo) CONST
{
	INT  nExpression;
	INT  nExpressions;

	for (nExpression = 0, nExpressions = (pEventInfo->m_szName == m_szName && pEventInfo->m_szMessage == m_szMessage && pEventInfo->m_szAudition == m_szAudition && pEventInfo->m_szNotification == m_szNotification && pEventInfo->m_nResultCode == m_nResultCode && pEventInfo->m_tTime == m_tTime && pEventInfo->m_bData[0] == m_bData[0] && pEventInfo->m_bData[1] == m_bData[1] && pEventInfo->m_bData[2] == m_bData[2]) ? (INT)GetSize() : -1; nExpression < nExpressions; nExpression++)
	{
		if (!pEventInfo->GetAt(nExpression)->Compare(GetAt(nExpression))) break;
		continue;
	}
	return((nExpression == nExpressions) ? TRUE : FALSE);
}

BOOL CTelemetryEventInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nExpression;
	INT  nExpressions;
	CByteArray  nExpressionData[2];
	CTelemetryEventExpression  *pExpression;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMessage = (m_szMessage.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAudition = (m_szAudition.GetLength() + 1)*sizeof(TCHAR);
	sData.cbNotification = (m_szNotification.GetLength() + 1)*sizeof(TCHAR);
	for (nExpression = 0, nExpressions = (INT)GetSize(), sData.bData[0] = m_bData[0], sData.bData[1] = m_bData[1], sData.bData[2] = m_bData[2], sData.nResultCode = m_nResultCode; nExpression < nExpressions; nExpression++)
	{
		if ((pExpression = GetAt(nExpression)) && pExpression->Map(nExpressionData[1]) && nExpressionData[0].Append(nExpressionData[1]) >= 0) continue;
		break;
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbMessage + sData.cbAudition + sData.cbNotification + (sData.cbExpressions = (INT)(nExpressionData[0].GetSize()*sizeof(BYTE))))); nInfo.GetSize() == sData.cbSize && nExpression == nExpressions; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szMessage, sData.cbMessage);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMessage), (LPCTSTR)m_szAudition, sData.cbAudition);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAudition), (LPCTSTR)m_szNotification, sData.cbNotification);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbNotification), nExpressionData[0].GetData(), sData.cbExpressions);
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryEventInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbExpression;
	INT  cbExpressions;
	CByteArray  nExpressionData[2];
	CTelemetryEventExpression  *pExpression;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbMessage + sData.cbAudition + sData.cbNotification + sData.cbExpressions && sData.cbName > 0 && sData.cbMessage > 0 && sData.cbAudition > 0 && sData.cbNotification > 0 && sData.cbExpressions >= 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szMessage.GetBufferSetLength(STRINGCHARS(sData.cbMessage)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbMessage));
		CopyMemory(m_szAudition.GetBufferSetLength(STRINGCHARS(sData.cbAudition)), nInfo.GetData() + (cbData = cbData + sData.cbMessage), STRINGBYTES(sData.cbAudition));
		CopyMemory(m_szNotification.GetBufferSetLength(STRINGCHARS(sData.cbNotification)), nInfo.GetData() + (cbData = cbData + sData.cbAudition), STRINGBYTES(sData.cbNotification));
		for (nExpressionData[0].SetSize(sData.cbExpressions), CopyMemory(nExpressionData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbNotification), sData.cbExpressions), m_bData[0] = sData.bData[0], m_bData[1] = sData.bData[1], m_bData[2] = sData.bData[2], m_nResultCode = sData.nResultCode, m_szName.ReleaseBuffer(), m_szMessage.ReleaseBuffer(), m_szAudition.ReleaseBuffer(), m_szNotification.ReleaseBuffer(), RemoveAll(), cbExpression = cbExpressions = 0; cbExpressions < sData.cbExpressions; cbExpressions += cbExpression)
		{
			for (CopyMemory(&cbExpression, nExpressionData[0].GetData() + cbExpressions, sizeof(cbExpression)), nExpressionData[1].SetSize(max(min(cbExpression, nExpressionData[0].GetSize() - cbExpressions), 0)); nExpressionData[1].GetSize() >= 0; )
			{
				CopyMemory(nExpressionData[1].GetData(), nExpressionData[0].GetData() + cbExpressions, nExpressionData[1].GetSize());
				break;
			}
			if ((pExpression = new CTelemetryEventExpression))
			{
				if (pExpression->Unmap(nExpressionData[1]) && Add(pExpression) >= 0) continue;
				delete pExpression;
			}
			break;
		}
		return((cbExpressions == sData.cbExpressions) ? TRUE : FALSE);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryEvents

CTelemetryEvents::CTelemetryEvents() : CMutexArray()
{
	return;
}

CTelemetryEvents::~CTelemetryEvents()
{
	RemoveAll();
}

INT CTelemetryEvents::Add(CTelemetryEventInfo *pEventInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pEventInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pEventInfo, 1);
	return nIndex;
}

INT CTelemetryEvents::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CTelemetryEventInfo *CTelemetryEvents::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryEventInfo *)CMutexArray::GetAt(nIndex) : (CTelemetryEventInfo *)NULL);
}

CTelemetryEventInfo *CTelemetryEvents::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryEventInfo *)CMutexArray::GetAt(nIndex) : (CTelemetryEventInfo *)NULL);
}

VOID CTelemetryEvents::RemoveAll()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (INT)GetSize(); nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = GetAt(nEvent))) delete pEventInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CTelemetryEvents::Copy(CONST CTelemetryEvents *pEvents)
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (INT)pEvents->GetSize(), RemoveAll(); nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = new CTelemetryEventInfo))
		{
			pEventInfo->Copy(pEvents->GetAt(nEvent));
			InsertAt(nEvent, pEventInfo, 1);
			continue;
		}
		break;
	}
	return((nEvent == nEvents) ? TRUE : FALSE);
}

BOOL CTelemetryEvents::Compare(CONST CTelemetryEvents *pEvents) CONST
{
	INT  nEvent;
	INT  nEvents;

	for (nEvent = 0, nEvents = (pEvents->GetSize() == GetSize()) ? (INT)GetSize() : -1; nEvent < nEvents; nEvent++)
	{
		if (!pEvents->GetAt(nEvent)->Compare(GetAt(nEvent))) break;
		continue;
	}
	return((nEvent == nEvents) ? TRUE : FALSE);
}

BOOL CTelemetryEvents::Map(CByteArray &nInfo) CONST
{
	INT  nEvent;
	INT  nEvents;
	CByteArray  nEventData;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (INT)GetSize(), nInfo.RemoveAll(); nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = GetAt(nEvent)) && pEventInfo->Map(nEventData) && nInfo.Append(nEventData) >= 0) continue;
		break;
	}
	return((nEvent == nEvents) ? TRUE : FALSE);
}

BOOL CTelemetryEvents::Unmap(CONST CByteArray &nInfo)
{
	INT  cbEvent;
	INT  cbEvents;
	CByteArray  nEventData;
	CTelemetryEventInfo  *pEventInfo;

	for (cbEvents = 0, RemoveAll(); cbEvents < nInfo.GetSize(); cbEvents += cbEvent)
	{
		for (CopyMemory(&cbEvent, nInfo.GetData() + cbEvents, sizeof(cbEvent)), nEventData.SetSize(max(min(cbEvent, nInfo.GetSize() - cbEvents), 0)); nEventData.GetSize() >= 0; )
		{
			CopyMemory(nEventData.GetData(), nInfo.GetData() + cbEvents, nEventData.GetSize());
			break;
		}
		if ((pEventInfo = new CTelemetryEventInfo))
		{
			if (pEventInfo->Unmap(nEventData) && Add(pEventInfo) >= 0) continue;
			delete pEventInfo;
		}
		break;
	}
	return((cbEvents == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTelemetryEvents::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTelemetryEventInfo  *pEventInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pEventInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pEventInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pEventInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pEventInfo->GetName() == pszName) || (bInsert && (((pEventInfo = GetAt(max(nIndex[0] - 1, 0))) && pEventInfo->GetName() != pszName && (pEventInfo = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pEventInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFileTriggerInfo

CTelemetryReportFileTriggerInfo::CTelemetryReportFileTriggerInfo() : CObject()
{
	m_nAttributes = TELEMETRYREPORT_FILETRIGGER_TRACKMODE_NONE;
}
CTelemetryReportFileTriggerInfo::CTelemetryReportFileTriggerInfo(CTelemetryReportFileTriggerInfo *pTriggerInfo) : CObject()
{
	Copy(pTriggerInfo);
}

VOID CTelemetryReportFileTriggerInfo::SetDirectory(LPCTSTR pszDirectory)
{
	m_szDirectory = pszDirectory;
}

CString CTelemetryReportFileTriggerInfo::GetDirectory() CONST
{
	return m_szDirectory;
}

VOID CTelemetryReportFileTriggerInfo::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CTelemetryReportFileTriggerInfo::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CTelemetryReportFileTriggerInfo::SetFilteredFiles(CONST CStringArray &szFiles, CONST CUIntArray &nFileAttributes)
{
	m_szFilteredFiles.Copy(szFiles);
	m_nFileAttributes.Copy(nFileAttributes);
}

INT CTelemetryReportFileTriggerInfo::GetFilteredFiles(CStringArray &szFiles, CUIntArray &nFileAttributes) CONST
{
	szFiles.Copy(m_szFilteredFiles);
	nFileAttributes.Copy(m_nFileAttributes);
	return((szFiles.GetSize() == nFileAttributes.GetSize()) ? (INT)szFiles.GetSize() : 0);
}

BOOL CTelemetryReportFileTriggerInfo::SetFileListing(LPCTSTR pszListing, LPCTSTR pszTime)
{
	if (m_nAttributes & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_ALLFILES)
	{
		m_szFileListings[0].SetAtGrow(0, pszListing);
		m_szFileListings[1].SetAtGrow(0, pszTime);
		m_szFileListings[0].SetSize(1);
		m_szFileListings[1].SetSize(1);
		return TRUE;
	}
	return FALSE;
}
BOOL CTelemetryReportFileTriggerInfo::SetFileListing(INT nIndex, LPCTSTR pszListing, LPCTSTR pszTime)
{
	if (m_nAttributes & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_SELECTEDFILES)
	{
		m_szFileListings[0].SetAtGrow(nIndex, pszListing);
		m_szFileListings[1].SetAtGrow(nIndex, pszTime);
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportFileTriggerInfo::GetFileListing(CString &szListing, CString &szTime) CONST
{
	for (szListing.Empty(), szTime.Empty(); m_nAttributes & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_ALLFILES; )
	{
		if (m_szFileListings[0].GetSize() > 0 && m_szFileListings[1].GetSize() > 0)
		{
			szListing = m_szFileListings[0].GetAt(0);
			szTime = m_szFileListings[1].GetAt(0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
BOOL CTelemetryReportFileTriggerInfo::GetFileListing(INT nIndex, CString &szListing, CString &szTime) CONST
{
	for (szListing.Empty(), szTime.Empty(); m_nAttributes & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_SELECTEDFILES; )
	{
		if (nIndex >= 0 && nIndex < m_szFileListings[0].GetSize() && nIndex < m_szFileListings[1].GetSize())
		{
			szListing = m_szFileListings[0].GetAt(nIndex);
			szTime = m_szFileListings[1].GetAt(nIndex);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

VOID CTelemetryReportFileTriggerInfo::Copy(CONST CTelemetryReportFileTriggerInfo *pTriggerInfo)
{
	m_szDirectory = pTriggerInfo->m_szDirectory;
	m_nAttributes = pTriggerInfo->m_nAttributes;
	m_nFileAttributes.Copy(pTriggerInfo->m_nFileAttributes);
	m_szFilteredFiles.Copy(pTriggerInfo->m_szFilteredFiles);
	m_szFileListings[0].Copy(pTriggerInfo->m_szFileListings[0]);
	m_szFileListings[1].Copy(pTriggerInfo->m_szFileListings[1]);
}

BOOL CTelemetryReportFileTriggerInfo::Compare(CONST CTelemetryReportFileTriggerInfo *pTriggerInfo) CONST
{
	INT  nFile[2];
	INT  nFiles[2];

	for (nFile[0] = 0, nFiles[0] = (!pTriggerInfo->m_szDirectory.CompareNoCase(m_szDirectory) && pTriggerInfo->m_nAttributes == m_nAttributes && pTriggerInfo->m_szFilteredFiles.GetSize() == m_szFilteredFiles.GetSize() && pTriggerInfo->m_szFileListings[0].GetSize() == m_szFileListings[0].GetSize() && pTriggerInfo->m_szFileListings[1].GetSize() == m_szFileListings[1].GetSize()) ? (INT)m_szFilteredFiles.GetSize() : -1; nFile[0] < nFiles[0]; nFile[0]++)
	{
		for (nFile[1] = 0, nFiles[1] = (INT)pTriggerInfo->m_szFilteredFiles.GetSize(); nFile[1] < nFiles[1]; nFile[1]++)
		{
			if (pTriggerInfo->m_szFilteredFiles.GetAt(nFile[1]).CompareNoCase(m_szFilteredFiles.GetAt(nFile[0]))) continue;
			if (pTriggerInfo->m_nFileAttributes.GetAt(nFile[1]) != m_nFileAttributes.GetAt(nFile[0])) continue;
			if (nFile[0] < m_szFileListings[0].GetSize() && nFile[1] < pTriggerInfo->m_szFileListings[0].GetSize() && pTriggerInfo->m_szFileListings[0].GetAt(nFile[1]).CompareNoCase(m_szFileListings[0].GetAt(nFile[0]))) continue;
			if (nFile[0] < m_szFileListings[1].GetSize() && nFile[1] < pTriggerInfo->m_szFileListings[1].GetSize() && pTriggerInfo->m_szFileListings[1].GetAt(nFile[1]).CompareNoCase(m_szFileListings[1].GetAt(nFile[0]))) continue;
			break;
		}
		if (nFile[1] == nFiles[1]) break;
	}
	return((nFile[0] == nFiles[0]) ? TRUE : FALSE);
}

BOOL CTelemetryReportFileTriggerInfo::Map(CByteArray &nInfo) CONST
{
	INT  nFile;
	INT  nFiles;
	INT  cbData;
	DATA  sData;
	CByteArray  nFilteredFilesData;

	for (nFile = 0, nFiles = (INT)m_szFilteredFiles.GetSize(), sData.cbDirectory = (m_szDirectory.GetLength() + 1)*sizeof(TCHAR), sData.cbFileAttributes = (INT)(m_nFileAttributes.GetSize()*sizeof(UINT)), sData.cbFilteredFiles = 0; nFile < nFiles; nFile++, sData.cbFilteredFiles += cbData)
	{
		nFilteredFilesData.SetSize(sData.cbFilteredFiles + (cbData = (m_szFilteredFiles.GetAt(nFile).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nFilteredFilesData.GetData() + sData.cbFilteredFiles, (LPCTSTR)m_szFilteredFiles.GetAt(nFile), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbDirectory + sData.cbFilteredFiles + sData.cbFileAttributes)), sData.nAttributes = m_nAttributes; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szDirectory, sData.cbDirectory);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDirectory), nFilteredFilesData.GetData(), sData.cbFilteredFiles);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFilteredFiles), m_nFileAttributes.GetData(), sData.cbFileAttributes);
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportFileTriggerInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbFile;
	INT  cbFiles;
	INT  cbData;
	DATA  sData;
	CByteArray  nFilteredFilesData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDirectory + sData.cbFilteredFiles + sData.cbFileAttributes && sData.cbDirectory > 0 && sData.cbFilteredFiles >= 0 && sData.cbFileAttributes >= 0; )
	{
		for (nFilteredFilesData.SetSize(sData.cbFilteredFiles), m_nFileAttributes.SetSize(sData.cbFileAttributes / sizeof(UINT)), CopyMemory(m_szDirectory.GetBufferSetLength(STRINGCHARS(sData.cbDirectory)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbDirectory)), CopyMemory(nFilteredFilesData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDirectory), sData.cbFilteredFiles), CopyMemory(m_nFileAttributes.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFilteredFiles), sData.cbFileAttributes), m_nAttributes = sData.nAttributes, cbFile = cbFiles = 0, m_szDirectory.ReleaseBuffer(), m_szFilteredFiles.RemoveAll(); cbFiles < sData.cbFilteredFiles; cbFiles += cbFile)
		{
			m_szFilteredFiles.Add((LPCTSTR)(nFilteredFilesData.GetData() + cbFiles));
			cbFile = (m_szFilteredFiles.GetAt(m_szFilteredFiles.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFileTriggers

CTelemetryReportFileTriggers::CTelemetryReportFileTriggers() : CPtrArray()
{
	return;
}

CTelemetryReportFileTriggers::~CTelemetryReportFileTriggers()
{
	RemoveAll();
}

INT CTelemetryReportFileTriggers::Add(CTelemetryReportFileTriggerInfo *pTriggerInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTriggerInfo->GetDirectory(), TRUE)) >= 0) InsertAt(nIndex, pTriggerInfo, 1);
	return nIndex;
}

INT CTelemetryReportFileTriggers::Find(LPCTSTR pszDirectory) CONST
{
	return FindIndex(pszDirectory);
}

CTelemetryReportFileTriggerInfo *CTelemetryReportFileTriggers::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportFileTriggerInfo *)CPtrArray::GetAt(nIndex) : (CTelemetryReportFileTriggerInfo *)NULL);
}

CTelemetryReportFileTriggerInfo *CTelemetryReportFileTriggers::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportFileTriggerInfo *)CPtrArray::GetAt(nIndex) : (CTelemetryReportFileTriggerInfo *)NULL);
}

VOID CTelemetryReportFileTriggers::RemoveAll()
{
	INT  nTrigger;
	INT  nTriggers;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo;

	for (nTrigger = 0, nTriggers = (INT)GetSize(); nTrigger < nTriggers; nTrigger++)
	{
		if ((pTriggerInfo = GetAt(nTrigger))) delete pTriggerInfo;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTelemetryReportFileTriggers::Copy(CONST CTelemetryReportFileTriggers *pTriggers)
{
	INT  nTrigger;
	INT  nTriggers;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo;

	for (nTrigger = 0, nTriggers = (INT)pTriggers->GetSize(), RemoveAll(); nTrigger < nTriggers; nTrigger++)
	{
		if ((pTriggerInfo = new CTelemetryReportFileTriggerInfo))
		{
			pTriggerInfo->Copy(pTriggers->GetAt(nTrigger));
			InsertAt(nTrigger, pTriggerInfo, 1);
			continue;
		}
		break;
	}
	return((nTrigger == nTriggers) ? TRUE : FALSE);
}

BOOL CTelemetryReportFileTriggers::Compare(CONST CTelemetryReportFileTriggers *pTriggers) CONST
{
	INT  nTrigger[2];
	INT  nTriggers[2];

	for (nTrigger[0] = 0, nTriggers[0] = (pTriggers->GetSize() == GetSize()) ? (INT)GetSize() : -1; nTrigger[0] < nTriggers[0]; nTrigger[0]++)
	{
		for (nTrigger[1] = 0, nTriggers[1] = (INT)pTriggers->GetSize(); nTrigger[1] < nTriggers[1]; nTrigger[1]++)
		{
			if (pTriggers->GetAt(nTrigger[1])->Compare(GetAt(nTrigger[0]))) break;
			continue;
		}
		if (nTrigger[1] == nTriggers[1]) break;
	}
	return((nTrigger[0] == nTriggers[0]) ? TRUE : FALSE);
}

BOOL CTelemetryReportFileTriggers::Map(CByteArray &nInfo) CONST
{
	INT  nTrigger;
	INT  nTriggers;
	CByteArray  nTriggerData;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo;

	for (nTrigger = 0, nTriggers = (INT)GetSize(), nInfo.RemoveAll(); nTrigger < nTriggers; nTrigger++)
	{
		if ((pTriggerInfo = GetAt(nTrigger)) && pTriggerInfo->Map(nTriggerData) && nInfo.Append(nTriggerData) >= 0) continue;
		break;
	}
	return((nTrigger == nTriggers) ? TRUE : FALSE);
}

BOOL CTelemetryReportFileTriggers::Unmap(CONST CByteArray &nInfo)
{
	INT  cbTrigger;
	INT  cbTriggers;
	CByteArray  nTriggerData;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo;

	for (cbTriggers = 0, RemoveAll(); cbTriggers < nInfo.GetSize(); cbTriggers += cbTrigger)
	{
		for (CopyMemory(&cbTrigger, nInfo.GetData() + cbTriggers, sizeof(cbTrigger)), nTriggerData.SetSize(max(min(cbTrigger, nInfo.GetSize() - cbTriggers), 0)); nTriggerData.GetSize() >= 0; )
		{
			CopyMemory(nTriggerData.GetData(), nInfo.GetData() + cbTriggers, nTriggerData.GetSize());
			break;
		}
		if ((pTriggerInfo = new CTelemetryReportFileTriggerInfo))
		{
			if (pTriggerInfo->Unmap(nTriggerData) && Add(pTriggerInfo) >= 0) continue;
			delete pTriggerInfo;
		}
		break;
	}
	return((cbTriggers == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTelemetryReportFileTriggers::FindIndex(LPCTSTR pszDirectory, BOOL bInsert) CONST
{
	INT  nTrigger;
	INT  nTriggers;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo;

	for (nTrigger = 0, nTriggers = (INT)GetSize(); nTrigger < nTriggers; nTrigger++)
	{
		if ((pTriggerInfo = GetAt(nTrigger)) && !pTriggerInfo->GetDirectory().CompareNoCase(pszDirectory)) break;
		continue;
	}
	return(((!bInsert  &&  nTrigger < nTriggers) || (bInsert  &&  nTrigger == nTriggers)) ? nTrigger : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFTPRecipientInfo

CTelemetryReportFTPRecipientInfo::CTelemetryReportFTPRecipientInfo() : CObject()
{
	m_nPort = 0;
	m_tRetryTime = 0;
	m_tRetryInterval = 0;
	m_nRetryCount[0] = 0;
	m_nRetryCount[1] = 0;
	m_nAudition = TELEMETRYREPORT_FTPRECIPIENT_AUDITION_NONE;
	m_bSend = FALSE;
}
CTelemetryReportFTPRecipientInfo::CTelemetryReportFTPRecipientInfo(CTelemetryReportFTPRecipientInfo *pRecipientInfo) : CObject()
{
	Copy(pRecipientInfo);
}

VOID CTelemetryReportFTPRecipientInfo::SetLocation(LPCTSTR pszLocation)
{
	m_szLocation = pszLocation;
}

CString CTelemetryReportFTPRecipientInfo::GetLocation() CONST
{
	return m_szLocation;
}

VOID CTelemetryReportFTPRecipientInfo::SetUserName(LPCTSTR pszUserName)
{
	m_szUserName = pszUserName;
}

CString CTelemetryReportFTPRecipientInfo::GetUserName() CONST
{
	return m_szUserName;
}

VOID CTelemetryReportFTPRecipientInfo::SetPassword(LPCTSTR pszPassword)
{
	m_szPassword = pszPassword;
}

CString CTelemetryReportFTPRecipientInfo::GetPassword() CONST
{
	return m_szPassword;
}

VOID CTelemetryReportFTPRecipientInfo::SetPort(UINT nPort)
{
	m_nPort = nPort;
}

UINT CTelemetryReportFTPRecipientInfo::GetPort() CONST
{
	return m_nPort;
}

VOID CTelemetryReportFTPRecipientInfo::SetRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval)
{
	m_nRetryCount[0] = nRetries;
	m_tRetryInterval = tInterval;
}

BOOL CTelemetryReportFTPRecipientInfo::GetRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST
{
	nRetries = m_nRetryCount[0];
	tInterval = m_tRetryInterval;
	return((nRetries >= 0) ? TRUE : FALSE);
}

VOID CTelemetryReportFTPRecipientInfo::SetRetryTime(CTimeKey &tTime)
{
	m_tRetryTime = tTime;
}

CTimeKey CTelemetryReportFTPRecipientInfo::GetRetryTime() CONST
{
	return m_tRetryTime;
}

VOID CTelemetryReportFTPRecipientInfo::SetRetryCount(UINT nCount)
{
	m_nRetryCount[1] = nCount;
}

UINT CTelemetryReportFTPRecipientInfo::GetRetryCount() CONST
{
	return m_nRetryCount[1];
}

VOID CTelemetryReportFTPRecipientInfo::SetAudition(UINT nAudition)
{
	m_nAudition = nAudition;
}

UINT CTelemetryReportFTPRecipientInfo::GetAudition() CONST
{
	return m_nAudition;
}

VOID CTelemetryReportFTPRecipientInfo::Enable(BOOL bSend)
{
	m_bSend = bSend;
}

BOOL CTelemetryReportFTPRecipientInfo::IsEnabled() CONST
{
	return m_bSend;
}

VOID CTelemetryReportFTPRecipientInfo::Copy(CONST CTelemetryReportFTPRecipientInfo *pRecipientInfo)
{
	m_szLocation = pRecipientInfo->m_szLocation;
	m_szUserName = pRecipientInfo->m_szUserName;
	m_szPassword = pRecipientInfo->m_szPassword;
	m_tRetryTime = pRecipientInfo->m_tRetryTime;
	m_tRetryInterval = pRecipientInfo->m_tRetryInterval;
	m_nRetryCount[0] = pRecipientInfo->m_nRetryCount[0];
	m_nRetryCount[1] = pRecipientInfo->m_nRetryCount[1];
	m_nAudition = pRecipientInfo->m_nAudition;
	m_nPort = pRecipientInfo->m_nPort;
	m_bSend = pRecipientInfo->m_bSend;
}

BOOL CTelemetryReportFTPRecipientInfo::Compare(CONST CTelemetryReportFTPRecipientInfo *pRecipientInfo) CONST
{
	return((!pRecipientInfo->m_szLocation.CompareNoCase(m_szLocation) && pRecipientInfo->m_szUserName == m_szUserName  &&  pRecipientInfo->m_szPassword == m_szPassword  &&  pRecipientInfo->m_nPort == m_nPort  &&  pRecipientInfo->m_nRetryCount[0] == m_nRetryCount[0] && pRecipientInfo->m_tRetryInterval == m_tRetryInterval  &&  pRecipientInfo->m_nAudition == m_nAudition  &&  pRecipientInfo->m_bSend == m_bSend) ? TRUE : FALSE);
}

BOOL CTelemetryReportFTPRecipientInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbLocation = (m_szLocation.GetLength() + 1)*sizeof(TCHAR);
	sData.cbUserName = (m_szUserName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbPassword = (m_szPassword.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbLocation + sData.cbUserName + sData.cbPassword)), sData.nAudition = m_nAudition, sData.bSend = m_bSend, sData.nPort = m_nPort, sData.tRetryTime = m_tRetryTime.GetTime(), sData.tRetryInterval = m_tRetryInterval.GetTotalSeconds(), sData.nRetryCount[0] = m_nRetryCount[0], sData.nRetryCount[1] = m_nRetryCount[1]; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szLocation, sData.cbLocation);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbLocation), (LPCTSTR)m_szUserName, sData.cbUserName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbUserName), (LPCTSTR)m_szPassword, sData.cbPassword);
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportFTPRecipientInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbLocation + sData.cbUserName + sData.cbPassword && sData.cbLocation > 0 && sData.cbUserName > 0 && sData.cbPassword > 0; )
	{
		CopyMemory(m_szLocation.GetBufferSetLength(STRINGCHARS(sData.cbLocation)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbLocation));
		CopyMemory(m_szUserName.GetBufferSetLength(STRINGCHARS(sData.cbUserName)), nInfo.GetData() + (cbData = cbData + sData.cbLocation), STRINGBYTES(sData.cbUserName));
		CopyMemory(m_szPassword.GetBufferSetLength(STRINGCHARS(sData.cbPassword)), nInfo.GetData() + (cbData = cbData + sData.cbUserName), STRINGBYTES(sData.cbPassword));
		m_nPort = sData.nPort;
		m_bSend = sData.bSend;
		m_nAudition = sData.nAudition;
		m_tRetryTime = sData.tRetryTime;
		m_tRetryInterval = sData.tRetryInterval;
		m_nRetryCount[0] = sData.nRetryCount[0];
		m_nRetryCount[1] = sData.nRetryCount[1];
		m_szLocation.ReleaseBuffer();
		m_szUserName.ReleaseBuffer();
		m_szPassword.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportFTPRecipients

CTelemetryReportFTPRecipients::CTelemetryReportFTPRecipients() : CPtrArray()
{
	return;
}

CTelemetryReportFTPRecipients::~CTelemetryReportFTPRecipients()
{
	RemoveAll();
}

INT CTelemetryReportFTPRecipients::Add(CTelemetryReportFTPRecipientInfo *pRecipientInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pRecipientInfo->GetLocation(), pRecipientInfo->GetUserName(), TRUE)) >= 0) InsertAt(nIndex, pRecipientInfo, 1);
	return nIndex;
}

INT CTelemetryReportFTPRecipients::Find(LPCTSTR pszLocation, LPCTSTR pszUserName) CONST
{
	return FindIndex(pszLocation, pszUserName);
}

CTelemetryReportFTPRecipientInfo *CTelemetryReportFTPRecipients::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportFTPRecipientInfo *)CPtrArray::GetAt(nIndex) : (CTelemetryReportFTPRecipientInfo *)NULL);
}

CTelemetryReportFTPRecipientInfo *CTelemetryReportFTPRecipients::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportFTPRecipientInfo *)CPtrArray::GetAt(nIndex) : (CTelemetryReportFTPRecipientInfo *)NULL);
}

VOID CTelemetryReportFTPRecipients::RemoveAll()
{
	INT  nRecipient;
	INT  nRecipients;
	CTelemetryReportFTPRecipientInfo  *pRecipientInfo;

	for (nRecipient = 0, nRecipients = (INT)GetSize(); nRecipient < nRecipients; nRecipient++)
	{
		if ((pRecipientInfo = GetAt(nRecipient))) delete pRecipientInfo;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTelemetryReportFTPRecipients::Copy(CONST CTelemetryReportFTPRecipients *pRecipients)
{
	INT  nRecipient;
	INT  nRecipients;
	CTelemetryReportFTPRecipientInfo  *pRecipientInfo;

	for (nRecipient = 0, nRecipients = (INT)pRecipients->GetSize(), RemoveAll(); nRecipient < nRecipients; nRecipient++)
	{
		if ((pRecipientInfo = new CTelemetryReportFTPRecipientInfo))
		{
			pRecipientInfo->Copy(pRecipients->GetAt(nRecipient));
			InsertAt(nRecipient, pRecipientInfo, 1);
			continue;
		}
		break;
	}
	return((nRecipient < nRecipients) ? TRUE : FALSE);
}

BOOL CTelemetryReportFTPRecipients::Compare(CONST CTelemetryReportFTPRecipients *pRecipients) CONST
{
	INT  nRecipient[2];
	INT  nRecipients[2];

	for (nRecipient[0] = 0, nRecipients[0] = (pRecipients->GetSize() == GetSize()) ? (INT)GetSize() : -1; nRecipient[0] < nRecipients[0]; nRecipient[0]++)
	{
		for (nRecipient[1] = 0, nRecipients[1] = (INT)pRecipients->GetSize(); nRecipient[1] < nRecipients[1]; nRecipient[1]++)
		{
			if (!pRecipients->GetAt(nRecipient[1])->Compare(GetAt(nRecipient[0]))) break;
			continue;
		}
		if (nRecipient[1] < nRecipients[1]) break;
	}
	return((nRecipient[0] == nRecipients[0]) ? TRUE : FALSE);
}

BOOL CTelemetryReportFTPRecipients::Map(CByteArray &nInfo) CONST
{
	INT  nRecipient;
	INT  nRecipients;
	CByteArray  nRecipientData;
	CTelemetryReportFTPRecipientInfo  *pRecipientInfo;

	for (nRecipient = 0, nRecipients = (INT)GetSize(), nInfo.RemoveAll(); nRecipient < nRecipients; nRecipient++)
	{
		if ((pRecipientInfo = GetAt(nRecipient)) && pRecipientInfo->Map(nRecipientData) && nInfo.Append(nRecipientData) >= 0) continue;
		break;
	}
	return((nRecipient == nRecipients) ? TRUE : FALSE);
}

BOOL CTelemetryReportFTPRecipients::Unmap(CONST CByteArray &nInfo)
{
	INT  cbRecipient;
	INT  cbRecipients;
	CByteArray  nRecipientData;
	CTelemetryReportFTPRecipientInfo  *pRecipientInfo;

	for (cbRecipients = 0, RemoveAll(); cbRecipients < nInfo.GetSize(); cbRecipients += cbRecipient)
	{
		for (CopyMemory(&cbRecipient, nInfo.GetData() + cbRecipients, sizeof(cbRecipient)), nRecipientData.SetSize(max(min(cbRecipient, nInfo.GetSize() - cbRecipients), 0)); nRecipientData.GetSize() >= 0; )
		{
			CopyMemory(nRecipientData.GetData(), nInfo.GetData() + cbRecipients, nRecipientData.GetSize());
			break;
		}
		if ((pRecipientInfo = new CTelemetryReportFTPRecipientInfo))
		{
			if (pRecipientInfo->Unmap(nRecipientData) && Add(pRecipientInfo) >= 0) continue;
			delete pRecipientInfo;
		}
		break;
	}
	return((cbRecipients == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTelemetryReportFTPRecipients::FindIndex(LPCTSTR pszLocation, LPCTSTR pszUserName, BOOL bInsert) CONST
{
	INT  nRecipient;
	INT  nRecipients;
	CTelemetryReportFTPRecipientInfo  *pRecipientInfo;

	for (nRecipient = 0, nRecipients = (INT)GetSize(); nRecipient < nRecipients; nRecipient++)
	{
		if ((pRecipientInfo = GetAt(nRecipient)) && !pRecipientInfo->GetLocation().CompareNoCase(pszLocation) && pRecipientInfo->GetUserName() == pszUserName) break;
		continue;
	}
	return(((!bInsert  &&  nRecipient < nRecipients) || (bInsert  &&  nRecipient == nRecipients)) ? nRecipient : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportInfo

CTelemetryReportInfo::CTelemetryReportInfo() : CObject()
{
	m_nOptions = TELEMETRTREPORTINFO_OPTION_KEEPALLFILES | TELEMETRYREPORTINFO_OPTION_MAILWEEKLY;
	m_tMailTime[0] = SECONDSPERHOUR*(m_tMailTime[0].GetTime() / SECONDSPERHOUR);
	m_tMailTime[1] = 0;
	m_tMailInterval = 0;
	m_tPeriodicalTime[0] = 0;
	m_tPeriodicalTime[1] = 0;
	m_tPeriodicalInterval = 0;
	m_tExecutionTime = 0;
	m_nStatus = 0;
}

VOID CTelemetryReportInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTelemetryReportInfo::GetName() CONST
{
	return m_szName;
}

VOID CTelemetryReportInfo::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CTelemetryReportInfo::GetOptions() CONST
{
	return m_nOptions;
}

VOID CTelemetryReportInfo::SetLink(CONST CByteArray &nData)
{
	m_nLinkData.Copy(nData);
}

INT CTelemetryReportInfo::GetLink(CByteArray &nData) CONST
{
	nData.Copy(m_nLinkData);
	return((INT)nData.GetSize());
}

VOID CTelemetryReportInfo::SetHistoricalSource(LPCTSTR pszSource)
{
	m_szSource = pszSource;
}

CString CTelemetryReportInfo::GetHistoricalSource() CONST
{
	return m_szSource;
}

BOOL CTelemetryReportInfo::SetHistoricalPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tInterval)
{
	if (tStartTime <= tStopTime  &&  tStartTime > 0)
	{
		m_nOptions = (m_nOptions & ~TELEMETRYREPORTINFO_OPTION_SCHEDULED) | TELEMETRYREPORTINFO_OPTION_HISTORICAL;
		m_tPeriodicalTime[0] = tStartTime;
		m_tPeriodicalTime[1] = tStopTime;
		m_tPeriodicalInterval = tInterval;
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportInfo::GetHistoricalPeriod(CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tInterval) CONST
{
	tStartTime = m_tPeriodicalTime[0];
	tStopTime = m_tPeriodicalTime[1];
	tInterval = m_tPeriodicalInterval;
	return((m_nOptions & TELEMETRYREPORTINFO_OPTION_HISTORICAL) ? TRUE : FALSE);
}

BOOL CTelemetryReportInfo::SetScheduledPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tInterval)
{
	if ((tStartTime > 0 && ((tStopTime == 0 && tInterval == 0) || (tInterval > 0 && (tStopTime == 0 || tStopTime >= tStartTime.GetTime() + tInterval.GetTotalSeconds())))) || (tStartTime == 0 && tStopTime == 0 && tInterval == 0))
	{
		m_nOptions = (tStartTime > 0) ? ((m_nOptions & ~TELEMETRYREPORTINFO_OPTION_HISTORICAL) | TELEMETRYREPORTINFO_OPTION_SCHEDULED) : (m_nOptions & ~TELEMETRYREPORTINFO_OPTION_SCHEDULED);
		m_tPeriodicalTime[0] = tStartTime;
		m_tPeriodicalTime[1] = tStopTime;
		m_tPeriodicalInterval = tInterval;
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportInfo::GetScheduledPeriod(CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tInterval) CONST
{
	tStartTime = m_tPeriodicalTime[0];
	tStopTime = m_tPeriodicalTime[1];
	tInterval = m_tPeriodicalInterval;
	return((m_nOptions & TELEMETRYREPORTINFO_OPTION_SCHEDULED) ? TRUE : FALSE);
}

BOOL CTelemetryReportInfo::SetFileTriggers(CONST CTelemetryReportFileTriggers &pTriggers)
{
	return m_pFileTriggers.Copy(&pTriggers);
}

INT CTelemetryReportInfo::GetFileTriggers(CTelemetryReportFileTriggers &pTriggers) CONST
{
	pTriggers.Copy(&m_pFileTriggers);
	return((INT)pTriggers.GetSize());
}

VOID CTelemetryReportInfo::SetLastExecutionTime(CONST CTimeKey &tTime)
{
	m_tExecutionTime = tTime;
}

CTimeKey CTelemetryReportInfo::GetLastExecutionTime() CONST
{
	return m_tExecutionTime;
}

VOID CTelemetryReportInfo::SetEvents(CONST CStringArray &szEvents)
{
	m_szEvents.Copy(szEvents);
}

INT CTelemetryReportInfo::GetEvents(CStringArray &szEvents) CONST
{
	szEvents.Copy(m_szEvents);
	return((INT)szEvents.GetSize());
}

VOID CTelemetryReportInfo::SetAlerts(CONST CStringArray &szAlerts)
{
	m_szAlerts.Copy(szAlerts);
}

INT CTelemetryReportInfo::GetAlerts(CStringArray &szAlerts) CONST
{
	szAlerts.Copy(m_szAlerts);
	return((INT)szAlerts.GetSize());
}

VOID CTelemetryReportInfo::SetScript(LPCTSTR pszScript)
{
	m_szScript = pszScript;
}

CString CTelemetryReportInfo::GetScript() CONST
{
	return m_szScript;
}

VOID CTelemetryReportInfo::SetInputFileName(LPCTSTR pszFileName)
{
	m_szInputFileName = pszFileName;
}

CString CTelemetryReportInfo::GetInputFileName() CONST
{
	return m_szInputFileName;
}

VOID CTelemetryReportInfo::SetOutputFileName(LPCTSTR pszFileName)
{
	m_szOutputFileName = pszFileName;
}

CString CTelemetryReportInfo::GetOutputFileName() CONST
{
	return m_szOutputFileName;
}

VOID CTelemetryReportInfo::SetMailFileName(LPCTSTR pszFileName)
{
	m_szMailFileName = pszFileName;
}

CString CTelemetryReportInfo::GetMailFileName() CONST
{
	return m_szMailFileName;
}

VOID CTelemetryReportInfo::SetMailTime(CONST CTimeKey &tTime)
{
	m_tMailTime[0] = tTime;
}

CTimeKey CTelemetryReportInfo::GetMailTime() CONST
{
	return m_tMailTime[0];
}

VOID CTelemetryReportInfo::SetLastMailTime(CONST CTimeKey &tTime)
{
	m_tMailTime[1] = tTime;
}

CTimeKey CTelemetryReportInfo::GetLastMailTime() CONST
{
	return m_tMailTime[1];
}

VOID CTelemetryReportInfo::SetMailTimeInterval(CONST CTimeSpan &tInterval)
{
	m_tMailInterval = tInterval;
}

CTimeSpan CTelemetryReportInfo::GetMailTimeInterval() CONST
{
	return m_tMailInterval;
}

VOID CTelemetryReportInfo::SetMailRecipients(CONST CStringArray &szRecipients)
{
	m_szMailRecipients.Copy(szRecipients);
}
VOID CTelemetryReportInfo::SetMailRecipients(CONST CTelemetryReportFTPRecipients &pRecipients)
{
	m_pMailRecipients.Copy(&pRecipients);
}

INT CTelemetryReportInfo::GetMailRecipients(CStringArray &szRecipients) CONST
{
	szRecipients.Copy(m_szMailRecipients);
	return((INT)szRecipients.GetSize());
}
INT CTelemetryReportInfo::GetMailRecipients(CTelemetryReportFTPRecipients &pRecipients) CONST
{
	pRecipients.Copy(&m_pMailRecipients);
	return((INT)pRecipients.GetSize());
}

VOID CTelemetryReportInfo::SetStatus(UINT nStatus)
{
	m_nStatus = nStatus;
}

UINT CTelemetryReportInfo::GetStatus() CONST
{
	return m_nStatus;
}

VOID CTelemetryReportInfo::Copy(CONST CTelemetryReportInfo *pReportInfo)
{
	m_szName = pReportInfo->m_szName;
	m_nStatus = pReportInfo->m_nStatus;
	m_nOptions = pReportInfo->m_nOptions;
	m_szSource = pReportInfo->m_szSource;
	m_szScript = pReportInfo->m_szScript;
	m_szInputFileName = pReportInfo->m_szInputFileName;
	m_szOutputFileName = pReportInfo->m_szOutputFileName;
	m_szMailFileName = pReportInfo->m_szMailFileName;
	m_nLinkData.Copy(pReportInfo->m_nLinkData);
	m_szEvents.Copy(pReportInfo->m_szEvents);
	m_szAlerts.Copy(pReportInfo->m_szAlerts);
	m_tMailTime[0] = pReportInfo->m_tMailTime[0];
	m_tMailTime[1] = pReportInfo->m_tMailTime[1];
	m_tMailInterval = pReportInfo->m_tMailInterval;
	m_tExecutionTime = pReportInfo->m_tExecutionTime;
	m_tPeriodicalTime[0] = pReportInfo->m_tPeriodicalTime[0];
	m_tPeriodicalTime[1] = pReportInfo->m_tPeriodicalTime[1];
	m_tPeriodicalInterval = pReportInfo->m_tPeriodicalInterval;
	m_szMailRecipients.Copy(pReportInfo->m_szMailRecipients);
	m_pMailRecipients.Copy(&pReportInfo->m_pMailRecipients);
	m_pFileTriggers.Copy(&pReportInfo->m_pFileTriggers);
}

BOOL CTelemetryReportInfo::Compare(CONST CTelemetryReportInfo *pReportInfo) CONST
{
	INT  nAlert[2];
	INT  nAlerts[2];
	INT  nEvent[2];
	INT  nEvents[2];
	INT  nRecipient[2];
	INT  nRecipients[2];

	for (nEvent[0] = 0, nEvents[0] = (pReportInfo->m_szName == m_szName && pReportInfo->m_nOptions == m_nOptions && !pReportInfo->m_szSource.CompareNoCase(m_szSource) && pReportInfo->m_szScript == m_szScript && !pReportInfo->m_szInputFileName.CompareNoCase(m_szInputFileName) && !pReportInfo->m_szOutputFileName.CompareNoCase(m_szOutputFileName) && !pReportInfo->m_szMailFileName.CompareNoCase(m_szMailFileName) && pReportInfo->m_nLinkData.GetSize() == m_nLinkData.GetSize() && !memcmp(pReportInfo->m_nLinkData.GetData(), m_nLinkData.GetData(), m_nLinkData.GetSize()*sizeof(BYTE)) && pReportInfo->m_tPeriodicalTime[0] == m_tPeriodicalTime[0] && pReportInfo->m_tPeriodicalTime[1] == m_tPeriodicalTime[1] && pReportInfo->m_tPeriodicalInterval == m_tPeriodicalInterval && pReportInfo->m_tExecutionTime == m_tExecutionTime && (((pReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILDAILY) && pReportInfo->m_tMailTime[0].GetTime() % SECONDSPERDAY == m_tMailTime[0].GetTime() % SECONDSPERDAY && pReportInfo->m_tMailInterval == m_tMailInterval) || ((pReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILWEEKLY) && pReportInfo->m_tMailTime[0].GetTime() % SECONDSPERWEEK == m_tMailTime[0].GetTime() % SECONDSPERWEEK && pReportInfo->m_tMailInterval == m_tMailInterval) || (pReportInfo->GetOptions() & (TELEMETRYREPORTINFO_OPTION_MAILDAILY | TELEMETRYREPORTINFO_OPTION_MAILWEEKLY)) == 0) && pReportInfo->m_tMailTime[1] == m_tMailTime[1] && pReportInfo->m_szEvents.GetSize() == m_szEvents.GetSize() && pReportInfo->m_pFileTriggers.Compare(&m_pFileTriggers) && pReportInfo->m_nStatus == m_nStatus) ? (INT)pReportInfo->m_szEvents.GetSize() : -1; nEvent[0] < nEvents[0]; nEvent[0]++)
	{
		for (nEvent[1] = 0, nEvents[1] = (INT)m_szEvents.GetSize(); nEvent[1] < nEvents[1]; nEvent[1]++)
		{
			if (!pReportInfo->m_szEvents.GetAt(nEvent[0]).Compare(m_szEvents.GetAt(nEvent[1]))) break;
			continue;
		}
		if (nEvent[1] == nEvents[1]) break;
	}
	for (nAlert[0] = 0, nAlerts[0] = (pReportInfo->m_szAlerts.GetSize() == m_szAlerts.GetSize() && nEvent[0] == nEvents[0]) ? (INT)pReportInfo->m_szAlerts.GetSize() : -1; nAlert[0] < nAlerts[0]; nAlert[0]++)
	{
		for (nAlert[1] = 0, nAlerts[1] = (INT)m_szAlerts.GetSize(); nAlert[1] < nAlerts[1]; nAlert[1]++)
		{
			if (!pReportInfo->m_szAlerts.GetAt(nAlert[0]).Compare(m_szAlerts.GetAt(nAlert[1]))) break;
			continue;
		}
		if (nAlert[1] == nAlerts[1]) break;
	}
	for (nRecipient[0] = 0, nRecipients[0] = (pReportInfo->m_szMailRecipients.GetSize() == m_szMailRecipients.GetSize() && pReportInfo->m_pMailRecipients.Compare(&m_pMailRecipients) && nEvent[0] == nEvents[0] && nAlert[0] == nAlerts[0]) ? (INT)pReportInfo->m_szMailRecipients.GetSize() : -1; nRecipient[0] < nRecipients[0]; nRecipient[0]++)
	{
		for (nRecipient[1] = 0, nRecipients[1] = (INT)m_szMailRecipients.GetSize(); nRecipient[1] < nRecipients[1]; nRecipient[1]++)
		{
			if (!pReportInfo->m_szMailRecipients.GetAt(nRecipient[0]).Compare(m_szMailRecipients.GetAt(nRecipient[1]))) break;
			continue;
		}
		if (nRecipient[1] == nRecipients[1]) break;
	}
	return((nEvent[0] == nEvents[0] && nAlert[0] == nAlerts[0] && nRecipient[0] == nRecipients[0]) ? TRUE : FALSE);
}

BOOL CTelemetryReportInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nAlert;
	INT  nAlerts;
	INT  nEvent;
	INT  nEvents;
	INT  nRecipient;
	INT  nRecipients;
	CByteArray  nAlertData;
	CByteArray  nEventData;
	CByteArray  nTriggersData;
	CByteArray  nRecipientData[2];

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbSource = (m_szSource.GetLength() + 1)*sizeof(TCHAR);
	sData.cbScript = (m_szScript.GetLength() + 1)*sizeof(TCHAR);
	sData.cbLinkData = (INT)(m_nLinkData.GetSize()*sizeof(BYTE));
	sData.cbMailFileName = (m_szMailFileName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbInputFileName = (m_szInputFileName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOutputFileName = (m_szOutputFileName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFileTriggers = (m_pFileTriggers.Map(nTriggersData)) ? (INT)nTriggersData.GetSize() : -1;
	for (nEvent = 0, nEvents = (INT)m_szEvents.GetSize(), sData.nOptions = m_nOptions, sData.tMailTime[0] = m_tMailTime[0].GetTime(), sData.tMailTime[1] = m_tMailTime[1].GetTime(), sData.tMailInterval = m_tMailInterval.GetTotalSeconds(), sData.tPeriodicalTime[0] = m_tPeriodicalTime[0].GetTime(), sData.tPeriodicalTime[1] = m_tPeriodicalTime[1].GetTime(), sData.tPeriodicalInterval = m_tPeriodicalInterval.GetTotalSeconds(), sData.cbEvents = 0; nEvent < nEvents; nEvent++, sData.cbEvents += cbData)
	{
		nEventData.SetSize(sData.cbEvents + (cbData = (m_szEvents.GetAt(nEvent).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nEventData.GetData() + sData.cbEvents, (LPCTSTR)m_szEvents.GetAt(nEvent), cbData);
	}
	for (nAlert = 0, nAlerts = (INT)m_szAlerts.GetSize(), sData.cbAlerts = 0; nAlert < nAlerts; nAlert++, sData.cbAlerts += cbData)
	{
		nAlertData.SetSize(sData.cbAlerts + (cbData = (m_szAlerts.GetAt(nAlert).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nAlertData.GetData() + sData.cbAlerts, (LPCTSTR)m_szAlerts.GetAt(nAlert), cbData);
	}
	for (nRecipient = 0, nRecipients = (INT)m_szMailRecipients.GetSize(), sData.cbMailRecipients[1] = (m_pMailRecipients.Map(nRecipientData[1])) ? (INT)(nRecipientData[1].GetSize()*sizeof(BYTE)) : -1, sData.cbMailRecipients[0] = 0; nRecipient < nRecipients; nRecipient++, sData.cbMailRecipients[0] += cbData)
	{
		nRecipientData[0].SetSize(sData.cbMailRecipients[0] + (cbData = (m_szMailRecipients.GetAt(nRecipient).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nRecipientData[0].GetData() + sData.cbMailRecipients[0], (LPCTSTR)m_szMailRecipients.GetAt(nRecipient), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbLinkData + sData.cbSource + sData.cbScript + sData.cbEvents + sData.cbAlerts + sData.cbMailFileName + sData.cbInputFileName + sData.cbOutputFileName + max(sData.cbFileTriggers, 0) + sData.cbMailRecipients[0] + max(sData.cbMailRecipients[1], 0))); nInfo.GetSize() == sData.cbSize && sData.cbFileTriggers >= 0 && sData.cbMailRecipients[1] >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), m_nLinkData.GetData(), sData.cbLinkData);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbLinkData), (LPCTSTR)m_szSource, sData.cbSource);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSource), (LPCTSTR)m_szScript, sData.cbScript);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbScript), (LPCTSTR)m_szInputFileName, sData.cbInputFileName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInputFileName), (LPCTSTR)m_szOutputFileName, sData.cbOutputFileName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOutputFileName), (LPCTSTR)m_szMailFileName, sData.cbMailFileName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMailFileName), nEventData.GetData(), sData.cbEvents);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbEvents), nAlertData.GetData(), sData.cbAlerts);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAlerts), nTriggersData.GetData(), sData.cbFileTriggers);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileTriggers), nRecipientData[0].GetData(), sData.cbMailRecipients[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMailRecipients[0]), nRecipientData[1].GetData(), sData.cbMailRecipients[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbAlert;
	INT  cbAlerts;
	INT  cbEvent;
	INT  cbEvents;
	INT  cbRecipient;
	INT  cbRecipients;
	CByteArray  nAlertData;
	CByteArray  nEventData;
	CByteArray  nTriggersData;
	CByteArray  nRecipientData[2];

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbLinkData + sData.cbSource + sData.cbScript + sData.cbEvents + sData.cbAlerts + sData.cbInputFileName + sData.cbOutputFileName + sData.cbFileTriggers + sData.cbMailFileName + sData.cbMailRecipients[0] + sData.cbMailRecipients[1] && sData.cbName > 0 && sData.cbLinkData >= 0 && sData.cbSource > 0 && sData.cbScript > 0 && sData.cbEvents >= 0 && sData.cbAlerts >= 0 && sData.cbInputFileName > 0 && sData.cbOutputFileName > 0 && sData.cbFileTriggers >= 0 && sData.cbMailFileName > 0 && sData.cbMailRecipients[0] >= 0 && sData.cbMailRecipients[1] >= 0; )
	{
		for (m_nLinkData.SetSize(sData.cbLinkData), nEventData.SetSize(sData.cbEvents); m_nLinkData.GetSize() == sData.cbLinkData && nEventData.GetSize() == sData.cbEvents; )
		{
			CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
			CopyMemory(m_nLinkData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbName), sData.cbLinkData);
			CopyMemory(m_szSource.GetBufferSetLength(STRINGCHARS(sData.cbSource)), nInfo.GetData() + (cbData = cbData + sData.cbLinkData), STRINGBYTES(sData.cbSource));
			CopyMemory(m_szScript.GetBufferSetLength(STRINGCHARS(sData.cbScript)), nInfo.GetData() + (cbData = cbData + sData.cbSource), STRINGBYTES(sData.cbScript));
			CopyMemory(m_szInputFileName.GetBufferSetLength(STRINGCHARS(sData.cbInputFileName)), nInfo.GetData() + (cbData = cbData + sData.cbScript), STRINGBYTES(sData.cbInputFileName));
			CopyMemory(m_szOutputFileName.GetBufferSetLength(STRINGCHARS(sData.cbOutputFileName)), nInfo.GetData() + (cbData = cbData + sData.cbInputFileName), STRINGBYTES(sData.cbOutputFileName));
			CopyMemory(m_szMailFileName.GetBufferSetLength(STRINGCHARS(sData.cbMailFileName)), nInfo.GetData() + (cbData = cbData + sData.cbOutputFileName), STRINGBYTES(sData.cbMailFileName));
			for (CopyMemory(nEventData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbMailFileName), sData.cbEvents), m_nOptions = sData.nOptions, m_tMailTime[0] = sData.tMailTime[0], m_tMailTime[1] = sData.tMailTime[1], m_tMailInterval = sData.tMailInterval, m_tPeriodicalTime[0] = sData.tPeriodicalTime[0], m_tPeriodicalTime[1] = sData.tPeriodicalTime[1], m_tPeriodicalInterval = sData.tPeriodicalInterval, m_szName.ReleaseBuffer(), m_szSource.ReleaseBuffer(), m_szScript.ReleaseBuffer(), m_szInputFileName.ReleaseBuffer(), m_szOutputFileName.ReleaseBuffer(), m_szMailFileName.ReleaseBuffer(), m_szEvents.RemoveAll(), cbEvent = cbEvents = 0; cbEvents < sData.cbEvents; cbEvents += (cbEvent = (m_szEvents.GetAt(m_szEvents.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
			{
				m_szEvents.Add((LPCTSTR)(nEventData.GetData() + cbEvents));
				continue;
			}
			for (nAlertData.SetSize(sData.cbAlerts), nTriggersData.SetSize(sData.cbFileTriggers), CopyMemory(nAlertData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbEvents), sData.cbAlerts), CopyMemory(nTriggersData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbAlerts), sData.cbFileTriggers), m_szAlerts.RemoveAll(), cbAlert = cbAlerts = 0; cbAlerts < sData.cbAlerts; cbAlerts += (cbAlert = (m_szAlerts.GetAt(m_szAlerts.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
			{
				m_szAlerts.Add((LPCTSTR)(nAlertData.GetData() + cbAlerts));
				continue;
			}
			for (nRecipientData[0].SetSize(sData.cbMailRecipients[0]), nRecipientData[1].SetSize(sData.cbMailRecipients[1]), CopyMemory(nRecipientData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFileTriggers), sData.cbMailRecipients[0]), CopyMemory(nRecipientData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbMailRecipients[0]), sData.cbMailRecipients[1]), m_szMailRecipients.RemoveAll(), cbRecipient = cbRecipients = 0; cbRecipients < sData.cbMailRecipients[0]; cbRecipients += (cbRecipient = (m_szMailRecipients.GetAt(m_szMailRecipients.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
			{
				m_szMailRecipients.Add((LPCTSTR)(nRecipientData[0].GetData() + cbRecipients));
				continue;
			}
			return((m_pFileTriggers.Unmap(nTriggersData) && m_pMailRecipients.Unmap(nRecipientData[1])) ? TRUE : FALSE);
		}
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReports

CTelemetryReports::CTelemetryReports() : CMutexArray()
{
	return;
}

CTelemetryReports::~CTelemetryReports()
{
	RemoveAll();
}

INT CTelemetryReports::Add(CTelemetryReportInfo *pReportInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pReportInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pReportInfo, 1);
	return nIndex;
}

INT CTelemetryReports::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CTelemetryReportInfo *CTelemetryReports::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportInfo *)CMutexArray::GetAt(nIndex) : (CTelemetryReportInfo *)NULL);
}

CTelemetryReportInfo *CTelemetryReports::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportInfo *)CMutexArray::GetAt(nIndex) : (CTelemetryReportInfo *)NULL);
}

VOID CTelemetryReports::RemoveAll()
{
	INT  nReport;
	INT  nReports;
	CTelemetryReportInfo  *pReportInfo;

	for (nReport = 0, nReports = (INT)GetSize(); nReport < nReports; nReport++)
	{
		if ((pReportInfo = GetAt(nReport))) delete pReportInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CTelemetryReports::Copy(CONST CTelemetryReports *pReports)
{
	INT  nReport;
	INT  nReports;
	CTelemetryReportInfo  *pReportInfo;

	for (nReport = 0, nReports = (INT)pReports->GetSize(), RemoveAll(); nReport < nReports; nReport++)
	{
		if ((pReportInfo = new CTelemetryReportInfo))
		{
			pReportInfo->Copy(pReports->GetAt(nReport));
			InsertAt(nReport, pReportInfo, 1);
			continue;
		}
		break;
	}
	return((nReport == nReports) ? TRUE : FALSE);
}

BOOL CTelemetryReports::Compare(CONST CTelemetryReports *pReports) CONST
{
	INT  nReport;
	INT  nReports;

	for (nReport = 0, nReports = (pReports->GetSize() == GetSize()) ? (INT)GetSize() : -1; nReport < nReports; nReport++)
	{
		if (!pReports->GetAt(nReport)->Compare(GetAt(nReport))) break;
		continue;
	}
	return((nReport == nReports) ? TRUE : FALSE);
}

BOOL CTelemetryReports::Map(CByteArray &nInfo) CONST
{
	INT  nReport;
	INT  nReports;
	CByteArray  nReportData;
	CTelemetryReportInfo  *pReportInfo;

	for (nReport = 0, nReports = (INT)GetSize(), nInfo.RemoveAll(); nReport < nReports; nReport++)
	{
		if ((pReportInfo = GetAt(nReport)) && pReportInfo->Map(nReportData) && nInfo.Append(nReportData) >= 0) continue;
		break;
	}
	return((nReport == nReports) ? TRUE : FALSE);
}

BOOL CTelemetryReports::Unmap(CONST CByteArray &nInfo)
{
	INT  cbReport;
	INT  cbReports;
	CByteArray  nReportData;
	CTelemetryReportInfo  *pReportInfo;

	for (cbReports = 0, RemoveAll(); cbReports < nInfo.GetSize(); cbReports += cbReport)
	{
		for (CopyMemory(&cbReport, nInfo.GetData() + cbReports, sizeof(cbReport)), nReportData.SetSize(max(min(cbReport, nInfo.GetSize() - cbReports), 0)); nReportData.GetSize() >= 0; )
		{
			CopyMemory(nReportData.GetData(), nInfo.GetData() + cbReports, nReportData.GetSize());
			break;
		}
		if ((pReportInfo = new CTelemetryReportInfo))
		{
			if (pReportInfo->Unmap(nReportData))
			{
				InsertAt(GetSize(), pReportInfo, 1);
				continue;
			}
			delete pReportInfo;
		}
		break;
	}
	return((cbReports == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTelemetryReports::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTelemetryReportInfo  *pReportInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pReportInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pReportInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pReportInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pReportInfo->GetName() == pszName) || (bInsert && (((pReportInfo = GetAt(max(nIndex[0] - 1, 0))) && pReportInfo->GetName() != pszName && (pReportInfo = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pReportInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryHistoricalReportInfo

CTelemetryHistoricalReportInfo::CTelemetryHistoricalReportInfo() : CObject()
{
	SetName(STRING(IDS_TELEMETRYREPORTS_DEFAULT_NAME));
	SetOptions(0);
	SetTimeRangeMode(0);
	SetExecutionMode(0);
	SetExecutionCycle(0);
	SetRangeInterval(0);
	SetLastExecutionTime(0);
	SetInputFTPPort(0);
}

CTelemetryHistoricalReportInfo::~CTelemetryHistoricalReportInfo()
{
	return;
}

VOID CTelemetryHistoricalReportInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTelemetryHistoricalReportInfo::GetName() CONST
{
	return m_szName;
}

VOID CTelemetryHistoricalReportInfo::SetReport(LPCTSTR pszReport)
{
	m_szReport = pszReport;
}

CString CTelemetryHistoricalReportInfo::GetReport() CONST
{
	return m_szReport;
}

VOID CTelemetryHistoricalReportInfo::SetSource(LPCTSTR pszSource)
{
	m_szSource = pszSource;
}

CString CTelemetryHistoricalReportInfo::GetSource() CONST
{
	return m_szSource;
}

VOID CTelemetryHistoricalReportInfo::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CTelemetryHistoricalReportInfo::GetOptions() CONST
{
	return m_nOptions;
}

VOID CTelemetryHistoricalReportInfo::SetTimeRangeMode(UINT nMode)
{
	if (nMode == TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL || nMode == TELEMETRYHISTORICALREPORTINFO_RANGE_DAILY || nMode == TELEMETRYHISTORICALREPORTINFO_RANGE_COMPLETEINTERVAL || nMode == TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL || nMode == TELEMETRYHISTORICALREPORTINFO_RANGE_TRIGGEREDINTERVAL || !nMode)
	{
		if ((m_nModes[0] = nMode) == 0)
		{
			m_tRange[0] = 0;
			m_tRange[1] = 0;
			m_tDailyRange[0] = 0;
			m_tDailyRange[1] = 0;
			m_tIntervalRange[0] = 0;
			m_tIntervalRange[1] = 0;
		}
	}
}

UINT CTelemetryHistoricalReportInfo::GetTimeRangeMode() CONST
{
	return m_nModes[0];
}

VOID CTelemetryHistoricalReportInfo::SetTimeRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	if (m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL)
	{
		if (tStartTime < tStopTime)
		{
			m_tRange[0] = tStartTime;
			m_tRange[1] = tStopTime;
		}
	}
}

BOOL CTelemetryHistoricalReportInfo::GetTimeRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL)
	{
		tStartTime = m_tRange[0];
		tStopTime = m_tRange[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTelemetryHistoricalReportInfo::SetDailyTimeRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	if (m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_DAILY)
	{
		m_tDailyRange[0] = tStartTime;
		m_tDailyRange[1] = tStopTime;
	}
}

BOOL CTelemetryHistoricalReportInfo::GetDailyTimeRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_DAILY)
	{
		tStartTime = m_tDailyRange[0];
		tStopTime = m_tDailyRange[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTelemetryHistoricalReportInfo::SetPeriodicalInterval(CONST CTimeSpan &tInterval)
{
	if (m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL)
	{
		m_tIntervalRange[0] = tInterval;
		return;
	}
}

CTimeSpan CTelemetryHistoricalReportInfo::GetPeriodicalInterval() CONST
{
	return((m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL) ? m_tIntervalRange[0] : CTimeSpan(0));
}

VOID CTelemetryHistoricalReportInfo::SetTriggeredInterval(CONST CTimeSpan &tInterval, BOOL bBefore)
{
	if (m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_TRIGGEREDINTERVAL)
	{
		m_tIntervalRange[0] = (!bBefore) ? tInterval : m_tIntervalRange[0];
		m_tIntervalRange[1] = (bBefore) ? tInterval : m_tIntervalRange[1];
	}
}

CTimeSpan CTelemetryHistoricalReportInfo::GetTriggeredInterval(BOOL bBefore) CONST
{
	return((m_nModes[0] == TELEMETRYHISTORICALREPORTINFO_RANGE_TRIGGEREDINTERVAL) ? ((!bBefore) ? m_tIntervalRange[0] : m_tIntervalRange[1]) : 0);
}

VOID CTelemetryHistoricalReportInfo::SetRangeInterval(CONST CTimeSpan &tInterval)
{
	m_tIntervalRange[2] = tInterval;
}

CTimeSpan CTelemetryHistoricalReportInfo::GetRangeInterval() CONST
{
	return m_tIntervalRange[2];
}

VOID CTelemetryHistoricalReportInfo::SetExecutionMode(UINT nMode)
{
	if (nMode == TELEMETRYHISTORICALREPORTINFO_EXECUTION_IMMEDIATELY || nMode == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME || nMode == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATDAILYTIME || nMode == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL || nMode == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATEVENT || !nMode)
	{
		if ((m_nModes[1] = nMode) == 0)
		{
			m_tExecution[0] = 0;
			m_tExecution[1] = 0;
			m_tExecution[2] = 0;
			m_tDailyExecution = 0;
			m_tIntervalExecution = 0;
		}
	}
}

UINT CTelemetryHistoricalReportInfo::GetExecutionMode() CONST
{
	return m_nModes[1];
}

VOID CTelemetryHistoricalReportInfo::SetExecutionCycle(UINT nCycle)
{
	m_nCycleCount = nCycle;
}

UINT CTelemetryHistoricalReportInfo::GetExecutionCycle() CONST
{
	return m_nCycleCount;
}

VOID CTelemetryHistoricalReportInfo::SetExecutionTime(CONST CTimeKey &tTime)
{
	if (m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME)
	{
		m_tExecution[0] = tTime;
		return;
	}
}

CTimeKey CTelemetryHistoricalReportInfo::GetExecutionTime() CONST
{
	return((m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME) ? m_tExecution[0] : CTimeKey(0));
}

VOID CTelemetryHistoricalReportInfo::SetDailyExecutionTime(CONST CTimeSpan &tTime)
{
	if (m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATDAILYTIME)
	{
		m_tDailyExecution = tTime;
		return;
	}
}

CTimeSpan CTelemetryHistoricalReportInfo::GetDailyExecutionTime() CONST
{
	return((m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATDAILYTIME) ? m_tDailyExecution : CTimeSpan(0));
}

VOID CTelemetryHistoricalReportInfo::SetPeriodicalExecutionTime(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if (m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL)
	{
		m_tExecution[1] = tStartTime;
		m_tExecution[2] = tStopTime;
		m_tIntervalExecution = tInterval;
	}
}

BOOL CTelemetryHistoricalReportInfo::GetPeriodicalExecutionTime(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if (m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL)
	{
		tStartTime = m_tExecution[1];
		tStopTime = m_tExecution[2];
		tInterval = m_tIntervalExecution;
		return TRUE;
	}
	return FALSE;
}

VOID CTelemetryHistoricalReportInfo::SetTriggeredExecution(LPCTSTR pszEvent)
{
	if (m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATEVENT)
	{
		m_szExecutionEvent = pszEvent;
		return;
	}
}

CString CTelemetryHistoricalReportInfo::GetTriggeredExecution() CONST
{
	return((m_nModes[1] == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATEVENT) ? (LPCTSTR)m_szExecutionEvent : EMPTYSTRING);
}

VOID CTelemetryHistoricalReportInfo::SetLastExecutionTime(CONST CTimeKey &tTime)
{
	m_tLastExecution = tTime;
}

CTimeKey CTelemetryHistoricalReportInfo::GetLastExecutionTime() CONST
{
	return m_tLastExecution;
}

VOID CTelemetryHistoricalReportInfo::SetInputFiles(CString &szFiles)
{
	m_szInputFiles = szFiles;
}

CString CTelemetryHistoricalReportInfo::GetInputFiles() CONST
{
	return m_szInputFiles;
}

VOID CTelemetryHistoricalReportInfo::SetInputDirectory(LPCTSTR pszDirectory)
{
	m_szInputDirectory = pszDirectory;
}

CString CTelemetryHistoricalReportInfo::GetInputDirectory() CONST
{
	return m_szInputDirectory;
}

VOID CTelemetryHistoricalReportInfo::SetInputFTPLocation(LPCTSTR pszLocation)
{
	m_szInputFTPLocation = pszLocation;
}

CString CTelemetryHistoricalReportInfo::GetInputFTPLocation() CONST
{
	return m_szInputFTPLocation;
}

VOID CTelemetryHistoricalReportInfo::SetInputFTPUserName(LPCTSTR pszUserName)
{
	m_szInputFTPUserName = pszUserName;
}

CString CTelemetryHistoricalReportInfo::GetInputFTPUserName() CONST
{
	return m_szInputFTPUserName;
}

VOID CTelemetryHistoricalReportInfo::SetInputFTPPassword(LPCTSTR pszPassword)
{
	m_szInputFTPPassword = pszPassword;
}

CString CTelemetryHistoricalReportInfo::GetInputFTPPassword() CONST
{
	return m_szInputFTPPassword;
}

VOID CTelemetryHistoricalReportInfo::SetInputFTPPort(UINT nPort)
{
	m_nInputFTPPort = nPort;
}

UINT CTelemetryHistoricalReportInfo::GetInputFTPPort() CONST
{
	return m_nInputFTPPort;
}

VOID CTelemetryHistoricalReportInfo::SetOutputFile(LPCTSTR pszFileName)
{
	m_szOutputFile = pszFileName;
}

CString CTelemetryHistoricalReportInfo::GetOutputFile() CONST
{
	return m_szOutputFile;
}

VOID CTelemetryHistoricalReportInfo::SetMailRecipients(CONST CStringArray &szRecipients)
{
	m_szMailRecipients.Copy(szRecipients);
}
VOID CTelemetryHistoricalReportInfo::SetMailRecipients(CONST CTelemetryReportFTPRecipients &pRecipients)
{
	m_pMailRecipients.Copy(&pRecipients);
}

INT CTelemetryHistoricalReportInfo::GetMailRecipients(CStringArray &szRecipients) CONST
{
	szRecipients.Copy(m_szMailRecipients);
	return((INT)szRecipients.GetSize());
}
INT CTelemetryHistoricalReportInfo::GetMailRecipients(CTelemetryReportFTPRecipients &pRecipients) CONST
{
	pRecipients.Copy(&m_pMailRecipients);
	return((INT)pRecipients.GetSize());
}

VOID CTelemetryHistoricalReportInfo::Copy(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo)
{
	m_szName = pHistoricalReportInfo->m_szName;
	m_szReport = pHistoricalReportInfo->m_szReport;
	m_szSource = pHistoricalReportInfo->m_szSource;
	m_nOptions = pHistoricalReportInfo->m_nOptions;
	m_nModes[0] = pHistoricalReportInfo->m_nModes[0];
	m_nModes[1] = pHistoricalReportInfo->m_nModes[1];
	m_tRange[0] = pHistoricalReportInfo->m_tRange[0];
	m_tRange[1] = pHistoricalReportInfo->m_tRange[1];
	m_nCycleCount = pHistoricalReportInfo->m_nCycleCount;
	m_tDailyRange[0] = pHistoricalReportInfo->m_tDailyRange[0];
	m_tDailyRange[1] = pHistoricalReportInfo->m_tDailyRange[1];
	m_tIntervalRange[0] = pHistoricalReportInfo->m_tIntervalRange[0];
	m_tIntervalRange[1] = pHistoricalReportInfo->m_tIntervalRange[1];
	m_tIntervalRange[2] = pHistoricalReportInfo->m_tIntervalRange[2];
	m_tExecution[0] = pHistoricalReportInfo->m_tExecution[0];
	m_tExecution[1] = pHistoricalReportInfo->m_tExecution[1];
	m_tExecution[2] = pHistoricalReportInfo->m_tExecution[2];
	m_tLastExecution = pHistoricalReportInfo->m_tLastExecution;
	m_tDailyExecution = pHistoricalReportInfo->m_tDailyExecution;
	m_tIntervalExecution = pHistoricalReportInfo->m_tIntervalExecution;
	m_szExecutionEvent = pHistoricalReportInfo->m_szExecutionEvent;
	m_szInputFiles = pHistoricalReportInfo->m_szInputFiles;
	m_szOutputFile = pHistoricalReportInfo->m_szOutputFile;
	m_nInputFTPPort = pHistoricalReportInfo->m_nInputFTPPort;
	m_szInputDirectory = pHistoricalReportInfo->m_szInputDirectory;
	m_szInputFTPLocation = pHistoricalReportInfo->m_szInputFTPLocation;
	m_szInputFTPUserName = pHistoricalReportInfo->m_szInputFTPUserName;
	m_szInputFTPPassword = pHistoricalReportInfo->m_szInputFTPPassword;
	m_szMailRecipients.Copy(pHistoricalReportInfo->m_szMailRecipients);
	m_pMailRecipients.Copy(&pHistoricalReportInfo->m_pMailRecipients);
}

BOOL CTelemetryHistoricalReportInfo::Compare(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST
{
	INT  nRecipient[2];
	INT  nRecipients[2];

	for (nRecipient[0] = 0, nRecipients[0] = (pHistoricalReportInfo->m_szName == m_szName && pHistoricalReportInfo->m_szReport == m_szReport && !pHistoricalReportInfo->m_szSource.CompareNoCase(m_szSource) && pHistoricalReportInfo->m_nOptions == m_nOptions && pHistoricalReportInfo->m_nModes[0] == m_nModes[0] && pHistoricalReportInfo->m_nModes[1] == m_nModes[1] && (m_nModes[0] != TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL || (pHistoricalReportInfo->m_tRange[0] == m_tRange[0] && pHistoricalReportInfo->m_tRange[1] == m_tRange[1])) && (m_nModes[0] != TELEMETRYHISTORICALREPORTINFO_RANGE_DAILY || (pHistoricalReportInfo->m_tDailyRange[0] == m_tDailyRange[0] && pHistoricalReportInfo->m_tDailyRange[1] == m_tDailyRange[1])) && (m_nModes[0] != TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL || pHistoricalReportInfo->m_tIntervalRange[0] == m_tIntervalRange[0]) && (m_nModes[0] != TELEMETRYHISTORICALREPORTINFO_RANGE_TRIGGEREDINTERVAL || (pHistoricalReportInfo->m_tIntervalRange[0] == m_tIntervalRange[0] && pHistoricalReportInfo->m_tIntervalRange[1] == m_tIntervalRange[1])) && pHistoricalReportInfo->m_tIntervalRange[2] == m_tIntervalRange[2] && ((m_nModes[1] != TELEMETRYHISTORICALREPORTINFO_EXECUTION_IMMEDIATELY && m_nModes[1] != TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME) || pHistoricalReportInfo->m_tExecution[0] == m_tExecution[0]) && (m_nModes[1] != TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATDAILYTIME || pHistoricalReportInfo->m_tDailyExecution == m_tDailyExecution) && (m_nModes[1] != TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL || (pHistoricalReportInfo->m_tExecution[1] == m_tExecution[1] && pHistoricalReportInfo->m_tIntervalExecution == m_tIntervalExecution && pHistoricalReportInfo->m_tExecution[2] == m_tExecution[2])) && (m_nModes[1] != TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATEVENT || pHistoricalReportInfo->m_szExecutionEvent == m_szExecutionEvent) && !pHistoricalReportInfo->m_szInputFiles.CompareNoCase(m_szInputFiles) && !pHistoricalReportInfo->m_szInputDirectory.CompareNoCase(m_szInputDirectory) && !pHistoricalReportInfo->m_szInputFTPLocation.CompareNoCase(m_szInputFTPLocation) && pHistoricalReportInfo->m_szInputFTPUserName == m_szInputFTPUserName && pHistoricalReportInfo->m_szInputFTPPassword == m_szInputFTPPassword && pHistoricalReportInfo->m_nInputFTPPort == m_nInputFTPPort && !pHistoricalReportInfo->m_szOutputFile.CompareNoCase(m_szOutputFile) && pHistoricalReportInfo->m_pMailRecipients.Compare(&m_pMailRecipients) && pHistoricalReportInfo->m_szMailRecipients.GetSize() == m_szMailRecipients.GetSize()) ? (INT)pHistoricalReportInfo->m_szMailRecipients.GetSize() : -1; nRecipient[0] < nRecipients[0]; nRecipient[0]++)
	{
		for (nRecipient[1] = 0, nRecipients[1] = (INT)m_szMailRecipients.GetSize(); nRecipient[1] < nRecipients[1]; nRecipient[1]++)
		{
			if (pHistoricalReportInfo->m_szMailRecipients.GetAt(nRecipient[0]) == m_szMailRecipients.GetAt(nRecipient[1])) break;
			continue;
		}
		if (nRecipient[1] == nRecipients[1]) break;
	}
	return((nRecipient[0] == nRecipients[0]) ? TRUE : FALSE);
}

BOOL CTelemetryHistoricalReportInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nRecipient;
	INT  nRecipients;
	CByteArray  nRecipientData[2];

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbReport = (m_szReport.GetLength() + 1)*sizeof(TCHAR);
	sData.cbSource = (m_szSource.GetLength() + 1)*sizeof(TCHAR);
	sData.cbInputFiles = (m_szInputFiles.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOutputFile = (m_szOutputFile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbInputDirectory = (m_szInputDirectory.GetLength() + 1)*sizeof(TCHAR);
	sData.cbExecutionEvent = (m_szExecutionEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbInputFTPLocation = (m_szInputFTPLocation.GetLength() + 1)*sizeof(TCHAR);
	sData.cbInputFTPUserName = (m_szInputFTPUserName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbInputFTPPassword = (m_szInputFTPPassword.GetLength() + 1)*sizeof(TCHAR);
	for (nRecipient = 0, nRecipients = (INT)m_szMailRecipients.GetSize(), sData.nModes[0] = m_nModes[0], sData.nModes[1] = m_nModes[1], sData.nOptions = m_nOptions, sData.tRange[0] = m_tRange[0].GetTime(), sData.tRange[1] = m_tRange[1].GetTime(), sData.tDailyRange[0] = m_tDailyRange[0].GetTotalSeconds(), sData.tDailyRange[1] = m_tDailyRange[1].GetTotalSeconds(), sData.tIntervalRange[0] = m_tIntervalRange[0].GetTotalSeconds(), sData.tIntervalRange[1] = m_tIntervalRange[1].GetTotalSeconds(), sData.tIntervalRange[2] = m_tIntervalRange[2].GetTotalSeconds(), sData.tExecution[0] = m_tExecution[0].GetTime(), sData.tExecution[1] = m_tExecution[1].GetTime(), sData.tExecution[2] = m_tExecution[2].GetTime(), sData.tDailyExecution = m_tDailyExecution.GetTotalSeconds(), sData.tIntervalExecution = m_tIntervalExecution.GetTotalSeconds(), sData.tLastExecution = m_tLastExecution.GetTime(), sData.nCycleCount = m_nCycleCount, sData.nInputFTPPort = m_nInputFTPPort, sData.cbMailRecipients[1] = (m_pMailRecipients.Map(nRecipientData[1])) ? (INT)nRecipientData[1].GetSize() : -1, sData.cbMailRecipients[0] = 0; nRecipient < nRecipients; nRecipient++, sData.cbMailRecipients[0] += cbData)
	{
		nRecipientData[0].SetSize(sData.cbMailRecipients[0] + (cbData = (m_szMailRecipients.GetAt(nRecipient).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nRecipientData[0].GetData() + sData.cbMailRecipients[0], (LPCTSTR)m_szMailRecipients.GetAt(nRecipient), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbReport + sData.cbSource + sData.cbInputFiles + sData.cbOutputFile + sData.cbInputDirectory + sData.cbExecutionEvent + sData.cbInputFTPLocation + sData.cbInputFTPUserName + sData.cbInputFTPPassword + sData.cbMailRecipients[0] + max(sData.cbMailRecipients[1], 0))); nInfo.GetSize() == sData.cbSize && sData.cbMailRecipients[1] >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szReport, sData.cbReport);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbReport), (LPCTSTR)m_szSource, sData.cbSource);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSource), (LPCTSTR)m_szExecutionEvent, sData.cbExecutionEvent);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbExecutionEvent), (LPCTSTR)m_szInputFiles, sData.cbInputFiles);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInputFiles), (LPCTSTR)m_szOutputFile, sData.cbOutputFile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOutputFile), (LPCTSTR)m_szInputDirectory, sData.cbInputDirectory);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInputDirectory), (LPCTSTR)m_szInputFTPLocation, sData.cbInputFTPLocation);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInputFTPLocation), (LPCTSTR)m_szInputFTPUserName, sData.cbInputFTPUserName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInputFTPUserName), (LPCTSTR)m_szInputFTPPassword, sData.cbInputFTPPassword);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInputFTPPassword), nRecipientData[0].GetData(), sData.cbMailRecipients[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMailRecipients[0]), nRecipientData[1].GetData(), sData.cbMailRecipients[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryHistoricalReportInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbRecipient;
	INT  cbRecipients;
	CByteArray  nRecipientData[2];

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbReport + sData.cbSource + sData.cbExecutionEvent + sData.cbInputFiles + sData.cbInputDirectory + sData.cbInputFTPLocation + sData.cbInputFTPUserName + sData.cbInputFTPPassword + sData.cbOutputFile + sData.cbMailRecipients[0] + sData.cbMailRecipients[1] && sData.cbName > 0 && sData.cbReport > 0 && sData.cbSource > 0 && sData.cbExecutionEvent > 0 && sData.cbInputFiles > 0 && sData.cbInputDirectory > 0 && sData.cbInputFTPLocation > 0 && sData.cbInputFTPUserName > 0 && sData.cbInputFTPPassword > 0 && sData.cbOutputFile > 0 && sData.cbMailRecipients[0] >= 0 && sData.cbMailRecipients[1] >= 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szReport.GetBufferSetLength(STRINGCHARS(sData.cbReport)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbReport));
		CopyMemory(m_szSource.GetBufferSetLength(STRINGCHARS(sData.cbSource)), nInfo.GetData() + (cbData = cbData + sData.cbReport), STRINGBYTES(sData.cbSource));
		CopyMemory(m_szExecutionEvent.GetBufferSetLength(STRINGCHARS(sData.cbExecutionEvent)), nInfo.GetData() + (cbData = cbData + sData.cbSource), STRINGBYTES(sData.cbExecutionEvent));
		CopyMemory(m_szInputFiles.GetBufferSetLength(STRINGCHARS(sData.cbInputFiles)), nInfo.GetData() + (cbData = cbData + sData.cbExecutionEvent), STRINGBYTES(sData.cbInputFiles));
		CopyMemory(m_szOutputFile.GetBufferSetLength(STRINGCHARS(sData.cbOutputFile)), nInfo.GetData() + (cbData = cbData + sData.cbInputFiles), STRINGBYTES(sData.cbOutputFile));
		CopyMemory(m_szInputDirectory.GetBufferSetLength(STRINGCHARS(sData.cbInputDirectory)), nInfo.GetData() + (cbData = cbData + sData.cbOutputFile), STRINGBYTES(sData.cbInputDirectory));
		CopyMemory(m_szInputFTPLocation.GetBufferSetLength(STRINGCHARS(sData.cbInputFTPLocation)), nInfo.GetData() + (cbData = cbData + sData.cbInputDirectory), STRINGBYTES(sData.cbInputFTPLocation));
		CopyMemory(m_szInputFTPUserName.GetBufferSetLength(STRINGCHARS(sData.cbInputFTPUserName)), nInfo.GetData() + (cbData = cbData + sData.cbInputFTPLocation), STRINGBYTES(sData.cbInputFTPUserName));
		CopyMemory(m_szInputFTPPassword.GetBufferSetLength(STRINGCHARS(sData.cbInputFTPPassword)), nInfo.GetData() + (cbData = cbData + sData.cbInputFTPUserName), STRINGBYTES(sData.cbInputFTPPassword));
		for (nRecipientData[0].SetSize(sData.cbMailRecipients[0]), nRecipientData[1].SetSize(sData.cbMailRecipients[1]), CopyMemory(nRecipientData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbInputFTPPassword), sData.cbMailRecipients[0]), CopyMemory(nRecipientData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbMailRecipients[0]), sData.cbMailRecipients[1]), m_nModes[0] = sData.nModes[0], m_nModes[1] = sData.nModes[1], m_nOptions = sData.nOptions, m_tRange[0] = sData.tRange[0], m_tRange[1] = sData.tRange[1], m_tDailyRange[0] = sData.tDailyRange[0], m_tDailyRange[1] = sData.tDailyRange[1], m_tIntervalRange[0] = sData.tIntervalRange[0], m_tIntervalRange[1] = sData.tIntervalRange[1], m_tIntervalRange[2] = sData.tIntervalRange[2], m_tExecution[0] = sData.tExecution[0], m_tExecution[1] = sData.tExecution[1], m_tExecution[2] = sData.tExecution[2], m_tDailyExecution = sData.tDailyExecution, m_tIntervalExecution = sData.tIntervalExecution, m_tLastExecution = sData.tLastExecution, m_nCycleCount = sData.nCycleCount, m_nInputFTPPort = sData.nInputFTPPort, m_szName.ReleaseBuffer(), m_szReport.ReleaseBuffer(), m_szSource.ReleaseBuffer(), m_szExecutionEvent.ReleaseBuffer(), m_szInputFiles.ReleaseBuffer(), m_szOutputFile.ReleaseBuffer(), m_szInputDirectory.ReleaseBuffer(), m_szInputFTPLocation.ReleaseBuffer(), m_szInputFTPUserName.ReleaseBuffer(), m_szInputFTPPassword.ReleaseBuffer(), m_szMailRecipients.RemoveAll(), cbRecipient = cbRecipients = 0; cbRecipients < sData.cbMailRecipients[0]; cbRecipients += (cbRecipient = (m_szMailRecipients.GetAt(m_szMailRecipients.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szMailRecipients.Add((LPCTSTR)(nRecipientData[0].GetData() + cbRecipients));
			continue;
		}
		return m_pMailRecipients.Unmap(nRecipientData[1]);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryHistoricalReports

CTelemetryHistoricalReports::CTelemetryHistoricalReports() : CMutexArray()
{
	return;
}

CTelemetryHistoricalReports::~CTelemetryHistoricalReports()
{
	RemoveAll();
}

INT CTelemetryHistoricalReports::Add(CTelemetryHistoricalReportInfo *pHistoricalReportInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pHistoricalReportInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pHistoricalReportInfo, 1);
	return nIndex;
}

INT CTelemetryHistoricalReports::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CTelemetryHistoricalReports::Enum(CStringArray &szNames) CONST
{
	INT  nReport;
	INT  nReports;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	for (nReport = 0, nReports = (INT)GetSize(), szNames.RemoveAll(); nReport < nReports; nReport++)
	{
		if ((pHistoricalReportInfo = GetAt(nReport)) != (CTelemetryHistoricalReportInfo *)NULL)
		{
			szNames.Add(pHistoricalReportInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CTelemetryHistoricalReportInfo *CTelemetryHistoricalReports::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryHistoricalReportInfo *)CMutexArray::GetAt(nIndex) : (CTelemetryHistoricalReportInfo *)NULL);
}

CTelemetryHistoricalReportInfo *CTelemetryHistoricalReports::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryHistoricalReportInfo *)CMutexArray::GetAt(nIndex) : (CTelemetryHistoricalReportInfo *)NULL);
}

VOID CTelemetryHistoricalReports::RemoveAll()
{
	INT  nReport;
	INT  nReports;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	for (nReport = 0, nReports = (INT)GetSize(); nReport < nReports; nReport++)
	{
		if ((pHistoricalReportInfo = GetAt(nReport))) delete pHistoricalReportInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CTelemetryHistoricalReports::Copy(CONST CTelemetryHistoricalReports *pHistoricalReports)
{
	INT  nReport;
	INT  nReports;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	for (nReport = 0, nReports = (INT)pHistoricalReports->GetSize(), RemoveAll(); nReport < nReports; nReport++)
	{
		if ((pHistoricalReportInfo = new CTelemetryHistoricalReportInfo))
		{
			pHistoricalReportInfo->Copy(pHistoricalReports->GetAt(nReport));
			InsertAt(nReport, pHistoricalReportInfo, 1);
			continue;
		}
		break;
	}
	return((nReport == nReports) ? TRUE : FALSE);
}

BOOL CTelemetryHistoricalReports::Compare(CONST CTelemetryHistoricalReports *pHistoricalReports) CONST
{
	INT  nReport;
	INT  nReports;

	for (nReport = 0, nReports = (pHistoricalReports->GetSize() == GetSize()) ? (INT)GetSize() : -1; nReport < nReports; nReport++)
	{
		if (!pHistoricalReports->GetAt(nReport)->Compare(GetAt(nReport))) break;
		continue;
	}
	return((nReport == nReports) ? TRUE : FALSE);
}

BOOL CTelemetryHistoricalReports::Map(CByteArray &nInfo) CONST
{
	INT  nReport;
	INT  nReports;
	CByteArray  nReportData;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	for (nReport = 0, nReports = (INT)GetSize(), nInfo.RemoveAll(); nReport < nReports; nReport++)
	{
		if ((pHistoricalReportInfo = GetAt(nReport)) && pHistoricalReportInfo->Map(nReportData) && nInfo.Append(nReportData) >= 0) continue;
		break;
	}
	return((nReport == nReports) ? TRUE : FALSE);
}

BOOL CTelemetryHistoricalReports::Unmap(CONST CByteArray &nInfo)
{
	INT  cbReport;
	INT  cbReports;
	CByteArray  nReportData;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	for (cbReports = 0, RemoveAll(); cbReports < nInfo.GetSize(); cbReports += cbReport)
	{
		for (CopyMemory(&cbReport, nInfo.GetData() + cbReports, sizeof(cbReport)), nReportData.SetSize(max(min(cbReport, nInfo.GetSize() - cbReports), 0)); nReportData.GetSize() >= 0; )
		{
			CopyMemory(nReportData.GetData(), nInfo.GetData() + cbReports, nReportData.GetSize());
			break;
		}
		if ((pHistoricalReportInfo = new CTelemetryHistoricalReportInfo))
		{
			if (pHistoricalReportInfo->Unmap(nReportData))
			{
				InsertAt(GetSize(), pHistoricalReportInfo, 1);
				continue;
			}
			delete pHistoricalReportInfo;
		}
		break;
	}
	if ((pHistoricalReportInfo = (!nInfo.GetSize()) ? new CTelemetryHistoricalReportInfo : (CTelemetryHistoricalReportInfo *)NULL))
	{
		for (pHistoricalReportInfo->SetName(STRING(IDS_TELEMETRYREPORTS_DEFAULT_NAME)); Add(pHistoricalReportInfo) >= 0; ) return TRUE;
		delete pHistoricalReportInfo;
		return FALSE;
	}
	return((cbReports == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTelemetryHistoricalReports::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pHistoricalReportInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pHistoricalReportInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pHistoricalReportInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pHistoricalReportInfo->GetName() == pszName) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsFileTriggersThread thread

IMPLEMENT_DYNCREATE(CTelemetryReportsFileTriggersThread, CThread)

CTelemetryReportsFileTriggersThread::CTelemetryReportsFileTriggersThread() : CThread()
{
	return;
}

CTelemetryReportsFileTriggersThread::~CTelemetryReportsFileTriggersThread()
{
	Stop(m_szName);
}

BOOL CTelemetryReportsFileTriggersThread::Start(LPCTSTR pszName, CONST CTelemetryReportFileTriggers &pTriggers)
{
	INT  nTrigger;
	INT  nTriggers;
	HANDLE  hEvent;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo;

	for (nTrigger = 0, nTriggers = (!(m_szName = pszName).IsEmpty() && m_pTriggers.Copy(&pTriggers)) ? (INT)m_pTriggers.GetSize() : -1; nTrigger < nTriggers; nTrigger++)
	{
		if ((hEvent = ((pTriggerInfo = m_pTriggers.GetAt(nTrigger))) ? FindFirstChangeNotification(pTriggerInfo->GetDirectory(), FALSE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE) : (HANDLE)NULL))
		{
			m_pEvents.InsertAt(nTrigger, hEvent, 1);
			continue;
		}
		break;
	}
	if ((hEvent = (nTrigger == nTriggers) ? CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL) : (HANDLE)NULL))
	{
		if (CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL, TRUE))
		{
			m_pEvents.InsertAt(0, hEvent, 1);
			ResumeThread();
			return TRUE;
		}
		CloseHandle(hEvent);
	}
	for (; nTrigger > 0; nTrigger--)
	{
		if ((hEvent = (HANDLE)m_pEvents.GetAt(nTrigger - 1)))
		{
			FindCloseChangeNotification(hEvent);
			continue;
		}
	}
	m_pEvents.RemoveAll();
	return FALSE;
}

BOOL CTelemetryReportsFileTriggersThread::Stop(LPCTSTR pszName)
{
	INT  nTrigger;
	INT  nTriggers;
	HANDLE  hEvent;

	for (nTrigger = 0, nTriggers = (m_szName == pszName && DestroyThread() >= 0) ? (INT)m_pEvents.GetSize() : -1; nTrigger < nTriggers; nTrigger++)
	{
		if ((hEvent = m_pEvents.GetAt(nTrigger)))
		{
			if (nTrigger == 0)
			{
				CloseHandle(hEvent);
				continue;
			}
			FindCloseChangeNotification(hEvent);
		}
	}
	if (nTrigger == nTriggers)
	{
		m_pEvents.RemoveAll();
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportsFileTriggersThread::Update()
{
	HANDLE  hEvent;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((hEvent = (m_pEvents.GetSize() > 0) ? (HANDLE)m_pEvents.GetAt(0) : (HANDLE)NULL)) ? SetEvent(hEvent) : FALSE);
}
BOOL CTelemetryReportsFileTriggersThread::Update(LPCTSTR pszName, CONST CTelemetryReportFileTriggers &pTriggers)
{
	INT  nIndex;
	INT  nTrigger;
	INT  nTriggers;
	HANDLE  hEvent;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_szName.Compare(pszName))
	{
		for (nTrigger = 0, nTriggers = (!m_pTriggers.Compare(&pTriggers)) ? (INT)m_pTriggers.GetSize() : -1; nTrigger < nTriggers; nTrigger++)
		{
			if ((pTriggerInfo[0] = m_pTriggers.GetAt(nTrigger)) != (CTelemetryReportFileTriggerInfo *)NULL)
			{
				if ((pTriggerInfo[1] = pTriggers.GetAt(pTriggers.Find(pTriggerInfo[0]->GetDirectory()))))
				{
					pTriggerInfo[0]->Copy(pTriggerInfo[1]);
					continue;
				}
				FindCloseChangeNotification(m_pEvents.GetAt(nTrigger + 1));
				m_pEvents.RemoveAt(nTrigger + 1);
				m_pTriggers.RemoveAt(nTrigger);
				delete pTriggerInfo[0];
				nTriggers--;
				nTrigger--;
			}
		}
		for (nTrigger = 0, nTriggers = (nTriggers >= 0) ? (INT)pTriggers.GetSize() : -1; nTrigger < nTriggers; nTrigger++)
		{
			if ((pTriggerInfo[0] = pTriggers.GetAt(nTrigger)) != (CTelemetryReportFileTriggerInfo *)NULL)
			{
				if (m_pTriggers.Find(pTriggerInfo[0]->GetDirectory()) < 0)
				{
					if ((pTriggerInfo[1] = new CTelemetryReportFileTriggerInfo))
					{
						pTriggerInfo[1]->Copy(pTriggerInfo[0]);
						if ((nIndex = m_pTriggers.Add(pTriggerInfo[1])) >= 0)
						{
							if ((hEvent = FindFirstChangeNotification(pTriggerInfo[1]->GetDirectory(), FALSE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE)))
							{
								m_pEvents.InsertAt(nIndex + 1, hEvent, 1);
								continue;
							}
							m_pTriggers.RemoveAt(nIndex);
						}
						delete pTriggerInfo[1];
					}
				}
			}
		}
		if (m_pTriggers.Compare(&pTriggers))
		{
			if (nTriggers >= 0) Update();
			return TRUE;
		}
		Update();
	}
	return FALSE;
}

int CTelemetryReportsFileTriggersThread::Run()
{
	INT  nTrigger;
	INT  nTriggers;
	DWORD  dwResult;
	CString  szMessage;
	CPtrArray  pEvents;
	CTelemetryReportFileTriggerInfo  *pTriggerInfo;

	do
	{
		for (dwResult = (pEvents.GetSize() > 0) ? dwResult : -1; Lock(); )
		{
			if (dwResult == WAIT_OBJECT_0 + 1 || dwResult == (DWORD)-1)
			{
				for (nTrigger = 0, nTriggers = (INT)m_pTriggers.GetSize(), pEvents.Copy(m_pEvents); nTrigger < nTriggers; nTrigger++)
				{
					if ((pTriggerInfo = m_pTriggers.GetAt(nTrigger)))
					{
						CollectTriggerFiles(pTriggerInfo);
						continue;
					}
				}
			}
			if (dwResult > WAIT_OBJECT_0 + 1 && dwResult <= WAIT_OBJECT_0 + pEvents.GetSize())
			{
				if ((pTriggerInfo = m_pTriggers.GetAt(dwResult - WAIT_OBJECT_0 - 1 - 1)) && IsTriggeredByFiles(pTriggerInfo))
				{
					for (szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_FILETRIGGERS_FAILURE), (LPCTSTR)pTriggerInfo->GetDirectory(), (LPCTSTR)m_szName); !GetTelemetryReportsService()->Update(m_szName); )
					{
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
						break;
					}
				}
				FindNextChangeNotification(pEvents.GetAt(dwResult - WAIT_OBJECT_0 - 1));
			}
			Unlock();
			break;
		}
	} while ((dwResult = Wait((LPHANDLE)pEvents.GetData(), (DWORD)pEvents.GetSize(), FALSE, INFINITE, FALSE)) != WAIT_OBJECT_0  &&  dwResult != WAIT_FAILED);
	return 0;
}

BOOL CTelemetryReportsFileTriggersThread::CollectTriggerFiles(CTelemetryReportFileTriggerInfo *pTriggerInfo) CONST
{
	INT  nFile;
	INT  nFiles;
	CString  szFileListing[2];
	CUIntArray  nFileAttributes;
	CStringArray  szFilteredFiles;

	if (pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_ALLFILES)
	{
		CollectTriggerFiles(pTriggerInfo->GetDirectory(), EMPTYSTRING, szFileListing[0], szFileListing[1]);
		pTriggerInfo->SetFileListing(szFileListing[0], szFileListing[1]);
		return TRUE;
	}
	if (pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_SELECTEDFILES)
	{
		for (nFile = 0, nFiles = pTriggerInfo->GetFilteredFiles(szFilteredFiles, nFileAttributes); nFile < nFiles; nFile++)
		{
			if (CollectTriggerFiles(pTriggerInfo->GetDirectory(), szFilteredFiles.GetAt(nFile), szFileListing[0], szFileListing[1]) || szFileListing[0].IsEmpty())
			{
				pTriggerInfo->SetFileListing(nFile, szFileListing[0], szFileListing[1]);
				continue;
			}
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTelemetryReportsFileTriggersThread::CollectTriggerFiles(LPCTSTR pszDirectory, LPCTSTR pszFilter, CString &szFiles, CString &szTimes) CONST
{
	BOOL  bFound;
	CString  szFilter;
	CString  szDirectory;
	FILETIME  sFileTime;
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;

	for (szDirectory = pszDirectory, szFilter = pszFilter, szDirectory = (szDirectory.GetLength() > 0 && szDirectory.GetAt(szDirectory.GetLength() - 1) == cDrives.GetPathDelimiter() && (szFilter.IsEmpty() || szFilter.GetAt(0) == cDrives.GetPathDelimiter())) ? szDirectory.Left(szDirectory.GetLength() - 1) : (((szDirectory.IsEmpty() || szDirectory.GetAt(szDirectory.GetLength() - 1) != cDrives.GetPathDelimiter()) && !szFilter.IsEmpty() && szFilter.GetAt(0) != cDrives.GetPathDelimiter()) ? (szDirectory + cDrives.GetPathDelimiter()) : szDirectory), szFiles.Empty(), szTimes.Empty(); (!lstrlen(pszFilter) && cFileFind.FindFile(szDirectory + STRING(IDS_FILENAME_ALL))) || (lstrlen(pszFilter) > 0 && cFileFind.FindFile(szDirectory + pszFilter)); )
	{
		for (bFound = cFileFind.FindNextFile(); TRUE; bFound = cFileFind.FindNextFile())
		{
			for (; !cFileFind.IsDots() && !cFileFind.IsDirectory() && cFileFind.GetLastWriteTime(&sFileTime); )
			{
				szFiles += (!szFiles.IsEmpty()) ? (TAB + cFileFind.GetFilePath()) : cFileFind.GetFilePath();
				szTimes += (!szTimes.IsEmpty()) ? (TAB + CTimeTag(sFileTime).FormatGmt()) : CTimeTag(sFileTime).FormatGmt();
				break;
			}
			if (!bFound) break;
		}
		cFileFind.Close();
		break;
	}
	return !szFiles.IsEmpty();
}

BOOL CTelemetryReportsFileTriggersThread::IsTriggeredByFiles(CTelemetryReportFileTriggerInfo *pTriggerInfo) CONST
{
	INT  nFile;
	INT  nFiles;
	BOOL  bTrigger;
	CString  szDirectory;
	CString  szFileListing[2][2];
	CUIntArray  nFileAttributes;
	CStringArray  szFilteredFiles;
	CLogicalDrives  cDrives;

	if ((pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKMODE_DISABLED) != TELEMETRYREPORT_FILETRIGGER_TRACKMODE_DISABLED)
	{
		if ((pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_ALLFILES) & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_ALLFILES)
		{
			for (CollectTriggerFiles(pTriggerInfo->GetDirectory(), EMPTYSTRING, szFileListing[0][0], szFileListing[0][1]), bTrigger = FALSE; pTriggerInfo->GetFileListing(szFileListing[1][0], szFileListing[1][1]); )
			{
				bTrigger = ((pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKMODE_NEWFILES) && szFileListing[0][0].CompareNoCase(szFileListing[1][0]) && IsTriggeredByFiles(szFileListing[0][0], szFileListing[1][0], TRUE)) || ((pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKMODE_DELETEDFILES) && szFileListing[0][0].CompareNoCase(szFileListing[1][0]) && IsTriggeredByFiles(szFileListing[0][0], szFileListing[1][0], FALSE)) || ((pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKMODE_UPDATEDFILES) && szFileListing[0][1].GetLength() == szFileListing[1][1].GetLength() && szFileListing[0][1].CompareNoCase(szFileListing[1][1]));
				pTriggerInfo->SetFileListing(szFileListing[0][0], szFileListing[0][1]);
				break;
			}
			return bTrigger;
		}
		if (pTriggerInfo->GetAttributes() & TELEMETRYREPORT_FILETRIGGER_TRACKFILTER_SELECTEDFILES)
		{
			for (nFile = 0, nFiles = pTriggerInfo->GetFilteredFiles(szFilteredFiles, nFileAttributes), bTrigger = FALSE; nFile < nFiles; nFile++)
			{
				for (CollectTriggerFiles(pTriggerInfo->GetDirectory(), szFilteredFiles.GetAt(nFile), szFileListing[0][0], szFileListing[0][1]); pTriggerInfo->GetFileListing(nFile, szFileListing[1][0], szFileListing[1][1]); )
				{
					bTrigger = (bTrigger || ((nFileAttributes.GetAt(nFile) & TELEMETRYREPORT_FILETRIGGER_TRACKMODE_NEWFILES) && szFileListing[0][0].CompareNoCase(szFileListing[1][0]) && IsTriggeredByFiles(szFileListing[0][0], szFileListing[1][0], TRUE)) || ((nFileAttributes.GetAt(nFile) & TELEMETRYREPORT_FILETRIGGER_TRACKMODE_DELETEDFILES) && szFileListing[0][0].CompareNoCase(szFileListing[1][0]) && IsTriggeredByFiles(szFileListing[0][0], szFileListing[1][0], FALSE)) || ((nFileAttributes.GetAt(nFile) & TELEMETRYREPORT_FILETRIGGER_TRACKMODE_UPDATEDFILES) && szFileListing[0][1].GetLength() == szFileListing[1][1].GetLength() && szFileListing[0][1].CompareNoCase(szFileListing[1][1])));
					pTriggerInfo->SetFileListing(nFile, szFileListing[0][0], szFileListing[0][1]);
					break;
				}
			}
			return bTrigger;
		}
	}
	return FALSE;
}
BOOL CTelemetryReportsFileTriggersThread::IsTriggeredByFiles(LPCTSTR pszNewFileListing, LPCTSTR pszOldFileListing, BOOL bNewFiles) CONST
{
	INT  nPos[2];
	CString  szFileListings[2];

	for (nPos[0] = 0, szFileListings[0] = (bNewFiles) ? pszNewFileListing : pszOldFileListing, szFileListings[1] = (!bNewFiles) ? pszNewFileListing : pszOldFileListing; nPos[0] < szFileListings[0].GetLength(); nPos[0] += nPos[1] + 1)
	{
		if ((nPos[1] = szFileListings[0].Mid(nPos[0]).Find(TAB)) < 0)
		{
			if (szFileListings[1].Find(szFileListings[0].Mid(nPos[0])) < 0) break;
			if (szFileListings[1].Find(szFileListings[0].Mid(nPos[0]) + TAB) < 0) break;
			nPos[1] = szFileListings[0].Mid(nPos[0]).GetLength();
			continue;
		}
		if (szFileListings[1].Find(szFileListings[0].Mid(nPos[0], nPos[1] + 1)) < 0) break;
	}
	return((nPos[0] < szFileListings[0].GetLength() || (!bNewFiles  &&  szFileListings[0].IsEmpty() && !szFileListings[1].IsEmpty())) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTelemetryReportsFileTriggersThread, CThread)
	//{{AFX_MSG_MAP(CTelemetryReportsFileTriggersThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsFileTriggersThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsFileTriggersThreads

CTelemetryReportsFileTriggersThreads::CTelemetryReportsFileTriggersThreads() : CPtrArray()
{
	return;
}

CTelemetryReportsFileTriggersThreads::~CTelemetryReportsFileTriggersThreads()
{
	RemoveAll();
}

INT CTelemetryReportsFileTriggersThreads::Add(CTelemetryReportsFileTriggersThread *pFileTriggersThread)
{
	INT  nIndex;

	if ((nIndex = FindIndex(*pFileTriggersThread, TRUE)) >= 0) InsertAt(nIndex, pFileTriggersThread, 1);
	return nIndex;
}

INT CTelemetryReportsFileTriggersThreads::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CTelemetryReportsFileTriggersThread *CTelemetryReportsFileTriggersThreads::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportsFileTriggersThread *)CPtrArray::GetAt(nIndex) : (CTelemetryReportsFileTriggersThread *)NULL);
}

CTelemetryReportsFileTriggersThread *CTelemetryReportsFileTriggersThreads::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTelemetryReportsFileTriggersThread *)CPtrArray::GetAt(nIndex) : (CTelemetryReportsFileTriggersThread *)NULL);
}

VOID CTelemetryReportsFileTriggersThreads::RemoveAll()
{
	INT  nThread;
	INT  nThreads;

	for (nThread = 0, nThreads = (INT)GetSize(); nThread < nThreads; nThread++)
	{
		delete GetAt(nThread);
		continue;
	}
	CPtrArray::RemoveAll();
}

INT CTelemetryReportsFileTriggersThreads::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nThread;
	INT  nThreads;

	for (nThread = 0, nThreads = (INT)GetSize(); nThread < nThreads; nThread++)
	{
		if (!lstrcmp(*GetAt(nThread), pszName)) break;
		continue;
	}
	return(((!bInsert  &&  nThread < nThreads) || (bInsert  &&  nThread == nThreads)) ? nThread : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsService

IMPLEMENT_DYNCREATE(CTelemetryReportsService, CThread)

CTelemetryReportsService::CTelemetryReportsService() : CThread()
{
	m_pReports[0] = new CTelemetryReports;
	m_pReports[1] = new CTelemetryReports;
	m_pReports[2] = new CTelemetryReports;
	m_pHistoricalReports = new CTelemetryHistoricalReports;
	m_nReportTimerID = 0;
	m_bExit = FALSE;
}

CTelemetryReportsService::~CTelemetryReportsService()
{
	delete m_pReports[0];
	delete m_pReports[1];
	delete m_pReports[2];
	delete m_pHistoricalReports;
}

BOOL CTelemetryReportsService::Start(CJScriptCodeExecutor *pExecutor)
{
	INT  nReport;
	INT  nReports;
	UINT  nReportID;
	LPWSTR  pszName;
	CTimeKey  tScheduleTime[2];
	CTimeSpan  tScheduleInterval;
	CTelemetryReports  pReports;
	CTelemetryReportInfo  *pReportInfo;
	CByteArray  nJobsInfo[2];
	CProfile  cProfile;

	for (nReport = 0, nReports = (cProfile.GetTelemetryReportJobsInfo(nJobsInfo[0], nJobsInfo[1]) && pReports.Unmap(nJobsInfo[0]) && m_pHistoricalReports->Unmap(nJobsInfo[1])) ? (INT)pReports.GetSize() : -1, m_pReports[1]->RemoveAll(), m_pReports[2]->RemoveAll(), m_nReportIDs.RemoveAll(); nReport < nReports; nReport++)
	{
		if ((pReportInfo = pReports.GetAt(nReport)))
		{
			if ((pReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_SCHEDULED) == 0)
			{
				m_pReports[1]->InsertAt(m_pReports[1]->GetSize(), pReportInfo, 1);
				pReports.RemoveAt(nReport);
				nReports--;
				nReport--;
				continue;
			}
			if ((pszName = new WCHAR[pReportInfo->GetName().GetLength() + 1]))
			{
#ifndef UNICODE
				MultiByteToWideChar(CP_ACP, 0, pReportInfo->GetName(), -1, pszName, pReportInfo->GetName().GetLength() + 1);
#else
				wcscpy_s(pszName, pReportInfo->GetName().GetLength() + 1, pReportInfo->GetName());
#endif
				if ((nReportID = (pReportInfo->GetScheduledPeriod(tScheduleTime[0], tScheduleTime[1], tScheduleInterval)) ? AddJScriptTaskSchedulerTelemetryReport(pszName, tScheduleTime[0].GetTime(), tScheduleInterval.GetTotalSeconds(), tScheduleTime[1].GetTime()) : -1) != (UINT)-1)
				{
					pReports.RemoveAt(nReport);
					delete pReportInfo;
					nReports--;
					nReport--;
				}
				delete[] pszName;
				continue;
			}
		}
		break;
	}
	return((CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL) && pExecutor->Start()) ? (nReport == nReports) : FALSE);
}

BOOL CTelemetryReportsService::Stop(CJScriptCodeExecutor *pExecutor)
{
	INT  nReport;
	INT  nReports;
	CUIntArray  nReportIDs;
	CTelemetryReports  pReports;
	CTelemetryReportInfo  *pReportInfo[2];
	CByteArray  nJobsInfo[2];
	CProfile  cProfile;

	for (nReport = 0, nReports = (DestroyThread() >= 0) ? (INT)m_pReports[2]->GetSize() : -1, m_pTriggerThreads.RemoveAll(), pExecutor->Stop(), pReports.Copy(m_pReports[1]), nReportIDs.Copy(m_nReportIDs); nReport < nReports; nReport++)
	{
		if ((pReportInfo[0] = m_pReports[2]->GetAt(nReport)))
		{
			if ((pReportInfo[1] = new CTelemetryReportInfo))
			{
				pReportInfo[1]->Copy(pReportInfo[0]);
				pReports.InsertAt(pReports.GetSize(), pReportInfo[1], 1);
			}
		}
	}
	for (nReport = 0, nReports = (nReports != -1) ? (INT)nReportIDs.GetSize() : -1; nReport < nReports; nReport++)
	{
		DeleteJScriptTaskSchedulerTelemetryReport(nReportIDs.GetAt(nReport));
		continue;
	}
	return((pReports.GetSize() == m_pReports[1]->GetSize() + nReports  &&  pReports.Map(nJobsInfo[0]) && m_pHistoricalReports->Map(nJobsInfo[1])) ? cProfile.SetTelemetryReportJobsInfo(nJobsInfo[0], nJobsInfo[1]) : FALSE);
}

int CTelemetryReportsService::ExitInstance()
{
	if (m_nReportTimerID != 0)
	{
		KillTimer((HWND)NULL, m_nReportTimerID);
		m_nReportTimerID = 0;
	}
	return CThread::ExitInstance();
}

BOOL CTelemetryReportsService::Update()
{
	return m_bUpdate.SetEvent();
}
BOOL CTelemetryReportsService::Update(LPCTSTR pszReport)
{
	CTelemetryReportInfo  *pReportInfo;

	if (m_pReports[0]->Lock())
	{
		if ((pReportInfo = m_pReports[0]->GetAt(m_pReports[0]->Find(pszReport))))
		{
			if (DoUpdateReport(pReportInfo))
			{
				m_pReports[0]->Unlock();
				return TRUE;
			}
		}
		m_pReports[0]->Unlock();
	}
	return FALSE;
}
BOOL CTelemetryReportsService::Update(CONST CTelemetryReportInfo *pReport)
{
	CTelemetryReportInfo  *pReportInfo;

	if (m_pReports[1]->Lock())
	{
		if ((pReportInfo = new CTelemetryReportInfo))
		{
			for (pReportInfo->Copy(pReport); TRUE; )
			{
				m_pReports[1]->InsertAt(m_pReports[1]->GetSize(), pReportInfo, 1);
				break;
			}
			m_pReports[1]->Unlock();
			return Update();
		}
		m_pReports[1]->Unlock();
	}
	return FALSE;
}
BOOL CTelemetryReportsService::Update(CONST CTelemetryHistoricalReportInfo *pReport)
{
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	if (m_pHistoricalReports->Lock())
	{
		if ((pHistoricalReportInfo = new CTelemetryHistoricalReportInfo))
		{
			pHistoricalReportInfo->Copy(pReport);
			m_pHistoricalReports->InsertAt(m_pHistoricalReports->GetSize(), pHistoricalReportInfo, 1);
			m_pHistoricalReports->Unlock();
			return Update();
		}
		m_pHistoricalReports->Unlock();
	}
	return FALSE;
}
BOOL CTelemetryReportsService::Update(CONST CTelemetryReports &pReports)
{
	INT  nIndex;
	INT  nReport;
	INT  nReports;
	CTimeKey  tTime;
	CTimeKey  tMailTime[2];
	CTimeKey  tExecutionTime;
	CTimeKey  tScheduleTime[2][2];
	CTimeSpan  tScheduleInterval[2];
	CTelemetryReportInfo  *pReportInfo[2];
	CTelemetryReportFileTriggers  pTriggers;
	CTelemetryReportsFileTriggersThread  *pReportTriggerThread;

	if (m_pReports[0]->Lock())
	{
		for (nReport = 0, nReports = (INT)pReports.GetSize(); nReport < nReports; nReport++)
		{
			if ((pReportInfo[0] = pReports.GetAt(nReport)))
			{
				if ((pReportInfo[1] = m_pReports[0]->GetAt(m_pReports[0]->Find(pReportInfo[0]->GetName()))))
				{
					for (; pReportInfo[0]->GetScheduledPeriod(tScheduleTime[0][0], tScheduleTime[0][1], tScheduleInterval[0]) && (!pReportInfo[1]->GetScheduledPeriod(tScheduleTime[1][0], tScheduleTime[1][1], tScheduleInterval[1]) || tScheduleTime[0][0] != tScheduleTime[1][0] || tScheduleTime[0][1] != tScheduleTime[1][1] || tScheduleInterval[0] != tScheduleInterval[1]); )
					{
						if (tScheduleTime[0][0] < tTime  &&  tScheduleTime[0][1] == 0 && tScheduleInterval[0] == 0)
						{
							pReportInfo[1]->SetLastExecutionTime(tScheduleTime[0][0]);
							break;
						}
						if (tScheduleTime[0][0] > 0 && tScheduleTime[0][1] == 0 && tScheduleInterval[0] == SECONDSPERDAY)
						{
							pReportInfo[1]->SetLastExecutionTime((tScheduleTime[0][0].GetTime() % SECONDSPERDAY >= tTime.GetTime() % SECONDSPERDAY) ? (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY - 1) + tScheduleTime[0][0].GetTime() % SECONDSPERDAY) : (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tScheduleTime[0][0].GetTime() % SECONDSPERDAY));
							break;
						}
						if (tScheduleTime[0][0] < tTime  &&  tScheduleInterval[0] > 0)
						{
							pReportInfo[1]->SetLastExecutionTime(min(tScheduleTime[0][0].GetTime() + tScheduleInterval[0].GetTotalSeconds()*((tTime.GetTime() - tScheduleTime[0][0].GetTime()) / tScheduleInterval[0].GetTotalSeconds()), tScheduleTime[0][1].GetTime()));
							break;
						}
						pReportInfo[1]->SetLastExecutionTime(0);
						break;
					}
					for (; !pReportInfo[0]->GetScheduledPeriod(tScheduleTime[0][0], tScheduleTime[0][1], tScheduleInterval[0]); )
					{
						pReportInfo[1]->SetLastExecutionTime(0);
						break;
					}
					for (tMailTime[0] = (((pReportInfo[0]->GetOptions() & (TELEMETRYREPORTINFO_OPTION_MAILDAILY | TELEMETRYREPORTINFO_OPTION_MAILWEEKLY)) == (pReportInfo[1]->GetOptions() & (TELEMETRYREPORTINFO_OPTION_MAILDAILY | TELEMETRYREPORTINFO_OPTION_MAILWEEKLY))) && pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY == pReportInfo[1]->GetMailTime().GetTime() % SECONDSPERDAY && pReportInfo[0]->GetMailTimeInterval() == pReportInfo[1]->GetMailTimeInterval()) ? pReportInfo[1]->GetLastMailTime() : CTimeKey(0), tExecutionTime = pReportInfo[1]->GetLastExecutionTime(), pReportInfo[1]->Copy(pReportInfo[0]); tMailTime[0] >= 0; )
					{
						pReportInfo[1]->SetLastExecutionTime(tExecutionTime);
						pReportInfo[1]->SetLastMailTime(tMailTime[0]);
						break;
					}
					if (pReportInfo[0]->GetFileTriggers(pTriggers) > 0)
					{
						for (pReportInfo[1]->SetFileTriggers(pTriggers); (pReportTriggerThread = m_pTriggerThreads.GetAt((nIndex = m_pTriggerThreads.Find(pReportInfo[1]->GetName())))); )
						{
							pReportTriggerThread->Update(pReportInfo[1]->GetName(), pTriggers);
							break;
						}
						if ((pReportTriggerThread = (nIndex < 0) ? new CTelemetryReportsFileTriggersThread : (CTelemetryReportsFileTriggersThread *)NULL))
						{
							if (pReportTriggerThread->Start(pReportInfo[1]->GetName(), pTriggers) && m_pTriggerThreads.Add(pReportTriggerThread) >= 0) continue;
							delete pReportTriggerThread;
						}
					}
					else
					{
						if ((pReportTriggerThread = m_pTriggerThreads.GetAt((nIndex = m_pTriggerThreads.Find(pReportInfo[1]->GetName())))))
						{
							m_pTriggerThreads.RemoveAt(nIndex);
							delete pReportTriggerThread;
						}
					}
					continue;
				}
				if ((pReportInfo[1] = new CTelemetryReportInfo))
				{
					for (pReportInfo[1]->Copy(pReportInfo[0]); pReportInfo[1]->GetScheduledPeriod(tScheduleTime[1][0], tScheduleTime[1][1], tScheduleInterval[1]); )
					{
						if (tScheduleTime[1][0] < tTime  &&  tScheduleTime[1][1] == 0 && tScheduleInterval[1] == 0)
						{
							pReportInfo[1]->SetLastExecutionTime(tScheduleTime[1][0]);
							break;
						}
						if (tScheduleTime[1][0] > 0 && tScheduleTime[1][1] == 0 && tScheduleInterval[1] == SECONDSPERDAY)
						{
							pReportInfo[1]->SetLastExecutionTime((tScheduleTime[1][0].GetTime() % SECONDSPERDAY >= tTime.GetTime() % SECONDSPERDAY) ? (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY - 1) + tScheduleTime[1][0].GetTime() % SECONDSPERDAY) : (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tScheduleTime[1][0].GetTime() % SECONDSPERDAY));
							break;
						}
						if (tScheduleTime[1][0] < tTime  &&  tScheduleInterval[1] > 0)
						{
							pReportInfo[1]->SetLastExecutionTime(min(tScheduleTime[1][0].GetTime() + tScheduleInterval[1].GetTotalSeconds()*((tTime.GetTime() - tScheduleTime[1][0].GetTime()) / tScheduleInterval[1].GetTotalSeconds()), tScheduleTime[1][1].GetTime()));
							break;
						}
						pReportInfo[1]->SetLastExecutionTime(0);
						break;
					}
					if (m_pReports[0]->Add(pReportInfo[1]) >= 0)
					{
						if (pReportInfo[1]->GetFileTriggers(pTriggers) > 0)
						{
							if ((pReportTriggerThread = new CTelemetryReportsFileTriggersThread))
							{
								if (pReportTriggerThread->Start(pReportInfo[1]->GetName(), pTriggers) && m_pTriggerThreads.Add(pReportTriggerThread) >= 0) continue;
								delete pReportTriggerThread;
							}
						}
						continue;
					}
					delete pReportInfo[1];
				}
			}
		}
		for (nReport = 0, nReports = (INT)m_pReports[0]->GetSize(); nReport < nReports; nReport++)
		{
			if ((pReportInfo[0] = m_pReports[0]->GetAt(nReport)) && pReports.Find(pReportInfo[0]->GetName()) < 0)
			{
				if ((pReportTriggerThread = m_pTriggerThreads.GetAt((nIndex = m_pTriggerThreads.Find(pReportInfo[0]->GetName())))))
				{
					m_pTriggerThreads.RemoveAt(nIndex);
					delete pReportTriggerThread;
				}
				m_pReports[0]->RemoveAt(nReport);
				delete pReportInfo[0];
				nReports--;
				nReport--;
			}
		}
		for (nReport = 0, nReports = (INT)m_pReports[0]->GetSize(); nReport < nReports; nReport++)
		{
			if ((pReportInfo[0] = m_pReports[0]->GetAt(nReport)) && (!pReportInfo[0]->GetLastMailTime().GetTime() || pReportInfo[0]->GetLastMailTime() > tMailTime[1]))
			{
				if (pReportInfo[0]->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILDAILY)
				{
					if (pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds() > SECONDSPERDAY)
					{
						pReportInfo[0]->SetLastMailTime(tMailTime[1]);
						continue;
					}
					if (pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY <= tMailTime[1].GetTime() % SECONDSPERDAY)
					{
						pReportInfo[0]->SetLastMailTime(tMailTime[1]);
						continue;
					}
					pReportInfo[0]->SetLastMailTime(tMailTime[1].GetTime() - SECONDSPERDAY);
					continue;
				}
				if (pReportInfo[0]->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILWEEKLY)
				{
					if ((pReportInfo[0]->GetMailTime().GetDayOfWeek() == tMailTime[1].GetDayOfWeek() && pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY <= tMailTime[1].GetTime() % SECONDSPERDAY) || (pReportInfo[0]->GetMailTime().GetDayOfWeek() + Thursday) % DAYSPERWEEK < (tMailTime[1].GetDayOfWeek() + Thursday) % DAYSPERWEEK)
					{
						pReportInfo[0]->SetLastMailTime(tMailTime[1]);
						continue;
					}
					pReportInfo[0]->SetLastMailTime(tMailTime[1].GetTime() - SECONDSPERWEEK);
					continue;
				}
			}
		}
		if (m_pReports[0]->GetSize() == pReports.GetSize())
		{
			m_pReports[0]->Unlock();
			return Update();
		}
		m_pReports[0]->Unlock();
	}
	return FALSE;
}
BOOL CTelemetryReportsService::Update(CONST CTelemetryReports &pReports, CONST CUIntArray &nIDs, CONST CStringArray &szErrors)
{
	INT  nReport;
	INT  nReports;
	INT  nReportID;
	INT  nReportIDs;
	CTimeKey  tTime;
	CTimeKey  tExecutionTime;
	CTimeKey  tScheduleTime[2][2];
	CTimeSpan  tScheduleInterval[2];
	CTelemetryReportInfo  *pReportInfo[2];

	if (m_pReports[2]->Lock())
	{
		for (nReport = 0, nReports = (INT)pReports.GetSize(), m_szErrors.Append(szErrors); nReport < nReports; nReport++)
		{
			if ((pReportInfo[0] = pReports.GetAt(nReport)) && pReportInfo[0]->GetScheduledPeriod(tScheduleTime[0][0], tScheduleTime[0][1], tScheduleInterval[0]))
			{
				if (tScheduleTime[0][0] < tTime && ((tScheduleInterval[0] == 0 && tScheduleTime[0][1] == 0) || tScheduleTime[0][1] < tTime))
				{
					DeleteJScriptTaskSchedulerTelemetryReport(nIDs.GetAt(nReport));
					continue;
				}
				for (nReportID = 0, nReportIDs = (INT)m_nReportIDs.GetSize(); nReportID < nReportIDs; nReportID++)
				{
					if (m_nReportIDs.GetAt(nReportID) == nIDs.GetAt(nReport)) break;
					continue;
				}
				if ((pReportInfo[1] = m_pReports[2]->GetAt(nReportID)))
				{
					for (; !pReportInfo[1]->GetScheduledPeriod(tScheduleTime[1][0], tScheduleTime[1][1], tScheduleInterval[1]) || tScheduleTime[0][0] != tScheduleTime[1][0] || tScheduleTime[0][1] != tScheduleTime[1][1] || tScheduleInterval[0] != tScheduleInterval[1]; )
					{
						if (tScheduleTime[0][0] < tTime  &&  tScheduleTime[0][1] == 0 && tScheduleInterval[0] == 0)
						{
							pReportInfo[1]->SetLastExecutionTime(tScheduleTime[0][0]);
							break;
						}
						if (tScheduleTime[0][0] > 0 && tScheduleTime[0][1] == 0 && tScheduleInterval[0] == SECONDSPERDAY)
						{
							pReportInfo[1]->SetLastExecutionTime((tScheduleTime[0][0].GetTime() % SECONDSPERDAY >= tTime.GetTime() % SECONDSPERDAY) ? (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY - 1) + tScheduleTime[0][0].GetTime() % SECONDSPERDAY) : (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tScheduleTime[0][0].GetTime() % SECONDSPERDAY));
							break;
						}
						if (tScheduleTime[0][0] < tTime  &&  tScheduleInterval[0] > 0)
						{
							pReportInfo[1]->SetLastExecutionTime(min(tScheduleTime[0][0].GetTime() + tScheduleInterval[0].GetTotalSeconds()*((tTime.GetTime() - tScheduleTime[0][0].GetTime()) / tScheduleInterval[0].GetTotalSeconds()), tScheduleTime[0][1].GetTime()));
							break;
						}
						pReportInfo[1]->SetLastExecutionTime(0);
						break;
					}
					for (; !pReportInfo[0]->GetScheduledPeriod(tScheduleTime[0][0], tScheduleTime[0][1], tScheduleInterval[0]); )
					{
						pReportInfo[1]->SetLastExecutionTime(0);
						break;
					}
					for (tExecutionTime = pReportInfo[1]->GetLastExecutionTime(), pReportInfo[1]->Copy(pReportInfo[0]); TRUE; )
					{
						pReportInfo[1]->SetLastExecutionTime(tExecutionTime);
						break;
					}
					continue;
				}
				if ((pReportInfo[1] = new CTelemetryReportInfo))
				{
					for (pReportInfo[1]->Copy(pReportInfo[0]), pReportInfo[1]->SetStatus(TELEMETRYREPORTINFO_STATUS_QUEUED); pReportInfo[1]->GetScheduledPeriod(tScheduleTime[1][0], tScheduleTime[1][1], tScheduleInterval[1]); )
					{
						if (tScheduleTime[1][0] < tTime  &&  tScheduleTime[1][1] == 0 && tScheduleInterval[1] == 0)
						{
							pReportInfo[1]->SetLastExecutionTime(tScheduleTime[1][0]);
							break;
						}
						if (tScheduleTime[1][0] > 0 && tScheduleTime[1][1] == 0 && tScheduleInterval[1] == SECONDSPERDAY)
						{
							pReportInfo[1]->SetLastExecutionTime((tScheduleTime[1][0].GetTime() % SECONDSPERDAY >= tTime.GetTime() % SECONDSPERDAY) ? (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY - 1) + tScheduleTime[1][0].GetTime() % SECONDSPERDAY) : (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + tScheduleTime[1][0].GetTime() % SECONDSPERDAY));
							break;
						}
						if (tScheduleTime[1][0] < tTime  &&  tScheduleInterval[1] > 0)
						{
							pReportInfo[1]->SetLastExecutionTime(min(tScheduleTime[1][0].GetTime() + tScheduleInterval[1].GetTotalSeconds()*((tTime.GetTime() - tScheduleTime[1][0].GetTime()) / tScheduleInterval[1].GetTotalSeconds()), tScheduleTime[1][1].GetTime()));
							break;
						}
						pReportInfo[1]->SetLastExecutionTime(0);
						break;
					}
					m_pReports[2]->InsertAt(m_pReports[2]->GetSize(), pReportInfo[1], 1);
					m_nReportIDs.InsertAt(m_nReportIDs.GetSize(), nIDs.GetAt(nReport));
					continue;
				}
			}
		}
		for (nReport = 0, nReports = (INT)m_pReports[2]->GetSize(); nReport < nReports; nReport++)
		{
			if ((pReportInfo[0] = m_pReports[2]->GetAt(nReport)) != (CTelemetryReportInfo *)NULL)
			{
				for (nReportID = 0, nReportIDs = (INT)nIDs.GetSize(); nReportID < nReportIDs; nReportID++)
				{
					if (m_nReportIDs.GetAt(nReport) == nIDs.GetAt(nReportID)) break;
					continue;
				}
				if (nReportID == nReportIDs)
				{
					m_pReports[2]->RemoveAt(nReport);
					m_nReportIDs.RemoveAt(nReport);
					delete pReportInfo[0];
					nReports--;
					nReport--;
				}
			}
		}
		if (m_pReports[2]->GetSize() == pReports.GetSize())
		{
			m_pReports[2]->Unlock();
			return Update();
		}
		m_pReports[2]->Unlock();
		Update();
	}
	return FALSE;
}

BOOL CTelemetryReportsService::Refresh(CTelemetryReports &pReports)
{
	INT  nReport;
	INT  nReports;
	CTimeKey  tScheduleTime[2];
	CTimeSpan  tScheduleInterval;
	CTelemetryReportInfo  *pReportInfo[2];

	if (m_pReports[0]->Lock())
	{
		for (nReport = 0, nReports = (INT)pReports.GetSize(); nReport < nReports; nReport++)
		{
			if ((pReportInfo[0] = pReports.GetAt(nReport)))
			{
				if ((pReportInfo[1] = m_pReports[0]->GetAt(m_pReports[0]->Find(pReportInfo[0]->GetName()))))
				{
					for (pReportInfo[0]->SetScheduledPeriod(0, 0, 0); pReportInfo[1]->GetScheduledPeriod(tScheduleTime[0], tScheduleTime[1], tScheduleInterval); )
					{
						pReportInfo[0]->SetScheduledPeriod(tScheduleTime[0], tScheduleTime[1], tScheduleInterval);
						break;
					}
					pReportInfo[0]->SetLastExecutionTime(pReportInfo[1]->GetLastExecutionTime());
					pReportInfo[0]->SetLastMailTime(pReportInfo[1]->GetLastMailTime());
				}
			}
		}
		m_pReports[0]->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CTelemetryReportsService::EnumReports(CTelemetryReports &pReports) CONST
{
	INT  nReport[4];
	INT  nReports[4];
	CTimeKey  tTime;
	CTimeKey  tScheduleTime[2];
	CTimeSpan  tScheduleInterval;
	CByteArray  nHistoricalReportData[2];
	CTelemetryReportInfo  *pReportInfo[2];
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	if (m_pReports[0]->Lock())
	{
		if (m_pReports[1]->Lock())
		{
			if (m_pReports[2]->Lock())
			{
				if (m_pHistoricalReports->Lock())
				{
					for (nReport[0] = 0, nReports[0] = (INT)m_pReports[0]->GetSize(), pReports.Copy(m_pReports[1]); nReport[0] < nReports[0]; nReport[0]++)
					{
						if ((pReportInfo[0] = m_pReports[0]->GetAt(nReport[0])))
						{
							if (pReportInfo[0]->GetScheduledPeriod(tScheduleTime[0], tScheduleTime[1], tScheduleInterval))
							{
								if ((tTime >= tScheduleTime[0] && (tTime <= tScheduleTime[1] || (tScheduleTime[1] == 0 && tScheduleInterval > 0))) || tTime < tScheduleTime[0])
								{
									if ((pReportInfo[1] = new CTelemetryReportInfo))
									{
										pReportInfo[1]->Copy(pReportInfo[0]);
										pReports.InsertAt(pReports.GetSize(), pReportInfo[1], 1);
										continue;
									}
									break;
								}
							}
							continue;
						}
						break;
					}
					for (nReport[1] = 0, nReports[1] = (INT)m_pReports[2]->GetSize(); nReport[1] < nReports[1]; nReport[1]++)
					{
						if ((pReportInfo[0] = m_pReports[2]->GetAt(nReport[1])))
						{
							if ((pReportInfo[1] = new CTelemetryReportInfo))
							{
								pReportInfo[1]->Copy(pReportInfo[0]);
								pReports.InsertAt(pReports.GetSize(), pReportInfo[1], 1);
								continue;
							}
						}
						break;
					}
					for (nReport[2] = 0, nReports[2] = (INT)m_pHistoricalReports->GetSize(); nReport[2] < nReports[2]; nReport[2]++)
					{
						if ((pHistoricalReportInfo = m_pHistoricalReports->GetAt(nReport[2])) && pHistoricalReportInfo->Map(nHistoricalReportData[0]))
						{
							for (nReport[3] = 0, nReports[3] = (pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATDAILYTIME || pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL) ? (INT)pReports.GetSize() : 0; nReport[3] < nReports[3]; nReport[3]++)
							{
								if ((pReportInfo[0] = pReports.GetAt(nReport[3])) && pReportInfo[0]->GetLink(nHistoricalReportData[1]) > 0 && nHistoricalReportData[0].GetSize() == nHistoricalReportData[1].GetSize() && !memcmp(nHistoricalReportData[0].GetData(), nHistoricalReportData[1].GetData(), nHistoricalReportData[0].GetSize())) break;
								continue;
							}
							if (nReport[3] == nReports[3])
							{
								if ((pReportInfo[1] = new CTelemetryReportInfo))
								{
									if (DoConvert(pHistoricalReportInfo, pReportInfo[1]))
									{
										pReports.InsertAt(pReports.GetSize(), pReportInfo[1], 1);
										continue;
									}
									delete pReportInfo[1];
								}
								break;
							}
							continue;
						}
						break;
					}
					if (nReport[0] == nReports[0] && nReport[1] == nReports[1] && nReport[2] == nReports[2])
					{
						m_pHistoricalReports->Unlock();
						m_pReports[2]->Unlock();
						m_pReports[1]->Unlock();
						m_pReports[0]->Unlock();
						return TRUE;
					}
					m_pHistoricalReports->Unlock();
				}
				m_pReports[2]->Unlock();
			}
			m_pReports[1]->Unlock();
		}
		m_pReports[0]->Unlock();
	}
	return FALSE;
}

BOOL CTelemetryReportsService::AbortReports(CONST CTelemetryReports &pReports)
{
	INT  nReport[4];
	INT  nReports[4];
	CByteArray  nHistoricalReportData[2];
	CTelemetryReportInfo  *pReportInfo[2];
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	if (m_pReports[0]->Lock())
	{
		if (m_pReports[1]->Lock())
		{
			if (m_pReports[2]->Lock())
			{
				if (m_pHistoricalReports->Lock())
				{
					for (nReport[0] = 0, nReports[0] = (INT)pReports.GetSize(); nReport[0] < nReports[0]; nReport[0]++)
					{
						for (nReport[1] = 0, nReports[1] = sizeof(m_pReports) / sizeof(CTelemetryReports); nReport[1] < nReports[1]; nReport[1]++)
						{
							for (nReport[2] = 0, nReports[2] = (INT)m_pReports[nReport[1]]->GetSize(); nReport[2] < nReports[2]; nReport[2]++)
							{
								if ((pReportInfo[0] = pReports.GetAt(nReport[0])) != (CTelemetryReportInfo *)NULL)
								{
									if ((pReportInfo[1] = m_pReports[nReport[1]]->GetAt(nReport[2])))
									{
										if (pReportInfo[0]->Compare(pReportInfo[1]))
										{
											for (DoDeleteMailFile(pReportInfo[1]); pReportInfo[1]->GetStatus() == TELEMETRYREPORTINFO_STATUS_EXECUTING; )
											{
												m_bAbort.SetEvent();
												break;
											}
											if (!nReport[1])
											{
												pReportInfo[1]->SetScheduledPeriod(0, 0, 0);
												pReportInfo[1]->SetLastExecutionTime(0);
												break;
											}
											if (nReport[1] == nReports[1] - 1)
											{
												DeleteJScriptTaskSchedulerTelemetryReport(m_nReportIDs.GetAt(nReport[2]));
												m_nReportIDs.RemoveAt(nReport[2]);
											}
											m_pReports[nReport[1]]->RemoveAt(nReport[2]);
											delete pReportInfo[1];
											break;
										}
									}
								}
							}
							if (nReport[2] < nReports[2]) break;
						}
						for (nReport[3] = 0, nReports[3] = ((pReportInfo[0] = pReports.GetAt(nReport[0])) && pReportInfo[0]->GetLink(nHistoricalReportData[0]) > 0) ? (INT)m_pHistoricalReports->GetSize() : 0; nReport[3] < nReports[3]; nReport[3]++)
						{
							if ((pHistoricalReportInfo = m_pHistoricalReports->GetAt(nReport[3])) && pHistoricalReportInfo->Map(nHistoricalReportData[1]) && nHistoricalReportData[0].GetSize() == nHistoricalReportData[1].GetSize() && !memcmp(nHistoricalReportData[0].GetData(), nHistoricalReportData[1].GetData(), nHistoricalReportData[0].GetSize()))
							{
								m_pHistoricalReports->RemoveAt(nReport[3]);
								delete pHistoricalReportInfo;
								break;
							}
						}
					}
					m_pHistoricalReports->Unlock();
					m_pReports[2]->Unlock();
					m_pReports[1]->Unlock();
					m_pReports[0]->Unlock();
					return Update();
				}
				m_pReports[2]->Unlock();
			}
			m_pReports[1]->Unlock();
		}
		m_pReports[0]->Unlock();
	}
	return FALSE;
}

BOOL CTelemetryReportsService::DoHistoricalReport(CTelemetryReportInfo *pReportInfo)
{
	UINT  nResult;
	CString  szError;
	CString  szMessage;
	CTimeKey  tTimeKey;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTMEnvironment  cTMEnvironment;
	CHistoryTMProcessEngine  cTMProcessEngine;

	if (cTMEnvironment.Create(GetDatabase()))
	{
		if (cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), pReportInfo->GetHistoricalSource(), &cTMEnvironment))
		{
			for (InitializeJScriptTelemetryInterface(GetDatabase(), &cTMEnvironment), m_bAbort.ResetEvent(), m_bExit = FALSE; (nResult = (DoTrack(&cTMEnvironment) && pReportInfo->GetHistoricalPeriod(tStartTime, tStopTime, tInterval)) ? cTMProcessEngine.ProcessTMData(GetDatabase(), &cTMEnvironment, (tTimeKey = tStartTime)) : 0) & HISTORYFILE_SUCCESS; )
			{
				if ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))
				{
					if (tTimeKey.GetTime() > tStopTime.GetTime())
					{
						UninitializeJScriptTelemetryInterface();
						cTMProcessEngine.Close();
						cTMEnvironment.Destroy();
						return TRUE;
					}
					if (DoUpdate(&cTMEnvironment, pReportInfo, TRUE))
					{
						for (szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EXECUTION_MESSAGE), (LPCTSTR)pReportInfo->GetName()), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE); tTimeKey <= tStopTime && Wait(0); )
						{
							if ((nResult = cTMProcessEngine.ReplayTMData(GetDatabase(), &cTMEnvironment, tTimeKey, tInterval.GetTotalSeconds())) & HISTORYFILE_SUCCESS)
							{
								if ((nResult & HISTORYFILE_TMUNIT) && tTimeKey <= tStopTime)
								{
									if (tTimeKey.GetTime() >= tStartTime.GetTime())
									{
										if (!DoUpdate(&cTMEnvironment, pReportInfo))
										{
											nResult = 0;
											break;
										}
									}
									continue;
								}
								if ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeKey <= tStopTime)
								{
									if (tTimeKey >= tStartTime  &&  tInterval.GetTotalSeconds() > 0)
									{
										if (!DoUpdate(&cTMEnvironment, pReportInfo))
										{
											nResult = 0;
											break;
										}
									}
									continue;
								}
							}
							break;
						}
						if (!Wait(0) || IsAborted())
						{
							szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EXECUTION_ABORT), (LPCTSTR)pReportInfo->GetName());
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
							DoDeleteOutputFile(pReportInfo);
							UninitializeJScriptTelemetryInterface();
							cTMProcessEngine.Close();
							cTMEnvironment.Destroy();
							return FALSE;
						}
					}
					else  nResult = 0;
				}
				if ((nResult & HISTORYFILE_SUCCESS) || (nResult & HISTORYFILE_DATA_NONE))
				{
					szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EXECUTION_SUCCESS), (LPCTSTR)pReportInfo->GetName());
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					pReportInfo->SetMailFileName(pReportInfo->GetOutputFileName());
					UninitializeJScriptTelemetryInterface();
					cTMProcessEngine.Close();
					cTMEnvironment.Destroy();
					return TRUE;
				}
				break;
			}
			UninitializeJScriptTelemetryInterface();
			cTMProcessEngine.Close();
		}
		cTMEnvironment.Destroy();
	}
	szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_FAILUREFORMAT), (LPCTSTR)pReportInfo->GetName(), STRING(IDS_TELEMETRYREPORTS_SERVICE_RETRIEVE_FAILURE));
	ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
	return FALSE;
}

BOOL CTelemetryReportsService::DoNotifyByEMail(CTelemetryReportInfo *pReportInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nCount;
	UINT  nWeekDays;
	BOOL  bWorkingDays;
	BOOL  bAttachment;
	CString  szSubject;
	CString  szLine[6];
	CString  szAddresses;
	CString  szAttachment;
	CString  szMessage[2];
	CString  szUsers[2];
	CString  szUser;
	CTimeKey  tTime;
	CTimeKey  tMission[2];
	CTimeKey  tHoliday[2];
	CTimeSpan  tDayHours[2];
	CFileFindEx  cFileFind;
	CVersionInfo  cVersionInfo;
	CStringArray  szRecipients[3];
	CUserProfiles  pRecipientsAddresses;
	CUserProfileInfo  *pRecipientAddressInfo;
	CUserAddressBook  cRecipientsAddressBook;
	CComputerToken  cComputerToken;

	for (nUser = 0, nUsers = (cRecipientsAddressBook.GetUserAddressBook(pRecipientsAddresses)) ? pReportInfo->GetMailRecipients(szRecipients[0]) : -1; nUser < nUsers; nUser++)
	{
		if ((pRecipientAddressInfo = pRecipientsAddresses.GetAt(pRecipientsAddresses.Find(szRecipients[0].GetAt(nUser)))))
		{
			if (pRecipientAddressInfo->GetOfficeHours(nWeekDays, tDayHours[0], tDayHours[1]))
			{
				if ((((nWeekDays & USERPROFILE_WORKDAY_MONDAY) && tTime.GetDayOfWeek() == Monday) || ((nWeekDays & USERPROFILE_WORKDAY_TUESDAY) && tTime.GetDayOfWeek() == Tuesday) || ((nWeekDays & USERPROFILE_WORKDAY_WEDNESDAY) && tTime.GetDayOfWeek() == Wednesday) || ((nWeekDays & USERPROFILE_WORKDAY_THURSDAY) && tTime.GetDayOfWeek() == Thursday) || ((nWeekDays & USERPROFILE_WORKDAY_FRIDAY) && tTime.GetDayOfWeek() == Friday) || ((nWeekDays & USERPROFILE_WORKDAY_SATURDAY) && tTime.GetDayOfWeek() == Saturday) || ((nWeekDays & USERPROFILE_WORKDAY_SUNDAY) && tTime.GetDayOfWeek() == Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
					szRecipients[2].Add(pRecipientAddressInfo->GetOfficeEMail());
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHomeHours(tDayHours[0], tDayHours[1], bWorkingDays))
			{
				if ((!bWorkingDays || (tTime.GetDayOfWeek() != Saturday && tTime.GetDayOfWeek() != Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHomeEMail());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHomeEMail());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetMission(tMission[0], tMission[1]))
			{
				if (tTime >= tMission[0].GetTime() && tTime <= tMission[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetMissionEMail());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetMissionEMail());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHoliday(tHoliday[0], tHoliday[1]))
			{
				if (tTime >= tHoliday[0].GetTime() && tTime <= tHoliday[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHolidayEMail());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHolidayEMail());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
		}
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), nCount = 0; nUser < nUsers; nUser++)
	{
		szUser.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_PARTSTEXT), (LPCTSTR)szRecipients[1].GetAt(nUser));
		if (!szRecipients[2].GetAt(nUser).IsEmpty())
		{
			szUsers[0] += (!szUsers[0].IsEmpty()) ? (CString(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SEPARATOR)) + SPACE + szUser) : szUser;
			szAddresses += (!szAddresses.IsEmpty()) ? (STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SEPARATOR) + szRecipients[2].GetAt(nUser)) : szRecipients[2].GetAt(nUser);
			continue;
		}
		szUsers[1] += (!szUsers[1].IsEmpty()) ? (CString(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SEPARATOR)) + SPACE + szUser) : szUser;
		nCount++;
	}
	if (nUsers > 0)
	{
		for (szAttachment = pReportInfo->GetMailFileName(), bAttachment = FALSE; !szAttachment.IsEmpty(); )
		{
			if (cFileFind.FindFile(szAttachment))
			{
				bAttachment = TRUE;
				cFileFind.Close();
			}
			break;
		}
		for (szSubject.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SUBJECT), (LPCTSTR)cVersionInfo.QueryProductName()), szLine[0].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_TITLETEXT), (LPCTSTR)cVersionInfo.QueryProductName()), szLine[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_DAILYTYPETEXT), (LPCTSTR)tTime.FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR))), szLine[2].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_DAYSTYPETEXT), (LPCTSTR)tTime.FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)), pReportInfo->GetMailTimeInterval().GetTotalSeconds() / SECONDSPERDAY), szLine[3].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_WEEKLYTYPETEXT), (LPCTSTR)tTime.FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR))), szLine[4].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SUBTITLETEXT), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tTime.FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)), (LPCTSTR)tTime.FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)), (pReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILDAILY) ? ((pReportInfo->GetMailTimeInterval().GetTotalSeconds() <= SECONDSPERDAY) ? (LPCTSTR)szLine[1] : (LPCTSTR)szLine[2]) : (LPCTSTR)szLine[3]), szLine[5].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_MESSAGETEXT), (LPCTSTR)cVersionInfo.QueryProductName(), (LPCTSTR)pReportInfo->GetName(), (!szAttachment.IsEmpty() && bAttachment) ? STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_ATTACHMENTTEXT) : STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_NOATTACHMENTTEXT), (LPCTSTR)cComputerToken.GetComputerName()), szMessage[0] = GetEMailSystem()->Send(szSubject, szLine[0] + CString(CR) + CString(EOL) + szLine[4] + CString(CR) + CString(EOL) + CString(CR) + CString(EOL) + CString(CR) + CString(EOL) + szLine[5], szAddresses, szAttachment); szMessage[0].IsEmpty(); )
		{
			for (szMessage[0].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SENDSUCCESS), (LPCTSTR)pReportInfo->GetName(), (LPCTSTR)szUsers[0]), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage[0], FALSE); !szAttachment.IsEmpty() && !bAttachment; )
			{
				szMessage[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_ATTACHMENTFAILURE), (LPCTSTR)szAttachment, (LPCTSTR)pReportInfo->GetName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[1], FALSE);
				break;
			}
			return TRUE;
		}
		for (ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[0], FALSE); !szUsers[0].IsEmpty(); )
		{
			szMessage[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SENDFAILURE), (LPCTSTR)pReportInfo->GetName(), (LPCTSTR)szUsers[0]);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[1], FALSE);
			break;
		}
		if (!szUsers[1].IsEmpty())
		{
			szMessage[1].Format((nCount > 1) ? STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SENDFAILURE_NODELIVERIES) : STRING(IDS_TELEMETRYREPORTS_SERVICE_EMAIL_SENDFAILURE_NODELIVERY), (LPCTSTR)szUsers[1], (LPCTSTR)pReportInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[1], FALSE);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CTelemetryReportsService::DoNotifyByFTP(CTelemetryReportInfo *pReportInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nResultCode;
	UINT  nRetries;
	CString  szUser;
	CString  szUsers;
	CString  szMessage;
	CTimeSpan  tRetryInterval;
	CStringArray  szRecipients[2];
	CTelemetryReportFTPRecipients  pRecipients;
	CTelemetryReportFTPRecipientInfo  *pRecipientInfo;

	for (nUser = 0, nUsers = pReportInfo->GetMailRecipients(pRecipients), m_bAbort.ResetEvent(), m_bExit = FALSE; nUser < nUsers && Wait(0); nUser++)
	{
		if ((pRecipientInfo = pRecipients.GetAt(nUser)) && pRecipientInfo->IsEnabled() && (pRecipientInfo->GetRetryTime() > 0 || !pRecipientInfo->GetRetryCount()))
		{
			if ((nResultCode = DoFTPMessageTransfer(pReportInfo, pRecipientInfo->GetUserName(), pRecipientInfo->GetLocation(), pRecipientInfo->GetPassword(), pRecipientInfo->GetPort())) > 0)
			{
				for (pRecipientInfo->SetRetryTime(CTimeKey(0)), pRecipientInfo->SetRetryCount(max(pRecipientInfo->GetRetryCount(), 1)); pRecipientInfo->GetAudition() == TELEMETRYREPORT_FTPRECIPIENT_AUDITION_ALL; )
				{
					szRecipients[0].Add(pRecipientInfo->GetLocation());
					break;
				}
				continue;
			}
			if (pRecipientInfo->GetRetryInfo(nRetries, tRetryInterval) && !nResultCode)
			{
				if (pRecipientInfo->GetRetryCount() < nRetries || nRetries == (UINT)-1)
				{
					pRecipientInfo->SetRetryCount(max(pRecipientInfo->GetRetryCount() + 1, pRecipientInfo->GetRetryCount()));
					pRecipientInfo->SetRetryTime(CTimeKey(CTime::GetCurrentTime().GetTime() + tRetryInterval.GetTotalSeconds()));
					continue;
				}
			}
			for (pRecipientInfo->SetRetryTime(CTimeKey(0)), pRecipientInfo->SetRetryCount(max(pRecipientInfo->GetRetryCount(), 1)); pRecipientInfo->GetAudition() != TELEMETRYREPORT_FTPRECIPIENT_AUDITION_NONE; )
			{
				szRecipients[1].Add(pRecipientInfo->GetLocation());
				break;
			}
		}
	}
	for (; nUsers > 0; )
	{
		pReportInfo->SetMailRecipients(pRecipients);
		break;
	}
	if (Wait(0) && !IsAborted())
	{
		if (szRecipients[0].GetSize() > 0 && !szRecipients[1].GetSize())
		{
			szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_FTPMESSAGE_SUCCESS), (LPCTSTR)pReportInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
		}
		if (szRecipients[1].GetSize() == 1)
		{
			szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_FTPMESSAGE_FAILURE_NODELIVERY), (LPCTSTR)pReportInfo->GetName(), (LPCTSTR)szRecipients[1].GetAt(0));
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		if (szRecipients[1].GetSize() > 1)
		{
			for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(); nUser < nUsers; nUser++)
			{
				szUser.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_FTPMESSAGE_PARTSTEXT), (LPCTSTR)szRecipients[1].GetAt(nUser));
				szUsers += (nUser > 0) ? (STRING(IDS_TELEMETRYREPORTS_SERVICE_FTPMESSAGE_SEPARATOR) + szUser) : szUser;
			}
			szMessage.Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_FTPMESSAGE_FAILURE_NODELIVERIES), (LPCTSTR)pReportInfo->GetName(), (LPCTSTR)szUsers);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

INT CTelemetryReportsService::DoFTPMessageTransfer(CONST CTelemetryReportInfo *pReportInfo, LPCTSTR pszUserName, LPCTSTR pszAddress, LPCTSTR pszPassword, UINT nPort)
{
	DWORD  cbData;
	DWORD  dwType;
	LPBYTE  pData;
	CFileEx  cFile;
	CString  szServer;
	CString  szFileName;
	CString  szDirectory;
	CFileFindEx  cFileFind;
	INTERNET_PORT  nInternetPort;
	CInternetFile  *pInternetFile;
	CFtpConnection  *pFtpConnection;
	CInternetSession  cInternetSession;

	if (AfxParseURL(pszAddress, dwType, szServer, szDirectory, nInternetPort))
	{
		try
		{
			pFtpConnection = cInternetSession.GetFtpConnection(szServer, pszUserName, pszPassword, (!nPort) ? ((nInternetPort == INTERNET_DEFAULT_FTP_PORT) ? INTERNET_INVALID_PORT_NUMBER : nInternetPort) : nPort);
		}
		catch (CInternetException *pException)
		{
			pException->Delete();
			return FALSE;
		}
		try
		{
			for (szFileName.Empty(), szDirectory = (szDirectory.Left(lstrlen(STRING(IDS_INTERNET_DELIMITER))) == STRING(IDS_INTERNET_DELIMITER)) ? szDirectory.Mid(lstrlen(STRING(IDS_INTERNET_DELIMITER))) : szDirectory; !szDirectory.IsEmpty(); )
			{
				pFtpConnection->SetCurrentDirectory(szDirectory);
				break;
			}
			if (cFileFind.FindFile(pReportInfo->GetMailFileName()) && !cFileFind.FindNextFile())
			{
				szFileName = cFileFind.GetFileName();
				cFileFind.Close();
			}
			if (szFileName.IsEmpty())
			{
				pFtpConnection->Close();
				delete pFtpConnection;
				return -1;
			}
			pInternetFile = pFtpConnection->OpenFile(szFileName, GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII);
		}
		catch (CInternetException *pException)
		{
			pFtpConnection->Close();
			delete pFtpConnection;
			pException->Delete();
			return FALSE;
		}
		try
		{
			if (cFile.Open(pReportInfo->GetMailFileName(), CFile::modeRead | CFile::shareDenyWrite))
			{
				if ((pData = (LPBYTE)GlobalAlloc(GPTR, (SIZE_T)(cFile.GetLength()))) != (LPBYTE)NULL)
				{
					if (ReadFile(cFile.m_hFile, pData, (DWORD)cFile.GetLength(), &cbData, (LPOVERLAPPED)NULL))
					{
						pInternetFile->Write(pData, cbData);
						pInternetFile->Close();
						pFtpConnection->Close();
						delete pFtpConnection;
						delete pInternetFile;
						GlobalFree(pData);
						cFile.Close();
						return TRUE;
					}
					GlobalFree(pData);
				}
				cFile.Close();
			}
			pFtpConnection->Remove(szFileName);
			pInternetFile->Close();
			pFtpConnection->Close();
			delete pFtpConnection;
			delete pInternetFile;
			return FALSE;
		}
		catch (CInternetException *pException)
		{
			pFtpConnection->Remove(szFileName);
			pInternetFile->Close();
			pFtpConnection->Close();
			delete pFtpConnection;
			delete pInternetFile;
			GlobalFree(pData);
			pException->Delete();
			return FALSE;
		}
	}
	return FALSE;
}

VOID CTelemetryReportsService::DoPrepareInputFiles(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CTelemetryReportInfo *pReportInfo)
{
	INT  nFile;
	INT  nFiles;
	INT  nPos[2];
	BOOL  bFound[2];
	DWORD  dwService;
	CString  szFileName;
	CString  szDirectory;
	CString  szFTPServer;
	CString  szFTPDirectory;
	CString  szTempDirectory;
	CString  szInputFiles;
	CFileFindEx  cFileFind;
	CStringArray  szFiles;
	INTERNET_PORT  nFTPPort;
	CLogicalDrives  cDrives;
	CFtpConnection  *pFtpConnection;
	CInternetSession  cInternetSession;

	for (szInputFiles = pHistoricalReportInfo->GetInputFiles(), szDirectory = pHistoricalReportInfo->GetInputDirectory(); !szInputFiles.IsEmpty(); )
	{
		nPos[0] = szInputFiles.Find(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_SEMICOLON));
		nPos[1] = szInputFiles.Find(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_COMMA));
		if ((nPos[0] < nPos[1] && nPos[0] >= 0) || (nPos[0] >= 0 && nPos[1] < 0))
		{
			szFiles.Add(szInputFiles.Left(nPos[0]));
			szInputFiles = szInputFiles.Mid(nPos[0]);
			szInputFiles = szInputFiles.Mid(lstrlen(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_SEMICOLON)));
			continue;
		}
		if ((nPos[0] > nPos[1] && nPos[1] >= 0) || (nPos[1] >= 0 && nPos[0] < 0))
		{
			szFiles.Add(szInputFiles.Left(nPos[1]));
			szInputFiles = szInputFiles.Mid(nPos[1]);
			szInputFiles = szInputFiles.Mid(lstrlen(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_COMMA)));
			continue;
		}
		szFiles.Add(szInputFiles);
		break;
	}
	for (nFile = 0, nFiles = (INT)szFiles.GetSize(), szInputFiles.Empty(); nFile < nFiles; nFile++)
	{
		if (szFiles.GetAt(nFile).IsEmpty())
		{
			szFiles.RemoveAt(nFile);
			nFiles--;
			nFile--;
			continue;
		}
		for (bFound[0] = cFileFind.FindFile(szFiles.GetAt(nFile)), bFound[1] = FALSE; bFound[0]; )
		{
			for (bFound[0] = cFileFind.FindNextFile(), bFound[1] = TRUE; !szDirectory.IsEmpty(); )
			{
				for (szFileName = (szDirectory.Right(1) != cDrives.GetPathDelimiter()) ? (szDirectory + cDrives.GetPathDelimiter() + cFileFind.GetFileName()) : (szDirectory + cFileFind.GetFileName()); CFileEx::Copy(cFileFind.GetFilePath(), szFileName); )
				{
					szInputFiles += (!szInputFiles.IsEmpty()) ? (STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_SEMICOLON) + szFileName) : szFileName;
					break;
				}
				break;
			}
			if (szDirectory.IsEmpty()) szInputFiles += (!szInputFiles.IsEmpty()) ? (STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_SEMICOLON) + cFileFind.GetFilePath()) : cFileFind.GetFilePath();
			cFileFind.Close();
		}
		if (!bFound[1])
		{
			if (AfxParseURL(pHistoricalReportInfo->GetInputFTPLocation(), dwService, szFTPServer, szFTPDirectory, nFTPPort) && dwService == AFX_INET_SERVICE_FTP)
			{
				try
				{
					pFtpConnection = cInternetSession.GetFtpConnection(szFTPServer, pHistoricalReportInfo->GetInputFTPUserName(), pHistoricalReportInfo->GetInputFTPPassword(), (!pHistoricalReportInfo->GetInputFTPPort()) ? nFTPPort : pHistoricalReportInfo->GetInputFTPPort());
				}
				catch (CInternetException *pException)
				{
					pException->Delete();
					continue;
				}
				try
				{
					for (GetTempPath(MAX_PATH, szTempDirectory.GetBufferSetLength(MAX_PATH)), szTempDirectory.ReleaseBuffer(), szFTPDirectory = (szFTPDirectory.Left(lstrlen(STRING(IDS_INTERNET_DELIMITER))) == STRING(IDS_INTERNET_DELIMITER)) ? szFTPDirectory.Mid(lstrlen(STRING(IDS_INTERNET_DELIMITER))) : szFTPDirectory, szFileName = (!szDirectory.IsEmpty()) ? ((szDirectory.Right(CString(cDrives.GetPathDelimiter()).GetLength()) != cDrives.GetPathDelimiter()) ? (szDirectory + cDrives.GetPathDelimiter() + szFiles.GetAt(nFile)) : (szDirectory + szFiles.GetAt(nFile))) : ((szTempDirectory.Right(CString(cDrives.GetPathDelimiter()).GetLength()) != cDrives.GetPathDelimiter()) ? (szTempDirectory + cDrives.GetPathDelimiter() + szFiles.GetAt(nFile)) : (szTempDirectory + szFiles.GetAt(nFile))); !szFTPDirectory.IsEmpty(); )
					{
						pFtpConnection->SetCurrentDirectory(szFTPDirectory);
						break;
					}
					if (pFtpConnection->GetFile(szFiles.GetAt(nFile), szFileName, FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_ASCII)) szInputFiles += (!szInputFiles.IsEmpty()) ? (STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_SEMICOLON) + szFileName) : szFileName;
					pFtpConnection->Close();
					delete pFtpConnection;
				}
				catch (CInternetException *pException)
				{
					pFtpConnection->Close();
					delete pFtpConnection;
					pException->Delete();
				}
			}
		}
	}
	pReportInfo->SetOptions(pReportInfo->GetOptions() | (pHistoricalReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_KEEPINPUTFILES));
	pReportInfo->SetInputFileName(szInputFiles);
}

VOID CTelemetryReportsService::DoPrepareOutputFile(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CTelemetryReportInfo *pReportInfo)
{
	CStringArray  szRecipients;
	CTelemetryReportFTPRecipients  pRecipients;

	for (pReportInfo->SetOutputFileName(pHistoricalReportInfo->GetOutputFile()); pHistoricalReportInfo->GetMailRecipients(szRecipients) >= 0; )
	{
		pReportInfo->SetMailRecipients(szRecipients);
		break;
	}
	for (; pHistoricalReportInfo->GetMailRecipients(pRecipients) >= 0; )
	{
		pReportInfo->SetMailRecipients(pRecipients);
		break;
	}
	pReportInfo->SetOptions(pReportInfo->GetOptions() | (pHistoricalReportInfo->GetOptions() & TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE));
	pReportInfo->SetOutputFileName(pHistoricalReportInfo->GetOutputFile());
}

BOOL CTelemetryReportsService::DoDeleteOutputFile(CONST CTelemetryReportInfo *pReportInfo)
{
	return((!pReportInfo->GetOutputFileName().IsEmpty()) ? CFileEx::Remove(pReportInfo->GetOutputFileName()) : FALSE);
}

BOOL CTelemetryReportsService::DoDeleteMailFile(CONST CTelemetryReportInfo *pReportInfo)
{
	return((!pReportInfo->GetMailFileName().IsEmpty()) ? CFileEx::Remove(pReportInfo->GetMailFileName()) : FALSE);
}

BOOL CTelemetryReportsService::DoTrack(CTMEnvironment *pTMEnvironment)
{
	INT  nEvent;
	INT  nEvents;
	INT  nSample;
	INT  nParameter;
	INT  nParameters;
	INT  nExpression;
	INT  nExpressions;
	BOOL  bSampleCoding;
	CString  szParameter;
	CUIntArray  nPastSamples;
	CStringArray  szParameters;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;
	CTelemetryEventExpression  *pEventExpression;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		for (nExpression = 0, nExpressions = (pEventInfo = pEvents.GetAt(nEvent)) ? (INT)pEventInfo->GetSize() : 0; nExpression < nExpressions; nExpression++)
		{
			if ((pEventExpression = pEventInfo->GetAt(nExpression)) && pEventExpression->IsParameter() && pEventExpression->GetParameter(szParameter, nSample, bSampleCoding))
			{
				for (nParameter = 0, nParameters = (nSample < 0) ? (INT)szParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
				{
					if (!szParameters.GetAt(nParameter).Compare(szParameter) && nPastSamples.GetAt(nParameter) < (UINT)abs(nSample))
					{
						nPastSamples.SetAt(nParameter, abs(nSample));
						break;
					}
					if (!szParameters.GetAt(nParameter).Compare(szParameter)) break;
				}
				if (nParameter == nParameters)
				{
					szParameters.Add(szParameter);
					nPastSamples.Add(abs(nSample));
				}
			}
		}
	}
	return pTMEnvironment->Initialize(szParameters, nPastSamples);
}

BOOL CTelemetryReportsService::DoUpdate(CONST CTMEnvironment *pTMEnvironment, CONST CTelemetryReportInfo *pReportInfo, BOOL bReset)
{
	INT  nEvent;
	INT  nEvents;
	INT  nExpression;
	INT  nExpressions;
	INT  nSample;
	UINT  nCount;
	UINT  nStatus;
	BOOL  bCoding;
	ULONGLONG  nValue;
	CString  szParameter;
	CTimeTag  tParameter;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;
	CTelemetryEventExpression  *pExpression;
	CTMParameter  *pTMParameter;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0, DoReset(bReset); nEvent < nEvents; nEvent++)
	{
		for (nExpression = 0, nExpressions = ((pEventInfo = pEvents.GetAt(nEvent))) ? (INT)pEventInfo->GetSize() : 0, tParameter = 0, nCount = 0; nExpression < nExpressions; nExpression++)
		{
			if ((pTMParameter = ((pExpression = pEventInfo->GetAt(nExpression)) && pExpression->GetParameter(szParameter, nSample, bCoding)) ? pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pExpression->GetParameter())) : (CTMParameter *)NULL))
			{
				if (pTMParameter->GetRawValue(nSample, nValue, nStatus) && ((nStatus & TMPARAMETER_STATUS_VALID) || pEventInfo->IsInvalidDataModeEnabled()) && ((nStatus & TMPARAMETER_STATUS_GOOD) || pEventInfo->IsBadDataModeEnabled()))
				{
					for (; pTMEnvironment->GetTMUnit()->GetTag() == pTMParameter->GetLastUpdateTMUnit() && pTMEnvironment->GetTMUnit()->GetTimeTag() == pTMParameter->GetLastUpdateTime(); )
					{
						tParameter = (pTMParameter->GetLastUpdateTime() > tParameter) ? pTMParameter->GetLastUpdateTime() : tParameter;
						break;
					}
					nCount++;
					continue;
				}
				break;
			}
		}
		if (nExpression == nExpressions)
		{
			if (tParameter > 0 || !nCount)
			{
				pEventInfo->SetTime(tParameter);
				DoAlert(pTMEnvironment, pReportInfo, pEventInfo);
			}
		}
	}
	return((nEvent == nEvents) ? TRUE : FALSE);
}

VOID CTelemetryReportsService::DoAlert(CONST CTMEnvironment *pTMEnvironment, CONST CTelemetryReportInfo *pReportInfo, CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nIndex;
	INT  nAlert;
	INT  nAlerts;
	INT  nEvent;
	INT  nEvents;
	INT  nExpression;
	INT  nExpressions;
	INT  nSample;
	UINT  nStatus;
	BOOL  bCoding;
	double  fValue;
	ULONGLONG  nValue;
	CString  szParameter;
	CStringArray  szEvents;
	CFloatArray  fExpressions;
	CTelemetryEventExpression  *pExpression;
	CTMParameter  *pTMParameter;

	for (nExpression = 0, nExpressions = (INT)pEventInfo->GetSize(), fExpressions.SetSize(pEventInfo->GetSize()), nIndex = 0; nExpression < nExpressions; nExpression++)
	{
		if ((pExpression = pEventInfo->GetAt(nExpressions - nExpression - 1)))
		{
			if (pExpression->IsNumber())
			{
				fExpressions[nIndex] = pExpression->GetNumber();
				nIndex++;
				continue;
			}
			if (pExpression->IsParameter())
			{
				if ((pTMParameter = (pExpression->GetParameter(szParameter, nSample, bCoding)) ? pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(szParameter)) : (CTMParameter *)NULL))
				{
					if (pTMParameter->GetRawValue(nSample, nValue, nStatus) && pTMParameter->GetValue(GetDatabase(), nSample, (bCoding) ? ((pTMParameter->GetAttributes() | TMPARAMETER_CALIBRATION_NONE) & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) : pTMParameter->GetAttributes(), fValue))
					{
						fExpressions[nIndex] = fValue;
						nIndex++;
						continue;
					}
				}
				break;
			}
			if (pExpression->IsOperator())
			{
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_DIV))
				{
					if (fExpressions[nIndex - 1] != 0.0  &&  fabs(fExpressions[nIndex - 1]) > FLT_EPSILON)
					{
						fExpressions[(nIndex - 1) - 1] = fExpressions[(nIndex - 1) - 1] / fExpressions[nIndex - 1];
						nIndex--;
						continue;
					}
					break;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_MUL))
				{
					fExpressions[(nIndex - 1) - 1] *= fExpressions[nIndex - 1];
					nIndex--;
					continue;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_SUB))
				{
					fExpressions[(nIndex - 1) - 1] = fExpressions[(nIndex - 1) - 1] - fExpressions[nIndex - 1];
					nIndex--;
					continue;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_ADD))
				{
					fExpressions[(nIndex - 1) - 1] += fExpressions[nIndex - 1];
					nIndex--;
					continue;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_CHG))
				{
					fExpressions[nIndex - 1] = -fExpressions[nIndex - 1];
					continue;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_AND))
				{
					fExpressions[(nIndex - 1) - 1] = (double)(((UINT)fExpressions[(nIndex - 1) - 1]) & ((UINT)fExpressions[nIndex - 1]));
					nIndex--;
					continue;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_OR))
				{
					fExpressions[(nIndex - 1) - 1] = (double)(((UINT)fExpressions[(nIndex - 1) - 1]) | ((UINT)fExpressions[nIndex - 1]));
					nIndex--;
					continue;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_NOT))
				{
					fExpressions[nIndex - 1] = (double)(~(ULONGLONG)fExpressions[nIndex - 1]);
					continue;
				}
				if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_XOR))
				{
					fExpressions[(nIndex - 1) - 1] = (double)(((UINT)fExpressions[(nIndex - 1) - 1]) ^ ((UINT)fExpressions[nIndex - 1]));
					nIndex--;
					continue;
				}
			}
			if (pExpression->IsFunction())
			{
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_SIN))
				{
					fExpressions[nIndex - 1] = sin(fExpressions[nIndex - 1]);
					continue;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_COS))
				{
					fExpressions[nIndex - 1] = cos(fExpressions[nIndex - 1]);
					continue;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_TAN))
				{
					if (fabs(fmod(fExpressions[nIndex - 1], M_PI)) - M_PI / 2.0 > FLT_EPSILON)
					{
						fExpressions[nIndex - 1] = tan(fExpressions[nIndex - 1]);
						continue;
					}
					break;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ASIN))
				{
					if (fabs(fExpressions[nIndex - 1]) <= 1.0)
					{
						fExpressions[nIndex - 1] = asin(fExpressions[nIndex - 1]);
						continue;
					}
					break;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ACOS))
				{
					if (fabs(fExpressions[nIndex - 1]) <= 1.0)
					{
						fExpressions[nIndex - 1] = acos(fExpressions[nIndex - 1]);
						continue;
					}
					break;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ATAN))
				{
					fExpressions[nIndex - 1] = atan(fExpressions[nIndex - 1]);
					continue;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ABS))
				{
					fExpressions[nIndex - 1] = fabs(fExpressions[nIndex - 1]);
					continue;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_INT))
				{
					fExpressions[nIndex - 1] = (fExpressions[nIndex - 1] >= 0.0) ? floor(fExpressions[nIndex - 1]) : ceil(fExpressions[nIndex - 1]);
					continue;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_SQRT))
				{
					if (fExpressions[nIndex - 1] >= 0.0)
					{
						fExpressions[nIndex - 1] = sqrt(fExpressions[nIndex - 1]);
						continue;
					}
					break;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_POW2))
				{
					fExpressions[nIndex - 1] = pow(fExpressions[nIndex - 1], 2.0);
					continue;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_POWY))
				{
					fExpressions[(nIndex - 1) - 1] = pow(fExpressions[(nIndex - 1) - 1], fExpressions[nIndex - 1]);
					nIndex--;
					continue;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_LN))
				{
					if (fExpressions[nIndex - 1] > 0.0)
					{
						fExpressions[nIndex - 1] = log(fExpressions[nIndex - 1]);
						continue;
					}
					break;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_LOG))
				{
					if (fExpressions[nIndex - 1] > 0.0)
					{
						fExpressions[nIndex - 1] = log10(fExpressions[nIndex - 1]);
						continue;
					}
					break;
				}
				if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_EXP))
				{
					fExpressions[nIndex - 1] = exp(fExpressions[nIndex - 1]);
					continue;
				}
			}
		}
	}
	if (nIndex == 1 && nExpression == nExpressions)
	{
		if ((pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_BELOWZERO  &&  fExpressions[nIndex - 1] < 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_EQUALZERO  &&  fExpressions[nIndex - 1] == 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_ABOVEZERO  &&  fExpressions[nIndex - 1] > 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_UNEQUALZERO  &&  fExpressions[nIndex - 1] != 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_BELOWEQUALZERO  &&  fExpressions[nIndex - 1] <= 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_ABOVEEQUALZERO  &&  fExpressions[nIndex - 1] >= 0.0))
		{
			for (nAlert = 0, nAlerts = (!pEventInfo->IsDisabledDataModeEnabled()) ? (INT)m_szAlerts.GetSize() : -1; nAlert < nAlerts; nAlert++)
			{
				if (m_szAlerts.GetAt(nAlert) == pEventInfo->GetName()) break;
				continue;
			}
			if (nAlert == nAlerts)
			{
				for (nEvent = 0, nEvents = pReportInfo->GetEvents(szEvents); nEvent < nEvents; nEvent++)
				{
					if (pEventInfo->GetName() == szEvents.GetAt(nEvent))
					{
						DoUpdateReport(pReportInfo, pEventInfo);
						break;
					}
				}
				m_szAlerts.Add(pEventInfo->GetName());
			}
		}
		else
		{
			for (nAlert = 0, nAlerts = (INT)m_szAlerts.GetSize(); nAlert < nAlerts; nAlert++)
			{
				if (m_szAlerts.GetAt(nAlert) == pEventInfo->GetName())
				{
					m_szAlerts.RemoveAt(nAlert);
					break;
				}
			}
		}
	}
}

BOOL CTelemetryReportsService::DoConvert(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CTelemetryReportInfo *pReportInfo) CONST
{
	INT  nIndex;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeKey  tExecution;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime[2];
	CByteArray  nHistoricalReportData;

	if ((nIndex = (pHistoricalReportInfo->Map(nHistoricalReportData)) ? m_pReports[0]->Find(pHistoricalReportInfo->GetReport()) : -1) >= 0)
	{
		for (pReportInfo->Copy(m_pReports[0]->GetAt(nIndex)), pReportInfo->SetLink(nHistoricalReportData), pReportInfo->SetHistoricalSource(pHistoricalReportInfo->GetSource()), pReportInfo->SetStatus(TELEMETRYREPORTINFO_STATUS_QUEUED); pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL && pHistoricalReportInfo->GetTimeRange(tStartTime, tStopTime); )
		{
			pReportInfo->SetHistoricalPeriod(tStartTime, tStopTime, pHistoricalReportInfo->GetRangeInterval());
			return TRUE;
		}
		if (pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_DAILY  &&  pHistoricalReportInfo->GetDailyTimeRange(tDailyTime[0], tDailyTime[1]))
		{
			tStartTime = (tExecution.GetTime() / SECONDSPERDAY)*SECONDSPERDAY + tDailyTime[0].GetTotalSeconds();
			tStopTime = (tExecution.GetTime() / SECONDSPERDAY)*SECONDSPERDAY + tDailyTime[1].GetTotalSeconds();
			tStopTime = (tStartTime > tStopTime) ? (tStopTime.GetTime() + SECONDSPERDAY) : tStopTime.GetTime();
			if (tStopTime > tExecution)
			{
				tStartTime -= SECONDSPERDAY;
				tStopTime -= SECONDSPERDAY;
			}
			pReportInfo->SetHistoricalPeriod(tStartTime, tStopTime, pHistoricalReportInfo->GetRangeInterval());
			return TRUE;
		}
		if (pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_COMPLETEINTERVAL  &&  pHistoricalReportInfo->GetPeriodicalExecutionTime(tStartTime, tInterval, tStopTime))
		{
			tStartTime = tStartTime.GetTime() + 2 * pHistoricalReportInfo->GetExecutionCycle()*tInterval.GetTotalSeconds();
			tStopTime = min(tStartTime.GetTime() + tInterval.GetTotalSeconds(), tStopTime.GetTime());
			pReportInfo->SetHistoricalPeriod(tStartTime, tStopTime, pHistoricalReportInfo->GetRangeInterval());
			return TRUE;
		}
		if (pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL  &&  pHistoricalReportInfo->GetPeriodicalExecutionTime(tStartTime, tInterval, tStopTime))
		{
			tStartTime = tStartTime.GetTime() + (pHistoricalReportInfo->GetExecutionCycle() + 1)*tInterval.GetTotalSeconds() - pHistoricalReportInfo->GetPeriodicalInterval().GetTotalSeconds();
			tStopTime = min(tStartTime.GetTime() + pHistoricalReportInfo->GetPeriodicalInterval().GetTotalSeconds(), tStopTime.GetTime());
			pReportInfo->SetHistoricalPeriod(tStartTime, tStopTime, pHistoricalReportInfo->GetRangeInterval());
			return TRUE;
		}
	}
	return FALSE;
}

VOID CTelemetryReportsService::DoReset(BOOL bReset)
{
	if (bReset)
	{
		m_szAlerts.RemoveAll();
	}
}

BOOL CTelemetryReportsService::IsAborted() CONST
{
	return m_bExit;
}

BOOL CTelemetryReportsService::Wait(DWORD dwTimeout)
{
	return(((m_bExit = (CThread::Wait(m_bAbort, FALSE, dwTimeout, TRUE) != WAIT_TIMEOUT) ? TRUE : m_bExit)) ? !m_bExit : TRUE);
}

VOID CTelemetryReportsService::ShowErrors(CONST CStringArray &szErrors)
{
	INT  nError;
	INT  nErrors;
	CString  szError[2];

	for (nError = 0, nErrors = (szErrors.GetSize() > 1) ? (INT)(szErrors.GetSize() - 1) : (INT)szErrors.GetSize(), szError[0].Empty(); nError < nErrors; nError++)
	{
		szError[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_MESSAGE_NAME), (LPCTSTR)szErrors.GetAt(nError));
		szError[0] += (!szError[0].IsEmpty()) ? (STRING(IDS_TELEMETRYREPORTS_SERVICE_MESSAGE_SEPARATOR) + szError[1]) : szError[1];
		continue;
	}
	for (szError[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_SCHEDULE_FAILURE), (szErrors.GetSize() == 1) ? (LPCTSTR)szErrors.GetAt(szErrors.GetUpperBound()) : EMPTYSTRING); szErrors.GetSize() > 1; )
	{
		szError[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_SCHEDULE_FAILURES), (LPCTSTR)szError[0], (LPCTSTR)szErrors.GetAt(szErrors.GetUpperBound()));
		break;
	}
	for (; szErrors.GetSize() > 0; )
	{
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError[1]);
		break;
	}
}

int CTelemetryReportsService::Run()
{
	INT  nIndex;
	INT  nPos[2];
	INT  nReport;
	INT  nReports;
	INT  nRecipient;
	INT  nRecipients;
	BOOL  bRecipients;
	UINT  nOptions;
	DWORD  dwDelta;
	DWORD  dwResult;
	DWORD  dwTimeout;
	TCHAR  szPath[MAX_PATH];
	CString  szFileName[2];
	CString  szInputFiles;
	CTimeKey  tMailTime;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeKey  tExecutionTime[2];
	CTimeKey  tHistoricalTime[2];
	CTimeSpan  tExecutionInterval;
	CTimeSpan  tHistoricalInterval;
	CByteArray  nHistoricalReportData;
	CFileFindEx  cFileFind[2];
	CStringArray  szRecipients;
	CTelemetryReportInfo  *pReportInfo[2];
	CTelemetryReportFTPRecipients  pRecipients;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;
	CTelemetryReportFTPRecipientInfo  *pRecipientInfo;

	do
	{
		for (m_nReportTimerID = SetTimer((HWND)NULL, m_nReportTimerID, 0, NULL), dwTimeout = INFINITE; m_pReports[0]->Lock(); )
		{
			for (tExecutionTime[0] = CTime::GetCurrentTime().GetTime(), tExecutionTime[1] = 0; m_pHistoricalReports->Lock(); )
			{
				for (nReport = 0, nReports = (INT)m_pHistoricalReports->GetSize(), nIndex = -1; nReport < nReports; nReport++)
				{
					if ((pHistoricalReportInfo = m_pHistoricalReports->GetAt(nReport)) != (CTelemetryHistoricalReportInfo *)NULL)
					{
						if (pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_IMMEDIATELY)
						{
							if (tExecutionTime[0] < tExecutionTime[1] || !tExecutionTime[1].GetTime())
							{
								tExecutionTime[1] = tExecutionTime[0];
								nIndex = nReport;
							}
							continue;
						}
						if (pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME)
						{
							if (pHistoricalReportInfo->GetExecutionTime() < tExecutionTime[1] || !tExecutionTime[1].GetTime())
							{
								tExecutionTime[1] = pHistoricalReportInfo->GetExecutionTime();
								nIndex = nReport;
							}
							continue;
						}
						if (pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATDAILYTIME)
						{
							if (((pHistoricalReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecutionTime[0].GetTime() / SECONDSPERDAY  &&  SECONDSPERDAY*(tExecutionTime[0].GetTime() / SECONDSPERDAY) + pHistoricalReportInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY < tExecutionTime[1].GetTime()) || (pHistoricalReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY >= tExecutionTime[0].GetTime() / SECONDSPERDAY  &&  SECONDSPERDAY*(tExecutionTime[0].GetTime() / SECONDSPERDAY + 1) + pHistoricalReportInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY < tExecutionTime[1].GetTime())) || !tExecutionTime[1].GetTime())
							{
								tExecutionTime[1] = (pHistoricalReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecutionTime[0].GetTime() / SECONDSPERDAY) ? (SECONDSPERDAY*(tExecutionTime[0].GetTime() / SECONDSPERDAY) + pHistoricalReportInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY) : (SECONDSPERDAY*(tExecutionTime[0].GetTime() / SECONDSPERDAY + 1) + pHistoricalReportInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY);
								nIndex = nReport;
							}
							continue;
						}
						if (pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL)
						{
							if (pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_COMPLETEINTERVAL  &&  pHistoricalReportInfo->GetPeriodicalExecutionTime(tStartTime, tExecutionInterval, tStopTime))
							{
								if (tStartTime.GetTime() + (2 * pHistoricalReportInfo->GetExecutionCycle() + 1)*tExecutionInterval.GetTotalSeconds() < tExecutionTime[1].GetTime() || !tExecutionTime[1].GetTime())
								{
									tExecutionTime[1] = tStartTime.GetTime() + (2 * pHistoricalReportInfo->GetExecutionCycle() + 1)*tExecutionInterval.GetTotalSeconds();
									nIndex = nReport;
								}
								continue;
							}
							if (pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL  &&  pHistoricalReportInfo->GetPeriodicalExecutionTime(tStartTime, tExecutionInterval, tStopTime))
							{
								if (tStartTime.GetTime() + (pHistoricalReportInfo->GetExecutionCycle() + 1)*tExecutionInterval.GetTotalSeconds() < tExecutionTime[1].GetTime() || !tExecutionTime[1].GetTime())
								{
									tExecutionTime[1] = tStartTime.GetTime() + (pHistoricalReportInfo->GetExecutionCycle() + 1)*tExecutionInterval.GetTotalSeconds();
									nIndex = nReport;
								}
								continue;
							}
						}
					}
					m_pHistoricalReports->RemoveAt(nReport);
					delete pHistoricalReportInfo;
					nReports--;
					nReport--;
				}
				for (; tExecutionTime[0] >= tExecutionTime[1] && tExecutionTime[1] > 0 && nIndex >= 0; )
				{
					if ((pHistoricalReportInfo = m_pHistoricalReports->GetAt(nIndex)))
					{
						if ((pReportInfo[0] = new CTelemetryReportInfo))
						{
							if (DoConvert(pHistoricalReportInfo, pReportInfo[0]))
							{
								DoPrepareInputFiles(pHistoricalReportInfo, pReportInfo[0]);
								DoPrepareOutputFile(pHistoricalReportInfo, pReportInfo[0]);
								if (pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_IMMEDIATELY || pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME || (pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATINTERVAL  &&  pHistoricalReportInfo->GetPeriodicalExecutionTime(tStartTime, tExecutionInterval, tStopTime) && ((pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_COMPLETEINTERVAL  &&  tStartTime.GetTime() + 2 * (pHistoricalReportInfo->GetExecutionCycle() + 1)*tExecutionInterval.GetTotalSeconds() > tStopTime.GetTime()) || (pHistoricalReportInfo->GetTimeRangeMode() == TELEMETRYHISTORICALREPORTINFO_RANGE_PARTIALINTERVAL  &&  tStartTime.GetTime() + ((pHistoricalReportInfo->GetExecutionCycle() + 1) + 1)*tExecutionInterval.GetTotalSeconds() - pHistoricalReportInfo->GetPeriodicalInterval().GetTotalSeconds() > tStopTime.GetTime()))))
								{
									pReportInfo[0]->SetLink(nHistoricalReportData);
									m_pHistoricalReports->RemoveAt(nIndex);
									delete pHistoricalReportInfo;
								}
								else
								{
									pHistoricalReportInfo->SetExecutionCycle(pHistoricalReportInfo->GetExecutionCycle() + 1);
									pHistoricalReportInfo->SetLastExecutionTime(tExecutionTime[0]);
								}
								if (m_pReports[1]->Lock())
								{
									m_pReports[1]->InsertAt(m_pReports[1]->GetSize(), pReportInfo[0], 1);
									m_pReports[1]->Unlock();
									break;
								}
							}
							m_pHistoricalReports->RemoveAt(nIndex);
							delete pHistoricalReportInfo;
							delete pReportInfo[0];
						}
					}
					else
					{
						m_pHistoricalReports->RemoveAt(nIndex);
						delete pHistoricalReportInfo;
					}
					tExecutionTime[1] = 0;
					nIndex = -1;
					break;
				}
				for (; tExecutionTime[0] < tExecutionTime[1] && nIndex >= 0; )
				{
					dwTimeout = (DWORD)min(tExecutionTime[1].GetTime() - tExecutionTime[0].GetTime(), SECONDSPERDAY);
					break;
				}
				m_pHistoricalReports->Unlock();
				break;
			}
			for (nReport = 0, nReports = (INT)m_pReports[0]->GetSize(), tMailTime = CTime::GetCurrentTime().GetTime(); nReport < nReports; nReport++)
			{
				if ((pReportInfo[0] = m_pReports[0]->GetAt(nReport)) && (pReportInfo[0]->GetOptions() & TELEMETRYREPORTINFO_OPTION_DISABLED) != TELEMETRYREPORTINFO_OPTION_DISABLED)
				{
					if ((nOptions = pReportInfo[0]->GetOptions()) & TELEMETRYREPORTINFO_OPTION_MAILDAILY)
					{
						if (pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds() / SECONDSPERDAY > 1)
						{
							if (SECONDSPERDAY*((pReportInfo[0]->GetLastMailTime().GetTime() + pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds()) / SECONDSPERDAY) + pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY <= tMailTime.GetTime())
							{
								dwTimeout = 0;
								break;
							}
							for (dwDelta = (DWORD)(SECONDSPERDAY*((pReportInfo[0]->GetLastMailTime().GetTime() + pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds()) / SECONDSPERDAY) + pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY - tMailTime.GetTime()); dwTimeout > dwDelta || dwTimeout == INFINITE; )
							{
								dwTimeout = dwDelta;
								break;
							}
							continue;
						}
						if (pReportInfo[0]->GetLastMailTime().GetTime() / SECONDSPERDAY < tMailTime.GetTime() / SECONDSPERDAY)
						{
							if (pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY <= tMailTime.GetTime() % SECONDSPERDAY)
							{
								dwTimeout = 0;
								break;
							}
							for (dwDelta = (DWORD)(pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY - tMailTime.GetTime() % SECONDSPERDAY); dwTimeout > dwDelta || dwTimeout == INFINITE; )
							{
								dwTimeout = dwDelta;
								break;
							}
							continue;
						}
						for (dwDelta = (DWORD)(SECONDSPERDAY - tMailTime.GetTime() % SECONDSPERDAY + pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY); dwTimeout > dwDelta || dwTimeout == INFINITE; )
						{
							dwTimeout = dwDelta;
							break;
						}
						continue;
					}
					if (nOptions & TELEMETRYREPORTINFO_OPTION_MAILWEEKLY)
					{
						if (pReportInfo[0]->GetLastMailTime().GetTime() < tMailTime.GetTime() - ((tMailTime.GetDayOfWeek() + Thursday) % DAYSPERWEEK)*SECONDSPERDAY - tMailTime.GetTime() % SECONDSPERDAY)
						{
							if (((tMailTime.GetDayOfWeek() + Thursday) % DAYSPERWEEK == (pReportInfo[0]->GetMailTime().GetDayOfWeek() + Thursday) % DAYSPERWEEK  &&  tMailTime.GetTime() % SECONDSPERDAY >= pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY) || (tMailTime.GetDayOfWeek() + Thursday) % DAYSPERWEEK > (pReportInfo[0]->GetMailTime().GetDayOfWeek() + Thursday) % DAYSPERWEEK)
							{
								dwTimeout = 0;
								break;
							}
							for (dwDelta = (tMailTime.GetDayOfWeek() != pReportInfo[0]->GetMailTime().GetDayOfWeek()) ? (DWORD)((SECONDSPERDAY - tMailTime.GetTime() % SECONDSPERDAY) + ((pReportInfo[0]->GetMailTime().GetDayOfWeek() + Thursday) % DAYSPERWEEK - (tMailTime.GetDayOfWeek() + Thursday) % DAYSPERWEEK - 1)*SECONDSPERDAY + pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY) : (DWORD)(pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY - tMailTime.GetTime() % SECONDSPERDAY); dwTimeout > dwDelta || dwTimeout == INFINITE; )
							{
								dwTimeout = dwDelta;
								break;
							}
							continue;
						}
						for (dwDelta = (DWORD)((DAYSPERWEEK - ((tMailTime.GetDayOfWeek() + Thursday) % DAYSPERWEEK) - 1)*SECONDSPERDAY + (SECONDSPERDAY - tMailTime.GetTime() % SECONDSPERDAY) + ((pReportInfo[0]->GetMailTime().GetDayOfWeek() + Thursday) % DAYSPERWEEK)*SECONDSPERDAY + pReportInfo[0]->GetMailTime().GetTime() % SECONDSPERDAY); dwTimeout > dwDelta || dwTimeout == INFINITE; )
						{
							dwTimeout = dwDelta;
							break;
						}
						continue;
					}
				}
			}
			if ((pReportInfo[0] = m_pReports[0]->GetAt(nReport)))
			{
				for (pReportInfo[0]->SetMailFileName(EMPTYSTRING); cFileFind[0].FindFile(pReportInfo[0]->GetOutputFileName()) && !cFileFind[0].FindNextFile(); )
				{
					if ((pReportInfo[0]->GetMailRecipients(szRecipients) > 0 || pReportInfo[0]->GetMailRecipients(pRecipients) > 0) && GetTempPath(sizeof(szPath) / sizeof(TCHAR), szPath) > 0)
					{
						for (szFileName[0].Format((pReportInfo[0]->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILDAILY) ? STRING(IDS_TELEMETRYREPORTS_SERVICE_DAILY_FILEFORMAT) : STRING(IDS_TELEMETRYREPORTS_SERVICE_WEEKLY_FILEFORMAT), szPath + cFileFind[0].GetFileTitle(), (pReportInfo[0]->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILDAILY) ? (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)) : (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)), (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_YEAR)), (LPCTSTR)pReportInfo[0]->GetOutputFileName().Right(max(cFileFind[0].GetFileName().GetLength() - cFileFind[0].GetFileTitle().GetLength() - 1, 0))), szFileName[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_DAYS_FILEFORMAT), szPath + cFileFind[0].GetFileTitle(), (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)), (INT)(pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds() / SECONDSPERDAY), (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_YEAR)), (LPCTSTR)pReportInfo[0]->GetOutputFileName().Right(max(cFileFind[0].GetFileName().GetLength() - cFileFind[0].GetFileTitle().GetLength() - 1, 0))), szFileName[0] = (((pReportInfo[0]->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILDAILY) && pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds() <= SECONDSPERDAY) || (pReportInfo[0]->GetOptions() & TELEMETRYREPORTINFO_OPTION_MAILWEEKLY)) ? szFileName[0] : szFileName[1]; CFileEx::Copy(pReportInfo[0]->GetOutputFileName(), szFileName[0]); )
						{
							pReportInfo[0]->SetMailFileName(szFileName[0]);
							break;
						}
					}
					cFileFind[0].Close();
					break;
				}
				if (((nOptions = pReportInfo[0]->GetOptions()) & TELEMETRTREPORTINFO_OPTION_KEEPALLFILES) != TELEMETRTREPORTINFO_OPTION_KEEPALLFILES)
				{
					if (cFileFind[0].FindFile(pReportInfo[0]->GetOutputFileName()) && !cFileFind[0].FindNextFile())
					{
						CFileEx::Remove(cFileFind[0].GetFilePath());
						cFileFind[0].Close();
					}
				}
				if (nOptions & TELEMETRTREPORTINFO_OPTION_KEEPALLFILES)
				{
					if (cFileFind[0].FindFile(pReportInfo[0]->GetOutputFileName()) && !cFileFind[0].FindNextFile())
					{
						if ((nOptions & TELEMETRYREPORTINFO_OPTION_MAILDAILY) || (nOptions & TELEMETRYREPORTINFO_OPTION_MAILWEEKLY))
						{
							for (szFileName[0].Format((nOptions & TELEMETRYREPORTINFO_OPTION_MAILDAILY) ? STRING(IDS_TELEMETRYREPORTS_SERVICE_DAILY_FILEFORMAT) : STRING(IDS_TELEMETRYREPORTS_SERVICE_WEEKLY_FILEFORMAT), cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - (cFileFind[0].GetFileName().GetLength() - cFileFind[0].GetFileTitle().GetLength())), (nOptions & TELEMETRYREPORTINFO_OPTION_MAILDAILY) ? (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)) : (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)), (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_YEAR)), (LPCTSTR)pReportInfo[0]->GetOutputFileName().Right(max(cFileFind[0].GetFileName().GetLength() - cFileFind[0].GetFileTitle().GetLength() - 1, 0))), szFileName[1].Format(STRING(IDS_TELEMETRYREPORTS_SERVICE_DAYS_FILEFORMAT), cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - (cFileFind[0].GetFileName().GetLength() - cFileFind[0].GetFileTitle().GetLength())), (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)), (INT)(pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds() / SECONDSPERDAY), (LPCTSTR)pReportInfo[0]->GetLastMailTime().FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_YEAR)), (LPCTSTR)pReportInfo[0]->GetOutputFileName().Right(max(cFileFind[0].GetFileName().GetLength() - cFileFind[0].GetFileTitle().GetLength() - 1, 0))), szFileName[0] = (((nOptions & TELEMETRYREPORTINFO_OPTION_MAILDAILY) && pReportInfo[0]->GetMailTimeInterval().GetTotalSeconds() <= SECONDSPERDAY) || (nOptions & TELEMETRYREPORTINFO_OPTION_MAILWEEKLY)) ? szFileName[0] : szFileName[1]; cFileFind[1].FindFile(pReportInfo[0]->GetOutputFileName()); )
							{
								CFileEx::Move(pReportInfo[0]->GetOutputFileName(), szFileName[0]);
								cFileFind[1].Close();
								break;
							}
						}
						cFileFind[0].Close();
					}
				}
				if ((pReportInfo[1] = new CTelemetryReportInfo))
				{
					for (pReportInfo[1]->Copy(pReportInfo[0]); m_pReports[1]->Lock(); )
					{
						pReportInfo[1]->SetStatus(TELEMETRYREPORTINFO_STATUS_EXECUTING);
						m_pReports[1]->InsertAt(0, pReportInfo[1], 1);
						m_pReports[1]->Unlock();
						break;
					}
				}
				DoNotifyByEMail(pReportInfo[0]);
				pReportInfo[0]->SetLastMailTime(tMailTime);
			}
			m_pReports[0]->Unlock();
			break;
		}
		for (pReportInfo[0] = (CTelemetryReportInfo *)NULL; m_pReports[1]->Lock(); )
		{
			for (nReport = 0, nReports = (INT)m_pReports[1]->GetSize(); nReport < nReports; nReport++)
			{
				if ((pReportInfo[1] = m_pReports[1]->GetAt(nReport)) != (CTelemetryReportInfo *)NULL)
				{
					for (nRecipient = 0, nRecipients = pReportInfo[1]->GetMailRecipients(pRecipients), bRecipients = FALSE; nRecipient < nRecipients; nRecipient++)
					{
						if ((pRecipientInfo = pRecipients.GetAt(nRecipient)) != (CTelemetryReportFTPRecipientInfo *)NULL  &&  pRecipientInfo->IsEnabled())
						{
							if ((pReportInfo[1]->GetStatus() == TELEMETRYREPORTINFO_STATUS_EXECUTING  &&  pRecipientInfo->GetRetryTime() == 0 && pRecipientInfo->GetRetryCount() == 0) || (pRecipientInfo->GetRetryTime() > 0 && pRecipientInfo->GetRetryTime() <= CTime::GetCurrentTime()))
							{
								if ((pReportInfo[0] = new CTelemetryReportInfo) != (CTelemetryReportInfo *)NULL)
								{
									pReportInfo[1]->SetStatus(TELEMETRYREPORTINFO_STATUS_EXECUTING);
									pReportInfo[0]->Copy(pReportInfo[1]);
									bRecipients = TRUE;
									break;
								}
							}
							bRecipients = ((pReportInfo[1]->GetStatus() != TELEMETRYREPORTINFO_STATUS_EXECUTING  &&  pRecipientInfo->GetRetryTime() == 0 && pRecipientInfo->GetRetryCount() == 0) || pRecipientInfo->GetRetryTime() > 0) ? TRUE : bRecipients;
						}
					}
					if ((!pReportInfo[1]->GetHistoricalPeriod(tHistoricalTime[0], tHistoricalTime[1], tHistoricalInterval) || nRecipients > 0) && !bRecipients)
					{
						for (; (pReportInfo[1]->GetOptions() & TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE) != TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE; )
						{
							DoDeleteMailFile(pReportInfo[1]);
							break;
						}
						m_pReports[1]->RemoveAt(nReport);
						delete pReportInfo[1];
						nReports--;
						nReport--;
						continue;
					}
					break;
				}
			}
			m_pReports[1]->Unlock();
			break;
		}
		if (pReportInfo[0] != (CTelemetryReportInfo *)NULL)
		{
			DoNotifyByFTP(pReportInfo[0]);
			dwTimeout = 0;
		}
		if (m_pReports[1]->Lock())
		{
			for (nReport = 0, nReports = (INT)m_pReports[1]->GetSize(); nReport < nReports; nReport++)
			{
				if ((pReportInfo[1] = m_pReports[1]->GetAt(nReport)) && pReportInfo[1]->GetStatus() == TELEMETRYREPORTINFO_STATUS_EXECUTING)
				{
					for (nRecipient = 0, nRecipients = pReportInfo[0]->GetMailRecipients(pRecipients); nRecipient < nRecipients; nRecipient++)
					{
						if ((pRecipientInfo = pRecipients.GetAt(nRecipient)) && pRecipientInfo->IsEnabled() && pRecipientInfo->GetRetryTime() > 0) break;
						continue;
					}
					for (pReportInfo[1]->Copy(pReportInfo[0]), pReportInfo[1]->SetStatus(TELEMETRYREPORTINFO_STATUS_QUEUED); nRecipient == nRecipients; )
					{
						for (; (pReportInfo[1]->GetOptions() & TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE) != TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE; )
						{
							DoDeleteMailFile(pReportInfo[1]);
							break;
						}
						m_pReports[1]->RemoveAt(nReport);
						delete pReportInfo[1];
						break;
					}
					delete pReportInfo[0];
					pReportInfo[0] = (CTelemetryReportInfo *)NULL;
					break;
				}
			}
			if (nReport == nReports)
			{
				delete pReportInfo[0];
				pReportInfo[0] = (CTelemetryReportInfo *)NULL;
			}
			for (nReport = 0, nReports = (INT)m_pReports[1]->GetSize(); nReport < nReports; nReport++)
			{
				if ((pReportInfo[1] = m_pReports[1]->GetAt(nReport)) && pReportInfo[1]->GetHistoricalPeriod(tHistoricalTime[0], tHistoricalTime[1], tHistoricalInterval))
				{
					if ((pReportInfo[0] = new CTelemetryReportInfo) != (CTelemetryReportInfo *)NULL)
					{
						pReportInfo[1]->SetStatus(TELEMETRYREPORTINFO_STATUS_EXECUTING);
						pReportInfo[0]->Copy(pReportInfo[1]);
						break;
					}
				}
			}
			m_pReports[1]->Unlock();
		}
		if (pReportInfo[0] != (CTelemetryReportInfo *)NULL)
		{
			if (DoHistoricalReport(pReportInfo[0]))
			{
				DoNotifyByEMail(pReportInfo[0]);
				DoNotifyByFTP(pReportInfo[0]);
			}
			if (((nOptions = pReportInfo[0]->GetOptions()) & TELEMETRYREPORTINFO_OPTION_KEEPINPUTFILES) != TELEMETRYREPORTINFO_OPTION_KEEPINPUTFILES)
			{
				for (szInputFiles = pReportInfo[0]->GetInputFileName(); !szInputFiles.IsEmpty(); )
				{
					nPos[0] = szInputFiles.Find(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_SEMICOLON));
					nPos[1] = szInputFiles.Find(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_COMMA));
					if ((nPos[0] < nPos[1] && nPos[0] >= 0) || (nPos[0] >= 0 && nPos[1] < 0))
					{
						if (cFileFind[0].FindFile(szInputFiles.Left(nPos[0])) && !cFileFind[0].FindNextFile())
						{
							CFileEx::Remove(cFileFind[0].GetFilePath());
							cFileFind[0].Close();
						}
						szInputFiles = szInputFiles.Mid(nPos[0]);
						szInputFiles = szInputFiles.Mid(lstrlen(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_SEMICOLON)));
						continue;
					}
					if ((nPos[0] > nPos[1] && nPos[1] >= 0) || (nPos[1] >= 0 && nPos[0] < 0))
					{
						if (cFileFind[0].FindFile(szInputFiles.Left(nPos[1])) && !cFileFind[0].FindNextFile())
						{
							CFileEx::Remove(cFileFind[0].GetFilePath());
							cFileFind[0].Close();
						}
						szInputFiles = szInputFiles.Mid(nPos[1]);
						szInputFiles = szInputFiles.Mid(lstrlen(STRING(IDS_TELEMETRYREPORTS_FILENAME_SEPARATOR_COMMA)));
						continue;
					}
					if (cFileFind[0].FindFile(szInputFiles) && !cFileFind[0].FindNextFile())
					{
						CFileEx::Remove(cFileFind[0].GetFilePath());
						cFileFind[0].Close();
					}
					break;
				}
			}
			if ((nOptions & TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE) != TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE)
			{
				if (cFileFind[0].FindFile(pReportInfo[0]->GetOutputFileName()) && !cFileFind[0].FindNextFile())
				{
					CFileEx::Remove(cFileFind[0].GetFilePath());
					cFileFind[0].Close();
				}
			}
			dwTimeout = 0;
		}
		if (m_pReports[1]->Lock())
		{
			for (nReport = 0, nReports = (INT)m_pReports[1]->GetSize(); nReport < nReports; nReport++)
			{
				if ((pReportInfo[1] = m_pReports[1]->GetAt(nReport)) && pReportInfo[1]->GetStatus() == TELEMETRYREPORTINFO_STATUS_EXECUTING)
				{
					for (nRecipient = 0, nRecipients = pReportInfo[0]->GetMailRecipients(pRecipients); nRecipient < nRecipients; nRecipient++)
					{
						if ((pRecipientInfo = pRecipients.GetAt(nRecipient)) && pRecipientInfo->IsEnabled() && pRecipientInfo->GetRetryTime() > 0) break;
						continue;
					}
					for (pReportInfo[1]->Copy(pReportInfo[0]), pReportInfo[1]->SetStatus(TELEMETRYREPORTINFO_STATUS_QUEUED); nRecipient == nRecipients; )
					{
						for (; (pReportInfo[1]->GetOptions() & TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE) != TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE; )
						{
							DoDeleteMailFile(pReportInfo[1]);
							break;
						}
						m_pReports[1]->RemoveAt(nReport);
						delete pReportInfo[1];
						break;
					}
					delete pReportInfo[0];
					pReportInfo[0] = (CTelemetryReportInfo *)NULL;
					break;
				}
			}
			if (nReport == nReports)
			{
				delete pReportInfo[0];
				pReportInfo[0] = (CTelemetryReportInfo *)NULL;
			}
			for (nReport = 0, nReports = (INT)m_pReports[1]->GetSize(); nReport < nReports; nReport++)
			{
				if ((pReportInfo[1] = m_pReports[1]->GetAt(nReport)) != (CTelemetryReportInfo *)NULL)
				{
					for (nRecipient = 0, nRecipients = pReportInfo[1]->GetMailRecipients(pRecipients), bRecipients = FALSE; nRecipient < nRecipients; nRecipient++)
					{
						if ((pRecipientInfo = pRecipients.GetAt(nRecipient)) && pRecipientInfo->IsEnabled() && pRecipientInfo->GetRetryTime() > 0)
						{
							if ((tMailTime = CTime::GetCurrentTime().GetTime()) > pRecipientInfo->GetRetryTime())
							{
								bRecipients = TRUE;
								dwTimeout = 0;
								continue;
							}
							dwTimeout = (pRecipientInfo->GetRetryTime().GetTime() - tMailTime.GetTime() < dwTimeout || dwTimeout == INFINITE) ? (DWORD)min(pRecipientInfo->GetRetryTime().GetTime() - tMailTime.GetTime(), SECONDSPERDAY) : dwTimeout;
							bRecipients = TRUE;
						}
					}
					if (!bRecipients)
					{
						for (; (pReportInfo[1]->GetOptions() & TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE) != TELEMETRYREPORTINFO_OPTION_KEEPOUTPUTFILE; )
						{
							DoDeleteMailFile(pReportInfo[1]);
							break;
						}
						m_pReports[1]->RemoveAt(nReport);
						delete pReportInfo[1];
						nReports--;
						nReport--;
					}
				}
			}
			m_pReports[1]->Unlock();
		}
	} while ((dwResult = CThread::Wait(m_bUpdate, FALSE, (dwTimeout != INFINITE) ? (1000 * min(dwTimeout, SECONDSPERDAY)) : INFINITE)) == WAIT_TIMEOUT || dwResult == WAIT_OBJECT_0 + 1);
	return ExitInstance();
}

BOOL CTelemetryReportsService::PreTranslateMessage(MSG *pMsg)
{
	INT  nReport;
	INT  nReports;
	DWORD  dwTimeout;
	CString  szError;
	CTimeKey  tExecutionTime;
	CTimeKey  tScheduleTime[2];
	CTimeSpan  tScheduleInterval;
	CTelemetryReportInfo  *pReportInfo;

	if (pMsg->message == WM_TIMER)
	{
		if (pMsg->wParam == (WPARAM)m_nReportTimerID)
		{
			for (tExecutionTime = CTimeKey(), dwTimeout = INFINITE; m_pReports[0]->Lock(); )
			{
				for (nReport = 0, nReports = (INT)m_pReports[0]->GetSize(); nReport < nReports; nReport++)
				{
					if ((pReportInfo = m_pReports[0]->GetAt(nReport)) && pReportInfo->GetScheduledPeriod(tScheduleTime[0], tScheduleTime[1], tScheduleInterval))
					{
						for (; tScheduleTime[0] <= tExecutionTime && tScheduleTime[1] == 0 && tScheduleInterval == 0 && pReportInfo->GetLastExecutionTime() == 0; )
						{
							DoUpdateReport(pReportInfo);
							break;
						}
						if (tScheduleTime[0] > tExecutionTime  &&  tScheduleTime[1] == 0 && tScheduleInterval == 0 && pReportInfo->GetLastExecutionTime() == 0)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY);
							continue;
						}
						if (tScheduleTime[0].GetTime() % SECONDSPERDAY <= tExecutionTime.GetTime() % SECONDSPERDAY  &&  tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() == SECONDSPERDAY  &&  pReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecutionTime.GetTime() / SECONDSPERDAY)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime(), SECONDSPERDAY);
							pReportInfo->SetLastExecutionTime(tExecutionTime);
							DoUpdateReport(pReportInfo);
							continue;
						}
						if (tScheduleTime[0].GetTime() % SECONDSPERDAY > tExecutionTime.GetTime() % SECONDSPERDAY  &&  tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() == SECONDSPERDAY  &&  pReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecutionTime.GetTime() / SECONDSPERDAY)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime() % SECONDSPERDAY, dwTimeout) : (DWORD)(tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime() % SECONDSPERDAY);
							continue;
						}
						if (tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() == SECONDSPERDAY  &&  pReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY >= tExecutionTime.GetTime() / SECONDSPERDAY)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime(), dwTimeout) : (DWORD)(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime());
							continue;
						}
						if (tScheduleTime[0] <= tExecutionTime && ((tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() != SECONDSPERDAY) || tScheduleTime[1] >= tExecutionTime) && tScheduleInterval > 0)
						{
							if (pReportInfo->GetLastExecutionTime() == 0 || (pReportInfo->GetLastExecutionTime().GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() < (tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds())
							{
								pReportInfo->SetLastExecutionTime(tExecutionTime);
								DoUpdateReport(pReportInfo);
							}
							if (tScheduleTime[1] == 0 || tScheduleTime[0].GetTime() + tScheduleInterval.GetTotalSeconds()*((tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() + 1) <= tScheduleTime[1].GetTime())
							{
								dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(tScheduleTime[0].GetTime() + tScheduleInterval.GetTotalSeconds()*((tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() + 1) - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(tScheduleTime[0].GetTime() + tScheduleInterval.GetTotalSeconds()*((tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() + 1) - tExecutionTime.GetTime(), SECONDSPERDAY);
								continue;
							}
						}
						if (tScheduleTime[0] > tExecutionTime)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY);
							continue;
						}
						pReportInfo->SetScheduledPeriod(0, 0, 0);
						pReportInfo->SetLastExecutionTime(0);
					}
				}
				m_pReports[0]->Unlock();
				break;
			}
			if (m_pReports[2]->Lock())
			{
				for (nReport = 0, nReports = (INT)m_pReports[2]->GetSize(), ShowErrors(m_szErrors); nReport < nReports; nReport++)
				{
					if ((pReportInfo = m_pReports[2]->GetAt(nReport)) && pReportInfo->GetScheduledPeriod(tScheduleTime[0], tScheduleTime[1], tScheduleInterval))
					{
						for (; tScheduleTime[0] <= tExecutionTime && tScheduleTime[1] == 0 && tScheduleInterval == 0 && pReportInfo->GetLastExecutionTime() == 0; )
						{
							DoUpdateReport(pReportInfo);
							break;
						}
						if (tScheduleTime[0] > tExecutionTime  &&  tScheduleTime[1] == 0 && tScheduleInterval == 0 && pReportInfo->GetLastExecutionTime() == 0)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY);
							continue;
						}
						if (tScheduleTime[0].GetTime() % SECONDSPERDAY <= tExecutionTime.GetTime() % SECONDSPERDAY  &&  tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() == SECONDSPERDAY  &&  pReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecutionTime.GetTime() / SECONDSPERDAY)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime(), SECONDSPERDAY);
							pReportInfo->SetLastExecutionTime(tExecutionTime);
							DoUpdateReport(pReportInfo);
							continue;
						}
						if (tScheduleTime[0].GetTime() % SECONDSPERDAY > tExecutionTime.GetTime() % SECONDSPERDAY  &&  tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() == SECONDSPERDAY  &&  pReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecutionTime.GetTime() / SECONDSPERDAY)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime() % SECONDSPERDAY, dwTimeout) : (DWORD)(tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime() % SECONDSPERDAY);
							continue;
						}
						if (tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() == SECONDSPERDAY  &&  pReportInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY >= tExecutionTime.GetTime() / SECONDSPERDAY)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime(), dwTimeout) : (DWORD)(SECONDSPERDAY*(tExecutionTime.GetTime() / SECONDSPERDAY + 1) + tScheduleTime[0].GetTime() % SECONDSPERDAY - tExecutionTime.GetTime());
							continue;
						}
						if (tScheduleTime[0] <= tExecutionTime && ((tScheduleTime[1] == 0 && tScheduleInterval.GetTotalSeconds() != SECONDSPERDAY) || tScheduleTime[1] >= tExecutionTime) && tScheduleInterval > 0)
						{
							if (pReportInfo->GetLastExecutionTime() == 0 || (pReportInfo->GetLastExecutionTime().GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() < (tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds())
							{
								pReportInfo->SetLastExecutionTime(tExecutionTime);
								DoUpdateReport(pReportInfo);
							}
							if (tScheduleTime[1] == 0 || tScheduleTime[0].GetTime() + tScheduleInterval.GetTotalSeconds()*((tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() + 1) <= tScheduleTime[1].GetTime())
							{
								dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(tScheduleTime[0].GetTime() + tScheduleInterval.GetTotalSeconds()*((tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() + 1) - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(tScheduleTime[0].GetTime() + tScheduleInterval.GetTotalSeconds()*((tExecutionTime.GetTime() - tScheduleTime[0].GetTime()) / tScheduleInterval.GetTotalSeconds() + 1) - tExecutionTime.GetTime(), SECONDSPERDAY);
								continue;
							}
						}
						if (tScheduleTime[0] > tExecutionTime)
						{
							dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY), dwTimeout) : (DWORD)min(tScheduleTime[0].GetTime() - tExecutionTime.GetTime(), SECONDSPERDAY);
							continue;
						}
						DeleteJScriptTaskSchedulerTelemetryReport(m_nReportIDs.GetAt(nReport));
						m_pReports[2]->RemoveAt(nReport);
						m_nReportIDs.RemoveAt(nReport);
						delete pReportInfo;
						nReports--;
						nReport--;
					}
				}
				m_szErrors.RemoveAll();
				m_pReports[2]->Unlock();
			}
			if (dwTimeout == INFINITE)
			{
				KillTimer((HWND)NULL, m_nReportTimerID);
				m_nReportTimerID = 0;
				return TRUE;
			}
			for (m_nReportTimerID = SetTimer((HWND)NULL, m_nReportTimerID, 1000 * dwTimeout, NULL); !m_nReportTimerID; )
			{
				m_bUpdate.SetEvent();
				break;
			}
			return TRUE;
		}
	}
	return CThread::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CTelemetryReportsService, CThread)
	//{{AFX_MSG_MAP(CTelemetryReportsService)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsService message handlers


/////////////////////////////////////////////////////////////////////////////
// CNotificationPhoneCallMonitorSink

CNotificationPhoneCallMonitorSink::CNotificationPhoneCallMonitorSink()
{
	m_nCallState = CS_IDLE;
	m_lRefCount = 0;
}

VOID CNotificationPhoneCallMonitorSink::SetCallState(CALL_STATE nState)
{
	m_nCallState = nState;
}

CALL_STATE CNotificationPhoneCallMonitorSink::GetCallState() CONST
{
	return m_nCallState;
}

VOID CNotificationPhoneCallMonitorSink::SetCallDigits(LPCTSTR pszDigits)
{
	m_szCallDigits = pszDigits;
}

CString CNotificationPhoneCallMonitorSink::GetCallDigits() CONST
{
	return m_szCallDigits;
}

HRESULT STDMETHODCALLTYPE CNotificationPhoneCallMonitorSink::Event(TAPI_EVENT nEvent, IDispatch *pEvent)
{
	UCHAR  szDigit;
	ITCallStateEvent  *pCallStateEvent;
	ITDigitDetectionEvent  *pCallDigitEvent;

	if (nEvent == TE_CALLSTATE)
	{
		if (SUCCEEDED(pEvent->QueryInterface(IID_ITCallStateEvent, (void **)&pCallStateEvent)))
		{
			if (SUCCEEDED(pCallStateEvent->get_State(&m_nCallState)))
			{
				pCallStateEvent->Release();
				return S_OK;
			}
			pCallStateEvent->Release();
		}
		return E_FAIL;
	}
	if (nEvent == TE_DIGITEVENT)
	{
		if (SUCCEEDED(pEvent->QueryInterface(IID_ITDigitDetectionEvent, (void **)&pCallDigitEvent)))
		{
			if (SUCCEEDED(pCallDigitEvent->get_Digit(&szDigit)))
			{
				m_szCallDigits += szDigit;
				pCallDigitEvent->Release();
				return S_OK;
			}
			pCallDigitEvent->Release();
		}
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CNotificationPhoneCallMonitorSink::QueryInterface(REFIID iid, void **ppvObject)
{
	if (iid == IID_ITTAPIEventNotification)
	{
		*ppvObject = (void *) this;
		AddRef();
		return S_OK;
	}
	if (iid == IID_IUnknown)
	{
		*ppvObject = (void *) this;
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CNotificationPhoneCallMonitorSink::AddRef()
{
	return InterlockedIncrement(&m_lRefCount);
}

ULONG STDMETHODCALLTYPE CNotificationPhoneCallMonitorSink::Release()
{
	if (!InterlockedDecrement(&m_lRefCount))
	{
		delete this;
		return 0;
	}
	return m_lRefCount;
};


/////////////////////////////////////////////////////////////////////////////
// CNotificationService

IMPLEMENT_DYNCREATE(CNotificationService, CThread)

CNotificationService::CNotificationService() : CThread()
{
	m_lPhoneCallID = 0;
	m_ulPhoneCallAdvise = 0;
	m_pIPhoneCallInterface = (ITTAPI2 *)NULL;
	m_pIPhoneCallAddress = (ITAddress *)NULL;
	m_pPhoneCallMonitor = (CNotificationPhoneCallMonitorSink *)NULL;
	m_bPhoneCall = FALSE;
	m_bPagerCall = FALSE;
	m_bFAXCall = FALSE;
	m_bExit = FALSE;
}

BOOL CNotificationService::Start()
{
	CByteArray  nJobsInfo;
	CProfile  cProfile;

	return((cProfile.GetNotificationJobsInfo(nJobsInfo) && m_pProfiles.Unmap(nJobsInfo)) ? CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CNotificationService::Stop()
{
	CByteArray  nJobsInfo;
	CProfile  cProfile;

	return((DestroyThread() >= 0) ? (m_pProfiles.Map(nJobsInfo) && cProfile.SetNotificationJobsInfo(nJobsInfo)) : FALSE);
}

BOOL CNotificationService::InitInstance()
{
	HANDLE  hDevice;
	CNotificationProfileInfo  cProfileInfo;

	if (CThread::InitInstance())
	{
		for (cProfileInfo.SetType(NOTIFICATIONINFO_TYPE_PHONECALL); (m_bPhoneCall = DoInitializePSTNService(&cProfileInfo));)
		{
			UninitializePSTNService();
			break;
		}
		for (cProfileInfo.SetType(NOTIFICATIONINFO_TYPE_PAGERCALL); (m_bPagerCall = DoInitializePSTNService(&cProfileInfo));)
		{
			UninitializePSTNService();
			break;
		}
		if ((m_bFAXCall = ((hDevice = DoInitializeFaxService()) != (HANDLE) NULL)))
		{
			UninitializeFaxService(hDevice);
		}
		ReportEvent((!IsEMailServiceAvailable()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, STRING(IDS_NOTIFICATION_SERVICE_EMAIL_FAILURE), FALSE);
		ReportEvent((!IsFaxServiceAvailable()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, STRING(IDS_NOTIFICATION_SERVICE_FAX_FAILURE), FALSE);
		ReportEvent((!IsPhoneCallServiceAvailable()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_FAILURE), FALSE);
		ReportEvent((!IsPagerCallServiceAvailable()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_FAILURE), FALSE);
		ReportEvent((!IsFTPMessageServiceAvailable()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FAILURE), FALSE);
		ReportEvent((!IsPrinterMessageServiceAvailable()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_FAILURE), FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL CNotificationService::EnumNotifications(CNotificationProfiles &pProfiles) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pProfiles.Copy(&m_pProfiles);
}

BOOL CNotificationService::AbortNotifications(CONST CNotificationProfiles &pProfiles)
{
	INT  nIndex;
	INT  nCount;
	INT  nProfile;
	INT  nProfiles;
	BOOL  bAbort;
	CNotificationProfileInfo  *pProfileInfo[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProfile = 0, nProfiles = (INT)pProfiles.GetSize(), bAbort = FALSE; nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo[0] = pProfiles.GetAt(nProfile)))
		{
			for (nIndex = 0, nCount = (INT)m_pProfiles.GetSize(); nIndex < nCount; nIndex++)
			{
				if ((pProfileInfo[1] = m_pProfiles.GetAt(nIndex)))
				{
					if (pProfileInfo[1]->Compare(pProfileInfo[0]))
					{
						m_pProfiles.RemoveAt(nIndex);
						delete pProfileInfo[1];
						break;
					}
				}
			}
			if (nIndex < nCount  &&  !nIndex  &&  !bAbort)
			{
				m_bAbort.SetEvent();
				bAbort = TRUE;
			}
		}
	}
	m_bUpdate.SetEvent();
	return TRUE;
}

BOOL CNotificationService::Update(CONST CNotificationProfileInfo *pProfile, LPCTSTR pszMessage)
{
	CNotificationProfileInfo  *pProfileInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProfileInfo = new CNotificationProfileInfo))
	{
		pProfileInfo->Copy(pProfile, FALSE);
		pProfileInfo->SetMessage(pszMessage);
		m_pProfiles.InsertAt(m_pProfiles.GetSize(), pProfileInfo, 1);
		m_bUpdate.SetEvent();
		return TRUE;
	}
	return FALSE;
}

BOOL CNotificationService::DoNotification(CNotificationProfileInfo *pProfileInfo)
{
	BOOL  bSuccess;

	for (; pProfileInfo->GetType() != NOTIFICATIONINFO_TYPE_NONE; )
	{
		if (m_bAbort.ResetEvent())
		{
			m_bExit = FALSE;
			break;
		}
		return FALSE;
	}
	switch (pProfileInfo->GetType())
	{
	case NOTIFICATIONINFO_TYPE_EMAIL:
	{ bSuccess = (IsEMailServiceAvailable()) ? DoNotifyByEMail(pProfileInfo) : FALSE;
	break;
	}
	case NOTIFICATIONINFO_TYPE_FAX:
	{ bSuccess = (IsFaxServiceAvailable()) ? DoNotifyByFax(pProfileInfo) : FALSE;
	break;
	}
	case NOTIFICATIONINFO_TYPE_PHONECALL:
	{ bSuccess = (IsPhoneCallServiceAvailable()) ? DoNotifyByPhoneCall(pProfileInfo) : FALSE;
	break;
	}
	case NOTIFICATIONINFO_TYPE_PAGERCALL:
	{ bSuccess = (IsPagerCallServiceAvailable()) ? DoNotifyByPagerCall(pProfileInfo) : FALSE;
	break;
	}
	case NOTIFICATIONINFO_TYPE_FTPMESSAGE:
	{ bSuccess = (IsFTPMessageServiceAvailable()) ? DoNotifyByFTPMessage(pProfileInfo) : FALSE;
	break;
	}
	case NOTIFICATIONINFO_TYPE_PRINTERMESSAGE:
	{ bSuccess = (IsPrinterMessageServiceAvailable()) ? DoNotifyByPrinterMessage(pProfileInfo) : FALSE;
	break;
	}
	default:
	{ bSuccess = FALSE;
	break;
	}
	}
	return bSuccess;
}

BOOL CNotificationService::DoNotifyByEMail(CNotificationProfileInfo *pProfileInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nCount;
	INT  nAttachment;
	INT  nAttachments;
	UINT  nWeekDays;
	UINT  nRetryCount;
	BOOL  bWorkingDays;
	CString  szSubject;
	CString  szLine[3];
	CString  szAddresses;
	CString  szAttachment;
	CString  szMessage[2];
	CString  szUsers[2];
	CString  szUser;
	CTimeKey  tTime;
	CTimeKey  tMission[2];
	CTimeKey  tHoliday[2];
	CTimeSpan  tDayHours[2];
	CTimeSpan  tRetryInterval;
	CTimeSpan  tAbortInterval;
	CFileFindEx  cFileFind;
	CVersionInfo  cVersionInfo;
	CStringArray  szRecipients[3];
	CStringArray  szAttachments[2];
	CUserProfiles  pRecipientsAddresses;
	CUserProfileInfo  *pRecipientAddressInfo;
	CUserAddressBook  cRecipientsAddressBook;
	CComputerToken  cComputerToken;

	for (nUser = 0, nUsers = (cRecipientsAddressBook.GetUserAddressBook(pRecipientsAddresses)) ? pProfileInfo->GetRecipients(szRecipients[0]) : -1; nUser < nUsers; nUser++)
	{
		if ((pRecipientAddressInfo = pRecipientsAddresses.GetAt(pRecipientsAddresses.Find(szRecipients[0].GetAt(nUser)))))
		{
			if (pRecipientAddressInfo->GetOfficeHours(nWeekDays, tDayHours[0], tDayHours[1]))
			{
				if ((((nWeekDays & USERPROFILE_WORKDAY_MONDAY) && tTime.GetDayOfWeek() == Monday) || ((nWeekDays & USERPROFILE_WORKDAY_TUESDAY) && tTime.GetDayOfWeek() == Tuesday) || ((nWeekDays & USERPROFILE_WORKDAY_WEDNESDAY) && tTime.GetDayOfWeek() == Wednesday) || ((nWeekDays & USERPROFILE_WORKDAY_THURSDAY) && tTime.GetDayOfWeek() == Thursday) || ((nWeekDays & USERPROFILE_WORKDAY_FRIDAY) && tTime.GetDayOfWeek() == Friday) || ((nWeekDays & USERPROFILE_WORKDAY_SATURDAY) && tTime.GetDayOfWeek() == Saturday) || ((nWeekDays & USERPROFILE_WORKDAY_SUNDAY) && tTime.GetDayOfWeek() == Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
					szRecipients[2].Add(pRecipientAddressInfo->GetOfficeEMail());
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHomeHours(tDayHours[0], tDayHours[1], bWorkingDays))
			{
				if ((!bWorkingDays || (tTime.GetDayOfWeek() != Saturday && tTime.GetDayOfWeek() != Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHomeEMail());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHomeEMail());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetMission(tMission[0], tMission[1]))
			{
				if (tTime >= tMission[0].GetTime() && tTime <= tMission[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetMissionEMail());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetMissionEMail());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHoliday(tHoliday[0], tHoliday[1]))
			{
				if (tTime >= tHoliday[0].GetTime() && tTime <= tHoliday[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHolidayEMail());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHolidayEMail());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
		}
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), nCount = 0; nUser < nUsers; nUser++)
	{
		szUser.Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_PARTSTEXT), (LPCTSTR)szRecipients[1].GetAt(nUser));
		if (!szRecipients[2].GetAt(nUser).IsEmpty())
		{
			szUsers[0] += (!szUsers[0].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SEPARATOR)) + SPACE + szUser) : szUser;
			szAddresses += (!szAddresses.IsEmpty()) ? (STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SEPARATOR) + szRecipients[2].GetAt(nUser)) : szRecipients[2].GetAt(nUser);
			continue;
		}
		szUsers[1] += (!szUsers[1].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SEPARATOR)) + SPACE + szUser) : szUser;
		nCount++;
	}
	if (nUsers > 0)
	{
		for (nAttachment = 0, nAttachments = pProfileInfo->GetAttachments(szAttachments[0]); nAttachment < nAttachments; nAttachment++)
		{
			if (cFileFind.FindFile(szAttachments[0].GetAt(nAttachment)))
			{
				if (nAttachment > 0)
				{
					szAttachments[0].SetAt(0, szAttachments[0].GetAt(0) + STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SEPARATOR) + szAttachments[0].GetAt(nAttachment));
				}
				cFileFind.Close();
				continue;
			}
			szAttachments[1].Add(szAttachments[0].GetAt(nAttachment));
			szAttachments[0].RemoveAt(nAttachment);
			nAttachments--;
			nAttachment--;
		}
		for (szSubject.Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SUBJECT), (LPCTSTR)cVersionInfo.QueryProductName()), szLine[0].Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_TITLETEXT), (LPCTSTR)cVersionInfo.QueryProductName()), szLine[1].Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SUBTITLETEXT), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tTime.FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)), (LPCTSTR)tTime.FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT))), szLine[2].Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_MESSAGETEXT), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)cComputerToken.GetComputerName()), szMessage[0] = GetEMailSystem()->Send(szSubject, szLine[0] + CString(CR) + CString(EOL) + szLine[1] + CString(CR) + CString(EOL) + CString(CR) + CString(EOL) + CString(CR) + CString(EOL) + ((!pProfileInfo->GetProlog().IsEmpty()) ? (pProfileInfo->GetProlog() + CR + EOL) : EMPTYSTRING) + ((!pProfileInfo->GetMessage().IsEmpty()) ? (pProfileInfo->GetMessage() + CR + EOL) : EMPTYSTRING) + ((!pProfileInfo->GetEpilog().IsEmpty()) ? (pProfileInfo->GetEpilog() + CR + EOL) : EMPTYSTRING) + CR + EOL + szLine[2], szAddresses, (szAttachments[0].GetSize() > 0) ? szAttachments[0].GetAt(0) : EMPTYSTRING, (pProfileInfo->GetPriority() == NOTIFICATIONINFO_PRIORITY_LOW) ? CSMTPMessage::LowPriority : ((pProfileInfo->GetPriority() == NOTIFICATIONINFO_PRIORITY_NORMAL) ? CSMTPMessage::NormalPriority : ((pProfileInfo->GetPriority() == NOTIFICATIONINFO_PRIORITY_HIGH) ? CSMTPMessage::HighPriority : CSMTPMessage::NoPriority))); szMessage[0].IsEmpty(); )
		{
			if (pProfileInfo->GetOptions() == NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING)
			{
				szMessage[0].Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SENDSUCCESS), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)szUsers[0]);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage[0], FALSE);
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				if (szAttachments[1].GetSize() > 0)
				{
					for (nAttachment = 0, nAttachments = (INT)szAttachments[1].GetSize(); nAttachment < nAttachments; nAttachment++)
					{
						for (szAttachment.Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_PARTSTEXT), (LPCTSTR)szAttachments[1].GetAt(nAttachment)); nAttachments == 1; )
						{
							szAttachment = szAttachments[1].GetAt(nAttachment);
							break;
						}
						szAttachments[1].SetAt(0, (nAttachment > 0) ? (szAttachments[1].GetAt(0) + STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SEPARATOR) + szAttachment) : szAttachment);
					}
					szMessage[1].Format((nAttachments > 1) ? STRING(IDS_NOTIFICATION_SERVICE_EMAIL_ATTACHMENTSFAILURE) : STRING(IDS_NOTIFICATION_SERVICE_EMAIL_ATTACHMENTFAILURE), (LPCTSTR)szAttachments[1].GetAt(0), (LPCTSTR)pProfileInfo->GetName());
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[1], FALSE);
				}
			}
			return TRUE;
		}
		if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
		{
			for (ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[0], FALSE); !szUsers[0].IsEmpty(); )
			{
				szMessage[1].Format(STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SENDFAILURE), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)szUsers[0]);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[1], FALSE);
				break;
			}
			if (!szUsers[1].IsEmpty())
			{
				szMessage[1].Format((nCount > 1) ? STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SENDFAILURE_NODELIVERIES) : STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SENDFAILURE_NODELIVERY), (LPCTSTR)szUsers[1], (LPCTSTR)pProfileInfo->GetName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[1], FALSE);
			}
		}
		if (pProfileInfo->GetBehaviorInfo(nRetryCount, tRetryInterval, tAbortInterval))
		{
			if (nRetryCount > pProfileInfo->GetRetryCount())
			{
				pProfileInfo->SetRetryTime(tTime.GetTime() + tRetryInterval.GetTotalSeconds());
				pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
				return FALSE;
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				szMessage[1].Format((pProfileInfo->GetRetryCount() > 1) ? STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SENDFAILURE_RETRIES) : STRING(IDS_NOTIFICATION_SERVICE_EMAIL_SENDFAILURE_RETRY), (LPCTSTR)pProfileInfo->GetName(), pProfileInfo->GetRetryCount());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage[1], FALSE);
			}
			pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
		}
	}
	return FALSE;
}

BOOL CNotificationService::DoNotifyByFax(CNotificationProfileInfo *pProfileInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nCount;
	INT  nEvent;
	INT  nEvents;
	UINT  nWeekDays;
	UINT  nRetryCount;
	BOOL  bWorkingDays;
	BOOL  bSuccess;
	DWORD  cbFAXEvent;
	DWORD  dwStatus[2];
	DWORD  dwJobId;
	HANDLE  hDevice;
	HANDLE  hFAXPort;
	CString  szTitle;
	CString  szSender;
	CString  szMessage;
	CString  szAddresses;
	CString  szUsers[2];
	CString  szUser;
	CTimeKey  tTime;
	CTimeKey  tMission[2];
	CTimeKey  tHoliday[2];
	CTimeSpan  tDayHours[2];
	CTimeSpan  tRetryInterval;
	CTimeSpan  tAbortInterval;
	CTimeSpan  tFAXDelay;
	ULONG_PTR  nFAXKey;
	CPtrArray  pFAXEvents;
	FAX_EVENT  *pFAXEvent;
	CStringArray  szRecipients[3];
	CUserProfiles  pRecipientsAddresses;
	CUserProfileInfo  *pRecipientAddressInfo;
	CUserAddressBook  cRecipientsAddressBook;
	PFAX_CONFIGURATION  pFAXConfigurationInfo;
	FAX_CONTEXT_INFO  sFAXContextInfo;
	FAX_PRINT_INFO  sFAXPrintInfo;
	CComputerToken  cComputerToken;
	CVersionInfo  cVersionInfo;

	for (nUser = 0, nUsers = (cRecipientsAddressBook.GetUserAddressBook(pRecipientsAddresses)) ? pProfileInfo->GetRecipients(szRecipients[0]) : -1; nUser < nUsers; nUser++)
	{
		if ((pRecipientAddressInfo = pRecipientsAddresses.GetAt(pRecipientsAddresses.Find(szRecipients[0].GetAt(nUser)))))
		{
			if (pRecipientAddressInfo->GetOfficeHours(nWeekDays, tDayHours[0], tDayHours[1]))
			{
				if ((((nWeekDays & USERPROFILE_WORKDAY_MONDAY) && tTime.GetDayOfWeek() == Monday) || ((nWeekDays & USERPROFILE_WORKDAY_TUESDAY) && tTime.GetDayOfWeek() == Tuesday) || ((nWeekDays & USERPROFILE_WORKDAY_WEDNESDAY) && tTime.GetDayOfWeek() == Wednesday) || ((nWeekDays & USERPROFILE_WORKDAY_THURSDAY) && tTime.GetDayOfWeek() == Thursday) || ((nWeekDays & USERPROFILE_WORKDAY_FRIDAY) && tTime.GetDayOfWeek() == Friday) || ((nWeekDays & USERPROFILE_WORKDAY_SATURDAY) && tTime.GetDayOfWeek() == Saturday) || ((nWeekDays & USERPROFILE_WORKDAY_SUNDAY) && tTime.GetDayOfWeek() == Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
					szRecipients[2].Add(pRecipientAddressInfo->GetOfficeFAX());
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHomeHours(tDayHours[0], tDayHours[1], bWorkingDays))
			{
				if ((!bWorkingDays || (tTime.GetDayOfWeek() != Saturday && tTime.GetDayOfWeek() != Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHomeFAX());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHomeFAX());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetMission(tMission[0], tMission[1]))
			{
				if (tTime >= tMission[0].GetTime() && tTime <= tMission[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetMissionFAX());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetMissionFAX());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHoliday(tHoliday[0], tHoliday[1]))
			{
				if (tTime >= tHoliday[0].GetTime() && tTime <= tHoliday[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHolidayFAX());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHolidayFAX());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
		}
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), nCount = 0; nUser < nUsers; nUser++)
	{
		szUser.Format(STRING(IDS_NOTIFICATION_SERVICE_FAX_PARTSTEXT), (LPCTSTR)szRecipients[1].GetAt(nUser));
		if (!szRecipients[2].GetAt(nUser).IsEmpty())
		{
			szUsers[0] += (!szUsers[0].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_FAX_SEPARATOR)) + SPACE + szUser) : szUser;
			szAddresses += (!szAddresses.IsEmpty()) ? (STRING(IDS_NOTIFICATION_SERVICE_FAX_SEPARATOR) + szRecipients[2].GetAt(nUser)) : szRecipients[2].GetAt(nUser);
			continue;
		}
		szUsers[1] += (!szUsers[1].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_FAX_SEPARATOR)) + SPACE + szUser) : szUser;
		szRecipients[1].RemoveAt(nUser);
		szRecipients[2].RemoveAt(nUser);
		nCount++;
		nUsers--;
		nUser--;
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), bSuccess = TRUE; nUser < nUsers && Wait(0); nUser++)
	{
		szTitle.Format(STRING(IDS_NOTIFICATION_SERVICE_FAX_SUBJECT), (LPCTSTR)cVersionInfo.QueryProductName());
		szSender.Format(STRING(IDS_NOTIFICATION_SERVICE_FAX_SENDER), (LPCTSTR)cVersionInfo.QueryProductName(), (LPCTSTR)cComputerToken.GetComputerName());
		sFAXContextInfo.SizeOfStruct = sizeof(sFAXContextInfo);
		sFAXPrintInfo.SizeOfStruct = sizeof(sFAXPrintInfo);
		sFAXPrintInfo.DocName = (LPCTSTR)szTitle;
		sFAXPrintInfo.RecipientName = (LPCTSTR)(szUser = szRecipients[1].GetAt(nUser));
		sFAXPrintInfo.RecipientNumber = (LPCTSTR)szRecipients[2].GetAt(nUser);
		sFAXPrintInfo.SenderName = (LPCTSTR)szSender;
		sFAXPrintInfo.SenderCompany = (LPCTSTR)NULL;
		sFAXPrintInfo.SenderDept = (LPCTSTR)NULL;
		sFAXPrintInfo.SenderBillingCode = (LPCTSTR)NULL;
		sFAXPrintInfo.DrEmailAddress = (LPCTSTR)NULL;
		sFAXPrintInfo.OutputFileName = (LPCTSTR)NULL;
		sFAXPrintInfo.Reserved = (LPCTSTR)NULL;
		if ((hDevice = DoInitializeFaxService()))
		{
			if (FaxGetConfiguration(hDevice, &pFAXConfigurationInfo))
			{
				pFAXConfigurationInfo->Retries = 0;
				pFAXConfigurationInfo->RetryDelay = 0;
				pFAXConfigurationInfo->DirtyDays = 0;
				pFAXConfigurationInfo->ArchiveOutgoingFaxes = TRUE;
				if (FaxSetConfiguration(hDevice, pFAXConfigurationInfo))
				{
					if ((hFAXPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, (HANDLE)NULL, 0, 0)))
					{
						if (FaxInitializeEventQueue(hDevice, hFAXPort, 0, (HWND)NULL, 0) && FaxStartPrintJob((LPCTSTR)NULL, &sFAXPrintInfo, &dwJobId, &sFAXContextInfo) && DoFaxTransmission(pProfileInfo, &sFAXContextInfo))
						{
							try
							{
								for (pFAXEvents.RemoveAll(), pFAXEvent = (FAX_EVENT *)NULL, dwStatus[0] = dwStatus[1] = 0, tFAXDelay = 0; Wait(1000); dwStatus[1] = (dwStatus[0] != dwStatus[1]) ? dwStatus[0] : dwStatus[1])
								{
									if (GetQueuedCompletionStatus(hFAXPort, &cbFAXEvent, (PULONG_PTR)&nFAXKey, (LPOVERLAPPED *)&pFAXEvent, 1000))
									{
										for (nEvent = 0, nEvents = (INT)pFAXEvents.GetSize(); nEvent < nEvents; nEvent++)
										{
											if (pFAXEvent == pFAXEvents.GetAt(nEvent)) break;
											continue;
										}
										for (dwStatus[0] = pFAXEvent->EventId; nEvent == nEvents; )
										{
											pFAXEvents.Add(pFAXEvent);
											break;
										}
										if (dwStatus[0] == FEI_IDLE) break;
										if (dwStatus[0] == FEI_BUSY) break;
										if (dwStatus[0] == FEI_NO_ANSWER) break;
										if (dwStatus[0] == FEI_BAD_ADDRESS) break;
										if (dwStatus[0] == FEI_NO_DIAL_TONE) break;
										if (dwStatus[0] == FEI_CALL_DELAYED) break;
										if (dwStatus[0] == FEI_CALL_BLACKLISTED) break;
										if (dwStatus[0] == FEI_LINE_UNAVAILABLE) break;
										if (dwStatus[0] == FEI_MODEM_POWERED_ON) break;
										if (dwStatus[0] == FEI_MODEM_POWERED_OFF) break;
										if (dwStatus[0] == FEI_FAXSVC_ENDED) break;
										if (dwStatus[0] == FEI_DISCONNECTED) break;
										if (dwStatus[0] == FEI_FATAL_ERROR) break;
										if (dwStatus[0] == FEI_COMPLETED) break;
										if (dwStatus[0] == FEI_ABORTING) break;
										tFAXDelay = 0;
										continue;
									}
									if ((tFAXDelay = tFAXDelay.GetTotalSeconds() + 1) > SECONDSPERMINUTE  &&  dwStatus[0] != FEI_SENDING) break;
								}
							}
							catch (...)
							{
								dwStatus[0] = FEI_ABORTING;
							}
							if ((dwStatus[0] == FEI_IDLE  &&  dwStatus[1] != FEI_DIALING) || dwStatus[0] == FEI_COMPLETED)
							{
								if (pProfileInfo->GetOptions() == NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING)
								{
									szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_FAX_SUCCESSFULCALL), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
									ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
									break;
								}
								for (nEvent = 0, nEvents = (INT)pFAXEvents.GetSize(), CloseHandle(hFAXPort), UninitializeFaxService(hDevice), FaxFreeBuffer(pFAXConfigurationInfo); nEvent < nEvents; nEvent++)
								{
									if ((pFAXEvent = (FAX_EVENT *)pFAXEvents.GetAt(nEvent)))
									{
										LocalFree(pFAXEvent);
										continue;
									}
								}
								pFAXEvents.RemoveAll();
								continue;
							}
							for (nEvent = 0, nEvents = (INT)pFAXEvents.GetSize(); nEvent < nEvents; nEvent++)
							{
								if ((pFAXEvent = (FAX_EVENT *)pFAXEvents.GetAt(nEvent)))
								{
									LocalFree(pFAXEvent);
									continue;
								}
							}
							pFAXEvents.RemoveAll();
						}
						CloseHandle(hFAXPort);
					}
				}
				FaxFreeBuffer(pFAXConfigurationInfo);
			}
			UninitializeFaxService(hDevice);
		}
		if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
		{
			szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_FAX_FAILEDCALL), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		if (pProfileInfo->GetBehaviorInfo(nRetryCount, tRetryInterval, tAbortInterval))
		{
			if (nRetryCount > pProfileInfo->GetRetryCount())
			{
				pProfileInfo->SetRetryTime(tTime.GetTime() + tRetryInterval.GetTotalSeconds());
				pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
				bSuccess = FALSE;
				continue;
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				szMessage.Format((pProfileInfo->GetRetryCount() > 1) ? STRING(IDS_NOTIFICATION_SERVICE_FAX_FAILURE_RETRIES) : STRING(IDS_NOTIFICATION_SERVICE_FAX_FAILURE_RETRY), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)szUser, pProfileInfo->GetRetryCount());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			}
			pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
		}
		bSuccess = FALSE;
	}
	if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
	{
		if (!szUsers[1].IsEmpty())
		{
			szMessage.Format((nCount > 1) ? STRING(IDS_NOTIFICATION_SERVICE_FAX_FAILURE_NODELIVERIES) : STRING(IDS_NOTIFICATION_SERVICE_FAX_FAILURE_NODELIVERY), (LPCTSTR)szUsers[1], (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			bSuccess = FALSE;
		}
	}
	return bSuccess;
}

BOOL CNotificationService::DoNotifyByPhoneCall(CNotificationProfileInfo *pProfileInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nCount;
	UINT  nWeekDays;
	UINT  nRetryCount;
	BOOL  bWorkingDays;
	BOOL  bSuccess;
	BSTR  pszAddress;
	LPWSTR  pszGrammar;
	CString  szMessage;
	CString  szAddresses;
	CString  szUsers[2];
	CString  szUser;
	CTimeKey  tTime;
	CTimeKey  tMission[2];
	CTimeKey  tHoliday[2];
	CTimeSpan  tDayHours[2];
	CTimeSpan  tRetryInterval;
	CTimeSpan  tAbortInterval;
	CStringArray  szRecipients[3];
	CUserProfiles  pRecipientsAddresses;
	CUserProfileInfo  *pRecipientAddressInfo;
	CUserAddressBook  cRecipientsAddressBook;
	ITBasicCallControl  *pIBasicCallControl;
	ITLegacyCallMediaControl2  *pILegacyCallMediaControl;

	for (nUser = 0, nUsers = (cRecipientsAddressBook.GetUserAddressBook(pRecipientsAddresses)) ? pProfileInfo->GetRecipients(szRecipients[0]) : -1; nUser < nUsers; nUser++)
	{
		if ((pRecipientAddressInfo = pRecipientsAddresses.GetAt(pRecipientsAddresses.Find(szRecipients[0].GetAt(nUser)))))
		{
			if (pRecipientAddressInfo->GetOfficeHours(nWeekDays, tDayHours[0], tDayHours[1]))
			{
				if ((((nWeekDays & USERPROFILE_WORKDAY_MONDAY) && tTime.GetDayOfWeek() == Monday) || ((nWeekDays & USERPROFILE_WORKDAY_TUESDAY) && tTime.GetDayOfWeek() == Tuesday) || ((nWeekDays & USERPROFILE_WORKDAY_WEDNESDAY) && tTime.GetDayOfWeek() == Wednesday) || ((nWeekDays & USERPROFILE_WORKDAY_THURSDAY) && tTime.GetDayOfWeek() == Thursday) || ((nWeekDays & USERPROFILE_WORKDAY_FRIDAY) && tTime.GetDayOfWeek() == Friday) || ((nWeekDays & USERPROFILE_WORKDAY_SATURDAY) && tTime.GetDayOfWeek() == Saturday) || ((nWeekDays & USERPROFILE_WORKDAY_SUNDAY) && tTime.GetDayOfWeek() == Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
					szRecipients[2].Add(pRecipientAddressInfo->GetOfficePhone());
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHomeHours(tDayHours[0], tDayHours[1], bWorkingDays))
			{
				if ((!bWorkingDays || (tTime.GetDayOfWeek() != Saturday && tTime.GetDayOfWeek() != Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHomePhone());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHomePhone());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetMission(tMission[0], tMission[1]))
			{
				if (tTime >= tMission[0].GetTime() && tTime <= tMission[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						for (szRecipients[1].Add(pRecipientAddressInfo->GetFullName()), szRecipients[2].Add(pRecipientAddressInfo->GetMissionMobile()); szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty(); )
						{
							szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetMissionPhone());
							break;
						}
					}
					else
					{
						for (szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetMissionMobile()); szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty(); )
						{
							szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetMissionPhone());
							break;
						}
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHoliday(tHoliday[0], tHoliday[1]))
			{
				if (tTime >= tHoliday[0].GetTime() && tTime <= tHoliday[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHolidayPhone());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHolidayPhone());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
		}
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), nCount = 0; nUser < nUsers; nUser++)
	{
		szUser.Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_PARTSTEXT), (LPCTSTR)szRecipients[1].GetAt(nUser));
		if (!szRecipients[2].GetAt(nUser).IsEmpty())
		{
			szUsers[0] += (!szUsers[0].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SEPARATOR)) + SPACE + szUser) : szUser;
			szAddresses += (!szAddresses.IsEmpty()) ? (STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SEPARATOR) + szRecipients[2].GetAt(nUser)) : szRecipients[2].GetAt(nUser);
			continue;
		}
		szUsers[1] += (!szUsers[1].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SEPARATOR)) + SPACE + szUser) : szUser;
		szRecipients[1].RemoveAt(nUser);
		szRecipients[2].RemoveAt(nUser);
		nCount++;
		nUsers--;
		nUser--;
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), bSuccess = TRUE; nUser < nUsers && Wait(0); nUser++)
	{
		if ((pRecipientAddressInfo = (DoInitializePSTNService(pProfileInfo)) ? pRecipientsAddresses.GetAt(pRecipientsAddresses.Find((szUser = szRecipients[1].GetAt(nUser)))) : (CUserProfileInfo *)NULL))
		{
			if (SUCCEEDED(m_cIPhoneVoice.CoCreateInstance(CLSID_SpVoice)))
			{
				if (SUCCEEDED(m_cIPhoneVoiceAudioOut.CoCreateInstance(CLSID_SpMMAudioOut)))
				{
					if (SUCCEEDED(m_cIPhoneVoiceAudioIn.CoCreateInstance(CLSID_SpMMAudioIn)))
					{
						if (SUCCEEDED(m_cIPhoneVoiceRecognizer.CoCreateInstance(CLSID_SpInprocRecognizer)))
						{
							if (SUCCEEDED(m_cIPhoneVoiceRecognizer->CreateRecoContext(&m_cIPhoneVoiceRecognizerContext)))
							{
								if (SUCCEEDED(m_cIPhoneVoiceRecognizerContext->SetNotifyWin32Event()) && SUCCEEDED(m_cIPhoneVoiceRecognizerContext->SetInterest(SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION), SPFEI(SPEI_RECOGNITION) | SPFEI(SPEI_FALSE_RECOGNITION))))
								{
									if (SUCCEEDED(m_cIPhoneVoiceRecognizerContext->SetAudioOptions(SPAO_RETAIN_AUDIO, (CONST GUID *) NULL, (CONST WAVEFORMATEX *) NULL)))
									{
										if (SUCCEEDED(m_cIPhoneVoiceRecognizerContext->CreateGrammar(0, &m_cIPhoneVoiceRecognizerGrammar)))
										{
											if ((pszGrammar = (LPWSTR)GlobalAlloc(GPTR, (lstrlen(STRING(IDS_RESOURCETYPE_SPEECHGRAMMAR)) + 1)*sizeof(WCHAR))))
											{
#ifndef UNICODE
												MultiByteToWideChar(CP_ACP, 0, STRING(IDS_RESOURCETYPE_SPEECHGRAMMAR), -1, pszGrammar, lstrlen(STRING(IDS_RESOURCETYPE_SPEECHGRAMMAR)) + 1);
#else
												wcscpy_s(pszGrammar, lstrlen(STRING(IDS_RESOURCETYPE_SPEECHGRAMMAR)) + 1, STRING(IDS_RESOURCETYPE_SPEECHGRAMMAR));
#endif
												if (SUCCEEDED(m_cIPhoneVoiceRecognizerGrammar->LoadCmdFromResource((HMODULE)NULL, MAKEINTRESOURCEW(IDSR_GRAMMAR), pszGrammar, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SPLO_DYNAMIC)) && SUCCEEDED(m_cIPhoneVoiceRecognizerGrammar->SetRuleIdState(0, SPRS_INACTIVE)))
												{
													if (SUCCEEDED(m_pIPhoneCallAddress->CreateCall((pszAddress = szRecipients[2].GetAt(nUser).AllocSysString()), LINEADDRESSTYPE_PHONENUMBER, TAPIMEDIATYPE_AUDIO, &pIBasicCallControl)))
													{
														if (SUCCEEDED(pIBasicCallControl->Connect(VARIANT_FALSE)))
														{
															if (SUCCEEDED(pIBasicCallControl->QueryInterface(IID_ITLegacyCallMediaControl2, (void **)&pILegacyCallMediaControl)))
															{
																if (DoAudioOutForPhoneCall(pILegacyCallMediaControl) && DoAudioInForPhoneCall(pILegacyCallMediaControl))
																{
																	if (DoPhoneCallConversation(pProfileInfo, pRecipientAddressInfo, pILegacyCallMediaControl))
																	{
																		for (pIBasicCallControl->Disconnect(DC_NORMAL); pProfileInfo->GetOptions() == NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING; )
																		{
																			szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SUCCESSFULCALL), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
																			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
																			break;
																		}
																		m_cIPhoneVoiceRecognizerGrammar.Release();
																		m_cIPhoneVoiceRecognizerContext.Release();
																		m_cIPhoneVoiceRecognizer.Release();
																		m_cIPhoneVoiceAudioOut.Release();
																		m_cIPhoneVoiceAudioIn.Release();
																		m_cIPhoneVoice.Release();
																		pILegacyCallMediaControl->Release();
																		pIBasicCallControl->Release();
																		GlobalFree(pszGrammar);
																		SysFreeString(pszAddress);
																		UninitializePSTNService();
																		continue;
																	}
																}
																pILegacyCallMediaControl->Release();
															}
															pIBasicCallControl->Disconnect(DC_NORMAL);
														}
														pIBasicCallControl->Release();
													}
													SysFreeString(pszAddress);
												}
												GlobalFree(pszGrammar);
											}
											m_cIPhoneVoiceRecognizerGrammar.Release();
										}
									}
								}
								m_cIPhoneVoiceRecognizerContext.Release();
							}
							m_cIPhoneVoiceRecognizer.Release();
						}
						m_cIPhoneVoiceAudioIn.Release();
					}
					m_cIPhoneVoiceAudioOut.Release();
				}
				m_cIPhoneVoice.Release();
			}
			UninitializePSTNService();
		}
		if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
		{
			szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_FAILEDCALL), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		if (pProfileInfo->GetBehaviorInfo(nRetryCount, tRetryInterval, tAbortInterval))
		{
			if (nRetryCount > pProfileInfo->GetRetryCount())
			{
				pProfileInfo->SetRetryTime(tTime.GetTime() + tRetryInterval.GetTotalSeconds());
				pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
				bSuccess = FALSE;
				continue;
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				szMessage.Format((pProfileInfo->GetRetryCount() > 1) ? STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_FAILURE_RETRIES) : STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_FAILURE_RETRY), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)szUser, pProfileInfo->GetRetryCount());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			}
			pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
		}
		bSuccess = FALSE;
	}
	if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
	{
		if (!szUsers[1].IsEmpty())
		{
			szMessage.Format((nCount > 1) ? STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_FAILURE_NODELIVERIES) : STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_FAILURE_NODELIVERY), (LPCTSTR)szUsers[1], (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			bSuccess = FALSE;
		}
	}
	return bSuccess;
}

BOOL CNotificationService::DoNotifyByPagerCall(CNotificationProfileInfo *pProfileInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nCount;
	UINT  nRetryCount;
	BOOL  bSuccess;
	BSTR  pszAddress;
	CString  szMessage;
	CString  szAddresses;
	CString  szUsers[2];
	CString  szUser;
	CTimeKey  tTime;
	CTimeSpan  tRetryInterval;
	CTimeSpan  tAbortInterval;
	CStringArray  szRecipients[3];
	CUserProfiles  pRecipientsAddresses;
	CUserProfileInfo  *pRecipientAddressInfo;
	CUserAddressBook  cRecipientsAddressBook;
	ITBasicCallControl  *pIBasicCallControl;

	for (nUser = 0, nUsers = (cRecipientsAddressBook.GetUserAddressBook(pRecipientsAddresses)) ? pProfileInfo->GetRecipients(szRecipients[0]) : -1; nUser < nUsers; nUser++)
	{
		if ((pRecipientAddressInfo = pRecipientsAddresses.GetAt(pRecipientsAddresses.Find(szRecipients[0].GetAt(nUser)))))
		{
			szRecipients[1].Add(szRecipients[0].GetAt(nUser));
			szRecipients[2].Add(pRecipientAddressInfo->GetOfficePager());
		}
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), nCount = 0; nUser < nUsers; nUser++)
	{
		szUser.Format(STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_PARTSTEXT), (LPCTSTR)szRecipients[1].GetAt(nUser));
		if (!szRecipients[2].GetAt(nUser).IsEmpty())
		{
			szUsers[0] += (!szUsers[0].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_SEPARATOR)) + SPACE + szUser) : szUser;
			szAddresses += (!szAddresses.IsEmpty()) ? (STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_SEPARATOR) + szRecipients[2].GetAt(nUser)) : szRecipients[2].GetAt(nUser);
			continue;
		}
		szUsers[1] += (!szUsers[1].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_SEPARATOR)) + SPACE + szUser) : szUser;
		szRecipients[1].RemoveAt(nUser);
		szRecipients[2].RemoveAt(nUser);
		nCount++;
		nUsers--;
		nUser--;
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), bSuccess = TRUE; nUser < nUsers && Wait(0); nUser++)
	{
		if ((pRecipientAddressInfo = (DoInitializePSTNService(pProfileInfo)) ? pRecipientsAddresses.GetAt(pRecipientsAddresses.Find((szUser = szRecipients[1].GetAt(nUser)))) : (CUserProfileInfo *)NULL))
		{
			if (SUCCEEDED(m_pIPhoneCallAddress->CreateCall((pszAddress = szRecipients[2].GetAt(nUser).AllocSysString()), LINEADDRESSTYPE_PHONENUMBER, TAPIMEDIATYPE_DATAMODEM, &pIBasicCallControl)))
			{
				if (SUCCEEDED(pIBasicCallControl->Connect(VARIANT_FALSE)))
				{
					if (DoPagerCallConnection(pProfileInfo, pRecipientAddressInfo))
					{
						for (pIBasicCallControl->Disconnect(DC_NORMAL); pProfileInfo->GetOptions() == NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING; )
						{
							szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_SUCCESSFULCALL), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
							break;
						}
						pIBasicCallControl->Release();
						SysFreeString(pszAddress);
						UninitializePSTNService();
						continue;
					}
					pIBasicCallControl->Disconnect(DC_NORMAL);
				}
				pIBasicCallControl->Release();
			}
			SysFreeString(pszAddress);
			UninitializePSTNService();
		}
		if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
		{
			szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_FAILEDCALL), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		if (pProfileInfo->GetBehaviorInfo(nRetryCount, tRetryInterval, tAbortInterval))
		{
			if (nRetryCount > pProfileInfo->GetRetryCount())
			{
				pProfileInfo->SetRetryTime(tTime.GetTime() + tRetryInterval.GetTotalSeconds());
				pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
				bSuccess = FALSE;
				continue;
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				szMessage.Format((pProfileInfo->GetRetryCount() > 1) ? STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_FAILURE_RETRIES) : STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_FAILURE_RETRY), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)szUser, pProfileInfo->GetRetryCount());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			}
			pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
		}
		bSuccess = FALSE;
	}
	if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
	{
		if (!szUsers[1].IsEmpty())
		{
			szMessage.Format((nCount > 1) ? STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_FAILURE_NODELIVERIES) : STRING(IDS_NOTIFICATION_SERVICE_PAGERCALL_FAILURE_NODELIVERY), (LPCTSTR)szUsers[1], (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			bSuccess = FALSE;
		}
	}
	return bSuccess;
}

BOOL CNotificationService::DoNotifyByFTPMessage(CNotificationProfileInfo *pProfileInfo)
{
	INT  nCount;
	INT  nUser[2];
	INT  nUsers[2];
	UINT  nFTPPort;
	UINT  nRetryCount;
	BOOL  bSuccess;
	CString  szUser;
	CString  szUsers;
	CString  szFTPUser;
	CString  szFTPAddress;
	CString  szFTPPassword;
	CString  szMessage;
	CTimeKey  tTime;
	CTimeSpan  tRetryInterval;
	CTimeSpan  tAbortInterval;
	CStringArray  szRecipients;
	CStringArray  szFTPUserNames[2];
	CStringArray  szFTPAddresses;
	CStringArray  szFTPPasswords;

	for (nUser[0] = 0, nUsers[0] = pProfileInfo->GetRecipients(szRecipients), pProfileInfo->GetFTPInfo(szFTPUserNames[0], szFTPUserNames[1], szFTPAddresses, szFTPPasswords, nFTPPort), nCount = 0, bSuccess = TRUE; nUser[0] < nUsers[0] && Wait(0); nUser[0]++)
	{
		for (nUser[1] = 0, nUsers[1] = (szFTPUserNames[0].GetSize() == szFTPUserNames[1].GetSize() && szFTPUserNames[0].GetSize() == szFTPAddresses.GetSize() && szFTPUserNames[0].GetSize() == szFTPPasswords.GetSize()) ? (INT)szFTPUserNames[0].GetSize() : -1, szUser.Empty(); nUser[1] < nUsers[1]; nUser[1]++)
		{
			if (szRecipients.GetAt(nUser[0]) == szFTPUserNames[0].GetAt(nUser[1]))
			{
				szUser = szFTPUserNames[0].GetAt(nUser[1]);
				szFTPUser = szFTPUserNames[1].GetAt(nUser[1]);
				szFTPAddress = szFTPAddresses.GetAt(nUser[1]);
				szFTPPassword = szFTPPasswords.GetAt(nUser[1]);
				break;
			}
		}
		if (nUser[1] < nUsers[1])
		{
			if (DoFTPMessageTransfer(pProfileInfo, szFTPUser, szFTPAddress, szFTPPassword, nFTPPort))
			{
				if (pProfileInfo->GetOptions() == NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING)
				{
					szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_SUCCESSFULSEND), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				}
				continue;
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FAILEDSEND), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			}
			if (pProfileInfo->GetBehaviorInfo(nRetryCount, tRetryInterval, tAbortInterval))
			{
				if (nRetryCount > pProfileInfo->GetRetryCount())
				{
					pProfileInfo->SetRetryTime(tTime.GetTime() + tRetryInterval.GetTotalSeconds());
					pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
					bSuccess = FALSE;
					continue;
				}
				if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
				{
					szMessage.Format((pProfileInfo->GetRetryCount() > 1) ? STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FAILURE_RETRIES) : STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FAILURE_RETRY), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)szUser, pProfileInfo->GetRetryCount());
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
				}
				pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
			}
			bSuccess = FALSE;
			continue;
		}
		szUser.Format(STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_PARTSTEXT), (LPCTSTR)szRecipients.GetAt(nUser[0]));
		szUsers += (!szUsers.IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_SEPARATOR)) + SPACE + szUser) : szUser;
		bSuccess = FALSE;
		nCount++;
	}
	if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
	{
		if (!szUsers.IsEmpty())
		{
			szMessage.Format((nCount > 1) ? STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FAILURE_NODELIVERIES) : STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FAILURE_NODELIVERY), (LPCTSTR)szUsers, (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			bSuccess = FALSE;
		}
	}
	return bSuccess;
}

BOOL CNotificationService::DoNotifyByPrinterMessage(CNotificationProfileInfo *pProfileInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nCount;
	UINT  nWeekDays;
	UINT  nRetryCount;
	BOOL  bWorkingDays;
	BOOL  bSuccess;
	CString  szMessage;
	CString  szAddresses;
	CString  szUsers[2];
	CString  szUser;
	CTimeKey  tTime;
	CTimeKey  tMission[2];
	CTimeKey  tHoliday[2];
	CTimeSpan  tDayHours[2];
	CTimeSpan  tRetryInterval;
	CTimeSpan  tAbortInterval;
	CStringArray  szRecipients[3];
	CUserProfiles  pRecipientsAddresses;
	CUserProfileInfo  *pRecipientAddressInfo;
	CUserAddressBook  cRecipientsAddressBook;

	for (nUser = 0, nUsers = (cRecipientsAddressBook.GetUserAddressBook(pRecipientsAddresses)) ? pProfileInfo->GetRecipients(szRecipients[0]) : -1; nUser < nUsers; nUser++)
	{
		if ((pRecipientAddressInfo = pRecipientsAddresses.GetAt(pRecipientsAddresses.Find(szRecipients[0].GetAt(nUser)))))
		{
			if (pRecipientAddressInfo->GetOfficeHours(nWeekDays, tDayHours[0], tDayHours[1]))
			{
				if ((((nWeekDays & USERPROFILE_WORKDAY_MONDAY) && tTime.GetDayOfWeek() == Monday) || ((nWeekDays & USERPROFILE_WORKDAY_TUESDAY) && tTime.GetDayOfWeek() == Tuesday) || ((nWeekDays & USERPROFILE_WORKDAY_WEDNESDAY) && tTime.GetDayOfWeek() == Wednesday) || ((nWeekDays & USERPROFILE_WORKDAY_THURSDAY) && tTime.GetDayOfWeek() == Thursday) || ((nWeekDays & USERPROFILE_WORKDAY_FRIDAY) && tTime.GetDayOfWeek() == Friday) || ((nWeekDays & USERPROFILE_WORKDAY_SATURDAY) && tTime.GetDayOfWeek() == Saturday) || ((nWeekDays & USERPROFILE_WORKDAY_SUNDAY) && tTime.GetDayOfWeek() == Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
					szRecipients[2].Add(pRecipientAddressInfo->GetOfficePrintProfile());
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHomeHours(tDayHours[0], tDayHours[1], bWorkingDays))
			{
				if ((!bWorkingDays || (tTime.GetDayOfWeek() != Saturday && tTime.GetDayOfWeek() != Sunday)) && tDayHours[0].GetTotalSeconds() <= tTime.GetTime() % SECONDSPERDAY && tDayHours[1].GetTotalSeconds() >= tTime.GetTime() % SECONDSPERDAY)
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHomePrintProfile());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHomePrintProfile());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetMission(tMission[0], tMission[1]))
			{
				if (tTime >= tMission[0].GetTime() && tTime <= tMission[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetMissionPrintProfile());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetMissionPrintProfile());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
			if (pRecipientAddressInfo->GetHoliday(tHoliday[0], tHoliday[1]))
			{
				if (tTime >= tHoliday[0].GetTime() && tTime <= tHoliday[1].GetTime())
				{
					if (!szRecipients[1].GetSize() || szRecipients[1].GetAt(szRecipients[1].GetUpperBound()) != pRecipientAddressInfo->GetFullName())
					{
						szRecipients[1].Add(pRecipientAddressInfo->GetFullName());
						szRecipients[2].Add(pRecipientAddressInfo->GetHolidayPrintProfile());
					}
					else
					{
						szRecipients[2].SetAt(szRecipients[2].GetUpperBound(), pRecipientAddressInfo->GetHolidayPrintProfile());
					}
					if (!szRecipients[2].GetAt(szRecipients[2].GetUpperBound()).IsEmpty()) continue;
				}
			}
		}
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), nCount = 0; nUser < nUsers; nUser++)
	{
		szUser.Format(STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_PARTSTEXT), (LPCTSTR)szRecipients[1].GetAt(nUser));
		if (!szRecipients[2].GetAt(nUser).IsEmpty())
		{
			szUsers[0] += (!szUsers[0].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_SEPARATOR)) + SPACE + szUser) : szUser;
			szAddresses += (!szAddresses.IsEmpty()) ? (STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_SEPARATOR) + szRecipients[2].GetAt(nUser)) : szRecipients[2].GetAt(nUser);
			continue;
		}
		szUsers[1] += (!szUsers[1].IsEmpty()) ? (CString(STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_SEPARATOR)) + SPACE + szUser) : szUser;
		szRecipients[1].RemoveAt(nUser);
		szRecipients[2].RemoveAt(nUser);
		nCount++;
		nUsers--;
		nUser--;
	}
	for (nUser = 0, nUsers = (INT)szRecipients[1].GetSize(), bSuccess = TRUE; nUser < nUsers && Wait(0); nUser++)
	{
		if ((pRecipientAddressInfo = pRecipientsAddresses.GetAt(pRecipientsAddresses.Find((szUser = szRecipients[1].GetAt(nUser))))))
		{
			if (DoPrinterMessageOutput(pProfileInfo, szRecipients[2].GetAt(nUser)))
			{
				if (pProfileInfo->GetOptions() == NOTIFICATIONINFO_OPTION_AUDIT_EVERYTHING)
				{
					szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_SUCCESSFULPRINT), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				}
				continue;
			}
		}
		if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
		{
			szMessage.Format(STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_FAILEDPRINT), (LPCTSTR)szUser, (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
		}
		if (pProfileInfo->GetBehaviorInfo(nRetryCount, tRetryInterval, tAbortInterval))
		{
			if (nRetryCount > pProfileInfo->GetRetryCount())
			{
				pProfileInfo->SetRetryTime(tTime.GetTime() + tRetryInterval.GetTotalSeconds());
				pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
				bSuccess = FALSE;
				continue;
			}
			if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
			{
				szMessage.Format((pProfileInfo->GetRetryCount() > 1) ? STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_FAILURE_RETRIES) : STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_FAILURE_RETRY), (LPCTSTR)pProfileInfo->GetName(), (LPCTSTR)szUser, pProfileInfo->GetRetryCount());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			}
			pProfileInfo->SetRetryCount(max(pProfileInfo->GetRetryCount() + 1, pProfileInfo->GetRetryCount()));
		}
		bSuccess = FALSE;
	}
	if (pProfileInfo->GetOptions() != NOTIFICATIONINFO_OPTION_AUDIT_NOTHING)
	{
		if (!szUsers[1].IsEmpty())
		{
			szMessage.Format((nCount > 1) ? STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_FAILURE_NODELIVERIES) : STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_FAILURE_NODELIVERY), (LPCTSTR)szUsers[1], (LPCTSTR)pProfileInfo->GetName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			bSuccess = FALSE;
		}
	}
	return bSuccess;
}

BOOL CNotificationService::DoFaxTransmission(CONST CNotificationProfileInfo *pProfileInfo, FAX_CONTEXT_INFO *pFAXContext)
{
	CDC  cDC;
	INT  nPos;
	INT  nPage;
	INT  nPages;
	INT  nOffset;
	INT  nBorder;
	CRgn  rgClip;
	CRect  rPage;
	CRect  rText[3];
	CSize  size[5];
	CFont  cFont[6];
	CFont  *pOldFont;
	CString  szTitle;
	CString  szFooter;
	CString  szNotice[3];
	LOGFONT  lfFont[3];
	CTimeKey  tTimeKey;
	COLORREF  nColor[3];
	COLORREF  nOldColor;
	TEXTMETRIC  tmFont[3];
	CFontTools  cFontTools;
	CVersionInfo  cVersionInfo;

	if (cDC.Attach(pFAXContext->hDC))
	{
		if (pProfileInfo->GetFontInfo(&lfFont[0], nColor[0], &lfFont[1], nColor[1], &lfFont[2], nColor[2]))
		{
			for (szTitle.Format(STRING(IDS_NOTIFICATION_SERVICE_FAX_SUBJECT), (LPCTSTR)cVersionInfo.QueryProductName()), lfFont[0].lfHeight = -3 * cFontTools.QueryPixels(&cDC, lfFont[0].lfHeight) / 4, lfFont[1].lfHeight = -3 * cFontTools.QueryPixels(&cDC, lfFont[1].lfHeight) / 4, lfFont[2].lfHeight = -3 * cFontTools.QueryPixels(&cDC, lfFont[2].lfHeight) / 4, lfFont[0].lfWidth = lfFont[1].lfWidth = lfFont[2].lfWidth = 0, rPage.left = 20 * (cDC.GetDeviceCaps(HORZRES) / cDC.GetDeviceCaps(HORZSIZE)), rPage.top = 30 * (cDC.GetDeviceCaps(VERTRES) / cDC.GetDeviceCaps(VERTSIZE)), rPage.right = cDC.GetDeviceCaps(HORZRES) - rPage.left, rPage.bottom = cDC.GetDeviceCaps(VERTRES) - rPage.top / 3, size[0].cx = size[0].cy = size[1].cx = size[1].cy = size[2].cx = size[2].cy = size[3].cx = size[3].cy = size[4].cx = size[4].cy = 0, szNotice[0] = ((nPos = cVersionInfo.QueryComments().Find((szNotice[2] = cVersionInfo.QueryCompanyName()))) >= 0) ? cVersionInfo.QueryComments().Left(nPos) : cVersionInfo.QueryComments(), szNotice[1] = (nPos >= 0) ? cVersionInfo.QueryComments().Mid(nPos + szNotice[2].GetLength()) : EMPTYSTRING; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]) && cFont[2].CreateFontIndirect(&lfFont[2]) && cFont[3].CreateFont(-(INT)(((((double)rPage.Width()*(double)cDC.GetDeviceCaps(HORZSIZE)) / (20.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cFont[4].CreateFont(-(INT)(((((double)rPage.Width()*(double)cDC.GetDeviceCaps(HORZSIZE)) / (72.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cFont[5].CreateFont(-(INT)(((((double)rPage.Width()*(double)cDC.GetDeviceCaps(HORZSIZE)) / (72.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO)); )
			{
				for (nPage = 0, nPages = -1, nOffset = 0; nPage <= nPages || nPages < 0; nPage++)
				{
					if (nPages < 0 || ((!nPage || cDC.EndPage() >= 0) && cDC.StartPage() >= 0))
					{
						if ((pOldFont = (!nPage) ? cDC.SelectObject(&cFont[3]) : (CFont *)NULL))
						{
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							size[0].cy = cDC.DrawText(szTitle, CRect(rPage), (nPages < 0) ? (DT_CALCRECT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[4])))
						{
							size[1] = cDC.GetTextExtent(szNotice[0]);
							size[2] = cDC.GetTextExtent(szNotice[1]);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[5])))
						{
							size[3] = cDC.GetTextExtent(szNotice[2]);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[4])))
						{
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							szFooter.Format(STRING(IDS_NOTIFICATION_SERVICE_FAX_FOOTER), (LPCTSTR)tTimeKey.FormatGmt(IDS_TIMEKEY_DEFAULTDATEFORMAT), (LPCTSTR)tTimeKey.FormatGmt(IDS_TIMEKEY_DEFAULTTIMEFORMAT), nPage + 1, nPages + 1);
							size[4].cy = cDC.DrawText(szFooter, CRect(rPage.left, rPage.bottom - size[1].cy - max(size[1].cy, size[2].cy), rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.DrawText(szNotice[0], CRect(rPage.left, rPage.bottom - size[1].cy, rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.DrawText(szNotice[1], CRect(rPage.left + size[1].cx + size[3].cx, rPage.bottom - size[2].cy, rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[5])))
						{
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							cDC.DrawText(szNotice[2], CRect(rPage.left + size[1].cx, rPage.bottom - size[3].cy, rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						if (rgClip.CreateRectRgn(rPage.left, (!nPage) ? (rPage.top + 2 * size[0].cy) : rPage.top, rPage.right, rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy)))
						{
							if (cDC.SelectClipRgn(&rgClip, RGN_COPY) != ERROR)
							{
								if ((pOldFont = cDC.SelectObject(&cFont[0])))
								{
									nOldColor = cDC.SetTextColor(nColor[0]);
									cDC.GetTextMetrics(&tmFont[0]);
									rText[0].left = rPage.left;
									rText[0].right = rPage.right;
									rText[0].top = (!nPage) ? (rPage.top + 2 * size[0].cy) : (rPage.top - nOffset);
									rText[0].bottom = nBorder = rText[0].top + ((rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy) - rText[0].top) / tmFont[0].tmHeight)*tmFont[0].tmHeight;
									cDC.DrawText(pProfileInfo->GetProlog(), rText[0], (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX) : (DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX));
									cDC.DrawText(pProfileInfo->GetProlog(), rText[0], DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);
									if (rText[0].bottom > nBorder)
									{
										nOffset += nBorder - rPage.top;
										cDC.SetTextColor(nOldColor);
										cDC.SelectObject(pOldFont);
										rgClip.DeleteObject();
										continue;
									}
									cDC.SetTextColor(nOldColor);
									cDC.SelectObject(pOldFont);
								}
								if ((pOldFont = cDC.SelectObject(&cFont[1])))
								{
									nOldColor = cDC.SetTextColor(nColor[1]);
									cDC.GetTextMetrics(&tmFont[1]);
									rText[1].left = rPage.left;
									rText[1].right = rPage.right;
									rText[1].top = (!nPage) ? (rPage.top + 2 * size[0].cy + rText[0].Height()) : (rPage.top + rText[0].Height() - nOffset);
									rText[1].bottom = nBorder = rText[1].top + ((rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy) - rText[1].top) / tmFont[1].tmHeight)*tmFont[1].tmHeight;
									cDC.DrawText(pProfileInfo->GetMessage(), rText[1], (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX) : (DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX));
									cDC.DrawText(pProfileInfo->GetMessage(), rText[1], DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);
									if (rText[1].bottom > nBorder)
									{
										nOffset += nBorder - rPage.top;
										cDC.SetTextColor(nOldColor);
										cDC.SelectObject(pOldFont);
										rgClip.DeleteObject();
										continue;
									}
									cDC.SetTextColor(nOldColor);
									cDC.SelectObject(pOldFont);
								}
								if ((pOldFont = cDC.SelectObject(&cFont[2])))
								{
									nOldColor = cDC.SetTextColor(nColor[2]);
									cDC.GetTextMetrics(&tmFont[2]);
									rText[2].left = rPage.left;
									rText[2].right = rPage.right;
									rText[2].top = (!nPage) ? (rPage.top + 2 * size[0].cy + rText[0].Height() + rText[1].Height()) : (rPage.top + rText[0].Height() + rText[1].Height() - nOffset);
									rText[2].bottom = nBorder = rText[2].top + ((rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy) - rText[2].top) / tmFont[2].tmHeight)*tmFont[2].tmHeight;
									cDC.DrawText(pProfileInfo->GetEpilog(), rText[2], (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX) : (DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX));
									cDC.DrawText(pProfileInfo->GetEpilog(), rText[2], DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);
									if (rText[2].bottom > nBorder)
									{
										nOffset += nBorder - rPage.top;
										cDC.SetTextColor(nOldColor);
										cDC.SelectObject(pOldFont);
										rgClip.DeleteObject();
										continue;
									}
									cDC.SetTextColor(nOldColor);
									cDC.SelectObject(pOldFont);
								}
								cDC.SelectClipRgn((CRgn *)NULL);
							}
							rgClip.DeleteObject();
						}
						if (nPages < 0)
						{
							nPages = nPage;
							nOffset = 0;
							nPage = -1;
							continue;
						}
						cDC.EndPage();
					}
					break;
				}
				if (nPage == nPages)
				{
					cDC.EndDoc();
					cDC.Detach();
					return TRUE;
				}
				break;
			}
		}
		cDC.AbortDoc();
		cDC.Detach();
	}
	return FALSE;
}

BOOL CNotificationService::DoPhoneCallConversation(CONST CNotificationProfileInfo *pProfileInfo, CONST CUserProfileInfo *pUserInfo, ITLegacyCallMediaControl2 *pLegacyCallMediaControl)
{
	WORD  wAge;
	WORD  wGender;
	UINT  nCount[3];
	BOOL  bConversation;
	LPWSTR  pszAtts[2];
	CString  szAtts[2];
	CString  szDigit[2];
	CString  szText[10];
	CString  szSpeaker;
	CString  szAnswer;
	CALL_STATE  nCallState;
	CVersionInfo  cVersionInfo;
	CStringTools  cStringTools;
	CComputerToken  cComputerToken;
	ISpObjectToken  *pIVoice;

	if (pProfileInfo->GetVoiceInfo(szSpeaker, wGender, wAge, bConversation))
	{
		szAtts[0].Format(STRING(IDS_VOICEATTRIBUTES_LANGUAGEINFO), GetLanguageID());
		szAtts[1].Format(STRING(IDS_VOICEATTRIBUTES_SPEAKERINFO), (LPCTSTR)szSpeaker, STRING(MINVOICEGENDER + wGender), STRING(MINVOICEAGE + wAge));
		szText[0].Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_WELCOMETEXT), (LPCTSTR)cVersionInfo.QueryInternalName(), (LPCTSTR)TranslateToPhoneticWord(cComputerToken.GetComputerName()), (LPCTSTR)pUserInfo->GetFirstName(), (LPCTSTR)pUserInfo->GetName());
		szText[1] = STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_CALLACCEPTTEXT);
		szText[2] = STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_CALLCONFIRMTEXT);
		szText[3] = STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_CALLEETESTTEXT);
		szText[4] = STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_CALLEEHOLDINGTEXT);
		szText[5] = STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERFAILURETEXT);
		szText[6].Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_CALLEEAVAILABLETEXT), (LPCTSTR)pUserInfo->GetFirstName(), (LPCTSTR)pUserInfo->GetName());
		szText[7].Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_CALLEEPASSINGONTEXT), (LPCTSTR)pUserInfo->GetFirstName(), (LPCTSTR)pUserInfo->GetName());
		szText[8].Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_LOOPWAITTEXT), (LPCTSTR)cVersionInfo.QueryInternalName(), (LPCTSTR)TranslateToPhoneticWord(cComputerToken.GetComputerName()));
		szText[9].Format(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_MESSAGETEXT), (LPCTSTR)pProfileInfo->GetProlog(), (LPCTSTR)pProfileInfo->GetMessage(), (LPCTSTR)pProfileInfo->GetMessage(), (LPCTSTR)pProfileInfo->GetMessage(), (LPCTSTR)pProfileInfo->GetEpilog());
		if ((pszAtts[0] = (LPWSTR)GlobalAlloc(GPTR, (szAtts[0].GetLength() + 1)*sizeof(WCHAR))))
		{
			if ((pszAtts[1] = (LPWSTR)GlobalAlloc(GPTR, (szAtts[1].GetLength() + 1)*sizeof(WCHAR))))
			{
#ifndef UNICODE
				MultiByteToWideChar(CP_ACP, 0, szAtts[0], -1, pszAtts[0], szAtts[0].GetLength() + 1);
				MultiByteToWideChar(CP_ACP, 0, szAtts[1], -1, pszAtts[1], szAtts[1].GetLength() + 1);
#else
				wcscpy_s(pszAtts[0], szAtts[0].GetLength() + 1, szAtts[0]);
				wcscpy_s(pszAtts[1], szAtts[1].GetLength() + 1, szAtts[1]);
#endif
				nCount[0] = 0;
				nCount[1] = 0;
				nCount[2] = 0;
				if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, pszAtts[0], pszAtts[1], &pIVoice)))
				{
					if (SUCCEEDED(m_cIPhoneVoice->SetVoice(pIVoice)) && SUCCEEDED(m_cIPhoneVoice->SetVolume(100)))
					{
						for (nCallState = CS_IDLE; Wait(100); nCallState = m_pPhoneCallMonitor->GetCallState())
						{
							if (m_pPhoneCallMonitor->GetCallState() == CS_CONNECTED)
							{
								nCallState = CS_CONNECTED;
								break;
							}
							if (m_pPhoneCallMonitor->GetCallState() != CS_INPROGRESS  &&  nCallState == CS_INPROGRESS) break;
							if (m_pPhoneCallMonitor->GetCallState() == CS_DISCONNECTED) break;
						}
						if (nCallState == CS_CONNECTED)
						{
							for (szDigit[0] = cStringTools.ConvertIntToString(1), szDigit[1] = cStringTools.ConvertIntToString(2); !bConversation && nCount[0] < 10; nCount[0]++)
							{
								if ((!nCount[0] && SUCCEEDED(pLegacyCallMediaControl->DetectDigits(LINEDIGITMODE_DTMF))) || nCount[0] > 0)
								{
									if (!DoSpeakOnPhoneCallLine(szText[8]))
									{
										nCount[0] = 10;
										break;
									}
									if (Wait(1000))
									{
										if (m_pPhoneCallMonitor->GetCallDigits().Find(szDigit[0]) >= 0) break;
										if (m_pPhoneCallMonitor->GetCallDigits().Find(szDigit[1]) < 0) continue;
									}
								}
								nCount[0] = 10;
								break;
							}
							if (!bConversation)
							{
								if (nCount[0] < 10)
								{
									if (DoSpeakOnPhoneCallLine(szText[9])) goto END;
									goto FAILURE;
								}
								goto REJECTTEXT;
							}
							for (; !DoWaitForPhoneCallLineAnswer(1000 * SECONDSPERMINUTE); )
							{
								goto NO_ANSWER;
								break;
							}
							for (; !DoListenToPhoneCallLineAnswer(szAnswer); )
							{
								goto FAILURE;
								break;
							}
						ACCEPTANCE:   if (++nCount[0] > 10) goto NO_ANSWER;
							if (DoSpeakOnPhoneCallLine(szText[1]))
							{
								if (DoWaitForPhoneCallLineAnswer(5000))
								{
									if (DoListenToPhoneCallLineAnswer(szAnswer))
									{
										if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOACCEPTTEXT)) >= 0 || szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERDONTACCEPTTEXT)) >= 0) goto REJECTTEXT;
										if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOREJECTTEXT)) >= 0 || szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERDONTREJECTTEXT)) >= 0) goto ACCEPTTEXT;
										if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOREFUSETEXT)) >= 0 || szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERDONTREFUSETEXT)) >= 0) goto ACCEPTTEXT;
										if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERACCEPTTEXT)) >= 0) goto ACCEPTTEXT;
										if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERREJECTTEXT)) >= 0) goto REJECTTEXT;
										if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERREFUSETEXT)) >= 0) goto REJECTTEXT;
										goto ACCEPTANCE;
									}
									goto FAILURE;
								}
								goto ACCEPTANCE;
							}
							goto FAILURE;
						ACCEPTTEXT:   if (DoSpeakOnPhoneCallLine(szText[2]))
						{
							if (DoWaitForPhoneCallLineAnswer(5000))
							{
								if (DoListenToPhoneCallLineAnswer(szAnswer))
								{
									if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOACCEPTTEXT)) >= 0 || szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERDONTACCEPTTEXT)) >= 0) goto REJECTTEXT;
									if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOREJECTTEXT)) >= 0 || szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERDONTREJECTTEXT)) >= 0) goto WELCOMETEXT;
									if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOREFUSETEXT)) >= 0 || szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERDONTREFUSETEXT)) >= 0) goto WELCOMETEXT;
									if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERACCEPTTEXT)) >= 0) goto WELCOMETEXT;
									if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERREJECTTEXT)) >= 0) goto REJECTTEXT;
									if (szAnswer.Find(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERREFUSETEXT)) >= 0) goto REJECTTEXT;
									goto ACCEPTANCE;
								}
								goto FAILURE;
							}
							goto ACCEPTANCE;
						}
									  goto FAILURE;
								  ANSWER:       if (DoListenToPhoneCallLineAnswer(szAnswer))
								  {
									  if (!szAnswer.Compare(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERYESTEXT))) goto WELCOMETEXT;
									  if (!szAnswer.Compare(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOTEXT))) goto REJECTTEXT;
									  goto ACCEPTANCE;
								  }
											WELCOMETEXT:  if (DoSpeakOnPhoneCallLine(szText[0]))
											{
												if (!DoWaitForPhoneCallLineAnswer(4000))
												{
													if (DoSpeakOnPhoneCallLine(szText[3]))
													{
														if (!DoWaitForPhoneCallLineAnswer(4000))
														{
															if (DoSpeakOnPhoneCallLine(szText[3]))
															{
																if (!DoWaitForPhoneCallLineAnswer(4000)) goto NO_ANSWER;
																goto ANSWER;
															}
															goto FAILURE;
														}
														goto ANSWER;
													}
													goto FAILURE;
												}
												goto WELCOMETEXT_ANSWER;
											}
														  goto FAILURE;
													  WELCOMETEXT_ANSWER:
														  if (DoListenToPhoneCallLineAnswer(szAnswer))
														  {
															  if (!szAnswer.CompareNoCase(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERYESTEXT))) goto WELCOMETEXT_ANSWER_YES;
															  if (!szAnswer.CompareNoCase(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOTEXT))) goto WELCOMETEXT_ANSWER_NO;
															  goto WELCOMETEXT_ANSWER_FAILURE;
														  }
														  goto FAILURE;
													  WELCOMETEXT_ANSWER_FAILURE:
														  if (++nCount[1] > 5) goto GOODBYETEXT;
														  if (DoSpeakOnPhoneCallLine(szText[5]))
														  {
															  if (!DoWaitForPhoneCallLineAnswer(4000))
															  {
																  if (DoSpeakOnPhoneCallLine(szText[3]))
																  {
																	  if (!DoWaitForPhoneCallLineAnswer(4000)) goto FAILURE;
																	  goto WELCOMETEXT_ANSWER;
																  }
																  goto FAILURE;
															  }
															  goto WELCOMETEXT_ANSWER;
														  }
														  goto FAILURE;
													  WELCOMETEXT_ANSWER_YES:
														  for (; pProfileInfo->GetProlog().GetLength() > 0; )
														  {
															  if (!DoSpeakOnPhoneCallLine(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SPEAKPAUSETEXT) + pProfileInfo->GetProlog() + STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SPEAKPAUSETEXT))) goto FAILURE;
															  break;
														  }
														  for (; pProfileInfo->GetMessage().GetLength() > 0; )
														  {
															  if (!DoSpeakOnPhoneCallLine(pProfileInfo->GetMessage() + STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SPEAKPAUSETEXT)) || !DoSpeakOnPhoneCallLine(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SPEAKREPEATTEXT) + pProfileInfo->GetMessage() + STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SPEAKPAUSETEXT))) goto FAILURE;
															  break;
														  }
														  for (; pProfileInfo->GetEpilog().GetLength() > 0; )
														  {
															  if (!DoSpeakOnPhoneCallLine(pProfileInfo->GetEpilog() + STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_SPEAKPAUSETEXT))) goto FAILURE;
															  break;
														  }
														  goto END;
													  WELCOMETEXT_ANSWER_NO:
														  if (DoSpeakOnPhoneCallLine(szText[6]))
														  {
															  if (!DoWaitForPhoneCallLineAnswer(4000))
															  {
																  if (DoSpeakOnPhoneCallLine(szText[3]))
																  {
																	  if (!DoWaitForPhoneCallLineAnswer(4000)) goto FAILURE;
																	  goto CALLEEAVAILABLE_ANSWER;
																  }
																  goto FAILURE;
															  }
															  goto CALLEEAVAILABLE_ANSWER;
														  }
														  goto FAILURE;
													  CALLEEAVAILABLE_ANSWER:
														  if (DoListenToPhoneCallLineAnswer(szAnswer))
														  {
															  if (!szAnswer.CompareNoCase(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERYESTEXT))) goto CALLEEAVAILABLE_ANSWER_YES;
															  if (!szAnswer.CompareNoCase(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_ANSWERNOTEXT))) goto CALLEEAVAILABLE_ANSWER_NO;
															  goto CALLEEAVAILABLE_ANSWER_FAILURE;
														  }
														  goto FAILURE;
													  CALLEEAVAILABLE_ANSWER_FAILURE:
														  if (++nCount[2] > 5) goto GOODBYETEXT;
														  if (DoSpeakOnPhoneCallLine(szText[5]))
														  {
															  if (!DoWaitForPhoneCallLineAnswer(4000))
															  {
																  if (DoSpeakOnPhoneCallLine(szText[3]))
																  {
																	  if (!DoWaitForPhoneCallLineAnswer(4000)) goto FAILURE;
																	  goto CALLEEAVAILABLE_ANSWER;
																  }
																  goto FAILURE;
															  }
															  goto CALLEEAVAILABLE_ANSWER;
														  }
														  goto FAILURE;
													  CALLEEAVAILABLE_ANSWER_YES:
														  if (DoSpeakOnPhoneCallLine(szText[4]))
														  {
														  CALLEEAVAILABLE_ANSWER_WAIT:
															  if (DoWaitForPhoneCallLineAnswer(120000))
															  {
																  if (DoListenToPhoneCallLineAnswer(szAnswer))
																  {
																	  if (!szAnswer.IsEmpty()) goto WELCOMETEXT;
																	  goto CALLEEAVAILABLE_ANSWER_WAIT;
																  }
																  goto FAILURE;
															  }
														  }
														  goto FAILURE;
													  CALLEEAVAILABLE_ANSWER_NO:
														  if (DoSpeakOnPhoneCallLine(szText[7])) goto WELCOMETEXT_ANSWER_YES;
														  goto FAILURE;
													  END:          GlobalFree(pszAtts[1]);
														  GlobalFree(pszAtts[0]);
														  pIVoice->Release();
														  return TRUE;
													  REJECTTEXT:   DoSpeakOnPhoneCallLine(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_REJECTTEXT));
														  goto FAILURE;
													  GOODBYETEXT:  DoSpeakOnPhoneCallLine(STRING(IDS_NOTIFICATION_SERVICE_PHONECALL_GOODBYTEXT));
														  goto FAILURE;
						}
					}
				NO_ANSWER:
				FAILURE:  pIVoice->Release();
				}
				GlobalFree(pszAtts[1]);
			}
			GlobalFree(pszAtts[0]);
		}
	}
	return FALSE;
}

BOOL CNotificationService::DoAudioOutForPhoneCall(ITLegacyCallMediaControl2 *pLegacyCallMediaControl)
{
	GUID  guidWaveOut;
	DWORD  cbDeviceID;
	LPUINT  pDeviceID;
	WAVEFORMATEX  *pWaveFormat;
	SPSTREAMFORMAT  nWaveFormat;

	if (SUCCEEDED(pLegacyCallMediaControl->GetID(COleVariant(STRING(IDS_VOICEWAVE_OUTPUTFORMAT)).bstrVal, &(cbDeviceID = sizeof(pDeviceID)), (LPBYTE *)&pDeviceID)))
	{
		for (nWaveFormat = SPSF_48kHz16BitStereo; nWaveFormat >= SPSF_8kHz8BitMono; nWaveFormat = (SPSTREAMFORMAT)(nWaveFormat - 1))
		{
			if (SUCCEEDED(SpConvertStreamFormatEnum(nWaveFormat, &(guidWaveOut = SPDFID_WaveFormatEx), &pWaveFormat)))
			{
				if (waveOutOpen((LPHWAVEOUT)NULL, *pDeviceID, pWaveFormat, 0, 0, WAVE_FORMAT_QUERY) == MMSYSERR_NOERROR) break;
				CoTaskMemFree(pWaveFormat);
			}
		}
		if (nWaveFormat >= SPSF_8kHz8BitMono  &&  nWaveFormat <= SPSF_48kHz16BitStereo)
		{
			if (SUCCEEDED(m_cIPhoneVoiceAudioOut->SetDeviceId(*pDeviceID)) && SUCCEEDED(m_cIPhoneVoiceAudioOut->SetFormat(guidWaveOut, pWaveFormat)) && SUCCEEDED(m_cIPhoneVoice->SetOutput(m_cIPhoneVoiceAudioOut, FALSE)))
			{
				CoTaskMemFree(pWaveFormat);
				return TRUE;
			}
			CoTaskMemFree(pWaveFormat);
		}
	}
	return FALSE;
}

BOOL CNotificationService::DoAudioInForPhoneCall(ITLegacyCallMediaControl2 *pLegacyCallMediaControl)
{
	GUID  guidWaveIn;
	DWORD  cbDeviceID;
	LPUINT  pDeviceID;
	WAVEFORMATEX  *pWaveFormat;
	SPSTREAMFORMAT  nWaveFormat;

	if (SUCCEEDED(pLegacyCallMediaControl->GetID(COleVariant(STRING(IDS_VOICEWAVE_INPUTFORMAT)).bstrVal, &(cbDeviceID = sizeof(pDeviceID)), (LPBYTE *)&pDeviceID)))
	{
		for (nWaveFormat = SPSF_48kHz16BitStereo; nWaveFormat >= SPSF_8kHz8BitMono; nWaveFormat = (SPSTREAMFORMAT)(nWaveFormat - 1))
		{
			if (SUCCEEDED(SpConvertStreamFormatEnum(nWaveFormat, &(guidWaveIn = SPDFID_WaveFormatEx), &pWaveFormat)))
			{
				if (waveInOpen((LPHWAVEIN)NULL, *pDeviceID, pWaveFormat, 0, 0, WAVE_FORMAT_QUERY) == MMSYSERR_NOERROR) break;
				CoTaskMemFree(pWaveFormat);
			}
		}
		if (nWaveFormat >= SPSF_8kHz8BitMono  &&  nWaveFormat <= SPSF_48kHz16BitStereo)
		{
			if (SUCCEEDED(m_cIPhoneVoiceAudioIn->SetDeviceId(*pDeviceID)) && SUCCEEDED(m_cIPhoneVoiceAudioIn->SetFormat(guidWaveIn, pWaveFormat)) && SUCCEEDED(m_cIPhoneVoiceRecognizer->SetInput(m_cIPhoneVoiceAudioIn, FALSE)))
			{
				CoTaskMemFree(pWaveFormat);
				return TRUE;
			}
			CoTaskMemFree(pWaveFormat);
		}
	}
	return FALSE;
}

BOOL CNotificationService::DoSpeakOnPhoneCallLine(LPCTSTR pszText)
{
	LPWSTR  pszConversation;

	if (Wait(0) && IsPhoneCallLineConnected())
	{
		if ((pszConversation = (LPWSTR)GlobalAlloc(GPTR, (lstrlen(pszText) + 1)*sizeof(WCHAR))))
		{
#ifndef UNICODE
			MultiByteToWideChar(CP_ACP, 0, pszText, -1, pszConversation, lstrlen(pszText) + 1);
#else
			wcscpy_s(pszConversation, lstrlen(pszText) + 1, pszText);
#endif
			if (SUCCEEDED(m_cIPhoneVoiceRecognizerGrammar->SetRuleIdState(0, SPRS_INACTIVE)) && SUCCEEDED(m_cIPhoneVoice->Speak(pszConversation, SPF_DEFAULT | SPF_IS_XML, (ULONG *)NULL)))
			{
				GlobalFree(pszConversation);
				return TRUE;
			}
			GlobalFree(pszConversation);
		}
	}
	return FALSE;
}

BOOL CNotificationService::DoWaitForPhoneCallLineAnswer(DWORD dwTimeout)
{
	return((SUCCEEDED(m_cIPhoneVoiceRecognizerGrammar->SetRuleIdState(0, SPRS_ACTIVE)) && m_cIPhoneVoiceRecognizerContext->WaitForNotifyEvent(dwTimeout) == S_OK) ? TRUE : FALSE);
}

BOOL CNotificationService::DoListenToPhoneCallLineAnswer(CString &szAnswer)
{
	BYTE  bAttributes;
	LPWSTR  pszAnswer;
	CString  szNoise;
	CSpEvent  cCalleeEvent;
	ISpRecoResult  *pIResult;

	if (SUCCEEDED(cCalleeEvent.GetFrom(m_cIPhoneVoiceRecognizerContext)))
	{
		if (cCalleeEvent.eEventId == SPEI_RECOGNITION)
		{
			if ((pIResult = cCalleeEvent.RecoResult()))
			{
				if (SUCCEEDED(pIResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, FALSE, &pszAnswer, &bAttributes)))
				{
#ifndef UNICODE
					WideCharToMultiByte(CP_ACP, 0, pszAnswer, -1, szAnswer.GetBufferSetLength((INT)wcslen(pszAnswer)), (INT)(wcslen(pszAnswer) + 1), (LPCSTR)NULL, (LPBOOL)NULL);
					szAnswer.ReleaseBuffer();
#else
					szAnswer = pszAnswer;
#endif
					CoTaskMemFree(pszAnswer);
					return TRUE;
				}
			}
		}
		if (cCalleeEvent.eEventId == SPEI_FALSE_RECOGNITION)
		{
			while (DoListenToPhoneCallLineAnswer(szAnswer));
			return TRUE;
		}
	}
	szAnswer.Empty();
	return FALSE;
}

BOOL CNotificationService::IsPhoneCallLineConnected() CONST
{
	return((m_pPhoneCallMonitor != (CNotificationPhoneCallMonitorSink *)NULL  &&  m_pPhoneCallMonitor->GetCallState() == CS_CONNECTED) ? TRUE : FALSE);
}

BOOL CNotificationService::DoPagerCallConnection(CONST CNotificationProfileInfo *pProfileInfo, CONST CUserProfileInfo *pUserInfo)
{
	UINT  nRetry;
	DWORD  dwAbort;
	DWORD  dwInterval;
	CTimeSpan  tRetry;
	CTimeSpan  tAbort;
	CALL_STATE  nCallState;

	for (pProfileInfo->GetBehaviorInfo(nRetry, tRetry, tAbort), dwInterval = 100, dwAbort = 0, nCallState = CS_IDLE; Wait(dwInterval); nCallState = (nCallState != CS_CONNECTED) ? m_pPhoneCallMonitor->GetCallState() : nCallState)
	{
		if (nCallState == CS_CONNECTED || dwAbort >= 1000 * tAbort.GetTotalSeconds()) break;
		dwAbort += dwInterval;
	}
	return((nCallState == CS_INPROGRESS || nCallState == CS_CONNECTED) ? TRUE : FALSE);
}

BOOL CNotificationService::DoFTPMessageTransfer(CONST CNotificationProfileInfo *pProfileInfo, LPCTSTR pszUserName, LPCTSTR pszAddress, LPCTSTR pszPassword, UINT nPort)
{
	DWORD  dwService;
	CString  szServer;
	CString  szMessage;
	CString  szFileName;
	CString  szDirectory;
	CTimeKey  tFileTime;
	INTERNET_PORT  nInternetPort;
	CInternetFile  *pInternetFile;
	CFtpConnection  *pFtpConnection;
	CInternetSession  cInternetSession;

	if (AfxParseURL(pszAddress, dwService, szServer, szDirectory, nInternetPort))
	{
		try
		{
			pFtpConnection = cInternetSession.GetFtpConnection(szServer, pszUserName, pszPassword, (!nPort) ? ((nInternetPort == INTERNET_DEFAULT_FTP_PORT) ? INTERNET_INVALID_PORT_NUMBER : nInternetPort) : nPort);
		}
		catch (CInternetException *pException)
		{
			pException->Delete();
			return FALSE;
		}
		try
		{
			for (szFileName.Format(STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FILENAME), (LPCTSTR)tFileTime.FormatGmt(STRING(IDS_NOTIFICATION_SERVICE_FTPMESSAGE_FILETIME))), szDirectory = (szDirectory.Left(lstrlen(STRING(IDS_INTERNET_DELIMITER))) == STRING(IDS_INTERNET_DELIMITER)) ? szDirectory.Mid(lstrlen(STRING(IDS_INTERNET_DELIMITER))) : szDirectory; !szDirectory.IsEmpty(); )
			{
				pFtpConnection->SetCurrentDirectory(szDirectory);
				break;
			}
			pInternetFile = pFtpConnection->OpenFile(szFileName, GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII);
		}
		catch (CInternetException *pException)
		{
			pFtpConnection->Close();
			delete pFtpConnection;
			pException->Delete();
			return FALSE;
		}
		try
		{
			for (; !pProfileInfo->GetProlog().IsEmpty(); )
			{
				szMessage = pProfileInfo->GetProlog();
				break;
			}
			for (; !pProfileInfo->GetMessage().IsEmpty(); )
			{
				szMessage = (!pProfileInfo->GetProlog().IsEmpty()) ? (szMessage + CR + EOL + pProfileInfo->GetMessage()) : pProfileInfo->GetMessage();
				break;
			}
			for (; !pProfileInfo->GetEpilog().IsEmpty(); )
			{
				szMessage = (!pProfileInfo->GetMessage().IsEmpty()) ? (szMessage + CR + EOL + pProfileInfo->GetEpilog()) : pProfileInfo->GetEpilog();
				break;
			}
			pInternetFile->Write((LPCTSTR)szMessage, szMessage.GetLength()*sizeof(TCHAR));
			pInternetFile->Close();
			pFtpConnection->Close();
			delete pFtpConnection;
			delete pInternetFile;
			return TRUE;
		}
		catch (CInternetException *pException)
		{
			pFtpConnection->Remove(szFileName);
			pInternetFile->Close();
			pFtpConnection->Close();
			delete pFtpConnection;
			delete pInternetFile;
			pException->Delete();
			return FALSE;
		}
	}
	return FALSE;
}

BOOL CNotificationService::DoPrinterMessageOutput(CONST CNotificationProfileInfo *pProfileInfo, LPCTSTR pszPrintProfile)
{
	CDC  cDC;
	INT  nPos;
	INT  nPage;
	INT  nPages;
	INT  nOffset;
	INT  nBorder;
	CRgn  rgClip;
	CRect  rPage;
	CRect  rText[3];
	CSize  size[5];
	CFont  cFont[6];
	CFont  *pOldFont;
	CString  szTitle;
	CString  szFooter;
	CString  szNotice[3];
	LOGFONT  lfFont[3];
	CTimeKey  tTimeKey;
	COLORREF  nColor[3];
	COLORREF  nOldColor;
	TEXTMETRIC  tmFont[3];
	CFontTools  cFontTools;
	CVersionInfo  cVersionInfo;

	if (CreatePrinterDC(pszPrintProfile, cDC))
	{
		if (pProfileInfo->GetFontInfo(&lfFont[0], nColor[0], &lfFont[1], nColor[1], &lfFont[2], nColor[2]))
		{
			for (szTitle.Format(STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_SUBJECT), (LPCTSTR)cVersionInfo.QueryProductName()), lfFont[0].lfHeight = -3 * cFontTools.QueryPixels(&cDC, lfFont[0].lfHeight) / 4, lfFont[1].lfHeight = -3 * cFontTools.QueryPixels(&cDC, lfFont[1].lfHeight) / 4, lfFont[2].lfHeight = -3 * cFontTools.QueryPixels(&cDC, lfFont[2].lfHeight) / 4, lfFont[0].lfWidth = lfFont[1].lfWidth = lfFont[2].lfWidth = 0, rPage.left = 20 * (cDC.GetDeviceCaps(HORZRES) / cDC.GetDeviceCaps(HORZSIZE)), rPage.top = 30 * (cDC.GetDeviceCaps(VERTRES) / cDC.GetDeviceCaps(VERTSIZE)), rPage.right = cDC.GetDeviceCaps(HORZRES) - rPage.left, rPage.bottom = cDC.GetDeviceCaps(VERTRES) - rPage.top / 3, size[0].cx = size[0].cy = size[1].cx = size[1].cy = size[2].cx = size[2].cy = size[3].cx = size[3].cy = size[4].cx = size[4].cy = 0, szNotice[0] = ((nPos = cVersionInfo.QueryComments().Find((szNotice[2] = cVersionInfo.QueryCompanyName()))) >= 0) ? cVersionInfo.QueryComments().Left(nPos) : cVersionInfo.QueryComments(), szNotice[1] = (nPos >= 0) ? cVersionInfo.QueryComments().Mid(nPos + szNotice[2].GetLength()) : EMPTYSTRING; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]) && cFont[2].CreateFontIndirect(&lfFont[2]) && cFont[3].CreateFont(-(INT)(((((double)rPage.Width()*(double)cDC.GetDeviceCaps(HORZSIZE)) / (20.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cFont[4].CreateFont(-(INT)(((((double)rPage.Width()*(double)cDC.GetDeviceCaps(HORZSIZE)) / (72.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cFont[5].CreateFont(-(INT)(((((double)rPage.Width()*(double)cDC.GetDeviceCaps(HORZSIZE)) / (72.0*(double)cDC.GetDeviceCaps(HORZRES)))*(double)cDC.GetDeviceCaps(VERTRES)) / (double)cDC.GetDeviceCaps(VERTSIZE)), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO)); )
			{
				for (nPage = 0, nPages = -1, nOffset = 0; nPage <= nPages || nPages < 0; nPage++)
				{
					if (nPages < 0 || ((!nPage || cDC.EndPage() >= 0) && (nPage > 0 || cDC.StartDoc(szTitle)) && cDC.StartPage() >= 0))
					{
						if ((pOldFont = (!nPage) ? cDC.SelectObject(&cFont[3]) : (CFont *)NULL))
						{
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							size[0].cy = cDC.DrawText(szTitle, CRect(rPage), (nPages < 0) ? (DT_CALCRECT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[4])))
						{
							size[1] = cDC.GetTextExtent(szNotice[0]);
							size[2] = cDC.GetTextExtent(szNotice[1]);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[5])))
						{
							size[3] = cDC.GetTextExtent(szNotice[2]);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[4])))
						{
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							szFooter.Format(STRING(IDS_NOTIFICATION_SERVICE_PRINTERMESSAGE_FOOTER), (LPCTSTR)tTimeKey.FormatGmt(IDS_TIMEKEY_DEFAULTDATEFORMAT), (LPCTSTR)tTimeKey.FormatGmt(IDS_TIMEKEY_DEFAULTTIMEFORMAT), nPage + 1, nPages + 1);
							size[4].cy = cDC.DrawText(szFooter, CRect(rPage.left, rPage.bottom - size[1].cy - max(size[1].cy, size[2].cy), rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.DrawText(szNotice[0], CRect(rPage.left, rPage.bottom - size[1].cy, rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.DrawText(szNotice[1], CRect(rPage.left + size[1].cx + size[3].cx, rPage.bottom - size[2].cy, rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						if ((pOldFont = cDC.SelectObject(&cFont[5])))
						{
							nOldColor = cDC.SetTextColor(VGA_COLOR_BLACK);
							cDC.DrawText(szNotice[2], CRect(rPage.left + size[1].cx, rPage.bottom - size[3].cy, rPage.right, rPage.bottom), (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE) : (DT_LEFT | DT_EXPANDTABS | DT_NOCLIP | DT_NOPREFIX | DT_SINGLELINE));
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						if (rgClip.CreateRectRgn(rPage.left, (!nPage) ? (rPage.top + 2 * size[0].cy) : rPage.top, rPage.right, rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy)))
						{
							if (cDC.SelectClipRgn(&rgClip, RGN_COPY) != ERROR)
							{
								if ((pOldFont = cDC.SelectObject(&cFont[0])))
								{
									nOldColor = cDC.SetTextColor(nColor[0]);
									cDC.GetTextMetrics(&tmFont[0]);
									rText[0].left = rPage.left;
									rText[0].right = rPage.right;
									rText[0].top = (!nPage) ? (rPage.top + 2 * size[0].cy) : (rPage.top - nOffset);
									rText[0].bottom = nBorder = rText[0].top + ((rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy) - rText[0].top) / tmFont[0].tmHeight)*tmFont[0].tmHeight;
									cDC.DrawText(pProfileInfo->GetProlog(), rText[0], (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX) : (DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX));
									cDC.DrawText(pProfileInfo->GetProlog(), rText[0], DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);
									if (rText[0].bottom > nBorder)
									{
										nOffset += nBorder - rPage.top;
										cDC.SetTextColor(nOldColor);
										cDC.SelectObject(pOldFont);
										rgClip.DeleteObject();
										continue;
									}
									cDC.SetTextColor(nOldColor);
									cDC.SelectObject(pOldFont);
								}
								if ((pOldFont = cDC.SelectObject(&cFont[1])))
								{
									nOldColor = cDC.SetTextColor(nColor[1]);
									cDC.GetTextMetrics(&tmFont[1]);
									rText[1].left = rPage.left;
									rText[1].right = rPage.right;
									rText[1].top = (!nPage) ? (rPage.top + 2 * size[0].cy + rText[0].Height()) : (rPage.top + rText[0].Height() - nOffset);
									rText[1].bottom = nBorder = rText[1].top + ((rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy) - rText[1].top) / tmFont[1].tmHeight)*tmFont[1].tmHeight;
									cDC.DrawText(pProfileInfo->GetMessage(), rText[1], (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX) : (DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX));
									cDC.DrawText(pProfileInfo->GetMessage(), rText[1], DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);
									if (rText[1].bottom > nBorder)
									{
										nOffset += nBorder - rPage.top;
										cDC.SetTextColor(nOldColor);
										cDC.SelectObject(pOldFont);
										rgClip.DeleteObject();
										continue;
									}
									cDC.SetTextColor(nOldColor);
									cDC.SelectObject(pOldFont);
								}
								if ((pOldFont = cDC.SelectObject(&cFont[2])))
								{
									nOldColor = cDC.SetTextColor(nColor[2]);
									cDC.GetTextMetrics(&tmFont[2]);
									rText[2].left = rPage.left;
									rText[2].right = rPage.right;
									rText[2].top = (!nPage) ? (rPage.top + 2 * size[0].cy + rText[0].Height() + rText[1].Height()) : (rPage.top + rText[0].Height() + rText[1].Height() - nOffset);
									rText[2].bottom = nBorder = rText[2].top + ((rPage.bottom - 2 * size[4].cy - max(size[1].cy, size[2].cy) - rText[2].top) / tmFont[2].tmHeight)*tmFont[2].tmHeight;
									cDC.DrawText(pProfileInfo->GetEpilog(), rText[2], (nPages < 0) ? (DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX) : (DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX));
									cDC.DrawText(pProfileInfo->GetEpilog(), rText[2], DT_CALCRECT | DT_LEFT | DT_EXPANDTABS | DT_NOPREFIX);
									if (rText[2].bottom > nBorder)
									{
										nOffset += nBorder - rPage.top;
										cDC.SetTextColor(nOldColor);
										cDC.SelectObject(pOldFont);
										rgClip.DeleteObject();
										continue;
									}
									cDC.SetTextColor(nOldColor);
									cDC.SelectObject(pOldFont);
								}
								cDC.SelectClipRgn((CRgn *)NULL);
							}
							rgClip.DeleteObject();
						}
						if (nPages < 0)
						{
							nPages = nPage;
							nOffset = 0;
							nPage = -1;
							continue;
						}
						cDC.EndPage();
					}
					break;
				}
				if (nPage == nPages)
				{
					cDC.EndDoc();
					return TRUE;
				}
				break;
			}
		}
		cDC.AbortDoc();
	}
	return FALSE;
}

CString CNotificationService::TranslateToPhoneticWord(LPCTSTR pszWord) CONST
{
	INT  nPos;
	CString  szWord;

	for (nPos = lstrlen((szWord = pszWord)) - 1; nPos >= 0; nPos--)
	{
		if (!_istdigit(pszWord[nPos])) break;
		continue;
	}
	return((nPos >= 0 && nPos < lstrlen(pszWord) - 1) ? (szWord.Left(nPos + 1) + SPACE + szWord.Mid(nPos + 1)) : szWord);
}

HANDLE CNotificationService::DoInitializeFaxService()
{
	HANDLE  hDevice;

	return((FaxConnectFaxServer((LPCTSTR)NULL, &hDevice)) ? hDevice : (HANDLE)NULL);
}

VOID CNotificationService::UninitializeFaxService(HANDLE hDevice)
{
	if (hDevice)
	{
		FaxClose(hDevice);
	}
}

BOOL CNotificationService::DoInitializePSTNService(CONST CNotificationProfileInfo *pProfileInfo)
{
	LONG  lMediaType;
	BSTR  pszDeviceName;
	CString  szDeviceName;
	VARIANT_BOOL  bMediaSupport;
	IEnumAddress  *pIEnumAddresses;
	ITMediaSupport  *pIMediaSupport;
	IConnectionPoint  *pIConnectionPoint;
	IConnectionPointContainer  *pIConnectionPointContainer;

	if ((m_pPhoneCallMonitor = new CNotificationPhoneCallMonitorSink))
	{
		if (SUCCEEDED(CoCreateInstance(CLSID_TAPI, NULL, CLSCTX_INPROC_SERVER, IID_ITTAPI2, (LPVOID *)&m_pIPhoneCallInterface)) && SUCCEEDED(m_pIPhoneCallInterface->Initialize()))
		{
			if (SUCCEEDED(m_pIPhoneCallInterface->QueryInterface(IID_IConnectionPointContainer, (void **)&pIConnectionPointContainer)))
			{
				if (SUCCEEDED(pIConnectionPointContainer->FindConnectionPoint(IID_ITTAPIEventNotification, &pIConnectionPoint)))
				{
					if (SUCCEEDED(m_pIPhoneCallInterface->put_EventFilter(TE_CALLSTATE | TE_DIGITEVENT)))
					{
						if (SUCCEEDED(pIConnectionPoint->Advise(m_pPhoneCallMonitor, &m_ulPhoneCallAdvise)))
						{
							if (SUCCEEDED(m_pIPhoneCallInterface->EnumerateAddresses(&pIEnumAddresses)))
							{
								for (bMediaSupport = VARIANT_FALSE; SUCCEEDED(pIEnumAddresses->Next(1, &m_pIPhoneCallAddress, (ULONG *)NULL)) && m_pIPhoneCallAddress != (ITAddress *)NULL; )
								{
									if (SUCCEEDED(m_pIPhoneCallAddress->get_AddressName(&pszDeviceName)) && (!pProfileInfo->GetModemInfo(szDeviceName) || !szDeviceName.CompareNoCase(CString(pszDeviceName))))
									{
										if (SUCCEEDED(m_pIPhoneCallAddress->QueryInterface(IID_ITMediaSupport, (void **)&pIMediaSupport)))
										{
											if (SUCCEEDED(pIMediaSupport->QueryMediaType((lMediaType = (pProfileInfo->GetType() == NOTIFICATIONINFO_TYPE_PHONECALL) ? TAPIMEDIATYPE_AUDIO : TAPIMEDIATYPE_DATAMODEM), &bMediaSupport)) && bMediaSupport == VARIANT_TRUE)
											{
												if (SUCCEEDED(m_pIPhoneCallInterface->RegisterCallNotifications(m_pIPhoneCallAddress, VARIANT_TRUE, VARIANT_TRUE, lMediaType, m_ulPhoneCallAdvise, &m_lPhoneCallID)))
												{
													pIConnectionPointContainer->Release();
													pIConnectionPoint->Release();
													pIEnumAddresses->Release();
													pIMediaSupport->Release();
													SysFreeString(pszDeviceName);
													return TRUE;
												}
												bMediaSupport = VARIANT_FALSE;
											}
											pIMediaSupport->Release();
										}
									}
									SysFreeString(pszDeviceName);
									m_pIPhoneCallAddress->Release();
									m_pIPhoneCallAddress = (ITAddress *)NULL;
								}
								pIEnumAddresses->Release();
							}
						}
					}
					pIConnectionPoint->Release();
				}
				pIConnectionPointContainer->Release();
			}
			m_pIPhoneCallInterface->Shutdown();
			m_pIPhoneCallInterface->Release();
			m_pIPhoneCallInterface = (ITTAPI2 *)NULL;
		}
		m_pPhoneCallMonitor = (CNotificationPhoneCallMonitorSink *)NULL;
	}
	return FALSE;
}

VOID CNotificationService::UninitializePSTNService()
{
	if (m_pIPhoneCallAddress != (ITAddress *)NULL)
	{
		m_pIPhoneCallAddress->Release();
		m_pIPhoneCallAddress = (ITAddress *)NULL;
	}
	if (m_pIPhoneCallInterface != (ITTAPI2 *)NULL)
	{
		m_pIPhoneCallInterface->UnregisterNotifications(m_lPhoneCallID);
		m_pIPhoneCallInterface->Shutdown();
		m_pIPhoneCallInterface->Release();
		m_pIPhoneCallInterface = (ITTAPI2 *)NULL;
	}
	m_pPhoneCallMonitor = (CNotificationPhoneCallMonitorSink *)NULL;
}

BOOL CNotificationService::IsEMailServiceAvailable() CONST
{
	return TRUE;
}

BOOL CNotificationService::IsFaxServiceAvailable() CONST
{
	return m_bFAXCall;
}

BOOL CNotificationService::IsPhoneCallServiceAvailable() CONST
{
	return m_bPhoneCall;
}

BOOL CNotificationService::IsPagerCallServiceAvailable() CONST
{
	return m_bPagerCall;
}

BOOL CNotificationService::IsFTPMessageServiceAvailable() CONST
{
	return TRUE;
}

BOOL CNotificationService::IsPrinterMessageServiceAvailable() CONST
{
	return TRUE;
}

BOOL CNotificationService::IsAborted() CONST
{
	return m_bExit;
}

BOOL CNotificationService::Wait(DWORD dwTimeout)
{
	return(((m_bExit = (CThread::Wait(m_bAbort, FALSE, dwTimeout) != WAIT_TIMEOUT) ? TRUE : m_bExit)) ? !m_bExit : TRUE);
}

int CNotificationService::Run()
{
	INT  nJob;
	INT  nJobs;
	INT  nIndex;
	UINT  nRetryCount;
	DWORD  dwResult;
	DWORD  dwWaitInterval;
	CTimeKey  tRetryTime;
	CTimeSpan  tRetryInterval;
	CTimeSpan  tAbortInterval;
	CNotificationProfileInfo  cProfileInfo;
	CNotificationProfileInfo  *pProfileInfo;

	do
	{
		if (Lock())
		{
			for (nJob = 0, nJobs = (INT)m_pProfiles.GetSize(), cProfileInfo.SetName(EMPTYSTRING), tRetryTime = 0, nIndex = -1; nJob < nJobs; nJob++)
			{
				if ((pProfileInfo = m_pProfiles.GetAt(nJob)) && pProfileInfo->GetRetryCount() > 0)
				{
					if (pProfileInfo->GetRetryTime() < tRetryTime || !tRetryTime.GetTime())
					{
						tRetryTime = pProfileInfo->GetRetryTime();
						nIndex = nJob;
						continue;
					}
				}
			}
			if (nIndex >= 0)
			{
				if ((pProfileInfo = m_pProfiles.GetAt(0)) && pProfileInfo->GetRetryCount() > 0)
				{
					m_pProfiles.InsertAt(0, m_pProfiles.GetAt(nIndex), 1);
					m_pProfiles.RemoveAt(nIndex + 1);
				}
			}
			for (; (pProfileInfo = m_pProfiles.GetAt(0)); )
			{
				if (pProfileInfo->GetType() != NOTIFICATIONINFO_TYPE_NONE && (pProfileInfo->GetRetryTime() <= CTime::GetCurrentTime().GetTime() || !pProfileInfo->GetRetryCount()))
				{
					cProfileInfo.Copy(pProfileInfo, TRUE);
					break;
				}
				if (pProfileInfo->GetType() == NOTIFICATIONINFO_TYPE_NONE)
				{
					m_pProfiles.RemoveAt(0);
					delete pProfileInfo;
				}
				cProfileInfo.SetName(EMPTYSTRING);
				break;
			}
			Unlock();
		}
		if (cProfileInfo.GetName().IsEmpty())
		{
			dwWaitInterval = (tRetryTime > 0) ? (DWORD)(1000 * (max(tRetryTime.GetTime() - CTime::GetCurrentTime().GetTime(), 0) % SECONDSPERDAY)) : INFINITE;
			continue;
		}
		if (DoNotification(&cProfileInfo))
		{
			for (Lock(); (pProfileInfo = m_pProfiles.GetAt(0)); )
			{
				if (pProfileInfo->GetName() == cProfileInfo.GetName())
				{
					m_pProfiles.RemoveAt(0);
					delete pProfileInfo;
				}
				break;
			}
			dwWaitInterval = 0;
			Unlock();
			continue;
		}
		for (Lock(); (pProfileInfo = m_pProfiles.GetAt(0)); )
		{
			if (pProfileInfo->GetName() == cProfileInfo.GetName())
			{
				if (!cProfileInfo.GetBehaviorInfo(nRetryCount, tRetryInterval, tAbortInterval) || nRetryCount < cProfileInfo.GetRetryCount())
				{
					m_pProfiles.RemoveAt(0);
					delete pProfileInfo;
					break;
				}
				pProfileInfo->Copy(&cProfileInfo, TRUE);
			}
			break;
		}
		dwWaitInterval = 0;
		Unlock();
		continue;
	} while ((dwResult = (dwWaitInterval > 0) ? CThread::Wait(m_bUpdate, FALSE, dwWaitInterval) : WAIT_TIMEOUT) == WAIT_OBJECT_0 + 1 || dwResult == WAIT_TIMEOUT);
	return 0;
}

BEGIN_MESSAGE_MAP(CNotificationService, CThread)
	//{{AFX_MSG_MAP(CNotificationService)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotificationService message handlers


/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadProfileInfo

CToolsDownloadProfileInfo::CToolsDownloadProfileInfo() : CObject()
{
	SetName(STRING(IDS_TOOLSDOWNLOADS_DEFAULT_NAME));
	SetOptions(TOOLSDOWNLOADINFO_OPTION_TRANSFERASASCII);
	SetFTPPort(0);
	SetExecutionMode(0);
	SetExecutionCycle(0);
	SetLastExecutionTime(0);
}

CToolsDownloadProfileInfo::~CToolsDownloadProfileInfo()
{
	return;
}

VOID CToolsDownloadProfileInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CToolsDownloadProfileInfo::GetName() CONST
{
	return m_szName;
}

VOID CToolsDownloadProfileInfo::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CToolsDownloadProfileInfo::GetOptions() CONST
{
	return m_nOptions;
}

VOID CToolsDownloadProfileInfo::SetExecutionMode(UINT nMode)
{
	if (nMode == TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY || nMode == TOOLSDOWNLOADINFO_EXECUTION_ATTIME || nMode == TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME || nMode == TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL || nMode == TOOLSDOWNLOADINFO_EXECUTION_ATEVENT || !nMode)
	{
		if ((m_nMode = nMode) == 0)
		{
			m_tExecution[0] = 0;
			m_tExecution[1] = 0;
			m_tExecution[2] = 0;
			m_tDailyExecution = 0;
			m_tExecutionDelay = 0;
			m_tIntervalExecution = 0;
		}
	}
}

UINT CToolsDownloadProfileInfo::GetExecutionMode() CONST
{
	return m_nMode;
}

VOID CToolsDownloadProfileInfo::SetExecutionCycle(UINT nCycle)
{
	m_nCycleCount = nCycle;
}

UINT CToolsDownloadProfileInfo::GetExecutionCycle() CONST
{
	return m_nCycleCount;
}

VOID CToolsDownloadProfileInfo::SetExecutionTime(CONST CTimeKey &tTime)
{
	if (m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATTIME)
	{
		m_tExecution[0] = tTime;
		return;
	}
}

CTimeKey CToolsDownloadProfileInfo::GetExecutionTime() CONST
{
	return((m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATTIME) ? m_tExecution[0] : CTimeKey(0));
}

VOID CToolsDownloadProfileInfo::SetDailyExecutionTime(CONST CTimeSpan &tTime)
{
	if (m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME)
	{
		m_tDailyExecution = tTime;
		return;
	}
}

CTimeSpan CToolsDownloadProfileInfo::GetDailyExecutionTime() CONST
{
	return((m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME) ? m_tDailyExecution : CTimeSpan(0));
}

VOID CToolsDownloadProfileInfo::SetPeriodicalExecutionTime(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if (m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL)
	{
		m_tExecution[1] = tStartTime;
		m_tExecution[2] = tStopTime;
		m_tIntervalExecution = tInterval;
	}
}

BOOL CToolsDownloadProfileInfo::GetPeriodicalExecutionTime(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if (m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL)
	{
		tStartTime = m_tExecution[1];
		tStopTime = m_tExecution[2];
		tInterval = m_tIntervalExecution;
		return TRUE;
	}
	return FALSE;
}

VOID CToolsDownloadProfileInfo::SetTriggeredExecution(LPCTSTR pszEvent, CONST CTimeSpan &tDelay)
{
	if (m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATEVENT)
	{
		m_szExecutionEvent = pszEvent;
		m_tExecutionDelay = tDelay;
	}
}

CString CToolsDownloadProfileInfo::GetTriggeredExecution(CTimeSpan &tDelay) CONST
{
	if (m_nMode == TOOLSDOWNLOADINFO_EXECUTION_ATEVENT)
	{
		tDelay = m_tExecutionDelay;
		return m_szExecutionEvent;
	}
	return EMPTYSTRING;
}

VOID CToolsDownloadProfileInfo::SetLastExecutionTime(CONST CTimeKey &tTime)
{
	m_tLastExecution = tTime;
}

CTimeKey CToolsDownloadProfileInfo::GetLastExecutionTime() CONST
{
	return m_tLastExecution;
}

VOID CToolsDownloadProfileInfo::SetFiles(CString &szFiles)
{
	m_szFiles = szFiles;
}

CString CToolsDownloadProfileInfo::GetFiles() CONST
{
	return m_szFiles;
}

VOID CToolsDownloadProfileInfo::SetDirectory(LPCTSTR pszDirectory)
{
	m_szDirectory = pszDirectory;
}

CString CToolsDownloadProfileInfo::GetDirectory() CONST
{
	return m_szDirectory;
}

VOID CToolsDownloadProfileInfo::SetFTPLocation(LPCTSTR pszLocation)
{
	m_szFTPLocation = pszLocation;
}

CString CToolsDownloadProfileInfo::GetFTPLocation() CONST
{
	return m_szFTPLocation;
}

VOID CToolsDownloadProfileInfo::SetFTPUserName(LPCTSTR pszUserName)
{
	m_szFTPUserName = pszUserName;
}

CString CToolsDownloadProfileInfo::GetFTPUserName() CONST
{
	return m_szFTPUserName;
}

VOID CToolsDownloadProfileInfo::SetFTPPassword(LPCTSTR pszPassword)
{
	m_szFTPPassword = pszPassword;
}

CString CToolsDownloadProfileInfo::GetFTPPassword() CONST
{
	return m_szFTPPassword;
}

VOID CToolsDownloadProfileInfo::SetFTPPort(UINT nPort)
{
	m_nFTPPort = nPort;
}

UINT CToolsDownloadProfileInfo::GetFTPPort() CONST
{
	return m_nFTPPort;
}

VOID CToolsDownloadProfileInfo::Copy(CONST CToolsDownloadProfileInfo *pProfileInfo)
{
	m_szName = pProfileInfo->m_szName;
	m_nMode = pProfileInfo->m_nMode;
	m_nOptions = pProfileInfo->m_nOptions;
	m_nCycleCount = pProfileInfo->m_nCycleCount;
	m_tExecution[0] = pProfileInfo->m_tExecution[0];
	m_tExecution[1] = pProfileInfo->m_tExecution[1];
	m_tExecution[2] = pProfileInfo->m_tExecution[2];
	m_tLastExecution = pProfileInfo->m_tLastExecution;
	m_tDailyExecution = pProfileInfo->m_tDailyExecution;
	m_tExecutionDelay = pProfileInfo->m_tExecutionDelay;
	m_tIntervalExecution = pProfileInfo->m_tIntervalExecution;
	m_szExecutionEvent = pProfileInfo->m_szExecutionEvent;
	m_szFiles = pProfileInfo->m_szFiles;
	m_nFTPPort = pProfileInfo->m_nFTPPort;
	m_szDirectory = pProfileInfo->m_szDirectory;
	m_szFTPLocation = pProfileInfo->m_szFTPLocation;
	m_szFTPUserName = pProfileInfo->m_szFTPUserName;
	m_szFTPPassword = pProfileInfo->m_szFTPPassword;
}

BOOL CToolsDownloadProfileInfo::Compare(CONST CToolsDownloadProfileInfo *pProfileInfo) CONST
{
	return((pProfileInfo->m_szName == m_szName  &&  pProfileInfo->m_nOptions == m_nOptions  &&  pProfileInfo->m_nMode == m_nMode && ((m_nMode != TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY  &&  m_nMode != TOOLSDOWNLOADINFO_EXECUTION_ATTIME) || pProfileInfo->m_tExecution[0] == m_tExecution[0]) && (m_nMode != TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME || pProfileInfo->m_tDailyExecution == m_tDailyExecution) && (m_nMode != TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL || (pProfileInfo->m_tExecution[1] == m_tExecution[1] && pProfileInfo->m_tIntervalExecution == m_tIntervalExecution  &&  pProfileInfo->m_tExecution[2] == m_tExecution[2])) && (m_nMode != TOOLSDOWNLOADINFO_EXECUTION_ATEVENT || (pProfileInfo->m_szExecutionEvent == m_szExecutionEvent  &&  pProfileInfo->m_tExecutionDelay == m_tExecutionDelay)) && pProfileInfo->m_tLastExecution == m_tLastExecution  &&  !pProfileInfo->m_szFiles.CompareNoCase(m_szFiles) && !pProfileInfo->m_szDirectory.CompareNoCase(m_szDirectory) && !pProfileInfo->m_szFTPLocation.CompareNoCase(m_szFTPLocation) && pProfileInfo->m_szFTPUserName == m_szFTPUserName  &&  pProfileInfo->m_szFTPPassword == m_szFTPPassword  &&  pProfileInfo->m_nFTPPort == m_nFTPPort) ? TRUE : FALSE);
}

BOOL CToolsDownloadProfileInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFiles = (m_szFiles.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDirectory = (m_szDirectory.GetLength() + 1)*sizeof(TCHAR);
	sData.cbExecutionEvent = (m_szExecutionEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPLocation = (m_szFTPLocation.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPUserName = (m_szFTPUserName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPPassword = (m_szFTPPassword.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbFiles + sData.cbDirectory + sData.cbExecutionEvent + sData.cbFTPLocation + sData.cbFTPUserName + sData.cbFTPPassword)), sData.nMode = m_nMode, sData.nOptions = m_nOptions, sData.tExecution[0] = m_tExecution[0].GetTime(), sData.tExecution[1] = m_tExecution[1].GetTime(), sData.tExecution[2] = m_tExecution[2].GetTime(), sData.tExecutionDelay = m_tExecutionDelay.GetTotalSeconds(), sData.tDailyExecution = m_tDailyExecution.GetTotalSeconds(), sData.tIntervalExecution = m_tIntervalExecution.GetTotalSeconds(), sData.tLastExecution = m_tLastExecution.GetTime(), sData.nCycleCount = m_nCycleCount, sData.nFTPPort = m_nFTPPort; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szFiles, sData.cbFiles);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFiles), (LPCTSTR)m_szDirectory, sData.cbDirectory);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDirectory), (LPCTSTR)m_szExecutionEvent, sData.cbExecutionEvent);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbExecutionEvent), (LPCTSTR)m_szFTPLocation, sData.cbFTPLocation);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPLocation), (LPCTSTR)m_szFTPUserName, sData.cbFTPUserName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPUserName), (LPCTSTR)m_szFTPPassword, sData.cbFTPPassword);
		return TRUE;
	}
	return FALSE;
}

BOOL CToolsDownloadProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbFiles + sData.cbDirectory + sData.cbExecutionEvent + sData.cbFTPLocation + sData.cbFTPUserName + sData.cbFTPPassword && sData.cbName > 0 && sData.cbFiles > 0 && sData.cbDirectory > 0 && sData.cbExecutionEvent > 0 && sData.cbFTPLocation > 0 && sData.cbFTPUserName > 0 && sData.cbFTPPassword > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szFiles.GetBufferSetLength(STRINGCHARS(sData.cbFiles)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbFiles));
		CopyMemory(m_szDirectory.GetBufferSetLength(STRINGCHARS(sData.cbDirectory)), nInfo.GetData() + (cbData = cbData + sData.cbFiles), STRINGBYTES(sData.cbDirectory));
		CopyMemory(m_szExecutionEvent.GetBufferSetLength(STRINGCHARS(sData.cbExecutionEvent)), nInfo.GetData() + (cbData = cbData + sData.cbDirectory), STRINGBYTES(sData.cbExecutionEvent));
		CopyMemory(m_szFTPLocation.GetBufferSetLength(STRINGCHARS(sData.cbFTPLocation)), nInfo.GetData() + (cbData = cbData + sData.cbExecutionEvent), STRINGBYTES(sData.cbFTPLocation));
		CopyMemory(m_szFTPUserName.GetBufferSetLength(STRINGCHARS(sData.cbFTPUserName)), nInfo.GetData() + (cbData = cbData + sData.cbFTPLocation), STRINGBYTES(sData.cbFTPUserName));
		CopyMemory(m_szFTPPassword.GetBufferSetLength(STRINGCHARS(sData.cbFTPPassword)), nInfo.GetData() + (cbData = cbData + sData.cbFTPUserName), STRINGBYTES(sData.cbFTPPassword));
		m_nMode = sData.nMode;
		m_nOptions = sData.nOptions;
		m_tExecution[0] = sData.tExecution[0];
		m_tExecution[1] = sData.tExecution[1];
		m_tExecution[2] = sData.tExecution[2];
		m_tExecutionDelay = sData.tExecutionDelay;
		m_tDailyExecution = sData.tDailyExecution;
		m_tIntervalExecution = sData.tIntervalExecution;
		m_tLastExecution = sData.tLastExecution;
		m_nCycleCount = sData.nCycleCount;
		m_nFTPPort = sData.nFTPPort;
		m_szName.ReleaseBuffer();
		m_szFiles.ReleaseBuffer();
		m_szDirectory.ReleaseBuffer();
		m_szExecutionEvent.ReleaseBuffer();
		m_szFTPLocation.ReleaseBuffer();
		m_szFTPUserName.ReleaseBuffer();
		m_szFTPPassword.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadProfiles

CToolsDownloadProfiles::CToolsDownloadProfiles() : CMutexArray()
{
	return;
}

CToolsDownloadProfiles::~CToolsDownloadProfiles()
{
	RemoveAll();
}

INT CToolsDownloadProfiles::Add(CToolsDownloadProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CToolsDownloadProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CToolsDownloadProfiles::Enum(CStringArray &szNames) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CToolsDownloadProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), szNames.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) != (CToolsDownloadProfileInfo *)NULL)
		{
			szNames.Add(pProfileInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CToolsDownloadProfileInfo *CToolsDownloadProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CToolsDownloadProfileInfo *)CMutexArray::GetAt(nIndex) : (CToolsDownloadProfileInfo *)NULL);
}

CToolsDownloadProfileInfo *CToolsDownloadProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CToolsDownloadProfileInfo *)CMutexArray::GetAt(nIndex) : (CToolsDownloadProfileInfo *)NULL);
}

VOID CToolsDownloadProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;
	CToolsDownloadProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile))) delete pProfileInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CToolsDownloadProfiles::Copy(CONST CToolsDownloadProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CToolsDownloadProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CToolsDownloadProfileInfo))
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CToolsDownloadProfiles::Compare(CONST CToolsDownloadProfiles *pProfiles) CONST
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (pProfiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if (!pProfiles->GetAt(nProfile)->Compare(GetAt(nProfile))) break;
		continue;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CToolsDownloadProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfileData;
	CToolsDownloadProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfileData) && nInfo.Append(nProfileData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CToolsDownloadProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfileData;
	CToolsDownloadProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfileData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfileData.GetSize() >= 0; )
		{
			CopyMemory(nProfileData.GetData(), nInfo.GetData() + cbProfiles, nProfileData.GetSize());
			break;
		}
		if ((pProfileInfo = new CToolsDownloadProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfileData) && Add(pProfileInfo) >= 0) continue;
			delete pProfileInfo;
		}
		break;
	}
	if ((pProfileInfo = (!nInfo.GetSize()) ? new CToolsDownloadProfileInfo : (CToolsDownloadProfileInfo *)NULL))
	{
		for (pProfileInfo->SetName(STRING(IDS_TOOLSDOWNLOADS_DEFAULT_NAME)); Add(pProfileInfo) >= 0; ) return TRUE;
		delete pProfileInfo;
		return FALSE;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CToolsDownloadProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CToolsDownloadProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfileInfo->GetName() == pszName) || (bInsert && (((pProfileInfo = GetAt(max(nIndex[0] - 1, 0))) && pProfileInfo->GetName() != pszName && (pProfileInfo = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pProfileInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadService

IMPLEMENT_DYNCREATE(CToolsDownloadService, CThread)

CToolsDownloadService::CToolsDownloadService() : CThread()
{
	return;
}

BOOL CToolsDownloadService::Start()
{
	CToolsDownloadProfiles  pProfiles;

	if (CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL))
	{
		if (GetToolsDownloadProfiles(pProfiles))
		{
			Update(pProfiles);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CToolsDownloadService::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CToolsDownloadService::Update(CONST CToolsDownloadProfiles &pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	BOOL  bProfiles;
	UINT  nExecutionCycle;
	CTimeKey  tDownload;
	CTimeKey  tExecution;
	CTimeKey  tStopTime[2];
	CTimeKey  tStartTime[2];
	CTimeSpan  tInterval[2];
	CTimeSpan  tTriggerDelay[2];
	CToolsDownloadProfileInfo  *pProfileInfo[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProfile = 0, nProfiles = (INT)pProfiles.GetSize(), bProfiles = TRUE; nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo[0] = pProfiles.GetAt(nProfile)) != (CToolsDownloadProfileInfo *)NULL)
		{
			if ((pProfileInfo[1] = m_pProfiles.GetAt(m_pProfiles.Find(pProfileInfo[0]->GetName()))))
			{
				if (pProfileInfo[0]->GetExecutionMode() != pProfileInfo[1]->GetExecutionMode() || pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY || ((pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATTIME  &&  pProfileInfo[0]->GetExecutionTime() != pProfileInfo[1]->GetExecutionTime()) || (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME  &&  pProfileInfo[0]->GetDailyExecutionTime() != pProfileInfo[1]->GetDailyExecutionTime()) || (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL  &&  pProfileInfo[0]->GetPeriodicalExecutionTime(tStartTime[0], tInterval[0], tStopTime[0]) && pProfileInfo[1]->GetPeriodicalExecutionTime(tStartTime[1], tInterval[1], tStopTime[1]) && (tStartTime[0] != tStartTime[1] || tStopTime[0] != tStopTime[1] || tInterval[0] != tInterval[1])) || (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATEVENT && (pProfileInfo[0]->GetTriggeredExecution(tTriggerDelay[0]) != pProfileInfo[1]->GetTriggeredExecution(tTriggerDelay[1]) || tTriggerDelay[0] != tTriggerDelay[1]))))
				{
					pProfileInfo[1]->Copy(pProfileInfo[0]);
					pProfileInfo[1]->SetLastExecutionTime(0);
					pProfileInfo[1]->SetExecutionCycle(0);
					continue;
				}
				for (tExecution = pProfileInfo[1]->GetLastExecutionTime(), nExecutionCycle = pProfileInfo[1]->GetExecutionCycle(); TRUE; )
				{
					pProfileInfo[1]->Copy(pProfileInfo[0]);
					pProfileInfo[1]->SetLastExecutionTime(tExecution);
					pProfileInfo[1]->SetExecutionCycle(nExecutionCycle);
					break;
				}
				continue;
			}
			if ((pProfileInfo[1] = new CToolsDownloadProfileInfo))
			{
				pProfileInfo[1]->Copy(pProfileInfo[0]);
				if (m_pProfiles.Add(pProfileInfo[1]) >= 0) continue;
				delete pProfileInfo[1];
			}
		}
		bProfiles = FALSE;
		break;
	}
	for (nProfile = 0, nProfiles = (INT)m_pProfiles.GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo[0] = m_pProfiles.GetAt(nProfile)) != (CToolsDownloadProfileInfo *)NULL)
		{
			if ((pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY || pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATTIME) && pProfileInfo[0]->GetLastExecutionTime().GetTime() != 0)
			{
				m_pProfiles.RemoveAt(nProfile);
				delete pProfileInfo[0];
				nProfiles--;
				nProfile--;
				continue;
			}
			if (pProfiles.Find(pProfileInfo[0]->GetName()) < 0)
			{
				m_pProfiles.RemoveAt(nProfile);
				delete pProfileInfo[0];
				nProfiles--;
				nProfile--;
				continue;
			}
		}
	}
	for (nProfile = 0; nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo[0] = m_pProfiles.GetAt(nProfile)) != (CToolsDownloadProfileInfo *)NULL)
		{
			if ((pProfileInfo[0]->GetOptions() & TOOLSDOWNLOADINFO_OPTION_DISABLED) != TOOLSDOWNLOADINFO_OPTION_DISABLED)
			{
				if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME)
				{
					if (pProfileInfo[0]->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY > tDownload.GetTime() % SECONDSPERDAY)
					{
						pProfileInfo[0]->SetLastExecutionTime(SECONDSPERDAY*(tDownload.GetTime() / SECONDSPERDAY - 1) + pProfileInfo[0]->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY);
						continue;
					}
					pProfileInfo[0]->SetLastExecutionTime(SECONDSPERDAY*(tDownload.GetTime() / SECONDSPERDAY) + pProfileInfo[0]->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY);
					continue;
				}
				if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL  &&  pProfileInfo[0]->GetPeriodicalExecutionTime(tStartTime[0], tInterval[0], tStopTime[0]))
				{
					if (tStopTime[0].GetTime() < tDownload.GetTime())
					{
						m_pProfiles.RemoveAt(nProfile);
						delete pProfileInfo[0];
						nProfiles--;
						nProfile--;
						continue;
					}
					pProfileInfo[0]->SetExecutionCycle((tStartTime[0] < tDownload) ? (UINT)((tDownload.GetTime() - tStartTime[0].GetTime()) / tInterval[0].GetTotalSeconds() + 1) : 0);
				}
				continue;
			}
		}
		m_pProfiles.RemoveAt(nProfile);
		delete pProfileInfo[0];
		nProfiles--;
		nProfile--;
	}
	m_bUpdate.SetEvent();
	return bProfiles;
}
BOOL CToolsDownloadService::Update(CONST CToolsDownloadProfileInfo *pProfile)
{
	CTimeKey  tDownload;
	CToolsDownloadProfileInfo  *pProfileInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProfileInfo = new CToolsDownloadProfileInfo))
	{
		for (pProfileInfo->Copy(pProfile), pProfileInfo->SetName(pProfileInfo->GetName() + EOL + tDownload.FormatGmt()); m_pProfiles.Add(pProfileInfo) >= 0; )
		{
			m_bUpdate.SetEvent();
			return TRUE;
		}
		delete pProfileInfo;
	}
	return FALSE;
}

BOOL CToolsDownloadService::Refresh(CToolsDownloadProfiles &pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CTimeKey  tTimeKey;
	CToolsDownloadProfileInfo  *pProfileInfo[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProfile = 0, nProfiles = (INT)pProfiles.GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo[0] = pProfiles.GetAt(nProfile)) != (CToolsDownloadProfileInfo *)NULL)
		{
			if ((pProfileInfo[1] = m_pProfiles.GetAt(m_pProfiles.Find(pProfileInfo[0]->GetName()))))
			{
				pProfileInfo[0]->SetLastExecutionTime(pProfileInfo[1]->GetLastExecutionTime());
				pProfileInfo[0]->SetExecutionCycle(pProfileInfo[1]->GetExecutionCycle());
				continue;
			}
			if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY)
			{
				pProfileInfo[0]->SetLastExecutionTime(tTimeKey);
				continue;
			}
			if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATTIME  &&  pProfileInfo[0]->GetExecutionTime() <= tTimeKey)
			{
				pProfileInfo[0]->SetLastExecutionTime(pProfileInfo[0]->GetExecutionTime());
				continue;
			}
		}
	}
	return TRUE;
}

VOID CToolsDownloadService::Download(CONST CToolsDownloadProfileInfo *pProfileInfo)
{
	INT  nFile;
	INT  nFiles;
	INT  nError;
	INT  nErrors;
	INT  nPos[2];
	DWORD  dwService;
	CString  szProfile;
	CString  szMessage;
	CString  szFileName;
	CString  szFileTitle;
	CString  szDirectory;
	CString  szFTPServer;
	CString  szFTPDirectory;
	CString  szTempDirectory;
	CString  szTempFileName;
	CString  szFileNames;
	CStringArray  szFiles;
	CStringArray  szErrors;
	INTERNET_PORT  nFTPPort;
	CLogicalDrives  cDrives;
	CFtpConnection  *pFtpConnection;
	CInternetSession  cInternetSession;
	CSecurityDescriptor  cSecurityDescriptor;

	for (szProfile = ((nPos[0] = pProfileInfo->GetName().Find(EOL)) >= 0) ? pProfileInfo->GetName().Left(nPos[0]) : pProfileInfo->GetName(), szFileNames = pProfileInfo->GetFiles(), szDirectory = pProfileInfo->GetDirectory(); !szFileNames.IsEmpty(); )
	{
		nPos[0] = szFileNames.Find(STRING(IDS_TOOLSDOWNLOADS_FILENAME_SEPARATOR_SEMICOLON));
		nPos[1] = szFileNames.Find(STRING(IDS_TOOLSDOWNLOADS_FILENAME_SEPARATOR_COMMA));
		if ((nPos[0] < nPos[1] && nPos[0] >= 0) || (nPos[0] >= 0 && nPos[1] < 0))
		{
			szFiles.Add(szFileNames.Left(nPos[0]));
			szFileNames = szFileNames.Mid(nPos[0]);
			szFileNames = szFileNames.Mid(lstrlen(STRING(IDS_TOOLSDOWNLOADS_FILENAME_SEPARATOR_SEMICOLON)));
			continue;
		}
		if ((nPos[0] > nPos[1] && nPos[1] >= 0) || (nPos[1] >= 0 && nPos[0] < 0))
		{
			szFiles.Add(szFileNames.Left(nPos[1]));
			szFileNames = szFileNames.Mid(nPos[1]);
			szFileNames = szFileNames.Mid(lstrlen(STRING(IDS_TOOLSDOWNLOADS_FILENAME_SEPARATOR_COMMA)));
			continue;
		}
		szFiles.Add(szFileNames);
		break;
	}
	if (AfxParseURL(pProfileInfo->GetFTPLocation(), dwService, szFTPServer, szFTPDirectory, nFTPPort) && dwService == AFX_INET_SERVICE_FTP)
	{
		try
		{
			pFtpConnection = cInternetSession.GetFtpConnection(szFTPServer, pProfileInfo->GetFTPUserName(), pProfileInfo->GetFTPPassword(), (!pProfileInfo->GetFTPPort()) ? nFTPPort : pProfileInfo->GetFTPPort());
		}
		catch (CInternetException *pException)
		{
			ReportEvent((pProfileInfo->GetOptions() & TOOLSDOWNLOADINFO_OPTION_AUDITION) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING) : 0, STRING(IDS_TOOLSDOWNLOAD_SERVICE_FAILURE), FALSE);
			pException->Delete();
			return;
		}
		try
		{
			for (nFile = 0, nFiles = (INT)szFiles.GetSize(); nFile < nFiles; nFile++)
			{
				if (szFiles.GetAt(nFile).IsEmpty())
				{
					szFiles.RemoveAt(nFile);
					nFiles--;
					nFile--;
					continue;
				}
				for (GetTempPath(MAX_PATH, szTempDirectory.GetBufferSetLength(MAX_PATH)), szTempDirectory.ReleaseBuffer(), szFTPDirectory = (szFTPDirectory.Left(lstrlen(STRING(IDS_INTERNET_DELIMITER))) == STRING(IDS_INTERNET_DELIMITER)) ? szFTPDirectory.Mid(lstrlen(STRING(IDS_INTERNET_DELIMITER))) : szFTPDirectory, szFileName = (!szDirectory.IsEmpty()) ? ((szDirectory.Right(CString(cDrives.GetPathDelimiter()).GetLength()) != cDrives.GetPathDelimiter()) ? (szDirectory + cDrives.GetPathDelimiter() + szFiles.GetAt(nFile)) : (szDirectory + szFiles.GetAt(nFile))) : ((szTempDirectory.Right(CString(cDrives.GetPathDelimiter()).GetLength()) != cDrives.GetPathDelimiter()) ? (szTempDirectory + cDrives.GetPathDelimiter() + szFiles.GetAt(nFile)) : (szTempDirectory + szFiles.GetAt(nFile))), GetTempFileName(szTempDirectory, EMPTYSTRING, 0, szTempFileName.GetBufferSetLength(MAX_PATH)), szTempFileName.ReleaseBuffer(); !szFTPDirectory.IsEmpty(); )
				{
					pFtpConnection->SetCurrentDirectory(szFTPDirectory);
					break;
				}
				if (pFtpConnection->GetFile(szFiles.GetAt(nFile), szTempFileName, FALSE, FILE_ATTRIBUTE_NORMAL, (pProfileInfo->GetOptions() & TOOLSDOWNLOADINFO_OPTION_TRANSFERASBINARY) ? FTP_TRANSFER_TYPE_BINARY : FTP_TRANSFER_TYPE_ASCII))
				{
					if (cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ))
					{
						if (MoveFileEx(szTempFileName, szFileName, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING))
						{
							if (pProfileInfo->GetOptions() & TOOLSDOWNLOADINFO_OPTION_DELETEFILES) pFtpConnection->Remove(szFiles.GetAt(nFile));
							CSecurity::SecureFile(szFileName, cSecurityDescriptor);
							continue;
						}
					}
					CFileEx::Remove(szTempFileName);
				}
				szFileTitle.Format(STRING(IDS_TOOLSDOWNLOAD_SERVICE_PARTSTEXT), (LPCTSTR)szFiles.GetAt(nFile));
				szErrors.Add(szFileTitle);
			}
			if (pProfileInfo->GetOptions() & TOOLSDOWNLOADINFO_OPTION_AUDITION)
			{
				for (nError = 0, nErrors = (INT)(szErrors.GetSize() - 1), szFileNames.Empty(); nError < nErrors; nError++)
				{
					szFileNames += (!szFileNames.IsEmpty()) ? (STRING(IDS_TOOLSDOWNLOAD_SERVICE_SEPARATOR) + szErrors.GetAt(nError)) : szErrors.GetAt(nError);
					continue;
				}
				if (szErrors.GetSize() > 1)
				{
					szMessage.Format(STRING(IDS_TOOLSDOWNLOAD_SERVICE_FAILURE_NOFILES), (LPCTSTR)szProfile, (LPCTSTR)szFileNames, (LPCTSTR)szErrors.GetAt(szErrors.GetUpperBound()));
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				}
				if (szErrors.GetSize() == 1)
				{
					szMessage.Format(STRING(IDS_TOOLSDOWNLOAD_SERVICE_FAILURE_NOFILE), (LPCTSTR)szProfile, (LPCTSTR)szErrors.GetAt(szErrors.GetUpperBound()));
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				}
				if (szFiles.GetSize() > 0 && !szErrors.GetSize())
				{
					szMessage.Format(STRING(IDS_TOOLSDOWNLOAD_SERVICE_SUCCESS), (LPCTSTR)szProfile);
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				}
			}
			pFtpConnection->Close();
			delete pFtpConnection;
			return;
		}
		catch (CInternetException *pException)
		{
			pFtpConnection->Close();
			delete pFtpConnection;
			pException->Delete();
		}
	}
	ReportEvent((pProfileInfo->GetOptions() & TOOLSDOWNLOADINFO_OPTION_AUDITION) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING) : 0, STRING(IDS_TOOLSDOWNLOAD_SERVICE_FAILURE), FALSE);
}

int CToolsDownloadService::Run()
{
	INT  nIndex;
	INT  nProfile;
	INT  nProfiles;
	DWORD  dwResult;
	DWORD  dwTimeout;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeKey  tExecution[2];
	CTimeSpan  tInterval[1];
	CToolsDownloadProfileInfo  *pProfileInfo[2];

	do
	{
		for (dwTimeout = INFINITE, pProfileInfo[0] = pProfileInfo[1] = (CToolsDownloadProfileInfo *)NULL; Lock(); )
		{
			for (nProfile = 0, nProfiles = (INT)m_pProfiles.GetSize(), tExecution[0] = CTime::GetCurrentTime().GetTime(), tExecution[1] = 0, nIndex = -1; nProfile < nProfiles; nProfile++)
			{
				if ((pProfileInfo[0] = m_pProfiles.GetAt(nProfile)) != (CToolsDownloadProfileInfo *)NULL)
				{
					if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY)
					{
						if (tExecution[0] < tExecution[1] || !tExecution[1].GetTime())
						{
							tExecution[1] = tExecution[0];
							nIndex = nProfile;
						}
						continue;
					}
					if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATTIME)
					{
						if (pProfileInfo[0]->GetExecutionTime() < tExecution[1] || !tExecution[1].GetTime())
						{
							tExecution[1] = pProfileInfo[0]->GetExecutionTime();
							nIndex = nProfile;
						}
						continue;
					}
					if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATDAILYTIME)
					{
						if (((pProfileInfo[0]->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecution[0].GetTime() / SECONDSPERDAY  &&  SECONDSPERDAY*(tExecution[0].GetTime() / SECONDSPERDAY) + pProfileInfo[0]->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY < tExecution[1].GetTime()) || (pProfileInfo[0]->GetLastExecutionTime().GetTime() / SECONDSPERDAY >= tExecution[0].GetTime() / SECONDSPERDAY  &&  SECONDSPERDAY*(tExecution[0].GetTime() / SECONDSPERDAY + 1) + pProfileInfo[0]->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY < tExecution[1].GetTime())) || !tExecution[1].GetTime())
						{
							tExecution[1] = (pProfileInfo[0]->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tExecution[0].GetTime() / SECONDSPERDAY) ? (SECONDSPERDAY*(tExecution[0].GetTime() / SECONDSPERDAY) + pProfileInfo[0]->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY) : (SECONDSPERDAY*(tExecution[0].GetTime() / SECONDSPERDAY + 1) + pProfileInfo[0]->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY);
							nIndex = nProfile;
						}
						continue;
					}
					if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATINTERVAL)
					{
						if (pProfileInfo[0]->GetPeriodicalExecutionTime(tStartTime, tInterval[0], tStopTime) && tExecution[0] <= tStopTime)
						{
							if (tStartTime.GetTime() + pProfileInfo[0]->GetExecutionCycle()*tInterval[0].GetTotalSeconds() < tExecution[1].GetTime() || !tExecution[1].GetTime())
							{
								tExecution[1] = tStartTime.GetTime() + pProfileInfo[0]->GetExecutionCycle()*tInterval[0].GetTotalSeconds();
								nIndex = nProfile;
							}
							continue;
						}
					}
				}
				m_pProfiles.RemoveAt(nProfile);
				delete pProfileInfo[0];
				nProfiles--;
				nProfile--;
			}
			if (tExecution[0] >= tExecution[1] && nIndex >= 0)
			{
				if ((pProfileInfo[0] = m_pProfiles.GetAt(nIndex)))
				{
					if ((pProfileInfo[1] = new CToolsDownloadProfileInfo)) pProfileInfo[1]->Copy(pProfileInfo[0]);
					if (pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY || pProfileInfo[0]->GetExecutionMode() == TOOLSDOWNLOADINFO_EXECUTION_ATTIME)
					{
						m_pProfiles.RemoveAt(nIndex);
						delete pProfileInfo[0];
					}
					else
					{
						pProfileInfo[0]->SetExecutionCycle(pProfileInfo[0]->GetExecutionCycle() + 1);
						pProfileInfo[0]->SetLastExecutionTime(tExecution[1]);
					}
				}
			}
			dwTimeout = (nIndex >= 0) ? ((tExecution[0] < tExecution[1]) ? (DWORD)min(tExecution[1].GetTime() - tExecution[0].GetTime(), SECONDSPERDAY) : 0) : INFINITE;
			Unlock();
			break;
		}
		if (pProfileInfo[1] != (CToolsDownloadProfileInfo *)NULL)
		{
			Download(pProfileInfo[1]);
			delete pProfileInfo[1];
		}
	} while ((dwResult = Wait(m_bUpdate, FALSE, (dwTimeout != INFINITE) ? (1000 * dwTimeout) : INFINITE)) == WAIT_TIMEOUT || dwResult == WAIT_OBJECT_0 + 1);
	return 0;
}

BEGIN_MESSAGE_MAP(CToolsDownloadService, CThread)
	//{{AFX_MSG_MAP(CToolsDownloadService)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadService message handlers


/////////////////////////////////////////////////////////////////////////////
// CToolsDatabaseService

IMPLEMENT_DYNCREATE(CToolsDatabaseService, CThread)

CToolsDatabaseService::CToolsDatabaseService() : CThread()
{
	m_nOption = TOOLSDATABASESERVICE_OPTION_DONOTHING;
	m_tStartTime = 0;
	m_tEndTime = 0;
}

BOOL CToolsDatabaseService::Start()
{
	UINT  nOption;
	CTimeKey  tStartTime;
	CTimeKey  tEndTime;
	CProfile  cProfile;

	return(((cProfile.GetToolsDatabaseOptionsInfo(nOption, tStartTime, tEndTime) && SetUpdateBehavior(nOption, tStartTime, tEndTime)) || SetUpdateBehavior(TOOLSDATABASESERVICE_OPTION_DONOTHING, 0, 0)) ? CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CToolsDatabaseService::Stop()
{
	UINT  nOption;
	CTimeKey  tStartTime;
	CTimeKey  tEndTime;
	CProfile  cProfile;

	return((GetUpdateBehavior(nOption, tStartTime, tEndTime) && cProfile.SetToolsDatabaseOptionsInfo(nOption, tStartTime, tEndTime)) ? (DestroyThread() >= 0) : FALSE);
}

BOOL CToolsDatabaseService::SetUpdateBehavior(UINT nOption, CONST CTimeKey &tStartTime, CONST CTimeKey &tEndTime)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nOption = nOption;
	m_tStartTime = tStartTime;
	m_tEndTime = tEndTime;
	return m_bUpdate.SetEvent();
}

BOOL CToolsDatabaseService::GetUpdateBehavior(UINT &nOption, CTimeKey &tStartTime, CTimeKey &tEndTime) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	nOption = m_nOption;
	tStartTime = m_tStartTime;
	tEndTime = m_tEndTime;
	return TRUE;
}

int CToolsDatabaseService::Run()
{
	UINT  nOption;
	DWORD  dwResult;
	DWORD  dwTimeout;
	HANDLE  hEvents[2];
	CFileEx  cFile;
	CString  szMessage;
	CTimeKey  tStartTime;
	CTimeKey  tEndTime;
	CTimeKey  tTime[3];
	CFileFindEx  cFileFind[2];
	OVERLAPPED  fOverlapped = { 0,0,0,0,0 };

	if (cFileFind[0].FindFile(GetDatabase()->GetFileName()) && !cFileFind[0].FindNextFile())
	{
		if ((hEvents[0] = FindFirstChangeNotification(cFileFind[0].GetRoot(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE)))
		{
			for (hEvents[1] = (HANDLE)m_bUpdate, FindNextChangeNotification(hEvents[0]), dwTimeout = INFINITE, dwResult = 0, tTime[0] = CTime::GetCurrentTime().GetTime(); cFileFind[1].FindFile(GetDatabase()->GetUpdateFileName()) && !cFileFind[1].FindNextFile(); )
			{
				tTime[0] = (cFileFind[1].GetLastWriteTime(tTime[0])) ? tTime[0].GetTime() : CTime::GetCurrentTime().GetTime();
				cFileFind[1].Close();
				break;
			}
			do
			{
				if (Lock())
				{
					nOption = m_nOption;
					tStartTime = m_tStartTime;
					tEndTime = m_tEndTime;
					Unlock();
				}
				if (dwResult > WAIT_OBJECT_0  &&  dwResult != WAIT_TIMEOUT)
				{
					for (; dwResult == WAIT_OBJECT_0 + sizeof(hEvents) / sizeof(HANDLE); )
					{
						dwTimeout = INFINITE;
						break;
					}
					if (cFileFind[1].FindFile(GetDatabase()->GetUpdateFileName()) && !cFileFind[1].FindNextFile())
					{
						if (cFileFind[1].GetLastWriteTime(tTime[1]) && ((tTime[0] == tTime[1] && dwResult == WAIT_OBJECT_0 + sizeof(hEvents) / sizeof(HANDLE)) || tTime[0] < tTime[1]))
						{
							if (cFile.Open(cFileFind[1].GetFilePath(), CFile::modeRead | CFile::shareDenyNone))
							{
								if (LockFileEx(cFile.m_hFile, 0, 0, MAXDWORD, MAXDWORD, (LPOVERLAPPED)&fOverlapped))
								{
									if (nOption == TOOLSDATABASESERVICE_OPTION_INFORMBYEVENT)
									{
										szMessage.Format(STRING(IDS_TOOLSOPTIONSDATABASE_UPDATE_MESSAGE_INFORMATIONAL), (LPCTSTR)GetDatabase()->GetName());
										ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage);
									}
									for (dwTimeout = (nOption != TOOLSDATABASESERVICE_OPTION_UPDATEIMMEDIATELY) ? dwTimeout : 0; nOption == TOOLSDATABASESERVICE_OPTION_UPDATEATTIME; )
									{
										if (((tTime[2] = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tStartTime.GetTime() % SECONDSPERDAY  &&  tTime[2].GetTime() % SECONDSPERDAY <= tEndTime.GetTime() % SECONDSPERDAY  &&  tStartTime <= tEndTime) || ((tTime[2].GetTime() % SECONDSPERDAY >= tStartTime.GetTime() % SECONDSPERDAY || tTime[2].GetTime() % SECONDSPERDAY <= tEndTime.GetTime() % SECONDSPERDAY) && tStartTime > tEndTime))
										{
											dwTimeout = 0;
											break;
										}
										dwTimeout = (tStartTime <= tEndTime  &&  tTime[2].GetTime() % SECONDSPERDAY > tEndTime.GetTime() % SECONDSPERDAY) ? (DWORD)(1000 * (SECONDSPERDAY - tTime[2].GetTime() % SECONDSPERDAY + tStartTime.GetTime() % SECONDSPERDAY)) : (DWORD)(1000 * (tStartTime.GetTime() % SECONDSPERDAY - tTime[2].GetTime() % SECONDSPERDAY));
										break;
									}
									UnlockFileEx(cFile.m_hFile, 0, MAXDWORD, MAXDWORD, &fOverlapped);
								}
								cFile.Close();
							}
							tTime[0] = tTime[1];
						}
					}
					for (; dwResult == WAIT_OBJECT_0 + 1; )
					{
						FindNextChangeNotification(hEvents[0]);
						break;
					}
				}
				if (dwResult == WAIT_TIMEOUT || !dwTimeout)
				{
					GetMainWnd()->SetTimer(TOOLSDATABASESERVICE_BEHAVIOR_TIMERID, TOOLSDATABASESERVICE_BEHAVIOR_TIMEOUT, NULL);
					dwTimeout = INFINITE;
				}
			} while ((dwResult = Wait(hEvents, sizeof(hEvents) / sizeof(HANDLE), FALSE, dwTimeout)) > WAIT_OBJECT_0 || dwResult == WAIT_TIMEOUT);
			FindCloseChangeNotification(hEvents[0]);
		}
		cFileFind[0].Close();
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CToolsDatabaseService, CThread)
	//{{AFX_MSG_MAP(CToolsDatabaseService)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsDatabaseService message handlers


/////////////////////////////////////////////////////////////////////////////
// CRASService

IMPLEMENT_DYNCREATE(CRASService, CThread)

CRASService::CRASService() : CThread()
{
	m_hConnection = (HRASCONN)NULL;
	m_nConnectionState = (RASCONNSTATE)0;
	m_tConnectionTimeKey = 0;
	m_bCalling = FALSE;
	m_bAborting = FALSE;
}

CRASService::~CRASService()
{
	StopCall();
}

BOOL CRASService::MakeCall(CONST RASENTRY *pConnectionEntry, CONST RASDIALEXTENSIONS *pConnectionExt, CONST RASDIALPARAMS *pConnectionInfo)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (StopCall(); CreateThread((LPVOID)NULL, THREAD_PRIORITY_NORMAL, TRUE); )
	{
		CopyMemory(&m_cConnectionExt, pConnectionExt, sizeof(RASDIALEXTENSIONS));
		CopyMemory(&m_cConnectionInfo, pConnectionInfo, sizeof(RASDIALPARAMS));
		CopyMemory(&m_cConnectionEntry, pConnectionEntry, sizeof(RASENTRY));
		InterlockedExchange(&m_bAborting, FALSE);
		InterlockedExchange(&m_bCalling, TRUE);
		ResumeThread();
		return TRUE;
	}
	return FALSE;
}

RASCONNSTATE CRASService::CheckCall() CONST
{
	RASCONNSTATUS  sStatus;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (sStatus.dwSize = sizeof(RASCONNSTATUS); RasGetConnectStatus(m_hConnection, &sStatus) == ERROR_SUCCESS; ) return sStatus.rasconnstate;
	return((RASCONNSTATE)0);
}

BOOL CRASService::StopCall()
{
	InterlockedExchange(&m_bAborting, TRUE);
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CRASService::SetState(RASCONNSTATE nState, DWORD dwError)
{
	RASCONNSTATUS  sStatus;

	if (Lock())
	{
		if (nState == RASCS_AuthNotify)
		{
			for (sStatus.dwSize = sizeof(RASCONNSTATUS); RasGetConnectStatus(m_hConnection, &sStatus) == ERROR_SUCCESS && sStatus.rasconnstate == nState && sStatus.dwError != 0; )
			{
				nState = (RASCONNSTATE)(RASCS_Disconnected + sStatus.dwError);
				break;
			}
		}
		for (nState = (dwError != 0) ? (RASCONNSTATE)(RASCS_Disconnected + dwError) : nState; nState == RASCS_Connected; )
		{
			m_bCalling = FALSE;
			break;
		}
		m_nConnectionState = nState;
		Unlock();
	}
	return FALSE;
}

RASCONNSTATE CRASService::GetState() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_nConnectionState;
}

BOOL CRASService::GetDetails(RAS_STATS *pDetails) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; CheckCall() == RASCS_Connected; )
	{
		for (pDetails->dwSize = sizeof(RAS_STATS); RasGetConnectionStatistics(m_hConnection, pDetails) == ERROR_SUCCESS; ) return TRUE;
		break;
	}
	return FALSE;
}
BOOL CRASService::GetDetails(CString &szServer, CString &szNumber, CTimeKey &tTime) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (CheckCall() == RASCS_Connected || IsCalling() || GetState() == (RASCONNSTATE)-1)
	{
		szServer = m_szConnectionServer;
		szNumber = m_szConnectionNumber;
		tTime = m_tConnectionTimeKey;
		return TRUE;
	}
	return FALSE;
}
CString CRASService::GetDetails() CONST
{
	CString  szDetails;
	CString  szLineSpeed;
	CString  szServerName;
	CString  szPhoneNumber;
	CString  szDurationTime[2];
	CString  szActivationTime;
	CTimeKey  tActivationTime;
	CTimeSpan  tDurationPeriod;
	RAS_STATS  sLineStatistics;
	CStringTools  cStringTools;

	if (CheckCall() == RASCS_Connected)
	{
		for (szServerName.Format(STRING(IDS_RAS_TOOLTIP_SERVERNAME), (LPCTSTR)m_szConnectionServer), szPhoneNumber.Format((m_cConnectionEntry.dwType == RASET_Vpn) ? STRING(IDS_RAS_TOOLTIP_VPNADDRESS) : STRING(IDS_RAS_TOOLTIP_PHONENUMBER), (LPCTSTR)m_szConnectionNumber); lstrlen(m_cConnectionInfo.szCallbackNumber) > 0; )
		{
			szPhoneNumber += STRING(IDS_RAS_TOOLTIP_CALLBACKHINT);
			break;
		}
		if (GetDetails(&sLineStatistics))
		{
			szLineSpeed.Format(STRING(IDS_RAS_TOOLTIP_SPEEDINFO), (LPCTSTR)cStringTools.ConvertUIntToStructuredString(sLineStatistics.dwBps));
			szLineSpeed += EOL;
		}
		tDurationPeriod = tActivationTime.GetTime() - m_tConnectionTimeKey.GetTime();
		szActivationTime = m_tConnectionTimeKey.FormatGmt(STRING(IDS_RAS_TOOLTIP_ACTIVATIONTIME));
		szDurationTime[0].Format((tDurationPeriod.GetTotalHours() != 1) ? STRING(IDS_RAS_TOOLTIP_DURATIONHOURSHINT) : STRING(IDS_RAS_TOOLTIP_DURATIONHOURHINT), tDurationPeriod.GetTotalHours());
		szDurationTime[1].Format((tDurationPeriod.GetTotalMinutes() % MINUTESPERHOUR != 1) ? STRING(IDS_RAS_TOOLTIP_DURATIONMINUTESHINT) : STRING(IDS_RAS_TOOLTIP_DURATIONMINUTEHINT), tDurationPeriod.GetTotalMinutes() % MINUTESPERHOUR);
		return(szServerName + EOL + szPhoneNumber + EOL + szLineSpeed + szActivationTime + szDurationTime[0] + szDurationTime[1]);
	}
	if (GetState() == RASCS_Connected)
	{
		szDetails.Format(STRING(IDS_RAS_STATE_DISCONNECTED), (LPCTSTR)m_szConnectionServer);
		return szDetails;
	}
	return EMPTYSTRING;
}

BOOL CRASService::IsCalling() CONST
{
	return m_bCalling;
}

BOOL CRASService::IsAborting() CONST
{
	return m_bAborting;
}

int CRASService::Run()
{
	INT  nPos;
	INT  nCode;
	CString  szMessage;
	CString  szPhoneBook;
	CTimeKey  tConnectionTime;
	CVersionInfo  cVersionInfo;

	if (Lock())
	{
		for (nPos = 0, m_szConnectionServer.Empty(), m_szConnectionNumber = m_cConnectionInfo.szPhoneNumber, m_tConnectionTimeKey = CTime::GetCurrentTime().GetTime(), szPhoneBook.Format(STRING(IDS_PHONEBOOKNAME_FORMAT), (LPCTSTR)cVersionInfo.QueryInternalName()); nPos < lstrlen(m_cConnectionInfo.szEntryName); nPos++)
		{
			if (_istspace(m_cConnectionInfo.szEntryName[nPos]) || m_cConnectionInfo.szEntryName[nPos] == TAB) break;
			m_szConnectionServer += m_cConnectionInfo.szEntryName[nPos];
		}
		if (RasSetEntryProperties(szPhoneBook, m_cConnectionInfo.szEntryName, &m_cConnectionEntry, (DWORD) sizeof(RASENTRY), (LPBYTE)NULL, (DWORD)NULL) != ERROR_SUCCESS)
		{
			InterlockedExchange(&m_bCalling, FALSE);
			m_nConnectionState = (RASCONNSTATE)-1;
			Unlock();
			return 0;
		}
		if (RasDial(&m_cConnectionExt, szPhoneBook, &m_cConnectionInfo, 0, DialupCallback, &m_hConnection) != ERROR_SUCCESS)
		{
			for (InterlockedExchange(&m_bCalling, FALSE); m_hConnection != (HRASCONN)NULL; )
			{
				RasHangUp(m_hConnection);
				break;
			}
			m_nConnectionState = (RASCONNSTATE)-1;
			m_hConnection = (HRASCONN)NULL;
			Unlock();
			return 0;
		}
		Unlock();
	}
	for (nCode = CThread::Run(); m_hConnection != (HRASCONN)NULL; )
	{
		for (GetTMService()->StopActiveTMProviderDevice(GetThreadHandle()), RasHangUp(m_hConnection), tConnectionTime = CTime::GetCurrentTime().GetTime(); (CheckCall() || GetState() == RASCS_Authenticated) && CTime::GetCurrentTime().GetTime() - tConnectionTime.GetTime() < SECONDSPERMINUTE / 6; )
		{
			Sleep(1000);
			continue;
		}
		break;
	}
	if (Lock())
	{
		m_hConnection = (HRASCONN)NULL;
		m_nConnectionState = (RASCONNSTATE)0;
		m_szConnectionServer.Empty();
		m_szConnectionNumber.Empty();
		m_tConnectionTimeKey = 0;
		Unlock();
	}
	InterlockedExchange(&m_bAborting, FALSE);
	InterlockedExchange(&m_bCalling, FALSE);
	return nCode;
}

void CALLBACK CRASService::DialupCallback(UINT nMsg, RASCONNSTATE nState, DWORD dwError)
{
	GetRASService()->SetState(nState, dwError);
}

BEGIN_MESSAGE_MAP(CRASService, CThread)
	//{{AFX_MSG_MAP(CRASService)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRASService message handlers


/////////////////////////////////////////////////////////////////////////////
// CCLCWToolWndPanel dialog

IMPLEMENT_DYNCREATE(CCLCWToolWndPanel, CLocaleDialog)

CCLCWToolWndPanel::CCLCWToolWndPanel(CWnd *pParentWnd) : CLocaleDialog(CCLCWToolWndPanel::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CCLCWToolWndPanel)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CCLCWToolWndPanel::Create(UINT nID, CWnd *pParentWnd, CBasePane *pBar)
{
	CFontTools  cFontTools(&m_cFont);

	m_dwCLCW = 0;
	m_pPanesBar = pBar;
	return CLocaleDialog::Create(nID, pParentWnd);
}

VOID CCLCWToolWndPanel::SetCLCW(DWORD dwCLCW)
{
	if (m_dwCLCW != dwCLCW)
	{
		for (m_dwCLCW = dwCLCW; IsWindow(GetSafeHwnd()); )
		{
			UpdateCodes();
			UpdateLamps();
			UpdateButtons();
			break;
		}
	}
}

DWORD CCLCWToolWndPanel::GetCLCW() CONST
{
	return m_dwCLCW;
}

VOID CCLCWToolWndPanel::UpdateCodes()
{
	CDC  *pDC;
	INT  nNumberID;
	INT  nNumberIDs;
	CFont  *pOldFont;
	CRect  rNumber[2];
	CString  szNumber;
	CStringTools  cStringTools;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cFont)))
		{
			for (nNumberID = 0, nNumberIDs = (INT)m_nNumberIDs.GetSize(); nNumberID < nNumberIDs; nNumberID++)
			{
				for (szNumber.Empty(); m_dwCLCW != 0; )
				{
					if (m_nNumberIDs.GetAt(nNumberID) == IDC_CLCWTOOLWINDOW_PANEL_VIRTUALCHANNEL)
					{
						szNumber = cStringTools.ConvertUIntToString(MAKECLCWVIRTUALCHANNEL(m_dwCLCW));
						break;
					}
					if (m_nNumberIDs.GetAt(nNumberID) == IDC_CLCWTOOLWINDOW_PANEL_FARMCOUNTER)
					{
						szNumber = cStringTools.ConvertUIntToPaddedString(MAKECLCWFARMCOUNTER(m_dwCLCW), 2, 2);
						break;
					}
					if (m_nNumberIDs.GetAt(nNumberID) == IDC_CLCWTOOLWINDOW_PANEL_REPORTVALUE)
					{
						szNumber = cStringTools.ConvertUIntToPaddedString(MAKECLCWREPORTVALUE(m_dwCLCW), 2, 16);
						break;
					}
					if (m_nNumberIDs.GetAt(nNumberID) == IDC_CLCWTOOLWINDOW_PANEL_RAWVALUE) szNumber = cStringTools.ConvertUIntToPaddedString(HIWORD(m_dwCLCW), 4, 16) + SPACE + cStringTools.ConvertUIntToPaddedString(LOWORD(m_dwCLCW), 4, 16);
					break;
				}
				for (GetDlgItem(m_nNumberIDs.GetAt(nNumberID))->GetWindowRect(rNumber[0]), GetDlgItem(m_nNumberIDs.GetAt(nNumberID))->GetClientRect(rNumber[1]), rNumber[0].DeflateRect((rNumber[0].Width() - rNumber[1].Width()) / 2, (rNumber[0].Height() - rNumber[1].Height()) / 2), ScreenToClient(rNumber[0]); !rNumber[0].IsRectEmpty(); )
				{
					pDC->DrawText(szNumber, (rNumber[1] = rNumber[0]), DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_CALCRECT);
					pDC->DrawText(szNumber, (rNumber[1] = CRect(rNumber[0].left + (rNumber[0].Width() - rNumber[1].Width()) / 2, rNumber[1].top, rNumber[0].left + (rNumber[0].Width() - rNumber[1].Width()) / 2 + rNumber[1].Width(), rNumber[1].bottom)), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					pDC->ExcludeClipRect(rNumber[1]);
					pDC->FillSolidRect(rNumber[0], GetSysColor(COLOR_WINDOW));
					ValidateRect(rNumber[1]);
					break;
				}
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

VOID CCLCWToolWndPanel::UpdateLamps()
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		DrawLamps(pDC);
		ReleaseDC(pDC);
	}
}

VOID CCLCWToolWndPanel::DrawLamps(CDC *pDC)
{
	INT  nLamp;
	INT  nLamps;

	for (nLamp = 0, nLamps = (INT)m_nLampIDs.GetSize(); nLamp < nLamps; nLamp++)
	{
		DrawLamp(pDC, m_nLampIDs.GetAt(nLamp));
		continue;
	}
}

VOID CCLCWToolWndPanel::DrawLamp(CDC *pDC, UINT nID)
{
	CRect  rLamp;

	for (GetDlgItem(nID)->GetWindowRect(rLamp), ScreenToClient(rLamp); nID == IDC_CLCWTOOLWINDOW_PANEL_NORFAVAILABLE; )
	{
		DrawLamp(pDC, rLamp, (m_dwCLCW != 0) ? (((m_dwCLCW & CLCWBITMASK_NORFAVAILABLE) == 0) ? IDP_TCDEVICELAMPGOOD : IDP_TCDEVICELAMPBAD) : IDP_TCDEVICELAMP);
		return;
	}
	if (nID == IDC_CLCWTOOLWINDOW_PANEL_NOBITLOCK)
	{
		DrawLamp(pDC, rLamp, (m_dwCLCW != 0) ? (((m_dwCLCW & CLCWBITMASK_NOBITLOCK) == 0) ? IDP_TCDEVICELAMPGOOD : IDP_TCDEVICELAMPBAD) : IDP_TCDEVICELAMP);
		return;
	}
	if (nID == IDC_CLCWTOOLWINDOW_PANEL_LOCKOUT)
	{
		DrawLamp(pDC, rLamp, (m_dwCLCW != 0) ? (((m_dwCLCW & CLCWBITMASK_LOCKOUT) == 0) ? IDP_TCDEVICELAMPGOOD : IDP_TCDEVICELAMPBAD) : IDP_TCDEVICELAMP);
		return;
	}
	if (nID == IDC_CLCWTOOLWINDOW_PANEL_WAIT)
	{
		DrawLamp(pDC, rLamp, (m_dwCLCW != 0) ? (((m_dwCLCW & CLCWBITMASK_WAIT) == 0) ? IDP_TCDEVICELAMPGOOD : IDP_TCDEVICELAMPBAD) : IDP_TCDEVICELAMP);
		return;
	}
	if (nID == IDC_CLCWTOOLWINDOW_PANEL_RETRANSMIT)
	{
		DrawLamp(pDC, rLamp, (m_dwCLCW != 0) ? (((m_dwCLCW & CLCWBITMASK_RETRANSMIT) == 0) ? IDP_TCDEVICELAMPGOOD : IDP_TCDEVICELAMPBAD) : IDP_TCDEVICELAMP);
		return;
	}
}
VOID CCLCWToolWndPanel::DrawLamp(CDC *pDC, LPCRECT pRect, UINT nLampID)
{
	CDC  cDC;
	CSize  size;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(pDC))
	{
		if (cBitmap.CreateCompatibleBitmap(pDC, (size.cx = m_cLamps[nLampID - FIRSTTCDEVICELAMPID].GetWidth()), (size.cy = m_cLamps[nLampID - FIRSTTCDEVICELAMPID].GetHeight())))
		{
			if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
			{
				DrawBackground(&cDC, CRect(0, 0, size.cx, size.cy));
				m_cLamps[nLampID - FIRSTTCDEVICELAMPID].Draw(cDC.GetSafeHdc(), 0, 0);
				pDC->BitBlt((pRect->left + pRect->right - size.cx) / 2, (pRect->top + pRect->bottom - size.cy) / 2, size.cx, size.cy, &cDC, 0, 0, SRCCOPY);
				pDC->ExcludeClipRect((pRect->left + pRect->right - size.cx) / 2, (pRect->top + pRect->bottom - size.cy) / 2, (pRect->left + pRect->right - size.cx) / 2 + size.cx, (pRect->top + pRect->bottom - size.cy) / 2 + size.cy);
				cDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cDC.DeleteDC();
	}
}

BOOL CCLCWToolWndPanel::LoadLamps()
{
	INT  nSymbol;
	INT  nSymbols;
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	for (nSymbol = 0, nSymbols = sizeof(m_cLamps) / sizeof(m_cLamps[0]); nSymbol < nSymbols; nSymbol++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), MAKEINTRESOURCE(FIRSTTCDEVICELAMPID + nSymbol), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_cLamps[nSymbol].Load(pIStream)))
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
	return(nSymbol == nSymbols);
}

VOID CCLCWToolWndPanel::UpdateButtons()
{
	GetDlgItem(IDC_CLCWTOOLWINDOW_PANEL_SEQUENCENUMBER)->SendNotifyMessage(WM_ENABLE, GetTCService()->CanCorrelateTCTransferFrameSequenceNumber(), 0);
}

VOID CCLCWToolWndPanel::DrawBackground(CDC *pDC, LPCRECT pRect)
{
	CMFCVisualManager::GetInstance()->OnFillBarBackground(pDC, (CBasePane *)CWnd::FromHandle(m_pPanesBar->GetSafeHwnd()), pRect, pRect);
}

void CCLCWToolWndPanel::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCLCWToolWndPanel)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCLCWToolWndPanel, CLocaleDialog)
	//{{AFX_MSG_MAP(CCLCWToolWndPanel)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CLCWTOOLWINDOW_PANEL_SEQUENCENUMBER, OnCorrelate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCLCWToolWndPanel message handlers

int CCLCWToolWndPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_nLampIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_NORFAVAILABLE);
	m_nLampIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_NOBITLOCK);
	m_nLampIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_LOCKOUT);
	m_nLampIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_WAIT);
	m_nLampIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_RETRANSMIT);
	m_nNumberIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_VIRTUALCHANNEL);
	m_nNumberIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_FARMCOUNTER);
	m_nNumberIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_REPORTVALUE);
	m_nNumberIDs.Add(IDC_CLCWTOOLWINDOW_PANEL_RAWVALUE);
	return((CLocaleDialog::OnCreate(lpCreateStruct) != -1 && LoadLamps()) ? 0 : -1);
}

HBRUSH CCLCWToolWndPanel::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	return((nCtlColor == CTLCOLOR_EDIT) ? GetSysColorBrush(COLOR_WINDOW) : (HBRUSH)GetStockObject(HOLLOW_BRUSH));
}

BOOL CCLCWToolWndPanel::OnEraseBkgnd(CDC *pDC)
{
	CRect  rToolWnd;

	DrawLamps(pDC);
	GetClientRect(rToolWnd);
	DrawBackground(pDC, rToolWnd);
	UpdateWindow();
	return TRUE;
}

void CCLCWToolWndPanel::OnDestroy()
{
	INT  nSymbol;
	INT  nSymbols;

	for (nSymbol = 0, nSymbols = sizeof(m_cLamps) / sizeof(m_cLamps[0]), m_nLampIDs.RemoveAll(), m_nNumberIDs.RemoveAll(), m_cFont.DeleteObject(); nSymbol < nSymbols; nSymbol++)
	{
		m_cLamps[nSymbol].Destroy();
		continue;
	}
	CWnd::OnDestroy();
}

BOOL CCLCWToolWndPanel::OnInitDialog()
{
	INT  nNumberID;
	INT  nNumberIDs;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	for (nNumberID = 0, nNumberIDs = (INT)m_nNumberIDs.GetSize(); nNumberID < nNumberIDs; nNumberID++)
	{
		GetDlgItem(m_nNumberIDs.GetAt(nNumberID))->EnableWindow();
		AccessControl(m_nNumberIDs.GetAt(nNumberID), FALSE);
	}
	return FALSE;
}

void CCLCWToolWndPanel::OnCorrelate()
{
	GetTCService()->CorrelateTCTransferFrameSequenceNumber();
}


/////////////////////////////////////////////////////////////////////////////
// CCLCWToolWnd

IMPLEMENT_DYNCREATE(CCLCWToolWnd, CWnd)

CCLCWToolWnd::CCLCWToolWnd() : CWnd()
{
	m_pwndPanel = (CCLCWToolWndPanel *)NULL;
	m_bRedraw = FALSE;
}

BOOL CCLCWToolWnd::Create(CWnd *pParentWnd, CBasePane *pBar)
{
	CRect  rPanel;
	CRect  rToolWnd;
	BOOL  bVisible;
	CProfile  cProfile;

	if (CWnd::CreateEx(WS_EX_TOOLWINDOW, AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW), STRING(IDS_CLCWTOOLWINDOW_PANEL_TITLE), WS_CHILD | WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), pParentWnd, 0))
	{
		if ((m_pwndPanel = new CCLCWToolWndPanel) != (CCLCWToolWndPanel *)NULL)
		{
			if (m_pwndPanel->Create(IDD_CLCWTOOLWINDOW_PANEL_DIALOG, this, pBar))
			{
				if (!cProfile.GetCLCWPanelLayoutInfo(rToolWnd, bVisible))
				{
					pParentWnd->GetClientRect(rToolWnd);
					m_pwndPanel->GetWindowRect(rPanel);
					rPanel.OffsetRect(-rPanel.TopLeft());
					AdjustWindowRectEx(rPanel, GetStyle(), FALSE, GetExStyle());
					rToolWnd.SetRect(rToolWnd.right - rPanel.Width(), rToolWnd.top, rToolWnd.right, rToolWnd.top + rPanel.Height());
					rToolWnd.OffsetRect(-GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU));
					bVisible = FALSE;
				}
				MoveWindow(rToolWnd);
				SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				ShowWindow((bVisible) ? SW_SHOW : SW_HIDE);
				return TRUE;
			}
			delete m_pwndPanel;
			m_pwndPanel = (CCLCWToolWndPanel *)NULL;
		}
	}
	return FALSE;
}

BOOL CCLCWToolWnd::Destroy()
{
	CRect  rToolWnd;
	CProfile  cProfile;

	if (IsWindow(GetSafeHwnd()))
	{
		GetWindowRect(rToolWnd);
		GetParent()->ScreenToClient(rToolWnd);
		cProfile.SetCLCWPanelLayoutInfo(rToolWnd, IsWindowVisible());
	}
	return DestroyWindow();
}

VOID CCLCWToolWnd::SetCLCW(DWORD dwCLCW)
{
	m_pwndPanel->SetCLCW(dwCLCW);
}

DWORD CCLCWToolWnd::GetCLCW() CONST
{
	return m_pwndPanel->GetCLCW();
}

VOID CCLCWToolWnd::RedrawLayout(BOOL bRedraw)
{
	if (bRedraw)
	{
		RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_FRAME | RDW_ALLCHILDREN | RDW_INVALIDATE);
		return;
	}
}

BOOL CCLCWToolWnd::IsRequiringRedraw() CONST
{
	CRect  rDisplayWnd[2];
	CDisplayWnd  *pDisplayWnd;
	CDisplayArea  *pDisplayArea;

	if ((pDisplayArea = GetDisplayArea()))
	{
		for (GetWindowRect(rDisplayWnd[0]); (pDisplayWnd = pDisplayArea->FindDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)) && pDisplayWnd->IsWindowVisible(); )
		{
			pDisplayWnd->GetWindowRect(rDisplayWnd[1]);
			return CRect().IntersectRect(rDisplayWnd[0], rDisplayWnd[1]);
		}
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CCLCWToolWnd, CWnd)
	//{{AFX_MSG_MAP(CCLCWToolWnd)
	ON_WM_SYSCOMMAND()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_EXITSIZEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCLCWToolWnd message handlers

void CCLCWToolWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		ShowWindow(SW_HIDE);
		return;
	}
	CWnd::OnSysCommand(nID, lParam);
}

void CCLCWToolWnd::OnMoving(UINT nSide, LPRECT lpRect)
{
	BOOL  bDrag;

	RedrawLayout((!SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &bDrag, 0) || bDrag) ? IsRequiringRedraw() : FALSE);
	CWnd::OnMoving(nSide, lpRect);
}

void CCLCWToolWnd::OnMove(int x, int y)
{
	BOOL  bDrag;

	RedrawLayout((!SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &bDrag, 0) || bDrag) ? IsRequiringRedraw() : FALSE);
	CWnd::OnMove(x, y);
}

void CCLCWToolWnd::OnEnterSizeMove()
{
	BOOL  bDrag;

	m_bRedraw = (!SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &bDrag, 0) || !bDrag) ? IsRequiringRedraw() : FALSE;
}

void CCLCWToolWnd::OnExitSizeMove()
{
	if (m_bRedraw)
	{
		RedrawLayout();
		m_bRedraw = FALSE;
	}
	CWnd::OnExitSizeMove();
}

void CCLCWToolWnd::OnDestroy()
{
	if (IsWindow(m_pwndPanel->GetSafeHwnd()))
	{
		m_pwndPanel->DestroyWindow();
		delete m_pwndPanel;
	}
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTMExtractionThread

IMPLEMENT_DYNCREATE(CTMExtractionThread, CThread)

CTMExtractionThread::CTMExtractionThread() : CThread()
{
	return;
}

BOOL CTMExtractionThread::Start()
{
	INT  nProfile;
	INT  nProfiles;
	UINT  nProfileID;
	LPWSTR  pszName;
	CTimeKey  tTimeRange[2];
	CArchivesExtractionProfiles  pProfiles;
	CArchivesExtractionProfileInfo  *pProfileInfo;
	CByteArray  nJobsInfo;
	CProfile  cProfile;

	for (nProfile = 0, nProfiles = (cProfile.GetTelemetryArchivesExtractionJobsInfo(nJobsInfo) && pProfiles.Unmap(nJobsInfo)) ? (INT)pProfiles.GetSize() : -1, m_pProfiles.RemoveAll(), m_nProfileIDs.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = pProfiles.GetAt(nProfile)))
		{
			if (pProfileInfo->GetExecutionMode() != ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT)
			{
				m_pProfiles.InsertAt(m_pProfiles.GetSize(), pProfileInfo, 1);
				m_nProfileIDs.InsertAt(m_nProfileIDs.GetSize(), -1);
				pProfiles.RemoveAt(nProfile);
				nProfiles--;
				nProfile--;
				continue;
			}
			if ((pszName = new WCHAR[pProfileInfo->GetName().GetLength() + 1]))
			{
#ifndef UNICODE
				MultiByteToWideChar(CP_ACP, 0, pProfileInfo->GetName(), -1, pszName, pProfileInfo->GetName().GetLength() + 1);
#else
				wcscpy_s(pszName, pProfileInfo->GetName().GetLength() + 1, pProfileInfo->GetName());
#endif
				if ((nProfileID = (pProfileInfo->GetTimeRange(tTimeRange[0], tTimeRange[1])) ? AddJScriptTaskSchedulerTelemetryDataExtraction(pszName, pProfileInfo->GetExecutionTime().GetTime(), tTimeRange[0].GetTime(), tTimeRange[1].GetTime()) : -1) != (UINT)-1)
				{
					pProfiles.RemoveAt(nProfile);
					delete pProfileInfo;
					nProfiles--;
					nProfile--;
				}
				delete[] pszName;
				continue;
			}
		}
		break;
	}
	return((CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL)) ? (nProfile == nProfiles) : FALSE);
}

BOOL CTMExtractionThread::Stop()
{
	INT  nProfile;
	INT  nProfiles;
	CUIntArray  nProfileIDs;
	CArchivesExtractionProfiles  pProfiles;
	CArchivesExtractionProfileInfo  *pProfileInfo;
	CByteArray  nJobsInfo;
	CProfile  cProfile;

	for (nProfile = 0, nProfiles = (DestroyThread() >= 0) ? (INT)m_nProfileIDs.GetSize() : -1, pProfiles.Copy(&m_pProfiles), nProfileIDs.Copy(m_nProfileIDs); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = m_pProfiles.GetAt(nProfile)) && pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT)
		{
			DeleteJScriptTaskSchedulerTelemetryDataExtraction(nProfileIDs.GetAt(nProfile));
			continue;
		}
	}
	return((pProfiles.GetSize() == nProfiles) ? (pProfiles.Map(nJobsInfo) && cProfile.SetTelemetryArchivesExtractionJobsInfo(nJobsInfo)) : FALSE);
}

BOOL CTMExtractionThread::Update(CArchivesExtractionProfileInfo *pProfileInfo)
{
	CArchivesExtractionProfileInfo  *pExtractionProfileInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pExtractionProfileInfo = new CArchivesExtractionProfileInfo))
	{
		for (pExtractionProfileInfo->Copy(pProfileInfo); TRUE; )
		{
			m_pProfiles.InsertAt(m_pProfiles.GetSize(), pExtractionProfileInfo, 1);
			m_nProfileIDs.Add(-1);
			break;
		}
		return m_bUpdate.SetEvent();
	}
	return FALSE;
}
BOOL CTMExtractionThread::Update(CONST CArchivesExtractionProfiles &pProfiles, CONST CUIntArray &nIDs, CONST CStringArray &szErrors)
{
	INT  nProfile;
	INT  nProfiles;
	INT  nProfileID;
	INT  nProfileIDs;
	CTimeKey  tTime;
	CArchivesExtractionProfileInfo  *pProfileInfo[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProfile = 0, nProfiles = (INT)pProfiles.GetSize(), m_szErrors.Append(szErrors); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo[0] = pProfiles.GetAt(nProfile)) && pProfileInfo[0]->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT)
		{
			if (pProfileInfo[0]->GetExecutionTime().GetTime() < tTime.GetTime())
			{
				DeleteJScriptTaskSchedulerTelemetryDataExtraction(nIDs.GetAt(nProfile));
				continue;
			}
			for (nProfileID = 0, nProfileIDs = (INT)m_nProfileIDs.GetSize(); nProfileID < nProfileIDs; nProfileID++)
			{
				if (m_nProfileIDs.GetAt(nProfileID) == nIDs.GetAt(nProfile)) break;
				continue;
			}
			if ((pProfileInfo[1] = m_pProfiles.GetAt(nProfileID)))
			{
				pProfileInfo[1]->Copy(pProfileInfo[0]);
				continue;
			}
			if ((pProfileInfo[1] = new CArchivesExtractionProfileInfo))
			{
				pProfileInfo[1]->Copy(pProfileInfo[0]);
				m_pProfiles.InsertAt(m_pProfiles.GetSize(), pProfileInfo[1], 1);
				m_nProfileIDs.InsertAt(m_nProfileIDs.GetSize(), nIDs.GetAt(nProfile));
				continue;
			}
		}
	}
	for (nProfile = 0, nProfiles = (INT)m_pProfiles.GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo[0] = m_pProfiles.GetAt(nProfile)) && pProfileInfo[0]->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT)
		{
			for (nProfileID = 0, nProfileIDs = (INT)nIDs.GetSize(); nProfileID < nProfileIDs; nProfileID++)
			{
				if (m_nProfileIDs.GetAt(nProfile) == nIDs.GetAt(nProfileID)) break;
				continue;
			}
			if (nProfileID == nProfileIDs)
			{
				m_pProfiles.RemoveAt(nProfile);
				m_nProfileIDs.RemoveAt(nProfile);
				delete pProfileInfo[0];
				nProfiles--;
				nProfile--;
			}
		}
	}
	return m_bUpdate.SetEvent();
}

BOOL CTMExtractionThread::EnumExtractions(CArchivesExtractionProfiles &pProfiles) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pProfiles.Copy(&m_pProfiles);
}

BOOL CTMExtractionThread::AbortExtractions(CONST CArchivesExtractionProfiles &pProfiles)
{
	INT  nProfile[2];
	INT  nProfiles[2];
	CArchivesExtractionProfileInfo  *pProfileInfo[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProfile[0] = 0, nProfiles[0] = (INT)pProfiles.GetSize(); nProfile[0] < nProfiles[0]; nProfile[0]++)
	{
		for (nProfile[1] = 0, nProfiles[1] = (INT)m_pProfiles.GetSize(); nProfile[1] < nProfiles[1]; nProfile[1]++)
		{
			if ((pProfileInfo[0] = pProfiles.GetAt(nProfile[0])) != (CArchivesExtractionProfileInfo *)NULL)
			{
				if ((pProfileInfo[1] = m_pProfiles.GetAt(nProfile[1])) != (CArchivesExtractionProfileInfo *)NULL)
				{
					if (pProfileInfo[0]->Compare(pProfileInfo[1]) && pProfileInfo[0]->GetExecutionStatus() == pProfileInfo[1]->GetExecutionStatus())
					{
						for (; pProfileInfo[1]->GetExecutionStatus() == ARCHIVESEXTRACTIONINFO_EXECUTIONSTATUS_RUNNING; )
						{
							m_bAbort.SetEvent();
							break;
						}
						for (; pProfileInfo[1]->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT; )
						{
							DeleteJScriptTaskSchedulerTelemetryDataExtraction(m_nProfileIDs.GetAt(nProfile[1]));
							break;
						}
						m_pProfiles.RemoveAt(nProfile[1]);
						m_nProfileIDs.RemoveAt(nProfile[1]);
						delete pProfileInfo[1];
						break;
					}
				}
			}
		}
	}
	return m_bUpdate.SetEvent();
}

int CTMExtractionThread::Run()
{
	INT  nJob;
	INT  nJobs;
	INT  nIndex;
	BOOL  bResult;
	DWORD  dwWait;
	CTimeKey  tTime;
	CTimeKey  tExecution;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CArchivesExtractionProfileInfo  *pProfileInfo;

	do
	{
		if (Lock())
		{
			for (nJob = 0, nJobs = (INT)m_pProfiles.GetSize(), ShowErrors(m_szErrors), tTime = CTime::GetCurrentTime().GetTime(), tExecution = 0, nIndex = -1; nJob < nJobs; nJob++)
			{
				if ((pProfileInfo = m_pProfiles.GetAt(nJob)) != (CArchivesExtractionProfileInfo *)NULL)
				{
					if (pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_IMMEDIATELY)
					{
						if (tTime < tExecution || !tExecution.GetTime())
						{
							tExecution = tTime;
							nIndex = nJob;
						}
						continue;
					}
					if (pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME || pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT)
					{
						if (pProfileInfo->GetExecutionTime() < tExecution || !tExecution.GetTime())
						{
							tExecution = pProfileInfo->GetExecutionTime();
							nIndex = nJob;
						}
						continue;
					}
					if (pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATDAILYTIME)
					{
						if (((pProfileInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tTime.GetTime() / SECONDSPERDAY  &&  SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + pProfileInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY < tExecution.GetTime()) || (pProfileInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY >= tTime.GetTime() / SECONDSPERDAY  &&  SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY + 1) + pProfileInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY < tExecution.GetTime())) || !tExecution.GetTime())
						{
							tExecution = (pProfileInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tTime.GetTime() / SECONDSPERDAY) ? (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY) + pProfileInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY) : (SECONDSPERDAY*(tTime.GetTime() / SECONDSPERDAY + 1) + pProfileInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY);
							nIndex = nJob;
						}
						continue;
					}
					if (pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL)
					{
						if (pProfileInfo->GetTimeRangeMode() == ARCHIVESEXTRACTIONINFO_RANGE_COMPLETEINTERVAL  &&  pProfileInfo->GetPeriodicalExecutionTime(tStartTime, tInterval, tStopTime))
						{
							if (tStartTime.GetTime() + (2 * pProfileInfo->GetExecutionCycle() + 1)*tInterval.GetTotalSeconds() < tExecution.GetTime() || !tExecution.GetTime())
							{
								tExecution = tStartTime.GetTime() + (2 * pProfileInfo->GetExecutionCycle() + 1)*tInterval.GetTotalSeconds();
								nIndex = nJob;
							}
							continue;
						}
						if (pProfileInfo->GetTimeRangeMode() == ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL  &&  pProfileInfo->GetPeriodicalExecutionTime(tStartTime, tInterval, tStopTime))
						{
							if (tStartTime.GetTime() + (pProfileInfo->GetExecutionCycle() + 1)*tInterval.GetTotalSeconds() < tExecution.GetTime() || !tExecution.GetTime())
							{
								tExecution = tStartTime.GetTime() + (pProfileInfo->GetExecutionCycle() + 1)*tInterval.GetTotalSeconds();
								nIndex = nJob;
							}
							continue;
						}
					}
				}
				for (; pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT; )
				{
					DeleteJScriptTaskSchedulerTelemetryDataExtraction(m_nProfileIDs.GetAt(nJob));
					break;
				}
				m_pProfiles.RemoveAt(nJob);
				m_nProfileIDs.RemoveAt(nJob);
				delete pProfileInfo;
				nJobs--;
				nJob--;
			}
			if (tTime >= tExecution  &&  tExecution > 0 && nIndex >= 0)
			{
				if ((pProfileInfo = m_pProfiles.GetAt(nIndex)) != (CArchivesExtractionProfileInfo *)NULL)
				{
					pProfileInfo->SetExecutionStatus(ARCHIVESEXTRACTIONINFO_EXECUTIONSTATUS_RUNNING);
					m_cProfileInfo.Copy(pProfileInfo);
				}
			}
			m_szErrors.RemoveAll();
			Unlock();
		}
		if (lstrlen(m_cProfileInfo.GetName()) > 0)
		{
			for (bResult = FALSE; m_cProfileInfo.GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_IMMEDIATELY || m_cProfileInfo.GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME || m_cProfileInfo.GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATDAILYTIME || m_cProfileInfo.GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL || m_cProfileInfo.GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT; )
			{
				if ((bResult = Extract(&m_cProfileInfo)))
				{
					Automate(&m_cProfileInfo);
					Transfer(&m_cProfileInfo);
				}
				Alert(&m_cProfileInfo, bResult);
				break;
			}
			if (Wait(0) == WAIT_OBJECT_0)
			{
				dwWait = 0;
				continue;
			}
			if (Lock())
			{
				for (nJob = 0, nJobs = (INT)m_pProfiles.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pProfileInfo = m_pProfiles.GetAt(nJob)) && pProfileInfo->GetExecutionStatus() == ARCHIVESEXTRACTIONINFO_EXECUTIONSTATUS_RUNNING)
					{
						if (pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_IMMEDIATELY || pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME || (pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL  &&  pProfileInfo->GetPeriodicalExecutionTime(tStartTime, tInterval, tStopTime) && ((pProfileInfo->GetTimeRangeMode() == ARCHIVESEXTRACTIONINFO_RANGE_COMPLETEINTERVAL  &&  tStartTime.GetTime() + 2 * (pProfileInfo->GetExecutionCycle() + 1)*tInterval.GetTotalSeconds() > tStopTime.GetTime()) || (pProfileInfo->GetTimeRangeMode() == ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL  &&  tStartTime.GetTime() + ((pProfileInfo->GetExecutionCycle() + 1) + 1)*tInterval.GetTotalSeconds() - pProfileInfo->GetPeriodicalInterval().GetTotalSeconds() > tStopTime.GetTime()))) || pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT || !bResult)
						{
							for (; pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT; )
							{
								DeleteJScriptTaskSchedulerTelemetryDataExtraction(m_nProfileIDs.GetAt(nJob));
								break;
							}
							m_pProfiles.RemoveAt(nJob);
							m_nProfileIDs.RemoveAt(nJob);
							delete pProfileInfo;
							break;
						}
						pProfileInfo->SetExecutionStatus(ARCHIVESEXTRACTIONINFO_EXECUTIONSTATUS_QUEUED);
						pProfileInfo->SetExecutionCycle(pProfileInfo->GetExecutionCycle() + 1);
						pProfileInfo->SetLastExecutionTime(tExecution);
						break;
					}
				}
				m_cProfileInfo.SetName(EMPTYSTRING);
				Unlock();
				dwWait = 0;
				continue;
			}
			m_cProfileInfo.SetName(EMPTYSTRING);
		}
		dwWait = (nIndex >= 0) ? ((tTime < tExecution.GetTime()) ? (DWORD)(1000 * min(tExecution.GetTime() - tTime.GetTime(), SECONDSPERDAY)) : 0) : INFINITE;
		continue;
	} while (Wait(m_bUpdate, FALSE, dwWait) != WAIT_OBJECT_0);
	return 0;
}

BOOL CTMExtractionThread::Extract(CArchivesExtractionProfileInfo *pProfile)
{
	UINT  nMode;
	UINT  nResult;
	BOOL  bAbort;
	CFileEx  cFile;
	CString  szName;
	CString  szError;
	CString  szSource;
	CString  szMessage;
	CString  szFileName;
	CString  szFileFormat;
	CString  szDirectory[2];
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeKey  tExtraction;
	CTimeSpan  tInterval[3];
	CTimeSpan  tDailyStopTime;
	CTimeSpan  tDailyStartTime;
	CModuleToken  cModuleToken;

	for (szName = pProfile->GetName(), szSource = pProfile->GetSource(), szDirectory[0] = pProfile->GetDirectory(), nMode = pProfile->GetTimeRangeMode(), tInterval[2] = pProfile->GetRangeInterval(), szDirectory[1] = cModuleToken.GetModuleFileRoot(), m_nParameterIDs.RemoveAll(), m_nParameterFormats.RemoveAll(), m_szParameterRows.RemoveAll(), m_tParameterTimes.RemoveAll(), m_szDelimiters[0].Empty(), m_szDelimiters[1].Empty(), m_szDelimiters[2].Empty(), m_bAbort.ResetEvent(); nMode == ARCHIVESEXTRACTIONINFO_RANGE_NORMAL; )
	{
		pProfile->GetTimeRange(tStartTime, tStopTime);
		break;
	}
	if (nMode == ARCHIVESEXTRACTIONINFO_RANGE_DAILY)
	{
		pProfile->GetDailyTimeRange(tDailyStartTime, tDailyStopTime);
		tStartTime = (tExtraction.GetTime() / SECONDSPERDAY)*SECONDSPERDAY + tDailyStartTime.GetTotalSeconds();
		tStopTime = (tExtraction.GetTime() / SECONDSPERDAY)*SECONDSPERDAY + tDailyStopTime.GetTotalSeconds();
		tStopTime = (tStartTime > tStopTime) ? (tStopTime.GetTime() + SECONDSPERDAY) : tStopTime.GetTime();
		if (tStopTime > tExtraction)
		{
			tStartTime -= SECONDSPERDAY;
			tStopTime -= SECONDSPERDAY;
		}
	}
	if (nMode == ARCHIVESEXTRACTIONINFO_RANGE_COMPLETEINTERVAL)
	{
		pProfile->GetPeriodicalExecutionTime(tStartTime, tInterval[0], tStopTime);
		tStartTime = tStartTime.GetTime() + 2 * pProfile->GetExecutionCycle()*tInterval[0].GetTotalSeconds();
		tStopTime = min(tStartTime.GetTime() + tInterval[0].GetTotalSeconds(), tStopTime.GetTime());
	}
	if (nMode == ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL)
	{
		pProfile->GetPeriodicalExecutionTime(tStartTime, tInterval[1], tStopTime);
		tStartTime = tStartTime.GetTime() + (pProfile->GetExecutionCycle() + 1)*tInterval[1].GetTotalSeconds() - pProfile->GetPeriodicalInterval().GetTotalSeconds();
		tStopTime = min(tStartTime.GetTime() + pProfile->GetPeriodicalInterval().GetTotalSeconds(), tStopTime.GetTime());
	}
	if (nMode == ARCHIVESEXTRACTIONINFO_RANGE_NORMAL || nMode == ARCHIVESEXTRACTIONINFO_RANGE_DAILY || nMode == ARCHIVESEXTRACTIONINFO_RANGE_COMPLETEINTERVAL || nMode == ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL)
	{
		szFileFormat.Format((pProfile->GetColumnDelimiter() == STRING(IDS_PROFILE_EXTRACTIONS_DELIMITER_COL_COMMA)) ? STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FILENAMEFORMAT) : STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FILENAMEDEFAULTFORMAT), (!szDirectory[0].IsEmpty()) ? (LPCTSTR)szDirectory[0] : (LPCTSTR)szDirectory[1], (LPCTSTR)szName, (LPCTSTR)tStartTime.FormatGmt(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FILETIMEFORMAT)));
		szFileName = szFileFormat;
	}
	if (TestDirectory(szFileName))
	{
		if (m_cTMEnvironment.Create(GetDatabase()))
		{
			if (m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), szSource, &m_cTMEnvironment))
			{
				if (cFile.Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
				{
					if ((nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = tStartTime))) & HISTORYFILE_SUCCESS)
					{
						if ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (tTimeKey.GetTime() > tStopTime.GetTime())
							{
								m_cTMProcessEngine.Close();
								m_cTMEnvironment.Destroy();
								cFile.Close();
								return TRUE;
							}
							if (Extract(pProfile, &m_cTMEnvironment, cFile, tTimeKey >= tStartTime || tInterval[2].GetTotalSeconds() > 0))
							{
								for (szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTION_MESSAGE), (LPCTSTR)szName), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE), bAbort = FALSE; tTimeKey.GetTime() <= tStopTime.GetTime() && m_nParameterIDs.GetSize() > 0 && !bAbort; bAbort = (Wait(m_bAbort, FALSE, 0) != WAIT_TIMEOUT) ? TRUE : bAbort)
								{
									if ((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, tInterval[2].GetTotalSeconds())) & HISTORYFILE_SUCCESS)
									{
										if ((nResult & HISTORYFILE_TMUNIT) && tTimeKey <= tStopTime)
										{
											if (tTimeKey.GetTime() >= tStartTime.GetTime())
											{
												if (!Extract(pProfile, &m_cTMEnvironment, cFile))
												{
													nResult = 0;
													break;
												}
											}
											continue;
										}
										if ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeKey <= tStopTime)
										{
											if (tTimeKey >= tStartTime  &&  tInterval[2].GetTotalSeconds() > 0)
											{
												if (!Extract(pProfile, &m_cTMEnvironment, cFile))
												{
													nResult = 0;
													break;
												}
											}
											continue;
										}
									}
									break;
								}
								if (bAbort)
								{
									szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTION_ABORT), (LPCTSTR)szName);
									ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
									m_cTMProcessEngine.Close();
									m_cTMEnvironment.Destroy();
									cFile.Close();
									cFile.Remove(szFileName);
									return FALSE;
								}
							}
							else  nResult = 0;
						}
						if ((nResult & HISTORYFILE_SUCCESS) || (nResult & HISTORYFILE_DATA_NONE))
						{
							if ((nResult = (Extract(cFile)) ? (nResult | HISTORYFILE_SUCCESS) : 0) != 0)
							{
								szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTION_SUCCESS), (LPCTSTR)szName);
								ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
								pProfile->SetFileName(szFileName);
								m_cTMProcessEngine.Close();
								m_cTMEnvironment.Destroy();
								cFile.Close();
								return TRUE;
							}
						}
					}
					cFile.Close();
					cFile.Remove(szFileName);
					szError.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FILEUPDATE_FAILURE), (LPCTSTR)szFileName);
					szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FAILUREFORMAT), (LPCTSTR)szName, (!nResult) ? (LPCTSTR)szError : STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_RETRIEVE_FAILURE));
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
					m_cTMProcessEngine.Close();
					m_cTMEnvironment.Destroy();
					return FALSE;
				}
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FILEOPEN_FAILURE), (LPCTSTR)szFileName);
				szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FAILUREFORMAT), (LPCTSTR)szName, (LPCTSTR)szError);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
				m_cTMProcessEngine.Close();
				m_cTMEnvironment.Destroy();
				return FALSE;
			}
			m_cTMEnvironment.Destroy();
		}
		szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FAILUREFORMAT), (LPCTSTR)szName, STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_RETRIEVE_FAILURE));
	}
	else  szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FAILUREFORMAT), (LPCTSTR)szName, STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_INTERNAL_FAILURE));
	ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
	return FALSE;
}
BOOL CTMExtractionThread::Extract(CArchivesExtractionProfileInfo *pProfile, CTMEnvironment *pTMEnvironment, CFile &cFile, BOOL bExtract)
{
	INT  nIndex;
	INT  nSample;
	INT  nSamples;
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus;
	BOOL  bFailure;
	BOOL  bTitleOption;
	DWORD  cbFileBytes;
	TCHAR  szTime[64];
	LPVOID  pTitleRow;
	LPVOID  pParameterRow;
	CString  szTitleRow;
	CString  szTitleCol;
	CString  szValueText;
	CString  szValueCode;
	CString  szTimeFormat;
	CString  szParameterRow;
	CString  szCalibrationTable;
	TIMETAG  tParameterTime[2];
	CTimeTag  tSampleTimeTag;
	CTimeSpan  tRangeInterval;
	ULONGLONG  nAttributes;
	ULONGLONG  nValue;
	CUIntArray  nFormats;
	CUIntArray  nTriggers;
	CStringArray  szParameters;
	CStringTools  cStringTools;
	CTMParameter  *pTMParameter;

	if (!m_nParameterIDs.GetSize())
	{
		for (nParameter = 0, nParameters = pProfile->GetParameters(szParameters, nFormats, nTriggers), m_nTimeFormat = pProfile->GetTimeFormat(), m_szDelimiters[0] = pProfile->GetColumnDelimiter(), m_szDelimiters[1] = pProfile->GetRowDelimiter(), m_szDelimiters[2] = pProfile->GetTextDelimiter(), m_nCharset = pProfile->GetCharset(), bTitleOption = pProfile->GetTitleOption(), szTitleRow = (bTitleOption) ? ((m_nTimeFormat != ARCHIVESEXTRACTIONINFO_TIMEFORMAT_NONE) ? (LPCTSTR)(m_szDelimiters[2] + STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_TITLETIMELABEL) + m_szDelimiters[2]) : EMPTYSTRING) : EMPTYSTRING; nParameter < nParameters; nParameter++)
		{
			m_nParameterIDs.SetAtGrow(nParameter, GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)));
			m_nParameterFormats.SetAtGrow(nParameter, nFormats.GetAt(nParameter));
			m_nParameterTriggers.SetAtGrow(nParameter, nTriggers.GetAt(nParameter));
			szTitleCol.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_TITLESTATUSLABEL), (LPCTSTR)szParameters.GetAt(nParameter));
			szTitleCol = (nFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_STATUS) ? szTitleCol : szParameters.GetAt(nParameter);
			szTitleRow += (bTitleOption) ? ((m_nTimeFormat != ARCHIVESEXTRACTIONINFO_TIMEFORMAT_NONE || nParameter > 0) ? (LPCTSTR)m_szDelimiters[0] : EMPTYSTRING) : EMPTYSTRING;
			szTitleRow += (bTitleOption) ? (LPCTSTR)m_szDelimiters[2] : EMPTYSTRING;
			szTitleRow += (bTitleOption) ? (LPCTSTR)szTitleCol : EMPTYSTRING;
			szTitleRow += (bTitleOption) ? (LPCTSTR)m_szDelimiters[2] : EMPTYSTRING;
		}
		if (bTitleOption)
		{
			szTitleRow += m_szDelimiters[1];
			if ((pTitleRow = (LPVOID)GlobalAlloc(GPTR, (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) ? ((szTitleRow.GetLength() + 1)*sizeof(WCHAR)) : ((szTitleRow.GetLength() + 1)*sizeof(CHAR)))))
			{
#ifndef UNICODE
				if (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) MultiByteToWideChar(CP_ACP, 0, szTitleRow, -1, (LPWSTR)pTitleRow, szTitleRow.GetLength() + 1);
				else  CopyMemory(pTitleRow, (LPCSTR)szTitleRow, (szTitleRow.GetLength() + 1)*sizeof(CHAR));
#else
				if (m_nCharset != ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) WideCharToMultiByte(CP_ACP, 0, szTitleRow, -1, (LPSTR)pTitleRow, szTitleRow.GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				else  CopyMemory(pTitleRow, (LPCWSTR)szTitleRow, (szTitleRow.GetLength() + 1)*sizeof(WCHAR));
#endif
				if (!WriteFile(cFile.m_hFile, pTitleRow, (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) ? (szTitleRow.GetLength()*sizeof(WCHAR)) : (szTitleRow.GetLength()*sizeof(CHAR)), &cbFileBytes, (LPOVERLAPPED)NULL))
				{
					GlobalFree(pTitleRow);
					return FALSE;
				}
				GlobalFree(pTitleRow);
			}
			else return FALSE;
		}
	}
	if (bExtract)
	{
		for (nParameter = 0, nParameters = (INT)m_nParameterIDs.GetSize(), tRangeInterval = pProfile->GetRangeInterval(), szParameterRow = EMPTYSTRING, nSamples = 0; nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter = (CTMParameter *)pTMEnvironment->GetTMParameters()->GetAt(m_nParameterIDs.GetAt(nParameter))) != (CTMParameter *)NULL)
			{
				if (((m_nParameterTriggers.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_TRIGGER_UPDATES) && ((pTMEnvironment->GetTMUnit()->GetTag() == pTMParameter->GetLastUpdateTMUnit() && pTMEnvironment->GetTMUnit()->GetTimeTag() == pTMParameter->GetLastUpdateTime()) || tRangeInterval.GetTotalSeconds() > 0)) || ((m_nParameterTriggers.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_TRIGGER_CHANGES) && pTMEnvironment->GetTMUnit()->GetTag() == pTMParameter->GetLastChangeTMUnit() && pTMEnvironment->GetTMUnit()->GetTimeTag() == pTMParameter->GetLastChangeTime()) || !m_szParameterRows.GetSize())
				{
					nSamples = max(pTMParameter->GetValueCount(), nSamples);
					continue;
				}
			}
		}
		for (nSample = 0; nSample < nSamples; nSample++)
		{
			for (nParameter = ((tSampleTimeTag = pTMEnvironment->GetTMUnit()->GetTimeTag()) > 0 && !tRangeInterval.GetTotalSeconds()) ? nParameters : 0; nParameter < nParameters; nParameter++)
			{
				if ((pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(m_nParameterIDs.GetAt(nParameter))) != (CTMParameter *)NULL)
				{
					tSampleTimeTag = (pTMParameter->GetLastUpdateTime() > tSampleTimeTag) ? pTMParameter->GetLastUpdateTime() : tSampleTimeTag;
					continue;
				}
			}
			if (m_nTimeFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SECONDS)
			{
				_i64tot_s(tSampleTimeTag.GetTimeInSeconds(), szTime, sizeof(szTime) / sizeof(TCHAR), 10);
				szParameterRow = szTime;
			}
			if (m_nTimeFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_MILLISECONDS)
			{
				_i64tot_s(tSampleTimeTag.GetTime() / 1000, szTime, sizeof(szTime) / sizeof(TCHAR), 10);
				szParameterRow = szTime;
			}
			if (m_nTimeFormat != ARCHIVESEXTRACTIONINFO_TIMEFORMAT_NONE  &&  m_nTimeFormat != ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SECONDS  &&  m_nTimeFormat != ARCHIVESEXTRACTIONINFO_TIMEFORMAT_MILLISECONDS)
			{
				szTimeFormat = STRING(MINPROFILEEXTRACTIONSTIMEFORMAT + m_nTimeFormat);
				szParameterRow = tSampleTimeTag.FormatGmt(szTimeFormat);
			}
			for (nParameter = 0; nParameter < nParameters; nParameter++)
			{
				if ((pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(m_nParameterIDs.GetAt(nParameter))))
				{
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_DEFAULT) ? pTMParameter->GetAttributes() : 0;
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_CODED) ? ((pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE) : nAttributes;
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_DECIMAL) ? ((pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_DECIMAL)) : nAttributes;
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_BINARY) ? ((pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_BINARY)) : nAttributes;
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_OCTAL) ? ((pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_OCTAL)) : nAttributes;
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_HEXADECIMAL) ? ((pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL)) | (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_HEXADECIMAL)) : nAttributes;
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_INVERSE) ? ((nAttributes & ~TMPARAMETER_CODING_BITPATTERN) | TMPARAMETER_CODING_INVERSEBITPATTERN) : nAttributes;
					nAttributes = (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_STATUS) ? pTMParameter->GetAttributes() : nAttributes;
					szParameterRow += (m_nTimeFormat != ARCHIVESEXTRACTIONINFO_TIMEFORMAT_NONE || nParameter > 0) ? (LPCTSTR)m_szDelimiters[0] : EMPTYSTRING;
					if (pTMParameter->GetRawValue(nSample, nValue, nStatus, szCalibrationTable) && pTMParameter->GetValueAsText(GetDatabase(), nSample, nAttributes, szValueText))
					{
						if (m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_STATUS)
						{
							szValueCode = cStringTools.ConvertUIntToString(nStatus);
							szValueText = szValueCode;
						}
						szParameterRow += ((m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_STATUS) == 0 && (nAttributes & TMPARAMETER_CALIBRATION_STATUS) && !szCalibrationTable.IsEmpty()) ? (m_szDelimiters[2] + szValueText) : szValueText;
						szParameterRow += ((m_nParameterFormats.GetAt(nParameter) & ARCHIVESEXTRACTIONINFO_FORMAT_STATUS) == 0 && (nAttributes & TMPARAMETER_CALIBRATION_STATUS) && !szCalibrationTable.IsEmpty()) ? (LPCTSTR)m_szDelimiters[2] : EMPTYSTRING;
					}
				}
			}
			for (nIndex = (INT)(m_szParameterRows.GetSize() - 1); nIndex >= 0; nIndex--)
			{
				if ((tParameterTime[0] = m_tParameterTimes.GetAt(nIndex).GetTime()) <= tSampleTimeTag.GetTime()) break;
				continue;
			}
			m_szParameterRows.InsertAt(nIndex + 1, szParameterRow);
			m_tParameterTimes.InsertAt(nIndex + 1, tSampleTimeTag);
		}
		if (m_szParameterRows.GetSize() > 1)
		{
			for (tParameterTime[0] = m_tParameterTimes.GetAt(0).GetTime(), tParameterTime[1] = m_tParameterTimes.GetAt((INT)m_tParameterTimes.GetUpperBound()).GetTime(), bFailure = FALSE; m_cTMProcessEngine.GetTimeCorrelationDelay() < (UINT)((tParameterTime[1] - tParameterTime[0]) / 1000000); tParameterTime[0] = m_tParameterTimes.GetAt(0).GetTime(), tParameterTime[1] = m_tParameterTimes.GetAt((INT)m_tParameterTimes.GetUpperBound()).GetTime())
			{
				if ((pParameterRow = (LPVOID)GlobalAlloc(GPTR, (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) ? (((szParameterRow = m_szParameterRows.GetAt(0) + m_szDelimiters[1]).GetLength() + 1)*sizeof(WCHAR)) : (((szParameterRow = m_szParameterRows.GetAt(0) + m_szDelimiters[1]).GetLength() + 1)*sizeof(CHAR)))))
				{
#ifndef UNICODE
					if (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) MultiByteToWideChar(CP_ACP, 0, szParameterRow, -1, (LPWSTR)pParameterRow, szParameterRow.GetLength() + 1);
					else  CopyMemory(pParameterRow, (LPCSTR)szParameterRow, (szParameterRow.GetLength() + 1)*sizeof(CHAR));
#else
					if (m_nCharset != ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) WideCharToMultiByte(CP_ACP, 0, szParameterRow, -1, (LPSTR)pParameterRow, szParameterRow.GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
					else  CopyMemory(pParameterRow, (LPCWSTR)szParameterRow, (szParameterRow.GetLength() + 1)*sizeof(WCHAR));
#endif
					if (!WriteFile(cFile.m_hFile, pParameterRow, (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) ? (szParameterRow.GetLength()*sizeof(WCHAR)) : (szParameterRow.GetLength()*sizeof(CHAR)), &cbFileBytes, (LPOVERLAPPED)NULL))
					{
						m_szParameterRows.RemoveAll();
						m_tParameterTimes.RemoveAll();
						GlobalFree(pParameterRow);
						bFailure = TRUE;
						break;
					}
					m_szParameterRows.RemoveAt(0);
					m_tParameterTimes.RemoveAt(0);
					if (m_szParameterRows.GetSize() > 1)
					{
						GlobalFree(pParameterRow);
						continue;
					}
					GlobalFree(pParameterRow);
					break;
				}
				m_szParameterRows.RemoveAll();
				m_tParameterTimes.RemoveAll();
				bFailure = TRUE;
				break;
			}
			return !bFailure;
		}
	}
	return TRUE;
}
BOOL CTMExtractionThread::Extract(CFile &cFile)
{
	DWORD  cbFileBytes;
	LPVOID  pParameterRow;
	CString  szParameterRow;

	while (m_szParameterRows.GetSize() > 0)
	{
		if ((pParameterRow = (LPVOID)GlobalAlloc(GPTR, (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) ? (((szParameterRow = m_szParameterRows.GetAt(0) + m_szDelimiters[1]).GetLength() + 1)*sizeof(WCHAR)) : (((szParameterRow = m_szParameterRows.GetAt(0) + m_szDelimiters[1]).GetLength() + 1)*sizeof(CHAR)))))
		{
#ifndef UNICODE
			if (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) MultiByteToWideChar(CP_ACP, 0, szParameterRow, -1, (LPWSTR)pParameterRow, szParameterRow.GetLength() + 1);
			else  CopyMemory(pParameterRow, (LPCSTR)szParameterRow, (szParameterRow.GetLength() + 1)*sizeof(CHAR));
#else
			if (m_nCharset != ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) WideCharToMultiByte(CP_ACP, 0, szParameterRow, -1, (LPSTR)pParameterRow, szParameterRow.GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			else  CopyMemory(pParameterRow, (LPCWSTR)szParameterRow, (szParameterRow.GetLength() + 1)*sizeof(WCHAR));
#endif
			if (!WriteFile(cFile.m_hFile, pParameterRow, (m_nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE) ? (szParameterRow.GetLength()*sizeof(WCHAR)) : (szParameterRow.GetLength()*sizeof(CHAR)), &cbFileBytes, (LPOVERLAPPED)NULL))
			{
				m_szParameterRows.RemoveAll();
				m_tParameterTimes.RemoveAll();
				GlobalFree(pParameterRow);
				break;
			}
			m_szParameterRows.RemoveAt(0);
			m_tParameterTimes.RemoveAt(0);
			GlobalFree(pParameterRow);
			continue;
		}
		m_szParameterRows.RemoveAll();
		m_tParameterTimes.RemoveAll();
		break;
	}
	return((!m_szParameterRows.GetSize()) ? TRUE : FALSE);
}

VOID CTMExtractionThread::Automate(CArchivesExtractionProfileInfo *pProfile)
{
	CString  szError;
	CString  szScript;
	CString  szMessage;
	CAutomationScript  *pScript;
	CAutomationScripts  pScripts;
	CJScriptCodeExecutor  cJScriptCodeExecutor;

	for (pProfile->SetAutomationScriptOutput(EMPTYSTRING); (pProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_DISABLED) != ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_DISABLED; )
	{
		if ((pScript = (GetDatabase()->EnumScripts(pScripts) > 0) ? pScripts.GetAt(pScripts.Find((szScript = pProfile->GetAutomationScriptName()))) : (CAutomationScript *)NULL))
		{
			for (pScript->SetInputFileName(pProfile->GetFileName()); cJScriptCodeExecutor.Run(pProfile->GetName(), pScript, szError); )
			{
				pProfile->SetAutomationScriptOutput(pScript->GetOutputFileName());
				return;
			}
			if (!szError.IsEmpty())
			{
				szMessage.Format(STRING(IDS_SCRIPTLANGUAGE_CODE_ERROR), (LPCTSTR)szScript, (LPCTSTR)szError);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			}
			else
			{
				szMessage.Format(STRING(IDS_SCRIPTLANGUAGE_CODE_INTERNALERROR), (LPCTSTR)szScript);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			}
		}
		break;
	}
}

VOID CTMExtractionThread::Transfer(CONST CArchivesExtractionProfileInfo *pProfile)
{
	INT  nUser;
	INT  nUsers;
	INT  nIndex;
	BOOL  bFile;
	UINT  nPort;
	UINT  nAudition;
	UINT  nRetries[2];
	TCHAR  szData[8192];
	DWORD  dwService;
	DWORD  cbFile;
	CFileEx  cFile[2];
	CString  szName;
	CString  szServer;
	CString  szMessage;
	CString  szError[4];
	CString  szLocation;
	CString  szUserName;
	CString  szPassword;
	CString  szFileName;
	CString  szFTPName[2];
	CString  szDirectory;
	CTimeKey  tRetryTime;
	CTimeSpan  tRetryInterval;
	CFileFindEx  cFileFind[3];
	CStringArray  szUsers[3];
	INTERNET_PORT  nInternetPort;
	CInternetFile  *pInternetFile[2];
	CFtpConnection  *pFtpConnection;
	CInternetSession  cInternetSession;
	CArchivesExtractionProfileInfo  *pFTPProfile;

	for (nUser = 0, nUsers = (pProfile->GetFTPOption()) ? EnumFTPUsers(pProfile, szUsers[0], szUsers[1], szUsers[2]) : 0, szName = pProfile->GetName(), nPort = pProfile->GetFTPPort(), szFileName = pProfile->GetFileName(), nAudition = pProfile->GetFTPAudition(); nUser < nUsers; nUser++)
	{
		if ((pFTPProfile = new CArchivesExtractionProfileInfo))
		{
			for (pFTPProfile->Copy(pProfile), nIndex = -1; TRUE; )
			{
				pProfile->GetFTPRetryInfo(nRetries[0], tRetryInterval);
				nRetries[1] = pProfile->GetFTPRetryCount();
				tRetryTime = pProfile->GetFTPRetryTime();
				break;
			}
			pFTPProfile->SetFTPLocation((szLocation = szUsers[0].GetAt(nUser)));
			pFTPProfile->SetFTPUserName((szUserName = szUsers[1].GetAt(nUser)));
			pFTPProfile->SetFTPPassword((szPassword = szUsers[2].GetAt(nUser)));
			if (AfxParseURL(szLocation, dwService, szServer, szDirectory, nInternetPort))
			{
				if (cFileFind[0].FindFile(szFileName) && !cFileFind[0].FindNextFile())
				{
					if (cFile[0].Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
					{
						try
						{
							pFtpConnection = cInternetSession.GetFtpConnection(szServer, szUserName, szPassword, (!nPort) ? ((nInternetPort == INTERNET_DEFAULT_FTP_PORT) ? INTERNET_INVALID_PORT_NUMBER : nInternetPort) : nPort);
						}
						catch (CInternetException *pException)
						{
							if (nRetries[0] > 0 && nRetries[0] > nRetries[1])
							{
								for (pFTPProfile->SetFTPRetryCount((nRetries[0] != (UINT)-1) ? (nRetries[1] + 1) : nRetries[1]), pFTPProfile->SetFTPRetryTime(CTime::GetCurrentTime().GetTime() + tRetryInterval.GetTotalSeconds()); (nIndex = m_pFTPQueue.Add(pFTPProfile)) >= 0; )
								{
									m_nTimerIDs.Add((LPVOID)SetTimer((HWND)NULL, m_nTimerIDs.GetSize(), (UINT)(1000 * tRetryInterval.GetTotalSeconds()), NULL));
									break;
								}
								if ((nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES) && nIndex < 0)
								{
									for (szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[0].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_INTERNAL_FAILURE)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE); (pFTPProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER) && cFileFind[2].FindFile(pFTPProfile->GetAutomationScriptOutput()) && !cFileFind[2].FindNextFile(); )
									{
										szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILURECOMMENT), (LPCTSTR)cFileFind[2].GetFileName());
										ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
										cFileFind[2].Close();
										break;
									}
								}
							}
							else
							{
								if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
								{
									for (szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_CONNECTION_FAILURE), (LPCTSTR)szServer), szError[1].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_CONNECTION_RETRIES_FAILURE), (LPCTSTR)szServer, nRetries[0]), szError[2].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szError[0]), szError[3].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szError[1]), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, (!nRetries[0]) ? szError[2] : szError[3], FALSE); (pFTPProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER) && cFileFind[2].FindFile(pFTPProfile->GetAutomationScriptOutput()) && !cFileFind[2].FindNextFile(); )
									{
										szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILURECOMMENT), (LPCTSTR)cFileFind[2].GetFileName());
										ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
										cFileFind[2].Close();
										break;
									}
								}
							}
							for (; nIndex < 0; )
							{
								delete pFTPProfile;
								break;
							}
							pException->Delete();
							cFileFind[0].Close();
							cFile[0].Close();
							continue;
						}
						try
						{
							for (szDirectory = (szDirectory.Left(lstrlen(STRING(IDS_INTERNET_DELIMITER))) == STRING(IDS_INTERNET_DELIMITER)) ? szDirectory.Mid(lstrlen(STRING(IDS_INTERNET_DELIMITER))) : szDirectory; !szDirectory.IsEmpty(); )
							{
								pFtpConnection->SetCurrentDirectory(szDirectory);
								break;
							}
							pInternetFile[0] = pFtpConnection->OpenFile((szFTPName[0] = cFileFind[0].GetFileName()), GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII);
						}
						catch (CInternetException *pException)
						{
							if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
							{
								for (szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[0].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_DESTINATIONFILE_OPEN_FAILURE)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE); (pFTPProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER) && cFileFind[2].FindFile(pFTPProfile->GetAutomationScriptOutput()) && !cFileFind[2].FindNextFile(); )
								{
									szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILURECOMMENT), (LPCTSTR)cFileFind[2].GetFileName());
									ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
									cFileFind[2].Close();
									break;
								}
							}
							pFtpConnection->Close();
							pException->Delete();
							delete pFtpConnection;
							delete pFTPProfile;
							cFileFind[0].Close();
							cFile[0].Close();
							continue;
						}
						try
						{
							while ((bFile = ReadFile(cFile[0].m_hFile, szData, sizeof(szData), &cbFile, (LPOVERLAPPED)NULL)) && cbFile > 0)
							{
								pInternetFile[0]->Write(szData, cbFile);
								continue;
							}
							for (pInternetFile[0]->Close(); bFile; )
							{
								if (pFTPProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER)
								{
									if (cFileFind[1].FindFile(pFTPProfile->GetAutomationScriptOutput()) && !cFileFind[1].FindNextFile())
									{
										if (cFile[1].Open(cFileFind[1].GetFilePath(), CFile::modeRead | CFile::shareDenyWrite))
										{
											try
											{
												for (szDirectory = (szDirectory.Left(lstrlen(STRING(IDS_INTERNET_DELIMITER))) == STRING(IDS_INTERNET_DELIMITER)) ? szDirectory.Mid(lstrlen(STRING(IDS_INTERNET_DELIMITER))) : szDirectory; !szDirectory.IsEmpty(); )
												{
													pFtpConnection->SetCurrentDirectory(szDirectory);
													break;
												}
												pInternetFile[1] = pFtpConnection->OpenFile((szFTPName[1] = cFileFind[1].GetFileName()), GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII);
											}
											catch (CInternetException *pException)
											{
												if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL)
												{
													szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFER_SUCCESS), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szServer);
													ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
												}
												if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
												{
													szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[1].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_DESTINATIONFILE_OPEN_FAILURE));
													ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
												}
												pFtpConnection->Close();
												pException->Delete();
												delete pInternetFile[0];
												delete pFtpConnection;
												delete pFTPProfile;
												cFileFind[0].Close();
												cFileFind[1].Close();
												cFile[0].Close();
												cFile[1].Close();
												break;
											}
											try
											{
												while ((bFile = ReadFile(cFile[1].m_hFile, szData, sizeof(szData), &cbFile, (LPOVERLAPPED)NULL)) && cbFile > 0)
												{
													pInternetFile[1]->Write(szData, cbFile);
													continue;
												}
												if (bFile)
												{
													if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL)
													{
														szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERS_SUCCESS), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)cFileFind[1].GetFileName(), (LPCTSTR)szServer);
														ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
													}
													pInternetFile[1]->Close();
												}
												else
												{
													if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL)
													{
														szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFER_SUCCESS), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szServer);
														ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
													}
													if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
													{
														szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[1].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_SOURCEFILE_READ_FAILURE));
														ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
													}
													pInternetFile[1]->Close();
													pFtpConnection->Remove(szFTPName[1]);
												}
												pFtpConnection->Close();
												delete pInternetFile[0];
												delete pInternetFile[1];
												delete pFtpConnection;
												delete pFTPProfile;
												cFileFind[0].Close();
												cFileFind[1].Close();
												cFile[0].Close();
												cFile[1].Close();
												break;
											}
											catch (CInternetException *pException)
											{
												if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL)
												{
													szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFER_SUCCESS), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szServer);
													ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
												}
												if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
												{
													szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[1].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_DESTINATIONFILE_WRITE_FAILURE));
													ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
												}
												pInternetFile[1]->Close();
												pFtpConnection->Remove(szFTPName[1]);
												pFtpConnection->Close();
												pException->Delete();
												delete pInternetFile[0];
												delete pInternetFile[1];
												delete pFtpConnection;
												delete pFTPProfile;
												cFileFind[0].Close();
												cFileFind[1].Close();
												cFile[0].Close();
												cFile[1].Close();
												break;
											}
											cFile[1].Close();
										}
										if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL)
										{
											szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFER_SUCCESS), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szServer);
											ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
										}
										if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
										{
											szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[1].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_SOURCEFILE_OPEN_FAILURE));
											ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
										}
										cFileFind[1].Close();
									}
									else
									{
										if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL)
										{
											szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFER_SUCCESS), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szServer);
											ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
										}
										if ((nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES) && !pFTPProfile->GetAutomationScriptOutput().IsEmpty())
										{
											szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)pFTPProfile->GetAutomationScriptOutput(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_SOURCEFILE_OPEN_FAILURE));
											ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
										}
									}
								}
								else
								{
									if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL)
									{
										szMessage.Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFER_SUCCESS), (LPCTSTR)cFileFind[0].GetFileName(), (LPCTSTR)szServer);
										ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
									}
								}
								pFtpConnection->Close();
								delete pInternetFile[0];
								delete pFtpConnection;
								delete pFTPProfile;
								cFileFind[0].Close();
								cFile[0].Close();
								break;
							}
							if (!bFile)
							{
								if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
								{
									for (szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[0].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_SOURCEFILE_READ_FAILURE)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE); (pFTPProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER) && cFileFind[2].FindFile(pFTPProfile->GetAutomationScriptOutput()) && !cFileFind[2].FindNextFile(); )
									{
										szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILURECOMMENT), (LPCTSTR)cFileFind[2].GetFileName());
										ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
										cFileFind[2].Close();
										break;
									}
								}
								pFtpConnection->Remove(szFTPName[0]);
								pFtpConnection->Close();
								delete pInternetFile[0];
								delete pFtpConnection;
								delete pFTPProfile;
								cFileFind[0].Close();
								cFile[0].Close();
							}
							continue;
						}
						catch (CInternetException *pException)
						{
							if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
							{
								for (szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)cFileFind[0].GetFileName(), STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_DESTINATIONFILE_WRITE_FAILURE)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE); (pFTPProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER) && cFileFind[2].FindFile(pFTPProfile->GetAutomationScriptOutput()) && !cFileFind[2].FindNextFile(); )
								{
									szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILURECOMMENT), (LPCTSTR)cFileFind[2].GetFileName());
									ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
									cFileFind[2].Close();
									break;
								}
							}
							pInternetFile[0]->Close();
							pFtpConnection->Remove(szFTPName[0]);
							pFtpConnection->Close();
							pException->Delete();
							delete pInternetFile[0];
							delete pFtpConnection;
							delete pFTPProfile;
							cFileFind[0].Close();
							cFile[0].Close();
							continue;
						}
						cFile[0].Close();
					}
					cFileFind[0].Close();
				}
				if ((nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES) && !szFileName.IsEmpty())
				{
					for (szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)szFileName, STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_SOURCEFILE_OPEN_FAILURE)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE); (pFTPProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER) && cFileFind[2].FindFile(pFTPProfile->GetAutomationScriptOutput()) && !cFileFind[2].FindNextFile(); )
					{
						szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILURECOMMENT), (LPCTSTR)cFileFind[2].GetFileName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
						cFileFind[2].Close();
						break;
					}
				}
				delete pFTPProfile;
				break;
			}
			delete pFTPProfile;
		}
		if (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES)
		{
			for (szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILUREFORMAT), (LPCTSTR)szFileName, STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_INTERNAL_FAILURE)), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE); (pProfile->GetAutomationScriptOptions() & ARCHIVESEXTRACTIONINFO_AUTOMATIONOPTION_FTPTRANSFER) && cFileFind[2].FindFile(pProfile->GetAutomationScriptOutput()) && !cFileFind[2].FindNextFile(); )
			{
				szError[0].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPFAILURECOMMENT), (LPCTSTR)cFileFind[2].GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError[0], FALSE);
				cFileFind[2].Close();
				break;
			}
		}
		break;
	}
}

VOID CTMExtractionThread::Alert(CONST CArchivesExtractionProfileInfo *pProfile, BOOL bSuccess)
{
	CString  szMessage[2];
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
	{
		if ((pAlertInfo[1] = (bSuccess) ? pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DATA_EXTRACTIONS_SUCCESS))) : pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DATA_EXTRACTIONS_FAILURE)))))
		{
			szMessage[0].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DATA_EXTRACTIONS_SUCCESS), (LPCTSTR)pProfile->GetName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)cComputerToken.GetComputerName());
			szMessage[1].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DATA_EXTRACTIONS_FAILURE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)pProfile->GetName());
			if (pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DATA_EXTRACTIONS_SUCCESS) && pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DATA_EXTRACTIONS_FAILURE))
			{
				szMessage[0] = pAlertInfo[1]->GetMessage();
				szMessage[1] = pAlertInfo[1]->GetMessage();
			}
			pAlertInfo[0]->Copy(pAlertInfo[1]);
			pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
			pAlertInfo[0]->SetType((bSuccess) ? EVENT_TYPE_SUCCESS : EVENT_TYPE_WARNING);
			pAlertInfo[0]->SetMessage((bSuccess) ? szMessage[0] : szMessage[1]);
			pAlertInfo[0]->SetExtraInfo(pProfile->GetFileName());
			ReportEvent(pAlertInfo[0]);
		}
		delete pAlertInfo[0];
	}
}

INT CTMExtractionThread::EnumFTPUsers(CONST CArchivesExtractionProfileInfo *pProfile, CStringArray &szLocations, CStringArray &szUsers, CStringArray &szPasswords) CONST
{
	for (ExtractFTPUsersData(pProfile->GetFTPLocation(), szLocations), ExtractFTPUsersData(pProfile->GetFTPUserName(), szUsers), ExtractFTPUsersData(pProfile->GetFTPPassword(), szPasswords); szLocations.GetSize() != szUsers.GetSize() || szLocations.GetSize() != szPasswords.GetSize(); )
	{
		szPasswords.SetSize(szLocations.GetSize());
		szUsers.SetSize(szLocations.GetSize());
		break;
	}
	return((INT)szLocations.GetSize());
}

INT CTMExtractionThread::ExtractFTPUsersData(LPCTSTR pszData, CStringArray &szData) CONST
{
	INT  nPos[2];
	CString  szInfo;

	for (szInfo = pszData, szData.RemoveAll(); !szInfo.IsEmpty(); )
	{
		nPos[0] = szInfo.Find(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPUSERS_SEPARATOR_SEMICOLON));
		nPos[1] = szInfo.Find(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPUSERS_SEPARATOR_COMMA));
		if ((nPos[0] < nPos[1] || nPos[1] < 0) && nPos[0] >= 0)
		{
			szData.Add(szInfo.Left(nPos[0]));
			szInfo = szInfo.Mid(nPos[0]);
			szInfo = szInfo.Mid(lstrlen(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPUSERS_SEPARATOR_SEMICOLON)));
			continue;
		}
		if ((nPos[0] >= nPos[1] || nPos[0] < 0) && nPos[1] >= 0)
		{
			szData.Add(szInfo.Left(nPos[1]));
			szInfo = szInfo.Mid(nPos[1]);
			szInfo = szInfo.Mid(lstrlen(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_FTPUSERS_SEPARATOR_COMMA)));
			continue;
		}
		szData.Add(szInfo);
		szInfo.Empty();
	}
	return((INT)szData.GetSize());
}

BOOL CTMExtractionThread::TestDirectory(LPCTSTR pszFileName) CONST
{
	INT  nPos;
	CString  szDrive;
	CString  szFilePath;
	CString  szFileName;
	CString  szFileTitle;
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;

	if (cFileFind.FindFile((szFileName = pszFileName)))
	{
		cFileFind.Close();
		return TRUE;
	}
	for (nPos = lstrlen(szFileName), szDrive = cDrives.ExtractDrive(szFileName), GetFileTitle(szFileName, szFileTitle.GetBufferSetLength(max(GetFileTitle(szFileName, (LPTSTR)NULL, 0) - 1, 0)), ::GetFileTitle(szFileName, (LPTSTR)NULL, 0)), szFileTitle.ReleaseBuffer(), nPos -= szFileTitle.GetLength(), szFilePath = (nPos > 0) ? szFileName : EMPTYSTRING; nPos >= 0; nPos--)
	{
		if (!_tcsnicmp(szFileName.Mid(nPos), szFileTitle, szFileTitle.GetLength()))
		{
			if (!_tcsnicmp(szFileName, szDrive, szDrive.GetLength()) && szDrive.GetLength() > 0)
			{
				szFilePath = (nPos > szDrive.GetLength()) ? szFileName.Left(nPos - 1) : EMPTYSTRING;
				break;
			}
			if (!_tcsnicmp(szFileName, szDrive, szDrive.GetLength() - 1) && szDrive.GetLength() > 0)
			{
				szFilePath = (nPos > szDrive.GetLength() - 1) ? szFileName.Left(nPos - 1) : EMPTYSTRING;
				break;
			}
			szFilePath = (nPos > 0 && cDrives.GetPathDelimiter() == szFileName.GetAt(nPos - 1)) ? szFileName.Left(nPos - 1) : szFileName.Left(nPos);
			break;
		}
	}
	if (!szFilePath.IsEmpty())
	{
		if (cFileFind.FindFile(szFilePath))
		{
			cFileFind.Close();
			return TRUE;
		}
		return((SHCreateDirectoryEx((HWND)NULL, CFileEx::TranslateToUNCName(szFilePath), (LPSECURITY_ATTRIBUTES)NULL) == ERROR_SUCCESS) ? TRUE : FALSE);
	}
	return TRUE;
}

VOID CTMExtractionThread::ShowErrors(CONST CStringArray &szErrors)
{
	INT  nError;
	INT  nErrors;
	CString  szError[2];

	for (nError = 0, nErrors = (szErrors.GetSize() > 1) ? (INT)(szErrors.GetSize() - 1) : (INT)szErrors.GetSize(), szError[0].Empty(); nError < nErrors; nError++)
	{
		szError[1].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_MESSAGE_NAME), (LPCTSTR)szErrors.GetAt(nError));
		szError[0] += (!szError[0].IsEmpty()) ? (STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_MESSAGE_SEPARATOR) + szError[1]) : szError[1];
		continue;
	}
	for (szError[1].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_SCHEDULE_FAILURE), (szErrors.GetSize() == 1) ? (LPCTSTR)szErrors.GetAt(szErrors.GetUpperBound()) : EMPTYSTRING); szErrors.GetSize() > 1; )
	{
		szError[1].Format(STRING(IDS_TELEMETRYARCHIVES_EXTRACTIONS_SCHEDULE_FAILURES), (LPCTSTR)szError[0], (LPCTSTR)szErrors.GetAt(szErrors.GetUpperBound()));
		break;
	}
	ReportEvent((szErrors.GetSize() > 0) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING) : 0, szError[1]);
}

BOOL CTMExtractionThread::PreTranslateMessage(MSG *pMsg)
{
	INT  nJob;
	INT  nJobs;
	INT  nTimer;
	INT  nTimers;
	CTimeKey  tTimeKey;
	CArchivesExtractionProfileInfo  *pProfile;

	if (pMsg->message == WM_TIMER)
	{
		for (nTimer = 0, nTimers = (INT)m_nTimerIDs.GetSize(); nTimer < nTimers; nTimer++)
		{
			if (m_nTimerIDs.GetAt(nTimer) == (LPCVOID)pMsg->wParam) break;
			continue;
		}
		if (nTimer < nTimers)
		{
			for (nJob = 0, nJobs = (INT)m_pFTPQueue.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pProfile = m_pFTPQueue.GetAt(nJob)) != (CArchivesExtractionProfileInfo *)NULL)
				{
					if (pProfile->GetFTPRetryTime() > tTimeKey) continue;
					Transfer(pProfile);
				}
				m_pFTPQueue.RemoveAt(nJob);
				delete pProfile;
				nJobs--;
				nJob--;
			}
			KillTimer((HWND)NULL, (UINT_PTR)m_nTimerIDs.GetAt(nTimer));
			m_nTimerIDs.RemoveAt(nTimer);
			return TRUE;
		}
	}
	return CThread::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CTMExtractionThread, CThread)
	//{{AFX_MSG_MAP(CTMExtractionThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMExtractionThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTMHistoryFileExtractionThread

IMPLEMENT_DYNCREATE(CTMHistoryFileExtractionThread, CThread)

CTMHistoryFileExtractionThread::CTMHistoryFileExtractionThread() : CThread()
{
	return;
}

BOOL CTMHistoryFileExtractionThread::Start()
{
	CByteArray  nInfo;
	CProfile  cProfile;

	return((cProfile.GetTelemetryHistoryFileExtractionInfo(nInfo) && m_pProfiles.Unmap(nInfo)) ? CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CTMHistoryFileExtractionThread::Stop()
{
	CByteArray  nInfo;
	CProfile  cProfile;

	return((DestroyThread() >= 0) ? (m_pProfiles.Map(nInfo) && cProfile.SetTelemetryHistoryFileExtractionInfo(nInfo)) : FALSE);
}

BOOL CTMHistoryFileExtractionThread::Update(CHistoryFileExtractionProfileInfo *pProfile)
{
	CHistoryFileExtractionProfileInfo  *pProfileInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProfileInfo = (!m_pProfiles.GetSize()) ? new CHistoryFileExtractionProfileInfo : (CHistoryFileExtractionProfileInfo *)NULL))
	{
		for (pProfileInfo->Copy(pProfile); m_pProfiles.Add(pProfileInfo) >= 0; )
		{
			m_bAbort.ResetEvent();
			m_bUpdate.SetEvent();
			return TRUE;
		}
		delete pProfileInfo;
	}
	return FALSE;
}

BOOL CTMHistoryFileExtractionThread::EnumExtractions(CHistoryFileExtractionProfiles &pProfiles) CONST
{
	CHistoryFileExtractionProfileInfo  *pProfileInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProfileInfo = (!m_pProfiles.GetSize()) ? new CHistoryFileExtractionProfileInfo : (CHistoryFileExtractionProfileInfo *)NULL))
	{
		if (pProfiles.Add(pProfileInfo) >= 0) return TRUE;
		delete pProfileInfo;
	}
	return((pProfiles.Copy(&m_pProfiles)) ? (pProfiles.GetSize() > 0) : FALSE);
}

BOOL CTMHistoryFileExtractionThread::AbortExtractions(CONST CHistoryFileExtractionProfiles &pProfiles)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (pProfiles.Compare(&m_pProfiles))
	{
		m_pProfiles.RemoveAll();
		m_bAbort.SetEvent();
		return TRUE;
	}
	return FALSE;
}

int CTMHistoryFileExtractionThread::Run()
{
	INT  nFile;
	INT  nFiles;
	INT  nMessage;
	INT  nMessages;
	UINT  nResult;
	BOOL  bError;
	BOOL  bAbort;
	CFile  cFile;
	DWORD  cbData;
	DWORD  dwWait;
	DWORD  dwResult;
	CString  szMessage;
	CString  szUnitTag;
	CString  szFileName[3];
	CTimeKey  tTimeKey[3];
	CTimeSpan  tTime[2];
	CByteArray  nFileData;
	CStringArray  szFiles;
	CStringArray  szSources;
	CStringArray  szMessages;
	CHistoryFile  cHistoryFile;
	CTMEnvironment  cTMEnvironment;
	CHistoryTMProcessEngine  cHistoryTMProcessEngine;
	CHistoryFileExtractionProfileInfo  cHistoryFileExtractionInfo;

	do
	{
		if (Lock())
		{
			for (cHistoryFileExtractionInfo.SetFileName(EMPTYSTRING); m_pProfiles.GetSize() > 0; )
			{
				cHistoryFileExtractionInfo.Copy(m_pProfiles.GetAt((INT)m_pProfiles.GetUpperBound()));
				break;
			}
			if (cHistoryFileExtractionInfo.GetFileName().IsEmpty())
			{
				m_pProfiles.RemoveAll();
				dwWait = INFINITE;
				Unlock();
				continue;
			}
			Unlock();
		}
		if (cHistoryFileExtractionInfo.GetDeniedExecutionTime(tTime[0], tTime[1]))
		{
			if ((tTimeKey[0] = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tTime[0].GetTotalSeconds() % SECONDSPERDAY  &&  tTimeKey[0].GetTime() % SECONDSPERDAY <= tTime[1].GetTotalSeconds() % SECONDSPERDAY)
			{
				dwWait = (DWORD)(1000 * (tTime[1].GetTotalSeconds() % SECONDSPERDAY - tTimeKey[0].GetTime() % SECONDSPERDAY));
				continue;
			}
		}
		if (cTMEnvironment.Create(GetDatabase()))
		{
			for (szMessage.Format((cHistoryFileExtractionInfo.GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) ? STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_MULTIPLEFILESEXECUTION_MESSAGE) : STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SINGLEFILEEXECUTION_MESSAGE), (LPCTSTR)cHistoryFileExtractionInfo.GetFileName()), ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE), szFileName[0] = DetermineSourceFile(&cHistoryFileExtractionInfo, (szUnitTag = EMPTYSTRING), (tTimeKey[0] = (cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STARTTIME) ? cHistoryFileExtractionInfo.GetStartTime() : 0), szMessages), szFileName[1].Empty(), szFiles.RemoveAll(), bError = FALSE, bAbort = FALSE; !(bError = szFileName[0].IsEmpty()); szFileName[0] = DetermineSourceFile(&cHistoryFileExtractionInfo, szUnitTag, tTimeKey[0], szMessages))
			{
				for (nMessage = 0, nMessages = (INT)szMessages.GetSize(), szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILECHANGE_SUCCESS), (LPCTSTR)szFileName[0], (LPCTSTR)tTimeKey[0].FormatGmt()), ReportEvent((szFileName[0].CompareNoCase(szFileName[1])) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szMessage, FALSE), szFileName[1] = szFileName[0]; nMessage < nMessages; nMessage++)
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessages.GetAt(nMessage), FALSE);
					szMessages.RemoveAt(nMessage);
					nMessages--;
					nMessage--;
				}
				if (cHistoryTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), szFileName[0], &cTMEnvironment))
				{
					if ((nResult = cHistoryTMProcessEngine.ProcessTMData(GetDatabase(), &cTMEnvironment, (tTimeKey[1] = tTimeKey[0]))) & HISTORYFILE_SUCCESS)
					{
						while ((dwResult = Wait(m_bAbort, FALSE, 0)) == WAIT_TIMEOUT && (nResult & (HISTORYFILE_TMPARAMETERS | HISTORYFILE_TMUNIT)) && ((tTimeKey[0] > tTimeKey[1] && szUnitTag.IsEmpty()) || (tTimeKey[0] >= tTimeKey[1] && !szUnitTag.IsEmpty())))
						{
							if (((nResult = cHistoryTMProcessEngine.ReplayTMData(GetDatabase(), &cTMEnvironment, tTimeKey[1], 0)) & HISTORYFILE_SUCCESS) != HISTORYFILE_SUCCESS)
							{
								szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEREAD_FAILURE), (LPCTSTR)szFileName[0]);
								ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
								RemoveSourceFile(&cHistoryFileExtractionInfo, szFileName[0]);
								break;
							}
						}
						for (dwWait = 0; (dwResult = (dwResult == WAIT_TIMEOUT) ? Wait(m_bAbort, FALSE, dwWait) : dwResult) == WAIT_TIMEOUT && (nResult & HISTORYFILE_SUCCESS) && (nResult & (HISTORYFILE_TMUNIT | HISTORYFILE_TMPARAMETERS)); )
						{
							if ((tTimeKey[2] = (cHistoryFileExtractionInfo.GetDeniedExecutionTime(tTime[0], tTime[1])) ? CTime::GetCurrentTime().GetTime() : 0).GetTime() % SECONDSPERDAY >= tTime[0].GetTotalSeconds() % SECONDSPERDAY  &&  tTimeKey[2].GetTime() % SECONDSPERDAY <= tTime[1].GetTotalSeconds() % SECONDSPERDAY  &&  tTimeKey[2] > 0)
							{
								dwWait = (DWORD)(1000 * (tTime[1].GetTotalSeconds() % SECONDSPERDAY - tTimeKey[2].GetTime() % SECONDSPERDAY));
								continue;
							}
							if (cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STANDARD)
							{
								for (szFileName[2] = cHistoryFileExtractionInfo.GetFileName(), dwWait = 0; !szFiles.GetSize(); )
								{
									cHistoryFile.Remove(szFileName[2]);
									szFiles.Add(szFileName[2]);
									break;
								}
								if (cHistoryFile.Open(szFileName[2], GetAccountSpacecraftName(), HISTORYSTORE_TYPE_TM, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
								{
									if (((cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPTIME) && tTimeKey[1] <= cHistoryFileExtractionInfo.GetStopTime()) || ((cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPSIZE) && cHistoryFile.GetSize() < cHistoryFileExtractionInfo.GetStopSize()) || (cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPDISK))
									{
										if ((!cHistoryFile.IsEmpty() || cHistoryFile.SetUpdateInterval(cHistoryFileExtractionInfo.GetUpdateInterval())) && (!FilterFileData(&cHistoryFileExtractionInfo, &cTMEnvironment) || (cHistoryFile.Write(&cTMEnvironment) & HISTORYFILE_SUCCESS)))
										{
											if (((nResult = cHistoryTMProcessEngine.ReplayTMData(GetDatabase(), &cTMEnvironment, (tTimeKey[2] = tTimeKey[1]), 0)) & HISTORYFILE_SUCCESS) && (nResult & (HISTORYFILE_TMUNIT | HISTORYFILE_TMPARAMETERS)) != 0)
											{
												if (tTimeKey[2] >= tTimeKey[1] && (tTimeKey[2].GetTime() - tTimeKey[1].GetTime() <= CTimeSpan(cHistoryFileExtractionInfo.GetGapInterval()).GetTotalSeconds() || cHistoryFileExtractionInfo.GetSources(szSources) == 1))
												{
													tTimeKey[1] = tTimeKey[2];
													cHistoryFile.Close();
													continue;
												}
												if (tTimeKey[2] >= tTimeKey[1])
												{
													cHistoryFile.Close();
													break;
												}
												nResult = HISTORYFILE_ERROR;
											}
											if ((nResult & HISTORYFILE_SUCCESS) != HISTORYFILE_SUCCESS)
											{
												szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEREAD_FAILURE), (LPCTSTR)szFileName[0]);
												ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
												RemoveSourceFile(&cHistoryFileExtractionInfo, szFileName[0]);
											}
											cHistoryFile.Close();
											break;
										}
										if ((cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPDISK) != HISTORYFILEEXTRACTION_OPTION_STOPDISK)
										{
											szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_FILEWRITE_FAILURE), (LPCTSTR)szFileName[2]);
											ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
											bError = TRUE;
										}
									}
									else
									{
										cHistoryFile.Close();
										break;
									}
								}
								else
								{
									szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_FILEOPEN_FAILURE), (LPCTSTR)szFileName[2]);
									ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
									bError = TRUE;
								}
							}
							if (cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_RAW)
							{
								if (FilterFileData(&cHistoryFileExtractionInfo, &cTMEnvironment) && cTMEnvironment.GetTMUnit()->IsValid())
								{
									for (nFile = 0, nFiles = (INT)szFiles.GetSize(), szFileName[2] = ConstructFileName(&cHistoryFileExtractionInfo, &cTMEnvironment), dwWait = 0; nFile < nFiles; nFile++)
									{
										if (!szFiles.GetAt(nFile).CompareNoCase(szFileName[2])) break;
										continue;
									}
									for (; nFile == nFiles; )
									{
										szFiles.Add(szFileName[2]);
										break;
									}
									if (cFile.Open(szFileName[2], (nFile < nFiles) ? (CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareExclusive) : (CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive)))
									{
										if (((cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPTIME) && tTimeKey[1] <= cHistoryFileExtractionInfo.GetStopTime()) || ((cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPSIZE) && cFile.GetLength() < cHistoryFileExtractionInfo.GetStopSize()) || (cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPDISK))
										{
											if (ConvertFileData(&cHistoryFileExtractionInfo, &cTMEnvironment, nFileData) && cFile.SeekToEnd() >= 0 && WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &cbData, (LPOVERLAPPED)NULL) && cbData == (DWORD)nFileData.GetSize())
											{
												if (((nResult = cHistoryTMProcessEngine.ReplayTMData(GetDatabase(), &cTMEnvironment, (tTimeKey[2] = tTimeKey[1]), 0)) & HISTORYFILE_SUCCESS) && (nResult & (HISTORYFILE_TMUNIT | HISTORYFILE_TMPARAMETERS)) != 0)
												{
													if (tTimeKey[2] >= tTimeKey[1] && (tTimeKey[2].GetTime() - tTimeKey[1].GetTime() <= CTimeSpan(cHistoryFileExtractionInfo.GetGapInterval()).GetTotalSeconds() || cHistoryFileExtractionInfo.GetSources(szSources) == 1))
													{
														tTimeKey[1] = tTimeKey[2];
														cFile.Close();
														continue;
													}
													if (tTimeKey[2] >= tTimeKey[1])
													{
														cFile.Close();
														break;
													}
													nResult = HISTORYFILE_ERROR;
												}
												if ((nResult & HISTORYFILE_SUCCESS) != HISTORYFILE_SUCCESS)
												{
													szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEREAD_FAILURE), (LPCTSTR)szFileName[0]);
													ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
													RemoveSourceFile(&cHistoryFileExtractionInfo, szFileName[0]);
												}
												cFile.Close();
												break;
											}
											if ((cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STOPDISK) != HISTORYFILEEXTRACTION_OPTION_STOPDISK)
											{
												szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_FILEWRITE_FAILURE), (LPCTSTR)szFileName[2]);
												ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
												bError = TRUE;
											}
										}
										else
										{
											cFile.Close();
											break;
										}
									}
									else
									{
										szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_FILEOPEN_FAILURE), (LPCTSTR)szFileName[2]);
										ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
										bError = TRUE;
									}
								}
								else
								{
									if (((nResult = cHistoryTMProcessEngine.ReplayTMData(GetDatabase(), &cTMEnvironment, (tTimeKey[2] = tTimeKey[1]), 0)) & HISTORYFILE_SUCCESS) && (nResult & (HISTORYFILE_TMUNIT | HISTORYFILE_TMPARAMETERS)) != 0)
									{
										if (tTimeKey[2] >= tTimeKey[1] && (tTimeKey[2].GetTime() - tTimeKey[1].GetTime() <= CTimeSpan(cHistoryFileExtractionInfo.GetGapInterval()).GetTotalSeconds() || cHistoryFileExtractionInfo.GetSources(szSources) == 1))
										{
											tTimeKey[1] = tTimeKey[2];
											dwWait = 0;
											continue;
										}
										if (tTimeKey[2] >= tTimeKey[1])
										{
											dwWait = 0;
											break;
										}
										nResult = HISTORYFILE_ERROR;
									}
									if ((nResult & HISTORYFILE_SUCCESS) != HISTORYFILE_SUCCESS)
									{
										szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEREAD_FAILURE), (LPCTSTR)szFileName[0]);
										ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
										RemoveSourceFile(&cHistoryFileExtractionInfo, szFileName[0]);
									}
									dwWait = 0;
									break;
								}
							}
						}
						if (dwResult != WAIT_TIMEOUT || bError)
						{
							for (szMessage.Format((cHistoryFileExtractionInfo.GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) ? STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_MULTIPLEFILESEXECUTION_ABORT) : STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SINGLEFILEEXECUTION_ABORT), (LPCTSTR)cHistoryFileExtractionInfo.GetFileName()); dwResult != WAIT_TIMEOUT; )
							{
								ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
								bAbort = TRUE;
								break;
							}
							for (; cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_STANDARD; )
							{
								cHistoryFile.Remove(cHistoryFileExtractionInfo.GetFileName());
								break;
							}
							for (nFile = 0, nFiles = (cHistoryFileExtractionInfo.GetOptions() & HISTORYFILEEXTRACTION_OPTION_RAW) ? (INT)szFiles.GetSize() : 0; nFile < nFiles; nFile++)
							{
								CFileEx::Remove(szFiles.GetAt(nFile));
								continue;
							}
							cHistoryTMProcessEngine.Close();
							bError = TRUE;
							break;
						}
						if (nResult & HISTORYFILE_SUCCESS)
						{
							cHistoryTMProcessEngine.Close();
							break;
						}
					}
					else
					{
						szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEREAD_FAILURE), (LPCTSTR)szFileName[0]);
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
						RemoveSourceFile(&cHistoryFileExtractionInfo, szFileName[0]);
					}
					cHistoryTMProcessEngine.Close();
				}
				else
				{
					szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEOPEN_FAILURE), (LPCTSTR)szFileName[0]);
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
					RemoveSourceFile(&cHistoryFileExtractionInfo, szFileName[0]);
				}
			}
			if (!bError)
			{
				szMessage.Format((cHistoryFileExtractionInfo.GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) ? STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_MULTIPLEFILESEXECUTION_SUCCESS) : STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SINGLEFILEEXECUTION_SUCCESS), (LPCTSTR)cHistoryFileExtractionInfo.GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
				Alert(&cHistoryFileExtractionInfo, TRUE);
			}
			else
			{
				for (szMessage.Format((cHistoryFileExtractionInfo.GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) ? STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_MULTIPLEFILESEXECUTION_FAILURE) : STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SINGLEFILEEXECUTION_FAILURE), (LPCTSTR)cHistoryFileExtractionInfo.GetFileName()); !bAbort; )
				{
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
					Alert(&cHistoryFileExtractionInfo, FALSE);
					break;
				}
			}
			cTMEnvironment.Destroy();
		}
		else
		{
			szMessage.Format((cHistoryFileExtractionInfo.GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) ? STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_MULTIPLEFILESEXECUTION_FAILURE) : STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SINGLEFILEEXECUTION_FAILURE), (LPCTSTR)cHistoryFileExtractionInfo.GetFileName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
			Alert(&cHistoryFileExtractionInfo, FALSE);
		}
		if (Lock())
		{
			if (m_pProfiles.GetSize() > 0)
			{
				delete m_pProfiles.GetAt((INT)m_pProfiles.GetUpperBound());
				m_pProfiles.RemoveAt(m_pProfiles.GetUpperBound());
			}
			dwWait = (!m_pProfiles.GetSize()) ? INFINITE : 0;
			Unlock();
		}
	} while ((dwResult = Wait(m_bUpdate, FALSE, dwWait)) == WAIT_OBJECT_0 + 1 || dwResult == WAIT_TIMEOUT);
	return 0;
}

CString CTMHistoryFileExtractionThread::DetermineSourceFile(CONST CHistoryFileExtractionProfileInfo *pProfile, LPCTSTR pszUnitTag, CTimeKey &tUnitTime, CStringArray &szMessages) CONST
{
	INT  nSource;
	INT  nSources;
	BOOL  bSource;
	CString  szSource;
	CString  szMessage;
	CLogFile  cLogFile;
	CTimeKey  tTimeKey[3];
	CByteArray  nFileData;
	CStringArray  szSources;
	CStringArray  szErrors;

	for (nSource = 0, nSources = pProfile->GetSources(szSources), szSource.Empty(), szErrors.Copy(szMessages), szMessages.RemoveAll(), szMessage.Empty(), tTimeKey[0] = tTimeKey[1] = tTimeKey[2] = 0; nSource < nSources; nSource++, szMessage.Empty())
	{
		if (cLogFile.Open(szSources.GetAt(nSource), GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TMHISTORY), STRING(IDS_LOGFILETYPE_HISTORY), CFile::modeRead))
		{
			for (bSource = cLogFile.SeekTo(tUnitTime, TRUE); bSource &= cLogFile.Read(tTimeKey[1], nFileData); )
			{
				if (!lstrlen(pszUnitTag) && tUnitTime <= tTimeKey[1].GetTime())
				{
					if (tTimeKey[0] > tTimeKey[1] || !tTimeKey[0].GetTime())
					{
						szSource = szSources.GetAt(nSource);
						tTimeKey[0] = tTimeKey[1];
					}
					break;
				}
				if (lstrlen(pszUnitTag) > 0 && tUnitTime < tTimeKey[1])
				{
					if (tTimeKey[0] > tTimeKey[1] || !tTimeKey[0].GetTime())
					{
						szSource = szSources.GetAt(nSource);
						tTimeKey[0] = tTimeKey[1];
					}
					break;
				}
			}
			if (!bSource)
			{
				if (!cLogFile.SeekToLast() || !cLogFile.Read(tTimeKey[2], nFileData) || tTimeKey[1] != tTimeKey[2])
				{
					szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEREAD_FAILURE), (LPCTSTR)szSources.GetAt(nSource));
					CheckMessage(szMessage, szErrors, szMessages);
				}
			}
			cLogFile.Close();
		}
		else
		{
			szMessage.Format(STRING(IDS_TELEMETRYHISTORYFILE_EXTRACTIONS_SOURCEFILEOPEN_FAILURE), (LPCTSTR)szSources.GetAt(nSource));
			CheckMessage(szMessage, szErrors, szMessages);
		}
	}
	if (!szSource.IsEmpty())
	{
		tUnitTime = tTimeKey[0];
		return szSource;
	}
	return EMPTYSTRING;
}

VOID CTMHistoryFileExtractionThread::RemoveSourceFile(CHistoryFileExtractionProfileInfo *pProfile, LPCTSTR pszFileName) CONST
{
	INT  nSource;
	INT  nSources;
	CStringArray  szSources;

	for (nSource = 0, nSources = pProfile->GetSources(szSources); nSource < nSources; nSource++)
	{
		if (!szSources.GetAt(nSource).CompareNoCase(pszFileName))
		{
			szSources.RemoveAt(nSource);
			nSources--;
			nSource--;
		}
	}
}

CString CTMHistoryFileExtractionThread::ConstructFileName(CONST CHistoryFileExtractionProfileInfo *pProfile, CONST CTMEnvironment *pTMEnvironment) CONST
{
	CString  szFileName[2];

	if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES)
	{
		for (szFileName[0] = pProfile->GetFileName(); PathRemoveFileSpec(szFileName[0].GetBufferSetLength(szFileName[0].GetLength())); )
		{
			for (szFileName[0].ReleaseBuffer(), szFileName[0] += pProfile->GetFileName().GetAt(szFileName[0].GetLength()) + pProfile->GetFilePrefix() + pTMEnvironment->GetTMUnit()->GetTag(); pProfile->GetFilePrefix().IsEmpty() && pProfile->GetFileExtension().IsEmpty(); )
			{
				szFileName[1].Format((pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_ASCII) ? STRING(IDS_TELEMETRYARCHIVES_TOOLSPAGE_ASCIIFILEFORMAT) : STRING(IDS_TELEMETRYARCHIVES_TOOLSPAGE_BINARYFILEFORMAT), (LPCTSTR)szFileName[0]);
				return szFileName[1];
			}
			if (!pProfile->GetFileExtension().IsEmpty())
			{
				for (szFileName[1].Format(STRING(IDS_TELEMETRYARCHIVES_TOOLSPAGE_ASCIIFILEFORMAT), EMPTYSTRING); pProfile->GetFileExtension().GetAt(0) != szFileName[1].GetAt(0); )
				{
					szFileName[0] += szFileName[1].GetAt(0);
					break;
				}
				szFileName[0] += pProfile->GetFileExtension();
			}
			return szFileName[0];
		}
	}
	return pProfile->GetFileName();
}

BOOL CTMHistoryFileExtractionThread::FilterFileData(CONST CHistoryFileExtractionProfileInfo *pProfile, CONST CTMEnvironment *pTMEnvironment) CONST
{
	INT  nFilter;
	INT  nFilters;
	CStringArray  szFilters;

	for (nFilter = 0, nFilters = pProfile->GetFilters(szFilters); nFilter < nFilters; nFilter++)
	{
		if (pTMEnvironment->GetTMUnit()->GetTag() == szFilters.GetAt(nFilter)) break;
		continue;
	}
	return((nFilter < nFilters || !nFilters) ? TRUE : FALSE);
}

BOOL CTMHistoryFileExtractionThread::ConvertFileData(CONST CHistoryFileExtractionProfileInfo *pProfile, CONST CTMEnvironment *pTMEnvironment, CByteArray &nData) CONST
{
	INT  nByte;
	INT  nBytes;
	INT  nRadix;
	CString  szTMUnitData;
	CByteArray  nTMUnitData;
	CStringTools  cStringTools;

	for (nData.RemoveAll(); pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_ASCII; )
	{
		for (nByte = 0, nBytes = pTMEnvironment->GetTMUnit()->GetData(nTMUnitData), nRadix = (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_RADIX2) ? 2 : ((pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_RADIX8) ? 8 : ((pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_RADIX10) ? 10 : 16)); nByte < nBytes; nByte++)
		{
			szTMUnitData += (((pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_BLOCK8BITS) || ((pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_BLOCK16BITS) && nByte % 2 == 0) || ((pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_BLOCK32BITS) && nByte % 4 == 0) || ((pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_BLOCK64BITS))) && nByte> 0) ? SPACE : EMPTYSTRING;
			szTMUnitData += cStringTools.ConvertUIntToPaddedString(nTMUnitData.GetAt(nByte), (nRadix == 2) ? 8 : ((nRadix != 16) ? 3 : 2), nRadix);
		}
		if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_CRSEPARATOR) szTMUnitData += CR;
		if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_EOLSEPARATOR) szTMUnitData += EOL;
		if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_CREOLSEPARATOR) szTMUnitData += CString(CR) + CString(EOL);
#ifndef UNICODE
		if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_UNICODECHARSET)
		{
			nData.SetSize(szTMUnitData.GetLength()*sizeof(WCHAR));
			MultiByteToWideChar(CP_ACP, 0, szTMUnitData, szTMUnitData.GetLength(), (LPWSTR)nData.GetData(), szTMUnitData.GetLength());
		}
		else
		{
			nData.SetSize(szTMUnitData.GetLength()*sizeof(CHAR));
			CopyMemory(nData.GetData(), (LPCTSTR)szTMUnitData, nData.GetSize());
		}
#else
		if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_UNICODECHARSET)
		{
			nData.SetSize(szTMUnitData.GetLength()*sizeof(WCHAR));
			CopyMemory(nData.GetData(), (LPCTSTR)szTMUnitData, nData.GetSize());
		}
		else
		{
			nData.SetSize(szTMUnitData.GetLength()*sizeof(CHAR));
			WideCharToMultiByte(CP_ACP, 0, szTMUnitData, szTMUnitData.GetLength(), (LPSTR)nData.GetData(), szTMUnitData.GetLength(), (LPSTR)NULL, (LPBOOL)NULL);
		}
#endif
		return(nData.GetSize() > 0);
	}
	if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_BINARY)
	{
		for (pTMEnvironment->GetTMUnit()->GetData(nData); nData.GetSize() > 0; )
		{
			if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_CRSEPARATOR)
			{
				nData.Add(CR);
				return TRUE;
			}
			if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_EOLSEPARATOR)
			{
				nData.Add(EOL);
				return TRUE;
			}
			if (pProfile->GetFormatting() & HISTORYFILEEXTRACTION_FORMAT_CREOLSEPARATOR)
			{
				nData.Add(CR);
				nData.Add(EOL);
			}
			return(nData.GetSize() > 0);
		}
	}
	return FALSE;
}

VOID CTMHistoryFileExtractionThread::CheckMessage(LPCTSTR pszMessage, CONST CStringArray &szErrors, CStringArray &szMessages) CONST
{
	INT  nError;
	INT  nErrors;
	INT  nMessage;
	INT  nMessages;

	for (nError = 0, nErrors = (INT)szErrors.GetSize(); nError < nErrors; nError++)
	{
		if (!szErrors.GetAt(nError).Compare(pszMessage)) break;
		continue;
	}
	for (nMessage = 0, nMessages = (INT)szMessages.GetSize(); nMessage < nMessages; nMessage++)
	{
		if (!szMessages.GetAt(nMessage).Compare(pszMessage)) break;
		continue;
	}
	if (nError == nErrors  &&  nMessage == nMessages)
	{
		szMessages.Add(pszMessage);
		return;
	}
}

VOID CTMHistoryFileExtractionThread::Alert(CONST CHistoryFileExtractionProfileInfo *pProfile, BOOL bSuccess)
{
	CString  szMessage[2];
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
	{
		if ((pAlertInfo[1] = (bSuccess) ? pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_HISTORY_FILE_EXTRACTIONS_SUCCESS))) : pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_HISTORY_FILE_EXTRACTIONS_FAILURE)))))
		{
			szMessage[0].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_EXTRACTIONS_SUCCESS), (LPCTSTR)pProfile->GetFileName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)cComputerToken.GetComputerName());
			szMessage[1].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_EXTRACTIONS_FAILURE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)pProfile->GetFileName());
			if (pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_EXTRACTIONS_SUCCESS) && pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_EXTRACTIONS_FAILURE))
			{
				szMessage[0] = pAlertInfo[1]->GetMessage();
				szMessage[1] = pAlertInfo[1]->GetMessage();
			}
			pAlertInfo[0]->Copy(pAlertInfo[1]);
			pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
			pAlertInfo[0]->SetType((bSuccess) ? EVENT_TYPE_SUCCESS : EVENT_TYPE_WARNING);
			pAlertInfo[0]->SetMessage((bSuccess) ? szMessage[0] : szMessage[1]);
			pAlertInfo[0]->SetExtraInfo(pProfile->GetFileName());
			ReportEvent(pAlertInfo[0]);
		}
		delete pAlertInfo[0];
	}
}

BEGIN_MESSAGE_MAP(CTMHistoryFileExtractionThread, CThread)
	//{{AFX_MSG_MAP(CTMHistoryFileExtractionThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMHistoryFileExtractionThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTMArchivesBackupThread

IMPLEMENT_DYNCREATE(CTMArchivesBackupThread, CThread)

BOOL CTMArchivesBackupThread::Start(CONST CHistoryStoreFile *pFile, BOOL bDelayed, HANDLE hSync, HANDLE bQuit)
{
	INT  nPos;
	CFileFindEx  cFileFind;
	CHistoryFile  cHistoryFile;
	TCHAR  szFileName[MAX_PATH];

	if (CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL, TRUE))
	{
		if (bDelayed  &&  cFileFind.FindFile(pFile->GetBackupFileName()) && !cFileFind.FindNextFile())
		{
			m_szFileName[0] = cFileFind.GetRoot();
			m_szFileName[1] = cFileFind.GetFileTitle();
			m_szFileName[2] = cFileFind.GetFilePath().Right(cFileFind.GetFileName().GetLength() - m_szFileName[1].GetLength());
			m_szFileName[1] = pFile->GetFileName().Mid(pFile->GetBackupFileName().Find(m_szFileName[1]));
			m_szFileName[2] = ((nPos = (!m_szFileName[2].IsEmpty()) ? pFile->GetFileName().ReverseFind(m_szFileName[2][0]) : -1) >= 0) ? (LPCTSTR)pFile->GetFileName().Right(pFile->GetFileName().GetLength() - nPos) : EMPTYSTRING;
			m_szFileName[1] = (nPos >= 0) ? (LPCTSTR)m_szFileName[1].Left(m_szFileName[1].GetLength() - m_szFileName[2].GetLength()) : EMPTYSTRING;
			m_cFile.Copy(pFile);
			m_bAutoDelete = TRUE;
			cFileFind.Close();
			m_hSync = hSync;
			m_bQuit = bQuit;
			ResumeThread();
			return TRUE;
		}
		if (!bDelayed  &&  cFileFind.FindFile(pFile->GetFileName()) && !cFileFind.FindNextFile())
		{
			if (GetTempFileName(cFileFind.GetRoot(), GetAccountSpacecraftName(), 0, szFileName) >= 0)
			{
				if (cHistoryFile.Rename(pFile->GetFileName(), szFileName, TRUE))
				{
					for (m_szFileName[0] = cFileFind.GetRoot(), m_szFileName[1] = cFileFind.GetFileTitle(), m_szFileName[2] = cFileFind.GetFilePath().Right(cFileFind.GetFileName().GetLength() - m_szFileName[1].GetLength()), m_cFile.Copy(pFile), m_bAutoDelete = TRUE, m_hSync = hSync, m_bQuit = bQuit; TRUE; )
					{
						m_cFile.SetBackupFileName(szFileName);
						break;
					}
					cFileFind.Close();
					ResumeThread();
					return TRUE;
				}
			}
			cFileFind.Close();
		}
		ResumeThread();
		DestroyThread();
	}
	Alert(pFile, FALSE);
	return FALSE;
}

BOOL CTMArchivesBackupThread::Stop()
{
	m_szFileName[0].Empty();
	m_szFileName[1].Empty();
	m_szFileName[2].Empty();
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CTMArchivesBackupThread::Run()
{
	UINT  nCount;
	UINT  nRetry;
	DWORD  dwWait;
	DWORD  dwData[2];
	DWORD  dwSize[2];
	PBYTE  pfBuffer;
	CString  szRoot;
	CString  szName;
	CString  szTitle;
	CString  szError;
	CFileEx  cFiles[2];
	CLogFile  cLogFile;
	CTimeKey  tTime[2];
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	CTimeSpan  tInterval;
	CByteArray  nFileData;
	CFileFindEx  cFileFind;
	CFileFindEx  cCopyFile;
	CFileFindEx  cDiskFile;
	CFileFindEx  cEnumFile;
	CHistoryFile  cHistoryFile;
	CLogicalDrives  cDrives;
	ULARGE_INTEGER  nDiskInfo[3];
	TCHAR  szFileName[MAX_PATH];

	while (Wait(m_bQuit, FALSE, 0) == WAIT_TIMEOUT)
	{
		if (m_cFile.GetBackupTime(tTime[0]) && tTime[0] > tTime[1])
		{
			Wait(m_bQuit, FALSE, (DWORD)(1000 * (tTime[0].GetTime() - tTime[1].GetTime())));
			tTime[1] = CTime::GetCurrentTime().GetTime();
		}
		if (m_cFile.GetBackupDailyPeriod(tStartTime, tStopTime) && tTime[1].GetTime() % SECONDSPERDAY >= tStartTime.GetTotalSeconds() && tTime[1].GetTime() % SECONDSPERDAY <= tStopTime.GetTotalSeconds())
		{
			Wait(m_bQuit, FALSE, (DWORD)(1000 * (tStopTime.GetTotalSeconds() - tTime[1].GetTime() % SECONDSPERDAY)));
			tTime[1] = CTime::GetCurrentTime().GetTime();
		}
		if (Lock())
		{
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPPROTECTEDDISK)
			{
				GetTempFileName(cDrives.ExtractDrive(m_cFile.GetBackupDirectory()), EMPTYSTRING, 0, szFileName);
				if (GetLastError() != NO_ERROR  &&  Wait(m_bQuit, FALSE, 1000 * TELEMETRYARCHIVESBACKUP_DELAY_INTERVAL) == WAIT_TIMEOUT)
				{
					Unlock();
					continue;
				}
				CFileEx::Remove(szFileName);
			}
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPEMPTYDISK)
			{
				if (cDiskFile.FindFile(cDrives.ExtractDrive(m_cFile.GetBackupDirectory()).Left(cDrives.ExtractDrive(m_cFile.GetBackupDirectory()).GetLength() - 1) + STRING(IDS_FILENAME_ALL)))
				{
					while (cDiskFile.FindNextFile())
					{
						if (cDiskFile.IsDots()) continue;
						break;
					}
					if (!cDiskFile.IsDots() && Wait(m_bQuit, FALSE, 1000 * TELEMETRYARCHIVESBACKUP_DELAY_INTERVAL) == WAIT_TIMEOUT)
					{
						cDiskFile.Close();
						Unlock();
						continue;
					}
					cDiskFile.Close();
				}
			}
			for (_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), EMPTYSTRING); m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPSIMPLE; )
			{
				for (_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_cFile.GetBackupDirectory()); m_cFile.GetBackupDirectory().Right(1) != CString(cDrives.GetPathDelimiter()); )
				{
					_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), CString(cDrives.GetPathDelimiter()));
					break;
				}
				for (_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_szFileName[1] + m_szFileName[2]); cFileFind.FindFile(szFileName); )
				{
					for (szName.Format(STRING(IDS_HISTORYFILE_SINGLEBACKUPFORMAT), (LPCTSTR)(m_szFileName[1] + m_szFileName[2])), szRoot = m_cFile.GetBackupDirectory(); szRoot.Right(1) != CString(cDrives.GetPathDelimiter()); )
					{
						szRoot += cDrives.GetPathDelimiter();
						break;
					}
					if (cCopyFile.FindFile((szName = szRoot + szName)))
					{
						for (nCount = 2; nCount != (UINT)-1; nCount++)
						{
							szName.Format(STRING(IDS_HISTORYFILE_MULTIPLEBACKUPFORMAT), nCount, (LPCTSTR)(m_szFileName[1] + m_szFileName[2]));
							if (cEnumFile.FindFile((szName = szRoot + szName)))
							{
								cEnumFile.Close();
								continue;
							}
							break;
						}
						_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), (nCount != (UINT)-1) ? (LPCTSTR)szName : EMPTYSTRING);
						cCopyFile.Close();
					}
					else
					{
						_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), szName);
						cFileFind.Close();
					}
					break;
				}
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_BEGIN), (LPCTSTR)m_cFile.GetFileName());
				ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
				break;
			}
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPTIMETAGGED)
			{
				if (cLogFile.Open(m_cFile.GetBackupFileName(), GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TMHISTORY), CFile::modeRead))
				{
					if (cLogFile.SeekToFirst() && cLogFile.Read(tTime[0], nFileData))
					{
						for (_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_cFile.GetBackupDirectory()); m_cFile.GetBackupDirectory().Right(1) != CString(cDrives.GetPathDelimiter()); )
						{
							_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), CString(cDrives.GetPathDelimiter()));
							break;
						}
						_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), tTime[0].FormatGmt(STRING(IDS_HISTORYFILE_TIMETAGGEDFORMAT)));
						_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_szFileName[2]);
					}
					cLogFile.Close();
				}
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_BEGIN), (LPCTSTR)m_cFile.GetFileName());
				ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
			}
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPENUMERATED)
			{
				for (nCount = 0, szRoot = (m_cFile.GetBackupDirectory().Right(1) != CString(cDrives.GetPathDelimiter())) ? (m_cFile.GetBackupDirectory() + cDrives.GetPathDelimiter()) : m_cFile.GetBackupDirectory(); nCount != (UINT)-1; nCount++)
				{
					szTitle.Format(STRING(IDS_HISTORYFILE_ENUMERATEDFORMAT), (LPCTSTR)GetAccountSpacecraftName(), nCount);
					_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), szRoot + szTitle + m_szFileName[2]);
					if (cFileFind.FindFile(szFileName))
					{
						cFileFind.Close();
						continue;
					}
					break;
				}
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_BEGIN), (LPCTSTR)m_cFile.GetFileName());
				ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
			}
			if (lstrlen(szFileName) > 0)
			{
				if (TestDirectory(szFileName))
				{
					if ((pfBuffer = new BYTE[TELEMETRYARCHIVESBACKUP_COPY_BUFFER]))
					{
						if (cFiles[0].Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
						{
							if (cFiles[1].Open(m_cFile.GetBackupFileName(), CFile::modeRead | CFile::shareExclusive))
							{
								if (GetDiskFreeSpaceEx(cDrives.ExtractDrive(szFileName), &nDiskInfo[0], &nDiskInfo[1], &nDiskInfo[2]))
								{
									if ((dwSize[0] = GetFileSize((HANDLE)cFiles[1].m_hFile, &dwSize[1])) >= 0 && (dwSize[1] < nDiskInfo[0].HighPart || (dwSize[1] == nDiskInfo[0].HighPart  &&  dwSize[0] < nDiskInfo[0].LowPart)))
									{
										while ((dwWait = Wait(m_bQuit, FALSE, 0)) == WAIT_TIMEOUT)
										{
											if (ReadFile(cFiles[1].m_hFile, pfBuffer, TELEMETRYARCHIVESBACKUP_COPY_BUFFER, &dwData[0], (LPOVERLAPPED)NULL) && dwData[0] > 0 && WriteFile(cFiles[0].m_hFile, pfBuffer, dwData[0], &dwData[1], (LPOVERLAPPED)NULL) && dwData[0] == dwData[1])
											{
												if (dwData[0] == TELEMETRYARCHIVESBACKUP_COPY_BUFFER)
												{
													UpdateArchivingStatus();
													continue;
												}
											}
											break;
										}
										if (dwWait == WAIT_TIMEOUT)
										{
											if (GetFileSize((HANDLE)cFiles[0].m_hFile, &dwSize[0]) == GetFileSize((HANDLE)cFiles[1].m_hFile, &dwSize[1]) && dwSize[0] == dwSize[1])
											{
												delete[] pfBuffer;
												cFiles[0].Close();
												cFiles[1].Close();
												cHistoryFile.Remove(m_cFile.GetBackupFileName());
												szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_END), (LPCTSTR)m_cFile.GetFileName());
												ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
												UpdateArchivingStatus();
												Alert(&m_cFile, TRUE);
												Unlock();
												return 0;
											}
										}
									}
								}
								cFiles[1].Close();
							}
							cFiles[0].Close();
							CFileEx::Remove(szFileName);
							UpdateArchivingStatus();
						}
						delete[] pfBuffer;
					}
				}
				if ((dwWait = Wait(m_bQuit, FALSE, 0)) == WAIT_TIMEOUT)
				{
					if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPRETRIES)
					{
						if ((nCount = m_cFile.GetBackupRetryCount()) > 0)
						{
							m_cFile.GetBackupRetryInfo(nRetry, tInterval);
							m_cFile.SetBackupRetryCount(nCount - 1);
							szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_RETRYLATER), (LPCTSTR)m_cFile.GetFileName(), tInterval.GetTotalSeconds() / SECONDSPERMINUTE);
							ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
							if ((dwWait = Wait(m_bQuit, FALSE, (DWORD)(1000 * tInterval.GetTotalSeconds()))) == WAIT_TIMEOUT)
							{
								Unlock();
								continue;
							}
						}
					}
					for (; dwWait == WAIT_TIMEOUT; )
					{
						cHistoryFile.Remove(m_cFile.GetBackupFileName());
						break;
					}
				}
			}
			Unlock();
			break;
		}
	}
	if ((dwWait = Wait(m_bQuit, FALSE, 0)) != WAIT_OBJECT_0 + 1)
	{
		szError.Format((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPRETRIES) ? (((nCount = m_cFile.GetBackupRetryCount()) >= 0 && m_cFile.GetBackupRetryInfo(nRetry, tInterval) && nCount < nRetry) ? STRING(IDS_TELEMETRYARCHIVES_BACKUP_RETRIES) : STRING(IDS_TELEMETRYARCHIVES_BACKUP_FAILURE)) : STRING(IDS_TELEMETRYARCHIVES_BACKUP_FAILURE), (LPCTSTR)m_cFile.GetFileName(), ((nCount = m_cFile.GetBackupRetryCount()) >= 0 && m_cFile.GetBackupRetryInfo(nRetry, tInterval)) ? (nRetry - nCount) : 0);
		ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING) : 0, szError);
		Alert(&m_cFile, FALSE);
		return 0;
	}
	if (!DelayBackup())
	{
		szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_DELAY), (LPCTSTR)m_cFile.GetFileName());
		ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING) : 0, szError);
		Alert(&m_cFile, FALSE);
	}
	szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_QUIT), (LPCTSTR)m_cFile.GetFileName());
	ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
	return 0;
}

VOID CTMArchivesBackupThread::Alert(CONST CHistoryStoreFile *pFile, BOOL bSuccess)
{
	CString  szMessage[2];
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
	{
		if ((pAlertInfo[1] = (bSuccess) ? pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_HISTORY_FILE_BACKUPS_SUCCESS))) : pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_HISTORY_FILE_BACKUPS_FAILURE)))))
		{
			szMessage[0].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_SUCCESS), (LPCTSTR)pFile->GetFileName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)cComputerToken.GetComputerName());
			szMessage[1].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_FAILURE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)pFile->GetFileName());
			if (pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_SUCCESS) && pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_FAILURE))
			{
				szMessage[0] = pAlertInfo[1]->GetMessage();
				szMessage[1] = pAlertInfo[1]->GetMessage();
			}
			pAlertInfo[0]->Copy(pAlertInfo[1]);
			pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
			pAlertInfo[0]->SetType((bSuccess) ? EVENT_TYPE_SUCCESS : EVENT_TYPE_WARNING);
			pAlertInfo[0]->SetMessage((bSuccess) ? szMessage[0] : szMessage[1]);
			pAlertInfo[0]->SetExtraInfo(pFile->GetFileName());
			ReportEvent(pAlertInfo[0]);
		}
		delete pAlertInfo[0];
	}
}

BOOL CTMArchivesBackupThread::TestDirectory(LPCTSTR pszFileName) CONST
{
	INT  nPos;
	CString  szDrive;
	CString  szFilePath;
	CString  szFileName;
	CString  szFileTitle;
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;

	if (cFileFind.FindFile((szFileName = pszFileName)))
	{
		cFileFind.Close();
		return TRUE;
	}
	for (nPos = lstrlen(szFileName), szDrive = cDrives.ExtractDrive(szFileName), GetFileTitle(szFileName, szFileTitle.GetBufferSetLength(max(GetFileTitle(szFileName, (LPTSTR)NULL, 0) - 1, 0)), ::GetFileTitle(szFileName, (LPTSTR)NULL, 0)), szFileTitle.ReleaseBuffer(), nPos -= szFileTitle.GetLength(), szFilePath = (nPos > 0) ? szFileName : EMPTYSTRING; nPos >= 0; nPos--)
	{
		if (!_tcsnicmp(szFileName.Mid(nPos), szFileTitle, szFileTitle.GetLength()))
		{
			if (!_tcsnicmp(szFileName, szDrive, szDrive.GetLength()) && szDrive.GetLength() > 0)
			{
				szFilePath = (nPos > szDrive.GetLength()) ? szFileName.Left(nPos - 1) : EMPTYSTRING;
				break;
			}
			if (!_tcsnicmp(szFileName, szDrive, szDrive.GetLength() - 1) && szDrive.GetLength() > 0)
			{
				szFilePath = (nPos > szDrive.GetLength() - 1) ? szFileName.Left(nPos - 1) : EMPTYSTRING;
				break;
			}
			szFilePath = (nPos > 0 && cDrives.GetDriveDelimiter() == szFileName.GetAt(nPos - 1)) ? szFileName.Left(nPos - 1) : szFileName.Left(nPos);
			break;
		}
	}
	if (!szFilePath.IsEmpty())
	{
		if (cFileFind.FindFile(szFilePath))
		{
			cFileFind.Close();
			return TRUE;
		}
		return((SHCreateDirectoryEx((HWND)NULL, CFileEx::TranslateToUNCName(szFilePath), (LPSECURITY_ATTRIBUTES)NULL) == ERROR_SUCCESS) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CTMArchivesBackupThread::DelayBackup()
{
	CByteArray  nBackupData;
	CHistoryStoreFile  *pFile;
	CHistoryStoreFiles  pFiles;
	CProfile  cProfile;

	if (Wait(m_hSync, FALSE, INFINITE))
	{
		if ((pFile = new CHistoryStoreFile))
		{
			if (cProfile.GetTelemetryArchivesBackupInfo(nBackupData) && pFiles.Unmap(nBackupData))
			{
				for (pFile->Copy(&m_cFile), pFiles.InsertAt(pFiles.GetSize(), pFile, 1); pFiles.Map(nBackupData) && cProfile.SetTelemetryArchivesBackupInfo(nBackupData); )
				{
					ReleaseMutex(m_hSync);
					return TRUE;
				}
			}
			delete pFile;
		}
		ReleaseMutex(m_hSync);
	}
	return FALSE;
}

BOOL CTMArchivesBackupThread::Lock()
{
	HANDLE  hSyncObjects[2] = { m_bQuit,m_hSync };

	return((Wait(hSyncObjects, sizeof(hSyncObjects) / sizeof(HANDLE), FALSE, INFINITE) != WAIT_OBJECT_0 + 1) ? TRUE : FALSE);
}

BOOL CTMArchivesBackupThread::Unlock()
{
	return ReleaseMutex(m_hSync);
}

BEGIN_MESSAGE_MAP(CTMArchivesBackupThread, CThread)
	//{{AFX_MSG_MAP(CTMArchivesBackupThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMArchivesBackupThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTMProcessThread

IMPLEMENT_DYNCREATE(CTMProcessThread, CThread)

CTMProcessThread::CTMProcessThread() : CThread()
{
	m_pTMEnvironment = new CTMEnvironment;
	m_pTMProcessEngine = new CTMProcessEngine;
	m_nArchiveBufferTimerID = 0;
	m_bArchiveBufferFlash = FALSE;
	m_bDatabaseValidity = FALSE;
	m_hUpdate = (HANDLE)NULL;
	m_bUpdate = FALSE;
	m_bTestMode = FALSE;
}

CTMProcessThread::~CTMProcessThread()
{
	delete m_pTMEnvironment;
	delete m_pTMProcessEngine;
}

BOOL CTMProcessThread::InitInstance()
{
	InitializeJScriptTelemetryInterface(GetDatabase(), m_pTMEnvironment);
	InitializeJScriptTaskScheduler(m_cUpdate[1], m_cUpdate[2]);
	return TRUE;
}

int CTMProcessThread::ExitInstance()
{
	UninitializeJScriptTelemetryInterface();
	UninitializeJScriptTaskScheduler();
	return CThread::ExitInstance();
}

BOOL CTMProcessThread::Start(LPCTSTR pszName)
{
	if (m_pTMEnvironment->Create(GetDatabase()))
	{
		if (m_pTMProcessEngine->Open(GetDatabase(), pszName, m_pTMEnvironment))
		{
			if (CThread::CreateThread((LPVOID)NULL, THREAD_PRIORITY_ABOVE_NORMAL, TRUE))
			{
				ReportEvent((!Initialize()) ? SYSTEM_INFORMATIONAL_TELEMETRYSERVICE_INITIALIZATION_FAILURE : SYSTEM_NOERROR);
				ReportEvent((!GetMemoryDumpsService()->Start()) ? SYSTEM_INFORMATIONAL_MEMORYDUMPSSERVICE_NOT_AVAILABLE : SYSTEM_NOERROR, FALSE);
				ReportEvent((!GetPFLPService()->Start()) ? SYSTEM_INFORMATIONAL_PFLP_NOT_AVAILABLE : SYSTEM_NOERROR);
				ReportEvent((!GetTPEPService()->Start()) ? SYSTEM_INFORMATIONAL_TPEP_NOT_AVAILABLE : SYSTEM_NOERROR);
				ResumeThread();
				return TRUE;
			}
			m_pTMProcessEngine->Close();
		}
		m_pTMEnvironment->Destroy();
	}
	ReportEvent(SYSTEM_WARNING_TELEMETRYSERVICE_GENERAL_FAILURE);
	ReportEvent(SYSTEM_INFORMATIONAL_MEMORYDUMPSSERVICE_NOT_AVAILABLE, FALSE);
	ReportEvent(SYSTEM_INFORMATIONAL_PFLP_NOT_AVAILABLE);
	ReportEvent(SYSTEM_INFORMATIONAL_TPEP_NOT_AVAILABLE);
	return FALSE;
}

BOOL CTMProcessThread::Suspend()
{
	return m_cTMDevice.Suspend();
}

BOOL CTMProcessThread::IsSuspended() CONST
{
	return m_cTMDevice.IsSuspended();
}

BOOL CTMProcessThread::Resume()
{
	return m_cTMDevice.Resume();
}

VOID CTMProcessThread::Stop()
{
	for (DestroyThread(); m_nArchiveBufferTimerID != 0; )
	{
		KillTimer((HWND)NULL, m_nArchiveBufferTimerID);
		m_nArchiveBufferTimerID = 0;
		break;
	}
	GetMemoryDumpsService()->Stop();
	GetPFLPService()->Stop();
	GetTPEPService()->Stop();
	m_pTMProcessEngine->Close();
	m_pTMEnvironment->Destroy();
	Uninitialize();
}

BOOL CTMProcessThread::Update()
{
	return m_cUpdate[0].SetEvent();
}

INT CTMProcessThread::EnumTMSubSystems(CStringArray &szSubSystems, BOOL bAll) CONST
{
	return((m_pTMProcessEngine != (CTMProcessEngine *)NULL) ? m_pTMProcessEngine->EnumSubSystems(szSubSystems, bAll) : 0);
}

UINT CTMProcessThread::TranslateTMSubSystemToID(LPCTSTR pszSubSystem) CONST
{
	return((m_pTMProcessEngine != (CTMProcessEngine *)NULL) ? m_pTMProcessEngine->TranslateSubSystemToID(pszSubSystem) : -1);
}

CString CTMProcessThread::TranslateIDToTMSubSystem(UINT nSubSystemID) CONST
{
	return((m_pTMProcessEngine != (CTMProcessEngine *)NULL) ? m_pTMProcessEngine->TranslateIDToSubSystem(nSubSystemID) : EMPTYSTRING);
}

BOOL CTMProcessThread::SetTMProviderDevices(CONST CTMProviderDevices &pDevices)
{
	CTMProviderDevice  cDevice[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTMDevices.Copy(&pDevices))
	{
		for (m_pTMDevices.EnumDevices(), GetDevice(&cDevice[0]), m_pTMDevices.GetActiveDevice(&cDevice[1]); cDevice[0].GetDeviceBrand() == cDevice[1].GetDeviceBrand() && cDevice[0].GetDeviceName() == cDevice[1].GetDeviceName(); )
		{
			UpdateTelemetryStatus();
			break;
		}
		return Update();
	}
	return FALSE;
}

INT CTMProcessThread::GetTMProviderDevices(CTMProviderDevices &pDevices) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pDevices.Copy(&m_pTMDevices);
}

BOOL CTMProcessThread::HasTMProviderDevices(BOOL bSupported) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTMDevices.HasAvailableDevices(bSupported);
}

BOOL CTMProcessThread::SetActiveTMProviderDevice(CONST CTMProviderDevice *pDevice)
{
	CTMProviderDevice  cDevice;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTMDevices.SetActiveDevice(pDevice))
	{
		for (GetDevice(&cDevice); pDevice->GetDeviceBrand() == cDevice.GetDeviceBrand() && pDevice->GetDeviceName() == cDevice.GetDeviceName(); )
		{
			UpdateTelemetryStatus(pDevice);
			break;
		}
		return Update();
	}
	return FALSE;
}

BOOL CTMProcessThread::GetActiveTMProviderDevice(CTMProviderDevice *pDevice) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTMDevices.GetActiveDevice(pDevice);
}

BOOL CTMProcessThread::StopActiveTMProviderDevice(HANDLE hDevice)
{
	for (m_cUpdate[3].ResetEvent(), m_hUpdate = hDevice, m_bUpdate = TRUE; Update(); )
	{
		Wait(m_cUpdate[3], FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMProcessThread::InitializeTMHistoryStore(CONST CHistoryStoreOptions &pOptions)
{
	INT  nOption;
	INT  nOptions;
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	CTMUnit  *pTMUnit;
	CTimeSpan  tRetention;
	CTMParameter  *pTMParameter;
	CHistoryStoreOptionInfo  *pOptionInfo;

	if (m_pTMEnvironment->Lock())
	{
		for (nPacket = 0, nPackets = (INT)m_pTMEnvironment->GetTMUnitCache()->GetSize(), m_pTMEnvironment->GetTMUnitCache()->RemoveAllRetentions(), tRetention = ((pOptionInfo = pOptions.GetAt(pOptions.Find(HISTORYSTOREOPTION_TYPE_TMPACKET, EMPTYSTRING)))) ? pOptionInfo->GetRetention() : -1; nPacket < nPackets; nPacket++)
		{
			if ((pTMUnit = m_pTMEnvironment->GetTMUnitCache()->GetAt(nPacket)))
			{
				pTMUnit->SetRetention(tRetention);
				continue;
			}
		}
		for (nParameter = 0, nParameters = (INT)m_pTMEnvironment->GetTMParameters()->GetSize(), tRetention = ((pOptionInfo = pOptions.GetAt(pOptions.Find(HISTORYSTOREOPTION_TYPE_TMPARAMETER, EMPTYSTRING)))) ? pOptionInfo->GetRetention() : -1; nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter = m_pTMEnvironment->GetTMParameters()->GetAt(nParameter)))
			{
				pTMParameter->SetRetention(tRetention);
				continue;
			}
		}
		for (nOption = 0, nOptions = (INT)pOptions.GetSize(); nOption < nOptions; nOption++)
		{
			if ((pOptionInfo = pOptions.GetAt(nOption)) != (CHistoryStoreOptionInfo *)NULL)
			{
				if ((pOptionInfo->GetType() & HISTORYSTOREOPTION_TYPE_TMPACKET) == HISTORYSTOREOPTION_TYPE_TMPACKET)
				{
					for (m_pTMEnvironment->GetTMUnitCache()->SetRetention(pOptionInfo->GetTag(), pOptionInfo->GetRetention()); (pTMUnit = m_pTMEnvironment->GetTMUnitCache()->GetAt(m_pTMEnvironment->GetTMUnitCache()->Find(pOptionInfo->GetTag()))); )
					{
						pTMUnit->SetRetention(pOptionInfo->GetRetention());
						break;
					}
					continue;
				}
				if (pOptionInfo->GetType() & HISTORYSTOREOPTION_TYPE_TMPARAMETER)
				{
					if ((pTMParameter = m_pTMEnvironment->GetTMParameters()->GetAt(m_pTMEnvironment->GetTMParameters()->Find(pOptionInfo->GetTag()))))
					{
						pTMParameter->SetRetention(pOptionInfo->GetRetention());
						continue;
					}
				}
			}
		}
		m_pTMEnvironment->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CTMProcessThread::InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData)
{
	return m_pTMEnvironment->Initialize(cTMUnit, bBadData);
}
BOOL CTMProcessThread::InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData)
{
	return m_pTMEnvironment->Initialize(pszTag, cTMUnit, bBadData);
}

BOOL CTMProcessThread::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return m_pTMEnvironment->Initialize(pTMParameters, bBadData);
}
BOOL CTMProcessThread::InitializeTMData(COolParameters &pOolParameters, BOOL bBadData)
{
	return m_pTMEnvironment->Initialize(pOolParameters, bBadData);
}

BOOL CTMProcessThread::InitializeTMDump(CMemoryDump &pDump, BOOL bBadData)
{
	return m_pTMEnvironment->Initialize(pDump, bBadData);
}

BOOL CTMProcessThread::IsTMDump(CONST CTMEnvironment *pTMEnvironment) CONST
{
	return((m_pTMProcessEngine != (CTMProcessEngine *)NULL) ? m_pTMProcessEngine->IsTMDump(pTMEnvironment) : FALSE);
}

BOOL CTMProcessThread::UpdateTMDisplays(BOOL bProcessData)
{
	if (bProcessData) UpdateDisplays();
	return TRUE;
}

BOOL CTMProcessThread::UpdateTMParameters(CONST CTMParameters &pTMParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTMUnit  cTMUnit;
	CString  szTMUnit;
	CTimeTag  tTMUnit[2];
	CTMParameter  *pTMParameter;

	for (nParameter = 0, nParameters = (INT)pTMParameters.GetSize(), szTMUnit.Empty(), tTMUnit[0] = m_pTMEnvironment->GetTMUnit()->GetTimeTag(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = pTMParameters.GetAt(nParameter)) != (CTMParameter *)NULL)
		{
			if (pTMParameter->GetLastUpdateTMUnit() == STRING(IDS_TMUNIT_INTERACTIVE))
			{
				if (pTMParameter->GetLastUpdateTime() > tTMUnit[0])
				{
					szTMUnit = pTMParameter->GetLastUpdateTMUnit();
					tTMUnit[0] = pTMParameter->GetLastUpdateTime();
				}
			}
		}
	}
	for (cTMUnit.SetTag((szTMUnit = (szTMUnit.IsEmpty()) ? STRING(IDS_TMUNIT_INTERACTIVE) : szTMUnit)), cTMUnit.SetTimeTag((tTMUnit[0] == 0) ? tTMUnit[1] : tTMUnit[0]), m_pTMEnvironment->GetTMUnit()->Copy(&cTMUnit); !m_pTMEnvironment->GetTMUnit()->IsUnknown(); )
	{
		if (m_pTMEnvironment->Update(pTMParameters))
		{
			UpdateTCService();
			UpdateTMDisplays();
			UpdateTelemetryEvents();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTMProcessThread::ResetTMParameters()
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter[2];
	CTMParameters  pTMParameters;

	for (nParameter = 0, nParameters = (INT)m_pTMEnvironment->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter[1] = ((pTMParameter[0] = m_pTMEnvironment->GetTMParameters()->GetAt(nParameter)) && (pTMParameter[0]->GetAttributes() & (TMPARAMETER_NATURE_DERIVED | TMPARAMETER_NATURE_DERIVED_OL | TMPARAMETER_NATURE_DERIVED_SPEL | TMPARAMETER_NATURE_DERIVED_HARDCODED))) ? new CTMParameter : (CTMParameter *)NULL))
		{
			for (pTMParameter[1]->Copy(pTMParameter[0]), pTMParameter[1]->Reset(); pTMParameters.Add(pTMParameter[1]) < 0; )
			{
				delete pTMParameter[1];
				break;
			}
		}
	}
	return UpdateTMParameters(pTMParameters);
}

double CTMProcessThread::GetTotalTMBandwidth() CONST
{
	double  fTMBandwidth[2];
	CTMProcessInfo  *pTMProcessInfo;

	return(((pTMProcessInfo = m_pTMEnvironment->GetTMProcessInfo()) && pTMProcessInfo->GetTMBandwidth(fTMBandwidth[0], fTMBandwidth[1])) ? fTMBandwidth[0] : 0.0);
}

double CTMProcessThread::GetAvailableTMBandwidth() CONST
{
	double  fTMBandwidth[3];
	CTimeTag  tTMBandwidth;
	CTMProcessInfo  *pTMProcessInfo;

	return(((pTMProcessInfo = m_pTMEnvironment->GetTMProcessInfo()) && pTMProcessInfo->GetTMBandwidth(fTMBandwidth[0], fTMBandwidth[1]) && pTMProcessInfo->GetTMBandwidth(fTMBandwidth[2], tTMBandwidth)) ? (fTMBandwidth[0] - fTMBandwidth[2]) : -1.0);
}

double CTMProcessThread::GetMaxDiagnosticTMBandwidth() CONST
{
	double  fTMBandwidth[2];
	CTMProcessInfo  *pTMProcessInfo;

	return(((pTMProcessInfo = m_pTMEnvironment->GetTMProcessInfo()) && pTMProcessInfo->GetTMBandwidth(fTMBandwidth[0], fTMBandwidth[1])) ? fTMBandwidth[1] : 0.0);
}

double CTMProcessThread::GetAvailableDiagnosticTMBandwidth() CONST
{
	double  fTMBandwidth[3];
	CTimeTag  tTMBandwidth;
	CTMProcessInfo  *pTMProcessInfo;

	return(((pTMProcessInfo = m_pTMEnvironment->GetTMProcessInfo()) && pTMProcessInfo->GetTMBandwidth(fTMBandwidth[0], fTMBandwidth[1]) && pTMProcessInfo->GetTMBandwidth(fTMBandwidth[2], tTMBandwidth)) ? min(fTMBandwidth[0] - fTMBandwidth[2], fTMBandwidth[1]) : -1.0);
}

CTimeTag CTMProcessThread::GetLastTMBandwidthMeasurementTime() CONST
{
	double  fTMBandwidth;
	CTimeTag  tTMBandwidth;
	CTMProcessInfo  *pTMProcessInfo;

	return(((pTMProcessInfo = m_pTMEnvironment->GetTMProcessInfo()) && pTMProcessInfo->GetTMBandwidth(fTMBandwidth, tTMBandwidth)) ? tTMBandwidth : 0);
}

BOOL CTMProcessThread::UpdateTMStream()
{
	INT  nStream;
	INT  nStreams;
	UINT  nStatus;
	ULONGLONG  nValue;
	CTMPacket  *pTMPacket;
	CTMParameter  *pTMParameter;
	CDatabaseTMPacketStream  *pStream;

	if (m_pTMEnvironment->Lock())
	{
		if ((pTMPacket = (CTMPacket *)m_pTMEnvironment->GetTMUnit()) && pTMPacket->IsValid())
		{
			if (CheckTMStreamInterruption(pTMPacket->GetTimeTag().GetTime() - m_tTMStream.GetTime()))
			{
				m_tTMStreams.RemoveAll();
				m_bTMStreams.RemoveAll();
				m_tTMStream = 0;
			}
			for (nStream = 0, nStreams = (m_tTMStreams.GetSize() > 0) ? (INT)m_pTMStreams.GetSize() : 0; nStream < nStreams; nStream++)
			{
				if ((pStream = m_pTMStreams.GetAt(nStream)) && nStream < m_bTMStreams.GetSize() && !m_bTMStreams.GetAt(nStream) && m_tTMStreams.GetAt(nStream).GetTime() > 0 && m_tTMStreams.GetAt(nStream).GetTime() + 1000 * (pStream->GetPeriod() + pStream->GetTimeout()) < pTMPacket->GetTimeTag().GetTime())
				{
					if (((pTMParameter = m_pTMEnvironment->GetTMParameters()->GetAt(pStream->GetValidityParameterRef())) && pTMParameter->GetRawValue(0, nValue, nStatus) && nValue == pStream->GetValidityValue()) || pStream->GetValidityParameterRef() < 0)
					{
						Alert(pStream->GetName(), (DWORD)((pTMPacket->GetTimeTag().GetTime() - m_tTMStreams.GetAt(nStream).GetTime() - 1000 * (pStream->GetPeriod() + pStream->GetTimeout())) / 1000));
						m_bTMStreams.SetAtGrow(nStream, TRUE);
					}
				}
			}
			for (nStream = 0, nStreams = (INT)m_pTMStreams.GetSize(), m_tTMStream = max(pTMPacket->GetTimeTag(), m_tTMStream); nStream < nStreams; nStream++)
			{
				if ((pStream = m_pTMStreams.GetAt(nStream)) && pStream->GetAPID() == pTMPacket->GetAPID() && pStream->GetTMID() == pTMPacket->GetTMID())
				{
					m_tTMStreams.SetAtGrow(nStream, pTMPacket->GetTimeTag());
					m_bTMStreams.SetAtGrow(nStream, FALSE);
					break;
				}
			}
			if (nStream < nStreams)
			{
				m_pTMEnvironment->Unlock();
				return TRUE;
			}
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTMProcessThread::CheckTMStreamInterruption() CONST
{
	CTimeTag  tTime;

	if (m_pTMEnvironment->Lock())
	{
		if (CheckTMStreamInterruption(tTime.GetTime() - m_tTMStream.GetTime()))
		{
			m_pTMEnvironment->Unlock();
			return TRUE;
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}
BOOL CTMProcessThread::CheckTMStreamInterruption(TIMETAG tInterval) CONST
{
	return((m_pTMProcessEngine != (CTMProcessEngine *)NULL) ? m_pTMProcessEngine->CheckTMStreamInterruption(tInterval) : FALSE);
}

BOOL CTMProcessThread::CheckTMStreamCorrelation() CONST
{
	return((m_pTMProcessEngine != (CTMProcessEngine *)NULL) ? m_pTMProcessEngine->CheckTMStreamCorrelation(m_pTMEnvironment) : FALSE);
}

BOOL CTMProcessThread::TrackSystemAlerts()
{
	CSystemAlerts  pAlerts;

	return((GetSystemAlerts(pAlerts)) ? TrackSystemAlerts(pAlerts) : FALSE);
}
BOOL CTMProcessThread::TrackSystemAlerts(CONST CSystemAlerts &pAlerts)
{
	return TRUE;
}

BOOL CTMProcessThread::TrackTelemetryEvents()
{
	CTelemetryEvents  pEvents;

	return((GetTelemetryEvents(pEvents)) ? TrackTelemetryEvents(pEvents) : FALSE);
}
BOOL CTMProcessThread::TrackTelemetryEvents(CONST CTelemetryEvents &pEvents)
{
	INT  nEvent;
	INT  nEvents;
	INT  nSample;
	INT  nParameter;
	INT  nParameters;
	INT  nExpression;
	INT  nExpressions;
	BOOL  bSampleCoding;
	CString  szParameter;
	CUIntArray  nPastSamples;
	CStringArray  szParameters;
	CTelemetryEventInfo  *pEventInfo;
	CTelemetryEventExpression  *pEventExpression;

	for (nEvent = 0, nEvents = (INT)pEvents.GetSize(); nEvent < nEvents; nEvent++)
	{
		for (nExpression = 0, nExpressions = (pEventInfo = pEvents.GetAt(nEvent)) ? (INT)pEventInfo->GetSize() : 0; nExpression < nExpressions; nExpression++)
		{
			if ((pEventExpression = pEventInfo->GetAt(nExpression)) && pEventExpression->IsParameter() && pEventExpression->GetParameter(szParameter, nSample, bSampleCoding))
			{
				for (nParameter = 0, nParameters = (nSample < 0) ? (INT)szParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
				{
					if (!szParameters.GetAt(nParameter).Compare(szParameter) && nPastSamples.GetAt(nParameter) < (UINT)abs(nSample))
					{
						nPastSamples.SetAt(nParameter, abs(nSample));
						break;
					}
					if (!szParameters.GetAt(nParameter).Compare(szParameter)) break;
				}
				if (nParameter == nParameters)
				{
					szParameters.Add(szParameter);
					nPastSamples.Add(abs(nSample));
				}
			}
		}
	}
	return m_pTMEnvironment->Initialize(szParameters, nPastSamples);
}

BOOL CTMProcessThread::CheckTelemetryEvent(LPCTSTR pszEvent) CONST
{
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	return(((pEventInfo = (GetTelemetryEvents(pEvents)) ? pEvents.GetAt(pEvents.Find(pszEvent)) : (CTelemetryEventInfo *)NULL)) ? Evaluate(pEventInfo) : FALSE);
}

BOOL CTMProcessThread::EnableTestMode(BOOL bEnable)
{
	m_bTestMode = bEnable;
	m_bUpdate = TRUE;
	return Update();
}

BOOL CTMProcessThread::IsTestModeEnabled() CONST
{
	return m_bTestMode;
}

int CTMProcessThread::Run()
{
	INT  nError;
	INT  nErrors;
	INT  nDevice;
	INT  nDevices;
	INT  nReport;
	INT  nReports;
	INT  nProfile;
	INT  nProfiles;
	BOOL  bDevice;
	DWORD  dwResult;
	DWORD  dwTimeout;
	DWORD  dwCount;
	LPUINT  nIDs;
	HANDLE  hEvents[5];
	CTMUnit  cTMUnit;
	CString  szReport;
	CString  szProfile;
	LPCWSTR  *pszNames;
	TIMEKEY  *tScheduleTimes;
	TIMEKEY  *tStartTimes;
	TIMEKEY  *tStopTimes;
	TIMEKEY  *tIntervals;
	CTimeSpan  tPeriod;
	CByteArray  nData;
	CUIntArray  nReportIDs;
	CUIntArray  nProfileIDs;
	CStringArray  szErrors;
	CTMProviderDevice  cDevice;
	CTMProviderDevices  pDevices;
	CTelemetryReports  pReports[2];
	CTMTransferUnit  cTMTransferUnit;
	CTelemetryReportInfo  *pReportInfo[2];
	CArchivesExtractionProfiles  pProfiles[2];
	CArchivesExtractionProfileInfo  *pProfileInfo[2];

	for (hEvents[0] = m_cUpdate[0], hEvents[1] = m_cUpdate[1], hEvents[2] = m_cUpdate[2], hEvents[3] = hEvents[4] = (HANDLE)NULL, dwTimeout = 0; ((dwResult = Wait(hEvents, (dwCount = (m_cTMDevice.IsOpen()) ? (sizeof(hEvents) / sizeof(HANDLE)) : (sizeof(m_cUpdate) / sizeof(CEvent) - 1)), FALSE, dwTimeout)) > WAIT_OBJECT_0 && dwResult <= WAIT_OBJECT_0 + dwCount) || dwResult == WAIT_TIMEOUT; dwTimeout = (HasTMProviderDevices()) ? ((m_cTMDevice.GetStatusIndication() & IODEVICE_STATUS_CONNECTED) ? (1000 * (DWORD)(m_cTMDevice.IsStandBy(tPeriod)*tPeriod.GetTotalSeconds())) : 0) : INFINITE)
	{
		if (dwResult == WAIT_OBJECT_0 + 1 || dwResult == WAIT_TIMEOUT)
		{
			for (bDevice = FALSE; dwResult == WAIT_OBJECT_0 + 1; )
			{
				for (GetActiveTMProviderDevice(&cDevice); m_bUpdate; )
				{
					if (!IsTestModeEnabled() || !m_cTMDevice.Compare(&cDevice) || !m_cTMDevice.IsLocal())
					{
						for (StopDevice(); m_cUpdate[3].SetEvent() && m_hUpdate != (HANDLE)NULL; )
						{
							Wait(m_hUpdate, FALSE);
							break;
						}
						m_cTMDevice.SetStatusIndication((m_cTMDevice.GetStatusIndication() & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED)) | IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED);
						cDevice.SetStatusIndication((cDevice.GetStatusIndication() & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED)) | IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED);
						m_cTMDevice.SetStatus(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_NOTREADY));
						cDevice.SetStatus(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_NOTREADY));
						SetActiveTMProviderDevice(&cDevice);
						m_hUpdate = (HANDLE)NULL;
						m_bUpdate = FALSE;
					}
					break;
				}
				for (; !m_cTMDevice.Compare(&cDevice); )
				{
					if (m_cTMDevice.GetDeviceBrand().IsEmpty() || m_cTMDevice.GetDeviceName().IsEmpty())
					{
						SetDevice(&cDevice);
						bDevice = TRUE;
						break;
					}
					if (m_cTMDevice.IsOpen())
					{
						if (m_cTMDevice.IsLocal() || !IsTestModeEnabled())
						{
							if (m_cTMDevice.Update(&cDevice, bDevice) && !bDevice)
							{
								for (; !m_cTMDevice.Compare(&cDevice); )
								{
									SetDevice(&cDevice);
									break;
								}
								if (cDevice.IsStandBy())
								{
									UpdateTelemetryStatus(&cDevice);
									break;
								}
								bDevice = TRUE;
							}
						}
						StopDevice();
						break;
					}
					if (m_cTMDevice.Open())
					{
						if (m_cTMDevice.IsLocal() || !IsTestModeEnabled())
						{
							if (m_cTMDevice.Update(&cDevice, bDevice) && !bDevice)
							{
								for (; !m_cTMDevice.Compare(&cDevice); )
								{
									SetDevice(&cDevice);
									break;
								}
								if (!cDevice.IsStandBy())
								{
									m_cTMDevice.Close();
									break;
								}
								bDevice = TRUE;
							}
						}
						m_cTMDevice.Close();
					}
					break;
				}
				if (bDevice)
				{
					StartDevice();
					break;
				}
				break;
			}
			for (; dwResult == WAIT_TIMEOUT; )
			{
				if (StartDevice())
				{
					bDevice = TRUE;
					break;
				}
				for (nDevice = 0, nDevices = m_pTMDevices.EnumBackupDevices(&m_cTMDevice, pDevices), GetDevice(&cDevice); (dwResult = Wait(m_cUpdate, sizeof(m_cUpdate) / sizeof(CEvent) - 1, FALSE, TMPROCESSTHREAD_DEVICE_TIMEOUT, FALSE)) == WAIT_TIMEOUT && nDevice < nDevices; nDevice++)
				{
					if (StartDevice(pDevices.GetAt(nDevice)))
					{
						bDevice = TRUE;
						break;
					}
				}
				if (!bDevice)
				{
					if (dwResult == WAIT_OBJECT_0 + 1)
					{
						Update();
						break;
					}
					if (dwResult == WAIT_TIMEOUT)
					{
						SetDevice(&cDevice);
						break;
					}
				}
				break;
			}
			if (bDevice)
			{
				for (Lock(); m_cTMDevice.MonitorDeviceDataBuffers(hEvents[3], hEvents[4]); )
				{
					SetActiveTMProviderDevice(&m_cTMDevice);
					break;
				}
				Unlock();
			}
			if (dwResult == WAIT_TIMEOUT) continue;
		}
		if (dwResult == WAIT_OBJECT_0 + sizeof(hEvents) / sizeof(HANDLE))
		{
			if (m_cTMDevice.Receive(nData))
			{
				Update(nData);
				continue;
			}
			if (m_cTMDevice.Receive(cTMUnit))
			{
				Update(cTMUnit);
				continue;
			}
			if (m_cTMDevice.Receive(cTMTransferUnit))
			{
				Update(cTMTransferUnit);
				continue;
			}
		}
		if (dwResult == WAIT_OBJECT_0 + (dwCount = sizeof(m_cUpdate) / sizeof(CEvent) - 1))
		{
			for (nProfile = 0, nProfiles = (GetTMService()->GetTMHistoryFileExtractionProfiles(pProfiles[0])) ? EnumJScriptTaskSchedulerTelemetryDataExtractions(&(pszNames = NULL), &(nIDs = NULL), &(tScheduleTimes = NULL), &(tStartTimes = NULL), &(tStopTimes = NULL)) : -1, szErrors.RemoveAll(); nProfile < nProfiles; nProfile++)
			{
#ifndef UNICODE
				WideCharToMultiByte(CP_ACP, 0, pszNames[nProfile], -1, szProfile.GetBufferSetLength((INT)wcslen(pszNames[nProfile])), (INT)(wcslen(pszNames[nProfile]) + 1), (LPCSTR)NULL, (LPBOOL)NULL);
				szProfile.ReleaseBuffer();
#else
				szProfile = pszNames[nProfile];
#endif
				if ((pProfileInfo[0] = pProfiles[0].GetAt(pProfiles[0].Find(szProfile))))
				{
					if ((pProfileInfo[1] = new CArchivesExtractionProfileInfo))
					{
						pProfileInfo[1]->Copy(pProfileInfo[0]);
						pProfileInfo[1]->SetTimeRangeMode(ARCHIVESEXTRACTIONINFO_RANGE_NORMAL);
						pProfileInfo[1]->SetTimeRange(tStartTimes[nProfile], tStopTimes[nProfile]);
						pProfileInfo[1]->SetExecutionMode(ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT);
						pProfileInfo[1]->SetExecutionTime(tScheduleTimes[nProfile]);
						pProfiles[1].InsertAt(pProfiles[1].GetSize(), pProfileInfo[1], 1);
						nProfileIDs.InsertAt(nProfileIDs.GetSize(), nIDs[nProfile], 1);
						delete[] pszNames[nProfile];
						continue;
					}
				}
				for (nError = 0, nErrors = (INT)szErrors.GetSize(); nError < nErrors; nError++)
				{
					if (szErrors.GetAt(nError) == szProfile) break;
					continue;
				}
				for (DeleteJScriptTaskSchedulerTelemetryDataExtraction(nIDs[nProfile]); nError == nErrors; )
				{
					szErrors.Add(szProfile);
					break;
				}
				delete[] pszNames[nProfile];
			}
			for (; pProfiles[1].GetSize() >= 0; )
			{
				GetTMService()->UpdateTMHistoryFileExtractions(pProfiles[1], nProfileIDs, szErrors);
				break;
			}
			delete nIDs;
			delete pszNames;
			delete tScheduleTimes;
			delete tStartTimes;
			delete tStopTimes;
			pProfiles[0].RemoveAll();
			pProfiles[1].RemoveAll();
			nProfileIDs.RemoveAll();
			continue;
		}
		if (dwResult == WAIT_OBJECT_0 + dwCount - 1)
		{
			for (nReport = 0, nReports = (GetTelemetryReports(pReports[0])) ? EnumJScriptTaskSchedulerTelemetryReports(&(pszNames = NULL), &(nIDs = NULL), &(tStartTimes = NULL), &(tIntervals = NULL), &(tStopTimes = NULL)) : -1, nReportIDs.RemoveAll(), szErrors.RemoveAll(); nReport < nReports; nReport++)
			{
#ifndef UNICODE
				WideCharToMultiByte(CP_ACP, 0, pszNames[nReport], -1, szReport.GetBufferSetLength((INT)wcslen(pszNames[nReport])), (INT)(wcslen(pszNames[nReport]) + 1), (LPCSTR)NULL, (LPBOOL)NULL);
				szReport.ReleaseBuffer();
#else
				szReport = pszNames[nReport];
#endif
				if ((pReportInfo[0] = pReports[0].GetAt(pReports[0].Find(szReport))))
				{
					if ((pReportInfo[1] = new CTelemetryReportInfo))
					{
						pReportInfo[1]->Copy(pReportInfo[0]);
						pReportInfo[1]->SetScheduledPeriod(tStartTimes[nReport], tStopTimes[nReport], tIntervals[nReport]);
						pReports[1].InsertAt(pReports[1].GetSize(), pReportInfo[1], 1);
						nReportIDs.InsertAt(nReportIDs.GetSize(), nIDs[nReport], 1);
						delete[] pszNames[nReport];
						continue;
					}
				}
				for (nError = 0, nErrors = (INT)szErrors.GetSize(); nError < nErrors; nError++)
				{
					if (szErrors.GetAt(nError) == szReport) break;
					continue;
				}
				for (DeleteJScriptTaskSchedulerTelemetryReport(nIDs[nReport]); nError == nErrors; )
				{
					szErrors.Add(szReport);
					break;
				}
				delete[] pszNames[nReport];
			}
			for (; pReports[1].GetSize() >= 0; )
			{
				GetTelemetryReportsService()->Update(pReports[1], nReportIDs, szErrors);
				break;
			}
			delete nIDs;
			delete pszNames;
			delete tStartTimes;
			delete tStopTimes;
			delete tIntervals;
			pReports[0].RemoveAll();
			pReports[1].RemoveAll();
			nReportIDs.RemoveAll();
			continue;
		}
	}
	StopDevice();
	return ExitInstance();
}

BOOL CTMProcessThread::Initialize()
{
	INT  nFile;
	INT  nFiles;
	INT  nIndex;
	INT  nCount;
	UINT  nResult;
	CTimeKey  tTimeKey;
	CByteArray  nBackupData;
	CHistoryStoreFile  *pFile;
	CHistoryStoreFiles  pFiles;
	CHistoryTMProcessEngine  cTMProcessEngine;
	CHistoryStoreOptions  pOptions;
	CHistoryStoreFile  cFile;
	CProfile  cProfile;

	for (nFile = 0, nFiles = (cProfile.GetTelemetryArchivesBackupInfo(nBackupData) && pFiles.Unmap(nBackupData)) ? (INT)pFiles.GetSize() : 0; nFile < nFiles; nFile++)
	{
		if ((pFile = pFiles.GetAt(nFile)) && !DoBackup(pFile)) continue;
		pFiles.RemoveAt(nFile);
		delete pFile;
		nFiles--;
		nFile--;
	}
	for (GetTCService()->Initialize(m_pTMEnvironment), TrackSystemAlerts(), TrackTelemetryEvents(), m_pTMDevices.EnumDevices(), m_pTMStreams.Copy(GetDatabase()->GetTMPacketStreams()), m_tTMStream = 0, m_tTMStreams.RemoveAll(), m_bTMStreams.RemoveAll(), nBackupData.SetSize((pFiles.Map(nBackupData)) ? nBackupData.GetSize() : 0); nBackupData.GetSize() >= 0; )
	{
		cProfile.SetTelemetryArchivesBackupInfo(nBackupData);
		break;
	}
	if (GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile))
	{
		if (cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), cFile.GetFileName(), m_pTMEnvironment))
		{
			if ((nResult = cTMProcessEngine.ProcessTMData(GetDatabase(), m_pTMEnvironment, tTimeKey) & HISTORYFILE_SUCCESS))
			{
				for (ShowMessage(IDS_STATUSBAR_INITIALIZING_PARAMETERS), ReportMessage(IDS_STATUSBAR_INITIALIZING_PARAMETERS), nIndex = 0, nCount = cFile.GetUpdateInterval(); (nResult = cTMProcessEngine.ReplayTMData(GetDatabase(), m_pTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS; nIndex++)
				{
					if (((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) && (nIndex <= 2 * nCount || !nCount))
					{
						ShowProgress((nCount > 0) ? ((100 * (nIndex%nCount)) / nCount) : 0);
						continue;
					}
					m_pTMEnvironment->GetTMUnit()->Reset();
					break;
				}
				if (nResult & HISTORYFILE_SUCCESS)
				{
					for (cTMProcessEngine.SetTimeCorrelation(m_pTMEnvironment); GetTMService()->GetTMHistoryFilesOptions(pOptions); )
					{
						InitializeTMHistoryStore(pOptions);
						break;
					}
					for (ShowProgress(100); GetDisplayArea()->InitializeDisplays(m_pTMEnvironment); )
					{
						UpdateDisplays();
						break;
					}
					return((nIndex <= 2 * nCount || !nCount) ? TRUE : FALSE);
				}
				ShowProgress(100);
			}
		}
	}
	for (cTMProcessEngine.SetTimeCorrelation(m_pTMEnvironment); GetTMService()->GetTMHistoryFilesOptions(pOptions); )
	{
		InitializeTMHistoryStore(pOptions);
		break;
	}
	if (GetDisplayArea()->InitializeDisplays(m_pTMEnvironment)) UpdateDisplays();
	return FALSE;
}

BOOL CTMProcessThread::Uninitialize()
{
	return TRUE;
}

BOOL CTMProcessThread::SetDevice(CONST CTMProviderDevice *pDevice)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_cTMDevice.Copy(pDevice);
}

BOOL CTMProcessThread::GetDevice(CTMProviderDevice *pDevice) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pDevice->Copy(&m_cTMDevice);
}

BOOL CTMProcessThread::StartDevice(CTMProviderDevice *pDevice)
{
	CString  szMessage;
	CTMProviderDevice  cDevice;

	for (StopDevice(); SetDevice(pDevice) && StartDevice(); )
	{
		if (pDevice->GetBackupOptions() & TELEMETRYPROVIDERDEVICE_BACKUP_RETRIES)
		{
			m_cTMDevice.SetBackupRetryCount(0);
			pDevice->SetBackupRetryCount(0);
		}
		for (GetActiveTMProviderDevice(&cDevice); (pDevice->GetDeviceBrand() != cDevice.GetDeviceBrand() || pDevice->GetDeviceName() != cDevice.GetDeviceName()) && (cDevice.GetBackupOptions() & TELEMETRYPROVIDERDEVICE_BACKUP_AUDITFAILURES); )
		{
			szMessage.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_BACKUPMESSAGE_FAILURE), (LPCTSTR)cDevice.GetDeviceName(), (LPCTSTR)pDevice->GetDeviceName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			break;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTMProcessThread::StartDevice()
{
	UINT  nRetry;
	UINT  nRetries;
	CString  szMessage;

	for (StopDevice(); m_cTMDevice.Open(); )
	{
		if (m_cTMDevice.IsLocal() || !IsTestModeEnabled())
		{
			if (m_cTMDevice.IsStandBy())
			{
				if (!GetRASService()->IsCalling())
				{
					if (m_cTMDevice.Initialize((m_cTMDevice.GetCapabilities() & ~(IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TC | ((m_pTMProcessEngine->DetectTMServiceLevel() == TMSERVICELEVEL_TRANSFERFRAMES) ? (IODEVICE_DATASERVICE_RAW | IODEVICE_DATASERVICE_SOURCEPACKETS) : (IODEVICE_DATASERVICE_RAW | IODEVICE_DATASERVICE_TRANSFERFRAMES)))) | IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TM | ((m_pTMProcessEngine->DetectTMServiceLevel() == TMSERVICELEVEL_TRANSFERFRAMES) ? IODEVICE_DATASERVICE_TRANSFERFRAMES : IODEVICE_DATASERVICE_SOURCEPACKETS), 2 * m_pTMProcessEngine->GetTMStreamInterruptionInterval().GetTotalSeconds(), m_pTMProcessEngine->GetTMStreamDelayInterval()) && m_cTMDevice.Start())
					{
						for (m_cTMDevice.SetStatusIndication((m_cTMDevice.GetStatusIndication() & ~(IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_OFFLINE)) | (IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_ONLINE)); m_cTMDevice.GetStatus() == STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_NOTREADY) || m_cTMDevice.GetStatus() == STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_OFFLINE) || m_cTMDevice.GetStatus() == STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_DISABLED); )
						{
							m_cTMDevice.SetStatusIndication((m_cTMDevice.GetStatusIndication() | IODEVICE_STATUS_WARNING) & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_ERROR));
							m_cTMDevice.SetStatus(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_READY));
							break;
						}
						return TRUE;
					}
					if ((m_cTMDevice.GetStatusIndication() & IODEVICE_STATUS_ONLINE) != IODEVICE_STATUS_ONLINE)
					{
						if ((m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS) != TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS && (m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED) != TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED && (m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_AUDIT))
						{
							szMessage.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_SCHEDULEMESSAGE_ACTIVE), (LPCTSTR)m_cTMDevice.GetDeviceName());
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
						}
					}
					if (m_cTMDevice.GetBackupOptions() & TELEMETRYPROVIDERDEVICE_BACKUP_RETRIES)
					{
						for (m_cTMDevice.GetBackupRetryCount(nRetry), m_cTMDevice.GetBackupRetries(nRetries); nRetry <= nRetries; )
						{
							for (m_cTMDevice.SetBackupRetryCount(nRetry + 1); (m_cTMDevice.GetBackupOptions() & TELEMETRYPROVIDERDEVICE_BACKUP_AUDITFAILURES) && nRetry == nRetries; )
							{
								szMessage.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_BACKUPMESSAGE_RETRIES), (LPCTSTR)m_cTMDevice.GetDeviceName(), nRetries);
								ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
								break;
							}
							break;
						}
					}
					m_cTMDevice.SetStatusIndication((m_cTMDevice.GetStatusIndication() & ~(IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_OFFLINE)) | (IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_ONLINE));
					m_cTMDevice.SetStatus(STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_NOTREADY));
				}
			}
			else
			{
				if ((m_cTMDevice.GetStatusIndication() & IODEVICE_STATUS_ONLINE) || (m_cTMDevice.GetStatusIndication() & (IODEVICE_STATUS_ONLINE | IODEVICE_STATUS_OFFLINE)) == 0)
				{
					if ((m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS) != TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS && (m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED) != TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED && (m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_AUDIT))
					{
						szMessage.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_SCHEDULEMESSAGE_INACTIVE), (LPCTSTR)m_cTMDevice.GetDeviceName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					}
				}
				m_cTMDevice.SetStatusIndication((m_cTMDevice.GetStatusIndication() & ~(IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_ONLINE)) | (IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_OFFLINE));
				m_cTMDevice.SetStatus((m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED) ? STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_DISABLED) : STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_OFFLINE));
			}
		}
		m_cTMDevice.Close();
		break;
	}
	return FALSE;
}

VOID CTMProcessThread::StopDevice()
{
	CString  szMessage;

	if (!m_cTMDevice.IsStandBy())
	{
		if (m_cTMDevice.GetStatusIndication() & IODEVICE_STATUS_ONLINE)
		{
			if ((m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS) != TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS && (m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED) != TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED && (m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_AUDIT))
			{
				szMessage.Format(STRING(IDS_TELEMETRYPROVIDERDEVICE_SCHEDULEMESSAGE_INACTIVE), (LPCTSTR)m_cTMDevice.GetDeviceName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			}
		}
		m_cTMDevice.SetStatusIndication((m_cTMDevice.GetStatusIndication() & ~(IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_ONLINE)) | (IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_OFFLINE));
		m_cTMDevice.SetStatus((m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS) ? STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_NOTREADY) : ((m_cTMDevice.GetScheduleOptions() & TELEMETRYPROVIDERDEVICE_SCHEDULE_DISABLED) ? STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_DISABLED) : STRING(IDS_TELEMETRYPROVIDERDEVICE_STATUS_OFFLINE)));
	}
	m_cTMDevice.Close();
}

VOID CTMProcessThread::UpdateDisplays()
{
	GetDisplayArea()->UpdateDisplays(m_pTMEnvironment);
}

VOID CTMProcessThread::UpdateArchives()
{
	INT  nFile;
	INT  nFiles;
	UINT  nResult;
	BOOL  bBuffering;
	CString  szError;
	CUIntArray  nErrors;
	CHistoryStoreFile  *pFile;
	CHistoryStoreFiles  pFiles;

	for (nFile = 0, nFiles = (!m_bArchiveBufferFlash) ? GetTMService()->UpdateTMHistoryFiles(m_pTMEnvironment, pFiles, nErrors) : GetTMService()->UpdateTMHistoryFiles(pFiles, nErrors), m_nArchiveBufferTimerID *= (m_nArchiveBufferTimerID > 0) ? !KillTimer((HWND)NULL, m_nArchiveBufferTimerID) : 0, bBuffering = FALSE; nFile < nFiles; nFile++)
	{
		if ((pFile = pFiles.GetAt(nFile)) != (CHistoryStoreFile *)NULL)
		{
			if (HIWORD((nResult = nErrors.GetAt(nFile))) & HISTORYSTORE_BACKUP)
			{
				if (!DoBackup(pFile, FALSE) && (pFile->GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES))
				{
					szError.Format(STRING(IDS_TELEMETRYARCHIVES_BACKUP_FAILURE), (LPCTSTR)pFile->GetFileName());
					ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
				}
				continue;
			}
			if (LOWORD(nResult) & HISTORYSTORE_FILEOPEN_FAILURE)
			{
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_FILEOPEN_FAILURE), (LPCTSTR)pFile->GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
				Alert(pFile->GetFileName());
			}
			if (LOWORD(nResult) & HISTORYSTORE_FILEUPDATE_FAILURE)
			{
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_FILEUPDATE_FAILURE), (LPCTSTR)pFile->GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
				Alert(pFile->GetFileName());
			}
			if (LOWORD(nResult) & HISTORYSTORE_FILECLOSE_FAILURE)
			{
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_FILECLOSE_FAILURE), (LPCTSTR)pFile->GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
				Alert(pFile->GetFileName());
			}
			if (LOWORD(nResult) & HISTORYSTORE_SECONDARY_FAILURE)
			{
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_SECONDARY_FAILURE), (LPCTSTR)pFile->GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
				Alert(pFile->GetFileName());
			}
			if (HIWORD(nResult) & HISTORYSTORE_SECONDARY_USE)
			{
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_SECONDARY_USE), (LPCTSTR)pFile->GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError, FALSE);
			}
			if (HIWORD(nResult) & HISTORYSTORE_DATA_LOST)
			{
				szError.Format(STRING(IDS_TELEMETRYARCHIVES_DATA_LOST), (LPCTSTR)pFile->GetFileName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError, FALSE);
			}
			bBuffering = (HIWORD(nResult) & HISTORYSTORE_DATA_BUFFERED) ? TRUE : bBuffering;
		}
	}
	for (; pFiles.GetSize() > 0; )
	{
		if (!m_nArchiveBufferTimerID  &&  bBuffering)
		{
			m_nArchiveBufferTimerID = SetTimer((HWND)NULL, TMPROCESSTHREAD_ARCHIVES_TIMERID, TMPROCESSTHREAD_ARCHIVES_TIMEOUT, NULL);
			break;
		}
		if (m_nArchiveBufferTimerID > 0 && !bBuffering)
		{
			KillTimer((HWND)NULL, m_nArchiveBufferTimerID);
			m_nArchiveBufferTimerID = 0;
		}
		break;
	}
	UpdateArchivingStatus();
}

VOID CTMProcessThread::UpdateTCService()
{
	GetTCService()->Update(m_pTMProcessEngine, m_pTMEnvironment);
}

VOID CTMProcessThread::UpdateOolAlerts()
{
	INT  nParameter;
	INT  nParameters;
	CString  szMessage;
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	COolParameter  *pOolParameter;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	for (nParameter = 0, nParameters = (INT)m_pTMEnvironment->GetOolParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter = m_pTMEnvironment->GetOolParameters()->GetAt(nParameter)) && (pOolParameter->GetOolFlags() & (TMPARAMETER_OOLFLAG_EVENT | TMPARAMETER_OOLFLAG_NOEVENT)))
		{
			if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? pAlertList.GetAt(pAlertList.Find((pOolParameter->GetOolFlags() & TMPARAMETER_OOLFLAG_EVENT) ? STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_OOL_APPEARANCE) : STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_OOL_DISAPPEARANCE))) : (CSystemAlertInfo *)NULL))
			{
				for (szMessage.Format((pOolParameter->GetOolFlags() & TMPARAMETER_OOLFLAG_EVENT) ? STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_OOL_APPEARANCE) : STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_OOL_DISAPPEARANCE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)pOolParameter->GetTag()); (pAlertInfo[1] = new CSystemAlertInfo); )
				{
					pAlertInfo[1]->Copy(pAlertInfo[0]);
					pAlertInfo[1]->SetCategory(EVENT_CATEGORY_SPACECRAFT);
					pAlertInfo[1]->SetType(EVENT_TYPE_INFORMATIONAL);
					pAlertInfo[1]->SetMessage(szMessage);
					pAlertInfo[1]->SetExtraInfo(pOolParameter->GetTag());
					ReportEvent(pAlertInfo[1]);
					delete pAlertInfo[1];
					break;
				}
			}
		}
	}
}

VOID CTMProcessThread::UpdateTelemetryEvents()
{
	INT  nEvent;
	INT  nEvents;
	INT  nExpression;
	INT  nExpressions;
	INT  nSample;
	UINT  nCount;
	UINT  nStatus;
	BOOL  bCoding;
	CString  szParameter;
	CTimeTag  tParameter;
	ULONGLONG  nValue;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;
	CTelemetryEventExpression  *pExpression;
	CTMParameter  *pTMParameter;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		for (nExpression = 0, nExpressions = ((pEventInfo = pEvents.GetAt(nEvent))) ? (INT)pEventInfo->GetSize() : 0, tParameter = 0, nCount = 0; nExpression < nExpressions; nExpression++)
		{
			if ((pTMParameter = ((pExpression = pEventInfo->GetAt(nExpression)) && pExpression->GetParameter(szParameter, nSample, bCoding)) ? m_pTMEnvironment->GetTMParameters()->GetAt(m_pTMEnvironment->GetTMParameters()->Find(pExpression->GetParameter())) : (CTMParameter *)NULL))
			{
				if (pTMParameter->GetRawValue(nSample, nValue, nStatus) && ((nStatus & TMPARAMETER_STATUS_VALID) || pEventInfo->IsInvalidDataModeEnabled()) && ((nStatus & TMPARAMETER_STATUS_GOOD) || pEventInfo->IsBadDataModeEnabled()))
				{
					for (; m_pTMEnvironment->GetTMUnit()->GetTag() == pTMParameter->GetLastUpdateTMUnit() && m_pTMEnvironment->GetTMUnit()->GetTimeTag() == pTMParameter->GetLastUpdateTime(); )
					{
						tParameter = (pTMParameter->GetLastUpdateTime() > tParameter) ? pTMParameter->GetLastUpdateTime() : tParameter;
						break;
					}
					nCount++;
					continue;
				}
				break;
			}
		}
		if (nExpression == nExpressions)
		{
			if (tParameter > 0 || !nCount)
			{
				pEventInfo->SetTime(tParameter);
				Alert(pEventInfo);
			}
		}
	}
}

VOID CTMProcessThread::UpdateMemoryDumps()
{
	GetMemoryDumpsService()->Update(m_pTMEnvironment);
}

VOID CTMProcessThread::UpdatePFLPClients()
{
	GetPFLPService()->Update(m_pTMEnvironment);
}

VOID CTMProcessThread::UpdateTPEPClients()
{
	GetTPEPService()->Update(m_pTMEnvironment);
}

VOID CTMProcessThread::UpdateOOBData()
{
	INT  nIndex;
	INT  nCount;
	CTMUnit  cTMUnit;
	CTMUnits  pTMUnits;

	for (nIndex = 0, nCount = (pTMUnits.Copy(m_pTMEnvironment->GetTMUnits())) ? (INT)pTMUnits.GetSize() : 0, m_pTMEnvironment->GetTMUnits()->RemoveAll(); nIndex < nCount; nIndex++)
	{
		m_pTMEnvironment->GetTMUnit()->Copy(pTMUnits.GetAt(nIndex));
		cTMUnit.Copy(pTMUnits.GetAt(nIndex));
		Update(cTMUnit);
	}
}

VOID CTMProcessThread::Update(CONST CByteArray &nData)
{
	return;
}
VOID CTMProcessThread::Update(CONST CTMUnit &cTMUnit)
{
	INT  nResult;
	BOOL  bValidity;

	for (bValidity = m_bDatabaseValidity; !(m_bDatabaseValidity = CheckDatabaseValidity(cTMUnit)); )
	{
		ReportEvent((bValidity) ? SYSTEM_WARNING_DATABASE_VALIDITY_FAILURE : SYSTEM_NOERROR);
		return;
	}
	if ((nResult = m_pTMProcessEngine->ProcessTMUnit(GetDatabase(), &cTMUnit, m_pTMEnvironment)) == TMPROCESSENGINE_DATA_PACKET)
	{
		UpdateDisplays();
		UpdateArchives();
		UpdateTCService();
		UpdateOolAlerts();
		UpdateTelemetryEvents();
		UpdateMemoryDumps();
		UpdatePFLPClients();
		UpdateTPEPClients();
		UpdateTMStream();
		return;
	}
	if (nResult == TMPROCESSENGINE_DATA_OOB)
	{
		UpdateOOBData();
		return;
	}
	if (nResult != TMPROCESSENGINE_DATA_NONE)
	{
		if (m_pTMEnvironment->GetTMUnit()->IsValid())
		{
			if (!m_pTMEnvironment->GetTMUnit()->IsUnknown())
			{
				UpdateDisplays();
				UpdateTCService();
				UpdateOolAlerts();
				UpdateTelemetryEvents();
				UpdateMemoryDumps();
				UpdatePFLPClients();
				UpdateTPEPClients();
			}
			UpdateArchives();
		}
		ReportEvent(SPACECRAFT_ERROR_TM_PACKET_DECODE_FAILURE);
	}
}
VOID CTMProcessThread::Update(CONST CTMTransferUnit &cTMTransferUnit)
{
	INT  nResult;
	BOOL  bValidity;

	for (bValidity = m_bDatabaseValidity; !(m_bDatabaseValidity = CheckDatabaseValidity(cTMTransferUnit)); )
	{
		ReportEvent((bValidity) ? SYSTEM_WARNING_DATABASE_VALIDITY_FAILURE : SYSTEM_NOERROR);
		return;
	}
	if ((nResult = m_pTMProcessEngine->ProcessTMTransferUnit(GetDatabase(), &cTMTransferUnit, m_pTMEnvironment)) == TMPROCESSENGINE_DATA_PACKET)
	{
		UpdateDisplays();
		UpdateArchives();
		UpdateTCService();
		UpdateOolAlerts();
		UpdateTelemetryEvents();
		UpdateMemoryDumps();
		UpdatePFLPClients();
		UpdateTPEPClients();
		UpdateTMStream();
		return;
	}
	if (nResult == TMPROCESSENGINE_DATA_OOB)
	{
		UpdateOOBData();
		return;
	}
	if (nResult != TMPROCESSENGINE_DATA_NONE)
	{
		if (m_pTMEnvironment->GetTMUnit()->IsValid())
		{
			if (!m_pTMEnvironment->GetTMUnit()->IsUnknown())
			{
				UpdateDisplays();
				UpdateTCService();
				UpdateOolAlerts();
				UpdateTelemetryEvents();
				UpdateMemoryDumps();
				UpdatePFLPClients();
				UpdateTPEPClients();
			}
			UpdateArchives();
		}
		ReportEvent(SPACECRAFT_ERROR_TM_TRANSFERFRAME_DECODE_FAILURE);
	}
}

VOID CTMProcessThread::Alert(LPCTSTR pszFileName)
{
	CString  szMessage;
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
	{
		if ((pAlertInfo[1] = pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_DATA_ARCHIVING_FAILURE)))))
		{
			szMessage.Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DATA_ARCHIVING_FAILURE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), pszFileName);
			szMessage = (pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_DATA_ARCHIVING_FAILURE)) ? pAlertInfo[1]->GetMessage() : szMessage;
			pAlertInfo[0]->Copy(pAlertInfo[1]);
			pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
			pAlertInfo[0]->SetType(EVENT_TYPE_WARNING);
			pAlertInfo[0]->SetMessage(szMessage);
			pAlertInfo[0]->SetExtraInfo(pszFileName);
			ReportEvent(pAlertInfo[0]);
		}
		delete pAlertInfo[0];
	}
}
VOID CTMProcessThread::Alert(LPCTSTR pszStreamName, DWORD dwTimeout)
{
	CString  szMessage;
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
	{
		if ((pAlertInfo[1] = pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_TELEMETRY_STREAM_TIMEOUT)))))
		{
			szMessage.Format(STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_STREAM_TIMEOUT), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), dwTimeout, pszStreamName);
			szMessage = (pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_TELEMETRY_STREAM_TIMEOUT)) ? pAlertInfo[1]->GetMessage() : szMessage;
			pAlertInfo[0]->Copy(pAlertInfo[1]);
			pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SPACECRAFT);
			pAlertInfo[0]->SetType(EVENT_TYPE_WARNING);
			pAlertInfo[0]->SetMessage(szMessage);
			ReportEvent(pAlertInfo[0]);
		}
		delete pAlertInfo[0];
	}
}
VOID CTMProcessThread::Alert(CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nAlert;
	INT  nAlerts;

	if (Evaluate(pEventInfo))
	{
		for (nAlert = 0, nAlerts = (!pEventInfo->IsDisabledDataModeEnabled()) ? (INT)m_szAlerts.GetSize() : -1; nAlert < nAlerts; nAlert++)
		{
			if (m_szAlerts.GetAt(nAlert) == pEventInfo->GetName()) break;
			continue;
		}
		if (nAlert == nAlerts)
		{
			ReportEvent(pEventInfo);
			DoPrintouts(pEventInfo);
			DoDownloads(pEventInfo);
			DoHistoryFileExtractions(pEventInfo);
			DoHistoricalTelemetryReports(pEventInfo);
			DoUpdateTelecommandSources(pEventInfo);
			m_szAlerts.Add(pEventInfo->GetName());
		}
		return;
	}
	for (nAlert = 0, nAlerts = (INT)m_szAlerts.GetSize(); nAlert < nAlerts; nAlert++)
	{
		if (m_szAlerts.GetAt(nAlert) == pEventInfo->GetName())
		{
			m_szAlerts.RemoveAt(nAlert);
			break;
		}
	}
}

BOOL CTMProcessThread::Evaluate(CONST CTelemetryEventInfo *pEventInfo) CONST
{
	INT  nIndex;
	INT  nExpression;
	INT  nExpressions;
	INT  nSample;
	UINT  nStatus;
	BOOL  bCoding;
	double  fValue;
	double  *pExpressions;
	CString  szParameter;
	ULONGLONG  nValue;
	CTelemetryEventExpression  *pExpression;
	CTMParameter  *pTMParameter;

	if ((pExpressions = (double *)GlobalAlloc(GPTR, pEventInfo->GetSize()*sizeof(double))))
	{
		for (nExpression = 0, nExpressions = (INT)pEventInfo->GetSize(), nIndex = 0; nExpression < nExpressions; nExpression++)
		{
			if ((pExpression = pEventInfo->GetAt(nExpressions - nExpression - 1)))
			{
				if (pExpression->IsNumber())
				{
					pExpressions[nIndex] = pExpression->GetNumber();
					nIndex = nIndex + 1;
					continue;
				}
				if (pExpression->IsParameter())
				{
					if ((pTMParameter = (pExpression->GetParameter(szParameter, nSample, bCoding)) ? m_pTMEnvironment->GetTMParameters()->GetAt(m_pTMEnvironment->GetTMParameters()->Find(szParameter)) : (CTMParameter *)NULL))
					{
						if (pTMParameter->GetRawValue(nSample, nValue, nStatus) && pTMParameter->GetValue(GetDatabase(), nSample, (bCoding) ? ((pTMParameter->GetAttributes() | TMPARAMETER_CALIBRATION_NONE) & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) : pTMParameter->GetAttributes(), fValue))
						{
							pExpressions[nIndex] = fValue;
							nIndex = nIndex + 1;
							continue;
						}
					}
					break;
				}
				if (pExpression->IsOperator())
				{
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_DIV))
					{
						if (pExpressions[nIndex - 1] != 0.0  &&  fabs(pExpressions[nIndex - 1]) > FLT_EPSILON)
						{
							pExpressions[(nIndex - 1) - 1] = pExpressions[(nIndex - 1) - 1] / pExpressions[nIndex - 1];
							nIndex = nIndex - 1;
							continue;
						}
						break;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_MUL))
					{
						pExpressions[(nIndex - 1) - 1] *= pExpressions[nIndex - 1];
						nIndex = nIndex - 1;
						continue;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_SUB))
					{
						pExpressions[(nIndex - 1) - 1] = pExpressions[(nIndex - 1) - 1] - pExpressions[nIndex - 1];
						nIndex = nIndex - 1;
						continue;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_ADD))
					{
						pExpressions[(nIndex - 1) - 1] += pExpressions[nIndex - 1];
						nIndex = nIndex - 1;
						continue;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_CHG))
					{
						pExpressions[nIndex - 1] = -pExpressions[nIndex - 1];
						continue;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_AND))
					{
						pExpressions[(nIndex - 1) - 1] = (double)(((UINT)pExpressions[(nIndex - 1) - 1]) & ((UINT)pExpressions[nIndex - 1]));
						nIndex = nIndex - 1;
						continue;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_OR))
					{
						pExpressions[(nIndex - 1) - 1] = (double)(((UINT)pExpressions[(nIndex - 1) - 1]) | ((UINT)pExpressions[nIndex - 1]));
						nIndex = nIndex - 1;
						continue;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_NOT))
					{
						pExpressions[nIndex - 1] = (double)(~(ULONGLONG)pExpressions[nIndex - 1]);
						continue;
					}
					if (pExpression->GetOperator() == STRING(IDS_TELEMETRYEVENTS_OPERATOR_XOR))
					{
						pExpressions[(nIndex - 1) - 1] = (double)(((UINT)pExpressions[(nIndex - 1) - 1]) ^ ((UINT)pExpressions[nIndex - 1]));
						nIndex = nIndex - 1;
						continue;
					}
				}
				if (pExpression->IsFunction())
				{
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_SIN))
					{
						pExpressions[nIndex - 1] = sin(pExpressions[nIndex - 1]);
						continue;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_COS))
					{
						pExpressions[nIndex - 1] = cos(pExpressions[nIndex - 1]);
						continue;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_TAN))
					{
						if (fabs(fmod(pExpressions[nIndex - 1], M_PI)) - M_PI / 2.0 > FLT_EPSILON)
						{
							pExpressions[nIndex - 1] = tan(pExpressions[nIndex - 1]);
							continue;
						}
						break;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ASIN))
					{
						if (fabs(pExpressions[nIndex - 1]) <= 1.0)
						{
							pExpressions[nIndex - 1] = asin(pExpressions[nIndex - 1]);
							continue;
						}
						break;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ACOS))
					{
						if (fabs(pExpressions[nIndex - 1]) <= 1.0)
						{
							pExpressions[nIndex - 1] = acos(pExpressions[nIndex - 1]);
							continue;
						}
						break;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ATAN))
					{
						pExpressions[nIndex - 1] = atan(pExpressions[nIndex - 1]);
						continue;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_ABS))
					{
						pExpressions[nIndex - 1] = fabs(pExpressions[nIndex - 1]);
						continue;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_INT))
					{
						pExpressions[nIndex - 1] = (pExpressions[nIndex - 1] >= 0.0) ? floor(pExpressions[nIndex - 1]) : ceil(pExpressions[nIndex - 1]);
						continue;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_SQRT))
					{
						if (pExpressions[nIndex - 1] >= 0.0)
						{
							pExpressions[nIndex - 1] = sqrt(pExpressions[nIndex - 1]);
							continue;
						}
						break;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_POW2))
					{
						pExpressions[nIndex - 1] = pow(pExpressions[nIndex - 1], 2.0);
						continue;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_POWY))
					{
						pExpressions[(nIndex - 1) - 1] = pow(pExpressions[(nIndex - 1) - 1], pExpressions[nIndex - 1]);
						nIndex = nIndex - 1;
						continue;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_LN))
					{
						if (pExpressions[nIndex - 1] > 0.0)
						{
							pExpressions[nIndex - 1] = log(pExpressions[nIndex - 1]);
							continue;
						}
						break;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_LOG))
					{
						if (pExpressions[nIndex - 1] > 0.0)
						{
							pExpressions[nIndex - 1] = log10(pExpressions[nIndex - 1]);
							continue;
						}
						break;
					}
					if (pExpression->GetFunction() == STRING(IDS_TELEMETRYEVENTS_MATHFUNCTION_EXP))
					{
						pExpressions[nIndex - 1] = exp(pExpressions[nIndex - 1]);
						continue;
					}
				}
			}
		}
		if (nIndex == 1 && nExpression == nExpressions)
		{
			if ((pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_BELOWZERO  &&  pExpressions[nIndex - 1] < 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_EQUALZERO  &&  pExpressions[nIndex - 1] == 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_ABOVEZERO  &&  pExpressions[nIndex - 1] > 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_UNEQUALZERO  &&  pExpressions[nIndex - 1] != 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_BELOWEQUALZERO  &&  pExpressions[nIndex - 1] <= 0.0) || (pEventInfo->GetResultCode() == TELEMETRYEVENTINFO_RESULT_ABOVEEQUALZERO  &&  pExpressions[nIndex - 1] >= 0.0))
			{
				GlobalFree(pExpressions);
				return TRUE;
			}
		}
		GlobalFree(pExpressions);
	}
	return FALSE;
}

VOID CTMProcessThread::DoPrintouts(CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nJob;
	INT  nJobs;
	INT  nPage;
	INT  nPages;
	INT  nDisplay;
	INT  nDisplays;
	BOOL  bPrintout;
	UINT  nPrintCount;
	UINT  nStopCount;
	CString  szEvent;
	CANDWnd  *pANDWnd;
	CGRDWnd  *pGRDWnd;
	CHEXWnd  *pHEXWnd;
	CMMDWnd  *pMMDWnd;
	COOLWnd  *pOOLWnd;
	CPODWnd  *pPODWnd;
	CTPEPWnd  *pTPEPWnd;
	CTimeKey  tStopTime;
	CPtrArray  pDisplays;
	CANDPrintJobs  pANDJobs;
	CGRDPrintJobs  pGRDJobs;
	CHEXPrintJobs  pHEXJobs;
	CMMDPrintJobs  pMMDJobs;
	COOLPrintJobs  pOOLJobs;
	CPODPrintJobs  pPODJobs;
	CTPEPPrintJobs  pTPEPJobs;
	CANDPrintJobInfo  *pANDJobInfo;
	CGRDPrintJobInfo  *pGRDJobInfo;
	CHEXPrintJobInfo  *pHEXJobInfo;
	CMMDPrintJobInfo  *pMMDJobInfo;
	COOLPrintJobInfo  *pOOLJobInfo;
	CPODPrintJobInfo  *pPODJobInfo;
	CTPEPPrintJobInfo  *pTPEPJobInfo;
	CTCOnBoardMemoryImagesWnd  *pTCOnBoardMemoryImagesWnd;
	CTCOnBoardMemoryImagesPrintJobs  pTCOnBoardMemoryImagesJobs;
	CTCOnBoardMemoryImagesPrintJobInfo  *pTCOnBoardMemoryImagesJobInfo;
	CDisplayWnd  *pDisplayWnd;

	for (nPage = 0, nPages = GetDisplayArea()->GetPageCount(); nPage < nPages; nPage++)
	{
		for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(nPage, pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_AND)
			{
				for (nJob = 0, nJobs = ((pANDWnd = (CANDWnd *)pDisplayWnd) && pANDWnd->GetPrintJobs(pANDJobs)) ? (INT)pANDJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pANDJobInfo = pANDJobs.GetAt(nJob)) && pANDJobInfo->GetPrintAtEvent(szEvent) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pANDWnd->Print(pANDJobInfo); (pANDJobInfo->GetPrintMode() & AND_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pANDJobInfo->SetPrintMode(pANDJobInfo->GetPrintMode() & ~AND_PRINT_CLEARCOMMENTS);
							pANDJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (!bPrintout)
						{
							ReportEvent(SYSTEM_WARNING_AND_PRINT_FAILURE, FALSE);
							continue;
						}
					}
				}
				pANDWnd->SetPrintJobs(pANDJobs);
				continue;
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_GRD)
			{
				for (nJob = 0, nJobs = ((pGRDWnd = (CGRDWnd *)pDisplayWnd) && pGRDWnd->GetPrintJobs(pGRDJobs)) ? (INT)pGRDJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pGRDJobInfo = pGRDJobs.GetAt(nJob)) && pGRDJobInfo->GetPrintAtEvent(szEvent) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pGRDWnd->Print(pGRDJobInfo); (pGRDJobInfo->GetPrintMode() & GRD_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pGRDJobInfo->SetPrintMode(pGRDJobInfo->GetPrintMode() & ~GRD_PRINT_CLEARCOMMENTS);
							pGRDJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (!bPrintout)
						{
							ReportEvent(SYSTEM_WARNING_GRD_PRINT_FAILURE, FALSE);
							continue;
						}
					}
				}
				pGRDWnd->SetPrintJobs(pGRDJobs);
				continue;
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_HEX)
			{
				for (nJob = 0, nJobs = ((pHEXWnd = (CHEXWnd *)pDisplayWnd) && pHEXWnd->GetPrintJobs(pHEXJobs)) ? (INT)pHEXJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pHEXJobInfo = pHEXJobs.GetAt(nJob)) && pHEXJobInfo->GetPrintAtEvent(szEvent) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pHEXWnd->Print(pHEXJobInfo); (pHEXJobInfo->GetPrintMode() & HEX_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pHEXJobInfo->SetPrintMode(pHEXJobInfo->GetPrintMode() & ~HEX_PRINT_CLEARCOMMENTS);
							pHEXJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (!bPrintout)
						{
							ReportEvent(SYSTEM_WARNING_HEX_PRINT_FAILURE, FALSE);
							continue;
						}
					}
				}
				pHEXWnd->SetPrintJobs(pHEXJobs);
				continue;
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_MMD)
			{
				for (nJob = 0, nJobs = ((pMMDWnd = (CMMDWnd *)pDisplayWnd) && pMMDWnd->GetPrintJobs(pMMDJobs)) ? (INT)pMMDJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pMMDJobInfo = pMMDJobs.GetAt(nJob)) && pMMDJobInfo->GetPrintAtEvent(szEvent) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pMMDWnd->Print(pMMDJobInfo); (pMMDJobInfo->GetPrintMode() & MMD_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pMMDJobInfo->SetPrintMode(pMMDJobInfo->GetPrintMode() & ~MMD_PRINT_CLEARCOMMENTS);
							pMMDJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (!bPrintout)
						{
							ReportEvent(SYSTEM_WARNING_MMD_PRINT_FAILURE, FALSE);
							continue;
						}
					}
				}
				pMMDWnd->SetPrintJobs(pMMDJobs);
				continue;
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_OOL && (pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL || !nPage))
			{
				for (nJob = 0, nJobs = ((pOOLWnd = (COOLWnd *)pDisplayWnd) && pOOLWnd->GetPrintJobs(pOOLJobs)) ? (INT)pOOLJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pOOLJobInfo = pOOLJobs.GetAt(nJob)) && pOOLJobInfo->GetPrintAtEvent(szEvent) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pOOLWnd->Print(pOOLJobInfo); (pOOLJobInfo->GetPrintMode() & OOL_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pOOLJobInfo->SetPrintMode(pOOLJobInfo->GetPrintMode() & ~OOL_PRINT_CLEARCOMMENTS);
							pOOLJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (!bPrintout)
						{
							ReportEvent(SYSTEM_WARNING_OOL_PRINT_FAILURE, FALSE);
							continue;
						}
					}
				}
				pOOLWnd->SetPrintJobs(pOOLJobs);
				continue;
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_POD)
			{
				for (nJob = 0, nJobs = ((pPODWnd = (CPODWnd *)pDisplayWnd) && pPODWnd->GetPrintJobs(pPODJobs)) ? (INT)pPODJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pPODJobInfo = pPODJobs.GetAt(nJob)) && pPODJobInfo->GetPrintAtEvent(szEvent) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pPODWnd->Print(pPODJobInfo); (pPODJobInfo->GetPrintMode() & POD_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pPODJobInfo->SetPrintMode(pPODJobInfo->GetPrintMode() & ~POD_PRINT_CLEARCOMMENTS);
							pPODJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (!bPrintout)
						{
							ReportEvent(SYSTEM_WARNING_POD_PRINT_FAILURE, FALSE);
							continue;
						}
					}
				}
				pPODWnd->SetPrintJobs(pPODJobs);
				continue;
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TPEP)
			{
				for (nJob = 0, nJobs = ((pTPEPWnd = (CTPEPWnd *)pDisplayWnd) && pTPEPWnd->GetPrintJobs(pTPEPJobs)) ? (INT)pTPEPJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pTPEPJobInfo = pTPEPJobs.GetAt(nJob)) && pTPEPJobInfo->GetPrintAtEvent(szEvent) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pTPEPWnd->Print(pTPEPJobInfo); (pTPEPJobInfo->GetPrintMode() & TPEP_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pTPEPJobInfo->SetPrintMode(pTPEPJobInfo->GetPrintMode() & ~TPEP_PRINT_CLEARCOMMENTS);
							pTPEPJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (!bPrintout)
						{
							ReportEvent(SYSTEM_WARNING_TPEP_PRINT_FAILURE, FALSE);
							continue;
						}
					}
				}
				pTPEPWnd->SetPrintJobs(pTPEPJobs);
				continue;
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)
			{
				for (nJob = 0, nJobs = ((pTCOnBoardMemoryImagesWnd = (CTCOnBoardMemoryImagesWnd *)pDisplayWnd) && pTCOnBoardMemoryImagesWnd->GetPrintJobs(pTCOnBoardMemoryImagesJobs)) ? (INT)pTCOnBoardMemoryImagesJobs.GetSize() : 0; nJob < nJobs; nJob++)
				{
					if ((pTCOnBoardMemoryImagesJobInfo = pTCOnBoardMemoryImagesJobs.GetAt(nJob)) && (pTCOnBoardMemoryImagesJobInfo->GetPrintAtEvent(szEvent, tStopTime) || pTCOnBoardMemoryImagesJobInfo->GetPrintAtEvent(szEvent, nStopCount)) && szEvent == pEventInfo->GetName())
					{
						for (bPrintout = pTCOnBoardMemoryImagesWnd->Print(pTCOnBoardMemoryImagesJobInfo); (pTCOnBoardMemoryImagesJobInfo->GetPrintMode() & TCONBOARDMEMORYIMAGES_PRINT_CLEARCOMMENTS) && bPrintout; )
						{
							pTCOnBoardMemoryImagesJobInfo->SetPrintMode(pTCOnBoardMemoryImagesJobInfo->GetPrintMode() & ~TCONBOARDMEMORYIMAGES_PRINT_CLEARCOMMENTS);
							pTCOnBoardMemoryImagesJobInfo->SetComments(EMPTYSTRING);
							break;
						}
						if (bPrintout)
						{
							pTCOnBoardMemoryImagesJobInfo->SetPrintCount((pTCOnBoardMemoryImagesJobInfo->GetPrintCount(nPrintCount)) ? (nPrintCount + 1) : 0);
							continue;
						}
						ReportEvent(SYSTEM_WARNING_TCONBOARDMEMORYIMAGES_PRINT_FAILURE, FALSE);
					}
				}
				pTCOnBoardMemoryImagesWnd->SetPrintJobs(pTCOnBoardMemoryImagesJobs);
				continue;
			}
		}
	}
}

VOID CTMProcessThread::DoDownloads(CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nProfile;
	INT  nProfiles;
	CTimeKey  tTimeKey;
	CTimeSpan  tDelay;
	CToolsDownloadProfiles  pProfiles;
	CToolsDownloadProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (GetToolsDownloadProfiles(pProfiles)) ? (INT)pProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = pProfiles.GetAt(nProfile)) && (pProfileInfo->GetOptions() & TOOLSDOWNLOADINFO_OPTION_DISABLED) != TOOLSDOWNLOADINFO_OPTION_DISABLED  &&  pProfileInfo->GetTriggeredExecution(tDelay) == pEventInfo->GetName())
		{
			pProfileInfo->SetExecutionMode((tDelay.GetTotalSeconds() > 0) ? TOOLSDOWNLOADINFO_EXECUTION_ATTIME : TOOLSDOWNLOADINFO_EXECUTION_IMMEDIATELY);
			pProfileInfo->SetExecutionTime((tDelay.GetTotalSeconds() > 0) ? (tTimeKey.GetTime() + tDelay.GetTotalSeconds()) : 0);
			GetToolsDownloadService()->Update(pProfileInfo);
		}
	}
}

VOID CTMProcessThread::DoHistoryFileExtractions(CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nProfile;
	INT  nProfiles;
	CTimeKey  tTimeKey;
	CTimeSpan  tTimeInterval[2];
	CArchivesExtractionProfiles  pProfiles;
	CArchivesExtractionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (GetTMService()->GetTMHistoryFileExtractionProfiles(pProfiles)) ? (INT)pProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = pProfiles.GetAt(nProfile)) && pProfileInfo->GetExecutionMode() == ARCHIVESEXTRACTIONINFO_EXECUTION_ATEVENT  &&  pProfileInfo->GetTriggeredExecution() == pEventInfo->GetName())
		{
			for (tTimeInterval[0] = pProfileInfo->GetTriggeredInterval(TRUE), tTimeInterval[1] = pProfileInfo->GetTriggeredInterval(FALSE); !tTimeInterval[1].GetTotalSeconds(); )
			{
				pProfileInfo->SetTimeRangeMode(ARCHIVESEXTRACTIONINFO_RANGE_NORMAL);
				pProfileInfo->SetExecutionMode(ARCHIVESEXTRACTIONINFO_EXECUTION_IMMEDIATELY);
				pProfileInfo->SetTimeRange(tTimeKey.GetTime() - tTimeInterval[0].GetTotalSeconds(), tTimeKey);
				break;
			}
			if (tTimeInterval[1].GetTotalSeconds() > 0)
			{
				pProfileInfo->SetTimeRangeMode(ARCHIVESEXTRACTIONINFO_RANGE_NORMAL);
				pProfileInfo->SetExecutionMode(ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME);
				pProfileInfo->SetTimeRange(tTimeKey.GetTime() - tTimeInterval[0].GetTotalSeconds(), tTimeKey.GetTime() + tTimeInterval[1].GetTotalSeconds());
				pProfileInfo->SetExecutionTime(tTimeKey.GetTime() + tTimeInterval[1].GetTotalSeconds());
			}
			GetTMService()->ExecuteTMHistoryFileExtraction(pProfileInfo);
		}
	}
}

VOID CTMProcessThread::DoHistoricalTelemetryReports(CONST CTelemetryEventInfo *pEventInfo)
{
	INT  nReport;
	INT  nReports;
	CTimeKey  tTimeKey;
	CTimeSpan  tTimeInterval[2];
	CTelemetryHistoricalReports  pHistoricalReports;
	CTelemetryHistoricalReportInfo  *pHistoricalReportInfo;

	for (nReport = 0, nReports = (GetTelemetryHistoricalReports(pHistoricalReports)) ? (INT)pHistoricalReports.GetSize() : 0; nReport < nReports; nReport++)
	{
		if ((pHistoricalReportInfo = pHistoricalReports.GetAt(nReport)) && pHistoricalReportInfo->GetExecutionMode() == TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATEVENT  &&  pHistoricalReportInfo->GetTriggeredExecution() == pEventInfo->GetName())
		{
			for (tTimeInterval[0] = pHistoricalReportInfo->GetTriggeredInterval(TRUE), tTimeInterval[1] = pHistoricalReportInfo->GetTriggeredInterval(FALSE); !tTimeInterval[1].GetTotalSeconds(); )
			{
				pHistoricalReportInfo->SetTimeRangeMode(TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL);
				pHistoricalReportInfo->SetExecutionMode(TELEMETRYHISTORICALREPORTINFO_EXECUTION_IMMEDIATELY);
				pHistoricalReportInfo->SetTimeRange(tTimeKey.GetTime() - tTimeInterval[0].GetTotalSeconds(), tTimeKey);
				break;
			}
			if (tTimeInterval[1].GetTotalSeconds() > 0)
			{
				pHistoricalReportInfo->SetTimeRangeMode(TELEMETRYHISTORICALREPORTINFO_RANGE_NORMAL);
				pHistoricalReportInfo->SetExecutionMode(TELEMETRYHISTORICALREPORTINFO_EXECUTION_ATTIME);
				pHistoricalReportInfo->SetTimeRange(tTimeKey.GetTime() - tTimeInterval[0].GetTotalSeconds(), tTimeKey.GetTime() + tTimeInterval[1].GetTotalSeconds());
				pHistoricalReportInfo->SetExecutionTime(tTimeKey.GetTime() + tTimeInterval[1].GetTotalSeconds());
			}
			GetTelemetryReportsService()->Update(pHistoricalReportInfo);
		}
	}
}

VOID CTMProcessThread::DoUpdateTelecommandSources(CONST CTelemetryEventInfo *pEventInfo)
{
	GetTCService()->Update(pEventInfo->GetName());
}

BOOL CTMProcessThread::DoBackup(CONST CHistoryStoreFile *pFile, BOOL bDelayed)
{
	CTMArchivesBackupThread  *pBackupThread;

	if ((pBackupThread = new CTMArchivesBackupThread))
	{
		if (pBackupThread->Start(pFile, bDelayed, m_cArchiveBackupFiles, m_hObject)) return TRUE;
		delete pBackupThread;
	}
	return FALSE;
}

BOOL CTMProcessThread::CheckDatabaseValidity(CONST CTMUnit &cTMUnit) CONST
{
	CTimeKey  tValidity[2];

	return((GetDatabase()->GetValidity(tValidity[0], tValidity[1]) && ((tValidity[0].GetTime() > 0 && tValidity[1].GetTime() > 0 && cTMUnit.GetTimeTag().GetTimeInSeconds() >= tValidity[0].GetTime() && cTMUnit.GetTimeTag().GetTimeInSeconds() <= tValidity[1].GetTime()) || (!tValidity[0].GetTime() && !tValidity[1].GetTime()))) ? TRUE : FALSE);
}

BOOL CTMProcessThread::Map(CByteArray &nInfo) CONST
{
	nInfo.RemoveAll();
	return TRUE;
}

BOOL CTMProcessThread::Unmap(CONST CByteArray &nInfo)
{
	return TRUE;
}

BOOL CTMProcessThread::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_TIMER)
	{
		for (Lock(); pMsg->wParam == m_nArchiveBufferTimerID && m_nArchiveBufferTimerID > 0; )
		{
			for (m_bArchiveBufferFlash = TRUE; m_bArchiveBufferFlash; m_bArchiveBufferFlash = FALSE)
			{
				UpdateArchives();
				continue;
			}
			Unlock();
			return TRUE;
		}
		Unlock();
	}
	return CThread::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CTMProcessThread, CThread)
	//{{AFX_MSG_MAP(CTMProcessThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMProcessThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTMService

CTMService::CTMService() : CObject()
{
	m_tLastTMRetrieveTime = 0;
}

BOOL CTMService::Start(LPCTSTR pszName)
{
	m_cTMHistoryStore.Open(pszName, HISTORYSTORE_TYPE_TM);
	ReportEvent((!LoadServiceInfo()) ? SYSTEM_WARNING_TELEMETRYSERVICE_LOAD_FAILURE : SYSTEM_NOERROR, FALSE);
	ReportEvent((!HasTMProviderDevices()) ? SYSTEM_INFORMATIONAL_TELEMETRYSERVICE_NOT_AVAILABLE : SYSTEM_NOERROR, FALSE);
	ReportEvent((!HasTMHistoryFiles(HISTORYFILE_TYPE_ARCHIVE)) ? SYSTEM_INFORMATIONAL_TELEMETRYARCHIVES_ARCHIVEFILES_NOT_AVAILABLE : SYSTEM_NOERROR, FALSE);
	ReportEvent((!HasTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE)) ? SYSTEM_INFORMATIONAL_TELEMETRYARCHIVES_RETRIEVEFILES_NOT_AVAILABLE : SYSTEM_NOERROR, FALSE);
	ReportEvent((!m_cTMHistoryFileExtractionThread.Start()) ? SYSTEM_WARNING_TELEMETRYHISTORYFILEEXTRACTIONSERVICE_GENERAL_FAILURE : SYSTEM_NOERROR, FALSE);
	ReportEvent((!m_cTMExtractionThread.Start()) ? SYSTEM_WARNING_TELEMETRYEXTRACTIONSERVICE_GENERAL_FAILURE : SYSTEM_NOERROR, FALSE);
	return m_cTMProcessThread.Start(pszName);
}

BOOL CTMService::Suspend()
{
	return m_cTMProcessThread.Suspend();
}

BOOL CTMService::IsSuspended() CONST
{
	return m_cTMProcessThread.IsSuspended();
}

BOOL CTMService::Resume()
{
	return m_cTMProcessThread.Resume();
}

VOID CTMService::Stop()
{
	ReportEvent((!SaveServiceInfo()) ? SYSTEM_WARNING_TELEMETRYSERVICE_SAVE_FAILURE : SYSTEM_NOERROR);
	m_cTMHistoryFileExtractionThread.Stop();
	m_cTMExtractionThread.Stop();
	m_cTMProcessThread.Stop();
	m_cTMHistoryStore.Close();
}

BOOL CTMService::Update()
{
	return m_cTMProcessThread.Update();
}

INT CTMService::EnumTMSubSystems(CStringArray &szSubSystems, BOOL bAll) CONST
{
	return m_cTMProcessThread.EnumTMSubSystems(szSubSystems, bAll);
}

UINT CTMService::TranslateTMSubSystemToID(LPCTSTR pszSubSystem) CONST
{
	return m_cTMProcessThread.TranslateTMSubSystemToID(pszSubSystem);
}

CString CTMService::TranslateIDToTMSubSystem(UINT nSubSystemID) CONST
{
	return m_cTMProcessThread.TranslateIDToTMSubSystem(nSubSystemID);
}

BOOL CTMService::SetTMProviderDevices(CONST CTMProviderDevices &pDevices)
{
	return m_cTMProcessThread.SetTMProviderDevices(pDevices);
}

INT CTMService::GetTMProviderDevices(CTMProviderDevices &pDevices) CONST
{
	return m_cTMProcessThread.GetTMProviderDevices(pDevices);
}

BOOL CTMService::HasTMProviderDevices(BOOL bSupported) CONST
{
	return m_cTMProcessThread.HasTMProviderDevices(bSupported);
}

BOOL CTMService::SetActiveTMProviderDevice(CONST CTMProviderDevice *pDevice)
{
	return m_cTMProcessThread.SetActiveTMProviderDevice(pDevice);
}

BOOL CTMService::GetActiveTMProviderDevice(CTMProviderDevice *pDevice) CONST
{
	return m_cTMProcessThread.GetActiveTMProviderDevice(pDevice);
}

BOOL CTMService::StopActiveTMProviderDevice(HANDLE hDevice)
{
	return m_cTMProcessThread.StopActiveTMProviderDevice(hDevice);
}

BOOL CTMService::SetTMHistoryFiles(UINT nType, CONST CHistoryStoreFiles &pFiles)
{
	if (m_cTMHistoryStore.SetHistoryFiles(nType, pFiles))
	{
		UpdateArchivingStatus();
		return TRUE;
	}
	return FALSE;
}

INT CTMService::GetTMHistoryFiles(UINT nType, CHistoryStoreFiles &pFiles) CONST
{
	return m_cTMHistoryStore.GetHistoryFiles(nType, pFiles);
}

INT CTMService::UpdateTMHistoryFiles(CONST CTMEnvironment *pTMEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors)
{
	return((!m_cTMProcessThread.IsTestModeEnabled()) ? m_cTMHistoryStore.Update(pTMEnvironment, pFiles, nErrors) : 0);
}
INT CTMService::UpdateTMHistoryFiles(CHistoryStoreFiles &pFiles, CUIntArray &nErrors)
{
	return m_cTMHistoryStore.Update(pFiles, nErrors);
}

BOOL CTMService::HasTMHistoryFiles(UINT nType) CONST
{
	CHistoryStoreFiles  pFiles;

	return((GetTMHistoryFiles(nType, pFiles) > 0) ? TRUE : FALSE);
}

BOOL CTMService::SetDefaultTMHistoryFile(UINT nType, CONST CHistoryStoreFile &cFile)
{
	if (m_cTMHistoryStore.SetDefaultHistoryFile(nType, cFile))
	{
		UpdateArchivingStatus();
		return TRUE;
	}
	return FALSE;
}

BOOL CTMService::GetDefaultTMHistoryFile(UINT nType, CHistoryStoreFile &cFile) CONST
{
	return m_cTMHistoryStore.GetDefaultHistoryFile(nType, cFile);
}

BOOL CTMService::SetTMHistoryFilesOptions(CONST CHistoryStoreOptions &pOptions)
{
	return((m_cTMHistoryStore.SetOptions(pOptions) && m_cTMProcessThread.InitializeTMHistoryStore(pOptions)) ? TRUE : FALSE);
}

BOOL CTMService::GetTMHistoryFilesOptions(CHistoryStoreOptions &pOptions) CONST
{
	return m_cTMHistoryStore.GetOptions(pOptions);
}

BOOL CTMService::SetTMHistoryFilesBrowseOptions(CONST CUIntArray &nOptions, CONST CStringArray &szDirectories)
{
	return m_cTMHistoryStore.SetBrowseOptions(nOptions, szDirectories);
}

BOOL CTMService::GetTMHistoryFilesBrowseOptions(CUIntArray &nOptions, CStringArray &szDirectories) CONST
{
	return m_cTMHistoryStore.GetBrowseOptions(nOptions, szDirectories);
}

BOOL CTMService::GetTMHistoryFilesDetails(CString &szArchiveFile, UINT &nArchiveFreeSpace, BOOL &bArchiveStatus, CString &szBackupDirectory, UINT &nBackupFreeSpace, BOOL &bBackupStatus) CONST
{
	CTimeKey  tBackupTime;
	DWORDLONG  dwDiskFree[2];

	return GetTMHistoryFilesDetails(szArchiveFile, dwDiskFree[0], nArchiveFreeSpace, bArchiveStatus, szBackupDirectory, dwDiskFree[1], nBackupFreeSpace, tBackupTime, bBackupStatus);
}
BOOL CTMService::GetTMHistoryFilesDetails(CString &szArchiveFile, DWORDLONG &dwArchiveFreeSpace, UINT &nArchiveFreeSpace, BOOL &bArchiveStatus, CString &szBackupDirectory, DWORDLONG &dwBackupFreeSpace, UINT &nBackupFreeSpace, CTimeKey &tBackupTime, BOOL &bBackupStatus) CONST
{
	INT  nFile;
	INT  nFiles;
	BOOL  bStatus[2];
	UINT  nDiskFree[2][2];
	double  fDiskFree[2];
	CString  szFile[2][2];
	CTimeKey  tFileTime[2];
	CTimeKey  tFileBackup[2];
	DWORDLONG  dwDiskFree[2][2];
	CByteArray  nFileData;
	CLogicalDrives  cDrives;
	CHistoryStoreFile  *pFile;
	CHistoryStoreFiles  pFiles;

	if (GetTMHistoryFiles(HISTORYFILE_TYPE_ARCHIVE, pFiles) > 0)
	{
		for (nFile = 0, nFiles = (INT)pFiles.GetSize(), tFileBackup[0] = 0; nFile < nFiles; nFile++)
		{
			if ((pFile = pFiles.GetAt(nFile)) && (pFile->GetOptions() & HISTORYSTORE_OPTION_SHOWSTATUS))
			{
				for (nDiskFree[0][1] = ((fDiskFree[0] = cDrives.GetFreeDriveSpace((szFile[0][1] = pFile->GetFileName()))) >= 0.0) ? (UINT)(100.0*fDiskFree[0]) : 0, dwDiskFree[0][1] = (fDiskFree[0] >= 0.0) ? cDrives.GetFreeDriveBytes(szFile[0][1]) : 0, szFile[0][1] = (fDiskFree[0] >= 0.0) ? szFile[0][1] : EMPTYSTRING; szFile[0][0].IsEmpty() || dwDiskFree[0][0] > dwDiskFree[0][1]; )
				{
					bStatus[0] = ((pFile->GetOptions() & HISTORYSTORE_OPTION_USE) || (pFile->GetOptions() & HISTORYSTORE_OPTION_DAILYUSE) || (pFile->GetOptions() & HISTORYSTORE_OPTION_LIMITEDUSE)) ? TRUE : FALSE;
					dwDiskFree[0][0] = dwDiskFree[0][1];
					nDiskFree[0][0] = nDiskFree[0][1];
					szFile[0][0] = szFile[0][1];
					break;
				}
				for (nDiskFree[1][1] = ((fDiskFree[1] = cDrives.GetFreeDriveSpace((szFile[1][1] = pFile->GetBackupDirectory()))) >= 0.0) ? (UINT)(100.0*fDiskFree[1]) : 0, dwDiskFree[1][1] = (fDiskFree[1] >= 0.0) ? cDrives.GetFreeDriveBytes(szFile[1][1]) : 0, szFile[1][1] = (fDiskFree[1] >= 0.0) ? szFile[1][1] : EMPTYSTRING; szFile[1][0].IsEmpty() || dwDiskFree[1][0] > dwDiskFree[1][1]; )
				{
					dwDiskFree[1][0] = dwDiskFree[1][1];
					nDiskFree[1][0] = nDiskFree[1][1];
					szFile[1][0] = szFile[1][1];
					break;
				}
				for (bStatus[1] = (pFile->GetOptions() & HISTORYSTORE_OPTION_BACKUP) ? TRUE : FALSE; bStatus[1]; )
				{
					if (pFile->CLogFile::Open(pFile->GetFileName(), (LPCTSTR)NULL, STRING(IDS_LOGFILETYPE_TMHISTORY), STRING(IDS_LOGFILETYPE_HISTORY), CFile::modeRead))
					{
						tFileBackup[1] = (pFile->CLogFile::SeekToFirst() && pFile->CLogFile::Read(tFileTime[0], nFileData) && tFileTime[1] >= tFileTime[0] && pFile->GetSize() > 0) ? ((pFile->GetOptions() & HISTORYSTORE_OPTION_BACKUPBYDEFAULT) ? ((pFile->GetFileSize() >= pFile->GetSize() && pFile->GetFileSize() / pFile->GetSize() <= 1000) ? (TIMEKEY)((double)tFileTime[0].GetTime() + ((double)pFile->GetFileSize() / (double)pFile->GetSize())*(double)(tFileTime[1].GetTime() - tFileTime[0].GetTime())) : 0) : ((pFile->GetBackupSize() >= pFile->GetSize() && pFile->GetBackupSize() / pFile->GetSize() <= 1000) ? (TIMEKEY)((double)tFileTime[0].GetTime() + ((double)pFile->GetBackupSize() / (double)pFile->GetSize())*(double)(tFileTime[1].GetTime() - tFileTime[0].GetTime())) : 0)) : 0;
						tFileBackup[0] = (tFileBackup[0] > tFileBackup[1] || tFileBackup[0] == 0) ? tFileBackup[1] : tFileBackup[0];
						pFile->CLogFile::Close();
					}
					break;
				}
			}
		}
		if (!szFile[0][0].IsEmpty())
		{
			szArchiveFile = szFile[0][0];
			dwArchiveFreeSpace = dwDiskFree[0][0];
			nArchiveFreeSpace = nDiskFree[0][0];
			bArchiveStatus = bStatus[0];
		}
		if (!szFile[1][0].IsEmpty())
		{
			szBackupDirectory = szFile[1][0];
			dwBackupFreeSpace = dwDiskFree[1][0];
			nBackupFreeSpace = nDiskFree[1][0];
			tBackupTime = tFileBackup[0];
			bBackupStatus = bStatus[1];
		}
	}
	if (szFile[0][0].IsEmpty())
	{
		szArchiveFile.Empty();
		dwArchiveFreeSpace = 0;
		nArchiveFreeSpace = 0;
		bArchiveStatus = FALSE;
	}
	if (szFile[1][0].IsEmpty())
	{
		szBackupDirectory.Empty();
		dwBackupFreeSpace = 0;
		nBackupFreeSpace = 0;
		tBackupTime = 0;
		bBackupStatus = FALSE;
	}
	return((!szFile[0][0].IsEmpty() || !szFile[1][0].IsEmpty()) ? TRUE : FALSE);
}
BOOL CTMService::GetTMHistoryFilesDetails(CString &szDetails) CONST
{
	INT  nPos;
	INT  cbDelimiter;
	BOOL  bStatus[2];
	UINT  nDiskFree[2];
	CString  szFile[2];
	CString  szDigit[2];
	CString  szStatus[3];
	CString  szDelimiter;
	CString  szDiskFree[2];
	CTimeKey  tBackupTime[1];
	DWORDLONG  dwDiskFree[2];
	CStringTools  cStringTools;

	if (GetTMHistoryFilesDetails(szFile[0], dwDiskFree[0], nDiskFree[0], bStatus[0], szFile[1], dwDiskFree[1], nDiskFree[1], tBackupTime[0], bStatus[1]))
	{
		if ((cbDelimiter = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, (LPTSTR)NULL, (INT)0)))
		{
			if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, szDelimiter.GetBufferSetLength(cbDelimiter - 1), cbDelimiter))
			{
				for (nPos = 0, dwDiskFree[0] = dwDiskFree[0] / 1024, szDigit[0] = cStringTools.ConvertIntToString(0), szDiskFree[0].Empty(), szDelimiter.ReleaseBuffer(); !nPos || dwDiskFree[0] > 0; nPos++)
				{
					szDiskFree[0] = (nPos > 0 && nPos % 3 == 0) ? (CString((TCHAR)(dwDiskFree[0] % 10 + __toascii(szDigit[0][0]))) + szDelimiter + szDiskFree[0]) : (CString((TCHAR)(dwDiskFree[0] % 10 + __toascii(szDigit[0][0]))) + szDiskFree[0]);
					dwDiskFree[0] = dwDiskFree[0] / 10;
				}
				for (nPos = 0, dwDiskFree[1] = dwDiskFree[1] / 1024, szDigit[1] = cStringTools.ConvertIntToString(0), szDiskFree[1].Empty(); !nPos || dwDiskFree[1] > 0; nPos++)
				{
					szDiskFree[1] = (nPos > 0 && nPos % 3 == 0) ? (CString((TCHAR)(dwDiskFree[1] % 10 + __toascii(szDigit[1][0]))) + szDelimiter + szDiskFree[1]) : (CString((TCHAR)(dwDiskFree[1] % 10 + __toascii(szDigit[1][0]))) + szDiskFree[1]);
					dwDiskFree[1] = dwDiskFree[1] / 10;
				}
				szStatus[0].Format(STRING(IDS_TELEMETRYARCHIVES_STATUS_ARCHIVEDETAILS), (LPCTSTR)szFile[0], (LPCTSTR)szDiskFree[0], nDiskFree[0], (bStatus[0]) ? STRING(IDS_TELEMETRYARCHIVES_STATUS_ARCHIVEONDETAILS) : STRING(IDS_TELEMETRYARCHIVES_STATUS_ARCHIVEOFFDETAILS));
				szStatus[1].Format(STRING(IDS_TELEMETRYARCHIVES_STATUS_BACKUPDETAILS), (LPCTSTR)szFile[1], (LPCTSTR)szDiskFree[1], nDiskFree[1], (bStatus[1]) ? STRING(IDS_TELEMETRYARCHIVES_STATUS_BACKUPONDETAILS) : STRING(IDS_TELEMETRYARCHIVES_STATUS_BACKUPOFFDETAILS));
				szStatus[2] = (tBackupTime[0] > 0) ? (EOL + tBackupTime[0].FormatGmt(STRING(IDS_TELEMETRYARCHIVES_STATUS_BACKUPTIME))) : EMPTYSTRING;
				szDetails = (!szFile[0].IsEmpty() && !szFile[1].IsEmpty()) ? (LPCTSTR)(szStatus[0] + EOL + szStatus[1] + szStatus[2]) : EMPTYSTRING;
				szDetails = (!szFile[0].IsEmpty() && szFile[1].IsEmpty()) ? (LPCTSTR)szStatus[0] : (LPCTSTR)szDetails;
				return TRUE;
			}
			szDelimiter.ReleaseBuffer();
		}
	}
	return FALSE;
}

BOOL CTMService::SetTMHistoryFileExtractionProfiles(CONST CArchivesExtractionProfiles &pProfiles)
{
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	return m_pTMHistoryExtractionProfiles.Copy(&pProfiles);
}
BOOL CTMService::SetTMHistoryFileExtractionProfiles(CONST CHistoryFileExtractionProfiles &pProfiles)
{
	return((pProfiles.GetSize() > 0) ? ExecuteTMHistoryFileExtraction(pProfiles.GetAt((INT)(pProfiles.GetSize() - 1))) : FALSE);
}

BOOL CTMService::GetTMHistoryFileExtractionProfiles(CArchivesExtractionProfiles &pProfiles) CONST
{
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	return pProfiles.Copy(&m_pTMHistoryExtractionProfiles);
}
BOOL CTMService::GetTMHistoryFileExtractionProfiles(CHistoryFileExtractionProfiles &pProfiles) CONST
{
	return EnumTMHistoryFileExtractions(pProfiles);
}

BOOL CTMService::EnumTMHistoryFileExtractions(CArchivesExtractionProfiles &pProfiles) CONST
{
	return m_cTMExtractionThread.EnumExtractions(pProfiles);
}
BOOL CTMService::EnumTMHistoryFileExtractions(CHistoryFileExtractionProfiles &pProfiles) CONST
{
	return m_cTMHistoryFileExtractionThread.EnumExtractions(pProfiles);
}

BOOL CTMService::ExecuteTMHistoryFileExtraction(CArchivesExtractionProfileInfo *pProfile)
{
	return m_cTMExtractionThread.Update(pProfile);
}
BOOL CTMService::ExecuteTMHistoryFileExtraction(CHistoryFileExtractionProfileInfo *pProfile)
{
	return m_cTMHistoryFileExtractionThread.Update(pProfile);
}

BOOL CTMService::UpdateTMHistoryFileExtractions(CONST CArchivesExtractionProfiles &pProfiles, CONST CUIntArray &nIDs, CONST CStringArray &szErrors)
{
	return m_cTMExtractionThread.Update(pProfiles, nIDs, szErrors);
}

BOOL CTMService::AbortTMHistoryFileExtractions(CONST CArchivesExtractionProfiles &pProfiles)
{
	return m_cTMExtractionThread.AbortExtractions(pProfiles);
}
BOOL CTMService::AbortTMHistoryFileExtractions(CONST CHistoryFileExtractionProfiles &pProfiles)
{
	return m_cTMHistoryFileExtractionThread.AbortExtractions(pProfiles);
}

BOOL CTMService::SetRecentTMHistoryTimeKey(CONST CTimeKey &tTime)
{
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	return(((m_tLastTMRetrieveTime = tTime) > 0) ? TRUE : FALSE);
}

BOOL CTMService::GetRecentTMHistoryTimeKey(CTimeKey &tTime) CONST
{
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	return(((tTime = m_tLastTMRetrieveTime) > 0) ? TRUE : FALSE);
}

BOOL CTMService::InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData)
{
	return m_cTMProcessThread.InitializeTMUnit(cTMUnit, bBadData);
}
BOOL CTMService::InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData)
{
	return m_cTMProcessThread.InitializeTMUnit(pszTag, cTMUnit, bBadData);
}

BOOL CTMService::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return m_cTMProcessThread.InitializeTMData(pTMParameters, bBadData);
}
BOOL CTMService::InitializeTMData(COolParameters &pOolParameters, BOOL bBadData)
{
	return m_cTMProcessThread.InitializeTMData(pOolParameters, bBadData);
}

BOOL CTMService::InitializeTMDump(CMemoryDump &pDump, BOOL bBadData)
{
	return m_cTMProcessThread.InitializeTMDump(pDump, bBadData);
}

BOOL CTMService::IsTMDump(CONST CTMEnvironment *pTMEnvironment) CONST
{
	return m_cTMProcessThread.IsTMDump(pTMEnvironment);
}

BOOL CTMService::UpdateTMDisplays(BOOL bProcessData)
{
	return m_cTMProcessThread.UpdateTMDisplays(bProcessData);
}

BOOL CTMService::UpdateTMParameters(CONST CTMParameters &pTMParameters)
{
	return m_cTMProcessThread.UpdateTMParameters(pTMParameters);
}

BOOL CTMService::ResetTMParameters()
{
	return m_cTMProcessThread.ResetTMParameters();
}

double CTMService::GetTotalTMBandwidth() CONST
{
	return m_cTMProcessThread.GetTotalTMBandwidth();
}

double CTMService::GetAvailableTMBandwidth() CONST
{
	return m_cTMProcessThread.GetAvailableTMBandwidth();
}

double CTMService::GetMaxDiagnosticTMBandwidth() CONST
{
	return m_cTMProcessThread.GetMaxDiagnosticTMBandwidth();
}

double CTMService::GetAvailableDiagnosticTMBandwidth() CONST
{
	return m_cTMProcessThread.GetAvailableDiagnosticTMBandwidth();
}

CTimeTag CTMService::GetLastTMBandwidthMeasurementTime() CONST
{
	return m_cTMProcessThread.GetLastTMBandwidthMeasurementTime();
}

BOOL CTMService::UpdateTMStream()
{
	return m_cTMProcessThread.UpdateTMStream();
}

BOOL CTMService::CheckTMStreamInterruption() CONST
{
	return m_cTMProcessThread.CheckTMStreamInterruption();
}
BOOL CTMService::CheckTMStreamInterruption(TIMETAG tInterval) CONST
{
	return m_cTMProcessThread.CheckTMStreamInterruption(tInterval);
}

BOOL CTMService::CheckTMStreamCorrelation() CONST
{
	return m_cTMProcessThread.CheckTMStreamCorrelation();
}

BOOL CTMService::TrackSystemAlerts(CONST CSystemAlerts &pAlerts)
{
	return m_cTMProcessThread.TrackSystemAlerts(pAlerts);
}

BOOL CTMService::TrackTelemetryEvents(CONST CTelemetryEvents &pEvents)
{
	return m_cTMProcessThread.TrackTelemetryEvents(pEvents);
}

BOOL CTMService::CheckTelemetryEvent(LPCTSTR pszEvent) CONST
{
	return m_cTMProcessThread.CheckTelemetryEvent(pszEvent);
}

BOOL CTMService::EnableTestMode(BOOL bEnable)
{
	return m_cTMProcessThread.EnableTestMode(bEnable);
}

BOOL CTMService::IsTestModeEnabled() CONST
{
	return m_cTMProcessThread.IsTestModeEnabled();
}

BOOL CTMService::IsHealthy() CONST
{
	return !m_cTMProcessThread.IsThreadActive() || m_cTMProcessThread.IsThreadHealthy();
}

BOOL CTMService::SetServiceInfo(CONST CByteArray &nInfo)
{
	SERVICEINFO  sServiceInfo;
	CByteArray  nServiceInfo[3];
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	if (nInfo.GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nInfo.GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbServiceInfo + sServiceInfo.cbArchivesSettingsInfo + sServiceInfo.cbArchivesExtractionsInfo && sServiceInfo.cbServiceInfo >= 0 && sServiceInfo.cbArchivesSettingsInfo >= 0 && sServiceInfo.cbArchivesExtractionsInfo >= 0; )
		{
			nServiceInfo[0].SetSize(sServiceInfo.cbServiceInfo);
			nServiceInfo[1].SetSize(sServiceInfo.cbArchivesSettingsInfo);
			nServiceInfo[2].SetSize(sServiceInfo.cbArchivesExtractionsInfo);
			CopyMemory(nServiceInfo[0].GetData(), nInfo.GetData() + sizeof(SERVICEINFO), sServiceInfo.cbServiceInfo);
			CopyMemory(nServiceInfo[1].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbServiceInfo, sServiceInfo.cbArchivesSettingsInfo);
			CopyMemory(nServiceInfo[2].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbServiceInfo + sServiceInfo.cbArchivesSettingsInfo, sServiceInfo.cbArchivesExtractionsInfo);
			if (Unmap(nServiceInfo[0]) && m_cTMHistoryStore.Unmap(nServiceInfo[1]) && m_pTMHistoryExtractionProfiles.Unmap(nServiceInfo[2]))
			{
				UpdateTelemetryStatus();
				UpdateArchivingStatus();
				return Update();
			}
			break;
		}
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CTMService::GetServiceInfo(CByteArray &nInfo) CONST
{
	SERVICEINFO  sServiceInfo;
	CByteArray  nServiceInfo[3];
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	if (Map(nServiceInfo[0]) && m_cTMHistoryStore.Map(nServiceInfo[1]) && m_pTMHistoryExtractionProfiles.Map(nServiceInfo[2]))
	{
		nInfo.SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbServiceInfo = (INT)nServiceInfo[0].GetSize()) + (sServiceInfo.cbArchivesSettingsInfo = (INT)nServiceInfo[1].GetSize()) + (sServiceInfo.cbArchivesExtractionsInfo = (INT)nServiceInfo[2].GetSize()))));
		CopyMemory(nInfo.GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO), nServiceInfo[0].GetData(), nServiceInfo[0].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize(), nServiceInfo[1].GetData(), nServiceInfo[1].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize() + nServiceInfo[1].GetSize(), nServiceInfo[2].GetData(), nServiceInfo[2].GetSize());
		return TRUE;
	}
	return FALSE;
}

BOOL CTMService::UpdateServiceInfo(BOOL bSave)
{
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	return((bSave  &&  SaveServiceInfo()) || (!bSave  &&  LoadServiceInfo()));
}

BOOL CTMService::SaveServiceInfo()
{
	BOOL  bSuccess;
	CByteArray  nInfo;
	CProfile  cProfile;

	bSuccess = Map(nInfo) && cProfile.SetTelemetryServiceInfo(nInfo);
	bSuccess &= m_cTMHistoryStore.Map(nInfo) && cProfile.SetTelemetryArchivesSettingsInfo(nInfo);
	bSuccess &= m_pTMHistoryExtractionProfiles.Map(nInfo) && cProfile.SetTelemetryArchivesExtractionInfo(nInfo);
	bSuccess &= m_cTMProcessThread.Map(nInfo) && cProfile.SetTelemetryServiceConfigurationInfo(nInfo);
	return bSuccess;
}

BOOL CTMService::LoadServiceInfo()
{
	BOOL  bSuccess;
	CByteArray  nInfo;
	CProfile  cProfile;

	bSuccess = cProfile.GetTelemetryServiceInfo(nInfo) && Unmap(nInfo);
	bSuccess &= cProfile.GetTelemetryArchivesSettingsInfo(nInfo) && m_cTMHistoryStore.Unmap(nInfo);
	bSuccess &= cProfile.GetTelemetryArchivesExtractionInfo(nInfo) && m_pTMHistoryExtractionProfiles.Unmap(nInfo);
	bSuccess &= cProfile.GetTelemetryServiceConfigurationInfo(nInfo) && m_cTMProcessThread.Unmap(nInfo);
	return bSuccess;
}

BOOL CTMService::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDevicesData;
	CTMProviderDevices  pDevices;
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	sData.cbDevicesData = (GetTMProviderDevices(pDevices) >= 0 && pDevices.Map(nDevicesData)) ? (INT)nDevicesData.GetSize() : -1;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + max(sData.cbDevicesData, 0))); nInfo.GetSize() == sData.cbSize && sData.cbDevicesData >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), nDevicesData.GetData(), sData.cbDevicesData);
		return TRUE;
	}
	return FALSE;
}

BOOL CTMService::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDevicesData;
	CTMProviderDevices  pDevices;
	CSingleLock  cLock(m_cTMProcessThread.m_pCriticalSection, TRUE);

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDevicesData && sData.cbDevicesData >= 0; )
	{
		for (nDevicesData.SetSize(sData.cbDevicesData), CopyMemory(nDevicesData.GetData(), nInfo.GetData() + (cbData = sizeof(DATA)), sData.cbDevicesData); pDevices.Unmap(nDevicesData); ) return SetTMProviderDevices(pDevices);
		break;
	}
	return((!nInfo.GetSize()) ? SetTMProviderDevices(pDevices) : FALSE);
}

BOOL CTMService::Lock()
{
	return m_cTMProcessThread.m_pCriticalSection->Lock();
}

BOOL CTMService::Unlock()
{
	return m_cTMProcessThread.m_pCriticalSection->Unlock();
}
