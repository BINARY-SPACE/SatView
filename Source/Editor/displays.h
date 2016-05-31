// DISPLAYS.H : Displays Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the displays related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DISPLAYS_H__
#define __DISPLAYS_H__


/////////////////////////////////////////////////////////////////////////////
// CDisplayDialog dialog

class CDisplayDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDisplayDialog)

	// Construction
public:
	CDisplayDialog();   // standard constructor

	// Attributes
private:
	BOOL  m_bModal;

	// Dialog Data
	//{{AFX_DATA(CDisplayDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, UINT nID, BOOL bModal = TRUE);

	class CDisplayWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayPropertySheetDialog

class CDisplayPropertySheetDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CDisplayPropertySheetDialog)

	// Construction
public:
	CDisplayPropertySheetDialog();
	CDisplayPropertySheetDialog(LPCTSTR pszTitle);

	// Attributes
private:
	BOOL  m_bModal;

	// Operations
public:
	INT Create(CWnd *pParentWnd, BOOL bModal = TRUE);

	class CDisplayWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayPropertySheetDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayPropertySheetDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayTableViewUndoItem

class CDisplayTableViewUndoItem : public CObject
{
	// Construction
public:
	CDisplayTableViewUndoItem();

	// Attributes
private:
	CString  m_szTable;
	CString  m_szContext;
	CString  m_szText[2];
	CPoint  m_ptCell;
	BOOL  m_bUpdates;
	BOOL  m_bActivation;
	BOOL  m_bSelection;
	INT  m_nAlignment;
	INT  m_nSel[2];
private:
	BOOL  m_bCollected;

	// Operations
public:
	VOID SetInfo(LPCTSTR pszTable, CONST POINT &ptCell, INT nAlignment, LPCTSTR pszText, LPCTSTR pszInitialText, INT nStartPos = -1, INT nEndPos = -1);
	VOID GetInfo(CString &szTable, CPoint &ptCell, INT &nAlignment, CString &szText, CString &szInitialText, INT &nStartPos, INT &nEndPos) CONST;
	VOID SetCell(LPCTSTR pszTable, CONST POINT &ptCell);
	BOOL GetCell(CString &szTable, CPoint &ptCell) CONST;
	VOID SetContext(LPCTSTR pszContext);
	CString GetContext() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetInitialText(LPCTSTR pszText);
	CString GetInitialText() CONST;
	VOID SetSel(INT nStartPos, INT nEndPos);
	VOID GetSel(INT &nStartPos, INT &nEndPos) CONST;
	VOID SetAlignment(INT nAlignment);
	INT GetAlignment() CONST;
	VOID AllowUpdates(BOOL bEnable = TRUE);
	BOOL CanUpdate() CONST;
	VOID AllowActivation(BOOL bEnable = TRUE);
	BOOL CanActivate() CONST;
	VOID AllowSelection(BOOL bEnable = TRUE);
	BOOL CanSelect() CONST;

	VOID Collect(BOOL bEnable = TRUE);
	BOOL IsCollected() CONST;

	VOID Clear();

	VOID Copy(CONST CDisplayTableViewUndoItem *pItem);
	BOOL Compare(CONST CDisplayTableViewUndoItem *pItem) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayTableViewUndoList

class CDisplayTableViewUndoList : public CPtrArray
{
	// Construction
public:
	CDisplayTableViewUndoList();
	~CDisplayTableViewUndoList();

	// Attributes
private:
	INT  m_nIndex;
	INT  m_nCount;
	BOOL  m_bUndoing;
	BOOL  m_bCollecting;
private:
	UINT  m_nLocks;

	// Operations
public:
	BOOL Add(CONST CDisplayTableViewUndoItem *pItem, BOOL bUpdates = FALSE);

	BOOL Undo(CDisplayTableViewUndoItem *pItem, BOOL bFocus);
	BOOL Undo(CONST CTableViewCell *pCell, CString &szText);
	BOOL CanUndo(BOOL bFocus) CONST;
	BOOL CanCollectUndo() CONST;
	BOOL Redo(CDisplayTableViewUndoItem *pItem, BOOL bFocus);
	BOOL Redo(CONST CTableViewCell *pCell, CString &szText);
	BOOL CanRedo(BOOL bFocus) CONST;
	BOOL CanCollectRedo() CONST;

	VOID Collect(BOOL bEnable = TRUE, INT nAfter = 0);
	BOOL IsCollecting() CONST;

	CDisplayTableViewUndoItem *GetAt(INT nIndex) CONST;
	CDisplayTableViewUndoItem *operator[](INT nIndex) CONST;

	VOID Reset();

	BOOL Lock();
	BOOL IsLocked() CONST;
	BOOL Unlock();

private:
	BOOL IsCellAction(INT nIndex) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayTableView view

// Specify the display table view form print related identifiers
#define DISPLAYTABLEVIEW_PRINT_TABLE   DATABASETABLEVIEW_PRINT_TABLE
#define DISPLAYTABLEVIEW_PRINT_SUBTABLE   DATABASETABLEVIEW_PRINT_SUBTABLE
#define DISPLAYTABLEVIEW_PRINT_ALL   DATABASETABLEVIEW_PRINT_ALL
// Specify the display table view form timer related identifiers
#define DISPLAYTABLEVIEW_ACTIVATION_TIMERID   100
#define DISPLAYTABLEVIEW_ACTIVATION_TIMEOUT   0
#define DISPLAYTABLEVIEW_UPDATEFORM_TIMERID   101
#define DISPLAYTABLEVIEW_UPDATEFORM_TIMEOUT   0
#define DISPLAYTABLEVIEW_UPDATEBARS_TIMERID   102
#define DISPLAYTABLEVIEW_UPDATEBARS_TIMEOUT   500

class CDisplayTableView : public CDatabaseTableView
{
	DECLARE_DYNCREATE(CDisplayTableView)

	// Construction
public:
	CDisplayTableView(ULONGLONG nComponent = DATABASE_COMPONENT_NONE, UINT nFloatingMenuID = 0);

	// Attributes
protected:
	CString  m_szTitle;
	CBitmap  m_cImage;
	CStringArray  m_szTables;
	CDisplayTableViewUndoList  m_cUndoList;
	UINT_PTR  m_nTimerID[3];
	UINT  m_nFloatingMenuID;
	BOOL  m_bPrint[2];
	BOOL  m_bUndo[2];
	BOOL  m_bImage;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, LPCTSTR pszTag, CONST RECT &rect);

	VOID SetTablesFonts(CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont);
	VOID GetTablesFonts(LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST;
	VOID SetTablesFontColors(COLORREF nTitleColor, COLORREF nItemsColor);
	VOID GetTablesFontColors(COLORREF &nTitleColor, COLORREF &nItemsColor) CONST;
	VOID SetTablesColors(COLORREF nTitleBackground, COLORREF nKeysBackground);
	VOID GetTablesColors(COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	VOID SetTableFonts(CTableViewObject *pTable, CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont);
	BOOL GetTableFonts(CONST CTableViewObject *pTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST;
	BOOL CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST;
	BOOL DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point);
	BOOL GotoTable(ULONGLONG nComponent, LPCTSTR pszName);

	BOOL DoSave();
	BOOL CanSave() CONST;
	BOOL DoCheck();
	BOOL CanCheck() CONST;
	BOOL DoPrint(LPCTSTR pszTable, LPCTSTR pszItem, CMetaFileDC &cMetaDC);
	BOOL CanPrint(UINT nFlags, CString &szTable, CStringArray &szTables) CONST;
	BOOL CanPrint(UINT nFlags) CONST;
	BOOL DoDelete();
	BOOL CanDelete() CONST;
	VOID DoClose();

	BOOL DoSaveTable();
	BOOL CanSaveTable() CONST;
	BOOL DoCheckTable();
	BOOL CanCheckTable() CONST;
	BOOL DoDeleteTable();
	BOOL CanDeleteTable() CONST;
	BOOL DoImportTables();
	BOOL CanImportTables() CONST;
	BOOL DoExportTables();
	BOOL CanExportTables() CONST;
	BOOL DoDiscardTables();
	BOOL CanDiscardTables() CONST;
	BOOL DoDiscardAllTables();
	BOOL CanDiscardAllTables() CONST;
	BOOL DoResetTables();
	BOOL CanResetTables() CONST;
	BOOL DoInsertTableRowAbove();
	BOOL CanInsertTableRowAbove() CONST;
	BOOL DoInsertTableRowBelow();
	BOOL CanInsertTableRowBelow() CONST;
	BOOL DoInsertTableColumnBefore();
	BOOL CanInsertTableColumnBefore() CONST;
	BOOL DoInsertTableColumnAfter();
	BOOL CanInsertTableColumnAfter() CONST;
	BOOL DoClearTableRow();
	BOOL CanClearTableRow() CONST;
	BOOL DoDeleteTableRow();
	BOOL CanDeleteTableRow() CONST;
	BOOL DoDeleteTableColumn();
	BOOL CanDeleteTableColumn() CONST;
	BOOL DoCopyTableRow();
	BOOL CanCopyTableRow() CONST;
	BOOL DoPasteTableRow();
	BOOL CanPasteTableRow() CONST;

	VOID DoSelectAll();
	BOOL CanSelectAll() CONST;
	VOID UnSelectAll();
	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;
	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;
	BOOL DoEmpty();
	BOOL IsEmpty() CONST;

	BOOL GetPanesInfo(CString &szDetails, CString &szFlag, CString &szType) CONST;

	BOOL IsModified() CONST;
	BOOL Check() CONST;

	class CDisplayWnd *GetParent() CONST;

protected:
	VOID BeginTableUpdate();
	VOID EndTableUpdate();

	VOID RefreshTables(BOOL bAll = TRUE);
	VOID RefreshTables(CONST CStringArray &szTables, BOOL bAll = TRUE);
	VOID RefreshTables(CONST CTableViewObject *pTable, BOOL bAll = TRUE);
	VOID RefreshTables(UINT nControlID);
	VOID RefreshTables(CONST CStringArray &szTables, UINT nControlID);
	VOID RefreshTable(LPCTSTR pszTable, BOOL bAll = TRUE);
	VOID RefreshTable(CTableViewObject *pTable, LPCTSTR pszValue, UINT nControlID);

	BOOL ConvertUndoItem(LPCTSTR pszTable, CDisplayTableViewUndoItem *pItem, BOOL bUpdates = TRUE) CONST;
	BOOL ConvertUndoItem(CWnd *pControl, CDisplayTableViewUndoItem *pItem, BOOL bUpdates = TRUE) CONST;
	BOOL ConvertUndoItem(CONST CDisplayTableViewUndoItem *pItem, BOOL bUndo = TRUE);

private:
	VOID RepositionTables(CONST CTableViewObjects *pTables, LPCTSTR pszTable, INT nOffset);
	VOID RepositionTables(CONST CTableViewObjects *pTables, LPCTSTR pszTable, CStringArray &szTables);
	BOOL InsertTableRow(CTableViewObject *pTable, INT nRow);
	BOOL RemoveTableRow(CTableViewObject *pTable, INT nRow);
	BOOL DeleteTableRow(CTableViewObject *pTable, INT nRow);
	BOOL ResizeTableColumns(CTableViewObject *pTable, INT nCount);
	BOOL InsertTableColumn(CTableViewObject *pTable, INT nCol);
	BOOL DeleteTableColumn(CTableViewObject *pTable, INT nCol);
	INT CalcTableOrder(CONST CTableViewObjects *pTables, LPCTSTR pszTable) CONST;
	VOID CalcTableOrder(CONST CTableViewObjects *pTables, LPCTSTR pszTable, INT &nOrder) CONST;
	INT CalcDefaultTableWidth(CONST CTableViewObject *pTable);
	INT CalcDefaultTableHeight(CONST CTableViewObject *pTable);
	INT CalcDefaultTableMargin(CONST CTableViewObject *pTable);
	INT CalcDefaultCellWidth(CONST CTableViewCell *pCell, UINT nColumnWidth, INT nWidth);
	INT CalcDefaultCellHeight(CONST CTableViewCell *pCell, INT nWidth);
	INT CalcDefaultCellHeight(CONST CTableViewObjects *pTables, CONST CTableViewCell *pCell, INT nWidth);

	VOID ShowTableInfo(CONST POINT &point);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayTableView)
public:
	virtual INT EnumTables(CStringArray &szTables, CUIntArray &nTypes, BOOL bMenu, BOOL bResetable = FALSE) CONST;
	virtual BOOL GetTableTitle(LPCTSTR pszTable, CString &szTitle) CONST;
	virtual BOOL GetTableLayout(LPCTSTR pszTable, CUIntArray &nWidths) CONST;
	virtual BOOL GetTableLayout(LPCTSTR pszTable, LPCTSTR pszItem, CUIntArray &nWidths) CONST;
	virtual BOOL GetTablePosition(LPCTSTR pszTable, CString &szTable, CRect &rPosition) CONST;
	virtual BOOL SetTableFloatingAlignment(LPCTSTR pszTable, INT nRow);
	virtual INT GetTableFloatingAlignment(LPCTSTR pszTable) CONST;
	virtual BOOL AlignFloatingTable(LPCTSTR pszTable);
	virtual BOOL GetTableOutline(LPCTSTR pszTable, COLORREF &nTitleRowColor, COLORREF &nFirstRowColor, COLORREF &nFirstColumnColor, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, INT &nOuterBorderSize, INT &nOuterBorderStyle, COLORREF &nOuterBorderColor, INT &nInnerBorderSize, INT &nInnerBorderStyle, COLORREF &nInnerBorderColor) CONST;
	virtual BOOL GetTableOutlineFonts(LPCTSTR pszTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST;
	virtual BOOL GetTableOutlineLimits(LPCTSTR pszTable, INT &nMinRows, INT &nMaxRows) CONST;
	virtual BOOL GetTableContents(LPCTSTR pszTable, LPCTSTR pszItem, INT nRows, CStringArray &szContents, CStringArray &szDescriptions, CStringArray &szDataTypes, CUIntArray &nFormats, CUIntArray &nIDs, BOOL &bResize, BOOL &bVisible) CONST;
	virtual INT EnumTableFieldValues(LPCTSTR pszTable, LPCTSTR pszField, CStringArray &szValues, CLongUIntArray &nValues) CONST;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, INT &nLow, INT &nHigh) CONST;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, UINT &uLow, UINT &uHigh) CONST;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, double &fLow, double &fHigh) CONST;
	virtual BOOL GetTableContext(LPCTSTR pszTable, CString &szTable, UINT &nControlID, CString &szValue) CONST;
	virtual INT EnumTableUpdates(UINT nControlID, CStringArray &szTables) CONST;
	virtual BOOL GetTableUpdateContents(LPCTSTR pszTable, UINT nControlID, LPCTSTR pszValue, CString &szItem, CStringArray &szContents) CONST;
	virtual BOOL UpdateTableFieldData(UINT nControlID, LPCTSTR pszValue, LPCTSTR pszOldValue = NULL);
	virtual INT InsertTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL InsertTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol = -1);
	virtual BOOL CheckTableFieldData(LPCTSTR pszTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableFieldData(LPCTSTR pszTable, CStringArray &szIssues) CONST;
	virtual BOOL SelectTableFieldData(LPCTSTR pszTable, CONST POINT &pt);
	virtual BOOL SelectTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL SaveTableFieldData(LPCTSTR pszTable, BOOL bPrompt = FALSE);
	virtual BOOL ProtectTableFieldData(LPCTSTR pszTable, BOOL bUndo = FALSE);
	virtual BOOL DeleteTableFieldData(LPCTSTR pszTable);
	virtual INT DeleteTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL DeleteTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol = -1);
	virtual BOOL GetTableFieldFlag(LPCTSTR pszTable, INT nRow, INT nCol, CString &szFlag) CONST;
	virtual INT EnumTableDropTargets(ULONGLONG nComponent, CStringArray &szTables, CStringArray &szFields) CONST;
	virtual BOOL FindTableDropTargetCell(LPCTSTR pszTable, LPCTSTR pszField, ULONGLONG nComponent, LPCTSTR pszItem, CString &szItem, INT &nRow, INT &nCol) CONST;
	virtual INT EnumPrintTables(LPCTSTR pszTable, UINT nFlags, CStringArray &szTables) CONST;
	virtual BOOL GetPrintTableContents(LPCTSTR pszTable, LPCTSTR pszItem, CStringArray &szContents) CONST;
	virtual BOOL PrintTable(LPCTSTR pszTable, LPCTSTR pszItem, CMetaFileDC &cMetaDC);
	virtual ULONGLONG TranslateTableNameToComponent(LPCTSTR pszTable) CONST;
	virtual CString TranslateComponentToTableName(ULONGLONG nComponent) CONST;
	virtual INT TranslateTableFieldToIndex(LPCTSTR pszTable, LPCTSTR pszField) CONST;
	virtual UINT TranslateTableFieldToID(LPCTSTR pszTable, LPCTSTR pszField) CONST;
public:
	virtual INT EnumTables(CTableViewObjects *pTables) CONST;
	virtual VOID RepositionTables(CONST CTableViewObjects *pTables);
	virtual VOID RepositionTables();
	virtual VOID ArrangeTables();
	virtual VOID ArrangeTables(UINT nControlID);
	virtual BOOL ActivateTable();
	virtual BOOL ActivateTable(CTableViewObject *pTable, BOOL bPrevious = FALSE);
	virtual BOOL ActivateNextTable(BOOL bPrevious = FALSE);
	virtual BOOL ActivateNextTableCell(BOOL bPrevious = FALSE);
	virtual VOID RecalcTable(CTableViewObject *pTable, BOOL bWidth, BOOL bAdjust, BOOL bRedraw = TRUE);
	virtual VOID RecalcTable(CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw = TRUE);
	virtual VOID RecalcTable(CONST CTableViewObjects *pTables, CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw = TRUE);
	virtual VOID RecalcTableRow(CTableViewObject *pTable, INT nRow, BOOL bRedraw = TRUE);
	virtual VOID RecalcTableRow(CONST CTableViewObjects *pTables, CTableViewObject *pTable, INT nRow, BOOL bAdjust);
	virtual VOID UpdateTableContents(CTableViewObject *pTable, CONST CStringArray &szContents);
	virtual VOID UpdateTableContents(CONST CTableViewObjects *pTables, CTableViewObject *pTable, LPCTSTR pszTable, CONST CStringArray &szContents);
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem);
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CUIntArray &nValues);
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CLongUIntArray &nValues);
	virtual BOOL LimitTableCellValues(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem);
	virtual VOID UpdateTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszValue);
	virtual VOID EnableTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszDefault, BOOL bEnable = TRUE);
	virtual BOOL IsTableRowEmpty(CONST CTableViewObject *pTable, INT nRow) CONST;
	virtual BOOL IsTableRowFull(CONST CTableViewObject *pTable, INT nRow) CONST;
	virtual BOOL IsSubTable(CONST CTableViewObject *pTable) CONST;
public:
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CANDLayout *pLayout, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CGRDLayout *pLayout, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CPODLayout *pLayout, INT nIndex, BOOL bDelete = FALSE);
public:
	virtual VOID UpdateTables(CONST CDatabaseTMPackets &pDatabaseTMPackets);
	virtual VOID UpdateTables(CONST CDatabaseTCFunctions &pDatabaseTCFunctions);
	virtual VOID UpdateTables(CONST CDatabaseTCSequences &pDatabaseTCSequences);
	virtual VOID UpdateTables(CONST CDatabaseOBProcessors &pDatabaseOBProcessors);
	virtual VOID UpdateTables(CONST CDatabaseTMParameters &pDatabaseTMParameters);
	virtual VOID UpdateTables(CONST CDatabaseTCParameters &pDatabaseTCParameters);
	virtual VOID UpdateTables(CONST CANDLayouts &pANDLayouts);
	virtual VOID UpdateTables(CONST CGRDLayouts &pGRDLayouts);
	virtual VOID UpdateTables(CONST CPODLayouts &pPODLayouts);
	virtual BOOL UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete);
	virtual BOOL UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete);
	virtual VOID UpdateTables(ULONGLONG nComponent);
	virtual VOID UpdateTables();
public:
	virtual BOOL EnableTablesAlignment(BOOL bEnable, BOOL bRealign);
	virtual BOOL EnableTablesAlignment(BOOL bEnable);
public:
	virtual VOID DrawTables();
	virtual VOID DrawTables(CDC *pDC);
	virtual VOID DrawTables(CDC *pDC, CONST CTableViewObjects *pTables, BOOL bPrinting = FALSE);
	virtual VOID DrawTable(CDC *pDC, CONST CTableViewObject *pTable, BOOL bPrinting = FALSE);
public:
	virtual BOOL EnableUndo(BOOL bEnable = TRUE);
	virtual BOOL IsUndoing() CONST;
	virtual BOOL IsRedoing() CONST;
	virtual VOID ClearUndo();
protected:
	virtual BOOL CheckPrivilege() CONST;
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayTableView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd frame

// Specify the display window types
#define DISPLAY_TYPE_TMPACKET   1
#define DISPLAY_TYPE_TCFUNCTION   2
#define DISPLAY_TYPE_TCSEQUENCE   3
#define DISPLAY_TYPE_TCPROCEDURE   4
#define DISPLAY_TYPE_TMPARAMETER   5
#define DISPLAY_TYPE_TCPARAMETER   6
#define DISPLAY_TYPE_OBPROCESSOR   7
#define DISPLAY_TYPE_AND   8
#define DISPLAY_TYPE_GRD   9
#define DISPLAY_TYPE_MMD   10
#define DISPLAY_TYPE_POD   11
#define DISPLAY_TYPE_SCRIPT   12
// Specify the display window edit modes
#define DISPLAY_MODE_EDIT   0
#define DISPLAY_MODE_DEBUG   1
// Specify the display window print types
#define DISPLAY_PRINTTYPE_CODE   0
#define DISPLAY_PRINTTYPE_IMAGE   1
// Specify the display window print fonts
#define DISPLAY_PRINTFONT_TITLE   0
#define DISPLAY_PRINTFONT_INFOTITLE   1
#define DISPLAY_PRINTFONT_FOOTER   2
#define DISPLAY_PRINTFONT_NOTICE   3
#define DISPLAY_PRINTFONT_LOGO   4
#define DISPLAY_PRINTFONTS   5

class CDisplayWnd : public CLocaleMDIChildWnd
{
	DECLARE_DYNCREATE(CDisplayWnd)

	// Construction
public:
	CDisplayWnd();

	// Attributes
private:
	typedef struct tagDISPLAYTITLEINFO {
		HWND  hWnd[3];
		LPCTSTR  pszTitle;
		INT  nNumber;
		INT  nCount;
	} DISPLAYTITLEINFO, *PDISPLAYTITLEINFO, *LPDISPLAYTITLEINFO;
protected:
	INT  m_nType;
	CRect  m_rPosition;
	POINT  m_ptPosition;
	BOOL  m_bToggleKey;

	// Operations
public:
	BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, CONST RECT &rect, UINT nResourceID, UINT nStyle = WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE, INT nBkgndColor = COLOR_WINDOW);

	BOOL SetType(INT nType = -1);
	INT GetType() CONST;

	VOID DoToggleKey();
	BOOL IsKeyToggled() CONST;

	class CMainWnd *GetTopLevelFrame() CONST;

protected:
	BOOL StartPrintJob(CDC &cDC, LPCTSTR pszName, LPCTSTR pszForm);
	BOOL PrintJob(CDC &cDC, CDisplayTableView *pView, LPCTSTR pszForm, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage = -1, WORD wToPage = -1);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, LPCTSTR pszTag, UINT nFlags, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, INT nPage = -1, BOOL bCalc = FALSE);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocInfoTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocInfoTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocNoticeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	static BOOL CALLBACK EnumDisplayWindows(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayWnd)
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
	virtual BOOL CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST;
	virtual BOOL DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point);
	virtual VOID UpdateAllPanes(LPCTSTR pszMessage, LPCTSTR pszFlag, LPCTSTR pszType);
	virtual BOOL Print(PRINTDLG *pPrintInfo, UINT nFlags);
public:
	virtual VOID DoSave();
	virtual BOOL CanSave() CONST;
	virtual VOID DoSaveAs();
	virtual BOOL CanSaveAs() CONST;
	virtual VOID DoCheck();
	virtual BOOL CanCheck() CONST;
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
	virtual VOID DoPrint(UINT nFlags);
	virtual BOOL CanPrint(UINT nFlags) CONST;
	virtual BOOL DoCompile();
	virtual BOOL IsCompiling() CONST;
	virtual BOOL CanCompile() CONST;
	virtual BOOL StopCompiling();
	virtual VOID DoTest();
	virtual BOOL IsTesting() CONST;
	virtual BOOL CanTest() CONST;
	virtual VOID DoTestBreak();
	virtual BOOL CanBreakTesting() CONST;
	virtual VOID DoTestContinue();
	virtual BOOL CanContinueTesting() CONST;
	virtual VOID DoTestStepInto();
	virtual BOOL CanTestStepInto() CONST;
	virtual VOID DoTestStepOver();
	virtual BOOL CanTestStepOver() CONST;
	virtual VOID DoTestStepOut();
	virtual BOOL CanTestStepOut() CONST;
	virtual VOID DoTestReset();
	virtual BOOL CanResetTesting() CONST;
	virtual VOID DoTestStop();
	virtual VOID DoClose();
public:
	virtual BOOL DoSaveTable();
	virtual BOOL CanSaveTable() CONST;
	virtual BOOL DoCheckTable();
	virtual BOOL CanCheckTable() CONST;
	virtual BOOL DoDeleteTable();
	virtual BOOL CanDeleteTable() CONST;
	virtual BOOL DoPrintTable();
	virtual BOOL CanPrintTable() CONST;
	virtual BOOL DoPrintAllTables();
	virtual BOOL CanPrintAllTables() CONST;
	virtual BOOL DoImportTables();
	virtual BOOL CanImportTables() CONST;
	virtual BOOL DoExportTables();
	virtual BOOL CanExportTables() CONST;
	virtual BOOL DoDiscardTables();
	virtual BOOL CanDiscardTables() CONST;
	virtual BOOL DoDiscardAllTables();
	virtual BOOL CanDiscardAllTables() CONST;
	virtual BOOL DoResetTables();
	virtual BOOL CanResetTables() CONST;
	virtual BOOL DoInsertTableRowAbove();
	virtual BOOL CanInsertTableRowAbove() CONST;
	virtual BOOL DoInsertTableRowBelow();
	virtual BOOL CanInsertTableRowBelow() CONST;
	virtual BOOL DoInsertTableColumnBefore();
	virtual BOOL CanInsertTableColumnBefore() CONST;
	virtual BOOL DoInsertTableColumnAfter();
	virtual BOOL CanInsertTableColumnAfter() CONST;
	virtual BOOL DoClearTableRow();
	virtual BOOL CanClearTableRow() CONST;
	virtual BOOL DoDeleteTableRow();
	virtual BOOL CanDeleteTableRow() CONST;
	virtual BOOL DoDeleteTableColumn();
	virtual BOOL CanDeleteTableColumn() CONST;
	virtual BOOL DoCopyTableRow();
	virtual BOOL CanCopyTableRow() CONST;
	virtual BOOL DoPasteTableRow();
	virtual BOOL CanPasteTableRow() CONST;
public:
	virtual VOID GotoTable(ULONGLONG nComponent, LPCTSTR pszName);
public:
	virtual VOID UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent);
	virtual VOID UpdateTables();
protected:
	virtual CString GetPrintDocTitle(LPCTSTR pszTag, UINT nFlags) CONST;
	virtual CString GetPrintDocInfoTitle() CONST;
	virtual CString GetPrintDocNotice() CONST;
	virtual CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPage = -1) CONST;
public:
	virtual VOID AdjustToPrivileges();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayFrame window

class CDisplayFrame : public CMDIClientAreaWnd
{
	DECLARE_DYNCREATE(CDisplayFrame)

	// Construction
public:
	CDisplayFrame();

	// Attributes
public:

	// Operations
public:
	BOOL Create(class CMainWnd *pParentWnd);
	VOID Destroy(class CMainWnd *pParentWnd);

	VOID Show();
	VOID Hide();

	class CMainWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayFrame)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayFrame)
	afx_msg void OnWindowPosChanging(LPWINDOWPOS lpwndpos);
	afx_msg void OnWindowPosChanged(LPWINDOWPOS lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DISPLAYS_H__
