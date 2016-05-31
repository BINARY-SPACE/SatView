// MIMICSGROUPCTL.H : Mimics Group Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics group control related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/05/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSGROUPCTL_H__
#define __MIMICSGROUPCTL_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupCtrlDispatchDriver wrapper class

class CMimicsGroupCtrlDispatchDriver : public CMimicsCtrlDispatchDriver
{
	// Construction
public:
	CMimicsGroupCtrlDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsGroupCtrlDispatchDriver(COleControl *pCtrl) : CMimicsCtrlDispatchDriver(pCtrl) {}
	CMimicsGroupCtrlDispatchDriver(const CMimicsGroupCtrlDispatchDriver &cDispatchSource) : CMimicsCtrlDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupCtrl

class CMimicsGroupCtrl : public CMimicsCtrl
{
	DECLARE_DYNCREATE(CMimicsGroupCtrl)

	// Constructor
public:
	CMimicsGroupCtrl();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsGroupCtrl)
public:
	virtual void InitializeProps();
	virtual void DoPropExchange(CPropExchange *pPX);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	DECLARE_OLECREATE_EX(CMimicsGroupCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMimicsGroupCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMimicsGroupCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMimicsGroupCtrl)      // Type name and misc status

	// Message maps
	//{{AFX_MSG(CMimicsGroupCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CMimicsGroupCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	// Event maps
	//{{AFX_EVENT(CMimicsGroupCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CMimicsGroupCtrl)
		dispidName = 65537L,
		dispidType = 65538L,
		dispidToolTipText = 65539L,
		dispidSetInitialSize = 65540L,
		dispidGetInitialSize = 65541L,
		dispidShow = 65542L,
		dispidHide = 65543L,
		dispidIsVisible = 65544L,
		dispidBlink = 65545L,
		dispidDraw = 65546L
		//}}AFX_DISP_ID
	};
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSGROUPCTL_H__
