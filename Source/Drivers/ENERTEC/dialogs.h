// DIALOGS.H : Dialogs Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the dialogs related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DIALOGS_H__
#define __DIALOGS_H__


/////////////////////////////////////////////////////////////////////////////
// CIODeviceDialog dialog

class CIODeviceDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CIODeviceDialog)

	// Construction
public:
	CIODeviceDialog(CWnd *pParentWnd = NULL);   // standard constructor

												// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CIODeviceDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
protected:
	CString TranslateToFullClientName(LPCTSTR pszName, LPCTSTR pszAddress) CONST;
	CString TranslateToClientName(LPCTSTR pszFullName) CONST;
	CString TranslateToClientAddress(LPCTSTR pszFullName) CONST;

	BOOL IsValidIPAddress(LPCTSTR pszAddress) CONST;

protected:
	HGLOBAL LoadLocaleDialogTemplate(UINT nDialogID) CONST;
	HGLOBAL LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIODeviceDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIODeviceDialog)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceDialog dialog

#define IDC_ENERTECDEVICE_DETAILS   1001
#define IDC_ENERTECDEVICE_NAME_STATIC   1002
#define IDC_ENERTECDEVICE_NAME   1003
#define IDC_ENERTECDEVICE_CLIENTS   1004
#define IDC_ENERTECDEVICE_PROPERTIES   1005
#define IDC_ENERTECDEVICE_PROPERTIES_ADDRESS_STATIC   1006
#define IDC_ENERTECDEVICE_PROPERTIES_ADDRESS   1007
#define IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT_STATIC   1008
#define IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT_SECONDS   1009
#define IDC_ENERTECDEVICE_PROPERTIES_TIMEOUT   1010
#define IDC_ENERTECDEVICE_PROPERTIES_PORT_STATIC   1011
#define IDC_ENERTECDEVICE_PROPERTIES_PORT   1012
#define IDC_ENERTECDEVICE_PROPERTIES_BUFFER_STATIC   1013
#define IDC_ENERTECDEVICE_PROPERTIES_BUFFER_KB   1014
#define IDC_ENERTECDEVICE_PROPERTIES_BUFFER   1015
#define IDC_ENERTECDEVICE_PROPERTIES_FILTERS   1016
#define IDC_ENERTECDEVICE_PROPERTIES_FILTERS_NONE   1017
#define IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID   1018
#define IDC_ENERTECDEVICE_PROPERTIES_FILTERS_APID_NUMBER   1019
#define IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID   1020
#define IDC_ENERTECDEVICE_PROPERTIES_FILTERS_VCID_NUMBER   1021
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION   1022
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH   1023
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_EPOCH_YEAR   1024
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR   1025
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_NUMBER   1026
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_ERROR_UNIT   1027
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA   1028
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_NUMBER   1029
#define IDC_ENERTECDEVICE_PROPERTIES_TIMECORRELATION_DELTA_UNIT   1030
#define IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT   1031
#define IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL   1032
#define IDC_ENERTECDEVICE_PROPERTIES_CLOCKADJUSTMENT_INTERVAL_STATIC   1033
#define IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE   1034
#define IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL   1035
#define IDC_ENERTECDEVICE_PROPERTIES_STATUSMESSAGE_INTERVAL_STATIC   1036
#define IDC_ENERTECDEVICE_HELP   1037

class CENERTECDeviceDialog : public CIODeviceDialog
{
	DECLARE_DYNCREATE(CENERTECDeviceDialog)

	// Construction
public:
	CENERTECDeviceDialog(CWnd *pParentWnd = NULL);   // standard constructor

													 // Attributes
private:
	CENERTECDevice  m_cDevice[2];
	UINT  m_nAllowedTypes;
	BOOL  m_bReadOnly;

	// Dialog Data
	//{{AFX_DATA(CENERTECDeviceDialog)
	enum { IDD = IDD_ENERTECDEVICE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowDeviceProperties();

	VOID AdjustPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CENERTECDeviceDialog)
public:
	virtual INT DoModal(CENERTECDevice *pDevice, UINT nAllowedTypes = IODEVICE_TYPE_SERVER | IODEVICE_TYPE_CLIENT, BOOL bReadOnly = FALSE);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CENERTECDeviceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClients();
	afx_msg void OnNoFilter();
	afx_msg void OnAPIDFilter();
	afx_msg void OnVCIDFilter();
	afx_msg void OnTimeCorrelationError();
	afx_msg void OnTimeCorrelationDelta();
	afx_msg void OnClockAdjustment();
	afx_msg void OnStatusMessage();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeAddress();
	afx_msg void OnSpinchangeTimeout();
	afx_msg void OnSpinchangePort();
	afx_msg void OnSpinchangeBufferSize();
	afx_msg void OnSpinchangeAPIDFilter();
	afx_msg void OnSpinchangeVCIDFilter();
	afx_msg void OnSpinchangeEpochYear();
	afx_msg void OnSpinchangeTimeCorrelationError();
	afx_msg void OnSpinchangeTimeCorrelationDelta();
	afx_msg void OnSpinchangeClockAdjustmentInterval();
	afx_msg void OnSpinchangeStatusMessageInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceClientsDialog dialog

#define IDC_ENERTECDEVICE_CLIENTS_DETAILS   1001
#define IDC_ENERTECDEVICE_CLIENTS_NAME_STATIC   1002
#define IDC_ENERTECDEVICE_CLIENTS_NAME   1003
#define IDC_ENERTECDEVICE_CLIENTS_IPADDRESS_STATIC   1004
#define IDC_ENERTECDEVICE_CLIENTS_IPADDRESS   1005
#define IDC_ENERTECDEVICE_CLIENTS_LIST_STATIC   1006
#define IDC_ENERTECDEVICE_CLIENTS_LIST   1007
#define IDC_ENERTECDEVICE_CLIENTS_ALLOWNONLISTED   1008
#define IDC_ENERTECDEVICE_CLIENTS_ADD   1009
#define IDC_ENERTECDEVICE_CLIENTS_REMOVE   1010
#define IDC_ENERTECDEVICE_CLIENTS_REMOVEALL   1011
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY   1012
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY_UNLIMITEDACCESS   1013
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY_RESTRICTEDACCESS   1014
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY_STARTACCESSTIME   1015
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY_ACCESSTIME_STATIC   1016
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY_STOPACCESSTIME   1017
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY_DENYACCESS   1018
#define IDC_ENERTECDEVICE_CLIENTS_SECURITY_AUDIT   1019
#define IDC_ENERTECDEVICE_CLIENTS_HELP   1020

class CENERTECDeviceClientsDialog : public CIODeviceDialog
{
	DECLARE_DYNCREATE(CENERTECDeviceClientsDialog)

	// Construction
public:
	CENERTECDeviceClientsDialog(CWnd *pParentWnd = NULL);   // standard constructor

															// Attributes
private:
	CENERTECDevice  m_cDevice[2];
	BOOL  m_bReadOnly;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CENERTECDeviceClientsDialog)
	enum { IDD = IDD_ENERTECDEVICE_CLIENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumDeviceClients();

	VOID ShowDeviceClientPolicy(INT nIndex = -1);
	VOID SetDeviceClientPolicy(INT nIndex, LPCTSTR pszClient, UINT nAccessCode, CONST CTimeKey &tBeginTime, CONST CTimeKey &tEndTime);
	BOOL GetDeviceClientPolicy(INT nIndex, CString &szClient, UINT &nAccessCode, CTimeKey &tBeginTime, CTimeKey &tEndTime) CONST;

	INT FindDeviceClient(LPCTSTR pszName, LPCTSTR pszAddress) CONST;

	VOID AdjustPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CENERTECDeviceClientsDialog)
public:
	virtual INT DoModal(CENERTECDevice *pDevice, BOOL bReadOnly = FALSE);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CENERTECDeviceClientsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAddClient();
	afx_msg void OnRemoveClient();
	afx_msg void OnRemoveAllClients();
	afx_msg void OnAllowNonListedClients();
	afx_msg void OnAllowUnlimitedAccess();
	afx_msg void OnRestrictAccessByTime();
	afx_msg void OnDenyAccess();
	afx_msg void OnAuditAccesses();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeIPAddress();
	afx_msg void OnSpinchangeRestrictedStartTime();
	afx_msg void OnSpinchangeRestrictedStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DIALOGS_H__
