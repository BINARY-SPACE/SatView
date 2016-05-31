// MIMICSSWITCHCTL.H : Mimics Switch Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics switch control related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/06/28 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSSWITCHCTL_H__
#define __MIMICSSWITCHCTL_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchCtrlDispatchDriver wrapper class

class CMimicsSwitchCtrlDispatchDriver : public CMimicsCtrlDispatchDriver
{
	// Construction
public:
	CMimicsSwitchCtrlDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsSwitchCtrlDispatchDriver(COleControl *pCtrl) : CMimicsCtrlDispatchDriver(pCtrl) {}
	CMimicsSwitchCtrlDispatchDriver(const CMimicsSwitchCtrlDispatchDriver &cDispatchSource) : CMimicsCtrlDispatchDriver(cDispatchSource) {}

	// Attributes
public:

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
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchCtrl

// Specify the mimics switch control styles
#define MIMICSSWITCHCTRL_STYLE_SIMPLE   (1<<0)
#define MIMICSSWITCHCTRL_STYLE_DOUBLE   (1<<1)
#define MIMICSSWITCHCTRL_STYLE_FRAME   (1<<2)
#define MIMICSSWITCHCTRL_STYLE_STUBS   (1<<3)
#define MIMICSSWITCHCTRL_STYLE_OPENCLOSE   (1<<4)
#define MIMICSSWITCHCTRL_STYLE_TWOPOS   (1<<5)
#define MIMICSSWITCHCTRL_STYLE_THREEPOS   (1<<6)
// Specify the mimics switch control default extensions
#define MIMICSSWITCHCTRL_DEFAULT_CX   50
#define MIMICSSWITCHCTRL_DEFAULT_CY   20

class CMimicsSwitchCtrl : public CMimicsCtrl
{
	DECLARE_DYNCREATE(CMimicsSwitchCtrl)

	// Constructor
public:
	CMimicsSwitchCtrl();

	// Attributes
private:
	INT  m_nStyle;
	INT  m_nWidth;
	INT  m_nBarWidth;
	INT  m_nStubsWidth;
	INT  m_nFrameWidth;
	INT  m_nCenterWidth;
	OLE_COLOR  m_nColor;
	OLE_COLOR  m_nBarColor;
	OLE_COLOR  m_nStubsColor;
	OLE_COLOR  m_nFrameColor[2];
	OLE_COLOR  m_nCenterColor[2];
private:
	INT  m_nStatus;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSwitchCtrl)
public:
	virtual void InitializeProps();
	virtual void DoPropExchange(CPropExchange *pPX);
public:
	virtual VOID DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape = FALSE);
protected:
	virtual void OnResetState();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	DECLARE_OLECREATE_EX(CMimicsSwitchCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMimicsSwitchCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMimicsSwitchCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMimicsSwitchCtrl)      // Type name and misc status

	// Message maps
	//{{AFX_MSG(CMimicsSwitchCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CMimicsSwitchCtrl)
public:
	afx_msg void SetStyle(LONG nStyle);
	afx_msg LONG GetStyle() CONST;
	afx_msg void SetColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetColor() CONST;
	afx_msg void SetFrameColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetFrameColor() CONST;
	afx_msg void SetInteriorFrameColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetInteriorFrameColor() CONST;
	afx_msg void SetCenterColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetCenterColor() CONST;
	afx_msg void SetInteriorCenterColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetInteriorCenterColor() CONST;
	afx_msg void SetBarColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetBarColor() CONST;
	afx_msg void SetStubsColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetStubsColor() CONST;
	afx_msg void SetThickness(LONG nWidth);
	afx_msg LONG GetThickness() CONST;
	afx_msg void SetFrameThickness(LONG nWidth);
	afx_msg LONG GetFrameThickness() CONST;
	afx_msg void SetCenterThickness(LONG nWidth);
	afx_msg LONG GetCenterThickness() CONST;
	afx_msg void SetBarThickness(LONG nWidth);
	afx_msg LONG GetBarThickness() CONST;
	afx_msg void SetStubsThickness(LONG nWidth);
	afx_msg LONG GetStubsThickness() CONST;
	afx_msg void Open();
	afx_msg BOOL IsOpen() CONST;
	afx_msg BOOL IsClosed() CONST;
	afx_msg void Close();
	afx_msg void Pos1();
	afx_msg BOOL IsPos1() CONST;
	afx_msg void Pos2();
	afx_msg BOOL IsPos2() CONST;
	afx_msg void Pos3();
	afx_msg BOOL IsPos3() CONST;
	afx_msg void Broken();
	afx_msg BOOL IsBroken() CONST;
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	// Event maps
	//{{AFX_EVENT(CMimicsSwitchCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CMimicsSwitchCtrl)
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
		dispidFrameColor = 3L,
		dispidInteriorFrameColor = 4L,
		dispidCenterColor = 5L,
		dispidInteriorCenterColor = 6L,
		dispidBarColor = 7L,
		dispidStubsColor = 8L,
		dispidThickness = 9L,
		dispidFrameThickness = 10L,
		dispidCenterThickness = 11L,
		dispidBarThickness = 12L,
		dispidStubsThickness = 13L,
		dispidOpen = 14L,
		dispidIsOpen = 15L,
		dispidIsClosed = 16L,
		dispidClose = 17L,
		dispidPos1 = 18L,
		dispidIsPos1 = 19L,
		dispidPos2 = 20L,
		dispidIsPos2 = 21L,
		dispidPos3 = 22L,
		dispidIsPos3 = 23L,
		dispidBroken = 24L,
		dispidIsBroken = 25L
		//}}AFX_DISP_ID
	};
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSSWITCHCTL_H__
