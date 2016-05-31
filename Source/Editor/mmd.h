// MMD.H : Mimics Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics display related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MMD_H__
#define __MMD_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CMMDDocument document

class CMMDDocument : public COleDocument
{
	DECLARE_DYNCREATE(CMMDDocument)

	// Construction
public:
	CMMDDocument();
	virtual ~CMMDDocument();

	// Attributes
private:
	BOOL  m_bAutoClose;

	// Operations
public:
	INT EnumItems(CPtrArray &pItems) CONST;

	POSITION FindItem(CMimicsClientItem *pItem) CONST;

	UINT GetItemCount() CONST;

	BOOL Copy(CONST CMMDDocument *pDocument, BOOL bAll = FALSE);
	BOOL Compare(CONST CMMDDocument *pDocument, BOOL bAll = FALSE) CONST;

	BOOL Map(CMMDLayout &cLayout, CONST POINT &ptOrigin) CONST;
	BOOL Unmap(CONST CMMDLayout &cLayout, CONST POINT &ptOrigin);

private:
	BOOL EnumItemsInList(CONST CMMDDocument *pDocument, CPtrArray &pItems) CONST;

	POSITION FindItemInList(CONST CMMDDocument *pDocument, CMimicsClientItem *pItem) CONST;
	CONST CMMDDocument *FindPositionInList(CONST CMMDDocument *pDocument, POSITION lPosition) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDDocument)
public:
	virtual POSITION GetStartPosition() CONST;
	virtual POSITION GetStopPosition() CONST;
	virtual CDocItem *GetNextItem(POSITION &lPosition) CONST;
	virtual CDocItem *GetPreviousItem(POSITION &lPosition) CONST;
	virtual void Serialize(CArchive &ar);   // overridden for document i/o
	virtual BOOL SaveModified();
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	virtual BOOL CanCloseFrame(CFrameWnd *pFrame);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDDocument)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsItemDispatchDriver wrapper class

class CMimicsItemDispatchDriver : public COleDispatchDriver
{
	// Construction
public:
	CMimicsItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsItemDispatchDriver(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMimicsItemDispatchDriver(const CMimicsItemDispatchDriver &cDispatchSource) : COleDispatchDriver(cDispatchSource) {}

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

	VOID Show();
	VOID Hide();
	BOOL IsVisible() CONST;
	BOOL Blink(INT nInterval);

	VOID Draw(HDC hDC, CONST RECT *pRect, CONST XFORM *pxForm, BOOL bShape = FALSE);

protected:
	COleDispatchDriver *GetDispatchDriver() CONST;
	DISPID GetDispatchID(OLECHAR FAR *pszMethod) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItemDispatchDriver wrapper class

class CMimicsLineItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsLineItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsLineItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsLineItemDispatchDriver(const CMimicsLineItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
// CMimicsRectangleItemDispatchDriver wrapper class

class CMimicsRectangleItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsRectangleItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsRectangleItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsRectangleItemDispatchDriver(const CMimicsRectangleItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItemDispatchDriver wrapper class

class CMimicsEllipseItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsEllipseItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsEllipseItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsEllipseItemDispatchDriver(const CMimicsEllipseItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItemDispatchDriver wrapper class

class CMimicsArcItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsArcItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsArcItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsArcItemDispatchDriver(const CMimicsArcItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
// CMimicsTriangleItemDispatchDriver wrapper class

class CMimicsTriangleItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsTriangleItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsTriangleItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsTriangleItemDispatchDriver(const CMimicsTriangleItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
	VOID SetEdges(double x1, double y1, double x2, double y2, double x3, double y3);
	VOID GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItemDispatchDriver wrapper class

class CMimicsSwitchItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsSwitchItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsSwitchItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsSwitchItemDispatchDriver(const CMimicsSwitchItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
// CMimicsTextItemDispatchDriver wrapper class

class CMimicsTextItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsTextItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsTextItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsTextItemDispatchDriver(const CMimicsTextItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
// CMimicsImageItemDispatchDriver wrapper class

class CMimicsImageItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsImageItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsImageItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsImageItemDispatchDriver(const CMimicsImageItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

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
// CMimicsGroupItemDispatchDriver wrapper class

class CMimicsGroupItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsGroupItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsGroupItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsGroupItemDispatchDriver(const CMimicsGroupItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsItem

// Specify the mimics item area codes
#define MIAC_NOWHERE   0
#define MIAC_SWTHUMB   1
#define MIAC_WTHUMB   2
#define MIAC_NWTHUMB   3
#define MIAC_NTHUMB   4
#define MIAC_NETHUMB   5
#define MIAC_ETHUMB   6
#define MIAC_SETHUMB   7
#define MIAC_STHUMB   8
#define MIAC_THUMBS   8
#define MIAC_INSIDE   9
#define MIAC_DRAGTHUMB   10
#define MIAC_FIRSTTHUMB   11
#define MIAC_LASTTHUMB   12
#define MIAC_FIRSTRADIALTHUMB   13
#define MIAC_LASTRADIALTHUMB   14
// Specify the mimics item activation thumb and grid size
#define MIMICSITEM_THUMB_SIZE   6
#define MIMICSITEM_GRID_SIZE   5

class CMimicsItem : public CMimicsClientItem
{
	DECLARE_DYNCREATE(CMimicsItem)

	// Construction
public:
	CMimicsItem(CMMDDocument *pContainerDoc = NULL);
	~CMimicsItem();

	// Attributes
protected:
	CLSID  m_clsid;
	CString  m_szName;
	CString  m_szType;
	CString  m_szText;
	CString  m_szLink;
	XFORM  m_xForm;
	CRect  m_rPosition[2];
	CPoint  m_ptCenter;
	BOOL  m_bVisible;
protected:
	CDC  *m_pDC;
	BOOL  m_bOriginal;
	BOOL  m_bSelected;
	BOOL  m_bActivated;
	BOOL  m_bRotateFlag;
	BOOL  m_bProperties;
	LPOLEINPLACEOBJECTWINDOWLESS  m_pOleInPlaceObjectWindowless;
protected:
	CByteArray  m_nInfo;
protected:
	CMimicsItem  *m_pContainerItem;
	CView  *m_pImageView;
private:
	LONG  m_bLocked;

	// Operations
public:
	static CMimicsItem *Create(CLSID &clsid, CView *pView, CMMDDocument *pDocument, CPoint point);
	static CMimicsItem *Create(CMimicsItem *pItem, CView *pView, CMMDDocument *pDocument);

	static CMimicsItem *AllocateFromItem(CMimicsItem *pItem, CMMDDocument *pDocument = NULL);
	static CMimicsItem *AllocateFromItem(CMMDLayoutItem *pItem, CMMDDocument *pDocument = NULL);
	static CMimicsItem *AllocateFromData(CONST CByteArray &nData, CMMDDocument *pDocument = NULL);

	VOID SetItemName(LPCTSTR pszName = NULL);
	CString GetItemName() CONST;
	VOID SetItemClassID(CLSID clsid);
	CLSID GetItemClassID() CONST;
	VOID SetItemType(LPCTSTR pszType = NULL);
	CString GetItemType() CONST;
	VOID SetItemLink(LPCTSTR pszName);
	CString GetItemLink() CONST;
	VOID SetItemSize(INT cx = 0, INT cy = 0);
	CSize GetItemSize() CONST;
	VOID SetItemToolTipText(LPCTSTR pszText = NULL);
	CString GetItemToolTipText() CONST;
	VOID SetItemRotateMode(BOOL bFlag);
	BOOL GetItemRotateMode() CONST;
	VOID ActivateItem(BOOL bActivate = TRUE);
	VOID ActivateItem(LONG nVerb, CView *pView = NULL, LPMSG lpMsg = NULL);
	BOOL IsItemActivated(BOOL bInPlace = FALSE) CONST;
	BOOL SelectItem(BOOL bSelect = FALSE);
	BOOL IsItemSelected() CONST;
	VOID ShowItem();
	VOID HideItem();
	BOOL IsItemVisible() CONST;
	VOID SetItemVisibility(UINT bVisible = -1);
	BOOL GetItemVisibility() CONST;
	VOID SetItemProperties(CONST CByteArray &nInfo);
	BOOL GetItemProperties(CByteArray &nInfo) CONST;
	VOID SetItemContainer(CMimicsItem *pItem = NULL);
	CMimicsItem *GetItemContainer() CONST;
	VOID AdjustItemContainer();
	VOID SetItemImage(CView *pView = NULL);
	CView *GetItemImage() CONST;

	CRect DoTransformation(CONST RECT &rect) CONST;
	CPoint DoTransformation(CONST POINT &point) CONST;
	VOID DoTransformation(XFORM &xForm, CRect &rPosition) CONST;
	VOID DoTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	VOID DoTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	CPoint DoInverseTransformation(CONST POINT &point) CONST;
	VOID DoInverseTransformation(XFORM &xForm, CRect &rPosition) CONST;
	VOID DoInverseTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	VOID DoInverseTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	CPoint CalcTransform(CONST POINT &point) CONST;
	CPoint CalcTransform(CONST XFORM &xForm, CONST POINT &point) CONST;
	CPoint CalcTransform(CONST POINT &ptCenter, CONST POINT &point) CONST;
	CPoint CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST POINT &point) CONST;
	CRect CalcTransform(CONST RECT &rect) CONST;
	CRect CalcTransform(CONST XFORM &xForm, CONST RECT &rect) CONST;
	CRect CalcTransform(CONST POINT &ptCenter, CONST RECT &rect) CONST;
	CRect CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST RECT &rect) CONST;

	BOOL Lock();
	BOOL IsLocked() CONST;
	BOOL Unlock();

protected:
	VOID BuildInverseTransform(XFORM &xForm) CONST;

	VOID DrawItem();
	VOID DrawItem(CONST RECT &rect);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsItem)
public:
	virtual	BOOL CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render = OLERENDER_DRAW, CLIPFORMAT cfFormat = 0, LPFORMATETC lpFormatEtc = NULL);
	virtual BOOL Draw(CDC *pDC, BOOL bShape = FALSE);
	virtual VOID SetPosition(CONST RECT &rect);
	virtual CRect GetPosition() CONST;
	virtual VOID FlipHorizontal();
	virtual VOID FlipVertical();
	virtual VOID Rotate(double fAngle);
	virtual VOID ResetState();
	virtual void Release(OLECLOSE dwCloseOption = OLECLOSE_NOSAVE);
public:
	virtual VOID SetItemPosition(CONST RECT &rect);
	virtual CRect GetItemPosition() CONST;
	virtual VOID GetItemPosition(CPoint &point, CSize &size) CONST;
	virtual VOID NormalizeItemPosition(BOOL bUndo = FALSE);
	virtual VOID AdjustItemPosition();
	virtual VOID AdjustItemPosition(CONST RECT &rect);
	virtual VOID SetItemDefaultPosition(CONST RECT &rect);
	virtual CRect GetItemDefaultPosition() CONST;
	virtual VOID AdjustItemDefaultPosition();
	virtual VOID SetItemCenterPoint();
	virtual VOID SetItemCenterPoint(CONST POINT &ptCenter);
	virtual CPoint GetItemCenterPoint() CONST;
	virtual VOID AdjustItemCenterPoint();
	virtual VOID HorzFlipItem();
	virtual VOID VertFlipItem();
	virtual VOID RotateItem(double fAngle);
	virtual BOOL IsItemFlippedOrRotated() CONST;
	virtual BOOL IsItemSizeable() CONST;
	virtual VOID DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld);
	virtual BOOL DrawItemFrame(CDC *pDC, CONST RECT &rect);
	virtual BOOL DrawItemDraggingFrame(CDC *pDC, CONST RECT &rect);
	virtual CRect CalcItemFrameExtent() CONST;
	virtual CRect CalcItemFramePosition() CONST;
	virtual CRect CalcItemFrameThumbPosition(UINT nCode, CONST RECT &rect) CONST;
	virtual INT CalcItemFrameThumbPositions(CONST RECT &rect, LPRECT prThumbs = NULL, INT nThumbs = 0) CONST;
	virtual CRect CalcItemFrameTurnThumbPosition(UINT nCode, CONST RECT &rect) CONST;
	virtual INT CalcItemFrameTurnThumbPositions(CONST RECT &rect, LPRECT prThumbs = NULL, INT nThumbs = 0) CONST;
	virtual INT CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints = NULL, INT nPoints = 0) CONST;
	virtual BOOL CalcItemShape(CBitmap *pBitmap);
	virtual UINT CheckPointOnItem(CONST POINT &ptPosition);
	virtual BOOL CheckPointInsideItem(CONST POINT &ptPosition);
	virtual BOOL CheckItemOnItem(CMimicsItem *pItem);
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID InitializeProperties();
	virtual VOID UpdateProperties();
	virtual BOOL IsUpdatingProperties() CONST;
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	virtual BOOL Map(CMMDLayoutItem *pItem, CONST POINT &ptOrigin);
	virtual BOOL Map(CByteArray &nData);
	virtual BOOL Map(CByteArray &nData, CONST POINT &ptOrigin);
	virtual BOOL Unmap(CONST CMMDLayoutItem *pItem, CONST POINT &ptOrigin);
	virtual BOOL Unmap(CONST CByteArray &nData);
	virtual BOOL Unmap(CONST CByteArray &nData, CONST POINT &ptOrigin);
protected:
	virtual void OnGetClipRect(CRect &rClip);
	virtual void OnGetItemPosition(CRect &rPosition);
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnDeactivate();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Interface
public:
	BEGIN_INTERFACE_PART(OleInPlaceSiteWindowless, IOleInPlaceSiteWindowless)
		INIT_INTERFACE_PART(CMimicsClientItem, OleInPlaceSiteWindowless)
		STDMETHOD(GetWindow)(HWND *phWnd);
		STDMETHOD(ContextSensitiveHelp)(BOOL bEnter);
		STDMETHOD(GetWindowContext)(IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT prectPos, LPRECT prectClip, LPOLEINPLACEFRAMEINFO pFrameInfo);
		STDMETHOD(CanWindowlessActivate)();
		STDMETHOD(CanInPlaceActivate)();
		STDMETHOD(RequestUIActivate)();
		STDMETHOD(DeactivateAndUndo)();
		STDMETHOD(DiscardUndoState)();
		STDMETHOD(Scroll)(SIZE sizeExtent);
		STDMETHOD(SetCapture)(BOOL bCapture);
		STDMETHOD(GetCapture)();
		STDMETHOD(SetFocus)(BOOL bFocus);
		STDMETHOD(GetFocus)();
		STDMETHOD(GetDC)(LPCRECT prect, DWORD dwFlags, HDC *phDC);
		STDMETHOD(ReleaseDC)(HDC hDC);
		STDMETHOD(InvalidateRect)(LPCRECT prect, BOOL bErase);
		STDMETHOD(InvalidateRgn)(HRGN hRgn, BOOL bErase);
		STDMETHOD(AdjustRect)(LPRECT prect);
		STDMETHOD(ScrollRect)(int dx, int dy, LPCRECT prectScroll, LPCRECT prectClip);
		STDMETHOD(OnInPlaceActivate)();
		STDMETHOD(OnInPlaceDeactivate)();
		STDMETHOD(OnInPlaceActivateEx)(BOOL *pbNoRedraw, DWORD dwFlags);
		STDMETHOD(OnInPlaceDeactivateEx)(BOOL bNoRedraw);
		STDMETHOD(OnUIActivate)();
		STDMETHOD(OnUIDeactivate)(BOOL bUndoable);
		STDMETHOD(OnPosRectChange)(LPCRECT prectPos);
		STDMETHOD(OnDefWindowMessage)(UINT nMessage, WPARAM wParam, LPARAM lParam, LRESULT *plResult);
	END_INTERFACE_PART(OleInPlaceSiteWindowless)

	DECLARE_INTERFACE_MAP()

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsItems

class CMimicsItems : public CPtrArray
{
	// Construction
public:
	CMimicsItems();
	~CMimicsItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CMimicsItem *pMimicsItem);

	INT Find(LPCTSTR pszName) CONST;

	CMimicsItem *GetAt(INT nIndex) CONST;
	CMimicsItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CMimicsItems *pMimicsItems, BOOL bAll = FALSE);
	BOOL Compare(CONST CMimicsItems *pMimicsItems, BOOL bAll = FALSE) CONST;

	BOOL Map(CByteArray &nData) CONST;
	BOOL Unmap(CONST CByteArray &nData);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItem

class CMimicsLineItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsLineItem)

	// Construction
public:
	CMimicsLineItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nWidth;
		BOOL  bCrossing;
		BOOL  bArrow[2];
		double  fPtCross;
		COLORREF  nColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nWidth;
	BOOL  m_bCrossing;
	BOOL  m_bArrow[2];
	double  m_fPtCross;
	COLORREF  m_nColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = PS_SOLID);
	INT GetStyle() CONST;
	VOID Arrow(BOOL bEnable = FALSE);
	VOID DoubleArrow(BOOL bEnable = FALSE);
	VOID Cross(BOOL bEnable = FALSE);
	BOOL SetCrossPt(double fPt = 0.0);
	BOOL GetCrossPt(double *fPt) CONST;
	BOOL IsArrow() CONST;
	BOOL IsDoubleArrow() CONST;
	BOOL IsCross() CONST;
	VOID SetColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetColor() CONST;
	VOID SetThickness(INT nWidth = 1);
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

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsLineItem)
public:
	virtual VOID SetItemPosition(CONST RECT &rect);
	virtual CRect GetItemPosition() CONST;
	virtual VOID GetItemPosition(CPoint &point, CSize &size) CONST;
	virtual VOID DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld);
	virtual BOOL DrawItemFrame(CDC *pDC, CONST RECT &rect);
	virtual BOOL DrawItemDraggingFrame(CDC *pDC, CONST RECT &rect);
	virtual CRect CalcItemFrameExtent() CONST;
	virtual CRect CalcItemFramePosition() CONST;
	virtual CRect CalcItemFrameThumbPosition(UINT nCode, CONST RECT &rect) CONST;
	virtual INT CalcItemFrameThumbPositions(CONST RECT &rect, LPRECT prThumbs = NULL, INT nThumbs = 0) CONST;
	virtual CRect CalcItemFrameTurnThumbPosition(UINT nCode, CONST RECT &rect) CONST;
	virtual INT CalcItemFrameTurnThumbPositions(CONST RECT &rect, LPRECT prThumbs = NULL, INT nThumbs = 0) CONST;
	virtual INT CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints = NULL, INT nPoints = 0) CONST;
	virtual BOOL CalcItemFrameCrossThumbPosition(CONST RECT &rect, LPRECT prThumb) CONST;
	virtual UINT CheckPointOnItem(CONST POINT &ptPosition);
	virtual BOOL CheckPointInsideItem(CONST POINT &ptPosition);
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsLineItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItem

class CMimicsRectangleItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsRectangleItem)

	// Construction
public:
	CMimicsRectangleItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsRectangleItem)
public:
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsRectangleItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItem

class CMimicsEllipseItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsEllipseItem)

	// Construction
public:
	CMimicsEllipseItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsEllipseItem)
public:
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsEllipseItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItem

class CMimicsArcItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsArcItem)

	// Construction
public:
	CMimicsArcItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		double  ptRadial[2];
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	double  m_ptRadial[2];
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
	VOID SetRadials(double fRadial1 = 0.0, double fRadial2 = 0.0);
	VOID GetRadials(double &fRadial1, double &fRadial2) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsArcItem)
public:
	virtual VOID DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld);
	virtual BOOL DrawItemFrame(CDC *pDC, CONST RECT &rect);
	virtual INT CalcItemFrameRadialThumbPositions(CONST RECT &rect, LPRECT prThumbs = NULL, INT nThumbs = 0) CONST;
	virtual INT CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints = NULL, INT nPoints = 0) CONST;
	virtual UINT CheckPointOnItem(CONST POINT &ptPosition);
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID InitializeProperties();
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsArcItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItem

class CMimicsTriangleItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsTriangleItem)

	// Construction
public:
	CMimicsTriangleItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		double  ptEdges[3][2];
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	double  m_ptEdges[3][2];
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
	VOID SetEdges(double x1 = 0.0, double y1 = 0.0, double x2 = 0.0, double y2 = 0.0, double x3 = 0.0, double y3 = 0.0);
	VOID GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTriangleItem)
public:
	virtual VOID DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld);
	virtual BOOL DrawItemFrame(CDC *pDC, CONST RECT &rect);
	virtual UINT CheckPointOnItem(CONST POINT &ptPosition);
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID InitializeProperties();
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsTriangleItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItem

class CMimicsSwitchItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsSwitchItem)

	// Construction
public:
	CMimicsSwitchItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nWidth;
		INT  nBarWidth;
		INT  nStubsWidth;
		INT  nFrameWidth;
		INT  nCenterWidth;
		COLORREF  nColor;
		COLORREF  nBarColor;
		COLORREF  nStubsColor;
		COLORREF  nFrameColor[2];
		COLORREF  nCenterColor[2];
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nWidth;
	INT  m_nBarWidth;
	INT  m_nStubsWidth;
	INT  m_nFrameWidth;
	INT  m_nCenterWidth;
	COLORREF  m_nColor;
	COLORREF  m_nBarColor;
	COLORREF  m_nStubsColor;
	COLORREF  m_nFrameColor[2];
	COLORREF  m_nCenterColor[2];

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetColor() CONST;
	VOID SetFrameColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetFrameColor() CONST;
	VOID SetInteriorFrameColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorFrameColor() CONST;
	VOID SetCenterColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetCenterColor() CONST;
	VOID SetInteriorCenterColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorCenterColor() CONST;
	VOID SetBarColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBarColor() CONST;
	VOID SetStubsColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetStubsColor() CONST;
	VOID SetThickness(INT nWidth = 1);
	INT GetThickness() CONST;
	VOID SetFrameThickness(INT nWidth = 2);
	INT GetFrameThickness() CONST;
	VOID SetCenterThickness(INT nWidth = 1);
	INT GetCenterThickness() CONST;
	VOID SetBarThickness(INT nWidth = 1);
	INT GetBarThickness() CONST;
	VOID SetStubsThickness(INT nWidth = 1);
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

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSwitchItem)
public:
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
public:
	virtual VOID ResetState();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsSwitchItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItem

class CMimicsTextItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsTextItem)

	// Construction
public:
	CMimicsTextItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbText;
		INT  nMode;
		INT  nTabs;
		UINT  nFormat;
		BOOL  bReading;
		LOGFONT  lfFont;
		COLORREF  nColor;
		COLORREF  nBkColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nMode;
	INT  m_nTabs;
	UINT  m_nFormat;
	BOOL  m_bReading;
	LOGFONT  m_lfFont;
	CString  m_szText;
	COLORREF  m_nColor;
	COLORREF  m_nBkColor;

	// Operations
public:
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetMode(INT nMode = TRANSPARENT);
	INT GetMode() CONST;
	VOID SetColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetBackgroundColor() CONST;
	BOOL SetFont(CONST LOGFONT *pFont = NULL);
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
	VOID SetTabChars(INT nChars = -1);
	INT GetTabChars() CONST;
	VOID WrapWords(BOOL bEnable = FALSE);
	BOOL IsWrappingWords() CONST;
	VOID SingleLine(BOOL bEnable = FALSE);
	BOOL IsSingleLine() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTextItem)
public:
	virtual BOOL CheckPointInsideItem(CONST POINT &ptPosition);
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsTextItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItem

class CMimicsImageItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsImageItem)

	// Construction
public:
	CMimicsImageItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbFileName;
		INT  nStyle;
		POINT  ptImage;
		SIZE  sizeImage;
		BYTE  nImageTransparency;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	CString  m_szFileName;
	CPoint  m_ptImage;
	CSize  m_sizeImage;
	BYTE  m_nImageTransparency;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetFileName(LPCTSTR pszFileName = EMPTYSTRING);
	CString GetFileName() CONST;
	VOID SetImageOrigin(CONST POINT &pt = CPoint(0, 0));
	CPoint GetImageOrigin() CONST;
	VOID SetImageSize(CONST SIZE &size = CSize(100, 100));
	CSize GetImageSize() CONST;
	VOID SetImageTransparency(BYTE nFactor = 0xFF);
	BYTE GetImageTransparency() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsImageItem)
public:
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual VOID UpdateProperties();
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsImageItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroup

class CMimicsGroup : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsGroup)

	// Construction
public:
	CMimicsGroup(CMMDDocument *pContainerDoc = NULL);
	CMimicsGroup(LPCTSTR pszName, CMMDDocument *pContainerDoc = NULL);
	~CMimicsGroup();

	// Attributes
private:
	CMMDDocument  *m_pItemList;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	VOID AddItem(CMimicsItem *pItem);
	VOID RemoveItem(CMimicsItem *pItem);

	CMimicsItem *GetAt(INT nIndex) CONST;
	CMimicsItem *operator[](INT nIndex) CONST;

	CMMDDocument *GetItemList() CONST;

	INT GetItemCount() CONST;

	VOID RemoveAllItems();

public:
	BOOL SaveAsStandardFile(LPCTSTR pszFileName);
	BOOL LoadAsStandardFile(LPCTSTR pszFileName);
	BOOL SaveAsMetafile(LPCTSTR pszFileName);
	BOOL SaveAsBitmap(LPCTSTR pszFileName);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsGroup)
public:
	virtual	BOOL CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render = OLERENDER_DRAW, CLIPFORMAT cfFormat = 0, LPFORMATETC lpFormatEtc = NULL);
	virtual BOOL Draw(CDC *pDC, BOOL bShape = FALSE);
public:
	virtual VOID SetItemPosition(CONST RECT &rect);
	virtual CRect GetItemPosition() CONST;
	virtual VOID NormalizeItemPosition(BOOL bUndo = FALSE);
	virtual VOID AdjustItemPosition();
	virtual VOID AdjustItemPosition(CONST RECT &rect);
	virtual VOID AdjustItemCenterPoint();
	virtual BOOL IsItemSizeable() CONST;
	virtual UINT CheckPointOnItem(CONST POINT &ptPosition);
	virtual BOOL CheckPointInsideItem(CONST POINT &ptPosition);
	virtual BOOL MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin);
	virtual BOOL Copy(CONST CMimicsItem *pItem, BOOL bAll = FALSE);
	virtual BOOL Compare(CONST CMimicsItem *pItem, BOOL bAll = FALSE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsGroup)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroups

class CMimicsGroups : public CPtrArray
{
	// Construction
public:
	CMimicsGroups();
	~CMimicsGroups();

	// Attributes
public:

	// Operations
public:
	INT Add(CMimicsGroup *pMimicsGroup);

	INT Find(LPCTSTR pszName) CONST;

	CMimicsGroup *GetAt(INT nIndex) CONST;
	CMimicsGroup *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CMimicsGroups *pMimicsGroups, BOOL bAll = FALSE);
	BOOL Compare(CONST CMimicsGroups *pMimicsGroups, BOOL bAll = FALSE) CONST;

	BOOL Map(CByteArray &nData) CONST;
	BOOL Unmap(CONST CByteArray &nData);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDUndoItem

class CMMDUndoItem : public CObject
{
	// Construction
public:
	CMMDUndoItem();
	~CMMDUndoItem();

	// Attributes
private:
	CMMDDocument  *m_pDocument[2];
	INT  m_nIndex;

	// Operations
public:
	BOOL SetInfo(CONST CMMDDocument *pDocument, CONST CMMDDocument *pOldDocument, INT nIndex);
	INT GetInfo(CMMDDocument *pDocument, CMMDDocument *pOldDocument) CONST;

	BOOL Copy(CONST CMMDUndoItem *pItem);
	BOOL Compare(CONST CMMDUndoItem *pItem) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDUndoList

class CMMDUndoList : public CPtrArray
{
	// Construction
public:
	CMMDUndoList();
	~CMMDUndoList();

	// Attributes
private:
	CMMDDocument  *m_pDocument;
	INT  m_nIndex[2];
private:
	INT  m_bLocked;

	// Operations
public:
	BOOL Update(CONST CMMDDocument *pDocument, BOOL bReset = FALSE);

	BOOL Undo(CMMDDocument *pDocument);
	BOOL Redo(CMMDDocument *pDocument);
	BOOL CanUndo() CONST;
	BOOL CanRedo() CONST;

	CMMDUndoItem *GetAt(INT nIndex) CONST;
	CMMDUndoItem *operator[](INT nIndex) CONST;

	VOID Reset();

	VOID Lock();
	BOOL IsLocked() CONST;
	VOID Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSaveDialog dialog

#define IDC_MMD_SAVE_DETAILS   1001
#define IDC_MMD_SAVE_DATABASE_STATIC   1002
#define IDC_MMD_SAVE_DATABASE   1003
#define IDC_MMD_SAVE_TITLE_STATIC   1004
#define IDC_MMD_SAVE_TITLE   1005
#define IDC_MMD_SAVE_NUMBER_STATIC   1006
#define IDC_MMD_SAVE_NUMBER   1007
#define IDC_MMD_SAVE_COMMENT_STATIC   1008
#define IDC_MMD_SAVE_COMMENT   1009
#define IDC_MMD_SAVE_DIRECTORY_STATIC   1010
#define IDC_MMD_SAVE_DIRECTORY   1011
#define IDC_MMD_SAVE_HELP   1012

class CMMDSaveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDSaveDialog)

	// Construction
public:
	CMMDSaveDialog();   // standard constructor

	// Attributes
private:
	CMMDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDSaveDialog)
	enum { IDD = IDD_MMD_SAVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

private:
	VOID EnumMMDs();

	BOOL FindMMD(LPCTSTR pszNumber) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDSaveDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDSaveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnEditchangeNumber();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDOpenDialog dialog

#define IDC_MMD_OPEN_DETAILS   1001
#define IDC_MMD_OPEN_DATABASE_STATIC   1002
#define IDC_MMD_OPEN_DATABASE   1003
#define IDC_MMD_OPEN_DIRECTORY_STATIC   1004
#define IDC_MMD_OPEN_DIRECTORY   1005
#define IDC_MMD_OPEN_HELP   1006

class CMMDOpenDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMMDOpenDialog)

	// Construction
public:
	CMMDOpenDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CMMDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDOpenDialog)
	enum { IDD = IDD_MMD_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumMMDs();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDOpenDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDImportDialog dialog

#define IDC_MMD_IMPORT_DETAILS   1001
#define IDC_MMD_IMPORT_FILENAME_STATIC   1002
#define IDC_MMD_IMPORT_FILENAME   1003
#define IDC_MMD_IMPORT_BROWSE   1004
#define IDC_MMD_IMPORT_DIRECTORY   1005
#define IDC_MMD_IMPORT_TYPE   1006
#define IDC_MMD_IMPORT_TYPE_DEFAULT   1007
#define IDC_MMD_IMPORT_TYPE_CUSTOM   1008
#define IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER   1009
#define IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER_STATIC   1010
#define IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1011
#define IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION    1012
#define IDC_MMD_IMPORT_HELP   1013

class CMMDImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMMDImportDialog)

	// Construction
public:
	CMMDImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CMMDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDImportDialog)
	enum { IDD = IDD_MMD_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumMMDs();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDImportDialog)
public:
	virtual INT_PTR DoModal();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeNumber();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDExportDialog dialog

#define IDC_MMD_EXPORT_DETAILS   1001
#define IDC_MMD_EXPORT_DIRECTORY_STATIC   1002
#define IDC_MMD_EXPORT_DIRECTORY   1003
#define IDC_MMD_EXPORT_FILENAME_STATIC   1004
#define IDC_MMD_EXPORT_FILENAME   1005
#define IDC_MMD_EXPORT_BROWSE   1006
#define IDC_MMD_EXPORT_TYPE   1007
#define IDC_MMD_EXPORT_TYPE_DEFAULT   1008
#define IDC_MMD_EXPORT_TYPE_CUSTOM   1009
#define IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER   1010
#define IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER_STATIC   1011
#define IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1012
#define IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION   1013
#define IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE   1014
#define IDC_MMD_EXPORT_HELP   1015

class CMMDExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMMDExportDialog)

	// Construction
public:
	CMMDExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CMMDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDExportDialog)
	enum { IDD = IDD_MMD_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumMMDs();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDExportDialog)
public:
	virtual INT_PTR DoModal();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnSourceCode();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeNumber();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDPropertiesDialog dialog

#define IDC_MMD_PROPERTIES_DETAILS   1001
#define IDC_MMD_PROPERTIES_SIZE_STATIC   1002
#define IDC_MMD_PROPERTIES_SIZE_DEFAULT   1003
#define IDC_MMD_PROPERTIES_SIZE_FIXED   1004
#define IDC_MMD_PROPERTIES_SIZE_FIXED_X   1005
#define IDC_MMD_PROPERTIES_SIZE_FIXED_STATIC   1006
#define IDC_MMD_PROPERTIES_SIZE_FIXED_Y   1007
#define IDC_MMD_PROPERTIES_SIZE_FIXED_UNITS   1008
#define IDC_MMD_PROPERTIES_MARGINS_STATIC   1009
#define IDC_MMD_PROPERTIES_MARGINS_LEFT_STATIC   1010
#define IDC_MMD_PROPERTIES_MARGINS_LEFT   1011
#define IDC_MMD_PROPERTIES_MARGINS_RIGHT_STATIC   1012
#define IDC_MMD_PROPERTIES_MARGINS_RIGHT   1013
#define IDC_MMD_PROPERTIES_MARGINS_TOP_STATIC   1014
#define IDC_MMD_PROPERTIES_MARGINS_TOP  1015
#define IDC_MMD_PROPERTIES_MARGINS_TOP_PIXELS   1016
#define IDC_MMD_PROPERTIES_MARGINS_BOTTOM_STATIC   1017
#define IDC_MMD_PROPERTIES_MARGINS_BOTTOM   1018
#define IDC_MMD_PROPERTIES_MARGINS_BOTTOM_PIXELS   1019
#define IDC_MMD_PROPERTIES_BACKGROUND_STATIC   1020
#define IDC_MMD_PROPERTIES_BACKGROUND   1021
#define IDC_MMD_PROPERTIES_GRID_STATIC   1022
#define IDC_MMD_PROPERTIES_GRID_POINTS   1023
#define IDC_MMD_PROPERTIES_GRID_LINES   1024
#define IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_STATIC   1025
#define IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL   1026
#define IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_UNITS   1027
#define IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_STATIC   1028
#define IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL   1029
#define IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_UNITS   1030
#define IDC_MMD_PROPERTIES_GRID_SHOWALWAYS   1031
#define IDC_MMD_PROPERTIES_GRID_COLOR_STATIC   1032
#define IDC_MMD_PROPERTIES_GRID_COLOR   1033
#define IDC_MMD_PROPERTIES_HELP   1034

// Specify the mimics display window default settings
#define MMDPROPERTIESDIALOG_DEFAULT_IMAGEWIDTH   450
#define MMDPROPERTIESDIALOG_DEFAULT_IMAGEHEIGHT   300
#define MMDPROPERTIESDIALOG_DEFAULT_GRIDINTERVAL   50

class CMMDPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDPropertiesDialog)

	// Construction
public:
	CMMDPropertiesDialog();   // standard constructor

	// Attributes
private:
	INT  m_nImage[2][4];
	CSize  m_sizeGrid[2];
	CSize  m_sizeImage[2];
	COLORREF  m_nImageGrid[2];
	COLORREF  m_nImageBkgnd[2];
	BOOL  m_bUseGrid[2];

	// Dialog Data
	//{{AFX_DATA(CMMDPropertiesDialog)
	enum { IDD = IDD_MMD_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDPropertiesDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDefaultSize();
	afx_msg void OnFixedSize();
	afx_msg void OnGridPoints();
	afx_msg void OnGridLines();
	afx_msg void OnShowGrid();
	afx_msg void OnSelchangeBackgroundColor();
	afx_msg void OnSelchangeGridColor();
	afx_msg void OnSpinchangeHorizontalSize();
	afx_msg void OnSpinchangeVerticalSize();
	afx_msg void OnSpinchangeLeftMargin();
	afx_msg void OnSpinchangeRightMargin();
	afx_msg void OnSpinchangeTopMargin();
	afx_msg void OnSpinchangeBottomMargin();
	afx_msg void OnSpinchangeHorizontalGridInterval();
	afx_msg void OnSpinchangeVerticalGridInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDLinkInformationDialog dialog

#define IDC_MMD_LINKINFORMATION_DETAILS   1001
#define IDC_MMD_LINKINFORMATION_NAME_STATIC   1002
#define IDC_MMD_LINKINFORMATION_NAME   1003
#define IDC_MMD_LINKINFORMATION_DISPLAY_STATIC  1004
#define IDC_MMD_LINKINFORMATION_DISPLAY   1005
#define IDC_MMD_LINKINFORMATION_HELP   1006

class CMMDLinkInformationDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDLinkInformationDialog)

	// Construction
public:
	CMMDLinkInformationDialog();   // standard constructor

	// Attributes
private:
	INT  m_nIndex;
	CMMDLayouts  m_pDisplays;

	// Dialog Data
	//{{AFX_DATA(CMMDLinkInformationDialog)
	enum { IDD = IDD_MMD_LINKINFORMATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

private:
	INT EnumDisplays();

	INT FindDisplay(LPCTSTR pszName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDLinkInformationDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDLinkInformationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeDisplay();
	afx_msg void OnSelchangeDisplay();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDCreateMimicsGroupDialog dialog

#define IDC_MMD_CREATEMIMICSGROUP_DETAILS   1001
#define IDC_MMD_CREATEMIMICSGROUP_NAME_STATIC   1002
#define IDC_MMD_CREATEMIMICSGROUP_NAME   1003
#define IDC_MMD_CREATEMIMICSGROUP_PREVIEW_STATIC   1004
#define IDC_MMD_CREATEMIMICSGROUP_PREVIEW   1005
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS   1006
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION_STATIC   1007
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION   1008
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS_STATIC   1009
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS   1010
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS_ADD   1011
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS_REMOVE   1012
#define IDC_MMD_CREATEMIMICSGROUP_MEMBERS_REMOVEALL   1013
#define IDC_MMD_CREATEMIMICSGROUP_HELP   1014

class CMMDCreateMimicsGroupDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDCreateMimicsGroupDialog)

	// Construction
public:
	CMMDCreateMimicsGroupDialog();   // standard constructor

	// Attributes
private:
	CPtrArray  m_pMimicsObjects;
	CMimicsGroups  m_pMimicsGroups;
	CMimicsItems  m_pMimicsItems[3];
	CMMDDocument  *m_pMimicsDocument;
private:
	CStringArray  m_szColumns[2];

	// Dialog Data
	//{{AFX_DATA(CMMDCreateMimicsGroupDialog)
	enum { IDD = IDD_MMD_CREATEMIMICSGROUP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumMimicsGroups();
	BOOL EnumMimicsObjects();

	VOID ShowMimicsGroupContents();
	VOID ShowMimicsGroupContents(LPCTSTR pszGroup);
	VOID DrawMimicsGroupPreviewPicture();
	VOID DrawMimicsGroupPreviewPicture(CDC *pDC);

	BOOL BuildMimicsGroupMemberItem(CMimicsItem *pItem);
	CMimicsItem *DuplicateMimicsGroupMemberItem(CMimicsItem *pItem);

	CSize CalcMimicsGroupPreviewSize() CONST;

	INT CalcColumnWidth(LPCTSTR pszTitle, CONST CStringArray &szItems);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDCreateMimicsGroupDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDCreateMimicsGroupDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnAddMember();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDDeleteMimicsGroupDialog dialog

#define IDC_MMD_DELETEMIMICSGROUP_DETAILS   1001
#define IDC_MMD_DELETEMIMICSGROUP_LIST_STATIC   1002
#define IDC_MMD_DELETEMIMICSGROUP_LIST   1003
#define IDC_MMD_DELETEMIMICSGROUP_DELETEGROUP   1004
#define IDC_MMD_DELETEMIMICSGROUP_DELETEALLGROUPS   1005
#define IDC_MMD_DELETEMIMICSGROUP_HELP   1006

class CMMDDeleteMimicsGroupDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDDeleteMimicsGroupDialog)

	// Construction
public:
	CMMDDeleteMimicsGroupDialog();   // standard constructor

	// Attributes
private:
	CMimicsGroups  m_pMimicsGroups;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDDeleteMimicsGroupDialog)
	enum { IDD = IDD_MMD_DELETEMIMICSGROUP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumMimicsGroups();

	INT CalcColumnWidth(CONST CStringArray &szItems);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDDeleteMimicsGroupDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDDeleteMimicsGroupDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeleteGroup();
	afx_msg void OnDeleteAllGroups();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDInsertMimicsGroupDialog dialog

#define IDC_MMD_INSERTMIMICSGROUP_DETAILS   1001
#define IDC_MMD_INSERTMIMICSGROUP_LIST_STATIC   1002
#define IDC_MMD_INSERTMIMICSGROUP_LIST   1003
#define IDC_MMD_INSERTMIMICSGROUP_HELP   1004

class CMMDInsertMimicsGroupDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDInsertMimicsGroupDialog)

	// Construction
public:
	CMMDInsertMimicsGroupDialog();   // standard constructor

	// Attributes
private:
	CMimicsGroups  m_pMimicsGroups;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDInsertMimicsGroupDialog)
	enum { IDD = IDD_MMD_INSERTMIMICSGROUP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumMimicsGroups();

	INT CalcColumnWidth(CONST CStringArray &szItems);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDInsertMimicsGroupDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDInsertMimicsGroupDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDImportMimicsGroupDialog dialog

#define IDC_MMD_IMPORTMIMICSGROUP_DETAILS   1001
#define IDC_MMD_IMPORTMIMICSGROUP_FILENAME_STATIC   1002
#define IDC_MMD_IMPORTMIMICSGROUP_FILENAME   1003
#define IDC_MMD_IMPORTMIMICSGROUP_BROWSE   1004
#define IDC_MMD_IMPORTMIMICSGROUP_NAME_STATIC   1005
#define IDC_MMD_IMPORTMIMICSGROUP_NAME   1006
#define IDC_MMD_IMPORTMIMICSGROUP_WARNING   1007
#define IDC_MMD_IMPORTMIMICSGROUP_LIST_STATIC   1008
#define IDC_MMD_IMPORTMIMICSGROUP_LIST   1009
#define IDC_MMD_IMPORTMIMICSGROUP_HELP   1010

class CMMDImportMimicsGroupDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMMDImportMimicsGroupDialog)

	// Construction
public:
	CMMDImportMimicsGroupDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CMimicsGroups  m_pMimicsGroups;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDImportMimicsGroupDialog)
	enum { IDD = IDD_MMD_IMPORTMIMICSGROUP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumMimicsGroups();

	INT CalcColumnWidth(CONST CStringArray &szItems);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDImportMimicsGroupDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDImportMimicsGroupDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDExportMimicsGroupDialog dialog

#define IDC_MMD_EXPORTMIMICSGROUP_DETAILS   1001
#define IDC_MMD_EXPORTMIMICSGROUP_LIST_STATIC   1002
#define IDC_MMD_EXPORTMIMICSGROUP_LIST   1003
#define IDC_MMD_EXPORTMIMICSGROUP_FORMAT_STATIC   1004
#define IDC_MMD_EXPORTMIMICSGROUP_FORMAT   1005
#define IDC_MMD_EXPORTMIMICSGROUP_FILENAME_STATIC   1006
#define IDC_MMD_EXPORTMIMICSGROUP_FILENAME   1007
#define IDC_MMD_EXPORTMIMICSGROUP_BROWSE   1008
#define IDC_MMD_EXPORTMIMICSGROUP_HELP   1009

class CMMDExportMimicsGroupDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMMDExportMimicsGroupDialog)

	// Construction
public:
	CMMDExportMimicsGroupDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CMimicsGroups  m_pMimicsGroups;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CMMDExportMimicsGroupDialog)
	enum { IDD = IDD_MMD_EXPORTMIMICSGROUP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumMimicsGroups();
	BOOL EnumExportFormats();

	INT CalcColumnWidth(CONST CStringArray &szItems);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDExportMimicsGroupDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDExportMimicsGroupDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeFormat();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDRotateMimicsObjectDialog dialog

#define IDC_MMD_ROTATEMIMICSOBJECT_DETAILS   1001
#define IDC_MMD_ROTATEMIMICSOBJECT_NAME_STATIC   1002
#define IDC_MMD_ROTATEMIMICSOBJECT_NAME   1003
#define IDC_MMD_ROTATEMIMICSOBJECT_TYPE_STATIC   1004
#define IDC_MMD_ROTATEMIMICSOBJECT_TYPE   1005
#define IDC_MMD_ROTATEMIMICSOBJECT_ANGLE_STATIC   1006
#define IDC_MMD_ROTATEMIMICSOBJECT_ANGLE90   1007
#define IDC_MMD_ROTATEMIMICSOBJECT_ANGLE180   1008
#define IDC_MMD_ROTATEMIMICSOBJECT_ANGLE270   1009
#define IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY   1010
#define IDC_MMD_ROTATEMIMICSOBJCT_ANGLEANY_STATIC   1011
#define IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER   1012
#define IDC_MMD_ROTATEMIMICSOBJECT_HELP   1013

class CMMDRotateMimicsObjectDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDRotateMimicsObjectDialog)

	// Construction
public:
	CMMDRotateMimicsObjectDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMMDRotateMimicsObjectDialog)
	enum { IDD = IDD_MMD_ROTATEMIMICSOBJECT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDRotateMimicsObjectDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDRotateMimicsObjectDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAngle90();
	afx_msg void OnAngle180();
	afx_msg void OnAngle270();
	afx_msg void OnAngleAny();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDTestParameter

class CMMDTestParameter : public CTMParameter
{
	// Construction
public:
	CMMDTestParameter();
	CMMDTestParameter(LPCTSTR pszName);

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDTestProfile

class CMMDTestProfile : public CPtrArray
{
	// Construction
public:
	CMMDTestProfile();
	CMMDTestProfile(LPCTSTR pszName);
	~CMMDTestProfile();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbParameters;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	INT Add(CMMDTestParameter *pParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CMMDTestParameter *GetAt(INT nIndex) CONST;
	CMMDTestParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CMMDTestProfile *pProfile);
	BOOL Compare(CONST CMMDTestProfile *pProfile) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDTestProfiles

class CMMDTestProfiles : public CPtrArray
{
	// Construction
public:
	CMMDTestProfiles();
	~CMMDTestProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CMMDTestProfile *pProfile);

	INT Find(LPCTSTR pszName) CONST;

	CMMDTestProfile *GetAt(INT nIndex) CONST;
	CMMDTestProfile *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CMMDTestProfiles *pProfiles);
	BOOL Compare(CONST CMMDTestProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nData) CONST;
	BOOL Unmap(CONST CByteArray &nData);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDTestDialog dialog

#define IDC_MMD_TEST_DETAILS   1001
#define IDC_MMD_TEST_PARAMETER_STATIC   1002
#define IDC_MMD_TEST_PARAMETER   1003
#define IDC_MMD_TEST_TABLE_STATIC   1004
#define IDC_MMD_TEST_TABLE   1005
#define IDC_MMD_TEST_VALUE_STATIC   1006
#define IDC_MMD_TEST_VALUE   1007
#define IDC_MMD_TEST_SAMPLE_STATIC   1008
#define IDC_MMD_TEST_SAMPLE   1009
#define IDC_MMD_TEST_STATUS_STATIC   1010
#define IDC_MMD_TEST_STATUS_NOLIMIT   1011
#define IDC_MMD_TEST_STATUS_SOFTLIMIT   1012
#define IDC_MMD_TEST_STATUS_HARDLIMIT   1013
#define IDC_MMD_TEST_STATUS_DELTALIMIT   1014
#define IDC_MMD_TEST_STATUS_CONSISTENCYLIMIT   1015
#define IDC_MMD_TEST_QUALITY_STATIC     1016
#define IDC_MMD_TEST_QUALITY_INVALIDDATA   1017
#define IDC_MMD_TEST_QUALITY_BADDATA    1018
#define IDC_MMD_TEST_SETVALUE   1019
#define IDC_MMD_TEST_RUNVALUE   1020
#define IDC_MMD_TEST_STOPVALUE   1021
#define IDC_MMD_TEST_RESETVALUE   1022
#define IDC_MMD_TEST_PROFILES   1023
#define IDC_MMD_TEST_PROFILES_NAME_STATIC   1024
#define IDC_MMD_TEST_PROFILES_NAME   1025
#define IDC_MMD_TEST_PROFILES_ADD   1026
#define IDC_MMD_TEST_PROFILES_REMOVE   1027
#define IDC_MMD_TEST_PROFILES_MEMBERS_STATIC   1028
#define IDC_MMD_TEST_PROFILES_MEMBERS   1029
#define IDC_MMD_TEST_PROFILES_MEMBERS_ADD   1030
#define IDC_MMD_TEST_PROFILES_MEMBERS_REMOVE   1031
#define IDC_MMD_TEST_PROFILES_TEST   1032
#define IDC_MMD_TEST_SCRIPT   1033
#define IDC_MMD_TEST_SCRIPT_CODE_STATIC   1034
#define IDC_MMD_TEST_SCRIPT_CODE   1035
#define IDC_MMD_TEST_SCRIPT_DELAY_STATIC   1036
#define IDC_MMD_TEST_SCRIPT_DELAY   1037
#define IDC_MMD_TEST_SCRIPT_DELAY_MILLISECONDS   1038
#define IDC_MMD_TEST_SCRIPT_ADDPROFILE   1039
#define IDC_MMD_TEST_SCRIPT_ADDPARAMETER   1040
#define IDC_MMD_TEST_SCRIPT_REMOVE   1041
#define IDC_MMD_TEST_SCRIPT_RUN   1042
#define IDC_MMD_TEST_SCRIPT_STOP   1043
#define IDC_MMD_TEST_HELP   1044

// Specify the mimics test dialog related settings
#define MMDTESTDIALOG_MINIMUMSAMPLE   0
#define MMDTESTDIALOG_MAXIMUMSAMPLE   100
#define MMDTESTDIALOG_DEFAULTSAMPLE   0
#define MMDTESTDIALOG_MINIMUMINTERVAL   100
#define MMDTESTDIALOG_MAXIMUMINTERVAL   (1000*SECONDSPERMINUTE)
#define MMDTESTDIALOG_DEFAULTINTERVAL   1000
// Specify the mimics test dialog related timer identifiers
#define MMDTESTDIALOG_TIMERID   100
#define MMDTESTDIALOG_TIMEOUT   0

class CMMDTestDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDTestDialog)

	// Construction
public:
	CMMDTestDialog();   // standard constructor

	// Attributes
private:
	INT  m_nCommand;
	CPtrArray  m_pItems;
	CPtrArray  m_pItemsCode;
	HINSTANCE  m_hImageCode;
	CPtrArray  m_pScriptParameters;
	CStringArray  m_szItemParameters;
	CMMDTestProfiles  m_pProfiles[2];
	CMMDDocument  *m_pDocument;
private:
	CTMEnvironment  m_cTMEnvironment;

	// Dialog Data
	//{{AFX_DATA(CMMDTestDialog)
	enum { IDD = IDD_MMD_TEST_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumParameters();
	BOOL EnumParameterTables();
	BOOL EnumParameterTableValues();
	BOOL EnumParameterProfiles();
	BOOL EnumParameterProfileMembers();

	VOID ShowParameterDetails();

	VOID Test();
	VOID Test(CONST CTMEnvironment *pTMEnvironment);
	VOID Stop();
	VOID Reset();
	VOID Reset(CMimicsItem *pItem);

	BOOL UpdateParameter(CTMParameter *pTMParameter) CONST;
	BOOL UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue) CONST;
	BOOL UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue, INT nSample, BYTE nStatus, LPCTSTR pszTable) CONST;
	BOOL UpdateParameter(CTMParameter *pTMParameter, ULONGLONG nRawValue, INT nSample, BYTE nStatus, LPCTSTR pszTable) CONST;

	BOOL CheckParameterValue() CONST;
	BOOL CheckParameterValue(LPCTSTR pszValue) CONST;
	BOOL CheckParameterValue(CONST CTMParameter *pTMParameter, LPCTSTR pszValue) CONST;

	BOOL LoadCode();
	VOID FreeCode();

	BOOL SaveProfiles();
	BOOL LoadProfiles();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDTestDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDTestDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnParameterStatusNoLimit();
	afx_msg void OnParameterStatusHardLimit();
	afx_msg void OnParameterStatusSoftLimit();
	afx_msg void OnParameterStatusDeltaLimit();
	afx_msg void OnParameterStatusConsistencyLimit();
	afx_msg void OnParameterStatusInvalid();
	afx_msg void OnParameterStatusBadData();
	afx_msg void OnSetParameterValue();
	afx_msg void OnRunParameterValue();
	afx_msg void OnStopParameterValue();
	afx_msg void OnResetParameterValue();
	afx_msg void OnAddProfile();
	afx_msg void OnRemoveProfile();
	afx_msg void OnTestProfile();
	afx_msg void OnAddProfileMember();
	afx_msg void OnRemoveProfileMember();
	afx_msg void OnAddScriptProfile();
	afx_msg void OnAddScriptParameter();
	afx_msg void OnRemoveScriptCommand();
	afx_msg void OnRunScript();
	afx_msg void OnStopScript();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeParameterTable();
	afx_msg void OnSelchangeParameterValue();
	afx_msg void OnSelchangeProfileName();
	afx_msg void OnSelchangeProfileMember();
	afx_msg void OnSelchangeScriptCommand();
	afx_msg void OnSpinchangeParameterSample();
	afx_msg void OnEditchangeParameterValue();
	afx_msg void OnEditchangeProfileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDFindDialog dialog

#define IDC_MMD_FIND_TEXT_STATIC   1001
#define IDC_MMD_FIND_TEXT   1002
#define IDC_MMD_FIND_DIRECTION   1003
#define IDC_MMD_FIND_DIRECTION_UP   1004
#define IDC_MMD_FIND_DIRECTION_DOWN   1005
#define IDC_MMD_FIND_ALL   1006
#define IDC_MMD_FIND_CASE   1007
#define IDC_MMD_FIND_WORD   1008
#define IDC_MMD_FIND_NEXT   1009
#define IDC_MMD_FIND_HELP   1010

class CMMDFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDFindDialog)

	// Construction
public:
	CMMDFindDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szSearchItems;

	// Dialog Data
	//{{AFX_DATA(CMMDFindDialog)
	enum { IDD = IDD_MMD_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CMMDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDFindDialog)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnFindText();
	afx_msg void OnSelchangeText();
	afx_msg void OnEditchangeText();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDReplaceDialog dialog

#define IDC_MMD_REPLACE_FINDTEXT_STATIC   1001
#define IDC_MMD_REPLACE_FINDTEXT   1002
#define IDC_MMD_REPLACE_TEXT_STATIC   1003
#define IDC_MMD_REPLACE_TEXT   1004
#define IDC_MMD_REPLACE_DIRECTION   1005
#define IDC_MMD_REPLACE_DIRECTION_UP   1006
#define IDC_MMD_REPLACE_DIRECTION_DOWN   1007
#define IDC_MMD_REPLACE_ALL   1008
#define IDC_MMD_REPLACE_CASE   1009
#define IDC_MMD_REPLACE_WORD   1010
#define IDC_MMD_REPLACE_FINDNEXT   1011
#define IDC_MMD_REPLACE_NEXT   1012
#define IDC_MMD_REPLACE_ALLNEXT   1013
#define IDC_MMD_REPLACE_HELP   1014

class CMMDReplaceDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDReplaceDialog)

	// Construction
public:
	CMMDReplaceDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szItems[2];

	// Dialog Data
	//{{AFX_DATA(CMMDReplaceDialog)
	enum { IDD = IDD_MMD_REPLACE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CMMDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDReplaceDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDReplaceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnFindNextText();
	afx_msg void OnReplaceText();
	afx_msg void OnReplaceAllText();
	afx_msg void OnSelchangeFindText();
	afx_msg void OnEditchangeFindText();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDGoToDialog dialog

#define IDC_MMD_GOTO_LINE_STATIC   1001
#define IDC_MMD_GOTO_LINE   1002
#define IDC_MMD_GOTO_LINENUMBER   1003
#define IDC_MMD_GOTO_JUMPDOWN   1004
#define IDC_MMD_GOTO_JUMPDOWNLINE   1005
#define IDC_MMD_GOTO_JUMPDOWN_STATIC   1006
#define IDC_MMD_GOTO_JUMPUP   1007
#define IDC_MMD_GOTO_JUMPUPLINE   1008
#define IDC_MMD_GOTO_JUMPUP_STATIC   1009
#define IDC_MMD_GOTO_JUMP   1010
#define IDC_MMD_GOTO_HELP   1011

class CMMDGoToDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDGoToDialog)

	// Construction
public:
	CMMDGoToDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CMMDGoToDialog)
	enum { IDD = IDD_MMD_GOTO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CMMDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDGoToDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDGoToDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLineNumber();
	afx_msg void OnJumpLineDown();
	afx_msg void OnJumpLineUp();
	afx_msg void OnJump();
	afx_msg void OnEditchangeLineNumber();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDStatusBar window

class CMMDStatusBar : public CMFCStatusBar
{
	DECLARE_DYNCREATE(CMMDStatusBar)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pIDs, INT nCount);

	BOOL SetPaneText(UINT nID, LPCTSTR pszText);
	BOOL GetPaneText(UINT nID, CString &szText) CONST;
	CString GetPaneText(UINT nID) CONST;

private:
	INT CalcPaneWidth(INT nIndex) CONST;
	INT CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDStatusBar)
private:
	virtual VOID Initialize();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDStatusBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDImageView view

// Specify the mimics image view ruler settings
#define MMDIMAGEVIEW_RULER_GRIDSINTERVAL   (10*MMDIMAGEVIEW_RULER_TICKSINTERVAL)
#define MMDIMAGEVIEW_RULER_TICKSINTERVAL   10
// Specify the mimics image view drag codes
#define MMDIMAGEVIEW_DRAG_HORIZONTAL   (1<<0)
#define MMDIMAGEVIEW_DRAG_VERTICAL   (1<<1)
#define MMDIMAGEVIEW_DRAG_OUTERMARGIN   (1<<2)
#define MMDIMAGEVIEW_DRAG_INNERMARGIN   (1<<3)
#define MMDIMAGEVIEW_DRAG_LEFT   (1<<4)
#define MMDIMAGEVIEW_DRAG_TOP   (1<<4)
#define MMDIMAGEVIEW_DRAG_RIGHT   (1<<5)
#define MMDIMAGEVIEW_DRAG_BOTTOM   (1<<5)
// Specify the mimics image related timer identifiers
#define MMDIMAGEVIEW_TIMERID   100
#define MMDIMAGEVIEW_TIMEOUT   0

class CMMDImageView : public CScrollView
{
	DECLARE_DYNCREATE(CMMDImageView)

	// Construction
public:
	CMMDImageView();

	// Attributes
private:
	INT  m_nImage[4];
	BOOL  m_bUseGrid;
	CSize  m_sizeGrid;
	CSize  m_sizeImage;
	COLORREF  m_nImageGrid;
	COLORREF  m_nImageBkgnd;
	CMMDDocument  *m_pDocument[2];
	CMMDUndoList  m_cUndoList;
	CMMDLayout  m_cLayout;
	BOOL  m_bModified;
private:
	UINT  m_nItemID;
	UINT  m_nItemDragCode;
	UINT  m_nRulerDragCode;
	UINT  m_nClipboardFormat;
	BOOL  m_bSelectionCode[2];
	POINT  m_ptItemDragPosition;
	POINT  m_ptRulerDragPosition;
	POINT  m_ptItemSelectionPosition;
	CSize  m_sizeItemSelectionArea;
	CRect  m_rItemSelectionArea;
	CRect  m_rItemToggledArea;
	CRect  m_rItemZoomHotSpot;
	CPtrArray  m_pSelectedItems;
	HCURSOR  m_hDefaultCursor;
	HCURSOR  m_hPointCursor;
	HCURSOR  m_hMoveCursor;
	HCURSOR  m_hSelectCursor;
	HCURSOR  m_hWESizeCursor;
	HCURSOR  m_hNSSizeCursor;
	HCURSOR  m_hWENSSizeCursor;
	HCURSOR  m_hSWNESizeCursor;
	HCURSOR  m_hNWSESizeCursor;
	HCURSOR  m_hHorzSizeCursor;
	HCURSOR  m_hVertSizeCursor;
	HCURSOR  m_hRotateCursor;
private:
	IUnknown  *m_pIUnknown;
	IClassFactory  *m_pIClassFactory;
	IEnumMimicsCtrls  *m_pIEnumMimicsCtrls;

	// Operations
public:
	VOID SetImage(LPCTSTR pszTitle);
	BOOL SetImage(CONST CMMDLayout &cLayout);
	VOID SetImage(CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid);
	CString GetImage() CONST;
	BOOL GetImage(CMMDLayout &cLayout) CONST;
	VOID GetImage(SIZE &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, SIZE &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid) CONST;

	VOID SetImageSize(CONST SIZE &size);
	CSize GetImageSize() CONST;
	VOID SetImageMargin(INT nLeft, INT nTop, INT nRight, INT nBottom);
	VOID GetImageMargin(INT &nLeft, INT &nTop, INT &nRight, INT &nBottom) CONST;
	CPoint GetImageOrigin() CONST;

	VOID DrawImage(CONST RECT &rect);

	VOID SetSelectedItemID(UINT nItemID = -1);
	UINT GetSelectedItemID() CONST;

	CMimicsItem *AddItem(UINT nItemID, CONST POINT &point, BOOL bActivate = FALSE);
	CMimicsItem *AddItem(CMimicsItem *pItem, BOOL bActivate = FALSE);
	CMimicsItem *FindItem(LPCTSTR pszName) CONST;
	VOID DeleteItem(CMimicsItem *pItem);

	BOOL SetActivatedItem(CMimicsItem *pItem = NULL);
	CMimicsItem *GetActivatedItem() CONST;
	BOOL HasActivatedItem() CONST;
	BOOL SelectItem(CMimicsItem *pItem = NULL);
	BOOL HasSelectedItems() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoCutItem();
	BOOL CanCutItem() CONST;
	VOID DoCopyItem();
	BOOL CanCopyItem() CONST;
	VOID DoPasteItem();
	BOOL CanPasteItem() CONST;
	VOID DoDeleteItem();
	BOOL CanDeleteItem() CONST;

	VOID DoSelectAllItems();
	VOID UnSelectAllItems();
	BOOL CanSelectAllItems() CONST;

	VOID CollectMimicsGroup();
	BOOL CanCollectMimicsGroup() CONST;
	VOID DiscardMimicsGroup();
	BOOL CanDiscardMimicsGroup() CONST;
	VOID StepIntoMimicsGroup();
	BOOL CanStepIntoMimicsGroup() CONST;
	VOID StepOutMimicsGroup();
	BOOL CanStepOutMimicsGroup() CONST;
	VOID DoHorzAlignItems();
	BOOL CanHorzAlignItems() CONST;
	VOID DoVertAlignItems();
	BOOL CanVertAlignItems() CONST;
	VOID DoMoveItemToTop();
	BOOL CanMoveItemToTop() CONST;
	VOID DoMoveItemToBottom();
	BOOL CanMoveItemToBottom() CONST;
	VOID DoMoveItemUp();
	BOOL CanMoveItemUp() CONST;
	VOID DoMoveItemDown();
	BOOL CanMoveItemDown() CONST;
	VOID DoShowHideItem();
	BOOL CanShowHideItem() CONST;
	VOID DoHorzFlipItem();
	BOOL CanHorzFlipItem() CONST;
	VOID DoVertFlipItem();
	BOOL CanVertFlipItem() CONST;
	VOID DoRotateItem(double fAngle);
	BOOL CanRotateItem() CONST;
	VOID SetItemRotateMode(BOOL bFlag);
	BOOL GetItemRotateMode() CONST;

	HRESULT SetCaptureOnItem(CMimicsItem *pItem);
	HRESULT ReleaseCaptureFromItem(CMimicsItem *pItem);
	CMimicsItem *GetItemWithCapture() CONST;
	HRESULT SetFocusOnItem(CMimicsItem *pItem);
	HRESULT ReleaseFocusFromItem(CMimicsItem *pItem);
	CMimicsItem *GetItemWithFocus() CONST;

	INT EnumItems(CPtrArray &pItems) CONST;
	INT EnumItems(CStringArray &szItems) CONST;

	INT GetItemCount() CONST;

	VOID UpdateAllItems(BOOL bUndo = FALSE);
	BOOL UpdateAllItems(CMimicsItem *pItem);

	VOID SetHotSpot(CONST RECT &rect);
	CRect GetHotSpot() CONST;
	VOID DrawHotSpot(CDC *pDC, CONST SIZE &size);

	BOOL GetPrintProperties(CMetaFileDC &cMetaDC);

	VOID SetModified(BOOL bFlag = TRUE);
	BOOL IsModified() CONST;

	CMMDDocument *GetDocument() CONST;

	class CMMDSplitterWnd *GetParent() CONST;

private:
	BOOL InstallMimicsCtrlInterface();
	VOID DestroyMimicsCtrlInterface();

	VOID DrawImage();
	VOID DrawImage(CDC *pDC);
	VOID DrawImage(CDC *pDC, CONST RECT &rect);
	VOID DrawImage(CDC *pDC, CONST RECT &rect, BOOL bPrinting);
	VOID DrawBackground(CDC *pDC, INT x, INT y, CONST RECT &rect, CONST SIZE &sizeView, CONST SIZE &sizeImage);
	VOID DrawRulers(CDC *pDC, CONST SIZE &sizeView, CONST SIZE &sizeImage, CONST RECT &rHorzRuler, CONST RECT &rVertRuler);
	VOID DrawRulerThumb(CDC *pDC, UINT nResourceID, INT x, INT y);

	CRect CalcHorizontalRulerPosition() CONST;
	CRect CalcHorizontalRulerPosition(CONST RECT &rect) CONST;
	CRect CalcVerticalRulerPosition() CONST;
	CRect CalcVerticalRulerPosition(CONST RECT &rect) CONST;
	BOOL CalcHorizontalRulerOuterThumbPosition(CONST RECT &rect, POINT *pPoints, INT nPoints);
	BOOL CalcHorizontalRulerInnerLeftThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints);
	BOOL CalcHorizontalRulerInnerRightThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints);
	BOOL CalcVerticalRulerOuterThumbPosition(CONST RECT &rect, POINT *pPoints, INT nPoints);
	BOOL CalcVerticalRulerInnerTopThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints);
	BOOL CalcVerticalRulerInnerBottomThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints);
	BOOL IsPointOnRulerThumb(CONST POINT &point, CONST POINT *pPoints) CONST;

	INT EnumOverlappingItems(INT &nPosition) CONST;
	BOOL RepositionOverlappingItems(INT nPosition);
	BOOL RepositionOverlappingItems(CMimicsItem *pItem, CMimicsItem *pPositionItem, BOOL bBefore = TRUE);

	HCURSOR DetermineItemCursor(CMimicsItem *pItem, CPoint point);

	VOID StartDraggingOnRuler(UINT nCode, CONST POINT &point);
	UINT IsDraggingOnRuler() CONST;
	VOID StopDraggingOnRuler();

	BOOL DoItemDragging(CMimicsItem *pItem, CPoint point);
	VOID StartDraggingItem(UINT nCode, CONST POINT &point);
	UINT IsDraggingItem() CONST;
	VOID StopDraggingItem();

	VOID StartSelectingItems(CONST POINT &point);
	BOOL IsSelectingItems() CONST;
	VOID StopSelectingItems();
	BOOL StartDraggingSelectedItems(CONST POINT &point);
	BOOL IsDraggingSelectedItems() CONST;
	VOID StopDraggingSelectedItems();

	BOOL HasSelectedItemsArea() CONST;
	CRect GetSelectedItemsArea() CONST;
	INT GetSelectedItemsAreaCount() CONST;

	VOID UpdateUndoList(BOOL bInitialize = FALSE);

	BOOL CopyToClipboard(CMimicsItem *pItem);
	CMimicsItem *PasteFromClipboard();

	CSize CalcScrollSizes() CONST;

	VOID UpdateZoomWindow();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDImageView)
public:
	virtual HRESULT DefWindowMessageProc(UINT nMessage, WPARAM wParam, LPARAM lParam, LRESULT *plResult);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDImageView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDCodeView view

class CMMDCodeView : public CRichEditView
{
	DECLARE_DYNCREATE(CMMDCodeView)

	// Construction
public:
	CMMDCodeView();

	// Attributes
private:
	CMMDFindDialog  m_dlgFind;
	CMMDGoToDialog  m_dlgGoTo;
	CMMDReplaceDialog  m_dlgReplace;
private:
	CString  m_szCode;
private:
	CFont  m_cCodeFont;
	BOOL  m_bModified;

	// Operations
public:
	BOOL SetCode(CONST CMMDLayout &cLayout);
	BOOL SetCode(CONST CByteArray &nCode);
	BOOL GetCode(CMMDLayout &cLayout) CONST;
	BOOL GetCode(CByteArray &nCode) CONST;
	INT GetCodeSize() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoFindCode();
	BOOL CanFindCode() CONST;
	VOID DoFindNextCode();
	VOID DoFindNextCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNextCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNextCode() CONST;
	VOID DoFindPreviousCode();
	VOID DoFindPreviousCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPreviousCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPreviousCode() CONST;
	VOID DoReplaceCode();
	BOOL CanReplaceCode() CONST;
	VOID DoGoToCode();
	BOOL CanGoToCode() CONST;

	VOID DoCutCode();
	BOOL CanCutCode() CONST;
	VOID DoCopyCode();
	BOOL CanCopyCode() CONST;
	VOID DoPasteCode();
	BOOL CanPasteCode() CONST;
	VOID DoDeleteCode();
	BOOL CanDeleteCode() CONST;

	VOID DoSelectAllCode();
	VOID UnSelectAllCode();
	BOOL CanSelectAllCode() CONST;

	INT FindCode(LPCTSTR pszName) CONST;
	BOOL FindCode(CString &szName) CONST;
	VOID SelectCode(LPCTSTR pszName);
	BOOL SearchCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceAllCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL GoToCode(UINT nLine, BOOL bDown = FALSE, BOOL bUp = FALSE);
	BOOL GoToCode(LPCTSTR pszLine);

	VOID ShowDialogs(BOOL bShow);
	BOOL HasDialogs() CONST;

	VOID SetModified(BOOL bFlag = TRUE);
	BOOL IsModified() CONST;

	class CMMDSplitterWnd *GetParent() CONST;

private:
	static DWORD CALLBACK SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	static DWORD CALLBACK GetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDCodeView)
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDCodeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnEditchangeCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSplitterWnd window

class CMMDSplitterWnd : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CMMDSplitterWnd)

	// Construction
public:
	CMMDSplitterWnd();

	// Attributes
private:
	CMMDDocument  *m_pDocument;

	// Operations
public:
	BOOL Create(class CMMDWnd *pParentWnd);

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoFind();
	BOOL CanFind() CONST;
	VOID DoFindNext(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNext() CONST;
	VOID DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPrevious() CONST;
	VOID DoReplace();
	BOOL CanReplace() CONST;
	VOID DoGoTo();
	BOOL CanGoTo() CONST;

	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;

	VOID DoSelectAll();
	VOID UnSelectAll();
	BOOL CanSelectAll() CONST;

	CView *GetActivePane() CONST;

	CMMDImageView *GetImageView() CONST;
	CMMDCodeView *GetCodeView() CONST;

	class CMMDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDSplitterWnd)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CMMDSplitterWnd)
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDCompileThread thread

class CMMDCompileThread : public CThread
{
	DECLARE_DYNAMIC(CMMDCompileThread)

	// Construction
public:
	CMMDCompileThread();

	// Attributes
private:
	LONG  m_bStop;
	LONG  m_bAbort;
	BOOL  m_bBatch;
	BOOL  m_bSyntax;
	UINT  m_nErrors;
	UINT  m_nWarnings;
	CString  m_szName;
	CStringArray  m_szLines;
	CMMDLayout  m_cLayout;
	CEvent  m_bCompilation[2];

	// Operations
public:
	BOOL StartCompiling(CBinaryDatabase *pDatabase, LPCTSTR pszName);
	BOOL StartCompiling(CBinaryDatabase *pDatabase, LPCTSTR pszName, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort);
	BOOL IsCompiling() CONST;
	BOOL StopCompiling();

	VOID SetCompileTarget(LPCTSTR pszName, BOOL bSyntax, BOOL bBatch);
	CString GetCompileTarget() CONST;
	BOOL IsSyntaxCompileTarget() CONST;
	BOOL IsBatchCompileTarget() CONST;

private:
	BOOL OpenCompileTarget(CBinaryDatabase *pDatabase);
	VOID CompileTarget(CBinaryDatabase *pDatabase);
	VOID CloseCompileTarget();

	BOOL TranslateSourceCode(CONST CBinaryDatabase *pDatabase, CONST CStringArray &szNames, LPCTSTR pszData, CString &szData, CStringArray &szGlobalParameters, CStringArray &szLocalParameters, CStringArray &szStaticParameters, CStringArray &szVolatileParameters, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, CStringArray &szPastParameters, CUIntArray &nPastSamples, CStringArray &szTriggerProcedures, CByteArray &bTriggerFlags);
	BOOL TranslateSourceCodeItems(CStringArray &szNames, CStringArray &szTypes) CONST;
	VOID TranslateSourceCodeItems(CMimicsItem *pItem, CStringArray &szNames, CStringArray &szTypes) CONST;

	VOID CalculateSourceCodeLines(LPCTSTR pszData, CUIntArray &nLines) CONST;
	UINT DetermineSourceCodeLine(CONST CUIntArray &nLines, INT nPos) CONST;
	UINT DetermineSourceCodeColumn(CONST CUIntArray &nLines, INT nPos) CONST;

	BOOL ConvertSourceCodeLineToData(LPCTSTR pszText, CByteArray &nData) CONST;

	BOOL CollectParameter(LPCTSTR pszParameter, CStringArray &szParameters) CONST;

	INT FindParameter(CONST CStringArray &szParameters, LPCTSTR pszParameter, BOOL bScope = TRUE) CONST;

	BOOL SetParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, INT nSamples, BOOL bAll) CONST;
	BOOL SetParameterPastSamples(LPCTSTR pszArgument, CStringArray &szPastParameters, CUIntArray &nPastSamples, INT nSamples) CONST;
	INT GetParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CONST CStringArray &szPastProcedures, CONST CStringArray &szPastProcedureParameters, CUIntArray &nPastSamples) CONST;
	INT GetParameterPastSamples(LPCTSTR pszArgument, CONST CStringArray &szPastParameters, CONST CUIntArray &nPastSamples) CONST;
	INT FindParameterPastSamples(LPCTSTR pszProcedureOrArgument, CONST CStringArray &szPastParameters, BOOL bInsert = FALSE) CONST;

	CString GetMimicsDescriptionFileName(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFormat, BOOL bTemporary = FALSE) CONST;
	BOOL SecureMimicsDescriptionFile(LPCTSTR pszFileName) CONST;
	CString GetMimicsDescriptionCompilerFileName() CONST;
	CString GetMimicsDescriptionCompilerFileName(LPCTSTR pszDirectory) CONST;
	CString GetMimicsDescriptionCompileOptions(CONST CBinaryDatabase *pDatabase) CONST;
	CString GetMimicsDescriptionLinkerFileName() CONST;
	CString GetMimicsDescriptionLinkOptions(CONST CBinaryDatabase *pDatabase) CONST;

	LPCTSTR FindMimicsDescriptionLangaugeSourceCodeKeyword(LPCTSTR pszSourceCode, INT nPos, LPCTSTR pszKeyword) CONST;

	CString FormatMimicsDescriptionCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszError, INT nLine);
	VOID ShowMimicsDescriptionCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors);
	VOID ShowMimicsDescriptionLinkerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors);

	VOID CleanupMimicsDescriptionBuildOutput(CONST CBinaryDatabase *pDatabase);

	VOID ShowStartCompileMessages();
	VOID ShowStopCompileMessages();
	VOID ShowCompileMessage(LPCTSTR pszMessage, BOOL bTimestamp = TRUE, BOOL bAudition = FALSE);

	VOID ShowError(LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);

	VOID SetErrorCount(UINT nCount = 0);
	UINT GetErrorCount() CONST;
	VOID SetWarningCount(UINT nCount = 0);
	UINT GetWarningCount() CONST;

	VOID SetAbortStatus(BOOL bAbort = FALSE);
	BOOL GetAbortStatus() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDCompileThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDCompileThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDWnd frame with splitter

// Specify the mimics display statusbar pane identifiers
#define ID_MMD_STATUSBAR_OBJECTPANE   ID_SEPARATOR
#define ID_MMD_STATUSBAR_POSITIONPANE   ID_STATUSBAR_PANE1
#define ID_MMD_STATUSBAR_SIZEPANE   ID_STATUSBAR_PANE2

class CMMDWnd : public CDisplayWnd
{
	DECLARE_DYNCREATE(CMMDWnd)

	// Construction
public:
	CMMDWnd();
	CMMDWnd(LPCTSTR pszName);

	// Attributes
private:
	CString  m_szName;
	CString  m_szTitle;
private:
	CMMDSplitterWnd  m_wndSplitter;
	CMMDStatusBar  m_wndStatusBar;
private:
	CMMDTestDialog  m_dlgTest;
	CMMDPropertiesDialog  m_dlgProperties;
	CMMDLinkInformationDialog  m_dlgLinkInformation;
public:
	static CMMDCompileThread  m_cCompileThread;

	// Operations
public:
	BOOL Create(CMDIFrameWnd *pParentWnd, UINT nShow = -1);

	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetImage(CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid);
	VOID GetImage(SIZE &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, SIZE &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid) CONST;

	CMimicsItem *AddMimicsCtrl(UINT nCtrlID, CONST POINT &point, BOOL bActivate = FALSE);
	CMimicsItem *AddMimicsCtrl(CMimicsItem *pItem, BOOL bActivate = FALSE);
	CMimicsItem *GetActivatedMimicsCtrl() CONST;
	VOID DeleteMimicsCtrl(CMimicsItem *pItem);
	INT EnumMimicsCtrls(CPtrArray &pItems) CONST;
	INT GetMimicsCtrlCount() CONST;

	VOID SetSelectedMimicsCtrlID(UINT nCtrlID = -1);
	UINT GetSelectedMimicsCtrlID() CONST;

	VOID CollectMimicsGroup();
	BOOL CanCollectMimicsGroup() CONST;
	VOID DiscardMimicsGroup();
	BOOL CanDiscardMimicsGroup() CONST;
	VOID StepIntoMimicsGroup();
	BOOL CanStepIntoMimicsGroup() CONST;
	VOID StepOutMimicsGroup();
	BOOL CanStepOutMimicsGroup() CONST;

	VOID DoHorzAlignMimicsCtrls();
	BOOL CanHorzAlignMimicsCtrls() CONST;
	VOID DoVertAlignMimicsCtrls();
	BOOL CanVertAlignMimicsCtrls() CONST;

	VOID DoMoveMimicsCtrlToTop();
	BOOL CanMoveMimicsCtrlToTop() CONST;
	VOID DoMoveMimicsCtrlToBottom();
	BOOL CanMoveMimicsCtrlToBottom() CONST;
	VOID DoMoveMimicsCtrlUp();
	BOOL CanMoveMimicsCtrlUp() CONST;
	VOID DoMoveMimicsCtrlDown();
	BOOL CanMoveMimicsCtrlDown() CONST;
	VOID DoShowHideMimicsCtrl();
	BOOL CanShowHideMimicsCtrl() CONST;
	VOID DoHorzFlipMimicsCtrl();
	BOOL CanHorzFlipMimicsCtrl() CONST;
	VOID DoVertFlipMimicsCtrl();
	BOOL CanVertFlipMimicsCtrl() CONST;
	VOID DoRotateMimicsCtrl(double fAngle);
	BOOL CanRotateMimicsCtrl() CONST;
	VOID SetMimicsCtrlRotateMode(BOOL bFlag);
	BOOL GetMimicsCtrlRotateMode() CONST;

	VOID ShowMimicsCtrlProperties();
	BOOL HasMimicsCtrlProperties();
	VOID ShowMimicsCtrlItem();
	BOOL HasMimicsCtrlItem() CONST;
	VOID ShowMimicsCtrlCode();
	BOOL HasMimicsCtrlCode() CONST;
	BOOL SearchMimicsCtrlCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceMimicsCtrlCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceAllMimicsCtrlCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL GoToMimicsCtrlCode(UINT nLine, BOOL bDown = FALSE, BOOL bUp = FALSE);
	BOOL GoToMimicsCtrlCode(LPCTSTR pszLine);

	VOID SetHotSpot(CONST RECT &rect);
	CRect GetHotSpot() CONST;
	VOID DrawHotSpot(CDC *pDC, CONST SIZE &size);

	BOOL GetPrintProperties(CMetaFileDC &cMetaDC, UINT nFlags) CONST;

	BOOL UpdateBars();
	BOOL UpdateBars(CMimicsItem *pItem);

	CMMDImageView *GetImageView() CONST;
	CMMDCodeView *GetCodeView() CONST;

private:
	VOID UpdateTitle();
	VOID UpdateMenus();

	INT SaveToDatabase();
	BOOL LoadFromDatabase();
	INT DeleteFromDatabase();

	CMenu *FindMenu(CMenu *pMenu, CMenu &cMenu) CONST;
	BOOL EnumMenu(CMenu &cMenu) CONST;

	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, CMetaFileDC &cMetaDC, WORD wFromPage = -1, WORD wToPage = -1);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage = -1, BOOL bCalc = FALSE);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocInfoTitle() CONST;

public:
	static BOOL StartCompilingMMD(CBinaryDatabase *pDatabase, LPCTSTR pszName);
	static BOOL StartCompilingMMD(CBinaryDatabase *pDatabase, LPCTSTR pszName, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort);
	static BOOL IsCompilingMMD();
	static BOOL IsAbortingMMDCompilation();
	static VOID StopCompilingMMD();

	static INT Delete(LPCTSTR pszName);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDWnd)
public:
	virtual BOOL IsNew() CONST;
	virtual BOOL IsModified() CONST;
	virtual BOOL Save(INT nPosition) CONST;
	virtual INT Load(INT nPosition);
	virtual BOOL UpdateProperties();
	virtual BOOL IsUpdatingProperties() CONST;
	virtual BOOL HasProperties() CONST;
	virtual BOOL UpdateLinkInformation();
	virtual BOOL IsUpdatingLinkInformation() CONST;
	virtual BOOL HasLinkInformation() CONST;
	virtual BOOL Print(PRINTDLG *pPrintInfo, UINT nFlags);
public:
	virtual VOID DoSave();
	virtual BOOL CanSave() CONST;
	virtual VOID DoSaveAs();
	virtual BOOL CanSaveAs() CONST;
	virtual VOID DoDelete();
	virtual BOOL CanDelete() CONST;
	virtual VOID DoUndo();
	virtual BOOL CanUndo() CONST;
	virtual VOID DoRedo();
	virtual BOOL CanRedo() CONST;
	virtual VOID DoFind();
	virtual BOOL CanFind() CONST;
	virtual VOID DoFindNext(BOOL bMatchCase, BOOL bMatchWord);
	virtual VOID DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	virtual BOOL CanFindNext() CONST;
	virtual VOID DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord);
	virtual VOID DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	virtual BOOL CanFindPrevious() CONST;
	virtual VOID DoReplace();
	virtual BOOL CanReplace() CONST;
	virtual VOID DoGoTo();
	virtual BOOL CanGoTo() CONST;
	virtual VOID DoSelectAll();
	virtual BOOL CanSelectAll() CONST;
	virtual VOID DoCutSel();
	virtual BOOL CanCutSel() CONST;
	virtual VOID DoCopySel();
	virtual BOOL CanCopySel() CONST;
	virtual VOID DoPasteSel();
	virtual BOOL CanPasteSel() CONST;
	virtual VOID DoDeleteSel();
	virtual BOOL CanDeleteSel() CONST;
	virtual BOOL CanPrint(UINT nFlags) CONST;
	virtual BOOL DoCompile();
	virtual BOOL IsCompiling() CONST;
	virtual BOOL CanCompile() CONST;
	virtual BOOL StopCompiling();
	virtual VOID DoTest();
	virtual BOOL IsTesting() CONST;
	virtual BOOL CanTest() CONST;
	virtual VOID DoClose();
public:
	virtual VOID AdjustToPrivileges();
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CMMDWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateStatusBarObjectPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarPositionPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarSizePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MMD_H__
