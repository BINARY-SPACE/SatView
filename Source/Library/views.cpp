// VIEWS.CPP : Views Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the views related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1999/12/13 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTextViewBlinkThread

IMPLEMENT_DYNCREATE(CTextViewBlinkThread, CThread)

CTextViewBlinkThread::CTextViewBlinkThread(CTextView *pView) : CThread()
{
	m_pView = pView;
	m_nCount = 0;
}

BOOL CTextViewBlinkThread::Start()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((!m_nCount  &&  CThread::CreateThread()) || m_nCount > 0)
	{
		m_nCount++;
		return TRUE;
	}
	return FALSE;
}

BOOL CTextViewBlinkThread::Stop()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_nCount = (m_nCount > 0) ? (m_nCount - 1) : m_nCount; !m_nCount; )
	{
		SetEvent(m_hObject);
		break;
	}
	return TRUE;
}

BOOL CTextViewBlinkThread::IsActive() CONST
{
	return IsThreadActive();
}

int CTextViewBlinkThread::Run()
{
	BOOL  bState;
	BOOL  bExit;

	for (bState = TRUE; Wait(DISPLAYVIEW_BLINK_INTERVAL) == WAIT_TIMEOUT; bState = !bState)
	{
		for (bExit = !m_nCount; m_pView != (CTextView *)NULL && !bExit; )
		{
			m_pView->DrawBlinking(bState);
			break;
		}
		if (bExit) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CTextViewBlinkThread, CThread)
	//{{AFX_MSG_MAP(CTextViewBlinkThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextViewBlinkThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTextViewAttribute

CTextViewAttribute::CTextViewAttribute() : CObject()
{
	return;
}

CTextViewAttribute::~CTextViewAttribute()
{
	Reset();
}

VOID CTextViewAttribute::SetColumnFormat(INT nColumn, UINT nFormat)
{
	if (nColumn >= 0)
	{
		m_nFormats.SetAtGrow(nColumn + 1, nFormat);
		m_bFormats.SetAtGrow(nColumn + 1, TRUE);
		return;
	}
	m_nFormats.RemoveAll();
	m_bFormats.RemoveAll();
	m_nFormats.Add(nFormat);
	m_bFormats.Add(TRUE);
}

BOOL CTextViewAttribute::GetColumnFormat(INT nColumn, UINT &nFormat) CONST
{
	if (nColumn >= 0)
	{
		if (nColumn < m_bFormats.GetSize() - 1 && m_bFormats.GetAt(nColumn + 1))
		{
			nFormat = m_nFormats.GetAt(nColumn + 1);
			return TRUE;
		}
	}
	if (m_bFormats.GetSize() > 0 && m_bFormats.GetAt(0))
	{
		nFormat = m_nFormats.GetAt(0);
		return TRUE;
	}
	return FALSE;
}

VOID CTextViewAttribute::SetColumnColor(INT nColumn, COLORREF nColor)
{
	if (nColumn >= 0)
	{
		m_nColors.SetAtGrow(nColumn + 1, nColor);
		m_bColors.SetAtGrow(nColumn + 1, TRUE);
		return;
	}
	m_nColors.RemoveAll();
	m_bColors.RemoveAll();
	m_nColors.Add(nColor);
	m_bColors.Add(TRUE);
}

BOOL CTextViewAttribute::GetColumnColor(INT nColumn, COLORREF &nColor) CONST
{
	if (nColumn >= 0)
	{
		if (nColumn < m_bColors.GetSize() - 1 && m_bColors.GetAt(nColumn + 1))
		{
			nColor = m_nColors.GetAt(nColumn + 1);
			return TRUE;
		}
	}
	if (m_bColors.GetSize() > 0 && m_bColors.GetAt(0))
	{
		nColor = m_nColors.GetAt(0);
		return TRUE;
	}
	return FALSE;
}

VOID CTextViewAttribute::SetColumnFont(INT nColumn, CONST LOGFONT *plfFont)
{
	INT  nFont;
	INT  nFonts;
	LOGFONT  *pFontInfo;

	if (nColumn >= 0)
	{
		if (nColumn < m_blfFonts.GetSize() - 1 && m_blfFonts.GetAt(nColumn + 1))
		{
			CopyMemory(m_plfFonts.GetAt(nColumn + 1), plfFont, sizeof(LOGFONT));
			return;
		}
		if ((pFontInfo = (LOGFONT *)GlobalAlloc(GPTR, sizeof(LOGFONT))))
		{
			CopyMemory(pFontInfo, plfFont, sizeof(LOGFONT));
			m_plfFonts.SetAtGrow(nColumn + 1, pFontInfo);
			m_blfFonts.SetAtGrow(nColumn + 1, TRUE);
		}
		return;
	}
	for (nFont = 0, nFonts = (INT)m_plfFonts.GetSize(); nFont < nFonts; nFont++)
	{
		if ((pFontInfo = (LOGFONT *)m_plfFonts.GetAt(nFont)) && m_blfFonts.GetAt(nFont))
		{
			GlobalFree(pFontInfo);
			continue;
		}
	}
	for (m_plfFonts.RemoveAll(), m_blfFonts.RemoveAll(); (pFontInfo = (LOGFONT *)GlobalAlloc(GPTR, sizeof(LOGFONT))); )
	{
		CopyMemory(pFontInfo, plfFont, sizeof(LOGFONT));
		m_plfFonts.Add(pFontInfo);
		m_blfFonts.Add(TRUE);
		break;
	}
}

BOOL CTextViewAttribute::GetColumnFont(INT nColumn, LOGFONT *plfFont) CONST
{
	if (nColumn >= 0)
	{
		if (nColumn < m_blfFonts.GetSize() - 1 && m_blfFonts.GetAt(nColumn + 1))
		{
			CopyMemory(plfFont, m_plfFonts.GetAt(nColumn + 1), sizeof(LOGFONT));
			return TRUE;
		}
	}
	if (m_blfFonts.GetSize() > 0 && m_blfFonts.GetAt(0))
	{
		CopyMemory(plfFont, m_plfFonts.GetAt(0), sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

VOID CTextViewAttribute::SetColumnBlinking(INT nColumn, BOOL bBlink)
{
	if (nColumn >= 0)
	{
		if (bBlink)
		{
			m_bBlink[0].SetAtGrow(nColumn + 1, TRUE);
			m_bBlink[1].SetAtGrow(nColumn + 1, TRUE);
			return;
		}
		if (nColumn == m_bBlink[1].GetUpperBound() - 1)
		{
			m_bBlink[0].RemoveAt(nColumn + 1);
			m_bBlink[1].RemoveAt(nColumn + 1);
			return;
		}
		if (nColumn < m_bBlink[1].GetUpperBound() - 1)
		{
			m_bBlink[0].SetAt(nColumn + 1, TRUE);
			m_bBlink[1].SetAt(nColumn + 1, FALSE);
		}
		return;
	}
	if (bBlink)
	{
		m_bBlink[0].SetAtGrow(0, TRUE);
		m_bBlink[1].SetAtGrow(0, TRUE);
		m_bBlink[0].SetSize(1);
		m_bBlink[1].SetSize(1);
		return;
	}
	m_bBlink[0].RemoveAll();
	m_bBlink[1].RemoveAll();
}

BOOL CTextViewAttribute::GetColumnBlinking(INT nColumn, BOOL &bBlink) CONST
{
	if (nColumn >= 0)
	{
		if (nColumn < m_bBlink[1].GetSize() - 1 && m_bBlink[1].GetAt(nColumn + 1))
		{
			bBlink = TRUE;
			return TRUE;
		}
	}
	if (m_bBlink[1].GetSize() > 0 && m_bBlink[1].GetAt(0))
	{
		bBlink = TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CTextViewAttribute::SetColumnBlinkingState(INT nColumn, BOOL bState)
{
	if (nColumn >= 0)
	{
		if (nColumn < m_bBlink[1].GetSize() - 1 && m_bBlink[1].GetAt(nColumn + 1))
		{
			m_bBlink[0].SetAt(nColumn + 1, bState);
			return TRUE;
		}
		return FALSE;
	}
	if (m_bBlink[1].GetSize() > 0 && m_bBlink[1].GetAt(0))
	{
		m_bBlink[0].SetAt(0, bState);
		return TRUE;
	}
	return FALSE;
}

BOOL CTextViewAttribute::GetColumnBlinkingState(INT nColumn, BOOL &bState) CONST
{
	if (nColumn >= 0)
	{
		if (nColumn < m_bBlink[1].GetSize() - 1 && m_bBlink[1].GetAt(nColumn + 1))
		{
			bState = m_bBlink[0].GetAt(nColumn + 1);
			return TRUE;
		}
	}
	if (m_bBlink[1].GetSize() > 0 && m_bBlink[1].GetAt(0))
	{
		bState = m_bBlink[0].GetAt(0);
		return TRUE;
	}
	return FALSE;
}

VOID CTextViewAttribute::Adjust(INT nColumn, BOOL bInsert)
{
	LOGFONT  *pFontInfo;

	for (; nColumn >= 0 && bInsert; )
	{
		if (nColumn < m_bFormats.GetSize() - 1)
		{
			m_nFormats.InsertAt(nColumn + 1, 0, 1);
			m_bFormats.InsertAt(nColumn + 1, FALSE, 1);
		}
		if (nColumn < m_bColors.GetSize() - 1)
		{
			m_nColors.InsertAt(nColumn + 1, 0, 1);
			m_bColors.InsertAt(nColumn + 1, FALSE, 1);
		}
		if (nColumn < m_blfFonts.GetSize() - 1)
		{
			m_plfFonts.InsertAt(nColumn + 1, 0, 1);
			m_blfFonts.InsertAt(nColumn + 1, FALSE, 1);
		}
		if (nColumn < m_bBlink[0].GetSize() - 1)
		{
			m_bBlink[0].InsertAt(nColumn + 1, FALSE, 1);
			m_bBlink[1].InsertAt(nColumn + 1, FALSE, 1);
		}
		break;
	}
	for (; nColumn >= 0 && !bInsert; )
	{
		if (nColumn < m_bFormats.GetSize() - 1)
		{
			m_nFormats.RemoveAt(nColumn + 1);
			m_bFormats.RemoveAt(nColumn + 1);
		}
		if (nColumn < m_bColors.GetSize() - 1)
		{
			m_nColors.RemoveAt(nColumn + 1);
			m_bColors.RemoveAt(nColumn + 1);
		}
		if (nColumn < m_blfFonts.GetSize() - 1)
		{
			for (; (pFontInfo = (LOGFONT *)m_plfFonts.GetAt(nColumn + 1)) && m_blfFonts.GetAt(nColumn + 1); )
			{
				GlobalFree(pFontInfo);
				break;
			}
			m_plfFonts.RemoveAt(nColumn + 1);
			m_blfFonts.RemoveAt(nColumn + 1);
		}
		if (nColumn < m_bBlink[0].GetSize() - 1)
		{
			m_bBlink[0].RemoveAt(nColumn + 1);
			m_bBlink[1].RemoveAt(nColumn + 1);
		}
		break;
	}
}

VOID CTextViewAttribute::Reset()
{
	INT  nFont;
	INT  nFonts;
	LOGFONT  *pFontInfo;

	for (nFont = 0, nFonts = (INT)m_plfFonts.GetSize(), m_nFormats.RemoveAll(), m_bFormats.RemoveAll(), m_nColors.RemoveAll(), m_bColors.RemoveAll(), m_bBlink[0].RemoveAll(), m_bBlink[1].RemoveAll(); nFont < nFonts; nFont++)
	{
		if ((pFontInfo = (LOGFONT *)m_plfFonts.GetAt(nFont)) && m_blfFonts.GetAt(nFont))
		{
			GlobalFree(pFontInfo);
			continue;
		}
	}
	m_plfFonts.RemoveAll();
	m_blfFonts.RemoveAll();
}

BOOL CTextViewAttribute::Copy(CONST CTextViewAttribute *pAttribute)
{
	INT  nFont;
	INT  nFonts;
	LOGFONT  *pFontInfo;

	for (nFont = 0, nFonts = (INT)pAttribute->m_plfFonts.GetSize(), Reset(), m_nFormats.Copy(pAttribute->m_nFormats), m_bFormats.Copy(pAttribute->m_bFormats), m_nColors.Copy(pAttribute->m_nColors), m_bColors.Copy(pAttribute->m_bColors), m_bBlink[0].Copy(pAttribute->m_bBlink[0]), m_bBlink[1].Copy(pAttribute->m_bBlink[1]); nFont < nFonts; nFont++)
	{
		if ((pFontInfo = (pAttribute->m_blfFonts.GetAt(nFont)) ? (LOGFONT *)GlobalAlloc(GPTR, sizeof(LOGFONT)) : (LOGFONT *)NULL))
		{
			CopyMemory(pFontInfo, pAttribute->m_plfFonts.GetAt(nFont), sizeof(LOGFONT));
			m_plfFonts.SetAtGrow(nFont, pFontInfo);
			m_blfFonts.SetAtGrow(nFont, TRUE);
			continue;
		}
		if (!pAttribute->m_blfFonts.GetAt(nFont))
		{
			m_plfFonts.SetAtGrow(nFont, (LPVOID)NULL);
			m_blfFonts.SetAtGrow(nFont, FALSE);
			continue;
		}
		break;
	}
	return((nFont == nFonts) ? TRUE : FALSE);
}

BOOL CTextViewAttribute::Compare(CONST CTextViewAttribute *pAttribute) CONST
{
	INT  nFont;
	INT  nFonts;

	for (nFont = 0, nFonts = (pAttribute->m_nFormats.GetSize() == m_nFormats.GetSize() && pAttribute->m_bFormats.GetSize() == m_bFormats.GetSize() && m_nFormats.GetSize() == m_bFormats.GetSize() && pAttribute->m_nColors.GetSize() == m_nColors.GetSize() && pAttribute->m_bColors.GetSize() == m_bColors.GetSize() && m_nColors.GetSize() == m_bColors.GetSize() && pAttribute->m_plfFonts.GetSize() == m_plfFonts.GetSize() && pAttribute->m_blfFonts.GetSize() == m_blfFonts.GetSize() && m_plfFonts.GetSize() == m_blfFonts.GetSize() && pAttribute->m_bBlink[0].GetSize() == m_bBlink[0].GetSize() && pAttribute->m_bBlink[1].GetSize() == m_bBlink[1].GetSize() && m_bBlink[0].GetSize() == m_bBlink[1].GetSize() && !memcmp(pAttribute->m_nFormats.GetData(), m_nFormats.GetData(), m_nFormats.GetSize()*sizeof(UINT)) && !memcmp(pAttribute->m_bFormats.GetData(), m_bFormats.GetData(), m_bFormats.GetSize()*sizeof(BYTE)) && !memcmp(pAttribute->m_nColors.GetData(), m_nColors.GetData(), m_nColors.GetSize()*sizeof(UINT)) && !memcmp(pAttribute->m_bColors.GetData(), m_bColors.GetData(), m_bColors.GetSize()*sizeof(BYTE)) && !memcmp(pAttribute->m_blfFonts.GetData(), m_blfFonts.GetData(), m_blfFonts.GetSize()*sizeof(BYTE)) && !memcmp(pAttribute->m_bBlink[0].GetData(), m_bBlink[0].GetData(), m_bBlink[0].GetSize()*sizeof(BYTE)) && !memcmp(pAttribute->m_bBlink[1].GetData(), m_bBlink[1].GetData(), m_bBlink[1].GetSize()*sizeof(BYTE))) ? (INT)m_plfFonts.GetSize() : -1; nFont < nFonts; nFont++)
	{
		if (memcmp(pAttribute->m_plfFonts.GetAt(nFont), m_plfFonts.GetAt(nFont), sizeof(LOGFONT))) break;
		continue;
	}
	return((nFont == nFonts) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTextViewAttributes

CTextViewAttributes::CTextViewAttributes() : CPtrArray()
{
	return;
}

CTextViewAttributes::~CTextViewAttributes()
{
	RemoveAll();
}

CTextViewAttribute *CTextViewAttributes::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTextViewAttribute *)CPtrArray::GetAt(nIndex) : (CTextViewAttribute *)NULL);
}

CTextViewAttribute *CTextViewAttributes::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTextViewAttribute *)CPtrArray::GetAt(nIndex) : (CTextViewAttribute *)NULL);
}

VOID CTextViewAttributes::RemoveAll()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)GetSize(); nIndex < nCount; nIndex++)
	{
		delete GetAt(nIndex);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTextViewAttributes::Copy(CONST CTextViewAttributes *pAttributes)
{
	INT  nIndex;
	INT  nCount;
	CTextViewAttribute  *pAttribute[2];

	for (nIndex = 0, nCount = (INT)pAttributes->GetSize(), RemoveAll(); nIndex < nCount; nIndex++)
	{
		if ((pAttribute[0] = pAttributes->GetAt(nIndex)))
		{
			if ((pAttribute[1] = new CTextViewAttribute))
			{
				pAttribute[1]->Copy(pAttribute[0]);
				SetAtGrow(nIndex, pAttribute[1]);
				continue;
			}
			RemoveAll();
			break;
		}
		SetAtGrow(nIndex, pAttribute[0]);
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTextViewAttributes::Compare(CONST CTextViewAttributes *pAttributes) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (pAttributes->GetSize() == GetSize()) ? (INT)pAttributes->GetSize() : -1; nIndex < nCount; nIndex++)
	{
		if ((!pAttributes->GetAt(nIndex) && !GetAt(nIndex)) || (pAttributes->GetAt(nIndex) && GetAt(nIndex) && pAttributes->GetAt(nIndex)->Compare(GetAt(nIndex)))) continue;
		break;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTextViewDocument

IMPLEMENT_DYNAMIC(CTextViewDocument, CDocument)

CTextViewDocument::CTextViewDocument() : CDocument()
{
	return;
}

CTextViewDocument::~CTextViewDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTextViewHeaderCtrl

IMPLEMENT_DYNCREATE(CTextViewHeaderCtrl, CMFCHeaderCtrl)

CTextViewHeaderCtrl::CTextViewHeaderCtrl() : CMFCHeaderCtrl()
{
	CFontTools  cFontTools(&m_cFont);

	m_nScrollPos = 0;
	m_bUpdate[0] = m_bUpdate[1] = FALSE;
	m_wTextIndent[0] = m_wTextIndent[1] = 0;
	m_wTextSpacing[0] = m_wTextSpacing[1] = 0;
	m_pParentWnd = (CTextView *)NULL;
}

BOOL CTextViewHeaderCtrl::Create(CTextView *pParentWnd, DWORD dwStyle, UINT nID)
{
	if (CMFCHeaderCtrl::Create(HDS_HORZ | (((dwStyle & TVS_BUTTONS) == TVS_BUTTONS) ? HDS_BUTTONS : 0) | WS_CHILD | WS_CLIPSIBLINGS | ((dwStyle & TVS_HEADER) ? WS_VISIBLE : 0), CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), nID))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTextViewHeaderCtrl::Initialize(CTextView *pParentWnd)
{
	CTextViewLock  cLock(pParentWnd);

	m_pParentWnd = pParentWnd;
}

BOOL CTextViewHeaderCtrl::SetColumns(CONST CStringArray &szColumns)
{
	CSize  sizeHeader;
	CUIntArray  nWidths;
	CTextViewLock  cLock(GetParent());

	if (!IsWindow(GetSafeHwnd()))
	{
		m_szColumnsText.Copy(szColumns);
		m_nColumnsWidth.RemoveAll();
		m_nColumnsFormat.RemoveAll();
		return TRUE;
	}
	return(((sizeHeader = CalcExtent(szColumns, nWidths)).cx > 0 && sizeHeader.cy > 0) ? SetColumns(szColumns, nWidths) : FALSE);
}
BOOL CTextViewHeaderCtrl::SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths)
{
	INT  nColumn;
	INT  nColumns;
	CUIntArray  nFormats;
	CTextViewLock  cLock(GetParent());

	if (!IsWindow(GetSafeHwnd()))
	{
		m_szColumnsText.Copy(szColumns);
		m_nColumnsWidth.Copy(nWidths);
		m_nColumnsFormat.RemoveAll();
		m_szColumnsText.SetSize(min(szColumns.GetSize(), nWidths.GetSize()));
		m_nColumnsWidth.SetSize(min(szColumns.GetSize(), nWidths.GetSize()));
		return TRUE;
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		nFormats.Add(HDF_LEFT);
		continue;
	}
	return SetColumns(szColumns, nWidths, nFormats);
}
BOOL CTextViewHeaderCtrl::SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nFormats)
{
	INT  nColumn;
	INT  nColumns;
	CTextViewLock  cLock(GetParent());

	for (nColumn = 0, nColumns = (m_szColumnsText.GetSize() == szColumns.GetSize() && m_nColumnsWidth.GetSize() == nWidths.GetSize() && m_nColumnsFormat.GetSize() == nFormats.GetSize()) ? (INT)szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
	{
		if (m_szColumnsText.GetAt(nColumn) != szColumns.GetAt(nColumn) || m_nColumnsWidth.GetAt(nColumn) != nWidths.GetAt(nColumn) || m_nColumnsFormat.GetAt(nColumn) != nFormats.GetAt(nColumn)) break;
		continue;
	}
	if (nColumn != nColumns)
	{
		m_szColumnsText.Copy(szColumns);
		m_nColumnsWidth.Copy(nWidths);
		m_nColumnsFormat.Copy(nFormats);
		m_szColumnsText.SetSize(min(min(szColumns.GetSize(), nWidths.GetSize()), nFormats.GetSize()));
		m_nColumnsWidth.SetSize(min(min(szColumns.GetSize(), nWidths.GetSize()), nFormats.GetSize()));
		m_nColumnsFormat.SetSize(min(min(szColumns.GetSize(), nWidths.GetSize()), nFormats.GetSize()));
		RecalcLayout((m_bUpdate[0] = TRUE));
	}
	return TRUE;
}

BOOL CTextViewHeaderCtrl::GetColumns(CStringArray &szColumns) CONST
{
	CTextViewLock  cLock(GetParent());

	szColumns.Copy(m_szColumnsText);
	return TRUE;
}
BOOL CTextViewHeaderCtrl::GetColumns(CStringArray &szColumns, CUIntArray &nWidths) CONST
{
	CTextViewLock  cLock(GetParent());

	szColumns.Copy(m_szColumnsText);
	nWidths.Copy(m_nColumnsWidth);
	return TRUE;
}
BOOL CTextViewHeaderCtrl::GetColumns(CStringArray &szColumns, CUIntArray &nWidths, CUIntArray &nFormats) CONST
{
	CTextViewLock  cLock(GetParent());

	szColumns.Copy(m_szColumnsText);
	nWidths.Copy(m_nColumnsWidth);
	nFormats.Copy(m_nColumnsFormat);
	return TRUE;
}

BOOL CTextViewHeaderCtrl::SetColumnsFont(CFont *pFont)
{
	LOGFONT  lfFont[2];
	CTextViewLock  cLock(GetParent());

	if (!m_cFont.GetSafeHandle() || !pFont->GetLogFont(&lfFont[0]) || !m_cFont.GetLogFont(&lfFont[1]) || memcmp(&lfFont[0], &lfFont[1], sizeof(LOGFONT)))
	{
		for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont[0]) > 0 && m_cFont.CreateFontIndirect(&lfFont[0]); )
		{
			m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent();
			m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing();
			RecalcLayout(TRUE);
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}
BOOL CTextViewHeaderCtrl::SetColumnsFont(CONST LOGFONT *plfFont)
{
	CFont  cFont;

	return((cFont.CreateFontIndirect(plfFont) && SetColumnsFont(&cFont)) ? TRUE : FALSE);
}

BOOL CTextViewHeaderCtrl::GetColumnsFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return(GetColumnsFont(&lfFont) && pFont->CreateFontIndirect(&lfFont));
}
BOOL CTextViewHeaderCtrl::GetColumnsFont(LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(GetParent());

	return((m_cFont.GetSafeHandle() != (HGDIOBJ)NULL  &&  m_cFont.GetObject(sizeof(LOGFONT), plfFont) > 0) ? TRUE : FALSE);
}

BOOL CTextViewHeaderCtrl::AddColumn(LPCTSTR pszColumn)
{
	return InsertColumn(pszColumn, -1);
}
BOOL CTextViewHeaderCtrl::AddColumn(LPCTSTR pszColumn, INT nWidth, UINT nFormat)
{
	return InsertColumn(pszColumn, -1, nWidth, nFormat);
}

BOOL CTextViewHeaderCtrl::InsertColumn(LPCTSTR pszColumn, INT nColumn)
{
	CTextViewLock  cLock(GetParent());

	return InsertColumn(pszColumn, nColumn, CalcColumnExtent(pszColumn).cx);
}
BOOL CTextViewHeaderCtrl::InsertColumn(LPCTSTR pszColumn, INT nColumn, INT nWidth, UINT nFormat)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	CStringArray  szItem;
	CStringArray  szContent;
	CTextViewAttribute  *pAttribute;
	CTextViewAttributes  pAttributes;
	CTextViewLock  cLock(GetParent());

	for (m_szColumnsText.InsertAt((nIndex = (nColumn < 0 || nColumn >(INT) m_szColumnsText.GetSize()) ? (INT)m_szColumnsText.GetSize() : nColumn), pszColumn), m_nColumnsWidth.InsertAt(nIndex, (nIndex > 0) ? ((INT)m_nColumnsWidth.GetAt(nIndex - 1) + nWidth) : nWidth), m_nColumnsFormat.InsertAt(nIndex, nFormat), nCount = (INT)m_szColumnsText.GetSize() - 1; nIndex < nCount; nIndex++)
	{
		m_nColumnsWidth.SetAt(nIndex + 1, m_nColumnsWidth.GetAt(nIndex + 1) + nWidth);
		continue;
	}
	for (nItem = 0, nItems = (GetParent()->GetContent(szContent, pAttributes)) ? (INT)szContent.GetSize() : 0; nItem < nItems; nItem++)
	{
		if (GetParent()->ConvertText(szContent.GetAt(nItem), szItem) >= 0) szItem.InsertAt((nColumn < 0) ? m_szColumnsText.GetSize() : nColumn, EMPTYSTRING);
		szContent.SetAt(nItem, GetParent()->ConvertText(szItem));
	}
	for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pAttribute = pAttributes.GetAt(nItem)))
		{
			pAttribute->Adjust((nColumn < 0) ? (INT)m_szColumnsText.GetSize() : nColumn);
			continue;
		}
	}
	GetParent()->SetContent(szContent, pAttributes);
	RecalcLayout((m_bUpdate[0] = TRUE));
	return TRUE;
}

BOOL CTextViewHeaderCtrl::DeleteColumn(INT nColumn)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	CStringArray  szItem;
	CStringArray  szContent;
	CTextViewAttribute  *pAttribute;
	CTextViewAttributes  pAttributes;
	CTextViewLock  cLock(GetParent());

	for (nIndex = nColumn + 1, nCount = (INT)m_szColumnsText.GetSize(); nIndex > 0 && nIndex < nCount; nIndex++)
	{
		m_nColumnsWidth.SetAt(nIndex, (nColumn > 0) ? (m_nColumnsWidth.GetAt(nIndex) - m_nColumnsWidth.GetAt(nColumn) + m_nColumnsWidth.GetAt(nColumn - 1)) : (m_nColumnsWidth.GetAt(nIndex) - m_nColumnsWidth.GetAt(nColumn)));
		continue;
	}
	if (nColumn >= 0 && nColumn < nCount)
	{
		for (nItem = 0, nItems = (GetParent()->GetContent(szContent, pAttributes)) ? (INT)szContent.GetSize() : 0, m_szColumnsText.RemoveAt(nColumn), m_nColumnsWidth.RemoveAt(nColumn), m_nColumnsFormat.RemoveAt(nColumn); nItem < nItems; nItem++)
		{
			if (nColumn < GetParent()->ConvertText(szContent.GetAt(nItem), szItem)) szItem.RemoveAt(nColumn);
			szContent.SetAt(nItem, GetParent()->ConvertText(szItem));
		}
		for (nItem = 0; nItem < nItems; nItem++)
		{
			if ((pAttribute = pAttributes.GetAt(nItem)))
			{
				pAttribute->Adjust(nColumn, FALSE);
				continue;
			}
		}
		GetParent()->SetContent(szContent, pAttributes);
		RecalcLayout((m_bUpdate[0] = TRUE));
		return TRUE;
	}
	return FALSE;
}

INT CTextViewHeaderCtrl::GetColumnCount() CONST
{
	CTextViewLock  cLock(GetParent());

	return((INT)m_szColumnsText.GetSize());
}

BOOL CTextViewHeaderCtrl::SetTextIndents(WORD wLeft, WORD wRight, BOOL bRedraw)
{
	CTextViewLock  cLock(GetParent());

	if (wLeft != m_wTextIndent[0] || wRight != m_wTextIndent[1])
	{
		for (m_wTextIndent[0] = wLeft, m_wTextIndent[1] = wRight; bRedraw; )
		{
			RecalcLayout(TRUE);
			break;
		}
	}
	return TRUE;
}

DWORD CTextViewHeaderCtrl::GetTextIndents() CONST
{
	CTextViewLock  cLock(GetParent());

	return((DWORD)MAKELONG(m_wTextIndent[0], m_wTextIndent[1]));
}

BOOL CTextViewHeaderCtrl::SetTextSpacings(WORD wTop, WORD wBottom, BOOL bRedraw)
{
	CTextViewLock  cLock(GetParent());

	if (wTop != m_wTextSpacing[0] || wBottom != m_wTextSpacing[1])
	{
		for (m_wTextSpacing[0] = wTop, m_wTextSpacing[1] = wBottom; bRedraw; )
		{
			RecalcLayout(TRUE);
			break;
		}
	}
	return TRUE;
}

DWORD CTextViewHeaderCtrl::GetTextSpacings() CONST
{
	CTextViewLock  cLock(GetParent());

	return((DWORD)MAKELONG(m_wTextSpacing[0], m_wTextSpacing[1]));
}

VOID CTextViewHeaderCtrl::RecalcLayout(BOOL bContent)
{
	INT  nColumn;
	INT  nColumns;
	BOOL  bUpdate;
	CRect  rHeader;
	CSize  sizeHeader;
	TCHAR  szText[256];
	HD_ITEM  sColumnItem;
	CUIntArray  nWidths;
	CUIntArray  nFormats;
	CStringArray  szColumns;
	CTextViewLock  cLock(GetParent());

	if (!CThread::IsSameThread(this))
	{
		if (IsWindow(GetSafeHwnd())) Invalidate(!(m_bUpdate[1] = TRUE));
		return;
	}
	for (GetParent()->GetClientRect(rHeader), szColumns.Copy(m_szColumnsText), sizeHeader = CalcExtent(m_szColumnsText, nWidths), nFormats.Copy(m_nColumnsFormat); sizeHeader.cx > 0 && sizeHeader.cy > 0; )
	{
		for (nColumn = 0, nColumns = ((bUpdate = m_bUpdate[0] || m_bUpdate[1])) ? (INT)m_szColumnsText.GetSize() : 0, ZeroMemory(&sColumnItem, sizeof(sColumnItem)), sColumnItem.mask = HDI_TEXT | HDI_WIDTH | HDI_FORMAT, sColumnItem.pszText = szText, sColumnItem.cchTextMax = sizeof(szText) / sizeof(TCHAR), m_bUpdate[1] = FALSE; nColumn < nColumns; nColumn++)
		{
			_tcscpy_s(sColumnItem.pszText, sColumnItem.cchTextMax, m_szColumnsText.GetAt(nColumn));
			sColumnItem.cxy = m_nColumnsWidth.GetAt(nColumn);
			sColumnItem.cxy -= (nColumn > 0) ? m_nColumnsWidth.GetAt(nColumn - 1) : 0;
			sColumnItem.fmt = m_nColumnsFormat.GetAt(nColumn) | HDF_STRING;
			if ((nColumn >= GetItemCount() && InsertItem(nColumn, &sColumnItem) < 0) || (nColumn < GetItemCount() && !SetItem(nColumn, &sColumnItem))) break;
		}
		while (nColumn < GetItemCount() && nColumns > 0)
		{
			if (!DeleteItem(nColumn)) break;
			continue;
		}
		for (Invalidate(FALSE), MoveWindow(rHeader.left - m_nScrollPos, ((GetParent()->GetStyle() & (TVS_TOP | TVS_BOTTOM)) == TVS_BOTTOM) ? (rHeader.bottom - sizeHeader.cy) : rHeader.top, max(sizeHeader.cx, rHeader.Width() + (INT)m_nScrollPos), (GetStyle() & WS_VISIBLE) ? sizeHeader.cy : 0), m_bUpdate[0] = FALSE; bContent; )
		{
			for (GetParent()->RecalcContent(); bUpdate; )
			{
				GetParent()->RefreshContent();
				break;
			}
			Invalidate(FALSE);
			UpdateWindow();
			break;
		}
		return;
	}
	for (MoveWindow(rHeader.left - m_nScrollPos, ((GetParent()->GetStyle() & (TVS_TOP | TVS_BOTTOM)) == TVS_TOP) ? rHeader.top : rHeader.bottom, rHeader.Width() + m_nScrollPos, 0), m_bUpdate[0] = m_bUpdate[1] = FALSE; bContent; )
	{
		GetParent()->RecalcContent();
		break;
	}
}

INT CTextViewHeaderCtrl::EnumColumnLines(LPCTSTR pszColumn, CStringArray &szLines) CONST
{
	INT  nPos[2];
	CString  szColumn;

	for (szColumn = pszColumn, nPos[0] = 0, szLines.RemoveAll(); (nPos[1] = szColumn.Mid(nPos[0]).Find(EOL)) >= 0; nPos[0] += nPos[1] + 1)
	{
		szLines.Add(szColumn.Mid(nPos[0], nPos[1]));
		continue;
	}
	szLines.Add(szColumn.Mid(nPos[0]));
	return((INT)szLines.GetSize());
}

CSize CTextViewHeaderCtrl::CalcExtent(CONST CStringArray &szColumns, CUIntArray &nWidths) CONST
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CSize  size[2];
	CTextViewLock  cLock(GetParent());

	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), nWidths.RemoveAll(), size[0].cx = size[0].cy = 0; nColumn < nColumns; nColumn++)
	{
		for (nWidth = (size[1] = CalcColumnExtent(szColumns.GetAt(nColumn))).cx; (!nColumn && m_nColumnsWidth.GetSize() > 0 && nWidth < (INT)m_nColumnsWidth.GetAt(nColumn)) || (nColumn > 0 && nColumn < m_nColumnsWidth.GetSize() && nWidth < (INT)(m_nColumnsWidth.GetAt(nColumn) - m_nColumnsWidth.GetAt(nColumn - 1))); )
		{
			nWidth = (nColumn > 0) ? (m_nColumnsWidth.GetAt(nColumn) - m_nColumnsWidth.GetAt(nColumn - 1)) : m_nColumnsWidth.GetAt(nColumn);
			break;
		}
		nWidths.Add((nColumn > 0) ? (nWidths.GetAt(nColumn - 1) + nWidth) : nWidth);
		size[0].cx = size[0].cx + nWidth;
		size[0].cy = max(size[0].cy, size[1].cy);
	}
	return((szColumns.GetSize() == nWidths.GetSize()) ? size[0] : CSize(0, 0));
}

CSize CTextViewHeaderCtrl::CalcColumnExtent(LPCTSTR pszColumn) CONST
{
	CFont  *pOldFont;
	CSize  sizeColumn[2];
	CStringArray  szLines;
	CClientDC  cDC(NULL);
	CTextViewLock  cLock(GetParent());

	if ((pOldFont = cDC.SelectObject((CFont *)&m_cFont)))
	{
		for (EnumColumnLines(pszColumn, szLines), sizeColumn[0].cx = sizeColumn[0].cy = 0; szLines.GetSize() > 0; szLines.RemoveAt(0))
		{
			sizeColumn[1] = cDC.GetTextExtent(szLines.GetAt(0));
			sizeColumn[1].cx += m_wTextIndent[0] + m_wTextIndent[1];
			sizeColumn[1].cy += m_wTextSpacing[0] + m_wTextSpacing[1];
			sizeColumn[0].cx = max(sizeColumn[0].cx, sizeColumn[1].cx);
			sizeColumn[0].cy += sizeColumn[1].cy;
		}
		cDC.SelectObject(pOldFont);
		return sizeColumn[0];
	}
	return CSize(0, 0);
}

WORD CTextViewHeaderCtrl::CalcDefaultIndent() CONST
{
	INT  nIndent;
	CFont  *pOldFont;
	CClientDC  cDC(NULL);
	CTextViewLock  cLock(GetParent());

	if ((pOldFont = cDC.SelectObject((CFont *)&m_cFont)))
	{
		nIndent = GetSystemMetrics(SM_CXEDGE) + cDC.GetTextExtent(SPACE).cy / 4;
		cDC.SelectObject(pOldFont);
		return nIndent;
	}
	return 0;
}

WORD CTextViewHeaderCtrl::CalcDefaultSpacing() CONST
{
	return GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER);
}

CTextView *CTextViewHeaderCtrl::GetParent() CONST
{
	return m_pParentWnd;
}

LRESULT CTextViewHeaderCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	return((!GetParent()->OnHeaderMessage(message, wParam, lParam, &lResult)) ? CMFCHeaderCtrl::WindowProc(message, wParam, lParam) : lResult);
}

BEGIN_MESSAGE_MAP(CTextViewHeaderCtrl, CMFCHeaderCtrl)
	//{{AFX_MSG_MAP(CTextViewHeaderCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextViewHeaderCtrl message handlers

int CTextViewHeaderCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(GetParent());

	if (CMFCHeaderCtrl::OnCreate(lpCreateStruct) != -1)
	{
		m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent();
		m_wTextSpacing[0] = CalcDefaultSpacing();
		m_wTextSpacing[1] = m_wTextSpacing[0] + 1;
		return 0;
	}
	return -1;
}

BOOL CTextViewHeaderCtrl::OnEraseBkgnd(CDC *pDC)
{
	CTextViewLock  cLock(GetParent());

	UpdateWindow();
	return TRUE;
}

void CTextViewHeaderCtrl::OnPaint()
{
	CTextViewLock  cLock(GetParent());

	if (m_bUpdate[1])
	{
		ValidateRect((LPCRECT)NULL);
		RecalcLayout(TRUE);
		return;
	}
	CMFCHeaderCtrl::OnPaint();
}

void CTextViewHeaderCtrl::OnDrawItem(CDC *pDC, int iItem, CRect rect, BOOL bIsPressed, BOOL bIsHighlighted)
{
	INT  cx;
	INT  cy;
	UINT  nFlags;
	CRect  rItem;
	CRect  rBitmap;
	CFont  *pOldFont;
	TCHAR  szText[256];
	CPoint  ptImage;
	BITMAP  sBitmap;
	CString  szLine;
	HD_ITEM  sItem;
	CBitmap  *pBitmap;
	CImageList  *pImageList;
	CStringArray  szLines;
	CTextViewLock  cLock(GetParent());

	for (CMFCVisualManager::GetInstance()->OnDrawHeaderCtrlBorder(this, pDC, rect, bIsPressed, bIsHighlighted); iItem >= 0; )
	{
		for (ZeroMemory(&sItem, sizeof(sItem)), sItem.mask = HDI_FORMAT | HDI_BITMAP | HDI_TEXT | HDI_IMAGE, sItem.pszText = szText, sItem.cchTextMax = sizeof(szText) / sizeof(TCHAR); GetItem(iItem, &sItem); )
		{
			if ((sItem.fmt & HDF_IMAGE) && sItem.iImage >= 0)
			{
				if ((pImageList = GetImageList()) != (CImageList *)NULL)
				{
					if (ImageList_GetIconSize(*pImageList, &(cx = 0), &(cy = 0)))
					{
						ptImage = CPoint(rect.left + 1, (rect.top + rect.bottom - cy) / 2);
						ptImage.Offset((bIsPressed) ? 1 : 0, (bIsPressed) ? 1 : 0);
						pImageList->Draw(pDC, sItem.iImage, ptImage, ILD_NORMAL);
						rect.left += cx;
					}
				}
			}
			if ((sItem.fmt & (HDF_BITMAP | HDF_BITMAP_ON_RIGHT)) && sItem.hbm != (HBITMAP)NULL)
			{
				if ((pBitmap = CBitmap::FromHandle(sItem.hbm)) && pBitmap->GetBitmap(&sBitmap) > 0)
				{
					for (rBitmap = rect; (sItem.fmt & HDF_BITMAP_ON_RIGHT) != HDF_BITMAP_ON_RIGHT; )
					{
						rect.left = rBitmap.right = rBitmap.left + sBitmap.bmWidth + 1;
						rBitmap.left++;
					}
					if (sItem.fmt & HDF_BITMAP_ON_RIGHT)
					{
						rect.right = rBitmap.left = rBitmap.right - sBitmap.bmWidth - 1;
						rBitmap.right--;
					}
					rBitmap.top += max(0, (rBitmap.Height() - sBitmap.bmHeight) / 2);
					rBitmap.bottom = rBitmap.top + sBitmap.bmHeight;
					rBitmap.OffsetRect((bIsPressed) ? 1 : 0, (bIsPressed) ? 1 : 0);
					pDC->DrawState(rBitmap.TopLeft(), rBitmap.Size(), pBitmap, DSS_NORMAL);
				}
			}
			if ((sItem.fmt & HDF_STRING) && sItem.pszText != (LPTSTR)NULL)
			{
				if ((pOldFont = pDC->SelectObject(&m_cFont)) != (CFont *)NULL)
				{
					for (EnumColumnLines(sItem.pszText, szLines), rItem = rect, rItem.DeflateRect(m_wTextIndent[0], m_wTextSpacing[0], m_wTextIndent[1], m_wTextSpacing[1]), rItem.DeflateRect(0, (szLines.GetSize() > 1) ? ((rItem.Height() - (INT)szLines.GetSize()*pDC->GetTextExtent(SPACE).cy) / 2) : 0), nFlags = ((sItem.fmt & HDF_CENTER) ? DT_CENTER : 0) | ((sItem.fmt & HDF_RIGHT) ? DT_RIGHT : 0) | ((szLines.GetSize() > 1) ? DT_TOP : DT_VCENTER) | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX | DT_WORD_ELLIPSIS; szLines.GetSize() > 0; szLines.RemoveAt(0))
					{
						pDC->DrawText((szLine = szLines.GetAt(0)), (bIsPressed) ? CRect(rItem.left + 1, rItem.top + 1, rItem.right + 1, rItem.bottom + 1) : rItem, nFlags);
						rItem.top += pDC->GetTextExtent(szLine).cy;
					}
					pDC->SelectObject(pOldFont);
				}
			}
			break;
		}
		break;
	}
}

void CTextViewHeaderCtrl::OnDestroy()
{
	CTextViewLock  cLock(GetParent());

	m_szColumnsText.RemoveAll();
	m_nColumnsWidth.RemoveAll();
	m_nColumnsFormat.RemoveAll();
	CMFCHeaderCtrl::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTextViewContentCtrl

IMPLEMENT_DYNCREATE(CTextViewContentCtrl, CScrollView)

CTextViewContentCtrl::CTextViewContentCtrl() : CScrollView()
{
	CFontTools  cFontTools(&m_cFont);

	m_nActiveItem = -1;
	m_nActiveColumn = -1;
	m_nSortColumn = -1;
	m_nTextLimit = -1;
	m_bFocused = FALSE;
	m_bUpdate = FALSE;
	m_bBars[0] = FALSE;
	m_bBars[1] = FALSE;
	m_bScrollBars = FALSE;
	m_nScrollPos[0] = m_nScrollPos[1] = 0;
	m_wTextIndent[0] = m_wTextIndent[1] = 0;
	m_wTextSpacing[0] = m_wTextSpacing[1] = 0;
	m_sizeExtent.cx = m_sizeExtent.cy = 0;
	m_pHeaderCtrl = (CTextViewHeaderCtrl *)NULL;
	m_pBlinkThread = (CTextViewBlinkThread *)NULL;
	m_pParentWnd = (CTextView *)NULL;
}

BOOL CTextViewContentCtrl::Create(CTextView *pParentWnd, DWORD dwStyle, UINT nID)
{
	CCreateContext  cContext;

	for (cContext.m_pCurrentDoc = new CTextViewDocument; CScrollView::Create(AfxRegisterWndClass(CS_DBLCLKS | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(COLOR_WINDOW)), (LPCTSTR)NULL, dwStyle, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), nID, &cContext); )
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTextViewContentCtrl::Initialize(CTextView *pParentWnd, CTextViewHeaderCtrl *pHeaderCtrl)
{
	CTextViewLock  cLock(pParentWnd);

	m_pParentWnd = pParentWnd;
	m_pHeaderCtrl = pHeaderCtrl;
}

BOOL CTextViewContentCtrl::SetColumnsFont(CFont *pFont)
{
	LOGFONT  lfFont[2];
	CTextViewLock  cLock(GetParent());

	if (!m_cFont.GetSafeHandle() || !pFont->GetLogFont(&lfFont[0]) || !m_cFont.GetLogFont(&lfFont[1]) || memcmp(&lfFont[0], &lfFont[1], sizeof(LOGFONT)))
	{
		for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont[0]) > 0 && m_cFont.CreateFontIndirect(&lfFont[0]); )
		{
			m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent();
			m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing();
			RecalcContent();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}
BOOL CTextViewContentCtrl::SetColumnsFont(CONST LOGFONT *plfFont)
{
	CFont  cFont;

	return((cFont.CreateFontIndirect(plfFont) && SetColumnsFont(&cFont)) ? TRUE : FALSE);
}

BOOL CTextViewContentCtrl::GetColumnsFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return(GetColumnsFont(&lfFont) && pFont->CreateFontIndirect(&lfFont));
}
BOOL CTextViewContentCtrl::GetColumnsFont(LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(GetParent());

	return((m_cFont.GetSafeHandle() != (HGDIOBJ)NULL  &&  m_cFont.GetObject(sizeof(LOGFONT), plfFont) > 0) ? TRUE : FALSE);
}

BOOL CTextViewContentCtrl::SetColumnFont(INT nColumn, CFont *pFont, BOOL bRedraw)
{
	INT  nFont;
	INT  nFonts;
	LOGFONT  lfFont[2];
	CFont  *pColumnFont[2];
	CTextViewLock  cLock(GetParent());

	if (nColumn >= 0 && nColumn < m_pHeaderCtrl->GetColumnCount())
	{
		if ((pColumnFont[0] = (nColumn < m_pColumnsFont.GetSize()) ? (CFont *)m_pColumnsFont.GetAt(nColumn) : (CFont *)NULL))
		{
			if (pFont->GetLogFont(&lfFont[0]) > 0 && pColumnFont[0]->GetLogFont(&lfFont[1]) > 0)
			{
				if (memcmp(&lfFont[0], &lfFont[1], sizeof(LOGFONT)) != 0)
				{
					if ((pColumnFont[1] = new CFont) != (CFont *)NULL)
					{
						if (pColumnFont[1]->CreateFontIndirect(&lfFont[0]))
						{
							for (m_pColumnsFont.SetAtGrow(nColumn, pColumnFont[1]), m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent(), m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing(); bRedraw; )
							{
								RecalcContent();
								break;
							}
							delete pColumnFont[0];
							return TRUE;
						}
						delete pColumnFont[1];
					}
					return FALSE;
				}
				return TRUE;
			}
			return FALSE;
		}
		if (pFont->GetLogFont(&lfFont[0]) > 0)
		{
			if ((pColumnFont[1] = new CFont) != (CFont *)NULL)
			{
				if (pColumnFont[1]->CreateFontIndirect(&lfFont[0]))
				{
					for (m_pColumnsFont.SetAtGrow(nColumn, pColumnFont[1]), m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent(), m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing(); bRedraw; )
					{
						RecalcContent();
						break;
					}
					return TRUE;
				}
				delete pColumnFont[1];
			}
		}
		return FALSE;
	}
	if (nColumn < -1 && abs(nColumn) <= m_pColumnsFont.GetSize())
	{
		if ((pColumnFont[0] = (CFont *)m_pColumnsFont.GetAt(abs(nColumn) - 1)))
		{
			for (nFont = 0, nFonts = (INT)m_pColumnsFont.GetSize(), m_pColumnsFont.SetAt(abs(nColumn) - 1, (LPVOID)NULL); nFont < nFonts; nFont++)
			{
				if ((pColumnFont[1] = (CFont *)m_pColumnsFont.GetAt(nFont))) break;
				continue;
			}
			if (nFont == nFonts) m_pColumnsFont.RemoveAll();
			for (m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent(), m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing(); bRedraw; )
			{
				RecalcContent();
				break;
			}
			delete pColumnFont[0];
		}
		return TRUE;
	}
	if (nColumn == -1)
	{
		for (nFont = 0, nFonts = (INT)m_pColumnsFont.GetSize(); nFont < nFonts; nFont++)
		{
			if ((pColumnFont[0] = (CFont *)m_pColumnsFont.GetAt(nFont))) delete pColumnFont[0];
			m_pColumnsFont.RemoveAt(nFont);
			nFonts--;
			nFont--;
		}
		for (m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent(), m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing(); bRedraw; )
		{
			RecalcContent();
			break;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTextViewContentCtrl::SetColumnFont(INT nColumn, CONST LOGFONT *plfFont, BOOL bRedraw)
{
	CFont  cFont;

	return((cFont.CreateFontIndirect(plfFont) && SetColumnFont(nColumn, &cFont, bRedraw)) ? TRUE : FALSE);
}
BOOL CTextViewContentCtrl::SetColumnFont(INT nItem, INT nColumn, CFont *pFont, BOOL bRedraw)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0 && SetColumnFont(nItem, nColumn, &lfFont, bRedraw)) ? TRUE : FALSE);
}
BOOL CTextViewContentCtrl::SetColumnFont(INT nItem, INT nColumn, CONST LOGFONT *plfFont, BOOL bRedraw)
{
	LOGFONT  lfFont;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount())
	{
		if ((pAttribute = m_pContentTextAttributes.GetAt(nItem)))
		{
			if (!pAttribute->GetColumnFont(nColumn, &lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)) != 0)
			{
				for (pAttribute->SetColumnFont(nColumn, plfFont), m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent(), m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing(); bRedraw; )
				{
					RecalcContent();
					break;
				}
			}
			return TRUE;
		}
		if ((pAttribute = new CTextViewAttribute))
		{
			for (pAttribute->SetColumnFont(nColumn, plfFont), m_pContentTextAttributes.SetAtGrow(nItem, pAttribute), m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent(), m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing(); bRedraw; )
			{
				RecalcContent();
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTextViewContentCtrl::GetColumnFont(INT nColumn, CFont *pFont) CONST
{
	LOGFONT  lfFont;
	CFont  *pColumnFont;
	CTextViewLock  cLock(GetParent());

	if (nColumn >= 0 && nColumn < m_pColumnsFont.GetSize())
	{
		if ((pColumnFont = (CFont *)m_pColumnsFont.GetAt(nColumn)) && pColumnFont->GetLogFont(&lfFont) > 0)
		{
			for (pFont->DeleteObject(); pFont->CreateFontIndirect(&lfFont); ) return TRUE;
			return FALSE;
		}
		return GetColumnsFont(pFont);
	}
	return FALSE;
}
BOOL CTextViewContentCtrl::GetColumnFont(INT nColumn, LOGFONT *plfFont) CONST
{
	CFont  cFont;

	return((GetColumnFont(nColumn, &cFont) && cFont.GetLogFont(plfFont) > 0) ? TRUE : FALSE);
}
BOOL CTextViewContentCtrl::GetColumnFont(INT nItem, INT nColumn, CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetColumnFont(nItem, nColumn, &lfFont) && pFont->CreateFontIndirect(&lfFont)) ? TRUE : FALSE);
}
BOOL CTextViewContentCtrl::GetColumnFont(INT nItem, INT nColumn, LOGFONT *plfFont) CONST
{
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	return((nItem >= 0 && nItem < GetTextCount()) ? (((pAttribute = m_pContentTextAttributes.GetAt(nItem)) && pAttribute->GetColumnFont(nColumn, plfFont)) || GetColumnFont(nColumn, plfFont)) : FALSE);
}

BOOL CTextViewContentCtrl::SetColumnFormat(INT nColumn, UINT nFormat, BOOL bRedraw)
{
	CTextViewLock  cLock(GetParent());

	if (nColumn >= 0)
	{
		if (nColumn < m_bColumnsFormat.GetSize() && nFormat == (UINT)-1)
		{
			for (m_nColumnsFormat.InsertAt(nColumn, 0, 1), m_bColumnsFormat.InsertAt(nColumn, FALSE, 1); bRedraw; )
			{
				RecalcContent();
				break;
			}
			return TRUE;
		}
		if (nColumn >= m_bColumnsFormat.GetSize() || !m_bColumnsFormat.GetAt(nColumn) || m_nColumnsFormat.GetAt(nColumn) != nFormat)
		{
			for (m_nColumnsFormat.SetAtGrow(nColumn, (nFormat != (UINT)-1) ? nFormat : 0), m_bColumnsFormat.SetAtGrow(nColumn, (nFormat != (UINT)-1) ? TRUE : FALSE); bRedraw; )
			{
				RecalcContent();
				break;
			}
		}
		return TRUE;
	}
	if (nColumn < -1 && m_bColumnsFormat.GetSize() > abs(nColumn) - 1)
	{
		for (m_nColumnsFormat.RemoveAt(abs(nColumn) - 1), m_bColumnsFormat.RemoveAt(abs(nColumn) - 1); bRedraw; )
		{
			RecalcContent();
			break;
		}
		return TRUE;
	}
	if (nColumn == -1)
	{
		if (m_bColumnsFormat.GetSize() > 0)
		{
			for (m_nColumnsFormat.RemoveAll(), m_bColumnsFormat.RemoveAll(); bRedraw; )
			{
				RecalcContent();
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTextViewContentCtrl::SetColumnFormat(INT nItem, INT nColumn, UINT nFormat, BOOL bRedraw)
{
	UINT  nColumnFormat;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount())
	{
		if ((pAttribute = m_pContentTextAttributes.GetAt(nItem)))
		{
			if (!pAttribute->GetColumnFormat(nColumn, nColumnFormat) || nColumnFormat != nFormat)
			{
				for (pAttribute->SetColumnFormat(nColumn, nFormat); bRedraw; )
				{
					RecalcContent();
					break;
				}
			}
			return TRUE;
		}
		if ((pAttribute = new CTextViewAttribute))
		{
			for (pAttribute->SetColumnFormat(nColumn, nFormat), m_pContentTextAttributes.SetAtGrow(nItem, pAttribute); bRedraw; )
			{
				RecalcContent();
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

UINT CTextViewContentCtrl::GetColumnFormat(INT nColumn) CONST
{
	CTextViewLock  cLock(GetParent());

	return((nColumn < m_bColumnsFormat.GetSize() && m_bColumnsFormat.GetAt(nColumn)) ? m_nColumnsFormat.GetAt(nColumn) : (DT_LEFT | DT_NOPREFIX | ((m_pHeaderCtrl->GetColumnCount() > 0) ? DT_WORDBREAK : DT_END_ELLIPSIS)));
}
UINT CTextViewContentCtrl::GetColumnFormat(INT nItem, INT nColumn) CONST
{
	UINT  nFormat;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	return(((pAttribute = m_pContentTextAttributes.GetAt(nItem)) && pAttribute->GetColumnFormat(nColumn, nFormat)) ? nFormat : GetColumnFormat(nColumn));
}

BOOL CTextViewContentCtrl::SetColumnColor(INT nColumn, COLORREF nColor, BOOL bRedraw)
{
	CTextViewLock  cLock(GetParent());

	if (nColumn >= 0)
	{
		if (nColumn < m_bColumnsColor.GetSize() && nColor == (COLORREF)-1)
		{
			for (m_nColumnsColor.InsertAt(nColumn, 0, 1), m_bColumnsColor.InsertAt(nColumn, FALSE, 1); bRedraw; )
			{
				DrawContent();
				break;
			}
			return TRUE;
		}
		if (nColumn >= m_bColumnsColor.GetSize() || !m_bColumnsColor.GetAt(nColumn) || m_nColumnsColor.GetAt(nColumn) != nColor)
		{
			for (m_nColumnsColor.SetAtGrow(nColumn, (nColor != (COLORREF)-1) ? nColor : 0), m_bColumnsColor.SetAtGrow(nColumn, (nColor != (COLORREF)-1) ? TRUE : FALSE); bRedraw; )
			{
				DrawContent();
				break;
			}
		}
		return TRUE;
	}
	if (nColumn < -1 && m_bColumnsColor.GetSize() > abs(nColumn) - 1)
	{
		for (m_nColumnsColor.RemoveAt(abs(nColumn) - 1), m_bColumnsColor.RemoveAt(abs(nColumn) - 1); bRedraw; )
		{
			DrawContent();
			break;
		}
		return TRUE;
	}
	if (nColumn == -1)
	{
		if (m_bColumnsColor.GetSize() > 0)
		{
			for (m_nColumnsColor.RemoveAll(), m_bColumnsColor.RemoveAll(); bRedraw; )
			{
				DrawContent();
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTextViewContentCtrl::SetColumnColor(INT nItem, INT nColumn, COLORREF nColor, BOOL bRedraw)
{
	COLORREF  nColumnColor;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount())
	{
		if ((pAttribute = m_pContentTextAttributes.GetAt(nItem)))
		{
			if (!pAttribute->GetColumnColor(nColumn, nColumnColor) || nColumnColor != nColor)
			{
				for (pAttribute->SetColumnColor(nColumn, nColor); bRedraw; )
				{
					DrawContent();
					break;
				}
			}
			return TRUE;
		}
		if ((pAttribute = new CTextViewAttribute))
		{
			for (pAttribute->SetColumnColor(nColumn, nColor), m_pContentTextAttributes.SetAtGrow(nItem, pAttribute); bRedraw; )
			{
				DrawContent();
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

COLORREF CTextViewContentCtrl::GetColumnColor(INT nColumn) CONST
{
	CTextViewLock  cLock(GetParent());

	return((nColumn < m_bColumnsColor.GetSize() && m_bColumnsColor.GetAt(nColumn)) ? m_nColumnsColor.GetAt(nColumn) : GetSysColor(COLOR_WINDOWTEXT));
}
COLORREF CTextViewContentCtrl::GetColumnColor(INT nItem, INT nColumn) CONST
{
	COLORREF  nColor;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	return(((pAttribute = m_pContentTextAttributes.GetAt(nItem)) && pAttribute->GetColumnColor(nColumn, nColor)) ? nColor : GetColumnColor(nColumn));
}

BOOL CTextViewContentCtrl::SetContent(CONST CStringArray &szContent, CONST CTextViewAttributes &pAttributes)
{
	INT  nItem;
	INT  nItems;
	CTextViewLock  cLock(GetParent());

	for (nItem = 0, nItems = (INT)szContent.GetSize(); nItem < nItems; nItem++)
	{
		if ((nItem < GetTextCount() && SetText(nItem, szContent.GetAt(nItem), pAttributes.GetAt(nItem), FALSE)) || (nItem >= GetTextCount() && AddText(szContent.GetAt(nItem), pAttributes.GetAt(nItem), FALSE) >= 0)) continue;
		break;
	}
	while (nItem < GetTextCount())
	{
		if (DeleteText(nItem, FALSE)) continue;
		break;
	}
	RecalcContent();
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTextViewContentCtrl::GetContent(CStringArray &szContent, CTextViewAttributes &pAttributes) CONST
{
	CTextViewLock  cLock(GetParent());

	szContent.Copy(m_szContentText);
	return(pAttributes.Copy(&m_pContentTextAttributes));
}

INT CTextViewContentCtrl::AddText(LPCTSTR pszText, CONST CTextViewAttribute *pAttribute, BOOL bRedraw)
{
	INT  nIndex;
	CTextViewLock  cLock(GetParent());

	return((InsertText((nIndex = GetTextCount()), pszText, pAttribute, bRedraw)) ? nIndex : -1);
}

BOOL CTextViewContentCtrl::InsertText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute, BOOL bRedraw)
{
	INT  nLine;
	INT  nLines;
	INT  nHeight;
	INT  nColumn;
	INT  nColumns;
	BOOL  bBlinking;
	CTextViewAttribute  *pTextAttribute;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem <= GetTextCount())
	{
		if (((pTextAttribute = (pAttribute) ? new CTextViewAttribute : (CTextViewAttribute *)NULL) && pTextAttribute->Copy(pAttribute)) || !pAttribute)
		{
			for (nLine = nItem + 1, nLines = GetTextCount() + 1, nHeight = (IsWindow(GetSafeHwnd())) ? CalcTextLines(pszText, pAttribute) : 0, m_szContentText.InsertAt(nItem, pszText), m_nContentTextPos.InsertAt(nItem, (nItem > 0) ? (m_nContentTextPos.GetAt(nItem - 1) + nHeight) : nHeight), m_pContentTextAttributes.InsertAt(nItem, pTextAttribute), m_nActiveItem = (m_nActiveItem >= 0 && m_nActiveItem >= nItem) ? (m_nActiveItem + 1) : m_nActiveItem; nLine < nLines; nLine++)
			{
				m_nContentTextPos.SetAt(nLine, m_nContentTextPos.GetAt(nLine) + nHeight);
				continue;
			}
			for (SetTextLimit(m_nTextLimit, FALSE); bRedraw; )
			{
				RecalcLayout();
				break;
			}
			for (nColumn = 0, nColumns = (pTextAttribute) ? m_pHeaderCtrl->GetColumnCount() : 0; nColumn < nColumns; nColumn++)
			{
				if (!nColumn  &&  pTextAttribute->GetColumnBlinking(-1, bBlinking) && StartTextBlinking(nItem))
				{
					nColumn = nColumns;
					break;
				}
				if (pTextAttribute->GetColumnBlinking(nColumn, bBlinking))
				{
					StartTextBlinking(nItem, nColumn);
					continue;
				}
			}
			return((nColumn == nColumns) ? TRUE : FALSE);
		}
		delete pTextAttribute;
	}
	return FALSE;
}

BOOL CTextViewContentCtrl::SetText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute, BOOL bRedraw)
{
	INT  nLine;
	INT  nLines;
	INT  nHeight;
	INT  nColumn;
	INT  nColumns;
	BOOL  bBlinking;
	CTextViewAttribute  *pTextAttribute;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount())
	{
		if (((pTextAttribute = (!(pTextAttribute = m_pContentTextAttributes.GetAt(nItem))) ? ((pAttribute) ? new CTextViewAttribute : (CTextViewAttribute *)NULL) : pTextAttribute) && pAttribute != (CONST CTextViewAttribute *) NULL  &&  pTextAttribute->Copy(pAttribute)) || !pAttribute)
		{
			for (nLine = nItem + 1, nLines = GetTextCount(), nHeight = (IsWindow(GetSafeHwnd())) ? ((nItem > 0) ? (CalcTextLines(pszText, pAttribute) - m_nContentTextPos.GetAt(nItem) + m_nContentTextPos.GetAt(nItem - 1)) : (CalcTextLines(pszText, pAttribute) - m_nContentTextPos.GetAt(nItem))) : 0, m_szContentText.SetAt(nItem, pszText), m_nContentTextPos.SetAt(nItem, m_nContentTextPos.GetAt(nItem) + nHeight), m_pContentTextAttributes.SetAt(nItem, pTextAttribute); nLine < nLines && nHeight != 0; nLine++)
			{
				m_nContentTextPos.SetAt(nLine, m_nContentTextPos.GetAt(nLine) + nHeight);
				continue;
			}
			for (SetTextLimit(m_nTextLimit, FALSE); bRedraw; )
			{
				RecalcLayout();
				break;
			}
			for (nColumn = 0, nColumns = (pTextAttribute) ? m_pHeaderCtrl->GetColumnCount() : 0; nColumn < nColumns; nColumn++)
			{
				if (!nColumn  &&  pTextAttribute->GetColumnBlinking(-1, bBlinking) && StartTextBlinking(nItem))
				{
					nColumn = nColumns;
					break;
				}
				if (pTextAttribute->GetColumnBlinking(nColumn, bBlinking))
				{
					StartTextBlinking(nItem, nColumn);
					continue;
				}
			}
			return((nColumn == nColumns) ? TRUE : FALSE);
		}
		if (!m_pContentTextAttributes.GetAt(nItem) && pAttribute != (CONST CTextViewAttribute *) NULL) delete pTextAttribute;
	}
	return FALSE;
}
BOOL CTextViewContentCtrl::SetText(INT nItem, INT nColumn, LPCTSTR pszText, BOOL bRedraw)
{
	INT  dy;
	INT  nLine;
	INT  nLines;
	CStringArray  szColumns;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount() && nColumn >= 0 && nColumn < m_pHeaderCtrl->GetColumnCount())
	{
		for (nLine = nItem, nLines = GetTextCount(), ConvertText(m_szContentText.GetAt(nItem), szColumns), szColumns.SetAtGrow(nColumn, pszText), m_szContentText.SetAt(nItem, ConvertText(szColumns)), dy = (nItem > 0) ? (CalcTextLines(m_szContentText.GetAt(nItem), m_pContentTextAttributes.GetAt(nItem)) - m_nContentTextPos.GetAt(nItem) + m_nContentTextPos.GetAt(nItem - 1)) : (CalcTextLines(m_szContentText.GetAt(nItem), m_pContentTextAttributes.GetAt(nItem)) - m_nContentTextPos.GetAt(nItem)); nLine < nLines && dy != 0; nLine++)
		{
			m_nContentTextPos.SetAt(nLine, m_nContentTextPos.GetAt(nLine) + dy);
			continue;
		}
		if (bRedraw  &&  !dy)
		{
			DrawText(nItem, nColumn, pszText);
			return TRUE;
		}
		if (bRedraw) RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTextViewContentCtrl::GetText(INT nItem, CString &szText, CTextViewAttribute *pAttribute) CONST
{
	CTextViewAttribute  *pTextAttribute;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount())
	{
		for (szText = m_szContentText.GetAt(nItem); (pTextAttribute = (pAttribute != (CONST CTextViewAttribute *) NULL) ? m_pContentTextAttributes.GetAt(nItem) : (CTextViewAttribute *)NULL) != (CONST CTextViewAttribute *) NULL; ) return pAttribute->Copy(pTextAttribute);
		return TRUE;
	}
	return FALSE;
}
BOOL CTextViewContentCtrl::GetText(INT nItem, INT nColumn, CString &szText) CONST
{
	CStringArray  szColumns;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount() && nColumn >= 0 && nColumn < m_pHeaderCtrl->GetColumnCount())
	{
		szText = (ConvertText(m_szContentText.GetAt(nItem), szColumns) > nColumn) ? (LPCTSTR)szColumns.GetAt(nColumn) : EMPTYSTRING;
		return TRUE;
	}
	return FALSE;
}

CString CTextViewContentCtrl::ConvertText(CONST CStringArray &szColumns) CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szText;

	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		szText += (nColumn > 0) ? (GetColumnDelimiter() + szColumns.GetAt(nColumn)) : szColumns.GetAt(nColumn);
		continue;
	}
	return szText;
}
INT CTextViewContentCtrl::ConvertText(LPCTSTR pszText, CStringArray &szColumns) CONST
{
	INT  nPos[2];
	INT  nLength;
	CString  szText;

	for (nPos[0] = 0, nLength = lstrlen(pszText), szColumns.RemoveAll(); nPos[0] <= nLength; nPos[0] += ++nPos[1])
	{
		if ((nPos[1] = (INT)_tcscspn((szText = pszText + nPos[0]), CString(GetColumnDelimiter()))) < nLength - nPos[0])
		{
			szColumns.Add((nPos[1] > 0) ? szText.Left(nPos[1]) : EMPTYSTRING);
			continue;
		}
		szColumns.Add(szText);
		break;
	}
	return((INT)szColumns.GetSize());
}

INT CTextViewContentCtrl::FindText(LPCTSTR pszText, INT nColumn, BOOL bExist) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nMinItem;
	INT  nMaxItem;
	INT  nSortColumn;
	UINT  nSortOrder;
	CString  szText;
	CStringArray  szItems;
	CTextViewLock  cLock(GetParent());

	if ((nSortOrder = GetParent()->GetStyle() & (TVS_SORTASCENDING | TVS_SORTDESCENDING)))
	{
		for (nMinItem = 0, nMaxItem = (INT)m_szContentText.GetSize(), nItem = (nMinItem + nMaxItem) / 2, nSortColumn = (nColumn < 0 || m_nSortColumn == nColumn) ? m_nSortColumn : -1, szText = (nSortColumn >= 0) ? ((ConvertText(pszText, szItems) > nSortColumn) ? (LPCTSTR)szItems.GetAt(nSortColumn) : EMPTYSTRING) : pszText; nMinItem < nMaxItem; nItem = (nMinItem + nMaxItem) / 2)
		{
			if (((nSortColumn < 0 && m_szContentText.GetAt(nItem) == szText) || (nSortColumn >= 0 && (ConvertText(m_szContentText.GetAt(nItem), szItems) > nSortColumn  &&  szItems.GetAt(nSortColumn) == szText))) && bExist) break;
			if (((nSortOrder & TVS_SORTASCENDING) && ((nSortColumn < 0 && m_szContentText.GetAt(nItem).Compare(szText) <= 0) || (nSortColumn >= 0 && (szItems.GetSize() <= nSortColumn || szItems.GetAt(nSortColumn).Compare(szText) <= 0)))) || ((nSortOrder & TVS_SORTDESCENDING) && ((nSortColumn < 0 && m_szContentText.GetAt(nItem).Compare(szText) >= 0) || (nSortColumn >= 0 && (szItems.GetSize() > nSortColumn  &&  szItems.GetAt(nSortColumn).Compare(szText) >= 0)))))
			{
				nMinItem = nItem + 1;
				continue;
			}
			nMaxItem = nItem;
		}
		return((bExist) ? ((nMaxItem > 0 && ((nSortColumn < 0 && m_szContentText.GetAt(nItem) == szText) || (nSortColumn >= 0 && (szItems.GetSize() > nSortColumn  &&  szItems.GetAt(nSortColumn) == szText)))) ? nItem : -1) : nItem);
	}
	for (nItem = 0, nItems = (bExist) ? (INT)m_szContentText.GetSize() : 0; nItem < nItems; nItem++)
	{
		if ((nColumn < 0 && m_szContentText.GetAt(nItem) == pszText) || (nColumn >= 0 && (ConvertText(m_szContentText.GetAt(nItem), szItems) > nColumn  &&  szItems.GetAt(nColumn) == pszText))) break;
		continue;
	}
	return((!bExist) ? (INT)m_szContentText.GetSize() : nItem);
}

BOOL CTextViewContentCtrl::FindTextFromPoint(CPoint point, INT &nItem, INT &nColumn, BOOL bExist) CONST
{
	INT  nIndex[2];
	INT  nLimit[2];
	CRect  rText[1];
	CTextViewLock  cLock(GetParent());

	for (nIndex[0] = FindFirstVisibleText(), nLimit[0] = FindLastVisibleText(); nIndex[0] >= 0 && nIndex[0] <= nLimit[0]; nIndex[0]++)
	{
		rText[0] = CalcTextRect(nIndex[0]);
		rText[0].InflateRect(m_wTextIndent[0], 0, 0, 0);
		rText[0].InflateRect(0, m_wTextSpacing[0], 0, 0);
		rText[0].InflateRect(0, 0, m_wTextIndent[1], 0);
		rText[0].InflateRect(0, 0, 0, m_wTextSpacing[1]);
		if (rText[0].PtInRect(point)) break;
	}
	if (nIndex[0] >= 0 && nIndex[0] <= nLimit[0])
	{
		for (nIndex[1] = 0, nLimit[1] = m_pHeaderCtrl->GetColumnCount(); nIndex[1] < nLimit[1]; nIndex[1]++)
		{
			if ((!nIndex[1] && point.x <= (INT)(m_pHeaderCtrl->m_nColumnsWidth.GetAt(0) - m_nScrollPos[0])) || (nIndex[1] > 0 && point.x > (INT)(m_pHeaderCtrl->m_nColumnsWidth.GetAt(nIndex[1] - 1) - m_nScrollPos[0]) && point.x <= (INT)(m_pHeaderCtrl->m_nColumnsWidth.GetAt(nIndex[1]) - m_nScrollPos[0]))) break;
			continue;
		}
		nItem = (bExist) ? min(nIndex[0], GetTextCount() - 1) : nIndex[0];
		nColumn = (bExist) ? min(nIndex[1], m_pHeaderCtrl->GetColumnCount() - 1) : nIndex[1];
		return TRUE;
	}
	nItem = nColumn = -1;
	return FALSE;
}
INT CTextViewContentCtrl::FindTextFromPoint(CPoint point, BOOL bExist) CONST
{
	INT  nItem;
	INT  nColumn;

	return((FindTextFromPoint(point, nItem, nColumn, bExist)) ? nItem : -1);
}

INT CTextViewContentCtrl::FindFirstVisibleText() CONST
{
	INT  nItem;
	INT  nItems;
	CRect  rContent;
	CTextViewLock  cLock(GetParent());

	for (nItem = 0, nItems = (INT)m_szContentText.GetSize(), GetClientRect(rContent); nItem < nItems; nItem++)
	{
		if (rContent.top <= (INT)(m_nContentTextPos.GetAt(nItem) - m_nScrollPos[1])) break;
		continue;
	}
	return nItem;
}

INT CTextViewContentCtrl::FindLastVisibleText() CONST
{
	INT  nItem;
	CRect  rContent;
	CTextViewLock  cLock(GetParent());

	for (nItem = (INT)m_szContentText.GetSize() - 1, GetClientRect(rContent); nItem > 0; nItem--)
	{
		if (rContent.bottom >= (INT)(m_nContentTextPos.GetAt(nItem - 1) - m_nScrollPos[1])) break;
		continue;
	}
	return nItem;
}

BOOL CTextViewContentCtrl::DeleteText(INT nItem, BOOL bRedraw)
{
	INT  nLine;
	INT  nLines;
	INT  nHeight;
	CTextViewAttribute  *pTextAttribute;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount())
	{
		for (nLine = nItem, nLines = GetTextCount() - 1, nHeight = (nItem > 0) ? (m_nContentTextPos.GetAt(nItem) - m_nContentTextPos.GetAt(nItem - 1)) : m_nContentTextPos.GetAt(nItem), StopTextBlinking(nItem), m_szContentText.RemoveAt(nItem), m_nContentTextPos.RemoveAt(nItem), pTextAttribute = m_pContentTextAttributes.GetAt(nItem), m_pContentTextAttributes.RemoveAt(nItem), m_nActiveItem = (m_nActiveItem >= 0 && m_nActiveItem >= nItem) ? ((m_nActiveItem > nItem) ? (m_nActiveItem - 1) : -1) : m_nActiveItem, m_nActiveColumn = (m_nActiveItem >= 0) ? m_nActiveColumn : -1; nLine < nLines; nLine++)
		{
			m_nContentTextPos.SetAt(nLine, m_nContentTextPos.GetAt(nLine) - nHeight);
			continue;
		}
		if (bRedraw) RecalcLayout();
		delete pTextAttribute;
		return TRUE;
	}
	return FALSE;
}

BOOL CTextViewContentCtrl::DeleteAllText(BOOL bRedraw)
{
	CTextViewLock  cLock(GetParent());

	if (m_szContentText.GetSize() > 0)
	{
		for (m_szContentText.RemoveAll(), m_nContentTextPos.RemoveAll(), m_pContentTextAttributes.RemoveAll(), m_nActiveItem = m_nActiveColumn = -1; bRedraw; )
		{
			RecalcLayout();
			break;
		}
	}
	return TRUE;
}

INT CTextViewContentCtrl::GetTextCount() CONST
{
	CTextViewLock  cLock(GetParent());

	return((INT)m_szContentText.GetSize());
}

BOOL CTextViewContentCtrl::SetCurText(INT nItem, INT nColumn)
{
	CTextViewLock  cLock(GetParent());

	if (nItem < GetTextCount() && nColumn < m_pHeaderCtrl->GetColumnCount())
	{
		if (m_nActiveItem != nItem || m_nActiveColumn != nColumn)
		{
			m_nActiveColumn = (nItem >= 0) ? nColumn : -1;
			m_nActiveItem = nItem;
			ScrollTo(nItem);
			DrawContent();
		}
		return TRUE;
	}
	return FALSE;
}

INT CTextViewContentCtrl::GetCurText() CONST
{
	return m_nActiveItem;
}

INT CTextViewContentCtrl::SearchText(LPCTSTR pszText, INT nColumn) CONST
{
	return FindText(pszText, nColumn);
}

BOOL CTextViewContentCtrl::StartTextBlinking(INT nItem, INT nColumn)
{
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	if ((pAttribute = (!m_pContentTextAttributes.GetAt(nItem)) ? new CTextViewAttribute : m_pContentTextAttributes.GetAt(nItem)))
	{
		m_pContentTextAttributes.SetAtGrow(nItem, pAttribute);
		pAttribute->SetColumnBlinking(nColumn, TRUE);
		return m_pBlinkThread->Start();
	}
	return FALSE;
}

BOOL CTextViewContentCtrl::StopTextBlinking(INT nItem, INT nColumn)
{
	BOOL  bBlinking;
	CString  szItem;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(GetParent());

	if ((pAttribute = m_pContentTextAttributes.GetAt(nItem)) && pAttribute->GetColumnBlinking(nColumn, bBlinking))
	{
		for (pAttribute->SetColumnBlinking(nColumn, FALSE); GetText(nItem, szItem); )
		{
			DrawText(nItem, szItem);
			break;
		}
		return m_pBlinkThread->Stop();
	}
	return FALSE;
}

BOOL CTextViewContentCtrl::SetTextLimit(INT nLimit, BOOL bRedraw)
{
	INT  nLine;
	INT  nLines;
	CTextViewLock  cLock(GetParent());

	for (nLine = m_nTextLimit = nLimit, nLines = (nLimit >= 0) ? GetTextCount() : nLine; nLine < nLines; nLine++)
	{
		if (!DeleteText(nLine, FALSE)) break;
		nLines--;
		nLine--;
	}
	if (bRedraw) RecalcLayout();
	return((nLine >= nLines) ? TRUE : FALSE);
}

INT CTextViewContentCtrl::GetTextLimit() CONST
{
	return m_nTextLimit;
}

BOOL CTextViewContentCtrl::SetTextIndents(WORD wLeft, WORD wRight, BOOL bRedraw)
{
	CTextViewLock  cLock(GetParent());

	if (wLeft != m_wTextIndent[0] || wRight != m_wTextIndent[1])
	{
		for (m_wTextIndent[0] = wLeft, m_wTextIndent[1] = wRight; bRedraw; )
		{
			RecalcContent();
			break;
		}
	}
	return TRUE;
}

DWORD CTextViewContentCtrl::GetTextIndents() CONST
{
	CTextViewLock  cLock(GetParent());

	return((DWORD)MAKELONG(m_wTextIndent[0], m_wTextIndent[1]));
}

BOOL CTextViewContentCtrl::SetTextSpacings(WORD wTop, WORD wBottom, BOOL bRedraw)
{
	CTextViewLock  cLock(GetParent());

	if (wTop != m_wTextSpacing[0] || wBottom != m_wTextSpacing[1])
	{
		for (m_wTextSpacing[0] = wTop, m_wTextSpacing[1] = wBottom; bRedraw; )
		{
			RecalcContent();
			break;
		}
	}
	return TRUE;
}

DWORD CTextViewContentCtrl::GetTextSpacings() CONST
{
	CTextViewLock  cLock(GetParent());

	return((DWORD)MAKELONG(m_wTextSpacing[0], m_wTextSpacing[1]));
}

BOOL CTextViewContentCtrl::SetTextSortOrder(UINT nOrder, INT nColumn)
{
	INT  nItem;
	INT  nItems;
	CStringArray  szText;
	CTextViewAttributes  pAttributes;
	CTextViewLock  cLock(GetParent());

	if ((nOrder == TVS_SORTASCENDING || nOrder == TVS_SORTDESCENDING || !nOrder) && nColumn >= -1 && nColumn < m_pHeaderCtrl->GetColumnCount())
	{
		if (((GetParent()->GetStyle() & nOrder) == nOrder  &&  m_nSortColumn == nColumn) || !nOrder)
		{
			GetParent()->ModifyStyle(TVS_SORTASCENDING | TVS_SORTDESCENDING, nOrder);
			return TRUE;
		}
		for (nItem = 0, nItems = GetTextCount(), szText.Copy(m_szContentText), pAttributes.Copy(&m_pContentTextAttributes), m_nSortColumn = nColumn, ModifyStyle(TVS_SORTASCENDING | TVS_SORTDESCENDING, nOrder), DeleteAllText(FALSE); nItem < nItems; nItem++)
		{
			if (!InsertText(FindText(szText.GetAt(nItem), nColumn, FALSE), szText.GetAt(nItem), pAttributes.GetAt(nItem), FALSE)) break;
			continue;
		}
		RecalcLayout();
		return((nItem == nItems) ? TRUE : FALSE);
	}
	return FALSE;
}

UINT CTextViewContentCtrl::GetTextSortOrder() CONST
{
	CTextViewLock  cLock(GetParent());

	return(GetParent()->GetStyle() & (TVS_SORTASCENDING | TVS_SORTDESCENDING));
}

BOOL CTextViewContentCtrl::ScrollToTop()
{
	return ScrollTo(0);
}

BOOL CTextViewContentCtrl::ScrollTo(INT nItem)
{
	CRect  rContent;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < GetTextCount())
	{
		for (GetClientRect(rContent); (!nItem && m_nScrollPos[1] > 0) || (nItem > 0 && m_nScrollPos[1] > m_nContentTextPos.GetAt(nItem - 1)); )
		{
			m_nScrollPos[1] = (nItem > 0) ? min(m_nContentTextPos.GetAt(nItem - 1), m_nContentTextPos.GetAt(m_nContentTextPos.GetUpperBound()) - rContent.Height() + 1) : 0;
			RecalcLayout();
			return TRUE;
		}
		if (m_nContentTextPos.GetSize() > 0 && m_nScrollPos[1] + rContent.Height() <= m_nContentTextPos.GetAt(nItem))
		{
			m_nScrollPos[1] += m_nContentTextPos.GetAt(nItem) - m_nScrollPos[1] - rContent.Height() + 1;
			RecalcLayout();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTextViewContentCtrl::ScrollToBottom()
{
	return ScrollTo(GetTextCount() - 1);
}

VOID CTextViewContentCtrl::SetScrollInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CTextViewLock  cLock(GetParent());

	if (memcmp(&m_sScrollInfo[0], pHorzScrollInfo, sizeof(SCROLLINFO)) != 0 || memcmp(&m_sScrollInfo[1], pVertScrollInfo, sizeof(SCROLLINFO)) != 0)
	{
		CopyMemory((LPVOID)&m_sScrollInfo[0], pHorzScrollInfo, sizeof(SCROLLINFO));
		CopyMemory((LPVOID)&m_sScrollInfo[1], pVertScrollInfo, sizeof(SCROLLINFO));
		m_bScrollBars = TRUE;
		RecalcLayout();
	}
}

VOID CTextViewContentCtrl::GetScrollInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CTextViewLock  cLock(GetParent());

	CopyMemory((LPVOID)pHorzScrollInfo, &m_sScrollInfo[0], sizeof(SCROLLINFO));
	CopyMemory((LPVOID)pVertScrollInfo, &m_sScrollInfo[1], sizeof(SCROLLINFO));
}

VOID CTextViewContentCtrl::RecalcLayout()
{
	CRect  rHeader;
	CRect  rContent;
	CSize  sizeContent;
	CTextViewLock  cLock(GetParent());

	if (!CThread::IsSameThread(this))
	{
		if (IsWindow(GetSafeHwnd()))
		{
			Invalidate(!(m_bUpdate = TRUE));
			DrawContent();
		}
		return;
	}
	if (m_bScrollBars)
	{
		CScrollView::SetScrollInfo(SB_HORZ, &m_sScrollInfo[0]);
		CScrollView::SetScrollInfo(SB_VERT, &m_sScrollInfo[1]);
		m_nScrollPos[0] = m_sScrollInfo[0].nPos;
		m_nScrollPos[1] = m_sScrollInfo[1].nPos;
		m_bScrollBars = FALSE;
	}
	for (m_pHeaderCtrl->GetWindowRect(rHeader), GetParent()->GetClientRect(rContent), m_bUpdate = FALSE; (GetParent()->GetStyle() & (TVS_TOP | TVS_BOTTOM)) == TVS_TOP; )
	{
		rContent.top += rHeader.Height();
		break;
	}
	for (; (GetParent()->GetStyle() & (TVS_TOP | TVS_BOTTOM)) == TVS_BOTTOM; )
	{
		rContent.bottom -= rHeader.Height();
		break;
	}
	for (sizeContent = CalcExtent(FALSE); m_sizeExtent.cx <= sizeContent.cx; )
	{
		MoveWindow(rContent);
		break;
	}
	for (SetScrollSizes(MM_TEXT, CSize((GetParent()->GetStyle() & TVS_HSCROLL) ? sizeContent.cx : 0, (GetParent()->GetStyle() & TVS_VSCROLL) ? sizeContent.cy : 0)); m_sizeExtent.cx > sizeContent.cx; )
	{
		MoveWindow(rContent);
		break;
	}
	for (m_sizeExtent = sizeContent; m_nScrollPos[1] != GetScrollPosition().y; )
	{
		ScrollToPosition(CPoint(GetScrollPosition().x, m_nScrollPos[1]));
		break;
	}
	UpdateScrollBars();
	DrawContent();
}

VOID CTextViewContentCtrl::RecalcContent()
{
	INT  nItem;
	INT  nItems;
	CTextViewLock  cLock(GetParent());

	for (nItem = 0, nItems = (INT)m_szContentText.GetSize(), m_nContentTextPos.RemoveAll(); nItem < nItems; nItem++)
	{
		m_nContentTextPos.SetAtGrow(nItem, (nItem > 0) ? (m_nContentTextPos.GetAt(nItem - 1) + CalcTextLines(m_szContentText.GetAt(nItem), m_pContentTextAttributes.GetAt(nItem))) : CalcTextLines(m_szContentText.GetAt(nItem), m_pContentTextAttributes.GetAt(nItem)));
		continue;
	}
	RecalcLayout();
}

VOID CTextViewContentCtrl::DrawContent()
{
	GetParent()->DrawContent();
}
VOID CTextViewContentCtrl::DrawContent(CDC *pDC)
{
	GetParent()->DrawContent(pDC);
}

VOID CTextViewContentCtrl::DrawText(INT nItem, LPCTSTR pszText)
{
	GetParent()->DrawText(nItem, pszText);
}
VOID CTextViewContentCtrl::DrawText(CDC *pDC, INT nItem, LPCTSTR pszText)
{
	GetParent()->DrawText(pDC, nItem, pszText);
}
VOID CTextViewContentCtrl::DrawText(INT nItem, INT nColumn, LPCTSTR pszText)
{
	GetParent()->DrawText(nItem, nColumn, pszText);
}
VOID CTextViewContentCtrl::DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText)
{
	GetParent()->DrawText(pDC, nItem, nColumn, pszText);
}

CSize CTextViewContentCtrl::CalcExtent(BOOL bFull) CONST
{
	INT  nItem;
	INT  nItems;
	CSize  size;
	CSize  sizeText;
	CRect  rContent;
	CFont  *pOldFont;
	CClientDC  cDC(NULL);
	CTextViewLock  cLock(GetParent());

	if (!GetParent()->CalcContentExtent(size))
	{
		for (size.cx = size.cy = 0; !m_pHeaderCtrl->GetColumnCount(); )
		{
			if ((pOldFont = cDC.SelectObject((CFont *)&m_cFont)) != (CFont *)NULL)
			{
				for (nItem = 0, nItems = (INT)m_szContentText.GetSize(), GetClientRect(rContent), size.cx = (bFull) ? rContent.Width() : 0; nItem < nItems; nItem++)
				{
					sizeText = cDC.GetTextExtent(m_szContentText.GetAt(nItem));
					sizeText.cx += m_wTextIndent[0] + m_wTextIndent[1];
					size.cx = max(sizeText.cx, size.cx);
				}
				cDC.SelectObject(pOldFont);
			}
			break;
		}
		size.cx = (m_pHeaderCtrl->GetColumnCount() > 0) ? m_pHeaderCtrl->m_nColumnsWidth.GetAt(m_pHeaderCtrl->m_nColumnsWidth.GetUpperBound()) : size.cx;
		size.cy = (m_nContentTextPos.GetSize() > 0) ? m_nContentTextPos.GetAt(m_nContentTextPos.GetUpperBound()) : 0;
	}
	return size;
}

INT CTextViewContentCtrl::CalcTextLines(LPCTSTR pszText, CONST CTextViewAttribute *pAttribute) CONST
{
	CClientDC  cDC(NULL);

	return CalcTextLines(&cDC, pszText, pAttribute);
}
INT CTextViewContentCtrl::CalcTextLines(CDC *pDC, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute) CONST
{
	INT  nHeight;
	INT  nColumn;
	INT  nColumns;
	UINT  nFormat;
	CRect  rHeader;
	CRect  rColumn;
	CFont  cFont;
	CFont  *pOldFont;
	LOGFONT  lfFont;
	TEXTMETRIC  tmText;
	CStringArray  szColumns;
	CTextViewLock  cLock(GetParent());

	for (nColumn = 0, nColumns = ConvertText(pszText, szColumns), m_pHeaderCtrl->GetWindowRect(rHeader), nHeight = 0; nColumn < nColumns; nColumn++)
	{
		for (rColumn.SetRect((nColumn < m_pHeaderCtrl->GetColumnCount() && nColumn > 0) ? (m_pHeaderCtrl->m_nColumnsWidth.GetAt(nColumn - 1) + m_wTextIndent[0]) : m_wTextIndent[0], 0, (nColumn < m_pHeaderCtrl->GetColumnCount()) ? (m_pHeaderCtrl->m_nColumnsWidth.GetAt(nColumn) - m_wTextIndent[1]) : (rHeader.Width() - m_wTextIndent[1]), 0), nFormat = (!pAttribute || !pAttribute->GetColumnFormat(nColumn, nFormat)) ? GetColumnFormat(nColumn) : nFormat; (pOldFont = pDC->SelectObject(((pAttribute != (CTextViewAttribute *)NULL && pAttribute->GetColumnFont(nColumn, &lfFont) && cFont.CreateFontIndirect(&lfFont)) || GetColumnFont(nColumn, &cFont)) ? &cFont : (CFont *)&m_cFont)); )
		{
			if ((nFormat & DT_SINGLELINE) == DT_SINGLELINE  &&  pDC->GetTextMetrics(&tmText))
			{
				nHeight = max(m_wTextSpacing[0] + tmText.tmHeight + m_wTextSpacing[1], nHeight);
				pDC->SelectObject(pOldFont);
				break;
			}
			for (pDC->DrawText(szColumns.GetAt(nColumn), rColumn, nFormat | DT_CALCRECT); !rColumn.Height(); )
			{
				rColumn.InflateRect(0, 0, 0, (pDC->GetTextMetrics(&tmText)) ? tmText.tmHeight : 0);
				break;
			}
			nHeight = max(m_wTextSpacing[0] + rColumn.Height() + m_wTextSpacing[1], nHeight);
			pDC->SelectObject(pOldFont);
			break;
		}
		cFont.DeleteObject();
	}
	return nHeight;
}

CRect CTextViewContentCtrl::CalcTextRect(INT nItem, INT nColumn) CONST
{
	CRect  rText;
	CRect  rContent;
	CSize  sizeContent;
	CTextViewLock  cLock(GetParent());

	if (nItem >= 0 && nItem < m_szContentText.GetSize())
	{
		if (nColumn <= 0 || nColumn < m_pHeaderCtrl->GetColumnCount())
		{
			for (GetClientRect(rContent), sizeContent = CalcExtent(), rText.SetRectEmpty(); nColumn > 0; )
			{
				rText.left = m_pHeaderCtrl->m_nColumnsWidth.GetAt(nColumn - 1) + m_wTextIndent[0] - m_nScrollPos[0];
				rText.right = m_pHeaderCtrl->m_nColumnsWidth.GetAt(nColumn) - m_wTextIndent[1] - m_nScrollPos[0];
				break;
			}
			if (nColumn <= 0)
			{
				rText.left = m_wTextIndent[0] - m_nScrollPos[0];
				rText.right = (m_pHeaderCtrl->m_nColumnsWidth.GetSize() > 0) ? (m_pHeaderCtrl->m_nColumnsWidth.GetAt((nColumn < 0) ? m_pHeaderCtrl->m_nColumnsWidth.GetUpperBound() : nColumn) - m_wTextIndent[1] - m_nScrollPos[0]) : (sizeContent.cx - m_wTextIndent[1] - m_nScrollPos[0]);
			}
			if (nItem > 0)
			{
				rText.top = rContent.top + m_wTextSpacing[0] + m_nContentTextPos.GetAt(nItem - 1) - m_nScrollPos[1];
				rText.bottom = rContent.top + m_nContentTextPos.GetAt(nItem) - m_wTextSpacing[1] - m_nScrollPos[1];
			}
			if (!nItem)
			{
				rText.top = rContent.top + m_wTextSpacing[0] - m_nScrollPos[1];
				rText.bottom = rContent.top + m_nContentTextPos.GetAt(nItem) - m_wTextSpacing[1] - m_nScrollPos[1];
			}
			return rText;
		}
	}
	return CRect(0, 0, 0, 0);
}

WORD CTextViewContentCtrl::CalcDefaultIndent() CONST
{
	INT  nIndent;
	CFont  *pOldFont;
	CClientDC  cDC(NULL);
	CTextViewLock  cLock(GetParent());

	if ((pOldFont = cDC.SelectObject((CFont *)&m_cFont)))
	{
		nIndent = GetSystemMetrics(SM_CXEDGE) + cDC.GetTextExtent(SPACE).cy / 4;
		cDC.SelectObject(pOldFont);
		return nIndent;
	}
	return 0;
}

WORD CTextViewContentCtrl::CalcDefaultSpacing() CONST
{
	return 0;
}

CTextView *CTextViewContentCtrl::GetParent() CONST
{
	return m_pParentWnd;
}

TCHAR CTextViewContentCtrl::GetColumnDelimiter()
{
	return FF;
}

VOID CTextViewContentCtrl::UpdateScrollBars()
{
	BOOL  bBar[2];
	CRect  rContent;
	CSize  sizeContent;

	for (CheckScrollBars(bBar[0], bBar[1]), CScrollView::GetScrollInfo(SB_HORZ, &m_sScrollInfo[0]), CScrollView::GetScrollInfo(SB_VERT, &m_sScrollInfo[1]); !bBar[0]; )
	{
		m_sScrollInfo[0].nMin = m_sScrollInfo[0].nMax = 0;
		m_sScrollInfo[0].nPage = 0;
		m_sScrollInfo[0].nPos = 0;
		break;
	}
	if (!bBar[1])
	{
		m_sScrollInfo[1].nMin = m_sScrollInfo[1].nMax = 0;
		m_sScrollInfo[1].nPage = 0;
		m_sScrollInfo[1].nPos = 0;
	}
	for (GetClientRect(rContent), sizeContent = CalcExtent(), m_nScrollPos[0] = (GetParent()->GetStyle() & TVS_HSCROLL) ? m_sScrollInfo[0].nPos : min((UINT)max(sizeContent.cx - rContent.Width() + 1, 0), m_nScrollPos[0]), m_nScrollPos[1] = (GetParent()->GetStyle() & TVS_VSCROLL) ? m_sScrollInfo[1].nPos : min((UINT)max(sizeContent.cy - rContent.Height() + 1, 0), m_nScrollPos[1]); m_pHeaderCtrl->m_nScrollPos != m_sScrollInfo[0].nPos; )
	{
		m_pHeaderCtrl->m_nScrollPos = m_sScrollInfo[0].nPos;
		m_pHeaderCtrl->RecalcLayout();
		break;
	}
	if (m_bBars[0] != bBar[0])
	{
		CScrollView::UpdateBars();
		m_bBars[0] = bBar[0];
	}
	if (m_bBars[1] != bBar[1])
	{
		CScrollView::UpdateBars();
		m_bBars[1] = bBar[1];
	}
}

LRESULT CTextViewContentCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	return((!GetParent()->OnContentMessage(message, wParam, lParam, &lResult)) ? CScrollView::WindowProc(message, wParam, lParam) : lResult);
}

void CTextViewContentCtrl::PostNcDestroy()
{
	return;
}

BEGIN_MESSAGE_MAP(CTextViewContentCtrl, CScrollView)
	//{{AFX_MSG_MAP(CTextViewContentCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_GETDLGCODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextViewContentCtrl drawing

void CTextViewContentCtrl::OnDraw(CDC *pDC)
{
	pDC->SetViewportOrg(CPoint(0, 0));
	DrawContent(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTextViewContentCtrl message handlers

int CTextViewContentCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(GetParent());

	if (CScrollView::OnCreate(lpCreateStruct) != -1)
	{
		for (ZeroMemory(&m_sScrollInfo[0], sizeof(SCROLLINFO)), ZeroMemory(&m_sScrollInfo[1], sizeof(SCROLLINFO)); (m_pBlinkThread = new CTextViewBlinkThread(GetParent())); )
		{
			m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent();
			m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing();
			SetScrollSizes(MM_TEXT, CSize(0, 0));
			return 0;
		}
	}
	return -1;
}

BOOL CTextViewContentCtrl::OnEraseBkgnd(CDC *pDC)
{
	CTextViewLock  cLock(GetParent());

	UpdateWindow();
	return TRUE;
}

void CTextViewContentCtrl::OnPaint()
{
	CPaintDC  cDC(this);
	CTextViewLock  cLock(GetParent());

	if (m_bUpdate)
	{
		RecalcLayout();
		return;
	}
	DrawContent(&cDC);
}

UINT CTextViewContentCtrl::OnGetDlgCode()
{
	return DLGC_WANTCHARS | DLGC_WANTARROWS;
}

void CTextViewContentCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nIndex;
	CTextViewLock  cLock(GetParent());

	if ((nIndex = FindTextFromPoint(point, FALSE)) >= 0)
	{
		SetCurText(nIndex);
		SetFocus();
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CTextViewContentCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nItem;
	INT  nItems;
	INT  nHeight;
	CRect  rContent;
	CTextViewLock  cLock(GetParent());

	if (nChar == VK_UP || nChar == VK_DOWN)
	{
		if ((nItem = GetCurText()) >= 0)
		{
			nItem = ((GetParent()->GetStyle() & TVS_NOSELECTION) != TVS_NOSELECTION) ? ((nChar == VK_UP) ? (nItem - 1) : (nItem + 1)) : ((nChar == VK_UP) ? FindFirstVisibleText() : FindLastVisibleText());
			nItem = min(nItem, GetTextCount() - 1);
			nItem = max(nItem, 0);
			SetCurText(nItem);
		}
		else
		{
			if (nChar == VK_UP) SetCurText(GetTextCount() - 1);
			if (nChar == VK_DOWN) SetCurText(0);
		}
	}
	if (nChar == VK_PRIOR || nChar == VK_NEXT)
	{
		for (nItem = GetCurText(), nItems = GetTextCount(), GetClientRect(rContent), nHeight = (nItems > 0) ? ((nItem > 0) ? (m_nContentTextPos.GetAt(nItem) - m_nContentTextPos.GetAt(nItem - 1)) : m_nContentTextPos.GetAt(0)) : 0; nItem >= 0 && nItem < nItems; nItem = (nChar == VK_NEXT) ? (nItem + 1) : (nItem - 1))
		{
			if (abs((INT)(m_nContentTextPos.GetAt(GetCurText()) - m_nContentTextPos.GetAt(nItem))) >= rContent.Height() - nHeight) break;
			continue;
		}
		SetCurText((GetCurText() >= 0) ? max(min(nItem, nItems - 1), 0) : ((nChar == VK_PRIOR) ? (nItems - 1) : 0));
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTextViewContentCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	SCROLLINFO  sScrollInfo;

	if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
	{
		sScrollInfo.fMask = SIF_TRACKPOS;
		sScrollInfo.cbSize = sizeof(SCROLLINFO);
		CView::GetScrollInfo(SB_HORZ, &sScrollInfo);
		nPos = sScrollInfo.nTrackPos;
	}
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTextViewContentCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	SCROLLINFO  sScrollInfo;

	if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION)
	{
		sScrollInfo.fMask = SIF_TRACKPOS;
		sScrollInfo.cbSize = sizeof(SCROLLINFO);
		CView::GetScrollInfo(SB_VERT, &sScrollInfo);
		nPos = sScrollInfo.nTrackPos;
	}
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTextViewContentCtrl::OnSetFocus(CWnd *pOldWnd)
{
	CTextViewLock  cLock(GetParent());

	for (m_bFocused = TRUE; m_nActiveItem >= 0 && m_nActiveItem < m_szContentText.GetSize(); )
	{
		DrawText(m_nActiveItem, m_szContentText.GetAt(m_nActiveItem));
		break;
	}
	CScrollView::OnSetFocus(pOldWnd);
}

void CTextViewContentCtrl::OnKillFocus(CWnd *pNewWnd)
{
	CTextViewLock  cLock(GetParent());

	for (m_bFocused = FALSE; m_nActiveItem >= 0 && m_nActiveItem < m_szContentText.GetSize(); )
	{
		DrawText(m_nActiveItem, m_szContentText.GetAt(m_nActiveItem));
		break;
	}
	CScrollView::OnKillFocus(pNewWnd);
}

BOOL CTextViewContentCtrl::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	BOOL  bResult;
	CRect  rCtrl;
	CSize  size[2];
	CTextViewLock  cLock(GetParent());

	for (size[0] = GetTotalSize(), size[1] = sizeScroll; abs(sizeScroll.cy) == size[0].cy / 10; )
	{
		for (GetClientRect(rCtrl), size[1].cy = (15 * rCtrl.Height()) / 16; sizeScroll.cy < 0; )
		{
			size[1].cy = -size[1].cy;
			break;
		}
		break;
	}
	if (abs(sizeScroll.cy) == size[0].cy / 100)
	{
		for (GetClientRect(rCtrl), size[1].cy = rCtrl.Height() / 16; sizeScroll.cy < 0; )
		{
			size[1].cy = -size[1].cy;
			break;
		}
	}
	bResult = CScrollView::OnScrollBy(size[1], bDoScroll);
	UpdateScrollBars();
	DrawContent();
	return bResult;
}

void CTextViewContentCtrl::OnDestroy()
{
	INT  nFont;
	INT  nFonts;
	CFont  *pFont;
	CTextViewLock  cLock(GetParent());

	for (nFont = 0, nFonts = (INT)m_pColumnsFont.GetSize(), m_szContentText.RemoveAll(), m_nContentTextPos.RemoveAll(), m_pContentTextAttributes.RemoveAll(), m_nColumnsFormat.RemoveAll(), m_bColumnsFormat.RemoveAll(), m_nColumnsColor.RemoveAll(), m_bColumnsColor.RemoveAll(); nFont < nFonts; nFont++)
	{
		if ((pFont = (CFont *)m_pColumnsFont.GetAt(nFont))) delete pFont;
		continue;
	}
	delete m_pBlinkThread;
	CScrollView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CWnd)

CTextView::CTextView() : CWnd()
{
	for (m_sizeTrack.cx = 0, m_sizeTrack.cy = 0; (m_pCriticalSection = new CCriticalSection); )
	{
		m_wndHeaderCtrl.Initialize(this);
		m_wndContentCtrl.Initialize(this, &m_wndHeaderCtrl);
		break;
	}
	m_pParentWnd = (CWnd *)NULL;
}

CTextView::~CTextView()
{
	delete m_pCriticalSection;
}

BOOL CTextView::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, UINT nID)
{
	return CWnd::Create(AfxRegisterWndClass(CS_NOCLOSE), (LPCTSTR)NULL, dwStyle, rect, (m_pParentWnd = pParentWnd), nID);
}

BOOL CTextView::SetTitleFont(CFont *pFont)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.SetColumnsFont(pFont);
}
BOOL CTextView::SetTitleFont(CONST LOGFONT *plfFont)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.SetColumnsFont(plfFont);
}

BOOL CTextView::GetTitleFont(CFont *pFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.GetColumnsFont(pFont);
}
BOOL CTextView::GetTitleFont(LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.GetColumnsFont(plfFont);
}

BOOL CTextView::SetTextFont(CFont *pFont)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnsFont(pFont);
}
BOOL CTextView::SetTextFont(CONST LOGFONT *plfFont)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnsFont(plfFont);
}

BOOL CTextView::GetTextFont(CFont *pFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnsFont(pFont);
}
BOOL CTextView::GetTextFont(LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnsFont(plfFont);
}

BOOL CTextView::SetColumns(CONST CStringArray &szColumns)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.SetColumns(szColumns);
}
BOOL CTextView::SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.SetColumns(szColumns, nWidths);
}
BOOL CTextView::SetColumns(CONST CStringArray &szColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nFormats)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.SetColumns(szColumns, nWidths, nFormats);
}

BOOL CTextView::GetColumns(CStringArray &szColumns) CONST
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.GetColumns(szColumns);
}
BOOL CTextView::GetColumns(CStringArray &szColumns, CUIntArray &nWidths) CONST
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.GetColumns(szColumns, nWidths);
}
BOOL CTextView::GetColumns(CStringArray &szColumns, CUIntArray &nWidths, CUIntArray &nFormats) CONST
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.GetColumns(szColumns, nWidths, nFormats);
}

BOOL CTextView::AddColumn(LPCTSTR pszColumn)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.AddColumn(pszColumn);
}
BOOL CTextView::AddColumn(LPCTSTR pszColumn, INT nWidth, UINT nFormat)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.AddColumn(pszColumn, nWidth, nFormat);
}

BOOL CTextView::InsertColumn(LPCTSTR pszColumn, INT nColumn)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.InsertColumn(pszColumn, nColumn);
}
BOOL CTextView::InsertColumn(LPCTSTR pszColumn, INT nColumn, INT nWidth, UINT nFormat)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.InsertColumn(pszColumn, nColumn, nWidth, nFormat);
}

BOOL CTextView::SetColumnFormat(INT nColumn, UINT nFormat, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnFormat(nColumn, nFormat, bRedraw);
}
BOOL CTextView::SetColumnFormat(INT nItem, INT nColumn, UINT nFormat, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnFormat(nItem, nColumn, nFormat, bRedraw);
}

UINT CTextView::GetColumnFormat(INT nColumn) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnFormat(nColumn);
}
UINT CTextView::GetColumnFormat(INT nItem, INT nColumn) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnFormat(nItem, nColumn);
}

BOOL CTextView::SetColumnColor(INT nColumn, COLORREF nColor, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnColor(nColumn, nColor, bRedraw);
}
BOOL CTextView::SetColumnColor(INT nItem, INT nColumn, COLORREF nColor, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnColor(nItem, nColumn, nColor, bRedraw);
}

COLORREF CTextView::GetColumnColor(INT nColumn) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnColor(nColumn);
}
COLORREF CTextView::GetColumnColor(INT nItem, INT nColumn) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnColor(nItem, nColumn);
}

BOOL CTextView::SetColumnFont(INT nColumn, CFont *pFont, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnFont(nColumn, pFont, bRedraw);
}
BOOL CTextView::SetColumnFont(INT nColumn, CONST LOGFONT *plfFont, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnFont(nColumn, plfFont, bRedraw);
}
BOOL CTextView::SetColumnFont(INT nItem, INT nColumn, CFont *pFont, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnFont(nItem, nColumn, pFont, bRedraw);
}
BOOL CTextView::SetColumnFont(INT nItem, INT nColumn, CONST LOGFONT *plfFont, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetColumnFont(nItem, nColumn, plfFont, bRedraw);
}

BOOL CTextView::GetColumnFont(INT nColumn, CFont *pFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnFont(nColumn, pFont);
}
BOOL CTextView::GetColumnFont(INT nColumn, LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnFont(nColumn, plfFont);
}
BOOL CTextView::GetColumnFont(INT nItem, INT nColumn, CFont *pFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnFont(nItem, nColumn, pFont);
}
BOOL CTextView::GetColumnFont(INT nItem, INT nColumn, LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetColumnFont(nItem, nColumn, plfFont);
}

BOOL CTextView::DeleteColumn(INT nColumn)
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.DeleteColumn(nColumn);
}

INT CTextView::GetColumnCount() CONST
{
	CTextViewLock  cLock(this);

	return m_wndHeaderCtrl.GetColumnCount();
}

BOOL CTextView::SetContent(CONST CStringArray &szContent, CONST CTextViewAttributes &pAttributes)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetContent(szContent, pAttributes);
}

BOOL CTextView::GetContent(CStringArray &szContent, CTextViewAttributes &pAttributes) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetContent(szContent, pAttributes);
}

INT CTextView::AddText(LPCTSTR pszText, CONST CTextViewAttribute *pAttribute, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.AddText(pszText, pAttribute, bRedraw);
}

BOOL CTextView::InsertText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.InsertText(nItem, pszText, pAttribute, bRedraw);
}

BOOL CTextView::SetText(INT nItem, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetText(nItem, pszText, pAttribute, bRedraw);
}
BOOL CTextView::SetText(INT nItem, INT nColumn, LPCTSTR pszText, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetText(nItem, nColumn, pszText, bRedraw);
}

BOOL CTextView::GetText(INT nItem, CString &szText, CTextViewAttribute *pAttribute) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetText(nItem, szText, pAttribute);
}
BOOL CTextView::GetText(INT nItem, INT nColumn, CString &szText) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetText(nItem, nColumn, szText);
}

CString CTextView::ConvertText(CONST CStringArray &szColumns) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.ConvertText(szColumns);
}
INT CTextView::ConvertText(LPCTSTR pszText, CStringArray &szColumns) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.ConvertText(pszText, szColumns);
}

INT CTextView::FindText(LPCTSTR pszText, INT nColumn, BOOL bExist) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.FindText(pszText, nColumn, bExist);
}

BOOL CTextView::FindTextFromPoint(CPoint point, INT &nItem, INT &nColumn, BOOL bExist) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.FindTextFromPoint(point, nItem, nColumn, bExist);
}
INT CTextView::FindTextFromPoint(CPoint point, BOOL bExist) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.FindTextFromPoint(point, bExist);
}

INT CTextView::FindFirstVisibleText() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.FindFirstVisibleText();
}

INT CTextView::FindLastVisibleText() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.FindLastVisibleText();
}

BOOL CTextView::DeleteText(INT nItem, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.DeleteText(nItem, bRedraw);
}

BOOL CTextView::DeleteAllText(BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.DeleteAllText(bRedraw);
}

INT CTextView::GetTextCount() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetTextCount();
}

BOOL CTextView::SetCurText(INT nItem, INT nColumn)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetCurText(nItem, nColumn);
}

INT CTextView::GetCurText() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetCurText();
}

INT CTextView::SearchText(LPCTSTR pszText, INT nColumn) CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SearchText(pszText, nColumn);
}

BOOL CTextView::StartTextBlinking(INT nItem, INT nColumn)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.StartTextBlinking(nItem, nColumn);
}

BOOL CTextView::StopTextBlinking(INT nItem, INT nColumn)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.StopTextBlinking(nItem, nColumn);
}

BOOL CTextView::SetTextLimit(INT nLimit, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetTextLimit(nLimit, bRedraw);
}

INT CTextView::GetTextLimit() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetTextLimit();
}

BOOL CTextView::SetTextIndents(WORD wLeft, WORD wRight, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetTextIndents(wLeft, wRight, bRedraw);
}

DWORD CTextView::GetTextIndents() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetTextIndents();
}

BOOL CTextView::SetTextSpacings(WORD wTop, WORD wBottom, BOOL bRedraw)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetTextSpacings(wTop, wBottom, bRedraw);
}

DWORD CTextView::GetTextSpacings() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetTextSpacings();
}

BOOL CTextView::SetTextSortOrder(UINT nOrder, INT nColumn)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.SetTextSortOrder(nOrder, nColumn);
}

UINT CTextView::GetTextSortOrder() CONST
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.GetTextSortOrder();
}

BOOL CTextView::ScrollToTop()
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.ScrollToTop();
}

BOOL CTextView::ScrollTo(INT nItem)
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.ScrollTo(nItem);
}

BOOL CTextView::ScrollToBottom()
{
	CTextViewLock  cLock(this);

	return m_wndContentCtrl.ScrollToBottom();
}

VOID CTextView::SetScrollInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CTextViewLock  cLock(this);

	m_wndContentCtrl.SetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
}

VOID CTextView::GetScrollInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CTextViewLock  cLock(this);

	m_wndContentCtrl.GetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
}

VOID CTextView::SetTrackSize(CONST SIZE &size)
{
	CTextViewLock  cLock(this);

	m_sizeTrack = size;
}

CSize CTextView::GetTrackSize() CONST
{
	CTextViewLock  cLock(this);

	return m_sizeTrack;
}

VOID CTextView::RecalcLayout()
{
	CTextViewLock  cLock(this);

	for (m_wndHeaderCtrl.RecalcLayout(), m_wndContentCtrl.RecalcLayout(); CThread::IsSameThread(this); )
	{
		m_sizeTrack = CalcTrackSize();
		break;
	}
}

VOID CTextView::RecalcContent()
{
	CTextViewLock  cLock(this);

	m_wndContentCtrl.RecalcContent();
}

VOID CTextView::RefreshContent()
{
	return;
}

VOID CTextView::DrawContent()
{
	CDC  *pDC;

	if ((pDC = m_wndContentCtrl.GetDC()))
	{
		DrawContent(pDC);
		m_wndContentCtrl.ReleaseDC(pDC);
	}
}
VOID CTextView::DrawContent(CDC *pDC)
{
	INT  nItem;
	INT  nItems;
	CRect  rText;
	CRect  rContent;
	CTextViewLock  cLock(this);

	for (m_wndContentCtrl.GetClientRect(rContent), rText = m_wndContentCtrl.CalcTextRect(GetTextCount() - 1), pDC->FillSolidRect((!GetTextCount()) ? rContent : CRect(0, 0, 0, 0), GetSysColor(COLOR_WINDOW)); GetTextCount() > 0; )
	{
		pDC->FillSolidRect(CRect(min(rText.right + m_wndContentCtrl.m_wTextIndent[1], rContent.right), rContent.top, rContent.right, min(max(rText.bottom + m_wndContentCtrl.m_wTextSpacing[1], rContent.top), rContent.bottom)), GetSysColor(COLOR_WINDOW));
		pDC->FillSolidRect(CRect(rContent.left, min(max(rText.bottom + m_wndContentCtrl.m_wTextSpacing[1], rContent.top), rContent.bottom), rContent.right, rContent.bottom), GetSysColor(COLOR_WINDOW));
		break;
	}
	for (nItem = FindFirstVisibleText(), nItems = FindLastVisibleText() + 1, nItems = min(GetTextCount() - 1, nItems); nItem >= 0 && nItem <= nItems; nItem++)
	{
		DrawText(pDC, nItem, m_wndContentCtrl.m_szContentText.GetAt(nItem));
		continue;
	}
}

VOID CTextView::DrawText(INT nItem, LPCTSTR pszText)
{
	CDC  *pDC;

	if ((pDC = m_wndContentCtrl.GetDC()))
	{
		DrawText(pDC, nItem, pszText);
		m_wndContentCtrl.ReleaseDC(pDC);
	}
}
VOID CTextView::DrawText(CDC *pDC, INT nItem, LPCTSTR pszText)
{
	INT  nColumn;
	INT  nColumns;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = ConvertText(pszText, szColumns), nColumns = (INT)max(m_wndHeaderCtrl.GetColumnCount(), szColumns.GetSize()); nColumn < nColumns; nColumn++)
	{
		DrawText(pDC, nItem, nColumn, (nColumn < szColumns.GetSize()) ? (LPCTSTR)szColumns.GetAt(nColumn) : EMPTYSTRING);
		continue;
	}
}
VOID CTextView::DrawText(INT nItem, INT nColumn, LPCTSTR pszText)
{
	CDC  *pDC;

	if ((pDC = m_wndContentCtrl.GetDC()))
	{
		DrawText(pDC, nItem, nColumn, pszText);
		m_wndContentCtrl.ReleaseDC(pDC);
	}
}
VOID CTextView::DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText)
{
	CDC  cDC;
	BOOL  bState;
	UINT  nFormat;
	CRect  rText[3];
	CFont  cTextFont;
	CFont  *pOldFont;
	CSize  sizeBitmap;
	CPoint  ptBitmap;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	COLORREF  nTextColor;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(this);

	for (m_wndContentCtrl.GetClientRect(rText[0]), rText[1] = m_wndContentCtrl.CalcTextRect(nItem, nColumn), sizeBitmap.cx = m_wndContentCtrl.m_wTextIndent[0] + rText[1].Width() + m_wndContentCtrl.m_wTextIndent[1], sizeBitmap.cy = m_wndContentCtrl.m_wTextSpacing[0] + rText[1].Height() + m_wndContentCtrl.m_wTextSpacing[1]; rText[2].IntersectRect(rText[0], CRect(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rText[1].right + m_wndContentCtrl.m_wTextIndent[1], rText[1].bottom + m_wndContentCtrl.m_wTextSpacing[1])); )
	{
		for (nFormat = GetColumnFormat(nItem, nColumn), nTextColor = GetColumnColor(nItem, nColumn), bState = TRUE; (pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nItem)); )
		{
			bState = (pAttribute->GetColumnBlinkingState(nColumn, bState) || pAttribute->GetColumnBlinkingState(-1, bState)) ? bState : TRUE;
			break;
		}
		if (cDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap.CreateCompatibleBitmap(pDC, sizeBitmap.cx, sizeBitmap.cy))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
				{
					for (cDC.SetBkMode(TRANSPARENT), cDC.SetTextColor(nTextColor), DrawBackground(&cDC, nItem, nColumn, CRect(0, 0, sizeBitmap.cx, sizeBitmap.cy)); (pOldFont = (bState) ? ((GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)) : (CFont *)NULL); )
					{
						cDC.DrawText(pszText, CRect(m_wndContentCtrl.m_wTextIndent[0], m_wndContentCtrl.m_wTextSpacing[0], sizeBitmap.cx - m_wndContentCtrl.m_wTextIndent[0], sizeBitmap.cy - m_wndContentCtrl.m_wTextSpacing[0]), nFormat);
						cDC.SelectObject(pOldFont);
						break;
					}
					ptBitmap.x = max(rText[2].left - rText[1].left + m_wndContentCtrl.m_wTextIndent[0], 0);
					ptBitmap.y = max(rText[2].top - rText[1].top + m_wndContentCtrl.m_wTextSpacing[0], 0);
					pDC->BitBlt(max(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rText[2].left), max(rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rText[2].top), min(sizeBitmap.cx - ptBitmap.x, rText[2].Width()), min(sizeBitmap.cy - ptBitmap.y, rText[2].Height()), &cDC, ptBitmap.x, ptBitmap.y, SRCCOPY);
					cDC.SelectObject(pOldBitmap);
				}
				cBitmap.DeleteObject();
			}
			cDC.DeleteDC();
		}
		break;
	}
}

BOOL CTextView::DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rect)
{
	CRect  rRect;
	HTHEME  hTheme;
	BOOL  bActive;
	CTextViewLock  cLock(this);

	for (bActive = ((GetStyle() & TVS_NOSELECTION) != TVS_NOSELECTION && ((nItem == m_wndContentCtrl.m_nActiveItem && (nColumn == m_wndContentCtrl.m_nActiveColumn || m_wndContentCtrl.m_nActiveColumn < 0)) || nItem < 0 || nColumn < 0)) ? TRUE : FALSE; !IsAppThemed(); )
	{
		pDC->FillSolidRect(&rect, (bActive) ? GetSysColor(COLOR_HIGHLIGHT) : GetSysColor(COLOR_WINDOW));
		pDC->SetTextColor((bActive) ? GetSysColor(COLOR_HIGHLIGHTTEXT) : pDC->GetTextColor());
		return FALSE;
	}
	for (pDC->FillSolidRect(&rect, GetSysColor(COLOR_WINDOW)); bActive && (m_wndContentCtrl.m_nActiveColumn == nColumn || m_wndContentCtrl.m_nActiveColumn < 0 || nItem < 0 || nColumn < 0); )
	{
		for (rRect.SetRect(rect.left, rect.top, rect.right, rect.bottom); m_wndContentCtrl.m_nActiveColumn != nColumn && nColumn >= 0; )
		{
			if (nColumn < m_wndHeaderCtrl.GetColumnCount() - 1) rRect.right += GetSystemMetrics(SM_CXFRAME);
			if (nColumn > 0) rRect.left -= GetSystemMetrics(SM_CXFRAME);
			break;
		}
		if ((hTheme = OpenThemeData(m_wndContentCtrl.GetSafeHwnd(), VSCLASS_MENU)))
		{
			for (DrawThemeBackground(hTheme, pDC->GetSafeHdc(), MENU_POPUPITEM, (m_wndContentCtrl.m_bFocused) ? MPI_HOT : MPI_DISABLEDHOT, rRect, (LPCRECT)NULL), DrawThemeBackground(hTheme, pDC->GetSafeHdc(), MENU_POPUPITEM, (m_wndContentCtrl.m_bFocused) ? MPI_HOT : MPI_DISABLEDHOT, rRect, (LPCRECT)NULL); m_wndContentCtrl.m_bFocused; )
			{
				DrawThemeBackground(hTheme, pDC->GetSafeHdc(), MENU_POPUPITEM, MPI_HOT, rRect, (LPCRECT)NULL);
				break;
			}
			CloseThemeData(hTheme);
		}
		break;
	}
	return TRUE;
}

VOID CTextView::DrawBlinking(BOOL bState)
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	BOOL  bBlinking[2];
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(this);

	for (nItem = FindFirstVisibleText(), nItems = FindLastVisibleText(); nItem >= 0 && nItem <= nItems; nItem++)
	{
		if ((pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nItem)) != (CTextViewAttribute *)NULL)
		{
			if (pAttribute->GetColumnBlinking(-1, bBlinking[0]) && pAttribute->SetColumnBlinkingState(-1, bState))
			{
				DrawText(nItem, m_wndContentCtrl.m_szContentText.GetAt(nItem));
				continue;
			}
			for (nColumn = 0, nColumns = m_wndHeaderCtrl.GetColumnCount(), bBlinking[0] = FALSE; nColumn < nColumns; nColumn++)
			{
				bBlinking[0] |= pAttribute->GetColumnBlinking(nColumn, bBlinking[1]) && pAttribute->SetColumnBlinkingState(nColumn, bState);
				continue;
			}
			if (nColumns > 0 && bBlinking[0])
			{
				DrawText(nItem, m_wndContentCtrl.m_szContentText.GetAt(nItem));
				continue;
			}
		}
	}
}

BOOL CTextView::CalcContentExtent(CSize &size) CONST
{
	size.cx = size.cy = 0;
	return FALSE;
}

CSize CTextView::CalcTrackSize() CONST
{
	CRect  rHeader;

	m_wndHeaderCtrl.GetWindowRect(rHeader);
	return CSize(max(2 * (GetSystemMetrics(SM_CXVSCROLL) + GetSystemMetrics(SM_CXHTHUMB)), GetSystemMetrics(SM_CXMINTRACK)), max(rHeader.Height() + 2 * (GetSystemMetrics(SM_CYHSCROLL) + GetSystemMetrics(SM_CYVTHUMB)), GetSystemMetrics(SM_CYMINTRACK)));
}

CWnd *CTextView::GetParent() CONST
{
	return m_pParentWnd;
}

TCHAR CTextView::GetColumnDelimiter()
{
	return CTextViewContentCtrl::GetColumnDelimiter();
}

BOOL CTextView::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTextView::Unlock()
{
	return m_pCriticalSection->Unlock();
}

BEGIN_MESSAGE_MAP(CTextView, CWnd)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers

int CTextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(this);

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndHeaderCtrl.Create(this, lpCreateStruct->style, FALSE))
		{
			if (m_wndContentCtrl.Create(this, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, TRUE))
			{
				m_sizeTrack = CalcTrackSize();
				return 0;
			}
		}
	}
	return -1;
}

void CTextView::OnSize(UINT nType, int cx, int cy)
{
	CTextViewLock  cLock(this);

	RecalcLayout();
	CWnd::OnSize(nType, cx, cy);
}

void CTextView::OnSetFocus(CWnd *pOldWnd)
{
	CTextViewLock  cLock(this);

	m_wndContentCtrl.SetFocus();
}

BOOL CTextView::OnHeaderMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	return FALSE;
}

BOOL CTextView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	return FALSE;
}

BOOL CTextView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nColumn;
	INT  nColumns;
	HDITEM  sColumn;
	NMHEADER  *pNotifyInfo = (NMHEADER *)lParam;
	CTextViewLock  cLock(this);

	if (pNotifyInfo->hdr.code == HDN_ITEMCHANGED  &&  !m_wndHeaderCtrl.m_bUpdate[0])
	{
		for (nColumn = 0, nColumns = m_wndHeaderCtrl.GetItemCount(), sColumn.mask = HDI_WIDTH; nColumn < nColumns; nColumn++)
		{
			if (m_wndHeaderCtrl.GetItem(nColumn, &sColumn) && !nColumn)
			{
				m_wndHeaderCtrl.m_nColumnsWidth.SetAtGrow(nColumn, sColumn.cxy);
				continue;
			}
			if (m_wndHeaderCtrl.GetItem(nColumn, &sColumn) && nColumn > 0)
			{
				m_wndHeaderCtrl.m_nColumnsWidth.SetAtGrow(nColumn, m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nColumn - 1) + sColumn.cxy);
				continue;
			}
			break;
		}
		RecalcContent();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTextViewLock

CTextViewLock::CTextViewLock(CONST CTextView *pView)
{
	if ((m_pView = (CTextView *)pView))
	{
		m_pView->Lock();
		return;
	}
}

CTextViewLock::~CTextViewLock()
{
	if (m_pView != (CTextView *)NULL)
	{
		m_pView->Unlock();
		return;
	}
}

BOOL CTextViewLock::Release()
{
	if (m_pView != (CTextView *)NULL)
	{
		m_pView->Unlock();
		m_pView = (CTextView *)NULL;
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewCell

CTableViewCell::CTableViewCell() : CPoint()
{
	CFontTools  cFontTools(&m_fntProperties);

	x = y = 0;
	m_nFormat = TAS_TYPE_TEXT | TAS_ALIGN_LEFT;
	m_nTextColor[0] = GetSysColor(COLOR_WINDOWTEXT);
	m_nTextColor[1] = GetSysColor(COLOR_WINDOW);
	m_nTextMode = TRANSPARENT;
	m_nBorderSize[0] = 0;
	m_nBorderSize[1] = 0;
	m_nBorderSize[2] = 0;
	m_nBorderSize[3] = 0;
	m_nBorderStyle[0] = 0;
	m_nBorderStyle[1] = 0;
	m_nBorderStyle[2] = 0;
	m_nBorderStyle[3] = 0;
	m_nBorderColor[0] = GetSysColor(COLOR_WINDOW);
	m_nBorderColor[1] = GetSysColor(COLOR_WINDOW);
	m_nBorderColor[2] = GetSysColor(COLOR_WINDOW);
	m_nBorderColor[3] = GetSysColor(COLOR_WINDOW);
	m_nBackgroundColor = GetSysColor(COLOR_WINDOW);
	m_rectPosition[0].SetRect(0, 0, 0, 0);
	m_rectPosition[1].SetRect(0, 0, 0, 0);
	m_nMinHeight = 0;
	m_nControlID = 0;
	m_pControl = (CWnd *)NULL;
	m_bActivated = FALSE;
	m_bEnabled = TRUE;
}

CTableViewCell::~CTableViewCell()
{
	DestroyControl();
}

VOID CTableViewCell::SetFormat(UINT nFormat)
{
	m_nFormat = nFormat;
}

UINT CTableViewCell::GetFormat() CONST
{
	return m_nFormat;
}

VOID CTableViewCell::SetPosition(CONST RECT &rect)
{
	m_rectPosition[0] = rect;
}

CRect CTableViewCell::GetPosition() CONST
{
	return m_rectPosition[0];
}

VOID CTableViewCell::SetInnerPosition(CONST RECT &rect)
{
	m_rectPosition[1] = rect;
}

CRect CTableViewCell::GetInnerPosition() CONST
{
	return((HasInnerPosition()) ? m_rectPosition[1] : m_rectPosition[0]);
}

BOOL CTableViewCell::HasInnerPosition() CONST
{
	return !m_rectPosition[1].IsRectNull();
}

VOID CTableViewCell::SetMinHeight(INT nHeight)
{
	m_nMinHeight = nHeight;
}

INT CTableViewCell::GetMinHeight() CONST
{
	return m_nMinHeight;
}

VOID CTableViewCell::SetBorder(UINT nSide, INT nSize, INT nStyle, COLORREF nColor)
{
	if (nSide & TAS_BORDER_LEFT)
	{
		m_nBorderSize[0] = nSize;
		m_nBorderStyle[0] = nStyle;
		m_nBorderColor[0] = nColor;
	}
	if (nSide & TAS_BORDER_TOP)
	{
		m_nBorderSize[1] = nSize;
		m_nBorderStyle[1] = nStyle;
		m_nBorderColor[1] = nColor;
	}
	if (nSide & TAS_BORDER_RIGHT)
	{
		m_nBorderSize[2] = nSize;
		m_nBorderStyle[2] = nStyle;
		m_nBorderColor[2] = nColor;
	}
	if (nSide & TAS_BORDER_BOTTOM)
	{
		m_nBorderSize[3] = nSize;
		m_nBorderStyle[3] = nStyle;
		m_nBorderColor[3] = nColor;
	}
}

BOOL CTableViewCell::GetBorder(UINT nSide, INT &nSize, INT &nStyle, COLORREF &nColor) CONST
{
	if (nSide == TAS_BORDER_LEFT)
	{
		nSize = m_nBorderSize[0];
		nStyle = m_nBorderStyle[0];
		nColor = m_nBorderColor[0];
		return TRUE;
	}
	if (nSide == TAS_BORDER_TOP)
	{
		nSize = m_nBorderSize[1];
		nStyle = m_nBorderStyle[1];
		nColor = m_nBorderColor[1];
		return TRUE;
	}
	if (nSide == TAS_BORDER_RIGHT)
	{
		nSize = m_nBorderSize[2];
		nStyle = m_nBorderStyle[2];
		nColor = m_nBorderColor[2];
		return TRUE;
	}
	if (nSide == TAS_BORDER_BOTTOM)
	{
		nSize = m_nBorderSize[3];
		nStyle = m_nBorderStyle[3];
		nColor = m_nBorderColor[3];
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewCell::SetBackgroundColor(COLORREF nColor)
{
	m_nBackgroundColor = nColor;
}

COLORREF CTableViewCell::GetBackgroundColor() CONST
{
	return m_nBackgroundColor;
}

VOID CTableViewCell::SetSubTable(LPCTSTR pszTable)
{
	m_szSubTable = pszTable;
}

CString CTableViewCell::GetSubTable() CONST
{
	return m_szSubTable;
}

BOOL CTableViewCell::SetText(LPCTSTR pszText, BOOL bVerify)
{
	INT  nIndex;
	CWnd  *pControl;
	CString  szText;
	CTableViewComboBoxListCtrl  *pComboBoxListCtrl;
	CTableViewComboBoxEditCtrl  *pComboBoxEditCtrl;

	if (IsWindow((pControl = GetControl())->GetSafeHwnd()))
	{
		for (; m_nFormat & TAS_TYPE_COMBOLISTBOX; )
		{
			pControl->SendMessage(CB_SETCURSEL, (WPARAM)pControl->SendMessage(CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszText));
			break;
		}
		for (; m_nFormat & TAS_TYPE_COMBOEDITBOX; )
		{
			if ((nIndex = (INT)pControl->SendMessage(CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszText)) >= 0) pControl->SendMessage(CB_SETCURSEL, (WPARAM)nIndex);
			break;
		}
		for (; m_nFormat & TAS_TYPE_COMBOCOLORSBOX; )
		{
			pControl->SendMessage(CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)CTableViewComboBoxColorsCtrl::TranslateColor(pszText));
			break;
		}
		for (; m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX; )
		{
			pControl->SendMessage(LSCB_SELECTLINESTYLE, (WPARAM)-1, (LPARAM)CTableViewComboBoxLineStylesCtrl::TranslateLineStyle(pszText));
			break;
		}
		for (; m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX; )
		{
			pControl->SendMessage(LSCB_SELECTLINESYMBOL, (WPARAM)-1, (LPARAM)CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol(pszText));
			break;
		}
		for (; m_nFormat & TAS_TYPE_SPINBOX; )
		{
			TableViewSpinCtrl_SetPos(pControl, CTableViewSpinCtrl::TranslateNumber(pszText));
			break;
		}
		for (; m_nFormat & TAS_TYPE_TIMESPINBOX; )
		{
			if (CTableViewTimeSpinCtrl::IsValidTime(pszText))
			{
				TableViewTimeSpinCtrl_SetTime(pControl, CTableViewTimeSpinCtrl::TranslateTime(pszText));
				break;
			}
			TableViewTimeSpinCtrl_SetTime(pControl, pszText);
			break;
		}
		if ((m_nFormat & (TAS_TYPE_SPINBOX | TAS_TYPE_TIMESPINBOX)) == 0)
		{
			for (pControl->GetWindowText(szText); szText.Compare(pszText); )
			{
				if ((pComboBoxListCtrl = (m_nFormat & TAS_TYPE_COMBOLISTBOX) ? (CTableViewComboBoxListCtrl *)GetControl() : (CTableViewComboBoxListCtrl *)NULL))
				{
					if (pComboBoxListCtrl->HasValue(pszText) || !bVerify) pControl->SetWindowText(pszText);
					break;
				}
				if ((pComboBoxEditCtrl = (m_nFormat & TAS_TYPE_COMBOEDITBOX) ? (CTableViewComboBoxEditCtrl *)GetControl() : (CTableViewComboBoxEditCtrl *)NULL))
				{
					if (pComboBoxEditCtrl->HasValue(pszText) || !bVerify) pControl->SetWindowText(pszText);
					break;
				}
				pControl->SetWindowText(pszText);
				break;
			}
		}
		if (bVerify)
		{
			if ((pComboBoxListCtrl = (m_nFormat & TAS_TYPE_COMBOLISTBOX) ? (CTableViewComboBoxListCtrl *)GetControl() : (CTableViewComboBoxListCtrl *)NULL) && !pComboBoxListCtrl->HasValue(pszText))
			{
				m_szText[0] = EMPTYSTRING;
				return FALSE;
			}
			if ((pComboBoxEditCtrl = (m_nFormat & TAS_TYPE_COMBOEDITBOX) ? (CTableViewComboBoxEditCtrl *)GetControl() : (CTableViewComboBoxEditCtrl *)NULL) && !pComboBoxEditCtrl->HasValue(pszText))
			{
				m_szText[0] = EMPTYSTRING;
				return FALSE;
			}
		}
	}
	m_szText[0] = pszText;
	return TRUE;
}

BOOL CTableViewCell::TranslateText(LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST
{
	LONGLONG  nRange[2];
	ULONGLONG  uRange[2];
	CTableViewComboBoxListCtrl  *pComboBoxListCtrl;
	CTableViewComboBoxEditCtrl  *pComboBoxEditCtrl;
	CTableViewDecNumberEditCtrl  *pDecNumberEditCtrl;
	CTableViewRawNumberEditCtrl  *pRawNumberEditCtrl;

	if (m_nFormat & TAS_TYPE_DECNUMBEREDIT)
	{
		if ((pDecNumberEditCtrl = (CTableViewDecNumberEditCtrl *)GetControl()))
		{
			if (pDecNumberEditCtrl->GetRange(nRange[0], nRange[1]))
			{
				sValue.Value.nValue = (LONGLONG)pDecNumberEditCtrl->TranslateNumber(pszText);
				return((lstrlen(pszText) > 0) ? TRUE : FALSE);
			}
			if (pDecNumberEditCtrl->GetRange(uRange[0], uRange[1]))
			{
				sValue.Value.uValue = (ULONGLONG)pDecNumberEditCtrl->TranslateNumber(pszText);
				return((lstrlen(pszText) > 0) ? TRUE : FALSE);
			}
			sValue.Value.fValue = pDecNumberEditCtrl->TranslateNumber(pszText);
			return((lstrlen(pszText) > 0) ? TRUE : FALSE);
		}
	}
	if (m_nFormat & TAS_TYPE_RAWNUMBEREDIT)
	{
		if ((pRawNumberEditCtrl = (CTableViewRawNumberEditCtrl *)GetControl()))
		{
			sValue.Value.uValue = pRawNumberEditCtrl->TranslateNumber(pszText);
			return((lstrlen(pszText) > 0) ? TRUE : FALSE);
		}
	}
	if (m_nFormat & TAS_TYPE_COMBOLISTBOX)
	{
		if ((pComboBoxListCtrl = (CTableViewComboBoxListCtrl *)GetControl()))
		{
			sValue.Value.nValue = pComboBoxListCtrl->TranslateValue(pszText);
			return((lstrlen(pszText) > 0) ? TRUE : FALSE);
		}
	}
	if (m_nFormat & TAS_TYPE_COMBOEDITBOX)
	{
		if ((pComboBoxEditCtrl = (CTableViewComboBoxEditCtrl *)GetControl()))
		{
			sValue.Value.nValue = pComboBoxEditCtrl->TranslateValue(pszText);
			return((lstrlen(pszText) > 0) ? TRUE : FALSE);
		}
	}
	if (m_nFormat & TAS_TYPE_COMBOCOLORSBOX)
	{
		sValue.Value.nColor = CTableViewComboBoxColorsCtrl::TranslateColor(pszText);
		return((lstrlen(pszText) > 0) ? TRUE : FALSE);
	}
	if (m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX)
	{
		sValue.Value.nValue = CTableViewComboBoxLineStylesCtrl::TranslateLineStyle(pszText);
		return((lstrlen(pszText) > 0) ? TRUE : FALSE);
	}
	if (m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX)
	{
		sValue.Value.nValue = CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol(pszText);
		return((lstrlen(pszText) > 0) ? TRUE : FALSE);
	}
	if (m_nFormat & TAS_TYPE_SPINBOX)
	{
		sValue.Value.nValue = CTableViewSpinCtrl::TranslateNumber(pszText);
		return((lstrlen(pszText) > 0) ? TRUE : FALSE);
	}
	if (m_nFormat & TAS_TYPE_TIMESPINBOX)
	{
		if (CTableViewTimeSpinCtrl::IsValidTime(pszText))
		{
			sValue.Value.tTime = CTableViewTimeSpinCtrl::TranslateTime(pszText);
			return((lstrlen(pszText) > 0) ? TRUE : FALSE);
		}
		sValue.Value.tTime = 0;
	}
	return FALSE;
}

BOOL CTableViewCell::UpdateText(LPCTSTR pszInitialText)
{
	CWnd  *pControl;

	if (IsWindow((pControl = GetControl())->GetSafeHwnd()))
	{
		if ((m_nFormat & TAS_TYPE_SPINBOX) || (m_nFormat & TAS_TYPE_TIMESPINBOX)) m_szText[0] = pszInitialText;
		return TRUE;
	}
	return FALSE;
}
BOOL CTableViewCell::UpdateText(UINT nAction)
{
	CWnd  *pControl;
	CString  szText;
	CTimeTag  tTimeTag;

	if (IsWindow((pControl = GetControl())->GetSafeHwnd()))
	{
		if ((m_nFormat & TAS_TYPE_SPINBOX) == TAS_TYPE_SPINBOX)
		{
			if (nAction == TAS_ACTION_NORMAL) SetText(CTableViewSpinCtrl::TranslateNumber(TableViewSpinCtrl_GetPos(pControl)));
			return TRUE;
		}
		if (m_nFormat & TAS_TYPE_TIMESPINBOX)
		{
			if (TableViewTimeSpinCtrl_GetTime(pControl, tTimeTag))
			{
				if (nAction == TAS_ACTION_NORMAL) SetText(CTableViewTimeSpinCtrl::TranslateTime(tTimeTag.GetTime(), (m_nFormat & TAS_TIME_SPAN) ? TRUE : FALSE));
				return TRUE;
			}
			if (TableViewTimeSpinCtrl_GetTime(pControl, szText)) m_szText[0] = (nAction == TAS_ACTION_NORMAL) ? szText : m_szText[0];
			return TRUE;
		}
		pControl->GetWindowText(szText);
		m_szText[0] = szText;
		return TRUE;
	}
	return FALSE;
}

CString CTableViewCell::GetText() CONST
{
	CWnd  *pControl;
	CString  szText;
	CTimeTag  tTimeTag;

	if (IsWindow((pControl = GetControl())->GetSafeHwnd()))
	{
		if (m_nFormat & TAS_TYPE_COMBOCOLORSBOX)
		{
			szText = CTableViewComboBoxColorsCtrl::TranslateColor((COLORREF)pControl->SendMessage(CCB_GETCOLOR, pControl->SendMessage(CB_GETCURSEL)));
			return szText;
		}
		if (m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX)
		{
			szText = CTableViewComboBoxLineStylesCtrl::TranslateLineStyle((INT)pControl->SendMessage(LSCB_GETLINESTYLE, pControl->SendMessage(CB_GETCURSEL)));
			return szText;
		}
		if (m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX)
		{
			szText = CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol((INT)pControl->SendMessage(LSCB_GETLINESYMBOL, pControl->SendMessage(CB_GETCURSEL)));
			return szText;
		}
		if (m_nFormat & TAS_TYPE_SPINBOX)
		{
			szText = CTableViewSpinCtrl::TranslateNumber(TableViewSpinCtrl_GetPos(pControl));
			return szText;
		}
		if (m_nFormat & TAS_TYPE_TIMESPINBOX)
		{
			if (TableViewTimeSpinCtrl_GetTime(pControl, tTimeTag))
			{
				szText = CTableViewTimeSpinCtrl::TranslateTime(tTimeTag.GetTime(), (m_nFormat & TAS_TIME_SPAN) ? TRUE : FALSE);
				return szText;
			}
			if (TableViewTimeSpinCtrl_GetTime(pControl, szText)) return szText;
		}
		pControl->GetWindowText(szText);
		return szText;
	}
	return m_szText[0];
}

VOID CTableViewCell::SetInitialText(LPCTSTR pszText)
{
	m_szText[1] = pszText;
}

CString CTableViewCell::GetInitialText() CONST
{
	return m_szText[1];
}

VOID CTableViewCell::SetTextStyle(INT nMode, COLORREF nColor, COLORREF nBkgndColor)
{
	m_nTextMode = nMode;
	m_nTextColor[0] = nColor;
	m_nTextColor[1] = nBkgndColor;
}

VOID CTableViewCell::GetTextStyle(INT &nMode, COLORREF &nColor, COLORREF &nBkgndColor) CONST
{
	nMode = m_nTextMode;
	nColor = m_nTextColor[0];
	nBkgndColor = m_nTextColor[1];
}

BOOL CTableViewCell::SetValue(CONST TABLEVIEWCELLVALUE &sValue)
{
	CString  szText;

	if (TranslateValue(sValue, szText))
	{
		SetText(szText);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewCell::TranslateValue(CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST
{
	CTableViewComboBoxListCtrl  *pComboBoxListCtrl;
	CTableViewComboBoxEditCtrl  *pComboBoxEditCtrl;
	CTableViewDecNumberEditCtrl  *pDecNumberEditCtrl;
	CTableViewRawNumberEditCtrl  *pRawNumberEditCtrl;

	if (m_nFormat & TAS_TYPE_DECNUMBEREDIT)
	{
		szText = ((pDecNumberEditCtrl = (CTableViewDecNumberEditCtrl *)GetControl()) && sValue.bValue) ? pDecNumberEditCtrl->TranslateNumber(sValue.Value.fValue) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_RAWNUMBEREDIT)
	{
		szText = ((pRawNumberEditCtrl = (CTableViewRawNumberEditCtrl *)GetControl()) && sValue.bValue) ? pRawNumberEditCtrl->TranslateNumber(sValue.Value.uValue) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_COMBOLISTBOX)
	{
		szText = ((pComboBoxListCtrl = (CTableViewComboBoxListCtrl *)GetControl()) && sValue.bValue) ? pComboBoxListCtrl->TranslateValue(sValue.Value.nValue) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_COMBOEDITBOX)
	{
		szText = ((pComboBoxEditCtrl = (CTableViewComboBoxEditCtrl *)GetControl()) && sValue.bValue) ? pComboBoxEditCtrl->TranslateValue(sValue.Value.nValue) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_COMBOCOLORSBOX)
	{
		szText = (sValue.bValue) ? CTableViewComboBoxColorsCtrl::TranslateColor(sValue.Value.nColor) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX)
	{
		szText = (sValue.bValue) ? CTableViewComboBoxLineStylesCtrl::TranslateLineStyle((INT)sValue.Value.nValue) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX)
	{
		szText = (sValue.bValue) ? CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol((INT)sValue.Value.nValue) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_SPINBOX)
	{
		szText = (sValue.bValue) ? CTableViewSpinCtrl::TranslateNumber(sValue.Value.nValue) : EMPTYSTRING;
		return sValue.bValue;
	}
	if (m_nFormat & TAS_TYPE_TIMESPINBOX)
	{
		szText = (sValue.bValue) ? CTableViewTimeSpinCtrl::TranslateTime(sValue.Value.tTime, (m_nFormat & TAS_TIME_SPAN) ? TRUE : FALSE) : EMPTYSTRING;
		return sValue.bValue;
	}
	return FALSE;
}

BOOL CTableViewCell::GetValue(TABLEVIEWCELLVALUE &sValue) CONST
{
	return TranslateText(GetText(), sValue);
}

BOOL CTableViewCell::SetFont(CONST LOGFONT *plfFont)
{
	CFont  cFont;
	CTableViewEditCtrl  *pEditCtrl;
	CTableViewSpinCtrl  *pSpinCtrl;
	CTableViewDPLEditCtrl  *pDPLEditCtrl;
	CTableViewMDLEditCtrl  *pMDLEditCtrl;
	CTableViewTPLEditCtrl  *pTPLEditCtrl;
	CTableViewTimeSpinCtrl  *pTimeSpinCtrl;
	CTableViewComboBoxListCtrl  *pComboBoxListCtrl;
	CTableViewComboBoxEditCtrl  *pComboBoxEditCtrl;
	CTableViewDecNumberEditCtrl  *pDecNumberEditCtrl;
	CTableViewRawNumberEditCtrl  *pRawNumberEditCtrl;
	CTableViewMultiLineEditCtrl  *pMultiLineEditCtrl;
	CTableViewComboBoxColorsCtrl  *pComboBoxColorsCtrl;
	CTableViewComboBoxLineStylesCtrl  *pComboBoxLineStylesCtrl;
	CTableViewComboBoxLineSymbolsCtrl  *pComboBoxLineSymbolsCtrl;

	for (CopyMemory(&m_fntProperties, plfFont, sizeof(LOGFONT)); IsWindow(GetControl()->GetSafeHwnd()); )
	{
		if ((pEditCtrl = (m_nFormat & TAS_TYPE_EDIT) ? (CTableViewEditCtrl *)GetControl() : (CTableViewEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pDPLEditCtrl = (m_nFormat & TAS_TYPE_DPLEDIT) ? (CTableViewDPLEditCtrl *)GetControl() : (CTableViewDPLEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				SetMinHeight(10 * plfFont->lfHeight);
				pDPLEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pMDLEditCtrl = (m_nFormat & TAS_TYPE_MDLEDIT) ? (CTableViewMDLEditCtrl *)GetControl() : (CTableViewMDLEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				SetMinHeight(10 * plfFont->lfHeight);
				pMDLEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pTPLEditCtrl = (m_nFormat & TAS_TYPE_TPLEDIT) ? (CTableViewTPLEditCtrl *)GetControl() : (CTableViewTPLEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				SetMinHeight(10 * plfFont->lfHeight);
				pTPLEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pMultiLineEditCtrl = (m_nFormat & TAS_TYPE_MULTILINEEDIT) ? (CTableViewMultiLineEditCtrl *)GetControl() : (CTableViewMultiLineEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pMultiLineEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pDecNumberEditCtrl = (m_nFormat & TAS_TYPE_DECNUMBEREDIT) ? (CTableViewDecNumberEditCtrl *)GetControl() : (CTableViewDecNumberEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pDecNumberEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pRawNumberEditCtrl = (m_nFormat & TAS_TYPE_RAWNUMBEREDIT) ? (CTableViewRawNumberEditCtrl *)GetControl() : (CTableViewRawNumberEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pRawNumberEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pComboBoxListCtrl = (m_nFormat & TAS_TYPE_COMBOLISTBOX) ? (CTableViewComboBoxListCtrl *)GetControl() : (CTableViewComboBoxListCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pComboBoxListCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pComboBoxEditCtrl = (m_nFormat & TAS_TYPE_COMBOEDITBOX) ? (CTableViewComboBoxEditCtrl *)GetControl() : (CTableViewComboBoxEditCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pComboBoxEditCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pComboBoxColorsCtrl = (m_nFormat & TAS_TYPE_COMBOCOLORSBOX) ? (CTableViewComboBoxColorsCtrl *)GetControl() : (CTableViewComboBoxColorsCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pComboBoxColorsCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pComboBoxLineStylesCtrl = (m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX) ? (CTableViewComboBoxLineStylesCtrl *)GetControl() : (CTableViewComboBoxLineStylesCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pComboBoxLineStylesCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pComboBoxLineSymbolsCtrl = (m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX) ? (CTableViewComboBoxLineSymbolsCtrl *)GetControl() : (CTableViewComboBoxLineSymbolsCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pComboBoxLineSymbolsCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pSpinCtrl = (m_nFormat & TAS_TYPE_SPINBOX) ? (CTableViewSpinCtrl *)GetControl() : (CTableViewSpinCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pSpinCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		if ((pTimeSpinCtrl = (m_nFormat & TAS_TYPE_TIMESPINBOX) ? (CTableViewTimeSpinCtrl *)GetControl() : (CTableViewTimeSpinCtrl *)NULL))
		{
			if (cFont.CreateFontIndirect(plfFont))
			{
				pTimeSpinCtrl->SetFont(&cFont);
				return TRUE;
			}
		}
		return FALSE;
	}
	return TRUE;
}

VOID CTableViewCell::GetFont(LOGFONT *plfFont) CONST
{
	CopyMemory(plfFont, &m_fntProperties, sizeof(LOGFONT));
}

BOOL CTableViewCell::CreateControl()
{
	CFont  cFont;
	LOGFONT  lfFont;
	CString  szTime[3];
	CTimeTag  tTime;
	CTableViewTimeSpinCtrl  *pTimeSpinCtrl;

	if (!m_pControl)
	{
		for (m_pControl = (m_nFormat & TAS_TYPE_EDIT) ? new CTableViewEditCtrl : (CTableViewEditCtrl *)NULL, m_pControl = (m_nFormat & TAS_TYPE_DPLEDIT) ? new CTableViewDPLEditCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_MDLEDIT) ? new CTableViewMDLEditCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_TPLEDIT) ? new CTableViewTPLEditCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_MULTILINEEDIT) ? new CTableViewMultiLineEditCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_DECNUMBEREDIT) ? new CTableViewDecNumberEditCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_RAWNUMBEREDIT) ? new CTableViewRawNumberEditCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_COMBOLISTBOX) ? new CTableViewComboBoxListCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_COMBOEDITBOX) ? new CTableViewComboBoxEditCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_COMBOCOLORSBOX) ? new CTableViewComboBoxColorsCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX) ? new CTableViewComboBoxLineStylesCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX) ? new CTableViewComboBoxLineSymbolsCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_SPINBOX) ? new CTableViewSpinCtrl : m_pControl, m_pControl = (m_nFormat & TAS_TYPE_TIMESPINBOX) ? new CTableViewTimeSpinCtrl : m_pControl; (pTimeSpinCtrl = (m_nFormat & TAS_TYPE_TIMESPINBOX) ? (CTableViewTimeSpinCtrl *)m_pControl : (CTableViewTimeSpinCtrl *)NULL); )
		{
			for (CTableViewTimeSpinCtrl::TranslateTimeAndFormat(m_szText[0], szTime[0], szTime[1], szTime[2]), pTimeSpinCtrl->SetFormat(szTime[2]); (tTime = CTableViewTimeSpinCtrl::TranslateTime(szTime[1])) > 0; )
			{
				pTimeSpinCtrl->SetInitialTime(tTime);
				break;
			}
			m_szText[0] = szTime[0];
			return TRUE;
		}
		if ((m_nFormat & TAS_TYPE_DPLEDIT) || (m_nFormat & TAS_TYPE_MDLEDIT) || (m_nFormat & TAS_TYPE_TPLEDIT))
		{
			if (cFont.CreateFontIndirect(&m_fntProperties))
			{
				if (cFont.GetLogFont(&lfFont)) SetMinHeight(10 * lfFont.lfHeight);
				cFont.DeleteObject();
			}
		}
	}
	return(((m_nFormat & TAS_TYPE_TEXT) || (m_nFormat & TAS_TYPE_SUBTABLE) || m_pControl) ? TRUE : FALSE);
}

VOID CTableViewCell::SetControlID(UINT nID)
{
	m_nControlID = nID;
}

UINT CTableViewCell::GetControlID() CONST
{
	return m_nControlID;
}

CWnd *CTableViewCell::GetControl() CONST
{
	return m_pControl;
}

BOOL CTableViewCell::ResizeControl()
{
	CRect  rControl[2];

	if (IsWindow(m_pControl->GetSafeHwnd()))
	{
		for (m_pControl->GetWindowRect(rControl[0]), m_pControl->GetParent()->ScreenToClient(rControl[0]), rControl[1] = CalcControlPosition(m_pControl->GetParent()); rControl[0] != rControl[1]; )
		{
			m_pControl->MoveWindow(rControl[1]);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewCell::DestroyControl()
{
	CWnd  *pControl;

	if ((pControl = m_pControl))
	{
		pControl->DestroyWindow();
		m_pControl = (CWnd *)NULL;
		delete pControl;
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewCell::Activate(CWnd *pWnd, BOOL bActivate)
{
	CFont  cFont;
	CTimeTag  tRange[2];
	CTableViewEditCtrl  *pEditCtrl;
	CTableViewSpinCtrl  *pSpinCtrl;
	CTableViewDPLEditCtrl  *pDPLEditCtrl;
	CTableViewMDLEditCtrl  *pMDLEditCtrl;
	CTableViewTPLEditCtrl  *pTPLEditCtrl;
	CTableViewTimeSpinCtrl  *pTimeSpinCtrl;
	CTableViewComboBoxListCtrl  *pComboBoxListCtrl;
	CTableViewComboBoxEditCtrl  *pComboBoxEditCtrl;
	CTableViewDecNumberEditCtrl  *pDecNumberEditCtrl;
	CTableViewRawNumberEditCtrl  *pRawNumberEditCtrl;
	CTableViewMultiLineEditCtrl  *pMultiLineEditCtrl;
	CTableViewComboBoxColorsCtrl  *pComboBoxColorsCtrl;
	CTableViewComboBoxLineStylesCtrl  *pComboBoxLineStylesCtrl;
	CTableViewComboBoxLineSymbolsCtrl  *pComboBoxLineSymbolsCtrl;

	if (bActivate)
	{
		if (m_bActivated != bActivate)
		{
			if (m_nFormat & TAS_TYPE_EDIT)
			{
				if ((pEditCtrl = (CTableViewEditCtrl *)m_pControl) && pEditCtrl->Create(pWnd, CalcControlPosition(pWnd), ES_AUTOHSCROLL | WS_CHILD | WS_TABSTOP | ((m_nFormat & TAS_ALIGN_LEFT) ? ES_LEFT : 0) | ((m_nFormat & TAS_ALIGN_RIGHT) ? ES_RIGHT : 0) | ((m_nFormat & TAS_ALIGN_HCENTER) ? ES_CENTER : 0), m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_DPLEDIT)
			{
				if ((pDPLEditCtrl = (CTableViewDPLEditCtrl *)m_pControl) && pDPLEditCtrl->Create(pWnd, CalcControlPosition(pWnd), ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP, GetControlID()))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pDPLEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pDPLEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_MDLEDIT)
			{
				if ((pMDLEditCtrl = (CTableViewMDLEditCtrl *)m_pControl) && pMDLEditCtrl->Create(pWnd, CalcControlPosition(pWnd), ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP, GetControlID()))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pMDLEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pMDLEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_TPLEDIT)
			{
				if ((pTPLEditCtrl = (CTableViewTPLEditCtrl *)m_pControl) && pTPLEditCtrl->Create(pWnd, CalcControlPosition(pWnd), ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP, GetControlID()))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pTPLEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pTPLEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_MULTILINEEDIT)
			{
				if ((pMultiLineEditCtrl = (CTableViewMultiLineEditCtrl *)m_pControl) && pMultiLineEditCtrl->Create(pWnd, CalcControlPosition(pWnd), ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_CHILD | WS_TABSTOP | ((m_nFormat & TAS_ALIGN_LEFT) ? ES_LEFT : 0) | ((m_nFormat & TAS_ALIGN_RIGHT) ? ES_RIGHT : 0) | ((m_nFormat & TAS_ALIGN_HCENTER) ? ES_CENTER : 0), m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pMultiLineEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pMultiLineEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_DECNUMBEREDIT)
			{
				if ((pDecNumberEditCtrl = (CTableViewDecNumberEditCtrl *)m_pControl) && pDecNumberEditCtrl->Create(pWnd, CalcControlPosition(pWnd), ES_AUTOHSCROLL | WS_CHILD | WS_TABSTOP | ((m_nFormat & TAS_ALIGN_LEFT) ? ES_LEFT : 0) | ((m_nFormat & TAS_ALIGN_RIGHT) ? ES_RIGHT : 0) | ((m_nFormat & TAS_ALIGN_HCENTER) ? ES_CENTER : 0), m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pDecNumberEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pDecNumberEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_RAWNUMBEREDIT)
			{
				if ((pRawNumberEditCtrl = (CTableViewRawNumberEditCtrl *)m_pControl) && pRawNumberEditCtrl->Create(pWnd, CalcControlPosition(pWnd), ES_AUTOHSCROLL | WS_CHILD | WS_TABSTOP | ((m_nFormat & TAS_ALIGN_LEFT) ? ES_LEFT : 0) | ((m_nFormat & TAS_ALIGN_RIGHT) ? ES_RIGHT : 0) | ((m_nFormat & TAS_ALIGN_HCENTER) ? ES_CENTER : 0), m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pRawNumberEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pRawNumberEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_COMBOLISTBOX)
			{
				if ((pComboBoxListCtrl = (CTableViewComboBoxListCtrl *)m_pControl) && pComboBoxListCtrl->Create(pWnd, CalcControlPosition(pWnd), CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_TABSTOP, m_nControlID))
				{
					for (pComboBoxListCtrl->SetItemHeight(-1, CalcControlHeight(pWnd, TRUE)), pComboBoxListCtrl->SetItemHeight(0, CalcControlHeight(pWnd, FALSE)); cFont.CreateFontIndirect(&m_fntProperties); )
					{
						pComboBoxListCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pComboBoxListCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_COMBOEDITBOX)
			{
				if ((pComboBoxEditCtrl = (CTableViewComboBoxEditCtrl *)m_pControl) && pComboBoxEditCtrl->Create(pWnd, CalcControlPosition(pWnd), CBS_AUTOHSCROLL | CBS_DROPDOWN | WS_CHILD | WS_VSCROLL | WS_TABSTOP, m_nControlID))
				{
					for (pComboBoxEditCtrl->SetItemHeight(-1, CalcControlHeight(pWnd, TRUE)), pComboBoxEditCtrl->SetItemHeight(0, CalcControlHeight(pWnd, FALSE)); cFont.CreateFontIndirect(&m_fntProperties); )
					{
						pComboBoxEditCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pComboBoxEditCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_COMBOCOLORSBOX)
			{
				if ((pComboBoxColorsCtrl = (CTableViewComboBoxColorsCtrl *)m_pControl) && pComboBoxColorsCtrl->Create(pWnd, CalcControlPosition(pWnd), CCBS_CUSTOM | CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_TABSTOP, m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pComboBoxColorsCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pComboBoxColorsCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX)
			{
				if ((pComboBoxLineStylesCtrl = (CTableViewComboBoxLineStylesCtrl *)m_pControl) && pComboBoxLineStylesCtrl->Create(pWnd, CalcControlPosition(pWnd), CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_TABSTOP, m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pComboBoxLineStylesCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pComboBoxLineStylesCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX)
			{
				if ((pComboBoxLineSymbolsCtrl = (CTableViewComboBoxLineSymbolsCtrl *)m_pControl) && pComboBoxLineSymbolsCtrl->Create(pWnd, CalcControlPosition(pWnd), CBS_DROPDOWNLIST | WS_CHILD | WS_VSCROLL | WS_TABSTOP, m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pComboBoxLineSymbolsCtrl->SetFont(&cFont);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pComboBoxLineSymbolsCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_SPINBOX)
			{
				if ((pSpinCtrl = (CTableViewSpinCtrl *)m_pControl) && pSpinCtrl->Create(pWnd, CalcControlPosition(pWnd), WS_CHILD | WS_TABSTOP, m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pSpinCtrl->SetFont(&cFont);
						SetInitialText(m_szText[0]);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pSpinCtrl->DestroyWindow();
				}
			}
			if (m_nFormat & TAS_TYPE_TIMESPINBOX)
			{
				if ((pTimeSpinCtrl = (CTableViewTimeSpinCtrl *)m_pControl) && pTimeSpinCtrl->Create(pWnd, CalcControlPosition(pWnd), pTimeSpinCtrl->GetFormat(), ((m_nFormat & TAS_TIME_FUTURE) ? TSBXS_FUTURE_TIME : 0) | ((m_nFormat & TAS_TIME_PAST) ? TSBXS_PAST_TIME : 0) | ((m_nFormat & TAS_TIME_UTC) ? TSBXS_UTC_TIME : 0) | ((m_nFormat & TAS_TIME_SPAN) ? TSBXS_SPAN_TIME : 0) | WS_CHILD | WS_TABSTOP, m_nControlID))
				{
					if (cFont.CreateFontIndirect(&m_fntProperties))
					{
						pTimeSpinCtrl->SetFont(&cFont);
						SetInitialText(m_szText[0]);
						SetText(m_szText[0]);
						m_bActivated = TRUE;
						return TRUE;
					}
					pTimeSpinCtrl->DestroyWindow();
				}
			}
			return(((m_nFormat & TAS_TYPE_TEXT) || (m_nFormat & TAS_TYPE_SUBTABLE)) ? TRUE : FALSE);
		}
		return TRUE;
	}
	if (m_bActivated  &&  m_pControl != (CWnd *)NULL)
	{
		m_pControl->DestroyWindow();
		m_bActivated = FALSE;
	}
	return TRUE;
}

BOOL CTableViewCell::IsActivated() CONST
{
	return m_bActivated;
}

VOID CTableViewCell::Enable(BOOL bEnabled)
{
	if (m_bEnabled != bEnabled)
	{
		if (IsWindow(m_pControl->GetSafeHwnd())) m_pControl->EnableWindow(bEnabled);
		m_bEnabled = bEnabled;
	}
}

BOOL CTableViewCell::IsEnabled() CONST
{
	return m_bEnabled;
}

VOID CTableViewCell::Draw(CDC *pDC)
{
	HPEN  hPen;
	HPEN  hSymPen;
	HPEN  hOldPen;
	UINT  nFormat;
	INT  nWidth;
	INT  nOldMode;
	INT  nTextMode;
	INT  nLineStyle;
	INT  nLineSymbol;
	CFont  *pOldFont;
	CFont  cFont;
	CRect  rColor;
	CRect  rStyles;
	CRect  rSymbols;
	CRect  rText[2];
	CBrush  cBrush;
	HBRUSH  hSymBrush;
	HBRUSH  hOldBrush;
	CString  szFormat;
	CString  szText;
	LOGFONT  lfText;
	COLORREF  nColor;
	COLORREF  nOldColor[2];
	COLORREF  nTextColor[2];
	LOGBRUSH  sPenBrush;
	CTableViewTimeSpinCtrl  *pTimeSpinCtrl;

	if (((nFormat = m_nFormat) & TAS_TYPE_TEXT) || (nFormat & TAS_TYPE_EDIT) || (nFormat & TAS_TYPE_DPLEDIT) || (nFormat & TAS_TYPE_MDLEDIT) || (nFormat & TAS_TYPE_TPLEDIT) || (nFormat & TAS_TYPE_MULTILINEEDIT) || (nFormat & TAS_TYPE_DECNUMBEREDIT) || (nFormat & TAS_TYPE_RAWNUMBEREDIT) || (nFormat & TAS_TYPE_COMBOLISTBOX) || (nFormat & TAS_TYPE_COMBOEDITBOX) || (nFormat & TAS_TYPE_SPINBOX))
	{
		for (GetFont(&lfText), GetTextStyle(nTextMode, nTextColor[0], nTextColor[1]), rText[0] = GetInnerPosition(); cFont.CreateFontIndirect(&lfText); )
		{
			nOldMode = pDC->SetBkMode(nTextMode);
			nOldColor[0] = pDC->SetTextColor(nTextColor[0]);
			nOldColor[1] = pDC->SetBkColor(nTextColor[1]);
			if ((pOldFont = (CFont *)pDC->SelectObject(&cFont)))
			{
				pDC->DrawText((szText = GetText()), (rText[1] = rText[0]), ((nFormat & TAS_ALIGN_LEFT) ? DT_LEFT : 0) | ((nFormat & TAS_ALIGN_RIGHT) ? DT_RIGHT : 0) | ((nFormat & TAS_ALIGN_HCENTER) ? DT_CENTER : 0) | DT_CALCRECT | DT_TOP | DT_EXPANDTABS | DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_NOPREFIX);
				pDC->DrawText(szText, ((nFormat & TAS_ALIGN_TOP) != TAS_ALIGN_TOP) ? ((nFormat & TAS_ALIGN_VCENTER) ? CRect(rText[0].left, max(rText[0].top + (rText[0].Height() - rText[1].Height()) / 2, rText[0].top), rText[0].right, min(rText[0].top + (rText[0].Height() - rText[1].Height()) / 2 + rText[1].Height(), rText[0].bottom)) : CRect(rText[0].left, max(rText[0].bottom - rText[1].Height(), rText[0].top), rText[0].right, rText[0].bottom)) : rText[0], ((nFormat & TAS_ALIGN_LEFT) ? DT_LEFT : 0) | ((nFormat & TAS_ALIGN_RIGHT) ? DT_RIGHT : 0) | ((nFormat & TAS_ALIGN_HCENTER) ? DT_CENTER : 0) | DT_TOP | DT_EXPANDTABS | DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_NOPREFIX);
				pDC->SelectObject(pOldFont);
			}
			pDC->SetTextColor(nOldColor[0]);
			pDC->SetBkColor(nOldColor[1]);
			pDC->SetBkMode(nOldMode);
			cFont.DeleteObject();
			break;
		}
		return;
	}
	if (nFormat & TAS_TYPE_COMBOCOLORSBOX)
	{
		if ((nColor = CTableViewComboBoxColorsCtrl::TranslateColor(GetText())) == GetSysColor(COLOR_WINDOW))
		{
			for (GetFont(&lfText), GetTextStyle(nTextMode, nTextColor[0], nTextColor[1]), rText[0] = GetInnerPosition(); cFont.CreateFontIndirect(&lfText); )
			{
				nOldMode = pDC->SetBkMode(nTextMode);
				nOldColor[0] = pDC->SetTextColor(nTextColor[0]);
				nOldColor[1] = pDC->SetBkColor(nTextColor[1]);
				if ((pOldFont = (CFont *)pDC->SelectObject(&cFont)))
				{
					pDC->DrawText(STRING(IDS_COLORSCOMBOBOX_CUSTOM), (rText[1] = rText[0]), DT_LEFT | DT_CALCRECT | DT_TOP | DT_EXPANDTABS | DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_NOPREFIX);
					pDC->DrawText(STRING(IDS_COLORSCOMBOBOX_CUSTOM), ((nFormat & TAS_ALIGN_TOP) != TAS_ALIGN_TOP) ? ((nFormat & TAS_ALIGN_VCENTER) ? CRect(rText[0].left, max(rText[0].top + (rText[0].Height() - rText[1].Height()) / 2, rText[0].top), rText[0].right, min(rText[0].top + (rText[0].Height() - rText[1].Height()) / 2 + rText[1].Height(), rText[0].bottom)) : CRect(rText[0].left, max(rText[0].bottom - rText[1].Height(), rText[0].top), rText[0].right, rText[0].bottom)) : rText[0], DT_LEFT | DT_TOP | DT_EXPANDTABS | DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_NOPREFIX);
					pDC->SelectObject(pOldFont);
				}
				pDC->SetTextColor(nOldColor[0]);
				pDC->SetBkColor(nOldColor[1]);
				pDC->SetBkMode(nOldMode);
				cFont.DeleteObject();
				break;
			}
			return;
		}
		if ((nColor = (lstrlen(GetText()) > 0) ? nColor : (COLORREF)-1) != (COLORREF)-1)
		{
			if (cBrush.CreateSolidBrush(nColor))
			{
				rColor = GetInnerPosition();
				rColor.DeflateRect(0, 2 * GetSystemMetrics(SM_CYEDGE));
				pDC->FillRect(rColor, &cBrush);
				cBrush.DeleteObject();
			}
		}
		return;
	}
	if (nFormat & TAS_TYPE_COMBOLINESTYLESBOX)
	{
		if ((nLineStyle = (lstrlen(GetText()) > 0) ? CTableViewComboBoxLineStylesCtrl::TranslateLineStyle(GetText()) : -1) != -1)
		{
			rStyles.SetRect(GetInnerPosition().left, GetInnerPosition().top, GetInnerPosition().right, GetInnerPosition().bottom);
			rStyles.DeflateRect(0, 2 * GetSystemMetrics(SM_CYEDGE));
			sPenBrush.lbStyle = BS_SOLID;
			sPenBrush.lbHatch = (ULONG_PTR)NULL;
			sPenBrush.lbColor = GetSysColor(COLOR_WINDOWTEXT);
			if ((hPen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | nLineStyle, 2, &sPenBrush, 0, (CONST DWORD *) NULL)))
			{
				if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hPen)) != (HPEN)NULL)
				{
					MoveToEx(pDC->GetSafeHdc(), rStyles.left, rStyles.CenterPoint().y, (LPPOINT)NULL);
					LineTo(pDC->GetSafeHdc(), rStyles.right, rStyles.CenterPoint().y);
					SelectObject(pDC->GetSafeHdc(), hOldPen);
				}
				DeleteObject(hPen);
			}
		}
		return;
	}
	if (nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX)
	{
		if ((nLineSymbol = (lstrlen(GetText()) > 0) ? CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol(GetText()) : -1) != -1)
		{
			rSymbols.SetRect(GetInnerPosition().left, GetInnerPosition().top, GetInnerPosition().right, GetInnerPosition().bottom);
			rSymbols.DeflateRect(0, 2 * GetSystemMetrics(SM_CYEDGE));
			sPenBrush.lbStyle = BS_SOLID;
			sPenBrush.lbHatch = (ULONG_PTR)NULL;
			sPenBrush.lbColor = GetSysColor(COLOR_WINDOWTEXT);
			if ((hPen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, (nWidth = 2), &sPenBrush, 0, (CONST DWORD *) NULL)))
			{
				if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hPen)) != (HPEN)NULL)
				{
					MoveToEx(pDC->GetSafeHdc(), rSymbols.left, rSymbols.CenterPoint().y, (LPPOINT)NULL);
					LineTo(pDC->GetSafeHdc(), rSymbols.right, rSymbols.CenterPoint().y);
					if ((hSymPen = CreatePen(PS_SOLID, 1, sPenBrush.lbColor)) != (HPEN)NULL)
					{
						if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hSymPen)))
						{
							if (nLineSymbol == LS_POINT || nLineSymbol == LS_SQUARE)
							{
								if ((hSymBrush = CreateSolidBrush(sPenBrush.lbColor)) != (HBRUSH)NULL)
								{
									if ((hOldBrush = (HBRUSH)SelectObject(pDC->GetSafeHdc(), hSymBrush)))
									{
										if (nLineSymbol == LS_POINT) Ellipse(pDC->GetSafeHdc(), rSymbols.CenterPoint().x - 2 * nWidth, rSymbols.CenterPoint().y - 2 * nWidth, rSymbols.CenterPoint().x + 2 * nWidth + 1, rSymbols.CenterPoint().y + 2 * nWidth + nWidth % 2);
										if (nLineSymbol == LS_SQUARE) Rectangle(pDC->GetSafeHdc(), rSymbols.CenterPoint().x - 2 * nWidth, rSymbols.CenterPoint().y - 2 * nWidth, rSymbols.CenterPoint().x + 2 * nWidth + 1, rSymbols.CenterPoint().y + 2 * nWidth + nWidth % 2);
										SelectObject(pDC->GetSafeHdc(), hOldBrush);
									}
									DeleteObject(hSymBrush);
								}
							}
							if (nLineSymbol == LS_STROKE)
							{
								MoveToEx(pDC->GetSafeHdc(), rSymbols.CenterPoint().x, rSymbols.CenterPoint().y - 2 * nWidth, (LPPOINT)NULL);
								LineTo(pDC->GetSafeHdc(), rSymbols.CenterPoint().x, rSymbols.CenterPoint().y + 2 * nWidth + nWidth % 2);
							}
							if (nLineSymbol == LS_CROSS)
							{
								MoveToEx(pDC->GetSafeHdc(), rSymbols.CenterPoint().x - 2 * nWidth, rSymbols.CenterPoint().y - 2 * nWidth - (nWidth + 1) % 2, (LPPOINT)NULL);
								LineTo(pDC->GetSafeHdc(), rSymbols.CenterPoint().x, rSymbols.CenterPoint().y - (nWidth + 1) % 2);
								MoveToEx(pDC->GetSafeHdc(), rSymbols.CenterPoint().x + 2 * nWidth, rSymbols.CenterPoint().y - 2 * nWidth - (nWidth + 1) % 2, (LPPOINT)NULL);
								LineTo(pDC->GetSafeHdc(), rSymbols.CenterPoint().x, rSymbols.CenterPoint().y - (nWidth + 1) % 2);
								MoveToEx(pDC->GetSafeHdc(), rSymbols.CenterPoint().x - 2 * nWidth, rSymbols.CenterPoint().y + 2 * nWidth, (LPPOINT)NULL);
								LineTo(pDC->GetSafeHdc(), rSymbols.CenterPoint().x, rSymbols.CenterPoint().y);
								MoveToEx(pDC->GetSafeHdc(), rSymbols.CenterPoint().x + 2 * nWidth, rSymbols.CenterPoint().y + 2 * nWidth, (LPPOINT)NULL);
								LineTo(pDC->GetSafeHdc(), rSymbols.CenterPoint().x, rSymbols.CenterPoint().y);
							}
							SelectObject(pDC->GetSafeHdc(), hOldPen);
						}
						DeleteObject(hSymPen);
					}
					SelectObject(pDC->GetSafeHdc(), hPen);
				}
				DeleteObject(hPen);
			}
		}
		return;
	}
	if (nFormat & TAS_TYPE_TIMESPINBOX)
	{
		for (GetFont(&lfText), GetTextStyle(nTextMode, nTextColor[0], nTextColor[1]); (pTimeSpinCtrl = (CTableViewTimeSpinCtrl *)GetControl()); )
		{
			szFormat = pTimeSpinCtrl->GetFormat();
			break;
		}
		if (cFont.CreateFontIndirect(&lfText))
		{
			nOldMode = pDC->SetBkMode(nTextMode);
			nOldColor[0] = pDC->SetTextColor(nTextColor[0]);
			nOldColor[1] = pDC->SetBkColor(nTextColor[1]);
			if ((pOldFont = (CFont *)pDC->SelectObject(&cFont)))
			{
				pDC->DrawText((szText = (!(szText = GetText()).IsEmpty() && szText.Find(TAB) < 0) ? ((!szFormat.IsEmpty()) ? ((nFormat & (TAS_TIME_UTC | TAS_TIME_SPAN)) ? CTimeTag(CTableViewTimeSpinCtrl::TranslateTime(szText)).FormatGmt(szFormat) : CTimeTag(CTableViewTimeSpinCtrl::TranslateTime(szText)).Format(szFormat)) : ((nFormat & (TAS_TIME_UTC | TAS_TIME_SPAN)) ? CTimeTag(CTableViewTimeSpinCtrl::TranslateTime(szText)).FormatGmt() : CTimeTag(CTableViewTimeSpinCtrl::TranslateTime(szText)).Format())) : EMPTYSTRING), (rText[1] = rText[0] = GetInnerPosition()), DT_LEFT | DT_CALCRECT | DT_TOP | DT_EXPANDTABS | DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_NOPREFIX);
				pDC->DrawText(szText, ((nFormat & TAS_ALIGN_TOP) != TAS_ALIGN_TOP) ? ((nFormat & TAS_ALIGN_VCENTER) ? CRect(rText[0].left, max(rText[0].top + (rText[0].Height() - rText[1].Height()) / 2, rText[0].top), rText[0].right, min(rText[0].top + (rText[0].Height() - rText[1].Height()) / 2 + rText[1].Height(), rText[0].bottom)) : CRect(rText[0].left, max(rText[0].bottom - rText[1].Height(), rText[0].top), rText[0].right, rText[0].bottom)) : rText[0], DT_LEFT | DT_TOP | DT_EXPANDTABS | DT_SINGLELINE | DT_WORD_ELLIPSIS | DT_NOPREFIX);
				pDC->SelectObject(pOldFont);
			}
			pDC->SetTextColor(nOldColor[0]);
			pDC->SetBkColor(nOldColor[1]);
			pDC->SetBkMode(nOldMode);
			cFont.DeleteObject();
		}
		return;
	}
}

VOID CTableViewCell::Copy(CONST CTableViewCell *pCell)
{
	x = pCell->x;
	y = pCell->y;
	m_nFormat = pCell->m_nFormat;
	m_szText[0] = pCell->GetText();
	m_szText[1] = pCell->m_szText[1];
	m_nTextMode = pCell->m_nTextMode;
	m_nTextColor[0] = pCell->m_nTextColor[0];
	m_nTextColor[1] = pCell->m_nTextColor[1];
	m_nBorderSize[0] = pCell->m_nBorderSize[0];
	m_nBorderSize[1] = pCell->m_nBorderSize[1];
	m_nBorderSize[2] = pCell->m_nBorderSize[2];
	m_nBorderSize[3] = pCell->m_nBorderSize[3];
	m_nBorderStyle[0] = pCell->m_nBorderStyle[0];
	m_nBorderStyle[1] = pCell->m_nBorderStyle[1];
	m_nBorderStyle[2] = pCell->m_nBorderStyle[2];
	m_nBorderStyle[3] = pCell->m_nBorderStyle[3];
	m_nBorderColor[0] = pCell->m_nBorderColor[0];
	m_nBorderColor[1] = pCell->m_nBorderColor[1];
	m_nBorderColor[2] = pCell->m_nBorderColor[2];
	m_nBorderColor[3] = pCell->m_nBorderColor[3];
	m_nBackgroundColor = pCell->m_nBackgroundColor;
	m_rectPosition[0] = pCell->m_rectPosition[0];
	m_rectPosition[1] = pCell->m_rectPosition[1];
	m_nMinHeight = pCell->m_nMinHeight;
	m_szSubTable = pCell->m_szSubTable;
	m_nControlID = pCell->m_nControlID;
	m_bActivated = pCell->m_bActivated;
	m_bEnabled = pCell->m_bEnabled;
	CopyMemory(&m_fntProperties, &pCell->m_fntProperties, sizeof(LOGFONT));
}

BOOL CTableViewCell::Compare(CONST CTableViewCell *pCell) CONST
{
	return((pCell->m_nFormat == m_nFormat  &&  pCell->GetText() == GetText() && pCell->m_nTextMode == m_nTextMode  &&  pCell->m_nTextColor[0] == m_nTextColor[0] && pCell->m_nTextColor[1] == m_nTextColor[1] && pCell->m_nBorderSize[0] == m_nBorderSize[0] && pCell->m_nBorderSize[1] == m_nBorderSize[1] && pCell->m_nBorderSize[2] == m_nBorderSize[2] && pCell->m_nBorderSize[3] == m_nBorderSize[3] && pCell->m_nBorderStyle[0] == m_nBorderStyle[0] && pCell->m_nBorderStyle[1] == m_nBorderStyle[1] && pCell->m_nBorderStyle[2] == m_nBorderStyle[2] && pCell->m_nBorderStyle[3] == m_nBorderStyle[3] && pCell->m_nBorderColor[0] == m_nBorderColor[0] && pCell->m_nBorderColor[1] == m_nBorderColor[1] && pCell->m_nBorderColor[2] == m_nBorderColor[2] && pCell->m_nBorderColor[3] == m_nBorderColor[3] && pCell->m_nBackgroundColor == m_nBackgroundColor  &&  pCell->m_rectPosition[0] == m_rectPosition[0] && pCell->m_rectPosition[1] == m_rectPosition[1] && pCell->m_nMinHeight == m_nMinHeight  &&  pCell->m_nControlID == m_nControlID  &&  pCell->m_szSubTable == m_szSubTable  &&  !memcmp(&pCell->m_fntProperties, &m_fntProperties, sizeof(LOGFONT)) && pCell->m_bActivated == m_bActivated  &&  pCell->m_bEnabled == m_bEnabled) ? (pCell->x == x  &&  pCell->y == y) : FALSE);
}

CRect CTableViewCell::CalcControlPosition(CWnd *pWnd)
{
	INT  nHeight;
	CRect  rPosition;

	if ((m_nFormat & TAS_TYPE_EDIT) || (m_nFormat & TAS_TYPE_DECNUMBEREDIT) || (m_nFormat & TAS_TYPE_RAWNUMBEREDIT))
	{
		for (rPosition = GetInnerPosition(), nHeight = CalcControlHeight(pWnd, FALSE); m_nFormat & TAS_ALIGN_VCENTER; )
		{
			rPosition.SetRect(rPosition.left, rPosition.top + (rPosition.Height() - nHeight) / 2, rPosition.right, rPosition.top + (rPosition.Height() - nHeight) / 2 + nHeight);
			break;
		}
		for (; m_nFormat & TAS_ALIGN_BOTTOM; )
		{
			rPosition.SetRect(rPosition.left, rPosition.bottom - nHeight, rPosition.right, rPosition.bottom);
			break;
		}
		for (; !(m_nFormat & TAS_ALIGN_VCENTER) && !(m_nFormat & TAS_ALIGN_BOTTOM); )
		{
			rPosition.SetRect(rPosition.left, rPosition.top, rPosition.right, rPosition.top + nHeight);
			break;
		}
		rPosition.OffsetRect(-pWnd->GetScrollPos(SB_HORZ), -pWnd->GetScrollPos(SB_VERT));
		return rPosition;
	}
	for (rPosition = GetInnerPosition(); (m_nFormat & TAS_TYPE_DPLEDIT) || (m_nFormat & TAS_TYPE_MDLEDIT) || (m_nFormat & TAS_TYPE_TPLEDIT) || (m_nFormat & TAS_TYPE_MULTILINEEDIT); )
	{
		rPosition.OffsetRect(-pWnd->GetScrollPos(SB_HORZ), -pWnd->GetScrollPos(SB_VERT));
		return rPosition;
	}
	if ((m_nFormat & TAS_TYPE_COMBOLISTBOX) || (m_nFormat & TAS_TYPE_COMBOEDITBOX) || (m_nFormat & TAS_TYPE_COMBOCOLORSBOX) || (m_nFormat & TAS_TYPE_COMBOLINESTYLESBOX) || (m_nFormat & TAS_TYPE_COMBOLINESYMBOLSBOX))
	{
		for (rPosition = GetInnerPosition(), nHeight = CalcControlHeight(pWnd); m_nFormat & TAS_ALIGN_VCENTER; )
		{
			rPosition.SetRect(rPosition.left, rPosition.top + (rPosition.Height() - nHeight) / 2, rPosition.right, rPosition.top + (rPosition.Height() - nHeight) / 2 + nHeight + 16 * CalcControlHeight(pWnd, FALSE));
			break;
		}
		for (; m_nFormat & TAS_ALIGN_BOTTOM; )
		{
			rPosition.SetRect(rPosition.left, rPosition.bottom - nHeight - 1, rPosition.right, rPosition.bottom + 16 * CalcControlHeight(pWnd, FALSE) - 1);
			break;
		}
		for (; !(m_nFormat & TAS_ALIGN_VCENTER) && !(m_nFormat & TAS_ALIGN_BOTTOM); )
		{
			rPosition.SetRect(rPosition.left, rPosition.top, rPosition.right, rPosition.top + nHeight + 16 * CalcControlHeight(pWnd, FALSE));
			break;
		}
		rPosition.OffsetRect(-pWnd->GetScrollPos(SB_HORZ), -pWnd->GetScrollPos(SB_VERT));
		return rPosition;
	}
	if ((m_nFormat & TAS_TYPE_SPINBOX) || (m_nFormat & TAS_TYPE_TIMESPINBOX))
	{
		for (rPosition = GetInnerPosition(), nHeight = CalcControlHeight(pWnd) + 1; m_nFormat & TAS_ALIGN_VCENTER; )
		{
			rPosition.SetRect(rPosition.left, rPosition.top + (rPosition.Height() - nHeight) / 2, rPosition.right, rPosition.top + (rPosition.Height() - nHeight) / 2 + nHeight);
			break;
		}
		for (; m_nFormat & TAS_ALIGN_BOTTOM; )
		{
			rPosition.SetRect(rPosition.left, rPosition.bottom - nHeight - 1, rPosition.right, rPosition.bottom - 1);
			break;
		}
		for (; !(m_nFormat & TAS_ALIGN_VCENTER) && !(m_nFormat & TAS_ALIGN_BOTTOM); )
		{
			rPosition.SetRect(rPosition.left, rPosition.top, rPosition.right, rPosition.top + nHeight);
			break;
		}
		rPosition.OffsetRect(-pWnd->GetScrollPos(SB_HORZ), -pWnd->GetScrollPos(SB_VERT));
		return rPosition;
	}
	return CRect(0, 0, 0, 0);
}

INT CTableViewCell::CalcControlHeight(CWnd *pWnd, BOOL bBorder)
{
	CDC  *pDC;
	INT  nHeight;
	CFont  cFont;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = pWnd->GetDC()))
	{
		if (cFont.CreateFontIndirect(&m_fntProperties))
		{
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				nHeight = (pDC->GetTextMetrics(&tmFont)) ? tmFont.tmHeight : 0;
				nHeight += (bBorder  &&  nHeight > 0) ? (2 * (GetSystemMetrics(SM_CYEDGE) + 1)) : 0;
				pDC->SelectObject(pOldFont);
				pWnd->ReleaseDC(pDC);
				cFont.DeleteObject();
				return nHeight;
			}
			cFont.DeleteObject();
		}
		pWnd->ReleaseDC(pDC);
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewCells

CTableViewCells::CTableViewCells() : CPtrArray()
{
	return;
}

CTableViewCells::~CTableViewCells()
{
	RemoveAll();
}

INT CTableViewCells::Add(CTableViewCell *pCell)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pCell->y, pCell->x, TRUE)) >= 0) InsertAt(nIndex, pCell, 1);
	return nIndex;
}

INT CTableViewCells::Find(INT nRow, INT nCol) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = (nRow >= 0 && nCol >= 0) ? GetAt((INT)GetSize() - 1) : (CTableViewCell *)NULL)) ? ((nRow <= pCell->y  &&  nCol <= pCell->x && (pCell->y + 1)*(pCell->x + 1) == (INT)GetSize()) ? (nRow*(pCell->x + 1) + nCol) : FindIndex(nRow, nCol)) : -1);
}
INT CTableViewCells::Find(CONST POINT &point) CONST
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (INT)GetSize(); nCell < nCells; nCell++)
	{
		if ((pCell = GetAt(nCell)) && pCell->GetPosition().PtInRect(point)) break;
		continue;
	}
	return((nCell < nCells) ? nCell : -1);
}

CTableViewCell *CTableViewCells::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTableViewCell *)CPtrArray::GetAt(nIndex) : (CTableViewCell *)NULL);
}

CTableViewCell *CTableViewCells::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTableViewCell *)CPtrArray::GetAt(nIndex) : (CTableViewCell *)NULL);
}

VOID CTableViewCells::RemoveAll()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)GetSize(); nIndex < nCount; nIndex++)
	{
		delete GetAt(nIndex);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTableViewCells::Copy(CONST CTableViewCells *pCells)
{
	INT  nIndex;
	INT  nCount;
	CTableViewCell  *pCell[2];

	for (nIndex = 0, nCount = (INT)pCells->GetSize(), RemoveAll(); nIndex < nCount; nIndex++)
	{
		if ((pCell[0] = pCells->GetAt(nIndex)))
		{
			if ((pCell[1] = new CTableViewCell))
			{
				pCell[1]->Copy(pCell[0]);
				SetAtGrow(nIndex, pCell[1]);
				continue;
			}
			RemoveAll();
			break;
		}
		SetAtGrow(nIndex, pCell[0]);
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTableViewCells::Compare(CONST CTableViewCells *pCells) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (pCells->GetSize() == GetSize()) ? (INT)pCells->GetSize() : -1; nIndex < nCount; nIndex++)
	{
		if (pCells->GetAt(nIndex)->Compare(GetAt(nIndex))) continue;
		break;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

INT CTableViewCells::FindIndex(INT nRow, INT nCol, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;
	CTableViewCell  *pCell;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (((pCell = GetAt(nIndex))->y == nRow  &&  pCell->x < nCol) || pCell->y < nRow)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return(((!bInsert && (pCell = GetAt(nIndex)) && pCell->y == nRow  &&  pCell->x == nCol) || (bInsert  &&  nIndex <= (INT)GetSize() && (!GetSize() || (((pCell = GetAt(max(nIndex - 1, 0))) && (pCell->y != nRow || pCell->x != nCol)) && ((pCell = GetAt(min(nIndex, (INT)GetUpperBound()))) && (pCell->y != nRow || pCell->x != nCol)))))) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewObject

CTableViewObject::CTableViewObject() : CRect()
{
	SetType(TAS_TABLE_NORMAL);
	SetRectEmpty();
	SetSelCell();
	SetSelColor(GetSysColor(COLOR_3DFACE));
	SetFloatingAlignment();
	EnableResize(FALSE);
	MakeVisible(TRUE);
}

CTableViewObject::~CTableViewObject()
{
	m_pCells.RemoveAll();
}

VOID CTableViewObject::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTableViewObject::GetName() CONST
{
	return m_szName;
}

VOID CTableViewObject::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CTableViewObject::GetTitle() CONST
{
	return m_szTitle;
}

BOOL CTableViewObject::HasTitle() CONST
{
	return !m_szTitle.IsEmpty();
}

VOID CTableViewObject::SetType(UINT nType)
{
	m_nType = nType;
}

UINT CTableViewObject::GetType() CONST
{
	return m_nType;
}

BOOL CTableViewObject::InsertRow(INT nRow)
{
	INT  nCol;
	INT  nCols;
	INT  nCell;
	INT  nCells;
	CRect  rCell;
	CTableViewCell  *pCell[2];
	LOGFONT  lfFont;

	if (nRow <= GetRows())
	{
		for (nCell = (m_pCells.Find(nRow, 0) < 0) ? (INT)m_pCells.GetCount() : 0, nCells = (INT)m_pCells.GetCount(); nCell < nCells; nCell++)
		{
			if ((pCell[0] = m_pCells.GetAt(nCell)) && pCell[0]->y >= nRow)
			{
				pCell[0]->y++;
				continue;
			}
		}
		for (nCol = 0, nCols = GetColumns(); nCol < nCols; nCol++)
		{
			if ((pCell[0] = m_pCells.GetAt(m_pCells.Find(nRow + 1, nCol))))
			{
				if ((pCell[1] = new CTableViewCell))
				{
					rCell = pCell[0]->GetPosition();
					pCell[0]->GetFont(&lfFont);
					pCell[1]->x = nCol;
					pCell[1]->y = nRow;
					pCell[1]->SetFont(&lfFont);
					pCell[1]->SetPosition(CRect(rCell.left, rCell.top, rCell.right, rCell.top));
					if (m_pCells.Add(pCell[1]) < 0)
					{
						delete pCell[1];
						break;
					}
					continue;
				}
				break;
			}
			if ((pCell[0] = m_pCells.GetAt(m_pCells.Find(nRow - 1, nCol))))
			{
				if ((pCell[1] = new CTableViewCell))
				{
					rCell = pCell[0]->GetPosition();
					pCell[0]->GetFont(&lfFont);
					pCell[1]->x = nCol;
					pCell[1]->y = nRow;
					pCell[1]->SetFont(&lfFont);
					pCell[1]->SetPosition(CRect(rCell.left, rCell.bottom, rCell.right, rCell.bottom));
					if (m_pCells.Add(pCell[1]) < 0)
					{
						delete pCell[1];
						break;
					}
					continue;
				}
				break;
			}
			if ((pCell[1] = new CTableViewCell))
			{
				pCell[1]->x = nCol;
				pCell[1]->y = nRow;
				if (m_pCells.Add(pCell[1]) < 0)
				{
					delete pCell[1];
					break;
				}
				continue;
			}
			break;
		}
		if (nCol == nCols)
		{
			m_ptSel.y = (m_ptSel.y >= nRow) ? (m_ptSel.y + 1) : m_ptSel.y;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTableViewObject::RemoveRow(INT nRow)
{
	INT  nCol;
	INT  nCols;
	INT  nCell;
	INT  nCells;
	INT  nIndex;
	INT  nOffset;
	CRect  rCell;
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = GetColumns(), nOffset = 0; nCol < nCols; nCol++)
	{
		if ((pCell = m_pCells.GetAt((nIndex = m_pCells.Find(nRow, nCol)))))
		{
			nOffset = (!nCol) ? pCell->GetPosition().Height() : nOffset;
			m_pCells.RemoveAt(nIndex);
			delete pCell;
			continue;
		}
		break;
	}
	for (nCell = m_pCells.Find(nRow + 1, 0), nCells = (INT)m_pCells.GetSize(); (pCell = (nCell < nCells) ? m_pCells.GetAt(nCell) : (CTableViewCell *)NULL); nCell++)
	{
		for (rCell = pCell->GetPosition(), rCell.OffsetRect(0, -nOffset), pCell->SetPosition(rCell); pCell->HasInnerPosition(); )
		{
			rCell = pCell->GetInnerPosition();
			rCell.OffsetRect(0, -nOffset);
			pCell->SetInnerPosition(rCell);
			break;
		}
		pCell->y--;
	}
	if (nCell == nCells || nCell < 0)
	{
		if (m_ptSel.x >= 0 && m_ptSel.y >= 0)
		{
			if (m_ptSel.y == nRow)
			{
				m_ptSel.x = -1;
				m_ptSel.y = -1;
				return TRUE;
			}
			if (m_ptSel.y > nRow)
			{
				m_ptSel.y = m_ptSel.y - 1;
				return TRUE;
			}
		}
		m_ptSel.y = (m_ptSel.y >= nRow) ? ((m_ptSel.y > nRow) ? (m_ptSel.y - 1) : -1) : m_ptSel.y;
		return TRUE;
	}
	return FALSE;
}

INT CTableViewObject::GetRows() CONST
{
	CTableViewCell  *pCell;

	return(((pCell = m_pCells.GetAt((INT)m_pCells.GetUpperBound()))) ? (pCell->y + 1) : 0);
}

BOOL CTableViewObject::InsertColumn(INT nCol)
{
	INT  nRow;
	INT  nRows;
	INT  nCell;
	INT  nCells;
	CRect  rCell;
	CTableViewCell  *pCell[2];
	LOGFONT  lfFont;

	if (nCol <= GetColumns())
	{
		for (nCell = (m_pCells.Find(0, nCol) < 0) ? (INT)m_pCells.GetCount() : 0, nCells = (INT)m_pCells.GetCount(); nCell < nCells; nCell++)
		{
			if ((pCell[0] = m_pCells.GetAt(nCell)) && pCell[0]->x >= nCol)
			{
				pCell[0]->x++;
				continue;
			}
		}
		for (nRow = 0, nRows = GetRows(); nRow < nRows; nRow++)
		{
			if ((pCell[0] = m_pCells.GetAt(m_pCells.Find(nRow, nCol + 1))))
			{
				if ((pCell[1] = new CTableViewCell))
				{
					rCell = pCell[0]->GetPosition();
					pCell[0]->GetFont(&lfFont);
					pCell[1]->x = nCol;
					pCell[1]->y = nRow;
					pCell[1]->SetFont(&lfFont);
					pCell[1]->SetPosition(CRect(rCell.left, rCell.top, rCell.left, rCell.bottom));
					if (m_pCells.Add(pCell[1]) < 0)
					{
						delete pCell[1];
						break;
					}
					continue;
				}
				break;
			}
			if ((pCell[0] = m_pCells.GetAt(m_pCells.Find(nRow, nCol - 1))))
			{
				if ((pCell[1] = new CTableViewCell))
				{
					rCell = pCell[0]->GetPosition();
					pCell[0]->GetFont(&lfFont);
					pCell[1]->x = nCol;
					pCell[1]->y = nRow;
					pCell[1]->SetFont(&lfFont);
					pCell[1]->SetPosition(CRect(rCell.right, rCell.top, rCell.right, rCell.bottom));
					if (m_pCells.Add(pCell[1]) < 0)
					{
						delete pCell[1];
						break;
					}
					continue;
				}
				break;
			}
			if ((pCell[1] = new CTableViewCell))
			{
				pCell[1]->x = nCol;
				pCell[1]->y = nRow;
				if (m_pCells.Add(pCell[1]) < 0)
				{
					delete pCell[1];
					break;
				}
				continue;
			}
			break;
		}
		if (nRow == nRows)
		{
			m_ptSel.x = (m_ptSel.x >= nCol) ? (m_ptSel.x + 1) : m_ptSel.x;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTableViewObject::RemoveColumn(INT nCol)
{
	INT  nRow;
	INT  nRows;
	INT  nCell;
	INT  nCells;
	INT  nIndex;
	INT  nOffset;
	CRect  rCell;
	CTableViewCell  *pCell;

	for (nRow = 0, nRows = ((nOffset = ((pCell = m_pCells.GetAt(m_pCells.Find(0, nCol)))) ? pCell->GetPosition().Width() : 0) != 0) ? GetRows() : -1; nRow < nRows; nRow++)
	{
		for (nCell = (nIndex = m_pCells.Find(nRow, nCol)) + 1, nCells = (INT)m_pCells.GetSize(); (pCell = (nCell < nCells) ? m_pCells.GetAt(nCell) : (CTableViewCell *)NULL) && pCell->y == nRow; nCell++)
		{
			for (rCell = pCell->GetPosition(), rCell.OffsetRect(-nOffset, 0), pCell->SetPosition(rCell); pCell->HasInnerPosition(); )
			{
				rCell = pCell->GetInnerPosition();
				rCell.OffsetRect(-nOffset, 0);
				pCell->SetInnerPosition(rCell);
				break;
			}
			pCell->x--;
		}
		delete m_pCells.GetAt(nIndex);
		m_pCells.RemoveAt(nIndex);
	}
	if (nRow == nRows)
	{
		if (m_ptSel.x >= 0 && m_ptSel.y >= 0)
		{
			if (m_ptSel.x == nCol)
			{
				m_ptSel.x = -1;
				m_ptSel.y = -1;
				return TRUE;
			}
			if (m_ptSel.x > nCol)
			{
				m_ptSel.x = m_ptSel.x - 1;
				return TRUE;
			}
		}
		m_ptSel.x = (m_ptSel.x >= nCol) ? ((m_ptSel.x > nCol) ? (m_ptSel.x - 1) : -1) : m_ptSel.x;
		return TRUE;
	}
	return FALSE;
}

INT CTableViewObject::GetColumns() CONST
{
	CTableViewCell  *pCell;

	return(((pCell = m_pCells.GetAt((INT)m_pCells.GetUpperBound()))) ? (pCell->x + 1) : 0);
}

BOOL CTableViewObject::SetRowHeight(INT nRow, INT nHeight)
{
	INT  nCell;
	INT  nCells;
	INT  nOffset;
	CRect  rCell[2];
	CTableViewCell  *pCell;

	for (nCell = (nRow >= 0) ? m_pCells.Find(nRow, 0) : 0, nCells = (nRow >= -1 && nRow < GetRows()) ? (INT)m_pCells.GetSize() : -1, nOffset = 0; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)))
		{
			if (pCell->y == nRow  &&  nRow >= 0)
			{
				rCell[0] = pCell->GetPosition();
				rCell[0].InflateRect(0, 0, 0, (nOffset = nHeight - rCell[0].Height()));
				pCell->SetPosition(rCell[0]);
				if (pCell->HasInnerPosition())
				{
					rCell[1] = pCell->GetInnerPosition();
					rCell[1].InflateRect(0, 0, 0, nOffset);
					pCell->SetInnerPosition(rCell[1]);
				}
				continue;
			}
			if (pCell->y > nRow  &&  nRow >= 0)
			{
				rCell[0] = pCell->GetPosition();
				rCell[0].OffsetRect(0, nOffset);
				pCell->SetPosition(rCell[0]);
				if (pCell->HasInnerPosition())
				{
					rCell[1] = pCell->GetInnerPosition();
					rCell[1].OffsetRect(0, nOffset);
					pCell->SetInnerPosition(rCell[1]);
				}
				continue;
			}
			if (nRow < 0)
			{
				for (rCell[0] = (!pCell->y) ? pCell->GetPosition() : rCell[0], rCell[1] = (!pCell->y) ? pCell->GetInnerPosition() : rCell[1], pCell->SetPosition(CRect(rCell[0].left, rCell[0].top + pCell->y*nHeight, rCell[0].right, rCell[0].top + (pCell->y + 1)*nHeight)); pCell->HasInnerPosition(); )
				{
					pCell->SetInnerPosition(CRect(rCell[1].left, rCell[1].top + pCell->y*nHeight, rCell[1].right, rCell[1].top + (pCell->y + 1)*nHeight));
					break;
				}
				continue;
			}
		}
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

BOOL CTableViewObject::SetRowFormat(INT nRow, UINT nFormat)
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = (nRow >= 0) ? m_pCells.Find(nRow, 0) : 0, nCells = (nRow >= -1 && nRow < GetRows()) ? (INT)m_pCells.GetSize() : -1; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->y == nRow)
		{
			pCell->SetFormat(nFormat);
			continue;
		}
		break;
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

BOOL CTableViewObject::SetRowFont(INT nRow, CONST LOGFONT *plfFont)
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = (nRow >= 0) ? m_pCells.Find(nRow, 0) : 0, nCells = (nRow >= -1 && nRow < GetRows()) ? (INT)m_pCells.GetSize() : -1; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->y == nRow)
		{
			pCell->SetFont(plfFont);
			continue;
		}
		break;
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

BOOL CTableViewObject::SetRowBackgroundColor(INT nRow, COLORREF nColor)
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = (nRow >= 0) ? m_pCells.Find(nRow, 0) : 0, nCells = (nRow >= -1 && nRow < GetRows()) ? (INT)m_pCells.GetSize() : -1; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->y == nRow)
		{
			pCell->SetBackgroundColor(nColor);
			continue;
		}
		break;
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

BOOL CTableViewObject::SetColumnWidth(INT nCol, INT nWidth)
{
	INT  nCell;
	INT  nCells;
	INT  nOffset;
	CRect  rCell[2];
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (nCol >= -1 && nCol < GetColumns()) ? (INT)m_pCells.GetSize() : -1, nOffset = 0; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)))
		{
			if (pCell->x == nCol  &&  nCol >= 0)
			{
				rCell[0] = pCell->GetPosition();
				if ((nOffset = nWidth - rCell[0].Width()) != 0)
				{
					rCell[0].InflateRect(0, 0, nOffset, 0);
					pCell->SetPosition(rCell[0]);
					if (pCell->HasInnerPosition())
					{
						rCell[1] = pCell->GetInnerPosition();
						rCell[1].InflateRect(0, 0, nOffset, 0);
						pCell->SetInnerPosition(rCell[1]);
					}
					continue;
				}
				break;
			}
			if (pCell->x > nCol  &&  nCol >= 0)
			{
				rCell[0] = pCell->GetPosition();
				rCell[0].OffsetRect(nOffset, 0);
				pCell->SetPosition(rCell[0]);
				if (pCell->HasInnerPosition())
				{
					rCell[1] = pCell->GetInnerPosition();
					rCell[1].OffsetRect(nOffset, 0);
					pCell->SetInnerPosition(rCell[1]);
				}
				continue;
			}
			if (nCol < 0)
			{
				for (rCell[0] = (!pCell->x) ? pCell->GetPosition() : rCell[0], rCell[1] = (!pCell->x) ? pCell->GetInnerPosition() : rCell[1], pCell->SetPosition(CRect(rCell[0].left + pCell->x*nWidth, rCell[0].top, rCell[0].left + (pCell->x + 1)*nWidth, rCell[0].bottom)); pCell->HasInnerPosition(); )
				{
					pCell->SetPosition(CRect(rCell[1].left + pCell->x*nWidth, rCell[1].top, rCell[1].left + (pCell->x + 1)*nWidth, rCell[1].bottom));
					break;
				}
			}
		}
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

BOOL CTableViewObject::SetColumnFormat(INT nCol, UINT nFormat)
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (nCol >= -1 && nCol < GetColumns()) ? (INT)m_pCells.GetSize() : -1; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->x == nCol)
		{
			pCell->SetFormat(nFormat);
			continue;
		}
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

BOOL CTableViewObject::SetColumnFont(INT nCol, CONST LOGFONT *plfFont)
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (nCol >= -1 && nCol < GetColumns()) ? (INT)m_pCells.GetSize() : -1; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->x == nCol)
		{
			pCell->SetFont(plfFont);
			continue;
		}
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

BOOL CTableViewObject::SetColumnBackgroundColor(INT nCol, COLORREF nColor)
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (nCol >= -1 && nCol < GetColumns()) ? (INT)m_pCells.GetSize() : -1; nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->x == nCol)
		{
			pCell->SetBackgroundColor(nColor);
			continue;
		}
	}
	return((nCells >= 0) ? TRUE : FALSE);
}

VOID CTableViewObject::SetOuterBorder(INT nSize, INT nStyle, COLORREF nColor)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = GetColumns(), nRows = GetRows(); nCol < nCols; nCol++)
	{
		if ((pCell = m_pCells.GetAt(m_pCells.Find(0, nCol)))) pCell->SetBorder(TAS_BORDER_TOP, nSize, nStyle, nColor);
		if ((pCell = m_pCells.GetAt(m_pCells.Find(nRows - 1, nCol)))) pCell->SetBorder(TAS_BORDER_BOTTOM, nSize, nStyle, nColor);
	}
	for (nRow = 0; nRow < nRows; nRow++)
	{
		if ((pCell = m_pCells.GetAt(m_pCells.Find(nRow, 0)))) pCell->SetBorder(TAS_BORDER_LEFT, nSize, nStyle, nColor);
		if ((pCell = m_pCells.GetAt(m_pCells.Find(nRow, nCols - 1)))) pCell->SetBorder(TAS_BORDER_RIGHT, nSize, nStyle, nColor);
	}
}

VOID CTableViewObject::SetInnerBorder(INT nSize, INT nStyle, COLORREF nColor)
{
	INT  nRows;
	INT  nCols;
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (INT)m_pCells.GetSize(), nRows = GetRows(), nCols = GetColumns(); nCell < nCells; nCell++)
	{
		if ((pCell = (CTableViewCell *)m_pCells.GetAt(nCell)) != (CTableViewCell *)NULL)
		{
			if (pCell->x > 0) pCell->SetBorder(TAS_BORDER_LEFT, nSize, nStyle, nColor);
			if (pCell->y > 0) pCell->SetBorder(TAS_BORDER_TOP, nSize, nStyle, nColor);
			if (pCell->x < nCols - 1) pCell->SetBorder(TAS_BORDER_RIGHT, nSize, nStyle, nColor);
			if (pCell->y < nRows - 1) pCell->SetBorder(TAS_BORDER_BOTTOM, nSize, nStyle, nColor);
		}
	}
}

VOID CTableViewObject::SetInnerMargin(UINT nSide, INT nMargin)
{
	INT  nCell;
	INT  nCells;
	CRect  rCell;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (INT)m_pCells.GetSize(); nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) != (CTableViewCell *)NULL)
		{
			for (rCell = pCell->GetPosition(); nSide & TAS_BORDER_LEFT; )
			{
				rCell.left += nMargin;
				break;
			}
			for (; nSide & TAS_BORDER_TOP; )
			{
				rCell.top += nMargin;
				break;
			}
			for (; nSide & TAS_BORDER_RIGHT; )
			{
				rCell.right -= nMargin;
				break;
			}
			for (; nSide & TAS_BORDER_BOTTOM; )
			{
				rCell.bottom -= nMargin;
				break;
			}
			pCell->SetInnerPosition(rCell);
		}
	}
}

BOOL CTableViewObject::SetSelRow(INT nRow)
{
	if (nRow <= GetRows() && nRow >= -1)
	{
		m_ptSel.y = nRow;
		m_ptSel.x = -1;
		return TRUE;
	}
	return FALSE;
}

INT CTableViewObject::GetSelRow() CONST
{
	return((m_ptSel.x == -1) ? m_ptSel.y : -1);
}

BOOL CTableViewObject::SetSelColumn(INT nCol)
{
	if (nCol <= GetColumns() && nCol >= -1)
	{
		m_ptSel.x = nCol;
		m_ptSel.y = -1;
		return TRUE;
	}
	return FALSE;
}

INT CTableViewObject::GetSelColumn() CONST
{
	return((m_ptSel.y == -1) ? m_ptSel.x : -1);
}

BOOL CTableViewObject::SetSelCell(INT nRow, INT nCol)
{
	if (nRow <= GetRows() && nCol <= GetColumns())
	{
		m_ptSel.x = nCol;
		m_ptSel.y = nRow;
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewObject::GetSelCell(INT &nRow, INT &nCol) CONST
{
	nCol = m_ptSel.x;
	nRow = m_ptSel.y;
	return((nRow != -1 && nCol != -1) ? TRUE : FALSE);
}

VOID CTableViewObject::SetSelColor(COLORREF nColor)
{
	m_nSelColor = nColor;
}

COLORREF CTableViewObject::GetSelColor() CONST
{
	return m_nSelColor;
}

VOID CTableViewObject::SetFloatingAlignment(INT nAlignment)
{
	m_nFloatingAlignment = nAlignment;
}

INT CTableViewObject::GetFloatingAlignment() CONST
{
	return m_nFloatingAlignment;
}

BOOL CTableViewObject::SetCells(CONST CTableViewCells &pCells)
{
	return m_pCells.Copy(&pCells);
}

INT CTableViewObject::GetCells(CTableViewCells &pCells) CONST
{
	return((pCells.Copy(&m_pCells)) ? (INT)pCells.GetSize() : -1);
}

INT CTableViewObject::GetCellCount() CONST
{
	return((INT)m_pCells.GetSize());
}

VOID CTableViewObject::OffsetCells(CONST SIZE &size)
{
	OffsetCells(size.cx, size.cy);
}
VOID CTableViewObject::OffsetCells(INT dx, INT dy)
{
	INT  nCell;
	INT  nCells;
	CRect  rCell[2];
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (INT)m_pCells.GetSize(); nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) != (CTableViewCell *)NULL)
		{
			for (rCell[0] = pCell->GetPosition(), rCell[1] = pCell->GetInnerPosition(), rCell[0].OffsetRect(dx, dy), pCell->SetPosition(rCell[0]); pCell->HasInnerPosition(); )
			{
				pCell->SetInnerPosition(CRect(rCell[1].left + dx, rCell[1].top + dy, rCell[1].right + dx, rCell[1].bottom + dy));
				break;
			}
		}
	}
}

CRect CTableViewObject::GetCellsBounds() CONST
{
	CRect  rCells;
	CTableViewCell  *pCell[2];

	if ((pCell[0] = FindCell(0, 0)))
	{
		if ((pCell[1] = FindCell(GetRows() - 1, GetColumns() - 1)))
		{
			rCells.SetRect(pCell[0]->GetPosition().left, pCell[0]->GetPosition().top, pCell[1]->GetPosition().right, pCell[1]->GetPosition().bottom);
			return rCells;
		}
	}
	return CRect(0, 0, 0, 0);
}

BOOL CTableViewObject::SetCellText(INT nRow, INT nCol, LPCTSTR pszText)
{
	CTableViewCell  *pCell;

	if ((pCell = FindCell(nRow, nCol)))
	{
		pCell->SetText(pszText);
		return TRUE;
	}
	return FALSE;
}
BOOL CTableViewObject::SetCellText(CONST POINT &point, LPCTSTR pszText)
{
	CTableViewCell  *pCell;

	if ((pCell = FindCell(point)))
	{
		pCell->SetText(pszText);
		return TRUE;
	}
	return FALSE;
}
BOOL CTableViewObject::SetCellText(UINT nControlID, LPCTSTR pszText)
{
	CTableViewCell  *pCell;

	if ((pCell = FindCell(nControlID)))
	{
		pCell->SetText(pszText);
		return TRUE;
	}
	return FALSE;
}
BOOL CTableViewObject::SetCellText(LPCTSTR pszRow, LPCTSTR pszColumn, LPCTSTR pszText)
{
	CTableViewCell  *pCell;

	if ((pCell = FindCell(pszRow, pszColumn)))
	{
		pCell->SetText(pszText);
		return TRUE;
	}
	return FALSE;
}
BOOL CTableViewObject::SetCellText(LPCTSTR pszRow, INT nCol, LPCTSTR pszText)
{
	CTableViewCell  *pCell;

	if ((pCell = FindCell(pszRow, nCol)))
	{
		pCell->SetText(pszText);
		return TRUE;
	}
	return FALSE;
}
BOOL CTableViewObject::SetCellText(INT nRow, LPCTSTR pszColumn, LPCTSTR pszText)
{
	CTableViewCell  *pCell;

	if ((pCell = FindCell(nRow, pszColumn)))
	{
		pCell->SetText(pszText);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewObject::TranslateCellText(INT nRow, INT nCol, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, nCol))) ? pCell->TranslateText(pszText, sValue) : FALSE);
}
BOOL CTableViewObject::TranslateCellText(CONST POINT &point, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(point))) ? pCell->TranslateText(pszText, sValue) : FALSE);
}
BOOL CTableViewObject::TranslateCellText(UINT nControlID, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nControlID))) ? pCell->TranslateText(pszText, sValue) : FALSE);
}
BOOL CTableViewObject::TranslateCellText(LPCTSTR pszRow, LPCTSTR pszColumn, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, pszColumn))) ? pCell->TranslateText(pszText, sValue) : FALSE);
}
BOOL CTableViewObject::TranslateCellText(LPCTSTR pszRow, INT nCol, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, nCol))) ? pCell->TranslateText(pszText, sValue) : FALSE);
}
BOOL CTableViewObject::TranslateCellText(INT nRow, LPCTSTR pszColumn, LPCTSTR pszText, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, pszColumn))) ? pCell->TranslateText(pszText, sValue) : FALSE);
}

CString CTableViewObject::GetCellText(INT nRow, INT nCol) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, nCol))) ? pCell->GetText() : EMPTYSTRING);
}
CString CTableViewObject::GetCellText(CONST POINT &point) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(point))) ? pCell->GetText() : EMPTYSTRING);
}
CString CTableViewObject::GetCellText(UINT nControlID) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nControlID))) ? pCell->GetText() : EMPTYSTRING);
}
CString CTableViewObject::GetCellText(LPCTSTR pszRow, LPCTSTR pszColumn) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, pszColumn))) ? pCell->GetText() : EMPTYSTRING);
}
CString CTableViewObject::GetCellText(LPCTSTR pszRow, INT nCol) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, nCol))) ? pCell->GetText() : EMPTYSTRING);
}
CString CTableViewObject::GetCellText(INT nRow, LPCTSTR pszColumn) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, pszColumn))) ? pCell->GetText() : EMPTYSTRING);
}

BOOL CTableViewObject::SetCellValue(INT nRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue)
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, nCol))) ? pCell->SetValue(sValue) : FALSE);
}
BOOL CTableViewObject::SetCellValue(CONST POINT &point, CONST TABLEVIEWCELLVALUE &sValue)
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(point))) ? pCell->SetValue(sValue) : FALSE);
}
BOOL CTableViewObject::SetCellValue(UINT nControlID, CONST TABLEVIEWCELLVALUE &sValue)
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nControlID))) ? pCell->SetValue(sValue) : FALSE);
}
BOOL CTableViewObject::SetCellValue(LPCTSTR pszRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue)
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, pszColumn))) ? pCell->SetValue(sValue) : FALSE);
}
BOOL CTableViewObject::SetCellValue(LPCTSTR pszRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue)
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, nCol))) ? pCell->SetValue(sValue) : FALSE);
}
BOOL CTableViewObject::SetCellValue(INT nRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue)
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, pszColumn))) ? pCell->SetValue(sValue) : FALSE);
}

BOOL CTableViewObject::TranslateCellValue(INT nRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, nCol))) ? pCell->TranslateValue(sValue, szText) : FALSE);
}
BOOL CTableViewObject::TranslateCellValue(CONST POINT &point, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(point))) ? pCell->TranslateValue(sValue, szText) : FALSE);
}
BOOL CTableViewObject::TranslateCellValue(UINT nControlID, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nControlID))) ? pCell->TranslateValue(sValue, szText) : FALSE);
}
BOOL CTableViewObject::TranslateCellValue(LPCTSTR pszRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, pszColumn))) ? pCell->TranslateValue(sValue, szText) : FALSE);
}
BOOL CTableViewObject::TranslateCellValue(LPCTSTR pszRow, INT nCol, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, nCol))) ? pCell->TranslateValue(sValue, szText) : FALSE);
}
BOOL CTableViewObject::TranslateCellValue(INT nRow, LPCTSTR pszColumn, CONST TABLEVIEWCELLVALUE &sValue, CString &szText) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, pszColumn))) ? pCell->TranslateValue(sValue, szText) : FALSE);
}

BOOL CTableViewObject::GetCellValue(INT nRow, INT nCol, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, nCol))) ? pCell->GetValue(sValue) : FALSE);
}
BOOL CTableViewObject::GetCellValue(CONST POINT &point, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(point))) ? pCell->GetValue(sValue) : FALSE);
}
BOOL CTableViewObject::GetCellValue(UINT nControlID, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nControlID))) ? pCell->GetValue(sValue) : FALSE);
}
BOOL CTableViewObject::GetCellValue(LPCTSTR pszRow, LPCTSTR pszColumn, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, pszColumn))) ? pCell->GetValue(sValue) : FALSE);
}
BOOL CTableViewObject::GetCellValue(LPCTSTR pszRow, INT nCol, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(pszRow, nCol))) ? pCell->GetValue(sValue) : FALSE);
}
BOOL CTableViewObject::GetCellValue(INT nRow, LPCTSTR pszColumn, TABLEVIEWCELLVALUE &sValue) CONST
{
	CTableViewCell  *pCell;

	return(((pCell = FindCell(nRow, pszColumn))) ? pCell->GetValue(sValue) : FALSE);
}

BOOL CTableViewObject::SetCellBorder(INT nCol, INT nRow, UINT nSide, INT nSize, INT nStyle, COLORREF nColor)
{
	CTableViewCell  *pCell[2];

	if ((pCell[0] = FindCell(nRow, nCol)))
	{
		for (pCell[0]->SetBorder(nSide, nSize, nStyle, nColor); (nSide & TAS_BORDER_LEFT) && nCol > 0; )
		{
			if ((pCell[1] = FindCell(nRow, nCol - 1))) pCell[1]->SetBorder(TAS_BORDER_RIGHT, nSize, nStyle, nColor);
			break;
		}
		for (; (nSide & TAS_BORDER_RIGHT) && nCol < GetColumns() - 1; )
		{
			if ((pCell[1] = FindCell(nRow, nCol + 1))) pCell[1]->SetBorder(TAS_BORDER_LEFT, nSize, nStyle, nColor);
			break;
		}
		for (; (nSide & TAS_BORDER_TOP) && nRow > 0; )
		{
			if ((pCell[1] = FindCell(nRow - 1, nCol))) pCell[1]->SetBorder(TAS_BORDER_BOTTOM, nSize, nStyle, nColor);
			break;
		}
		for (; (nSide & TAS_BORDER_BOTTOM) && nRow < GetRows() - 1; )
		{
			if ((pCell[1] = FindCell(nRow + 1, nCol))) pCell[1]->SetBorder(TAS_BORDER_TOP, nSize, nStyle, nColor);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewObject::GetCellBorder(INT nCol, INT nRow, UINT nSide, INT &nSize, INT &nStyle, COLORREF &nColor) CONST
{
	CTableViewCell  *pCell[2];

	if ((pCell[0] = FindCell(nRow, nCol)))
	{
		for (pCell[0]->GetBorder(nSide, nSize, nStyle, nColor); (nSide & TAS_BORDER_LEFT) && nCol > 0; )
		{
			if ((pCell[1] = FindCell(nRow, nCol - 1))) pCell[1]->GetBorder(TAS_BORDER_RIGHT, nSize, nStyle, nColor);
			break;
		}
		for (; (nSide & TAS_BORDER_RIGHT) && nCol < GetColumns() - 1; )
		{
			if ((pCell[1] = FindCell(nRow, nCol + 1))) pCell[1]->GetBorder(TAS_BORDER_LEFT, nSize, nStyle, nColor);
			break;
		}
		for (; (nSide & TAS_BORDER_TOP) && nRow > 0; )
		{
			if ((pCell[1] = FindCell(nRow - 1, nCol))) pCell[1]->GetBorder(TAS_BORDER_BOTTOM, nSize, nStyle, nColor);
			break;
		}
		for (; (nSide & TAS_BORDER_BOTTOM) && nRow < GetRows() - 1; )
		{
			if ((pCell[1] = FindCell(nRow + 1, nCol))) pCell[1]->GetBorder(TAS_BORDER_TOP, nSize, nStyle, nColor);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

CTableViewCell *CTableViewObject::FindCell(INT nRow, INT nCol) CONST
{
	return m_pCells.GetAt(m_pCells.Find(nRow, nCol));
}
CTableViewCell *CTableViewObject::FindCell(CONST POINT &point) CONST
{
	CRect  rCells;
	CTableViewCell  *pCell;

	if (!(pCell = m_pCells.GetAt(m_pCells.Find(point))))
	{
		for (rCells = GetCellsBounds(); rCells.right == point.x; )
		{
			if ((pCell = FindCell(CPoint(point.x - 1, point.y)))) return pCell;
			break;
		}
		for (; rCells.bottom == point.y; )
		{
			if ((pCell = FindCell(CPoint(point.x, point.y - 1)))) return pCell;
			break;
		}
		for (; rCells.right == point.x && rCells.bottom == point.y; )
		{
			if ((pCell = FindCell(CPoint(point.x - 1, point.y - 1)))) return pCell;
			break;
		}
		return((CTableViewCell *)NULL);
	}
	return pCell;

}
CTableViewCell *CTableViewObject::FindCell(CWnd *pControl) CONST
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (INT)m_pCells.GetSize(); nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->GetControl() == pControl) break;
		continue;
	}
	return((nCell < nCells) ? m_pCells.GetAt(nCell) : (CTableViewCell *)NULL);
}
CTableViewCell *CTableViewObject::FindCell(UINT nControlID) CONST
{
	INT  nCell;
	INT  nCells;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (INT)m_pCells.GetSize(); nCell < nCells; nCell++)
	{
		if ((pCell = m_pCells.GetAt(nCell)) && pCell->GetControlID() == nControlID) break;
		continue;
	}
	return((nCell < nCells) ? m_pCells.GetAt(nCell) : (CTableViewCell *)NULL);
}
CTableViewCell *CTableViewObject::FindCell(LPCTSTR pszRow, LPCTSTR pszColumn) CONST
{
	INT  nCol;
	INT  nRow;
	INT  nCols;
	INT  nRows;
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = (GetType() == TAS_TABLE_NORMAL) ? GetColumns() : 0; nCol < nCols; nCol++)
	{
		if ((pCell = FindCell(0, nCol)) && pCell->GetText() == pszColumn) break;
		continue;
	}
	for (nRow = 0, nRows = (GetType() == TAS_TABLE_NORMAL) ? GetRows() : 0; nRow < nRows; nRow++)
	{
		if ((pCell = FindCell(nRow, 0)) && pCell->GetText() == pszRow) break;
		continue;
	}
	return((nCol < nCols  &&  nRow < nRows) ? FindCell(nRow, nCol) : (CTableViewCell *)NULL);
}
CTableViewCell *CTableViewObject::FindCell(LPCTSTR pszRow, INT nCol) CONST
{
	INT  nRow;
	INT  nRows;
	CTableViewCell  *pCell;

	for (nRow = 0, nRows = (GetType() == TAS_TABLE_NORMAL) ? GetRows() : 0; nRow < nRows; nRow++)
	{
		if ((pCell = FindCell(nRow, 0)) && pCell->GetText() == pszRow) break;
		continue;
	}
	return((nRow < nRows) ? FindCell(nRow, nCol) : (CTableViewCell *)NULL);
}
CTableViewCell *CTableViewObject::FindCell(INT nRow, LPCTSTR pszColumn) CONST
{
	INT  nCol;
	INT  nCols;
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = (GetType() == TAS_TABLE_LIST) ? GetColumns() : 0; nCol < nCols; nCol++)
	{
		if ((pCell = FindCell(0, nCol)) && pCell->GetText() == pszColumn) break;
		continue;
	}
	return((nCol < nCols) ? FindCell(nRow, nCol) : (CTableViewCell *)NULL);
}
CTableViewCell *CTableViewObject::FindCell(INT nIndex) CONST
{
	return m_pCells.GetAt(nIndex);
}

VOID CTableViewObject::EnableResize(BOOL bEnable)
{
	m_bResize = bEnable;
}

BOOL CTableViewObject::IsResizeEnabled() CONST
{
	return m_bResize;
}

VOID CTableViewObject::MakeVisible(BOOL bEnable)
{
	INT  nCell;
	INT  nCells;
	CWnd  *pControl;
	CTableView  *pView;
	CTableViewCell  *pCell;

	for (nCell = 0, nCells = (!(m_bVisible = bEnable)) ? (INT)m_pCells.GetSize() : 0; nCell < nCells; nCell++)
	{
		if ((pControl = ((pCell = m_pCells.GetAt(nCell))) ? pCell->GetControl() : (CWnd *)NULL) != (CWnd *)NULL)
		{
			if ((pView = (IsWindow(pControl->GetSafeHwnd())) ? (CTableView *)pControl->GetParent() : (CTableView *)NULL))
			{
				pView->SetActiveCell();
				break;
			}
		}
	}
}

BOOL CTableViewObject::IsVisible() CONST
{
	return m_bVisible;
}

BOOL CTableViewObject::Copy(CONST CTableViewObject *pTable)
{
	m_nType = pTable->m_nType;
	m_szName = pTable->m_szName;
	m_szTitle = pTable->m_szTitle;
	m_ptSel = pTable->m_ptSel;
	m_nSelColor = pTable->m_nSelColor;
	m_bResize = pTable->m_bResize;
	m_bVisible = pTable->m_bVisible;
	m_nFloatingAlignment = pTable->m_nFloatingAlignment;
	SetRect(pTable->left, pTable->top, pTable->right, pTable->bottom);
	return m_pCells.Copy(&pTable->m_pCells);
}

BOOL CTableViewObject::Compare(CONST CTableViewObject *pTable) CONST
{
	return((pTable->m_szName == m_szName  &&  pTable->m_szTitle == m_szTitle  &&  pTable->m_nType == m_nType  &&  pTable->m_ptSel == m_ptSel  &&  pTable->m_nSelColor == m_nSelColor  &&  pTable->m_nFloatingAlignment == m_nFloatingAlignment  &&  pTable->m_bResize == m_bResize  &&  pTable->m_bVisible == m_bVisible  &&  pTable->m_pCells.Compare(&m_pCells)) ? EqualRect(pTable) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewObjects

CTableViewObjects::CTableViewObjects() : CPtrArray()
{
	return;
}

CTableViewObjects::~CTableViewObjects()
{
	RemoveAll();
}

INT CTableViewObjects::Add(CTableViewObject *pTable)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pTable->GetName(), TRUE)) >= 0) InsertAt(nIndex, pTable, 1);
	return nIndex;
}

INT CTableViewObjects::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CTableViewObject *CTableViewObjects::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTableViewObject *)CPtrArray::GetAt(nIndex) : (CTableViewObject *)NULL);
}

CTableViewObject *CTableViewObjects::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTableViewObject *)CPtrArray::GetAt(nIndex) : (CTableViewObject *)NULL);
}

VOID CTableViewObjects::RemoveAll()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)GetSize(); nIndex < nCount; nIndex++)
	{
		delete GetAt(nIndex);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTableViewObjects::Copy(CONST CTableViewObjects *pTables)
{
	INT  nIndex;
	INT  nCount;
	CTableViewObject  *pTable[2];

	for (nIndex = 0, nCount = (INT)pTables->GetSize(), RemoveAll(); nIndex < nCount; nIndex++)
	{
		if ((pTable[0] = pTables->GetAt(nIndex)))
		{
			if ((pTable[1] = new CTableViewObject))
			{
				pTable[1]->Copy(pTable[0]);
				SetAtGrow(nIndex, pTable[1]);
				continue;
			}
			RemoveAll();
			break;
		}
		SetAtGrow(nIndex, pTable[0]);
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTableViewObjects::Compare(CONST CTableViewObjects *pTables) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (pTables->GetSize() == GetSize()) ? (INT)pTables->GetSize() : -1; nIndex < nCount; nIndex++)
	{
		if (pTables->GetAt(nIndex)->Compare(GetAt(nIndex))) continue;
		break;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

INT CTableViewObjects::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (GetAt(nIndex)->GetName() < pszName)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return(((!bInsert  &&  nIndex < (INT)GetSize() && GetAt(nIndex)->GetName() == pszName) || (bInsert  &&  nIndex <= (INT)GetSize() && (!GetSize() || (GetAt(max(nIndex - 1, 0))->GetName() != pszName  &&  GetAt(min(nIndex, (INT)GetUpperBound()))->GetName() != pszName))) && lstrlen(pszName) > 0) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewEditCtrl

IMPLEMENT_DYNCREATE(CTableViewEditCtrl, CEdit)

CTableViewEditCtrl::CTableViewEditCtrl() : CEdit()
{
	m_nLimit = 0;
}

BOOL CTableViewEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	if (CEdit::Create(dwStyle, rect, pParentWnd, nID))
	{
		CEdit::LimitText(m_nLimit);
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewEditCtrl::LimitText(INT nCount)
{
	m_nLimit = nCount;
}

BOOL CTableViewEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CEdit::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewEditCtrl::GetParent() CONST
{
	return((CTableView *)CEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewEditCtrl, CEdit)
	//{{AFX_MSG_MAP(CTableViewEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewEditCtrl message handlers

UINT CTableViewEditCtrl::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void CTableViewEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CEdit::OnMouseMove(nFlags, point);
}

void CTableViewEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewDPLEditCtrl

IMPLEMENT_DYNCREATE(CTableViewDPLEditCtrl, CDPLCodeEdit)

CTableViewDPLEditCtrl::CTableViewDPLEditCtrl() : CDPLCodeEdit()
{
	m_nLimit = 0;
}

BOOL CTableViewDPLEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	if (CDPLCodeEdit::Create(pParentWnd, rect, nID, dwStyle))
	{
		CDPLCodeEdit::LimitText(m_nLimit);
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewDPLEditCtrl::LimitText(INT nCount)
{
	m_nLimit = nCount;
}

BOOL CTableViewDPLEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CDPLCodeEdit::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewDPLEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewDPLEditCtrl::GetParent() CONST
{
	return((CTableView *)CDPLCodeEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewDPLEditCtrl, CDPLCodeEdit)
	//{{AFX_MSG_MAP(CTableViewDPLEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewDPLEditCtrl message handlers

UINT CTableViewDPLEditCtrl::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void CTableViewDPLEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CDPLCodeEdit::OnMouseMove(nFlags, point);
}

void CTableViewDPLEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CDPLCodeEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewDPLEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			if (!IsWindow(GetSafeHwnd())) return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CDPLCodeEdit::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewMDLEditCtrl

IMPLEMENT_DYNCREATE(CTableViewMDLEditCtrl, CMDLCodeEdit)

CTableViewMDLEditCtrl::CTableViewMDLEditCtrl() : CMDLCodeEdit()
{
	m_nLimit = 0;
}

BOOL CTableViewMDLEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	if (CMDLCodeEdit::Create(pParentWnd, rect, nID, dwStyle))
	{
		CMDLCodeEdit::LimitText(m_nLimit);
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewMDLEditCtrl::LimitText(INT nCount)
{
	m_nLimit = nCount;
}

BOOL CTableViewMDLEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CMDLCodeEdit::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewMDLEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewMDLEditCtrl::GetParent() CONST
{
	return((CTableView *)CMDLCodeEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewMDLEditCtrl, CMDLCodeEdit)
	//{{AFX_MSG_MAP(CTableViewMDLEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewMDLEditCtrl message handlers

UINT CTableViewMDLEditCtrl::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void CTableViewMDLEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CMDLCodeEdit::OnMouseMove(nFlags, point);
}

void CTableViewMDLEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CMDLCodeEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewMDLEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			if (!IsWindow(GetSafeHwnd())) return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CMDLCodeEdit::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewTPLEditCtrl

IMPLEMENT_DYNCREATE(CTableViewTPLEditCtrl, CTPLCodeEdit)

CTableViewTPLEditCtrl::CTableViewTPLEditCtrl() : CTPLCodeEdit()
{
	m_nLimit = 0;
}

BOOL CTableViewTPLEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	if (CTPLCodeEdit::Create(pParentWnd, rect, nID, dwStyle))
	{
		CTPLCodeEdit::LimitText(m_nLimit);
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewTPLEditCtrl::LimitText(INT nCount)
{
	m_nLimit = nCount;
}

BOOL CTableViewTPLEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CTPLCodeEdit::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewTPLEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewTPLEditCtrl::GetParent() CONST
{
	return((CTableView *)CTPLCodeEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewTPLEditCtrl, CTPLCodeEdit)
	//{{AFX_MSG_MAP(CTableViewTPLEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewTPLEditCtrl message handlers

UINT CTableViewTPLEditCtrl::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void CTableViewTPLEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CTPLCodeEdit::OnMouseMove(nFlags, point);
}

void CTableViewTPLEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CTPLCodeEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewTPLEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			if (!IsWindow(GetSafeHwnd())) return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CTPLCodeEdit::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewMultiLineEditCtrl

IMPLEMENT_DYNCREATE(CTableViewMultiLineEditCtrl, CEdit)

CTableViewMultiLineEditCtrl::CTableViewMultiLineEditCtrl() : CEdit()
{
	m_nLimit = 0;
}

BOOL CTableViewMultiLineEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	if (CEdit::Create(dwStyle, rect, pParentWnd, nID))
	{
		CEdit::LimitText(m_nLimit);
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewMultiLineEditCtrl::LimitText(INT nCount)
{
	m_nLimit = nCount;
}

BOOL CTableViewMultiLineEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CEdit::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewMultiLineEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewMultiLineEditCtrl::GetParent() CONST
{
	return((CTableView *)CEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewMultiLineEditCtrl, CEdit)
	//{{AFX_MSG_MAP(CTableViewMultiLineEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewMultiLineEditCtrl message handlers

UINT CTableViewMultiLineEditCtrl::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void CTableViewMultiLineEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CEdit::OnMouseMove(nFlags, point);
}

void CTableViewMultiLineEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewMultiLineEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewDecNumberEditCtrl

IMPLEMENT_DYNCREATE(CTableViewDecNumberEditCtrl, CEdit)

CTableViewDecNumberEditCtrl::CTableViewDecNumberEditCtrl() : CEdit()
{
	m_nDigits = -1;
	m_nRange[0] = 0;
	m_nRange[1] = 0;
	m_uRange[0] = 0;
	m_uRange[1] = 0;
	m_fRange[0] = 0.0;
	m_fRange[1] = 0.0;
	m_bRange[0] = FALSE;
	m_bRange[1] = FALSE;
	m_bRange[2] = FALSE;
}

BOOL CTableViewDecNumberEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	CStringTools  cStringTools;

	if (CEdit::Create(dwStyle, rect, pParentWnd, nID))
	{
		if (m_bRange[0]) LimitText((m_nDigits < 0) ? max(cStringTools.ConvertLongIntToString(m_nRange[0]).GetLength(), cStringTools.ConvertLongIntToString(m_nRange[1]).GetLength()) : m_nDigits);
		if (m_bRange[1]) LimitText((m_nDigits < 0) ? max(cStringTools.ConvertLongUIntToString(m_uRange[0]).GetLength(), cStringTools.ConvertLongUIntToString(m_uRange[1]).GetLength()) : m_nDigits);
		if (m_bRange[2]) LimitText();
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewDecNumberEditCtrl::SetRange(LONGLONG nLow, LONGLONG nHigh, INT nDigits)
{
	m_nRange[0] = nLow;
	m_nRange[1] = nHigh;
	m_bRange[0] = TRUE;
	m_bRange[1] = FALSE;
	m_bRange[2] = FALSE;
	m_nDigits = nDigits;
}
VOID CTableViewDecNumberEditCtrl::SetRange(ULONGLONG uLow, ULONGLONG uHigh, INT nDigits)
{
	m_uRange[0] = uLow;
	m_uRange[1] = uHigh;
	m_bRange[0] = FALSE;
	m_bRange[1] = TRUE;
	m_bRange[2] = FALSE;
	m_nDigits = nDigits;
}
VOID CTableViewDecNumberEditCtrl::SetRange(double fLow, double fHigh)
{
	m_fRange[0] = fLow;
	m_fRange[1] = fHigh;
	m_bRange[0] = FALSE;
	m_bRange[1] = FALSE;
	m_bRange[2] = TRUE;
	m_nDigits = -1;
}

BOOL CTableViewDecNumberEditCtrl::GetRange(LONGLONG &nLow, LONGLONG &nHigh) CONST
{
	if (m_bRange[0])
	{
		nLow = m_nRange[0];
		nHigh = m_nRange[1];
	}
	return m_bRange[0];
}
BOOL CTableViewDecNumberEditCtrl::GetRange(ULONGLONG &uLow, ULONGLONG &uHigh) CONST
{
	if (m_bRange[1])
	{
		uLow = m_uRange[0];
		uHigh = m_uRange[1];
	}
	return m_bRange[1];
}
BOOL CTableViewDecNumberEditCtrl::GetRange(double &fLow, double &fHigh) CONST
{
	if (m_bRange[2])
	{
		fLow = m_fRange[0];
		fHigh = m_fRange[1];
	}
	return m_bRange[2];
}

double CTableViewDecNumberEditCtrl::GetNumber() CONST
{
	double  fNumber;
	LONGLONG  nNumber;
	ULONGLONG  uNumber;
	CString  szNumber;

	for (GetLine(0, szNumber.GetBufferSetLength(LineLength()), LineLength()), szNumber.ReleaseBuffer(), fNumber = TranslateNumber(szNumber), nNumber = (LONGLONG)fNumber, uNumber = (ULONGLONG)fNumber; (m_bRange[0] && m_nRange[0] > nNumber) || (m_bRange[1] && m_uRange[0] > uNumber) || (m_bRange[2] && m_fRange[0] > fNumber); )
	{
		fNumber = (m_bRange[0]) ? (double)m_nRange[0] : fNumber;
		fNumber = (m_bRange[1]) ? (double)m_uRange[0] : fNumber;
		fNumber = (m_bRange[2]) ? m_fRange[0] : fNumber;
		break;
	}
	if ((m_bRange[0] && m_nRange[1] < nNumber) || (m_bRange[1] && m_uRange[1] < uNumber) || (m_bRange[2] && m_fRange[1] < fNumber))
	{
		fNumber = (m_bRange[0]) ? (double)m_nRange[1] : fNumber;
		fNumber = (m_bRange[1]) ? (double)m_uRange[1] : fNumber;
		fNumber = (m_bRange[2]) ? m_fRange[1] : fNumber;
	}
	return fNumber;
}

CString CTableViewDecNumberEditCtrl::GetNumberAsText() CONST
{
	CStringTools  cStringTools;

	return((LineLength() > 0) ? ((m_bRange[0]) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)GetNumber()) : ((m_bRange[1]) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)GetNumber()) : (LPCTSTR)cStringTools.ConvertFloatToString(GetNumber()))) : EMPTYSTRING);
}

BOOL CTableViewDecNumberEditCtrl::HasNumber() CONST
{
	return((LineLength() > 0) ? TRUE : FALSE);
}

CString CTableViewDecNumberEditCtrl::TranslateNumber(double fValue) CONST
{
	CStringTools  cStringTools;

	if (m_bRange[0]) return cStringTools.ConvertLongIntToString((LONGLONG)fValue);
	if (m_bRange[1]) return cStringTools.ConvertLongUIntToString((ULONGLONG)fValue);
	if (m_bRange[2]) return cStringTools.ConvertFloatToString(fValue);
	return EMPTYSTRING;
}
double CTableViewDecNumberEditCtrl::TranslateNumber(LPCTSTR pszNumber) CONST
{
	LPTSTR  p;

	return _tcstod(pszNumber, &p);
}

BOOL CTableViewDecNumberEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CEdit::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewDecNumberEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewDecNumberEditCtrl::GetParent() CONST
{
	return((CTableView *)CEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewDecNumberEditCtrl, CEdit)
	//{{AFX_MSG_MAP(CTableViewDecNumberEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_GETTEXTLENGTH, OnGetWindowTextLength)
	ON_MESSAGE(WM_GETTEXT, OnGetWindowText)
	ON_CONTROL_REFLECT(EN_UPDATE, OnNumberUpdate)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillFocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewDecNumberEditCtrl message handlers

UINT CTableViewDecNumberEditCtrl::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void CTableViewDecNumberEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CEdit::OnMouseMove(nFlags, point);
}

void CTableViewDecNumberEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewDecNumberEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CTableViewDecNumberEditCtrl::OnGetWindowTextLength(WPARAM wParam, LPARAM lParam)
{
	return GetNumberAsText().GetLength();
}

LRESULT CTableViewDecNumberEditCtrl::OnGetWindowText(WPARAM wParam, LPARAM lParam)
{
	CString  szNumber;

	szNumber = GetNumberAsText();
	CopyMemory((LPVOID)lParam, (LPCTSTR)szNumber, min(szNumber.GetLength() + 1, (INT)wParam)*sizeof(TCHAR));
	return(wParam - 1);
}

void CTableViewDecNumberEditCtrl::OnNumberUpdate()
{
	INT  nPos;
	LPTSTR  p;
	CString  szSign;
	CString  szNumber[2];
	CStringTools  cStringTools;

	for (GetLine(0, szNumber[0].GetBufferSetLength(LineLength()), LineLength()), szNumber[0].ReleaseBuffer(), szNumber[1].Empty(), nPos = 0, szSign = cStringTools.ConvertIntToString(-1); (m_bRange[0] || m_bRange[1]) && nPos < szNumber[0].GetLength(); nPos++)
	{
		if (!szNumber[1].GetLength() && szNumber[0].GetAt(nPos) == szSign.GetAt(0) && m_bRange[0])
		{
			szNumber[1] = szNumber[0].GetAt(nPos);
			continue;
		}
		if (_istdigit(szNumber[0].GetAt(nPos)))
		{
			szNumber[1] += szNumber[0].GetAt(nPos);
			continue;
		}
		if (!szNumber[1].GetLength() && _istspace(szNumber[0].GetAt(nPos))) continue;
		SetWindowText(szNumber[0].Left(nPos));
		CAudioDevice::AlertBySound();
		SetSel(0, -1);
		break;
	}
	for (_tcstod(szNumber[0], &p); m_bRange[2] && lstrlen(p) > 0 && _tcsncmp(p, szSign, 1); )
	{
		SetWindowText(szNumber[0].Left(szNumber[0].GetLength() - lstrlen(p)));
		CAudioDevice::AlertBySound();
		SetSel(0, -1);
		break;
	}
}

void CTableViewDecNumberEditCtrl::OnKillFocus()
{
	CString  szNumber[2];

	for (GetWindowText(szNumber[0]), szNumber[1] = GetNumberAsText(); szNumber[0] != szNumber[1]; )
	{
		SetWindowText(szNumber[1]);
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewRawNumberEditCtrl

IMPLEMENT_DYNCREATE(CTableViewRawNumberEditCtrl, CEdit)

CTableViewRawNumberEditCtrl::CTableViewRawNumberEditCtrl() : CEdit()
{
	m_nRadix = 16;
	m_nDigits = -1;
	m_nRange[0] = 0;
	m_nRange[1] = 0;
	m_bRange = FALSE;
	m_bPadded = FALSE;
}

BOOL CTableViewRawNumberEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	CStringTools  cStringTools;

	if (CEdit::Create(dwStyle, rect, pParentWnd, nID))
	{
		if (m_bRange) LimitText((m_nDigits < 0) ? max(cStringTools.ConvertLongUIntToString(m_nRange[0], m_nRadix).GetLength(), cStringTools.ConvertLongUIntToString(m_nRange[1], m_nRadix).GetLength()) : m_nDigits);
		return TRUE;
	}
	return FALSE;
}

VOID CTableViewRawNumberEditCtrl::SetRadix(UINT nRadix)
{
	m_nRadix = max(nRadix, 2);
}

INT CTableViewRawNumberEditCtrl::GetRadix() CONST
{
	return m_nRadix;
}

VOID CTableViewRawNumberEditCtrl::SetRange(ULONGLONG nLow, ULONGLONG nHigh, INT nDigits, BOOL bPadded)
{
	m_nRange[0] = nLow;
	m_nRange[1] = nHigh;
	m_bPadded = ((m_nDigits = nDigits) > 0) ? bPadded : FALSE;
	m_bRange = TRUE;
}

BOOL CTableViewRawNumberEditCtrl::GetRange(ULONGLONG &nLow, ULONGLONG &nHigh) CONST
{
	if (m_bRange)
	{
		nLow = m_nRange[0];
		nHigh = m_nRange[1];
	}
	return m_bRange;
}

ULONGLONG CTableViewRawNumberEditCtrl::GetNumber() CONST
{
	ULONGLONG  nNumber;
	CString  szNumber;

	for (GetLine(0, szNumber.GetBufferSetLength(LineLength()), LineLength()), szNumber.ReleaseBuffer(), nNumber = TranslateNumber(szNumber); m_nRange[0] > nNumber; )
	{
		nNumber = m_nRange[0];
		break;
	}
	if (m_nRange[1] < nNumber) nNumber = m_nRange[1];
	return nNumber;
}

CString CTableViewRawNumberEditCtrl::GetNumberAsText() CONST
{
	CStringTools  cStringTools;

	return((LineLength() > 0) ? ((m_bPadded) ? (LPCTSTR)cStringTools.ConvertLongUIntToPaddedString(GetNumber(), m_nDigits, m_nRadix) : (LPCTSTR)cStringTools.ConvertLongUIntToString(GetNumber(), m_nRadix)) : EMPTYSTRING);
}

BOOL CTableViewRawNumberEditCtrl::HasNumber() CONST
{
	return((LineLength() > 0) ? TRUE : FALSE);
}

CString CTableViewRawNumberEditCtrl::TranslateNumber(ULONGLONG nValue) CONST
{
	CStringTools  cStringTools;

	return((m_bPadded) ? cStringTools.ConvertLongUIntToPaddedString(GetNumber(), m_nDigits, m_nRadix) : cStringTools.ConvertLongUIntToString(nValue, m_nRadix));
}
ULONGLONG CTableViewRawNumberEditCtrl::TranslateNumber(LPCTSTR pszNumber) CONST
{
	INT  nPos;
	INT  nLength;
	TCHAR  szDigit;
	CString  szMin;
	CString  szMax;
	CString  szHex;
	CString  szNumber;
	ULONGLONG  nNumber;
	CStringTools  cStringTools;

	for (nPos = 0, szNumber = pszNumber, nLength = szNumber.GetLength(), szNumber.MakeUpper(), szMin = cStringTools.ConvertUIntToString(0, m_nRadix), szMax = cStringTools.ConvertUIntToString(m_nRadix - 1, m_nRadix), szHex = cStringTools.ConvertUIntToString(10, m_nRadix), szHex.MakeUpper(), nNumber = 0; nPos < nLength; nPos++)
	{
		if (_istdigit((szDigit = szNumber.GetAt(nPos))) && szDigit >= szMin.GetAt(0) && szDigit <= szMax.GetAt(0))
		{
			nNumber = nNumber*m_nRadix + szDigit - szMin.GetAt(0);
			continue;
		}
		if (!_istdigit(szDigit) && szDigit >= szHex.GetAt(0) && szDigit <= szMax.GetAt(0))
		{
			nNumber = nNumber*m_nRadix + szDigit - szHex.GetAt(0) + 10;
			continue;
		}
		if (_istspace(szDigit) && _tcsspn(szNumber.Left(nPos), CString(szDigit)) == nPos) continue;
		break;
	}
	return nNumber;
}

BOOL CTableViewRawNumberEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CEdit::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewRawNumberEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewRawNumberEditCtrl::GetParent() CONST
{
	return((CTableView *)CEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewRawNumberEditCtrl, CEdit)
	//{{AFX_MSG_MAP(CTableViewRawNumberEditCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_GETTEXTLENGTH, OnGetWindowTextLength)
	ON_MESSAGE(WM_GETTEXT, OnGetWindowText)
	ON_CONTROL_REFLECT(EN_UPDATE, OnNumberUpdate)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillFocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewRawNumberEditCtrl message handlers

UINT CTableViewRawNumberEditCtrl::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

void CTableViewRawNumberEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CEdit::OnMouseMove(nFlags, point);
}

void CTableViewRawNumberEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewRawNumberEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CTableViewRawNumberEditCtrl::OnGetWindowTextLength(WPARAM wParam, LPARAM lParam)
{
	return GetNumberAsText().GetLength();
}

LRESULT CTableViewRawNumberEditCtrl::OnGetWindowText(WPARAM wParam, LPARAM lParam)
{
	CString  szNumber;

	szNumber = GetNumberAsText();
	CopyMemory((LPVOID)lParam, (LPCTSTR)szNumber, min(szNumber.GetLength() + 1, (INT)wParam)*sizeof(TCHAR));
	return(wParam - 1);
}

void CTableViewRawNumberEditCtrl::OnNumberUpdate()
{
	INT  nPos;
	INT  nLength;
	TCHAR  szDigit;
	CString  szMin;
	CString  szMax;
	CString  szHex;
	CString  szNumber[3];
	CStringTools  cStringTools;

	for (GetLine(0, szNumber[0].GetBufferSetLength(LineLength()), LineLength()), szNumber[0].ReleaseBuffer(), nPos = 0, nLength = szNumber[0].GetLength(), szNumber[1] = szNumber[0], szNumber[1].MakeUpper(), szNumber[2].Empty(), szMin = cStringTools.ConvertUIntToString(0, m_nRadix), szMax = cStringTools.ConvertUIntToString(m_nRadix - 1, m_nRadix), szHex = cStringTools.ConvertUIntToString(10, m_nRadix), szHex.MakeUpper(); nPos < nLength; nPos++)
	{
		if ((_istdigit((szDigit = szNumber[1].GetAt(nPos))) && szDigit >= szMin.GetAt(0) && szDigit <= szMax.GetAt(0)) || (!_istdigit(szDigit) && szDigit >= szHex.GetAt(0) && szDigit <= szMax.GetAt(0)))
		{
			szNumber[2] += szNumber[1].GetAt(nPos);
			continue;
		}
		if (_istspace(szDigit) && _tcsspn(szNumber[2], CString(szDigit)) == szNumber[2].GetLength())
		{
			szNumber[2] += szNumber[1].GetAt(nPos);
			continue;
		}
	}
	if (szNumber[1] != szNumber[2])
	{
		SetWindowText(szNumber[0].Left(szNumber[2].GetLength()));
		CAudioDevice::AlertBySound();
		SetSel(0, -1);
	}
}

void CTableViewRawNumberEditCtrl::OnKillFocus()
{
	CString  szNumber[2];

	for (GetWindowText(szNumber[0]), szNumber[1] = GetNumberAsText(); szNumber[0] != szNumber[1]; )
	{
		SetWindowText(szNumber[1]);
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxListCtrl

IMPLEMENT_DYNCREATE(CTableViewComboBoxListCtrl, CComboBox)

BOOL CTableViewComboBoxListCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (CComboBox::Create(dwStyle, rect, pParentWnd, nID)) ? (INT)m_szValues.GetSize() : -1; nIndex < nCount; nIndex++)
	{
		SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szValues.GetAt(nIndex));
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CTableViewComboBoxListCtrl::SetValues(CONST CStringArray &szValues, CONST CLongUIntArray &nValues)
{
	if (szValues.GetSize() == nValues.GetSize())
	{
		m_szValues.Copy(szValues);
		m_nValues.Copy(nValues);
		return TRUE;
	}
	return FALSE;
}

INT CTableViewComboBoxListCtrl::GetValues(CStringArray &szValues) CONST
{
	szValues.Copy(m_szValues);
	return((INT)szValues.GetSize());
}
INT CTableViewComboBoxListCtrl::GetValues(CLongUIntArray &nValues) CONST
{
	nValues.Copy(m_nValues);
	return((INT)nValues.GetSize());
}

ULONGLONG CTableViewComboBoxListCtrl::GetValue() CONST
{
	INT  nIndex;

	return(((nIndex = FindStringExact(-1, GetValueAsText())) >= 0 && nIndex < m_nValues.GetSize()) ? m_nValues.GetAt(nIndex) : -1);
}

CString CTableViewComboBoxListCtrl::GetValueAsText() CONST
{
	CString  szText;

	GetWindowText(szText);
	return szText;
}

BOOL CTableViewComboBoxListCtrl::HasValue(LPCTSTR pszValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_szValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_szValues.GetAt(nIndex) == pszValue) break;
		continue;
	}
	return((nIndex < nCount) ? TRUE : FALSE);
}
BOOL CTableViewComboBoxListCtrl::HasValue(ULONGLONG nValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_nValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_nValues.GetAt(nIndex) == nValue) break;
		continue;
	}
	return((nIndex < nCount) ? TRUE : FALSE);
}
BOOL CTableViewComboBoxListCtrl::HasValue() CONST
{
	return((m_szValues.GetSize() > 0) ? TRUE : FALSE);
}

CString CTableViewComboBoxListCtrl::TranslateValue(ULONGLONG nValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_nValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_nValues.GetAt(nIndex) == nValue) break;
		continue;
	}
	return((nIndex < nCount) ? m_szValues.GetAt(nIndex) : EMPTYSTRING);
}
ULONGLONG CTableViewComboBoxListCtrl::TranslateValue(LPCTSTR pszValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_szValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_szValues.GetAt(nIndex) == pszValue) break;
		continue;
	}
	return((nIndex < nCount) ? m_nValues.GetAt(nIndex) : -1);
}

INT CTableViewComboBoxListCtrl::SetCurSel(INT nIndex)
{
	INT  nSel;

	if ((nSel = CComboBox::SetCurSel(nIndex)) < 0) GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), CBN_SELCHANGE), (LPARAM)GetSafeHwnd());
	return nSel;
}

INT CTableViewComboBoxListCtrl::GetCurSel() CONST
{
	return CComboBox::GetCurSel();
}

BOOL CTableViewComboBoxListCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CComboBox::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewComboBoxListCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

BOOL CTableViewComboBoxListCtrl::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_DELETE)
		{
			SetCurSel(-1);
			return TRUE;
		}
	}
	return CComboBox::PreTranslateMessage(pMsg);
}

CTableView *CTableViewComboBoxListCtrl::GetParent() CONST
{
	return((CTableView *)CComboBox::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewComboBoxListCtrl, CComboBox)
	//{{AFX_MSG_MAP(CTableViewComboBoxListCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxListCtrl message handlers

void CTableViewComboBoxListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CComboBox::OnMouseMove(nFlags, point);
}

void CTableViewComboBoxListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_BACK)
	{
		SetCurSel(-1);
		return;
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewComboBoxListCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CComboBox::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxEditSubCtrl

IMPLEMENT_DYNCREATE(CTableViewComboBoxEditSubCtrl, CEdit)

CTableViewComboBoxEditCtrl *CTableViewComboBoxEditSubCtrl::GetParent() CONST
{
	return((CTableViewComboBoxEditCtrl *)CEdit::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewComboBoxEditSubCtrl, CEdit)
	//{{AFX_MSG_MAP(CTableViewComboBoxEditSubCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxEditSubCtrl message handlers

void CTableViewComboBoxEditSubCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->GetParent()->ScreenToClient(&pt);
	GetParent()->GetParent()->UpdateTablePosition(nFlags, pt);
	CEdit::OnMouseMove(nFlags, point);
}

void CTableViewComboBoxEditSubCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->GetParent()->SetActiveCell();
		return;
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewComboBoxEditSubCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxEditCtrl

IMPLEMENT_DYNCREATE(CTableViewComboBoxEditCtrl, CComboBox)

CTableViewComboBoxEditCtrl::CTableViewComboBoxEditCtrl() : CComboBox()
{
	m_nLimit = 0;
}

BOOL CTableViewComboBoxEditCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (CComboBox::Create(dwStyle, rect, pParentWnd, nID)) ? (INT)m_szValues.GetSize() : -1; nIndex < nCount; nIndex++)
	{
		SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szValues.GetAt(nIndex));
		continue;
	}
	if (nIndex == nCount)
	{
		CComboBox::LimitText(m_nLimit);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewComboBoxEditCtrl::SetValues(CONST CStringArray &szValues, CONST CLongUIntArray &nValues)
{
	if (szValues.GetSize() == nValues.GetSize())
	{
		m_szValues.Copy(szValues);
		m_nValues.Copy(nValues);
		return TRUE;
	}
	return FALSE;
}

INT CTableViewComboBoxEditCtrl::GetValues(CStringArray &szValues) CONST
{
	szValues.Copy(m_szValues);
	return((INT)szValues.GetSize());
}
INT CTableViewComboBoxEditCtrl::GetValues(CLongUIntArray &nValues) CONST
{
	nValues.Copy(m_nValues);
	return((INT)nValues.GetSize());
}

ULONGLONG CTableViewComboBoxEditCtrl::GetValue() CONST
{
	INT  nIndex;

	return(((nIndex = FindStringExact(-1, GetValueAsText())) >= 0 && nIndex < m_nValues.GetSize()) ? m_nValues.GetAt(nIndex) : -1);
}

CString CTableViewComboBoxEditCtrl::GetValueAsText() CONST
{
	CString  szText;

	GetWindowText(szText);
	return szText;
}

BOOL CTableViewComboBoxEditCtrl::HasValue(LPCTSTR pszValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_szValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_szValues.GetAt(nIndex) == pszValue) break;
		continue;
	}
	return((nIndex < nCount) ? TRUE : FALSE);
}
BOOL CTableViewComboBoxEditCtrl::HasValue(ULONGLONG nValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_nValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_nValues.GetAt(nIndex) == nValue) break;
		continue;
	}
	return((nIndex < nCount) ? TRUE : FALSE);
}
BOOL CTableViewComboBoxEditCtrl::HasValue() CONST
{
	return((m_szValues.GetSize() > 0) ? TRUE : FALSE);
}

CString CTableViewComboBoxEditCtrl::TranslateValue(ULONGLONG nValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_nValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_nValues.GetAt(nIndex) == nValue) break;
		continue;
	}
	return((nIndex < nCount) ? m_szValues.GetAt(nIndex) : EMPTYSTRING);
}
ULONGLONG CTableViewComboBoxEditCtrl::TranslateValue(LPCTSTR pszValue) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_szValues.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_szValues.GetAt(nIndex) == pszValue) break;
		continue;
	}
	return((nIndex < nCount) ? m_nValues.GetAt(nIndex) : -1);
}

VOID CTableViewComboBoxEditCtrl::LimitText(INT nCount)
{
	m_nLimit = nCount;
}

BOOL CTableViewComboBoxEditCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		CComboBox::SetFont(&m_cFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTableViewComboBoxEditCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((GetObject(m_cFont.GetSafeHandle(), sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

CTableView *CTableViewComboBoxEditCtrl::GetParent() CONST
{
	return((CTableView *)CComboBox::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewComboBoxEditCtrl, CComboBox)
	//{{AFX_MSG_MAP(CTableViewComboBoxEditCtrl)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(CBN_KILLFOCUS, OnKillFocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxEditCtrl message handlers

int CTableViewComboBoxEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CComboBox::OnCreate(lpCreateStruct) != -1 && m_cEdit.SubclassWindow(GetWindow(GW_CHILD)->GetSafeHwnd())) ? 0 : -1);
}

void CTableViewComboBoxEditCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CComboBox::OnMouseMove(nFlags, point);
}

void CTableViewComboBoxEditCtrl::OnKillFocus()
{
	INT  nIndex;
	CString  szText;

	for (GetWindowText(szText); (nIndex = (INT)SendMessage(CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText)) >= 0; )
	{
		SetCurSel(nIndex);
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxColorsCtrl

IMPLEMENT_DYNCREATE(CTableViewComboBoxColorsCtrl, CColorsComboBox)

BOOL CTableViewComboBoxColorsCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	return CColorsComboBox::Create(pParentWnd, rect, nID, dwStyle);
}

VOID CTableViewComboBoxColorsCtrl::SetColors(CONST CUIntArray &nColors)
{
	m_nColors.Copy(nColors);
}

INT CTableViewComboBoxColorsCtrl::GetColors(CUIntArray &nColors) CONST
{
	nColors.Copy(m_nColors);
	return((INT)nColors.GetSize());
}

COLORREF CTableViewComboBoxColorsCtrl::GetColor() CONST
{
	INT  nIndex;

	return(((nIndex = GetCurSel()) >= 0 && nIndex < GetCount()) ? (COLORREF)GetItemData(nIndex) : -1);
}
CString CTableViewComboBoxColorsCtrl::GetColorAsText() CONST
{
	return TranslateColor(GetColor());
}

CString CTableViewComboBoxColorsCtrl::TranslateColor(COLORREF nColor)
{
	CStringTools  cStringTools;

	return cStringTools.ConvertIntToString(nColor);
}
COLORREF CTableViewComboBoxColorsCtrl::TranslateColor(LPCTSTR pszColor)
{
	CStringTools  cStringTools;

	return((lstrlen(pszColor) > 0) ? ((!cStringTools.ConvertIntToString(_ttoi(pszColor)).Compare(pszColor)) ? _ttoi(pszColor) : (((COLORREF *)pszColor)[0])) : -1);
}

void CTableViewComboBoxColorsCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CTableViewComboBoxColorsCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	INT  nBkMode;
	CFont  *pOldFont;
	CRect  rItemArea;
	CBrush  cBkBrush;
	CBrush  cItemBrush;
	COLORREF  nOldColor;
	TEXTMETRIC  tmFont;

	if (cDC.Attach(lpDrawItemStruct->hDC))
	{
		if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_SELECT))
		{
			if (cBkBrush.CreateSolidBrush((lpDrawItemStruct->itemState & ODS_SELECTED) ? (COLORREF)GetSysColor(COLOR_HIGHLIGHT) : (COLORREF)cDC.GetBkColor()))
			{
				cDC.FillRect(&lpDrawItemStruct->rcItem, &cBkBrush);
				if ((lpDrawItemStruct->itemState & ODS_SELECTED) && lpDrawItemStruct->rcItem.left > 0) cDC.DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
			if (!(lpDrawItemStruct->itemState & ODS_DISABLED))
			{
				if (lpDrawItemStruct->itemID != (UINT)-1)
				{
					rItemArea = lpDrawItemStruct->rcItem;
					rItemArea.DeflateRect(2 * GetSystemMetrics(SM_CXBORDER), 2 * GetSystemMetrics(SM_CYBORDER));
					if ((GetStyle() & CCBS_CUSTOM) && lpDrawItemStruct->itemID == (UINT)GetCount() - 1)
					{
						if ((pOldFont = (CFont *)cDC.SelectObject(GetFont())))
						{
							if (cDC.GetTextMetrics(&tmFont))
							{
								nBkMode = cDC.SetBkMode(TRANSPARENT);
								nOldColor = cDC.SetTextColor((lpDrawItemStruct->itemState & ODS_SELECTED) ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT));
								cDC.TextOut(rItemArea.left, rItemArea.top + (rItemArea.Height() - tmFont.tmHeight) / 2, STRING(IDS_COLORSCOMBOBOX_CUSTOM));
								cDC.SetTextColor(nOldColor);
								cDC.SelectObject(pOldFont);
								cDC.SetBkMode(nBkMode);
							}
						}
					}
					else
					{
						if (cItemBrush.CreateSolidBrush((COLORREF)lpDrawItemStruct->itemData))
						{
							cDC.FillRect(rItemArea, &cItemBrush);
							cItemBrush.DeleteObject();
						}
					}
				}
			}
		}
		cDC.Detach();
	}
}

CTableView *CTableViewComboBoxColorsCtrl::GetParent() CONST
{
	return((CTableView *)CColorsComboBox::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewComboBoxColorsCtrl, CColorsComboBox)
	//{{AFX_MSG_MAP(CTableViewComboBoxColorsCtrl)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_GETTEXT, OnGetText)
	ON_MESSAGE(WM_GETTEXTLENGTH, OnGetTextLength)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxColorsCtrl message handlers

int CTableViewComboBoxColorsCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nColor;
	INT  nColors;

	if (CColorsComboBox::OnCreate(lpCreateStruct) != -1)
	{
		if ((nColors = (INT)m_nColors.GetSize()) > 0)
		{
			for (nColor = 0, ResetContent(), ModifyStyle(CCBS_CUSTOM, CCBS_STANDARD); nColor < nColors; nColor++)
			{
				InsertColor(nColor, m_nColors.GetAt(nColor));
				continue;
			}
		}
		return 0;
	}
	return -1;
}

void CTableViewComboBoxColorsCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CColorsComboBox::OnMouseMove(nFlags, point);
}

void CTableViewComboBoxColorsCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CColorsComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewComboBoxColorsCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CColorsComboBox::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CTableViewComboBoxColorsCtrl::OnSetText(WPARAM wParam, LPARAM lParam)
{
	SelectColor(-1, TranslateColor((LPCTSTR)lParam));
	return TRUE;
}

LRESULT CTableViewComboBoxColorsCtrl::OnGetText(WPARAM wParam, LPARAM lParam)
{
	return((!_tcscpy_s((LPTSTR)lParam, GetColorAsText().GetLength() + 1, GetColorAsText())) ? GetColorAsText().GetLength() : 0);
}

LRESULT CTableViewComboBoxColorsCtrl::OnGetTextLength(WPARAM wParam, LPARAM lParam)
{
	return GetColorAsText().GetLength() + 1;
}

LRESULT CTableViewComboBoxColorsCtrl::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	INT  nItem;
	INT  nItems;
	MEASUREITEMSTRUCT  sItem;

	for (nItem = -1, nItems = GetCount(), Default(); nItem < nItems; nItem++)
	{
		sItem.itemID = nItem;
		MeasureItem(&sItem);
		SetItemHeight(nItem, sItem.itemHeight);
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxLineStylesCtrl

IMPLEMENT_DYNCREATE(CTableViewComboBoxLineStylesCtrl, CLineStylesComboBox)

BOOL CTableViewComboBoxLineStylesCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	return CLineStylesComboBox::Create(pParentWnd, rect, nID, dwStyle);
}

VOID CTableViewComboBoxLineStylesCtrl::SetLineStyles(CONST CUIntArray &nStyles)
{
	m_nStyles.Copy(nStyles);
}

INT CTableViewComboBoxLineStylesCtrl::GetLineStyles(CUIntArray &nStyles) CONST
{
	nStyles.Copy(m_nStyles);
	return((INT)nStyles.GetSize());
}

INT CTableViewComboBoxLineStylesCtrl::GetLineStyle() CONST
{
	INT  nIndex;

	return(((nIndex = GetCurSel()) >= 0 && nIndex < GetCount()) ? (INT)GetItemData(nIndex) : -1);
}

CString CTableViewComboBoxLineStylesCtrl::GetLineStyleAsText() CONST
{
	return TranslateLineStyle(GetLineStyle());
}

CString CTableViewComboBoxLineStylesCtrl::TranslateLineStyle(INT nStyle)
{
	CStringTools  cStringTools;

	return cStringTools.ConvertIntToString(nStyle);
}
INT CTableViewComboBoxLineStylesCtrl::TranslateLineStyle(LPCTSTR pszStyle)
{
	CStringTools  cStringTools;

	return((lstrlen(pszStyle) > 0) ? ((!cStringTools.ConvertIntToString(_ttoi(pszStyle)).Compare(pszStyle)) ? _ttoi(pszStyle) : (((INT *)pszStyle)[0])) : -1);
}

void CTableViewComboBoxLineStylesCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

CTableView *CTableViewComboBoxLineStylesCtrl::GetParent() CONST
{
	return((CTableView *)CLineStylesComboBox::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewComboBoxLineStylesCtrl, CLineStylesComboBox)
	//{{AFX_MSG_MAP(CTableViewComboBoxLineStylesCtrl)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_GETTEXT, OnGetText)
	ON_MESSAGE(WM_GETTEXTLENGTH, OnGetTextLength)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxLineStylesCtrl message handlers

int CTableViewComboBoxLineStylesCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nStyle;
	INT  nStyles;

	if (CLineStylesComboBox::OnCreate(lpCreateStruct) != -1)
	{
		if ((nStyles = (INT)m_nStyles.GetSize()) > 0)
		{
			for (nStyle = 0, ResetContent(); nStyle < nStyles; nStyle++)
			{
				InsertLineStyle(nStyle, m_nStyles.GetAt(nStyle));
				continue;
			}
		}
		return 0;
	}
	return -1;
}

void CTableViewComboBoxLineStylesCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CLineStylesComboBox::OnMouseMove(nFlags, point);
}

void CTableViewComboBoxLineStylesCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CLineStylesComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewComboBoxLineStylesCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CLineStylesComboBox::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CTableViewComboBoxLineStylesCtrl::OnSetText(WPARAM wParam, LPARAM lParam)
{
	SelectLineStyle(-1, TranslateLineStyle((LPCTSTR)lParam));
	return TRUE;
}

LRESULT CTableViewComboBoxLineStylesCtrl::OnGetText(WPARAM wParam, LPARAM lParam)
{
	return((!_tcscpy_s((LPTSTR)lParam, GetLineStyleAsText().GetLength() + 1, GetLineStyleAsText())) ? GetLineStyleAsText().GetLength() : 0);
}

LRESULT CTableViewComboBoxLineStylesCtrl::OnGetTextLength(WPARAM wParam, LPARAM lParam)
{
	return GetLineStyleAsText().GetLength() + 1;
}

LRESULT CTableViewComboBoxLineStylesCtrl::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	INT  nItem;
	INT  nItems;
	MEASUREITEMSTRUCT  sItem;

	for (nItem = -1, nItems = GetCount(), Default(); nItem < nItems; nItem++)
	{
		sItem.itemID = nItem;
		MeasureItem(&sItem);
		SetItemHeight(nItem, sItem.itemHeight);
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxLineSymbolsCtrl

IMPLEMENT_DYNCREATE(CTableViewComboBoxLineSymbolsCtrl, CLineSymbolsComboBox)

BOOL CTableViewComboBoxLineSymbolsCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	return CLineSymbolsComboBox::Create(pParentWnd, rect, nID, dwStyle);
}

VOID CTableViewComboBoxLineSymbolsCtrl::SetLineSymbols(CONST CUIntArray &nSymbols)
{
	m_nSymbols.Copy(nSymbols);
}

INT CTableViewComboBoxLineSymbolsCtrl::GetLineSymbols(CUIntArray &nSymbols) CONST
{
	nSymbols.Copy(m_nSymbols);
	return((INT)nSymbols.GetSize());
}

INT CTableViewComboBoxLineSymbolsCtrl::GetLineSymbol() CONST
{
	INT  nIndex;

	return(((nIndex = GetCurSel()) >= 0 && nIndex < GetCount()) ? (INT)GetItemData(nIndex) : -1);
}

CString CTableViewComboBoxLineSymbolsCtrl::GetLineSymbolAsText() CONST
{
	return TranslateLineSymbol(GetLineSymbol());
}

CString CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol(INT nSymbol)
{
	CStringTools  cStringTools;

	return cStringTools.ConvertIntToString(nSymbol);
}
INT CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol(LPCTSTR pszSymbol)
{
	CStringTools  cStringTools;

	return((lstrlen(pszSymbol) > 0) ? ((!cStringTools.ConvertIntToString(_ttoi(pszSymbol)).Compare(pszSymbol)) ? _ttoi(pszSymbol) : (((INT *)pszSymbol)[0])) : -1);
}

void CTableViewComboBoxLineSymbolsCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

CTableView *CTableViewComboBoxLineSymbolsCtrl::GetParent() CONST
{
	return((CTableView *)CLineSymbolsComboBox::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewComboBoxLineSymbolsCtrl, CLineSymbolsComboBox)
	//{{AFX_MSG_MAP(CTableViewComboBoxLineSymbolsCtrl)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_GETTEXT, OnGetText)
	ON_MESSAGE(WM_GETTEXTLENGTH, OnGetTextLength)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewComboBoxLineSymbolsCtrl message handlers

int CTableViewComboBoxLineSymbolsCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nSymbol;
	INT  nSymbols;

	if (CLineSymbolsComboBox::OnCreate(lpCreateStruct) != -1)
	{
		if ((nSymbols = (INT)m_nSymbols.GetSize()) > 0)
		{
			for (nSymbol = 0, ResetContent(); nSymbol < nSymbols; nSymbol++)
			{
				InsertLineSymbol(nSymbol, m_nSymbols.GetAt(nSymbol));
				continue;
			}
		}
		return 0;
	}
	return -1;
}

void CTableViewComboBoxLineSymbolsCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ScreenToClient(&pt);
	GetParent()->UpdateTablePosition(nFlags, pt);
	CLineSymbolsComboBox::OnMouseMove(nFlags, point);
}

void CTableViewComboBoxLineSymbolsCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_LEFT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(TRUE);
			return;
		}
	}
	if (nChar == VK_RIGHT)
	{
		if (HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTable(FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE)
	{
		GetParent()->SetActiveCell();
		return;
	}
	CLineSymbolsComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableViewComboBoxLineSymbolsCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CLineSymbolsComboBox::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CTableViewComboBoxLineSymbolsCtrl::OnSetText(WPARAM wParam, LPARAM lParam)
{
	SelectLineSymbol(-1, TranslateLineSymbol((LPCTSTR)lParam));
	return TRUE;
}

LRESULT CTableViewComboBoxLineSymbolsCtrl::OnGetText(WPARAM wParam, LPARAM lParam)
{
	return((!_tcscpy_s((LPTSTR)lParam, GetLineSymbolAsText().GetLength() + 1, GetLineSymbolAsText())) ? GetLineSymbolAsText().GetLength() : 0);
}

LRESULT CTableViewComboBoxLineSymbolsCtrl::OnGetTextLength(WPARAM wParam, LPARAM lParam)
{
	return GetLineSymbolAsText().GetLength() + 1;
}

LRESULT CTableViewComboBoxLineSymbolsCtrl::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	INT  nItem;
	INT  nItems;
	MEASUREITEMSTRUCT  sItem;

	for (nItem = -1, nItems = GetCount(), Default(); nItem < nItems; nItem++)
	{
		sItem.itemID = nItem;
		MeasureItem(&sItem);
		SetItemHeight(nItem, sItem.itemHeight);
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewSpinCtrl

IMPLEMENT_DYNCREATE(CTableViewSpinCtrl, CSpinBox)

CTableViewSpinCtrl::CTableViewSpinCtrl() : CSpinBox()
{
	m_nMin = 0;
	m_nMax = 0;
	m_nBase = 10;
	m_nDigits = 0;
	m_nAccel = 0;
	m_pAccel = (UDACCEL *)NULL;
}

CTableViewSpinCtrl::~CTableViewSpinCtrl()
{
	if (m_nAccel > 0)
	{
		GlobalFree(m_pAccel);
		m_pAccel = (UDACCEL *)NULL;
		m_nAccel = 0;
	}
}

BOOL CTableViewSpinCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle, INT nID)
{
	if (CSpinBox::Create(pParentWnd, rect, nID, dwStyle))
	{
		for (CSpinBox::SetBase(m_nBase, m_nDigits), CSpinBox::SetRange(m_nMin, m_nMax); m_nAccel > 0; )
		{
			CSpinBox::SetAccel(m_nAccel, m_pAccel);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

CString CTableViewSpinCtrl::TranslateNumber(LONGLONG nNumber)
{
	CStringTools  cStringTools;

	return cStringTools.ConvertLongIntToString(nNumber);
}

LONGLONG CTableViewSpinCtrl::TranslateNumber(LPCTSTR pszNumber)
{
	return _ttoi64(pszNumber);
}

CTableView *CTableViewSpinCtrl::GetParent() CONST
{
	return((CTableView *)CSpinBox::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewSpinCtrl, CSpinBox)
	//{{AFX_MSG_MAP(CTableViewSpinCtrl)
	ON_WM_CHAR()
	ON_MESSAGE(SBXM_SETBASE, OnSetBase)
	ON_MESSAGE(SBXM_GETBASE, OnGetBase)
	ON_MESSAGE(SBXM_SETRANGE, OnSetRange)
	ON_MESSAGE(SBXM_GETRANGE, OnGetRange)
	ON_MESSAGE(SBXM_SETACCEL, OnSetAccel)
	ON_MESSAGE(SBXM_GETACCEL, OnGetAccel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewSpinCtrl message handlers

void CTableViewSpinCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CSpinBox::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CTableViewSpinCtrl::OnSetBase(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETBASE, wParam, lParam) : FALSE);
}

LRESULT CTableViewSpinCtrl::OnGetBase(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETBASE, wParam, lParam) : FALSE);
}

LRESULT CTableViewSpinCtrl::OnSetRange(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETRANGE, wParam, lParam) : FALSE);
}

LRESULT CTableViewSpinCtrl::OnGetRange(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETRANGE, wParam, lParam) : FALSE);
}

LRESULT CTableViewSpinCtrl::OnSetAccel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndSpinCtrl.GetSafeHwnd())) ? m_wndSpinCtrl.SendMessage(UDM_SETACCEL, wParam, lParam) : FALSE);
}

LRESULT CTableViewSpinCtrl::OnGetAccel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndSpinCtrl.GetSafeHwnd())) ? m_wndSpinCtrl.SendMessage(UDM_GETACCEL, wParam, lParam) : FALSE);
}

// TableViewSpinCtrl helpers
BOOL TableViewSpinCtrl_SetPos(CWnd *pCtrl, LONGLONG nPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETPOS, (WPARAM)NULL, (LPARAM)&nPos));
}

LONGLONG TableViewSpinCtrl_GetPos(CWnd *pCtrl)
{
	LONGLONG  nPos;

	pCtrl->SendMessage(SBXM_GETPOS, (WPARAM)NULL, (LPARAM)&nPos);
	return nPos;
}

BOOL TableViewSpinCtrl_SetBase(CWnd *pCtrl, UINT nBase, UINT nDigits)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETBASE, nBase, nDigits));
}

BOOL TableViewSpinCtrl_GetBase(CWnd *pCtrl, UINT &nBase, UINT &nDigits)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETBASE, (WPARAM)&nBase, (LPARAM)&nDigits));
}

BOOL TableViewSpinCtrl_SetRange(CWnd *pCtrl, LONGLONG nMin, LONGLONG nMax)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETRANGE, (WPARAM)&nMin, (LPARAM)&nMax));
}

BOOL TableViewSpinCtrl_GetRange(CWnd *pCtrl, LONGLONG &nMin, LONGLONG &nMax)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETRANGE, (WPARAM)&nMin, (LPARAM)&nMax));
}

BOOL TableViewSpinCtrl_SetAccel(CWnd *pCtrl, INT nAccel, CONST UDACCEL *pAccel)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETACCEL, nAccel, (LPARAM)pAccel));
}

UINT TableViewSpinCtrl_GetAccel(CWnd *pCtrl, INT nAccel, UDACCEL *pAccel)
{
	return((UINT)pCtrl->SendMessage(SBXM_GETACCEL, nAccel, (LPARAM)pAccel));
}

BOOL TableViewSpinCtrl_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETSEL, nStartPos, nStopPos));
}

BOOL TableViewSpinCtrl_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETSEL, (WPARAM)&nStartPos, (LPARAM)&nStopPos));
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewTimeSpinCtrl

IMPLEMENT_DYNCREATE(CTableViewTimeSpinCtrl, CTimeSpinBox)

CTableViewTimeSpinCtrl::CTableViewTimeSpinCtrl() : CTimeSpinBox()
{
	m_tInitial = 0;
	m_tRange[0] = 0;
	m_tRange[1] = 0;
}

BOOL CTableViewTimeSpinCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, LPCTSTR pszFormat, DWORD dwStyle, INT nID)
{
	CTimeTag  tTime;

	if (CTimeSpinBox::Create(pParentWnd, rect, nID, dwStyle, (m_szFormat = pszFormat), m_tRange[0], m_tRange[1]))
	{
		TableViewTimeSpinCtrl_SetTime(this, (m_tInitial == 0) ? (((m_dwStyle & TSBXS_SPAN_TIME) == 0) ? tTime : 0) : m_tInitial);
		return TRUE;
	}
	return FALSE;
}

CString CTableViewTimeSpinCtrl::TranslateTime(TIMETAG tTime, BOOL bSpan)
{
	CStringTools  cStringTools;

	return((tTime > 0 || bSpan) ? cStringTools.ConvertLongIntToString(tTime) : EMPTYSTRING);
}

TIMETAG CTableViewTimeSpinCtrl::TranslateTime(LPCTSTR pszTime)
{
	return _ttoi64(pszTime);
}

CString CTableViewTimeSpinCtrl::TranslateTimeAndFormat(LPCTSTR pszTime, LPCTSTR pszFormat)
{
	return TranslateTimeAndFormat(pszTime, EMPTYSTRING, pszFormat);
}
CString CTableViewTimeSpinCtrl::TranslateTimeAndFormat(LPCTSTR pszTime, LPCTSTR pszInitialTime, LPCTSTR pszFormat)
{
	return pszTime + GetSeparator() + pszInitialTime + GetSeparator() + pszFormat;
}
VOID CTableViewTimeSpinCtrl::TranslateTimeAndFormat(LPCTSTR pszTimeAndFormat, CString &szTime, CString &szInitialTime, CString &szFormat)
{
	INT  nPos[2];
	CString  szSeparator;
	CString  szTimeAndFormat;

	for (szTimeAndFormat = pszTimeAndFormat; (nPos[0] = szTimeAndFormat.Find((szSeparator = GetSeparator()))) >= 0; )
	{
		if ((nPos[1] = ((nPos[1] = szTimeAndFormat.Mid(nPos[0] + szSeparator.GetLength()).Find(szSeparator)) >= 0) ? (nPos[0] + nPos[1] + szSeparator.GetLength()) : -1) >= 0)
		{
			szInitialTime = szTimeAndFormat.Mid(nPos[0] + szSeparator.GetLength(), nPos[1] - nPos[0] - szSeparator.GetLength());
			szFormat = szTimeAndFormat.Mid(nPos[1] + szSeparator.GetLength());
			szTime = szTimeAndFormat.Left(nPos[0]);
			return;
		}
	}
	szTime = szTimeAndFormat;
	szInitialTime.Empty();
	szFormat.Empty();
}

BOOL CTableViewTimeSpinCtrl::IsValidTime(LPCTSTR pszTime)
{
	INT  nLength;

	return((nLength = lstrlen(pszTime)) > 0 && _tcscspn(pszTime, CString(TAB)) == nLength);
}

CString CTableViewTimeSpinCtrl::GetSeparator()
{
	CString  szSeparator;

	szSeparator = EOL;
	szSeparator += CR;
	return szSeparator;
}

CTableView *CTableViewTimeSpinCtrl::GetParent() CONST
{
	return((CTableView *)CTimeSpinBox::GetParent());
}

BEGIN_MESSAGE_MAP(CTableViewTimeSpinCtrl, CTimeSpinBox)
	//{{AFX_MSG_MAP(CTableViewTimeSpinCtrl)
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE(TSBXM_SETTIME, OnSetTime)
	ON_MESSAGE(TSBXM_GETTIME, OnGetTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableViewTimeSpinCtrl message handlers

void CTableViewTimeSpinCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNextTableCell((HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE);
			return;
		}
	}
	if (nChar == VK_ESCAPE) return;
	CTimeSpinBox::OnChar(nChar, nRepCnt, nFlags);
}

void CTableViewTimeSpinCtrl::OnTimer(UINT_PTR nEventID)
{
	if (!nEventID)
	{
		if (m_bState[0]) GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_SETFOCUS), (LPARAM)GetSafeHwnd());
		KillTimer(nEventID);
		return;
	}
	CTimeSpinBox::OnTimer(nEventID);
}

LRESULT CTableViewTimeSpinCtrl::OnSetTime(WPARAM wParam, LPARAM lParam)
{
	INT  nPos;
	INT  nCtrl;
	INT  nCtrls;
	CWnd  *pCtrl;
	CString  szTime;

	if (wParam == (WPARAM)-1)
	{
		for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(), szTime = (LPCTSTR)lParam; nCtrl < nCtrls; nCtrl++)
		{
			if ((pCtrl = (CWnd *)m_pwndEditCtrls.GetAt(nCtrl)))
			{
				if ((nPos = szTime.Find(TAB)) >= 0)
				{
					pCtrl->SendMessage(WM_SETTEXT, TRUE, (LPARAM)(LPCTSTR)szTime.Left(nPos));
					szTime = szTime.Mid(nPos + 1);
				}
			}
		}
		return 0;
	}
	for (CTimeSpinBox::OnSetTime(wParam, lParam); (m_dwStyle & TSBXS_SPAN_TIME) == 0 && m_tTime == 0; )
	{
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_CHANGE), (LPARAM)GetSafeHwnd());
		break;
	}
	return 0;
}

LRESULT CTableViewTimeSpinCtrl::OnGetTime(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	CWnd  *pCtrl;
	TIMETAG  tTime;
	CString  szTime;
	CString  szText;
	LRESULT  lResult;

	if (wParam == (WPARAM)-1)
	{
		for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
		{
			if ((pCtrl = (CWnd *)m_pwndEditCtrls.GetAt(nCtrl)))
			{
				pCtrl->GetWindowText(szText);
				szTime += szText + TAB;
			}
		}
		CopyMemory((LPVOID)lParam, (LPCTSTR)szTime, min((szTime.GetLength() + 1)*sizeof(TCHAR), 10 * m_szFormat.GetLength()*sizeof(TCHAR)));
		return !szTime.IsEmpty();
	}
	for (lResult = CTimeSpinBox::OnGetTime(wParam, lParam), CopyMemory(&tTime, (LPCVOID)lParam, sizeof(tTime)); (m_dwStyle & TSBXS_SPAN_TIME) == 0 && tTime < 0; )
	{
		CopyMemory((LPVOID)lParam, &(tTime = -tTime), sizeof(tTime));
		break;
	}
	return lResult;
}

void CTableViewTimeSpinCtrl::OnDestroy()
{
	CTimeTag  tTime;

	for (EnableAutoCompletion(FALSE); !GetTime(tTime); )
	{
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_CHANGE), (LPARAM)GetSafeHwnd());
		break;
	}
	GetParent()->SetFocus();
	CTimeSpinBox::OnDestroy();
}


// TableViewTimeSpinCtrl helpers
VOID TableViewTimeSpinCtrl_SetTime(CWnd *pCtrl)
{
	Timespinbox_SetTime(pCtrl);
}
VOID TableViewTimeSpinCtrl_SetTime(CWnd *pCtrl, CONST CTimeTag &tTime)
{
	Timespinbox_SetTime(pCtrl, tTime);
}
VOID TableViewTimeSpinCtrl_SetTime(CWnd *pCtrl, LPCTSTR pszTime)
{
	pCtrl->SendMessage(TSBXM_SETTIME, (WPARAM)-1, (LPARAM)pszTime);
}

CTimeTag TableViewTimeSpinCtrl_GetTime(CWnd *pCtrl)
{
	CTimeTag  tTime;

	return((Timespinbox_GetTime(pCtrl, tTime)) ? tTime : 0);
}
BOOL TableViewTimeSpinCtrl_GetTime(CWnd *pCtrl, CTimeTag &tTime)
{
	return Timespinbox_GetTime(pCtrl, tTime);
}
BOOL TableViewTimeSpinCtrl_GetTime(CWnd *pCtrl, CString &szTime)
{
	CTableViewTimeSpinCtrl  *pTimeSpinBox;

	for (szTime.Empty(); (pTimeSpinBox = (pCtrl->IsKindOf(RUNTIME_CLASS(CTableViewTimeSpinCtrl))) ? (CTableViewTimeSpinCtrl *)pCtrl : (CTableViewTimeSpinCtrl *)NULL); )
	{
		if (pCtrl->SendMessage(TSBXM_GETTIME, (WPARAM)-1, (LPARAM)szTime.GetBufferSetLength(10 * pTimeSpinBox->GetFormat().GetLength())))
		{
			szTime.ReleaseBuffer();
			return TRUE;
		}
		szTime.ReleaseBuffer();
		break;
	}
	return FALSE;
}

BOOL TableViewTimeSpinCtrl_SetRange(CWnd *pCtrl, CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	return Timespinbox_SetRange(pCtrl, tStartTime, tStopTime);
}

BOOL TableViewTimeSpinCtrl_GetRange(CWnd *pCtrl, CTimeTag &tStartTime, CTimeTag &tStopTime)
{
	return Timespinbox_GetRange(pCtrl, tStartTime, tStopTime);
}

BOOL TableViewTimeSpinCtrl_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos)
{
	return Timespinbox_SetSel(pCtrl, nStartPos, nStopPos);
}

BOOL TableViewTimeSpinCtrl_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos)
{
	return Timespinbox_GetSel(pCtrl, nStartPos, nStopPos);
}


/////////////////////////////////////////////////////////////////////////////
// CTableViewDocument

IMPLEMENT_DYNAMIC(CTableViewDocument, CDocument)

CTableViewDocument::CTableViewDocument() : CDocument()
{
	return;
}

CTableViewDocument::~CTableViewDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTableView

IMPLEMENT_DYNCREATE(CTableView, CScrollView)

CTableView::CTableView() : CScrollView()
{
	m_pTables = new CTableViewObjects;
	m_pTable = m_pDragTable = (CTableViewObject *)NULL;
	m_pCell = (CTableViewCell *)NULL;
	m_pParentWnd = (CWnd *)NULL;
}

CTableView::~CTableView()
{
	delete m_pTables;
}

BOOL CTableView::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle)
{
	CCreateContext  cContext;

	cContext.m_pCurrentDoc = new CTableViewDocument;
	return CScrollView::Create(AfxRegisterWndClass(CS_DBLCLKS | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(COLOR_WINDOW)), (LPCTSTR)NULL, dwStyle, rect, (m_pParentWnd = pParentWnd), 0, &cContext);
}

BOOL CTableView::AddTable(CTableViewObject *pTable, BOOL bRedraw)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nIndex;
	CTableViewCell  *pCell;

	if ((nIndex = m_pTables->Add(pTable)) >= 0)
	{
		for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
		{
			for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				if ((pCell = pTable->FindCell(nRow, nCol)))
				{
					pCell->CreateControl();
					continue;
				}
			}
		}
		for (RecalcScrollSizes(); bRedraw; )
		{
			DrawTables();
			break;
		}
		return TRUE;
	}
	return FALSE;
}

CTableViewObject *CTableView::FindTable(LPCTSTR pszName) CONST
{
	return m_pTables->GetAt(m_pTables->Find(pszName));
}

BOOL CTableView::RemoveTable(LPCTSTR pszName, BOOL bRedraw)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nIndex;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	if ((pTable = m_pTables->GetAt((nIndex = m_pTables->Find(pszName)))) >= 0)
	{
		for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow = nRow + 1)
		{
			for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				if ((pCell = pTable->FindCell(nRow, nCol)))
				{
					pCell->DestroyControl();
					continue;
				}
			}
		}
		for (m_pTables->RemoveAt(nIndex), RecalcScrollSizes(); bRedraw; )
		{
			DrawTables();
			break;
		}
		delete pTable;
		return TRUE;
	}
	return FALSE;
}

BOOL CTableView::ActivateTable()
{
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_NORMAL  &&  pTable->IsVisible())
		{
			if (ActivateTable(pTable)) break;
			continue;
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}
BOOL CTableView::ActivateTable(CTableViewObject *pTable, BOOL bPrevious)
{
	INT  nCol;
	INT  nRow;
	INT  nCols;
	INT  nRows;
	CTableViewCell  *pCell;
	CTableViewObject  *pSubTable;

	if (pTable->IsVisible())
	{
		for (nRow = (bPrevious) ? (pTable->GetRows() - 1) : 0, nRows = pTable->GetRows(); nRow >= 0 && nRow < nRows; nRow = (!bPrevious) ? (nRow + 1) : (nRow - 1))
		{
			for (nCol = (bPrevious) ? (pTable->GetColumns() - 1) : 0, nCols = pTable->GetColumns(); nCol >= 0 && nCol < nCols; nCol = (!bPrevious) ? (nCol + 1) : (nCol - 1))
			{
				if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
				{
					if (pCell->IsEnabled() && pCell->GetControl())
					{
						SetActiveCell(pTable, pCell);
						break;
					}
					if (pCell->GetFormat() & TAS_TYPE_SUBTABLE)
					{
						if ((pSubTable = m_pTables->GetAt(m_pTables->Find(pCell->GetSubTable()))))
						{
							if (ActivateTable(pSubTable, bPrevious)) return TRUE;
							continue;
						}
					}
				}
			}
			if (nCol >= 0 && nCol < nCols) break;
		}
		return((nRow >= 0 && nRow < nRows) ? TRUE : FALSE);
	}
	return FALSE;
}

CTableViewObject *CTableView::GetActiveTable() CONST
{
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	if (!GetActiveCell(pTable))
	{
		for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
		{
			if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetSelRow() >= 0) break;
			continue;
		}
		return((nTable < nTables) ? m_pTables->GetAt(nTable) : (CTableViewObject *)NULL);
	}
	return pTable;
}

BOOL CTableView::ActivateNextTable(BOOL bPrevious)
{
	INT  nTable[2];
	INT  nTables[2];
	CTableViewCell  *pCell;
	CTableViewObject  *pTable[2];

	if ((pCell = GetActiveCell(pTable[0])))
	{
		for (nTable[0] = 0, nTables[0] = (INT)m_pTables->GetSize(); nTable[0] < nTables[0]; nTable[0]++)
		{
			if ((pTable[1] = m_pTables->GetAt(nTable[0])) && pTable[0]->GetName() == pTable[1]->GetName())
			{
				for (nTable[1] = (!bPrevious) ? (nTable[0] + 1) : (nTable[0] - 1), nTable[1] = (nTable[1] < 0) ? (nTables[0] - 1) : nTable[1], nTable[1] = (nTable[1] < nTables[0]) ? nTable[1] : 0, nTables[1] = 0; nTables[0] > nTables[1]; nTable[1] = (!bPrevious) ? (nTable[1] + 1) : (nTable[1] - 1), nTable[1] = (nTable[1] < 0) ? (nTables[0] - 1) : nTable[1], nTable[1] = (nTable[1] < nTables[0]) ? nTable[1] : 0, nTables[1]++)
				{
					if ((pTable[1] = m_pTables->GetAt(nTable[1])) && pTable[1]->IsVisible())
					{
						if (ActivateTable(pTable[1], bPrevious)) break;
						continue;
					}
				}
				return((nTables[0] > nTables[1]) ? TRUE : FALSE);
			}
		}
	}
	return FALSE;
}

BOOL CTableView::ActivateNextTableCell(BOOL bPrevious)
{
	INT  nCol;
	INT  nRow;
	INT  nCols;
	INT  nRows;
	INT  nTable;
	INT  nTables;
	CTableViewCell  *pCell[3];
	CTableViewObject  *pTable[3];

	if ((pCell[0] = GetActiveCell(pTable[0])))
	{
		for (nRow = pCell[0]->y, nRows = pTable[0]->GetRows(); nRow >= 0 && nRow < nRows; nRow = (!bPrevious) ? (nRow + 1) : (nRow - 1))
		{
			for (nCol = (nRow == pCell[0]->y) ? ((!bPrevious) ? (pCell[0]->x + 1) : (pCell[0]->x - 1)) : ((bPrevious) ? (pTable[0]->GetColumns() - 1) : 0), nCols = pTable[0]->GetColumns(); nCol >= 0 && nCol < nCols; nCol = (!bPrevious) ? (nCol + 1) : (nCol - 1))
			{
				if ((pCell[1] = pTable[0]->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
				{
					if (pCell[1]->IsEnabled() && pCell[1]->GetControl())
					{
						SetActiveCell(pTable[0], pCell[1]);
						return TRUE;
					}
					if (pCell[1]->GetFormat() & TAS_TYPE_SUBTABLE)
					{
						if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(pCell[1]->GetSubTable()))))
						{
							if (ActivateTable(pTable[1], bPrevious)) return TRUE;
							continue;
						}
					}
				}
			}
		}
		for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
		{
			if ((pTable[1] = m_pTables->GetAt(nTable)) != (CTableViewObject *)NULL)
			{
				if ((pCell[1] = pTable[1]->FindCell(pCell[0]->GetPosition().CenterPoint())))
				{
					if ((pCell[1]->GetFormat() & TAS_TYPE_SUBTABLE) && !pCell[1]->GetSubTable().Compare(pTable[0]->GetName()))
					{
						for (nRow = pCell[1]->y; nRow >= 0 && nRow < pTable[1]->GetRows(); nRow = (!bPrevious) ? (nRow + 1) : (nRow - 1))
						{
							for (nCol = (nRow == pCell[1]->y) ? ((!bPrevious) ? (pCell[1]->x + 1) : (pCell[1]->x - 1)) : ((bPrevious) ? (pTable[1]->GetColumns() - 1) : 0); nCol >= 0 && nCol < pTable[1]->GetColumns(); nCol = (!bPrevious) ? (nCol + 1) : (nCol - 1))
							{
								if ((pCell[2] = pTable[1]->FindCell(nRow, nCol)) && pCell[2]->IsEnabled() && pCell[2]->GetControl())
								{
									for (pTable[0]->SetSelCell(); pTable[1]->GetType() == TAS_TABLE_LIST; )
									{
										pTable[1]->SetSelRow(pCell[2]->y);
										break;
									}
									SetActiveCell(pTable[1], pCell[2]);
									return TRUE;
								}
								if (pCell[2]->GetFormat() & TAS_TYPE_SUBTABLE)
								{
									if ((pTable[2] = m_pTables->GetAt(m_pTables->Find(pCell[2]->GetSubTable()))))
									{
										if (ActivateTable(pTable[2], bPrevious)) return TRUE;
										continue;
									}
								}
							}
						}
					}
				}
			}
		}
		for (nRow = (bPrevious) ? (nRows - 1) : 0; nRow >= 0 && nRow < nRows; nRow = (!bPrevious) ? (nRow + 1) : (nRow - 1))
		{
			for (nCol = (bPrevious) ? (nCols - 1) : 0; nCol >= 0 && nCol < nCols; nCol = (!bPrevious) ? (nCol + 1) : (nCol - 1))
			{
				if ((pCell[1] = pTable[0]->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
				{
					if (pCell[1]->IsEnabled() && pCell[1]->GetControl())
					{
						SetActiveCell(pTable[0], pCell[1]);
						return TRUE;
					}
					if (pCell[1]->GetFormat() & TAS_TYPE_SUBTABLE)
					{
						if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(pCell[1]->GetSubTable()))))
						{
							if (ActivateTable(pTable[1], bPrevious)) return TRUE;
							continue;
						}
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CTableView::SetActiveCell(LPCTSTR pszInitialText)
{
	CWnd  *pControl;
	CRect  rCell[2];
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	if ((pCell = GetActiveCell(pTable)))
	{
		if ((pControl = pCell->GetControl()))
		{
			for (pCell->UpdateText(pszInitialText), rCell[0] = pCell->GetPosition(), RecalcTableRow(pTable, pCell->y, FALSE), rCell[1] = pCell->GetPosition(); rCell[1].Height() != rCell[0].Height(); )
			{
				pTable->SetRect(pTable->left, pTable->top, pTable->right, pTable->bottom + rCell[1].Height() - rCell[0].Height());
				RepositionTables();
				break;
			}
			pCell->Activate(this, FALSE);
			SetFocus();
		}
		m_pTable = (CTableViewObject *)NULL;
		m_pCell = (CTableViewCell *)NULL;
		DrawTables();
		return TRUE;
	}
	return FALSE;
}
BOOL CTableView::SetActiveCell(UINT nAction)
{
	CWnd  *pControl;
	CRect  rCell[2];
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	if ((pCell = GetActiveCell(pTable)))
	{
		if ((pControl = pCell->GetControl()))
		{
			for (pCell->UpdateText(nAction), rCell[0] = pCell->GetPosition(), RecalcTableRow(pTable, pCell->y, FALSE), rCell[1] = pCell->GetPosition(); rCell[1].Height() != rCell[0].Height(); )
			{
				pTable->SetRect(pTable->left, pTable->top, pTable->right, pTable->bottom + rCell[1].Height() - rCell[0].Height());
				RepositionTables();
				break;
			}
			pCell->Activate(this, FALSE);
			SetFocus();
		}
		m_pTable = (CTableViewObject *)NULL;
		m_pCell = (CTableViewCell *)NULL;
		DrawTables();
		return TRUE;
	}
	return FALSE;
}
BOOL CTableView::SetActiveCell(CTableViewObject *pTable, CTableViewCell *pCell, UINT nAction)
{
	CWnd  *pControl;
	CRect  rView[1];
	CRect  rCell[2];
	CPoint  ptScroll;
	CString  szText;
	CTableViewTimeSpinCtrl  *pTimeSpinCtrl;

	if (pCell != GetActiveCell())
	{
		if ((pControl = (pCell->IsEnabled() && pCell->Activate(this)) ? pCell->GetControl() : (CWnd *)NULL))
		{
			for (SetActiveCell(nAction), szText = pCell->GetText(), pCell->SetText((pCell->GetFormat() & TAS_TYPE_TIMESPINBOX) ? szText : EMPTYSTRING); ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT)) && nAction == TAS_ACTION_NORMAL; )
			{
				for (pControl->SetWindowText(szText); (pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT); )
				{
					pControl->SendMessage(EM_SETSEL, 0, -1);
					break;
				}
				if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT)) pControl->SendMessage(EM_SETSEL);
				break;
			}
			for (; nAction == TAS_ACTION_NORMAL; )
			{
				if ((pCell->GetFormat() & TAS_TYPE_COMBOLISTBOX) || (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX))
				{
					pControl->SendMessage(CB_SETCURSEL, (WPARAM)pControl->SendMessage(CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText));
					break;
				}
				if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
				{
					pControl->SetWindowText(szText);
					pControl->SendMessage(CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
					break;
				}
				if (pCell->GetFormat() & TAS_TYPE_COMBOCOLORSBOX)
				{
					if (!szText.IsEmpty() && CTableViewComboBoxColorsCtrl::TranslateColor(szText) != -1)
					{
						pControl->SendMessage(CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)CTableViewComboBoxColorsCtrl::TranslateColor(szText));
						break;
					}
					pControl->SendMessage(CB_SETCURSEL, (WPARAM)-1);
					break;
				}
				if (pCell->GetFormat() & TAS_TYPE_COMBOLINESTYLESBOX)
				{
					if (!szText.IsEmpty() && CTableViewComboBoxLineStylesCtrl::TranslateLineStyle(szText) != -1)
					{
						pControl->SendMessage(LSCB_SELECTLINESTYLE, (WPARAM)-1, (LPARAM)CTableViewComboBoxLineStylesCtrl::TranslateLineStyle(szText));
						break;
					}
					pControl->SendMessage(CB_SETCURSEL, (WPARAM)-1);
					break;
				}
				if (pCell->GetFormat() & TAS_TYPE_COMBOLINESYMBOLSBOX)
				{
					if (!szText.IsEmpty() && CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol(szText) != -1)
					{
						pControl->SendMessage(LSCB_SELECTLINESYMBOL, (WPARAM)-1, (LPARAM)CTableViewComboBoxLineSymbolsCtrl::TranslateLineSymbol(szText));
						break;
					}
					pControl->SendMessage(CB_SETCURSEL, (WPARAM)-1);
					break;
				}
				if (pCell->GetFormat() & TAS_TYPE_SPINBOX)
				{
					TableViewSpinCtrl_SetPos(pControl, CTableViewSpinCtrl::TranslateNumber(szText));
					break;
				}
				if (pCell->GetFormat() & TAS_TYPE_TIMESPINBOX)
				{
					if ((pTimeSpinCtrl = (CTableViewTimeSpinCtrl *)pControl) && pTimeSpinCtrl->GetInitialTime() > 0 && szText.IsEmpty())
					{
						TableViewTimeSpinCtrl_SetTime(pControl, pTimeSpinCtrl->GetInitialTime());
						break;
					}
					if (!szText.IsEmpty())
					{
						TableViewTimeSpinCtrl_SetTime(pControl, CTableViewTimeSpinCtrl::TranslateTime(szText));
						break;
					}
					TableViewTimeSpinCtrl_SetTime(pControl);
				}
				break;
			}
			GetClientRect(rView[0]);
			rCell[0] = pCell->GetPosition();
			rCell[0].OffsetRect(-GetScrollPosition());
			for (m_pTable = pTable, m_pCell = pCell; !rCell[1].IntersectRect(rView[0], rCell[0]) || rCell[0] != rCell[1]; )
			{
				ptScroll.x = (rCell[0].left < rView[0].left) ? (GetScrollPosition().x + rCell[0].left - rView[0].left) : GetScrollPosition().x;
				ptScroll.x = (rCell[0].left > rView[0].right) ? (GetScrollPosition().x + rCell[0].left - rView[0].right + rCell[0].Height()) : ptScroll.x;
				ptScroll.y = (rCell[0].top < rView[0].top) ? (GetScrollPosition().y + rCell[0].top - rView[0].top) : GetScrollPosition().y;
				ptScroll.y = (rCell[0].bottom > rView[0].bottom) ? (GetScrollPosition().y + rCell[0].bottom - rView[0].bottom) : ptScroll.y;
				ScrollToPosition(ptScroll);
				break;
			}
			for (DrawTables(); nAction == TAS_ACTION_NORMAL; )
			{
				pControl->ShowWindow(SW_SHOW);
				pControl->SetFocus();
				break;
			}
			return TRUE;
		}
	}
	else
	{
		if (IsWindow((pControl = pCell->GetControl())->GetSafeHwnd()))
		{
			if (!IsWindow(GetFocus()->GetSafeHwnd()) || (pControl->GetSafeHwnd() != GetFocus()->GetSafeHwnd() && !pControl->IsChild(GetFocus())))
			{
				for (; ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT)) && nAction == TAS_ACTION_NORMAL; )
				{
					pControl->SendMessage(EM_SETSEL, 0, ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT)) ? 0 : -1);
					break;
				}
				for (; nAction == TAS_ACTION_NORMAL; )
				{
					if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
					{
						pControl->SendMessage(CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
						break;
					}
					if (pCell->GetFormat() & TAS_TYPE_SPINBOX)
					{
						TableViewSpinCtrl_SetSel(pControl, 0, -1);
						break;
					}
					if (pCell->GetFormat() & TAS_TYPE_TIMESPINBOX) TableViewTimeSpinCtrl_SetSel(pControl, 0, -1);
					break;
				}
			}
			for (GetClientRect(rView[0]), rCell[0] = pCell->GetPosition(), rCell[0].OffsetRect(-GetScrollPosition()); !rCell[1].IntersectRect(rView[0], rCell[0]) || rCell[0] != rCell[1]; )
			{
				ptScroll.x = (rCell[0].left < rView[0].left) ? (GetScrollPosition().x + rCell[0].left - rView[0].left) : GetScrollPosition().x;
				ptScroll.x = (rCell[0].left > rView[0].right) ? (GetScrollPosition().x + rCell[0].left - rView[0].right + rCell[0].Height()) : ptScroll.x;
				ptScroll.y = (rCell[0].top < rView[0].top) ? (GetScrollPosition().y + rCell[0].top - rView[0].top) : GetScrollPosition().y;
				ptScroll.y = (rCell[0].bottom > rView[0].bottom) ? (GetScrollPosition().y + rCell[0].bottom - rView[0].bottom) : ptScroll.y;
				ScrollToPosition(ptScroll);
				break;
			}
			for (DrawTables(); nAction == TAS_ACTION_NORMAL; )
			{
				pControl->SetFocus();
				break;
			}
			return TRUE;
		}
	}
	return FALSE;
}

CTableViewCell *CTableView::GetActiveCell(CTableViewObject *&pTable) CONST
{
	pTable = m_pTable;
	return GetActiveCell();
}
CTableViewCell *CTableView::GetActiveCell() CONST
{
	return m_pCell;
}

VOID CTableView::UpdateTablePosition(UINT nFlags, CPoint point)
{
	return;
}

VOID CTableView::ScrollTableRows(CTableViewObject *pTable, BOOL bDown)
{
	INT  nRow;
	INT  nRows;
	CRect  rView;
	CRect  rCell[2];
	CTableViewCell  *pCell[2];

	if ((pCell[0] = pTable->FindCell((nRow = pTable->GetSelRow()), 0)))
	{
		for (nRows = pTable->GetRows(), rCell[0] = pCell[0]->GetPosition(), RepositionBars(0, 0xFFFF, AFX_IDW_PANE_FIRST, CWnd::reposQuery, rView); nRow < nRows && nRow >= 0; nRow = (bDown) ? (nRow + 1) : (nRow - 1))
		{
			if ((pCell[1] = pTable->FindCell(nRow, 0)))
			{
				rCell[1] = pCell[1]->GetPosition();
				if (abs(rCell[0].top - rCell[1].top) >= rView.Height() || (bDown  &&  nRow == nRows - 1) || (!bDown && ((!pTable->HasTitle() && !nRow) || (pTable->HasTitle() && nRow == 1))))
				{
					pTable->SetSelRow(nRow);
					ScrollToTableRow(pTable, nRow);
					break;
				}
			}
		}
	}
}

VOID CTableView::ScrollToTableRow(CTableViewObject *pTable, INT nRow)
{
	CRect  rArea;
	CRect  rView;
	CRect  rCell[2];
	CTableViewCell  *pCell;

	if ((pCell = pTable->FindCell(nRow, 0)))
	{
		for (rCell[0] = rCell[1] = pCell->GetPosition(), rCell[1].OffsetRect(-GetScrollPosition()), RepositionBars(0, 0xFFFF, AFX_IDW_PANE_FIRST, CWnd::reposQuery, rView); !rArea.IntersectRect(rView, rCell[1]) && rView.top > rCell[1].top; )
		{
			ScrollToPosition(CPoint(GetScrollPosition().x, rCell[0].top - rView.top));
			break;
		}
		for (; !rArea.IntersectRect(rView, rCell[1]) && rView.bottom < rCell[1].bottom; )
		{
			ScrollToPosition(CPoint(GetScrollPosition().x, rCell[0].bottom - rView.bottom));
			break;
		}
	}
	DrawTables();
}

VOID CTableView::ScrollToTableColumn(CTableViewObject *pTable, INT nColumn)
{
	CRect  rArea;
	CRect  rView;
	CRect  rCell[2];
	CTableViewCell  *pCell;

	if ((pCell = pTable->FindCell(0, nColumn)))
	{
		for (rCell[0] = rCell[1] = pCell->GetPosition(), rCell[1].OffsetRect(-GetScrollPosition()), RepositionBars(0, 0xFFFF, AFX_IDW_PANE_FIRST, CWnd::reposQuery, rView); !rArea.IntersectRect(rView, rCell[1]) && rView.left > rCell[1].left; )
		{
			ScrollToPosition(CPoint(rCell[0].left - rView.left, GetScrollPosition().y));
			break;
		}
		for (; !rArea.IntersectRect(rView, rCell[1]) && rView.right < rCell[1].right; )
		{
			ScrollToPosition(CPoint(rCell[0].right - rView.right, GetScrollPosition().y));
			break;
		}
	}
	DrawTables();
}

VOID CTableView::RecalcScrollSizes()
{
	INT  nSize;
	INT  nStyle;
	INT  nTable;
	INT  nTables;
	CRect  rTables[3];
	COLORREF  nColor;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), rTables[0].SetRectEmpty(), rTables[1].SetRectEmpty(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) != (CTableViewObject *)NULL  &&  pTable->IsVisible())
		{
			for (rTables[2] = pTable; pTable->GetCellBorder(pTable->GetColumns() - 1, pTable->GetRows() - 1, TAS_BORDER_RIGHT, nSize, nStyle, nColor); )
			{
				rTables[2].right += (nSize + 1) / 2;
				break;
			}
			rTables[2].bottom += (pTable->GetCellBorder(pTable->GetColumns() - 1, pTable->GetRows() - 1, TAS_BORDER_BOTTOM, nSize, nStyle, nColor)) ? ((nSize + 1) / 2) : 0;
			rTables[1].UnionRect(rTables[2], rTables[0]);
			rTables[0] = rTables[1];
		}
	}
	SetScrollSizes(MM_TEXT, CSize(rTables[0].right, rTables[0].bottom));
}

CWnd *CTableView::GetParent() CONST
{
	return m_pParentWnd;
}

VOID CTableView::RepositionTables()
{
	return;
}

VOID CTableView::RecalcTables(BOOL bRedraw)
{
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)))
		{
			RecalcTable(pTable, bRedraw);
			continue;
		}
	}
}

VOID CTableView::RecalcTable(CTableViewObject *pTable, BOOL bRedraw)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nWidth;
	INT  nHeight;
	CRect  rCell;
	CTableViewCell  *pCell;

	for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
	{
		for (nCol = 0, nCols = pTable->GetColumns(), nHeight = 0; nCol < nCols; nCol++)
		{
			if ((pCell = pTable->FindCell(nRow, nCol)))
			{
				rCell = CalcTableCellExtent(pCell);
				nHeight = max(rCell.Height(), nHeight);
			}
		}
		pTable->SetRowHeight(nRow, nHeight);
	}
	for (nCol = 0; nCol < nCols; nCol++)
	{
		for (nRow = 0, nWidth = 0; nRow < nRows; nRow++)
		{
			if ((pCell = pTable->FindCell(nRow, nCol)))
			{
				rCell = CalcTableCellExtent(pCell);
				nWidth = max(rCell.Width(), nWidth);
			}
		}
		pTable->SetColumnWidth(nCol, nWidth);
	}
	if (bRedraw) DrawTables();
}

VOID CTableView::RecalcTableRow(CTableViewObject *pTable, INT nRow, BOOL bAdjust)
{
	INT  nCol;
	INT  nCols;
	INT  nHeight;
	CRect  rCell[2];
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = pTable->GetColumns(), nHeight = 0; nCol < nCols; nCol++)
	{
		if ((pCell = pTable->FindCell(nRow, nCol)))
		{
			rCell[0] = pCell->GetPosition();
			rCell[1] = CalcTableCellPosition(pCell);
			nHeight = (!bAdjust) ? max(max(rCell[0].Height(), rCell[1].Height()), nHeight) : max(rCell[1].Height(), nHeight);
		}
	}
	pTable->SetRowHeight(nRow, nHeight);
}

VOID CTableView::RecalcTableColumn(CTableViewObject *pTable, INT nCol, BOOL bAdjust)
{
	INT  nRow;
	INT  nRows;
	INT  nWidth;
	CRect  rCell[2];
	CTableViewCell  *pCell;

	for (nRow = 0, nRows = pTable->GetRows(), nWidth = 0; nRow < nRows; nRow++)
	{
		if ((pCell = pTable->FindCell(nRow, nCol)))
		{
			rCell[0] = pCell->GetPosition();
			rCell[1] = CalcTableCellExtent(pCell);
			nWidth = (!bAdjust) ? max(max(rCell[0].Width(), rCell[1].Width()), nWidth) : max(rCell[1].Width(), nWidth);
		}
	}
	pTable->SetColumnWidth(nCol, nWidth);
}

CRect CTableView::CalcTableCellExtent(CONST CTableViewCell *pCell)
{
	CDC  *pDC;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rCell[4];
	CSize  sizeText;
	LOGFONT  lfFont;
	TEXTMETRIC  tmFont;
	CTableViewObject  *pTable;

	if ((pDC = GetDC()))
	{
		for (rCell[0] = rCell[1] = pCell->GetPosition(), rCell[2] = pCell->GetInnerPosition(), pCell->GetFont(&lfFont), sizeText.cx = sizeText.cy = 0; cFont.CreateFontIndirect(&lfFont); )
		{
			if ((pTable = (pCell->GetFormat() & TAS_TYPE_SUBTABLE) ? m_pTables->GetAt(m_pTables->Find(pCell->GetSubTable())) : (CTableViewObject *)NULL) && pTable->IsVisible())
			{
				rCell[0].InflateRect(0, 0, pTable->Width() - rCell[2].Width(), pTable->Height() - rCell[2].Height());
				ReleaseDC(pDC);
				return rCell[0];
			}
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				if (pDC->GetTextMetrics(&tmFont) != 0)
				{
					if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT))
					{
						pDC->DrawText(pCell->GetText(), (rCell[3] = rCell[0]), ((pCell->GetFormat() & TAS_ALIGN_LEFT) ? DT_LEFT : 0) | ((pCell->GetFormat() & TAS_ALIGN_RIGHT) ? DT_RIGHT : 0) | ((pCell->GetFormat() & TAS_ALIGN_HCENTER) ? DT_CENTER : 0) | DT_CALCRECT | DT_TOP | DT_EXPANDTABS | DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_NOPREFIX);
						sizeText.cx = min(pDC->GetTextExtent(pCell->GetText()).cx, rCell[3].Width());
						sizeText.cy = max(rCell[3].Height(), tmFont.tmHeight);
					}
					else
					{
						sizeText.cx = pDC->GetTextExtent(pCell->GetText()).cx;
						sizeText.cy = tmFont.tmHeight;
					}
					rCell[0].InflateRect(0, 0, sizeText.cx + rCell[2].left - rCell[1].left + rCell[1].right - rCell[2].right - rCell[1].Width(), sizeText.cy + rCell[2].top - rCell[1].top + rCell[1].bottom - rCell[2].bottom - rCell[1].Height());
					pDC->SelectObject(pOldFont);
					ReleaseDC(pDC);
					return rCell[0];
				}
				pDC->SelectObject(pOldFont);
			}
			break;
		}
		ReleaseDC(pDC);
	}
	return CRect(0, 0, 0, 0);
}

CRect CTableView::CalcTableCellPosition(CONST CTableViewCell *pCell)
{
	CDC  *pDC;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rCell[4];
	LOGFONT  lfFont;
	TEXTMETRIC  tmFont;
	CTableViewObject  *pTable;

	if ((pDC = GetDC()))
	{
		for (rCell[0] = rCell[1] = pCell->GetPosition(), rCell[2] = pCell->GetInnerPosition(), pCell->GetFont(&lfFont); cFont.CreateFontIndirect(&lfFont); )
		{
			if ((pTable = (pCell->GetFormat() & TAS_TYPE_SUBTABLE) ? m_pTables->GetAt(m_pTables->Find(pCell->GetSubTable())) : (CTableViewObject *)NULL) && pTable->IsVisible())
			{
				rCell[0].InflateRect(0, 0, pTable->Width() - rCell[2].Width(), pTable->Height() - rCell[2].Height());
				ReleaseDC(pDC);
				return rCell[0];
			}
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				if (pDC->GetTextMetrics(&tmFont) != 0)
				{
					pDC->DrawText(pCell->GetText(), (rCell[3] = rCell[2]), ((pCell->GetFormat() & TAS_ALIGN_LEFT) ? DT_LEFT : 0) | ((pCell->GetFormat() & TAS_ALIGN_RIGHT) ? DT_RIGHT : 0) | ((pCell->GetFormat() & TAS_ALIGN_HCENTER) ? DT_CENTER : 0) | ((pCell->GetFormat() & TAS_ALIGN_TOP) ? DT_TOP : 0) | ((pCell->GetFormat() & TAS_ALIGN_BOTTOM) ? (DT_SINGLELINE | DT_BOTTOM) : 0) | ((pCell->GetFormat() & TAS_ALIGN_VCENTER) ? (DT_SINGLELINE | DT_VCENTER) : 0) | DT_CALCRECT | DT_EXPANDTABS | DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_NOPREFIX);
					rCell[3].SetRect(rCell[1].left, rCell[1].top, rCell[1].right, rCell[1].bottom + rCell[3].Height() - rCell[2].Height());
					pDC->SelectObject(pOldFont);
					ReleaseDC(pDC);
					return rCell[3];
				}
				pDC->SelectObject(pOldFont);
			}
			break;
		}
		ReleaseDC(pDC);
	}
	return CRect(0, 0, 0, 0);
}

VOID CTableView::DrawTables()
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		pDC->SetViewportOrg(-GetScrollPosition());
		DrawTables(pDC);
		ReleaseDC(pDC);
	}
}
VOID CTableView::DrawTables(CDC *pDC)
{
	CDC  cDC;
	INT  nTable;
	INT  nTables;
	CRect  rView;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CTableViewObject  *pTable;

	for (GetClientRect(rView); cDC.CreateCompatibleDC(pDC); )
	{
		if (cBitmap.CreateCompatibleBitmap(pDC, rView.Width(), rView.Height()))
		{
			if ((pOldBitmap = (CBitmap *)cDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				for (nTable = 0, nTables = (INT)m_pTables->GetSize(), cDC.SetViewportOrg(-GetScrollPosition()), cDC.FillSolidRect(0, 0, max(GetTotalSize().cx, rView.Width()), max(GetTotalSize().cy, rView.Height()), GetSysColor(COLOR_WINDOW)); nTable < nTables; nTable++)
				{
					if ((pTable = m_pTables->GetAt(nTable)) && pTable->IsVisible())
					{
						DrawTable(&cDC, pTable);
						continue;
					}
				}
				pDC->BitBlt(GetScrollPosition().x, GetScrollPosition().y, rView.Width(), rView.Height(), &cDC, GetScrollPosition().x, GetScrollPosition().y, SRCCOPY);
				cDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cDC.DeleteDC();
		break;
	}
}

VOID CTableView::DrawTable(CDC *pDC, CTableViewObject *pTable)
{
	INT  nCol;
	INT  nRow;
	INT  nCols;
	INT  nRows;
	INT  nSel[2];
	INT  nBorderSize;
	INT  nBorderStyle;
	CPen  cBorderPen;
	CPen  *pOldPen;
	CRect  rView;
	CRect  rClip;
	LOGBRUSH  sPen;
	COLORREF  nBkgndColor;
	COLORREF  nBorderColor;
	CTableViewCell  *pCell;

	GetClientRect(rView);
	rView.OffsetRect(GetScrollPosition());
	if (rClip.IntersectRect(rView, pTable))
	{
		for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
		{
			for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
				{
					if (pCell->GetPosition().bottom >= rView.top  &&  pCell->GetPosition().top <= rView.bottom  &&  pCell->GetPosition().right >= rView.left  &&  pCell->GetPosition().left <= rView.right)
					{
						for (pCell->GetBorder(TAS_BORDER_LEFT, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL, pDC->FillSolidRect(pCell->GetPosition().left, pCell->GetPosition().top, 1, pCell->GetPosition().Height(), (nBkgndColor = (pCell != GetActiveCell() || (pCell->GetFormat() & TAS_TYPE_TEXT) || (pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_SPINBOX) || (pCell->GetFormat() & TAS_TYPE_TIMESPINBOX) || (pCell->GetFormat() & TAS_TYPE_SUBTABLE)) ? ((pCell != GetActiveCell() || (pCell->GetFormat() & TAS_TYPE_TEXT) || (pCell->GetFormat() & TAS_TYPE_SUBTABLE)) ? ((pTable->GetSelRow() == pCell->y || pTable->GetSelColumn() == pCell->x || (pTable->GetSelCell(nSel[0], nSel[1]) && pCell->x == nSel[1] && pCell->y == nSel[0])) ? pTable->GetSelColor() : pCell->GetBackgroundColor()) : GetSysColor(COLOR_WINDOW)) : GetSysColor(COLOR_3DFACE))), pDC->FillSolidRect(pCell->GetPosition().left, pCell->GetPosition().top, pCell->GetPosition().Width(), 1, nBkgndColor), pDC->FillSolidRect(pCell->GetPosition().right - 1, pCell->GetPosition().top, 1, pCell->GetPosition().Height(), nBkgndColor), pDC->FillSolidRect(pCell->GetPosition().left, pCell->GetPosition().bottom - 1, pCell->GetPosition().Width(), 1, nBkgndColor), pDC->FillSolidRect(((pCell->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE) ? pCell->GetPosition() : CRect(0, 0, 0, 0), nBkgndColor); cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
						{
							if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)) != (CPen *)NULL)
							{
								pDC->MoveTo(pCell->GetPosition().left, pCell->GetPosition().bottom);
								pDC->LineTo(pCell->GetPosition().left, pCell->GetPosition().top);
								pDC->SelectObject(pOldPen);
							}
							cBorderPen.DeleteObject();
							break;
						}
						for (pCell->GetBorder(TAS_BORDER_TOP, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL; cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
						{
							if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)) != (CPen *)NULL)
							{
								pDC->MoveTo(pCell->GetPosition().left, pCell->GetPosition().top);
								pDC->LineTo(pCell->GetPosition().right, pCell->GetPosition().top);
								pDC->SelectObject(pOldPen);
							}
							cBorderPen.DeleteObject();
							break;
						}
						for (pCell->GetBorder(TAS_BORDER_RIGHT, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL; cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
						{
							if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)) != (CPen *)NULL)
							{
								pDC->MoveTo(pCell->GetPosition().right, pCell->GetPosition().top);
								pDC->LineTo(pCell->GetPosition().right, pCell->GetPosition().bottom);
								pDC->SelectObject(pOldPen);
							}
							cBorderPen.DeleteObject();
							break;
						}
						for (pCell->GetBorder(TAS_BORDER_BOTTOM, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL; cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
						{
							if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)) != (CPen *)NULL)
							{
								pDC->MoveTo(pCell->GetPosition().left, pCell->GetPosition().bottom);
								pDC->LineTo(pCell->GetPosition().right, pCell->GetPosition().bottom);
								pDC->SelectObject(pOldPen);
							}
							cBorderPen.DeleteObject();
							break;
						}
						if (pCell != GetActiveCell()) pCell->Draw(pDC);
						continue;
					}
					if (pCell->GetPosition().top > rView.bottom) break;
				}
			}
			if (nCol < nCols) break;
		}
	}
}

VOID CTableView::DrawDragLine()
{
	DrawDragLine(m_ptDragCell[0]);
}
VOID CTableView::DrawDragLine(CONST POINT &point)
{
	CDC  *pDC;
	INT  nOldMode;
	CPen  cDragPen;
	CPen  *pOldPen;
	CRect  rCells;
	CPoint  ptOrigin;

	if (IsDraggingCells())
	{
		if ((pDC = GetDC()))
		{
			if (cDragPen.CreatePen(PS_DOT, 1, m_nDragColor))
			{
				if ((pOldPen = pDC->SelectObject(&cDragPen)))
				{
					for (ptOrigin = pDC->SetViewportOrg(-GetScrollPosition()), nOldMode = pDC->SetROP2(R2_XORPEN); IsHorzDraggingCells(); )
					{
						if ((rCells = m_pDragTable->GetCellsBounds()).right < point.x)
						{
							pDC->MoveTo(rCells.right, rCells.top);
							pDC->LineTo(point.x, rCells.top);
							pDC->MoveTo(rCells.right, rCells.bottom);
							pDC->LineTo(point.x, rCells.bottom);
						}
						if (point.x < rCells.left)
						{
							pDC->MoveTo(rCells.left, rCells.top);
							pDC->LineTo(point.x, rCells.top);
							pDC->MoveTo(rCells.left, rCells.bottom);
							pDC->LineTo(point.x, rCells.bottom);
						}
						pDC->MoveTo(point.x, rCells.top);
						pDC->LineTo(point.x, rCells.bottom);
						break;
					}
					if (IsVertDraggingCells())
					{
						if ((rCells = m_pDragTable->GetCellsBounds()).bottom < point.y)
						{
							pDC->MoveTo(rCells.left, rCells.bottom);
							pDC->LineTo(rCells.left, point.y);
							pDC->MoveTo(rCells.right, rCells.bottom);
							pDC->LineTo(rCells.right, point.y);
						}
						if (point.y < rCells.top)
						{
							pDC->MoveTo(rCells.left, rCells.top);
							pDC->LineTo(rCells.left, point.y);
							pDC->MoveTo(rCells.right, rCells.top);
							pDC->LineTo(rCells.right, point.y);
						}
						pDC->MoveTo(rCells.left, point.y);
						pDC->LineTo(rCells.right, point.y);
					}
					pDC->SetROP2(nOldMode);
					pDC->SelectObject(pOldPen);
					pDC->SetViewportOrg(ptOrigin);
				}
				cDragPen.DeleteObject();
			}
			ReleaseDC(pDC);
		}
	}
}

BOOL CTableView::IsDraggingCells() CONST
{
	return((m_pDragTable != (CTableViewObject *)NULL) ? TRUE : FALSE);
}

BOOL CTableView::IsHorzDraggingCells() CONST
{
	return((IsDraggingCells() && !m_ptDragCell[1].y  &&  !m_ptDragCell[2].y) ? TRUE : FALSE);
}

BOOL CTableView::IsVertDraggingCells() CONST
{
	return((IsDraggingCells() && !m_ptDragCell[1].x  &&  !m_ptDragCell[2].x) ? TRUE : FALSE);
}

LRESULT CTableView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	if (message == WM_COMMAND)
	{
		if (HIWORD(wParam) == EN_KILLFOCUS) SetActiveCell();
		if (HIWORD(wParam) == CBN_KILLFOCUS) SetActiveCell();
	}
	lResult = CScrollView::WindowProc(message, wParam, lParam);
	return lResult;
}

void CTableView::PostNcDestroy()
{
	return;
}

BEGIN_MESSAGE_MAP(CTableView, CScrollView)
	//{{AFX_MSG_MAP(CTableView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_GETDLGCODE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableView drawing

void CTableView::OnDraw(CDC *pDC)
{
	DrawTables(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTableView message handlers

int CTableView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) != -1)
	{
		SetScrollSizes(MM_TEXT, CSize(0, 0));
		return 0;
	}
	return -1;
}

BOOL CTableView::OnEraseBkgnd(CDC *pDC)
{
	UpdateWindow();
	return TRUE;
}

UINT CTableView::OnGetDlgCode()
{
	return DLGC_WANTALLKEYS;
}

BOOL CTableView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  dx[2];
	INT  dy[2];
	INT  nTable;
	INT  nTables;
	CRect  rCell;
	CPoint  ptCursor;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (pWnd == this && nHitTest == HTCLIENT) ? (INT)m_pTables->GetSize() : 0, ptCursor = GetCurrentMessage()->pt, ScreenToClient(&ptCursor), ptCursor += GetScrollPosition(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->IsVisible() && pTable->IsResizeEnabled() && pTable->PtInRect(ptCursor))
		{
			if ((pCell = pTable->FindCell(ptCursor)))
			{
				rCell = pCell->GetPosition();
				dx[0] = abs(rCell.left - ptCursor.x);
				dx[1] = abs(rCell.right - ptCursor.x);
				dy[0] = abs(rCell.top - ptCursor.y);
				dy[1] = abs(rCell.bottom - ptCursor.y);
				if (dx[0] <= 2 * GetSystemMetrics(SM_CXBORDER) || dx[1] <= 2 * GetSystemMetrics(SM_CXBORDER))
				{
					SetCursor(LoadCursor(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDC_TABLEVIEWSPLITHORIZONTAL)));
					return TRUE;
				}
				if (dy[0] <= 2 * GetSystemMetrics(SM_CYBORDER) || dy[1] <= 2 * GetSystemMetrics(SM_CYBORDER))
				{
					SetCursor(LoadCursor(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDC_TABLEVIEWSPLITVERTICAL)));
					return TRUE;
				}
			}
		}
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CTableView::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint  ptCursor;

	if (IsDraggingCells())
	{
		for (DrawDragLine(m_ptDragCell[0]); IsHorzDraggingCells(); )
		{
			m_ptDragCell[0].x = max(m_ptDragCell[1].x + 1, (ptCursor = point + GetScrollPosition()).x);
			m_ptDragCell[0].x = (m_ptDragCell[2].x >= 0) ? min(m_ptDragCell[2].x - 1, m_ptDragCell[0].x) : m_ptDragCell[0].x;
			break;
		}
		if (IsVertDraggingCells())
		{
			m_ptDragCell[0].y = max(m_ptDragCell[1].y + 1, (ptCursor = point + GetScrollPosition()).y);
			m_ptDragCell[0].y = (m_ptDragCell[2].y >= 0) ? min(m_ptDragCell[2].y - 1, m_ptDragCell[0].y) : m_ptDragCell[0].y;
		}
		DrawDragLine(m_ptDragCell[0]);
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CTableView::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  dx[2];
	INT  dy[2];
	INT  nSize;
	INT  nStyle;
	INT  nTable;
	INT  nTables;
	CRect  rCell;
	CPoint  ptCursor;
	COLORREF  nColor;
	CTableViewCell  *pCell[2];
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), ptCursor = point + GetScrollPosition(), SetActiveCell(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->IsVisible() && pTable->IsResizeEnabled() && pTable->PtInRect(ptCursor))
		{
			if ((pCell[0] = pTable->FindCell(ptCursor)))
			{
				rCell = pCell[0]->GetPosition();
				dx[0] = abs(rCell.left - ptCursor.x);
				dx[1] = abs(rCell.right - ptCursor.x);
				dy[0] = abs(rCell.top - ptCursor.y);
				dy[1] = abs(rCell.bottom - ptCursor.y);
				if (abs(pTable->left - ptCursor.x) <= GetSystemMetrics(SM_CXFRAME))
				{
					if ((pCell[0] = pTable->FindCell(0, 0)) && pCell[0]->GetBorder(TAS_BORDER_LEFT, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].x = pCell[0]->GetPosition().left;
						m_ptDragCell[2].x = pCell[0]->GetPosition().right;
						m_ptDragCell[1].x = ((pCell[1] = pTable->FindCell(pCell[0]->y, pCell[0]->x - 1))) ? pCell[1]->GetPosition().left : (m_ptDragCell[0].x - 1);
						m_ptDragCell[0].y = m_ptDragCell[1].y = m_ptDragCell[2].y = 0;
						m_nDragColor = nColor;
						break;
					}
				}
				if (abs(pTable->top - ptCursor.y) <= GetSystemMetrics(SM_CYFRAME))
				{
					if ((pCell[0] = pTable->FindCell(0, 0)) && pCell[0]->GetBorder(TAS_BORDER_TOP, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].y = pCell[0]->GetPosition().top;
						m_ptDragCell[2].y = pCell[0]->GetPosition().bottom;
						m_ptDragCell[1].y = ((pCell[1] = pTable->FindCell(pCell[0]->y - 1, pCell[0]->x))) ? pCell[1]->GetPosition().top : (m_ptDragCell[0].y - 1);
						m_ptDragCell[0].x = m_ptDragCell[1].x = m_ptDragCell[2].x = 0;
						m_nDragColor = nColor;
						break;
					}
				}
				if (abs(pTable->right - ptCursor.x) <= GetSystemMetrics(SM_CXFRAME))
				{
					if ((pCell[0] = pTable->FindCell(pTable->GetRows() - 1, pTable->GetColumns() - 1)) && pCell[0]->GetBorder(TAS_BORDER_RIGHT, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].x = pCell[0]->GetPosition().right;
						m_ptDragCell[1].x = pCell[0]->GetPosition().left;
						m_ptDragCell[2].x = ((pCell[1] = pTable->FindCell(pCell[0]->y, pCell[0]->x + 1))) ? pCell[1]->GetPosition().right : -1;
						m_ptDragCell[0].y = m_ptDragCell[1].y = m_ptDragCell[2].y = 0;
						m_nDragColor = nColor;
						break;
					}
				}
				if (abs(pTable->bottom - ptCursor.y) <= GetSystemMetrics(SM_CYFRAME))
				{
					if ((pCell[0] = pTable->FindCell(pTable->GetRows() - 1, pTable->GetColumns() - 1)) && pCell[0]->GetBorder(TAS_BORDER_BOTTOM, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].y = pCell[0]->GetPosition().bottom;
						m_ptDragCell[1].y = pCell[0]->GetPosition().top;
						m_ptDragCell[2].y = ((pCell[1] = pTable->FindCell(pCell[0]->y + 1, pCell[0]->x))) ? pCell[1]->GetPosition().bottom : -1;
						m_ptDragCell[0].x = m_ptDragCell[1].x = m_ptDragCell[2].x = 0;
						m_nDragColor = nColor;
						break;
					}
				}
				if (dx[0] <= 2 * GetSystemMetrics(SM_CXBORDER))
				{
					if (pCell[0]->GetBorder(TAS_BORDER_LEFT, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].x = pCell[0]->GetPosition().left;
						m_ptDragCell[2].x = pCell[0]->GetPosition().right;
						m_ptDragCell[1].x = ((pCell[1] = pTable->FindCell(pCell[0]->y, pCell[0]->x - 1))) ? pCell[1]->GetPosition().left : (m_ptDragCell[0].x - 1);
						m_ptDragCell[0].y = m_ptDragCell[1].y = m_ptDragCell[2].y = 0;
						m_nDragColor = nColor;
						break;
					}
				}
				if (dy[0] <= 2 * GetSystemMetrics(SM_CYBORDER))
				{
					if (pCell[0]->GetBorder(TAS_BORDER_TOP, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].y = pCell[0]->GetPosition().top;
						m_ptDragCell[2].y = pCell[0]->GetPosition().bottom;
						m_ptDragCell[1].y = ((pCell[1] = pTable->FindCell(pCell[0]->y - 1, pCell[0]->x))) ? pCell[1]->GetPosition().top : (m_ptDragCell[0].y - 1);
						m_ptDragCell[0].x = m_ptDragCell[1].x = m_ptDragCell[2].x = 0;
						m_nDragColor = nColor;
						break;
					}
				}
				if (dx[1] <= 2 * GetSystemMetrics(SM_CXBORDER))
				{
					if (pCell[0]->GetBorder(TAS_BORDER_RIGHT, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].x = pCell[0]->GetPosition().right;
						m_ptDragCell[1].x = pCell[0]->GetPosition().left;
						m_ptDragCell[2].x = ((pCell[1] = pTable->FindCell(pCell[0]->y, pCell[0]->x + 1))) ? pCell[1]->GetPosition().right : -1;
						m_ptDragCell[0].y = m_ptDragCell[1].y = m_ptDragCell[2].y = 0;
						m_nDragColor = nColor;
						break;
					}
				}
				if (dy[1] <= 2 * GetSystemMetrics(SM_CYBORDER))
				{
					if (pCell[0]->GetBorder(TAS_BORDER_BOTTOM, nSize, nStyle, nColor))
					{
						m_pDragTable = pTable;
						m_nDragCell.x = pCell[0]->x;
						m_nDragCell.y = pCell[0]->y;
						m_ptDragCell[0].y = pCell[0]->GetPosition().bottom;
						m_ptDragCell[1].y = pCell[0]->GetPosition().top;
						m_ptDragCell[2].y = ((pCell[1] = pTable->FindCell(pCell[0]->y + 1, pCell[0]->x))) ? pCell[1]->GetPosition().bottom : -1;
						m_ptDragCell[0].x = m_ptDragCell[1].x = m_ptDragCell[2].x = 0;
						m_nDragColor = nColor;
						break;
					}
				}
			}
		}
	}
	if (IsDraggingCells())
	{
		SetActiveCell();
		DrawDragLine();
		SetCapture();
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CTableView::OnLButtonUp(UINT nFlags, CPoint point)
{
	INT  nRow;
	INT  nRows;
	CRect  rTable;
	CRect  rCell[2];
	CTableViewCell  *pCell[2];

	if (IsDraggingCells())
	{
		if (IsHorzDraggingCells())
		{
			for (; (pCell[0] = m_pDragTable->FindCell(m_nDragCell.y, m_nDragCell.x)); )
			{
				if (pCell[0]->GetPosition().right == m_ptDragCell[2].x  &&  pCell[0]->x > 0)
				{
					if ((pCell[1] = m_pDragTable->FindCell(m_nDragCell.y, m_nDragCell.x - 1)) != (CTableViewCell *)NULL)
					{
						m_pDragTable->SetColumnWidth(pCell[0]->x - 1, (rCell[1] = pCell[1]->GetPosition()).Width() - (rCell[0] = pCell[0]->GetPosition()).left + m_ptDragCell[0].x);
						m_pDragTable->SetColumnWidth(pCell[0]->x, rCell[0].Width() + rCell[0].left - m_ptDragCell[0].x);
					}
					break;
				}
				if (pCell[0]->GetPosition().right == m_ptDragCell[2].x)
				{
					m_pDragTable->OffsetCells(m_ptDragCell[0].x - (rCell[0] = pCell[0]->GetPosition()).left, 0);
					m_pDragTable->SetColumnWidth(pCell[0]->x, rCell[0].Width() + rCell[0].left - m_ptDragCell[0].x);
					m_pDragTable->SetRect(max(m_pDragTable->left + m_ptDragCell[0].x - rCell[0].left, 0), m_pDragTable->top, m_pDragTable->right, m_pDragTable->bottom);
					break;
				}
				if ((pCell[0]->GetPosition().right < m_ptDragCell[2].x || m_ptDragCell[2].x < 0) && pCell[0]->x < m_pDragTable->GetColumns() - 1)
				{
					if ((pCell[1] = m_pDragTable->FindCell(m_nDragCell.y, m_nDragCell.x + 1)) != (CTableViewCell *)NULL)
					{
						m_pDragTable->SetColumnWidth(pCell[0]->x, (rCell[0] = pCell[0]->GetPosition()).Width() + m_ptDragCell[0].x - pCell[0]->GetPosition().right);
						m_pDragTable->SetColumnWidth(pCell[0]->x + 1, pCell[1]->GetPosition().Width() - m_ptDragCell[0].x + rCell[0].right);
					}
					break;
				}
				if (pCell[0]->GetPosition().right < m_ptDragCell[2].x || m_ptDragCell[2].x < 0)
				{
					m_pDragTable->SetColumnWidth(pCell[0]->x, (rCell[0] = pCell[0]->GetPosition()).Width() + m_ptDragCell[0].x - pCell[0]->GetPosition().right);
					m_pDragTable->SetRect(m_pDragTable->left, m_pDragTable->top, m_pDragTable->right + m_ptDragCell[0].x - rCell[0].right, m_pDragTable->bottom);
					break;
				}
			}
			for (nRow = 0, nRows = m_pDragTable->GetRows(), rTable = m_pDragTable->GetCellsBounds(); nRow < nRows; nRow++)
			{
				RecalcTableRow(m_pDragTable, nRow);
				continue;
			}
			m_pDragTable->SetRect(m_pDragTable->left, m_pDragTable->top, m_pDragTable->right, m_pDragTable->bottom + m_pDragTable->GetCellsBounds().Height() - rTable.Height());
			RepositionTables();
			RecalcScrollSizes();
			DrawTables();
		}
		if (IsVertDraggingCells())
		{
			for (; (pCell[0] = m_pDragTable->FindCell(m_nDragCell.y, m_nDragCell.x)); )
			{
				if (pCell[0]->GetPosition().bottom == m_ptDragCell[2].y  &&  pCell[0]->y > 0)
				{
					if ((pCell[1] = m_pDragTable->FindCell(m_nDragCell.y - 1, m_nDragCell.x)) != (CTableViewCell *)NULL)
					{
						m_pDragTable->SetRowHeight(pCell[0]->y - 1, (rCell[1] = pCell[1]->GetPosition()).Height() - (rCell[0] = pCell[0]->GetPosition()).top + m_ptDragCell[0].y);
						m_pDragTable->SetRowHeight(pCell[0]->y, rCell[0].Height() + rCell[0].top - m_ptDragCell[0].y);
						RepositionTables();
					}
					break;
				}
				if (pCell[0]->GetPosition().bottom == m_ptDragCell[2].y)
				{
					m_pDragTable->OffsetCells(0, m_ptDragCell[0].y - (rCell[0] = pCell[0]->GetPosition()).top);
					m_pDragTable->SetRowHeight(pCell[0]->y, rCell[0].Height() + rCell[0].top - m_ptDragCell[0].y);
					m_pDragTable->SetRect(m_pDragTable->left, max(m_pDragTable->top + m_ptDragCell[0].y - rCell[0].top, 0), m_pDragTable->right, m_pDragTable->bottom);
					RepositionTables();
					RecalcScrollSizes();
					break;
				}
				if ((pCell[0]->GetPosition().bottom < m_ptDragCell[2].y || m_ptDragCell[2].y < 0) && pCell[0]->y < m_pDragTable->GetRows() - 1)
				{
					if ((pCell[1] = m_pDragTable->FindCell(m_nDragCell.y + 1, m_nDragCell.x)) != (CTableViewCell *)NULL)
					{
						m_pDragTable->SetRowHeight(pCell[0]->y, (rCell[0] = pCell[0]->GetPosition()).Height() + m_ptDragCell[0].y - pCell[0]->GetPosition().bottom);
						m_pDragTable->SetRowHeight(pCell[0]->y + 1, pCell[1]->GetPosition().Height() - m_ptDragCell[0].y + rCell[0].bottom);
						RepositionTables();
					}
					break;
				}
				if (pCell[0]->GetPosition().bottom < m_ptDragCell[2].y || m_ptDragCell[2].y < 0)
				{
					m_pDragTable->SetRowHeight(pCell[0]->y, (rCell[0] = pCell[0]->GetPosition()).Height() + m_ptDragCell[0].y - pCell[0]->GetPosition().bottom);
					m_pDragTable->SetRect(m_pDragTable->left, m_pDragTable->top, m_pDragTable->right, m_pDragTable->bottom + m_ptDragCell[0].y - rCell[0].bottom);
					RepositionTables();
					RecalcScrollSizes();
					break;
				}
			}
			DrawTables();
		}
		m_pDragTable = (CTableViewObject *)NULL;
		ReleaseCapture();
	}
	CScrollView::OnLButtonUp(nFlags, point);
}

void CTableView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	INT  nTable;
	INT  nTables;
	CPoint  ptCursor;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), ptCursor = point + GetScrollPosition(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->IsVisible() && pTable->PtInRect(ptCursor))
		{
			if ((pCell = pTable->FindCell(ptCursor)))
			{
				if (SetActiveCell(pTable, pCell)) break;
				continue;
			}
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CTableView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	BOOL  bShift;
	CTableViewObject  *pTable[2];

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), nRow = nCol = -1; nTable < nTables; nTable++)
	{
		if ((pTable[0] = m_pTables->GetAt(nTable)) && pTable[0]->IsVisible())
		{
			if ((nRow = pTable[0]->GetSelRow()) >= 0)
			{
				if (nChar == VK_DOWN)
				{
					if (nRow < pTable[0]->GetRows() - 1)
					{
						pTable[0]->SetSelRow(nRow + 1);
						ScrollToTableRow(pTable[0], nRow + 1);
					}
					return;
				}
				if (nChar == VK_UP)
				{
					if ((!pTable[0]->HasTitle() && nRow > 0) || (pTable[0]->HasTitle() && nRow > 1))
					{
						pTable[0]->SetSelRow(nRow - 1);
						ScrollToTableRow(pTable[0], nRow - 1);
					}
					return;
				}
				for (; nChar == VK_NEXT; )
				{
					ScrollTableRows(pTable[0], TRUE);
					break;
				}
				if (nChar == VK_PRIOR)
				{
					ScrollTableRows(pTable[0], FALSE);
					break;
				}
				if (nChar == VK_END)
				{
					if ((!pTable[0]->HasTitle() && pTable[0]->GetRows() > 0) || (pTable[0]->HasTitle() && pTable[0]->GetRows() > 1))
					{
						pTable[0]->SetSelRow(pTable[0]->GetRows() - 1);
						ScrollToTableRow(pTable[0], pTable[0]->GetSelRow());
					}
					return;
				}
				if (nChar == VK_TAB)
				{
					for (bShift = HIBYTE(GetKeyState(VK_SHIFT)); (pTable[1] = m_pTables->GetAt((!bShift) ? ((nTable + 1) % nTables) : ((nTable + nTables - 1) % nTables))); )
					{
						if (pTable[1]->GetType() == TAS_TABLE_NORMAL)
						{
							ActivateTable(pTable[1]);
							return;
						}
						if (pTable[1]->GetType() == TAS_TABLE_LIST)
						{
							pTable[1]->SetSelRow((bShift) ? (pTable[1]->GetRows() - 1) : pTable[1]->HasTitle());
							ScrollToTableRow(pTable[1], pTable[1]->GetSelRow());
							return;
						}
						break;
					}
				}
			}
			if ((nCol = pTable[0]->GetSelColumn()) >= 0)
			{
				if (nChar == VK_RIGHT)
				{
					if (nCol < pTable[0]->GetColumns() - 1)
					{
						pTable[0]->SetSelColumn(nCol + 1);
						ScrollToTableColumn(pTable[0], nCol + 1);
					}
					return;
				}
				if (nChar == VK_LEFT)
				{
					if (nCol > 0)
					{
						pTable[0]->SetSelColumn(nCol - 1);
						ScrollToTableColumn(pTable[0], nCol - 1);
					}
					return;
				}
				if (nChar == VK_END)
				{
					if (pTable[0]->GetColumns() > 0)
					{
						pTable[0]->SetSelColumn(pTable[0]->GetColumns() - 1);
						ScrollToTableColumn(pTable[0], pTable[0]->GetSelColumn());
					}
					return;
				}
				if (nChar == VK_TAB)
				{
					for (bShift = HIBYTE(GetKeyState(VK_SHIFT)); (pTable[1] = m_pTables->GetAt((!bShift) ? ((nTable + 1) % nTables) : ((nTable + nTables - 1) % nTables))); )
					{
						if (pTable[1]->GetType() == TAS_TABLE_NORMAL)
						{
							ActivateTable(pTable[1]);
							return;
						}
						if (pTable[1]->GetType() == TAS_TABLE_LIST)
						{
							pTable[1]->SetSelColumn((bShift) ? (pTable[1]->GetColumns() - 1) : 0);
							ScrollToTableColumn(pTable[1], pTable[1]->GetSelColumn());
							return;
						}
						break;
					}
				}
			}
		}
	}
	if (nChar == VK_DOWN) ActivateTable();
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTableView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	CRect  rView;
	SCROLLINFO  sScrollInfo[2];

	for (GetClientRect(rView), GetScrollInfo(SB_HORZ, &sScrollInfo[0]), GetScrollInfo(SB_VERT, &sScrollInfo[1]); nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK; )
	{
		ScrollToPosition(CPoint((nSBCode == SB_THUMBTRACK) ? sScrollInfo[0].nTrackPos : sScrollInfo[0].nPos, sScrollInfo[1].nPos));
		return;
	}
	if (nSBCode == SB_PAGELEFT || nSBCode == SB_PAGERIGHT)
	{
		ScrollToPosition(CPoint((nSBCode == SB_PAGELEFT) ? max(sScrollInfo[0].nPos - rView.Width(), 0) : min(sScrollInfo[0].nPos + rView.Width(), sScrollInfo[0].nMax), sScrollInfo[1].nPos));
		return;
	}
	if (nSBCode == SB_LINELEFT || nSBCode == SB_LINERIGHT)
	{
		ScrollToPosition(CPoint((nSBCode == SB_LINELEFT) ? max(sScrollInfo[0].nPos - rView.Width() / 16, 0) : min(sScrollInfo[0].nPos + rView.Width() / 16, sScrollInfo[0].nMax), sScrollInfo[1].nPos));
		return;
	}
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTableView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	CRect  rView;
	SCROLLINFO  sScrollInfo[2];

	for (GetClientRect(rView), GetScrollInfo(SB_HORZ, &sScrollInfo[0]), GetScrollInfo(SB_VERT, &sScrollInfo[1]); nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK; )
	{
		ScrollToPosition(CPoint(sScrollInfo[0].nPos, (nSBCode == SB_THUMBTRACK) ? sScrollInfo[1].nTrackPos : sScrollInfo[1].nPos));
		return;
	}
	if (nSBCode == SB_PAGEUP || nSBCode == SB_PAGEDOWN)
	{
		ScrollToPosition(CPoint(sScrollInfo[0].nPos, (nSBCode == SB_PAGEUP) ? max(sScrollInfo[1].nPos - rView.Height(), 0) : min(sScrollInfo[1].nPos + rView.Height(), sScrollInfo[1].nMax)));
		return;
	}
	if (nSBCode == SB_LINEUP || nSBCode == SB_LINEDOWN)
	{
		ScrollToPosition(CPoint(sScrollInfo[0].nPos, (nSBCode == SB_LINEUP) ? max(sScrollInfo[1].nPos - rView.Height() / 16, 0) : min(sScrollInfo[1].nPos + rView.Height() / 16, sScrollInfo[1].nMax)));
		return;
	}
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CTableView::OnDestroy()
{
	m_pTables->RemoveAll();
	CScrollView::OnDestroy();
}
