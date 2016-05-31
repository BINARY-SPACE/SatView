// MIMICSCTL.H : Mimics Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics control related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSCTL_H__
#define __MIMICSCTL_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsCtrlDispatchDriver wrapper class

class CMimicsCtrlDispatchDriver : public COleDispatchDriver
{
	// Construction
public:
	CMimicsCtrlDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsCtrlDispatchDriver(COleControl *pCtrl) : COleDispatchDriver(pCtrl -> GetIDispatch(TRUE)) {}
	CMimicsCtrlDispatchDriver(const CMimicsCtrlDispatchDriver &cDispatchSource) : COleDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(LPCTSTR pszType);
	CString GetType() CONST;
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;
	VOID SetInitialSize(CONST SIZE &size);
	CSize GetInitialSize() CONST;

protected:
	COleDispatchDriver *GetDispatchDriver() CONST;
	DISPID GetDispatchID(OLECHAR FAR *pszMethod) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsBlinkThread thread

class CMimicsBlinkThread : public CWinThread
{
	DECLARE_DYNCREATE(CMimicsBlinkThread)

	// Construction
public:
	CMimicsBlinkThread();
	~CMimicsBlinkThread();

	// Attributes
private:
	LONG  m_nInterval;
	CEvent  m_cEvent;

	// Operations
public:
	BOOL StartBlinking(class CMimicsCtrl *pCtrl, INT nInterval);
	BOOL StopBlinking(BOOL bWait = FALSE);

	BOOL IsBlinking() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsBlinkThread)
public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMimicsBlinkThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsCtrl

// Specify the mimics control default extensions
#define MIMICSCTRL_DEFAULT_CX   50
#define MIMICSCTRL_DEFAULT_CY   50

class CMimicsCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMimicsCtrl)

	// Constructor
public:
	CMimicsCtrl();
	~CMimicsCtrl();

	// Attributes
protected:
	CString  m_szName;
	CString  m_szType;
	CString  m_szToolTipText;
	CSize  m_sizeCtrl;
	LONG  m_bVisible;
private:
	CMimicsBlinkThread  m_cBlinkThread;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsCtrl)
public:
	virtual void InitializeProps();
	virtual HRESULT GetClassID(LPCLSID pclsid);
	virtual UINT GetUserTypeNameID();
	virtual DWORD GetControlFlags();
	virtual DWORD GetMiscStatus();
public:
	virtual VOID DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape = FALSE);
	virtual VOID DrawCtrl(HDC hDC, CONST RECT *pRect, CONST XFORM *pxForm, BOOL bShape = FALSE);
protected:
	virtual void OnDraw(CDC *pDC, const CRect &rcBounds, const CRect &rcInvalid);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	HPEN CreatePen(DWORD dwStyle, DWORD dwWidth, COLORREF nColor);
	HPEN CreatePen(DWORD dwStyle, DWORD dwWidth, COLORREF nColor, UINT lbStyle, LONG lbHatch);
	VOID DeletePen(HPEN hPen);

	// Message maps
	//{{AFX_MSG(CMimicsCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CMimicsCtrl)
public:
	afx_msg void SetName(LPCTSTR pszName);
	afx_msg BSTR GetName() CONST;
	afx_msg void SetType(LPCTSTR pszType);
	afx_msg BSTR GetType() CONST;
	afx_msg void SetToolTipText(LPCTSTR pszText);
	afx_msg BSTR GetToolTipText() CONST;
	afx_msg void SetInitialSize(OLE_XSIZE_PIXELS cx, OLE_YSIZE_PIXELS cy);
	afx_msg void GetInitialSize(OLE_XSIZE_PIXELS *cx, OLE_YSIZE_PIXELS *cy) CONST;
	afx_msg void Show();
	afx_msg void Hide();
	afx_msg BOOL IsVisible() CONST;
	afx_msg BOOL Blink(LONG nInterval);
	afx_msg void Draw(OLE_HANDLE hDC, VARIANT *pRect, VARIANT *pxForm, BOOL bShape);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	// Event maps
	//{{AFX_EVENT(CMimicsCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CMimicsCtrl)
		dispidName = 1L,
		dispidType = 2L,
		dispidToolTipText = 3L,
		dispidSetInitialSize = 4L,
		dispidGetInitialSize = 5L,
		dispidShow = 6L,
		dispidHide = 7L,
		dispidIsVisible = 8L,
		dispidBlink = 9L,
		dispidDraw = 10L
		//}}AFX_DISP_ID
	};
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSCTL_H__
