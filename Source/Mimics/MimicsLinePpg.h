// MIMICSLINEPPG.H : Mimics Line Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics line control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/03 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSLINEPPG_H__
#define __MIMICSLINEPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsLineGeneralPage dialog

#define IDC_MIMICSLINE_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSLINE_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSLINE_GENERALPAGE_NAME   1003
#define IDC_MIMICSLINE_GENERALPAGE_TOOLTIP_STATIC   1004
#define IDC_MIMICSLINE_GENERALPAGE_TOOLTIP   1005

class CMimicsLineGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsLineGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsLineGeneralPage)

	// Constructor
public:
	CMimicsLineGeneralPage();

	// Attributes
public:
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Dialog Data
	//{{AFX_DATA(CMimicsLineGeneralPage)
	enum { IDD = IDD_MIMICSLINE_GENERALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsLineGeneralPage)
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
	//{{AFX_MSG(CMimicsLineGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsLineOutlinePage dialog

#define IDC_MIMICSLINE_OUTLINEPAGE_DETAILS   1001
#define IDC_MIMICSLINE_OUTLINEPAGE_STYLE_STATIC   1002
#define IDC_MIMICSLINE_OUTLINEPAGE_STYLE   1003
#define IDC_MIMICSLINE_OUTLINEPAGE_COLOR_STATIC   1004
#define IDC_MIMICSLINE_OUTLINEPAGE_COLOR   1005
#define IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS_STATIC   1006
#define IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS   1007
#define IDC_MIMICSLINE_OUTLINEPAGE_THICKNESS_PIXELS   1008
#define IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_STATIC   1009
#define IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_CROSSING   1010
#define IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_ARROW   1011
#define IDC_MIMICSLINE_OUTLINEPAGE_EFFECTS_DOUBLEARROW   1012
#define IDC_MIMICSLINE_OUTLINEPAGE_SAMPLE   1013
#define IDC_MIMICSLINE_OUTLINEPAGE_SAMPLE_IMAGE   1014

// Specify the mimics line outline page related settings
#define MIMICSLINEOUTLINEPAGE_MINIMIMTHICKNESS   1
#define MIMICSLINEOUTLINEPAGE_MAXIMUMTHICKNESS   10
#define MIMICSLINEOUTLINEPAGE_DEFAULTTHICKNESS   1

class CMimicsLineOutlinePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsLineOutlinePage)
	DECLARE_OLECREATE_EX(CMimicsLineOutlinePage)

	// Constructor
public:
	CMimicsLineOutlinePage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsLineOutlinePage)
	enum { IDD = IDD_MIMICSLINE_OUTLINEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID Arrow(BOOL bEnable);
	VOID DoubleArrow(BOOL bEnable);
	VOID Cross(BOOL bEnable);
	BOOL SetCrossPt(double fPt);
	BOOL GetCrossPt(double *fPt) CONST;
	BOOL IsArrow() CONST;
	BOOL IsDoubleArrow() CONST;
	BOOL IsCross() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetThickness(INT nWidth);
	INT GetThickness() CONST;
	VOID Solid();
	VOID Dash();
	VOID Dot();
	VOID DashDot();
	VOID DashDotDot();
	BOOL IsSolid() CONST;
	BOOL IsDashed() CONST;
	BOOL IsDotted() CONST;
	BOOL IsDashDotted() CONST;
	BOOL IsDashDotDotted() CONST;

private:
	VOID ShowDetails();
	VOID ShowSample();

	VOID DrawSample(CDC *pDC, CONST RECT &rect);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsLineOutlinePage)
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
	//{{AFX_MSG(CMimicsLineOutlinePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEffectCrossing();
	afx_msg void OnEffectArrow();
	afx_msg void OnEffectDoubleArrow();
	afx_msg void OnSelchangeStyle();
	afx_msg void OnSelchangeColor();
	afx_msg void OnSpinchangeThickness();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSLINEPPG_H__
