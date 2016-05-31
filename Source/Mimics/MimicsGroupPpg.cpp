// MIMICSGROUPPPG.CPP : Mimics Group Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics group
// control dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/05/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsGroupGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsGroupGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsGroupGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSGROUP_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsGroupGeneralPage, "MIMICS.MimicsGroupPropPage.1", 0xd9b0da15, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupGeneralPage::CMimicsGroupGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsGroupGeneralPage

BOOL CMimicsGroupGeneralPage::CMimicsGroupGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSGROUPCTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupGeneralPage

CMimicsGroupGeneralPage::CMimicsGroupGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSGROUPCTRLDIALOG_TITLE), CMimicsGroupGeneralPage::IDD, IDS_MIMICSGROUPCTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsGroupGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsGroupGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsGroupCtrlDispatchDriver  cMimicsGroupCtrl(GetOleControl());

	cMimicsGroupCtrl.SetToolTipText(pszText);
}

CString CMimicsGroupGeneralPage::GetToolTipText() CONST
{
	CMimicsGroupCtrlDispatchDriver  cMimicsGroupCtrl(GetOleControl());

	return cMimicsGroupCtrl.GetToolTipText();
}

BOOL CMimicsGroupGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsGroupGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsGroupGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsGroupGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsGroupGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupGeneralPage message handlers

BOOL CMimicsGroupGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsGroupGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsGroupGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}
