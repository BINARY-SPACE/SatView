// MIMICSLINEPPG.CPP : Mimics Line Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics line
// control dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/03 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsLineGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsLineGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsLineGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSLINE_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSLINE_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsLineGeneralPage, "MIMICS.MimicsLinePropPage.1", 0xd9b0d9f1, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineGeneralPage::CMimicsLineGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsLineGeneralPage

BOOL CMimicsLineGeneralPage::CMimicsLineGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSLINECTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineGeneralPage

CMimicsLineGeneralPage::CMimicsLineGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSLINECTRLDIALOG_TITLE), CMimicsLineGeneralPage::IDD, IDS_MIMICSLINECTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsLineGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsLineGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.SetToolTipText(pszText);
}

CString CMimicsLineGeneralPage::GetToolTipText() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.GetToolTipText();
}

BOOL CMimicsLineGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsLineGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsLineGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsLineGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsLineGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineGeneralPage message handlers

BOOL CMimicsLineGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsLineGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsLineGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsLineOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsLineOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsLineOutlinePage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_CROSSING, OnEffectCrossing)
	ON_BN_CLICKED(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW, OnEffectArrow)
	ON_BN_CLICKED(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW, OnEffectDoubleArrow)
	ON_CBN_SELCHANGE(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, OnSelchangeStyle)
	ON_CBN_SELCHANGE(IDC_MIMICSLINE_OUTLINEPAGE_COLOR, OnSelchangeColor)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS, OnSpinchangeThickness)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsLineOutlinePage, "MIMICS.MimicsLinePropPage.2", 0xd9b0d9f2, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineOutlinePage::CMimicsLineOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsLineOutlinePage

BOOL CMimicsLineOutlinePage::CMimicsLineOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSLINECTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineOutlinePage

CMimicsLineOutlinePage::CMimicsLineOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSLINECTRLDIALOG_TITLE), CMimicsLineOutlinePage::IDD, IDS_MIMICSLINECTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsLineOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsLineOutlinePage::SetStyle(INT nStyle)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.SetStyle(nStyle);
}

INT CMimicsLineOutlinePage::GetStyle() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.GetStyle();
}

VOID CMimicsLineOutlinePage::Arrow(BOOL bEnable)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.Arrow(bEnable);
}

VOID CMimicsLineOutlinePage::DoubleArrow(BOOL bEnable)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.DoubleArrow(bEnable);
}

VOID CMimicsLineOutlinePage::Cross(BOOL bEnable)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.Cross(bEnable);
}

BOOL CMimicsLineOutlinePage::SetCrossPt(double fPt)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.SetCrossPt(fPt);
}

BOOL CMimicsLineOutlinePage::GetCrossPt(double *fPt) CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.GetCrossPt(fPt);
}

BOOL CMimicsLineOutlinePage::IsArrow() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsArrow();
}

BOOL CMimicsLineOutlinePage::IsDoubleArrow() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsDoubleArrow();
}

BOOL CMimicsLineOutlinePage::IsCross() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsCross();
}

VOID CMimicsLineOutlinePage::SetColor(COLORREF nColor)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.SetColor(nColor);
}

COLORREF CMimicsLineOutlinePage::GetColor() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.GetColor();
}

VOID CMimicsLineOutlinePage::SetThickness(INT nWidth)
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.SetThickness(nWidth);
}

INT CMimicsLineOutlinePage::GetThickness() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.GetThickness();
}

VOID CMimicsLineOutlinePage::Solid()
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.Solid();
}

VOID CMimicsLineOutlinePage::Dash()
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.Dash();
}

VOID CMimicsLineOutlinePage::Dot()
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.Dot();
}

VOID CMimicsLineOutlinePage::DashDot()
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.DashDot();
}

VOID CMimicsLineOutlinePage::DashDotDot()
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	cMimicsLineCtrl.DashDotDot();
}

BOOL CMimicsLineOutlinePage::IsSolid() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsSolid();
}

BOOL CMimicsLineOutlinePage::IsDashed() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsDashed();
}

BOOL CMimicsLineOutlinePage::IsDotted() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsDotted();
}

BOOL CMimicsLineOutlinePage::IsDashDotted() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsDashDotted();
}

BOOL CMimicsLineOutlinePage::IsDashDotDotted() CONST
{
	CMimicsLineCtrlDispatchDriver  cMimicsLineCtrl(GetOleControl());

	return cMimicsLineCtrl.IsDashDotDotted();
}

VOID CMimicsLineOutlinePage::ShowDetails()
{
	SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_SELECTLINESTYLE, (WPARAM)-1, (IsSolid()) ? LS_SOLID : ((IsDashed()) ? LS_DASH : ((IsDotted()) ? LS_DOT : ((IsDashDotted()) ? LS_DASHDOT : ((IsDashDotDotted()) ? LS_DASHDOTDOT : -1)))));
	SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetColor());
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS), GetThickness());
	CheckDlgButton(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW, IsArrow());
	CheckDlgButton(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW, IsDoubleArrow());
	CheckDlgButton(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_CROSSING, IsCross());
	ShowSample();
}

VOID CMimicsLineOutlinePage::ShowSample()
{
	CRect  rSample;

	for (GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); !rSample.IsRectEmpty(); )
	{
		InvalidateRect(rSample, FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsLineOutlinePage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CMimicsLineCtrl  cMimicsLineCtrl;

	for (xForm.eDx = xForm.eDy = 0.0, xForm.eM11 = xForm.eM22 = 1.0, xForm.eM12 = xForm.eM21 = 0.0; SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_SOLID; )
	{
		cMimicsLineCtrl.Solid();
		break;
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DASHDOTDOT)
	{
		cMimicsLineCtrl.DashDotDot();
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DASHDOT)
	{
		cMimicsLineCtrl.DashDot();
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DASH)
	{
		cMimicsLineCtrl.Dash();
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DOT)
	{
		cMimicsLineCtrl.Dot();
	}
	cMimicsLineCtrl.Cross(IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_CROSSING));
	cMimicsLineCtrl.Arrow(IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW));
	cMimicsLineCtrl.DoubleArrow(IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW));
	cMimicsLineCtrl.SetColor((COLORREF)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_COLOR, CB_GETCURSEL)));
	cMimicsLineCtrl.SetThickness((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS)));
	cMimicsLineCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
}

BOOL CMimicsLineOutlinePage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (IsArrow() != (BOOL)IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW) || IsDoubleArrow() != (BOOL)IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW) || IsCross() != (BOOL)IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_CROSSING) || GetColor() != (COLORREF)GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_COLOR)->SendMessage(CB_GETCURSEL)) || GetThickness() != MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS)) || (IsSolid() && GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(CB_GETCURSEL)) != LS_SOLID) || (IsDashed() && GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(CB_GETCURSEL)) != LS_DASH) || (IsDotted() && GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(CB_GETCURSEL)) != LS_DOT) || (IsDashDotted() && GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(CB_GETCURSEL)) != LS_DASHDOT) || (IsDashDotDotted() && GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->SendMessage(CB_GETCURSEL)) != LS_DASHDOTDOT)) : GetParent()->IsModified()) : FALSE);
}

BOOL CMimicsLineOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CMimicsLineOutlinePage::Update()
{
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_SOLID)
	{
		Solid();
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DASHDOTDOT)
	{
		DashDotDot();
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DASHDOT)
	{
		DashDot();
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DASH)
	{
		Dash();
	}
	if (SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, LSCB_GETLINESTYLE, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_STYLE, CB_GETCURSEL)) == LS_DOT)
	{
		Dot();
	}
	Cross(IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_CROSSING));
	Arrow(IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW));
	DoubleArrow(IsDlgButtonChecked(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW));
	SetColor((COLORREF)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_COLOR, CB_GETCURSEL)));
	SetThickness((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS)));
}

void CMimicsLineOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsLineOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineOutlinePage message handlers

BOOL CMimicsLineOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS), MIMICSLINEOUTLINEPAGE_MINIMIMTHICKNESS, MIMICSLINEOUTLINEPAGE_MAXIMUMTHICKNESS);
	SendDlgItemMessage(IDC_MIMICSLINE_OUTLINEPAGE_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_COLOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_STYLE)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_CROSSING)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_SAMPLE)->EnableWindow();
	ShowDetails();
	return TRUE;
}

void CMimicsLineOutlinePage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_MIMICSLINE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); cMemDC.CreateCompatibleDC(&cDC); )
	{
		if (cBitmap.CreateCompatibleBitmap(&cDC, rSample.Width(), rSample.Height()))
		{
			if ((pOldBitmap = (CBitmap *)cMemDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				cMemDC.FillSolidRect(0, 0, rSample.Width(), rSample.Height(), GetSysColor(COLOR_3DFACE));
				DrawSample(&cMemDC, CRect(0, rSample.Height() / 2, rSample.Width(), rSample.Height() / 2));
				cDC.BitBlt(rSample.left, rSample.top, rSample.Width(), rSample.Height(), &cMemDC, 0, 0, SRCCOPY);
				cMemDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cMemDC.DeleteDC();
		break;
	}
}

void CMimicsLineOutlinePage::OnEffectCrossing()
{
	ShowSample();
}

void CMimicsLineOutlinePage::OnEffectArrow()
{
	CheckDlgButton(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW, FALSE);
	ShowSample();
}

void CMimicsLineOutlinePage::OnEffectDoubleArrow()
{
	CheckDlgButton(IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW, FALSE);
	ShowSample();
}

void CMimicsLineOutlinePage::OnSelchangeStyle()
{
	ShowSample();
}

void CMimicsLineOutlinePage::OnSelchangeColor()
{
	ShowSample();
}

void CMimicsLineOutlinePage::OnSpinchangeThickness()
{
	ShowSample();
}
