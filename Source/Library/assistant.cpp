// ASSISTANT.CPP : Assistant Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the assistant related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2001/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAssistantSupportDateConversionsDialog dialog

IMPLEMENT_DYNCREATE(CAssistantSupportDateConversionsDialog, CLocaleDialog)

CAssistantSupportDateConversionsDialog::CAssistantSupportDateConversionsDialog(CWnd *pParentWnd) : CLocaleDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CAssistantSupportDateConversionsDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

HGLOBAL CAssistantSupportDateConversionsDialog::LoadLocaleDialogTemplate(UINT nDialogID) CONST
{
	return LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID));
}
HGLOBAL CAssistantSupportDateConversionsDialog::LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST
{
	HMODULE  hModule;
	HRSRC  hDialogTemplate;

	return(((hDialogTemplate = FindResourceEx((hModule = GetLibraryModuleInstance()), RT_DIALOG, pszDialogName, GetLanguageID())) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hDialogTemplate) : (LPVOID)NULL);
}

void CAssistantSupportDateConversionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssistantSupportDateConversionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAssistantSupportDateConversionsDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CAssistantSupportDateConversionsDialog)
	ON_CONTROL(TSBXN_CHANGE, IDC_ASSISTANTSUPPORT_DATECONVERSIONS_DAYOFYEAR, OnSpinchangeDayofYear)
	ON_BN_CLICKED(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CLOSE, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssistantSupportDateConversionsDialog message handlers

BOOL CAssistantSupportDateConversionsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_COMMENT_STATIC)->EnableWindow();
	GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CALENDAR)->EnableWindow();
	GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_SYMBOL_STATIC)->EnableWindow();
	GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_DAYOFYEAR)->EnableWindow();
	GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CLOSE)->EnableWindow();
	GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CALENDAR)->SetFocus();
	return FALSE;
}

BOOL CAssistantSupportDateConversionsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CTimeKey  tTime;
	NMSELCHANGE  *pNotifyInfo = (NMSELCHANGE *)lParam;

	if (pNotifyInfo->nmhdr.idFrom == IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CALENDAR)
	{
		if (pNotifyInfo->nmhdr.code == MCN_SELCHANGE)
		{
			tTime.SetTime(pNotifyInfo->stSelStart);
			Timespinbox_SetTime(GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_DAYOFYEAR), tTime);
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CAssistantSupportDateConversionsDialog::OnSpinchangeDayofYear()
{
	CTimeKey  tTime;
	SYSTEMTIME  sTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_DAYOFYEAR)); tTime.GetTime(sTime); )
	{
		SendDlgItemMessage(IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CALENDAR, MCM_SETCURSEL, (WPARAM)NULL, (LPARAM)&sTime);
		break;
	}
}
