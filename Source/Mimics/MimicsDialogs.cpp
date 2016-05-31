// MIMICSDIALOGS.CPP : Mimics Dialogs Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics dialogs
// related interface.
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



/////////////////////////////////////////////////////////////////////////////
// CMimicsFileBrowseDialog

IMPLEMENT_DYNCREATE(CMimicsFileBrowseDialog, CFileDialog)

CMimicsFileBrowseDialog::CMimicsFileBrowseDialog(CWnd *pParentWnd, LPCTSTR pszFileName, LPCTSTR pszFilter, DWORD dwFlags) : CFileDialog(TRUE, (LPCTSTR)NULL, pszFileName, dwFlags, pszFilter, pParentWnd)
{
	for (; GetCurrentDirectory(sizeof(m_szDirectory) / sizeof(TCHAR), m_szDirectory) > 0; )
	{
		m_ofn.lpstrTitle = STRING(IDS_MIMICSFILEBROWSEDIALOG_TITLE);
		break;
	}
}
CMimicsFileBrowseDialog::CMimicsFileBrowseDialog(CWnd *pParentWnd, UINT nCtrlID, LPCTSTR pszFilter, DWORD dwFlags) : CFileDialog(TRUE, (LPCTSTR)NULL, (LPCTSTR)NULL, dwFlags, pszFilter, pParentWnd)
{
	CWnd  *pWnd;
	CString  szFileName;

	for (; GetCurrentDirectory(sizeof(m_szDirectory) / sizeof(TCHAR), m_szDirectory) > 0; )
	{
		m_ofn.lpstrTitle = STRING(IDS_MIMICSFILEBROWSEDIALOG_TITLE);
		break;
	}
	if ((pWnd = (IsWindow(pParentWnd->GetSafeHwnd())) ? pParentWnd->GetDlgItem(nCtrlID) : (CWnd *)NULL))
	{
		pWnd->GetWindowText(szFileName);
		lstrcpy(m_szFileName, szFileName);
	}
}

void CMimicsFileBrowseDialog::PostNcDestroy()
{
	SetCurrentDirectory(m_szDirectory);
	CFileDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMimicsFileBrowseDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMimicsFileBrowseDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsFileBrowseDialog message handlers
