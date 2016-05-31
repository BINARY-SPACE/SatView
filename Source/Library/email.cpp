// EMAIL.CPP : E-Mail Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the e-mail related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2015/11/14 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CEMailSystem

CEMailSystem::CEMailSystem() : CObject()
{
	m_nPort = SMTP_DEFAULT_PORT;
	m_nOptions = SMTP_OPTIONS_NONE;
	m_nType = CSMTPConnection::PlainText;
	m_nPriority = CSMTPMessage::NormalPriority;
	m_nSSLProtocol = CSMTPConnection::OSDefault;
	m_nAuthentication = CSMTPConnection::AUTH_LOGIN;
	m_pCriticalSection = new CCriticalSection;
}

CEMailSystem::~CEMailSystem()
{
	delete m_pCriticalSection;
}

VOID CEMailSystem::SetServer(LPCTSTR pszServer)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szServer = pszServer;
}

CString CEMailSystem::GetServer() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szServer;
}

VOID CEMailSystem::SetSecurity(CSMTPConnection::ConnectionType nType)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nType = nType;
}

CSMTPConnection::ConnectionType CEMailSystem::GetSecurity() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_nType;
}

VOID CEMailSystem::SetAuthentication(CSMTPConnection::AuthenticationMethod nMethod)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nAuthentication = nMethod;
}

CSMTPConnection::AuthenticationMethod CEMailSystem::GetAuthentication() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_nAuthentication;
}

VOID CEMailSystem::SetSSLProtocol(CSMTPConnection::SSLProtocol nProtocol)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nSSLProtocol = nProtocol;
}

CSMTPConnection::SSLProtocol CEMailSystem::GetSSLProtocol() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_nSSLProtocol;
}

VOID CEMailSystem::SetPriority(CSMTPMessage::PRIORITY nPriority)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nPriority = nPriority;
}

CSMTPMessage::PRIORITY CEMailSystem::GetPriority() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_nPriority;
}

VOID CEMailSystem::SetExtraOptions(UINT nOptions)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nOptions = nOptions;
}

UINT CEMailSystem::GetExtraOptions() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_nOptions;
}

VOID CEMailSystem::SetPort(UINT nPort)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_nPort = nPort;
}

UINT CEMailSystem::GetPort() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_nPort;
}

VOID CEMailSystem::SetCharsetEncoding(LPCTSTR pszEncoding)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szCharsetEncoding = pszEncoding;
}

CString CEMailSystem::GetCharsetEncoding() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szCharsetEncoding;
}

VOID CEMailSystem::SetConnectIPAddress(LPCTSTR pszIPAddress)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szConnectBoundIP = pszIPAddress;
}

CString CEMailSystem::GetConnectIPAddress() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szConnectBoundIP;
}

VOID CEMailSystem::SetAccountName(LPCTSTR pszName)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szAccountName = pszName;
}

CString CEMailSystem::GetAccountName() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szAccountName;
}

VOID CEMailSystem::SetAccountAddress(LPCTSTR pszAddress)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szAccountAddress = pszAddress;
}

CString CEMailSystem::GetAccountAddress() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szAccountAddress;
}

VOID CEMailSystem::SetAccountLogin(LPCTSTR pszUserName)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szAccountLogin = pszUserName;
}

CString CEMailSystem::GetAccountLogin() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szAccountLogin;
}

VOID CEMailSystem::SetAccountPassword(LPCTSTR pszPassword)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szAccountPassword = pszPassword;
}

CString CEMailSystem::GetAccountPassword() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szAccountPassword;
}

CString CEMailSystem::Send(LPCTSTR pszSubject, LPCTSTR pszMessage, LPCTSTR pszRecipients, LPCTSTR pszAttachments, CSMTPMessage::PRIORITY nPriority)
{
	CString  szResult;
	CSMTPMessage  *pSMTPMessage;
	CSMTPBodyPart  cSMTPMessageAttachment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pSMTPMessage = new CSMTPMessage))
	{
		try
		{
			CSMTPAddress  cAddress(m_szAccountName, m_szAccountAddress);

			if (!lstrlen(pszRecipients))
			{
				szResult = CString(STRING(IDS_EMAILSYSTEM_MESSAGE_PREFIX_FORMAT)) + SPACE + STRING(IDS_EMAILSYSTEM_ERROR_FAILED_RECIPIENTS_NOTAVAILABLE);
				delete pSMTPMessage;
				return szResult;
			}
			for (pSMTPMessage->m_From = cAddress, pSMTPMessage->m_sSubject = pszSubject, (m_nOptions & SMTP_OPTIONS_ENCODING_HTML) ? pSMTPMessage->AddHTMLBody(ConvertTextToHTML(pszMessage)) : pSMTPMessage->AddTextBody(pszMessage), pSMTPMessage->SetCharset(m_szCharsetEncoding), pSMTPMessage->SetMime((m_nOptions & SMTP_OPTIONS_ENCODING_MIME) ? TRUE : FALSE), pSMTPMessage->ParseMultipleRecipients(pszRecipients, pSMTPMessage->m_To), pSMTPMessage->AddMultipleAttachments(pszAttachments), cSMTPMessageAttachment.SetCharset(m_szCharsetEncoding), pSMTPMessage->m_Priority = (nPriority != CSMTPMessage::NoPriority) ? nPriority : m_nPriority, pSMTPMessage->m_sXMailer.Empty(), pSMTPMessage->m_dwDSN = CSMTPMessage::DSN_NOT_SPECIFIED; m_nOptions & SMTP_OPTIONS_DSN; )
			{
				pSMTPMessage->m_DSNReturnType = (m_nOptions & SMTP_OPTIONS_DSN_HEADERS) ? CSMTPMessage::HeadersOnly : CSMTPMessage::FullEmail;
				if (m_nOptions & SMTP_OPTIONS_DSN_SUCCESS) pSMTPMessage->m_dwDSN |= CSMTPMessage::DSN_SUCCESS;
				if (m_nOptions & SMTP_OPTIONS_DSN_FAILURE) pSMTPMessage->m_dwDSN |= CSMTPMessage::DSN_FAILURE;
				if (m_nOptions & SMTP_OPTIONS_DSN_DELAY) pSMTPMessage->m_dwDSN |= CSMTPMessage::DSN_DELAY;
				break;
			}
			if (m_nOptions & SMTP_OPTIONS_MDN)
			{
				pSMTPMessage->m_MessageDispositionEmailAddresses.Add(m_szAccountAddress);
			}
			if (m_nOptions & SMTP_OPTIONS_AUTOCONNECT)
			{
				m_cConnection.ConnectToInternet();
			}
			for (m_cConnection.SetSSLProtocol(m_nSSLProtocol), m_cConnection.SetBindAddress((m_szConnectBoundIP != STRING(IDS_EMAILSYSTEM_ADDRESSBINDING_ANY)) ? m_szConnectBoundIP : EMPTYSTRING), m_cConnection.Connect(m_szServer, m_nAuthentication, m_szAccountLogin, m_szAccountPassword, m_nPort, m_nType, pSMTPMessage->m_dwDSN), m_cConnection.SendMessage(*pSMTPMessage); m_cConnection.IsConnected(); )
			{
				m_cConnection.Disconnect(TRUE);
				break;
			}
			if (m_nOptions & SMTP_OPTIONS_AUTOCONNECT)
			{
				m_cConnection.CloseInternetConnection();
			}
			delete pSMTPMessage;
			return szResult;
		}
		catch (CSMTPException *pException)
		{
			for (szResult = CString(STRING(IDS_EMAILSYSTEM_MESSAGE_PREFIX_FORMAT)) + SPACE + pException->GetErrorMessage(); szResult.Right(1) == CR || szResult.Right(1) == EOL; )
			{
				szResult = szResult.Left(szResult.GetLength() - 1);
			}
			if (m_cConnection.IsConnected())
			{
				m_cConnection.Disconnect(FALSE);
			}
			pException->Delete();
		}
		delete pSMTPMessage;
		return szResult;
	}
	return(CString(STRING(IDS_EMAILSYSTEM_MESSAGE_PREFIX_FORMAT)) + SPACE + STRING(IDS_EMAILSYSTEM_ERROR_MEMORY_FAILURE));
}

CString CEMailSystem::ConvertTextToHTML(LPCTSTR pszText) CONST
{
	INT  nPos[2];
	CString  szText;

	for (szText = pszText, nPos[0] = 0; (nPos[1] = szText.Mid(nPos[0]).Find(CString(CR) + EOL)) >= 0; nPos[0] += nPos[1] + lstrlen(STRING(IDS_EMAILMESSAGE_HTML_NEWLINE)))
	{
		szText = szText.Left(nPos[0] + nPos[1]) + STRING(IDS_EMAILMESSAGE_HTML_NEWLINE) + szText.Mid(nPos[0] + 1 + nPos[1] + 1);
	}
	for (nPos[0] = 0; (nPos[1] = szText.Mid(nPos[0]).Find(CR)) >= 0; nPos[0] += nPos[1] + lstrlen(STRING(IDS_EMAILMESSAGE_HTML_NEWLINE)))
	{
		szText = szText.Left(nPos[0] + nPos[1]) + STRING(IDS_EMAILMESSAGE_HTML_NEWLINE) + szText.Mid(nPos[0] + nPos[1] + 1);
	}
	for (nPos[0] = 0; (nPos[1] = szText.Mid(nPos[0]).Find(EOL)) >= 0; nPos[0] += nPos[1] + lstrlen(STRING(IDS_EMAILMESSAGE_HTML_NEWLINE)))
	{
		szText = szText.Left(nPos[0] + nPos[1]) + STRING(IDS_EMAILMESSAGE_HTML_NEWLINE) + szText.Mid(nPos[0] + nPos[1] + 1);
	}
	return szText;
}

BOOL CEMailSystem::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nPassword;
	CCryptographyTools  cCryptographyTools;

	sData.cbServer = (m_szServer.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAccountName = (m_szAccountName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAccountAddress = (m_szAccountAddress.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAccountLogin = (m_szAccountLogin.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAccountPassword = cCryptographyTools.EncryptText(m_szAccountPassword, nPassword);
	sData.cbCharsetEncoding = (m_szCharsetEncoding.GetLength() + 1)*sizeof(TCHAR);
	sData.cbConnectBoundIP = (m_szConnectBoundIP.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbServer + sData.cbAccountName + sData.cbAccountAddress + sData.cbAccountLogin + max(sData.cbAccountPassword, 0) + sData.cbCharsetEncoding + sData.cbConnectBoundIP)), sData.nType = m_nType, sData.nPort = m_nPort, sData.nAuthentication = m_nAuthentication, sData.nPriority = m_nPriority, sData.nOptions = m_nOptions; nInfo.GetSize() == sData.cbSize && sData.cbAccountPassword > 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szServer, sData.cbServer);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbServer), (LPCTSTR)m_szAccountName, sData.cbAccountName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAccountName), (LPCTSTR)m_szAccountAddress, sData.cbAccountAddress);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAccountAddress), (LPCTSTR)m_szAccountLogin, sData.cbAccountLogin);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAccountLogin), nPassword.GetData(), sData.cbAccountPassword);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAccountPassword), (LPCTSTR)m_szCharsetEncoding, sData.cbCharsetEncoding);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbCharsetEncoding), (LPCTSTR)m_szConnectBoundIP, sData.cbConnectBoundIP);
		return TRUE;
	}
	return FALSE;
}

BOOL CEMailSystem::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nPassword;
	CCryptographyTools  cCryptographyTools;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbServer + sData.cbAccountName + sData.cbAccountAddress + sData.cbAccountLogin + sData.cbAccountPassword + sData.cbCharsetEncoding + sData.cbConnectBoundIP && sData.cbServer > 0 && sData.cbAccountName > 0 && sData.cbAccountAddress > 0 && sData.cbAccountLogin > 0 && sData.cbAccountPassword > 0 && sData.cbCharsetEncoding > 0 && sData.cbConnectBoundIP > 0; )
	{
		nPassword.SetSize(sData.cbAccountPassword);
		CopyMemory(m_szServer.GetBufferSetLength(STRINGCHARS(sData.cbServer)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbServer));
		CopyMemory(m_szAccountName.GetBufferSetLength(STRINGCHARS(sData.cbAccountName)), nInfo.GetData() + (cbData = cbData + sData.cbServer), STRINGBYTES(sData.cbAccountName));
		CopyMemory(m_szAccountAddress.GetBufferSetLength(STRINGCHARS(sData.cbAccountAddress)), nInfo.GetData() + (cbData = cbData + sData.cbAccountName), STRINGBYTES(sData.cbAccountAddress));
		CopyMemory(m_szAccountLogin.GetBufferSetLength(STRINGCHARS(sData.cbAccountLogin)), nInfo.GetData() + (cbData = cbData + sData.cbAccountAddress), STRINGBYTES(sData.cbAccountLogin));
		CopyMemory(nPassword.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbAccountLogin), sData.cbAccountPassword);
		CopyMemory(m_szCharsetEncoding.GetBufferSetLength(STRINGCHARS(sData.cbCharsetEncoding)), nInfo.GetData() + (cbData = cbData + sData.cbAccountPassword), STRINGBYTES(sData.cbCharsetEncoding));
		CopyMemory(m_szConnectBoundIP.GetBufferSetLength(STRINGCHARS(sData.cbConnectBoundIP)), nInfo.GetData() + (cbData = cbData + sData.cbCharsetEncoding), STRINGBYTES(sData.cbConnectBoundIP));
		m_nType = sData.nType;
		m_nPort = sData.nPort;
		m_nAuthentication = sData.nAuthentication;
		m_nPriority = sData.nPriority;
		m_nOptions = sData.nOptions;
		m_szServer.ReleaseBuffer();
		m_szAccountName.ReleaseBuffer();
		m_szAccountAddress.ReleaseBuffer();
		m_szAccountLogin.ReleaseBuffer();
		m_szCharsetEncoding.ReleaseBuffer();
		m_szConnectBoundIP.ReleaseBuffer();
		return cCryptographyTools.DecryptText(nPassword, m_szAccountPassword);
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CEMailSystem::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CEMailSystem::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CEMailSystemConfigurationDialog dialog

IMPLEMENT_DYNCREATE(CEMailSystemConfigurationDialog, CLocaleDialog)

CEMailSystemConfigurationDialog::CEMailSystemConfigurationDialog(CWnd *pParentWnd) : CLocaleDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CEMailSystemConfigurationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT_PTR CEMailSystemConfigurationDialog::DoModal(CString &szServer, CSMTPConnection::ConnectionType &nType, CSMTPConnection::AuthenticationMethod &nAuthentication, CSMTPConnection::SSLProtocol &nSSLProtocol, CSMTPMessage::PRIORITY &nPriority, UINT &nOptions, UINT &nPort, CString &szConnectIP, CString &szCharsetEncoding, CString &szAccountName, CString &szAccountAddress, CString &szAccountLogin, CString &szAccountPassword)
{
	INT_PTR  nResult;

	for (m_szServer = szServer, m_nType = nType, m_nAuthentication = nAuthentication, m_nSSLProtocol = nSSLProtocol, m_nPriority = nPriority, m_nOptions = nOptions, m_nPort = nPort, m_szConnectIP = szConnectIP, m_szCharsetEncoding = szCharsetEncoding, m_szAccountName = szAccountName, m_szAccountAddress = szAccountAddress, m_szAccountLogin = szAccountLogin, m_szAccountPassword = szAccountPassword; (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		szServer = m_szServer;
		szAccountName = m_szAccountName;
		szAccountAddress = m_szAccountAddress;
		szAccountLogin = m_szAccountLogin;
		szAccountPassword = m_szAccountPassword;
		szCharsetEncoding = m_szCharsetEncoding;
		szConnectIP = m_szConnectIP;
		nPort = m_nPort;
		nType = m_nType;
		nOptions = m_nOptions;
		nPriority = m_nPriority;
		nSSLProtocol = m_nSSLProtocol;
		nAuthentication = m_nAuthentication;
		break;
	}
	return nResult;
}

VOID CEMailSystemConfigurationDialog::EnumAuthenticationMethods()
{
	INT  nMethod;
	INT  nMethods;

	for (nMethod = 0, nMethods = MAXEMAILSYSTEMAUTHENTICATIONMETHOD - MINEMAILSYSTEMAUTHENTICATIONMETHOD; nMethod <= nMethods; nMethod++)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINEMAILSYSTEMAUTHENTICATIONMETHOD + nMethod));
	}
	SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_AUTHENTICATION_LOGIN)));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION_STATIC)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_GETCOUNT) > 0);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_GETCOUNT) > 0);
}

VOID CEMailSystemConfigurationDialog::EnumConnectionTypes()
{
	INT  nType;
	INT  nTypes;

	for (nType = 0, nTypes = MAXEMAILSYSTEMCONNECTIONTYPE - MINEMAILSYSTEMCONNECTIONTYPE; nType <= nTypes; nType++)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINEMAILSYSTEMCONNECTIONTYPE + nType));
	}
	SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_PLAINTEXT)));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE_STATIC)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_GETCOUNT) > 0);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_GETCOUNT) > 0);
}

VOID CEMailSystemConfigurationDialog::EnumSSLProtocols()
{
	INT  nProtocol;
	INT  nProtocols;

	for (nProtocol = 0, nProtocols = MAXEMAILSYSTEMSSLPROTOCOL - MINEMAILSYSTEMSSLPROTOCOL; nProtocol <= nProtocols; nProtocol++)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINEMAILSYSTEMSSLPROTOCOL + nProtocol));
	}
	SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_OSDEFAULT)));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL_STATIC)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_GETCOUNT) > 0);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_GETCOUNT) > 0);
}

VOID CEMailSystemConfigurationDialog::EnumIPAddresses()
{
	INT  nAddress;
	INT  nAddresses;
	CStringArray  szAddresses;

	for (nAddress = 0, nAddresses = CNetworkBrowseService::EnumHostAddresses(szAddresses, AF_UNSPEC, FALSE), SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_ADDRESSBINDING_ANY)); nAddress < nAddresses; nAddress++)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szAddresses.GetAt(nAddress));
	}
	SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_ADDRESSBINDING_ANY)));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO_STATIC)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_GETCOUNT) > 0);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_GETCOUNT) > 0);
}

VOID CEMailSystemConfigurationDialog::EnumEncodings()
{
	INT  nEncoding;
	INT  nEncodings;

	for (nEncoding = 0, nEncodings = MAXEMAILSYSTEMENCODING - MINEMAILSYSTEMENCODING; nEncoding <= nEncodings; nEncoding++)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINEMAILSYSTEMENCODING + nEncoding));
	}
	SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_ENCODING_WESTERNEUROPE_WINDOWS)));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING_STATIC)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, CB_GETCOUNT) > 0);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, CB_GETCOUNT) > 0);
}

VOID CEMailSystemConfigurationDialog::EnumPriorities()
{
	INT  nPriority;
	INT  nPriorities;

	for (nPriority = 0, nPriorities = MAXEMAILSYSTEMPRIORITY - MINEMAILSYSTEMPRIORITY; nPriority <= nPriorities; nPriority++)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINEMAILSYSTEMPRIORITY + nPriority));
	}
	SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_PRIORITY_NORMAL)));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY_STATIC)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, CB_GETCOUNT) > 0);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY)->EnableWindow(SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, CB_GETCOUNT) > 0);
}

VOID CEMailSystemConfigurationDialog::ShowSettings()
{
	INT  nIndex;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)TranslateAuthenticationMethod(m_nAuthentication))) >= 0)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_SETCURSEL, nIndex);
	}
	if ((nIndex = (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)TranslateConnectionType(m_nType))) >= 0)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_SETCURSEL, nIndex);
	}
	if ((nIndex = (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)TranslateSSLProtocol(m_nSSLProtocol))) >= 0)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_SETCURSEL, nIndex);
	}
	if ((nIndex = (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)TranslateCharsetEncoding(m_szCharsetEncoding))) >= 0)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, CB_SETCURSEL, nIndex);
	}
	if ((nIndex = (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szConnectIP)) >= 0)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, CB_SETCURSEL, nIndex);
	}
	if ((nIndex = (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)TranslatePriority(m_nPriority))) >= 0)
	{
		SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, CB_SETCURSEL, nIndex);
	}
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_AUTOCONNECT, (m_nOptions & SMTP_OPTIONS_AUTOCONNECT) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MIMEENCODED, (m_nOptions & SMTP_OPTIONS_ENCODING_MIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_HTMLENCODED, (m_nOptions & SMTP_OPTIONS_ENCODING_HTML) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN, (m_nOptions & SMTP_OPTIONS_DSN) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS, (m_nOptions & SMTP_OPTIONS_DSN_SUCCESS) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE, (m_nOptions & SMTP_OPTIONS_DSN_FAILURE) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY, (m_nOptions & SMTP_OPTIONS_DSN_DELAY) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS, (m_nOptions & SMTP_OPTIONS_DSN_HEADERS) ? TRUE : FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MDN, (m_nOptions & SMTP_OPTIONS_MDN) ? TRUE : FALSE);
	Spinbox_SetRange(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT), EMAILCONFIGURATION_MINIMUMPORT, EMAILCONFIGURATION_MAXIMUMPORT);
	Spinbox_SetPos(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT), m_nPort);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME)->SetWindowText(m_szAccountName);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS)->SetWindowText(m_szAccountAddress);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->SetWindowText((m_nAuthentication != CSMTPConnection::AUTH_NONE) ? m_szAccountLogin : EMPTYSTRING);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->SetWindowText((m_nAuthentication != CSMTPConnection::AUTH_NONE) ? m_szAccountPassword : EMPTYSTRING);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS)->SetWindowText(m_szServer);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS_STATIC)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME_STATIC)->EnableWindow(m_nAuthentication != CSMTPConnection::AUTH_NONE);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->EnableWindow(m_nAuthentication != CSMTPConnection::AUTH_NONE);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD_STATIC)->EnableWindow(m_nAuthentication != CSMTPConnection::AUTH_NONE);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->EnableWindow(m_nAuthentication != CSMTPConnection::AUTH_NONE);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS_STATIC)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT_STATIC)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_AUTOCONNECT)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MIMEENCODED)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_HTMLENCODED)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MDN)->EnableWindow();
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
}

CString CEMailSystemConfigurationDialog::TranslateConnectionType(CSMTPConnection::ConnectionType nType) CONST
{
	return((nType == CSMTPConnection::PlainText) ? STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_PLAINTEXT) : ((nType == CSMTPConnection::SSL_TLS) ? STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_SSLTLS) : ((nType == CSMTPConnection::STARTTLS) ? STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_STARTTLS) : ((nType == CSMTPConnection::AutoUpgradeToSTARTTLS) ? STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_AUTOSTARTTLS) : EMPTYSTRING))));
}
CSMTPConnection::ConnectionType CEMailSystemConfigurationDialog::TranslateConnectionType(LPCTSTR pszType) CONST
{
	return((!lstrcmp(pszType, STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_PLAINTEXT))) ? CSMTPConnection::PlainText : ((!lstrcmp(pszType, STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_SSLTLS))) ? CSMTPConnection::SSL_TLS : ((!lstrcmp(pszType, STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_STARTTLS))) ? CSMTPConnection::STARTTLS : ((!lstrcmp(pszType, STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_AUTOSTARTTLS))) ? CSMTPConnection::AutoUpgradeToSTARTTLS : (CSMTPConnection::ConnectionType)0))));
}

CString CEMailSystemConfigurationDialog::TranslateAuthenticationMethod(CSMTPConnection::AuthenticationMethod nMethod) CONST
{
	return((nMethod == CSMTPConnection::AUTH_NONE) ? STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE) : ((nMethod == CSMTPConnection::AUTH_CRAM_MD5) ? STRING(IDS_EMAILSYSTEM_AUTHENTICATION_CRAM) : ((nMethod == CSMTPConnection::AUTH_LOGIN) ? STRING(IDS_EMAILSYSTEM_AUTHENTICATION_LOGIN) : ((nMethod == CSMTPConnection::AUTH_PLAIN) ? STRING(IDS_EMAILSYSTEM_AUTHENTICATION_PLAIN) : ((nMethod == CSMTPConnection::AUTH_NTLM) ? STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NTLM) : ((nMethod == CSMTPConnection::AUTH_AUTO) ? STRING(IDS_EMAILSYSTEM_AUTHENTICATION_AUTO) : EMPTYSTRING))))));
}
CSMTPConnection::AuthenticationMethod CEMailSystemConfigurationDialog::TranslateAuthenticationMethod(LPCTSTR pszMethod) CONST
{
	return((!lstrcmp(pszMethod, STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE))) ? CSMTPConnection::AUTH_NONE : ((!lstrcmp(pszMethod, STRING(IDS_EMAILSYSTEM_AUTHENTICATION_CRAM))) ? CSMTPConnection::AUTH_CRAM_MD5 : ((!lstrcmp(pszMethod, STRING(IDS_EMAILSYSTEM_AUTHENTICATION_LOGIN))) ? CSMTPConnection::AUTH_LOGIN : ((!lstrcmp(pszMethod, STRING(IDS_EMAILSYSTEM_AUTHENTICATION_PLAIN))) ? CSMTPConnection::AUTH_PLAIN : ((!lstrcmp(pszMethod, STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NTLM))) ? CSMTPConnection::AUTH_NTLM : ((!lstrcmp(pszMethod, STRING(IDS_EMAILSYSTEM_AUTHENTICATION_AUTO))) ? CSMTPConnection::AUTH_AUTO : (CSMTPConnection::AuthenticationMethod)0))))));
}

CString CEMailSystemConfigurationDialog::TranslateSSLProtocol(CSMTPConnection::SSLProtocol nProtocol) CONST
{
	return((nProtocol == CSMTPConnection::SSLv2orv3) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_V2ORV3) : ((nProtocol == CSMTPConnection::SSLv2) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_V2) : ((nProtocol == CSMTPConnection::SSLv3) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_V3) : ((nProtocol == CSMTPConnection::TLSv1) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSV1_0) : ((nProtocol == CSMTPConnection::TLSv1_1) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSV1_1) : ((nProtocol == CSMTPConnection::TLSv1_2) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSV1_2) : ((nProtocol == CSMTPConnection::AnyTLS) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSANY) : ((nProtocol == CSMTPConnection::OSDefault) ? STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_OSDEFAULT) : EMPTYSTRING))))))));
}
CSMTPConnection::SSLProtocol CEMailSystemConfigurationDialog::TranslateSSLProtocol(LPCTSTR pszProtocol) CONST
{
	return((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_V2ORV3))) ? CSMTPConnection::SSLv2orv3 : ((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_V2))) ? CSMTPConnection::SSLv2 : ((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_V3))) ? CSMTPConnection::SSLv3 : ((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSV1_0))) ? CSMTPConnection::TLSv1 : ((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSV1_1))) ? CSMTPConnection::TLSv1_1 : ((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSV1_2))) ? CSMTPConnection::TLSv1_2 : ((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_TLSANY))) ? CSMTPConnection::AnyTLS : ((!lstrcmp(pszProtocol, STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_OSDEFAULT))) ? CSMTPConnection::OSDefault : (CSMTPConnection::SSLProtocol)0))))))));
}

CString CEMailSystemConfigurationDialog::TranslatePriority(CSMTPMessage::PRIORITY nPriority) CONST
{
	return((nPriority == CSMTPMessage::NoPriority) ? STRING(IDS_EMAILSYSTEM_PRIORITY_NONE) : ((nPriority == CSMTPMessage::LowPriority) ? STRING(IDS_EMAILSYSTEM_PRIORITY_LOW) : ((nPriority == CSMTPMessage::NormalPriority) ? STRING(IDS_EMAILSYSTEM_PRIORITY_NORMAL) : ((nPriority == CSMTPMessage::HighPriority) ? STRING(IDS_EMAILSYSTEM_PRIORITY_HIGH) : EMPTYSTRING))));
}
CSMTPMessage::PRIORITY CEMailSystemConfigurationDialog::TranslatePriority(LPCTSTR pszPriority) CONST
{
	return((!lstrcmp(pszPriority, STRING(IDS_EMAILSYSTEM_PRIORITY_NONE))) ? CSMTPMessage::NoPriority : ((!lstrcmp(pszPriority, STRING(IDS_EMAILSYSTEM_PRIORITY_LOW))) ? CSMTPMessage::LowPriority : ((!lstrcmp(pszPriority, STRING(IDS_EMAILSYSTEM_PRIORITY_NORMAL))) ? CSMTPMessage::NormalPriority : ((!lstrcmp(pszPriority, STRING(IDS_EMAILSYSTEM_PRIORITY_HIGH))) ? CSMTPMessage::HighPriority : (CSMTPMessage::PRIORITY)0))));
}

CString CEMailSystemConfigurationDialog::TranslateCharsetEncoding(LPCTSTR pszEncoding) CONST
{
	INT  nEncoding;
	INT  nEncodings;

	for (nEncoding = 0, nEncodings = MAXEMAILSYSTEMENCODINGMNEMONIC - MINEMAILSYSTEMENCODINGMNEMONIC; nEncoding <= nEncodings; nEncoding++)
	{
		if (!lstrcmp(pszEncoding, STRING(MINEMAILSYSTEMENCODINGMNEMONIC + nEncoding))) return STRING(MINEMAILSYSTEMENCODING + nEncoding);
	}
	for (nEncoding = 0; nEncoding <= nEncodings; nEncoding++)
	{
		if (!lstrcmp(pszEncoding, STRING(MINEMAILSYSTEMENCODING + nEncoding))) return STRING(MINEMAILSYSTEMENCODINGMNEMONIC + nEncoding);
	}
	return EMPTYSTRING;
}

VOID CEMailSystemConfigurationDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME, (bCheck = CheckAccountPrivilege(PRIVILEGE_TOOLSEMAILOPTIONS_CHANGE)));
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_AUTOCONNECT, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MIMEENCODED, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_HTMLENCODED, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS, bCheck);
	AccessControl(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MDN, bCheck);
}

BOOL CEMailSystemConfigurationDialog::IsModified() CONST
{
	UINT  nOptions;
	CString  szType;
	CString  szServer;
	CString  szAccountName;
	CString  szAccountAddress;
	CString  szAccountLogin;
	CString  szAccountPassword;
	CString  szCharsetEncoding;
	CString  szAuthentication;
	CString  szSSLProtocol;
	CString  szConnectIP;
	CString  szPriority;

	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME)->GetWindowText(szAccountName);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS)->GetWindowText(szAccountAddress);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION)->GetWindowText(szAuthentication);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->GetWindowText(szAccountLogin);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->GetWindowText(szAccountPassword);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS)->GetWindowText(szServer);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE)->GetWindowText(szType);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL)->GetWindowText(szSSLProtocol);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING)->GetWindowText(szCharsetEncoding);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO)->GetWindowText(szConnectIP);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY)->GetWindowText(szPriority);
	nOptions = (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_AUTOCONNECT)) ? SMTP_OPTIONS_AUTOCONNECT : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MIMEENCODED)) ? SMTP_OPTIONS_ENCODING_MIME : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_HTMLENCODED)) ? SMTP_OPTIONS_ENCODING_HTML : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN)) ? SMTP_OPTIONS_DSN : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS)) ? SMTP_OPTIONS_DSN_SUCCESS : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE)) ? SMTP_OPTIONS_DSN_FAILURE : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY)) ? SMTP_OPTIONS_DSN_DELAY : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS)) ? SMTP_OPTIONS_DSN_HEADERS : 0;
	nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MDN)) ? SMTP_OPTIONS_MDN : 0;
	return((szAccountName != m_szAccountName || szAccountAddress != m_szAccountAddress || TranslateAuthenticationMethod(szAuthentication) != m_nAuthentication || szAccountLogin != m_szAccountLogin || szAccountPassword != m_szAccountPassword || szServer != m_szServer || Spinbox_GetPos(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT)) != m_nPort || TranslateConnectionType(szType) != m_nType || TranslateSSLProtocol(szSSLProtocol) != m_nSSLProtocol || szConnectIP != m_szConnectIP || TranslateCharsetEncoding(szCharsetEncoding) != m_szCharsetEncoding || TranslatePriority(szPriority) != m_nPriority || nOptions != m_nOptions) ? TRUE : FALSE);
}

BOOL CEMailSystemConfigurationDialog::Check(BOOL bModified) CONST
{
	CString  szAuthentication;

	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION)->GetWindowText(szAuthentication);
	return((GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS)->GetWindowTextLength() > 0 && ((szAuthentication == STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE) && !GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->GetWindowTextLength() && !GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->GetWindowTextLength()) || (szAuthentication != STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE) && GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->GetWindowTextLength() > 0)) && GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

HGLOBAL CEMailSystemConfigurationDialog::LoadLocaleDialogTemplate(UINT nDialogID) CONST
{
	return LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID));
}
HGLOBAL CEMailSystemConfigurationDialog::LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST
{
	HMODULE  hModule;
	HRSRC  hDialogTemplate;

	return(((hDialogTemplate = FindResourceEx((hModule = GetLibraryModuleInstance()), RT_DIALOG, pszDialogName, GetLanguageID())) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hDialogTemplate) : (LPVOID)NULL);
}

void CEMailSystemConfigurationDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEMailSystemConfigurationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEMailSystemConfigurationDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CEMailSystemConfigurationDialog)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_AUTOCONNECT, OnAutoConnect)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MIMEENCODED, OnMIMEEncoding)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_HTMLENCODED, OnHTMLEncoding)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN, OnDSN)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS, OnDSNSuccess)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE, OnDSNFailure)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY, OnDSNDelay)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS, OnDSNHeaders)
	ON_BN_CLICKED(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MDN, OnMDN)
	ON_EN_CHANGE(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME, OnEditchangeAccountName)
	ON_EN_CHANGE(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS, OnEditchangeAccountAddress)
	ON_EN_CHANGE(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME, OnEditchangeAccountLogin)
	ON_EN_CHANGE(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD, OnEditchangeAccountPassword)
	ON_EN_CHANGE(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS, OnEditchangeServer)
	ON_CBN_SELCHANGE(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, OnSelchangeAuthentication)
	ON_CBN_SELCHANGE(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, OnSelchangeConnectionType)
	ON_CBN_SELCHANGE(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, OnSelchangeSSLProtocol)
	ON_CBN_SELCHANGE(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING, OnSelchangeEncoding)
	ON_CBN_SELCHANGE(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO, OnSelchangeConnectIP)
	ON_CBN_SELCHANGE(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY, OnSelchangePriority)
	ON_CONTROL(SBXN_CHANGE, IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT, OnSpinchangePort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEMailSystemConfigurationDialog message handlers

BOOL CEMailSystemConfigurationDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	EnumAuthenticationMethods();
	EnumConnectionTypes();
	EnumSSLProtocols();
	EnumIPAddresses();
	EnumPriorities();
	EnumEncodings();
	ShowSettings();
	AdjustToPrivileges();
	return TRUE;
}

void CEMailSystemConfigurationDialog::OnAutoConnect()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnMIMEEncoding()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnHTMLEncoding()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnDSN()
{
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS, FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE, FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY, FALSE);
	CheckDlgButton(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS, FALSE);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS)->EnableWindow(IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnDSNSuccess()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnDSNFailure()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnDSNDelay()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnDSNHeaders()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnMDN()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnEditchangeAccountName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnEditchangeAccountAddress()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnEditchangeAccountLogin()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnEditchangeAccountPassword()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnEditchangeServer()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnSelchangeAuthentication()
{
	CString  szAuthentication;

	if ((szAuthentication = Combobox_GetText(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION), (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION, CB_GETCURSEL))) == STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE))
	{
		GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->SetWindowText(EMPTYSTRING);
	}
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME_STATIC)->EnableWindow(szAuthentication != STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->EnableWindow(szAuthentication != STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD_STATIC)->EnableWindow(szAuthentication != STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE));
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->EnableWindow(szAuthentication != STRING(IDS_EMAILSYSTEM_AUTHENTICATION_NONE));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnSelchangeConnectionType()
{
	if (Combobox_GetText(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE), (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_GETCURSEL)) == STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_PLAINTEXT))
	{
		if (Combobox_GetText(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL), (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_GETCURSEL)) != STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_OSDEFAULT))
		{
			SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_OSDEFAULT)));
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnSelchangeSSLProtocol()
{
	if (Combobox_GetText(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL), (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL, CB_GETCURSEL)) != STRING(IDS_EMAILSYSTEM_SSLPROTOCOL_OSDEFAULT))
	{
		if (Combobox_GetText(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE), (INT)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_GETCURSEL)) == STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_PLAINTEXT))
		{
			SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EMAILSYSTEM_CONNECTIONTYPE_SSLTLS)));
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnSelchangeEncoding()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnSelchangeConnectIP()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnSelchangePriority()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnSpinchangePort()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEMailSystemConfigurationDialog::OnOK()
{
	CString  szType;
	CString  szPriority;
	CString  szSSLProtocol;
	CString  szAuthentication;
	CString  szCharsetEncoding;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME)->GetWindowText(m_szAccountName);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS)->GetWindowText(m_szAccountAddress);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME)->GetWindowText(m_szAccountLogin);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD)->GetWindowText(m_szAccountPassword);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION)->GetWindowText(szAuthentication);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS)->GetWindowText(m_szServer);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE)->GetWindowText(szType);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL)->GetWindowText(szSSLProtocol);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING)->GetWindowText(szCharsetEncoding);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO)->GetWindowText(m_szConnectIP);
	GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY)->GetWindowText(szPriority);
	m_nOptions = (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_AUTOCONNECT)) ? SMTP_OPTIONS_AUTOCONNECT : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MIMEENCODED)) ? SMTP_OPTIONS_ENCODING_MIME : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_HTMLENCODED)) ? SMTP_OPTIONS_ENCODING_HTML : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN)) ? SMTP_OPTIONS_DSN : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS)) ? SMTP_OPTIONS_DSN_SUCCESS : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE)) ? SMTP_OPTIONS_DSN_FAILURE : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY)) ? SMTP_OPTIONS_DSN_DELAY : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS)) ? SMTP_OPTIONS_DSN_HEADERS : 0;
	m_nOptions |= (IsDlgButtonChecked(IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MDN)) ? SMTP_OPTIONS_MDN : 0;
	m_nPort = (UINT)Spinbox_GetPos(GetDlgItem(IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT));
	m_szCharsetEncoding = TranslateCharsetEncoding(szCharsetEncoding);
	m_nAuthentication = TranslateAuthenticationMethod(szAuthentication);
	m_nSSLProtocol = TranslateSSLProtocol(szSSLProtocol);
	m_nPriority = TranslatePriority(szPriority);
	m_nType = TranslateConnectionType(szType);
	CLocaleDialog::OnOK();
}
