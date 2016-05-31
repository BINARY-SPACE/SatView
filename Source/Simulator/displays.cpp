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
* 2010/12/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Simulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Specify the IID for the data console document
static const IID  IID_ISimulatorDataConsoleDocument = { 0x8CC497C0,0xA1DF,0x11ce,{ 0x80,0x98,0x00,0xAA,0x00,0x47,0xBE,0x5D } };


static UINT nDataConsoleWndndicators[] =
{
	ID_SEPARATOR,
	ID_DATACONSOLE_PANE_SATELLITE,
	ID_DATACONSOLE_PANE_IODEVICE,
	ID_DATACONSOLE_PANE_IODEVICESTATE
};

static UINT nMessageConsoleWndIndicators[] =
{
	ID_SEPARATOR
};



/////////////////////////////////////////////////////////////////////////////
// CDisplayLockable

CDisplayLockable::CDisplayLockable()
{
	m_pCriticalSection = new CCriticalSection;
}

CDisplayLockable::~CDisplayLockable()
{
	delete m_pCriticalSection;
}

CCriticalSection *CDisplayLockable::GetLock() CONST
{
	return m_pCriticalSection;
}

BOOL CDisplayLockable::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CDisplayLockable::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd

IMPLEMENT_DYNCREATE(CDisplayWnd, CLocaleMDIChildWnd)

CDisplayWnd::CDisplayWnd() : CLocaleMDIChildWnd(), CDisplayLockable()
{
	m_nState = 0;
}

BOOL CDisplayWnd::Start()
{
	return FALSE;
}

BOOL CDisplayWnd::CanStart() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::Suspend()
{
	return FALSE;
}

BOOL CDisplayWnd::CanSuspend() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::IsSuspended() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::Stop()
{
	return FALSE;
}

BOOL CDisplayWnd::CanStop() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::Reload()
{
	return FALSE;
}

BOOL CDisplayWnd::CanReload() CONST
{
	return FALSE;
}

CMainWnd *CDisplayWnd::GetParent() CONST
{
	return((CMainWnd *)CLocaleMDIChildWnd::GetParentFrame());
}

BEGIN_MESSAGE_MAP(CDisplayWnd, CLocaleMDIChildWnd)
	//{{AFX_MSG_MAP(CDisplayWnd)
	ON_WM_MDIACTIVATE()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateContentSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd message handlers

void CDisplayWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	CDocument  *pDocument;

	if (bActivate) GetParent()->UpdateTitle(((pDocument = GetActiveDocument())) ? pDocument->GetTitle() : EMPTYSTRING);
	CLocaleMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CDisplayWnd::OnUpdateContentSave(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleThread thread

IMPLEMENT_DYNCREATE(CSimulatorDataConsoleThread, CThread)

BOOL CSimulatorDataConsoleThread::Start(CSimulatorDataConsoleWnd *pDataConsoleWnd)
{
	return(IsThreadActive() || CreateThread(pDataConsoleWnd));
}

BOOL CSimulatorDataConsoleThread::Stop()
{
	return((DestroyThread() != (DWORD)-1) ? TRUE : FALSE);
}

int CSimulatorDataConsoleThread::Run()
{
	INT  nIndex;
	INT  nCount;
	CTMUnit  *pTMUnit;
	CTMUnits  pTMUnits;
	CTimeTag  tTimeTag;
	CTMTransferUnit  *pTMTransferUnit;
	CTMTransferUnits  pTMTransferUnits;
	CSimulatorDataConsoleWnd  *pDataConsoleWnd = (CSimulatorDataConsoleWnd *)GetThreadInfo();

	while (Wait(0) == WAIT_TIMEOUT)
	{
		if (pDataConsoleWnd->GetData(pTMUnits))
		{
			for (nIndex = 0, nCount = (INT)pTMUnits.GetSize(), tTimeTag = CTimeTag(); nIndex < nCount; nIndex++)
			{
				if ((pTMUnit = pTMUnits.GetAt(nIndex)) != (CTMUnit *)NULL)
				{
					if (Wait((DWORD)max((tTimeTag.GetTime() + pTMUnit->GetTimeTag().GetTime() - CTimeTag().GetTime()) / 1000, 0)) == WAIT_TIMEOUT)
					{
						pTMUnit->SetTimeTag((tTimeTag = tTimeTag.GetTime() + pTMUnit->GetTimeTag().GetTime()));
						pTMUnit->SetQuality(pTMUnit->GetQuality() | TMUNIT_SEQUENCEQUALITY_GOOD);
						pDataConsoleWnd->DistributeData(pTMUnit);
						continue;
					}
				}
				break;
			}
			continue;
		}
		if (pDataConsoleWnd->GetData(pTMTransferUnits))
		{
			for (nIndex = 0, nCount = (INT)pTMTransferUnits.GetSize(), tTimeTag = CTimeTag(); nIndex < nCount; nIndex++)
			{
				if ((pTMTransferUnit = pTMTransferUnits.GetAt(nIndex)) != (CTMTransferUnit *)NULL)
				{
					if (Wait((DWORD)max((tTimeTag.GetTime() + pTMTransferUnit->GetTimeTag().GetTime() - CTimeTag().GetTime()) / 1000, 0)) == WAIT_TIMEOUT)
					{
						pTMTransferUnit->SetTimeTag((tTimeTag = tTimeTag.GetTime() + pTMTransferUnit->GetTimeTag().GetTime()));
						pTMTransferUnit->SetQuality(pTMTransferUnit->GetQuality() | TMUNIT_SEQUENCEQUALITY_GOOD);
						pDataConsoleWnd->DistributeData(pTMTransferUnit);
						continue;
					}
				}
				break;
			}
			continue;
		}
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CSimulatorDataConsoleThread, CThread)
	//{{AFX_MSG_MAP(CSimulatorDataConsoleThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleDocument

IMPLEMENT_DYNCREATE(CSimulatorDataConsoleDocument, CDocument)

CSimulatorDataConsoleDocument::CSimulatorDataConsoleDocument() : CDocument()
{
	return;
}

BEGIN_MESSAGE_MAP(CSimulatorDataConsoleDocument, CDocument)
	//{{AFX_MSG_MAP(CSimulatorDataConsoleDocument)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleDocument message handlers

BOOL CSimulatorDataConsoleDocument::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile  *pFile;
	CString  szData;
	CString  szProlog;
	CString  szMessage;
	CString  szFileName;
	POSITION  lPosition;
	CTMUnits  pTMUnits;
	CFileException  cError;
	CStringTools  cStringTools;
	CTMTransferUnits  pTMTransferUnits;
	CSimulatorDataConsoleView  *pView;

	if ((pFile = GetFile((lstrlen((szFileName = lpszPathName)) <= lstrlen(STRING(IDS_FILEEXTENSION_TXT)) || szFileName.Right(lstrlen(STRING(IDS_FILEEXTENSION_TXT))).CompareNoCase(STRING(IDS_FILEEXTENSION_TXT))) ? (szFileName + STRING(IDS_FILEEXTENSION_TXT)) : szFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &cError)))
	{
		for (lPosition = GetFirstViewPosition(); (pView = (CSimulatorDataConsoleView *)GetNextView(lPosition)); )
		{
			for (szProlog = STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE) + CString(SPACE) + pView->GetDataSource() + CR + EOL; pView->GetDataType() == IODEVICE_DATASERVICE_RAW; )
			{
				szProlog += STRING(IDS_DEVICEDATA_KEYWORD_TYPE);
				szProlog += CString(SPACE) + STRING(IDS_DEVICEDATA_TYPE_RAWDATA);
				break;
			}
			if (pView->GetDataType() == IODEVICE_DATASERVICE_SOURCEPACKETS)
			{
				szProlog += STRING(IDS_DEVICEDATA_KEYWORD_TYPE);
				szProlog += CString(SPACE) + STRING(IDS_DEVICEDATA_TYPE_SOURCEPACKETS);
			}
			if (pView->GetDataType() == IODEVICE_DATASERVICE_TRANSFERFRAMES)
			{
				szProlog += STRING(IDS_DEVICEDATA_KEYWORD_TYPE);
				szProlog += CString(SPACE) + STRING(IDS_DEVICEDATA_TYPE_TRANSFERFRAMES);
			}
			szProlog += CR;
			szProlog += EOL;
			szProlog += STRING(IDS_DEVICEDATA_KEYWORD_FORMAT) + CString(SPACE) + cStringTools.ConvertUIntToString(pView->GetDataFormat()) + CR + EOL;
			szProlog += STRING(IDS_DEVICEDATA_KEYWORD_OBRT) + CString(SPACE) + cStringTools.ConvertUIntToString(pView->GetDataOBRTPerSecond()) + CR + EOL + CR + EOL;
			for (pView->GetWindowText(szData), szMessage = (pView->GetDataType() == IODEVICE_DATASERVICE_SOURCEPACKETS) ? pView->TranslateData(szData, pTMUnits) : pView->TranslateData(szData, pTMTransferUnits); szMessage.IsEmpty(); )
			{
				if (pView->GetDataType() == IODEVICE_DATASERVICE_SOURCEPACKETS)
				{
					pView->SetData(pTMUnits);
					break;
				}
				pView->SetData(pTMTransferUnits);
				break;
			}
			for (szData = szProlog + szData; !szMessage.IsEmpty(); )
			{
				ShowMessage(STRING(IDS_MESSAGETYPE_WARNING), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
				break;
			}
#ifndef UNICODE
			pFile->Write((LPCVOID)(LPCSTR)szData, szData.GetLength()*sizeof(CHAR));
			pView->GetRichEditCtrl().SetModify(FALSE);
			break;
#else
			LPBYTE  pData;
			if ((pData = (LPBYTE)GlobalAlloc(GPTR, szData.GetLength() + 1)))
			{
				WideCharToMultiByte(CP_ACP, 0, szData, -1, (LPSTR)pData, szData.GetLength(), (LPCSTR)NULL, (LPBOOL)NULL);
				pFile->Write(pData, szData.GetLength());
				pView->GetRichEditCtrl().SetModify(FALSE);
				GlobalFree(pData);
				break;
			}
			szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_SAVE_FAILURE), (LPCTSTR)GetTitle());
			ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
			break;
#endif
		}
		pFile->Close();
		delete pFile;
	}
	else
	{
		szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_SAVE_FAILURE), (LPCTSTR)GetTitle());
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
	}
	return(szMessage.IsEmpty());
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleView

IMPLEMENT_DYNCREATE(CSimulatorDataConsoleView, CRichEditView)

CSimulatorDataConsoleView::CSimulatorDataConsoleView() : CRichEditView()
{
	m_bData = FALSE;
	m_nDataType = 0;
	m_nDataFormat = 0;
	m_nDataOBRTPerSecond = 0;
	m_rUpdate.SetRectEmpty();
	m_pCriticalSection = new CCriticalSection;
}

CSimulatorDataConsoleView::~CSimulatorDataConsoleView()
{
	delete m_pCriticalSection;
}

VOID CSimulatorDataConsoleView::SetData(LPCTSTR pszData)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szData = pszData;
}
VOID CSimulatorDataConsoleView::SetData(CONST CTMUnits &pTMUnits)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pTMUnits.Copy(&pTMUnits);
}
VOID CSimulatorDataConsoleView::SetData(CONST CTMTransferUnits &pTMTransferUnits)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pTMTransferUnits.Copy(&pTMTransferUnits);
}

CString CSimulatorDataConsoleView::GetData() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_szData;
}
INT CSimulatorDataConsoleView::GetData(CTMUnits &pTMUnits) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((pTMUnits.Copy(&m_pTMUnits)) ? (INT)pTMUnits.GetSize() : -1);
}
INT CSimulatorDataConsoleView::GetData(CTMTransferUnits &pTMTransferUnits) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((pTMTransferUnits.Copy(&m_pTMTransferUnits)) ? (INT)pTMTransferUnits.GetSize() : -1);
}

CString CSimulatorDataConsoleView::TranslateData(LPCTSTR pszData, CTMUnits &pTMUnits) CONST
{
	INT  nPos;
	INT  nOffset;
	INT  nSkipBytes;
	UINT  nOBRT[3];
	BOOL  bOBRT[3];
	BOOL  bFinalLine;
	CTMUnit  *pTMUnit;
	CString  szMessage;
	CString  szDocument;
	CString  szDataLine;
	CByteArray  nLineData;
	CByteArray  nPacketData;
	CSimulatorDataConsoleDocument  *pDocument;

	for (szDocument = ((pDocument = GetDocument()) && !pDocument->GetTitle().IsEmpty()) ? pDocument->GetTitle() : EMPTYSTRING, pTMUnits.RemoveAll(); m_nDataType == IODEVICE_DATASERVICE_SOURCEPACKETS && (m_nDataFormat == 1 || m_nDataFormat == 2) && m_nDataOBRTPerSecond > 0; )
	{
		for (nPos = 0, nOffset = 0, nSkipBytes = 0, nOBRT[0] = nOBRT[1] = 0, bOBRT[0] = bOBRT[1] = FALSE; ReadDataLine(pszData, nPos, szDataLine, bFinalLine); )
		{
			if (CollectLineData(szDataLine, nOffset, nSkipBytes, nLineData, nOBRT[2], bOBRT[2]))
			{
				if ((nOffset < nPacketData.GetSize() || bFinalLine) && nOffset != (UINT)-1)
				{
					if (bOBRT[1] == TRUE)
					{
						if (bFinalLine)
						{
							nPacketData.SetSize(nOffset);
							nPacketData.Append(nLineData);
						}
						if ((pTMUnit = new CTMUnit))
						{
							pTMUnit->SetData(nPacketData);
							pTMUnit->SetTimeTag((nOBRT[1] >= nOBRT[0]) ? ((1000000 * (TIMETAG)(nOBRT[1] - nOBRT[0])) / (TIMETAG)m_nDataOBRTPerSecond) : (-(1000000 * (TIMETAG)(nOBRT[0] - nOBRT[1])) / (TIMETAG)m_nDataOBRTPerSecond));
							pTMUnit->SetQuality(TMUNIT_DATAQUALITY_GOOD);
							pTMUnits.InsertAt(pTMUnits.GetSize(), pTMUnit, 1);
							nPacketData.RemoveAll();
							nPacketData.Append(nLineData);
							nOffset = (INT)nLineData.GetSize();
							nOBRT[0] = nOBRT[1];
							bOBRT[0] = bOBRT[0];
							nOBRT[1] = (bOBRT[2]) ? nOBRT[2] : 0;
							nOBRT[1] = (bOBRT[2]) ? ((m_nDataFormat == 1) ? ((nOBRT[0] & 0xFFFF0000) | nOBRT[1]) : nOBRT[1]) : 0;
							bOBRT[1] = bOBRT[2];
							continue;
						}
					}
					szMessage.Format((!szDocument.IsEmpty()) ? STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE) : STRING(IDS_MESSAGE_DATACONSOLE_LOAD_UNKNOWN_FAILURE), (LPCTSTR)szDocument);
					break;
				}
				if (nOffset == (UINT)-1)
				{
					szMessage.Format((!szDocument.IsEmpty()) ? STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE) : STRING(IDS_MESSAGE_DATACONSOLE_LOAD_UNKNOWN_FAILURE), (LPCTSTR)szDocument);
					break;
				}
				if (bOBRT[2])
				{
					for (nOBRT[1] = nOBRT[2], nOBRT[1] = (m_nDataFormat == 1) ? ((nOBRT[0] & 0xFFFF0000) | nOBRT[1]) : nOBRT[1], bOBRT[1] = bOBRT[2]; !bOBRT[0]; )
					{
						nOBRT[0] = nOBRT[2];
						bOBRT[0] = bOBRT[2];
						break;
					}
				}
				nPacketData.SetSize(nOffset);
				nPacketData.Append(nLineData);
				nOffset += (INT)nLineData.GetSize();
				continue;
			}
		}
		return szMessage;
	}
	szMessage.Format((!szDocument.IsEmpty()) ? STRING(IDS_MESSAGE_DATACONSOLE_SUPPORT_MISSING) : STRING(IDS_MESSAGE_DATACONSOLE_SUPPORT_UNKNOWN_MISSING), (LPCTSTR)szDocument);
	return szMessage;
}
CString CSimulatorDataConsoleView::TranslateData(LPCTSTR pszData, CTMTransferUnits &pTMTransferUnits) CONST
{
	INT  nPos;
	INT  nOffset;
	INT  nSkipBytes;
	UINT  nOBRT[3];
	BOOL  bOBRT[3];
	BOOL  bFinalLine;
	CString  szMessage;
	CString  szDocument;
	CString  szDataLine;
	CByteArray  nLineData;
	CByteArray  nTransferUnitData;
	CTMTransferUnit  *pTMTransferUnit;
	CSimulatorDataConsoleDocument  *pDocument;

	for (szDocument = ((pDocument = GetDocument()) && !pDocument->GetTitle().IsEmpty()) ? pDocument->GetTitle() : EMPTYSTRING, pTMTransferUnits.RemoveAll(); m_nDataType == IODEVICE_DATASERVICE_TRANSFERFRAMES && (m_nDataFormat == 1 || m_nDataFormat == 2) && m_nDataOBRTPerSecond > 0; )
	{
		for (nPos = 0, nOffset = 0, nSkipBytes = 0, nOBRT[0] = nOBRT[1] = 0, bOBRT[0] = bOBRT[1] = FALSE; ReadDataLine(pszData, nPos, szDataLine, bFinalLine); )
		{
			if (CollectLineData(szDataLine, nOffset, nSkipBytes, nLineData, nOBRT[2], bOBRT[2]))
			{
				if ((nOffset < nTransferUnitData.GetSize() || bFinalLine) && nOffset != (UINT)-1)
				{
					if (bOBRT[1] == TRUE)
					{
						if (bFinalLine)
						{
							nTransferUnitData.SetSize(nOffset);
							nTransferUnitData.Append(nLineData);
						}
						if ((pTMTransferUnit = new CTMTransferUnit))
						{
							pTMTransferUnit->SetData(nTransferUnitData);
							pTMTransferUnit->SetTimeTag((nOBRT[1] >= nOBRT[0]) ? ((1000000 * (TIMETAG)(nOBRT[1] - nOBRT[0])) / (TIMETAG)m_nDataOBRTPerSecond) : 0);
							pTMTransferUnit->SetQuality(TMUNIT_DATAQUALITY_GOOD);
							pTMTransferUnits.InsertAt(pTMTransferUnits.GetSize(), pTMTransferUnit, 1);
							nTransferUnitData.RemoveAll();
							nTransferUnitData.Append(nLineData);
							nOffset = (INT)nLineData.GetSize();
							nOBRT[0] = nOBRT[1];
							bOBRT[0] = bOBRT[0];
							nOBRT[1] = (bOBRT[2]) ? nOBRT[2] : 0;
							nOBRT[1] = (bOBRT[2]) ? ((m_nDataFormat == 1) ? ((nOBRT[0] & 0xFFFF0000) | nOBRT[1]) : nOBRT[1]) : 0;
							bOBRT[1] = bOBRT[2];
							continue;
						}
					}
					szMessage.Format((!szDocument.IsEmpty()) ? STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE) : STRING(IDS_MESSAGE_DATACONSOLE_LOAD_UNKNOWN_FAILURE), (LPCTSTR)szDocument);
					break;
				}
				if (nOffset == (UINT)-1)
				{
					szMessage.Format((!szDocument.IsEmpty()) ? STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE) : STRING(IDS_MESSAGE_DATACONSOLE_LOAD_UNKNOWN_FAILURE), (LPCTSTR)szDocument);
					break;
				}
				if (bOBRT[2])
				{
					for (nOBRT[1] = nOBRT[2], nOBRT[1] = (m_nDataFormat == 1) ? ((nOBRT[0] & 0xFFFF0000) | nOBRT[1]) : nOBRT[1], bOBRT[1] = bOBRT[2]; !bOBRT[0]; )
					{
						nOBRT[0] = nOBRT[2];
						bOBRT[0] = bOBRT[2];
						break;
					}
				}
				nTransferUnitData.SetSize(nOffset);
				nTransferUnitData.Append(nLineData);
				nOffset += (INT)nLineData.GetSize();
				continue;
			}
		}
		return szMessage;
	}
	szMessage.Format((!szDocument.IsEmpty()) ? STRING(IDS_MESSAGE_DATACONSOLE_SUPPORT_MISSING) : STRING(IDS_MESSAGE_DATACONSOLE_SUPPORT_UNKNOWN_MISSING), (LPCTSTR)szDocument);
	return szMessage;
}

CString CSimulatorDataConsoleView::UpdateData()
{
	m_pTMUnits.RemoveAll();
	m_pTMTransferUnits.RemoveAll();
	return((m_nDataType == IODEVICE_DATASERVICE_SOURCEPACKETS) ? TranslateData(m_szData, m_pTMUnits) : TranslateData(m_szData, m_pTMTransferUnits));
}

CString CSimulatorDataConsoleView::GetDataSource() CONST
{
	return m_szDataSource;
}

UINT CSimulatorDataConsoleView::GetDataType() CONST
{
	return m_nDataType;
}

UINT CSimulatorDataConsoleView::GetDataFormat() CONST
{
	return m_nDataFormat;
}

UINT CSimulatorDataConsoleView::GetDataOBRTPerSecond() CONST
{
	return m_nDataOBRTPerSecond;
}

BOOL CSimulatorDataConsoleView::CanSave() CONST
{
	return((GetData().IsEmpty()) ? GetRichEditCtrl().GetModify() : FALSE);
}

CSimulatorDataConsoleWnd *CSimulatorDataConsoleView::GetParent() CONST
{
	return((CSimulatorDataConsoleWnd *)CRichEditView::GetParent());
}

VOID CSimulatorDataConsoleView::FormatLines()
{
	LONG  lCount;
	LONG  nSel[2];
	CString  szData;
	LPCTSTR  pPos[4];
	CHARFORMAT2  cFormat;
	IRichEditOle  *pIRichEditOle;
	ITextDocument  *pITextDocument;

	if ((pIRichEditOle = GetRichEditCtrl().GetIRichEditOle()))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_ISimulatorDataConsoleDocument, (LPVOID *)&pITextDocument)))
		{
			for (pITextDocument->Freeze(&lCount), pITextDocument->Undo(tomSuspend, NULL), pITextDocument->Redo(tomSuspend, NULL), GetRichEditCtrl().GetSel(nSel[0], nSel[1]), GetRichEditCtrl().GetTextRange(0, GetRichEditCtrl().GetTextLength(), szData), pPos[0] = pPos[1] = (LPCTSTR)szData, cFormat.cbSize = sizeof(cFormat), cFormat.dwMask = CFM_COLOR | CFM_BOLD, cFormat.dwEffects = CFE_BOLD, cFormat.crTextColor = VGA_COLOR_GREEN; (pPos[2] = _tcsstr(pPos[1], STRING(IDS_DEVICEDATA_OBRT_BEGINSYMBOL))) && (pPos[3] = _tcsstr(pPos[2], STRING(IDS_DEVICEDATA_OBRT_ENDSYMBOL))); pPos[1] = pPos[3])
			{
				GetRichEditCtrl().SetSel((INT)(pPos[2] - pPos[0]), (INT)(pPos[3] - pPos[0]) + lstrlen(STRING(IDS_DEVICEDATA_OBRT_ENDSYMBOL)));
				GetRichEditCtrl().SetSelectionCharFormat(cFormat);
			}
			GetRichEditCtrl().SetSel(nSel[0], nSel[1]);
			pITextDocument->Undo(tomResume, NULL);
			pITextDocument->Redo(tomResume, NULL);
			pITextDocument->Unfreeze(&lCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}

VOID CSimulatorDataConsoleView::FormatLine(INT nLine)
{
	INT  nOffset;
	LONG  lCount;
	LONG  nSel[2];
	CString  szLine;
	LPCTSTR  pPos[3];
	CHARFORMAT2  cFormat;
	IRichEditOle  *pIRichEditOle;
	ITextDocument  *pITextDocument;

	if ((pIRichEditOle = GetRichEditCtrl().GetIRichEditOle()))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_ISimulatorDataConsoleDocument, (LPVOID *)&pITextDocument)))
		{
			for (pITextDocument->Freeze(&lCount), pITextDocument->Undo(tomSuspend, NULL), pITextDocument->Redo(tomSuspend, NULL), GetRichEditCtrl().GetSel(nSel[0], nSel[1]), cFormat.cbSize = sizeof(cFormat), cFormat.dwMask = CFM_COLOR | CFM_BOLD, cFormat.dwEffects = CFE_AUTOCOLOR, GetRichEditCtrl().SetSel((nOffset = GetRichEditCtrl().LineIndex(nLine)), GetRichEditCtrl().LineIndex(nLine) + GetRichEditCtrl().LineLength(GetRichEditCtrl().LineIndex(nLine))), GetRichEditCtrl().SetSelectionCharFormat(cFormat), GetRichEditCtrl().GetLine(nLine, szLine.GetBufferSetLength(GetRichEditCtrl().LineLength(nOffset) + sizeof(int)), GetRichEditCtrl().LineLength(nOffset) + sizeof(int) + 1), szLine.ReleaseBuffer(), cFormat.dwEffects = CFE_BOLD, cFormat.crTextColor = VGA_COLOR_GREEN; (pPos[1] = _tcsstr((pPos[0] = szLine), STRING(IDS_DEVICEDATA_OBRT_BEGINSYMBOL))) && (pPos[2] = _tcsstr(pPos[1], STRING(IDS_DEVICEDATA_OBRT_ENDSYMBOL))); )
			{
				GetRichEditCtrl().SetSel(nOffset + (INT)(pPos[1] - pPos[0]), nOffset + (INT)(pPos[2] - pPos[0]) + lstrlen(STRING(IDS_DEVICEDATA_OBRT_ENDSYMBOL)));
				GetRichEditCtrl().SetSelectionCharFormat(cFormat);
				break;
			}
			GetRichEditCtrl().SetSel(nSel[0], nSel[1]);
			pITextDocument->Undo(tomResume, NULL);
			pITextDocument->Redo(tomResume, NULL);
			pITextDocument->Unfreeze(&lCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}

BOOL CSimulatorDataConsoleView::ReadDataLine(LPCTSTR pszData, INT &nPos, CString &szDataLine, BOOL &bFinalLine) CONST
{
	INT  nLength;
	LPCTSTR  pPos;

	for (szDataLine.Empty(), nLength = lstrlen(pszData), bFinalLine = TRUE; (pPos = _tcschr(&pszData[nPos], CR)) || (pPos = _tcschr(&pszData[nPos], EOL)); )
	{
		for (_tcsncpy_s(szDataLine.GetBufferSetLength((INT)(pPos - pszData) - nPos), (INT)(pPos - pszData) - nPos + 1, &pszData[nPos], (INT)(pPos - pszData) - nPos), szDataLine.ReleaseBuffer(), nPos = (INT)(pPos - pszData + 1); nPos < nLength; nPos++)
		{
			if (pszData[nPos] != CR  &&  pszData[nPos] != EOL) break;
			continue;
		}
		bFinalLine = (nPos == nLength);
		return TRUE;
	}
	szDataLine = pszData + nPos;
	return !szDataLine.IsEmpty();
}

BOOL CSimulatorDataConsoleView::CollectLineData(LPCTSTR pszDataLine, INT &nOffset, INT &nSkipBytes, CByteArray &nLineData, UINT &nOBRT, BOOL &bOBRT) CONST
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	BOOL  bSkipping;
	BYTE  nNumber;
	TCHAR  szChar;
	LPCTSTR  pPos;
	CString  szDigit[2];
	CStringTools  cStringTools;

	for (nPos = 0, nLength = lstrlen(pszDataLine); (pPos = _tcschr(pszDataLine, STRINGCHAR(IDS_DEVICEDATA_ADDRESS_SEPARATOR))); )
	{
		nOffset = ReadDataOffset(pszDataLine, (nPos = (INT)(pPos - pszDataLine) + 1) - 1);
		nOffset = (nOffset > nSkipBytes  &&  nOffset != (UINT)-1) ? (nOffset - nSkipBytes) : nOffset;
		break;
	}
	for (SkipSpaces(pszDataLine, nPos), bSkipping = FALSE; !_tcsncmp(&pszDataLine[nPos], STRING(IDS_DEVICEDATA_SKIPBYTES_SYMBOL), lstrlen(STRING(IDS_DEVICEDATA_SKIPBYTES_SYMBOL))) && !nOffset; )
	{
		SkipSpaces(pszDataLine, (nPos = nPos + lstrlen(STRING(IDS_DEVICEDATA_SKIPBYTES_SYMBOL))));
		nSkipBytes = (bSkipping) ? (nSkipBytes + 1) : 1;
		bSkipping = TRUE;
	}
	for (nLineData.RemoveAll(), szDigit[0] = cStringTools.ConvertUIntToString(0, 16), szDigit[1] = cStringTools.ConvertUIntToString(10, 16), nNumber = 0, nCount = 0; nPos < nLength; nPos++)
	{
		if (_istdigit((szChar = _totupper(pszDataLine[nPos]))))
		{
			nNumber = 16 * nNumber + __toascii(szChar);
			nNumber -= __toascii(szDigit[0].GetAt(0));
			nLineData.SetAtGrow(nCount / 2, nNumber);
			if ((nCount = nCount + 1) % 2 == 0) nNumber = 0;
			continue;
		}
		if (_istxdigit(szChar))
		{
			nNumber = 16 * nNumber + __toascii(szChar) - __toascii(szDigit[1].GetAt(0)) + 10;
			nLineData.SetAtGrow(nCount / 2, nNumber);
			if ((nCount = nCount + 1) % 2 == 0) nNumber = 0;
			continue;
		}
		if (!_istspace(szChar) && szChar != STRINGCHAR(IDS_DEVICEDATA_OBRT_BEGINSYMBOL) && szChar != STRINGCHAR(IDS_DEVICEDATA_OBRT_ENDSYMBOL)) break;
	}
	for (nLineData.RemoveAt(0, (!bSkipping && !nOffset) ? min(nSkipBytes, nLineData.GetSize()) : 0), nOBRT = 0, bOBRT = FALSE; (pPos = _tcschr(pszDataLine, STRINGCHAR(IDS_DEVICEDATA_OBRT_BEGINSYMBOL))); )
	{
		for (nPos = (INT)(pPos - pszDataLine) + 1; nPos < nLength; nPos++)
		{
			if (_istdigit((szChar = _totupper(pszDataLine[nPos]))))
			{
				nOBRT = 16 * nOBRT + __toascii(szChar);
				nOBRT -= __toascii(szDigit[0].GetAt(0));
				bOBRT = TRUE;
				continue;
			}
			if (_istxdigit(szChar))
			{
				nOBRT = 16 * nOBRT + __toascii(szChar) - __toascii(szDigit[1].GetAt(0)) + 10;
				bOBRT = TRUE;
				continue;
			}
			if (!_istspace(szChar)) break;
		}
		break;
	}
	return(nLineData.GetSize() > 0);
}

UINT CSimulatorDataConsoleView::ReadDataOffset(LPCTSTR pszDataLine, INT nLength) CONST
{
	INT  nPos;
	UINT  nNumber;
	TCHAR  szChar;
	CString  szDigit;
	CStringTools  cStringTools;

	for (SkipSpaces(pszDataLine, (nPos = 0)), szDigit = cStringTools.ConvertUIntToString(0), nNumber = 0; nPos < nLength; nPos++)
	{
		if (_istdigit((szChar = _totupper(pszDataLine[nPos]))))
		{
			nNumber = 10 * nNumber + __toascii(szChar);
			nNumber -= __toascii(szDigit.GetAt(0));
			continue;
		}
		nNumber = (UINT)-1;
		break;
	}
	return nNumber;
}

VOID CSimulatorDataConsoleView::SkipSpaces(LPCTSTR pszDataLine, INT &nPos) CONST
{
	INT  nLength;

	for (nLength = lstrlen(pszDataLine); nPos < nLength; nPos++)
	{
		if (!_istspace(pszDataLine[nPos])) break;
		continue;
	}
}

BOOL CSimulatorDataConsoleView::ReadDataKeyword(LPCTSTR pszData, INT nPos, CString &szValue) CONST
{
	TCHAR  szChar;

	for (szValue.Empty(); nPos < lstrlen(pszData) && nPos >= 0; nPos++)
	{
		if (!_istspace((szChar = pszData[nPos])))
		{
			szValue += szChar;
			continue;
		}
		if (szChar != CR  &&  szChar != EOL)
		{
			if (!szValue.IsEmpty()) szValue += szChar;
			continue;
		}
		break;
	}
	return !szValue.IsEmpty();
}
BOOL CSimulatorDataConsoleView::ReadDataKeyword(LPCTSTR pszData, INT nPos, UINT &nValue) CONST
{
	CString  szValue;

	for (nValue = 0; ReadDataKeyword(pszData, nPos, szValue); )
	{
		nValue = (UINT)_ttoi64(szValue);
		return TRUE;
	}
	return FALSE;
}

BOOL CSimulatorDataConsoleView::DrawPrintDocPage(CDC *pDC, CPrintInfo *pPrintInfo)
{
	CFont  cFont[5];

	return((CalcPrintDocTitleFont(pDC, pPrintInfo->m_rectDraw, cFont[0]) && CalcPrintDocInfoTitleFont(pDC, pPrintInfo->m_rectDraw, cFont[1]) && CalcPrintDocNoticeFont(pDC, pPrintInfo->m_rectDraw, cFont[2], cFont[3]) && CalcPrintDocFooterFont(pDC, pPrintInfo->m_rectDraw, cFont[4])) ? (DrawPrintDocTitle(pDC, pPrintInfo->m_rectDraw, GetPrintDocTitle(), cFont[0]) && DrawPrintDocInfoTitle(pDC, pPrintInfo->m_rectDraw, GetPrintDocInfoTitle(), cFont[1]) && DrawPrintDocNotice(pDC, pPrintInfo->m_rectDraw, GetPrintDocNotice(), cFont[2], cFont[3]) && DrawPrintDocFooter(pDC, pPrintInfo->m_rectDraw, GetPrintDocFooter(pPrintInfo), cFont[4])) : FALSE);
}

BOOL CSimulatorDataConsoleView::DrawPrintDocTitle(CDC *pDC, LPRECT prClip, LPCTSTR pszTitle, CFont &cFont)
{
	CFont  *pOldFont;

	if ((pOldFont = pDC->SelectObject(&cFont)))
	{
		pDC->DrawText(pszTitle, prClip, DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += pDC->GetTextExtent(pszTitle).cy;
		pDC->SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CSimulatorDataConsoleView::DrawPrintDocInfoTitle(CDC *pDC, LPRECT prClip, LPCTSTR pszTitle, CFont &cFont)
{
	CFont  *pOldFont;

	if ((pOldFont = pDC->SelectObject(&cFont)))
	{
		pDC->DrawText(pszTitle, prClip, DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += 4 * pDC->GetTextExtent(pszTitle).cy;
		pDC->SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CSimulatorDataConsoleView::DrawPrintDocNotice(CDC *pDC, LPRECT prClip, LPCTSTR pszNotice, CFont &cFont, CFont &cLogoFont)
{
	INT  nPos;
	CFont  *pOldFont;
	CSize  sizeNotice[3];
	CString  szNotice[3];
	CString  szCopyrightNotice;
	CVersionInfo  cVersionInfo;

	for (szCopyrightNotice = pszNotice, sizeNotice[0].cx = sizeNotice[0].cy = 0, sizeNotice[1].cx = sizeNotice[1].cy = 0; (pOldFont = pDC->SelectObject(&cFont)); )
	{
		szNotice[0] = ((nPos = szCopyrightNotice.Find((szNotice[2] = cVersionInfo.QueryCompanyName()))) >= 0) ? szCopyrightNotice.Left(nPos) : szCopyrightNotice;
		szNotice[1] = (nPos >= 0) ? szCopyrightNotice.Mid(nPos + szNotice[2].GetLength()) : EMPTYSTRING;
		sizeNotice[0] = pDC->GetTextExtent(szNotice[0]);
		sizeNotice[1] = pDC->GetTextExtent(szNotice[1]);
		pDC->SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = pDC->SelectObject(&cLogoFont)))
	{
		sizeNotice[2] = pDC->GetTextExtent(szNotice[2]);
		pDC->SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0) ? pDC->SelectObject(&cFont) : (CFont *)NULL))
	{
		pDC->TextOut(prClip->left, prClip->bottom - sizeNotice[0].cy, (LPCTSTR)szNotice[0]);
		pDC->SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0) ? pDC->SelectObject(&cLogoFont) : (CFont *)NULL))
	{
		pDC->TextOut(prClip->left + sizeNotice[0].cx, prClip->bottom - sizeNotice[2].cy, (LPCTSTR)szNotice[2]);
		pDC->SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[1].cx > 0 && sizeNotice[1].cy > 0) ? pDC->SelectObject(&cFont) : (CFont *)NULL))
	{
		pDC->TextOut(prClip->left + sizeNotice[0].cx + sizeNotice[2].cx, prClip->bottom - sizeNotice[1].cy, (LPCTSTR)szNotice[1]);
		pDC->SelectObject(pOldFont);
	}
	if (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0)
	{
		prClip->bottom -= max(sizeNotice[0].cy, sizeNotice[2].cy);
		return TRUE;
	}
	return FALSE;
}

BOOL CSimulatorDataConsoleView::DrawPrintDocFooter(CDC *pDC, LPRECT prClip, LPCTSTR pszFooter, CFont &cFont)
{
	CFont  *pOldFont;

	if ((pOldFont = pDC->SelectObject(&cFont)))
	{
		pDC->DrawText(pszFooter, prClip, DT_LEFT | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);
		prClip->bottom -= 3 * pDC->GetTextExtent(pszFooter).cy;
		pDC->SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CSimulatorDataConsoleView::CalcPrintDocTitleFont(CDC *pDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)pDC->GetDeviceCaps(HORZRES)) / (double)pDC->GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CSimulatorDataConsoleView::CalcPrintDocInfoTitleFont(CDC *pDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)pDC->GetDeviceCaps(HORZRES)) / (double)pDC->GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CSimulatorDataConsoleView::CalcPrintDocNoticeFont(CDC *pDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)pDC->GetDeviceCaps(HORZRES)) / (double)pDC->GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)pDC->GetDeviceCaps(HORZRES)) / (double)pDC->GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CSimulatorDataConsoleView::CalcPrintDocFooterFont(CDC *pDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)pDC->GetDeviceCaps(HORZRES)) / (double)pDC->GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

CString CSimulatorDataConsoleView::GetPrintDocTitle() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryProductName() + cVersionInfo.QueryFileDescription().Mid(cVersionInfo.QueryInternalName().GetLength());
}

CString CSimulatorDataConsoleView::GetPrintDocInfoTitle() CONST
{
	CString  szTitle;

	GetParent()->GetWindowText(szTitle);
	return szTitle;
}

CString CSimulatorDataConsoleView::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CSimulatorDataConsoleView::GetPrintDocFooter(CONST CPrintInfo *pPrintInfo) CONST
{
	CString  szFooter;
	CTimeKey  tTime;
	DEVMODE  *pDevMode;

	if ((pDevMode = (DEVMODE *)GlobalLock(pPrintInfo->m_pPD->m_pd.hDevMode)))
	{
		szFooter.Format(STRING(IDS_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pDevMode->dmDeviceName, pPrintInfo->m_nCurPage);
		GlobalUnlock(pPrintInfo->m_pPD->m_pd.hDevMode);
		return szFooter;
	}
	szFooter.Format(STRING(IDS_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), STRING(IDS_PRINTDOCUMENT_UNKNOWNDEVICE), pPrintInfo->m_nCurPage);
	return szFooter;
}

CSimulatorDataConsoleDocument *CSimulatorDataConsoleView::GetDocument() const
{
	return((CSimulatorDataConsoleDocument *)m_pDocument);
}

BEGIN_MESSAGE_MAP(CSimulatorDataConsoleView, CRichEditView)
	//{{AFX_MSG_MAP(CSimulatorDataConsoleView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchangeData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleView drawing

void CSimulatorDataConsoleView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleView message handlers

int CSimulatorDataConsoleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	LOGFONT  lfFont;
	CFontTools  cFontTools(ANSI_FIXED_FONT, &lfFont);

	if (CRichEditView::OnCreate(lpCreateStruct) != -1)
	{
		if (m_cFont.CreateFontIndirect(&lfFont)) SetFont(&m_cFont);
		return 0;
	}
	return -1;
}

void CSimulatorDataConsoleView::OnInitialUpdate()
{
	INT  nPos[4];
	CFile  *pFile;
	CString  szData;
	CString  szType;
	CString  szMessage;
	CByteArray  nFileData;
	CFileException  cFileError;
	CSimulatorDataConsoleDocument  *pDocument = GetDocument();

	CRichEditView::OnInitialUpdate();
	for (GetRichEditCtrl().RequestResize(), GetRichEditCtrl().SetEventMask(GetRichEditCtrl().GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE), m_nWordWrap = WrapNone, WrapChanged(); (pFile = pDocument->GetFile(pDocument->GetPathName(), CFile::modeRead | CFile::shareDenyWrite, &cFileError)); )
	{
		nFileData.SetSize((INT_PTR)(pFile->GetLength() + 1));
		if (pFile->Read(nFileData.GetData(), (UINT)pFile->GetLength()) > 0)
		{
			for (; nFileData.GetSize() > 0; )
			{
#ifndef UNICODE
				if (!IsTextUnicode(nFileData.GetData(), (INT)pFile->GetLength(), (LPINT)NULL))
				{
					szData = (LPCSTR)nFileData.GetData();
					break;
				}
				WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)nFileData.GetData(), (INT)(pFile->GetLength() / sizeof(WCHAR)), szData.GetBufferSetLength((INT)(pFile->GetLength() / sizeof(WCHAR))), (INT)(pFile->GetLength() / sizeof(WCHAR)), (LPCSTR)NULL, (LPBOOL)NULL);
				szData.ReleaseBuffer();
				break;
#else
				if (IsTextUnicode(nFileData.GetData(), (INT)pFile->GetLength(), (LPINT)NULL))
				{
					szData = (LPCWSTR)nFileData.GetData();
					break;
				}
				MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)nFileData.GetData(), (INT)pFile->GetLength(), szData.GetBufferSetLength((INT)pFile->GetLength()), (INT)pFile->GetLength());
				szData.ReleaseBuffer();
				break;
#endif
			}
			for (; (nPos[0] = szData.Find(STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE))) >= 0; )
			{
				nPos[0] = (ReadDataKeyword(szData, nPos[0] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE)), m_szDataSource)) ? nPos[0] : -1;
				break;
			}
			if ((nPos[1] = szData.Find(STRING(IDS_DEVICEDATA_KEYWORD_TYPE))) >= 0)
			{
				for (m_nDataType = 0; ReadDataKeyword(szData, nPos[1] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_TYPE)), szType); )
				{
					if (!szType.CompareNoCase(STRING(IDS_DEVICEDATA_TYPE_RAWDATA)))
					{
						m_nDataType = IODEVICE_DATASERVICE_RAW;
						break;
					}
					if (!szType.CompareNoCase(STRING(IDS_DEVICEDATA_TYPE_TRANSFERFRAMES)))
					{
						m_nDataType = IODEVICE_DATASERVICE_TRANSFERFRAMES;
						break;
					}
					if (!szType.CompareNoCase(STRING(IDS_DEVICEDATA_TYPE_SOURCEPACKETS)))
					{
						m_nDataType = IODEVICE_DATASERVICE_SOURCEPACKETS;
						break;
					}
					nPos[1] = -1;
					break;
				}
			}
			for (; (nPos[2] = szData.Find(STRING(IDS_DEVICEDATA_KEYWORD_FORMAT))) >= 0; )
			{
				nPos[2] = (ReadDataKeyword(szData, nPos[2] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_FORMAT)), m_nDataFormat)) ? nPos[2] : -1;
				break;
			}
			for (; (nPos[3] = szData.Find(STRING(IDS_DEVICEDATA_KEYWORD_OBRT))) >= 0; )
			{
				nPos[3] = (ReadDataKeyword(szData, nPos[3] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_OBRT)), m_nDataOBRTPerSecond)) ? nPos[3] : -1;
				break;
			}
			if (nPos[0] >= 0 && nPos[1] >= 0 && nPos[2] >= 0 && nPos[3] >= 0)
			{
				for (nPos[0] = max(nPos[0] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE)), max(nPos[1] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_TYPE)), max(nPos[2] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_FORMAT)), nPos[3] + lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_OBRT))))); (nPos[1] = szData.Mid(nPos[0]).Find(CR)) >= 0; )
				{
					while (nPos[0] + nPos[1] < szData.GetLength())
					{
						if (_istspace(szData.GetAt(nPos[0] + nPos[1])) || szData.GetAt(nPos[0] + nPos[1]) == CR || szData.GetAt(nPos[0] + nPos[1]) == EOL)
						{
							nPos[1]++;
							continue;
						}
						break;
					}
					break;
				}
				for (SetWindowText((szData = szData.Mid(nPos[0] + nPos[1]))), m_pTMUnits.RemoveAll(), m_pTMTransferUnits.RemoveAll(), szMessage = (m_nDataType == IODEVICE_DATASERVICE_SOURCEPACKETS) ? TranslateData(szData, m_pTMUnits) : TranslateData(szData, m_pTMTransferUnits); !szMessage.IsEmpty(); )
				{
					ShowMessage(STRING(IDS_MESSAGETYPE_WARNING), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
					break;
				}
			}
			else
			{
				if (nPos[0] < 0)
				{
					szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_KEYWORD_MISSING), CString(STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE)).Left(lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_SATELLITE)) - 1), (LPCTSTR)pDocument->GetTitle());
					ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
				}
				if (nPos[1] < 0)
				{
					szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_KEYWORD_MISSING), CString(STRING(IDS_DEVICEDATA_KEYWORD_TYPE)).Left(lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_TYPE)) - 1), (LPCTSTR)pDocument->GetTitle());
					ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
				}
				if (nPos[2] < 0)
				{
					szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_KEYWORD_MISSING), CString(STRING(IDS_DEVICEDATA_KEYWORD_FORMAT)).Left(lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_FORMAT)) - 1), (LPCTSTR)pDocument->GetTitle());
					ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
				}
				if (nPos[3] < 0)
				{
					szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_KEYWORD_MISSING), CString(STRING(IDS_DEVICEDATA_KEYWORD_OBRT)).Left(lstrlen(STRING(IDS_DEVICEDATA_KEYWORD_OBRT)) - 1), (LPCTSTR)pDocument->GetTitle());
					ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
				}
			}
		}
		else
		{
			szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE), (LPCTSTR)pDocument->GetTitle());
			ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
		}
		pFile->Close();
		delete pFile;
		break;
	}
	if (!pFile)
	{
		szMessage.Format(STRING(IDS_MESSAGE_DATACONSOLE_LOAD_FAILURE), (LPCTSTR)pDocument->GetTitle());
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
	}
}

BOOL CSimulatorDataConsoleView::OnEditchangeData()
{
	CString  szData;
	CSimulatorDataConsoleDocument  *pDocument = GetDocument();

	for (GetWindowText(szData); szData.GetLength() > 0; )
	{
		SetData(szData);
		break;
	}
	for (GetParent()->UpdateAllPanes(pDocument, GetRichEditCtrl().GetTextLength()); !m_bData; )
	{
		SetTimer(SIMULATORDATACONSOLEVIEW_DEVICEDATA_TIMERID, SIMULATORDATACONSOLEVIEW_DEVICEDATA_TIMEOUT, NULL);
		return FALSE;
	}
	FormatLine(GetRichEditCtrl().LineFromChar(GetRichEditCtrl().LineIndex()));
	return FALSE;
}

void CSimulatorDataConsoleView::OnTimer(UINT_PTR nTimerID)
{
	for (; nTimerID == SIMULATORDATACONSOLEVIEW_DEVICEDATA_TIMERID; )
	{
		if (m_bData)
		{
			KillTimer(nTimerID);
			break;
		}
		if (GetRichEditCtrl().LineIndex(GetRichEditCtrl().GetLineCount() - 1) >= 0)
		{
			CHourglassCursor  cCursor;
			KillTimer(nTimerID);
			FormatLines();
			m_bData = TRUE;
		}
		break;
	}
	CRichEditView::OnTimer(nTimerID);
}

void CSimulatorDataConsoleView::OnPrint(CDC *pDC, CPrintInfo *pInfo)
{
	INT  dx, dy;
	INT  nIndex;
	INT  nScale;
	UINT  nPage;
	FORMATRANGE  fr;

	for (DrawPrintDocPage(pDC, pInfo), dx = GetPaperSize().cx / pDC->GetDeviceCaps(HORZRES), dy = GetPaperSize().cy / pDC->GetDeviceCaps(VERTRES), nScale = max((100 * pDC->GetDeviceCaps(PHYSICALOFFSETX)) / pDC->GetDeviceCaps(HORZRES), (100 * pDC->GetDeviceCaps(PHYSICALOFFSETY)) / pDC->GetDeviceCaps(VERTRES)), ScaleWindowExtEx(pDC->m_hDC, 100, 100 - nScale, 100, 100 - nScale, (LPSIZE)NULL), ScaleWindowExtEx(pDC->m_hDC, ::GetDeviceCaps(pDC->m_hDC, LOGPIXELSX), ::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSX), ::GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), ::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSY), (LPSIZE)NULL), fr.hdc = pDC->m_hDC, fr.hdcTarget = pDC->m_hAttribDC, fr.rcPage = GetPageRect(), fr.rc = GetPrintRect(), fr.rc.top += pInfo->m_rectDraw.top*dy, fr.rc.bottom -= (pDC->GetDeviceCaps(VERTRES) - pInfo->m_rectDraw.bottom)*dy, fr.chrg.cpMin = (long)m_aPageStart[(nPage = pInfo->m_nCurPage) - 1], fr.chrg.cpMax = -1; (nIndex = GetRichEditCtrl().FormatRange(&fr, TRUE)) >= GetTextLengthEx(GTL_PRECISE | GTL_NUMCHARS); )
	{
		pInfo->SetMaxPage(nPage);
		break;
	}
	if (nPage == (UINT)m_aPageStart.GetSize() && nIndex < GetTextLengthEx(GTL_PRECISE | GTL_NUMCHARS)) m_aPageStart.Add(nIndex);
	ScaleWindowExtEx(pDC->m_hDC, 100 - nScale, 100, 100 - nScale, 100, (LPSIZE)NULL);
}

void CSimulatorDataConsoleView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSimulatorDataConsoleView::OnPreparePrinting(CPrintInfo *pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CSimulatorDataConsoleView::OnDestroy()
{
	m_cFont.DeleteObject();
	CRichEditView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleWnd

IMPLEMENT_DYNCREATE(CSimulatorDataConsoleWnd, CDisplayWnd)

CSimulatorDataConsoleWnd::CSimulatorDataConsoleWnd() : CDisplayWnd()
{
	m_nState = DATACONSOLE_STATE_READY;
}

BOOL CSimulatorDataConsoleWnd::Start()
{
	CString  szTitle;
	CString  szMessage;
	CIODevice  cIODevice;
	CStringArray  szClients;

	if (GetParent()->GetIODevice(&cIODevice))
	{
		if (!m_cIODevice.Compare(&cIODevice))
		{
			GetWindowText(szTitle);
			szMessage.Format(STRING(IDS_MESSAGE_UPDATE_DATACONSOLE), (LPCTSTR)szTitle);
			ShowMessage(STRING(IDS_MESSAGETYPE_SUCCESS), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
			m_cIODevice.Copy(&cIODevice);
		}
	}
	if (m_cIODevice.Open())
	{
		if (!m_cIODevice.IsSuspended())
		{
			for (m_cIODevice.Initialize((GetView()->GetDataType() == IODEVICE_DATASERVICE_SOURCEPACKETS) ? ((m_cIODevice.GetCapabilities() & ~(IODEVICE_TYPE_CLIENT | IODEVICE_DATASERVICE_RAW | IODEVICE_DATASERVICE_TRANSFERFRAMES)) | IODEVICE_TYPE_SERVER | IODEVICE_DATASERVICE_SOURCEPACKETS) : ((m_cIODevice.GetCapabilities() & ~(IODEVICE_TYPE_CLIENT | IODEVICE_DATASERVICE_RAW | IODEVICE_DATASERVICE_SOURCEPACKETS)) | IODEVICE_TYPE_SERVER | IODEVICE_DATASERVICE_TRANSFERFRAMES)), m_cIODevice.MonitorDeviceLogins(IODEVICE_LOGIN_SUCCESS | IODEVICE_LOGIN_FAILURE | IODEVICE_LOGOUT_SUCCESS, TrackIODeviceLogins, this); m_cIODevice.Start(); )
			{
				for (m_nState = DATACONSOLE_STATE_RUNNING; GetClients(szClients) > 0; )
				{
					StartDataDistribution();
					break;
				}
				szMessage.Format(STRING(IDS_DEVICEINFORMATION_START), (LPCTSTR)m_cIODevice.GetDeviceName());
				ShowMessage(STRING(IDS_MESSAGETYPE_SUCCESS), m_cIODevice.GetDeviceBrand(), szMessage);
				UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
				return TRUE;
			}
			ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), STRING(IDS_DEVICEERROR_GENERAL));
			UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
			return FALSE;
		}
		if (m_cIODevice.Resume())
		{
			for (m_nState = DATACONSOLE_STATE_RUNNING; GetClients(szClients) > 0; )
			{
				StartDataDistribution();
				break;
			}
			szMessage.Format(STRING(IDS_DEVICEINFORMATION_START), (LPCTSTR)m_cIODevice.GetDeviceName());
			ShowMessage(STRING(IDS_MESSAGETYPE_SUCCESS), m_cIODevice.GetDeviceBrand(), szMessage);
			UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
			return TRUE;
		}
		szMessage.Format(STRING(IDS_DEVICEERROR_START), (LPCTSTR)m_cIODevice.GetDeviceName());
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), m_cIODevice.GetDeviceBrand(), szMessage);
		UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
		m_cIODevice.Close();
		return FALSE;
	}
	ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), STRING(IDS_DEVICEERROR_GENERAL));
	UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
	return FALSE;
}

BOOL CSimulatorDataConsoleWnd::CanStart() CONST
{
	return((m_nState != DATACONSOLE_STATE_NONE  &&  m_nState != DATACONSOLE_STATE_RUNNING) ? TRUE : FALSE);
}

BOOL CSimulatorDataConsoleWnd::Suspend()
{
	CString  szMessage;

	if (m_cIODevice.Suspend())
	{
		m_nState = DATACONSOLE_STATE_SUSPENDED;
		szMessage.Format(STRING(IDS_DEVICEINFORMATION_SUSPEND), (LPCTSTR)m_cIODevice.GetDeviceName());
		ShowMessage(STRING(IDS_MESSAGETYPE_SUCCESS), m_cIODevice.GetDeviceBrand(), szMessage);
		UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
		return TRUE;
	}
	if (!m_cIODevice.GetDeviceBrand().IsEmpty() && !m_cIODevice.GetDeviceName().IsEmpty())
	{
		szMessage.Format(STRING(IDS_DEVICEERROR_SUSPEND), (LPCTSTR)m_cIODevice.GetDeviceName());
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), m_cIODevice.GetDeviceBrand(), szMessage);
		UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
		return FALSE;
	}
	ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), STRING(IDS_DEVICEERROR_GENERAL));
	UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
	return FALSE;
}

BOOL CSimulatorDataConsoleWnd::CanSuspend() CONST
{
	return((m_nState == DATACONSOLE_STATE_RUNNING) ? TRUE : FALSE);
}

BOOL CSimulatorDataConsoleWnd::IsSuspended() CONST
{
	return((m_nState == DATACONSOLE_STATE_SUSPENDED) ? TRUE : FALSE);
}

BOOL CSimulatorDataConsoleWnd::Stop()
{
	CString  szMessage;

	StopDataDistribution();
	if (m_cIODevice.Stop())
	{
		m_nState = DATACONSOLE_STATE_STOPPED;
		szMessage.Format(STRING(IDS_DEVICEINFORMATION_STOP), (LPCTSTR)m_cIODevice.GetDeviceName());
		ShowMessage(STRING(IDS_MESSAGETYPE_SUCCESS), m_cIODevice.GetDeviceBrand(), szMessage);
		UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
		m_cIODevice.Close();
		return TRUE;
	}
	if (!m_cIODevice.GetDeviceBrand().IsEmpty() && !m_cIODevice.GetDeviceName().IsEmpty())
	{
		szMessage.Format(STRING(IDS_DEVICEERROR_STOP), (LPCTSTR)m_cIODevice.GetDeviceName());
		ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), m_cIODevice.GetDeviceBrand(), szMessage);
		UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
		m_cIODevice.Close();
		return FALSE;
	}
	ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), STRING(IDS_DEVICEERROR_GENERAL));
	UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, TranslateDeviceState());
	m_cIODevice.Close();
	return FALSE;
}

BOOL CSimulatorDataConsoleWnd::CanStop() CONST
{
	return((m_nState == DATACONSOLE_STATE_RUNNING) ? TRUE : FALSE);
}

BOOL CSimulatorDataConsoleWnd::Reload()
{
	CString  szMessage;
	CSimulatorDataConsoleView  *pView;

	if ((pView = GetView()))
	{
		for (szMessage = pView->UpdateData(); !szMessage.IsEmpty(); )
		{
			ShowMessage(STRING(IDS_MESSAGETYPE_ERROR), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSimulatorDataConsoleWnd::CanReload() CONST
{
	return TRUE;
}

BOOL CSimulatorDataConsoleWnd::StartDataDistribution()
{
	return m_cDataDeliveryThread.Start(this);
}

BOOL CSimulatorDataConsoleWnd::DistributeData(CONST CTMUnit *pTMUnit)
{
	return(m_cIODevice.Send(*pTMUnit) >= 0);
}
BOOL CSimulatorDataConsoleWnd::DistributeData(CONST CTMTransferUnit *pTMTransferUnit)
{
	return(m_cIODevice.Send(*pTMTransferUnit) >= 0);
}

BOOL CSimulatorDataConsoleWnd::StopDataDistribution()
{
	return m_cDataDeliveryThread.Stop();
}

INT CSimulatorDataConsoleWnd::GetData(CTMUnits &pTMUnits) CONST
{
	CSimulatorDataConsoleView  *pView;

	for (pTMUnits.RemoveAll(); (pView = GetView()); )
	{
		pView->GetData(pTMUnits);
		break;
	}
	return((INT)pTMUnits.GetSize());
}
INT CSimulatorDataConsoleWnd::GetData(CTMTransferUnits &pTMTransferUnits) CONST
{
	CSimulatorDataConsoleView  *pView;

	for (pTMTransferUnits.RemoveAll(); (pView = GetView()); )
	{
		pView->GetData(pTMTransferUnits);
		break;
	}
	return((INT)pTMTransferUnits.GetSize());
}

INT CSimulatorDataConsoleWnd::GetClients(CStringArray &szClients) CONST
{
	CTimeTagArray  tClients;

	return GetClients(szClients, tClients);
}
INT CSimulatorDataConsoleWnd::GetClients(CStringArray &szClients, CTimeTagArray &tClients) CONST
{
	CSingleLock  cLock(GetLock(), TRUE);

	szClients.Copy(m_szIODeviceClients);
	tClients.Copy(m_tIODeviceClients);
	return((INT)szClients.GetSize());
}

VOID CSimulatorDataConsoleWnd::UpdateAllPanes(CDocument *pDocument, INT cbDocument)
{
	CString  szPane[4];
	CString  szMessage;
	CStringTools  cStringTools;

	for (szPane[0].Format(STRING(IDS_STATUSBAR_SATELLITEDATASIZE), (LPCTSTR)cStringTools.ConvertIntToStructuredString(cbDocument)), szPane[1] = SPACE + (szPane[2] = STRING(IDS_STATUSBAR_SATELLITEDATANONE)) + SPACE; pDocument != (CDocument *)NULL && !pDocument->GetTitle().IsEmpty(); )
	{
		szPane[1] = (!pDocument->GetPathName().IsEmpty()) ? (SPACE + (szPane[2] = pDocument->GetTitle()) + SPACE) : szPane[1];
		break;
	}
	if (m_wndStatusBar.GetPaneText(m_wndStatusBar.CommandToIndex(ID_DATACONSOLE_PANE_SATELLITE)) != szPane[1])
	{
		szMessage.Format((szPane[1] == SPACE + CString(STRING(IDS_STATUSBAR_SATELLITEDATANONE)) + SPACE) ? STRING(IDS_MESSAGE_NEW_DATACONSOLE) : STRING(IDS_MESSAGE_OPEN_DATACONSOLE), (LPCTSTR)szPane[2]);
		ShowMessage(STRING(IDS_MESSAGETYPE_INFORMATIONAL), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
	}
	UpdatePane(0, szPane[0]);
	UpdatePane(ID_DATACONSOLE_PANE_SATELLITE, szPane[1]);
	UpdatePane(ID_DATACONSOLE_PANE_IODEVICE, (szPane[2] = SPACE + GetIODevice() + SPACE));
	UpdatePane(ID_DATACONSOLE_PANE_IODEVICESTATE, (szPane[3] = (m_nState == DATACONSOLE_STATE_READY) ? (SPACE + CString(STRING(IDS_DEVICESTATE_READY)) + SPACE) : ((m_nState == DATACONSOLE_STATE_RUNNING) ? (SPACE + CString(STRING(IDS_DEVICESTATE_RUNNING)) + SPACE) : ((m_nState == DATACONSOLE_STATE_SUSPENDED) ? (SPACE + CString(STRING(IDS_DEVICESTATE_SUSPENDED)) + SPACE) : ((m_nState == DATACONSOLE_STATE_STOPPED) ? (SPACE + CString(STRING(IDS_DEVICESTATE_STOPPED)) + SPACE) : (SPACE + CString(STRING(IDS_DEVICESTATE_UNKNOWN)) + SPACE))))));
}

VOID CSimulatorDataConsoleWnd::UpdatePane(UINT nPaneID, LPCTSTR pszText)
{
	CString  szText(pszText);

	for (m_wndStatusBar.SetPaneText((nPaneID != 0) ? m_wndStatusBar.CommandToIndex(nPaneID) : 0, (szText = SPACE + szText.Trim() + SPACE)); nPaneID != 0; )
	{
		m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(nPaneID), nPaneID, SBPS_NORMAL, CalcPaneExtent(szText).cx);
		break;
	}
}

CSimulatorDataConsoleView *CSimulatorDataConsoleWnd::GetView() CONST
{
	return((CSimulatorDataConsoleView *)CDisplayWnd::GetActiveView());
}

VOID CALLBACK CSimulatorDataConsoleWnd::TrackIODeviceLogins(UINT nFlags, LPCTSTR pszClient, TIMETAG tConnectTime, LPVOID pData)
{
	INT  nClient;
	INT  nClients;
	CString  szClient;
	CString  szMessage;
	CSimulatorDataConsoleWnd  *pDataConsoleWnd = (CSimulatorDataConsoleWnd *)pData;
	CSingleLock  cLock(pDataConsoleWnd->GetLock(), TRUE);

	if (nFlags & IODEVICE_LOGIN_SUCCESS)
	{
		for (nClient = 0, nClients = (INT)pDataConsoleWnd->m_szIODeviceClients.GetSize(); nClient < nClients; nClient++)
		{
			if (!pDataConsoleWnd->m_szIODeviceClients.GetAt(nClient).CompareNoCase(pszClient) && pDataConsoleWnd->m_tIODeviceClients.GetAt(nClient) == tConnectTime) break;
			continue;
		}
		if (nClient == nClients)
		{
			for (pDataConsoleWnd->m_szIODeviceClients.Add(pszClient), pDataConsoleWnd->m_tIODeviceClients.Add(tConnectTime); pDataConsoleWnd->m_nState == DATACONSOLE_STATE_RUNNING; )
			{
				pDataConsoleWnd->StartDataDistribution();
				break;
			}
		}
		for (nClient = 0, nClients = (INT)pDataConsoleWnd->m_szIODeviceLogins.GetSize(); nClient < nClients; nClient++)
		{
			if (!pDataConsoleWnd->m_szIODeviceLogins.GetAt(nClient).CompareNoCase(pszClient))
			{
				pDataConsoleWnd->m_szIODeviceLogins.RemoveAt(nClient);
				continue;
			}
		}
		for (szMessage.Format(STRING(IDS_MESSAGE_CLIENT_LOGIN_SUCCESS), ((szClient = pDataConsoleWnd->TranslateToClientName(pszClient)).IsEmpty()) ? pDataConsoleWnd->TranslateToClientAddress(pszClient) : szClient, (LPCTSTR)pDataConsoleWnd->m_cIODevice.GetDeviceName()); nFlags & IODEVICE_LOGINOUT_AUDIT; )
		{
			ShowMessage(STRING(IDS_MESSAGETYPE_SUCCESS), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
			break;
		}
	}
	if (nFlags & IODEVICE_LOGIN_FAILURE)
	{
		for (nClient = 0, nClients = (INT)pDataConsoleWnd->m_szIODeviceClients.GetSize(); nClient < nClients; nClient++)
		{
			if (!pDataConsoleWnd->m_szIODeviceClients.GetAt(nClient).CompareNoCase(pszClient) && pDataConsoleWnd->m_tIODeviceClients.GetAt(nClient) == tConnectTime)
			{
				pDataConsoleWnd->m_szIODeviceClients.RemoveAt(nClient);
				pDataConsoleWnd->m_tIODeviceClients.RemoveAt(nClient);
				break;
			}
		}
		for (nClient = 0, nClients = (INT)pDataConsoleWnd->m_szIODeviceLogins.GetSize(); nClient < nClients; nClient++)
		{
			if (!pDataConsoleWnd->m_szIODeviceLogins.GetAt(nClient).CompareNoCase(pszClient)) break;
			continue;
		}
		if (nClient == nClients)
		{
			for (szMessage.Format(STRING(IDS_MESSAGE_CLIENT_LOGIN_FAILURE), ((szClient = pDataConsoleWnd->TranslateToClientName(pszClient)).IsEmpty()) ? pDataConsoleWnd->TranslateToClientAddress(pszClient) : szClient, (LPCTSTR)pDataConsoleWnd->m_cIODevice.GetDeviceName()), pDataConsoleWnd->m_szIODeviceLogins.Add(pszClient); nFlags & IODEVICE_LOGINOUT_AUDIT; )
			{
				ShowMessage(STRING(IDS_MESSAGETYPE_INFORMATIONAL), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
				break;
			}
		}
		return;
	}
	if (nFlags & IODEVICE_LOGOUT_SUCCESS)
	{
		for (nClient = 0, nClients = (INT)pDataConsoleWnd->m_szIODeviceClients.GetSize(); nClient < nClients; nClient++)
		{
			if (!pDataConsoleWnd->m_szIODeviceClients.GetAt(nClient).CompareNoCase(pszClient) && pDataConsoleWnd->m_tIODeviceClients.GetAt(nClient) == tConnectTime) break;
			continue;
		}
		if (nClient < nClients)
		{
			for (pDataConsoleWnd->m_szIODeviceClients.RemoveAt(nClient), pDataConsoleWnd->m_tIODeviceClients.RemoveAt(nClient); nClients == 1; )
			{
				pDataConsoleWnd->StopDataDistribution();
				break;
			}
		}
		for (nClient = 0, nClients = (INT)pDataConsoleWnd->m_szIODeviceLogins.GetSize(); nClient < nClients; nClient++)
		{
			if (!pDataConsoleWnd->m_szIODeviceLogins.GetAt(nClient).CompareNoCase(pszClient))
			{
				pDataConsoleWnd->m_szIODeviceLogins.RemoveAt(nClient);
				continue;
			}
		}
		for (szMessage.Format(STRING(IDS_MESSAGE_CLIENT_LOGOUT_SUCCESS), ((szClient = pDataConsoleWnd->TranslateToClientName(pszClient)).IsEmpty()) ? pDataConsoleWnd->TranslateToClientAddress(pszClient) : szClient, (LPCTSTR)pDataConsoleWnd->m_cIODevice.GetDeviceName()); nFlags & IODEVICE_LOGINOUT_AUDIT; )
		{
			ShowMessage(STRING(IDS_MESSAGETYPE_SUCCESS), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
			break;
		}
	}
}

CString CSimulatorDataConsoleWnd::TranslateDeviceState() CONST
{
	return TranslateDeviceState(m_nState);
}
CString CSimulatorDataConsoleWnd::TranslateDeviceState(UINT nState) CONST
{
	CString  szState(STRING(IDS_DEVICESTATE_UNKNOWN));

	if (nState & DATACONSOLE_STATE_READY) szState = STRING(IDS_DEVICESTATE_READY);
	if (nState & DATACONSOLE_STATE_RUNNING) szState = STRING(IDS_DEVICESTATE_RUNNING);
	if (nState & DATACONSOLE_STATE_SUSPENDED) szState = STRING(IDS_DEVICESTATE_SUSPENDED);
	if (nState & DATACONSOLE_STATE_STOPPED) szState = STRING(IDS_DEVICESTATE_STOPPED);
	return szState;
}

CString CSimulatorDataConsoleWnd::TranslateToClientName(LPCTSTR pszFullName) CONST
{
	INT  nPos;
	CString  szFullName(pszFullName);

	return(((nPos = szFullName.Find(EOL)) >= 0) ? szFullName.Left(nPos) : szFullName);
}

CString CSimulatorDataConsoleWnd::TranslateToClientAddress(LPCTSTR pszFullName) CONST
{
	INT  nPos;
	CString  szFullName(pszFullName);

	return(((nPos = szFullName.Find(EOL)) >= 0) ? szFullName.Mid(nPos + 1) : EMPTYSTRING);
}

CSize CSimulatorDataConsoleWnd::CalcPaneExtent(LPCTSTR pszText)
{
	CDC  *pDC;
	CFont  *pOldFont;
	CSize  size(0, 0);

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(m_wndStatusBar.GetFont())))
		{
			size = pDC->GetTextExtent(pszText);
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
	return size;
}

BEGIN_MESSAGE_MAP(CSimulatorDataConsoleWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CSimulatorDataConsoleWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateContentSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleWndmessage handlers

int CSimulatorDataConsoleWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE))
		{
			szMessage.Format(STRING(IDS_STATUSBAR_SATELLITEDATASIZE), (LPCTSTR)cStringTools.ConvertUIntToStructuredString(UINT_MAX));
			m_wndStatusBar.SetIndicators(nDataConsoleWndndicators, sizeof(nDataConsoleWndndicators) / sizeof(UINT));
			m_wndStatusBar.SetPaneInfo(0, nDataConsoleWndndicators[0], SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneExtent(szMessage).cx);
			UpdateAllPanes();
			return 0;
		}
	}
	return -1;
}

void CSimulatorDataConsoleWnd::OnDestroy()
{
	CString  szPane;
	CString  szMessage;

	for (; m_cIODevice.IsSuspended(); )
	{
		m_cIODevice.Resume();
		break;
	}
	for (; CanStop(); )
	{
		Stop();
		break;
	}
	for (szPane = m_wndStatusBar.GetPaneText(m_wndStatusBar.CommandToIndex(ID_DATACONSOLE_PANE_SATELLITE)); !szPane.IsEmpty(); )
	{
		szPane.TrimLeft();
		szPane.TrimRight();
		break;
	}
	szMessage.Format(STRING(IDS_MESSAGE_CLOSE_DATACONSOLE), (LPCTSTR)szPane);
	ShowMessage(STRING(IDS_MESSAGETYPE_INFORMATIONAL), STRING(IDS_MESSAGESOURCE_DATACONSOLE), szMessage);
	CDisplayWnd::OnDestroy();
}

void CSimulatorDataConsoleWnd::OnUpdateContentSave(CCmdUI *pCmdUI)
{
	CSimulatorDataConsoleView  *pView;

	pCmdUI->Enable(((pView = (CSimulatorDataConsoleView *)GetActiveView())) ? pView->GetRichEditCtrl().GetModify() : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleDocument

IMPLEMENT_DYNCREATE(CSimulatorMessagesConsoleDocument, CDocument)

CSimulatorMessagesConsoleDocument::CSimulatorMessagesConsoleDocument() : CDocument()
{
	return;
}

CSimulatorMessagesConsoleDocument::~CSimulatorMessagesConsoleDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleView

IMPLEMENT_DYNCREATE(CSimulatorMessagesConsoleView, CListView)

CSimulatorMessagesConsoleView::CSimulatorMessagesConsoleView() : CListView()
{
	return;
}

VOID CSimulatorMessagesConsoleView::ShowMessage(LPCTSTR pszMessage)
{
	ShowMessage(STRING(IDS_MESSAGETYPE_NONE), STRING(IDS_MESSAGESOURCE_NONE), pszMessage);
}
VOID CSimulatorMessagesConsoleView::ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage)
{
	ShowMessage(pszType, STRING(IDS_MESSAGESOURCE_NONE), pszMessage);
}
VOID CSimulatorMessagesConsoleView::ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage)
{
	INT  nIndex;
	CTimeKey  tTime;

	if (Listview_InsertText(&GetListCtrl(), (nIndex = GetListCtrl().GetItemCount()), tTime.FormatGmt()))
	{
		Listview_SetText(&GetListCtrl(), nIndex, FindColumnIndex(STRING(IDS_MESSAGESWINDOW_TITLEITEM_TYPE)), pszType);
		Listview_SetText(&GetListCtrl(), nIndex, FindColumnIndex(STRING(IDS_MESSAGESWINDOW_TITLEITEM_SOURCE)), pszSource);
		Listview_SetText(&GetListCtrl(), nIndex, FindColumnIndex(STRING(IDS_MESSAGESWINDOW_TITLEITEM_MESSAGE)), pszMessage);
		Listview_SetCurText(&GetListCtrl(), nIndex);
		GetListCtrl().EnsureVisible(nIndex, TRUE);
	}
}

INT CSimulatorMessagesConsoleView::GetMessageCount() CONST
{
	return GetListCtrl().GetItemCount();
}

INT CSimulatorMessagesConsoleView::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nIndex;
	INT  nWidth;
	CString  szColumn;

	for (nIndex = 0; Listview_GetColumn(&GetListCtrl(), nIndex, szColumn, nWidth); nIndex++)
	{
		if (szColumn == pszColumn) return nIndex;
		continue;
	}
	return 0;
}

CSize CSimulatorMessagesConsoleView::CalcColumnExtent(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nDevice;
	INT  nDevices;
	CSize  size;
	CStringArray  szDevices;

	if ((pDC = GetDC()))
	{
		for (size.cx = LVSCW_AUTOSIZE_USEHEADER, size.cy = -1; !lstrcmp(pszColumn, STRING(IDS_MESSAGESWINDOW_TITLEITEM_TIME)); )
		{
			size.cx = pDC->GetTextExtent(SPACE + CTimeKey().FormatGmt() + SPACE).cx;
			break;
		}
		if (!lstrcmp(pszColumn, STRING(IDS_MESSAGESWINDOW_TITLEITEM_TYPE)))
		{
			size.cx = pDC->GetTextExtent(SPACE + CString(STRING(IDS_MESSAGETYPE_INFORMATIONAL)) + SPACE).cx;
			size.cx = max(pDC->GetTextExtent(SPACE + CString(STRING(IDS_MESSAGETYPE_SUCCESS)) + SPACE).cx, size.cx);
			size.cx = max(pDC->GetTextExtent(SPACE + CString(STRING(IDS_MESSAGETYPE_WARNING)) + SPACE).cx, size.cx);
			size.cx = max(pDC->GetTextExtent(SPACE + CString(STRING(IDS_MESSAGETYPE_ERROR)) + SPACE).cx, size.cx);
		}
		if (!lstrcmp(pszColumn, STRING(IDS_MESSAGESWINDOW_TITLEITEM_SOURCE)))
		{
			for (nDevice = 0, nDevices = EnumIODevices(szDevices); nDevice < nDevices; nDevice++)
			{
				size.cx = max(pDC->GetTextExtent(szDevices.GetAt(nDevice)).cx, size.cx);
				continue;
			}
		}
		size.cy = 2 * GetSystemMetrics(SM_CYBORDER) + pDC->GetTextExtent(SPACE).cy;
		ReleaseDC(pDC);
	}
	return size;
}

BOOL CSimulatorMessagesConsoleView::PreCreateWindow(CREATESTRUCT &cs)
{
	cs.style |= LVS_REPORT | LVS_NOSORTHEADER;
	return CListView::PreCreateWindow(cs);
}

BEGIN_MESSAGE_MAP(CSimulatorMessagesConsoleView, CListView)
	//{{AFX_MSG_MAP(CSimulatorMessagesConsoleView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleView handlers

int CSimulatorMessagesConsoleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CSize  size;
	CRect  rHeader;

	if (CListView::OnCreate(lpCreateStruct) != -1)
	{
		GetListCtrl().ModifyStyle(0, LVS_SHOWSELALWAYS);
		GetListCtrl().SetExtendedStyle(LVS_EX_FULLROWSELECT);
		GetListCtrl().InsertColumn(0, STRING(IDS_MESSAGESWINDOW_TITLEITEM_TIME), LVCFMT_LEFT);
		GetListCtrl().InsertColumn(1, STRING(IDS_MESSAGESWINDOW_TITLEITEM_TYPE), LVCFMT_LEFT);
		GetListCtrl().InsertColumn(2, STRING(IDS_MESSAGESWINDOW_TITLEITEM_SOURCE), LVCFMT_LEFT);
		GetListCtrl().InsertColumn(3, STRING(IDS_MESSAGESWINDOW_TITLEITEM_MESSAGE), LVCFMT_LEFT);
		GetListCtrl().SetColumnWidth(0, CalcColumnExtent(STRING(IDS_MESSAGESWINDOW_TITLEITEM_TIME)).cx);
		GetListCtrl().SetColumnWidth(1, CalcColumnExtent(STRING(IDS_MESSAGESWINDOW_TITLEITEM_TYPE)).cx);
		GetListCtrl().SetColumnWidth(2, CalcColumnExtent(STRING(IDS_MESSAGESWINDOW_TITLEITEM_SOURCE)).cx);
		GetListCtrl().SetColumnWidth(3, CalcColumnExtent(STRING(IDS_MESSAGESWINDOW_TITLEITEM_MESSAGE)).cx);
		for (GetListCtrl().GetHeaderCtrl()->GetClientRect(rHeader), size = CalcColumnExtent(EMPTYSTRING); size.cy > 0; )
		{
			rHeader.bottom = rHeader.top + size.cy;
			break;
		}
		GetListCtrl().GetHeaderCtrl()->MoveWindow(rHeader);
		return 0;
	}
	return -1;
}

BOOL CSimulatorMessagesConsoleView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	LPNMHDR  pNotifyInfo = (LPNMHDR)lParam;

	if (pNotifyInfo->code == HDN_BEGINTRACK)
	{
		RedrawWindow();
		RedrawWindow();
	}
	return CListView::OnNotify(wParam, lParam, pResult);
}


/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleWnd

IMPLEMENT_DYNCREATE(CSimulatorMessagesConsoleWnd, CDisplayWnd)

CSimulatorMessagesConsoleWnd::CSimulatorMessagesConsoleWnd() : CDisplayWnd()
{
	return;
}

VOID CSimulatorMessagesConsoleWnd::ShowMessage(LPCTSTR pszMessage)
{
	CString  szMessage;

	m_pwndView->ShowMessage(pszMessage);
	szMessage.Format(STRING(IDS_STATUSBAR_MESSAGECOUNT), GetMessageCount());
	m_wndStatusBar.SetPaneText(0, szMessage);
}
VOID CSimulatorMessagesConsoleWnd::ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage)
{
	CString  szMessage;

	m_pwndView->ShowMessage(pszType, pszMessage);
	szMessage.Format(STRING(IDS_STATUSBAR_MESSAGECOUNT), GetMessageCount());
	m_wndStatusBar.SetPaneText(0, szMessage);
}
VOID CSimulatorMessagesConsoleWnd::ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage)
{
	CString  szMessage;

	m_pwndView->ShowMessage(pszType, pszSource, pszMessage);
	szMessage.Format(STRING(IDS_STATUSBAR_MESSAGECOUNT), GetMessageCount());
	m_wndStatusBar.SetPaneText(0, szMessage);
}

INT CSimulatorMessagesConsoleWnd::GetMessageCount() CONST
{
	return m_pwndView->GetMessageCount();
}

BOOL CSimulatorMessagesConsoleWnd::PreCreateWindow(CREATESTRUCT &cs)
{
	cs.dwExStyle |= WS_EX_TOOLWINDOW;
	return CDisplayWnd::PreCreateWindow(cs);
}

BEGIN_MESSAGE_MAP(CSimulatorMessagesConsoleWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CSimulatorMessagesConsoleWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleWnd message handlers

int CSimulatorMessagesConsoleWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CCreateContext  cContext;

	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE))
		{
			for (m_wndStatusBar.SetIndicators(nMessageConsoleWndIndicators, sizeof(nMessageConsoleWndIndicators) / sizeof(UINT)), m_wndStatusBar.SetPaneStyle(0, SBPS_NOBORDERS), cContext.m_pCurrentDoc = new CSimulatorMessagesConsoleDocument; (m_pwndView = new CSimulatorMessagesConsoleView); )
			{
				if (m_pwndView->Create((LPCTSTR)NULL, EMPTYSTRING, WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(lpCreateStruct->x, lpCreateStruct->y, lpCreateStruct->cx, lpCreateStruct->cy), this, 0, &cContext)) return 0;
				delete m_pwndView;
				break;
			}
		}
	}
	return -1;
}

void CSimulatorMessagesConsoleWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rStatusBar;

	m_wndStatusBar.GetWindowRect(rStatusBar);
	m_pwndView->MoveWindow(0, 0, cx, cy - rStatusBar.Height());
	CDisplayWnd::OnSize(nType, cx, cy);
}

void CSimulatorMessagesConsoleWnd::OnDestroy()
{
	m_pwndView->DestroyWindow();
	CDisplayWnd::OnDestroy();
}
