// MIMICSDIALOGS.H : Mimics Dialogs Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics dialogs related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/09/10 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSDIALOGS_H__
#define __MIMICSDIALOGS_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsFileBrowseDialog dialog

class CMimicsFileBrowseDialog : public CFileDialog
{
	DECLARE_DYNCREATE(CMimicsFileBrowseDialog)

	// Construction
public:
	CMimicsFileBrowseDialog(CWnd *pParentWnd = NULL, LPCTSTR pszFileName = NULL, LPCTSTR pszFilter = NULL, DWORD dwFlags = OFN_HIDEREADONLY);
	CMimicsFileBrowseDialog(CWnd *pParentWnd, UINT nCtrlID, LPCTSTR pszFilter = NULL, DWORD dwFlags = OFN_HIDEREADONLY);

	// Attributes
private:
	TCHAR  m_szDirectory[MAX_PATH];

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsFileBrowseDialog)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CMimicsFileBrowseDialog)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSDIALOGS_H__
