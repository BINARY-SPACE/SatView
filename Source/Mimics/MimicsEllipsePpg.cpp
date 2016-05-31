// MIMICSELLIPSEPPG.CPP : Mimics Ellipse Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics ellipse
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



IMPLEMENT_DYNCREATE(CMimicsEllipseGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsEllipseGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsEllipseGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSELLIPSE_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsEllipseGeneralPage, "MIMICS.MimicsEllipsePropPage.1", 0xd9b0d9fb, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseGeneralPage::CMimicsEllipseGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsEllipseGeneralPage

BOOL CMimicsEllipseGeneralPage::CMimicsEllipseGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSELLIPSECTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseGeneralPage

CMimicsEllipseGeneralPage::CMimicsEllipseGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSELLIPSECTRLDIALOG_TITLE), CMimicsEllipseGeneralPage::IDD, IDS_MIMICSELLIPSECTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsEllipseGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsEllipseGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	cMimicsEllipseCtrl.SetToolTipText(pszText);
}

CString CMimicsEllipseGeneralPage::GetToolTipText() CONST
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	return cMimicsEllipseCtrl.GetToolTipText();
}

BOOL CMimicsEllipseGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsEllipseGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsEllipseGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsEllipseGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsEllipseGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseGeneralPage message handlers

BOOL CMimicsEllipseGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsEllipseGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsEllipseGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsEllipseOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsEllipseOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsEllipseOutlinePage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT, OnInteriorTransparent)
	ON_CBN_SELCHANGE(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE, OnSelchangeBorderStyle)
	ON_CBN_SELCHANGE(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR, OnSelchangeBorderColor)
	ON_CBN_SELCHANGE(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, OnSelchangeInteriorColor)
	ON_CBN_SELCHANGE(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, OnSelchangeInteriorHatch)
	ON_CBN_SELCHANGE(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, OnSelchangeInteriorHatchColor)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE, OnSpinchangeBorderSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsEllipseOutlinePage, "MIMICS.MimicsEllipsePropPage.2", 0xd9b0d9fc, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseOutlinePage::CMimicsEllipseOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsEllipseOutlinePage

BOOL CMimicsEllipseOutlinePage::CMimicsEllipseOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSELLIPSECTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseOutlinePage

CMimicsEllipseOutlinePage::CMimicsEllipseOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSELLIPSECTRLDIALOG_TITLE), CMimicsEllipseOutlinePage::IDD, IDS_MIMICSELLIPSECTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsEllipseOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsEllipseOutlinePage::SetStyle(INT nStyle)
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	cMimicsEllipseCtrl.SetStyle(nStyle);
}

INT CMimicsEllipseOutlinePage::GetStyle() CONST
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	return cMimicsEllipseCtrl.GetStyle();
}

VOID CMimicsEllipseOutlinePage::SetBorderSize(INT nSize)
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	cMimicsEllipseCtrl.SetBorderSize(nSize);
}

INT CMimicsEllipseOutlinePage::GetBorderSize() CONST
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	return cMimicsEllipseCtrl.GetBorderSize();
}

VOID CMimicsEllipseOutlinePage::SetBorderStyle(INT nStyle)
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	cMimicsEllipseCtrl.SetBorderStyle(nStyle);
}

INT CMimicsEllipseOutlinePage::GetBorderStyle() CONST
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	return cMimicsEllipseCtrl.GetBorderStyle();
}

VOID CMimicsEllipseOutlinePage::SetBorderColor(COLORREF nColor)
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	cMimicsEllipseCtrl.SetBorderColor(nColor);
}

COLORREF CMimicsEllipseOutlinePage::GetBorderColor() CONST
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	return cMimicsEllipseCtrl.GetBorderColor();
}

VOID CMimicsEllipseOutlinePage::SetInteriorColor(COLORREF nColor)
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	cMimicsEllipseCtrl.SetInteriorColor(nColor);
}

COLORREF CMimicsEllipseOutlinePage::GetInteriorColor() CONST
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	return cMimicsEllipseCtrl.GetInteriorColor();
}

VOID CMimicsEllipseOutlinePage::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	cMimicsEllipseCtrl.SetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsEllipseOutlinePage::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsEllipseCtrlDispatchDriver  cMimicsEllipseCtrl(GetOleControl());

	return cMimicsEllipseCtrl.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsEllipseOutlinePage::ShowDetails()
{
	INT  nHatch;
	COLORREF  nColor;

	CheckDlgButton(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT, ((GetStyle() & MIMICSELLIPSECTRL_TYPE_NORMAL) && GetInteriorColor() == (COLORREF)-1) ? TRUE : FALSE);
	CheckRadioButton(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL, IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL, IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE), GetBorderSize());
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE, LSCB_SELECTLINESTYLE, (WPARAM)-1, (LPARAM)GetBorderStyle());
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetBorderColor());
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorColor() != (COLORREF)-1) ? (LPARAM)GetInteriorColor() : (LPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)));
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nHatch : (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (GetInteriorHatch(nHatch, nColor)) ? (LPARAM)nColor : (LPARAM)-1);
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && nHatch != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL));
	ShowSample();
}

VOID CMimicsEllipseOutlinePage::ShowSample()
{
	CRect  rSample;

	for (GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); !rSample.IsRectEmpty(); )
	{
		InvalidateRect(rSample, FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsEllipseOutlinePage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CMimicsEllipseCtrl  cMimicsEllipseCtrl;

	xForm.eDx = xForm.eDy = 0.0;
	xForm.eM11 = xForm.eM22 = 1.0;
	xForm.eM12 = xForm.eM21 = 0.0;
	cMimicsEllipseCtrl.SetStyle(MIMICSELLIPSECTRL_TYPE_NORMAL);
	cMimicsEllipseCtrl.SetBorderSize((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE)));
	cMimicsEllipseCtrl.SetBorderStyle((LONG)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	cMimicsEllipseCtrl.SetBorderColor((OLE_COLOR)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	cMimicsEllipseCtrl.SetInteriorColor((IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (OLE_COLOR)-1);
	cMimicsEllipseCtrl.SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL)) ? (LONG)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL)) ? (OLE_COLOR)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : (OLE_COLOR)0);
	cMimicsEllipseCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
}

BOOL CMimicsEllipseOutlinePage::IsModified(BOOL bAll) CONST
{
	INT  nHatch;
	COLORREF  nColor;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetInteriorHatch(nHatch, nColor);
		return(((GetStyle() == MIMICSELLIPSECTRL_TYPE_NORMAL  &&  !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL)) || GetBorderStyle() != GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE)->SendMessage(CB_GETCURSEL)) || GetBorderColor() != (COLORREF)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR)->SendMessage(CB_GETCURSEL)) || GetBorderSize() != MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE)) || (IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && ((IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && GetInteriorColor() != (COLORREF)-1) || (!IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && (GetInteriorColor() != (COLORREF)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR)->SendMessage(CB_GETCURSEL)) || (nHatch > 0 && GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) == HT_SOLID) || (nHatch <= 0 && GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != HT_SOLID) || (nHatch >= 0 && GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(HCB_GETHATCH, (WPARAM)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->SendMessage(CB_GETCURSEL)) != nHatch) || (nHatch > 0 && nColor != (COLORREF)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->SendMessage(CB_GETCURSEL)))))))) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsEllipseOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CMimicsEllipseOutlinePage::Update()
{
	SetStyle(MIMICSELLIPSECTRL_TYPE_NORMAL);
	SetBorderSize((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE)));
	SetBorderStyle((INT)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE, CB_GETCURSEL)));
	SetBorderColor((COLORREF)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR, CB_GETCURSEL)));
	SetInteriorColor((IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL) && !IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CB_GETCURSEL)) : (COLORREF)-1);
	SetInteriorHatch((IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL)) ? (INT)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) : -1, (IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL)) ? (COLORREF)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CB_GETCURSEL)) : (COLORREF)0);
}

void CMimicsEllipseOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsEllipseOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseOutlinePage message handlers

BOOL CMimicsEllipseOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE), MIMICSELLIPSEOUTLINEPAGE_MINIMIMTHICKNESS, MIMICSELLIPSEOUTLINEPAGE_MAXIMUMTHICKNESS);
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_SELECTHATCH, (WPARAM)-1, (LPARAM)HT_SOLID);
	SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_SAMPLE)->EnableWindow();
	ShowDetails();
	return TRUE;
}

void CMimicsEllipseOutlinePage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); cMemDC.CreateCompatibleDC(&cDC); )
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

void CMimicsEllipseOutlinePage::OnTypeNormal()
{
	ShowSample();
}

void CMimicsEllipseOutlinePage::OnInteriorTransparent()
{
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH)->EnableWindow(!IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT));
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT) && SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsEllipseOutlinePage::OnSelchangeBorderStyle()
{
	ShowSample();
}

void CMimicsEllipseOutlinePage::OnSelchangeBorderColor()
{
	ShowSample();
}

void CMimicsEllipseOutlinePage::OnSelchangeInteriorColor()
{
	ShowSample();
}

void CMimicsEllipseOutlinePage::OnSelchangeInteriorHatch()
{
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	GetDlgItem(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR)->EnableWindow((SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, HCB_GETHATCH, (WPARAM)SendDlgItemMessage(IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH, CB_GETCURSEL)) != HT_SOLID) ? TRUE : FALSE);
	ShowSample();
}

void CMimicsEllipseOutlinePage::OnSelchangeInteriorHatchColor()
{
	ShowSample();
}

void CMimicsEllipseOutlinePage::OnSpinchangeBorderSize()
{
	ShowSample();
}
