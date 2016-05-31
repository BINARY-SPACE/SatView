// MIMICSTEXTCTL.H : Mimics Text Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics text control related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSTEXTCTL_H__
#define __MIMICSTEXTCTL_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextCtrlDispatchDriver wrapper class

class CMimicsTextCtrlDispatchDriver : public CMimicsCtrlDispatchDriver
{
	// Construction
public:
	CMimicsTextCtrlDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsTextCtrlDispatchDriver(COleControl *pCtrl) : CMimicsCtrlDispatchDriver(pCtrl) {}
	CMimicsTextCtrlDispatchDriver(const CMimicsTextCtrlDispatchDriver &cDispatchSource) : CMimicsCtrlDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetMode(INT nMode);
	INT GetMode() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;
	BOOL SetFont(CONST LOGFONT *pFont);
	BOOL GetFont(LOGFONT *pFont) CONST;
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
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextCtrl

class CMimicsTextCtrl : public CMimicsCtrl
{
	DECLARE_DYNCREATE(CMimicsTextCtrl)

	// Constructor
public:
	CMimicsTextCtrl();
	~CMimicsTextCtrl();

	// Attributes
private:
	INT  m_nMode;
	INT  m_nTabs;
	UINT  m_nFormat;
	BOOL  m_bReading;
	CString  m_szText;
	COLORREF  m_nColor;
	COLORREF  m_nBkColor;
private:
	HFONT  m_hFont;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTextCtrl)
public:
	virtual void InitializeProps();
	virtual void DoPropExchange(CPropExchange *pPX);
public:
	virtual VOID DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape = FALSE);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	DECLARE_OLECREATE_EX(CMimicsTextCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMimicsTextCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMimicsTextCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMimicsTextCtrl)      // Type name and misc status

	// Message maps
	//{{AFX_MSG(CMimicsTextCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Dispatch maps
	//{{AFX_DISPATCH(CMimicsTextCtrl)
public:
	afx_msg void SetText(LPCTSTR pszText);
	afx_msg BSTR GetText() CONST;
	afx_msg void SetMode(LONG nMode);
	afx_msg LONG GetMode() CONST;
	afx_msg void SetColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetColor() CONST;
	afx_msg void SetBackgroundColor(OLE_COLOR nColor);
	afx_msg OLE_COLOR GetBackgroundColor() CONST;
	afx_msg BOOL SetFont(VARIANT *pFont);
	afx_msg BOOL GetFont(VARIANT *pFont) CONST;
	afx_msg void AlignLeft();
	afx_msg void AlignCenter();
	afx_msg void AlignRight();
	afx_msg void AlignVertical(BOOL bEnable);
	afx_msg BOOL IsLeftAligned() CONST;
	afx_msg BOOL IsCenterAligned() CONST;
	afx_msg BOOL IsRightAligned() CONST;
	afx_msg BOOL IsVerticalAligned() CONST;
	afx_msg void LeftToRightReading();
	afx_msg void TopToBottomReading();
	afx_msg BOOL IsLeftToRightReading() CONST;
	afx_msg BOOL IsTopToBottomReading() CONST;
	afx_msg void SetTabChars(LONG nChars);
	afx_msg LONG GetTabChars() CONST;
	afx_msg void WrapWords(BOOL bEnable);
	afx_msg BOOL IsWrappingWords() CONST;
	afx_msg void SingleLine(BOOL bEnable);
	afx_msg BOOL IsSingleLine() CONST;
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	// Event maps
	//{{AFX_EVENT(CMimicsTextCtrl)
	// NOTE - ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	// Dispatch and event IDs
public:
	enum {
		//{{AFX_DISP_ID(CMimicsTextCtrl)
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
		dispidText = 1L,
		dispidMode = 2L,
		dispidColor = 3L,
		dispidBackgroundColor = 4L,
		dispidSetFont = 5L,
		dispidGetFont = 6L,
		dispidAlignLeft = 7L,
		dispidAlignCenter = 8L,
		dispidAlignRight = 9L,
		dispidAlignVertical = 10L,
		dispidIsLeftAligned = 11L,
		dispidIsCenterAligned = 12L,
		dispidIsRightAligned = 13L,
		dispidIsVerticalAligned = 14L,
		dispidLeftToRightReading = 15L,
		dispidTopToBottomReading = 16L,
		dispidIsLeftToRightReading = 17L,
		dispidIsTopToBottomReading = 18L,
		dispidSetTabChars = 19L,
		dispidGetTabChars = 20L,
		dispidWrapWords = 21L,
		dispidIsWrappingWords = 22L,
		dispidSingleLine = 23L,
		dispidIsSingleLine = 24L
		//}}AFX_DISP_ID
	};
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSTEXTCTL_H__
