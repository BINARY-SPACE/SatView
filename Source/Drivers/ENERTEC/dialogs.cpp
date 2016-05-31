// DIALOGS.CPP : Dialogs Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the dialogs related
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
// CIODeviceDialog dialog

IMPLEMENT_DYNCREATE(CIODeviceDialog, CLocaleDialog)

CIODeviceDialog::CIODeviceDialog(CWnd *pParentWnd) : CLocaleDialog()
{
	m_pParentWnd = pParentWnd;
}

CString CIODeviceDialog::TranslateToFullClientName(LPCTSTR pszName, LPCTSTR pszAddress) CONST
{
	return(pszName + CString(EOL) + pszAddress);
}

CString CIODeviceDialog::TranslateToClientName(LPCTSTR pszFullName) CONST
{
	INT  nPos;
	CString  szFullName(pszFullName);

	return(((nPos = szFullName.Find(EOL)) >= 0) ? szFullName.Left(nPos) : szFullName);
}

CString CIODeviceDialog::TranslateToClientAddress(LPCTSTR pszFullName) CONST
{
	INT  nPos;
	CString  szFullName(pszFullName);

	return(((nPos = szFullName.Find(EOL)) >= 0 && nPos < szFullName.GetLength() - 1) ? szFullName.Mid(nPos + 1) : EMPTYSTRING);
}

BOOL CIODeviceDialog::IsValidIPAddress(LPCTSTR pszAddress) CONST
{
	IN_ADDR  sAddress;

	return(InetPton(AF_INET, pszAddress, &sAddress) > 0 && sAddress.S_un.S_addr != 0);
}

HGLOBAL CIODeviceDialog::LoadLocaleDialogTemplate(UINT nDialogID) CONST
{
	return LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID));
}
HGLOBAL CIODeviceDialog::LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST
{
	HMODULE  hModule;
	HRSRC  hDialogTemplate;

	return(((hDialogTemplate = FindResourceEx((hModule = GetLibraryInstance()), RT_DIALOG, pszDialogName, GetLanguageID())) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hDialogTemplate) : (LPVOID)NULL);
}

void CIODeviceDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIODeviceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIODeviceDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CIODeviceDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIODeviceDialog message handlers


/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceDialog dialog

IMPLEMENT_DYNCREATE(CENERTECDeviceDialog, CIODeviceDialog)

CENERTECDeviceDialog::CENERTECDeviceDialog(CWnd *pParentWnd) : CIODeviceDialog(pParentWnd)
{
	LPVOID  pDialogTemplate;

	if ((pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CENERTECDeviceDialog::IDD))))
	{
		InitModalIndirect(pDialogTemplate);
		return;
	}
}

INT CENERTECDeviceDialog::DoModal(CENERTECDevice *pDevice, UINT nAllowedTypes, BOOL bReadOnly)
{
	INT  nResult;

	for (m_cDevice[0].Copy(pDevice), m_cDevice[1].Copy(pDevice), m_nAllowedTypes = nAllowedTypes, m_bReadOnly = bReadOnly; (nResult = (INT)CIODeviceDialog::DoModal()) == IDOK; )
	{
		pDevice->Copy(&m_cDevice[0]);
		break;
	}
	return nResult;
}

VOID CENERTECDeviceDialog::ShowDeviceProperties()
{
	UINT  nIPPort;
	UINT  nDeviceMode;
	UINT  nBufferSize;
	WORD  wAPIDFilter;
	WORD  wVCIDFilter;
	LONG  tCorrelationError;
	LONG  tCorrelationDelta;
	CString  szIPAddress;
	CTimeSpan  tTimeout;
	CTimeSpan  tInterval;
	SYSTEMTIME  tEpochTime;
	SOCKADDR_IN  sIPAddress;

	GetDlgItem(IDC_ENERTECDEVICE_NAME)->SetWindowText(m_cDevice[0].GetDeviceName());
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS)->SetWindowText((m_cDevice[0].GetIPAddress(szIPAddress, nIPPort)) ? (LPCTSTR)szIPAddress : EMPTYSTRING);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE, (((nDeviceMode = (m_cDevice[0].GetDeviceMode(nDeviceMode)) ? (m_nAllowedTypes & nDeviceMode) : m_nAllowedTypes) & IODEVICE_TYPE_CLIENT) && !m_cDevice[0].GetAPIDFilter(wAPIDFilter) && !m_cDevice[0].GetVCIDFilter(wVCIDFilter)) ? TRUE : FALSE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID, ((nDeviceMode & IODEVICE_TYPE_CLIENT) && m_cDevice[0].GetAPIDFilter(wAPIDFilter)) ? TRUE : FALSE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID, ((nDeviceMode & IODEVICE_TYPE_CLIENT) && m_cDevice[0].GetVCIDFilter(wVCIDFilter)) ? TRUE : FALSE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR, ((nDeviceMode & IODEVICE_TYPE_CLIENT) && m_cDevice[0].GetTimeCorrelation(tCorrelationError, tCorrelationDelta)) ? ((tCorrelationError != 0) ? TRUE : FALSE) : FALSE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA, ((nDeviceMode & IODEVICE_TYPE_CLIENT) && m_cDevice[0].GetTimeCorrelation(tCorrelationError, tCorrelationDelta)) ? ((tCorrelationDelta != 0) ? TRUE : FALSE) : FALSE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT, ((nDeviceMode & IODEVICE_TYPE_CLIENT) && m_cDevice[0].GetClockAdjustmentInterval(tInterval)) ? TRUE : FALSE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE, ((nDeviceMode & IODEVICE_TYPE_SERVER) && m_cDevice[0].GetStatusMessageInterval(tInterval)) ? TRUE : FALSE);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT), ENERTECDEVICE_MINIMUMTIMEOUT, ENERTECDEVICE_MAXIMUMTIMEOUT);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_PORT), ENERTECDEVICE_MINIMUMPORT, ENERTECDEVICE_MAXIMUMPORT);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_BUFFER), ENERTECDEVICE_MINIMUMBUFFER, ENERTECDEVICE_MAXIMUMBUFFER);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER), ENERTECDEVICE_MINIMUMAPIDFILTER, ENERTECDEVICE_MAXIMUMAPIDFILTER);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER), ENERTECDEVICE_MINIMUMVCIDFILTER, ENERTECDEVICE_MAXIMUMVCIDFILTER);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH_YEAR), ENERTECDEVICE_MINIMUMEPOCHYEAR, ENERTECDEVICE_MAXIMUMEPOCHYEAR);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER), ENERTECDEVICE_MINIMUMTIMEERROR, ENERTECDEVICE_MAXIMUMTIMEERROR);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER), ENERTECDEVICE_MINIMUMTIMEDELTA, ENERTECDEVICE_MAXIMUMTIMEDELTA);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL), ENERTECDEVICE_MINIMUMCLOCKADJUSTMENTINTERVAL, ENERTECDEVICE_MAXIMUMCLOCKADJUSTMENTINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL), ENERTECDEVICE_MINIMUMSTATUSMESSAGEINTERVAL, ENERTECDEVICE_MAXIMUMSTATUSMESSAGEINTERVAL);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT), (m_cDevice[0].GetTimeout(tTimeout)) ? tTimeout.GetTotalSeconds() : ENERTECDEVICE_DEFAULTTIMEOUT);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_PORT), (m_cDevice[0].GetIPAddress(&sIPAddress)) ? sIPAddress.sin_port : ENERTECDEVICE_DEFAULTPORT);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_BUFFER), (m_cDevice[0].GetBufferSize(nBufferSize)) ? (nBufferSize / 1024) : ENERTECDEVICE_DEFAULTBUFFER);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER), (m_cDevice[0].GetAPIDFilter(wAPIDFilter)) ? wAPIDFilter : ENERTECDEVICE_DEFAULTAPIDFILTER);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER), (m_cDevice[0].GetVCIDFilter(wVCIDFilter)) ? wVCIDFilter : ENERTECDEVICE_DEFAULTVCIDFILTER);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH_YEAR), (m_cDevice[0].GetTimeEpoch(&tEpochTime)) ? tEpochTime.wYear : ENERTECDEVICE_DEFAULTEPOCHYEAR);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER), (m_cDevice[0].GetTimeCorrelation(tCorrelationError, tCorrelationDelta)) ? tCorrelationError : 0);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER), (m_cDevice[0].GetTimeCorrelation(tCorrelationError, tCorrelationDelta)) ? tCorrelationDelta : 0);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL), (m_cDevice[0].GetClockAdjustmentInterval(tInterval)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : ENERTECDEVICE_DEFAULTCLOCKADJUSTMENTINTERVAL);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL), (m_cDevice[0].GetStatusMessageInterval(tInterval)) ? tInterval.GetTotalSeconds() : ENERTECDEVICE_DEFAULTSTATUSMESSAGEINTERVAL);
	GetDlgItem(IDC_ENERTECDEVICE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_NAME)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS)->EnableWindow((nDeviceMode & IODEVICE_TYPE_SERVER) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT_SECONDS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_PORT_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_PORT)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_BUFFER_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_BUFFER)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_BUFFER_KB)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID)->EnableWindow((m_cDevice[0].GetDeviceBrand() == STRING(IDS_DEVICE_BRANDNAME) && (nDeviceMode & IODEVICE_TYPE_CLIENT)) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER)->EnableWindow((m_cDevice[0].GetDeviceBrand() == STRING(IDS_DEVICE_BRANDNAME) && (nDeviceMode & IODEVICE_TYPE_CLIENT)) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH_YEAR)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_UNIT)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_UNIT)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL_STATIC)->EnableWindow((nDeviceMode & IODEVICE_TYPE_CLIENT) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE)->EnableWindow((nDeviceMode & IODEVICE_TYPE_SERVER) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL)->EnableWindow((nDeviceMode & IODEVICE_TYPE_SERVER) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL_STATIC)->EnableWindow((nDeviceMode & IODEVICE_TYPE_SERVER) ? IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE) : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_HELP)->EnableWindow(IsHelpAvailable());
}

BOOL CENERTECDeviceDialog::IsModified() CONST
{
	return((!m_cDevice[0].Compare(&m_cDevice[1])) ? TRUE : FALSE);
}

BOOL CENERTECDeviceDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_ENERTECDEVICE_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

VOID CENERTECDeviceDialog::AdjustPrivileges()
{
	AccessControl(IDC_ENERTECDEVICE_NAME, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_PORT, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_BUFFER, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH_YEAR, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL, !m_bReadOnly);
}

void CENERTECDeviceDialog::DoDataExchange(CDataExchange *pDX)
{
	CIODeviceDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CENERTECDeviceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CENERTECDeviceDialog, CIODeviceDialog)
	//{{AFX_MSG_MAP(CENERTECDeviceDialog)
	ON_WM_CREATE()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS, OnClients)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE, OnNoFilter)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID, OnAPIDFilter)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID, OnVCIDFilter)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR, OnTimeCorrelationError)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA, OnTimeCorrelationDelta)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT, OnClockAdjustment)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE, OnStatusMessage)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_HELP, OnHelp)
	ON_EN_CHANGE(IDC_ENERTECDEVICE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS, OnEditchangeAddress)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT, OnSpinchangeTimeout)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_PORT, OnSpinchangePort)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_BUFFER, OnSpinchangeBufferSize)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER, OnSpinchangeAPIDFilter)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER, OnSpinchangeVCIDFilter)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH_YEAR, OnSpinchangeEpochYear)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER, OnSpinchangeTimeCorrelationError)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER, OnSpinchangeTimeCorrelationDelta)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL, OnSpinchangeClockAdjustmentInterval)
	ON_CONTROL(SBXN_CHANGE, IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL, OnSpinchangeStatusMessageInterval)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceDialog message handlers

int CENERTECDeviceDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString  szDevice;
	CString  szTitle[2];

	if (CIODeviceDialog::OnCreate(lpCreateStruct) != -1)
	{
		for (szDevice = m_cDevice[0].GetDeviceBrand(); !szDevice.IsEmpty() && !_istspace(szDevice.Right(1).GetAt(0)); szDevice = szDevice.Left(szDevice.GetLength() - 1)) continue;
		for (szDevice.TrimRight(), GetWindowText(szTitle[0]), szTitle[1].Format(szTitle[0], (LPCTSTR)szDevice); szTitle[0].IsEmpty(); )
		{
			szTitle[1] = szDevice;
			break;
		}
		SetWindowText(szTitle[1]);
		return 0;
	}
	return -1;
}

BOOL CENERTECDeviceDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CIODeviceDialog::OnInitDialog();
	ShowDeviceProperties();
	AdjustPrivileges();
	return TRUE;
}

void CENERTECDeviceDialog::OnClients()
{
	CENERTECDeviceClientsDialog  cClientsDialog(this);
	CHourglassCursor  cCursor;

	cClientsDialog.DoModal(&m_cDevice[0], m_bReadOnly);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnNoFilter()
{
	m_cDevice[0].SetAPIDFilter(-1);
	m_cDevice[0].SetVCIDFilter(-1);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE, TRUE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID, FALSE);
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID, FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnAPIDFilter()
{
	m_cDevice[0].SetAPIDFilter((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID)) ? ENERTECDEVICE_DEFAULTAPIDFILTER : -1);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER), ENERTECDEVICE_DEFAULTAPIDFILTER);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID));
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE, !IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID) && !IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID));
	GetDlgItem((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE)) ? IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE : IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnVCIDFilter()
{
	m_cDevice[0].SetVCIDFilter((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID)) ? ENERTECDEVICE_DEFAULTVCIDFILTER : -1);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER), ENERTECDEVICE_DEFAULTVCIDFILTER);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID));
	CheckDlgButton(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE, !IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID) && !IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID));
	GetDlgItem((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE)) ? IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE : IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnTimeCorrelationError()
{
	m_cDevice[0].SetTimeCorrelation((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR)) ? ENERTECDEVICE_DEFAULTTIMEERROR : 0, (IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA)) ? (LONG)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER)) : 0);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER), ENERTECDEVICE_DEFAULTTIMEERROR);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_UNIT)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnTimeCorrelationDelta()
{
	m_cDevice[0].SetTimeCorrelation((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR)) ? (LONG)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER)) : 0, (IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA)) ? ENERTECDEVICE_DEFAULTTIMEDELTA : 0);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER), ENERTECDEVICE_DEFAULTTIMEDELTA);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_UNIT)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnClockAdjustment()
{
	m_cDevice[0].SetClockAdjustmentInterval((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT)) ? (SECONDSPERMINUTE*ENERTECDEVICE_DEFAULTCLOCKADJUSTMENTINTERVAL) : 0);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL), ENERTECDEVICE_DEFAULTCLOCKADJUSTMENTINTERVAL);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnStatusMessage()
{
	m_cDevice[0].SetStatusMessageInterval((IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE)) ? ENERTECDEVICE_DEFAULTSTATUSMESSAGEINTERVAL : 0);
	Spinbox_SetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL), ENERTECDEVICE_DEFAULTSTATUSMESSAGEINTERVAL);
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE));
	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnEditchangeName()
{
	CString  szName;

	GetDlgItem(IDC_ENERTECDEVICE_NAME)->GetWindowText(szName);
	m_cDevice[0].SetDeviceName(szName);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnEditchangeAddress()
{
	CString  szIPAddress;

	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS)->GetWindowText(szIPAddress);
	m_cDevice[0].SetIPAddress(szIPAddress, (UINT)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_PORT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeTimeout()
{
	m_cDevice[0].SetTimeout((TIMEKEY)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangePort()
{
	CString  szIPAddress;

	GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_ADDRESS)->GetWindowText(szIPAddress);
	m_cDevice[0].SetIPAddress(szIPAddress, (UINT)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_PORT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeBufferSize()
{
	m_cDevice[0].SetBufferSize((UINT)(1024 * Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_BUFFER))));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeAPIDFilter()
{
	m_cDevice[0].SetAPIDFilter((UINT)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeVCIDFilter()
{
	m_cDevice[0].SetVCIDFilter((UINT)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeEpochYear()
{
	SYSTEMTIME  tTimeEpoch;

	tTimeEpoch.wYear = (WORD)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH_YEAR));
	tTimeEpoch.wMonth = January;
	tTimeEpoch.wDay = 1;
	tTimeEpoch.wDayOfWeek = 0;
	tTimeEpoch.wHour = 0;
	tTimeEpoch.wMinute = 0;
	tTimeEpoch.wSecond = 0;
	tTimeEpoch.wMilliseconds = 0;
	m_cDevice[0].SetTimeEpoch(&tTimeEpoch);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeTimeCorrelationError()
{
	m_cDevice[0].SetTimeCorrelation((LONG)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER)), (LONG)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeTimeCorrelationDelta()
{
	m_cDevice[0].SetTimeCorrelation((LONG)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER)), (LONG)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeClockAdjustmentInterval()
{
	m_cDevice[0].SetClockAdjustmentInterval((TIMEKEY)(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL))));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnSpinchangeStatusMessageInterval()
{
	m_cDevice[0].SetStatusMessageInterval((TIMEKEY)Spinbox_GetPos(GetDlgItem(IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceDialog::OnOK()
{
	CHourglassCursor  cCursor;

	EndDialog(IDOK);
}

BOOL CENERTECDeviceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowHelp((m_cDevice[0].GetDeviceBrand() == STRING(IDS_DEVICE_BRANDNAME)) ? STRING(IDS_ONLINEHELP_ENERTECDEVICEDIALOG_TOPIC) : STRING(IDS_ONLINEHELP_ENERTECEMULATIONDEVICEDIALOG_TOPIC));
	return TRUE;
}

void CENERTECDeviceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowHelp((m_cDevice[0].GetDeviceBrand() == STRING(IDS_DEVICE_BRANDNAME)) ? STRING(IDS_ONLINEHELP_ENERTECDEVICEDIALOG_TOPIC) : STRING(IDS_ONLINEHELP_ENERTECEMULATIONDEVICEDIALOG_TOPIC));
}


/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceClientsDialog dialog

IMPLEMENT_DYNCREATE(CENERTECDeviceClientsDialog, CIODeviceDialog)

CENERTECDeviceClientsDialog::CENERTECDeviceClientsDialog(CWnd *pParentWnd) : CIODeviceDialog(pParentWnd)
{
	LPVOID  pDialogTemplate;

	if ((pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CENERTECDeviceClientsDialog::IDD))))
	{
		InitModalIndirect(pDialogTemplate);
		return;
	}
}

INT CENERTECDeviceClientsDialog::DoModal(CENERTECDevice *pDevice, BOOL bReadOnly)
{
	INT  nResult;

	for (m_cDevice[0].Copy(pDevice), m_cDevice[1].Copy(pDevice), m_bReadOnly = bReadOnly; (nResult = (INT)CIODeviceDialog::DoModal()) == IDOK; )
	{
		pDevice->Copy(&m_cDevice[0]);
		break;
	}
	return nResult;
}

VOID CENERTECDeviceClientsDialog::EnumDeviceClients()
{
	INT  nOffset;
	INT  nColumn;
	INT  nColumns;
	INT  nClient;
	INT  nClients;
	CString  szClient;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;

	for (nClient = 0, nClients = m_cDevice[0].GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes), nOffset = 0; nClient < nClients; nClient++)
	{
		if (szClients.GetAt(nClient).IsEmpty() && nAccessCodes.GetAt(nClient) != 0)
		{
			CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_ALLOWNONLISTED, TRUE);
			nOffset++;
			continue;
		}
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			for (szClient.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_ENERTECDEVICECLIENTSDIALOG_TITLEITEM_NAME); )
			{
				szClient = TranslateToClientName(szClients.GetAt(nClient));
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ENERTECDEVICECLIENTSDIALOG_TITLEITEM_IPADDRESS); )
			{
				szClient = TranslateToClientAddress(szClients.GetAt(nClient));
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ENERTECDEVICECLIENTSDIALOG_TITLEITEM_ACCESS); )
			{
				if (nAccessCodes.GetAt(nClient) & IODEVICE_SECURITY_UNLIMITEDACCESS)
				{
					szClient = STRING(IDS_ENERTECDEVICECLIENTSDIALOG_ACCESS_UNLIMITED);
					break;
				}
				if (nAccessCodes.GetAt(nClient) & IODEVICE_SECURITY_RESTRICTEDACCESS)
				{
					szClient = STRING(IDS_ENERTECDEVICECLIENTSDIALOG_ACCESS_RESTRICTED);
					break;
				}
				szClient = STRING(IDS_ENERTECDEVICECLIENTSDIALOG_ACCESS_DENIED);
				break;
			}
			if (nClient - nOffset >= (INT)SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) && !nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), nClient - nOffset, szClient);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), nClient - nOffset, nColumn, szClient);
		}
	}
	while (nClients - nOffset < (INT)SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT))
	{
		if (!Listview_DeleteText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), nClients - nOffset)) break;
		continue;
	}
	Listview_SetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), max(Listview_GetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)), 0));
	ShowDeviceClientPolicy(Listview_GetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)));
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_ALLOWNONLISTED)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS));
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_ACCESSTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS));
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS));
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)) >= 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_HELP)->EnableWindow(IsHelpAvailable());
}

VOID CENERTECDeviceClientsDialog::ShowDeviceClientPolicy(INT nIndex)
{
	UINT  nAccessCode;
	CString  szClient;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	if (GetDeviceClientPolicy((GetDeviceClientPolicy(0, szClient, nAccessCode, tStartTime, tStopTime) && szClient.IsEmpty()) ? (nIndex + 1) : nIndex, szClient, nAccessCode, tStartTime, tStopTime))
	{
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->SetWindowText(TranslateToClientName(szClient));
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->SetWindowText(TranslateToClientAddress(szClient));
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS, (nAccessCode & IODEVICE_SECURITY_UNLIMITEDACCESS) ? TRUE : FALSE);
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS, (nAccessCode & IODEVICE_SECURITY_RESTRICTEDACCESS) ? TRUE : FALSE);
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS, (nAccessCode & IODEVICE_SECURITY_DENIEDACCESS) ? TRUE : FALSE);
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT, (nAccessCode & IODEVICE_SECURITY_AUDITACCESS) ? TRUE : FALSE);
		Timespinbox_SetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME), (tStartTime > 0) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME), (tStopTime > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS));
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_ACCESSTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS));
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)->EnableWindow(IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS));
	}
	if (nIndex < 0)
	{
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->SetWindowText(EMPTYSTRING);
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS, TRUE);
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS, FALSE);
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS, FALSE);
		CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT, FALSE);
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_ACCESSTIME_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)->EnableWindow(FALSE);
	}
}

VOID CENERTECDeviceClientsDialog::SetDeviceClientPolicy(INT nIndex, LPCTSTR pszClient, UINT nAccessCode, CONST CTimeKey &tBeginTime, CONST CTimeKey &tEndTime)
{
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;

	for (m_cDevice[0].GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes); nIndex >= 0 && nIndex < (INT)szClients.GetSize(); )
	{
		szClients.SetAt(nIndex, pszClient);
		nAccessCodes.SetAt(nIndex, nAccessCode);
		tStartTimes.SetAt(nIndex, tBeginTime);
		tStopTimes.SetAt(nIndex, tEndTime);
		break;
	}
	if (nIndex < 0)
	{
		szClients.Add(pszClient);
		nAccessCodes.Add(nAccessCode);
		tStartTimes.Add(tBeginTime);
		tStopTimes.Add(tEndTime);
	}
	m_cDevice[0].SetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes);
}

BOOL CENERTECDeviceClientsDialog::GetDeviceClientPolicy(INT nIndex, CString &szClient, UINT &nAccessCode, CTimeKey &tBeginTime, CTimeKey &tEndTime) CONST
{
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;

	if (nIndex >= 0 && nIndex < m_cDevice[0].GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes))
	{
		szClient = szClients.GetAt(nIndex);
		nAccessCode = nAccessCodes.GetAt(nIndex);
		tBeginTime = tStartTimes.GetAt(nIndex);
		tEndTime = tStopTimes.GetAt(nIndex);
		return TRUE;
	}
	return FALSE;
}

INT CENERTECDeviceClientsDialog::FindDeviceClient(LPCTSTR pszName, LPCTSTR pszAddress) CONST
{
	INT  nClient;
	INT  nClients;
	CString  szClient[2];
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;

	for (nClient = 0, nClients = m_cDevice[0].GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes), szClient[0] = TranslateToFullClientName(pszName, pszAddress), szClient[0].MakeUpper(); nClient < nClients; nClient++)
	{
		szClient[1] = szClients.GetAt(nClient);
		szClient[0].MakeUpper();
		szClient[1].MakeUpper();
		if (!TranslateToClientAddress(szClient[0]).CompareNoCase(TranslateToClientAddress(szClient[1]))) break;
	}
	return((nClient < nClients) ? nClient : -1);
}

BOOL CENERTECDeviceClientsDialog::IsModified() CONST
{
	return((!m_cDevice[0].Compare(&m_cDevice[1])) ? TRUE : FALSE);
}

BOOL CENERTECDeviceClientsDialog::Check(BOOL bModified) CONST
{
	CString  szName;
	CString  szAddress;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	return(((szName.IsEmpty() && !IsValidIPAddress(szAddress)) || FindDeviceClient(szName, szAddress) >= 0) ? (!bModified || IsModified()) : FALSE);
}

VOID CENERTECDeviceClientsDialog::AdjustPrivileges()
{
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_NAME, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_ALLOWNONLISTED, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS, !m_bReadOnly);
	AccessControl(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT, !m_bReadOnly);
}

void CENERTECDeviceClientsDialog::DoDataExchange(CDataExchange *pDX)
{
	CIODeviceDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CENERTECDeviceClientsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CENERTECDeviceClientsDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CIODeviceDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CENERTECDeviceClientsDialog, CIODeviceDialog)
	//{{AFX_MSG_MAP(CENERTECDeviceClientsDialog)
	ON_WM_CREATE()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_ADD, OnAddClient)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_REMOVE, OnRemoveClient)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_REMOVEALL, OnRemoveAllClients)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_ALLOWNONLISTED, OnAllowNonListedClients)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS, OnAllowUnlimitedAccess)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS, OnRestrictAccessByTime)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS, OnDenyAccess)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT, OnAuditAccesses)
	ON_BN_CLICKED(IDC_ENERTECDEVICE_CLIENTS_HELP, OnHelp)
	ON_EN_CHANGE(IDC_ENERTECDEVICE_CLIENTS_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS, OnEditchangeIPAddress)
	ON_CONTROL(TSBXN_CHANGE, IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME, OnSpinchangeRestrictedStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME, OnSpinchangeRestrictedStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceClientsDialog message handlers

int CENERTECDeviceClientsDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString  szDevice;
	CString  szTitle[2];

	if (CIODeviceDialog::OnCreate(lpCreateStruct) != -1)
	{
		for (szDevice = m_cDevice[0].GetDeviceBrand(); !szDevice.IsEmpty() && !_istspace(szDevice.Right(1).GetAt(0)); szDevice = szDevice.Left(szDevice.GetLength() - 1)) continue;
		for (szDevice.TrimRight(), GetWindowText(szTitle[0]), szTitle[1].Format(szTitle[0], (LPCTSTR)szDevice); szTitle[0].IsEmpty(); )
		{
			szTitle[1].TrimLeft();
			break;
		}
		SetWindowText(szTitle[1]);
		return 0;
	}
	return -1;
}

BOOL CENERTECDeviceClientsDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CIODeviceDialog::OnInitDialog();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_ENERTECDEVICECLIENTSDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_ENERTECDEVICECLIENTSDIALOG_TITLEITEM_IPADDRESS));
	m_szColumns.Add(STRING(IDS_ENERTECDEVICECLIENTSDIALOG_TITLEITEM_ACCESS));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_ENERTECDEVICECLIENTSDIALOG_TITLEITEM_NAME)) ? (rColumns.Width() / 2) : (rColumns.Width() / 3));
		continue;
	}
	EnumDeviceClients();
	AdjustPrivileges();
	return TRUE;
}

BOOL CENERTECDeviceClientsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_ENERTECDEVICE_CLIENTS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowDeviceClientPolicy(pNotifyListView->iItem);
	}
	return CIODeviceDialog::OnNotify(wParam, lParam, pResult);
}

void CENERTECDeviceClientsDialog::OnAddClient()
{
	INT  nCount;
	CString  szName;
	CString  szAddress;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	if ((nCount = m_cDevice[0].GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes)) >= 0)
	{
		szClients.Add(TranslateToFullClientName(szName, szAddress));
		nAccessCodes.Add(((IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS)) ? IODEVICE_SECURITY_UNLIMITEDACCESS : 0) | ((IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS)) ? IODEVICE_SECURITY_RESTRICTEDACCESS : 0) | ((IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS)) ? IODEVICE_SECURITY_DENIEDACCESS : 0) | ((IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT)) ? IODEVICE_SECURITY_AUDITACCESS : 0));
		tStartTimes.Add((IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS) && (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME))) > 0) ? tStartTime : 0);
		tStopTimes.Add((IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS) && (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME))) > 0) ? tStopTime : 0);
		m_cDevice[0].SetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes);
		EnumDeviceClients();
	}
	Listview_SetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), nCount);
	SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_NAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_ADD)->EnableWindow((FindDeviceClient(szName, szAddress) < 0 && IsValidIPAddress(szAddress)) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)) >= 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnRemoveClient()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;
	CHourglassCursor  cCursor;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST))) >= 0 && nIndex < m_cDevice[0].GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes))
	{
		if (Listview_DeleteText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), nIndex))
		{
			szClients.RemoveAt(nIndex);
			nAccessCodes.RemoveAt(nIndex);
			tStartTimes.RemoveAt(nIndex);
			tStopTimes.RemoveAt(nIndex);
		}
		m_cDevice[0].SetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes);
	}
	ShowDeviceClientPolicy((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? 0 : -1);
	Listview_SetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST), 0);
	SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_NAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_ADD)->EnableWindow((FindDeviceClient(szName, szAddress) < 0 && IsValidIPAddress(szAddress)) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)) >= 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_GETITEMCOUNT) > 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnRemoveAllClients()
{
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;
	CHourglassCursor  cCursor;

	ShowDeviceClientPolicy();
	m_cDevice[0].SetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes);
	SendDlgItemMessage(IDC_ENERTECDEVICE_CLIENTS_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnAllowNonListedClients()
{
	INT  nClient;
	INT  nClients;
	CStringArray  szClients;
	CTimeKeyArray  tStartTimes;
	CTimeKeyArray  tStopTimes;
	CUIntArray  nAccessCodes;
	CHourglassCursor  cCursor;

	for (nClient = 0, nClients = m_cDevice[0].GetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes); nClient < nClients; nClient++)
	{
		if (szClients.GetAt(nClient).IsEmpty()) break;
		continue;
	}
	if (IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_ALLOWNONLISTED) && nClient == nClients)
	{
		nAccessCodes.InsertAt(0, IODEVICE_SECURITY_UNLIMITEDACCESS | IODEVICE_SECURITY_AUDITACCESS);
		szClients.InsertAt(0, EMPTYSTRING);
		tStartTimes.InsertAt(0, CTimeKey(0));
		tStopTimes.InsertAt(0, CTimeKey(0));
	}
	if (!IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_ALLOWNONLISTED) && nClient < nClients)
	{
		szClients.RemoveAt(nClient);
		nAccessCodes.RemoveAt(nClient);
		tStartTimes.RemoveAt(nClient);
		tStopTimes.RemoveAt(nClient);
	}
	m_cDevice[0].SetDeviceSecurity(szClients, nAccessCodes, tStartTimes, tStopTimes);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnAllowUnlimitedAccess()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_ACCESSTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)->EnableWindow(FALSE);
	for (CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS, TRUE), CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS, FALSE), CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS, FALSE); (nIndex = FindDeviceClient(szName, szAddress)) >= 0; )
	{
		SetDeviceClientPolicy(nIndex, TranslateToFullClientName(szName, szAddress), IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT) ? (IODEVICE_SECURITY_UNLIMITEDACCESS | IODEVICE_SECURITY_AUDITACCESS) : IODEVICE_SECURITY_UNLIMITEDACCESS, 0, 0);
		EnumDeviceClients();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnRestrictAccessByTime()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_ACCESSTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)->EnableWindow();
	for (CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS, FALSE), CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS, TRUE), CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS, FALSE), Timespinbox_SetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME), tStartTime), Timespinbox_SetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME), (tStopTime = tStartTime.GetTime() + SECONDSPERDAY)); (nIndex = FindDeviceClient(szName, szAddress)) >= 0; )
	{
		SetDeviceClientPolicy(nIndex, TranslateToFullClientName(szName, szAddress), IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT) ? (IODEVICE_SECURITY_RESTRICTEDACCESS | IODEVICE_SECURITY_AUDITACCESS) : IODEVICE_SECURITY_RESTRICTEDACCESS, tStartTime, tStopTime);
		EnumDeviceClients();
		break;
	}
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnDenyAccess()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_ACCESSTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)->EnableWindow(FALSE);
	for (CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS, FALSE), CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS, FALSE), CheckDlgButton(IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS, TRUE); (nIndex = FindDeviceClient(szName, szAddress)) >= 0; )
	{
		SetDeviceClientPolicy(nIndex, TranslateToFullClientName(szName, szAddress), IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT) ? (IODEVICE_SECURITY_DENIEDACCESS | IODEVICE_SECURITY_AUDITACCESS) : IODEVICE_SECURITY_DENIEDACCESS, 0, 0);
		EnumDeviceClients();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnAuditAccesses()
{
	INT  nIndex;
	UINT  nCode;
	CString  szName;
	CString  szAddress;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)), nCode = (IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS)) ? IODEVICE_SECURITY_UNLIMITEDACCESS : ((IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS)) ? IODEVICE_SECURITY_RESTRICTEDACCESS : IODEVICE_SECURITY_DENIEDACCESS); (nIndex = FindDeviceClient(szName, szAddress)) >= 0; )
	{
		SetDeviceClientPolicy(nIndex, TranslateToFullClientName(szName, szAddress), IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT) ? (nCode | IODEVICE_SECURITY_AUDITACCESS) : nCode, tStartTime, tStopTime);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnEditchangeName()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_ADD)->EnableWindow(((nIndex = FindDeviceClient(szName, szAddress)) < 0 && IsValidIPAddress(szAddress)) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVE)->EnableWindow((nIndex >= 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnEditchangeIPAddress()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_ADD)->EnableWindow(((nIndex = FindDeviceClient(szName, szAddress)) < 0 && IsValidIPAddress(szAddress)) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_REMOVE)->EnableWindow((nIndex >= 0) ? !m_bReadOnly : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnSpinchangeRestrictedStartTime()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)); tStartTime > tStopTime; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME), (tStopTime = tStartTime));
		break;
	}
	if ((nIndex = FindDeviceClient(szName, szAddress)) >= 0) SetDeviceClientPolicy(nIndex, TranslateToFullClientName(szName, szAddress), IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT) ? (IODEVICE_SECURITY_RESTRICTEDACCESS | IODEVICE_SECURITY_AUDITACCESS) : IODEVICE_SECURITY_RESTRICTEDACCESS, tStartTime, tStopTime);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnSpinchangeRestrictedStopTime()
{
	INT  nIndex;
	CString  szName;
	CString  szAddress;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_IPADDRESS)->GetWindowText(szAddress);
	for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME)); tStartTime > tStopTime; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME), (tStartTime = tStopTime));
		break;
	}
	if ((nIndex = FindDeviceClient(szName, szAddress)) >= 0) SetDeviceClientPolicy(nIndex, TranslateToFullClientName(szName, szAddress), IsDlgButtonChecked(IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT) ? (IODEVICE_SECURITY_RESTRICTEDACCESS | IODEVICE_SECURITY_AUDITACCESS) : IODEVICE_SECURITY_RESTRICTEDACCESS, tStartTime, tStopTime);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CENERTECDeviceClientsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	EndDialog(IDOK);
}

BOOL CENERTECDeviceClientsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowHelp((m_cDevice[0].GetDeviceBrand() == STRING(IDS_DEVICE_BRANDNAME)) ? STRING(IDS_ONLINEHELP_ENERTECDEVICECLIENTSDIALOG_TOPIC) : STRING(IDS_ONLINEHELP_ENERTECEMULATIONDEVICECLIENTSDIALOG_TOPIC));
	return TRUE;
}

void CENERTECDeviceClientsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowHelp((m_cDevice[0].GetDeviceBrand() == STRING(IDS_DEVICE_BRANDNAME)) ? STRING(IDS_ONLINEHELP_ENERTECDEVICECLIENTSDIALOG_TOPIC) : STRING(IDS_ONLINEHELP_ENERTECEMULATIONDEVICECLIENTSDIALOG_TOPIC));
}
