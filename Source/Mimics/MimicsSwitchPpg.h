// MIMICSSWITCHPPG.H : Mimics Switch Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics switch control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/06/28 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSSWITCHPPG_H__
#define __MIMICSSWITCHPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchGeneralPage dialog

#define IDC_MIMICSSWITCH_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSSWITCH_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSSWITCH_GENERALPAGE_NAME   1003
#define IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP_STATIC   1004
#define IDC_MIMICSSWITCH_GENERALPAGE_TOOLTIP   1005

class CMimicsSwitchGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsSwitchGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsSwitchGeneralPage)

	// Constructor
public:
	CMimicsSwitchGeneralPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsSwitchGeneralPage)
	enum { IDD = IDD_MIMICSSWITCH_GENERALPAGE };
	//}}AFX_DATA

	// Operations
public:
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSwitchGeneralPage)
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
	//{{AFX_MSG(CMimicsSwitchGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchOutlinePage dialog

#define IDC_MIMICSSWITCH_OUTLINEPAGE_DETAILS   1001
#define IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_STATIC   1002
#define IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_SIMPLE   1003
#define IDC_MIMICSSWITCH_OUTLINEPAGE_TYPE_DOUBLE   1004
#define IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_STATIC   1005
#define IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_OPENCLOSE   1006
#define IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_TWOPOS   1007
#define IDC_MIMICSSWITCH_OUTLINEPAGE_BEHAVIOR_THREEPOS   1008
#define IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_STATIC   1009
#define IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR_ITEM   1010
#define IDC_MIMICSSWITCH_OUTLINEPAGE_COLOR   1011
#define IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_STATIC   1012
#define IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_ITEM   1013
#define IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS_PIXELS   1014
#define IDC_MIMICSSWITCH_OUTLINEPAGE_THICKNESS   1015
#define IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STATIC   1016
#define IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_ROUNDEDFRAME   1017
#define IDC_MIMICSSWITCH_OUTLINEPAGE_STYLE_STUBS   1018
#define IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE   1019
#define IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_SIMPLE   1020
#define IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_DOUBLE   1021
#define IDC_MIMICSSWITCH_OUTLINEPAGE_SAMPLE_FRAME   1022

// Specify the mimics switch outline page related settings
#define MIMICSSWITCHOUTLINEPAGE_MINIMIMTHICKNESS   1
#define MIMICSSWITCHOUTLINEPAGE_MAXIMUMTHICKNESS   5
#define MIMICSSWITCHOUTLINEPAGE_DEFAULTTHICKNESS   1

class CMimicsSwitchOutlinePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsSwitchOutlinePage)
	DECLARE_OLECREATE_EX(CMimicsSwitchOutlinePage)

	// Constructor
public:
	CMimicsSwitchOutlinePage();

	// Attributes
private:
	CUIntArray  m_nColors[2];
	CUIntArray  m_nWidths[2];

	// Dialog Data
	//{{AFX_DATA(CMimicsSwitchOutlinePage)
	enum { IDD = IDD_MIMICSSWITCH_OUTLINEPAGE };
	//}}AFX_DATA

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetFrameColor(COLORREF nColor);
	COLORREF GetFrameColor() CONST;
	VOID SetInteriorFrameColor(COLORREF nColor);
	COLORREF GetInteriorFrameColor() CONST;
	VOID SetCenterColor(COLORREF nColor);
	COLORREF GetCenterColor() CONST;
	VOID SetInteriorCenterColor(COLORREF nColor);
	COLORREF GetInteriorCenterColor() CONST;
	VOID SetBarColor(COLORREF nColor);
	COLORREF GetBarColor() CONST;
	VOID SetStubsColor(COLORREF nColor);
	COLORREF GetStubsColor() CONST;
	VOID SetThickness(INT nWidth);
	INT GetThickness() CONST;
	VOID SetFrameThickness(INT nWidth);
	INT GetFrameThickness() CONST;
	VOID SetCenterThickness(INT nWidth);
	INT GetCenterThickness() CONST;
	VOID SetBarThickness(INT nWidth);
	INT GetBarThickness() CONST;
	VOID SetStubsThickness(INT nWidth);
	INT GetStubsThickness() CONST;

public:
	VOID Open();
	BOOL IsOpen() CONST;
	BOOL IsClosed() CONST;
	VOID Close();
	VOID Pos1();
	BOOL IsPos1() CONST;
	VOID Pos2();
	BOOL IsPos2() CONST;
	VOID Pos3();
	BOOL IsPos3() CONST;
	VOID Broken();
	BOOL IsBroken() CONST;

private:
	BOOL EnumColorsText();
	BOOL EnumThicknessText();

	VOID ShowDetails();
	VOID ShowSample();

	VOID DrawSample(CDC *pDC, CONST RECT &rect);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSwitchOutlinePage)
public:
	virtual VOID Update();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support

	// Message maps
protected:
	//{{AFX_MSG(CMimicsSwitchOutlinePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTypeSimple();
	afx_msg void OnTypeDouble();
	afx_msg void OnBehaviorOpenClose();
	afx_msg void OnBehaviorTwoPos();
	afx_msg void OnBehaviorThreePos();
	afx_msg void OnStyleRoundedFrame();
	afx_msg void OnStyleStubs();
	afx_msg void OnSelchangeColorItem();
	afx_msg void OnSelchangeColor();
	afx_msg void OnSelchangeThicknessItem();
	afx_msg void OnSpinchangeThickness();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSSWITCHPPG_H__
