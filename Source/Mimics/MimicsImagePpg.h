// MIMICSIMAGEPPG.H : Mimics Image Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics image control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/09/10 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSIMAGEPPG_H__
#define __MIMICSIMAGEPPG_H__

#include "resource.h"


////////////////////////////////////////////////////////////////////////////
// CMimicsImageGeneralPage dialog

#define IDC_MIMICSIMAGE_GENERALPAGE_DETAILS   1001
#define IDC_MIMICSIMAGE_GENERALPAGE_NAME_STATIC   1002
#define IDC_MIMICSIMAGE_GENERALPAGE_NAME   1003
#define IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP_STATIC   1004
#define IDC_MIMICSIMAGE_GENERALPAGE_TOOLTIP   1005

class CMimicsImageGeneralPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsImageGeneralPage)
	DECLARE_OLECREATE_EX(CMimicsImageGeneralPage)

	// Constructor
public:
	CMimicsImageGeneralPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsImageGeneralPage)
	enum { IDD = IDD_MIMICSIMAGE_GENERALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsImageGeneralPage)
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
	//{{AFX_MSG(CMimicsImageGeneralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeToolTipText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// CMimicsImageOutlinePage dialog

#define IDC_MIMICSIMAGE_OUTLINEPAGE_DETAILS   1001
#define IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_STATIC   1002
#define IDC_MIMICSIMAGE_OUTLINEPAGE_TYPE_NORMAL   1003
#define IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME_STATIC   1004
#define IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME   1005
#define IDC_MIMICSIMAGE_OUTLINEPAGE_FILENAME_BROWSE   1006
#define IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_STATIC   1007
#define IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X_STATIC   1008
#define IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_X   1009
#define IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y_STATIC   1010
#define IDC_MIMICSIMAGE_OUTLINEPAGE_ORIGIN_Y   1011
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_STATIC   1012
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X_STATIC   1013
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X   1014
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_X_PERCENT   1015
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y_STATIC   1016
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y   1017
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SIZE_Y_PERCENT   1018
#define IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY_STATIC   1019
#define IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY   1020
#define IDC_MIMICSIMAGE_OUTLINEPAGE_TRANSPARENCY_PERCENT   1021
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SAMPLE   1022
#define IDC_MIMICSIMAGE_OUTLINEPAGE_SAMPLE_IMAGE   1023

// Specify the mimics image outline page related settings
#define MIMICSIMAGEOUTLINEPAGE_MINIMUMSIZE   0
#define MIMICSIMAGEOUTLINEPAGE_MAXIMUMSIZE   1000
#define MIMICSIMAGEOUTLINEPAGE_DEFAULTSIZE   100
#define MIMICSIMAGEOUTLINEPAGE_MINIMUMTRANSPARENCY   0
#define MIMICSIMAGEOUTLINEPAGE_MAXIMUMTRANSPARENCY   100
#define MIMICSIMAGEOUTLINEPAGE_DEFAULTTRANSPARENCY   0

class CMimicsImageOutlinePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMimicsImageOutlinePage)
	DECLARE_OLECREATE_EX(CMimicsImageOutlinePage)

	// Constructor
public:
	CMimicsImageOutlinePage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMimicsImageOutlinePage)
	enum { IDD = IDD_MIMICSIMAGE_OUTLINEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetImageOrigin(CONST POINT &pt);
	CPoint GetImageOrigin() CONST;
	VOID SetImageSize(CONST SIZE &size);
	CSize GetImageSize() CONST;
	VOID SetImageTransparency(BYTE nFactor);
	BYTE GetImageTransparency() CONST;

private:
	VOID ShowDetails();
	VOID ShowSample();

	VOID DrawSample(CDC *pDC, CONST RECT &rect);

	BYTE ToTransparencyFactor(LONG nPercent) CONST;
	LONG ToTransparencyPercent(BYTE nFactor) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMimicsImageOutlinePage)
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
	//{{AFX_MSG(CMimicsImageOutlinePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTypeNormal();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSpinchangeImageXPos();
	afx_msg void OnSpinchangeImageYPos();
	afx_msg void OnSpinchangeImageXSize();
	afx_msg void OnSpinchangeImageYSize();
	afx_msg void OnSpinchangeImageTransparency();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSIMAGEPPG_H__
