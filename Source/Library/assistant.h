// ASSISTANT.H : Assistant Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the assistant related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2001/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __ASSISTANT_H__
#define __ASSISTANT_H__

#ifndef RC_INVOKED
#include "language.h"
#endif

#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CAssistantSupportDateConversionsDialog dialog

#define IDC_ASSISTANTSUPPORT_DATECONVERSIONS_DETAILS   1001
#define IDC_ASSISTANTSUPPORT_DATECONVERSIONS_COMMENT_STATIC   1002
#define IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CALENDAR   1003
#define IDC_ASSISTANTSUPPORT_DATECONVERSIONS_SYMBOL_STATIC   1004
#define IDC_ASSISTANTSUPPORT_DATECONVERSIONS_DAYOFYEAR   1005
#define IDC_ASSISTANTSUPPORT_DATECONVERSIONS_CLOSE   1006

class AFX_EXT_CLASS CAssistantSupportDateConversionsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAssistantSupportDateConversionsDialog)

	// Construction
public:
	CAssistantSupportDateConversionsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
public:

	// Operations
public:

private:
	HGLOBAL LoadLocaleDialogTemplate(UINT nDialogID) CONST;
	HGLOBAL LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST;

	// Dialog Data
	//{{AFX_DATA(CAssistantSupportDateConversionsDialog)
	enum { IDD = IDD_ASSISTANTSUPPORT_DATECONVERSTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssistantSupportDateConversionsDialog)
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAssistantSupportDateConversionsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSpinchangeDayofYear();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __ASSISTANT_H__
