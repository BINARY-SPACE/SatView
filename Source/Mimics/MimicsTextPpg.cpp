// MIMICSTEXTPPG.CPP : Mimics Text Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics text
// control dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsTextGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsTextGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsTextGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSTEXT_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSTEXT_GENERALPAGE_TEXT, OnEditchangeText)
	ON_EN_CHANGE(IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsTextGeneralPage, "MIMICS.MimicsTextPropPage.1", 0xd9b0da0f, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextGeneralPage::CMimicsTextGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsTextGeneralPage

BOOL CMimicsTextGeneralPage::CMimicsTextGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSTEXTCTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextGeneralPage

CMimicsTextGeneralPage::CMimicsTextGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSTEXTCTRLDIALOG_TITLE), CMimicsTextGeneralPage::IDD, IDS_MIMICSTEXTCTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsTextGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsTextGeneralPage::SetText(LPCTSTR pszText)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.SetText(pszText);
}

CString CMimicsTextGeneralPage::GetText() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.GetText();
}

VOID CMimicsTextGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.SetToolTipText(pszText);
}

CString CMimicsTextGeneralPage::GetToolTipText() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.GetToolTipText();
}

BOOL CMimicsTextGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szText;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TEXT)->GetWindowText(szText);
		GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szText != GetText() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsTextGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsTextGeneralPage::Update()
{
	CString  szName;
	CString  szText[2];

	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TEXT)->GetWindowText(szText[0]);
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP)->GetWindowText(szText[1]);
	SetToolTipText(szText[1]);
	SetText(szText[0]);
	SetName(szName);
}

void CMimicsTextGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsTextGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextGeneralPage message handlers

BOOL CMimicsTextGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TEXT)->SetWindowText(GetText());
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TEXT)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsTextGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextGeneralPage::OnEditchangeText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsTextFontPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsTextFontPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsTextFontPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSTEXT_FONTPAGE_STYLE_ITALIC, OnStyleItalic)
	ON_BN_CLICKED(IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD, OnStyleBold)
	ON_BN_CLICKED(IDC_MIMICSTEXT_FONTPAGE_STYLE_UNDERLINE, OnStyleUnderline)
	ON_BN_CLICKED(IDC_MIMICSTEXT_FONTPAGE_STYLE_STRIKEOUT, OnStyleStrikeout)
	ON_CBN_SELCHANGE(IDC_MIMICSTEXT_FONTPAGE_NAME, OnSelchangeFont)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSTEXT_FONTPAGE_SIZE, OnSpinchangeSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsTextFontPage, "MIMICS.MimicsTextPropPage.2", 0xd9b0da10, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextFontPage::CMimicsTextFontPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsTextFontPage

BOOL CMimicsTextFontPage::CMimicsTextFontPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSTEXTCTRLDIALOG_FONTPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextFontPage

CMimicsTextFontPage::CMimicsTextFontPage() : CLocalePropertyPage(STRING(IDS_MIMICSTEXTCTRLDIALOG_TITLE), CMimicsTextFontPage::IDD, IDS_MIMICSTEXTCTRLDIALOG_FONTPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsTextFontPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMimicsTextFontPage::SetFont(CONST LOGFONT *pFont)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.SetFont(pFont);
}

BOOL CMimicsTextFontPage::GetFont(LOGFONT *pFont) CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.GetFont(pFont);
}

VOID CMimicsTextFontPage::ShowDetails()
{
	LOGFONT  sFont;
	CFontTools  cFontTools;

	if (GetFont(&sFont))
	{
		SendDlgItemMessage(IDC_MIMICSTEXT_FONTPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MIMICSTEXT_FONTPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)sFont.lfFaceName));
		MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE), cFontTools.QueryPoints(&sFont));
		CheckDlgButton(IDC_MIMICSTEXT_FONTPAGE_STYLE_ITALIC, (sFont.lfItalic) ? TRUE : FALSE);
		CheckDlgButton(IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD, (sFont.lfWeight >= FW_BOLD) ? TRUE : FALSE);
		CheckDlgButton(IDC_MIMICSTEXT_FONTPAGE_STYLE_UNDERLINE, (sFont.lfUnderline) ? TRUE : FALSE);
		CheckDlgButton(IDC_MIMICSTEXT_FONTPAGE_STYLE_STRIKEOUT, (sFont.lfStrikeOut) ? TRUE : FALSE);
	}
	ShowSample();
}

VOID CMimicsTextFontPage::ShowSample()
{
	CRect  rSample;

	for (GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); !rSample.IsRectEmpty(); )
	{
		InvalidateRect(rSample, FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsTextFontPage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CFont  cFont;
	LOGFONT  sFont;
	CString  szFont;
	CFontTools  cFontTools;
	CMimicsTextCtrl  cMimicsTextCtrl;

	for (szFont = Combobox_GetText(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_NAME), (INT)SendDlgItemMessage(IDC_MIMICSTEXT_FONTPAGE_NAME, CB_GETCURSEL)); cFont.CreateFont(cFontTools.QueryPixels((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE))), 0, 0, 0, (!IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD)) ? FW_NORMAL : FW_BOLD, IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_ITALIC), IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_UNDERLINE), IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_STRIKEOUT), DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, szFont) && cFont.GetObject(sizeof(LOGFONT), &sFont); )
	{
		xForm.eDx = xForm.eDy = 0.0;
		xForm.eM11 = xForm.eM22 = 1.0;
		xForm.eM12 = xForm.eM21 = 0.0;
		cMimicsTextCtrl.SetMode(TRANSPARENT);
		cMimicsTextCtrl.SetFont((VARIANT *)&sFont);
		cMimicsTextCtrl.SetColor(GetSysColor(COLOR_WINDOWTEXT));
		cMimicsTextCtrl.SetText(STRING(IDS_MIMICSTEXTCTRLDIALOG_FONTPAGESAMPLE));
		cMimicsTextCtrl.SingleLine(TRUE);
		cMimicsTextCtrl.AlignCenter();
		cMimicsTextCtrl.AlignVertical(TRUE);
		cMimicsTextCtrl.LeftToRightReading();
		cMimicsTextCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
		cFont.DeleteObject();
		break;
	}
}

BOOL CMimicsTextFontPage::IsModified(BOOL bAll) CONST
{
	LOGFONT  sFont;
	CString  szFont;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		szFont = Combobox_GetText(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_NAME), (INT)GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_NAME)->SendMessage(CB_GETCURSEL));
		return((GetFont(&sFont)) ? ((szFont.CompareNoCase(sFont.lfFaceName) || MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE)) != cFontTools.QueryPoints(&sFont) || IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_ITALIC) != sFont.lfItalic || ((IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD) && sFont.lfWeight < FW_BOLD) || (!IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD) && sFont.lfWeight >= FW_BOLD)) || IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_UNDERLINE) != sFont.lfUnderline || IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_STRIKEOUT) != sFont.lfStrikeOut) ? TRUE : FALSE) : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsTextFontPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CMimicsTextFontPage::Update()
{
	CFont  cFont;
	LOGFONT  sFont;
	CString  szFont;
	CFontTools  cFontTools;

	for (szFont = Combobox_GetText(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_NAME), (INT)SendDlgItemMessage(IDC_MIMICSTEXT_FONTPAGE_NAME, CB_GETCURSEL)); cFont.CreateFont(cFontTools.QueryPixels((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE))), 0, 0, 0, (!IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD)) ? FW_NORMAL : FW_BOLD, IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_ITALIC), IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_UNDERLINE), IsDlgButtonChecked(IDC_MIMICSTEXT_FONTPAGE_STYLE_STRIKEOUT), DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, szFont) && cFont.GetLogFont(&sFont); )
	{
		SetFont(&sFont);
		cFont.DeleteObject();
		break;
	}
}

void CMimicsTextFontPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsTextFontPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextFontPage message handlers

BOOL CMimicsTextFontPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE), 2, 72);
	SendDlgItemMessage(IDC_MIMICSTEXT_FONTPAGE_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS | 0x80000000);
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SIZE_POINTS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_STYLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_STYLE_ITALIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_STYLE_UNDERLINE)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_STYLE_STRIKEOUT)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SAMPLE)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SAMPLE_IMAGE)->EnableWindow();
	ShowDetails();
	return TRUE;
}

void CMimicsTextFontPage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_MIMICSTEXT_FONTPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); cMemDC.CreateCompatibleDC(&cDC); )
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

void CMimicsTextFontPage::OnStyleItalic()
{
	ShowSample();
}

void CMimicsTextFontPage::OnStyleBold()
{
	ShowSample();
}

void CMimicsTextFontPage::OnStyleUnderline()
{
	ShowSample();
}

void CMimicsTextFontPage::OnStyleStrikeout()
{
	ShowSample();
}

void CMimicsTextFontPage::OnSelchangeFont()
{
	ShowSample();
}

void CMimicsTextFontPage::OnSpinchangeSize()
{
	ShowSample();
}


IMPLEMENT_DYNCREATE(CMimicsTextOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsTextOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsTextOutlinePage)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_TRANSPARENT, OnModeTransparent)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE, OnModeOpaque)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT, OnAlignLeft)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_CENTER, OnAlignCenter)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_RIGHT, OnAlignRight)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL, OnAlignVertical)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_TABS, OnUseTabs)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP, OnWrappingWords)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING, OnVerticalReading)
	ON_BN_CLICKED(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE, OnSingleLine)
	ON_CBN_SELCHANGE(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR, OnSelchangeColor)
	ON_CBN_SELCHANGE(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND, OnSelchangeBackground)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS, OnSpinchangeTabChars)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsTextOutlinePage, "MIMICS.MimicsTextPropPage.3", 0xd9b0da11, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextOutlinePage::CMimicsTextOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsTextOutlinePage

BOOL CMimicsTextOutlinePage::CMimicsTextOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSTEXTCTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextOutlinePage

CMimicsTextOutlinePage::CMimicsTextOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSTEXTCTRLDIALOG_TITLE), CMimicsTextOutlinePage::IDD, IDS_MIMICSTEXTCTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsTextOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsTextOutlinePage::SetMode(INT nMode)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.SetMode(nMode);
}

INT CMimicsTextOutlinePage::GetMode() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.GetMode();
}

VOID CMimicsTextOutlinePage::SetColor(COLORREF nColor)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.SetColor(nColor);
}

COLORREF CMimicsTextOutlinePage::GetColor() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.GetColor();
}

VOID CMimicsTextOutlinePage::SetBackgroundColor(COLORREF nColor)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.SetBackgroundColor(nColor);
}

COLORREF CMimicsTextOutlinePage::GetBackgroundColor() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.GetBackgroundColor();
}

VOID CMimicsTextOutlinePage::AlignLeft()
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.AlignLeft();
}

VOID CMimicsTextOutlinePage::AlignCenter()
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.AlignCenter();
}

VOID CMimicsTextOutlinePage::AlignRight()
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.AlignRight();
}

VOID CMimicsTextOutlinePage::AlignVertical(BOOL bEnable)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.AlignVertical(bEnable);
}

BOOL CMimicsTextOutlinePage::IsLeftAligned() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsLeftAligned();
}

BOOL CMimicsTextOutlinePage::IsCenterAligned() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsCenterAligned();
}

BOOL CMimicsTextOutlinePage::IsRightAligned() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsRightAligned();
}

BOOL CMimicsTextOutlinePage::IsVerticalAligned() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsVerticalAligned();
}

VOID CMimicsTextOutlinePage::LeftToRightReading()
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.LeftToRightReading();
}

VOID CMimicsTextOutlinePage::TopToBottomReading()
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.TopToBottomReading();
}

BOOL CMimicsTextOutlinePage::IsLeftToRightReading() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsLeftToRightReading();
}

BOOL CMimicsTextOutlinePage::IsTopToBottomReading() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsTopToBottomReading();
}

void CMimicsTextOutlinePage::SetTabChars(INT nChars)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.SetTabChars(nChars);
}

INT CMimicsTextOutlinePage::GetTabChars() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.GetTabChars();
}

VOID CMimicsTextOutlinePage::WrapWords(BOOL bEnable)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.WrapWords(bEnable);
}

BOOL CMimicsTextOutlinePage::IsWrappingWords() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsWrappingWords();
}

VOID CMimicsTextOutlinePage::SingleLine(BOOL bEnable)
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	cMimicsTextCtrl.SingleLine(bEnable);
}

BOOL CMimicsTextOutlinePage::IsSingleLine() CONST
{
	CMimicsTextCtrlDispatchDriver  cMimicsTextCtrl(GetOleControl());

	return cMimicsTextCtrl.IsSingleLine();
}

BOOL CMimicsTextOutlinePage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetMode() == TRANSPARENT  &&  !IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_TRANSPARENT)) || (GetMode() == OPAQUE  &&  !IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE)) || IsLeftAligned() != (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT) == BST_CHECKED) || IsCenterAligned() != (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_CENTER) == BST_CHECKED) || IsRightAligned() != (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_RIGHT) == BST_CHECKED) || IsVerticalAligned() != (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL) == BST_CHECKED) || IsWrappingWords() != (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP) == BST_CHECKED) || IsTopToBottomReading() != (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING) == BST_CHECKED) || IsSingleLine() != (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE) == BST_CHECKED) || (GetTabChars() > 0 && !IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS)) || (GetTabChars() < 0 && IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS)) || (GetTabChars() > 0 && IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS) && GetTabChars() != MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS))) || GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)GetColor())) != GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR)->SendMessage(CB_GETCURSEL)) || (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE) && GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)GetBackgroundColor())) != GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND)->SendMessage(CB_GETCURSEL)))) : GetParent()->IsModified()) : FALSE);
}

BOOL CMimicsTextOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CMimicsTextOutlinePage::Update()
{
	SetMode((IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_TRANSPARENT)) ? TRANSPARENT : OPAQUE);
	SetColor((COLORREF)SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR, CB_GETCURSEL)));
	SetBackgroundColor((COLORREF)SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND, CB_GETCURSEL)));
	SetTabChars((IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS)) ? (INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS)) : -1);
	AlignVertical(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL));
	if (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT)) AlignLeft();
	if (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_CENTER)) AlignCenter();
	if (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_RIGHT)) AlignRight();
	if (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING)) TopToBottomReading();
	if (!IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING)) LeftToRightReading();
	SingleLine(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE));
	WrapWords(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP));
}

void CMimicsTextOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsTextOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextOutlinePage message handlers

BOOL CMimicsTextOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS), MIMICSTEXTOUTLINEPAGE_MINIMUMTABS, MIMICSTEXTOUTLINEPAGE_MAXIMUMTABS);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS), GetTabChars());
	SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetColor());
	SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND, CCB_INSERTCOLOR, 0, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetBackgroundColor());
	CheckRadioButton(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_TRANSPARENT, IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE, (GetMode() == TRANSPARENT) ? IDC_MIMICSTEXT_OUTLINEPAGE_MODE_TRANSPARENT : IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE);
	CheckRadioButton(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT, IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_RIGHT, (IsLeftAligned()) ? IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT : ((IsCenterAligned()) ? IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_CENTER : ((IsRightAligned()) ? IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_RIGHT : IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT)));
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL, IsVerticalAligned());
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_TABS, (GetTabChars() > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP, IsWrappingWords());
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING, IsTopToBottomReading());
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE, IsSingleLine());
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_TRANSPARENT)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_CENTER)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_RIGHT)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL)->EnableWindow(IsSingleLine());
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_COLOR)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE));
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE));
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS));
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS));
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE)->EnableWindow();
	return TRUE;
}

void CMimicsTextOutlinePage::OnModeTransparent()
{
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnModeOpaque()
{
	SendDlgItemMessage(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_WHITE);
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnAlignLeft()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnAlignCenter()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnAlignRight()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnAlignVertical()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnUseTabs()
{
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS), MIMICSTEXTOUTLINEPAGE_DEFAULTTABS);
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS));
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_TABS));
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnWrappingWords()
{
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING, (!IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP)) ? IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING) : FALSE);
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnVerticalReading()
{
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP, (!IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING)) ? IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP) : FALSE);
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP)->EnableWindow((!IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnSingleLine()
{
	CheckDlgButton(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL, (IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE)) ? IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL) : FALSE);
	GetDlgItem(IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL)->EnableWindow(IsDlgButtonChecked(IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnSelchangeColor()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnSelchangeBackground()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsTextOutlinePage::OnSpinchangeTabChars()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}
