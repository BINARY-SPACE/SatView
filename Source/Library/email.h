// EMAIL.H : E-Mail Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the e-mail related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2015/11/14 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __EMAIL_H__
#define __EMAIL_H__

#ifndef RC_INVOKED
#include "language.h"
#include "profiles.h"

#include "SMTP.h"
#endif

#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CEMailSystem

// Specify the various e-mail options
#define SMTP_OPTIONS_NONE   0
#define SMTP_OPTIONS_AUTOCONNECT   (1<<0)
#define SMTP_OPTIONS_ENCODING_MIME   (1<<1)
#define SMTP_OPTIONS_ENCODING_HTML   (1<<2)
#define SMTP_OPTIONS_DSN   (1<<3)
#define SMTP_OPTIONS_DSN_SUCCESS   (1<<4)
#define SMTP_OPTIONS_DSN_FAILURE   (1<<5)
#define SMTP_OPTIONS_DSN_DELAY   (1<<6)
#define SMTP_OPTIONS_DSN_HEADERS   (1<<7)
#define SMTP_OPTIONS_MDN   (1<<8)
// Specify the default e-mail port
#define SMTP_DEFAULT_PORT   25

class AFX_EXT_CLASS CEMailSystem : public CObject
{
	// Construction
public:
	CEMailSystem();
	~CEMailSystem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbServer;
		INT  cbAccountName;
		INT  cbAccountAddress;
		INT  cbAccountLogin;
		INT  cbAccountPassword;
		INT  cbCharsetEncoding;
		INT  cbConnectBoundIP;
		CSMTPConnection::ConnectionType  nType;
		CSMTPConnection::AuthenticationMethod   nAuthentication;
		CSMTPConnection::SSLProtocol  nSSLProtocol;
		CSMTPMessage::PRIORITY  nPriority;
		UINT  nOptions;
		UINT  nPort;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szServer;
	CString  m_szAccountName;
	CString  m_szAccountAddress;
	CString  m_szAccountLogin;
	CString  m_szAccountPassword;
	CString  m_szCharsetEncoding;
	CString  m_szConnectBoundIP;
	CSMTPConnection::ConnectionType  m_nType;
	CSMTPConnection::AuthenticationMethod   m_nAuthentication;
	CSMTPConnection::SSLProtocol  m_nSSLProtocol;
	CSMTPMessage::PRIORITY  m_nPriority;
	UINT  m_nOptions;
	UINT  m_nPort;
private:
	CSMTPConnection  m_cConnection;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	VOID SetServer(LPCTSTR pszServer);
	CString GetServer() CONST;
	VOID SetSecurity(CSMTPConnection::ConnectionType nType);
	CSMTPConnection::ConnectionType GetSecurity() CONST;
	VOID SetAuthentication(CSMTPConnection::AuthenticationMethod nMethod);
	CSMTPConnection::AuthenticationMethod GetAuthentication() CONST;
	VOID SetSSLProtocol(CSMTPConnection::SSLProtocol nProtocol);
	CSMTPConnection::SSLProtocol GetSSLProtocol() CONST;
	VOID SetPriority(CSMTPMessage::PRIORITY nPriority);
	CSMTPMessage::PRIORITY GetPriority() CONST;
	VOID SetExtraOptions(UINT nOptions);
	UINT GetExtraOptions() CONST;
	VOID SetPort(UINT nPort);
	UINT GetPort() CONST;
	VOID SetCharsetEncoding(LPCTSTR pszEncoding);
	CString GetCharsetEncoding() CONST;
	VOID SetConnectIPAddress(LPCTSTR pszIPAddress);
	CString GetConnectIPAddress() CONST;
	VOID SetAccountName(LPCTSTR pszName);
	CString GetAccountName() CONST;
	VOID SetAccountAddress(LPCTSTR pszAddress);
	CString GetAccountAddress() CONST;
	VOID SetAccountLogin(LPCTSTR pszUserName);
	CString GetAccountLogin() CONST;
	VOID SetAccountPassword(LPCTSTR pszPassword);
	CString GetAccountPassword() CONST;

	CString Send(LPCTSTR pszSubject, LPCTSTR pszMessage, LPCTSTR pszRecipients, LPCTSTR pszAttachments, CSMTPMessage::PRIORITY nPriority = CSMTPMessage::NoPriority);

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

	BOOL Lock();
	BOOL Unlock();

private:
	CString ConvertTextToHTML(LPCTSTR pszText) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEMailSystemConfigurationDialog dialog

#define IDC_EMAILSYSTEM_CONFIGURATION_DETAILS   100
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES   101
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME_STATIC   102
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_NAME   103
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS_STATIC   104
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_ADDRESS   105
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION_STATIC   106
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_AUTHENTICATION   107
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME_STATIC   108
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_USERNAME   109
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD_STATIC   110
#define IDC_EMAILSYSTEM_CONFIGURATION_ACCOUNTPROPERTIES_PASSWORD   111
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES   112
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS_STATIC   113
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_ADDRESS   114
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT_STATIC   115
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_PORT   116
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE_STATIC   117
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_CONNECTIONTYPE   118
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL_STATIC   119
#define IDC_EMAILSYSTEM_CONFIGURATION_SERVERPROPERTIES_SSLPROTOCOL   120
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS   121
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_AUTOCONNECT   122
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO_STATIC   123
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_BINDTO   124
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING_STATIC   125
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_ENCODING   126
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MIMEENCODED   127
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_HTMLENCODED   128
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY_STATIC   129
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_PRIORITY   130
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN   131
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_SUCCESS   132
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_FAILURE   133
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_DELAY   134
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_DSN_HEADERS   135
#define IDC_EMAILSYSTEM_CONFIGURATION_MISCELLANEOUS_MDN   136

// Specify the e-mail configuration related settings
#define EMAILCONFIGURATION_MINIMUMPORT   1
#define EMAILCONFIGURATION_MAXIMUMPORT   65535
#define EMAILCONFIGURATION_DEFAULTPORT   SMTP_DEFAULT_PORT

class AFX_EXT_CLASS CEMailSystemConfigurationDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CEMailSystemConfigurationDialog)

	// Construction
public:
	CEMailSystemConfigurationDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szServer;
	CString  m_szAccountName;
	CString  m_szAccountAddress;
	CString  m_szAccountLogin;
	CString  m_szAccountPassword;
	CString  m_szCharsetEncoding;
	CString  m_szConnectIP;
	CSMTPConnection::ConnectionType  m_nType;
	CSMTPConnection::AuthenticationMethod  m_nAuthentication;
	CSMTPConnection::SSLProtocol  m_nSSLProtocol;
	CSMTPMessage::PRIORITY  m_nPriority;
	UINT  m_nOptions;
	UINT  m_nPort;

	// Operations
private:
	VOID EnumAuthenticationMethods();
	VOID EnumConnectionTypes();
	VOID EnumSSLProtocols();
	VOID EnumIPAddresses();
	VOID EnumEncodings();
	VOID EnumPriorities();

	VOID ShowSettings();

	CString TranslateConnectionType(CSMTPConnection::ConnectionType nType) CONST;
	CSMTPConnection::ConnectionType TranslateConnectionType(LPCTSTR pszType) CONST;
	CString TranslateAuthenticationMethod(CSMTPConnection::AuthenticationMethod nMethod) CONST;
	CSMTPConnection::AuthenticationMethod TranslateAuthenticationMethod(LPCTSTR pszMethod) CONST;
	CString TranslateSSLProtocol(CSMTPConnection::SSLProtocol nProtocol) CONST;
	CSMTPConnection::SSLProtocol TranslateSSLProtocol(LPCTSTR pszProtocol) CONST;
	CString TranslatePriority(CSMTPMessage::PRIORITY nPriority) CONST;
	CSMTPMessage::PRIORITY TranslatePriority(LPCTSTR pszPriority) CONST;
	CString TranslateCharsetEncoding(LPCTSTR pszEncoding) CONST;

	HGLOBAL LoadLocaleDialogTemplate(UINT nDialogID) CONST;
	HGLOBAL LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST;

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CEMailSystemConfigurationDialog)
	enum { IDD = IDD_EMAILSYSTEM_CONFIGURATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEMailSystemConfigurationDialog)
public:
	virtual INT_PTR DoModal(CString &szServer, CSMTPConnection::ConnectionType &nType, CSMTPConnection::AuthenticationMethod &nAuthentication, CSMTPConnection::SSLProtocol &nSSLProtocol, CSMTPMessage::PRIORITY &nPriority, UINT &nOptions, UINT &nPort, CString &szConnectIP, CString &szCharsetEncoding, CString &szAccountName, CString &szAccountAddress, CString &szAccountLogin, CString &szAccountPassword);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEMailSystemConfigurationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAutoConnect();
	afx_msg void OnMIMEEncoding();
	afx_msg void OnHTMLEncoding();
	afx_msg void OnDSN();
	afx_msg void OnDSNSuccess();
	afx_msg void OnDSNFailure();
	afx_msg void OnDSNDelay();
	afx_msg void OnDSNHeaders();
	afx_msg void OnMDN();
	afx_msg void OnEditchangeAccountName();
	afx_msg void OnEditchangeAccountAddress();
	afx_msg void OnEditchangeAccountLogin();
	afx_msg void OnEditchangeAccountPassword();
	afx_msg void OnEditchangeServer();
	afx_msg void OnSelchangeAuthentication();
	afx_msg void OnSelchangeConnectionType();
	afx_msg void OnSelchangeSSLProtocol();
	afx_msg void OnSelchangeEncoding();
	afx_msg void OnSelchangeConnectIP();
	afx_msg void OnSelchangePriority();
	afx_msg void OnSpinchangePort();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __EMAIL_H__
