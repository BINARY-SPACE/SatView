// MIMICSELLIPSEPPG.H : Mimics Ellipse Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics ellipse control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSELLIPSEPPG_H__
#define __MIMICSELLIPSEPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseGeneralPage dialog

#define IDC_MIMICSELLIPSE_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSELLIPSE_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSELLIPSE_GENERALPAGE_NAME   1003
#define IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP_STATIC   1004
#define IDC_MIMICSELLIPSE_GENERALPAGE_TOOLTIP   1005

class CMimicsEllipseGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsEllipseGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsEllipseGeneralPage)

	// Constructor
public:
	CMimicsEllipseGeneralPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsEllipseGeneralPage)
	enum { IDD = IDD_MIMICSELLIPSE_GENERALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsEllipseGeneralPage)
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
	//{{AFX_MSG(CMimicsEllipseGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseOutlinePage dialog

#define IDC_MIMICSELLIPSE_OUTLINEPAGE_DETAILS   1001
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_STATIC   1002
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_TYPE_NORMAL   1003
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER   1004
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE_STATIC   1005
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_STYLE   1006
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR_STATIC   1007
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_COLOR   1008
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE_STATIC   1009
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE   1010
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_BORDER_SIZE_PIXELS   1011
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR   1012
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR_STATIC   1013
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_COLOR   1014
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH_STATIC   1015
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCH   1016
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC   1017
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_HATCHCOLOR   1018
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_INTERIOR_TRANSPARENT   1019
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_SAMPLE   1020
#define IDC_MIMICSELLIPSE_OUTLINEPAGE_SAMPLE_IMAGE   1021

// Specify the mimics ellipse outline page related settings
#define MIMICSELLIPSEOUTLINEPAGE_MINIMIMTHICKNESS   1
#define MIMICSELLIPSEOUTLINEPAGE_MAXIMUMTHICKNESS   10
#define MIMICSELLIPSEOUTLINEPAGE_DEFAULTTHICKNESS   1

class CMimicsEllipseOutlinePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsEllipseOutlinePage)
	DECLARE_OLECREATE_EX(CMimicsEllipseOutlinePage)

	// Constructor
public:
	CMimicsEllipseOutlinePage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsEllipseOutlinePage)
	enum { IDD = IDD_MIMICSELLIPSE_OUTLINEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch, COLORREF nColor);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;

private:
	VOID ShowDetails();
	VOID ShowSample();

	VOID DrawSample(CDC *pDC, CONST RECT &rect);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsEllipseOutlinePage)
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
	//{{AFX_MSG(CMimicsEllipseOutlinePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTypeNormal();
	afx_msg void OnInteriorTransparent();
	afx_msg void OnSelchangeBorderStyle();
	afx_msg void OnSelchangeBorderColor();
	afx_msg void OnSelchangeInteriorColor();
	afx_msg void OnSelchangeInteriorHatch();
	afx_msg void OnSelchangeInteriorHatchColor();
	afx_msg void OnSpinchangeBorderSize();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSELLIPSEPPG_H__
