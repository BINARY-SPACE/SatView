// EDITOR.CPP : SatView Editor Application.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the application related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/02/07 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#include <initguid.h>
#include "MimicsIIDs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// CEditorApp
CEditorApp  cEditorApp;


static UINT BASED_CODE  nFloatingMenuIDs[] =
{
	IDM_NEW_TMPACKET,IDM_OPEN_TMPACKET,IDM_IMPORT_TMPACKET,IDM_EXPORT_TMPACKET,IDM_NEWITEM_TMPACKET,IDM_OPENITEM_TMPACKET,IDM_DELETEITEM_TMPACKET,
	IDM_NEW_TCFUNCTION,IDM_OPEN_TCFUNCTION,IDM_IMPORT_TCFUNCTION,IDM_EXPORT_TCFUNCTION,IDM_NEWITEM_TCFUNCTION,IDM_OPENITEM_TCFUNCTION,IDM_DELETEITEM_TCFUNCTION,
	IDM_NEW_TCSEQUENCE,IDM_OPEN_TCSEQUENCE,IDM_IMPORT_TCSEQUENCE,IDM_EXPORT_TCSEQUENCE,IDM_NEWITEM_TCSEQUENCE,IDM_OPENITEM_TCSEQUENCE,IDM_DELETEITEM_TCSEQUENCE,
	IDM_NEW_TCPROCEDURE,IDM_OPEN_TCPROCEDURE,IDM_IMPORT_TCPROCEDURE,IDM_EXPORT_TCPROCEDURE,IDM_NEWITEM_TCPROCEDURE,IDM_OPENITEM_TCPROCEDURE,IDM_DELETEITEM_TCPROCEDURE,
	IDM_NEW_TMPARAMETER,IDM_OPEN_TMPARAMETER,IDM_IMPORT_TMPARAMETER,IDM_EXPORT_TMPARAMETER,IDM_NEWITEM_TMPARAMETER,IDM_OPENITEM_TMPARAMETER,IDM_DELETEITEM_TMPARAMETER,
	IDM_NEW_TCPARAMETER,IDM_OPEN_TCPARAMETER,IDM_IMPORT_TCPARAMETER,IDM_EXPORT_TCPARAMETER,IDM_NEWITEM_TCPARAMETER,IDM_OPENITEM_TCPARAMETER,IDM_DELETEITEM_TCPARAMETER,
	IDM_NEW_OBPROCESSOR,IDM_OPEN_OBPROCESSOR,IDM_IMPORT_OBPROCESSOR,IDM_EXPORT_OBPROCESSOR,IDM_NEWITEM_OBPROCESSOR,IDM_OPENITEM_OBPROCESSOR,IDM_DELETEITEM_OBPROCESSOR,
	IDM_NEW_AND,IDM_OPEN_AND,IDM_IMPORT_AND,IDM_EXPORT_AND,IDM_NEWITEM_AND,IDM_OPENITEM_AND,IDM_DELETEITEM_AND,
	IDM_NEW_GRD,IDM_OPEN_GRD,IDM_IMPORT_GRD,IDM_EXPORT_GRD,IDM_NEWITEM_GRD,IDM_OPENITEM_GRD,IDM_DELETEITEM_GRD,
	IDM_NEW_MMD,IDM_OPEN_MMD,IDM_IMPORT_MMD,IDM_EXPORT_MMD,IDM_NEWITEM_MMD,IDM_OPENITEM_MMD,IDM_DELETEITEM_MMD,
	IDM_NEW_POD,IDM_OPEN_POD,IDM_IMPORT_POD,IDM_EXPORT_POD,IDM_NEWITEM_POD,IDM_OPENITEM_POD,IDM_DELETEITEM_POD,
	IDM_NEW_SCRIPT,IDM_OPEN_SCRIPT,IDM_IMPORT_SCRIPT,IDM_EXPORT_SCRIPT,IDM_NEWITEM_SCRIPT,IDM_OPENITEM_SCRIPT,IDM_DELETEITEM_SCRIPT,
	IDM_EDIT_SAVETABLE,IDM_EDIT_CHECKTABLE,IDM_EDIT_DELETETABLE,IDM_EDIT_IMPORTTABLES,IDM_EDIT_EXPORTTABLES,IDM_EDIT_PRINTTABLE,IDM_EDIT_PRINTALLTABLES,IDM_EDIT_INSERTTABLEROWABOVE,IDM_EDIT_INSERTTABLEROWBELOW,IDM_EDIT_CLEARTABLEROW,IDM_EDIT_DELETETABLEROW,IDM_EDIT_INSERTTABLECOLUMNBEFORE,IDM_EDIT_INSERTTABLECOLUMNAFTER,IDM_EDIT_DELETETABLECOLUMN,IDM_EDIT_COPYTABLEROW,IDM_EDIT_PASTETABLEROW,IDM_EDIT_DISCARDALLTABLES,IDM_EDIT_DISCARDTABLES,IDM_EDIT_RESETTABLES,
	IDM_VIEW_MIMICSOBJECTPROPERTIES,IDM_VIEW_MIMICSOBJECTCODE
};

static UINT BASED_CODE  nStatusBarIndicators[] =
{
	ID_STATUSBAR_MESSAGEPANE,
	ID_STATUSBAR_SERVERPANE,
	ID_STATUSBAR_SPACECRAFTPANE,
	ID_STATUSBAR_USERPANE,
	ID_STATUSBAR_DATABASEPANE,
	ID_STATUSBAR_CAPSKEYPANE,
	ID_STATUSBAR_NUMKEYPANE,
	ID_STATUSBAR_SCRLKEYPANE,
	ID_STATUSBAR_OVRKEYPANE
};



/////////////////////////////////////////////////////////////////////////////
// CRecentDocumentInfo

CRecentDocumentInfo::CRecentDocumentInfo() : CObject()
{
	m_nComponent = DATABASE_COMPONENT_NONE | DATABASE_SUBCOMPONENT_NONE;
}

VOID CRecentDocumentInfo::SetDocument(LPCTSTR pszName, LPCTSTR pszTitle, ULONGLONG nComponent)
{
	m_szName = pszName;
	m_szTitle = pszTitle;
	m_nComponent = nComponent;
}

BOOL CRecentDocumentInfo::GetDocument(CString &szName, CString &szTitle, ULONGLONG &nComponent) CONST
{
	if (m_nComponent != (DATABASE_COMPONENT_NONE | DATABASE_SUBCOMPONENT_NONE))
	{
		szName = m_szName;
		szTitle = m_szTitle;
		nComponent = m_nComponent;
		return TRUE;
	}
	return FALSE;
}

VOID CRecentDocumentInfo::Reset()
{
	m_szName.Empty();
	m_szTitle.Empty();
	m_nComponent = DATABASE_COMPONENT_NONE | DATABASE_SUBCOMPONENT_NONE;
}

VOID CRecentDocumentInfo::Copy(CONST CRecentDocumentInfo *pDocumentInfo)
{
	m_szName = pDocumentInfo->m_szName;
	m_szTitle = pDocumentInfo->m_szTitle;
	m_nComponent = pDocumentInfo->m_nComponent;
}

BOOL CRecentDocumentInfo::Compare(CONST CRecentDocumentInfo *pDocumentInfo) CONST
{
	return((pDocumentInfo->m_nComponent == m_nComponent  &&  pDocumentInfo->m_szName == m_szName  &&  pDocumentInfo->m_szTitle == m_szTitle) ? TRUE : FALSE);
}

BOOL CRecentDocumentInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbTitle = (m_szTitle.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbTitle)), sData.nComponent = m_nComponent; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szTitle, sData.cbTitle);
		return TRUE;
	}
	return FALSE;
}

BOOL CRecentDocumentInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbTitle && sData.cbName > 0 && sData.cbTitle > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szTitle.GetBufferSetLength(STRINGCHARS(sData.cbTitle)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbTitle));
		m_nComponent = sData.nComponent;
		m_szName.ReleaseBuffer();
		m_szTitle.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CRecentDocuments

CRecentDocuments::CRecentDocuments() : CPtrArray()
{
	return;
}

CRecentDocuments::~CRecentDocuments()
{
	RemoveAll();
}

INT CRecentDocuments::Add(CRecentDocumentInfo *pDocumentInfo)
{
	return((INT)CPtrArray::Add(pDocumentInfo));
}

INT CRecentDocuments::Find(LPCTSTR pszName) CONST
{
	INT  nDocument;
	INT  nDocuments;
	CStringArray  szDocuments;

	for (nDocument = 0, nDocuments = Enum(szDocuments); nDocument < nDocuments; nDocument++)
	{
		if (szDocuments.GetAt(nDocument) == pszName) break;
		continue;
	}
	return((nDocument < nDocuments) ? nDocument : -1);
}

INT CRecentDocuments::Enum(CStringArray &szNames) CONST
{
	INT  nDocument;
	INT  nDocuments;
	CString  szName;
	CString  szTitle;
	ULONGLONG  nComponent;
	CRecentDocumentInfo  *pDocumentInfo;

	for (nDocument = 0, nDocuments = (INT)GetSize(), szNames.RemoveAll(); nDocument < nDocuments; nDocument++)
	{
		if ((pDocumentInfo = GetAt(nDocument)) && pDocumentInfo->GetDocument(szName, szTitle, nComponent))
		{
			szNames.Add(szName);
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CRecentDocumentInfo *CRecentDocuments::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CRecentDocumentInfo *)CPtrArray::GetAt(nIndex) : (CRecentDocumentInfo *)NULL);
}

CRecentDocumentInfo *CRecentDocuments::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CRecentDocumentInfo *)CPtrArray::GetAt(nIndex) : (CRecentDocumentInfo *)NULL);
}

VOID CRecentDocuments::RemoveAll()
{
	INT  nDocument;
	INT  nDocuments;

	for (nDocument = 0, nDocuments = (INT)GetSize(); nDocument < nDocuments; nDocument++)
	{
		delete GetAt(nDocument);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CRecentDocuments::Copy(CONST CRecentDocuments *pDocuments)
{
	INT  nDocument;
	INT  nDocuments;
	CRecentDocumentInfo  *pDocumentInfo;

	for (nDocument = 0, nDocuments = (INT)pDocuments->GetSize(), RemoveAll(); nDocument < nDocuments; nDocument++)
	{
		if ((pDocumentInfo = new CRecentDocumentInfo) != (CRecentDocumentInfo *)NULL)
		{
			pDocumentInfo->Copy(pDocuments->GetAt(nDocument));
			InsertAt(nDocument, pDocumentInfo, 1);
			continue;
		}
		break;
	}
	return((nDocument == nDocuments) ? TRUE : FALSE);
}

BOOL CRecentDocuments::Compare(CONST CRecentDocuments *pDocuments) CONST
{
	INT  nDocument;
	INT  nDocuments;

	for (nDocument = 0, nDocuments = (pDocuments->GetSize() == GetSize()) ? (INT)GetSize() : -1; nDocument < nDocuments; nDocument++)
	{
		if (!pDocuments->GetAt(nDocument)->Compare(GetAt(nDocument))) break;
		continue;
	}
	return((nDocument == nDocuments) ? TRUE : FALSE);
}

BOOL CRecentDocuments::Map(CByteArray &nInfo) CONST
{
	INT  nDocument;
	INT  nDocuments;
	CByteArray  nDocumentData;
	CRecentDocumentInfo  *pDocumentInfo;

	for (nDocument = 0, nDocuments = (INT)GetSize(), nInfo.RemoveAll(); nDocument < nDocuments; nDocument++)
	{
		if ((pDocumentInfo = GetAt(nDocument)) && pDocumentInfo->Map(nDocumentData) && nInfo.Append(nDocumentData) >= 0)
			break;
	}
	return((nDocument == nDocuments) ? TRUE : FALSE);
}

BOOL CRecentDocuments::Unmap(CONST CByteArray &nInfo)
{
	INT  cbDocument;
	INT  cbDocuments;
	CByteArray  nDocumentData;
	CRecentDocumentInfo  *pDocumentInfo;

	for (cbDocuments = 0, RemoveAll(); cbDocuments < nInfo.GetSize(); cbDocuments += cbDocument)
	{
		for (CopyMemory(&cbDocument, nInfo.GetData() + cbDocuments, sizeof(cbDocument)), nDocumentData.SetSize(max(min(cbDocument, nInfo.GetSize() - cbDocuments), 0)); nDocumentData.GetSize() >= 0; )
		{
			CopyMemory(nDocumentData.GetData(), nInfo.GetData() + cbDocuments, nDocumentData.GetSize());
			break;
		}
		if ((pDocumentInfo = new CRecentDocumentInfo))
		{
			if (pDocumentInfo->Unmap(nDocumentData) && Add(pDocumentInfo) >= 0) continue;
			delete pDocumentInfo;
		}
		break;
	}
	return((cbDocuments == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CRecentDatabaseInfo

CRecentDatabaseInfo::CRecentDatabaseInfo() : CDatabaseProfileInfo()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CRecentDatabases

CRecentDatabases::CRecentDatabases() : CDatabaseProfiles()
{
	return;
}

CRecentDatabases::~CRecentDatabases()
{
	RemoveAll();
}

INT CRecentDatabases::Add(CRecentDatabaseInfo *pDatabaseInfo)
{
	return((INT)CPtrArray::Add(pDatabaseInfo));
}

INT CRecentDatabases::Find(LPCTSTR pszName) CONST
{
	INT  nDatabase;
	INT  nDatabases;
	CStringArray  szDatabases;

	for (nDatabase = 0, nDatabases = Enum(szDatabases); nDatabase < nDatabases; nDatabase++)
	{
		if (szDatabases.GetAt(nDatabase) == pszName) break;
		continue;
	}
	return((nDatabase < nDatabases) ? nDatabase : -1);
}

INT CRecentDatabases::Enum(CStringArray &szNames) CONST
{
	INT  nDatabase;
	INT  nDatabases;
	CRecentDatabaseInfo  *pDatabaseInfo;

	for (nDatabase = 0, nDatabases = (INT)GetSize(), szNames.RemoveAll(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseInfo = GetAt(nDatabase)) != (CRecentDatabaseInfo *)NULL)
		{
			szNames.Add(pDatabaseInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CRecentDatabaseInfo *CRecentDatabases::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CRecentDatabaseInfo *)CPtrArray::GetAt(nIndex) : (CRecentDatabaseInfo *)NULL);
}

CRecentDatabaseInfo *CRecentDatabases::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CRecentDatabaseInfo *)CPtrArray::GetAt(nIndex) : (CRecentDatabaseInfo *)NULL);
}

VOID CRecentDatabases::RemoveAll()
{
	INT  nDatabase;
	INT  nDatabases;

	for (nDatabase = 0, nDatabases = (INT)GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		delete GetAt(nDatabase);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CRecentDatabases::Copy(CONST CRecentDatabases *pDatabases)
{
	INT  nDatabase;
	INT  nDatabases;
	CRecentDatabaseInfo  *pDatabaseInfo;

	for (nDatabase = 0, nDatabases = (INT)pDatabases->GetSize(), RemoveAll(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseInfo = new CRecentDatabaseInfo) != (CRecentDatabaseInfo *)NULL)
		{
			pDatabaseInfo->Copy(pDatabases->GetAt(nDatabase));
			InsertAt(nDatabase, pDatabaseInfo, 1);
			continue;
		}
		RemoveAll();
		break;
	}
	return((nDatabase == nDatabases) ? TRUE : FALSE);
}

BOOL CRecentDatabases::Compare(CONST CRecentDatabases *pDatabases) CONST
{
	INT  nDatabase;
	INT  nDatabases;

	for (nDatabase = 0, nDatabases = (pDatabases->GetSize() == GetSize()) ? (INT)GetSize() : -1; nDatabase < nDatabases; nDatabase++)
	{
		if (!pDatabases->GetAt(nDatabase)->Compare(GetAt(nDatabase))) break;
		continue;
	}
	return((nDatabase == nDatabases) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarToolTipCtrl

IMPLEMENT_DYNCREATE(CMainStatusBarToolTipCtrl, CToolTipCtrl)

BOOL CMainStatusBarToolTipCtrl::UpdateTipText(LPCTSTR pszText, CWnd *pWnd, UINT nToolID)
{
	m_szText = pszText;
	m_sInfo.uFlags = 0;
	m_sInfo.uId = nToolID;
	m_sInfo.cbSize = sizeof(m_sInfo);
	m_sInfo.hwnd = pWnd->GetSafeHwnd();
	m_sInfo.lpszText = (LPTSTR)(LPCTSTR)m_szText;
	return((IsWindow(GetSafeHwnd())) ? SendNotifyMessage(TTM_UPDATETIPTEXT, 0, (LPARAM)&m_sInfo) : FALSE);
}

BEGIN_MESSAGE_MAP(CMainStatusBarToolTipCtrl, CToolTipCtrl)
	//{{AFX_MSG_MAP(CMainStatusBarToolTipCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarToolTipCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainStatusBar

IMPLEMENT_DYNCREATE(CMainStatusBar, CMFCStatusBar)

BOOL CMainStatusBar::Create(CWnd *pParentWnd, DWORD dwStyle, UINT nID)
{
	CUIntArray  nPaneIDs;

	if (CMFCStatusBar::Create(pParentWnd, dwStyle, nID))
	{
		SetIndicators(nPaneIDs);
		return TRUE;
	}
	return FALSE;
}

BOOL CMainStatusBar::SetIndicators()
{
	return SetIndicators(m_nPaneIDs.GetData(), (INT)m_nPaneIDs.GetSize());
}
BOOL CMainStatusBar::SetIndicators(CONST UINT *pID, INT nSize)
{
	INT  nIndex;
	INT  nCount;
	CRect  rBar;
	CRect  rPane[8];
	CString  szPane;
	CToolInfo  cToolInfo;

	for (szPane = ((nIndex = CommandToIndex(ID_STATUSBAR_MESSAGEPANE)) >= 0) ? GetPaneText(nIndex) : EMPTYSTRING; CMFCStatusBar::SetIndicators(pID, (nCount = (TestAccount()) ? nSize : 1)); )
	{
		for (nIndex = 0; nIndex < nCount; nIndex++)
		{
			if (pID[nIndex] == ID_STATUSBAR_MESSAGEPANE)
			{
				for (GetClientRect(rBar), SetPaneStyle(nIndex, SBPS_NOBORDERS | SBPS_STRETCH); nCount > 1; )
				{
					SetPaneWidth(nIndex, 2 * rBar.Height());
					break;
				}
				continue;
			}
			if (pID[nIndex] == ID_STATUSBAR_SERVERPANE)
			{
				if (!IsWindow(m_wndToolTip[0].GetSafeHwnd()))
				{
					m_wndToolTip[0].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[0].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[0].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_SPACECRAFTPANE)
			{
				if (!IsWindow(m_wndToolTip[1].GetSafeHwnd()))
				{
					m_wndToolTip[1].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[1].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[1].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_USERPANE)
			{
				if (!IsWindow(m_wndToolTip[2].GetSafeHwnd()))
				{
					m_wndToolTip[2].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[2].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[2].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_DATABASEPANE)
			{
				if (!IsWindow(m_wndToolTip[3].GetSafeHwnd()))
				{
					m_wndToolTip[3].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[3].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[3].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_CAPSKEYPANE)
			{
				if (!IsWindow(m_wndToolTip[4].GetSafeHwnd()))
				{
					m_wndToolTip[4].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[4].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[4].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_NUMKEYPANE)
			{
				if (!IsWindow(m_wndToolTip[5].GetSafeHwnd()))
				{
					m_wndToolTip[5].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[5].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[5].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_SCRLKEYPANE)
			{
				if (!IsWindow(m_wndToolTip[6].GetSafeHwnd()))
				{
					m_wndToolTip[6].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[6].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[6].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_OVRKEYPANE)
			{
				if (!IsWindow(m_wndToolTip[7].GetSafeHwnd()))
				{
					m_wndToolTip[7].Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
					SetClassLongPtr(m_wndToolTip[7].GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip[7].GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
				}
			}
		}
		for (nIndex = 0; nIndex < nCount; nIndex++)
		{
			if (pID[nIndex] == ID_STATUSBAR_SERVERPANE)
			{
				if (IsWindow(m_wndToolTip[0].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[0]); !m_wndToolTip[0].GetToolInfo(cToolInfo, this, ID_STATUSBAR_SERVERPANE); )
					{
						m_wndToolTip[0].AddTool(this, LPSTR_TEXTCALLBACK, rPane[0], ID_STATUSBAR_SERVERPANE);
						m_wndToolTip[0].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[0].Activate(TRUE);
						break;
					}
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_SPACECRAFTPANE)
			{
				if (IsWindow(m_wndToolTip[1].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[1]); !m_wndToolTip[1].GetToolInfo(cToolInfo, this, ID_STATUSBAR_SPACECRAFTPANE); )
					{
						m_wndToolTip[1].AddTool(this, LPSTR_TEXTCALLBACK, rPane[1], ID_STATUSBAR_SPACECRAFTPANE);
						m_wndToolTip[1].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[1].Activate(TRUE);
						break;
					}
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_USERPANE)
			{
				if (IsWindow(m_wndToolTip[2].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[2]); !m_wndToolTip[2].GetToolInfo(cToolInfo, this, ID_STATUSBAR_USERPANE); )
					{
						m_wndToolTip[2].AddTool(this, LPSTR_TEXTCALLBACK, rPane[2], ID_STATUSBAR_USERPANE);
						m_wndToolTip[2].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[2].Activate(TRUE);
						break;
					}
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_DATABASEPANE)
			{
				if (IsWindow(m_wndToolTip[3].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[3]); !m_wndToolTip[3].GetToolInfo(cToolInfo, this, ID_STATUSBAR_DATABASEPANE); )
					{
						m_wndToolTip[3].AddTool(this, LPSTR_TEXTCALLBACK, rPane[3], ID_STATUSBAR_DATABASEPANE);
						m_wndToolTip[3].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[3].Activate(TRUE);
						break;
					}
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_CAPSKEYPANE)
			{
				if (IsWindow(m_wndToolTip[4].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[4]); !m_wndToolTip[4].GetToolInfo(cToolInfo, this, ID_STATUSBAR_CAPSKEYPANE); )
					{
						m_wndToolTip[4].AddTool(this, LPSTR_TEXTCALLBACK, rPane[4], ID_STATUSBAR_CAPSKEYPANE);
						m_wndToolTip[4].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[4].Activate(TRUE);
						break;
					}
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_NUMKEYPANE)
			{
				if (IsWindow(m_wndToolTip[5].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[5]); !m_wndToolTip[5].GetToolInfo(cToolInfo, this, ID_STATUSBAR_NUMKEYPANE); )
					{
						m_wndToolTip[5].AddTool(this, LPSTR_TEXTCALLBACK, rPane[5], ID_STATUSBAR_NUMKEYPANE);
						m_wndToolTip[5].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[5].Activate(TRUE);
						break;
					}
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_SCRLKEYPANE)
			{
				if (IsWindow(m_wndToolTip[6].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[6]); !m_wndToolTip[6].GetToolInfo(cToolInfo, this, ID_STATUSBAR_SCRLKEYPANE); )
					{
						m_wndToolTip[6].AddTool(this, LPSTR_TEXTCALLBACK, rPane[6], ID_STATUSBAR_SCRLKEYPANE);
						m_wndToolTip[6].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[6].Activate(TRUE);
						break;
					}
				}
			}
			if (pID[nIndex] == ID_STATUSBAR_OVRKEYPANE)
			{
				if (IsWindow(m_wndToolTip[7].GetSafeHwnd()))
				{
					for (GetItemRect(nIndex, rPane[7]); !m_wndToolTip[7].GetToolInfo(cToolInfo, this, ID_STATUSBAR_OVRKEYPANE); )
					{
						m_wndToolTip[7].AddTool(this, LPSTR_TEXTCALLBACK, rPane[7], ID_STATUSBAR_OVRKEYPANE);
						m_wndToolTip[7].SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
						m_wndToolTip[7].Activate(TRUE);
						break;
					}
				}
			}
		}
		if (CommandToIndex(ID_STATUSBAR_SERVERPANE) < 0) m_wndToolTip[0].DestroyWindow();
		if (CommandToIndex(ID_STATUSBAR_SPACECRAFTPANE) < 0) m_wndToolTip[1].DestroyWindow();
		if (CommandToIndex(ID_STATUSBAR_USERPANE) < 0) m_wndToolTip[2].DestroyWindow();
		if (CommandToIndex(ID_STATUSBAR_DATABASEPANE) < 0) m_wndToolTip[3].DestroyWindow();
		if (CommandToIndex(ID_STATUSBAR_CAPSKEYPANE) < 0) m_wndToolTip[4].DestroyWindow();
		if (CommandToIndex(ID_STATUSBAR_NUMKEYPANE) < 0) m_wndToolTip[5].DestroyWindow();
		if (CommandToIndex(ID_STATUSBAR_SCRLKEYPANE) < 0) m_wndToolTip[6].DestroyWindow();
		if (CommandToIndex(ID_STATUSBAR_OVRKEYPANE) < 0) m_wndToolTip[7].DestroyWindow();
		SetPaneText(CommandToIndex(ID_STATUSBAR_MESSAGEPANE), szPane);
		return TRUE;
	}
	return FALSE;
}
VOID CMainStatusBar::SetIndicators(CONST CUIntArray &nPaneIDs)
{
	for (m_nPaneIDs.Copy(nPaneIDs); !nPaneIDs.GetSize(); )
	{
		m_nPaneIDs.SetSize(sizeof(nStatusBarIndicators) / sizeof(nStatusBarIndicators[0]));
		CopyMemory(m_nPaneIDs.GetData(), nStatusBarIndicators, m_nPaneIDs.GetSize()*sizeof(UINT));
		break;
	}
}

INT CMainStatusBar::GetIndicators(CUIntArray &nPaneIDs) CONST
{
	nPaneIDs.Copy(m_nPaneIDs);
	return((INT)nPaneIDs.GetSize());
}

BOOL CMainStatusBar::UpdateAllPanes()
{
	CString  szDatabase;

	SetPaneText(CommandToIndex(ID_STATUSBAR_SERVERPANE), GetAccountComputerName());
	SetPaneText(CommandToIndex(ID_STATUSBAR_SPACECRAFTPANE), GetAccountSpacecraftName());
	SetPaneText(CommandToIndex(ID_STATUSBAR_USERPANE), GetAccountUserName());
	SetPaneText(CommandToIndex(ID_STATUSBAR_DATABASEPANE), (!(szDatabase = GetAccountDatabase()).IsEmpty()) ? szDatabase : STRING(IDS_STATUSBAR_NODATABASETEXT));
	SetPaneText(CommandToIndex(ID_STATUSBAR_CAPSKEYPANE), STRING(IDS_STATUSBAR_CAPSKEYPANETEXT));
	SetPaneText(CommandToIndex(ID_STATUSBAR_NUMKEYPANE), STRING(IDS_STATUSBAR_NUMKEYPANETEXT));
	SetPaneText(CommandToIndex(ID_STATUSBAR_SCRLKEYPANE), STRING(IDS_STATUSBAR_SCRLKEYPANETEXT));
	SetPaneText(CommandToIndex(ID_STATUSBAR_OVRKEYPANE), STRING(IDS_STATUSBAR_OVRKEYPANETEXT));
	return TRUE;
}

CMainWnd *CMainStatusBar::GetParent() CONST
{
	return((CMainWnd *)CMFCStatusBar::GetParent());
}

INT CMainStatusBar::CalcPaneWidth(LPCTSTR pszText)
{
	CDC  *pDC;
	INT  nWidth;
	CFont  *pOldFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			nWidth = pDC->GetTextExtent(SPACE + CString(pszText) + SPACE).cx;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

VOID CMainStatusBar::RecalcPanes()
{
	INT  nIndex;
	INT  nCount;
	INT  nWidth;
	UINT  nID;
	UINT  nStyle;
	CRect  rBar;
	CRect  rPane;

	for (nIndex = 0, nCount = GetCount(), GetClientRect(rBar); nIndex < nCount; nIndex++)
	{
		for (GetItemRect(nIndex, rPane), GetPaneInfo(nIndex, nID, nStyle, nWidth); (nStyle & SBPS_STRETCH) != SBPS_STRETCH && rPane.IntersectRect(rBar, rPane); )
		{
			SetPaneInfo(nIndex, nID, nStyle, CalcPaneWidth(GetPaneText(nIndex)));
			break;
		}
	}
}

BEGIN_MESSAGE_MAP(CMainStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CMainStatusBar)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBar message handlers

int CMainStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFont  *pFont;
	LOGFONT  lfFont;

	if (CMFCStatusBar::OnCreate(lpCreateStruct) != -1)
	{
		if ((pFont = GetFont()) && pFont->GetLogFont(&lfFont) > 0 && m_cPanesFont.CreateFontIndirect(&lfFont))
		{
			EnableToolTips();
			return 0;
		}
	}
	return -1;
}

BOOL CMainStatusBar::OnEraseBkgnd(CDC *pDC)
{
	RecalcPanes();
	return CMFCStatusBar::OnEraseBkgnd(pDC);
}

void CMainStatusBar::OnPaint()
{
	INT  nIndex;
	INT  nCount;
	CRect  rPane;
	CToolInfo  cToolInfo;

	for (nIndex = 1, nCount = GetCount(), RecalcPanes(); nIndex < nCount; nIndex++)
	{
		for (GetItemRect(nIndex, rPane); IsWindow(m_wndToolTip[nIndex - 1].GetSafeHwnd()); )
		{
			for (m_wndToolTip[nIndex - 1].GetToolInfo(cToolInfo, this, GetItemID(nIndex)); !rPane.EqualRect(&cToolInfo.rect); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip[nIndex - 1].SetToolInfo(&cToolInfo);
				break;
			}
			break;
		}
	}
	CMFCStatusBar::OnPaint();
}

void CMainStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;
	INT  nToolTip;
	INT  nToolTips;

	for (nToolTip = 0, nToolTips = (INT)(sizeof(m_wndToolTip) / sizeof(CMainStatusBarToolTipCtrl)), CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG)); nToolTip < nToolTips; nToolTip++)
	{
		if (IsWindow(m_wndToolTip[nToolTip].GetSafeHwnd()))
		{
			m_wndToolTip[nToolTip].RelayEvent(&sMsg);
			continue;
		}
	}
	CMFCStatusBar::OnMouseMove(nFlags, point);
}

BOOL CMainStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_STATUSBAR_SERVERPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_STATUSBAR_SERVERPANETOOLTIP);
	return TRUE;
	}
	case ID_STATUSBAR_SPACECRAFTPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_STATUSBAR_SPACECRAFTPANETOOLTIP);
	return TRUE;
	}
	case ID_STATUSBAR_USERPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_STATUSBAR_USERPANETOOLTIP);
	return TRUE;
	}
	case ID_STATUSBAR_DATABASEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_STATUSBAR_DATABASEPANETOOLTIP);
	return TRUE;
	}
	case ID_STATUSBAR_CAPSKEYPANE:
	{ m_szToolTipText[0].Format(STRING(IDS_STATUSBAR_KEYSPANETOOLTIP), (LPCTSTR)GetPaneText(CommandToIndex((UINT)pNotifyInfo->idFrom)), (GetParent()->CheckKeyState(VK_CAPITAL)) ? STRING(IDS_STATUSBAR_KEYONTEXT) : STRING(IDS_STATUSBAR_KEYOFFTEXT));
	pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[0];
	return TRUE;
	}
	case ID_STATUSBAR_NUMKEYPANE:
	{ m_szToolTipText[1].Format(STRING(IDS_STATUSBAR_KEYSPANETOOLTIP), (LPCTSTR)GetPaneText(CommandToIndex((UINT)pNotifyInfo->idFrom)), (GetParent()->CheckKeyState(VK_NUMLOCK)) ? STRING(IDS_STATUSBAR_KEYONTEXT) : STRING(IDS_STATUSBAR_KEYOFFTEXT));
	pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[1];
	return TRUE;
	}
	case ID_STATUSBAR_SCRLKEYPANE:
	{ m_szToolTipText[2].Format(STRING(IDS_STATUSBAR_KEYSPANETOOLTIP), (LPCTSTR)GetPaneText(CommandToIndex((UINT)pNotifyInfo->idFrom)), (GetParent()->CheckKeyState(VK_SCROLL)) ? STRING(IDS_STATUSBAR_KEYONTEXT) : STRING(IDS_STATUSBAR_KEYOFFTEXT));
	pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[2];
	return TRUE;
	}
	case ID_STATUSBAR_OVRKEYPANE:
	{ m_szToolTipText[3].Format(STRING(IDS_STATUSBAR_KEYSPANETOOLTIP), (LPCTSTR)GetPaneText(CommandToIndex((UINT)pNotifyInfo->idFrom)), (GetParent()->CheckKeyState(VK_INSERT)) ? STRING(IDS_STATUSBAR_KEYONTEXT) : STRING(IDS_STATUSBAR_KEYOFFTEXT));
	pToolTipInfo->lpszText = (LPTSTR)(LPCTSTR)m_szToolTipText[3];
	return TRUE;
	}
	}
	return FALSE;
}

LRESULT CMainStatusBar::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	CFont  cFont;
	LOGFONT  lfFont;
	LRESULT  lResult;

	for (lResult = Default(); wParam != (WPARAM)NULL; )
	{
		if (GetObject((HGDIOBJ)wParam, sizeof(LOGFONT), &lfFont) > 0 && cFont.CreateFontIndirect(&lfFont))
		{
			m_cPanesFont.DeleteObject();
			m_cPanesFont.Attach(cFont.Detach());
		}
		break;
	}
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CToolButton

IMPLEMENT_DYNCREATE(CToolButton, CBitmapButton)

void CToolButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  *pDC;

	if ((pDC = CDC::FromHandle(lpDrawItemStruct->hDC)))
	{
		DrawButton(pDC);
	}
}

VOID CToolButton::DrawButton(CDC *pDC)
{
	CRect  rButton;

	GetClientRect(rButton);
	if (GetState() & BST_PUSHED)
	{
		pDC->DrawFrameControl(rButton, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
		DrawButtonSymbol(pDC, &m_bitmapSel);
		return;
	}
	if (!IsWindowEnabled())
	{
		pDC->DrawFrameControl(rButton, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_INACTIVE);
		DrawButtonSymbol(pDC, &m_bitmapDisabled);
		return;
	}
	pDC->DrawFrameControl(rButton, DFC_BUTTON, DFCS_BUTTONPUSH);
	DrawButtonSymbol(pDC, &m_bitmap);
}

VOID CToolButton::DrawButtonSymbol(CDC *pDC, CBitmap *pBitmap)
{
	CDC  cMemDC;
	BITMAP  sBitmap;
	CBitmap  *pOldBitmap;

	if (cMemDC.CreateCompatibleDC(pDC))
	{
		if (pBitmap->GetObject(sizeof(BITMAP), &sBitmap))
		{
			if ((pOldBitmap = cMemDC.SelectObject(pBitmap)))
			{
				pDC->BitBlt(0, 0, sBitmap.bmWidth, sBitmap.bmHeight, &cMemDC, 0, 0, SRCAND);
				cMemDC.SelectObject(pOldBitmap);
			}
		}
		cMemDC.DeleteDC();
	}
}

BEGIN_MESSAGE_MAP(CToolButton, CBitmapButton)
	//{{AFX_MSG_MAP(CToolButton)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolButton message handlers

BOOL CToolButton::OnEraseBkgnd(CDC *pDC)
{
	UpdateWindow();
	return TRUE;
}

void CToolButton::OnPaint()
{
	CPaintDC  cDC(this);

	DrawButton(&cDC);
}


/////////////////////////////////////////////////////////////////////////////
// CToolSizeBarCtrl

IMPLEMENT_DYNCREATE(CToolSizeBarCtrl, CWnd)

CToolSizeBarCtrl::CToolSizeBarCtrl() : CWnd()
{
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CToolSizeBarCtrl::Create(CWnd *pParentWnd)
{
	return CWnd::CreateEx(0, AfxRegisterWndClass(CS_NOCLOSE), EMPTYSTRING, WS_POPUP, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd)->GetTopLevelParent(), 0);
}

VOID CToolSizeBarCtrl::Activate(CONST RECT &rect)
{
	CRect  rBar;

	for (GetParent()->StartSizing(); rect.right - rect.left > rect.bottom - rect.top; )
	{
		rBar.SetRect(rect.left, rect.top + (rect.bottom - rect.top) / 2 - GetSystemMetrics(SM_CYFRAME) / 2, rect.right, rect.top + (rect.bottom - rect.top) / 2 - GetSystemMetrics(SM_CYFRAME) / 2 + GetSystemMetrics(SM_CYFRAME));
		break;
	}
	for (; rect.right - rect.left < rect.bottom - rect.top; )
	{
		rBar.SetRect(rect.left + (rect.right - rect.left) / 2 - GetSystemMetrics(SM_CXFRAME) / 2, rect.top, rect.left + (rect.right - rect.left) / 2 - GetSystemMetrics(SM_CXFRAME) / 2 + GetSystemMetrics(SM_CXFRAME), rect.bottom);
		break;
	}
	MoveWindow(rBar);
	ShowWindow(SW_SHOW);
	UpdateWindow();
	SetCapture();
}

VOID CToolSizeBarCtrl::Deactivate()
{
	ReleaseCapture();
	ShowWindow(SW_HIDE);
	GetParent()->StopSizing();
}

CToolWnd *CToolSizeBarCtrl::GetParent() CONST
{
	return((CToolWnd *)m_pParentWnd);
}

BEGIN_MESSAGE_MAP(CToolSizeBarCtrl, CWnd)
	//{{AFX_MSG_MAP(CToolSizeBarCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolSizeBarCtrl message handlers

BOOL CToolSizeBarCtrl::OnEraseBkgnd(CDC *pDC)
{
	CRect  rBar;

	GetClientRect(rBar);
	pDC->DrawDragRect(rBar, CSize(GetSystemMetrics(SM_CXFRAME), GetSystemMetrics(SM_CYFRAME)), (LPCRECT)NULL, CSize(0, 0));
	return TRUE;
}

void CToolSizeBarCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect  rBar;
	CPoint  pt;

	pt = point;
	ClientToScreen(&pt);
	GetWindowRect(rBar);
	GetParent()->AdjustSizeBar(pt, rBar);
	MoveWindow(rBar.left, rBar.top, rBar.Width(), rBar.Height());
	GetMainWnd()->RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
	GetMainWnd()->GetZoomWindow()->RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);
	CWnd::OnMouseMove(nFlags, point);
}

void CToolSizeBarCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	Deactivate();
}


/////////////////////////////////////////////////////////////////////////////
// CToolWnd

IMPLEMENT_DYNCREATE(CToolWnd, CMiniFrameWnd)

CToolWnd::CToolWnd(CToolWnd *pToolWnd) : CMiniFrameWnd()
{
	m_bVisible = FALSE;
	m_bDragFull = FALSE;
	m_bDockDrag = FALSE;
	m_bDockSize = FALSE;
	m_ptDockDrag.x = -1;
	m_ptDockDrag.y = -1;
	m_rDockDrag.SetRectEmpty();
	m_rDockRect.SetRectEmpty();
	m_bDockFull = !AfxIsValidAddress(pToolWnd, sizeof(CToolWnd));
	m_nDockState = (!m_bDockFull) ? pToolWnd->m_nDockState : 0;
	m_sizeDefault[TOOLWINDOW_SIZE_DOCKED] = (!m_bDockFull) ? pToolWnd->m_sizeDefault[TOOLWINDOW_SIZE_DOCKED] : CSize(TOOLWINDOW_SIZE_WIDTH, TOOLWINDOW_SIZE_HEIGHT);
	m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED] = (!m_bDockFull) ? pToolWnd->m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED] : CSize(TOOLWINDOW_SIZE_WIDTH, TOOLWINDOW_SIZE_HEIGHT);
	m_sizeDefault[TOOLWINDOW_SIZE_FLOATING] = (!m_bDockFull) ? pToolWnd->m_sizeDefault[TOOLWINDOW_SIZE_FLOATING] : CSize(TOOLWINDOW_SIZE_WIDTH, TOOLWINDOW_SIZE_HEIGHT);
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CToolWnd::Create(CWnd *pParentWnd, LPCTSTR pszTitle, DWORD dwStyle, CONST RECT &rect, UINT nID)
{
	if (CMiniFrameWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), pszTitle, (dwStyle & TWS_FLOATING) ? ((dwStyle | TWS_NOEXPANDBUTTON | TWS_NOHIDEBUTTON | MFS_SYNCACTIVE | MFS_THICKFRAME | WS_POPUP | WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_DLGFRAME | WS_SYSMENU) & ~(MFS_4THICKFRAME | MFS_MOVEFRAME | MFS_BLOCKSYSMENU | WS_CHILD | WS_THICKFRAME | WS_VISIBLE)) : ((dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS) & ~(MFS_4THICKFRAME | MFS_MOVEFRAME | MFS_BLOCKSYSMENU | MFS_SYNCACTIVE | MFS_THICKFRAME | WS_POPUP | WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_SYSMENU | WS_VISIBLE)), rect, (m_pParentWnd = pParentWnd), nID))
	{
		ModifyStyleEx(0, (dwStyle & TWS_FLOATING) ? (WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE) : 0);
		ShowWindow((dwStyle & WS_VISIBLE) ? SW_SHOWNORMAL : SW_HIDE);
		SetTitle(pszTitle);
		return TRUE;
	}
	return FALSE;
}

VOID CToolWnd::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CToolWnd::GetTitle() CONST
{
	return m_szTitle;
}

VOID CToolWnd::SetDockState(UINT nState)
{
	m_nDockState = MAKELONG((WORD)nState, HIWORD(m_nDockState));
}

UINT CToolWnd::GetDockState(BOOL bAll) CONST
{
	return((!bAll) ? (LOWORD(m_nDockState) & (TOOLWINDOW_DOCKSTATE_LEFT | TOOLWINDOW_DOCKSTATE_TOP | TOOLWINDOW_DOCKSTATE_RIGHT | TOOLWINDOW_DOCKSTATE_BOTTOM)) : LOWORD(m_nDockState));
}

VOID CToolWnd::SetDraggedDockState(UINT nState)
{
	m_nDockState = MAKELONG(LOWORD(m_nDockState), (WORD)nState);
}

UINT CToolWnd::GetDraggedDockState(BOOL bAll) CONST
{
	return((!bAll) ? (HIWORD(m_nDockState) & (TOOLWINDOW_DOCKSTATE_LEFT | TOOLWINDOW_DOCKSTATE_TOP | TOOLWINDOW_DOCKSTATE_RIGHT | TOOLWINDOW_DOCKSTATE_BOTTOM)) : HIWORD(m_nDockState));
}

UINT CToolWnd::GetDockSide() CONST
{
	CRect  rArea[2];
	CRect  rToolWnd;

	GetWindowRect(rToolWnd);
	GetParent()->ScreenToClient(rToolWnd);
	rArea[0] = GetParent()->CalcClientRect(TRUE);
	rArea[1] = GetParent()->CalcClientRect(FALSE);
	return(((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (((rArea[1].top >= rToolWnd.top) ? TOOLWINDOW_DOCKSTATE_TOP : 0) | ((rArea[1].bottom <= rToolWnd.bottom) ? TOOLWINDOW_DOCKSTATE_BOTTOM : 0) | ((rArea[1].left >= rToolWnd.left) ? TOOLWINDOW_DOCKSTATE_LEFT : 0) | ((rArea[1].right <= rToolWnd.right) ? TOOLWINDOW_DOCKSTATE_RIGHT : 0)) : (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (((rArea[1].left >= rToolWnd.left) ? TOOLWINDOW_DOCKSTATE_LEFT : 0) | ((rArea[0].top >= rToolWnd.top) ? TOOLWINDOW_DOCKSTATE_TOP : 0) | ((rArea[1].right <= rToolWnd.right) ? TOOLWINDOW_DOCKSTATE_RIGHT : 0) | ((rArea[0].bottom <= rToolWnd.bottom) ? TOOLWINDOW_DOCKSTATE_BOTTOM : 0)) : 0));
}

BOOL CToolWnd::IsDocked(BOOL bAll) CONST
{
	return((!bAll) ? ((!(GetStyle() & TWS_FLOATING)) ? TRUE : FALSE) : m_bDockFull);
}

VOID CToolWnd::SetDockRect()
{
	m_rDockRect.SetRectEmpty();
}
VOID CToolWnd::SetDockRect(CONST RECT &rect)
{
	m_rDockRect.SetRect(rect.left, rect.top, rect.right, rect.bottom);
}

VOID CToolWnd::GetDockRect(LPRECT lpRect) CONST
{
	CRect  rToolWnd;

	GetWindowRect(rToolWnd);
	SetRect(lpRect, (!m_rDockRect.IsRectEmpty()) ? m_rDockRect.left : rToolWnd.left, (!m_rDockRect.IsRectEmpty()) ? m_rDockRect.top : rToolWnd.top, (!m_rDockRect.IsRectEmpty()) ? m_rDockRect.right : rToolWnd.right, (!m_rDockRect.IsRectEmpty()) ? m_rDockRect.bottom : rToolWnd.bottom);
}

VOID CToolWnd::SetDefaultSize(CONST SIZE &size)
{
	INT  nCount;

	if (size.cx > 0 || size.cy > 0)
	{
		if (IsDocked() && !IsExpanded() && !IsShrinked())
		{
			if ((nCount = GetParent()->EnumToolWindows(this)) >= 0 && nCount <= 1)
			{
				m_sizeDefault[TOOLWINDOW_SIZE_DOCKED] = CSize(((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? size.cx : m_sizeDefault[TOOLWINDOW_SIZE_DOCKED].cx, ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? size.cy : m_sizeDefault[TOOLWINDOW_SIZE_DOCKED].cy);
				return;
			}
			m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED] = CSize(((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED].cx : size.cx, ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED].cy : size.cy);
			return;
		}
		if (!IsDocked())
		{
			m_sizeDefault[TOOLWINDOW_SIZE_FLOATING] = size;
			return;
		}
	}
}

CSize CToolWnd::GetDefaultSize(UINT nState) CONST
{
	return((nState == TOOLWINDOW_SIZE_DOCKED || nState == TOOLWINDOW_SIZE_MULTIDOCKED || nState == TOOLWINDOW_SIZE_FLOATING) ? m_sizeDefault[nState] : CSize(0, 0));
}
CSize CToolWnd::GetDefaultSize() CONST
{
	return((IsDocked() && !IsExpanded() && !IsShrinked()) ? m_sizeDefault[TOOLWINDOW_SIZE_DOCKED] : ((IsDocked()) ? m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED] : m_sizeDefault[TOOLWINDOW_SIZE_FLOATING]));
}

VOID CToolWnd::Show()
{
	SendNotifyMessage(WM_SHOWWINDOW, TRUE, (LPARAM)-1);
}

VOID CToolWnd::Hide()
{
	SendNotifyMessage(WM_SHOWWINDOW, FALSE, (LPARAM)-1);
}

BOOL CToolWnd::IsVisible() CONST
{
	return m_bVisible;
}

VOID CToolWnd::Expand(BOOL bContract)
{
	CRect  rPane;
	CRect  rToolWnd;
	CSize  sizeToolWnd;
	CToolWnd  *pToolWnd;
	CPtrArray  pToolWnds;

	GetWindowRect(rToolWnd);
	if (GetParent()->EnumToolPane(GetDockState(), GetParent()->FindToolPane(GetDockState(), rToolWnd), rPane, pToolWnds) > 1)
	{
		for (rToolWnd.SetRect(rPane.left, rPane.top, rPane.right, rPane.bottom), GetParent()->ScreenToClient(rToolWnd); pToolWnds.GetSize() && !bContract; rToolWnd.DeflateRect(((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? pToolWnd->CalcExtent().cx : 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? pToolWnd->CalcExtent().cy : 0, 0, 0))
		{
			if ((pToolWnd = (CToolWnd *)pToolWnds.GetAt(0)) && pToolWnd != this)
			{
				pToolWnd->Shrink(CRect(rToolWnd.left, rToolWnd.top, ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.left + pToolWnd->CalcExtent().cx) : rToolWnd.right, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.top + pToolWnd->CalcExtent().cy) : rToolWnd.bottom));
				pToolWnds.RemoveAt(0);
				continue;
			}
			break;
		}
		for (; pToolWnds.GetSize() && !bContract; rToolWnd.DeflateRect(0, 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? pToolWnd->CalcExtent().cx : 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? pToolWnd->CalcExtent().cy : 0))
		{
			if ((pToolWnd = (CToolWnd *)pToolWnds.GetAt(pToolWnds.GetUpperBound())) && pToolWnd != this)
			{
				pToolWnd->Shrink(CRect(((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.right - pToolWnd->CalcExtent().cx) : rToolWnd.left, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.bottom - pToolWnd->CalcExtent().cy) : rToolWnd.top, rToolWnd.right, rToolWnd.bottom));
				pToolWnds.RemoveAt(pToolWnds.GetUpperBound());
				continue;
			}
			break;
		}
		if (!bContract)
		{
			SetButtonBitmaps(TOOLWINDOW_DOCKSTATE_EXPANDED);
			MoveWindow(rToolWnd.left, rToolWnd.top, rToolWnd.Width(), rToolWnd.Height());
			return;
		}
		for (rToolWnd.SetRect(rPane.left, rPane.top, rPane.right, rPane.bottom), GetParent()->ScreenToClient(rToolWnd); pToolWnds.GetSize() && bContract; rToolWnd.DeflateRect(((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? sizeToolWnd.cx : 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? sizeToolWnd.cy : 0, 0, 0))
		{
			if ((pToolWnd = (CToolWnd *)pToolWnds.GetAt(0)) && pToolWnd != this)
			{
				pToolWnd->Shrink(CRect(rToolWnd.left, rToolWnd.top, ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.left + (sizeToolWnd.cx = pToolWnd->GetDefaultSize().cx)) : (rToolWnd.right + (sizeToolWnd.cx = 0)), ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.top + (sizeToolWnd.cy = pToolWnd->GetDefaultSize().cy)) : (rToolWnd.bottom + (sizeToolWnd.cy = 0))));
				pToolWnds.RemoveAt(0);
				continue;
			}
			break;
		}
		for (; pToolWnds.GetSize() && bContract; rToolWnd.DeflateRect(0, 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? sizeToolWnd.cx : 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? sizeToolWnd.cy : 0))
		{
			if ((pToolWnd = (CToolWnd *)pToolWnds.GetAt(pToolWnds.GetUpperBound())) && pToolWnd != this)
			{
				pToolWnd->Shrink(CRect(((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.right - (sizeToolWnd.cx = pToolWnd->GetDefaultSize().cx)) : (rToolWnd.left - (sizeToolWnd.cx = 0)), ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.bottom - (sizeToolWnd.cy = pToolWnd->GetDefaultSize().cy)) : (rToolWnd.top - (sizeToolWnd.cy = 0)), rToolWnd.right, rToolWnd.bottom));
				pToolWnds.RemoveAt(pToolWnds.GetUpperBound());
				continue;
			}
			break;
		}
		if (bContract)
		{
			Shrink(rToolWnd);
			return;
		}
	}
}

BOOL CToolWnd::IsExpanded() CONST
{
	return((GetDockState(TRUE) & TOOLWINDOW_DOCKSTATE_EXPANDED) ? TRUE : FALSE);
}

VOID CToolWnd::Shrink(LPCRECT pRect)
{
	SetButtonBitmaps(TOOLWINDOW_DOCKSTATE_SHRINKED);
	MoveWindow(pRect);
}

BOOL CToolWnd::IsShrinked() CONST
{
	return((GetDockState(TRUE) & TOOLWINDOW_DOCKSTATE_SHRINKED) ? TRUE : FALSE);
}

VOID CToolWnd::StartDragging()
{
	if (!IsDragged())
	{
		SetDraggedDockState(GetDockState((m_bDockDrag = TRUE)));
		SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &m_bDragFull, 0);
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, (LPVOID)NULL, 0);
	}
}

BOOL CToolWnd::IsDragged() CONST
{
	return m_bDockDrag;
}

VOID CToolWnd::StopDragging()
{
	if (IsDragged())
	{
		SetDockState(GetDraggedDockState(!(m_bDockDrag = FALSE)));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, m_bDragFull, (LPVOID)NULL, 0);
		GetMainWnd()->RepositionToolWindow(this, m_rDockDrag);
	}
}

VOID CToolWnd::StartSizing()
{
	if (!IsSized())
	{
		m_ptDockDrag = GetCurrentMessage()->pt;
		m_bDockSize = TRUE;
	}
}

BOOL CToolWnd::IsSized() CONST
{
	return m_bDockSize;
}

VOID CToolWnd::StopSizing()
{
	if (IsSized())
	{
		GetMainWnd()->ArrangeToolWindows(this, m_rDockDrag);
		m_bDockSize = FALSE;
	}
}

VOID CToolWnd::AdjustDragFrame(CONST POINT &pt, LPRECT lpRect)
{
	CRect  rArea[2];

	if (IsDragged())
	{
		for (rArea[0] = GetParent()->CalcClientRect(TRUE), rArea[1] = GetParent()->CalcClientRect(FALSE), GetParent()->ClientToScreen(rArea[0]), GetParent()->ClientToScreen(rArea[1]); ((GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && rArea[0].left < lpRect->left && rArea[0].right > lpRect->right; )
		{
			SetRect(lpRect, pt.x - m_sizeDefault[TOOLWINDOW_SIZE_FLOATING].cx / 2, lpRect->top, pt.x + m_sizeDefault[TOOLWINDOW_SIZE_FLOATING].cx / 2, lpRect->top + m_sizeDefault[TOOLWINDOW_SIZE_FLOATING].cy);
			SetDraggedDockState();
			break;
		}
		if (((GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && rArea[0].top < lpRect->top  &&  rArea[0].bottom > lpRect->bottom)
		{
			SetRect(lpRect, pt.x - m_sizeDefault[TOOLWINDOW_SIZE_FLOATING].cx / 2, pt.y - TOOLWINDOW_CAPTION_SIZE / 2, pt.x + m_sizeDefault[TOOLWINDOW_SIZE_FLOATING].cx / 2, pt.y - TOOLWINDOW_CAPTION_SIZE / 2 + m_sizeDefault[TOOLWINDOW_SIZE_FLOATING].cy);
			SetDraggedDockState();
		}
		if (((GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_LEFT) && ((lpRect->bottom - lpRect->top == rArea[0].Height() && rArea[0].left - lpRect->left > (lpRect->right - lpRect->left) / 2 && rArea[1].left - lpRect->left <= (lpRect->right - lpRect->left) / 2 && GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect)) || (lpRect->bottom - lpRect->top != rArea[0].Height() && (rArea[0].left - lpRect->left <= (lpRect->right - lpRect->left) / 2 || rArea[1].left - lpRect->left > (lpRect->right - lpRect->left) / 2 || !GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect))))) || (!GetDraggedDockState() && lpRect->left < rArea[0].left  &&  pt.x - TOOLWINDOW_SIZE_WIDTH + GetSystemMetrics(SM_CXFRAME) < rArea[0].left))
		{
			SetRect(lpRect, (GetDraggedDockState()) ? max(lpRect->left, -TOOLWINDOW_SIZE_WIDTH + GetSystemMetrics(SM_CXFRAME)) : ((lpRect->left + TOOLWINDOW_SIZE_WIDTH - GetSystemMetrics(SM_CXFRAME) < pt.x) ? (pt.x - TOOLWINDOW_SIZE_WIDTH + GetSystemMetrics(SM_CXFRAME)) : lpRect->left), (lpRect->bottom - lpRect->top == rArea[0].Height()) ? max(lpRect->top, pt.y - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME)) : lpRect->top, (GetDraggedDockState()) ? (max(lpRect->left, -TOOLWINDOW_SIZE_WIDTH + GetSystemMetrics(SM_CXFRAME)) + TOOLWINDOW_SIZE_WIDTH) : ((lpRect->left + TOOLWINDOW_SIZE_WIDTH - GetSystemMetrics(SM_CXFRAME) < pt.x) ? (pt.x + GetSystemMetrics(SM_CXFRAME)) : (lpRect->left + TOOLWINDOW_SIZE_WIDTH)), (lpRect->bottom - lpRect->top == rArea[0].Height()) ? (max(lpRect->top, pt.y - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME)) + TOOLWINDOW_SIZE_HEIGHT) : (lpRect->top + rArea[0].Height()));
			OffsetRect(lpRect, -max(lpRect->left - rArea[0].left, 0), 0);
			SetDraggedDockState(TOOLWINDOW_DOCKSTATE_LEFT);
		}
		if (((GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_TOP) && ((lpRect->right - lpRect->left == rArea[1].Width() && rArea[0].top - lpRect->top > (lpRect->bottom - lpRect->top) / 2 && rArea[1].top - lpRect->top <= (lpRect->bottom - lpRect->top) / 2 && GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect)) || (lpRect->right - lpRect->left != rArea[1].Width() && (rArea[0].top - lpRect->top <= (lpRect->bottom - lpRect->top) / 2 || rArea[1].top - lpRect->top > (lpRect->bottom - lpRect->top) / 2 || !GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect))))) || (!GetDraggedDockState() && lpRect->top < rArea[0].top  &&  pt.y - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME) < rArea[0].top))
		{
			SetRect(lpRect, (lpRect->right - lpRect->left == rArea[1].Width()) ? (pt.x - TOOLWINDOW_SIZE_WIDTH / 2) : rArea[1].left, (GetDraggedDockState()) ? max(lpRect->top, -TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME)) : ((lpRect->top + TOOLWINDOW_SIZE_HEIGHT - GetSystemMetrics(SM_CYFRAME) < pt.y) ? (pt.y - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME)) : lpRect->top), (lpRect->right - lpRect->left == rArea[1].Width()) ? (pt.x + TOOLWINDOW_SIZE_WIDTH / 2) : rArea[1].right, (GetDraggedDockState()) ? (max(lpRect->top, -TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME)) + TOOLWINDOW_SIZE_HEIGHT) : ((lpRect->top + TOOLWINDOW_SIZE_HEIGHT - GetSystemMetrics(SM_CYFRAME) < pt.y) ? (pt.y + GetSystemMetrics(SM_CYFRAME)) : (lpRect->top + TOOLWINDOW_SIZE_HEIGHT)));
			OffsetRect(lpRect, 0, -max(lpRect->top - rArea[0].top, 0));
			SetDraggedDockState(TOOLWINDOW_DOCKSTATE_TOP);
		}
		if (((GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) && ((lpRect->bottom - lpRect->top == rArea[0].Height() && lpRect->right - rArea[0].right > (lpRect->right - lpRect->left) / 2 && lpRect->right - rArea[1].right <= (lpRect->right - lpRect->left) / 2 && GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect)) || (lpRect->bottom - lpRect->top != rArea[0].Height() && (lpRect->right - rArea[0].right <= (lpRect->right - lpRect->left) / 2 || lpRect->right - rArea[1].right > (lpRect->right - lpRect->left) / 2 || !GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect))))) || (!GetDraggedDockState() && lpRect->right > rArea[0].right  &&  pt.x + TOOLWINDOW_SIZE_WIDTH - GetSystemMetrics(SM_CXFRAME) > rArea[0].right))
		{
			SetRect(lpRect, (GetDraggedDockState()) ? min(lpRect->left, rArea[1].right - GetSystemMetrics(SM_CXFRAME)) : ((lpRect->right - TOOLWINDOW_SIZE_WIDTH + GetSystemMetrics(SM_CXFRAME) > pt.x) ? (pt.x - GetSystemMetrics(SM_CXFRAME)) : (lpRect->right - TOOLWINDOW_SIZE_WIDTH)), (lpRect->bottom - lpRect->top == rArea[0].Height()) ? max(lpRect->top, pt.y - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME)) : lpRect->top, (GetDraggedDockState()) ? (min(lpRect->left, rArea[1].right - GetSystemMetrics(SM_CXFRAME)) + TOOLWINDOW_SIZE_WIDTH) : ((lpRect->right - TOOLWINDOW_SIZE_WIDTH + GetSystemMetrics(SM_CXFRAME) > pt.x) ? (pt.x + TOOLWINDOW_SIZE_WIDTH - GetSystemMetrics(SM_CXFRAME)) : lpRect->right), (lpRect->bottom - lpRect->top == rArea[0].Height()) ? (max(lpRect->top, pt.y - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME)) + TOOLWINDOW_SIZE_HEIGHT) : (lpRect->top + rArea[0].Height()));
			OffsetRect(lpRect, max(rArea[0].right - lpRect->right, 0), 0);
			SetDraggedDockState(TOOLWINDOW_DOCKSTATE_RIGHT);
		}
		if (((GetDraggedDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) && ((lpRect->right - lpRect->left == rArea[1].Width() && lpRect->bottom - rArea[0].bottom > (lpRect->bottom - lpRect->top) / 2 && lpRect->bottom - rArea[1].bottom <= (lpRect->bottom - lpRect->top) / 2 && GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect)) || (lpRect->right - lpRect->left != rArea[1].Width() && (lpRect->bottom - rArea[0].bottom <= (lpRect->bottom - lpRect->top) / 2 || lpRect->bottom - rArea[1].bottom > (lpRect->bottom - lpRect->top) / 2 || !GetParent()->EnumToolWindows(this, GetDraggedDockState(), lpRect))))) || (!GetDraggedDockState() && lpRect->bottom > rArea[0].bottom  &&  pt.y + TOOLWINDOW_SIZE_HEIGHT - GetSystemMetrics(SM_CYFRAME) > rArea[0].bottom))
		{
			SetRect(lpRect, (lpRect->right - lpRect->left == rArea[1].Width()) ? (pt.x - TOOLWINDOW_SIZE_WIDTH / 2) : rArea[1].left, (GetDraggedDockState()) ? min(lpRect->top, rArea[1].bottom - GetSystemMetrics(SM_CYFRAME)) : ((lpRect->bottom - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME) > pt.y) ? (pt.y - GetSystemMetrics(SM_CYFRAME)) : (lpRect->bottom - TOOLWINDOW_SIZE_HEIGHT)), (lpRect->right - lpRect->left == rArea[1].Width()) ? (pt.x + TOOLWINDOW_SIZE_WIDTH / 2) : rArea[1].right, (GetDraggedDockState()) ? (min(lpRect->top, rArea[1].bottom - GetSystemMetrics(SM_CYFRAME)) + TOOLWINDOW_SIZE_HEIGHT) : ((lpRect->bottom - TOOLWINDOW_SIZE_HEIGHT + GetSystemMetrics(SM_CYFRAME) > pt.y) ? (pt.y + TOOLWINDOW_SIZE_HEIGHT - GetSystemMetrics(SM_CYFRAME)) : lpRect->bottom));
			OffsetRect(lpRect, 0, max(rArea[0].bottom - lpRect->bottom, 0));
			SetDraggedDockState(TOOLWINDOW_DOCKSTATE_BOTTOM);
		}
		m_rDockDrag.SetRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}
}

VOID CToolWnd::AdjustSizeBar(CONST POINT &pt, LPRECT lpRect)
{
	CRect  rArea;
	CRect  rToolWnd;

	if (IsSized())
	{
		GetWindowRect(rToolWnd);
		GetParent()->ClientToScreen((rArea = GetParent()->CalcClientRect()));
		rArea.SetRect((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) ? rToolWnd.left : rArea.left, (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) ? rToolWnd.top : rArea.top, (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) ? rToolWnd.right : rArea.right, (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? rToolWnd.bottom : rArea.bottom);
		SetRect(lpRect, (lpRect->right - lpRect->left < lpRect->bottom - lpRect->top) ? min(max(lpRect->left + pt.x - m_ptDockDrag.x, rArea.left + CalcExtent().cx), rArea.right - CalcExtent().cx - lpRect->right + lpRect->left) : lpRect->left, (lpRect->right - lpRect->left > lpRect->bottom - lpRect->top) ? min(max(lpRect->top + pt.y - m_ptDockDrag.y, rArea.top + CalcExtent().cy), rArea.bottom - CalcExtent().cy - lpRect->bottom + lpRect->top) : lpRect->top, (lpRect->right - lpRect->left < lpRect->bottom - lpRect->top) ? max(min(lpRect->right + pt.x - m_ptDockDrag.x, rArea.right - CalcExtent().cx), rArea.left + CalcExtent().cx + lpRect->right - lpRect->left) : lpRect->right, (lpRect->right - lpRect->left > lpRect->bottom - lpRect->top) ? max(min(lpRect->bottom + pt.y - m_ptDockDrag.y, rArea.bottom - CalcExtent().cy), rArea.top + CalcExtent().cy + lpRect->bottom - lpRect->top) : lpRect->bottom);
		m_rDockDrag.SetRect((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT) && lpRect->right - lpRect->left < lpRect->bottom - lpRect->top) ? lpRect->left : rToolWnd.left, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP) && lpRect->right - lpRect->left > lpRect->bottom - lpRect->top) ? lpRect->top : rToolWnd.top, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) && lpRect->right - lpRect->left < lpRect->bottom - lpRect->top) ? lpRect->right : rToolWnd.right, ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) && lpRect->right - lpRect->left > lpRect->bottom - lpRect->top) ? lpRect->bottom : rToolWnd.bottom);
		m_ptDockDrag.x = (lpRect->right - lpRect->left < lpRect->bottom - lpRect->top) ? min(max(pt.x, lpRect->left), lpRect->right) : m_ptDockDrag.x;
		m_ptDockDrag.y = (lpRect->right - lpRect->left > lpRect->bottom - lpRect->top) ? min(max(pt.y, lpRect->top), lpRect->bottom) : m_ptDockDrag.y;
	}
}

BOOL CToolWnd::CalcDragCaption(LPRECT lpRect) CONST
{
	CRect  rCaption;
	CRect  rToolWnd;
	CRect  rButtonCtrl;

	for (GetWindowRect(rToolWnd), ScreenToClient(rToolWnd); (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT); )
	{
		rCaption.SetRect((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (rToolWnd.left + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE) : (rToolWnd.left + TOOLWINDOW_BORDER_SIZE), (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP)) ? (rToolWnd.top + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE) : (rToolWnd.top + TOOLWINDOW_BORDER_SIZE), (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.right - TOOLWINDOW_BORDER_SIZE - TOOLWINDOW_FRAME_SIZE) : (rToolWnd.right - TOOLWINDOW_BORDER_SIZE), (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP)) ? (rToolWnd.top + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_CAPTION_SIZE) : (rToolWnd.top + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_CAPTION_SIZE));
		if (IsWindow(m_wndExpandButtonCtrl.GetSafeHwnd()))
		{
			m_wndExpandButtonCtrl.GetWindowRect(rButtonCtrl);
			ScreenToClient(rButtonCtrl);
			rCaption.right = min(rButtonCtrl.left - TOOLWINDOW_BORDER_SIZE - 1, rCaption.right);
		}
		if (IsWindow(m_wndHideButtonCtrl.GetSafeHwnd()))
		{
			m_wndHideButtonCtrl.GetWindowRect(rButtonCtrl);
			ScreenToClient(rButtonCtrl);
			rCaption.right = min(rButtonCtrl.left - TOOLWINDOW_BORDER_SIZE - 1, rCaption.right);
		}
		SetRect(lpRect, rCaption.left, rCaption.top, rCaption.right, rCaption.bottom);
		return TRUE;
	}
	if ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM))
	{
		rCaption.SetRect((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (rToolWnd.left + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE) : (rToolWnd.left + TOOLWINDOW_BORDER_SIZE), (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP)) ? (rToolWnd.top + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE) : (rToolWnd.top + TOOLWINDOW_BORDER_SIZE), (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (rToolWnd.left + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_CAPTION_SIZE) : (rToolWnd.left + TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_CAPTION_SIZE), (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom - TOOLWINDOW_BORDER_SIZE - TOOLWINDOW_FRAME_SIZE) : (rToolWnd.bottom - TOOLWINDOW_BORDER_SIZE));
		if (IsWindow(m_wndExpandButtonCtrl.GetSafeHwnd()))
		{
			m_wndExpandButtonCtrl.GetWindowRect(rButtonCtrl);
			ScreenToClient(rButtonCtrl);
			rCaption.top = max(rButtonCtrl.bottom + TOOLWINDOW_BORDER_SIZE + 1, rCaption.top);
		}
		if (IsWindow(m_wndHideButtonCtrl.GetSafeHwnd()))
		{
			m_wndHideButtonCtrl.GetWindowRect(rButtonCtrl);
			ScreenToClient(rButtonCtrl);
			rCaption.top = max(rButtonCtrl.bottom + TOOLWINDOW_BORDER_SIZE + 1, rCaption.top);
		}
		SetRect(lpRect, rCaption.left, rCaption.top, rCaption.right, rCaption.bottom);
		return TRUE;
	}
	return FALSE;
}

BOOL CToolWnd::CalcSizeBorder(UINT nSide, LPRECT lpRect) CONST
{
	CRect  rArea;
	CRect  rToolWnd;

	GetWindowRect(rToolWnd);
	GetParent()->ScreenToClient(rToolWnd);
	if (nSide & TOOLWINDOW_DOCKSTATE_LEFT)
	{
		if (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)
		{
			rArea = GetParent()->CalcClientRect(TRUE);
			SetRect(lpRect, rToolWnd.left, rArea.top, rToolWnd.left + TOOLWINDOW_FRAME_SIZE, rArea.bottom);
			return TRUE;
		}
		SetRect(lpRect, rToolWnd.left, rToolWnd.top, rToolWnd.left + TOOLWINDOW_FRAME_SIZE, rToolWnd.bottom);
		return TRUE;
	}
	if (nSide & TOOLWINDOW_DOCKSTATE_TOP)
	{
		if (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)
		{
			rArea = GetParent()->CalcClientRect(FALSE);
			SetRect(lpRect, rArea.left, rToolWnd.top, rArea.right, rToolWnd.top + TOOLWINDOW_FRAME_SIZE);
			return TRUE;
		}
		SetRect(lpRect, rToolWnd.left, rToolWnd.top, rToolWnd.right, rToolWnd.top + TOOLWINDOW_FRAME_SIZE);
		return TRUE;
	}
	if (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)
	{
		rArea = GetParent()->CalcClientRect(TRUE);
		SetRect(lpRect, rToolWnd.right - TOOLWINDOW_FRAME_SIZE + 1, rArea.top, rToolWnd.right + 1, rArea.bottom);
		return TRUE;
	}
	if (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)
	{
		rArea = GetParent()->CalcClientRect(FALSE);
		SetRect(lpRect, rArea.left, rToolWnd.bottom - TOOLWINDOW_FRAME_SIZE + 1, rArea.right, rToolWnd.bottom + 1);
		return TRUE;
	}
	return FALSE;
}

BOOL CToolWnd::IsPointOnDragCaption(CONST POINT &pt) CONST
{
	CRect  rCaption;

	return((CalcDragCaption(rCaption)) ? rCaption.PtInRect(pt) : FALSE);
}

UINT CToolWnd::IsPointOnSizeBorder(CONST POINT &pt) CONST
{
	CRect  rBorder;
	CRect  rToolWnd;

	for (GetWindowRect(rToolWnd), ScreenToClient(rToolWnd); GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT; )
	{
		rBorder.SetRect(rToolWnd.right - TOOLWINDOW_FRAME_SIZE, rToolWnd.top, rToolWnd.right, rToolWnd.bottom);
		if (rBorder.PtInRect(pt)) return TOOLWINDOW_DOCKSTATE_RIGHT;
		break;
	}
	if (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP)
	{
		rBorder.SetRect(rToolWnd.left, rToolWnd.bottom - TOOLWINDOW_FRAME_SIZE, rToolWnd.right, rToolWnd.bottom);
		if (rBorder.PtInRect(pt)) return TOOLWINDOW_DOCKSTATE_BOTTOM;
	}
	if ((GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) || (((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)))
	{
		rBorder.SetRect(rToolWnd.left, (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rToolWnd.top + TOOLWINDOW_FRAME_SIZE) : rToolWnd.top, rToolWnd.left + TOOLWINDOW_FRAME_SIZE, (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) ? (rToolWnd.bottom - TOOLWINDOW_FRAME_SIZE) : rToolWnd.bottom);
		if (rBorder.PtInRect(pt)) return TOOLWINDOW_DOCKSTATE_LEFT;
	}
	if ((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) || (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP)))
	{
		rBorder.SetRect((GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) ? (rToolWnd.left + TOOLWINDOW_FRAME_SIZE) : rToolWnd.left, rToolWnd.top, (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) ? (rToolWnd.right - TOOLWINDOW_FRAME_SIZE) : rToolWnd.right, rToolWnd.top + TOOLWINDOW_FRAME_SIZE);
		if (rBorder.PtInRect(pt)) return TOOLWINDOW_DOCKSTATE_TOP;
	}
	return 0;
}

INT CToolWnd::CalcTrackExtent(UINT nSide) CONST
{
	CRect  rButtonCtrl[2];

	rButtonCtrl[0].SetRectEmpty();
	rButtonCtrl[1].SetRectEmpty();
	if (IsWindow(m_wndHideButtonCtrl.GetSafeHwnd())) m_wndHideButtonCtrl.GetWindowRect(rButtonCtrl[0]);
	if (IsWindow(m_wndExpandButtonCtrl.GetSafeHwnd())) m_wndExpandButtonCtrl.GetWindowRect(rButtonCtrl[1]);
	return(((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (TOOLWINDOW_FRAME_SIZE + 7 * TOOLWINDOW_BORDER_SIZE + rButtonCtrl[0].Height() + rButtonCtrl[1].Height()) : CalcExtent().cx) : (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (TOOLWINDOW_FRAME_SIZE + 6 * TOOLWINDOW_BORDER_SIZE + rButtonCtrl[0].Width() + rButtonCtrl[1].Width()) : CalcExtent().cy) : 0));
}

CSize CToolWnd::CalcExtent() CONST
{
	return(((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? ((GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT) ? CSize(TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_CAPTION_SIZE + GetSystemMetrics(SM_CXEDGE), CalcTrackExtent(GetDockState())) : CSize(TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_CAPTION_SIZE + GetSystemMetrics(SM_CXEDGE), CalcTrackExtent(GetDockState()))) : (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP) ? CSize(CalcTrackExtent(GetDockState()), TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_CAPTION_SIZE + 2 * GetSystemMetrics(SM_CYEDGE)) : CSize(CalcTrackExtent(GetDockState()), TOOLWINDOW_BORDER_SIZE + TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_CAPTION_SIZE + GetSystemMetrics(SM_CYEDGE))) : CSize(0, 0)));
}

VOID CToolWnd::SetData(CONST CByteArray &nData)
{
	SIZE  sizeDefault[TOOLWINDOW_SIZES];
	CByteArray  nInfo[TOOLWINDOW_SIZES];

	nInfo[TOOLWINDOW_SIZE_DOCKED].Copy(nData);
	nInfo[TOOLWINDOW_SIZE_MULTIDOCKED].Copy(nData);
	nInfo[TOOLWINDOW_SIZE_FLOATING].Copy(nData);
	if (nData.GetSize() >= (INT)(sizeof(sizeDefault[TOOLWINDOW_SIZE_DOCKED]) + sizeof(sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED]) + sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING])))
	{
		nInfo[TOOLWINDOW_SIZE_DOCKED].RemoveAt(0, nData.GetSize() - sizeof(sizeDefault[TOOLWINDOW_SIZE_DOCKED]) - sizeof(sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED]) - sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING]));
		nInfo[TOOLWINDOW_SIZE_MULTIDOCKED].RemoveAt(0, nData.GetSize() - sizeof(sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED]) - sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING]));
		nInfo[TOOLWINDOW_SIZE_FLOATING].RemoveAt(0, nData.GetSize() - sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING]));
		CopyMemory(&sizeDefault[TOOLWINDOW_SIZE_DOCKED], nInfo[TOOLWINDOW_SIZE_DOCKED].GetData(), sizeof(sizeDefault[TOOLWINDOW_SIZE_DOCKED]));
		CopyMemory(&sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED], nInfo[TOOLWINDOW_SIZE_MULTIDOCKED].GetData(), sizeof(sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED]));
		CopyMemory(&sizeDefault[TOOLWINDOW_SIZE_FLOATING], nInfo[TOOLWINDOW_SIZE_FLOATING].GetData(), sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING]));
		m_sizeDefault[TOOLWINDOW_SIZE_DOCKED] = sizeDefault[TOOLWINDOW_SIZE_DOCKED];
		m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED] = sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED];
		m_sizeDefault[TOOLWINDOW_SIZE_FLOATING] = sizeDefault[TOOLWINDOW_SIZE_FLOATING];
	}
}

VOID CToolWnd::GetData(CByteArray &nData) CONST
{
	SIZE  sizeDefault[TOOLWINDOW_SIZES];
	CByteArray  nInfo[TOOLWINDOW_SIZES];

	sizeDefault[TOOLWINDOW_SIZE_DOCKED] = m_sizeDefault[TOOLWINDOW_SIZE_DOCKED];
	sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED] = m_sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED];
	sizeDefault[TOOLWINDOW_SIZE_FLOATING] = m_sizeDefault[TOOLWINDOW_SIZE_FLOATING];
	nInfo[TOOLWINDOW_SIZE_DOCKED].SetSize(sizeof(sizeDefault[TOOLWINDOW_SIZE_DOCKED]));
	nInfo[TOOLWINDOW_SIZE_MULTIDOCKED].SetSize(sizeof(sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED]));
	nInfo[TOOLWINDOW_SIZE_FLOATING].SetSize(sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING]));
	if (nInfo[TOOLWINDOW_SIZE_DOCKED].GetSize() == sizeof(sizeDefault[TOOLWINDOW_SIZE_DOCKED]) && nInfo[TOOLWINDOW_SIZE_MULTIDOCKED].GetSize() == sizeof(sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED]) && nInfo[TOOLWINDOW_SIZE_FLOATING].GetSize() == sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING]))
	{
		CopyMemory(nInfo[TOOLWINDOW_SIZE_DOCKED].GetData(), &sizeDefault[TOOLWINDOW_SIZE_DOCKED], sizeof(sizeDefault[TOOLWINDOW_SIZE_DOCKED]));
		CopyMemory(nInfo[TOOLWINDOW_SIZE_MULTIDOCKED].GetData(), &sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED], sizeof(sizeDefault[TOOLWINDOW_SIZE_MULTIDOCKED]));
		CopyMemory(nInfo[TOOLWINDOW_SIZE_FLOATING].GetData(), &sizeDefault[TOOLWINDOW_SIZE_FLOATING], sizeof(sizeDefault[TOOLWINDOW_SIZE_FLOATING]));
		nData.Append(nInfo[TOOLWINDOW_SIZE_DOCKED]);
		nData.Append(nInfo[TOOLWINDOW_SIZE_MULTIDOCKED]);
		nData.Append(nInfo[TOOLWINDOW_SIZE_FLOATING]);
	}
}

CMainWnd *CToolWnd::GetParent() CONST
{
	return((CMainWnd *)m_pParentWnd);
}

VOID CToolWnd::CalcClientRect(LPRECT pRect) CONST
{
	CRect  rToolWnd;

	if (IsDocked())
	{
		GetClientRect(rToolWnd);
		rToolWnd.DeflateRect(TOOLWINDOW_BORDER_SIZE, TOOLWINDOW_BORDER_SIZE);
		rToolWnd.DeflateRect(0, (GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP) ? GetSystemMetrics(SM_CYEDGE) : 0, 0, (!(GetDockState() & TOOLWINDOW_DOCKSTATE_TOP)) ? ((GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? GetSystemMetrics(SM_CYEDGE) : 1) : 0);
		if (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) rToolWnd.DeflateRect((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? GetSystemMetrics(SM_CXEDGE) : 0, 0, TOOLWINDOW_FRAME_SIZE, 0);
		if (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) rToolWnd.DeflateRect(0, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP)) ? GetSystemMetrics(SM_CYEDGE) : 0, 0, TOOLWINDOW_FRAME_SIZE);
		if ((GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) rToolWnd.DeflateRect((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? TOOLWINDOW_FRAME_SIZE : 0, 0, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? GetSystemMetrics(SM_CXEDGE) : 0, 0);
		if ((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) || (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) rToolWnd.DeflateRect(0, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP)) ? TOOLWINDOW_FRAME_SIZE : 0, 0, 0);
		if ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) rToolWnd.DeflateRect(TOOLWINDOW_BORDER_SIZE, TOOLWINDOW_CAPTION_SIZE, TOOLWINDOW_BORDER_SIZE, 0);
		if ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) rToolWnd.DeflateRect(TOOLWINDOW_CAPTION_SIZE, 0, TOOLWINDOW_BORDER_SIZE, 0);
		SetRect(pRect, rToolWnd.left, rToolWnd.top, rToolWnd.right, rToolWnd.bottom);
		return;
	}
	GetClientRect(rToolWnd);
	SetRect(pRect, rToolWnd.left, rToolWnd.top, rToolWnd.right, rToolWnd.bottom);
	return;
}

VOID CToolWnd::SetButtonBitmaps(UINT nState)
{
	if (IsWindow(m_wndExpandButtonCtrl.GetSafeHwnd()))
	{
		SetDockState((nState) ? (GetDockState() | nState) : GetDockState(TRUE));
		m_wndExpandButtonCtrl.LoadBitmaps(((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!IsExpanded()) ? IDB_MINIEXPANDVERTICALBUTTON : IDB_MINICONTRACTVERTICALBUTTON) : ((!IsExpanded()) ? IDB_MINIEXPANDHORIZONTALBUTTON : IDB_MINICONTRACTHORIZONTALBUTTON), ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!IsExpanded()) ? IDB_MINIEXPANDVERTICALBUTTONPRESSED : IDB_MINICONTRACTVERTICALBUTTONPRESSED) : ((!IsExpanded()) ? IDB_MINIEXPANDHORIZONTALBUTTONPRESSED : IDB_MINICONTRACTHORIZONTALBUTTONPRESSED), 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!IsExpanded()) ? IDB_MINIEXPANDVERTICALBUTTONDISABLED : 0) : ((!IsExpanded()) ? IDB_MINIEXPANDHORIZONTALBUTTONDISABLED : 0));
	}
}

VOID CToolWnd::RepositionButtons()
{
	CRect  rToolWnd;
	CRect  rButtonCtrl;
	CPoint  ptButtonCtrl(0, 0);

	if (GetDockState())
	{
		SetButtonBitmaps();
		GetClientRect(rToolWnd);
		if (IsWindow(m_wndHideButtonCtrl.GetSafeHwnd()))
		{
			m_wndHideButtonCtrl.SizeToContent();
			m_wndHideButtonCtrl.GetWindowRect(rButtonCtrl);
			if (!ptButtonCtrl.x  &&  !ptButtonCtrl.y)
			{
				ptButtonCtrl.x = (((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM))) ? ((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_BORDER_SIZE + 1) : TOOLWINDOW_BORDER_SIZE) : (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.right - TOOLWINDOW_FRAME_SIZE - 2 * TOOLWINDOW_BORDER_SIZE - rButtonCtrl.Width()) : (rToolWnd.right - 2 * TOOLWINDOW_BORDER_SIZE - rButtonCtrl.Width())) : 0);
				ptButtonCtrl.y = (GetDockState()) ? ((GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP) ? (GetSystemMetrics(SM_CYEDGE) + TOOLWINDOW_BORDER_SIZE) : (TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_BORDER_SIZE)) : 0;
			}
			m_wndHideButtonCtrl.MoveWindow(ptButtonCtrl.x, ptButtonCtrl.y, (GetDockState()) ? rButtonCtrl.Width() : 0, (GetDockState()) ? rButtonCtrl.Height() : 0);
			ptButtonCtrl.x = ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (ptButtonCtrl.x - rButtonCtrl.Width() - TOOLWINDOW_BORDER_SIZE + 1) : ptButtonCtrl.x;
			ptButtonCtrl.y = ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (ptButtonCtrl.y + rButtonCtrl.Height() + TOOLWINDOW_BORDER_SIZE - 1) : ptButtonCtrl.y;
		}
		if (IsWindow(m_wndExpandButtonCtrl.GetSafeHwnd()))
		{
			m_wndExpandButtonCtrl.SizeToContent();
			m_wndExpandButtonCtrl.GetWindowRect(rButtonCtrl);
			if (!ptButtonCtrl.x  &&  !ptButtonCtrl.y)
			{
				ptButtonCtrl.x = ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? ((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_BORDER_SIZE + 1) : TOOLWINDOW_BORDER_SIZE) : (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.right - TOOLWINDOW_FRAME_SIZE - 2 * TOOLWINDOW_BORDER_SIZE - rButtonCtrl.Width()) : (rToolWnd.right - 2 * TOOLWINDOW_BORDER_SIZE - rButtonCtrl.Width())) : 0);
				ptButtonCtrl.y = (GetDockState()) ? ((GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP) ? (GetSystemMetrics(SM_CYEDGE) + TOOLWINDOW_BORDER_SIZE) : (TOOLWINDOW_FRAME_SIZE + TOOLWINDOW_BORDER_SIZE)) : 0;
			}
			m_wndExpandButtonCtrl.EnableWindow(((((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT) || !(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT))) || (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP) || !(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)))) ? TRUE : FALSE);
			m_wndExpandButtonCtrl.MoveWindow(ptButtonCtrl.x, ptButtonCtrl.y, (GetDockState()) ? rButtonCtrl.Width() : 0, (GetDockState()) ? rButtonCtrl.Height() : 0);
		}
	}
}

void CToolWnd::RecalcLayout(BOOL bNotify)
{
	RepositionButtons();
	CMiniFrameWnd::RecalcLayout(bNotify);
}

BEGIN_MESSAGE_MAP(CToolWnd, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CToolWnd)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOVE()
	ON_WM_MOVING()
	ON_WM_SETCURSOR()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_COMMAND(TOOLWINDOW_EXPANDBUTTON_ID, OnExpand)
	ON_COMMAND(TOOLWINDOW_HIDEBUTTON_ID, OnHide)
	ON_MESSAGE(WM_ENTERSIZEMOVE, OnEnterSizeMove)
	ON_MESSAGE(WM_EXITSIZEMOVE, OnExitSizeMove)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolWnd message handlers

int CToolWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (((lpCreateStruct->style & TWS_NOEXPANDBUTTON) || (m_wndExpandButtonCtrl.Create((LPCTSTR)NULL, BS_PUSHBUTTON | BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, TOOLWINDOW_EXPANDBUTTON_ID) && m_wndExpandButtonCtrl.LoadBitmaps(((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!IsExpanded()) ? IDB_MINIEXPANDVERTICALBUTTON : IDB_MINICONTRACTVERTICALBUTTON) : ((!IsExpanded()) ? IDB_MINIEXPANDHORIZONTALBUTTON : IDB_MINICONTRACTHORIZONTALBUTTON), ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!IsExpanded()) ? IDB_MINIEXPANDVERTICALBUTTONPRESSED : IDB_MINICONTRACTVERTICALBUTTONPRESSED) : ((!IsExpanded()) ? IDB_MINIEXPANDHORIZONTALBUTTONPRESSED : IDB_MINICONTRACTHORIZONTALBUTTONPRESSED), 0, ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((!IsExpanded()) ? IDB_MINIEXPANDVERTICALBUTTONDISABLED : 0) : ((!IsExpanded()) ? IDB_MINIEXPANDHORIZONTALBUTTONDISABLED : 0)))) && ((lpCreateStruct->style & TWS_NOHIDEBUTTON) || (m_wndHideButtonCtrl.Create((LPCTSTR)NULL, BS_PUSHBUTTON | BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, TOOLWINDOW_HIDEBUTTON_ID) && m_wndHideButtonCtrl.LoadBitmaps(IDB_MINICLOSEBUTTON, IDB_MINICLOSEBUTTONPRESSED))) && m_wndSizeCtrl.Create(this))
		{
			GetParent()->RegisterToolWindow(this);
			EnableToolTips(TRUE);
			RecalcLayout();
			return 0;
		}
	}
	return -1;
}

void CToolWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		Hide();
		return;
	}
	CMiniFrameWnd::OnSysCommand(nID, lParam);
}

void CToolWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (nStatus == (UINT)-1)
	{
		ShowWindow(((m_bVisible = bShow)) ? SW_SHOW : SW_HIDE);
		GetParent()->ArrangeToolWindows();
		return;
	}
	SetDockState(((m_bVisible = bShow)) ? (GetDockState(TRUE) & ~TOOLWINDOW_DOCKSTATE_HIDDEN) : (GetDockState(TRUE) | TOOLWINDOW_DOCKSTATE_HIDDEN));
	CMiniFrameWnd::OnShowWindow(bShow, nStatus);
}

void CToolWnd::OnWindowPosChanging(WINDOWPOS *lpwndpos)
{
	if (!IsDocked())
	{
		if (IsVisible())
		{
			if (lpwndpos->cx > 0 || lpwndpos->cy > 0)
			{
				if (GetParent()->RepositionToolWindow(this, m_rDockDrag)) return;
				lpwndpos->flags = (GetDraggedDockState()) ? (lpwndpos->flags | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE) : (lpwndpos->flags | SWP_NOACTIVATE);
			}
		}
	}
	lpwndpos->flags |= (IsDocked() && IsDragged()) ? (SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE) : 0;
	CMiniFrameWnd::OnWindowPosChanging(lpwndpos);
}

void CToolWnd::OnSize(UINT nType, int cx, int cy)
{
	INT  nTool;
	INT  nTools;
	CRect  rToolDrag;
	CRect  rToolWnd[2];
	CToolWnd  *pToolWnd;
	CPtrArray  pToolWnds;

	for (GetWindowRect(rToolWnd[0]), SetDefaultSize(CSize(rToolWnd[0].Width(), rToolWnd[0].Height())); IsWindow(m_wndExpandButtonCtrl.GetSafeHwnd()); )
	{
		for (nTool = 0, nTools = GetParent()->EnumToolPane(GetDockState(), GetParent()->FindToolPane(GetDockState(), rToolWnd[0]), pToolWnds); nTool < nTools && nTools > 1; nTool++)
		{
			if ((pToolWnd = (CToolWnd *)pToolWnds.GetAt(nTool)) && pToolWnd != this)
			{
				pToolWnd->GetWindowRect(rToolWnd[1]);
				if ((((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && rToolWnd[1].Width() == pToolWnd->CalcExtent().cx) || (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && rToolWnd[1].Height() == pToolWnd->CalcExtent().cy)) continue;
				break;
			}
		}
		SetDockState((!(GetDockState(TRUE) & TOOLWINDOW_DOCKSTATE_LOCKED) && ((((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && rToolWnd[0].Width() != CalcExtent().cx) || (((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && rToolWnd[0].Height() != CalcExtent().cy))) ? (GetDockState(TRUE) & ~TOOLWINDOW_DOCKSTATE_SHRINKED) : GetDockState(TRUE));
		SetDockState((!(GetDockState(TRUE) & TOOLWINDOW_DOCKSTATE_LOCKED) && nTool < nTools) ? (GetDockState(TRUE) & ~TOOLWINDOW_DOCKSTATE_EXPANDED) : GetDockState(TRUE));
		break;
	}
	CMiniFrameWnd::OnSize(nType, cx, cy);
}

BOOL CToolWnd::OnEraseBkgnd(CDC *pDC)
{
	INT  nSize;
	CPen  cPen[4];
	CPen  *pOldPen;
	CRect  rToolWnd;
	CRect  rButtonCtrl;
	CBrush  cBorderBrush;
	CPoint  ptCaptionGrip;

	if (IsDocked())
	{
		RepositionButtons();
		GetClientRect(rToolWnd);
		if (cBorderBrush.CreateSolidBrush(GetSysColor(COLOR_3DFACE)))
		{
			if (cPen[0].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DHILIGHT)) && cPen[1].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DSHADOW)) && cPen[2].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DFACE)) && cPen[3].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)))
			{
				if ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM))
				{
					if (GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP)
					{
						if ((pOldPen = pDC->SelectObject(&cPen[1])))
						{
							pDC->MoveTo(rToolWnd.left, rToolWnd.top);
							pDC->LineTo(rToolWnd.right, rToolWnd.top);
							pDC->SelectObject(pOldPen);
							rToolWnd.top++;
						}
						if ((pOldPen = pDC->SelectObject(&cPen[0])))
						{
							pDC->MoveTo(rToolWnd.left, rToolWnd.top);
							pDC->LineTo(rToolWnd.right, rToolWnd.top);
							pDC->SelectObject(pOldPen);
							rToolWnd.top++;
						}
					}
					if (!(GetDockState() & TOOLWINDOW_DOCKSTATE_TOP))
					{
						if ((pOldPen = pDC->SelectObject(&cPen[0])))
						{
							pDC->MoveTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.left + TOOLWINDOW_FRAME_SIZE) : rToolWnd.left, rToolWnd.bottom - 1);
							pDC->LineTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.right - TOOLWINDOW_FRAME_SIZE + 1) : rToolWnd.right, rToolWnd.bottom - 1);
							pDC->SelectObject(pOldPen);
							rToolWnd.bottom--;
						}
						if (GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)
						{
							if ((pOldPen = pDC->SelectObject(&cPen[1])))
							{
								pDC->MoveTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.left + TOOLWINDOW_FRAME_SIZE) : rToolWnd.left, rToolWnd.bottom - 1);
								pDC->LineTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.right - TOOLWINDOW_FRAME_SIZE + 1) : rToolWnd.right, rToolWnd.bottom - 1);
								pDC->SelectObject(pOldPen);
								rToolWnd.bottom--;
							}
						}
					}
					if (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT)
					{
						if (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT))
						{
							if ((pOldPen = pDC->SelectObject(&cPen[1])))
							{
								pDC->MoveTo(rToolWnd.left, rToolWnd.top);
								pDC->LineTo(rToolWnd.left, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
								pDC->SelectObject(pOldPen);
								rToolWnd.left++;
							}
							if ((pOldPen = pDC->SelectObject(&cPen[3])))
							{
								pDC->MoveTo(rToolWnd.left, rToolWnd.top);
								pDC->LineTo(rToolWnd.left, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
								pDC->SelectObject(pOldPen);
								rToolWnd.left++;
							}
						}
						if ((pOldPen = pDC->SelectObject(&cPen[2])))
						{
							for (nSize = 0; nSize < TOOLWINDOW_FRAME_SIZE - GetSystemMetrics(SM_CXEDGE); nSize++)
							{
								pDC->MoveTo(rToolWnd.right - 1, rToolWnd.top);
								pDC->LineTo(rToolWnd.right - 1, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
								rToolWnd.right--;
							}
							pDC->SelectObject(pOldPen);
						}
						if ((pOldPen = pDC->SelectObject(&cPen[0])))
						{
							pDC->MoveTo(rToolWnd.right - 1, rToolWnd.top);
							pDC->LineTo(rToolWnd.right - 1, (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
							pDC->SelectObject(pOldPen);
							rToolWnd.right--;
						}
						if ((pOldPen = pDC->SelectObject(&cPen[2])))
						{
							pDC->MoveTo(rToolWnd.right - 1, rToolWnd.top);
							pDC->LineTo(rToolWnd.right - 1, rToolWnd.bottom);
							pDC->SelectObject(pOldPen);
							rToolWnd.right--;
						}
					}
					if (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP)
					{
						if (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP))
						{
							if ((pOldPen = pDC->SelectObject(&cPen[3])))
							{
								pDC->MoveTo(rToolWnd.left, rToolWnd.top);
								pDC->LineTo(rToolWnd.right, rToolWnd.top);
								pDC->SelectObject(pOldPen);
								rToolWnd.top++;
							}
							if ((pOldPen = pDC->SelectObject(&cPen[1])))
							{
								pDC->MoveTo(rToolWnd.left, rToolWnd.top);
								pDC->LineTo(rToolWnd.right, rToolWnd.top);
								pDC->SelectObject(pOldPen);
								rToolWnd.top++;
							}
						}
						if ((pOldPen = pDC->SelectObject(&cPen[2])))
						{
							for (nSize = 0; nSize < TOOLWINDOW_FRAME_SIZE - GetSystemMetrics(SM_CYEDGE); nSize++)
							{
								pDC->MoveTo(rToolWnd.left, rToolWnd.bottom - 1);
								pDC->LineTo(rToolWnd.right, rToolWnd.bottom - 1);
								rToolWnd.bottom--;
							}
							pDC->SelectObject(pOldPen);
						}
						if ((pOldPen = pDC->SelectObject(&cPen[0])))
						{
							pDC->MoveTo(rToolWnd.left, rToolWnd.bottom - 1);
							pDC->LineTo(rToolWnd.right, rToolWnd.bottom - 1);
							pDC->SelectObject(pOldPen);
							rToolWnd.bottom--;
						}
						if ((pOldPen = pDC->SelectObject(&cPen[2])))
						{
							pDC->MoveTo(rToolWnd.left, rToolWnd.bottom - 1);
							pDC->LineTo(rToolWnd.right, rToolWnd.bottom - 1);
							pDC->SelectObject(pOldPen);
							rToolWnd.bottom--;
						}
					}
					if ((GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM))
					{
						if (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT))
						{
							if ((pOldPen = pDC->SelectObject(&cPen[0])))
							{
								pDC->MoveTo(rToolWnd.right - 1, (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rToolWnd.top + TOOLWINDOW_FRAME_SIZE) : rToolWnd.top);
								pDC->LineTo(rToolWnd.right - 1, (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
								pDC->SelectObject(pOldPen);
								rToolWnd.right--;
							}
							if ((pOldPen = pDC->SelectObject(&cPen[2])))
							{
								pDC->MoveTo(rToolWnd.right - 1, (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rToolWnd.top + TOOLWINDOW_FRAME_SIZE) : rToolWnd.top);
								pDC->LineTo(rToolWnd.right - 1, (GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
								pDC->SelectObject(pOldPen);
								rToolWnd.right--;
							}
						}
						if (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT))
						{
							if ((pOldPen = pDC->SelectObject(&cPen[2])))
							{
								for (nSize = 0; nSize < TOOLWINDOW_FRAME_SIZE - GetSystemMetrics(SM_CXEDGE); nSize++)
								{
									pDC->MoveTo(rToolWnd.left, (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rToolWnd.top + TOOLWINDOW_FRAME_SIZE) : rToolWnd.top);
									pDC->LineTo(rToolWnd.left, (!(GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
									rToolWnd.left++;
								}
								pDC->SelectObject(pOldPen);
							}
							if ((pOldPen = pDC->SelectObject(&cPen[1])))
							{
								pDC->MoveTo(rToolWnd.left, (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rToolWnd.top + TOOLWINDOW_FRAME_SIZE) : rToolWnd.top);
								pDC->LineTo(rToolWnd.left, (!(GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
								pDC->SelectObject(pOldPen);
								rToolWnd.left++;
							}
							if ((pOldPen = pDC->SelectObject(&cPen[3])))
							{
								pDC->MoveTo(rToolWnd.left, (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rToolWnd.top + TOOLWINDOW_FRAME_SIZE) : rToolWnd.top);
								pDC->LineTo(rToolWnd.left, (!(GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd.bottom + 1) : rToolWnd.bottom);
								pDC->SelectObject(pOldPen);
								rToolWnd.left++;
							}
						}
					}
					if ((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) || (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT))
					{
						if (!(GetDockSide() & TOOLWINDOW_DOCKSTATE_TOP))
						{
							if ((pOldPen = pDC->SelectObject(&cPen[2])))
							{
								for (nSize = 0; nSize < TOOLWINDOW_FRAME_SIZE - GetSystemMetrics(SM_CYEDGE); nSize++)
								{
									pDC->MoveTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (rToolWnd.left - TOOLWINDOW_FRAME_SIZE - 1) : rToolWnd.left, rToolWnd.top);
									pDC->LineTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.right + GetSystemMetrics(SM_CXEDGE)) : (rToolWnd.right + 1), rToolWnd.top);
									rToolWnd.top++;
								}
								pDC->SelectObject(pOldPen);
							}
							if ((pOldPen = pDC->SelectObject(&cPen[1])))
							{
								pDC->MoveTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (rToolWnd.left - TOOLWINDOW_FRAME_SIZE - 1) : rToolWnd.left, rToolWnd.top);
								pDC->LineTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.right + GetSystemMetrics(SM_CXEDGE)) : (rToolWnd.right + 1), rToolWnd.top);
								pDC->SelectObject(pOldPen);
								rToolWnd.top++;
							}
							if ((pOldPen = pDC->SelectObject(&cPen[3])))
							{
								pDC->MoveTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_LEFT)) ? (rToolWnd.left - TOOLWINDOW_FRAME_SIZE - 1) : rToolWnd.left, rToolWnd.top);
								pDC->LineTo(((GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) && !(GetDockSide() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd.right + GetSystemMetrics(SM_CXEDGE)) : (rToolWnd.right + 1), rToolWnd.top);
								pDC->SelectObject(pOldPen);
								rToolWnd.top++;
							}
						}
					}
					if (GetDockState())
					{
						if ((pOldPen = pDC->SelectObject(&cPen[2])))
						{
							for (nSize = 0; nSize < TOOLWINDOW_BORDER_SIZE; nSize++)
							{
								pDC->MoveTo(rToolWnd.left, rToolWnd.bottom - 1);
								pDC->LineTo(rToolWnd.right - 1, rToolWnd.bottom - 1);
								pDC->LineTo(rToolWnd.right - 1, rToolWnd.top);
								pDC->LineTo(rToolWnd.left, rToolWnd.top);
								pDC->LineTo(rToolWnd.left, rToolWnd.bottom - 1);
								rToolWnd.DeflateRect(1, 1, 1, 1);
							}
							pDC->SelectObject(pOldPen);
						}
						ptCaptionGrip.x = (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) ? (rToolWnd.right - TOOLWINDOW_FRAME_SIZE - TOOLWINDOW_BORDER_SIZE) : (rToolWnd.right - TOOLWINDOW_BORDER_SIZE);
						ptCaptionGrip.y = (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rToolWnd.top + TOOLWINDOW_FRAME_SIZE) : rToolWnd.top;
						if (IsWindow(m_wndExpandButtonCtrl.GetSafeHwnd()))
						{
							m_wndExpandButtonCtrl.GetWindowRect(rButtonCtrl);
							ScreenToClient(rButtonCtrl);
							ptCaptionGrip.x = min(rButtonCtrl.left - TOOLWINDOW_BORDER_SIZE, ptCaptionGrip.x);
							ptCaptionGrip.y = max(rButtonCtrl.bottom + TOOLWINDOW_BORDER_SIZE, ptCaptionGrip.y);
						}
						if (IsWindow(m_wndHideButtonCtrl.GetSafeHwnd()))
						{
							m_wndHideButtonCtrl.GetWindowRect(rButtonCtrl);
							ScreenToClient(rButtonCtrl);
							ptCaptionGrip.x = min(rButtonCtrl.left - TOOLWINDOW_BORDER_SIZE, ptCaptionGrip.x);
							ptCaptionGrip.y = max(rButtonCtrl.bottom + TOOLWINDOW_BORDER_SIZE, ptCaptionGrip.y);
						}
						if ((GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM))
						{
							pDC->FillRect(CRect(rToolWnd.left, rToolWnd.top, rToolWnd.left + TOOLWINDOW_CAPTION_SIZE, rToolWnd.bottom), &cBorderBrush);
							pDC->FillRect(CRect(rToolWnd.right - TOOLWINDOW_BORDER_SIZE, rToolWnd.top, rToolWnd.right, rToolWnd.bottom), &cBorderBrush);
							if ((pOldPen = pDC->SelectObject(&cPen[0])))
							{
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 2 * GetSystemMetrics(SM_CXEDGE) - 1, ptCaptionGrip.y);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 2 * GetSystemMetrics(SM_CXEDGE) - 1, rToolWnd.bottom - 1);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 2 * GetSystemMetrics(SM_CXEDGE) - 1, ptCaptionGrip.y);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - GetSystemMetrics(SM_CXEDGE) - 1, ptCaptionGrip.y);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 1, ptCaptionGrip.y);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 1, rToolWnd.bottom - 1);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 1, ptCaptionGrip.y);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 + GetSystemMetrics(SM_CXEDGE) - 1, ptCaptionGrip.y);
								pDC->SelectObject(pOldPen);
							}
							if ((pOldPen = pDC->SelectObject(&cPen[1])))
							{
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - (GetSystemMetrics(SM_CXEDGE) + 1), ptCaptionGrip.y);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - (GetSystemMetrics(SM_CXEDGE) + 1), rToolWnd.bottom - 1);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 2 * (GetSystemMetrics(SM_CXEDGE) + 1), rToolWnd.bottom - 1);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 + GetSystemMetrics(SM_CXEDGE) - 1, ptCaptionGrip.y);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 + GetSystemMetrics(SM_CXEDGE) - 1, rToolWnd.bottom - 1);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 2, rToolWnd.bottom - 1);
								pDC->SelectObject(pOldPen);
							}
							if ((pOldPen = pDC->SelectObject(&cPen[2])))
							{
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 2 * GetSystemMetrics(SM_CXEDGE), ptCaptionGrip.y + 1);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - 2 * GetSystemMetrics(SM_CXEDGE), rToolWnd.bottom - 2);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - GetSystemMetrics(SM_CXEDGE), ptCaptionGrip.y + 1);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_CAPTION_SIZE / 2 - GetSystemMetrics(SM_CXEDGE), rToolWnd.bottom - 2);
								pDC->SelectObject(pOldPen);
							}
						}
						if ((GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT))
						{
							pDC->FillRect(CRect(rToolWnd.left, rToolWnd.top, (GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) ? (rToolWnd.right - TOOLWINDOW_BORDER_SIZE) : rToolWnd.right, rToolWnd.top + TOOLWINDOW_CAPTION_SIZE), &cBorderBrush);
							pDC->FillRect(CRect(rToolWnd.left, rToolWnd.top, rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.bottom), &cBorderBrush);
							pDC->FillRect(CRect(rToolWnd.right - TOOLWINDOW_BORDER_SIZE, rToolWnd.top, rToolWnd.right, rToolWnd.bottom), &cBorderBrush);
							if ((pOldPen = pDC->SelectObject(&cPen[0])))
							{
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - 2 * GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->LineTo(ptCaptionGrip.x, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - 2 * GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - 2 * GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + 1);
								pDC->LineTo(ptCaptionGrip.x, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + 1);
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + 1);
								pDC->LineTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->SelectObject(pOldPen);
							}
							if ((pOldPen = pDC->SelectObject(&cPen[1])))
							{
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->LineTo(ptCaptionGrip.x, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->LineTo(ptCaptionGrip.x, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - 2 * GetSystemMetrics(SM_CYEDGE));
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->LineTo(ptCaptionGrip.x, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + GetSystemMetrics(SM_CYEDGE) + 1);
								pDC->LineTo(ptCaptionGrip.x, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2);
								pDC->SelectObject(pOldPen);
							}
							if ((pOldPen = pDC->SelectObject(&cPen[2])))
							{
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE + 1, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - GetSystemMetrics(SM_CYEDGE));
								pDC->LineTo(ptCaptionGrip.x - 1, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 - GetSystemMetrics(SM_CYEDGE));
								pDC->MoveTo(rToolWnd.left + TOOLWINDOW_BORDER_SIZE + 1, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + GetSystemMetrics(SM_CYEDGE));
								pDC->LineTo(ptCaptionGrip.x - 1, rToolWnd.top + (TOOLWINDOW_CAPTION_SIZE - TOOLWINDOW_BORDER_SIZE) / 2 + GetSystemMetrics(SM_CYEDGE));
								pDC->SelectObject(pOldPen);
							}
						}
					}
					m_wndExpandButtonCtrl.UpdateWindow();
					m_wndHideButtonCtrl.UpdateWindow();
					return TRUE;
				}
			}
		}
	}
	return CMiniFrameWnd::OnEraseBkgnd(pDC);
}

void CToolWnd::OnMove(int x, int y)
{
	RecalcLayout();
	CMiniFrameWnd::OnMove(x, y);
}

void CToolWnd::OnMoving(UINT nSide, LPRECT lpRect)
{
	AdjustDragFrame(GetCurrentMessage()->pt, lpRect);
	CMiniFrameWnd::OnMoving(nSide, lpRect);
}

BOOL CToolWnd::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	CPoint  pt;

	if (IsDocked())
	{
		for (pt = GetCurrentMessage()->pt, ScreenToClient(&pt); (IsPointOnSizeBorder(pt) && !IsDragged()) || IsSized(); )
		{
			SetCursor(LoadCursor(GetModuleHandle((LPCTSTR)NULL), ((IsPointOnSizeBorder(pt) & TOOLWINDOW_DOCKSTATE_LEFT) || (IsPointOnSizeBorder(pt) & TOOLWINDOW_DOCKSTATE_RIGHT) || (IsSized() & TOOLWINDOW_DOCKSTATE_LEFT) || (IsSized() & TOOLWINDOW_DOCKSTATE_RIGHT)) ? MAKEINTRESOURCE(IDC_SPLITHORIZONTAL) : MAKEINTRESOURCE(IDC_SPLITVERTICAL)));
			return TRUE;
		}
	}
	return CMiniFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CToolWnd::OnNcHitTest(CPoint point)
{
	CPoint  pt;

	if (IsDocked())
	{
		pt = point;
		ScreenToClient(&pt);
		return((IsPointOnDragCaption(pt)) ? HTCAPTION : CMiniFrameWnd::OnNcHitTest(point));
	}
	return CMiniFrameWnd::OnNcHitTest(point);
}

void CToolWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (nHitTest == HTCAPTION) StartDragging();
	CMiniFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void CToolWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect  rToolBorder;

	if (IsDocked())
	{
		if (CalcSizeBorder(IsPointOnSizeBorder(point), rToolBorder))
		{
			GetParent()->ClientToScreen(rToolBorder);
			m_wndSizeCtrl.Activate(rToolBorder);
		}
	}
	CMiniFrameWnd::OnLButtonDown(nFlags, point);
}

void CToolWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_ESCAPE)
	{
		GetTopLevelParent()->SetFocus();
		return;
	}
	CMiniFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CToolWnd::OnToolTip(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	CString  szTitle;
	CString  szToolTip;
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	GetWindowText(szTitle);
	if (pToolTipInfo->uFlags & TTF_IDISHWND)
	{
		if (pToolTipInfo->hdr.idFrom == (UINT_PTR)m_wndExpandButtonCtrl.GetSafeHwnd())
		{
			szToolTip.Format((!IsExpanded()) ? STRING(IDS_TOOLWINDOW_TOOLTIP_EXPAND) : STRING(IDS_TOOLWINDOW_TOOLTIP_CONTRACT), (LPCTSTR)szTitle);
			CopyMemory(pToolTipInfo->szText, (LPCTSTR)szToolTip, (szToolTip.GetLength() + 1)*sizeof(TCHAR));
			return TRUE;
		}
		if (pToolTipInfo->hdr.idFrom == (UINT_PTR)m_wndHideButtonCtrl.GetSafeHwnd())
		{
			szToolTip.Format(STRING(IDS_TOOLWINDOW_TOOLTIP_HIDE), (LPCTSTR)szTitle);
			CopyMemory(pToolTipInfo->szText, (LPCTSTR)szToolTip, (szToolTip.GetLength() + 1)*sizeof(TCHAR));
			return TRUE;
		}
	}
	return FALSE;
}

LRESULT CToolWnd::OnEnterSizeMove(WPARAM wParam, LPARAM lParam)
{
	StartDragging();
	return Default();
}

LRESULT CToolWnd::OnExitSizeMove(WPARAM wParam, LPARAM lParam)
{
	StopDragging();
	return 0;
}

void CToolWnd::OnExpand()
{
	Expand(IsExpanded());
}

void CToolWnd::OnHide()
{
	Hide();
}

void CToolWnd::OnDestroy()
{
	GetParent()->UnregisterToolWindow(this);
	m_wndSizeCtrl.DestroyWindow();
	CMiniFrameWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewPage

IMPLEMENT_DYNCREATE(CWorkspaceViewPage, CWnd)

CWorkspaceViewPage::CWorkspaceViewPage() : CWnd()
{
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CWorkspaceViewPage::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	return CWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), EMPTYSTRING, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, rect, (m_pParentWnd = pParentWnd), 0);
}

CWorkspaceView *CWorkspaceViewPage::GetParent() CONST
{
	return((CWorkspaceView *)m_pParentWnd);
}

BEGIN_MESSAGE_MAP(CWorkspaceViewPage, CWnd)
	//{{AFX_MSG_MAP(CWorkspaceViewPage)
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewPage message handlers

BOOL CWorkspaceViewPage::OnEraseBkgnd(CDC *pDC)
{
	CRect  rPage[2];

	for (GetWindowRect(rPage[0]), GetParent()->ScreenToClient(rPage[0]), GetParent()->CalcClientRect(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		MoveWindow(rPage[1]);
		return TRUE;
	}
	UpdateWindow();
	return TRUE;
}

void CWorkspaceViewPage::OnNcPaint()
{
	CRect  rPage[2];

	for (GetWindowRect(rPage[0]), GetParent()->ScreenToClient(rPage[0]), GetParent()->CalcClientRect(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		MoveWindow(rPage[1]);
		return;
	}
	CWnd::OnNcPaint();
}

void CWorkspaceViewPage::OnPaint()
{
	CRect  rPage;
	CPaintDC  cDC(this);

	GetClientRect(rPage);
	cDC.FillRect(rPage, CBrush::FromHandle(GetSysColorBrush(COLOR_WINDOW)));
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePageToolTip

IMPLEMENT_DYNCREATE(CWorkspaceViewDatabasePageToolTip, CWnd)

CWorkspaceViewDatabasePageToolTip::CWorkspaceViewDatabasePageToolTip() : CWnd()
{
	m_szText.Empty();
	m_rText.SetRectEmpty();
	m_bBoldText = FALSE;
}

BOOL CWorkspaceViewDatabasePageToolTip::ShowTip(CWnd *pParentWnd, LPCTSTR pszText, CONST RECT &rect, BOOL bBold)
{
	if ((m_szText != pszText  &&  lstrlen(pszText) > 0) && !m_rText.EqualRect(&rect))
	{
		for (DeleteTip(); CWnd::CreateEx(0, AfxRegisterWndClass(CS_DBLCLKS | CS_SAVEBITS | CS_DROPSHADOW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), EMPTYSTRING, WS_POPUP | WS_BORDER, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, (m_pParentWnd = pParentWnd)->GetSafeHwnd(), (HMENU)NULL); )
		{
			SetTimer(WORKSPACEVIEWDATABASEPAGE_TOOLTIP_TIMERID, 0, NULL);
			m_bBoldText = bBold;
			m_szText = pszText;
			m_rText = rect;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePageToolTip::DeleteTip()
{
	for (m_szText.Empty(), m_rText.SetRectEmpty(), m_bBoldText = FALSE; IsWindow(GetSafeHwnd()); )
	{
		KillTimer(WORKSPACEVIEWDATABASEPAGE_TOOLTIP_TIMERID);
		DestroyWindow();
		return TRUE;
	}
	return FALSE;
}

CWorkspaceViewDatabasePageTreeCtrl *CWorkspaceViewDatabasePageToolTip::GetParent() CONST
{
	return((CWorkspaceViewDatabasePageTreeCtrl *)m_pParentWnd);
}

VOID CWorkspaceViewDatabasePageToolTip::DrawContent(CDC *pDC)
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pFont;
	CFont  *pOldFont;
	CRect  rToolTip;
	LOGFONT  lfFont;

	for (GetClientRect(rToolTip); (pFont = GetParent()->GetFont()) && pFont->GetLogFont(&lfFont); )
	{
		if (cFont.CreateFont(lfFont.lfHeight, lfFont.lfWidth, lfFont.lfEscapement, lfFont.lfOrientation, (m_bBoldText) ? FW_BOLD : lfFont.lfWeight, lfFont.lfItalic, lfFont.lfUnderline, lfFont.lfStrikeOut, lfFont.lfCharSet, lfFont.lfOutPrecision, lfFont.lfClipPrecision, lfFont.lfQuality, lfFont.lfPitchAndFamily, lfFont.lfFaceName))
		{
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				nBkMode = pDC->SetBkMode(TRANSPARENT);
				pDC->DrawText(m_szText, CRect(GetSystemMetrics(SM_CXBORDER), 0, m_rText.Width(), m_rText.Height()), DT_LEFT | DT_TOP | DT_NOPREFIX);
				pDC->SelectObject(pOldFont);
				pDC->SetBkMode(nBkMode);
			}
			cFont.DeleteObject();
		}
		break;
	}
}

BEGIN_MESSAGE_MAP(CWorkspaceViewDatabasePageToolTip, CWnd)
	//{{AFX_MSG_MAP(CWorkspaceViewDatabasePageToolTip)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePageToolTip message handlers

BOOL CWorkspaceViewDatabasePageToolTip::OnEraseBkgnd(CDC *pDC)
{
	CRect  rToolTip;
	CBrush  cBkgndBrush;

	for (GetClientRect(rToolTip); cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK); )
	{
		pDC->FillRect(rToolTip, &cBkgndBrush);
		cBkgndBrush.DeleteObject();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CWorkspaceViewDatabasePageToolTip::OnPaint()
{
	CPaintDC  cDC(this);

	DrawContent(&cDC);
}

void CWorkspaceViewDatabasePageToolTip::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect  rToolTip;

	for (GetWindowRect(rToolTip), ScreenToClient(rToolTip); !rToolTip.PtInRect(point); )
	{
		DeleteTip();
		break;
	}
	SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	CWnd::OnMouseMove(nFlags, point);
}

void CWorkspaceViewDatabasePageToolTip::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->OpenDatabaseItem(pt);
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CWorkspaceViewDatabasePageToolTip::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ShowFloatingMenu(pt);
	CWnd::OnRButtonDown(nFlags, point);
}

void CWorkspaceViewDatabasePageToolTip::OnTimer(UINT_PTR nEventID)
{
	CPoint  ptCursor;

	if (nEventID == WORKSPACEVIEWDATABASEPAGE_TOOLTIP_TIMERID)
	{
		if (IsWindowVisible())
		{
			KillTimer(nEventID);
			ReleaseCapture();
			DestroyWindow();
			return;
		}
		for (GetCursorPos(&ptCursor); m_rText.PtInRect(ptCursor); )
		{
			SetTimer(WORKSPACEVIEWDATABASEPAGE_TOOLTIP_TIMERID, WORKSPACEVIEWDATABASEPAGE_TOOLTIP_TIMEOUT, NULL);
			ShowWindow(SW_SHOWNA);
			SetCapture();
			break;
		}
		if (!m_rText.PtInRect(ptCursor))
		{
			KillTimer(nEventID);
			DestroyWindow();
			return;
		}
	}
	CWnd::OnTimer(nEventID);
}

void CWorkspaceViewDatabasePageToolTip::OnDestroy()
{
	if (GetCapture()->GetSafeHwnd() == GetSafeHwnd()) ReleaseCapture();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePageTreeCtrl

IMPLEMENT_DYNCREATE(CWorkspaceViewDatabasePageTreeCtrl, CTreeCtrl)

CWorkspaceViewDatabasePageTreeCtrl::CWorkspaceViewDatabasePageTreeCtrl() : CTreeCtrl()
{
	return;
}

VOID CWorkspaceViewDatabasePageTreeCtrl::OpenDatabaseItem(CONST POINT &ptItem)
{
	GetParent()->OpenDatabaseItem(ptItem);
}

VOID CWorkspaceViewDatabasePageTreeCtrl::ShowFloatingMenu(CONST POINT &ptItem)
{
	GetParent()->ShowFloatingMenu(ptItem);
}

CWorkspaceViewDatabasePage *CWorkspaceViewDatabasePageTreeCtrl::GetParent() CONST
{
	return((CWorkspaceViewDatabasePage *)CTreeCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CWorkspaceViewDatabasePageTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CWorkspaceViewDatabasePageTreeCtrl)
	ON_WM_SETCURSOR()
	ON_WM_CHAR()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePageTreeCtrl message handlers

BOOL CWorkspaceViewDatabasePageTreeCtrl::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	CRect  rEdit;
	POINT  ptCursor;

	if (IsWindow(GetEditControl()->GetSafeHwnd()) && GetEditControl()->IsWindowVisible())
	{
		for (GetCursorPos(&ptCursor), GetEditControl()->GetWindowRect(rEdit); rEdit.PtInRect(ptCursor); )
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_IBEAM));
			return TRUE;
		}
	}
	return CTreeCtrl::OnSetCursor(pWnd, nHitTest, message);
}

void CWorkspaceViewDatabasePageTreeCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN || nChar == VK_ESCAPE) return;
	CTreeCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CWorkspaceViewDatabasePageTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect  rItem;
	CPoint  ptItem;
	HTREEITEM  hItem;

	for (hItem = GetFirstVisibleItem(); hItem != (HTREEITEM)NULL; hItem = GetNextVisibleItem(hItem))
	{
		if (GetItemRect(hItem, rItem, FALSE) && rItem.PtInRect(point))
		{
			ClientToScreen(&(ptItem = point));
			ShowFloatingMenu(ptItem);
			return;
		}
	}
	CTreeCtrl::OnRButtonDown(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePage

IMPLEMENT_DYNCREATE(CWorkspaceViewDatabasePage, CWorkspaceViewPage)

CWorkspaceViewDatabasePage::CWorkspaceViewDatabasePage() : CWorkspaceViewPage()
{
	m_hItem = (HTREEITEM)NULL;
	m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] = 0;
	m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] = 0;
	m_bDragItem = FALSE;
	m_nDragItem = 0;
	m_nTimerID = 0;
}

VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sTMPacketItem[2];
	HTREEITEM  hTMPacketItem;
	HTREEITEM  hTMPacketFolder;

	if ((hTMPacketFolder = FindTMPacketFolder()))
	{
		for (hTMPacketItem = m_wndView.GetChildItem(hTMPacketFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETITEMTEXT), (LPCTSTR)pDatabaseTMPacket->GetDescription(), (LPCTSTR)pDatabaseTMPacket->GetTag()), nIndex = 0; hTMPacketItem; hTMPacketItem = m_wndView.GetNextItem(hTMPacketItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pDatabaseTMPacket->GetTag().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hTMPacketItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_TMPACKETSYMBOL, WORKSPACEDATABASEPAGE_TMPACKETSYMBOL, hTMPacketFolder, (hTMPacketItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hTMPacketItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hTMPacketItem, (DWORD_PTR)lstrcpy(pszName, pDatabaseTMPacket->GetTag())))
				{
					sTMPacketItem[0].hItem = hTMPacketFolder;
					sTMPacketItem[1].hItem = hTMPacketFolder;
					sTMPacketItem[0].mask = TVIF_CHILDREN;
					sTMPacketItem[1].mask = TVIF_CHILDREN;
					sTMPacketItem[0].cChildren = TRUE;
					sTMPacketItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sTMPacketItem[0]);
					m_wndView.SetItem(&sTMPacketItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hTMPacketItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hTMPacketItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hTMPacketItem, szItem);
			return;
		}
		if (hTMPacketItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] = (m_wndView.DeleteItem(hTMPacketItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sTCFunctionItem[2];
	HTREEITEM  hTCFunctionItem;
	HTREEITEM  hTCFunctionFolder;

	if ((hTCFunctionFolder = FindTCFunctionFolder()))
	{
		for (hTCFunctionItem = m_wndView.GetChildItem(hTCFunctionFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONITEMTEXT), (LPCTSTR)pDatabaseTCFunction->GetDescription(), (LPCTSTR)pDatabaseTCFunction->GetName()), nIndex = 0; hTCFunctionItem; hTCFunctionItem = m_wndView.GetNextItem(hTCFunctionItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pDatabaseTCFunction->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hTCFunctionItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL, WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL, hTCFunctionFolder, (hTCFunctionItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hTCFunctionItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hTCFunctionItem, (DWORD_PTR)lstrcpy(pszName, pDatabaseTCFunction->GetName())))
				{
					sTCFunctionItem[0].hItem = hTCFunctionFolder;
					sTCFunctionItem[1].hItem = hTCFunctionFolder;
					sTCFunctionItem[0].mask = TVIF_CHILDREN;
					sTCFunctionItem[1].mask = TVIF_CHILDREN;
					sTCFunctionItem[0].cChildren = TRUE;
					sTCFunctionItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sTCFunctionItem[0]);
					m_wndView.SetItem(&sTCFunctionItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hTCFunctionItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hTCFunctionItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hTCFunctionItem, szItem);
			return;
		}
		if (hTCFunctionItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] = (m_wndView.DeleteItem(hTCFunctionItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szTag;
	CString  szItem;
	CString  szDescription;
	HTREEITEM  hTMParameterItem;
	HTREEITEM  hTMParameterFolder;
	TVITEM  sTMParameterItem[2];

	if ((hTMParameterFolder = FindTMParameterFolder()))
	{
		for (hTMParameterItem = m_wndView.GetChildItem(hTMParameterFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERITEMTEXT), (LPCTSTR)(szDescription = pDatabaseTMParameter->GetDescription()), (LPCTSTR)(szTag = pDatabaseTMParameter->GetTag())), szItem = (szDescription.IsEmpty()) ? szTag : szItem, nIndex = 0; hTMParameterItem; hTMParameterItem = m_wndView.GetNextItem(hTMParameterItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pDatabaseTMParameter->GetTag().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hTMParameterItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL, WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL, hTMParameterFolder, (hTMParameterItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hTMParameterItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hTMParameterItem, (DWORD_PTR)lstrcpy(pszName, pDatabaseTMParameter->GetTag())))
				{
					sTMParameterItem[0].hItem = hTMParameterFolder;
					sTMParameterItem[1].hItem = hTMParameterFolder;
					sTMParameterItem[0].mask = TVIF_CHILDREN;
					sTMParameterItem[1].mask = TVIF_CHILDREN;
					sTMParameterItem[0].cChildren = TRUE;
					sTMParameterItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sTMParameterItem[0]);
					m_wndView.SetItem(&sTMParameterItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hTMParameterItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hTMParameterItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hTMParameterItem, szItem);
			return;
		}
		if (hTMParameterItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] = (m_wndView.DeleteItem(hTMParameterItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szTag;
	CString  szItem;
	CString  szDescription;
	HTREEITEM  hTCParameterItem;
	HTREEITEM  hTCParameterFolder;
	TVITEM  sTCParameterItem[2];

	if ((hTCParameterFolder = FindTCParameterFolder()))
	{
		for (hTCParameterItem = m_wndView.GetChildItem(hTCParameterFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERITEMTEXT), (LPCTSTR)(szDescription = pDatabaseTCParameter->GetDescription()), (LPCTSTR)(szTag = pDatabaseTCParameter->GetTag())), szItem = (szDescription.IsEmpty()) ? szTag : szItem, nIndex = 0; hTCParameterItem; hTCParameterItem = m_wndView.GetNextItem(hTCParameterItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pDatabaseTCParameter->GetTag().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hTCParameterItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL, WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL, hTCParameterFolder, (hTCParameterItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hTCParameterItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hTCParameterItem, (DWORD_PTR)lstrcpy(pszName, pDatabaseTCParameter->GetTag())))
				{
					sTCParameterItem[0].hItem = hTCParameterFolder;
					sTCParameterItem[1].hItem = hTCParameterFolder;
					sTCParameterItem[0].mask = TVIF_CHILDREN;
					sTCParameterItem[1].mask = TVIF_CHILDREN;
					sTCParameterItem[0].cChildren = TRUE;
					sTCParameterItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sTCParameterItem[0]);
					m_wndView.SetItem(&sTCParameterItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hTCParameterItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hTCParameterItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hTCParameterItem, szItem);
			return;
		}
		if (hTCParameterItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] = (m_wndView.DeleteItem(hTCParameterItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sOBProcessorItem[2];
	HTREEITEM  hOBProcessorItem;
	HTREEITEM  hOBProcessorFolder;

	if ((hOBProcessorFolder = FindOBProcessorFolder()))
	{
		for (hOBProcessorItem = m_wndView.GetChildItem(hOBProcessorFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORITEMTEXT), (LPCTSTR)pDatabaseOBProcessor->GetName(), (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseOBProcessor->GetDescription() : (LPCTSTR)pDatabaseOBProcessor->GetDetails()), nIndex = 0; hOBProcessorItem; hOBProcessorItem = m_wndView.GetNextItem(hOBProcessorItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pDatabaseOBProcessor->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hOBProcessorItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL, WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL, hOBProcessorFolder, (hOBProcessorItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hOBProcessorItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hOBProcessorItem, (DWORD_PTR)lstrcpy(pszName, pDatabaseOBProcessor->GetName())))
				{
					sOBProcessorItem[0].hItem = hOBProcessorFolder;
					sOBProcessorItem[1].hItem = hOBProcessorFolder;
					sOBProcessorItem[0].mask = TVIF_CHILDREN;
					sOBProcessorItem[1].mask = TVIF_CHILDREN;
					sOBProcessorItem[0].cChildren = TRUE;
					sOBProcessorItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sOBProcessorItem[0]);
					m_wndView.SetItem(&sOBProcessorItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hOBProcessorItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hOBProcessorItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hOBProcessorItem, szItem);
			return;
		}
		if (hOBProcessorItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] = (m_wndView.DeleteItem(hOBProcessorItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sANDItem[2];
	HTREEITEM  hANDItem;
	HTREEITEM  hANDFolder;

	if ((hANDFolder = FindANDFolder()))
	{
		for (hANDItem = m_wndView.GetChildItem(hANDFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDITEMTEXT), (LPCTSTR)pANDWnd->GetTitle(), (LPCTSTR)pANDWnd->GetName()), szItem = (pANDWnd->GetTitle().IsEmpty()) ? pANDWnd->GetName() : szItem, nIndex = 0; hANDItem; hANDItem = m_wndView.GetNextItem(hANDItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pANDWnd->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hANDItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_ANDSYMBOL, WORKSPACEDATABASEPAGE_ANDSYMBOL, hANDFolder, (hANDItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hANDItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hANDItem, (DWORD_PTR)lstrcpy(pszName, pANDWnd->GetName())))
				{
					sANDItem[0].hItem = hANDFolder;
					sANDItem[1].hItem = hANDFolder;
					sANDItem[0].mask = TVIF_CHILDREN;
					sANDItem[1].mask = TVIF_CHILDREN;
					sANDItem[0].cChildren = TRUE;
					sANDItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sANDItem[0]);
					m_wndView.SetItem(&sANDItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hANDItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hANDItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hANDItem, szItem);
			return;
		}
		if (hANDItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] = (m_wndView.DeleteItem(hANDItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sGRDItem[2];
	HTREEITEM  hGRDItem;
	HTREEITEM  hGRDFolder;

	if ((hGRDFolder = FindGRDFolder()))
	{
		for (hGRDItem = m_wndView.GetChildItem(hGRDFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDITEMTEXT), (LPCTSTR)pGRDWnd->GetTitle(), (LPCTSTR)pGRDWnd->GetName()), szItem = (pGRDWnd->GetTitle().IsEmpty()) ? pGRDWnd->GetName() : szItem, nIndex = 0; hGRDItem; hGRDItem = m_wndView.GetNextItem(hGRDItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pGRDWnd->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hGRDItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_GRDSYMBOL, WORKSPACEDATABASEPAGE_GRDSYMBOL, hGRDFolder, (hGRDItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hGRDItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hGRDItem, (DWORD_PTR)lstrcpy(pszName, pGRDWnd->GetName())))
				{
					sGRDItem[0].hItem = hGRDFolder;
					sGRDItem[1].hItem = hGRDFolder;
					sGRDItem[0].mask = TVIF_CHILDREN;
					sGRDItem[1].mask = TVIF_CHILDREN;
					sGRDItem[0].cChildren = TRUE;
					sGRDItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sGRDItem[0]);
					m_wndView.SetItem(&sGRDItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hGRDItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hGRDItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hGRDItem, szItem);
			return;
		}
		if (hGRDItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] = (m_wndView.DeleteItem(hGRDItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sMMDItem[2];
	HTREEITEM  hMMDItem;
	HTREEITEM  hMMDFolder;

	if ((hMMDFolder = FindMMDFolder()))
	{
		for (hMMDItem = m_wndView.GetChildItem(hMMDFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDITEMTEXT), (LPCTSTR)pMMDWnd->GetTitle(), (LPCTSTR)pMMDWnd->GetName()), szItem = (pMMDWnd->GetTitle().IsEmpty()) ? pMMDWnd->GetName() : szItem, nIndex = 0; hMMDItem; hMMDItem = m_wndView.GetNextItem(hMMDItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pMMDWnd->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hMMDItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_MMDSYMBOL, WORKSPACEDATABASEPAGE_MMDSYMBOL, hMMDFolder, (hMMDItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hMMDItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hMMDItem, (DWORD_PTR)lstrcpy(pszName, pMMDWnd->GetName())))
				{
					sMMDItem[0].hItem = hMMDFolder;
					sMMDItem[1].hItem = hMMDFolder;
					sMMDItem[0].mask = TVIF_CHILDREN;
					sMMDItem[1].mask = TVIF_CHILDREN;
					sMMDItem[0].cChildren = TRUE;
					sMMDItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sMMDItem[0]);
					m_wndView.SetItem(&sMMDItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hMMDItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hMMDItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hMMDItem, szItem);
			return;
		}
		if (hMMDItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] = (m_wndView.DeleteItem(hMMDItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sPODItem[2];
	HTREEITEM  hPODItem;
	HTREEITEM  hPODFolder;

	if ((hPODFolder = FindPODFolder()))
	{
		for (hPODItem = m_wndView.GetChildItem(hPODFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODITEMTEXT), (LPCTSTR)pPODWnd->GetTitle(), (LPCTSTR)pPODWnd->GetName()), szItem = (pPODWnd->GetTitle().IsEmpty()) ? pPODWnd->GetName() : szItem, nIndex = 0; hPODItem; hPODItem = m_wndView.GetNextItem(hPODItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pPODWnd->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hPODItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_PODSYMBOL, WORKSPACEDATABASEPAGE_PODSYMBOL, hPODFolder, (hPODItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hPODItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hPODItem, (DWORD_PTR)lstrcpy(pszName, pPODWnd->GetName())))
				{
					sPODItem[0].hItem = hPODFolder;
					sPODItem[1].hItem = hPODFolder;
					sPODItem[0].mask = TVIF_CHILDREN;
					sPODItem[1].mask = TVIF_CHILDREN;
					sPODItem[0].cChildren = TRUE;
					sPODItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sPODItem[0]);
					m_wndView.SetItem(&sPODItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hPODItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hPODItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hPODItem, szItem);
			return;
		}
		if (hPODItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] = (m_wndView.DeleteItem(hPODItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sScriptItem[2];
	HTREEITEM  hScriptItem;
	HTREEITEM  hScriptFolder;

	if ((hScriptFolder = FindScriptFolder()))
	{
		for (hScriptItem = m_wndView.GetChildItem(hScriptFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTITEMTEXT), (LPCTSTR)pScriptWnd->GetTitle(), (LPCTSTR)pScriptWnd->GetName()), szItem = (pScriptWnd->GetTitle().IsEmpty()) ? pScriptWnd->GetName() : szItem, nIndex = 0; hScriptItem; hScriptItem = m_wndView.GetNextItem(hScriptItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pScriptWnd->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hScriptItem = m_wndView.InsertItem(szItem, WORKSPACEDATABASEPAGE_SCRIPTSYMBOL, WORKSPACEDATABASEPAGE_SCRIPTSYMBOL, hScriptFolder, (hScriptItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hScriptItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hScriptItem, (DWORD_PTR)lstrcpy(pszName, pScriptWnd->GetName())))
				{
					sScriptItem[0].hItem = hScriptFolder;
					sScriptItem[1].hItem = hScriptFolder;
					sScriptItem[0].mask = TVIF_CHILDREN;
					sScriptItem[1].mask = TVIF_CHILDREN;
					sScriptItem[0].cChildren = TRUE;
					sScriptItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sScriptItem[0]);
					m_wndView.SetItem(&sScriptItem[1]);
					m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hScriptItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hScriptItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hScriptItem, szItem);
			return;
		}
		if (hScriptItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] = (m_wndView.DeleteItem(hScriptItem)) ? max(m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] - 1, 0) : m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewDatabasePage::UpdateDatabaseContents()
{
	TVITEM  sRootItem;
	CString  szDatabaseRoot;

	for (szDatabaseRoot.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ROOTSYMBOLTEXT), (LPCTSTR)GetAccountDatabase()), szDatabaseRoot = (GetAccountDatabase().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ROOTNOSYMBOLTEXT) : szDatabaseRoot, m_wndView.DeleteAllItems(); (sRootItem.hItem = m_wndView.InsertItem((GetDatabase()->IsOpen()) ? (LPCTSTR)szDatabaseRoot : STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ROOTNOSYMBOLTEXT), (GetDatabase()->IsOpen()) ? WORKSPACEDATABASEPAGE_ROOTSYMBOL : WORKSPACEDATABASEPAGE_ROOTNOSYMBOL, (GetDatabase()->IsOpen()) ? WORKSPACEDATABASEPAGE_ROOTSYMBOL : WORKSPACEDATABASEPAGE_ROOTNOSYMBOL, (HTREEITEM)NULL, (HTREEITEM)NULL)) && m_wndView.SetItemState(sRootItem.hItem, TVIS_BOLD, TVIS_BOLD); )
	{
		EnumTMPackets(sRootItem.hItem);
		EnumTCFunctions(sRootItem.hItem);
		EnumTMParameters(sRootItem.hItem);
		EnumTCParameters(sRootItem.hItem);
		EnumOBProcessors(sRootItem.hItem);
		EnumANDs(sRootItem.hItem);
		EnumGRDs(sRootItem.hItem);
		EnumMMDs(sRootItem.hItem);
		EnumPODs(sRootItem.hItem);
		EnumScripts(sRootItem.hItem);
		m_wndView.Expand(sRootItem.hItem, TVE_EXPAND);
		break;
	}
}

BOOL CWorkspaceViewDatabasePage::CreateDatabaseItem()
{
	CString  szItem;
	HTREEITEM  hItem;

	if ((FindFolder((szItem = m_wndView.GetItemText((hItem = m_wndView.GetSelectedItem())))) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETSYMBOLTEXT)) || FindTMPacketItem(hItem)) return CreateTMPacket();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONSYMBOLTEXT)) || FindTCFunctionItem(hItem)) return CreateTCFunction();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERSYMBOLTEXT)) || FindTMParameterItem(hItem)) return CreateTMParameter();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERSYMBOLTEXT)) || FindTCParameterItem(hItem)) return CreateTCParameter();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORSYMBOLTEXT)) || FindOBProcessorItem(hItem)) return CreateOBProcessor();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDSYMBOLTEXT)) || FindANDItem(hItem)) return CreateAND();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDSYMBOLTEXT)) || FindGRDItem(hItem)) return CreateGRD();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDSYMBOLTEXT)) || FindMMDItem(hItem)) return CreateMMD();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODSYMBOLTEXT)) || FindPODItem(hItem)) return CreatePOD();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTSYMBOLTEXT)) || FindScriptItem(hItem)) return CreateScript();
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::OpenDatabaseItem()
{
	HTREEITEM  hItem;

	if (FindTMPacketItem((hItem = m_wndView.GetSelectedItem()))) return OpenTMPacket(hItem);
	if (FindTCFunctionItem(hItem)) return OpenTCFunction(hItem);
	if (FindTMParameterItem(hItem)) return OpenTMParameter(hItem);
	if (FindTCParameterItem(hItem)) return OpenTCParameter(hItem);
	if (FindOBProcessorItem(hItem)) return OpenOBProcessor(hItem);
	if (FindANDItem(hItem)) return OpenAND(hItem);
	if (FindGRDItem(hItem)) return OpenGRD(hItem);
	if (FindMMDItem(hItem)) return OpenMMD(hItem);
	if (FindPODItem(hItem)) return OpenPOD(hItem);
	if (FindScriptItem(hItem)) return OpenScript(hItem);
	return FALSE;
}
VOID CWorkspaceViewDatabasePage::OpenDatabaseItem(CONST POINT &ptItem)
{
	UINT  nFlags;
	POINT  point;
	CString  szMessage;
	HTREEITEM  hItem;

	point.x = ptItem.x;
	point.y = ptItem.y;
	m_wndView.ScreenToClient(&point);
	if ((hItem = m_wndView.HitTest(point, &nFlags)))
	{
		if (nFlags & TVHT_ONITEM)
		{
			if (FindTMPacketItem(hItem))
			{
				if (!OpenTMPacket(hItem))
				{
					szMessage.Format(STRING(IDS_TMPACKET_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindTCFunctionItem(hItem))
			{
				if (!OpenTCFunction(hItem))
				{
					szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindTMParameterItem(hItem))
			{
				if (!OpenTMParameter(hItem))
				{
					szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindTCParameterItem(hItem))
			{
				if (!OpenTCParameter(hItem))
				{
					szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindOBProcessorItem(hItem))
			{
				if (!OpenOBProcessor(hItem))
				{
					szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindANDItem(hItem))
			{
				if (!OpenAND(hItem))
				{
					szMessage.Format(STRING(IDS_AND_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindGRDItem(hItem))
			{
				if (!OpenGRD(hItem))
				{
					szMessage.Format(STRING(IDS_GRD_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindMMDItem(hItem))
			{
				if (!OpenMMD(hItem))
				{
					szMessage.Format(STRING(IDS_MMD_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindPODItem(hItem))
			{
				if (!OpenPOD(hItem))
				{
					szMessage.Format(STRING(IDS_POD_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindScriptItem(hItem))
			{
				if (!OpenScript(hItem))
				{
					szMessage.Format(STRING(IDS_SCRIPT_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
		}
	}
}

BOOL CWorkspaceViewDatabasePage::HasDatabaseItem(INT nType) CONST
{
	if (nType == DATABASE_COMPONENT_TMPACKET) return m_wndView.ItemHasChildren(FindTMPacketFolder());
	if (nType == DATABASE_COMPONENT_TCFUNCTION) return m_wndView.ItemHasChildren(FindTCFunctionFolder());
	if (nType == DATABASE_COMPONENT_TMPARAMETER) return m_wndView.ItemHasChildren(FindTMParameterFolder());
	if (nType == DATABASE_COMPONENT_TCPARAMETER) return m_wndView.ItemHasChildren(FindTCParameterFolder());
	if (nType == DATABASE_COMPONENT_OBPROCESSOR) return m_wndView.ItemHasChildren(FindOBProcessorFolder());
	if (nType == DATABASE_COMPONENT_AND) return m_wndView.ItemHasChildren(FindANDFolder());
	if (nType == DATABASE_COMPONENT_GRD) return m_wndView.ItemHasChildren(FindGRDFolder());
	if (nType == DATABASE_COMPONENT_MMD) return m_wndView.ItemHasChildren(FindMMDFolder());
	if (nType == DATABASE_COMPONENT_POD) return m_wndView.ItemHasChildren(FindPODFolder());
	if (nType == DATABASE_COMPONENT_SCRIPT) return m_wndView.ItemHasChildren(FindScriptFolder());
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::RenameDatabaseItem()
{
	HTREEITEM  hItem;

	if (FindTMPacketItem((hItem = m_wndView.GetSelectedItem()))) return RenameTMPacket(hItem);
	if (FindTCFunctionItem(hItem)) return RenameTCFunction(hItem);
	if (FindTMParameterItem(hItem)) return RenameTMParameter(hItem);
	if (FindTCParameterItem(hItem)) return RenameTCParameter(hItem);
	if (FindOBProcessorItem(hItem)) return RenameOBProcessor(hItem);
	if (FindANDItem(hItem)) return RenameAND(hItem);
	if (FindGRDItem(hItem)) return RenameGRD(hItem);
	if (FindMMDItem(hItem)) return RenameMMD(hItem);
	if (FindPODItem(hItem)) return RenamePOD(hItem);
	if (FindScriptItem(hItem)) return RenameScript(hItem);
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::DeleteDatabaseItem()
{
	HTREEITEM  hItem;
	CString  szMessage;

	if (FindTMPacketItem((hItem = m_wndView.GetSelectedItem())))
	{
		for (szMessage.Format(STRING(IDS_TMPACKET_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTMPacket(hItem); )
		{
			szMessage.Format(STRING(IDS_TMPACKET_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindTCFunctionItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_TCFUNCTION_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTCFunction(hItem); )
		{
			szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindTMParameterItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_TMPARAMETER_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTMParameter(hItem); )
		{
			szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindTCParameterItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_TCPARAMETER_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTCParameter(hItem); )
		{
			szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindOBProcessorItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_OBPROCESSOR_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteOBProcessor(hItem); )
		{
			szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindANDItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_AND_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteAND(hItem); )
		{
			szMessage.Format(STRING(IDS_AND_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindGRDItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_GRD_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteGRD(hItem); )
		{
			szMessage.Format(STRING(IDS_GRD_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindMMDItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_MMD_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteMMD(hItem); )
		{
			szMessage.Format(STRING(IDS_MMD_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindPODItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_POD_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeletePOD(hItem); )
		{
			szMessage.Format(STRING(IDS_POD_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindScriptItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_SCRIPT_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteScript(hItem); )
		{
			szMessage.Format(STRING(IDS_SCRIPT_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CWorkspaceViewDatabasePage::ShowFloatingMenu(CONST POINT &ptItem)
{
	UINT  nFlags;
	POINT  point;
	CString  szItem;
	HTREEITEM  hItem;

	for (point.x = ptItem.x, point.y = ptItem.y, m_wndView.ScreenToClient(&point); (hItem = m_wndView.HitTest(point, &nFlags)); )
	{
		if (nFlags & TVHT_ONITEM)
		{
			if (FindTMPacketItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindTCFunctionItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindTMParameterItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindTCParameterItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindOBProcessorItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindANDItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindGRDItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindMMDItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindPODItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindScriptItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindFolder((szItem = m_wndView.GetItemText(hItem))))
			{
				ShowFloatingMenu(hItem, szItem, point);
				return;
			}
		}
		break;
	}
}
VOID CWorkspaceViewDatabasePage::ShowFloatingMenu(HTREEITEM hItem, CPoint point)
{
	UINT  nID;
	CPoint  ptMenu;
	CLocaleMenu  cMenu;
	CMFCPopupMenu  *pFloatingMenu;

	for (nID = IDR_TMPACKETFOLDERFORMMENU*FindTMPacketItem(hItem) + IDR_TCFUNCTIONFOLDERFORMMENU*FindTCFunctionItem(hItem) + IDR_TMPARAMETERFOLDERFORMMENU*FindTMParameterItem(hItem) + IDR_TCPARAMETERFOLDERFORMMENU*FindTCParameterItem(hItem) + IDR_OBPROCESSORFOLDERFORMMENU*FindOBProcessorItem(hItem) + IDR_ANDFOLDERFORMMENU*FindANDItem(hItem) + IDR_GRDFOLDERFORMMENU*FindGRDItem(hItem) + IDR_MMDFOLDERFORMMENU*FindMMDItem(hItem) + IDR_PODFOLDERFORMMENU*FindPODItem(hItem) + IDR_SCRIPTFOLDERFORMMENU*FindScriptItem(hItem); nID != 0; )
	{
		for (m_wndView.ClientToScreen(&(ptMenu = point)), m_wndView.SetFocus(); m_wndView.GetSelectedItem() != hItem; )
		{
			m_wndView.SelectItem(hItem);
			break;
		}
		if ((pFloatingMenu = (cMenu.LoadMenu(nID)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL)) pFloatingMenu->Create(this, ptMenu.x, ptMenu.y, cMenu.Detach());
		break;
	}
}
VOID CWorkspaceViewDatabasePage::ShowFloatingMenu(HTREEITEM hItem, LPCTSTR pszItem, CPoint point)
{
	UINT  nID;
	CPoint  ptMenu;
	CLocaleMenu  cMenu;
	CMFCPopupMenu  *pFloatingMenu;

	for (nID = (hItem == FindTMPacketFolder()) ? IDR_TMPACKETFOLDERMENU : 0, nID = (hItem == FindTCFunctionFolder()) ? IDR_TCFUNCTIONFOLDERMENU : nID, nID = (hItem == FindTMParameterFolder()) ? IDR_TMPARAMETERFOLDERMENU : nID, nID = (hItem == FindTCParameterFolder()) ? IDR_TCPARAMETERFOLDERMENU : nID, nID = (hItem == FindOBProcessorFolder()) ? IDR_OBPROCESSORFOLDERMENU : nID, nID = (hItem == FindANDFolder()) ? IDR_ANDFOLDERMENU : nID, nID = (hItem == FindGRDFolder()) ? IDR_GRDFOLDERMENU : nID, nID = (hItem == FindMMDFolder()) ? IDR_MMDFOLDERMENU : nID, nID = (hItem == FindPODFolder()) ? IDR_PODFOLDERMENU : nID, nID = (hItem == FindScriptFolder()) ? IDR_SCRIPTFOLDERMENU : nID; nID != 0; )
	{
		for (m_wndView.ClientToScreen(&(ptMenu = point)), m_wndView.SetFocus(); m_wndView.GetSelectedItem() != hItem; )
		{
			m_wndView.SelectItem(hItem);
			break;
		}
		if ((pFloatingMenu = (cMenu.LoadMenu(nID)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL)) pFloatingMenu->Create(this, ptMenu.x, ptMenu.y, cMenu.Detach());
		break;
	}
}

BOOL CWorkspaceViewDatabasePage::CanDeleteSel() CONST
{
	HTREEITEM  hItem;

	return(((hItem = m_wndView.GetSelectedItem()) && CWnd::GetFocus()->GetSafeHwnd() == m_wndView.GetSafeHwnd()) ? ((FindTMPacketItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE)) || (FindTCFunctionItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE)) || (FindTMParameterItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE)) || (FindTCParameterItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE)) || (FindOBProcessorItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE)) || (FindANDItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE)) || (FindGRDItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE)) || (FindMMDItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE)) || (FindPODItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_POD_CHANGE)) || (FindScriptItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE))) : FALSE);
}

VOID CWorkspaceViewDatabasePage::DoDeleteSel()
{
	HTREEITEM  hItem;
	CString  szMessage;

	if (CanDeleteSel())
	{
		if (FindTMPacketItem((hItem = m_wndView.GetSelectedItem())))
		{
			for (szMessage.Format(STRING(IDS_TMPACKET_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTMPacket(hItem); )
			{
				szMessage.Format(STRING(IDS_TMPACKET_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindTCFunctionItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_TCFUNCTION_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTCFunction(hItem); )
			{
				szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindTMParameterItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_TMPARAMETER_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTMParameter(hItem); )
			{
				szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindTCParameterItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_TCPARAMETER_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTCParameter(hItem); )
			{
				szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindOBProcessorItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_OBPROCESSOR_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteOBProcessor(hItem); )
			{
				szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindANDItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_AND_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteAND(hItem); )
			{
				szMessage.Format(STRING(IDS_AND_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindGRDItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_GRD_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteGRD(hItem); )
			{
				szMessage.Format(STRING(IDS_GRD_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindMMDItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_MMD_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteMMD(hItem); )
			{
				szMessage.Format(STRING(IDS_MMD_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindPODItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_POD_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeletePOD(hItem); )
			{
				szMessage.Format(STRING(IDS_POD_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
		if (FindScriptItem(hItem))
		{
			for (szMessage.Format(STRING(IDS_SCRIPT_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteScript(hItem); )
			{
				szMessage.Format(STRING(IDS_SCRIPT_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
				break;
			}
		}
	}
}

VOID CWorkspaceViewDatabasePage::EnumTMPackets(HTREEITEM hParentItem)
{
	INT  nPacket;
	INT  nPackets;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szName[2];
	CString  szDescription;
	HTREEITEM  hTMPacketItem[2];
	CDatabaseTMPacket  *pDatabaseTMPacket;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindTMPacketFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nPacket = 0, nPackets = m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] = (INT)GetDatabase()->GetTMPackets()->GetSize(), hTMPacketItem[0] = hTMPacketItem[1] = (HTREEITEM)NULL; nPacket < nPackets; nPacket++)
		{
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(nPacket)))
			{
				szName[0] = pDatabaseTMPacket->GetTag();
				szDescription = pDatabaseTMPacket->GetDescription();
				szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETITEMTEXT), (LPCTSTR)szDescription, (LPCTSTR)szName[0]);
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))) != (LPTSTR)NULL)
				{
					if ((hTMPacketItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_TMPACKETSYMBOL, WORKSPACEDATABASEPAGE_TMPACKETSYMBOL, sFolderItem.hItem, (!hTMPacketItem[0]) ? TVI_FIRST : hTMPacketItem[0])))
					{
						if (m_wndView.SetItemData(hTMPacketItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hTMPacketItem[0] = hTMPacketItem[1];
							continue;
						}
						m_wndView.DeleteItem(hTMPacketItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hTMPacketItem[1] = m_wndView.GetNextItem(hTMPacketItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hTMPacketItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] = nPacket;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumTCFunctions(HTREEITEM hParentItem)
{
	INT  nFunction;
	INT  nFunctions;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szName[2];
	CString  szDescription;
	HTREEITEM  hTCFunctionItem[2];
	CDatabaseTCFunction  *pDatabaseTCFunction;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindTCFunctionFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nFunction = 0, nFunctions = m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] = (INT)GetDatabase()->GetTCFunctions()->GetSize(), hTCFunctionItem[0] = hTCFunctionItem[1] = (HTREEITEM)NULL; nFunction < nFunctions; nFunction++)
		{
			if ((pDatabaseTCFunction = GetDatabase()->GetTCFunctions()->GetAt(nFunction)))
			{
				szName[0] = pDatabaseTCFunction->GetName();
				szDescription = pDatabaseTCFunction->GetDescription();
				szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONITEMTEXT), (LPCTSTR)szDescription, (LPCTSTR)szName[0]);
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))) != (LPTSTR)NULL)
				{
					if ((hTCFunctionItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL, WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL, sFolderItem.hItem, (!hTCFunctionItem[0]) ? TVI_FIRST : hTCFunctionItem[0])))
					{
						if (m_wndView.SetItemData(hTCFunctionItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hTCFunctionItem[0] = hTCFunctionItem[1];
							continue;
						}
						m_wndView.DeleteItem(hTCFunctionItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hTCFunctionItem[1] = m_wndView.GetNextItem(hTCFunctionItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hTCFunctionItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] = nFunction;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumTMParameters(HTREEITEM hParentItem)
{
	INT  nParameter;
	INT  nParameters;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szName[2];
	CString  szDescription;
	HTREEITEM  hTMParameterItem[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindTMParameterFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nParameter = 0, nParameters = m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] = (INT)GetDatabase()->GetTMParameters()->GetSize(), hTMParameterItem[0] = hTMParameterItem[1] = (HTREEITEM)NULL; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)))
			{
				szName[0] = pDatabaseTMParameter->GetTag();
				szDescription = pDatabaseTMParameter->GetDescription();
				for (szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERITEMTEXT), (LPCTSTR)szDescription, (LPCTSTR)szName[0]); szDescription.IsEmpty(); )
				{
					szName[1] = szName[0];
					break;
				}
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))))
				{
					if ((hTMParameterItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL, WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL, sFolderItem.hItem, (!hTMParameterItem[0]) ? TVI_FIRST : hTMParameterItem[0])))
					{
						if (m_wndView.SetItemData(hTMParameterItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hTMParameterItem[0] = hTMParameterItem[1];
							continue;
						}
						m_wndView.DeleteItem(hTMParameterItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hTMParameterItem[1] = m_wndView.GetNextItem(hTMParameterItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hTMParameterItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] = nParameter;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumTCParameters(HTREEITEM hParentItem)
{
	INT  nParameter;
	INT  nParameters;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szName[2];
	CString  szDescription;
	HTREEITEM  hTCParameterItem[2];
	CDatabaseTCParameter  *pDatabaseTCParameter;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindTCParameterFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nParameter = 0, nParameters = m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] = (INT)GetDatabase()->GetTCParameters()->GetSize(), hTCParameterItem[0] = hTCParameterItem[1] = (HTREEITEM)NULL; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTCParameter = GetDatabase()->GetTCParameters()->GetAt(nParameter)))
			{
				szName[0] = pDatabaseTCParameter->GetTag();
				szDescription = pDatabaseTCParameter->GetDescription();
				for (szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERITEMTEXT), (LPCTSTR)szDescription, (LPCTSTR)szName[0]); szDescription.IsEmpty(); )
				{
					szName[1] = szName[0];
					break;
				}
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))))
				{
					if ((hTCParameterItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL, WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL, sFolderItem.hItem, (!hTCParameterItem[0]) ? TVI_FIRST : hTCParameterItem[0])))
					{
						if (m_wndView.SetItemData(hTCParameterItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hTCParameterItem[0] = hTCParameterItem[1];
							continue;
						}
						m_wndView.DeleteItem(hTCParameterItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hTCParameterItem[1] = m_wndView.GetNextItem(hTCParameterItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hTCParameterItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] = nParameter;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumOBProcessors(HTREEITEM hParentItem)
{
	INT  nProcessor;
	INT  nProcessors;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szName[2];
	CString  szDescription;
	HTREEITEM  hOBProcessorItem[2];
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindOBProcessorFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nProcessor = 0, nProcessors = m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] = (INT)GetDatabase()->GetOBProcessors()->GetSize(), hOBProcessorItem[0] = hOBProcessorItem[1] = (HTREEITEM)NULL; nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = GetDatabase()->GetOBProcessors()->GetAt(nProcessor)))
			{
				szName[0] = pDatabaseOBProcessor->GetName();
				szDescription = (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? pDatabaseOBProcessor->GetDescription() : pDatabaseOBProcessor->GetDetails();
				szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORITEMTEXT), (LPCTSTR)szName[0], (LPCTSTR)szDescription);
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))) != (LPTSTR)NULL)
				{
					if ((hOBProcessorItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL, WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL, sFolderItem.hItem, (!hOBProcessorItem[0]) ? TVI_FIRST : hOBProcessorItem[0])))
					{
						if (m_wndView.SetItemData(hOBProcessorItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hOBProcessorItem[0] = hOBProcessorItem[1];
							continue;
						}
						m_wndView.DeleteItem(hOBProcessorItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hOBProcessorItem[1] = m_wndView.GetNextItem(hOBProcessorItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hOBProcessorItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] = nProcessor;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumANDs(HTREEITEM hParentItem)
{
	INT  nDisplay;
	INT  nDisplays;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szTitle;
	CString  szName[2];
	HTREEITEM  hANDItem[2];
	CANDLayout  *pANDLayout;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindANDFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nDisplay = 0, nDisplays = m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] = (INT)GetDatabase()->GetANDs()->GetSize(), hANDItem[0] = hANDItem[1] = (HTREEITEM)NULL; nDisplay < nDisplays; nDisplay++)
		{
			if ((pANDLayout = GetDatabase()->GetANDs()->GetAt(nDisplay)))
			{
				szName[0] = pANDLayout->GetName();
				szTitle = pANDLayout->GetTitle();
				for (szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDITEMTEXT), (LPCTSTR)szTitle, (LPCTSTR)szName[0]); szTitle.IsEmpty(); )
				{
					szName[1] = szName[0];
					break;
				}
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))))
				{
					if ((hANDItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_ANDSYMBOL, WORKSPACEDATABASEPAGE_ANDSYMBOL, sFolderItem.hItem, (!hANDItem[0]) ? TVI_FIRST : hANDItem[0])))
					{
						if (m_wndView.SetItemData(hANDItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hANDItem[0] = hANDItem[1];
							continue;
						}
						m_wndView.DeleteItem(hANDItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hANDItem[1] = m_wndView.GetNextItem(hANDItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hANDItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] = nDisplay;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumGRDs(HTREEITEM hParentItem)
{
	INT  nDisplay;
	INT  nDisplays;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szTitle;
	CString  szName[2];
	HTREEITEM  hGRDItem[2];
	CGRDLayout  *pGRDLayout;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindGRDFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nDisplay = 0, nDisplays = m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] = (INT)GetDatabase()->GetGRDs()->GetSize(), hGRDItem[0] = hGRDItem[1] = (HTREEITEM)NULL; nDisplay < nDisplays; nDisplay++)
		{
			if ((pGRDLayout = GetDatabase()->GetGRDs()->GetAt(nDisplay)))
			{
				szName[0] = pGRDLayout->GetName();
				szTitle = pGRDLayout->GetTitle();
				for (szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDITEMTEXT), (LPCTSTR)szTitle, (LPCTSTR)szName[0]); szTitle.IsEmpty(); )
				{
					szName[1] = szName[0];
					break;
				}
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))))
				{
					if ((hGRDItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_GRDSYMBOL, WORKSPACEDATABASEPAGE_GRDSYMBOL, sFolderItem.hItem, (!hGRDItem[0]) ? TVI_FIRST : hGRDItem[0])))
					{
						if (m_wndView.SetItemData(hGRDItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hGRDItem[0] = hGRDItem[1];
							continue;
						}
						m_wndView.DeleteItem(hGRDItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hGRDItem[1] = m_wndView.GetNextItem(hGRDItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hGRDItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] = nDisplay;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumMMDs(HTREEITEM hParentItem)
{
	INT  nDisplay;
	INT  nDisplays;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szTitle;
	CString  szName[2];
	HTREEITEM  hMMDItem[2];
	CMMDLayout  *pMMDLayout;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindMMDFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nDisplay = 0, nDisplays = m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] = (INT)GetDatabase()->GetMMDs()->GetSize(), hMMDItem[0] = hMMDItem[1] = (HTREEITEM)NULL; nDisplay < nDisplays; nDisplay++)
		{
			if ((pMMDLayout = GetDatabase()->GetMMDs()->GetAt(nDisplay)))
			{
				szName[0] = pMMDLayout->GetName();
				szTitle = pMMDLayout->GetTitle();
				for (szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDITEMTEXT), (LPCTSTR)szTitle, (LPCTSTR)szName[0]); szTitle.IsEmpty(); )
				{
					szName[1] = szName[0];
					break;
				}
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))))
				{
					if ((hMMDItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_MMDSYMBOL, WORKSPACEDATABASEPAGE_MMDSYMBOL, sFolderItem.hItem, (!hMMDItem[0]) ? TVI_FIRST : hMMDItem[0])))
					{
						if (m_wndView.SetItemData(hMMDItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hMMDItem[0] = hMMDItem[1];
							continue;
						}
						m_wndView.DeleteItem(hMMDItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hMMDItem[1] = m_wndView.GetNextItem(hMMDItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hMMDItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] = nDisplay;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumPODs(HTREEITEM hParentItem)
{
	INT  nDisplay;
	INT  nDisplays;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szTitle;
	CString  szName[2];
	HTREEITEM  hPODItem[2];
	CPODLayout  *pPODLayout;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindPODFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nDisplay = 0, nDisplays = m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] = (INT)GetDatabase()->GetPODs()->GetSize(), hPODItem[0] = hPODItem[1] = (HTREEITEM)NULL; nDisplay < nDisplays; nDisplay++)
		{
			if ((pPODLayout = GetDatabase()->GetPODs()->GetAt(nDisplay)))
			{
				szName[0] = pPODLayout->GetName();
				szTitle = pPODLayout->GetTitle();
				for (szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODITEMTEXT), (LPCTSTR)szTitle, (LPCTSTR)szName[0]); szTitle.IsEmpty(); )
				{
					szName[1] = szName[0];
					break;
				}
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))))
				{
					if ((hPODItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_PODSYMBOL, WORKSPACEDATABASEPAGE_PODSYMBOL, sFolderItem.hItem, (!hPODItem[0]) ? TVI_FIRST : hPODItem[0])))
					{
						if (m_wndView.SetItemData(hPODItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hPODItem[0] = hPODItem[1];
							continue;
						}
						m_wndView.DeleteItem(hPODItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hPODItem[1] = m_wndView.GetNextItem(hPODItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hPODItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] = nDisplay;
		break;
	}
}

VOID CWorkspaceViewDatabasePage::EnumScripts(HTREEITEM hParentItem)
{
	INT  nScript;
	INT  nScripts;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szTitle;
	CString  szName[2];
	HTREEITEM  hScriptItem[2];
	CAutomationScript  *pScript;

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindScriptFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nScript = 0, nScripts = m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] = (INT)GetDatabase()->GetScripts()->GetSize(), hScriptItem[0] = hScriptItem[1] = (HTREEITEM)NULL; nScript < nScripts; nScript++)
		{
			if ((pScript = GetDatabase()->GetScripts()->GetAt(nScript)))
			{
				szName[0] = pScript->GetName();
				szTitle = pScript->GetTitle();
				for (szName[1].Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTITEMTEXT), (LPCTSTR)szTitle, (LPCTSTR)szName[0]); szTitle.IsEmpty(); )
				{
					szName[1] = szName[0];
					break;
				}
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (szName[0].GetLength() + 1)*sizeof(TCHAR))))
				{
					if ((hScriptItem[1] = m_wndView.InsertItem(szName[1], WORKSPACEDATABASEPAGE_SCRIPTSYMBOL, WORKSPACEDATABASEPAGE_SCRIPTSYMBOL, sFolderItem.hItem, (!hScriptItem[0]) ? TVI_FIRST : hScriptItem[0])))
					{
						if (m_wndView.SetItemData(hScriptItem[1], (DWORD_PTR)lstrcpy(pszName, szName[0])))
						{
							hScriptItem[0] = hScriptItem[1];
							continue;
						}
						m_wndView.DeleteItem(hScriptItem[1]);
					}
					GlobalFree(pszName);
				}
			}
			break;
		}
		while ((hScriptItem[1] = m_wndView.GetNextItem(hScriptItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hScriptItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] = nScript;
		break;
	}
}

HTREEITEM CWorkspaceViewDatabasePage::FindTMPacketFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindTCFunctionFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindTMParameterFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindTCParameterFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindOBProcessorFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindANDFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindGRDFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindMMDFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindPODFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindScriptFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewDatabasePage::FindFolder(LPCTSTR pszFolder) CONST
{
	HTREEITEM  hFolderItem;

	for (hFolderItem = m_wndView.GetChildItem(m_wndView.GetRootItem()); hFolderItem; hFolderItem = m_wndView.GetNextItem(hFolderItem, TVGN_NEXT))
	{
		if (m_wndView.GetItemText(hFolderItem) == pszFolder) break;
		continue;
	}
	return hFolderItem;
}

BOOL CWorkspaceViewDatabasePage::FindTMPacketItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindTCFunctionItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindTMParameterItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindTCParameterItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindOBProcessorItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindANDItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindGRDItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindMMDItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindPODItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindScriptItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTSYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewDatabasePage::FindItem(LPCTSTR pszItem, HTREEITEM hItem) CONST
{
	INT  nPosition;
	HTREEITEM  hChildItem;
	HTREEITEM  hFolderItem;

	if (!m_wndView.ItemHasChildren(hItem))
	{
		if ((hFolderItem = m_wndView.GetParentItem(hItem)) && m_wndView.GetItemText(hFolderItem) == pszItem)
		{
			for (hChildItem = m_wndView.GetChildItem(hFolderItem), nPosition = 0; hChildItem != (HTREEITEM)NULL; hChildItem = m_wndView.GetNextItem(hChildItem, TVGN_NEXT), nPosition++)
			{
				if (hChildItem == hItem) break;
				continue;
			}
			return((hChildItem != (HTREEITEM)NULL) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateTMPacket()
{
	CTMPacketWnd  *pTMPacketWnd;

	return(((pTMPacketWnd = new CTMPacketWnd) && pTMPacketWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenTMPacket(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTMPacketWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET) ? (CTMPacketWnd *)pDisplayWnd : (CTMPacketWnd *)NULL) && pTMPacketWnd->GetName() == szName)
		{
			pTMPacketWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pTMPacketWnd = new CTMPacketWnd(szName))) ? pTMPacketWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameTMPacket(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameTMPacket(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTMPacketWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET) ? (CTMPacketWnd *)pDisplayWnd : (CTMPacketWnd *)NULL) && pTMPacketWnd->GetName() == szName)
		{
			szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETITEMTEXT), pszItem, (LPCTSTR)szName);
			pTMPacketWnd->SetTitle(pszItem);
			nCount++;
		}
	}
	return((nCount > 0) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::DeleteTMPacket(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->DeleteTMPacket((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
			{
				pDisplayWnd->UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
				continue;
			}
		}
		m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateTCFunction()
{
	CTCFunctionWnd  *pTCFunctionWnd;

	return(((pTCFunctionWnd = new CTCFunctionWnd) && pTCFunctionWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenTCFunction(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCFunctionWnd  *pTCFunctionWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCFunctionWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION) ? (CTCFunctionWnd *)pDisplayWnd : (CTCFunctionWnd *)NULL) && pTCFunctionWnd->GetName() == szName)
		{
			pTCFunctionWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pTCFunctionWnd = new CTCFunctionWnd(szName))) ? pTCFunctionWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameTCFunction(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameTCFunction(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCFunctionWnd  *pTCFunctionWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCFunctionWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION) ? (CTCFunctionWnd *)pDisplayWnd : (CTCFunctionWnd *)NULL) && pTCFunctionWnd->GetName() == szName)
		{
			szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONITEMTEXT), pszItem, (LPCTSTR)szName);
			pTCFunctionWnd->SetTitle(pszItem);
			nCount++;
		}
	}
	return((nCount > 0) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::DeleteTCFunction(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->DeleteTCFunction((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
			{
				pDisplayWnd->UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
				continue;
			}
		}
		m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateTMParameter()
{
	CTMParameterWnd  *pTMParameterWnd;

	return(((pTMParameterWnd = new CTMParameterWnd) && pTMParameterWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenTMParameter(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMParameterWnd  *pTMParameterWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTMParameterWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER) ? (CTMParameterWnd *)pDisplayWnd : (CTMParameterWnd *)NULL) && pTMParameterWnd->GetName() == szName)
		{
			pTMParameterWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pTMParameterWnd = new CTMParameterWnd(szName))) ? pTMParameterWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameTMParameter(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameTMParameter(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMParameterWnd  *pTMParameterWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTMParameterWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER) ? (CTMParameterWnd *)pDisplayWnd : (CTMParameterWnd *)NULL) && pTMParameterWnd->GetName() == szName)
		{
			szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERITEMTEXT), pszItem, (LPCTSTR)szName);
			pTMParameterWnd->SetTitle(pszItem);
			nCount++;
		}
	}
	return((nCount > 0) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::DeleteTMParameter(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->DeleteTMParameter((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
			{
				pDisplayWnd->UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
				continue;
			}
		}
		m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateTCParameter()
{
	CTCParameterWnd  *pTCParameterWnd;

	return(((pTCParameterWnd = new CTCParameterWnd) && pTCParameterWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenTCParameter(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCParameterWnd  *pTCParameterWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCParameterWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER) ? (CTCParameterWnd *)pDisplayWnd : (CTCParameterWnd *)NULL) && pTCParameterWnd->GetName() == szName)
		{
			pTCParameterWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pTCParameterWnd = new CTCParameterWnd(szName))) ? pTCParameterWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameTCParameter(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameTCParameter(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCParameterWnd  *pTCParameterWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCParameterWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER) ? (CTCParameterWnd *)pDisplayWnd : (CTCParameterWnd *)NULL) && pTCParameterWnd->GetName() == szName)
		{
			szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERITEMTEXT), pszItem, (LPCTSTR)szName);
			pTCParameterWnd->SetTitle(pszItem);
			nCount++;
		}
	}
	return((nCount > 0) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::DeleteTCParameter(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->DeleteTCParameter((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
			{
				pDisplayWnd->UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
				continue;
			}
		}
		m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateOBProcessor()
{
	COBProcessorWnd  *pOBProcessorWnd;

	return(((pOBProcessorWnd = new COBProcessorWnd) && pOBProcessorWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenOBProcessor(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pOBProcessorWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR) ? (COBProcessorWnd *)pDisplayWnd : (COBProcessorWnd *)NULL) && pOBProcessorWnd->GetName() == szName)
		{
			pOBProcessorWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pOBProcessorWnd = new COBProcessorWnd(szName))) ? pOBProcessorWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameOBProcessor(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameOBProcessor(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	COBProcessorWnd  *pOBProcessorWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pOBProcessorWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR) ? (COBProcessorWnd *)pDisplayWnd : (COBProcessorWnd *)NULL) && pOBProcessorWnd->GetName() == szName)
		{
			szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORITEMTEXT), pszItem, (LPCTSTR)szName);
			pOBProcessorWnd->SetTitle(pszItem);
			nCount++;
		}
	}
	return((nCount > 0) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::DeleteOBProcessor(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->DeleteOBProcessor((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
			{
				pDisplayWnd->UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
				continue;
			}
		}
		m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateAND()
{
	CANDWnd  *pANDWnd;

	return(((pANDWnd = new CANDWnd) && pANDWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenAND(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CANDWnd  *pANDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pANDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND) ? (CANDWnd *)pDisplayWnd : (CANDWnd *)NULL) && pANDWnd->GetName() == szName)
		{
			pANDWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pANDWnd = new CANDWnd(szName))) ? pANDWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameAND(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameAND(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CANDWnd  *pANDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
		{
			if ((pANDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND) ? (CANDWnd *)pDisplayWnd : (CANDWnd *)NULL) && pANDWnd->GetName() == szName)
			{
				for (szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
				{
					szItem = szName;
					break;
				}
				pANDWnd->SetTitle(pszItem);
				nCount++;
			}
		}
		return((nCount > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::DeleteAND(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CANDWnd  *pANDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND))
	{
		if (GetDatabase()->DeleteAND((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
		{
			for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
			{
				if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
				{
					pDisplayWnd->UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
					continue;
				}
			}
			m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] - 1, 0);
			return TRUE;
		}
		return FALSE;
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pANDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND) ? (CANDWnd *)pDisplayWnd : (CANDWnd *)NULL) && pANDWnd->GetName() == szName)
		{
			pANDWnd->DestroyWindow();
			break;
		}
	}
	if (CANDWnd::Delete(szName) >= 0 && m_wndView.DeleteItem(hItem))
	{
		m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateGRD()
{
	CGRDWnd  *pGRDWnd;

	return(((pGRDWnd = new CGRDWnd) && pGRDWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenGRD(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CGRDWnd  *pGRDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pGRDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD) ? (CGRDWnd *)pDisplayWnd : (CGRDWnd *)NULL) && pGRDWnd->GetName() == szName)
		{
			pGRDWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pGRDWnd = new CGRDWnd(szName))) ? pGRDWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameGRD(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameGRD(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CGRDWnd  *pGRDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
		{
			if ((pGRDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD) ? (CGRDWnd *)pDisplayWnd : (CGRDWnd *)NULL) && pGRDWnd->GetName() == szName)
			{
				for (szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
				{
					szItem = szName;
					break;
				}
				pGRDWnd->SetTitle(pszItem);
				nCount++;
			}
		}
		return((nCount > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::DeleteGRD(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CGRDWnd  *pGRDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD))
	{
		if (GetDatabase()->DeleteGRD((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
		{
			for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
			{
				if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
				{
					pDisplayWnd->UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
					continue;
				}
			}
			m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] - 1, 0);
			return TRUE;
		}
		return FALSE;
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pGRDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD) ? (CGRDWnd *)pDisplayWnd : (CGRDWnd *)NULL) && pGRDWnd->GetName() == szName)
		{
			pGRDWnd->DestroyWindow();
			break;
		}
	}
	if (CGRDWnd::Delete(szName) >= 0 && m_wndView.DeleteItem(hItem))
	{
		m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateMMD()
{
	CMMDWnd  *pMMDWnd;

	return(((pMMDWnd = new CMMDWnd) && pMMDWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenMMD(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CMMDWnd  *pMMDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && _ttoi(pMMDWnd->GetName()) == _ttoi(szName))
		{
			pMMDWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pMMDWnd = new CMMDWnd(szName))) ? pMMDWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameMMD(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameMMD(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CMMDWnd  *pMMDWnd;
	CPtrArray  pDisplays;
	CMMDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && _ttoi(pMMDWnd->GetName()) == _ttoi(szName))
		{
			for (szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
			{
				szItem = szName;
				break;
			}
			pMMDWnd->SetTitle(pszItem);
			break;
		}
	}
	if (GetDatabase()->LoadMMD(szName, cLayout))
	{
		for (cLayout.SetTitle(pszItem), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
		{
			szItem = szName;
			break;
		}
		return((GetDatabase()->SaveMMD(cLayout) >= 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::DeleteMMD(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CMMDWnd  *pMMDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && _ttoi(pMMDWnd->GetName()) == _ttoi(szName))
		{
			pMMDWnd->DestroyWindow();
			break;
		}
	}
	if (CMMDWnd::Delete(szName) >= 0 && m_wndView.DeleteItem(hItem))
	{
		m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreatePOD()
{
	CPODWnd  *pPODWnd;

	return(((pPODWnd = new CPODWnd) && pPODWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenPOD(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPODWnd  *pPODWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pPODWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD) ? (CPODWnd *)pDisplayWnd : (CPODWnd *)NULL) && pPODWnd->GetName() == szName)
		{
			pPODWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pPODWnd = new CPODWnd(szName))) ? pPODWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenamePOD(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenamePOD(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPODWnd  *pPODWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
		{
			if ((pPODWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD) ? (CPODWnd *)pDisplayWnd : (CPODWnd *)NULL) && pPODWnd->GetName() == szName)
			{
				for (szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
				{
					szItem = szName;
					break;
				}
				pPODWnd->SetTitle(pszItem);
				nCount++;
			}
		}
		return((nCount > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::DeletePOD(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPODWnd  *pPODWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD))
	{
		if (GetDatabase()->DeletePOD((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
		{
			for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
			{
				if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
				{
					pDisplayWnd->UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
					continue;
				}
			}
			m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] - 1, 0);
			return TRUE;
		}
		return FALSE;
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pPODWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD) ? (CPODWnd *)pDisplayWnd : (CPODWnd *)NULL) && pPODWnd->GetName() == szName)
		{
			pPODWnd->DestroyWindow();
			break;
		}
	}
	if (CPODWnd::Delete(szName) >= 0 && m_wndView.DeleteItem(hItem))
	{
		m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::CreateScript()
{
	CScriptWnd  *pScriptWnd;

	return(((pScriptWnd = new CScriptWnd) && pScriptWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewDatabasePage::OpenScript(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pScriptWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT) ? (CScriptWnd *)pDisplayWnd : (CScriptWnd *)NULL) && _ttoi(pScriptWnd->GetName()) == _ttoi(szName))
		{
			pScriptWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pScriptWnd = new CScriptWnd(szName))) ? pScriptWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewDatabasePage::RenameScript(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewDatabasePage::RenameScript(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CAutomationScript  cScript;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pScriptWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT) ? (CScriptWnd *)pDisplayWnd : (CScriptWnd *)NULL) && _ttoi(pScriptWnd->GetName()) == _ttoi(szName))
		{
			for (szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
			{
				szItem = szName;
				break;
			}
			pScriptWnd->SetTitle(pszItem);
			break;
		}
	}
	if (GetDatabase()->LoadScript(szName, cScript))
	{
		for (cScript.SetTitle(pszItem), szItem.Format(STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
		{
			szItem = szName;
			break;
		}
		return((GetDatabase()->SaveScript(cScript) >= 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::DeleteScript(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pScriptWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT) ? (CScriptWnd *)pDisplayWnd : (CScriptWnd *)NULL) && _ttoi(pScriptWnd->GetName()) == _ttoi(szName))
		{
			pScriptWnd->DestroyWindow();
			break;
		}
	}
	if (CScriptWnd::Delete(szName) >= 0 && m_wndView.DeleteItem(hItem))
	{
		m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] = max(m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewDatabasePage::IsDraggingDatabaseItem() CONST
{
	return(m_nDragItem != 0);
}

BEGIN_MESSAGE_MAP(CWorkspaceViewDatabasePage, CWorkspaceViewPage)
	//{{AFX_MSG_MAP(CWorkspaceViewDatabasePage)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePage message handlers

int CWorkspaceViewDatabasePage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	BITMAP  sBitmap;
	CBitmap  cBitmap[WORKSPACEDATABASEPAGE_SYMBOLS];

	if (CWorkspaceViewPage::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndView.Create(TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS | TVS_NOTOOLTIPS | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0))
		{
			if (cBitmap[WORKSPACEDATABASEPAGE_ROOTSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEROOTSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_ROOTNOSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEROOTNOSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_FOLDERSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEFOLDERSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_FOLDEROPENSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEFOLDEROPENSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGETMPACKETSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGETCFUNCTIONSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGETMPARAMETERSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGETCPARAMETERSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEOBPROCESSORSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_ANDSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEANDSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_GRDSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEGRDSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_MMDSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEMMDSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_PODSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGEPODSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL].LoadBitmap(IDB_WORKSPACEDATABASEPAGESCRIPTSYMBOL) && cBitmap[WORKSPACEDATABASEPAGE_ROOTSYMBOL].GetObject(sizeof(BITMAP), &sBitmap) > 0)
			{
				if (m_pItems.Create(sBitmap.bmWidth, sBitmap.bmHeight, ILC_COLOR32, WORKSPACEDATABASEPAGE_SYMBOLS, 1))
				{
					if (m_cDragItem.Create(sBitmap.bmWidth, sBitmap.bmHeight, ILC_COLOR32, 1, 1))
					{
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_ROOTSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_ROOTNOSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_FOLDERSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_FOLDEROPENSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_ANDSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_GRDSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_MMDSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_PODSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL], (CBitmap *)NULL);
						if (m_pItems.GetImageCount() == WORKSPACEDATABASEPAGE_SYMBOLS)
						{
							m_wndView.SetImageList(&m_pItems, TVSIL_NORMAL);
							return 0;
						}
						m_cDragItem.DeleteImageList();
					}
					m_pItems.DeleteImageList();
				}
			}
		}
	}
	return -1;
}

void CWorkspaceViewDatabasePage::OnSize(UINT nType, int cx, int cy)
{
	m_wndView.MoveWindow(0, 0, cx, cy);
	CWorkspaceViewPage::OnSize(nType, cx, cy);
}

BOOL CWorkspaceViewDatabasePage::OnEraseBkgnd(CDC *pDC)
{
	CRect  rPage[2];

	for (GetWindowRect(rPage[0]), GetParent()->ScreenToClient(rPage[0]), GetParent()->CalcClientRect(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		MoveWindow(rPage[1]);
		return TRUE;
	}
	for (GetClientRect(rPage[0]), m_wndView.GetWindowRect(rPage[1]), GetParent()->ScreenToClient(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		m_wndView.MoveWindow(rPage[0], FALSE);
		m_wndView.RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
		return TRUE;
	}
	return CWorkspaceViewPage::OnEraseBkgnd(pDC);
}

void CWorkspaceViewDatabasePage::OnPaint()
{
	m_wndView.UpdateWindow();
	CWorkspaceViewPage::OnPaint();
}

void CWorkspaceViewDatabasePage::OnSetFocus(CWnd *pOldWnd)
{
	m_wndView.SetFocus();
}

void CWorkspaceViewDatabasePage::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd  *pWnd[2];
	CPoint  ptDrag;
	CDisplayWnd  *pDisplayWnd;

	for (ptDrag = point, ClientToScreen(&ptDrag); IsDraggingDatabaseItem(); )
	{
		if ((pWnd[0] = WindowFromPoint(ptDrag)) != (CWnd *)NULL)
		{
			while (!pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pWnd[1] = pWnd[0]->GetParent()))
				{
					pWnd[0] = pWnd[1];
					continue;
				}
				break;
			}
			if (IsWindow(pWnd[0]->GetSafeHwnd()) && pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pDisplayWnd = (CDisplayWnd *)pWnd[0])->CheckTableDropTarget(m_szDragItem, m_nDragItem, ptDrag))
				{
					if (m_bDragItem)
					{
						m_cDragItem.DragMove(ptDrag);
						break;
					}
					ShowCursor(FALSE);
					m_cDragItem.DragEnter((CWnd *)NULL, ptDrag);
					m_bDragItem = TRUE;
					break;
				}
				if (m_bDragItem)
				{
					ShowCursor(TRUE);
					m_cDragItem.DragLeave((CWnd *)NULL);
					m_bDragItem = FALSE;
				}
				SetCursor(LoadCursor((HINSTANCE)NULL, IDC_NO));
				break;
			}
		}
		if (m_bDragItem)
		{
			m_cDragItem.DragMove(ptDrag);
			break;
		}
		ShowCursor(FALSE);
		m_cDragItem.DragEnter((CWnd *)NULL, ptDrag);
		m_bDragItem = TRUE;
		break;
	}
	CWorkspaceViewPage::OnMouseMove(nFlags, point);
}

void CWorkspaceViewDatabasePage::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd  *pWnd[2];
	CPoint  ptDrag;
	CDisplayWnd  *pDisplayWnd;

	for (ptDrag = point, ClientToScreen(&ptDrag); IsDraggingDatabaseItem(); )
	{
		if ((pWnd[0] = WindowFromPoint(ptDrag)) != (CWnd *)NULL)
		{
			while (!pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pWnd[1] = pWnd[0]->GetParent()))
				{
					pWnd[0] = pWnd[1];
					continue;
				}
				break;
			}
			if (IsWindow(pWnd[0]->GetSafeHwnd()) && pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pDisplayWnd = (CDisplayWnd *)pWnd[0]) && pDisplayWnd->CheckTableDropTarget(m_szDragItem, m_nDragItem, ptDrag))
				{
					for (m_cDragItem.EndDrag(); m_bDragItem; )
					{
						m_bDragItem = FALSE;
						ShowCursor(TRUE);
						break;
					}
					pDisplayWnd->DropOnTableTarget(m_szDragItem, m_nDragItem, ptDrag);
					m_szDragItem.Empty();
					m_nDragItem = 0;
					ReleaseCapture();
					break;
				}
			}
		}
		for (m_cDragItem.EndDrag(); m_bDragItem; )
		{
			m_bDragItem = FALSE;
			ShowCursor(TRUE);
			break;
		}
		m_szDragItem.Empty();
		m_nDragItem = 0;
		ReleaseCapture();
		break;
	}
	CWorkspaceViewPage::OnLButtonUp(nFlags, point);
}

BOOL CWorkspaceViewDatabasePage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rItem;
	CRect  rView;
	CRect  rResult;
	CEdit  *pEdit;
	LPVOID  pData;
	CPoint  ptDrag;
	CPoint  ptCursor;
	CBitmap  cBitmap;
	CString  szItem;
	CString  szMessage;
	NMMOUSE  *pNotifyMouseInfo = (NMMOUSE *)lParam;
	NMTREEVIEW  *pNotifyTreeInfo = (NMTREEVIEW *)lParam;
	NMTVKEYDOWN  *pNotifyKeyInfo = (NMTVKEYDOWN *)lParam;
	NMTVDISPINFO  *pNotifyDispInfo = (NMTVDISPINFO *)lParam;

	GetCursorPos(&ptCursor);
	ScreenToClient(&ptCursor);
	m_wndView.GetClientRect(rView);
	if (pNotifyMouseInfo->hdr.code == NM_SETCURSOR)
	{
		if (m_wndView.GetItemRect((HTREEITEM)pNotifyMouseInfo->dwItemSpec, rItem, TRUE))
		{
			if (rResult.IntersectRect(rView, rItem) && !rResult.EqualRect(rItem) && rItem.PtInRect(ptCursor))
			{
				for (m_wndView.ClientToScreen(rItem), szItem = m_wndView.GetItemText((HTREEITEM)pNotifyMouseInfo->dwItemSpec); !szItem.IsEmpty(); )
				{
					m_wndToolTip.ShowTip(&m_wndView, szItem, rItem, (m_wndView.GetRootItem() == (HTREEITEM)pNotifyMouseInfo->dwItemSpec) ? TRUE : FALSE);
					return FALSE;
				}
			}
		}
		m_wndToolTip.DeleteTip();
		return FALSE;
	}
	if ((pNotifyKeyInfo->hdr.code == TVN_KEYDOWN  &&  pNotifyKeyInfo->wVKey == VK_RETURN) || pNotifyMouseInfo->hdr.code == NM_DBLCLK)
	{
		if (FindTMPacketItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenTMPacket(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_TMPACKET_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindTCFunctionItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenTCFunction(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindTMParameterItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenTMParameter(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindTCParameterItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenTCParameter(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindOBProcessorItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenOBProcessor(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindANDItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenAND(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_AND_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindGRDItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenGRD(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_GRD_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindMMDItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenMMD(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_MMD_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindPODItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenPOD(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_POD_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindScriptItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenScript(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_SCRIPT_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
	}
	if (pNotifyKeyInfo->hdr.code == TVN_KEYDOWN)
	{
		if (pNotifyKeyInfo->wVKey == VK_DECIMAL)
		{
			if (!IsCompiling())
			{
				DeleteDatabaseItem();
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (pNotifyKeyInfo->wVKey == VK_ESCAPE)
		{
			GetTopLevelParent()->SetFocus();
			*pResult = TRUE;
			return TRUE;
		}
	}
	if (pNotifyDispInfo->hdr.code == TVN_GETDISPINFO)
	{
		if ((szItem = m_wndView.GetItemText(pNotifyDispInfo->item.hItem)) == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTSYMBOLTEXT))
		{
			if (pNotifyDispInfo->item.mask & TVIF_IMAGE) pNotifyDispInfo->item.iImage = ((m_wndView.GetItemState(pNotifyDispInfo->item.hItem, TVIF_STATE) & TVIS_EXPANDED) && m_wndView.ItemHasChildren(pNotifyDispInfo->item.hItem)) ? WORKSPACEDATABASEPAGE_FOLDEROPENSYMBOL : WORKSPACEDATABASEPAGE_FOLDERSYMBOL;
			if (pNotifyDispInfo->item.mask & TVIF_SELECTEDIMAGE) pNotifyDispInfo->item.iSelectedImage = ((m_wndView.GetItemState(pNotifyDispInfo->item.hItem, TVIF_STATE) & TVIS_EXPANDED) && m_wndView.ItemHasChildren(pNotifyDispInfo->item.hItem)) ? WORKSPACEDATABASEPAGE_FOLDEROPENSYMBOL : WORKSPACEDATABASEPAGE_FOLDERSYMBOL;
		}
		if (pNotifyDispInfo->item.mask & TVIF_CHILDREN)
		{
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPACKETSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_TMPACKETSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCFUNCTIONSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TMPARAMETERSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_TCPARAMETERSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_OBPROCESSORSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_ANDSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_ANDSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_GRDSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_GRDSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_MMDSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_MMDSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_PODSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_PODSYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_DATABASEPAGE_SCRIPTSYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEDATABASEPAGE_SCRIPTSYMBOL] > 0) ? TRUE : FALSE;
		}
	}
	if (pNotifyDispInfo->hdr.code == TVN_BEGINLABELEDIT)
	{
		if (((!FindTMPacketItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE)) && (!FindTCFunctionItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE)) && (!FindTMParameterItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE)) && (!FindTCParameterItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE)) && (!FindANDItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE)) && (!FindGRDItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE)) && (!FindMMDItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE)) && (!FindPODItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_POD_CHANGE)) && (!FindScriptItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE))) && !IsCompiling())
		{
			*pResult = TRUE;
			return TRUE;
		}
		if ((pEdit = m_wndView.GetEditControl()))
		{
			for (szItem = m_wndView.GetItemText(pNotifyDispInfo->item.hItem); !szItem.IsEmpty(); )
			{
				if (!_istspace(szItem[szItem.GetLength() - 1]))
				{
					szItem = szItem.Left(szItem.GetLength() - 1);
					continue;
				}
				szItem = szItem.Left(szItem.GetLength() - 1);
				break;
			}
			pEdit->SetWindowText(szItem);
		}
	}
	if (pNotifyDispInfo->hdr.code == TVN_ENDLABELEDIT)
	{
		if (AfxIsValidString(pNotifyDispInfo->item.pszText))
		{
			if (FindTMPacketItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameTMPacket(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_TMPACKETSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindTCFunctionItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameTCFunction(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindTMParameterItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameTMParameter(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindTCParameterItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameTCParameter(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindANDItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameAND(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_ANDSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindGRDItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameGRD(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_GRDSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindMMDItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameMMD(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_MMDSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindPODItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenamePOD(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_PODSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindScriptItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameScript(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEDATABASEPAGE_SCRIPTSYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
		}
	}
	if (pNotifyTreeInfo->hdr.code == TVN_BEGINDRAG)
	{
		for (m_nDragItem = DATABASE_COMPONENT_NONE, m_bDragItem = FALSE; FindTMPacketItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGETMPACKETSYMBOL)) ? DATABASE_COMPONENT_TMPACKET : m_nDragItem;
			break;
		}
		for (; FindTCFunctionItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGETCFUNCTIONSYMBOL)) ? DATABASE_COMPONENT_TCFUNCTION : m_nDragItem;
			break;
		}
		for (; FindTMParameterItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGETMPARAMETERSYMBOL)) ? DATABASE_COMPONENT_TMPARAMETER : m_nDragItem;
			break;
		}
		for (; FindTCParameterItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGETCPARAMETERSYMBOL)) ? DATABASE_COMPONENT_TCPARAMETER : m_nDragItem;
			break;
		}
		for (; FindOBProcessorItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGEOBPROCESSORSYMBOL)) ? DATABASE_COMPONENT_OBPROCESSOR : m_nDragItem;
			break;
		}
		for (; FindANDItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGEANDSYMBOL)) ? DATABASE_COMPONENT_AND : m_nDragItem;
			break;
		}
		for (; FindGRDItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGEGRDSYMBOL)) ? DATABASE_COMPONENT_GRD : m_nDragItem;
			break;
		}
		for (; FindMMDItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGEMMDSYMBOL)) ? DATABASE_COMPONENT_MMD : m_nDragItem;
			break;
		}
		for (; FindPODItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGEPODSYMBOL)) ? DATABASE_COMPONENT_POD : m_nDragItem;
			break;
		}
		for (; FindScriptItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEDATABASEPAGESCRIPTSYMBOL)) ? DATABASE_COMPONENT_SCRIPT : m_nDragItem;
			break;
		}
		if (m_nDragItem != DATABASE_COMPONENT_NONE)
		{
			if ((!m_cDragItem.GetImageCount() && !m_cDragItem.Add(&cBitmap, (CBitmap *)NULL)) || (m_cDragItem.GetImageCount() > 0 && m_cDragItem.Replace(0, &cBitmap, (CBitmap *)NULL)))
			{
				for (ptDrag = pNotifyTreeInfo->ptDrag, ClientToScreen(&ptDrag), m_wndView.SelectItem(pNotifyTreeInfo->itemNew.hItem); m_cDragItem.BeginDrag(0, CPoint(0, 0)) && m_cDragItem.DragEnter((CWnd *)NULL, ptDrag); )
				{
					m_szDragItem = (LPCTSTR)pNotifyTreeInfo->itemNew.lParam;
					m_bDragItem = TRUE;
					ShowCursor(FALSE);
					SetCapture();
					break;
				}
			}
			m_nDragItem = (m_bDragItem) ? m_nDragItem : DATABASE_COMPONENT_NONE;
		}
	}
	if (pNotifyTreeInfo->hdr.code == TVN_DELETEITEM)
	{
		if ((pData = (LPVOID)pNotifyTreeInfo->itemOld.lParam))
		{
			pNotifyTreeInfo->itemOld.lParam = 0;
			GlobalFree(pData);
		}
	}
	return CWorkspaceViewPage::OnNotify(wParam, lParam, pResult);
}

void CWorkspaceViewDatabasePage::OnTimer(UINT_PTR nEventID)
{
	KillTimer(m_nTimerID);
	m_wndView.SetItemText(m_hItem, m_szItem);
	m_hItem = (HTREEITEM)NULL;
	m_szItem.Empty();
	m_nTimerID = 0;
}

void CWorkspaceViewDatabasePage::OnDestroy()
{
	m_cDragItem.DeleteImageList();
	CWorkspaceViewPage::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPageToolTip

IMPLEMENT_DYNCREATE(CWorkspaceViewProceduresPageToolTip, CWnd)

CWorkspaceViewProceduresPageToolTip::CWorkspaceViewProceduresPageToolTip() : CWnd()
{
	m_szText.Empty();
	m_rText.SetRectEmpty();
	m_bBoldText = FALSE;
}

BOOL CWorkspaceViewProceduresPageToolTip::ShowTip(CWnd *pParentWnd, LPCTSTR pszText, CONST RECT &rect, BOOL bBold)
{
	if ((m_szText != pszText  &&  lstrlen(pszText) > 0) && !m_rText.EqualRect(&rect))
	{
		for (DeleteTip(); CWnd::CreateEx(0, AfxRegisterWndClass(CS_DBLCLKS | CS_SAVEBITS | CS_DROPSHADOW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), EMPTYSTRING, WS_POPUP | WS_BORDER, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, (m_pParentWnd = pParentWnd)->GetSafeHwnd(), (HMENU)NULL); )
		{
			SetTimer(WORKSPACEVIEWPROCEDURESPAGE_TOOLTIP_TIMERID, 0, NULL);
			m_bBoldText = bBold;
			m_szText = pszText;
			m_rText = rect;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CWorkspaceViewProceduresPageToolTip::DeleteTip()
{
	for (m_szText.Empty(), m_rText.SetRectEmpty(), m_bBoldText = FALSE; IsWindow(GetSafeHwnd()); )
	{
		KillTimer(WORKSPACEVIEWPROCEDURESPAGE_TOOLTIP_TIMERID);
		DestroyWindow();
		return TRUE;
	}
	return FALSE;
}

CWorkspaceViewProceduresPageTreeCtrl *CWorkspaceViewProceduresPageToolTip::GetParent() CONST
{
	return((CWorkspaceViewProceduresPageTreeCtrl *)m_pParentWnd);
}

VOID CWorkspaceViewProceduresPageToolTip::DrawContent(CDC *pDC)
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pFont;
	CFont  *pOldFont;
	CRect  rToolTip;
	LOGFONT  lfFont;

	for (GetClientRect(rToolTip); (pFont = GetParent()->GetFont()) && pFont->GetLogFont(&lfFont); )
	{
		if (cFont.CreateFont(lfFont.lfHeight, lfFont.lfWidth, lfFont.lfEscapement, lfFont.lfOrientation, (m_bBoldText) ? FW_BOLD : lfFont.lfWeight, lfFont.lfItalic, lfFont.lfUnderline, lfFont.lfStrikeOut, lfFont.lfCharSet, lfFont.lfOutPrecision, lfFont.lfClipPrecision, lfFont.lfQuality, lfFont.lfPitchAndFamily, lfFont.lfFaceName))
		{
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				nBkMode = pDC->SetBkMode(TRANSPARENT);
				pDC->DrawText(m_szText, CRect(GetSystemMetrics(SM_CXBORDER), 0, m_rText.Width(), m_rText.Height()), DT_LEFT | DT_TOP | DT_NOPREFIX);
				pDC->SelectObject(pOldFont);
				pDC->SetBkMode(nBkMode);
			}
			cFont.DeleteObject();
		}
		break;
	}
}

BEGIN_MESSAGE_MAP(CWorkspaceViewProceduresPageToolTip, CWnd)
	//{{AFX_MSG_MAP(CWorkspaceViewProceduresPageToolTip)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPageToolTip message handlers

BOOL CWorkspaceViewProceduresPageToolTip::OnEraseBkgnd(CDC *pDC)
{
	CRect  rToolTip;
	CBrush  cBkgndBrush;

	for (GetClientRect(rToolTip); cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK); )
	{
		pDC->FillRect(rToolTip, &cBkgndBrush);
		cBkgndBrush.DeleteObject();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CWorkspaceViewProceduresPageToolTip::OnPaint()
{
	CPaintDC  cDC(this);

	DrawContent(&cDC);
}

void CWorkspaceViewProceduresPageToolTip::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect  rToolTip;

	for (GetWindowRect(rToolTip), ScreenToClient(rToolTip); !rToolTip.PtInRect(point); )
	{
		DeleteTip();
		break;
	}
	SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	CWnd::OnMouseMove(nFlags, point);
}

void CWorkspaceViewProceduresPageToolTip::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->OpenProceduresItem(pt);
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CWorkspaceViewProceduresPageToolTip::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint  pt(point);

	ClientToScreen(&pt);
	GetParent()->ShowFloatingMenu(pt);
	CWnd::OnRButtonDown(nFlags, point);
}

void CWorkspaceViewProceduresPageToolTip::OnTimer(UINT_PTR nEventID)
{
	CPoint  ptCursor;

	if (nEventID == WORKSPACEVIEWPROCEDURESPAGE_TOOLTIP_TIMERID)
	{
		if (IsWindowVisible())
		{
			KillTimer(nEventID);
			ReleaseCapture();
			DestroyWindow();
			return;
		}
		for (GetCursorPos(&ptCursor); m_rText.PtInRect(ptCursor); )
		{
			SetTimer(WORKSPACEVIEWPROCEDURESPAGE_TOOLTIP_TIMERID, WORKSPACEVIEWPROCEDURESPAGE_TOOLTIP_TIMEOUT, NULL);
			ShowWindow(SW_SHOWNA);
			SetCapture();
			break;
		}
		if (!m_rText.PtInRect(ptCursor))
		{
			KillTimer(nEventID);
			DestroyWindow();
			return;
		}
	}
	CWnd::OnTimer(nEventID);
}

void CWorkspaceViewProceduresPageToolTip::OnDestroy()
{
	if (GetCapture()->GetSafeHwnd() == GetSafeHwnd()) ReleaseCapture();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPageTreeCtrl

IMPLEMENT_DYNCREATE(CWorkspaceViewProceduresPageTreeCtrl, CTreeCtrl)

CWorkspaceViewProceduresPageTreeCtrl::CWorkspaceViewProceduresPageTreeCtrl() : CTreeCtrl()
{
	return;
}

VOID CWorkspaceViewProceduresPageTreeCtrl::OpenProceduresItem(CONST POINT &ptItem)
{
	GetParent()->OpenProceduresItem(ptItem);
}

VOID CWorkspaceViewProceduresPageTreeCtrl::ShowFloatingMenu(CONST POINT &ptItem)
{
	GetParent()->ShowFloatingMenu(ptItem);
}

CWorkspaceViewProceduresPage *CWorkspaceViewProceduresPageTreeCtrl::GetParent() CONST
{
	return((CWorkspaceViewProceduresPage *)CTreeCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CWorkspaceViewProceduresPageTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CWorkspaceViewProceduresPageTreeCtrl)
	ON_WM_SETCURSOR()
	ON_WM_CHAR()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPageTreeCtrl message handlers

BOOL CWorkspaceViewProceduresPageTreeCtrl::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	CRect  rEdit;
	POINT  ptCursor;

	if (IsWindow(GetEditControl()->GetSafeHwnd()) && GetEditControl()->IsWindowVisible())
	{
		for (GetCursorPos(&ptCursor), GetEditControl()->GetWindowRect(rEdit); rEdit.PtInRect(ptCursor); )
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_IBEAM));
			return TRUE;
		}
	}
	return CTreeCtrl::OnSetCursor(pWnd, nHitTest, message);
}

void CWorkspaceViewProceduresPageTreeCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN || nChar == VK_ESCAPE) return;
	CTreeCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CWorkspaceViewProceduresPageTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect  rItem;
	CPoint  ptItem;
	HTREEITEM  hItem;

	for (hItem = GetFirstVisibleItem(); hItem != (HTREEITEM)NULL; hItem = GetNextVisibleItem(hItem))
	{
		if (GetItemRect(hItem, rItem, FALSE) && rItem.PtInRect(point))
		{
			ClientToScreen(&(ptItem = point));
			ShowFloatingMenu(ptItem);
			return;
		}
	}
	CTreeCtrl::OnRButtonDown(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPage

IMPLEMENT_DYNCREATE(CWorkspaceViewProceduresPage, CWorkspaceViewPage)

CWorkspaceViewProceduresPage::CWorkspaceViewProceduresPage() : CWorkspaceViewPage()
{
	m_hItem = (HTREEITEM)NULL;
	m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] = 0;
	m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] = 0;
	m_bDragItem = FALSE;
	m_nDragItem = 0;
	m_nTimerID = 0;
}

VOID CWorkspaceViewProceduresPage::UpdateDatabaseProcedures(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sTCSequenceItem[2];
	HTREEITEM  hTCSequenceItem;
	HTREEITEM  hTCSequenceFolder;

	if ((hTCSequenceFolder = FindTCSequenceFolder()))
	{
		for (hTCSequenceItem = m_wndView.GetChildItem(hTCSequenceFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCEITEMTEXT), (LPCTSTR)pDatabaseTCSequence->GetDescription(), (LPCTSTR)pDatabaseTCSequence->GetName()), szItem = (pDatabaseTCSequence->GetDescription().IsEmpty()) ? pDatabaseTCSequence->GetName() : szItem, nIndex = 0; hTCSequenceItem; hTCSequenceItem = m_wndView.GetNextItem(hTCSequenceItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pDatabaseTCSequence->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hTCSequenceItem = m_wndView.InsertItem(szItem, WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL, WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL, hTCSequenceFolder, (hTCSequenceItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hTCSequenceItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hTCSequenceItem, (DWORD_PTR)lstrcpy(pszName, pDatabaseTCSequence->GetName())))
				{
					sTCSequenceItem[0].hItem = hTCSequenceFolder;
					sTCSequenceItem[1].hItem = hTCSequenceFolder;
					sTCSequenceItem[0].mask = TVIF_CHILDREN;
					sTCSequenceItem[1].mask = TVIF_CHILDREN;
					sTCSequenceItem[0].cChildren = TRUE;
					sTCSequenceItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sTCSequenceItem[0]);
					m_wndView.SetItem(&sTCSequenceItem[1]);
					m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hTCSequenceItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hTCSequenceItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hTCSequenceItem, szItem);
			return;
		}
		if (hTCSequenceItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] = (m_wndView.DeleteItem(hTCSequenceItem)) ? max(m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] - 1, 0) : m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewProceduresPage::UpdateDatabaseProcedures(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sTCProcedureItem[2];
	HTREEITEM  hTCProcedureItem;
	HTREEITEM  hTCProcedureFolder;

	if ((hTCProcedureFolder = FindTCProcedureFolder()))
	{
		for (hTCProcedureItem = m_wndView.GetChildItem(hTCProcedureFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDUREITEMTEXT), (LPCTSTR)pDatabaseTCProcedure->GetDescription(), (LPCTSTR)pDatabaseTCProcedure->GetName()), szItem = (pDatabaseTCProcedure->GetDescription().IsEmpty()) ? pDatabaseTCProcedure->GetName() : szItem, nIndex = 0; hTCProcedureItem; hTCProcedureItem = m_wndView.GetNextItem(hTCProcedureItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pDatabaseTCProcedure->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hTCProcedureItem = m_wndView.InsertItem(szItem, WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL, WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL, hTCProcedureFolder, (hTCProcedureItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hTCProcedureItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hTCProcedureItem, (DWORD_PTR)lstrcpy(pszName, pDatabaseTCProcedure->GetName())))
				{
					sTCProcedureItem[0].hItem = hTCProcedureFolder;
					sTCProcedureItem[1].hItem = hTCProcedureFolder;
					sTCProcedureItem[0].mask = TVIF_CHILDREN;
					sTCProcedureItem[1].mask = TVIF_CHILDREN;
					sTCProcedureItem[0].cChildren = TRUE;
					sTCProcedureItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sTCProcedureItem[0]);
					m_wndView.SetItem(&sTCProcedureItem[1]);
					m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hTCProcedureItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hTCProcedureItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hTCProcedureItem, szItem);
			return;
		}
		if (hTCProcedureItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] = (m_wndView.DeleteItem(hTCProcedureItem)) ? max(m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] - 1, 0) : m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewProceduresPage::UpdateDatabaseProcedures(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	LPTSTR  pszName;
	CString  szItem;
	TVITEM  sTCSequenceItem[2];
	HTREEITEM  hTCSequenceItem;
	HTREEITEM  hTCSequenceFolder;

	if ((hTCSequenceFolder = FindTCSequenceFolder()))
	{
		for (hTCSequenceItem = m_wndView.GetChildItem(hTCSequenceFolder), szItem.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCEITEMTEXT), (LPCTSTR)pTCSequenceWnd->GetTitle(), (LPCTSTR)pTCSequenceWnd->GetName()), szItem = (pTCSequenceWnd->GetTitle().IsEmpty()) ? pTCSequenceWnd->GetName() : szItem, nIndex = 0; hTCSequenceItem; hTCSequenceItem = m_wndView.GetNextItem(hTCSequenceItem, TVGN_NEXT), nIndex++)
		{
			if ((nPosition < 0 && nIndex == abs(nPosition) - 1) || (nPosition >= 0 && nIndex == nPosition)) break;
			continue;
		}
		if ((pszName = (nPosition < 0) ? (LPTSTR)GlobalAlloc(GPTR, (pTCSequenceWnd->GetName().GetLength() + 1)*sizeof(TCHAR)) : (LPTSTR)NULL))
		{
			if ((hTCSequenceItem = m_wndView.InsertItem(szItem, WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL, WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL, hTCSequenceFolder, (hTCSequenceItem) ? ((nIndex > 0) ? m_wndView.GetNextItem(hTCSequenceItem, TVGN_PREVIOUS) : TVI_FIRST) : TVI_LAST)))
			{
				if (m_wndView.SetItemData(hTCSequenceItem, (DWORD_PTR)lstrcpy(pszName, pTCSequenceWnd->GetName())))
				{
					sTCSequenceItem[0].hItem = hTCSequenceFolder;
					sTCSequenceItem[1].hItem = hTCSequenceFolder;
					sTCSequenceItem[0].mask = TVIF_CHILDREN;
					sTCSequenceItem[1].mask = TVIF_CHILDREN;
					sTCSequenceItem[0].cChildren = TRUE;
					sTCSequenceItem[1].cChildren = I_CHILDRENCALLBACK;
					m_wndView.SetItem(&sTCSequenceItem[0]);
					m_wndView.SetItem(&sTCSequenceItem[1]);
					m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL]++;
					return;
				}
				m_wndView.DeleteItem(hTCSequenceItem);
			}
			GlobalFree(pszName);
			return;
		}
		if (hTCSequenceItem  &&  nPosition >= 0 && !bDelete)
		{
			m_wndView.SetItemText(hTCSequenceItem, szItem);
			return;
		}
		if (hTCSequenceItem  &&  nPosition >= 0 && bDelete)
		{
			m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] = (m_wndView.DeleteItem(hTCSequenceItem)) ? max(m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] - 1, 0) : m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL];
			return;
		}
	}
}
VOID CWorkspaceViewProceduresPage::UpdateDatabaseProcedures()
{
	TVITEM  sRootItem;
	CString  szProceduresRoot;

	for (szProceduresRoot.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_ROOTSYMBOLTEXT), (LPCTSTR)GetAccountDatabase()), m_wndView.DeleteAllItems(); (sRootItem.hItem = m_wndView.InsertItem((GetDatabase()->IsOpen()) ? (LPCTSTR)szProceduresRoot : STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_ROOTNOSYMBOLTEXT), (GetDatabase()->IsOpen()) ? WORKSPACEPROCEDURESPAGE_ROOTSYMBOL : WORKSPACEPROCEDURESPAGE_ROOTNOSYMBOL, (GetDatabase()->IsOpen()) ? WORKSPACEPROCEDURESPAGE_ROOTSYMBOL : WORKSPACEPROCEDURESPAGE_ROOTNOSYMBOL, (HTREEITEM)NULL, (HTREEITEM)NULL)) && m_wndView.SetItemState(sRootItem.hItem, TVIS_BOLD, TVIS_BOLD); )
	{
		EnumTCSequences(sRootItem.hItem);
		EnumTCProcedures(sRootItem.hItem);
		m_wndView.Expand(sRootItem.hItem, TVE_EXPAND);
		break;
	}
}

BOOL CWorkspaceViewProceduresPage::CreateProceduresItem()
{
	CString  szItem;
	HTREEITEM  hItem;

	if ((FindFolder((szItem = m_wndView.GetItemText((hItem = m_wndView.GetSelectedItem())))) && szItem == STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCESYMBOLTEXT)) || FindTCSequenceItem(hItem)) return CreateTCSequence();
	if ((FindFolder(szItem) && szItem == STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDURESYMBOLTEXT)) || FindTCProcedureItem(hItem)) return CreateTCProcedure();
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::OpenProceduresItem()
{
	HTREEITEM  hItem;

	if (FindTCSequenceItem((hItem = m_wndView.GetSelectedItem()))) return OpenTCSequence(hItem);
	if (FindTCProcedureItem(hItem)) return OpenTCProcedure(hItem);
	return FALSE;
}
VOID CWorkspaceViewProceduresPage::OpenProceduresItem(CONST POINT &ptItem)
{
	UINT  nFlags;
	POINT  point;
	CString  szMessage;
	HTREEITEM  hItem;

	point.x = ptItem.x;
	point.y = ptItem.y;
	m_wndView.ScreenToClient(&point);
	if ((hItem = m_wndView.HitTest(point, &nFlags)))
	{
		if (nFlags & TVHT_ONITEM)
		{
			if (FindTCSequenceItem(hItem))
			{
				if (!OpenTCSequence(hItem))
				{
					szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
			if (FindTCProcedureItem(hItem))
			{
				if (!OpenTCProcedure(hItem))
				{
					szMessage.Format(STRING(IDS_TCPROCEDURE_FAILURE_LOAD), m_wndView.GetItemText(hItem));
					ShowMessage(szMessage);
				}
			}
		}
	}
}

BOOL CWorkspaceViewProceduresPage::HasProceduresItem(INT nType) CONST
{
	if (nType == DATABASE_COMPONENT_TCSEQUENCE) return m_wndView.ItemHasChildren(FindTCSequenceFolder());
	if (nType == DATABASE_COMPONENT_TCPROCEDURE) return m_wndView.ItemHasChildren(FindTCProcedureFolder());
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::RenameProceduresItem()
{
	HTREEITEM  hItem;

	if (FindTCSequenceItem((hItem = m_wndView.GetSelectedItem()))) return RenameTCSequence(hItem);
	if (FindTCProcedureItem(hItem)) return RenameTCProcedure(hItem);
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::DeleteProceduresItem()
{
	HTREEITEM  hItem;
	CString  szMessage;

	if (FindTCSequenceItem((hItem = m_wndView.GetSelectedItem())))
	{
		for (szMessage.Format(STRING(IDS_TCSEQUENCE_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTCSequence(hItem); )
		{
			szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	if (FindTCProcedureItem(hItem))
	{
		for (szMessage.Format(STRING(IDS_TCPROCEDURE_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem)); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES && !DeleteTCProcedure(hItem); )
		{
			szMessage.Format(STRING(IDS_TCPROCEDURE_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			ShowMessage(szMessage);
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CWorkspaceViewProceduresPage::ShowFloatingMenu(CONST POINT &ptItem)
{
	UINT  nFlags;
	POINT  point;
	CString  szItem;
	HTREEITEM  hItem;

	for (point.x = ptItem.x, point.y = ptItem.y, m_wndView.ScreenToClient(&point); (hItem = m_wndView.HitTest(point, &nFlags)); )
	{
		if (nFlags & TVHT_ONITEM)
		{
			if (FindTCSequenceItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindTCProcedureItem(hItem))
			{
				ShowFloatingMenu(hItem, point);
				return;
			}
			if (FindFolder((szItem = m_wndView.GetItemText(hItem))))
			{
				ShowFloatingMenu(hItem, szItem, point);
				return;
			}
		}
		break;
	}
}
VOID CWorkspaceViewProceduresPage::ShowFloatingMenu(HTREEITEM hItem, CPoint point)
{
	UINT  nID;
	CPoint  ptMenu;
	CLocaleMenu  cMenu;
	CMFCPopupMenu  *pFloatingMenu;

	for (nID = IDR_TCSEQUENCEFOLDERFORMMENU*FindTCSequenceItem(hItem) + IDR_TCPROCEDUREFOLDERFORMMENU*FindTCProcedureItem(hItem); nID != 0; )
	{
		for (m_wndView.ClientToScreen(&(ptMenu = point)), m_wndView.SetFocus(); m_wndView.GetSelectedItem() != hItem; )
		{
			m_wndView.SelectItem(hItem);
			break;
		}
		if ((pFloatingMenu = (cMenu.LoadMenu(nID)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL)) pFloatingMenu->Create(this, ptMenu.x, ptMenu.y, cMenu.Detach());
		break;
	}
}
VOID CWorkspaceViewProceduresPage::ShowFloatingMenu(HTREEITEM hItem, LPCTSTR pszItem, CPoint point)
{
	UINT  nID;
	CPoint  ptMenu;
	CLocaleMenu  cMenu;
	CMFCPopupMenu  *pFloatingMenu;

	for (nID = (hItem == FindTCSequenceFolder()) ? IDR_TCSEQUENCEFOLDERMENU : 0, nID = (hItem == FindTCProcedureFolder()) ? IDR_TCPROCEDUREFOLDERMENU : nID; nID != 0; )
	{
		for (m_wndView.ClientToScreen(&(ptMenu = point)), m_wndView.SetFocus(); m_wndView.GetSelectedItem() != hItem; )
		{
			m_wndView.SelectItem(hItem);
			break;
		}
		if ((pFloatingMenu = (cMenu.LoadMenu(nID)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL)) pFloatingMenu->Create(this, ptMenu.x, ptMenu.y, cMenu.Detach());
		break;
	}
}

BOOL CWorkspaceViewProceduresPage::CanDeleteSel() CONST
{
	HTREEITEM  hItem;

	return(((hItem = m_wndView.GetSelectedItem()) && CWnd::GetFocus()->GetSafeHwnd() == m_wndView.GetSafeHwnd()) ? ((FindTCSequenceItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE)) || (FindTCProcedureItem(hItem) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE))) : FALSE);
}

VOID CWorkspaceViewProceduresPage::DoDeleteSel()
{
	HTREEITEM  hItem;
	CString  szMessage;

	if (CanDeleteSel())
	{
		if (FindTCSequenceItem((hItem = m_wndView.GetSelectedItem())))
		{
			szMessage.Format(STRING(IDS_TCSEQUENCE_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES  &&  !DeleteTCSequence(hItem))
			{
				szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
			}
		}
		if (FindTCProcedureItem(hItem))
		{
			szMessage.Format(STRING(IDS_TCPROCEDURE_QUESTION_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
			if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES  &&  !DeleteTCProcedure(hItem))
			{
				szMessage.Format(STRING(IDS_TCPROCEDURE_FAILURE_DELETE), (LPCTSTR)m_wndView.GetItemText(hItem));
				ShowMessage(szMessage);
			}
		}
	}
}

VOID CWorkspaceViewProceduresPage::EnumTCSequences(HTREEITEM hParentItem)
{
	INT  nSequence;
	INT  nSequences;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szName[2];
	CString  szDescription;
	HTREEITEM  hTCSequenceItem[2];

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindTCSequenceFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCESYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nSequence = 0, nSequences = m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] = (INT)GetDatabase()->GetTCSequences()->GetSize(), hTCSequenceItem[0] = hTCSequenceItem[1] = (HTREEITEM)NULL; nSequence < nSequences; nSequence++)
		{
			szName[0].Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCEITEMTEXT), (LPCTSTR)(szDescription = GetDatabase()->GetTCSequences()->GetAt(nSequence)->GetDescription()), (LPCTSTR)GetDatabase()->GetTCSequences()->GetAt(nSequence)->GetName());
			szName[1].Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCEITEMSHORTTEXT), (LPCTSTR)GetDatabase()->GetTCSequences()->GetAt(nSequence)->GetName());
			if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (GetDatabase()->GetTCSequences()->GetAt(nSequence)->GetName().GetLength() + 1)*sizeof(TCHAR))) != (LPTSTR)NULL)
			{
				if ((hTCSequenceItem[1] = m_wndView.InsertItem((!szDescription.IsEmpty()) ? szName[0] : szName[1], WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL, WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL, sFolderItem.hItem, (!hTCSequenceItem[0]) ? TVI_FIRST : hTCSequenceItem[0])))
				{
					if (m_wndView.SetItemData(hTCSequenceItem[1], (DWORD_PTR)lstrcpy(pszName, GetDatabase()->GetTCSequences()->GetAt(nSequence)->GetName())))
					{
						hTCSequenceItem[0] = hTCSequenceItem[1];
						continue;
					}
					m_wndView.DeleteItem(hTCSequenceItem[1]);
				}
				GlobalFree(pszName);
			}
			break;
		}
		while ((hTCSequenceItem[1] = m_wndView.GetNextItem(hTCSequenceItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hTCSequenceItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] = nSequence;
		break;
	}
}

VOID CWorkspaceViewProceduresPage::EnumTCProcedures(HTREEITEM hParentItem)
{
	INT  nProcedure;
	INT  nProcedures;
	LPTSTR  pszName;
	TVITEM  sFolderItem;
	CString  szName[2];
	CString  szDescription;
	HTREEITEM  hTCProcedureItem[2];

	for (sFolderItem.mask = TVIF_CHILDREN, sFolderItem.cChildren = I_CHILDRENCALLBACK; (sFolderItem.hItem = FindTCProcedureFolder()) || ((sFolderItem.hItem = m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDURESYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem)) && m_wndView.SetItem(&sFolderItem)); )
	{
		for (nProcedure = 0, nProcedures = m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] = (INT)GetDatabase()->GetTCProcedures()->GetSize(), hTCProcedureItem[0] = hTCProcedureItem[1] = (HTREEITEM)NULL; nProcedure < nProcedures; nProcedure++)
		{
			szName[0].Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDUREITEMTEXT), (LPCTSTR)(szDescription = GetDatabase()->GetTCProcedures()->GetAt(nProcedure)->GetDescription()), (LPCTSTR)GetDatabase()->GetTCProcedures()->GetAt(nProcedure)->GetName());
			szName[1].Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDUREITEMSHORTTEXT), (LPCTSTR)GetDatabase()->GetTCProcedures()->GetAt(nProcedure)->GetName());
			if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (GetDatabase()->GetTCProcedures()->GetAt(nProcedure)->GetName().GetLength() + 1)*sizeof(TCHAR))) != (LPTSTR)NULL)
			{
				if ((hTCProcedureItem[1] = m_wndView.InsertItem((!szDescription.IsEmpty()) ? szName[0] : szName[1], WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL, WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL, sFolderItem.hItem, (!hTCProcedureItem[0]) ? TVI_FIRST : hTCProcedureItem[0])))
				{
					if (m_wndView.SetItemData(hTCProcedureItem[1], (DWORD_PTR)lstrcpy(pszName, GetDatabase()->GetTCProcedures()->GetAt(nProcedure)->GetName())))
					{
						hTCProcedureItem[0] = hTCProcedureItem[1];
						continue;
					}
					m_wndView.DeleteItem(hTCProcedureItem[1]);
				}
				GlobalFree(pszName);
			}
			break;
		}
		while ((hTCProcedureItem[1] = m_wndView.GetNextItem(hTCProcedureItem[0], TVGN_NEXT)))
		{
			if (m_wndView.DeleteItem(hTCProcedureItem[1])) continue;
			break;
		}
		m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] = nProcedure;
		break;
	}
}

HTREEITEM CWorkspaceViewProceduresPage::FindTCSequenceFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCESYMBOLTEXT));
}

HTREEITEM CWorkspaceViewProceduresPage::FindTCProcedureFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDURESYMBOLTEXT));
}

HTREEITEM CWorkspaceViewProceduresPage::FindFolder(LPCTSTR pszFolder) CONST
{
	HTREEITEM  hFolderItem;

	for (hFolderItem = m_wndView.GetChildItem(m_wndView.GetRootItem()); hFolderItem; hFolderItem = m_wndView.GetNextItem(hFolderItem, TVGN_NEXT))
	{
		if (m_wndView.GetItemText(hFolderItem) == pszFolder) break;
		continue;
	}
	return hFolderItem;
}

BOOL CWorkspaceViewProceduresPage::FindTCSequenceItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCESYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewProceduresPage::FindTCProcedureItem(HTREEITEM hItem) CONST
{
	return FindItem(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDURESYMBOLTEXT), hItem);
}

BOOL CWorkspaceViewProceduresPage::FindItem(LPCTSTR pszItem, HTREEITEM hItem) CONST
{
	INT  nPosition;
	HTREEITEM  hChildItem;
	HTREEITEM  hFolderItem;

	if (!m_wndView.ItemHasChildren(hItem))
	{
		if ((hFolderItem = m_wndView.GetParentItem(hItem)) && m_wndView.GetItemText(hFolderItem) == pszItem)
		{
			for (hChildItem = m_wndView.GetChildItem(hFolderItem), nPosition = 0; hChildItem != (HTREEITEM)NULL; hChildItem = m_wndView.GetNextItem(hChildItem, TVGN_NEXT), nPosition++)
			{
				if (hChildItem == hItem) break;
				continue;
			}
			return((hChildItem != (HTREEITEM)NULL) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::CreateTCSequence()
{
	CTCSequenceWnd  *pTCSequenceWnd;

	return(((pTCSequenceWnd = new CTCSequenceWnd) && pTCSequenceWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewProceduresPage::OpenTCSequence(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCSequenceWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE) ? (CTCSequenceWnd *)pDisplayWnd : (CTCSequenceWnd *)NULL) && pTCSequenceWnd->GetName() == szName)
		{
			pTCSequenceWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pTCSequenceWnd = new CTCSequenceWnd(szName))) ? pTCSequenceWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewProceduresPage::RenameTCSequence(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewProceduresPage::RenameTCSequence(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCSequenceWnd  *pTCSequenceWnd;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE))
	{
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem), nCount = 0; nDisplay < nDisplays; nDisplay++)
		{
			if ((pTCSequenceWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE) ? (CTCSequenceWnd *)pDisplayWnd : (CTCSequenceWnd *)NULL) && pTCSequenceWnd->GetName() == szName)
			{
				for (szItem.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCEITEMTEXT), pszItem, (LPCTSTR)szName); !lstrlen(pszItem); )
				{
					szItem.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCEITEMSHORTTEXT), (LPCTSTR)szName);
					break;
				}
				pTCSequenceWnd->SetTitle(pszItem);
				nCount++;
			}
		}
		return((nCount > 0) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::DeleteTCSequence(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CHourglassCursor  cCursor;

	if (GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE))
	{
		if (GetDatabase()->DeleteTCSequence((szName = (LPCTSTR)m_wndView.GetItemData(hItem))) && m_wndView.DeleteItem(hItem))
		{
			for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
			{
				if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
				{
					pDisplayWnd->UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, szName, TRUE);
					continue;
				}
			}
			m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] = max(m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] - 1, 0);
			return TRUE;
		}
		return FALSE;
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCSequenceWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE) ? (CTCSequenceWnd *)pDisplayWnd : (CTCSequenceWnd *)NULL) && pTCSequenceWnd->GetName() == szName)
		{
			pTCSequenceWnd->DestroyWindow();
			break;
		}
	}
	if (CTCSequenceWnd::Delete(szName) >= 0 && m_wndView.DeleteItem(hItem))
	{
		m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] = max(m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::CreateTCProcedure()
{
	CTCProcedureWnd  *pTCProcedureWnd;

	return(((pTCProcedureWnd = new CTCProcedureWnd) && pTCProcedureWnd->Create(GetMainWnd())) ? TRUE : FALSE);
}

BOOL CWorkspaceViewProceduresPage::OpenTCProcedure(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCProcedureWnd  *pTCProcedureWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCProcedureWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE) ? (CTCProcedureWnd *)pDisplayWnd : (CTCProcedureWnd *)NULL) && pTCProcedureWnd->GetName() == szName)
		{
			pTCProcedureWnd->MDIActivate();
			break;
		}
	}
	return((nDisplay == nDisplays) ? (((pTCProcedureWnd = new CTCProcedureWnd(szName))) ? pTCProcedureWnd->Create(GetMainWnd()) : FALSE) : TRUE);
}

BOOL CWorkspaceViewProceduresPage::RenameTCProcedure(HTREEITEM hItem)
{
	m_wndView.SetFocus();
	return IsWindow(m_wndView.EditLabel(hItem)->GetSafeHwnd());
}
BOOL CWorkspaceViewProceduresPage::RenameTCProcedure(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCProcedureWnd  *pTCProcedureWnd;
	CDatabaseTCProcedure  *pProcedure[2];

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCProcedureWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE) ? (CTCProcedureWnd *)pDisplayWnd : (CTCProcedureWnd *)NULL) && pTCProcedureWnd->GetName() == szName)
		{
			szItem.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDUREITEMTEXT), pszItem, (LPCTSTR)szName);
			pTCProcedureWnd->SetTitle(pszItem);
			break;
		}
	}
	if ((pProcedure[0] = new CDatabaseTCProcedure))
	{
		if ((pProcedure[1] = GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(szName))) && pProcedure[0]->Copy(pProcedure[1]))
		{
			for (pProcedure[0]->SetDescription(pszItem), szItem.Format(STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDUREITEMTEXT), pszItem, (LPCTSTR)szName); GetDatabase()->Save(pProcedure[0]) >= 0; )
			{
				delete pProcedure[0];
				return TRUE;
			}
		}
		delete pProcedure[0];
	}
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::DeleteTCProcedure(HTREEITEM hItem)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCProcedureWnd  *pTCProcedureWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), szName = (LPCTSTR)m_wndView.GetItemData(hItem); nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCProcedureWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE) ? (CTCProcedureWnd *)pDisplayWnd : (CTCProcedureWnd *)NULL) && pTCProcedureWnd->GetName() == szName)
		{
			pTCProcedureWnd->DestroyWindow();
			break;
		}
	}
	if (CTCProcedureWnd::Delete(szName) >= 0 && m_wndView.DeleteItem(hItem))
	{
		m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] = max(m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] - 1, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CWorkspaceViewProceduresPage::IsDraggingDatabaseItem() CONST
{
	return(m_nDragItem != 0);
}

BEGIN_MESSAGE_MAP(CWorkspaceViewProceduresPage, CWorkspaceViewPage)
	//{{AFX_MSG_MAP(CWorkspaceViewProceduresPage)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPage message handlers

int CWorkspaceViewProceduresPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	BITMAP  sBitmap;
	CBitmap  cBitmap[WORKSPACEPROCEDURESPAGE_SYMBOLS];

	if (CWorkspaceViewPage::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndView.Create(TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS | TVS_NOTOOLTIPS | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0))
		{
			if (cBitmap[WORKSPACEPROCEDURESPAGE_ROOTSYMBOL].LoadBitmap(IDB_WORKSPACEPROCEDURESPAGEROOTSYMBOL) && cBitmap[WORKSPACEPROCEDURESPAGE_ROOTNOSYMBOL].LoadBitmap(IDB_WORKSPACEPROCEDURESPAGEROOTNOSYMBOL) && cBitmap[WORKSPACEPROCEDURESPAGE_FOLDERSYMBOL].LoadBitmap(IDB_WORKSPACEPROCEDURESPAGEFOLDERSYMBOL) && cBitmap[WORKSPACEPROCEDURESPAGE_FOLDEROPENSYMBOL].LoadBitmap(IDB_WORKSPACEPROCEDURESPAGEFOLDEROPENSYMBOL) && cBitmap[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL].LoadBitmap(IDB_WORKSPACEPROCEDURESPAGETCSEQUENCESYMBOL) && cBitmap[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL].LoadBitmap(IDB_WORKSPACEPROCEDURESPAGETCPROCEDURESYMBOL) && cBitmap[WORKSPACEPROCEDURESPAGE_ROOTSYMBOL].GetObject(sizeof(BITMAP), &sBitmap) > 0)
			{
				if (m_pItems.Create(sBitmap.bmWidth, sBitmap.bmHeight, ILC_COLOR32, WORKSPACEPROCEDURESPAGE_SYMBOLS, 1))
				{
					if (m_cDragItem.Create(sBitmap.bmWidth, sBitmap.bmHeight, ILC_COLOR32, 1, 1))
					{
						m_pItems.Add(&cBitmap[WORKSPACEPROCEDURESPAGE_ROOTSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEPROCEDURESPAGE_ROOTNOSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEPROCEDURESPAGE_FOLDERSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEPROCEDURESPAGE_FOLDEROPENSYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL], (CBitmap *)NULL);
						m_pItems.Add(&cBitmap[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL], (CBitmap *)NULL);
						if (m_pItems.GetImageCount() == WORKSPACEPROCEDURESPAGE_SYMBOLS)
						{
							m_wndView.SetImageList(&m_pItems, TVSIL_NORMAL);
							return 0;
						}
						m_cDragItem.DeleteImageList();
					}
					m_pItems.DeleteImageList();
				}
			}
		}
	}
	return -1;
}

void CWorkspaceViewProceduresPage::OnSize(UINT nType, int cx, int cy)
{
	m_wndView.MoveWindow(0, 0, cx, cy);
	CWorkspaceViewPage::OnSize(nType, cx, cy);
}

BOOL CWorkspaceViewProceduresPage::OnEraseBkgnd(CDC *pDC)
{
	CRect  rPage[2];

	for (GetWindowRect(rPage[0]), GetParent()->ScreenToClient(rPage[0]), GetParent()->CalcClientRect(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		MoveWindow(rPage[1]);
		return TRUE;
	}
	for (GetClientRect(rPage[0]), m_wndView.GetWindowRect(rPage[1]), GetParent()->ScreenToClient(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		m_wndView.MoveWindow(rPage[0], FALSE);
		m_wndView.RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
		return TRUE;
	}
	return CWorkspaceViewPage::OnEraseBkgnd(pDC);
}

void CWorkspaceViewProceduresPage::OnPaint()
{
	m_wndView.UpdateWindow();
	CWorkspaceViewPage::OnPaint();
}

void CWorkspaceViewProceduresPage::OnSetFocus(CWnd *pOldWnd)
{
	m_wndView.SetFocus();
}

void CWorkspaceViewProceduresPage::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd  *pWnd[2];
	CPoint  ptDrag;
	CDisplayWnd  *pDisplayWnd;

	for (ptDrag = point, ClientToScreen(&ptDrag); IsDraggingDatabaseItem(); )
	{
		if ((pWnd[0] = WindowFromPoint(ptDrag)) != (CWnd *)NULL)
		{
			while (!pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pWnd[1] = pWnd[0]->GetParent()))
				{
					pWnd[0] = pWnd[1];
					continue;
				}
				break;
			}
			if (IsWindow(pWnd[0]->GetSafeHwnd()) && pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pDisplayWnd = (CDisplayWnd *)pWnd[0])->CheckTableDropTarget(m_szDragItem, m_nDragItem, ptDrag))
				{
					if (m_bDragItem)
					{
						m_cDragItem.DragMove(ptDrag);
						break;
					}
					ShowCursor(FALSE);
					m_cDragItem.DragEnter((CWnd *)NULL, ptDrag);
					m_bDragItem = TRUE;
					break;
				}
				if (m_bDragItem)
				{
					ShowCursor(TRUE);
					m_cDragItem.DragLeave((CWnd *)NULL);
					m_bDragItem = FALSE;
				}
				SetCursor(LoadCursor((HINSTANCE)NULL, IDC_NO));
				break;
			}
		}
		if (m_bDragItem)
		{
			m_cDragItem.DragMove(ptDrag);
			break;
		}
		ShowCursor(FALSE);
		m_cDragItem.DragEnter((CWnd *)NULL, ptDrag);
		m_bDragItem = TRUE;
		break;
	}
	CWorkspaceViewPage::OnMouseMove(nFlags, point);
}

void CWorkspaceViewProceduresPage::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd  *pWnd[2];
	CPoint  ptDrag;
	CDisplayWnd  *pDisplayWnd;

	for (ptDrag = point, ClientToScreen(&ptDrag); IsDraggingDatabaseItem(); )
	{
		if ((pWnd[0] = WindowFromPoint(ptDrag)) != (CWnd *)NULL)
		{
			while (!pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pWnd[1] = pWnd[0]->GetParent()))
				{
					pWnd[0] = pWnd[1];
					continue;
				}
				break;
			}
			if (IsWindow(pWnd[0]->GetSafeHwnd()) && pWnd[0]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				if ((pDisplayWnd = (CDisplayWnd *)pWnd[0]) && pDisplayWnd->CheckTableDropTarget(m_szDragItem, m_nDragItem, ptDrag))
				{
					for (m_cDragItem.EndDrag(); m_bDragItem; )
					{
						m_bDragItem = FALSE;
						ShowCursor(TRUE);
						break;
					}
					pDisplayWnd->DropOnTableTarget(m_szDragItem, m_nDragItem, ptDrag);
					m_szDragItem.Empty();
					m_nDragItem = 0;
					ReleaseCapture();
					break;
				}
			}
		}
		for (m_cDragItem.EndDrag(); m_bDragItem; )
		{
			m_bDragItem = FALSE;
			ShowCursor(TRUE);
			break;
		}
		m_szDragItem.Empty();
		m_nDragItem = 0;
		ReleaseCapture();
		break;
	}
	CWorkspaceViewPage::OnLButtonUp(nFlags, point);
}

BOOL CWorkspaceViewProceduresPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rItem;
	CRect  rView;
	CRect  rResult;
	CEdit  *pEdit;
	LPVOID  pData;
	CPoint  ptDrag;
	CPoint  ptCursor;
	CBitmap  cBitmap;
	CString  szItem;
	CString  szMessage;
	NMMOUSE  *pNotifyMouseInfo = (NMMOUSE *)lParam;
	NMTREEVIEW  *pNotifyTreeInfo = (NMTREEVIEW *)lParam;
	NMTVKEYDOWN  *pNotifyKeyInfo = (NMTVKEYDOWN *)lParam;
	NMTVDISPINFO  *pNotifyDispInfo = (NMTVDISPINFO *)lParam;

	GetCursorPos(&ptCursor);
	ScreenToClient(&ptCursor);
	m_wndView.GetClientRect(rView);
	if (pNotifyMouseInfo->hdr.code == NM_SETCURSOR)
	{
		if (m_wndView.GetItemRect((HTREEITEM)pNotifyMouseInfo->dwItemSpec, rItem, TRUE))
		{
			if (rResult.IntersectRect(rView, rItem) && !rResult.EqualRect(rItem) && rItem.PtInRect(ptCursor))
			{
				for (m_wndView.ClientToScreen(rItem), szItem = m_wndView.GetItemText((HTREEITEM)pNotifyMouseInfo->dwItemSpec); !szItem.IsEmpty(); )
				{
					m_wndToolTip.ShowTip(&m_wndView, szItem, rItem, (m_wndView.GetRootItem() == (HTREEITEM)pNotifyMouseInfo->dwItemSpec) ? TRUE : FALSE);
					return FALSE;
				}
			}
		}
		m_wndToolTip.DeleteTip();
		return FALSE;
	}
	if ((pNotifyKeyInfo->hdr.code == TVN_KEYDOWN  &&  pNotifyKeyInfo->wVKey == VK_RETURN) || pNotifyMouseInfo->hdr.code == NM_DBLCLK)
	{
		if (FindTCSequenceItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenTCSequence(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
		if (FindTCProcedureItem(m_wndView.GetSelectedItem()))
		{
			if (!OpenTCProcedure(m_wndView.GetSelectedItem()))
			{
				szMessage.Format(STRING(IDS_TCPROCEDURE_FAILURE_LOAD), m_wndView.GetItemText(m_wndView.GetSelectedItem()));
				ShowMessage(szMessage);
				*pResult = TRUE;
				return TRUE;
			}
		}
	}
	if (pNotifyKeyInfo->hdr.code == TVN_KEYDOWN)
	{
		if (pNotifyKeyInfo->wVKey == VK_ESCAPE)
		{
			GetTopLevelParent()->SetFocus();
			*pResult = TRUE;
			return TRUE;
		}
	}
	if (pNotifyDispInfo->hdr.code == TVN_GETDISPINFO)
	{
		if ((szItem = m_wndView.GetItemText(pNotifyDispInfo->item.hItem)) == STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCESYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDURESYMBOLTEXT))
		{
			if (pNotifyDispInfo->item.mask & TVIF_IMAGE) pNotifyDispInfo->item.iImage = ((m_wndView.GetItemState(pNotifyDispInfo->item.hItem, TVIF_STATE) & TVIS_EXPANDED) && m_wndView.ItemHasChildren(pNotifyDispInfo->item.hItem)) ? WORKSPACEPROCEDURESPAGE_FOLDEROPENSYMBOL : WORKSPACEPROCEDURESPAGE_FOLDERSYMBOL;
			if (pNotifyDispInfo->item.mask & TVIF_SELECTEDIMAGE) pNotifyDispInfo->item.iSelectedImage = ((m_wndView.GetItemState(pNotifyDispInfo->item.hItem, TVIF_STATE) & TVIS_EXPANDED) && m_wndView.ItemHasChildren(pNotifyDispInfo->item.hItem)) ? WORKSPACEPROCEDURESPAGE_FOLDEROPENSYMBOL : WORKSPACEPROCEDURESPAGE_FOLDERSYMBOL;
		}
		if (pNotifyDispInfo->item.mask & TVIF_CHILDREN)
		{
			if (szItem == STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCSEQUENCESYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL] > 0) ? TRUE : FALSE;
			if (szItem == STRING(IDS_WORKSPACEWINDOW_PROCEDURESPAGE_TCPROCEDURESYMBOLTEXT)) pNotifyDispInfo->item.cChildren = (m_nCount[WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL] > 0) ? TRUE : FALSE;
		}
	}
	if (pNotifyDispInfo->hdr.code == TVN_BEGINLABELEDIT)
	{
		if ((!FindTCSequenceItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE)) && (!FindTCProcedureItem(pNotifyDispInfo->item.hItem) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE)) && !IsCompiling())
		{
			*pResult = TRUE;
			return TRUE;
		}
		if ((pEdit = m_wndView.GetEditControl()))
		{
			for (szItem = m_wndView.GetItemText(pNotifyDispInfo->item.hItem); !szItem.IsEmpty(); )
			{
				if (!_istspace(szItem[szItem.GetLength() - 1]))
				{
					szItem = szItem.Left(szItem.GetLength() - 1);
					continue;
				}
				szItem = szItem.Left(szItem.GetLength() - 1);
				break;
			}
			pEdit->SetWindowText(szItem);
		}
	}
	if (pNotifyDispInfo->hdr.code == TVN_ENDLABELEDIT)
	{
		if (AfxIsValidString(pNotifyDispInfo->item.pszText))
		{
			if (FindTCSequenceItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameTCSequence(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
			if (FindTCProcedureItem(pNotifyDispInfo->item.hItem))
			{
				for (CHourglassCursor cCursor; (*pResult = RenameTCProcedure(pNotifyDispInfo->item.hItem, pNotifyDispInfo->item.pszText, szItem)); )
				{
					m_nTimerID = SetTimer(WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL, 0, NULL);
					m_hItem = pNotifyDispInfo->item.hItem;
					m_szItem = szItem;
					break;
				}
				return TRUE;
			}
		}
	}
	if (pNotifyTreeInfo->hdr.code == TVN_BEGINDRAG)
	{
		for (m_nDragItem = DATABASE_COMPONENT_NONE, m_bDragItem = FALSE; FindTCSequenceItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEPROCEDURESPAGETCSEQUENCESYMBOL)) ? DATABASE_COMPONENT_TCSEQUENCE : m_nDragItem;
			break;
		}
		for (; FindTCProcedureItem(pNotifyTreeInfo->itemNew.hItem); )
		{
			m_nDragItem = (cBitmap.LoadBitmap(IDB_WORKSPACEPROCEDURESPAGETCPROCEDURESYMBOL)) ? DATABASE_COMPONENT_TCPROCEDURE : m_nDragItem;
			break;
		}
		if (m_nDragItem != DATABASE_COMPONENT_NONE)
		{
			if ((!m_cDragItem.GetImageCount() && !m_cDragItem.Add(&cBitmap, (CBitmap *)NULL)) || (m_cDragItem.GetImageCount() > 0 && m_cDragItem.Replace(0, &cBitmap, (CBitmap *)NULL)))
			{
				for (ptDrag = pNotifyTreeInfo->ptDrag, ClientToScreen(&ptDrag), m_wndView.SelectItem(pNotifyTreeInfo->itemNew.hItem); m_cDragItem.BeginDrag(0, CPoint(0, 0)) && m_cDragItem.DragEnter((CWnd *)NULL, ptDrag); )
				{
					m_szDragItem = (LPCTSTR)pNotifyTreeInfo->itemNew.lParam;
					m_bDragItem = TRUE;
					ShowCursor(FALSE);
					SetCapture();
					break;
				}
			}
			m_nDragItem = (m_bDragItem) ? m_nDragItem : DATABASE_COMPONENT_NONE;
		}
	}
	if (pNotifyTreeInfo->hdr.code == TVN_DELETEITEM)
	{
		if ((pData = (LPVOID)pNotifyTreeInfo->itemOld.lParam))
		{
			pNotifyTreeInfo->itemOld.lParam = 0;
			GlobalFree(pData);
		}
	}
	return CWorkspaceViewPage::OnNotify(wParam, lParam, pResult);
}

void CWorkspaceViewProceduresPage::OnTimer(UINT_PTR nEventID)
{
	KillTimer(m_nTimerID);
	m_wndView.SetItemText(m_hItem, m_szItem);
	m_hItem = (HTREEITEM)NULL;
	m_szItem.Empty();
	m_nTimerID = 0;
}

void CWorkspaceViewProceduresPage::OnDestroy()
{
	m_cDragItem.DeleteImageList();
	CWorkspaceViewPage::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPageToolTip

IMPLEMENT_DYNCREATE(CWorkspaceViewLogsPageToolTip, CWnd)

CWorkspaceViewLogsPageToolTip::CWorkspaceViewLogsPageToolTip() : CWnd()
{
	m_szText.Empty();
	m_rText.SetRectEmpty();
	m_bBoldText = FALSE;
}

BOOL CWorkspaceViewLogsPageToolTip::ShowTip(CWnd *pParentWnd, LPCTSTR pszText, CONST RECT &rect, BOOL bBold)
{
	if ((m_szText != pszText  &&  lstrlen(pszText) > 0) && !m_rText.EqualRect(&rect))
	{
		for (DeleteTip(); CWnd::CreateEx(0, AfxRegisterWndClass(CS_DBLCLKS | CS_SAVEBITS | CS_DROPSHADOW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), EMPTYSTRING, WS_POPUP | WS_BORDER, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, (m_pParentWnd = pParentWnd)->GetSafeHwnd(), (HMENU)NULL); )
		{
			SetTimer(WORKSPACEVIEWLOGSPAGE_TOOLTIP_TIMERID, 0, NULL);
			m_bBoldText = bBold;
			m_szText = pszText;
			m_rText = rect;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CWorkspaceViewLogsPageToolTip::DeleteTip()
{
	for (m_szText.Empty(), m_rText.SetRectEmpty(), m_bBoldText = FALSE; IsWindow(GetSafeHwnd()); )
	{
		KillTimer(WORKSPACEVIEWLOGSPAGE_TOOLTIP_TIMERID);
		DestroyWindow();
		return TRUE;
	}
	return FALSE;
}

CWorkspaceViewLogsPageTreeCtrl *CWorkspaceViewLogsPageToolTip::GetParent() CONST
{
	return((CWorkspaceViewLogsPageTreeCtrl *)m_pParentWnd);
}

VOID CWorkspaceViewLogsPageToolTip::DrawContent(CDC *pDC)
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pFont;
	CFont  *pOldFont;
	CRect  rToolTip;
	LOGFONT  lfFont;

	for (GetClientRect(rToolTip); (pFont = GetParent()->GetFont()) && pFont->GetLogFont(&lfFont); )
	{
		if (cFont.CreateFont(lfFont.lfHeight, lfFont.lfWidth, lfFont.lfEscapement, lfFont.lfOrientation, (m_bBoldText) ? FW_BOLD : lfFont.lfWeight, lfFont.lfItalic, lfFont.lfUnderline, lfFont.lfStrikeOut, lfFont.lfCharSet, lfFont.lfOutPrecision, lfFont.lfClipPrecision, lfFont.lfQuality, lfFont.lfPitchAndFamily, lfFont.lfFaceName))
		{
			if ((pOldFont = pDC->SelectObject(&cFont)))
			{
				nBkMode = pDC->SetBkMode(TRANSPARENT);
				pDC->DrawText(m_szText, CRect(GetSystemMetrics(SM_CXBORDER), 0, m_rText.Width(), m_rText.Height()), DT_LEFT | DT_TOP | DT_NOPREFIX);
				pDC->SelectObject(pOldFont);
				pDC->SetBkMode(nBkMode);
			}
			cFont.DeleteObject();
		}
		break;
	}
}

BEGIN_MESSAGE_MAP(CWorkspaceViewLogsPageToolTip, CWnd)
	//{{AFX_MSG_MAP(CWorkspaceViewLogsPageToolTip)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPageToolTip message handlers

BOOL CWorkspaceViewLogsPageToolTip::OnEraseBkgnd(CDC *pDC)
{
	CRect  rToolTip;
	CBrush  cBkgndBrush;

	for (GetClientRect(rToolTip); cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK); )
	{
		pDC->FillRect(rToolTip, &cBkgndBrush);
		cBkgndBrush.DeleteObject();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CWorkspaceViewLogsPageToolTip::OnPaint()
{
	CPaintDC  cDC(this);

	DrawContent(&cDC);
}

void CWorkspaceViewLogsPageToolTip::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect  rToolTip;

	for (GetWindowRect(rToolTip), ScreenToClient(rToolTip); !rToolTip.PtInRect(point); )
	{
		DeleteTip();
		break;
	}
	SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	CWnd::OnMouseMove(nFlags, point);
}

void CWorkspaceViewLogsPageToolTip::OnTimer(UINT_PTR nEventID)
{
	CPoint  ptCursor;

	if (nEventID == WORKSPACEVIEWLOGSPAGE_TOOLTIP_TIMERID)
	{
		if (IsWindowVisible())
		{
			KillTimer(nEventID);
			ReleaseCapture();
			DestroyWindow();
			return;
		}
		for (GetCursorPos(&ptCursor); m_rText.PtInRect(ptCursor); )
		{
			SetTimer(WORKSPACEVIEWLOGSPAGE_TOOLTIP_TIMERID, WORKSPACEVIEWLOGSPAGE_TOOLTIP_TIMEOUT, NULL);
			ShowWindow(SW_SHOWNA);
			SetCapture();
			break;
		}
		if (!m_rText.PtInRect(ptCursor))
		{
			KillTimer(nEventID);
			DestroyWindow();
			return;
		}
	}
	CWnd::OnTimer(nEventID);
}

void CWorkspaceViewLogsPageToolTip::OnDestroy()
{
	if (GetCapture()->GetSafeHwnd() == GetSafeHwnd()) ReleaseCapture();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPageTreeCtrl

IMPLEMENT_DYNCREATE(CWorkspaceViewLogsPageTreeCtrl, CTreeCtrl)

CWorkspaceViewLogsPageTreeCtrl::CWorkspaceViewLogsPageTreeCtrl() : CTreeCtrl()
{
	return;
}

CWorkspaceViewLogsPage *CWorkspaceViewLogsPageTreeCtrl::GetParent() CONST
{
	return((CWorkspaceViewLogsPage *)CTreeCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CWorkspaceViewLogsPageTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CWorkspaceViewLogsPageTreeCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPageTreeCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPage

IMPLEMENT_DYNCREATE(CWorkspaceViewLogsPage, CWorkspaceViewPage)

CWorkspaceViewLogsPage::CWorkspaceViewLogsPage() : CWorkspaceViewPage()
{
	return;
}

VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTMPacketItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pDatabaseTMPacket->GetTag(), szText, GetAccountUserName(), DATABASE_COMPONENT_TMPACKET, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTMPacketItem = m_wndView.GetChildItem((hFolderItem = FindTMPacketFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTMPacketItem != (HTREEITEM)NULL; hTMPacketItem = m_wndView.GetNextItem(hTMPacketItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTMPacketItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hTMPacketItem || !hTMPacketItem) ? TVI_FIRST : m_wndView.GetNextItem(hTMPacketItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTMPacket->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMTEXT), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTMPacketItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTMPacketItem != (HTREEITEM)NULL; hTMPacketItem = m_wndView.GetNextItem(hTMPacketItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTMPacketItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hTMPacketItem || !hTMPacketItem) ? FindScriptFolder() : m_wndView.GetNextItem(hTMPacketItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTMPacket->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMNAMETEXT), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCFunctionItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pDatabaseTCFunction->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_TCFUNCTION, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCFunctionItem = m_wndView.GetChildItem((hFolderItem = FindTCFunctionFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCFunctionItem != (HTREEITEM)NULL; hTCFunctionItem = m_wndView.GetNextItem(hTCFunctionItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCFunctionItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hTCFunctionItem || !hTCFunctionItem) ? TVI_FIRST : m_wndView.GetNextItem(hTCFunctionItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCFunction->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMTEXT), (LPCTSTR)pDatabaseTCFunction->GetName(), (LPCTSTR)pDatabaseTCFunction->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCFunctionItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCFunctionItem != (HTREEITEM)NULL; hTCFunctionItem = m_wndView.GetNextItem(hTCFunctionItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCFunctionItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hTCFunctionItem || !hTCFunctionItem) ? FindScriptFolder() : m_wndView.GetNextItem(hTCFunctionItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCFunction->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMNAMETEXT), (LPCTSTR)pDatabaseTCFunction->GetName(), (LPCTSTR)pDatabaseTCFunction->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCSequenceItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pDatabaseTCSequence->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_TCSEQUENCE, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCSequenceItem = m_wndView.GetChildItem((hFolderItem = FindTCSequenceFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCSequenceItem != (HTREEITEM)NULL; hTCSequenceItem = m_wndView.GetNextItem(hTCSequenceItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCSequenceItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hTCSequenceItem || !hTCSequenceItem) ? TVI_FIRST : m_wndView.GetNextItem(hTCSequenceItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCSequence->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMTEXT), (LPCTSTR)pDatabaseTCSequence->GetName(), (LPCTSTR)pDatabaseTCSequence->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCSequenceItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCSequenceItem != (HTREEITEM)NULL; hTCSequenceItem = m_wndView.GetNextItem(hTCSequenceItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCSequenceItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hTCSequenceItem || !hTCSequenceItem) ? FindScriptFolder() : m_wndView.GetNextItem(hTCSequenceItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCSequence->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMNAMETEXT), (LPCTSTR)pDatabaseTCSequence->GetName(), (LPCTSTR)pDatabaseTCSequence->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCProcedureItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pDatabaseTCProcedure->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_TCPROCEDURE, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCProcedureItem = m_wndView.GetChildItem((hFolderItem = FindTCProcedureFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCProcedureItem != (HTREEITEM)NULL; hTCProcedureItem = m_wndView.GetNextItem(hTCProcedureItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCProcedureItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hTCProcedureItem || !hTCProcedureItem) ? TVI_FIRST : m_wndView.GetNextItem(hTCProcedureItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCProcedure->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMTEXT), (LPCTSTR)pDatabaseTCProcedure->GetName(), (LPCTSTR)pDatabaseTCProcedure->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCProcedureItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCProcedureItem != (HTREEITEM)NULL; hTCProcedureItem = m_wndView.GetNextItem(hTCProcedureItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCProcedureItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hTCProcedureItem || !hTCProcedureItem) ? FindScriptFolder() : m_wndView.GetNextItem(hTCProcedureItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCProcedure->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMNAMETEXT), (LPCTSTR)pDatabaseTCProcedure->GetName(), (LPCTSTR)pDatabaseTCProcedure->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTMParameterItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pDatabaseTMParameter->GetTag(), szText, GetAccountUserName(), DATABASE_COMPONENT_TMPARAMETER, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTMParameterItem = m_wndView.GetChildItem((hFolderItem = FindTMParameterFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTMParameterItem != (HTREEITEM)NULL; hTMParameterItem = m_wndView.GetNextItem(hTMParameterItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTMParameterItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hTMParameterItem || !hTMParameterItem) ? TVI_FIRST : m_wndView.GetNextItem(hTMParameterItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTMParameter->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMTEXT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTMParameterItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTMParameterItem != (HTREEITEM)NULL; hTMParameterItem = m_wndView.GetNextItem(hTMParameterItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTMParameterItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hTMParameterItem || !hTMParameterItem) ? FindScriptFolder() : m_wndView.GetNextItem(hTMParameterItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTMParameter->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMNAMETEXT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCParameterItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pDatabaseTCParameter->GetTag(), szText, GetAccountUserName(), DATABASE_COMPONENT_TCPARAMETER, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCParameterItem = m_wndView.GetChildItem((hFolderItem = FindTCParameterFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCParameterItem != (HTREEITEM)NULL; hTCParameterItem = m_wndView.GetNextItem(hTCParameterItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCParameterItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hTCParameterItem || !hTCParameterItem) ? TVI_FIRST : m_wndView.GetNextItem(hTCParameterItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCParameter->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMTEXT), (LPCTSTR)pDatabaseTCParameter->GetTag(), (LPCTSTR)pDatabaseTCParameter->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCParameterItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCParameterItem != (HTREEITEM)NULL; hTCParameterItem = m_wndView.GetNextItem(hTCParameterItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCParameterItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hTCParameterItem || !hTCParameterItem) ? FindScriptFolder() : m_wndView.GetNextItem(hTCParameterItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseTCParameter->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMNAMETEXT), (LPCTSTR)pDatabaseTCParameter->GetTag(), (LPCTSTR)pDatabaseTCParameter->GetDescription());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hOBProcessorItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pDatabaseOBProcessor->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_OBPROCESSOR, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hOBProcessorItem = m_wndView.GetChildItem((hFolderItem = FindOBProcessorFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hOBProcessorItem != (HTREEITEM)NULL; hOBProcessorItem = m_wndView.GetNextItem(hOBProcessorItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hOBProcessorItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hOBProcessorItem || !hOBProcessorItem) ? TVI_FIRST : m_wndView.GetNextItem(hOBProcessorItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseOBProcessor->GetDescription().IsEmpty() || !pDatabaseOBProcessor->GetDetails().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMTEXT), (LPCTSTR)pDatabaseOBProcessor->GetName(), (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseOBProcessor->GetDescription() : (LPCTSTR)pDatabaseOBProcessor->GetDetails());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hOBProcessorItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hOBProcessorItem != (HTREEITEM)NULL; hOBProcessorItem = m_wndView.GetNextItem(hOBProcessorItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hOBProcessorItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hOBProcessorItem || !hOBProcessorItem) ? FindScriptFolder() : m_wndView.GetNextItem(hOBProcessorItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pDatabaseOBProcessor->GetDescription().IsEmpty() || !pDatabaseOBProcessor->GetDetails().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMNAMETEXT), (LPCTSTR)pDatabaseOBProcessor->GetName(), (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseOBProcessor->GetDescription() : (LPCTSTR)pDatabaseOBProcessor->GetDetails());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCSequenceItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pTCSequenceWnd->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_TCSEQUENCE, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCSequenceItem = m_wndView.GetChildItem((hFolderItem = FindTCSequenceFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCSequenceItem != (HTREEITEM)NULL; hTCSequenceItem = m_wndView.GetNextItem(hTCSequenceItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCSequenceItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hTCSequenceItem || !hTCSequenceItem) ? TVI_FIRST : m_wndView.GetNextItem(hTCSequenceItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pTCSequenceWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMTEXT), (LPCTSTR)pTCSequenceWnd->GetName(), (LPCTSTR)pTCSequenceWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hTCSequenceItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hTCSequenceItem != (HTREEITEM)NULL; hTCSequenceItem = m_wndView.GetNextItem(hTCSequenceItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hTCSequenceItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hTCSequenceItem || !hTCSequenceItem) ? FindScriptFolder() : m_wndView.GetNextItem(hTCSequenceItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pTCSequenceWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMNAMETEXT), (LPCTSTR)pTCSequenceWnd->GetName(), (LPCTSTR)pTCSequenceWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hANDItem;
	HTREEITEM  hFolderItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pANDWnd->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_AND, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hANDItem = m_wndView.GetChildItem((hFolderItem = FindANDFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hANDItem != (HTREEITEM)NULL; hANDItem = m_wndView.GetNextItem(hANDItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hANDItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hANDItem || !hANDItem) ? TVI_FIRST : m_wndView.GetNextItem(hANDItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pANDWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMTEXT), (LPCTSTR)pANDWnd->GetName(), (LPCTSTR)pANDWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hANDItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hANDItem != (HTREEITEM)NULL; hANDItem = m_wndView.GetNextItem(hANDItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hANDItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hANDItem || !hANDItem) ? FindScriptFolder() : m_wndView.GetNextItem(hANDItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pANDWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMNAMETEXT), (LPCTSTR)pANDWnd->GetName(), (LPCTSTR)pANDWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hGRDItem;
	HTREEITEM  hFolderItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pGRDWnd->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_GRD, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hGRDItem = m_wndView.GetChildItem((hFolderItem = FindGRDFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hGRDItem != (HTREEITEM)NULL; hGRDItem = m_wndView.GetNextItem(hGRDItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hGRDItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hGRDItem || !hGRDItem) ? TVI_FIRST : m_wndView.GetNextItem(hGRDItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pGRDWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMTEXT), (LPCTSTR)pGRDWnd->GetName(), (LPCTSTR)pGRDWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hGRDItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hGRDItem != (HTREEITEM)NULL; hGRDItem = m_wndView.GetNextItem(hGRDItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hGRDItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hGRDItem || !hGRDItem) ? FindScriptFolder() : m_wndView.GetNextItem(hGRDItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pGRDWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMNAMETEXT), (LPCTSTR)pGRDWnd->GetName(), (LPCTSTR)pGRDWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hMMDItem;
	HTREEITEM  hFolderItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			szText = (!bDelete  &&  pMMDWnd->IsCompilingMMD()) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_COMPILATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pMMDWnd->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_MMD, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hMMDItem = m_wndView.GetChildItem((hFolderItem = FindMMDFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hMMDItem != (HTREEITEM)NULL; hMMDItem = m_wndView.GetNextItem(hMMDItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hMMDItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hMMDItem || !hMMDItem) ? TVI_FIRST : m_wndView.GetNextItem(hMMDItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pMMDWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMTEXT), (LPCTSTR)pMMDWnd->GetName(), (LPCTSTR)pMMDWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hMMDItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hMMDItem != (HTREEITEM)NULL; hMMDItem = m_wndView.GetNextItem(hMMDItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hMMDItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hMMDItem || !hMMDItem) ? FindScriptFolder() : m_wndView.GetNextItem(hMMDItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pMMDWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMNAMETEXT), (LPCTSTR)pMMDWnd->GetName(), (LPCTSTR)pMMDWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hPODItem;
	HTREEITEM  hFolderItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pPODWnd->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_POD, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hPODItem = m_wndView.GetChildItem((hFolderItem = FindPODFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hPODItem != (HTREEITEM)NULL; hPODItem = m_wndView.GetNextItem(hPODItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hPODItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hPODItem || !hPODItem) ? TVI_FIRST : m_wndView.GetNextItem(hPODItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pPODWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMTEXT), (LPCTSTR)pPODWnd->GetName(), (LPCTSTR)pPODWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hPODItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hPODItem != (HTREEITEM)NULL; hPODItem = m_wndView.GetNextItem(hPODItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hPODItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hPODItem || !hPODItem) ? FindScriptFolder() : m_wndView.GetNextItem(hPODItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pPODWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMNAMETEXT), (LPCTSTR)pPODWnd->GetName(), (LPCTSTR)pPODWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nComponent;
	HTREEITEM  hScriptItem;
	HTREEITEM  hFolderItem;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			szText = (bDelete) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DELETIONTEXT)) : EMPTYSTRING;
			szText = (!bDelete  &&  nPosition < 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_CREATIONTEXT)) : szText;
			szText = (!bDelete  &&  nPosition >= 0) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MODIFICATIONTEXT)) : szText;
			szText = (!bDelete  &&  pScriptWnd->IsCompilingScript()) ? tTime.FormatGmt(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_COMPILATIONTEXT)) : szText;
			for (pLogInfo[0]->SetLog(pScriptWnd->GetName(), szText, GetAccountUserName(), DATABASE_COMPONENT_SCRIPT, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
			{
				ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
				break;
			}
			if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
			{
				if (pLogInfo[0]->GetLog(szName, szText, szUser, nComponent, tTime, nData))
				{
					for (; (pLogEntry[0] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hScriptItem = m_wndView.GetChildItem((hFolderItem = FindScriptFolder())), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hScriptItem != (HTREEITEM)NULL; hScriptItem = m_wndView.GetNextItem(hScriptItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hScriptItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hScriptItem || !hScriptItem) ? TVI_FIRST : m_wndView.GetNextItem(hScriptItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pScriptWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMTEXT), (LPCTSTR)pScriptWnd->GetName(), (LPCTSTR)pScriptWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
								m_wndView.DeleteItem(pLogEntry[0]->hItem);
							}
							GlobalFree(pLogEntry[0]->pData);
						}
						GlobalFree(pLogEntry[0]);
						pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
					{
						if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
						{
							for (hScriptItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hScriptItem != (HTREEITEM)NULL; hScriptItem = m_wndView.GetNextItem(hScriptItem, TVGN_NEXT))
							{
								for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hScriptItem)); )
								{
									nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
									CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
									break;
								}
								if (pLogInfo[1]->Unmap(nInfo[1]))
								{
									if (pLogInfo[1]->GetLogTime() <= tTime) break;
									continue;
								}
							}
							for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hScriptItem || !hScriptItem) ? FindScriptFolder() : m_wndView.GetNextItem(hScriptItem, TVGN_PREVIOUS); TRUE; )
							{
								szItem.Format((!pScriptWnd->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMNAMETEXT), (LPCTSTR)pScriptWnd->GetName(), (LPCTSTR)pScriptWnd->GetTitle());
								sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
							{
								if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
								m_wndView.DeleteItem(pLogEntry[1]->hItem);
							}
							GlobalFree(pLogEntry[1]->pData);
						}
						GlobalFree(pLogEntry[1]);
						pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
						break;
					}
					if (pLogEntry[0] != (PWORKSPACELOGENTRY)NULL  &&  pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
					{
						m_wndView.Invalidate(FALSE);
						m_wndView.UpdateWindow();
						delete pLogInfo[1];
						return;
					}
				}
				m_pLogs.RemoveAt(nIndex);
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs(ULONGLONG nComponent, LPCTSTR pszName)
{
	INT  nIndex;
	INT  cbSize;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo[2];
	ULONGLONG  nType;
	HTREEITEM  hItem;
	HTREEITEM  hFolderItem;
	CMMDLayout  *pMMDLayout;
	TVINSERTSTRUCT  sLogItem[1];
	CDatabaseLogInfo  *pLogInfo[2];
	WORKSPACELOGENTRY  *pLogEntry[3];
	CAutomationScript  *pScriptLayout;
	CDatabaseTCProcedure  *pProcedure;

	if ((pLogInfo[0] = new CDatabaseLogInfo))
	{
		if ((pLogInfo[1] = new CDatabaseLogInfo))
		{
			if (GetDatabase()->GetLoggingPolicy() & LOGFILE_POLICY_DISABLED)
			{
				delete pLogInfo[0];
				delete pLogInfo[1];
				return;
			}
			if (nComponent == DATABASE_COMPONENT_TCPROCEDURE || nComponent == ~DATABASE_COMPONENT_TCPROCEDURE || nComponent == DATABASE_COMPONENT_MMD || nComponent == ~DATABASE_COMPONENT_MMD || nComponent == DATABASE_COMPONENT_SCRIPT || nComponent == ~DATABASE_COMPONENT_SCRIPT || nComponent == DATABASE_COMPONENTS_ANY || nComponent == ~DATABASE_COMPONENTS_ANY || nComponent == DATABASE_COMPONENTS_ALL || nComponent == ~DATABASE_COMPONENTS_ALL)
			{
				for (pLogInfo[0]->SetLog(pszName, (szText = tTime.FormatGmt((nComponent == DATABASE_COMPONENT_TCPROCEDURE || nComponent == DATABASE_COMPONENT_MMD || nComponent == DATABASE_COMPONENT_SCRIPT || nComponent == DATABASE_COMPONENTS_ANY || nComponent == DATABASE_COMPONENTS_ALL) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_COMPILATIONTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ABORTCOMPILATIONTEXT))), GetAccountUserName(), nComponent, tTime, nData); !GetDatabase()->WriteLog(pLogInfo[0]); )
				{
					ShowMessage(SYSTEM_WARNING_DATABASELOG_WRITE_FAILURE);
					break;
				}
				if ((nIndex = m_pLogs.Add(pLogInfo[0])) >= 0)
				{
					if (pLogInfo[0]->GetLog(szName, szText, szUser, nType, tTime, nData))
					{
						for (; (pLogEntry[0] = (nComponent == DATABASE_COMPONENT_TCPROCEDURE || nComponent == ~DATABASE_COMPONENT_TCPROCEDURE || nComponent == DATABASE_COMPONENT_MMD || nComponent == ~DATABASE_COMPONENT_MMD || nComponent == DATABASE_COMPONENT_SCRIPT || nComponent == ~DATABASE_COMPONENT_SCRIPT) ? (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY)) : (PWORKSPACELOGENTRY)NULL); )
						{
							if ((pLogEntry[0]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL) != (LPBYTE)NULL)
							{
								for (hItem = m_wndView.GetChildItem((hFolderItem = (nComponent == DATABASE_COMPONENT_TCPROCEDURE || nComponent == ~DATABASE_COMPONENT_TCPROCEDURE) ? FindTCProcedureFolder() : ((nComponent == DATABASE_COMPONENT_MMD || nComponent == ~DATABASE_COMPONENT_MMD) ? FindMMDFolder() : FindScriptFolder()))), CopyMemory(pLogEntry[0]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hItem != (HTREEITEM)NULL; hItem = m_wndView.GetNextItem(hItem, TVGN_NEXT))
								{
									for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hItem)); )
									{
										nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
										CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
										break;
									}
									if (pLogInfo[1]->Unmap(nInfo[1]))
									{
										if (pLogInfo[1]->GetLogTime() <= tTime) break;
										continue;
									}
								}
								for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetChildItem(hFolderItem) == hItem || !hItem) ? TVI_FIRST : m_wndView.GetNextItem(hItem, TVGN_PREVIOUS); (pProcedure = (nComponent == DATABASE_COMPONENT_TCPROCEDURE || nComponent == ~DATABASE_COMPONENT_TCPROCEDURE) ? GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(szName)) : (CDatabaseTCProcedure *)NULL); )
								{
									szItem.Format((!pProcedure->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMTEXT), (LPCTSTR)pProcedure->GetName(), (LPCTSTR)pProcedure->GetDescription());
									sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
									sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
									break;
								}
								if ((pMMDLayout = (nComponent == DATABASE_COMPONENT_MMD || nComponent == ~DATABASE_COMPONENT_MMD) ? GetDatabase()->GetMMDs()->GetAt(GetDatabase()->GetMMDs()->Find(szName)) : (CMMDLayout *)NULL))
								{
									szItem.Format((!pMMDLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMTEXT), (LPCTSTR)pMMDLayout->GetName(), (LPCTSTR)pMMDLayout->GetTitle());
									sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
									sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								}
								if ((pScriptLayout = (nComponent == DATABASE_COMPONENT_SCRIPT || nComponent == ~DATABASE_COMPONENT_SCRIPT) ? GetDatabase()->GetScripts()->GetAt(GetDatabase()->GetScripts()->Find(szName)) : (CAutomationScript *)NULL))
								{
									szItem.Format((!pScriptLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMTEXT), (LPCTSTR)pScriptLayout->GetName(), (LPCTSTR)pScriptLayout->GetTitle());
									sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
									sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								}
								if ((pLogEntry[0]->hItem = m_wndView.InsertItem(&sLogItem[0])))
								{
									if (m_wndView.SetItemData(pLogEntry[0]->hItem, (DWORD_PTR)pLogEntry[0])) break;
									m_wndView.DeleteItem(pLogEntry[0]->hItem);
								}
								GlobalFree(pLogEntry[0]->pData);
							}
							GlobalFree(pLogEntry[0]);
							pLogEntry[0] = (PWORKSPACELOGENTRY)NULL;
							break;
						}
						for (; (pLogEntry[1] = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))); )
						{
							if ((pLogEntry[1]->pData = (pLogInfo[0]->Map(nInfo[0])) ? (LPBYTE)GlobalAlloc(GPTR, nInfo[0].GetSize()) : (LPBYTE)NULL))
							{
								for (hItem = m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT), hFolderItem = m_wndView.GetRootItem(), CopyMemory(pLogEntry[1]->pData, nInfo[0].GetData(), nInfo[0].GetSize()); hItem != (HTREEITEM)NULL; hItem = m_wndView.GetNextItem(hItem, TVGN_NEXT))
								{
									for (nInfo[1].RemoveAll(); (pLogEntry[2] = (PWORKSPACELOGENTRY)m_wndView.GetItemData(hItem)); )
									{
										nInfo[1].SetSize((cbSize = (INT)GlobalSize(pLogEntry[2]->pData)));
										CopyMemory(nInfo[1].GetData(), pLogEntry[2]->pData, cbSize);
										break;
									}
									if (pLogInfo[1]->Unmap(nInfo[1]))
									{
										if (pLogInfo[1]->GetLogTime() <= tTime) break;
										continue;
									}
								}
								for (sLogItem[0].itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szName, sLogItem[0].itemex.iIntegral = CalcLines(szName, szText, szUser), sLogItem[0].itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sLogItem[0].hParent = hFolderItem, sLogItem[0].hInsertAfter = (m_wndView.GetNextItem(FindScriptFolder(), TVGN_NEXT) == hItem || !hItem) ? FindScriptFolder() : m_wndView.GetNextItem(hItem, TVGN_PREVIOUS); (pProcedure = (nComponent == DATABASE_COMPONENT_TCPROCEDURE || nComponent == ~DATABASE_COMPONENT_TCPROCEDURE) ? GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(szName)) : (CDatabaseTCProcedure *)NULL); )
								{
									szItem.Format((!pProcedure->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMNAMETEXT), (LPCTSTR)pProcedure->GetName(), (LPCTSTR)pProcedure->GetDescription());
									sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
									sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
									break;
								}
								if ((pMMDLayout = (nComponent == DATABASE_COMPONENT_MMD || nComponent == ~DATABASE_COMPONENT_MMD) ? GetDatabase()->GetMMDs()->GetAt(GetDatabase()->GetMMDs()->Find(szName)) : (CMMDLayout *)NULL))
								{
									szItem.Format((!pMMDLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMNAMETEXT), (LPCTSTR)pMMDLayout->GetName(), (LPCTSTR)pMMDLayout->GetTitle());
									sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
									sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								}
								if ((pScriptLayout = (nComponent == DATABASE_COMPONENT_SCRIPT || nComponent == ~DATABASE_COMPONENT_SCRIPT) ? GetDatabase()->GetScripts()->GetAt(GetDatabase()->GetScripts()->Find(szName)) : (CAutomationScript *)NULL))
								{
									szItem.Format((!pScriptLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMNAMEFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMNAMETEXT), (LPCTSTR)pScriptLayout->GetName(), (LPCTSTR)pScriptLayout->GetTitle());
									sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
									sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								}
								if (nComponent == DATABASE_COMPONENTS_ANY || nComponent == ~DATABASE_COMPONENTS_ANY || nComponent == DATABASE_COMPONENTS_ALL || nComponent == ~DATABASE_COMPONENTS_ALL)
								{
									szItem.Format((nComponent == DATABASE_COMPONENTS_ALL || nComponent == ~DATABASE_COMPONENTS_ALL) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DATABASEALLITEMTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DATABASEANYITEMTEXT), pszName);
									sLogItem[0].itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
									sLogItem[0].itemex.iIntegral = CalcLines(szItem, szText, szUser);
								}
								if ((pLogEntry[1]->hItem = m_wndView.InsertItem(&sLogItem[0])))
								{
									if (m_wndView.SetItemData(pLogEntry[1]->hItem, (DWORD_PTR)pLogEntry[1])) break;
									m_wndView.DeleteItem(pLogEntry[1]->hItem);
								}
								GlobalFree(pLogEntry[1]->pData);
							}
							GlobalFree(pLogEntry[1]);
							pLogEntry[1] = (PWORKSPACELOGENTRY)NULL;
							break;
						}
						if ((nComponent == DATABASE_COMPONENTS_ANY || nComponent == ~DATABASE_COMPONENTS_ANY || nComponent == DATABASE_COMPONENTS_ALL || nComponent == ~DATABASE_COMPONENTS_ALL || pLogEntry[0] != (PWORKSPACELOGENTRY)NULL) && pLogEntry[1] != (PWORKSPACELOGENTRY)NULL)
						{
							m_wndView.Invalidate(FALSE);
							m_wndView.UpdateWindow();
							delete pLogInfo[1];
							return;
						}
					}
					m_pLogs.RemoveAt(nIndex);
				}
			}
			delete pLogInfo[1];
		}
		delete pLogInfo[0];
	}
	ShowMessage(SYSTEM_WARNING_DATABASELOG_UPDATE_FAILURE);
}
VOID CWorkspaceViewLogsPage::UpdateDatabaseLogs()
{
	TVITEM  sRootItem;
	CString  szLogRoot;

	for (ShowMessage((!GetDatabase()->ReadLog(m_pLogs)) ? SYSTEM_WARNING_DATABASELOG_READ_FAILURE : SYSTEM_NOERROR), szLogRoot.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ROOTSYMBOLTEXT), (LPCTSTR)GetAccountDatabase()), m_wndView.DeleteAllItems(); (sRootItem.hItem = m_wndView.InsertItem((GetDatabase()->IsOpen()) ? (LPCTSTR)szLogRoot : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ROOTNOSYMBOLTEXT), (GetDatabase()->IsOpen()) ? WORKSPACELOGSPAGE_ROOTSYMBOL : WORKSPACELOGSPAGE_ROOTNOSYMBOL, (GetDatabase()->IsOpen()) ? WORKSPACELOGSPAGE_ROOTSYMBOL : WORKSPACELOGSPAGE_ROOTNOSYMBOL, (HTREEITEM)NULL, (HTREEITEM)NULL)) && m_wndView.SetItemState(sRootItem.hItem, TVIS_BOLD, TVIS_BOLD); )
	{
		EnumTMPacketLogs(sRootItem.hItem, m_pLogs);
		EnumTCFunctionLogs(sRootItem.hItem, m_pLogs);
		EnumTCSequenceLogs(sRootItem.hItem, m_pLogs);
		EnumTCProcedureLogs(sRootItem.hItem, m_pLogs);
		EnumTMParameterLogs(sRootItem.hItem, m_pLogs);
		EnumTCParameterLogs(sRootItem.hItem, m_pLogs);
		EnumOBProcessorLogs(sRootItem.hItem, m_pLogs);
		EnumANDLogs(sRootItem.hItem, m_pLogs);
		EnumGRDLogs(sRootItem.hItem, m_pLogs);
		EnumMMDLogs(sRootItem.hItem, m_pLogs);
		EnumPODLogs(sRootItem.hItem, m_pLogs);
		EnumScriptLogs(sRootItem.hItem, m_pLogs);
		EnumLogs(sRootItem.hItem, m_pLogs);
		m_wndView.Expand(sRootItem.hItem, TVE_EXPAND);
		break;
	}
}

VOID CWorkspaceViewLogsPage::EnumTMPacketLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTMPacketItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindTMPacketFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindTMPacketFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hTMPacketItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_TMPACKET)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szName))); )
							{
								szItem.Format((!pDatabaseTMPacket->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMTEXT), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetTMPackets()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hTMPacketItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hTMPacketItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hTMPacketItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumTCFunctionLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCFunctionItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseTCFunction  *pDatabaseTCFunction;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindTCFunctionFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindTCFunctionFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hTCFunctionItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_TCFUNCTION)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pDatabaseTCFunction = GetDatabase()->GetTCFunctions()->GetAt(GetDatabase()->GetTCFunctions()->Find(szName))); )
							{
								szItem.Format((!pDatabaseTCFunction->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMTEXT), (LPCTSTR)pDatabaseTCFunction->GetName(), (LPCTSTR)pDatabaseTCFunction->GetDescription());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetTCFunctions()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hTCFunctionItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hTCFunctionItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hTCFunctionItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumTCSequenceLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCSequenceItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseTCSequence  *pDatabaseTCSequence;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindTCSequenceFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCESYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindTCSequenceFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hTCSequenceItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_TCSEQUENCE)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pDatabaseTCSequence = GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(szName))); )
							{
								szItem.Format((!pDatabaseTCSequence->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMTEXT), (LPCTSTR)pDatabaseTCSequence->GetName(), (LPCTSTR)pDatabaseTCSequence->GetDescription());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetTCSequences()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hTCSequenceItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hTCSequenceItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hTCSequenceItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumTCProcedureLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCProcedureItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseTCProcedure  *pDatabaseTCProcedure;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindTCProcedureFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDURESYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindTCProcedureFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hTCProcedureItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_TCPROCEDURE)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pDatabaseTCProcedure = GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(szName))); )
							{
								szItem.Format((!pDatabaseTCProcedure->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMTEXT), (LPCTSTR)pDatabaseTCProcedure->GetName(), (LPCTSTR)pDatabaseTCProcedure->GetDescription());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetTCProcedures()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hTCProcedureItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hTCProcedureItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hTCProcedureItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumTMParameterLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTMParameterItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindTMParameterFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindTMParameterFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hTMParameterItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_TMPARAMETER)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szName))); )
							{
								szItem.Format((!pDatabaseTMParameter->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMTEXT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetTMParameters()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hTMParameterItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hTMParameterItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hTMParameterItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumTCParameterLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hFolderItem;
	HTREEITEM  hTCParameterItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindTCParameterFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindTCParameterFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hTCParameterItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_TCPARAMETER)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pDatabaseTCParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(szName))); )
							{
								szItem.Format((!pDatabaseTCParameter->GetDescription().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMTEXT), (LPCTSTR)pDatabaseTCParameter->GetTag(), (LPCTSTR)pDatabaseTCParameter->GetDescription());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetTCParameters()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hTCParameterItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hTCParameterItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hTCParameterItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumOBProcessorLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hFolderItem;
	HTREEITEM  hOBProcessorItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindOBProcessorFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindOBProcessorFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hOBProcessorItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_OBPROCESSOR)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pDatabaseOBProcessor = GetDatabase()->GetOBProcessors()->GetAt(GetDatabase()->GetOBProcessors()->Find(szName))); )
							{
								szItem.Format((!pDatabaseOBProcessor->GetDescription().IsEmpty() || !pDatabaseOBProcessor->GetDetails().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMTEXT), (LPCTSTR)pDatabaseOBProcessor->GetName(), (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseOBProcessor->GetDescription() : (LPCTSTR)pDatabaseOBProcessor->GetDetails());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetOBProcessors()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hOBProcessorItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hOBProcessorItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hOBProcessorItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumANDLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hANDItem;
	HTREEITEM  hFolderItem;
	CANDLayout  *pANDLayout;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindANDFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindANDFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hANDItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_AND)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pANDLayout = GetDatabase()->GetANDs()->GetAt(GetDatabase()->GetANDs()->Find(szName))); )
							{
								szItem.Format((!pANDLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMTEXT), (LPCTSTR)pANDLayout->GetName(), (LPCTSTR)pANDLayout->GetTitle());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetANDs()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hANDItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hANDItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hANDItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumGRDLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hGRDItem;
	HTREEITEM  hFolderItem;
	CGRDLayout  *pGRDLayout;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindGRDFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindGRDFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hGRDItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_GRD)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pGRDLayout = GetDatabase()->GetGRDs()->GetAt(GetDatabase()->GetGRDs()->Find(szName))); )
							{
								szItem.Format((!pGRDLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMTEXT), (LPCTSTR)pGRDLayout->GetName(), (LPCTSTR)pGRDLayout->GetTitle());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetGRDs()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hGRDItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hGRDItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hGRDItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumMMDLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hMMDItem;
	HTREEITEM  hFolderItem;
	CMMDLayout  *pMMDLayout;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindMMDFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindMMDFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hMMDItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_MMD)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pMMDLayout = GetDatabase()->GetMMDs()->GetAt(GetDatabase()->GetMMDs()->Find(szName))); )
							{
								szItem.Format((!pMMDLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMTEXT), (LPCTSTR)pMMDLayout->GetName(), (LPCTSTR)pMMDLayout->GetTitle());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetMMDs()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hMMDItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hMMDItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hMMDItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumPODLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hPODItem;
	HTREEITEM  hFolderItem;
	CPODLayout  *pPODLayout;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindPODFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindPODFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hPODItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_POD)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pPODLayout = GetDatabase()->GetPODs()->GetAt(GetDatabase()->GetPODs()->Find(szName))); )
							{
								szItem.Format((!pPODLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMTEXT), (LPCTSTR)pPODLayout->GetName(), (LPCTSTR)pPODLayout->GetTitle());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetPODs()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hPODItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hPODItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hPODItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumScriptLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nPos;
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CByteArray  nInfo;
	HTREEITEM  hScriptItem;
	HTREEITEM  hFolderItem;
	CDatabaseLogInfo  *pLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	CAutomationScript  *pScriptLayout;
	TVINSERTSTRUCT  sItem;

	if ((hFolderItem = (!FindScriptFolder()) ? m_wndView.InsertItem(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTSYMBOLTEXT), I_IMAGECALLBACK, I_IMAGECALLBACK, hParentItem) : FindScriptFolder()))
	{
		for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hScriptItem = (HTREEITEM)NULL; nLog < nLogs; nLog++)
		{
			if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->Map(nInfo))
			{
				if (pLogInfo->GetLogType() == DATABASE_COMPONENT_SCRIPT)
				{
					if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))))
					{
						if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize())) != (LPBYTE)NULL)
						{
							for (sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE, sItem.itemex.pszText = (LPTSTR)(LPCTSTR)(szName = pLogInfo->GetLogName()), sItem.itemex.iIntegral = CalcLines(szName, (szText = pLogInfo->GetLogText()), (szUser = pLogInfo->GetLogUser())), sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL, sItem.hParent = hFolderItem, sItem.hInsertAfter = TVI_FIRST, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()), szItem = szName; (pScriptLayout = GetDatabase()->GetScripts()->GetAt(GetDatabase()->GetScripts()->Find(szName))); )
							{
								szItem.Format((!pScriptLayout->GetTitle().IsEmpty()) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMFULLTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMTEXT), (LPCTSTR)pScriptLayout->GetName(), (LPCTSTR)pScriptLayout->GetTitle());
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
								break;
							}
							if (GetDatabase()->GetScripts()->Find(szName) < 0)
							{
								szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMTEXT), (LPCTSTR)szName);
								szItem = szItem.Left(((nPos = szItem.ReverseFind(SPACE[0])) < 0) ? szItem.GetLength() : nPos);
								sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
								sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
							}
							if ((pLogEntry->hItem = hScriptItem = m_wndView.InsertItem(&sItem)))
							{
								if (m_wndView.SetItemData(hScriptItem, (DWORD_PTR)pLogEntry)) continue;
								m_wndView.DeleteItem(hScriptItem);
							}
							GlobalFree(pLogEntry->pData);
						}
						GlobalFree(pLogEntry);
					}
				}
			}
		}
	}
}

VOID CWorkspaceViewLogsPage::EnumLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs)
{
	INT  nLog;
	INT  nLogs;
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	CByteArray  nData;
	CByteArray  nInfo;
	HTREEITEM  hItem;
	HTREEITEM  hFolderItem;
	ULONGLONG  nComponent;
	CANDLayout  *pANDLayout;
	CGRDLayout  *pGRDLayout;
	CMMDLayout  *pMMDLayout;
	CPODLayout  *pPODLayout;
	CAutomationScript  *pScriptLayout;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CDatabaseTCFunction  *pDatabaseTCFunction;
	CDatabaseTCSequence  *pDatabaseTCSequence;
	CDatabaseTCProcedure  *pDatabaseTCProcedure;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;
	WORKSPACELOGENTRY  *pLogEntry;
	CDatabaseLogInfo  *pLogInfo;
	TVINSERTSTRUCT  sItem;

	for (nLog = 0, nLogs = (INT)pLogs.GetSize(), hFolderItem = m_wndView.GetRootItem(), hItem = (FindScriptFolder()) ? FindScriptFolder() : TVI_FIRST; nLog < nLogs; nLog++)
	{
		if ((pLogInfo = pLogs.GetAt(nLog)) && pLogInfo->GetLog(szName, szText, szUser, nComponent, tTime, nData) && pLogInfo->Map(nInfo))
		{
			if ((pLogEntry = (PWORKSPACELOGENTRY)GlobalAlloc(GPTR, sizeof(WORKSPACELOGENTRY))) != (PWORKSPACELOGENTRY)NULL)
			{
				if ((pLogEntry->pData = (LPBYTE)GlobalAlloc(GPTR, nInfo.GetSize()*sizeof(BYTE))) != (LPBYTE)NULL)
				{
					for (szItem = szName, CopyMemory(pLogEntry->pData, nInfo.GetData(), nInfo.GetSize()); nComponent == DATABASE_COMPONENT_TMPACKET; )
					{
						if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szName))) && !pDatabaseTMPacket->GetDescription().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pDatabaseTMPacket->GetDescription());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_TCFUNCTION; )
					{
						if ((pDatabaseTCFunction = GetDatabase()->GetTCFunctions()->GetAt(GetDatabase()->GetTCFunctions()->Find(szName))) && !pDatabaseTCFunction->GetDescription().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pDatabaseTCFunction->GetDescription());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_TCSEQUENCE; )
					{
						if ((pDatabaseTCSequence = GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(szName))) && !pDatabaseTCSequence->GetDescription().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pDatabaseTCSequence->GetDescription());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCEITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_TCPROCEDURE; )
					{
						if ((pDatabaseTCProcedure = GetDatabase()->GetTCProcedures()->GetAt(GetDatabase()->GetTCProcedures()->Find(szName))) && !pDatabaseTCProcedure->GetDescription().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pDatabaseTCProcedure->GetDescription());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDUREITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_TMPARAMETER; )
					{
						if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szName))) && !pDatabaseTMParameter->GetDescription().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pDatabaseTMParameter->GetDescription());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_TCPARAMETER; )
					{
						if ((pDatabaseTCParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(szName))) && !pDatabaseTCParameter->GetDescription().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pDatabaseTCParameter->GetDescription());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_OBPROCESSOR; )
					{
						if ((pDatabaseOBProcessor = GetDatabase()->GetOBProcessors()->GetAt(GetDatabase()->GetOBProcessors()->Find(szName))) && (!pDatabaseOBProcessor->GetDescription().IsEmpty() || !pDatabaseOBProcessor->GetDetails().IsEmpty()))
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMNAMEFULLTEXT), (LPCTSTR)szName, (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseOBProcessor->GetDescription() : (LPCTSTR)pDatabaseOBProcessor->GetDetails());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_AND; )
					{
						if ((pANDLayout = GetDatabase()->GetANDs()->GetAt(GetDatabase()->GetANDs()->Find(szName))) && !pANDLayout->GetTitle().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pANDLayout->GetTitle());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_GRD; )
					{
						if ((pGRDLayout = GetDatabase()->GetGRDs()->GetAt(GetDatabase()->GetGRDs()->Find(szName))) && !pGRDLayout->GetTitle().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pGRDLayout->GetTitle());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_MMD; )
					{
						if ((pMMDLayout = GetDatabase()->GetMMDs()->GetAt(GetDatabase()->GetMMDs()->Find(szName))) && !pMMDLayout->GetTitle().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pMMDLayout->GetTitle());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_POD; )
					{
						if ((pPODLayout = GetDatabase()->GetPODs()->GetAt(GetDatabase()->GetPODs()->Find(szName))) && !pPODLayout->GetTitle().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pPODLayout->GetTitle());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENT_SCRIPT; )
					{
						if ((pScriptLayout = GetDatabase()->GetScripts()->GetAt(GetDatabase()->GetScripts()->Find(szName))) && !pScriptLayout->GetTitle().IsEmpty())
						{
							szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMNAMEFULLTEXT), (LPCTSTR)szName, (LPCTSTR)pScriptLayout->GetTitle());
							break;
						}
						szItem.Format(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTITEMNAMETEXT), (LPCTSTR)szName);
						break;
					}
					for (; nComponent == DATABASE_COMPONENTS_ANY || nComponent == DATABASE_COMPONENTS_ALL; )
					{
						szItem.Format((nComponent == DATABASE_COMPONENTS_ALL) ? STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DATABASEALLITEMTEXT) : STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_DATABASEANYITEMTEXT), (LPCTSTR)szName);
						break;
					}
					sItem.hParent = hFolderItem;
					sItem.hInsertAfter = hItem;
					sItem.itemex.mask = TVIF_TEXT | TVIF_INTEGRAL | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
					sItem.itemex.pszText = (LPTSTR)(LPCTSTR)szItem;
					sItem.itemex.iIntegral = CalcLines(szItem, szText, szUser);
					sItem.itemex.iSelectedImage = WORKSPACELOGSPAGE_ENTRYSYMBOL;
					sItem.itemex.iImage = WORKSPACELOGSPAGE_ENTRYSYMBOL;
					if ((pLogEntry->hItem = m_wndView.InsertItem(&sItem)))
					{
						if (m_wndView.SetItemData(pLogEntry->hItem, (DWORD_PTR)pLogEntry)) continue;
						m_wndView.DeleteItem(pLogEntry->hItem);
					}
					GlobalFree(pLogEntry->pData);
				}
				GlobalFree(pLogEntry);
			}
		}
	}
}

HTREEITEM CWorkspaceViewLogsPage::FindTMPacketFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindTCFunctionFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindTCSequenceFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCESYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindTCProcedureFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDURESYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindTMParameterFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindTCParameterFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindOBProcessorFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindANDFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindGRDFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindMMDFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindPODFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindScriptFolder() CONST
{
	return FindFolder(STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTSYMBOLTEXT));
}

HTREEITEM CWorkspaceViewLogsPage::FindFolder(LPCTSTR pszFolder) CONST
{
	HTREEITEM  hFolderItem;

	for (hFolderItem = m_wndView.GetChildItem(m_wndView.GetRootItem()); hFolderItem; hFolderItem = m_wndView.GetNextItem(hFolderItem, TVGN_NEXT))
	{
		if (m_wndView.GetItemText(hFolderItem) == pszFolder) break;
		continue;
	}
	return hFolderItem;
}

INT CWorkspaceViewLogsPage::CalcLines(LPCTSTR pszName, LPCTSTR pszText, LPCTSTR pszUser) CONST
{
	INT  nCount;
	INT  nPos[2];
	CString  szText;

	for (nPos[0] = 0, szText = pszText, nCount = 0, nCount = (lstrlen(pszUser) > 0) ? (nCount + 1) : nCount; nPos[0] < lstrlen(pszText); )
	{
		if ((nPos[1] = szText.Mid(nPos[0]).Find(CString(CR))) >= 0)
		{
			for (; szText.GetAt(nPos[0] + nPos[1] + 1) == EOL; )
			{
				nPos[0]++;
				break;
			}
			nPos[0] += nPos[1] + 1;
			nCount++;
			continue;
		}
		if ((nPos[1] = szText.Mid(nPos[0]).Find(EOL)) >= 0)
		{
			nPos[0] += nPos[1] + 1;
			nCount++;
			continue;
		}
		nCount++;
		break;
	}
	return nCount + 1;
}

BEGIN_MESSAGE_MAP(CWorkspaceViewLogsPage, CWorkspaceViewPage)
	//{{AFX_MSG_MAP(CWorkspaceViewLogsPage)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPage message handlers

int CWorkspaceViewLogsPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	BITMAP  sBitmap;
	CBitmap  cBitmap[WORKSPACELOGSPAGE_SYMBOLS];

	if (CWorkspaceViewPage::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndView.Create(TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_NOTOOLTIPS | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0))
		{
			if (cBitmap[WORKSPACELOGSPAGE_ROOTSYMBOL].LoadBitmap(IDB_WORKSPACELOGSPAGEROOTSYMBOL) && cBitmap[WORKSPACELOGSPAGE_ROOTNOSYMBOL].LoadBitmap(IDB_WORKSPACELOGSPAGEROOTNOSYMBOL) && cBitmap[WORKSPACELOGSPAGE_FOLDERSYMBOL].LoadBitmap(IDB_WORKSPACELOGSPAGEFOLDERSYMBOL) && cBitmap[WORKSPACELOGSPAGE_FOLDEROPENSYMBOL].LoadBitmap(IDB_WORKSPACELOGSPAGEFOLDEROPENSYMBOL) && cBitmap[WORKSPACELOGSPAGE_ENTRYSYMBOL].LoadBitmap(IDB_WORKSPACELOGSPAGEENTRYSYMBOL) && cBitmap[WORKSPACELOGSPAGE_ROOTSYMBOL].GetObject(sizeof(BITMAP), &sBitmap) > 0)
			{
				if (m_pItems.Create(sBitmap.bmWidth, sBitmap.bmHeight, ILC_COLOR32, WORKSPACELOGSPAGE_SYMBOLS, 1))
				{
					m_pItems.Add(&cBitmap[WORKSPACELOGSPAGE_ROOTSYMBOL], (CBitmap *)NULL);
					m_pItems.Add(&cBitmap[WORKSPACELOGSPAGE_ROOTNOSYMBOL], (CBitmap *)NULL);
					m_pItems.Add(&cBitmap[WORKSPACELOGSPAGE_FOLDERSYMBOL], (CBitmap *)NULL);
					m_pItems.Add(&cBitmap[WORKSPACELOGSPAGE_FOLDEROPENSYMBOL], (CBitmap *)NULL);
					m_pItems.Add(&cBitmap[WORKSPACELOGSPAGE_ENTRYSYMBOL], (CBitmap *)NULL);
					if (m_pItems.GetImageCount() == WORKSPACELOGSPAGE_SYMBOLS)
					{
						m_wndView.SetImageList(&m_pItems, TVSIL_NORMAL);
						return 0;
					}
				}
			}
		}
	}
	return -1;
}

void CWorkspaceViewLogsPage::OnSize(UINT nType, int cx, int cy)
{
	m_wndView.MoveWindow(0, 0, cx, cy);
	CWorkspaceViewPage::OnSize(nType, cx, cy);
}

BOOL CWorkspaceViewLogsPage::OnEraseBkgnd(CDC *pDC)
{
	CRect  rPage[2];

	for (GetWindowRect(rPage[0]), GetParent()->ScreenToClient(rPage[0]), GetParent()->CalcClientRect(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		MoveWindow(rPage[1]);
		return TRUE;
	}
	for (GetClientRect(rPage[0]), m_wndView.GetWindowRect(rPage[1]), GetParent()->ScreenToClient(rPage[1]); !rPage[0].EqualRect(rPage[1]); )
	{
		m_wndView.MoveWindow(rPage[0], FALSE);
		m_wndView.RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
		return TRUE;
	}
	return CWorkspaceViewPage::OnEraseBkgnd(pDC);
}

void CWorkspaceViewLogsPage::OnPaint()
{
	m_wndView.UpdateWindow();
	CWorkspaceViewPage::OnPaint();
}

void CWorkspaceViewLogsPage::OnSetFocus(CWnd *pOldWnd)
{
	m_wndView.SetFocus();
}

BOOL CWorkspaceViewLogsPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CDC  cDC;
	INT  nCount;
	UINT  nOldMode;
	BOOL  bResized;
	RECT  rItemText;
	CSize  size[3];
	CRect  rView;
	CRect  rItem;
	CRect  rResult;
	CFont  *pOldFont;
	CPoint  ptCursor;
	SIZE_T  tSize[1];
	CString  szName;
	CString  szItem;
	CString  szText;
	CString  szUser;
	CTimeKey  tTime;
	COLORREF  nOldColor;
	ULONGLONG  nComponent;
	CByteArray  nData;
	CByteArray  nInfo;
	CStringTools  cStringTools;
	CDatabaseLogInfo  cLogInfo;
	WORKSPACELOGENTRY  *pLogEntry;
	NMMOUSE  *pNotifyMouseInfo = (NMMOUSE *)lParam;
	NMTREEVIEW  *pNotifyTreeInfo = (NMTREEVIEW *)lParam;
	NMTVDISPINFO  *pNotifyDispInfo = (NMTVDISPINFO *)lParam;
	NMTVCUSTOMDRAW  *pNotifyDrawInfo = (NMTVCUSTOMDRAW *)lParam;

	GetCursorPos(&ptCursor);
	ScreenToClient(&ptCursor);
	m_wndView.GetClientRect(rView);
	if (pNotifyMouseInfo->hdr.code == NM_SETCURSOR)
	{
		if (m_wndView.GetItemRect((HTREEITEM)pNotifyMouseInfo->dwItemSpec, rItem, TRUE))
		{
			if (rResult.IntersectRect(rView, rItem) && !rResult.EqualRect(rItem) && rItem.PtInRect(ptCursor))
			{
				if ((pLogEntry = (PWORKSPACELOGENTRY)m_wndView.GetItemData((HTREEITEM)pNotifyMouseInfo->dwItemSpec)))
				{
					for (szItem = m_wndView.GetItemText(pLogEntry->hItem), m_wndView.ClientToScreen(rItem), nInfo.SetSize((tSize[0] = GlobalSize(pLogEntry->pData))), CopyMemory(nInfo.GetData(), pLogEntry->pData, tSize[0]); cLogInfo.Unmap(nInfo) && cLogInfo.GetLog(szName, szText, szUser, nComponent, tTime, nData); )
					{
						m_wndToolTip.ShowTip(&m_wndView, szItem + CR + EOL + szText + CR + EOL + szUser, rItem, FALSE);
						return FALSE;
					}
				}
				for (szItem = m_wndView.GetItemText((HTREEITEM)pNotifyMouseInfo->dwItemSpec), m_wndView.ClientToScreen(rItem); TRUE; )
				{
					m_wndToolTip.ShowTip(&m_wndView, szItem, rItem, (m_wndView.GetRootItem() == (HTREEITEM)pNotifyMouseInfo->dwItemSpec) ? TRUE : FALSE);
					return FALSE;
				}
			}
		}
		m_wndToolTip.DeleteTip();
		return FALSE;
	}
	if (pNotifyDrawInfo->nmcd.hdr.code == NM_CUSTOMDRAW)
	{
		if (pNotifyDrawInfo->nmcd.dwDrawStage != CDDS_PREPAINT)
		{
			if ((pLogEntry = (pNotifyDrawInfo->nmcd.dwDrawStage == CDDS_ITEMPREPAINT || pNotifyDrawInfo->nmcd.dwDrawStage == CDDS_ITEMPOSTPAINT) ? (PWORKSPACELOGENTRY)pNotifyDrawInfo->nmcd.lItemlParam : (PWORKSPACELOGENTRY)NULL))
			{
				for (szItem = m_wndView.GetItemText(pLogEntry->hItem), m_wndView.GetItemRect(pLogEntry->hItem, &rItemText, TRUE), nInfo.SetSize((tSize[0] = GlobalSize(pLogEntry->pData))), CopyMemory(nInfo.GetData(), pLogEntry->pData, tSize[0]); cLogInfo.Unmap(nInfo) && cLogInfo.GetLog(szName, szText, szUser, nComponent, tTime, nData); )
				{
					if (pNotifyDrawInfo->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
					{
						if (cDC.Attach(pNotifyDrawInfo->nmcd.hdc))
						{
							if ((pOldFont = cDC.SelectObject(m_wndView.GetFont())))
							{
								size[0] = cDC.GetTextExtent(szItem);
								size[1] = cDC.GetTextExtent(szText);
								size[2] = cDC.GetTextExtent(szUser);
								if (size[0].cx < max(size[1].cx, size[2].cx))
								{
									nCount = (max(size[1].cx, size[2].cx) - size[0].cx) / cDC.GetTextExtent(SPACE).cx + 1;
									m_wndView.SetItemText(pLogEntry->hItem, szItem + CString(SPACE[0], nCount));
								}
								else if (size[0].cx > max(size[1].cx, size[2].cx))
								{
									for (bResized = FALSE; szItem.GetLength() > 0 && _istspace(szItem.Right(1).GetAt(0)); )
									{
										if (cDC.GetTextExtent(szItem.Left(szItem.GetLength() - 1)).cx >= max(size[1].cx, size[2].cx))
										{
											szItem = szItem.Left(szItem.GetLength() - 1);
											bResized = TRUE;
											continue;
										}
										break;
									}
									for (; bResized; )
									{
										m_wndView.SetItemText(pLogEntry->hItem, szItem);
										break;
									}
								}
								cDC.SelectObject(pOldFont);
							}
							cDC.Detach();
						}
						*pResult = CDRF_NOTIFYPOSTPAINT;
						return TRUE;
					}
					if (pNotifyDrawInfo->nmcd.dwDrawStage == CDDS_ITEMPOSTPAINT)
					{
						if (cDC.Attach(pNotifyDrawInfo->nmcd.hdc))
						{
							if ((pOldFont = cDC.SelectObject(m_wndView.GetFont())))
							{
								size[0] = cDC.GetTextExtent(szItem);
								size[1] = cDC.GetTextExtent(szText);
								nOldMode = cDC.SetBkMode(TRANSPARENT);
								nOldColor = cDC.SetTextColor(pNotifyDrawInfo->clrText);
								cDC.TextOut(rItemText.left + 2 * GetSystemMetrics(SM_CXBORDER), rItemText.top + GetSystemMetrics(SM_CYBORDER) + size[0].cy, szText);
								cDC.TextOut(rItemText.left + 2 * GetSystemMetrics(SM_CXBORDER), rItemText.top + GetSystemMetrics(SM_CYBORDER) + size[0].cy + size[1].cy, szUser);
								cDC.SelectObject(pOldFont);
								cDC.SetTextColor(nOldColor);
								cDC.SetBkMode(nOldMode);
							}
							cDC.Detach();
						}
						*pResult = CDRF_DODEFAULT;
						return TRUE;
					}
				}
			}
		}
		*pResult = (pNotifyDrawInfo->nmcd.dwDrawStage == CDDS_PREPAINT) ? CDRF_NOTIFYITEMDRAW : CDRF_DODEFAULT;
		return TRUE;
	}
	if (pNotifyDispInfo->hdr.code == TVN_GETDISPINFO)
	{
		if ((szItem = m_wndView.GetItemText(pNotifyDispInfo->item.hItem)) == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPACKETSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCFUNCTIONSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCSEQUENCESYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPROCEDURESYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TMPARAMETERSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_TCPARAMETERSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_OBPROCESSORSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_ANDSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_GRDSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_MMDSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_PODSYMBOLTEXT) || szItem == STRING(IDS_WORKSPACEWINDOW_LOGSPAGE_SCRIPTSYMBOLTEXT))
		{
			if (pNotifyDispInfo->item.mask & TVIF_IMAGE) pNotifyDispInfo->item.iImage = ((m_wndView.GetItemState(pNotifyDispInfo->item.hItem, TVIF_STATE) & TVIS_EXPANDED) && m_wndView.ItemHasChildren(pNotifyDispInfo->item.hItem)) ? WORKSPACELOGSPAGE_FOLDEROPENSYMBOL : WORKSPACELOGSPAGE_FOLDERSYMBOL;
			if (pNotifyDispInfo->item.mask & TVIF_SELECTEDIMAGE) pNotifyDispInfo->item.iSelectedImage = ((m_wndView.GetItemState(pNotifyDispInfo->item.hItem, TVIF_STATE) & TVIS_EXPANDED) && m_wndView.ItemHasChildren(pNotifyDispInfo->item.hItem)) ? WORKSPACELOGSPAGE_FOLDEROPENSYMBOL : WORKSPACELOGSPAGE_FOLDERSYMBOL;
		}
	}
	if (pNotifyTreeInfo->hdr.code == TVN_DELETEITEM)
	{
		if ((pLogEntry = (PWORKSPACELOGENTRY)m_wndView.GetItemData(pNotifyTreeInfo->itemOld.hItem)))
		{
			m_wndView.SetItemData(pNotifyTreeInfo->itemOld.hItem, (DWORD_PTR)NULL);
			GlobalFree(pLogEntry->pData);
			GlobalFree(pLogEntry);
		}
	}
	return CWorkspaceViewPage::OnNotify(wParam, lParam, pResult);
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView

IMPLEMENT_DYNCREATE(CWorkspaceView, CWnd)

CWorkspaceView::CWorkspaceView() : CWnd()
{
	m_nPage = 0;
	m_nPagePos = 0;
	m_nState[0] = 0;
	m_nState[1] = 0;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CWorkspaceView::Create(CWnd *pParentWnd)
{
	return CWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), EMPTYSTRING, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), 0);
}

VOID CWorkspaceView::SetCurPage(LPCTSTR pszPage)
{
	INT  nPage;
	INT  nPages;

	for (nPage = 0, nPages = (INT)m_szPages.GetSize(); nPage < nPages; nPage++)
	{
		if (m_szPages.GetAt(nPage) == pszPage)
		{
			SetCurPage(nPage);
			break;
		}
	}
}
VOID CWorkspaceView::SetCurPage(INT nPage)
{
	CRect  rPage;
	CUIntArray  nPageTabsPos;
	CWorkspaceViewPage  *pPage;

	if (m_nPage != nPage)
	{
		if ((pPage = (CWorkspaceViewPage *)m_pwndPages.GetAt((m_nPage = nPage))))
		{
			pPage->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
			pPage->GetWindowRect(rPage);
			ScreenToClient(rPage);
			InvalidateRect(CRect(rPage.left, rPage.bottom, rPage.right, rPage.bottom + WORKSPACEVIEW_FRAME_SIZE), FALSE);
		}
	}
}

INT CWorkspaceView::GetCurPage(CString &szPage) CONST
{
	szPage = m_szPages.GetAt(GetCurPage());
	return m_nPage;
}
INT CWorkspaceView::GetCurPage() CONST
{
	return m_nPage;
}

VOID CWorkspaceView::UpdateDatabaseContents(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pDatabaseTMPacket, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pDatabaseTCFunction, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pDatabaseTMParameter, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pDatabaseTCParameter, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pDatabaseOBProcessor, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pANDWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pGRDWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pMMDWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pPODWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents(pScriptWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseContents()
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->UpdateDatabaseContents();
	}
}

VOID CWorkspaceView::UpdateDatabaseProcedures(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	if ((pProceduresPage = GetProceduresPage()))
	{
		pProceduresPage->UpdateDatabaseProcedures(pDatabaseTCSequence, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseProcedures(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	if ((pProceduresPage = GetProceduresPage()))
	{
		pProceduresPage->UpdateDatabaseProcedures(pDatabaseTCProcedure, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseProcedures(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	if ((pProceduresPage = GetProceduresPage()))
	{
		pProceduresPage->UpdateDatabaseProcedures(pTCSequenceWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseProcedures()
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	if ((pProceduresPage = GetProceduresPage()))
	{
		pProceduresPage->UpdateDatabaseProcedures();
	}
}

VOID CWorkspaceView::UpdateDatabaseLogs(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pDatabaseTMPacket, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pDatabaseTCFunction, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pDatabaseTCSequence, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pDatabaseTCProcedure, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pDatabaseTMParameter, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pDatabaseTCParameter, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pDatabaseOBProcessor, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pTCSequenceWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pANDWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pGRDWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pMMDWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pPODWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(pScriptWnd, nPosition, bDelete);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs(ULONGLONG nComponent, LPCTSTR pszName)
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs(nComponent, pszName);
	}
}
VOID CWorkspaceView::UpdateDatabaseLogs()
{
	CWorkspaceViewLogsPage  *pLogsPage;

	if ((pLogsPage = GetLogsPage()))
	{
		pLogsPage->UpdateDatabaseLogs();
	}
}

BOOL CWorkspaceView::CreateDatabaseItem()
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	return(((pDatabasePage = GetDatabasePage())) ? pDatabasePage->CreateDatabaseItem() : FALSE);
}

BOOL CWorkspaceView::OpenDatabaseItem()
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	return(((pDatabasePage = GetDatabasePage())) ? pDatabasePage->OpenDatabaseItem() : FALSE);
}

BOOL CWorkspaceView::HasDatabaseItem(INT nType) CONST
{
	CWorkspaceViewDatabasePage  *pDatabasePage;
	CWorkspaceViewProceduresPage  *pProceduresPage;

	switch (nType)
	{
	case DATABASE_COMPONENT_TMPACKET:
	case DATABASE_COMPONENT_TCFUNCTION:
	case DATABASE_COMPONENT_TMPARAMETER:
	case DATABASE_COMPONENT_TCPARAMETER:
	case DATABASE_COMPONENT_OBPROCESSOR:
	case DATABASE_COMPONENT_AND:
	case DATABASE_COMPONENT_GRD:
	case DATABASE_COMPONENT_MMD:
	case DATABASE_COMPONENT_POD:
	case DATABASE_COMPONENT_SCRIPT:
	{ return(((pDatabasePage = GetDatabasePage())) ? pDatabasePage->HasDatabaseItem(nType) : FALSE);
	break;
	}
	case DATABASE_COMPONENT_TCSEQUENCE:
	case DATABASE_COMPONENT_TCPROCEDURE:
	{ return(((pProceduresPage = GetProceduresPage())) ? pProceduresPage->HasProceduresItem(nType) : FALSE);
	break;
	}
	}
	return FALSE;
}

BOOL CWorkspaceView::RenameDatabaseItem()
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	return(((pDatabasePage = GetDatabasePage())) ? pDatabasePage->RenameDatabaseItem() : FALSE);
}

BOOL CWorkspaceView::DeleteDatabaseItem()
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	return(((pDatabasePage = GetDatabasePage())) ? pDatabasePage->DeleteDatabaseItem() : FALSE);
}

BOOL CWorkspaceView::CreateProceduresItem()
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	return(((pProceduresPage = GetProceduresPage())) ? pProceduresPage->CreateProceduresItem() : FALSE);
}

BOOL CWorkspaceView::OpenProceduresItem()
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	return(((pProceduresPage = GetProceduresPage())) ? pProceduresPage->OpenProceduresItem() : FALSE);
}

BOOL CWorkspaceView::HasProceduresItem(INT nType) CONST
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	return(((pProceduresPage = GetProceduresPage())) ? pProceduresPage->HasProceduresItem(nType) : FALSE);
}

BOOL CWorkspaceView::RenameProceduresItem()
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	return(((pProceduresPage = GetProceduresPage())) ? pProceduresPage->RenameProceduresItem() : FALSE);
}

BOOL CWorkspaceView::DeleteProceduresItem()
{
	CWorkspaceViewProceduresPage  *pProceduresPage;

	return(((pProceduresPage = GetProceduresPage())) ? pProceduresPage->DeleteProceduresItem() : FALSE);
}

BOOL CWorkspaceView::CanDeleteSel() CONST
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	return(((pDatabasePage = GetDatabasePage())) ? pDatabasePage->CanDeleteSel() : FALSE);
}

VOID CWorkspaceView::DoDeleteSel()
{
	CWorkspaceViewDatabasePage  *pDatabasePage;

	if ((pDatabasePage = GetDatabasePage()))
	{
		pDatabasePage->DoDeleteSel();
	}
}

CWorkspaceViewDatabasePage *CWorkspaceView::GetDatabasePage() CONST
{
	return((CWorkspaceViewDatabasePage *)FindPage(STRING(IDS_WORKSPACEWINDOW_DATABASETAB)));
}

CWorkspaceViewProceduresPage *CWorkspaceView::GetProceduresPage() CONST
{
	return((CWorkspaceViewProceduresPage *)FindPage(STRING(IDS_WORKSPACEWINDOW_PROCEDURESTAB)));
}

CWorkspaceViewLogsPage *CWorkspaceView::GetLogsPage() CONST
{
	return((CWorkspaceViewLogsPage *)FindPage(STRING(IDS_WORKSPACEWINDOW_LOGSTAB)));
}

VOID CWorkspaceView::SetParent(class CWorkspaceWnd *pParentWnd)
{
	CWnd::SetParent((m_pParentWnd = pParentWnd));
}

CWorkspaceWnd *CWorkspaceView::GetParent() CONST
{
	return((CWorkspaceWnd *)m_pParentWnd);
}

CWorkspaceViewPage *CWorkspaceView::FindPage(LPCTSTR pszPage) CONST
{
	INT  nPage;
	INT  nPages;

	for (nPage = 0, nPages = (INT)m_szPages.GetSize(); nPage < nPages; nPage++)
	{
		if (m_szPages.GetAt(nPage) == pszPage) break;
		continue;
	}
	return((nPage < nPages) ? (CWorkspaceViewPage *)m_pwndPages.GetAt(nPage) : (CWorkspaceViewPage *)NULL);
}

VOID CWorkspaceView::CalcClientRect(LPRECT lpRect, BOOL bMargin)
{
	CRect  rView;

	GetClientRect(rView);
	SetRect(lpRect, (!bMargin) ? (rView.left + WORKSPACEVIEW_FRAME_SIZE) : rView.left, (!bMargin) ? (rView.top + WORKSPACEVIEW_FRAME_SIZE) : rView.top, (!bMargin) ? (rView.right - WORKSPACEVIEW_FRAME_SIZE) : rView.right, (!bMargin) ? (rView.bottom - CalcTabsExtent().cy - WORKSPACEVIEW_FRAME_SIZE) : (rView.bottom - CalcTabsExtent().cy));
}

CSize CWorkspaceView::CalcTabsExtent()
{
	CUIntArray  nTabsPos;

	return CalcTabsExtent(nTabsPos);
}
CSize CWorkspaceView::CalcTabsExtent(CUIntArray &nTabsPos)
{
	INT  nPage;
	INT  nPages;

	for (nPage = 0, nPages = (INT)m_pwndPages.GetSize(), nTabsPos.RemoveAll(); nPage < nPages; nPage++)
	{
		nTabsPos.Add((nPage) ? (nTabsPos.GetAt(nPage - 1) + CalcTabExtent(nPage).cx) : CalcTabExtent(nPage).cx);
		continue;
	}
	return CSize(nTabsPos.GetAt(nTabsPos.GetUpperBound()), CalcTabExtent(0).cy);
}

CSize CWorkspaceView::CalcTabExtent(INT nTab)
{
	CDC  *pDC;
	CSize  sizeTab;
	CFont  *pOldFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_fntPages)))
		{
			sizeTab = CSize(3 * WORKSPACEVIEW_FRAME_SIZE, 3 * GetSystemMetrics(SM_CYEDGE));
			if (m_szPages.GetAt(nTab) == STRING(IDS_WORKSPACEWINDOW_DATABASETAB))
			{
				sizeTab.cx += pDC->GetTextExtent(m_szPages.GetAt(nTab), m_szPages.GetAt(nTab).GetLength()).cx + m_cSymbol[WORKSPACEVIEW_DATABASEPAGE_SYMBOL].GetWidth();
				sizeTab.cy += m_cSymbol[WORKSPACEVIEW_DATABASEPAGE_SYMBOL].GetHeight();
			}
			if (m_szPages.GetAt(nTab) == STRING(IDS_WORKSPACEWINDOW_PROCEDURESTAB))
			{
				sizeTab.cx += pDC->GetTextExtent(m_szPages.GetAt(nTab), m_szPages.GetAt(nTab).GetLength()).cx + m_cSymbol[WORKSPACEVIEW_PROCEDURESPAGE_SYMBOL].GetWidth();
				sizeTab.cy += m_cSymbol[WORKSPACEVIEW_PROCEDURESPAGE_SYMBOL].GetHeight();
			}
			if (m_szPages.GetAt(nTab) == STRING(IDS_WORKSPACEWINDOW_LOGSTAB))
			{
				sizeTab.cx += pDC->GetTextExtent(m_szPages.GetAt(nTab), m_szPages.GetAt(nTab).GetLength()).cx + m_cSymbol[WORKSPACEVIEW_LOGSPAGE_SYMBOL].GetWidth();
				sizeTab.cy += m_cSymbol[WORKSPACEVIEW_LOGSPAGE_SYMBOL].GetHeight();
			}
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return CSize(sizeTab);
		}
		ReleaseDC(pDC);
	}
	return CSize(0, 0);
}

CSize CWorkspaceView::CalcScrollButtonSize() CONST
{
	BITMAP  sBitmap[2];
	CBitmap  cBitmap[2];

	return((cBitmap[0].LoadBitmap(IDB_WORKSPACESCROLLLEFTBUTTON) && cBitmap[1].LoadBitmap(IDB_WORKSPACESCROLLRIGHTBUTTON) && cBitmap[0].GetObject(sizeof(sBitmap[0]), &sBitmap[0]) && cBitmap[1].GetObject(sizeof(sBitmap[1]), &sBitmap[1])) ? CSize(max(sBitmap[0].bmWidth, sBitmap[1].bmWidth), max(sBitmap[0].bmHeight, sBitmap[1].bmHeight)) : CSize(0, 0));
}

VOID CWorkspaceView::CalcScrollLButtonPosition(LPRECT pRect)
{
	CRect  rView;
	CSize  sizeButton;

	CalcClientRect(rView, TRUE);
	sizeButton = CalcScrollButtonSize();
	SetRect(pRect, rView.right - WORKSPACEVIEW_FRAME_SIZE - 2 * sizeButton.cx, rView.bottom, rView.right - WORKSPACEVIEW_FRAME_SIZE - sizeButton.cx, rView.bottom + sizeButton.cy);
}

VOID CWorkspaceView::CalcScrollRButtonPosition(LPRECT pRect)
{
	CRect  rView;
	CSize  sizeButton;

	CalcClientRect(rView, TRUE);
	sizeButton = CalcScrollButtonSize();
	SetRect(pRect, rView.right - WORKSPACEVIEW_FRAME_SIZE - sizeButton.cx, rView.bottom, rView.right - WORKSPACEVIEW_FRAME_SIZE, rView.bottom + sizeButton.cy);
}

INT CWorkspaceView::CalcScrollPosition()
{
	INT  nTab;
	INT  nTabs;
	CRect  rTabs;
	CUIntArray  nTabsPos;

	CalcClientRect(rTabs);
	CalcTabsExtent(nTabsPos);
	for (nTab = 0, nTabs = (INT)nTabsPos.GetSize(); nTab < nTabs; nTab++)
	{
		if (rTabs.Width() - WORKSPACEVIEW_FRAME_SIZE - 2 * CalcScrollButtonSize().cx + 1 >= (INT)nTabsPos.GetAt(nTab)) continue;
		break;
	}
	return max(nTab - nTabs, -nTabs + 1);
}

VOID CWorkspaceView::DrawViewPages(CDC *pDC)
{
	INT  nPage;
	INT  nPages;
	INT  nIndex;
	INT  cxPage;
	INT  cyPage;
	INT  nWidth;
	INT  nHeight;
	INT  nBkMode;
	CPen  cPen[4];
	CPen  *pOldPen;
	CFont  *pOldFont;
	CRect  rView[2];
	CRect  rButton[2];
	CImage  cTabSymbol;
	TEXTMETRIC  tmFont;
	CUIntArray  nTabsPos;
	COLORREF  nOldColor;

	GetClientRect(rView[0]);
	CalcClientRect(rView[1], TRUE);
	CalcScrollLButtonPosition(rButton[0]);
	CalcScrollRButtonPosition(rButton[1]);
	if (cPen[0].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)) && cPen[1].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DSHADOW)) && cPen[2].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DHIGHLIGHT)) && cPen[3].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DFACE)))
	{
		if ((pOldPen = pDC->SelectObject(&cPen[0])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].left + TOOLWINDOW_FRAME_SIZE + 1, rView[1].bottom - 1);
			pDC->MoveTo(rView[1].right - 2 * (TOOLWINDOW_FRAME_SIZE + CalcScrollButtonSize().cx + 1), rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].top - 1);
			pDC->SelectObject(pOldPen);
			rView[1].bottom--;
			rView[1].right--;
		}
		if ((pOldPen = pDC->SelectObject(&cPen[2])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].left, rView[1].top);
			pDC->LineTo(rView[1].right, rView[1].top);
			pDC->SelectObject(pOldPen);
			rView[1].left++;
			rView[1].top++;
		}
		if ((pOldPen = pDC->SelectObject(&cPen[1])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].left + TOOLWINDOW_FRAME_SIZE, rView[1].bottom - 1);
			pDC->MoveTo(rView[1].right - 2 * (TOOLWINDOW_FRAME_SIZE + CalcScrollButtonSize().cx + 1), rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].top - 1);
			pDC->SelectObject(pOldPen);
			rView[1].bottom--;
			rView[1].right--;
		}
		if ((pOldPen = pDC->SelectObject(&cPen[3])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].left, rView[1].top);
			pDC->LineTo(rView[1].right, rView[1].top);
			pDC->SelectObject(pOldPen);
			rView[1].left++;
			rView[1].top++;
		}
		pDC->FrameRect(rView[1], CBrush::FromHandle(GetSysColorBrush(COLOR_3DFACE)));
		pDC->FrameRect((rView[1] = CRect(rView[1].left + 1, rView[1].top + 1, rView[1].right - 1, rView[1].bottom - 1)), CBrush::FromHandle(GetSysColorBrush(COLOR_3DFACE)));
		rView[1].SetRect(rView[1].left + 1, rView[1].top + 1, rView[1].right - 1, rView[1].bottom - 1);
		if ((pOldPen = pDC->SelectObject(&cPen[2])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].top - 1);
			pDC->SelectObject(pOldPen);
			rView[1].bottom--;
			rView[1].right--;
		}
		if ((pOldPen = pDC->SelectObject(&cPen[1])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].left, rView[1].top);
			pDC->LineTo(rView[1].right, rView[1].top);
			pDC->SelectObject(pOldPen);
			rView[1].left++;
			rView[1].top++;
		}
		if ((pOldPen = pDC->SelectObject(&cPen[3])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].bottom - 1);
			pDC->LineTo(rView[1].right - 1, rView[1].top - 1);
			pDC->SelectObject(pOldPen);
			rView[1].bottom--;
			rView[1].right--;
		}
		if ((pOldPen = pDC->SelectObject(&cPen[0])))
		{
			pDC->MoveTo(rView[1].left, rView[1].bottom - 1);
			pDC->LineTo(rView[1].left, rView[1].top);
			pDC->LineTo(rView[1].right, rView[1].top);
			pDC->SelectObject(pOldPen);
			rView[1].left++;
			rView[1].top++;
		}
		DrawScrollLButton(pDC);
		DrawScrollRButton(pDC);
		pDC->FillSolidRect(CRect(rView[0].left, rButton[0].top, rView[0].left + WORKSPACEVIEW_FRAME_SIZE, rView[0].bottom), GetSysColor(COLOR_3DFACE));
		pDC->FillSolidRect(CRect(rButton[0].left - WORKSPACEVIEW_FRAME_SIZE, rButton[0].top, rButton[0].left, rView[0].bottom), GetSysColor(COLOR_3DFACE));
		pDC->FillSolidRect(CRect(rButton[0].left, rButton[0].bottom, rView[0].right, rView[0].bottom), GetSysColor(COLOR_3DFACE));
		pDC->FillSolidRect(CRect(rButton[1].right, rButton[1].top, rView[0].right, rView[0].bottom), GetSysColor(COLOR_3DFACE));
		pDC->ExcludeClipRect(rButton[0].left - WORKSPACEVIEW_FRAME_SIZE, rButton[0].top - GetSystemMetrics(SM_CYEDGE), rView[0].right, rView[0].bottom);
		pDC->ExcludeClipRect(rView[1].right, rView[0].top, rView[0].right, rView[0].bottom);
		for (nPage = abs(m_nPagePos), nPages = (INT)m_pwndPages.GetSize(), CalcTabsExtent(nTabsPos), cxPage = rView[0].left + WORKSPACEVIEW_FRAME_SIZE, cyPage = rView[0].bottom - rButton[0].top, nWidth = (nPage) ? (nTabsPos.GetAt(nPage) - nTabsPos.GetAt(nPage - 1)) : nTabsPos.GetAt(0); nPage < nPages && cxPage < rButton[0].left - WORKSPACEVIEW_FRAME_SIZE; nPage++, nWidth = (nPage < nPages) ? (nTabsPos.GetAt(nPage) - nTabsPos.GetAt(nPage - 1)) : nWidth)
		{
			pDC->FillRect(CRect(cxPage + 1, (nPage == GetCurPage()) ? (rButton[0].top - GetSystemMetrics(SM_CYEDGE)) : rButton[0].top, (cxPage < min(cxPage + nWidth - GetSystemMetrics(SM_CXEDGE), rButton[0].left - WORKSPACEVIEW_FRAME_SIZE) - 1) ? min(cxPage + nWidth - GetSystemMetrics(SM_CXEDGE), rButton[0].left - WORKSPACEVIEW_FRAME_SIZE) : (cxPage + 1), rView[0].bottom - GetSystemMetrics(SM_CYEDGE)), CBrush::FromHandle(GetSysColorBrush(COLOR_3DFACE)));
			if ((pOldPen = (CPen *)pDC->SelectObject(&cPen[2])) != (CPen *)NULL)
			{
				pDC->MoveTo(cxPage, (nPage == GetCurPage()) ? (rButton[0].top - GetSystemMetrics(SM_CYEDGE)) : rButton[0].top);
				pDC->LineTo(cxPage, rView[0].bottom - GetSystemMetrics(SM_CYEDGE));
				pDC->SelectObject(pOldPen);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[3])))
			{
				pDC->MoveTo(cxPage, rView[0].bottom - GetSystemMetrics(SM_CYEDGE));
				pDC->LineTo(cxPage, rView[0].bottom - 1);
				pDC->LineTo(cxPage + GetSystemMetrics(SM_CXEDGE), rView[0].bottom - 1);
				pDC->MoveTo(cxPage + nWidth - GetSystemMetrics(SM_CXEDGE), rView[0].bottom - 1);
				pDC->LineTo(cxPage + nWidth - 1, rView[0].bottom - 1);
				pDC->LineTo(cxPage + nWidth - 1, rView[0].bottom - GetSystemMetrics(SM_CYEDGE) - 1);
				pDC->SelectObject(pOldPen);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[0])))
			{
				pDC->MoveTo(cxPage + GetSystemMetrics(SM_CXEDGE), rView[0].bottom - 1);
				pDC->LineTo(cxPage + nWidth - GetSystemMetrics(SM_CXEDGE) - 1, rView[0].bottom - 1);
				pDC->LineTo(cxPage + nWidth - 1, rView[0].bottom - GetSystemMetrics(SM_CYEDGE) - 1);
				pDC->LineTo(cxPage + nWidth - 1, (nPage == GetCurPage()) ? (rButton[0].top - GetSystemMetrics(SM_CYEDGE)) : (rButton[0].top - 1));
				if (nPage != GetCurPage())
				{
					pDC->MoveTo(cxPage, rButton[0].top - 1);
					pDC->LineTo(cxPage + nWidth, rButton[0].top - 1);
				}
				pDC->SelectObject(pOldPen);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[1])))
			{
				pDC->MoveTo(cxPage + 1, rView[0].bottom - GetSystemMetrics(SM_CYEDGE) - 1);
				pDC->LineTo(cxPage + 1, rView[0].bottom - GetSystemMetrics(SM_CYEDGE));
				pDC->LineTo(cxPage + nWidth - 1, rView[0].bottom - GetSystemMetrics(SM_CYEDGE));
				pDC->MoveTo(cxPage + nWidth - GetSystemMetrics(SM_CXEDGE), rView[0].bottom - GetSystemMetrics(SM_CYEDGE));
				pDC->LineTo(cxPage + nWidth - GetSystemMetrics(SM_CXEDGE), (nPage == GetCurPage()) ? (rButton[0].top - GetSystemMetrics(SM_CYEDGE) - 1) : (rButton[0].top - 1));
				pDC->MoveTo(cxPage + nWidth - GetSystemMetrics(SM_CXEDGE), rButton[0].top - GetSystemMetrics(SM_CYEDGE));
				pDC->LineTo(cxPage + nWidth, rButton[0].top - GetSystemMetrics(SM_CYEDGE));
				if (nPage != GetCurPage())
				{
					pDC->MoveTo(cxPage, rButton[0].top - GetSystemMetrics(SM_CYEDGE));
					pDC->LineTo(cxPage + nWidth, rButton[0].top - GetSystemMetrics(SM_CYEDGE));
				}
				pDC->SelectObject(pOldPen);
			}
			for (nIndex = (m_szPages.GetAt(nPage) == STRING(IDS_WORKSPACEWINDOW_DATABASETAB)) ? WORKSPACEVIEW_DATABASEPAGE_SYMBOL : ((m_szPages.GetAt(nPage) == STRING(IDS_WORKSPACEWINDOW_PROCEDURESTAB)) ? WORKSPACEVIEW_PROCEDURESPAGE_SYMBOL : ((m_szPages.GetAt(nPage) == STRING(IDS_WORKSPACEWINDOW_LOGSTAB)) ? WORKSPACEVIEW_LOGSPAGE_SYMBOL : -1)); nIndex >= 0; )
			{
				for (m_cSymbol[nIndex].Draw(pDC->GetSafeHdc(), cxPage + WORKSPACEVIEW_FRAME_SIZE, rButton[0].top + (cyPage - m_cSymbol[nIndex].GetHeight()) / 2); (pOldFont = pDC->SelectObject(&m_fntPages)); )
				{
					nOldColor = pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));
					nBkMode = pDC->SetBkMode(TRANSPARENT);
					pDC->GetTextMetrics(&tmFont);
					pDC->TextOut(cxPage + 2 * WORKSPACEVIEW_FRAME_SIZE + m_cSymbol[nIndex].GetWidth(), rButton[0].top + (cyPage - tmFont.tmHeight) / 2, m_szPages.GetAt(nPage));
					pDC->SelectObject(pOldFont);
					pDC->SetTextColor(nOldColor);
					pDC->SetBkMode(nBkMode);
					break;
				}
				break;
			}
			cxPage += nWidth;
		}
		if (cxPage <= rButton[0].left - WORKSPACEVIEW_FRAME_SIZE)
		{
			if ((pOldPen = pDC->SelectObject(&cPen[1])))
			{
				pDC->MoveTo(cxPage, rButton[0].top - GetSystemMetrics(SM_CYEDGE));
				pDC->LineTo(rButton[0].left, rButton[0].top - GetSystemMetrics(SM_CYEDGE));
				pDC->SelectObject(pOldPen);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[0])))
			{
				pDC->MoveTo(cxPage, rButton[0].top - 1);
				pDC->LineTo(rButton[0].left, rButton[0].top - 1);
				pDC->SelectObject(pOldPen);
			}
			pDC->FillRect(CRect(cxPage, rButton[0].top, rButton[0].left - WORKSPACEVIEW_FRAME_SIZE, rView[0].bottom), CBrush::FromHandle(GetSysColorBrush(COLOR_3DFACE)));
		}
		if (cxPage > rButton[0].left - WORKSPACEVIEW_FRAME_SIZE  &&  rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE > rView[0].left)
		{
			pDC->FillSolidRect(CRect(rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE, rButton[0].top, rButton[0].left - WORKSPACEVIEW_FRAME_SIZE, rView[0].bottom), GetSysColor(COLOR_3DFACE));
			if ((pOldPen = (CPen *)pDC->SelectObject(&cPen[1])) != (CPen *)NULL)
			{
				for (nHeight = 0; nHeight < (rView[0].bottom - rButton[0].top) / 2; nHeight++)
				{
					pDC->MoveTo((nHeight % 2 == 1) ? (rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE + 1) : ((!(nHeight % 4)) ? (rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE + 2) : (rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE)), rButton[0].top + 2 * nHeight);
					pDC->LineTo((nHeight % 2 == 1) ? (rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE + 1) : ((!(nHeight % 4)) ? (rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE + 2) : (rButton[0].left - WORKSPACEVIEW_FRAME_SIZE - WORKSPACEVIEW_TABBORDER_SIZE)), rButton[0].top + 2 * (nHeight + 1));
				}
				pDC->SelectObject(pOldPen);
			}
		}
		pDC->ExcludeClipRect(rView[1].left - WORKSPACEVIEW_FRAME_SIZE, rView[1].top - WORKSPACEVIEW_FRAME_SIZE, rView[1].left, rView[1].bottom + WORKSPACEVIEW_FRAME_SIZE);
		pDC->ExcludeClipRect(rView[1].right, rView[1].top - WORKSPACEVIEW_FRAME_SIZE, rView[1].right + WORKSPACEVIEW_FRAME_SIZE, rView[1].bottom + WORKSPACEVIEW_FRAME_SIZE);
		pDC->ExcludeClipRect(rView[1].left - WORKSPACEVIEW_FRAME_SIZE, rView[1].top - WORKSPACEVIEW_FRAME_SIZE, rView[1].right + WORKSPACEVIEW_FRAME_SIZE, rView[1].top);
		pDC->ExcludeClipRect(rView[1].left - WORKSPACEVIEW_FRAME_SIZE, rView[1].bottom, rView[1].right + WORKSPACEVIEW_FRAME_SIZE, rView[1].bottom + WORKSPACEVIEW_FRAME_SIZE);
		pDC->ExcludeClipRect(rView[0].left, rButton[0].top, rView[0].right, rView[0].bottom);
	}
}

VOID CWorkspaceView::DrawScrollLButton(CDC *pDC)
{
	CDC  cDC;
	CRect  rButton;
	BITMAP  sBitmap;
	CBitmap  *pBitmap;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(pDC))
	{
		for (CalcScrollLButtonPosition(rButton), pDC->DrawFrameControl(rButton, DFC_BUTTON, (IsScrollLButtonDown()) ? (DFCS_BUTTONPUSH | DFCS_PUSHED) : ((!IsScrollLButtonEnabled()) ? (DFCS_BUTTONPUSH | DFCS_INACTIVE) : DFCS_BUTTONPUSH)); (pOldBitmap = cDC.SelectObject((pBitmap = &m_bmpButton[(IsScrollLButtonDown()) ? WORKSPACEVIEW_SCROLLLBUTTON_PRESSED : ((!IsScrollLButtonEnabled()) ? WORKSPACEVIEW_SCROLLLBUTTON_DISABLED : WORKSPACEVIEW_SCROLLLBUTTON_DEFAULT)]))); )
		{
			if (pBitmap->GetObject(sizeof(BITMAP), &sBitmap)) pDC->BitBlt(rButton.left, rButton.top, sBitmap.bmWidth, sBitmap.bmHeight, &cDC, 0, 0, SRCAND);
			cDC.SelectObject(pOldBitmap);
			break;
		}
		cDC.DeleteDC();
	}
}
VOID CWorkspaceView::DrawScrollLButton(CPoint point, UINT bPushed)
{
	CDC  *pDC;
	UINT  nState;

	if ((pDC = GetDC()))
	{
		for (nState = (bPushed != (UINT)-1) ? ((bPushed) ? BST_PUSHED : 0) : (m_nState[0] & BST_PUSHED), nState |= (!IsScrollLButtonEnabled()) ? BST_INDETERMINATE : 0; m_nState[0] != nState; )
		{
			m_nState[0] = nState;
			DrawScrollLButton(pDC);
			break;
		}
		ReleaseDC(pDC);
	}
}

VOID CWorkspaceView::DrawScrollRButton(CDC *pDC)
{
	CDC  cDC;
	CRect  rButton;
	BITMAP  sBitmap;
	CBitmap  *pBitmap;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(pDC))
	{
		for (CalcScrollRButtonPosition(rButton), pDC->DrawFrameControl(rButton, DFC_BUTTON, (IsScrollRButtonDown()) ? (DFCS_BUTTONPUSH | DFCS_PUSHED) : ((!IsScrollRButtonEnabled()) ? (DFCS_BUTTONPUSH | DFCS_INACTIVE) : DFCS_BUTTONPUSH)); (pOldBitmap = cDC.SelectObject((pBitmap = &m_bmpButton[(IsScrollRButtonDown()) ? WORKSPACEVIEW_SCROLLRBUTTON_PRESSED : ((!IsScrollRButtonEnabled()) ? WORKSPACEVIEW_SCROLLRBUTTON_DISABLED : WORKSPACEVIEW_SCROLLRBUTTON_DEFAULT)]))); )
		{
			if (pBitmap->GetObject(sizeof(BITMAP), &sBitmap)) pDC->BitBlt(rButton.left, rButton.top, sBitmap.bmWidth, sBitmap.bmHeight, &cDC, 0, 0, SRCAND);
			cDC.SelectObject(pOldBitmap);
			break;
		}
		cDC.DeleteDC();
	}
}
VOID CWorkspaceView::DrawScrollRButton(CPoint point, UINT bPushed)
{
	CDC  *pDC;
	UINT  nState;

	if ((pDC = GetDC()))
	{
		for (nState = (bPushed != (UINT)-1) ? ((bPushed) ? BST_PUSHED : 0) : (m_nState[1] & BST_PUSHED), nState |= (!IsScrollRButtonEnabled()) ? BST_INDETERMINATE : 0; m_nState[1] != nState; )
		{
			m_nState[1] = nState;
			DrawScrollRButton(pDC);
			break;
		}
		ReleaseDC(pDC);
	}
}

BOOL CWorkspaceView::IsPointOnScrollLButton(CPoint point)
{
	CRect  rButton;

	CalcScrollLButtonPosition(rButton);
	return rButton.PtInRect(point);
}

BOOL CWorkspaceView::IsPointOnScrollRButton(CPoint point)
{
	CRect  rButton;

	CalcScrollRButtonPosition(rButton);
	return rButton.PtInRect(point);
}

UINT CWorkspaceView::IsPointOnTab(CPoint point)
{
	INT  nTab;
	INT  nTabs;
	INT  nTabPos;
	CRect  rTab;
	CRect  rTabs;
	CSize  sizeTabs;
	CUIntArray  nTabsPos;

	for (sizeTabs = CalcTabsExtent(nTabsPos); nTabsPos.GetSize() > 0; )
	{
		for (nTab = abs(m_nPagePos), nTabs = (INT)nTabsPos.GetSize(), nTabPos = (nTab) ? nTabsPos.GetAt(nTab - 1) : 0, GetParent()->CalcClientRect(rTabs), GetParent()->ClientToScreen(rTabs), ScreenToClient(rTabs); nTab < nTabs; nTab++)
		{
			rTab.SetRect((nTab) ? (WORKSPACEVIEW_FRAME_SIZE + nTabsPos.GetAt(nTab - 1) - nTabPos + 1) : (WORKSPACEVIEW_FRAME_SIZE + 1), rTabs.bottom - sizeTabs.cy, WORKSPACEVIEW_FRAME_SIZE + nTabsPos.GetAt(nTab) - nTabPos - 1, rTabs.bottom - 1);
			if (rTab.PtInRect(point)) break;
		}
		return((nTab < nTabs) ? nTab : -1);
	}
	return -1;
}

BOOL CWorkspaceView::IsScrollLButtonDown() CONST
{
	return((m_nState[0] & BST_PUSHED) ? TRUE : FALSE);
}

BOOL CWorkspaceView::IsScrollRButtonDown() CONST
{
	return((m_nState[1] & BST_PUSHED) ? TRUE : FALSE);
}

BOOL CWorkspaceView::IsScrollLButtonEnabled()
{
	return((m_nPagePos < 0) ? TRUE : FALSE);
}

BOOL CWorkspaceView::IsScrollRButtonEnabled()
{
	return((m_nPagePos > CalcScrollPosition()) ? TRUE : FALSE);
}

VOID CWorkspaceView::StartTabsScrolling()
{
	SetTimer(WORKSPACEVIEW_SCROLL_TIMERID, WORKSPACEVIEW_SCROLL_TIMEOUT, NULL);
}

VOID CWorkspaceView::ScrollTabs(BOOL bLeft)
{
	INT  nTabPos;
	CRect  rView;
	CRect  rPage;
	CRect  rButton[2];
	CWorkspaceViewPage  *pPage;

	if ((nTabPos = (bLeft) ? min(m_nPagePos + 1, 0) : max(m_nPagePos - 1, CalcScrollPosition())) != m_nPagePos)
	{
		if (!nTabPos || nTabPos == CalcScrollPosition())
		{
			m_nPagePos = nTabPos;
			Invalidate(FALSE);
			UpdateWindow();
			return;
		}
		if ((pPage = (CWorkspaceViewPage *)m_pwndPages.GetAt(0)))
		{
			pPage->GetWindowRect(rPage);
			ScreenToClient(rPage);
			GetClientRect(rView);
			CalcScrollLButtonPosition(rButton[0]);
			CalcScrollRButtonPosition(rButton[1]);
			InvalidateRect(CRect(rPage.left, rPage.bottom, rButton[0].left, rView.bottom), FALSE);
			InvalidateRect(CRect(rButton[1].right, rPage.bottom, rPage.right, rView.bottom), FALSE);
			InvalidateRect(CRect(rButton[0].left, rButton[0].bottom, rButton[1].right, rView.bottom), FALSE);
			m_nPagePos = nTabPos;
			UpdateWindow();
			return;
		}
	}
}

VOID CWorkspaceView::StopTabsScrolling()
{
	KillTimer(WORKSPACEVIEW_SCROLL_TIMERID);
}

void CWorkspaceView::PostNcDestroy()
{
	INT  nPage;
	INT  nPages;
	CWorkspaceViewPage  *pPage;

	for (nPage = 0, nPages = (INT)m_pwndPages.GetSize(); nPage < nPages; nPage++)
	{
		if ((pPage = (CWorkspaceViewPage *)m_pwndPages.GetAt(nPage)))
		{
			delete pPage;
			continue;
		}
	}
	m_pwndPages.RemoveAll();
	CWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CWorkspaceView, CWnd)
	//{{AFX_MSG_MAP(CWorkspaceView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView message handlers

int CWorkspaceView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nButton;
	INT  nButtons;
	INT  nSymbol;
	INT  nSymbols;
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	LPSTREAM  pIStream;
	HGLOBAL  hMemResource[2];
	CWorkspaceViewDatabasePage  *pDatabasePage;
	CWorkspaceViewProceduresPage  *pProceduresPage;
	CWorkspaceViewLogsPage  *pLogsPage;
	CFontTools  cFontTools;

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if ((pDatabasePage = new CWorkspaceViewDatabasePage))
		{
			if ((pProceduresPage = new CWorkspaceViewProceduresPage))
			{
				if ((pLogsPage = new CWorkspaceViewLogsPage))
				{
					if (pDatabasePage->Create(this, CRect(0, 0, 0, 0)) && pProceduresPage->Create(this, CRect(0, 0, 0, 0)) && pLogsPage->Create(this, CRect(0, 0, 0, 0)))
					{
						for (nSymbol = 0, nSymbols = sizeof(m_cSymbol) / sizeof(m_cSymbol[0]); nSymbol < nSymbols; nSymbol = nSymbol + 1)
						{
							if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), MAKEINTRESOURCE(FIRSTWORKSPACEPAGESYMBOLID + nSymbol), STRING(IDS_RESOURCETYPE_PICTURE))))
							{
								if ((hMemResource[0] = LoadResource(hModule, hResource)))
								{
									if ((pResource = LockResource(hMemResource[0])))
									{
										if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
										{
											if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
											{
												if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_cSymbol[nSymbol].Load(pIStream)))
												{
													pIStream->Release();
													continue;
												}
												pIStream->Release();
											}
										}
									}
								}
							}
							break;
						}
						for (nButton = 0, nButtons = sizeof(m_bmpButton) / sizeof(m_bmpButton[0]); nButton < nButtons; nButton++)
						{
							if (!m_bmpButton[nButton].LoadBitmap(min(IDB_WORKSPACESCROLLLEFTBUTTON, min(IDB_WORKSPACESCROLLLEFTBUTTONPRESSED, min(IDB_WORKSPACESCROLLLEFTBUTTONDISABLED, min(IDB_WORKSPACESCROLLRIGHTBUTTON, min(IDB_WORKSPACESCROLLRIGHTBUTTONPRESSED, IDB_WORKSPACESCROLLRIGHTBUTTONDISABLED))))) + nButton)) break;
							continue;
						}
						if (cFontTools.QueryDefaultFont(&m_fntPages) && nSymbol == nSymbols  &&  nButton == nButtons)
						{
							m_szPages.Add(STRING(IDS_WORKSPACEWINDOW_DATABASETAB));
							m_szPages.Add(STRING(IDS_WORKSPACEWINDOW_PROCEDURESTAB));
							m_szPages.Add(STRING(IDS_WORKSPACEWINDOW_LOGSTAB));
							m_pwndPages.Add(pDatabasePage);
							m_pwndPages.Add(pProceduresPage);
							m_pwndPages.Add(pLogsPage);
							return 0;
						}
					}
					pDatabasePage->DestroyWindow();
					pProceduresPage->DestroyWindow();
					pLogsPage->DestroyWindow();
					delete pLogsPage;
				}
				delete pProceduresPage;
			}
			delete pDatabasePage;
		}
	}
	return -1;
}

void CWorkspaceView::OnSize(UINT nType, int cx, int cy)
{
	INT  nPage;
	INT  nPages;
	CRect  rPage;
	CWorkspaceViewPage  *pPage;

	for (nPage = 0, nPages = (INT)m_pwndPages.GetSize(), CalcClientRect(rPage); nPage < nPages; nPage++)
	{
		if ((pPage = (CWorkspaceViewPage *)m_pwndPages.GetAt(nPage)))
		{
			pPage->MoveWindow(rPage);
			continue;
		}
	}
	CWnd::OnSize(nType, cx, cy);
}

BOOL CWorkspaceView::OnEraseBkgnd(CDC *pDC)
{
	INT  nPage;
	INT  nPages;
	CRect  rPage;
	CRect  rView[2];
	CWorkspaceViewPage  *pPage;

	for (GetWindowRect(rView[0]), GetParent()->ScreenToClient(rView[0]), GetParent()->CalcClientRect(rView[1]); !rView[0].EqualRect(rView[1]); )
	{
		MoveWindow(rView[1]);
		return TRUE;
	}
	for (nPage = 0, nPages = (INT)m_pwndPages.GetSize(), CalcClientRect(rPage); nPage < nPages; nPage++)
	{
		if ((pPage = (CWorkspaceViewPage *)m_pwndPages.GetAt(nPage)))
		{
			pPage->MoveWindow(rPage);
			pPage->UpdateWindow();
		}
	}
	DrawViewPages(pDC);
	return TRUE;
}

void CWorkspaceView::OnNcPaint()
{
	CRect  rView[2];

	for (GetWindowRect(rView[0]), GetParent()->ScreenToClient(rView[0]), GetParent()->CalcClientRect(rView[1]); !rView[0].EqualRect(rView[1]); )
	{
		MoveWindow(rView[1]);
		return;
	}
	CWnd::OnNcPaint();
}

void CWorkspaceView::OnPaint()
{
	CPaintDC  cDC(this);

	DrawViewPages(&cDC);
}

void CWorkspaceView::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nTab;

	if (IsScrollLButtonEnabled() && IsPointOnScrollLButton(point))
	{
		DrawScrollLButton(point, TRUE);
		DrawScrollRButton(point);
		StartTabsScrolling();
		ScrollTabs(TRUE);
		SetCapture();
	}
	if (IsScrollRButtonEnabled() && IsPointOnScrollRButton(point))
	{
		DrawScrollRButton(point, TRUE);
		DrawScrollLButton(point);
		StartTabsScrolling();
		ScrollTabs(FALSE);
		SetCapture();
	}
	if ((nTab = IsPointOnTab(point)) >= 0 && !IsPointOnScrollLButton(point) && !IsPointOnScrollRButton(point)) SetCurPage(nTab);
	CWnd::OnLButtonDown(nFlags, point);
}

void CWorkspaceView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (IsScrollLButtonDown())
	{
		DrawScrollLButton(point, FALSE);
		DrawScrollRButton(point, FALSE);
		StopTabsScrolling();
		ReleaseCapture();
	}
	if (IsScrollRButtonDown())
	{
		DrawScrollRButton(point, FALSE);
		DrawScrollLButton(point, FALSE);
		StopTabsScrolling();
		ReleaseCapture();
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void CWorkspaceView::OnSetFocus(CWnd *pOldWnd)
{
	INT  nPage;
	CWorkspaceViewPage  *pPage;

	if ((nPage = GetCurPage()) >= 0)
	{
		if ((pPage = (CWorkspaceViewPage *)m_pwndPages.GetAt(nPage)))
		{
			pPage->SetFocus();
			return;
		}
	}
	CWnd::OnSetFocus(pOldWnd);
}

void CWorkspaceView::OnTimer(UINT_PTR nEventID)
{
	POINT  ptCursor;

	for (GetCursorPos(&ptCursor), ScreenToClient(&ptCursor); nEventID == WORKSPACEVIEW_SCROLL_TIMERID; )
	{
		if (IsPointOnScrollLButton(ptCursor))
		{
			if (!IsScrollLButtonEnabled())
			{
				DrawScrollLButton(CPoint(0, 0), FALSE);
				DrawScrollRButton(ptCursor);
				StopTabsScrolling();
				ReleaseCapture();
			}
			else  ScrollTabs(TRUE);
		}
		if (IsPointOnScrollRButton(ptCursor))
		{
			if (!IsScrollRButtonEnabled())
			{
				DrawScrollRButton(CPoint(0, 0), FALSE);
				DrawScrollLButton(ptCursor);
				StopTabsScrolling();
				ReleaseCapture();
			}
			else  ScrollTabs(FALSE);
		}
		break;
	}
	CWnd::OnTimer(nEventID);
}

void CWorkspaceView::OnDestroy()
{
	INT  nSymbol;
	INT  nSymbols;
	INT  nButton;
	INT  nButtons;

	for (nSymbol = 0, nSymbols = sizeof(m_cSymbol) / sizeof(m_cSymbol[0]); nSymbol < nSymbols; nSymbol++)
	{
		m_cSymbol[nSymbol].Destroy();
		continue;
	}
	for (nButton = 0, nButtons = sizeof(m_bmpButton) / sizeof(m_bmpButton[0]); nButton < nButtons; nButton++)
	{
		m_bmpButton[nButton].DeleteObject();
		continue;
	}
	m_fntPages.DeleteObject();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CWorkspaceWnd

IMPLEMENT_DYNCREATE(CWorkspaceWnd, CToolWnd)

CWorkspaceWnd::CWorkspaceWnd(CWorkspaceWnd *pWorkspaceWnd) : CToolWnd(pWorkspaceWnd)
{
	m_pwndView = (CWorkspaceView *)NULL;
}

VOID CWorkspaceWnd::SetPage(LPCTSTR pszPage)
{
	m_pwndView->SetCurPage(pszPage);
}

CString CWorkspaceWnd::GetPage() CONST
{
	CString  szPage;

	m_pwndView->GetCurPage(szPage);
	return szPage;
}

VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pDatabaseTMPacket, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pDatabaseTCFunction, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pDatabaseTMParameter, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pDatabaseTCParameter, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pDatabaseOBProcessor, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pANDWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pGRDWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pMMDWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pPODWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseContents(pScriptWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseContents()
{
	m_pwndView->UpdateDatabaseContents();
}

VOID CWorkspaceWnd::UpdateDatabaseProcedures(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseProcedures(pDatabaseTCSequence, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseProcedures(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseProcedures(pDatabaseTCProcedure, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseProcedures(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseProcedures(pTCSequenceWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseProcedures()
{
	m_pwndView->UpdateDatabaseProcedures();
}

VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pDatabaseTMPacket, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pDatabaseTCFunction, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pDatabaseTCSequence, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pDatabaseTCProcedure, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pDatabaseTMParameter, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pDatabaseTCParameter, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pDatabaseOBProcessor, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pTCSequenceWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pANDWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pGRDWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pMMDWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pPODWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	m_pwndView->UpdateDatabaseLogs(pScriptWnd, nPosition, bDelete);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs(ULONGLONG nComponent, LPCTSTR pszName)
{
	m_pwndView->UpdateDatabaseLogs(nComponent, pszName);
}
VOID CWorkspaceWnd::UpdateDatabaseLogs()
{
	m_pwndView->UpdateDatabaseLogs();
}

BOOL CWorkspaceWnd::CreateDatabaseItem()
{
	return m_pwndView->CreateDatabaseItem();
}

BOOL CWorkspaceWnd::OpenDatabaseItem()
{
	return m_pwndView->OpenDatabaseItem();
}

BOOL CWorkspaceWnd::HasDatabaseItem(INT nType) CONST
{
	return m_pwndView->HasDatabaseItem(nType);
}

BOOL CWorkspaceWnd::RenameDatabaseItem()
{
	return m_pwndView->RenameDatabaseItem();
}

BOOL CWorkspaceWnd::DeleteDatabaseItem()
{
	return m_pwndView->DeleteDatabaseItem();
}

BOOL CWorkspaceWnd::CreateProceduresItem()
{
	return m_pwndView->CreateProceduresItem();
}

BOOL CWorkspaceWnd::OpenProceduresItem()
{
	return m_pwndView->OpenProceduresItem();
}

BOOL CWorkspaceWnd::HasProceduresItem(INT nType) CONST
{
	return m_pwndView->HasProceduresItem(nType);
}

BOOL CWorkspaceWnd::RenameProceduresItem()
{
	return m_pwndView->RenameProceduresItem();
}

BOOL CWorkspaceWnd::DeleteProceduresItem()
{
	return m_pwndView->DeleteProceduresItem();
}

BOOL CWorkspaceWnd::CanDeleteSel() CONST
{
	return m_pwndView->CanDeleteSel();
}

VOID CWorkspaceWnd::DoDeleteSel()
{
	m_pwndView->DoDeleteSel();
}

VOID CWorkspaceWnd::Copy(CWorkspaceWnd *pWorkspaceWnd)
{
	CRect  rView;

	CalcClientRect(rView);
	m_pwndView = pWorkspaceWnd->m_pwndView;
	pWorkspaceWnd->m_pwndView->SetParent(this);
	pWorkspaceWnd->m_pwndView->MoveWindow(rView);
	pWorkspaceWnd->m_pwndView = (CWorkspaceView *)NULL;
	pWorkspaceWnd->ShowWindow(SW_HIDE);
}

void CWorkspaceWnd::PostNcDestroy()
{
	delete m_pwndView;
	CToolWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CWorkspaceWnd, CToolWnd)
	//{{AFX_MSG_MAP(CWorkspaceWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceWnd message handlers

int CWorkspaceWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CToolWnd::OnCreate(lpCreateStruct) != -1)
	{
		if ((m_pwndView = (IsDocked(TRUE)) ? new CWorkspaceView : (CWorkspaceView *)NULL))
		{
			if (m_pwndView->Create(this)) return 0;
			delete m_pwndView;
		}
		m_pwndView = (CWorkspaceView *)NULL;
		return((!IsDocked(TRUE)) ? 0 : -1);
	}
	return -1;
}

void CWorkspaceWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rView;

	if (IsWindow(m_pwndView->GetSafeHwnd()))
	{
		CalcClientRect(rView);
		m_pwndView->MoveWindow(rView);
	}
	CToolWnd::OnSize(nType, cx, cy);
}

void CWorkspaceWnd::OnPaint()
{
	if (IsWindow(m_pwndView->GetSafeHwnd())) m_pwndView->UpdateWindow();
	CToolWnd::OnPaint();
}

void CWorkspaceWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN)
	{
		m_pwndView->SetFocus();
		return;
	}
	CToolWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// COutputViewScrollBar

IMPLEMENT_DYNCREATE(COutputViewScrollBar, CScrollBar)

COutputViewScrollBar::COutputViewScrollBar() : CScrollBar()
{
	ZeroMemory(&m_sScrollInfo, sizeof(SCROLLINFO));
	m_pCriticalSection = new CCriticalSection;
}

COutputViewScrollBar::~COutputViewScrollBar()
{
	delete m_pCriticalSection;
}

VOID COutputViewScrollBar::SetScrollInfo(CONST SCROLLINFO *pScrollInfo, BOOL bRedraw)
{
	if (Lock())
	{
		CopyMemory(&m_sScrollInfo, pScrollInfo, sizeof(SCROLLINFO));
		Unlock();
	}
	if (bRedraw)
	{
		for (Invalidate(FALSE); CThread::IsSameThread(this); )
		{
			UpdateWindow();
			break;
		}
	}
}

VOID COutputViewScrollBar::GetScrollInfo(SCROLLINFO *pScrollInfo) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	CopyMemory(pScrollInfo, &m_sScrollInfo, sizeof(SCROLLINFO));
}

BOOL COutputViewScrollBar::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL COutputViewScrollBar::Unlock()
{
	return m_pCriticalSection->Unlock();
}

BEGIN_MESSAGE_MAP(COutputViewScrollBar, CScrollBar)
	//{{AFX_MSG_MAP(COutputViewScrollBar)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputViewScrollBar message handlers

void COutputViewScrollBar::OnPaint()
{
	CScrollBar::SetScrollInfo(&m_sScrollInfo);
	CScrollBar::OnPaint();
}


/////////////////////////////////////////////////////////////////////////////
// COutputViewBar

IMPLEMENT_DYNCREATE(COutputViewBar, CWnd)

COutputViewBar::COutputViewBar() : CWnd()
{
	m_nTab = 0;
	m_nTabPos = 0;
	m_nState[0] = 0;
	m_nState[1] = 0;
	m_nSplitPos = 0;
	m_bSplitBar = FALSE;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL COutputViewBar::Create(CWnd *pParentWnd, CONST RECT &rect, CStringArray &szTabs)
{
	if (CWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), EMPTYSTRING, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), 0))
	{
		m_szTabs.Copy(szTabs);
		return TRUE;
	}
	return FALSE;
}

VOID COutputViewBar::SetCurTab(INT nTab)
{
	CRect  rTab[2];
	CRect  rViewBar;

	if (m_nTab != nTab)
	{
		if (nTab < m_nTabsPos.GetSize() / 2)
		{
			GetClientRect(rViewBar);
			rTab[0].SetRect(m_nTabsPos.GetAt(2 * nTab), rViewBar.top, m_nTabsPos.GetAt(2 * nTab + 1), rViewBar.bottom);
			rTab[1].SetRect(m_nTabsPos.GetAt(2 * m_nTab), rViewBar.top, m_nTabsPos.GetAt(2 * m_nTab + 1), rViewBar.bottom);
			GetParent()->SetConsole((m_nTab = nTab));
			InvalidateRect(rTab[0], FALSE);
			InvalidateRect(rTab[1], FALSE);
		}
	}
}

INT COutputViewBar::GetCurTab() CONST
{
	return m_nTab;
}

VOID COutputViewBar::SetScrollInfo(CONST SCROLLINFO *pScrollInfo)
{
	if (IsWindow(m_wndScrollBar.GetSafeHwnd()))
	{
		m_wndScrollBar.SetScrollInfo(pScrollInfo);
		return;
	}
}

VOID COutputViewBar::GetScrollInfo(SCROLLINFO *pScrollInfo)
{
	if (IsWindow(m_wndScrollBar.GetSafeHwnd()))
	{
		m_wndScrollBar.GetScrollInfo(pScrollInfo);
		return;
	}
}

COutputView *COutputViewBar::GetParent() CONST
{
	return((COutputView *)m_pParentWnd);
}

CSize COutputViewBar::CalcExtent()
{
	INT  nTab;
	CSize  sizeTabs;

	for (nTab = 0, sizeTabs.cx = CalcTabsExtent().cx + CalcScrollExtent().cx + OUTPUTVIEWBAR_SPLITBAR_WIDTH, sizeTabs.cy = CalcTabsExtent().cy; nTab < m_szTabs.GetSize(); nTab++)
	{
		sizeTabs.cx += CalcTabItemExtent(nTab).cx + sizeTabs.cy;
		continue;
	}
	return CSize(sizeTabs);
}

CSize COutputViewBar::CalcTabsExtent() CONST
{
	CSize  sizeButton;

	sizeButton = CalcScrollButtonSize();
	return CSize(2 * sizeButton.cx, GetSystemMetrics(SM_CYHSCROLL));
}

CSize COutputViewBar::CalcTabItemExtent(INT nItem)
{
	CDC  *pDC;
	CSize  sizeTabs;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_fntTabs)))
		{
			pDC->GetTextMetrics(&tmFont);
			sizeTabs.cx = pDC->GetTextExtent(m_szTabs.GetAt(nItem)).cx + 2 * tmFont.tmAveCharWidth;
			sizeTabs.cy = CalcTabsExtent().cy;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return CSize(sizeTabs);
		}
		ReleaseDC(pDC);
	}
	return CSize(0, 0);
}

CSize COutputViewBar::CalcScrollExtent() CONST
{
	return CSize(5 * GetSystemMetrics(SM_CXHSCROLL), CalcTabsExtent().cy);
}

CSize COutputViewBar::CalcScrollButtonSize() CONST
{
	BITMAP  sBitmap[2];
	CBitmap  cBitmap[2];

	return((cBitmap[0].LoadBitmap(IDB_OUTPUTSCROLLLEFTBUTTON) && cBitmap[1].LoadBitmap(IDB_OUTPUTSCROLLRIGHTBUTTON) && cBitmap[0].GetObject(sizeof(sBitmap[0]), &sBitmap[0]) && cBitmap[1].GetObject(sizeof(sBitmap[1]), &sBitmap[1])) ? CSize(max(sBitmap[0].bmWidth, sBitmap[1].bmWidth), max(sBitmap[0].bmHeight, sBitmap[1].bmHeight)) : CSize(0, 0));
}

VOID COutputViewBar::CalcScrollLButtonPosition(LPRECT pRect) CONST
{
	CRect  rViewBar;
	CSize  sizeButton;

	GetClientRect(rViewBar);
	sizeButton = CalcScrollButtonSize();
	SetRect(pRect, rViewBar.left, rViewBar.top + 1, rViewBar.left + sizeButton.cx - 1, rViewBar.top + sizeButton.cy + 1);
}

VOID COutputViewBar::CalcScrollRButtonPosition(LPRECT pRect) CONST
{
	CRect  rViewBar;
	CSize  sizeButton;

	GetClientRect(rViewBar);
	sizeButton = CalcScrollButtonSize();
	SetRect(pRect, rViewBar.left + sizeButton.cx - 1, rViewBar.top + 1, rViewBar.left + 2 * sizeButton.cx - 1, rViewBar.top + sizeButton.cy + 1);
}

VOID COutputViewBar::CalcSplitBarPosition(LPRECT pRect) CONST
{
	CRect  rViewBar;

	GetClientRect(rViewBar);
	SetRect(pRect, (m_nSplitPos > 0) ? m_nSplitPos : 0, (m_nSplitPos > 0) ? rViewBar.top : 0, (m_nSplitPos > 0) ? (m_nSplitPos + OUTPUTVIEWBAR_SPLITBAR_WIDTH) : 0, (m_nSplitPos > 0) ? rViewBar.bottom : 0);
}

VOID COutputViewBar::AdjustSplitPosition()
{
	CRect  rViewBar;
	CRect  rScrollBar;

	GetClientRect(rViewBar);
	if (IsWindow(m_wndScrollBar.GetSafeHwnd()) && !IsScrollLButtonDown() && !IsScrollRButtonDown() && !IsSplitBarDragged() && !rViewBar.IsRectEmpty())
	{
		rScrollBar.SetRect((m_nSplitPos = (rViewBar.Width() > CalcExtent().cx) ? max(CalcExtent().cx - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH, m_nSplitPos) : (rViewBar.right - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH)) + OUTPUTVIEWBAR_SPLITBAR_WIDTH, rViewBar.top, rViewBar.right, rViewBar.bottom);
		m_wndScrollBar.MoveWindow(rScrollBar);
	}
}

VOID COutputViewBar::DrawViewBar(CDC *pDC)
{
	INT  x;
	INT  y;
	INT  cx;
	INT  cy;
	INT  nTab;
	INT  nTabs;
	INT  cxTab;
	INT  cyTab;
	INT  nBkMode;
	CPen  cPen[4];
	CPen  *pOldPen;
	CFont  *pOldFont;
	CRect  rButtons;
	CRect  rViewBar;
	COLORREF  refColor;
	TEXTMETRIC  tmFont;

	DrawScrollLButton(pDC);
	DrawScrollRButton(pDC);
	GetClientRect(rViewBar);
	cx = CalcTabsExtent().cx;
	cy = CalcTabsExtent().cy;
	cxTab = m_nSplitPos;
	cyTab = rViewBar.bottom - cy;
	CalcScrollRButtonPosition(rButtons);
	if (cPen[0].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)) && cPen[1].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DSHADOW)) && cPen[2].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DHIGHLIGHT)) && cPen[3].CreatePen(PS_SOLID, 0, GetSysColor(COLOR_3DFACE)))
	{
		if ((pOldPen = pDC->SelectObject(&cPen[0])))
		{
			pDC->MoveTo(cxTab, cyTab);
			pDC->LineTo(cxTab + OUTPUTVIEWBAR_SPLITBAR_WIDTH, cyTab);
			pDC->MoveTo(cxTab, cyTab);
			pDC->LineTo(cxTab, cyTab + cy);
			pDC->MoveTo(rViewBar.left, rViewBar.top);
			pDC->LineTo(rButtons.right + 1, rViewBar.top);
			pDC->SelectObject(pOldPen);
		}
		if ((pOldPen = pDC->SelectObject(&cPen[2])))
		{
			pDC->MoveTo(++cxTab, cyTab + 1);
			pDC->LineTo(cxTab, cyTab + cy);
			pDC->SelectObject(pOldPen);
		}
		if ((pOldPen = pDC->SelectObject(&cPen[3])))
		{
			pDC->MoveTo(++cxTab, cyTab + 1);
			pDC->LineTo(cxTab, cyTab + cy);
			pDC->MoveTo(rButtons.right, rViewBar.top + 1);
			pDC->LineTo(rButtons.right, rViewBar.bottom);
			pDC->SelectObject(pOldPen);
		}
		if ((pOldPen = pDC->SelectObject(&cPen[1])))
		{
			pDC->MoveTo(++cxTab, cyTab + 1);
			pDC->LineTo(cxTab, cyTab + cy);
			pDC->SelectObject(pOldPen);
		}
		pDC->FillSolidRect(rViewBar.left, rButtons.bottom, rButtons.right, rViewBar.bottom, GetSysColor(COLOR_3DFACE));
		pDC->ExcludeClipRect(rViewBar.left, rViewBar.top, rButtons.right + 1, rViewBar.bottom);
		pDC->ExcludeClipRect(m_nSplitPos, rViewBar.top, rViewBar.right, rViewBar.bottom);
		pDC->FillSolidRect(rViewBar, GetSysColor(COLOR_3DFACE));
		for (nTab = 0, nTabs = (INT)m_szTabs.GetSize(), cxTab = rButtons.right + m_nTabPos + 1, cyTab = rViewBar.bottom - cy, cx = CalcTabItemExtent(nTab).cx; nTab < nTabs; nTab++, cx = (nTab < nTabs) ? CalcTabItemExtent(nTab).cx : cx)
		{
			m_nTabsPos.SetAtGrow(2 * nTab, cxTab);
			if ((pOldPen = pDC->SelectObject(&cPen[0])))
			{
				pDC->MoveTo((nTab  &&  nTab != GetCurTab()) ? (cxTab + cy / 4) : cxTab, (nTab  &&  nTab != GetCurTab()) ? (cyTab + cy / 2) : cyTab);
				pDC->LineTo(cxTab + cy / 2, cyTab + cy);
				if (nTab != GetCurTab())
				{
					pDC->MoveTo((nTab) ? (cxTab + cy / 2) : cxTab, cyTab);
					pDC->LineTo(cxTab + cx + cy + 1, cyTab);
				}
				pDC->SelectObject(pOldPen);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[2])))
			{
				pDC->MoveTo((nTab  &&  nTab != GetCurTab()) ? (cxTab + cy / 4 + 1) : (cxTab + 1), (nTab  &&  nTab != GetCurTab()) ? (cyTab + cy / 2) : (cyTab + 1));
				pDC->LineTo(cxTab + cy / 2 + 1, cyTab + cy);
				if (nTab == GetCurTab())
				{
					for (x = cxTab + 1, y = cyTab; x < cxTab + cx + 1; x++)
					{
						pDC->MoveTo(x, y);
						pDC->LineTo(x + cy / 2, cyTab + cy);
					}
					for (x = x + cy / 2; x > cxTab + cy / 2 + 1; x--)
					{
						pDC->MoveTo(x, cyTab + cy);
						pDC->LineTo(x + cy / 2, cyTab - 1);
					}
				}
				pDC->SelectObject(pOldPen);
				cxTab += cy / 2;
			}
			if ((pOldFont = pDC->SelectObject(&m_fntTabs)))
			{
				refColor = pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));
				nBkMode = pDC->SetBkMode(TRANSPARENT);
				pDC->GetTextMetrics(&tmFont);
				pDC->TextOut(cxTab + (cx - pDC->GetTextExtent(m_szTabs.GetAt(nTab)).cx) / 2, cyTab + (cy - tmFont.tmHeight - tmFont.tmInternalLeading) / 2, m_szTabs.GetAt(nTab));
				pDC->SelectObject(pOldFont);
				pDC->SetTextColor(refColor);
				pDC->SetBkMode(nBkMode);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[0])))
			{
				pDC->MoveTo(cxTab, cyTab + cy - 1);
				pDC->LineTo(cxTab + cx + 1, cyTab + cy - 1);
				pDC->SelectObject(pOldPen);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[1])))
			{
				pDC->MoveTo(cxTab, cyTab + cy - 2);
				pDC->LineTo((cxTab = cxTab + cx) + 1, cyTab + cy - 2);
				pDC->MoveTo(cxTab, cyTab + cy);
				pDC->LineTo((nTab < nTabs  &&  GetCurTab() == nTab + 1) ? (cxTab + cy / 4) : (cxTab + cy / 2), (nTab < nTabs  &&  GetCurTab() == nTab + 1) ? (cyTab + cy / 2 - 1) : ((nTab == GetCurTab()) ? (cyTab - 1) : cyTab));
				pDC->SelectObject(pOldPen);
			}
			if ((pOldPen = pDC->SelectObject(&cPen[0])))
			{
				pDC->MoveTo(++cxTab, cyTab + cy - 1);
				pDC->LineTo(cxTab - cx, cyTab + cy - 1);
				pDC->MoveTo(cxTab, cyTab + cy);
				pDC->LineTo((nTab < nTabs  &&  GetCurTab() == nTab + 1) ? (cxTab + cy / 4) : (cxTab + cy / 2), (nTab < nTabs  &&  GetCurTab() == nTab + 1) ? (cyTab + cy / 2 - 1) : (cyTab - 1));
				pDC->SelectObject(pOldPen);
			}
			m_nTabsPos.SetAtGrow(2 * nTab + 1, cxTab + cy / 2);
			cxTab++;
		}
		if ((pOldPen = pDC->SelectObject(&cPen[0])))
		{
			pDC->MoveTo(cxTab + cy / 2, cyTab);
			pDC->LineTo(m_nSplitPos, cyTab);
			pDC->SelectObject(pOldPen);
		}
	}
	m_wndScrollBar.UpdateWindow();
}

VOID COutputViewBar::DrawScrollLButton(CDC *pDC)
{
	CDC  cDC;
	CRect  rButton;
	BITMAP  sBitmap;
	CBitmap  *pBitmap;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(pDC))
	{
		for (CalcScrollLButtonPosition(rButton), pDC->DrawFrameControl(rButton, DFC_BUTTON, (IsScrollLButtonDown()) ? (DFCS_BUTTONPUSH | DFCS_PUSHED) : ((!IsScrollLButtonEnabled()) ? (DFCS_BUTTONPUSH | DFCS_INACTIVE) : DFCS_BUTTONPUSH)); (pOldBitmap = cDC.SelectObject((pBitmap = &m_bmpButton[(IsScrollLButtonDown()) ? OUTPUTVIEWBAR_SCROLLLBUTTON_PRESSED : ((!IsScrollLButtonEnabled()) ? OUTPUTVIEWBAR_SCROLLLBUTTON_DISABLED : OUTPUTVIEWBAR_SCROLLLBUTTON_DEFAULT)]))); )
		{
			if (pBitmap->GetObject(sizeof(BITMAP), &sBitmap) == sizeof(BITMAP)) pDC->BitBlt(rButton.left, rButton.top, sBitmap.bmWidth, sBitmap.bmHeight, &cDC, 0, 0, SRCAND);
			cDC.SelectObject(pOldBitmap);
			break;
		}
		cDC.DeleteDC();
	}
}
VOID COutputViewBar::DrawScrollLButton(CPoint point, UINT bPushed)
{
	CDC  *pDC;
	UINT  nState;

	if ((pDC = GetDC()))
	{
		for (nState = (bPushed != (UINT)-1) ? ((bPushed) ? BST_PUSHED : 0) : (m_nState[0] & BST_PUSHED), nState |= (!IsScrollLButtonEnabled()) ? BST_INDETERMINATE : 0; m_nState[0] != nState; )
		{
			m_nState[0] = nState;
			DrawScrollLButton(pDC);
			break;
		}
		ReleaseDC(pDC);
	}
}

VOID COutputViewBar::DrawScrollRButton(CDC *pDC)
{
	CDC  cDC;
	CRect  rButton;
	BITMAP  sBitmap;
	CBitmap  *pBitmap;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(pDC))
	{
		for (CalcScrollRButtonPosition(rButton), pDC->DrawFrameControl(rButton, DFC_BUTTON, (IsScrollRButtonDown()) ? (DFCS_BUTTONPUSH | DFCS_PUSHED) : ((!IsScrollRButtonEnabled()) ? (DFCS_BUTTONPUSH | DFCS_INACTIVE) : DFCS_BUTTONPUSH)); (pOldBitmap = cDC.SelectObject((pBitmap = &m_bmpButton[(IsScrollRButtonDown()) ? OUTPUTVIEWBAR_SCROLLRBUTTON_PRESSED : ((!IsScrollRButtonEnabled()) ? OUTPUTVIEWBAR_SCROLLRBUTTON_DISABLED : OUTPUTVIEWBAR_SCROLLRBUTTON_DEFAULT)]))); )
		{
			if (pBitmap->GetObject(sizeof(BITMAP), &sBitmap) == sizeof(BITMAP)) pDC->BitBlt(rButton.left, rButton.top, sBitmap.bmWidth, sBitmap.bmHeight, &cDC, 0, 0, SRCAND);
			cDC.SelectObject(pOldBitmap);
			break;
		}
		cDC.DeleteDC();
	}
}
VOID COutputViewBar::DrawScrollRButton(CPoint point, UINT bPushed)
{
	CDC  *pDC;
	UINT  nState;

	if ((pDC = GetDC()))
	{
		for (nState = (bPushed != (UINT)-1) ? ((bPushed) ? BST_PUSHED : 0) : (m_nState[1] & BST_PUSHED), nState |= (!IsScrollRButtonEnabled()) ? BST_INDETERMINATE : 0; m_nState[1] != nState; )
		{
			m_nState[1] = nState;
			DrawScrollRButton(pDC);
			break;
		}
		ReleaseDC(pDC);
	}
}

BOOL COutputViewBar::IsPointOnScrollLButton(CPoint point) CONST
{
	CRect  rButton;

	CalcScrollLButtonPosition(rButton);
	return rButton.PtInRect(point);
}

BOOL COutputViewBar::IsPointOnScrollRButton(CPoint point) CONST
{
	CRect  rButton;

	CalcScrollRButtonPosition(rButton);
	return rButton.PtInRect(point);
}

BOOL COutputViewBar::IsPointOnSplitBar(CPoint point) CONST
{
	CRect  rSplitBar;

	CalcSplitBarPosition(rSplitBar);
	return rSplitBar.PtInRect(point);
}

UINT COutputViewBar::IsPointOnTab(CPoint point) CONST
{
	INT  nTab;
	INT  nTabs;
	CRect  rTab;

	for (nTab = 0, nTabs = (INT)m_nTabsPos.GetSize() / 2, rTab.SetRect(0, 0, 0, CalcTabsExtent().cy); nTab < nTabs; nTab++)
	{
		rTab.SetRect(m_nTabsPos.GetAt(2 * nTab) + rTab.Height() / 2, rTab.top, m_nTabsPos.GetAt(2 * nTab + 1) - rTab.Height() / 2, rTab.bottom);
		if ((rTab.PtInRect(point) || ((nTab == GetCurTab() || !nTab) && (point.x >= (INT)m_nTabsPos.GetAt(2 * nTab) + point.y / 2 && point.x <= (INT)m_nTabsPos.GetAt(2 * nTab + 1) - point.y / 2)) || ((nTab != GetCurTab() && (nTab == nTabs - 1 || GetCurTab() != nTab + 1) && nTab) && (point.x >(INT) m_nTabsPos.GetAt(2 * nTab) + abs(rTab.Height() / 2 - point.y) && point.x <= (INT)m_nTabsPos.GetAt(2 * nTab + 1) - point.y / 2)) || ((GetCurTab() == nTab + 1 && nTab) && (point.x > (INT)m_nTabsPos.GetAt(2 * nTab) + abs(rTab.Height() / 2 - point.y) && point.x < (INT)m_nTabsPos.GetAt(2 * nTab + 1) - abs(rTab.Height() / 2 - point.y)))) && point.x < m_nSplitPos) break;
	}
	return((nTab < nTabs) ? nTab : -1);
}

BOOL COutputViewBar::IsScrollLButtonDown() CONST
{
	return((m_nState[0] & BST_PUSHED) ? TRUE : FALSE);
}

BOOL COutputViewBar::IsScrollRButtonDown() CONST
{
	return((m_nState[1] & BST_PUSHED) ? TRUE : FALSE);
}

BOOL COutputViewBar::IsScrollLButtonEnabled()
{
	return((m_nTabPos < 0) ? TRUE : FALSE);
}

BOOL COutputViewBar::IsScrollRButtonEnabled()
{
	return((m_nSplitPos - m_nTabPos < CalcExtent().cx - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH) ? TRUE : FALSE);
}

VOID COutputViewBar::StartTabsScrolling()
{
	SetTimer(OUTPUTVIEWBAR_SCROLL_TIMERID, OUTPUTVIEWBAR_SCROLL_TIMEOUT, NULL);
}

VOID COutputViewBar::ScrollTabs(BOOL bLeft)
{
	INT  nTabPos;
	CRect  rViewBar;
	CRect  rButton[2];

	if ((nTabPos = (bLeft) ? min(m_nTabPos + OUTPUTVIEWBAR_SCROLL_INTERVAL, 0) : max(m_nTabPos - OUTPUTVIEWBAR_SCROLL_INTERVAL, m_nSplitPos - (CalcExtent().cx - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH))) != m_nTabPos)
	{
		if (!nTabPos || nTabPos == m_nSplitPos - (CalcExtent().cx - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH))
		{
			m_nTabPos = nTabPos;
			Invalidate(FALSE);
			UpdateWindow();
			return;
		}
		GetClientRect(rViewBar);
		CalcScrollLButtonPosition(rButton[0]);
		CalcScrollRButtonPosition(rButton[1]);
		InvalidateRect(CRect(rViewBar.left, rButton[0].bottom, rButton[1].right, rViewBar.bottom), FALSE);
		InvalidateRect(CRect(rButton[1].right, rViewBar.top, rViewBar.right, rViewBar.bottom), FALSE);
		m_nTabPos = nTabPos;
		UpdateWindow();
	}
}

VOID COutputViewBar::StopTabsScrolling()
{
	KillTimer(OUTPUTVIEWBAR_SCROLL_TIMERID);
}

VOID COutputViewBar::StartSplitBarDragging()
{
	m_bSplitBar = TRUE;
}

BOOL COutputViewBar::IsSplitBarDragged() CONST
{
	return m_bSplitBar;
}

VOID COutputViewBar::StopSplitBarDragging()
{
	m_bSplitBar = FALSE;
}

BEGIN_MESSAGE_MAP(COutputViewBar, CWnd)
	//{{AFX_MSG_MAP(COutputViewBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputViewBar message handlers

int COutputViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nButton;
	INT  nButtons;
	LOGFONT  lfFont;
	CFontTools  cFontTools(&lfFont);

	if (CWnd::OnCreate(lpCreateStruct) != -1 && m_wndScrollBar.Create(SBS_HORZ | SBS_BOTTOMALIGN | WS_CHILD | WS_CLIPSIBLINGS | WS_DISABLED | WS_VISIBLE, CRect(0, 0, 0, 0), this, OUTPUTVIEWBAR_SCROLLBAR_ID))
	{
		for (nButton = 0, nButtons = sizeof(m_bmpButton) / sizeof(m_bmpButton[0]); nButton < nButtons; nButton++) if (!m_bmpButton[nButton].LoadBitmap(min(IDB_OUTPUTSCROLLLEFTBUTTON, min(IDB_OUTPUTSCROLLLEFTBUTTONPRESSED, min(IDB_OUTPUTSCROLLLEFTBUTTONDISABLED, min(IDB_OUTPUTSCROLLRIGHTBUTTON, min(IDB_OUTPUTSCROLLRIGHTBUTTONPRESSED, IDB_OUTPUTSCROLLRIGHTBUTTONDISABLED))))) + nButton)) break;
		for (lfFont.lfHeight = min(CalcTabsExtent().cy - 2 * GetSystemMetrics(SM_CYEDGE), cFontTools.QueryHeight(&lfFont)); m_fntTabs.CreateFontIndirect(&lfFont); ) return((nButton == nButtons) ? 0 : -1);
	}
	return -1;
}

void COutputViewBar::OnSize(UINT nType, int cx, int cy)
{
	AdjustSplitPosition();
	CWnd::OnSize(nType, cx, cy);
}

void COutputViewBar::OnPaint()
{
	CPaintDC  cDC(this);

	DrawViewBar(&cDC);
}

BOOL COutputViewBar::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	CPoint  point(GetCurrentMessage()->pt);

	ScreenToClient(&point);
	if (IsPointOnSplitBar(point) || IsSplitBarDragged())
	{
		SetCursor(LoadCursor(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_SPLITHORIZONTAL)));
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void COutputViewBar::OnMouseMove(UINT nFlags, CPoint point)
{
	INT  nTabPos;
	INT  nSplitPos;
	CRect  rButtons;
	CRect  rViewBar;
	CRect  rScrollBar;

	for (GetClientRect(rViewBar), CalcScrollRButtonPosition(rButtons), SetCursor((IsPointOnSplitBar(point) || IsSplitBarDragged()) ? LoadCursor(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_SPLITHORIZONTAL)) : LoadCursor((HINSTANCE)NULL, IDC_ARROW)); IsWindow(m_wndScrollBar.GetSafeHwnd()) && HIBYTE(GetKeyState(VK_LBUTTON)) && IsSplitBarDragged(); )
	{
		for (rScrollBar.SetRect((nSplitPos = min(max(point.x, rButtons.right), rViewBar.right - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH)) + OUTPUTVIEWBAR_SPLITBAR_WIDTH, rViewBar.top, rViewBar.right, rViewBar.bottom), InvalidateRect(CRect((nSplitPos > m_nSplitPos) ? m_nSplitPos : nSplitPos, rViewBar.top, nSplitPos + OUTPUTVIEWBAR_SPLITBAR_WIDTH, rViewBar.bottom), FALSE); (nTabPos = m_nTabPos) < 0 && m_nSplitPos < nSplitPos && m_nTabPos + CalcExtent().cx - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH < nSplitPos; )
		{
			if ((nTabPos = min(nSplitPos - (CalcExtent().cx - CalcScrollExtent().cx - OUTPUTVIEWBAR_SPLITBAR_WIDTH), 0)) < 0)
			{
				InvalidateRect(CRect(rViewBar.left, rButtons.bottom + 1, rButtons.right, rViewBar.bottom), FALSE);
				InvalidateRect(CRect(rButtons.right + 1, rViewBar.top, rViewBar.right, rViewBar.bottom), FALSE);
				break;
			}
			Invalidate(FALSE);
			break;
		}
		m_wndScrollBar.MoveWindow(rScrollBar);
		m_nSplitPos = nSplitPos;
		m_nTabPos = nTabPos;
		UpdateWindow();
		break;
	}
	CWnd::OnMouseMove(nFlags, point);
}

void COutputViewBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nTab;

	if (IsScrollLButtonEnabled() && IsPointOnScrollLButton(point))
	{
		DrawScrollLButton(point, TRUE);
		DrawScrollRButton(point);
		StartTabsScrolling();
		ScrollTabs(TRUE);
		SetCapture();
	}
	if (IsScrollRButtonEnabled() && IsPointOnScrollRButton(point))
	{
		DrawScrollRButton(point, TRUE);
		DrawScrollLButton(point);
		StartTabsScrolling();
		ScrollTabs(FALSE);
		SetCapture();
	}
	if (IsPointOnSplitBar(point))
	{
		DrawScrollLButton(point);
		DrawScrollRButton(point);
		StartSplitBarDragging();
		SetCapture();
	}
	if ((nTab = IsPointOnTab(point)) >= 0 && !IsPointOnScrollLButton(point) && !IsPointOnScrollRButton(point) && !IsSplitBarDragged()) SetCurTab(nTab);
	CWnd::OnLButtonDown(nFlags, point);
}

void COutputViewBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (IsScrollLButtonDown())
	{
		DrawScrollLButton(point, FALSE);
		DrawScrollRButton(point, FALSE);
		StopTabsScrolling();
		ReleaseCapture();
	}
	if (IsScrollRButtonDown())
	{
		DrawScrollLButton(point, FALSE);
		DrawScrollRButton(point, FALSE);
		StopTabsScrolling();
		ReleaseCapture();
	}
	if (IsSplitBarDragged())
	{
		DrawScrollLButton(point, FALSE);
		DrawScrollRButton(point, FALSE);
		StopSplitBarDragging();
		ReleaseCapture();
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void COutputViewBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	SCROLLINFO  sScrollInfo;

	switch (nSBCode)
	{
	case SB_TOP:
	case SB_BOTTOM:
	{ GetParent()->ScrollTo(SB_HORZ, nSBCode);
	break;
	}
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
	{ sScrollInfo.cbSize = sizeof(sScrollInfo);
	pScrollBar->GetScrollInfo(&sScrollInfo);
	GetParent()->ScrollTo(SB_HORZ, sScrollInfo.nTrackPos);
	break;
	}
	case SB_LINEUP:
	case SB_PAGEUP:
	{ GetParent()->ScrollUp(SB_HORZ, (nSBCode == SB_PAGEUP) ? TRUE : FALSE);
	break;
	}
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
	{ GetParent()->ScrollDown(SB_HORZ, (nSBCode == SB_PAGEDOWN) ? TRUE : FALSE);
	break;
	}
	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void COutputViewBar::OnTimer(UINT_PTR nEventID)
{
	POINT  ptCursor;

	for (GetCursorPos(&ptCursor), ScreenToClient(&ptCursor); nEventID == OUTPUTVIEWBAR_SCROLL_TIMERID; )
	{
		if (IsPointOnScrollLButton(ptCursor))
		{
			if (!IsScrollLButtonEnabled())
			{
				DrawScrollLButton(CPoint(0, 0), FALSE);
				DrawScrollRButton(ptCursor);
				StopTabsScrolling();
				ReleaseCapture();
			}
			else  ScrollTabs(TRUE);
		}
		if (IsPointOnScrollRButton(ptCursor))
		{
			if (!IsScrollRButtonEnabled())
			{
				DrawScrollRButton(CPoint(0, 0), FALSE);
				DrawScrollLButton(ptCursor);
				StopTabsScrolling();
				ReleaseCapture();
			}
			else  ScrollTabs(FALSE);
		}
		break;
	}
	CWnd::OnTimer(nEventID);
}

void COutputViewBar::OnDestroy()
{
	INT  nButton;
	INT  nButtons;

	for (nButton = 0, nButtons = sizeof(m_bmpButton) / sizeof(m_bmpButton[0]); nButton < nButtons; nButton++)
	{
		m_bmpButton[nButton].DeleteObject();
		continue;
	}
	m_fntTabs.DeleteObject();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// COutputViewConsoleWnd

IMPLEMENT_DYNCREATE(COutputViewConsoleWnd, CTextView)

COutputViewConsoleWnd::COutputViewConsoleWnd() : CTextView()
{
	ZeroMemory(&m_sScrollInfo[0], sizeof(SCROLLINFO));
	ZeroMemory(&m_sScrollInfo[1], sizeof(SCROLLINFO));
}

BOOL COutputViewConsoleWnd::Create(CWnd *pParentWnd, CONST RECT &rect, BOOL bIndent)
{
	return CTextView::Create(pParentWnd, rect, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE);
}

VOID COutputViewConsoleWnd::Activate()
{
	SendNotifyMessage(WM_SHOWWINDOW, TRUE, (LPARAM)-1);
}

BOOL COutputViewConsoleWnd::SetLine(INT nLine, LPCTSTR pszText)
{
	CRecentDocumentInfo  *pDocument;
	CTextViewLock  cLock(this);

	if ((pDocument = (SetText(nLine, pszText)) ? m_pDocuments.GetAt(nLine) : (CRecentDocumentInfo *)NULL))
	{
		pDocument->Copy(&m_cDocument);
		UpdateScrollBars();
		return TRUE;
	}
	return FALSE;
}
BOOL COutputViewConsoleWnd::SetLine(INT nLine, LPCTSTR pszText, CONST CRecentDocumentInfo *pDocumentInfo)
{
	CRecentDocumentInfo  *pDocument;
	CTextViewLock  cLock(this);

	if ((pDocument = (SetText(nLine, pszText)) ? m_pDocuments.GetAt(nLine) : (CRecentDocumentInfo *)NULL))
	{
		pDocument->Copy(pDocumentInfo);
		UpdateScrollBars();
		return TRUE;
	}
	return FALSE;
}

CString COutputViewConsoleWnd::GetLine(INT nLine) CONST
{
	CString  szText;

	return((GetText(nLine, szText)) ? szText : EMPTYSTRING);
}
CString COutputViewConsoleWnd::GetLine(INT nLine, CRecentDocumentInfo *pDocumentInfo) CONST
{
	CString  szText;
	CRecentDocumentInfo  *pDocument;
	CTextViewLock  cLock(this);

	if ((pDocument = (GetText(nLine, szText)) ? m_pDocuments.GetAt(nLine) : (CRecentDocumentInfo *)NULL)) pDocumentInfo->Copy(pDocument);
	return szText;
}

BOOL COutputViewConsoleWnd::InsertLine(INT nLine, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute)
{
	CRecentDocumentInfo  *pDocument;
	CTextViewLock  cLock(this);

	if ((pDocument = (InsertText((nLine = (nLine < 0) ? GetLineCount() : nLine), pszText, pAttribute)) ? new CRecentDocumentInfo : (CRecentDocumentInfo *)NULL))
	{
		m_pDocuments.InsertAt(nLine, pDocument, 1);
		pDocument->Copy(&m_cDocument);
		UpdateScrollBars();
		return TRUE;
	}
	return FALSE;
}

BOOL COutputViewConsoleWnd::DeleteLine(INT nLine)
{
	CRecentDocumentInfo  *pDocument;
	CTextViewLock  cLock(this);

	if ((pDocument = (DeleteText(nLine)) ? m_pDocuments.GetAt(nLine) : (CRecentDocumentInfo *)NULL))
	{
		m_pDocuments.RemoveAt(nLine);
		UpdateScrollBars();
		delete pDocument;
		return TRUE;
	}
	return FALSE;
}

BOOL COutputViewConsoleWnd::SetCurLine(INT nLine)
{
	CTextViewLock  cLock(this);

	if (SetCurText(nLine))
	{
		UpdateScrollBars();
		return TRUE;
	}
	return FALSE;
}

INT COutputViewConsoleWnd::GetCurLine() CONST
{
	return GetCurText();
}

INT COutputViewConsoleWnd::GetLineCount() CONST
{
	return GetTextCount();
}

VOID COutputViewConsoleWnd::ResetContent()
{
	CTextViewLock  cLock(this);

	for (m_cDocument.Reset(), m_pDocuments.RemoveAll(); DeleteAllText(); )
	{
		UpdateScrollBars();
		break;
	}
}

BOOL COutputViewConsoleWnd::SetContext(CONST CRecentDocumentInfo *pDocument)
{
	CTextViewLock  cLock(this);

	m_cDocument.Copy(pDocument);
	return TRUE;
}

BOOL COutputViewConsoleWnd::GetContext(CRecentDocumentInfo *pDocument) CONST
{
	CString  szName;
	CString  szTitle;
	ULONGLONG  nComponent;
	CTextViewLock  cLock(this);

	if (m_cDocument.GetDocument(szName, szTitle, nComponent))
	{
		pDocument->Copy(&m_cDocument);
		return TRUE;
	}
	return FALSE;
}

VOID COutputViewConsoleWnd::SetScrollInfo(UINT nBar, CONST SCROLLINFO *pScrollInfo)
{
	CTextViewLock  cLock(this);

	CopyMemory(&m_sScrollInfo[0], pScrollInfo, (nBar == SB_HORZ) ? sizeof(SCROLLINFO) : 0);
	CopyMemory(&m_sScrollInfo[1], pScrollInfo, (nBar == SB_VERT) ? sizeof(SCROLLINFO) : 0);
	m_wndContentCtrl.m_nScrollPos[0] = m_sScrollInfo[0].nPos;
	m_wndContentCtrl.m_nScrollPos[1] = m_sScrollInfo[1].nPos;
	DrawContent();
}

VOID COutputViewConsoleWnd::GetScrollInfo(UINT nBar, SCROLLINFO *pScrollInfo) CONST
{
	CTextViewLock  cLock(this);

	CopyMemory(pScrollInfo, &m_sScrollInfo[nBar == SB_VERT], sizeof(SCROLLINFO));
}

VOID COutputViewConsoleWnd::UpdateScrollBars()
{
	CRect  rContent;
	CSize  sizeContent;
	CTextViewLock  cLock(this);

	for (m_wndContentCtrl.GetClientRect(rContent), sizeContent = m_wndContentCtrl.CalcExtent(), m_sScrollInfo[0].cbSize = m_sScrollInfo[1].cbSize = sizeof(SCROLLINFO), m_sScrollInfo[0].fMask = m_sScrollInfo[1].fMask = SIF_ALL, m_sScrollInfo[0].nMin = m_sScrollInfo[0].nTrackPos = 0, m_sScrollInfo[1].nMin = m_sScrollInfo[1].nTrackPos = 0, m_sScrollInfo[0].nMax = (rContent.Width() < sizeContent.cx) ? sizeContent.cx : 0, m_sScrollInfo[1].nMax = (rContent.Height() < sizeContent.cy) ? sizeContent.cy : 0, m_sScrollInfo[0].nPage = (m_sScrollInfo[0].nMax > 0) ? rContent.Width() : 0, m_sScrollInfo[1].nPage = (m_sScrollInfo[1].nMax > 0) ? rContent.Height() : 0, m_sScrollInfo[0].nPos = m_wndContentCtrl.m_nScrollPos[0], m_sScrollInfo[1].nPos = m_wndContentCtrl.m_nScrollPos[1]; !GetNextWindow(GW_HWNDPREV); )
	{
		GetParent()->SetScrollInfo(SB_HORZ, &m_sScrollInfo[0]);
		GetParent()->SetScrollInfo(SB_VERT, &m_sScrollInfo[1]);
		break;
	}
}

COutputView *COutputViewConsoleWnd::GetParent() CONST
{
	return((COutputView *)CTextView::GetParent());
}

BEGIN_MESSAGE_MAP(COutputViewConsoleWnd, CTextView)
	//{{AFX_MSG_MAP(COutputViewConsoleWnd)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputViewConsoleWnd message handlers

int COutputViewConsoleWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFont  cFont;
	BITMAP  sBitmap[2];
	CBitmap  cBitmap[2];
	CTextViewLock  cLock(this);

	if (CTextView::OnCreate(lpCreateStruct) != -1)
	{
		if (cFont.CreateFont((cBitmap[0].LoadBitmap(IDB_OUTPUTSCROLLLEFTBUTTON) && cBitmap[1].LoadBitmap(IDB_OUTPUTSCROLLRIGHTBUTTON) && cBitmap[0].GetObject(sizeof(BITMAP), &sBitmap[0]) && cBitmap[1].GetObject(sizeof(BITMAP), &sBitmap[1])) ? max(sBitmap[0].bmHeight, sBitmap[1].bmHeight) : GetSystemMetrics(SM_CYSMICON), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE, (LPCTSTR)NULL))
		{
			SetTextFont(&cFont);
			return 0;
		}
	}
	return -1;
}

void COutputViewConsoleWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	if (nStatus == (UINT)-1)
	{
		SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		return;
	}
	CTextView::OnShowWindow(bShow, nStatus);
}

void COutputViewConsoleWnd::OnSize(UINT nType, int cx, int cy)
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	for (RecalcLayout(); (nIndex = GetCurLine()) >= 0; )
	{
		ScrollTo(nIndex);
		break;
	}
	UpdateScrollBars();
	CTextView::OnSize(nType, cx, cy);
}

BOOL COutputViewConsoleWnd::OnEraseBkgnd(CDC *pDC)
{
	CRect  rConsole[2];

	for (GetWindowRect(rConsole[0]), GetParent()->ScreenToClient(rConsole[0]), GetParent()->CalcClientRect(rConsole[1]); !rConsole[0].EqualRect(rConsole[1]); )
	{
		MoveWindow(rConsole[1]);
		return TRUE;
	}
	return CTextView::OnEraseBkgnd(pDC);
}

void COutputViewConsoleWnd::OnNcPaint()
{
	CRect  rConsole[2];

	for (GetWindowRect(rConsole[0]), GetParent()->ScreenToClient(rConsole[0]), GetParent()->CalcClientRect(rConsole[1]); !rConsole[0].EqualRect(rConsole[1]); )
	{
		MoveWindow(rConsole[1]);
		return;
	}
	CTextView::OnNcPaint();
}

BOOL COutputViewConsoleWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	SCROLLINFO  sScrollInfo;

	for (GetScrollInfo(SB_VERT, &sScrollInfo); sScrollInfo.nMax - sScrollInfo.nMin >= (INT)sScrollInfo.nPage; )
	{
		if (sScrollInfo.nPos < sScrollInfo.nMax  &&  zDelta < 0) sScrollInfo.nPos = min(sScrollInfo.nPos + (INT)sScrollInfo.nPage / 10, sScrollInfo.nMax - (INT)sScrollInfo.nPage + 1);
		if (sScrollInfo.nPos > sScrollInfo.nMin  &&  zDelta > 0) sScrollInfo.nPos = max(sScrollInfo.nPos - (INT)sScrollInfo.nPage / 10, sScrollInfo.nMin);
		SetScrollInfo(SB_VERT, &sScrollInfo);
		UpdateScrollBars();
		break;
	}
	return CTextView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL COutputViewConsoleWnd::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CString  szLine;
	CString  szTitle;
	CString  szMessage;
	CANDWnd  *pANDWnd;
	CGRDWnd  *pGRDWnd;
	CMMDWnd  *pMMDWnd;
	CPODWnd  *pPODWnd;
	CPtrArray  pDisplays;
	ULONGLONG  nComponent;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;
	CTCFunctionWnd  *pTCFunctionWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CTCProcedureWnd  *pTCProcedureWnd;
	CTMParameterWnd  *pTMParameterWnd;
	CTCParameterWnd  *pTCParameterWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CRecentDocumentInfo  *pDocument;
	CTextViewLock  cLock(this);

	if (message == WM_LBUTTONDBLCLK)
	{
		for (BeginWaitCursor(); (pDocument = m_pDocuments.GetAt(GetCurText())); )
		{
			if (pDocument->GetDocument(szName, szTitle, nComponent))
			{
				switch (DATABASECOMPONENTFROMCODE(nComponent))
				{
				case DATABASE_COMPONENT_TMPACKET:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0 || lstrlen(szTitle) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET)
					{
						if ((pTMPacketWnd = (CTMPacketWnd *)pDisplayWnd)->GetName() == szName)
						{
							pTMPacketWnd->MDIActivate();
							pTMPacketWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					if ((pTMPacketWnd = new CTMPacketWnd(szName)) && pTMPacketWnd->Create(GetMainWnd()))
					{
						pTMPacketWnd->GotoTable(nComponent, szTitle);
						EndWaitCursor();
						return FALSE;
					}
					szMessage.Format(STRING(IDS_TMPACKET_FAILURE_LOAD), (!szName.IsEmpty()) ? (LPCTSTR)szName : STRING(IDS_WINDOW_UNTITLED));
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_TCFUNCTION:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0 || lstrlen(szTitle) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION)
					{
						if ((pTCFunctionWnd = (CTCFunctionWnd *)pDisplayWnd)->GetName() == szName)
						{
							pTCFunctionWnd->MDIActivate();
							pTCFunctionWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					if ((pTCFunctionWnd = new CTCFunctionWnd(szName)) && pTCFunctionWnd->Create(GetMainWnd()))
					{
						pTCFunctionWnd->GotoTable(nComponent, szTitle);
						EndWaitCursor();
						return FALSE;
					}
					szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_LOAD), (!szName.IsEmpty()) ? (LPCTSTR)szName : STRING(IDS_WINDOW_UNTITLED));
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_TCSEQUENCE:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0 || lstrlen(szTitle) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE)
					{
						if ((pTCSequenceWnd = (CTCSequenceWnd *)pDisplayWnd)->GetName() == szName)
						{
							pTCSequenceWnd->MDIActivate();
							pTCSequenceWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					if ((pTCSequenceWnd = new CTCSequenceWnd(szName)) && pTCSequenceWnd->Create(GetMainWnd()))
					{
						pTCSequenceWnd->GotoTable(nComponent, szTitle);
						EndWaitCursor();
						return FALSE;
					}
					szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_LOAD), (!szName.IsEmpty()) ? (LPCTSTR)szName : STRING(IDS_WINDOW_UNTITLED));
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_TCPROCEDURE:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0) ? EnumDisplayWindows(pDisplays) : -1, GetText(GetCurText(), szLine); nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE)
					{
						if (_ttoi((pTCProcedureWnd = (CTCProcedureWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
						{
							pTCProcedureWnd->MDIActivate();
							pTCProcedureWnd->GotoSourceCode(szLine);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					for (; (pTCProcedureWnd = new CTCProcedureWnd(szName)); )
					{
						if (pTCProcedureWnd->Create(GetMainWnd()))
						{
							pTCProcedureWnd->GotoSourceCode(szLine);
							EndWaitCursor();
							return FALSE;
						}
						break;
					}
					szMessage.Format(STRING(IDS_SCRIPT_FAILURE_LOAD), (LPCTSTR)szName);
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_TMPARAMETER:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0 || lstrlen(szTitle) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER)
					{
						if ((pTMParameterWnd = (CTMParameterWnd *)pDisplayWnd)->GetName() == szName)
						{
							pTMParameterWnd->MDIActivate();
							pTMParameterWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					if ((pTMParameterWnd = new CTMParameterWnd(szName)) && pTMParameterWnd->Create(GetMainWnd()))
					{
						pTMParameterWnd->GotoTable(nComponent, szTitle);
						EndWaitCursor();
						return FALSE;
					}
					szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_LOAD), (!szName.IsEmpty()) ? (LPCTSTR)szName : STRING(IDS_WINDOW_UNTITLED));
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_TCPARAMETER:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0 || lstrlen(szTitle) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER)
					{
						if ((pTCParameterWnd = (CTCParameterWnd *)pDisplayWnd)->GetName() == szName)
						{
							pTCParameterWnd->MDIActivate();
							pTCParameterWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					if ((pTCParameterWnd = new CTCParameterWnd(szName)) && pTCParameterWnd->Create(GetMainWnd()))
					{
						pTCParameterWnd->GotoTable(nComponent, szTitle);
						EndWaitCursor();
						return FALSE;
					}
					szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_LOAD), (!szName.IsEmpty()) ? (LPCTSTR)szName : STRING(IDS_WINDOW_UNTITLED));
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_OBPROCESSOR:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0 || lstrlen(szTitle) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR)
					{
						if ((pOBProcessorWnd = (COBProcessorWnd *)pDisplayWnd)->GetName() == szName)
						{
							pOBProcessorWnd->MDIActivate();
							pOBProcessorWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					if ((pOBProcessorWnd = new COBProcessorWnd(szName)) && pOBProcessorWnd->Create(GetMainWnd()))
					{
						pOBProcessorWnd->GotoTable(nComponent, szTitle);
						EndWaitCursor();
						return FALSE;
					}
					szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_LOAD), (!szName.IsEmpty()) ? (LPCTSTR)szName : STRING(IDS_WINDOW_UNTITLED));
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_AND:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND)
					{
						if ((pANDWnd = (CANDWnd *)pDisplayWnd)->GetName() == szName)
						{
							pANDWnd->MDIActivate();
							pANDWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					for (; (pANDWnd = new CANDWnd(szName)); )
					{
						if (pANDWnd->Create(GetMainWnd()))
						{
							EndWaitCursor();
							return FALSE;
						}
						break;
					}
					szMessage.Format(STRING(IDS_AND_FAILURE_LOAD), (LPCTSTR)szName);
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_GRD:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD)
					{
						if ((pGRDWnd = (CGRDWnd *)pDisplayWnd)->GetName() == szName)
						{
							pGRDWnd->MDIActivate();
							pGRDWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					for (; (pGRDWnd = new CGRDWnd(szName)); )
					{
						if (pGRDWnd->Create(GetMainWnd()))
						{
							EndWaitCursor();
							return FALSE;
						}
						break;
					}
					szMessage.Format(STRING(IDS_GRD_FAILURE_LOAD), (LPCTSTR)szName);
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_MMD:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0) ? EnumDisplayWindows(pDisplays) : -1, GetText(GetCurText(), szLine); nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD)
					{
						if (_ttoi((pMMDWnd = (CMMDWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
						{
							pMMDWnd->MDIActivate();
							pMMDWnd->GoToMimicsCtrlCode(szLine);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					for (; (pMMDWnd = new CMMDWnd(szName)); )
					{
						if (pMMDWnd->Create(GetMainWnd()))
						{
							pMMDWnd->GoToMimicsCtrlCode(szLine);
							EndWaitCursor();
							return FALSE;
						}
						break;
					}
					szMessage.Format(STRING(IDS_MMD_FAILURE_LOAD), (LPCTSTR)szName);
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_POD:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD)
					{
						if ((pPODWnd = (CPODWnd *)pDisplayWnd)->GetName() == szName)
						{
							pPODWnd->MDIActivate();
							pPODWnd->GotoTable(nComponent, szTitle);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					for (; (pPODWnd = new CPODWnd(szName)); )
					{
						if (pPODWnd->Create(GetMainWnd()))
						{
							EndWaitCursor();
							return FALSE;
						}
						break;
					}
					szMessage.Format(STRING(IDS_POD_FAILURE_LOAD), (LPCTSTR)szName);
					ShowMessage(szMessage);
				}
				break;
				}
				case DATABASE_COMPONENT_SCRIPT:
				{ for (nDisplay = 0, nDisplays = (lstrlen(szName) > 0) ? EnumDisplayWindows(pDisplays) : -1, GetText(GetCurText(), szLine); nDisplay < nDisplays; nDisplay++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT)
					{
						if (_ttoi((pScriptWnd = (CScriptWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
						{
							pScriptWnd->MDIActivate();
							pScriptWnd->GoToScriptCode(szLine);
							EndWaitCursor();
							return FALSE;
						}
					}
				}
				if (nDisplay == nDisplays)
				{
					for (; (pScriptWnd = new CScriptWnd(szName)); )
					{
						if (pScriptWnd->Create(GetMainWnd()))
						{
							pScriptWnd->GoToScriptCode(szLine);
							EndWaitCursor();
							return FALSE;
						}
						break;
					}
					szMessage.Format(STRING(IDS_SCRIPT_FAILURE_LOAD), (LPCTSTR)szName);
					ShowMessage(szMessage);
				}
				break;
				}
				default:
				{ if ((!lstrcmp(szName, STRING(IDS_OUTPUTWINDOW_QUERY1TAB)) || !lstrcmp(szName, STRING(IDS_OUTPUTWINDOW_QUERY2TAB))) && nComponent == (ULONGLONG)-1)
				{
					GetMainWnd()->DoFind(szTitle);
					EndWaitCursor();
					return FALSE;
				}
				break;
				}
				}
			}
			break;
		}
		CAudioDevice::AlertBySound();
		EndWaitCursor();
		return FALSE;
	}
	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_RETURN)
		{
			StopTextBlinking(GetCurLine());
			return FALSE;
		}
		if (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_PRIOR || wParam == VK_NEXT)
		{
			UpdateScrollBars();
			return FALSE;
		}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// COutputView

IMPLEMENT_DYNCREATE(COutputView, CWnd)

COutputView::COutputView() : CWnd()
{
	m_pParentWnd = (CWnd *)NULL;
}

BOOL COutputView::Create(CWnd *pParentWnd)
{
	return CWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), EMPTYSTRING, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), 0);
}

VOID COutputView::SetConsole(LPCTSTR pszConsole)
{
	SCROLLINFO  sScrollInfo[2];
	COutputViewConsoleWnd  *pConsole;

	if ((pConsole = FindConsole(pszConsole)))
	{
		pConsole->Activate();
		pConsole->GetScrollInfo(SB_HORZ, &sScrollInfo[0]);
		pConsole->GetScrollInfo(SB_VERT, &sScrollInfo[1]);
		SetScrollInfo(SB_HORZ, &sScrollInfo[0]);
		SetScrollInfo(SB_VERT, &sScrollInfo[1]);
		m_wndViewBar.SetCurTab(FindConsoleIndex(pszConsole));
	}
}
VOID COutputView::SetConsole(INT nIndex)
{
	SCROLLINFO  sScrollInfo[2];
	COutputViewConsoleWnd  *pConsole;

	if ((pConsole = FindConsoleIndex(nIndex)))
	{
		pConsole->Activate();
		pConsole->GetScrollInfo(SB_HORZ, &sScrollInfo[0]);
		pConsole->GetScrollInfo(SB_VERT, &sScrollInfo[1]);
		SetScrollInfo(SB_HORZ, &sScrollInfo[0]);
		SetScrollInfo(SB_VERT, &sScrollInfo[1]);
		m_wndViewBar.SetCurTab(nIndex);
	}
}

INT COutputView::GetConsole(CString &szConsole) CONST
{
	szConsole = m_szConsoles.GetAt(GetConsole());
	return m_wndViewBar.GetCurTab();
}
INT COutputView::GetConsole() CONST
{
	return m_wndViewBar.GetCurTab();
}

BOOL COutputView::SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->SetLine(nLine, pszText) : FALSE);
}
BOOL COutputView::SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CRecentDocumentInfo *pDocumentInfo)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->SetLine(nLine, pszText, pDocumentInfo) : FALSE);
}

CString COutputView::GetLine(LPCTSTR pszConsole, INT nLine) CONST
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? CString(pConsole->GetLine(nLine)) : EMPTYSTRING);
}
CString COutputView::GetLine(LPCTSTR pszConsole, INT nLine, CRecentDocumentInfo *pDocumentInfo) CONST
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? CString(pConsole->GetLine(nLine, pDocumentInfo)) : EMPTYSTRING);
}

BOOL COutputView::InsertLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->InsertLine(nLine, pszText, pAttribute) : FALSE);
}

BOOL COutputView::DeleteLine(LPCTSTR pszConsole, INT nLine)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->DeleteLine(nLine) : FALSE);
}

BOOL COutputView::SetCurLine(LPCTSTR pszConsole, INT nLine)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->SetCurLine(nLine) : FALSE);
}

INT COutputView::GetCurLine(LPCTSTR pszConsole) CONST
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->GetCurLine() : -1);
}

INT COutputView::GetLineCount(LPCTSTR pszConsole) CONST
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->GetLineCount() : -1);
}

VOID COutputView::ResetContent(LPCTSTR pszConsole)
{
	COutputViewConsoleWnd  *pConsole;

	if ((pConsole = FindConsole(pszConsole))) pConsole->ResetContent();
}

VOID COutputView::ResetAllContent()
{
	INT  nConsole;
	INT  nConsoles;
	COutputViewConsoleWnd  *pConsole;

	for (nConsole = 0, nConsoles = (INT)m_pwndConsoles.GetSize(); nConsole < nConsoles; nConsole++)
	{
		if ((pConsole = (COutputViewConsoleWnd *)m_pwndConsoles.GetAt(nConsole)))
		{
			pConsole->ResetContent();
			continue;
		}
	}
}

BOOL COutputView::SetContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->SetContext(pDocument) : FALSE);
}

BOOL COutputView::GetContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument) CONST
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->GetContext(pDocument) : FALSE);
}

BOOL COutputView::StartBlinking(LPCTSTR pszConsole, INT nLine)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->StartTextBlinking(nLine) : FALSE);
}

BOOL COutputView::StopBlinking(LPCTSTR pszConsole, INT nLine)
{
	COutputViewConsoleWnd  *pConsole;

	return(((pConsole = FindConsole(pszConsole))) ? pConsole->StopTextBlinking(nLine) : FALSE);
}

VOID COutputView::ScrollTo(UINT nBar, INT nPos)
{
	SCROLLINFO  sScrollInfo;

	for (GetScrollInfo(nBar, &sScrollInfo); nPos != sScrollInfo.nPos; )
	{
		sScrollInfo.nPos = nPos;
		SetScrollInfo(nBar, &sScrollInfo);
		break;
	}
}
VOID COutputView::ScrollTo(UINT nBar, UINT nCode)
{
	INT  nPos;
	SCROLLINFO  sScrollInfo;

	for (GetScrollInfo(nBar, &sScrollInfo); (nPos = (nCode == SB_TOP || nCode == SB_ENDSCROLL) ? sScrollInfo.nMin : ((nCode == SB_BOTTOM) ? (sScrollInfo.nMax - sScrollInfo.nPage + 1) : sScrollInfo.nPos)) != sScrollInfo.nPos; )
	{
		sScrollInfo.nPos = nPos;
		SetScrollInfo(nBar, &sScrollInfo);
		break;
	}
}

VOID COutputView::ScrollUp(UINT nBar, BOOL bPage)
{
	INT  nPos;
	CRect  rConsole;
	SCROLLINFO  sScrollInfo;
	COutputViewConsoleWnd  *pConsole;

	if ((pConsole = FindConsole()))
	{
		for (GetScrollInfo(nBar, &sScrollInfo), pConsole->GetClientRect(rConsole); (nPos = (bPage) ? max((nBar == SB_HORZ) ? (sScrollInfo.nPos - rConsole.Width()) : (sScrollInfo.nPos - (INT)sScrollInfo.nPage), sScrollInfo.nMin) : max((nBar == SB_HORZ) ? (sScrollInfo.nPos - max(rConsole.Width() / 16, 1)) : (sScrollInfo.nPos - max(rConsole.Height() / 16, 1)), sScrollInfo.nMin)) != sScrollInfo.nPos; )
		{
			sScrollInfo.nPos = nPos;
			SetScrollInfo(nBar, &sScrollInfo);
			break;
		}
	}
}

VOID COutputView::ScrollDown(UINT nBar, BOOL bPage)
{
	INT  nPos;
	CRect  rConsole;
	SCROLLINFO  sScrollInfo;
	COutputViewConsoleWnd  *pConsole;

	if ((pConsole = FindConsole()))
	{
		for (GetScrollInfo(nBar, &sScrollInfo), pConsole->GetClientRect(rConsole); (nPos = (bPage) ? min((nBar == SB_HORZ) ? (sScrollInfo.nPos + rConsole.Width()) : (sScrollInfo.nPos + (INT)sScrollInfo.nPage), sScrollInfo.nMax - (INT)sScrollInfo.nPage + 1) : min((nBar == SB_HORZ) ? (sScrollInfo.nPos + max(rConsole.Width() / 16, 1)) : (sScrollInfo.nPos + max(rConsole.Height() / 16, 1)), sScrollInfo.nMax - (INT)sScrollInfo.nPage + 1)) != sScrollInfo.nPos; )
		{
			sScrollInfo.nPos = nPos;
			SetScrollInfo(nBar, &sScrollInfo);
			break;
		}
	}
}

VOID COutputView::SetScrollInfo(UINT nBar, CONST SCROLLINFO *pScrollInfo)
{
	CRect  rView;
	SCROLLINFO  sScrollInfo;
	COutputViewConsoleWnd  *pConsole;

	if ((pConsole = FindConsole()))
	{
		for (CopyMemory(&sScrollInfo, pScrollInfo, sizeof(SCROLLINFO)), sScrollInfo.fMask = sScrollInfo.fMask | SIF_DISABLENOSCROLL; nBar == SB_HORZ; )
		{
			if (pScrollInfo->nMin || pScrollInfo->nMax)
			{
				pConsole->SetScrollInfo(nBar, pScrollInfo);
				m_wndViewBar.SetScrollInfo(&sScrollInfo);
				return;
			}
			for (GetClientRect(rView); rView.Width() > 0 || rView.Height() > 0; )
			{
				sScrollInfo.fMask = SIF_RANGE | SIF_DISABLENOSCROLL;
				m_wndViewBar.SetScrollInfo(&sScrollInfo);
				break;
			}
			return;
		}
		if (nBar == SB_VERT)
		{
			if (pScrollInfo->nMin || pScrollInfo->nMax)
			{
				pConsole->SetScrollInfo(nBar, pScrollInfo);
				m_wndScrollBar.SetScrollInfo(&sScrollInfo);
				return;
			}
			for (GetClientRect(rView); rView.Width() > 0 || rView.Height() > 0; )
			{
				sScrollInfo.fMask = SIF_RANGE | SIF_DISABLENOSCROLL;
				m_wndScrollBar.SetScrollInfo(&sScrollInfo);
				break;
			}
		}
	}
}

VOID COutputView::GetScrollInfo(UINT nBar, SCROLLINFO *pScrollInfo) CONST
{
	COutputViewConsoleWnd  *pConsole;

	if ((pConsole = FindConsole()))
	{
		pConsole->GetScrollInfo(nBar, pScrollInfo);
		return;
	}
}

VOID COutputView::SetParent(class COutputWnd *pParentWnd)
{
	CWnd::SetParent((m_pParentWnd = pParentWnd));
}

COutputWnd *COutputView::GetParent() CONST
{
	return((COutputWnd *)m_pParentWnd);
}

COutputViewConsoleWnd *COutputView::FindConsole() CONST
{
	return((m_pwndConsoles.GetSize() > GetConsole()) ? (COutputViewConsoleWnd *)m_pwndConsoles.GetAt(GetConsole()) : (COutputViewConsoleWnd *)NULL);
}
COutputViewConsoleWnd *COutputView::FindConsole(LPCTSTR pszConsole) CONST
{
	INT  nConsole;
	INT  nConsoles;

	for (nConsole = 0, nConsoles = (INT)m_szConsoles.GetSize(); nConsole < nConsoles; nConsole++)
	{
		if (m_szConsoles.GetAt(nConsole) == pszConsole) break;
		continue;
	}
	return((nConsole < nConsoles) ? (COutputViewConsoleWnd *)m_pwndConsoles.GetAt(nConsole) : (COutputViewConsoleWnd *)NULL);
}

COutputViewConsoleWnd *COutputView::FindConsoleIndex(INT nConsole) CONST
{
	return((nConsole >= 0 && nConsole < m_pwndConsoles.GetSize()) ? (COutputViewConsoleWnd *)m_pwndConsoles.GetAt(nConsole) : (COutputViewConsoleWnd *)NULL);
}
INT COutputView::FindConsoleIndex(LPCTSTR pszConsole) CONST
{
	INT  nConsole;
	INT  nConsoles;

	for (nConsole = 0, nConsoles = (INT)m_szConsoles.GetSize(); nConsole < nConsoles; nConsole++)
	{
		if (m_szConsoles.GetAt(nConsole) == pszConsole) break;
		continue;
	}
	return((nConsole < nConsoles) ? nConsole : -1);
}

VOID COutputView::CalcClientRect(LPRECT pRect) CONST
{
	CRect  rView[3];

	GetClientRect(rView[0]);
	GetWindowRect(rView[1]);
	GetParent()->CalcClientRect(rView[2]);
	rView[2].DeflateRect(rView[0].left - rView[1].left, rView[0].top - rView[1].top, rView[1].right - rView[0].right, rView[1].bottom - rView[0].bottom);
	SetRect(pRect, 0, 0, rView[2].Width() - GetSystemMetrics(SM_CXVSCROLL), rView[2].Height() - GetSystemMetrics(SM_CYHSCROLL));
}

VOID COutputView::CalcViewBarRect(LPRECT pRect) CONST
{
	CRect  rView[3];

	GetClientRect(rView[0]);
	GetWindowRect(rView[1]);
	GetParent()->CalcClientRect(rView[2]);
	rView[2].DeflateRect(rView[0].left - rView[1].left, rView[0].top - rView[1].top, rView[1].right - rView[0].right, rView[1].bottom - rView[0].bottom);
	SetRect(pRect, 0, rView[2].Height() - GetSystemMetrics(SM_CYHSCROLL), rView[2].Width() - GetSystemMetrics(SM_CXVSCROLL), rView[2].Height());
}

VOID COutputView::CalcScrollBarRect(LPRECT pRect) CONST
{
	CRect  rView[3];

	GetClientRect(rView[0]);
	GetWindowRect(rView[1]);
	GetParent()->CalcClientRect(rView[2]);
	rView[2].DeflateRect(rView[0].left - rView[1].left, rView[0].top - rView[1].top, rView[1].right - rView[0].right, rView[1].bottom - rView[0].bottom);
	SetRect(pRect, rView[2].Width() - GetSystemMetrics(SM_CXVSCROLL), 0, rView[2].Width(), rView[2].Height() - GetSystemMetrics(SM_CYHSCROLL));
}

void COutputView::PostNcDestroy()
{
	INT  nConsole;
	INT  nConsoles;
	COutputViewConsoleWnd  *pConsole;

	for (nConsole = 0, nConsoles = (INT)m_pwndConsoles.GetSize(); nConsole < nConsoles; nConsole++)
	{
		if ((pConsole = (COutputViewConsoleWnd *)m_pwndConsoles.GetAt(nConsole)))
		{
			delete pConsole;
			continue;
		}
	}
	m_pwndConsoles.RemoveAll();
	CWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COutputView, CWnd)
	//{{AFX_MSG_MAP(COutputView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputView message handlers

int COutputView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nConsole;
	INT  nConsoles;
	SCROLLINFO  sScrollInfo[2];
	COutputViewConsoleWnd  *pConsole;

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (nConsole = 0, nConsoles = MAXOUTPUTWINDOWTAB - MINOUTPUTWINDOWTAB + 1; nConsole < nConsoles; nConsole++)
		{
			if ((pConsole = (COutputViewConsoleWnd *) new COutputViewConsoleWnd) != (COutputViewConsoleWnd *)NULL)
			{
				if (pConsole->Create(this, CRect(0, 0, 0, 0), (!lstrcmp(STRING(MINOUTPUTWINDOWTAB + nConsole), STRING(IDS_OUTPUTWINDOW_MESSAGETAB)) || !lstrcmp(STRING(MINOUTPUTWINDOWTAB + nConsole), STRING(IDS_OUTPUTWINDOW_BUILDTAB))) ? TRUE : FALSE))
				{
					m_szConsoles.Add(STRING(MINOUTPUTWINDOWTAB + nConsole));
					m_pwndConsoles.Add(pConsole);
					continue;
				}
				delete pConsole;
			}
			break;
		}
		if (m_wndViewBar.Create(this, CRect(0, 0, 0, 0), m_szConsoles) && m_wndScrollBar.Create(SBS_VERT | SBS_RIGHTALIGN | WS_CHILD | WS_CLIPSIBLINGS | WS_DISABLED | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0))
		{
			ZeroMemory(&sScrollInfo[0], sizeof(SCROLLINFO));
			ZeroMemory(&sScrollInfo[1], sizeof(SCROLLINFO));
			sScrollInfo[0].fMask = SIF_RANGE | SIF_DISABLENOSCROLL;
			sScrollInfo[1].fMask = SIF_RANGE | SIF_DISABLENOSCROLL;
			m_wndViewBar.SetScrollInfo(&sScrollInfo[0]);
			m_wndScrollBar.SetScrollInfo(&sScrollInfo[1]);
			return((nConsole == nConsoles) ? 0 : -1);
		}
	}
	return -1;
}

void COutputView::OnSize(UINT nType, int cx, int cy)
{
	INT  nConsole;
	INT  nConsoles;
	CRect  rConsole;
	CRect  rViewBar;
	CRect  rScrollBar;
	COutputViewConsoleWnd  *pConsole;

	CalcClientRect(rConsole);
	for (nConsole = 0, nConsoles = (INT)m_pwndConsoles.GetSize(); nConsole < nConsoles; nConsole++)
	{
		if ((pConsole = (COutputViewConsoleWnd *)m_pwndConsoles.GetAt(nConsole)))
		{
			pConsole->MoveWindow(rConsole);
			continue;
		}
	}
	if (IsWindow(m_wndViewBar.GetSafeHwnd()))
	{
		CalcViewBarRect(rViewBar);
		m_wndViewBar.MoveWindow(rViewBar);
	}
	if (IsWindow(m_wndScrollBar.GetSafeHwnd()))
	{
		CalcScrollBarRect(rScrollBar);
		m_wndScrollBar.MoveWindow(rScrollBar);
	}
	CWnd::OnSize(nType, cx, cy);
}

BOOL COutputView::OnEraseBkgnd(CDC *pDC)
{
	INT  nConsole;
	INT  nConsoles;
	CRect  rConsole;
	CRect  rView[3];
	CRect  rViewBar;
	CRect  rScrollBar;
	COutputViewConsoleWnd  *pConsole;

	for (GetClientRect(rView[0]), GetWindowRect(rView[1]), GetParent()->ScreenToClient(rView[1]), GetParent()->CalcClientRect(rView[2]); !rView[1].EqualRect(rView[2]); )
	{
		MoveWindow(rView[2]);
		return TRUE;
	}
	for (nConsole = 0, nConsoles = (INT)m_pwndConsoles.GetSize(), CalcClientRect(rConsole); nConsole < nConsoles; nConsole++)
	{
		if ((pConsole = (COutputViewConsoleWnd *)m_pwndConsoles.GetAt(nConsole)))
		{
			pConsole->MoveWindow(rConsole);
			pConsole->UpdateWindow();
		}
	}
	if (IsWindow(m_wndViewBar.GetSafeHwnd()))
	{
		CalcViewBarRect(rViewBar);
		m_wndViewBar.MoveWindow(rViewBar);
		m_wndViewBar.UpdateWindow();
	}
	if (IsWindow(m_wndScrollBar.GetSafeHwnd()))
	{
		CalcScrollBarRect(rScrollBar);
		m_wndScrollBar.MoveWindow(rScrollBar);
		m_wndScrollBar.UpdateWindow();
	}
	pDC->FillRect(CRect(rView[0].right - GetSystemMetrics(SM_CXVSCROLL), rView[0].bottom - GetSystemMetrics(SM_CYHSCROLL), rView[0].right + 1, rView[0].bottom + 1), CBrush::FromHandle(GetSysColorBrush(COLOR_3DFACE)));
	return TRUE;
}

void COutputView::OnNcPaint()
{
	CRect  rView[2];

	for (GetWindowRect(rView[0]), GetParent()->ScreenToClient(rView[0]), GetParent()->CalcClientRect(rView[1]); !rView[0].EqualRect(rView[1]); )
	{
		MoveWindow(rView[1]);
		return;
	}
	CWnd::OnNcPaint();
}

void COutputView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	SCROLLINFO  sScrollInfo;

	switch (nSBCode)
	{
	case SB_TOP:
	case SB_BOTTOM:
	{ ScrollTo(SB_VERT, nSBCode);
	break;
	}
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
	{ sScrollInfo.cbSize = sizeof(sScrollInfo);
	pScrollBar->GetScrollInfo(&sScrollInfo);
	ScrollTo(SB_VERT, sScrollInfo.nTrackPos);
	break;
	}
	case SB_LINEUP:
	case SB_PAGEUP:
	{ ScrollUp(SB_VERT, (nSBCode == SB_PAGEUP) ? TRUE : FALSE);
	break;
	}
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
	{ ScrollDown(SB_VERT, (nSBCode == SB_PAGEDOWN) ? TRUE : FALSE);
	break;
	}
	}
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


/////////////////////////////////////////////////////////////////////////////
// COutputWnd

IMPLEMENT_DYNCREATE(COutputWnd, CToolWnd)

COutputWnd::COutputWnd(COutputWnd *pOutputWnd) : CToolWnd(pOutputWnd)
{
	m_pwndView = (COutputView *)NULL;
}

VOID COutputWnd::SetConsole(LPCTSTR pszConsole)
{
	m_pwndView->SetConsole(pszConsole);
}

CString COutputWnd::GetConsole() CONST
{
	CString  szConsole;

	m_pwndView->GetConsole(szConsole);
	return szConsole;
}

BOOL COutputWnd::SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText)
{
	return m_pwndView->SetLine(pszConsole, nLine, pszText);
}
BOOL COutputWnd::SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CRecentDocumentInfo *pDocumentInfo)
{
	return m_pwndView->SetLine(pszConsole, nLine, pszText, pDocumentInfo);
}

CString COutputWnd::GetLine(LPCTSTR pszConsole, INT nLine) CONST
{
	return m_pwndView->GetLine(pszConsole, nLine);
}
CString COutputWnd::GetLine(LPCTSTR pszConsole, INT nLine, CRecentDocumentInfo *pDocumentInfo) CONST
{
	return m_pwndView->GetLine(pszConsole, nLine, pDocumentInfo);
}

BOOL COutputWnd::InsertLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute)
{
	return m_pwndView->InsertLine(pszConsole, nLine, pszText, pAttribute);
}

BOOL COutputWnd::DeleteLine(LPCTSTR pszConsole, INT nLine)
{
	return m_pwndView->DeleteLine(pszConsole, nLine);
}

BOOL COutputWnd::SetCurLine(LPCTSTR pszConsole, INT nLine)
{
	return m_pwndView->SetCurLine(pszConsole, nLine);
}

INT COutputWnd::GetCurLine(LPCTSTR pszConsole) CONST
{
	return m_pwndView->GetCurLine(pszConsole);
}

INT COutputWnd::GetLineCount(LPCTSTR pszConsole) CONST
{
	return m_pwndView->GetLineCount(pszConsole);
}

VOID COutputWnd::ResetContent(LPCTSTR pszConsole)
{
	m_pwndView->ResetContent(pszConsole);
}

VOID COutputWnd::ResetAllContent()
{
	m_pwndView->ResetAllContent();
}

BOOL COutputWnd::SetContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument)
{
	return m_pwndView->SetContext(pszConsole, pDocument);
}

BOOL COutputWnd::GetContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument) CONST
{
	return m_pwndView->GetContext(pszConsole, pDocument);
}

BOOL COutputWnd::StartBlinking(LPCTSTR pszConsole, INT nLine)
{
	return m_pwndView->StartBlinking(pszConsole, nLine);
}

BOOL COutputWnd::StopBlinking(LPCTSTR pszConsole, INT nLine)
{
	return m_pwndView->StopBlinking(pszConsole, nLine);
}

VOID COutputWnd::Copy(COutputWnd *pOutputWnd)
{
	CRect  rView;

	CalcClientRect(rView);
	m_pwndView = pOutputWnd->m_pwndView;
	pOutputWnd->m_pwndView->SetParent(this);
	pOutputWnd->m_pwndView->MoveWindow(rView);
	pOutputWnd->m_pwndView = (COutputView *)NULL;
	pOutputWnd->ShowWindow(SW_HIDE);
}

void COutputWnd::PostNcDestroy()
{
	delete m_pwndView;
	CToolWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COutputWnd, CToolWnd)
	//{{AFX_MSG_MAP(COutputWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputWnd message handlers

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CToolWnd::OnCreate(lpCreateStruct) != -1)
	{
		if ((m_pwndView = (IsDocked(TRUE)) ? new COutputView : (COutputView *)NULL))
		{
			if (m_pwndView->Create(this) && m_pwndView->ModifyStyleEx(0, WS_EX_CLIENTEDGE)) return 0;
			m_pwndView->DestroyWindow();
			delete m_pwndView;
		}
		m_pwndView = (COutputView *)NULL;
		return((!IsDocked(TRUE)) ? 0 : -1);
	}
	return -1;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rView;

	if (IsWindow(m_pwndView->GetSafeHwnd()))
	{
		CalcClientRect(rView);
		m_pwndView->MoveWindow(rView);
	}
	CToolWnd::OnSize(nType, cx, cy);
}

void COutputWnd::OnPaint()
{
	if (IsWindow(m_pwndView->GetSafeHwnd())) m_pwndView->UpdateWindow();
	CToolWnd::OnPaint();
}


/////////////////////////////////////////////////////////////////////////////
// CZoomWnd

IMPLEMENT_DYNCREATE(CZoomWnd, CMiniFrameWnd)

CZoomWnd::CZoomWnd() : CMiniFrameWnd()
{
	m_rDrag.SetRectEmpty();
	m_ptDrag.x = m_ptDrag.y = 0;
	m_hPointCursor = (HCURSOR)NULL;
	m_hDragCursor = (HCURSOR)NULL;
}

BOOL CZoomWnd::Create(CWnd *pParentWnd, LPCTSTR pszTitle, DWORD dwStyle, CONST RECT &rect, UINT nID)
{
	if (CMiniFrameWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), pszTitle, (dwStyle | MFS_SYNCACTIVE | MFS_THICKFRAME | WS_POPUP | WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_DLGFRAME | WS_SYSMENU | WS_VSCROLL) & ~(MFS_4THICKFRAME | MFS_MOVEFRAME | MFS_BLOCKSYSMENU | WS_CHILD | WS_THICKFRAME | WS_VISIBLE), rect, pParentWnd, nID))
	{
		ModifyStyleEx(0, WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE);
		ShowWindow((dwStyle & WS_VISIBLE) ? SW_SHOW : SW_HIDE);
		return TRUE;
	}
	return FALSE;
}

VOID CZoomWnd::AdjustZoomFactor(CONST RECT &rect)
{
	CRect  rZoomWnd;

	GetClientRect(rZoomWnd);
	SetScrollPos(SB_VERT, (!IsRectEmpty(&rect)) ? (rZoomWnd.Width() / (rect.right - rect.left)) : 1);
}

VOID CZoomWnd::Connect()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = GetZoomedWindow()))
	{
		AdjustZoomFactor(pMMDWnd->GetHotSpot());
		RedrawWindow();
	}
}

VOID CZoomWnd::Clear()
{
	CDC  *pDC;
	CRect  rect;

	if ((pDC = GetDC()))
	{
		GetClientRect(rect);
		pDC->FillSolidRect(rect, GetSysColor(COLOR_WINDOW));
		ReleaseDC(pDC);
	}
}

CMainWnd *CZoomWnd::GetParent() CONST
{
	return((CMainWnd *)CMiniFrameWnd::GetParent());
}

VOID CZoomWnd::StartDragging(CONST POINT &point)
{
	CRect  rect;
	CRect  rDrag;

	m_ptDrag = point;
	GetClientRect(rect);
	rDrag.SetRect(point.x - (rect.right - rect.left) / (2 * GetScrollPos(SB_VERT)), point.y - (rect.bottom - rect.top) / (2 * GetScrollPos(SB_VERT)), point.x + (rect.right - rect.left) / (2 * GetScrollPos(SB_VERT)), point.y + (rect.bottom - rect.top) / (2 * GetScrollPos(SB_VERT)));
	ClientToScreen((m_rDrag = rDrag));
	DrawDraggingFrame(m_rDrag);
	SetCursor(m_hDragCursor);
	SetCapture();
}

VOID CZoomWnd::StopDragging()
{
	CMMDWnd  *pMMDWnd;

	for (DrawDraggingFrame(m_rDrag), ReleaseCapture(); (pMMDWnd = GetZoomedWindow()); )
	{
		pMMDWnd->GetImageView()->SetFocus();
		break;
	}
}

VOID CZoomWnd::DrawDraggingFrame(CONST RECT &rect)
{
	INT  nMode;
	CPen  cPen;
	CPen  *pOldPen;
	CRgn  rDragClip;
	CRect  rDragArea;
	CClientDC  cDC(NULL);

	for (GetParent()->ClientToScreen((rDragArea = GetParent()->CalcClientRect())); rDragClip.CreateRectRgn(rDragArea.left, rDragArea.top, rDragArea.right, rDragArea.bottom); )
	{
		if (cPen.CreatePen(PS_DOT, 1, GetSysColor(COLOR_WINDOWFRAME)))
		{
			if (cDC.SelectClipRgn(&rDragClip) != ERROR)
			{
				if ((pOldPen = cDC.SelectObject(&cPen)))
				{
					nMode = cDC.SetROP2(R2_NOTXORPEN);
					cDC.MoveTo(rect.left, rect.top);
					cDC.LineTo(rect.right, rect.top);
					cDC.LineTo(rect.right, rect.bottom);
					cDC.LineTo(rect.left, rect.bottom);
					cDC.LineTo(rect.left, rect.top);
					cDC.SelectObject(pOldPen);
					cDC.SetROP2(nMode);
				}
				cDC.SelectClipRgn((CRgn *)NULL);
			}
			cPen.DeleteObject();
		}
		rDragClip.DeleteObject();
		break;
	}
	DrawHotSpot(rect);
}
VOID CZoomWnd::DrawDraggingFrame(CONST POINT &point)
{
	INT  nMode;
	CPen  cPen;
	CPen  *pOldPen;
	CRgn  rDragClip;
	CRect  rDrag[2];
	CRect  rDragArea;
	CClientDC  cDC(NULL);

	if (GetCapture() == (CWnd *) this)
	{
		for (GetParent()->ClientToScreen((rDragArea = GetParent()->CalcClientRect())), rDrag[0].SetRect(m_rDrag.left, m_rDrag.top, m_rDrag.right, m_rDrag.bottom), rDrag[1].SetRect(m_rDrag.left + point.x - m_ptDrag.x, m_rDrag.top + point.y - m_ptDrag.y, m_rDrag.right + point.x - m_ptDrag.x, m_rDrag.bottom + point.y - m_ptDrag.y); rDragClip.CreateRectRgn(rDragArea.left, rDragArea.top, rDragArea.right, rDragArea.bottom); )
		{
			if (cPen.CreatePen(PS_DOT, 1, GetSysColor(COLOR_WINDOWFRAME)))
			{
				if (cDC.SelectClipRgn(&rDragClip) != ERROR)
				{
					if ((pOldPen = cDC.SelectObject(&cPen)))
					{
						nMode = cDC.SetROP2(R2_NOTXORPEN);
						cDC.MoveTo(rDrag[0].left, rDrag[0].top);
						cDC.LineTo(rDrag[0].right, rDrag[0].top);
						cDC.LineTo(rDrag[0].right, rDrag[0].bottom);
						cDC.LineTo(rDrag[0].left, rDrag[0].bottom);
						cDC.LineTo(rDrag[0].left, rDrag[0].top);
						cDC.MoveTo(rDrag[1].left, rDrag[1].top);
						cDC.LineTo(rDrag[1].right, rDrag[1].top);
						cDC.LineTo(rDrag[1].right, rDrag[1].bottom);
						cDC.LineTo(rDrag[1].left, rDrag[1].bottom);
						cDC.LineTo(rDrag[1].left, rDrag[1].top);
						cDC.SelectObject(pOldPen);
						cDC.SetROP2(nMode);
					}
					cDC.SelectClipRgn((CRgn *)NULL);
				}
				cPen.DeleteObject();
			}
			rDragClip.DeleteObject();
			break;
		}
		DrawHotSpot(rDrag[1]);
		SetCursor(m_hDragCursor);
		m_rDrag = rDrag[1];
		m_ptDrag = point;
	}
}

VOID CZoomWnd::DrawHotSpot(CONST RECT &rect)
{
	CRect  rView;
	CRect  rResult;
	CRect  rHotSpot(rect);
	CMMDImageView  *pView;
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = GetZoomedWindow()))
	{
		if ((pView = pMMDWnd->GetImageView()))
		{
			for (pView->GetWindowRect(rView); rResult.IntersectRect(rView, &rect); )
			{
				rHotSpot.OffsetRect(pView->GetScrollPos(SB_HORZ), 0);
				rHotSpot.OffsetRect(0, pView->GetScrollPos(SB_VERT));
				pView->ScreenToClient(rHotSpot);
				pView->SetHotSpot(rHotSpot);
				Invalidate(FALSE);
				UpdateWindow();
				break;
			}
		}
	}
}

CMMDWnd *CZoomWnd::GetZoomedWindow() CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD  &&  pDisplayWnd->IsWindowVisible()) break;
		continue;
	}
	return((nDisplay < nDisplays) ? (CMMDWnd *)pDisplays.GetAt(nDisplay) : (CMMDWnd *)NULL);
}

BEGIN_MESSAGE_MAP(CZoomWnd, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CZoomWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_VSCROLL()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomWnd message handlers

int CZoomWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CMMDWnd  *pMMDWnd;
	HCURSOR  hCursor[2];

	if (CMiniFrameWnd::OnCreate(lpCreateStruct) != -1)
	{
		if ((hCursor[0] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_ZOOMPOINT), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
		{
			if ((hCursor[1] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_ZOOMDRAG), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
			{
				if ((pMMDWnd = GetZoomedWindow()))
				{
					SetScrollRange(SB_VERT, 1, 10);
					AdjustZoomFactor(pMMDWnd->GetHotSpot());
					m_hPointCursor = hCursor[0];
					m_hDragCursor = hCursor[1];
					return 0;
				}
				m_hDragCursor = hCursor[1];
				m_hPointCursor = hCursor[0];
				SetScrollRange(SB_VERT, 1, 10);
				SetScrollPos(SB_VERT, 1);
				return 0;
			}
			DestroyCursor(hCursor[0]);
		}
	}
	return -1;
}

void CZoomWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rHotSpot[2];
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = GetZoomedWindow()))
	{
		rHotSpot[0] = pMMDWnd->GetHotSpot();
		rHotSpot[1].SetRect(rHotSpot[0].CenterPoint().x - cx / (2 * GetScrollPos(SB_VERT)), rHotSpot[0].CenterPoint().y - cy / (2 * GetScrollPos(SB_VERT)), rHotSpot[0].CenterPoint().x + cx / (2 * GetScrollPos(SB_VERT)), rHotSpot[0].CenterPoint().y + cy / (2 * GetScrollPos(SB_VERT)));
		rHotSpot[1].OffsetRect((rHotSpot[0].IsRectEmpty()) ? -min(rHotSpot[0].left, 0) : 0, (rHotSpot[0].IsRectEmpty()) ? -min(rHotSpot[0].top, 0) : 0);
		pMMDWnd->SetHotSpot(rHotSpot[1]);
	}
	CMiniFrameWnd::OnSize(nType, cx, cy);
}

void CZoomWnd::OnPaint()
{
	CDC  *pDC;
	CSize  size;
	CRect  rect;
	CMMDWnd  *pMMDWnd;
	CPaintDC  cDC(this);

	if ((pMMDWnd = GetZoomedWindow()))
	{
		GetClientRect(rect);
		size.cx = rect.Width();
		size.cy = rect.Height();
		pMMDWnd->DrawHotSpot(&cDC, size);
		return;
	}
	if ((pDC = GetDC()))
	{
		GetClientRect(rect);
		pDC->FillSolidRect(rect, GetSysColor(COLOR_WINDOW));
		ReleaseDC(pDC);
	}
}

void CZoomWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		ShowWindow(SW_HIDE);
		return;
	}
	CMiniFrameWnd::OnSysCommand(nID, lParam);
}

void CZoomWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	StartDragging(point);
	CMiniFrameWnd::OnLButtonDown(nFlags, point);
}

void CZoomWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	StopDragging();
	CMiniFrameWnd::OnLButtonUp(nFlags, point);
}

void CZoomWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	DrawDraggingFrame(point);
	CMiniFrameWnd::OnMouseMove(nFlags, point);
}

BOOL CZoomWnd::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest == HTCLIENT)
	{
		SetCursor(m_hPointCursor);
		return TRUE;
	}
	return CMiniFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CZoomWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	INT  nMin;
	INT  nMax;
	CRect  rect;
	CRect  rHotSpot[2];
	CMMDWnd  *pMMDWnd;

	switch (nSBCode)
	{
	case SB_TOP:
	{ GetScrollRange(SB_VERT, &nMin, &nMax);
	SetScrollPos(SB_VERT, nMin);
	break;
	}
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
	{ SetScrollPos(SB_VERT, nPos);
	break;
	}
	case SB_LINEUP:
	{ GetScrollRange(SB_VERT, &nMin, &nMax);
	SetScrollPos(SB_VERT, max(GetScrollPos(SB_VERT) - 1, nMin));
	break;
	}
	case SB_PAGEUP:
	{ GetScrollRange(SB_VERT, &nMin, &nMax);
	SetScrollPos(SB_VERT, max(GetScrollPos(SB_VERT) - (nMax - nMin) / 5, nMin));
	break;
	}
	case SB_LINEDOWN:
	{ GetScrollRange(SB_VERT, &nMin, &nMax);
	SetScrollPos(SB_VERT, min(GetScrollPos(SB_VERT) + 1, nMax));
	break;
	}
	case SB_PAGEDOWN:
	{ GetScrollRange(SB_VERT, &nMin, &nMax);
	SetScrollPos(SB_VERT, min(GetScrollPos(SB_VERT) + (nMax - nMin) / 5, nMax));
	break;
	}
	case SB_BOTTOM:
	{ GetScrollRange(SB_VERT, &nMin, &nMax);
	SetScrollPos(SB_VERT, nMax);
	break;
	}
	}
	GetClientRect(rect);
	if ((pMMDWnd = GetZoomedWindow()))
	{
		rHotSpot[0] = pMMDWnd->GetHotSpot();
		rHotSpot[1].SetRect(rHotSpot[0].CenterPoint().x - rect.Width() / (2 * GetScrollPos(SB_VERT)), rHotSpot[0].CenterPoint().y - rect.Height() / (2 * GetScrollPos(SB_VERT)), rHotSpot[0].CenterPoint().x + rect.Width() / (2 * GetScrollPos(SB_VERT)), rHotSpot[0].CenterPoint().y + rect.Height() / (2 * GetScrollPos(SB_VERT)));
		rHotSpot[1].OffsetRect((rHotSpot[0].IsRectEmpty()) ? -min(rHotSpot[0].left, 0) : 0, (rHotSpot[0].IsRectEmpty()) ? -min(rHotSpot[0].top, 0) : 0);
		pMMDWnd->SetHotSpot(rHotSpot[1]);
		Invalidate(FALSE);
		UpdateWindow();
	}
	CMiniFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CZoomWnd::OnDestroy()
{
	DestroyCursor(m_hPointCursor);
	DestroyCursor(m_hDragCursor);
	CMiniFrameWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CMainRibbonBar

IMPLEMENT_DYNCREATE(CMainRibbonBar, CMFCRibbonBar)

CMainRibbonBar::CMainRibbonBar() : CMFCRibbonBar()
{
	m_bFindDefaults[0] = TRUE;
	m_bFindDefaults[1] = TRUE;
	m_bFindDefaults[2] = FALSE;
	m_bFindDefaults[3] = FALSE;
}

VOID CMainRibbonBar::SetFindDefaults(BOOL bForward, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord, BOOL bToggle)
{
	m_bFindDefaults[0] = (bToggle) ? ((bForward) ? !m_bFindDefaults[0] : m_bFindDefaults[0]) : bForward;
	m_bFindDefaults[1] = (bToggle) ? ((bSearchAll) ? !m_bFindDefaults[1] : m_bFindDefaults[1]) : bSearchAll;
	m_bFindDefaults[2] = (bToggle) ? ((bMatchCase) ? !m_bFindDefaults[2] : m_bFindDefaults[2]) : bMatchCase;
	m_bFindDefaults[3] = (bToggle) ? ((bMatchWord) ? !m_bFindDefaults[3] : m_bFindDefaults[3]) : bMatchWord;
}

VOID CMainRibbonBar::GetFindDefaults(BOOL &bForward, BOOL &bSearchAll, BOOL &bMatchCase, BOOL &bMatchWord) CONST
{
	bForward = m_bFindDefaults[0];
	bSearchAll = m_bFindDefaults[1];
	bMatchCase = m_bFindDefaults[2];
	bMatchWord = m_bFindDefaults[3];
}

BEGIN_MESSAGE_MAP(CMainRibbonBar, CMFCRibbonBar)
	//{{AFX_MSG_MAP(CMainRibbonBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainRibbonBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainRibbonButton

IMPLEMENT_DYNCREATE(CMainRibbonButton, CMFCRibbonButton)

CMainRibbonButton::CMainRibbonButton(UINT nID, LPCTSTR pszText, HICON hIcon, HICON hSmallIcon) : CMFCRibbonButton(nID, pszText, hIcon, FALSE, hSmallIcon, FALSE, TRUE)
{
	m_hIcon[0] = hIcon;
	m_hIcon[1] = hSmallIcon;
}
CMainRibbonButton::CMainRibbonButton(UINT nID, LPCTSTR pszText, INT nSmallImageIndex, INT nLargeImageIndex, BOOL bDescription) : CMFCRibbonButton(nID, pszText, nSmallImageIndex, nLargeImageIndex, bDescription)
{
	m_hIcon[0] = m_hIcon[1] = (HICON)NULL;
}

CMainRibbonButton::~CMainRibbonButton()
{
	if (m_hIcon[0] != (HICON)NULL) DestroyIcon(m_hIcon[0]);
	if (m_hIcon[1] != (HICON)NULL) DestroyIcon(m_hIcon[1]);
}

void CMainRibbonButton::OnDraw(CDC *pDC)
{
	UINT  nID;
	CSize  size[2];

	if (((nID = GetID()) >= IDM_FIRSTMRUDOCUMENT  &&  nID <= IDM_LASTMRUDOCUMENT) || (nID >= IDM_FIRSTMRUDATABASE  &&  nID <= IDM_LASTMRUDATABASE))
	{
		for (size[0] = CMFCToolBar::GetMenuButtonSize(), size[1] = CMFCToolBar::GetMenuImageSize(); size[1].cx != 0 || size[1].cy != 0; )
		{
			CMFCToolBar::SetMenuSizes(size[0], CSize(0, 0));
			break;
		}
		CMFCRibbonButton::OnDraw(pDC);
		CMFCToolBar::SetMenuSizes(size[0], size[1]);
		return;
	}
	CMFCRibbonButton::OnDraw(pDC);
}

CSize CMainRibbonButton::GetImageSize(RibbonImageType type) const
{
	return CMFCRibbonButton::GetImageSize(RibbonImageSmall);
}

CSize CMainRibbonButton::GetIntermediateSize(CDC *pDC)
{
	CSize  size;

	size = CMFCRibbonButton::GetIntermediateSize(pDC);
	size.cx += GetSystemMetrics(SM_CXFRAME);
	return size;
}

BOOL CMainRibbonButton::HasLargeMode() const
{
	return FALSE;
}

void CMainRibbonButton::OnUpdateCmdUI(CMFCRibbonCmdUI *pCmdUI, CFrameWnd *pTarget, BOOL bDisableIfNoHndler)
{
	INT  nItem;
	INT  nItems;
	BOOL  bDisabled;
	CMFCRibbonButton  *pItem;

	for (nItem = 0, nItems = (INT)GetSubItems().GetCount(), bDisabled = TRUE; nItem < nItems; nItem++)
	{
		if ((pItem = (CMFCRibbonButton *)GetSubItems().GetAt(nItem)) && pItem->GetID() != (UINT)-1 && pItem->GetID() != 0)
		{
			for (pCmdUI->m_pUpdated = pItem, pCmdUI->m_nID = pItem->GetID(), pCmdUI->DoUpdate(pTarget, bDisableIfNoHndler); !pItem->IsDisabled(); )
			{
				bDisabled = FALSE;
				break;
			}
			pCmdUI->m_pUpdated = NULL;
		}
	}
	if (nItems > 0)
	{
		m_bIsDisabled = bDisabled;
		return;
	}
	CMFCRibbonButton::OnUpdateCmdUI(pCmdUI, pTarget, bDisableIfNoHndler);
}


/////////////////////////////////////////////////////////////////////////////
// CMainMimicsObjectsToolBar

IMPLEMENT_DYNCREATE(CMainMimicsObjectsToolBar, CMFCToolBar)

CMainMimicsObjectsToolBar::CMainMimicsObjectsToolBar() : CMFCToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CMainMimicsObjectsToolBar, CMFCToolBar)
	//{{AFX_MSG_MAP(CMainMimicsObjectsToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainMimicsObjectsToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainTCStepsToolBar

IMPLEMENT_DYNCREATE(CMainTCStepsToolBar, CMFCToolBar)

CMainTCStepsToolBar::CMainTCStepsToolBar() : CMFCToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CMainTCStepsToolBar, CMFCToolBar)
	//{{AFX_MSG_MAP(CMainTCStepsToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainTCStepsToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CMainWnd

IMPLEMENT_DYNCREATE(CMainWnd, CLocaleMDIFrameWnd)

CMainWnd::CMainWnd() : CLocaleMDIFrameWnd()
{
	m_pZoomWnd = (CZoomWnd *)NULL;
	m_pDisplayFrame = new CDisplayFrame;
	m_pCriticalSection = new CCriticalSection;
	m_nRecentPrintJobs = 0;
}

CMainWnd::~CMainWnd()
{
	delete m_pDisplayFrame;
	delete m_pCriticalSection;
}

BOOL CMainWnd::LoadFrame(UINT nResourceID, DWORD dwDefaultStyle)
{
	if (CLocaleMDIFrameWnd::LoadFrame(nResourceID, dwDefaultStyle))
	{
		ShowBarMessage(IDS_STATUSBAR_INITIALIZING);
		ShowWindow(SW_SHOWNORMAL);
		UpdateWindow();
		UpdateMenus();
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWnd::PreCreateWindow(CREATESTRUCT &cs)
{
	CSize  size;
	CRect  rPosition;
	APPBARDATA  sBarData = { sizeof(sBarData) };

	SHAppBarMessage(ABM_GETTASKBARPOS, &sBarData);
	size.cx = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	size.cy = GetSystemMetrics(SM_CYVIRTUALSCREEN) - (sBarData.rc.bottom - sBarData.rc.top);
	rPosition.SetRect(0, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + 1) : 0, size.cx, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + size.cy) : size.cy);
	cs.x = rPosition.left;
	cs.y = rPosition.top;
	cs.cx = rPosition.Width();
	cs.cy = rPosition.Height();
	return CLocaleMDIFrameWnd::PreCreateWindow(cs);
}

VOID CMainWnd::SaveEnvironment()
{
	ShowBarMessage(IDS_STATUSBAR_SAVING);
	SaveDisplayWindows();
	SaveMRULists();
}

VOID CMainWnd::LoadEnvironment()
{
	ShowBarMessage(IDS_STATUSBAR_LOADING);
	ArrangeToolWindows();
	LoadProfiles();
	LoadMRULists();
	LoadDisplayWindows();
	CreateZoomWindow();
	StartAssistant();
	ShowBarMessage(IDS_STATUSBAR_READY);
}

BOOL CMainWnd::SelectDatabase(BOOL bReset)
{
	BOOL  bSuccess;

	if (!bReset)
	{
		ShowBarMessage(IDS_STATUSBAR_LOADINGDATABASE);
		bSuccess = GetDatabase()->Load();
	}
	else
	{
		CloseAllWindows();
		GetDatabase()->Reset();
		bSuccess = TRUE;
	}
	UpdateTitle();
	UpdateWorkspaceWindow();
	UpdateOutputWindow();
	UpdateStatusBar();
	return bSuccess;
}

VOID CMainWnd::UpdateDatabase(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pDatabaseTMPacket, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pDatabaseTMPacket, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pDatabaseTCFunction, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pDatabaseTCFunction, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseProcedures(pDatabaseTCSequence, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pDatabaseTCSequence, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseProcedures(pDatabaseTCProcedure, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pDatabaseTCProcedure, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pDatabaseOBProcessor, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pDatabaseOBProcessor, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pDatabaseTMParameter, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pDatabaseTMParameter, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pDatabaseTCParameter, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pDatabaseTCParameter, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseProcedures(pTCSequenceWnd, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pTCSequenceWnd, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pANDWnd, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pANDWnd, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pGRDWnd, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pGRDWnd, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pMMDWnd, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pMMDWnd, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pPODWnd, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pPODWnd, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents(pScriptWnd, nPosition, bDelete);
		pWorkspaceWnd->UpdateDatabaseLogs(pScriptWnd, nPosition, bDelete);
	}
}
VOID CMainWnd::UpdateDatabase(ULONGLONG nComponent, LPCTSTR pszName)
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseLogs(nComponent, pszName);
	}
}
VOID CMainWnd::UpdateDatabase()
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents();
		pWorkspaceWnd->UpdateDatabaseProcedures();
		pWorkspaceWnd->UpdateDatabaseLogs();
	}
}

VOID CMainWnd::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMPacketWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMPacket, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMPacketWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMPacketIdentification, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMPacketWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMPacketIdentificationCriterion, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMPacketWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMPacketHeader, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMPacketWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMPacketStream, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMPacketWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMPacketGroup, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCFunction, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCPacket, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCPacketParameter, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCPreExeGroup, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCExeVerStage, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCExeVerGroup, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCParameterSet, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCParameterValueSet, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCFunctionWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCFunctionRoutingPath, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCSequenceWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCSequence, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCSequenceWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCFunctionBlock, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCSequenceWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCParameterSet, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCSequenceWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCParameterValueSet, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pOBProcessorWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseOBProcessor, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pOBProcessorWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseOBProcessorMemoryImage, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMParameter, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMNumCalTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMTxtCalTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMNumOolTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMTxtOolTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTMParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTMParameterGroup, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCParameter, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCNumCalTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCTxtCalTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCNumOolTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pTCParameterWnd)
		{
			pDisplayWnd->UpdateTables(pDatabaseTCTxtOolTable, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CANDWnd *pANDWnd, CONST CANDLayout *pLayout, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pANDWnd)
		{
			pDisplayWnd->UpdateTables(pLayout, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CGRDWnd *pGRDWnd, CONST CGRDLayout *pLayout, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pGRDWnd)
		{
			pDisplayWnd->UpdateTables(pLayout, bDelete);
			continue;
		}
	}
}
VOID CMainWnd::UpdateForms(CONST CPODWnd *pPODWnd, CONST CPODLayout *pLayout, BOOL bDelete)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd != (CDisplayWnd *)pPODWnd)
		{
			pDisplayWnd->UpdateTables(pLayout, bDelete);
			continue;
		}
	}
}

VOID CMainWnd::SaveToolWindows()
{
	INT  nTool;
	INT  nTools;
	UINT  nState;
	CRect  rToolWnd;
	CRect  rZoomWnd;
	CRect  rToolBar[2];
	CToolWnd  *pToolWnd;
	CZoomWnd  *pZoomWnd;
	CByteArray  nToolInfo;
	CProfile  cProfile;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!IsIconic())
	{
		for (nTool = 0, nTools = (cProfile.SetWorkspaceWindowInfo(0, (LPCRECT)NULL, CByteArray()) && cProfile.SetOutputWindowInfo(0, (LPCRECT)NULL, CByteArray())) ? (INT)m_pwndTools.GetSize() : 0; nTool < nTools; nTool++)
		{
			if ((pToolWnd = (CToolWnd *)m_pwndTools.GetAt(nTool)))
			{
				pToolWnd->GetData(nToolInfo);
				pToolWnd->GetWindowRect(rToolWnd);
				if (pToolWnd == GetWorkspaceWindow())
				{
					cProfile.SetWorkspaceWindowInfo(pToolWnd->GetDockState(TRUE), rToolWnd, nToolInfo);
					continue;
				}
				if (pToolWnd == GetOutputWindow())
				{
					cProfile.SetOutputWindowInfo(pToolWnd->GetDockState(TRUE), rToolWnd, nToolInfo);
					continue;
				}
			}
		}
		for (cProfile.SetMimicsObjectsToolBarInfo(); IsWindow(m_wndMimicsObjectsToolBar.GetSafeHwnd()); )
		{
			m_wndMimicsObjectsToolBar.GetParentMiniFrame(TRUE)->GetWindowRect(rToolBar[0]);
			cProfile.SetMimicsObjectsToolBarInfo(rToolBar[0], m_wndMimicsObjectsToolBar.IsVisible());
			break;
		}
		for (cProfile.SetTCStepsToolBarInfo(); IsWindow(m_wndTCStepsToolBar.GetSafeHwnd()); )
		{
			m_wndTCStepsToolBar.GetParentMiniFrame(TRUE)->GetWindowRect(rToolBar[1]);
			cProfile.SetTCStepsToolBarInfo(rToolBar[1], m_wndTCStepsToolBar.IsVisible());
			break;
		}
		if ((pZoomWnd = GetZoomWindow()))
		{
			nState = pZoomWnd->GetStyle();
			pZoomWnd->GetWindowRect(rZoomWnd);
			cProfile.SetZoomWindowInfo(nState, rZoomWnd);
			m_pZoomWnd = (CZoomWnd *)NULL;
			return;
		}
		cProfile.SetZoomWindowInfo(-1, (LPCRECT)NULL);
	}
}

VOID CMainWnd::ArrangeToolWindows()
{
	INT  dx;
	INT  dy;
	INT  nPane;
	INT  nPanes;
	CRect  rArea;
	CRect  rPane[4];
	CRect  *prToolPanes;
	CPtrArray  *pToolWnds;
	CUIntArray  nToolPanes[2];

	for (rArea = CalcClientRect(FALSE), ClientToScreen(rArea), rPane[0].SetRectEmpty(), rPane[1].SetRectEmpty(), rPane[2].SetRectEmpty(), rPane[3].SetRectEmpty(); (nPanes = GetToolPaneCount(TOOLWINDOW_DOCKSTATE_TOP)) > 0; )
	{
		if ((pToolWnds = new CPtrArray[nPanes]))
		{
			if ((prToolPanes = new CRect[nPanes]))
			{
				for (nPane = 0, nToolPanes[0].RemoveAll(), nToolPanes[1].RemoveAll(); nPane < nPanes; nPane++)
				{
					EnumToolPane(TOOLWINDOW_DOCKSTATE_TOP, nPane, prToolPanes[nPane], dx, dy, pToolWnds[nPane]);
					nToolPanes[0].InsertAt(nPane, dx);
					nToolPanes[1].InsertAt(nPane, dy);
				}
				for (nPane = 0; nPane < nPanes; nPane++)
				{
					rPane[1] = prToolPanes[nPane];
					rPane[0].SetRect(0, (!nPane) ? (rArea.top - rPane[1].top) : (rPane[0].top + rPane[0].bottom - rPane[1].top), 0, rPane[1].bottom);
					rPane[1].SetRect(rArea.left, rPane[1].top + rPane[0].top, rArea.right, rPane[1].bottom + rPane[0].top);
					rPane[2].SetRect(rPane[1].left, (!nPane) ? rPane[1].top : rPane[2].top, rPane[1].right, rPane[1].bottom);
					RecalcToolPane(TOOLWINDOW_DOCKSTATE_TOP, rPane[1], nToolPanes[0][nPane], nToolPanes[1][nPane], pToolWnds[nPane]);
				}
				delete[] prToolPanes;
			}
			delete[] pToolWnds;
		}
		break;
	}
	if ((nPanes = GetToolPaneCount(TOOLWINDOW_DOCKSTATE_BOTTOM)) > 0)
	{
		if ((pToolWnds = new CPtrArray[nPanes]))
		{
			if ((prToolPanes = new CRect[nPanes]))
			{
				for (nPane = 0, nToolPanes[0].RemoveAll(), nToolPanes[1].RemoveAll(); nPane < nPanes; nPane++)
				{
					EnumToolPane(TOOLWINDOW_DOCKSTATE_BOTTOM, nPane, prToolPanes[nPane], dx, dy, pToolWnds[nPane]);
					nToolPanes[0].InsertAt(nPane, dx);
					nToolPanes[1].InsertAt(nPane, dy);
				}
				for (nPane = 0; nPane < nPanes; nPane++)
				{
					rPane[1] = prToolPanes[nPane];
					rPane[0].SetRect(0, rPane[1].top, 0, (!nPane) ? (rArea.bottom - rPane[1].bottom) : (rPane[0].bottom + rPane[0].top - rPane[1].bottom));
					rPane[1].SetRect(rArea.left, rPane[1].top + rPane[0].bottom, rArea.right, rPane[1].bottom + rPane[0].bottom);
					rPane[3].SetRect(rPane[1].left, rPane[1].top, rPane[1].right, (!nPane) ? rPane[1].bottom : rPane[3].bottom);
					RecalcToolPane(TOOLWINDOW_DOCKSTATE_BOTTOM, rPane[1], nToolPanes[0][nPane], nToolPanes[1][nPane], pToolWnds[nPane]);
				}
				delete[] prToolPanes;
			}
			delete[] pToolWnds;
		}
	}
	if ((nPanes = GetToolPaneCount(TOOLWINDOW_DOCKSTATE_LEFT)) > 0)
	{
		if ((pToolWnds = new CPtrArray[nPanes]))
		{
			if ((prToolPanes = new CRect[nPanes]))
			{
				for (nPane = 0, nToolPanes[0].RemoveAll(), nToolPanes[1].RemoveAll(); nPane < nPanes; nPane++)
				{
					EnumToolPane(TOOLWINDOW_DOCKSTATE_LEFT, nPane, prToolPanes[nPane], dx, dy, pToolWnds[nPane]);
					nToolPanes[0].InsertAt(nPane, dx);
					nToolPanes[1].InsertAt(nPane, dy);
				}
				for (nPane = 0; nPane < nPanes; nPane++)
				{
					rPane[1] = prToolPanes[nPane];
					rPane[0].SetRect((!nPane) ? (rArea.left - rPane[1].left) : (rPane[0].left + rPane[0].right - rPane[1].left), 0, rPane[1].right, 0);
					rPane[1].SetRect(rPane[1].left + rPane[0].left, rArea.top + rPane[2].Height(), rPane[1].right + rPane[0].left, rArea.bottom - rPane[3].Height());
					RecalcToolPane(TOOLWINDOW_DOCKSTATE_LEFT, rPane[1], nToolPanes[0][nPane], nToolPanes[1][nPane], pToolWnds[nPane]);
				}
				delete[] prToolPanes;
			}
			delete[] pToolWnds;
		}
	}
	if ((nPanes = GetToolPaneCount(TOOLWINDOW_DOCKSTATE_RIGHT)) > 0)
	{
		if ((pToolWnds = new CPtrArray[nPanes]))
		{
			if ((prToolPanes = new CRect[nPanes]))
			{
				for (nPane = 0, nToolPanes[0].RemoveAll(), nToolPanes[1].RemoveAll(); nPane < nPanes; nPane++)
				{
					EnumToolPane(TOOLWINDOW_DOCKSTATE_RIGHT, nPane, prToolPanes[nPane], dx, dy, pToolWnds[nPane]);
					nToolPanes[0].InsertAt(nPane, dx);
					nToolPanes[1].InsertAt(nPane, dy);
				}
				for (nPane = 0; nPane < nPanes; nPane++)
				{
					rPane[1] = prToolPanes[nPane];
					rPane[0].SetRect(rPane[1].left, 0, (!nPane) ? (rArea.right - rPane[1].right) : (rPane[0].right + rPane[0].left - rPane[1].right), 0);
					rPane[1].SetRect(rPane[1].left + rPane[0].right, rArea.top + rPane[2].Height(), rPane[1].right + rPane[0].right, rArea.bottom - rPane[3].Height());
					RecalcToolPane(TOOLWINDOW_DOCKSTATE_RIGHT, rPane[1], nToolPanes[0][nPane], nToolPanes[1][nPane], pToolWnds[nPane]);
				}
				delete[] prToolPanes;
			}
			delete[] pToolWnds;
		}
	}
	GetDisplayFrame()->MoveWindow(CalcClientRect());
}
VOID CMainWnd::ArrangeToolWindows(CToolWnd *pToolWnd, LPCRECT pRect)
{
	CRect  rPane;
	CRect  rToolWnd;
	CPtrArray  pToolWnds;

	for (pToolWnd->GetWindowRect(rToolWnd); EnumToolPane(pToolWnd->GetDockState(), FindToolPane(pToolWnd->GetDockState(), rToolWnd), rPane, pToolWnds); )
	{
		RecalcToolPane(pToolWnd->GetDockState(), CRect((pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT) ? pRect->left : rPane.left, (pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM) ? pRect->top : rPane.top, (pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) ? pRect->right : rPane.right, (pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) ? pRect->bottom : rPane.bottom), pToolWnd, pRect, pToolWnds);
		ArrangeToolWindows();
		break;
	}
}

VOID CMainWnd::DeleteToolWindows()
{
	CProfile  cProfile;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	cProfile.SetWorkspaceWindowInfo(0, (LPCRECT)NULL, CByteArray());
	cProfile.SetOutputWindowInfo(0, (LPCRECT)NULL, CByteArray());
	cProfile.SetZoomWindowInfo(-1, (LPCRECT)NULL);
}

INT CMainWnd::EnumToolWindows(UINT nSide) CONST
{
	CPtrArray  pwndTools;

	return EnumToolWindows(nSide, pwndTools);
}
INT CMainWnd::EnumToolWindows(UINT nSide, CPtrArray &pwndTools) CONST
{
	INT  nTool;
	INT  nTools;
	CToolWnd  *pToolWnd;

	for (nTool = 0, nTools = (INT)m_pwndTools.GetSize(), pwndTools.RemoveAll(); nTool < nTools; nTool++)
	{
		if ((pToolWnd = (CToolWnd *)m_pwndTools.GetAt(nTool)) != (CToolWnd *)NULL)
		{
			if (!(pToolWnd->GetDockState(TRUE) & TOOLWINDOW_DOCKSTATE_HIDDEN))
			{
				if ((pToolWnd->GetDockState() & nSide) == nSide || nSide == (UINT)-1)
				{
					pwndTools.Add(pToolWnd);
					continue;
				}
			}
		}
	}
	return((INT)pwndTools.GetSize());
}
INT CMainWnd::EnumToolWindows(CToolWnd *pToolWnd) CONST
{
	CPtrArray  pwndTools;

	return EnumToolWindows(pToolWnd, pwndTools);
}
INT CMainWnd::EnumToolWindows(CToolWnd *pToolWnd, CPtrArray &pwndTools) CONST
{
	INT  nTool;
	INT  nTools;
	UINT  nSide;
	CRect  rWnd[2];
	CToolWnd  *pWnd;
	CPtrArray  pToolWnds;

	for (nTool = 0, nTools = EnumToolWindows((nSide = pToolWnd->GetDockState()), pToolWnds), pToolWnd->GetWindowRect(rWnd[0]), pwndTools.RemoveAll(); nTool < nTools; nTool++)
	{
		if ((pWnd = (CToolWnd *)pToolWnds.GetAt(nTool)))
		{
			if ((pWnd->GetDockState() & nSide) == nSide)
			{
				pWnd->GetWindowRect(rWnd[1]);
				if ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT))
				{
					if (rWnd[0].left == rWnd[1].left  &&  rWnd[0].right == rWnd[1].right)
					{
						pwndTools.Add(pWnd);
						continue;
					}
				}
				if ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM))
				{
					if (rWnd[0].top == rWnd[1].top  &&  rWnd[0].bottom == rWnd[1].bottom)
					{
						pwndTools.Add(pWnd);
						continue;
					}
				}
			}
		}
	}
	return((INT)pwndTools.GetSize());
}
INT CMainWnd::EnumToolWindows(CToolWnd *pToolWnd, LPCRECT pRect, BOOL bAll)
{
	CPtrArray  pwndTools;

	return EnumToolWindows(pToolWnd, pToolWnd->GetDockState(), pRect, bAll, pwndTools);
}
INT CMainWnd::EnumToolWindows(CToolWnd *pToolWnd, UINT nSide, LPCRECT pRect, BOOL bAll)
{
	CPtrArray  pwndTools;

	return EnumToolWindows(pToolWnd, nSide, pRect, bAll, pwndTools);
}
INT CMainWnd::EnumToolWindows(CToolWnd *pToolWnd, LPCRECT pRect, BOOL bAll, CPtrArray &pwndTools)
{
	return EnumToolWindows(pToolWnd, pToolWnd->GetDockState(), pRect, bAll, pwndTools);
}
INT CMainWnd::EnumToolWindows(CToolWnd *pToolWnd, UINT nSide, LPCRECT pRect, BOOL bAll, CPtrArray &pwndTools)
{
	INT  nTool;
	INT  nTools;
	CRect  rWnd;
	CRect  rArea;
	CToolWnd  *pWnd;
	CPtrArray  pToolWnds;

	for (ClientToScreen((rArea = CalcClientRect())), pwndTools.RemoveAll(); ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) && pRect->right - rArea.left < (pRect->right - pRect->left) / 2) || ((nSide & TOOLWINDOW_DOCKSTATE_TOP) && pRect->bottom - rArea.top < (pRect->bottom - pRect->top) / 2) || ((nSide & TOOLWINDOW_DOCKSTATE_RIGHT) && rArea.right - pRect->left < (pRect->right - pRect->left) / 2) || ((nSide & TOOLWINDOW_DOCKSTATE_BOTTOM) && rArea.bottom - pRect->top < (pRect->bottom - pRect->top) / 2); )
	{
		for (nTool = 0, nTools = EnumToolWindows(nSide, pToolWnds); nTool < nTools; nTool++)
		{
			if ((pWnd = (CToolWnd *)pToolWnds.GetAt(nTool)) && (bAll || pWnd != pToolWnd))
			{
				for (pWnd->GetWindowRect(rWnd); (pWnd->GetDockState() & nSide) == nSide; )
				{
					if ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT))
					{
						if (((nSide & TOOLWINDOW_DOCKSTATE_LEFT) && rWnd.left + rWnd.Width() / 2 <= (pRect->right + pRect->left) / 2 && rWnd.right >= (pRect->right + pRect->left) / 2) || ((nSide & TOOLWINDOW_DOCKSTATE_RIGHT) && rWnd.left <= (pRect->right + pRect->left) / 2 && rWnd.right - rWnd.Width() / 2 >= (pRect->right + pRect->left) / 2))
						{
							pwndTools.Add(pWnd);
							break;
						}
					}
					if ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM))
					{
						if (((nSide & TOOLWINDOW_DOCKSTATE_TOP) && rWnd.top + rWnd.Height() / 2 <= (pRect->bottom + pRect->top) / 2 && rWnd.bottom >= (pRect->bottom + pRect->top) / 2) || ((nSide & TOOLWINDOW_DOCKSTATE_BOTTOM) && rWnd.top <= (pRect->bottom + pRect->top) / 2 && rWnd.bottom - rWnd.Height() / 2 >= (pRect->bottom + pRect->top) / 2))
						{
							pwndTools.Add(pWnd);
							break;
						}
					}
					break;
				}
			}
		}
		return((INT)pwndTools.GetSize());
	}
	return 0;
}

VOID CMainWnd::RegisterToolWindow(CToolWnd *pToolWnd)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pwndTools.Add(pToolWnd);
}

VOID CMainWnd::UnregisterToolWindow(CToolWnd *pToolWnd)
{
	INT  nTool;
	INT  nTools;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nTool = 0, nTools = (INT)m_pwndTools.GetSize(); nTool < nTools; nTool++)
	{
		if (m_pwndTools.GetAt(nTool) == (LPVOID)pToolWnd)
		{
			m_pwndTools.RemoveAt(nTool);
			break;
		}
	}
}

BOOL CMainWnd::RepositionToolWindow(CToolWnd *pToolWnd, LPCRECT pRect)
{
	CString  szTitle;
	COutputWnd  *pOutputWnd;
	CWorkspaceWnd  *pWorkspaceWnd;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (pToolWnd->GetDockState())
	{
		if (!pToolWnd->IsDocked())
		{
			pToolWnd->GetWindowText(szTitle);
			if (pToolWnd == GetWorkspaceWindow())
			{
				if ((pWorkspaceWnd = new CWorkspaceWnd(GetWorkspaceWindow())))
				{
					if (pWorkspaceWnd->Create(this, szTitle, TWS_DOCKED | WS_CLIPCHILDREN | WS_VISIBLE, CRect(0, 0, 0, 0)))
					{
						pWorkspaceWnd->Copy(GetWorkspaceWindow());
						DockToolWindow(pWorkspaceWnd, pRect);
						DestroyToolWindow(pToolWnd);
						return TRUE;
					}
					delete pWorkspaceWnd;
				}
			}
			if (pToolWnd == GetOutputWindow())
			{
				if ((pOutputWnd = new COutputWnd(GetOutputWindow())))
				{
					if (pOutputWnd->Create(this, szTitle, TWS_DOCKED | WS_CLIPCHILDREN | WS_VISIBLE, CRect(0, 0, 0, 0)))
					{
						pOutputWnd->Copy(GetOutputWindow());
						DockToolWindow(pOutputWnd, pRect);
						DestroyToolWindow(pToolWnd);
						return TRUE;
					}
					delete pOutputWnd;
				}
			}
			return FALSE;
		}
		DockToolWindow(pToolWnd, pRect);
		return FALSE;
	}
	if (pToolWnd->IsDocked())
	{
		pToolWnd->GetWindowText(szTitle);
		if (pToolWnd == GetWorkspaceWindow())
		{
			if ((pWorkspaceWnd = new CWorkspaceWnd(GetWorkspaceWindow())))
			{
				if (pWorkspaceWnd->Create(this, szTitle, TWS_FLOATING | WS_CLIPCHILDREN | WS_VISIBLE, CRect(pRect->left, pRect->top, pRect->right, pRect->bottom)))
				{
					pWorkspaceWnd->Copy(GetWorkspaceWindow());
					ArrangeToolWindows();
					DestroyToolWindow(pToolWnd);
					return TRUE;
				}
			}
		}
		if (pToolWnd == GetOutputWindow())
		{
			if ((pOutputWnd = new COutputWnd(GetOutputWindow())))
			{
				if (pOutputWnd->Create(this, szTitle, TWS_FLOATING | WS_CLIPCHILDREN | WS_VISIBLE, CRect(pRect->left, pRect->top, pRect->right, pRect->bottom)))
				{
					pOutputWnd->Copy(GetOutputWindow());
					ArrangeToolWindows();
					DestroyToolWindow(pToolWnd);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

VOID CMainWnd::DockToolWindow(CToolWnd *pToolWnd, LPCRECT pRect)
{
	INT  nPane;
	UINT  nSide;
	CRect  rPane;
	CRect  rArea[2];
	CRect  rToolWnd;
	CPtrArray  pToolWnds;

	if (pToolWnd->IsDocked())
	{
		if ((nSide = pToolWnd->GetDockState()))
		{
			if (GetToolPaneCount(nSide))
			{
				pToolWnd->SetDockState();
				if (EnumToolWindows(pToolWnd, nSide, pRect))
				{
					if (EnumToolPane(nSide, (nPane = FindToolPane(nSide, pRect)), rPane, pToolWnds))
					{
						for (rToolWnd.SetRect(((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? rPane.left : min(pRect->left, rPane.right - pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cx), ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? rPane.top : min(pRect->top, rPane.bottom - pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cy), ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? rPane.right : (min(pRect->left, rPane.right - pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cx) + pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cx), ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? rPane.bottom : (min(pRect->top, rPane.bottom - pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cy) + pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cy)), pToolWnd->SetDockState(nSide), pToolWnd->SetDockRect(rToolWnd); EnumToolPane(nSide, nPane, rPane, pToolWnds); )
						{
							RecalcToolPane(nSide, rPane, pToolWnd, rToolWnd, pToolWnds);
							break;
						}
					}
				}
				else
				{
					rToolWnd.SetRect(pRect->left, pRect->top, ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (pRect->left + pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cx) : pRect->right, ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (pRect->top + pToolWnd->GetDefaultSize(TOOLWINDOW_SIZE_DOCKED).cy) : pRect->bottom);
					pToolWnd->SetDockRect(rToolWnd);
				}
			}
			else
			{
				rArea[0] = CalcClientRect(TRUE);
				rArea[1] = CalcClientRect(FALSE);
				rToolWnd.SetRect((nSide & TOOLWINDOW_DOCKSTATE_RIGHT) ? (rArea[1].right - pToolWnd->GetDefaultSize().cx) : rArea[1].left, (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM) ? (rArea[0].bottom - pToolWnd->GetDefaultSize().cy) : rArea[0].top, (nSide & TOOLWINDOW_DOCKSTATE_LEFT) ? (rArea[1].left + pToolWnd->GetDefaultSize().cx) : rArea[1].right, (nSide & TOOLWINDOW_DOCKSTATE_TOP) ? (rArea[0].top + pToolWnd->GetDefaultSize().cy) : rArea[0].bottom);
				pToolWnd->SetDockRect(rToolWnd);
			}
			pToolWnd->SetDockState(nSide);
			ArrangeToolWindows();
		}
		pToolWnd->SetDockRect();
	}
}

INT CMainWnd::FindToolWindow(CToolWnd *pToolWnd) CONST
{
	INT  nTool;
	INT  nTools;

	for (nTool = 0, nTools = (INT)m_pwndTools.GetSize(); nTool < nTools; nTool++)
	{
		if (m_pwndTools.GetAt(nTool) == (LPVOID)pToolWnd) break;
		continue;
	}
	return((nTool < nTools) ? nTool : -1);
}
CToolWnd *CMainWnd::FindToolWindow(LPCTSTR pszTitle) CONST
{
	INT  nTool;
	INT  nTools;
	CString  szTitle;
	CToolWnd  *pToolWnd;

	for (nTool = 0, nTools = (INT)m_pwndTools.GetSize(); nTool < nTools; nTool++)
	{
		if ((pToolWnd = (CToolWnd *)m_pwndTools.GetAt(nTool)))
		{
			if (pToolWnd->GetTitle() == pszTitle) break;
			continue;
		}
	}
	return((nTool < nTools) ? (CToolWnd *)m_pwndTools.GetAt(nTool) : (CToolWnd *)NULL);
}

VOID CMainWnd::DestroyToolWindow(CToolWnd *pToolWnd)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	UnregisterToolWindow(pToolWnd);
	pToolWnd->DestroyWindow();
}

INT CMainWnd::FindToolPane(UINT nSide, LPCRECT pRect) CONST
{
	INT  nPane;
	INT  nPanes;
	CUIntArray  nPanesPos;

	for (nPane = 0, nPanes = GetToolPaneCount(nSide, nPanesPos); nPane < nPanes; nPane++)
	{
		if (((nSide & TOOLWINDOW_DOCKSTATE_LEFT) && (pRect->left + pRect->right) / 2 < (INT)nPanesPos.GetAt(nPane)) || ((nSide & TOOLWINDOW_DOCKSTATE_TOP) && (pRect->top + pRect->bottom) / 2 < (INT)nPanesPos.GetAt(nPane)) || ((nSide & TOOLWINDOW_DOCKSTATE_RIGHT) && (pRect->left + pRect->right) / 2 > (INT)nPanesPos.GetAt(nPane)) || ((nSide & TOOLWINDOW_DOCKSTATE_BOTTOM) && (pRect->top + pRect->bottom) / 2 > (INT)nPanesPos.GetAt(nPane))) break;
		continue;
	}
	return nPane - 1;
}

INT CMainWnd::EnumToolPane(UINT nSide, INT nPane, CPtrArray &pwndTools) CONST
{
	INT  nPos;
	INT  nTool;
	INT  nTools;
	CRect  rToolWnd;
	CToolWnd  *pToolWnd;
	CUIntArray  nPanesPos;

	for (nTool = 0, nTools = (GetToolPaneCount(nSide, nPanesPos) > nPane) ? (INT)m_pwndTools.GetSize() : 0, pwndTools.RemoveAll(); nTool < nTools; nTool++)
	{
		if ((pToolWnd = (CToolWnd *)m_pwndTools.GetAt(nTool)))
		{
			if (!(pToolWnd->GetDockState(TRUE) & TOOLWINDOW_DOCKSTATE_HIDDEN))
			{
				if ((pToolWnd->GetDockState() & nSide) == nSide)
				{
					pToolWnd->GetDockRect(rToolWnd);
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_LEFT) ? rToolWnd.left : 0;
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_TOP) ? rToolWnd.top : nPos;
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_RIGHT) ? rToolWnd.right : nPos;
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM) ? rToolWnd.bottom : nPos;
					if (nPos == (INT)nPanesPos.GetAt(nPane)) pwndTools.Add(pToolWnd);
				}
			}
		}
	}
	return((INT)pwndTools.GetSize());
}
INT CMainWnd::EnumToolPane(UINT nSide, INT nPane, LPRECT pRect, CPtrArray &pwndTools) CONST
{
	INT  dx;
	INT  dy;

	return EnumToolPane(nSide, nPane, pRect, dx, dy, pwndTools);
}
INT CMainWnd::EnumToolPane(UINT nSide, INT nPane, LPRECT pRect, INT &dx, INT &dy, CPtrArray &pwndTools) CONST
{
	INT  nTool[2];
	INT  nTools[2];
	CRect  rToolWnd[2];
	CToolWnd  *pToolWnd[2];
	CPtrArray  pToolWnds;

	for (nTool[0] = 0, nTools[0] = EnumToolPane(nSide, nPane, pToolWnds), SetRectEmpty(pRect), dx = dy = 0, pwndTools.RemoveAll(); nTool[0] < nTools[0]; nTool[0]++)
	{
		if ((pToolWnd[0] = (CToolWnd *)pToolWnds.GetAt(nTool[0])))
		{
			pToolWnd[0]->GetDockRect(rToolWnd[0]);
			pRect->left = (nTool[0]) ? min(rToolWnd[0].left, pRect->left) : rToolWnd[0].left;
			pRect->top = (nTool[0]) ? min(rToolWnd[0].top, pRect->top) : rToolWnd[0].top;
			pRect->right = (nTool[0]) ? max(rToolWnd[0].right, pRect->right) : rToolWnd[0].right;
			pRect->bottom = (nTool[0]) ? max(rToolWnd[0].bottom, pRect->bottom) : rToolWnd[0].bottom;
			dx = ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (dx + rToolWnd[0].Width()) : rToolWnd[0].Width();
			dy = ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (dy + rToolWnd[0].Height()) : rToolWnd[0].Height();
			for (nTool[1] = 0, nTools[1] = (INT)pwndTools.GetSize(); nTool[1] < nTools[1]; nTool[1]++)
			{
				if ((pToolWnd[1] = (CToolWnd *)pwndTools.GetAt(nTool[1])))
				{
					pToolWnd[1]->GetDockRect(rToolWnd[1]);
					if (((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) && rToolWnd[0].top < rToolWnd[1].top) break;
					if (((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) && rToolWnd[0].left < rToolWnd[1].left) break;
				}
			}
			pwndTools.InsertAt(nTool[1], pToolWnd[0], 1);
		}
	}
	return((INT)pwndTools.GetSize());
}

VOID CMainWnd::RecalcToolPane(UINT nSide, LPCRECT prPane, CToolWnd *pWnd, LPCRECT prWnd, CONST CPtrArray &pwndTools)
{
	INT  cx;
	INT  cy;
	INT  dx[2];
	INT  dy[2];
	INT  nTool;
	INT  nTools;
	HDWP  hToolWnds;
	CRect  rToolPane;
	CRect  rToolWnd[3];
	CToolWnd  *pToolWnd;
	CPtrArray  pToolWnds;

	for (nTool = 0, nTools = (INT)pwndTools.GetSize(), pToolWnds.Copy(pwndTools); nTool < nTools; nTool++)
	{
		if ((pToolWnd = (CToolWnd *)pwndTools.GetAt(nTool)) == pWnd)
		{
			pToolWnds.RemoveAt(nTool);
			break;
		}
	}
	for (nTool = 0, nTools = (INT)pToolWnds.GetSize(), dx[0] = dy[0] = 0; !nTool || nTool < nTools; nTool++)
	{
		if ((pToolWnd = (nTools) ? (CToolWnd *)pToolWnds.GetAt(nTool) : (CToolWnd *)NULL))
		{
			pToolWnd->GetDockRect(rToolWnd[0]);
			if ((((pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && (prWnd->left + prWnd->right) / 2 < (rToolWnd[0].left + rToolWnd[0].right) / 2) || (((pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (pToolWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && (prWnd->top + prWnd->bottom) / 2 < (rToolWnd[0].top + rToolWnd[0].bottom) / 2))
			{
				pToolWnds.InsertAt(nTool, pWnd, 1);
				break;
			}
			dx[0] = (((pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && nTool > 0) ? (dx[0] + rToolWnd[0].Width()) : rToolWnd[0].Width();
			dy[0] = (((pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && nTool > 0) ? (dy[0] + rToolWnd[0].Height()) : rToolWnd[0].Height();
			if (nTool == nTools - 1)
			{
				pToolWnds.Add(pWnd);
				break;
			}
			continue;
		}
		pToolWnds.Add(pWnd);
		break;
	}
	for (nTool = 0, nTools = (INT)pToolWnds.GetSize(), dx[1] = dy[1] = 0; nTool < nTools; nTool++)
	{
		if ((pToolWnd = (CToolWnd *)pToolWnds.GetAt(nTool)))
		{
			pToolWnd->GetDockRect(rToolWnd[0]);
			rToolWnd[0].SetRect((pToolWnd == pWnd) ? prWnd->left : rToolWnd[0].left, (pToolWnd == pWnd) ? prWnd->top : rToolWnd[0].top, (pToolWnd == pWnd) ? prWnd->right : rToolWnd[0].right, (pToolWnd == pWnd) ? prWnd->bottom : rToolWnd[0].bottom);
			dx[1] = (((pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_TOP) || (pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_BOTTOM)) && nTool > 0) ? (dx[1] + rToolWnd[0].Width()) : rToolWnd[0].Width();
			dy[1] = (((pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_LEFT) || (pWnd->GetDockState() & TOOLWINDOW_DOCKSTATE_RIGHT)) && nTool > 0) ? (dy[1] + rToolWnd[0].Height()) : rToolWnd[0].Height();
		}
	}
	if ((hToolWnds = BeginDeferWindowPos((INT)pToolWnds.GetSize())))
	{
		for (nTool = 0, nTools = (INT)pToolWnds.GetSize(), rToolPane.SetRect(prPane->left, prPane->top, prPane->right, prPane->bottom), ScreenToClient(rToolPane), rToolWnd[0].SetRect(rToolPane.left, rToolPane.top, rToolPane.left, rToolPane.bottom), rToolWnd[1].SetRect(prWnd->left, prWnd->top, prWnd->right, prWnd->bottom); nTool < nTools; nTool++)
		{
			if ((pToolWnd = (CToolWnd *)pToolWnds.GetAt(nTool)))
			{
				pToolWnd->GetDockRect(rToolWnd[2]);
				pToolWnd->Invalidate(FALSE);
				DeferWindowPos(hToolWnds, pToolWnd->GetSafeHwnd(), (HWND)NULL, rToolWnd[0].left, rToolWnd[0].top, (cx = ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? ((dx[1] - prPane->right + prPane->left >= prWnd->right - prWnd->left) ? ((nTool < nTools - 1) ? ((pToolWnd != pWnd) ? max(rToolWnd[2].Width() - (rToolWnd[2].Width()*(prWnd->right - prWnd->left)) / rToolPane.Width(), pToolWnd->CalcExtent().cx) : max(prWnd->right - prWnd->left, pToolWnd->CalcExtent().cx)) : (rToolPane.right - rToolWnd[0].left)) : (((nTool < nTools - 1 && pToolWnds.GetAt(nTool + 1) == (LPVOID)pWnd) || pToolWnd == pWnd) ? ((pToolWnd == pWnd) ? max(rToolWnd[2].right - rToolWnd[1].left, pToolWnd->CalcExtent().cx) : max(rToolWnd[1].left - rToolWnd[2].left, pToolWnd->CalcExtent().cx)) : rToolWnd[2].Width())) : rToolPane.Width()), (cy = ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((dy[1] - prPane->bottom + prPane->top >= prWnd->bottom - prWnd->top) ? ((nTool < nTools - 1) ? ((pToolWnd != pWnd) ? max(rToolWnd[2].Height() - (rToolWnd[2].Height()*(prWnd->bottom - prWnd->top)) / rToolPane.Height(), pToolWnd->CalcExtent().cy) : max(prWnd->bottom - prWnd->top, pToolWnd->CalcExtent().cy)) : (rToolPane.bottom - rToolWnd[0].top)) : (((nTool < nTools - 1 && pToolWnds.GetAt(nTool + 1) == (LPVOID)pWnd) || pToolWnd == pWnd) ? ((pToolWnd == pWnd) ? max(rToolWnd[2].bottom - rToolWnd[1].top, pToolWnd->CalcExtent().cy) : max(rToolWnd[1].top - rToolWnd[2].top, pToolWnd->CalcExtent().cy)) : rToolWnd[2].Height())) : rToolPane.Height()), SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);
				rToolWnd[0].SetRect(((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd[0].left + cx) : rToolWnd[0].left, ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd[0].top + cy) : rToolWnd[0].top, ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd[0].left + cx) : rToolWnd[0].right, ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd[0].top + cy) : rToolWnd[0].bottom);
			}
		}
		EndDeferWindowPos(hToolWnds);
	}
}
VOID CMainWnd::RecalcToolPane(UINT nSide, LPCRECT prPane, INT dx, INT dy, CONST CPtrArray &pwndTools)
{
	INT  cx;
	INT  cy;
	INT  nTool;
	INT  nTools;
	HDWP  hToolWnds;
	CRect  rToolPane;
	CRect  rToolWnd[2];
	CToolWnd  *pToolWnd;

	if ((hToolWnds = BeginDeferWindowPos((INT)pwndTools.GetSize())))
	{
		for (nTool = 0, nTools = (INT)pwndTools.GetSize(), rToolPane.SetRect(prPane->left, prPane->top, prPane->right, prPane->bottom), ScreenToClient(rToolPane), rToolWnd[0].SetRect(rToolPane.left, rToolPane.top, rToolPane.left, rToolPane.bottom); nTool < nTools; nTool++)
		{
			if ((pToolWnd = (CToolWnd *)pwndTools.GetAt(nTool)))
			{
				pToolWnd->GetDockRect(rToolWnd[1]);
				pToolWnd->Invalidate(FALSE);
				DeferWindowPos(hToolWnds, pToolWnd->GetSafeHwnd(), (HWND)NULL, rToolWnd[0].left, rToolWnd[0].top, cx = max(((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? ((nTool < nTools - 1) ? (rToolWnd[1].Width() + (rToolWnd[1].Width()*(rToolPane.Width() - dx)) / dx) : (rToolPane.right - rToolWnd[0].left)) : rToolPane.Width(), pToolWnd->CalcExtent().cx), cy = max(((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? ((nTool < nTools - 1) ? (rToolWnd[1].Height() + (rToolWnd[1].Height()*(rToolPane.Height() - dy)) / dy) : (rToolPane.bottom - rToolWnd[0].top)) : rToolPane.Height(), pToolWnd->CalcExtent().cy), SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER);
				rToolWnd[0].SetRect(((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd[0].left + cx) : rToolWnd[0].left, ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd[0].top + cy) : rToolWnd[0].top, ((nSide & TOOLWINDOW_DOCKSTATE_TOP) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (rToolWnd[0].left + cx) : rToolWnd[0].right, ((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_RIGHT)) ? (rToolWnd[0].top + cy) : rToolWnd[0].bottom);
			}
		}
		EndDeferWindowPos(hToolWnds);
	}
}

INT CMainWnd::GetToolPaneCount(UINT nSide, CUIntArray &nPanesPos) CONST
{
	INT  nPos;
	INT  nPane;
	INT  nTool;
	INT  nPanes;
	INT  nTools;
	CRect  rToolWnd;
	CToolWnd  *pToolWnd;

	for (nTool = 0, nTools = (INT)m_pwndTools.GetSize(), nPanesPos.RemoveAll(); nTool < nTools; nTool++)
	{
		if ((pToolWnd = (CToolWnd *)m_pwndTools.GetAt(nTool)) != (CToolWnd *)NULL)
		{
			if (!(pToolWnd->GetDockState(TRUE) & TOOLWINDOW_DOCKSTATE_HIDDEN))
			{
				if ((pToolWnd->GetDockState() & nSide) == nSide)
				{
					pToolWnd->GetDockRect(rToolWnd);
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_LEFT) ? rToolWnd.left : 0;
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_TOP) ? rToolWnd.top : nPos;
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_RIGHT) ? rToolWnd.right : nPos;
					nPos = (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM) ? rToolWnd.bottom : nPos;
					for (nPane = 0, nPanes = (INT)nPanesPos.GetSize(); nPane < nPanes; nPane++)
					{
						if (nPos == (INT)nPanesPos.GetAt(nPane)) break;
						continue;
					}
					if (!nPanes)
					{
						nPanesPos.Add(nPos);
						continue;
					}
					for (nPane = (nPane < nPanes) ? nPanes : 0; nPane < nPanes; nPane++)
					{
						if ((((nSide & TOOLWINDOW_DOCKSTATE_LEFT) || (nSide & TOOLWINDOW_DOCKSTATE_TOP)) && nPos < (INT)nPanesPos.GetAt(nPane)) || (((nSide & TOOLWINDOW_DOCKSTATE_RIGHT) || (nSide & TOOLWINDOW_DOCKSTATE_BOTTOM)) && nPos >(INT) nPanesPos.GetAt(nPane)))
						{
							nPanesPos.InsertAt(nPane, nPos);
							break;
						}
						if (nPane == nPanes - 1)
						{
							nPanesPos.Add(nPos);
							break;
						}
					}
				}
			}
		}
	}
	return((INT)nPanesPos.GetSize());
}
INT CMainWnd::GetToolPaneCount(UINT nSide) CONST
{
	CUIntArray  nPanesPos;

	return GetToolPaneCount(nSide, nPanesPos);
}

VOID CMainWnd::SaveDisplayWindows()
{
	INT  nDisplay;
	INT  nDisplays;
	INT  nDisplayCount;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CComputerToken  cComputerToken;
	CProfile  cProfile;

	if (GetDatabase()->IsLocal())
	{
		for (nDisplay = 0, nDisplays = ((nDisplayCount = (cProfile.GetDisplayWindowCount(nDisplayCount)) ? nDisplayCount : 0) >= 0) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)))
			{
				if (!pDisplayWnd->Save(nDisplay))
				{
					pDisplays.RemoveAt(nDisplay);
					nDisplays--;
					nDisplay--;
				}
			}
		}
		for (cProfile.SetDisplayWindowCount(nDisplays); nDisplay < nDisplayCount; nDisplay++)
		{
			cProfile.DeleteDisplayWindowInfo(nDisplay);
			continue;
		}
	}
}

VOID CMainWnd::LoadDisplayWindows()
{
	INT  nDisplay;
	INT  nDisplays;
	UINT  nDisplayType;
	CANDWnd  *pANDWnd;
	CGRDWnd  *pGRDWnd;
	CMMDWnd  *pMMDWnd;
	CPODWnd  *pPODWnd;
	CZoomWnd  *pZoomWnd;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;
	CTCFunctionWnd  *pTCFunctionWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CTMParameterWnd  *pTMParameterWnd;
	CTCParameterWnd  *pTCParameterWnd;
	CTCProcedureWnd  *pTCProcedureWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CProfile  cProfile;

	if (GetDatabase()->IsLocal())
	{
		for (nDisplay = nDisplays = (cProfile.GetDisplayWindowCount(nDisplays)) ? nDisplays : 0, GetDisplayFrame()->Hide(); nDisplay > 0; nDisplay--)
		{
			if (cProfile.GetDisplayWindowType(nDisplay - 1, nDisplayType))
			{
				if (nDisplayType == DISPLAY_TYPE_TMPACKET)
				{
					if ((pTMPacketWnd = new CTMPacketWnd))
					{
						for (; pTMPacketWnd->Load(nDisplay - 1) < 0; )
						{
							delete pTMPacketWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_TCFUNCTION)
				{
					if ((pTCFunctionWnd = new CTCFunctionWnd))
					{
						for (; pTCFunctionWnd->Load(nDisplay - 1) < 0; )
						{
							delete pTCFunctionWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_TCSEQUENCE)
				{
					if ((pTCSequenceWnd = new CTCSequenceWnd))
					{
						for (; pTCSequenceWnd->Load(nDisplay - 1) < 0; )
						{
							delete pTCSequenceWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_TCPROCEDURE)
				{
					if ((pTCProcedureWnd = new CTCProcedureWnd))
					{
						for (; pTCProcedureWnd->Load(nDisplay - 1) < 0; )
						{
							delete pTCProcedureWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_TMPARAMETER)
				{
					if ((pTMParameterWnd = new CTMParameterWnd))
					{
						for (; pTMParameterWnd->Load(nDisplay - 1) < 0; )
						{
							delete pTMParameterWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_TCPARAMETER)
				{
					if ((pTCParameterWnd = new CTCParameterWnd))
					{
						for (; pTCParameterWnd->Load(nDisplay - 1) < 0; )
						{
							delete pTCParameterWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_OBPROCESSOR)
				{
					if ((pOBProcessorWnd = new COBProcessorWnd))
					{
						for (; pOBProcessorWnd->Load(nDisplay - 1) < 0; )
						{
							delete pOBProcessorWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_AND)
				{
					if ((pANDWnd = new CANDWnd) != (CANDWnd *)NULL)
					{
						for (; pANDWnd->Load(nDisplay - 1) < 0; )
						{
							delete pANDWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_GRD)
				{
					if ((pGRDWnd = new CGRDWnd) != (CGRDWnd *)NULL)
					{
						for (; pGRDWnd->Load(nDisplay - 1) < 0; )
						{
							delete pANDWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_MMD)
				{
					if ((pMMDWnd = new CMMDWnd) != (CMMDWnd *)NULL)
					{
						for (; pMMDWnd->Load(nDisplay - 1) < 0; )
						{
							delete pGRDWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_POD)
				{
					if ((pPODWnd = new CPODWnd) != (CPODWnd *)NULL)
					{
						for (; pPODWnd->Load(nDisplay - 1) < 0; )
						{
							delete pPODWnd;
							break;
						}
					}
				}
				if (nDisplayType == DISPLAY_TYPE_SCRIPT)
				{
					if ((pScriptWnd = new CScriptWnd))
					{
						for (; pScriptWnd->Load(nDisplay - 1) < 0; )
						{
							delete pScriptWnd;
							break;
						}
					}
				}
			}
		}
		for (GetDisplayFrame()->Show(); (pDisplayWnd = (CDisplayWnd *)MDIGetActive()); )
		{
			pDisplayWnd->SetFocus();
			break;
		}
	}
	if ((pZoomWnd = GetMainWnd()->GetZoomWindow())) pZoomWnd->Connect();
}

INT CMainWnd::EnumDisplayWindows() CONST
{
	CPtrArray  pDisplays;

	return EnumDisplayWindows(pDisplays);
}
INT CMainWnd::EnumDisplayWindows(CPtrArray &pDisplays) CONST
{
	return((EnumChildWindows(GetSafeHwnd(), EnumDisplayWindows, (LPARAM)&pDisplays)) ? (INT)pDisplays.GetSize() : 0);
}

VOID CMainWnd::ActivateDisplayWindow(CWnd *pWnd)
{
	MDIActivate(pWnd);
}

CDisplayWnd *CMainWnd::GetActiveDisplayWindow() CONST
{
	return((CDisplayWnd *)MDIGetActive());
}

VOID CMainWnd::DoSelectAll()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoSelectAll();
	}
}

BOOL CMainWnd::CanSelectAll() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanSelectAll() : FALSE);
}

VOID CMainWnd::DoUndo()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoUndo();
	}
}

BOOL CMainWnd::CanUndo() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanUndo() : FALSE);
}

VOID CMainWnd::DoRedo()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoRedo();
	}
}

BOOL CMainWnd::CanRedo() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanRedo() : FALSE);
}

VOID CMainWnd::DoCutSel()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoCutSel();
	}
}

BOOL CMainWnd::CanCutSel() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanCutSel() : FALSE);
}

VOID CMainWnd::DoCopySel()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoCopySel();
	}
}

BOOL CMainWnd::CanCopySel() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanCopySel() : FALSE);
}

VOID CMainWnd::DoPasteSel()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoPasteSel();
	}
}

BOOL CMainWnd::CanPasteSel() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanPasteSel() : FALSE);
}

VOID CMainWnd::DoDeleteSel()
{
	CDisplayWnd  *pDisplayWnd;
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()) && pWorkspaceWnd->CanDeleteSel())
	{
		pWorkspaceWnd->DoDeleteSel();
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoDeleteSel();
		return;
	}
}

BOOL CMainWnd::CanDeleteSel() CONST
{
	CDisplayWnd  *pDisplayWnd;
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()) && pWorkspaceWnd->CanDeleteSel()) return TRUE;
	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanDeleteSel() : FALSE);
}

VOID CMainWnd::DoFind()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET || pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION || pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER || pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER || pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR || (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD)))
		{
			m_dlgDatabaseFind.DoModal();
			return;
		}
		if ((pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE)) || pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE || (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_MMD || (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT)
		{
			pDisplayWnd->DoFind();
			return;
		}
	}
}
VOID CMainWnd::DoFind(LPCTSTR pszQuery)
{
	m_dlgDatabaseFind.DoModal(pszQuery);
}

BOOL CMainWnd::CanFind() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET || pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION || pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER || pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER || pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR || (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD)) || (((pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE)) || pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE || (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_MMD || (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT) && pDisplayWnd->CanFind())) : FALSE);
}

VOID CMainWnd::DoFindNext()
{
	BOOL  bFindDefaults[4];
	CDisplayWnd  *pDisplayWnd;

	for (m_wndRibbonBar.GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]); (pDisplayWnd = (CDisplayWnd *)MDIGetActive()); )
	{
		pDisplayWnd->DoFindNext(bFindDefaults[2], bFindDefaults[3]);
		break;
	}
}

BOOL CMainWnd::CanFindNext() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (((pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE)) || pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE || (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_MMD || (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT) && pDisplayWnd->CanFindNext()) : FALSE);
}

VOID CMainWnd::DoFindPrevious()
{
	BOOL  bFindDefaults[4];
	CDisplayWnd  *pDisplayWnd;

	for (m_wndRibbonBar.GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]); (pDisplayWnd = (CDisplayWnd *)MDIGetActive()); )
	{
		pDisplayWnd->DoFindPrevious(bFindDefaults[2], bFindDefaults[3]);
		break;
	}
}

BOOL CMainWnd::CanFindPrevious() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (((pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE)) || pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE || (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND)) || (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_MMD || (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  !GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD)) || pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT) && pDisplayWnd->CanFindPrevious()) : FALSE);
}

VOID CMainWnd::DoReplace()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoReplace();
		return;
	}
}

BOOL CMainWnd::CanReplace() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanReplace() : FALSE);
}

VOID CMainWnd::DoGoTo()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoGoTo();
	}
}

BOOL CMainWnd::CanGoTo() CONST
{
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? pDisplayWnd->CanGoTo() : FALSE);
}

VOID CMainWnd::ActivateWindow(BOOL bNext)
{
	CPtrArray  pDisplays;

	if (bNext)
	{
		MDINext();
		return;
	}
	if (EnumDisplayWindows(pDisplays) > 0)
	{
		MDIActivate((CWnd *)pDisplays.GetAt(pDisplays.GetUpperBound()));
		return;
	}
}

VOID CMainWnd::CloseWindow()
{
	CMDIChildWnd  *pWindow;

	if ((pWindow = MDIGetActive()))
	{
		pWindow->DestroyWindow();
	}
}

VOID CMainWnd::CloseAllWindows()
{
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CZoomWnd  *pZoomWnd;

	for (EnumDisplayWindows(pDisplays), GetDisplayFrame()->Hide(); pDisplays.GetSize() > 0; pDisplays.RemoveAt(0))
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(0)))
		{
			pDisplayWnd->DestroyWindow();
			continue;
		}
	}
	if ((pZoomWnd = GetZoomWindow())) pZoomWnd->Clear();
	GetDisplayFrame()->Show();
}

BOOL CMainWnd::ShowMessage(LPCTSTR pszMessage, BOOL bAudition)
{
	return ShowConsoleText(STRING(IDS_OUTPUTWINDOW_MESSAGETAB), pszMessage, TRUE, bAudition);
}
BOOL CMainWnd::ShowMessage(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition)
{
	CEventObject  *pEvent;

	if ((pEvent = (sEvent.Opcode != 0) ? new CEventObject(sEvent) : (CEventObject *)NULL))
	{
		if (ShowMessage(pEvent->GetMessage(), bAudition))
		{
			delete pEvent;
			return TRUE;
		}
		delete pEvent;
	}
	return((!sEvent.Opcode) ? TRUE : FALSE);
}

BOOL CMainWnd::ResetMessages()
{
	return ResetConsoleContent(STRING(IDS_OUTPUTWINDOW_MESSAGETAB));
}

BOOL CMainWnd::SetConsoleContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument)
{
	COutputWnd  *pOutputWnd;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pOutputWnd = (IsWindowVisible()) ? GetOutputWindow() : (COutputWnd *)NULL)) ? pOutputWnd->SetContext(pszConsole, pDocument) : FALSE);
}

BOOL CMainWnd::GetConsoleContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument) CONST
{
	COutputWnd  *pOutputWnd;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pOutputWnd = (IsWindowVisible()) ? GetOutputWindow() : (COutputWnd *)NULL)) ? pOutputWnd->GetContext(pszConsole, pDocument) : FALSE);
}

BOOL CMainWnd::ShowConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, BOOL bTimestamp, BOOL bAudition)
{
	CString  szTimeKey;
	CTimeKey  tTimeKey;
	COutputWnd  *pOutputWnd;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pOutputWnd = (IsWindowVisible()) ? GetOutputWindow() : (COutputWnd *)NULL))
	{
		for (pOutputWnd->SetConsole(pszConsole), pOutputWnd->InsertLine(pszConsole, -1, (lstrlen(pszText) > 0) ? ((bTimestamp) ? (LPCTSTR)((szTimeKey = tTimeKey.Format() + CString(SPACE) + SPACE) + pszText) : pszText) : EMPTYSTRING), pOutputWnd->SetCurLine(pszConsole, pOutputWnd->GetLineCount(pszConsole) - 1), pOutputWnd->Show(); bAudition; )
		{
			CAudioDevice::AlertBySound();
			break;
		}
		return TRUE;
	}
	MessageBox(pszText, GetAppTitle(), MB_ICONERROR);
	return FALSE;
}

BOOL CMainWnd::ReadConsoleText(LPCTSTR pszConsole, CStringArray &szText, BOOL bTimestamp, BOOL bAll) CONST
{
	INT  nLine;
	INT  nLines;
	CString  szLine;
	CString  szName;
	CString  szTitle;
	CString  szTimeKey;
	CTimeKey  tTimeKey;
	ULONGLONG  nComponent;
	COutputWnd  *pOutputWnd;
	CRecentDocumentInfo  cDocumentInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pOutputWnd = (IsWindowVisible()) ? GetOutputWindow() : (COutputWnd *)NULL))
	{
		for (nLine = 0, nLines = pOutputWnd->GetLineCount(pszConsole), szText.RemoveAll(), szTimeKey = (!bTimestamp) ? (tTimeKey.Format() + CString(SPACE) + SPACE) : EMPTYSTRING; nLine < nLines; nLine++)
		{
			for (szLine = pOutputWnd->GetLine(pszConsole, nLine, &cDocumentInfo).Mid(szTimeKey.GetLength()); (!bAll && cDocumentInfo.GetDocument(szName, szTitle, nComponent) && LOWORD(nComponent) != DISPLAY_TYPE_MMD && LOWORD(nComponent) != DISPLAY_TYPE_SCRIPT) || bAll; )
			{
				szText.Add(pOutputWnd->GetLine(pszConsole, nLine, &cDocumentInfo).Mid(szTimeKey.GetLength()));
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}

INT CMainWnd::AlertConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, COLORREF nColor, BOOL bTimestamp)
{
	INT  nLine;
	CString  szTimeKey;
	CTimeKey  tTimeKey;
	COutputWnd  *pOutputWnd;
	CTextViewAttribute  cAttribute;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pOutputWnd = (IsWindowVisible()) ? GetOutputWindow() : (COutputWnd *)NULL))
	{
		cAttribute.SetColumnColor(-1, nColor);
		pOutputWnd->SetConsole(pszConsole);
		pOutputWnd->InsertLine(pszConsole, -1, (lstrlen(pszText) > 0) ? ((bTimestamp) ? (LPCTSTR)((szTimeKey = tTimeKey.Format() + CString(SPACE) + SPACE) + pszText) : pszText) : EMPTYSTRING, &cAttribute);
		pOutputWnd->SetCurLine(pszConsole, (nLine = pOutputWnd->GetLineCount(pszConsole) - 1));
		pOutputWnd->StartBlinking(pszConsole, nLine);
		pOutputWnd->Show();
		return nLine;
	}
	return -1;
}

BOOL CMainWnd::AcknowledgeConsoleText(LPCTSTR pszConsole, INT nLine)
{
	CString  szTimeKey;
	CTimeKey  tTimeKey;
	COutputWnd  *pOutputWnd;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pOutputWnd = (IsWindowVisible()) ? GetOutputWindow() : (COutputWnd *)NULL))
	{
		pOutputWnd->StopBlinking(pszConsole, nLine);
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWnd::ResetConsoleContent(LPCTSTR pszConsole)
{
	COutputWnd  *pOutputWnd;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pOutputWnd = GetOutputWindow()))
	{
		pOutputWnd->SetConsole(pszConsole);
		pOutputWnd->ResetContent(pszConsole);
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWnd::ResetAllConsoles()
{
	COutputWnd  *pOutputWnd;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pOutputWnd = GetOutputWindow()))
	{
		pOutputWnd->ResetAllContent();
		return TRUE;
	}
	return FALSE;
}

VOID CMainWnd::SetFindDefaults(BOOL bForward, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord, BOOL bToggle)
{
	m_wndRibbonBar.SetFindDefaults(bForward, bSearchAll, bMatchCase, bMatchWord, bToggle);
}

VOID CMainWnd::GetFindDefaults(BOOL &bForward, BOOL &bSearchAll, BOOL &bMatchCase, BOOL &bMatchWord) CONST
{
	m_wndRibbonBar.GetFindDefaults(bForward, bSearchAll, bMatchCase, bMatchWord);
}

void CMainWnd::GetMessageString(UINT nID, CString &szMessage) CONST
{
	if (nID >= AFX_IDM_FIRST_MDICHILD)
	{
		szMessage = STRING(IDS_WINDOW_ACTIVATE);
		return;
	}
	CLocaleMDIFrameWnd::GetMessageString(nID, szMessage);
}

VOID CMainWnd::UpdateBars()
{
	UpdateBars((CDisplayWnd *)NULL, FALSE);
}
VOID CMainWnd::UpdateBars(CDisplayWnd *pDisplayWnd, BOOL bActivate)
{
	if (GetDisplayFrame()->IsWindowVisible() && bActivate)
	{
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET || pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION || pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE || pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER || pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER || pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR || pDisplayWnd->GetType() == DISPLAY_TYPE_AND || pDisplayWnd->GetType() == DISPLAY_TYPE_GRD || pDisplayWnd->GetType() == DISPLAY_TYPE_POD)
		{
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_DATABASE, TRUE);
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_MIMICS, FALSE);
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_TELECOMMANDS, FALSE);
			m_wndRibbonBar.RecalcLayout();
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_MMD)
		{
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_DATABASE, FALSE);
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_MIMICS, TRUE);
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_TELECOMMANDS, FALSE);
			m_wndRibbonBar.RecalcLayout();
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE)
		{
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_DATABASE, FALSE);
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_MIMICS, FALSE);
			m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_TELECOMMANDS, TRUE);
			m_wndRibbonBar.RecalcLayout();
			return;
		}
		return;
	}
	m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_DATABASE, FALSE);
	m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_MIMICS, FALSE);
	m_wndRibbonBar.ShowContextCategories(ID_CONTEXTCATEGORY_TELECOMMANDS, FALSE);
	m_wndRibbonBar.RecalcLayout();
}

VOID CMainWnd::UpdateMenus()
{
	INT  nID;
	INT  nIDs;
	INT  nPos;
	BITMAP  sBitmap;
	CBitmap  cBitmap;
	CString  szItem;
	CImageList  cImages;
	CMFCRibbonButton  *pButton[2];
	CMFCRibbonSeparator  *pSeparator;

	if ((pButton[0] = (CMFCRibbonButton *)m_wndRibbonBar.FindByID(IDM_OPEN)))
	{
		for (nID = 0, nIDs = (!pButton[0]->GetSubItems().GetSize()) ? (LASTOPENFORMMENUID - FIRSTOPENMENUID) : -1; nID <= nIDs; nID++)
		{
			if ((pButton[1] = new CMainRibbonButton(FIRSTOPENMENUID + nID, CString(STRING(FIRSTDISPLAYMENUITEMSTRINGID + nID)) + STRING(IDS_WINDOW_ELLIPSESMENUITEM), FIRSTOPENMENUIMAGEOFFSET + nID)))
			{
				pButton[0]->AddSubItem(pButton[1]);
				continue;
			}
			break;
		}
	}
	if ((pButton[0] = (CMFCRibbonButton *)m_wndRibbonBar.FindByID(IDM_IMPORT)))
	{
		for (nID = 0, nIDs = (!pButton[0]->GetSubItems().GetSize()) ? (LASTIMPORTFORMMENUID - FIRSTIMPORTMENUID) : -1; nID <= nIDs; nID++)
		{
			if ((pButton[1] = new CMainRibbonButton(FIRSTIMPORTMENUID + nID, CString(STRING(FIRSTDISPLAYMENUITEMSTRINGID + nID)) + STRING(IDS_WINDOW_ELLIPSESMENUITEM), FIRSTIMPORTMENUIMAGEOFFSET + nID)))
			{
				pButton[0]->AddSubItem(pButton[1]);
				continue;
			}
			break;
		}
	}
	if ((pButton[0] = (CMFCRibbonButton *)m_wndRibbonBar.FindByID(IDM_EXPORT)))
	{
		for (nID = 0, nIDs = (!pButton[0]->GetSubItems().GetSize()) ? (LASTEXPORTFORMMENUID - FIRSTEXPORTMENUID) : -1; nID <= nIDs; nID++)
		{
			if ((pButton[1] = new CMainRibbonButton(FIRSTEXPORTMENUID + nID, CString(STRING(FIRSTDISPLAYMENUITEMSTRINGID + nID)) + STRING(IDS_WINDOW_ELLIPSESMENUITEM), FIRSTEXPORTMENUIMAGEOFFSET + nID)))
			{
				pButton[0]->AddSubItem(pButton[1]);
				continue;
			}
			break;
		}
	}
	if ((pButton[0] = (CMFCRibbonButton *)m_wndRibbonBar.FindByID(IDM_MIMICSOBJECTS, FALSE)))
	{
		if (cBitmap.LoadBitmap(IDB_MIMICSOBJECTSMENUTEMPLATE) && cBitmap.GetBitmap(&sBitmap) > 0)
		{
			if (cImages.Create(sBitmap.bmHeight, sBitmap.bmHeight, ILC_COLOR32, sBitmap.bmWidth / sBitmap.bmHeight, 1) && cImages.Add(&cBitmap, RGB(0, 0, 0)) >= 0)
			{
				for (nID = 0, nIDs = (!pButton[0]->GetSubItems().GetSize()) ? (IDM_LASTMIMICSOBJECT - IDM_FIRSTMIMICSOBJECT) : -1; nID <= nIDs; nID++)
				{
					for (szItem.LoadString(IDM_FIRSTMIMICSOBJECT + nID); (nPos = szItem.Find(EOL)) >= 0; )
					{
						szItem = szItem.Mid(nPos + 1);
						break;
					}
					if ((pButton[1] = (nPos >= 0) ? new CMainRibbonButton(IDM_FIRSTMIMICSOBJECT + nID, szItem, cImages.ExtractIcon(nID), cImages.ExtractIcon(nID)) : (CMFCRibbonButton *)NULL))
					{
						pButton[0]->AddSubItem(pButton[1]);
						continue;
					}
				}
				if ((pSeparator = (nID > nIDs) ? new CMFCRibbonSeparator(TRUE) : (CMFCRibbonSeparator *)NULL))
				{
					for (pButton[0]->AddSubItem(pSeparator), szItem.LoadString(IDM_MIMICSGROUP), szItem = ((nPos = szItem.Find(EOL)) >= 0) ? szItem.Mid(nPos + 1) : szItem; (pButton[1] = new CMainRibbonButton(IDM_MIMICSGROUP, szItem, cImages.ExtractIcon(nID), cImages.ExtractIcon(nID))); )
					{
						pButton[0]->AddSubItem(pButton[1]);
						break;
					}
				}
				cImages.DeleteImageList();
			}
		}
		cBitmap.DeleteObject();
	}
	if ((pButton[0] = (CMFCRibbonButton *)m_wndRibbonBar.FindByID(IDM_TCSTEPS, FALSE)))
	{
		if (cBitmap.LoadBitmap(IDB_TCSTEPSMENUTEMPLATE) && cBitmap.GetBitmap(&sBitmap) > 0)
		{
			if (cImages.Create(sBitmap.bmHeight, sBitmap.bmHeight, ILC_COLOR32, sBitmap.bmWidth / sBitmap.bmHeight, 1) && cImages.Add(&cBitmap, RGB(0, 0, 0)) >= 0)
			{
				for (nID = 0, nIDs = (!pButton[0]->GetSubItems().GetSize()) ? (IDM_LASTTCSTEP - IDM_FIRSTTCSTEP) : -1; nID <= nIDs; nID = nID + 1)
				{
					for (; (pSeparator = (nID == IDM_FIRSTTCACTIONOBJECTSTEP - IDM_FIRSTTCSTEP) ? new CMFCRibbonSeparator(TRUE) : (CMFCRibbonSeparator *)NULL); )
					{
						pButton[0]->AddSubItem(pSeparator);
						break;
					}
					for (szItem.LoadString(IDM_FIRSTTCSTEP + nID); (nPos = szItem.Find(EOL)) >= 0; )
					{
						szItem = szItem.Mid(nPos + 1);
						break;
					}
					if ((pButton[1] = (nPos >= 0) ? new CMainRibbonButton(IDM_FIRSTTCSTEP + nID, szItem, cImages.ExtractIcon(nID), cImages.ExtractIcon(nID)) : (CMFCRibbonButton *)NULL))
					{
						pButton[0]->AddSubItem(pButton[1]);
						continue;
					}
				}
				cImages.DeleteImageList();
			}
		}
		cBitmap.DeleteObject();
	}
}
VOID CMainWnd::UpdateMenus(CDisplayWnd *pDisplayWnd)
{
	INT  nID;
	INT  nItem;
	INT  nItems;
	INT  nElement;
	INT  nElements;
	CString  szItem[2];
	CPtrArray  pDisplays;
	CMFCRibbonButton  *pButton[2];
	CMFCRibbonSeparator  *pSeparator;
	CMFCRibbonBaseElement  *pElement[3];

	if ((pButton[0] = (CMFCRibbonButton *)(pElement[0] = m_wndRibbonBar.FindByID(IDM_WINDOWS))))
	{
		for (nElement = 0, nElements = (INT)pButton[0]->GetSubItems().GetCount(); nElement < nElements; nElements--)
		{
			if ((pElement[1] = pButton[0]->GetSubItems().GetAt(nElements - 1)) && pElement[1]->GetID() != IDM_CLOSEALLWINDOWS)
			{
				if (!pButton[0]->RemoveSubItem(nElements - 1)) break;
				continue;
			}
			break;
		}
		if ((pSeparator = new CMFCRibbonSeparator(TRUE)))
		{
			for (pButton[0]->AddSubItem(pSeparator), nID = IDM_FIRSTDISPLAYWINDOW; ; )
			{
				for (nItem = 1, nItems = EnumDisplayWindows(pDisplays), nItems = min(IDM_LASTDISPLAYWINDOWS - IDM_FIRSTDISPLAYWINDOWS + 1, nItems); nItem <= nItems; nItem++)
				{
					if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nItem - 1)) != (CDisplayWnd *)NULL)
					{
						for (pDisplayWnd->GetWindowText(szItem[0]), szItem[1].Format((nItem < 10) ? STRING(IDS_WINDOW_MENUITEM) : STRING(IDS_WINDOW_EXTENDEDMENUITEM), nItem, (LPCTSTR)szItem[0]); (pButton[1] = new CMainRibbonButton(nID, szItem[1])); )
						{
							pButton[0]->AddSubItem(pButton[1]);
							nID++;
							break;
						}
					}
				}
				if ((pButton[1] = (nItems > 0) ? new CMainRibbonButton(IDM_DISPLAYWINDOWS, STRING(IDS_WINDOW_MOREMENUITEM)) : (CMFCRibbonButton *)NULL)) pButton[0]->AddSubItem(pButton[1]);
				break;
			}
		}
	}
}

VOID CMainWnd::UpdateLayout()
{
	UINT  nShow;
	CSize  size;
	CRect  rPosition;
	CUIntArray  nPaneIDs;
	APPBARDATA  sBarData;
	CProfile  cProfile;

	for (GetEditorApp()->LoadState(GetAccountUserName() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + STRING(IDS_REG_SUBKEYPART_WORKSPACE), &m_Impl); cProfile.GetState(nShow) && cProfile.GetPosition(rPosition); )
	{
		for (sBarData.cbSize = sizeof(sBarData), SHAppBarMessage(ABM_GETTASKBARPOS, &sBarData), size.cx = GetSystemMetrics(SM_CXVIRTUALSCREEN), size.cy = GetSystemMetrics(SM_CYVIRTUALSCREEN) - (sBarData.rc.bottom - sBarData.rc.top); rPosition.left < 0 || rPosition.top < 0 || (rPosition.top >= sBarData.rc.top && rPosition.top <= sBarData.rc.bottom) || rPosition.right > GetSystemMetrics(SM_CXVIRTUALSCREEN) || rPosition.bottom > GetSystemMetrics(SM_CYVIRTUALSCREEN) || (rPosition.bottom >= sBarData.rc.top && rPosition.bottom <= sBarData.rc.bottom) || rPosition.Width() > size.cx || rPosition.Height() > size.cy; )
		{
			rPosition.SetRect(0, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + 1) : 0, size.cx, (sBarData.rc.top <= 0) ? (sBarData.rc.bottom + size.cy) : size.cy);
			break;
		}
		for (SetWindowPos((CONST CWnd *) NULL, rPosition.left, rPosition.top, rPosition.Width(), rPosition.Height(), SWP_SHOWWINDOW | SWP_NOZORDER); nShow != SW_SHOWMINIMIZED; )
		{
			ShowWindow(nShow);
			break;
		}
		break;
	}
	if (CreateWorkspaceWindow() && CreateOutputWindow())
	{
		UpdateWorkspaceWindow();
		UpdateOutputWindow();
	}
}

VOID CMainWnd::AddMRUMenuItem(LPCTSTR pszName, LPCTSTR pszTitle, ULONGLONG nType)
{
	INT  nDocument;
	INT  nDocuments;
	CString  szName;
	CString  szTitle;
	ULONGLONG  nComponent;
	CRecentDocumentInfo  *pRecentDocument[2];

	if ((pRecentDocument[0] = (lstrlen(pszName) > 0) ? new CRecentDocumentInfo : (CRecentDocumentInfo *)NULL))
	{
		for (nDocument = 1, nDocuments = (INT)m_pRecentDocuments.GetSize() + 1, pRecentDocument[0]->SetDocument(pszName, pszTitle, nType), m_pRecentDocuments.InsertAt(0, pRecentDocument[0], 1); nDocument < nDocuments; nDocument++)
		{
			if ((pRecentDocument[1] = m_pRecentDocuments.GetAt(nDocument)) && pRecentDocument[1]->GetDocument(szName, szTitle, nComponent))
			{
				if (szName == pszName  &&  nComponent == nType)
				{
					m_pRecentDocuments.RemoveAt(nDocument);
					delete pRecentDocument[1];
					break;
				}
			}
		}
		if (m_pRecentDocuments.GetSize() > IDM_LASTMRUDOCUMENT - IDM_FIRSTMRUDOCUMENT + 1)
		{
			if ((pRecentDocument[1] = m_pRecentDocuments.GetAt((INT)m_pRecentDocuments.GetUpperBound()))) delete pRecentDocument[1];
			m_pRecentDocuments.RemoveAt(m_pRecentDocuments.GetUpperBound());
		}
		UpdateMRUMenus();
	}
}
VOID CMainWnd::AddMRUMenuItem(CONST CDatabaseProfileInfo *pDatabaseInfo)
{
	INT  nDatabase;
	INT  nDatabases;
	CRecentDatabaseInfo  *pRecentDatabase[2];

	if ((pRecentDatabase[0] = new CRecentDatabaseInfo))
	{
		for (nDatabase = 1, nDatabases = (INT)m_pRecentDatabases.GetSize() + 1, pRecentDatabase[0]->Copy(pDatabaseInfo), m_pRecentDatabases.InsertAt(0, pRecentDatabase[0], 1), m_pRecentDocuments.RemoveAll(); nDatabase < nDatabases; nDatabase++)
		{
			if ((pRecentDatabase[1] = m_pRecentDatabases.GetAt(nDatabase)) && pRecentDatabase[0]->Compare(pRecentDatabase[1]))
			{
				m_pRecentDatabases.RemoveAt(nDatabase);
				delete pRecentDatabase[1];
				break;
			}
		}
		if (m_pRecentDatabases.GetSize() > IDM_LASTMRUDATABASE - IDM_FIRSTMRUDATABASE + 1)
		{
			if ((pRecentDatabase[1] = m_pRecentDatabases.GetAt((INT)m_pRecentDatabases.GetUpperBound()))) delete pRecentDatabase[1];
			m_pRecentDatabases.RemoveAt(m_pRecentDatabases.GetUpperBound());
		}
		UpdateMRUMenus();
	}
}

VOID CMainWnd::RemoveMRUMenuItem(LPCTSTR pszName, LPCTSTR pszTitle, ULONGLONG nType)
{
	INT  nDocument;
	INT  nDocuments;
	CString  szName;
	CString  szTitle;
	ULONGLONG  nComponent;
	CRecentDocumentInfo  *pRecentDocument;

	for (nDocument = 0, nDocuments = (INT)m_pRecentDocuments.GetSize(); nDocument < nDocuments; nDocument++)
	{
		if ((pRecentDocument = m_pRecentDocuments.GetAt(nDocument)) && pRecentDocument->GetDocument(szName, szTitle, nComponent) && szName == pszName  &&  szTitle == pszTitle  &&  nComponent == nType)
		{
			m_pRecentDocuments.RemoveAt(nDocument);
			delete pRecentDocument;
			break;
		}
	}
	if (nDocument < nDocuments) UpdateMRUMenus();
}
VOID CMainWnd::RemoveMRUMenuItem(CONST CDatabaseProfileInfo *pDatabaseInfo)
{
	INT  nDatabase;
	INT  nDatabases;
	CRecentDatabaseInfo  *pRecentDatabase;

	for (nDatabase = 0, nDatabases = (INT)m_pRecentDatabases.GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pRecentDatabase = m_pRecentDatabases.GetAt(nDatabase)) && pRecentDatabase->GetName() == pDatabaseInfo->GetName())
		{
			m_pRecentDatabases.RemoveAt(nDatabase);
			delete pRecentDatabase;
			break;
		}
	}
	if (nDatabase < nDatabases) UpdateMRUMenus();
}

VOID CMainWnd::UpdateMRUMenus()
{
	INT  nItem;
	INT  nItems;
	INT  nElement;
	INT  nElements;
	CString  szName;
	CString  szItem;
	CString  szTitle[3];
	ULONGLONG  nComponent;
	CMFCRibbonButton  *pButton[2];
	CMFCRibbonBaseElement  *pElement;
	CRecentDocuments  pRecentDocuments;
	CRecentDatabases  pRecentDatabases;
	CRecentDocumentInfo  *pRecentDocument;
	CRecentDatabaseInfo  *pRecentDatabase;

	if ((pButton[0] = (CMFCRibbonButton *)m_wndRibbonBar.FindByID(IDM_MRUDOCUMENTS)))
	{
		for (nElement = 0, nElements = (INT)pButton[0]->GetSubItems().GetCount(); nElement < nElements; nElements--)
		{
			if ((pElement = pButton[0]->GetSubItems().GetAt(nElements - 1)))
			{
				if (!pButton[0]->RemoveSubItem(nElements - 1)) break;
				continue;
			}
			break;
		}
		for (nItem = 0, nItems = EnumMRUDocuments(pRecentDocuments); nItem < nItems; nItem++)
		{
			if ((pRecentDocument = pRecentDocuments.GetAt(nItem)) && pRecentDocument->GetDocument(szName, szTitle[0], nComponent))
			{
				for (szTitle[1].Format((LOWORD(nComponent) == DISPLAY_TYPE_MMD) ? STRING(IDS_DISPLAY_TITLE_MMD) : ((LOWORD(nComponent) == DISPLAY_TYPE_SCRIPT) ? STRING(IDS_DISPLAY_TITLE_SCRIPT) : ((LOWORD(nComponent) == DISPLAY_TYPE_TCPROCEDURE) ? STRING(IDS_DISPLAY_TITLE_TCPROCEDURE) : EMPTYSTRING)), (LPCTSTR)szName), szTitle[2].Format(STRING(IDS_WINDOW_FULLTITLE), (!szTitle[0].IsEmpty()) ? (LPCTSTR)szTitle[0] : (LPCTSTR)szName, (LOWORD(nComponent) == DISPLAY_TYPE_TMPACKET) ? STRING(IDS_DISPLAY_TITLE_TMPACKET) : ((LOWORD(nComponent) == DISPLAY_TYPE_TCFUNCTION) ? STRING(IDS_DISPLAY_TITLE_TCFUNCTION) : ((LOWORD(nComponent) == DISPLAY_TYPE_TCSEQUENCE) ? STRING(IDS_DISPLAY_TITLE_TCSEQUENCE) : ((LOWORD(nComponent) == DISPLAY_TYPE_TCPROCEDURE) ? (LPCTSTR)szTitle[1] : ((LOWORD(nComponent) == DISPLAY_TYPE_TMPARAMETER) ? STRING(IDS_DISPLAY_TITLE_TMPARAMETER) : ((LOWORD(nComponent) == DISPLAY_TYPE_TCPARAMETER) ? STRING(IDS_DISPLAY_TITLE_TCPARAMETER) : ((LOWORD(nComponent) == DISPLAY_TYPE_OBPROCESSOR) ? STRING(IDS_DISPLAY_TITLE_OBPROCESSOR) : ((LOWORD(nComponent) == DISPLAY_TYPE_AND) ? STRING(IDS_DISPLAY_TITLE_AND) : ((LOWORD(nComponent) == DISPLAY_TYPE_GRD) ? STRING(IDS_DISPLAY_TITLE_GRD) : ((LOWORD(nComponent) == DISPLAY_TYPE_MMD) ? (LPCTSTR)szTitle[1] : ((LOWORD(nComponent) == DISPLAY_TYPE_POD) ? STRING(IDS_DISPLAY_TITLE_POD) : (LPCTSTR)szTitle[1]))))))))))), szItem.Format((nItem + 1 < 10) ? STRING(IDS_WINDOW_MENUITEM) : STRING(IDS_WINDOW_EXTENDEDMENUITEM), nItem + 1, (LPCTSTR)szTitle[2]); (pButton[1] = new CMainRibbonButton(IDM_FIRSTMRUDOCUMENT + nItem, szItem)); )
				{
					pButton[0]->AddSubItem(pButton[1]);
					break;
				}
			}
		}
	}
	if ((pButton[0] = (CMFCRibbonButton *)m_wndRibbonBar.FindByID(IDM_MRUDATABASES)))
	{
		for (nElement = 0, nElements = (INT)pButton[0]->GetSubItems().GetCount(); nElement < nElements; nElements--)
		{
			if ((pElement = pButton[0]->GetSubItems().GetAt(nElements - 1)))
			{
				if (!pButton[0]->RemoveSubItem(nElements - 1)) break;
				continue;
			}
			break;
		}
		for (nItem = 0, nItems = EnumMRUDatabases(pRecentDatabases); nItem < nItems; nItem++)
		{
			if ((pRecentDatabase = pRecentDatabases.GetAt(nItem)) != (CRecentDatabaseInfo *)NULL)
			{
				for (szItem.Format((nItem + 1 < 10) ? STRING(IDS_WINDOW_MENUITEM) : STRING(IDS_WINDOW_EXTENDEDMENUITEM), nItem + 1, (LPCTSTR)pRecentDatabase->GetName()); (pButton[1] = new CMainRibbonButton(IDM_FIRSTMRUDATABASE + nItem, szItem)); )
				{
					pButton[0]->AddSubItem(pButton[1]);
					break;
				}
			}
		}
	}
}

BOOL CMainWnd::CheckKeyState(INT nVirtKey) CONST
{
	BOOL  bKeyState;
	BYTE  nKeyState[256];
	CDisplayWnd  *pDisplayWnd;

	if (nVirtKey == VK_INSERT)
	{
		if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
		{
			bKeyState = pDisplayWnd->IsKeyToggled();
			return bKeyState;
		}
		return FALSE;
	}
	GetKeyboardState(nKeyState);
	return((nVirtKey == VK_CAPITAL || nVirtKey == VK_NUMLOCK || nVirtKey == VK_SCROLL) ? ((nKeyState[nVirtKey] & 0x01) ? TRUE : FALSE) : FALSE);
}

BOOL CMainWnd::IsCompiling() CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = (!GetDatabase()->IsCompiling()) ? EnumDisplayWindows(pDisplays) : -1; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->IsCompiling()) break;
		continue;
	}
	return((nDisplay != nDisplays) ? TRUE : FALSE);
}

BOOL CMainWnd::IsTesting() CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->IsTesting()) break;
		continue;
	}
	return((nDisplay != nDisplays) ? TRUE : FALSE);
}

BOOL CMainWnd::IsPrinting() CONST
{
	return((m_nRecentPrintJobs > 0) ? TRUE : FALSE);
}

CDisplayFrame *CMainWnd::GetDisplayFrame() CONST
{
	return((IsWindow(m_pDisplayFrame->GetSafeHwnd())) ? m_pDisplayFrame : (CDisplayFrame *)NULL);
}

CWorkspaceWnd *CMainWnd::GetWorkspaceWindow() CONST
{
	return((CWorkspaceWnd *)FindToolWindow(STRING(IDS_WORKSPACEWINDOW_TITLE)));
}

COutputWnd *CMainWnd::GetOutputWindow() CONST
{
	return((COutputWnd *)FindToolWindow(STRING(IDS_OUTPUTWINDOW_TITLE)));
}

CZoomWnd *CMainWnd::GetZoomWindow() CONST
{
	return m_pZoomWnd;
}

BOOL CMainWnd::CreateRibbonBar()
{
	return((m_wndRibbonBar.Create(this) && m_wndRibbonBar.LoadFromResource(IDR_MAINFRAME)) ? TRUE : FALSE);
}

BOOL CMainWnd::CreateToolBars()
{
	INT  nItem[2];
	INT  nItems[2];
	BOOL  bShow[2];
	CRect  rToolBar[2];
	BITMAP  sBitmap[2];
	CBitmap  cBitmap[2];
	CUIntArray  nItemIDs[2];
	CProfile  cProfile;

	if (m_wndMimicsObjectsToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(1, 1, 1, 1), ID_MIMICSOBJECTS_TOOLBAR))
	{
		if (m_wndTCStepsToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(1, 1, 1, 1), ID_TCSTEPS_TOOLBAR))
		{
			for (nItem[0] = 0, nItems[0] = IDM_LASTMIMICSOBJECT - IDM_FIRSTMIMICSOBJECT; nItem[0] <= nItems[0]; nItem[0]++)
			{
				nItemIDs[0].Add(IDM_FIRSTMIMICSOBJECT + nItem[0]);
				continue;
			}
			for (nItem[1] = 0, nItems[1] = IDM_LASTTCSTEP - IDM_FIRSTTCSTEP; nItem[1] <= nItems[1]; nItem[1]++)
			{
				nItemIDs[1].Add(IDM_FIRSTTCSTEP + nItem[1]);
				continue;
			}
			if (cBitmap[0].LoadBitmap(IDB_MIMICSOBJECTSTOOLBARTEMPLATE) && cBitmap[0].GetBitmap(&sBitmap[0]) > 0)
			{
				if (cBitmap[1].LoadBitmap(IDB_TCSTEPSTOOLBARTEMPLATE) && cBitmap[1].GetBitmap(&sBitmap[1]) > 0)
				{
					for (m_wndMimicsObjectsToolBar.SetWindowText(STRING(IDS_TOOLBAR_MIMICSOBJECTS_TITLE)), m_wndTCStepsToolBar.SetWindowText(STRING(IDS_TOOLBAR_TCSTEPS_TITLE)), m_wndMimicsObjectsToolBar.SetLockedSizes(CSize(sBitmap[0].bmWidth / (INT)nItemIDs[0].GetSize() + sBitmap[0].bmHeight / 4, sBitmap[0].bmHeight + sBitmap[0].bmHeight / 4), CSize(sBitmap[0].bmWidth / (INT)nItemIDs[0].GetSize(), sBitmap[0].bmHeight)), m_wndTCStepsToolBar.SetLockedSizes(CSize(sBitmap[1].bmWidth / (INT)nItemIDs[1].GetSize() + sBitmap[1].bmHeight / 4, sBitmap[1].bmHeight + sBitmap[1].bmHeight / 4), CSize(sBitmap[1].bmWidth / (INT)nItemIDs[1].GetSize(), sBitmap[1].bmHeight)), m_wndMimicsObjectsToolBar.SetButtons(nItemIDs[0].GetData(), (INT)nItemIDs[0].GetSize()), m_wndTCStepsToolBar.SetButtons(nItemIDs[1].GetData(), (INT)nItemIDs[1].GetSize()), m_wndMimicsObjectsToolBar.EnableDocking(FALSE), m_wndTCStepsToolBar.EnableDocking(FALSE); m_wndMimicsObjectsToolBar.LoadBitmap(IDB_MIMICSOBJECTSTOOLBARTEMPLATE, IDB_MIMICSOBJECTSTOOLBARTEMPLATE, 0, TRUE, IDB_MIMICSOBJECTSDISABLEDTOOLBARTEMPLATE) && m_wndTCStepsToolBar.LoadBitmap(IDB_TCSTEPSTOOLBARTEMPLATE, IDB_TCSTEPSTOOLBARTEMPLATE, 0, TRUE, IDB_TCSTEPSDISABLEDTOOLBARTEMPLATE); )
					{
						for (m_wndTCStepsToolBar.InsertSeparator(IDM_FIRSTTCACTIONOBJECTSTEP - IDM_FIRSTTCSTEP), bShow[0] = FALSE; cProfile.GetMimicsObjectsToolBarInfo(rToolBar[0], bShow[0]); )
						{
							m_wndMimicsObjectsToolBar.SetPaneRect(rToolBar[0]);
							break;
						}
						for (bShow[1] = FALSE; cProfile.GetTCStepsToolBarInfo(rToolBar[1], bShow[1]); )
						{
							m_wndTCStepsToolBar.SetPaneRect(rToolBar[1]);
							break;
						}
						m_wndMimicsObjectsToolBar.FloatPane(m_wndMimicsObjectsToolBar.GetPaneRect(), DM_UNKNOWN, FALSE);
						m_wndTCStepsToolBar.FloatPane(m_wndTCStepsToolBar.GetPaneRect(), DM_UNKNOWN, FALSE);
						m_wndMimicsObjectsToolBar.ShowPane(bShow[0], FALSE, FALSE);
						m_wndTCStepsToolBar.ShowPane(bShow[1], FALSE, FALSE);
						cBitmap[1].DeleteObject();
						cBitmap[0].DeleteObject();
						return TRUE;
					}
					cBitmap[1].DeleteObject();
				}
				cBitmap[0].DeleteObject();
			}
			m_wndTCStepsToolBar.DestroyWindow();
		}
		m_wndMimicsObjectsToolBar.DestroyWindow();
	}
	return FALSE;
}

BOOL CMainWnd::CreateStatusBar()
{
	return(m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1));
}

BOOL CMainWnd::CreateWorkspaceWindow()
{
	UINT  nState;
	CRect  rWorkspaceWnd;
	CByteArray  nWorkspaceInfo;
	CWorkspaceWnd  *pWorkspaceWnd;
	CProfile  cProfile;

	if (!cProfile.GetWorkspaceWindowInfo(nState, rWorkspaceWnd, nWorkspaceInfo))
	{
		ClientToScreen((rWorkspaceWnd = CalcClientRect(TRUE)));
		rWorkspaceWnd.SetRect(rWorkspaceWnd.left, rWorkspaceWnd.top, rWorkspaceWnd.left + WORKSPACEWINDOW_DEFAULT_WIDTH, rWorkspaceWnd.bottom);
		nState = TOOLWINDOW_DOCKSTATE_LEFT;
	}
	if ((pWorkspaceWnd = new CWorkspaceWnd))
	{
		for (pWorkspaceWnd->SetDockState(nState | TOOLWINDOW_DOCKSTATE_LOCKED); nState & (TOOLWINDOW_DOCKSTATE_LEFT | TOOLWINDOW_DOCKSTATE_TOP | TOOLWINDOW_DOCKSTATE_RIGHT | TOOLWINDOW_DOCKSTATE_BOTTOM); )
		{
			ScreenToClient(rWorkspaceWnd);
			break;
		}
		if (pWorkspaceWnd->Create(this, STRING(IDS_WORKSPACEWINDOW_TITLE), ((nState & (TOOLWINDOW_DOCKSTATE_LEFT | TOOLWINDOW_DOCKSTATE_TOP | TOOLWINDOW_DOCKSTATE_RIGHT | TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (TWS_DOCKED | WS_CLIPCHILDREN) : (TWS_FLOATING | WS_CLIPCHILDREN)) | ((!(nState & TOOLWINDOW_DOCKSTATE_HIDDEN)) ? WS_VISIBLE : 0), rWorkspaceWnd))
		{
			pWorkspaceWnd->SetDockState(nState);
			pWorkspaceWnd->SetData(nWorkspaceInfo);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMainWnd::CreateOutputWindow()
{
	UINT  nState;
	CRect  rOutputWnd;
	CByteArray  nOutputInfo;
	COutputWnd  *pOutputWnd;
	CProfile  cProfile;

	if (!cProfile.GetOutputWindowInfo(nState, rOutputWnd, nOutputInfo))
	{
		ClientToScreen((rOutputWnd = CalcClientRect(TRUE)));
		rOutputWnd.SetRect(rOutputWnd.left, rOutputWnd.bottom - OUTPUTWINDOW_DEFAULT_HEIGHT, rOutputWnd.right, rOutputWnd.bottom);
		nState = TOOLWINDOW_DOCKSTATE_BOTTOM;
	}
	if ((pOutputWnd = new COutputWnd))
	{
		for (pOutputWnd->SetDockState(nState | TOOLWINDOW_DOCKSTATE_LOCKED); nState & (TOOLWINDOW_DOCKSTATE_LEFT | TOOLWINDOW_DOCKSTATE_TOP | TOOLWINDOW_DOCKSTATE_RIGHT | TOOLWINDOW_DOCKSTATE_BOTTOM); )
		{
			ScreenToClient(rOutputWnd);
			break;
		}
		if (pOutputWnd->Create(this, STRING(IDS_OUTPUTWINDOW_TITLE), ((nState & (TOOLWINDOW_DOCKSTATE_LEFT | TOOLWINDOW_DOCKSTATE_TOP | TOOLWINDOW_DOCKSTATE_RIGHT | TOOLWINDOW_DOCKSTATE_BOTTOM)) ? (TWS_DOCKED | WS_CLIPCHILDREN) : (TWS_FLOATING | WS_CLIPCHILDREN)) | ((!(nState & TOOLWINDOW_DOCKSTATE_HIDDEN)) ? WS_VISIBLE : 0), rOutputWnd))
		{
			pOutputWnd->SetDockState(nState);
			pOutputWnd->SetData(nOutputInfo);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMainWnd::CreateZoomWindow()
{
	UINT  nState;
	CRect  rArea;
	CRect  rZoomWnd;
	CZoomWnd  *pZoomWnd;
	CProfile  cProfile;

	if (!cProfile.GetZoomWindowInfo(nState, rZoomWnd))
	{
		ClientToScreen((rArea = CalcClientRect(TRUE)));
		rZoomWnd.SetRect(rArea.right - ZOOMWINDOW_SIZE_WIDTH, rArea.bottom - ZOOMWINDOW_SIZE_HEIGHT, rArea.right, rArea.bottom);
		rZoomWnd.OffsetRect(-GetSystemMetrics(SM_CXFRAME), -GetSystemMetrics(SM_CYFRAME));
		nState = 0;
	}
	if ((pZoomWnd = new CZoomWnd))
	{
		if (pZoomWnd->Create(this, STRING(IDS_ZOOMWINDOW_TITLE), nState, rZoomWnd))
		{
			m_pZoomWnd = pZoomWnd;
			return TRUE;
		}
	}
	return FALSE;
}

VOID CMainWnd::UpdateTitle()
{
	CString  szTitle;

	if (TestAccount())
	{
		szTitle.Format(STRING(IDS_EDITOR_TITLE), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetAppTitle());
		SetWindowText(szTitle);
		return;
	}
	SetWindowText(GetAppTitle());
}

VOID CMainWnd::UpdateStatusBar()
{
	m_wndStatusBar.SetIndicators();
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE), STRING(IDS_STATUSBAR_READY));
	m_wndStatusBar.UpdateAllPanes();
}

VOID CMainWnd::UpdateWorkspaceWindow()
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		pWorkspaceWnd->UpdateDatabaseContents();
		pWorkspaceWnd->UpdateDatabaseProcedures();
		pWorkspaceWnd->UpdateDatabaseLogs();
	}
}

VOID CMainWnd::UpdateOutputWindow()
{
	return;
}

INT CMainWnd::EnumMRUDocuments(CRecentDocuments &pRecentDocuments)
{
	INT  nDocument;
	INT  nDocuments;
	CString  szName;
	CString  szTitle;
	CANDWnd  *pANDWnd;
	CGRDWnd  *pGRDWnd;
	CMMDWnd  *pMMDWnd;
	CPODWnd  *pPODWnd;
	ULONGLONG  nComponent;
	CPtrArray  pDocuments;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;
	CTCFunctionWnd  *pTCFunctionWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CTCProcedureWnd  *pTCProcedureWnd;
	CTMParameterWnd  *pTMParameterWnd;
	CTCParameterWnd  *pTCParameterWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CRecentDocumentInfo  *pRecentDocument;

	for (nDocument = 0, nDocuments = (!m_pRecentDocuments.GetSize()) ? EnumDisplayWindows(pDocuments) : 0, nDocuments = min(IDM_LASTMRUDOCUMENT - IDM_FIRSTMRUDOCUMENT + 1, nDocuments); nDocument < nDocuments; nDocument++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDocuments.GetAt(nDocument)))
		{
			if ((pRecentDocument = new CRecentDocumentInfo))
			{
				switch (pDisplayWnd->GetType())
				{
				case DISPLAY_TYPE_TMPACKET:
				{ if ((pTMPacketWnd = (CTMPacketWnd *)pDisplayWnd) && lstrlen(pTMPacketWnd->GetName()) > 0) pRecentDocument->SetDocument(pTMPacketWnd->GetName(), pTMPacketWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_TCFUNCTION:
				{ if ((pTCFunctionWnd = (CTCFunctionWnd *)pDisplayWnd) && lstrlen(pTCFunctionWnd->GetName()) > 0) pRecentDocument->SetDocument(pTCFunctionWnd->GetName(), pTCFunctionWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_TCSEQUENCE:
				{ if ((pTCSequenceWnd = (CTCSequenceWnd *)pDisplayWnd) && lstrlen(pTCSequenceWnd->GetName()) > 0) pRecentDocument->SetDocument(pTCSequenceWnd->GetName(), pTCSequenceWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_TCPROCEDURE:
				{ if ((pTCProcedureWnd = (CTCProcedureWnd *)pDisplayWnd) && lstrlen(pTCProcedureWnd->GetName()) > 0) pRecentDocument->SetDocument(pTCProcedureWnd->GetName(), pTCProcedureWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_TMPARAMETER:
				{ if ((pTMParameterWnd = (CTMParameterWnd *)pDisplayWnd) && lstrlen(pTMParameterWnd->GetName()) > 0) pRecentDocument->SetDocument(pTMParameterWnd->GetName(), pTMParameterWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_TCPARAMETER:
				{ if ((pTCParameterWnd = (CTCParameterWnd *)pDisplayWnd) && lstrlen(pTCParameterWnd->GetName()) > 0) pRecentDocument->SetDocument(pTCParameterWnd->GetName(), pTCParameterWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_OBPROCESSOR:
				{ if ((pOBProcessorWnd = (COBProcessorWnd *)pDisplayWnd) && lstrlen(pOBProcessorWnd->GetName()) > 0) pRecentDocument->SetDocument(pOBProcessorWnd->GetName(), pOBProcessorWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_AND:
				{ if ((pANDWnd = (CANDWnd *)pDisplayWnd) && lstrlen(pANDWnd->GetName()) > 0) pRecentDocument->SetDocument(pANDWnd->GetName(), pANDWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_GRD:
				{ if ((pGRDWnd = (CGRDWnd *)pDisplayWnd) && lstrlen(pGRDWnd->GetName()) > 0) pRecentDocument->SetDocument(pGRDWnd->GetName(), pGRDWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_MMD:
				{ if ((pMMDWnd = (CMMDWnd *)pDisplayWnd) && lstrlen(pMMDWnd->GetName()) > 0) pRecentDocument->SetDocument(pMMDWnd->GetName(), pMMDWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_POD:
				{ if ((pPODWnd = (CPODWnd *)pDisplayWnd) && lstrlen(pPODWnd->GetName()) > 0) pRecentDocument->SetDocument(pPODWnd->GetName(), pPODWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				case DISPLAY_TYPE_SCRIPT:
				{ if ((pScriptWnd = (CScriptWnd *)pDisplayWnd) && lstrlen(pScriptWnd->GetName()) > 0) pRecentDocument->SetDocument(pScriptWnd->GetName(), pScriptWnd->GetTitle(), pDisplayWnd->GetType());
				break;
				}
				}
				if (!pRecentDocument->GetDocument(szName, szTitle, nComponent) || m_pRecentDocuments.Add(pRecentDocument) < 0)
				{
					delete pRecentDocument;
					continue;
				}
			}
		}
	}
	pRecentDocuments.Copy(&m_pRecentDocuments);
	return((INT)pRecentDocuments.GetSize());
}

INT CMainWnd::EnumMRUDatabases(CRecentDatabases &pRecentDatabases)
{
	CRecentDatabaseInfo  *pRecentDatabase;

	if (!m_pRecentDatabases.GetSize())
	{
		if ((pRecentDatabase = (GetDatabase()->GetName().GetLength() > 0) ? new CRecentDatabaseInfo : (CRecentDatabaseInfo *)NULL))
		{
			for (pRecentDatabase->Copy(GetDatabase()); m_pRecentDatabases.Add(pRecentDatabase) < 0; )
			{
				delete pRecentDatabase;
				break;
			}
		}
	}
	pRecentDatabases.Copy(&m_pRecentDatabases);
	return((INT)pRecentDatabases.GetSize());
}

VOID CMainWnd::SaveMRULists()
{
	CByteArray  nInfo[2];
	CProfile  cProfile;

	if (m_pRecentDocuments.Map(nInfo[0]) && m_pRecentDatabases.Map(nInfo[1]))
	{
		cProfile.SetRecentDocuments(nInfo[0]);
		cProfile.SetRecentDatabases(nInfo[1]);
	}
}

VOID CMainWnd::LoadMRULists()
{
	CByteArray  nInfo[2];
	CProfile  cProfile;

	if ((cProfile.GetRecentDocuments(nInfo[0]) || !nInfo[0].GetSize()) && (cProfile.GetRecentDatabases(nInfo[1]) || !nInfo[1].GetSize()))
	{
		m_pRecentDocuments.Unmap(nInfo[0]);
		m_pRecentDatabases.Unmap(nInfo[1]);
	}
}

BOOL CMainWnd::ShowPrintStatus(BOOL bPrinting)
{
	CMenu  *pMenu;

	for (m_nRecentPrintJobs = (bPrinting) ? (m_nRecentPrintJobs + 1) : (m_nRecentPrintJobs - 1); (pMenu = GetSystemMenu(FALSE)); )
	{
		pMenu->EnableMenuItem(SC_CLOSE, (!m_nRecentPrintJobs) ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_GRAYED));
		break;
	}
	return TRUE;
}

BOOL CMainWnd::ShowBarMessage(INT nMessageID)
{
	CString  szMessage;

	if (nMessageID == IDS_STATUSBAR_INITIALIZING || nMessageID == IDS_STATUSBAR_LOGGING)
	{
		if ((szMessage = STRING(nMessageID)) == m_wndStatusBar.GetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE))) return TRUE;
		m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1);
	}
	if (m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_STATUSBAR_MESSAGEPANE), STRING(nMessageID)))
	{
		m_wndStatusBar.UpdateWindow();
		return TRUE;
	}
	return FALSE;
}

UINT CMainWnd::GetSubMenuState(CMenu *pMenu) CONST
{
	UINT  nItem;
	UINT  nItems;
	CMenu  *pSubMenu;

	for (nItem = 0, nItems = pMenu->GetMenuItemCount(); nItem < nItems; nItem++)
	{
		if ((pSubMenu = pMenu->GetSubMenu(nItem)) && !(GetSubMenuState(pSubMenu) & MF_GRAYED)) break;
		if (!pSubMenu  &&  pMenu->GetMenuItemID(nItem) && !(pMenu->GetMenuState(nItem, MF_BYPOSITION) & MF_GRAYED)) break;
	}
	return((nItem < nItems) ? MF_ENABLED : MF_GRAYED);
}

VOID CMainWnd::DoCleanDatabaseFiles()
{
	INT  nPos;
	INT  nCount;
	INT  nScript;
	INT  nScripts;
	INT  nLayout;
	INT  nLayouts;
	INT  nProcedure;
	INT  nProcedures;
	CString  szFileName[2];
	CString  szFileFormat;
	CString  szSearchFile;
	CString  szFileTitle;
	CMMDLayout  *pLayout;
	CMMDLayouts  pLayouts;
	CFileFindEx  cFileFind;
	CAutomationScript  *pScript;
	CAutomationScripts  pScripts;
	CDatabaseTCProcedure  *pProcedure;
	CDatabaseTCProcedures  pProcedures;

	if ((nPos = GetDatabase()->GetFileName().ReverseFind(STRING(IDS_FILENAME_TMP)[0])) >= 0)
	{
		for (szSearchFile = GetDatabase()->GetFileName().Left(nPos) + STRING(IDS_FILENAME_TMP); cFileFind.FindFile(szSearchFile); )
		{
			while (cFileFind.FindNextFile())
			{
				CFileEx::Remove(cFileFind.GetFilePath());
				continue;
			}
			CFileEx::Remove(cFileFind.GetFilePath());
			cFileFind.Close();
			break;
		}
		for (szSearchFile = GetDatabase()->GetFileName().Left(nPos) + STRING(IDS_FILENAME_NEW), nCount = 1; cFileFind.FindFile(szSearchFile); )
		{
			while ((nCount = (!cFileFind.FindNextFile()) ? (nCount - 1) : nCount) >= 0)
			{
				if (!cFileFind.GetFilePath().CompareNoCase(GetDatabase()->GetUpdateFileName()))
				{
					for (CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) & ~FILE_ATTRIBUTE_READONLY), CFileEx::SetAttributes(GetDatabase()->GetFileName(), CFileEx::GetAttributes(GetDatabase()->GetFileName()) & ~FILE_ATTRIBUTE_READONLY); CFileEx::Copy(cFileFind.GetFilePath(), GetDatabase()->GetFileName()); )
					{
						CDatabaseEngine::SecureDirectoryOrFile(GetDatabase()->GetFileName());
						CFileEx::Remove(cFileFind.GetFilePath());
						break;
					}
					CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) | FILE_ATTRIBUTE_READONLY);
					CFileEx::SetAttributes(GetDatabase()->GetFileName(), CFileEx::GetAttributes(GetDatabase()->GetFileName()) | FILE_ATTRIBUTE_READONLY);
					continue;
				}
				if (!cFileFind.GetFilePath().CompareNoCase(GetDatabase()->GetLibraryUpdateFileName()))
				{
					for (CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) & ~FILE_ATTRIBUTE_READONLY), CFileEx::SetAttributes(GetDatabase()->GetLibraryFileName(), CFileEx::GetAttributes(GetDatabase()->GetLibraryFileName()) & ~FILE_ATTRIBUTE_READONLY); CFileEx::Copy(cFileFind.GetFilePath(), GetDatabase()->GetLibraryFileName()); )
					{
						CDatabaseEngine::SecureDirectoryOrFile(GetDatabase()->GetLibraryFileName());
						CFileEx::Remove(cFileFind.GetFilePath());
						break;
					}
					CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) | FILE_ATTRIBUTE_READONLY);
					CFileEx::SetAttributes(GetDatabase()->GetLibraryFileName(), CFileEx::GetAttributes(GetDatabase()->GetLibraryFileName()) | FILE_ATTRIBUTE_READONLY);
					continue;
				}
				for (nLayout = 0, nLayouts = GetDatabase()->EnumMMDs(pLayouts); nLayout < nLayouts; nLayout++)
				{
					if ((pLayout = pLayouts.GetAt(nLayout)) != (CMMDLayout *)NULL)
					{
						szFileFormat = STRING(IDS_MIMICSDISPLAYCODE_UPDATE_FILENAME);
						szFileTitle.Format(szFileFormat, (LPCTSTR)pLayout->GetName());
						if (cFileFind.GetFileName().CompareNoCase(szFileTitle) == 0)
						{
							szFileFormat = STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME);
							szFileName[0].Format(szFileFormat, (LPCTSTR)pLayout->GetName());
							szFileName[1] = cFileFind.GetFilePath().Left(cFileFind.GetFilePath().GetLength() - cFileFind.GetFileName().GetLength()) + szFileName[0];
							for (CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) & ~FILE_ATTRIBUTE_READONLY), CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) & ~FILE_ATTRIBUTE_READONLY); CFileEx::Copy(cFileFind.GetFilePath(), szFileName[1]); )
							{
								CDatabaseEngine::SecureDirectoryOrFile(szFileName[1]);
								CFileEx::Remove(cFileFind.GetFilePath());
								break;
							}
							CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) | FILE_ATTRIBUTE_READONLY);
							CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) | FILE_ATTRIBUTE_READONLY);
							break;
						}
					}
				}
				for (nScript = 0, nScripts = (nLayout == nLayouts) ? GetDatabase()->EnumScripts(pScripts) : 0; nScript < nScripts; nScript++)
				{
					if ((pScript = pScripts.GetAt(nScript)) != (CAutomationScript *)NULL)
					{
						szFileFormat = STRING(IDS_SCRIPTDISPLAYCODE_UPDATE_FILENAME);
						szFileTitle.Format(szFileFormat, (LPCTSTR)pScript->GetName());
						if (cFileFind.GetFileName().CompareNoCase(szFileTitle) == 0)
						{
							szFileFormat = STRING(IDS_SCRIPTDISPLAYCODE_NORMAL_FILENAME);
							szFileName[0].Format(szFileFormat, (LPCTSTR)pScript->GetName());
							szFileName[1] = cFileFind.GetFilePath().Left(cFileFind.GetFilePath().GetLength() - cFileFind.GetFileName().GetLength()) + szFileName[0];
							for (CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) & ~FILE_ATTRIBUTE_READONLY), CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) & ~FILE_ATTRIBUTE_READONLY); CFileEx::Copy(cFileFind.GetFilePath(), szFileName[1]); )
							{
								CDatabaseEngine::SecureDirectoryOrFile(szFileName[1]);
								CFileEx::Remove(cFileFind.GetFilePath());
								break;
							}
							CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) | FILE_ATTRIBUTE_READONLY);
							CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) | FILE_ATTRIBUTE_READONLY);
							break;
						}
					}
				}
				for (nProcedure = 0, nProcedures = (nLayout == nLayouts && nScript == nScripts) ? ((pProcedures.Copy(GetDatabase()->GetTCProcedures())) ? (INT)pProcedures.GetSize() : 0) : 0; nProcedure < nProcedures; nProcedure++)
				{
					if ((pProcedure = pProcedures.GetAt(nProcedure)) != (CDatabaseTCProcedure *)NULL)
					{
						szFileFormat = STRING(IDS_TELECOMMANDPROCEDURECODE_UPDATE_FILENAME);
						szFileTitle.Format(szFileFormat, (LPCTSTR)pProcedure->GetName());
						if (cFileFind.GetFileName().CompareNoCase(szFileTitle) == 0)
						{
							szFileFormat = STRING(IDS_TELECOMMANDPROCEDURECODE_NORMAL_FILENAME);
							szFileName[0].Format(szFileFormat, (LPCTSTR)pProcedure->GetName());
							szFileName[1] = cFileFind.GetFilePath().Left(cFileFind.GetFilePath().GetLength() - cFileFind.GetFileName().GetLength()) + szFileName[0];
							for (CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) & ~FILE_ATTRIBUTE_READONLY), CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) & ~FILE_ATTRIBUTE_READONLY); CFileEx::Copy(cFileFind.GetFilePath(), szFileName[1]); )
							{
								CDatabaseEngine::SecureDirectoryOrFile(szFileName[1]);
								CFileEx::Remove(cFileFind.GetFilePath());
								break;
							}
							CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) | FILE_ATTRIBUTE_READONLY);
							CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) | FILE_ATTRIBUTE_READONLY);
							break;
						}
					}
				}
				if (nLayout == nLayouts  &&  nScript == nScripts  &&  nProcedure == nProcedures)
				{
					CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) & ~FILE_ATTRIBUTE_READONLY);
					CFileEx::Remove(cFileFind.GetFilePath());
				}
			}
			cFileFind.Close();
			break;
		}
	}
}

BOOL CMainWnd::CanCleanDatabaseFiles() CONST
{
	INT  nPos;
	CString  szSearchFile;
	CFileFindEx  cFileFind;

	if ((nPos = GetDatabase()->GetFileName().ReverseFind(STRING(IDS_FILENAME_TMP)[0])) >= 0)
	{
		for (szSearchFile = GetDatabase()->GetFileName().Left(nPos) + STRING(IDS_FILENAME_TMP); cFileFind.FindFile(szSearchFile); )
		{
			cFileFind.Close();
			return TRUE;
		}
		for (szSearchFile = GetDatabase()->GetFileName().Left(nPos) + STRING(IDS_FILENAME_NEW); cFileFind.FindFile(szSearchFile); )
		{
			cFileFind.Close();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMainWnd::StartAssistant()
{
	return FALSE;
}

VOID CMainWnd::StopAssistant()
{
	return;
}

CRect CMainWnd::CalcClientRect(BOOL bFrame) CONST
{
	INT  nTool;
	INT  nTools;
	UINT  nState;
	CRect  rWnd[4];
	CRect  rToolWnd[5];
	CToolWnd  *pToolWnd;

	for (GetClientRect(rWnd[0]), m_wndRibbonBar.GetWindowRect(rWnd[1]), m_wndStatusBar.GetWindowRect(rWnd[2]), ScreenToClient(rWnd[1]), ScreenToClient(rWnd[2]), rWnd[0].SubtractRect(rWnd[0], rWnd[1]), rWnd[0].SubtractRect(rWnd[0], rWnd[2]); bFrame; )
	{
		for (nTool = 0, nTools = (INT)m_pwndTools.GetSize(), rToolWnd[0].SetRectEmpty(), rToolWnd[1].SetRectEmpty(), rToolWnd[2].SetRectEmpty(), rToolWnd[3].SetRectEmpty(), rWnd[1] = rWnd[0]; nTool < nTools; nTool++)
		{
			if ((pToolWnd = (CToolWnd *)m_pwndTools.GetAt(nTool)) && pToolWnd->IsVisible() && pToolWnd->IsDocked())
			{
				pToolWnd->GetWindowRect(rToolWnd[4]);
				ScreenToClient(rToolWnd[4]);
				if ((nState = pToolWnd->GetDockState(TRUE)) & TOOLWINDOW_DOCKSTATE_LEFT)
				{
					rToolWnd[0] = (rToolWnd[0].IsRectEmpty() || rToolWnd[0].left > rToolWnd[4].left) ? rToolWnd[4] : rToolWnd[0];
					rWnd[1].left = max(rToolWnd[4].right, rWnd[1].left);
					continue;
				}
				if (nState & TOOLWINDOW_DOCKSTATE_TOP)
				{
					rToolWnd[1] = (rToolWnd[1].IsRectEmpty() || rToolWnd[1].top > rToolWnd[4].top) ? rToolWnd[4] : rToolWnd[1];
					rWnd[1].top = max(rToolWnd[4].bottom, rWnd[1].top);
					continue;
				}
				if (nState & TOOLWINDOW_DOCKSTATE_RIGHT)
				{
					rToolWnd[2] = (rToolWnd[2].IsRectEmpty() || rToolWnd[2].right < rToolWnd[4].right) ? rToolWnd[4] : rToolWnd[2];
					rWnd[1].right = min(rToolWnd[4].left, rWnd[1].right);
					continue;
				}
				if (nState & TOOLWINDOW_DOCKSTATE_BOTTOM)
				{
					rToolWnd[3] = (rToolWnd[3].IsRectEmpty() || rToolWnd[3].bottom < rToolWnd[4].bottom) ? rToolWnd[4] : rToolWnd[3];
					rWnd[1].bottom = min(rToolWnd[4].top, rWnd[1].bottom);
					continue;
				}
			}
		}
		if (!rToolWnd[0].IsRectEmpty())
		{
			rWnd[2].left = min(rToolWnd[0].left, rWnd[0].left);
			rWnd[3].left = max(rToolWnd[0].left, rWnd[0].left);
			rWnd[1].left -= min(rWnd[2].left - rWnd[0].left, 0) + max(rWnd[3].left - rWnd[0].left, 0);
		}
		if (!rToolWnd[1].IsRectEmpty())
		{
			rWnd[2].top = min(rToolWnd[1].top, rWnd[0].top);
			rWnd[3].top = max(rToolWnd[1].top, rWnd[0].top);
			rWnd[1].top -= min(rWnd[2].top - rWnd[0].top, 0) + max(rWnd[3].top - rWnd[0].top, 0);
		}
		if (!rToolWnd[2].IsRectEmpty())
		{
			rWnd[2].right = max(rToolWnd[2].right, rWnd[0].right);
			rWnd[3].right = min(rToolWnd[2].right, rWnd[0].right);
			rWnd[1].right -= max(rWnd[2].right - rWnd[0].right, 0) + min(rWnd[3].right - rWnd[0].right, 0);
		}
		if (!rToolWnd[3].IsRectEmpty())
		{
			rWnd[2].bottom = max(rToolWnd[3].bottom, rWnd[0].bottom);
			rWnd[3].bottom = min(rToolWnd[3].bottom, rWnd[0].bottom);
			rWnd[1].bottom -= max(rWnd[2].bottom - rWnd[0].bottom, 0) + min(rWnd[3].bottom - rWnd[0].bottom, 0);
		}
		return rWnd[1];
	}
	return rWnd[0];
}

void CMainWnd::RecalcLayout(BOOL bNotify)
{
	if (IsWindow(m_wndRibbonBar.GetSafeHwnd()) && IsWindow(m_wndStatusBar.GetSafeHwnd())) ArrangeToolWindows();
	CLocaleMDIFrameWnd::RecalcLayout(bNotify);
}

BOOL CMainWnd::EnumDisplayWindows(HWND hWnd, LPARAM lParam)
{
	DWORD_PTR  dwStyle;
	CPtrArray  *pDisplays = (CPtrArray *)lParam;

	for (dwStyle = (DWORD_PTR)GetWindowLongPtr(hWnd, GWL_EXSTYLE); dwStyle & WS_EX_MDICHILD; )
	{
		pDisplays->Add(CWnd::FromHandle(hWnd));
		break;
	}
	return TRUE;
}

LRESULT CMainWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == AFX_WM_ON_RIBBON_CUSTOMIZE)
	{
		SetTimer(message, 0, NULL);
		return TRUE;
	}
	return CLocaleMDIFrameWnd::WindowProc(message, wParam, lParam);
}

BOOL CMainWnd::CanUpdateUI() CONST
{
	return(!IsCompiling());
}

BEGIN_MESSAGE_MAP(CMainWnd, CLocaleMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_INITMENUPOPUP()
	ON_WM_ENTERIDLE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_NEW, OnNew)
	ON_COMMAND(IDM_NEWITEM_TMPACKET, OnNewItemTMPacket)
	ON_COMMAND(IDM_NEWITEM_TCFUNCTION, OnNewItemTCFunction)
	ON_COMMAND(IDM_NEWITEM_TCSEQUENCE, OnNewItemTCSequence)
	ON_COMMAND(IDM_NEWITEM_TCPROCEDURE, OnNewItemTCProcedure)
	ON_COMMAND(IDM_NEWITEM_TMPARAMETER, OnNewItemTMParameter)
	ON_COMMAND(IDM_NEWITEM_TCPARAMETER, OnNewItemTCParameter)
	ON_COMMAND(IDM_NEWITEM_OBPROCESSOR, OnNewItemOBProcessor)
	ON_COMMAND(IDM_NEWITEM_AND, OnNewItemAND)
	ON_COMMAND(IDM_NEWITEM_GRD, OnNewItemGRD)
	ON_COMMAND(IDM_NEWITEM_MMD, OnNewItemMMD)
	ON_COMMAND(IDM_NEWITEM_POD, OnNewItemPOD)
	ON_COMMAND(IDM_NEWITEM_SCRIPT, OnNewItemScript)
	ON_COMMAND(IDM_OPENITEM_TMPACKET, OnOpenItemTMPacket)
	ON_COMMAND(IDM_OPENITEM_TCFUNCTION, OnOpenItemTCFunction)
	ON_COMMAND(IDM_OPENITEM_TCSEQUENCE, OnOpenItemTCSequence)
	ON_COMMAND(IDM_OPENITEM_TCPROCEDURE, OnOpenItemTCProcedure)
	ON_COMMAND(IDM_OPENITEM_TMPARAMETER, OnOpenItemTMParameter)
	ON_COMMAND(IDM_OPENITEM_TCPARAMETER, OnOpenItemTCParameter)
	ON_COMMAND(IDM_OPENITEM_OBPROCESSOR, OnOpenItemOBProcessor)
	ON_COMMAND(IDM_OPENITEM_AND, OnOpenItemAND)
	ON_COMMAND(IDM_OPENITEM_GRD, OnOpenItemGRD)
	ON_COMMAND(IDM_OPENITEM_MMD, OnOpenItemMMD)
	ON_COMMAND(IDM_OPENITEM_POD, OnOpenItemPOD)
	ON_COMMAND(IDM_OPENITEM_SCRIPT, OnOpenItemScript)
	ON_COMMAND(IDM_RENAMEITEM_TMPACKET, OnRenameItemTMPacket)
	ON_COMMAND(IDM_RENAMEITEM_TCFUNCTION, OnRenameItemTCFunction)
	ON_COMMAND(IDM_RENAMEITEM_TCSEQUENCE, OnRenameItemTCSequence)
	ON_COMMAND(IDM_RENAMEITEM_TCPROCEDURE, OnRenameItemTCProcedure)
	ON_COMMAND(IDM_RENAMEITEM_TMPARAMETER, OnRenameItemTMParameter)
	ON_COMMAND(IDM_RENAMEITEM_TCPARAMETER, OnRenameItemTCParameter)
	ON_COMMAND(IDM_RENAMEITEM_OBPROCESSOR, OnRenameItemOBProcessor)
	ON_COMMAND(IDM_RENAMEITEM_AND, OnRenameItemAND)
	ON_COMMAND(IDM_RENAMEITEM_GRD, OnRenameItemGRD)
	ON_COMMAND(IDM_RENAMEITEM_MMD, OnRenameItemMMD)
	ON_COMMAND(IDM_RENAMEITEM_POD, OnRenameItemPOD)
	ON_COMMAND(IDM_RENAMEITEM_SCRIPT, OnRenameItemScript)
	ON_COMMAND(IDM_DELETEITEM_TMPACKET, OnDeleteItemTMPacket)
	ON_COMMAND(IDM_DELETEITEM_TCFUNCTION, OnDeleteItemTCFunction)
	ON_COMMAND(IDM_DELETEITEM_TCSEQUENCE, OnDeleteItemTCSequence)
	ON_COMMAND(IDM_DELETEITEM_TCPROCEDURE, OnDeleteItemTCProcedure)
	ON_COMMAND(IDM_DELETEITEM_TMPARAMETER, OnDeleteItemTMParameter)
	ON_COMMAND(IDM_DELETEITEM_TCPARAMETER, OnDeleteItemTCParameter)
	ON_COMMAND(IDM_DELETEITEM_OBPROCESSOR, OnDeleteItemOBProcessor)
	ON_COMMAND(IDM_DELETEITEM_AND, OnDeleteItemAND)
	ON_COMMAND(IDM_DELETEITEM_GRD, OnDeleteItemGRD)
	ON_COMMAND(IDM_DELETEITEM_MMD, OnDeleteItemMMD)
	ON_COMMAND(IDM_DELETEITEM_POD, OnDeleteItemPOD)
	ON_COMMAND(IDM_DELETEITEM_SCRIPT, OnDeleteItemScript)
	ON_COMMAND(IDM_OPEN_TMPACKET, OnOpenTMPacket)
	ON_COMMAND(IDM_IMPORT_TMPACKET, OnImportTMPacket)
	ON_COMMAND(IDM_EXPORT_TMPACKET, OnExportTMPacket)
	ON_COMMAND(IDM_OPEN_TCFUNCTION, OnOpenTCFunction)
	ON_COMMAND(IDM_IMPORT_TCFUNCTION, OnImportTCFunction)
	ON_COMMAND(IDM_EXPORT_TCFUNCTION, OnExportTCFunction)
	ON_COMMAND(IDM_OPEN_TCSEQUENCE, OnOpenTCSequence)
	ON_COMMAND(IDM_IMPORT_TCSEQUENCE, OnImportTCSequence)
	ON_COMMAND(IDM_EXPORT_TCSEQUENCE, OnExportTCSequence)
	ON_COMMAND(IDM_OPEN_TCPROCEDURE, OnOpenTCProcedure)
	ON_COMMAND(IDM_IMPORT_TCPROCEDURE, OnImportTCProcedure)
	ON_COMMAND(IDM_EXPORT_TCPROCEDURE, OnExportTCProcedure)
	ON_COMMAND(IDM_OPEN_TMPARAMETER, OnOpenTMParameter)
	ON_COMMAND(IDM_IMPORT_TMPARAMETER, OnImportTMParameter)
	ON_COMMAND(IDM_EXPORT_TMPARAMETER, OnExportTMParameter)
	ON_COMMAND(IDM_OPEN_TCPARAMETER, OnOpenTCParameter)
	ON_COMMAND(IDM_IMPORT_TCPARAMETER, OnImportTCParameter)
	ON_COMMAND(IDM_EXPORT_TCPARAMETER, OnExportTCParameter)
	ON_COMMAND(IDM_OPEN_OBPROCESSOR, OnOpenOBProcessor)
	ON_COMMAND(IDM_IMPORT_OBPROCESSOR, OnImportOBProcessor)
	ON_COMMAND(IDM_EXPORT_OBPROCESSOR, OnExportOBProcessor)
	ON_COMMAND(IDM_CUSTOMIMPORT_OBPROCESSOR, OnCustomImportOBProcessor)
	ON_COMMAND(IDM_CUSTOMEXPORT_OBPROCESSOR, OnCustomExportOBProcessor)
	ON_COMMAND(IDM_CUSTOMIMPORT_MEMORYIMAGE, OnCustomImportMemoryImage)
	ON_COMMAND(IDM_CUSTOMEXPORT_MEMORYIMAGE, OnCustomExportMemoryImage)
	ON_COMMAND(IDM_OPEN_AND, OnOpenAND)
	ON_COMMAND(IDM_IMPORT_AND, OnImportAND)
	ON_COMMAND(IDM_EXPORT_AND, OnExportAND)
	ON_COMMAND(IDM_OPEN_GRD, OnOpenGRD)
	ON_COMMAND(IDM_IMPORT_GRD, OnImportGRD)
	ON_COMMAND(IDM_EXPORT_GRD, OnExportGRD)
	ON_COMMAND(IDM_OPEN_MMD, OnOpenMMD)
	ON_COMMAND(IDM_IMPORT_MMD, OnImportMMD)
	ON_COMMAND(IDM_EXPORT_MMD, OnExportMMD)
	ON_COMMAND(IDM_OPEN_POD, OnOpenPOD)
	ON_COMMAND(IDM_IMPORT_POD, OnImportPOD)
	ON_COMMAND(IDM_EXPORT_POD, OnExportPOD)
	ON_COMMAND(IDM_OPEN_SCRIPT, OnOpenScript)
	ON_COMMAND(IDM_IMPORT_SCRIPT, OnImportScript)
	ON_COMMAND(IDM_EXPORT_SCRIPT, OnExportScript)
	ON_COMMAND(IDM_DATABASE_NEW, OnDatabaseNew)
	ON_COMMAND(IDM_DATABASE_OPEN, OnDatabaseOpen)
	ON_COMMAND(IDM_DATABASE_IMPORT, OnDatabaseImport)
	ON_COMMAND(IDM_DATABASE_EXPORT, OnDatabaseExport)
	ON_COMMAND(IDM_DATABASE_DELETE, OnDatabaseDelete)
	ON_COMMAND(IDM_DATABASE_VERSIONING, OnDatabaseVersioning)
	ON_COMMAND(IDM_DOCUMENT_NEW, OnDocumentNew)
	ON_COMMAND(IDM_DOCUMENT_OPEN, OnDocumentOpen)
	ON_COMMAND(IDM_DOCUMENT_SAVE, OnDocumentSave)
	ON_COMMAND(IDM_DOCUMENT_SAVEAS, OnDocumentSaveAs)
	ON_COMMAND(IDM_DOCUMENT_SAVEALL, OnDocumentSaveAll)
	ON_COMMAND(IDM_DOCUMENT_CHECK, OnDocumentCheck)
	ON_COMMAND(IDM_DOCUMENT_DELETE, OnDocumentDelete)
	ON_COMMAND(IDM_DOCUMENT_CLOSE, OnDocumentClose)
	ON_COMMAND(IDM_PRINTSETUP, OnPrintSetup)
	ON_COMMAND(IDM_PRINT, OnPrint)
	ON_COMMAND(IDM_PRINTSOURCECODE, OnPrintSourceCode)
	ON_COMMAND(IDM_PRINTALLITEMS, OnPrintAllItems)
	ON_COMMAND(IDM_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(IDM_EDIT_REDO, OnEditRedo)
	ON_COMMAND(IDM_EDIT_FIND, OnEditFind)
	ON_COMMAND(IDM_EDIT_FINDSEARCHFORWARD, OnEditFindSearchForward)
	ON_COMMAND(IDM_EDIT_FINDSEARCHALL, OnEditFindSearchAll)
	ON_COMMAND(IDM_EDIT_FINDMATCHCASE, OnEditFindMatchCase)
	ON_COMMAND(IDM_EDIT_FINDMATCHWORD, OnEditFindMatchWord)
	ON_COMMAND(IDM_EDIT_FINDNEXT, OnEditFindNext)
	ON_COMMAND(IDM_EDIT_FINDPREVIOUS, OnEditFindPrevious)
	ON_COMMAND(IDM_EDIT_REPLACE, OnEditReplace)
	ON_COMMAND(IDM_EDIT_GOTO, OnEditGoTo)
	ON_COMMAND(IDM_EDIT_CUT, OnEditCut)
	ON_COMMAND(IDM_EDIT_COPY, OnEditCopy)
	ON_COMMAND(IDM_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(IDM_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(IDM_EDIT_SELECTALL, OnEditSelectAll)
	ON_COMMAND(IDM_EDIT_SAVETABLE, OnEditSaveTable)
	ON_COMMAND(IDM_EDIT_CHECKTABLE, OnEditCheckTable)
	ON_COMMAND(IDM_EDIT_DELETETABLE, OnEditDeleteTable)
	ON_COMMAND(IDM_EDIT_IMPORTTABLES, OnEditImportTables)
	ON_COMMAND(IDM_EDIT_EXPORTTABLES, OnEditExportTables)
	ON_COMMAND(IDM_EDIT_PRINTTABLE, OnEditPrintTable)
	ON_COMMAND(IDM_EDIT_PRINTALLTABLES, OnEditPrintAllTables)
	ON_COMMAND(IDM_EDIT_INSERTTABLEROWABOVE, OnEditInsertTableRowAbove)
	ON_COMMAND(IDM_EDIT_INSERTTABLEROWBELOW, OnEditInsertTableRowBelow)
	ON_COMMAND(IDM_EDIT_INSERTTABLECOLUMNBEFORE, OnEditInsertTableColumnBefore)
	ON_COMMAND(IDM_EDIT_INSERTTABLECOLUMNAFTER, OnEditInsertTableColumnAfter)
	ON_COMMAND(IDM_EDIT_CLEARTABLEROW, OnEditClearTableRow)
	ON_COMMAND(IDM_EDIT_DELETETABLEROW, OnEditDeleteTableRow)
	ON_COMMAND(IDM_EDIT_DELETETABLECOLUMN, OnEditDeleteTableColumn)
	ON_COMMAND(IDM_EDIT_COPYTABLEROW, OnEditCopyTableRow)
	ON_COMMAND(IDM_EDIT_PASTETABLEROW, OnEditPasteTableRow)
	ON_COMMAND(IDM_EDIT_DISCARDALLTABLES, OnEditDiscardAllTables)
	ON_COMMAND(IDM_EDIT_DISCARDTABLES, OnEditDiscardTables)
	ON_COMMAND(IDM_EDIT_RESETTABLES, OnEditResetTables)
	ON_COMMAND(IDM_EDIT_CREATEMIMICSGROUP, OnEditCreateMimicsGroup)
	ON_COMMAND(IDM_EDIT_DELETEMIMICSGROUP, OnEditDeleteMimicsGroup)
	ON_COMMAND(IDM_EDIT_COLLECTMIMICSGROUP, OnEditCollectMimicsGroup)
	ON_COMMAND(IDM_EDIT_DISCARDMIMICSGROUP, OnEditDiscardMimicsGroup)
	ON_COMMAND(IDM_EDIT_STEPINTOMIMICSGROUP, OnEditStepIntoMimicsGroup)
	ON_COMMAND(IDM_EDIT_STEPOUTMIMICSGROUP, OnEditStepOutMimicsGroup)
	ON_COMMAND(IDM_EDIT_IMPORTMIMICSGROUP, OnEditImportMimicsGroup)
	ON_COMMAND(IDM_EDIT_EXPORTMIMICSGROUP, OnEditExportMimicsGroup)
	ON_COMMAND(IDM_EDIT_ALIGNMIMICSOBJECTHORIZONTAL, OnEditHorzAlignMimicsObjects)
	ON_COMMAND(IDM_EDIT_ALIGNMIMICSOBJECTVERTICAL, OnEditVertAlignMimicsObjects)
	ON_COMMAND(IDM_EDIT_MOVEMIMICSOBJECTTOTOP, OnEditMoveMimicsObjectToTop)
	ON_COMMAND(IDM_EDIT_MOVEMIMICSOBJECTTOBOTTOM, OnEditMoveMimicsObjectToBottom)
	ON_COMMAND(IDM_EDIT_MOVEMIMICSOBJECTUP, OnEditMoveMimicsObjectUp)
	ON_COMMAND(IDM_EDIT_MOVEMIMICSOBJECTDOWN, OnEditMoveMimicsObjectDown)
	ON_COMMAND(IDM_EDIT_SHOWHIDEMIMICSOBJECT, OnEditShowHideMimicsObject)
	ON_COMMAND(IDM_EDIT_FLIPMIMICSOBJECTHORIZONTAL, OnEditHorzFlipMimicsObject)
	ON_COMMAND(IDM_EDIT_FLIPMIMICSOBJECTVERTICAL, OnEditVertFlipMimicsObject)
	ON_COMMAND(IDM_EDIT_ROTATEMIMICSOBJECT, OnEditRotateMimicsObject)
	ON_COMMAND(IDM_EDIT_TURNMIMICSOBJECT, OnEditTurnMimicsObject)
	ON_COMMAND(IDM_VIEW_MIMICSOBJECTPROPERTIES, OnViewMimicsObjectProperties)
	ON_COMMAND(IDM_VIEW_MIMICSOBJECTITEM, OnViewMimicsObjectItem)
	ON_COMMAND(IDM_VIEW_MIMICSOBJECTCODE, OnViewMimicsObjectCode)
	ON_COMMAND(IDM_PROPERTIES, OnProperties)
	ON_COMMAND(IDM_SOURCECODE, OnSourceCode)
	ON_COMMAND(IDM_LINKINFORMATION, OnLinkInformation)
	ON_COMMAND(IDM_WORKSPACEWINDOW, OnWorkspaceWindow)
	ON_COMMAND(IDM_OUTPUTWINDOW, OnOutputWindow)
	ON_COMMAND(IDM_ZOOMWINDOW, OnZoomWindow)
	ON_COMMAND(IDM_MIMICSOBJECTSTOOLBAR, OnMimicsObjectsToolBar)
	ON_COMMAND(IDM_MIMICSGROUP, OnMimicsGroup)
	ON_COMMAND(IDM_TCSTEPSTOOLBAR, OnTCStepsToolBar)
	ON_COMMAND(IDM_BUILDOPTIONS, OnBuildOptions)
	ON_COMMAND(IDM_BUILDDIRECTIVES, OnBuildDirectives)
	ON_COMMAND(IDM_BUILDDOWNLOAD, OnBuildDownload)
	ON_COMMAND(IDM_BUILDCOMPILE, OnBuildCompile)
	ON_COMMAND(IDM_BUILDCOMPILEALL, OnBuildCompileAll)
	ON_COMMAND(IDM_BUILDCOMPILEBATCHES, OnBuildCompileBatches)
	ON_COMMAND(IDM_BUILDCOMPILESTOP, OnBuildCompileStop)
	ON_COMMAND(IDM_BUILDCLEAN, OnBuildClean)
	ON_COMMAND(IDM_BUILDTEST, OnBuildTest)
	ON_COMMAND(IDM_BUILDTESTBREAK, OnBuildTestBreak)
	ON_COMMAND(IDM_BUILDTESTCONTINUE, OnBuildTestContinue)
	ON_COMMAND(IDM_BUILDTESTSTEPINTO, OnBuildTestStepInto)
	ON_COMMAND(IDM_BUILDTESTSTEPOVER, OnBuildTestStepOver)
	ON_COMMAND(IDM_BUILDTESTSTEPOUT, OnBuildTestStepOut)
	ON_COMMAND(IDM_BUILDTESTSTOP, OnBuildTestStop)
	ON_COMMAND(IDM_BUILDTESTRESET, OnBuildTestReset)
	ON_COMMAND(IDM_OPTIONS, OnToolsOptions)
	ON_COMMAND(IDM_USERS, OnUsers)
	ON_COMMAND(IDM_PRIVILEGES, OnPrivileges)
	ON_COMMAND(IDM_VALIDITY, OnValidity)
	ON_COMMAND(IDM_NEXTWINDOW, OnNextWindow)
	ON_COMMAND(IDM_PREVIOUSWINDOW, OnPreviousWindow)
	ON_COMMAND(IDM_CLOSEWINDOW, OnCloseWindow)
	ON_COMMAND(IDM_CLOSEALLWINDOWS, OnCloseAllWindows)
	ON_COMMAND(IDM_WINDOWS, OnWindows)
	ON_COMMAND(IDM_ASSISTANTSUPPORTDATECONVERSIONS, OnAssistantSupportDateConversions)
	ON_COMMAND(IDM_ASSISTANTLISTEN, OnAssistantListen)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_COMMAND_RANGE(IDM_FIRSTMRUDOCUMENT, IDM_LASTMRUDOCUMENT, OnMRUDocument)
	ON_COMMAND_RANGE(IDM_FIRSTMRUDATABASE, IDM_LASTMRUDATABASE, OnMRUDatabase)
	ON_COMMAND_RANGE(IDM_FIRSTMIMICSOBJECT, IDM_LASTMIMICSOBJECT, OnMimicsObjects)
	ON_COMMAND_RANGE(IDM_FIRSTTCSTEP, IDM_LASTTCSTEP, OnTCSteps)
	ON_MESSAGE(WM_SETTINGCHANGE, OnSystemSettingsChange)
	ON_MESSAGE(WM_HELP, OnOnlineHelp)
	ON_UPDATE_COMMAND_UI(IDM_NEW, OnUpdateNew)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_TMPACKET, OnUpdateNewItemTMPacket)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_TCFUNCTION, OnUpdateNewItemTCFunction)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_TCSEQUENCE, OnUpdateNewItemTCSequence)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_TCPROCEDURE, OnUpdateNewItemTCProcedure)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_TMPARAMETER, OnUpdateNewItemTMParameter)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_TCPARAMETER, OnUpdateNewItemTCParameter)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_OBPROCESSOR, OnUpdateNewItemOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_AND, OnUpdateNewItemAND)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_GRD, OnUpdateNewItemGRD)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_MMD, OnUpdateNewItemMMD)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_POD, OnUpdateNewItemPOD)
	ON_UPDATE_COMMAND_UI(IDM_NEWITEM_SCRIPT, OnUpdateNewItemScript)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_TMPACKET, OnUpdateOpenItemTMPacket)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_TCFUNCTION, OnUpdateOpenItemTCFunction)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_TCSEQUENCE, OnUpdateOpenItemTCSequence)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_TCPROCEDURE, OnUpdateOpenItemTCProcedure)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_TMPARAMETER, OnUpdateOpenItemTMParameter)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_TCPARAMETER, OnUpdateOpenItemTCParameter)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_OBPROCESSOR, OnUpdateOpenItemOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_AND, OnUpdateOpenItemAND)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_GRD, OnUpdateOpenItemGRD)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_MMD, OnUpdateOpenItemMMD)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_POD, OnUpdateOpenItemPOD)
	ON_UPDATE_COMMAND_UI(IDM_OPENITEM_SCRIPT, OnUpdateOpenItemScript)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_TMPACKET, OnUpdateRenameItemTMPacket)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_TCFUNCTION, OnUpdateRenameItemTCFunction)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_TCSEQUENCE, OnUpdateRenameItemTCSequence)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_TCPROCEDURE, OnUpdateRenameItemTCProcedure)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_TMPARAMETER, OnUpdateRenameItemTMParameter)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_TCPARAMETER, OnUpdateRenameItemTCParameter)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_OBPROCESSOR, OnUpdateRenameItemOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_AND, OnUpdateRenameItemAND)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_GRD, OnUpdateRenameItemGRD)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_MMD, OnUpdateRenameItemMMD)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_POD, OnUpdateRenameItemPOD)
	ON_UPDATE_COMMAND_UI(IDM_RENAMEITEM_SCRIPT, OnUpdateRenameItemScript)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_TMPACKET, OnUpdateDeleteItemTMPacket)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_TCFUNCTION, OnUpdateDeleteItemTCFunction)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_TCSEQUENCE, OnUpdateDeleteItemTCSequence)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_TCPROCEDURE, OnUpdateDeleteItemTCProcedure)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_TMPARAMETER, OnUpdateDeleteItemTMParameter)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_TCPARAMETER, OnUpdateDeleteItemTCParameter)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_OBPROCESSOR, OnUpdateDeleteItemOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_AND, OnUpdateDeleteItemAND)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_GRD, OnUpdateDeleteItemGRD)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_MMD, OnUpdateDeleteItemMMD)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_POD, OnUpdateDeleteItemPOD)
	ON_UPDATE_COMMAND_UI(IDM_DELETEITEM_SCRIPT, OnUpdateDeleteItemScript)
	ON_UPDATE_COMMAND_UI(IDM_OPEN, OnUpdateOpen)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT, OnUpdateImport)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT, OnUpdateExport)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_TMPACKET, OnUpdateOpenTMPacket)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_TMPACKET, OnUpdateImportTMPacket)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_TMPACKET, OnUpdateExportTMPacket)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_TCFUNCTION, OnUpdateOpenTCFunction)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_TCFUNCTION, OnUpdateImportTCFunction)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_TCFUNCTION, OnUpdateExportTCFunction)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_TCSEQUENCE, OnUpdateOpenTCSequence)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_TCSEQUENCE, OnUpdateImportTCSequence)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_TCSEQUENCE, OnUpdateExportTCSequence)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_TCPROCEDURE, OnUpdateOpenTCProcedure)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_TCPROCEDURE, OnUpdateImportTCProcedure)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_TCPROCEDURE, OnUpdateExportTCProcedure)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_TMPARAMETER, OnUpdateOpenTMParameter)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_TMPARAMETER, OnUpdateImportTMParameter)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_TMPARAMETER, OnUpdateExportTMParameter)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_TCPARAMETER, OnUpdateOpenTCParameter)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_TCPARAMETER, OnUpdateImportTCParameter)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_TCPARAMETER, OnUpdateExportTCParameter)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_OBPROCESSOR, OnUpdateOpenOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_OBPROCESSOR, OnUpdateImportOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_OBPROCESSOR, OnUpdateExportOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_CUSTOMIMPORT_OBPROCESSOR, OnUpdateCustomImportOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_CUSTOMEXPORT_OBPROCESSOR, OnUpdateCustomExportOBProcessor)
	ON_UPDATE_COMMAND_UI(IDM_CUSTOMIMPORT_MEMORYIMAGE, OnUpdateCustomImportMemoryImage)
	ON_UPDATE_COMMAND_UI(IDM_CUSTOMEXPORT_MEMORYIMAGE, OnUpdateCustomExportMemoryImage)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_AND, OnUpdateOpenAND)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_AND, OnUpdateImportAND)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_AND, OnUpdateExportAND)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_GRD, OnUpdateOpenGRD)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_GRD, OnUpdateImportGRD)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_GRD, OnUpdateExportGRD)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_MMD, OnUpdateOpenMMD)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_MMD, OnUpdateImportMMD)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_MMD, OnUpdateExportMMD)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_POD, OnUpdateOpenPOD)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_POD, OnUpdateImportPOD)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_POD, OnUpdateExportPOD)
	ON_UPDATE_COMMAND_UI(IDM_OPEN_SCRIPT, OnUpdateOpenScript)
	ON_UPDATE_COMMAND_UI(IDM_IMPORT_SCRIPT, OnUpdateImportScript)
	ON_UPDATE_COMMAND_UI(IDM_EXPORT_SCRIPT, OnUpdateExportScript)
	ON_UPDATE_COMMAND_UI(IDM_DATABASE_NEW, OnUpdateDatabaseNew)
	ON_UPDATE_COMMAND_UI(IDM_DATABASE_OPEN, OnUpdateDatabaseOpen)
	ON_UPDATE_COMMAND_UI(IDM_DATABASE_IMPORT, OnUpdateDatabaseImport)
	ON_UPDATE_COMMAND_UI(IDM_DATABASE_EXPORT, OnUpdateDatabaseExport)
	ON_UPDATE_COMMAND_UI(IDM_DATABASE_DELETE, OnUpdateDatabaseDelete)
	ON_UPDATE_COMMAND_UI(IDM_DATABASE_VERSIONING, OnUpdateDatabaseVersioning)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_NEW, OnUpdateDocumentNew)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_OPEN, OnUpdateDocumentOpen)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_SAVE, OnUpdateDocumentSave)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_SAVEAS, OnUpdateDocumentSaveAs)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_SAVEALL, OnUpdateDocumentSaveAll)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_CHECK, OnUpdateDocumentCheck)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_DELETE, OnUpdateDocumentDelete)
	ON_UPDATE_COMMAND_UI(IDM_DOCUMENT_CLOSE, OnUpdateDocumentClose)
	ON_UPDATE_COMMAND_UI(IDM_PRINTSETUP, OnUpdatePrintSetup)
	ON_UPDATE_COMMAND_UI(IDM_PRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(IDM_PRINTSOURCECODE, OnUpdatePrintSourceCode)
	ON_UPDATE_COMMAND_UI(IDM_PRINTALLITEMS, OnUpdatePrintAllItems)
	ON_UPDATE_COMMAND_UI(IDM_MRUDOCUMENTS, OnUpdateMRUDocuments)
	ON_UPDATE_COMMAND_UI(IDM_MRUDATABASES, OnUpdateMRUDatabases)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FIND, OnUpdateEditFind)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FINDSEARCHFORWARD, OnUpdateEditFindSearchForward)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FINDSEARCHALL, OnUpdateEditFindSearchAll)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FINDMATCHCASE, OnUpdateEditFindMatchCase)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FINDMATCHWORD, OnUpdateEditFindMatchWord)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FINDNEXT, OnUpdateEditFindNext)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FINDPREVIOUS, OnUpdateEditFindPrevious)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_REPLACE, OnUpdateEditReplace)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_GOTO, OnUpdateEditGoTo)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_SELECTALL, OnUpdateEditSelectAll)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_SAVETABLE, OnUpdateEditSaveTable)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_CHECKTABLE, OnUpdateEditCheckTable)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DELETETABLE, OnUpdateEditDeleteTable)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_IMPORTTABLES, OnUpdateEditImportTables)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_EXPORTTABLES, OnUpdateEditExportTables)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PRINTTABLE, OnUpdateEditPrintTable)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PRINTALLTABLES, OnUpdateEditPrintAllTables)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_INSERTTABLEROWABOVE, OnUpdateEditInsertTableRowAbove)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_INSERTTABLEROWBELOW, OnUpdateEditInsertTableRowBelow)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_INSERTTABLECOLUMNBEFORE, OnUpdateEditInsertTableColumnBefore)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_INSERTTABLECOLUMNAFTER, OnUpdateEditInsertTableColumnAfter)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_CLEARTABLEROW, OnUpdateEditClearTableRow)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DELETETABLEROW, OnUpdateEditDeleteTableRow)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DELETETABLECOLUMN, OnUpdateEditDeleteTableColumn)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_COPYTABLEROW, OnUpdateEditCopyTableRow)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_PASTETABLEROW, OnUpdateEditPasteTableRow)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DISCARDALLTABLES, OnUpdateEditDiscardAllTables)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DISCARDTABLES, OnUpdateEditDiscardTables)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_RESETTABLES, OnUpdateEditResetTables)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_CREATEMIMICSGROUP, OnUpdateEditCreateMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DELETEMIMICSGROUP, OnUpdateEditDeleteMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_COLLECTMIMICSGROUP, OnUpdateEditCollectMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_DISCARDMIMICSGROUP, OnUpdateEditDiscardMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_STEPINTOMIMICSGROUP, OnUpdateEditStepIntoMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_STEPOUTMIMICSGROUP, OnUpdateEditStepOutMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_IMPORTMIMICSGROUP, OnUpdateEditImportMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_EXPORTMIMICSGROUP, OnUpdateEditExportMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_ALIGNMIMICSOBJECTHORIZONTAL, OnUpdateEditHorzAlignMimicsObjects)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_ALIGNMIMICSOBJECTVERTICAL, OnUpdateEditVertAlignMimicsObjects)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_MOVEMIMICSOBJECTTOTOP, OnUpdateEditMoveMimicsObjectToTop)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_MOVEMIMICSOBJECTTOBOTTOM, OnUpdateEditMoveMimicsObjectToBottom)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_MOVEMIMICSOBJECTUP, OnUpdateEditMoveMimicsObjectUp)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_MOVEMIMICSOBJECTDOWN, OnUpdateEditMoveMimicsObjectDown)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_SHOWHIDEMIMICSOBJECT, OnUpdateEditShowHideMimicsObject)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FLIPMIMICSOBJECTHORIZONTAL, OnUpdateEditHorzFlipMimicsObject)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_FLIPMIMICSOBJECTVERTICAL, OnUpdateEditVertFlipMimicsObject)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_ROTATEMIMICSOBJECT, OnUpdateEditRotateMimicsObject)
	ON_UPDATE_COMMAND_UI(IDM_EDIT_TURNMIMICSOBJECT, OnUpdateEditTurnMimicsObject)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MIMICSOBJECTPROPERTIES, OnUpdateViewMimicsObjectProperties)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MIMICSOBJECTITEM, OnUpdateViewMimicsObjectItem)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_MIMICSOBJECTCODE, OnUpdateViewMimicsObjectCode)
	ON_UPDATE_COMMAND_UI(IDM_PROPERTIES, OnUpdateProperties)
	ON_UPDATE_COMMAND_UI(IDM_SOURCECODE, OnUpdateSourceCode)
	ON_UPDATE_COMMAND_UI(IDM_LINKINFORMATION, OnUpdateLinkInformation)
	ON_UPDATE_COMMAND_UI(IDM_WORKSPACEWINDOW, OnUpdateWorkspaceWindow)
	ON_UPDATE_COMMAND_UI(IDM_OUTPUTWINDOW, OnUpdateOutputWindow)
	ON_UPDATE_COMMAND_UI(IDM_ZOOMWINDOW, OnUpdateZoomWindow)
	ON_UPDATE_COMMAND_UI(IDM_MIMICSOBJECTSTOOLBAR, OnUpdateMimicsObjectsToolBar)
	ON_UPDATE_COMMAND_UI(IDM_MIMICSOBJECTS, OnUpdateMimicsObjectsMenu)
	ON_UPDATE_COMMAND_UI(IDM_MIMICSGROUP, OnUpdateMimicsGroup)
	ON_UPDATE_COMMAND_UI(IDM_TCSTEPSTOOLBAR, OnUpdateTCStepsToolBar)
	ON_UPDATE_COMMAND_UI(IDM_TCSTEPS, OnUpdateTCStepsMenu)
	ON_UPDATE_COMMAND_UI(IDM_BUILDOPTIONS, OnUpdateBuildOptions)
	ON_UPDATE_COMMAND_UI(IDM_BUILDDIRECTIVES, OnUpdateBuildDirectives)
	ON_UPDATE_COMMAND_UI(IDM_BUILDDOWNLOAD, OnUpdateBuildDownload)
	ON_UPDATE_COMMAND_UI(IDM_BUILDCOMPILE, OnUpdateBuildCompile)
	ON_UPDATE_COMMAND_UI(IDM_BUILDCOMPILEALL, OnUpdateBuildCompileAll)
	ON_UPDATE_COMMAND_UI(IDM_BUILDCOMPILEBATCHES, OnUpdateBuildCompileBatches)
	ON_UPDATE_COMMAND_UI(IDM_BUILDCOMPILESTOP, OnUpdateBuildCompileStop)
	ON_UPDATE_COMMAND_UI(IDM_BUILDCLEAN, OnUpdateBuildClean)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTEST, OnUpdateBuildTest)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTESTBREAK, OnUpdateBuildTestBreak)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTESTCONTINUE, OnUpdateBuildTestContinue)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTESTSTEPINTO, OnUpdateBuildTestStepInto)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTESTSTEPOVER, OnUpdateBuildTestStepOver)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTESTSTEPOUT, OnUpdateBuildTestStepOut)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTESTSTOP, OnUpdateBuildTestStop)
	ON_UPDATE_COMMAND_UI(IDM_BUILDTESTRESET, OnUpdateBuildTestReset)
	ON_UPDATE_COMMAND_UI(IDM_OPTIONS, OnUpdateToolsOptions)
	ON_UPDATE_COMMAND_UI(IDM_USERS, OnUpdateUsers)
	ON_UPDATE_COMMAND_UI(IDM_PRIVILEGES, OnUpdatePrivileges)
	ON_UPDATE_COMMAND_UI(IDM_VALIDITY, OnUpdateValidity)
	ON_UPDATE_COMMAND_UI(IDM_NEXTWINDOW, OnUpdateNextWindow)
	ON_UPDATE_COMMAND_UI(IDM_PREVIOUSWINDOW, OnUpdatePreviousWindow)
	ON_UPDATE_COMMAND_UI(IDM_CLOSEWINDOW, OnUpdateCloseWindow)
	ON_UPDATE_COMMAND_UI(IDM_CLOSEALLWINDOWS, OnUpdateCloseAllWindows)
	ON_UPDATE_COMMAND_UI(IDM_WINDOWS, OnUpdateWindows)
	ON_UPDATE_COMMAND_UI(IDM_ASSISTANTSUPPORTDATECONVERSIONS, OnUpdateAssistantSupportDateConversions)
	ON_UPDATE_COMMAND_UI(IDM_ASSISTANTLISTEN, OnUpdateAssistantListen)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SERVERPANE, OnUpdateStatusBarServerPane)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SPACECRAFTPANE, OnUpdateStatusBarSpacecraftPane)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_USERPANE, OnUpdateStatusBarUserPane)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_DATABASEPANE, OnUpdateStatusBarDatabasePane)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_CAPSKEYPANE, OnUpdateStatusBarCAPSKeyPane)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_NUMKEYPANE, OnUpdateStatusBarNUMKeyPane)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_SCRLKEYPANE, OnUpdateStatusBarSCRLKeyPane)
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_OVRKEYPANE, OnUpdateStatusBarOVRKeyPane)
	ON_UPDATE_COMMAND_UI(IDM_ABOUT, OnUpdateAbout)
	ON_UPDATE_COMMAND_UI(IDM_HELP, OnUpdateHelp)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateExit)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTMRUDOCUMENT, IDM_LASTMRUDOCUMENT, OnUpdateMRUDocument)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTMRUDATABASE, IDM_LASTMRUDATABASE, OnUpdateMRUDatabase)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTMIMICSOBJECT, IDM_LASTMIMICSOBJECT, OnUpdateMimicsObjects)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTTCSTEP, IDM_LASTTCSTEP, OnUpdateTCSteps)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTTCSTEPBREAKPOINTOPTION, IDM_LASTTCSTEPBREAKPOINTOPTION, OnUpdateTCStepBreakpointOptions)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTDISPLAYWINDOWS, IDM_LASTDISPLAYWINDOWS, OnUpdateDisplayWindows)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_FIRSTDISPLAYWINDOW, IDM_LASTDISPLAYWINDOW, OnUpdateDisplayWindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWnd message handlers

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CLocaleMDIFrameWnd::OnCreate(lpCreateStruct) != -1 && CreateToolBars() && CreateRibbonBar() && CreateStatusBar()) ? 0 : -1);
}

BOOL CMainWnd::OnCreateClient(LPCREATESTRUCT pcs, CCreateContext *pContext)
{
	SCROLLINFO  sScrollInfo = { sizeof(SCROLLINFO),SIF_ALL };

	for (m_bDoSubclass = FALSE; CLocaleMDIFrameWnd::OnCreateClient(pcs, pContext); )
	{
		if (m_pDisplayFrame->Create(this))
		{
			m_pDisplayFrame->SetScrollInfo(SB_HORZ, &sScrollInfo);
			m_pDisplayFrame->SetScrollInfo(SB_VERT, &sScrollInfo);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CMainWnd::OnEraseBkgnd(CDC *pDC)
{
	CRect  rArea;
	CBrush  cBrush;

	for (GetClientRect(rArea); cBrush.CreateSolidBrush(GetSysColor(COLOR_APPWORKSPACE)); )
	{
		pDC->FillRect(rArea, &cBrush);
		cBrush.DeleteObject();
		return TRUE;
	}
	return CLocaleMDIFrameWnd::OnEraseBkgnd(pDC);
}

void CMainWnd::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	UINT  nItem;
	UINT  nItems;
	CMenu  *pSubMenu;

	for (nItem = 0, nItems = pPopupMenu->GetMenuItemCount(); nItem < nItems && !bSysMenu; nItem++)
	{
		if ((pSubMenu = pPopupMenu->GetSubMenu(nItem)))
		{
			OnInitMenuPopup(pSubMenu, nItem, bSysMenu);
			pPopupMenu->EnableMenuItem(nItem, MF_BYPOSITION | GetSubMenuState(pSubMenu));
			continue;
		}
	}
	CLocaleMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

void CMainWnd::OnEnterIdle(UINT nType, CWnd *pWnd)
{
	if (nType == MSGF_DIALOGBOX)
	{
		for (; pWnd->IsKindOf(RUNTIME_CLASS(CLoginDialog)); )
		{
			ShowBarMessage(IDS_STATUSBAR_LOGGING);
			break;
		}
	}
	CLocaleMDIFrameWnd::OnEnterIdle(nType, pWnd);
}

BOOL CMainWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	INT  nIndex;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	if (LOWORD(wParam) >= IDM_FIRSTDISPLAYWINDOWS  &&  LOWORD(wParam) <= IDM_LASTDISPLAYWINDOWS)
	{
		CDisplayWindowsDialog  cDisplayWindowsDialog;
		cDisplayWindowsDialog.DoModal();
		return TRUE;
	}
	if (LOWORD(wParam) >= IDM_FIRSTDISPLAYWINDOW  &&  LOWORD(wParam) <= IDM_LASTDISPLAYWINDOW)
	{
		if ((pDisplayWnd = ((nIndex = LOWORD(wParam) - IDM_FIRSTDISPLAYWINDOW) < EnumDisplayWindows(pDisplays)) ? (CDisplayWnd *)pDisplays.GetAt(nIndex) : (CDisplayWnd *)NULL))
		{
			MDIActivate(pDisplayWnd);
			return TRUE;
		}
	}
	return CLocaleMDIFrameWnd::OnCommand(wParam, lParam);
}

void CMainWnd::OnTimer(UINT_PTR nEventID)
{
	CUserInterfaceDialog  *pUserInterfaceDialog;

	if (nEventID == AFX_WM_ON_RIBBON_CUSTOMIZE)
	{
		for (KillTimer(nEventID); (pUserInterfaceDialog = new CUserInterfaceDialog(this, &m_wndRibbonBar)); )
		{
			pUserInterfaceDialog->DoModal();
			delete pUserInterfaceDialog;
			break;
		}
	}
	CLocaleMDIFrameWnd::OnTimer(nEventID);
}

LRESULT CMainWnd::OnSystemSettingsChange(WPARAM wParam, LPARAM lParam)
{
	InitializeDefaultPrinter();
	return Default();
}

LRESULT CMainWnd::OnOnlineHelp(WPARAM wParam, LPARAM lParam)
{
	CString  szTopic;

	szTopic.Format(STRING(IDS_ONLINEHELP_MMDOBJECTPROPERTIESDIALOG_TOPIC), (wParam == (UINT)-1) ? (LPCTSTR)lParam : EMPTYSTRING);
	return((wParam == (WPARAM)-1) ? ShowHelp(szTopic) : Default());
}

void CMainWnd::OnNew()
{
	CHourglassCursor  cCursor;

	m_dlgNewDocuments.DoModal();
}

void CMainWnd::OnNewItemTMPacket()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_TMPACKET_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemTCFunction()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_TCFUNCTION_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemTCSequence()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateProceduresItem()) ? SYSTEM_WARNING_TCSEQUENCE_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemTCProcedure()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateProceduresItem()) ? SYSTEM_WARNING_TCPROCEDURE_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemTMParameter()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_TMPARAMETER_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemTCParameter()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_TCPARAMETER_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemOBProcessor()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_OBPROCESSOR_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemAND()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_AND_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemGRD()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_GRD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemMMD()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_MMD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemPOD()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_POD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnNewItemScript()
{
	CHourglassCursor  cCursor;

	ShowMessage((!CreateDatabaseItem()) ? SYSTEM_WARNING_AUTOMATIONSCRIPT_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemTMPacket()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_TMPACKET_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemTCFunction()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_TCFUNCTION_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemTCSequence()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenProceduresItem()) ? SYSTEM_WARNING_TCSEQUENCE_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemTCProcedure()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenProceduresItem()) ? SYSTEM_WARNING_TCPROCEDURE_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemTMParameter()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_TMPARAMETER_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemTCParameter()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_TCPARAMETER_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemOBProcessor()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_OBPROCESSOR_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemAND()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_AND_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemGRD()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_GRD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemMMD()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_MMD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemPOD()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_POD_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnOpenItemScript()
{
	CHourglassCursor  cCursor;

	ShowMessage((!OpenDatabaseItem()) ? SYSTEM_WARNING_AUTOMATIONSCRIPT_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMainWnd::OnRenameItemTMPacket()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemTCFunction()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemTCSequence()
{
	CHourglassCursor  cCursor;

	RenameProceduresItem();
}

void CMainWnd::OnRenameItemTCProcedure()
{
	CHourglassCursor  cCursor;

	RenameProceduresItem();
}

void CMainWnd::OnRenameItemTMParameter()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemTCParameter()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemOBProcessor()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemAND()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemGRD()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemMMD()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemPOD()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnRenameItemScript()
{
	CHourglassCursor  cCursor;

	RenameDatabaseItem();
}

void CMainWnd::OnDeleteItemTMPacket()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemTCFunction()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemTCSequence()
{
	CHourglassCursor  cCursor;

	DeleteProceduresItem();
}

void CMainWnd::OnDeleteItemTCProcedure()
{
	CHourglassCursor  cCursor;

	DeleteProceduresItem();
}

void CMainWnd::OnDeleteItemTMParameter()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemTCParameter()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemOBProcessor()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemAND()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemGRD()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemMMD()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemPOD()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnDeleteItemScript()
{
	CHourglassCursor  cCursor;

	DeleteDatabaseItem();
}

void CMainWnd::OnOpenTMPacket()
{
	CHourglassCursor  cCursor;

	m_dlgOpenTMPacket.DoModal();
}

void CMainWnd::OnImportTMPacket()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;
	CDatabaseTMPackets  pDatabaseTMPackets;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportTMPacket.DoModal(pDatabaseTMPackets) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTMPacketWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET) ? (CTMPacketWnd *)pDisplayWnd : (CTMPacketWnd *)NULL))
		{
			pTMPacketWnd->UpdateTables(pDatabaseTMPackets);
			continue;
		}
	}
}

void CMainWnd::OnExportTMPacket()
{
	CHourglassCursor  cCursor;

	m_dlgExportTMPacket.DoModal();
}

void CMainWnd::OnOpenTCFunction()
{
	CHourglassCursor  cCursor;

	m_dlgOpenTCFunction.DoModal();
}

void CMainWnd::OnImportTCFunction()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCFunctionWnd  *pTCFunctionWnd;
	CDatabaseTCFunctions  pDatabaseTCFunctions;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportTCFunction.DoModal(pDatabaseTCFunctions) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCFunctionWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION) ? (CTCFunctionWnd *)pDisplayWnd : (CTCFunctionWnd *)NULL))
		{
			pTCFunctionWnd->UpdateTables(pDatabaseTCFunctions);
			continue;
		}
	}
}

void CMainWnd::OnExportTCFunction()
{
	CHourglassCursor  cCursor;

	m_dlgExportTCFunction.DoModal();
}

void CMainWnd::OnOpenTCSequence()
{
	CHourglassCursor  cCursor;

	m_dlgOpenTCSequence.DoModal();
}

void CMainWnd::OnImportTCSequence()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CDatabaseTCSequences  pDatabaseTCSequences;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportTCSequence.DoModal(pDatabaseTCSequences) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCSequenceWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE) ? (CTCSequenceWnd *)pDisplayWnd : (CTCSequenceWnd *)NULL))
		{
			pTCSequenceWnd->UpdateTables(pDatabaseTCSequences);
			continue;
		}
	}
}

void CMainWnd::OnExportTCSequence()
{
	CHourglassCursor  cCursor;

	m_dlgExportTCSequence.DoModal();
}

void CMainWnd::OnOpenTCProcedure()
{
	CHourglassCursor  cCursor;

	m_dlgOpenTCProcedure.DoModal();
}

void CMainWnd::OnImportTCProcedure()
{
	CHourglassCursor  cCursor;

	m_dlgImportTCProcedure.DoModal();
}

void CMainWnd::OnExportTCProcedure()
{
	CHourglassCursor  cCursor;

	m_dlgExportTCProcedure.DoModal();
}

void CMainWnd::OnOpenTMParameter()
{
	CHourglassCursor  cCursor;

	m_dlgOpenTMParameter.DoModal();
}

void CMainWnd::OnImportTMParameter()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMParameterWnd  *pTMParameterWnd;
	CDatabaseTMParameters  pDatabaseTMParameters;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportTMParameter.DoModal(pDatabaseTMParameters) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTMParameterWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER) ? (CTMParameterWnd *)pDisplayWnd : (CTMParameterWnd *)NULL))
		{
			pTMParameterWnd->UpdateTables(pDatabaseTMParameters);
			continue;
		}
	}
}

void CMainWnd::OnExportTMParameter()
{
	CHourglassCursor  cCursor;

	m_dlgExportTMParameter.DoModal();
}

void CMainWnd::OnOpenTCParameter()
{
	CHourglassCursor  cCursor;

	m_dlgOpenTCParameter.DoModal();
}

void CMainWnd::OnImportTCParameter()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCParameterWnd  *pTCParameterWnd;
	CDatabaseTCParameters  pDatabaseTCParameters;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportTCParameter.DoModal(pDatabaseTCParameters) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pTCParameterWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER) ? (CTCParameterWnd *)pDisplayWnd : (CTCParameterWnd *)NULL))
		{
			pTCParameterWnd->UpdateTables(pDatabaseTCParameters);
			continue;
		}
	}
}

void CMainWnd::OnExportTCParameter()
{
	CHourglassCursor  cCursor;

	m_dlgExportTCParameter.DoModal();
}

void CMainWnd::OnOpenOBProcessor()
{
	CHourglassCursor  cCursor;

	m_dlgOpenOBProcessor.DoModal();
}

void CMainWnd::OnImportOBProcessor()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CDatabaseOBProcessors  pDatabaseOBProcessors;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportOBProcessor.DoModal(pDatabaseOBProcessors) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pOBProcessorWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR) ? (COBProcessorWnd *)pDisplayWnd : (COBProcessorWnd *)NULL))
		{
			pOBProcessorWnd->UpdateTables(pDatabaseOBProcessors);
			continue;
		}
	}
}

void CMainWnd::OnExportOBProcessor()
{
	CHourglassCursor  cCursor;

	m_dlgExportOBProcessor.DoModal();
}

void CMainWnd::OnCustomImportOBProcessor()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	INT  nProcessor;
	INT  nProcessors;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CDatabaseOBProcessor  *pDatabaseOBProcessor[2];
	CDatabaseOBProcessors  pDatabaseOBProcessors;
	CHourglassCursor  cCursor;

	for (pDatabaseOBProcessors.Copy(GetDatabase()->GetOBProcessors()); GetDatabase()->ImportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, TRUE); )
	{
		for (nProcessor = 0, nProcessors = (INT)GetDatabase()->GetOBProcessors()->GetSize(); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor[0] = GetDatabase()->GetOBProcessors()->GetAt(nProcessor)) != (CDatabaseOBProcessor *)NULL)
			{
				if ((pDatabaseOBProcessor[1] = pDatabaseOBProcessors.GetAt((nIndex = pDatabaseOBProcessors.Find(pDatabaseOBProcessor[0]->GetName())))))
				{
					if (pDatabaseOBProcessor[0]->Compare(pDatabaseOBProcessor[1]))
					{
						pDatabaseOBProcessors.RemoveAt(nIndex);
						delete pDatabaseOBProcessor[1];
					}
					continue;
				}
				if ((pDatabaseOBProcessor[1] = new CDatabaseOBProcessor))
				{
					if (pDatabaseOBProcessor[1]->Copy(pDatabaseOBProcessor[0]) && pDatabaseOBProcessors.Add(pDatabaseOBProcessor[1]) >= 0) continue;
					delete pDatabaseOBProcessor[1];
				}
			}
			szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTDATA_ERROR), (LPCTSTR)GetDatabase()->GetName());
			ShowMessage(szMessage);
			break;
		}
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pOBProcessorWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR) ? (COBProcessorWnd *)pDisplayWnd : (COBProcessorWnd *)NULL))
			{
				pOBProcessorWnd->UpdateTables(pDatabaseOBProcessors);
				continue;
			}
		}
		break;
	}
}

void CMainWnd::OnCustomExportOBProcessor()
{
	CHourglassCursor  cCursor;

	GetDatabase()->ExportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, TRUE);
}

void CMainWnd::OnCustomImportMemoryImage()
{
	INT  nIndex;
	INT  nCount;
	INT  nImage;
	INT  nImages;
	INT  nBlock;
	INT  nBlocks;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage[2];
	CDatabaseOBProcessorMemoryImages  pDatabaseOBProcessorMemoryImages;
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock[2];
	CHourglassCursor  cCursor;

	for (pDatabaseOBProcessorMemoryImages.Copy(GetDatabase()->GetOBProcessorMemoryImages()); GetDatabase()->ImportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, TRUE); )
	{
		for (nImage = 0, nImages = (INT)GetDatabase()->GetOBProcessorMemoryImages()->GetSize(); nImage < nImages; nImage++)
		{
			if ((pDatabaseOBProcessorMemoryImage[0] = GetDatabase()->GetOBProcessorMemoryImages()->GetAt(nImage)))
			{
				if ((pDatabaseOBProcessorMemoryImage[1] = pDatabaseOBProcessorMemoryImages.GetAt((nIndex = pDatabaseOBProcessorMemoryImages.Find(pDatabaseOBProcessorMemoryImage[0]->GetName())))))
				{
					if (pDatabaseOBProcessorMemoryImage[0]->Compare(pDatabaseOBProcessorMemoryImage[1]))
					{
						pDatabaseOBProcessorMemoryImages.RemoveAt(nIndex);
						delete pDatabaseOBProcessorMemoryImage[1];
					}
					continue;
				}
				if ((pDatabaseOBProcessorMemoryImage[1] = new CDatabaseOBProcessorMemoryImage))
				{
					if (pDatabaseOBProcessorMemoryImage[1]->Copy(pDatabaseOBProcessorMemoryImage[0]) && pDatabaseOBProcessorMemoryImages.Add(pDatabaseOBProcessorMemoryImage[1]) >= 0) continue;
					delete pDatabaseOBProcessorMemoryImage[1];
				}
			}
			szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTDATA_ERROR), (LPCTSTR)GetDatabase()->GetName());
			ShowMessage(szMessage);
			break;
		}
		for (nImage = 0, nImages = (INT)pDatabaseOBProcessorMemoryImages.GetSize(); nImage < nImages; nImage++)
		{
			if ((pDatabaseOBProcessorMemoryImage[0] = pDatabaseOBProcessorMemoryImages.GetAt(nImage)))
			{
				if ((pDatabaseOBProcessorMemoryImage[1] = GetDatabase()->GetOBProcessorMemoryImages()->GetAt(GetDatabase()->GetOBProcessorMemoryImages()->Find(pDatabaseOBProcessorMemoryImage[0]->GetName()))))
				{
					for (nBlock = 0, nBlocks = (INT)pDatabaseOBProcessorMemoryImage[0]->GetSize(); nBlock < nBlocks; nBlock++)
					{
						if ((pDatabaseOBProcessorMemoryImageBlock[0] = pDatabaseOBProcessorMemoryImage[0]->GetAt(nBlock)))
						{
							for (nIndex = pDatabaseOBProcessorMemoryImage[1]->Find(pDatabaseOBProcessorMemoryImageBlock[0]->GetVersion()), nCount = (INT)pDatabaseOBProcessorMemoryImage[1]->GetSize(); nIndex >= 0 && nIndex < nCount; nIndex++)
							{
								if ((pDatabaseOBProcessorMemoryImageBlock[1] = pDatabaseOBProcessorMemoryImage[1]->GetAt(nIndex)) && pDatabaseOBProcessorMemoryImageBlock[0]->GetVersion() == pDatabaseOBProcessorMemoryImageBlock[1]->GetVersion())
								{
									pDatabaseOBProcessorMemoryImage[1]->RemoveAt(nIndex);
									delete pDatabaseOBProcessorMemoryImageBlock[1];
									nIndex--;
									nCount--;
									continue;
								}
								break;
							}
						}
					}
					for (nBlock = 0; nBlock < nBlocks; nBlock++)
					{
						if ((pDatabaseOBProcessorMemoryImageBlock[1] = ((pDatabaseOBProcessorMemoryImageBlock[0] = pDatabaseOBProcessorMemoryImage[0]->GetAt(nBlock))) ? new CDatabaseOBProcessorMemoryImageBlock : (CDatabaseOBProcessorMemoryImageBlock *)NULL))
						{
							pDatabaseOBProcessorMemoryImageBlock[1]->Copy(pDatabaseOBProcessorMemoryImageBlock[0]);
							if (pDatabaseOBProcessorMemoryImage[1]->Add(pDatabaseOBProcessorMemoryImageBlock[1]) >= 0) continue;
							delete pDatabaseOBProcessorMemoryImageBlock[1];
						}
						if (szMessage.IsEmpty())
						{
							szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTDATA_ERROR), (LPCTSTR)GetDatabase()->GetName());
							ShowMessage(szMessage);
						}
						break;
					}
				}
			}
		}
		for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pOBProcessorWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR) ? (COBProcessorWnd *)pDisplayWnd : (COBProcessorWnd *)NULL))
			{
				for (nImage = 0, nImages = (INT)pDatabaseOBProcessorMemoryImages.GetSize(); nImage < nImages; nImage++)
				{
					if ((pDatabaseOBProcessorMemoryImage[0] = pDatabaseOBProcessorMemoryImages.GetAt(nImage)))
					{
						if ((pDatabaseOBProcessorMemoryImage[1] = GetDatabase()->GetOBProcessorMemoryImages()->GetAt(GetDatabase()->GetOBProcessorMemoryImages()->Find(pDatabaseOBProcessorMemoryImage[0]->GetName()))))
						{
							pOBProcessorWnd->UpdateTables(pDatabaseOBProcessorMemoryImage[1]);
							continue;
						}
					}
				}
			}
		}
		break;
	}
}

void CMainWnd::OnCustomExportMemoryImage()
{
	CHourglassCursor  cCursor;

	GetDatabase()->ExportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, TRUE);
}

void CMainWnd::OnOpenAND()
{
	CHourglassCursor  cCursor;

	m_dlgOpenAND.DoModal();
}

void CMainWnd::OnImportAND()
{
	INT  nDisplay;
	INT  nDisplays;
	CANDWnd  *pANDWnd;
	CPtrArray  pDisplays;
	CANDLayouts  pANDLayouts;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportAND.DoModal(pANDLayouts) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pANDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND) ? (CANDWnd *)pDisplayWnd : (CANDWnd *)NULL))
		{
			pANDWnd->UpdateTables(pANDLayouts);
			continue;
		}
	}
}

void CMainWnd::OnExportAND()
{
	CHourglassCursor  cCursor;

	m_dlgExportAND.DoModal();
}

void CMainWnd::OnOpenGRD()
{
	CHourglassCursor  cCursor;

	m_dlgOpenGRD.DoModal();
}

void CMainWnd::OnImportGRD()
{
	INT  nDisplay;
	INT  nDisplays;
	CGRDWnd  *pGRDWnd;
	CPtrArray  pDisplays;
	CGRDLayouts  pGRDLayouts;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportGRD.DoModal(pGRDLayouts) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pGRDWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD) ? (CGRDWnd *)pDisplayWnd : (CGRDWnd *)NULL))
		{
			pGRDWnd->UpdateTables(pGRDLayouts);
			continue;
		}
	}
}

void CMainWnd::OnExportGRD()
{
	CHourglassCursor  cCursor;

	m_dlgExportGRD.DoModal();
}

void CMainWnd::OnOpenMMD()
{
	CHourglassCursor  cCursor;

	m_dlgOpenMMD.DoModal();
}

void CMainWnd::OnImportMMD()
{
	CHourglassCursor  cCursor;

	m_dlgImportMMD.DoModal();
}

void CMainWnd::OnExportMMD()
{
	CHourglassCursor  cCursor;

	m_dlgExportMMD.DoModal();
}

void CMainWnd::OnOpenPOD()
{
	CHourglassCursor  cCursor;

	m_dlgOpenPOD.DoModal();
}

void CMainWnd::OnImportPOD()
{
	INT  nDisplay;
	INT  nDisplays;
	CPODWnd  *pPODWnd;
	CPtrArray  pDisplays;
	CPODLayouts  pPODLayouts;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgImportPOD.DoModal(pPODLayouts) == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pPODWnd = ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD) ? (CPODWnd *)pDisplayWnd : (CPODWnd *)NULL))
		{
			pPODWnd->UpdateTables(pPODLayouts);
			continue;
		}
	}
}

void CMainWnd::OnExportPOD()
{
	CHourglassCursor  cCursor;

	m_dlgExportPOD.DoModal();
}

void CMainWnd::OnOpenScript()
{
	CHourglassCursor  cCursor;

	m_dlgOpenScript.DoModal();
}

void CMainWnd::OnImportScript()
{
	CHourglassCursor  cCursor;

	m_dlgImportScript.DoModal();
}

void CMainWnd::OnExportScript()
{
	CHourglassCursor  cCursor;

	m_dlgExportScript.DoModal();
}

void CMainWnd::OnDatabaseNew()
{
	CStringArray  szDocuments;
	CHourglassCursor  cCursor;

	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE));
	m_dlgNewDocuments.DoModal(szDocuments);
}

void CMainWnd::OnDatabaseOpen()
{
	CHourglassCursor  cCursor;

	m_dlgDatabaseOpen.DoModal();
}

void CMainWnd::OnDocumentNew()
{
	CStringArray  szDocuments;
	CHourglassCursor  cCursor;

	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TMPACKET));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCFUNCTION));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCSEQUENCE));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCPROCEDURE));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TMPARAMETER));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCPARAMETER));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_OBPROCESSOR));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_ALPHANUMERICDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_GRAPHICDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_MIMICSDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_PARAMETEROBSERVATIONDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_AUTOMATIONSCRIPT));
	m_dlgNewDocuments.DoModal(szDocuments);
}

void CMainWnd::OnDatabaseImport()
{
	CHourglassCursor  cCursor;

	m_dlgDatabaseImport.DoModal();
}

void CMainWnd::OnDatabaseExport()
{
	CHourglassCursor  cCursor;

	m_dlgDatabaseExport.DoModal();
}

void CMainWnd::OnDatabaseDelete()
{
	CHourglassCursor  cCursor;

	m_dlgDatabaseDelete.DoModal();
}

void CMainWnd::OnDatabaseVersioning()
{
	CHourglassCursor  cCursor;

	m_dlgDatabaseVersioning.DoModal();
}

void CMainWnd::OnDocumentOpen()
{
	CHourglassCursor  cCursor;

	m_dlgOpenDocuments.DoModal();
}

void CMainWnd::OnDocumentSave()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoSave();
	}
}

void CMainWnd::OnDocumentSaveAs()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoSaveAs();
	}
}

void CMainWnd::OnDocumentSaveAll()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->CanSave())
		{
			pDisplayWnd->DoSave();
			continue;
		}
	}
}

void CMainWnd::OnDocumentCheck()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoCheck();
	}
}

void CMainWnd::OnDocumentDelete()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoDelete();
	}
}

void CMainWnd::OnDocumentClose()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoClose();
		pDisplayWnd->DestroyWindow();
	}
}

void CMainWnd::OnPrintSetup()
{
	CHourglassCursor  cCursor;

	m_dlgPrintPageSetup.DoModal();
}

void CMainWnd::OnPrint()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_TMPACKET_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_TCFUNCTION_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_TCSEQUENCE_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAY_PRINTTYPE_IMAGE)) ? SYSTEM_WARNING_TCPROCEDURE_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_TMPARAMETER_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_TCPARAMETER_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_OBPROCESSOR_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_AND_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_GRD_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAY_PRINTTYPE_IMAGE)) ? SYSTEM_WARNING_MMD_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE)) ? SYSTEM_WARNING_POD_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAY_PRINTTYPE_IMAGE)) ? SYSTEM_WARNING_AUTOMATIONSCRIPT_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
}

void CMainWnd::OnPrintSourceCode()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAY_PRINTTYPE_CODE)) ? SYSTEM_WARNING_TCPROCEDURE_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAY_PRINTTYPE_CODE)) ? SYSTEM_WARNING_MMD_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAY_PRINTTYPE_CODE)) ? SYSTEM_WARNING_AUTOMATIONSCRIPT_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
}

void CMainWnd::OnPrintAllItems()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_TMPACKET_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_TCFUNCTION_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_TCSEQUENCE_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_TMPARAMETER_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_TCPARAMETER_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_OBPROCESSOR_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_AND_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_GRD_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  m_dlgPrintPagePrepare.DoModal() == IDOK)
	{
		for (ShowPrintStatus(TRUE); ShowMessage((!pDisplayWnd->Print(&m_dlgPrintPagePrepare.m_pd, DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL)) ? SYSTEM_WARNING_POD_PRINT_FAILURE : SYSTEM_NOERROR) >= 0; )
		{
			ShowPrintStatus(FALSE);
			break;
		}
		return;
	}
}

void CMainWnd::OnEditUndo()
{
	CHourglassCursor  cCursor;

	DoUndo();
}

void CMainWnd::OnEditRedo()
{
	CHourglassCursor  cCursor;

	DoRedo();
}

void CMainWnd::OnEditFind()
{
	CHourglassCursor  cCursor;

	DoFind();
}

void CMainWnd::OnEditFindSearchForward()
{
	m_wndRibbonBar.SetFindDefaults(TRUE, FALSE, FALSE, FALSE, TRUE);
}

void CMainWnd::OnEditFindSearchAll()
{
	m_wndRibbonBar.SetFindDefaults(FALSE, TRUE, FALSE, FALSE, TRUE);
}

void CMainWnd::OnEditFindMatchCase()
{
	m_wndRibbonBar.SetFindDefaults(FALSE, FALSE, TRUE, FALSE, TRUE);
}

void CMainWnd::OnEditFindMatchWord()
{
	m_wndRibbonBar.SetFindDefaults(FALSE, FALSE, FALSE, TRUE, TRUE);
}

void CMainWnd::OnEditFindNext()
{
	CHourglassCursor  cCursor;

	DoFindNext();
}

void CMainWnd::OnEditFindPrevious()
{
	CHourglassCursor  cCursor;

	DoFindPrevious();
}

void CMainWnd::OnEditReplace()
{
	CHourglassCursor  cCursor;

	DoReplace();
}

void CMainWnd::OnEditGoTo()
{
	CHourglassCursor  cCursor;

	DoGoTo();
}

void CMainWnd::OnEditCut()
{
	CHourglassCursor  cCursor;

	DoCutSel();
}

void CMainWnd::OnEditCopy()
{
	CHourglassCursor  cCursor;

	DoCopySel();
}

void CMainWnd::OnEditPaste()
{
	CHourglassCursor  cCursor;

	DoPasteSel();
}

void CMainWnd::OnEditDelete()
{
	CHourglassCursor  cCursor;

	DoDeleteSel();
}

void CMainWnd::OnEditSelectAll()
{
	CHourglassCursor  cCursor;

	DoSelectAll();
}

void CMainWnd::OnEditSaveTable()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoSaveTable();
	}
}

void CMainWnd::OnEditCheckTable()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoCheckTable();
	}
}

void CMainWnd::OnEditDeleteTable()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoDeleteTable();
	}
}

void CMainWnd::OnEditImportTables()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoImportTables();
	}
}

void CMainWnd::OnEditExportTables()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoExportTables();
	}
}

void CMainWnd::OnEditPrintTable()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (!pDisplayWnd->DoPrintTable()) ShowMessage(STRING(IDS_PRINTJOB_MESSAGE_FAILURE));
	}
}

void CMainWnd::OnEditPrintAllTables()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (!pDisplayWnd->DoPrintAllTables()) ShowMessage(STRING(IDS_PRINTJOB_MESSAGE_FAILURE));
	}
}

void CMainWnd::OnEditInsertTableRowAbove()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoInsertTableRowAbove();
	}
}

void CMainWnd::OnEditInsertTableRowBelow()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoInsertTableRowBelow();
	}
}

void CMainWnd::OnEditInsertTableColumnBefore()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoInsertTableColumnBefore();
	}
}

void CMainWnd::OnEditInsertTableColumnAfter()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoInsertTableColumnAfter();
	}
}

void CMainWnd::OnEditClearTableRow()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoClearTableRow();
	}
}

void CMainWnd::OnEditDeleteTableRow()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoDeleteTableRow();
	}
}

void CMainWnd::OnEditDeleteTableColumn()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoDeleteTableColumn();
	}
}

void CMainWnd::OnEditCopyTableRow()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoCopyTableRow();
	}
}

void CMainWnd::OnEditPasteTableRow()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoPasteTableRow();
	}
}

void CMainWnd::OnEditDiscardAllTables()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoDiscardAllTables();
	}
}

void CMainWnd::OnEditDiscardTables()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoDiscardTables();
	}
}

void CMainWnd::OnEditResetTables()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoResetTables();
	}
}

void CMainWnd::OnEditCreateMimicsGroup()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		m_dlgCreateMimicsGroup.Create(pMMDWnd);
	}
}

void CMainWnd::OnEditDeleteMimicsGroup()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		m_dlgDeleteMimicsGroup.Create(pMMDWnd);
	}
}

void CMainWnd::OnEditCollectMimicsGroup()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->CollectMimicsGroup();
	}
}

void CMainWnd::OnEditDiscardMimicsGroup()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DiscardMimicsGroup();
	}
}

void CMainWnd::OnEditStepIntoMimicsGroup()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->StepIntoMimicsGroup();
	}
}

void CMainWnd::OnEditStepOutMimicsGroup()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->StepOutMimicsGroup();
	}
}

void CMainWnd::OnEditImportMimicsGroup()
{
	CHourglassCursor  cCursor;

	m_dlgImportMimicsGroup.DoModal();
}

void CMainWnd::OnEditExportMimicsGroup()
{
	CHourglassCursor  cCursor;

	m_dlgExportMimicsGroup.DoModal();
}

void CMainWnd::OnEditHorzAlignMimicsObjects()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoHorzAlignMimicsCtrls();
	}
}

void CMainWnd::OnEditVertAlignMimicsObjects()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoVertAlignMimicsCtrls();
	}
}

void CMainWnd::OnEditMoveMimicsObjectToTop()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoMoveMimicsCtrlToTop();
	}
}

void CMainWnd::OnEditMoveMimicsObjectToBottom()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoMoveMimicsCtrlToBottom();
	}
}

void CMainWnd::OnEditMoveMimicsObjectUp()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoMoveMimicsCtrlUp();
	}
}

void CMainWnd::OnEditMoveMimicsObjectDown()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoMoveMimicsCtrlDown();
	}
}

void CMainWnd::OnEditShowHideMimicsObject()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoShowHideMimicsCtrl();
	}
}

void CMainWnd::OnEditHorzFlipMimicsObject()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoHorzFlipMimicsCtrl();
	}
}

void CMainWnd::OnEditVertFlipMimicsObject()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->DoVertFlipMimicsCtrl();
	}
}

void CMainWnd::OnEditRotateMimicsObject()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		m_dlgRotateMimicsObject.Create(pMMDWnd);
	}
}

void CMainWnd::OnEditTurnMimicsObject()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->SetMimicsCtrlRotateMode(!pMMDWnd->GetMimicsCtrlRotateMode());
	}
}

void CMainWnd::OnViewMimicsObjectProperties()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->ShowMimicsCtrlProperties();
	}
}

void CMainWnd::OnViewMimicsObjectItem()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->ShowMimicsCtrlItem();
	}
}

void CMainWnd::OnViewMimicsObjectCode()
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->ShowMimicsCtrlCode();
	}
}

void CMainWnd::OnProperties()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->UpdateProperties();
	}
}

void CMainWnd::OnSourceCode()
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_MMD)
		{
			if ((pMMDWnd = (CMMDWnd *)pDisplayWnd)->HasMimicsCtrlCode())
			{
				pMMDWnd->ShowMimicsCtrlCode();
			}
		}
	}
}

void CMainWnd::OnLinkInformation()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->UpdateLinkInformation();
	}
}

void CMainWnd::OnWorkspaceWindow()
{
	CWorkspaceWnd  *pWorkspaceWnd;

	if ((pWorkspaceWnd = GetWorkspaceWindow()))
	{
		if (pWorkspaceWnd->IsVisible())
		{
			pWorkspaceWnd->Hide();
			return;
		}
		pWorkspaceWnd->Show();
	}
}

void CMainWnd::OnOutputWindow()
{
	COutputWnd  *pOutputWnd;

	if ((pOutputWnd = GetOutputWindow()))
	{
		if (pOutputWnd->IsVisible())
		{
			pOutputWnd->Hide();
			return;
		}
		pOutputWnd->Show();
	}
}

void CMainWnd::OnZoomWindow()
{
	CRect  rArea[2];
	CRect  rZoomWnd[2];
	CZoomWnd  *pZoomWnd;

	if ((pZoomWnd = GetZoomWindow()))
	{
		for (GetWindowRect(rArea[0]), ClientToScreen((rArea[1] = CalcClientRect())), rArea[0].InflateRect(-GetSystemMetrics(SM_CXFRAME), -GetSystemMetrics(SM_CYFRAME)), pZoomWnd->GetWindowRect(rZoomWnd[0]); !pZoomWnd->IsWindowVisible() && !rZoomWnd[1].IntersectRect(rArea[0], rZoomWnd[0]); )
		{
			rZoomWnd[1].SetRect(rArea[1].right - ZOOMWINDOW_SIZE_WIDTH, rArea[1].bottom - ZOOMWINDOW_SIZE_HEIGHT, rArea[1].right, rArea[1].bottom);
			rZoomWnd[1].OffsetRect(-GetSystemMetrics(SM_CXFRAME), -GetSystemMetrics(SM_CYFRAME));
			pZoomWnd->MoveWindow(rZoomWnd[1]);
			break;
		}
		pZoomWnd->ShowWindow((!pZoomWnd->IsWindowVisible()) ? SW_SHOWNA : SW_HIDE);
	}
}

void CMainWnd::OnMimicsObjectsToolBar()
{
	m_wndMimicsObjectsToolBar.ShowPane(!m_wndMimicsObjectsToolBar.IsVisible(), FALSE, FALSE);
}

void CMainWnd::OnMimicsObjects(UINT nID)
{
	CMMDWnd  *pMMDWnd;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		pMMDWnd->SetSelectedMimicsCtrlID((nID != pMMDWnd->GetSelectedMimicsCtrlID()) ? nID : -1);
	}
}

void CMainWnd::OnMimicsGroup()
{
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	if ((pMMDWnd = (CMMDWnd *)MDIGetActive()))
	{
		if (m_dlgInsertMimicsGroup.Create(pMMDWnd) == IDOK)
		{
			pMMDWnd->GetImageView()->SetFocus();
		}
	}
}

void CMainWnd::OnTCStepsToolBar()
{
	m_wndTCStepsToolBar.ShowPane(!m_wndTCStepsToolBar.IsVisible(), FALSE, FALSE);
}

void CMainWnd::OnTCSteps(UINT nID)
{
	CTCProcedureWnd  *pTCProcedureWnd;

	if ((pTCProcedureWnd = (CTCProcedureWnd *)MDIGetActive()))
	{
		pTCProcedureWnd->SetSelectedTCStepID((nID != pTCProcedureWnd->GetSelectedTCStepID()) ? nID : -1);
	}
}

void CMainWnd::OnBuildOptions()
{
	CHourglassCursor  cCursor;

	m_dlgCompileOptions.DoModal();
}

void CMainWnd::OnBuildDirectives()
{
	CHourglassCursor  cCursor;

	m_dlgCompileDirectives.DoModal();
}

void CMainWnd::OnBuildDownload()
{
	return;
}

void CMainWnd::OnBuildCompile()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoCompile();
	}
}

void CMainWnd::OnBuildCompileAll()
{
	CHourglassCursor  cCursor;

	GetDatabase()->StartCompiling();
}

void CMainWnd::OnBuildCompileBatches()
{
	CHourglassCursor  cCursor;

	m_dlgCompileBatches.DoModal();
}

void CMainWnd::OnBuildCompileStop()
{
	CHourglassCursor  cCursor;

	if (CMMDWnd::IsCompilingMMD())
	{
		CMMDWnd::StopCompilingMMD();
		return;
	}
	if (CScriptWnd::IsCompilingScript())
	{
		CScriptWnd::StopCompilingScript();
		return;
	}
	if (CTCProcedureWnd::IsCompilingProcedure())
	{
		CTCProcedureWnd::StopCompilingProcedure();
		return;
	}
	if (GetDatabase()->IsCompiling())
	{
		GetDatabase()->StopCompiling();
		return;
	}
}

void CMainWnd::OnBuildClean()
{
	CHourglassCursor  cCursor;

	DoCleanDatabaseFiles();
}

void CMainWnd::OnBuildTest()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (!pDisplayWnd->IsTesting())
		{
			pDisplayWnd->DoTest();
			return;
		}
		pDisplayWnd->DoTestContinue();
	}
}

void CMainWnd::OnBuildTestBreak()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoTestBreak();
	}
}

void CMainWnd::OnBuildTestContinue()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoTestContinue();
	}
}

void CMainWnd::OnBuildTestStepInto()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoTestStepInto();
	}
}

void CMainWnd::OnBuildTestStepOver()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoTestStepOver();
	}
}

void CMainWnd::OnBuildTestStepOut()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoTestStepOut();
	}
}

void CMainWnd::OnBuildTestStop()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoTestStop();
	}
}

void CMainWnd::OnBuildTestReset()
{
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		pDisplayWnd->DoTestReset();
	}
}

void CMainWnd::OnToolsOptions()
{
	CHourglassCursor  cCursor;

	m_dlgToolsOptions.DoModal();
}

void CMainWnd::OnUsers()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgDatabaseUsers.DoModal() == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)))
		{
			pDisplayWnd->AdjustToPrivileges();
			continue;
		}
	}
}

void CMainWnd::OnPrivileges()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (m_dlgDatabasePrivileges.DoModal() == IDOK) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)))
		{
			pDisplayWnd->AdjustToPrivileges();
			continue;
		}
	}
}

void CMainWnd::OnValidity()
{
	CHourglassCursor  cCursor;

	m_dlgDatabaseValidity.DoModal();
}

void CMainWnd::OnNextWindow()
{
	ActivateWindow(TRUE);
}

void CMainWnd::OnPreviousWindow()
{
	ActivateWindow(FALSE);
}

void CMainWnd::OnCloseWindow()
{
	CloseWindow();
}

void CMainWnd::OnCloseAllWindows()
{
	CloseAllWindows();
}

void CMainWnd::OnWindows()
{
	CHourglassCursor  cCursor;

	m_dlgDisplayWindows.DoModal();
}

void CMainWnd::OnAssistantSupportDateConversions()
{
	CAssistantSupportDateConversionsDialog  cDateConversionDialog(this);

	cDateConversionDialog.DoModal();
}

void CMainWnd::OnAssistantListen()
{
}

void CMainWnd::OnMRUDocument(UINT nID)
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CString  szTitle;
	CString  szMessage;
	CANDWnd  *pANDWnd;
	CGRDWnd  *pGRDWnd;
	CMMDWnd  *pMMDWnd;
	CPODWnd  *pPODWnd;
	ULONGLONG  nComponent;
	CPtrArray  pDisplays;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;
	CTCFunctionWnd  *pTCFunctionWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CTCProcedureWnd  *pTCProcedureWnd;
	CTMParameterWnd  *pTMParameterWnd;
	CTCParameterWnd  *pTCParameterWnd;
	COBProcessorWnd  *pOBProcessorWnd;
	CRecentDocumentInfo  *pRecentDocument;
	CHourglassCursor  cCursor;

	if ((pRecentDocument = m_pRecentDocuments.GetAt(nID - IDM_FIRSTMRUDOCUMENT)) && pRecentDocument->GetDocument(szName, szTitle, nComponent))
	{
		switch (LOWORD(nComponent))
		{
		case DISPLAY_TYPE_TMPACKET:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET)
			{
				if ((pTMPacketWnd = (CTMPacketWnd *)pDisplayWnd)->GetName() == szName)
				{
					pTMPacketWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pTMPacketWnd = new CTMPacketWnd(szName)); )
			{
				if (pTMPacketWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_TMPACKET_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_TCFUNCTION:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION)
			{
				if ((pTCFunctionWnd = (CTCFunctionWnd *)pDisplayWnd)->GetName() == szName)
				{
					pTCFunctionWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pTCFunctionWnd = new CTCFunctionWnd(szName)); )
			{
				if (pTCFunctionWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_TCSEQUENCE:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE)
			{
				if ((pTCSequenceWnd = (CTCSequenceWnd *)pDisplayWnd)->GetName() == szName)
				{
					pTCSequenceWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pTCSequenceWnd = new CTCSequenceWnd(szName)); )
			{
				if (pTCSequenceWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_TCPROCEDURE:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE)
			{
				if ((pTCProcedureWnd = (CTCProcedureWnd *)pDisplayWnd)->GetName() == szName)
				{
					pTCProcedureWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pTCProcedureWnd = new CTCProcedureWnd(szName)); )
			{
				if (pTCProcedureWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_TCPROCEDURE_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_TMPARAMETER:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER)
			{
				if ((pTMParameterWnd = (CTMParameterWnd *)pDisplayWnd)->GetName() == szName)
				{
					pTMParameterWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pTMParameterWnd = new CTMParameterWnd(szName)); )
			{
				if (pTMParameterWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_TCPARAMETER:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER)
			{
				if ((pTCParameterWnd = (CTCParameterWnd *)pDisplayWnd)->GetName() == szName)
				{
					pTCParameterWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pTCParameterWnd = new CTCParameterWnd(szName)); )
			{
				if (pTCParameterWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_OBPROCESSOR:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR)
			{
				if ((pOBProcessorWnd = (COBProcessorWnd *)pDisplayWnd)->GetName() == szName)
				{
					pOBProcessorWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pOBProcessorWnd = new COBProcessorWnd(szName)); )
			{
				if (pOBProcessorWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_AND:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND)
			{
				if (_ttoi((pANDWnd = (CANDWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
				{
					pANDWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pANDWnd = new CANDWnd(szName)); )
			{
				if (pANDWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_AND_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_GRD:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD)
			{
				if (_ttoi((pGRDWnd = (CGRDWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
				{
					pGRDWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pGRDWnd = new CGRDWnd(szName)); )
			{
				if (pGRDWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_GRD_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_MMD:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD)
			{
				if (_ttoi((pMMDWnd = (CMMDWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
				{
					pMMDWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pMMDWnd = new CMMDWnd(szName)); )
			{
				if (pMMDWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_MMD_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_POD:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD)
			{
				if (_ttoi((pPODWnd = (CPODWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
				{
					pPODWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pPODWnd = new CPODWnd(szName)); )
			{
				if (pPODWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_POD_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		case DISPLAY_TYPE_SCRIPT:
		{ for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT)
			{
				if (_ttoi((pScriptWnd = (CScriptWnd *)pDisplayWnd)->GetName()) == _ttoi(szName))
				{
					pScriptWnd->MDIActivate();
					return;
				}
			}
		}
		if (nDisplay == nDisplays)
		{
			for (; (pScriptWnd = new CScriptWnd(szName)); )
			{
				if (pScriptWnd->Create(GetMainWnd())) return;
				break;
			}
			szMessage.Format(STRING(IDS_SCRIPT_FAILURE_LOAD), (LPCTSTR)szName);
			ShowMessage(szMessage);
		}
		break;
		}
		}
	}
	if (nID - IDM_FIRSTMRUDOCUMENT < (UINT)m_pRecentDocuments.GetSize())
	{
		if ((pRecentDocument = m_pRecentDocuments.GetAt(nID - IDM_FIRSTMRUDOCUMENT))) delete pRecentDocument;
		m_pRecentDocuments.RemoveAt(nID - IDM_FIRSTMRUDOCUMENT);
		UpdateMRUMenus();
	}
}

void CMainWnd::OnMRUDatabase(UINT nID)
{
	CRecentDatabaseInfo  *pRecentDatabase;
	CHourglassCursor  cCursor;

	if ((pRecentDatabase = m_pRecentDatabases.GetAt(nID - IDM_FIRSTMRUDATABASE)))
	{
		if (pRecentDatabase->GetName() != GetDatabase()->GetName() || pRecentDatabase->GetSpacecraft() != GetDatabase()->GetSpacecraft() || pRecentDatabase->GetServer() != GetDatabase()->GetServer())
		{
			if (!SetDatabase(pRecentDatabase->GetServer(), pRecentDatabase->GetSpacecraft(), pRecentDatabase->GetName()))
			{
				if (nID - IDM_FIRSTMRUDATABASE < (UINT)m_pRecentDatabases.GetSize())
				{
					delete m_pRecentDatabases.GetAt(nID - IDM_FIRSTMRUDATABASE);
					m_pRecentDatabases.RemoveAt(nID - IDM_FIRSTMRUDATABASE);
					UpdateMRUMenus();
				}
			}
			return;
		}
		if (pRecentDatabase->GetName() == GetDatabase()->GetName() && pRecentDatabase->GetSpacecraft() == GetDatabase()->GetSpacecraft() && pRecentDatabase->GetServer() == GetDatabase()->GetServer()) return;
	}
	if (nID - IDM_FIRSTMRUDATABASE < (UINT)m_pRecentDatabases.GetSize())
	{
		if ((pRecentDatabase = m_pRecentDatabases.GetAt(nID - IDM_FIRSTMRUDATABASE))) delete pRecentDatabase;
		m_pRecentDatabases.RemoveAt(nID - IDM_FIRSTMRUDATABASE);
		UpdateMRUMenus();
	}
}

void CMainWnd::OnAbout()
{
	CHourglassCursor  cCursor;

	m_dlgAbout.DoModal();
}

void CMainWnd::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowHelp();
}

void CMainWnd::OnClose()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), CTCProcedureWnd::Clean(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)))
		{
			pDisplayWnd->DoClose();
			continue;
		}
	}
	for (SaveEnvironment(), SaveProfiles(), SaveToolWindows(), StopAssistant(), ShowWindow(SW_HIDE), ShowOwnedPopups(FALSE), SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE), nDisplay = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)))
		{
			pDisplayWnd->DestroyWindow();
			continue;
		}
	}
	GetDatabase()->Close();
	CLocaleMDIFrameWnd::OnClose();
}

void CMainWnd::OnDestroy()
{
	WINDOWPLACEMENT  wndPlacement;
	CProfile  cProfile;

	for (ZeroMemory(&wndPlacement, sizeof(WINDOWPLACEMENT)), wndPlacement.length = sizeof(WINDOWPLACEMENT); GetWindowPlacement(&wndPlacement); )
	{
		cProfile.SetPosition(&wndPlacement.rcNormalPosition);
		cProfile.SetState(wndPlacement.showCmd);
		break;
	}
	CLocaleMDIFrameWnd::OnDestroy();
}

void CMainWnd::OnUpdateNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!GetDatabase()->IsValid() || !IsCompiling());
	pCmdUI->SetCheck(IsWindow(m_dlgNewDocuments.GetSafeHwnd()));
}

void CMainWnd::OnUpdateNewItemTMPacket(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemTCFunction(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemTCSequence(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemTCProcedure(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemTMParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemTCParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemPOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_POD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateNewItemScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateOpenItemTMPacket(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemTCFunction(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemTCSequence(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemTCProcedure(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemTMParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemTCParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemPOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenItemScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateRenameItemTMPacket(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemTCFunction(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemTCSequence(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemTCProcedure(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemTMParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemTCParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemPOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_POD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateRenameItemScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemTMPacket(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemTCFunction(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemTCSequence(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemTCProcedure(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemTMParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemTCParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemPOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_POD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateDeleteItemScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateExport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateOpenTMPacket(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_TMPACKET));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenTMPacket.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportTMPacket(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TMPACKET) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportTMPacket.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportTMPacket(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TMPACKET) && HasDatabaseItem(DATABASE_COMPONENT_TMPACKET));
	pCmdUI->SetCheck(IsWindow(m_dlgExportTMPacket.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenTCFunction(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_TCFUNCTION));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenTCFunction.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportTCFunction(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCFUNCTION) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportTCFunction.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportTCFunction(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCFUNCTION) && HasDatabaseItem(DATABASE_COMPONENT_TCFUNCTION));
	pCmdUI->SetCheck(IsWindow(m_dlgExportTCFunction.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenTCSequence(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_TCSEQUENCE));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenTCSequence.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportTCSequence(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportTCSequence.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportTCSequence(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE) && HasDatabaseItem(DATABASE_COMPONENT_TCSEQUENCE));
	pCmdUI->SetCheck(IsWindow(m_dlgExportTCSequence.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenTCProcedure(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_TCPROCEDURE));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenTCProcedure.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportTCProcedure(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportTCProcedure.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportTCProcedure(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_TCPROCEDURE));
	pCmdUI->SetCheck(IsWindow(m_dlgExportTCProcedure.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenTMParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_TMPARAMETER));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenTMParameter.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportTMParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TMPARAMETER) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportTMParameter.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportTMParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TMPARAMETER) && HasDatabaseItem(DATABASE_COMPONENT_TMPARAMETER));
	pCmdUI->SetCheck(IsWindow(m_dlgExportTMParameter.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenTCParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_TCPARAMETER));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenTCParameter.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportTCParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCPARAMETER) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportTCParameter.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportTCParameter(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCPARAMETER) && HasDatabaseItem(DATABASE_COMPONENT_TCPARAMETER));
	pCmdUI->SetCheck(IsWindow(m_dlgExportTCParameter.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_OBPROCESSOR));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenOBProcessor.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_OBPROCESSOR) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportOBProcessor.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_OBPROCESSOR) && HasDatabaseItem(DATABASE_COMPONENT_OBPROCESSOR));
	pCmdUI->SetCheck(IsWindow(m_dlgExportOBProcessor.GetSafeHwnd()));
}

void CMainWnd::OnUpdateCustomImportOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_OBPROCESSOR) && GetDatabase()->CanImportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, TRUE) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateCustomExportOBProcessor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_OBPROCESSOR) && GetDatabase()->CanExportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, TRUE) && HasDatabaseItem(DATABASE_COMPONENT_OBPROCESSOR));
}

void CMainWnd::OnUpdateCustomImportMemoryImage(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_OBPROCESSOR) && GetDatabase()->CanImportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, TRUE) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateCustomExportMemoryImage(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_OBPROCESSOR) && GetDatabase()->CanExportTables((CDatabaseTableView *)NULL, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, TRUE) && HasDatabaseItem(DATABASE_COMPONENT_OBPROCESSOR));
}

void CMainWnd::OnUpdateOpenAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_AND));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenAND.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportAND.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportAND(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND) && HasDatabaseItem(DATABASE_COMPONENT_AND));
	pCmdUI->SetCheck(IsWindow(m_dlgExportAND.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_GRD));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenGRD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportGRD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportGRD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD) && HasDatabaseItem(DATABASE_COMPONENT_GRD));
	pCmdUI->SetCheck(IsWindow(m_dlgExportGRD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_MMD));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenMMD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportMMD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportMMD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_MMD));
	pCmdUI->SetCheck(IsWindow(m_dlgExportMMD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenPOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_POD));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenPOD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportPOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD) && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_POD_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportPOD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportPOD(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_POD) && HasDatabaseItem(DATABASE_COMPONENT_POD));
	pCmdUI->SetCheck(IsWindow(m_dlgExportPOD.GetSafeHwnd()));
}

void CMainWnd::OnUpdateOpenScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_SCRIPT));
	pCmdUI->SetCheck(IsWindow(m_dlgOpenScript.GetSafeHwnd()));
}

void CMainWnd::OnUpdateImportScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportScript.GetSafeHwnd()));
}

void CMainWnd::OnUpdateExportScript(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && HasDatabaseItem(DATABASE_COMPONENT_SCRIPT));
	pCmdUI->SetCheck(IsWindow(m_dlgExportScript.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDatabaseNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((!GetDatabase()->IsValid() || !IsCompiling()) ? (CheckAccountPrivilege(PRIVILEGE_DATABASE_CREATE) || CheckAccountPrivilege(PRIVILEGE_DATABASE_REMOTECREATE)) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgNewDocuments.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDatabaseOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((!GetDatabase()->IsValid() || !IsCompiling()));
	pCmdUI->SetCheck(IsWindow(m_dlgDatabaseOpen.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDatabaseImport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((!GetDatabase()->IsValid() || !IsCompiling()) ? CheckAccountPrivilege(PRIVILEGE_DATABASE_CREATE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgDatabaseImport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDatabaseExport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && !IsCompiling());
	pCmdUI->SetCheck(IsWindow(m_dlgDatabaseExport.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDatabaseDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((!IsCompiling()) ? (CheckAccountPrivilege(PRIVILEGE_DATABASE_DELETE) || CheckAccountPrivilege(PRIVILEGE_DATABASE_REMOTEDELETE)) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgDatabaseDelete.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDatabaseVersioning(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsVersioningSupported() && !IsCompiling());
	pCmdUI->SetCheck(IsWindow(m_dlgDatabaseVersioning.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDocumentNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!GetDatabase()->IsValid() || !IsCompiling());
	pCmdUI->SetCheck(IsWindow(m_dlgNewDocuments.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDocumentOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_dlgOpenDocuments.GetSafeHwnd()));
}

void CMainWnd::OnUpdateDocumentSave(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling() && pDisplayWnd->CanSave() && !pDisplayWnd->IsNew()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateDocumentSaveAs(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling() && pDisplayWnd->CanSaveAs()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateDocumentSaveAll(CCmdUI *pCmdUI)
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = (GetDatabase()->IsValid() && !IsCompiling()) ? EnumDisplayWindows(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->CanSave() && !pDisplayWnd->IsNew()) break;
		continue;
	}
	pCmdUI->Enable((nDisplay < nDisplay) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateDocumentCheck(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling() && pDisplayWnd->CanCheck()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateDocumentDelete(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling() && pDisplayWnd->CanDelete()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateDocumentClose(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdatePrintSetup(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsDefaultPrinterAvailable());
}

void CMainWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE  &&  pDisplayWnd->CanPrint(DISPLAY_PRINTTYPE_IMAGE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_MMD  &&  pDisplayWnd->CanPrint(DISPLAY_PRINTTYPE_IMAGE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT  &&  pDisplayWnd->CanPrint(DISPLAY_PRINTTYPE_IMAGE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
	}
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdatePrintSourceCode(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE  &&  pDisplayWnd->CanPrint(DISPLAY_PRINTTYPE_CODE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_MMD  &&  pDisplayWnd->CanPrint(DISPLAY_PRINTTYPE_CODE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT  &&  pDisplayWnd->CanPrint(DISPLAY_PRINTTYPE_CODE))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
	}
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdatePrintAllItems(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()))
	{
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_AND  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_GRD  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
		if (pDisplayWnd->GetType() == DISPLAY_TYPE_POD  &&  pDisplayWnd->CanPrint(DISPLAYTABLEVIEW_PRINT_TABLE | DISPLAYTABLEVIEW_PRINT_ALL))
		{
			pCmdUI->Enable(GetDatabase()->IsValid() && IsDefaultPrinterAvailable());
			return;
		}
	}
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateMRUDocuments(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateMRUDatabases(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
}

void CMainWnd::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanUndo());
}

void CMainWnd::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanRedo());
}

void CMainWnd::OnUpdateEditFind(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanFind());
}

void CMainWnd::OnUpdateEditFindSearchForward(CCmdUI *pCmdUI)
{
	BOOL  bFindDefaults[4];

	m_wndRibbonBar.GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]);
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(bFindDefaults[0]);
}

void CMainWnd::OnUpdateEditFindSearchAll(CCmdUI *pCmdUI)
{
	BOOL  bFindDefaults[4];

	m_wndRibbonBar.GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]);
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(bFindDefaults[1]);
}

void CMainWnd::OnUpdateEditFindMatchCase(CCmdUI *pCmdUI)
{
	BOOL  bFindDefaults[4];

	m_wndRibbonBar.GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]);
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(bFindDefaults[2]);
}

void CMainWnd::OnUpdateEditFindMatchWord(CCmdUI *pCmdUI)
{
	BOOL  bFindDefaults[4];

	m_wndRibbonBar.GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]);
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(bFindDefaults[3]);
}

void CMainWnd::OnUpdateEditFindNext(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && CanFindNext()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditFindPrevious(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && CanFindPrevious()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditReplace(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanReplace());
}

void CMainWnd::OnUpdateEditGoTo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanGoTo());
}

void CMainWnd::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanCutSel());
}

void CMainWnd::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanCopySel());
}

void CMainWnd::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanPasteSel());
}

void CMainWnd::OnUpdateEditDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanDeleteSel());
}

void CMainWnd::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanSelectAll());
}

void CMainWnd::OnUpdateEditSaveTable(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling()) ? pDisplayWnd->CanSaveTable() : FALSE);
}

void CMainWnd::OnUpdateEditCheckTable(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling()) ? pDisplayWnd->CanCheckTable() : FALSE);
}

void CMainWnd::OnUpdateEditDeleteTable(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling()) ? pDisplayWnd->CanDeleteTable() : FALSE);
}

void CMainWnd::OnUpdateEditImportTables(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid() && !IsCompiling()) ? pDisplayWnd->CanImportTables() : FALSE);
}

void CMainWnd::OnUpdateEditExportTables(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanExportTables() : FALSE);
}

void CMainWnd::OnUpdateEditPrintTable(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanPrintTable() : FALSE);
}

void CMainWnd::OnUpdateEditPrintAllTables(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanPrintAllTables() : FALSE);
}

void CMainWnd::OnUpdateEditInsertTableRowAbove(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanInsertTableRowAbove() : FALSE);
}

void CMainWnd::OnUpdateEditInsertTableRowBelow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanInsertTableRowBelow() : FALSE);
}

void CMainWnd::OnUpdateEditInsertTableColumnBefore(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanInsertTableColumnBefore() : FALSE);
}

void CMainWnd::OnUpdateEditInsertTableColumnAfter(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanInsertTableColumnAfter() : FALSE);
}

void CMainWnd::OnUpdateEditClearTableRow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanClearTableRow() : FALSE);
}

void CMainWnd::OnUpdateEditDeleteTableRow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanDeleteTableRow() : FALSE);
}

void CMainWnd::OnUpdateEditDeleteTableColumn(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanDeleteTableColumn() : FALSE);
}

void CMainWnd::OnUpdateEditCopyTableRow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanCopyTableRow() : FALSE);
}

void CMainWnd::OnUpdateEditPasteTableRow(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanPasteTableRow() : FALSE);
}

void CMainWnd::OnUpdateEditDiscardAllTables(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanDiscardAllTables() : FALSE);
}

void CMainWnd::OnUpdateEditDiscardTables(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanDiscardTables() : FALSE);
}

void CMainWnd::OnUpdateEditResetTables(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && GetDatabase()->IsValid()) ? pDisplayWnd->CanResetTables() : FALSE);
}

void CMainWnd::OnUpdateEditCreateMimicsGroup(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	if ((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->GetMimicsCtrlCount() > 0)
	{
		pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
		pCmdUI->SetCheck(IsWindow(m_dlgCreateMimicsGroup.GetSafeHwnd()));
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateEditDeleteMimicsGroup(CCmdUI *pCmdUI)
{
	CProfile  cProfile;
	CByteArray  nGroupsInfo;
	CMimicsGroups  pMimicsGroups;
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD)
	{
		if (cProfile.GetMimicsGroupsInfo(nGroupsInfo) && pMimicsGroups.Unmap(nGroupsInfo) && pMimicsGroups.GetSize() > 0)
		{
			pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
			pCmdUI->SetCheck(IsWindow(m_dlgDeleteMimicsGroup.GetSafeHwnd()));
			return;
		}
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateEditCollectMimicsGroup(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanCollectMimicsGroup() && GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateEditDiscardMimicsGroup(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanDiscardMimicsGroup() && GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateEditStepIntoMimicsGroup(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanStepIntoMimicsGroup() && GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateEditStepOutMimicsGroup(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanStepOutMimicsGroup() && GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateEditImportMimicsGroup(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetDatabase()->IsValid() && !IsCompiling()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgImportMimicsGroup.GetSafeHwnd()));
}

void CMainWnd::OnUpdateEditExportMimicsGroup(CCmdUI *pCmdUI)
{
	CProfile  cProfile;
	CByteArray  nGroupsInfo;
	CMimicsGroups  pMimicsGroups;

	if (cProfile.GetMimicsGroupsInfo(nGroupsInfo) && pMimicsGroups.Unmap(nGroupsInfo) && pMimicsGroups.GetSize() > 0)
	{
		pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
		pCmdUI->SetCheck(IsWindow(m_dlgExportMimicsGroup.GetSafeHwnd()));
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateEditHorzAlignMimicsObjects(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanHorzAlignMimicsCtrls() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditVertAlignMimicsObjects(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanVertAlignMimicsCtrls() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditMoveMimicsObjectToTop(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanMoveMimicsCtrlToTop() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditMoveMimicsObjectToBottom(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanMoveMimicsCtrlToBottom() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditMoveMimicsObjectUp(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanMoveMimicsCtrlUp() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditMoveMimicsObjectDown(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanMoveMimicsCtrlDown() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditShowHideMimicsObject(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanShowHideMimicsCtrl() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditHorzFlipMimicsObject(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanHorzFlipMimicsCtrl() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditVertFlipMimicsObject(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanVertFlipMimicsCtrl() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditRotateMimicsObject(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanRotateMimicsCtrl() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateEditTurnMimicsObject(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	if ((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->CanRotateMimicsCtrl())
	{
		pCmdUI->SetCheck(GetDatabase()->IsValid() && pMMDWnd->GetMimicsCtrlRotateMode());
		pCmdUI->Enable(GetDatabase()->IsValid());
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateViewMimicsObjectProperties(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	if ((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->HasMimicsCtrlProperties())
	{
		pCmdUI->SetCheck(GetDatabase()->IsValid() && pMMDWnd->IsUpdatingProperties());
		pCmdUI->Enable(GetDatabase()->IsValid());
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateViewMimicsObjectItem(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->HasMimicsCtrlItem() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateViewMimicsObjectCode(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && pMMDWnd->HasMimicsCtrlCode() && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateProperties(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->HasProperties())
	{
		pCmdUI->SetCheck(GetDatabase()->IsValid() && pDisplayWnd->IsUpdatingProperties());
		pCmdUI->Enable(GetDatabase()->IsValid());
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateSourceCode(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL) && GetDatabase()->IsValid()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateLinkInformation(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->HasLinkInformation())
	{
		pCmdUI->SetCheck(pDisplayWnd->IsUpdatingLinkInformation());
		pCmdUI->Enable(GetDatabase()->IsValid());
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateWorkspaceWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsWindow(GetWorkspaceWindow()->GetSafeHwnd()));
	pCmdUI->SetCheck(IsWindow(GetWorkspaceWindow()->GetSafeHwnd()) && GetWorkspaceWindow()->IsVisible());
}

void CMainWnd::OnUpdateOutputWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsWindow(GetOutputWindow()->GetSafeHwnd()));
	pCmdUI->SetCheck(IsWindow(GetOutputWindow()->GetSafeHwnd()) && GetOutputWindow()->IsVisible());
}

void CMainWnd::OnUpdateZoomWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsWindow(GetZoomWindow()->GetSafeHwnd()) && GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(GetZoomWindow()->GetSafeHwnd()) && GetZoomWindow()->IsWindowVisible());
}

void CMainWnd::OnUpdateMimicsObjectsToolBar(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsWindow(m_wndMimicsObjectsToolBar.GetSafeHwnd()) && GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_wndMimicsObjectsToolBar.GetSafeHwnd()) && m_wndMimicsObjectsToolBar.IsVisible());
}

void CMainWnd::OnUpdateMimicsObjectsMenu(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD  &&  GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateMimicsObjects(CCmdUI *pCmdUI)
{
	CMMDWnd  *pMMDWnd;
	CDisplayWnd  *pDisplayWnd;

	if ((pMMDWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD) ? (CMMDWnd *)pDisplayWnd : (CMMDWnd *)NULL))
	{
		pCmdUI->SetCheck((GetDatabase()->IsValid() && pMMDWnd->GetSelectedMimicsCtrlID() == pCmdUI->m_nID) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
		pCmdUI->Enable((GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateMimicsGroup(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD  &&  GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateTCStepsToolBar(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsWindow(m_wndTCStepsToolBar.GetSafeHwnd()) && GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_wndTCStepsToolBar.GetSafeHwnd()) && m_wndTCStepsToolBar.IsVisible());
}

void CMainWnd::OnUpdateTCStepsMenu(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE  &&  GetDatabase()->IsValid()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateTCSteps(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;
	CTCProcedureWnd  *pTCProcedureWnd;

	if ((pTCProcedureWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE) ? (CTCProcedureWnd *)pDisplayWnd : (CTCProcedureWnd *)NULL))
	{
		pCmdUI->SetCheck((GetDatabase()->IsValid() && !pTCProcedureWnd->IsTesting() && pTCProcedureWnd->GetSelectedTCStepID() == pCmdUI->m_nID) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
		pCmdUI->Enable((GetDatabase()->IsValid() && !pTCProcedureWnd->IsTesting()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
		return;
	}
	pCmdUI->SetCheck(FALSE);
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateTCStepBreakpointOptions(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;
	CTCProcedureWnd  *pTCProcedureWnd;

	pCmdUI->Enable(((pTCProcedureWnd = ((pDisplayWnd = (CDisplayWnd *)MDIGetActive()) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE  &&  GetDatabase()->IsValid()) ? (CTCProcedureWnd *)pDisplayWnd : (CTCProcedureWnd *)NULL)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE) : FALSE);
}

void CMainWnd::OnUpdateBuildOptions(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_dlgCompileOptions.GetSafeHwnd()));
}

void CMainWnd::OnUpdateBuildDirectives(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_dlgCompileDirectives.GetSafeHwnd()));
}

void CMainWnd::OnUpdateBuildDownload(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}

void CMainWnd::OnUpdateBuildCompile(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && !pDisplayWnd->IsTesting() && pDisplayWnd->CanCompile() && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILE)) : FALSE);
}

void CMainWnd::OnUpdateBuildCompileAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && !IsCompiling() && !IsTesting() && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILE));
}

void CMainWnd::OnUpdateBuildCompileBatches(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && !IsCompiling() && !IsTesting());
	pCmdUI->SetCheck(IsWindow(m_dlgCompileBatches.GetSafeHwnd()));
}

void CMainWnd::OnUpdateBuildCompileStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && IsCompiling() && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILE));
}

void CMainWnd::OnUpdateBuildClean(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid() && CanCleanDatabaseFiles() && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILE));
}

void CMainWnd::OnUpdateBuildTest(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && !pDisplayWnd->IsTesting() && pDisplayWnd->CanTest()) : FALSE);
}

void CMainWnd::OnUpdateBuildTestBreak(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && pDisplayWnd->CanBreakTesting()) : FALSE);
}

void CMainWnd::OnUpdateBuildTestContinue(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && pDisplayWnd->CanContinueTesting()) : FALSE);
}

void CMainWnd::OnUpdateBuildTestStepInto(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && pDisplayWnd->CanTestStepInto()) : FALSE);
}

void CMainWnd::OnUpdateBuildTestStepOver(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && pDisplayWnd->CanTestStepOver()) : FALSE);
}

void CMainWnd::OnUpdateBuildTestStepOut(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && pDisplayWnd->CanTestStepOut()) : FALSE);
}

void CMainWnd::OnUpdateBuildTestStop(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && pDisplayWnd->IsTesting()) : FALSE);
}

void CMainWnd::OnUpdateBuildTestReset(CCmdUI *pCmdUI)
{
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable(((pDisplayWnd = (CDisplayWnd *)MDIGetActive())) ? (GetDatabase()->IsValid() && !GetDatabase()->IsCompiling() && !pDisplayWnd->IsCompiling() && pDisplayWnd->CanResetTesting()) : FALSE);
}

void CMainWnd::OnUpdateToolsOptions(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_dlgToolsOptions.GetSafeHwnd()));
}

void CMainWnd::OnUpdateUsers(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_dlgDatabaseUsers.GetSafeHwnd()));
}

void CMainWnd::OnUpdatePrivileges(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_dlgDatabasePrivileges.GetSafeHwnd()));
}

void CMainWnd::OnUpdateValidity(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDatabase()->IsValid());
	pCmdUI->SetCheck(IsWindow(m_dlgDatabaseValidity.GetSafeHwnd()));
}

void CMainWnd::OnUpdateNextWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((MDIGetActive()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdatePreviousWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((MDIGetActive()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateCloseWindow(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((MDIGetActive()) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateCloseAllWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((EnumDisplayWindows() > 0) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((EnumDisplayWindows() > 0) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateDisplayWindows(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((EnumDisplayWindows() > 0) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateDisplayWindow(CCmdUI *pCmdUI)
{
	INT  nIndex;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	pCmdUI->Enable((EnumDisplayWindows(pDisplays) > 0) ? TRUE : FALSE);
	pCmdUI->SetCheck(((pDisplayWnd = ((nIndex = pCmdUI->m_nID - IDM_FIRSTDISPLAYWINDOW) >= 0 && nIndex < pDisplays.GetSize()) ? (CDisplayWnd *)pDisplays.GetAt(nIndex) : (CDisplayWnd *)NULL) && MDIGetActive() == (CMDIChildWnd *)pDisplayWnd) ? TRUE : FALSE);
}

void CMainWnd::OnUpdateAssistantSupportDateConversions(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMainWnd::OnUpdateAssistantListen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMainWnd::OnUpdateMRUDocument(CCmdUI *pCmdUI)
{
	CRecentDocuments  pDocuments;

	pCmdUI->Enable(EnumMRUDocuments(pDocuments) > 0);
}

void CMainWnd::OnUpdateMRUDatabase(CCmdUI *pCmdUI)
{
	CRecentDatabases  pDatabases;

	pCmdUI->Enable(EnumMRUDatabases(pDatabases) > 0);
}

void CMainWnd::OnUpdateStatusBarServerPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount());
}

void CMainWnd::OnUpdateStatusBarSpacecraftPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount());
}

void CMainWnd::OnUpdateStatusBarUserPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount());
}

void CMainWnd::OnUpdateStatusBarDatabasePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TestAccount());
}

void CMainWnd::OnUpdateStatusBarCAPSKeyPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CheckKeyState(VK_CAPITAL));
}

void CMainWnd::OnUpdateStatusBarNUMKeyPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CheckKeyState(VK_NUMLOCK));
}

void CMainWnd::OnUpdateStatusBarSCRLKeyPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CheckKeyState(VK_SCROLL));
}

void CMainWnd::OnUpdateStatusBarOVRKeyPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CheckKeyState(VK_INSERT));
}

void CMainWnd::OnUpdateAbout(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMainWnd::OnUpdateHelp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsHelpAvailable());
}

void CMainWnd::OnUpdateExit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!IsCompiling() && !IsPrinting());
}


/////////////////////////////////////////////////////////////////////////////
// CEditorAppCommandLineInfo

CEditorAppCommandLineInfo::CEditorAppCommandLineInfo() : CCommandLineInfo()
{
	m_bServer = FALSE;
	m_bSpacecraft = FALSE;
	m_bDatabase = FALSE;
	m_bPassword = FALSE;
	m_bUser = FALSE;
}

CString CEditorAppCommandLineInfo::GetServer() CONST
{
	return m_cAccountToken.GetComputerName();
}

CString CEditorAppCommandLineInfo::GetSpacecraft() CONST
{
	return m_cAccountToken.GetSpacecraftName();
}

CString CEditorAppCommandLineInfo::GetDatabase() CONST
{
	return m_cAccountToken.GetDatabase();
}

CString CEditorAppCommandLineInfo::GetPassword() CONST
{
	return m_cAccountToken.GetPassword();
}

CString CEditorAppCommandLineInfo::GetUser() CONST
{
	return m_cAccountToken.GetUserName();
}

BOOL CEditorAppCommandLineInfo::IsValid() CONST
{
	return !m_cAccountToken.GetSpacecraftName().IsEmpty() && !m_cAccountToken.GetUserName().IsEmpty() && !m_cAccountToken.GetDatabase().IsEmpty();
}

void CEditorAppCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast)
{
	INT  nPos;
	CString  szUser;
	CString  szServer;
	CString  szFlag[2];
	CString  szDatabase;
	CString  szPassword;
	CString  szSpacecraft;

	for (szFlag[0] = pszParam, szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_SERVER); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szServer = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szServer.IsEmpty() && szServer.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szServer = szServer.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bServer = TRUE;
			break;
		}
		if (!szServer.IsEmpty() && szServer.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bServer)
		{
			szServer = szServer.Left(szServer.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bServer = FALSE;
		}
		m_cAccountToken.SetComputerName(szServer);
		m_bSpacecraft = m_bUser = m_bDatabase = m_bPassword = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_SPACECRAFT); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szSpacecraft = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szSpacecraft.IsEmpty() && szSpacecraft.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szSpacecraft = szSpacecraft.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bSpacecraft = TRUE;
			break;
		}
		if (!szSpacecraft.IsEmpty() && szSpacecraft.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bSpacecraft)
		{
			szSpacecraft = szSpacecraft.Left(szSpacecraft.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bSpacecraft = FALSE;
		}
		m_cAccountToken.SetSpacecraftName(szSpacecraft);
		m_bServer = m_bUser = m_bDatabase = m_bPassword = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_USER); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szUser = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szUser.IsEmpty() && szUser.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szUser = szUser.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bUser = TRUE;
			break;
		}
		if (!szUser.IsEmpty() && szUser.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bUser)
		{
			szUser = szUser.Left(szUser.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bUser = FALSE;
		}
		m_cAccountToken.SetUserName(szUser);
		m_bServer = m_bSpacecraft = m_bDatabase = m_bPassword = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_DATABASE); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szDatabase = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szDatabase.IsEmpty() && szDatabase.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szDatabase = szDatabase.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bDatabase = TRUE;
			break;
		}
		if (!szDatabase.IsEmpty() && szDatabase.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bDatabase)
		{
			szDatabase = szDatabase.Left(szDatabase.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bDatabase = FALSE;
		}
		m_cAccountToken.SetDatabase(szDatabase);
		m_bServer = m_bSpacecraft = m_bUser = m_bPassword = FALSE;
		return;
	}
	for (szFlag[1] = STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAG_PASSWORD); (nPos = szFlag[0].Find(szFlag[1].Mid(1))) >= 0; )
	{
		for (szPassword = szFlag[0].Mid(nPos + szFlag[1].GetLength() - 1).Trim(); !szPassword.IsEmpty() && szPassword.Mid(0, lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER); )
		{
			szPassword = szPassword.Mid(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bPassword = TRUE;
			break;
		}
		if (!szPassword.IsEmpty() && szPassword.Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER) && m_bPassword)
		{
			szPassword = szPassword.Left(szPassword.GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)));
			m_bPassword = FALSE;
		}
		m_cAccountToken.SetPassword(szPassword);
		m_bServer = m_bSpacecraft = m_bUser = m_bDatabase = FALSE;
		return;
	}
	if (szFlag[0].GetLength() > lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)) && szFlag[0].Right(lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))) == STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER))
	{
		m_cAccountToken.SetComputerName((m_bServer) ? (m_cAccountToken.GetComputerName() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetComputerName());
		m_cAccountToken.SetSpacecraftName((m_bSpacecraft) ? (m_cAccountToken.GetSpacecraftName() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetSpacecraftName());
		m_cAccountToken.SetUserName((m_bUser) ? (m_cAccountToken.GetUserName() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetUserName());
		m_cAccountToken.SetDatabase((m_bDatabase) ? (m_cAccountToken.GetDatabase() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetDatabase());
		m_cAccountToken.SetPassword((m_bPassword) ? (m_cAccountToken.GetPassword() + SPACE + szFlag[0].Left(szFlag[0].GetLength() - lstrlen(STRING(IDS_APPLICATIONINFO_COMMANDLINEFLAGVALUE_DELIMITER)))) : m_cAccountToken.GetPassword());
		m_bServer = m_bSpacecraft = m_bUser = m_bDatabase = m_bPassword = FALSE;
	}
	CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}


/////////////////////////////////////////////////////////////////////////////
// CEditorApp

IMPLEMENT_DYNAMIC(CEditorApp, CAccountsApp)

CEditorApp::CEditorApp() : CAccountsApp()
{
	m_pDatabase = new CSourceDatabase;
	m_pNetworkBrowseService = new CNetworkBrowseService;
	m_pMainWnd = (CMainWnd *)NULL;
}

CEditorApp::~CEditorApp()
{
	delete m_pNetworkBrowseService;
	delete m_pDatabase;
}

BOOL CEditorApp::InitInstance()
{
	INT  nResultCode;
	CMainWnd  *pMainWnd;
	CEventLog  cEventLog;
	CStringArray  szLogs;
	CVersionInfo  cVersionInfo;
	CEditorAppCommandLineInfo  cStartupInfo;
	CHourglassCursor  cCursor;

	if (CAccountsApp::InitInstance())
	{
		if ((nResultCode = RegisterApp()) > 0)
		{
			if ((m_pMainWnd = pMainWnd = new CMainWnd) && pMainWnd->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL))
			{
				for (ParseCommandLine(cStartupInfo); RunAccount(cStartupInfo); )
				{
					StartNetworkBrowseService();
					return TRUE;
				}
				pMainWnd->DestroyWindow();
				m_pMainWnd = (CWnd *)NULL;
				return FALSE;
			}
		}
		if (nResultCode >= 0)
		{
			szLogs.Add(cVersionInfo.QueryComments());
			szLogs.Add(cVersionInfo.QueryLegalCopyright());
			cEventLog.Report(SYSTEM_CRITICAL_INITIALIZATION_FAILURE, szLogs);
		}
		m_pMainWnd = (CWnd *)NULL;
	}
	return FALSE;
}

int CEditorApp::ExitInstance()
{
	CHourglassCursor  cCursor;

	UnregisterApp();
	StopNetworkBrowseService();
	return CAccountsApp::ExitInstance();
}

BOOL CEditorApp::SetDatabase()
{
	return SetDatabase(GetAccountSpacecraftName());
}
BOOL CEditorApp::SetDatabase(LPCTSTR pszSpacecraft)
{
	return SetDatabase(pszSpacecraft, GetAccountDatabase());
}
BOOL CEditorApp::SetDatabase(LPCTSTR pszSpacecraft, LPCTSTR pszDatabase)
{
	return SetDatabase(GetAccountComputerName(), pszSpacecraft, pszDatabase);
}
BOOL CEditorApp::SetDatabase(LPCTSTR pszServer, LPCTSTR pszSpacecraft, LPCTSTR pszDatabase, BOOL bLoad, BOOL bBinary)
{
	INT  nUser;
	INT  nUsers;
	INT  nDatabase;
	INT  nDatabases;
	BOOL  bDatabase;
	CString  szPassword;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;
	CTimeKey  tValidity[2];
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CAccountToken  cAccountToken;

	if (GetAccountComputerName().CompareNoCase(pszServer) || GetAccountSpacecraftName() != pszSpacecraft || GetAccountDatabase() != pszDatabase)
	{
		GetMainWnd()->SaveDisplayWindows();
		GetMainWnd()->CloseAllWindows();
		GetDatabase()->Close();
	}
	for (nDatabase = 0, nDatabases = (cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : 0, GetAccount(&cAccountToken); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetServer() == pszServer  &&  pDatabaseProfileInfo->GetSpacecraft() == pszSpacecraft  &&  pDatabaseProfileInfo->GetName() == pszDatabase)
		{
			if (!GetDatabase()->Open(pDatabaseProfileInfo, FALSE, bBinary))
			{
				nDatabase = nDatabases;
				break;
			}
			if (!GetAccountComputerName().CompareNoCase(pszServer) && GetAccountSpacecraftName() == pszSpacecraft  &&  GetAccountDatabase() == pszDatabase)
			{
				if (!GetMainWnd()->SelectDatabase())
				{
					nDatabase = nDatabases;
					break;
				}
				GetMainWnd()->AddMRUMenuItem(pDatabaseProfileInfo);
				break;
			}
			for (nUser = 0, nUsers = (pDatabaseProfileInfo->GetUsers(szUsers, szPasswords, nPrivileges) > 0) ? (INT)szUsers.GetSize() : 0; nUser < nUsers; nUser++)
			{
				if (szUsers.GetAt(nUser) == GetAccountUserName())
				{
					szPassword = szPasswords.GetAt(nUser);
					break;
				}
			}
			if (nUser < nUsers)
			{
				if ((bDatabase = cAccountToken.GetPrivileges(nPrivileges) && cAccountToken.GetValidity(tValidity[0], tValidity[1])))
				{
					cAccountToken.SetOwner(pszServer, pszSpacecraft, GetAccountUserName());
					cAccountToken.SetMode(ACCOUNT_MODE_OFFLINE);
					cAccountToken.SetPrivileges(nPrivileges);
					cAccountToken.SetDatabase(pszDatabase);
					cAccountToken.SetPassword(szPassword);
					cAccountToken.SetValidity(tValidity[0], tValidity[1]);
					SetAccount(&cAccountToken);
				}
				if (bDatabase)
				{
					for (GetDatabase()->Attach(pDatabaseProfileInfo); (bDatabase = GetMainWnd()->SelectDatabase()); )
					{
						GetMainWnd()->AddMRUMenuItem(pDatabaseProfileInfo);
						GetMainWnd()->LoadDisplayWindows();
						break;
					}
					if (bDatabase) break;
				}
			}
			GetDatabase()->Close();
			nDatabase = nDatabases;
			break;
		}
	}
	if (nDatabase == nDatabases)
	{
		if ((pDatabaseProfileInfo = new CDatabaseProfileInfo))
		{
			if (cAccountToken.GetPrivileges(nPrivileges) && cAccountToken.GetValidity(tValidity[0], tValidity[1]) && (szPassword = cAccountToken.GetPassword()).GetLength() >= 0)
			{
				cAccountToken.SetOwner(pszServer, EMPTYSTRING, GetAccountUserName());
				cAccountToken.SetMode(ACCOUNT_MODE_OFFLINE);
				cAccountToken.SetPrivileges(nPrivileges);
				cAccountToken.SetDatabase(EMPTYSTRING);
				cAccountToken.SetPassword(szPassword);
				cAccountToken.SetValidity(tValidity[0], tValidity[1]);
				SetAccount(&cAccountToken);
			}
			GetDatabase()->Attach(pDatabaseProfileInfo);
			GetMainWnd()->SelectDatabase(TRUE);
			delete pDatabaseProfileInfo;
		}
		ShowMessage((lstrlen(pszDatabase) > 0 && nDatabases > 0) ? SYSTEM_WARNING_DATABASE_LOAD_FAILURE : SYSTEM_NOERROR);
		return FALSE;
	}
	return GetDatabase()->Initialize(ReportID, ReportMessage, HelpTopic);
}

CSourceDatabase *CEditorApp::GetDatabase() CONST
{
	return m_pDatabase;
}

VOID CEditorApp::UpdateDatabase(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pDatabaseTMPacket, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pDatabaseTCFunction, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pDatabaseTCSequence, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pDatabaseTCProcedure, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pDatabaseOBProcessor, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pDatabaseTMParameter, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pDatabaseTCParameter, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pTCSequenceWnd, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pANDWnd, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pGRDWnd, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pMMDWnd, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pPODWnd, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete)
{
	GetMainWnd()->UpdateDatabase(pScriptWnd, nPosition, bDelete);
}
VOID CEditorApp::UpdateDatabase(ULONGLONG nComponent, LPCTSTR pszName)
{
	GetMainWnd()->UpdateDatabase(nComponent, pszName);
}
VOID CEditorApp::UpdateDatabase()
{
	GetMainWnd()->UpdateDatabase();
}

VOID CEditorApp::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMPacketWnd, pDatabaseTMPacket, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketIdentification, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketIdentificationCriterion, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketHeader, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketStream, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketGroup, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCFunction, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCPacket, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCPacketParameter, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCPreExeGroup, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCExeVerStage, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCExeVerGroup, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCParameterSet, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCParameterValueSet, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCFunctionWnd, pDatabaseTCFunctionRoutingPath, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCSequenceWnd, pDatabaseTCSequence, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCSequenceWnd, pDatabaseTCFunctionBlock, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCSequenceWnd, pDatabaseTCParameterSet, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCSequenceWnd, pDatabaseTCParameterValueSet, bDelete);
}
VOID CEditorApp::UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pOBProcessorWnd, pDatabaseOBProcessor, bDelete);
}
VOID CEditorApp::UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pOBProcessorWnd, pDatabaseOBProcessorMemoryImage, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMParameterWnd, pDatabaseTMParameter, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMParameterWnd, pDatabaseTMNumCalTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMParameterWnd, pDatabaseTMTxtCalTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMParameterWnd, pDatabaseTMNumOolTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMParameterWnd, pDatabaseTMTxtOolTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTMParameterWnd, pDatabaseTMParameterGroup, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCParameterWnd, pDatabaseTCParameter, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCParameterWnd, pDatabaseTCNumCalTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCParameterWnd, pDatabaseTCTxtCalTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCParameterWnd, pDatabaseTCNumOolTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pTCParameterWnd, pDatabaseTCTxtOolTable, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CANDWnd *pANDWnd, CONST CANDLayout *pLayout, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pANDWnd, pLayout, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CGRDWnd *pGRDWnd, CONST CGRDLayout *pLayout, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pGRDWnd, pLayout, bDelete);
}
VOID CEditorApp::UpdateForms(CONST CPODWnd *pPODWnd, CONST CPODLayout *pLayout, BOOL bDelete)
{
	GetMainWnd()->UpdateForms(pPODWnd, pLayout, bDelete);
}

BOOL CEditorApp::CreateDatabaseItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->CreateDatabaseItem();
}

BOOL CEditorApp::OpenDatabaseItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->OpenDatabaseItem();
}

BOOL CEditorApp::HasDatabaseItem(INT nType) CONST
{
	return GetMainWnd()->GetWorkspaceWindow()->HasDatabaseItem(nType);
}

BOOL CEditorApp::RenameDatabaseItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->RenameDatabaseItem();
}

BOOL CEditorApp::DeleteDatabaseItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->DeleteDatabaseItem();
}

BOOL CEditorApp::CreateProceduresItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->CreateProceduresItem();
}

BOOL CEditorApp::OpenProceduresItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->OpenProceduresItem();
}

BOOL CEditorApp::HasProceduresItem(INT nType) CONST
{
	return GetMainWnd()->GetWorkspaceWindow()->HasProceduresItem(nType);
}

BOOL CEditorApp::RenameProceduresItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->RenameProceduresItem();
}

BOOL CEditorApp::DeleteProceduresItem()
{
	return GetMainWnd()->GetWorkspaceWindow()->DeleteProceduresItem();
}

INT CEditorApp::EnumDisplayWindows()
{
	return GetMainWnd()->EnumDisplayWindows();
}
INT CEditorApp::EnumDisplayWindows(CPtrArray &pDisplays)
{
	return GetMainWnd()->EnumDisplayWindows(pDisplays);
}

VOID CEditorApp::ActivateDisplayWindow(CWnd *pWnd)
{
	GetMainWnd()->ActivateDisplayWindow(pWnd);
}

CDisplayWnd *CEditorApp::GetActiveDisplayWindow() CONST
{
	return GetMainWnd()->GetActiveDisplayWindow();
}

BOOL CEditorApp::ShowMessage(LPCTSTR pszMessage, BOOL bAudition)
{
	return((IsWindow(GetMainWnd()->GetSafeHwnd())) ? GetMainWnd()->ShowMessage(pszMessage, bAudition) : FALSE);
}
BOOL CEditorApp::ShowMessage(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition)
{
	return((IsWindow(GetMainWnd()->GetSafeHwnd())) ? GetMainWnd()->ShowMessage(sEvent, bAudition) : FALSE);
}

BOOL CEditorApp::ResetMessages()
{
	return GetMainWnd()->ResetMessages();
}

BOOL CEditorApp::SetConsoleContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument)
{
	return GetMainWnd()->SetConsoleContext(pszConsole, pDocument);
}

BOOL CEditorApp::GetConsoleContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument)
{
	return GetMainWnd()->GetConsoleContext(pszConsole, pDocument);
}

BOOL CEditorApp::ShowConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, BOOL bTimestamp, BOOL bAudition)
{
	return((IsWindow(GetMainWnd()->GetSafeHwnd())) ? GetMainWnd()->ShowConsoleText(pszConsole, pszText, bTimestamp, bAudition) : FALSE);
}

BOOL CEditorApp::ReadConsoleText(LPCTSTR pszConsole, CStringArray &szText, BOOL bTimestamp, BOOL bAll)
{
	return((IsWindow(GetMainWnd()->GetSafeHwnd())) ? GetMainWnd()->ReadConsoleText(pszConsole, szText, bTimestamp, bAll) : FALSE);
}

INT CEditorApp::AlertConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, COLORREF nColor, BOOL bTimestamp)
{
	return((IsWindow(GetMainWnd()->GetSafeHwnd())) ? GetMainWnd()->AlertConsoleText(pszConsole, pszText, nColor, bTimestamp) : -1);
}

BOOL CEditorApp::AcknowledgeConsoleText(LPCTSTR pszConsole, INT nLine)
{
	return((IsWindow(GetMainWnd()->GetSafeHwnd())) ? GetMainWnd()->AcknowledgeConsoleText(pszConsole, nLine) : FALSE);
}

BOOL CEditorApp::ResetConsoleContent(LPCTSTR pszConsole)
{
	return GetMainWnd()->ResetConsoleContent(pszConsole);
}

BOOL CEditorApp::ResetAllConsoles()
{
	return GetMainWnd()->ResetAllConsoles();
}

VOID CEditorApp::SetFindDefaults(BOOL bForward, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord, BOOL bToggle)
{
	GetMainWnd()->SetFindDefaults(bForward, bSearchAll, bMatchCase, bMatchWord, bToggle);
}

VOID CEditorApp::GetFindDefaults(BOOL &bForward, BOOL &bSearchAll, BOOL &bMatchCase, BOOL &bMatchWord) CONST
{
	GetMainWnd()->GetFindDefaults(bForward, bSearchAll, bMatchCase, bMatchWord);
}

VOID CEditorApp::SaveProfiles()
{
	ShowMessage((!SaveCompileBatchProfiles()) ? SYSTEM_WARNING_COMPILEBATCHPROFILES_SAVE_FAILURE : SYSTEM_NOERROR);
	ShowMessage((!SavePrintProfile()) ? SYSTEM_WARNING_PRINTPROFILES_SAVE_FAILURE : SYSTEM_NOERROR);
}

VOID CEditorApp::LoadProfiles()
{
	ShowMessage((!LoadCompileBatchProfiles()) ? SYSTEM_WARNING_COMPILEBATCHPROFILES_LOAD_FAILURE : SYSTEM_NOERROR);
	ShowMessage((!LoadPrintProfile()) ? SYSTEM_WARNING_PRINTPROFILES_LOAD_FAILURE : SYSTEM_NOERROR);
}

BOOL CEditorApp::SetCompileBatchProfiles(CONST CCompileBatches &pBatches)
{
	return GetDatabase()->SetCompileBatches(pBatches);
}

BOOL CEditorApp::GetCompileBatchProfiles(CCompileBatches &pBatches)
{
	return GetDatabase()->GetCompileBatches(pBatches);
}

BOOL CEditorApp::SetPrintProfile(CONST CPrintProfileInfo &cProfileInfo)
{
	return m_cPrintProfile.Copy(&cProfileInfo);
}

BOOL CEditorApp::GetPrintProfile(CPrintProfileInfo &cProfileInfo)
{
	return cProfileInfo.Copy(&m_cPrintProfile);
}

BOOL CEditorApp::InitializeDefaultPrinter()
{
	return m_cDefaultPrinter.Initialize();
}

BOOL CEditorApp::IsDefaultPrinterAvailable() CONST
{
	return m_cDefaultPrinter.IsAvailable();
}

BOOL CEditorApp::SetDefaultPrinterInfo(CONST PAGESETUPDLG *pPrinterInfo)
{
	if (m_cPrintProfile.SetDeviceInfo(pPrinterInfo->hDevNames, pPrinterInfo->hDevMode))
	{
		m_cPrintProfile.SetPaperInfo(CSize(pPrinterInfo->ptPaperSize.x, pPrinterInfo->ptPaperSize.y), pPrinterInfo->rtMargin, pPrinterInfo->rtMinMargin, (pPrinterInfo->Flags & PSD_INHUNDREDTHSOFMILLIMETERS) ? TRUE : FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorApp::GetDefaultPrinterInfo(PAGESETUPDLG *pPrinterInfo)
{
	BOOL  bMetrics;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	HANDLE  hDevMode;
	HANDLE  hDevNames;

	if (m_cPrintProfile.GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetrics) && m_cPrintProfile.GetDeviceInfo(hDevNames, hDevMode))
	{
		pPrinterInfo->ptPaperSize.x = ptPaperSize.cx;
		pPrinterInfo->ptPaperSize.y = ptPaperSize.cy;
		CopyMemory(&pPrinterInfo->rtMargin, &rtMargin[0], sizeof(RECT));
		CopyMemory(&pPrinterInfo->rtMinMargin, &rtMargin[1], sizeof(RECT));
		pPrinterInfo->Flags |= (bMetrics) ? (PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS | PSD_NOWARNING) : (PSD_MARGINS | PSD_INTHOUSANDTHSOFINCHES | PSD_NOWARNING);
		pPrinterInfo->hDevNames = hDevNames;
		pPrinterInfo->hDevMode = hDevMode;
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorApp::CreatePrinterDC(CONST CPrintProfileInfo *pProfileInfo, CDC &cDC)
{
	HANDLE  hDevMode;
	HANDLE  hDevNames;

	if (pProfileInfo->GetDeviceInfo(hDevNames, hDevMode))
	{
		if (CreatePrinterDC(hDevNames, hDevMode, cDC))
		{
			GlobalFree(hDevNames);
			GlobalFree(hDevMode);
			return TRUE;
		}
		GlobalFree(hDevNames);
		GlobalFree(hDevMode);
	}
	return FALSE;
}
BOOL CEditorApp::CreatePrinterDC(HANDLE hDevNames, HANDLE hDevMode, CDC &cDC)
{
	HDC  hDC;

	if ((hDC = AfxCreateDC(hDevNames, hDevMode)))
	{
		for (cDC.DeleteDC(); !cDC.Attach(hDC); )
		{
			DeleteDC(hDC);
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorApp::IsCompiling() CONST
{
	return GetMainWnd()->IsCompiling();
}

BOOL CEditorApp::IsTesting() CONST
{
	return GetMainWnd()->IsTesting();
}

BOOL CEditorApp::IsPrinting() CONST
{
	return GetMainWnd()->IsPrinting();
}

BOOL CEditorApp::CheckDatabasePrivilege(UINT nPrivilege)
{
	INT  nUser;
	INT  nUsers;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;

	for (nUser = 0, nUsers = (GetDatabase()->GetUsers(szUsers, szPasswords, nPrivileges) >= 0) ? (INT)szUsers.GetSize() : -1; nUser < nUsers; nUser++)
	{
		if (szUsers.GetAt(nUser) == GetAccountUserName() && (nPrivileges.GetAt(nUser) & nPrivilege)) break;
		continue;
	}
	return((!nUsers || nUser < nUsers) ? TRUE : FALSE);
}

BOOL CEditorApp::ShowHelp(LPCTSTR pszTopic)
{
	if (IsHelpAvailable())
	{
		HtmlHelp((DWORD_PTR)pszTopic, HH_DISPLAY_TOPIC);
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorApp::IsHelpAvailable() CONST
{
	CFileFindEx  cFileFind;

	if (cFileFind.FindFile(GetHelpFileName()))
	{
		cFileFind.Close();
		return TRUE;
	}
	return FALSE;
}

CNetworkBrowseService *CEditorApp::GetNetworkBrowseService() CONST
{
	return m_pNetworkBrowseService;
}

CDisplayFrame *CEditorApp::GetDisplayFrame() CONST
{
	return GetMainWnd()->GetDisplayFrame();
}

CMainWnd *CEditorApp::GetMainWnd() CONST
{
	return((CMainWnd *)m_pMainWnd);
}

INT CEditorApp::RegisterApp()
{
	INT  nIndex;
	INT  nCount;
	CImage  cImage;
	HANDLE  hMutex;
	CVersionInfo  cVersionInfo;
	CMFCToolBarImages  *pImages;
	CMFCToolTipInfo  cToolTipInfo;
	CWelcomeDialog  cWelcomeDialog;

	for (CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7)), InitContextMenuManager(), InitCommonControls(), InitKeyboardManager(), InitTooltipManager(), AfxOleInit(), AfxInitRichEdit(), AfxEnableControlContainer(), EnableTaskbarInteraction(FALSE), EnableHtmlHelp(), cToolTipInfo.m_bVislManagerTheme = TRUE, GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &cToolTipInfo); !(hMutex = CreateMutex((LPSECURITY_ATTRIBUTES)NULL, FALSE, cVersionInfo.QueryFileDescription())) || GetLastError() == ERROR_ALREADY_EXISTS; )
	{
		for (EnumWindows(EnumTopLevelWindows, (LPARAM)(LPCTSTR)GetAppTitle()); hMutex != (HANDLE)NULL; )
		{
			CloseHandle(hMutex);
			break;
		}
		return -1;
	}
	if ((IsInitialized() || cWelcomeDialog.DoModal() == IDOK) && CAccountsApp::RegisterApp() && LoadAccount())
	{
		for (RegisterCustomControls(), RegisterMimicsControls(), InitializeDefaultPrinter(); (pImages = CMFCToolBar::GetImages()); )
		{
			for (cImage.LoadFromResource(GetModuleHandle((LPCTSTR)NULL), IDB_FLOATINGMENUSIMAGELIST), pImages->SetImageSize(CSize(cImage.GetWidth() / (sizeof(nFloatingMenuIDs) / sizeof(UINT)), cImage.GetHeight())); pImages->Load(IDB_FLOATINGMENUSIMAGELIST, (HINSTANCE)NULL, TRUE);)
			{
				for (nIndex = 0, nCount = sizeof(nFloatingMenuIDs) / sizeof(UINT); nIndex < nCount; nIndex++)
				{
					GetCmdMgr()->SetCmdImage(nFloatingMenuIDs[nIndex], nIndex, FALSE);
					continue;
				}
				return TRUE;
			}
			break;
		}
	}
	return FALSE;
}

BOOL CEditorApp::UnregisterApp()
{
	UnregisterCustomControls();
	return CAccountsApp::UnregisterApp();
}

BOOL CEditorApp::RunAccount(CONST CEditorAppCommandLineInfo &cStartupInfo)
{
	CLoginDialog  cLoginDialog;

	if (cStartupInfo.IsValid())
	{
		if (EvaluateAccount(cStartupInfo))
		{
			GetMainWnd()->UpdateLayout();
			GetMainWnd()->LoadEnvironment();
			return TRUE;
		}
		return FALSE;
	}
	if (cLoginDialog.DoModal() == IDOK)
	{
		GetMainWnd()->UpdateLayout();
		GetMainWnd()->LoadEnvironment();
		return TRUE;
	}
	return FALSE;
}

BOOL CEditorApp::EvaluateAccount(CONST CEditorAppCommandLineInfo &cStartupInfo)
{
	INT  nUser;
	INT  nUsers;
	INT  nAccount;
	INT  nAccounts;
	INT  nDatabase;
	INT  nDatabases;
	CDatabases  cDatabases;
	CStringArray  szUsers;
	CUserAccounts  cUserAccounts;
	CAccountToken  cAccountToken;
	CAccountTokens  pAccountTokens;
	CDatabaseProfiles  pDatabaseProfiles;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	for (nAccount = 0, nAccounts = cUserAccounts.EnumAccounts(pAccountTokens); nAccount < nAccounts; nAccount++)
	{
		if (!pAccountTokens.GetAt(nAccount)->GetSpacecraftName().CompareNoCase(cStartupInfo.GetSpacecraft()) && !pAccountTokens.GetAt(nAccount)->GetUserName().Compare(cStartupInfo.GetUser()) && !pAccountTokens.GetAt(nAccount)->GetPassword().Compare(cStartupInfo.GetPassword()))
		{
			for (nDatabase = 0, nDatabases = (cDatabases.SetComputerName(cStartupInfo.GetServer()) && cDatabases.GetDatabases(pDatabaseProfiles)) ? (INT)pDatabaseProfiles.GetSize() : -1, cAccountToken.Copy(pAccountTokens.GetAt(nAccount)); nDatabase < nDatabases; nDatabase++)
			{
				if ((pDatabaseProfileInfo = pDatabaseProfiles.GetAt(nDatabase)) && !pDatabaseProfileInfo->GetName().Compare(cStartupInfo.GetDatabase()) && !pDatabaseProfileInfo->GetSpacecraft().CompareNoCase(cStartupInfo.GetSpacecraft()))
				{
					for (nUser = 0, nUsers = pDatabaseProfileInfo->GetUsers(szUsers); nUser < nUsers; nUser++)
					{
						if (!szUsers.GetAt(nUser).Compare(cStartupInfo.GetUser())) break;
						continue;
					}
					if (nUser < nUsers) break;
				}
			}
			if (nDatabase < nDatabases)
			{
				for (cAccountToken.SetDatabase(cStartupInfo.GetDatabase()), SetAccount(&cAccountToken); !SetDatabase(cStartupInfo.GetServer(), cAccountToken.GetSpacecraftName(), cStartupInfo.GetDatabase()); )
				{
					nAccount = nAccounts;
					break;
				}
				break;
			}
			nAccount = nAccounts;
			break;
		}
	}
	return((nAccount < nAccounts) ? TRUE : FALSE);
}

BOOL CEditorApp::SaveState(LPCTSTR lpszSectionName, CFrameImpl *pFrameImpl)
{
	return TRUE;
}

BOOL CEditorApp::LoadState(LPCTSTR lpszSectionName, CFrameImpl *pFrameImpl)
{
	return TRUE;
}

BOOL CEditorApp::StartNetworkBrowseService()
{
	if (!GetNetworkBrowseService()->Start())
	{
		ShowMessage(SYSTEM_WARNING_NETWORKBROWSESERVICE_START_FAILURE);
		return FALSE;
	}
	return TRUE;
}

BOOL CEditorApp::StopNetworkBrowseService()
{
	if (!GetNetworkBrowseService()->Stop())
	{
		ShowMessage(SYSTEM_WARNING_NETWORKBROWSESERVICE_STOP_FAILURE);
		return FALSE;
	}
	return TRUE;
}

BOOL CEditorApp::SaveCompileBatchProfiles()
{
	CCompileBatches  pBatches;
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return((GetCompileBatchProfiles(pBatches) && pBatches.Map(nProfilesInfo) && cProfile.SetCompileBatchesInfo(nProfilesInfo)) ? TRUE : FALSE);
}

BOOL CEditorApp::LoadCompileBatchProfiles()
{
	CCompileBatches  pBatches;
	CByteArray  nProfilesInfo;
	CProfile  cProfile;

	return((cProfile.GetCompileBatchesInfo(nProfilesInfo) && pBatches.Unmap(nProfilesInfo) && SetCompileBatchProfiles(pBatches)) ? TRUE : FALSE);
}

BOOL CEditorApp::SavePrintProfile()
{
	CByteArray  nProfileInfo;
	CProfile  cProfile;

	return((m_cPrintProfile.Map(nProfileInfo) && cProfile.SetPrintProfileInfo(nProfileInfo)) ? TRUE : FALSE);
}

BOOL CEditorApp::LoadPrintProfile()
{
	CByteArray  nProfileInfo;
	CProfile  cProfile;

	return((cProfile.GetPrintProfileInfo(nProfileInfo) && m_cPrintProfile.Unmap(nProfileInfo)) ? TRUE : (!nProfileInfo.GetSize()));
}

BOOL CEditorApp::ReportID(CONST EVENT_DESCRIPTOR nMessageID)
{
	return GetEditorApp()->ShowMessage(nMessageID);
}

BOOL CEditorApp::ReportMessage(LPCTSTR pszMessage, BOOL bAudition)
{
	return GetEditorApp()->ShowMessage(pszMessage, bAudition);
}

BOOL CEditorApp::HelpTopic(LPCTSTR pszTopic)
{
	return GetEditorApp()->ShowHelp(pszTopic);
}

BOOL CALLBACK CEditorApp::EnumTopLevelWindows(HWND hWnd, LPARAM lParam)
{
	CWnd  *pWnd;
	CString  szText;
	CString  szTitle;

	for (GetWindowText(hWnd, szTitle.GetBufferSetLength(GetWindowTextLength(hWnd)), GetWindowTextLength(hWnd) + 1), szTitle.ReleaseBuffer(), szText = (LPCTSTR)lParam; szTitle.Right(szText.GetLength()) == szText; )
	{
		if ((pWnd = CWnd::FromHandle(GetLastActivePopup(hWnd))))
		{
			for (; pWnd->IsIconic(); )
			{
				ShowWindow(hWnd, SW_RESTORE);
				break;
			}
			pWnd->SetForegroundWindow();
		}
		return FALSE;
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CEditorApp, CAccountsApp)
	//{{AFX_MSG_MAP(CEditorApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditorApp message handlers

BOOL CEditorApp::PreTranslateMessage(MSG *pMsg)
{
	if (IsWindow(GetMainWnd()->GetSafeHwnd()))
	{
		for (; pMsg->message == WM_SETMESSAGESTRING; )
		{
			if (IsInitialized() || pMsg->wParam != AFX_IDS_IDLEMESSAGE) break;
			return TRUE;
		}
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_ESCAPE)
			{
				if (CMMDWnd::IsCompilingMMD())
				{
					CMMDWnd::StopCompilingMMD();
					return TRUE;
				}
				if (CScriptWnd::IsCompilingScript())
				{
					CScriptWnd::StopCompilingScript();
					return TRUE;
				}
				if (CTCProcedureWnd::IsCompilingProcedure())
				{
					CTCProcedureWnd::StopCompilingProcedure();
					return TRUE;
				}
				if (GetDatabase()->IsCompiling())
				{
					GetDatabase()->StopCompiling();
					return TRUE;
				}
			}
		}
	}
	return CAccountsApp::PreTranslateMessage(pMsg);
}
