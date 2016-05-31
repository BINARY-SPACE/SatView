// MIMICSIMAGEPPG.CPP : Mimics Image Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics image
// control dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/09/10 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsImageGeneralPage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsImageGeneralPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsImageGeneralPage)
	ON_EN_CHANGE(IDC_MIMICSIMAGE_GENERALPAGE_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP, OnEditchangeToolTipText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsImageGeneralPage, "MIMICS.MimicsImagePropPage.1", 0xd9b0da1a, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageGeneralPage::CMimicsImageGeneralPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsImageGeneralPage

BOOL CMimicsImageGeneralPage::CMimicsImageGeneralPageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSIMAGECTRLDIALOG_GENERALPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageGeneralPage

CMimicsImageGeneralPage::CMimicsImageGeneralPage() : CLocalePropertyPage(STRING(IDS_MIMICSIMAGECTRLDIALOG_TITLE), CMimicsImageGeneralPage::IDD, IDS_MIMICSIMAGECTRLDIALOG_GENERALPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsImageGeneralPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsImageGeneralPage::SetToolTipText(LPCTSTR pszText)
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	cMimicsImageCtrl.SetToolTipText(pszText);
}

CString CMimicsImageGeneralPage::GetToolTipText() CONST
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	return cMimicsImageCtrl.GetToolTipText();
}

BOOL CMimicsImageGeneralPage::IsModified(BOOL bAll) CONST
{
	CString  szName;
	CString  szToolTipText;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP)->GetWindowText(szToolTipText);
		return((szName != GetName() || szToolTipText != GetToolTipText()) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsImageGeneralPage::Check(BOOL bAll) CONST
{
	CString  szName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_NAME)->GetWindowText(szName);
		return !szName.IsEmpty();
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->Check() : TRUE);
}

void CMimicsImageGeneralPage::Update()
{
	CString  szName;
	CString  szText;

	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP)->GetWindowText(szText);
	SetToolTipText(szText);
	SetName(szName);
}

void CMimicsImageGeneralPage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsImageGeneralPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageGeneralPage message handlers

BOOL CMimicsImageGeneralPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_NAME)->SetWindowText(GetName());
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP)->SetWindowText(GetToolTipText());
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_NAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP)->EnableWindow();
	return TRUE;
}

void CMimicsImageGeneralPage::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMimicsImageGeneralPage::OnEditchangeToolTipText()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


IMPLEMENT_DYNCREATE(CMimicsImageOutlinePage, CLocalePropertyPage)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsImageOutlinePage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMimicsImageOutlinePage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME_BROWSE, OnBrowseFileName)
	ON_EN_CHANGE(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME, OnEditchangeFileName)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X, OnSpinchangeImageXPos)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y, OnSpinchangeImageYPos)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X, OnSpinchangeImageXSize)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y, OnSpinchangeImageYSize)
	ON_CONTROL(SBXN_CHANGE, IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY, OnSpinchangeImageTransparency)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsImageOutlinePage, "MIMICS.MimicsImagePropPage.2", 0xd9b0da1b, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageOutlinePage::CMimicsImageOutlinePageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsImageOutlinePage

BOOL CMimicsImageOutlinePage::CMimicsImageOutlinePageFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(), m_clsid, IDS_MIMICSIMAGECTRLDIALOG_OUTLINEPAGENAME) : AfxOleUnregisterClass(m_clsid, NULL));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageOutlinePage

CMimicsImageOutlinePage::CMimicsImageOutlinePage() : CLocalePropertyPage(STRING(IDS_MIMICSIMAGECTRLDIALOG_TITLE), CMimicsImageOutlinePage::IDD, IDS_MIMICSIMAGECTRLDIALOG_OUTLINEPAGETITLE)
{
	//{{AFX_DATA_INIT(CMimicsImageOutlinePage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CMimicsImageOutlinePage::SetStyle(INT nStyle)
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	cMimicsImageCtrl.SetStyle(nStyle);
}

INT CMimicsImageOutlinePage::GetStyle() CONST
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	return cMimicsImageCtrl.GetStyle();
}

VOID CMimicsImageOutlinePage::SetFileName(LPCTSTR pszFileName)
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	cMimicsImageCtrl.SetFileName(pszFileName);
}

CString CMimicsImageOutlinePage::GetFileName() CONST
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	return cMimicsImageCtrl.GetFileName();
}

VOID CMimicsImageOutlinePage::SetImageOrigin(CONST POINT &pt)
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	cMimicsImageCtrl.SetImageOrigin(pt);
}

CPoint CMimicsImageOutlinePage::GetImageOrigin() CONST
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	return cMimicsImageCtrl.GetImageOrigin();
}

VOID CMimicsImageOutlinePage::SetImageSize(CONST SIZE &size)
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	cMimicsImageCtrl.SetImageSize(size);
}

CSize CMimicsImageOutlinePage::GetImageSize() CONST
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	return cMimicsImageCtrl.GetImageSize();
}

VOID CMimicsImageOutlinePage::SetImageTransparency(BYTE nFactor)
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	cMimicsImageCtrl.SetImageTransparency(nFactor);
}

BYTE CMimicsImageOutlinePage::GetImageTransparency() CONST
{
	CMimicsImageCtrlDispatchDriver  cMimicsImageCtrl(GetOleControl());

	return cMimicsImageCtrl.GetImageTransparency();
}

VOID CMimicsImageOutlinePage::ShowDetails()
{
	CheckRadioButton(IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_NORMAL, IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_NORMAL, IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_NORMAL);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X), GetImageOrigin().x);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y), GetImageOrigin().y);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X), GetImageSize().cx);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y), GetImageSize().cy);
	MimicsSpinbox_SetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY), ToTransparencyPercent(GetImageTransparency()));
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->SetWindowText(GetFileName());
	ShowSample();
}

VOID CMimicsImageOutlinePage::ShowSample()
{
	CRect  rSample;

	for (GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); !rSample.IsRectEmpty(); )
	{
		InvalidateRect(rSample, FALSE);
		UpdateWindow();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

VOID CMimicsImageOutlinePage::DrawSample(CDC *pDC, CONST RECT &rect)
{
	XFORM  xForm;
	CString  szFileName;
	CMimicsImageCtrl  cMimicsImageCtrl;

	xForm.eDx = xForm.eDy = 0.0;
	xForm.eM11 = xForm.eM22 = 1.0;
	xForm.eM12 = xForm.eM21 = 0.0;
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->GetWindowText(szFileName);
	cMimicsImageCtrl.SetStyle(MIMICSIMAGECTRL_TYPE_NORMAL);
	cMimicsImageCtrl.SetFileName(szFileName);
	cMimicsImageCtrl.SetImageOrigin((OLE_XPOS_PIXELS)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X)), (OLE_YPOS_PIXELS)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y)));
	cMimicsImageCtrl.SetImageSize((OLE_XSIZE_PIXELS)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X)), (OLE_YSIZE_PIXELS)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y)));
	cMimicsImageCtrl.SetImageTransparency(ToTransparencyFactor((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY))));
	cMimicsImageCtrl.CMimicsCtrl::DrawCtrl(pDC->GetSafeHdc(), &rect, &xForm);
}

BYTE CMimicsImageOutlinePage::ToTransparencyFactor(LONG nPercent) CONST
{
	return((BYTE)(0xFF - (0xFF * nPercent) / 100));
}

LONG CMimicsImageOutlinePage::ToTransparencyPercent(BYTE nFactor) CONST
{
	return(100 - (100 * (LONG)nFactor) / 255);
}

BOOL CMimicsImageOutlinePage::IsModified(BOOL bAll) CONST
{
	CPoint  ptImage;
	CSize  sizeImage;
	CString  szFileName;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->GetWindowText(szFileName);
		ptImage.x = (LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X));
		ptImage.y = (LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y));
		sizeImage.cx = (LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X));
		sizeImage.cy = (LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y));
		return(((GetStyle() == MIMICSIMAGECTRL_TYPE_NORMAL  &&  !IsDlgButtonChecked(IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_NORMAL)) || szFileName.CompareNoCase(GetFileName()) || GetImageOrigin() != ptImage || GetImageSize() != sizeImage || GetImageTransparency() != ToTransparencyFactor((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY)))) ? TRUE : FALSE);
	}
	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsModified() : FALSE);
}

BOOL CMimicsImageOutlinePage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->GetWindowTextLength() > 0) : GetParent()->Check()) : TRUE);
}

void CMimicsImageOutlinePage::Update()
{
	CString  szFileName;

	SetStyle(MIMICSIMAGECTRL_TYPE_NORMAL);
	SetImageOrigin(CPoint((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X)), (INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y))));
	SetImageSize(CSize((INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X)), (INT)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y))));
	SetImageTransparency(ToTransparencyFactor((LONG)MimicsSpinbox_GetPos(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY))));
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->GetWindowText(szFileName);
	SetFileName(szFileName);
}

void CMimicsImageOutlinePage::DoDataExchange(CDataExchange *pDX)
{
	//{{AFX_DATA_MAP(CMimicsImageOutlinePage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageOutlinePage message handlers

BOOL CMimicsImageOutlinePage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X), -GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN));
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y), -GetSystemMetrics(SM_CYSCREEN), GetSystemMetrics(SM_CYSCREEN));
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X), MIMICSIMAGEOUTLINEPAGE_MINIMUMSIZE, MIMICSIMAGEOUTLINEPAGE_MAXIMUMSIZE);
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y), MIMICSIMAGEOUTLINEPAGE_MINIMUMSIZE, MIMICSIMAGEOUTLINEPAGE_MAXIMUMSIZE);
	MimicsSpinbox_SetRange(GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY), MIMICSIMAGEOUTLINEPAGE_MINIMUMTRANSPARENCY, MIMICSIMAGEOUTLINEPAGE_MAXIMUMTRANSPARENCY);
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X_PERCENT)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y_PERCENT)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY_STATIC)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY_PERCENT)->EnableWindow();
	GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SAMPLE)->EnableWindow();
	ShowDetails();
	return TRUE;
}

void CMimicsImageOutlinePage::OnPaint()
{
	CDC  cMemDC;
	CRect  rSample;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_SAMPLE_IMAGE)->GetWindowRect(rSample), ScreenToClient(rSample); cMemDC.CreateCompatibleDC(&cDC); )
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

void CMimicsImageOutlinePage::OnTypeNormal()
{
	ShowSample();
}

void CMimicsImageOutlinePage::OnBrowseFileName()
{
	CMimicsFileBrowseDialog  cFileBrowseDialog(this, IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME, STRING(IDS_MIMICSFILEBROWSEDIALOG_IMAGEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		GetDlgItem(IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME)->SetFocus();
	}
	ShowSample();
}

void CMimicsImageOutlinePage::OnEditchangeFileName()
{
	ShowSample();
}

void CMimicsImageOutlinePage::OnSpinchangeImageXPos()
{
	ShowSample();
}

void CMimicsImageOutlinePage::OnSpinchangeImageYPos()
{
	ShowSample();
}

void CMimicsImageOutlinePage::OnSpinchangeImageXSize()
{
	ShowSample();
}

void CMimicsImageOutlinePage::OnSpinchangeImageYSize()
{
	ShowSample();
}

void CMimicsImageOutlinePage::OnSpinchangeImageTransparency()
{
	ShowSample();
}
