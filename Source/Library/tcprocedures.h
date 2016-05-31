// TCPROCEDURES.H : Telecommand Procedures Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand procedures related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2006/11/11 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TCPROCEDURES_H__
#define __TCPROCEDURES_H__

#ifndef RC_INVOKED
#include "language.h"
#include "ttcprocess.h"
#endif

#include "resource.h"


#ifndef TCP_DLL
// Specify the telecommand procedure document default settings
#define TCPROCEDUREDOCUMENT_DEFAULT_MARGIN   20
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL   40
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE   9
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT   30
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPHORZINDENT   90
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPVERTINDENT   40
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT   150
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT   32
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT   6
#define TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT   4
#define TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH   6

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocument document

class AFX_EXT_CLASS CTCProcedureDocument : public COleDocument
{
	DECLARE_DYNCREATE(CTCProcedureDocument)

	friend class CTCProcedureDocumentItem;

	// Construction
public:
	CTCProcedureDocument();
	virtual ~CTCProcedureDocument();

	// Attributes
public:

	// Operations
public:
	VOID AddStep(CTCProcedureDocumentItem *pStep);
	POSITION InsertStep(CTCProcedureDocumentItem *pStep, POSITION &lPosition, BOOL bBefore = TRUE);
	POSITION FindStep(CONST CTCProcedureDocumentItem *pStep, BOOL bAll = TRUE) CONST;
	BOOL RemoveStep(CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentItem *GetFirstStep() CONST;
	CTCProcedureDocumentItem *GetNextStep(POSITION &lPosition) CONST;
	CTCProcedureDocumentItem *GetNextStep(CONST CTCProcedureDocumentItem *pStep) CONST;
	CTCProcedureDocumentItem *GetPreviousStep(POSITION &lPosition) CONST;
	CTCProcedureDocumentItem *GetPreviousStep(CONST CTCProcedureDocumentItem *pStep) CONST;
	CTCProcedureDocumentItem *GetLastStep() CONST;

	UINT EnumSteps(CPtrArray &pSteps, BOOL bAll = FALSE, BOOL bNamed = FALSE) CONST;

	UINT GetStepCount(BOOL bAll = FALSE) CONST;

	BOOL Copy(CONST CTCProcedureDocument *pDocument, BOOL bState = TRUE);
	BOOL Compare(CONST CTCProcedureDocument *pDocument, BOOL bState = TRUE) CONST;

	BOOL Map(CByteArray &nData) CONST;
	BOOL Map(CDatabaseTCProcedureThreadContents *pContents) CONST;
	BOOL Unmap(CONST CByteArray &nData);
	BOOL Unmap(CONST CDatabaseTCProcedureThreadContents *pContents);

private:
	UINT EnumSteps(CONST CTCProcedureDocument *pDocument, CPtrArray &pSteps, BOOL bAll = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocument)
public:
	virtual POSITION GetStartPosition() CONST;
	virtual POSITION GetStopPosition() CONST;
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
	//{{AFX_MSG(CTCProcedureDocument)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentItem

// Specify the telecommand procedure item color related identifiers
#define TCPROCEDUREDOCUMENTITEM_TRANSPARENTCOLOR   RGB(0,255,0)
#define TCPROCEDUREDOCUMENTITEM_BACKGROUNDCOLOR   RGB(13,87,189)
#define TCPROCEDUREDOCUMENTITEM_BACKGROUNDALPHA   0x32

class AFX_EXT_CLASS CTCProcedureDocumentItem : public COleClientItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentItem)

	friend class CTCProcedureDocument;

	// Construction
public:
	CTCProcedureDocumentItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbLabel;
		INT  cbComments;
		INT  cbPreexecutionExpression;
		INT  cbConfirmationExpression;
		INT  cbConfirmationMessage;
		INT  cbTriggerExpression;
		INT  cbTriggerMessage;
		INT  cbTriggerObject;
		INT  cbFailureLabels;
		INT  cbProperties;
		INT  cbSubSteps;
		UINT  nType;
		UINT  nSubThreadID;
		UINT  nTriggerType;
		UINT  nConfirmationType;
		UINT  nFailureOptions;
		RECT  rPosition;
		BOOL  bActivated;
		BOOL  bExpanded;
		TIMETAG  tTriggerTime;
		TIMEKEY  tTriggerTimeOffset;
		TIMEKEY  tTriggerTimeDelay;
		TIMEKEY  tTriggerTimeout;
		TIMEKEY  tConfirmationTimeout;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szName;
	CString  m_szLabel;
	CString  m_szComments;
	CString  m_szPreexecutionExpression;
	CString  m_szConfirmationExpression;
	CString  m_szConfirmationMessage;
	CString  m_szTriggerExpression;
	CString  m_szTriggerMessage;
	CString  m_szTriggerObject;
	CTimeTag  m_tTriggerTime;
	CTimeSpan  m_tTriggerTimeOffset;
	CTimeSpan  m_tTriggerTimeDelay;
	CTimeSpan  m_tTriggerTimeout;
	CTimeSpan  m_tConfirmationTimeout;
	CStringArray  m_szFailureLabels;
	CByteArray  m_nInfo;
	CSize  m_sizeDesign;
	CRect  m_rPosition;
	UINT  m_nType;
	UINT  m_nState;
	UINT  m_nSubThreadID;
	UINT  m_nTriggerType;
	UINT  m_nConfirmationType;
	UINT  m_nFailureOptions;
	BOOL  m_bActivated;
	BOOL  m_bSelected;
	BOOL  m_bExpanded;
protected:
	CImage  m_cSymbol[3];
	CSize  m_sizeSymbol[3];
protected:
	CFont  m_cLabelFont;
	COLORREF  m_nLabelColor;
protected:
	CTCProcedureDocument  *m_pSubSteps;

	// Operations
public:
	static CTCProcedureDocumentItem *Create(UINT nType, UINT nSubThreadID = 0);

	static CTCProcedureDocumentItem *AllocateFromItem(CONST CTCProcedureDocumentItem *pItem);
	static CTCProcedureDocumentItem *AllocateFromItem(CONST CDatabaseTCProcedureThreadStep *pItem);
	static CTCProcedureDocumentItem *AllocateFromData(CONST CByteArray &nData);

	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetPosition(CONST RECT &rect);
	CRect GetPosition() CONST;
	VOID Relocate(CONST POINT &ptOffset);
	VOID SetDesignSize(CONST SIZE &size);
	CSize GetDesignSize() CONST;
	VOID SetImageSize(CONST SIZE &size);
	CSize GetImageSize() CONST;
	VOID SetSubThreadID(UINT nID);
	UINT GetSubThreadID() CONST;
	VOID SetLabel(LPCTSTR pszLabel);
	CString GetLabel() CONST;
	BOOL SetLabelFont(CONST CFont *pFont);
	BOOL GetLabelFont(CFont *pFont) CONST;
	VOID SetLabelColor(COLORREF nColor);
	COLORREF GetLabelColor() CONST;
	VOID SetTriggerType(UINT nType);
	UINT GetTriggerType() CONST;
	VOID SetTriggerTime(CONST CTimeTag &tTime);
	CTimeTag GetTriggerTime() CONST;
	VOID SetTriggerTimeOffset(CONST CTimeSpan &tDelay);
	CTimeSpan GetTriggerTimeOffset() CONST;
	VOID SetTriggerTimeDelay(CONST CTimeSpan &tDelay);
	CTimeSpan GetTriggerTimeDelay() CONST;
	VOID SetTriggerSynchronizationObject(LPCTSTR pszObject);
	CString GetTriggerSynchronizationObject() CONST;
	VOID SetTriggerTimeout(CONST CTimeSpan &tTimeout);
	CTimeSpan GetTriggerTimeout() CONST;
	VOID SetTriggerMessage(LPCTSTR pszMessage);
	CString GetTriggerMessage() CONST;
	VOID SetTriggerExpression(LPCTSTR pszExpression);
	CString GetTriggerExpression() CONST;
	VOID SetPreexecutionExpression(LPCTSTR pszExpression);
	CString GetPreexecutionExpression() CONST;
	VOID SetConfirmationType(UINT nType);
	UINT GetConfirmationType() CONST;
	VOID SetConfirmationTimeout(CONST CTimeSpan &tTimeout);
	CTimeSpan GetConfirmationTimeout() CONST;
	VOID SetConfirmationMessage(LPCTSTR pszMessage);
	CString GetConfirmationMessage() CONST;
	VOID SetConfirmationExpression(LPCTSTR pszExpression);
	CString GetConfirmationExpression() CONST;
	VOID SetFailureOptions(UINT nOptions);
	UINT GetFailureOptions() CONST;
	VOID SetFailureLabels(CONST CStringArray &szLabels);
	INT GetFailureLabels(CStringArray &szLabels) CONST;

	VOID SetState(UINT nState);
	UINT GetState() CONST;

	BOOL Copy(CONST CTCProcedureDocumentItem *pStep, BOOL bState = TRUE);
	BOOL Compare(CONST CTCProcedureDocumentItem *pStep, BOOL bState = TRUE) CONST;

	BOOL Map(CByteArray &nData) CONST;
	BOOL Map(CDatabaseTCProcedureThreadStep *pItem) CONST;
	BOOL Unmap(CONST CByteArray &nData);
	BOOL Unmap(CONST CDatabaseTCProcedureThreadStep *pItem);

	CTCProcedureDocument *GetSubSteps() CONST;

public:
	static VOID DrawConnectionLine(CDC *pDC, CONST POINT &ptFrom, CONST POINT &ptTo);
	static VOID DrawConnectionLine(CDC *pDC, CONST POINT &pt1, CONST POINT &pt2, CONST POINT &pt3);
	static VOID DrawConnectionLine(CDC *pDC, CONST POINT &ptFrom, CONST POINT &ptTo, CONST RECT &rEdge);

protected:
	VOID DrawLabelSymbol(CDC *pDC, CONST RECT &rect, LPCTSTR pszLabel);
	VOID DrawLabelSymbol(CDC *pDC, CONST RECT &rect, UINT nFlags, LPCTSTR pszLabel);
	VOID DrawSymbol(CDC *pDC, UINT nBitmapID, INT x, INT y, LPCRECT lpClip = NULL);
	VOID DrawSymbol(CDC *pDC, CImage &cSymbol, INT x, INT y, LPCRECT lpClip = NULL);
	BOOL LoadSymbol(UINT nBitmapID, CImage &cSymbol) CONST;
	BOOL LoadSymbol(LPCTSTR pszBitmapName, CImage &cSymbol) CONST;
	CSize CalcSymbolSize(UINT nBitmapID) CONST;
	CSize CalcSymbolSize(LPCTSTR pszBitmapName) CONST;

private:
	VOID Relocate(CTCProcedureDocumentItem *pStep, CONST POINT &ptOffset);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentItem)
public:
	virtual VOID Draw(CDC *pDC, BOOL bFaded = FALSE);
protected:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL Activate(BOOL bActivate = TRUE);
	virtual BOOL IsActivated() CONST;
	virtual BOOL CanSelect() CONST;
	virtual BOOL Select(BOOL bSelect = TRUE);
	virtual BOOL IsSelected() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual BOOL IsExpanded() CONST;
	virtual BOOL IsPtOnImage(CONST POINT &pt) CONST;
	virtual BOOL IsPtOnTreeSymbol(CONST POINT &pt) CONST;
	virtual CPoint CalcConnectionPoint(BOOL bIn = TRUE, BOOL bExpanded = TRUE) CONST;
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentStartItem

class AFX_EXT_CLASS CTCProcedureDocumentStartItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentStartItem)

	// Construction
public:
	CTCProcedureDocumentStartItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentStartItem();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentStartItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanSelect() CONST;
	virtual CPoint CalcConnectionPoint(BOOL bIn = TRUE, BOOL bExpanded = TRUE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentStartItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentBranchItem

class AFX_EXT_CLASS CTCProcedureDocumentBranchItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentBranchItem)

	// Construction
public:
	CTCProcedureDocumentBranchItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentBranchItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbExpression[2];
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szExpression[2];

	// Operations
public:
	VOID SetInvariantCondition(LPCTSTR pszCondition);
	CString GetInvariantCondition() CONST;
	VOID SetTestExpression(LPCTSTR pszExpression);
	CString GetTestExpression() CONST;

private:
	CRect CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartTrueBranch, CPoint &ptEndTrueBranch, CPoint &ptStartFalseBranch, CPoint &ptEndFalseBranch, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentBranchItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentBranchItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSwitchItem

class AFX_EXT_CLASS CTCProcedureDocumentSwitchItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentSwitchItem)

	// Construction
public:
	CTCProcedureDocumentSwitchItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentSwitchItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbExpressions;
		INT  nBranchCount;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nBranchCount;
	CStringArray  m_szExpressions;

	// Operations
public:
	VOID SetBranches(INT nCount);
	INT GetBranches() CONST;
	VOID SetInvariantCondition(LPCTSTR pszCondition);
	CString GetInvariantCondition() CONST;
	VOID SetBranchTestExpression(INT nBranch, LPCTSTR pszExpression);
	CString GetBranchTestExpression(INT nBranch) CONST;

private:
	CRect CalcLayoutPositions(CRect &rSymbol, CUIntArray &nPoints, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentSwitchItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentSwitchItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentForLoopItem

class AFX_EXT_CLASS CTCProcedureDocumentForLoopItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentForLoopItem)

	// Construction
public:
	CTCProcedureDocumentForLoopItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentForLoopItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbExpression;
		INT  nInteractionCount;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nIterationCount;
	CString  m_szExpression;

	// Operations
public:
	VOID SetIterations(INT nCount);
	INT GetIterations() CONST;
	VOID SetInvariantCondition(LPCTSTR pszCondition);
	CString GetInvariantCondition() CONST;

private:
	CRect CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentForLoopItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentForLoopItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWhileLoopItem

class AFX_EXT_CLASS CTCProcedureDocumentWhileLoopItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentWhileLoopItem)

	// Construction
public:
	CTCProcedureDocumentWhileLoopItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentWhileLoopItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbExpression[2];
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szExpression[2];

	// Operations
public:
	VOID SetInvariantCondition(LPCTSTR pszCondition);
	CString GetInvariantCondition() CONST;
	VOID SetTestExpression(LPCTSTR pszExpression);
	CString GetTestExpression() CONST;

private:
	CRect CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentWhileLoopItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentWhileLoopItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentDoLoopItem

class AFX_EXT_CLASS CTCProcedureDocumentDoLoopItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentDoLoopItem)

	// Construction
public:
	CTCProcedureDocumentDoLoopItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentDoLoopItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbExpression[2];
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szExpression[2];

	// Operations
public:
	VOID SetInvariantCondition(LPCTSTR pszCondition);
	CString GetInvariantCondition() CONST;
	VOID SetTestExpression(LPCTSTR pszExpression);
	CString GetTestExpression() CONST;

private:
	CRect CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CPoint &ptStartLoopBranch, CPoint &ptEndLoopBranch, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentDoLoopItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentDoLoopItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentBlockItem

class AFX_EXT_CLASS CTCProcedureDocumentBlockItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentBlockItem)

	// Construction
public:
	CTCProcedureDocumentBlockItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentBlockItem();

	// Attributes
public:

	// Operations
private:
	CRect CalcLayoutPositions(CRect &rStartSymbol, CRect &rEndSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentBlockItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentBlockItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentGotoItem

class AFX_EXT_CLASS CTCProcedureDocumentGotoItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentGotoItem)

	// Construction
public:
	CTCProcedureDocumentGotoItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentGotoItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbJumpLabel;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szJumpLabel;

	// Operations
public:
	VOID SetJumpLabel(LPCTSTR pszLabel);
	CString GetJumpLabel() CONST;

private:
	CRect CalcLayoutPositions(CRect &rSymbol, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentGotoItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentGotoItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentLabelItem

class AFX_EXT_CLASS CTCProcedureDocumentLabelItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentLabelItem)

	// Construction
public:
	CTCProcedureDocumentLabelItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentLabelItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbJumpLabel;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szJumpLabel;

	// Operations
public:
	VOID SetJumpLabel(LPCTSTR pszLabel);
	CString GetJumpLabel() CONST;

private:
	CRect CalcLayoutPositions(CRect &rSymbol, CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentLabelItem)
private:
	virtual VOID DrawContents(CDC *pDC);
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
	virtual BOOL CanExpand() CONST;
	virtual BOOL Expand(BOOL bExpand = TRUE);
	virtual VOID RecalcLayout();
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentLabelItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentEndItem

class AFX_EXT_CLASS CTCProcedureDocumentEndItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentEndItem)

	// Construction
public:
	CTCProcedureDocumentEndItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentEndItem();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentEndItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual CPoint CalcConnectionPoint(BOOL bIn = TRUE, BOOL bExpanded = TRUE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentEndItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetArgumentsItem

class AFX_EXT_CLASS CTCProcedureDocumentSetArgumentsItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentSetArgumentsItem)

	// Construction
public:
	CTCProcedureDocumentSetArgumentsItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentSetArgumentsItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbArguments;
		INT  cbExpressions;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CStringArray  m_szArguments;
	CStringArray  m_szExpressions;

	// Operations
public:
	VOID SetArguments(CONST CStringArray &szArguments);
	INT GetArguments(CStringArray &szArguments) CONST;
	VOID SetExpressions(CONST CStringArray &szExpressions);
	INT GetExpressions(CStringArray &szExpressions) CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentSetArgumentsItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentSetArgumentsItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetVariablesItem

class AFX_EXT_CLASS CTCProcedureDocumentSetVariablesItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentSetVariablesItem)

	// Construction
public:
	CTCProcedureDocumentSetVariablesItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentSetVariablesItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbVariables;
		INT  cbExpressions;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CStringArray  m_szVariables;
	CStringArray  m_szExpressions;

	// Operations
public:
	VOID SetVariables(CONST CStringArray &szVariables);
	INT GetVariables(CStringArray &szVariables) CONST;
	VOID SetExpressions(CONST CStringArray &szExpressions);
	INT GetExpressions(CStringArray &szExpressions) CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentSetVariablesItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentSetVariablesItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetParametersItem

class AFX_EXT_CLASS CTCProcedureDocumentSetParametersItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentSetParametersItem)

	// Construction
public:
	CTCProcedureDocumentSetParametersItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentSetParametersItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbParameters;
		INT  cbExpressions;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CStringArray  m_szParameters;
	CStringArray  m_szExpressions;

	// Operations
public:
	VOID SetParameters(CONST CStringArray &szParameters);
	INT GetParameters(CStringArray &szParameters) CONST;
	VOID SetExpressions(CONST CStringArray &szExpressions);
	INT GetExpressions(CStringArray &szExpressions) CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentSetParametersItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentSetParametersItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetSynchronizationObjectItem

class AFX_EXT_CLASS CTCProcedureDocumentSetSynchronizationObjectItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentSetSynchronizationObjectItem)

	// Construction
public:
	CTCProcedureDocumentSetSynchronizationObjectItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentSetSynchronizationObjectItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbObjectName;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szObjectName;

	// Operations
public:
	VOID SetObjectName(LPCTSTR pszName);
	CString GetObjectName() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentSetSynchronizationObjectItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentSetSynchronizationObjectItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentInjectAlertItem

class AFX_EXT_CLASS CTCProcedureDocumentInjectAlertItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentInjectAlertItem)

	// Construction
public:
	CTCProcedureDocumentInjectAlertItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentInjectAlertItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbType;
		INT  cbSubtype;
		INT  cbMessage;
		INT  cbComments;
		INT  cbAudition;
		INT  cbNotification;
		UINT  nType;
		UINT  nCategory;
		BOOL  bBlinking;
		COLORREF  nColor;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nCategory;
	CString  m_szType;
	CString  m_szSubtype;
	CString  m_szMessage;
	CString  m_szComments;
	CString  m_szAudition;
	CString  m_szNotification;
	COLORREF  m_nColor;
	BOOL  m_bBlinking;

	// Operations
public:
	VOID SetCategory(UINT nCategory);
	UINT GetCategory() CONST;
	VOID SetType(LPCTSTR pszType);
	CString GetType() CONST;
	VOID SetSubtype(LPCTSTR pszSubtype);
	CString GetSubtype() CONST;
	VOID SetMessage(LPCTSTR pszMessage);
	CString GetMessage() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;
	VOID SetAudition(LPCTSTR pszProfile);
	CString GetAudition() CONST;
	VOID SetNotification(LPCTSTR pszProfile);
	CString GetNotification() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID DoBlinking(BOOL bEnable = TRUE);
	BOOL IsBlinking() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentInjectAlertItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentInjectAlertItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentCallProcedureItem

class AFX_EXT_CLASS CTCProcedureDocumentCallProcedureItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentCallProcedureItem)

	// Construction
public:
	CTCProcedureDocumentCallProcedureItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentCallProcedureItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbProcedure;
		INT  cbDescription;
		INT  cbCondition;
		INT  cbArguments;
		INT  cbArgumentValues;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szProcedure;
	CString  m_szDescription;
	CString  m_szCondition;
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments;
	CStringArray  m_szArgumentValues;

	// Operations
public:
	VOID SetProcedure(LPCTSTR pszName);
	CString GetProcedure() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetInvariantCondition(LPCTSTR pszCondition);
	CString GetInvariantCondition() CONST;
	VOID SetArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CONST CStringArray &szValues);
	INT GetArguments(CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CStringArray &szValues) CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentCallProcedureItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentCallProcedureItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentStartProcedureItem

class AFX_EXT_CLASS CTCProcedureDocumentStartProcedureItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentStartProcedureItem)

	// Construction
public:
	CTCProcedureDocumentStartProcedureItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentStartProcedureItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbProcedure;
		INT  cbDescription;
		INT  cbCondition;
		INT  cbArguments;
		INT  cbArgumentValues;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szProcedure;
	CString  m_szDescription;
	CString  m_szCondition;
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments;
	CStringArray  m_szArgumentValues;

	// Operations
public:
	VOID SetProcedure(LPCTSTR pszName);
	CString GetProcedure() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetInvariantCondition(LPCTSTR pszCondition);
	CString GetInvariantCondition() CONST;
	VOID SetArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CONST CStringArray &szValues);
	INT GetArguments(CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CStringArray &szValues) CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentStartProcedureItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentStartProcedureItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentControlProcedureItem

class AFX_EXT_CLASS CTCProcedureDocumentControlProcedureItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentControlProcedureItem)

	// Construction
public:
	CTCProcedureDocumentControlProcedureItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentControlProcedureItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbProcedure;
		UINT  nType;
		UINT  nState;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szProcedure;
	UINT  m_nState;

	// Operations
public:
	VOID SetProcedure(LPCTSTR pszName);
	CString GetProcedure() CONST;
	VOID SetActionState(UINT nState);
	UINT GetActionState() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentControlProcedureItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentControlProcedureItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentControlThreadItem

class AFX_EXT_CLASS CTCProcedureDocumentControlThreadItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentControlThreadItem)

	// Construction
public:
	CTCProcedureDocumentControlThreadItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentControlThreadItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbThread;
		UINT  nType;
		UINT  nState;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szThread;
	UINT  m_nState;

	// Operations
public:
	VOID SetThread(LPCTSTR pszName);
	CString GetThread() CONST;
	VOID SetActionState(UINT nState);
	UINT GetActionState() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentControlThreadItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentControlThreadItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWaitTimeIntervalItem

class AFX_EXT_CLASS CTCProcedureDocumentWaitTimeIntervalItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentWaitTimeIntervalItem)

	// Construction
public:
	CTCProcedureDocumentWaitTimeIntervalItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentWaitTimeIntervalItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		UINT  nType;
		DWORD  dwWaitInterval;
		TIMEKEY  tWaitTime;
	} DATA, *PDATA, *LPDATA;
private:
	DWORD  m_dwWaitInterval;
	CTimeKey  m_tWaitTime;

	// Operations
public:
	VOID SetWaitInterval(DWORD dwInterval);
	DWORD GetWaitInterval() CONST;
	VOID SetWaitTime(CONST CTimeKey &tTime);
	CTimeKey GetWaitTime() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentWaitTimeIntervalItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentWaitTimeIntervalItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWaitSynchronizationObjectItem

class AFX_EXT_CLASS CTCProcedureDocumentWaitSynchronizationObjectItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentWaitSynchronizationObjectItem)

	// Construction
public:
	CTCProcedureDocumentWaitSynchronizationObjectItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentWaitSynchronizationObjectItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbObjectName;
		UINT  nType;
		DWORD  dwTimeout;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szObjectName;
	DWORD  m_dwTimeout;

	// Operations
public:
	VOID SetObjectName(LPCTSTR pszName);
	CString GetObjectName() CONST;
	VOID SetTimeout(DWORD dwTimeout);
	DWORD GetTimeout() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentWaitSynchronizationObjectItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentWaitSynchronizationObjectItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSendTCFunctionItem

// Specify the telecommand procedure send-function item related identifiers
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_EXECUTEATTIME   (1<<0)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_EXECUTEATOFFSET   (1<<1)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_RELEASEATTIME   (1<<2)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_RELEASEATOFFSET   (1<<3)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_FIRSTSTEP   (1<<4)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_SECONDSTEP   (1<<5)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREPREEXEVERIFICATION   (1<<6)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREEXEVERIFICATION   (1<<7)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_CRITICAL   (1<<8)
#define TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_AUTHORIZATION   (1<<9)
#define TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_ACCEPTANCE   (1<<10)
#define TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_START   (1<<11)
#define TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_PROGRESS   (1<<12)
#define TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_COMPLETION   (1<<13)

class AFX_EXT_CLASS CTCProcedureDocumentSendTCFunctionItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentSendTCFunctionItem)

	// Construction
public:
	CTCProcedureDocumentSendTCFunctionItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentSendTCFunctionItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbFunction[2];
		INT  cbDescription;
		INT  cbCondition[2];
		INT  cbMemoryPatch;
		UINT  nType;
		UINT  nOptions;
		BOOL  bExeEarlier;
		DWORD  dwReleaseDelta;
		DWORD  dwExecutionDelta;
		TIMETAG  tReleaseTime;
		TIMETAG  tExecutionTime;
		TIMEKEY  tTimeWindow;
	} DATA, *PDATA, *LPDATA;
private:
	CDatabaseTCPacket  m_cPacket;
	CDatabaseTCFunction  m_cFunction;
	CTimeSpan  m_tTimeWindow;
	CTimeTag  m_tReleaseTime;
	CTimeTag  m_tExecutionTime;
	CString  m_szDescription;
	CString  m_szCondition[2];
	CString  m_szMemoryPatch;
	DWORD  m_dwExecutionDelta;
	DWORD  m_dwReleaseDelta;
	BOOL  m_bExeEarlier;
	UINT  m_nOptions;

	// Operations
public:
	BOOL SetFunction(CONST CDatabaseTCFunction *pFunction = NULL, CONST CDatabaseTCPacket *pPacket = NULL);
	BOOL GetFunction(CDatabaseTCFunction *pFunction, CDatabaseTCPacket *pPacket) CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;
	VOID SetPreexecutionVerificationCondition(LPCTSTR pszCondition);
	CString GetPreexecutionVerificationCondition() CONST;
	VOID SetExecutionVerificationCondition(LPCTSTR pszCondition);
	CString GetExecutionVerificationCondition() CONST;
	VOID SetExecutionVerificationTimeWindow(CONST CTimeSpan &tInterval);
	CTimeSpan GetExecutionVerificationTimeWindow() CONST;
	VOID SetReleaseTime(CONST CTimeTag &tTime);
	CTimeTag GetReleaseTime() CONST;
	VOID SetReleaseDeltaTime(DWORD dwDelta);
	DWORD GetReleaseDeltaTime() CONST;
	VOID SetExecutionTime(CONST CTimeTag &tTime);
	CTimeTag GetExecutionTime() CONST;
	VOID SetExecutionDeltaTime(DWORD dwDelta, BOOL bEarlier = FALSE);
	DWORD GetExecutionDeltaTime(BOOL &bEarlier) CONST;
	DWORD GetExecutionDeltaTime() CONST;
	BOOL IsEarlierExecutionDeltaTime() CONST;
	VOID SetMemoryPatch(LPCTSTR pszMemoryPatch);
	CString GetMemoryPatch() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentSendTCFunctionItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentSendTCFunctionItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSendTCSequenceItem

// Specify the telecommand procedure send-sequence item related identifiers
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_EXECUTEATTIME   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_EXECUTEATTIME
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_EXECUTEATOFFSET   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_EXECUTEATOFFSET
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_RELEASEATTIME   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_RELEASEATTIME
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_RELEASEATOFFSET   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_RELEASEATOFFSET
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_FIRSTSTEP   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_FIRSTSTEP
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_SECONDSTEP   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_SECONDSTEP
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_IGNOREPREEXEVERIFICATION   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREPREEXEVERIFICATION
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_IGNOREEXEVERIFICATION   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_IGNOREEXEVERIFICATION
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_BLOCKED   (TCPROCEDURESENDTCSEQUENCEITEM_ACKFLAG_COMPLETION << 1)
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_GROUPED   (TCPROCEDURESENDTCSEQUENCEITEM_ACKFLAG_COMPLETION << 2)
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_CRITICAL   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_CRITICAL
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_AUTHORIZATION   TCPROCEDURESENDTCFUNCTIONITEM_OPTIONS_AUTHORIZATION
#define TCPROCEDURESENDTCSEQUENCEITEM_OPTIONS_PROCEDURE   (TCPROCEDURESENDTCSEQUENCEITEM_ACKFLAG_COMPLETION << 3)
#define TCPROCEDURESENDTCSEQUENCEITEM_ACKFLAG_ACCEPTANCE   TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_ACCEPTANCE
#define TCPROCEDURESENDTCSEQUENCEITEM_ACKFLAG_START   TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_START
#define TCPROCEDURESENDTCSEQUENCEITEM_ACKFLAG_PROGRESS   TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_PROGRESS
#define TCPROCEDURESENDTCSEQUENCEITEM_ACKFLAG_COMPLETION   TCPROCEDURESENDTCFUNCTIONITEM_ACKFLAG_COMPLETION

class AFX_EXT_CLASS CTCProcedureDocumentSendTCSequenceItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentSendTCSequenceItem)

	// Construction
public:
	CTCProcedureDocumentSendTCSequenceItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentSendTCSequenceItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbSequence;
		INT  cbParameters;
		INT  cbEntries;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szSequence;
	CDatabaseTCParameters  m_pParameters;
	CPtrArray  m_pItems;

	// Operations
public:
	VOID SetSequence(LPCTSTR pszSequence);
	CString GetSequence() CONST;
	VOID SetParameters(CONST CDatabaseTCParameters &pParameters);
	INT GetParameters(CDatabaseTCParameters &pParameters) CONST;

	INT Add(CTCProcedureDocumentSendTCFunctionItem *pItem);

	CTCProcedureDocumentSendTCFunctionItem *GetAt(INT nIndex) CONST;
	CTCProcedureDocumentSendTCFunctionItem *operator[](INT nIndex) CONST;

	INT GetSize() CONST;

	VOID RemoveAll();

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentSendTCSequenceItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentSendTCSequenceItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentLogMessageItem

// Specify the telecommand procedure log-message item related identifiers
#define TCPROCEDURELOGMESSAGEITEM_OPTIONS_PLAINTEXT   (1<<0)
#define TCPROCEDURELOGMESSAGEITEM_OPTIONS_UNICODE   (1<<1)
#define TCPROCEDURELOGMESSAGEITEM_OPTIONS_RESET   (1<<2)

class AFX_EXT_CLASS CTCProcedureDocumentLogMessageItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentLogMessageItem)

	// Construction
public:
	CTCProcedureDocumentLogMessageItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentLogMessageItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbMessage;
		INT  cbFileName;
		UINT  nType;
		UINT  nOptions;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szMessage;
	CString  m_szFileName;
	UINT  m_nOptions;

	// Operations
public:
	VOID SetMessage(LPCTSTR pszMessage);
	CString GetMessage() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentLogMessageItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentLogMessageItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentUserInteractionItem

// Specify the telecommand procedure user-interaction item related identifiers
#define TCPROCEDUREUSERINTERACTIONITEM_ACTION_ACKNOWLEDGE   1
#define TCPROCEDUREUSERINTERACTIONITEM_ACTION_REQUEST   2
#define TCPROCEDUREUSERINTERACTIONITEM_ACTION_CHOOSE   3

class AFX_EXT_CLASS CTCProcedureDocumentUserInteractionItem : public CTCProcedureDocumentItem
{
	DECLARE_DYNCREATE(CTCProcedureDocumentUserInteractionItem)

	// Construction
public:
	CTCProcedureDocumentUserInteractionItem(CTCProcedureDocument *pContainerDoc = NULL, UINT nSubThreadID = 0);
	~CTCProcedureDocumentUserInteractionItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbMessage;
		INT  cbVariables;
		INT  cbValues;
		UINT  nType;
		UINT  nAction;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nAction;
	CString  m_szMessage;
	CStringArray  m_szVariables;
	CStringArray  m_szValues;

	// Operations
public:
	VOID SetAction(UINT nAction);
	UINT GetAction() CONST;
	VOID SetMessage(LPCTSTR pszMessage);
	CString GetMessage() CONST;
	VOID SetVariables(CONST CStringArray &szVariables);
	INT GetVariables(CStringArray &szVariables) CONST;
	VOID SetVariableValues(LPCTSTR pszVariable, CONST CStringArray &szValues);
	INT GetVariableValues(LPCTSTR pszVariable, CStringArray &szValues) CONST;

private:
	CRect CalcLayoutPositions(CRect &rLabel) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDocumentUserInteractionItem)
private:
	virtual VOID DrawLabels(CDC *pDC);
public:
	virtual BOOL CanActivate() CONST;
public:
	virtual BOOL HasProperties() CONST;
	virtual BOOL MapProperties(CByteArray &nInfo) CONST;
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureDocumentUserInteractionItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // TCP_DLL


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDialog dialog

class CTCProcedureDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedureDialog)

	// Construction
public:

	// Attributes
public:

	// Operations
protected:
	HGLOBAL LoadLocaleDialogTemplate(UINT nDialogID) CONST;
	HGLOBAL LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST;

private:
	static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureDialog)
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationDialog dialog

#define IDC_TCPROCEDURESTEPAUTHORIZATION_DETAILS   1001
#define IDC_TCPROCEDURESTEPAUTHORIZATION_NAME_STATIC   1002
#define IDC_TCPROCEDURESTEPAUTHORIZATION_NAME   1003
#define IDC_TCPROCEDURESTEPAUTHORIZATION_THREAD_STATIC   1004
#define IDC_TCPROCEDURESTEPAUTHORIZATION_THREAD   1005
#define IDC_TCPROCEDURESTEPAUTHORIZATION_STEP_STATIC   1006
#define IDC_TCPROCEDURESTEPAUTHORIZATION_STEP   1007
#define IDC_TCPROCEDURESTEPAUTHORIZATION_TYPE_STATIC   1008
#define IDC_TCPROCEDURESTEPAUTHORIZATION_TYPE   1009
#define IDC_TCPROCEDURESTEPAUTHORIZATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURESTEPAUTHORIZATION_DESCRIPTION   1011
#define IDC_TCPROCEDURESTEPAUTHORIZATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDURESTEPAUTHORIZATION_COMMENTS   1013
#define IDC_TCPROCEDURESTEPAUTHORIZATION_TIME_STATIC   1014
#define IDC_TCPROCEDURESTEPAUTHORIZATION_TIME   1015
#define IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION   1016
#define IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_USERNAME_STATIC   1017
#define IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_USERNAME   1018
#define IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_PASSWORD_STATIC   1019
#define IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_PASSWORD   1020

class CTCProcedureStepAuthorizationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureStepAuthorizationDialog)

	// Construction
public:
	CTCProcedureStepAuthorizationDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CTimeKey  m_tAuthorization;

	// Operations
public:

	// Dialog Data
	//{{AFX_DATA(CTCProcedureStepAuthorizationDialog)
	enum { IDD = IDD_TCPROCEDURE_STEPAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureStepAuthorizationDialog)
public:
	virtual INT DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureStepAuthorizationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersCalibrationPage dialog

#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCProcedureStepAuthorizationParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProcedureStepAuthorizationParametersCalibrationPage)

	// Construction
public:
	CTCProcedureStepAuthorizationParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CStringArray  m_szCalTableIDs;
private:
	CONST CDatabaseEngine  *m_pDatabase;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureStepAuthorizationParametersCalibrationPage)
	enum { IDD = IDD_TCPROCEDURE_STEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedureStepAuthorizationParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	HGLOBAL LoadLocalePropertyPageTemplate(UINT nPropertyPageID) CONST;
	HGLOBAL LoadLocalePropertyPageTemplate(LPCTSTR pszPropertyPageName) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureStepAuthorizationParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProcedureStepAuthorizationParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersFolderTabCtrl window

class CTCProcedureStepAuthorizationParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedureStepAuthorizationParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCProcedureStepAuthorizationParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureStepAuthorizationParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureStepAuthorizationParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersFolder

class CTCProcedureStepAuthorizationParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProcedureStepAuthorizationParametersFolder)

	// Construction
public:
	CTCProcedureStepAuthorizationParametersFolder();

	// Attributes
private:
	CTCProcedureStepAuthorizationParametersFolderTabCtrl  m_wndTabCtrl;
	CTCProcedureStepAuthorizationParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedureStepAuthorizationParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureStepAuthorizationParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureStepAuthorizationParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersDialog dialog

#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM_STATIC   1002
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM   1003
#define IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_FOLDER   1004

class CTCProcedureStepAuthorizationParametersDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureStepAuthorizationParametersDialog)

	// Construction
public:
	CTCProcedureStepAuthorizationParametersDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szParameter;
private:
	CONST CDatabaseEngine  *m_pDatabase;
private:
	CTCProcedureStepAuthorizationParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureStepAuthorizationParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_STEPAUTHORIZATIONPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedureSetParametersAuthorizationDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureStepAuthorizationParametersDialog)
public:
	virtual INT DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszParameter, CString &szValue);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureStepAuthorizationParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeParameter();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetArgumentsAuthorizationDialog dialog

#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DETAILS   1001
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_NAME_STATIC   1002
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_NAME   1003
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_THREAD_STATIC   1004
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_THREAD   1005
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_STEP_STATIC   1006
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_STEP   1007
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TYPE_STATIC   1008
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TYPE   1009
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DESCRIPTION   1011
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_COMMENTS   1013
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TIME_STATIC   1014
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TIME   1015
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS   1016
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST   1017
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_STATIC   1018
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE   1019
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_SET   1020
#define IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ACKNOWLEDGE   1021

class CTCProcedureSetArgumentsAuthorizationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureSetArgumentsAuthorizationDialog)

	// Construction
public:
	CTCProcedureSetArgumentsAuthorizationDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CTimeKey  m_tAuthorization;
	CStringArray  m_szArguments;
	CStringArray  m_szArgumentValues;
	CLongUIntArray  m_nArgumentAttributes;
	CPtrArray  m_pArguments;
private:
	CStringArray  m_szColumns;

	// Operations
private:
	VOID EnumArguments();

	VOID ShowArgumentDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureSetArgumentsAuthorizationDialog)
	enum { IDD = IDD_TCPROCEDURE_SETARGUMENTSAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSetArgumentsAuthorizationDialog)
public:
	virtual INT DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CONST CStringArray &szArguments, CONST CLongUIntArray &nArgumentAttributes, CONST CPtrArray &pArguments);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureSetArgumentsAuthorizationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetValue();
	afx_msg void OnAcknowledge();
	afx_msg void OnEditchangeValue();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetVariablesAuthorizationDialog dialog

#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DETAILS   1001
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_NAME_STATIC   1002
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_NAME   1003
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_THREAD_STATIC   1004
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_THREAD   1005
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_STEP_STATIC   1006
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_STEP   1007
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TYPE_STATIC   1008
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TYPE   1009
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DESCRIPTION   1011
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_COMMENTS   1013
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TIME_STATIC   1014
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TIME   1015
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES   1016
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST   1017
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_STATIC   1018
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE   1019
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_SET   1020
#define IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_ACKNOWLEDGE   1021

class CTCProcedureSetVariablesAuthorizationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureSetVariablesAuthorizationDialog)

	// Construction
public:
	CTCProcedureSetVariablesAuthorizationDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CTimeKey  m_tAuthorization;
	CStringArray  m_szVariables;
	CStringArray  m_szVariableValues;
	CLongUIntArray  m_nVariableAttributes;
	CPtrArray  m_pVariables;
private:
	CStringArray  m_szColumns;

	// Operations
private:
	VOID EnumVariables();

	VOID ShowVariableDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureSetVariablesAuthorizationDialog)
	enum { IDD = IDD_TCPROCEDURE_SETVARIABLESAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSetVariablesAuthorizationDialog)
public:
	virtual INT DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CONST CStringArray &szVariables, CONST CLongUIntArray &nVariableAttributes, CONST CPtrArray &pVariables);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureSetVariablesAuthorizationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetValue();
	afx_msg void OnAcknowledge();
	afx_msg void OnEditchangeValue();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetParametersAuthorizationDialog dialog

#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DETAILS   1001
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_NAME_STATIC   1002
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_NAME   1003
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_THREAD_STATIC   1004
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_THREAD   1005
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_STEP_STATIC   1006
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_STEP   1007
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TYPE_STATIC   1008
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TYPE   1009
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DESCRIPTION   1011
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_COMMENTS   1013
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TIME_STATIC   1014
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TIME   1015
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS   1016
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST   1017
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_STATIC   1018
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE   1019
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE_STATIC   1020
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE   1021
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_SET   1022
#define IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_ACKNOWLEDGE   1023

// Specify the telecommand procedure step authorization dialog related identifiers
#define TCPROCEDURESETPARAMETERSAUTHORIZATION_MINIMUMSAMPLE   0
#define TCPROCEDURESETPARAMETERSAUTHORIZATION_MAXIMUMSAMPLE   100
#define TCPROCEDURESETPARAMETERSAUTHORIZATION_DEFAULTSAMPLE   0

class CTCProcedureSetParametersAuthorizationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureSetParametersAuthorizationDialog)

	// Construction
public:
	CTCProcedureSetParametersAuthorizationDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CTimeKey  m_tAuthorization;
	CStringArray  m_szParameters;
	CTCParameters  m_pParameterValues[2];
	CLongUIntArray  m_nParameterAttributes;
	CPtrArray  m_pParameters;
private:
	CONST CDatabaseEngine  *m_pDatabase;
	CTCEnvironment  *m_pTCEnvironment;
private:
	CStringArray  m_szColumns;

	// Operations
private:
	VOID EnumParameters();

	VOID ShowParameterDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureSetParametersAuthorizationDialog)
	enum { IDD = IDD_TCPROCEDURE_SETPARAMETERSAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSetParametersAuthorizationDialog)
public:
	virtual INT DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CONST CStringArray &szParameters, CONST CLongUIntArray &nParameterAttributes, CONST CPtrArray &pParameters, CTCEnvironment *pTCEnvironment);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureSetParametersAuthorizationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetValue();
	afx_msg void OnAcknowledge();
	afx_msg void OnEditchangeValue();
	afx_msg void OnSpinchangeSample();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureCallProcedureAuthorizationDialog dialog

#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DETAILS   1001
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_NAME_STATIC   1002
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_NAME   1003
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_THREAD_STATIC   1004
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_THREAD   1005
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_STEP_STATIC   1006
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_STEP   1007
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TYPE_STATIC   1008
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TYPE   1009
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DESCRIPTION   1011
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_COMMENTS   1013
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TIME_STATIC   1014
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TIME   1015
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS   1016
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST   1017
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_STATIC   1018
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE   1019
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET   1020
#define IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ACKNOWLEDGE   1021

class CTCProcedureCallProcedureAuthorizationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureCallProcedureAuthorizationDialog)

	// Construction
public:
	CTCProcedureCallProcedureAuthorizationDialog(CWnd *pParentWnd = NULL);   // standard constructor
	~CTCProcedureCallProcedureAuthorizationDialog();

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CString  m_szProcedure;
	CTimeKey  m_tAuthorization;
	CPtrArray  m_pArgumentStrings;
	CStringArray  m_szArgumentValues;
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments;
	va_list  m_pArgumentList[2];
private:
	CONST CDatabaseEngine  *m_pDatabase;
private:
	CStringArray  m_szColumns;

	// Operations
private:
	VOID EnumArguments();

	VOID ShowArgumentDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureCallProcedureAuthorizationDialog)
	enum { IDD = IDD_TCPROCEDURE_CALLPROCEDUREAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureCallProcedureAuthorizationDialog)
public:
	virtual INT DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, LPCTSTR pszProcedure, va_list pArgumentList);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureCallProcedureAuthorizationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetValue();
	afx_msg void OnAcknowledge();
	afx_msg void OnEditchangeValue();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStartProcedureAuthorizationDialog dialog

#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DETAILS   1001
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_NAME_STATIC   1002
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_NAME   1003
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_THREAD_STATIC   1004
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_THREAD   1005
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_STEP_STATIC   1006
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_STEP   1007
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TYPE_STATIC   1008
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TYPE   1009
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DESCRIPTION   1011
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_COMMENTS   1013
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TIME_STATIC   1014
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TIME   1015
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS   1016
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST   1017
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_STATIC   1018
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE   1019
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET   1020
#define IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ACKNOWLEDGE   1021

class CTCProcedureStartProcedureAuthorizationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureStartProcedureAuthorizationDialog)

	// Construction
public:
	CTCProcedureStartProcedureAuthorizationDialog(CWnd *pParentWnd = NULL);   // standard constructor
	~CTCProcedureStartProcedureAuthorizationDialog();

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CString  m_szProcedure;
	CTimeKey  m_tAuthorization;
	CPtrArray  m_pArgumentStrings;
	CStringArray  m_szArgumentValues;
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments;
	va_list  m_pArgumentList[2];
private:
	CONST CDatabaseEngine  *m_pDatabase;
private:
	CStringArray  m_szColumns;

	// Operations
private:
	VOID EnumArguments();

	VOID ShowArgumentDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureStartProcedureAuthorizationDialog)
	enum { IDD = IDD_TCPROCEDURE_STARTPROCEDUREAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureStartProcedureAuthorizationDialog)
public:
	virtual INT DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, LPCTSTR pszProcedure, va_list pArgumentList);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureStartProcedureAuthorizationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetValue();
	afx_msg void OnAcknowledge();
	afx_msg void OnEditchangeValue();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersCalibrationPage dialog

#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCProcedureSendTCFunctionParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProcedureSendTCFunctionParametersCalibrationPage)

	// Construction
public:
	CTCProcedureSendTCFunctionParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CStringArray  m_szCalTableIDs;
private:
	CONST CDatabaseEngine  *m_pDatabase;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureSendTCFunctionParametersCalibrationPage)
	enum { IDD = IDD_TCPROCEDURE_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pParameter);

	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedureSendTCFunctionParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	HGLOBAL LoadLocalePropertyPageTemplate(UINT nPropertyPageID) CONST;
	HGLOBAL LoadLocalePropertyPageTemplate(LPCTSTR pszPropertyPageName) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSendTCFunctionParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProcedureSendTCFunctionParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersFolderTabCtrl window

class CTCProcedureSendTCFunctionParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedureSendTCFunctionParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCProcedureSendTCFunctionParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSendTCFunctionParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureSendTCFunctionParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersFolder

class CTCProcedureSendTCFunctionParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProcedureSendTCFunctionParametersFolder)

	// Construction
public:
	CTCProcedureSendTCFunctionParametersFolder();

	// Attributes
private:
	CTCProcedureSendTCFunctionParametersFolderTabCtrl  m_wndTabCtrl;
	CTCProcedureSendTCFunctionParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedureSendTCFunctionParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSendTCFunctionParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureSendTCFunctionParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersDialog dialog

#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM_STATIC   1002
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM   1003
#define IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_FOLDER   1004

class CTCProcedureSendTCFunctionParametersDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureSendTCFunctionParametersDialog)

	// Construction
public:
	CTCProcedureSendTCFunctionParametersDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szFunction;
	CString  m_szParameter;
private:
	CONST CDatabaseEngine  *m_pDatabase;
private:
	CTCProcedureSendTCFunctionParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureSendTCFunctionParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_SENDTCFUNCTIONPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedureSendTCFunctionAuthorizationDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSendTCFunctionParametersDialog)
public:
	virtual INT DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszFunction, LPCTSTR pszParameter, CString &szValue);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureSendTCFunctionParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeParameter();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionAuthorizationDialog dialog

#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DETAILS   1001
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_NAME_STATIC   1002
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_NAME   1003
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_THREAD_STATIC   1004
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_THREAD   1005
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_STEP_STATIC   1006
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_STEP   1007
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TYPE_STATIC   1008
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TYPE   1009
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DESCRIPTION   1011
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_COMMENTS   1013
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TIME_STATIC   1014
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TIME   1015
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS   1016
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST   1017
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_REMARK   1018
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_NOEXTRAPOLATION   1019
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_SHOWALL   1020
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_STATIC   1021
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE   1022
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_SET   1023
#define IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_ACKNOWLEDGE   1024

class CTCProcedureSendTCFunctionAuthorizationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureSendTCFunctionAuthorizationDialog)

	// Construction
public:
	CTCProcedureSendTCFunctionAuthorizationDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CTimeKey  m_tAuthorization;
private:
	CONST CDatabaseEngine  *m_pDatabase;
	CONST CTCProcessEngine  *m_pTCProcessEngine;
	CONST CTCEnvironment  *m_pTCEnvironment;
private:
	CDatabaseTCFunction  *m_pTCFunction[2];
	CDatabaseTCPacket  *m_pTCPacket[2];
private:
	CStringArray  m_szColumns;

	// Operations
private:
	VOID EnumParameters();

	BOOL SetTCFunctionParameterRawIntValue(CDatabaseTCFunctionElement *pTCFunctionElement, LONGLONG nValue);
	BOOL SetTCFunctionParameterRawUIntValue(CDatabaseTCFunctionElement *pTCFunctionElement, ULONGLONG nValue);
	BOOL SetTCFunctionParameterRawFloatValue(CDatabaseTCFunctionElement *pTCFunctionElement, double fValue);
	BOOL SetTCFunctionParameterValue(CDatabaseTCFunctionElement *pTCFunctionElement, double fValue, BOOL bExtrapolate = TRUE);
	BOOL SetTCFunctionParameterTimeValue(CDatabaseTCFunctionElement *pTCFunctionElement, LPCTSTR pszTime);
	BOOL SetTCFunctionParameterStringValue(CDatabaseTCFunctionElement *pTCFunctionElement, LPCTSTR pszText);
	BOOL SetTCPacketParameterRawIntValue(CDatabaseTCPacketParameter *pTCPacketParameter, LONGLONG nValue);
	BOOL SetTCPacketParameterRawUIntValue(CDatabaseTCPacketParameter *pTCPacketParameter, ULONGLONG nValue);
	BOOL SetTCPacketParameterRawFloatValue(CDatabaseTCPacketParameter *pTCPacketParameter, double fValue);
	BOOL SetTCPacketParameterRawTimeValue(CDatabaseTCPacketParameter *pTCPacketParameter, LPCTSTR pszTime);

	UINT ConvertTimeStringValue(LPCTSTR pszTime) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureSendTCFunctionAuthorizationDialog)
	enum { IDD = IDD_TCPROCEDURE_SENDTCFUNCTIONAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSendTCFunctionAuthorizationDialog)
public:
	virtual INT DoModal(CONST CDatabaseEngine *pDatabase, CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureSendTCFunctionAuthorizationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnNoExtrapolation();
	afx_msg void OnShowAll();
	afx_msg void OnSetParameterValue();
	afx_msg void OnAcknowledge();
	afx_msg void OnEditchangeParameterValue();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureUserInteractionDialog dialog

#define IDC_TCPROCEDUREUSERINTERACTION_DETAILS   1001
#define IDC_TCPROCEDUREUSERINTERACTION_TYPE_STATIC   1002
#define IDC_TCPROCEDUREUSERINTERACTION_TYPE   1003
#define IDC_TCPROCEDUREUSERINTERACTION_MESSAGE_STATIC   1004
#define IDC_TCPROCEDUREUSERINTERACTION_MESSAGE   1005
#define IDC_TCPROCEDUREUSERINTERACTION_VARIABLES_STATIC   1006
#define IDC_TCPROCEDUREUSERINTERACTION_VARIABLES   1007
#define IDC_TCPROCEDUREUSERINTERACTION_VALUE_STATIC   1008
#define IDC_TCPROCEDUREUSERINTERACTION_VALUE   1009
#define IDC_TCPROCEDUREUSERINTERACTION_VALUE_SET   1010

// Specify the telecommand procedure user-interaction dialog related identifiers
#define TCPROCEDUREUSERINTERACTIONITEM_ACTION_ACKNOWLEDGE   1
#define TCPROCEDUREUSERINTERACTIONITEM_ACTION_REQUEST   2
#define TCPROCEDUREUSERINTERACTIONITEM_ACTION_CHOOSE   3

class CTCProcedureUserInteractionDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureUserInteractionDialog)

	// Construction
public:
	CTCProcedureUserInteractionDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	UINT  m_nType;
	CString  m_szMessage;
	CStringArray  m_szVariables;
	CStringArray  m_szVariableValues;
	CLongUIntArray  m_nVariableAttributes;
	CPtrArray  m_pVariables;
private:
	CStringArray  m_szColumns;

	// Operations
private:
	BOOL EnumVariables();
	BOOL EnumVariableValues();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureUserInteractionDialog)
	enum { IDD = IDD_TCPROCEDURE_USERINTERACTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureUserInteractionDialog)
public:
	virtual INT DoModal(UINT nType, LPCTSTR pszMessage, CONST CStringArray &szVariables, CONST CLongUIntArray &nVariableAttributes, CONST CPtrArray &pVariables, CONST CStringArray &szVariableValues);
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
	//{{AFX_MSG(CTCProcedureUserInteractionDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSetValue();
	afx_msg void OnEditchangeValue();
	afx_msg void OnSelchangeValue();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureUserConfirmationDialog dialog

#define IDC_TCPROCEDUREUSERCONFIRMATION_DETAILS   1001
#define IDC_TCPROCEDUREUSERCONFIRMATION_NAME_STATIC   1002
#define IDC_TCPROCEDUREUSERCONFIRMATION_NAME   1003
#define IDC_TCPROCEDUREUSERCONFIRMATION_THREAD_STATIC   1004
#define IDC_TCPROCEDUREUSERCONFIRMATION_THREAD   1005
#define IDC_TCPROCEDUREUSERCONFIRMATION_STEP_STATIC   1006
#define IDC_TCPROCEDUREUSERCONFIRMATION_STEP   1007
#define IDC_TCPROCEDUREUSERCONFIRMATION_TYPE_STATIC   1008
#define IDC_TCPROCEDUREUSERCONFIRMATION_TYPE   1009
#define IDC_TCPROCEDUREUSERCONFIRMATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDUREUSERCONFIRMATION_DESCRIPTION   1011
#define IDC_TCPROCEDUREUSERCONFIRMATION_COMMENTS_STATIC   1012
#define IDC_TCPROCEDUREUSERCONFIRMATION_COMMENTS   1013
#define IDC_TCPROCEDUREUSERCONFIRMATION_TIME_STATIC   1014
#define IDC_TCPROCEDUREUSERCONFIRMATION_TIME   1015
#define IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION   1016
#define IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_TRIGGER_STATIC   1017
#define IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_COMPLETION_STATIC   1018
#define IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_SUCCESSFUL   1019
#define IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_FAILED   1020
#define IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_TIME   1021

// Specify the telecommand procedure user-confirmation dialog related identifiers
#define TCPROCEDUREUSERCONFIRMATION_TIMEOUT_TIMERID   100
#define TCPROCEDUREUSERCONFIRMATION_TIMEOUT_INTERVAL   1000

class CTCProcedureUserConfirmationDialog : public CTCProcedureDialog
{
	DECLARE_DYNCREATE(CTCProcedureUserConfirmationDialog)

	// Construction
public:
	CTCProcedureUserConfirmationDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szProcess;
	CString  m_szThread;
	CString  m_szStep[4];
	CString  m_szTimeout;
	CTimeKey  m_tStep;
	CTimeSpan  m_tTimeout;
	BOOL  m_bConfirmation;
	BOOL  m_bResult;

	// Operations
public:

	// Dialog Data
	//{{AFX_DATA(CTCProcedureUserConfirmationDialog)
	enum { IDD = IDD_TCPROCEDURE_USERCONFIRMATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureUserConfirmationDialog)
public:
	virtual INT DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tStep, CONST CTimeSpan &tTimeout, BOOL bConfirmation);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureUserConfirmationDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimer(UINT_PTR nEventID);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureThread

class AFX_EXT_CLASS CTCProcedureThread : public CThread
{
	DECLARE_DYNCREATE(CTCProcedureThread)

	friend class CTCProcedureProcess;
	friend class CTCProcedureProcessScheduleThread;
	friend class CTCProcedureProcessVerificationThread;
	friend class CTCProcedureProcessManager;

	// Construction
public:
	CTCProcedureThread();
	CTCProcedureThread(LPCTSTR pszName, CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, HANDLE hTMEvent, HANDLE hTCEvent, HANDLE hUpdate, HANDLE hExit);
	~CTCProcedureThread();

	// Attributes
private:
	CString  m_szName;
private:
	CONST CDatabaseEngine  *m_pDatabase;
	CTCProcessEngine  *m_pTCProcessEngine;
	CTCEnvironment  *m_pTCEnvironment;
private:
	CTMUnit  m_cTMUnit;
	CTMParameters  m_pTMParameters;
	CTimeTag  m_tTMBandwidth;
	double  m_fTMBandwidth[4];
private:
	CDatabaseTCProcedureThreadContents  m_pContents;
	CDatabaseTCProcedureThreadBreakpoints  m_pDatabaseTCProcedureThreadBreakpoints;
private:
	CString  m_szStepName;
	CStringArray  m_szStepNames;
	CUIntArray  m_nStepStates;
private:
	UINT  m_nLine;
	UINT  m_nState;
	BOOL  m_bSynchronized;
	BOOL  m_bEnabled;
	BOOL  m_bAborted;
	CTimeKey  m_tTime;
	HANDLE  m_hState;
	HANDLE  m_hUpdate;
	HANDLE  m_hResume;
	HANDLE  m_hTMEvent;
	HANDLE  m_hTCEvent;
	HANDLE  m_hResult[2];
	HANDLE  m_hExit;
private:
	CCriticalSection  *m_pTMEnvironment;

	// Operations
private:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	BOOL SetContents(CONST CDatabaseTCProcedureThreadContents *pContents);
	INT GetContents(CDatabaseTCProcedureThreadContents *pContents) CONST;
	BOOL SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;
	VOID EnableSynchronization(BOOL bEnable = TRUE);
	BOOL IsSynchronizationEnabled() CONST;

private:
	BOOL Initialize(CStringArray &szErrorParameters);
	BOOL Initialize(CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth);

	BOOL Update(CONST CTMEnvironment *pTMEnvironment);

	BOOL UpdateBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);

	VOID SetRunningState(UINT nState);
	UINT GetRunningState() CONST;

	BOOL Break(LPCTSTR pszName);

	BOOL Suspend();
	BOOL Synchronize();
	BOOL Resume();

protected:
	BOOL CheckStepTrigger(LPCTSTR pszName);
	BOOL CheckStepBody(LPCTSTR pszName);
	BOOL CheckStepConfirmation(LPCTSTR pszName);

	VOID AlertStepTriggerSuccess(LPCTSTR pszName);
	VOID AlertStepTriggerSuccess(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepTriggerWarning(LPCTSTR pszName);
	VOID AlertStepTriggerWarning(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepTriggerFailure(LPCTSTR pszName);
	VOID AlertStepTriggerFailure(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepBodySuccess(LPCTSTR pszName);
	VOID AlertStepBodySuccess(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepBodyWarning(LPCTSTR pszName);
	VOID AlertStepBodyWarning(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepBodyFailure(LPCTSTR pszName);
	VOID AlertStepBodyFailure(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepConfirmationSuccess(LPCTSTR pszName);
	VOID AlertStepConfirmationSuccess(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepConfirmationWarning(LPCTSTR pszName);
	VOID AlertStepConfirmationWarning(LPCTSTR pszName, LPCTSTR pszMessage);
	VOID AlertStepConfirmationFailure(LPCTSTR pszName);
	VOID AlertStepConfirmationFailure(LPCTSTR pszName, LPCTSTR pszMessage);

	BOOL CallProcedure(LPCTSTR pszName, ...);
	BOOL StartProcedure(LPCTSTR pszName, ...);
	BOOL SetProcedureState(LPCTSTR pszName, UINT nState);
	BOOL SetThreadState(LPCTSTR pszName, UINT nState);
	VOID EnableThread(BOOL bEnable = TRUE);
	BOOL IsThreadEnabled() CONST;
	VOID ResetThread();

	BOOL SetSynchronizationObject(CEvent &cEvent);
	BOOL SetSynchronizationObject(LPCTSTR pszEvent);
	BOOL WaitSynchronizationObject(CEvent &cEvent, DWORD dwTimeout);
	BOOL WaitSynchronizationObject(LPCTSTR pszEvent, DWORD dwTimeout);
	BOOL WaitTimeInterval(DWORD dwTimeInterval);
	BOOL WaitAbsoluteTime(CONST CTimeKey &tTime);

	BOOL InjectAlert(LPCTSTR pszAlert);
	BOOL LogMessage(LPCTSTR pszFileName, LPCTSTR pszMessage, BOOL bPlainText = FALSE, BOOL bUnicode = FALSE);
	BOOL UserInteraction(UINT nType, LPCTSTR pszMessage, CONST CStringArray &szVariables, CONST CStringArray &szVariableValues);

	BOOL ScheduleTCFunction(LPCTSTR pszName, LPCTSTR pszSequence, LPCTSTR pszFunction, BOOL bProcedure, INT nEntry, INT nEntries, CONST CTimeTag &tScheduleTime, CONST CTimeTag &tReleaseTime, DWORD dwReleaseOffset, CONST CTimeTag &tExecutionTime, DWORD dwExecutionOffset, BOOL bEarlierExecution, INT nBlockID, BOOL bGrouped, BOOL bCritical, ULONGLONG nAckFlags);

protected:
	CString GetTMUnitTag() CONST;
	CTimeTag GetTMUnitTimeTag() CONST;
	UINT GetTMUnitID() CONST;
	BOOL GetTMUnitData(INT nBytePos, BYTE &nValue) CONST;
	BOOL GetTMUnitData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST;
	WORD GetTMUnitQuality() CONST;

	double GetTotalTMBandwidth() CONST;
	double GetAvailableTMBandwidth() CONST;
	double GetMaxDiagnosticTMBandwidth() CONST;
	double GetAvailableDiagnosticTMBandwidth() CONST;
	CTimeTag GetLastTMBandwidthMeasurementTime() CONST;

protected:
	ULONGLONG ConvertBinaryStringToValue(LPCTSTR pszValue) CONST;
	ULONGLONG ConvertOctalStringToValue(LPCTSTR pszValue) CONST;
	ULONGLONG ConvertHexadecimalStringToValue(LPCTSTR pszValue) CONST;
	TIMETAG ConvertTimeStringToValue(LPCTSTR pszTime) CONST;

protected:
	BOOL __InitTCFunctionConstParameters(CDatabaseTCFunction *pTCFunction);
	BOOL __InitTCPacketConstParameters(CDatabaseTCPacket *pTCPacket);
	BOOL __CheckTCFunctionPreexecutionParameterGroup(LPCTSTR pszGroup, CStringArray &szParameters) CONST;
	BOOL __CheckTCFunctionExecutionParameterGroup(CONST CDatabaseTCFunction *pTCFunction, LPCTSTR pszGroup, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;
	BOOL __SetTCFunctionParameter(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nAttributes = 0);
	BOOL __SetTCFunctionParameterRawIntValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LONGLONG nValue);
	BOOL __SetTCFunctionParameterRawUIntValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nValue);
	BOOL __SetTCFunctionParameterRawFloatValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, double fValue);
	BOOL __SetTCFunctionParameterValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, double fValue, BOOL bExtrapolate = TRUE);
	BOOL __SetTCFunctionParameterTimeValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LPCTSTR pszTime);
	BOOL __SetTCFunctionParameterStringValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LPCTSTR pszText);
	BOOL __SetTCPacketParameter(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nAttributes = 0);
	BOOL __SetTCPacketParameterRawIntValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LONGLONG nValue);
	BOOL __SetTCPacketParameterRawUIntValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nValue);
	BOOL __SetTCPacketParameterRawFloatValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, double fValue);
	BOOL __SetTCPacketParameterRawTimeValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LPCTSTR pszTime);

	BOOL __SetRawIntValue(CTCParameter *pTCParameter, INT nOccurrence, LONGLONG nValue);
	LONGLONG __GetRawIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	LONGLONG __GetRawIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	BOOL __SetRawUIntValue(CTCParameter *pTCParameter, INT nOccurrence, ULONGLONG nValue);
	ULONGLONG __GetRawUIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	ULONGLONG __GetRawUIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	BOOL __SetRawFloatValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue);
	double __GetRawFloatValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	double __GetRawFloatValue(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	BOOL __SetIntValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue);
	LONGLONG __GetIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	LONGLONG __GetIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	BOOL __SetUIntValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue);
	ULONGLONG __GetUIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	ULONGLONG __GetUIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	BOOL __SetFloatValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue);
	double __GetFloatValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	double __GetFloatValue(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	BOOL __SetTimeValue(CTCParameter *pTCParameter, INT nOccurrence, CONST CTimeTag &tTime);
	CTimeTag __GetTimeValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	BOOL __SetStringValue(CTCParameter *pTCParameter, INT nOccurrence, LPCTSTR pszText);
	CString __GetStringValue(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	CString __GetStringValue(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	CTimeTag __GetValueTime(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	LONGLONG __GetPastRawIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	ULONGLONG __GetPastRawUIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	double __GetPastRawFloatValue(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	LONGLONG __GetPastIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	ULONGLONG __GetPastUIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	double __GetPastFloatValue(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	CString __GetPastStringValue(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	CTimeTag __GetPastValueTime(CONST CTMParameter *pTMParameter, INT nSample) CONST;
	LONGLONG __CalculateAverageIntValue(CONST CTMParameter *pTMParameter, INT nSamples) CONST;
	ULONGLONG __CalculateAverageUIntValue(CONST CTMParameter *pTMParameter, INT nSamples) CONST;
	double __CalculateAverageFloatValue(CONST CTMParameter *pTMParameter, INT nSamples) CONST;
	UINT __GetValueStatus(CONST CTMParameter *pTMParameter, INT nOccurrence = 0) CONST;
	UINT __GetValueStatus(CONST CTCParameter *pTCParameter, INT nOccurrence = 0) CONST;
	LONGLONG __DecalibrateToIntValue(CONST CTCParameter *pTCParameter, double fValue) CONST;
	LONGLONG __DecalibrateToIntValue(CONST CTCParameter *pTCParameter, LPCTSTR pszValue) CONST;
	ULONGLONG __DecalibrateToUIntValue(CONST CTCParameter *pTCParameter, double fValue) CONST;
	ULONGLONG __DecalibrateToUIntValue(CONST CTCParameter *pTCParameter, LPCTSTR pszValue) CONST;
	double __DecalibrateToFloatValue(CONST CTCParameter *pTCParameter, double fValue) CONST;
	double __DecalibrateToFloatValue(CONST CTCParameter *pTCParameter, LPCTSTR pszValue) CONST;

	LONGLONG __CheckArgumentIntValueRange(LPCTSTR pszArgument, LONGLONG nValue) CONST;
	ULONGLONG __CheckArgumentUIntValueRange(LPCTSTR pszArgument, ULONGLONG nValue) CONST;
	double __CheckArgumentFloatValueRange(LPCTSTR pszArgument, double fValue) CONST;
	CString __CheckArgumentTextRange(LPCTSTR pszArgument, LPCTSTR pszText) CONST;
	TIMETAG __CheckArgumentTimeRange(LPCTSTR pszArgument, TIMETAG tTime) CONST;
	LONGLONG __CheckVariableIntValueRange(LPCTSTR pszVariable, LONGLONG nValue) CONST;
	ULONGLONG __CheckVariableUIntValueRange(LPCTSTR pszVariable, ULONGLONG nValue) CONST;
	double __CheckVariableFloatValueRange(LPCTSTR pszVariable, double fValue) CONST;
	CString __CheckVariableTextRange(LPCTSTR pszVariable, LPCTSTR pszText) CONST;
	TIMETAG __CheckVariableTimeRange(LPCTSTR pszVariable, TIMETAG tTime) CONST;

protected:
	INT __Break(UINT nLine);

protected:
	CTMParameter *__GetTMParameter(INT nIndex) CONST;
	CTCParameter *__GetTCParameter(INT nIndex) CONST;

	HANDLE __GetTMEvent() CONST;
	HANDLE __GetTCEvent() CONST;

private:
	BOOL CheckLineBreakpoint(UINT nLine, UINT nType);
	BOOL CheckStepBreakpoint(LPCTSTR pszName, UINT nType);
	BOOL CheckStepAuthorization(LPCTSTR pszName, BOOL bTrigger = TRUE);
	BOOL AuthorizeStepExecution(LPCTSTR pszName);
	BOOL ChangeStepState(LPCTSTR pszName, UINT nState);
	BOOL CheckStepStates(UINT &nState, CStringArray &szNames, CUIntArray &nStates, UINT &nLine);
	BOOL AcknowledgeStepStates();
	BOOL ResetStepStates();

private:
	CDatabaseTCProcedureThreadStep *FindStep() CONST;
	CDatabaseTCProcedureThreadStep *FindStep(LPCTSTR pszName) CONST;

private:
	BOOL ReportSuccessMessage(LPCTSTR pszMessage);
	BOOL ReportWarningMessage(LPCTSTR pszMessage);
	BOOL ReportFailureMessage(LPCTSTR pszMessage);
	BOOL ReportAlertMessage(LPCTSTR pszMessage);

	BOOL HasOpenDialogs() CONST;

	BOOL IsThreadTerminating() CONST;

	CTCProcedureProcess *GetProcess() CONST;

private:
	static BOOL CALLBACK EnumThreadDialogsProc(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureThread)
public:
	virtual int Run();
	virtual BOOL InitInstance();
	virtual int ExitInstance(INT nExitCode);
private:
	virtual BOOL InitParameters();
	virtual INT EnumParameters(CStringArray &szParameters) CONST;
protected:
	virtual BOOL WaitThreadActivationExpression();
	virtual BOOL CheckStepTriggerExpression(LPCTSTR pszName) CONST;
	virtual BOOL CheckStepBodyExpression(LPCTSTR pszName) CONST;
	virtual BOOL CheckStepConfirmationExpression(LPCTSTR pszName) CONST;
protected:
	virtual BOOL InitTCFunction(LPCTSTR pszName, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch, BOOL &bAuthorization);
	virtual BOOL EnumTCFunctionExecutionVerificationTimeWindows(LPCTSTR pszName, INT nEntry, CUIntArray &nStageIDs, CUIntArray &nStageTimeWindowOffsets, CUIntArray &nStageTimeWindowSizes, CUIntArray &nStageTimeWindowUncertainties) CONST;
	virtual BOOL CheckTCFunctionPreexecutionExpression(LPCTSTR pszName, INT nEntry, CStringArray &szParameters) CONST;
	virtual BOOL CheckTCFunctionExecutionExpression(LPCTSTR pszName, INT nEntry, CONST CDatabaseTCFunction *pTCFunction, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureProcess

// Specify the telecommand procedure process identifier types
#define TCPROCEDUREPROCESS_IDENTIFIERTYPE_NONE   0
#define TCPROCEDUREPROCESS_IDENTIFIERTYPE_ARGUMENT   1
#define TCPROCEDUREPROCESS_IDENTIFIERTYPE_VARIABLE   2
#define TCPROCEDUREPROCESS_IDENTIFIERTYPE_TMPARAMETER   3
#define TCPROCEDUREPROCESS_IDENTIFIERTYPE_TCPARAMETER   4
// Specify the telecommand procedure process event types
#define TCPROCEDUREPROCESS_EVENTTYPE_COMMAND   0
#define TCPROCEDUREPROCESS_EVENTTYPE_UPDATE   1
#define TCPROCEDUREPROCESS_EVENTTYPE_EXIT   2
#define TCPROCEDUREPROCESS_EVENTTYPES   3

class AFX_EXT_CLASS CTCProcedureProcess : public CPtrArray
{
	// Construction
public:
	CTCProcedureProcess();
	CTCProcedureProcess(LPCTSTR pszName, INT nProcedureID, INT nID, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	~CTCProcedureProcess();

	// Attributes
private:
	INT  m_nProcessID;
	INT  m_nProcedureID;
	UINT  m_nAttributes;
	CString  m_szName;
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments;
	CDatabaseTCProcedureVariables  m_pDatabaseTCProcedureVariables;
private:
	UINT  m_nState;
	BOOL  m_bAutoExecution;
	BOOL  m_bAutoTermination;
private:
	CTCProcessEngine  *m_pTCProcessEngine;
	CTCEnvironment  *m_pTCEnvironment;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetID(INT nID);
	INT GetID() CONST;
	VOID SetProcedureID(INT nID);
	INT GetProcedureID() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	BOOL SetArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments);
	INT GetArguments(CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments) CONST;
	BOOL SetVariables(CONST CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables);
	INT GetVariables(CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables) CONST;

public:
	BOOL Initialize(CStringArray &szErrorParameters);

	BOOL Update(CONST CTMEnvironment *pTMEnvironment);

	VOID SetRunningState(UINT nState);
	UINT GetRunningState() CONST;

	BOOL Break();

	VOID EnableAutoExecution(BOOL bEnable = TRUE);
	BOOL IsAutoExecutionEnabled() CONST;
	VOID EnableAutoTermination(BOOL bEnable = TRUE);
	BOOL IsAutoTerminationEnabled() CONST;

	BOOL Terminate(BOOL bAuto = TRUE);

public:
	virtual VOID AssignArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, va_list pArgumentList);
	virtual VOID AssignArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments);
	virtual VOID AssignVariables();

	virtual INT EnumIdentifiers(CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CLongUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers) CONST;
	virtual INT EnumSynchronizationObjects(CStringArray &szObjects, CPtrArray &phObjects) CONST;

public:
	BOOL ReportSuccessMessage(LPCTSTR pszMessage);
	BOOL ReportSuccessMessage(LPCTSTR pszThread, LPCTSTR pszMessage);
	BOOL ReportWarningMessage(LPCTSTR pszMessage);
	BOOL ReportWarningMessage(LPCTSTR pszThread, LPCTSTR pszMessage);
	BOOL ReportFailureMessage(LPCTSTR pszMessage);
	BOOL ReportFailureMessage(LPCTSTR pszThread, LPCTSTR pszMessage);
	BOOL ReportAlertMessage(LPCTSTR pszMessage);

public:
	INT Add(CTCProcedureThread *pThread);

	INT Find(LPCTSTR pszName) CONST;

	CTCProcedureThread *GetAt(INT nIndex) CONST;
	CTCProcedureThread *operator[](INT nIndex) CONST;

	VOID RemoveAll();

private:
	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureProcessManager

class AFX_EXT_CLASS CTCProcedureProcessManager : public CObject
{
	// Construction
public:
	CTCProcedureProcessManager();
	~CTCProcedureProcessManager();

	// Attributes
private:
	CONST CDatabaseEngine  *m_pDatabase;
	CTCProcessEngine  *m_pTCProcessEngine;
	CTCEnvironment  *m_pTCEnvironment;
private:
	CPtrArray  m_pTCProcedureProcesses;
	CUIntArray  m_nTCProcedureProcessIDs;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Initialize(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nProcessID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters);
	BOOL InitializeParameters(INT nProcessID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth);
	BOOL Run(INT nProcessID, va_list pArgumentList, UINT nExecutionMode);
	BOOL Start(INT nProcessID, CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, UINT nExecutionMode);
	BOOL Update(INT nProcessID, CONST CTMEnvironment *pTMEnvironment);
	BOOL Suspend(INT nProcessID);
	BOOL IsSuspended(INT nProcessID) CONST;
	BOOL Resume(INT nProcessID, BOOL bAuto = TRUE);
	BOOL IsRunning(INT nProcessID) CONST;
	BOOL Terminate(INT nProcessID, BOOL bAuto = TRUE);
	BOOL Abort(INT nProcessID);

	INT EnumIdentifiers(INT nProcessID, CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CLongUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers) CONST;

	INT EnumThreads(INT nProcessID, CStringArray &szThreads, CUIntArray &nThreadStates) CONST;
	INT EnumThreadStepStates(INT nProcessID, LPCTSTR pszThread, UINT &nState, CStringArray &szStepNames, CUIntArray &nStepStates, UINT &nLine) CONST;
	BOOL AcknowledgeThreadStepState(INT nProcessID, LPCTSTR pszThread);

	BOOL UpdateThreadBreakpoints(INT nProcessID, LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);

	BOOL InitThreadTCFunction(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch, BOOL bAllowAuthorization);
	BOOL EnumThreadTCFunctionExecutionVerificationTimeWindows(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CUIntArray &nStageIDs, CUIntArray &nStageTimeWindowOffsets, CUIntArray &nStageTimeWindowSizes, CUIntArray &nStageTimeWindowUncertainties) CONST;
	BOOL CheckThreadTCFunctionPreexecutionExpression(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CStringArray &szParameters) CONST;
	BOOL CheckThreadTCFunctionExecutionExpression(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CONST CDatabaseTCFunction *pTCFunction, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;

	BOOL HasThreadOpenDialogs(INT nProcessID, LPCTSTR pszThread) CONST;

public:
	INT LinkTMParameter(INT nProcessID, LPCTSTR pszTag) CONST;
	INT LinkTCParameter(INT nProcessID, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag) CONST;

private:
	virtual CTCProcedureProcess *AllocateProcess(LPCTSTR pszName, INT nProcedureID, INT nProcessID, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	virtual CTCProcedureThread *AllocateThread(LPCTSTR pszName, CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, HANDLE hTMEvent, HANDLE hTCEvent, HANDLE hUpdate, HANDLE hExit);

private:
	CTCProcedureProcess *AddProcess(LPCTSTR pszName, INT nProcedureID, INT nProcessID, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	CTCProcedureProcess *FindProcess(INT nProcessID) CONST;
	BOOL RemoveProcess(INT nProcessID);

	VOID AssignParameters(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments);

	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TCPROCEDURES_H__
