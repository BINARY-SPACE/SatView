// MIMICSRECTANGLEPPG.CPP : Mimics Rectangle Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics rectangle
// control dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsRectangleGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsRectangleGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsRectangleGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSRECTANGLE_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsRectangleGeneralPage, "MIMICS.MimicsRectanglePropPage.1", 0xd9b0da00, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleGeneralPage::CMimicsRectangleGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsRectangleGeneralPage

BOOL CMimicsRectangleGeneralPage::CMimicsRectangleGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSRECTANGLECTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleGeneralPage

CMimicsRectangleGeneralPage::CMimicsRectangleGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSRECTANGLECTRLDIALOG_TITLE), CMimicsRectangleGeneralPage::IDD, IDS_MIMICSRECTANGLECTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsRectangleGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsRectangleGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	cMimicsRectangleCtrl.SetToolTipText(pszText);
}

CString CMimicsRectangleGeneralPage::GetToolTipText() CONST
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	return cMimicsRectangleCtrl.GetToolTipText();
}

BOOL CMimicsRectangleGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsRectangleGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsRectangleGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsRectangleGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsRectangleGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleGeneralPage message handlers

BOOL CMimicsRectangleGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsRectangleGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsRectangleGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsRectangleOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsRectangleOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsRectangleOutlinePage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND, OnTypeRound)
	ON_BN_CLICKED(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT, OnInteriorTransparent)
	ON_CBN_SELCHANGE(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE, OnSelchangeBorderStyle)
	ON_CBN_SELCHANGE(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR, OnSelchangeBorderColor)
	ON_CBN_SELCHANGE(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, OnSelchangeInteriorColor)
	ON_CBN_SELCHANGE(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, OnSelchangeInteriorHatch)
	ON_CBN_SELCHANGE(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, OnSelchangeInteriorHatchColor)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE, OnSpinchangeBorderSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsRectangleOutlinePage, "MIMICS.MimicsRectanglePropPage.2", 0xd9b0da01, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleOutlinePage::CMimicsRectangleOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsRectangleOutlinePage

BOOL CMimicsRectangleOutlinePage::CMimicsRectangleOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSRECTANGLECTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleOutlinePage

CMimicsRectangleOutlinePage::CMimicsRectangleOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSRECTANGLECTRLDIALOG_TITLE), CMimicsRectangleOutlinePage::IDD, IDS_MIMICSRECTANGLECTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsRectangleOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsRectangleOutlinePage::SetStyle(INT nStyle)
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	cMimicsRectangleCtrl.SetStyle(nStyle);
}

INT CMimicsRectangleOutlinePage::GetStyle() CONST
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	return cMimicsRectangleCtrl.GetStyle();
}

VOID CMimicsRectangleOutlinePage::SetBorderSize(INT nSize)
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	cMimicsRectangleCtrl.SetBorderSize(nSize);
}

INT CMimicsRectangleOutlinePage::GetBorderSize() CONST
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	return cMimicsRectangleCtrl.GetBorderSize();
}

VOID CMimicsRectangleOutlinePage::SetBorderStyle(INT nStyle)
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	cMimicsRectangleCtrl.SetBorderStyle(nStyle);
}

INT CMimicsRectangleOutlinePage::GetBorderStyle() CONST
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	return cMimicsRectangleCtrl.GetBorderStyle();
}

VOID CMimicsRectangleOutlinePage::SetBorderColor(COLORREF nColor)
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	cMimicsRectangleCtrl.SetBorderColor(nColor);
}

COLORREF CMimicsRectangleOutlinePage::GetBorderColor() CONST
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	return cMimicsRectangleCtrl.GetBorderColor();
}

VOID CMimicsRectangleOutlinePage::SetInteriorColor(COLORREF nColor)
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	cMimicsRectangleCtrl.SetInteriorColor(nColor);
}

COLORREF CMimicsRectangleOutlinePage::GetInteriorColor() CONST
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	return cMimicsRectangleCtrl.GetInteriorColor();
}

VOID CMimicsRectangleOutlinePage::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	cMimicsRectangleCtrl.SetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsRectangleOutlinePage::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsRectangleCtrlDispatchDriver  cMimicsRectangleCtrl(GetOleControl());

	return cMimicsRectangleCtrl.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsRectangleOutlinePage::ShowDetails()
{
	INT  nHatch;
	COLORREF  nColor;

	CheckDlgButton(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT, (((GetStyle() & MIMICSRECTANGLECTRL_TYPE_NORMAL) || (GetStyle() & MIMICSRECTANGLECTRL_TYPE_ROUND)) && GetInteriorColor() == (COLORREF)-1) ? TRUE : FALSE);
	CheckRadioButton(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL, IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND, (GetStyle() & MIMICSRECTANGLECTRL_TYPE_NORMAL) ? IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL : ((GetStyle() & MIMICSRECTANGLECTRL_TYPE_ROUND) ? IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND : IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL));
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE), GetBorderSize());
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE, LSCB_SELECTLINESTYLE, (WPARAM)-1, (LPARAM)GetBorderStyle());
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetBorderColor());
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorColor() != (COLORREF)-1) ? (LPARAM)GetInteriorColor() : (LPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)));
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nHatch : (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nColor : (LPARAM)-1);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND));
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND));
	ShowSample();
}

VOID CMimicsRectangleOutlinePage::ShowSample()
{
	CRect  rSample;

	for (GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); !rSample.IsRectEmpty(); )
	{
		InvalidateRect(rSample, FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsRectangleOutlinePage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CMimicsRectangleCtrl  cMimicsRectangleCtrl;

	xForm.eDx = xForm.eDy = 0.0;
	xForm.eM11 = xForm.eM22 = 1.0;
	xForm.eM12 = xForm.eM21 = 0.0;
	cMimicsRectangleCtrl.SetStyle((!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL)) ? MIMICSRECTANGLECTRL_TYPE_ROUND : MIMICSRECTANGLECTRL_TYPE_NORMAL);
	cMimicsRectangleCtrl.SetBorderSize((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE)));
	cMimicsRectangleCtrl.SetBorderStyle((LONG)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	cMimicsRectangleCtrl.SetBorderColor((OLE_COLOR)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	cMimicsRectangleCtrl.SetInteriorColor(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (OLE_COLOR)-1);
	cMimicsRectangleCtrl.SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) ? (LONG)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : 0);
	cMimicsRectangleCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
}

BOOL CMimicsRectangleOutlinePage::IsModified(BOOL bAll) CONST
{
	INT  nHatch;
	COLORREF  nColor;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetInteriorHatch(nHatch, nColor);
		return(((GetStyle() == MIMICSRECTANGLECTRL_TYPE_NORMAL  &&  !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL)) || (GetStyle() == MIMICSRECTANGLECTRL_TYPE_ROUND  &&  !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) || GetBorderStyle() != GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE)->SendMessage(CB_GETCURSEL)) || GetBorderColor() != (COLORREF)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CB_GETCURSEL)) || GetBorderSize() != MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE)) || ((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && ((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && GetInteriorColor() != (COLORREF)-1) || (!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && (GetInteriorColor() != (COLORREF)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CB_GETCURSEL)) || (nHatch > 0 && GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) == HT_SOLID) || (nHatch <= 0 && GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != HT_SOLID) || (nHatch >= 0 && GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != nHatch) || (nHatch > 0 && nColor != (COLORREF)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CB_GETCURSEL)))))))) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsRectangleOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CMimicsRectangleOutlinePage::Update()
{
	SetStyle((!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL)) ? MIMICSRECTANGLECTRL_TYPE_ROUND : MIMICSRECTANGLECTRL_TYPE_NORMAL);
	SetBorderSize((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE)));
	SetBorderStyle((INT)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	SetBorderColor((COLORREF)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	SetInteriorColor(((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) && !IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (COLORREF)-1);
	SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) ? (INT)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL) || IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : (COLORREF)0);
}

void CMimicsRectangleOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsRectangleOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleOutlinePage message handlers

BOOL CMimicsRectangleOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE), MIMICSRECTANGLEOUTLINEPAGE_MINIMIMTHICKNESS, MIMICSRECTANGLEOUTLINEPAGE_MAXIMUMTHICKNESS);
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_SAMPLE)->EnableWindow();
	ShowDetails();
	return TRUE;
}

void CMimicsRectangleOutlinePage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); cMemDC.CreateCompatibleDC(&cDC); )
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

void CMimicsRectangleOutlinePage::OnTypeNormal()
{
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnTypeRound()
{
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnInteriorTransparent()
{
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnSelchangeBorderStyle()
{
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnSelchangeBorderColor()
{
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnSelchangeInteriorColor()
{
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnSelchangeInteriorHatch()
{
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnSelchangeInteriorHatchColor()
{
	ShowSample();
}

void CMimicsRectangleOutlinePage::OnSpinchangeBorderSize()
{
	ShowSample();
}
