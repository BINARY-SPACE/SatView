// MIMICSARCPPG.H : Mimics Arc Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics arc control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/10/15 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSARCPPG_H__
#define __MIMICSARCPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsArcGeneralPage dialog

#define IDC_MIMICSARC_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSARC_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSARC_GENERALPAGE_NAME   1003
#define IDC_MIMICSARC_GENERALPAGE_TOOLTIP_STATIC   1004
#define IDC_MIMICSARC_GENERALPAGE_TOOLTIP   1005

class CMimicsArcGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsArcGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsArcGeneralPage)

	// Constructor
public:
	CMimicsArcGeneralPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsArcGeneralPage)
	enum { IDD = IDD_MIMICSARC_GENERALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsArcGeneralPage)
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
	//{{AFX_MSG(CMimicsArcGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsArcOutlinePage dialog

#define IDC_MIMICSARC_OUTLINEPAGE_DETAILS   1001
#define IDC_MIMICSARC_OUTLINEPAGE_TYPE_STATIC   1002
#define IDC_MIMICSARC_OUTLINEPAGE_TYPE_ARC   1003
#define IDC_MIMICSARC_OUTLINEPAGE_TYPE_PIE   1004
#define IDC_MIMICSARC_OUTLINEPAGE_TYPE_CHORD   1005
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER   1006
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE_STATIC   1007
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER_STYLE   1008
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR_STATIC   1009
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER_COLOR   1010
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE_STATIC   1011
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE   1012
#define IDC_MIMICSARC_OUTLINEPAGE_BORDER_SIZE_PIXELS   1013
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR   1014
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR_STATIC   1015
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_COLOR   1016
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH_STATIC   1017
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCH   1018
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR_STATIC   1019
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_HATCHCOLOR   1020
#define IDC_MIMICSARC_OUTLINEPAGE_INTERIOR_TRANSPARENT   1021
#define IDC_MIMICSARC_OUTLINEPAGE_SAMPLE   1022
#define IDC_MIMICSARC_OUTLINEPAGE_SAMPLE_IMAGE   1023

// Specify the mimics arc outline page related settings
#define MIMICSARCOUTLINEPAGE_MINIMIMTHICKNESS   1
#define MIMICSARCOUTLINEPAGE_MAXIMUMTHICKNESS   10
#define MIMICSARCOUTLINEPAGE_DEFAULTTHICKNESS   1

class CMimicsArcOutlinePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsArcOutlinePage)
	DECLARE_OLECREATE_EX(CMimicsArcOutlinePage)

	// Constructor
public:
	CMimicsArcOutlinePage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsArcOutlinePage)
	enum { IDD = IDD_MIMICSARC_OUTLINEPAGE };
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
	//{{AFX_VIRTUAL(CMimicsArcOutlinePage)
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
	//{{AFX_MSG(CMimicsArcOutlinePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTypeArc();
	afx_msg void OnTypePie();
	afx_msg void OnTypeChord();
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


#endif // __MIMICSARCPPG_H__
