// MIMICS.H : Mimics Objects Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics objects related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/07/07 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICS_H__
#define __MIMICS_H__

#include "ttcprocess.h"


/////////////////////////////////////////////////////////////////////////////
// CMimicsClientItem

class AFX_EXT_CLASS CMimicsClientItem : public COleClientItem
{
	DECLARE_DYNCREATE(CMimicsClientItem)

	// Construction
public:
	CMimicsClientItem(COleDocument *pContainerDoc = NULL);

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsItem)
public:
	virtual VOID SetPosition(CONST RECT &rect);
	virtual CRect GetPosition() CONST;
	virtual VOID FlipHorizontal();
	virtual VOID FlipVertical();
	virtual VOID Rotate(double fAngle);
	//}}AFX_VIRTUAL

	// Implementation
public:
	LPOLEOBJECT GetOleObject() CONST;
	LPDISPATCH GetDispatch() CONST;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsClientItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsObjectDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsObjectDispatchDriver : public COleDispatchDriver
{
	// Construction
public:
	CMimicsObjectDispatchDriver();		// Calls COleDispatchDriver default constructor
	~CMimicsObjectDispatchDriver();

	// Attributes
protected:
	CMimicsClientItem  *m_pItem;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	VOID SetPosition(CONST RECT &rect);
	CRect GetPosition() CONST;
	VOID FlipHorizontal();
	VOID FlipVertical();
	VOID Rotate(double fAngle);

	VOID Show();
	VOID Hide();
	BOOL IsVisible() CONST;
	BOOL Blink(INT nInterval);

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);

public:
	VOID AttachDispatch(CMimicsClientItem *pItem, BOOL bAutoRelease = TRUE);
	VOID ReleaseDispatch();

protected:
	CMimicsClientItem *GetDispatchItem() CONST;
	COleDispatchDriver *GetDispatchDriver() CONST;
	DISPID GetDispatchID(OLECHAR FAR *pszMethod) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsLineDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsLineDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
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

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsRectangleDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsRectangleDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
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

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsEllipseDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsEllipseDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
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

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsArcDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsArcDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
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

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsTriangleDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsTriangleDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
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
	VOID SetEdges(double x1, double y1, double x2, double y2, double x3, double y3);
	VOID GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST;

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsSwitchDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsSwitchDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
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

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsTextDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsTextDispatchDriver() {}

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

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsImageDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsImageDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetImageOrigin(CONST POINT &pt);
	CPoint GetImageOrigin() CONST;
	VOID SetImageSize(CONST SIZE &size);
	CSize GetImageSize() CONST;
	VOID SetImageTransparency(BYTE nFactor);
	BYTE GetImageTransparency() CONST;

public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupDispatchDriver wrapper class

class AFX_EXT_CLASS CMimicsGroupDispatchDriver : public CMimicsObjectDispatchDriver
{
	// Construction
public:
	CMimicsGroupDispatchDriver() {}

	// Attributes
public:

	// Operations
public:
	virtual BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData = FALSE);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICS_H__
