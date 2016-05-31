// LOGO.H : Logo Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the logo related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __LOGO_H__
#define __LOGO_H__


/////////////////////////////////////////////////////////////////////////////
// CLogoWnd window

// Specify the logo related identifiers
#define LOGO_TIMERID   0
#define LOGO_TIMEOUT   5000

class CLogoWnd : public CWnd
{
	DECLARE_DYNCREATE(CLogoWnd)

	// Construction
public:
	CLogoWnd();

	// Attributes
private:
	HANDLE  m_hLogo;
	CBitmap  m_bmLogo;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, HANDLE hLogo);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogoWnd)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogoWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __LOGO_H__
