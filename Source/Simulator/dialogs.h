// DIALOGS.H : Dialogs Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the dialogs related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DIALOGS_H__
#define __DIALOGS_H__


/////////////////////////////////////////////////////////////////////////////
// CAboutDialog

#define IDC_ABOUT_NAMEANDVERSION   1001
#define IDC_ABOUT_COPYRIGHT   1002

class CAboutDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAboutDialog)

	// Construction
public:
	CAboutDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CAboutDialog)
	enum { IDD = IDD_ABOUTBOX };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DIALOGS_H__
