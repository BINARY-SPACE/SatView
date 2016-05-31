// DIALOGS.CPP : Dialogs Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the dialogs related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Simulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

IMPLEMENT_DYNCREATE(CAboutDialog, CLocaleDialog)

CAboutDialog::CAboutDialog(CWnd *pParentWnd) : CLocaleDialog(CAboutDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CAboutDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CAboutDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CAboutDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog message handlers

BOOL CAboutDialog::OnInitDialog()
{
	CString  szTitle[2];
	CString  szVersion[2];
	CString  szCopyright[2];
	CTimeKey  tCopyrightTime;
	CVersionInfo  cVersionInfo;

	CLocaleDialog::OnInitDialog();
	for (GetWindowText(szTitle[0]), GetDlgItem(IDC_ABOUT_NAMEANDVERSION)->GetWindowText(szVersion[0]), GetDlgItem(IDC_ABOUT_COPYRIGHT)->GetWindowText(szCopyright[0]), szTitle[1].Format(szTitle[0], (LPCTSTR)GetAppTitle()), szVersion[1].Format(szVersion[0], (LPCTSTR)cVersionInfo.QueryProductName(), (LPCTSTR)cVersionInfo.QueryProductVersion()), szCopyright[1].Format(szCopyright[0], tCopyrightTime.GetYear(), (LPCTSTR)cVersionInfo.QueryCompanyName()); szTitle[0] != szTitle[1]; )
	{
		SetWindowText(szTitle[1]);
		break;
	}
	GetDlgItem(IDC_ABOUT_NAMEANDVERSION)->SetWindowText(szVersion[1]);
	GetDlgItem(IDC_ABOUT_COPYRIGHT)->SetWindowText(szCopyright[1]);
	return TRUE;
}
