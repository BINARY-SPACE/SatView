// MIMICSARCCTL.H : Mimics Arc Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics arc control related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/10/15 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSARCCTL_H__
#define __MIMICSARCCTL_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcCtrlDispatchDriver wrapper class

class CMimicsArcCtrlDispatchDriver : public CMimicsCtrlDispatchDriver
{
	// Construction
public:
	CMimicsArcCtrlDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsArcCtrlDispatchDriver(COleControl *pCtrl) : CMimicsCtrlDispatchDriver(pCtrl) {}
	CMimicsArcCtrlDispatchDriver(const CMimicsArcCtrlDispatchDriver &cDispatchSource) : CMimicsCtrlDispatchDriver(cDispatchSource) {}

	// Attributes
public:

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
	VOID SetRadials(double fRadial1, double fRadial2);
	VOID GetRadials(double &fRadial1, double &fRadial2) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcCtrl

// Specify the mimics arc control types
#define MIMICSARCCTRL_TYPE_ARC   (1<<0)
#define MIMICSARCCTRL_TYPE_PIE   (1<<1)
#define MIMICSARCCTRL_TYPE_CHORD   (1<<2)

class CMimicsArcCtrl : public CMimicsCtrl
{
	DECLARE_DYNCREATE(CMimicsArcCtrl)

	// Constructor
public:
	CMimicsArcCtrl();

	// Attributes
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	double  m_ptRadial[2];
	OLE_COLOR  m_nHatchColor;
	OLE_COLOR  m_nBorderColor;
	OLE_COLOR  m_nInteriorColor;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsArcCtrl)
public:
	virtual void InitializeProps();
	virtual void DoPropExchange(CPropExchange *pPX);
public:
	virtual VOID DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape = FALSE);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	DECLARE_OLECREATE_EX(CMimicsArcCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMimicsArcCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMimicsArcCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMimicsArcCtrl)      // Type name and misc status

	// Message maps
	//{{AFX_MSG(CMimicsArcCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CMimicsArcCtrl)
public:
	afx_msg void SetStyle(LONG nStyle);
	afx_msg LONG GetStyle() CONST;
	afx_msg void SetBorderSize(LONG nSize);
	afx_msg LONG GetBorderSize() CONST;
	afx_msg void SetBorderStyle(LONG nStyle);
	afx_msg LONG GetBorderStyle() CONST;
	afx_msg void SetBorderColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetBorderColor() CONST;
	afx_msg void SetInteriorColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetInteriorColor() CONST;
	afx_msg void SetInteriorHatch(LONG nHatch, OLE_COLOR nColor);
	afx_msg BOOL GetInteriorHatch(LONG *pHatch, OLE_COLOR *pColor) CONST;
	afx_msg void SetRadials(double fRadial1, double fRadial2);
	afx_msg void GetRadials(double *fRadial1, double *fRadial2) CONST;
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	// Event maps
	//{{AFX_EVENT(CMimicsArcCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CMimicsArcCtrl)
		dispidName = 65537L,
		dispidType = 65538L,
		dispidToolTipText = 65539L,
		dispidSetInitialSize = 65540L,
		dispidGetInitialSize = 65541L,
		dispidShow = 65542L,
		dispidHide = 65543L,
		dispidIsVisible = 65544L,
		dispidBlink = 65545L,
		dispidDraw = 65546L,
		dispidStyle = 1L,
		dispidBorderSize = 2L,
		dispidBorderStyle = 3L,
		dispidBorderColor = 4L,
		dispidInteriorColor = 5L,
		dispidSetInteriorHatch = 6L,
		dispidGetInteriorHatch = 7L,
		dispidSetRadials = 8L,
		dispidGetRadials = 9L
		//}}AFX_DISP_ID
	};
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSARCCTL_H__
