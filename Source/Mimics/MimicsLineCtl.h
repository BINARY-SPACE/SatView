// MIMICSLINECTL.H : Mimics Line Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics line control related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/03 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSLINECTL_H__
#define __MIMICSLINECTL_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineCtrlDispatchDriver wrapper class

class CMimicsLineCtrlDispatchDriver : public CMimicsCtrlDispatchDriver
{
	// Construction
public:
	CMimicsLineCtrlDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsLineCtrlDispatchDriver(COleControl *pCtrl) : CMimicsCtrlDispatchDriver(pCtrl) {}
	CMimicsLineCtrlDispatchDriver(const CMimicsLineCtrlDispatchDriver &cDispatchSource) : CMimicsCtrlDispatchDriver(cDispatchSource) {}

	// Attributes
public:

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
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineCtrl

// Specify the mimics line control styles
#define MIMICSLINECTRL_STYLE_SOLID   (1<<0)
#define MIMICSLINECTRL_STYLE_DASH   (1<<1)
#define MIMICSLINECTRL_STYLE_DOT   (1<<2)
#define MIMICSLINECTRL_STYLE_DASHDOT   (1<<3)
#define MIMICSLINECTRL_STYLE_DASHDOTDOT   (1<<4)
#define MIMICSLINECTRL_STYLE_CROSSING   (1<<5)
#define MIMICSLINECTRL_STYLE_ARROW   (1<<6)
#define MIMICSLINECTRL_STYLE_DOUBLEARROW   (1<<7)
// Specify the mimics line control default extensions
#define MIMICSLINECTRL_DEFAULT_CX   100
#define MIMICSLINECTRL_DEFAULT_CY   0

class CMimicsLineCtrl : public CMimicsCtrl
{
	DECLARE_DYNCREATE(CMimicsLineCtrl)

	// Constructor
public:
	CMimicsLineCtrl();

	// Attributes
private:
	INT  m_nStyle;
	INT  m_nWidth;
	OLE_COLOR  m_nColor;
	double  m_fPtCross;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsLineCtrl)
public:
	virtual void InitializeProps();
	virtual void DoPropExchange(CPropExchange *pPX);
public:
	virtual VOID DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape = FALSE);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	DECLARE_OLECREATE_EX(CMimicsLineCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMimicsLineCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMimicsLineCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMimicsLineCtrl)      // Type name and misc status

	// Message maps
	//{{AFX_MSG(CMimicsLineCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CMimicsLineCtrl)
public:
	afx_msg void SetStyle(LONG nStyle);
	afx_msg LONG GetStyle() CONST;
	afx_msg void Arrow(BOOL bEnable);
	afx_msg void DoubleArrow(BOOL bEnable);
	afx_msg void Cross(BOOL bEnable);
	afx_msg BOOL SetCrossPt(double fPt);
	afx_msg BOOL GetCrossPt(double *fPt) CONST;
	afx_msg BOOL IsArrow() CONST;
	afx_msg BOOL IsDoubleArrow() CONST;
	afx_msg BOOL IsCross() CONST;
	afx_msg void SetColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetColor() CONST;
	afx_msg void SetThickness(LONG nWidth);
	afx_msg LONG GetThickness() CONST;
	afx_msg void Solid();
	afx_msg void Dash();
	afx_msg void Dot();
	afx_msg void DashDot();
	afx_msg void DashDotDot();
	afx_msg BOOL IsSolid() CONST;
	afx_msg BOOL IsDashed() CONST;
	afx_msg BOOL IsDotted() CONST;
	afx_msg BOOL IsDashDotted() CONST;
	afx_msg BOOL IsDashDotDotted() CONST;
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	// Event maps
	//{{AFX_EVENT(CMimicsLineCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CMimicsLineCtrl)
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
		dispidColor = 2L,
		dispidThickness = 3L,
		dispidArrow = 4L,
		dispidDoubleArrow = 5L,
		dispidCross = 6L,
		dispidSetCrossPt = 7L,
		dispidGetCrossPt = 8L,
		dispidIsArrow = 9L,
		dispidIsDoubleArrow = 10L,
		dispidIsCross = 11L,
		dispidSolid = 12L,
		dispidDash = 13L,
		dispidDot = 14L,
		dispidDashDot = 15L,
		dispidDashDotDot = 16L,
		dispidIsSolid = 17L,
		dispidIsDashed = 18L,
		dispidIsDotted = 19L,
		dispidIsDashDotted = 20L,
		dispidIsDashDotDotted = 21L
		//}}AFX_DISP_ID
	};
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSLINECTL_H__
