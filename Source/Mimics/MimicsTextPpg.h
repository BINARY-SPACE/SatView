// MIMICSTEXTPPG.H : Mimics Text Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics text control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSTEXTPPG_H__
#define __MIMICSTEXTPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsTextGeneralPage dialog

#define IDC_MIMICSTEXT_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSTEXT_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSTEXT_GENERALPAGE_NAME   1003
#define IDC_MIMICSTEXT_GENERALPAGE_TEXT_STATIC   1004
#define IDC_MIMICSTEXT_GENERALPAGE_TEXT   1005
#define IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP_STATIC   1006
#define IDC_MIMICSTEXT_GENERALPAGE_TOOLTIP   1007

class CMimicsTextGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsTextGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsTextGeneralPage)

	// Constructor
public:
	CMimicsTextGeneralPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsTextGeneralPage)
	enum { IDD = IDD_MIMICSTEXT_GENERALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTextGeneralPage)
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
	//{{AFX_MSG(CMimicsTextGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeText();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsTextFontPage dialog

#define IDC_MIMICSTEXT_FONTPAGE_DETAILS   1001
#define IDC_MIMICSTEXT_FONTPAGE_NAME_STATIC   1002
#define IDC_MIMICSTEXT_FONTPAGE_NAME   1003
#define IDC_MIMICSTEXT_FONTPAGE_SIZE_STATIC   1004
#define IDC_MIMICSTEXT_FONTPAGE_SIZE   1005
#define IDC_MIMICSTEXT_FONTPAGE_SIZE_POINTS   1006
#define IDC_MIMICSTEXT_FONTPAGE_STYLE_STATIC   1007
#define IDC_MIMICSTEXT_FONTPAGE_STYLE_ITALIC   1008
#define IDC_MIMICSTEXT_FONTPAGE_STYLE_BOLD   1009
#define IDC_MIMICSTEXT_FONTPAGE_STYLE_UNDERLINE   1010
#define IDC_MIMICSTEXT_FONTPAGE_STYLE_STRIKEOUT   1011
#define IDC_MIMICSTEXT_FONTPAGE_SAMPLE   1012
#define IDC_MIMICSTEXT_FONTPAGE_SAMPLE_IMAGE   1013

class CMimicsTextFontPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsTextFontPage)
	DECLARE_OLECREATE_EX(CMimicsTextFontPage)

	// Constructor
public:
	CMimicsTextFontPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsTextFontPage)
	enum { IDD = IDD_MIMICSTEXT_FONTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL SetFont(CONST LOGFONT *pFont);
	BOOL GetFont(LOGFONT *pFont) CONST;

private:
	VOID ShowDetails();
	VOID ShowSample();

	VOID DrawSample(CDC *pDC, CONST RECT &rect);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTextFontPage)
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
	//{{AFX_MSG(CMimicsTextFontPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnStyleItalic();
	afx_msg void OnStyleBold();
	afx_msg void OnStyleUnderline();
	afx_msg void OnStyleStrikeout();
	afx_msg void OnSelchangeFont();
	afx_msg void OnSpinchangeSize();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsTextOutlinePage dialog

#define IDC_MIMICSTEXT_OUTLINEPAGE_DETAILS   1001
#define IDC_MIMICSTEXT_OUTLINEPAGE_MODE_STATIC   1002
#define IDC_MIMICSTEXT_OUTLINEPAGE_MODE_TRANSPARENT   1003
#define IDC_MIMICSTEXT_OUTLINEPAGE_MODE_OPAQUE   1004
#define IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_STATIC   1005
#define IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_LEFT   1006
#define IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_CENTER   1007
#define IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_RIGHT   1008
#define IDC_MIMICSTEXT_OUTLINEPAGE_ALIGN_VERTICAL   1009
#define IDC_MIMICSTEXT_OUTLINEPAGE_COLOR_STATIC   1010
#define IDC_MIMICSTEXT_OUTLINEPAGE_COLOR   1011
#define IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND_STATIC   1012
#define IDC_MIMICSTEXT_OUTLINEPAGE_BACKGROUND   1013
#define IDC_MIMICSTEXT_OUTLINEPAGE_TABS_STATIC   1014
#define IDC_MIMICSTEXT_OUTLINEPAGE_TABS   1015
#define IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS_STATIC 1016
#define IDC_MIMICSTEXT_OUTLINEPAGE_TABS_CHARS   1017
#define IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_STATIC   1018
#define IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_WORDWRAP   1019
#define IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_READING   1020
#define IDC_MIMICSTEXT_OUTLINEPAGE_OPTIONS_SINGLELINE   1021

// Specify the mimics text outline page related settings
#define MIMICSTEXTOUTLINEPAGE_MINIMUMTABS   2
#define MIMICSTEXTOUTLINEPAGE_MAXIMUMTABS   255
#define MIMICSTEXTOUTLINEPAGE_DEFAULTTABS   8

class CMimicsTextOutlinePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsTextOutlinePage)
	DECLARE_OLECREATE_EX(CMimicsTextOutlinePage)

	// Constructor
public:
	CMimicsTextOutlinePage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsTextOutlinePage)
	enum { IDD = IDD_MIMICSTEXT_OUTLINEPAGE };
	//}}AFX_DATA

	// Operations
public:
	VOID SetMode(INT nMode);
	INT GetMode() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;
	VOID AlignLeft();
	VOID AlignCenter();
	VOID AlignRight();
	VOID AlignVertical(BOOL bEnable);
	BOOL IsLeftAligned() CONST;
	BOOL IsCenterAligned() CONST;
	BOOL IsRightAligned() CONST;
	BOOL IsVerticalAligned() CONST;
	VOID LeftToRightReading();
	VOID TopToBottomReading();
	BOOL IsLeftToRightReading() CONST;
	BOOL IsTopToBottomReading() CONST;
	VOID SetTabChars(INT nChars);
	INT GetTabChars() CONST;
	VOID WrapWords(BOOL bEnable);
	BOOL IsWrappingWords() CONST;
	VOID SingleLine(BOOL bEnable);
	BOOL IsSingleLine() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTextOutlinePage)
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
	//{{AFX_MSG(CMimicsTextOutlinePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnModeTransparent();
	afx_msg void OnModeOpaque();
	afx_msg void OnAlignLeft();
	afx_msg void OnAlignCenter();
	afx_msg void OnAlignRight();
	afx_msg void OnAlignVertical();
	afx_msg void OnUseTabs();
	afx_msg void OnWrappingWords();
	afx_msg void OnVerticalReading();
	afx_msg void OnSingleLine();
	afx_msg void OnSelchangeColor();
	afx_msg void OnSelchangeBackground();
	afx_msg void OnSpinchangeTabChars();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSTEXTPPG_H__
