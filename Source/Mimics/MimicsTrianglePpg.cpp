// MIMICSTRIANGLEPPG.CPP : Mimics Triangle Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics triangle
// control dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/06/05 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsTriangleGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsTriangleGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsTriangleGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSTRIANGLE_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSTRIANGLE_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsTriangleGeneralPage, "MIMICS.MimicsTrianglePropPage.1", 0xd9b0da05, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleGeneralPage::CMimicsTriangleGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsTriangleGeneralPage

BOOL CMimicsTriangleGeneralPage::CMimicsTriangleGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSTRIANGLECTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleGeneralPage

CMimicsTriangleGeneralPage::CMimicsTriangleGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSTRIANGLECTRLDIALOG_TITLE), CMimicsTriangleGeneralPage::IDD, IDS_MIMICSTRIANGLECTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsTriangleGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsTriangleGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	cMimicsTriangleCtrl.SetToolTipText(pszText);
}

CString CMimicsTriangleGeneralPage::GetToolTipText() CONST
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	return cMimicsTriangleCtrl.GetToolTipText();
}

BOOL CMimicsTriangleGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsTriangleGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsTriangleGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsTriangleGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsTriangleGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleGeneralPage message handlers

BOOL CMimicsTriangleGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsTriangleGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTriangleGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsTriangleOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsTriangleOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsTriangleOutlinePage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT, OnInteriorTransparent)
	ON_CBN_SELCHANGE(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE, OnSelchangeBorderStyle)
	ON_CBN_SELCHANGE(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR, OnSelchangeBorderColor)
	ON_CBN_SELCHANGE(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, OnSelchangeInteriorColor)
	ON_CBN_SELCHANGE(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, OnSelchangeInteriorHatch)
	ON_CBN_SELCHANGE(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, OnSelchangeInteriorHatchColor)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE, OnSpinchangeBorderSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsTriangleOutlinePage, "MIMICS.MimicsTrianglePropPage.2", 0xd9b0da06, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleOutlinePage::CMimicsTriangleOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsTriangleOutlinePage

BOOL CMimicsTriangleOutlinePage::CMimicsTriangleOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSTRIANGLECTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleOutlinePage

CMimicsTriangleOutlinePage::CMimicsTriangleOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSTRIANGLECTRLDIALOG_TITLE), CMimicsTriangleOutlinePage::IDD, IDS_MIMICSTRIANGLECTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsTriangleOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsTriangleOutlinePage::SetStyle(INT nStyle)
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	cMimicsTriangleCtrl.SetStyle(nStyle);
}

INT CMimicsTriangleOutlinePage::GetStyle() CONST
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	return cMimicsTriangleCtrl.GetStyle();
}

VOID CMimicsTriangleOutlinePage::SetBorderSize(INT nSize)
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	cMimicsTriangleCtrl.SetBorderSize(nSize);
}

INT CMimicsTriangleOutlinePage::GetBorderSize() CONST
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	return cMimicsTriangleCtrl.GetBorderSize();
}

VOID CMimicsTriangleOutlinePage::SetBorderStyle(INT nStyle)
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	cMimicsTriangleCtrl.SetBorderStyle(nStyle);
}

INT CMimicsTriangleOutlinePage::GetBorderStyle() CONST
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	return cMimicsTriangleCtrl.GetBorderStyle();
}

VOID CMimicsTriangleOutlinePage::SetBorderColor(COLORREF nColor)
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	cMimicsTriangleCtrl.SetBorderColor(nColor);
}

COLORREF CMimicsTriangleOutlinePage::GetBorderColor() CONST
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	return cMimicsTriangleCtrl.GetBorderColor();
}

VOID CMimicsTriangleOutlinePage::SetInteriorColor(COLORREF nColor)
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	cMimicsTriangleCtrl.SetInteriorColor(nColor);
}

COLORREF CMimicsTriangleOutlinePage::GetInteriorColor() CONST
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	return cMimicsTriangleCtrl.GetInteriorColor();
}

VOID CMimicsTriangleOutlinePage::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	cMimicsTriangleCtrl.SetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsTriangleOutlinePage::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsTriangleCtrlDispatchDriver  cMimicsTriangleCtrl(GetOleControl());

	return cMimicsTriangleCtrl.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsTriangleOutlinePage::ShowDetails()
{
	INT  nHatch;
	COLORREF  nColor;

	CheckDlgButton(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT, ((GetStyle() & MIMICSTRIANGLECTRL_TYPE_NORMAL) && GetInteriorColor() == (COLORREF)-1) ? TRUE : FALSE);
	CheckRadioButton(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL, IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL, IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE), GetBorderSize());
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE, LSCB_SELECTLINESTYLE, (WPARAM)-1, (LPARAM)GetBorderStyle());
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetBorderColor());
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorColor() != (COLORREF)-1) ? (LPARAM)GetInteriorColor() : (LPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)));
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nHatch : (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nColor : (LPARAM)-1);
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL));
	ShowSample();
}

VOID CMimicsTriangleOutlinePage::ShowSample()
{
	CRect  rSample;

	for (GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); !rSample.IsRectEmpty(); )
	{
		InvalidateRect(rSample, FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsTriangleOutlinePage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CMimicsTriangleCtrl  cMimicsTriangleCtrl;

	xForm.eDx = xForm.eDy = 0.0;
	xForm.eM11 = xForm.eM22 = 1.0;
	xForm.eM12 = xForm.eM21 = 0.0;
	cMimicsTriangleCtrl.SetStyle(MIMICSTRIANGLECTRL_TYPE_NORMAL);
	cMimicsTriangleCtrl.SetBorderSize((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE)));
	cMimicsTriangleCtrl.SetBorderStyle((LONG)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	cMimicsTriangleCtrl.SetBorderColor((OLE_COLOR)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	cMimicsTriangleCtrl.SetInteriorColor((IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (OLE_COLOR)-1);
	cMimicsTriangleCtrl.SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL)) ? (LONG)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : (OLE_COLOR)0);
	cMimicsTriangleCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
}

BOOL CMimicsTriangleOutlinePage::IsModified(BOOL bAll) CONST
{
	INT  nHatch;
	COLORREF  nColor;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetInteriorHatch(nHatch, nColor);
		return(((GetStyle() == MIMICSTRIANGLECTRL_TYPE_NORMAL  &&  !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL)) || GetBorderStyle() != GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE)->SendMessage(CB_GETCURSEL)) || GetBorderColor() != (COLORREF)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CB_GETCURSEL)) || GetBorderSize() != MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE)) || (IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && ((IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && GetInteriorColor() != (COLORREF)-1) || (!IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && (GetInteriorColor() != (COLORREF)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CB_GETCURSEL)) || (nHatch > 0 && GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) == HT_SOLID) || (nHatch <= 0 && GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != HT_SOLID) || (nHatch >= 0 && GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != nHatch) || (nHatch > 0 && nColor != (COLORREF)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CB_GETCURSEL)))))))) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsTriangleOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CMimicsTriangleOutlinePage::Update()
{
	SetStyle(MIMICSTRIANGLECTRL_TYPE_NORMAL);
	SetBorderSize((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE)));
	SetBorderStyle((INT)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	SetBorderColor((COLORREF)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	SetInteriorColor((IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (COLORREF)-1);
	SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL)) ? (INT)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : (COLORREF)0);
}

void CMimicsTriangleOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsTriangleOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleOutlinePage message handlers

BOOL CMimicsTriangleOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE), MIMICSTRIANGLEOUTLINEPAGE_MINIMIMTHICKNESS, MIMICSTRIANGLEOUTLINEPAGE_MAXIMUMTHICKNESS);
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_STYLE)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_COLOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_BORDER_SIZE_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_SAMPLE)->EnableWindow();
	ShowDetails();
	return TRUE;
}

void CMimicsTriangleOutlinePage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); cMemDC.CreateCompatibleDC(&cDC); )
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

void CMimicsTriangleOutlinePage::OnTypeNormal()
{
	ShowSample();
}

void CMimicsTriangleOutlinePage::OnInteriorTransparent()
{
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsTriangleOutlinePage::OnSelchangeBorderStyle()
{
	ShowSample();
}

void CMimicsTriangleOutlinePage::OnSelchangeBorderColor()
{
	ShowSample();
}

void CMimicsTriangleOutlinePage::OnSelchangeInteriorColor()
{
	ShowSample();
}

void CMimicsTriangleOutlinePage::OnSelchangeInteriorHatch()
{
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSTRIANGLE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsTriangleOutlinePage::OnSelchangeInteriorHatchColor()
{
	ShowSample();
}

void CMimicsTriangleOutlinePage::OnSpinchangeBorderSize()
{
	ShowSample();
}
