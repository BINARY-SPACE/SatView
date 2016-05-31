// MIMICSSWITCHPPG.CPP : Mimics Switch Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics switch
// control dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/06/28 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsSwitchGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsSwitchGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsSwitchGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSSWITCH_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsSwitchGeneralPage, "MIMICS.MimicsSwitchPropPage.1", 0xd9b0da0a, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchGeneralPage::CMimicsSwitchGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsSwitchGeneralPage

BOOL CMimicsSwitchGeneralPage::CMimicsSwitchGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSSWITCHCTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchGeneralPage

CMimicsSwitchGeneralPage::CMimicsSwitchGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSSWITCHCTRLDIALOG_TITLE), CMimicsSwitchGeneralPage::IDD, IDS_MIMICSSWITCHCTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsSwitchGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsSwitchGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetToolTipText(pszText);
}

CString CMimicsSwitchGeneralPage::GetToolTipText() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetToolTipText();
}

BOOL CMimicsSwitchGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsSwitchGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsSwitchGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsSwitchGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsSwitchGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchGeneralPage message handlers

BOOL CMimicsSwitchGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsSwitchGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsSwitchGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsSwitchOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsSwitchOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsSwitchOutlinePage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE, OnTypeSimple)
	ON_BN_CLICKED(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE, OnTypeDouble)
	ON_BN_CLICKED(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE, OnBehaviorOpenClose)
	ON_BN_CLICKED(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_TWOPOS, OnBehaviorTwoPos)
	ON_BN_CLICKED(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS, OnBehaviorThreePos)
	ON_BN_CLICKED(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME, OnStyleRoundedFrame)
	ON_BN_CLICKED(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STUBS, OnStyleStubs)
	ON_CBN_SELCHANGE(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, OnSelchangeColorItem)
	ON_CBN_SELCHANGE(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR, OnSelchangeColor)
	ON_CBN_SELCHANGE(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, OnSelchangeThicknessItem)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS, OnSpinchangeThickness)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsSwitchOutlinePage, "MIMICS.MimicsSwitchPropPage.2", 0xd9b0da0b, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchOutlinePage::CMimicsSwitchOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsSwitchOutlinePage

BOOL CMimicsSwitchOutlinePage::CMimicsSwitchOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchOutlinePage

CMimicsSwitchOutlinePage::CMimicsSwitchOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSSWITCHCTRLDIALOG_TITLE), CMimicsSwitchOutlinePage::IDD, IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsSwitchOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsSwitchOutlinePage::SetStyle(INT nStyle)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetStyle(nStyle);
}

INT CMimicsSwitchOutlinePage::GetStyle() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetStyle();
}

VOID CMimicsSwitchOutlinePage::SetColor(COLORREF nColor)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetColor(nColor);
}

COLORREF CMimicsSwitchOutlinePage::GetColor() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetColor();
}

VOID CMimicsSwitchOutlinePage::SetFrameColor(COLORREF nColor)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetFrameColor(nColor);
}

COLORREF CMimicsSwitchOutlinePage::GetFrameColor() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetFrameColor();
}

VOID CMimicsSwitchOutlinePage::SetInteriorFrameColor(COLORREF nColor)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetInteriorFrameColor(nColor);
}

COLORREF CMimicsSwitchOutlinePage::GetInteriorFrameColor() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetInteriorFrameColor();
}

VOID CMimicsSwitchOutlinePage::SetCenterColor(COLORREF nColor)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetCenterColor(nColor);
}

COLORREF CMimicsSwitchOutlinePage::GetCenterColor() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetCenterColor();
}

VOID CMimicsSwitchOutlinePage::SetInteriorCenterColor(COLORREF nColor)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetInteriorCenterColor(nColor);
}

COLORREF CMimicsSwitchOutlinePage::GetInteriorCenterColor() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetInteriorCenterColor();
}

VOID CMimicsSwitchOutlinePage::SetBarColor(COLORREF nColor)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetBarColor(nColor);
}

COLORREF CMimicsSwitchOutlinePage::GetBarColor() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetBarColor();
}

VOID CMimicsSwitchOutlinePage::SetStubsColor(COLORREF nColor)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetStubsColor(nColor);
}

COLORREF CMimicsSwitchOutlinePage::GetStubsColor() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetStubsColor();
}

VOID CMimicsSwitchOutlinePage::SetThickness(INT nWidth)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetThickness(nWidth);
}

INT CMimicsSwitchOutlinePage::GetThickness() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetThickness();
}

VOID CMimicsSwitchOutlinePage::SetFrameThickness(INT nWidth)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetFrameThickness(nWidth);
}

INT CMimicsSwitchOutlinePage::GetFrameThickness() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetFrameThickness();
}

VOID CMimicsSwitchOutlinePage::SetCenterThickness(INT nWidth)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetCenterThickness(nWidth);
}

INT CMimicsSwitchOutlinePage::GetCenterThickness() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetCenterThickness();
}

VOID CMimicsSwitchOutlinePage::SetBarThickness(INT nWidth)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetBarThickness(nWidth);
}

INT CMimicsSwitchOutlinePage::GetBarThickness() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetBarThickness();
}

VOID CMimicsSwitchOutlinePage::SetStubsThickness(INT nWidth)
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.SetStubsThickness(nWidth);
}

INT CMimicsSwitchOutlinePage::GetStubsThickness() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.GetStubsThickness();
}

VOID CMimicsSwitchOutlinePage::Open()
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.Open();
}

BOOL CMimicsSwitchOutlinePage::IsOpen() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.IsOpen();
}

BOOL CMimicsSwitchOutlinePage::IsClosed() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.IsClosed();
}

VOID CMimicsSwitchOutlinePage::Close()
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.Close();
}

VOID CMimicsSwitchOutlinePage::Pos1()
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.Pos1();
}

BOOL CMimicsSwitchOutlinePage::IsPos1() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.IsPos1();
}

VOID CMimicsSwitchOutlinePage::Pos2()
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.Pos2();
}

BOOL CMimicsSwitchOutlinePage::IsPos2() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.IsPos2();
}

VOID CMimicsSwitchOutlinePage::Pos3()
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.Pos3();
}

BOOL CMimicsSwitchOutlinePage::IsPos3() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.IsPos3();
}

VOID CMimicsSwitchOutlinePage::Broken()
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	cMimicsSwitchCtrl.Broken();
}

BOOL CMimicsSwitchOutlinePage::IsBroken() CONST
{
	CMimicsSwitchCtrlDispatchDriver  cMimicsSwitchCtrl(GetOleControl());

	return cMimicsSwitchCtrl.IsBroken();
}

BOOL CMimicsSwitchOutlinePage::EnumColorsText()
{
	m_nColors[0].Add(GetColor());
	m_nColors[0].Add(GetFrameColor());
	m_nColors[0].Add(GetInteriorFrameColor());
	m_nColors[0].Add(GetCenterColor());
	m_nColors[0].Add(GetInteriorCenterColor());
	m_nColors[0].Add(GetBarColor());
	m_nColors[0].Add(GetStubsColor());
	m_nColors[1].Copy(m_nColors[0]);
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEPARTS));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAME));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAMEINTERIOR));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTER));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTERINTERIOR));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGESTUBS));
	return((SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_GETCOUNT) == m_nColors[0].GetSize()) ? TRUE : FALSE);
}

BOOL CMimicsSwitchOutlinePage::EnumThicknessText()
{
	m_nWidths[0].Add(GetThickness());
	m_nWidths[0].Add(GetFrameThickness());
	m_nWidths[0].Add(GetCenterThickness());
	m_nWidths[0].Add(GetBarThickness());
	m_nWidths[0].Add(GetStubsThickness());
	m_nWidths[1].Copy(m_nWidths[0]);
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEPARTS));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAME));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTER));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGESTUBS));
	return((SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_GETCOUNT) == m_nWidths[0].GetSize()) ? TRUE : FALSE);
}

VOID CMimicsSwitchOutlinePage::ShowDetails()
{
	INT  nStyle;

	CheckDlgButton(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME, ((nStyle = GetStyle()) & MIMICSSWITCHCTRL_STYLE_FRAME) ? TRUE : FALSE);
	CheckDlgButton(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STUBS, (nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) ? TRUE : FALSE);
	CheckRadioButton(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE, IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE, (nStyle & MIMICSSWITCHCTRL_STYLE_SIMPLE) ? IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE : IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE);
	CheckRadioButton(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE, IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS, (nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) ? IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE : ((nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) ? IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_TWOPOS : IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR)));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR)));
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetBarColor());
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS), GetBarThickness());
	GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR)->EnableWindow((SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS)->EnableWindow((SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	ShowSample();
}

VOID CMimicsSwitchOutlinePage::ShowSample()
{
	CRect  rSample[4];

	for (GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_FRAME)->GetWindowRect(rSample[0]), GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_DOUBLE)->GetWindowRect(rSample[1]), GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_SIMPLE)->GetWindowRect(rSample[2]), rSample[3].UnionRect(rSample[0], rSample[1]), rSample[3].UnionRect(rSample[2], rSample[3]), ScreenToClient(rSample[3]); !rSample[3].IsRectEmpty(); )
	{
		InvalidateRect(rSample[3], FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsSwitchOutlinePage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CMimicsSwitchCtrl  cMimicsSwitchCtrl;

	xForm.eDx = xForm.eDy = 0.0;
	xForm.eM11 = xForm.eM22 = 1.0;
	xForm.eM12 = xForm.eM21 = 0.0;
	cMimicsSwitchCtrl.SetStyle(((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE)) ? MIMICSSWITCHCTRL_STYLE_SIMPLE : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE)) ? MIMICSSWITCHCTRL_STYLE_DOUBLE : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE)) ? MIMICSSWITCHCTRL_STYLE_OPENCLOSE : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_TWOPOS)) ? MIMICSSWITCHCTRL_STYLE_TWOPOS : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS)) ? MIMICSSWITCHCTRL_STYLE_THREEPOS : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME)) ? MIMICSSWITCHCTRL_STYLE_FRAME : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STUBS)) ? MIMICSSWITCHCTRL_STYLE_STUBS : 0));
	cMimicsSwitchCtrl.SetColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEPARTS))));
	cMimicsSwitchCtrl.SetFrameColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAME))));
	cMimicsSwitchCtrl.SetInteriorFrameColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAMEINTERIOR))));
	cMimicsSwitchCtrl.SetCenterColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTER))));
	cMimicsSwitchCtrl.SetInteriorCenterColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTERINTERIOR))));
	cMimicsSwitchCtrl.SetBarColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR))));
	cMimicsSwitchCtrl.SetStubsColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGESTUBS))));
	cMimicsSwitchCtrl.SetThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEPARTS))));
	cMimicsSwitchCtrl.SetFrameThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAME))));
	cMimicsSwitchCtrl.SetCenterThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTER))));
	cMimicsSwitchCtrl.SetBarThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR))));
	cMimicsSwitchCtrl.SetStubsThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGESTUBS))));
	cMimicsSwitchCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
}

BOOL CMimicsSwitchOutlinePage::IsModified(BOOL bAll) CONST
{
	INT  nStyle;

	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((((nStyle = GetStyle()) & MIMICSSWITCHCTRL_STYLE_SIMPLE) && !IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE)) || ((nStyle & MIMICSSWITCHCTRL_STYLE_DOUBLE) && !IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE)) || ((nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) && !IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE)) || ((nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) && !IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_TWOPOS)) || ((nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS) && !IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS)) || ((nStyle & MIMICSSWITCHCTRL_STYLE_FRAME) != ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME)) ? MIMICSSWITCHCTRL_STYLE_FRAME : 0)) || ((nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) != ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STUBS)) ? MIMICSSWITCHCTRL_STYLE_STUBS : 0)) || memcmp(m_nColors[0].GetData(), m_nColors[1].GetData(), m_nColors[0].GetSize()*sizeof(UINT)) || memcmp(m_nWidths[0].GetData(), m_nWidths[1].GetData(), m_nWidths[0].GetSize()*sizeof(UINT))) : GetParent()->IsModified()) : FALSE);
}

BOOL CMimicsSwitchOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM)->SendMessage(CB_GETCURSEL) >= 0) : GetParent()->Check()) : TRUE);
}

void CMimicsSwitchOutlinePage::Update()
{
	SetStyle(((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE)) ? MIMICSSWITCHCTRL_STYLE_SIMPLE : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE)) ? MIMICSSWITCHCTRL_STYLE_DOUBLE : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE)) ? MIMICSSWITCHCTRL_STYLE_OPENCLOSE : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_TWOPOS)) ? MIMICSSWITCHCTRL_STYLE_TWOPOS : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS)) ? MIMICSSWITCHCTRL_STYLE_THREEPOS : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME)) ? MIMICSSWITCHCTRL_STYLE_FRAME : 0) | ((IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STUBS)) ? MIMICSSWITCHCTRL_STYLE_STUBS : 0));
	SetColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEPARTS))));
	SetFrameColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAME))));
	SetInteriorFrameColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAMEINTERIOR))));
	SetCenterColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTER))));
	SetInteriorCenterColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTERINTERIOR))));
	SetBarColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR))));
	SetStubsColor(m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGESTUBS))));
	SetThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEPARTS))));
	SetFrameThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAME))));
	SetCenterThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTER))));
	SetBarThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEBAR))));
	SetStubsThickness(m_nWidths[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGESTUBS))));
}

void CMimicsSwitchOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsSwitchOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

void CMimicsSwitchOutlinePage::PostNcDestroy()
{
	m_nColors[0].RemoveAll();
	m_nColors[1].RemoveAll();
	m_nWidths[0].RemoveAll();
	m_nWidths[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchOutlinePage message handlers

BOOL CMimicsSwitchOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	if (EnumColorsText() && EnumThicknessText())
	{
		MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS), MIMICSSWITCHOUTLINEPAGE_MINIMIMTHICKNESS, MIMICSSWITCHOUTLINEPAGE_MAXIMUMTHICKNESS);
		SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)GetSysColor(COLOR_WINDOW));
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_STATIC)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_TWOPOS)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_STATIC)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_STATIC)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_PIXELS)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STUBS)->EnableWindow();
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE)->EnableWindow();
		ShowDetails();
	}
	return TRUE;
}

void CMimicsSwitchOutlinePage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CRect  rImage[4];
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_FRAME)->GetWindowRect(rImage[0]);
	GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_DOUBLE)->GetWindowRect(rImage[1]);
	GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_SIMPLE)->GetWindowRect(rImage[2]);
	for (rImage[3].UnionRect(rImage[0], rImage[1]), rImage[3].UnionRect(rImage[2], rImage[3]), ScreenToClient(rImage[3]); IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME); )
	{
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_FRAME)->GetWindowRect(rSample);
		ScreenToClient(rSample);
		break;
	}
	if (IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE) && !IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME))
	{
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_DOUBLE)->GetWindowRect(rSample);
		ScreenToClient(rSample);
	}
	if (IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE) && !IsDlgButtonChecked(IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME))
	{
		GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_SIMPLE)->GetWindowRect(rSample);
		ScreenToClient(rSample);
	}
	if (cMemDC.CreateCompatibleDC(&cDC))
	{
		if (cBitmap.CreateCompatibleBitmap(&cDC, rImage[3].Width(), rImage[3].Height()))
		{
			if ((pOldBitmap = (CBitmap *)cMemDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				cMemDC.FillSolidRect(0, 0, rImage[3].Width(), rImage[3].Height(), GetSysColor(COLOR_3DFACE));
				DrawSample(&cMemDC, CRect((rImage[3].Width() - rSample.Width()) / 2, (rImage[3].Height() - rSample.Height()) / 2, (rImage[3].Width() - rSample.Width()) / 2 + rSample.Width(), (rImage[3].Height() - rSample.Height()) / 2 + rSample.Height()));
				cDC.BitBlt(rImage[3].left, rImage[3].top, rImage[3].Width(), rImage[3].Height(), &cMemDC, 0, 0, SRCCOPY);
				cMemDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cMemDC.DeleteDC();
	}
}

void CMimicsSwitchOutlinePage::OnTypeSimple()
{
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnTypeDouble()
{
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnBehaviorOpenClose()
{
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnBehaviorTwoPos()
{
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnBehaviorThreePos()
{
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnStyleRoundedFrame()
{
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnStyleStubs()
{
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnSelchangeColorItem()
{
	SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_GETCURSEL)));
}

void CMimicsSwitchOutlinePage::OnSelchangeColor()
{
	INT  nIndex;
	COLORREF  nColor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_GETCURSEL)) >= 0)
	{
		for (m_nColors[0].SetAt(nIndex, (nColor = (COLORREF)SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR, CB_GETCURSEL)))), nIndex = (nIndex > 0) ? (INT)m_nColors[0].GetSize() : 0; nIndex < (INT)m_nColors[0].GetSize(); nIndex++)
		{
			if (nIndex != SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGEFRAMEINTERIOR)) && nIndex != SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MIMICSSWITCHCTRLDIALOG_OUTLINEPAGECENTERINTERIOR)))
			{
				m_nColors[0].SetAt(nIndex, nColor);
				continue;
			}
		}
	}
	ShowSample();
}

void CMimicsSwitchOutlinePage::OnSelchangeThicknessItem()
{
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS), m_nWidths[0].GetAt((INT_PTR)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM))));
}

void CMimicsSwitchOutlinePage::OnSpinchangeThickness()
{
	INT  nIndex;
	INT  nThickness;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM, CB_GETCURSEL)) >= 0)
	{
		for (m_nWidths[0].SetAt(nIndex, (nThickness = (INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS)))), nIndex = (nIndex > 0) ? (INT)m_nWidths[0].GetSize() : 0; nIndex < (INT)m_nWidths[0].GetSize(); nIndex++)
		{
			m_nWidths[0].SetAt(nIndex, nThickness);
			continue;
		}
	}
	ShowSample();
}
