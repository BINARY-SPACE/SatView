// MIMICSARCPPG.CPP : Mimics Arc Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics arc control
// dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/10/15 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsArcGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsArcGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsArcGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSARC_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSARC_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsArcGeneralPage, "MIMICS.MimicsArcPropPage.1", 0xd9b0d9f6, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcGeneralPage::CMimicsArcGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsArcGeneralPage

BOOL CMimicsArcGeneralPage::CMimicsArcGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSARCCTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcGeneralPage

CMimicsArcGeneralPage::CMimicsArcGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSARCCTRLDIALOG_TITLE), CMimicsArcGeneralPage::IDD, IDS_MIMICSARCCTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsArcGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsArcGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	cMimicsArcCtrl.SetToolTipText(pszText);
}

CString CMimicsArcGeneralPage::GetToolTipText() CONST
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	return cMimicsArcCtrl.GetToolTipText();
}

BOOL CMimicsArcGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSARC_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSARC_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsArcGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSARC_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsArcGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsArcGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsArcGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcGeneralPage message handlers

BOOL CMimicsArcGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsArcGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsArcGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsArcOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsArcOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsArcOutlinePage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSARC_OUTLINEPAGE_TYPE_ARC, OnTypeArc)
	ON_BN_CLICKED(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE, OnTypePie)
	ON_BN_CLICKED(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD, OnTypeChord)
	ON_BN_CLICKED(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT, OnInteriorTransparent)
	ON_CBN_SELCHANGE(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE, OnSelchangeBorderStyle)
	ON_CBN_SELCHANGE(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR, OnSelchangeBorderColor)
	ON_CBN_SELCHANGE(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, OnSelchangeInteriorColor)
	ON_CBN_SELCHANGE(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, OnSelchangeInteriorHatch)
	ON_CBN_SELCHANGE(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, OnSelchangeInteriorHatchColor)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE, OnSpinchangeBorderSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsArcOutlinePage, "MIMICS.MimicsArcPropPage.2", 0xd9b0d9f7, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcOutlinePage::CMimicsArcOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsArcOutlinePage

BOOL CMimicsArcOutlinePage::CMimicsArcOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSARCCTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcOutlinePage

CMimicsArcOutlinePage::CMimicsArcOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSARCCTRLDIALOG_TITLE), CMimicsArcOutlinePage::IDD, IDS_MIMICSARCCTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsArcOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsArcOutlinePage::SetStyle(INT nStyle)
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	cMimicsArcCtrl.SetStyle(nStyle);
}

INT CMimicsArcOutlinePage::GetStyle() CONST
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	return cMimicsArcCtrl.GetStyle();
}

VOID CMimicsArcOutlinePage::SetBorderSize(INT nSize)
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	cMimicsArcCtrl.SetBorderSize(nSize);
}

INT CMimicsArcOutlinePage::GetBorderSize() CONST
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	return cMimicsArcCtrl.GetBorderSize();
}

VOID CMimicsArcOutlinePage::SetBorderStyle(INT nStyle)
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	cMimicsArcCtrl.SetBorderStyle(nStyle);
}

INT CMimicsArcOutlinePage::GetBorderStyle() CONST
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	return cMimicsArcCtrl.GetBorderStyle();
}

VOID CMimicsArcOutlinePage::SetBorderColor(COLORREF nColor)
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	cMimicsArcCtrl.SetBorderColor(nColor);
}

COLORREF CMimicsArcOutlinePage::GetBorderColor() CONST
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	return cMimicsArcCtrl.GetBorderColor();
}

VOID CMimicsArcOutlinePage::SetInteriorColor(COLORREF nColor)
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	cMimicsArcCtrl.SetInteriorColor(nColor);
}

COLORREF CMimicsArcOutlinePage::GetInteriorColor() CONST
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	return cMimicsArcCtrl.GetInteriorColor();
}

VOID CMimicsArcOutlinePage::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	cMimicsArcCtrl.SetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsArcOutlinePage::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsArcCtrlDispatchDriver  cMimicsArcCtrl(GetOleControl());

	return cMimicsArcCtrl.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsArcOutlinePage::ShowDetails()
{
	INT  nHatch;
	COLORREF  nColor;

	CheckDlgButton(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT, (((GetStyle() & MIMICSARCCTRL_TYPE_PIE) || (GetStyle() & MIMICSARCCTRL_TYPE_CHORD)) && GetInteriorColor() == (COLORREF)-1) ? TRUE : FALSE);
	CheckRadioButton(IDC_MIMICSARC_OUTLINEPAGE_TYPE_ARC, IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD, (GetStyle() & MIMICSARCCTRL_TYPE_ARC) ? IDC_MIMICSARC_OUTLINEPAGE_TYPE_ARC : ((GetStyle() & MIMICSARCCTRL_TYPE_PIE) ? IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE : ((GetStyle() & MIMICSARCCTRL_TYPE_CHORD) ? IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD : IDC_MIMICSARC_OUTLINEPAGE_TYPE_ARC)));
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE), GetBorderSize());
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE, LSCB_SELECTLINESTYLE, (WPARAM)-1, (LPARAM)GetBorderStyle());
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetBorderColor());
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorColor() != (COLORREF)-1) ? (LPARAM)GetInteriorColor() : (LPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)));
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nHatch : (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nColor : (LPARAM)-1);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD));
	ShowSample();
}

VOID CMimicsArcOutlinePage::ShowSample()
{
	CRect  rSample;

	for (GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); !rSample.IsRectEmpty(); )
	{
		InvalidateRect(rSample, FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsArcOutlinePage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CMimicsArcCtrl  cMimicsArcCtrl;

	xForm.eDx = xForm.eDy = 0.0;
	xForm.eM11 = xForm.eM22 = 1.0;
	xForm.eM12 = xForm.eM21 = 0.0;
	cMimicsArcCtrl.SetStyle((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE)) ? ((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) ? MIMICSARCCTRL_TYPE_ARC : MIMICSARCCTRL_TYPE_CHORD) : MIMICSARCCTRL_TYPE_PIE);
	cMimicsArcCtrl.SetBorderSize((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE)));
	cMimicsArcCtrl.SetBorderStyle((LONG)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	cMimicsArcCtrl.SetBorderColor((OLE_COLOR)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	cMimicsArcCtrl.SetInteriorColor(((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (OLE_COLOR)-1);
	cMimicsArcCtrl.SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) ? (LONG)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : (OLE_COLOR)0);
	cMimicsArcCtrl.SetRadials(2.0*M_PI - M_PI / 4.0, 2.0*M_PI - (7.0*M_PI) / 8.0);
	cMimicsArcCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
}

BOOL CMimicsArcOutlinePage::IsModified(BOOL bAll) CONST
{
	INT  nHatch;
	COLORREF  nColor;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetInteriorHatch(nHatch, nColor);
		return(((GetStyle() == MIMICSARCCTRL_TYPE_ARC  &&  !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_ARC)) || (GetStyle() == MIMICSARCCTRL_TYPE_PIE  &&  !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE)) || (GetStyle() == MIMICSARCCTRL_TYPE_CHORD  &&  !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) || GetBorderStyle() != GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE)->SendMessage(CB_GETCURSEL)) || GetBorderColor() != (COLORREF)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CB_GETCURSEL)) || GetBorderSize() != MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE)) || ((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && ((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && GetInteriorColor() != (COLORREF)-1) || (!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && (GetInteriorColor() != (COLORREF)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CB_GETCURSEL)) || (nHatch > 0 && GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) == HT_SOLID) || (nHatch <= 0 && GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != HT_SOLID) || (nHatch >= 0 && GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != nHatch) || (nHatch > 0 && nColor != (COLORREF)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CB_GETCURSEL)))))))) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsArcOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CMimicsArcOutlinePage::Update()
{
	SetStyle((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE)) ? ((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) ? MIMICSARCCTRL_TYPE_ARC : MIMICSARCCTRL_TYPE_CHORD) : MIMICSARCCTRL_TYPE_PIE);
	SetBorderSize((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE)));
	SetBorderStyle((INT)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	SetBorderColor((COLORREF)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	SetInteriorColor(((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) && !IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (COLORREF)-1);
	SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) ? (INT)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE) || IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : (COLORREF)0);
}

void CMimicsArcOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsArcOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcOutlinePage message handlers

BOOL CMimicsArcOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE), MIMICSARCOUTLINEPAGE_MINIMIMTHICKNESS, MIMICSARCOUTLINEPAGE_MAXIMUMTHICKNESS);
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_TYPE_ARC)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_SAMPLE)->EnableWindow();
	ShowDetails();
	return TRUE;
}

void CMimicsArcOutlinePage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); cMemDC.CreateCompatibleDC(&cDC); )
	{
		if (cBitmap.CreateCompatibleBitmap(&cDC, rSample.Width(), rSample.Height()))
		{
			if ((pOldBitmap = (CBitmap *)cMemDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				cMemDC.FillSolidRect(0, 0, rSample.Width(), rSample.Height(), GetSysColor(COLOR_3DFACE));
				DrawSample(&cMemDC, CRect(0, 0, rSample.Width(), rSample.Height()));
				cDC.BitBlt(rSample.left, rSample.top, rSample.Width(), rSample.Height(), &cMemDC, 0, 0, SRCCOPY);
				cMemDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cMemDC.DeleteDC();
		break;
	}
}

void CMimicsArcOutlinePage::OnTypeArc()
{
	CheckDlgButton(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT, FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT)->EnableWindow(FALSE);
	ShowSample();
}

void CMimicsArcOutlinePage::OnTypePie()
{
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT)->EnableWindow();
	ShowSample();
}

void CMimicsArcOutlinePage::OnTypeChord()
{
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT)->EnableWindow();
	ShowSample();
}

void CMimicsArcOutlinePage::OnInteriorTransparent()
{
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsArcOutlinePage::OnSelchangeBorderStyle()
{
	ShowSample();
}

void CMimicsArcOutlinePage::OnSelchangeBorderColor()
{
	ShowSample();
}

void CMimicsArcOutlinePage::OnSelchangeInteriorColor()
{
	ShowSample();
}

void CMimicsArcOutlinePage::OnSelchangeInteriorHatch()
{
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsArcOutlinePage::OnSelchangeInteriorHatchColor()
{
	ShowSample();
}

void CMimicsArcOutlinePage::OnSpinchangeBorderSize()
{
	ShowSample();
}
