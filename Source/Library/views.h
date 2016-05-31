// VIEWS.H : Views Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the views related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1999/12/13 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __VIEWS_H__
#define __VIEWS_H__

#include "tools.h"
#include "thread.h"
#include "controls.h"


/////////////////////////////////////////////////////////////////////////////
// CTextViewBlinkThread thread

// Specify the display view blink interval
#define DISPLAYVIEW_BLINK_INTERVAL   500

class CTextViewBlinkThread : public CThread
{
	DECLARE_DYNCREATE(CTextViewBlinkThread)

	// Construction
public:
	CTextViewBlinkThread(class CTextView *pView = NULL);

	// Attributes
private:
	ULONGLONG  m_nCount;
private:
	CTextView  *m_pView;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL IsActive() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextViewBlinkThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextViewBlinkThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextViewAttribute

class AFX_EXT_CLASS CTextViewAttribute : public CObject
{
	// Construction
public:
	CTextViewAttribute();
	~CTextViewAttribute();

	// Attributes
private:
	CPtrArray  m_plfFonts;
	CUIntArray  m_nFormats;
	CUIntArray  m_nColors;
	CByteArray  m_blfFonts;
	CByteArray  m_bFormats;
	CByteArray  m_bColors;
	CByteArray  m_bBlink[2];

	// Operations
public:
	VOID SetColumnFormat(INT nColumn, UINT nFormat);
	BOOL GetColumnFormat(INT nColumn, UINT &nFormat) CONST;
	VOID SetColumnColor(INT nColumn, COLORREF nColor);
	BOOL GetColumnColor(INT nColumn, COLORREF &nColor) CONST;
	VOID SetColumnFont(INT nColumn, CONST LOGFONT *plfFont);
	BOOL GetColumnFont(INT nColumn, LOGFONT *plfFont) CONST;
	VOID SetColumnBlinking(INT nColumn, BOOL bBlink);
	BOOL GetColumnBlinking(INT nColumn, BOOL &bBlink) CONST;
	BOOL SetColumnBlinkingState(INT nColumn, BOOL bState);
	BOOL GetColumnBlinkingState(INT nColumn, BOOL &bState) CONST;

	VOID Adjust(INT nColumn, BOOL bInsert = TRUE);

	VOID Reset();

	BOOL Copy(CONST CTextViewAttribute *pAttribute);
	BOOL Compare(CONST CTextViewAttribute *pAttribute) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextViewAttributes

class AFX_EXT_CLASS CTextViewAttributes : public CPtrArray
{
	// Construction
public:
	CTextViewAttributes();
	~CTextViewAttributes();

	// Attributes
public:

	// Operations
public:
	CTextViewAttribute *GetAt(INT nIndex) CONST;
	CTextViewAttribute *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTextViewAttributes *pAttributes);
	BOOL Compare(CONST CTextViewAttributes *pAttributes) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextViewDocument

class CTextViewDocument : public CDocument
{
	DECLARE_DYNAMIC(CTextViewDocument)

	// Construction
public:
	CTextViewDocument();
	virtual ~CTextViewDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextViewHeaderCtrl window

class CTextViewHeaderCtrl : public CMFCHeaderCtrl
{
	DECLARE_DYNCREATE(CTextViewHeaderCtrl)

	// Construction
public:
	CTextViewHeaderCtrl();

	// Attributes
public:
	CStringArray  m_szColumnsText;
	CUIntArray  m_nColumnsWidth;
	CUIntArray  m_nColumnsFormat;
public:
	WORD  m_wTextIndent[2];
	WORD  m_wTextSpacing[2];
public:
	UINT  m_nScrollPos;
public:
	CFont  m_cFont;
public:
	BOOL  m_bUpdate[2];
public:
	class CTextView  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CTextView *pParentWnd, DWORD dwStyle, UINT nID);

	VOID Initialize(CTextView *pParentWnd);

	BOOL SetColumns(CONST CStringArray &szColumns);
	BOOL SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths);
	BOOL SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nFormats);
	BOOL GetColumns(CStringArray &szColumns) CONST;
	BOOL GetColumns(CStringArray &szColumns, CUIntArray &nWidths) CONST;
	BOOL GetColumns(CStringArray &szColumns, CUIntArray &nWidths, CUIntArray &nFormats) CONST;
	BOOL SetColumnsFont(CFont *pFont);
	BOOL SetColumnsFont(CONST LOGFONT *plfFont);
	BOOL GetColumnsFont(CFont *pFont) CONST;
	BOOL GetColumnsFont(LOGFONT *plfFont) CONST;

	BOOL AddColumn(LPCTSTR pszColumn);
	BOOL AddColumn(LPCTSTR pszColumn, INT nWidth, UINT nFormat = HDF_LEFT);
	BOOL InsertColumn(LPCTSTR pszColumn, INT nColumn);
	BOOL InsertColumn(LPCTSTR pszColumn, INT nColumn, INT nWidth, UINT nFormat = HDF_LEFT);
	BOOL DeleteColumn(INT nColumn);
	INT GetColumnCount() CONST;

	BOOL SetTextIndents(WORD wLeft, WORD wRight, BOOL bRedraw = TRUE);
	DWORD GetTextIndents() CONST;
	BOOL SetTextSpacings(WORD wTop, WORD wBottom, BOOL bRedraw = TRUE);
	DWORD GetTextSpacings() CONST;

	class CTextView *GetParent() CONST;

private:
	INT EnumColumnLines(LPCTSTR pszColumn, CStringArray &szLines) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextViewHeaderCtrl)
public:
	virtual VOID RecalcLayout(BOOL bContent = FALSE);
public:
	virtual CSize CalcExtent(CONST CStringArray &szColumns, CUIntArray &nWidths) CONST;
	virtual CSize CalcColumnExtent(LPCTSTR pszColumn) CONST;
	virtual WORD CalcDefaultIndent() CONST;
	virtual WORD CalcDefaultSpacing() CONST;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void OnDrawItem(CDC *pDC, int iItem, CRect rect, BOOL bIsPressed, BOOL bIsHighlighted);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextViewHeaderCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextViewContentCtrl window

class CTextViewContentCtrl : public CScrollView
{
	DECLARE_DYNCREATE(CTextViewContentCtrl)

	// Construction
public:
	CTextViewContentCtrl();

	// Attributes
public:
	CTextViewHeaderCtrl  *m_pHeaderCtrl;
	CTextViewBlinkThread  *m_pBlinkThread;
public:
	CStringArray  m_szContentText;
	CTextViewAttributes  m_pContentTextAttributes;
	CUIntArray  m_nContentTextPos;
	CUIntArray  m_nColumnsFormat;
	CUIntArray  m_nColumnsColor;
	CByteArray  m_bColumnsFormat;
	CByteArray  m_bColumnsColor;
public:
	WORD  m_wTextIndent[2];
	WORD  m_wTextSpacing[2];
	INT  m_nTextLimit;
public:
	INT  m_nActiveItem;
	INT  m_nActiveColumn;
	INT  m_nSortColumn;
public:
	SCROLLINFO  m_sScrollInfo[2];
	UINT  m_nScrollPos[2];
	BOOL  m_bScrollBars;
public:
	CPtrArray  m_pColumnsFont;
	CFont  m_cFont;
public:
	CSize  m_sizeExtent;
	BOOL  m_bBars[2];
	BOOL  m_bFocused;
	BOOL  m_bUpdate;
public:
	class CTextView  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CTextView *pParentWnd, DWORD dwStyle, UINT nID);

	VOID Initialize(CTextView *pParentWnd, CTextViewHeaderCtrl *pHeaderCtrl);

	BOOL SetColumnsFont(CFont *pFont);
	BOOL SetColumnsFont(CONST LOGFONT *plfFont);
	BOOL GetColumnsFont(CFont *pFont) CONST;
	BOOL GetColumnsFont(LOGFONT *plfFont) CONST;

	BOOL SetColumnFont(INT nColumn, CFont *pFont, BOOL bRedraw = TRUE);
	BOOL SetColumnFont(INT nColumn = -1, CONST LOGFONT *plfFont = NULL, BOOL bRedraw = TRUE);
	BOOL SetColumnFont(INT nItem, INT nColumn, CFont *pFont, BOOL bRedraw = TRUE);
	BOOL SetColumnFont(INT nItem, INT nColumn, CONST LOGFONT *plfFont, BOOL bRedraw = TRUE);
	BOOL GetColumnFont(INT nColumn, CFont *pFont) CONST;
	BOOL GetColumnFont(INT nColumn, LOGFONT *plfFont) CONST;
	BOOL GetColumnFont(INT nItem, INT nColumn, CFont *pFont) CONST;
	BOOL GetColumnFont(INT nItem, INT nColumn, LOGFONT *plfFont) CONST;
	BOOL SetColumnFormat(INT nColumn = -1, UINT nFormat = -1, BOOL bRedraw = TRUE);
	BOOL SetColumnFormat(INT nItem, INT nColumn, UINT nFormat, BOOL bRedraw = TRUE);
	UINT GetColumnFormat(INT nColumn) CONST;
	UINT GetColumnFormat(INT nItem, INT nColumn) CONST;
	BOOL SetColumnColor(INT nColumn = -1, COLORREF nColor = -1, BOOL bRedraw = TRUE);
	BOOL SetColumnColor(INT nItem, INT nColumn, COLORREF nColor, BOOL bRedraw = TRUE);
	COLORREF GetColumnColor(INT nColumn) CONST;
	COLORREF GetColumnColor(INT nItem, INT nColumn) CONST;

	BOOL SetContent(CONST CStringArray &szContent, CONST CTextViewAttributes &pAttributes);
	BOOL GetContent(CStringArray &szContent, CTextViewAttributes &pAttributes) CONST;

	INT AddText(LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL, BOOL bRedraw = TRUE);
	BOOL InsertText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL, BOOL bRedraw = TRUE);
	BOOL SetText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL, BOOL bRedraw = TRUE);
	BOOL SetText(INT nItem, INT nColumn, LPCTSTR pszText, BOOL bRedraw = TRUE);
	BOOL GetText(INT nItem, CString &szText, CTextViewAttribute *pAttribute = NULL) CONST;
	BOOL GetText(INT nItem, INT nColumn, CString &szText) CONST;
	CString ConvertText(CONST CStringArray &szColumns) CONST;
	INT ConvertText(LPCTSTR pszText, CStringArray &szColumns) CONST;
	INT FindText(LPCTSTR pszText, INT nColumn = -1, BOOL bExist = TRUE) CONST;
	BOOL FindTextFromPoint(CPoint point, INT &nItem, INT &nColumn, BOOL bExist = TRUE) CONST;
	INT FindTextFromPoint(CPoint point, BOOL bExist = TRUE) CONST;
	INT FindFirstVisibleText() CONST;
	INT FindLastVisibleText() CONST;
	BOOL DeleteText(INT nItem, BOOL bRedraw = TRUE);
	BOOL DeleteAllText(BOOL bRedraw = TRUE);
	INT GetTextCount() CONST;

	BOOL SetCurText(INT nItem, INT nColumn = -1);
	INT GetCurText() CONST;

	INT SearchText(LPCTSTR pszText, INT nColumn = -1) CONST;

	BOOL StartTextBlinking(INT nItem, INT nColumn = -1);
	BOOL StopTextBlinking(INT nItem, INT nColumn = -1);

	BOOL SetTextLimit(INT nLimit = -1, BOOL bRedraw = TRUE);
	INT GetTextLimit() CONST;
	BOOL SetTextIndents(WORD wLeft, WORD wRight, BOOL bRedraw = TRUE);
	DWORD GetTextIndents() CONST;
	BOOL SetTextSpacings(WORD wTop, WORD wBottom, BOOL bRedraw = TRUE);
	DWORD GetTextSpacings() CONST;
	BOOL SetTextSortOrder(UINT nOrder, INT nColumn = -1);
	UINT GetTextSortOrder() CONST;

	BOOL ScrollToTop();
	BOOL ScrollTo(INT nItem);
	BOOL ScrollToBottom();
	VOID SetScrollInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	VOID GetScrollInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;

	class CTextView *GetParent() CONST;

private:
	VOID UpdateScrollBars();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextViewContentCtrl)
public:
	virtual VOID RecalcLayout();
	virtual VOID RecalcContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
public:
	virtual CSize CalcExtent(BOOL bFull = TRUE) CONST;
	virtual INT CalcTextLines(LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL) CONST;
	virtual INT CalcTextLines(CDC *pDC, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL) CONST;
	virtual CRect CalcTextRect(INT nItem, INT nColumn = -1) CONST;
	virtual WORD CalcDefaultIndent() CONST;
	virtual WORD CalcDefaultSpacing() CONST;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	virtual void OnDraw(CDC *pDC);
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:
	static TCHAR GetColumnDelimiter();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextViewContentCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextView window

// Specify the text view styles
#define TVS_HEADER   (1<<0)
#define TVS_TOP   TVS_HEADER
#define TVS_BOTTOM   (TVS_HEADER | (1<<1))
#define TVS_BUTTONS   (TVS_HEADER | (1<<2))
#define TVS_HSCROLL   (1<<3)
#define TVS_VSCROLL   (1<<4)
#define TVS_SORTASCENDING   (1<<5)
#define TVS_SORTDESCENDING   (1<<6)
#define TVS_NOSELECTION   (1<<7)

class AFX_EXT_CLASS CTextView : public CWnd
{
	DECLARE_DYNCREATE(CTextView)

	// Construction
public:
	CTextView();
	~CTextView();

	// Attributes
protected:
	CTextViewHeaderCtrl  m_wndHeaderCtrl;
	CTextViewContentCtrl  m_wndContentCtrl;
	CSize  m_sizeTrack;
protected:
	CCriticalSection  *m_pCriticalSection;
protected:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle = TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, UINT nID = 0);

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetTextFont(CFont *pFont);
	BOOL SetTextFont(CONST LOGFONT *plfFont);
	BOOL GetTextFont(CFont *pFont) CONST;
	BOOL GetTextFont(LOGFONT *plfFont) CONST;

	BOOL SetColumns(CONST CStringArray &szColumns);
	BOOL SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths);
	BOOL SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nFormats);
	BOOL GetColumns(CStringArray &szColumns) CONST;
	BOOL GetColumns(CStringArray &szColumns, CUIntArray &nWidths) CONST;
	BOOL GetColumns(CStringArray &szColumns, CUIntArray &nWidths, CUIntArray &nFormats) CONST;

	BOOL AddColumn(LPCTSTR pszColumn);
	BOOL AddColumn(LPCTSTR pszColumn, INT nWidth, UINT nFormat = HDF_LEFT);
	BOOL InsertColumn(LPCTSTR pszColumn, INT nColumn);
	BOOL InsertColumn(LPCTSTR pszColumn, INT nColumn, INT nWidth, UINT nFormat = HDF_LEFT);
	BOOL SetColumnFormat(INT nColumn = -1, UINT nFormat = -1, BOOL bRedraw = TRUE);
	BOOL SetColumnFormat(INT nItem, INT nColumn, UINT nFormat, BOOL bRedraw = TRUE);
	UINT GetColumnFormat(INT nColumn) CONST;
	UINT GetColumnFormat(INT nItem, INT nColumn) CONST;
	BOOL SetColumnColor(INT nColumn = -1, COLORREF nColor = -1, BOOL bRedraw = TRUE);
	BOOL SetColumnColor(INT nItem, INT nColumn, COLORREF nColor, BOOL bRedraw = TRUE);
	COLORREF GetColumnColor(INT nColumn) CONST;
	COLORREF GetColumnColor(INT nItem, INT nColumn) CONST;
	BOOL SetColumnFont(INT nColumn, CFont *pFont, BOOL bRedraw = TRUE);
	BOOL SetColumnFont(INT nColumn = -1, CONST LOGFONT *plfFont = NULL, BOOL bRedraw = TRUE);
	BOOL SetColumnFont(INT nItem, INT nColumn, CFont *pFont, BOOL bRedraw = TRUE);
	BOOL SetColumnFont(INT nItem, INT nColumn, CONST LOGFONT *plfFont, BOOL bRedraw = TRUE);
	BOOL GetColumnFont(INT nColumn, CFont *pFont) CONST;
	BOOL GetColumnFont(INT nColumn, LOGFONT *plfFont) CONST;
	BOOL GetColumnFont(INT nItem, INT nColumn, CFont *pFont) CONST;
	BOOL GetColumnFont(INT nItem, INT nColumn, LOGFONT *plfFont) CONST;
	BOOL DeleteColumn(INT nColumn);
	INT GetColumnCount() CONST;

	BOOL SetContent(CONST CStringArray &szContent, CONST CTextViewAttributes &pAttributes);
	BOOL GetContent(CStringArray &szContent, CTextViewAttributes &pAttributes) CONST;

	INT AddText(LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL, BOOL bRedraw = TRUE);
	BOOL InsertText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL, BOOL bRedraw = TRUE);
	BOOL SetText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL, BOOL bRedraw = TRUE);
	BOOL SetText(INT nItem, INT nColumn, LPCTSTR pszText, BOOL bRedraw = TRUE);
	BOOL GetText(INT nItem, CString &szText, CTextViewAttribute *pAttribute = NULL) CONST;
	BOOL GetText(INT nItem, INT nColumn, CString &szText) CONST;
	CString ConvertText(CONST CStringArray &szColumns) CONST;
	INT ConvertText(LPCTSTR pszText, CStringArray &szColumns) CONST;
	INT FindText(LPCTSTR pszText, INT nColumn = -1, BOOL bExist = TRUE) CONST;
	BOOL FindTextFromPoint(CPoint point, INT &nItem, INT &nColumn, BOOL bExist = TRUE) CONST;
	INT FindTextFromPoint(CPoint point, BOOL bExist = TRUE) CONST;
	INT FindFirstVisibleText() CONST;
	INT FindLastVisibleText() CONST;
	BOOL DeleteText(INT nItem, BOOL bRedraw = TRUE);
	BOOL DeleteAllText(BOOL bRedraw = TRUE);
	INT GetTextCount() CONST;

	BOOL SetCurText(INT nItem, INT nColumn = -1);
	INT GetCurText() CONST;

	INT SearchText(LPCTSTR pszText, INT nColumn = -1) CONST;

	BOOL StartTextBlinking(INT nItem, INT nColumn = -1);
	BOOL StopTextBlinking(INT nItem, INT nColumn = -1);

	BOOL SetTextLimit(INT nLimit = -1, BOOL bRedraw = TRUE);
	INT GetTextLimit() CONST;
	BOOL SetTextIndents(WORD wLeft, WORD wRight, BOOL bRedraw = TRUE);
	DWORD GetTextIndents() CONST;
	BOOL SetTextSpacings(WORD wTop, WORD wBottom, BOOL bRedraw = TRUE);
	DWORD GetTextSpacings() CONST;
	BOOL SetTextSortOrder(UINT nOrder, INT nColumn = -1);
	UINT GetTextSortOrder() CONST;

	BOOL ScrollToTop();
	BOOL ScrollTo(INT nItem);
	BOOL ScrollToBottom();
	VOID SetScrollInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	VOID GetScrollInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextView)
public:
	virtual VOID RecalcLayout();
	virtual VOID RecalcContent();
	virtual VOID RefreshContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
	virtual BOOL DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rect);
	virtual VOID DrawBlinking(BOOL bState);
public:
	virtual BOOL CalcContentExtent(CSize &size) CONST;
	virtual CSize CalcTrackSize() CONST;
public:
	virtual BOOL OnHeaderMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:
	static TCHAR GetColumnDelimiter();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextViewLock

class AFX_EXT_CLASS CTextViewLock : public CObject
{
	// Construction
public:
	CTextViewLock(CONST CTextView *pView);
	~CTextViewLock();

	// Attributes
private:
	CTextView  *m_pView;

	// Operations
public:
	BOOL Release();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewCell

// Specify the table view cell related types
typedef struct tagTABLEVIEWCELLVALUE {
	union {
		LONGLONG  nValue;
		ULONGLONG  uValue;
		double  fValue;
		TIMETAG  tTime;
		COLORREF  nColor;
	} Value;
	BOOL  bValue;
	tagTABLEVIEWCELLVALUE()
	{
		Value.nValue = 0; Value.uValue = 0; Value.fValue = 0.0; Value.tTime = 0; Value.nColor = 0; bValue = FALSE;
	}
	tagTABLEVIEWCELLVALUE(LONGLONG nValue)
	{
		Value.nValue = nValue; bValue = TRUE;
	}
	tagTABLEVIEWCELLVALUE(ULONGLONG uValue)
	{
		Value.uValue = uValue; bValue = TRUE;
	}
	tagTABLEVIEWCELLVALUE(double fValue)
	{
		Value.fValue = fValue; bValue = TRUE;
	}
	tagTABLEVIEWCELLVALUE(CONST CTimeTag &tTime)
	{
		Value.tTime = tTime.GetTime(); bValue = TRUE;
	}
	tagTABLEVIEWCELLVALUE(COLORREF nColor)
	{
		Value.nColor = nColor; bValue = TRUE;
	}
} TABLEVIEWCELLVALUE, *PTABLEVIEWCELLVALUE, *LPTABLEVIEWCELLVALUE;

class AFX_EXT_CLASS CTableViewCell : public CPoint
{
	// Construction
public:
	CTableViewCell();
	~CTableViewCell();

	// Attributes
private:
	UINT  m_nFormat;
	BOOL  m_bEnabled;
	BOOL  m_bActivated;
	CRect  m_rectPosition[2];
	INT  m_nMinHeight;
private:
	INT  m_nBorderSize[4];
	INT  m_nBorderStyle[4];
	COLORREF  m_nBorderColor[4];
	COLORREF  m_nBackgroundColor;
private:
	INT  m_nTextMode;
	CString  m_szText[2];
	COLORREF  m_nTextColor[2];
private:
	LOGFONT  m_fntProperties;
private:
	CString  m_szSubTable;
private:
	CWnd  *m_pControl;
	UINT  m_nControlID;

	// Operations
public:
	VOID SetFormat(UINT nFormat);
	UINT GetFormat() CONST;
	VOID SetPosition(CONST RECT &rect);
	CRect GetPosition() CONST;
	VOID SetInnerPosition(CONST RECT &rect);
	CRect GetInnerPosition() CONST;
	BOOL HasInnerPosition() CONST;
	VOID SetMinHeight(INT nHeight);
	INT GetMinHeight() CONST;
	VOID SetBorder(UINT nSide, INT nSize, INT nStyle, COLORREF nColor);
	BOOL GetBorder(UINT nSide, INT &nSize, INT &nStyle, COLORREF &nColor) CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;
	VOID SetSubTable(LPCTSTR pszTable);
	CString GetSubTable() CONST;

	BOOL SetText(LPCTSTR pszText, BOOL bVerify = TRUE);
	BOOL TranslateText(LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL UpdateText(LPCTSTR pszInitialText);
	BOOL UpdateText(UINT nAction);
	CString GetText() CONST;
	VOID SetInitialText(LPCTSTR pszText);
	CString GetInitialText() CONST;
	VOID SetTextStyle(INT nMode, COLORREF nColor, COLORREF nBkgndColor);
	VOID GetTextStyle(INT &nMode, COLORREF &nColor, COLORREF &nBkgndColor) CONST;
	BOOL SetValue(CONST TABLEVIEWCELLVALUE &sValue);
	BOOL TranslateValue(CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST;
	BOOL GetValue(TABLEVIEWCELLVALUE &sValue) CONST;

	BOOL SetFont(CONST LOGFONT *plfFont);
	VOID GetFont(LOGFONT *plfFont) CONST;

	BOOL CreateControl();
	VOID SetControlID(UINT nID);
	UINT GetControlID() CONST;
	CWnd *GetControl() CONST;
	BOOL ResizeControl();
	BOOL DestroyControl();

	BOOL Activate(CWnd *pWnd, BOOL bActivate = TRUE);
	BOOL IsActivated() CONST;

	VOID Enable(BOOL bEnabled = TRUE);
	BOOL IsEnabled() CONST;

	VOID Draw(CDC *pDC);

	VOID Copy(CONST CTableViewCell *pCell);
	BOOL Compare(CONST CTableViewCell *pCell) CONST;

private:
	CRect CalcControlPosition(CWnd *pWnd);
	INT CalcControlHeight(CWnd *pWnd, BOOL bBorder = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewCells

class AFX_EXT_CLASS CTableViewCells : public CPtrArray
{
	// Construction
public:
	CTableViewCells();
	~CTableViewCells();

	// Attributes
public:

	// Operations
public:
	INT Add(CTableViewCell *pCell);

	INT Find(INT nRow, INT nCol) CONST;
	INT Find(CONST POINT &point) CONST;

	CTableViewCell *GetAt(INT nIndex) CONST;
	CTableViewCell *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTableViewCells *pCells);
	BOOL Compare(CONST CTableViewCells *pCells) CONST;

private:
	INT FindIndex(INT nRow, INT nCol, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewObject

class AFX_EXT_CLASS CTableViewObject : public CRect
{
	// Construction
public:
	CTableViewObject();
	~CTableViewObject();

	// Attributes
private:
	UINT  m_nType;
	CString  m_szName;
	CString  m_szTitle;
	CTableViewCells  m_pCells;
private:
	INT  m_nFloatingAlignment;
	COLORREF  m_nSelColor;
	CPoint  m_ptSel;
	BOOL  m_bResize;
	BOOL  m_bVisible;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	BOOL HasTitle() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;

	BOOL InsertRow(INT nRow);
	BOOL RemoveRow(INT nRow);
	INT GetRows() CONST;
	BOOL InsertColumn(INT nCol);
	BOOL RemoveColumn(INT nCol);
	INT GetColumns() CONST;
	BOOL SetRowHeight(INT nRow, INT nHeight);
	BOOL SetRowFormat(INT nRow, UINT nFormat);
	BOOL SetRowFont(INT nRow, CONST LOGFONT *plfFont);
	BOOL SetRowBackgroundColor(INT nRow, COLORREF nColor);
	BOOL SetColumnWidth(INT nCol, INT nWidth);
	BOOL SetColumnFormat(INT nCol, UINT nFormat);
	BOOL SetColumnFont(INT nCol, CONST LOGFONT *plfFont);
	BOOL SetColumnBackgroundColor(INT nCol, COLORREF nColor);
	VOID SetOuterBorder(INT nSize, INT nStyle, COLORREF nColor);
	VOID SetInnerBorder(INT nSize, INT nStyle, COLORREF nColor);
	VOID SetInnerMargin(UINT nSide, INT nMargin);

	BOOL SetSelRow(INT nRow = -1);
	INT GetSelRow() CONST;
	BOOL SetSelColumn(INT nCol = -1);
	INT GetSelColumn() CONST;
	BOOL SetSelCell(INT nRow = -1, INT nCol = -1);
	BOOL GetSelCell(INT &nRow, INT &nCol) CONST;
	VOID SetSelColor(COLORREF nColor);
	COLORREF GetSelColor() CONST;

	VOID SetFloatingAlignment(INT nAlignment = -1);
	INT GetFloatingAlignment() CONST;

	BOOL SetCells(CONST CTableViewCells &pCells);
	INT GetCells(CTableViewCells &pCells) CONST;
	INT GetCellCount() CONST;
	VOID OffsetCells(CONST SIZE &size);
	VOID OffsetCells(INT dx, INT dy);
	CRect GetCellsBounds() CONST;

	BOOL SetCellText(INT nRow, INT nCol, LPCTSTR pszText);
	BOOL SetCellText(CONST POINT &point, LPCTSTR pszText);
	BOOL SetCellText(UINT nControlID, LPCTSTR pszText);
	BOOL SetCellText(LPCTSTR pszRow, LPCTSTR pszColumn, LPCTSTR pszText);
	BOOL SetCellText(LPCTSTR pszRow, INT nCol, LPCTSTR pszText);
	BOOL SetCellText(INT nRow, LPCTSTR pszColumn, LPCTSTR pszText);
	BOOL TranslateCellText(INT nRow, INT nCol, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL TranslateCellText(CONST POINT &point, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL TranslateCellText(UINT nControlID, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL TranslateCellText(LPCTSTR pszRow, LPCTSTR pszColumn, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL TranslateCellText(LPCTSTR pszRow, INT nCol, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL TranslateCellText(INT nRow, LPCTSTR pszColumn, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST;
	CString GetCellText(INT nRow, INT nCol) CONST;
	CString GetCellText(CONST POINT &point) CONST;
	CString GetCellText(UINT nControlID) CONST;
	CString GetCellText(LPCTSTR pszRow, LPCTSTR pszColumn) CONST;
	CString GetCellText(LPCTSTR pszRow, INT nCol) CONST;
	CString GetCellText(INT nRow, LPCTSTR pszColumn) CONST;
	BOOL SetCellValue(INT nRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue);
	BOOL SetCellValue(CONST POINT &point, CONST TABLEVIEWCELLVALUE &sValue);
	BOOL SetCellValue(UINT nControlID, CONST TABLEVIEWCELLVALUE &sValue);
	BOOL SetCellValue(LPCTSTR pszRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue);
	BOOL SetCellValue(LPCTSTR pszRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue);
	BOOL SetCellValue(INT nRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue);
	BOOL TranslateCellValue(INT nRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST;
	BOOL TranslateCellValue(CONST POINT &point, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST;
	BOOL TranslateCellValue(UINT nControlID, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST;
	BOOL TranslateCellValue(LPCTSTR pszRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST;
	BOOL TranslateCellValue(LPCTSTR pszRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST;
	BOOL TranslateCellValue(INT nRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST;
	BOOL GetCellValue(INT nRow, INT nCol, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL GetCellValue(CONST POINT &point, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL GetCellValue(UINT nControlID, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL GetCellValue(LPCTSTR pszRow, LPCTSTR pszColumn, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL GetCellValue(LPCTSTR pszRow, INT nCol, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL GetCellValue(INT nRow, LPCTSTR pszColumn, TABLEVIEWCELLVALUE &sValue) CONST;
	BOOL SetCellBorder(INT nCol, INT nRow, UINT nSide, INT nSize, INT nStyle, COLORREF nColor);
	BOOL GetCellBorder(INT nCol, INT nRow, UINT nSide, INT &nSize, INT &nStyle, COLORREF &nColor) CONST;
	CTableViewCell *FindCell(INT nRow, INT nCol) CONST;
	CTableViewCell *FindCell(CONST POINT &point) CONST;
	CTableViewCell *FindCell(CWnd *pControl) CONST;
	CTableViewCell *FindCell(UINT nControlID) CONST;
	CTableViewCell *FindCell(LPCTSTR pszRow, LPCTSTR pszColumn) CONST;
	CTableViewCell *FindCell(LPCTSTR pszRow, INT nCol) CONST;
	CTableViewCell *FindCell(INT nRow, LPCTSTR pszColumn) CONST;
	CTableViewCell *FindCell(INT nIndex) CONST;

	VOID EnableResize(BOOL bEnable = TRUE);
	BOOL IsResizeEnabled() CONST;

	VOID MakeVisible(BOOL bEnable = TRUE);
	BOOL IsVisible() CONST;

	BOOL Copy(CONST CTableViewObject *pTable);
	BOOL Compare(CONST CTableViewObject *pTable) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewObjects

class AFX_EXT_CLASS CTableViewObjects : public CPtrArray
{
	// Construction
public:
	CTableViewObjects();
	~CTableViewObjects();

	// Attributes
public:

	// Operations
public:
	INT Add(CTableViewObject *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CTableViewObject *GetAt(INT nIndex) CONST;
	CTableViewObject *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTableViewObjects *pTables);
	BOOL Compare(CONST CTableViewObjects *pTables) CONST;

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewEditCtrl window

class AFX_EXT_CLASS CTableViewEditCtrl : public CEdit
{
	DECLARE_DYNCREATE(CTableViewEditCtrl)

	// Construction
public:
	CTableViewEditCtrl();

	// Attributes
private:
	INT  m_nLimit;
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID LimitText(INT nCount = 0);

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewEditCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewDPLEditCtrl window

class AFX_EXT_CLASS CTableViewDPLEditCtrl : public CDPLCodeEdit
{
	DECLARE_DYNCREATE(CTableViewDPLEditCtrl)

	// Construction
public:
	CTableViewDPLEditCtrl();

	// Attributes
private:
	INT  m_nLimit;
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID LimitText(INT nCount = 0);

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewDPLEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewDPLEditCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewMDLEditCtrl window

class AFX_EXT_CLASS CTableViewMDLEditCtrl : public CMDLCodeEdit
{
	DECLARE_DYNCREATE(CTableViewMDLEditCtrl)

	// Construction
public:
	CTableViewMDLEditCtrl();

	// Attributes
private:
	INT  m_nLimit;
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID LimitText(INT nCount = 0);

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewMDLEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewMDLEditCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewTPLEditCtrl window

class AFX_EXT_CLASS CTableViewTPLEditCtrl : public CTPLCodeEdit
{
	DECLARE_DYNCREATE(CTableViewTPLEditCtrl)

	// Construction
public:
	CTableViewTPLEditCtrl();

	// Attributes
private:
	INT  m_nLimit;
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID LimitText(INT nCount = 0);

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewTPLEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewTPLEditCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewMultiLineEditCtrl window

class AFX_EXT_CLASS CTableViewMultiLineEditCtrl : public CEdit
{
	DECLARE_DYNCREATE(CTableViewMultiLineEditCtrl)

	// Construction
public:
	CTableViewMultiLineEditCtrl();

	// Attributes
private:
	INT  m_nLimit;
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID LimitText(INT nCount = 0);

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewMultiLineEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewMultiLineEditCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewDecNumberEditCtrl window

class AFX_EXT_CLASS CTableViewDecNumberEditCtrl : public CEdit
{
	DECLARE_DYNCREATE(CTableViewDecNumberEditCtrl)

	// Construction
public:
	CTableViewDecNumberEditCtrl();

	// Attributes
private:
	INT  m_nDigits;
	LONGLONG  m_nRange[2];
	ULONGLONG  m_uRange[2];
	double  m_fRange[2];
	BOOL  m_bRange[3];
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID SetRange(LONGLONG nLow, LONGLONG nHigh, INT nDigits = -1);
	VOID SetRange(ULONGLONG uLow, ULONGLONG uHigh, INT nDigits = -1);
	VOID SetRange(double fLow, double fHigh);
	BOOL GetRange(LONGLONG &nLow, LONGLONG &nHigh) CONST;
	BOOL GetRange(ULONGLONG &uLow, ULONGLONG &uHigh) CONST;
	BOOL GetRange(double &fLow, double &fHigh) CONST;

	double GetNumber() CONST;
	CString GetNumberAsText() CONST;
	BOOL HasNumber() CONST;

	CString TranslateNumber(double fValue) CONST;
	double TranslateNumber(LPCTSTR pszNumber) CONST;

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewDecNumberEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewDecNumberEditCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnGetWindowTextLength(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetWindowText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNumberUpdate();
	afx_msg void OnKillFocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewRawNumberEditCtrl window

class AFX_EXT_CLASS CTableViewRawNumberEditCtrl : public CEdit
{
	DECLARE_DYNCREATE(CTableViewRawNumberEditCtrl)

	// Construction
public:
	CTableViewRawNumberEditCtrl();

	// Attributes
private:
	INT  m_nDigits;
	UINT  m_nRadix;
	BOOL  m_bRange;
	BOOL  m_bPadded;
	ULONGLONG  m_nRange[2];
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID SetRadix(UINT nRadix);
	INT GetRadix() CONST;
	VOID SetRange(ULONGLONG nLow, ULONGLONG nHigh, INT nDigits = -1, BOOL bPadded = FALSE);
	BOOL GetRange(ULONGLONG &nLow, ULONGLONG &nHigh) CONST;

	ULONGLONG GetNumber() CONST;
	CString GetNumberAsText() CONST;
	BOOL HasNumber() CONST;

	CString TranslateNumber(ULONGLONG nValue) CONST;
	ULONGLONG TranslateNumber(LPCTSTR pszNumber) CONST;

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewRawNumberEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewRawNumberEditCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnGetWindowTextLength(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetWindowText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNumberUpdate();
	afx_msg void OnKillFocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxListCtrl window

class AFX_EXT_CLASS CTableViewComboBoxListCtrl : public CComboBox
{
	DECLARE_DYNCREATE(CTableViewComboBoxListCtrl)

	// Construction
public:

	// Attributes
private:
	CStringArray  m_szValues;
	CLongUIntArray  m_nValues;
private:
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	BOOL SetValues(CONST CStringArray &szValues, CONST CLongUIntArray &nValues);
	INT GetValues(CStringArray &szValues) CONST;
	INT GetValues(CLongUIntArray &nValues) CONST;

	ULONGLONG GetValue() CONST;
	CString GetValueAsText() CONST;
	BOOL HasValue(LPCTSTR pszValue) CONST;
	BOOL HasValue(ULONGLONG nValue) CONST;
	BOOL HasValue() CONST;

	CString TranslateValue(ULONGLONG nValue) CONST;
	ULONGLONG TranslateValue(LPCTSTR pszValue) CONST;

	INT SetCurSel(INT nIndex = -1);
	INT GetCurSel() CONST;

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewComboBoxListCtrl)
public:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewComboBoxListCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxEditSubCtrl window

class AFX_EXT_CLASS CTableViewComboBoxEditSubCtrl : public CEdit
{
	DECLARE_DYNCREATE(CTableViewComboBoxEditSubCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTableViewComboBoxEditCtrl *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewComboBoxEditSubCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewComboBoxEditSubCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxEditCtrl window

class AFX_EXT_CLASS CTableViewComboBoxEditCtrl : public CComboBox
{
	DECLARE_DYNCREATE(CTableViewComboBoxEditCtrl)

	// Construction
public:
	CTableViewComboBoxEditCtrl();

	// Attributes
private:
	INT  m_nLimit;
	CStringArray  m_szValues;
	CLongUIntArray  m_nValues;
private:
	CTableViewComboBoxEditSubCtrl  m_cEdit;
	CFont  m_cFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	BOOL SetValues(CONST CStringArray &szValues, CONST CLongUIntArray &nValues);
	INT GetValues(CStringArray &szValues) CONST;
	INT GetValues(CLongUIntArray &nValues) CONST;

	ULONGLONG GetValue() CONST;
	CString GetValueAsText() CONST;
	BOOL HasValue(LPCTSTR pszValue) CONST;
	BOOL HasValue(ULONGLONG nValue) CONST;
	BOOL HasValue() CONST;

	CString TranslateValue(ULONGLONG nValue) CONST;
	ULONGLONG TranslateValue(LPCTSTR pszValue) CONST;

	VOID LimitText(INT nCount = 0);

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	class CTableView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewComboBoxEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewComboBoxEditCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxColorsCtrl window

class AFX_EXT_CLASS CTableViewComboBoxColorsCtrl : public CColorsComboBox
{
	DECLARE_DYNCREATE(CTableViewComboBoxColorsCtrl)

	// Construction
public:

	// Attributes
private:
	CUIntArray  m_nColors;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID SetColors(CONST CUIntArray &nColors);
	INT GetColors(CUIntArray &nColors) CONST;

	COLORREF GetColor() CONST;
	CString GetColorAsText() CONST;

	class CTableView *GetParent() CONST;

public:
	static CString TranslateColor(COLORREF nColor);
	static COLORREF TranslateColor(LPCTSTR pszColor);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewComboBoxColorsCtrl)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewComboBoxColorsCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxLineStylesCtrl window

class AFX_EXT_CLASS CTableViewComboBoxLineStylesCtrl : public CLineStylesComboBox
{
	DECLARE_DYNCREATE(CTableViewComboBoxLineStylesCtrl)

	// Construction
public:

	// Attributes
private:
	CUIntArray  m_nStyles;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID SetLineStyles(CONST CUIntArray &nStyles);
	INT GetLineStyles(CUIntArray &nStyles) CONST;

	INT GetLineStyle() CONST;
	CString GetLineStyleAsText() CONST;

	class CTableView *GetParent() CONST;

public:
	static CString TranslateLineStyle(INT nStyle);
	static INT TranslateLineStyle(LPCTSTR pszStyle);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewComboBoxLineStylesCtrl)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewComboBoxLineStylesCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxLineSymbolsCtrl window

class AFX_EXT_CLASS CTableViewComboBoxLineSymbolsCtrl : public CLineSymbolsComboBox
{
	DECLARE_DYNCREATE(CTableViewComboBoxLineSymbolsCtrl)

	// Construction
public:

	// Attributes
private:
	CUIntArray  m_nSymbols;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	VOID SetLineSymbols(CONST CUIntArray &nSymbols);
	INT GetLineSymbols(CUIntArray &nSymbols) CONST;

	INT GetLineSymbol() CONST;
	CString GetLineSymbolAsText() CONST;

	class CTableView *GetParent() CONST;

public:
	static CString TranslateLineSymbol(INT nSymbol);
	static INT TranslateLineSymbol(LPCTSTR pszSymbol);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewComboBoxLineSymbolsCtrl)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewComboBoxLineSymbolsCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTextLength(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewSpinCtrl window

class AFX_EXT_CLASS CTableViewSpinCtrl : public CSpinBox
{
	DECLARE_DYNCREATE(CTableViewSpinCtrl)

	// Construction
public:
	CTableViewSpinCtrl();
	~CTableViewSpinCtrl();

	// Attributes
private:
	INT  m_nBase;
	INT  m_nDigits;
	INT  m_nAccel;
	LONGLONG  m_nMin;
	LONGLONG  m_nMax;
	UDACCEL  *m_pAccel;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID);

	BOOL SetBase(UINT nBase, UINT nDigits = 0);
	BOOL GetBase(UINT &nBase, UINT &nDigits) CONST;
	BOOL SetRange(LONGLONG nMin, LONGLONG nMax);
	BOOL GetRange(LONGLONG &nMin, LONGLONG &nMax) CONST;
	BOOL SetAccel(INT nAccel, CONST UDACCEL *pAccel);
	UINT GetAccel(INT nAccel, UDACCEL *pAccel) CONST;

	class CTableView *GetParent() CONST;

public:
	static CString TranslateNumber(LONGLONG nNumber);
	static LONGLONG TranslateNumber(LPCTSTR pszNumber);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewSpinCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewSpinCtrl)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetBase(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetBase(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetAccel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetAccel(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated helper functions
__declspec(dllexport) BOOL TableViewSpinCtrl_SetPos(CWnd *pCtrl, LONGLONG nPos);
__declspec(dllexport) LONGLONG TableViewSpinCtrl_GetPos(CWnd *pCtrl);
__declspec(dllexport) BOOL TableViewSpinCtrl_SetBase(CWnd *pCtrl, UINT nBase, UINT nDigits);
__declspec(dllexport) BOOL TableViewSpinCtrl_GetBase(CWnd *pCtrl, UINT &nBase, UINT &nDigits);
__declspec(dllexport) BOOL TableViewSpinCtrl_SetRange(CWnd *pCtrl, LONGLONG nMin, LONGLONG nMax);
__declspec(dllexport) BOOL TableViewSpinCtrl_GetRange(CWnd *pCtrl, LONGLONG &nMin, LONGLONG &nMax);
__declspec(dllexport) BOOL TableViewSpinCtrl_SetAccel(CWnd *pCtrl, INT nAccel, CONST UDACCEL *pAccel);
__declspec(dllexport) UINT TableViewSpinCtrl_GetAccel(CWnd *pCtrl, INT nAccel, UDACCEL *pAccel);
__declspec(dllexport) BOOL TableViewSpinCtrl_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL TableViewSpinCtrl_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos);

// Specify the associated inline definitions
inline BOOL CTableViewSpinCtrl::SetBase(UINT nBase, UINT nDigits)
{
	if (nBase == 2 || nBase == 8 || nBase == 10 || nBase == 16)
	{
		m_nDigits = nDigits;
		m_nBase = nBase;
		return((IsWindow(GetSafeHwnd())) ? TableViewSpinCtrl_SetBase(CTableViewSpinCtrl::FromHandle(GetSafeHwnd()), nBase, nDigits) : TRUE);
	}
	return FALSE;
}
inline BOOL CTableViewSpinCtrl::GetBase(UINT &nBase, UINT &nDigits) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		nBase = m_nBase;
		nDigits = m_nDigits;
		return((nBase == 2 || nBase == 8 || nBase == 10 || nBase == 16) ? TRUE : FALSE);
	}
	return TableViewSpinCtrl_GetBase(CTableViewSpinCtrl::FromHandle(GetSafeHwnd()), nBase, nDigits);
}
inline BOOL CTableViewSpinCtrl::SetRange(LONGLONG nMin, LONGLONG nMax)
{
	if (nMin <= nMax)
	{
		m_nMin = nMin;
		m_nMax = nMax;
		return((IsWindow(GetSafeHwnd())) ? TableViewSpinCtrl_SetRange(CTableViewSpinCtrl::FromHandle(GetSafeHwnd()), nMin, nMax) : TRUE);
	}
	return FALSE;
}
inline BOOL CTableViewSpinCtrl::GetRange(LONGLONG &nMin, LONGLONG &nMax) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		nMin = m_nMin;
		nMax = m_nMax;
		return((nMin <= nMax) ? TRUE : FALSE);
	}
	return TableViewSpinCtrl_GetRange(CTableViewSpinCtrl::FromHandle(GetSafeHwnd()), nMin, nMax);
}
inline BOOL CTableViewSpinCtrl::SetAccel(INT nAccel, CONST UDACCEL *pAccel)
{
	if ((m_pAccel = (!m_pAccel) ? (UDACCEL *)GlobalAlloc(GPTR, nAccel*sizeof(UDACCEL)) : (UDACCEL *)GlobalReAlloc(m_pAccel, nAccel*sizeof(UDACCEL), GMEM_MOVEABLE | GMEM_ZEROINIT)))
	{
		CopyMemory(m_pAccel, pAccel, (m_nAccel = nAccel)*sizeof(UDACCEL));
		return((IsWindow(GetSafeHwnd())) ? TableViewSpinCtrl_SetAccel(CTableViewSpinCtrl::FromHandle(GetSafeHwnd()), nAccel, pAccel) : TRUE);
	}
	return FALSE;
}
inline UINT CTableViewSpinCtrl::GetAccel(INT nAccel, UDACCEL *pAccel) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		CopyMemory(pAccel, m_pAccel, max(min(nAccel, m_nAccel), 0)*sizeof(UDACCEL));
		return max(min(nAccel, m_nAccel), 0);
	}
	return TableViewSpinCtrl_GetAccel(CTableViewSpinCtrl::FromHandle(GetSafeHwnd()), nAccel, pAccel);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewTimeSpinCtrl window

class AFX_EXT_CLASS CTableViewTimeSpinCtrl : public CTimeSpinBox
{
	DECLARE_DYNCREATE(CTableViewTimeSpinCtrl)

	// Construction
public:
	CTableViewTimeSpinCtrl();

	// Attributes
private:
	CString  m_szFormat;
	CTimeTag  m_tInitial;
	CTimeTag  m_tRange[2];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, LPCTSTR pszFormat, DWORD dwStyle, INT nID);

	VOID SetFormat(LPCTSTR pszFormat);
	CString GetFormat() CONST;
	VOID SetInitialTime(CONST CTimeTag &tTime);
	CTimeTag GetInitialTime() CONST;
	BOOL SetRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
	BOOL GetRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST;

	class CTableView *GetParent() CONST;

public:
	static CString TranslateTime(TIMETAG tTime, BOOL bSpan = FALSE);
	static TIMETAG TranslateTime(LPCTSTR pszTime);

	static CString TranslateTimeAndFormat(LPCTSTR pszTime, LPCTSTR pszFormat);
	static CString TranslateTimeAndFormat(LPCTSTR pszTime, LPCTSTR pszInitialTime, LPCTSTR pszFormat);
	static VOID TranslateTimeAndFormat(LPCTSTR pszTimeAndFormat, CString &szTime, CString &szInitialTime, CString &szFormat);

	static BOOL IsValidTime(LPCTSTR pszTime);

private:
	static CString GetSeparator();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableViewTimeSpinCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableViewTimeSpinCtrl)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg LRESULT OnSetTime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTime(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated helper functions
__declspec(dllexport) VOID TableViewTimeSpinCtrl_SetTime(CWnd *pCtrl);
__declspec(dllexport) VOID TableViewTimeSpinCtrl_SetTime(CWnd *pCtrl, CONST CTimeTag &tTime);
__declspec(dllexport) VOID TableViewTimeSpinCtrl_SetTime(CWnd *pCtrl, LPCTSTR pszTime);
__declspec(dllexport) CTimeTag TableViewTimeSpinCtrl_GetTime(CWnd *pCtrl);
__declspec(dllexport) BOOL TableViewTimeSpinCtrl_GetTime(CWnd *pCtrl, CTimeTag &tTime);
__declspec(dllexport) BOOL TableViewTimeSpinCtrl_GetTime(CWnd *pCtrl, CString &szTime);
__declspec(dllexport) BOOL TableViewTimeSpinCtrl_SetRange(CWnd *pCtrl, CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
__declspec(dllexport) BOOL TableViewTimeSpinCtrl_GetRange(CWnd *pCtrl, CTimeTag &tStartTime, CTimeTag &tStopTime);
__declspec(dllexport) BOOL TableViewTimeSpinCtrl_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL TableViewTimeSpinCtrl_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos);

// Specify the associated inline definitions
inline VOID CTableViewTimeSpinCtrl::SetFormat(LPCTSTR pszFormat)
{
	m_szFormat = pszFormat;
}

inline CString CTableViewTimeSpinCtrl::GetFormat() CONST
{
	return m_szFormat;
}

inline VOID CTableViewTimeSpinCtrl::SetInitialTime(CONST CTimeTag &tTime)
{
	m_tInitial = tTime;
}

inline CTimeTag CTableViewTimeSpinCtrl::GetInitialTime() CONST
{
	return m_tInitial;
}

inline BOOL CTableViewTimeSpinCtrl::SetRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	if (tStartTime <= tStopTime)
	{
		m_tRange[0] = tStartTime;
		m_tRange[1] = tStopTime;
		return((IsWindow(GetSafeHwnd())) ? TableViewTimeSpinCtrl_SetRange(CTableViewTimeSpinCtrl::FromHandle(GetSafeHwnd()), tStartTime, tStopTime) : TRUE);
	}
	return FALSE;
}

inline BOOL CTableViewTimeSpinCtrl::GetRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST
{
	if (!IsWindow(GetSafeHwnd()))
	{
		tStartTime = m_tRange[0];
		tStopTime = m_tRange[1];
		return(tStartTime <= tStopTime);
	}
	return TableViewTimeSpinCtrl_GetRange(CTableViewTimeSpinCtrl::FromHandle(GetSafeHwnd()), tStartTime, tStopTime);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableViewDocument

class CTableViewDocument : public CDocument
{
	DECLARE_DYNAMIC(CTableViewDocument)

	// Construction
public:
	CTableViewDocument();
	virtual ~CTableViewDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTableView window

#define TAS_TABLE_NORMAL  0
#define TAS_TABLE_LIST   1
#define TAS_TYPE_TEXT   (1<<0)
#define TAS_TYPE_EDIT   (1<<1)
#define TAS_TYPE_DPLEDIT   (1<<2)
#define TAS_TYPE_MDLEDIT   (1<<3)
#define TAS_TYPE_TPLEDIT   (1<<4)
#define TAS_TYPE_MULTILINEEDIT   (1<<5)
#define TAS_TYPE_DECNUMBEREDIT   (1<<6)
#define TAS_TYPE_RAWNUMBEREDIT   (1<<7)
#define TAS_TYPE_COMBOLISTBOX   (1<<8)
#define TAS_TYPE_COMBOEDITBOX   (1<<9)
#define TAS_TYPE_COMBOCOLORSBOX   (1<<10)
#define TAS_TYPE_COMBOLINESTYLESBOX   (1<<11)
#define TAS_TYPE_COMBOLINESYMBOLSBOX   (1<<12)
#define TAS_TYPE_SPINBOX   (1<<13)
#define TAS_TYPE_TIMESPINBOX   (1<<14)
#define TAS_TYPE_SUBTABLE   (1<<15)
#define TAS_TIME_FUTURE   (1<<16)
#define TAS_TIME_PAST   (1<<17)
#define TAS_TIME_UTC   (1<<18)
#define TAS_TIME_SPAN   (1<<19)
#define TAS_ALIGN_LEFT   (1<<20)
#define TAS_ALIGN_RIGHT   (1<<21)
#define TAS_ALIGN_HCENTER   (1<<22)
#define TAS_ALIGN_TOP   (1<<23)
#define TAS_ALIGN_BOTTOM   (1<<24)
#define TAS_ALIGN_VCENTER   (1<<25)
#define TAS_BORDER_LEFT   (1<<26)
#define TAS_BORDER_TOP   (1<<27)
#define TAS_BORDER_RIGHT   (1<<28)
#define TAS_BORDER_BOTTOM   (1<<29)
#define TAS_ACTION_NORMAL   0
#define TAS_ACTION_UNDO   1
#define TAS_ACTION_REDO   2

class AFX_EXT_CLASS CTableView : public CScrollView
{
	DECLARE_DYNCREATE(CTableView)

	// Construction
public:
	CTableView();
	~CTableView();

	// Attributes
protected:
	CTableViewCell  *m_pCell;
	CTableViewObject  *m_pTable;
	CTableViewObjects  *m_pTables;
protected:
	CPoint  m_nDragCell;
	CPoint  m_ptDragCell[3];
	COLORREF  m_nDragColor;
	CTableViewObject  *m_pDragTable;
protected:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle = WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);

	BOOL AddTable(CTableViewObject *pTable, BOOL bRedraw = TRUE);
	CTableViewObject *FindTable(LPCTSTR pszName) CONST;
	BOOL RemoveTable(LPCTSTR pszName, BOOL bRedraw = TRUE);

	CWnd *GetParent() CONST;

private:
	VOID DrawDragLine();
	VOID DrawDragLine(CONST POINT &point);
	BOOL IsDraggingCells() CONST;
	BOOL IsHorzDraggingCells() CONST;
	BOOL IsVertDraggingCells() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableView)
public:
	virtual	BOOL ActivateTable();
	virtual BOOL ActivateTable(CTableViewObject *pTable, BOOL bPrevious = FALSE);
	virtual CTableViewObject *GetActiveTable() CONST;
	virtual BOOL ActivateNextTable(BOOL bPrevious = FALSE);
	virtual BOOL ActivateNextTableCell(BOOL bPrevious = FALSE);
	virtual BOOL SetActiveCell(LPCTSTR pszInitialText);
	virtual BOOL SetActiveCell(UINT nAction = TAS_ACTION_NORMAL);
	virtual BOOL SetActiveCell(CTableViewObject *pTable, CTableViewCell *pCell, UINT nAction = TAS_ACTION_NORMAL);
	virtual CTableViewCell *GetActiveCell(CTableViewObject *&pTable) CONST;
	virtual CTableViewCell *GetActiveCell() CONST;
public:
	virtual VOID UpdateTablePosition(UINT nFlags, CPoint point);
public:
	virtual VOID ScrollTableRows(CTableViewObject *pTable, BOOL bDown = TRUE);
	virtual VOID ScrollToTableRow(CTableViewObject *pTable, INT nRow);
	virtual VOID ScrollToTableColumn(CTableViewObject *pTable, INT nColumn);
	virtual VOID RecalcScrollSizes();
protected:
	virtual VOID RepositionTables();
	virtual VOID RecalcTables(BOOL bRedraw = TRUE);
	virtual VOID RecalcTable(CTableViewObject *pTable, BOOL bRedraw = TRUE);
	virtual VOID RecalcTableRow(CTableViewObject *pTable, INT nRow, BOOL bAdjust = TRUE);
	virtual VOID RecalcTableColumn(CTableViewObject *pTable, INT nCol, BOOL bAdjust = TRUE);
	virtual CRect CalcTableCellExtent(CONST CTableViewCell *pCell);
	virtual CRect CalcTableCellPosition(CONST CTableViewCell *pCell);
protected:
	virtual VOID DrawTables();
	virtual VOID DrawTables(CDC *pDC);
	virtual VOID DrawTable(CDC *pDC, CTableViewObject *pTable);
protected:
	virtual void OnDraw(CDC *pDC);
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTableView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __VIEWS_H__
