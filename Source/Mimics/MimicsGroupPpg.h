// MIMICSGROUPPPG.H : Mimics Group Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics group control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/05/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSGROUPPPG_H__
#define __MIMICSGROUPPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsGroupGeneralPage dialog

#define IDC_MIMICSGROUP_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSGROUP_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSGROUP_GENERALPAGE_NAME   1003
#define IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP_STATIC   1004
#define IDC_MIMICSGROUP_GENERALPAGE_TOOLTIP   1005

class CMimicsGroupGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsGroupGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsGroupGeneralPage)

	// Constructor
public:
	CMimicsGroupGeneralPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsGroupGeneralPage)
	enum { IDD = IDD_MIMICSGROUP_GENERALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsGroupGeneralPage)
public:
	virtual VOID Update();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support

	// Message maps
protected:
	//{{AFX_MSG(CMimicsGroupGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSGROUPPPG_H__
