// MIMICSRECTANGLEPPG.H : Mimics Rectangle Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics rectangle control dialog
// related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSRECTANGLEPPG_H__
#define __MIMICSRECTANGLEPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleGeneralPage dialog

#define IDC_MIMICSRECTANGLE_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSRECTANGLE_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSRECTANGLE_GENERALPAGE_NAME   1003
#define IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP_STATIC   1004
#define IDC_MIMICSRECTANGLE_GENERALPAGE_TOOLTIP   1005

class CMimicsRectangleGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsRectangleGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsRectangleGeneralPage)

	// Constructor
public:
	CMimicsRectangleGeneralPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsRectangleGeneralPage)
	enum { IDD = IDD_MIMICSRECTANGLE_GENERALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsRectangleGeneralPage)
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
	//{{AFX_MSG(CMimicsRectangleGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleOutlinePage dialog

#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_DETAILS   1001
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_STATIC   1002
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_NORMAL   1003
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_TYPE_ROUND   1004
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER   1005
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE_STATIC   1006
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_STYLE   1007
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR_STATIC   1008
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_COLOR   1009
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE_STATIC   1010
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE   1011
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_BORDER_SIZE_PIXELS   1012
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR   1013
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR_STATIC   1014
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_COLOR   1015
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH_STATIC   1016
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCH   1017
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC   1018
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_HATCHCOLOR   1019
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_INTERIOR_TRANSPARENT   1020
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_SAMPLE   1021
#define IDC_MIMICSRECTANGLE_OUTLINEPAGE_SAMPLE_IMAGE   1022

// Specify the mimics rectangle outline page related settings
#define MIMICSRECTANGLEOUTLINEPAGE_MINIMIMTHICKNESS   1
#define MIMICSRECTANGLEOUTLINEPAGE_MAXIMUMTHICKNESS   10
#define MIMICSRECTANGLEOUTLINEPAGE_DEFAULTTHICKNESS   1

class CMimicsRectangleOutlinePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsRectangleOutlinePage)
	DECLARE_OLECREATE_EX(CMimicsRectangleOutlinePage)

	// Constructor
public:
	CMimicsRectangleOutlinePage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsRectangleOutlinePage)
	enum { IDD = IDD_MIMICSRECTANGLE_OUTLINEPAGE };
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
	//{{AFX_VIRTUAL(CMimicsRectangleOutlinePage)
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
	//{{AFX_MSG(CMimicsRectangleOutlinePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTypeNormal();
	afx_msg void OnTypeRound();
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


#endif // __MIMICSRECTANGLEPPG_H__
