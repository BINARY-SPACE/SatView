// DISPLAYS.CPP : Displays Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the displays related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDisplayDialog dialog

IMPLEMENT_DYNCREATE(CDisplayDialog, CLocaleDialog)

CDisplayDialog::CDisplayDialog() : CLocaleDialog()
{
	//{{AFX_DATA_INIT(CDisplayDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CDisplayDialog::Create(CWnd *pParentWnd, UINT nID, BOOL bModal)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd, m_bModal = bModal; (pDialogTemplate = (!m_hDialogTemplate) ? LoadLocaleDialogTemplate(MAKEINTRESOURCE(nID)) : (LPVOID)NULL); )
	{
		if (!bModal) return((INT)CreateIndirect(pDialogTemplate, pParentWnd));
		InitModalIndirect(pDialogTemplate);
		break;
	}
	return((INT)DoModal());
}

CDisplayWnd *CDisplayDialog::GetParentDisplay() CONST
{
	CWnd  *pWnd;
	CDisplayWnd  *pDisplayWnd;
	CDisplayDialog  *pDisplayDialog;
	CDisplayPropertySheetDialog  *pDisplayPropertySheetDialog;

	for (pWnd = GetParent(), pDisplayWnd = (CDisplayWnd *)NULL; IsWindow(pWnd->GetSafeHwnd()); )
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayDialog)))
		{
			if ((pDisplayDialog = (CDisplayDialog *)pWnd))
			{
				pWnd = pDisplayDialog->GetParent();
				continue;
			}
			break;
		}
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayPropertySheetDialog)))
		{
			if ((pDisplayPropertySheetDialog = (CDisplayPropertySheetDialog *)pWnd))
			{
				pWnd = pDisplayPropertySheetDialog->GetParent();
				continue;
			}
			break;
		}
		if (!pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
		{
			pWnd = pWnd->GetParent();
			continue;
		}
		pDisplayWnd = (CDisplayWnd *)pWnd;
		break;
	}
	return pDisplayWnd;
}

void CDisplayDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDisplayDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDisplayDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayDialog message handlers

BOOL CDisplayDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); (pDisplayWnd = GetParentDisplay())->GetSafeHwnd() == GetParent()->GetSafeHwnd() || rDialog[0].Width() <= rDialog[1].Width() || rDialog[0].Height() <= rDialog[1].Height(); )
	{
		MoveWindow(rDialog[0].left + 5 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	return TRUE;
}

void CDisplayDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDOK);
}

void CDisplayDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDCANCEL);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayPropertySheetDialog

IMPLEMENT_DYNCREATE(CDisplayPropertySheetDialog, CLocalePropertySheetDialog)

CDisplayPropertySheetDialog::CDisplayPropertySheetDialog() : CLocalePropertySheetDialog()
{
	//{{AFX_DATA_INIT(CDisplayPropertySheetDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CDisplayPropertySheetDialog::CDisplayPropertySheetDialog(LPCTSTR pszTitle) : CLocalePropertySheetDialog(pszTitle)
{
	//{{AFX_DATA_INIT(CDisplayPropertySheetDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CDisplayPropertySheetDialog::Create(CWnd *pParentWnd, BOOL bModal)
{
	Construct(EMPTYSTRING, pParentWnd);
	return(((m_bModal = bModal)) ? (INT)DoModal() : (INT)CLocalePropertySheetDialog::Create(pParentWnd));
}

CDisplayWnd *CDisplayPropertySheetDialog::GetParentDisplay() CONST
{
	CWnd  *pWnd;
	CDisplayWnd  *pDisplayWnd;
	CDisplayDialog  *pDisplayDialog;
	CDisplayPropertySheetDialog  *pDisplayPropertySheetDialog;

	for (pWnd = GetParent(), pDisplayWnd = (CDisplayWnd *)NULL; IsWindow(pWnd->GetSafeHwnd()); )
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayDialog)))
		{
			if ((pDisplayDialog = (CDisplayDialog *)pWnd))
			{
				pWnd = pDisplayDialog->GetParent();
				continue;
			}
			break;
		}
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayPropertySheetDialog)))
		{
			if ((pDisplayPropertySheetDialog = (CDisplayPropertySheetDialog *)pWnd))
			{
				pWnd = pDisplayPropertySheetDialog->GetParent();
				continue;
			}
			break;
		}
		if (!pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
		{
			pWnd = pWnd->GetParent();
			continue;
		}
		pDisplayWnd = (CDisplayWnd *)pWnd;
		break;
	}
	return pDisplayWnd;
}

BEGIN_MESSAGE_MAP(CDisplayPropertySheetDialog, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CDisplayPropertySheetDialog)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayPropertySheetDialog message handlers

BOOL CDisplayPropertySheetDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	CLocalePropertySheetDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); (pDisplayWnd = GetParentDisplay())->GetSafeHwnd() == GetParent()->GetSafeHwnd() || rDialog[0].Width() <= rDialog[1].Width() || rDialog[0].Height() <= rDialog[1].Height(); )
	{
		MoveWindow(rDialog[0].left + 5 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	return TRUE;
}

void CDisplayPropertySheetDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDOK);
}

void CDisplayPropertySheetDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDCANCEL);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayTableViewUndoItem

CDisplayTableViewUndoItem::CDisplayTableViewUndoItem() : CObject()
{
	Clear();
}

VOID CDisplayTableViewUndoItem::SetInfo(LPCTSTR pszTable, CONST POINT &ptCell, INT nAlignment, LPCTSTR pszText, LPCTSTR pszInitialText, INT nStartPos, INT nEndPos)
{
	m_szTable = pszTable;
	m_szText[0] = pszText;
	m_szText[1] = pszInitialText;
	m_nAlignment = nAlignment;
	m_nSel[0] = nStartPos;
	m_nSel[1] = nEndPos;
	m_ptCell = ptCell;
}

VOID CDisplayTableViewUndoItem::GetInfo(CString &szTable, CPoint &ptCell, INT &nAlignment, CString &szText, CString &szInitialText, INT &nStartPos, INT &nEndPos) CONST
{
	szTable = m_szTable;
	szText = m_szText[0];
	szInitialText = m_szText[1];
	nAlignment = m_nAlignment;
	nStartPos = m_nSel[0];
	nEndPos = m_nSel[1];
	ptCell = m_ptCell;
}

VOID CDisplayTableViewUndoItem::SetCell(LPCTSTR pszTable, CONST POINT &ptCell)
{
	m_szTable = pszTable;
	m_ptCell = ptCell;
}

BOOL CDisplayTableViewUndoItem::GetCell(CString &szTable, CPoint &ptCell) CONST
{
	ptCell = m_ptCell;
	szTable = m_szTable;
	return !szTable.IsEmpty();
}

VOID CDisplayTableViewUndoItem::SetContext(LPCTSTR pszContext)
{
	m_szContext = pszContext;
}

CString CDisplayTableViewUndoItem::GetContext() CONST
{
	return m_szContext;
}

VOID CDisplayTableViewUndoItem::SetText(LPCTSTR pszText)
{
	m_szText[0] = pszText;
}

CString CDisplayTableViewUndoItem::GetText() CONST
{
	return m_szText[0];
}

VOID CDisplayTableViewUndoItem::SetInitialText(LPCTSTR pszText)
{
	m_szText[1] = pszText;
}

CString CDisplayTableViewUndoItem::GetInitialText() CONST
{
	return m_szText[1];
}

VOID CDisplayTableViewUndoItem::SetSel(INT nStartPos, INT nEndPos)
{
	m_nSel[0] = nStartPos;
	m_nSel[1] = nEndPos;
}

VOID CDisplayTableViewUndoItem::GetSel(INT &nStartPos, INT &nEndPos) CONST
{
	nStartPos = m_nSel[0];
	nEndPos = m_nSel[1];
}

VOID CDisplayTableViewUndoItem::SetAlignment(INT nAlignment)
{
	m_nAlignment = nAlignment;
}

INT CDisplayTableViewUndoItem::GetAlignment() CONST
{
	return m_nAlignment;
}

VOID CDisplayTableViewUndoItem::AllowUpdates(BOOL bEnable)
{
	m_bUpdates = bEnable;
}

BOOL CDisplayTableViewUndoItem::CanUpdate() CONST
{
	return m_bUpdates;
}

VOID CDisplayTableViewUndoItem::AllowActivation(BOOL bEnable)
{
	m_bActivation = bEnable;
}

BOOL CDisplayTableViewUndoItem::CanActivate() CONST
{
	return m_bActivation;
}

VOID CDisplayTableViewUndoItem::AllowSelection(BOOL bEnable)
{
	m_bSelection = bEnable;
}

BOOL CDisplayTableViewUndoItem::CanSelect() CONST
{
	return m_bSelection;
}

VOID CDisplayTableViewUndoItem::Collect(BOOL bEnable)
{
	m_bCollected = bEnable;
}

BOOL CDisplayTableViewUndoItem::IsCollected() CONST
{
	return m_bCollected;
}

VOID CDisplayTableViewUndoItem::Clear()
{
	m_szTable.Empty();
	m_szContext.Empty();
	m_szText[0].Empty();
	m_szText[1].Empty();
	m_nAlignment = -1;
	m_ptCell.x = -1;
	m_ptCell.y = -1;
	m_nSel[0] = -1;
	m_nSel[1] = -1;
	m_bUpdates = FALSE;
	m_bActivation = FALSE;
	m_bSelection = TRUE;
	m_bCollected = FALSE;
}

VOID CDisplayTableViewUndoItem::Copy(CONST CDisplayTableViewUndoItem *pItem)
{
	m_szTable = pItem->m_szTable;
	m_szContext = pItem->m_szContext;
	m_szText[0] = pItem->m_szText[0];
	m_szText[1] = pItem->m_szText[1];
	m_nAlignment = pItem->m_nAlignment;
	m_nSel[0] = pItem->m_nSel[0];
	m_nSel[1] = pItem->m_nSel[1];
	m_ptCell = pItem->m_ptCell;
	m_bUpdates = pItem->m_bUpdates;
	m_bActivation = pItem->m_bActivation;
	m_bSelection = pItem->m_bSelection;
	m_bCollected = pItem->m_bCollected;
}

BOOL CDisplayTableViewUndoItem::Compare(CONST CDisplayTableViewUndoItem *pItem) CONST
{
	return((pItem->m_szTable == m_szTable  &&  pItem->m_szContext == m_szContext  &&  pItem->m_szText[0] == m_szText[0] && pItem->m_szText[1] == m_szText[1] && pItem->m_nAlignment == m_nAlignment  &&  pItem->m_ptCell == m_ptCell  &&  pItem->m_nSel[0] == m_nSel[0] && pItem->m_nSel[1] == m_nSel[1] && pItem->m_bUpdates == m_bUpdates  &&  pItem->m_bActivation == m_bActivation  &&  pItem->m_bSelection == m_bSelection  &&  pItem->m_bCollected == m_bCollected) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayTableViewUndoList

CDisplayTableViewUndoList::CDisplayTableViewUndoList() : CPtrArray()
{
	m_nIndex = -1;
	m_nCount = -1;
	m_bUndoing = FALSE;
	m_bCollecting = FALSE;
	m_nLocks = 0;
}

CDisplayTableViewUndoList::~CDisplayTableViewUndoList()
{
	Reset();
}

BOOL CDisplayTableViewUndoList::Add(CONST CDisplayTableViewUndoItem *pItem, BOOL bUpdates)
{
	INT  nItem;
	INT  nItems;
	CPoint  ptCell[2];
	CString  szTable[2];
	CDisplayTableViewUndoItem  *pUndoItem[2];

	if (!IsLocked())
	{
		if (((pUndoItem[0] = GetAt(m_nIndex)) && (!pUndoItem[0]->Compare(pItem) || !pItem->GetCell(szTable[0], ptCell[0]) || (ptCell[0].x == -1 || ptCell[0].y == -1))) || m_nIndex < 0)
		{
			for (nItem = (m_nIndex >= 0) ? ((!m_bUndoing) ? (m_nIndex + 1) : m_nIndex) : (m_nIndex + 1), nItems = (INT)GetSize(); nItem < nItems; nItem++)
			{
				delete GetAt(nItem);
				RemoveAt(nItem);
				nItems--;
				nItem--;
			}
			if ((pUndoItem[0] = new CDisplayTableViewUndoItem))
			{
				for (pUndoItem[0]->Copy(pItem), pUndoItem[0]->Collect(pUndoItem[0]->IsCollected() || m_bCollecting); CPtrArray::Add(pUndoItem[0]) >= 0; )
				{
					if ((pUndoItem[1] = (bUpdates) ? GetAt((INT)(GetUpperBound() - 1)) : (CDisplayTableViewUndoItem *)NULL) && pUndoItem[0]->GetCell(szTable[0], ptCell[0]) && pUndoItem[1]->GetCell(szTable[1], ptCell[1]) && szTable[0] == szTable[1] && ptCell[0].x == ptCell[1].x  &&  ptCell[0].y == ptCell[1].y) pUndoItem[1]->AllowUpdates();
					for (m_nIndex = (INT)GetUpperBound(); m_nCount > 0; )
					{
						m_bCollecting = (--m_nCount == 0) ? TRUE : FALSE;
						break;
					}
					m_bUndoing = FALSE;
					return TRUE;
				}
				delete pUndoItem[0];
			}
		}
	}
	return FALSE;
}

BOOL CDisplayTableViewUndoList::Undo(CDisplayTableViewUndoItem *pItem, BOOL bFocus)
{
	BOOL  bStep;
	CDisplayTableViewUndoItem  *pUndoItem;

	if ((pUndoItem = ((bStep = (bFocus  &&  IsCellAction(m_nIndex)) || m_bUndoing)) ? GetAt(m_nIndex - 1) : GetAt(m_nIndex)))
	{
		pItem->Copy(pUndoItem);
		m_nIndex -= bStep;
		m_bUndoing = TRUE;
		return TRUE;
	}
	m_nIndex = -1;
	return FALSE;
}
BOOL CDisplayTableViewUndoList::Undo(CONST CTableViewCell *pCell, CString &szText)
{
	CPoint  ptCell;
	CString  szTable;
	CDisplayTableViewUndoItem  *pUndoItem;

	for (szText.Empty(); (pUndoItem = GetAt(0)) && pUndoItem->GetCell(szTable, ptCell) && pCell->x == ptCell.x && pCell->y == ptCell.y; )
	{
		szText = pUndoItem->GetInitialText();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableViewUndoList::CanUndo(BOOL bFocus) CONST
{
	INT  nItem;
	INT  nItems;
	CDisplayTableViewUndoItem  *pUndoItem;

	for (nItem = ((bFocus && IsCellAction(m_nIndex)) || m_bUndoing) ? (m_nIndex - 1) : m_nIndex, nItems = (INT)GetSize(); nItem >= 0; nItem--)
	{
		if ((pUndoItem = GetAt(nItem)) && !pUndoItem->IsCollected()) break;
		continue;
	}
	return((!m_nIndex  &&  bFocus) || nItem >= 0);
}

BOOL CDisplayTableViewUndoList::CanCollectUndo() CONST
{
	CDisplayTableViewUndoItem  *pUndoItem;

	return(((pUndoItem = GetAt(m_nIndex)) && pUndoItem->IsCollected()) ? TRUE : FALSE);
}

BOOL CDisplayTableViewUndoList::Redo(CDisplayTableViewUndoItem *pItem, BOOL bFocus)
{
	BOOL  bStep;
	CDisplayTableViewUndoItem  *pUndoItem;

	if ((pUndoItem = ((bStep = (IsCellAction(m_nIndex) || !m_bUndoing))) ? GetAt(m_nIndex + 1) : GetAt((m_nIndex = max(m_nIndex, 0)))))
	{
		pItem->Copy(pUndoItem);
		m_nIndex += bStep;
		m_bUndoing = FALSE;
		return TRUE;
	}
	return FALSE;
}
BOOL CDisplayTableViewUndoList::Redo(CONST CTableViewCell *pCell, CString &szText)
{
	CPoint  ptCell;
	CString  szTable;
	CDisplayTableViewUndoItem  *pUndoItem;

	for (szText.Empty(); (pUndoItem = (GetSize() > 1) ? GetAt((INT)(GetUpperBound())) : (CDisplayTableViewUndoItem *)NULL) && pUndoItem->GetCell(szTable, ptCell) && pCell->x == ptCell.x && pCell->y == ptCell.y; )
	{
		szText = pUndoItem->GetText();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableViewUndoList::CanRedo(BOOL bFocus) CONST
{
	INT  nItem;
	INT  nItems;
	CDisplayTableViewUndoItem  *pUndoItem;

	for (nItem = (IsCellAction(m_nIndex) && !m_bUndoing) ? (m_nIndex + 1) : max(m_nIndex, 0), nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		if ((pUndoItem = GetAt(nItem)) && !pUndoItem->IsCollected()) break;
		continue;
	}
	return(nItem < nItems);
}

BOOL CDisplayTableViewUndoList::CanCollectRedo() CONST
{
	CDisplayTableViewUndoItem  *pUndoItem;

	return(((pUndoItem = GetAt(m_nIndex + 1)) && pUndoItem->IsCollected()) ? TRUE : FALSE);
}

VOID CDisplayTableViewUndoList::Collect(BOOL bEnable, INT nAfter)
{
	if (!IsLocked())
	{
		if (bEnable)
		{
			if (m_bCollecting)
			{
				m_nCount = 0;
				return;
			}
			if ((m_nCount = nAfter) <= 0)
			{
				m_bCollecting = TRUE;
				m_nCount = 0;
			}
			return;
		}
		m_bCollecting = bEnable;
		m_nCount = -1;
	}
}

BOOL CDisplayTableViewUndoList::IsCollecting() CONST
{
	return m_bCollecting;
}

CDisplayTableViewUndoItem *CDisplayTableViewUndoList::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CDisplayTableViewUndoItem *)CPtrArray::GetAt(nIndex) : (CDisplayTableViewUndoItem *)NULL);
}

CDisplayTableViewUndoItem *CDisplayTableViewUndoList::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CDisplayTableViewUndoItem *)CPtrArray::GetAt(nIndex) : (CDisplayTableViewUndoItem *)NULL);
}

VOID CDisplayTableViewUndoList::Reset()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)GetSize(), m_nIndex = -1, m_bUndoing = FALSE, m_bCollecting = FALSE; nItem < nItems; nItem++)
	{
		delete GetAt(nItem);
		RemoveAt(nItem);
		nItems--;
		nItem--;
	}
}

BOOL CDisplayTableViewUndoList::Lock()
{
	if (m_nLocks < UINT_MAX)
	{
		m_nLocks++;
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableViewUndoList::IsLocked() CONST
{
	return((m_nLocks > 0) ? TRUE : FALSE);
}

BOOL CDisplayTableViewUndoList::Unlock()
{
	if (m_nLocks > 0)
	{
		m_nLocks--;
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableViewUndoList::IsCellAction(INT nIndex) CONST
{
	CPoint  ptCell;
	CString  szTable;
	CDisplayTableViewUndoItem  *pUndoItem;

	return(((pUndoItem = GetAt(nIndex)) && pUndoItem->GetCell(szTable, ptCell)) ? (ptCell.x >= 0 && ptCell.y >= 0) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayTableView

IMPLEMENT_DYNCREATE(CDisplayTableView, CDatabaseTableView)

CDisplayTableView::CDisplayTableView(ULONGLONG nComponent, UINT nFloatingMenuID) : CDatabaseTableView(nComponent)
{
	CFontTools  cTitleFont(&m_lfTable[0]);
	CFontTools  cItemsFont(&m_lfTable[1]);

	m_nTimerID[0] = 0;
	m_nTimerID[1] = 0;
	m_nTimerID[2] = 0;
	m_nFloatingMenuID = nFloatingMenuID;
	m_nTableColors[0] = GetSysColor(COLOR_WINDOWTEXT);
	m_nTableColors[1] = GetSysColor(COLOR_3DFACE);
	m_nTableFontColors[0] = GetSysColor(COLOR_WINDOW);
	m_nTableFontColors[1] = GetSysColor(COLOR_WINDOWTEXT);
	m_lfTable[0].lfWeight = FW_BOLD;
	m_lfTable[1].lfWeight = FW_NORMAL;
	m_bPrint[0] = FALSE;
	m_bPrint[1] = FALSE;
	m_bUndo[0] = FALSE;
	m_bUndo[1] = FALSE;
	m_bImage = FALSE;
}

BOOL CDisplayTableView::Create(CWnd *pParentWnd, LPCTSTR pszTag, CONST RECT &rect)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nTable[2];
	INT  nTables[2];
	BOOL  bResize;
	BOOL  bVisible;
	CString  szName;
	CString  szTitle;
	LOGFONT  lfFont[2];
	CUIntArray  nIDs;
	CUIntArray  nTypes;
	CUIntArray  nFormats;
	CStringArray  szItems;
	CStringArray  szRow[3];
	CStringArray  szColumns[2];
	CTableViewCell  *pCell;
	CTableViewCells  pCells;
	CTableViewObject  *pTable;

	if (CDatabaseTableView::Create(pParentWnd, rect))
	{
		for (nTable[0] = 0, nTables[0] = EnumTables(m_szTables, nTypes, FALSE), SetName(pszTag); nTable[0] < nTables[0]; nTable[0]++)
		{
			if (GetTableTitle(m_szTables.GetAt(nTable[0]), szTitle) && GetTableContents(m_szTables.GetAt(nTable[0]), pszTag, -1, szRow[0], szRow[1], szRow[2], nFormats, nIDs, bResize, bVisible))
			{
				if ((pTable = new CTableViewObject) != (CTableViewObject *)NULL)
				{
					for (pTable->SetName(m_szTables.GetAt(nTable[0])), pTable->SetTitle(szTitle), pTable->SetType(nTypes.GetAt(nTable[0])), pTable->EnableResize(bResize), pTable->MakeVisible(bVisible); pTable->GetType() == TAS_TABLE_LIST; )
					{
						if (!szRow[0].GetSize()) szRow[0].Add(EMPTYSTRING);
						break;
					}
					for (nCol = 0, nCols = (!szTitle.IsEmpty()) ? ExtractTextItems(szTitle, szColumns[0]) : 0, GetTableOutlineFonts(pTable->GetName(), &lfFont[0], &lfFont[1]); nCol < nCols; nCol++)
					{
						if ((pCell = new CTableViewCell) != (CTableViewCell *)NULL)
						{
							pCell->SetFormat(TAS_TYPE_TEXT | TAS_ALIGN_LEFT | TAS_ALIGN_VCENTER);
							pCell->SetTextStyle(TRANSPARENT, m_nTableFontColors[0], m_nTableColors[0]);
							pCell->SetText(szColumns[0].GetAt(nCol), FALSE);
							pCell->SetFont(&lfFont[0]);
							pCell->x = nCol;
							pCell->y = 0;
							if (pCells.Add(pCell) >= 0) continue;
							delete pCell;
						}
						break;
					}
					for (nRow = 0, nRows = (nCol == nCols) ? (INT)szRow[0].GetSize() : -1; nRow < nRows; nRow++)
					{
						for (nCol = 0, nCols = (ExtractTextItems(szRow[0].GetAt(nRow), szColumns[1]) >= 0 && szTitle.IsEmpty()) ? (INT)szColumns[1].GetSize() : nCols; nCol < nCols; nCol++)
						{
							if ((pCell = new CTableViewCell) != (CTableViewCell *)NULL)
							{
								if (pTable->GetType() == TAS_TABLE_NORMAL)
								{
									for (pCell->SetFormat(TAS_TYPE_TEXT | TAS_ALIGN_LEFT | TAS_ALIGN_VCENTER); !nCol; )
									{
										pCell->SetFormat(TAS_TYPE_TEXT | TAS_ALIGN_RIGHT | TAS_ALIGN_VCENTER);
										break;
									}
									if (nCol == nCols - 1)
									{
										if (nRow < nFormats.GetSize()) pCell->SetFormat(nFormats.GetAt(nRow));
										if (nRow < nIDs.GetSize()) pCell->SetControlID(nIDs.GetAt(nRow));
									}
								}
								if (pTable->GetType() == TAS_TABLE_LIST)
								{
									if (nCol < nFormats.GetSize()) pCell->SetFormat(nFormats.GetAt(nCol));
									if (nCol < nIDs.GetSize()) pCell->SetControlID(nIDs.GetAt(nCol));
								}
								for (pCell->x = nCol, pCell->y = nRow, pCell->SetFont(&lfFont[1]), pCell->SetTextStyle(TRANSPARENT, m_nTableFontColors[1], m_nTableColors[1]), pCell->SetText((nCol < szColumns[1].GetSize()) ? (LPCTSTR)szColumns[1].GetAt(nCol) : EMPTYSTRING, FALSE); !szTitle.IsEmpty(); )
								{
									pCell->y = nRow + 1;
									break;
								}
								if (pCells.Add(pCell) >= 0) continue;
								delete pCell;
							}
							break;
						}
					}
					if (nRows >= 0)
					{
						if (pTable->SetCells(pCells))
						{
							if (AddTable(pTable, FALSE))
							{
								for (nRow = 0, nRows = (pTable->GetType() == TAS_TABLE_NORMAL) ? (INT)szRow[0].GetSize() : 0; nRow < nRows; nRow++)
								{
									if ((pCell = pTable->FindCell((pTable->HasTitle()) ? (nRow + 1) : nRow, (INT)max(szColumns[0].GetSize() - 1, 0))))
									{
										ExtractTextItems(szRow[0].GetAt(nRow), szColumns[1]);
										EnumTableCellValues(pTable, pCell, szColumns[1].GetAt(0));
										LimitTableCellValues(pTable, pCell, szColumns[1].GetAt(0));
									}
								}
								for (nCol = 0, nCols = (pTable->GetType() == TAS_TABLE_LIST) ? (INT)max(szColumns[0].GetSize(), szColumns[1].GetSize()) : 0; nCol < nCols; nCol++)
								{
									for (nRow = 0, nRows = (INT)szRow[0].GetSize(); nRow < nRows; nRow++)
									{
										if ((pCell = pTable->FindCell((pTable->HasTitle()) ? (nRow + 1) : nRow, nCol)))
										{
											EnumTableCellValues(pTable, pCell, (nCol < szColumns[0].GetSize()) ? szColumns[0].GetAt(nCol) : EMPTYSTRING);
											LimitTableCellValues(pTable, pCell, (nCol < szColumns[0].GetSize()) ? szColumns[0].GetAt(nCol) : EMPTYSTRING);
										}
									}
								}
								pTable->EnableResize();
								szColumns[0].RemoveAll();
								szColumns[1].RemoveAll();
								pCells.RemoveAll();
								continue;
							}
						}
					}
					delete pTable;
				}
			}
			break;
		}
		for (nTable[1] = 0, nTables[1] = nTables[0], ArrangeTables(); nTable[1] < nTables[1]; nTable[1]++)
		{
			if ((pTable = m_pTables->GetAt(m_pTables->Find(m_szTables.GetAt(nTable[1])))))
			{
				if (GetTableUpdateContents(pTable->GetName(), -1, GetName(), szName, szItems))
				{
					UpdateTableContents(pTable, szItems);
					continue;
				}
				ProtectTableFieldData(pTable->GetName());
			}
		}
		ArrangeTables(0);
		return((nTable[0] == nTables[0]) ? TRUE : FALSE);
	}
	return FALSE;
}

VOID CDisplayTableView::SetTablesFonts(CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont)
{
	INT  nTable;
	INT  nTables;
	LOGFONT  lfTable[2];
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (memcmp(&m_lfTable[0], plfTitleFont, sizeof(LOGFONT)) || memcmp(&m_lfTable[1], plfItemsFont, sizeof(LOGFONT))) ? (INT)m_pTables->GetSize() : 0, CopyMemory(&m_lfTable[0], plfTitleFont, sizeof(LOGFONT)), CopyMemory(&m_lfTable[1], plfItemsFont, sizeof(LOGFONT)); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && GetTableFonts(pTable, &lfTable[0], &lfTable[1]))
		{
			SetTableFonts(pTable, &lfTable[0], &lfTable[1]);
			RecalcTable(pTable, FALSE, TRUE, FALSE);
		}
	}
	RepositionTables();
}

VOID CDisplayTableView::GetTablesFonts(LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST
{
	CopyMemory(plfTitleFont, &m_lfTable[0], sizeof(LOGFONT));
	CopyMemory(plfItemsFont, &m_lfTable[1], sizeof(LOGFONT));
}

VOID CDisplayTableView::SetTablesFontColors(COLORREF nTitleColor, COLORREF nItemsColor)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nMode;
	INT  nTable;
	INT  nTables;
	COLORREF  nColors[2];
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (m_nTableFontColors[0] != nTitleColor || m_nTableFontColors[1] != nItemsColor) ? (INT)m_pTables->GetSize() : 0, m_nTableFontColors[0] = nTitleColor, m_nTableFontColors[1] = nItemsColor; nTable < nTables; nTable++)
	{
		for (nRow = 0, nRows = ((pTable = m_pTables->GetAt(nTable))) ? pTable->GetRows() : 0; nRow < nRows; nRow++)
		{
			for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				if ((pCell = pTable->FindCell(nRow, nCol)))
				{
					pCell->GetTextStyle(nMode, nColors[0], nColors[1]);
					pCell->SetTextStyle(nMode, (pTable->HasTitle() && !nRow) ? nTitleColor : nItemsColor, nColors[1]);
				}
			}
		}
	}
}

VOID CDisplayTableView::GetTablesFontColors(COLORREF &nTitleColor, COLORREF &nItemsColor) CONST
{
	nTitleColor = m_nTableFontColors[0];
	nItemsColor = m_nTableFontColors[1];
}

VOID CDisplayTableView::SetTablesColors(COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (m_nTableColors[0] != nTitleBackground || m_nTableColors[1] != nKeysBackground) ? (INT)m_pTables->GetSize() : 0, m_nTableColors[0] = nTitleBackground, m_nTableColors[1] = nKeysBackground; nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)))
		{
			if (pTable->GetType() == TAS_TABLE_NORMAL)
			{
				for (pTable->SetRowBackgroundColor(1, nKeysBackground); pTable->HasTitle(); )
				{
					pTable->SetRowBackgroundColor(0, nTitleBackground);
					break;
				}
				continue;
			}
			if (pTable->GetType() == TAS_TABLE_LIST)
			{
				for (pTable->SetColumnBackgroundColor(0, nKeysBackground); pTable->HasTitle(); )
				{
					pTable->SetRowBackgroundColor(0, nTitleBackground);
					break;
				}
			}
		}
	}
}

VOID CDisplayTableView::GetTablesColors(COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	nTitleBackground = m_nTableColors[0];
	nKeysBackground = m_nTableColors[1];
}

VOID CDisplayTableView::SetTableFonts(CTableViewObject *pTable, CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	CTableViewCell  *pCell;

	for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
	{
		for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
		{
			if ((pCell = pTable->FindCell(nRow, nCol)))
			{
				if (pTable->HasTitle() && !nRow)
				{
					pCell->SetFont(plfTitleFont);
					continue;
				}
				pCell->SetFont(plfItemsFont);
			}
		}
	}
}

BOOL CDisplayTableView::GetTableFonts(CONST CTableViewObject *pTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST
{
	return GetTableOutlineFonts(GetName(), plfTitleFont, plfItemsFont);
}

BOOL CDisplayTableView::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	CPoint  ptDrop;
	CString  szName;
	CStringArray  szCells;
	CStringArray  szTables;
	CTableViewCell  *pCell[2];
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = EnumTableDropTargets(nComponent, szTables, szCells), ptDrop = point, ptDrop.Offset(GetScrollPosition()), ScreenToClient(&ptDrop); nTable < nTables; nTable++)
	{
		if ((pCell[0] = (((pTable = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable)))) && pTable->IsVisible() && pTable->PtInRect(ptDrop) && FindTableDropTargetCell(pTable->GetName(), szCells.GetAt(nTable), nComponent, pszTable, szName, nRow, nCol))) ? pTable->FindCell(ptDrop) : (CTableViewCell *)NULL) && (pCell[0]->y > 0 || !pTable->HasTitle()))
		{
			if ((pCell[1] = pTable->FindCell(pCell[0]->y, nCol)) && pCell[0]->x == nCol  &&  nRow < 0 && pCell[1]->IsEnabled()) break;
			if ((pCell[1] = pTable->FindCell(nRow, pCell[0]->x)) && pCell[0]->y == nRow  &&  nCol < 0 && pCell[1]->IsEnabled()) break;
			if ((pCell[1] = pTable->FindCell(nRow, nCol)) && pCell[0]->x == nCol  &&  pCell[0]->y == nRow  &&  pCell[1]->IsEnabled()) break;
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	INT  nRow;
	INT  nCol;
	INT  nTable[2];
	INT  nTables[2];
	CPoint  ptDrop;
	CString  szName;
	CString  szItem;
	CString  szTable[2];
	CStringArray  szCells;
	CStringArray  szItems;
	CStringArray  szTables[2];
	CTableViewCell  *pCell[3];
	CTableViewObject  *pTable[2];
	CDisplayTableViewUndoItem  cUndoItem;

	for (nTable[0] = 0, nTables[0] = EnumTableDropTargets(nComponent, szTables[0], szCells), ptDrop = point, ptDrop.Offset(GetScrollPosition()), ScreenToClient(&ptDrop), SetActiveCell(); nTable[0] < nTables[0]; nTable[0]++)
	{
		if ((pTable[0] = m_pTables->GetAt(m_pTables->Find((szTable[0] = szTables[0].GetAt(nTable[0]))))) && pTable[0]->IsVisible() && pTable[0]->PtInRect(ptDrop))
		{
			if (FindTableDropTargetCell(szTable[0], szCells.GetAt(nTable[0]), nComponent, pszTable, szName, nRow, nCol))
			{
				if ((pCell[0] = pTable[0]->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
				{
					if ((pCell[1] = pTable[0]->FindCell(ptDrop)) && pCell[0]->x == pCell[1]->x  &&  pCell[0]->y == pCell[1]->y)
					{
						if (((pCell[0]->GetFormat() & TAS_TYPE_TEXT) != TAS_TYPE_TEXT) && ((pCell[0]->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE))
						{
							ConvertUndoItem(pCell[0]->GetControl(), &cUndoItem);
							m_cUndoList.Add(&cUndoItem);
							cUndoItem.SetText(szName);
							cUndoItem.SetSel(0, szName.GetLength());
							m_cUndoList.Add(&cUndoItem);
						}
						for (m_cUndoList.Lock(), nTable[1] = 0, nTables[1] = EnumTableUpdates(pCell[0]->GetControlID(), szTables[1]), UpdateTableFieldData(pCell[0]->GetControlID(), szName); nTable[1] < nTables[1]; nTable[1]++)
						{
							if (GetTableUpdateContents((szTable[1] = szTables[1].GetAt(nTable[1])), pCell[0]->GetControlID(), szName, szItem, szItems))
							{
								if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(szTable[1]))))
								{
									UpdateTableContents(pTable[1], szItems);
									ArrangeTables(0);
								}
							}
						}
						for (pCell[0]->SetText((pCell[0]->GetFormat() & TAS_TYPE_SUBTABLE) ? pCell[0]->GetText() : szName); (pCell[0]->GetFormat() & (TAS_TYPE_TEXT | TAS_TYPE_SUBTABLE)) == 0; )
						{
							SetActiveCell(pTable[0], pCell[0]);
							break;
						}
						m_cUndoList.Unlock();
						break;
					}
					continue;
				}
				if (nRow < 0)
				{
					if ((pCell[1] = pTable[0]->FindCell(ptDrop)))
					{
						if (pCell[1]->x == nCol  &&  pCell[1]->y >= 0)
						{
							if ((pCell[2] = pTable[0]->FindCell(pCell[1]->y, nCol)))
							{
								if (((pCell[2]->GetFormat() & TAS_TYPE_TEXT) != TAS_TYPE_TEXT) && ((pCell[2]->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE))
								{
									ConvertUndoItem(pCell[2]->GetControl(), &cUndoItem);
									m_cUndoList.Add(&cUndoItem);
									cUndoItem.SetText(szName);
									cUndoItem.SetSel(0, szName.GetLength());
									m_cUndoList.Add(&cUndoItem);
								}
								for (m_cUndoList.Lock(), pCell[2]->SetText(szName); ((pCell[2]->GetFormat() & TAS_TYPE_TEXT) != TAS_TYPE_TEXT) && ((pCell[2]->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE); )
								{
									pTable[0]->SetSelRow(pCell[2]->y);
									SetActiveCell(pTable[0], pCell[2]);
									break;
								}
								if ((pCell[2]->GetFormat() & TAS_TYPE_COMBOLISTBOX) || (pCell[2]->GetFormat() & TAS_TYPE_COMBOEDITBOX))
								{
									for (nTable[1] = 0, nTables[1] = EnumTableUpdates(pCell[2]->GetControlID(), szTables[1]); nTable[1] < nTables[1]; nTable[1]++)
									{
										if (GetTableUpdateContents((szTable[1] = szTables[1].GetAt(nTable[1])), pCell[0]->GetControlID(), szName, szItem, szItems))
										{
											if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(szTable[1]))))
											{
												UpdateTableContents(pTable[1], szItems);
												continue;
											}
										}
									}
								}
								UpdateTableFieldData(pCell[2]->GetControlID(), szName);
								ProtectTableFieldData(pTable[0]->GetName());
								RecalcTable(pTable[0], FALSE, TRUE, FALSE);
								ArrangeTables(0);
								m_cUndoList.Unlock();
								break;
							}
						}
					}
					continue;
				}
				break;
			}
		}
	}
	return((nTable[0] < nTables[0]) ? TRUE : FALSE);
}

BOOL CDisplayTableView::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	CTableViewObject  *pTable;

	if ((pTable = FindTable(TranslateComponentToTableName(nComponent))))
	{
		SelectTableFieldData(pTable->GetName(), pszName);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::DoSave()
{
	if (GetDatabase()->SaveTables(this, m_nComponent))
	{
		SetActiveCell();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::CanSave() CONST
{
	return GetDatabase()->CanSaveTables(this, m_nComponent);
}

BOOL CDisplayTableView::DoCheck()
{
	INT  nIssue;
	INT  nIssues;
	BOOL  bCheck;
	CString  szMessage[2];
	CStringArray  szIssues;

	for (bCheck = GetDatabase()->CheckTables(this, m_nComponent, szIssues), ResetMessages(); szIssues.GetSize() > 0; )
	{
		szMessage[0].Format(STRING(IDS_COMPILER_MESSAGE_STARTCHECKING), (LPCTSTR)GetDatabase()->GetName(), (LPCTSTR)szIssues.GetAt(0));
		szMessage[1].Format(STRING(IDS_COMPILER_MESSAGE_STOPCHECKING), (UINT)(szIssues.GetSize() - 1));
		szIssues.SetAt(0, szMessage[0]);
		szIssues.Add(szMessage[1]);
		break;
	}
	for (nIssue = 0, nIssues = (INT)szIssues.GetSize(), ResetMessages(); nIssue < nIssues; nIssue++)
	{
		ShowMessage(szIssues.GetAt(nIssue), FALSE);
		continue;
	}
	return bCheck;
}

BOOL CDisplayTableView::CanCheck() CONST
{
	return GetDatabase()->CanCheckTables(this, m_nComponent);
}

BOOL CDisplayTableView::DoPrint(LPCTSTR pszTable, LPCTSTR pszItem, CMetaFileDC &cMetaDC)
{
	return PrintTable(pszTable, pszItem, cMetaDC);
}

BOOL CDisplayTableView::CanPrint(UINT nFlags, CString &szTable, CStringArray &szTables) CONST
{
	INT  nCount;
	INT  nTable;
	INT  nTables;
	CUIntArray  nTypes;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable[2];

	if (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE)
	{
		szTable = ((nCount = (INT)m_szTables.GetSize()) > 0) ? (LPCTSTR)m_szTables.GetAt(m_szTables.GetSize() - nCount) : EMPTYSTRING;
		return((EnumPrintTables(szTable, nFlags, szTables) > 0) ? TRUE : FALSE);
	}
	if (nFlags & DISPLAYTABLEVIEW_PRINT_SUBTABLE)
	{
		for (nTable = 0, nTables = EnumTables(szTables, nTypes, TRUE, FALSE); nTable < nTables; nTable++)
		{
			if ((pTable[0] = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable)))))
			{
				if ((pCell = GetActiveCell(pTable[1])) && pTable[0] == pTable[1])
				{
					szTable = pTable[0]->GetName();
					break;
				}
				if (pTable[0]->GetSelRow() > 0)
				{
					szTable = pTable[0]->GetName();
					break;
				}
			}
		}
		if (nTable < nTables)
		{
			szTables.RemoveAll();
			return((EnumPrintTables(szTable, nFlags, szTables) > 0) ? TRUE : FALSE);
		}
	}
	szTable.Empty();
	szTables.RemoveAll();
	return FALSE;
}
BOOL CDisplayTableView::CanPrint(UINT nFlags) CONST
{
	CString  szName;
	CStringArray  szTables;

	return CanPrint(nFlags, szName, szTables);
}

BOOL CDisplayTableView::DoDelete()
{
	if (GetDatabase()->DeleteTables(this, m_nComponent))
	{
		DoResetTables();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::CanDelete() CONST
{
	return GetDatabase()->CanDeleteTables(this, m_nComponent);
}

VOID CDisplayTableView::DoClose()
{
	GetDatabase()->SaveTables(this, m_nComponent, TRUE, TRUE);
}

BOOL CDisplayTableView::DoSaveTable()
{
	CTableViewObject  *pTable;

	if ((pTable = GetActiveTable()))
	{
		GetDatabase()->SaveTables(this, TranslateTableNameToComponent(pTable->GetName()));
		SetActiveCell();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::CanSaveTable() CONST
{
	ULONGLONG  nComponent;
	CTableViewObject  *pTable;

	return(((pTable = GetActiveTable())) ? GetDatabase()->CanSaveTables(this, ((nComponent = TranslateTableNameToComponent(pTable->GetName())) & DATABASE_SUBCOMPONENTS_ALL) ? nComponent : 0) : FALSE);
}

BOOL CDisplayTableView::DoCheckTable()
{
	INT  nIssue;
	INT  nIssues;
	BOOL  bCheck;
	CString  szMessage[2];
	CStringArray  szIssues;
	CTableViewObject  *pTable;

	if ((pTable = GetActiveTable()))
	{
		for (bCheck = GetDatabase()->CheckTables(this, TranslateTableNameToComponent(pTable->GetName()), szIssues); szIssues.GetSize() > 0; )
		{
			szMessage[0].Format(STRING(IDS_COMPILER_MESSAGE_STARTCHECKING), (LPCTSTR)GetDatabase()->GetName(), (LPCTSTR)szIssues.GetAt(0));
			szMessage[1].Format(STRING(IDS_COMPILER_MESSAGE_STOPCHECKING), (UINT)(szIssues.GetSize() - 1));
			szIssues.SetAt(0, szMessage[0]);
			szIssues.Add(szMessage[1]);
			break;
		}
		for (nIssue = 0, nIssues = (INT)szIssues.GetSize(), ResetMessages(); nIssue < nIssues; nIssue++)
		{
			ShowMessage(szIssues.GetAt(nIssue), FALSE);
			continue;
		}
		return bCheck;
	}
	return FALSE;
}

BOOL CDisplayTableView::CanCheckTable() CONST
{
	ULONGLONG  nComponent;
	CTableViewObject  *pTable;

	return(((pTable = GetActiveTable())) ? GetDatabase()->CanCheckTables(this, ((nComponent = TranslateTableNameToComponent(pTable->GetName())) & DATABASE_SUBCOMPONENTS_ALL) ? nComponent : 0) : FALSE);
}

BOOL CDisplayTableView::DoDeleteTable()
{
	CTableViewObject  *pTable;

	if ((pTable = GetActiveTable()))
	{
		GetDatabase()->DeleteTables(this, TranslateTableNameToComponent(pTable->GetName()));
		SetActiveCell();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::CanDeleteTable() CONST
{
	ULONGLONG  nComponent;
	CTableViewObject  *pTable;

	return(((pTable = GetActiveTable())) ? GetDatabase()->CanDeleteTables(this, ((nComponent = TranslateTableNameToComponent(pTable->GetName())) & DATABASE_SUBCOMPONENTS_ALL) ? nComponent : 0) : FALSE);
}

BOOL CDisplayTableView::DoImportTables()
{
	CTableViewObject  *pTable;

	return(((pTable = GetActiveTable())) ? GetDatabase()->ImportTables(this, TranslateTableNameToComponent(pTable->GetName())) : FALSE);
}

BOOL CDisplayTableView::CanImportTables() CONST
{
	ULONGLONG  nComponent;
	CTableViewObject  *pTable;

	return(((pTable = GetActiveTable())) ? GetDatabase()->CanImportTables(this, ((nComponent = TranslateTableNameToComponent(pTable->GetName())) & DATABASE_SUBCOMPONENTS_ALL) ? nComponent : 0) : FALSE);
}

BOOL CDisplayTableView::DoExportTables()
{
	CTableViewObject  *pTable;

	return(((pTable = GetActiveTable())) ? GetDatabase()->ExportTables(this, TranslateTableNameToComponent(pTable->GetName())) : FALSE);
}

BOOL CDisplayTableView::CanExportTables() CONST
{
	ULONGLONG  nComponent;
	CTableViewObject  *pTable;

	return(((pTable = GetActiveTable())) ? GetDatabase()->CanExportTables(this, ((nComponent = TranslateTableNameToComponent(pTable->GetName())) & DATABASE_SUBCOMPONENTS_ALL) ? nComponent : 0) : FALSE);
}

BOOL CDisplayTableView::DoDiscardTables()
{
	for (SetActiveCell(); GetDatabase()->DiscardTables(this, m_nComponent, FALSE); )
	{
		RefreshTables();
		ClearUndo();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::CanDiscardTables() CONST
{
	return GetDatabase()->CanDiscardTables(this, m_nComponent, FALSE);
}

BOOL CDisplayTableView::DoDiscardAllTables()
{
	for (SetActiveCell(); GetDatabase()->DiscardTables(this, m_nComponent, TRUE); )
	{
		RefreshTables();
		ClearUndo();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::CanDiscardAllTables() CONST
{
	return GetDatabase()->CanDiscardTables(this, m_nComponent, TRUE);
}

BOOL CDisplayTableView::DoResetTables()
{
	return DoEmpty();
}

BOOL CDisplayTableView::CanResetTables() CONST
{
	return !IsEmpty();
}

BOOL CDisplayTableView::DoInsertTableRowAbove()
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	BOOL  bSuccess;
	CString  szTable;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), bSuccess = FALSE; nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelRow() >= 0 && pTable->GetSelRow() < pTable->GetRows() && !pTable->GetSelCell(nRow, nCol))
		{
			for (m_cUndoList.Collect(TRUE, 1), SetActiveCell(); (bSuccess = InsertTableRow(pTable, (nRow = pTable->GetSelRow())) && InsertTableFieldData((szTable = pTable->GetName()), nRow)); )
			{
				ProtectTableFieldData(szTable, TRUE);
				RecalcTable(pTable, FALSE, TRUE, FALSE);
				SelectTableFieldData(szTable, CPoint(-1, nRow));
				break;
			}
			m_cUndoList.Collect(FALSE);
			ArrangeTables(0);
			break;
		}
	}
	return bSuccess;
}

BOOL CDisplayTableView::CanInsertTableRowAbove() CONST
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	INT  nLimits[2];
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelRow() >= 0 && pTable->GetSelRow() < pTable->GetRows() && !pTable->GetSelCell(nRow, nCol))
		{
			if (!GetTableOutlineLimits(pTable->GetName(), nLimits[0], nLimits[1]) || pTable->GetRows() < nLimits[1])
			{
				if ((nRow = pTable->GetSelRow()) > 0 || !pTable->HasTitle())
				{
					if (IsTableRowEmpty(pTable, nRow)) nTable = nTables;
					break;
				}
			}
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DoInsertTableRowBelow()
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	BOOL  bSuccess;
	CString  szTable;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), bSuccess = FALSE; nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST && ((pTable->GetSelRow() >= 0 && pTable->GetSelRow() < pTable->GetRows()) || (pTable->GetRows() == 1 && pTable->GetSelRow() == pTable->GetRows())) && !pTable->GetSelCell(nRow, nCol))
		{
			for (m_cUndoList.Collect(TRUE, 1), SetActiveCell(); (bSuccess = InsertTableRow(pTable, (nRow = min(max(pTable->GetSelRow() + 1, 0), pTable->GetRows()))) && InsertTableFieldData((szTable = pTable->GetName()), nRow)); )
			{
				ProtectTableFieldData(szTable, TRUE);
				RecalcTable(pTable, FALSE, TRUE, FALSE);
				SelectTableFieldData(szTable, CPoint(-1, nRow));
				break;
			}
			m_cUndoList.Collect(FALSE);
			ArrangeTables(0);
			break;
		}
	}
	return bSuccess;
}

BOOL CDisplayTableView::CanInsertTableRowBelow() CONST
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	INT  nLimits[2];
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST && ((pTable->GetSelRow() >= 0 && pTable->GetSelRow() < pTable->GetRows()) || (pTable->GetRows() == 1 && pTable->GetSelRow() == pTable->GetRows())) && !pTable->GetSelCell(nRow, nCol))
		{
			if (!GetTableOutlineLimits(pTable->GetName(), nLimits[0], nLimits[1]) || pTable->GetRows() < nLimits[1])
			{
				if ((nRow = min(max(pTable->GetSelRow(), 0), pTable->GetRows() - 1)) > 0 || !pTable->HasTitle())
				{
					if (IsTableRowEmpty(pTable, nRow)) nTable = nTables;
					break;
				}
			}
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DoInsertTableColumnBefore()
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	BOOL  bSuccess;
	CString  szTable;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), bSuccess = FALSE; nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelCell(nRow, nCol))
		{
			for (m_cUndoList.Collect(TRUE, 1), SetActiveCell(); (bSuccess = InsertTableColumn(pTable, nCol) && InsertTableFieldData((szTable = pTable->GetName()), nRow, nCol)); )
			{
				ProtectTableFieldData(szTable, TRUE);
				RecalcTable(pTable, TRUE, TRUE, FALSE);
				SelectTableFieldData(szTable, CPoint(nCol, nRow));
				break;
			}
			m_cUndoList.Collect(FALSE);
			ArrangeTables(0);
			break;
		}
	}
	return bSuccess;
}

BOOL CDisplayTableView::CanInsertTableColumnBefore() CONST
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelCell(nRow, nCol))
		{
			if (!IsTableRowFull(pTable, nRow)) nTable = nTables;
			break;
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DoInsertTableColumnAfter()
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	BOOL  bSuccess;
	CString  szTable;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), bSuccess = FALSE; nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelCell(nRow, nCol))
		{
			for (m_cUndoList.Collect(TRUE, 1), SetActiveCell(); (bSuccess = InsertTableColumn(pTable, nCol + 1) && InsertTableFieldData((szTable = pTable->GetName()), nRow, nCol + 1)); )
			{
				ProtectTableFieldData(szTable, TRUE);
				RecalcTable(pTable, TRUE, TRUE, FALSE);
				SelectTableFieldData(szTable, CPoint(nCol + 1, nRow));
				break;
			}
			m_cUndoList.Collect(FALSE);
			ArrangeTables(0);
			break;
		}
	}
	return bSuccess;
}

BOOL CDisplayTableView::CanInsertTableColumnAfter() CONST
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelCell(nRow, nCol))
		{
			if (!IsTableRowFull(pTable, nRow)) nTable = nTables;
			break;
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DoClearTableRow()
{
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	CRect  rTable;
	CString  szText;
	CString  szItem;
	CStringArray  szItems;
	CStringArray  szTables;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable[2];
	CDisplayTableViewUndoItem  cUndoItem[2];

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable[0] = m_pTables->GetAt(nTable)) && ((!pTable[0]->HasTitle() && pTable[0]->GetSelRow() >= 0) || (pTable[0]->HasTitle() && pTable[0]->GetSelRow() > 0)) && pTable[0]->GetSelRow() < pTable[0]->GetRows())
		{
			for (nCol = 0, nCols = pTable[0]->GetColumns(), m_cUndoList.Collect(TRUE, 1), SetActiveCell(), ConvertUndoItem(pTable[0]->GetName(), &cUndoItem[0]), ConvertUndoItem(pTable[0]->GetName(), &cUndoItem[1]); nCol < nCols; nCol++)
			{
				for (cUndoItem[0].SetCell(pTable[0]->GetName(), CPoint(nCol, pTable[0]->GetSelRow())), cUndoItem[1].SetCell(pTable[0]->GetName(), CPoint(nCol, pTable[0]->GetSelRow())), cUndoItem[0].SetText(pTable[0]->GetCellText(pTable[0]->GetSelRow(), nCol)), cUndoItem[1].SetText(EMPTYSTRING), cUndoItem[0].SetSel(0, cUndoItem[0].GetText().GetLength()), cUndoItem[1].SetSel(0, cUndoItem[1].GetText().GetLength()); (pCell = pTable[0]->FindCell(pTable[0]->GetSelRow(), nCol)); )
				{
					if ((pCell->GetFormat() & (TAS_TYPE_TEXT | TAS_TYPE_SUBTABLE)) == 0)
					{
						m_cUndoList.Add(&cUndoItem[0]);
						m_cUndoList.Add(&cUndoItem[1]);
					}
					break;
				}
			}
			for (nCol = 0; nCol < nCols; nCol++)
			{
				if ((pCell = pTable[0]->FindCell(pTable[0]->GetSelRow(), nCol)))
				{
					for (nTable = 0, nTables = EnumTableUpdates(pCell->GetControlID(), szTables), pCell->SetText((szText = EMPTYSTRING), FALSE), UpdateTableFieldData(pCell->GetControlID(), szText); nTable < nTables; nTable++)
					{
						if (GetTableUpdateContents(szTables.GetAt(nTable), pCell->GetControlID(), pCell->GetText(), szItem, szItems))
						{
							if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable)))))
							{
								UpdateTableContents(pTable[1], szItems);
								continue;
							}
						}
					}
				}
			}
			m_cUndoList.Collect(FALSE);
			ArrangeTables(0);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDisplayTableView::CanClearTableRow() CONST
{
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	CString  szTitle;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST && ((((szTitle = pTable->GetTitle()).GetLength() > 0 && pTable->GetSelRow() > 0) || (szTitle.IsEmpty() && pTable->GetRows() > 1)) && pTable->GetSelRow() >= 0 && pTable->GetSelRow() < pTable->GetRows()))
		{
			for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				if ((pCell = pTable->FindCell(pTable->GetSelRow(), nCol)))
				{
					if (pCell->GetFormat() & TAS_TYPE_TEXT) continue;
					if (!pCell->GetText().IsEmpty()) break;
				}
			}
			return((nCol < nCols) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CDisplayTableView::DoDeleteTableRow()
{
	INT  nRow;
	INT  nTable;
	INT  nTables;
	BOOL  bSuccess;
	CRect  rTable;
	CString  szTitle;
	CString  szTable;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), bSuccess = FALSE; nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  GetTableTitle(pTable->GetName(), szTitle) && (((!szTitle.IsEmpty() && pTable->GetSelRow() > 0) || (szTitle.IsEmpty() && pTable->GetRows() > 1)) && pTable->GetSelRow() >= 0 && pTable->GetSelRow() < pTable->GetRows()))
		{
			for (m_cUndoList.Collect(TRUE, 1), SetActiveCell(); (bSuccess = RemoveTableRow(pTable, (nRow = pTable->GetSelRow())) && DeleteTableFieldData((szTable = pTable->GetName()), nRow)); )
			{
				ProtectTableFieldData(szTable, TRUE);
				RecalcTable(pTable, FALSE, TRUE, FALSE);
				SelectTableFieldData(szTable, CPoint(-1, -1));
				break;
			}
			m_cUndoList.Collect(FALSE);
			ArrangeTables(0);
			break;
		}
	}
	return bSuccess;
}

BOOL CDisplayTableView::CanDeleteTableRow() CONST
{
	INT  nTable;
	INT  nTables;
	INT  nLimits[2];
	CString  szTitle;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST && ((((szTitle = pTable->GetTitle()).GetLength() > 0 && pTable->GetSelRow() > 0) || (szTitle.IsEmpty() && pTable->GetRows() > 1)) && pTable->GetSelRow() >= 0 && pTable->GetSelRow() < pTable->GetRows()))
		{
			if (!GetTableOutlineLimits(pTable->GetName(), nLimits[0], nLimits[1]) || pTable->GetRows() > nLimits[0]) break;
			continue;
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DoDeleteTableColumn()
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	BOOL  bSuccess;
	CString  szTable;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), bSuccess = FALSE; nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelCell(nRow, nCol))
		{
			for (m_cUndoList.Collect(TRUE, 1), SetActiveCell(); (bSuccess = DeleteTableColumn(pTable, nCol) && DeleteTableFieldData((szTable = pTable->GetName()), nRow, nCol)); )
			{
				ProtectTableFieldData(szTable, TRUE);
				RecalcTable(pTable, TRUE, TRUE, FALSE);
				SelectTableFieldData(szTable, CPoint(-1, -1));
				break;
			}
			m_cUndoList.Collect(FALSE);
			ArrangeTables(0);
			break;
		}
	}
	return bSuccess;
}

BOOL CDisplayTableView::CanDeleteTableColumn() CONST
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && pTable->GetType() == TAS_TABLE_LIST  &&  pTable->GetSelCell(nRow, nCol)) break;
		continue;
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DoCopyTableRow()
{
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	LPSTR  pszText;
	HANDLE  hGlobal;
	CString  szRow;
	CString  szCol;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && ((!pTable->HasTitle() && pTable->GetSelRow() >= 0) || (pTable->HasTitle() && pTable->GetSelRow() > 0)) && pTable->GetSelRow() < pTable->GetRows() && !IsTableRowEmpty(pTable, pTable->GetSelRow()))
		{
			for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				szCol = pTable->GetCellText(pTable->GetSelRow(), nCol);
				szRow += (nCol > 0) ? (TAB + szCol) : szCol;
			}
			if (::OpenClipboard(GetSafeHwnd()))
			{
				if ((hGlobal = GlobalAlloc(GHND, (szRow.GetLength() + 1))))
				{
					if ((pszText = (LPSTR)GlobalLock(hGlobal)) != (LPSTR)NULL)
					{
#ifndef UNICODE
						strcpy_s(pszText, szRow.GetLength() + 1, szRow);
#else
						WideCharToMultiByte(CP_ACP, 0, szRow, szRow.GetLength(), pszText, szRow.GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
						if (SetClipboardData(CF_TEXT, hGlobal))
						{
							GlobalUnlock(hGlobal);
							::CloseClipboard();
							return TRUE;
						}
						GlobalUnlock(hGlobal);
					}
					GlobalFree(hGlobal);
				}
				::CloseClipboard();
			}
			break;
		}
	}
	return FALSE;
}

BOOL CDisplayTableView::CanCopyTableRow() CONST
{
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)) && ((!pTable->HasTitle() && pTable->GetSelRow() >= 0) || (pTable->HasTitle() && pTable->GetSelRow() > 0)) && pTable->GetSelRow() < pTable->GetRows() && !IsTableRowEmpty(pTable, pTable->GetSelRow())) break;
		continue;
	}
	return((nTable < nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::DoPasteTableRow()
{
	INT  nPos;
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	LPSTR  pszText;
	HANDLE  hGlobal;
	CString  szText;
	CString  szRow[2];
	CStringArray  szItems;
	CStringArray  szTables;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable[2];
	CDisplayTableViewUndoItem  cUndoItem[2];

	if (::OpenClipboard(GetSafeHwnd()))
	{
		if ((hGlobal = GetClipboardData(CF_TEXT)))
		{
			if ((pszText = (LPSTR)GlobalLock(hGlobal)))
			{
#ifndef UNICODE
				szRow[0] = szRow[1] = pszText;
#else
				MultiByteToWideChar(CP_ACP, 0, pszText, -1, szRow[0].GetBufferSetLength((INT)strlen(pszText)), (INT)strlen(pszText) + 1);
				szRow[0].ReleaseBuffer();
				szRow[1] = szRow[0];
#endif
				for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
				{
					if ((pTable[0] = m_pTables->GetAt(nTable)) && ((!pTable[0]->HasTitle() && pTable[0]->GetSelRow() >= 0) || (pTable[0]->HasTitle() && pTable[0]->GetSelRow() > 0)) && pTable[0]->GetSelRow() < pTable[0]->GetRows())
					{
						for (nCol = 0, nCols = pTable[0]->GetColumns(), SetActiveCell(), ConvertUndoItem(pTable[0]->GetName(), &cUndoItem[0]), ConvertUndoItem(pTable[0]->GetName(), &cUndoItem[1]); nCol < nCols; nCol++)
						{
							for (cUndoItem[0].SetCell(pTable[0]->GetName(), CPoint(nCol, pTable[0]->GetSelRow())), cUndoItem[1].SetCell(pTable[0]->GetName(), CPoint(nCol, pTable[0]->GetSelRow())), cUndoItem[0].SetText(pTable[0]->GetCellText(pTable[0]->GetSelRow(), nCol)), cUndoItem[1].SetText((szText = ((nPos = szRow[0].Find(TAB)) >= 0) ? szRow[0].Left(nPos) : szRow[0])), cUndoItem[0].SetSel(0, cUndoItem[0].GetText().GetLength()), cUndoItem[1].SetSel(0, cUndoItem[1].GetText().GetLength()), cUndoItem[0].Collect(nCol > 0), cUndoItem[1].Collect(TRUE), szRow[0] = (nPos >= 0) ? szRow[0].Mid(nPos + 1) : EMPTYSTRING; (pCell = pTable[0]->FindCell(pTable[0]->GetSelRow(), nCol)); )
							{
								if ((pCell->GetFormat() & (TAS_TYPE_TEXT | TAS_TYPE_SUBTABLE)) == 0)
								{
									m_cUndoList.Add(&cUndoItem[0]);
									m_cUndoList.Add(&cUndoItem[1]);
								}
								break;
							}
						}
						for (nCol = 0, m_cUndoList.Collect(); nCol < nCols; nCol++)
						{
							if ((pCell = pTable[0]->FindCell(pTable[0]->GetSelRow(), nCol)))
							{
								for (nTable = 0, nTables = EnumTableUpdates(pCell->GetControlID(), szTables), pCell->SetText((szText = ((nPos = szRow[1].Find(TAB)) >= 0) ? szRow[1].Left(nPos) : szRow[1]), FALSE), UpdateTableFieldData(pCell->GetControlID(), szText), szRow[1] = (nPos >= 0) ? szRow[1].Mid(nPos + 1) : EMPTYSTRING; nTable < nTables; nTable++)
								{
									if (GetTableUpdateContents(szTables.GetAt(nTable), pCell->GetControlID(), pCell->GetText(), GetName(), szItems))
									{
										if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable)))))
										{
											UpdateTableContents(pTable[1], szItems);
											continue;
										}
									}
								}
							}
						}
						m_cUndoList.Collect(FALSE);
						GlobalUnlock(hGlobal);
						::CloseClipboard();
						ArrangeTables(0);
						return TRUE;
					}
				}
				GlobalUnlock(hGlobal);
			}
		}
		::CloseClipboard();
	}
	return FALSE;
}

BOOL CDisplayTableView::CanPasteTableRow() CONST
{
	INT  nTable;
	INT  nTables;
	UINT  nFormat[2];
	CTableViewObject  *pTable;

	if (::OpenClipboard(GetSafeHwnd()))
	{
		for (nFormat[0] = 0; (nFormat[1] = EnumClipboardFormats(nFormat[0])); nFormat[0] = nFormat[1])
		{
			if (nFormat[1] == CF_TEXT) break;
			continue;
		}
		for (nTable = 0, nTables = (nFormat[1] == CF_TEXT) ? (INT)m_pTables->GetSize() : 0; nTable < nTables; nTable++)
		{
			if ((pTable = m_pTables->GetAt(nTable)) && ((!pTable->HasTitle() && pTable->GetSelRow() >= 0) || (pTable->HasTitle() && pTable->GetSelRow() > 0)) && pTable->GetSelRow() < pTable->GetRows())
			{
				::CloseClipboard();
				return TRUE;
			}
		}
		::CloseClipboard();
	}
	return FALSE;
}

INT CDisplayTableView::EnumTables(CStringArray &szTables, CUIntArray &nTypes, BOOL bMenu, BOOL bResetable) CONST
{
	return GetDatabase()->EnumTables(this, szTables, nTypes, bMenu, bResetable);
}

BOOL CDisplayTableView::GetTableTitle(LPCTSTR pszTable, CString &szTitle) CONST
{
	return GetDatabase()->GetTableTitle(this, pszTable, szTitle);
}

BOOL CDisplayTableView::GetTableLayout(LPCTSTR pszTable, CUIntArray &nWidths) CONST
{
	return GetDatabase()->GetTableLayout(this, pszTable, nWidths);
}
BOOL CDisplayTableView::GetTableLayout(LPCTSTR pszTable, LPCTSTR pszItem, CUIntArray &nWidths) CONST
{
	return GetDatabase()->GetTableLayout(this, pszTable, pszItem, nWidths);
}

BOOL CDisplayTableView::GetTablePosition(LPCTSTR pszTable, CString &szTable, CRect &rPosition) CONST
{
	return GetDatabase()->GetTablePosition(this, pszTable, szTable, rPosition);
}

BOOL CDisplayTableView::SetTableFloatingAlignment(LPCTSTR pszTable, INT nRow)
{
	CTableViewObject  *pTable;

	if ((pTable = m_pTables->GetAt(m_pTables->Find(pszTable))))
	{
		pTable->SetFloatingAlignment(nRow);
		return TRUE;
	}
	return FALSE;
}

INT CDisplayTableView::GetTableFloatingAlignment(LPCTSTR pszTable) CONST
{
	CTableViewObject  *pTable;

	return(((pTable = (!m_bPrint[0] || !m_bPrint[1]) ? m_pTables->GetAt(m_pTables->Find(pszTable)) : (CTableViewObject *)NULL)) ? pTable->GetFloatingAlignment() : -1);
}

BOOL CDisplayTableView::AlignFloatingTable(LPCTSTR pszTable)
{
	INT  nRow;
	CRect  rTable;
	CString  szTable;
	CTableViewObject  *pTable;

	if ((nRow = GetTableFloatingAlignment(pszTable)) >= 0 && GetTablePosition(pszTable, szTable, rTable))
	{
		for (SelectTableFieldData(szTable, CPoint(-1, nRow)); (pTable = m_pTables->GetAt(m_pTables->Find(szTable))); )
		{
			pTable->SetSelRow();
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayTableView::GetTableOutline(LPCTSTR pszTable, COLORREF &nTitleRowColor, COLORREF &nFirstRowColor, COLORREF &nFirstColumnColor, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, INT &nOuterBorderSize, INT &nOuterBorderStyle, COLORREF &nOuterBorderColor, INT &nInnerBorderSize, INT &nInnerBorderStyle, COLORREF &nInnerBorderColor) CONST
{
	return GetDatabase()->GetTableOutline(this, pszTable, nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nOuterBorderSize, nOuterBorderStyle, nOuterBorderColor, nInnerBorderSize, nInnerBorderStyle, nInnerBorderColor);
}

BOOL CDisplayTableView::GetTableOutlineFonts(LPCTSTR pszTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST
{
	return GetDatabase()->GetTableOutlineFonts(this, pszTable, plfTitleFont, plfItemsFont);
}

BOOL CDisplayTableView::GetTableOutlineLimits(LPCTSTR pszTable, INT &nMinRows, INT &nMaxRows) CONST
{
	return GetDatabase()->GetTableOutlineLimits(this, pszTable, nMinRows, nMaxRows);
}

BOOL CDisplayTableView::GetTableContents(LPCTSTR pszTable, LPCTSTR pszItem, INT nRows, CStringArray &szContents, CStringArray &szDescriptions, CStringArray &szDataTypes, CUIntArray &nFormats, CUIntArray &nIDs, BOOL &bResize, BOOL &bVisible) CONST
{
	return GetDatabase()->GetTableContents(this, pszTable, pszItem, nRows, szContents, szDescriptions, szDataTypes, nFormats, nIDs, bResize, bVisible);
}

INT CDisplayTableView::EnumTableFieldValues(LPCTSTR pszTable, LPCTSTR pszField, CStringArray &szValues, CLongUIntArray &nValues) CONST
{
	return GetDatabase()->EnumTableFieldValues(this, pszTable, pszField, szValues, nValues);
}

BOOL CDisplayTableView::GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, INT &nLow, INT &nHigh) CONST
{
	return GetDatabase()->GetTableFieldLimits(this, pszTable, pszField, nLow, nHigh);
}
BOOL CDisplayTableView::GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, UINT &uLow, UINT &uHigh) CONST
{
	return GetDatabase()->GetTableFieldLimits(this, pszTable, pszField, uLow, uHigh);
}
BOOL CDisplayTableView::GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, double &fLow, double &fHigh) CONST
{
	return GetDatabase()->GetTableFieldLimits(this, pszTable, pszField, fLow, fHigh);
}

BOOL CDisplayTableView::GetTableContext(LPCTSTR pszTable, CString &szTable, UINT &nControlID, CString &szValue) CONST
{
	return GetDatabase()->GetTableContext(this, pszTable, szTable, nControlID, szValue);
}

INT CDisplayTableView::EnumTableUpdates(UINT nControlID, CStringArray &szTables) CONST
{
	return GetDatabase()->EnumTableUpdates(this, nControlID, szTables);
}

BOOL CDisplayTableView::GetTableUpdateContents(LPCTSTR pszTable, UINT nControlID, LPCTSTR pszValue, CString &szItem, CStringArray &szContents) CONST
{
	return GetDatabase()->GetTableUpdateContents(this, pszTable, nControlID, pszValue, szItem, szContents);
}

BOOL CDisplayTableView::UpdateTableFieldData(UINT nControlID, LPCTSTR pszValue, LPCTSTR pszOldValue)
{
	m_nTimerID[1] = SetTimer(DISPLAYTABLEVIEW_UPDATEFORM_TIMERID, DISPLAYTABLEVIEW_UPDATEFORM_TIMEOUT, NULL);
	return GetDatabase()->UpdateTableFieldData(this, nControlID, pszValue, pszOldValue);
}

INT CDisplayTableView::InsertTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue)
{
	return GetDatabase()->InsertTableFieldData(this, pszTable, pszValue);
}
BOOL CDisplayTableView::InsertTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol)
{
	return GetDatabase()->InsertTableFieldData(this, pszTable, nRow, nCol);
}

BOOL CDisplayTableView::CheckTableFieldData(LPCTSTR pszTable, BOOL bModified, BOOL bExist) CONST
{
	return GetDatabase()->CheckTableFieldData(this, pszTable, bModified, bExist);
}
BOOL CDisplayTableView::CheckTableFieldData(LPCTSTR pszTable, CStringArray &szIssues) CONST
{
	return GetDatabase()->CheckTableFieldData(this, pszTable, szIssues);
}

BOOL CDisplayTableView::SelectTableFieldData(LPCTSTR pszTable, CONST POINT &pt)
{
	return GetDatabase()->SelectTableFieldData(this, pszTable, pt);
}
BOOL CDisplayTableView::SelectTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue)
{
	return GetDatabase()->SelectTableFieldData(this, pszTable, pszValue);
}

BOOL CDisplayTableView::SaveTableFieldData(LPCTSTR pszTable, BOOL bPrompt)
{
	return GetDatabase()->SaveTableFieldData(this, pszTable, bPrompt);
}

BOOL CDisplayTableView::ProtectTableFieldData(LPCTSTR pszTable, BOOL bUndo)
{
	return GetDatabase()->ProtectTableFieldData(this, pszTable, bUndo);
}

BOOL CDisplayTableView::DeleteTableFieldData(LPCTSTR pszTable)
{
	return GetDatabase()->DeleteTableFieldData(this, pszTable);
}
INT CDisplayTableView::DeleteTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue)
{
	return GetDatabase()->DeleteTableFieldData(this, pszTable, pszValue);
}
BOOL CDisplayTableView::DeleteTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol)
{
	return GetDatabase()->DeleteTableFieldData(this, pszTable, nRow, nCol);
}

BOOL CDisplayTableView::GetTableFieldFlag(LPCTSTR pszTable, INT nRow, INT nCol, CString &szFlag) CONST
{
	return GetDatabase()->GetTableFieldFlag(this, pszTable, nRow, nCol, szFlag);
}

INT CDisplayTableView::EnumTableDropTargets(ULONGLONG nComponent, CStringArray &szTables, CStringArray &szFields) CONST
{
	return GetDatabase()->EnumTableDropTargets(this, nComponent, szTables, szFields);
}

BOOL CDisplayTableView::FindTableDropTargetCell(LPCTSTR pszTable, LPCTSTR pszField, ULONGLONG nComponent, LPCTSTR pszItem, CString &szItem, INT &nRow, INT &nCol) CONST
{
	return GetDatabase()->FindTableDropTargetCell(this, pszTable, pszField, nComponent, pszItem, szItem, nRow, nCol);
}

INT CDisplayTableView::EnumPrintTables(LPCTSTR pszTable, UINT nFlags, CStringArray &szTables) CONST
{
	return GetDatabase()->EnumPrintTables(this, pszTable, nFlags, szTables);
}

BOOL CDisplayTableView::GetPrintTableContents(LPCTSTR pszTable, LPCTSTR pszItem, CStringArray &szContents) CONST
{
	return GetDatabase()->GetPrintTableContents(this, pszTable, pszItem, szContents);
}

BOOL CDisplayTableView::PrintTable(LPCTSTR pszTable, LPCTSTR pszItem, CMetaFileDC &cMetaDC)
{
	return GetDatabase()->PrintTable(this, pszTable, pszItem, cMetaDC);
}

ULONGLONG CDisplayTableView::TranslateTableNameToComponent(LPCTSTR pszTable) CONST
{
	return GetDatabase()->TranslateTableNameToComponent(this, pszTable);
}

CString CDisplayTableView::TranslateComponentToTableName(ULONGLONG nComponent) CONST
{
	return GetDatabase()->TranslateComponentToTableName(this, nComponent);
}

INT CDisplayTableView::TranslateTableFieldToIndex(LPCTSTR pszTable, LPCTSTR pszField) CONST
{
	return GetDatabase()->TranslateTableFieldToIndex(this, pszTable, pszField);
}

UINT CDisplayTableView::TranslateTableFieldToID(LPCTSTR pszTable, LPCTSTR pszField) CONST
{
	return GetDatabase()->TranslateTableFieldToID(this, pszTable, pszField);
}

INT CDisplayTableView::EnumTables(CTableViewObjects *pTables) CONST
{
	return((pTables->Copy(m_pTables)) ? (INT)pTables->GetSize() : 0);
}

VOID CDisplayTableView::RepositionTables(CONST CTableViewObjects *pTables)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	INT  nSize[4];
	INT  nStyle[4];
	CRect  rTable[2];
	CString  szTable[2];
	COLORREF  nColor[4];
	CStringArray  szTables;
	CTableViewCell  *pCell[2];
	CTableViewObject  *pTable[2];

	for (nTable = 0, nTables = (INT)m_szTables.GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable[0] = pTables->GetAt(pTables->Find(m_szTables.GetAt(nTable)))) && pTable[0]->GetType() == TAS_TABLE_NORMAL)
		{
			if (GetTablePosition(pTable[0]->GetName(), szTable[0], rTable[0]) && !szTable[0].IsEmpty() && rTable[0].IsRectEmpty())
			{
				pTable[0]->OffsetCells(-pTable[0]->left, -pTable[0]->top);
				pTable[0]->OffsetRect(-pTable[0]->left, -pTable[0]->top);
			}
		}
	}
	for (nTable = 0; nTable < nTables; nTable++)
	{
		if (GetTablePosition((szTable[0] = m_szTables.GetAt(nTable)), szTable[1], rTable[0]) && !szTable[1].IsEmpty())
		{
			if ((pTable[0] = pTables->GetAt(pTables->Find(szTable[0]))))
			{
				if ((pTable[1] = pTables->GetAt(pTables->Find(szTable[1]))))
				{
					if (rTable[0].left > 0 && !rTable[0].top  &&  !rTable[0].bottom)
					{
						if ((pCell[0] = pTable[1]->FindCell(rTable[0].left, 0)))
						{
							rTable[1].SetRect(pTable[1]->left - pTable[0]->Width() - DATABASETABLEVIEW_TABLE_DISTANCE, pCell[0]->GetPosition().top, pTable[1]->left - DATABASETABLEVIEW_TABLE_DISTANCE, pCell[0]->GetPosition().top + pTable[0]->Height());
							pTable[0]->OffsetCells(rTable[1].TopLeft() - pTable[0]->TopLeft());
							pTable[0]->SetRect(rTable[1].left, rTable[1].top, rTable[1].right, rTable[1].bottom);
						}
					}
					else if (rTable[0].right > 0 && !rTable[0].top  &&  !rTable[0].bottom)
					{
						if ((pCell[0] = pTable[1]->FindCell(rTable[0].right, pTable[1]->GetColumns() - 1)))
						{
							rTable[1].SetRect(pTable[1]->right + DATABASETABLEVIEW_TABLE_DISTANCE, pCell[0]->GetPosition().top, pTable[1]->right + DATABASETABLEVIEW_TABLE_DISTANCE + pTable[0]->Width(), pCell[0]->GetPosition().top + pTable[0]->Height());
							pTable[0]->OffsetCells(rTable[1].TopLeft() - pTable[0]->TopLeft());
							pTable[0]->SetRect(rTable[1].left, rTable[1].top, rTable[1].right, rTable[1].bottom);
						}
					}
					else if (rTable[0].top > 0 && !rTable[0].left  &&  !rTable[0].right)
					{
						if ((pCell[0] = pTable[1]->FindCell(0, rTable[0].top - 1)))
						{
							rTable[1].SetRect(pCell[0]->GetPosition().left, pTable[1]->top - DATABASETABLEVIEW_TABLE_DISTANCE - pTable[0]->Height(), pCell[0]->GetPosition().left + pTable[0]->Width(), pTable[1]->top - DATABASETABLEVIEW_TABLE_DISTANCE);
							pTable[0]->OffsetCells(rTable[1].TopLeft() - pTable[0]->TopLeft());
							pTable[0]->SetRect(rTable[1].left, rTable[1].top, rTable[1].right, rTable[1].bottom);
						}
					}
					else if (rTable[0].bottom > 0 && !rTable[0].left  &&  !rTable[0].right)
					{
						if ((pCell[0] = pTable[1]->FindCell(pTable[1]->GetRows() - 1, rTable[0].bottom - 1)))
						{
							rTable[1].SetRect(pCell[0]->GetPosition().left, pTable[1]->bottom + DATABASETABLEVIEW_TABLE_DISTANCE, pCell[0]->GetPosition().left + pTable[0]->Width(), pTable[1]->bottom + DATABASETABLEVIEW_TABLE_DISTANCE + pTable[0]->Height());
							pTable[0]->OffsetCells(rTable[1].TopLeft() - pTable[0]->TopLeft());
							pTable[0]->SetRect(rTable[1].left, rTable[1].top, rTable[1].right, rTable[1].bottom);
						}
					}
					else if (rTable[0].left > 0 && rTable[0].top > 0 && !rTable[0].right  &&  !rTable[0].bottom)
					{
						if ((pCell[0] = pTable[1]->FindCell(rTable[0].left, rTable[0].top - 1)))
						{
							if ((pCell[0]->GetFormat() & TAS_TYPE_SUBTABLE) == TAS_TYPE_SUBTABLE)
							{
								pCell[0]->GetBorder(TAS_BORDER_LEFT, nSize[0], nStyle[0], nColor[0]);
								pCell[0]->GetBorder(TAS_BORDER_TOP, nSize[1], nStyle[1], nColor[1]);
								pCell[0]->GetBorder(TAS_BORDER_RIGHT, nSize[2], nStyle[2], nColor[2]);
								pCell[0]->GetBorder(TAS_BORDER_BOTTOM, nSize[3], nStyle[3], nColor[3]);
								pTable[1]->SetColumnWidth(pCell[0]->x, (pTable[0]->IsVisible()) ? max(CalcDefaultTableWidth(pTable[0]), pCell[0]->GetPosition().Width()) : pCell[0]->GetPosition().Width());
								pTable[1]->SetRowHeight(pCell[0]->y, (pTable[0]->IsVisible()) ? max(CalcDefaultTableHeight(pTable[0]), pCell[0]->GetPosition().Height()) : CalcDefaultCellHeight(pCell[0], pCell[0]->GetInnerPosition().Width()));
								for (pTable[1]->SetRect(pTable[1]->GetCellsBounds().TopLeft(), pTable[1]->GetCellsBounds().BottomRight()), rTable[1].SetRect(pCell[0]->GetPosition().left + (nSize[0] - 1) / 2 + 1, pCell[0]->GetPosition().top + (nSize[1] - 1) / 2 + 1, pCell[0]->GetPosition().right - nSize[2] / 2, pCell[0]->GetPosition().bottom - nSize[3] / 2); rTable[1].TopLeft() != pTable[0]->TopLeft(); )
								{
									pTable[0]->OffsetCells(rTable[1].TopLeft() - pTable[0]->TopLeft());
									pTable[0]->OffsetRect(rTable[1].left - pTable[0]->left, rTable[1].top - pTable[0]->top);
									break;
								}
								for (nRow = 0, nRows = pTable[0]->GetRows(); nRow < nRows; nRow++)
								{
									if ((pCell[1] = pTable[0]->FindCell(nRow, pTable[0]->GetColumns() - 1)) && pCell[1]->GetPosition().right != rTable[1].right)
									{
										pCell[1]->SetPosition(CRect(pCell[1]->GetPosition().left, pCell[1]->GetPosition().top, rTable[1].right, pCell[1]->GetPosition().bottom));
										pCell[1]->SetInnerPosition(CRect(pCell[1]->GetInnerPosition().left, pCell[1]->GetInnerPosition().top, pCell[0]->GetInnerPosition().right, pCell[1]->GetInnerPosition().bottom));
									}
								}
								for (nCol = 0, nCols = pTable[0]->GetColumns(); nCol < nCols; nCol++)
								{
									if ((pCell[1] = pTable[0]->FindCell(pTable[0]->GetRows() - 1, nCol)) && pCell[1]->GetPosition().bottom != rTable[1].bottom)
									{
										pCell[1]->SetPosition(CRect(pCell[1]->GetPosition().left, pCell[1]->GetPosition().top, pCell[1]->GetPosition().right, rTable[1].bottom));
										pCell[1]->SetInnerPosition(CRect(pCell[1]->GetInnerPosition().left, pCell[1]->GetInnerPosition().top, pCell[1]->GetInnerPosition().right, pCell[0]->GetInnerPosition().bottom));
									}
								}
								pTable[0]->SetRect(pTable[0]->GetCellsBounds().TopLeft(), pTable[0]->GetCellsBounds().BottomRight());
							}
						}
					}
					else if (rTable[0].right > 0 && rTable[0].bottom > 0 && !rTable[0].left  &&  !rTable[0].top)
					{
						if ((pCell[0] = pTable[1]->FindCell(rTable[0].right, rTable[0].bottom - 1)))
						{
							if ((pCell[0]->GetFormat() & TAS_TYPE_SUBTABLE) == TAS_TYPE_SUBTABLE)
							{
								pCell[0]->GetBorder(TAS_BORDER_LEFT, nSize[0], nStyle[0], nColor[0]);
								pCell[0]->GetBorder(TAS_BORDER_TOP, nSize[1], nStyle[1], nColor[1]);
								pCell[0]->GetBorder(TAS_BORDER_RIGHT, nSize[2], nStyle[2], nColor[2]);
								pCell[0]->GetBorder(TAS_BORDER_BOTTOM, nSize[3], nStyle[3], nColor[3]);
								pTable[1]->SetColumnWidth(pCell[0]->x, (pTable[0]->IsVisible()) ? max(CalcDefaultTableWidth(pTable[0]), pCell[0]->GetPosition().Width()) : pCell[0]->GetPosition().Width());
								pTable[1]->SetRowHeight(pCell[0]->y, (pTable[0]->IsVisible()) ? max(CalcDefaultTableHeight(pTable[0]), pCell[0]->GetPosition().Height()) : CalcDefaultCellHeight(pCell[0], pCell[0]->GetInnerPosition().Width()));
								for (pTable[1]->SetRect(pTable[1]->GetCellsBounds().TopLeft(), pTable[1]->GetCellsBounds().BottomRight()), rTable[1].SetRect(pCell[0]->GetPosition().left + (nSize[0] - 1) / 2 + 1, pCell[0]->GetPosition().top + (nSize[1] - 1) / 2 + 1, pCell[0]->GetPosition().right - nSize[2] / 2, pCell[0]->GetPosition().bottom - nSize[3] / 2); rTable[1].TopLeft() != pTable[0]->TopLeft(); )
								{
									pTable[0]->OffsetCells(rTable[1].TopLeft() - pTable[0]->TopLeft());
									pTable[0]->OffsetRect(rTable[1].left - pTable[0]->left, rTable[1].top - pTable[0]->top);
									break;
								}
								for (nRow = 0, nRows = pTable[0]->GetRows(); nRow < nRows; nRow++)
								{
									if ((pCell[1] = pTable[0]->FindCell(nRow, pTable[0]->GetColumns() - 1)) && pCell[1]->GetPosition().right != rTable[1].right)
									{
										pCell[1]->SetPosition(CRect(pCell[1]->GetPosition().left, pCell[1]->GetPosition().top, rTable[1].right, pCell[1]->GetPosition().bottom));
										pCell[1]->SetInnerPosition(CRect(pCell[1]->GetInnerPosition().left, pCell[1]->GetInnerPosition().top, pCell[0]->GetInnerPosition().right, pCell[1]->GetInnerPosition().bottom));
									}
								}
								for (nCol = 0, nCols = pTable[0]->GetColumns(); nCol < nCols; nCol++)
								{
									if ((pCell[1] = pTable[0]->FindCell(pTable[0]->GetRows() - 1, nCol)) && pCell[1]->GetPosition().bottom != rTable[1].bottom)
									{
										pCell[1]->SetPosition(CRect(pCell[1]->GetPosition().left, pCell[1]->GetPosition().top, pCell[1]->GetPosition().right, rTable[1].bottom));
										pCell[1]->SetInnerPosition(CRect(pCell[1]->GetInnerPosition().left, pCell[1]->GetInnerPosition().top, pCell[1]->GetInnerPosition().right, pCell[0]->GetInnerPosition().bottom));
									}
								}
								pTable[0]->SetRect(pTable[0]->GetCellsBounds().TopLeft(), pTable[0]->GetCellsBounds().BottomRight());
							}
						}
					}
				}
			}
		}
	}
	for (nTable = 0, nTables = (INT)m_szTables.GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable[0] = pTables->GetAt(pTables->Find(m_szTables.GetAt(nTable)))) && pTable[0]->GetType() == TAS_TABLE_NORMAL)
		{
			RepositionTables(pTables, pTable[0]->GetName(), szTables);
			break;
		}
	}
	for (nTable = 0, rTable[0].SetRectEmpty(), rTable[1].SetRectEmpty(); nTable < nTables; nTable++)
	{
		if ((pTable[0] = pTables->GetAt(nTable)))
		{
			rTable[1].UnionRect(pTable[0], rTable[0]);
			rTable[0] = rTable[1];
		}
	}
	for (nTable = 0, nTables = (rTable[0].left < 0 || rTable[0].top < 0) ? nTables : 0, rTable[0].OffsetRect(-DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN, -DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN); nTable < nTables; nTable++)
	{
		if ((pTable[0] = pTables->GetAt(nTable)) != (CTableViewObject *)NULL)
		{
			pTable[0]->OffsetCells(-rTable[0].left, -rTable[0].top);
			pTable[0]->OffsetRect(-rTable[0].TopLeft());
		}
	}
	if ((pCell[0] = GetActiveCell())) pCell[0]->ResizeControl();
	RecalcScrollSizes();
	DrawTables();
}
VOID CDisplayTableView::RepositionTables()
{
	RepositionTables(m_pTables);
}

VOID CDisplayTableView::ArrangeTables()
{
	GetDatabase()->ArrangeTables(this);
}
VOID CDisplayTableView::ArrangeTables(UINT nControlID)
{
	GetDatabase()->ArrangeTables(this, nControlID);
}

BOOL CDisplayTableView::ActivateTable()
{
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_szTables.GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(m_pTables->Find(m_szTables.GetAt(nTable)))) && pTable->GetType() == TAS_TABLE_NORMAL  &&  pTable->IsVisible())
		{
			if (ActivateTable(pTable)) break;
			continue;
		}
	}
	return((nTable < nTables) ? TRUE : FALSE);
}
BOOL CDisplayTableView::ActivateTable(CTableViewObject *pTable, BOOL bPrevious)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	CTableViewCell  *pCell;
	CTableViewObject  *pSubTable;

	if (pTable->IsVisible())
	{
		for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
		{
			m_pTables->GetAt(nTable)->SetSelCell();
			continue;
		}
		for (nRow = (bPrevious) ? (pTable->GetRows() - 1) : 0, nRows = pTable->GetRows(); nRow >= 0 && nRow < nRows; nRow = (!bPrevious) ? (nRow + 1) : (nRow - 1))
		{
			for (nCol = (bPrevious) ? (pTable->GetColumns() - 1) : 0, nCols = pTable->GetColumns(); nCol >= 0 && nCol < nCols; nCol = (!bPrevious) ? (nCol + 1) : (nCol - 1))
			{
				if ((pCell = pTable->FindCell(nRow, nCol)))
				{
					if (pCell->GetControl() != (CWnd *)NULL)
					{
						for (; pTable->GetType() == TAS_TABLE_LIST; )
						{
							pTable->SetSelRow(pCell->y);
							break;
						}
						SetActiveCell(pTable, pCell);
						break;
					}
					if (pCell->GetFormat() & TAS_TYPE_SUBTABLE)
					{
						if ((pSubTable = m_pTables->GetAt(m_pTables->Find(pCell->GetSubTable()))))
						{
							if (ActivateTable(pSubTable, bPrevious)) break;
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

BOOL CDisplayTableView::ActivateNextTable(BOOL bPrevious)
{
	INT  nTable[2];
	INT  nTables[2];
	CTableViewCell  *pCell;
	CTableViewObject  *pTable[2];

	if ((pCell = GetActiveCell(pTable[0])))
	{
		for (nTable[0] = 0, nTables[0] = (INT)m_szTables.GetSize(); nTable[0] < nTables[0]; nTable[0]++)
		{
			if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(m_szTables.GetAt(nTable[0])))) && pTable[0]->GetName() == pTable[1]->GetName())
			{
				for (nTable[1] = (!bPrevious) ? (nTable[0] + 1) : (nTable[0] - 1), nTable[1] = (nTable[1] < 0) ? (nTables[0] - 1) : nTable[1], nTable[1] = (nTable[1] < nTables[0]) ? nTable[1] : 0, nTables[1] = 0; nTables[0] > nTables[1]; nTable[1] = (!bPrevious) ? (nTable[1] + 1) : (nTable[1] - 1), nTable[1] = (nTable[1] < 0) ? (nTables[0] - 1) : nTable[1], nTable[1] = (nTable[1] < nTables[0]) ? nTable[1] : 0, nTables[1]++)
				{
					if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(m_szTables.GetAt(nTable[1])))) && pTable[1]->IsVisible())
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

BOOL CDisplayTableView::ActivateNextTableCell(BOOL bPrevious)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
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
				if ((pCell[1] = pTable[0]->FindCell(nRow, nCol)) && pCell[1]->IsEnabled() && pCell[1]->GetControl())
				{
					for (; pTable[0]->GetType() == TAS_TABLE_LIST; )
					{
						pTable[0]->SetSelRow(pCell[1]->y);
						break;
					}
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
				if ((pCell[1] = pTable[0]->FindCell(nRow, nCol)) && pCell[1]->IsEnabled() && pCell[1]->GetControl())
				{
					for (; pTable[0]->GetType() == TAS_TABLE_LIST; )
					{
						pTable[0]->SetSelRow(pCell[1]->y);
						break;
					}
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
	return FALSE;
}

VOID CDisplayTableView::RecalcTable(CTableViewObject *pTable, BOOL bWidth, BOOL bAdjust, BOOL bRedraw)
{
	CUIntArray  nWidths;

	if (!bWidth || GetTableLayout(pTable->GetName(), nWidths))
	{
		RecalcTable(m_pTables, pTable, nWidths, bAdjust, bRedraw);
		return;
	}
}
VOID CDisplayTableView::RecalcTable(CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw)
{
	RecalcTable(m_pTables, pTable, nWidths, bAdjust, bRedraw);
}
VOID CDisplayTableView::RecalcTable(CONST CTableViewObjects *pTables, CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nCell;
	INT  nCells;
	INT  nIndex;
	INT  nCount;
	INT  nMargin;
	INT  nExtent;
	INT  nSize[2];
	INT  nStyle[2];
	INT  nWidth[2];
	INT  nHeight[3];
	INT  nOffset[2];
	CRect  rCell[2];
	CRect  rTable;
	CString  szTable;
	COLORREF  nColor[2];
	COLORREF  nTitleRowColor;
	COLORREF  nFirstRowColor;
	COLORREF  nFirstColumnColor;
	COLORREF  nTitleFontColor;
	COLORREF  nItemsFontColor;
	CPtrArray  pCells;
	CUIntArray  nColumns;
	CTableViewCell  *pCell;
	CTableViewObject  *pSubTable;

	if ((pSubTable = (GetTablePosition(pTable->GetName(), szTable, rTable) && (!nWidths.GetSize() || GetTableLayout(szTable, nColumns)) && IsSubTable(pTable) && bAdjust) ? pTables->GetAt(pTables->Find(szTable)) : (CTableViewObject *)NULL))
	{
		RecalcTable(pTables, pSubTable, nColumns, bAdjust, bRedraw);
		return;
	}
	if (GetTableOutline(pTable->GetName(), nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nSize[0], nStyle[0], nColor[0], nSize[1], nStyle[1], nColor[1]))
	{
		for (pTable->SetOuterBorder(nSize[0], nStyle[0], nColor[0]), pTable->SetInnerBorder(nSize[1], nStyle[1], nColor[1]); pTable->GetType() == TAS_TABLE_NORMAL; )
		{
			pTable->SetRowBackgroundColor(1, nFirstRowColor);
			break;
		}
		for (; pTable->GetType() == TAS_TABLE_LIST; )
		{
			pTable->SetColumnBackgroundColor(0, nFirstColumnColor);
			break;
		}
		for (; pTable->HasTitle(); )
		{
			pTable->SetRowBackgroundColor(0, nTitleRowColor);
			break;
		}
		for (nCol = 0, nCols = pTable->GetColumns(), nMargin = CalcDefaultTableMargin(pTable), nExtent = 0; nCol < nCols; nCol++)
		{
			for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
			{
				if ((pCell = pTable->FindCell(nRow, nCol)))
				{
					if (pCell->GetFormat() & TAS_TYPE_SUBTABLE)
					{
						if ((pSubTable = pTables->GetAt(pTables->Find(pCell->GetSubTable()))))
						{
							for (nColumns.RemoveAll(); GetTableLayout(pSubTable->GetName(), nColumns); )
							{
								RecalcTable(pTables, pSubTable, nColumns, FALSE, FALSE);
								break;
							}
						}
					}
				}
			}
			for (nRow = 0, nRows = (nCol < nWidths.GetSize()) ? pTable->GetRows() : -1, nWidth[0] = 0; nRow < nRows; nRow++)
			{
				if ((pCell = pTable->FindCell(nRow, nCol)))
				{
					pCell->SetInnerPosition(CRect(0, 0, 0, 0));
					for (rCell[0] = CalcTableCellExtent(pCell); !nCol || nCol == nCols - 1; )
					{
						nWidth[1] = max(nSize[0] + 2 * nMargin + rCell[0].Width(), nWidth[0]);
						nWidth[1] = CalcDefaultCellWidth(pCell, nWidths.GetAt(nCol), (pTable->GetType() != TAS_TABLE_NORMAL || (pCell->GetFormat() & TAS_TYPE_SUBTABLE) || !nCol) ? nWidth[1] : 0);
						nWidth[0] = max(nWidth[0], nWidth[1]);
						break;
					}
					if (nCol > 0 && nCol < nCols - 1)
					{
						nWidth[1] = max(nSize[1] + 3 * nMargin + rCell[0].Width(), nWidth[0]);
						nWidth[1] = CalcDefaultCellWidth(pCell, nWidths.GetAt(nCol), nWidth[1]);
						nWidth[0] = max(nWidth[0], nWidth[1]);
					}
				}
			}
			if (nRows >= 0)
			{
				pTable->SetColumnWidth(nCol, nWidth[0]);
				continue;
			}
		}
		for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
		{
			for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
				{
					for (rCell[0] = pCell->GetPosition(); !nCol || nCol == nCols - 1; )
					{
						rCell[0].SetRect((!nCol) ? (rCell[0].left + nSize[0] + nMargin) : (rCell[0].left + nMargin), rCell[0].top + nSize[1], (nCol > 0) ? (rCell[0].right - nSize[0] - nMargin) : (rCell[0].right - nMargin), (nRow == nRows - 1) ? (rCell[0].bottom - nSize[0] / 2 - 1) : (rCell[0].bottom - nSize[1] / 2 - 1));
						pCell->SetInnerPosition(rCell[0]);
						break;
					}
					if (nCol > 0 && nCol < nCols - 1)
					{
						rCell[0].DeflateRect(nMargin, nSize[1], nMargin, (nRow == nRows - 1) ? (nSize[0] / 2 + 1) : (nSize[1] / 2 + 1));
						pCell->SetInnerPosition(rCell[0]);
					}
				}
			}
		}
		for (nCell = 0, nCells = pTable->GetCellCount(), nOffset[0] = 0; nCell < nCells; nCell++)
		{
			if ((pCell = pTable->FindCell(nCell)))
			{
				for (; pCell->x == 0; )
				{
					pCells.RemoveAll();
					break;
				}
				for (nHeight[0] = CalcDefaultCellHeight(m_pTables, pCell, pCell->GetInnerPosition().Width()), nHeight[1] = (pCell->x > 0) ? max(nHeight[0], nHeight[1]) : nHeight[0], nHeight[2] = (pCell->x > 0) ? max(pCell->GetPosition().Height(), nHeight[2]) : pCell->GetPosition().Height(), nHeight[0] = (!nWidths.GetSize() && !bAdjust) ? max(nHeight[1], nHeight[2]) : nHeight[1], pCells.Add(pCell); pCell->x == pTable->GetColumns() - 1; )
				{
					for (nIndex = 0, nCount = (INT)pCells.GetSize(); nIndex < nCount; nIndex++)
					{
						if ((pCell = (CTableViewCell *)pCells.GetAt(nIndex)) != (CTableViewCell *)NULL)
						{
							for (rCell[0] = pCell->GetPosition(), rCell[0].OffsetRect(0, nOffset[0]), rCell[0].InflateRect(0, 0, 0, (nOffset[1] = nHeight[0] - rCell[0].Height())), pCell->SetPosition(rCell[0]); pCell->HasInnerPosition(); )
							{
								rCell[1] = pCell->GetInnerPosition();
								rCell[1].OffsetRect(0, nOffset[0]);
								rCell[1].InflateRect(0, 0, 0, nOffset[1]);
								pCell->SetInnerPosition(rCell[1]);
								break;
							}
						}
					}
					nOffset[0] += nOffset[1];
					break;
				}
			}
		}
		for (pTable->OffsetCells((!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN - pTable->GetCellsBounds().left) : (-pTable->GetCellsBounds().left), (!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN - pTable->GetCellsBounds().top) : (-pTable->GetCellsBounds().top)), rTable = pTable->GetCellsBounds(), rTable.InflateRect(rTable.left, rTable.top, (pTable->GetType() == TAS_TABLE_LIST && !IsSubTable(pTable)) ? DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN : rTable.left, (pTable->GetType() == TAS_TABLE_LIST && !IsSubTable(pTable)) ? DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN : rTable.top), pTable->SetRect(rTable.left, rTable.top, rTable.right, rTable.bottom); bRedraw; )
		{
			DrawTables();
			break;
		}
	}
}

VOID CDisplayTableView::RecalcTableRow(CTableViewObject *pTable, INT nRow, BOOL bAdjust)
{
	RecalcTableRow(m_pTables, pTable, nRow, bAdjust);
}
VOID CDisplayTableView::RecalcTableRow(CONST CTableViewObjects *pTables, CTableViewObject *pTable, INT nRow, BOOL bAdjust)
{
	INT  nCol;
	INT  nCols;
	INT  nHeight[3];
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
	{
		if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
		{
			for (nHeight[0] = CalcDefaultCellHeight(pTables, pCell, pCell->GetInnerPosition().Width()), nHeight[1] = (nCol > 0) ? max(nHeight[0], nHeight[1]) : nHeight[0], nHeight[2] = (nCol > 0) ? max(pCell->GetPosition().Height(), nHeight[2]) : pCell->GetPosition().Height(); nCol == nCols - 1; )
			{
				pTable->SetRowHeight(nRow, (!bAdjust) ? max(nHeight[1], nHeight[2]) : nHeight[1]);
				break;
			}
		}
	}
}

VOID CDisplayTableView::UpdateTableContents(CTableViewObject *pTable, CONST CStringArray &szContents)
{
	UpdateTableContents(m_pTables, pTable, GetName(), szContents);
}
VOID CDisplayTableView::UpdateTableContents(CONST CTableViewObjects *pTables, CTableViewObject *pTable, LPCTSTR pszTable, CONST CStringArray &szContents)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nCell;
	INT  nCells;
	INT  nIndex;
	INT  nSize[2];
	INT  nStyle[2];
	BOOL  bWidth;
	BOOL  bResize;
	BOOL  bVisible;
	CString  szItem;
	COLORREF  nColor[2];
	COLORREF  nTitleRowColor;
	COLORREF  nFirstRowColor;
	COLORREF  nFirstColumnColor;
	COLORREF  nTitleFontColor;
	COLORREF  nItemsFontColor;
	CTableViewCell  *pCell;
	CStringArray  szColumns;
	CStringArray  szDataTypes;
	CStringArray  szDescriptions;
	CUIntArray  nFormats;
	CUIntArray  nWidths;
	CUIntArray  nIDs;

	for (BeginTableUpdate(); GetTableLayout(pTable->GetName(), nWidths) && GetTableContents(pTable->GetName(), GetName(), 0, szColumns, szDescriptions, szDataTypes, nFormats, nIDs, bResize, bVisible) && GetTableOutline(pTable->GetName(), nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nSize[0], nStyle[0], nColor[0], nSize[1], nStyle[1], nColor[1]); )
	{
		for (bWidth = FALSE; pTable->GetType() == TAS_TABLE_LIST; )
		{
			for (nRow = pTable->GetRows(), nRows = (pTable->HasTitle()) ? (INT)(szContents.GetSize() + 1) : (INT)szContents.GetSize(), bWidth = (nRow != nRows); nRow < nRows; nRow++)
			{
				InsertTableRow(pTable, nRow);
				continue;
			}
			for (nRow = (pTable->HasTitle()) ? (INT)(szContents.GetSize() + 1) : (INT)szContents.GetSize(), nRows = pTable->GetRows(); nRow < nRows; nRow++)
			{
				DeleteTableRow(pTable, pTable->GetRows() - 1);
				nRows--;
				nRow--;
			}
			for (nCol = pTable->GetColumns(), nCols = (INT)nWidths.GetSize(), bWidth |= (nCol != nCols); nCol < nCols; nCol++)
			{
				InsertTableColumn(pTable, nCol);
				continue;
			}
			for (nCol = (INT)nWidths.GetSize(), nCols = pTable->GetColumns(); nCol < nCols; nCol++)
			{
				DeleteTableColumn(pTable, pTable->GetColumns() - 1);
				nCols--;
				nCol--;
			}
			break;
		}
		for (nRows = (pTable->HasTitle()) ? (INT)(szContents.GetSize() + 1) : (INT)szContents.GetSize(), nCell = (pTable->GetType() == TAS_TABLE_NORMAL) ? (pTable->GetColumns() - 1) : 0, nCell += (pTable->HasTitle() && nCell >= 0) ? pTable->GetColumns() : 0, nCells = nRows*(nCols = pTable->GetColumns()), nCells = (nCell >= 0) ? nCells : -1; nCell < nCells; nCell = (pTable->GetType() == TAS_TABLE_NORMAL) ? (nCell + nCols) : (nCell + 1))
		{
			if ((pCell = pTable->FindCell(nCell)) && ((pTable->GetType() == TAS_TABLE_LIST  &&  pCell->x > 0) || ExtractTextItems(((nIndex = (pTable->HasTitle()) ? (pCell->y - 1) : pCell->y) < szContents.GetSize()) ? szContents.GetAt(nIndex) : EMPTYSTRING, szColumns) >= 0))
			{
				if (pTable->GetType() == TAS_TABLE_NORMAL  &&  szColumns.GetSize() > 0)
				{
					for (szItem = szColumns.GetAt(0); pCell->GetText() != szItem; )
					{
						pCell->SetText(szItem, FALSE);
						break;
					}
					continue;
				}
				if (pTable->GetType() == TAS_TABLE_LIST  &&  pCell->x < szColumns.GetSize())
				{
					for (szItem = szColumns.GetAt(pCell->x); pCell->GetText() != szItem; )
					{
						pCell->SetText(szItem, FALSE);
						break;
					}
					continue;
				}
				pCell->SetText(EMPTYSTRING, FALSE);
				continue;
			}
			break;
		}
		if (pTable->GetType() == TAS_TABLE_LIST)
		{
			for (; (!pTable->HasTitle() && max(nRows, 1) < pTable->GetRows()) || (pTable->HasTitle() && max(nRows, 2) < pTable->GetRows()); )
			{
				pTable->RemoveRow(pTable->GetRows() - 1);
				continue;
			}
			for (nCol = 0, nCols = pTable->GetColumns(); !szContents.GetSize() && pTable->GetRows() > nRows && nCol < nCols; nCol++)
			{
				if ((pCell = pTable->FindCell(pTable->GetRows() - 1, nCol)))
				{
					pCell->SetText(EMPTYSTRING, FALSE);
					continue;
				}
			}
		}
		pTable->SetOuterBorder(nSize[0], nStyle[0], nColor[0]);
		pTable->SetInnerBorder(nSize[1], nStyle[1], nColor[1]);
		RecalcTable(pTables, pTable, nWidths, TRUE, FALSE);
		ProtectTableFieldData(pTable->GetName());
		break;
	}
	EndTableUpdate();
}

BOOL CDisplayTableView::EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem)
{
	CStringArray  szValues;
	CLongUIntArray  nValues;

	if ((pCell->GetFormat() & TAS_TYPE_COMBOLISTBOX) || (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX))
	{
		EnumTableFieldValues(pTable->GetName(), pszItem, szValues, nValues);
		return EnumTableCellValues(pTable, pCell, szValues, nValues);
	}
	return TRUE;
}
BOOL CDisplayTableView::EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CUIntArray &nValues)
{
	CLongUIntArray  lValues;

	return EnumTableCellValues(pTable, pCell, szValues, (lValues = nValues));
}
BOOL CDisplayTableView::EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CLongUIntArray &nValues)
{
	INT  nRow;
	INT  nItem;
	INT  nItems;
	INT  nTable;
	INT  nTables;
	BOOL  bValue;
	DWORD  dwSel;
	CString  szValue;
	CStringArray  szItems;
	CStringArray  szTables;
	CTableViewComboBoxListCtrl  *pComboListCtrl;
	CTableViewComboBoxEditCtrl  *pComboEditCtrl;

	if (pCell->GetFormat() & TAS_TYPE_COMBOLISTBOX)
	{
		if ((pComboListCtrl = (CTableViewComboBoxListCtrl *)pCell->GetControl()))
		{
			for (szValue = pCell->GetText(), bValue = pComboListCtrl->HasValue(szValue), pComboListCtrl->SetValues(szValues, nValues); IsWindow(pComboListCtrl->GetSafeHwnd()); )
			{
				for (nItem = 0, nItems = (INT)szValues.GetSize(), pComboListCtrl->ResetContent(); nItem < nItems; nItem++)
				{
					pComboListCtrl->SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValues.GetAt(nItem));
					continue;
				}
				break;
			}
			for (pCell->SetText(szValue, bValue); pCell->GetText() != szValue; )
			{
				for (nRow = pTable->GetSelRow(); pTable->SetSelRow(pCell->y); )
				{
					UpdateTableFieldData(pCell->GetControlID(), pCell->GetText());
					break;
				}
				for (nTable = 0, nTables = EnumTableUpdates(pCell->GetControlID(), szTables); nTable < nTables; nTable++)
				{
					if (GetTableUpdateContents(szTables.GetAt(nTable), pCell->GetControlID(), pCell->GetText(), szValue, szItems))
					{
						UpdateTableContents(m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable))), szItems);
						continue;
					}
				}
				for (pTable->SetSelRow(nRow); nTables > 0; )
				{
					ClearUndo();
					break;
				}
				break;
			}
			return TRUE;
		}
		return FALSE;
	}
	if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
	{
		if ((pComboEditCtrl = (CTableViewComboBoxEditCtrl *)pCell->GetControl()))
		{
			for (szValue = pCell->GetText(), bValue = pComboEditCtrl->HasValue(szValue), pComboEditCtrl->SetValues(szValues, nValues); IsWindow(pComboEditCtrl->GetSafeHwnd()); )
			{
				for (nItem = 0, nItems = (INT)szValues.GetSize(), dwSel = pComboEditCtrl->GetEditSel(), pComboEditCtrl->ResetContent(); nItem < nItems; nItem++)
				{
					pComboEditCtrl->SendMessage(CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValues.GetAt(nItem));
					continue;
				}
				break;
			}
			for (pCell->SetText(szValue, bValue); pCell->GetText() != szValue; )
			{
				for (nRow = pTable->GetSelRow(); pTable->SetSelRow(pCell->y); )
				{
					UpdateTableFieldData(pCell->GetControlID(), pCell->GetText());
					break;
				}
				for (nTable = 0, nTables = EnumTableUpdates(pCell->GetControlID(), szTables); nTable < nTables; nTable++)
				{
					if (GetTableUpdateContents(szTables.GetAt(nTable), pCell->GetControlID(), pCell->GetText(), szValue, szItems))
					{
						UpdateTableContents(m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable))), szItems);
						continue;
					}
				}
				for (pTable->SetSelRow(nRow); nTables > 0; )
				{
					ClearUndo();
					break;
				}
				break;
			}
			for (; IsWindow(pComboEditCtrl->GetSafeHwnd()); )
			{
				pComboEditCtrl->SetEditSel(LOWORD(dwSel), HIWORD(dwSel));
				break;
			}
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CDisplayTableView::LimitTableCellValues(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem)
{
	INT  nLow;
	INT  nHigh;
	UINT  uLow;
	UINT  uHigh;
	double  fLow;
	double  fHigh;
	CTableViewSpinCtrl  *pSpinCtrl;
	CTableViewDecNumberEditCtrl  *pDecNumberEditCtrl;
	CTableViewRawNumberEditCtrl  *pRawNumberEditCtrl;

	if (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT)
	{
		if ((pDecNumberEditCtrl = (CTableViewDecNumberEditCtrl *)pCell->GetControl()))
		{
			if (GetTableFieldLimits(pTable->GetName(), pszItem, nLow, nHigh))
			{
				pDecNumberEditCtrl->SetRange((LONGLONG)nLow, (LONGLONG)nHigh);
				return TRUE;
			}
			if (GetTableFieldLimits(pTable->GetName(), pszItem, uLow, uHigh))
			{
				pDecNumberEditCtrl->SetRange((ULONGLONG)uLow, (ULONGLONG)uHigh);
				return TRUE;
			}
			for (; GetTableFieldLimits(pTable->GetName(), pszItem, fLow, fHigh); )
			{
				pDecNumberEditCtrl->SetRange(fLow, fHigh);
				break;
			}
			return TRUE;
		}
		return FALSE;
	}
	if (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT)
	{
		if ((pRawNumberEditCtrl = (CTableViewRawNumberEditCtrl *)pCell->GetControl()))
		{
			if (GetTableFieldLimits(pTable->GetName(), pszItem, nLow, nHigh))
			{
				pRawNumberEditCtrl->SetRange((ULONGLONG)max(nLow, 0), (ULONGLONG)max(nHigh, 0));
				return TRUE;
			}
			if (GetTableFieldLimits(pTable->GetName(), pszItem, uLow, uHigh))
			{
				pRawNumberEditCtrl->SetRange(uLow, uHigh);
				return TRUE;
			}
			return TRUE;
		}
		return FALSE;
	}
	if (pCell->GetFormat() & TAS_TYPE_SPINBOX)
	{
		if ((pSpinCtrl = (CTableViewSpinCtrl *)pCell->GetControl()))
		{
			if (GetTableFieldLimits(pTable->GetName(), pszItem, nLow, nHigh))
			{
				pSpinCtrl->SetRange(nLow, nHigh);
				return TRUE;
			}
			if (GetTableFieldLimits(pTable->GetName(), pszItem, uLow, uHigh))
			{
				if (uLow <= INT_MAX  &&  uHigh <= INT_MAX)
				{
					pSpinCtrl->SetRange(uLow, uHigh);
					return TRUE;
				}
			}
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

VOID CDisplayTableView::UpdateTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszValue)
{
	CDisplayTableViewUndoItem  cUndoItem[2];

	if (!IsUndoing() && !IsRedoing())
	{
		if (pCell->GetText() != pszValue)
		{
			ConvertUndoItem(pTable->GetName(), &cUndoItem[0]);
			ConvertUndoItem(pTable->GetName(), &cUndoItem[1]);
			cUndoItem[0].SetCell(pTable->GetName(), CPoint(pCell->x, pCell->y));
			cUndoItem[1].SetCell(pTable->GetName(), CPoint(pCell->x, pCell->y));
			cUndoItem[0].SetText(pTable->GetCellText(pCell->y, pCell->x));
			cUndoItem[1].SetText(pszValue);
			cUndoItem[0].SetSel(0, cUndoItem[0].GetText().GetLength());
			cUndoItem[1].SetSel(0, cUndoItem[1].GetText().GetLength());
			cUndoItem[0].AllowSelection(FALSE);
			cUndoItem[1].AllowSelection(FALSE);
			cUndoItem[0].Collect(FALSE);
			cUndoItem[1].Collect(TRUE);
			m_cUndoList.Add(&cUndoItem[0]);
			m_cUndoList.Add(&cUndoItem[1]);
			pCell->SetText(pszValue);
		}
	}
}

VOID CDisplayTableView::EnableTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszDefault, BOOL bEnable)
{
	CDisplayTableViewUndoItem  cUndoItem[2];

	if (!bEnable)
	{
		if ((pCell->GetFormat() & (TAS_TYPE_TEXT & TAS_TYPE_SUBTABLE)) == 0)
		{
			if (IsUndoing() || IsRedoing())
			{
				pCell->Enable(FALSE);
				return;
			}
			ConvertUndoItem(pTable->GetName(), &cUndoItem[0]);
			ConvertUndoItem(pTable->GetName(), &cUndoItem[1]);
			cUndoItem[0].SetCell(pTable->GetName(), CPoint(pCell->x, pCell->y));
			cUndoItem[1].SetCell(pTable->GetName(), CPoint(pCell->x, pCell->y));
			cUndoItem[0].SetText(pTable->GetCellText(pCell->y, pCell->x));
			cUndoItem[1].SetText((pCell->GetFormat() & (TAS_TYPE_EDIT | TAS_TYPE_MULTILINEEDIT | TAS_TYPE_DECNUMBEREDIT | TAS_TYPE_RAWNUMBEREDIT | TAS_TYPE_DPLEDIT | TAS_TYPE_MDLEDIT | TAS_TYPE_TPLEDIT | TAS_TYPE_COMBOLISTBOX | TAS_TYPE_COMBOEDITBOX)) ? pszDefault : EMPTYSTRING);
			cUndoItem[0].SetSel(0, cUndoItem[0].GetText().GetLength());
			cUndoItem[1].SetSel(0, cUndoItem[1].GetText().GetLength());
			cUndoItem[0].AllowSelection(FALSE);
			cUndoItem[1].AllowSelection(FALSE);
			cUndoItem[0].Collect(FALSE);
			cUndoItem[1].Collect(TRUE);
			m_cUndoList.Add(&cUndoItem[0]);
			m_cUndoList.Add(&cUndoItem[1]);
			pCell->SetText(cUndoItem[1].GetText());
			pCell->Enable(FALSE);
		}
		return;
	}
	pCell->Enable();
}

BOOL CDisplayTableView::IsTableRowEmpty(CONST CTableViewObject *pTable, INT nRow) CONST
{
	INT  nCol;
	INT  nCols;
	INT  nSubRow;
	INT  nSubRows;
	CTableViewCell  *pCell;
	CTableViewObject  *pSubTable;

	for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
	{
		if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
		{
			if ((pCell->GetFormat() & TAS_TYPE_SUBTABLE) == TAS_TYPE_SUBTABLE)
			{
				if ((pSubTable = FindTable(pCell->GetSubTable())) != (CTableViewObject *)NULL)
				{
					for (nSubRow = 0, nSubRows = pSubTable->GetRows(); nSubRow < nSubRows; nSubRow++)
					{
						if (!IsTableRowEmpty(pSubTable, nSubRow)) break;
						continue;
					}
					if (nSubRow < nSubRows) break;
				}
				continue;
			}
			if ((pCell->GetFormat() & TAS_TYPE_TEXT) != TAS_TYPE_TEXT  &&  !pCell->GetText().IsEmpty()) break;
		}
	}
	return((nCol == nCols) ? TRUE : FALSE);
}

BOOL CDisplayTableView::IsTableRowFull(CONST CTableViewObject *pTable, INT nRow) CONST
{
	INT  nCol;
	INT  nCols;
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
	{
		if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
		{
			if ((pCell->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE && (pCell->GetFormat() & TAS_TYPE_TEXT) != TAS_TYPE_TEXT  &&  pCell->GetText().IsEmpty()) break;
			continue;
		}
	}
	return((nCol == nCols) ? TRUE : FALSE);
}

BOOL CDisplayTableView::IsSubTable(CONST CTableViewObject *pTable) CONST
{
	CRect  rTable;
	CString  szTable;

	return((GetTablePosition(pTable->GetName(), szTable, rTable) && !szTable.IsEmpty() && (rTable.left*rTable.top != 0 || rTable.right*rTable.bottom != 0)) ? TRUE : FALSE);
}

VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CANDLayout *pLayout, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CGRDLayout *pLayout, INT nIndex, BOOL bDelete)
{
	return;
}
VOID CDisplayTableView::UpdateTableForms(CONST CPODLayout *pLayout, INT nIndex, BOOL bDelete)
{
	return;
}

VOID CDisplayTableView::UpdateTables(CONST CDatabaseTMPackets &pDatabaseTMPackets)
{
	GetDatabase()->UpdateTables(this, pDatabaseTMPackets);
}
VOID CDisplayTableView::UpdateTables(CONST CDatabaseTCFunctions &pDatabaseTCFunctions)
{
	GetDatabase()->UpdateTables(this, pDatabaseTCFunctions);
}
VOID CDisplayTableView::UpdateTables(CONST CDatabaseTCSequences &pDatabaseTCSequences)
{
	GetDatabase()->UpdateTables(this, pDatabaseTCSequences);
}
VOID CDisplayTableView::UpdateTables(CONST CDatabaseOBProcessors &pDatabaseOBProcessors)
{
	GetDatabase()->UpdateTables(this, pDatabaseOBProcessors);
}
VOID CDisplayTableView::UpdateTables(CONST CDatabaseTMParameters &pDatabaseTMParameters)
{
	GetDatabase()->UpdateTables(this, pDatabaseTMParameters);
}
VOID CDisplayTableView::UpdateTables(CONST CDatabaseTCParameters &pDatabaseTCParameters)
{
	GetDatabase()->UpdateTables(this, pDatabaseTCParameters);
}
VOID CDisplayTableView::UpdateTables(CONST CANDLayouts &pANDLayouts)
{
	GetDatabase()->UpdateTables(this, pANDLayouts);
}
VOID CDisplayTableView::UpdateTables(CONST CGRDLayouts &pGRDLayouts)
{
	GetDatabase()->UpdateTables(this, pGRDLayouts);
}
VOID CDisplayTableView::UpdateTables(CONST CPODLayouts &pPODLayouts)
{
	GetDatabase()->UpdateTables(this, pPODLayouts);
}
BOOL CDisplayTableView::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	CString  szName;

	for (szName = GetName(); GetDatabase()->UpdateTables(this, nComponent, pszName, bDelete); )
	{
		if (DATABASECOMPONENTFROMCODE(nComponent) == GetComponent() && DATABASESUBCOMPONENTFROMCODE(nComponent) == DATABASE_SUBCOMPONENT_NONE  &&  !szName.Compare(pszName))
		{
			for (ClearUndo(); bDelete; )
			{
				DoResetTables();
				break;
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}
BOOL CDisplayTableView::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	return GetDatabase()->UpdateTables(this, nComponent, nID, bDelete);
}
VOID CDisplayTableView::UpdateTables(ULONGLONG nComponent)
{
	GetDatabase()->UpdateTables(this, nComponent);
}
VOID CDisplayTableView::UpdateTables()
{
	UpdateTables(GetComponent());
}

BOOL CDisplayTableView::EnableTablesAlignment(BOOL bEnable, BOOL bRealign)
{
	BOOL  bAlignment;

	bAlignment = m_bPrint[0];
	m_bPrint[1] = bRealign;
	m_bPrint[0] = bEnable;
	return bAlignment;
}
BOOL CDisplayTableView::EnableTablesAlignment(BOOL bEnable)
{
	return EnableTablesAlignment(bEnable, m_bPrint[1]);
}

VOID CDisplayTableView::DrawTables()
{
	CDC  *pDC;

	if ((pDC = (IsWindow(GetSafeHwnd()) && !m_cUndoList.IsCollecting() && !IsUndoing() && !IsRedoing() && !m_bImage) ? GetDC() : (CDC *)NULL))
	{
		pDC->SetViewportOrg(-GetScrollPosition());
		DrawTables(pDC);
		ReleaseDC(pDC);
	}
}
VOID CDisplayTableView::DrawTables(CDC *pDC)
{
	CDC  cDC;
	CDC  *pcDC;
	CRect  rView;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;

	for (GetClientRect(rView); (pcDC = (m_bImage) ? GetDC() : (CDC *)NULL); )
	{
		if ((pOldBitmap = (cDC.CreateCompatibleDC(pDC)) ? cDC.SelectObject(&m_cImage) : (CBitmap *)NULL))
		{
			pcDC->BitBlt(0, 0, rView.Width(), rView.Height(), &cDC, 0, 0, SRCCOPY);
			cDC.SelectObject(pOldBitmap);
			cDC.DeleteDC();
			ReleaseDC(pcDC);
			return;
		}
		cDC.DeleteDC();
		ReleaseDC(pcDC);
		break;
	}
	if (cDC.CreateCompatibleDC(pDC))
	{
		if (cBitmap.CreateCompatibleBitmap(pDC, rView.Width(), rView.Height()))
		{
			if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
			{
				cDC.FillSolidRect(rView, GetSysColor(COLOR_WINDOW));
				cDC.SetViewportOrg(-GetScrollPosition());
				DrawTables(&cDC, m_pTables, FALSE);
				pDC->BitBlt(GetScrollPosition().x, GetScrollPosition().y, rView.Width(), rView.Height(), &cDC, GetScrollPosition().x, GetScrollPosition().y, SRCCOPY);
				cDC.SelectClipRgn((CRgn *)NULL);
				cDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cDC.DeleteDC();
	}
}
VOID CDisplayTableView::DrawTables(CDC *pDC, CONST CTableViewObjects *pTables, BOOL bPrinting)
{
	INT  nLine;
	INT  nLines;
	INT  nIndex;
	INT  nCount;
	INT  nTable;
	INT  nTables;
	BOOL  bTables;
	CPen  cLinePen;
	CPen  *pOldPen;
	CRgn  rgClip;
	CRect  rClip;
	CRect  rTable;
	CPoint  ptLine[2];
	CString  szTable[2];
	LOGBRUSH  sPenBrush;
	CUIntArray  nXPt[2];
	CUIntArray  nYPt[2];
	CStringArray  szTables;
	CTableViewCell  *pCell[2];
	CTableViewObject  *pTable[2];

	for (nTable = 0, nTables = (INT)pTables->GetSize(), bTables = EnableTablesAlignment(bPrinting); nTable < nTables; nTable++)
	{
		if ((pTable[0] = pTables->GetAt(nTable)) && pTable[0]->IsVisible())
		{
			szTables.Add(pTable[0]->GetName());
			DrawTable(pDC, pTable[0], bPrinting);
		}
	}
	for (nTable = 0, nTables = (INT)szTables.GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable[0] = pTables->GetAt(pTables->Find(szTables.GetAt(nTable)))))
		{
			rClip = pTable[0]->GetCellsBounds();
			pDC->ExcludeClipRect(rClip);
		}
	}
	for (nTable = 0, nTables = (INT)szTables.GetSize(); nTable < nTables; nTable++)
	{
		if (GetTablePosition((szTable[0] = szTables.GetAt(nTable)), szTable[1], rTable))
		{
			if ((pTable[0] = pTables->GetAt(pTables->Find(szTable[0]))))
			{
				if ((pTable[1] = pTables->GetAt(pTables->Find(szTable[1]))))
				{
					if (rTable.left > 0 && rTable.top == 0)
					{
						if ((pCell[0] = pTable[0]->FindCell(0, pTable[0]->GetColumns() - 1)))
						{
							if ((pCell[1] = pTable[1]->FindCell(rTable.left, 0)))
							{
								if (pCell[1]->GetPosition().CenterPoint().y <= pCell[0]->GetPosition().top || pCell[1]->GetPosition().CenterPoint().y >= pCell[0]->GetPosition().bottom)
								{
									nXPt[0].Add(pCell[1]->GetPosition().left);
									nXPt[1].Add(pCell[0]->GetPosition().right);
									nYPt[0].Add(pCell[1]->GetPosition().CenterPoint().y);
									nYPt[1].Add(pCell[0]->GetPosition().CenterPoint().y);
								}
							}
						}
					}
					if (rTable.top > 0 && !rTable.left)
					{
						if ((pCell[0] = pTable[0]->FindCell(pTable[0]->GetRows() - 1, 0)))
						{
							if ((pCell[1] = pTable[1]->FindCell(0, rTable.top - 1)))
							{
								if (pCell[1]->GetPosition().CenterPoint().x <= pCell[0]->GetPosition().left || pCell[1]->GetPosition().CenterPoint().x >= pCell[0]->GetPosition().right)
								{
									nXPt[0].Add(pCell[1]->GetPosition().CenterPoint().x);
									nXPt[1].Add(pCell[0]->GetPosition().CenterPoint().x);
									nYPt[0].Add(pCell[1]->GetPosition().top);
									nYPt[1].Add(pCell[0]->GetPosition().bottom);
								}
							}
						}
					}
					if (rTable.right > 0 && !rTable.bottom)
					{
						if ((pCell[0] = pTable[0]->FindCell(0, 0)))
						{
							if ((pCell[1] = pTable[1]->FindCell(rTable.right, pTable[1]->GetColumns() - 1)))
							{
								if (pCell[1]->GetPosition().CenterPoint().y <= pCell[0]->GetPosition().top || pCell[1]->GetPosition().CenterPoint().y >= pCell[0]->GetPosition().bottom)
								{
									nXPt[0].Add(pCell[1]->GetPosition().right);
									nXPt[1].Add(pCell[0]->GetPosition().left);
									nYPt[0].Add(pCell[1]->GetPosition().CenterPoint().y);
									nYPt[1].Add(pCell[0]->GetPosition().CenterPoint().y);
								}
							}
						}
					}
					if (rTable.bottom > 0 && !rTable.right)
					{
						if ((pCell[0] = pTable[0]->FindCell(0, 0)))
						{
							if ((pCell[1] = pTable[1]->FindCell(pTable[1]->GetRows() - 1, rTable.bottom - 1)))
							{
								if (pCell[1]->GetPosition().CenterPoint().x <= pCell[0]->GetPosition().left || pCell[1]->GetPosition().CenterPoint().x >= pCell[0]->GetPosition().right)
								{
									nXPt[0].Add(pCell[1]->GetPosition().CenterPoint().x);
									nXPt[1].Add(pCell[0]->GetPosition().CenterPoint().x);
									nYPt[0].Add(pCell[1]->GetPosition().bottom);
									nYPt[1].Add(pCell[0]->GetPosition().top);
								}
							}
						}
					}
				}
			}
		}
	}
	for (sPenBrush.lbStyle = PS_SOLID, sPenBrush.lbHatch = (ULONG_PTR)NULL, sPenBrush.lbColor = GetSysColor(COLOR_WINDOWTEXT); cLinePen.CreatePen(PS_SOLID | PS_GEOMETRIC | PS_ENDCAP_SQUARE, DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE, &sPenBrush); )
	{
		if ((pOldPen = (CPen *)pDC->SelectObject(&cLinePen)))
		{
			for (nTable = 0; nTable < nTables; nTable = nTable + 1)
			{
				if (GetTablePosition((szTable[0] = szTables.GetAt(nTable)), szTable[1], rTable))
				{
					if ((pTable[0] = pTables->GetAt(pTables->Find(szTable[0]))))
					{
						if ((pTable[1] = pTables->GetAt(pTables->Find(szTable[1]))))
						{
							if (rTable.left > 0 && rTable.top == 0)
							{
								if ((pCell[0] = pTable[0]->FindCell(0, pTable[0]->GetColumns() - 1)))
								{
									if ((pCell[1] = pTable[1]->FindCell(rTable.left, 0)) != (CTableViewCell *)NULL)
									{
										if (pCell[1]->GetPosition().CenterPoint().y <= pCell[0]->GetPosition().top || pCell[1]->GetPosition().CenterPoint().y >= pCell[0]->GetPosition().bottom)
										{
											for (nLine = 0, nLines = (INT)nXPt[0].GetSize(), ptLine[0].x = pCell[1]->GetPosition().left, ptLine[0].y = pCell[1]->GetPosition().CenterPoint().y, ptLine[1].x = pCell[0]->GetPosition().right, ptLine[1].y = pCell[0]->GetPosition().CenterPoint().y, nCount = 0; nLine < nLines; nLine++)
											{
												if (min(ptLine[0].x, ptLine[1].x) - DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE >(INT) max(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine)) || max(ptLine[0].x, ptLine[1].x) + DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE < (INT)min(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine))) continue;
												if (min(ptLine[0].y, ptLine[1].y) - DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE >(INT) max(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine)) || max(ptLine[0].y, ptLine[1].y) + DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE < (INT)min(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine))) continue;
												if (ptLine[0].x == nXPt[0].GetAt(nLine) && ptLine[0].y == nYPt[0].GetAt(nLine) && nIndex > 0) continue;
												nIndex = (min(ptLine[0].y, ptLine[1].y) <= (INT)min(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine))) ? (nIndex + 1) : nIndex;
												nCount++;
											}
											pDC->MoveTo(ptLine[0]);
											pDC->LineTo(ptLine[0].x - ((ptLine[0].x - ptLine[1].x)*nIndex) / (nCount + 1), ptLine[0].y);
											pDC->LineTo(ptLine[0].x - ((ptLine[0].x - ptLine[1].x)*nIndex) / (nCount + 1), ptLine[1].y);
											pDC->LineTo(ptLine[1]);
										}
										else
										{
											pDC->MoveTo(pCell[1]->GetPosition().left, pCell[1]->GetPosition().CenterPoint().y);
											pDC->LineTo(pCell[0]->GetPosition().right, pCell[1]->GetPosition().CenterPoint().y);
										}
									}
								}
							}
							if (rTable.top > 0 && !rTable.left)
							{
								if ((pCell[0] = pTable[0]->FindCell(pTable[0]->GetRows() - 1, 0)))
								{
									if ((pCell[1] = pTable[1]->FindCell(0, rTable.top - 1)) != (CTableViewCell *)NULL)
									{
										if (pCell[1]->GetPosition().CenterPoint().x <= pCell[0]->GetPosition().left || pCell[1]->GetPosition().CenterPoint().x >= pCell[0]->GetPosition().right)
										{
											for (nLine = 0, nLines = (INT)nYPt[0].GetSize(), ptLine[0].x = pCell[1]->GetPosition().CenterPoint().x, ptLine[0].y = pCell[1]->GetPosition().top, ptLine[1].x = pCell[0]->GetPosition().CenterPoint().x, ptLine[1].y = pCell[0]->GetPosition().bottom, nCount = 0, nIndex = 0; nLine < nLines; nLine++)
											{
												if (min(ptLine[0].x, ptLine[1].x) - DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE >(INT) max(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine)) || max(ptLine[0].x, ptLine[1].x) + DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE < (INT)min(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine))) continue;
												if (min(ptLine[0].y, ptLine[1].y) - DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE >(INT) max(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine)) || max(ptLine[0].y, ptLine[1].y) + DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE < (INT)min(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine))) continue;
												if (ptLine[0].x == nXPt[0].GetAt(nLine) && ptLine[0].y == nYPt[0].GetAt(nLine) && nIndex > 0) continue;
												nIndex = (min(ptLine[0].x, ptLine[1].x) <= (INT)min(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine))) ? (nIndex + 1) : nIndex;
												nCount++;
											}
											pDC->MoveTo(ptLine[0]);
											pDC->LineTo(ptLine[0].x, ptLine[0].y - ((ptLine[0].y - ptLine[1].y)*nIndex) / (nCount + 1));
											pDC->LineTo(ptLine[1].x, ptLine[0].y - ((ptLine[0].y - ptLine[1].y)*nIndex) / (nCount + 1));
											pDC->LineTo(ptLine[1]);
										}
										else
										{
											pDC->MoveTo(pCell[1]->GetPosition().CenterPoint().x, pCell[1]->GetPosition().top);
											pDC->LineTo(pCell[1]->GetPosition().CenterPoint().x, pCell[0]->GetPosition().bottom);
										}
									}
								}
							}
							if (rTable.right > 0 && !rTable.bottom)
							{
								if ((pCell[0] = pTable[0]->FindCell(0, 0)))
								{
									if ((pCell[1] = pTable[1]->FindCell(rTable.right, pTable[1]->GetColumns() - 1)))
									{
										if (pCell[1]->GetPosition().CenterPoint().y <= pCell[0]->GetPosition().top || pCell[1]->GetPosition().CenterPoint().y >= pCell[0]->GetPosition().bottom)
										{
											for (nLine = 0, nLines = (INT)nXPt[0].GetSize(), ptLine[0].x = pCell[1]->GetPosition().right, ptLine[0].y = pCell[1]->GetPosition().CenterPoint().y, ptLine[1].x = pCell[0]->GetPosition().left, ptLine[1].y = pCell[0]->GetPosition().CenterPoint().y, nCount = 0, nIndex = 0; nLine < nLines; nLine++)
											{
												if (min(ptLine[0].x, ptLine[1].x) - DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE >(INT) max(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine)) || max(ptLine[0].x, ptLine[1].x) + DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE < (INT)min(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine))) continue;
												if (min(ptLine[0].y, ptLine[1].y) - DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE >(INT) max(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine)) || max(ptLine[0].y, ptLine[1].y) + DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE < (INT)min(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine))) continue;
												if (ptLine[0].x == nXPt[0].GetAt(nLine) && ptLine[0].y == nYPt[0].GetAt(nLine) && nIndex > 0) continue;
												nIndex = (min(ptLine[0].y, ptLine[1].y) <= (INT)min(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine))) ? (nIndex + 1) : nIndex;
												nCount++;
											}
											pDC->MoveTo(ptLine[0]);
											pDC->LineTo(ptLine[0].x + ((ptLine[1].x - ptLine[0].x)*nIndex) / (nCount + 1), ptLine[0].y);
											pDC->LineTo(ptLine[0].x + ((ptLine[1].x - ptLine[0].x)*nIndex) / (nCount + 1), ptLine[1].y);
											pDC->LineTo(ptLine[1]);
										}
										else
										{
											pDC->MoveTo(pCell[1]->GetPosition().right, pCell[1]->GetPosition().CenterPoint().y);
											pDC->LineTo(pCell[0]->GetPosition().left, pCell[1]->GetPosition().CenterPoint().y);
										}
									}
								}
							}
							if (rTable.bottom > 0 && !rTable.right)
							{
								if ((pCell[0] = pTable[0]->FindCell(0, 0)))
								{
									if ((pCell[1] = pTable[1]->FindCell(pTable[1]->GetRows() - 1, rTable.bottom - 1)))
									{
										if (pCell[1]->GetPosition().CenterPoint().x <= pCell[0]->GetPosition().left || pCell[1]->GetPosition().CenterPoint().x >= pCell[0]->GetPosition().right)
										{
											for (nLine = 0, nLines = (INT)nYPt[0].GetSize(), ptLine[0].x = pCell[1]->GetPosition().CenterPoint().x, ptLine[0].y = pCell[1]->GetPosition().bottom, ptLine[1].x = pCell[0]->GetPosition().CenterPoint().x, ptLine[1].y = pCell[0]->GetPosition().top, nCount = 0, nIndex = 0; nLine < nLines; nLine++)
											{
												if (min(ptLine[0].x, ptLine[1].x) >(INT) max(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine)) || max(ptLine[0].x, ptLine[1].x) < (INT)min(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine))) continue;
												if (min(ptLine[0].y, ptLine[1].y) > (INT)max(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine)) || max(ptLine[0].y, ptLine[1].y) < (INT)min(nYPt[0].GetAt(nLine), nYPt[1].GetAt(nLine))) continue;
												if (ptLine[0].x == nXPt[0].GetAt(nLine) && ptLine[0].y == nYPt[0].GetAt(nLine) && nIndex > 0) continue;
												nIndex = (min(ptLine[0].x, ptLine[1].x) <= (INT)min(nXPt[0].GetAt(nLine), nXPt[1].GetAt(nLine))) ? (nIndex + 1) : nIndex;
												nCount++;
											}
											pDC->MoveTo(ptLine[0]);
											pDC->LineTo(ptLine[0].x, ptLine[0].y + ((ptLine[1].y - ptLine[0].y)*nIndex) / (nCount + 1));
											pDC->LineTo(ptLine[1].x, ptLine[0].y + ((ptLine[1].y - ptLine[0].y)*nIndex) / (nCount + 1));
											pDC->LineTo(ptLine[1]);
										}
										else
										{
											pDC->MoveTo(pCell[1]->GetPosition().CenterPoint().x, pCell[1]->GetPosition().bottom);
											pDC->LineTo(pCell[1]->GetPosition().CenterPoint().x, pCell[0]->GetPosition().top);
										}
									}
								}
							}
						}
					}
				}
			}
			pDC->SelectObject(pOldPen);
		}
		cLinePen.DeleteObject();
		break;
	}
	for (nTable = 0, nTables = (INT)szTables.GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable[0] = pTables->GetAt(pTables->Find(szTables.GetAt(nTable)))))
		{
			for (rClip = pTable[0]->GetCellsBounds(); rgClip.CreateRectRgn(rClip.left, rClip.top, rClip.right, rClip.bottom); )
			{
				pDC->SelectClipRgn(&rgClip, RGN_OR);
				rgClip.DeleteObject();
				break;
			}
		}
	}
	EnableTablesAlignment(bTables);
}

VOID CDisplayTableView::DrawTable(CDC *pDC, CONST CTableViewObject *pTable, BOOL bPrinting)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nSel[2];
	INT  nBorderSize;
	INT  nBorderStyle;
	CPen  cBorderPen;
	CPen  *pOldPen;
	CRect  rView;
	CRect  rClip;
	CRect  rCell;
	LOGBRUSH  sPen;
	COLORREF  nBkgndColor;
	COLORREF  nBorderColor;
	CTableViewCell  *pCell;

	GetClientRect(rView);
	rView.OffsetRect(GetScrollPosition());
	for (nRow = 0, nRows = (rClip.IntersectRect(rView, pTable) || bPrinting) ? pTable->GetRows() : 0; nRow < nRows; nRow++)
	{
		for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
		{
			if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
			{
				if (((rCell = pCell->GetPosition()).bottom >= rView.top  &&  rCell.top <= rView.bottom  &&  rCell.right >= rView.left  &&  rCell.left <= rView.right) || bPrinting)
				{
					for (pCell->GetBorder(TAS_BORDER_LEFT, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL, pDC->FillSolidRect(rCell.left, rCell.top, 1, rCell.Height(), (nBkgndColor = (pCell != GetActiveCell() || (pCell->GetFormat() & TAS_TYPE_TEXT) || (pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_SPINBOX) || (pCell->GetFormat() & TAS_TYPE_TIMESPINBOX) || (pCell->GetFormat() & TAS_TYPE_SUBTABLE)) ? ((pCell != GetActiveCell() || (pCell->GetFormat() & TAS_TYPE_TEXT) || (pCell->GetFormat() & TAS_TYPE_SUBTABLE)) ? ((pTable->GetSelRow() == pCell->y || pTable->GetSelColumn() == pCell->x || (pTable->GetSelCell(nSel[0], nSel[1]) && pCell->x == nSel[1] && pCell->y == nSel[0])) ? pTable->GetSelColor() : pCell->GetBackgroundColor()) : GetSysColor(COLOR_WINDOW)) : GetSysColor(COLOR_3DFACE))), pDC->FillSolidRect(rCell.left, rCell.top, rCell.Width(), 1, nBkgndColor), pDC->FillSolidRect(rCell.right - 1, rCell.top, 1, rCell.Height(), nBkgndColor), pDC->FillSolidRect(rCell.left, rCell.bottom - 1, rCell.Width(), 1, nBkgndColor), pDC->FillSolidRect(((pCell->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE) ? rCell : CRect(0, 0, 0, 0), nBkgndColor); cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
					{
						if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)))
						{
							pDC->MoveTo(rCell.left, rCell.bottom);
							pDC->LineTo(rCell.left, rCell.top);
							pDC->SelectObject(pOldPen);
						}
						cBorderPen.DeleteObject();
						break;
					}
					for (pCell->GetBorder(TAS_BORDER_TOP, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL; cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
					{
						if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)))
						{
							pDC->MoveTo(rCell.left, rCell.top);
							pDC->LineTo(rCell.right, rCell.top);
							pDC->SelectObject(pOldPen);
						}
						cBorderPen.DeleteObject();
						break;
					}
					for (pCell->GetBorder(TAS_BORDER_RIGHT, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL; cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
					{
						if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)))
						{
							pDC->MoveTo(rCell.right, rCell.top);
							pDC->LineTo(rCell.right, rCell.bottom);
							pDC->SelectObject(pOldPen);
						}
						cBorderPen.DeleteObject();
						break;
					}
					for (pCell->GetBorder(TAS_BORDER_BOTTOM, nBorderSize, nBorderStyle, nBorderColor), sPen.lbStyle = PS_SOLID, sPen.lbColor = nBorderColor, sPen.lbHatch = (ULONG_PTR)NULL; cBorderPen.CreatePen(nBorderStyle | PS_GEOMETRIC | PS_ENDCAP_SQUARE, nBorderSize, &sPen); )
					{
						if ((pOldPen = (CPen *)pDC->SelectObject(&cBorderPen)))
						{
							pDC->MoveTo(rCell.left, rCell.bottom);
							pDC->LineTo(rCell.right, rCell.bottom);
							pDC->SelectObject(pOldPen);
						}
						cBorderPen.DeleteObject();
						break;
					}
					if (pCell != GetActiveCell()) pCell->Draw(pDC);
					continue;
				}
				if (rCell.top > rView.bottom  &&  !bPrinting) break;
			}
		}
		if (nCol < nCols) break;
	}
}

BOOL CDisplayTableView::GetPanesInfo(CString &szDetails, CString &szFlag, CString &szType) CONST
{
	BOOL  bResize;
	BOOL  bVisible;
	CUIntArray  nIDs;
	CUIntArray  nFormats;
	CStringArray  szRow[3];

	for (szDetails.Empty(), szFlag.Empty(), szType.Empty(); GetTableContents((m_szTables.GetSize() > 0) ? (LPCTSTR)m_szTables.GetAt(0) : EMPTYSTRING, EMPTYSTRING, 0, szRow[0], szRow[1], szRow[2], nFormats, nIDs, bResize, bVisible) && szRow[1].GetSize() > 0 && szRow[2].GetSize() > 0; )
	{
		szFlag = STRING(IDS_DATABASE_DATAFLAG_NOTAPPLICABLE);
		szDetails = szRow[1].GetAt(0);
		szType = szRow[2].GetAt(0);
		return TRUE;
	}
	return FALSE;
}

VOID CDisplayTableView::DoSelectAll()
{
	return;
}

BOOL CDisplayTableView::CanSelectAll() CONST
{
	return FALSE;
}

VOID CDisplayTableView::UnSelectAll()
{
	INT  nTable;
	INT  nTables;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), SetActiveCell(); nTable < nTables; nTable++)
	{
		if ((pTable = m_pTables->GetAt(nTable)))
		{
			pTable->SetSelCell();
			continue;
		}
	}
	DrawTables();
}

VOID CDisplayTableView::DoCutSel()
{
	CEdit  *pEdit;
	CComboBox  *pComboBox;
	CRichEditCtrl  *pRichEditCtrl;
	CTableViewCell  *pCell;

	if ((pCell = GetActiveCell()))
	{
		if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
		{
			if ((pEdit = (CEdit *)pCell->GetControl()))
			{
				pEdit->Cut();
				return;
			}
		}
		if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
		{
			if ((pRichEditCtrl = (CRichEditCtrl *)pCell->GetControl()))
			{
				pRichEditCtrl->Cut();
				return;
			}
		}
		if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
		{
			if ((pComboBox = (CComboBox *)pCell->GetControl()))
			{
				pComboBox->Cut();
				return;
			}
		}
	}
}

BOOL CDisplayTableView::CanCutSel() CONST
{
	INT  nSel[2];
	WORD  wSel[1];
	DWORD  dwSel[1];
	CEdit  *pEdit;
	CComboBox  *pComboBox;
	CRichEditCtrl  *pRichEditCtrl;
	CTableViewCell  *pCell;

	if ((pCell = GetActiveCell()))
	{
		if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
		{
			if ((pEdit = (CEdit *)pCell->GetControl()))
			{
				pEdit->GetSel(nSel[0], nSel[1]);
				return((nSel[0] < nSel[1]) ? CheckPrivilege() : FALSE);
			}
		}
		if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
		{
			if ((pRichEditCtrl = (CRichEditCtrl *)pCell->GetControl()))
			{
				wSel[0] = pRichEditCtrl->GetSelectionType();
				return((wSel[0] != SEL_EMPTY) ? CheckPrivilege() : FALSE);
			}
		}
		if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
		{
			if ((pComboBox = (CComboBox *)pCell->GetControl()))
			{
				dwSel[0] = pComboBox->GetEditSel();
				return((LOWORD(dwSel[0]) < HIWORD(dwSel[0])) ? CheckPrivilege() : FALSE);
			}
		}
	}
	return FALSE;
}

VOID CDisplayTableView::DoCopySel()
{
	CEdit  *pEdit;
	CComboBox  *pComboBox;
	CRichEditCtrl  *pRichEditCtrl;
	CTableViewCell  *pCell;

	if ((pCell = GetActiveCell()))
	{
		if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
		{
			if ((pEdit = (CEdit *)pCell->GetControl()))
			{
				pEdit->Copy();
				return;
			}
		}
		if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
		{
			if ((pRichEditCtrl = (CRichEditCtrl *)pCell->GetControl()))
			{
				pRichEditCtrl->Copy();
				return;
			}
		}
		if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
		{
			if ((pComboBox = (CComboBox *)pCell->GetControl()))
			{
				pComboBox->Copy();
				return;
			}
		}
	}
}

BOOL CDisplayTableView::CanCopySel() CONST
{
	INT  nSel[2];
	WORD  wSel[1];
	DWORD  dwSel[1];
	CEdit  *pEdit;
	CComboBox  *pComboBox;
	CRichEditCtrl  *pRichEditCtrl;
	CTableViewCell  *pCell;

	if ((pCell = GetActiveCell()))
	{
		if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
		{
			if ((pEdit = (CEdit *)pCell->GetControl()))
			{
				pEdit->GetSel(nSel[0], nSel[1]);
				return((nSel[0] < nSel[1]) ? CheckPrivilege() : FALSE);
			}
		}
		if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
		{
			if ((pRichEditCtrl = (CRichEditCtrl *)pCell->GetControl()))
			{
				wSel[0] = pRichEditCtrl->GetSelectionType();
				return((wSel[0] != SEL_EMPTY) ? CheckPrivilege() : FALSE);
			}
		}
		if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
		{
			if ((pComboBox = (CComboBox *)pCell->GetControl()))
			{
				dwSel[0] = pComboBox->GetEditSel();
				return((LOWORD(dwSel[0]) < HIWORD(dwSel[0])) ? CheckPrivilege() : FALSE);
			}
		}
	}
	return FALSE;
}

VOID CDisplayTableView::DoPasteSel()
{
	CEdit  *pEdit;
	CComboBox  *pComboBox;
	CRichEditCtrl  *pRichEditCtrl;
	CTableViewCell  *pCell;

	if ((pCell = GetActiveCell()))
	{
		if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
		{
			if ((pEdit = (CEdit *)pCell->GetControl()))
			{
				pEdit->Paste();
				return;
			}
		}
		if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
		{
			if ((pRichEditCtrl = (CRichEditCtrl *)pCell->GetControl()))
			{
				pRichEditCtrl->Paste();
				return;
			}
		}
		if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
		{
			if ((pComboBox = (CComboBox *)pCell->GetControl()))
			{
				pComboBox->Paste();
				return;
			}
		}
	}
}

BOOL CDisplayTableView::CanPasteSel() CONST
{
	CTableViewCell  *pCell;

	return(((pCell = GetActiveCell()) && ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)) && IsClipboardFormatAvailable(CF_TEXT)) ? CheckPrivilege() : FALSE);
}

VOID CDisplayTableView::DoDeleteSel()
{
	CEdit  *pEdit;
	CComboBox  *pComboBox;
	CRichEditCtrl  *pRichEditCtrl;
	CTableViewCell  *pCell;

	if ((pCell = GetActiveCell()))
	{
		if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
		{
			if ((pEdit = (CEdit *)pCell->GetControl()))
			{
				pEdit->Clear();
				return;
			}
		}
		if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
		{
			if ((pRichEditCtrl = (CRichEditCtrl *)pCell->GetControl()))
			{
				pRichEditCtrl->Clear();
				return;
			}
		}
		if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
		{
			if ((pComboBox = (CComboBox *)pCell->GetControl()))
			{
				pComboBox->Clear();
				return;
			}
		}
	}
}

BOOL CDisplayTableView::CanDeleteSel() CONST
{
	INT  nSel[2];
	WORD  wSel[1];
	DWORD  dwSel[1];
	CEdit  *pEdit;
	CComboBox  *pComboBox;
	CRichEditCtrl  *pRichEditCtrl;
	CTableViewCell  *pCell;

	if ((pCell = GetActiveCell()))
	{
		if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
		{
			if ((pEdit = (CEdit *)pCell->GetControl()))
			{
				pEdit->GetSel(nSel[0], nSel[1]);
				return((nSel[0] < nSel[1]) ? CheckPrivilege() : FALSE);
			}
		}
		if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
		{
			if ((pRichEditCtrl = (CRichEditCtrl *)pCell->GetControl()))
			{
				wSel[0] = pRichEditCtrl->GetSelectionType();
				return((wSel[0] != SEL_EMPTY) ? CheckPrivilege() : FALSE);
			}
		}
		if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
		{
			if ((pComboBox = (CComboBox *)pCell->GetControl()))
			{
				dwSel[0] = pComboBox->GetEditSel();
				return((LOWORD(dwSel[0]) < HIWORD(dwSel[0])) ? CheckPrivilege() : FALSE);
			}
		}
	}
	return FALSE;
}

BOOL CDisplayTableView::EnableUndo(BOOL bEnable)
{
	return((!bEnable  &&  m_cUndoList.Lock()) || (bEnable  &&  m_cUndoList.Unlock()));
}

VOID CDisplayTableView::DoUndo()
{
	INT  nCount;
	BOOL  bFocus;
	CString  szText;
	CTableViewCell  *pCell;
	CDisplayTableViewUndoItem  cUndoItem;

	for (m_cUndoList.Lock(), m_bUndo[0] = TRUE, nCount = ((bFocus = (GetActiveCell() != (CTableViewCell *)NULL))) ? 0 : -1; m_cUndoList.CanUndo(bFocus); )
	{
		do
		{
			if (m_cUndoList.Undo(&cUndoItem, bFocus))
			{
				for (ConvertUndoItem(&cUndoItem, TRUE); nCount >= 0; )
				{
					nCount++;
					break;
				}
				bFocus = TRUE;
				continue;
			}
			break;
		} while (m_cUndoList.CanCollectUndo());
		if (nCount > 1)
		{
			nCount = -1;
			continue;
		}
		break;
	}
	for (m_bUndo[0] = FALSE; !CanUndo(); )
	{
		if ((pCell = GetActiveCell()) && m_cUndoList.Undo(pCell, szText)) SetActiveCell(szText);
		break;
	}
	m_cUndoList.Unlock();
	DrawTables();
}

BOOL CDisplayTableView::IsUndoing() CONST
{
	return m_bUndo[0];
}

BOOL CDisplayTableView::CanUndo() CONST
{
	return((m_cUndoList.CanUndo(GetActiveCell() != (CTableViewCell *)NULL)) ? CheckPrivilege() : FALSE);
}

VOID CDisplayTableView::DoRedo()
{
	BOOL  bFocus;
	CString  szText;
	CTableViewCell  *pCell;
	CDisplayTableViewUndoItem  cUndoItem;

	for (m_cUndoList.Lock(), m_bUndo[1] = TRUE; m_cUndoList.CanRedo((bFocus = (GetActiveCell() != (CTableViewCell *)NULL))); )
	{
		do
		{
			if (m_cUndoList.Redo(&cUndoItem, bFocus))
			{
				ConvertUndoItem(&cUndoItem, FALSE);
				bFocus = TRUE;
				continue;
			}
			break;
		} while (m_cUndoList.CanCollectRedo());
		break;
	}
	for (m_bUndo[1] = FALSE; !CanRedo(); )
	{
		if ((pCell = GetActiveCell()) && m_cUndoList.Redo(pCell, szText)) SetActiveCell(szText);
		break;
	}
	m_cUndoList.Unlock();
	DrawTables();
}

BOOL CDisplayTableView::IsRedoing() CONST
{
	return m_bUndo[1];
}

BOOL CDisplayTableView::CanRedo() CONST
{
	return((m_cUndoList.CanRedo(GetActiveCell() != (CTableViewCell *)NULL)) ? CheckPrivilege() : FALSE);
}

VOID CDisplayTableView::ClearUndo()
{
	m_cUndoList.Reset();
}

BOOL CDisplayTableView::DoEmpty()
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	CRect  rTable;
	CUIntArray  nTypes;
	CUIntArray  nWidths;
	CStringArray  szTables;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = EnumTables(szTables, nTypes, FALSE, TRUE), SetName(EMPTYSTRING), SetActiveCell(), ClearUndo(), EnableUndo(FALSE); nTable < nTables; nTable++)
	{
		if ((pTable = FindTable(szTables.GetAt(nTable))) != (CTableViewObject *)NULL)
		{
			for (nRow = 0, nRows = pTable->GetRows(), pTable->SetSelCell(); nRow < nRows; nRow++)
			{
				for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
				{
					if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
					{
						if (((pTable->GetType() == TAS_TABLE_NORMAL && (pCell->GetFormat() & TAS_TYPE_TEXT) != TAS_TYPE_TEXT) || pTable->GetType() == TAS_TABLE_LIST) && (pCell->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE && (!pTable->HasTitle() || nRow > 0))
						{
							pCell->SetText(EMPTYSTRING);
							continue;
						}
					}
				}
				if (pTable->GetType() == TAS_TABLE_LIST && ((pTable->HasTitle() && pTable->GetRows() > 2 && nRow > 0) || (!pTable->HasTitle() && pTable->GetRows() > 1)) && pTable->RemoveRow(nRow))
				{
					nRows--;
					nRow--;
				}
			}
		}
	}
	for (nTable = 0; nTable < nTables; nTable++)
	{
		if ((pTable = FindTable(szTables.GetAt(nTable))))
		{
			if (GetTableLayout(pTable->GetName(), nWidths))
			{
				ProtectTableFieldData(pTable->GetName());
				RecalcTable(pTable, nWidths, TRUE, FALSE);
				continue;
			}
		}
		break;
	}
	ArrangeTables(0);
	EnableUndo(TRUE);
	return((nTable == nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::IsEmpty() CONST
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	CUIntArray  nTypes;
	CStringArray  szTables;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = EnumTables(szTables, nTypes, FALSE, TRUE); nTable < nTables; nTable++)
	{
		if ((pTable = FindTable(szTables.GetAt(nTable))) != (CTableViewObject *)NULL)
		{
			for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
			{
				for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
				{
					if ((pCell = pTable->FindCell(nRow, nCol)) != (CTableViewCell *)NULL)
					{
						if (pCell->GetFormat() & TAS_TYPE_SUBTABLE) continue;
						if (pCell->GetFormat() & TAS_TYPE_TEXT) continue;
						if (!pCell->GetText().IsEmpty()) break;
					}
				}
				if (nCol < nCols) break;
			}
			if (nRow < nRows) break;
		}
	}
	return((nTable == nTables) ? TRUE : FALSE);
}

BOOL CDisplayTableView::IsModified() CONST
{
	return CheckTableFieldData(TranslateComponentToTableName(m_nComponent), TRUE);
}

BOOL CDisplayTableView::Check() CONST
{
	return CheckTableFieldData(TranslateComponentToTableName(m_nComponent), FALSE);
}

CDisplayWnd *CDisplayTableView::GetParent() CONST
{
	return((CDisplayWnd *)CDatabaseTableView::GetParent());
}

VOID CDisplayTableView::BeginTableUpdate()
{
	CDC  cDC;
	CRect  rView;
	CBitmap  *pOldBitmap;
	CClientDC  cClientDC(this);

	for (BeginWaitCursor(), GetClientRect(rView), m_cImage.DeleteObject(), m_bImage = FALSE, m_cUndoList.Lock(); cDC.CreateCompatibleDC(&cClientDC); )
	{
		if (m_cImage.CreateCompatibleBitmap(&cClientDC, rView.Width(), rView.Height()))
		{
			if ((pOldBitmap = cDC.SelectObject(&m_cImage)) != (CBitmap *)NULL)
			{
				cDC.BitBlt(0, 0, rView.Width(), rView.Height(), &cClientDC, 0, 0, SRCCOPY);
				cDC.SelectObject(pOldBitmap);
				cDC.DeleteDC();
				m_bImage = TRUE;
				return;
			}
			m_cImage.DeleteObject();
		}
		cDC.DeleteDC();
		break;
	}
}

VOID CDisplayTableView::EndTableUpdate()
{
	if (m_bImage)
	{
		m_cImage.DeleteObject();
		m_bImage = FALSE;
	}
	m_cUndoList.Unlock();
	EndWaitCursor();
}

VOID CDisplayTableView::RefreshTables(BOOL bAll)
{
	RefreshTables(m_szTables, bAll);
}
VOID CDisplayTableView::RefreshTables(CONST CStringArray &szTables, BOOL bAll)
{
	INT  nTable;
	INT  nTables;

	for (nTable = 0, nTables = (INT)szTables.GetSize(); nTable < nTables; nTable++)
	{
		RefreshTable(szTables.GetAt(nTable), (bAll) ? -1 : 0);
		continue;
	}
	ArrangeTables(0);
}
VOID CDisplayTableView::RefreshTables(CONST CTableViewObject *pTable, BOOL bAll)
{
	INT  nTable;
	INT  nTables;
	CRect  rTable;
	CString  szTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if (GetTablePosition(m_pTables->GetAt(nTable)->GetName(), szTable, rTable) && pTable->GetName() == szTable)
		{
			RefreshTable(m_pTables->GetAt(nTable), GetName(), (bAll) ? -1 : 0);
			continue;
		}
	}
	ArrangeTables(0);
}
VOID CDisplayTableView::RefreshTables(UINT nControlID)
{
	CStringArray  szTables;

	if (EnumTableUpdates(nControlID, szTables) > 0)
	{
		RefreshTables(szTables, nControlID);
		return;
	}
}
VOID CDisplayTableView::RefreshTables(CONST CStringArray &szTables, UINT nControlID)
{
	INT  nTable;
	INT  nTables;
	CString  szValue;
	CTableViewObject  *pTable;
	CTableViewCell  *pCell;

	for (nTable = 0, nTables = (nControlID != 0 && nControlID != (UINT)-1) ? (INT)m_szTables.GetSize() : 0; nTable < nTables; nTable++)
	{
		if ((pCell = ((pTable = FindTable(m_szTables.GetAt(nTable)))) ? pTable->FindCell(nControlID) : (CTableViewCell *)NULL))
		{
			szValue = (pTable->GetType() == TAS_TABLE_LIST) ? (((pCell = pTable->FindCell(max(pTable->GetSelRow(), (pTable->HasTitle()) ? 1 : 0), pCell->x))) ? pCell->GetText() : EMPTYSTRING) : pCell->GetText();
			break;
		}
	}
	for (nTable = 0, nTables = (INT)szTables.GetSize(); nTable < nTables; nTable++)
	{
		if ((pTable = FindTable(szTables.GetAt(nTable))) != (CTableViewObject *)NULL)
		{
			RefreshTable(pTable, (!nControlID || nControlID == (UINT)-1) ? GetName() : szValue, nControlID);
			continue;
		}
	}
	ArrangeTables(0);
}

VOID CDisplayTableView::RefreshTable(LPCTSTR pszTable, BOOL bAll)
{
	CTableViewObject  *pTable;

	if ((pTable = FindTable(pszTable)))
	{
		RefreshTable(pTable, GetName(), (bAll) ? -1 : 0);
		return;
	}
}
VOID CDisplayTableView::RefreshTable(CTableViewObject *pTable, LPCTSTR pszValue, UINT nControlID)
{
	CString  szTable;
	CStringArray  szContents;

	for (EnableUndo(FALSE); GetTableUpdateContents(pTable->GetName(), nControlID, pszValue, szTable, szContents); )
	{
		UpdateTableContents(pTable, szContents);
		break;
	}
	EnableUndo(TRUE);
}

BOOL CDisplayTableView::ConvertUndoItem(LPCTSTR pszTable, CDisplayTableViewUndoItem *pItem, BOOL bUpdates) CONST
{
	UINT  nControlID;
	CString  szTable;
	CString  szValue;

	if (GetTableContext(pszTable, szTable, nControlID, szValue))
	{
		pItem->SetAlignment(GetTableFloatingAlignment(pszTable));
		pItem->AllowUpdates(bUpdates);
		pItem->AllowActivation(FALSE);
		pItem->SetContext(szValue);
		return TRUE;
	}
	return FALSE;
}
BOOL CDisplayTableView::ConvertUndoItem(CWnd *pControl, CDisplayTableViewUndoItem *pItem, BOOL bUpdates) CONST
{
	INT  nTable;
	INT  nTables;
	INT  nSel[2];
	UINT  nControlID;
	DWORD  dwSel[2];
	CPoint  ptCell;
	CString  szItem;
	CString  szTable;
	CString  szValue;
	CHARRANGE  sRange;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;
	CStringTools  cStringTools;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), pItem->Clear(), pItem->AllowUpdates(bUpdates), pItem->AllowActivation(); nTable < nTables; nTable++)
	{
		if ((pCell = ((pTable = m_pTables->GetAt(nTable))) ? pTable->FindCell(pControl) : (CTableViewCell *)NULL) != (CTableViewCell *)NULL)
		{
			for (pItem->SetCell(pTable->GetName(), CPoint(pCell->x, pCell->y)); GetTableContext(pTable->GetName(), szTable, nControlID, szValue); )
			{
				pItem->SetContext(szValue);
				break;
			}
			pItem->SetAlignment(GetTableFloatingAlignment(pTable->GetName()));
			break;
		}
	}
	for (pItem->GetCell(szTable, ptCell); (pTable = m_pTables->GetAt(m_pTables->Find(szTable))); )
	{
		if ((pCell = pTable->FindCell(ptCell.y, ptCell.x)) != (CTableViewCell *)NULL)
		{
			if ((pCell->GetFormat() & TAS_TYPE_EDIT) || (pCell->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell->GetFormat() & TAS_TYPE_RAWNUMBEREDIT))
			{
				for (dwSel[0] = 0, dwSel[1] = (DWORD)-1; IsWindow(pControl->GetSafeHwnd()); )
				{
					pControl->SendMessage(EM_GETSEL, (WPARAM)&dwSel[0], (LPARAM)&dwSel[1]);
					break;
				}
				pItem->SetText(pCell->GetText());
				pItem->SetSel(dwSel[0], dwSel[1]);
				return TRUE;
			}
			if ((pCell->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell->GetFormat() & TAS_TYPE_TPLEDIT))
			{
				for (sRange.cpMin = 0, sRange.cpMax = -1; IsWindow(pControl->GetSafeHwnd()); )
				{
					pControl->SendMessage(EM_EXGETSEL, (WPARAM)NULL, (LPARAM)&sRange);
					break;
				}
				pItem->SetText(pCell->GetText());
				pItem->SetSel(sRange.cpMin, sRange.cpMax);
				return TRUE;
			}
			if (pCell->GetFormat() & TAS_TYPE_COMBOLISTBOX)
			{
				pItem->SetText(pCell->GetText());
				return TRUE;
			}
			if (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX)
			{
				for (dwSel[0] = 0, dwSel[1] = (DWORD)-1; IsWindow(pControl->GetSafeHwnd()); )
				{
					pControl->SendMessage(CB_GETEDITSEL, (WPARAM)&dwSel[0], (LPARAM)&dwSel[1]);
					break;
				}
				pItem->SetText(pCell->GetText());
				pItem->SetSel(dwSel[0], dwSel[1]);
				return TRUE;
			}
			if (pCell->GetFormat() & TAS_TYPE_COMBOCOLORSBOX)
			{
				pItem->SetText(pCell->GetText());
				return TRUE;
			}
			if (pCell->GetFormat() & TAS_TYPE_COMBOLINESTYLESBOX)
			{
				pItem->SetText(pCell->GetText());
				return TRUE;
			}
			if (pCell->GetFormat() & TAS_TYPE_COMBOLINESYMBOLSBOX)
			{
				pItem->SetText(pCell->GetText());
				return TRUE;
			}
			if (pCell->GetFormat() & TAS_TYPE_SPINBOX)
			{
				for (nSel[0] = 0, nSel[1] = -1; IsWindow(pControl->GetSafeHwnd()); )
				{
					Spinbox_GetSel(pControl, nSel[0], nSel[1]);
					break;
				}
				pItem->SetInitialText(pCell->GetInitialText());
				pItem->SetText(pCell->GetText());
				pItem->SetSel(nSel[0], nSel[1]);
				return TRUE;
			}
			if (pCell->GetFormat() & TAS_TYPE_TIMESPINBOX)
			{
				for (nSel[0] = 0, nSel[1] = -1; IsWindow(pControl->GetSafeHwnd()); )
				{
					Timespinbox_GetSel(pControl, nSel[0], nSel[1]);
					break;
				}
				pItem->SetInitialText(pCell->GetInitialText());
				pItem->SetText(pCell->GetText());
				pItem->SetSel(nSel[0], nSel[1]);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}
BOOL CDisplayTableView::ConvertUndoItem(CONST CDisplayTableViewUndoItem *pItem, BOOL bUndo)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nTable;
	INT  nTables;
	INT  nSel[2];
	UINT  nControlID;
	CWnd  *pControl;
	CRect  rTable;
	CPoint  ptCell;
	CString  szText;
	CString  szItem;
	CString  szTable;
	CString  szValue;
	CHARRANGE  sRange;
	CStringArray  szRow;
	CStringArray  szItems;
	CStringArray  szTables;
	CStringArray  szColumn;
	CTableViewCell  *pCell[2];
	CTableViewObject  *pTable[3];

	for (pItem->GetCell(szTable, ptCell); (pTable[0] = m_pTables->GetAt(m_pTables->Find(szTable))); )
	{
		if (pItem->GetAlignment() != GetTableFloatingAlignment(pTable[0]->GetName()) && pItem->GetAlignment() >= 0)
		{
			SetTableFloatingAlignment(pTable[0]->GetName(), pItem->GetAlignment());
			AlignFloatingTable(pTable[0]->GetName());
		}
		if ((pCell[0] = pTable[0]->FindCell(ptCell.y, ptCell.x)))
		{
			for (szText = pCell[0]->GetText(); ptCell.y >= pTable[0]->GetRows(); )
			{
				if (!pTable[0]->SetSelRow(pTable[0]->GetRows() - 1)) break;
				if (!DoInsertTableRowBelow()) break;
			}
			if ((pControl = (pCell[0]->IsEnabled() && !pItem->IsCollected() && pItem->CanActivate()) ? pCell[0]->GetControl() : (CWnd *)NULL))
			{
				for (SetActiveCell(pTable[0], pCell[0], (bUndo) ? TAS_ACTION_UNDO : TAS_ACTION_REDO); pTable[0]->GetType() == TAS_TABLE_LIST; )
				{
					SelectTableFieldData(pTable[0]->GetName(), CPoint(pCell[0]->x, pCell[0]->y));
					break;
				}
				for (pControl->ShowWindow(SW_SHOW), pCell[0]->SetText(pItem->GetText(), FALSE); (pCell[0]->GetFormat() & TAS_TYPE_TIMESPINBOX) != TAS_TYPE_TIMESPINBOX; )
				{
					pControl->SetFocus();
					break;
				}
				for (pItem->GetSel(nSel[0], nSel[1]); (pCell[0]->GetFormat() & TAS_TYPE_EDIT) || (pCell[0]->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell[0]->GetFormat() & TAS_TYPE_RAWNUMBEREDIT); )
				{
					pControl->SendMessage(EM_SETSEL, nSel[0], nSel[1]);
					break;
				}
				if ((pCell[0]->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_TPLEDIT))
				{
					sRange.cpMin = nSel[0];
					sRange.cpMax = nSel[1];
					pControl->SendMessage(EM_EXSETSEL, (WPARAM)NULL, (LPARAM)&sRange);
				}
				for (; pCell[0]->GetFormat() & TAS_TYPE_COMBOEDITBOX; )
				{
					pControl->SendMessage(CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(nSel[0], nSel[1]));
					break;
				}
				for (; pCell[0]->GetFormat() & TAS_TYPE_SPINBOX; )
				{
					Spinbox_SetSel(pControl, nSel[0], nSel[1]);
					break;
				}
				for (; pCell[0]->GetFormat() & TAS_TYPE_TIMESPINBOX; )
				{
					Timespinbox_SetSel(pControl, nSel[0], nSel[1]);
					break;
				}
			}
			if (pItem->IsCollected() || !pItem->CanActivate())
			{
				for (pCell[0]->SetText(pItem->GetText(), FALSE); pTable[0]->GetType() == TAS_TABLE_LIST && pItem->CanSelect(); )
				{
					SelectTableFieldData(pTable[0]->GetName(), CPoint(pCell[0]->x, pCell[0]->y));
					break;
				}
			}
			for (nTable = 0, nTables = pItem->CanUpdate()*EnumTableUpdates(pCell[0]->GetControlID(), szTables), UpdateTableFieldData(pCell[0]->GetControlID(), pItem->GetText()); nTable < nTables; nTable++)
			{
				if (GetTableUpdateContents(szTables.GetAt(nTable), pCell[0]->GetControlID(), pItem->GetText(), szItem, szItems))
				{
					if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable)))))
					{
						UpdateTableContents(pTable[1], szItems);
						continue;
					}
				}
			}
			ArrangeTables(0);
			return TRUE;
		}
		if (ptCell.x == -1)
		{
			for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
			{
				if ((pTable[1] = m_pTables->GetAt(nTable)))
				{
					pTable[1]->SetSelRow();
					pTable[1]->SetSelColumn();
				}
			}
			for (pTable[0]->SetSelRow(min(pTable[0]->GetRows() - 1, abs(ptCell.y) - 1)), SetActiveCell(); (bUndo && ((ptCell.y < 0 && ((abs(ptCell.y) <= pTable[0]->GetRows() && DoInsertTableRowAbove()) || (abs(ptCell.y) > pTable[0]->GetRows() && DoInsertTableRowBelow()))) || (ptCell.y > 0 && DoDeleteTableRow()))) || (!bUndo && ((ptCell.y > 0 && ((abs(ptCell.y) <= pTable[0]->GetRows() && DoInsertTableRowAbove()) || (abs(ptCell.y) > pTable[0]->GetRows() && DoInsertTableRowBelow()))) || (ptCell.y < 0 && DoDeleteTableRow()))); )
			{
				for (nCol = 0, nCols = ((bUndo && ptCell.y < 0) || (!bUndo && ptCell.y > 0)) ? pTable[0]->GetColumns() : 0, ExtractTextItems(pItem->GetText(), szRow); nCol < nCols; nCol++)
				{
					if ((pCell[0] = pTable[0]->FindCell(abs(ptCell.y) - 1, nCol)) != (CTableViewCell *)NULL)
					{
						for (pCell[0]->SetText((szText = (nCol < szRow.GetSize()) ? (LPCTSTR)szRow.GetAt(nCol) : EMPTYSTRING), FALSE); IsWindow((pControl = pCell[0]->GetControl())->GetSafeHwnd()); )
						{
							for (sRange.cpMin = sRange.cpMax = 0; (pCell[0]->GetFormat() & TAS_TYPE_EDIT) || (pCell[0]->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell[0]->GetFormat() & TAS_TYPE_RAWNUMBEREDIT); )
							{
								pControl->SendMessage(EM_SETSEL, 0, -1);
								break;
							}
							if ((pCell[0]->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_TPLEDIT)) pControl->SendMessage(EM_EXSETSEL, (WPARAM)NULL, (LPARAM)&sRange);
							if (pCell[0]->GetFormat() & TAS_TYPE_COMBOEDITBOX) pControl->SendMessage(CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
							if (pCell[0]->GetFormat() & TAS_TYPE_TIMESPINBOX) Timespinbox_SetSel(pControl, 0, -1);
							if (pCell[0]->GetFormat() & TAS_TYPE_SPINBOX) Spinbox_SetSel(pControl, 0, -1);
							break;
						}
						UpdateTableFieldData(pCell[0]->GetControlID(), szText);
					}
				}
				for (nCol = 0; nCol < nCols; nCol++)
				{
					if ((pCell[0] = pTable[0]->FindCell(abs(ptCell.y) - 1, nCol)))
					{
						for (nTable = 0, nTables = EnumTableUpdates(pCell[0]->GetControlID(), szTables); nTable < nTables; nTable++)
						{
							if (GetTableUpdateContents(szTables.GetAt(nTable), pCell[0]->GetControlID(), pCell[0]->GetText(), szItem, szItems))
							{
								if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable)))))
								{
									UpdateTableContents(pTable[1], szItems);
									continue;
								}
							}
						}
					}
				}
				for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
				{
					if ((pTable[1] = m_pTables->GetAt(nTable)) && GetTablePosition(pTable[1]->GetName(), szTable, rTable) && pTable[0]->GetName() == szTable  &&  GetTableFloatingAlignment(pTable[1]->GetName()) >= 0)
					{
						for (GetTableContext(pTable[1]->GetName(), szTable, nControlID, szValue); GetTableUpdateContents(pTable[1]->GetName(), -1, szValue, szItem, szItems); )
						{
							UpdateTableContents(pTable[1], szItems);
							break;
						}
						continue;
					}
				}
				ArrangeTables(0);
				return TRUE;
			}
		}
		if (ptCell.y == -1)
		{
			for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
			{
				if ((pTable[1] = m_pTables->GetAt(nTable)))
				{
					pTable[1]->SetSelRow();
					pTable[1]->SetSelColumn();
				}
			}
			for (pTable[0]->SetSelCell(0, min(pTable[0]->GetColumns() - 1, abs(ptCell.x) - 1)), SetActiveCell(); (bUndo && ((ptCell.x < 0 && ((abs(ptCell.x) <= pTable[0]->GetColumns() && DoInsertTableColumnBefore()) || (abs(ptCell.x) > pTable[0]->GetColumns() && DoInsertTableColumnAfter()))) || (ptCell.x > 0 && DoDeleteTableColumn()))) || (!bUndo && ((ptCell.x > 0 && ((abs(ptCell.x) <= pTable[0]->GetColumns() && DoInsertTableColumnBefore()) || (abs(ptCell.x) > pTable[0]->GetColumns() && DoInsertTableColumnAfter()))) || (ptCell.x < 0 && DoDeleteTableColumn()))); )
			{
				for (nRow = 0, nRows = ((bUndo && ptCell.x < 0) || (!bUndo && ptCell.x > 0)) ? pTable[0]->GetRows() : 0, ExtractTextItems(pItem->GetText(), szColumn); nRow < nRows; nRow++)
				{
					if ((pCell[0] = pTable[0]->FindCell(nRow, abs(ptCell.x) - 1)) != (CTableViewCell *)NULL)
					{
						for (pCell[0]->SetText((szText = (nRow < szColumn.GetSize()) ? (LPCTSTR)szColumn.GetAt(nRow) : EMPTYSTRING), FALSE); IsWindow((pControl = pCell[0]->GetControl())->GetSafeHwnd()); )
						{
							for (sRange.cpMin = sRange.cpMax = 0; (pCell[0]->GetFormat() & TAS_TYPE_EDIT) || (pCell[0]->GetFormat() & TAS_TYPE_MULTILINEEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_DECNUMBEREDIT) || (pCell[0]->GetFormat() & TAS_TYPE_RAWNUMBEREDIT); )
							{
								pControl->SendMessage(EM_SETSEL, 0, -1);
								break;
							}
							if ((pCell[0]->GetFormat() & TAS_TYPE_DPLEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_MDLEDIT) || (pCell[0]->GetFormat() & TAS_TYPE_TPLEDIT)) pControl->SendMessage(EM_EXSETSEL, (WPARAM)NULL, (LPARAM)&sRange);
							if (pCell[0]->GetFormat() & TAS_TYPE_COMBOEDITBOX) pControl->SendMessage(CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
							if (pCell[0]->GetFormat() & TAS_TYPE_TIMESPINBOX) Timespinbox_SetSel(pControl, 0, -1);
							if (pCell[0]->GetFormat() & TAS_TYPE_SPINBOX) Spinbox_SetSel(pControl, 0, -1);
							break;
						}
						UpdateTableFieldData(pCell[0]->GetControlID(), szText);
					}
				}
				for (nRow = 0; nRow < nRows; nRow++)
				{
					if ((pCell[0] = pTable[0]->FindCell(nRow, abs(ptCell.x) - 1)))
					{
						for (nTable = 0, nTables = EnumTableUpdates(pCell[0]->GetControlID(), szTables); nTable < nTables; nTable++)
						{
							if (GetTableUpdateContents(szTables.GetAt(nTable), pCell[0]->GetControlID(), pCell[0]->GetText(), szItem, szItems))
							{
								if ((pTable[1] = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable)))))
								{
									UpdateTableContents(pTable[1], szItems);
									continue;
								}
							}
						}
					}
				}
				for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
				{
					if ((pTable[1] = m_pTables->GetAt(nTable)) && GetTablePosition(pTable[1]->GetName(), szTable, rTable) && pTable[0]->GetName() == szTable  &&  GetTableFloatingAlignment(pTable[1]->GetName()) >= 0)
					{
						if (GetTableUpdateContents(pTable[1]->GetName(), -1, GetName(), szItem, szItems))
						{
							UpdateTableContents(pTable[1], szItems);
							continue;
						}
					}
				}
				ArrangeTables(0);
				return TRUE;
			}
		}
		return FALSE;
	}
	SetActiveCell();
	ArrangeTables(0);
	return TRUE;
}

VOID CDisplayTableView::RepositionTables(CONST CTableViewObjects *pTables, LPCTSTR pszTable, INT nOffset)
{
	INT  nTable;
	INT  nTables;
	CRect  rTable;
	CString  szTable;
	CTableViewObject  *pTable;

	for (nTable = 0, nTables = (nOffset != 0) ? (INT)pTables->GetSize() : 0; nTable < nTables; nTable++)
	{
		if ((pTable = pTables->GetAt(nTable)) && GetTablePosition(pTable->GetName(), szTable, rTable) && !szTable.Compare(pszTable))
		{
			RepositionTables(pTables, pTable->GetName(), nOffset);
			pTable->OffsetCells(0, nOffset);
			pTable->OffsetRect(0, nOffset);
		}
	}
}
VOID CDisplayTableView::RepositionTables(CONST CTableViewObjects *pTables, LPCTSTR pszTable, CStringArray &szTables)
{
	INT  nTable;
	INT  nTables;
	INT  nOffset;
	CRect  rTable[3];
	CString  szTable;
	CTableViewObject  *pTable[2];

	if ((pTable[0] = pTables->GetAt(pTables->Find(pszTable))))
	{
		for (nTable = 0, nTables = (INT)szTables.GetSize(); nTable < nTables; nTable++)
		{
			if (!szTables.GetAt(nTable).Compare(pszTable)) break;
			continue;
		}
		for (; nTable == nTables; )
		{
			szTables.Add(pszTable);
			break;
		}
		for (nTable = 0, nTables = (INT)szTables.GetSize(), rTable[0].SetRect(pTable[0]->TopLeft(), pTable[0]->BottomRight()), rTable[0].InflateRect(DATABASETABLEVIEW_TABLE_DISTANCE / 2 - 1, DATABASETABLEVIEW_TABLE_DISTANCE / 2 - 1); nTable < nTables; nTable++)
		{
			if ((pTable[1] = pTables->GetAt(pTables->Find(szTables.GetAt(nTable)))) && pTable[0]->GetName() != pTable[1]->GetName() && pTable[1]->IsVisible())
			{
				rTable[1].SetRect(pTable[1]->TopLeft(), pTable[1]->BottomRight());
				rTable[1].InflateRect(DATABASETABLEVIEW_TABLE_DISTANCE / 2 - 1, 0);
				rTable[1].InflateRect(0, DATABASETABLEVIEW_TABLE_DISTANCE / 2 - 1);
				if (rTable[2].IntersectRect(rTable[0], rTable[1]))
				{
					if (CalcTableOrder(pTables, pTable[0]->GetName()) > CalcTableOrder(pTables, pTable[1]->GetName()))
					{
						if ((nOffset = pTable[1]->bottom - pTable[0]->top + DATABASETABLEVIEW_TABLE_DISTANCE) != 0)
						{
							RepositionTables(pTables, pTable[0]->GetName(), nOffset);
							pTable[0]->OffsetCells(0, nOffset);
							pTable[0]->OffsetRect(0, nOffset);
							rTable[0].OffsetRect(0, nOffset);
							nTable = -1;
						}
						continue;
					}
					RepositionTables(pTables, pTable[1]->GetName(), szTables);
				}
			}
		}
		for (nTable = 0, nTables = (INT)m_szTables.GetSize(); nTable < nTables; nTable++)
		{
			if ((pTable[1] = pTables->GetAt(pTables->Find(m_szTables.GetAt(nTable)))) && pTable[0]->GetName() != pTable[1]->GetName() && pTable[1]->IsVisible())
			{
				if (GetTablePosition(pTable[1]->GetName(), szTable, rTable[2]) && !szTable.Compare(pszTable) && rTable[2].left*rTable[2].top == 0 && rTable[2].right*rTable[2].bottom == 0)
				{
					RepositionTables(pTables, pTable[1]->GetName(), szTables);
					continue;
				}
			}
		}
	}
}

BOOL CDisplayTableView::InsertTableRow(CTableViewObject *pTable, INT nRow)
{
	INT  nCol;
	INT  nCols;
	INT  nRows;
	INT  nMargin;
	INT  nSize[2];
	INT  nStyle[2];
	BOOL  bResize;
	BOOL  bVisible;
	CRect  rTable;
	CRect  rCell[2];
	LOGFONT  lfFont[2];
	COLORREF  nColor[2];
	COLORREF  nTitleRowColor;
	COLORREF  nFirstRowColor;
	COLORREF  nFirstColumnColor;
	COLORREF  nTitleFontColor;
	COLORREF  nItemsFontColor;
	CUIntArray  nIDs;
	CUIntArray  nFormats;
	CStringArray  szItems[2];
	CStringArray  szDataTypes;
	CStringArray  szDescriptions;
	CTableViewCell  *pCell[2];
	CDisplayTableViewUndoItem  cUndoItem;

	for (GetTableOutlineFonts(pTable->GetName(), &lfFont[0], &lfFont[1]); pTable->InsertRow(nRow) && GetTableContents(pTable->GetName(), GetName(), 1, szItems[0], szDescriptions, szDataTypes, nFormats, nIDs, bResize, bVisible) && GetTableOutline(pTable->GetName(), nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nSize[0], nStyle[0], nColor[0], nSize[1], nStyle[1], nColor[1]); )
	{
		for (nCol = 0, nCols = pTable->GetColumns(), nRows = pTable->GetRows(), RecalcTableRow(pTable, nRow); nCol < nCols; nCol++)
		{
			if ((pCell[1] = ((pCell[0] = pTable->FindCell(0, nCol))) ? pTable->FindCell(nRow, nCol) : (CTableViewCell *)NULL))
			{
				if (pTable->GetType() == TAS_TABLE_LIST)
				{
					for (pCell[1]->SetFormat(nFormats.GetAt(nCol)), pCell[1]->SetControlID(nIDs.GetAt(nCol)), pCell[1]->SetBackgroundColor((nCol > 0) ? pCell[1]->GetBackgroundColor() : nFirstColumnColor); pCell[1]->CreateControl(); )
					{
						EnumTableCellValues(pTable, pCell[1], pCell[0]->GetText());
						LimitTableCellValues(pTable, pCell[1], pCell[0]->GetText());
						break;
					}
				}
				for (; pTable->GetType() == TAS_TABLE_NORMAL; )
				{
					pCell[1]->SetBackgroundColor((nRow != 1) ? pCell[1]->GetBackgroundColor() : nFirstRowColor);
					break;
				}
				for (pCell[1]->SetBackgroundColor((!pTable->HasTitle() || nRow > 0) ? pCell[1]->GetBackgroundColor() : nTitleRowColor), pCell[1]->SetBorder(TAS_BORDER_LEFT, (!nCol) ? nSize[0] : nSize[1], (!nCol) ? nStyle[0] : nStyle[1], (!nCol) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_TOP, (!nRow) ? nSize[0] : nSize[1], (!nRow) ? nStyle[0] : nStyle[1], (!nRow) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_RIGHT, (nCol == nCols - 1) ? nSize[0] : nSize[1], (nCol == nCols - 1) ? nStyle[0] : nStyle[1], (nCol == nCols - 1) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_BOTTOM, (nRow == nRows - 1) ? nSize[0] : nSize[1], (nRow == nRows - 1) ? nStyle[0] : nStyle[1], (nRow == nRows - 1) ? nColor[0] : nColor[1]), pCell[1]->SetFont(&lfFont[1]), rCell[0] = pCell[0]->GetPosition(), rCell[1] = pCell[1]->GetPosition(), rCell[1].SetRect(rCell[0].left, rCell[1].top, rCell[0].right, rCell[1].bottom), pCell[1]->SetPosition(rCell[1]), nMargin = CalcDefaultTableMargin(pTable); !nCol || nCol == nCols - 1; )
				{
					rCell[1].SetRect((!nCol) ? (rCell[1].left + nSize[0] + nMargin) : (rCell[1].left + nMargin), rCell[1].top + nSize[1], (nCol > 0) ? (rCell[1].right - nSize[0] - nMargin) : (rCell[1].right - nMargin), (nRow == nRows - 1) ? (rCell[1].bottom - (nSize[0] + 1) / 2) : (rCell[1].bottom - nSize[1]));
					pCell[1]->SetInnerPosition(rCell[1]);
					break;
				}
				if (nCol > 0 && nCol < nCols - 1)
				{
					rCell[1].DeflateRect(nMargin, nSize[1], nMargin, (nRow == nRows - 1) ? ((nSize[0] + 1) / 2) : nSize[1]);
					pCell[1]->SetInnerPosition(rCell[1]);
				}
				continue;
			}
			break;
		}
		rTable = pTable->GetCellsBounds();
		rTable.InflateRect(0, 0, (!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN + (DATABASETABLEVIEW_TABLE_OUTERBORDERSIZE + 1) / 2) : 0, (!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN + (DATABASETABLEVIEW_TABLE_OUTERBORDERSIZE + 1) / 2) : 0);
		pTable->SetRect(rTable.left, rTable.top, rTable.right, rTable.bottom);
		cUndoItem.SetCell(pTable->GetName(), CPoint(-1, nRow + 1));
		m_cUndoList.Add(&cUndoItem);
		return(nCol == nCols);
	}
	return FALSE;
}

BOOL CDisplayTableView::RemoveTableRow(CTableViewObject *pTable, INT nRow)
{
	INT  nIndex;
	INT  nCount;
	INT  nTable;
	INT  nTables;
	INT  nMinRows;
	INT  nMaxRows;
	CRect  rTable;
	CString  szTable;
	CTableViewObject  *pFloatingTable;

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(); nTable < nTables; nTable++)
	{
		if ((pFloatingTable = m_pTables->GetAt(nTable)) && pFloatingTable->GetType() == TAS_TABLE_LIST  &&  GetTablePosition(pFloatingTable->GetName(), szTable, rTable) && pTable->GetName() == szTable && ((rTable.left == nRow  &&  !rTable.top) || (rTable.right == nRow  &&  !rTable.bottom)))
		{
			for (nIndex = 0, nCount = pFloatingTable->GetRows(), GetTableOutlineLimits(pFloatingTable->GetName(), nMinRows, nMaxRows); (!pFloatingTable->HasTitle() && nIndex < nCount) || (pFloatingTable->HasTitle() && nIndex < nCount - 1); nIndex++)
			{
				RemoveTableRow(pFloatingTable, nCount - nIndex - 1);
				nIndex--;
				nCount--;
			}
			for (nIndex = 0, nCount = nMinRows; nIndex < nCount - 1; nIndex++)
			{
				if (!InsertTableRow(pFloatingTable, (pFloatingTable->HasTitle()) ? (nIndex + 1) : nIndex)) break;
				continue;
			}
		}
	}
	return DeleteTableRow(pTable, nRow);
}

BOOL CDisplayTableView::DeleteTableRow(CTableViewObject *pTable, INT nRow)
{
	INT  nCol;
	INT  nCols;
	INT  nSize[2];
	INT  nStyle[2];
	CRect  rTable;
	CString  szRow;
	COLORREF  nColor[2];
	COLORREF  nTitleRowColor;
	COLORREF  nFirstRowColor;
	COLORREF  nFirstColumnColor;
	COLORREF  nTitleFontColor;
	COLORREF  nItemsFontColor;
	CTableViewCell  *pCell;
	CDisplayTableViewUndoItem  cUndoItem;

	for (nCol = 0, nCols = pTable->GetColumns(); nCol < nCols; nCol++)
	{
		if ((pCell = pTable->FindCell(nRow, nCol)))
		{
			for (; pCell == GetActiveCell(); )
			{
				SetActiveCell();
				break;
			}
			szRow += (nCol > 0) ? (TAB + pCell->GetText()) : pCell->GetText();
		}
	}
	if (pTable->RemoveRow(nRow))
	{
		if (GetTableOutline(pTable->GetName(), nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nSize[0], nStyle[0], nColor[0], nSize[1], nStyle[1], nColor[1]))
		{
			pTable->SetOuterBorder(nSize[0], nStyle[0], nColor[0]);
			pTable->SetInnerBorder(nSize[1], nStyle[1], nColor[1]);
			rTable = pTable->GetCellsBounds();
			rTable.InflateRect(0, 0, (!IsSubTable(pTable)) ? DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN : 0, (!IsSubTable(pTable)) ? DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN : 0);
			pTable->SetRect(rTable.left, rTable.top, rTable.right, rTable.bottom);
			cUndoItem.SetInfo(pTable->GetName(), CPoint(-1, -nRow - 1), GetTableFloatingAlignment(pTable->GetName()), szRow, EMPTYSTRING);
			m_cUndoList.Add(&cUndoItem);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDisplayTableView::ResizeTableColumns(CTableViewObject *pTable, INT nCount)
{
	INT  nRow;
	INT  nRows;
	INT  nCol;
	INT  nCols;
	INT  nMargin;
	INT  nSize[2];
	INT  nStyle[2];
	BOOL  bResize;
	BOOL  bVisible;
	CRect  rTable;
	CRect  rCell[2];
	CString  szTitle;
	LOGFONT  lfFont[2];
	COLORREF  nColor[2];
	COLORREF  nTitleRowColor;
	COLORREF  nFirstRowColor;
	COLORREF  nFirstColumnColor;
	COLORREF  nTitleFontColor;
	COLORREF  nItemsFontColor;
	CUIntArray  nIDs;
	CUIntArray  nFormats;
	CStringArray  szItems[3];
	CStringArray  szDataTypes;
	CStringArray  szDescriptions;
	CTableViewCell  *pCell[2];

	for (nCol = pTable->GetColumns(), nCols = (GetTableTitle(pTable->GetName(), szTitle) && GetTableContents(pTable->GetName(), GetName(), -1, szItems[0], szDescriptions, szDataTypes, nFormats, nIDs, bResize, bVisible) && GetTableOutline(pTable->GetName(), nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nSize[0], nStyle[0], nColor[0], nSize[1], nStyle[1], nColor[1])) ? nCount : -1, GetTableOutlineFonts(pTable->GetName(), &lfFont[0], &lfFont[1]); nCol < nCols; nCol++)
	{
		for (nRow = 0, nRows = (pTable->InsertColumn(nCol)) ? pTable->GetRows() : -1, RecalcTableRow(pTable, nRow); nRow < nRows; nRow++)
		{
			if ((pCell[1] = ((pCell[0] = pTable->FindCell(0, nCol))) ? pTable->FindCell(nRow, nCol) : (CTableViewCell *)NULL))
			{
				if (nRow == 0 && szTitle.GetLength() > 0)
				{
					pCell[1]->SetFormat(TAS_TYPE_TEXT | TAS_ALIGN_LEFT | TAS_ALIGN_VCENTER);
					pCell[1]->SetTextStyle(TRANSPARENT, m_nTableFontColors[0], m_nTableColors[0]);
					pCell[1]->SetText((nCol < szItems[1].GetSize()) ? szItems[1].GetAt(nCol) : EMPTYSTRING);
				}
				if (nRow > 0 || szTitle.IsEmpty())
				{
					if (pTable->GetType() == TAS_TABLE_LIST)
					{
						for (pCell[1]->SetFormat(nFormats.GetAt(nCol)), pCell[1]->SetControlID(nIDs.GetAt(nCol)), pCell[1]->SetBackgroundColor((nCol > 0) ? pCell[1]->GetBackgroundColor() : nFirstColumnColor); (pCell[1]->GetFormat() & TAS_TYPE_TIMESPINBOX) && nRow < szItems[0].GetSize() && nCol < ExtractTextItems(szItems[0].GetAt(nRow), szItems[2]); )
						{
							pCell[1]->SetText(szItems[2].GetAt(nCol));
							break;
						}
						if (pCell[1]->CreateControl())
						{
							EnumTableCellValues(pTable, pCell[1], pCell[0]->GetText());
							LimitTableCellValues(pTable, pCell[1], pCell[0]->GetText());
						}
					}
					for (; pTable->GetType() == TAS_TABLE_NORMAL; )
					{
						pCell[1]->SetBackgroundColor((nRow != 1) ? pCell[1]->GetBackgroundColor() : nFirstRowColor);
						break;
					}
				}
				for (pCell[1]->SetBackgroundColor((!pTable->HasTitle() || nRow > 0) ? pCell[1]->GetBackgroundColor() : nTitleRowColor), pCell[1]->SetBorder(TAS_BORDER_LEFT, (!nCol) ? nSize[0] : nSize[1], (!nCol) ? nStyle[0] : nStyle[1], (!nCol) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_TOP, (!nRow) ? nSize[0] : nSize[1], (!nRow) ? nStyle[0] : nStyle[1], (!nRow) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_RIGHT, (nCol == nCols - 1) ? nSize[0] : nSize[1], (nCol == nCols - 1) ? nStyle[0] : nStyle[1], (nCol == nCols - 1) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_BOTTOM, (nRow == nRows - 1) ? nSize[0] : nSize[1], (nRow == nRows - 1) ? nStyle[0] : nStyle[1], (nRow == nRows - 1) ? nColor[0] : nColor[1]), pCell[1]->SetFont(&lfFont[1]), rCell[0] = pCell[0]->GetPosition(), rCell[1] = pCell[1]->GetPosition(), rCell[1].SetRect(rCell[0].left, rCell[1].top, rCell[0].right, rCell[1].bottom), pCell[1]->SetPosition(rCell[1]), nMargin = CalcDefaultTableMargin(pTable); !nCol || nCol == nCols - 1; )
				{
					rCell[1].SetRect((!nCol) ? (rCell[1].left + nSize[0] + nMargin) : (rCell[1].left + nMargin), rCell[1].top + nSize[1], (nCol > 0) ? (rCell[1].right - nSize[0] - nMargin) : (rCell[1].right - nMargin), (nRow == nRows - 1) ? (rCell[1].bottom - (nSize[0] + 1) / 2) : (rCell[1].bottom - nSize[1]));
					pCell[1]->SetInnerPosition(rCell[1]);
					break;
				}
				if (nCol > 0 && nCol < nCols - 1)
				{
					rCell[1].DeflateRect(nMargin, nSize[1], nMargin, (nRow == nRows - 1) ? ((nSize[0] + 1) / 2) : nSize[1]);
					pCell[1]->SetInnerPosition(rCell[1]);
				}
				continue;
			}
			break;
		}
		if (nRow != nRows) break;
	}
	for (nCols = (nCol == nCols) ? pTable->GetColumns() : -1; nCols > nCount; nCol = nCols = nCols - 1)
	{
		if (!pTable->RemoveColumn(nCols - 1))
		{
			nCols = -1;
			break;
		}
	}
	rTable = pTable->GetCellsBounds();
	rTable.InflateRect(0, 0, (!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN + (DATABASETABLEVIEW_TABLE_OUTERBORDERSIZE + 1) / 2) : 0, (!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN + (DATABASETABLEVIEW_TABLE_OUTERBORDERSIZE + 1) / 2) : 0);
	pTable->SetRect(rTable.left, rTable.top, rTable.right, rTable.bottom);
	return((nCol == nCols) ? TRUE : FALSE);
}

BOOL CDisplayTableView::InsertTableColumn(CTableViewObject *pTable, INT nCol)
{
	INT  nRow;
	INT  nRows;
	INT  nCols;
	INT  nMargin;
	INT  nSize[2];
	INT  nStyle[2];
	BOOL  bResize;
	BOOL  bVisible;
	CRect  rTable;
	CRect  rCell[2];
	CString  szTitle;
	LOGFONT  lfFont[2];
	COLORREF  nColor[2];
	COLORREF  nTitleRowColor;
	COLORREF  nFirstRowColor;
	COLORREF  nFirstColumnColor;
	COLORREF  nTitleFontColor;
	COLORREF  nItemsFontColor;
	CUIntArray  nIDs;
	CUIntArray  nFormats;
	CStringArray  szItems[3];
	CStringArray  szDataTypes;
	CStringArray  szDescriptions;
	CTableViewCell  *pCell[2];
	CDisplayTableViewUndoItem  cUndoItem;

	for (GetTableOutlineFonts(pTable->GetName(), &lfFont[0], &lfFont[1]); pTable->InsertColumn(nCol) && GetTableTitle(pTable->GetName(), szTitle) && GetTableContents(pTable->GetName(), GetName(), -1, szItems[0], szDescriptions, szDataTypes, nFormats, nIDs, bResize, bVisible) && GetTableOutline(pTable->GetName(), nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nSize[0], nStyle[0], nColor[0], nSize[1], nStyle[1], nColor[1]); )
	{
		for (nRow = 0, nRows = pTable->GetRows(), nCols = pTable->GetColumns(), RecalcTableRow(pTable, nRow), ExtractTextItems(szTitle, szItems[1]); nRow < nRows; nRow++)
		{
			if ((pCell[1] = ((pCell[0] = pTable->FindCell(0, nCol))) ? pTable->FindCell(nRow, nCol) : (CTableViewCell *)NULL))
			{
				if (nRow == 0 && szTitle.GetLength() > 0)
				{
					pCell[1]->SetFormat(TAS_TYPE_TEXT | TAS_ALIGN_LEFT | TAS_ALIGN_VCENTER);
					pCell[1]->SetTextStyle(TRANSPARENT, m_nTableFontColors[0], m_nTableColors[0]);
					pCell[1]->SetText((nCol < szItems[1].GetSize()) ? szItems[1].GetAt(nCol) : EMPTYSTRING);
				}
				if (nRow > 0 || szTitle.IsEmpty())
				{
					if (pTable->GetType() == TAS_TABLE_LIST)
					{
						for (pCell[1]->SetFormat((nCol < nFormats.GetSize()) ? nFormats.GetAt(nCol) : ((nFormats.GetSize() > 0) ? nFormats.GetAt(nFormats.GetUpperBound()) : pCell[1]->GetFormat())), pCell[1]->SetControlID((nCol < nIDs.GetSize()) ? nIDs.GetAt(nCol) : ((nIDs.GetSize() > 0) ? nIDs.GetAt(nIDs.GetUpperBound()) : 0)), pCell[1]->SetBackgroundColor((nCol > 0) ? pCell[1]->GetBackgroundColor() : nFirstColumnColor); (pCell[1]->GetFormat() & TAS_TYPE_TIMESPINBOX) && nRow < szItems[0].GetSize() && nCol < ExtractTextItems(szItems[0].GetAt(nRow), szItems[2]); )
						{
							pCell[1]->SetText(szItems[2].GetAt(nCol));
							break;
						}
						if (pCell[1]->CreateControl())
						{
							EnumTableCellValues(pTable, pCell[1], pCell[0]->GetText());
							LimitTableCellValues(pTable, pCell[1], pCell[0]->GetText());
						}
					}
					for (; pTable->GetType() == TAS_TABLE_NORMAL; )
					{
						pCell[1]->SetBackgroundColor((nRow != 1) ? pCell[1]->GetBackgroundColor() : nFirstRowColor);
						break;
					}
				}
				for (pCell[1]->SetBackgroundColor((!pTable->HasTitle() || nRow > 0) ? pCell[1]->GetBackgroundColor() : nTitleRowColor), pCell[1]->SetBorder(TAS_BORDER_LEFT, (!nCol) ? nSize[0] : nSize[1], (!nCol) ? nStyle[0] : nStyle[1], (!nCol) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_TOP, (!nRow) ? nSize[0] : nSize[1], (!nRow) ? nStyle[0] : nStyle[1], (!nRow) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_RIGHT, (nCol == nCols - 1) ? nSize[0] : nSize[1], (nCol == nCols - 1) ? nStyle[0] : nStyle[1], (nCol == nCols - 1) ? nColor[0] : nColor[1]), pCell[1]->SetBorder(TAS_BORDER_BOTTOM, (nRow == nRows - 1) ? nSize[0] : nSize[1], (nRow == nRows - 1) ? nStyle[0] : nStyle[1], (nRow == nRows - 1) ? nColor[0] : nColor[1]), pCell[1]->SetFont(&lfFont[1]), rCell[0] = pCell[0]->GetPosition(), rCell[1] = pCell[1]->GetPosition(), rCell[1].SetRect(rCell[0].left, rCell[1].top, rCell[0].right, rCell[1].bottom), pCell[1]->SetPosition(rCell[1]), nMargin = CalcDefaultTableMargin(pTable); !nCol || nCol == nCols - 1; )
				{
					rCell[1].SetRect((!nCol) ? (rCell[1].left + nSize[0] + nMargin) : (rCell[1].left + nMargin), rCell[1].top + nSize[1], (nCol > 0) ? (rCell[1].right - nSize[0] - nMargin) : (rCell[1].right - nMargin), (nRow == nRows - 1) ? (rCell[1].bottom - (nSize[0] + 1) / 2) : (rCell[1].bottom - nSize[1]));
					pCell[1]->SetInnerPosition(rCell[1]);
					break;
				}
				if (nCol > 0 && nCol < nCols - 1)
				{
					rCell[1].DeflateRect(nMargin, nSize[1], nMargin, (nRow == nRows - 1) ? ((nSize[0] + 1) / 2) : nSize[1]);
					pCell[1]->SetInnerPosition(rCell[1]);
				}
				continue;
			}
			break;
		}
		rTable = pTable->GetCellsBounds();
		rTable.InflateRect(0, 0, (!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN + (DATABASETABLEVIEW_TABLE_OUTERBORDERSIZE + 1) / 2) : 0, (!IsSubTable(pTable)) ? (DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN + (DATABASETABLEVIEW_TABLE_OUTERBORDERSIZE + 1) / 2) : 0);
		pTable->SetRect(rTable.left, rTable.top, rTable.right, rTable.bottom);
		cUndoItem.SetCell(pTable->GetName(), CPoint(nCol + 1, -1));
		m_cUndoList.Add(&cUndoItem);
		return(nRow == nRows);
	}
	return FALSE;
}

BOOL CDisplayTableView::DeleteTableColumn(CTableViewObject *pTable, INT nCol)
{
	INT  nRow;
	INT  nRows;
	INT  nSize[2];
	INT  nStyle[2];
	CRect  rTable;
	CString  szCol;
	COLORREF  nColor[2];
	COLORREF  nTitleRowColor;
	COLORREF  nFirstRowColor;
	COLORREF  nFirstColumnColor;
	COLORREF  nTitleFontColor;
	COLORREF  nItemsFontColor;
	CTableViewCell  *pCell;
	CDisplayTableViewUndoItem  cUndoItem;

	for (nRow = 0, nRows = pTable->GetRows(); nRow < nRows; nRow++)
	{
		if ((pCell = pTable->FindCell(nRow, nCol)))
		{
			for (; pCell == GetActiveCell(); )
			{
				SetActiveCell();
				break;
			}
			szCol += (nRow > 0) ? (TAB + pCell->GetText()) : pCell->GetText();
		}
	}
	if (pTable->RemoveColumn(nCol))
	{
		if (GetTableOutline(pTable->GetName(), nTitleRowColor, nFirstRowColor, nFirstColumnColor, nTitleFontColor, nItemsFontColor, nSize[0], nStyle[0], nColor[0], nSize[1], nStyle[1], nColor[1]))
		{
			pTable->SetOuterBorder(nSize[0], nStyle[0], nColor[0]);
			pTable->SetInnerBorder(nSize[1], nStyle[1], nColor[1]);
			rTable = pTable->GetCellsBounds();
			rTable.InflateRect(0, 0, (!IsSubTable(pTable)) ? DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN : 0, (!IsSubTable(pTable)) ? DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN : 0);
			pTable->SetRect(rTable.left, rTable.top, rTable.right, rTable.bottom);
			cUndoItem.SetInfo(pTable->GetName(), CPoint(-nCol - 1, -1), GetTableFloatingAlignment(pTable->GetName()), szCol, EMPTYSTRING);
			m_cUndoList.Add(&cUndoItem);
			return TRUE;
		}
	}
	return FALSE;
}

INT CDisplayTableView::CalcTableOrder(CONST CTableViewObjects *pTables, LPCTSTR pszTable) CONST
{
	INT  nOrder;

	CalcTableOrder(pTables, pszTable, (nOrder = 0));
	return nOrder;
}
VOID CDisplayTableView::CalcTableOrder(CONST CTableViewObjects *pTables, LPCTSTR pszTable, INT &nOrder) CONST
{
	for (nOrder = 0; nOrder < (INT)m_szTables.GetSize(); nOrder++)
	{
		if (m_szTables.GetAt(nOrder) == pszTable) break;
		continue;
	}
}

INT CDisplayTableView::CalcDefaultTableWidth(CONST CTableViewObject *pTable)
{
	INT  nCol;
	INT  nCols;
	INT  nWidth;
	INT  nBorderSize[2];
	INT  nBorderStyle[2];
	COLORREF  nColor[7];
	CUIntArray  nWidths;
	CTableViewCell  *pCell;

	for (nCol = 0, nCols = (GetTableLayout(pTable->GetName(), nWidths) && GetTableOutline(pTable->GetName(), nColor[0], nColor[1], nColor[2], nColor[3], nColor[4], nBorderSize[0], nBorderStyle[0], nColor[5], nBorderSize[1], nBorderStyle[1], nColor[6])) ? (INT)min(pTable->GetColumns(), nWidths.GetSize()) : 0, nWidth = 2 * nBorderSize[0]; nCol < nCols; nCol++)
	{
		if ((pCell = pTable->FindCell(0, nCol)) != (CTableViewCell *)NULL)
		{
			nWidth += CalcDefaultCellWidth(pCell, nWidths.GetAt(nCol), 0);
			continue;
		}
	}
	return nWidth;
}

INT CDisplayTableView::CalcDefaultTableHeight(CONST CTableViewObject *pTable)
{
	INT  nRow;
	INT  nRows;
	INT  nHeight;
	INT  nBorderSize[2];
	INT  nBorderStyle[2];
	COLORREF  nColor[7];
	CUIntArray  nWidths;
	CTableViewCell  *pCell;

	for (nRow = 0, nRows = (GetTableLayout(pTable->GetName(), nWidths) && GetTableOutline(pTable->GetName(), nColor[0], nColor[1], nColor[2], nColor[3], nColor[4], nBorderSize[0], nBorderStyle[0], nColor[5], nBorderSize[1], nBorderStyle[1], nColor[6])) ? pTable->GetRows() : 0, nHeight = 2 * nBorderSize[0]; nRow < nRows; nRow++)
	{
		nHeight += ((pCell = pTable->FindCell(nRow, 0))) ? CalcDefaultCellHeight(pCell, pCell->GetInnerPosition().Width()) : 0;
		continue;
	}
	return nHeight;
}

INT CDisplayTableView::CalcDefaultTableMargin(CONST CTableViewObject *pTable)
{
	CDC  *pDC;
	CFont  cFont;
	CFont  *pOldFont;
	LOGFONT  lfFont[2];
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		for (GetTableOutlineFonts(pTable->GetName(), &lfFont[0], &lfFont[1]); cFont.CreateFontIndirect(&lfFont[0]); )
		{
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				pDC->GetTextMetrics(&tmFont);
				pDC->SelectObject(pOldFont);
				cFont.DeleteObject();
				ReleaseDC(pDC);
				return tmFont.tmHeight / 4;
			}
			cFont.DeleteObject();
			break;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CDisplayTableView::CalcDefaultCellWidth(CONST CTableViewCell *pCell, UINT nColumnWidth, INT nWidth)
{
	CDC  *pDC;
	CFont  cFont;
	CFont  *pOldFont;
	LOGFONT  lfFont[1];
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		for (pCell->GetFont(&lfFont[0]), ZeroMemory(&tmFont, sizeof(tmFont)); cFont.CreateFontIndirect(&lfFont[0]); )
		{
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				pDC->GetTextMetrics(&tmFont);
				pDC->SelectObject(pOldFont);
			}
			break;
		}
		ReleaseDC(pDC);
		return((nColumnWidth != (UINT)-1) ? (((pCell->GetFormat() & TAS_TYPE_COMBOLISTBOX) || (pCell->GetFormat() & TAS_TYPE_COMBOEDITBOX) || (pCell->GetFormat() & TAS_TYPE_COMBOCOLORSBOX) || (pCell->GetFormat() & TAS_TYPE_COMBOLINESTYLESBOX) || (pCell->GetFormat() & TAS_TYPE_COMBOLINESYMBOLSBOX)) ? max(GetSystemMetrics(SM_CXVSCROLL) + (INT)nColumnWidth*tmFont.tmAveCharWidth, nWidth) : max((INT)nColumnWidth*tmFont.tmAveCharWidth, nWidth)) : nWidth);
	}
	return nWidth;
}

INT CDisplayTableView::CalcDefaultCellHeight(CONST CTableViewCell *pCell, INT nWidth)
{
	return CalcDefaultCellHeight(m_pTables, pCell, nWidth);
}
INT CDisplayTableView::CalcDefaultCellHeight(CONST CTableViewObjects *pTables, CONST CTableViewCell *pCell, INT nWidth)
{
	CDC  *pDC;
	INT  nSize[2];
	INT  nStyle[2];
	INT  nHeight[2];
	CRect  rCell[3];
	CFont  cFont[1];
	CFont  *pOldFont;
	LOGFONT  lfFont[1];
	COLORREF  nColor[2];
	TEXTMETRIC  tmFont;
	CTableViewObject  *pTable;

	if ((pDC = GetDC()))
	{
		for (pCell->GetFont(&lfFont[0]), ZeroMemory(&tmFont, sizeof(tmFont)), nHeight[0] = nHeight[1] = 0; cFont[0].CreateFontIndirect(&lfFont[0]); )
		{
			if ((pTable = (pCell->GetFormat() & TAS_TYPE_SUBTABLE) ? pTables->GetAt(pTables->Find(pCell->GetSubTable())) : (CTableViewObject *)NULL) && pTable->IsVisible())
			{
				pCell->GetBorder(TAS_BORDER_TOP, nSize[0], nStyle[0], nColor[0]);
				pCell->GetBorder(TAS_BORDER_BOTTOM, nSize[1], nStyle[1], nColor[1]);
				nHeight[0] = pTable->Height() + max(nSize[0] - 1, 0) / 2 + nSize[1] / 2 + 1;
				ReleaseDC(pDC);
				return nHeight[0];
			}
			if ((pOldFont = pDC->SelectObject(&cFont[0])))
			{
				for (rCell[0] = pCell->GetPosition(), rCell[1] = pCell->GetInnerPosition(), pCell->GetBorder(TAS_BORDER_TOP, nSize[0], nStyle[0], nColor[0]), pCell->GetBorder(TAS_BORDER_BOTTOM, nSize[1], nStyle[1], nColor[1]), pDC->GetTextMetrics(&tmFont), pDC->DrawText(((pCell->GetFormat() & TAS_TYPE_TIMESPINBOX) != TAS_TYPE_TIMESPINBOX) ? pCell->GetText() : EMPTYSTRING, (rCell[2] = CRect(0, 0, nWidth, 0)), ((pCell->GetFormat() & TAS_ALIGN_LEFT) ? DT_LEFT : 0) | ((pCell->GetFormat() & TAS_ALIGN_RIGHT) ? DT_RIGHT : 0) | ((pCell->GetFormat() & TAS_ALIGN_HCENTER) ? DT_CENTER : 0) | DT_CALCRECT | DT_TOP | DT_EXPANDTABS | DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_NOPREFIX), nHeight[0] = (nWidth <= 0) ? CalcTableCellExtent(pCell).Height() : rCell[2].Height(), nHeight[0] = max(tmFont.tmHeight, nHeight[0]); TRUE; )
				{
					nHeight[1] = 2 * DATABASETABLEVIEW_TABLE_INNERBORDERMARGIN + max(nSize[0] - 1, 0) / 2 + nSize[1] / 2 + nHeight[0] + 1;
					nHeight[1] += rCell[1].top - rCell[0].top + rCell[0].bottom - rCell[1].bottom;
					break;
				}
				pDC->SelectObject(pOldFont);
			}
			nHeight[1] = max(pCell->GetMinHeight(), nHeight[1]);
			break;
		}
		ReleaseDC(pDC);
		return nHeight[1];
	}
	return 0;
}

VOID CDisplayTableView::ShowTableInfo(CONST POINT &point)
{
	INT  nTable;
	INT  nTables;
	BOOL  bResize;
	BOOL  bVisible;
	CPoint  ptCursor;
	CString  szFlag;
	CString  szType;
	CString  szDetails;
	CUIntArray  nIDs;
	CUIntArray  nFormats;
	CStringArray  szRow[3];
	CTableViewCell  *pCell;
	CTableViewObject  *pTable[2];

	for (nTable = 0, nTables = (INT)m_pTables->GetSize(), ptCursor = CPoint(point) + GetScrollPosition(); nTable < nTables; nTable++)
	{
		if ((pTable[0] = m_pTables->GetAt(nTable)) != (CTableViewObject *)NULL  &&  pTable[0]->IsVisible() && pTable[0]->PtInRect(ptCursor))
		{
			if ((pCell = pTable[0]->FindCell(ptCursor)) && (!(pTable[1] = m_pTables->GetAt(m_pTables->Find(pCell->GetSubTable()))) || !pTable[1]->IsVisible()))
			{
				if (GetTableContents(pTable[0]->GetName(), GetName(), 0, szRow[0], szRow[1], szRow[2], nFormats, nIDs, bResize, bVisible) && GetTableFieldFlag(pTable[0]->GetName(), pCell->y, pCell->x, szFlag))
				{
					if ((pTable[0]->GetType() == TAS_TABLE_NORMAL && ((pTable[0]->GetRows() == szRow[1].GetSize() && pCell->y < szRow[1].GetSize() && pCell->y < szRow[2].GetSize()) || (pTable[0]->GetRows() == szRow[1].GetSize() + 1 && pCell->y > 0 && pCell->y <= szRow[1].GetSize() && pCell->y <= szRow[2].GetSize()))) || (pTable[0]->GetType() == TAS_TABLE_LIST  &&  pCell->x < szRow[1].GetSize() && pCell->x < szRow[2].GetSize()))
					{
						for (szDetails = (pTable[0]->GetType() == TAS_TABLE_NORMAL) ? ((pTable[0]->GetRows() == szRow[1].GetSize() + 1) ? szRow[1].GetAt(pCell->y - 1) : szRow[1].GetAt(pCell->y)) : szRow[1].GetAt(pCell->x), szType = (pTable[0]->GetType() == TAS_TABLE_NORMAL) ? ((pTable[0]->GetRows() == szRow[1].GetSize() + 1) ? szRow[2].GetAt(pCell->y - 1) : szRow[2].GetAt(pCell->y)) : szRow[2].GetAt(pCell->x); (m_nTimerID[2] = SetTimer(DISPLAYTABLEVIEW_UPDATEBARS_TIMERID, DISPLAYTABLEVIEW_UPDATEBARS_TIMEOUT, NULL)) != 0; )
						{
							GetParent()->UpdateAllPanes(szDetails, szFlag, szType);
							break;
						}
						break;
					}
				}
			}
		}
	}
	if (nTable == nTables)
	{
		if (GetPanesInfo(szDetails, szFlag, szType))
		{
			GetParent()->UpdateAllPanes(szDetails, szFlag, szType);
			KillTimer(m_nTimerID[2]);
			m_nTimerID[2] = 0;
		}
	}
}

BOOL CDisplayTableView::CheckPrivilege() CONST
{
	return FALSE;
}

BOOL CDisplayTableView::PreTranslateMessage(MSG *pMsg)
{
	CWnd  *pWnd;
	CPoint  point;

	if ((pWnd = CWnd::FromHandle(pMsg->hwnd)) && IsChild(pWnd))
	{
		if (pMsg->message == WM_MOUSEMOVE)
		{
			ScreenToClient(&(point = pMsg->pt));
			ShowTableInfo(point);
		}
	}
	return FALSE;
}

LRESULT CDisplayTableView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	INT  nTable;
	INT  nTables;
	BOOL  bFocus;
	BOOL  bControl;
	CWnd  *pControl;
	CString  szItem;
	CString  szValue[2];
	CStringArray  szItems;
	CStringArray  szTables;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;
	CDisplayTableViewUndoItem  cUndoItem;

	if (message == WM_COMMAND)
	{
		if ((bFocus = (HIWORD(wParam) == CBN_SETFOCUS || HIWORD(wParam) == EN_SETFOCUS || HIWORD(wParam) == SBXN_SETFOCUS || HIWORD(wParam) == TSBXN_SETFOCUS)))
		{
			if ((pControl = ((pCell = GetActiveCell()) && pCell->GetControlID() == LOWORD(wParam)) ? pCell->GetControl() : (CWnd *)NULL) != (CWnd *)NULL)
			{
				for (ConvertUndoItem(pControl, &cUndoItem, FALSE), m_cUndoList.Add(&cUndoItem), m_cUndoList.Collect(TRUE), szValue[0] = pCell->GetText(); HIWORD(wParam) == TSBXN_SETFOCUS; )
				{
					UpdateTableFieldData(pCell->GetControlID(), szValue[0]);
					break;
				}
				m_cUndoList.Collect(FALSE);
			}
		}
		if (HIWORD(wParam) == CBN_SELCHANGE)
		{
			if ((pControl = ((pCell = GetActiveCell(pTable)) && pCell->GetControlID() == LOWORD(wParam)) ? pCell->GetControl() : (CWnd *)NULL))
			{
				for (szValue[0] = Combobox_GetText(pControl, (INT)pControl->SendMessage(CB_GETCURSEL)), pControl->GetWindowText(szValue[1]); (bControl = ((pControl->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_SIMPLE || (pControl->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_DROPDOWN)); )
				{
					if (EnumTableUpdates(pCell->GetControlID(), szTables) > 0 && !GetTableUpdateContents(pTable->GetName(), 0, GetName(), szItem, szItems))
					{
						for (ConvertUndoItem(pControl, &cUndoItem, TRUE), cUndoItem.SetText(EMPTYSTRING); m_cUndoList.GetSize() > 0; )
						{
							m_cUndoList.Reset();
							break;
						}
						m_cUndoList.Add(&cUndoItem);
					}
					break;
				}
				for (pControl->SetWindowText(Combobox_GetText(pControl, (INT)pControl->SendMessage(CB_GETCURSEL))), ConvertUndoItem(pControl, &cUndoItem, TRUE); bControl; )
				{
					cUndoItem.SetSel(0, cUndoItem.GetText().GetLength());
					break;
				}
				for (nTable = 0, nTables = (!m_cUndoList.IsLocked()) ? EnumTableUpdates(pCell->GetControlID(), szTables) : 0, m_cUndoList.Add(&cUndoItem, TRUE), m_cUndoList.Collect(TRUE), UpdateTableFieldData(LOWORD(wParam), szValue[0], szValue[1]); nTable < nTables; nTable++)
				{
					if ((pTable = (GetTableUpdateContents(szTables.GetAt(nTable), pCell->GetControlID(), szValue[0], szItem, szItems)) ? m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable))) : (CTableViewObject *)NULL)) UpdateTableContents(pTable, szItems);
					if (nTable == nTables - 1) ArrangeTables(0);
				}
				m_cUndoList.Collect(FALSE);
			}
		}
		if (HIWORD(wParam) == EN_UPDATE)
		{
			if ((pControl = ((pCell = GetActiveCell(pTable)) && pCell->GetControlID() == LOWORD(wParam)) ? pCell->GetControl() : (CWnd *)NULL))
			{
				if ((pControl->GetStyle() & ES_MULTILINE) && (pControl->GetStyle() & WS_VSCROLL) == 0)
				{
					RecalcTableRow(pTable, pCell->y, FALSE);
					RepositionTables();
				}
			}
		}
		if (HIWORD(wParam) == CBN_EDITCHANGE || HIWORD(wParam) == EN_CHANGE || HIWORD(wParam) == SBXN_CHANGE || HIWORD(wParam) == TSBXN_CHANGE)
		{
			if ((pControl = ((pCell = GetActiveCell()) && pCell->GetControlID() == LOWORD(wParam)) ? pCell->GetControl() : (CWnd *)NULL))
			{
				for (ConvertUndoItem(pControl, &cUndoItem, FALSE), m_cUndoList.Add(&cUndoItem), m_cUndoList.Collect(TRUE), szValue[0] = pCell->GetText(); szValue[0].GetLength() >= 0; )
				{
					UpdateTableFieldData(pCell->GetControlID(), szValue[0]);
					break;
				}
				m_cUndoList.Collect(FALSE);
			}
		}
		if (HIWORD(wParam) == CBN_KILLFOCUS || HIWORD(wParam) == EN_KILLFOCUS || HIWORD(wParam) == SBXN_KILLFOCUS || HIWORD(wParam) == TSBXN_KILLFOCUS)
		{
			if ((pControl = ((pCell = GetActiveCell()) && pCell->GetControlID() == LOWORD(wParam)) ? pCell->GetControl() : (CWnd *)NULL) != (CWnd *)NULL)
			{
				for (nTable = 0, nTables = ((szValue[0] = pCell->GetText()).IsEmpty()) ? EnumTableUpdates(LOWORD(wParam), szTables) : 0; nTable < nTables; nTable++)
				{
					if ((pTable = (GetTableUpdateContents(szTables.GetAt(nTable), LOWORD(wParam), szValue[0], GetName(), szItems)) ? m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable))) : (CTableViewObject *)NULL)) UpdateTableContents(pTable, szItems);
					if (nTable == nTables - 1) ArrangeTables(0);
				}
			}
		}
		for (DrawTables(); !bFocus; )
		{
			if ((pCell = GetActiveCell(pTable)) && !pTable->IsVisible()) SetActiveCell();
			return TRUE;
		}
	}
	return CScrollView::WindowProc(message, wParam, lParam);
}

void CDisplayTableView::PostNcDestroy()
{
	ClearUndo();
	m_szTables.RemoveAll();
	CDatabaseTableView::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDisplayTableView, CDatabaseTableView)
	//{{AFX_MSG_MAP(CDisplayTableView)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayTableView message handlers

void CDisplayTableView::OnSize(UINT nType, int cx, int cy)
{
	if (GetParent()->IsZoomed()) Invalidate();
	CDatabaseTableView::OnSize(nType, cx, cy);
}

void CDisplayTableView::OnMouseMove(UINT nFlags, CPoint point)
{
	ShowTableInfo(point);
	CDatabaseTableView::OnMouseMove(nFlags, point);
}

void CDisplayTableView::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nTable;
	INT  nTables;
	BOOL  bTable;
	POINT  ptCursor;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;
	CHourglassCursor  cCursor;

	if (CheckPrivilege())
	{
		for (nTable = 0, nTables = (INT)m_pTables->GetSize(), ptCursor = point + GetScrollPosition(), SetActiveCell(), bTable = FALSE; nTable < nTables; nTable++)
		{
			if ((pTable = m_pTables->GetAt(nTable)) && pTable->IsVisible())
			{
				if (pTable->GetType() == TAS_TABLE_LIST  &&  pTable->PtInRect(ptCursor) && !bTable)
				{
					if ((pCell = pTable->FindCell(ptCursor)) && (!pCell->HasInnerPosition() || pCell->GetInnerPosition().PtInRect(ptCursor)) && (pCell->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE && ((!pTable->HasTitle() && !pCell->y) || pCell->y > 0))
					{
						if (SelectTableFieldData(pTable->GetName(), CPoint(pCell->x, pCell->y)))
						{
							bTable = TRUE;
							continue;
						}
					}
				}
				if (pTable->GetType() == TAS_TABLE_LIST)
				{
					pTable->SetSelCell();
					continue;
				}
			}
		}
		for (nTable = 0, nTables = (!bTable) ? (INT)m_pTables->GetSize() : 0; nTable < nTables; nTable++)
		{
			if ((pTable = m_pTables->GetAt(nTable)) && pTable->IsVisible())
			{
				if (pTable->GetSelColumn() >= 0 || pTable->GetSelRow() >= 0)
				{
					SelectTableFieldData(pTable->GetName(), CPoint(-1, -1));
					continue;
				}
			}
		}
		DrawTables();
	}
	CDatabaseTableView::OnLButtonDown(nFlags, point);
}

void CDisplayTableView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	INT  nTable;
	INT  nTables;
	BOOL  bTable;
	POINT  ptCursor;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable;
	CHourglassCursor  cCursor;

	if (CheckPrivilege())
	{
		for (nTable = 0, nTables = (INT)m_pTables->GetSize(), ptCursor = point + GetScrollPosition(), bTable = FALSE; nTable < nTables; nTable++)
		{
			if ((pTable = m_pTables->GetAt(nTable)) != (CTableViewObject *)NULL  &&  pTable->IsVisible())
			{
				if (pTable->GetType() == TAS_TABLE_LIST  &&  pTable->PtInRect(ptCursor) && !bTable)
				{
					if ((pCell = pTable->FindCell(ptCursor)) && (!pCell->HasInnerPosition() || pCell->GetInnerPosition().PtInRect(ptCursor)) && (pCell->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE && ((!pTable->HasTitle() && !pCell->y) || pCell->y > 0))
					{
						if (SelectTableFieldData(pTable->GetName(), CPoint(pCell->x, pCell->y)))
						{
							SetActiveCell(pTable, pCell);
							bTable = TRUE;
							continue;
						}
					}
				}
				if (pTable->GetType() == TAS_TABLE_LIST)
				{
					pTable->SetSelCell();
					DrawTables();
					continue;
				}
				if (pTable->GetType() == TAS_TABLE_NORMAL  &&  pTable->PtInRect(ptCursor) && !bTable)
				{
					if ((pCell = pTable->FindCell(ptCursor)) && (!pCell->HasInnerPosition() || pCell->GetInnerPosition().PtInRect(ptCursor)) && (pCell->GetFormat() & TAS_TYPE_SUBTABLE) != TAS_TYPE_SUBTABLE && ((!pTable->HasTitle() && !pCell->y) || pCell->y > 0))
					{
						SetActiveCell(pTable, pCell);
						bTable = TRUE;
						continue;
					}
				}
			}
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CDisplayTableView::OnRButtonDown(UINT nFlags, CPoint point)
{
	INT  nRow;
	INT  nCol;
	INT  nTable[2];
	INT  nTables[2];
	POINT  ptCursor;
	CUIntArray  nTypes;
	CLocaleMenu  cMenu;
	CStringArray  szTables;
	CTableViewCell  *pCell;
	CTableViewObject  *pTable[3];
	CMFCPopupMenu  *pFloatingMenu;

	for (nTable[0] = 0, nTables[0] = EnumTables(szTables, nTypes, TRUE, FALSE), ptCursor = point + GetScrollPosition(); nTable[0] < nTables[0]; nTable[0]++)
	{
		if ((pTable[0] = m_pTables->GetAt(m_pTables->Find(szTables.GetAt(nTable[0])))) && pTable[0]->IsVisible() && pTable[0]->PtInRect(ptCursor))
		{
			for (nTable[1] = 0, nTables[1] = (INT)m_pTables->GetSize(); nTable[1] < nTables[1]; nTable[1]++)
			{
				if ((pTable[1] = m_pTables->GetAt(nTable[1])) && pTable[0] != pTable[1])
				{
					if ((pCell = GetActiveCell(pTable[2])) && pTable[1] == pTable[2])
					{
						pTable[1]->SetSelCell();
						SetActiveCell();
						break;
					}
					if (pTable[1]->GetSelRow() >= 0)
					{
						pTable[1]->SetSelCell();
						DrawTables();
						break;
					}
				}
			}
			if (!pTable[0]->GetSelCell(nRow, nCol))
			{
				for (nRow = pTable[0]->GetSelRow(); nRow < 0; )
				{
					pTable[0]->SetSelRow(pTable[0]->GetRows());
					break;
				}
			}
			for (ClientToScreen(&point); (pFloatingMenu = (cMenu.LoadMenu(m_nFloatingMenuID)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL); )
			{
				pFloatingMenu->Create(this, point.x, point.y, cMenu.Detach());
				break;
			}
			break;
		}
	}
	CDatabaseTableView::OnRButtonDown(nFlags, point);
}

void CDisplayTableView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nRow;
	INT  nCol;
	INT  nTable;
	INT  nTables;
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
						SelectTableFieldData(pTable[0]->GetName(), CPoint(0, nRow + 1));
						ScrollToTableRow(pTable[0], nRow + 1);
					}
					return;
				}
				if (nChar == VK_UP)
				{
					if ((!pTable[0]->HasTitle() && nRow > 0) || (pTable[0]->HasTitle() && nRow > 1))
					{
						SelectTableFieldData(pTable[0]->GetName(), CPoint(0, nRow - 1));
						ScrollToTableRow(pTable[0], nRow - 1);
					}
					return;
				}
				if (nChar == VK_NEXT)
				{
					ScrollTableRows(pTable[0], TRUE);
					SelectTableFieldData(pTable[0]->GetName(), CPoint(0, pTable[0]->GetSelRow()));
					return;
				}
				if (nChar == VK_PRIOR)
				{
					ScrollTableRows(pTable[0], FALSE);
					SelectTableFieldData(pTable[0]->GetName(), CPoint(0, pTable[0]->GetSelRow()));
					return;
				}
				if (nChar == VK_END)
				{
					if ((!pTable[0]->HasTitle() && pTable[0]->GetRows() > 0) || (pTable[0]->HasTitle() && pTable[0]->GetRows() > 1))
					{
						SelectTableFieldData(pTable[0]->GetName(), CPoint(0, pTable[0]->GetRows() - 1));
						ScrollToTableRow(pTable[0], pTable[0]->GetSelRow());
					}
					return;
				}
			}
			if ((nCol = pTable[0]->GetSelColumn()) >= 0)
			{
				if (nChar == VK_RIGHT)
				{
					if (nCol < pTable[0]->GetColumns() - 1)
					{
						SelectTableFieldData(pTable[0]->GetName(), CPoint(nCol + 1, 0));
						ScrollToTableColumn(pTable[0], nCol + 1);
					}
					return;
				}
				if (nChar == VK_LEFT)
				{
					if (nCol > 0)
					{
						SelectTableFieldData(pTable[0]->GetName(), CPoint(nCol - 1, 0));
						ScrollToTableColumn(pTable[0], nCol - 1);
					}
					return;
				}
				if (nChar == VK_END)
				{
					if (pTable[0]->GetColumns() > 0)
					{
						SelectTableFieldData(pTable[0]->GetName(), CPoint(pTable[0]->GetColumns() - 1, 0));
						ScrollToTableColumn(pTable[0], pTable[0]->GetSelColumn());
					}
					return;
				}
			}
		}
	}
	CTableView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDisplayTableView::OnSetFocus(CWnd *pOldWnd)
{
	CWnd  *pControl;
	CTableViewCell  *pCell;

	for (; (pControl = ((pCell = GetActiveCell())) ? pCell->GetControl() : (CWnd *)NULL) && !IsChild(pOldWnd); )
	{
		m_nTimerID[0] = SetTimer(DISPLAYTABLEVIEW_ACTIVATION_TIMERID, DISPLAYTABLEVIEW_ACTIVATION_TIMEOUT, NULL);
		break;
	}
	CScrollView::OnSetFocus(pOldWnd);
}

void CDisplayTableView::OnTimer(UINT_PTR nEventID)
{
	CWnd  *pWnd;
	CWnd  *pControl;
	POINT  ptCursor;
	CString  szFlag;
	CString  szType;
	CString  szDetails;
	CTableViewCell  *pCell;

	if (nEventID == DISPLAYTABLEVIEW_ACTIVATION_TIMERID)
	{
		for (EnableUndo(FALSE), KillTimer(m_nTimerID[0]), m_nTimerID[0] = 0; (pControl = ((pCell = GetActiveCell())) ? pCell->GetControl() : (CWnd *)NULL); )
		{
			pControl->SetFocus();
			break;
		}
		EnableUndo(TRUE);
	}
	if (nEventID == DISPLAYTABLEVIEW_UPDATEFORM_TIMERID)
	{
		KillTimer(m_nTimerID[1]);
		m_nTimerID[1] = 0;
	}
	if (nEventID == DISPLAYTABLEVIEW_UPDATEBARS_TIMERID)
	{
		for (GetCursorPos(&ptCursor), KillTimer(m_nTimerID[2]), m_nTimerID[2] = 0; (pWnd = WindowFromPoint(ptCursor)) && pWnd->GetSafeHwnd() != GetSafeHwnd() && !IsChild(pWnd); )
		{
			if (GetPanesInfo(szDetails, szFlag, szType)) GetParent()->UpdateAllPanes(szDetails, szFlag, szType);
			break;
		}
	}
	CDatabaseTableView::OnTimer(nEventID);
}

void CDisplayTableView::OnDestroy()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)(sizeof(m_nTimerID) / sizeof(m_nTimerID[0])); nIndex < nCount; nIndex++)
	{
		if (m_nTimerID[nIndex] != 0)
		{
			KillTimer(m_nTimerID[nIndex]);
			m_nTimerID[nIndex] = 0;
		}
	}
	CDatabaseTableView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd

IMPLEMENT_DYNCREATE(CDisplayWnd, CLocaleMDIChildWnd)

CDisplayWnd::CDisplayWnd() : CLocaleMDIChildWnd()
{
	SetType();
}

BOOL CDisplayWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, CONST RECT &rect, UINT nResourceID, UINT nStyle, INT nBkgndColor)
{
	if (CLocaleMDIChildWnd::Create(AfxRegisterWndClass(0, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(nBkgndColor), LoadIcon(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(nResourceID))), pszTitle, nStyle, rect, pParentWnd))
	{
		ModifyStyleEx(0, WS_EX_CLIENTEDGE);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayWnd::SetType(INT nType)
{
	switch (LOWORD(nType))
	{
	case DISPLAY_TYPE_TMPACKET:
	case DISPLAY_TYPE_TCFUNCTION:
	case DISPLAY_TYPE_TCSEQUENCE:
	case DISPLAY_TYPE_TCPROCEDURE:
	case DISPLAY_TYPE_OBPROCESSOR:
	case DISPLAY_TYPE_TMPARAMETER:
	case DISPLAY_TYPE_TCPARAMETER:
	case DISPLAY_TYPE_AND:
	case DISPLAY_TYPE_GRD:
	case DISPLAY_TYPE_MMD:
	case DISPLAY_TYPE_POD:
	case DISPLAY_TYPE_SCRIPT:
	{ m_nType = nType;
	m_bToggleKey = FALSE;
	return TRUE;
	break;
	}
	default:
	{ m_nType = -1;
	m_bToggleKey = FALSE;
	return TRUE;
	break;
	}
	}
	return FALSE;
}

INT CDisplayWnd::GetType() CONST
{
	return m_nType;
}

VOID CDisplayWnd::DoToggleKey()
{
	m_bToggleKey = !m_bToggleKey;
}

BOOL CDisplayWnd::IsKeyToggled() CONST
{
	return m_bToggleKey;
}

BOOL CDisplayWnd::IsNew() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::IsModified() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::Save(INT nPosition) CONST
{
	return FALSE;
}

INT CDisplayWnd::Load(INT nPosition)
{
	return -1;
}

BOOL CDisplayWnd::UpdateProperties()
{
	return FALSE;
}

BOOL CDisplayWnd::IsUpdatingProperties() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::HasProperties() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::UpdateLinkInformation()
{
	return FALSE;
}

BOOL CDisplayWnd::IsUpdatingLinkInformation() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::HasLinkInformation() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return FALSE;
}

VOID CDisplayWnd::UpdateAllPanes(LPCTSTR pszMessage, LPCTSTR pszFlag, LPCTSTR pszType)
{
	return;
}

BOOL CDisplayWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
{
	return FALSE;
}

VOID CDisplayWnd::DoSave()
{
	return;
}

BOOL CDisplayWnd::CanSave() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoSaveAs()
{
	return;
}

BOOL CDisplayWnd::CanSaveAs() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoCheck()
{
	return;
}

BOOL CDisplayWnd::CanCheck() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoDelete()
{
	return;
}

BOOL CDisplayWnd::CanDelete() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoUndo()
{
	return;
}

BOOL CDisplayWnd::CanUndo() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoRedo()
{
	return;
}

BOOL CDisplayWnd::CanRedo() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoFind()
{
	return;
}

BOOL CDisplayWnd::CanFind() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	return;
}
VOID CDisplayWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	return;
}

BOOL CDisplayWnd::CanFindNext() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	return;
}
VOID CDisplayWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	return;
}

BOOL CDisplayWnd::CanFindPrevious() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoReplace()
{
	return;
}

BOOL CDisplayWnd::CanReplace() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoGoTo()
{
	return;
}

BOOL CDisplayWnd::CanGoTo() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoSelectAll()
{
	return;
}

BOOL CDisplayWnd::CanSelectAll() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoCutSel()
{
	return;
}

BOOL CDisplayWnd::CanCutSel() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoCopySel()
{
	return;
}

BOOL CDisplayWnd::CanCopySel() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoPasteSel()
{
	return;
}

BOOL CDisplayWnd::CanPasteSel() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoDeleteSel()
{
	return;
}

BOOL CDisplayWnd::CanDeleteSel() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoPrint(UINT nFlags)
{
	Print((PRINTDLG *)NULL, nFlags);
}

BOOL CDisplayWnd::CanPrint(UINT nFlags) CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoCompile()
{
	return FALSE;
}

BOOL CDisplayWnd::IsCompiling() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::CanCompile() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::StopCompiling()
{
	return FALSE;
}

VOID CDisplayWnd::DoTest()
{
	return;
}

BOOL CDisplayWnd::IsTesting() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::CanTest() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoTestBreak()
{
	return;
}

BOOL CDisplayWnd::CanBreakTesting() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoTestContinue()
{
	return;
}

BOOL CDisplayWnd::CanContinueTesting() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoTestStepInto()
{
	return;
}

BOOL CDisplayWnd::CanTestStepInto() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoTestStepOver()
{
	return;
}

BOOL CDisplayWnd::CanTestStepOver() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoTestStepOut()
{
	return;
}

BOOL CDisplayWnd::CanTestStepOut() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoTestReset()
{
	return;
}

BOOL CDisplayWnd::CanResetTesting() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoTestStop()
{
	return;
}

VOID CDisplayWnd::DoClose()
{
	return;
}

BOOL CDisplayWnd::DoSaveTable()
{
	return FALSE;
}

BOOL CDisplayWnd::CanSaveTable() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoCheckTable()
{
	return FALSE;
}

BOOL CDisplayWnd::CanCheckTable() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoDeleteTable()
{
	return FALSE;
}

BOOL CDisplayWnd::CanDeleteTable() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoPrintTable()
{
	return FALSE;
}

BOOL CDisplayWnd::CanPrintTable() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoPrintAllTables()
{
	return FALSE;
}

BOOL CDisplayWnd::CanPrintAllTables() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoImportTables()
{
	return FALSE;
}

BOOL CDisplayWnd::CanImportTables() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoExportTables()
{
	return FALSE;
}

BOOL CDisplayWnd::CanExportTables() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoDiscardTables()
{
	return FALSE;
}

BOOL CDisplayWnd::CanDiscardTables() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoDiscardAllTables()
{
	return FALSE;
}

BOOL CDisplayWnd::CanDiscardAllTables() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoResetTables()
{
	return FALSE;
}

BOOL CDisplayWnd::CanResetTables() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoInsertTableRowAbove()
{
	return FALSE;
}

BOOL CDisplayWnd::CanInsertTableRowAbove() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoInsertTableRowBelow()
{
	return FALSE;
}

BOOL CDisplayWnd::CanInsertTableRowBelow() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoInsertTableColumnBefore()
{
	return FALSE;
}

BOOL CDisplayWnd::CanInsertTableColumnBefore() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoInsertTableColumnAfter()
{
	return FALSE;
}

BOOL CDisplayWnd::CanInsertTableColumnAfter() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoClearTableRow()
{
	return FALSE;
}

BOOL CDisplayWnd::CanClearTableRow() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoDeleteTableRow()
{
	return FALSE;
}

BOOL CDisplayWnd::CanDeleteTableRow() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoDeleteTableColumn()
{
	return FALSE;
}

BOOL CDisplayWnd::CanDeleteTableColumn() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoCopyTableRow()
{
	return FALSE;
}

BOOL CDisplayWnd::CanCopyTableRow() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::DoPasteTableRow()
{
	return FALSE;
}

BOOL CDisplayWnd::CanPasteTableRow() CONST
{
	return FALSE;
}

VOID CDisplayWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	return;
}

VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	return;
}
VOID CDisplayWnd::UpdateTables(ULONGLONG nComponent)
{
	return;
}
VOID CDisplayWnd::UpdateTables()
{
	return;
}

CMainWnd *CDisplayWnd::GetTopLevelFrame() CONST
{
	return((CMainWnd *)CLocaleMDIChildWnd::GetTopLevelFrame());
}

BOOL CDisplayWnd::StartPrintJob(CDC &cDC, LPCTSTR pszName, LPCTSTR pszForm)
{
	CString  szJob;
	DOCINFO  sDocInfo;

	for (sDocInfo.cbSize = sizeof(DOCINFO), sDocInfo.fwType = 0, sDocInfo.lpszDatatype = (LPCTSTR)NULL, sDocInfo.lpszOutput = (LPCTSTR)NULL, sDocInfo.lpszDocName = (LPTSTR)EMPTYSTRING; lstrlen(pszForm) > 0; )
	{
		szJob.Format((lstrlen(pszName) > 0) ? STRING(IDS_PRINTDOCUMENT_TITLE_FORM) : STRING(IDS_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAppTitle(), pszForm, pszName);
		sDocInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJob;
		break;
	}
	return((cDC.StartDoc(&sDocInfo) >= 0 && cDC.StartPage() >= 0) ? TRUE : FALSE);
}

BOOL CDisplayWnd::PrintJob(CDC &cDC, CDisplayTableView *pView, LPCTSTR pszForm, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage, WORD wToPage)
{
	INT  nPage;
	INT  nPages;
	INT  nTable;
	INT  nTables;
	INT  nOffset;
	INT  nMargin;
	BOOL  bCalc;
	BOOL  bUndo;
	CRgn  rgnClip[2];
	CRect  rPrintArea[4];
	CFont  cPrintFont[DISPLAY_PRINTFONTS];
	TCHAR  szTempDirectory[MAX_PATH];
	TCHAR  szTempFileName[MAX_PATH];
	double  fPrintScaling;
	CString  szTableName;
	CTimeKey  tPrintTime;
	CPtrArray  pFonts;
	CMetaFileDC  cMetaDC;
	HENHMETAFILE  hMetaDC;
	CStringArray  szTables;
	ENHMETAHEADER  sMetaHeader;
	CClientDC  cClientDC(this);

	if (StartPrintJob(cDC, pView->GetName(), pszForm))
	{
		if (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rPrintArea[0]) != ERROR  &&  CalcPrintDocTitleFont(cDC, rPrintArea[0], cPrintFont[DISPLAY_PRINTFONT_TITLE]) && pFonts.Add(&cPrintFont[DISPLAY_PRINTFONT_TITLE]) >= 0 && CalcPrintDocInfoTitleFont(cDC, rPrintArea[0], cPrintFont[DISPLAY_PRINTFONT_INFOTITLE]) && pFonts.Add(&cPrintFont[DISPLAY_PRINTFONT_INFOTITLE]) >= 0 && CalcPrintDocFooterFont(cDC, rPrintArea[0], cPrintFont[DISPLAY_PRINTFONT_FOOTER]) && pFonts.Add(&cPrintFont[DISPLAY_PRINTFONT_FOOTER]) >= 0 && CalcPrintDocNoticeFont(cDC, rPrintArea[0], cPrintFont[DISPLAY_PRINTFONT_NOTICE], cPrintFont[DISPLAY_PRINTFONT_LOGO]) && pFonts.Add(&cPrintFont[DISPLAY_PRINTFONT_NOTICE]) >= 0 && pFonts.Add(&cPrintFont[DISPLAY_PRINTFONT_LOGO]) >= 0)
		{
			for (nPage = 1, nPages = -nPage, GetTempPath(sizeof(szTempDirectory) / sizeof(TCHAR), szTempDirectory), GetTempFileName(szTempDirectory, GetAccountSpacecraftName(), 0, szTempFileName), bUndo = pView->EnableUndo(FALSE); pView->CanPrint(nFlags, szTableName, szTables); )
			{
				for (nTable = 0, nTables = (INT)szTables.GetSize(); nTable < nTables; nTable++)
				{
					if (cMetaDC.CreateEnhanced(&cDC, szTempFileName, (LPCRECT)NULL, (LPCTSTR)NULL))
					{
						for (cMetaDC.SetAttribDC(cDC.GetSafeHdc()), hMetaDC = (HENHMETAFILE)NULL; pView->DoPrint(szTableName, (nFlags & DISPLAYTABLEVIEW_PRINT_ALL) ? szTables.GetAt(nTable) : pView->GetName(), cMetaDC) && DrawPrintDocPage(cDC, ((nFlags & DISPLAYTABLEVIEW_PRINT_ALL) || (nFlags & DISPLAYTABLEVIEW_PRINT_SUBTABLE) || !lstrlen(pView->GetName())) ? szTables.GetAt(nTable) : pView->GetName(), nFlags, tPrintTime, pszPrinterName, pFonts, (rPrintArea[2] = rPrintArea[0]), 0, TRUE) && rgnClip[0].CreateRectRgn(rPrintArea[0].left, rPrintArea[0].top, rPrintArea[0].right, rPrintArea[0].bottom) && rgnClip[1].CreateRectRgn(rPrintArea[2].left, rPrintArea[2].top, rPrintArea[2].right, rPrintArea[2].bottom) && rPrintArea[2].Height() > 0; )
						{
							for (hMetaDC = cMetaDC.CloseEnhanced(), GetEnhMetaFileHeader(hMetaDC, sizeof(sMetaHeader), &sMetaHeader), fPrintScaling = min((double)cDC.GetDeviceCaps(LOGPIXELSX) / (double)cClientDC.GetDeviceCaps(LOGPIXELSX), (double)(rPrintArea[2].right - rPrintArea[2].left) / (double)(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)), rPrintArea[3].SetRect(rPrintArea[2].left, rPrintArea[2].top, (INT)(rPrintArea[2].left + fPrintScaling*(double)(sMetaHeader.rclBounds.right - sMetaHeader.rclBounds.left)), (INT)(rPrintArea[2].top + fPrintScaling*(double)(sMetaHeader.rclBounds.bottom - sMetaHeader.rclBounds.top))), nMargin = rPrintArea[0].Height() / 100, nOffset = max(rPrintArea[2].Height() - nMargin, 1), nPages = 0; DrawPrintDocPage(cDC, ((nFlags & DISPLAYTABLEVIEW_PRINT_ALL) || (nFlags & DISPLAYTABLEVIEW_PRINT_SUBTABLE) || !lstrlen(pView->GetName())) ? szTables.GetAt(nTable) : pView->GetName(), nFlags, tPrintTime, pszPrinterName, pFonts, (rPrintArea[1] = rPrintArea[0]), nPage, (bCalc = ((nPage < wFromPage || nPage > wToPage) && wFromPage != (WORD)-1 && wToPage != (WORD)-1) ? TRUE : FALSE)); )
							{
								if (cDC.SelectClipRgn(&rgnClip[1], RGN_COPY) != ERROR)
								{
									if (!bCalc) cDC.PlayMetaFile(hMetaDC, rPrintArea[3]);
									cDC.SelectClipRgn(&rgnClip[0], RGN_COPY);
									if (!LOBYTE(GetAsyncKeyState(VK_ESCAPE)))
									{
										if (rPrintArea[1].bottom < rPrintArea[3].bottom && (wFromPage == (WORD)-1 || wToPage == (WORD)-1 || nPage < wToPage))
										{
											if (bCalc || (cDC.EndPage() >= 0 && cDC.StartPage() >= 0))
											{
												rPrintArea[3].OffsetRect(0, -nOffset);
												nPage = nPage + 1;
												nPages++;
												continue;
											}
											nPages = -1;
											break;
										}
										for (nPage++, nPages++; !bCalc && (wFromPage == (WORD)-1 || wToPage == (WORD)-1 || (nPage >= wFromPage && nPage < wToPage)); )
										{
											if (nTable < nTables - 1)
											{
												cDC.EndPage();
												cDC.StartPage();
											}
											break;
										}
										break;
									}
									nPages = 0;
									break;
								}
								nPages = -1;
							}
							break;
						}
						DeleteEnhMetaFile((!hMetaDC) ? cMetaDC.CloseEnhanced() : hMetaDC);
						CFileEx::Remove(szTempFileName);
						rgnClip[0].DeleteObject();
						rgnClip[1].DeleteObject();
						if (nPages > 0) continue;
					}
					break;
				}
				for (pView->EnableUndo(bUndo); nTable == nTables; )
				{
					EndPrintJob(cDC);
					cDC.DeleteDC();
					return TRUE;
				}
				if (!nPages)
				{
					cDC.AbortDoc();
					cDC.DeleteDC();
					return TRUE;
				}
				break;
			}
		}
		cDC.AbortDoc();
		cDC.DeleteDC();
	}
	return FALSE;
}

BOOL CDisplayWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndPage() >= 0 && cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

CString CDisplayWnd::GetPrintDocTitle(LPCTSTR pszTag, UINT nFlags) CONST
{
	return EMPTYSTRING;
}

CString CDisplayWnd::GetPrintDocInfoTitle() CONST
{
	return EMPTYSTRING;
}

CString CDisplayWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CDisplayWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPage) CONST
{
	CString  szFooter;
	CString  szPageNumber;

	szFooter.Format(STRING(IDS_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName);
	szPageNumber.Format(STRING(IDS_PRINTDOCUMENT_PAGES), nPage);
	return((nPage >= 0) ? (szFooter + szPageNumber) : szFooter);
}

BOOL CDisplayWnd::DrawPrintDocPage(CDC &cDC, LPCTSTR pszTag, UINT nFlags, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, INT nPage, BOOL bCalc)
{
	return((DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(pszTag, nFlags), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_TITLE), bCalc) && DrawPrintDocInfoTitle(cDC, prClip, GetPrintDocInfoTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_INFOTITLE), bCalc) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_LOGO), bCalc) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPage), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_FOOTER), bCalc)) ? TRUE : FALSE);
}

BOOL CDisplayWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayWnd::DrawPrintDocInfoTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += 4 * rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
{
	INT  nPos;
	CFont  *pOldFont;
	CSize  sizeNotice[3];
	CString  szNotice[3];
	CString  szCopyrightNotice;
	CVersionInfo  cVersionInfo;

	for (szCopyrightNotice = pszNotice, sizeNotice[0].cx = sizeNotice[0].cy = 0, sizeNotice[1].cx = sizeNotice[1].cy = 0; (pOldFont = cDC.SelectObject(pFont)); )
	{
		szNotice[0] = ((nPos = szCopyrightNotice.Find((szNotice[2] = cVersionInfo.QueryCompanyName()))) >= 0) ? szCopyrightNotice.Left(nPos) : szCopyrightNotice;
		szNotice[1] = (nPos >= 0) ? szCopyrightNotice.Mid(nPos + szNotice[2].GetLength()) : EMPTYSTRING;
		sizeNotice[0] = cDC.GetTextExtent(szNotice[0]);
		sizeNotice[1] = cDC.GetTextExtent(szNotice[1]);
		cDC.SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = cDC.SelectObject(pLogoFont)))
	{
		sizeNotice[2] = cDC.GetTextExtent(szNotice[2]);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0) ? cDC.SelectObject(pFont) : (CFont *)NULL))
	{
		cDC.TextOut(prClip->left, prClip->bottom - sizeNotice[0].cy, (!bCalc) ? (LPCTSTR)szNotice[0] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0) ? cDC.SelectObject(pLogoFont) : (CFont *)NULL))
	{
		cDC.TextOut(prClip->left + sizeNotice[0].cx, prClip->bottom - sizeNotice[2].cy, (!bCalc) ? (LPCTSTR)szNotice[2] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[1].cx > 0 && sizeNotice[1].cy > 0) ? cDC.SelectObject(pFont) : (CFont *)NULL))
	{
		cDC.TextOut(prClip->left + sizeNotice[0].cx + sizeNotice[2].cx, prClip->bottom - sizeNotice[1].cy, (!bCalc) ? (LPCTSTR)szNotice[1] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0)
	{
		prClip->bottom -= max(sizeNotice[0].cy, sizeNotice[2].cy);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszFooter, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszFooter, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);
		prClip->bottom -= 3 * rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CDisplayWnd::CalcPrintDocInfoTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CDisplayWnd::CalcPrintDocNoticeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CDisplayWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CDisplayWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

VOID CDisplayWnd::AdjustToPrivileges()
{
	return;
}

BOOL CALLBACK CDisplayWnd::EnumDisplayWindows(HWND hWnd, LPARAM lParam)
{
	CWnd  *pWnd;
	CString  szDisplayTitle;
	CDisplayWnd  *pDisplayWnd;
	PDISPLAYTITLEINFO  pDisplayTitleInfo = (PDISPLAYTITLEINFO)lParam;

	if ((pWnd = CWnd::FromHandle(hWnd)) && pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
	{
		if ((pDisplayWnd = (pWnd->IsWindowVisible() || !pWnd->GetParent()->IsWindowVisible()) ? (CDisplayWnd *)pWnd : (CDisplayWnd *)NULL) && pDisplayTitleInfo->hWnd[0] != hWnd)
		{
			for (pDisplayWnd->GetWindowText(szDisplayTitle); szDisplayTitle == pDisplayTitleInfo->pszTitle; )
			{
				pDisplayTitleInfo->nNumber = ++pDisplayTitleInfo->nCount + 1;
				pDisplayTitleInfo->hWnd[1] = hWnd;
				return TRUE;
			}
			if (szDisplayTitle.Left(lstrlen(pDisplayTitleInfo->pszTitle)) == pDisplayTitleInfo->pszTitle  &&  szDisplayTitle.Mid(lstrlen(pDisplayTitleInfo->pszTitle), 1) == CString(STRING(IDS_WINDOW_EXTENDEDTITLE)).Mid(lstrlen(STRING(IDS_WINDOW_TITLE)), 1))
			{
				pDisplayTitleInfo->nNumber = max(_ttoi(szDisplayTitle.Mid(lstrlen(pDisplayTitleInfo->pszTitle) + 1)) + 1, max(pDisplayTitleInfo->nNumber, pDisplayTitleInfo->nCount + 1));
				pDisplayTitleInfo->nCount = pDisplayTitleInfo->nCount + 1;
				pDisplayTitleInfo->hWnd[2] = hWnd;
			}
		}
	}
	return TRUE;
}

void CDisplayWnd::PostNcDestroy()
{
	GetMainWnd()->UpdateMenus(this);
	CLocaleMDIChildWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDisplayWnd, CLocaleMDIChildWnd)
	//{{AFX_MSG_MAP(CDisplayWnd)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd message handlers

int CDisplayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CLocaleMDIChildWnd::OnCreate(lpCreateStruct) != -1)
	{
		SetWindowText(lpCreateStruct->lpszName);
		return 0;
	}
	return -1;
}

LRESULT CDisplayWnd::OnSetText(WPARAM wParam, LPARAM lParam)
{
	CWnd  *pWnd;
	LRESULT  lResult;
	CString  szDisplayTitle;
	DISPLAYTITLEINFO  sDisplayTitleInfo = { { GetSafeHwnd() },(LPCTSTR)lParam };

	if (!_tcsstr(sDisplayTitleInfo.pszTitle, CString(STRING(IDS_WINDOW_EXTENDEDTITLE)).Mid(lstrlen(STRING(IDS_WINDOW_TITLE)), 1)))
	{
		if (EnumChildWindows(GetParent()->GetSafeHwnd(), EnumDisplayWindows, (LPARAM)&sDisplayTitleInfo) && sDisplayTitleInfo.nCount > 0)
		{
			if (sDisplayTitleInfo.nCount == 1 && IsWindow(sDisplayTitleInfo.hWnd[1]))
			{
				if ((pWnd = CWnd::FromHandle(sDisplayTitleInfo.hWnd[1])) != (CWnd *)NULL)
				{
					szDisplayTitle.Format(STRING(IDS_WINDOW_EXTENDEDTITLE), sDisplayTitleInfo.pszTitle, 1);
					pWnd->SetWindowText(szDisplayTitle);
				}
			}
			szDisplayTitle.Format(STRING(IDS_WINDOW_EXTENDEDTITLE), sDisplayTitleInfo.pszTitle, sDisplayTitleInfo.nNumber);
			SetWindowText(szDisplayTitle);
			return TRUE;
		}
	}
	lResult = Default();
	GetTopLevelFrame()->UpdateMenus(this);
	return lResult;
}

void CDisplayWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	GetTopLevelFrame()->UpdateMenus(this);
	GetTopLevelFrame()->UpdateBars(this, bActivate);
	CLocaleMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CDisplayWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rPosition;

	if (nType == SIZE_RESTORED)
	{
		GetWindowRect(rPosition);
		GetParent()->ScreenToClient(rPosition);
		m_rPosition = rPosition;
		m_ptPosition.x = 0;
		m_ptPosition.y = 0;
	}
	if (nType == SIZE_MINIMIZED)
	{
		GetWindowRect(rPosition);
		GetParent()->ScreenToClient(rPosition);
		m_ptPosition.x = rPosition.left;
		m_ptPosition.y = rPosition.top;
	}
	CLocaleMDIChildWnd::OnSize(nType, cx, cy);
}

void CDisplayWnd::OnMove(int x, int y)
{
	CRect  rPosition;

	if (!IsIconic() && !IsZoomed())
	{
		GetWindowRect(rPosition);
		GetParent()->ScreenToClient(rPosition);
		m_rPosition = rPosition;
		m_ptPosition.x = 0;
		m_ptPosition.y = 0;
	}
	if (IsIconic())
	{
		GetWindowRect(rPosition);
		GetParent()->ScreenToClient(rPosition);
		m_ptPosition.x = rPosition.left;
		m_ptPosition.y = rPosition.top;
	}
	CLocaleMDIChildWnd::OnMove(x, y);
}

void CDisplayWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	CWnd  *pWnd;
	LPCTSTR  pPos[2];
	CString  szDisplayTitle;
	DISPLAYTITLEINFO  sDisplayTitleInfo;

	if (nID == SC_MAXIMIZE)
	{
		GetParent()->ShowScrollBar(SB_HORZ, FALSE);
		GetParent()->ShowScrollBar(SB_VERT, FALSE);
	}
	if (nID == SC_CLOSE)
	{
		for (GetWindowText(szDisplayTitle); (pPos[0] = pPos[1] = _tcsstr(szDisplayTitle, CString(STRING(IDS_WINDOW_EXTENDEDTITLE)).Mid(lstrlen(STRING(IDS_WINDOW_TITLE)), 1))); )
		{
			while (lstrlen(++pPos[1]) > 0)
			{
				if (!_istdigit(pPos[1][0])) break;
				continue;
			}
			for (sDisplayTitleInfo.hWnd[0] = GetSafeHwnd(), sDisplayTitleInfo.nCount = sDisplayTitleInfo.nNumber = 0, sDisplayTitleInfo.pszTitle = szDisplayTitle = (!lstrlen(pPos[1])) ? szDisplayTitle.Left(szDisplayTitle.GetLength() - (INT)(pPos[1] - pPos[0])) : szDisplayTitle, pWnd = GetParent(), Default(); EnumChildWindows(pWnd->GetSafeHwnd(), EnumDisplayWindows, (LPARAM)&sDisplayTitleInfo) && sDisplayTitleInfo.nCount > 0; )
			{
				if (sDisplayTitleInfo.nCount == 1 && IsWindow(sDisplayTitleInfo.hWnd[2]))
				{
					if ((pWnd = CWnd::FromHandle(sDisplayTitleInfo.hWnd[2])))
					{
						szDisplayTitle = sDisplayTitleInfo.pszTitle;
						pWnd->SetWindowText(szDisplayTitle);
					}
				}
				break;
			}
			return;
		}
	}
	CLocaleMDIChildWnd::OnSysCommand(nID, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayFrame

IMPLEMENT_DYNCREATE(CDisplayFrame, CMDIClientAreaWnd)

CDisplayFrame::CDisplayFrame() : CMDIClientAreaWnd()
{
	return;
}

BOOL CDisplayFrame::Create(CMainWnd *pParentWnd)
{
	return SubclassWindow(pParentWnd->m_hWndMDIClient);
}

VOID CDisplayFrame::Destroy(CMainWnd *pParentWnd)
{
	pParentWnd->m_hWndMDIClient = (HWND)NULL;
	UnsubclassWindow();
}

VOID CDisplayFrame::Show()
{
	CDisplayWnd  *pDisplayWnd;

	for (ShowWindow(SW_SHOW); (pDisplayWnd = (CDisplayWnd *)GetParent()->MDIGetActive()); )
	{
		GetParent()->UpdateMenus(pDisplayWnd);
		GetParent()->UpdateBars(pDisplayWnd, TRUE);
		break;
	}
}

VOID CDisplayFrame::Hide()
{
	GetParent()->UpdateBars();
	ShowWindow(SW_HIDE);
}

CMainWnd *CDisplayFrame::GetParent() CONST
{
	return((CMainWnd *)CMDIClientAreaWnd::GetParent());
}

BEGIN_MESSAGE_MAP(CDisplayFrame, CMDIClientAreaWnd)
	//{{AFX_MSG_MAP(CDisplayFrame)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayFrame message handlers

void CDisplayFrame::OnWindowPosChanging(LPWINDOWPOS lpwndpos)
{
	CRect  rWnd;

	rWnd = GetParent()->CalcClientRect();
	lpwndpos->x = rWnd.left;
	lpwndpos->y = rWnd.top;
	lpwndpos->cx = rWnd.Width();
	lpwndpos->cy = rWnd.Height();
	CMDIClientAreaWnd::OnWindowPosChanging(lpwndpos);
}

void CDisplayFrame::OnWindowPosChanged(LPWINDOWPOS lpwndpos)
{
	GetParent()->ArrangeToolWindows();
	CMDIClientAreaWnd::OnWindowPosChanged(lpwndpos);
}
