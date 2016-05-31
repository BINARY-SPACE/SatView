// MIMICSIMAGECTL.H : Mimics Image Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics image control related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/09/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSIMAGECTL_H__
#define __MIMICSIMAGECTL_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageCtrlDispatchDriver wrapper class

class CMimicsImageCtrlDispatchDriver : public CMimicsCtrlDispatchDriver
{
	// Construction
public:
	CMimicsImageCtrlDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsImageCtrlDispatchDriver(COleControl *pCtrl) : CMimicsCtrlDispatchDriver(pCtrl) {}
	CMimicsImageCtrlDispatchDriver(const CMimicsImageCtrlDispatchDriver &cDispatchSource) : CMimicsCtrlDispatchDriver(cDispatchSource) {}

	// Attributes
public:

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
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageCtrl

// Specify the mimics image control types
#define MIMICSIMAGECTRL_TYPE_NORMAL   (1<<0)

class CMimicsImageCtrl : public CMimicsCtrl
{
	DECLARE_DYNCREATE(CMimicsImageCtrl)

	// Constructor
public:
	CMimicsImageCtrl();
	~CMimicsImageCtrl();

	// Attributes
private:
	INT  m_nStyle;
	CImage  m_cImage;
	CString  m_szFileName;
	CPoint  m_ptImage;
	CSize  m_sizeImage;
	BYTE  m_nImageTransparency;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsImageCtrl)
public:
	virtual void InitializeProps();
	virtual void DoPropExchange(CPropExchange *pPX);
public:
	virtual VOID DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape = FALSE);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	DECLARE_OLECREATE_EX(CMimicsImageCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMimicsImageCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMimicsImageCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMimicsImageCtrl)      // Type name and misc status

	// Message maps
	//{{AFX_MSG(CMimicsImageCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CMimicsImageCtrl)
public:
	afx_msg void SetStyle(LONG nStyle);
	afx_msg LONG GetStyle() CONST;
	afx_msg void SetFileName(LPCTSTR pszFileName);
	afx_msg BSTR GetFileName() CONST;
	afx_msg void SetImageOrigin(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y);
	afx_msg void GetImageOrigin(OLE_XPOS_PIXELS *x, OLE_YPOS_PIXELS *y) CONST;
	afx_msg void SetImageSize(OLE_XSIZE_PIXELS cx, OLE_YSIZE_PIXELS cy);
	afx_msg void GetImageSize(OLE_XSIZE_PIXELS *cx, OLE_YSIZE_PIXELS *cy) CONST;
	afx_msg void SetImageTransparency(BYTE nFactor);
	afx_msg BYTE GetImageTransparency() CONST;
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	// Event maps
	//{{AFX_EVENT(CMimicsImageCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CMimicsImageCtrl)
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
		dispidFileName = 2L,
		dispidImageTransparency = 3L,
		dispidSetImageOrigin = 4L,
		dispidGetImageOrigin = 5L,
		dispidSetImageSize = 6L,
		dispidGetImageSize = 7L
		//}}AFX_DISP_ID
	};
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSIMAGECTL_H__
