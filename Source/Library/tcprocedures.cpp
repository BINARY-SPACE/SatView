// TCPROCEDURES.CPP : Telecommand Procedures Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand
// procedures related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2006/11/11 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#ifndef TCP_DLL
/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocument

IMPLEMENT_DYNCREATE(CTCProcedureDocument, COleDocument)

CTCProcedureDocument::CTCProcedureDocument() : COleDocument()
{
	m_bAutoDelete = FALSE;
}

CTCProcedureDocument::~CTCProcedureDocument()
{
	DeleteContents();
}

VOID CTCProcedureDocument::AddStep(CTCProcedureDocumentItem *pStep)
{
	pStep->m_pDocument = this;
	m_docItemList.AddTail(pStep);
}

POSITION CTCProcedureDocument::InsertStep(CTCProcedureDocumentItem *pStep, POSITION &lPosition, BOOL bBefore)
{
	pStep->m_pDocument = this;
	return((bBefore) ? m_docItemList.InsertBefore(lPosition, pStep) : m_docItemList.InsertAfter(lPosition, pStep));
}

POSITION CTCProcedureDocument::FindStep(CONST CTCProcedureDocumentItem *pStep, BOOL bAll) CONST
{
	POSITION  lPosition[2];
	CTCProcedureDocumentItem  *pItem;

	for (lPosition[0] = lPosition[1] = GetStartPosition(); lPosition[0]; lPosition[1] = lPosition[0])
	{
		if ((pItem = GetNextStep(lPosition[0])) != (CTCProcedureDocumentItem *)NULL  &&  pItem == pStep) break;
		if ((lPosition[1] = (bAll) ? pItem->GetSubSteps()->FindStep(pStep) : (POSITION)NULL)) break;
	}
	return lPosition[1];
}

BOOL CTCProcedureDocument::RemoveStep(CTCProcedureDocumentItem *pStep)
{
	POSITION  lPosition;

	if ((lPosition = pStep->m_pDocument->m_docItemList.Find(pStep)))
	{
		pStep->m_pDocument->m_docItemList.RemoveAt(lPosition);
		pStep->m_pDocument = (CTCProcedureDocument *)NULL;
		return TRUE;
	}
	return FALSE;
}

CTCProcedureDocumentItem *CTCProcedureDocument::GetFirstStep() CONST
{
	return((m_docItemList.GetCount() > 0) ? (CTCProcedureDocumentItem *)m_docItemList.GetHead() : (CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProcedureDocument::GetNextStep(POSITION &lPosition) CONST
{
	return((m_docItemList.GetCount() > 0) ? (CTCProcedureDocumentItem *)m_docItemList.GetNext(lPosition) : (CTCProcedureDocumentItem *)NULL);
}
CTCProcedureDocumentItem *CTCProcedureDocument::GetNextStep(CONST CTCProcedureDocumentItem *pStep) CONST
{
	POSITION  lPosition;

	return((m_docItemList.GetCount() > 0 && pStep->m_pDocument->m_docItemList.GetNext((lPosition = pStep->m_pDocument->m_docItemList.Find((CObject *)pStep))) && lPosition) ? (CTCProcedureDocumentItem *)pStep->m_pDocument->m_docItemList.GetNext(lPosition) : (CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProcedureDocument::GetPreviousStep(POSITION &lPosition) CONST
{
	return((m_docItemList.GetCount() > 0) ? (CTCProcedureDocumentItem *)m_docItemList.GetPrev(lPosition) : (CTCProcedureDocumentItem *)NULL);
}
CTCProcedureDocumentItem *CTCProcedureDocument::GetPreviousStep(CONST CTCProcedureDocumentItem *pStep) CONST
{
	POSITION  lPosition;

	return((m_docItemList.GetCount() > 0 && pStep->m_pDocument->m_docItemList.GetPrev((lPosition = pStep->m_pDocument->m_docItemList.Find((CObject *)pStep))) && lPosition) ? (CTCProcedureDocumentItem *)pStep->m_pDocument->m_docItemList.GetPrev(lPosition) : (CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProcedureDocument::GetLastStep() CONST
{
	return((m_docItemList.GetCount() > 0) ? (CTCProcedureDocumentItem *)m_docItemList.GetTail() : (CTCProcedureDocumentItem *)NULL);
}

UINT CTCProcedureDocument::EnumSteps(CPtrArray &pSteps, BOOL bAll, BOOL bNamed) CONST
{
	INT  nIndex;
	INT  nStep[2];
	INT  nSteps[2];
	CString  szName;
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep[2];

	for (lPosition = GetStartPosition(), pSteps.RemoveAll(); lPosition; )
	{
		if ((pStep[0] = GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((!bAll  &&  pStep[0]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep[0]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END) || bAll)
			{
				for (pSteps.Add(pStep[0]); (pDocument = pStep[0]->GetSubSteps()); )
				{
					EnumSteps(pDocument, pSteps, bAll);
					break;
				}
			}
		}
	}
	for (nStep[0] = 0, nSteps[0] = (bNamed) ? (INT)pSteps.GetSize() : 0, nIndex = 0; nStep[0] < nSteps[0]; nStep[0]++)
	{
		while ((pStep[0] = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep[0])) && pStep[0]->GetName().IsEmpty())
		{
			for (nStep[1] = 0, nSteps[1] = nSteps[0], szName.Format(STRING(IDS_TELECOMMANDPROCEDURESTEP_DEFAULT_NAME), nIndex + 1); nStep[1] < nSteps[1]; nStep[1]++)
			{
				if ((pStep[1] = (CTCProcedureDocumentItem *)pSteps.GetAt(nStep[1])) && pStep[1]->GetName() == szName) break;
				continue;
			}
			if (nStep[1] == nSteps[1])
			{
				pStep[0]->SetName(szName);
				break;
			}
			nIndex++;
		}
	}
	return((UINT)pSteps.GetSize());
}
UINT CTCProcedureDocument::EnumSteps(CONST CTCProcedureDocument *pDocument, CPtrArray &pSteps, BOOL bAll) CONST
{
	POSITION  lPosition;
	CTCProcedureDocument  *pSubDocument;
	CTCProcedureDocumentItem  *pSubStep;

	for (lPosition = pDocument->GetStartPosition(); lPosition; )
	{
		if ((pSubStep = pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((!bAll  &&  pSubStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pSubStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END) || bAll)
			{
				for (pSteps.Add(pSubStep); (pSubDocument = pSubStep->GetSubSteps()); )
				{
					EnumSteps(pSubDocument, pSteps, bAll);
					break;
				}
			}
		}
	}
	return((UINT)pSteps.GetSize());
}

UINT CTCProcedureDocument::GetStepCount(BOOL bAll) CONST
{
	CPtrArray  pSteps;

	return EnumSteps(pSteps, bAll);
}

POSITION CTCProcedureDocument::GetStartPosition() CONST
{
	return m_docItemList.GetHeadPosition();
}

POSITION CTCProcedureDocument::GetStopPosition() CONST
{
	return m_docItemList.GetTailPosition();
}

BOOL CTCProcedureDocument::SaveModified()
{
	return TRUE;
}

BOOL CTCProcedureDocument::OnNewDocument()
{
	return COleDocument::OnNewDocument();
}

void CTCProcedureDocument::OnCloseDocument()
{
	DeleteContents();
}

BOOL CTCProcedureDocument::CanCloseFrame(CFrameWnd *pFrame)
{
	return TRUE;
}

VOID CTCProcedureDocument::DeleteContents()
{
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = GetStartPosition(); lPosition; )
	{
		if ((pStep = GetNextStep(lPosition)))
		{
			pStep->Release();
			pStep->Delete();
		}
	}
	SetModifiedFlag(FALSE);
	COleDocument::DeleteContents();
}

BOOL CTCProcedureDocument::Copy(CONST CTCProcedureDocument *pDocument, BOOL bState)
{
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep[2];

	for (lPosition = pDocument->GetStartPosition(), DeleteContents(); lPosition; )
	{
		if ((pStep[0] = pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((pStep[1] = CTCProcedureDocumentItem::Create(pStep[0]->GetType(), pStep[0]->GetSubThreadID())))
			{
				if (pStep[1]->Copy(pStep[0], bState))
				{
					AddStep(pStep[1]);
					continue;
				}
				delete pStep[1];
			}
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CTCProcedureDocument::Compare(CONST CTCProcedureDocument *pDocument, BOOL bState) CONST
{
	POSITION  lPosition[2];
	CTCProcedureDocumentItem  *pStep;

	for (lPosition[0] = pDocument->GetStartPosition(), lPosition[1] = GetStartPosition(); pDocument->GetStepCount() == GetStepCount() && lPosition[0] && lPosition[1]; )
	{
		if ((pStep = pDocument->GetNextStep(lPosition[0])) && pStep->Compare(GetNextStep(lPosition[1]), bState)) continue;
		lPosition[0] = pDocument->GetStartPosition();
		lPosition[1] = GetStartPosition();
		break;
	}
	return((pDocument->GetStepCount() == GetStepCount()) ? ((!lPosition[0] && !lPosition[1]) ? TRUE : FALSE) : FALSE);
}

BOOL CTCProcedureDocument::Map(CByteArray &nData) CONST
{
	POSITION  lPosition;
	CByteArray  nStepData;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = GetStartPosition(), nData.RemoveAll(); lPosition; )
	{
		if ((pStep = GetNextStep(lPosition)) && pStep->Map(nStepData) && nData.Append(nStepData) >= 0) continue;
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}
BOOL CTCProcedureDocument::Map(CDatabaseTCProcedureThreadContents *pContents) CONST
{
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThreadStep  *pThreadStep;

	for (lPosition = GetStartPosition(), pContents->RemoveAll(); lPosition; )
	{
		if ((pStep = GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((pThreadStep = new CDatabaseTCProcedureThreadStep) != (CDatabaseTCProcedureThreadStep *)NULL)
			{
				if (pStep->Map(pThreadStep) && pContents->Add(pThreadStep) >= 0) continue;
				delete pThreadStep;
			}
		}
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CTCProcedureDocument::Unmap(CONST CByteArray &nData)
{
	INT  cbStep;
	INT  cbSteps;
	CByteArray  nStepData;
	CTCProcedureDocumentItem  *pStep;

	for (cbSteps = 0, DeleteContents(); cbSteps < nData.GetSize(); cbSteps += cbStep)
	{
		for (CopyMemory(&cbStep, nData.GetData() + cbSteps, sizeof(cbStep)), nStepData.SetSize(max(min(cbStep, nData.GetSize() - cbSteps), 0)); nStepData.GetSize() >= 0; )
		{
			CopyMemory(nStepData.GetData(), nData.GetData() + cbSteps, nStepData.GetSize());
			break;
		}
		if ((pStep = CTCProcedureDocumentItem::AllocateFromData(nStepData)))
		{
			AddStep(pStep);
			continue;
		}
		break;
	}
	return((cbSteps == nData.GetSize()) ? TRUE : FALSE);
}
BOOL CTCProcedureDocument::Unmap(CONST CDatabaseTCProcedureThreadContents *pContents)
{
	INT  nStep;
	INT  nSteps;
	CTCProcedureDocumentItem  *pStep;
	CDatabaseTCProcedureThreadStep  *pThreadStep;

	for (nStep = 0, nSteps = (INT)pContents->GetSize(), DeleteContents(); nStep < nSteps; nStep++)
	{
		if ((pThreadStep = pContents->GetAt(nStep)) != (CDatabaseTCProcedureThreadStep *)NULL)
		{
			if ((pStep = CTCProcedureDocumentItem::AllocateFromItem(pThreadStep)))
			{
				AddStep(pStep);
				continue;
			}
		}
		break;
	}
	return((nStep == nSteps) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTCProcedureDocument, COleDocument)
	//{{AFX_MSG_MAP(CTCProcedureDocument)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocument serialization

void CTCProcedureDocument::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocument commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentItem, COleClientItem)

CTCProcedureDocumentItem::CTCProcedureDocumentItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : COleClientItem(pContainerDoc)
{
	CFontTools  cFontTools(&m_cLabelFont);

	m_nType = 0;
	m_nState = 0;
	m_sizeDesign.cx = 0;
	m_sizeDesign.cy = 0;
	m_sizeSymbol[0].cx = 0;
	m_sizeSymbol[0].cy = 0;
	m_sizeSymbol[1].cx = 0;
	m_sizeSymbol[1].cy = 0;
	m_sizeSymbol[2].cx = 0;
	m_sizeSymbol[2].cy = 0;
	m_nTriggerType = 0;
	m_tTriggerTime = 0;
	m_tTriggerTimeOffset = 0;
	m_tTriggerTimeDelay = 0;
	m_tTriggerTimeout = 0;
	m_nConfirmationType = 0;
	m_tConfirmationTimeout = 0;
	m_nFailureOptions = 0;
	m_rPosition.SetRectEmpty();
	m_nSubThreadID = nSubThreadID;
	m_nLabelColor = GetSysColor(COLOR_WINDOWTEXT);
	m_pSubSteps = new CTCProcedureDocument;
	m_bActivated = FALSE;
	m_bSelected = FALSE;
	m_bExpanded = FALSE;
}

CTCProcedureDocumentItem::~CTCProcedureDocumentItem()
{
	delete m_pSubSteps;
}

CTCProcedureDocumentItem *CTCProcedureDocumentItem::Create(UINT nType, UINT nSubThreadID)
{
	switch (nType)
	{
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_START: return new CTCProcedureDocumentStartItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_BRANCH: return new CTCProcedureDocumentBranchItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_SWITCH: return new CTCProcedureDocumentSwitchItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_FORLOOP: return new CTCProcedureDocumentForLoopItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_WHILELOOP: return new CTCProcedureDocumentWhileLoopItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_DOLOOP: return new CTCProcedureDocumentDoLoopItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_BLOCK: return new CTCProcedureDocumentBlockItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO: return new CTCProcedureDocumentGotoItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_LABEL: return new CTCProcedureDocumentLabelItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_FLOWCONTROL_END: return new CTCProcedureDocumentEndItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETARGUMENTS: return new CTCProcedureDocumentSetArgumentsItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETVARIABLES: return new CTCProcedureDocumentSetVariablesItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETPARAMETERS: return new CTCProcedureDocumentSetParametersItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETSYNCOBJECT: return new CTCProcedureDocumentSetSynchronizationObjectItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_INJECTALERT: return new CTCProcedureDocumentInjectAlertItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_CALLPROCEDURE: return new CTCProcedureDocumentCallProcedureItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_STARTPROCEDURE: return new CTCProcedureDocumentStartProcedureItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_CONTROLPROCEDURE: return new CTCProcedureDocumentControlProcedureItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_CONTROLTHREAD: return new CTCProcedureDocumentControlThreadItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_WAITTIMEINTERVAL: return new CTCProcedureDocumentWaitTimeIntervalItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_WAITSYNCOBJECT: return new CTCProcedureDocumentWaitSynchronizationObjectItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCFUNCTION: return new CTCProcedureDocumentSendTCFunctionItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE: return new CTCProcedureDocumentSendTCSequenceItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_LOGMESSAGE: return new CTCProcedureDocumentLogMessageItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	case TCPROCEDURETHREADSTEP_ACTIONOBJECT_USERINTERACTION: return new CTCProcedureDocumentUserInteractionItem((CTCProcedureDocument *)NULL, nSubThreadID); break;
	default: return new CTCProcedureDocumentItem;
	}
	return((CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProcedureDocumentItem::AllocateFromItem(CONST CTCProcedureDocumentItem *pItem)
{
	CTCProcedureDocumentItem  *pStep;

	if ((pStep = Create(pItem->GetType(), pItem->GetSubThreadID())))
	{
		if (pStep->Copy(pItem)) return pStep;
		delete pStep;
	}
	return((CTCProcedureDocumentItem *)NULL);
}
CTCProcedureDocumentItem *CTCProcedureDocumentItem::AllocateFromItem(CONST CDatabaseTCProcedureThreadStep *pItem)
{
	CTCProcedureDocumentItem  *pStep;

	if ((pStep = Create(pItem->GetType(), pItem->GetSubThreadID())))
	{
		if (pStep->Unmap(pItem)) return pStep;
		delete pStep;
	}
	return((CTCProcedureDocumentItem *)NULL);
}

CTCProcedureDocumentItem *CTCProcedureDocumentItem::AllocateFromData(CONST CByteArray &nData)
{
	CTCProcedureDocumentItem  *pStep[2];

	if ((pStep[0] = new CTCProcedureDocumentItem))
	{
		if ((pStep[1] = (pStep[0]->Unmap(nData)) ? Create(pStep[0]->GetType(), pStep[0]->GetSubThreadID()) : (CTCProcedureDocumentItem *)NULL))
		{
			if (pStep[1]->Copy(pStep[0]))
			{
				delete pStep[0];
				return pStep[1];
			}
		}
		delete pStep[0];
	}
	return((CTCProcedureDocumentItem *)NULL);
}

VOID CTCProcedureDocumentItem::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCProcedureDocumentItem::GetName() CONST
{
	return m_szName;
}

VOID CTCProcedureDocumentItem::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CTCProcedureDocumentItem::GetComments() CONST
{
	return m_szComments;
}

VOID CTCProcedureDocumentItem::SetType(UINT nType)
{
	m_nType = nType;
}

UINT CTCProcedureDocumentItem::GetType() CONST
{
	return m_nType;
}

VOID CTCProcedureDocumentItem::SetPosition(CONST RECT &rect)
{
	m_rPosition = rect;
}

CRect CTCProcedureDocumentItem::GetPosition() CONST
{
	return m_rPosition;
}

VOID CTCProcedureDocumentItem::SetDesignSize(CONST SIZE &size)
{
	m_sizeDesign = size;
}

CSize CTCProcedureDocumentItem::GetDesignSize() CONST
{
	return m_sizeDesign;
}

VOID CTCProcedureDocumentItem::SetImageSize(CONST SIZE &size)
{
	m_sizeSymbol[0] = size;
}

CSize CTCProcedureDocumentItem::GetImageSize() CONST
{
	return m_sizeSymbol[0];
}

VOID CTCProcedureDocumentItem::SetSubThreadID(UINT nID)
{
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			pStep->SetSubThreadID(pStep->GetSubThreadID() + nID - m_nSubThreadID);
			continue;
		}
	}
	m_nSubThreadID = nID;
}

UINT CTCProcedureDocumentItem::GetSubThreadID() CONST
{
	return m_nSubThreadID;
}

VOID CTCProcedureDocumentItem::SetLabel(LPCTSTR pszLabel)
{
	m_szLabel = pszLabel;
}

CString CTCProcedureDocumentItem::GetLabel() CONST
{
	return m_szLabel;
}

BOOL CTCProcedureDocumentItem::SetLabelFont(CONST CFont *pFont)
{
	LOGFONT  lfFont;
	CFontTools  cFontTools;

	m_cLabelFont.DeleteObject();
	return((pFont->GetObject(sizeof(LOGFONT), &lfFont) > 0) ? m_cLabelFont.CreateFontIndirect(&lfFont) : cFontTools.QueryDefaultFont(&m_cLabelFont));
}

BOOL CTCProcedureDocumentItem::GetLabelFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	pFont->DeleteObject();
	return((m_cLabelFont.GetObject(sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

VOID CTCProcedureDocumentItem::SetLabelColor(COLORREF nColor)
{
	m_nLabelColor = nColor;
}

COLORREF CTCProcedureDocumentItem::GetLabelColor() CONST
{
	return m_nLabelColor;
}

VOID CTCProcedureDocumentItem::SetTriggerType(UINT nType)
{
	m_nTriggerType = nType;
}

UINT CTCProcedureDocumentItem::GetTriggerType() CONST
{
	return m_nTriggerType;
}

VOID CTCProcedureDocumentItem::SetTriggerTime(CONST CTimeTag &tTime)
{
	m_tTriggerTime = tTime;
}

CTimeTag CTCProcedureDocumentItem::GetTriggerTime() CONST
{
	return m_tTriggerTime;
}

VOID CTCProcedureDocumentItem::SetTriggerTimeOffset(CONST CTimeSpan &tOffset)
{
	m_tTriggerTimeOffset = tOffset;
}

CTimeSpan CTCProcedureDocumentItem::GetTriggerTimeOffset() CONST
{
	return m_tTriggerTimeOffset;
}

VOID CTCProcedureDocumentItem::SetTriggerTimeDelay(CONST CTimeSpan &tDelay)
{
	m_tTriggerTimeDelay = tDelay;
}

CTimeSpan CTCProcedureDocumentItem::GetTriggerTimeDelay() CONST
{
	return m_tTriggerTimeDelay;
}

VOID CTCProcedureDocumentItem::SetTriggerSynchronizationObject(LPCTSTR pszObject)
{
	m_szTriggerObject = pszObject;
}

CString CTCProcedureDocumentItem::GetTriggerSynchronizationObject() CONST
{
	return m_szTriggerObject;
}

VOID CTCProcedureDocumentItem::SetTriggerTimeout(CONST CTimeSpan &tTimeout)
{
	m_tTriggerTimeout = tTimeout;
}

CTimeSpan CTCProcedureDocumentItem::GetTriggerTimeout() CONST
{
	return m_tTriggerTimeout;
}

VOID CTCProcedureDocumentItem::SetTriggerMessage(LPCTSTR pszMessage)
{
	m_szTriggerMessage = pszMessage;
}

CString CTCProcedureDocumentItem::GetTriggerMessage() CONST
{
	return m_szTriggerMessage;
}

VOID CTCProcedureDocumentItem::SetTriggerExpression(LPCTSTR pszExpression)
{
	m_szTriggerExpression = pszExpression;
}

CString CTCProcedureDocumentItem::GetTriggerExpression() CONST
{
	return m_szTriggerExpression;
}

VOID CTCProcedureDocumentItem::SetPreexecutionExpression(LPCTSTR pszExpression)
{
	m_szPreexecutionExpression = pszExpression;
}

CString CTCProcedureDocumentItem::GetPreexecutionExpression() CONST
{
	return m_szPreexecutionExpression;
}

VOID CTCProcedureDocumentItem::SetConfirmationType(UINT nType)
{
	m_nConfirmationType = nType;
}

UINT CTCProcedureDocumentItem::GetConfirmationType() CONST
{
	return m_nConfirmationType;
}

VOID CTCProcedureDocumentItem::SetConfirmationTimeout(CONST CTimeSpan &tTimeout)
{
	m_tConfirmationTimeout = tTimeout;
}

CTimeSpan CTCProcedureDocumentItem::GetConfirmationTimeout() CONST
{
	return m_tConfirmationTimeout;
}

VOID CTCProcedureDocumentItem::SetConfirmationMessage(LPCTSTR pszMessage)
{
	m_szConfirmationMessage = pszMessage;
}

CString CTCProcedureDocumentItem::GetConfirmationMessage() CONST
{
	return m_szConfirmationMessage;
}

VOID CTCProcedureDocumentItem::SetConfirmationExpression(LPCTSTR pszExpression)
{
	m_szConfirmationExpression = pszExpression;
}

CString CTCProcedureDocumentItem::GetConfirmationExpression() CONST
{
	return m_szConfirmationExpression;
}

VOID CTCProcedureDocumentItem::SetFailureOptions(UINT nOptions)
{
	m_nFailureOptions = nOptions;
}

UINT CTCProcedureDocumentItem::GetFailureOptions() CONST
{
	return m_nFailureOptions;
}

VOID CTCProcedureDocumentItem::SetFailureLabels(CONST CStringArray &szLabels)
{
	m_szFailureLabels.Copy(szLabels);
}

INT CTCProcedureDocumentItem::GetFailureLabels(CStringArray &szLabels) CONST
{
	szLabels.Copy(m_szFailureLabels);
	return((INT)szLabels.GetSize());
}

BOOL CTCProcedureDocumentItem::CanActivate() CONST
{
	return FALSE;
}

BOOL CTCProcedureDocumentItem::Activate(BOOL bActivate)
{
	if (m_bActivated != bActivate)
	{
		m_bActivated = (CanActivate()) ? bActivate : FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentItem::IsActivated() CONST
{
	return m_bActivated;
}

BOOL CTCProcedureDocumentItem::CanSelect() CONST
{
	return FALSE;
}

BOOL CTCProcedureDocumentItem::Select(BOOL bSelect)
{
	if (m_bSelected != bSelect)
	{
		m_bSelected = (CanSelect()) ? bSelect : FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentItem::IsSelected() CONST
{
	return m_bSelected;
}

BOOL CTCProcedureDocumentItem::CanExpand() CONST
{
	return FALSE;
}

BOOL CTCProcedureDocumentItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = (CanExpand()) ? bExpand : FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentItem::IsExpanded() CONST
{
	return m_bExpanded;
}

VOID CTCProcedureDocumentItem::SetState(UINT nState)
{
	m_nState = nState;
}

UINT CTCProcedureDocumentItem::GetState() CONST
{
	return m_nState;
}

BOOL CTCProcedureDocumentItem::IsPtOnImage(CONST POINT &pt) CONST
{
	CRect  rImage;

	rImage.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx, m_rPosition.top + m_sizeSymbol[0].cy);
	return rImage.PtInRect(pt);
}

BOOL CTCProcedureDocumentItem::IsPtOnTreeSymbol(CONST POINT &pt) CONST
{
	CRect  rSymbol;

	rSymbol.SetRect(m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, m_rPosition.top + m_sizeSymbol[0].cy / 2 - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2, m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT, m_rPosition.top + m_sizeSymbol[0].cy / 2 - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE);
	return((CanExpand()) ? rSymbol.PtInRect(pt) : FALSE);
}

CPoint CTCProcedureDocumentItem::CalcConnectionPoint(BOOL bIn, BOOL bExpanded) CONST
{
	CPoint  pt;

	for (pt.x = pt.y = 0; bIn; )
	{
		pt.x = m_rPosition.left + m_sizeSymbol[0].cx - m_sizeSymbol[1].cx / 2;
		pt.y = m_rPosition.top;
		return pt;
	}
	if (!bIn)
	{
		if (!bExpanded)
		{
			pt.x = m_rPosition.left + m_sizeSymbol[0].cx - m_sizeSymbol[1].cx / 2;
			pt.y = m_rPosition.top + m_sizeSymbol[0].cy;
			return pt;
		}
		pt.x = m_rPosition.left + m_sizeSymbol[0].cx - m_sizeSymbol[1].cx / 2;
		pt.y = m_rPosition.bottom;
	}
	return pt;
}

VOID CTCProcedureDocumentItem::RecalcLayout()
{
	return;
}

BOOL CTCProcedureDocumentItem::HasProperties() CONST
{
	return FALSE;
}

BOOL CTCProcedureDocumentItem::MapProperties(CByteArray &nInfo) CONST
{
	nInfo.Copy(m_nInfo);
	return TRUE;
}

BOOL CTCProcedureDocumentItem::UnmapProperties(CONST CByteArray &nInfo)
{
	return TRUE;
}

VOID CTCProcedureDocumentItem::Draw(CDC *pDC, BOOL bFaded)
{
	INT  i, j;
	INT  nMode;
	INT  nRadius;
	UINT  nID[3];
	UINT  nState;
	CPen  cPen[2];
	CPen  *pOldPen;
	CPoint  pt[2];
	CBrush  cBrush;
	CBrush  *pOldBrush;
	CImage  cSymbol;
	POSITION  lPosition;
	LOGBRUSH  sPenBrush;
	CTCProcedureDocumentItem  *pStep[2];

	for (DrawContents(pDC), lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL, pStep[0] = pStep[1] = (CTCProcedureDocumentItem *)NULL; lPosition; pStep[1] = pStep[0])
	{
		if ((pStep[0] = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep[1] && pStep[1]->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO)
			{
				if (pStep[0]->GetSubThreadID() == pStep[1]->GetSubThreadID())
				{
					pt[0] = pStep[1]->CalcConnectionPoint(FALSE, pStep[1]->IsExpanded());
					pt[1] = pStep[0]->CalcConnectionPoint(TRUE, pStep[0]->IsExpanded());
					DrawConnectionLine(pDC, pt[0], pt[1]);
				}
			}
		}
	}
	for (lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep[0] = m_pSubSteps->GetNextStep(lPosition)))
		{
			pStep[0]->Draw(pDC);
			continue;
		}
	}
	for (DrawSymbol(pDC, m_cSymbol[0], m_rPosition.left, m_rPosition.top); m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_START && m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO && m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_LABEL && m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_END; )
	{
		DrawSymbol(pDC, m_cSymbol[1], m_rPosition.left + m_sizeSymbol[0].cx - m_sizeSymbol[1].cx, m_rPosition.top);
		break;
	}
	if (m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
	{
		if (m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO  &&  m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_LABEL)
		{
			switch ((nState = GetState()) & (TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING | TCPROCEDURETHREADSTEP_STATE_TRIGGER_EXECUTED | TCPROCEDURETHREADSTEP_STATE_TRIGGER_FAILED | TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED))
			{
			case TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING: nID[0] = IDP_TCFLOWSTATUSTRIGGERRUNNINGSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_TRIGGER_EXECUTED: nID[0] = IDP_TCFLOWSTATUSTRIGGEREXECUTEDSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_TRIGGER_FAILED: nID[0] = IDP_TCFLOWSTATUSTRIGGERFAILEDSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED: nID[0] = IDP_TCFLOWSTATUSTRIGGERFORCEDSYMBOL; break;
			default: nID[0] = -1; break;
			}
			switch (nState & (TCPROCEDURETHREADSTEP_STATE_BODY_RUNNING | TCPROCEDURETHREADSTEP_STATE_BODY_EXECUTED | TCPROCEDURETHREADSTEP_STATE_BODY_FAILED | TCPROCEDURETHREADSTEP_STATE_BODY_FORCED))
			{
			case TCPROCEDURETHREADSTEP_STATE_BODY_RUNNING: nID[1] = IDP_TCFLOWSTATUSBODYRUNNINGSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_BODY_EXECUTED: nID[1] = IDP_TCFLOWSTATUSBODYEXECUTEDSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_BODY_FAILED: nID[1] = IDP_TCFLOWSTATUSBODYFAILEDSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_BODY_FORCED: nID[1] = IDP_TCFLOWSTATUSBODYFORCEDSYMBOL; break;
			default: nID[1] = -1; break;
			}
			switch (nState & (TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_RUNNING | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_EXECUTED | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FAILED | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED))
			{
			case TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_RUNNING: nID[2] = IDP_TCFLOWSTATUSCONFIRMATIONRUNNINGSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_EXECUTED: nID[2] = IDP_TCFLOWSTATUSCONFIRMATIONEXECUTEDSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FAILED: nID[2] = IDP_TCFLOWSTATUSCONFIRMATIONFAILEDSYMBOL; break;
			case TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED: nID[2] = IDP_TCFLOWSTATUSCONFIRMATIONFORCEDSYMBOL; break;
			default: nID[2] = -1; break;
			}
			for (i = 0, j = sizeof(nID) / sizeof(UINT); i < j; i++)
			{
				if (LoadSymbol(MAKEINTRESOURCE(nID[i]), cSymbol))
				{
					DrawSymbol(pDC, cSymbol, m_rPosition.left + m_sizeSymbol[0].cx - m_sizeSymbol[1].cx, m_rPosition.top);
					cSymbol.Destroy();
				}
			}
		}
		if (m_bActivated)
		{
			if (LoadSymbol((m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO  &&  m_nType != TCPROCEDURETHREADSTEP_FLOWCONTROL_LABEL) ? IDP_TCFLOWSTATUSACTIVATEDSYMBOL : IDP_TCFLOWSTATUSACTIVATEDNOSYMBOL, cSymbol))
			{
				DrawSymbol(pDC, cSymbol, m_rPosition.left + m_sizeSymbol[0].cx - cSymbol.GetWidth(), m_rPosition.top);
				cSymbol.Destroy();
			}
		}
	}
	if (m_bSelected)
	{
		if (GetObjectType(pDC->GetSafeHdc()) != OBJ_ENHMETADC)
		{
			if (cPen[0].CreatePen(PS_SOLID, 1, TCPROCEDUREDOCUMENTITEM_BACKGROUNDCOLOR))
			{
				if (cBrush.CreateSolidBrush(TCPROCEDUREDOCUMENTITEM_BACKGROUNDCOLOR))
				{
					if ((pOldBrush = pDC->SelectObject(&cBrush)))
					{
						if ((pOldPen = pDC->SelectObject(&cPen[0])))
						{
							nMode = pDC->SetROP2(R2_COPYPEN);
							nRadius = min(m_sizeSymbol[0].cx, m_sizeSymbol[0].cy) / 5 + 1;
							pDC->Ellipse(m_rPosition.left + (m_sizeSymbol[0].cx - 2 * nRadius) / 2, m_rPosition.top + (m_sizeSymbol[0].cy - 2 * nRadius) / 2, m_rPosition.left + (m_sizeSymbol[0].cx - 2 * nRadius) / 2 + 2 * nRadius, m_rPosition.top + (m_sizeSymbol[0].cy - 2 * nRadius) / 2 + 2 * nRadius);
							pDC->SelectObject(pOldPen);
							pDC->SetROP2(nMode);
						}
						pDC->SelectObject(pOldBrush);
					}
					cBrush.DeleteObject();
				}
				cPen[0].DeleteObject();
			}
		}
	}
	if (CanExpand() && !bFaded)
	{
		sPenBrush.lbStyle = BS_SOLID;
		sPenBrush.lbColor = VGA_COLOR_GRAY;
		sPenBrush.lbHatch = (ULONG_PTR)NULL;
		if (cPen[0].CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_DOT, 1, &sPenBrush))
		{
			if (cPen[1].CreatePen(PS_SOLID, 1, VGA_COLOR_BLACK))
			{
				if (cBrush.CreateStockObject(HOLLOW_BRUSH))
				{
					if ((pOldPen = pDC->SelectObject(&cPen[0])))
					{
						if ((pOldBrush = pDC->SelectObject(&cBrush)))
						{
							pDC->Rectangle(m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, m_rPosition.top + m_sizeSymbol[0].cy / 2 - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2, m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT, m_rPosition.top + m_sizeSymbol[0].cy / 2 - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE);
							pDC->MoveTo(m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT, m_rPosition.top + m_sizeSymbol[0].cy / 2);
							pDC->LineTo(m_rPosition.left, m_rPosition.top + m_sizeSymbol[0].cy / 2);
							pDC->SelectObject(pOldBrush);
						}
						pDC->SelectObject(pOldPen);
					}
					cBrush.DeleteObject();
				}
				if ((pOldPen = pDC->SelectObject(&cPen[1])))
				{
					for (pDC->MoveTo(m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE + 1 + 1, m_rPosition.top + m_sizeSymbol[0].cy / 2), pDC->LineTo(m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - 1 - 1, m_rPosition.top + m_sizeSymbol[0].cy / 2); !m_bExpanded; )
					{
						pDC->MoveTo(m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2 - 1, m_rPosition.top + m_sizeSymbol[0].cy / 2 - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2 + 1 + 1);
						pDC->LineTo(m_rPosition.left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2 - 1, m_rPosition.top + m_sizeSymbol[0].cy / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE / 2 - 1);
						break;
					}
					pDC->SelectObject(pOldPen);
				}
				cPen[1].DeleteObject();
			}
			cPen[0].DeleteObject();
		}
	}
	if (!bFaded)
	{
		DrawLabels(pDC);
		return;
	}
}

BOOL CTCProcedureDocumentItem::Copy(CONST CTCProcedureDocumentItem *pStep, BOOL bState)
{
	CFont  cFont;

	for (m_szName = pStep->m_szName, m_nType = pStep->m_nType, m_szLabel = pStep->m_szLabel, m_nLabelColor = pStep->m_nLabelColor, m_szComments = pStep->m_szComments, m_nSubThreadID = pStep->m_nSubThreadID, m_rPosition = pStep->m_rPosition, m_nState = (bState) ? pStep->m_nState : m_nState, m_bActivated = (bState) ? pStep->m_bActivated : m_bActivated, m_bSelected = (bState) ? pStep->m_bSelected : m_bSelected, m_bExpanded = pStep->m_bExpanded, m_sizeDesign = pStep->m_sizeDesign, m_nTriggerType = pStep->m_nTriggerType, m_tTriggerTime = pStep->m_tTriggerTime, m_tTriggerTimeOffset = pStep->m_tTriggerTimeOffset, m_tTriggerTimeDelay = pStep->m_tTriggerTimeDelay, m_tTriggerTimeout = pStep->m_tTriggerTimeout, m_szTriggerObject = pStep->m_szTriggerObject, m_szTriggerMessage = pStep->m_szTriggerMessage, m_szTriggerExpression = pStep->m_szTriggerExpression, m_szPreexecutionExpression = pStep->m_szPreexecutionExpression, m_nConfirmationType = pStep->m_nConfirmationType, m_szConfirmationMessage = pStep->m_szConfirmationMessage, m_szConfirmationExpression = pStep->m_szConfirmationExpression, m_tConfirmationTimeout = pStep->m_tConfirmationTimeout, m_nFailureOptions = pStep->m_nFailureOptions, m_szFailureLabels.Copy(pStep->m_szFailureLabels); pStep->GetLabelFont(&cFont) && SetLabelFont(&cFont) && m_pSubSteps->Copy(pStep->m_pSubSteps, bState) && pStep->MapProperties(m_nInfo); )
	{
		UnmapProperties(m_nInfo);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentItem::Compare(CONST CTCProcedureDocumentItem *pStep, BOOL bState) CONST
{
	INT  nLabel;
	INT  nLabels;
	LOGFONT  lfFont[2];
	CByteArray  nInfo[2];

	for (nLabel = 0, nLabels = (pStep->m_szName == m_szName && pStep->m_nType == m_nType && pStep->m_szLabel == m_szLabel && pStep->m_nLabelColor == m_nLabelColor && pStep->m_szComments == m_szComments && pStep->m_nSubThreadID == m_nSubThreadID && pStep->m_rPosition == m_rPosition && ((bState && pStep->m_nState == m_nState && pStep->m_bActivated == m_bActivated && pStep->m_bSelected == m_bSelected) || !bState) && pStep->m_bExpanded == m_bExpanded && pStep->m_sizeDesign == m_sizeDesign && pStep->m_nTriggerType == m_nTriggerType && ((m_nTriggerType & (TCPROCEDURETHREADSTEP_TRIGGERTYPE_ATTIME | TCPROCEDURETHREADSTEP_TRIGGERTYPE_NOTAFTERTIME)) == 0 || pStep->m_tTriggerTime == m_tTriggerTime) && ((m_nTriggerType & TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEOFFSET) != TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEOFFSET || pStep->m_tTriggerTimeOffset == m_tTriggerTimeOffset) && ((m_nTriggerType & TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEDELAY) != TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEDELAY || pStep->m_tTriggerTimeDelay == m_tTriggerTimeDelay) && ((m_nTriggerType & TCPROCEDURETHREADSTEP_TRIGGERTYPE_SYNCOBJECT) != TCPROCEDURETHREADSTEP_TRIGGERTYPE_SYNCOBJECT || pStep->m_szTriggerObject == m_szTriggerObject) && pStep->m_tTriggerTimeout == m_tTriggerTimeout && pStep->m_szTriggerMessage == m_szTriggerMessage && ((m_nTriggerType & TCPROCEDURETHREADSTEP_TRIGGERTYPE_EXPRESSION) != TCPROCEDURETHREADSTEP_TRIGGERTYPE_EXPRESSION || pStep->m_szTriggerExpression == m_szTriggerExpression) && pStep->m_szPreexecutionExpression == m_szPreexecutionExpression && pStep->m_nConfirmationType == m_nConfirmationType && pStep->m_tConfirmationTimeout == m_tConfirmationTimeout && pStep->m_szConfirmationMessage == m_szConfirmationMessage && ((m_nConfirmationType & TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_EXPRESSION) != TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_EXPRESSION || pStep->m_szConfirmationExpression == m_szConfirmationExpression) && pStep->m_nFailureOptions == m_nFailureOptions && pStep->m_szFailureLabels.GetSize() == m_szFailureLabels.GetSize() && pStep->m_cLabelFont.GetObject(sizeof(LOGFONT), &lfFont[0]) > 0 && m_cLabelFont.GetObject(sizeof(LOGFONT), &lfFont[1]) > 0 && !memcmp(&lfFont[0], &lfFont[1], sizeof(LOGFONT)) && pStep->m_pSubSteps->Compare(m_pSubSteps, bState) && pStep->MapProperties(nInfo[0]) && MapProperties(nInfo[1]) && nInfo[0].GetSize() == nInfo[1].GetSize() && !memcmp(nInfo[0].GetData(), nInfo[1].GetData(), nInfo[0].GetSize())) ? (INT)m_szFailureLabels.GetSize() : -1; nLabel < nLabels; nLabel++)
	{
		if (pStep->m_szFailureLabels.GetAt(nLabel) != m_szFailureLabels.GetAt(nLabel)) break;
		continue;
	}
	return((nLabel == nLabels) ? TRUE : FALSE);
}

BOOL CTCProcedureDocumentItem::Map(CByteArray &nData) CONST
{
	INT  cbData;
	INT  nLabel;
	INT  nLabels;
	CByteArray  nSubStepsData;
	CByteArray  nPropertiesData;
	CByteArray  nFailureLabelsData;
	DATA  sData = { 0 };

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbLabel = (m_szLabel.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	sData.cbTriggerObject = (m_szTriggerObject.GetLength() + 1)*sizeof(TCHAR);
	sData.cbTriggerMessage = (m_szTriggerMessage.GetLength() + 1)*sizeof(TCHAR);
	sData.cbTriggerExpression = (m_szTriggerExpression.GetLength() + 1)*sizeof(TCHAR);
	sData.cbConfirmationMessage = (m_szConfirmationMessage.GetLength() + 1)*sizeof(TCHAR);
	sData.cbPreexecutionExpression = (m_szPreexecutionExpression.GetLength() + 1)*sizeof(TCHAR);
	sData.cbConfirmationExpression = (m_szConfirmationExpression.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProperties = (MapProperties(nPropertiesData)) ? (INT)nPropertiesData.GetSize() : -1;
	sData.cbSubSteps = (m_pSubSteps->Map(nSubStepsData)) ? (INT)nSubStepsData.GetSize() : -1;
	for (nLabel = 0, nLabels = (INT)m_szFailureLabels.GetSize(), sData.cbFailureLabels = 0; nLabel < nLabels; nLabel++, sData.cbFailureLabels += cbData)
	{
		nFailureLabelsData.SetSize(sData.cbFailureLabels + (cbData = (m_szFailureLabels.GetAt(nLabel).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nFailureLabelsData.GetData() + sData.cbFailureLabels, (LPCTSTR)m_szFailureLabels.GetAt(nLabel), cbData);
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbLabel + sData.cbComments + sData.cbTriggerObject + sData.cbTriggerMessage + sData.cbTriggerExpression + sData.cbPreexecutionExpression + sData.cbConfirmationExpression + sData.cbConfirmationMessage + sData.cbFailureLabels + max(sData.cbProperties, 0) + max(sData.cbSubSteps, 0))), sData.nType = GetType(), sData.rPosition.left = GetPosition().left, sData.rPosition.top = GetPosition().top, sData.rPosition.right = GetPosition().right, sData.rPosition.bottom = GetPosition().bottom, sData.nSubThreadID = m_nSubThreadID, sData.bActivated = IsActivated(), sData.bExpanded = IsExpanded(), sData.nTriggerType = m_nTriggerType, sData.tTriggerTime = m_tTriggerTime.GetTime(), sData.tTriggerTimeOffset = m_tTriggerTimeOffset.GetTotalSeconds(), sData.tTriggerTimeDelay = m_tTriggerTimeDelay.GetTotalSeconds(), sData.tTriggerTimeout = m_tTriggerTimeout.GetTotalSeconds(), sData.nConfirmationType = m_nConfirmationType, sData.tConfirmationTimeout = m_tConfirmationTimeout.GetTotalSeconds(), sData.nFailureOptions = m_nFailureOptions; nData.GetSize() == sData.cbSize && sData.cbProperties >= 0 && sData.cbSubSteps >= 0; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szLabel, sData.cbLabel);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbLabel), (LPCTSTR)m_szComments, sData.cbComments);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbComments), (LPCTSTR)m_szTriggerObject, sData.cbTriggerObject);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbTriggerObject), (LPCTSTR)m_szTriggerMessage, sData.cbTriggerMessage);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbTriggerMessage), (LPCTSTR)m_szTriggerExpression, sData.cbTriggerExpression);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbTriggerExpression), (LPCTSTR)m_szPreexecutionExpression, sData.cbPreexecutionExpression);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbPreexecutionExpression), (LPCTSTR)m_szConfirmationExpression, sData.cbConfirmationExpression);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbConfirmationExpression), (LPCTSTR)m_szConfirmationMessage, sData.cbConfirmationMessage);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbConfirmationMessage), nFailureLabelsData.GetData(), sData.cbFailureLabels);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbFailureLabels), nPropertiesData.GetData(), sData.cbProperties);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbProperties), nSubStepsData.GetData(), sData.cbSubSteps);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcedureDocumentItem::Map(CDatabaseTCProcedureThreadStep *pItem) CONST
{
	CByteArray  nInfo;
	CDatabaseTCProcedureThreadContents  pContents;

	for (pItem->SetName(m_szName), pItem->SetType(m_nType), pItem->SetLabel(m_szLabel), pItem->SetComments(m_szComments), pItem->SetPosition(m_rPosition), pItem->SetSubThreadID(m_nSubThreadID), pItem->Activate(m_bActivated), pItem->Expand(m_bExpanded), pItem->SetTriggerType(m_nTriggerType), pItem->SetTriggerTime(m_tTriggerTime), pItem->SetTriggerTimeOffset(m_tTriggerTimeOffset), pItem->SetTriggerTimeDelay(m_tTriggerTimeDelay), pItem->SetTriggerSynchronizationObject(m_szTriggerObject), pItem->SetTriggerTimeout(m_tTriggerTimeout), pItem->SetTriggerMessage(m_szTriggerMessage), pItem->SetTriggerExpression(m_szTriggerExpression), pItem->SetPreexecutionExpression(m_szPreexecutionExpression), pItem->SetConfirmationType(m_nConfirmationType), pItem->SetConfirmationTimeout(m_tConfirmationTimeout), pItem->SetConfirmationMessage(m_szConfirmationMessage), pItem->SetConfirmationExpression(m_szConfirmationExpression), pItem->SetFailureOptions(m_nFailureOptions), pItem->SetFailureLabels(m_szFailureLabels); MapProperties(nInfo) && GetSubSteps()->Map(&pContents); )
	{
		pItem->SetSubSteps(pContents);
		pItem->SetProperties(nInfo);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentItem::Unmap(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbLabel;
	INT  cbLabels;
	CByteArray  nSubStepsData;
	CByteArray  nPropertiesData;
	CByteArray  nFailureLabelsData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbLabel + sData.cbComments + sData.cbTriggerObject + sData.cbTriggerMessage + sData.cbTriggerExpression + sData.cbPreexecutionExpression + sData.cbConfirmationExpression + sData.cbConfirmationMessage + sData.cbFailureLabels + sData.cbProperties + sData.cbSubSteps && sData.cbName > 0 && sData.cbLabel > 0 && sData.cbComments > 0 && sData.cbTriggerObject > 0 && sData.cbTriggerMessage > 0 && sData.cbTriggerExpression > 0 && sData.cbPreexecutionExpression > 0 && sData.cbConfirmationExpression > 0 && sData.cbConfirmationMessage > 0 && sData.cbFailureLabels >= 0 && sData.cbProperties >= 0 && sData.cbSubSteps >= 0; )
	{
		for (nFailureLabelsData.SetSize(sData.cbFailureLabels), nPropertiesData.SetSize(sData.cbProperties), nSubStepsData.SetSize(sData.cbSubSteps), CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), CopyMemory(m_szLabel.GetBufferSetLength(STRINGCHARS(sData.cbLabel)), nData.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbLabel)), CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nData.GetData() + (cbData = cbData + sData.cbLabel), STRINGBYTES(sData.cbComments)), CopyMemory(m_szTriggerObject.GetBufferSetLength(STRINGCHARS(sData.cbTriggerObject)), nData.GetData() + (cbData = cbData + sData.cbComments), STRINGBYTES(sData.cbTriggerObject)), CopyMemory(m_szTriggerMessage.GetBufferSetLength(STRINGCHARS(sData.cbTriggerMessage)), nData.GetData() + (cbData = cbData + sData.cbTriggerObject), STRINGBYTES(sData.cbTriggerMessage)), CopyMemory(m_szTriggerExpression.GetBufferSetLength(STRINGCHARS(sData.cbTriggerExpression)), nData.GetData() + (cbData = cbData + sData.cbTriggerMessage), STRINGBYTES(sData.cbTriggerExpression)), CopyMemory(m_szPreexecutionExpression.GetBufferSetLength(STRINGCHARS(sData.cbPreexecutionExpression)), nData.GetData() + (cbData = cbData + sData.cbTriggerExpression), STRINGBYTES(sData.cbPreexecutionExpression)), CopyMemory(m_szConfirmationExpression.GetBufferSetLength(STRINGCHARS(sData.cbConfirmationExpression)), nData.GetData() + (cbData = cbData + sData.cbPreexecutionExpression), STRINGBYTES(sData.cbConfirmationExpression)), CopyMemory(m_szConfirmationMessage.GetBufferSetLength(STRINGCHARS(sData.cbConfirmationMessage)), nData.GetData() + (cbData = cbData + sData.cbConfirmationExpression), STRINGBYTES(sData.cbConfirmationMessage)), CopyMemory(nFailureLabelsData.GetData(), nData.GetData() + (cbData = cbData + sData.cbConfirmationMessage), sData.cbFailureLabels), CopyMemory(nPropertiesData.GetData(), nData.GetData() + (cbData = cbData + sData.cbFailureLabels), sData.cbProperties), CopyMemory(nSubStepsData.GetData(), nData.GetData() + (cbData = cbData + sData.cbProperties), sData.cbSubSteps), m_nType = sData.nType, m_nSubThreadID = sData.nSubThreadID, m_rPosition = sData.rPosition, m_bActivated = sData.bActivated, m_bExpanded = sData.bExpanded, m_nTriggerType = sData.nTriggerType, m_tTriggerTime = sData.tTriggerTime, m_tTriggerTimeOffset = sData.tTriggerTimeOffset, m_tTriggerTimeDelay = sData.tTriggerTimeDelay, m_tTriggerTimeout = sData.tTriggerTimeout, m_nConfirmationType = sData.nConfirmationType, m_tConfirmationTimeout = sData.tConfirmationTimeout, m_nFailureOptions = sData.nFailureOptions, m_nInfo.Copy(nPropertiesData), m_szName.ReleaseBuffer(), m_szLabel.ReleaseBuffer(), m_szComments.ReleaseBuffer(), m_szTriggerObject.ReleaseBuffer(), m_szTriggerMessage.ReleaseBuffer(), m_szTriggerExpression.ReleaseBuffer(), m_szPreexecutionExpression.ReleaseBuffer(), m_szConfirmationExpression.ReleaseBuffer(), m_szConfirmationMessage.ReleaseBuffer(), m_szFailureLabels.RemoveAll(), cbLabels = 0; cbLabels < sData.cbFailureLabels; cbLabels += cbLabel)
		{
			m_szFailureLabels.Add((LPCTSTR)(nFailureLabelsData.GetData() + cbLabels));
			cbLabel = (m_szFailureLabels.GetAt(m_szFailureLabels.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
		}
		return((UnmapProperties(nPropertiesData) && m_pSubSteps->Unmap(nSubStepsData)) ? TRUE : FALSE);
	}
	return FALSE;
}
BOOL CTCProcedureDocumentItem::Unmap(CONST CDatabaseTCProcedureThreadStep *pItem)
{
	CByteArray  nInfo;
	CDatabaseTCProcedureThreadContents  pContents;

	for (m_szName = pItem->GetName(), m_nType = pItem->GetType(), m_szLabel = pItem->GetLabel(), m_szComments = pItem->GetComments(), m_rPosition = pItem->GetPosition(), m_nSubThreadID = pItem->GetSubThreadID(), m_bActivated = pItem->IsActivated(), m_bExpanded = pItem->IsExpanded(), m_nTriggerType = pItem->GetTriggerType(), m_tTriggerTime = pItem->GetTriggerTime(), m_tTriggerTimeOffset = pItem->GetTriggerTimeOffset(), m_tTriggerTimeDelay = pItem->GetTriggerTimeDelay(), m_szTriggerObject = pItem->GetTriggerSynchronizationObject(), m_tTriggerTimeout = pItem->GetTriggerTimeout(), m_szTriggerMessage = pItem->GetTriggerMessage(), m_szTriggerExpression = pItem->GetTriggerExpression(), m_szPreexecutionExpression = pItem->GetPreexecutionExpression(), m_nConfirmationType = pItem->GetConfirmationType(), m_tConfirmationTimeout = pItem->GetConfirmationTimeout(), m_szConfirmationMessage = pItem->GetConfirmationMessage(), m_szConfirmationExpression = pItem->GetConfirmationExpression(), m_nFailureOptions = pItem->GetFailureOptions(), pItem->GetFailureLabels(m_szFailureLabels), pItem->GetSubSteps(pContents), pItem->GetProperties(nInfo); UnmapProperties(nInfo) && GetSubSteps()->Unmap(&pContents); ) return TRUE;
	return FALSE;
}

CTCProcedureDocument *CTCProcedureDocumentItem::GetSubSteps() CONST
{
	return m_pSubSteps;
}

VOID CTCProcedureDocumentItem::Relocate(CONST POINT &ptOffset)
{
	SetPosition(GetPosition() + ptOffset);
	Relocate(this, ptOffset);
}
VOID CTCProcedureDocumentItem::Relocate(CTCProcedureDocumentItem *pStep, CONST POINT &ptOffset)
{
	POSITION  lPosition;
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pSubItem;

	for (lPosition = (pDocument = pStep->GetSubSteps())->GetStartPosition(); lPosition; )
	{
		if ((pSubItem = pDocument->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			pSubItem->SetPosition(pSubItem->GetPosition() + ptOffset);
			Relocate(pSubItem, ptOffset);
		}
	}
}

VOID CTCProcedureDocumentItem::DrawContents(CDC *pDC)
{
	return;
}

VOID CTCProcedureDocumentItem::DrawLabels(CDC *pDC)
{
	return;
}

VOID CTCProcedureDocumentItem::DrawConnectionLine(CDC *pDC, CONST POINT &ptFrom, CONST POINT &ptTo)
{
	DrawConnectionLine(pDC, ptFrom, ptTo, CRect(0, 0, 0, 0));
}
VOID CTCProcedureDocumentItem::DrawConnectionLine(CDC *pDC, CONST POINT &pt1, CONST POINT &pt2, CONST POINT &pt3)
{
	CRect  rEdge;
	CPoint  ptEdge;

	for (rEdge.SetRectEmpty(); pt1.x == pt2.x; )
	{
		rEdge.SetRect(pt1.x < pt3.x, min(pt1.y, pt2.y) == pt3.y, pt1.x > pt3.x, max(pt1.y, pt2.y) == pt3.y);
		ptEdge = (pt1.y == pt3.y) ? pt1 : pt2;
		break;
	}
	if (pt2.x == pt3.x)
	{
		rEdge.SetRect(pt2.x < pt1.x, min(pt2.y, pt3.y) == pt1.y, pt2.x > pt1.x, max(pt2.y, pt3.y) == pt1.y);
		ptEdge = (pt2.y == pt1.y) ? pt2 : pt3;
	}
	if (pt3.x == pt1.x)
	{
		rEdge.SetRect(pt3.x < pt2.x, min(pt3.y, pt1.y) == pt2.y, pt3.x > pt2.x, max(pt3.y, pt1.y) == pt2.y);
		ptEdge = (pt3.y == pt2.y) ? pt3 : pt1;
	}
	if (!rEdge.IsRectNull())
	{
		DrawConnectionLine(pDC, (ptEdge == pt2 || ptEdge == pt3) ? pt1 : pt2, (ptEdge == pt1 || ptEdge == pt2) ? pt3 : pt2, rEdge);
		return;
	}
}
VOID CTCProcedureDocumentItem::DrawConnectionLine(CDC *pDC, CONST POINT &ptFrom, CONST POINT &ptTo, CONST RECT &rEdge)
{
	CPen  cPen[3];
	CPen  *pOldPen;
	CPoint  ptEdges[4];

	if (cPen[0].CreatePen(PS_SOLID, 1, VGA_COLOR_BLACK))
	{
		if (cPen[1].CreatePen(PS_SOLID, 1, VGA_COLOR_WHITE))
		{
			if (cPen[2].CreatePen(PS_SOLID, 1, VGA_COLOR_GRAY))
			{
				if (ptFrom.x == ptTo.x  &&  ptFrom.y != ptTo.y)
				{
					if ((pOldPen = pDC->SelectObject(&cPen[0])))
					{
						pDC->MoveTo(ptFrom.x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2, ptFrom.y);
						pDC->LineTo(ptTo.x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2, ptTo.y);
						pDC->MoveTo(ptFrom.x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1, ptFrom.y);
						pDC->LineTo(ptTo.x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1, ptTo.y);
						pDC->SelectObject(pOldPen);
					}
					if ((pOldPen = pDC->SelectObject(&cPen[1])))
					{
						pDC->MoveTo(ptFrom.x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1, ptFrom.y);
						pDC->LineTo(ptTo.x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1, ptTo.y);
						pDC->SelectObject(pOldPen);
					}
					if ((pOldPen = pDC->SelectObject(&cPen[2])))
					{
						pDC->MoveTo(ptFrom.x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2, ptFrom.y);
						pDC->LineTo(ptTo.x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2, ptTo.y);
						pDC->MoveTo(ptFrom.x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2, ptFrom.y);
						pDC->LineTo(ptTo.x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2, ptTo.y);
						pDC->MoveTo(ptFrom.x, ptFrom.y);
						pDC->LineTo(ptTo.x, ptTo.y);
						pDC->SelectObject(pOldPen);
					}
				}
				if (ptFrom.x != ptTo.x  &&  ptFrom.y == ptTo.y)
				{
					if ((pOldPen = pDC->SelectObject(&cPen[0])))
					{
						pDC->MoveTo(ptFrom.x, ptFrom.y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2);
						pDC->LineTo(ptTo.x, ptTo.y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2);
						pDC->MoveTo(ptFrom.x, ptFrom.y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1);
						pDC->LineTo(ptTo.x, ptTo.y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1);
						pDC->SelectObject(pOldPen);
					}
					if ((pOldPen = pDC->SelectObject(&cPen[1])))
					{
						pDC->MoveTo(ptFrom.x, ptFrom.y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1);
						pDC->LineTo(ptTo.x, ptTo.y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1);
						pDC->SelectObject(pOldPen);
					}
					if ((pOldPen = pDC->SelectObject(&cPen[2])))
					{
						pDC->MoveTo(ptFrom.x, ptFrom.y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2);
						pDC->LineTo(ptTo.x, ptTo.y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2);
						pDC->MoveTo(ptFrom.x, ptFrom.y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2);
						pDC->LineTo(ptTo.x, ptTo.y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2);
						pDC->MoveTo(ptFrom.x, ptFrom.y);
						pDC->LineTo(ptTo.x, ptTo.y);
						pDC->SelectObject(pOldPen);
					}
				}
				if (ptFrom.x != ptTo.x  &&  ptFrom.y != ptTo.y)
				{
					if (!rEdge.top  &&  !rEdge.bottom)
					{
						if (ptFrom.y <= ptTo.y)
						{
							ptEdges[0] = ptFrom;
							ptEdges[1].x = ptFrom.x;
							ptEdges[1].y = (ptFrom.y + ptTo.y) / 2;
							ptEdges[2].x = ptTo.x;
							ptEdges[2].y = ptEdges[1].y;
							ptEdges[3] = ptTo;
						}
						else
						{
							ptEdges[0] = ptTo;
							ptEdges[1].x = ptTo.x;
							ptEdges[1].y = (ptFrom.y + ptTo.y) / 2;
							ptEdges[2].x = ptFrom.x;
							ptEdges[2].y = ptEdges[1].y;
							ptEdges[3] = ptFrom;
						}
					}
					if (rEdge.top)
					{
						if (ptFrom.y <= ptTo.y)
						{
							ptEdges[0] = ptEdges[1] = ptFrom;
							ptEdges[2].x = ptTo.x;
							ptEdges[2].y = ptFrom.y;
							ptEdges[3] = ptTo;
						}
						else
						{
							ptEdges[0] = ptEdges[1] = ptTo;
							ptEdges[2].x = ptFrom.x;
							ptEdges[2].y = ptTo.y;
							ptEdges[3] = ptFrom;
						}
					}
					if (rEdge.bottom)
					{
						if (ptFrom.y <= ptTo.y)
						{
							ptEdges[0] = ptFrom;
							ptEdges[1].x = ptFrom.x;
							ptEdges[1].y = ptTo.y;
							ptEdges[2] = ptEdges[3] = ptTo;
						}
						else
						{
							ptEdges[0] = ptTo;
							ptEdges[1].x = ptTo.x;
							ptEdges[1].y = ptFrom.y;
							ptEdges[2] = ptEdges[3] = ptFrom;
						}
					}
					if ((pOldPen = pDC->SelectObject(&cPen[0])))
					{
						pDC->MoveTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2), ptEdges[0].y);
						pDC->LineTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[1].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[1].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[2].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[2].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2), ptEdges[3].y);
						pDC->MoveTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1), ptEdges[0].y);
						pDC->LineTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[1].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[1].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[2].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[2].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1), ptEdges[3].y);
						pDC->SelectObject(pOldPen);
					}
					if ((pOldPen = pDC->SelectObject(&cPen[1])))
					{
						pDC->MoveTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1), ptEdges[0].y);
						pDC->LineTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1), ptEdges[1].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1);
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1), ptEdges[1].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1);
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1), ptEdges[3].y);
						pDC->SelectObject(pOldPen);
					}
					if ((pOldPen = pDC->SelectObject(&cPen[2])))
					{
						pDC->MoveTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2), ptEdges[0].y);
						pDC->LineTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[1].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2) : (ptEdges[1].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[2].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2) : (ptEdges[2].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2), ptEdges[3].y);
						pDC->MoveTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2), ptEdges[0].y);
						pDC->LineTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[1].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2) : (ptEdges[1].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2), (ptEdges[0].x <= ptEdges[3].x) ? (ptEdges[2].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 2) : (ptEdges[2].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2));
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 2), ptEdges[3].y);
						pDC->MoveTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[0].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[0].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : ptEdges[0].x, ptEdges[0].y);
						pDC->LineTo((ptEdges[0] == ptEdges[1]) ? ((rEdge.right) ? (ptEdges[1].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2) : (ptEdges[1].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)) : ptEdges[1].x, ptEdges[1].y);
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[2].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[2].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : ptEdges[2].x, ptEdges[2].y);
						pDC->LineTo((ptEdges[2] == ptEdges[3]) ? ((rEdge.left) ? (ptEdges[3].x + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : (ptEdges[3].x - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2)) : ptEdges[3].x, ptEdges[3].y);
						pDC->SelectObject(pOldPen);
					}
				}
				cPen[2].DeleteObject();
			}
			cPen[1].DeleteObject();
		}
		cPen[0].DeleteObject();
	}
}

VOID CTCProcedureDocumentItem::DrawLabelSymbol(CDC *pDC, CONST RECT &rect, LPCTSTR pszLabel)
{
	DrawLabelSymbol(pDC, rect, DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX | DT_WORDBREAK, pszLabel);
}
VOID CTCProcedureDocumentItem::DrawLabelSymbol(CDC *pDC, CONST RECT &rect, UINT nFlags, LPCTSTR pszLabel)
{
	INT  nOldMode;
	CRect  rLabel;
	CFont  *pOldFont;
	COLORREF  nOldColor;
	TEXTMETRIC  tmFont;

	if (lstrlen(pszLabel) > 0)
	{
		nOldMode = pDC->SetBkMode(TRANSPARENT);
		nOldColor = pDC->SetTextColor(m_nLabelColor);
		if ((pOldFont = pDC->SelectObject(&m_cLabelFont)))
		{
			for (pDC->DrawText(pszLabel, (rLabel = CRect(rect)), DT_CALCRECT | (nFlags & ~DT_VCENTER)); pDC->GetTextMetrics(&tmFont); )
			{
				rLabel.SetRect(rLabel.left, rLabel.top, rLabel.right, (rLabel.bottom > rect.bottom) ? (rLabel.top + tmFont.tmHeight*((rect.bottom - rect.top) / tmFont.tmHeight)) : rLabel.bottom);
				break;
			}
			pDC->DrawText(pszLabel, (rLabel = CRect(rect.left, (nFlags & DT_VCENTER) ? max((rect.top + rect.bottom) / 2 - rLabel.Height() / 2, rect.top) : rect.top, rect.right, rect.bottom)), nFlags);
			pDC->SelectObject(pOldFont);
		}
		pDC->SetTextColor(nOldColor);
		pDC->SetBkMode(nOldMode);
	}
}

VOID CTCProcedureDocumentItem::DrawSymbol(CDC *pDC, UINT nBitmapID, INT x, INT y, LPCRECT lpClip)
{
	CImage  cSymbol;

	if (LoadSymbol(nBitmapID, cSymbol))
	{
		DrawSymbol(pDC, cSymbol, x, y, lpClip);
		cSymbol.Destroy();
	}
}
VOID CTCProcedureDocumentItem::DrawSymbol(CDC *pDC, CImage &cSymbol, INT x, INT y, LPCRECT lpClip)
{
	CRect  rSymbol;

	for (rSymbol.SetRectEmpty(); lpClip != (LPCRECT)NULL; )
	{
		rSymbol.SetRect((lpClip->left != 0) ? (cSymbol.GetWidth() / lpClip->left) : 0, (lpClip->top != 0) ? (cSymbol.GetHeight() / lpClip->top) : 0, (lpClip->right != 0) ? (cSymbol.GetWidth() / lpClip->right) : 0, (lpClip->bottom != 0) ? (cSymbol.GetHeight() / lpClip->bottom) : 0);
		break;
	}
	cSymbol.TransparentBlt(pDC->GetSafeHdc(), x, y, (rSymbol.Width() > 0) ? rSymbol.Width() : cSymbol.GetWidth(), (rSymbol.Height() > 0) ? rSymbol.Height() : cSymbol.GetHeight(), TCPROCEDUREDOCUMENTITEM_TRANSPARENTCOLOR);
}

BOOL CTCProcedureDocumentItem::LoadSymbol(UINT nBitmapID, CImage &cSymbol) CONST
{
	return LoadSymbol(MAKEINTRESOURCE(nBitmapID), cSymbol);
}
BOOL CTCProcedureDocumentItem::LoadSymbol(LPCTSTR pszBitmapName, CImage &cSymbol) CONST
{
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	if ((hResource = FindResource((hModule = GetLibraryModuleInstance()), pszBitmapName, STRING(IDS_RESOURCETYPE_PICTURE))))
	{
		if ((hMemResource[0] = LoadResource(hModule, hResource)))
		{
			if ((pResource = LockResource(hMemResource[0])))
			{
				if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
				{
					if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
					{
						if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)))
						{
							if (SUCCEEDED(cSymbol.Load(pIStream)))
							{
								pIStream->Release();
								return TRUE;
							}
						}
						pIStream->Release();
					}
				}
			}
		}
	}
	return FALSE;
}

CSize CTCProcedureDocumentItem::CalcSymbolSize(UINT nBitmapID) CONST
{
	return CalcSymbolSize(MAKEINTRESOURCE(nBitmapID));
}
CSize CTCProcedureDocumentItem::CalcSymbolSize(LPCTSTR pszBitmapName) CONST
{
	CImage  cSymbol;
	CSize  sizeSymbol;

	for (sizeSymbol.cx = sizeSymbol.cy = 0; LoadSymbol(pszBitmapName, cSymbol); )
	{
		sizeSymbol.cx = cSymbol.GetWidth();
		sizeSymbol.cy = cSymbol.GetHeight();
		cSymbol.Destroy();
		break;
	}
	return sizeSymbol;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentItem, COleClientItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentStartItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentStartItem, CTCProcedureDocumentItem)

CTCProcedureDocumentStartItem::CTCProcedureDocumentStartItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_START, m_szLabel = (!nSubThreadID) ? STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_START) : EMPTYSTRING; LoadSymbol((!nSubThreadID) ? IDP_TCFLOWCONTROLSTARTSYMBOL : IDP_TCFLOWCONTROLSTARTSUBSYMBOL, m_cSymbol[0]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		break;
	}
}

CTCProcedureDocumentStartItem::~CTCProcedureDocumentStartItem()
{
	m_cSymbol[0].Destroy();
}

BOOL CTCProcedureDocumentStartItem::CanSelect() CONST
{
	return TRUE;
}

CPoint CTCProcedureDocumentStartItem::CalcConnectionPoint(BOOL bIn, BOOL bExpanded) CONST
{
	CPoint  pt;

	for (pt.x = pt.y = 0; bIn; )
	{
		pt.x = 0;
		pt.y = 0;
		return pt;
	}
	if (!bIn)
	{
		pt.x = m_rPosition.left + m_sizeSymbol[0].cx / 2;
		pt.y = m_rPosition.bottom;
		return pt;
	}
	return pt;
}

VOID CTCProcedureDocumentStartItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	LOGFONT  lfLabel;
	CFontTools  cFontTools;

	rLabel.SetRect(0, (m_cLabelFont.GetLogFont(&lfLabel) > 0) ? (m_rPosition.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT - cFontTools.QueryHeight(&lfLabel)) : (m_rPosition.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT), 2 * m_rPosition.CenterPoint().x, m_rPosition.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT);
	DrawLabelSymbol(pDC, rLabel, DT_SINGLELINE | DT_CENTER | DT_BOTTOM | DT_END_ELLIPSIS | DT_NOPREFIX, m_szLabel);
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentStartItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentStartItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentStartItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentBranchItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentBranchItem, CTCProcedureDocumentItem)

CTCProcedureDocumentBranchItem::CTCProcedureDocumentBranchItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	CTCProcedureDocumentItem  *pStep[4];

	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_BRANCH; LoadSymbol(IDP_TCFLOWCONTROLBRANCHSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLBRANCHSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
	if (!m_pSubSteps->GetStepCount(TRUE))
	{
		if ((pStep[0] = new CTCProcedureDocumentStartItem(m_pSubSteps, nSubThreadID + 1)))
		{
			if ((pStep[1] = new CTCProcedureDocumentEndItem(m_pSubSteps, nSubThreadID + 1)))
			{
				if ((pStep[2] = new CTCProcedureDocumentStartItem(m_pSubSteps, nSubThreadID + 1 + 1)))
				{
					if ((pStep[3] = new CTCProcedureDocumentEndItem(m_pSubSteps, nSubThreadID + 1 + 1))) return;
					delete pStep[2];
				}
				delete pStep[1];
			}
			delete pStep[0];
		}
	}
}

CTCProcedureDocumentBranchItem::~CTCProcedureDocumentBranchItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

VOID CTCProcedureDocumentBranchItem::SetInvariantCondition(LPCTSTR pszCondition)
{
	m_szExpression[0] = pszCondition;
}

CString CTCProcedureDocumentBranchItem::GetInvariantCondition() CONST
{
	return m_szExpression[0];
}

VOID CTCProcedureDocumentBranchItem::SetTestExpression(LPCTSTR pszExpression)
{
	m_szExpression[1] = pszExpression;
}

CString CTCProcedureDocumentBranchItem::GetTestExpression() CONST
{
	return m_szExpression[1];
}

BOOL CTCProcedureDocumentBranchItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentBranchItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentBranchItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentBranchItem::RecalcLayout()
{
	CRect  rStep;
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptTrueBranch[2];
	CPoint  ptFalseBranch[2];
	CTCProcedureDocumentItem  *pStep;
	POSITION  lPosition;

	for (lPosition = m_pSubSteps->GetStartPosition(), rContents = CalcLayoutPositions(rSymbol, ptTrueBranch[0], ptTrueBranch[1], ptFalseBranch[0], ptFalseBranch[1], rLabel); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				if (pStep->GetSubThreadID() == GetSubThreadID() + 1)
				{
					rStep.SetRect(ptFalseBranch[0].x - pStep->GetImageSize().cx / 2, ptFalseBranch[0].y - pStep->GetImageSize().cy / 2, ptFalseBranch[0].x + pStep->GetImageSize().cx / 2, ptFalseBranch[0].y + pStep->GetImageSize().cy / 2);
					pStep->SetPosition(rStep);
					continue;
				}
				rStep.SetRect(ptTrueBranch[0].x - pStep->GetImageSize().cx / 2, ptTrueBranch[0].y - pStep->GetImageSize().cy / 2, ptTrueBranch[0].x + pStep->GetImageSize().cx / 2, ptTrueBranch[0].y + pStep->GetImageSize().cy / 2);
				pStep->SetPosition(rStep);
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				if (pStep->GetSubThreadID() == GetSubThreadID() + 1)
				{
					rStep.SetRect(ptFalseBranch[1].x - pStep->GetImageSize().cx / 2, ptFalseBranch[1].y - pStep->GetImageSize().cy / 2, ptFalseBranch[1].x + pStep->GetImageSize().cx / 2, ptFalseBranch[1].y + pStep->GetImageSize().cy / 2);
					pStep->SetPosition(rStep);
					continue;
				}
				rStep.SetRect(ptTrueBranch[1].x - pStep->GetImageSize().cx / 2, ptTrueBranch[1].y - pStep->GetImageSize().cy / 2, ptTrueBranch[1].x + pStep->GetImageSize().cx / 2, ptTrueBranch[1].y + pStep->GetImageSize().cy / 2);
				pStep->SetPosition(rStep);
				continue;
			}
			if (pStep->GetSubThreadID() == GetSubThreadID() + 1)
			{
				for (rStep.SetRect(ptFalseBranch[0].x - pStep->GetImageSize().cx / 2, pStep->GetPosition().top, ptFalseBranch[0].x + pStep->GetImageSize().cx / 2, pStep->GetPosition().bottom), rStep.OffsetRect(pStep->GetPosition().left + pStep->GetImageSize().cx / 2 - pStep->CalcConnectionPoint().x, 0); pStep->GetPosition().left != rStep.left; )
				{
					pStep->Relocate(CPoint(rStep.left - pStep->GetPosition().left, 0));
					break;
				}
				continue;
			}
			for (rStep.SetRect(ptTrueBranch[0].x - pStep->GetImageSize().cx / 2, pStep->GetPosition().top, ptTrueBranch[0].x + pStep->GetImageSize().cx / 2, pStep->GetPosition().bottom), rStep.OffsetRect(pStep->GetPosition().left + pStep->GetImageSize().cx / 2 - pStep->CalcConnectionPoint().x, 0); pStep->GetPosition().left != rStep.left; )
			{
				pStep->Relocate(CPoint(rStep.left - pStep->GetPosition().left, 0));
				break;
			}
		}
	}
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentBranchItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentBranchItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbExpression[0] = (m_szExpression[0].GetLength() + 1)*sizeof(TCHAR)) + (sData.cbExpression[1] = (m_szExpression[1].GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szExpression[0], sData.cbExpression[0]);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbExpression[0]), (LPCTSTR)m_szExpression[1], sData.cbExpression[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentBranchItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbExpression[0] + sData.cbExpression[1] && sData.cbExpression[0] > 0 && sData.cbExpression[1] > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szExpression[0].GetBufferSetLength(STRINGCHARS(sData.cbExpression[0])), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbExpression[0]));
		CopyMemory(m_szExpression[1].GetBufferSetLength(STRINGCHARS(sData.cbExpression[1])), nData.GetData() + (cbData = cbData + sData.cbExpression[0]), STRINGBYTES(sData.cbExpression[1]));
		m_szExpression[0].ReleaseBuffer();
		m_szExpression[1].ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentBranchItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptLine[10];
	CPoint  ptTrueBranch[2];
	CPoint  ptFalseBranch[2];

	if (m_bExpanded)
	{
		rContents = CalcLayoutPositions(rSymbol, ptTrueBranch[0], ptTrueBranch[1], ptFalseBranch[0], ptFalseBranch[1], rLabel);
		ptLine[0] = CalcConnectionPoint(FALSE, FALSE);
		ptLine[1].x = rSymbol.CenterPoint().x;
		ptLine[1].y = rSymbol.top;
		ptLine[2].x = rSymbol.left;
		ptLine[2].y = rSymbol.CenterPoint().y;
		ptLine[3] = ptFalseBranch[0];
		ptLine[4].x = rSymbol.right;
		ptLine[4].y = rSymbol.CenterPoint().y;
		ptLine[5] = ptTrueBranch[0];
		ptLine[6] = ptFalseBranch[1];
		ptLine[7] = ptTrueBranch[1];
		ptLine[8].x = ptLine[1].x;
		ptLine[8].y = ptLine[6].y;
		ptLine[9].x = ptLine[0].x;
		ptLine[9].y = rContents.bottom;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawConnectionLine(pDC, ptLine[2], ptLine[3]);
		DrawConnectionLine(pDC, ptLine[4], ptLine[5]);
		DrawConnectionLine(pDC, ptLine[6], ptLine[7]);
		DrawConnectionLine(pDC, CPoint(ptLine[8].x, (ptLine[8].y = ptLine[8].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1)), ptLine[9]);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[0].x + ptLine[1].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[0].y + ptLine[1].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL, (ptLine[8].x + ptLine[9].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cx / 2, (ptLine[8].y + ptLine[9].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cy / 2);
		DrawSymbol(pDC, m_cSymbol[2], ptLine[1].x - m_sizeSymbol[2].cx / 2, ptLine[1].y);
	}
}

VOID CTCProcedureDocumentBranchItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CPoint  ptTrueBranch[2];
	CPoint  ptFalseBranch[2];
	CTCProcedureDocumentItem  *pStep;
	POSITION  lPosition;

	for (CalcLayoutPositions(rSymbol, ptTrueBranch[0], ptTrueBranch[1], ptFalseBranch[0], ptFalseBranch[1], rLabel); !m_nSubThreadID || m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	for (lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) && pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END  &&  !pStep->IsExpanded())
		{
			rLabel.SetRect(pStep->GetPosition().left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, pStep->GetPosition().bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT, pStep->GetPosition().right, pStep->GetPosition().bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT);
			DrawLabelSymbol(pDC, rLabel, pStep->GetLabel());
		}
	}
}

CRect CTCProcedureDocumentBranchItem::CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartTrueBranch, CPoint &ptEndTrueBranch, CPoint &ptStartFalseBranch, CPoint &ptEndFalseBranch, CRect &rLabel) CONST
{
	INT  nHeight[2];
	CRect  rContents;
	CSize  sizeBranch[2];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), sizeBranch[0].cx = sizeBranch[0].cy = 0, sizeBranch[1].cx = sizeBranch[1].cy = 0, nHeight[0] = 0, nHeight[1] = 0; lPosition; )
	{
		if ((pStep = (CTCProcedureDocumentItem *)m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START || pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				nHeight[0] += (pStep->GetSubThreadID() == GetSubThreadID() + 1) ? pStep->GetImageSize().cy / 2 : 0;
				nHeight[1] += (pStep->GetSubThreadID() != GetSubThreadID() + 1) ? pStep->GetImageSize().cy / 2 : 0;
				continue;
			}
			if (pStep->GetSubThreadID() == GetSubThreadID() + 1)
			{
				for (; pStep->GetPosition().Width() > sizeBranch[0].cx; )
				{
					sizeBranch[0].cx = pStep->GetPosition().Width();
					break;
				}
				sizeBranch[0].cy = max(pStep->GetPosition().bottom - nHeight[0], sizeBranch[0].cy);
				continue;
			}
			for (; pStep->GetPosition().Width() > sizeBranch[1].cx; )
			{
				sizeBranch[1].cx = pStep->GetPosition().Width();
				break;
			}
			sizeBranch[1].cy = max(pStep->GetPosition().bottom - nHeight[1], sizeBranch[1].cy);
		}
	}
	rSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + max(sizeBranch[0].cx - m_sizeSymbol[0].cx, 0) - m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + max(sizeBranch[0].cx - m_sizeSymbol[0].cx, 0) + m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + m_sizeSymbol[2].cy);
	ptStartTrueBranch.x = rSymbol.right + m_sizeSymbol[0].cx;
	ptStartTrueBranch.y = rSymbol.CenterPoint().y;
	ptEndTrueBranch.x = ptStartTrueBranch.x;
	ptEndTrueBranch.y = ptStartTrueBranch.y + max(nHeight[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + max(sizeBranch[0].cy - ptStartTrueBranch.y, 0), nHeight[1] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + max(sizeBranch[1].cy - ptStartTrueBranch.y, 0));
	ptStartFalseBranch.x = rSymbol.left - m_sizeSymbol[0].cx - max(sizeBranch[0].cx - m_sizeSymbol[0].cx, 0);
	ptStartFalseBranch.y = rSymbol.CenterPoint().y;
	ptEndFalseBranch.x = ptStartFalseBranch.x;
	ptEndFalseBranch.y = ptEndTrueBranch.y;
	rContents.SetRect(ptStartFalseBranch.x - m_sizeSymbol[0].cx / 2 - (CalcConnectionPoint().x - m_rPosition.left - m_sizeSymbol[0].cx / 2), rSymbol.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, ptStartTrueBranch.x + m_sizeSymbol[0].cx / 2 - (CalcConnectionPoint().x - m_rPosition.left - m_sizeSymbol[0].cx / 2) + max(sizeBranch[1].cx - m_sizeSymbol[0].cx, 0), max(ptEndTrueBranch.y, ptEndFalseBranch.y) + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentBranchItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentBranchItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentBranchItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSwitchItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentSwitchItem, CTCProcedureDocumentItem)

CTCProcedureDocumentSwitchItem::CTCProcedureDocumentSwitchItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_SWITCH, m_nBranchCount = 0; LoadSymbol(IDP_TCFLOWCONTROLSWITCHSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLSWITCHSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
}

CTCProcedureDocumentSwitchItem::~CTCProcedureDocumentSwitchItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

VOID CTCProcedureDocumentSwitchItem::SetBranches(INT nCount)
{
	INT  nBranch;
	INT  nBranches;
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep[2];

	for (lPosition = m_pSubSteps->GetStartPosition(), nBranches = 0; lPosition; )
	{
		if ((pStep[0] = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep[0]->GetSubThreadID() - GetSubThreadID() > (UINT)nCount)
			{
				delete pStep[0];
				continue;
			}
			nBranches = max(pStep[0]->GetSubThreadID() - GetSubThreadID(), (UINT)nBranches);
		}
	}
	for (nBranch = nBranches, nBranches = nCount; nBranch < nBranches; nBranch++)
	{
		if ((pStep[0] = new CTCProcedureDocumentStartItem(m_pSubSteps, TRUE)))
		{
			if ((pStep[1] = new CTCProcedureDocumentEndItem(m_pSubSteps, TRUE)))
			{
				pStep[0]->SetSubThreadID(GetSubThreadID() + nBranch + 1);
				pStep[1]->SetSubThreadID(GetSubThreadID() + nBranch + 1);
				continue;
			}
			delete pStep[0];
		}
		break;
	}
	m_nBranchCount = nBranch;
	m_szExpressions.SetSize(nBranch + 1);
	RecalcLayout();
}

INT CTCProcedureDocumentSwitchItem::GetBranches() CONST
{
	return m_nBranchCount;
}

VOID CTCProcedureDocumentSwitchItem::SetInvariantCondition(LPCTSTR pszCondition)
{
	m_szExpressions.SetAtGrow(0, pszCondition);
}

CString CTCProcedureDocumentSwitchItem::GetInvariantCondition() CONST
{
	return((m_szExpressions.GetSize() > 0) ? m_szExpressions.GetAt(0) : EMPTYSTRING);
}

VOID CTCProcedureDocumentSwitchItem::SetBranchTestExpression(INT nBranch, LPCTSTR pszExpression)
{
	m_szExpressions.SetAtGrow(max(nBranch, 1), pszExpression);
}

CString CTCProcedureDocumentSwitchItem::GetBranchTestExpression(INT nBranch) CONST
{
	return((nBranch > 0 && nBranch < m_szExpressions.GetSize()) ? m_szExpressions.GetAt(nBranch) : EMPTYSTRING);
}

BOOL CTCProcedureDocumentSwitchItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSwitchItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSwitchItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentSwitchItem::RecalcLayout()
{
	INT  nIndex;
	CRect  rStep;
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	POSITION  lPosition;
	CUIntArray  nPoints;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), rContents = CalcLayoutPositions(rSymbol, nPoints, rLabel); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((nIndex = pStep->GetSubThreadID() - GetSubThreadID() - 1) < nPoints.GetSize() / 4)
			{
				if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
				{
					rStep.SetRect(nPoints.GetAt(4 * nIndex) - pStep->GetImageSize().cx / 2, nPoints.GetAt(4 * nIndex + 1) - pStep->GetImageSize().cy / 2, nPoints.GetAt(4 * nIndex) + pStep->GetImageSize().cx / 2, nPoints.GetAt(4 * nIndex + 1) + pStep->GetImageSize().cy / 2);
					pStep->SetPosition(rStep);
					continue;
				}
				if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
				{
					rStep.SetRect(nPoints.GetAt(4 * nIndex + 2) - pStep->GetImageSize().cx / 2, nPoints.GetAt(4 * nIndex + 3) - pStep->GetImageSize().cy / 2, nPoints.GetAt(4 * nIndex + 2) + pStep->GetImageSize().cx / 2, nPoints.GetAt(4 * nIndex + 3) + pStep->GetImageSize().cy / 2);
					pStep->SetPosition(rStep);
					continue;
				}
				for (rStep.SetRect(nPoints.GetAt(4 * nIndex) - m_sizeSymbol[0].cx / 2, pStep->GetPosition().top, nPoints.GetAt(4 * nIndex) + m_sizeSymbol[0].cx / 2, pStep->GetPosition().bottom), rStep.OffsetRect(pStep->GetPosition().left + pStep->GetImageSize().cx / 2 - pStep->CalcConnectionPoint().x, 0); pStep->GetPosition().left != rStep.left; )
				{
					pStep->Relocate(CPoint(rStep.left - pStep->GetPosition().left, 0));
					break;
				}
			}
		}
	}
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentSwitchItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSwitchItem::MapProperties(CByteArray &nData) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  cbData;
	CByteArray  nExpressionData;
	DATA  sData = { 0 };

	for (nIndex = 0, nCount = (INT)m_szExpressions.GetSize(), sData.cbExpressions = 0; nIndex < nCount; nIndex++)
	{
		nExpressionData.SetSize(sData.cbExpressions + (cbData = (m_szExpressions.GetAt(nIndex).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nExpressionData.GetData() + sData.cbExpressions, (LPCTSTR)m_szExpressions.GetAt(nIndex), cbData);
		sData.cbExpressions += cbData;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + sData.cbExpressions)), sData.nType = m_nType, sData.nBranchCount = m_nBranchCount; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), nExpressionData.GetData(), sData.cbExpressions);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentSwitchItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	CByteArray  nExpressionData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbExpressions && sData.cbExpressions >= 0 && sData.nType == m_nType; )
	{
		for (nExpressionData.SetSize(sData.cbExpressions), CopyMemory(nExpressionData.GetData(), nData.GetData() + (cbData = sizeof(DATA)), sData.cbExpressions), m_nBranchCount = sData.nBranchCount, m_szExpressions.RemoveAll(); nExpressionData.GetSize() > 0; nExpressionData.RemoveAt(0, (m_szExpressions.GetAt(m_szExpressions.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szExpressions.Add((LPCTSTR)nExpressionData.GetData());
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentSwitchItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptLine[12];
	CUIntArray  nPoints;

	if (m_bExpanded)
	{
		rContents = CalcLayoutPositions(rSymbol, nPoints, rLabel);
		ptLine[0] = CalcConnectionPoint(FALSE, FALSE);
		ptLine[1].x = rSymbol.CenterPoint().x;
		ptLine[1].y = rSymbol.top;
		ptLine[2].x = ptLine[1].x;
		ptLine[2].y = rSymbol.bottom;
		ptLine[3].x = ptLine[2].x;
		ptLine[3].y = (m_nBranchCount > 0) ? nPoints.GetAt(1) : rSymbol.bottom;
		ptLine[4].x = ptLine[3].x;
		ptLine[4].y = (m_nBranchCount > 1) ? (ptLine[3].y - TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 + 1) : ptLine[3].y;
		ptLine[5].x = (m_nBranchCount > 1) ? nPoints.GetAt(0) : rSymbol.CenterPoint().x;
		ptLine[5].y = ptLine[3].y;
		ptLine[6].x = (m_nBranchCount > 1) ? nPoints.GetAt(nPoints.GetSize() - 4) : rSymbol.CenterPoint().x;
		ptLine[6].y = ptLine[3].y;
		ptLine[7].x = ptLine[5].x;
		ptLine[7].y = (m_nBranchCount > 0) ? nPoints.GetAt(3) : rSymbol.bottom;
		ptLine[8].x = ptLine[6].x;
		ptLine[8].y = ptLine[7].y;
		ptLine[9].x = ptLine[3].x;
		ptLine[9].y = ptLine[7].y;
		ptLine[10].x = ptLine[9].x;
		ptLine[10].y = (m_nBranchCount > 1) ? (ptLine[9].y + TCPROCEDUREDOCUMENT_DEFAULT_CONNECTIONLINEWIDTH / 2 - 1) : ptLine[9].y;
		ptLine[11].x = ptLine[0].x;
		ptLine[11].y = rContents.bottom;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawConnectionLine(pDC, ptLine[3], ptLine[5]);
		DrawConnectionLine(pDC, ptLine[3], ptLine[6]);
		DrawConnectionLine(pDC, ptLine[9], ptLine[7]);
		DrawConnectionLine(pDC, ptLine[9], ptLine[8]);
		DrawConnectionLine(pDC, ptLine[2], ptLine[4]);
		DrawConnectionLine(pDC, ptLine[10], ptLine[11]);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[0].x + ptLine[1].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[0].y + ptLine[1].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL, (ptLine[10].x + ptLine[11].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cx / 2, (ptLine[10].y + ptLine[11].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cy / 2);
		DrawSymbol(pDC, m_cSymbol[2], rSymbol.left, rSymbol.top);
	}
}

VOID CTCProcedureDocumentSwitchItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	POSITION  lPosition;
	CUIntArray  nPoints;
	CTCProcedureDocumentItem  *pStep;

	for (CalcLayoutPositions(rSymbol, nPoints, rLabel); !m_nSubThreadID || m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	for (lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) && pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END  &&  !pStep->IsExpanded())
		{
			rLabel.SetRect(pStep->GetPosition().left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT, pStep->GetPosition().right, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT);
			DrawLabelSymbol(pDC, rLabel, pStep->GetLabel());
		}
	}
}

CRect CTCProcedureDocumentSwitchItem::CalcLayoutPositions(CRect &rSymbol, CUIntArray &nPoints, CRect &rLabel) CONST
{
	INT  x[2];
	INT  y[2];
	INT  nIndex;
	INT  nWidth;
	INT  nHeight;
	INT  nBranch;
	INT  nBranches;
	CRect  rContents;
	POSITION  lPosition;
	CUIntArray  nHeights;
	CUIntArray  sizeBranches[2];
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), nHeights.SetSize(m_nBranchCount), sizeBranches[0].SetSize(m_nBranchCount), sizeBranches[1].SetSize(m_nBranchCount); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if ((nIndex = pStep->GetSubThreadID() - GetSubThreadID() - 1) < m_nBranchCount)
			{
				if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
				{
					nHeights.SetAt(nIndex, nHeights.GetAt(nIndex) + pStep->GetImageSize().cy / 2);
					continue;
				}
				if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
				{
					nHeights.SetAt(nIndex, nHeights.GetAt(nIndex) + pStep->GetImageSize().cy / 2);
					continue;
				}
				sizeBranches[0].SetAt(nIndex, max(pStep->GetPosition().Width(), (INT)sizeBranches[0].GetAt(nIndex)));
				sizeBranches[1].SetAt(nIndex, max(pStep->GetPosition().bottom - (INT)nHeights.GetAt(nIndex), (INT)sizeBranches[1].GetAt(nIndex)));
			}
		}
	}
	for (nBranch = 0, nBranches = m_nBranchCount, nWidth = max(nBranches - 1, 0)*m_sizeSymbol[0].cx, nHeight = 0; nBranch < nBranches; nBranch++)
	{
		nWidth += (nBranch < nBranches / 2) ? max((INT)sizeBranches[0].GetAt(nBranch) - m_sizeSymbol[0].cx, 0) : 0;
		nHeight = max((INT)sizeBranches[1].GetAt(nBranch), nHeight);
	}
	for (nBranch = 0, rSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + nWidth - m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + nWidth + m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + m_sizeSymbol[2].cy), x[0] = x[1] = rSymbol.CenterPoint().x - nWidth, y[0] = (nBranches > 0) ? (rSymbol.bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL / 2) : rSymbol.bottom, y[1] = (nBranches > 0) ? (y[0] + nHeights.GetAt(nBranch) + max(nHeight - y[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL)) : y[0], nPoints.RemoveAll(); nBranch < nBranches; x[0] += (nBranch < nBranches - 1) ? (max(sizeBranches[0].GetAt(nBranch), (UINT)m_sizeSymbol[0].cx) + m_sizeSymbol[0].cx) : 0, x[1] = x[0], nBranch++)
	{
		nPoints.Add(x[0]);
		nPoints.Add(y[0]);
		nPoints.Add(x[1]);
		nPoints.Add(y[1]);
	}
	rContents.SetRect(rSymbol.CenterPoint().x - nWidth / 2 - (CalcConnectionPoint().x - m_rPosition.left - m_sizeSymbol[0].cx / 2), rSymbol.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, (nBranches > 0) ? max(x[1] + m_rPosition.left - CalcConnectionPoint().x + max(sizeBranches[0].GetAt(sizeBranches[0].GetUpperBound()), (UINT)m_sizeSymbol[0].cx), (UINT)rSymbol.right) : rSymbol.right, y[1] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentSwitchItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentSwitchItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSwitchItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentForLoopItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentForLoopItem, CTCProcedureDocumentItem)

CTCProcedureDocumentForLoopItem::CTCProcedureDocumentForLoopItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	CTCProcedureDocumentItem  *pStep[2];

	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_FORLOOP, m_nIterationCount = 0; LoadSymbol(IDP_TCFLOWCONTROLFORLOOPSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLFORLOOPSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
	if (!m_pSubSteps->GetStepCount(TRUE))
	{
		if ((pStep[0] = new CTCProcedureDocumentStartItem(m_pSubSteps, nSubThreadID + 1)))
		{
			if ((pStep[1] = new CTCProcedureDocumentEndItem(m_pSubSteps, nSubThreadID + 1))) return;
			delete pStep[0];
		}
	}
}

CTCProcedureDocumentForLoopItem::~CTCProcedureDocumentForLoopItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

VOID CTCProcedureDocumentForLoopItem::SetIterations(INT nCount)
{
	m_nIterationCount = nCount;
}

INT CTCProcedureDocumentForLoopItem::GetIterations() CONST
{
	return m_nIterationCount;
}

VOID CTCProcedureDocumentForLoopItem::SetInvariantCondition(LPCTSTR pszCondition)
{
	m_szExpression = pszCondition;
}

CString CTCProcedureDocumentForLoopItem::GetInvariantCondition() CONST
{
	return m_szExpression;
}

BOOL CTCProcedureDocumentForLoopItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentForLoopItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentForLoopItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentForLoopItem::RecalcLayout()
{
	CRect  rStep;
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptBranch[2];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), rContents = CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], rLabel); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				rStep.left = ptBranch[0].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[0].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				rStep.left = ptBranch[1].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[1].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			for (rStep.SetRect(ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left, pStep->GetPosition().top, ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left + pStep->GetPosition().Width(), pStep->GetPosition().bottom); pStep->GetPosition().left != rStep.left; )
			{
				pStep->Relocate(CPoint(rStep.left - pStep->GetPosition().left, 0));
				break;
			}
		}
	}
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentForLoopItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentForLoopItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbExpression = (m_szExpression.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType, sData.nInteractionCount = m_nIterationCount; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szExpression, sData.cbExpression);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentForLoopItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbExpression && sData.cbExpression > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szExpression.GetBufferSetLength(STRINGCHARS(sData.cbExpression)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbExpression));
		m_nIterationCount = sData.nInteractionCount;
		m_szExpression.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentForLoopItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptLine[10];
	CPoint  ptBranch[2];

	if (m_bExpanded)
	{
		rContents = CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], rLabel);
		ptLine[0] = CalcConnectionPoint(FALSE, FALSE);
		ptLine[1].x = rSymbol.CenterPoint().x;
		ptLine[1].y = rSymbol.top;
		ptLine[2].x = rSymbol.right;
		ptLine[2].y = rSymbol.CenterPoint().y;
		ptLine[3] = ptBranch[0];
		ptLine[4] = ptBranch[1];
		ptLine[5].x = ptLine[1].x;
		ptLine[5].y = ptLine[4].y;
		ptLine[6].x = ptLine[5].x;
		ptLine[6].y = rSymbol.bottom;
		ptLine[7].x = rSymbol.left;
		ptLine[7].y = ptLine[2].y;
		ptLine[8].x = ptLine[0].x;
		ptLine[8].y = ptLine[7].y;
		ptLine[9].x = ptLine[8].x;
		ptLine[9].y = rContents.bottom;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawConnectionLine(pDC, ptLine[2], ptLine[3]);
		DrawConnectionLine(pDC, ptLine[4], ptLine[5], ptLine[6]);
		DrawConnectionLine(pDC, ptLine[7], ptLine[8], ptLine[9]);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[0].x + ptLine[1].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[0].y + ptLine[1].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[2].x + ptLine[3].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[2].y + ptLine[3].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL, (ptLine[4].x + ptLine[5].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cx / 2, (ptLine[4].y + ptLine[5].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL, (ptLine[7].x + ptLine[8].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cx / 2, (ptLine[7].y + ptLine[8].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cy / 2);
		DrawSymbol(pDC, m_cSymbol[2], rSymbol.left, rSymbol.top);
	}
}

VOID CTCProcedureDocumentForLoopItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CPoint  ptBranch[2];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], rLabel); !m_nSubThreadID || m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	for (lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) && pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END  &&  !pStep->IsExpanded())
		{
			rLabel.SetRect(pStep->GetPosition().left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT, pStep->GetPosition().right, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT);
			DrawLabelSymbol(pDC, rLabel, pStep->GetLabel());
		}
	}
}

CRect CTCProcedureDocumentForLoopItem::CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CRect &rLabel) CONST
{
	INT  nHeight[2];
	CRect  rContents;
	CSize  sizeBranch;
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), sizeBranch.cx = sizeBranch.cy = 0, nHeight[0] = 0, nHeight[1] = 0; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				nHeight[0] = pStep->GetImageSize().cy / 2;
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				nHeight[1] = pStep->GetImageSize().cy / 2;
				continue;
			}
			sizeBranch.cx = max(pStep->GetPosition().Width(), sizeBranch.cx);
			sizeBranch.cy = max(pStep->GetPosition().bottom, sizeBranch.cy);
		}
	}
	rSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT - m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + m_sizeSymbol[2].cy);
	ptStartBranch.x = 2 * rSymbol.CenterPoint().x - CalcConnectionPoint().x;
	ptStartBranch.y = rSymbol.CenterPoint().y;
	ptEndBranch.x = ptStartBranch.x;
	ptEndBranch.y = (sizeBranch.cy > 0) ? (sizeBranch.cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]) : (ptStartBranch.y + nHeight[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]);
	rContents.SetRect(rSymbol.left, rSymbol.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, ptStartBranch.x + m_rPosition.left - CalcConnectionPoint().x + max(sizeBranch.cx, m_sizeSymbol[0].cx), ptEndBranch.y + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentForLoopItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentForLoopItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentForLoopItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWhileLoopItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentWhileLoopItem, CTCProcedureDocumentItem)

CTCProcedureDocumentWhileLoopItem::CTCProcedureDocumentWhileLoopItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	CTCProcedureDocumentItem  *pStep[2];

	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_WHILELOOP; LoadSymbol(IDP_TCFLOWCONTROLWHILELOOPSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLWHILELOOPSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
	if (!m_pSubSteps->GetStepCount(TRUE))
	{
		if ((pStep[0] = new CTCProcedureDocumentStartItem(m_pSubSteps, nSubThreadID + 1)))
		{
			if ((pStep[1] = new CTCProcedureDocumentEndItem(m_pSubSteps, nSubThreadID + 1))) return;
			delete pStep[0];
		}
	}
}

CTCProcedureDocumentWhileLoopItem::~CTCProcedureDocumentWhileLoopItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

VOID CTCProcedureDocumentWhileLoopItem::SetInvariantCondition(LPCTSTR pszCondition)
{
	m_szExpression[0] = pszCondition;
}

CString CTCProcedureDocumentWhileLoopItem::GetInvariantCondition() CONST
{
	return m_szExpression[0];
}

VOID CTCProcedureDocumentWhileLoopItem::SetTestExpression(LPCTSTR pszExpression)
{
	m_szExpression[1] = pszExpression;
}

CString CTCProcedureDocumentWhileLoopItem::GetTestExpression() CONST
{
	return m_szExpression[1];
}

BOOL CTCProcedureDocumentWhileLoopItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentWhileLoopItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentWhileLoopItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentWhileLoopItem::RecalcLayout()
{
	CRect  rStep;
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptBranch[2];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), rContents = CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], rLabel); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				rStep.left = ptBranch[0].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[0].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				rStep.left = ptBranch[1].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[1].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			for (rStep.SetRect(ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left, pStep->GetPosition().top, ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left + pStep->GetPosition().Width(), pStep->GetPosition().bottom); pStep->GetPosition().left != rStep.left; )
			{
				pStep->Relocate(CPoint(rStep.left - pStep->GetPosition().left, 0));
				break;
			}
		}
	}
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentWhileLoopItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentWhileLoopItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbExpression[0] = (m_szExpression[0].GetLength() + 1)*sizeof(TCHAR)) + (sData.cbExpression[1] = (m_szExpression[1].GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szExpression[0], sData.cbExpression[0]);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbExpression[0]), (LPCTSTR)m_szExpression[1], sData.cbExpression[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentWhileLoopItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbExpression[0] + sData.cbExpression[1] && sData.cbExpression[0] > 0 && sData.cbExpression[1] > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szExpression[0].GetBufferSetLength(STRINGCHARS(sData.cbExpression[0])), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbExpression[0]));
		CopyMemory(m_szExpression[1].GetBufferSetLength(STRINGCHARS(sData.cbExpression[1])), nData.GetData() + (cbData = cbData + sData.cbExpression[0]), STRINGBYTES(sData.cbExpression[1]));
		m_szExpression[0].ReleaseBuffer();
		m_szExpression[1].ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentWhileLoopItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptLine[10];
	CPoint  ptBranch[2];

	if (m_bExpanded)
	{
		rContents = CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], rLabel);
		ptLine[0] = CalcConnectionPoint(FALSE, FALSE);
		ptLine[1].x = rSymbol.CenterPoint().x;
		ptLine[1].y = rSymbol.top;
		ptLine[2].x = rSymbol.right;
		ptLine[2].y = rSymbol.CenterPoint().y;
		ptLine[3] = ptBranch[0];
		ptLine[4] = ptBranch[1];
		ptLine[5].x = ptLine[1].x;
		ptLine[5].y = ptLine[4].y;
		ptLine[6].x = ptLine[5].x;
		ptLine[6].y = rSymbol.bottom;
		ptLine[7].x = rSymbol.left;
		ptLine[7].y = ptLine[2].y;
		ptLine[8].x = ptLine[0].x;
		ptLine[8].y = ptLine[7].y;
		ptLine[9].x = ptLine[8].x;
		ptLine[9].y = rContents.bottom;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawConnectionLine(pDC, ptLine[2], ptLine[3]);
		DrawConnectionLine(pDC, ptLine[4], ptLine[5], ptLine[6]);
		DrawConnectionLine(pDC, ptLine[7], ptLine[8], ptLine[9]);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[0].x + ptLine[1].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[0].y + ptLine[1].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[2].x + ptLine[3].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[2].y + ptLine[3].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL, (ptLine[4].x + ptLine[5].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cx / 2, (ptLine[4].y + ptLine[5].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL, (ptLine[7].x + ptLine[8].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cx / 2, (ptLine[7].y + ptLine[8].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cy / 2);
		DrawSymbol(pDC, m_cSymbol[2], rSymbol.left, rSymbol.top);
	}
}

VOID CTCProcedureDocumentWhileLoopItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CPoint  ptBranch[2];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], rLabel); !m_nSubThreadID || m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	for (lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) && pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END  &&  !pStep->IsExpanded())
		{
			rLabel.SetRect(pStep->GetPosition().left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT, pStep->GetPosition().right, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT);
			DrawLabelSymbol(pDC, rLabel, pStep->GetLabel());
		}
	}
}

CRect CTCProcedureDocumentWhileLoopItem::CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CRect &rLabel) CONST
{
	INT  nHeight[2];
	CRect  rContents;
	CSize  sizeBranch;
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), sizeBranch.cx = sizeBranch.cy = 0, nHeight[0] = 0, nHeight[1] = 0; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				nHeight[0] = pStep->GetImageSize().cy / 2;
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				nHeight[1] = pStep->GetImageSize().cy / 2;
				continue;
			}
			sizeBranch.cx = max(pStep->GetPosition().Width(), sizeBranch.cx);
			sizeBranch.cy = max(pStep->GetPosition().bottom, sizeBranch.cy);
		}
	}
	rSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT - m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + m_sizeSymbol[2].cy);
	ptStartBranch.x = 2 * rSymbol.CenterPoint().x - CalcConnectionPoint().x;
	ptStartBranch.y = rSymbol.CenterPoint().y;
	ptEndBranch.x = ptStartBranch.x;
	ptEndBranch.y = (sizeBranch.cy > 0) ? (sizeBranch.cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]) : (ptStartBranch.y + nHeight[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]);
	rContents.SetRect(rSymbol.left, rSymbol.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, ptStartBranch.x + m_rPosition.left - CalcConnectionPoint().x + max(sizeBranch.cx, m_sizeSymbol[0].cx), ptEndBranch.y + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentWhileLoopItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentWhileLoopItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWhileLoopItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentDoLoopItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentDoLoopItem, CTCProcedureDocumentItem)

CTCProcedureDocumentDoLoopItem::CTCProcedureDocumentDoLoopItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	CTCProcedureDocumentItem  *pStep[2];

	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_DOLOOP; LoadSymbol(IDP_TCFLOWCONTROLDOLOOPSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLDOLOOPSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
	if (!m_pSubSteps->GetStepCount(TRUE))
	{
		if ((pStep[0] = new CTCProcedureDocumentStartItem(m_pSubSteps, nSubThreadID + 1)))
		{
			if ((pStep[1] = new CTCProcedureDocumentEndItem(m_pSubSteps, nSubThreadID + 1))) return;
			delete pStep[0];
		}
	}
}

CTCProcedureDocumentDoLoopItem::~CTCProcedureDocumentDoLoopItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

VOID CTCProcedureDocumentDoLoopItem::SetInvariantCondition(LPCTSTR pszCondition)
{
	m_szExpression[0] = pszCondition;
}

CString CTCProcedureDocumentDoLoopItem::GetInvariantCondition() CONST
{
	return m_szExpression[0];
}

VOID CTCProcedureDocumentDoLoopItem::SetTestExpression(LPCTSTR pszExpression)
{
	m_szExpression[1] = pszExpression;
}

CString CTCProcedureDocumentDoLoopItem::GetTestExpression() CONST
{
	return m_szExpression[1];
}

BOOL CTCProcedureDocumentDoLoopItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentDoLoopItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentDoLoopItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentDoLoopItem::RecalcLayout()
{
	CRect  rStep;
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptBranch[4];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), rContents = CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], ptBranch[2], ptBranch[3], rLabel); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				rStep.left = ptBranch[0].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[0].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				rStep.left = ptBranch[1].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[1].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			for (rStep.SetRect(ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left, pStep->GetPosition().top, ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left + pStep->GetPosition().Width(), pStep->GetPosition().bottom); pStep->GetPosition().left != rStep.left; )
			{
				pStep->Relocate(CPoint(rStep.left - pStep->GetPosition().left, 0));
				break;
			}
		}
	}
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentDoLoopItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentDoLoopItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbExpression[0] = (m_szExpression[0].GetLength() + 1)*sizeof(TCHAR)) + (sData.cbExpression[1] = (m_szExpression[1].GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szExpression[0], sData.cbExpression[0]);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbExpression[0]), (LPCTSTR)m_szExpression[1], sData.cbExpression[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentDoLoopItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbExpression[0] + sData.cbExpression[1] && sData.cbExpression[0] > 0 && sData.cbExpression[1] > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szExpression[0].GetBufferSetLength(STRINGCHARS(sData.cbExpression[0])), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbExpression[0]));
		CopyMemory(m_szExpression[1].GetBufferSetLength(STRINGCHARS(sData.cbExpression[1])), nData.GetData() + (cbData = cbData + sData.cbExpression[0]), STRINGBYTES(sData.cbExpression[1]));
		m_szExpression[0].ReleaseBuffer();
		m_szExpression[1].ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentDoLoopItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;
	CPoint  ptLine[10];
	CPoint  ptBranch[4];

	if (m_bExpanded)
	{
		rContents = CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], ptBranch[2], ptBranch[3], rLabel);
		ptLine[0] = CalcConnectionPoint(FALSE, FALSE);
		ptLine[1] = ptBranch[0];
		ptLine[2] = ptBranch[1];
		ptLine[3].x = ptLine[2].x;
		ptLine[3].y = rSymbol.top;
		ptLine[4].x = rSymbol.right;
		ptLine[4].y = rSymbol.CenterPoint().y;
		ptLine[5] = ptBranch[2];
		ptLine[6] = ptBranch[3];
		ptLine[7].x = rSymbol.left;
		ptLine[7].y = ptLine[4].y;
		ptLine[8].x = ptLine[0].x;
		ptLine[8].y = ptLine[7].y;
		ptLine[9].x = ptLine[8].x;
		ptLine[9].y = rContents.bottom;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawConnectionLine(pDC, ptLine[2], ptLine[3]);
		DrawConnectionLine(pDC, ptLine[4], ptLine[5], ptLine[6]);
		DrawConnectionLine(pDC, ptLine[5], ptLine[6], ptLine[1]);
		DrawConnectionLine(pDC, ptLine[7], ptLine[8], ptLine[9]);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[0].x + ptLine[1].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[0].y + ptLine[1].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONUPSYMBOL, (ptLine[5].x + ptLine[6].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONUPSYMBOL).cx / 2, (ptLine[5].y + ptLine[6].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONUPSYMBOL).cy / 2);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL, (ptLine[7].x + ptLine[8].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cx / 2, (ptLine[7].y + ptLine[8].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONLEFTSYMBOL).cy / 2);
		DrawSymbol(pDC, m_cSymbol[2], rSymbol.left, rSymbol.top);
	}
}

VOID CTCProcedureDocumentDoLoopItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CPoint  ptBranch[4];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (CalcLayoutPositions(rSymbol, ptBranch[0], ptBranch[1], ptBranch[2], ptBranch[3], rLabel); !m_nSubThreadID || m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	for (lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) && pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END  &&  !pStep->IsExpanded())
		{
			rLabel.SetRect(pStep->GetPosition().left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT, pStep->GetPosition().right, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT);
			DrawLabelSymbol(pDC, rLabel, pStep->GetLabel());
		}
	}
}

CRect CTCProcedureDocumentDoLoopItem::CalcLayoutPositions(CRect &rSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CPoint &ptStartLoopBranch, CPoint &ptEndLoopBranch, CRect &rLabel) CONST
{
	INT  nHeight[2];
	CRect  rContents;
	CSize  sizeBranch;
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), sizeBranch.cx = sizeBranch.cy = 0, nHeight[0] = 0, nHeight[1] = 0; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				nHeight[0] = pStep->GetImageSize().cy;
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				nHeight[1] = pStep->GetImageSize().cy;
				continue;
			}
			sizeBranch.cx = max(pStep->GetPosition().Width(), sizeBranch.cx);
			sizeBranch.cy = max(pStep->GetPosition().bottom, sizeBranch.cy);
		}
	}
	rSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT - m_sizeSymbol[2].cx / 2, (sizeBranch.cy > 0) ? (sizeBranch.cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]) : (m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]), m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + m_sizeSymbol[2].cx / 2, (sizeBranch.cy > 0) ? (sizeBranch.cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1] + m_sizeSymbol[2].cy) : (m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1] + m_sizeSymbol[2].cy));
	ptStartBranch.x = rSymbol.CenterPoint().x;
	ptStartBranch.y = m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[0] / 2;
	ptEndBranch.x = ptStartBranch.x;
	ptEndBranch.y = rSymbol.top - nHeight[1] / 2;
	ptStartLoopBranch.x = 2 * rSymbol.CenterPoint().x - CalcConnectionPoint().x + max(sizeBranch.cx - m_sizeSymbol[0].cx, 0);
	ptStartLoopBranch.y = rSymbol.CenterPoint().y;
	ptEndLoopBranch.x = ptStartLoopBranch.x;
	ptEndLoopBranch.y = ptStartBranch.y;
	rContents.SetRect(rSymbol.left, ptStartBranch.y - TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, ptStartLoopBranch.x + CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONUPSYMBOL).cx / 2, rSymbol.bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentDoLoopItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentDoLoopItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentDoLoopItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentBlockItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentBlockItem, CTCProcedureDocumentItem)

CTCProcedureDocumentBlockItem::CTCProcedureDocumentBlockItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	CTCProcedureDocumentItem  *pStep[2];

	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_BLOCK; LoadSymbol(IDP_TCFLOWCONTROLBLOCKSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLBLOCKSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
	if (!m_pSubSteps->GetStepCount(TRUE))
	{
		if ((pStep[0] = new CTCProcedureDocumentStartItem(m_pSubSteps, nSubThreadID + 1)))
		{
			if ((pStep[1] = new CTCProcedureDocumentEndItem(m_pSubSteps, nSubThreadID + 1))) return;
			delete pStep[0];
		}
	}
}

CTCProcedureDocumentBlockItem::~CTCProcedureDocumentBlockItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

BOOL CTCProcedureDocumentBlockItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentBlockItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentBlockItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentBlockItem::RecalcLayout()
{
	CRect  rStep;
	CRect  rLabel;
	CRect  rContents;
	CRect  rSymbol[2];
	CPoint  ptBranch[2];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), rContents = CalcLayoutPositions(rSymbol[0], rSymbol[1], ptBranch[0], ptBranch[1], rLabel); lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				rStep.left = ptBranch[0].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[0].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				rStep.left = ptBranch[1].x - pStep->GetImageSize().cx / 2;
				rStep.top = ptBranch[1].y - pStep->GetImageSize().cy / 2;
				rStep.right = rStep.left + pStep->GetImageSize().cx;
				rStep.bottom = rStep.top + pStep->GetImageSize().cy;
				pStep->SetPosition(rStep);
				continue;
			}
			for (rStep.SetRect(ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left, pStep->GetPosition().top, ptBranch[0].x - pStep->CalcConnectionPoint().x + pStep->GetPosition().left + pStep->GetPosition().Width(), pStep->GetPosition().bottom); pStep->GetPosition().left != rStep.left; )
			{
				pStep->Relocate(CPoint(rStep.left - pStep->GetPosition().left, 0));
				break;
			}
		}
	}
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentBlockItem::MapProperties(CByteArray &nData) CONST
{
	return CTCProcedureDocumentItem::MapProperties(nData);
}

BOOL CTCProcedureDocumentBlockItem::UnmapProperties(CONST CByteArray &nData)
{
	return CTCProcedureDocumentItem::UnmapProperties(nData);
}

VOID CTCProcedureDocumentBlockItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rClip[2];
	CRect  rContents;
	CRect  rSymbol[2];
	CPoint  ptLine[4];
	CPoint  ptBranch[2];

	if (m_bExpanded)
	{
		rContents = CalcLayoutPositions(rSymbol[0], rSymbol[1], ptBranch[0], ptBranch[1], rLabel);
		ptLine[0] = CalcConnectionPoint(FALSE, FALSE);
		ptLine[1].x = rSymbol[0].CenterPoint().x;
		ptLine[1].y = rSymbol[0].top;
		ptLine[2].x = rSymbol[1].CenterPoint().x;
		ptLine[2].y = rSymbol[1].bottom;
		ptLine[3].x = ptLine[0].x;
		ptLine[3].y = rContents.bottom;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawConnectionLine(pDC, ptLine[2], ptLine[3]);
		DrawSymbol(pDC, m_cSymbol[2], rSymbol[0].left, rSymbol[0].top, (rClip[0] = CRect(0, 0, 1, 2)));
		DrawSymbol(pDC, m_cSymbol[2], rSymbol[1].left, rSymbol[1].top, (rClip[1] = CRect(0, 2, 1, 1)));
	}
}

VOID CTCProcedureDocumentBlockItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol[2];
	CPoint  ptBranch[2];
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (CalcLayoutPositions(rSymbol[0], rSymbol[1], ptBranch[0], ptBranch[1], rLabel); !m_nSubThreadID || m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	for (lPosition = (m_bExpanded) ? m_pSubSteps->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) && pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_START  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_FLOWCONTROL_END  &&  !pStep->IsExpanded())
		{
			rLabel.SetRect(pStep->GetPosition().left - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREEINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPTREESYMBOLSIZE, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT, pStep->GetPosition().right, pStep->GetPosition().top - TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT);
			DrawLabelSymbol(pDC, rLabel, pStep->GetLabel());
		}
	}
}

CRect CTCProcedureDocumentBlockItem::CalcLayoutPositions(CRect &rStartSymbol, CRect &rEndSymbol, CPoint &ptStartBranch, CPoint &ptEndBranch, CRect &rLabel) CONST
{
	INT  nHeight[2];
	CRect  rContents;
	CSize  sizeBranch;
	POSITION  lPosition;
	CTCProcedureDocumentItem  *pStep;

	for (lPosition = m_pSubSteps->GetStartPosition(), sizeBranch.cx = sizeBranch.cy = 0, nHeight[0] = 0, nHeight[1] = 0; lPosition; )
	{
		if ((pStep = m_pSubSteps->GetNextStep(lPosition)) != (CTCProcedureDocumentItem *)NULL)
		{
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_START)
			{
				nHeight[0] = pStep->GetImageSize().cy;
				continue;
			}
			if (pStep->GetType() == TCPROCEDURETHREADSTEP_FLOWCONTROL_END)
			{
				nHeight[1] = pStep->GetImageSize().cy;
				continue;
			}
			sizeBranch.cx = max(pStep->GetPosition().Width(), sizeBranch.cx);
			sizeBranch.cy = max(pStep->GetPosition().bottom, sizeBranch.cy);
		}
	}
	rStartSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT - m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + m_sizeSymbol[2].cy / 2);
	rEndSymbol.SetRect(rStartSymbol.left, (sizeBranch.cy > 0) ? (sizeBranch.cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]) : (rStartSymbol.bottom + nHeight[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1]), rStartSymbol.right, (sizeBranch.cy > 0) ? (sizeBranch.cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1] + m_sizeSymbol[2].cy / 2) : (rStartSymbol.bottom + nHeight[0] + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + nHeight[1] + m_sizeSymbol[2].cy / 2));
	ptStartBranch.x = rStartSymbol.CenterPoint().x;
	ptStartBranch.y = rStartSymbol.bottom + nHeight[0] / 2;
	ptEndBranch.x = ptStartBranch.x;
	ptEndBranch.y = rEndSymbol.top - nHeight[1] / 2;
	rContents.SetRect(min(ptStartBranch.x + m_rPosition.left - CalcConnectionPoint().x, rStartSymbol.left), rStartSymbol.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, ptStartBranch.x + max(m_rPosition.left - CalcConnectionPoint().x + sizeBranch.cx, m_sizeSymbol[2].cx / 2), rEndSymbol.bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentBlockItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentBlockItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentBlockItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentGotoItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentGotoItem, CTCProcedureDocumentItem)

CTCProcedureDocumentGotoItem::CTCProcedureDocumentGotoItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO; LoadSymbol(IDP_TCFLOWCONTROLGOTOSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLGOTOSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
}

CTCProcedureDocumentGotoItem::~CTCProcedureDocumentGotoItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

VOID CTCProcedureDocumentGotoItem::SetJumpLabel(LPCTSTR pszLabel)
{
	m_szJumpLabel = pszLabel;
}

CString CTCProcedureDocumentGotoItem::GetJumpLabel() CONST
{
	return m_szJumpLabel;
}

BOOL CTCProcedureDocumentGotoItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentGotoItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentGotoItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentGotoItem::RecalcLayout()
{
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;

	rContents = CalcLayoutPositions(rSymbol, rLabel);
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentGotoItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentGotoItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbJumpLabel = (m_szJumpLabel.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szJumpLabel, sData.cbJumpLabel);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentGotoItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbJumpLabel && sData.cbJumpLabel > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szJumpLabel.GetBufferSetLength(STRINGCHARS(sData.cbJumpLabel)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbJumpLabel));
		m_szJumpLabel.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentGotoItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CPoint  ptLine[2];

	if (m_bExpanded)
	{
		CalcLayoutPositions(rSymbol, rLabel);
		ptLine[0] = CalcConnectionPoint(FALSE, FALSE);
		ptLine[1].x = rSymbol.CenterPoint().x;
		ptLine[1].y = rSymbol.top;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawSymbol(pDC, IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL, (ptLine[0].x + ptLine[1].x) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cx / 2, (ptLine[0].y + ptLine[1].y) / 2 - CalcSymbolSize(IDP_TCFLOWCONTROLDIRECTIONRIGHTSYMBOL).cy / 2);
		DrawSymbol(pDC, m_cSymbol[2], rSymbol.left, rSymbol.top);
	}
}

VOID CTCProcedureDocumentGotoItem::DrawLabels(CDC *pDC)
{
	INT  nBkMode;
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rJumpLabel;
	LOGFONT  lfFont;
	CFont  *pOldFont;
	CFont  cFont;

	for (CalcLayoutPositions(rSymbol, rLabel); !m_nSubThreadID || m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	if (m_bExpanded)
	{
		if (!m_szJumpLabel.IsEmpty() && m_cLabelFont.GetLogFont(&lfFont))
		{
			for (rJumpLabel.SetRect(rSymbol.left + rSymbol.Width() / 16, rSymbol.bottom - (5 * rSymbol.Height()) / 8, rSymbol.right - rSymbol.Width() / 6, rSymbol.bottom - rSymbol.Height() / 8), lfFont.lfHeight = rSymbol.Height() / 3, lfFont.lfWeight = FW_NORMAL, lfFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE, _tcscpy_s(lfFont.lfFaceName, sizeof(lfFont.lfFaceName) / sizeof(TCHAR), EMPTYSTRING); cFont.CreateFontIndirect(&lfFont); )
			{
				if ((pOldFont = pDC->SelectObject(&cFont)))
				{
					nBkMode = pDC->SetBkMode(TRANSPARENT);
					pDC->DrawText(m_szJumpLabel, rJumpLabel, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_WORD_ELLIPSIS);
					pDC->SelectObject(pOldFont);
					pDC->SetBkMode(nBkMode);
				}
				cFont.DeleteObject();
				break;
			}
		}
	}
}

CRect CTCProcedureDocumentGotoItem::CalcLayoutPositions(CRect &rSymbol, CRect &rLabel) CONST
{
	CRect  rContents;

	rSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT - m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + m_sizeSymbol[2].cx / 2, m_rPosition.top + m_sizeSymbol[0].cy + TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL + m_sizeSymbol[2].cy);
	rContents.SetRect(rSymbol.left, rSymbol.top - TCPROCEDUREDOCUMENT_DEFAULT_STEPINTERVAL, rSymbol.right, rSymbol.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentGotoItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentGotoItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentGotoItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentLabelItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentLabelItem, CTCProcedureDocumentItem)

CTCProcedureDocumentLabelItem::CTCProcedureDocumentLabelItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_LABEL; LoadSymbol(IDP_TCFLOWCONTROLLABELSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]) && LoadSymbol(IDP_TCFLOWCONTROLLABELSUBSYMBOL, m_cSymbol[2]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		m_sizeSymbol[2].cx = m_cSymbol[2].GetWidth();
		m_sizeSymbol[2].cy = m_cSymbol[2].GetHeight();
		break;
	}
}

CTCProcedureDocumentLabelItem::~CTCProcedureDocumentLabelItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
	m_cSymbol[2].Destroy();
}

VOID CTCProcedureDocumentLabelItem::SetJumpLabel(LPCTSTR pszLabel)
{
	m_szJumpLabel = pszLabel;
}

CString CTCProcedureDocumentLabelItem::GetJumpLabel() CONST
{
	return m_szJumpLabel;
}

BOOL CTCProcedureDocumentLabelItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentLabelItem::CanExpand() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentLabelItem::Expand(BOOL bExpand)
{
	if (m_bExpanded != bExpand)
	{
		m_bExpanded = bExpand;
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentLabelItem::RecalcLayout()
{
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rContents;

	rContents = CalcLayoutPositions(rSymbol, rLabel);
	m_rPosition.SetRect(m_rPosition.left, m_rPosition.top, (m_bExpanded) ? rContents.right : (m_rPosition.left + m_sizeSymbol[0].cx), (m_bExpanded) ? rContents.bottom : (m_rPosition.top + m_sizeSymbol[0].cy));
}

BOOL CTCProcedureDocumentLabelItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentLabelItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbJumpLabel = (m_szJumpLabel.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szJumpLabel, sData.cbJumpLabel);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentLabelItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbJumpLabel && sData.cbJumpLabel > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szJumpLabel.GetBufferSetLength(STRINGCHARS(sData.cbJumpLabel)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbJumpLabel));
		m_szJumpLabel.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentLabelItem::DrawContents(CDC *pDC)
{
	CRect  rLabel;
	CRect  rSymbol;
	CPoint  ptLine[2];

	if (m_bExpanded)
	{
		CalcLayoutPositions(rSymbol, rLabel);
		ptLine[0].x = m_rPosition.left + m_sizeSymbol[0].cx;
		ptLine[0].y = m_rPosition.top + m_sizeSymbol[0].cy / 2;
		ptLine[1].x = rSymbol.left;
		ptLine[1].y = ptLine[0].y;
		DrawConnectionLine(pDC, ptLine[0], ptLine[1]);
		DrawSymbol(pDC, m_cSymbol[2], rSymbol.left, rSymbol.top);
	}
}

VOID CTCProcedureDocumentLabelItem::DrawLabels(CDC *pDC)
{
	INT  nBkMode;
	CRect  rLabel;
	CRect  rSymbol;
	CRect  rJumpLabel;
	LOGFONT  lfFont;
	CFont  *pOldFont;
	CFont  cFont;

	for (CalcLayoutPositions(rSymbol, rLabel); !m_nSubThreadID && !m_bExpanded; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
	if (m_bExpanded)
	{
		if (!m_szJumpLabel.IsEmpty() && m_cLabelFont.GetLogFont(&lfFont))
		{
			for (rJumpLabel.SetRect(rSymbol.left + rSymbol.Width() / 6, rSymbol.bottom - (5 * rSymbol.Height()) / 6, rSymbol.right - rSymbol.Width() / 16, rSymbol.bottom - rSymbol.Height() / 6), lfFont.lfHeight = (4 * rSymbol.Height()) / 9, lfFont.lfWeight = FW_NORMAL, lfFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE, _tcscpy_s(lfFont.lfFaceName, sizeof(lfFont.lfFaceName) / sizeof(TCHAR), EMPTYSTRING); cFont.CreateFontIndirect(&lfFont); )
			{
				if ((pOldFont = pDC->SelectObject(&cFont)))
				{
					nBkMode = pDC->SetBkMode(TRANSPARENT);
					pDC->DrawText(m_szJumpLabel, rJumpLabel, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_WORD_ELLIPSIS);
					pDC->SelectObject(pOldFont);
					pDC->SetBkMode(nBkMode);
				}
				cFont.DeleteObject();
				break;
			}
		}
	}
}

CRect CTCProcedureDocumentLabelItem::CalcLayoutPositions(CRect &rSymbol, CRect &rLabel) CONST
{
	CRect  rContents;

	rSymbol.SetRect(m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT - m_sizeSymbol[2].cx / 2, max(m_rPosition.CenterPoint().y - m_sizeSymbol[2].cy / 2, m_rPosition.top), m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT + m_sizeSymbol[2].cx / 2, max(m_rPosition.CenterPoint().y - m_sizeSymbol[2].cy / 2, m_rPosition.top) + m_sizeSymbol[2].cy);
	rContents.SetRect(rSymbol.left, rSymbol.top, rSymbol.right, max(rSymbol.bottom, m_rPosition.bottom));
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentLabelItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentLabelItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentLabelItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentEndItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentEndItem, CTCProcedureDocumentItem)

CTCProcedureDocumentEndItem::CTCProcedureDocumentEndItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_FLOWCONTROL_END, m_szLabel = (!nSubThreadID) ? STRING(IDS_TELECOMMANDPROCEDURESTEP_FLOWCONTROL_END) : EMPTYSTRING; LoadSymbol((!nSubThreadID) ? IDP_TCFLOWCONTROLENDSYMBOL : IDP_TCFLOWCONTROLENDSUBSYMBOL, m_cSymbol[0]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		break;
	}
}

CTCProcedureDocumentEndItem::~CTCProcedureDocumentEndItem()
{
	m_cSymbol[0].Destroy();
}

CPoint CTCProcedureDocumentEndItem::CalcConnectionPoint(BOOL bIn, BOOL bExpanded) CONST
{
	CPoint  pt;

	for (pt.x = pt.y = 0; bIn; )
	{
		pt.x = m_rPosition.left + m_sizeSymbol[0].cx / 2;
		pt.y = m_rPosition.top;
		return pt;
	}
	if (!bIn)
	{
		pt.x = 0;
		pt.y = 0;
		return pt;
	}
	return pt;
}

VOID CTCProcedureDocumentEndItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;
	LOGFONT  lfLabel;
	CFontTools  cFontTools;

	rLabel.SetRect(0, m_rPosition.bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT, 2 * m_rPosition.CenterPoint().x, (m_cLabelFont.GetLogFont(&lfLabel) > 0) ? (m_rPosition.bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + cFontTools.QueryHeight(&lfLabel)) : (m_rPosition.bottom + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELVERTINDENT + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHEIGHT));
	DrawLabelSymbol(pDC, rLabel, DT_SINGLELINE | DT_CENTER | DT_TOP | DT_END_ELLIPSIS | DT_NOPREFIX, m_szLabel);
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentEndItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentEndItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentEndItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetArgumentsItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentSetArgumentsItem, CTCProcedureDocumentItem)

CTCProcedureDocumentSetArgumentsItem::CTCProcedureDocumentSetArgumentsItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETARGUMENTS; LoadSymbol(IDP_TCACTIONOBJECTSETARGUMENTSSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentSetArgumentsItem::~CTCProcedureDocumentSetArgumentsItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentSetArgumentsItem::SetArguments(CONST CStringArray &szArguments)
{
	m_szArguments.Copy(szArguments);
}

INT CTCProcedureDocumentSetArgumentsItem::GetArguments(CStringArray &szArguments) CONST
{
	szArguments.Copy(m_szArguments);
	return((INT)szArguments.GetSize());
}

VOID CTCProcedureDocumentSetArgumentsItem::SetExpressions(CONST CStringArray &szExpressions)
{
	m_szExpressions.Copy(szExpressions);
}

INT CTCProcedureDocumentSetArgumentsItem::GetExpressions(CStringArray &szExpressions) CONST
{
	szExpressions.Copy(m_szExpressions);
	return((INT)szExpressions.GetSize());
}

BOOL CTCProcedureDocumentSetArgumentsItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetArgumentsItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetArgumentsItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	INT  nArgument;
	INT  nArguments;
	INT  nExpression;
	INT  nExpressions;
	CByteArray  nArgumentsData;
	CByteArray  nExpressionsData;
	DATA  sData = { 0 };

	for (nArgument = 0, nArguments = (INT)m_szArguments.GetSize(), sData.cbArguments = 0; nArgument < nArguments; nArgument++)
	{
		nArgumentsData.SetSize(sData.cbArguments + (cbData = (m_szArguments.GetAt(nArgument).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nArgumentsData.GetData() + sData.cbArguments, (LPCTSTR)m_szArguments.GetAt(nArgument), cbData);
		sData.cbArguments += cbData;
	}
	for (nExpression = 0, nExpressions = nArguments, sData.cbExpressions = 0; nExpression < nExpressions; nExpression++)
	{
		nExpressionsData.SetSize(sData.cbExpressions + (cbData = (nExpression < m_szExpressions.GetSize()) ? ((m_szExpressions.GetAt(nExpression).GetLength() + 1)*sizeof(TCHAR)) : sizeof(TCHAR)));
		CopyMemory(nExpressionsData.GetData() + sData.cbExpressions, (nExpression < m_szExpressions.GetSize()) ? (LPCTSTR)m_szExpressions.GetAt(nExpression) : EMPTYSTRING, cbData);
		sData.cbExpressions += cbData;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + sData.cbArguments + sData.cbExpressions)), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), nArgumentsData.GetData(), sData.cbArguments);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbArguments), nExpressionsData.GetData(), sData.cbExpressions);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentSetArgumentsItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbArgument;
	INT  cbArguments;
	INT  cbExpression;
	INT  cbExpressions;
	CByteArray  nArgumentsData;
	CByteArray  nExpressionsData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbArguments + sData.cbExpressions && sData.cbArguments >= 0 && sData.cbExpressions >= 0 && sData.nType == m_nType; )
	{
		for (nArgumentsData.SetSize(sData.cbArguments), nExpressionsData.SetSize(sData.cbExpressions), CopyMemory(nArgumentsData.GetData(), nData.GetData() + (cbData = sizeof(DATA)), sData.cbArguments), CopyMemory(nExpressionsData.GetData(), nData.GetData() + (cbData = cbData + sData.cbArguments), sData.cbExpressions), m_szArguments.RemoveAll(), m_szExpressions.RemoveAll(), cbArgument = cbArguments = 0; cbArguments < nArgumentsData.GetSize(); cbArguments += (cbArgument = (m_szArguments.GetAt(m_szArguments.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szArguments.Add((LPCTSTR)(nArgumentsData.GetData() + cbArguments));
			continue;
		}
		for (cbExpression = cbExpressions = 0; cbExpressions < nExpressionsData.GetSize(); cbExpressions += (cbExpression = (m_szExpressions.GetAt(m_szExpressions.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szExpressions.Add((LPCTSTR)(nExpressionsData.GetData() + cbExpressions));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentSetArgumentsItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentSetArgumentsItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentSetArgumentsItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentSetArgumentsItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetArgumentsItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetVariablesItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentSetVariablesItem, CTCProcedureDocumentItem)

CTCProcedureDocumentSetVariablesItem::CTCProcedureDocumentSetVariablesItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETVARIABLES; LoadSymbol(IDP_TCACTIONOBJECTSETVARIABLESSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentSetVariablesItem::~CTCProcedureDocumentSetVariablesItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentSetVariablesItem::SetVariables(CONST CStringArray &szVariables)
{
	m_szVariables.Copy(szVariables);
}

INT CTCProcedureDocumentSetVariablesItem::GetVariables(CStringArray &szVariables) CONST
{
	szVariables.Copy(m_szVariables);
	return((INT)szVariables.GetSize());
}

VOID CTCProcedureDocumentSetVariablesItem::SetExpressions(CONST CStringArray &szExpressions)
{
	m_szExpressions.Copy(szExpressions);
}

INT CTCProcedureDocumentSetVariablesItem::GetExpressions(CStringArray &szExpressions) CONST
{
	szExpressions.Copy(m_szExpressions);
	return((INT)szExpressions.GetSize());
}

BOOL CTCProcedureDocumentSetVariablesItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetVariablesItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetVariablesItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	INT  nVariable;
	INT  nVariables;
	INT  nExpression;
	INT  nExpressions;
	CByteArray  nVariablesData;
	CByteArray  nExpressionsData;
	DATA  sData = { 0 };

	for (nVariable = 0, nVariables = (INT)m_szVariables.GetSize(), sData.cbVariables = 0; nVariable < nVariables; nVariable++)
	{
		nVariablesData.SetSize(sData.cbVariables + (cbData = (m_szVariables.GetAt(nVariable).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nVariablesData.GetData() + sData.cbVariables, (LPCTSTR)m_szVariables.GetAt(nVariable), cbData);
		sData.cbVariables += cbData;
	}
	for (nExpression = 0, nExpressions = nVariables, sData.cbExpressions = 0; nExpression < nExpressions; nExpression++)
	{
		nExpressionsData.SetSize(sData.cbExpressions + (cbData = (nExpression < m_szExpressions.GetSize()) ? ((m_szExpressions.GetAt(nExpression).GetLength() + 1)*sizeof(TCHAR)) : sizeof(TCHAR)));
		CopyMemory(nExpressionsData.GetData() + sData.cbExpressions, (nExpression < m_szExpressions.GetSize()) ? (LPCTSTR)m_szExpressions.GetAt(nExpression) : EMPTYSTRING, cbData);
		sData.cbExpressions += cbData;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + sData.cbVariables + sData.cbExpressions)), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), nVariablesData.GetData(), sData.cbVariables);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbVariables), nExpressionsData.GetData(), sData.cbExpressions);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentSetVariablesItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbVariable;
	INT  cbVariables;
	INT  cbExpression;
	INT  cbExpressions;
	CByteArray  nVariablesData;
	CByteArray  nExpressionsData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbVariables + sData.cbExpressions && sData.cbVariables >= 0 && sData.cbExpressions >= 0 && sData.nType == m_nType; )
	{
		for (nVariablesData.SetSize(sData.cbVariables), nExpressionsData.SetSize(sData.cbExpressions), CopyMemory(nVariablesData.GetData(), nData.GetData() + (cbData = sizeof(DATA)), sData.cbVariables), CopyMemory(nExpressionsData.GetData(), nData.GetData() + (cbData = cbData + sData.cbVariables), sData.cbExpressions), m_szVariables.RemoveAll(), m_szExpressions.RemoveAll(), cbVariable = cbVariables = 0; cbVariables < nVariablesData.GetSize(); cbVariables += (cbVariable = (m_szVariables.GetAt(m_szVariables.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szVariables.Add((LPCTSTR)(nVariablesData.GetData() + cbVariables));
			continue;
		}
		for (cbExpression = cbExpressions = 0; cbExpressions < nExpressionsData.GetSize(); cbExpressions += (cbExpression = (m_szExpressions.GetAt(m_szExpressions.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szExpressions.Add((LPCTSTR)(nExpressionsData.GetData() + cbExpressions));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentSetVariablesItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentSetVariablesItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentSetVariablesItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentSetVariablesItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetVariablesItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetParametersItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentSetParametersItem, CTCProcedureDocumentItem)

CTCProcedureDocumentSetParametersItem::CTCProcedureDocumentSetParametersItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETPARAMETERS; LoadSymbol(IDP_TCACTIONOBJECTSETPARAMETERSSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentSetParametersItem::~CTCProcedureDocumentSetParametersItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentSetParametersItem::SetParameters(CONST CStringArray &szParameters)
{
	m_szParameters.Copy(szParameters);
}

INT CTCProcedureDocumentSetParametersItem::GetParameters(CStringArray &szParameters) CONST
{
	szParameters.Copy(m_szParameters);
	return((INT)szParameters.GetSize());
}

VOID CTCProcedureDocumentSetParametersItem::SetExpressions(CONST CStringArray &szExpressions)
{
	m_szExpressions.Copy(szExpressions);
}

INT CTCProcedureDocumentSetParametersItem::GetExpressions(CStringArray &szExpressions) CONST
{
	szExpressions.Copy(m_szExpressions);
	return((INT)szExpressions.GetSize());
}

BOOL CTCProcedureDocumentSetParametersItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetParametersItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetParametersItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	INT  nParameter;
	INT  nParameters;
	INT  nExpression;
	INT  nExpressions;
	CByteArray  nParametersData;
	CByteArray  nExpressionsData;
	DATA  sData = { 0 };

	for (nParameter = 0, nParameters = (INT)m_szParameters.GetSize(), sData.cbParameters = 0; nParameter < nParameters; nParameter++)
	{
		nParametersData.SetSize(sData.cbParameters + (cbData = (m_szParameters.GetAt(nParameter).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nParametersData.GetData() + sData.cbParameters, (LPCTSTR)m_szParameters.GetAt(nParameter), cbData);
		sData.cbParameters += cbData;
	}
	for (nExpression = 0, nExpressions = nParameters, sData.cbExpressions = 0; nExpression < nExpressions; nExpression++)
	{
		nExpressionsData.SetSize(sData.cbExpressions + (cbData = (nExpression < m_szExpressions.GetSize()) ? ((m_szExpressions.GetAt(nExpression).GetLength() + 1)*sizeof(TCHAR)) : sizeof(TCHAR)));
		CopyMemory(nExpressionsData.GetData() + sData.cbExpressions, (nExpression < m_szExpressions.GetSize()) ? (LPCTSTR)m_szExpressions.GetAt(nExpression) : EMPTYSTRING, cbData);
		sData.cbExpressions += cbData;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + sData.cbParameters + sData.cbExpressions)), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), nParametersData.GetData(), sData.cbParameters);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbParameters), nExpressionsData.GetData(), sData.cbExpressions);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentSetParametersItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbParameter;
	INT  cbParameters;
	INT  cbExpression;
	INT  cbExpressions;
	CByteArray  nParametersData;
	CByteArray  nExpressionsData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbParameters + sData.cbExpressions && sData.cbParameters >= 0 && sData.cbExpressions >= 0 && sData.nType == m_nType; )
	{
		for (nParametersData.SetSize(sData.cbParameters), nExpressionsData.SetSize(sData.cbExpressions), CopyMemory(nParametersData.GetData(), nData.GetData() + (cbData = sizeof(DATA)), sData.cbParameters), CopyMemory(nExpressionsData.GetData(), nData.GetData() + (cbData = cbData + sData.cbParameters), sData.cbExpressions), m_szParameters.RemoveAll(), m_szExpressions.RemoveAll(), cbParameter = cbParameters = 0; cbParameters < nParametersData.GetSize(); cbParameters += (cbParameter = (m_szParameters.GetAt(m_szParameters.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szParameters.Add((LPCTSTR)(nParametersData.GetData() + cbParameters));
			continue;
		}
		for (cbExpression = cbExpressions = 0; cbExpressions < nExpressionsData.GetSize(); cbExpressions += (cbExpression = (m_szExpressions.GetAt(m_szExpressions.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szExpressions.Add((LPCTSTR)(nExpressionsData.GetData() + cbExpressions));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentSetParametersItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentSetParametersItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentSetParametersItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentSetParametersItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetParametersItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetSynchronizationObjectItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentSetSynchronizationObjectItem, CTCProcedureDocumentItem)

CTCProcedureDocumentSetSynchronizationObjectItem::CTCProcedureDocumentSetSynchronizationObjectItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETSYNCOBJECT; LoadSymbol(IDP_TCACTIONOBJECTSETSYNCHRONIZATIONSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentSetSynchronizationObjectItem::~CTCProcedureDocumentSetSynchronizationObjectItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentSetSynchronizationObjectItem::SetObjectName(LPCTSTR pszName)
{
	m_szObjectName = pszName;
}

CString CTCProcedureDocumentSetSynchronizationObjectItem::GetObjectName() CONST
{
	return m_szObjectName;
}

BOOL CTCProcedureDocumentSetSynchronizationObjectItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetSynchronizationObjectItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSetSynchronizationObjectItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbObjectName = (m_szObjectName.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szObjectName, sData.cbObjectName);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentSetSynchronizationObjectItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbObjectName && sData.cbObjectName > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szObjectName.GetBufferSetLength(STRINGCHARS(sData.cbObjectName)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbObjectName));
		m_szObjectName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentSetSynchronizationObjectItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentSetSynchronizationObjectItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentSetSynchronizationObjectItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentSetSynchronizationObjectItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSetSynchronizationObjectItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentInjectAlertItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentInjectAlertItem, CTCProcedureDocumentItem)

CTCProcedureDocumentInjectAlertItem::CTCProcedureDocumentInjectAlertItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_INJECTALERT, m_nCategory = EVENTLOG_CATEGORY_NONE, m_nColor = GetSysColor(COLOR_WINDOWTEXT), m_bBlinking = FALSE; LoadSymbol(IDP_TCACTIONOBJECTINJECTALERTSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentInjectAlertItem::~CTCProcedureDocumentInjectAlertItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentInjectAlertItem::SetCategory(UINT nCategory)
{
	m_nCategory = nCategory;
}

UINT CTCProcedureDocumentInjectAlertItem::GetCategory() CONST
{
	return m_nCategory;
}

VOID CTCProcedureDocumentInjectAlertItem::SetType(LPCTSTR pszType)
{
	m_szType = pszType;
}

CString CTCProcedureDocumentInjectAlertItem::GetType() CONST
{
	return m_szType;
}

VOID CTCProcedureDocumentInjectAlertItem::SetSubtype(LPCTSTR pszSubtype)
{
	m_szSubtype = pszSubtype;
}

CString CTCProcedureDocumentInjectAlertItem::GetSubtype() CONST
{
	return m_szSubtype;
}

VOID CTCProcedureDocumentInjectAlertItem::SetMessage(LPCTSTR pszMessage)
{
	m_szMessage = pszMessage;
}

CString CTCProcedureDocumentInjectAlertItem::GetMessage() CONST
{
	return m_szMessage;
}

VOID CTCProcedureDocumentInjectAlertItem::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CTCProcedureDocumentInjectAlertItem::GetComments() CONST
{
	return m_szComments;
}

VOID CTCProcedureDocumentInjectAlertItem::SetAudition(LPCTSTR pszProfile)
{
	m_szAudition = pszProfile;
}

CString CTCProcedureDocumentInjectAlertItem::GetAudition() CONST
{
	return m_szAudition;
}

VOID CTCProcedureDocumentInjectAlertItem::SetNotification(LPCTSTR pszProfile)
{
	m_szNotification = pszProfile;
}

CString CTCProcedureDocumentInjectAlertItem::GetNotification() CONST
{
	return m_szNotification;
}

VOID CTCProcedureDocumentInjectAlertItem::SetColor(COLORREF nColor)
{
	m_nColor = nColor;
}

COLORREF CTCProcedureDocumentInjectAlertItem::GetColor() CONST
{
	return m_nColor;
}

VOID CTCProcedureDocumentInjectAlertItem::DoBlinking(BOOL bEnable)
{
	m_bBlinking = bEnable;
}

BOOL CTCProcedureDocumentInjectAlertItem::IsBlinking() CONST
{
	return m_bBlinking;
}

BOOL CTCProcedureDocumentInjectAlertItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentInjectAlertItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentInjectAlertItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbType = (m_szType.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbSubtype = (m_szSubtype.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbMessage = (m_szMessage.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbAudition = (m_szAudition.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbNotification = (m_szNotification.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType, sData.nCategory = m_nCategory, sData.nColor = m_nColor, sData.bBlinking = m_bBlinking; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szType, sData.cbType);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbType), (LPCTSTR)m_szSubtype, sData.cbSubtype);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbSubtype), (LPCTSTR)m_szMessage, sData.cbMessage);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbMessage), (LPCTSTR)m_szComments, sData.cbComments);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbComments), (LPCTSTR)m_szAudition, sData.cbAudition);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbAudition), (LPCTSTR)m_szNotification, sData.cbNotification);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentInjectAlertItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbType + sData.cbSubtype + sData.cbMessage + sData.cbComments + sData.cbAudition + sData.cbNotification && sData.cbType > 0 && sData.cbSubtype > 0 && sData.cbMessage > 0 && sData.cbComments > 0 && sData.cbAudition > 0 && sData.cbNotification > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szType.GetBufferSetLength(STRINGCHARS(sData.cbType)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbType));
		CopyMemory(m_szSubtype.GetBufferSetLength(STRINGCHARS(sData.cbSubtype)), nData.GetData() + (cbData = cbData + sData.cbType), STRINGBYTES(sData.cbSubtype));
		CopyMemory(m_szMessage.GetBufferSetLength(STRINGCHARS(sData.cbMessage)), nData.GetData() + (cbData = cbData + sData.cbSubtype), STRINGBYTES(sData.cbMessage));
		CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nData.GetData() + (cbData = cbData + sData.cbMessage), STRINGBYTES(sData.cbComments));
		CopyMemory(m_szAudition.GetBufferSetLength(STRINGCHARS(sData.cbAudition)), nData.GetData() + (cbData = cbData + sData.cbComments), STRINGBYTES(sData.cbAudition));
		CopyMemory(m_szNotification.GetBufferSetLength(STRINGCHARS(sData.cbNotification)), nData.GetData() + (cbData = cbData + sData.cbAudition), STRINGBYTES(sData.cbNotification));
		m_nCategory = sData.nCategory;
		m_bBlinking = sData.bBlinking;
		m_nColor = sData.nColor;
		m_szType.ReleaseBuffer();
		m_szSubtype.ReleaseBuffer();
		m_szMessage.ReleaseBuffer();
		m_szComments.ReleaseBuffer();
		m_szAudition.ReleaseBuffer();
		m_szNotification.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentInjectAlertItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentInjectAlertItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentInjectAlertItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentInjectAlertItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentInjectAlertItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentCallProcedureItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentCallProcedureItem, CTCProcedureDocumentItem)

CTCProcedureDocumentCallProcedureItem::CTCProcedureDocumentCallProcedureItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_CALLPROCEDURE; LoadSymbol(IDP_TCACTIONOBJECTCALLPROCEDURESYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentCallProcedureItem::~CTCProcedureDocumentCallProcedureItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentCallProcedureItem::SetProcedure(LPCTSTR pszName)
{
	m_szProcedure = pszName;
}

CString CTCProcedureDocumentCallProcedureItem::GetProcedure() CONST
{
	return m_szProcedure;
}

VOID CTCProcedureDocumentCallProcedureItem::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CTCProcedureDocumentCallProcedureItem::GetDescription() CONST
{
	return m_szDescription;
}

VOID CTCProcedureDocumentCallProcedureItem::SetInvariantCondition(LPCTSTR pszCondition)
{
	m_szCondition = pszCondition;
}

CString CTCProcedureDocumentCallProcedureItem::GetInvariantCondition() CONST
{
	return m_szCondition;
}

VOID CTCProcedureDocumentCallProcedureItem::SetArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CONST CStringArray &szValues)
{
	m_pDatabaseTCProcedureArguments.Copy(&pDatabaseTCProcedureArguments);
	m_szArgumentValues.Copy(szValues);
}

INT CTCProcedureDocumentCallProcedureItem::GetArguments(CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CStringArray &szValues) CONST
{
	INT  nArgument;
	INT  nArguments;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;

	for (nArgument = 0, nArguments = (INT)m_pDatabaseTCProcedureArguments.GetSize(), pDatabaseTCProcedureArguments.Copy(&m_pDatabaseTCProcedureArguments), szValues.Copy(m_szArgumentValues); nArgument < nArguments; nArgument++)
	{
		if ((pDatabaseTCProcedureArgument = pDatabaseTCProcedureArguments.GetAt(nArgument)) && !pDatabaseTCProcedureArgument->GetConstValueAsText().IsEmpty() && (nArgument >= szValues.GetSize() || szValues.GetAt(nArgument).IsEmpty()))
		{
			szValues.SetAtGrow(nArgument, pDatabaseTCProcedureArgument->GetConstValueAsText());
			continue;
		}
	}
	return((INT)pDatabaseTCProcedureArguments.GetSize());
}

BOOL CTCProcedureDocumentCallProcedureItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentCallProcedureItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentCallProcedureItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	INT  nValue;
	INT  nValues;
	CByteArray  nArgumentsData;
	CByteArray  nValuesData;
	DATA  sData = { 0 };

	for (nValue = 0, nValues = (INT)m_szArgumentValues.GetSize(), sData.cbArgumentValues = 0; nValue < nValues; nValue++)
	{
		nValuesData.SetSize(sData.cbArgumentValues + (cbData = (m_szArgumentValues.GetAt(nValue).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nValuesData.GetData() + sData.cbArgumentValues, (LPCTSTR)m_szArgumentValues.GetAt(nValue), cbData);
		sData.cbArgumentValues += cbData;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbProcedure = (m_szProcedure.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbDescription = (m_szDescription.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbCondition = (m_szCondition.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbArguments = (m_pDatabaseTCProcedureArguments.Map(nArgumentsData)) ? (INT)nArgumentsData.GetSize() : -1) + sData.cbArgumentValues)), sData.nType = m_nType; sData.cbSize == (INT)nData.GetSize() && sData.cbArguments >= 0; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szProcedure, sData.cbProcedure);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbProcedure), (LPCTSTR)m_szDescription, sData.cbDescription);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbDescription), (LPCTSTR)m_szCondition, sData.cbCondition);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbCondition), nArgumentsData.GetData(), sData.cbArguments);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbArguments), nValuesData.GetData(), sData.cbArgumentValues);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentCallProcedureItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbValue;
	INT  cbValues;
	CByteArray  nArgumentsData;
	CByteArray  nValuesData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbProcedure + sData.cbDescription + sData.cbCondition + sData.cbArguments + sData.cbArgumentValues && sData.cbProcedure > 0 && sData.cbDescription > 0 && sData.cbCondition > 0 && sData.cbArguments >= 0 && sData.cbArgumentValues >= 0 && sData.nType == m_nType; )
	{
		for (nArgumentsData.SetSize(sData.cbArguments), nValuesData.SetSize(sData.cbArgumentValues), CopyMemory(m_szProcedure.GetBufferSetLength(STRINGCHARS(sData.cbProcedure)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbProcedure)), CopyMemory(m_szDescription.GetBufferSetLength(STRINGCHARS(sData.cbDescription)), nData.GetData() + (cbData = cbData + sData.cbProcedure), STRINGBYTES(sData.cbDescription)), CopyMemory(m_szCondition.GetBufferSetLength(STRINGCHARS(sData.cbCondition)), nData.GetData() + (cbData = cbData + sData.cbDescription), STRINGBYTES(sData.cbCondition)), CopyMemory(nArgumentsData.GetData(), nData.GetData() + (cbData = cbData + sData.cbCondition), STRINGBYTES(sData.cbArguments)), CopyMemory(nValuesData.GetData(), nData.GetData() + (cbData = cbData + sData.cbArguments), sData.cbArgumentValues), m_szProcedure.ReleaseBuffer(), m_szDescription.ReleaseBuffer(), m_szCondition.ReleaseBuffer(); m_pDatabaseTCProcedureArguments.Unmap(nArgumentsData); )
		{
			for (cbValue = 0, cbValues = 0, m_szArgumentValues.RemoveAll(); cbValues < nValuesData.GetSize(); cbValues += (cbValue = (m_szArgumentValues.GetAt(m_szArgumentValues.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
			{
				m_szArgumentValues.Add((LPCTSTR)(nValuesData.GetData() + cbValues));
				continue;
			}
			return((cbValues == nValuesData.GetSize()) ? TRUE : FALSE);
		}
		break;
	}
	return FALSE;
}

VOID CTCProcedureDocumentCallProcedureItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentCallProcedureItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentCallProcedureItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentCallProcedureItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentCallProcedureItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentStartProcedureItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentStartProcedureItem, CTCProcedureDocumentItem)

CTCProcedureDocumentStartProcedureItem::CTCProcedureDocumentStartProcedureItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_STARTPROCEDURE; LoadSymbol(IDP_TCACTIONOBJECTSTARTPROCEDURESYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentStartProcedureItem::~CTCProcedureDocumentStartProcedureItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentStartProcedureItem::SetProcedure(LPCTSTR pszName)
{
	m_szProcedure = pszName;
}

CString CTCProcedureDocumentStartProcedureItem::GetProcedure() CONST
{
	return m_szProcedure;
}

VOID CTCProcedureDocumentStartProcedureItem::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CTCProcedureDocumentStartProcedureItem::GetDescription() CONST
{
	return m_szDescription;
}

VOID CTCProcedureDocumentStartProcedureItem::SetInvariantCondition(LPCTSTR pszCondition)
{
	m_szCondition = pszCondition;
}

CString CTCProcedureDocumentStartProcedureItem::GetInvariantCondition() CONST
{
	return m_szCondition;
}

VOID CTCProcedureDocumentStartProcedureItem::SetArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CONST CStringArray &szValues)
{
	m_pDatabaseTCProcedureArguments.Copy(&pDatabaseTCProcedureArguments);
	m_szArgumentValues.Copy(szValues);
}

INT CTCProcedureDocumentStartProcedureItem::GetArguments(CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CStringArray &szValues) CONST
{
	INT  nArgument;
	INT  nArguments;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;

	for (nArgument = 0, nArguments = (INT)m_pDatabaseTCProcedureArguments.GetSize(), pDatabaseTCProcedureArguments.Copy(&m_pDatabaseTCProcedureArguments), szValues.Copy(m_szArgumentValues); nArgument < nArguments; nArgument++)
	{
		if ((pDatabaseTCProcedureArgument = pDatabaseTCProcedureArguments.GetAt(nArgument)) && !pDatabaseTCProcedureArgument->GetConstValueAsText().IsEmpty() && (nArgument >= szValues.GetSize() || szValues.GetAt(nArgument).IsEmpty()))
		{
			szValues.SetAtGrow(nArgument, pDatabaseTCProcedureArgument->GetConstValueAsText());
			continue;
		}
	}
	return((INT)pDatabaseTCProcedureArguments.GetSize());
}

BOOL CTCProcedureDocumentStartProcedureItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentStartProcedureItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentStartProcedureItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	INT  nValue;
	INT  nValues;
	CByteArray  nArgumentsData;
	CByteArray  nValuesData;
	DATA  sData = { 0 };

	for (nValue = 0, nValues = (INT)m_szArgumentValues.GetSize(), sData.cbArgumentValues = 0; nValue < nValues; nValue++)
	{
		nValuesData.SetSize(sData.cbArgumentValues + (cbData = (m_szArgumentValues.GetAt(nValue).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nValuesData.GetData() + sData.cbArgumentValues, (LPCTSTR)m_szArgumentValues.GetAt(nValue), cbData);
		sData.cbArgumentValues += cbData;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbProcedure = (m_szProcedure.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbDescription = (m_szDescription.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbCondition = (m_szCondition.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbArguments = (m_pDatabaseTCProcedureArguments.Map(nArgumentsData)) ? (INT)nArgumentsData.GetSize() : -1) + sData.cbArgumentValues)), sData.nType = m_nType; sData.cbSize == (INT)nData.GetSize() && sData.cbArguments >= 0; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szProcedure, sData.cbProcedure);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbProcedure), (LPCTSTR)m_szDescription, sData.cbDescription);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbDescription), (LPCTSTR)m_szCondition, sData.cbCondition);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbCondition), nArgumentsData.GetData(), sData.cbArguments);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbArguments), nValuesData.GetData(), sData.cbArgumentValues);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentStartProcedureItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbValue;
	INT  cbValues;
	CByteArray  nArgumentsData;
	CByteArray  nValuesData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbProcedure + sData.cbDescription + sData.cbCondition + sData.cbArguments + sData.cbArgumentValues && sData.cbProcedure > 0 && sData.cbDescription > 0 && sData.cbCondition > 0 && sData.cbArguments >= 0 && sData.cbArgumentValues >= 0 && sData.nType == m_nType; )
	{
		for (nArgumentsData.SetSize(sData.cbArguments), nValuesData.SetSize(sData.cbArgumentValues), CopyMemory(m_szProcedure.GetBufferSetLength(STRINGCHARS(sData.cbProcedure)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbProcedure)), CopyMemory(m_szDescription.GetBufferSetLength(STRINGCHARS(sData.cbDescription)), nData.GetData() + (cbData = cbData + sData.cbProcedure), STRINGBYTES(sData.cbDescription)), CopyMemory(m_szCondition.GetBufferSetLength(STRINGCHARS(sData.cbCondition)), nData.GetData() + (cbData = cbData + sData.cbDescription), STRINGBYTES(sData.cbCondition)), CopyMemory(nArgumentsData.GetData(), nData.GetData() + (cbData = cbData + sData.cbCondition), STRINGBYTES(sData.cbArguments)), CopyMemory(nValuesData.GetData(), nData.GetData() + (cbData = cbData + sData.cbArguments), sData.cbArgumentValues), m_szProcedure.ReleaseBuffer(), m_szDescription.ReleaseBuffer(), m_szCondition.ReleaseBuffer(); m_pDatabaseTCProcedureArguments.Unmap(nArgumentsData); )
		{
			for (cbValue = 0, cbValues = 0, m_szArgumentValues.RemoveAll(); cbValues < nValuesData.GetSize(); cbValues += (cbValue = (m_szArgumentValues.GetAt(m_szArgumentValues.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
			{
				m_szArgumentValues.Add((LPCTSTR)(nValuesData.GetData() + cbValues));
				continue;
			}
			return((cbValues == nValuesData.GetSize()) ? TRUE : FALSE);
		}
		break;
	}
	return FALSE;
}

VOID CTCProcedureDocumentStartProcedureItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentStartProcedureItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentStartProcedureItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentStartProcedureItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentStartProcedureItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentControlProcedureItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentControlProcedureItem, CTCProcedureDocumentItem)

CTCProcedureDocumentControlProcedureItem::CTCProcedureDocumentControlProcedureItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_CONTROLPROCEDURE, m_nState = 0; LoadSymbol(IDP_TCACTIONOBJECTCONTROLPROCEDURESYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentControlProcedureItem::~CTCProcedureDocumentControlProcedureItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentControlProcedureItem::SetProcedure(LPCTSTR pszName)
{
	m_szProcedure = pszName;
}

CString CTCProcedureDocumentControlProcedureItem::GetProcedure() CONST
{
	return m_szProcedure;
}

VOID CTCProcedureDocumentControlProcedureItem::SetActionState(UINT nState)
{
	m_nState = nState;
}

UINT CTCProcedureDocumentControlProcedureItem::GetActionState() CONST
{
	return m_nState;
}

BOOL CTCProcedureDocumentControlProcedureItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentControlProcedureItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentControlProcedureItem::MapProperties(CByteArray &nData) CONST
{
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbProcedure = (m_szProcedure.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType, sData.nState = m_nState; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + sizeof(DATA), (LPCTSTR)m_szProcedure, sData.cbProcedure);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentControlProcedureItem::UnmapProperties(CONST CByteArray &nData)
{
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbProcedure && sData.cbProcedure > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szProcedure.GetBufferSetLength(STRINGCHARS(sData.cbProcedure)), nData.GetData() + sizeof(DATA), STRINGBYTES(sData.cbProcedure));
		m_szProcedure.ReleaseBuffer();
		m_nState = sData.nState;
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentControlProcedureItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentControlProcedureItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentControlProcedureItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentControlProcedureItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentControlProcedureItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentControlThreadItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentControlThreadItem, CTCProcedureDocumentItem)

CTCProcedureDocumentControlThreadItem::CTCProcedureDocumentControlThreadItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_CONTROLTHREAD, m_nState = 0; LoadSymbol(IDP_TCACTIONOBJECTCONTROLTHREADSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentControlThreadItem::~CTCProcedureDocumentControlThreadItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentControlThreadItem::SetThread(LPCTSTR pszName)
{
	m_szThread = pszName;
}

CString CTCProcedureDocumentControlThreadItem::GetThread() CONST
{
	return m_szThread;
}

VOID CTCProcedureDocumentControlThreadItem::SetActionState(UINT nState)
{
	m_nState = nState;
}

UINT CTCProcedureDocumentControlThreadItem::GetActionState() CONST
{
	return m_nState;
}

BOOL CTCProcedureDocumentControlThreadItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentControlThreadItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentControlThreadItem::MapProperties(CByteArray &nData) CONST
{
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbThread = (m_szThread.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType, sData.nState = m_nState; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + sizeof(DATA), (LPCTSTR)m_szThread, sData.cbThread);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentControlThreadItem::UnmapProperties(CONST CByteArray &nData)
{
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbThread && sData.cbThread > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szThread.GetBufferSetLength(STRINGCHARS(sData.cbThread)), nData.GetData() + sizeof(DATA), STRINGBYTES(sData.cbThread));
		m_szThread.ReleaseBuffer();
		m_nState = sData.nState;
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentControlThreadItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentControlThreadItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentControlThreadItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentControlThreadItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentControlThreadItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWaitTimeIntervalItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentWaitTimeIntervalItem, CTCProcedureDocumentItem)

CTCProcedureDocumentWaitTimeIntervalItem::CTCProcedureDocumentWaitTimeIntervalItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_WAITTIMEINTERVAL, m_tWaitTime = 0, m_dwWaitInterval = 0; LoadSymbol(IDP_TCACTIONOBJECTWAITTIMEINTERVALSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentWaitTimeIntervalItem::~CTCProcedureDocumentWaitTimeIntervalItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentWaitTimeIntervalItem::SetWaitInterval(DWORD dwInterval)
{
	m_dwWaitInterval = dwInterval;
	m_tWaitTime = 0;
}

DWORD CTCProcedureDocumentWaitTimeIntervalItem::GetWaitInterval() CONST
{
	return m_dwWaitInterval;
}

VOID CTCProcedureDocumentWaitTimeIntervalItem::SetWaitTime(CONST CTimeKey &tTime)
{
	m_tWaitTime = tTime;
	m_dwWaitInterval = 0;
}

CTimeKey CTCProcedureDocumentWaitTimeIntervalItem::GetWaitTime() CONST
{
	return m_tWaitTime;
}

BOOL CTCProcedureDocumentWaitTimeIntervalItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentWaitTimeIntervalItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentWaitTimeIntervalItem::MapProperties(CByteArray &nData) CONST
{
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA))), sData.nType = m_nType, sData.dwWaitInterval = m_dwWaitInterval, sData.tWaitTime = m_tWaitTime.GetTime(); nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentWaitTimeIntervalItem::UnmapProperties(CONST CByteArray &nData)
{
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.nType == m_nType; )
	{
		m_dwWaitInterval = sData.dwWaitInterval;
		m_tWaitTime = sData.tWaitTime;
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentWaitTimeIntervalItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentWaitTimeIntervalItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentWaitTimeIntervalItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentWaitTimeIntervalItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWaitTimeIntervalItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWaitSynchronizationObjectItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentWaitSynchronizationObjectItem, CTCProcedureDocumentItem)

CTCProcedureDocumentWaitSynchronizationObjectItem::CTCProcedureDocumentWaitSynchronizationObjectItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_WAITSYNCOBJECT, m_dwTimeout = INFINITE; LoadSymbol(IDP_TCACTIONOBJECTWAITSYNCHRONIZATIONSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentWaitSynchronizationObjectItem::~CTCProcedureDocumentWaitSynchronizationObjectItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentWaitSynchronizationObjectItem::SetObjectName(LPCTSTR pszName)
{
	m_szObjectName = pszName;
}

CString CTCProcedureDocumentWaitSynchronizationObjectItem::GetObjectName() CONST
{
	return m_szObjectName;
}

VOID CTCProcedureDocumentWaitSynchronizationObjectItem::SetTimeout(DWORD dwTimeout)
{
	m_dwTimeout = dwTimeout;
}

DWORD CTCProcedureDocumentWaitSynchronizationObjectItem::GetTimeout() CONST
{
	return m_dwTimeout;
}

BOOL CTCProcedureDocumentWaitSynchronizationObjectItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentWaitSynchronizationObjectItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentWaitSynchronizationObjectItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbObjectName = (m_szObjectName.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType, sData.dwTimeout = m_dwTimeout; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szObjectName, sData.cbObjectName);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentWaitSynchronizationObjectItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbObjectName && sData.cbObjectName > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szObjectName.GetBufferSetLength(STRINGCHARS(sData.cbObjectName)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbObjectName));
		m_dwTimeout = sData.dwTimeout;
		m_szObjectName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentWaitSynchronizationObjectItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentWaitSynchronizationObjectItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentWaitSynchronizationObjectItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentWaitSynchronizationObjectItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentWaitSynchronizationObjectItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSendTCFunctionItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentSendTCFunctionItem, CTCProcedureDocumentItem)

CTCProcedureDocumentSendTCFunctionItem::CTCProcedureDocumentSendTCFunctionItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCFUNCTION, m_nOptions = 0, m_tTimeWindow = 0, m_tReleaseTime = m_tExecutionTime = 0, m_dwReleaseDelta = m_dwExecutionDelta = 0, m_bExeEarlier = FALSE; LoadSymbol(IDP_TCACTIONOBJECTSENDTCFUNCTIONSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentSendTCFunctionItem::~CTCProcedureDocumentSendTCFunctionItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

BOOL CTCProcedureDocumentSendTCFunctionItem::SetFunction(CONST CDatabaseTCFunction *pFunction, CONST CDatabaseTCPacket *pPacket)
{
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunction  cFunction;

	return((((pFunction != (CDatabaseTCFunction *)NULL  &&  m_cFunction.Copy(pFunction)) || (!pFunction  &&  m_cFunction.Copy(&cFunction))) && ((pPacket != (CDatabaseTCPacket *)NULL  &&  m_cPacket.Copy(pPacket)) || (!pPacket  &&  m_cPacket.Copy(&cPacket)))) ? TRUE : FALSE);
}

BOOL CTCProcedureDocumentSendTCFunctionItem::GetFunction(CDatabaseTCFunction *pFunction, CDatabaseTCPacket *pPacket) CONST
{
	return((pFunction->Copy(&m_cFunction) && pPacket->Copy(&m_cPacket)) ? TRUE : FALSE);
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CTCProcedureDocumentSendTCFunctionItem::GetDescription() CONST
{
	return m_szDescription;
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CTCProcedureDocumentSendTCFunctionItem::GetOptions() CONST
{
	return m_nOptions;
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetPreexecutionVerificationCondition(LPCTSTR pszCondition)
{
	m_szCondition[0] = pszCondition;
}

CString CTCProcedureDocumentSendTCFunctionItem::GetPreexecutionVerificationCondition() CONST
{
	return m_szCondition[0];
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetExecutionVerificationCondition(LPCTSTR pszCondition)
{
	m_szCondition[1] = pszCondition;
}

CString CTCProcedureDocumentSendTCFunctionItem::GetExecutionVerificationCondition() CONST
{
	return m_szCondition[1];
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetExecutionVerificationTimeWindow(CONST CTimeSpan &tInterval)
{
	m_tTimeWindow = tInterval;
}

CTimeSpan CTCProcedureDocumentSendTCFunctionItem::GetExecutionVerificationTimeWindow() CONST
{
	return m_tTimeWindow;
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetReleaseTime(CONST CTimeTag &tTime)
{
	m_tReleaseTime = tTime;
}

CTimeTag CTCProcedureDocumentSendTCFunctionItem::GetReleaseTime() CONST
{
	return m_tReleaseTime;
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetReleaseDeltaTime(DWORD dwDelta)
{
	m_dwReleaseDelta = dwDelta;
}

DWORD CTCProcedureDocumentSendTCFunctionItem::GetReleaseDeltaTime() CONST
{
	return m_dwReleaseDelta;
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetExecutionTime(CONST CTimeTag &tTime)
{
	m_tExecutionTime = tTime;
}

CTimeTag CTCProcedureDocumentSendTCFunctionItem::GetExecutionTime() CONST
{
	return m_tExecutionTime;
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetExecutionDeltaTime(DWORD dwDelta, BOOL bEarlier)
{
	m_dwExecutionDelta = dwDelta;
	m_bExeEarlier = bEarlier;
}

DWORD CTCProcedureDocumentSendTCFunctionItem::GetExecutionDeltaTime(BOOL &bEarlier) CONST
{
	bEarlier = m_bExeEarlier;
	return m_dwExecutionDelta;
}
DWORD CTCProcedureDocumentSendTCFunctionItem::GetExecutionDeltaTime() CONST
{
	return m_dwExecutionDelta;
}

BOOL CTCProcedureDocumentSendTCFunctionItem::IsEarlierExecutionDeltaTime() CONST
{
	return m_bExeEarlier;
}

VOID CTCProcedureDocumentSendTCFunctionItem::SetMemoryPatch(LPCTSTR pszMemoryPatch)
{
	m_szMemoryPatch = pszMemoryPatch;
}

CString CTCProcedureDocumentSendTCFunctionItem::GetMemoryPatch() CONST
{
	return m_szMemoryPatch;
}

BOOL CTCProcedureDocumentSendTCFunctionItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSendTCFunctionItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSendTCFunctionItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	CByteArray  nFunctionData[2];
	DATA  sData = { 0 };

	sData.cbDescription = (m_szDescription.GetLength() + 1)*sizeof(TCHAR);
	sData.cbCondition[0] = (m_szCondition[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbCondition[1] = (m_szCondition[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbMemoryPatch = (m_szMemoryPatch.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFunction[0] = (m_cFunction.Map(nFunctionData[0], FALSE)) ? (INT)nFunctionData[0].GetSize() : -1;
	sData.cbFunction[1] = (m_cPacket.Map(nFunctionData[1], FALSE)) ? (INT)nFunctionData[1].GetSize() : -1;
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + max(sData.cbFunction[0], 0) + max(sData.cbFunction[1], 0) + sData.cbDescription + sData.cbCondition[0] + sData.cbCondition[1] + sData.cbMemoryPatch)), sData.nType = m_nType, sData.nOptions = m_nOptions, sData.tReleaseTime = m_tReleaseTime.GetTime(), sData.dwReleaseDelta = m_dwReleaseDelta, sData.tExecutionTime = m_tExecutionTime.GetTime(), sData.dwExecutionDelta = m_dwExecutionDelta, sData.bExeEarlier = m_bExeEarlier, sData.tTimeWindow = m_tTimeWindow.GetTotalSeconds(); nData.GetSize() == sData.cbSize && sData.cbFunction[0] >= 0 && sData.cbFunction[1] >= 0; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), nFunctionData[0].GetData(), sData.cbFunction[0]);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbFunction[0]), nFunctionData[1].GetData(), sData.cbFunction[1]);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbFunction[1]), (LPCTSTR)m_szDescription, sData.cbDescription);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbDescription), (LPCTSTR)m_szCondition[0], sData.cbCondition[0]);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbCondition[0]), (LPCTSTR)m_szCondition[1], sData.cbCondition[1]);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbCondition[1]), (LPCTSTR)m_szMemoryPatch, sData.cbMemoryPatch);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentSendTCFunctionItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	CByteArray  nFunctionData[2];
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbFunction[0] + sData.cbFunction[1] + sData.cbDescription + sData.cbCondition[0] + sData.cbCondition[1] + sData.cbMemoryPatch && sData.cbFunction[0] > 0 && sData.cbFunction[1] > 0 && sData.cbDescription > 0 && sData.cbCondition[0] > 0 && sData.cbCondition[1] > 0 && sData.cbMemoryPatch > 0 && sData.nType == m_nType; )
	{
		for (nFunctionData[0].SetSize(sData.cbFunction[0]), nFunctionData[1].SetSize(sData.cbFunction[1]), CopyMemory(nFunctionData[0].GetData(), nData.GetData() + (cbData = sizeof(DATA)), sData.cbFunction[0]), CopyMemory(nFunctionData[1].GetData(), nData.GetData() + (cbData = cbData + sData.cbFunction[0]), sData.cbFunction[1]), CopyMemory(m_szDescription.GetBufferSetLength(STRINGCHARS(sData.cbDescription)), nData.GetData() + (cbData = cbData + sData.cbFunction[1]), STRINGBYTES(sData.cbDescription)), CopyMemory(m_szCondition[0].GetBufferSetLength(STRINGCHARS(sData.cbCondition[0])), nData.GetData() + (cbData = cbData + sData.cbDescription), STRINGBYTES(sData.cbCondition[0])), CopyMemory(m_szCondition[1].GetBufferSetLength(STRINGCHARS(sData.cbCondition[1])), nData.GetData() + (cbData = cbData + sData.cbCondition[0]), STRINGBYTES(sData.cbCondition[1])), CopyMemory(m_szMemoryPatch.GetBufferSetLength(STRINGCHARS(sData.cbMemoryPatch)), nData.GetData() + (cbData = cbData + sData.cbCondition[1]), STRINGBYTES(sData.cbMemoryPatch)), m_nOptions = sData.nOptions, m_tReleaseTime = sData.tReleaseTime, m_dwReleaseDelta = sData.dwReleaseDelta, m_tExecutionTime = sData.tExecutionTime, m_dwExecutionDelta = sData.dwExecutionDelta, m_bExeEarlier = sData.bExeEarlier, m_tTimeWindow = sData.tTimeWindow, m_szDescription.ReleaseBuffer(), m_szCondition[0].ReleaseBuffer(), m_szCondition[1].ReleaseBuffer(), m_szMemoryPatch.ReleaseBuffer(); m_cFunction.Unmap(nFunctionData[0], FALSE) && m_cPacket.Unmap(nFunctionData[1], FALSE); ) return TRUE;
		break;
	}
	return FALSE;
}

VOID CTCProcedureDocumentSendTCFunctionItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentSendTCFunctionItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentSendTCFunctionItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentSendTCFunctionItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSendTCFunctionItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSendTCSequenceItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentSendTCSequenceItem, CTCProcedureDocumentItem)

CTCProcedureDocumentSendTCSequenceItem::CTCProcedureDocumentSendTCSequenceItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE; LoadSymbol(IDP_TCACTIONOBJECTSENDTCSEQUENCESYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentSendTCSequenceItem::~CTCProcedureDocumentSendTCSequenceItem()
{
	RemoveAll();
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentSendTCSequenceItem::SetSequence(LPCTSTR pszSequence)
{
	m_szSequence = pszSequence;
}

CString CTCProcedureDocumentSendTCSequenceItem::GetSequence() CONST
{
	return m_szSequence;
}

VOID CTCProcedureDocumentSendTCSequenceItem::SetParameters(CONST CDatabaseTCParameters &pParameters)
{
	m_pParameters.Copy(&pParameters);
}

INT CTCProcedureDocumentSendTCSequenceItem::GetParameters(CDatabaseTCParameters &pParameters) CONST
{
	pParameters.Copy(&m_pParameters);
	return((INT)pParameters.GetSize());
}

INT CTCProcedureDocumentSendTCSequenceItem::Add(CTCProcedureDocumentSendTCFunctionItem *pItem)
{
	return((INT)m_pItems.Add(pItem));
}

CTCProcedureDocumentSendTCFunctionItem *CTCProcedureDocumentSendTCSequenceItem::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < m_pItems.GetSize()) ? (CTCProcedureDocumentSendTCFunctionItem *)m_pItems.GetAt(nIndex) : (CTCProcedureDocumentSendTCFunctionItem *)NULL);
}

CTCProcedureDocumentSendTCFunctionItem *CTCProcedureDocumentSendTCSequenceItem::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < m_pItems.GetSize()) ? (CTCProcedureDocumentSendTCFunctionItem *)m_pItems.GetAt(nIndex) : (CTCProcedureDocumentSendTCFunctionItem *)NULL);
}

INT CTCProcedureDocumentSendTCSequenceItem::GetSize() CONST
{
	return((INT)m_pItems.GetSize());
}

VOID CTCProcedureDocumentSendTCSequenceItem::RemoveAll()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(); nItem < nItems; nItem++)
	{
		delete GetAt(nItem);
		continue;
	}
	m_pItems.RemoveAll();
}

BOOL CTCProcedureDocumentSendTCSequenceItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSendTCSequenceItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentSendTCSequenceItem::MapProperties(CByteArray &nData) CONST
{
	INT  nItem;
	INT  nItems;
	INT  cbData;
	CByteArray  nItemsData[2];
	CByteArray  nParametersData;
	CTCProcedureDocumentSendTCFunctionItem  *pItem;
	DATA  sData = { 0 };

	for (nItem = 0, nItems = GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && pItem->Map(nItemsData[1]) && nItemsData[0].Append(nItemsData[1]) >= 0) continue;
		break;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbSequence = (m_szSequence.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbParameters = (m_pParameters.Map(nParametersData)) ? (INT)nParametersData.GetSize() : -1) + (sData.cbEntries = (INT)nItemsData[0].GetSize()))), sData.nType = m_nType; nItem == nItems && sData.cbParameters >= 0; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szSequence, sData.cbSequence);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbSequence), nParametersData.GetData(), sData.cbParameters);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbParameters), nItemsData[0].GetData(), sData.cbEntries);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentSendTCSequenceItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbItem;
	INT  cbItems;
	INT  cbData;
	CByteArray  nItemsData[2];
	CByteArray  nParametersData;
	CTCProcedureDocumentSendTCFunctionItem  *pItem;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbSequence + sData.cbParameters + sData.cbEntries && sData.cbSequence > 0 && sData.cbParameters >= 0 && sData.cbEntries >= 0 && sData.nType == m_nType; )
	{
		for (nParametersData.SetSize(sData.cbParameters), nItemsData[0].SetSize(sData.cbEntries), CopyMemory(m_szSequence.GetBufferSetLength(STRINGCHARS(sData.cbSequence)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbSequence)), CopyMemory(nParametersData.GetData(), nData.GetData() + (cbData = cbData + sData.cbSequence), sData.cbParameters), CopyMemory(nItemsData[0].GetData(), nData.GetData() + (cbData = cbData + sData.cbParameters), sData.cbEntries), m_szSequence.ReleaseBuffer(), cbItems = 0, RemoveAll(); cbItems < nItemsData[0].GetSize(); cbItems += cbItem)
		{
			for (CopyMemory(&cbItem, nItemsData[0].GetData() + cbItems, sizeof(cbItem)), nItemsData[1].SetSize(max(min(cbItem, nItemsData[0].GetSize() - cbItems), 0)); nItemsData[1].GetSize() >= 0; )
			{
				CopyMemory(nItemsData[1].GetData(), nItemsData[0].GetData() + cbItems, nItemsData[1].GetSize());
				break;
			}
			if ((pItem = new CTCProcedureDocumentSendTCFunctionItem))
			{
				if (pItem->Unmap(nItemsData[1]) && Add(pItem) >= 0) continue;
				delete pItem;
			}
			break;
		}
		return((m_pParameters.Unmap(nParametersData) && cbItems == nItemsData[0].GetSize()) ? TRUE : FALSE);
	}
	return FALSE;
}

VOID CTCProcedureDocumentSendTCSequenceItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentSendTCSequenceItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentSendTCSequenceItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentSendTCSequenceItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentSendTCSequenceItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentLogMessageItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentLogMessageItem, CTCProcedureDocumentItem)

CTCProcedureDocumentLogMessageItem::CTCProcedureDocumentLogMessageItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_LOGMESSAGE, m_nOptions = 0; LoadSymbol(IDP_TCACTIONOBJECTLOGMESSAGESYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentLogMessageItem::~CTCProcedureDocumentLogMessageItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentLogMessageItem::SetMessage(LPCTSTR pszMessage)
{
	m_szMessage = pszMessage;
}

CString CTCProcedureDocumentLogMessageItem::GetMessage() CONST
{
	return m_szMessage;
}

VOID CTCProcedureDocumentLogMessageItem::SetFileName(LPCTSTR pszFileName)
{
	m_szFileName = pszFileName;
}

CString CTCProcedureDocumentLogMessageItem::GetFileName() CONST
{
	return m_szFileName;
}

VOID CTCProcedureDocumentLogMessageItem::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CTCProcedureDocumentLogMessageItem::GetOptions() CONST
{
	return m_nOptions;
}

BOOL CTCProcedureDocumentLogMessageItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentLogMessageItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentLogMessageItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	DATA  sData = { 0 };

	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbMessage = (m_szMessage.GetLength() + 1)*sizeof(TCHAR)) + (sData.cbFileName = (m_szFileName.GetLength() + 1)*sizeof(TCHAR)))), sData.nType = m_nType, sData.nOptions = m_nOptions; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szMessage, sData.cbMessage);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbMessage), (LPCTSTR)m_szFileName, sData.cbFileName);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentLogMessageItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbMessage + sData.cbFileName && sData.cbMessage > 0 && sData.cbFileName > 0 && sData.nType == m_nType; )
	{
		CopyMemory(m_szMessage.GetBufferSetLength(STRINGCHARS(sData.cbMessage)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbMessage));
		CopyMemory(m_szFileName.GetBufferSetLength(STRINGCHARS(sData.cbFileName)), nData.GetData() + (cbData = cbData + sData.cbMessage), STRINGBYTES(sData.cbFileName));
		m_nOptions = sData.nOptions;
		m_szMessage.ReleaseBuffer();
		m_szFileName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentLogMessageItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentLogMessageItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentLogMessageItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentLogMessageItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentLogMessageItem commands


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentUserInteractionItem

IMPLEMENT_DYNCREATE(CTCProcedureDocumentUserInteractionItem, CTCProcedureDocumentItem)

CTCProcedureDocumentUserInteractionItem::CTCProcedureDocumentUserInteractionItem(CTCProcedureDocument *pContainerDoc, UINT nSubThreadID) : CTCProcedureDocumentItem(pContainerDoc, nSubThreadID)
{
	for (m_nType = TCPROCEDURETHREADSTEP_ACTIONOBJECT_USERINTERACTION, m_nAction = 0; LoadSymbol(IDP_TCACTIONOBJECTUSERINTERACTIONSYMBOL, m_cSymbol[0]) && LoadSymbol(IDP_TCFLOWSTATUSSYMBOL, m_cSymbol[1]); )
	{
		m_sizeSymbol[0].cx = m_cSymbol[0].GetWidth();
		m_sizeSymbol[0].cy = m_cSymbol[0].GetHeight();
		m_sizeSymbol[1].cx = m_cSymbol[1].GetWidth();
		m_sizeSymbol[1].cy = m_cSymbol[1].GetHeight();
		break;
	}
}

CTCProcedureDocumentUserInteractionItem::~CTCProcedureDocumentUserInteractionItem()
{
	m_cSymbol[0].Destroy();
	m_cSymbol[1].Destroy();
}

VOID CTCProcedureDocumentUserInteractionItem::SetAction(UINT nAction)
{
	m_nAction = nAction;
}

UINT CTCProcedureDocumentUserInteractionItem::GetAction() CONST
{
	return m_nAction;
}

VOID CTCProcedureDocumentUserInteractionItem::SetMessage(LPCTSTR pszMessage)
{
	m_szMessage = pszMessage;
}

CString CTCProcedureDocumentUserInteractionItem::GetMessage() CONST
{
	return m_szMessage;
}

VOID CTCProcedureDocumentUserInteractionItem::SetVariables(CONST CStringArray &szVariables)
{
	INT  nVariable[2];
	INT  nVariables[2];
	CStringArray  szValues;

	for (nVariable[0] = 0, nVariables[0] = (INT)szVariables.GetSize(); nVariable[0] < nVariables[0]; nVariable[0]++)
	{
		for (nVariable[1] = 0, nVariables[1] = (INT)m_szVariables.GetSize(); nVariable[1] < nVariables[1]; nVariable[1]++)
		{
			if (m_szVariables.GetAt(nVariable[1]) == szVariables.GetAt(nVariable[0])) break;
			continue;
		}
		if (nVariable[1] < nVariables[1])
		{
			szValues.SetAtGrow(nVariable[0], m_szValues.GetAt(nVariable[1]));
			continue;
		}
		szValues.SetAtGrow(nVariable[0], EMPTYSTRING);
	}
	m_szVariables.Copy(szVariables);
	m_szValues.Copy(szValues);
}

INT CTCProcedureDocumentUserInteractionItem::GetVariables(CStringArray &szVariables) CONST
{
	szVariables.Copy(m_szVariables);
	return((INT)szVariables.GetSize());
}

VOID CTCProcedureDocumentUserInteractionItem::SetVariableValues(LPCTSTR pszVariable, CONST CStringArray &szValues)
{
	INT  nValue;
	INT  nValues;
	INT  nVariable;
	INT  nVariables;
	CString  szValueList;

	for (nValue = 0, nValues = (INT)szValues.GetSize(); nValue < nValues; nValue++)
	{
		szValueList += (nValue > 0) ? (TAB + szValues.GetAt(nValue)) : szValues.GetAt(nValue);
		continue;
	}
	for (nVariable = 0, nVariables = (INT)m_szVariables.GetSize(); nVariable < nVariables; nVariable++)
	{
		if (!m_szVariables.GetAt(nVariable).Compare(pszVariable))
		{
			m_szValues.SetAtGrow(nVariable, szValueList);
			continue;
		}
	}
}

INT CTCProcedureDocumentUserInteractionItem::GetVariableValues(LPCTSTR pszVariable, CStringArray &szValues) CONST
{
	INT  nPos;
	INT  nVariable;
	INT  nVariables;
	CString  szValueList;

	for (nVariable = 0, nVariables = (INT)m_szVariables.GetSize(); nVariable < nVariables; nVariable++)
	{
		if (!m_szVariables.GetAt(nVariable).Compare(pszVariable)) break;
		continue;
	}
	for (szValueList = (nVariable < nVariables && nVariable < m_szValues.GetSize()) ? m_szValues.GetAt(nVariable) : EMPTYSTRING, szValues.RemoveAll(); !szValueList.IsEmpty(); szValueList = szValueList.Mid(nPos + 1))
	{
		if ((nPos = szValueList.Find(TAB)) < 0)
		{
			szValues.Add(szValueList);
			break;
		}
		szValues.Add(szValueList.Left(nPos));
	}
	return((INT)szValues.GetSize());
}

BOOL CTCProcedureDocumentUserInteractionItem::CanActivate() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentUserInteractionItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCProcedureDocumentUserInteractionItem::MapProperties(CByteArray &nData) CONST
{
	INT  cbData;
	INT  nValue;
	INT  nValues;
	INT  nVariable;
	INT  nVariables;
	CByteArray  nValuesData;
	CByteArray  nVariablesData;
	DATA  sData = { 0 };

	for (nVariable = 0, nVariables = (INT)m_szVariables.GetSize(), sData.cbVariables = 0; nVariable < nVariables; nVariable++)
	{
		nVariablesData.SetSize(sData.cbVariables + (cbData = (m_szVariables.GetAt(nVariable).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nVariablesData.GetData() + sData.cbVariables, (LPCTSTR)m_szVariables.GetAt(nVariable), cbData);
		sData.cbVariables += cbData;
	}
	for (nValue = 0, nValues = nVariables, sData.cbValues = 0; nValue < nValues; nValue++)
	{
		nValuesData.SetSize(sData.cbValues + (cbData = (nValue < m_szValues.GetSize()) ? ((m_szValues.GetAt(nValue).GetLength() + 1)*sizeof(TCHAR)) : sizeof(TCHAR)));
		CopyMemory(nValuesData.GetData() + sData.cbValues, (nValue < m_szValues.GetSize()) ? (LPCTSTR)m_szValues.GetAt(nValue) : EMPTYSTRING, cbData);
		sData.cbValues += cbData;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + (sData.cbMessage = (m_szMessage.GetLength() + 1)*sizeof(TCHAR)) + sData.cbVariables + sData.cbValues)), sData.nType = m_nType, sData.nAction = m_nAction; nData.GetSize() == sData.cbSize; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szMessage, sData.cbMessage);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbMessage), nVariablesData.GetData(), sData.cbVariables);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbVariables), nValuesData.GetData(), sData.cbValues);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureDocumentUserInteractionItem::UnmapProperties(CONST CByteArray &nData)
{
	INT  cbData;
	INT  cbValue;
	INT  cbValues;
	INT  cbVariable;
	INT  cbVariables;
	CByteArray  nValuesData;
	CByteArray  nVariablesData;
	DATA  sData = { 0 };

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbMessage + sData.cbVariables + sData.cbValues && sData.cbMessage > 0 && sData.cbVariables >= 0 && sData.cbValues >= 0 && sData.nType == m_nType; )
	{
		for (nVariablesData.SetSize(sData.cbVariables), nValuesData.SetSize(sData.cbValues), CopyMemory(m_szMessage.GetBufferSetLength(STRINGCHARS(sData.cbMessage)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbMessage)), CopyMemory(nVariablesData.GetData(), nData.GetData() + (cbData = cbData + sData.cbMessage), sData.cbVariables), CopyMemory(nValuesData.GetData(), nData.GetData() + (cbData = cbData + sData.cbVariables), sData.cbValues), m_nAction = sData.nAction, m_szMessage.ReleaseBuffer(), m_szVariables.RemoveAll(), m_szValues.RemoveAll(), cbVariable = cbVariables = 0; cbVariables < nVariablesData.GetSize(); cbVariables += (cbVariable = (m_szVariables.GetAt(m_szVariables.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szVariables.Add((LPCTSTR)(nVariablesData.GetData() + cbVariables));
			continue;
		}
		for (cbValue = cbValues = 0; cbValues < nValuesData.GetSize(); cbValues += (cbValue = (m_szValues.GetAt(m_szValues.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szValues.Add((LPCTSTR)(nValuesData.GetData() + cbValues));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureDocumentUserInteractionItem::DrawLabels(CDC *pDC)
{
	CRect  rLabel;

	for (CalcLayoutPositions(rLabel); !m_nSubThreadID; )
	{
		DrawLabelSymbol(pDC, rLabel, m_szLabel);
		break;
	}
}

CRect CTCProcedureDocumentUserInteractionItem::CalcLayoutPositions(CRect &rLabel) CONST
{
	CRect  rContents;

	rContents.SetRect(m_rPosition.left, m_rPosition.top, m_rPosition.left + m_sizeSymbol[0].cx / 2 + TCPROCEDUREDOCUMENT_DEFAULT_STEPCONTENTSINDENT, m_rPosition.bottom);
	rLabel.SetRect(m_rPosition.left + m_sizeSymbol[0].cx + TCPROCEDUREDOCUMENT_DEFAULT_STEPLABELHORZINDENT, m_rPosition.top, rContents.right, m_rPosition.top + m_sizeSymbol[0].cy);
	return rContents;
}

BEGIN_MESSAGE_MAP(CTCProcedureDocumentUserInteractionItem, CTCProcedureDocumentItem)
	//{{AFX_MSG_MAP(CTCProcedureDocumentUserInteractionItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentUserInteractionItem commands
#endif  // TCP_DLL


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureDialog, CLocaleDialog)

HGLOBAL CTCProcedureDialog::LoadLocaleDialogTemplate(UINT nDialogID) CONST
{
	return LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID));
}
HGLOBAL CTCProcedureDialog::LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST
{
	HMODULE  hModule;
	HRSRC  hDialogTemplate;

	return(((hDialogTemplate = FindResourceEx((hModule = GetLibraryModuleInstance()), RT_DIALOG, pszDialogName, GetLanguageID())) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hDialogTemplate) : (LPVOID)NULL);
}

BOOL CALLBACK CTCProcedureDialog::EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	DWORD  dwThreadID[2];
	DWORD  dwProcessID[2];

	for (dwThreadID[0] = GetWindowThreadProcessId(AfxGetMainWnd()->GetSafeHwnd(), &dwProcessID[0]), dwThreadID[1] = GetWindowThreadProcessId(hWnd, &dwProcessID[1]); dwProcessID[0] == dwProcessID[1] && dwThreadID[0] != dwThreadID[1] && hWnd != (HWND)lParam; )
	{
		::SetForegroundWindow(hWnd);
		return FALSE;
	}
	return TRUE;
}

void CTCProcedureDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProcedureDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCProcedureDialog)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDialog message handlers

void CTCProcedureDialog::OnDestroy()
{
	EnumWindows(EnumWindowsProc, (LPARAM)GetSafeHwnd());
	CLocaleDialog::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureStepAuthorizationDialog, CTCProcedureDialog)

CTCProcedureStepAuthorizationDialog::CTCProcedureStepAuthorizationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureStepAuthorizationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureStepAuthorizationDialog::DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization)
{
	for (m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tAuthorization = tAuthorization; TRUE; )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return IDOK;
		break;
	}
	return IDCANCEL;
}

void CTCProcedureStepAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureStepAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProcedureStepAuthorizationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureStepAuthorizationDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationDialog message handlers

BOOL CTCProcedureStepAuthorizationDialog::OnInitDialog()
{
	CString  szStep[2];
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_DESCRIPTION)->GetWindowText(szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_COMMENTS)->GetWindowText(szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_TYPE)->SetWindowText(m_szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_DESCRIPTION)->SetWindowText((m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0]));
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_COMMENTS)->SetWindowText((m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1]));
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_TIME)->SetWindowText(m_tAuthorization.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_USERNAME)->SetWindowText(GetAccountUserName());
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_USERNAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_USERNAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_PASSWORD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_PASSWORD)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow();
	return TRUE;
}

void CTCProcedureStepAuthorizationDialog::OnOK()
{
	INT  nAccount;
	INT  nAccounts;
	CString  szUserName;
	CString  szPassword;
	CUserAccounts  cUserAccounts;
	CAccountToken  *pAccountToken;
	CAccountTokens  pAccountTokens;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_USERNAME)->GetWindowText(szUserName);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_PASSWORD)->GetWindowText(szPassword);
	for (nAccount = 0, nAccounts = cUserAccounts.EnumAccounts(pAccountTokens); nAccount < nAccounts; nAccount++)
	{
		if ((pAccountToken = pAccountTokens.GetAt(nAccount)) && pAccountToken->GetUserName() == szUserName  &&  pAccountToken->GetSpacecraftName() == GetAccountSpacecraftName())
		{
			if (pAccountToken->GetPassword() == szPassword) break;
			continue;
		}
	}
	if (nAccount == nAccounts)
	{
		GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_PASSWORD)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATION_AUTHORIZATION_PASSWORD)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CTCProcedureStepAuthorizationParametersCalibrationPage, CLocalePropertyPage)

CTCProcedureStepAuthorizationParametersCalibrationPage::CTCProcedureStepAuthorizationParametersCalibrationPage() : CLocalePropertyPage()
{
	m_psp.dwFlags |= PSP_DLGINDIRECT;
	m_psp.pResource = (LPCDLGTEMPLATE)LoadLocalePropertyPageTemplate(MAKEINTRESOURCE(CTCProcedureStepAuthorizationParametersCalibrationPage::IDD));
}

VOID CTCProcedureStepAuthorizationParametersCalibrationPage::ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	CString  szName;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	for (SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), m_pDatabase = pDatabase, m_szCalTableIDs.RemoveAll(); pDatabaseTCParameter != (CONST CDatabaseTCParameter *) NULL; )
	{
		if ((m_nCalTableType = (pDatabaseTCParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))) == TCPARAMETER_CALIBRATION_NUMERICAL)
		{
			if ((pDatabaseTCNumCalTable = m_pDatabase->GetTCNumCalTables()->GetAt(m_pDatabase->GetTCNumCalTables()->Find(pDatabaseTCParameter->GetCalTable()))))
			{
				for (szName.Format(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTCNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTCNumCalTable->GetName()); pDatabaseTCNumCalTable->GetDescription().IsEmpty(); )
				{
					szName = pDatabaseTCNumCalTable->GetDescription();
					break;
				}
				SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_szCalTableIDs.Add(pDatabaseTCNumCalTable->GetName());
			}
		}
		if (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((pDatabaseTCTxtCalTable = m_pDatabase->GetTCTxtCalTables()->GetAt(m_pDatabase->GetTCTxtCalTables()->Find(pDatabaseTCParameter->GetCalTable()))))
			{
				for (szName.Format(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTCTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTCTxtCalTable->GetName()); pDatabaseTCTxtCalTable->GetDescription().IsEmpty(); )
				{
					szName = pDatabaseTCTxtCalTable->GetDescription();
					break;
				}
				SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_szCalTableIDs.Add(pDatabaseTCTxtCalTable->GetName());
			}
		}
		break;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CTCProcedureStepAuthorizationParametersCalibrationPage::ShowCalibrationInfo()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	double  fCalPtX;
	double  fCalPtY;
	CString  szItem;
	CString  szCalPtX;
	CString  szCalPtY;
	CString  szCalText;
	CStringTools  cStringTools;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCNumCalPoint  *pDatabaseTCNumCalPoint;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pDatabaseTCTxtCalPoint;

	SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0)
	{
		if ((pDatabaseTCNumCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_NUMERICAL) ? m_pDatabase->GetTCNumCalTables()->GetAt(m_pDatabase->GetTCNumCalTables()->Find(m_szCalTableIDs.GetAt(nIndex))) : (CDatabaseTCNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTCNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCNumCalPoint = pDatabaseTCNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTCNumCalPoint->GetX(), -1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTCNumCalPoint->GetY(), -1);
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTCNumCalTable->GetName());
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
		if ((pDatabaseTCTxtCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_STATUS) ? m_pDatabase->GetTCTxtCalTables()->GetAt(m_pDatabase->GetTCTxtCalTables()->Find(m_szCalTableIDs.GetAt(nIndex))) : (CDatabaseTCTxtCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTCTxtCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCTxtCalPoint = pDatabaseTCTxtCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTCTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTCTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTCTxtCalTable->GetName());
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

BOOL CTCProcedureStepAuthorizationParametersCalibrationPage::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X)));
	szY = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y)));
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CTCProcedureStepAuthorizationParametersFolder *CTCProcedureStepAuthorizationParametersCalibrationPage::GetParent() CONST
{
	return((CTCProcedureStepAuthorizationParametersFolder *)CLocalePropertyPage::GetParent());
}

INT CTCProcedureStepAuthorizationParametersCalibrationPage::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

HGLOBAL CTCProcedureStepAuthorizationParametersCalibrationPage::LoadLocalePropertyPageTemplate(UINT nPropertyPageID) CONST
{
	return LoadLocalePropertyPageTemplate(MAKEINTRESOURCE(nPropertyPageID));
}
HGLOBAL CTCProcedureStepAuthorizationParametersCalibrationPage::LoadLocalePropertyPageTemplate(LPCTSTR pszPropertyPageName) CONST
{
	HMODULE  hModule;
	HRSRC  hPropertyPageTemplate;

	return(((hPropertyPageTemplate = FindResourceEx((hModule = GetLibraryModuleInstance()), RT_DIALOG, pszPropertyPageName, GetLanguageID())) || (hPropertyPageTemplate = FindResourceEx(hModule, RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hPropertyPageTemplate = FindResourceEx(hModule, RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hPropertyPageTemplate) : (LPVOID)NULL);
}

void CTCProcedureStepAuthorizationParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureStepAuthorizationParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureStepAuthorizationParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_szCalTableIDs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureStepAuthorizationParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCProcedureStepAuthorizationParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersCalibrationPage message handlers

BOOL CTCProcedureStepAuthorizationParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5; nColumn < nColumns; nWidth = (++nColumn > 0) ? (2 * (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

BOOL CTCProcedureStepAuthorizationParametersCalibrationPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szX;
	CString  szY;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_CALIBRATIONPAGE_POINTS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			if (GetSelectedCalibrationPoint(szX, szY))
			{
				GetParent()->GetParent()->SetSelectedCalibrationPoint(szX, szY);
				GetParent()->GetParent()->EndDialog(IDOK);
				return TRUE;
			}
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureStepAuthorizationParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CTCProcedureStepAuthorizationParametersFolderTabCtrl, CTabCtrl)

CTCProcedureStepAuthorizationParametersFolder *CTCProcedureStepAuthorizationParametersFolderTabCtrl::GetParent() CONST
{
	return((CTCProcedureStepAuthorizationParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CTCProcedureStepAuthorizationParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCProcedureStepAuthorizationParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersFolderTabCtrl message handlers

UINT CTCProcedureStepAuthorizationParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CTCProcedureStepAuthorizationParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd  *pWnd;

	if (nChar == VK_TAB)
	{
		if ((pWnd = GetParent()->GetParent()->GetNextDlgTabItem(GetParent(), (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	if (nChar == VK_DOWN)
	{
		if ((pWnd = GetParent()->GetActivePage()->GetNextDlgTabItem((CWnd *)NULL)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersFolder

IMPLEMENT_DYNCREATE(CTCProcedureStepAuthorizationParametersFolder, CLocalePropertySheetDialog)

CTCProcedureStepAuthorizationParametersFolder::CTCProcedureStepAuthorizationParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CTCProcedureStepAuthorizationParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	INT  nPage;

	if (CLocalePropertySheetDialog::Create(pParentWnd, WS_CHILD | WS_TABSTOP | WS_DISABLED))
	{
		for (nPage = GetPageCount() - 1, m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage >= 0; nPage--)
		{
			SetActivePage(nPage);
			continue;
		}
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		ShowWindow(SW_SHOWNORMAL);
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureStepAuthorizationParametersFolder::ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	m_pageCalibration.ShowParameterInfo(pDatabase, pDatabaseTCParameter);
}

BOOL CTCProcedureStepAuthorizationParametersFolder::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	return m_pageCalibration.GetSelectedCalibrationPoint(szX, szY);
}

CTCProcedureStepAuthorizationParametersDialog *CTCProcedureStepAuthorizationParametersFolder::GetParent() CONST
{
	return((CTCProcedureStepAuthorizationParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

BEGIN_MESSAGE_MAP(CTCProcedureStepAuthorizationParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CTCProcedureStepAuthorizationParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersFolder message handlers

void CTCProcedureStepAuthorizationParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureStepAuthorizationParametersDialog, CTCProcedureDialog)

CTCProcedureStepAuthorizationParametersDialog::CTCProcedureStepAuthorizationParametersDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureStepAuthorizationParametersDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureStepAuthorizationParametersDialog::DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszParameter, CString &szValue)
{
	INT  nResult;
	CString  szX;
	CString  szY;

	for (m_pDatabase = pDatabase, m_szParameter = pszParameter, szValue.Empty(); (nResult = (INT)CTCProcedureDialog::DoModal()) == IDOK; )
	{
		szValue = (GetSelectedCalibrationPoint(szX, szY)) ? szY : EMPTYSTRING;
		break;
	}
	return nResult;
}

VOID CTCProcedureStepAuthorizationParametersDialog::SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY)
{
	m_szX = pszX;
	m_szY = pszY;
}

BOOL CTCProcedureStepAuthorizationParametersDialog::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = m_szX;
	szY = m_szY;
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CTCProcedureSetParametersAuthorizationDialog *CTCProcedureStepAuthorizationParametersDialog::GetParent() CONST
{
	return((CTCProcedureSetParametersAuthorizationDialog *)CTCProcedureDialog::GetParent());
}

BOOL CTCProcedureStepAuthorizationParametersDialog::EnumParameters()
{
	CString  szParameter;
	CDatabaseTCParameter  *pParameter;

	if ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(m_szParameter))))
	{
		if (pParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))
		{
			szParameter.Format(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERSDIALOG_FORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
			SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	szParameter.Format(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERSDIALOG_FORMAT), (LPCTSTR)m_szParameter, EMPTYSTRING);
	SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter), 0));
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCProcedureStepAuthorizationParametersDialog::ShowParameterInfo()
{
	CString  szParameter[2];
	CDatabaseTCParameter  *pParameter;

	for (GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM)->GetWindowText(szParameter[0]), szParameter[1].Format(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONPARAMETERSDIALOG_FORMAT), EMPTYSTRING, EMPTYSTRING), szParameter[0] = (szParameter[0].Find(szParameter[1]) >= 0) ? szParameter[0].Left(szParameter[0].Find(szParameter[1])) : szParameter[0]; (pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(szParameter[0]))); )
	{
		m_wndFolderCtrl.ShowParameterInfo(m_pDatabase, pParameter);
		return;
	}
	m_wndFolderCtrl.ShowParameterInfo(m_pDatabase);
}

CRect CTCProcedureStepAuthorizationParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CTCProcedureStepAuthorizationParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureStepAuthorizationParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProcedureStepAuthorizationParametersDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureStepAuthorizationParametersDialog)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStepAuthorizationParametersDialog message handlers

BOOL CTCProcedureStepAuthorizationParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	if (m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_TCPROCEDURESTEPAUTHORIZATIONPARAMETERS_FOLDER - 1)))
	{
		for (; EnumParameters(); )
		{
			ShowParameterInfo();
			break;
		}
	}
	return TRUE;
}

void CTCProcedureStepAuthorizationParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

void CTCProcedureStepAuthorizationParametersDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_wndFolderCtrl.GetSelectedCalibrationPoint(m_szX, m_szY);
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetArgumentsAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureSetArgumentsAuthorizationDialog, CTCProcedureDialog)

CTCProcedureSetArgumentsAuthorizationDialog::CTCProcedureSetArgumentsAuthorizationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureSetArgumentsAuthorizationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureSetArgumentsAuthorizationDialog::DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CONST CStringArray &szArguments, CONST CLongUIntArray &nArgumentAttributes, CONST CPtrArray &pArguments)
{
	for (m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tAuthorization = tAuthorization, m_szArguments.Copy(szArguments), m_nArgumentAttributes.Copy(nArgumentAttributes), m_pArguments.Copy(pArguments); TRUE; )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return IDOK;
		break;
	}
	return IDCANCEL;
}

VOID CTCProcedureSetArgumentsAuthorizationDialog::EnumArguments()
{
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	double  fValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	TIMETAG  tValue;
	CString  *pValue;
	CString  szItem;
	CStringTools  cStringTools;

	for (nArgument = 0, nArguments = (INT)m_szArguments.GetSize(); nArgument < nArguments; nArgument++)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
		{
			for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME); )
			{
				szItem = m_szArguments.GetAt(nArgument);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE); )
			{
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CALIBRATION_NONE) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_RAW) : EMPTYSTRING;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_NUMERICAL) : szItem;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_STATUS) : szItem;
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_CODING); )
			{
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_BITPATTERN) : EMPTYSTRING;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_SIGNEDINTEGER) : szItem;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_UNSIGNEDINTEGER) : szItem;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_FLOATINGPOINT) : szItem;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_DATETIME) : szItem;
				szItem = ((m_nArgumentAttributes.GetAt(nArgument) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? ((m_nArgumentAttributes.GetAt(nArgument) & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) ? ((m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_BITPATTERN)) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_STRING)) : szItem;
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_RADIX); )
			{
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_BINARY) : EMPTYSTRING;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_OCTAL) : szItem;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_DECIMAL) : szItem;
				szItem = (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_HEXADECIMAL) : szItem;
				break;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))
			{
				if (((m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_BITPATTERN) || (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
				{
					for (CopyMemory(&uValue, m_pArguments.GetAt(nArgument), sizeof(uValue)); m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_BINARY; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 2);
						break;
					}
					for (; m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_OCTAL; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 8);
						break;
					}
					for (; m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_RADIX_HEXADECIMAL; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 16);
						break;
					}
					for (; (m_nArgumentAttributes.GetAt(nArgument) & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 10);
						break;
					}
				}
				if ((m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
				{
					if (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_SIGNEDINTEGER)
					{
						CopyMemory(&nValue, m_pArguments.GetAt(nArgument), sizeof(nValue));
						szItem = cStringTools.ConvertLongIntToString(nValue);
					}
					if (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_FLOATINGPOINT)
					{
						CopyMemory(&fValue, m_pArguments.GetAt(nArgument), sizeof(fValue));
						szItem = cStringTools.ConvertFloatToString(fValue);
					}
					if (m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CODING_TIME)
					{
						CopyMemory(&tValue, m_pArguments.GetAt(nArgument), sizeof(tValue));
						szItem = CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME));
					}
				}
				if ((m_nArgumentAttributes.GetAt(nArgument) & TCPARAMETER_CALIBRATION_STATUS) || (m_nArgumentAttributes.GetAt(nArgument) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) szItem = ((pValue = (CString *)m_pArguments.GetAt(nArgument))) ? (LPCTSTR)(*pValue) : EMPTYSTRING;
				m_szArgumentValues.InsertAt(nArgument, szItem);
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), nArgument, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), nArgument, nColumn, szItem);
		}
	}
	if (SendDlgItemMessage(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST, LVM_GETITEMCOUNT) > 0)
	{
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), 0);
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)->EnableWindow();
		ShowArgumentDetails();
		return;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)->EnableWindow(FALSE);
	ShowArgumentDetails();
}

VOID CTCProcedureSetArgumentsAuthorizationDialog::ShowArgumentDetails()
{
	INT  nIndex;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST))) >= 0)
	{
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE)->SetWindowText(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))));
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE)->EnableWindow();
	}
	else
	{
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow(FALSE);
}

INT CTCProcedureSetArgumentsAuthorizationDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProcedureSetArgumentsAuthorizationDialog::IsModified() CONST
{
	INT  nArgument;
	INT  nArguments;

	for (nArgument = 0, nArguments = (INT)m_szArguments.GetSize(); nArgument < nArguments; nArgument++)
	{
		if (Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))) != m_szArgumentValues.GetAt(nArgument)) break;
		continue;
	}
	return((nArgument < nArguments) ? TRUE : FALSE);
}

void CTCProcedureSetArgumentsAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureSetArgumentsAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureSetArgumentsAuthorizationDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pArguments.RemoveAll();
	m_szArguments.RemoveAll();
	m_szArgumentValues.RemoveAll();
	m_nArgumentAttributes.RemoveAll();
	CTCProcedureDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureSetArgumentsAuthorizationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureSetArgumentsAuthorizationDialog)
	ON_BN_CLICKED(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_SET, OnSetValue)
	ON_BN_CLICKED(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ACKNOWLEDGE, OnAcknowledge)
	ON_EN_CHANGE(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE, OnEditchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetArgumentsAuthorizationDialog message handlers

BOOL CTCProcedureSetArgumentsAuthorizationDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CString  szStep[2];
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE)) ? (rColumns.Width() / 7) : (9 * rColumns.Width() / 35)));
		continue;
	}
	EnumArguments();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DESCRIPTION)->GetWindowText(szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_COMMENTS)->GetWindowText(szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TYPE)->SetWindowText(m_szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DESCRIPTION)->SetWindowText((m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0]));
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_COMMENTS)->SetWindowText((m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1]));
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TIME)->SetWindowText(m_tAuthorization.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ACKNOWLEDGE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ACKNOWLEDGE)->SetFocus();
	return FALSE;
}

BOOL CTCProcedureSetArgumentsAuthorizationDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowArgumentDetails();
	}
	return CTCProcedureDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureSetArgumentsAuthorizationDialog::OnSetValue()
{
	INT  nIndex;
	TIMETAG  tValue;
	CString  szValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE)->GetWindowText(szValue); (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST))) >= 0; )
	{
		if ((((nAttributes = m_nArgumentAttributes.GetAt(nIndex)) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 2);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 2);
			}
			if (nAttributes & TCPARAMETER_RADIX_OCTAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 8);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 8);
			}
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 16);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 16);
			}
			for (; (nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0; )
			{
				szValue = cStringTools.ConvertLongUIntToString(CDatabaseEngine::ParseValue(szValue, 10));
				break;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), szValue);
			break;
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = cStringTools.ConvertLongIntToString(CDatabaseEngine::ParseValue(szValue, 10))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = cStringTools.ConvertFloatToString(CDatabaseEngine::ParseValue(szValue))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_TIME)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)) : EMPTYSTRING));
				break;
			}
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
		{
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), szValue);
			break;
		}
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureSetArgumentsAuthorizationDialog::OnEditchangeValue()
{
	CString  szValue;

	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE)->GetWindowText(szValue);
	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))) != szValue  &&  !szValue.IsEmpty()) ? TRUE : FALSE);
}

void CTCProcedureSetArgumentsAuthorizationDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnOK();
}

void CTCProcedureSetArgumentsAuthorizationDialog::OnOK()
{
	INT  nArgument;
	INT  nArguments;
	double  fValue;
	TIMETAG  tValue;
	CString  szValue;
	CString  *pValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCPROCEDURESETARGUMENTSAUTHORIZATION_ARGUMENTS_VALUE)->GetWindowText(szValue);
	for (nArgument = 0, nArguments = (INT)m_szArguments.GetSize(); nArgument < nArguments; nArgument++)
	{
		if ((((nAttributes = m_nArgumentAttributes.GetAt(nArgument)) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY) uValue = CDatabaseEngine::ParseValue(szValue, 2);
			if (nAttributes & TCPARAMETER_RADIX_OCTAL) uValue = CDatabaseEngine::ParseValue(szValue, 8);
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) uValue = CDatabaseEngine::ParseValue(szValue, 16);
			if ((nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) uValue = CDatabaseEngine::ParseValue(szValue, 10);
			CopyMemory(m_pArguments.GetAt(nArgument), &uValue, sizeof(uValue));
			continue;
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
			{
				CopyMemory(m_pArguments.GetAt(nArgument), &(nValue = CDatabaseEngine::ParseValue(szValue, 10)), sizeof(nValue));
				continue;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				CopyMemory(m_pArguments.GetAt(nArgument), &(fValue = CDatabaseEngine::ParseValue(szValue)), sizeof(fValue));
				continue;
			}
			if (nAttributes & TCPARAMETER_CODING_TIME)
			{
				CopyMemory(m_pArguments.GetAt(nArgument), &(tValue = CDatabaseEngine::ParseTime(szValue)), sizeof(tValue));
				continue;
			}
		}
		if ((pValue = ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? (CString *)m_pArguments.GetAt(nArgument) : (CString *)NULL))
		{
			*pValue = szValue;
			continue;
		}
	}
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetVariablesAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureSetVariablesAuthorizationDialog, CTCProcedureDialog)

CTCProcedureSetVariablesAuthorizationDialog::CTCProcedureSetVariablesAuthorizationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureSetVariablesAuthorizationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureSetVariablesAuthorizationDialog::DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CONST CStringArray &szVariables, CONST CLongUIntArray &nVariableAttributes, CONST CPtrArray &pVariables)
{
	for (m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tAuthorization = tAuthorization, m_szVariables.Copy(szVariables), m_nVariableAttributes.Copy(nVariableAttributes), m_pVariables.Copy(pVariables); TRUE; )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return IDOK;
		break;
	}
	return IDCANCEL;
}

VOID CTCProcedureSetVariablesAuthorizationDialog::EnumVariables()
{
	INT  nColumn;
	INT  nColumns;
	INT  nVariable;
	INT  nVariables;
	double  fValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	TIMETAG  tValue;
	CString  *pValue;
	CString  szItem;
	CStringTools  cStringTools;

	for (nVariable = 0, nVariables = (INT)m_szVariables.GetSize(); nVariable < nVariables; nVariable++)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
		{
			for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_NAME); )
			{
				szItem = m_szVariables.GetAt(nVariable);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_TYPE); )
			{
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CALIBRATION_NONE) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTYPE_RAW) : EMPTYSTRING;
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_CODING); )
			{
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_BITPATTERN) : EMPTYSTRING;
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_SIGNEDINTEGER) : szItem;
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_UNSIGNEDINTEGER) : szItem;
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_FLOATINGPOINT) : szItem;
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_DATETIME) : szItem;
				szItem = ((m_nVariableAttributes.GetAt(nVariable) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? ((m_nVariableAttributes.GetAt(nVariable) & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) ? ((m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_BITPATTERN)) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESCODING_STRING)) : szItem;
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_RADIX); )
			{
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESRADIX_BINARY) : EMPTYSTRING;
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESRADIX_OCTAL) : szItem;
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESRADIX_DECIMAL) : szItem;
				szItem = (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESRADIX_HEXADECIMAL) : szItem;
				break;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE))
			{
				if (((m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_BITPATTERN) || (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
				{
					for (CopyMemory(&uValue, m_pVariables.GetAt(nVariable), sizeof(uValue)); m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_BINARY; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 2);
						break;
					}
					for (; m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_OCTAL; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 8);
						break;
					}
					for (; m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_RADIX_HEXADECIMAL; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 16);
						break;
					}
					for (; (m_nVariableAttributes.GetAt(nVariable) & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 10);
						break;
					}
				}
				if ((m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
				{
					if (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_SIGNEDINTEGER)
					{
						CopyMemory(&nValue, m_pVariables.GetAt(nVariable), sizeof(nValue));
						szItem = cStringTools.ConvertLongIntToString(nValue);
					}
					if (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_FLOATINGPOINT)
					{
						CopyMemory(&fValue, m_pVariables.GetAt(nVariable), sizeof(fValue));
						szItem = cStringTools.ConvertFloatToString(fValue);
					}
					if (m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CODING_TIME)
					{
						CopyMemory(&tValue, m_pVariables.GetAt(nVariable), sizeof(tValue));
						szItem = CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME));
					}
				}
				if ((m_nVariableAttributes.GetAt(nVariable) & TCPARAMETER_CALIBRATION_STATUS) || (m_nVariableAttributes.GetAt(nVariable) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) szItem = ((pValue = (CString *)m_pVariables.GetAt(nVariable))) ? (LPCTSTR)(*pValue) : EMPTYSTRING;
				m_szVariableValues.InsertAt(nVariable, szItem);
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), nVariable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), nVariable, nColumn, szItem);
		}
	}
	if (SendDlgItemMessage(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST, LVM_GETITEMCOUNT) > 0)
	{
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), 0);
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)->EnableWindow();
		ShowVariableDetails();
		return;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)->EnableWindow(FALSE);
	ShowVariableDetails();
}

VOID CTCProcedureSetVariablesAuthorizationDialog::ShowVariableDetails()
{
	INT  nIndex;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST))) >= 0)
	{
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE)->SetWindowText(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE))));
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE)->EnableWindow();
	}
	else
	{
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_SET)->EnableWindow(FALSE);
}

INT CTCProcedureSetVariablesAuthorizationDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProcedureSetVariablesAuthorizationDialog::IsModified() CONST
{
	INT  nVariable;
	INT  nVariables;

	for (nVariable = 0, nVariables = (INT)m_szVariables.GetSize(); nVariable < nVariables; nVariable++)
	{
		if (Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), nVariable, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE))) != m_szVariableValues.GetAt(nVariable)) break;
		continue;
	}
	return((nVariable < nVariables) ? TRUE : FALSE);
}

void CTCProcedureSetVariablesAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureSetVariablesAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureSetVariablesAuthorizationDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pVariables.RemoveAll();
	m_szVariables.RemoveAll();
	m_szVariableValues.RemoveAll();
	m_nVariableAttributes.RemoveAll();
	CTCProcedureDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureSetVariablesAuthorizationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureSetVariablesAuthorizationDialog)
	ON_BN_CLICKED(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_SET, OnSetValue)
	ON_BN_CLICKED(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_ACKNOWLEDGE, OnAcknowledge)
	ON_EN_CHANGE(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE, OnEditchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetVariablesAuthorizationDialog message handlers

BOOL CTCProcedureSetVariablesAuthorizationDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CString  szStep[2];
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_NAME)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_TYPE)) ? (rColumns.Width() / 7) : (9 * rColumns.Width() / 35)));
		continue;
	}
	EnumVariables();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DESCRIPTION)->GetWindowText(szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_COMMENTS)->GetWindowText(szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TYPE)->SetWindowText(m_szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DESCRIPTION)->SetWindowText((m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0]));
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_COMMENTS)->SetWindowText((m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1]));
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TIME)->SetWindowText(m_tAuthorization.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_ACKNOWLEDGE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_ACKNOWLEDGE)->SetFocus();
	return FALSE;
}

BOOL CTCProcedureSetVariablesAuthorizationDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowVariableDetails();
	}
	return CTCProcedureDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureSetVariablesAuthorizationDialog::OnSetValue()
{
	INT  nIndex;
	TIMETAG  tValue;
	CString  szValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE)->GetWindowText(szValue); (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST))) >= 0; )
	{
		if ((((nAttributes = m_nVariableAttributes.GetAt(nIndex)) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 2);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 2);
			}
			if (nAttributes & TCPARAMETER_RADIX_OCTAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 8);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 8);
			}
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 16);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 16);
			}
			for (; (nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0; )
			{
				szValue = cStringTools.ConvertLongUIntToString(CDatabaseEngine::ParseValue(szValue, 10));
				break;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE)), szValue);
			break;
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE)), (szValue = cStringTools.ConvertLongIntToString(CDatabaseEngine::ParseValue(szValue, 10))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE)), (szValue = cStringTools.ConvertFloatToString(CDatabaseEngine::ParseValue(szValue))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_TIME)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE)), (szValue = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)) : EMPTYSTRING));
				break;
			}
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
		{
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE)), szValue);
			break;
		}
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureSetVariablesAuthorizationDialog::OnEditchangeValue()
{
	CString  szValue;

	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE)->GetWindowText(szValue);
	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE_SET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_VARIABLESTITLEITEM_VALUE))) != szValue  &&  !szValue.IsEmpty()) ? TRUE : FALSE);
}

void CTCProcedureSetVariablesAuthorizationDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnOK();
}

void CTCProcedureSetVariablesAuthorizationDialog::OnOK()
{
	INT  nVariable;
	INT  nVariables;
	double  fValue;
	TIMETAG  tValue;
	CString  szValue;
	CString  *pValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCPROCEDURESETVARIABLESAUTHORIZATION_VARIABLES_VALUE)->GetWindowText(szValue);
	for (nVariable = 0, nVariables = (INT)m_szVariables.GetSize(); nVariable < nVariables; nVariable++)
	{
		if ((((nAttributes = m_nVariableAttributes.GetAt(nVariable)) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY) uValue = CDatabaseEngine::ParseValue(szValue, 2);
			if (nAttributes & TCPARAMETER_RADIX_OCTAL) uValue = CDatabaseEngine::ParseValue(szValue, 8);
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) uValue = CDatabaseEngine::ParseValue(szValue, 16);
			if ((nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) uValue = CDatabaseEngine::ParseValue(szValue, 10);
			CopyMemory(m_pVariables.GetAt(nVariable), &uValue, sizeof(uValue));
			continue;
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
			{
				CopyMemory(m_pVariables.GetAt(nVariable), &(nValue = CDatabaseEngine::ParseValue(szValue, 10)), sizeof(nValue));
				continue;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				CopyMemory(m_pVariables.GetAt(nVariable), &(fValue = CDatabaseEngine::ParseValue(szValue)), sizeof(fValue));
				continue;
			}
			if (nAttributes & TCPARAMETER_CODING_TIME)
			{
				CopyMemory(m_pVariables.GetAt(nVariable), &(tValue = CDatabaseEngine::ParseTime(szValue)), sizeof(tValue));
				continue;
			}
		}
		if ((pValue = ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? (CString *)m_pVariables.GetAt(nVariable) : (CString *)NULL))
		{
			*pValue = szValue;
			continue;
		}
	}
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetParametersAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureSetParametersAuthorizationDialog, CTCProcedureDialog)

CTCProcedureSetParametersAuthorizationDialog::CTCProcedureSetParametersAuthorizationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureSetParametersAuthorizationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureSetParametersAuthorizationDialog::DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CONST CStringArray &szParameters, CONST CLongUIntArray &nParameterAttributes, CONST CPtrArray &pParameters, CTCEnvironment *pTCEnvironment)
{
	for (m_pDatabase = pDatabase, m_pTCEnvironment = pTCEnvironment, m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tAuthorization = tAuthorization, m_szParameters.Copy(szParameters), m_nParameterAttributes.Copy(nParameterAttributes), m_pParameters.Copy(pParameters); TRUE; )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return IDOK;
		break;
	}
	return IDCANCEL;
}

VOID CTCProcedureSetParametersAuthorizationDialog::EnumParameters()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	BOOL  bValue;
	CString  szItem;
	CString  szValue;
	CStringArray  szParameters;
	CTCParameter  *pTCParameter;

	for (nParameter = 0, nParameters = (INT)m_szParameters.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTCParameter = new CTCParameter) != (CTCParameter *)NULL)
		{
			pTCParameter->SetTag(m_szParameters.GetAt(nParameter));
			pTCParameter->SetAttributes(m_nParameterAttributes.GetAt(nParameter));
			if (m_pParameterValues[0].Add(pTCParameter) < 0)
			{
				m_nParameterAttributes.RemoveAt(nParameter);
				m_szParameters.RemoveAt(nParameter);
				m_pParameters.RemoveAt(nParameter);
				delete pTCParameter;
				nParameters--;
				nParameter--;
			}
		}
		if (nParameter == nParameters - 1)
		{
			m_pParameterValues[1].Copy(&m_pParameterValues[0]);
			m_pTCEnvironment->Initialize(m_pParameterValues[0]);
			m_pTCEnvironment->Initialize(m_pParameterValues[1]);
			continue;
		}
	}
	for (nParameter = 0; nParameter < nParameters; nParameter++)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			for (szItem.Empty(), bValue = FALSE; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG); )
			{
				szItem = m_szParameters.GetAt(nParameter);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE); )
			{
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CALIBRATION_NONE) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_RAW) : EMPTYSTRING;
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_NUMERICAL) : szItem;
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_STATUS) : szItem;
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_CODING); )
			{
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_BITPATTERN) : EMPTYSTRING;
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_SIGNEDINTEGER) : szItem;
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_UNSIGNEDINTEGER) : szItem;
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_FLOATINGPOINT) : szItem;
				szItem = (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_DATETIME) : szItem;
				szItem = ((m_nParameterAttributes.GetAt(nParameter) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? (((m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_RADIX_DECIMAL) || (m_nParameterAttributes.GetAt(nParameter) & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_BITPATTERN)) : szItem;
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_RADIX); )
			{
				if (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_RADIX_BINARY) szItem = STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_BINARY);
				if (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_RADIX_OCTAL) szItem = STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_OCTAL);
				if (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_RADIX_DECIMAL) szItem = STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_DECIMAL);
				if (m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_RADIX_HEXADECIMAL) szItem = STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_HEXADECIMAL);
				if (szItem.IsEmpty()) szItem = ((m_nParameterAttributes.GetAt(nParameter) & TCPARAMETER_CODING_BITPATTERN) != TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_DECIMAL) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_BINARY);
				break;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE))
			{
				if ((pTCParameter = m_pParameterValues[0].GetAt(m_pParameterValues[0].Find(m_szParameters.GetAt(nParameter)))))
				{
					szItem = (pTCParameter->GetValueAsText(m_pDatabase, 0, m_nParameterAttributes.GetAt(nParameter), (szValue = STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)), bValue)) ? szValue : EMPTYSTRING;
					szItem += (bValue) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUE_EXTRAPOLATED) : EMPTYSTRING;
				}
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), nParameter, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), nParameter, nColumn, szItem);
		}
	}
	if (SendDlgItemMessage(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST, LVM_GETITEMCOUNT) > 0)
	{
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), 0);
		GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)->EnableWindow();
		ShowParameterDetails();
		return;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)->EnableWindow(FALSE);
	ShowParameterDetails();
}

VOID CTCProcedureSetParametersAuthorizationDialog::ShowParameterDetails()
{
	Spinbox_SetPos(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE), TCPROCEDURESETPARAMETERSAUTHORIZATION_DEFAULTSAMPLE);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE)->SetWindowText(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE))));
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE)->EnableWindow();
}

INT CTCProcedureSetParametersAuthorizationDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProcedureSetParametersAuthorizationDialog::IsModified() CONST
{
	return !m_pParameterValues[0].Compare(&m_pParameterValues[1]);
}

void CTCProcedureSetParametersAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureSetParametersAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureSetParametersAuthorizationDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pParameters.RemoveAll();
	m_szParameters.RemoveAll();
	m_pParameterValues[0].RemoveAll();
	m_pParameterValues[1].RemoveAll();
	m_nParameterAttributes.RemoveAll();
	CTCProcedureDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureSetParametersAuthorizationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureSetParametersAuthorizationDialog)
	ON_BN_CLICKED(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_SET, OnSetValue)
	ON_BN_CLICKED(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_ACKNOWLEDGE, OnAcknowledge)
	ON_EN_CHANGE(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE, OnEditchangeValue)
	ON_CONTROL(SBXN_CHANGE, IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE, OnSpinchangeSample)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSetParametersAuthorizationDialog message handlers

BOOL CTCProcedureSetParametersAuthorizationDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CString  szStep[2];
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE));
	Spinbox_SetRange(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE), TCPROCEDURESETPARAMETERSAUTHORIZATION_MINIMUMSAMPLE, TCPROCEDURESETPARAMETERSAUTHORIZATION_MAXIMUMSAMPLE);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE)) ? (rColumns.Width() / 7) : (9 * rColumns.Width() / 35)));
		continue;
	}
	EnumParameters();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DESCRIPTION)->GetWindowText(szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_COMMENTS)->GetWindowText(szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TYPE)->SetWindowText(m_szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DESCRIPTION)->SetWindowText((m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0]));
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_COMMENTS)->SetWindowText((m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1]));
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TIME)->SetWindowText(m_tAuthorization.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_ACKNOWLEDGE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_ACKNOWLEDGE)->SetFocus();
	return FALSE;
}

BOOL CTCProcedureSetParametersAuthorizationDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szValue;
	CTCProcedureStepAuthorizationParametersDialog  cParametersDialog(this);
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		for (; pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED); )
		{
			ShowParameterDetails();
			break;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE))) != STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_RAW))
		{
			if (cParametersDialog.DoModal(m_pDatabase, Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG))), szValue) == IDOK  &&  !szValue.IsEmpty())
			{
				GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE))) != szValue || Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE)) > 0) ? TRUE : FALSE);
				GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE)->SetWindowText(szValue);
				SendDlgItemMessage(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE, EM_SETSEL, 0, -1);
				GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE)->SetFocus();
			}
		}
	}
	return CTCProcedureDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureSetParametersAuthorizationDialog::OnSetValue()
{
	INT  nIndex;
	INT  nPoint;
	INT  nPoints;
	INT  nSample;
	BOOL  bValue;
	BOOL  bTime;
	double  fX[2];
	double  fValue;
	double  fRawValue;
	CString  szY;
	CString  szTag;
	CString  szValue;
	CString  szFormat;
	CTimeTag  tValue;
	ULONGLONG  nAttributes;
	CTCParameter  *pTCParameter;
	CDatabaseTCParameter  *pParameter;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCNumCalPoint  *pDatabaseTCNumCalPoint[2];
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pDatabaseTCTxtCalPoint;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE)->GetWindowText(szValue), nSample = (INT)Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE)); (pTCParameter = m_pParameterValues[0].GetAt(m_pParameterValues[0].Find((szTag = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST))), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG))))))); )
	{
		if ((pTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) && (m_nParameterAttributes.GetAt(nIndex) & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_ENABLED | TCPARAMETER_VTYPE_CALIBRATED)))
		{
			if ((pDatabaseTCNumCalTable = ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag())))) ? m_pDatabase->GetTCNumCalTables()->GetAt((pParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCNumCalTables()->Find(pParameter->GetCalTable()) : pParameter->GetCalTableRef()) : (CDatabaseTCNumCalTable *)NULL))
			{
				for (nPoint = 0, nPoints = (INT)pDatabaseTCNumCalTable->GetSize() - 1, fValue = _tstof(szValue); nPoint < nPoints; nPoint++)
				{
					if ((pDatabaseTCNumCalPoint[0] = pDatabaseTCNumCalTable->GetAt(nPoint)))
					{
						if ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(nPoint + 1)))
						{
							if ((fValue >= pDatabaseTCNumCalPoint[0]->GetY() && fValue <= pDatabaseTCNumCalPoint[1]->GetY()) || (fValue <= pDatabaseTCNumCalPoint[0]->GetY() && fValue >= pDatabaseTCNumCalPoint[1]->GetY()))
							{
								fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX());
								break;
							}
						}
					}
				}
				if (nPoint < nPoints)
				{
					pTCParameter->SetRawValue(nSample, (pTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), fRawValue) : CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), (ULONGLONG)fRawValue), TCPARAMETER_STATUS_NONE);
					break;
				}
				if ((pTCParameter->GetAttributes() & TCPARAMETER_INTERPRETATION_FULL) == 0)
				{
					if ((pDatabaseTCNumCalPoint[0] = pDatabaseTCNumCalTable->GetAt(0)))
					{
						if ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(1)))
						{
							if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pParameter->GetWidth()))
							{
								pTCParameter->SetRawValue(nSample, (pTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), fRawValue) : CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), (ULONGLONG)fRawValue), TCPARAMETER_STATUS_NONE);
								break;
							}
							if ((pDatabaseTCNumCalPoint[0] = pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound() - 1)))
							{
								if ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound())))
								{
									if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pParameter->GetWidth()))
									{
										pTCParameter->SetRawValue(nSample, (pTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), fRawValue) : CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), (ULONGLONG)fRawValue), TCPARAMETER_STATUS_NONE);
										break;
									}
								}
							}
						}
					}
				}
				break;
			}
		}
		if ((pTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) && (m_nParameterAttributes.GetAt(nIndex) & (TCPARAMETER_CALIBRATION_STATUS | TCPARAMETER_CALIBRATION_ENABLED | TCPARAMETER_VTYPE_CALIBRATED)))
		{
			if ((pDatabaseTCTxtCalTable = ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag())))) ? m_pDatabase->GetTCTxtCalTables()->GetAt((pParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCTxtCalTables()->Find(pParameter->GetCalTable()) : pParameter->GetCalTableRef()) : (CDatabaseTCTxtCalTable *)NULL))
			{
				for (nPoint = 0, nPoints = (INT)pDatabaseTCTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
				{
					if ((pDatabaseTCTxtCalPoint = pDatabaseTCTxtCalTable->GetAt(nPoint)))
					{
						if ((pDatabaseTCTxtCalPoint->GetPoint(fX[0], szY) && szY == szValue) || (pDatabaseTCTxtCalPoint->GetRange(fX[0], fX[1], szY) && szY == szValue)) break;
						continue;
					}
				}
				if (nPoint < nPoints)
				{
					pTCParameter->SetRawValue(nSample, (pTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), fX[0]) : CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), (ULONGLONG)fX[0]), TCPARAMETER_STATUS_NONE);
					break;
				}
				break;
			}
		}
		for (fValue = _tstof(szValue), bTime = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? TRUE : FALSE; (pParameter = (((nAttributes = m_nParameterAttributes.GetAt(nIndex)) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_UNSIGNEDINTEGER))) ? m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag())) : (CDatabaseTCParameter *)NULL) && !bTime; )
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY) fValue = (double)CDatabaseEngine::ParseValue(szValue, 2);
			if (nAttributes & TCPARAMETER_RADIX_OCTAL) fValue = (double)CDatabaseEngine::ParseValue(szValue, 8);
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) fValue = (double)CDatabaseEngine::ParseValue(szValue, 16);
			pTCParameter->SetRawValue(nSample, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), nAttributes, pParameter->GetWidth(), (ULONGLONG)fValue), TCPARAMETER_STATUS_NONE);
			break;
		}
		if (!bTime)
		{
			if ((pParameter = (nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) ? m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag())) : (CDatabaseTCParameter *)NULL))
			{
				pTCParameter->SetRawValue(nSample, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), nAttributes, pParameter->GetWidth(), (ULONGLONG)fValue), TCPARAMETER_STATUS_NONE);
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				pTCParameter->SetRawValue(nSample, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), nAttributes, fValue), TCPARAMETER_STATUS_NONE);
				break;
			}
		}
		if ((nAttributes & TCPARAMETER_CODING_TIME) || bTime)
		{
			pTCParameter->SetRawValue(nSample, tValue, TCPARAMETER_STATUS_NONE);
			break;
		}
		break;
	}
	if ((pTCParameter = m_pParameterValues[0].GetAt(m_pParameterValues[0].Find(szTag))) && pTCParameter->GetValueAsText(m_pDatabase, 0, m_nParameterAttributes.GetAt(nIndex), (szValue = STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)), bValue)) Listview_SetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE)), (bValue) ? (szValue + STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUE_EXTRAPOLATED)) : szValue);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureSetParametersAuthorizationDialog::OnEditchangeValue()
{
	CString  szValue;

	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE)->GetWindowText(szValue);
	GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow(((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE))) != szValue || Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE)) > 0) && !szValue.IsEmpty()) ? TRUE : FALSE);
}

void CTCProcedureSetParametersAuthorizationDialog::OnSpinchangeSample()
{
	INT  nIndex;
	BOOL  bValue;
	CString  szValue;
	CTCParameter  *pTCParameter;

	if ((pTCParameter = m_pParameterValues[0].GetAt(m_pParameterValues[0].Find(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST), (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_LIST))), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG)))))))
	{
		GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE)->SetWindowText((pTCParameter->GetValueAsText(m_pDatabase, (INT)Spinbox_GetPos(GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_SAMPLE)), m_nParameterAttributes.GetAt(nIndex), (szValue = STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)), bValue)) ? ((bValue) ? (szValue + STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUE_EXTRAPOLATED)) : szValue) : EMPTYSTRING);
		GetDlgItem(IDC_TCPROCEDURESETPARAMETERSAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow(FALSE);
	}
}

void CTCProcedureSetParametersAuthorizationDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnOK();
}

void CTCProcedureSetParametersAuthorizationDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_pTCEnvironment->Update(m_pParameterValues[0]);
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureCallProcedureAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureCallProcedureAuthorizationDialog, CTCProcedureDialog)

CTCProcedureCallProcedureAuthorizationDialog::CTCProcedureCallProcedureAuthorizationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureCallProcedureAuthorizationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

CTCProcedureCallProcedureAuthorizationDialog::~CTCProcedureCallProcedureAuthorizationDialog()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)m_pArgumentStrings.GetSize(); nItem < nItems; nItem++)
	{
		GlobalFree(m_pArgumentStrings.GetAt(nItem));
		continue;
	}
	m_pArgumentStrings.RemoveAll();
}

INT CTCProcedureCallProcedureAuthorizationDialog::DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, LPCTSTR pszProcedure, va_list pArgumentList)
{
	for (m_pDatabase = pDatabase, m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tAuthorization = tAuthorization, m_szProcedure = pszProcedure, m_pArgumentList[0] = m_pArgumentList[1] = pArgumentList; TRUE; )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return IDOK;
		break;
	}
	return IDCANCEL;
}

VOID CTCProcedureCallProcedureAuthorizationDialog::EnumArguments()
{
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	double  fValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	TIMETAG  tValue;
	CString  szItem;
	CStringTools  cStringTools;
	CDatabaseTCProcedure  *pProcedure;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;

	if ((pProcedure = m_pDatabase->GetTCProcedures()->GetAt(m_pDatabase->GetTCProcedures()->Find(m_szProcedure))))
	{
		for (nArgument = 0, nArguments = pProcedure->GetArguments(m_pDatabaseTCProcedureArguments); nArgument < nArguments; nArgument++)
		{
			if ((pDatabaseTCProcedureArgument = m_pDatabaseTCProcedureArguments.GetAt(nArgument)))
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
				{
					for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME); )
					{
						szItem = pDatabaseTCProcedureArgument->GetTag();
						break;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE))
					{
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_RAW) : EMPTYSTRING;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_NUMERICAL) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_STATUS) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_CODING))
					{
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_BITPATTERN) : EMPTYSTRING;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_SIGNEDINTEGER) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_UNSIGNEDINTEGER) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_FLOATINGPOINT) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_DATETIME) : szItem;
						szItem = ((pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? ((pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) ? ((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_BITPATTERN)) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_STRING)) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_RADIX))
					{
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_BINARY) : EMPTYSTRING;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_OCTAL) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_DECIMAL) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_HEXADECIMAL) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))
					{
						if (((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
						{
							try
							{
								for (uValue = va_arg(m_pArgumentList[0], ULONGLONG); pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_BINARY; )
								{
									szItem = cStringTools.ConvertLongUIntToString(uValue, 2);
									break;
								}
								if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_OCTAL) szItem = cStringTools.ConvertLongUIntToString(uValue, 8);
								if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) szItem = cStringTools.ConvertLongUIntToString(uValue, 16);
								if ((pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) szItem = cStringTools.ConvertLongUIntToString(uValue, 10);
							}
							catch (...)
							{
								szItem.Empty();
							}
						}
						if ((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
						{
							if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER)
							{
								try
								{
									nValue = va_arg(m_pArgumentList[0], LONGLONG);
									szItem = cStringTools.ConvertLongIntToString(nValue);
								}
								catch (...)
								{
									szItem.Empty();
								}
							}
							if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT)
							{
								try
								{
									fValue = va_arg(m_pArgumentList[0], double);
									szItem = cStringTools.ConvertFloatToString(fValue);
								}
								catch (...)
								{
									szItem.Empty();
								}
							}
							if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_TIME)
							{
								try
								{
									tValue = va_arg(m_pArgumentList[0], TIMETAG);
									szItem = CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME));
								}
								catch (...)
								{
									szItem.Empty();
								}
							}
						}
						if ((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) || (pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
						{
							try
							{
								szItem = va_arg(m_pArgumentList[0], LPCTSTR);
							}
							catch (...)
							{
								szItem.Empty();
							}
						}
						m_szArgumentValues.InsertAt(nArgument, szItem);
					}
					if (!nColumn)
					{
						Listview_InsertText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, szItem);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, nColumn, szItem);
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST, LVM_GETITEMCOUNT) > 0)
	{
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), 0);
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->EnableWindow();
		ShowArgumentDetails();
		return;
	}
	SendDlgItemMessage(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->EnableWindow(FALSE);
	ShowArgumentDetails();
}

VOID CTCProcedureCallProcedureAuthorizationDialog::ShowArgumentDetails()
{
	INT  nIndex;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST))) >= 0)
	{
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->SetWindowText(Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))));
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->EnableWindow();
	}
	else
	{
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow(FALSE);
}

INT CTCProcedureCallProcedureAuthorizationDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProcedureCallProcedureAuthorizationDialog::IsModified() CONST
{
	INT  nArgument;
	INT  nArguments;

	for (nArgument = 0, nArguments = (INT)m_szArgumentValues.GetSize(); nArgument < nArguments; nArgument++)
	{
		if (Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))) != m_szArgumentValues.GetAt(nArgument)) break;
		continue;
	}
	return((nArgument < nArguments) ? TRUE : FALSE);
}

void CTCProcedureCallProcedureAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureCallProcedureAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureCallProcedureAuthorizationDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_szArgumentValues.RemoveAll();
	m_pDatabaseTCProcedureArguments.RemoveAll();
	CTCProcedureDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureCallProcedureAuthorizationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureCallProcedureAuthorizationDialog)
	ON_BN_CLICKED(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET, OnSetValue)
	ON_BN_CLICKED(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ACKNOWLEDGE, OnAcknowledge)
	ON_EN_CHANGE(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE, OnEditchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureCallProcedureAuthorizationDialog message handlers

BOOL CTCProcedureCallProcedureAuthorizationDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CString  szStep[2];
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE)) ? (rColumns.Width() / 7) : (9 * rColumns.Width() / 35)));
		continue;
	}
	EnumArguments();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DESCRIPTION)->GetWindowText(szStep[0]);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_COMMENTS)->GetWindowText(szStep[1]);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TYPE)->SetWindowText(m_szStep[1]);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DESCRIPTION)->SetWindowText((m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0]));
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_COMMENTS)->SetWindowText((m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1]));
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TIME)->SetWindowText(m_tAuthorization.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ACKNOWLEDGE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ACKNOWLEDGE)->SetFocus();
	return FALSE;
}

BOOL CTCProcedureCallProcedureAuthorizationDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowArgumentDetails();
	}
	return CTCProcedureDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureCallProcedureAuthorizationDialog::OnSetValue()
{
	TIMETAG  tValue;
	CString  szValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->GetWindowText(szValue); (pDatabaseTCProcedureArgument = m_pDatabaseTCProcedureArguments.GetAt(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)))); )
	{
		if ((((nAttributes = pDatabaseTCProcedureArgument->GetAttributes()) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 2);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 2);
			}
			if (nAttributes & TCPARAMETER_RADIX_OCTAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 8);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 8);
			}
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 16);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 16);
			}
			if ((nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) szValue = cStringTools.ConvertLongUIntToString(CDatabaseEngine::ParseValue(szValue, 10));
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), szValue);
			break;
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = cStringTools.ConvertLongIntToString(CDatabaseEngine::ParseValue(szValue, 10))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = cStringTools.ConvertFloatToString(CDatabaseEngine::ParseValue(szValue))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_TIME)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)) : EMPTYSTRING));
				break;
			}
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
		{
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), szValue);
			break;
		}
		break;
	}
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureCallProcedureAuthorizationDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnOK();
}

void CTCProcedureCallProcedureAuthorizationDialog::OnEditchangeValue()
{
	CString  szValue;

	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->GetWindowText(szValue);
	GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))) != szValue  &&  !szValue.IsEmpty()) ? TRUE : FALSE);
}

void CTCProcedureCallProcedureAuthorizationDialog::OnOK()
{
	INT  nArgument;
	INT  nArguments;
	double  fValue;
	LPTSTR  pszValue;
	TIMETAG  tValue;
	CString  szValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CHourglassCursor  cCursor;

	for (nArgument = 0, nArguments = (INT)m_pDatabaseTCProcedureArguments.GetSize(); nArgument < nArguments; nArgument++)
	{
		if ((pDatabaseTCProcedureArgument = m_pDatabaseTCProcedureArguments.GetAt(nArgument)))
		{
			if ((((nAttributes = pDatabaseTCProcedureArgument->GetAttributes()) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
			{
				for (szValue = Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))); nAttributes & TCPARAMETER_RADIX_BINARY; )
				{
					uValue = CDatabaseEngine::ParseValue(szValue, 2);
					break;
				}
				if (nAttributes & TCPARAMETER_RADIX_OCTAL) uValue = CDatabaseEngine::ParseValue(szValue, 8);
				if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) uValue = CDatabaseEngine::ParseValue(szValue, 16);
				if ((nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) uValue = CDatabaseEngine::ParseValue(szValue, 10);
				va_arg(m_pArgumentList[1], ULONGLONG) = uValue;
				continue;
			}
			if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
			{
				if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
				{
					va_arg(m_pArgumentList[1], LONGLONG) = nValue = CDatabaseEngine::ParseValue(Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))), 10);
					continue;
				}
				if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
				{
					va_arg(m_pArgumentList[1], double) = fValue = CDatabaseEngine::ParseValue(Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))));
					continue;
				}
				if (nAttributes & TCPARAMETER_CODING_TIME)
				{
					va_arg(m_pArgumentList[1], TIMETAG) = tValue = CDatabaseEngine::ParseTime(Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))));
					continue;
				}
			}
			if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
			{
				if ((pszValue = (LPTSTR)GlobalAlloc(GPTR, ((szValue = Listview_GetText(GetDlgItem(IDC_TCPROCEDURECALLPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)))).GetLength() + 1)*sizeof(TCHAR))))
				{
					_tcscpy_s(pszValue, szValue.GetLength() + 1, szValue);
					va_arg(m_pArgumentList[1], LPCTSTR) = pszValue;
					m_pArgumentStrings.Add(pszValue);
					continue;
				}
			}
		}
	}
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStartProcedureAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureStartProcedureAuthorizationDialog, CTCProcedureDialog)

CTCProcedureStartProcedureAuthorizationDialog::CTCProcedureStartProcedureAuthorizationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureStartProcedureAuthorizationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

CTCProcedureStartProcedureAuthorizationDialog::~CTCProcedureStartProcedureAuthorizationDialog()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)m_pArgumentStrings.GetSize(); nItem < nItems; nItem++)
	{
		GlobalFree(m_pArgumentStrings.GetAt(nItem));
		continue;
	}
	m_pArgumentStrings.RemoveAll();
}

INT CTCProcedureStartProcedureAuthorizationDialog::DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, LPCTSTR pszProcedure, va_list pArgumentList)
{
	for (m_pDatabase = pDatabase, m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tAuthorization = tAuthorization, m_szProcedure = pszProcedure, m_pArgumentList[0] = m_pArgumentList[1] = pArgumentList; TRUE; )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return IDOK;
		break;
	}
	return IDCANCEL;
}

VOID CTCProcedureStartProcedureAuthorizationDialog::EnumArguments()
{
	INT  nColumn;
	INT  nColumns;
	INT  nArgument;
	INT  nArguments;
	double  fValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	TIMETAG  tValue;
	CString  szItem;
	CStringTools  cStringTools;
	CDatabaseTCProcedure  *pProcedure;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;

	if ((pProcedure = m_pDatabase->GetTCProcedures()->GetAt(m_pDatabase->GetTCProcedures()->Find(m_szProcedure))))
	{
		for (nArgument = 0, nArguments = pProcedure->GetArguments(m_pDatabaseTCProcedureArguments); nArgument < nArguments; nArgument++)
		{
			if ((pDatabaseTCProcedureArgument = m_pDatabaseTCProcedureArguments.GetAt(nArgument)))
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
				{
					for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME); )
					{
						szItem = pDatabaseTCProcedureArgument->GetTag();
						break;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE))
					{
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_RAW) : EMPTYSTRING;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_NUMERICAL) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTYPE_STATUS) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_CODING))
					{
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_BITPATTERN) : EMPTYSTRING;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_SIGNEDINTEGER) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_UNSIGNEDINTEGER) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_FLOATINGPOINT) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_DATETIME) : szItem;
						szItem = ((pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? ((pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) ? ((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_BITPATTERN)) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSCODING_STRING)) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_RADIX))
					{
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_BINARY) : EMPTYSTRING;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_OCTAL) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_DECIMAL) : szItem;
						szItem = (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSRADIX_HEXADECIMAL) : szItem;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))
					{
						if (((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
						{
							try
							{
								for (uValue = va_arg(m_pArgumentList[0], ULONGLONG); pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_BINARY; )
								{
									szItem = cStringTools.ConvertLongUIntToString(uValue, 2);
									break;
								}
								if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_OCTAL) szItem = cStringTools.ConvertLongUIntToString(uValue, 8);
								if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) szItem = cStringTools.ConvertLongUIntToString(uValue, 16);
								if ((pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) szItem = cStringTools.ConvertLongUIntToString(uValue, 10);
							}
							catch (...)
							{
								szItem.Empty();
							}
						}
						if ((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
						{
							if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER)
							{
								try
								{
									nValue = va_arg(m_pArgumentList[0], LONGLONG);
									szItem = cStringTools.ConvertLongIntToString(nValue);
								}
								catch (...)
								{
									szItem.Empty();
								}
							}
							if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT)
							{
								try
								{
									fValue = va_arg(m_pArgumentList[0], double);
									szItem = cStringTools.ConvertFloatToString(fValue);
								}
								catch (...)
								{
									szItem.Empty();
								}
							}
							if (pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CODING_TIME)
							{
								try
								{
									tValue = va_arg(m_pArgumentList[0], TIMETAG);
									szItem = CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME));
								}
								catch (...)
								{
									szItem.Empty();
								}
							}
						}
						if ((pDatabaseTCProcedureArgument->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) || (pDatabaseTCProcedureArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
						{
							try
							{
								szItem = va_arg(m_pArgumentList[0], LPCTSTR);
							}
							catch (...)
							{
								szItem.Empty();
							}
						}
						m_szArgumentValues.InsertAt(nArgument, szItem);
					}
					if (!nColumn)
					{
						Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, szItem);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, nColumn, szItem);
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST, LVM_GETITEMCOUNT) > 0)
	{
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), 0);
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->EnableWindow();
		ShowArgumentDetails();
		return;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->EnableWindow(FALSE);
	ShowArgumentDetails();
}

VOID CTCProcedureStartProcedureAuthorizationDialog::ShowArgumentDetails()
{
	INT  nIndex;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST))) >= 0)
	{
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->SetWindowText(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))));
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->EnableWindow();
	}
	else
	{
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow(FALSE);
}

INT CTCProcedureStartProcedureAuthorizationDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProcedureStartProcedureAuthorizationDialog::IsModified() CONST
{
	INT  nArgument;
	INT  nArguments;

	for (nArgument = 0, nArguments = (INT)m_szArgumentValues.GetSize(); nArgument < nArguments; nArgument++)
	{
		if (Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))) != m_szArgumentValues.GetAt(nArgument)) break;
		continue;
	}
	return((nArgument < nArguments) ? TRUE : FALSE);
}

void CTCProcedureStartProcedureAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureStartProcedureAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureStartProcedureAuthorizationDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_szArgumentValues.RemoveAll();
	m_pDatabaseTCProcedureArguments.RemoveAll();
	CTCProcedureDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureStartProcedureAuthorizationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureStartProcedureAuthorizationDialog)
	ON_BN_CLICKED(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET, OnSetValue)
	ON_BN_CLICKED(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ACKNOWLEDGE, OnAcknowledge)
	ON_EN_CHANGE(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE, OnEditchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStartProcedureAuthorizationDialog message handlers

BOOL CTCProcedureStartProcedureAuthorizationDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CString  szStep[2];
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_NAME)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_TYPE)) ? (rColumns.Width() / 7) : (9 * rColumns.Width() / 35)));
		continue;
	}
	EnumArguments();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DESCRIPTION)->GetWindowText(szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_COMMENTS)->GetWindowText(szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TYPE)->SetWindowText(m_szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DESCRIPTION)->SetWindowText((m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0]));
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_COMMENTS)->SetWindowText((m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1]));
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TIME)->SetWindowText(m_tAuthorization.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ACKNOWLEDGE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ACKNOWLEDGE)->SetFocus();
	return FALSE;
}

BOOL CTCProcedureStartProcedureAuthorizationDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowArgumentDetails();
	}
	return CTCProcedureDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureStartProcedureAuthorizationDialog::OnSetValue()
{
	TIMETAG  tValue;
	CString  szValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->GetWindowText(szValue); (pDatabaseTCProcedureArgument = m_pDatabaseTCProcedureArguments.GetAt(Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)))); )
	{
		if ((((nAttributes = pDatabaseTCProcedureArgument->GetAttributes()) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 2);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 2);
			}
			if (nAttributes & TCPARAMETER_RADIX_OCTAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 8);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 8);
			}
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 16);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 16);
			}
			for (; (nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0; )
			{
				szValue = cStringTools.ConvertLongUIntToString((uValue = CDatabaseEngine::ParseValue(szValue, 10)));
				break;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), szValue);
			break;
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = cStringTools.ConvertLongIntToString(CDatabaseEngine::ParseValue(szValue, 10))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = cStringTools.ConvertFloatToString(CDatabaseEngine::ParseValue(szValue))));
				break;
			}
			if (nAttributes & TCPARAMETER_CODING_TIME)
			{
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), (szValue = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? CTimeTag().FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)) : EMPTYSTRING));
				break;
			}
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
		{
			Listview_SetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)), szValue);
			break;
		}
		break;
	}
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureStartProcedureAuthorizationDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnOK();
}

void CTCProcedureStartProcedureAuthorizationDialog::OnEditchangeValue()
{
	CString  szValue;

	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE)->GetWindowText(szValue);
	GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_VALUE_SET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST)), FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))) != szValue  &&  !szValue.IsEmpty()) ? TRUE : FALSE);
}

void CTCProcedureStartProcedureAuthorizationDialog::OnOK()
{
	INT  nArgument;
	INT  nArguments;
	double  fValue;
	LPTSTR  pszValue;
	TIMETAG  tValue;
	CString  szValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CHourglassCursor  cCursor;

	for (nArgument = 0, nArguments = (INT)m_pDatabaseTCProcedureArguments.GetSize(); nArgument < nArguments; nArgument++)
	{
		if ((pDatabaseTCProcedureArgument = m_pDatabaseTCProcedureArguments.GetAt(nArgument)))
		{
			if ((((nAttributes = pDatabaseTCProcedureArgument->GetAttributes()) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
			{
				for (szValue = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))); nAttributes & TCPARAMETER_RADIX_BINARY; )
				{
					uValue = CDatabaseEngine::ParseValue(szValue, 2);
					break;
				}
				if (nAttributes & TCPARAMETER_RADIX_OCTAL) uValue = CDatabaseEngine::ParseValue(szValue, 8);
				if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) uValue = CDatabaseEngine::ParseValue(szValue, 16);
				if ((nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) uValue = CDatabaseEngine::ParseValue(szValue, 10);
				va_arg(m_pArgumentList[1], ULONGLONG) = uValue;
				continue;
			}
			if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
			{
				if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
				{
					va_arg(m_pArgumentList[1], LONGLONG) = nValue = CDatabaseEngine::ParseValue(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))), 10);
					continue;
				}
				if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
				{
					va_arg(m_pArgumentList[1], double) = fValue = CDatabaseEngine::ParseValue(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))));
					continue;
				}
				if (nAttributes & TCPARAMETER_CODING_TIME)
				{
					va_arg(m_pArgumentList[1], TIMETAG) = tValue = CDatabaseEngine::ParseTime(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE))));
					continue;
				}
			}
			if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0)
			{
				if ((pszValue = (LPTSTR)GlobalAlloc(GPTR, ((szValue = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESTARTPROCEDUREAUTHORIZATION_ARGUMENTS_LIST), nArgument, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_ARGUMENTSTITLEITEM_VALUE)))).GetLength() + 1)*sizeof(TCHAR))))
				{
					_tcscpy_s(pszValue, szValue.GetLength() + 1, szValue);
					va_arg(m_pArgumentList[1], LPCTSTR) = pszValue;
					m_pArgumentStrings.Add(pszValue);
					continue;
				}
			}
		}
	}
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CTCProcedureSendTCFunctionParametersCalibrationPage, CLocalePropertyPage)

CTCProcedureSendTCFunctionParametersCalibrationPage::CTCProcedureSendTCFunctionParametersCalibrationPage() : CLocalePropertyPage()
{
	m_psp.dwFlags |= PSP_DLGINDIRECT;
	m_psp.pResource = (LPCDLGTEMPLATE)LoadLocalePropertyPageTemplate(MAKEINTRESOURCE(CTCProcedureSendTCFunctionParametersCalibrationPage::IDD));
}

VOID CTCProcedureSendTCFunctionParametersCalibrationPage::ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	CString  szName;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	for (SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), m_pDatabase = pDatabase, m_szCalTableIDs.RemoveAll(); pDatabaseTCParameter != (CONST CDatabaseTCParameter *) NULL; )
	{
		if ((m_nCalTableType = (pDatabaseTCParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))) == TCPARAMETER_CALIBRATION_NUMERICAL)
		{
			if ((pDatabaseTCNumCalTable = m_pDatabase->GetTCNumCalTables()->GetAt(m_pDatabase->GetTCNumCalTables()->Find(pDatabaseTCParameter->GetCalTable()))))
			{
				for (szName.Format(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTCNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTCNumCalTable->GetName()); pDatabaseTCNumCalTable->GetDescription().IsEmpty(); )
				{
					szName = pDatabaseTCNumCalTable->GetDescription();
					break;
				}
				SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_szCalTableIDs.Add(pDatabaseTCNumCalTable->GetName());
			}
		}
		if (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((pDatabaseTCTxtCalTable = m_pDatabase->GetTCTxtCalTables()->GetAt(m_pDatabase->GetTCTxtCalTables()->Find(pDatabaseTCParameter->GetCalTable()))))
			{
				for (szName.Format(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTCTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTCTxtCalTable->GetName()); pDatabaseTCTxtCalTable->GetDescription().IsEmpty(); )
				{
					szName = pDatabaseTCTxtCalTable->GetDescription();
					break;
				}
				SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
				m_szCalTableIDs.Add(pDatabaseTCTxtCalTable->GetName());
			}
		}
		break;
	}
	SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CTCProcedureSendTCFunctionParametersCalibrationPage::ShowCalibrationInfo()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	double  fCalPtX;
	double  fCalPtY;
	CString  szItem;
	CString  szCalPtX;
	CString  szCalPtY;
	CString  szCalText;
	CStringTools  cStringTools;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCNumCalPoint  *pDatabaseTCNumCalPoint;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pDatabaseTCTxtCalPoint;

	SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0)
	{
		if ((pDatabaseTCNumCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_NUMERICAL) ? m_pDatabase->GetTCNumCalTables()->GetAt(m_pDatabase->GetTCNumCalTables()->Find(m_szCalTableIDs.GetAt(nIndex))) : (CDatabaseTCNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTCNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCNumCalPoint = pDatabaseTCNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTCNumCalPoint->GetX(), -1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTCNumCalPoint->GetY(), -1);
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTCNumCalTable->GetName());
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
		if ((pDatabaseTCTxtCalTable = (m_nCalTableType == TCPARAMETER_CALIBRATION_STATUS) ? m_pDatabase->GetTCTxtCalTables()->GetAt(m_pDatabase->GetTCTxtCalTables()->Find(m_szCalTableIDs.GetAt(nIndex))) : (CDatabaseTCTxtCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTCTxtCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCTxtCalPoint = pDatabaseTCTxtCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTCTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTCTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTCTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTCTxtCalTable->GetName());
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

BOOL CTCProcedureSendTCFunctionParametersCalibrationPage::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X)));
	szY = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y)));
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CTCProcedureSendTCFunctionParametersFolder *CTCProcedureSendTCFunctionParametersCalibrationPage::GetParent() CONST
{
	return((CTCProcedureSendTCFunctionParametersFolder *)CLocalePropertyPage::GetParent());
}

INT CTCProcedureSendTCFunctionParametersCalibrationPage::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

HGLOBAL CTCProcedureSendTCFunctionParametersCalibrationPage::LoadLocalePropertyPageTemplate(UINT nPropertyPageID) CONST
{
	return LoadLocalePropertyPageTemplate(MAKEINTRESOURCE(nPropertyPageID));
}
HGLOBAL CTCProcedureSendTCFunctionParametersCalibrationPage::LoadLocalePropertyPageTemplate(LPCTSTR pszPropertyPageName) CONST
{
	HMODULE  hModule;
	HRSRC  hPropertyPageTemplate;

	return(((hPropertyPageTemplate = FindResourceEx((hModule = GetLibraryModuleInstance()), RT_DIALOG, pszPropertyPageName, GetLanguageID())) || (hPropertyPageTemplate = FindResourceEx(hModule, RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hPropertyPageTemplate = FindResourceEx(hModule, RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hPropertyPageTemplate) : (LPVOID)NULL);
}

void CTCProcedureSendTCFunctionParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureSendTCFunctionParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureSendTCFunctionParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_szCalTableIDs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureSendTCFunctionParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCProcedureSendTCFunctionParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersCalibrationPage message handlers

BOOL CTCProcedureSendTCFunctionParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5; nColumn < nColumns; nWidth = (++nColumn > 0) ? (2 * (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

BOOL CTCProcedureSendTCFunctionParametersCalibrationPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szX;
	CString  szY;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			if (GetSelectedCalibrationPoint(szX, szY))
			{
				GetParent()->GetParent()->SetSelectedCalibrationPoint(szX, szY);
				GetParent()->GetParent()->EndDialog(IDOK);
				return TRUE;
			}
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureSendTCFunctionParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CTCProcedureSendTCFunctionParametersFolderTabCtrl, CTabCtrl)

CTCProcedureSendTCFunctionParametersFolder *CTCProcedureSendTCFunctionParametersFolderTabCtrl::GetParent() CONST
{
	return((CTCProcedureSendTCFunctionParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CTCProcedureSendTCFunctionParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCProcedureSendTCFunctionParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersFolderTabCtrl message handlers

UINT CTCProcedureSendTCFunctionParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CTCProcedureSendTCFunctionParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd  *pWnd;

	if (nChar == VK_TAB)
	{
		if ((pWnd = GetParent()->GetParent()->GetNextDlgTabItem(GetParent(), (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	if (nChar == VK_DOWN)
	{
		if ((pWnd = GetParent()->GetActivePage()->GetNextDlgTabItem((CWnd *)NULL)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersFolder

IMPLEMENT_DYNCREATE(CTCProcedureSendTCFunctionParametersFolder, CLocalePropertySheetDialog)

CTCProcedureSendTCFunctionParametersFolder::CTCProcedureSendTCFunctionParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CTCProcedureSendTCFunctionParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	INT  nPage;

	if (CLocalePropertySheetDialog::Create(pParentWnd, WS_CHILD | WS_TABSTOP | WS_DISABLED))
	{
		for (nPage = GetPageCount() - 1, m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage >= 0; nPage--)
		{
			SetActivePage(nPage);
			continue;
		}
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		ShowWindow(SW_SHOWNORMAL);
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureSendTCFunctionParametersFolder::ShowParameterInfo(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	m_pageCalibration.ShowParameterInfo(pDatabase, pDatabaseTCParameter);
}

BOOL CTCProcedureSendTCFunctionParametersFolder::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	return m_pageCalibration.GetSelectedCalibrationPoint(szX, szY);
}

CTCProcedureSendTCFunctionParametersDialog *CTCProcedureSendTCFunctionParametersFolder::GetParent() CONST
{
	return((CTCProcedureSendTCFunctionParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

BEGIN_MESSAGE_MAP(CTCProcedureSendTCFunctionParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CTCProcedureSendTCFunctionParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersFolder message handlers

void CTCProcedureSendTCFunctionParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureSendTCFunctionParametersDialog, CTCProcedureDialog)

CTCProcedureSendTCFunctionParametersDialog::CTCProcedureSendTCFunctionParametersDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureSendTCFunctionParametersDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureSendTCFunctionParametersDialog::DoModal(CONST CDatabaseEngine *pDatabase, LPCTSTR pszFunction, LPCTSTR pszParameter, CString &szValue)
{
	INT  nResult;
	CString  szX;
	CString  szY;

	for (m_pDatabase = pDatabase, m_szFunction = pszFunction, m_szParameter = (AfxIsValidString(pszParameter)) ? pszParameter : EMPTYSTRING; (nResult = (INT)CTCProcedureDialog::DoModal()) == IDOK; )
	{
		szValue = (GetSelectedCalibrationPoint(szX, szY)) ? szY : EMPTYSTRING;
		break;
	}
	return nResult;
}

VOID CTCProcedureSendTCFunctionParametersDialog::SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY)
{
	m_szX = pszX;
	m_szY = pszY;
}

BOOL CTCProcedureSendTCFunctionParametersDialog::GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST
{
	szX = m_szX;
	szY = m_szY;
	return((!szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CTCProcedureSendTCFunctionAuthorizationDialog *CTCProcedureSendTCFunctionParametersDialog::GetParent() CONST
{
	return((CTCProcedureSendTCFunctionAuthorizationDialog *)CTCProcedureDialog::GetParent());
}

BOOL CTCProcedureSendTCFunctionParametersDialog::EnumParameters()
{
	INT  nElement;
	INT  nElements;
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTCPacket  *pTCPacket;
	CDatabaseTCFunction  *pTCFunction;
	CDatabaseTCPacketParameter  *pTCPacketParameter;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	if ((pTCFunction = m_pDatabase->GetTCFunctions()->GetAt(m_pDatabase->GetTCFunctions()->Find(m_szFunction))))
	{
		if ((pTCPacket = m_pDatabase->GetTCPackets()->GetAt(m_pDatabase->GetTCPackets()->Find(pTCFunction->GetTCPacket()))))
		{
			for (nParameter = 0, nParameters = (INT)pTCPacket->GetSize(); nParameter < nParameters; nParameter++)
			{
				if ((pTCPacketParameter = pTCPacket->GetAt(nParameter)) && pTCPacketParameter->GetTag() == m_szParameter)
				{
					if ((pTCPacketParameter->GetAttributes() & (TCPARAMETER_TYPE_VARIABLE | TCPARAMETER_CALIBRATION_ENABLED)) == (TCPARAMETER_TYPE_VARIABLE | TCPARAMETER_CALIBRATION_ENABLED))
					{
						szParameter.Format(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERSDIALOG_FORMAT), (LPCTSTR)pTCPacketParameter->GetTag(), (LPCTSTR)pTCPacketParameter->GetDescription());
						SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
						break;
					}
				}
			}
		}
		if (!SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_GETCOUNT))
		{
			for (nElement = 0, nElements = (INT)pTCFunction->GetSize(); nElement < nElements; nElement++)
			{
				if ((pTCFunctionElement = pTCFunction->GetAt(nElement)) && pTCFunctionElement->GetName() == m_szParameter)
				{
					if ((pTCFunctionElement->GetAttributes() & (TCPARAMETER_TYPE_VARIABLE | TCPARAMETER_CALIBRATION_ENABLED)) == (TCPARAMETER_TYPE_VARIABLE | TCPARAMETER_CALIBRATION_ENABLED))
					{
						szParameter.Format(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERSDIALOG_FORMAT), (LPCTSTR)pTCFunctionElement->GetName(), (LPCTSTR)pTCFunctionElement->GetDescription());
						SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
						break;
					}
				}
			}
		}
	}
	szParameter.Format(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERSDIALOG_FORMAT), (LPCTSTR)m_szParameter, EMPTYSTRING);
	SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter), 0));
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCProcedureSendTCFunctionParametersDialog::ShowParameterInfo()
{
	CString  szParameter[2];
	CDatabaseTCParameter  *pParameter;

	for (GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM)->GetWindowText(szParameter[0]), szParameter[1].Format(STRING(IDS_TCPROCEDURESENDTCFUNCTIONPARAMETERSDIALOG_FORMAT), EMPTYSTRING, EMPTYSTRING), szParameter[0] = (szParameter[0].Find(szParameter[1]) >= 0) ? szParameter[0].Left(szParameter[0].Find(szParameter[1])) : szParameter[0]; (pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(szParameter[0]))); )
	{
		m_wndFolderCtrl.ShowParameterInfo(m_pDatabase, pParameter);
		return;
	}
	m_wndFolderCtrl.ShowParameterInfo(m_pDatabase);
}

CRect CTCProcedureSendTCFunctionParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CTCProcedureSendTCFunctionParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureSendTCFunctionParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProcedureSendTCFunctionParametersDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureSendTCFunctionParametersDialog)
	ON_CBN_SELCHANGE(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionParametersDialog message handlers

BOOL CTCProcedureSendTCFunctionParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	if (m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONPARAMETERS_FOLDER - 1)))
	{
		for (; EnumParameters(); )
		{
			ShowParameterInfo();
			break;
		}
	}
	return TRUE;
}

void CTCProcedureSendTCFunctionParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

void CTCProcedureSendTCFunctionParametersDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_wndFolderCtrl.GetSelectedCalibrationPoint(m_szX, m_szY);
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionAuthorizationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureSendTCFunctionAuthorizationDialog, CTCProcedureDialog)

CTCProcedureSendTCFunctionAuthorizationDialog::CTCProcedureSendTCFunctionAuthorizationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureSendTCFunctionAuthorizationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureSendTCFunctionAuthorizationDialog::DoModal(CONST CDatabaseEngine *pDatabase, CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tAuthorization, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket)
{
	for (m_pDatabase = pDatabase, m_pTCProcessEngine = pTCProcessEngine, m_pTCEnvironment = pTCEnvironment, m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tAuthorization = tAuthorization, m_pTCFunction[0] = pTCFunction, m_pTCPacket[0] = pTCPacket, m_pTCFunction[1] = (CDatabaseTCFunction *)NULL, m_pTCPacket[1] = (CDatabaseTCPacket *)NULL; (m_pTCFunction[1] = new CDatabaseTCFunction) && (m_pTCPacket[1] = new CDatabaseTCPacket) && m_pTCFunction[1]->Copy(pTCFunction) && m_pTCPacket[1]->Copy(pTCPacket); )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return IDOK;
		break;
	}
	return IDCANCEL;
}

VOID CTCProcedureSendTCFunctionAuthorizationDialog::EnumParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nColumn;
	INT  nColumns;
	INT  nElement;
	INT  nElements;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CStringTools  cStringTools;
	CDatabaseTCParameter  *pParameter;
	CDatabaseTCPacketParameter  *pTCPacketParameter;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST, LVM_DELETEALLITEMS);
	for (nParameter = 0, nParameters = (INT)m_pTCPacket[1]->GetSize(), nCount = 0; nParameter < nParameters; nParameter++)
	{
		if ((pTCPacketParameter = m_pTCPacket[1]->GetAt(nParameter)) != (CDatabaseTCPacketParameter *)NULL)
		{
			for (nColumn = 0, nColumns = ((pTCPacketParameter->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) != TCPARAMETER_TYPE_CONSTANT || IsDlgButtonChecked(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_SHOWALL)) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG); )
				{
					szItem = pTCPacketParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_DESCRIPTION); )
				{
					szItem = pTCPacketParameter->GetDescription();
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE))
				{
					szItem = ((pTCPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (pTCPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_DISABLED)) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_RAW) : EMPTYSTRING;
					szItem = ((pTCPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCPacketParameter->GetTag())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_NUMERICAL) : szItem;
					szItem = ((pTCPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCPacketParameter->GetTag())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_STATUS) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET); )
				{
					szItem = cStringTools.ConvertIntToString(8 * pTCPacketParameter->GetBytePos() + pTCPacketParameter->GetBitPos());
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITLENGTH); )
				{
					szItem = cStringTools.ConvertIntToString(pTCPacketParameter->GetWidth());
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_CODING))
				{
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_BITPATTERN) : EMPTYSTRING;
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_SIGNEDINTEGER) : szItem;
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_UNSIGNEDINTEGER) : szItem;
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_FLOATINGPOINT) : szItem;
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_DATETIME) : szItem;
					szItem = ((pTCPacketParameter->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? (((pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) || (pTCPacketParameter->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_BITPATTERN)) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_RADIX))
				{
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_BINARY) : EMPTYSTRING;
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_OCTAL) : szItem;
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_DECIMAL) : szItem;
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_HEXADECIMAL) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE); )
				{
					szItem = pTCPacketParameter->GetConstValueAsText();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_FLAG); )
				{
					szItem = (pTCPacketParameter->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_FIXED) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nCount, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nCount, nColumn, szItem);
				nCount = (nColumn == nColumns - 1) ? (nCount + 1) : nCount;
			}
		}
	}
	for (nElement = 0, nElements = (INT)m_pTCFunction[1]->GetSize(); nElement < nElements; nElement++)
	{
		if ((pTCFunctionElement = m_pTCFunction[1]->GetAt(nElement)) != (CDatabaseTCFunctionElement *)NULL)
		{
			for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
			{
				if (_ttoi(Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET)))) > 8 * pTCFunctionElement->GetBytePos() + pTCFunctionElement->GetBitPos()) break;
				continue;
			}
			for (nColumn = 0, nColumns = ((pTCFunctionElement->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) != TCPARAMETER_TYPE_CONSTANT || IsDlgButtonChecked(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_SHOWALL)) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG); )
				{
					szItem = pTCFunctionElement->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_DESCRIPTION); )
				{
					szItem = pTCFunctionElement->GetDescription();
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE))
				{
					szItem = ((pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_DISABLED)) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_RAW) : EMPTYSTRING;
					szItem = ((pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_NUMERICAL) : szItem;
					szItem = ((pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_STATUS) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET); )
				{
					szItem = cStringTools.ConvertIntToString(8 * pTCFunctionElement->GetBytePos() + pTCFunctionElement->GetBitPos());
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITLENGTH); )
				{
					szItem = cStringTools.ConvertIntToString(pTCFunctionElement->GetWidth());
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_CODING))
				{
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_BITPATTERN) : EMPTYSTRING;
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_SIGNEDINTEGER) : szItem;
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_UNSIGNEDINTEGER) : szItem;
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_FLOATINGPOINT) : szItem;
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_DATETIME) : szItem;
					szItem = ((pTCFunctionElement->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? (((pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) || (pTCFunctionElement->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_UNSIGNEDINTEGER) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSCODING_BITPATTERN)) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_RADIX))
				{
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_BINARY) : EMPTYSTRING;
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_OCTAL) : szItem;
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_DECIMAL) : szItem;
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSRADIX_HEXADECIMAL) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE); )
				{
					szItem = pTCFunctionElement->GetConstValueAsText();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_FLAG); )
				{
					szItem = (pTCFunctionElement->GetAttributes() & TCPARAMETER_TYPE_CONSTANT) ? STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_FIXED) : STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nItem, nColumn, szItem);
			}
		}
	}
	for (GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->SetWindowText(EMPTYSTRING), GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow(FALSE); SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST, LVM_GETITEMCOUNT) > 0; )
	{
		Listview_SetCurText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), 0);
		GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_SHOWALL)->EnableWindow();
		return;
	}
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_REMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_REMARK)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_SHOWALL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->EnableWindow(FALSE);
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCFunctionParameterRawIntValue(CDatabaseTCFunctionElement *pTCFunctionElement, LONGLONG nValue)
{
	pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), pTCFunctionElement->GetWidth(), nValue));
	return TRUE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCFunctionParameterRawUIntValue(CDatabaseTCFunctionElement *pTCFunctionElement, ULONGLONG nValue)
{
	pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), pTCFunctionElement->GetWidth(), nValue));
	return TRUE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCFunctionParameterRawFloatValue(CDatabaseTCFunctionElement *pTCFunctionElement, double fValue)
{
	pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), fValue));
	return TRUE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCFunctionParameterValue(CDatabaseTCFunctionElement *pTCFunctionElement, double fValue, BOOL bExtrapolate)
{
	INT  nPoint;
	INT  nPoints;
	double  fRawValue;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCNumCalPoint  *pDatabaseTCNumCalPoint[2];

	if ((pDatabaseTCParameter = m_pDatabase->GetTCParameters()->GetAt((pTCFunctionElement->GetRef() < 0) ? m_pDatabase->GetTCParameters()->Find(pTCFunctionElement->GetName()) : pTCFunctionElement->GetRef())))
	{
		if ((pDatabaseTCNumCalTable = ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) && (pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED)) ? m_pDatabase->GetTCNumCalTables()->GetAt((pDatabaseTCParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCNumCalTables()->Find(pDatabaseTCParameter->GetCalTable()) : pDatabaseTCParameter->GetCalTableRef()) : (CDatabaseTCNumCalTable *)NULL))
		{
			for (nPoint = 0, nPoints = (INT)pDatabaseTCNumCalTable->GetSize() - 1; nPoint < nPoints; nPoint++)
			{
				if ((pDatabaseTCNumCalPoint[0] = pDatabaseTCNumCalTable->GetAt(nPoint)))
				{
					if ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(nPoint + 1)))
					{
						if ((fValue >= pDatabaseTCNumCalPoint[0]->GetY() && fValue <= pDatabaseTCNumCalPoint[1]->GetY()) || (fValue <= pDatabaseTCNumCalPoint[0]->GetY() && fValue >= pDatabaseTCNumCalPoint[1]->GetY()))
						{
							fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX());
							break;
						}
					}
				}
			}
			for (; nPoint == nPoints && bExtrapolate; )
			{
				if ((pDatabaseTCNumCalPoint[0] = ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(1))) ? pDatabaseTCNumCalTable->GetAt(0) : (CDatabaseTCNumCalPoint *)NULL))
				{
					if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTCParameter->GetWidth()))
					{
						nPoint = nPoints - 1;
						break;
					}
				}
				if ((pDatabaseTCNumCalPoint[0] = ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound()))) ? pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound() - 1) : (CDatabaseTCNumCalPoint *)NULL))
				{
					if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTCParameter->GetWidth()))
					{
						nPoint = nPoints - 1;
						break;
					}
				}
				break;
			}
			if (nPoint < nPoints)
			{
				if (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) return SetTCFunctionParameterRawIntValue(pTCFunctionElement, (LONGLONG)fRawValue);
				if ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER)) return SetTCFunctionParameterRawUIntValue(pTCFunctionElement, (ULONGLONG)fRawValue);
				if (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) return SetTCFunctionParameterRawFloatValue(pTCFunctionElement, fRawValue);
			}
		}
	}
	return FALSE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCFunctionParameterTimeValue(CDatabaseTCFunctionElement *pTCFunctionElement, LPCTSTR pszTime)
{
	ULONGLONG  nValue;

	if (m_pTCProcessEngine->ConvertTCParameterTimeValue(m_pDatabase, m_pTCEnvironment, pTCFunctionElement->GetName(), pTCFunctionElement->GetWidth(), pszTime, nValue))
	{
		pTCFunctionElement->SetConstValue(nValue);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCFunctionParameterStringValue(CDatabaseTCFunctionElement *pTCFunctionElement, LPCTSTR pszText)
{
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szValue;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pDatabaseTCTxtCalPoint;

	if ((pDatabaseTCParameter = m_pDatabase->GetTCParameters()->GetAt((pTCFunctionElement->GetRef() < 0) ? m_pDatabase->GetTCParameters()->Find(pTCFunctionElement->GetName()) : pTCFunctionElement->GetRef())))
	{
		if ((pDatabaseTCTxtCalTable = ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) && (pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED)) ? m_pDatabase->GetTCTxtCalTables()->GetAt((pDatabaseTCParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCTxtCalTables()->Find(pDatabaseTCParameter->GetCalTable()) : pDatabaseTCParameter->GetCalTableRef()) : (CDatabaseTCTxtCalTable *)NULL))
		{
			for (nPoint = 0, nPoints = (INT)pDatabaseTCTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
			{
				if ((pDatabaseTCTxtCalPoint = pDatabaseTCTxtCalTable->GetAt(nPoint)))
				{
					if ((pDatabaseTCTxtCalPoint->GetPoint(fX[0], szValue) && szValue == pszText) || (pDatabaseTCTxtCalPoint->GetRange(fX[0], fX[1], szValue) && szValue == pszText)) break;
					continue;
				}
			}
			if (nPoint < nPoints)
			{
				if (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) return SetTCFunctionParameterRawIntValue(pTCFunctionElement, (LONGLONG)fX[0]);
				if ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER)) return SetTCFunctionParameterRawUIntValue(pTCFunctionElement, (ULONGLONG)fX[0]);
				if (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) return SetTCFunctionParameterRawFloatValue(pTCFunctionElement, fX[0]);
			}
		}
	}
	return FALSE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCPacketParameterRawIntValue(CDatabaseTCPacketParameter *pTCPacketParameter, LONGLONG nValue)
{
	pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), pTCPacketParameter->GetWidth(), nValue));
	return TRUE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCPacketParameterRawUIntValue(CDatabaseTCPacketParameter *pTCPacketParameter, ULONGLONG nValue)
{
	pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), pTCPacketParameter->GetWidth(), nValue));
	return TRUE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCPacketParameterRawFloatValue(CDatabaseTCPacketParameter *pTCPacketParameter, double fValue)
{
	pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), fValue));
	return TRUE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::SetTCPacketParameterRawTimeValue(CDatabaseTCPacketParameter *pTCPacketParameter, LPCTSTR pszTime)
{
	ULONGLONG  nValue;

	if (m_pTCProcessEngine->ConvertTCParameterTimeValue(m_pDatabase, m_pTCEnvironment, pTCPacketParameter->GetTag(), pTCPacketParameter->GetWidth(), pszTime, nValue))
	{
		pTCPacketParameter->SetConstValue(nValue);
		return TRUE;
	}
	return FALSE;
}

UINT CTCProcedureSendTCFunctionAuthorizationDialog::ConvertTimeStringValue(LPCTSTR pszTime) CONST
{
	CTimeTag  tTime;

	return(((tTime = CDatabaseEngine::ParseTime(pszTime)) > 0) ? m_pTCProcessEngine->ConvertTimeToOBRT(m_pTCEnvironment, tTime) : 0);
}

INT CTCProcedureSendTCFunctionAuthorizationDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::IsModified() CONST
{
	return((!m_pTCFunction[0]->Compare(m_pTCFunction[1]) || !m_pTCPacket[0]->Compare(m_pTCPacket[1])) ? TRUE : FALSE);
}

void CTCProcedureSendTCFunctionAuthorizationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureSendTCFunctionAuthorizationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureSendTCFunctionAuthorizationDialog::PostNcDestroy()
{
	delete m_pTCPacket[1];
	delete m_pTCFunction[1];
	m_szColumns.RemoveAll();
	CTCProcedureDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureSendTCFunctionAuthorizationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureSendTCFunctionAuthorizationDialog)
	ON_BN_CLICKED(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_NOEXTRAPOLATION, OnNoExtrapolation)
	ON_BN_CLICKED(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_SHOWALL, OnShowAll)
	ON_BN_CLICKED(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_SET, OnSetParameterValue)
	ON_BN_CLICKED(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_ACKNOWLEDGE, OnAcknowledge)
	ON_EN_CHANGE(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE, OnEditchangeParameterValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSendTCFunctionAuthorizationDialog message handlers

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CString  szStep[2];
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITLENGTH));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE));
	m_szColumns.Add(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_FLAG));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_DESCRIPTION)) ? (2 * rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_FLAG)) ? (rColumns.Width() / 7) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITLENGTH)) ? (rColumns.Width() / 10) : (9 * rColumns.Width() / 35)))));
		continue;
	}
	EnumParameters();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DESCRIPTION)->GetWindowText(szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_COMMENTS)->GetWindowText(szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TYPE)->SetWindowText(m_szStep[1]);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DESCRIPTION)->SetWindowText((m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0]));
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_COMMENTS)->SetWindowText((m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1]));
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TIME)->SetWindowText(m_tAuthorization.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_ACKNOWLEDGE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_ACKNOWLEDGE)->SetFocus();
	return FALSE;
}

BOOL CTCProcedureSendTCFunctionAuthorizationDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szTag;
	CString  szType;
	CString  szFlag;
	CString  szValue;
	CString  szOffset;
	CDatabaseTCFunctionElement  *pFunctionElement;
	CTCProcedureSendTCFunctionParametersDialog  cParametersDialog;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			szTag = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG)));
			szType = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE)));
			szFlag = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_FLAG)));
			szOffset = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET)));
			CheckDlgButton(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_NOEXTRAPOLATION, ((pFunctionElement = m_pTCFunction[1]->GetAt(m_pTCFunction[1]->Find(szTag, _ttoi(szOffset) / 8, _ttoi(szOffset) % 8))) && (pFunctionElement->GetAttributes() & TCPARAMETER_INTERPRETATION_FULL) && szFlag == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE)) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->SetWindowText((szFlag == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE)) ? Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE))) : EMPTYSTRING);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_REMARK)->ShowWindow((szType != STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_RAW)) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_REMARK)->EnableWindow((szType != STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_RAW)) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_NOEXTRAPOLATION)->EnableWindow((szType == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_NUMERICAL) && szFlag == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE)) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_STATIC)->EnableWindow((szFlag == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE)) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->EnableWindow((szFlag == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE)) ? TRUE : FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow(FALSE);
			GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)->SetFocus();
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			for (szTag = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG))), szType = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TYPE))), szFlag = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_FLAG))); szType != STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTYPE_RAW) && cParametersDialog.DoModal(m_pDatabase, m_pTCFunction[1]->GetName(), szTag, szValue) == IDOK && szFlag == STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSVALUEFLAG_VARIABLE) && !szValue.IsEmpty(); )
			{
				GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)), FindColumnIndex(STRING(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE))) != szValue  &&  !szValue.IsEmpty()) ? TRUE : FALSE);
				GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->SetWindowText(szValue);
				SendDlgItemMessage(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE, EM_SETSEL, 0, -1);
				GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->SetFocus();
				break;
			}
		}
	}
	return CTCProcedureDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureSendTCFunctionAuthorizationDialog::OnNoExtrapolation()
{
	INT  nIndex;
	CString  szTag;
	CString  szOffset;
	CDatabaseTCFunctionElement  *pTCFunctionElement;
	CHourglassCursor  cCursor;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST))) >= 0)
	{
		for (szTag = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG))), szOffset = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET))); (pTCFunctionElement = m_pTCFunction[1]->GetAt(m_pTCFunction[1]->Find(szTag, _ttoi(szOffset) / 8, _ttoi(szOffset) % 8))); )
		{
			pTCFunctionElement->SetAttributes((IsDlgButtonChecked(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_NOEXTRAPOLATION)) ? ((pTCFunctionElement->GetAttributes() & ~TCPARAMETER_INTERPRETATION_EXTRAPOLATE) | TCPARAMETER_INTERPRETATION_FULL) : ((pTCFunctionElement->GetAttributes() & ~TCPARAMETER_INTERPRETATION_FULL) | TCPARAMETER_INTERPRETATION_EXTRAPOLATE));
			break;
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureSendTCFunctionAuthorizationDialog::OnShowAll()
{
	CHourglassCursor  cCursor;

	EnumParameters();
}

void CTCProcedureSendTCFunctionAuthorizationDialog::OnSetParameterValue()
{
	INT  nBit;
	INT  nByte;
	INT  nIndex;
	BOOL  bTime;
	double  fValue;
	CString  szTag;
	CString  szValue;
	CString  szOffset;
	LONGLONG  nValue;
	CTimeTag  tValue;
	CStringTools  cStringTools;
	CDatabaseTCParameter  *pParameter;
	CDatabaseTCPacketParameter  *pTCPacketParameter;
	CDatabaseTCFunctionElement  *pTCFunctionElement;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->GetWindowText(szValue); (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST))) >= 0; )
	{
		for (szTag = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_TAG))), szOffset = Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_BITOFFSET))); (pTCFunctionElement = m_pTCFunction[1]->GetAt(m_pTCFunction[1]->Find(szTag, (nByte = _ttoi(szOffset) / 8), (nBit = _ttoi(szOffset) % 8)))); )
		{
			if ((pParameter = (pTCFunctionElement->GetAttributes() & TCFUNCTIONELEMENT_TYPE_PARAMETER) ? m_pDatabase->GetTCParameters()->GetAt((pTCFunctionElement->GetRef() < 0) ? m_pDatabase->GetTCParameters()->Find(pTCFunctionElement->GetName()) : pTCFunctionElement->GetRef()) : (CDatabaseTCParameter *)NULL))
			{
				for (bTime = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? TRUE : FALSE; (pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) == 0 || (pParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS)) == 0; )
				{
					if (((pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) || (pTCFunctionElement->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) && !bTime)
					{
						if ((pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_BINARY) == TCPARAMETER_RADIX_BINARY)
						{
							SetTCFunctionParameterRawUIntValue(pTCFunctionElement, CDatabaseEngine::ParseValue(szValue, 2));
							szValue = cStringTools.ConvertLongUIntToString(pTCFunctionElement->GetConstValue(), 2);
							break;
						}
						if (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_OCTAL)
						{
							SetTCFunctionParameterRawUIntValue(pTCFunctionElement, CDatabaseEngine::ParseValue(szValue, 8));
							szValue = cStringTools.ConvertLongUIntToString(pTCFunctionElement->GetConstValue(), 8);
							break;
						}
						if (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL)
						{
							SetTCFunctionParameterRawUIntValue(pTCFunctionElement, CDatabaseEngine::ParseValue(szValue, 16));
							szValue = cStringTools.ConvertLongUIntToString(pTCFunctionElement->GetConstValue(), 16);
							break;
						}
						SetTCFunctionParameterRawUIntValue(pTCFunctionElement, CDatabaseEngine::ParseValue(szValue, 10));
						szValue = cStringTools.ConvertLongUIntToString(pTCFunctionElement->GetConstValue());
						break;
					}
					if (!bTime)
					{
						if (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER)
						{
							SetTCFunctionParameterRawIntValue(pTCFunctionElement, (nValue = CDatabaseEngine::ParseValue(szValue, 10)));
							szValue = cStringTools.ConvertLongIntToString(nValue);
							break;
						}
						if (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT)
						{
							SetTCFunctionParameterRawFloatValue(pTCFunctionElement, (fValue = CDatabaseEngine::ParseValue(szValue)));
							szValue = cStringTools.ConvertFloatToString(fValue);
							break;
						}
					}
					if ((pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) || bTime)
					{
						SetTCFunctionParameterTimeValue(pTCFunctionElement, szValue);
						szValue = tValue.FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME));
						break;
					}
					szValue = pTCFunctionElement->GetConstValueAsText();
					break;
				}
				for (; pTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED; )
				{
					if (pParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS))
					{
						if ((pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) == TCPARAMETER_CALIBRATION_NUMERICAL)
						{
							szValue = (!SetTCFunctionParameterValue(pTCFunctionElement, CDatabaseEngine::ParseValue(szValue), !IsDlgButtonChecked(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_NOEXTRAPOLATION))) ? pTCFunctionElement->GetConstValueAsText() : szValue;
							break;
						}
						if (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)
						{
							szValue = (!SetTCFunctionParameterStringValue(pTCFunctionElement, szValue)) ? pTCFunctionElement->GetConstValueAsText() : szValue;
							break;
						}
					}
					szValue = pTCFunctionElement->GetConstValueAsText();
					break;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE)), szValue);
				pTCFunctionElement->SetConstValueAsText(szValue);
			}
			break;
		}
		for (; (pTCPacketParameter = m_pTCPacket[1]->GetAt(m_pTCPacket[1]->Find(szTag, nByte, nBit))); )
		{
			if ((pParameter = (pTCPacketParameter->GetAttributes() & TCPACKETPARAMETER_TYPE_VARIABLE) ? m_pDatabase->GetTCParameters()->GetAt((pTCPacketParameter->GetRef() < 0) ? m_pDatabase->GetTCParameters()->Find(pTCPacketParameter->GetTag()) : pTCPacketParameter->GetRef()) : (CDatabaseTCParameter *)NULL))
			{
				for (bTime = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? TRUE : FALSE; (pTCPacketParameter->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) == 0 || (pParameter->GetAttributes() & (TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS)) == 0; )
				{
					if (((pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) || (pTCPacketParameter->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) && !bTime)
					{
						if ((pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_BINARY) == TCPARAMETER_RADIX_BINARY)
						{
							SetTCPacketParameterRawUIntValue(pTCPacketParameter, CDatabaseEngine::ParseValue(szValue, 2));
							szValue = cStringTools.ConvertLongUIntToString(pTCPacketParameter->GetConstValue(), 2);
							break;
						}
						if (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_OCTAL)
						{
							SetTCPacketParameterRawUIntValue(pTCPacketParameter, CDatabaseEngine::ParseValue(szValue, 8));
							szValue = cStringTools.ConvertLongUIntToString(pTCPacketParameter->GetConstValue(), 8);
							break;
						}
						if (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL)
						{
							SetTCPacketParameterRawUIntValue(pTCPacketParameter, CDatabaseEngine::ParseValue(szValue, 16));
							szValue = cStringTools.ConvertLongUIntToString(pTCPacketParameter->GetConstValue(), 16);
							break;
						}
						SetTCPacketParameterRawUIntValue(pTCPacketParameter, CDatabaseEngine::ParseValue(szValue, 10));
						szValue = cStringTools.ConvertLongUIntToString(pTCPacketParameter->GetConstValue());
						break;
					}
					if (!bTime)
					{
						if (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER)
						{
							SetTCPacketParameterRawIntValue(pTCPacketParameter, (nValue = CDatabaseEngine::ParseValue(szValue, 10)));
							szValue = cStringTools.ConvertLongIntToString(nValue);
							break;
						}
						if (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT)
						{
							SetTCPacketParameterRawFloatValue(pTCPacketParameter, (fValue = CDatabaseEngine::ParseValue(szValue)));
							szValue = cStringTools.ConvertFloatToString(fValue);
							break;
						}
					}
					if ((pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME) || bTime)
					{
						SetTCPacketParameterRawTimeValue(pTCPacketParameter, szValue);
						szValue = tValue.FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME));
						break;
					}
					szValue = pTCPacketParameter->GetConstValueAsText();
					break;
				}
				Listview_SetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDURESTEPAUTHORIZATIONDIALOG_PARAMETERSTITLEITEM_VALUE)), szValue);
				pTCPacketParameter->SetConstValueAsText(szValue);
			}
			break;
		}
		GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureSendTCFunctionAuthorizationDialog::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnOK();
}

void CTCProcedureSendTCFunctionAuthorizationDialog::OnEditchangeParameterValue()
{
	CString  szValue;

	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE)->GetWindowText(szValue);
	GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE_SET)->EnableWindow((Listview_GetText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_LIST)), FindColumnIndex(STRING(IDC_TCPROCEDURESENDTCFUNCTIONAUTHORIZATION_PARAMETERS_VALUE))) != szValue  &&  !szValue.IsEmpty()) ? TRUE : FALSE);
}

void CTCProcedureSendTCFunctionAuthorizationDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_pTCPacket[0]->Copy(m_pTCPacket[1]);
	m_pTCFunction[0]->Copy(m_pTCFunction[1]);
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureUserInteractionDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureUserInteractionDialog, CTCProcedureDialog)

CTCProcedureUserInteractionDialog::CTCProcedureUserInteractionDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureUserInteractionDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureUserInteractionDialog::DoModal(UINT nType, LPCTSTR pszMessage, CONST CStringArray &szVariables, CONST CLongUIntArray &nVariableAttributes, CONST CPtrArray &pVariables, CONST CStringArray &szVariableValues)
{
	INT  nVariable;
	INT  nVariables;

	for (nVariable = 0, nVariables = (INT)szVariables.GetSize(), m_nType = nType, m_szMessage = pszMessage, m_szVariables.Copy(szVariables), m_nVariableAttributes.Copy(nVariableAttributes), m_pVariables.Copy(pVariables), m_szVariableValues.Copy(szVariableValues); nVariable < nVariables; nVariable++)
	{
		if (!m_pVariables.GetAt(nVariable))
		{
			m_szVariables.RemoveAt(nVariable);
			m_pVariables.RemoveAt(nVariable);
			m_nVariableAttributes.RemoveAt(nVariable);
			m_szVariableValues.RemoveAt(nVariable);
			nVariables--;
			nVariable--;
		}
	}
	return((INT)CTCProcedureDialog::DoModal());
}

BOOL CTCProcedureUserInteractionDialog::EnumVariables()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	double  fValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	TIMETAG  tValue;
	CString  *pValue;
	CString  szItem;
	CStringTools  cStringTools;

	for (nItem = 0, nItems = (INT)m_szVariables.GetSize(); nItem < nItems; nItem++)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_NAME); )
			{
				szItem = m_szVariables.GetAt(nItem);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_TYPE); )
			{
				szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTYPE_VARIABLE);
				break;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_CODING))
			{
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_BITPATTERN) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSCODING_BITPATTERN);
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_SIGNEDINTEGER) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSCODING_SIGNEDINTEGER);
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_UNSIGNEDINTEGER) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSCODING_UNSIGNEDINTEGER);
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_FLOATINGPOINT) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSCODING_FLOATINGPOINT);
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_TIME) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSCODING_DATETIME);
				if ((m_nVariableAttributes.GetAt(nItem) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSCODING_STRING);
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_RADIX))
			{
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_RADIX_BINARY) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSRADIX_BINARY);
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_RADIX_OCTAL) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSRADIX_OCTAL);
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_RADIX_DECIMAL) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSRADIX_DECIMAL);
				if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_RADIX_HEXADECIMAL) szItem = STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSRADIX_HEXADECIMAL);
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE); )
			{
				if (((m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_BITPATTERN) || (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
				{
					for (CopyMemory(&uValue, m_pVariables.GetAt(nItem), sizeof(uValue)); m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_RADIX_BINARY; )
					{
						szItem = cStringTools.ConvertLongUIntToString(uValue, 2);
						break;
					}
					if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_RADIX_OCTAL) szItem = cStringTools.ConvertLongUIntToString(uValue, 8);
					if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_RADIX_HEXADECIMAL) szItem = cStringTools.ConvertLongUIntToString(uValue, 16);
					if ((m_nVariableAttributes.GetAt(nItem) & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) szItem = cStringTools.ConvertLongUIntToString(uValue, 10);
				}
				if ((m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
				{
					if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_SIGNEDINTEGER)
					{
						CopyMemory(&nValue, m_pVariables.GetAt(nItem), sizeof(nValue));
						szItem = cStringTools.ConvertLongIntToString(nValue);
					}
					if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_FLOATINGPOINT)
					{
						CopyMemory(&fValue, m_pVariables.GetAt(nItem), sizeof(fValue));
						szItem = cStringTools.ConvertFloatToString(fValue);
					}
					if (m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CODING_TIME)
					{
						CopyMemory(&tValue, m_pVariables.GetAt(nItem), sizeof(tValue));
						szItem = CTimeTag(tValue).FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME));
					}
				}
				if ((m_nVariableAttributes.GetAt(nItem) & TCPARAMETER_CALIBRATION_STATUS) || (m_nVariableAttributes.GetAt(nItem) & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) szItem = ((pValue = (CString *)m_pVariables.GetAt(nItem))) ? (LPCTSTR)(*pValue) : EMPTYSTRING;
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nItem, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nItem, nColumn, szItem);
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), 0);
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)->EnableWindow((SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES, LVM_GETITEMCOUNT) > 0 && EnumVariableValues()) ? TRUE : FALSE);
}

BOOL CTCProcedureUserInteractionDialog::EnumVariableValues()
{
	INT  nPos;
	INT  nIndex;
	CString  szValue;
	CString  szValues;

	SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VALUE, CB_RESETCONTENT);
	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES))) >= 0 && nIndex < m_szVariableValues.GetSize())
	{
		for (szValues = m_szVariableValues.GetAt(nIndex), szValue = Listview_GetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE))); (nPos = szValues.Find(TAB)) >= 0 || !szValues.IsEmpty(); szValues = (nPos >= 0) ? szValues.Mid(nPos + 1) : EMPTYSTRING)
		{
			SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nPos >= 0) ? (LPCTSTR)szValues.Left(nPos) : (LPCTSTR)szValues));
			continue;
		}
		SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VALUE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue));
		GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE)->EnableWindow();
		GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE_SET)->EnableWindow(FALSE);
		return TRUE;
	}
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE_STATIC)->EnableWindow((m_nType == TCPROCEDUREUSERINTERACTIONITEM_ACTION_REQUEST) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE)->EnableWindow((m_nType == TCPROCEDUREUSERINTERACTIONITEM_ACTION_REQUEST) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE_SET)->EnableWindow(FALSE);
	return FALSE;
}

INT CTCProcedureUserInteractionDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CTCProcedureUserInteractionDialog::IsModified() CONST
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	CString  szValue;
	CString  szValues;

	for (nItem = 0, nItems = (INT)GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)->SendMessage(LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if ((szValue = Listview_GetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nItem, FindColumnIndex(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE)))).GetLength() > 0)
		{
			for (nPos = 0, szValues = (m_nType == TCPROCEDUREUSERINTERACTIONITEM_ACTION_CHOOSE) ? m_szVariableValues.GetAt(nItem) : EMPTYSTRING; (nPos = szValues.Find(TAB)) >= 0 || !szValues.IsEmpty(); szValues = (nPos >= 0) ? szValues.Mid(nPos + 1) : EMPTYSTRING)
			{
				if ((nPos >= 0 && szValues.Left(nPos) == szValue) || (nPos < 0 && szValues == szValue)) break;
				continue;
			}
			if (m_nType != TCPROCEDUREUSERINTERACTIONITEM_ACTION_CHOOSE || !szValues.IsEmpty()) continue;
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCProcedureUserInteractionDialog::Check(BOOL bModified) CONST
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)->SendMessage(LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if (!Listview_GetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nItem, FindColumnIndex(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE))).GetLength()) break;
		continue;
	}
	return((nItem == nItems) ? (!bModified || IsModified()) : FALSE);
}

void CTCProcedureUserInteractionDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureUserInteractionDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCProcedureUserInteractionDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pVariables.RemoveAll();
	m_szVariables.RemoveAll();
	m_szVariableValues.RemoveAll();
	m_nVariableAttributes.RemoveAll();
	CTCProcedureDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCProcedureUserInteractionDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureUserInteractionDialog)
	ON_BN_CLICKED(IDC_TCPROCEDUREUSERINTERACTION_VALUE_SET, OnSetValue)
	ON_CBN_EDITCHANGE(IDC_TCPROCEDUREUSERINTERACTION_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_TCPROCEDUREUSERINTERACTION_VALUE, OnSelchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureUserInteractionDialog message handlers

BOOL CTCProcedureUserInteractionDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_NAME)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_TYPE)) ? (rColumns.Width() / 8) : (rColumns.Width() / 4)));
		continue;
	}
	EnumVariables();
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_TYPE)->SetWindowText((m_nType == TCPROCEDUREUSERINTERACTIONITEM_ACTION_ACKNOWLEDGE) ? STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_ACTIONTYPE_ACKNOWLEDGE) : ((m_nType == TCPROCEDUREUSERINTERACTIONITEM_ACTION_REQUEST) ? STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_ACTIONTYPE_REQUEST) : STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_ACTIONTYPE_CHOOSE)));
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_MESSAGE)->SetWindowText(m_szMessage);
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_MESSAGE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_MESSAGE)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return TRUE;
}

BOOL CTCProcedureUserInteractionDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) EnumVariableValues();
	}
	return CTCProcedureDialog::OnNotify(wParam, lParam, pResult);
}

void CTCProcedureUserInteractionDialog::OnSetValue()
{
	INT  nIndex;
	CString  szValue;
	CTimeTag  tValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE)->GetWindowText(szValue); (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES))) >= 0; )
	{
		if ((((nAttributes = m_nVariableAttributes.GetAt(nIndex)) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 2);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 2);
			}
			if (nAttributes & TCPARAMETER_RADIX_OCTAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 8);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 8);
			}
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL)
			{
				uValue = CDatabaseEngine::ParseValue(szValue, 16);
				szValue = cStringTools.ConvertLongUIntToString(uValue, 16);
			}
			if ((nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) szValue = cStringTools.ConvertLongUIntToString(CDatabaseEngine::ParseValue(szValue, 10));
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if (nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) szValue = cStringTools.ConvertLongIntToString(CDatabaseEngine::ParseValue(szValue, 10));
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT) szValue = cStringTools.ConvertFloatToString(CDatabaseEngine::ParseValue(szValue));
			if (nAttributes & TCPARAMETER_CODING_TIME) szValue = ((tValue = CDatabaseEngine::ParseTime(szValue)) > 0) ? tValue.FormatGmt(STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME)) : EMPTYSTRING;
		}
		Listview_SetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nIndex, FindColumnIndex(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE)), szValue);
		GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE_SET)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCProcedureUserInteractionDialog::OnEditchangeValue()
{
	CString  szValue[2];

	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE)->GetWindowText(szValue[0]);
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE_SET)->EnableWindow(((szValue[1] = Listview_GetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)), FindColumnIndex(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE)))) != szValue[0] && !szValue[0].IsEmpty() && (m_nType == TCPROCEDUREUSERINTERACTIONITEM_ACTION_REQUEST || (m_nType == TCPROCEDUREUSERINTERACTIONITEM_ACTION_CHOOSE  &&  SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue[0]) >= 0))) ? TRUE : FALSE);
}

void CTCProcedureUserInteractionDialog::OnSelchangeValue()
{
	CString  szValue[2];

	szValue[0] = Combobox_GetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE), (INT)SendDlgItemMessage(IDC_TCPROCEDUREUSERINTERACTION_VALUE, CB_GETCURSEL));
	GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VALUE_SET)->EnableWindow(((szValue[1] = Listview_GetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), Listview_GetCurText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES)), FindColumnIndex(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE)))) != szValue[0] && !szValue[0].IsEmpty()) ? TRUE : FALSE);
}

void CTCProcedureUserInteractionDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	double  fValue;
	TIMETAG  tValue;
	CString  szValue;
	CString  *pValue;
	LONGLONG  nValue;
	ULONGLONG  uValue;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	for (nItem = 0, nItems = (INT)m_szVariables.GetSize(); nItem < nItems; nItem++)
	{
		for (szValue = Listview_GetText(GetDlgItem(IDC_TCPROCEDUREUSERINTERACTION_VARIABLES), nItem, FindColumnIndex(STRING(IDS_TCPROCEDUREUSERINTERACTIONDIALOG_IDENTIFIERSTITLEITEM_VALUE))); (((nAttributes = m_nVariableAttributes.GetAt(nItem)) & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && (nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS; )
		{
			if (nAttributes & TCPARAMETER_RADIX_BINARY) uValue = CDatabaseEngine::ParseValue(szValue, 2);
			if (nAttributes & TCPARAMETER_RADIX_OCTAL) uValue = CDatabaseEngine::ParseValue(szValue, 8);
			if (nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) uValue = CDatabaseEngine::ParseValue(szValue, 16);
			if ((nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) uValue = CDatabaseEngine::ParseValue(szValue, 10);
			CopyMemory(m_pVariables.GetAt(nItem), &uValue, sizeof(uValue));
			break;
		}
		if ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) != TCPARAMETER_CALIBRATION_STATUS)
		{
			if ((nAttributes & TCPARAMETER_CODING_SIGNEDINTEGER) == TCPARAMETER_CODING_SIGNEDINTEGER)
			{
				CopyMemory(m_pVariables.GetAt(nItem), &(nValue = CDatabaseEngine::ParseValue(szValue, 10)), sizeof(nValue));
				continue;
			}
			if (nAttributes & TCPARAMETER_CODING_FLOATINGPOINT)
			{
				CopyMemory(m_pVariables.GetAt(nItem), &(fValue = CDatabaseEngine::ParseValue(szValue)), sizeof(fValue));
				continue;
			}
			if (nAttributes & TCPARAMETER_CODING_TIME)
			{
				CopyMemory(m_pVariables.GetAt(nItem), &(tValue = CDatabaseEngine::ParseTime(szValue)), sizeof(tValue));
				continue;
			}
		}
		if ((pValue = ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) || (nAttributes & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == 0) ? (CString *)m_pVariables.GetAt(nItem) : (CString *)NULL)) *pValue = szValue;
	}
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureUserConfirmationDialog dialog

IMPLEMENT_DYNCREATE(CTCProcedureUserConfirmationDialog, CTCProcedureDialog)

CTCProcedureUserConfirmationDialog::CTCProcedureUserConfirmationDialog(CWnd *pParentWnd) : CTCProcedureDialog()
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CTCProcedureUserConfirmationDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT CTCProcedureUserConfirmationDialog::DoModal(LPCTSTR pszProcess, LPCTSTR pszThread, LPCTSTR pszStep, UINT nType, LPCTSTR pszDescription, LPCTSTR pszComments, CONST CTimeKey &tStep, CONST CTimeSpan &tTimeout, BOOL bConfirmation)
{
	for (m_szProcess = pszProcess, m_szThread = pszThread, m_szStep[0] = pszStep, m_szStep[1] = STRING(MINTELECOMMANDPROCEDURESTEPTYPE + nType - 1), m_szStep[2] = pszDescription, m_szStep[3] = pszComments, m_tStep = tStep, m_tTimeout = tTimeout, m_bConfirmation = bConfirmation, m_bResult = FALSE; TRUE; )
	{
		if (CTCProcedureDialog::DoModal() == IDOK) return((m_bResult) ? IDOK : IDCANCEL);
		break;
	}
	return IDCANCEL;
}

void CTCProcedureUserConfirmationDialog::DoDataExchange(CDataExchange *pDX)
{
	CTCProcedureDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCProcedureUserConfirmationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCProcedureUserConfirmationDialog, CTCProcedureDialog)
	//{{AFX_MSG_MAP(CTCProcedureUserConfirmationDialog)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureUserConfirmationDialog message handlers

BOOL CTCProcedureUserConfirmationDialog::OnInitDialog()
{
	CString  szStep[2];
	CString  szTimeout;
	CHourglassCursor  cCursor;

	CTCProcedureDialog::OnInitDialog();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_NAME)->SetWindowText(m_szProcess);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_THREAD)->SetWindowText(m_szThread);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_STEP)->SetWindowText(m_szStep[0]);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_TYPE)->SetWindowText(m_szStep[1]);
	for (GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_DESCRIPTION)->GetWindowText(szStep[0]), GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_COMMENTS)->GetWindowText(szStep[1]), GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_TIME)->GetWindowText(m_szTimeout), m_szStep[2] = (!m_szStep[2].IsEmpty()) ? m_szStep[2] : szStep[0], m_szStep[3] = (!m_szStep[3].IsEmpty()) ? m_szStep[3] : szStep[1], szTimeout.Format(m_szTimeout, m_tTimeout.GetTotalSeconds()); TRUE; )
	{
		GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_TIME)->SetWindowText(m_tStep.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_AUTHORIZATION_TIMEFORMAT)));
		GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_TIME)->SetWindowText(szTimeout);
		GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_DESCRIPTION)->SetWindowText(m_szStep[2]);
		GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_COMMENTS)->SetWindowText(m_szStep[3]);
		break;
	}
	SetTimer(TCPROCEDUREUSERCONFIRMATION_TIMEOUT_TIMERID, TCPROCEDUREUSERCONFIRMATION_TIMEOUT_INTERVAL, NULL);
	CheckRadioButton(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_SUCCESSFUL, IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_FAILED, IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_FAILED);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_TRIGGER_STATIC)->ShowWindow((!m_bConfirmation) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_COMPLETION_STATIC)->ShowWindow((m_bConfirmation) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_THREAD_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_THREAD)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_STEP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_STEP)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_TRIGGER_STATIC)->EnableWindow(!m_bConfirmation);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_COMPLETION_STATIC)->EnableWindow(m_bConfirmation);
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_SUCCESSFUL)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_FAILED)->EnableWindow();
	GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_TIME)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow();
	return TRUE;
}

void CTCProcedureUserConfirmationDialog::OnTimer(UINT_PTR nEventID)
{
	CString  szTimeout;

	if (m_tTimeout.GetTotalSeconds() > 0)
	{
		szTimeout.Format(m_szTimeout, (m_tTimeout = m_tTimeout.GetTotalSeconds() - TCPROCEDUREUSERCONFIRMATION_TIMEOUT_INTERVAL / 1000).GetTotalSeconds());
		GetDlgItem(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_TIME)->SetWindowText(szTimeout);
	}
	if (!m_tTimeout.GetTotalSeconds())
	{
		KillTimer(TCPROCEDUREUSERCONFIRMATION_TIMEOUT_TIMERID);
		CTCProcedureDialog::OnCancel();
		return;
	}
	CTCProcedureDialog::OnTimer(nEventID);
}

void CTCProcedureUserConfirmationDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_bResult = IsDlgButtonChecked(IDC_TCPROCEDUREUSERCONFIRMATION_CONFIRMATION_RESULT_SUCCESSFUL);
	CTCProcedureDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureThread

IMPLEMENT_DYNCREATE(CTCProcedureThread, CThread)

CTCProcedureThread::CTCProcedureThread() : CThread()
{
	m_pDatabase = (CONST CDatabaseEngine *) NULL;
	m_pTCProcessEngine = (CTCProcessEngine *)NULL;
	m_pTCEnvironment = (CTCEnvironment *)NULL;
	m_pTMEnvironment = new CCriticalSection;
	m_fTMBandwidth[0] = NAN;
	m_fTMBandwidth[2] = NAN;
	m_fTMBandwidth[1] = NAN;
	m_fTMBandwidth[3] = NAN;
	m_tTMBandwidth = CTimeTag(0);
	m_nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING;
	m_hState = (HANDLE)NULL;
	m_hUpdate = (HANDLE)NULL;
	m_hResume = (HANDLE)NULL;
	m_hTMEvent = (HANDLE)NULL;
	m_hTCEvent = (HANDLE)NULL;
	m_hResult[0] = (HANDLE)NULL;
	m_hResult[1] = (HANDLE)NULL;
	m_hExit = (HANDLE)NULL;
	m_bEnabled = TRUE;
	m_bAborted = FALSE;
	m_nLine = 0;
}
CTCProcedureThread::CTCProcedureThread(LPCTSTR pszName, CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, HANDLE hTMEvent, HANDLE hTCEvent, HANDLE hUpdate, HANDLE hExit) : CThread()
{
	m_szName = pszName;
	m_pDatabase = pDatabase;
	m_pTCProcessEngine = pTCProcessEngine;
	m_pTCEnvironment = pTCEnvironment;
	m_pTMEnvironment = new CCriticalSection;
	m_fTMBandwidth[0] = NAN;
	m_fTMBandwidth[2] = NAN;
	m_fTMBandwidth[1] = NAN;
	m_fTMBandwidth[3] = NAN;
	m_tTMBandwidth = CTimeTag(0);
	m_nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING;
	m_hState = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, TRUE, FALSE, (LPCTSTR)NULL);
	m_hResume = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL);
	m_hResult[0] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL);
	m_hResult[1] = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, FALSE, FALSE, (LPCTSTR)NULL);
	m_hTMEvent = hTMEvent;
	m_hTCEvent = hTCEvent;
	m_hUpdate = hUpdate;
	m_hExit = hExit;
	m_bEnabled = TRUE;
	m_bAborted = FALSE;
	m_nLine = 0;
}

CTCProcedureThread::~CTCProcedureThread()
{
	if (GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED)
	{
		SetRunningState(TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING);
		Resume();
	}
	if (GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING) ResumeThread();
	for (DestroyThread(); m_hState; )
	{
		CloseHandle(m_hState);
		m_hState = (HANDLE)NULL;
		break;
	}
	if (m_hResume)
	{
		CloseHandle(m_hResume);
		m_hResume = (HANDLE)NULL;
	}
	if (m_hResult[0])
	{
		CloseHandle(m_hResult[0]);
		m_hResult[0] = (HANDLE)NULL;
	}
	if (m_hResult[1])
	{
		CloseHandle(m_hResult[1]);
		m_hResult[1] = (HANDLE)NULL;
	}
	delete m_pTMEnvironment;
	m_pTMEnvironment = (CCriticalSection *)NULL;
}

VOID CTCProcedureThread::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCProcedureThread::GetName() CONST
{
	return m_szName;
}

BOOL CTCProcedureThread::SetContents(CONST CDatabaseTCProcedureThreadContents *pContents)
{
	return m_pContents.Copy(pContents);
}

INT CTCProcedureThread::GetContents(CDatabaseTCProcedureThreadContents *pContents) CONST
{
	pContents->Copy(&m_pContents);
	return((INT)pContents->GetSize());
}

BOOL CTCProcedureThread::SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints)
{
	return m_pDatabaseTCProcedureThreadBreakpoints.Copy(&pDatabaseTCProcedureThreadBreakpoints);
}

INT CTCProcedureThread::GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST
{
	pDatabaseTCProcedureThreadBreakpoints.Copy(&m_pDatabaseTCProcedureThreadBreakpoints);
	return((INT)pDatabaseTCProcedureThreadBreakpoints.GetSize());
}

VOID CTCProcedureThread::EnableSynchronization(BOOL bEnable)
{
	m_bSynchronized = bEnable;
}

BOOL CTCProcedureThread::IsSynchronizationEnabled() CONST
{
	return m_bSynchronized;
}

int CTCProcedureThread::Run()
{
	return ExitInstance(0);
}

BOOL CTCProcedureThread::InitInstance()
{
	for (m_tTime = CTime::GetCurrentTime().GetTime(), m_nLine = 0; TRUE; )
	{
		ReportSuccessMessage(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_THREADSTART));
		break;
	}
	return TRUE;
}

INT CTCProcedureThread::ExitInstance(INT nExitCode)
{
	CString  szMessage;

	for (SetRunningState(TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING); SetEvent(m_hObject) && SetEvent(m_hExit); )
	{
		szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_THREADEXIT), nExitCode);
		ReportSuccessMessage(szMessage);
		break;
	}
	return nExitCode;
}

BOOL CTCProcedureThread::InitParameters()
{
	return TRUE;
}

INT CTCProcedureThread::EnumParameters(CStringArray &szParameters) CONST
{
	szParameters.RemoveAll();
	return 0;
}

BOOL CTCProcedureThread::Initialize(CStringArray &szErrorParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTMUnit  cTMUnit;
	CUIntArray  nTableRefs[2];
	CStringArray  szParameters;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (nParameter = 0, nParameters = EnumParameters(szParameters), szErrorParameters.RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = ((pDatabaseTMParameter = m_pDatabase->GetTMParameters()->GetAt(m_pDatabase->GetTMParameters()->Find(szParameters.GetAt(nParameter))))) ? new CTMParameter : (CTMParameter *)NULL))
		{
			for (pTMParameter->SetTag(pDatabaseTMParameter->GetTag()), pTMParameter->SetAttributes(pDatabaseTMParameter->GetAttributes()); (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) == TMPARAMETER_NATURE_CONSTANT; )
			{
				pTMParameter->SetRawValue(&cTMUnit, 0, pDatabaseTMParameter->GetConstValue(), TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID, (pDatabaseTMParameter->GetCalTableRefs(nTableRefs[0], nTableRefs[1]) > 0) ? ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (((pDatabaseTMNumCalTable = m_pDatabase->GetTMNumCalTables()->GetAt(nTableRefs[0].GetAt(0)))) ? (LPCTSTR)pDatabaseTMNumCalTable->GetName() : EMPTYSTRING) : (((pDatabaseTMTxtCalTable = m_pDatabase->GetTMTxtCalTables()->GetAt(nTableRefs[0].GetAt(0)))) ? (LPCTSTR)pDatabaseTMTxtCalTable->GetName() : EMPTYSTRING)) : EMPTYSTRING);
				break;
			}
			if (m_pTMParameters.Add(pTMParameter) >= 0) continue;
			delete pTMParameter;
		}
		szErrorParameters.Add(szParameters.GetAt(nParameter));
	}
	return((nParameter == nParameters) ? InitParameters() : FALSE);
}
BOOL CTCProcedureThread::Initialize(CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth)
{
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nParameter = 0, nParameters = (INT)m_pTMParameters.GetSize(), m_fTMBandwidth[0] = (fTotalTMBandwidth > 0.0) ? fTotalTMBandwidth : NAN, m_fTMBandwidth[1] = (fTotalTMBandwidth > 0.0 && fAvailableTMBandwidth >= 0.0) ? (fAvailableTMBandwidth / fTotalTMBandwidth) : NAN, m_fTMBandwidth[2] = (fMaxDiagnosticTMBandwidth > 0.0) ? fMaxDiagnosticTMBandwidth : NAN, m_fTMBandwidth[3] = (fMaxDiagnosticTMBandwidth > 0.0 && fAvailableDiagnosticTMBandwidth >= 0.0) ? (fAvailableDiagnosticTMBandwidth / fMaxDiagnosticTMBandwidth) : NAN, m_tTMBandwidth = tTMBandwidth; nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter[0] = ((pTMParameter[1] = m_pTMParameters.GetAt(nParameter))) ? pTMParameters.GetAt(pTMParameters.Find(pTMParameter[1]->GetTag())) : (CTMParameter *)NULL))
		{
			pTMParameter[1]->Initialize(pTMParameter[0]);
			continue;
		}
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::Update(CONST CTMEnvironment *pTMEnvironment)
{
	BOOL  bTMBandwidth;
	double  fTMBandwidth[3];
	CTimeTag  tTMBandwidth;
	CTMProcessInfo  *pTMProcessInfo;

	if (m_pTMEnvironment->Lock())
	{
		if ((pTMProcessInfo = pTMEnvironment->GetTMProcessInfo()))
		{
			if (pTMProcessInfo->GetTMBandwidth(fTMBandwidth[0], fTMBandwidth[2]))
			{
				for (m_fTMBandwidth[0] = fTMBandwidth[0], m_fTMBandwidth[2] = fTMBandwidth[2]; (bTMBandwidth = pTMProcessInfo->GetTMBandwidth(fTMBandwidth[1], tTMBandwidth)); )
				{
					m_fTMBandwidth[1] = (fTMBandwidth[0] - fTMBandwidth[1]) / fTMBandwidth[0];
					m_fTMBandwidth[3] = min(fTMBandwidth[0] - fTMBandwidth[1], fTMBandwidth[2]) / fTMBandwidth[2];
					m_tTMBandwidth = tTMBandwidth;
					break;
				}
				if (!bTMBandwidth)
				{
					m_fTMBandwidth[1] = m_fTMBandwidth[3] = NAN;
					m_tTMBandwidth = 0;
				}
			}
			else
			{
				m_fTMBandwidth[0] = m_fTMBandwidth[1] = m_fTMBandwidth[2] = m_fTMBandwidth[3] = NAN;
				m_tTMBandwidth = 0;
			}
		}
		for (m_cTMUnit.Copy(pTMEnvironment->GetTMUnit()); m_pTMParameters.Update(m_pDatabase, pTMEnvironment->GetTMUnit(), pTMEnvironment->GetTMParameters()); )
		{
			m_pTMEnvironment->Unlock();
			SetEvent(m_hTMEvent);
			return TRUE;
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcedureThread::UpdateBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pDatabaseTCProcedureThreadBreakpoints.Copy(&pDatabaseTCProcedureThreadBreakpoints);
}

VOID CTCProcedureThread::SetRunningState(UINT nState)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_nState != nState)
	{
		m_nState = nState;
		SetEvent(m_hUpdate);
	}
}

UINT CTCProcedureThread::GetRunningState() CONST
{
	return m_nState;
}

BOOL CTCProcedureThread::Break(LPCTSTR pszName)
{
	CString  szMessage;

	szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_BREAKPOINT_HITATSTEP), pszName);
	ReportSuccessMessage(szMessage);
	return GetProcess()->Break();
}

BOOL CTCProcedureThread::Suspend()
{
	for (ResetEvent(m_hState), SetEvent(m_hUpdate); GetCurrentThreadId() != GetThreadID() || Wait(m_hState, FALSE) == WAIT_OBJECT_0 + 1; ) return TRUE;
	return FALSE;
}

BOOL CTCProcedureThread::Synchronize()
{
	DWORD  dwResult;

	for (dwResult = Wait(m_hState, FALSE); dwResult != WAIT_OBJECT_0; )
	{
		if (IsSynchronizationEnabled())
		{
			ResetEvent(m_hResume);
			SetEvent(m_hUpdate);
			return((Wait(m_hResume, FALSE) == WAIT_OBJECT_0 + 1) ? TRUE : FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::Resume()
{
	return((SetEvent(m_hState)) ? SetEvent(m_hUpdate) : FALSE);
}

BOOL CTCProcedureThread::CheckStepTrigger(LPCTSTR pszName)
{
	INT  nObject;
	INT  nObjects;
	BOOL  bSuccess;
	DWORD  dwCode;
	CString  szMessage;
	CTimeTag  tTimeTag;
	CPtrArray  phObjects;
	CStringArray  szObjects;
	CDatabaseTCProcedureThreadStep  *pStep;
	CTCProcedureUserConfirmationDialog  cUserConfirmationDialog;

	if (Wait(0) != WAIT_TIMEOUT)
	{
		for (szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_THREADABORTATSTEP), pszName); !m_bAborted; )
		{
			ReportWarningMessage(szMessage);
			m_bAborted = TRUE;
			break;
		}
		return FALSE;
	}
	for (ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING); CheckStepBreakpoint(pszName, TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS); )
	{
		for (Break(pszName), szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_THREADABORTATSTEP), pszName); (dwCode = Wait(0)) != WAIT_TIMEOUT && !m_bAborted; )
		{
			ReportWarningMessage(szMessage);
			m_bAborted = TRUE;
			break;
		}
		if (dwCode == WAIT_TIMEOUT) break;
		return FALSE;
	}
	for (bSuccess = FALSE; (pStep = FindStep(pszName)); )
	{
		for (szMessage = pStep->GetTriggerMessage(); pStep->GetFailureOptions() & (TCPROCEDURETHREADSTEP_FAILUREOPTION_TRIGGERSUCCESS | TCPROCEDURETHREADSTEP_FAILUREOPTION_TRIGGERFAILURE); )
		{
			if (pStep->GetFailureOptions() & TCPROCEDURETHREADSTEP_FAILUREOPTION_TRIGGERSUCCESS)
			{
				ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED);
				ReportSuccessMessage(szMessage);
				bSuccess = TRUE;
			}
			break;
		}
		if ((pStep->GetFailureOptions() & (TCPROCEDURETHREADSTEP_FAILUREOPTION_TRIGGERSUCCESS | TCPROCEDURETHREADSTEP_FAILUREOPTION_TRIGGERFAILURE)) == 0)
		{
			for (; (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_ATTIME) == TCPROCEDURETHREADSTEP_TRIGGERTYPE_ATTIME; )
			{
				if (Wait(max((DWORD)((pStep->GetTriggerTime().GetTime() - tTimeTag.GetTime()) / 1000), 0)) == WAIT_TIMEOUT)
				{
					ReportSuccessMessage(szMessage);
					bSuccess = TRUE;
				}
				break;
			}
			if (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_NOTAFTERTIME)
			{
				if (pStep->GetTriggerTime() >= tTimeTag.GetTime() && Wait(max((DWORD)((pStep->GetTriggerTime().GetTime() - tTimeTag.GetTime()) / 1000), 0)) == WAIT_TIMEOUT)
				{
					ReportSuccessMessage(szMessage);
					bSuccess = TRUE;
				}
				break;
			}
			if (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEOFFSET)
			{
				if (Wait(max((DWORD)(1000 * (pStep->GetTriggerTimeOffset().GetTotalSeconds() - tTimeTag.GetTimeInSeconds() + m_tTime.GetTime())), 0)) == WAIT_TIMEOUT)
				{
					ReportSuccessMessage(szMessage);
					bSuccess = TRUE;
				}
				break;
			}
			if (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEDELAY)
			{
				if (Wait((DWORD)(1000 * pStep->GetTriggerTimeDelay().GetTotalSeconds())) == WAIT_TIMEOUT)
				{
					ReportSuccessMessage(szMessage);
					bSuccess = TRUE;
				}
				break;
			}
			if (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_SYNCOBJECT)
			{
				for (nObject = 0, nObjects = GetProcess()->EnumSynchronizationObjects(szObjects, phObjects); nObject < nObjects; nObject++)
				{
					if ((dwCode = (pStep->GetTriggerSynchronizationObject() == szObjects.GetAt(nObject)) ? Wait((HANDLE)phObjects.GetAt(nObject), FALSE, (DWORD)(1000 * pStep->GetTriggerTimeout().GetTotalSeconds())) : 0) == WAIT_OBJECT_0 + 1) break;
					continue;
				}
				if (nObject < nObjects)
				{
					ReportSuccessMessage(szMessage);
					bSuccess = TRUE;
				}
				break;
			}
			if (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_EXPRESSION)
			{
				do
				{
					if (CheckStepTriggerExpression(pszName))
					{
						dwCode = WAIT_OBJECT_0 + 1;
						break;
					}
				} while ((dwCode = Wait(m_hTMEvent, FALSE, (DWORD)(1000 * pStep->GetTriggerTimeout().GetTotalSeconds()))) == WAIT_OBJECT_0 + 1);
				if (dwCode == (DWORD)WAIT_OBJECT_0 + 1)
				{
					ReportSuccessMessage(szMessage);
					bSuccess = TRUE;
				}
				break;
			}
			if (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_OPERATOR)
			{
				if (cUserConfirmationDialog.DoModal(GetProcess()->GetName(), GetName(), pszName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tTimeTag.GetTimeInSeconds(), pStep->GetTriggerTimeout(), FALSE) == IDOK)
				{
					ReportSuccessMessage(szMessage);
					bSuccess = TRUE;
				}
				break;
			}
			ReportSuccessMessage(szMessage);
			bSuccess = TRUE;
		}
		break;
	}
	for (; bSuccess; )
	{
		if (CheckStepAuthorization(pszName, TRUE) && !AuthorizeStepExecution(pszName)) break;
		return TRUE;
	}
	for (; CheckStepBreakpoint(pszName, TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER); )
	{
		Break(pszName);
		break;
	}
	return FALSE;
}

BOOL CTCProcedureThread::CheckStepTriggerExpression(LPCTSTR pszName) CONST
{
	return TRUE;
}

BOOL CTCProcedureThread::CheckStepBody(LPCTSTR pszName)
{
	DWORD  dwCode;
	CString  szMessage;
	CDatabaseTCProcedureThreadStep  *pStep;

	if (Wait(0) != WAIT_TIMEOUT)
	{
		for (szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_THREADABORTATSTEP), pszName); !m_bAborted; )
		{
			ReportWarningMessage(szMessage);
			m_bAborted = TRUE;
			break;
		}
		return FALSE;
	}
	for (ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_BODY_RUNNING), ResetEvent(m_hResult[0]), ResetEvent(m_hResult[1]); (pStep = FindStep(pszName)); )
	{
		if (pStep->GetFailureOptions() & TCPROCEDURETHREADSTEP_FAILUREOPTION_BODYSUCCESS)
		{
			ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_BODY_FORCED);
			return TRUE;
		}
		if ((pStep->GetFailureOptions() & TCPROCEDURETHREADSTEP_FAILUREOPTION_BODYFAILURE) != TCPROCEDURETHREADSTEP_FAILUREOPTION_BODYFAILURE)
		{
			do
			{
				if (CheckStepBodyExpression(pszName))
				{
					dwCode = WAIT_OBJECT_0 + 1;
					break;
				}
			} while ((dwCode = Wait(m_hTMEvent, FALSE, (DWORD)(1000 * pStep->GetTriggerTimeout().GetTotalSeconds()))) == WAIT_OBJECT_0 + 1);
			if (dwCode == WAIT_OBJECT_0 + 1) return TRUE;
		}
		break;
	}
	for (; CheckStepBreakpoint(pszName, TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY); )
	{
		Break(pszName);
		break;
	}
	return FALSE;
}

BOOL CTCProcedureThread::CheckStepBodyExpression(LPCTSTR pszName) CONST
{
	return TRUE;
}

BOOL CTCProcedureThread::CheckStepConfirmation(LPCTSTR pszName)
{
	DWORD  dwCode;
	CString  szMessage;
	CTimeKey  tUserConfirmation;
	CDatabaseTCProcedureThreadStep  *pStep;
	CTCProcedureUserConfirmationDialog  cUserConfirmationDialog;

	if (Wait(0) != WAIT_TIMEOUT)
	{
		for (szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_THREADABORTATSTEP), pszName); !m_bAborted; )
		{
			ReportWarningMessage(szMessage);
			m_bAborted = TRUE;
			break;
		}
		return FALSE;
	}
	for (ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_RUNNING); (pStep = (!CheckStepAuthorization(pszName, FALSE) || AuthorizeStepExecution(pszName)) ? FindStep(pszName) : (CDatabaseTCProcedureThreadStep *)NULL); )
	{
		for (szMessage = pStep->GetConfirmationMessage(); pStep->GetFailureOptions() & TCPROCEDURETHREADSTEP_FAILUREOPTION_CONFIRMATIONSUCCESS; )
		{
			ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED);
			ReportSuccessMessage(szMessage);
			return TRUE;
		}
		if ((pStep->GetFailureOptions() & TCPROCEDURETHREADSTEP_FAILUREOPTION_CONFIRMATIONFAILURE) != TCPROCEDURETHREADSTEP_FAILUREOPTION_CONFIRMATIONFAILURE)
		{
			if ((pStep->GetConfirmationType() & TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_COMMAND) == TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_COMMAND)
			{
				if (Wait(m_hResult, sizeof(m_hResult) / sizeof(HANDLE), FALSE, (DWORD)(1000 * pStep->GetConfirmationTimeout().GetTotalSeconds())) == WAIT_OBJECT_0 + 1)
				{
					ReportSuccessMessage(szMessage);
					return TRUE;
				}
				break;
			}
			if (pStep->GetConfirmationType() & TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_EXPRESSION)
			{
				do
				{
					if (CheckStepConfirmationExpression(pszName))
					{
						dwCode = WAIT_OBJECT_0 + 1;
						break;
					}
				} while ((dwCode = Wait(m_hTMEvent, FALSE, (DWORD)(1000 * pStep->GetConfirmationTimeout().GetTotalSeconds()))) == WAIT_OBJECT_0 + 1);
				if (dwCode == (DWORD)WAIT_OBJECT_0 + 1)
				{
					ReportSuccessMessage(szMessage);
					return TRUE;
				}
				break;
			}
			if (pStep->GetConfirmationType() & TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_OPERATOR)
			{
				if (cUserConfirmationDialog.DoModal(GetProcess()->GetName(), GetName(), pszName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tUserConfirmation, pStep->GetConfirmationTimeout(), TRUE) == IDOK)
				{
					ReportSuccessMessage(szMessage);
					return TRUE;
				}
				break;
			}
			ReportSuccessMessage(szMessage);
			return TRUE;
		}
		break;
	}
	for (; CheckStepBreakpoint(pszName, TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION); )
	{
		Break(pszName);
		break;
	}
	return FALSE;
}

BOOL CTCProcedureThread::CheckStepConfirmationExpression(LPCTSTR pszName) CONST
{
	return TRUE;
}

VOID CTCProcedureThread::AlertStepTriggerSuccess(LPCTSTR pszName)
{
	AlertStepTriggerSuccess(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepTriggerSuccess(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_TRIGGER_EXECUTED);
	ReportSuccessMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepTriggerWarning(LPCTSTR pszName)
{
	AlertStepTriggerWarning(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepTriggerWarning(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ReportWarningMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepTriggerFailure(LPCTSTR pszName)
{
	AlertStepTriggerFailure(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepTriggerFailure(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_TRIGGER_FAILED);
	ReportFailureMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepBodySuccess(LPCTSTR pszName)
{
	AlertStepBodySuccess(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepBodySuccess(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_BODY_EXECUTED);
	ReportSuccessMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepBodyWarning(LPCTSTR pszName)
{
	AlertStepBodyWarning(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepBodyWarning(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ReportWarningMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepBodyFailure(LPCTSTR pszName)
{
	AlertStepBodyFailure(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepBodyFailure(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_BODY_FAILED);
	ReportFailureMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepConfirmationSuccess(LPCTSTR pszName)
{
	AlertStepConfirmationSuccess(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepConfirmationSuccess(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_EXECUTED);
	ReportSuccessMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepConfirmationWarning(LPCTSTR pszName)
{
	AlertStepConfirmationWarning(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepConfirmationWarning(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ReportWarningMessage(pszMessage);
}

VOID CTCProcedureThread::AlertStepConfirmationFailure(LPCTSTR pszName)
{
	AlertStepConfirmationFailure(pszName, EMPTYSTRING);
}
VOID CTCProcedureThread::AlertStepConfirmationFailure(LPCTSTR pszName, LPCTSTR pszMessage)
{
	ChangeStepState(pszName, TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FAILED);
	ReportFailureMessage(pszMessage);
}

BOOL CTCProcedureThread::CallProcedure(LPCTSTR pszName, ...)
{
	INT  nTCProcessID;
	INT  nTCProcedureID;
	DWORD  dwTCProcedureCode;
	CString  szErrorMessage;
	CString  szTCProcedure[3];
	CTimeTag  tAuthorization;
	HINSTANCE  hTCProcedureCode;
	CPtrArray  hTCProcedureEvents;
	CStringArray  szErrorParameters;
	CDatabaseTCProcedureThreadStep  *pStep;
	CTCProcedureCallProcedureAuthorizationDialog  cCallProcedureAuthorizationDialog;
	BOOL(__cdecl *pInitialize)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters);
	BOOL(__cdecl *pRun)(INT nID, va_list pArgumentList, UINT nExecutionMode);
	BOOL(__cdecl *pTerminate)(INT nID, BOOL bAuto);

	va_list  pArgumentList;
	for (va_start(pArgumentList, pszName); (pStep = FindStep()); )
	{
		if ((GetProcess()->GetAttributes() & (TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS)) || (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_AUTHORIZATION))
		{
			if (cCallProcedureAuthorizationDialog.DoModal(m_pDatabase, GetProcess()->GetName(), GetName(), m_szStepName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tAuthorization, pszName, pArgumentList) != IDOK)
			{
				szErrorMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_AUTHORIZATION_DENIAL), (LPCTSTR)m_szStepName);
				ReportFailureMessage(szErrorMessage);
				return FALSE;
			}
		}
		if (m_pTCProcessEngine->IsDebuggingEnabled() && GetThreadID() == GetCurrentThreadId())
		{
			if (m_pTCEnvironment->CallTCProcedure(pszName, pArgumentList))
			{
				va_end(pArgumentList);
				return TRUE;
			}
			va_end(pArgumentList);
			return FALSE;
		}
		if ((nTCProcessID = m_pTCEnvironment->LoadTCProcedure(m_pDatabase, pszName, FALSE, hTCProcedureCode, hTCProcedureEvents)) >= 0)
		{
#ifndef UNICODE
			szTCProcedure[0] = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE);
			szTCProcedure[1] = STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE);
			szTCProcedure[2] = STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE);
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE), -1, (LPSTR)szTCProcedure[0].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE), -1, (LPSTR)szTCProcedure[1].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE), -1, (LPSTR)szTCProcedure[2].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_TERMINATETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szTCProcedure[0].ReleaseBuffer();
			szTCProcedure[1].ReleaseBuffer();
			szTCProcedure[2].ReleaseBuffer();
#endif
			if ((pInitialize = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters)) GetProcAddress(hTCProcedureCode, (LPCSTR)(LPCTSTR)szTCProcedure[0])))
			{
				if ((pRun = (BOOL(__cdecl *)(INT nID, va_list pArgumentList, UINT nExecutionMode)) GetProcAddress(hTCProcedureCode, (LPCSTR)(LPCTSTR)szTCProcedure[1])))
				{
					if ((pTerminate = (BOOL(__cdecl *)(INT nID, BOOL bAuto)) GetProcAddress(hTCProcedureCode, (LPCSTR)(LPCTSTR)szTCProcedure[2])))
					{
						if ((*pInitialize)(m_pDatabase, m_pTCProcessEngine, m_pTCEnvironment, pszName, ((nTCProcedureID = GetProcess()->GetProcedureID()) < 0) ? GetProcess()->GetID() : nTCProcedureID, nTCProcessID, -1, FALSE, hTCProcedureEvents, szErrorParameters) && (*pRun)(nTCProcessID, pArgumentList, GetProcess()->GetAttributes() & (TCPROCEDURE_EXECUTIONMODE_AUTOMATIC | TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS | TCPROCEDURE_EXECUTIONMODE_COMMANDS)))
						{
							while ((dwTCProcedureCode = Wait(hTCProcedureEvents.GetAt(hTCProcedureEvents.GetUpperBound()), FALSE)) > WAIT_OBJECT_0)
							{
								if ((*pTerminate)(nTCProcessID, FALSE)) break;
								continue;
							}
							va_end(pArgumentList);
							m_pTCEnvironment->FreeTCProcedure(nTCProcessID);
							return((dwTCProcedureCode == WAIT_OBJECT_0 + 1) ? TRUE : FALSE);
						}
					}
				}
			}
			m_pTCEnvironment->FreeTCProcedure(nTCProcessID);
		}
		break;
	}
	va_end(pArgumentList);
	return FALSE;
}

BOOL CTCProcedureThread::StartProcedure(LPCTSTR pszName, ...)
{
	INT  nTCProcessID;
	INT  nTCProcedureID;
	CString  szErrorMessage;
	CString  szTCProcedure[2];
	CTimeTag  tAuthorization;
	HINSTANCE  hTCProcedureCode;
	CPtrArray  hTCProcedureEvents;
	CStringArray  szErrorParameters;
	CDatabaseTCProcedureThreadStep  *pStep;
	CTCProcedureStartProcedureAuthorizationDialog  cStartProcedureAuthorizationDialog;
	BOOL(__cdecl *pInitialize)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters);
	BOOL(__cdecl *pRun)(INT nID, va_list pArgumentList, UINT nExecutionMode);

	va_list  pArgumentList;
	for (va_start(pArgumentList, pszName); (pStep = FindStep()); )
	{
		if ((GetProcess()->GetAttributes() & (TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS)) || (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_AUTHORIZATION))
		{
			if (cStartProcedureAuthorizationDialog.DoModal(m_pDatabase, GetProcess()->GetName(), GetName(), m_szStepName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tAuthorization, pszName, pArgumentList) != IDOK)
			{
				szErrorMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_AUTHORIZATION_DENIAL), (LPCTSTR)m_szStepName);
				ReportFailureMessage(szErrorMessage);
				return FALSE;
			}
		}
		if (m_pTCProcessEngine->IsDebuggingEnabled() && GetThreadID() == GetCurrentThreadId())
		{
			if (m_pTCEnvironment->StartTCProcedure(pszName, pArgumentList))
			{
				va_end(pArgumentList);
				return TRUE;
			}
			va_end(pArgumentList);
			return FALSE;
		}
		if ((nTCProcessID = m_pTCEnvironment->LoadTCProcedure(m_pDatabase, pszName, FALSE, hTCProcedureCode, hTCProcedureEvents)) >= 0)
		{
#ifndef UNICODE
			szTCProcedure[0] = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE);
			szTCProcedure[1] = STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE);
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE), -1, (LPSTR)szTCProcedure[0].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE), -1, (LPSTR)szTCProcedure[1].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_RUNTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szTCProcedure[0].ReleaseBuffer();
			szTCProcedure[1].ReleaseBuffer();
#endif
			if ((pRun = ((pInitialize = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters)) GetProcAddress(hTCProcedureCode, (LPCSTR)(LPCTSTR)szTCProcedure[0]))) ? (BOOL(__cdecl *)(INT nID, va_list pArgumentList, UINT nExecutionMode)) GetProcAddress(hTCProcedureCode, (LPCSTR)(LPCTSTR)szTCProcedure[1]) : (BOOL(__cdecl *)(INT nID, va_list pArgumentList, UINT nExecutionMode)) NULL) && (*pInitialize)(m_pDatabase, m_pTCProcessEngine, m_pTCEnvironment, pszName, ((nTCProcedureID = GetProcess()->GetProcedureID()) < 0) ? GetProcess()->GetID() : nTCProcedureID, nTCProcessID, -1, FALSE, hTCProcedureEvents, szErrorParameters) && (*pRun)(nTCProcessID, pArgumentList, GetProcess()->GetAttributes() & (TCPROCEDURE_EXECUTIONMODE_AUTOMATIC | TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS | TCPROCEDURE_EXECUTIONMODE_COMMANDS)))
			{
				va_end(pArgumentList);
				return TRUE;
			}
			m_pTCEnvironment->FreeTCProcedure(nTCProcessID);
		}
		break;
	}
	va_end(pArgumentList);
	return FALSE;
}

BOOL CTCProcedureThread::SetProcedureState(LPCTSTR pszName, UINT nState)
{
	INT  nProcedure;
	INT  nProcedures;
	BOOL  bSuccess[2];
	CString  szCode[2];
	CString  szFileName[2];
	CString  szTCProcedure;
	CFileFind  cFileFind[2];
	HINSTANCE  hTCProcedure;
	CPtrArray  pTCProcedures;
	CUIntArray  nTCProcedureIDs;
	CStringArray  szTCProcedures;
	CDatabaseTCProcedure  *pProcedure;
	BOOL(__cdecl *pSuspend)(INT nID);
	BOOL(__cdecl *pResume)(INT nID, BOOL bAuto);
	BOOL(__cdecl *pAbort)(INT nID);

	if (m_pTCProcessEngine->IsDebuggingEnabled())
	{
		for (szFileName[0] = m_pDatabase->GetFileName(), szFileName[1] = m_pDatabase->GetUpdateFileName(); (pProcedure = m_pDatabase->GetTCProcedures()->GetAt(m_pDatabase->GetTCProcedures()->Find(pszName))); )
		{
			if ((cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile())
			{
				szCode[0].Format(STRING(IDS_TELECOMMANDPROCEDURECODE_NORMAL_FILENAME), pszName);
				szCode[1].Format(STRING(IDS_TELECOMMANDPROCEDURECODE_UPDATE_FILENAME), pszName);
				szCode[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[0];
				szCode[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[1];
				if ((cFileFind[1].FindFile(szCode[1]) && !cFileFind[1].FindNextFile()) || (cFileFind[1].FindFile(szCode[0]) && !cFileFind[1].FindNextFile()))
				{
					if ((hTCProcedure = ((hTCProcedure = AfxLoadLibrary(cFileFind[1].GetFileName())) == (HINSTANCE)NULL) ? AfxLoadLibrary(szCode[0]) : hTCProcedure))
					{
						if (nState == TCPROCEDURE_ACTIONSTATE_SUSPEND)
						{
#ifndef UNICODE
							szTCProcedure = STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE);
#else
							WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE), -1, (LPSTR)szTCProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
							szTCProcedure.ReleaseBuffer();
#endif
							if ((pSuspend = (BOOL(__cdecl *)(INT nID)) GetProcAddress(hTCProcedure, (LPCSTR)(LPCTSTR)szTCProcedure)) && (*pSuspend)(-1))
							{
								AfxFreeLibrary(hTCProcedure);
								return TRUE;
							}
						}
						if (nState == TCPROCEDURE_ACTIONSTATE_RESUME)
						{
#ifndef UNICODE
							szTCProcedure = STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE);
#else
							WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE), -1, (LPSTR)szTCProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
							szTCProcedure.ReleaseBuffer();
#endif
							if ((pResume = (BOOL(__cdecl *)(INT nID, BOOL bAuto)) GetProcAddress(hTCProcedure, (LPCSTR)(LPCTSTR)szTCProcedure)) && (*pResume)(-1, FALSE))
							{
								AfxFreeLibrary(hTCProcedure);
								return TRUE;
							}
						}
						if (nState == TCPROCEDURE_ACTIONSTATE_ABORT)
						{
#ifndef UNICODE
							szTCProcedure = STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE);
#else
							WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE), -1, (LPSTR)szTCProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
							szTCProcedure.ReleaseBuffer();
#endif
							if ((pAbort = (BOOL(__cdecl *)(INT nID)) GetProcAddress(hTCProcedure, (LPCSTR)(LPCTSTR)szTCProcedure)) && (*pAbort)(-1))
							{
								AfxFreeLibrary(hTCProcedure);
								return TRUE;
							}
						}
						AfxFreeLibrary(hTCProcedure);
					}
				}
			}
			break;
		}
		return FALSE;
	}
	for (nProcedure = 0, nProcedures = m_pTCEnvironment->EnumTCProcedures(szTCProcedures, nTCProcedureIDs, pTCProcedures), bSuccess[0] = FALSE, bSuccess[1] = TRUE; nProcedure < nProcedures; nProcedure++)
	{
		if (szTCProcedures.GetAt(nProcedure) == pszName)
		{
			if (nState == TCPROCEDURE_ACTIONSTATE_SUSPEND)
			{
#ifndef UNICODE
				szTCProcedure = STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE);
				bSuccess[0] = TRUE;
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE), -1, (LPSTR)szTCProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_SUSPENDTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szTCProcedure.ReleaseBuffer();
				bSuccess[0] = TRUE;
#endif
				if ((pSuspend = (BOOL(__cdecl *)(INT nID)) GetProcAddress((HINSTANCE)pTCProcedures.GetAt(nProcedure), (LPCSTR)(LPCTSTR)szTCProcedure)) && (*pSuspend)(nTCProcedureIDs.GetAt(nProcedure))) continue;
			}
			if (nState == TCPROCEDURE_ACTIONSTATE_RESUME)
			{
#ifndef UNICODE
				szTCProcedure = STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE);
				bSuccess[0] = TRUE;
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE), -1, (LPSTR)szTCProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_RESUMETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szTCProcedure.ReleaseBuffer();
				bSuccess[0] = TRUE;
#endif
				if ((pResume = (BOOL(__cdecl *)(INT nID, BOOL bAuto)) GetProcAddress((HINSTANCE)pTCProcedures.GetAt(nProcedure), (LPCSTR)(LPCTSTR)szTCProcedure)) && (*pResume)(nTCProcedureIDs.GetAt(nProcedure), FALSE)) continue;
			}
			if (nState == TCPROCEDURE_ACTIONSTATE_ABORT)
			{
#ifndef UNICODE
				szTCProcedure = STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE);
				bSuccess[0] = TRUE;
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE), -1, (LPSTR)szTCProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_ABORTTCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szTCProcedure.ReleaseBuffer();
				bSuccess[0] = TRUE;
#endif
				if ((pAbort = (BOOL(__cdecl *)(INT nID)) GetProcAddress((HINSTANCE)pTCProcedures.GetAt(nProcedure), (LPCSTR)(LPCTSTR)szTCProcedure)) && (*pAbort)(nTCProcedureIDs.GetAt(nProcedure)))
				{
					m_pTCEnvironment->FreeTCProcedure(nTCProcedureIDs.GetAt(nProcedure));
					continue;
				}
			}
			bSuccess[1] = FALSE;
		}
	}
	return bSuccess[0] && bSuccess[1];
}

BOOL CTCProcedureThread::SetThreadState(LPCTSTR pszName, UINT nState)
{
	CTCProcedureThread  *pThreadInfo;

	if ((pThreadInfo = GetProcess()->GetAt(GetProcess()->Find(pszName))) && pThreadInfo->IsThreadActive())
	{
		if (pThreadInfo->GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING  &&  nState == TCPROCEDURETHREAD_ACTIONSTATE_SUSPEND)
		{
			pThreadInfo->SetRunningState((pThreadInfo->Suspend()) ? TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED : pThreadInfo->GetRunningState());
			return TRUE;
		}
		if (pThreadInfo->GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED  &&  nState == TCPROCEDURETHREAD_ACTIONSTATE_RESUME)
		{
			pThreadInfo->SetRunningState((pThreadInfo->Resume()) ? TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING : pThreadInfo->GetRunningState());
			return TRUE;
		}
		if (nState == TCPROCEDURETHREAD_ACTIONSTATE_ABORT)
		{
			pThreadInfo->SetRunningState((pThreadInfo->DestroyThread() >= 0) ? TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING : pThreadInfo->GetRunningState());
			return TRUE;
		}
		if (nState == TCPROCEDURETHREAD_ACTIONSTATE_ENABLE)
		{
			pThreadInfo->EnableThread(TRUE);
			return TRUE;
		}
		if (nState == TCPROCEDURETHREAD_ACTIONSTATE_DISABLE)
		{
			pThreadInfo->EnableThread(FALSE);
			return TRUE;
		}
	}
	return FALSE;
}

VOID CTCProcedureThread::EnableThread(BOOL bEnable)
{
	if (m_bEnabled != bEnable)
	{
		for (m_bEnabled = bEnable; bEnable; )
		{
			SetEvent(m_hTMEvent);
			return;
		}
	}
}

BOOL CTCProcedureThread::IsThreadEnabled() CONST
{
	return m_bEnabled;
}

VOID CTCProcedureThread::ResetThread()
{
	ResetStepStates();
}

BOOL CTCProcedureThread::SetSynchronizationObject(CEvent &cEvent)
{
	return cEvent.SetEvent();
}
BOOL CTCProcedureThread::SetSynchronizationObject(LPCTSTR pszEvent)
{
	INT  nObject;
	INT  nObjects;
	HANDLE  hEvent;
	CPtrArray  phObjects;
	CStringArray  szObjects;

	for (nObject = 0, nObjects = GetProcess()->EnumSynchronizationObjects(szObjects, phObjects); nObject < nObjects; nObject++)
	{
		if (szObjects.GetAt(nObject) == pszEvent) break;
		continue;
	}
	return(((hEvent = (nObject < nObjects) ? (HANDLE)phObjects.GetAt(nObject) : (HANDLE)NULL)) ? SetEvent(hEvent) : FALSE);
}

BOOL CTCProcedureThread::WaitSynchronizationObject(CEvent &cEvent, DWORD dwTimeout)
{
	return((Wait(cEvent, FALSE, dwTimeout) == WAIT_OBJECT_0 + 1) ? TRUE : FALSE);
}
BOOL CTCProcedureThread::WaitSynchronizationObject(LPCTSTR pszEvent, DWORD dwTimeout)
{
	INT  nObject;
	INT  nObjects;
	HANDLE  hEvent;
	CPtrArray  phObjects;
	CStringArray  szObjects;

	for (nObject = 0, nObjects = GetProcess()->EnumSynchronizationObjects(szObjects, phObjects); nObject < nObjects; nObject++)
	{
		if (szObjects.GetAt(nObject) == pszEvent) break;
		continue;
	}
	return(((hEvent = (nObject < nObjects) ? (HANDLE)phObjects.GetAt(nObject) : (HANDLE)NULL)) ? ((Wait(hEvent, FALSE, dwTimeout) == WAIT_OBJECT_0 + 1) ? TRUE : FALSE) : FALSE);
}

BOOL CTCProcedureThread::WaitThreadActivationExpression()
{
	return FALSE;
}

BOOL CTCProcedureThread::WaitTimeInterval(DWORD dwTimeInterval)
{
	return((Wait(dwTimeInterval) == WAIT_TIMEOUT) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::WaitAbsoluteTime(CONST CTimeKey &tTime)
{
	TIMEKEY  tInterval;

	while ((tInterval = CTime::GetCurrentTime().GetTime()) < tTime.GetTime())
	{
		if (Wait(1000 * min((DWORD)(tTime.GetTime() - tInterval), SECONDSPERDAY)) == WAIT_TIMEOUT) continue;
		return FALSE;
	}
	return TRUE;
}

BOOL CTCProcedureThread::InjectAlert(LPCTSTR pszAlert)
{
	return ReportAlertMessage(pszAlert);
}

BOOL CTCProcedureThread::LogMessage(LPCTSTR pszFileName, LPCTSTR pszMessage, BOOL bPlainText, BOOL bUnicode)
{
	LONG  lData;
	DWORD  cbData;
	CFileEx  cFile;
	CString  szText;
	CLogFile  cLogFile;
	CTimeKey  tTimeKey;
	CByteArray  nData;
	OVERLAPPED  fOverlapped = { 0,0,0,0,0 };

	if (bPlainText)
	{
		if (cFile.Open(pszFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyNone))
		{
			if (LockFileEx(cFile.m_hFile, LOCKFILE_EXCLUSIVE_LOCK, 0, MAXDWORD, MAXDWORD, (LPOVERLAPPED)&fOverlapped))
			{
				for (szText = tTimeKey.FormatGmt(STRING(IDS_TELECOMMANDPROCEDURESTEP_LOGMESSAGE_TIMEFORMAT)) + TAB + pszMessage + CR + EOL, nData.SetSize((bUnicode) ? ((szText.GetLength() + 1)*sizeof(WCHAR)) : (szText.GetLength() + 1)), cFile.SeekToEnd(); TRUE; )
				{
#ifndef UNICODE
					if (!bUnicode)
					{
						CopyMemory(nData.GetData(), (LPCTSTR)szText, nData.GetSize());
						break;
					}
					MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szText, -1, (LPWSTR)nData.GetData(), szText.GetLength() + 1);
					break;
#else
					if (!bUnicode)
					{
						WideCharToMultiByte(CP_ACP, 0, szText, -1, (LPSTR)nData.GetData(), szText.GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
						break;
					}
					CopyMemory(nData.GetData(), (LPCTSTR)szText, nData.GetSize());
					break;
#endif
				}
				if ((lstrlen(pszMessage) > 0 && WriteFile(cFile.m_hFile, nData.GetData(), (DWORD)nData.GetSize() - 1, &cbData, (LPOVERLAPPED)NULL)) || (!lstrlen(pszMessage) && SetFilePointer(cFile.m_hFile, 0, &(lData = 0), FILE_BEGIN) != INVALID_SET_FILE_POINTER  &&  SetEndOfFile((HANDLE)cFile.m_hFile)))
				{
					UnlockFileEx(cFile.m_hFile, 0, MAXDWORD, MAXDWORD, &fOverlapped);
					cFile.Close();
					return TRUE;
				}
				UnlockFileEx(cFile.m_hFile, 0, MAXDWORD, MAXDWORD, &fOverlapped);
			}
			cFile.Close();
		}
		return FALSE;
	}
	if (cLogFile.Open(pszFileName, GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCLOG), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
	{
		for (nData.SetSize((lstrlen(pszMessage) + 1)*sizeof(TCHAR)), CopyMemory(nData.GetData(), pszMessage, nData.GetSize()); (lstrlen(pszMessage) > 0 && cLogFile.Write(tTimeKey, nData)) || (!lstrlen(pszMessage) && cLogFile.Reset()); )
		{
			cLogFile.Close();
			return TRUE;
		}
		cLogFile.Close();
	}
	return FALSE;
}

BOOL CTCProcedureThread::UserInteraction(UINT nType, LPCTSTR pszMessage, CONST CStringArray &szVariables, CONST CStringArray &szVariableValues)
{
	INT  nVariable;
	INT  nVariables;
	INT  nIdentifier;
	INT  nIdentifiers;
	CPtrArray  pVariables;
	CPtrArray  pIdentifiers;
	CUIntArray  nIdentifierTypes;
	CStringArray  szIdentifiers;
	CLongUIntArray  nVariableAttributes;
	CLongUIntArray  nIdentifierAttributes;
	CTCProcedureUserInteractionDialog  cUserInteractionDialog;

	for (nIdentifier = 0, nIdentifiers = GetProcess()->EnumIdentifiers(szIdentifiers, nIdentifierTypes, nIdentifierAttributes, pIdentifiers); nIdentifier < nIdentifiers; nIdentifier++)
	{
		if (nIdentifierTypes.GetAt(nIdentifier) != TCPROCEDUREPROCESS_IDENTIFIERTYPE_VARIABLE)
		{
			szIdentifiers.RemoveAt(nIdentifier);
			nIdentifierTypes.RemoveAt(nIdentifier);
			nIdentifierAttributes.RemoveAt(nIdentifier);
			pIdentifiers.RemoveAt(nIdentifier);
			nIdentifiers--;
			nIdentifier--;
		}
	}
	for (nVariable = 0, nVariables = (INT)szVariables.GetSize(); nVariable < nVariables; nVariable++)
	{
		for (nIdentifier = 0, nIdentifiers = (INT)szIdentifiers.GetSize(); nIdentifier < nIdentifiers; nIdentifier++)
		{
			if (szVariables.GetAt(nVariable) == szIdentifiers.GetAt(nIdentifier))
			{
				nVariableAttributes.SetAtGrow(nVariable, nIdentifierAttributes.GetAt(nIdentifier));
				pVariables.SetAtGrow(nVariable, pIdentifiers.GetAt(nIdentifier));
				break;
			}
		}
	}
	return((cUserInteractionDialog.DoModal(nType, pszMessage, szVariables, nVariableAttributes, pVariables, szVariableValues) == IDOK) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::ScheduleTCFunction(LPCTSTR pszName, LPCTSTR pszSequence, LPCTSTR pszFunction, BOOL bProcedure, INT nEntry, INT nEntries, CONST CTimeTag &tScheduleTime, CONST CTimeTag &tReleaseTime, DWORD dwReleaseOffset, CONST CTimeTag &tExecutionTime, DWORD dwExecutionOffset, BOOL bEarlierExecution, INT nBlockID, BOOL bGrouped, BOOL bCritical, ULONGLONG nAckFlags)
{
	CDatabaseTCProcedureThreadStep  *pStep;

	if ((pStep = FindStep(pszName)))
	{
		if (m_pTCEnvironment->AddTCFunction(GetProcess()->GetProcedureID(), GetProcess()->GetID(), GetName(), pszName, pszSequence, pszFunction, bProcedure, nEntry, nEntries, tScheduleTime, tReleaseTime, dwReleaseOffset, tExecutionTime, dwExecutionOffset, bEarlierExecution, nBlockID, bGrouped, bCritical, GetProcess()->GetAttributes() & (TCPROCEDURE_EXECUTIONMODE_AUTOMATIC | TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS | TCPROCEDURE_EXECUTIONMODE_COMMANDS), nAckFlags, (pStep->GetConfirmationType() & TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_COMMAND) ? m_hResult[0] : (HANDLE)NULL, (pStep->GetConfirmationType() & TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_COMMAND) ? m_hResult[1] : (HANDLE)NULL))
		{
			GetProcess()->EnableAutoTermination((!m_pTCProcessEngine->IsDebuggingEnabled() || bProcedure) ? GetProcess()->IsAutoTerminationEnabled() : FALSE);
			return SetEvent(m_hTCEvent);
		}
	}
	return FALSE;
}

BOOL CTCProcedureThread::InitTCFunction(LPCTSTR pszName, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch, BOOL &bAuthorization)
{
	return FALSE;
}

BOOL CTCProcedureThread::EnumTCFunctionExecutionVerificationTimeWindows(LPCTSTR pszName, INT nEntry, CUIntArray &nStages, CUIntArray &nStageTimeWindowOffsets, CUIntArray &nStageTimeWindowSizes, CUIntArray &nStageTimeWindowUncertainties) CONST
{
	return FALSE;
}

BOOL CTCProcedureThread::CheckTCFunctionPreexecutionExpression(LPCTSTR pszName, INT nEntry, CStringArray &szParameters) CONST
{
	return FALSE;
}

BOOL CTCProcedureThread::CheckTCFunctionExecutionExpression(LPCTSTR pszName, INT nEntry, CONST CDatabaseTCFunction *pTCFunction, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	return FALSE;
}

CString CTCProcedureThread::GetTMUnitTag() CONST
{
	CString  szTag;

	if (m_pTMEnvironment->Lock())
	{
		szTag = m_cTMUnit.GetTag();
		m_pTMEnvironment->Unlock();
	}
	return szTag;
}

CTimeTag CTCProcedureThread::GetTMUnitTimeTag() CONST
{
	CTimeTag  tTag;

	if (m_pTMEnvironment->Lock())
	{
		tTag = m_cTMUnit.GetTimeTag();
		m_pTMEnvironment->Unlock();
		return tTag;
	}
	return 0;
}

UINT CTCProcedureThread::GetTMUnitID() CONST
{
	UINT  nID;

	if (m_pTMEnvironment->Lock())
	{
		nID = m_cTMUnit.GetUnitID();
		m_pTMEnvironment->Unlock();
		return nID;
	}
	return -1;
}

BOOL CTCProcedureThread::GetTMUnitData(INT nBytePos, BYTE &nValue) CONST
{
	if (m_pTMEnvironment->Lock())
	{
		if (m_cTMUnit.GetData(nBytePos, nValue))
		{
			m_pTMEnvironment->Unlock();
			return TRUE;
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}
BOOL CTCProcedureThread::GetTMUnitData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST
{
	if (m_pTMEnvironment->Lock())
	{
		if (m_cTMUnit.GetData(nBytePos, nBitPos, nLength, nValue))
		{
			m_pTMEnvironment->Unlock();
			return TRUE;
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}

WORD CTCProcedureThread::GetTMUnitQuality() CONST
{
	WORD  wQuality;

	if (m_pTMEnvironment->Lock())
	{
		wQuality = m_cTMUnit.GetQuality();
		m_pTMEnvironment->Unlock();
		return wQuality;
	}
	return TMUNIT_DATAQUALITY_NONE;
}

double CTCProcedureThread::GetTotalTMBandwidth() CONST
{
	double  fTMBandwidth;

	if (m_pTMEnvironment->Lock())
	{
		fTMBandwidth = m_fTMBandwidth[0];
		m_pTMEnvironment->Unlock();
		return fTMBandwidth;
	}
	return NAN;
}

double CTCProcedureThread::GetAvailableTMBandwidth() CONST
{
	double  fTMBandwidth;

	if (m_pTMEnvironment->Lock())
	{
		fTMBandwidth = m_fTMBandwidth[1];
		m_pTMEnvironment->Unlock();
		return fTMBandwidth;
	}
	return NAN;
}

double CTCProcedureThread::GetMaxDiagnosticTMBandwidth() CONST
{
	double  fTMBandwidth;

	if (m_pTMEnvironment->Lock())
	{
		fTMBandwidth = m_fTMBandwidth[2];
		m_pTMEnvironment->Unlock();
		return fTMBandwidth;
	}
	return NAN;
}

double CTCProcedureThread::GetAvailableDiagnosticTMBandwidth() CONST
{
	double  fTMBandwidth;

	if (m_pTMEnvironment->Lock())
	{
		fTMBandwidth = m_fTMBandwidth[3];
		m_pTMEnvironment->Unlock();
		return fTMBandwidth;
	}
	return NAN;
}

CTimeTag CTCProcedureThread::GetLastTMBandwidthMeasurementTime() CONST
{
	CTimeTag  tTMBandwidth;

	if (m_pTMEnvironment->Lock())
	{
		tTMBandwidth = m_tTMBandwidth;
		m_pTMEnvironment->Unlock();
		return tTMBandwidth;
	}
	return 0;
}

ULONGLONG CTCProcedureThread::ConvertBinaryStringToValue(LPCTSTR pszValue) CONST
{
	return CDatabaseEngine::ParseValue(pszValue, 2);
}

ULONGLONG CTCProcedureThread::ConvertOctalStringToValue(LPCTSTR pszValue) CONST
{
	return CDatabaseEngine::ParseValue(pszValue, 8);
}

ULONGLONG CTCProcedureThread::ConvertHexadecimalStringToValue(LPCTSTR pszValue) CONST
{
	return CDatabaseEngine::ParseValue(pszValue, 16);
}

TIMETAG CTCProcedureThread::ConvertTimeStringToValue(LPCTSTR pszTime) CONST
{
	return CDatabaseEngine::ParseTime(pszTime);
}

BOOL CTCProcedureThread::__InitTCFunctionConstParameters(CDatabaseTCFunction *pTCFunction)
{
	INT  nElement;
	INT  nElements;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	for (nElement = 0, nElements = (INT)pTCFunction->GetSize(); nElement < nElements; nElement++)
	{
		if ((pTCFunctionElement = pTCFunction->GetAt(nElement)) && pTCFunctionElement->GetName().IsEmpty() && !pTCFunctionElement->HasConstValue())
		{
			if (pTCFunctionElement->GetAttributes() & TCFUNCTIONELEMENT_TYPE_CONSTANT)
			{
				if (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_BINARY)
				{
					pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), pTCFunctionElement->GetWidth(), CDatabaseEngine::ParseValue(pTCFunctionElement->GetConstValueAsText(), 2)));
					continue;
				}
				if (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_OCTAL)
				{
					pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), pTCFunctionElement->GetWidth(), CDatabaseEngine::ParseValue(pTCFunctionElement->GetConstValueAsText(), 8)));
					continue;
				}
				if (pTCFunctionElement->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL)
				{
					pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), pTCFunctionElement->GetWidth(), CDatabaseEngine::ParseValue(pTCFunctionElement->GetConstValueAsText(), 16)));
					continue;
				}
				if (pTCFunctionElement->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT)
				{
					pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), CDatabaseEngine::ParseValue(pTCFunctionElement->GetConstValueAsText())));
					continue;
				}
				pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), pTCFunctionElement->GetWidth(), CDatabaseEngine::ParseValue(pTCFunctionElement->GetConstValueAsText(), 10)));
			}
		}
	}
	return((nElement == nElements) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::__InitTCPacketConstParameters(CDatabaseTCPacket *pTCPacket)
{
	INT  nParameter;
	INT  nParameters;
	CDatabaseTCPacketParameter  *pTCPacketParameter;

	for (nParameter = 0, nParameters = (INT)pTCPacket->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTCPacketParameter = pTCPacket->GetAt(nParameter)) && pTCPacketParameter->GetTag().IsEmpty() && !pTCPacketParameter->HasConstValue())
		{
			if (pTCPacketParameter->GetAttributes() & TCPACKETPARAMETER_TYPE_FIXED)
			{
				if (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_BINARY)
				{
					pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), pTCPacketParameter->GetWidth(), CDatabaseEngine::ParseValue(pTCPacketParameter->GetConstValueAsText(), 2)));
					continue;
				}
				if (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_OCTAL)
				{
					pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), pTCPacketParameter->GetWidth(), CDatabaseEngine::ParseValue(pTCPacketParameter->GetConstValueAsText(), 8)));
					continue;
				}
				if (pTCPacketParameter->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL)
				{
					pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), pTCPacketParameter->GetWidth(), CDatabaseEngine::ParseValue(pTCPacketParameter->GetConstValueAsText(), 16)));
					continue;
				}
				if (pTCPacketParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT)
				{
					pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), CDatabaseEngine::ParseValue(pTCPacketParameter->GetConstValueAsText())));
					continue;
				}
				pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), pTCPacketParameter->GetWidth(), CDatabaseEngine::ParseValue(pTCPacketParameter->GetConstValueAsText(), 10)));
			}
		}
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::__CheckTCFunctionPreexecutionParameterGroup(LPCTSTR pszGroup, CStringArray &szParameters) CONST
{
	return m_pTCProcessEngine->CheckTCFunctionPreexecutionParameterGroup(m_pDatabase, m_pTMParameters, pszGroup, szParameters);
}

BOOL CTCProcedureThread::__CheckTCFunctionExecutionParameterGroup(CONST CDatabaseTCFunction *pTCFunction, LPCTSTR pszGroup, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	return m_pTCProcessEngine->CheckTCFunctionExecutionParameterGroup(m_pDatabase, m_pTMParameters, pTCFunction, pszGroup, nStageID, tStageStart, tUncertainty, szParameters);
}

BOOL CTCProcedureThread::__SetTCFunctionParameter(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nAttributes)
{
	UINT  nStatus;
	CString  szValue;
	CTimeTag  tValue;
	ULONGLONG  nValue;
	CTCParameter  *pTCParameter;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	if (nAttributes != 0)
	{
		if ((pTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
		{
			pTCFunctionElement->SetAttributes(nAttributes);
			return TRUE;
		}
		return FALSE;
	}
	if (m_pTCEnvironment->Lock())
	{
		if ((pTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
		{
			if ((pTCParameter = m_pTCEnvironment->GetTCParameters()->GetAt((pTCFunctionElement->GetRef() < 0) ? m_pTCEnvironment->GetTCParameters()->Find(pszTag) : pTCFunctionElement->GetRef())))
			{
				if (pTCParameter->GetRawValue(0, nValue, nStatus) && pTCParameter->GetValueAsText(m_pDatabase, 0, szValue))
				{
					pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), pTCFunctionElement->GetWidth(), nValue));
					pTCFunctionElement->SetConstValueAsText(szValue);
					m_pTCEnvironment->Unlock();
					return TRUE;
				}
				if (pTCParameter->GetRawValue(0, tValue, nStatus) && pTCParameter->GetValueAsText(m_pDatabase, 0, (szValue = STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME))))
				{
					if (m_pTCProcessEngine->ConvertTCParameterTimeValue(m_pDatabase, m_pTCEnvironment, pTCFunctionElement->GetName(), pTCFunctionElement->GetWidth(), tValue, nValue))
					{
						pTCFunctionElement->SetConstValueAsText(szValue);
						pTCFunctionElement->SetConstValue(nValue);
						m_pTCEnvironment->Unlock();
						return TRUE;
					}
				}
			}
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCFunctionParameterRawIntValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LONGLONG nValue)
{
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	if ((pTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
	{
		pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), (nAttributes = pTCFunctionElement->GetAttributes()), pTCFunctionElement->GetWidth(), nValue));
		pTCFunctionElement->SetConstValueAsText(cStringTools.ConvertLongIntToString(nValue, (nAttributes & TCPARAMETER_RADIX_BINARY) ? 2 : ((nAttributes & TCPARAMETER_RADIX_OCTAL) ? 8 : ((nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) ? 16 : 10))));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCFunctionParameterRawUIntValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nValue)
{
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	if ((pTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
	{
		pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), (nAttributes = pTCFunctionElement->GetAttributes()), pTCFunctionElement->GetWidth(), nValue));
		pTCFunctionElement->SetConstValueAsText(cStringTools.ConvertLongUIntToString(nValue, (nAttributes & TCPARAMETER_RADIX_BINARY) ? 2 : ((nAttributes & TCPARAMETER_RADIX_OCTAL) ? 8 : ((nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) ? 16 : 10))));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCFunctionParameterRawFloatValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, double fValue)
{
	CStringTools  cStringTools;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	if ((pTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
	{
		pTCFunctionElement->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCFunctionElement->GetAttributes(), fValue));
		pTCFunctionElement->SetConstValueAsText(cStringTools.ConvertFloatToString(fValue));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCFunctionParameterValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, double fValue, BOOL bExtrapolate)
{
	INT  nPoint;
	INT  nPoints;
	double  fRawValue;
	CStringTools  cStringTools;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCNumCalPoint  *pDatabaseTCNumCalPoint[2];
	CDatabaseTCFunctionElement  *pDatabaseTCFunctionElement;

	if ((pDatabaseTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
	{
		if ((pDatabaseTCParameter = m_pDatabase->GetTCParameters()->GetAt((pDatabaseTCFunctionElement->GetRef() < 0) ? m_pDatabase->GetTCParameters()->Find(pszTag) : pDatabaseTCFunctionElement->GetRef())))
		{
			if ((pDatabaseTCNumCalTable = ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) && (pDatabaseTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED)) ? m_pDatabase->GetTCNumCalTables()->GetAt((pDatabaseTCParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCNumCalTables()->Find(pDatabaseTCParameter->GetCalTable()) : pDatabaseTCParameter->GetCalTableRef()) : (CDatabaseTCNumCalTable *)NULL))
			{
				for (nPoint = 0, nPoints = (INT)pDatabaseTCNumCalTable->GetSize() - 1; nPoint < nPoints; nPoint++)
				{
					if ((pDatabaseTCNumCalPoint[0] = pDatabaseTCNumCalTable->GetAt(nPoint)))
					{
						if ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(nPoint + 1)))
						{
							if ((fValue >= pDatabaseTCNumCalPoint[0]->GetY() && fValue <= pDatabaseTCNumCalPoint[1]->GetY()) || (fValue <= pDatabaseTCNumCalPoint[0]->GetY() && fValue >= pDatabaseTCNumCalPoint[1]->GetY()))
							{
								fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX());
								break;
							}
						}
					}
				}
				for (; nPoint == nPoints && bExtrapolate; )
				{
					if ((pDatabaseTCNumCalPoint[0] = ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(1))) ? pDatabaseTCNumCalTable->GetAt(0) : (CDatabaseTCNumCalPoint *)NULL))
					{
						if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTCParameter->GetWidth()))
						{
							nPoint = nPoints - 1;
							break;
						}
					}
					if ((pDatabaseTCNumCalPoint[0] = ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound()))) ? pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound() - 1) : (CDatabaseTCNumCalPoint *)NULL))
					{
						if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTCParameter->GetWidth()))
						{
							nPoint = nPoints - 1;
							break;
						}
					}
					break;
				}
				if (nPoint < nPoints)
				{
					if (((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) && __SetTCFunctionParameterRawIntValue(pTCFunction, pszTag, nBytePos, nBitPos, (LONGLONG)fRawValue)) || (((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && __SetTCFunctionParameterRawUIntValue(pTCFunction, pszTag, nBytePos, nBitPos, (ULONGLONG)fRawValue)) || ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) && __SetTCFunctionParameterRawFloatValue(pTCFunction, pszTag, nBytePos, nBitPos, fRawValue)))
					{
						pDatabaseTCFunctionElement->SetConstValueAsText(cStringTools.ConvertFloatToString(fValue));
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCFunctionParameterTimeValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LPCTSTR pszTime)
{
	ULONGLONG  nValue;
	CDatabaseTCFunctionElement  *pTCFunctionElement;

	if ((pTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
	{
		if (m_pTCProcessEngine->ConvertTCParameterTimeValue(m_pDatabase, m_pTCEnvironment, pTCFunctionElement->GetName(), pTCFunctionElement->GetWidth(), pszTime, nValue))
		{
			pTCFunctionElement->SetConstValue(nValue);
			pTCFunctionElement->SetConstValueAsText(pszTime);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCFunctionParameterStringValue(CDatabaseTCFunction *pTCFunction, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LPCTSTR pszText)
{
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szValue;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pDatabaseTCTxtCalPoint;
	CDatabaseTCFunctionElement  *pDatabaseTCFunctionElement;

	if ((pDatabaseTCFunctionElement = pTCFunction->GetAt(pTCFunction->Find(pszTag, nBytePos, nBitPos))))
	{
		if ((pDatabaseTCParameter = m_pDatabase->GetTCParameters()->GetAt((pDatabaseTCFunctionElement->GetRef() < 0) ? m_pDatabase->GetTCParameters()->Find(pszTag) : pDatabaseTCFunctionElement->GetRef())))
		{
			if ((pDatabaseTCTxtCalTable = ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) && (pDatabaseTCFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED)) ? m_pDatabase->GetTCTxtCalTables()->GetAt((pDatabaseTCParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCTxtCalTables()->Find(pDatabaseTCParameter->GetCalTable()) : pDatabaseTCParameter->GetCalTableRef()) : (CDatabaseTCTxtCalTable *)NULL))
			{
				for (nPoint = 0, nPoints = (INT)pDatabaseTCTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
				{
					if ((pDatabaseTCTxtCalPoint = pDatabaseTCTxtCalTable->GetAt(nPoint)))
					{
						if ((pDatabaseTCTxtCalPoint->GetPoint(fX[0], szValue) && szValue == pszText) || (pDatabaseTCTxtCalPoint->GetRange(fX[0], fX[1], szValue) && szValue == pszText)) break;
						continue;
					}
				}
				if (nPoint < nPoints)
				{
					if (((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) && __SetTCFunctionParameterRawIntValue(pTCFunction, pszTag, nBytePos, nBitPos, (LONGLONG)fX[0])) || (((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) || (pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && __SetTCFunctionParameterRawUIntValue(pTCFunction, pszTag, nBytePos, nBitPos, (ULONGLONG)fX[0])) || ((pDatabaseTCParameter->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) && __SetTCFunctionParameterRawFloatValue(pTCFunction, pszTag, nBytePos, nBitPos, fX[0])))
					{
						pDatabaseTCFunctionElement->SetConstValueAsText(pszText);
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCPacketParameter(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nAttributes)
{
	UINT  nStatus;
	CString  szValue;
	CTimeTag  tValue;
	ULONGLONG  nValue;
	CTCParameter  *pTCParameter;
	CDatabaseTCPacketParameter  *pTCPacketParameter;

	if (nAttributes != 0)
	{
		if ((pTCPacketParameter = pTCPacket->GetAt(pTCPacket->Find(pszTag, nBytePos, nBitPos))))
		{
			pTCPacketParameter->SetAttributes(nAttributes);
			return TRUE;
		}
		return FALSE;
	}
	if (m_pTCEnvironment->Lock())
	{
		if ((pTCPacketParameter = pTCPacket->GetAt(pTCPacket->Find(pszTag, nBytePos, nBitPos))))
		{
			if ((pTCParameter = m_pTCEnvironment->GetTCParameters()->GetAt((pTCPacketParameter->GetRef() < 0) ? m_pTCEnvironment->GetTCParameters()->Find(pszTag) : pTCPacketParameter->GetRef())))
			{
				if (pTCParameter->GetRawValue(0, nValue, nStatus) && pTCParameter->GetValueAsText(m_pDatabase, 0, szValue))
				{
					pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), pTCPacketParameter->GetWidth(), nValue));
					pTCPacketParameter->SetConstValueAsText(szValue);
					m_pTCEnvironment->Unlock();
					return TRUE;
				}
				if (pTCParameter->GetRawValue(0, tValue, nStatus) && pTCParameter->GetValueAsText(m_pDatabase, 0, (szValue = STRING(IDS_DATABASE_DATAFORMAT_ABSOLUTETIME))))
				{
					if (m_pTCProcessEngine->ConvertTCParameterTimeValue(m_pDatabase, m_pTCEnvironment, pTCPacketParameter->GetTag(), pTCPacketParameter->GetWidth(), tValue, nValue))
					{
						pTCPacketParameter->SetConstValueAsText(szValue);
						pTCPacketParameter->SetConstValue(nValue);
						m_pTCEnvironment->Unlock();
						return TRUE;
					}
				}
			}
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCPacketParameterRawIntValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LONGLONG nValue)
{
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCPacketParameter  *pTCPacketParameter;

	if ((pTCPacketParameter = pTCPacket->GetAt(pTCPacket->Find(pszTag, nBytePos, nBitPos))))
	{
		pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), (nAttributes = pTCPacketParameter->GetAttributes()), pTCPacketParameter->GetWidth(), nValue));
		pTCPacketParameter->SetConstValueAsText(cStringTools.ConvertLongIntToString(nValue, (nAttributes & TCPARAMETER_RADIX_BINARY) ? 2 : ((nAttributes & TCPARAMETER_RADIX_OCTAL) ? 8 : ((nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) ? 16 : 10))));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCPacketParameterRawUIntValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, ULONGLONG nValue)
{
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CDatabaseTCPacketParameter  *pTCPacketParameter;

	if ((pTCPacketParameter = pTCPacket->GetAt(pTCPacket->Find(pszTag, nBytePos, nBitPos))))
	{
		pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), (nAttributes = pTCPacketParameter->GetAttributes()), pTCPacketParameter->GetWidth(), nValue));
		pTCPacketParameter->SetConstValueAsText(cStringTools.ConvertLongUIntToString(nValue, (nAttributes & TCPARAMETER_RADIX_BINARY) ? 2 : ((nAttributes & TCPARAMETER_RADIX_OCTAL) ? 8 : ((nAttributes & TCPARAMETER_RADIX_HEXADECIMAL) ? 16 : 10))));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCPacketParameterRawFloatValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, double fValue)
{
	CStringTools  cStringTools;
	CDatabaseTCPacketParameter  *pTCPacketParameter;

	if ((pTCPacketParameter = pTCPacket->GetAt(pTCPacket->Find(pszTag, nBytePos, nBitPos))))
	{
		pTCPacketParameter->SetConstValue(CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCPacketParameter->GetAttributes(), fValue));
		pTCPacketParameter->SetConstValueAsText(cStringTools.ConvertFloatToString(fValue));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetTCPacketParameterRawTimeValue(CDatabaseTCPacket *pTCPacket, LPCTSTR pszTag, INT nBytePos, INT nBitPos, LPCTSTR pszTime)
{
	ULONGLONG  nValue;
	CDatabaseTCPacketParameter  *pTCPacketParameter;

	if ((pTCPacketParameter = pTCPacket->GetAt(pTCPacket->Find(pszTag, nBytePos, nBitPos))))
	{
		if (m_pTCProcessEngine->ConvertTCParameterTimeValue(m_pDatabase, m_pTCEnvironment, pTCPacketParameter->GetTag(), pTCPacketParameter->GetWidth(), pszTime, nValue))
		{
			pTCPacketParameter->SetConstValue(nValue);
			pTCPacketParameter->SetConstValueAsText(pszTime);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProcedureThread::__SetRawIntValue(CTCParameter *pTCParameter, INT nOccurrence, LONGLONG nValue)
{
	CDatabaseTCParameter  *pParameter;

	if (m_pTCEnvironment->Lock())
	{
		if ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag()))) && pTCParameter->SetRawValue(nOccurrence, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), nValue), m_pTCProcessEngine->CheckTCParameterOolStatus(m_pDatabase, pParameter, pTCParameter, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), nValue))))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

LONGLONG CTCProcedureThread::__GetRawIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (!pTCParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTCEnvironment->Unlock();
			return 0;
		}
		m_pTCEnvironment->Unlock();
		return((LONGLONG)nValue);
	}
	return 0;
}
LONGLONG CTCProcedureThread::__GetRawIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return((LONGLONG)nValue);
	}
	return 0;
}

BOOL CTCProcedureThread::__SetRawUIntValue(CTCParameter *pTCParameter, INT nOccurrence, ULONGLONG nValue)
{
	CDatabaseTCParameter  *pParameter;

	if (m_pTCEnvironment->Lock())
	{
		if ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag()))) && pTCParameter->SetRawValue(nOccurrence, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), nValue), m_pTCProcessEngine->CheckTCParameterOolStatus(m_pDatabase, pParameter, pTCParameter, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), pParameter->GetWidth(), nValue))))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

ULONGLONG CTCProcedureThread::__GetRawUIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (!pTCParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTCEnvironment->Unlock();
			return 0;
		}
		m_pTCEnvironment->Unlock();
		return nValue;
	}
	return 0;
}
ULONGLONG CTCProcedureThread::__GetRawUIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return nValue;
	}
	return 0;
}

BOOL CTCProcedureThread::__SetRawFloatValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue)
{
	CDatabaseTCParameter  *pParameter;

	if (m_pTCEnvironment->Lock())
	{
		if ((pParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag()))) && pTCParameter->SetRawValue(nOccurrence, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), fValue), m_pTCProcessEngine->CheckTCParameterOolStatus(m_pDatabase, pParameter, pTCParameter, CDatabaseEngine::EncodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), fValue))))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

double CTCProcedureThread::__GetRawFloatValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	double  fValue;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (pTCParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			fValue = CDatabaseEngine::DecodeValue(m_pDatabase->GetType(), pTCParameter->GetAttributes(), nValue);
			m_pTCEnvironment->Unlock();
			return fValue;
		}
		szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
		GetProcess()->ReportWarningMessage(GetName(), szMessage);
		m_pTCEnvironment->Unlock();
	}
	return 0.0;
}
double CTCProcedureThread::__GetRawFloatValue(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	double  fValue;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (pTMParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			fValue = CDatabaseEngine::DecodeValue(m_pDatabase->GetType(), pTMParameter->GetAttributes(), nValue, FALSE);
			m_pTMEnvironment->Unlock();
			return fValue;
		}
		szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
		GetProcess()->ReportWarningMessage(GetName(), szMessage);
		m_pTMEnvironment->Unlock();
	}
	return 0.0;
}

BOOL CTCProcedureThread::__SetIntValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue)
{
	if (m_pTCEnvironment->Lock())
	{
		if (__SetRawIntValue(pTCParameter, nOccurrence, __DecalibrateToIntValue(pTCParameter, fValue)))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

LONGLONG CTCProcedureThread::__GetIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (!pTCParameter->GetValue(m_pDatabase, nOccurrence, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTCEnvironment->Unlock();
			return 0;
		}
		m_pTCEnvironment->Unlock();
		return((LONGLONG)fValue);
	}
	return 0;
}
LONGLONG CTCProcedureThread::__GetIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetValue(m_pDatabase, nOccurrence, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return((LONGLONG)fValue);
	}
	return 0;
}

BOOL CTCProcedureThread::__SetUIntValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue)
{
	if (m_pTCEnvironment->Lock())
	{
		if (__SetRawUIntValue(pTCParameter, nOccurrence, __DecalibrateToUIntValue(pTCParameter, fValue)))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

ULONGLONG CTCProcedureThread::__GetUIntValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (!pTCParameter->GetValue(m_pDatabase, nOccurrence, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTCEnvironment->Unlock();
			return 0;
		}
		m_pTCEnvironment->Unlock();
		return((ULONGLONG)fValue);
	}
	return 0;
}
ULONGLONG CTCProcedureThread::__GetUIntValue(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetValue(m_pDatabase, nOccurrence, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return((ULONGLONG)fValue);
	}
	return 0;
}

BOOL CTCProcedureThread::__SetFloatValue(CTCParameter *pTCParameter, INT nOccurrence, double fValue)
{
	if (m_pTCEnvironment->Lock())
	{
		if (__SetRawFloatValue(pTCParameter, nOccurrence, __DecalibrateToFloatValue(pTCParameter, fValue)))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

double CTCProcedureThread::__GetFloatValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (!pTCParameter->GetValue(m_pDatabase, nOccurrence, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTCEnvironment->Unlock();
			return 0.0;
		}
		m_pTCEnvironment->Unlock();
		return fValue;
	}
	return 0.0;
}
double CTCProcedureThread::__GetFloatValue(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetValue(m_pDatabase, nOccurrence, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0.0;
		}
		m_pTMEnvironment->Unlock();
		return fValue;
	}
	return 0.0;
}

BOOL CTCProcedureThread::__SetTimeValue(CTCParameter *pTCParameter, INT nOccurrence, CONST CTimeTag &tTime)
{
	if (m_pTCEnvironment->Lock())
	{
		if (pTCParameter->SetRawValue(nOccurrence, tTime))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

CTimeTag CTCProcedureThread::__GetTimeValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	CTimeTag  tTime;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (!pTCParameter->GetRawValue(nOccurrence, tTime, nStatus))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTCEnvironment->Unlock();
			return 0;
		}
		m_pTCEnvironment->Unlock();
		return tTime;
	}
	return 0;
}

BOOL CTCProcedureThread::__SetStringValue(CTCParameter *pTCParameter, INT nOccurrence, LPCTSTR pszText)
{
	ULONGLONG  nAttributes;
	CString  szValue;

	if (m_pTCEnvironment->Lock())
	{
		if ((((nAttributes = pTCParameter->GetAttributes()) & TCPARAMETER_CODING_SIGNEDINTEGER) && __SetRawIntValue(pTCParameter, nOccurrence, __DecalibrateToIntValue(pTCParameter, pszText))) || (((nAttributes & TCPARAMETER_CODING_BITPATTERN) || (nAttributes & TCPARAMETER_CODING_UNSIGNEDINTEGER)) && __SetRawUIntValue(pTCParameter, nOccurrence, __DecalibrateToUIntValue(pTCParameter, pszText))) || ((nAttributes & TCPARAMETER_CODING_FLOATINGPOINT) && __SetRawFloatValue(pTCParameter, nOccurrence, __DecalibrateToFloatValue(pTCParameter, pszText))) || ((nAttributes & TCPARAMETER_CODING_TIME) && __SetTimeValue(pTCParameter, nOccurrence, ConvertTimeStringToValue(pszText))))
		{
			if (pTCParameter->GetValueAsText(m_pDatabase, nOccurrence, szValue) && szValue == pszText)
			{
				m_pTCEnvironment->Unlock();
				return TRUE;
			}
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

CString CTCProcedureThread::__GetStringValue(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	CString  szValue;
	CString  szMessage;

	if (m_pTCEnvironment->Lock())
	{
		if (!pTCParameter->GetValueAsText(m_pDatabase, nOccurrence, szValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TCPARAMETERVALUE_MISSING), (LPCTSTR)pTCParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
		}
		m_pTCEnvironment->Unlock();
	}
	return szValue;
}
CString CTCProcedureThread::__GetStringValue(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	CString  szValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetValueAsText(m_pDatabase, nOccurrence, szValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
		}
		m_pTMEnvironment->Unlock();
	}
	return szValue;
}

CTimeTag CTCProcedureThread::__GetValueTime(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;
	CTimeTag  tValue;

	if (m_pTMEnvironment->Lock())
	{
		for (tValue = pTMParameter->GetValueTime(nOccurrence); !pTMParameter->GetRawValue(nOccurrence, nValue, nStatus); )
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			tValue = 0;
			break;
		}
		m_pTMEnvironment->Unlock();
		return tValue;
	}
	return 0;
}

LONGLONG CTCProcedureThread::__GetPastRawIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetPastRawValue(nSample, nValue, nStatus))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return((LONGLONG)nValue);
	}
	return 0;
}

ULONGLONG CTCProcedureThread::__GetPastRawUIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetPastRawValue(nSample, nValue, nStatus))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return nValue;
	}
	return 0;
}

double CTCProcedureThread::__GetPastRawFloatValue(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	UINT  nStatus;
	double  fValue;
	ULONGLONG  nValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (pTMParameter->GetPastRawValue(nSample, nValue, nStatus))
		{
			fValue = CDatabaseEngine::DecodeValue(m_pDatabase->GetType(), pTMParameter->GetAttributes(), nValue, FALSE);
			m_pTMEnvironment->Unlock();
			return fValue;
		}
		szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
		GetProcess()->ReportWarningMessage(GetName(), szMessage);
		m_pTMEnvironment->Unlock();
	}
	return 0.0;
}

LONGLONG CTCProcedureThread::__GetPastIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetPastValue(m_pDatabase, nSample, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return((LONGLONG)fValue);
	}
	return 0;
}

ULONGLONG CTCProcedureThread::__GetPastUIntValue(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetPastValue(m_pDatabase, nSample, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0;
		}
		m_pTMEnvironment->Unlock();
		return((ULONGLONG)fValue);
	}
	return 0;
}

double CTCProcedureThread::__GetPastFloatValue(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	double  fValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetPastValue(m_pDatabase, nSample, fValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			m_pTMEnvironment->Unlock();
			return 0.0;
		}
		m_pTMEnvironment->Unlock();
		return fValue;
	}
	return 0.0;
}

CString CTCProcedureThread::__GetPastStringValue(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	CString  szValue;
	CString  szMessage;

	if (m_pTMEnvironment->Lock())
	{
		if (!pTMParameter->GetPastValueAsText(m_pDatabase, nSample, szValue))
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
		}
		m_pTMEnvironment->Unlock();
	}
	return szValue;
}

CTimeTag CTCProcedureThread::__GetPastValueTime(CONST CTMParameter *pTMParameter, INT nSample) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;
	CString  szMessage;
	CTimeTag  tValue;

	if (m_pTMEnvironment->Lock())
	{
		for (tValue = pTMParameter->GetValueTime(nSample, TRUE); !pTMParameter->GetPastRawValue(nSample, nValue, nStatus); )
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TMPARAMETERPASTVALUE_MISSING), (LPCTSTR)pTMParameter->GetTag());
			GetProcess()->ReportWarningMessage(GetName(), szMessage);
			tValue = 0;
			break;
		}
		m_pTMEnvironment->Unlock();
		return tValue;
	}
	return 0;
}

LONGLONG CTCProcedureThread::__CalculateAverageIntValue(CONST CTMParameter *pTMParameter, INT nSamples) CONST
{
	INT  nSample;
	UINT  nStatus;
	LONGLONG  lValue;
	ULONGLONG  nValue;

	if (nSamples > 0)
	{
		for (m_pTMEnvironment->Lock(), nSample = 0, lValue = 0; nSample < nSamples; nSample++)
		{
			if (pTMParameter->GetPastRawValue(nSample + 1, nValue, nStatus))
			{
				lValue += __GetPastIntValue(pTMParameter, nSample + 1);
				continue;
			}
			break;
		}
		if (nSample > 0)
		{
			m_pTMEnvironment->Unlock();
			return((LONGLONG)(lValue / nSample));
		}
		m_pTMEnvironment->Unlock();
	}
	return __GetIntValue(pTMParameter);
}

ULONGLONG CTCProcedureThread::__CalculateAverageUIntValue(CONST CTMParameter *pTMParameter, INT nSamples) CONST
{
	INT  nSample;
	UINT  nStatus;
	ULONGLONG  nValue;
	DWORDLONG  dwValue;

	if (nSamples > 0)
	{
		for (m_pTMEnvironment->Lock(), nSample = 0, dwValue = 0; nSample < nSamples; nSample++)
		{
			if (pTMParameter->GetPastRawValue(nSample + 1, nValue, nStatus))
			{
				dwValue += __GetPastUIntValue(pTMParameter, nSample + 1);
				continue;
			}
			break;
		}
		if (nSample > 0)
		{
			m_pTMEnvironment->Unlock();
			return((ULONGLONG)(dwValue / nSample));
		}
		m_pTMEnvironment->Unlock();
	}
	return __GetUIntValue(pTMParameter);
}

double CTCProcedureThread::__CalculateAverageFloatValue(CONST CTMParameter *pTMParameter, INT nSamples) CONST
{
	INT  nSample;
	UINT  nStatus;
	double  fValue;
	ULONGLONG  nValue;

	if (nSamples > 0)
	{
		for (m_pTMEnvironment->Lock(), nSample = 0, fValue = 0.0; nSample < nSamples; nSample++)
		{
			if (pTMParameter->GetPastRawValue(nSample + 1, nValue, nStatus))
			{
				fValue += __GetPastFloatValue(pTMParameter, nSample + 1);
				continue;
			}
			break;
		}
		if (nSample > 0)
		{
			m_pTMEnvironment->Unlock();
			return fValue / (double)nSample;
		}
		m_pTMEnvironment->Unlock();
	}
	return __GetFloatValue(pTMParameter);
}

UINT CTCProcedureThread::__GetValueStatus(CONST CTMParameter *pTMParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;

	if (m_pTMEnvironment->Lock())
	{
		if (pTMParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			m_pTMEnvironment->Unlock();
			return nStatus;
		}
		m_pTMEnvironment->Unlock();
	}
	return TMPARAMETER_STATUS_NONE;
}
UINT CTCProcedureThread::__GetValueStatus(CONST CTCParameter *pTCParameter, INT nOccurrence) CONST
{
	UINT  nStatus;
	ULONGLONG  nValue;

	if (m_pTMEnvironment->Lock())
	{
		if (pTCParameter->GetRawValue(nOccurrence, nValue, nStatus))
		{
			m_pTMEnvironment->Unlock();
			return nStatus;
		}
		m_pTMEnvironment->Unlock();
	}
	return TCPARAMETER_STATUS_NONE;
}

LONGLONG CTCProcedureThread::__DecalibrateToIntValue(CONST CTCParameter *pTCParameter, double fValue) CONST
{
	return((LONGLONG)__DecalibrateToFloatValue(pTCParameter, fValue));
}
LONGLONG CTCProcedureThread::__DecalibrateToIntValue(CONST CTCParameter *pTCParameter, LPCTSTR pszValue) CONST
{
	return((LONGLONG)__DecalibrateToFloatValue(pTCParameter, pszValue));
}

ULONGLONG CTCProcedureThread::__DecalibrateToUIntValue(CONST CTCParameter *pTCParameter, double fValue) CONST
{
	return((ULONGLONG)__DecalibrateToFloatValue(pTCParameter, fValue));
}
ULONGLONG CTCProcedureThread::__DecalibrateToUIntValue(CONST CTCParameter *pTCParameter, LPCTSTR pszValue) CONST
{
	return((ULONGLONG)__DecalibrateToFloatValue(pTCParameter, pszValue));
}

double CTCProcedureThread::__DecalibrateToFloatValue(CONST CTCParameter *pTCParameter, double fValue) CONST
{
	INT  nPoint;
	INT  nPoints;
	double  fRawValue;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCNumCalPoint  *pDatabaseTCNumCalPoint[2];

	if ((pDatabaseTCNumCalTable = ((pDatabaseTCParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag()))) && (pTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? ((pDatabaseTCParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCNumCalTables()->GetAt(m_pDatabase->GetTCNumCalTables()->Find(pDatabaseTCParameter->GetCalTable())) : m_pDatabase->GetTCNumCalTables()->GetAt(pDatabaseTCParameter->GetCalTableRef())) : (CDatabaseTCNumCalTable *)NULL))
	{
		for (nPoint = 0, nPoints = (INT)pDatabaseTCNumCalTable->GetSize() - 1; nPoint < nPoints; nPoint++)
		{
			if ((pDatabaseTCNumCalPoint[0] = pDatabaseTCNumCalTable->GetAt(nPoint)))
			{
				if ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(nPoint + 1)))
				{
					if ((fValue >= pDatabaseTCNumCalPoint[0]->GetY() && fValue <= pDatabaseTCNumCalPoint[1]->GetY()) || (fValue <= pDatabaseTCNumCalPoint[0]->GetY() && fValue >= pDatabaseTCNumCalPoint[1]->GetY()))
					{
						fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX());
						break;
					}
				}
			}
		}
		for (; nPoint == nPoints; )
		{
			if ((pTCParameter->GetAttributes() & TCPARAMETER_INTERPRETATION_FULL) == 0)
			{
				if ((pDatabaseTCNumCalPoint[0] = ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt(1))) ? pDatabaseTCNumCalTable->GetAt(0) : (CDatabaseTCNumCalPoint *)NULL))
				{
					if ((pDatabaseTCNumCalPoint[0]->GetY() < pDatabaseTCNumCalPoint[1]->GetY() && fValue < pDatabaseTCNumCalPoint[0]->GetY()) || ((pDatabaseTCNumCalPoint[0]->GetY() > pDatabaseTCNumCalPoint[1]->GetY()) && fValue > pDatabaseTCNumCalPoint[0]->GetY()))
					{
						if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTCParameter->GetWidth()))
						{
							nPoint = nPoints - 1;
							break;
						}
					}
				}
				if ((pDatabaseTCNumCalPoint[0] = ((pDatabaseTCNumCalPoint[1] = pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound()))) ? pDatabaseTCNumCalTable->GetAt((INT)pDatabaseTCNumCalTable->GetUpperBound() - 1) : (CDatabaseTCNumCalPoint *)NULL))
				{
					if ((pDatabaseTCNumCalPoint[0]->GetY() < pDatabaseTCNumCalPoint[1]->GetY() && fValue > pDatabaseTCNumCalPoint[1]->GetY()) || (pDatabaseTCNumCalPoint[0]->GetY() > pDatabaseTCNumCalPoint[1]->GetY() && fValue < pDatabaseTCNumCalPoint[1]->GetY()))
					{
						if ((fRawValue = pDatabaseTCNumCalPoint[0]->GetX() + ((fValue - pDatabaseTCNumCalPoint[0]->GetY()) / (pDatabaseTCNumCalPoint[1]->GetY() - pDatabaseTCNumCalPoint[0]->GetY()))*(pDatabaseTCNumCalPoint[1]->GetX() - pDatabaseTCNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTCParameter->GetWidth()))
						{
							nPoint = nPoints - 1;
							break;
						}
					}
				}
			}
			break;
		}
		return((nPoint < nPoints) ? fRawValue : 0.0);
	}
	return fValue;
}
double CTCProcedureThread::__DecalibrateToFloatValue(CONST CTCParameter *pTCParameter, LPCTSTR pszValue) CONST
{
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szValue;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCTxtCalPoint  *pDatabaseTCTxtCalPoint;

	if ((pDatabaseTCTxtCalTable = ((pDatabaseTCParameter = m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pTCParameter->GetTag()))) && (pTCParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? ((pDatabaseTCParameter->GetCalTableRef() < 0) ? m_pDatabase->GetTCTxtCalTables()->GetAt(m_pDatabase->GetTCTxtCalTables()->Find(pDatabaseTCParameter->GetCalTable())) : m_pDatabase->GetTCTxtCalTables()->GetAt(pDatabaseTCParameter->GetCalTableRef())) : (CDatabaseTCTxtCalTable *)NULL))
	{
		for (nPoint = 0, nPoints = (INT)pDatabaseTCTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
		{
			if ((pDatabaseTCTxtCalPoint = pDatabaseTCTxtCalTable->GetAt(nPoint)))
			{
				if ((pDatabaseTCTxtCalPoint->GetPoint(fX[0], szValue) && szValue == pszValue) || (pDatabaseTCTxtCalPoint->GetRange(fX[0], fX[1], szValue) && szValue == pszValue)) break;
				continue;
			}
		}
		return((nPoint < nPoints) ? fX[0] : 0.0);
	}
	return 0.0;
}

LONGLONG CTCProcedureThread::__CheckArgumentIntValueRange(LPCTSTR pszArgument, LONGLONG nValue) CONST
{
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CDatabaseTCProcedureArguments  pDatabaseTCProcedureArguments;

	if ((pDatabaseTCProcedureArgument = (GetProcess()->GetArguments(pDatabaseTCProcedureArguments) > 0) ? pDatabaseTCProcedureArguments.GetAt(pDatabaseTCProcedureArguments.Find(pszArgument)) : (CDatabaseTCProcedureArgument *)NULL))
	{
		if (!pDatabaseTCProcedureArgument->GetMinValueAsText().IsEmpty() && nValue < (LONGLONG)pDatabaseTCProcedureArgument->GetMinValue()) nValue = (LONGLONG)pDatabaseTCProcedureArgument->GetMinValue();
		if (!pDatabaseTCProcedureArgument->GetMaxValueAsText().IsEmpty() && nValue >(LONGLONG) pDatabaseTCProcedureArgument->GetMaxValue()) nValue = (LONGLONG)pDatabaseTCProcedureArgument->GetMaxValue();
	}
	return nValue;
}

ULONGLONG CTCProcedureThread::__CheckArgumentUIntValueRange(LPCTSTR pszArgument, ULONGLONG nValue) CONST
{
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CDatabaseTCProcedureArguments  pDatabaseTCProcedureArguments;

	if ((pDatabaseTCProcedureArgument = (GetProcess()->GetArguments(pDatabaseTCProcedureArguments) > 0) ? pDatabaseTCProcedureArguments.GetAt(pDatabaseTCProcedureArguments.Find(pszArgument)) : (CDatabaseTCProcedureArgument *)NULL))
	{
		if (!pDatabaseTCProcedureArgument->GetMinValueAsText().IsEmpty() && nValue < pDatabaseTCProcedureArgument->GetMinValue()) nValue = pDatabaseTCProcedureArgument->GetMinValue();
		if (!pDatabaseTCProcedureArgument->GetMaxValueAsText().IsEmpty() && nValue > pDatabaseTCProcedureArgument->GetMaxValue()) nValue = pDatabaseTCProcedureArgument->GetMaxValue();
	}
	return nValue;
}

double CTCProcedureThread::__CheckArgumentFloatValueRange(LPCTSTR pszArgument, double fValue) CONST
{
	double  fRange[2];
	ULONGLONG  nValue;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CDatabaseTCProcedureArguments  pDatabaseTCProcedureArguments;

	if ((pDatabaseTCProcedureArgument = (GetProcess()->GetArguments(pDatabaseTCProcedureArguments) > 0) ? pDatabaseTCProcedureArguments.GetAt(pDatabaseTCProcedureArguments.Find(pszArgument)) : (CDatabaseTCProcedureArgument *)NULL))
	{
		for (CopyMemory(&fRange[0], &(nValue = pDatabaseTCProcedureArgument->GetMinValue()), sizeof(fRange[0])); !pDatabaseTCProcedureArgument->GetMinValueAsText().IsEmpty(); )
		{
			fValue = (fValue < fRange[0]) ? fRange[0] : fValue;
			break;
		}
		for (CopyMemory(&fRange[1], &(nValue = pDatabaseTCProcedureArgument->GetMaxValue()), sizeof(fRange[1])); !pDatabaseTCProcedureArgument->GetMaxValueAsText().IsEmpty(); )
		{
			fValue = (fValue > fRange[1]) ? fRange[1] : fValue;
			break;
		}
	}
	return fValue;
}

CString CTCProcedureThread::__CheckArgumentTextRange(LPCTSTR pszArgument, LPCTSTR pszText) CONST
{
	CString  szText;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CDatabaseTCProcedureArguments  pDatabaseTCProcedureArguments;

	for (szText = pszText; (pDatabaseTCProcedureArgument = (GetProcess()->GetArguments(pDatabaseTCProcedureArguments) > 0) ? pDatabaseTCProcedureArguments.GetAt(pDatabaseTCProcedureArguments.Find(pszArgument)) : (CDatabaseTCProcedureArgument *)NULL); )
	{
		if (!pDatabaseTCProcedureArgument->GetMinValueAsText().IsEmpty() && pDatabaseTCProcedureArgument->GetMinValueAsText() > pszText) szText = pDatabaseTCProcedureArgument->GetMinValueAsText();
		if (!pDatabaseTCProcedureArgument->GetMaxValueAsText().IsEmpty() && pDatabaseTCProcedureArgument->GetMaxValueAsText() < pszText) szText = pDatabaseTCProcedureArgument->GetMaxValueAsText();
		break;
	}
	return szText;
}

TIMETAG CTCProcedureThread::__CheckArgumentTimeRange(LPCTSTR pszArgument, TIMETAG tTime) CONST
{
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;
	CDatabaseTCProcedureArguments  pDatabaseTCProcedureArguments;

	if ((pDatabaseTCProcedureArgument = (GetProcess()->GetArguments(pDatabaseTCProcedureArguments) > 0) ? pDatabaseTCProcedureArguments.GetAt(pDatabaseTCProcedureArguments.Find(pszArgument)) : (CDatabaseTCProcedureArgument *)NULL))
	{
		if (!pDatabaseTCProcedureArgument->GetMinValueAsText().IsEmpty() && tTime < ConvertTimeStringToValue(pDatabaseTCProcedureArgument->GetMinValueAsText())) tTime = ConvertTimeStringToValue(pDatabaseTCProcedureArgument->GetMinValueAsText());
		if (!pDatabaseTCProcedureArgument->GetMaxValueAsText().IsEmpty() && tTime > ConvertTimeStringToValue(pDatabaseTCProcedureArgument->GetMaxValueAsText())) tTime = ConvertTimeStringToValue(pDatabaseTCProcedureArgument->GetMaxValueAsText());
	}
	return tTime;
}

LONGLONG CTCProcedureThread::__CheckVariableIntValueRange(LPCTSTR pszVariable, LONGLONG nValue) CONST
{
	CDatabaseTCProcedureVariable  *pDatabaseTCProcedureVariable;
	CDatabaseTCProcedureVariables  pDatabaseTCProcedureVariables;

	if ((pDatabaseTCProcedureVariable = (GetProcess()->GetVariables(pDatabaseTCProcedureVariables) > 0) ? pDatabaseTCProcedureVariables.GetAt(pDatabaseTCProcedureVariables.Find(pszVariable)) : (CDatabaseTCProcedureVariable *)NULL))
	{
		if (!pDatabaseTCProcedureVariable->GetMinValueAsText().IsEmpty() && nValue < (LONGLONG)pDatabaseTCProcedureVariable->GetMinValue()) nValue = (LONGLONG)pDatabaseTCProcedureVariable->GetMinValue();
		if (!pDatabaseTCProcedureVariable->GetMaxValueAsText().IsEmpty() && nValue >(LONGLONG) pDatabaseTCProcedureVariable->GetMaxValue()) nValue = (LONGLONG)pDatabaseTCProcedureVariable->GetMaxValue();
	}
	return nValue;
}

ULONGLONG CTCProcedureThread::__CheckVariableUIntValueRange(LPCTSTR pszVariable, ULONGLONG nValue) CONST
{
	CDatabaseTCProcedureVariable  *pDatabaseTCProcedureVariable;
	CDatabaseTCProcedureVariables  pDatabaseTCProcedureVariables;

	if ((pDatabaseTCProcedureVariable = (GetProcess()->GetVariables(pDatabaseTCProcedureVariables) > 0) ? pDatabaseTCProcedureVariables.GetAt(pDatabaseTCProcedureVariables.Find(pszVariable)) : (CDatabaseTCProcedureVariable *)NULL))
	{
		if (!pDatabaseTCProcedureVariable->GetMinValueAsText().IsEmpty() && nValue < pDatabaseTCProcedureVariable->GetMinValue()) nValue = pDatabaseTCProcedureVariable->GetMinValue();
		if (!pDatabaseTCProcedureVariable->GetMaxValueAsText().IsEmpty() && nValue > pDatabaseTCProcedureVariable->GetMaxValue()) nValue = pDatabaseTCProcedureVariable->GetMaxValue();
	}
	return nValue;
}

double CTCProcedureThread::__CheckVariableFloatValueRange(LPCTSTR pszVariable, double fValue) CONST
{
	double  fRange[2];
	ULONGLONG  nValue;
	CDatabaseTCProcedureVariable  *pDatabaseTCProcedureVariable;
	CDatabaseTCProcedureVariables  pDatabaseTCProcedureVariables;

	if ((pDatabaseTCProcedureVariable = (GetProcess()->GetVariables(pDatabaseTCProcedureVariables) > 0) ? pDatabaseTCProcedureVariables.GetAt(pDatabaseTCProcedureVariables.Find(pszVariable)) : (CDatabaseTCProcedureVariable *)NULL))
	{
		for (CopyMemory(&fRange[0], &(nValue = pDatabaseTCProcedureVariable->GetMinValue()), sizeof(fRange[0])); !pDatabaseTCProcedureVariable->GetMinValueAsText().IsEmpty(); )
		{
			fValue = (fValue < fRange[0]) ? fRange[0] : fValue;
			break;
		}
		for (CopyMemory(&fRange[1], &(nValue = pDatabaseTCProcedureVariable->GetMaxValue()), sizeof(fRange[0])); !pDatabaseTCProcedureVariable->GetMaxValueAsText().IsEmpty(); )
		{
			fValue = (fValue > fRange[1]) ? fRange[1] : fValue;
			break;
		}
	}
	return fValue;
}

CString CTCProcedureThread::__CheckVariableTextRange(LPCTSTR pszVariable, LPCTSTR pszText) CONST
{
	CString  szText;
	CDatabaseTCProcedureVariable  *pDatabaseTCProcedureVariable;
	CDatabaseTCProcedureVariables  pDatabaseTCProcedureVariables;

	for (szText = pszText; (pDatabaseTCProcedureVariable = (GetProcess()->GetVariables(pDatabaseTCProcedureVariables) > 0) ? pDatabaseTCProcedureVariables.GetAt(pDatabaseTCProcedureVariables.Find(pszVariable)) : (CDatabaseTCProcedureVariable *)NULL); )
	{
		if (!pDatabaseTCProcedureVariable->GetMinValueAsText().IsEmpty() && pDatabaseTCProcedureVariable->GetMinValueAsText() > pszText) szText = pDatabaseTCProcedureVariable->GetMinValueAsText();
		if (!pDatabaseTCProcedureVariable->GetMaxValueAsText().IsEmpty() && pDatabaseTCProcedureVariable->GetMaxValueAsText() < pszText) szText = pDatabaseTCProcedureVariable->GetMaxValueAsText();
		break;
	}
	return szText;
}

TIMETAG CTCProcedureThread::__CheckVariableTimeRange(LPCTSTR pszVariable, TIMETAG tTime) CONST
{
	CDatabaseTCProcedureVariable  *pDatabaseTCProcedureVariable;
	CDatabaseTCProcedureVariables  pDatabaseTCProcedureVariables;

	if ((pDatabaseTCProcedureVariable = (pDatabaseTCProcedureVariable = (GetProcess()->GetVariables(pDatabaseTCProcedureVariables) > 0) ? pDatabaseTCProcedureVariables.GetAt(pDatabaseTCProcedureVariables.Find(pszVariable)) : (CDatabaseTCProcedureVariable *)NULL)))
	{
		if (!pDatabaseTCProcedureVariable->GetMinValueAsText().IsEmpty() && tTime < ConvertTimeStringToValue(pDatabaseTCProcedureVariable->GetMinValueAsText())) tTime = ConvertTimeStringToValue(pDatabaseTCProcedureVariable->GetMinValueAsText());
		if (!pDatabaseTCProcedureVariable->GetMaxValueAsText().IsEmpty() && tTime > ConvertTimeStringToValue(pDatabaseTCProcedureVariable->GetMaxValueAsText())) tTime = ConvertTimeStringToValue(pDatabaseTCProcedureVariable->GetMaxValueAsText());
	}
	return tTime;
}

INT CTCProcedureThread::__Break(UINT nLine)
{
	BOOL  bBreakpoint;
	CString  szMessage;

	if (Lock())
	{
		if ((bBreakpoint = CheckLineBreakpoint((m_nLine = nLine), TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS)) || !GetProcess()->IsAutoExecutionEnabled())
		{
			for (szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_BREAKPOINT_HITATLINE), nLine); bBreakpoint; )
			{
				ReportSuccessMessage(szMessage);
				break;
			}
			for (Unlock(); Synchronize(); )
			{
				GetProcess()->EnableAutoExecution(FALSE);
				return GetProcess()->Break();
			}
		}
		if (!m_bAborted)
		{
			if (Wait(0) == WAIT_TIMEOUT)
			{
				Unlock();
				return 0;
			}
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_THREADABORTATLINE), nLine);
			ReportWarningMessage(szMessage);
			m_bAborted = TRUE;
		}
		Unlock();
		return -1;
	}
	return 0;
}

CTMParameter *CTCProcedureThread::__GetTMParameter(INT nIndex) CONST
{
	return m_pTMParameters.GetAt(nIndex);
}

CTCParameter *CTCProcedureThread::__GetTCParameter(INT nIndex) CONST
{
	return m_pTCEnvironment->GetTCParameters()->GetAt(nIndex);
}

HANDLE CTCProcedureThread::__GetTMEvent() CONST
{
	return m_hTMEvent;
}

HANDLE CTCProcedureThread::__GetTCEvent() CONST
{
	return m_hTCEvent;
}

BOOL CTCProcedureThread::CheckLineBreakpoint(UINT nLine, UINT nType)
{
	CDatabaseTCProcedureThreadBreakpoint  *pDatabaseTCProcedureThreadBreakpoint;

	return(((pDatabaseTCProcedureThreadBreakpoint = m_pDatabaseTCProcedureThreadBreakpoints.GetAt(m_pDatabaseTCProcedureThreadBreakpoints.Find(nLine))) && (pDatabaseTCProcedureThreadBreakpoint->GetOptions() & nType) && (pDatabaseTCProcedureThreadBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) != TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::CheckStepBreakpoint(LPCTSTR pszName, UINT nType)
{
	CDatabaseTCProcedureThreadBreakpoint  *pDatabaseTCProcedureThreadBreakpoint;

	return(((pDatabaseTCProcedureThreadBreakpoint = m_pDatabaseTCProcedureThreadBreakpoints.GetAt(m_pDatabaseTCProcedureThreadBreakpoints.Find(pszName))) && (pDatabaseTCProcedureThreadBreakpoint->GetOptions() & nType) && (pDatabaseTCProcedureThreadBreakpoint->GetOptions() & TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) != TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::CheckStepAuthorization(LPCTSTR pszName, BOOL bTrigger)
{
	UINT  nAttributes;
	CDatabaseTCProcedureThreadStep  *pStep;

	return(((pStep = FindStep(pszName)) && (pStep->GetType() != TCPROCEDURETHREADSTEP_ACTIONOBJECT_CALLPROCEDURE  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_ACTIONOBJECT_STARTPROCEDURE  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCFUNCTION  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE) && ((((nAttributes = GetProcess()->GetAttributes()) & TCPROCEDURE_EXECUTIONMODE_SINGLESTEP) && ((!bTrigger && (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETARGUMENTS || pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETVARIABLES || pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETPARAMETERS)) || (bTrigger  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETARGUMENTS  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETVARIABLES  &&  pStep->GetType() != TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETPARAMETERS))) || ((nAttributes & TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS) && !bTrigger && (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETARGUMENTS || pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETVARIABLES || pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETPARAMETERS)) || (bTrigger && (pStep->GetTriggerType() & TCPROCEDURETHREADSTEP_TRIGGERTYPE_AUTHORIZATION)) || (!bTrigger && (pStep->GetConfirmationType() & TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_AUTHORIZATION)))) ? TRUE : FALSE);
}

BOOL CTCProcedureThread::AuthorizeStepExecution(LPCTSTR pszName)
{
	INT  nIdentifier;
	INT  nIdentifiers;
	CString  szMessage;
	CTimeKey  tAuthorization;
	CPtrArray  pIdentifiers;
	CUIntArray  nIdentifierTypes;
	CStringArray  szIdentifierNames;
	CLongUIntArray  nIdentifierAttributes;
	CDatabaseTCProcedureThreadStep  *pStep;
	CTCProcedureStepAuthorizationDialog  cStepAuthorizationDialog;
	CTCProcedureSetArgumentsAuthorizationDialog  cSetArgumentsAuthorizationDialog;
	CTCProcedureSetVariablesAuthorizationDialog  cSetVariablesAuthorizationDialog;
	CTCProcedureSetParametersAuthorizationDialog  cSetParametersAuthorizationDialog;

	for (; (pStep = FindStep(pszName)); )
	{
		if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETARGUMENTS)
		{
			for (nIdentifier = 0, nIdentifiers = GetProcess()->EnumIdentifiers(szIdentifierNames, nIdentifierTypes, nIdentifierAttributes, pIdentifiers); nIdentifier < nIdentifiers; nIdentifier++)
			{
				if (nIdentifierTypes.GetAt(nIdentifier) != TCPROCEDUREPROCESS_IDENTIFIERTYPE_ARGUMENT)
				{
					szIdentifierNames.RemoveAt(nIdentifier);
					nIdentifierTypes.RemoveAt(nIdentifier);
					nIdentifierAttributes.RemoveAt(nIdentifier);
					pIdentifiers.RemoveAt(nIdentifier);
					nIdentifiers--;
					nIdentifier--;
				}
			}
			if (cSetArgumentsAuthorizationDialog.DoModal(GetProcess()->GetName(), GetName(), pszName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tAuthorization, szIdentifierNames, nIdentifierAttributes, pIdentifiers) != IDOK)
			{
				szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_AUTHORIZATION_DENIAL), pszName);
				ReportFailureMessage(szMessage);
				break;
			}
			return TRUE;
		}
		if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETVARIABLES)
		{
			for (nIdentifier = 0, nIdentifiers = GetProcess()->EnumIdentifiers(szIdentifierNames, nIdentifierTypes, nIdentifierAttributes, pIdentifiers); nIdentifier < nIdentifiers; nIdentifier++)
			{
				if (nIdentifierTypes.GetAt(nIdentifier) != TCPROCEDUREPROCESS_IDENTIFIERTYPE_VARIABLE)
				{
					szIdentifierNames.RemoveAt(nIdentifier);
					nIdentifierTypes.RemoveAt(nIdentifier);
					nIdentifierAttributes.RemoveAt(nIdentifier);
					pIdentifiers.RemoveAt(nIdentifier);
					nIdentifiers--;
					nIdentifier--;
				}
			}
			if (cSetVariablesAuthorizationDialog.DoModal(GetProcess()->GetName(), GetName(), pszName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tAuthorization, szIdentifierNames, nIdentifierAttributes, pIdentifiers) != IDOK)
			{
				szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_AUTHORIZATION_DENIAL), pszName);
				ReportFailureMessage(szMessage);
				break;
			}
			return TRUE;
		}
		if (pStep->GetType() == TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETPARAMETERS)
		{
			for (nIdentifier = 0, nIdentifiers = GetProcess()->EnumIdentifiers(szIdentifierNames, nIdentifierTypes, nIdentifierAttributes, pIdentifiers); nIdentifier < nIdentifiers; nIdentifier++)
			{
				if (nIdentifierTypes.GetAt(nIdentifier) != TCPROCEDUREPROCESS_IDENTIFIERTYPE_TCPARAMETER)
				{
					szIdentifierNames.RemoveAt(nIdentifier);
					nIdentifierTypes.RemoveAt(nIdentifier);
					nIdentifierAttributes.RemoveAt(nIdentifier);
					pIdentifiers.RemoveAt(nIdentifier);
					nIdentifiers--;
					nIdentifier--;
				}
			}
			if (cSetParametersAuthorizationDialog.DoModal(m_pDatabase, GetProcess()->GetName(), GetName(), pszName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tAuthorization, szIdentifierNames, nIdentifierAttributes, pIdentifiers, m_pTCEnvironment) != IDOK)
			{
				szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_AUTHORIZATION_DENIAL), pszName);
				ReportFailureMessage(szMessage);
				break;
			}
			return TRUE;
		}
		if (cStepAuthorizationDialog.DoModal(GetProcess()->GetName(), GetName(), pszName, pStep->GetType(), pStep->GetLabel(), pStep->GetComments(), tAuthorization) != IDOK)
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_AUTHORIZATION_DENIAL), pszName);
			ReportFailureMessage(szMessage);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::ChangeStepState(LPCTSTR pszName, UINT nState)
{
	INT  nStep;
	INT  nSteps;

	if (Lock())
	{
		for (nStep = 0, nSteps = (INT)m_szStepNames.GetSize(); nStep < nSteps; nStep++)
		{
			if (m_szStepNames.GetAt(nStep) == pszName)
			{
				m_szStepName = pszName;
				break;
			}
		}
		if (nStep < nSteps)
		{
			if ((m_nStepStates.GetAt(nStep) & nState) != nState)
			{
				if (nState & (TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING | TCPROCEDURETHREADSTEP_STATE_TRIGGER_EXECUTED | TCPROCEDURETHREADSTEP_STATE_TRIGGER_FAILED | TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED)) m_nStepStates.SetAt(nStep, ((m_nStepStates.GetAt(nStep) & TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED) != TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED || nState != TCPROCEDURETHREADSTEP_STATE_TRIGGER_EXECUTED) ? ((m_nStepStates.GetAt(nStep) & ~(TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING | TCPROCEDURETHREADSTEP_STATE_TRIGGER_EXECUTED | TCPROCEDURETHREADSTEP_STATE_TRIGGER_FAILED | TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED)) | nState) : m_nStepStates.GetAt(nStep));
				if (nState & (TCPROCEDURETHREADSTEP_STATE_BODY_RUNNING | TCPROCEDURETHREADSTEP_STATE_BODY_EXECUTED | TCPROCEDURETHREADSTEP_STATE_BODY_FAILED | TCPROCEDURETHREADSTEP_STATE_BODY_FORCED)) m_nStepStates.SetAt(nStep, ((m_nStepStates.GetAt(nStep) & TCPROCEDURETHREADSTEP_STATE_BODY_FORCED) != TCPROCEDURETHREADSTEP_STATE_BODY_FORCED || nState != TCPROCEDURETHREADSTEP_STATE_BODY_EXECUTED) ? ((m_nStepStates.GetAt(nStep) & ~(TCPROCEDURETHREADSTEP_STATE_BODY_RUNNING | TCPROCEDURETHREADSTEP_STATE_BODY_EXECUTED | TCPROCEDURETHREADSTEP_STATE_BODY_FAILED | TCPROCEDURETHREADSTEP_STATE_BODY_FORCED)) | nState) : m_nStepStates.GetAt(nStep));
				if (nState & (TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_RUNNING | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_EXECUTED | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FAILED | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED)) m_nStepStates.SetAt(nStep, ((m_nStepStates.GetAt(nStep) & TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED) != TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED || nState != TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_EXECUTED) ? ((m_nStepStates.GetAt(nStep) & ~(TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_RUNNING | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_EXECUTED | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FAILED | TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED)) | nState) : m_nStepStates.GetAt(nStep));
				if (nState == TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING  &&  nStep < m_nStepStates.GetUpperBound())
				{
					m_szStepNames.Add((LPCTSTR)m_szStepNames.GetAt(nStep));
					m_nStepStates.Add(m_nStepStates.GetAt(nStep));
					m_szStepNames.RemoveAt(nStep);
					m_nStepStates.RemoveAt(nStep);
				}
				Unlock();
				return Synchronize();
			}
			Unlock();
			return TRUE;
		}
		for (m_szStepName = pszName, m_szStepNames.Add(pszName), m_nStepStates.Add(nState), Unlock(); Synchronize(); ) return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureThread::CheckStepStates(UINT &nState, CStringArray &szNames, CUIntArray &nStates, UINT &nLine)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	nState = GetRunningState();
	nState |= (IsThreadEnabled()) ? TCPROCEDURETHREAD_AUTHORITY_ENABLED : TCPROCEDURETHREAD_AUTHORITY_DISABLED;
	szNames.Copy(m_szStepNames);
	nStates.Copy(m_nStepStates);
	nLine = m_nLine;
	return TRUE;
}

BOOL CTCProcedureThread::AcknowledgeStepStates()
{
	return SetEvent(m_hResume);
}

BOOL CTCProcedureThread::ResetStepStates()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_szStepName.Empty();
	m_szStepNames.RemoveAll();
	m_nStepStates.RemoveAll();
	SetEvent(m_hUpdate);
	return TRUE;
}

CDatabaseTCProcedureThreadStep *CTCProcedureThread::FindStep() CONST
{
	return FindStep(m_szStepName);
}
CDatabaseTCProcedureThreadStep *CTCProcedureThread::FindStep(LPCTSTR pszName) CONST
{
	INT  nStep;
	INT  nSteps;
	CPtrArray  pSteps[2];
	CTCProcedureDocument  *pDocument;
	CTCProcedureDocumentItem  *pStep;

	if ((pDocument = new CTCProcedureDocument))
	{
		for (nStep = 0, nSteps = (pDocument->Unmap(&m_pContents) && m_pContents.Enum(pSteps[0]) == pDocument->EnumSteps(pSteps[1], FALSE, TRUE)) ? (INT)pSteps[1].GetSize() : 0; nStep < nSteps; nStep++)
		{
			if ((pStep = (CTCProcedureDocumentItem *)pSteps[1].GetAt(nStep)))
			{
				if (pStep->GetName() == pszName) break;
				continue;
			}
		}
		delete pDocument;
		return((nStep < nSteps) ? (CDatabaseTCProcedureThreadStep *)pSteps[0].GetAt(nStep) : (CDatabaseTCProcedureThreadStep *)NULL);
	}
	return((CDatabaseTCProcedureThreadStep *)NULL);
}

BOOL CTCProcedureThread::ReportSuccessMessage(LPCTSTR pszMessage)
{
	return GetProcess()->ReportSuccessMessage(GetName(), pszMessage);
}

BOOL CTCProcedureThread::ReportWarningMessage(LPCTSTR pszMessage)
{
	return GetProcess()->ReportWarningMessage(GetName(), pszMessage);
}

BOOL CTCProcedureThread::ReportFailureMessage(LPCTSTR pszMessage)
{
	return GetProcess()->ReportFailureMessage(GetName(), pszMessage);
}

BOOL CTCProcedureThread::ReportAlertMessage(LPCTSTR pszMessage)
{
	return GetProcess()->ReportAlertMessage(pszMessage);
}

BOOL CTCProcedureThread::HasOpenDialogs() CONST
{
	INT  nCount;

	return((EnumThreadWindows(GetThreadID(), EnumThreadDialogsProc, (LPARAM)&(nCount = 0)) && nCount > 0) ? TRUE : FALSE);
}

BOOL CALLBACK CTCProcedureThread::EnumThreadDialogsProc(HWND hWnd, LPARAM lParam)
{
	CWnd  *pWnd;

	for (; (pWnd = CWnd::FromHandle(hWnd)) && pWnd->IsKindOf(RUNTIME_CLASS(CTCProcedureDialog)); )
	{
		(*((LPINT)lParam))++;
		break;
	}
	return TRUE;
}

BOOL CTCProcedureThread::IsThreadTerminating() CONST
{
	return((WaitForSingleObject(m_hObject, 0) == WAIT_OBJECT_0) ? TRUE : FALSE);
}

CTCProcedureProcess *CTCProcedureThread::GetProcess() CONST
{
	return((CTCProcedureProcess *)GetThreadInfo());
}

BEGIN_MESSAGE_MAP(CTCProcedureThread, CThread)
	//{{AFX_MSG_MAP(CTCProcedureThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureProcess

CTCProcedureProcess::CTCProcedureProcess() : CPtrArray()
{
	m_nState = TCPROCEDURE_RUNNINGSTATE_NOTRUNNING;
	m_nAttributes = 0;
	m_nProcessID = -1;
	m_nProcedureID = -1;
	m_bAutoExecution = TRUE;
	m_bAutoTermination = TRUE;
	m_pTCProcessEngine = (CTCProcessEngine *)NULL;
	m_pTCEnvironment = (CTCEnvironment *)NULL;
	m_pCriticalSection = new CCriticalSection;
}
CTCProcedureProcess::CTCProcedureProcess(LPCTSTR pszName, INT nProcedureID, INT nID, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment) : CPtrArray()
{
	m_nState = TCPROCEDURE_RUNNINGSTATE_NOTRUNNING;
	m_szName = pszName;
	m_nAttributes = 0;
	m_nProcessID = nID;
	m_nProcedureID = nProcedureID;
	m_bAutoExecution = TRUE;
	m_bAutoTermination = TRUE;
	m_pTCProcessEngine = pTCProcessEngine;
	m_pTCEnvironment = pTCEnvironment;
	m_pCriticalSection = new CCriticalSection;
}

CTCProcedureProcess::~CTCProcedureProcess()
{
	RemoveAll();
	delete m_pCriticalSection;
}

VOID CTCProcedureProcess::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCProcedureProcess::GetName() CONST
{
	return m_szName;
}

VOID CTCProcedureProcess::SetID(INT nID)
{
	m_nProcessID = nID;
}

INT CTCProcedureProcess::GetID() CONST
{
	return m_nProcessID;
}

VOID CTCProcedureProcess::SetProcedureID(INT nID)
{
	m_nProcedureID = nID;
}

INT CTCProcedureProcess::GetProcedureID() CONST
{
	return m_nProcedureID;
}

VOID CTCProcedureProcess::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CTCProcedureProcess::GetAttributes() CONST
{
	return m_nAttributes;
}

BOOL CTCProcedureProcess::SetArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments)
{
	return m_pDatabaseTCProcedureArguments.Copy(&pDatabaseTCProcedureArguments);
}

INT CTCProcedureProcess::GetArguments(CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments) CONST
{
	pDatabaseTCProcedureArguments.Copy(&m_pDatabaseTCProcedureArguments);
	return((INT)pDatabaseTCProcedureArguments.GetSize());
}

BOOL CTCProcedureProcess::SetVariables(CONST CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables)
{
	return m_pDatabaseTCProcedureVariables.Copy(&pDatabaseTCProcedureVariables);
}

INT CTCProcedureProcess::GetVariables(CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables) CONST
{
	pDatabaseTCProcedureVariables.Copy(&m_pDatabaseTCProcedureVariables);
	return((INT)pDatabaseTCProcedureVariables.GetSize());
}

BOOL CTCProcedureProcess::Initialize(CStringArray &szErrorParameters)
{
	INT  nThread;
	INT  nThreads;
	CStringArray  szMessages;
	CTCProcedureThread  *pThreadInfo;

	for (nThread = 0, nThreads = (INT)GetSize(), szErrorParameters.RemoveAll(); nThread < nThreads; nThread++)
	{
		if ((pThreadInfo = GetAt(nThread)))
		{
			if (pThreadInfo->Initialize(szMessages))
			{
				szErrorParameters.Append(szMessages);
				continue;
			}
			break;
		}
	}
	return((!szErrorParameters.GetSize()) ? TRUE : FALSE);
}

BOOL CTCProcedureProcess::Update(CONST CTMEnvironment *pTMEnvironment)
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;

	for (nThread = 0, nThreads = (INT)GetSize(); nThread < nThreads; nThread++)
	{
		if ((pThreadInfo = GetAt(nThread)))
		{
			pThreadInfo->Update(pTMEnvironment);
			continue;
		}
		break;
	}
	return((nThread == nThreads) ? TRUE : FALSE);
}

VOID CTCProcedureProcess::SetRunningState(UINT nState)
{
	m_nState = nState;
}

UINT CTCProcedureProcess::GetRunningState() CONST
{
	return m_nState;
}

BOOL CTCProcedureProcess::Break()
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;

	for (nThread = 0, nThreads = (INT)GetSize(); nThread < nThreads; nThread++)
	{
		if ((pThreadInfo = GetAt(nThread)) && pThreadInfo->GetThreadID() != GetCurrentThreadId() && pThreadInfo->IsThreadActive() && pThreadInfo->GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING)
		{
			pThreadInfo->SetRunningState(TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED);
			pThreadInfo->Suspend();
		}
	}
	for (nThread = 0; nThread < nThreads; nThread++)
	{
		if ((pThreadInfo = GetAt(nThread)) && pThreadInfo->GetThreadID() == GetCurrentThreadId())
		{
			pThreadInfo->SetRunningState(TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED);
			SetRunningState(TCPROCEDURE_RUNNINGSTATE_STOPPED);
			pThreadInfo->Suspend();
			break;
		}
	}
	return TRUE;
}

VOID CTCProcedureProcess::EnableAutoExecution(BOOL bEnable)
{
	m_bAutoExecution = bEnable;
}

BOOL CTCProcedureProcess::IsAutoExecutionEnabled() CONST
{
	return m_bAutoExecution;
}

VOID CTCProcedureProcess::EnableAutoTermination(BOOL bEnable)
{
	m_bAutoTermination = bEnable;
}

BOOL CTCProcedureProcess::IsAutoTerminationEnabled() CONST
{
	return m_bAutoTermination;
}

BOOL CTCProcedureProcess::Terminate(BOOL bAuto)
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;

	for (nThread = 0, nThreads = (!bAuto || m_bAutoTermination) ? (INT)GetSize() : -1; nThread < nThreads; nThread++)
	{
		if ((pThreadInfo = GetAt(nThread)) && pThreadInfo->IsThreadActive() && !pThreadInfo->IsThreadTerminating()) break;
		continue;
	}
	return((nThread == nThreads) ? TRUE : FALSE);
}

VOID CTCProcedureProcess::AssignArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, va_list pArgumentList)
{
	return;
}
VOID CTCProcedureProcess::AssignArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments)
{
	return;
}

VOID CTCProcedureProcess::AssignVariables()
{
	return;
}

INT CTCProcedureProcess::EnumIdentifiers(CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CLongUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers) CONST
{
	szIdentifiers.RemoveAll();
	nIdentifierTypes.RemoveAll();
	nIdentifierAttributes.RemoveAll();
	pIdentifiers.RemoveAll();
	return 0;
}

INT CTCProcedureProcess::EnumSynchronizationObjects(CStringArray &szObjects, CPtrArray &phObjects) CONST
{
	szObjects.RemoveAll();
	phObjects.RemoveAll();
	return 0;
}

BOOL CTCProcedureProcess::ReportSuccessMessage(LPCTSTR pszMessage)
{
	return((lstrlen(pszMessage) > 0) ? m_pTCEnvironment->AddMessage(GetID(), STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_SUCCESS), pszMessage) : FALSE);
}
BOOL CTCProcedureProcess::ReportSuccessMessage(LPCTSTR pszThread, LPCTSTR pszMessage)
{
	CString  szMessage[2];

	szMessage[0].Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_REPORTFORMAT), pszThread, pszMessage);
	szMessage[1].Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_DEBUGREPORTFORMAT), (LPCTSTR)GetName(), pszThread, pszMessage);
	return((lstrlen(pszMessage) > 0) ? ReportSuccessMessage((!m_pTCProcessEngine->IsDebuggingEnabled()) ? szMessage[0] : szMessage[1]) : FALSE);
}

BOOL CTCProcedureProcess::ReportWarningMessage(LPCTSTR pszMessage)
{
	return((lstrlen(pszMessage) > 0) ? m_pTCEnvironment->AddMessage(GetID(), STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_WARNING), pszMessage) : FALSE);
}
BOOL CTCProcedureProcess::ReportWarningMessage(LPCTSTR pszThread, LPCTSTR pszMessage)
{
	CString  szMessage[2];

	szMessage[0].Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_REPORTFORMAT), pszThread, pszMessage);
	szMessage[1].Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_DEBUGREPORTFORMAT), (LPCTSTR)GetName(), pszThread, pszMessage);
	return((lstrlen(pszMessage) > 0) ? ReportWarningMessage((!m_pTCProcessEngine->IsDebuggingEnabled()) ? szMessage[0] : szMessage[1]) : FALSE);
}

BOOL CTCProcedureProcess::ReportFailureMessage(LPCTSTR pszMessage)
{
	return((lstrlen(pszMessage) > 0) ? m_pTCEnvironment->AddMessage(GetID(), STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_ERROR), pszMessage) : FALSE);
}
BOOL CTCProcedureProcess::ReportFailureMessage(LPCTSTR pszThread, LPCTSTR pszMessage)
{
	CString  szMessage[2];

	szMessage[0].Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_REPORTFORMAT), pszThread, pszMessage);
	szMessage[1].Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_DEBUGREPORTFORMAT), (LPCTSTR)GetName(), pszThread, pszMessage);
	return((lstrlen(pszMessage) > 0) ? ReportFailureMessage((!m_pTCProcessEngine->IsDebuggingEnabled()) ? szMessage[0] : szMessage[1]) : FALSE);
}

BOOL CTCProcedureProcess::ReportAlertMessage(LPCTSTR pszMessage)
{
	return((lstrlen(pszMessage) > 0) ? m_pTCEnvironment->AddMessage(GetID(), STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_ALERT), pszMessage) : FALSE);
}

INT CTCProcedureProcess::Add(CTCProcedureThread *pThread)
{
	return((INT)CPtrArray::Add(pThread));
}

INT CTCProcedureProcess::Find(LPCTSTR pszName) CONST
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;

	for (nThread = 0, nThreads = (INT)GetSize(); nThread < nThreads; nThread++)
	{
		if ((pThreadInfo = GetAt(nThread)) && pThreadInfo->GetName() == pszName) break;
		continue;
	}
	return((nThread < nThreads) ? nThread : -1);
}

CTCProcedureThread *CTCProcedureProcess::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProcedureThread *)CPtrArray::GetAt(nIndex) : (CTCProcedureThread *)NULL);
}

CTCProcedureThread *CTCProcedureProcess::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProcedureThread *)CPtrArray::GetAt(nIndex) : (CTCProcedureThread *)NULL);
}

VOID CTCProcedureProcess::RemoveAll()
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;

	for (nThread = 0, nThreads = (INT)GetSize(); nThread < nThreads; nThread++)
	{
		if ((pThreadInfo = GetAt(nThread)))
		{
			delete pThreadInfo;
			continue;
		}
	}
	CPtrArray::RemoveAll();
}

BOOL CTCProcedureProcess::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTCProcedureProcess::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureProcessManager

CTCProcedureProcessManager::CTCProcedureProcessManager() : CObject()
{
	m_pDatabase = (CONST CDatabaseEngine *) NULL;
	m_pTCEnvironment = (CTCEnvironment *)NULL;
	m_pTCProcessEngine = (CTCProcessEngine *)NULL;
	m_pCriticalSection = new CCriticalSection;
}

CTCProcedureProcessManager::~CTCProcedureProcessManager()
{
	delete m_pCriticalSection;
}

BOOL CTCProcedureProcessManager::Initialize(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nProcessID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters)
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CDatabaseTCProcedure  *pProcedure;
	CDatabaseTCProcedureThread  *pThread;
	CDatabaseTCProcedureArguments  pDatabaseTCProcedureArguments;
	CDatabaseTCProcedureVariables  pDatabaseTCProcedureVariables;
	CDatabaseTCProcedureThreadBreakpoints  pDatabaseTCProcedureThreadBreakpoints;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcessInfo = AddProcess(pszName, nProcedureID, nProcessID, pTCProcessEngine, pTCEnvironment)))
	{
		if ((pProcedure = pDatabase->GetTCProcedures()->GetAt(pDatabase->GetTCProcedures()->Find(pszName))))
		{
			for (pProcessInfo->SetAttributes((nExecutionMode != (UINT)-1) ? ((pProcedure->GetAttributes() & ~(TCPROCEDURE_EXECUTIONMODE_AUTOMATIC | TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS | TCPROCEDURE_EXECUTIONMODE_COMMANDS)) | nExecutionMode) : pProcedure->GetAttributes()); pProcedure->GetArguments(pDatabaseTCProcedureArguments) > 0; )
			{
				pProcessInfo->SetArguments(pDatabaseTCProcedureArguments);
				break;
			}
			for (; pProcedure->GetVariables(pDatabaseTCProcedureVariables) > 0; )
			{
				pProcessInfo->SetVariables(pDatabaseTCProcedureVariables);
				break;
			}
			for (nThread = 0, nThreads = (INT)pProcedure->GetSize(); nThread < nThreads; nThread++)
			{
				if ((pThreadInfo = ((pThread = pProcedure->GetAt(nThread)) && pThread->GetBreakpoints(pDatabaseTCProcedureThreadBreakpoints) >= 0) ? AllocateThread(pThread->GetName(), pDatabase, pTCProcessEngine, pTCEnvironment, (HANDLE)hEvents.GetAt(nThread), (HANDLE)hEvents.GetAt(hEvents.GetSize() - TCPROCEDUREPROCESS_EVENTTYPES + TCPROCEDUREPROCESS_EVENTTYPE_COMMAND), (HANDLE)hEvents.GetAt(hEvents.GetSize() - TCPROCEDUREPROCESS_EVENTTYPES + TCPROCEDUREPROCESS_EVENTTYPE_UPDATE), (HANDLE)hEvents.GetAt(hEvents.GetSize() - TCPROCEDUREPROCESS_EVENTTYPES + TCPROCEDUREPROCESS_EVENTTYPE_EXIT)) : (CTCProcedureThread *)NULL))
				{
					if (pThreadInfo->CreateThread(pProcessInfo, max(GetThreadPriority(GetCurrentThread()), THREAD_PRIORITY_BELOW_NORMAL), TRUE))
					{
						AttachThreadInput(pThreadInfo->GetThreadID(), GetWindowThreadProcessId(pThreadInfo->GetMainWnd()->GetSafeHwnd(), (LPDWORD)NULL), TRUE);
						pThreadInfo->EnableThread((pThread->GetAttributes() & TCPROCEDURETHREAD_AUTHORITY_AUTOENABLED) ? TRUE : FALSE);
						pThreadInfo->SetBreakpoints(pDatabaseTCProcedureThreadBreakpoints);
						pThreadInfo->EnableSynchronization(bSynchronized);
						pThreadInfo->SetContents(pThread);
						pProcessInfo->Add(pThreadInfo);
						continue;
					}
					delete pThreadInfo;
				}
				break;
			}
			if (nThread == nThreads)
			{
				if (pProcessInfo->Initialize(szErrorParameters))
				{
					m_pTCProcessEngine = pTCProcessEngine;
					m_pTCEnvironment = pTCEnvironment;
					m_pDatabase = pDatabase;
					return TRUE;
				}
			}
		}
		RemoveProcess(nProcessID);
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::InitializeParameters(INT nProcessID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth)
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(); nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)) && pThreadInfo->Initialize(pTMParameters, fTotalTMBandwidth, fAvailableTMBandwidth, fMaxDiagnosticTMBandwidth, fAvailableDiagnosticTMBandwidth, tTMBandwidth)) continue;
			break;
		}
		return((nThread == nThreads) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::Run(INT nProcessID, va_list pArgumentList, UINT nExecutionMode)
{
	INT  nThread;
	INT  nThreads;
	CString  szMessage;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CDatabaseTCProcedureArguments  pDatabaseTCProcedureArguments;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (pProcessInfo->SetAttributes((nExecutionMode != (UINT)-1) ? ((pProcessInfo->GetAttributes() & ~(TCPROCEDURE_EXECUTIONMODE_AUTOMATIC | TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS | TCPROCEDURE_EXECUTIONMODE_COMMANDS)) | nExecutionMode) : pProcessInfo->GetAttributes()); pProcessInfo->GetArguments(pDatabaseTCProcedureArguments) > 0; )
		{
			pProcessInfo->AssignArguments(pDatabaseTCProcedureArguments, pArgumentList);
			AssignParameters(pDatabaseTCProcedureArguments);
			break;
		}
		for (pProcessInfo->AssignVariables(); m_pTCProcessEngine->IsDebuggingEnabled(); )
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_DEBUGPROCESSSTART), (LPCTSTR)pProcessInfo->GetName());
			m_pTCEnvironment->AddMessage(pProcessInfo->GetID(), szMessage);
			break;
		}
		if (!m_pTCProcessEngine->IsDebuggingEnabled())
		{
			szMessage = STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_PROCESSSTART);
			m_pTCEnvironment->AddMessage(pProcessInfo->GetID(), szMessage);
		}
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(), Resume(nProcessID); nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)))
			{
				pThreadInfo->ResumeThread();
				continue;
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::Start(INT nProcessID, CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, UINT nExecutionMode)
{
	INT  nThread;
	INT  nThreads;
	CString  szMessage;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (pProcessInfo->SetAttributes((nExecutionMode != (UINT)-1) ? ((pProcessInfo->GetAttributes() & ~(TCPROCEDURE_EXECUTIONMODE_AUTOMATIC | TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS | TCPROCEDURE_EXECUTIONMODE_COMMANDS)) | nExecutionMode) : pProcessInfo->GetAttributes()), pProcessInfo->AssignArguments(pDatabaseTCProcedureArguments), pProcessInfo->AssignVariables(), AssignParameters(pDatabaseTCProcedureArguments); m_pTCProcessEngine->IsDebuggingEnabled(); )
		{
			szMessage.Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_DEBUGPROCESSSTART), (LPCTSTR)pProcessInfo->GetName());
			m_pTCEnvironment->AddMessage(pProcessInfo->GetID(), szMessage);
			break;
		}
		if (!m_pTCProcessEngine->IsDebuggingEnabled())
		{
			szMessage = STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_PROCESSSTART);
			m_pTCEnvironment->AddMessage(pProcessInfo->GetID(), szMessage);
		}
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(), Resume(nProcessID); nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)))
			{
				pThreadInfo->ResumeThread();
				continue;
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::Update(INT nProcessID, CONST CTMEnvironment *pTMEnvironment)
{
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->Update(pTMEnvironment) : FALSE);
}

BOOL CTCProcedureProcessManager::Suspend(INT nProcessID)
{
	INT  nID;
	INT  nIDs;
	INT  nCount;
	INT  nThread;
	INT  nThreads;
	BOOL  bSuccess;
	CString  szName;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nProcessID < 0)
	{
		for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (m_nTCProcedureProcessIDs.GetAt(nID) == abs(nProcessID)) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID) : (CTCProcedureProcess *)NULL))
			{
				szName = pProcessInfo->GetName();
				break;
			}
		}
		for (nID = 0, nIDs = (!szName.IsEmpty()) ? nIDs : -1, bSuccess = (nIDs > 0); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID)) && pProcessInfo->GetName() == szName)
			{
				bSuccess &= Suspend(m_nTCProcedureProcessIDs.GetAt(nID));
				continue;
			}
		}
		return bSuccess;
	}
	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(), nCount = 0; nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)) && pThreadInfo->IsThreadActive() && pThreadInfo->GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING)
			{
				pThreadInfo->SetRunningState(TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED);
				pThreadInfo->Suspend();
				nCount++;
			}
		}
		if (nCount > 0)
		{
			pProcessInfo->SetRunningState(TCPROCEDURE_RUNNINGSTATE_STOPPED);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::IsSuspended(INT nProcessID) CONST
{
	INT  nID;
	INT  nIDs;
	INT  nCount;
	INT  nThread;
	INT  nThreads;
	CString  szName;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nProcessID < 0)
	{
		for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (m_nTCProcedureProcessIDs.GetAt(nID) == abs(nProcessID)) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID) : (CTCProcedureProcess *)NULL))
			{
				szName = pProcessInfo->GetName();
				break;
			}
		}
		for (nID = 0, nIDs = (!szName.IsEmpty()) ? nIDs : -1; nID < nIDs; nID++)
		{
			if ((pProcessInfo = (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID)) && pProcessInfo->GetName() == szName)
			{
				if (IsSuspended(m_nTCProcedureProcessIDs.GetAt(nID))) break;
				continue;
			}
		}
		return(nID < nIDs);
	}
	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(), nCount = 0; nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)) && pThreadInfo->GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED) nCount++;
			continue;
		}
		return(nCount > 0);
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::Resume(INT nProcessID, BOOL bAuto)
{
	INT  nID;
	INT  nIDs;
	INT  nCount;
	INT  nThread;
	INT  nThreads;
	BOOL  bSuccess;
	CString  szName;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nProcessID < 0)
	{
		for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (m_nTCProcedureProcessIDs.GetAt(nID) == abs(nProcessID)) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID) : (CTCProcedureProcess *)NULL))
			{
				szName = pProcessInfo->GetName();
				break;
			}
		}
		for (nID = 0, nIDs = (!szName.IsEmpty()) ? nIDs : -1, bSuccess = (nIDs > 0); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID)) && pProcessInfo->GetName() == szName)
			{
				bSuccess &= Resume(m_nTCProcedureProcessIDs.GetAt(nID), bAuto);
				continue;
			}
		}
		return bSuccess;
	}
	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(), pProcessInfo->EnableAutoExecution((bAuto) ? pProcessInfo->IsAutoExecutionEnabled() : TRUE), nCount = 0; nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)) && pThreadInfo->IsThreadActive() && pThreadInfo->GetRunningState() != TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING)
			{
				pThreadInfo->SetRunningState(TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING);
				pThreadInfo->Resume();
				nCount++;
			}
		}
		if (nCount > 0)
		{
			pProcessInfo->SetRunningState(TCPROCEDURE_RUNNINGSTATE_RUNNING);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::IsRunning(INT nProcessID) CONST
{
	INT  nID;
	INT  nIDs;
	INT  nCount;
	INT  nThread;
	INT  nThreads;
	CString  szName;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nProcessID < 0)
	{
		for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (m_nTCProcedureProcessIDs.GetAt(nID) == abs(nProcessID)) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID) : (CTCProcedureProcess *)NULL))
			{
				szName = pProcessInfo->GetName();
				break;
			}
		}
		for (nID = 0, nIDs = (!szName.IsEmpty()) ? nIDs : -1; nID < nIDs; nID++)
		{
			if ((pProcessInfo = (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID)) && pProcessInfo->GetName() == szName)
			{
				if (IsRunning(m_nTCProcedureProcessIDs.GetAt(nID))) break;
				continue;
			}
		}
		return(nID < nIDs);
	}
	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(), nCount = 0; nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)) && pThreadInfo->GetRunningState() == TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING) nCount++;
			continue;
		}
		return(nCount > 0);
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::Terminate(INT nProcessID, BOOL bAuto)
{
	INT  nID[2];
	INT  nIDs[2];
	BOOL  bSuccess;
	CString  szName;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nProcessID < 0)
	{
		for (nID[0] = 0, nIDs[0] = (INT)m_nTCProcedureProcessIDs.GetSize(); nID[0] < nIDs[0]; nID[0]++)
		{
			if ((pProcessInfo = (m_nTCProcedureProcessIDs.GetAt(nID[0]) == abs(nProcessID)) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID[0]) : (CTCProcedureProcess *)NULL))
			{
				szName = pProcessInfo->GetName();
				break;
			}
		}
		for (nID[0] = 0, nIDs[0] = (!szName.IsEmpty()) ? nIDs[0] : -1; nID[0] < nIDs[0]; nID[0]++)
		{
			if ((pProcessInfo = (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID[0])) && pProcessInfo->GetName() == szName)
			{
				if (!pProcessInfo->Terminate(bAuto)) break;
				continue;
			}
		}
		for (nID[1] = 0, nIDs[1] = (nID[0] == nIDs[0]) ? nIDs[0] : -1, bSuccess = (nIDs[1] > 0); nID[1] < nIDs[1]; nID[1]++)
		{
			if ((pProcessInfo = (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID[1])) && pProcessInfo->GetName() == szName)
			{
				if (Terminate(m_nTCProcedureProcessIDs.GetAt(nID[1]), bAuto))
				{
					nIDs[1]--;
					nID[1]--;
					continue;
				}
				bSuccess = FALSE;
			}
		}
		return bSuccess;
	}
	return(((pProcessInfo = FindProcess(nProcessID)) && pProcessInfo->Terminate(bAuto)) ? Abort(nProcessID) : FALSE);
}

BOOL CTCProcedureProcessManager::Abort(INT nProcessID)
{
	INT  nID;
	INT  nIDs;
	BOOL  bSuccess;
	CString  szName;
	CString  szMessage[2];
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nProcessID < 0)
	{
		for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (m_nTCProcedureProcessIDs.GetAt(nID) == abs(nProcessID)) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID) : (CTCProcedureProcess *)NULL))
			{
				szName = pProcessInfo->GetName();
				break;
			}
		}
		for (nID = 0, nIDs = (!szName.IsEmpty()) ? nIDs : -1, bSuccess = (nIDs > 0); nID < nIDs; nID++)
		{
			if ((pProcessInfo = (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID)) && pProcessInfo->GetName() == szName)
			{
				if (Abort(m_nTCProcedureProcessIDs.GetAt(nID)))
				{
					nIDs--;
					nID--;
					continue;
				}
				bSuccess = FALSE;
			}
		}
		return bSuccess;
	}
	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (szMessage[0].Format(STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_DEBUGPROCESSEXIT), (LPCTSTR)(szName = pProcessInfo->GetName())), szMessage[1] = STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_PROCESSEXIT); RemoveProcess(nProcessID); )
		{
			m_pTCEnvironment->AddMessage(nProcessID, (m_pTCProcessEngine->IsDebuggingEnabled()) ? szMessage[0] : szMessage[1]);
			return TRUE;
		}
	}
	return FALSE;
}

INT CTCProcedureProcessManager::EnumIdentifiers(INT nProcessID, CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CLongUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers) CONST
{
	INT  nThread;
	INT  nThreads;
	INT  nParameter;
	INT  nParameters;
	INT  nIdentifier;
	INT  nIdentifiers;
	CStringArray  szParameters;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		if (pProcessInfo->EnumIdentifiers(szIdentifiers, nIdentifierTypes, nIdentifierAttributes, pIdentifiers) >= 0)
		{
			for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(); nThread < nThreads; nThread++)
			{
				if ((pThreadInfo = pProcessInfo->GetAt(nThread)))
				{
					for (nParameter = 0, nParameters = pThreadInfo->EnumParameters(szParameters); nParameter < nParameters; nParameter++)
					{
						for (nIdentifier = 0, nIdentifiers = (INT)szIdentifiers.GetSize(); nIdentifier < nIdentifiers; nIdentifier = nIdentifier + 1)
						{
							if (szParameters.GetAt(nParameter) == szIdentifiers.GetAt(nIdentifier) && nIdentifierTypes.GetAt(nIdentifier) == TCPROCEDUREPROCESS_IDENTIFIERTYPE_TMPARAMETER) break;
							continue;
						}
						if (nIdentifier == nIdentifiers)
						{
							szIdentifiers.Add(szParameters.GetAt(nParameter));
							nIdentifierTypes.Add(TCPROCEDUREPROCESS_IDENTIFIERTYPE_TMPARAMETER);
							nIdentifierAttributes.Add(pThreadInfo->__GetTMParameter(nParameter)->GetAttributes());
							pIdentifiers.Add(NULL);
						}
					}
				}
			}
			return((INT)szIdentifiers.GetSize());
		}
	}
	return 0;
}

INT CTCProcedureProcessManager::EnumThreads(INT nProcessID, CStringArray &szThreads, CUIntArray &nThreadStates) CONST
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		for (nThread = 0, nThreads = (INT)pProcessInfo->GetSize(), szThreads.RemoveAll(), nThreadStates.RemoveAll(); nThread < nThreads; nThread++)
		{
			if ((pThreadInfo = pProcessInfo->GetAt(nThread)))
			{
				nThreadStates.Add(pThreadInfo->GetRunningState());
				szThreads.Add(pThreadInfo->GetName());
			}
		}
		return((INT)szThreads.GetSize());
	}
	return 0;
}

INT CTCProcedureProcessManager::EnumThreadStepStates(INT nProcessID, LPCTSTR pszThread, UINT &nState, CStringArray &szStepNames, CUIntArray &nStepStates, UINT &nLine) CONST
{
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pThreadInfo = ((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->GetAt(pProcessInfo->Find(pszThread)) : (CTCProcedureThread *)NULL) && pThreadInfo->CheckStepStates(nState, szStepNames, nStepStates, nLine)) ? (INT)szStepNames.GetSize() : -1);
}

BOOL CTCProcedureProcessManager::AcknowledgeThreadStepState(INT nProcessID, LPCTSTR pszThread)
{
	INT  nThread;
	INT  nThreads;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pProcessInfo = FindProcess(nProcessID)))
	{
		if (!(pThreadInfo = pProcessInfo->GetAt(pProcessInfo->Find(pszThread))) || !pThreadInfo->AcknowledgeStepStates())
		{
			for (nThread = 0, nThreads = (!lstrlen(pszThread)) ? (INT)pProcessInfo->GetSize() : -1; nThread < nThreads; nThread++)
			{
				if ((pThreadInfo = pProcessInfo->GetAt(nThread)) && pThreadInfo->AcknowledgeStepStates()) continue;
				break;
			}
			return((nThread == nThreads) ? TRUE : FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::UpdateThreadBreakpoints(INT nProcessID, LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints)
{
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pThreadInfo = ((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->GetAt(pProcessInfo->Find(pszThread)) : (CTCProcedureThread *)NULL) && pThreadInfo->UpdateBreakpoints(pDatabaseTCProcedureThreadBreakpoints)) ? TRUE : FALSE);
}

BOOL CTCProcedureProcessManager::InitThreadTCFunction(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch, BOOL bAllowAuthorization)
{
	UINT  nType;
	BOOL  bAuthorize;
	CString  szLabel;
	CString  szThread;
	CString  szProcess;
	CString  szMessage;
	CString  szComments;
	CTimeKey  tAuthorization;
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CDatabaseTCProcedureThreadStep  *pStep;
	CTCProcedureSendTCFunctionAuthorizationDialog  cSendTCFunctionAuthorizationDialog;

	if (Lock())
	{
		if ((pProcessInfo = FindProcess(nProcessID)))
		{
			if ((pStep = ((pThreadInfo = pProcessInfo->GetAt(pProcessInfo->Find(pszThread)))) ? pThreadInfo->FindStep(pszStep) : (CDatabaseTCProcedureThreadStep *)NULL))
			{
				if (pThreadInfo->InitTCFunction(pszStep, nEntry, bExpanded, pTCFunction, pTCPacket, szMemoryPatch, bAuthorize))
				{
					if ((pProcessInfo->GetAttributes() & (TCPROCEDURE_EXECUTIONMODE_SINGLESTEP | TCPROCEDURE_EXECUTIONMODE_COMMANDS)) || (bAuthorize  &&  bAllowAuthorization))
					{
						for (szProcess = pProcessInfo->GetName(), szThread = pThreadInfo->GetName(), nType = pStep->GetType(), szLabel = pStep->GetLabel(), szComments = pStep->GetComments(), Unlock(); cSendTCFunctionAuthorizationDialog.DoModal(m_pDatabase, m_pTCProcessEngine, m_pTCEnvironment, szProcess, szThread, pszStep, nType, szLabel, szComments, tAuthorization, pTCFunction, pTCPacket) == IDOK; ) return TRUE;
						return FALSE;
					}
					Unlock();
					return TRUE;
				}
			}
		}
		Unlock();
	}
	return FALSE;
}

BOOL CTCProcedureProcessManager::EnumThreadTCFunctionExecutionVerificationTimeWindows(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CUIntArray &nStageIDs, CUIntArray &nStageTimeWindowOffsets, CUIntArray &nStageTimeWindowSizes, CUIntArray &nStageTimeWindowUncertainties) CONST
{
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pThreadInfo = ((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->GetAt(pProcessInfo->Find(pszThread)) : (CTCProcedureThread *)NULL) && pThreadInfo->EnumTCFunctionExecutionVerificationTimeWindows(pszStep, nEntry, nStageIDs, nStageTimeWindowOffsets, nStageTimeWindowSizes, nStageTimeWindowUncertainties)) ? TRUE : FALSE);
}

BOOL CTCProcedureProcessManager::CheckThreadTCFunctionPreexecutionExpression(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CStringArray &szParameters) CONST
{
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pThreadInfo = ((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->GetAt(pProcessInfo->Find(pszThread)) : (CTCProcedureThread *)NULL) && pThreadInfo->CheckTCFunctionPreexecutionExpression(pszStep, nEntry, szParameters)) ? TRUE : FALSE);
}

BOOL CTCProcedureProcessManager::CheckThreadTCFunctionExecutionExpression(INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CONST CDatabaseTCFunction *pTCFunction, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pThreadInfo = ((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->GetAt(pProcessInfo->Find(pszThread)) : (CTCProcedureThread *)NULL) && pThreadInfo->CheckTCFunctionExecutionExpression(pszStep, nEntry, pTCFunction, nStageID, tStageStart, tUncertainty, szParameters)) ? TRUE : FALSE);
}

BOOL CTCProcedureProcessManager::HasThreadOpenDialogs(INT nProcessID, LPCTSTR pszThread) CONST
{
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pThreadInfo = ((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->GetAt(pProcessInfo->Find(pszThread)) : (CTCProcedureThread *)NULL) && pThreadInfo->HasOpenDialogs()) ? TRUE : FALSE);
}

INT CTCProcedureProcessManager::LinkTMParameter(INT nProcessID, LPCTSTR pszTag) CONST
{
	CTCProcedureThread  *pThreadInfo;
	CTCProcedureProcess  *pProcessInfo;

	return(((pThreadInfo = ((pProcessInfo = FindProcess(nProcessID))) ? pProcessInfo->GetAt(0) : (CTCProcedureThread *)NULL)) ? pThreadInfo->m_pTMParameters.Find(pszTag) : -1);
}

INT CTCProcedureProcessManager::LinkTCParameter(INT nProcessID, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag) CONST
{
	return pTCEnvironment->GetTCParameters()->Find(pszTag);
}

CTCProcedureProcess *CTCProcedureProcessManager::AllocateProcess(LPCTSTR pszName, INT nProcedureID, INT nProcessID, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment)
{
	return new CTCProcedureProcess(pszName, nProcedureID, nProcessID, pTCProcessEngine, pTCEnvironment);
}

CTCProcedureThread *CTCProcedureProcessManager::AllocateThread(LPCTSTR pszName, CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, HANDLE hTMEvent, HANDLE hTCEvent, HANDLE hUpdate, HANDLE hExit)
{
	return new CTCProcedureThread(pszName, pDatabase, pTCProcessEngine, pTCEnvironment, hTMEvent, hTCEvent, hUpdate, hExit);
}

CTCProcedureProcess *CTCProcedureProcessManager::AddProcess(LPCTSTR pszName, INT nProcedureID, INT nProcessID, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment)
{
	INT  nID;
	INT  nIDs;
	CTCProcedureProcess  *pProcessInfo;

	for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
	{
		if (m_nTCProcedureProcessIDs.GetAt(nID) == nProcessID) break;
		continue;
	}
	if ((pProcessInfo = (nID == nIDs) ? AllocateProcess(pszName, nProcedureID, nProcessID, pTCProcessEngine, pTCEnvironment) : (CTCProcedureProcess *)NULL))
	{
		m_pTCProcedureProcesses.Add(pProcessInfo);
		m_nTCProcedureProcessIDs.Add(nProcessID);
		return pProcessInfo;
	}
	return((CTCProcedureProcess *)NULL);
}

CTCProcedureProcess *CTCProcedureProcessManager::FindProcess(INT nProcessID) CONST
{
	INT  nID;
	INT  nIDs;

	for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
	{
		if (m_nTCProcedureProcessIDs.GetAt(nID) == nProcessID) break;
		continue;
	}
	return((nID < nIDs) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID) : (CTCProcedureProcess *)NULL);
}

BOOL CTCProcedureProcessManager::RemoveProcess(INT nProcessID)
{
	INT  nID;
	INT  nIDs;
	CTCProcedureProcess  *pProcessInfo;

	for (nID = 0, nIDs = (INT)m_nTCProcedureProcessIDs.GetSize(); nID < nIDs; nID++)
	{
		if (m_nTCProcedureProcessIDs.GetAt(nID) == nProcessID) break;
		continue;
	}
	if ((pProcessInfo = (nID < nIDs) ? (CTCProcedureProcess *)m_pTCProcedureProcesses.GetAt(nID) : (CTCProcedureProcess *)NULL))
	{
		m_nTCProcedureProcessIDs.RemoveAt(nID);
		m_pTCProcedureProcesses.RemoveAt(nID);
		delete pProcessInfo;
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcedureProcessManager::AssignParameters(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments)
{
	INT  nArgument;
	INT  nArguments;
	CTCParameter  *pTCParameter;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCProcedureArgument  *pDatabaseTCProcedureArgument;

	for (nArgument = 0, nArguments = (INT)pDatabaseTCProcedureArguments.GetSize(); nArgument < nArguments; nArgument++)
	{
		if ((pTCParameter = ((pDatabaseTCParameter = ((pDatabaseTCProcedureArgument = pDatabaseTCProcedureArguments.GetAt(nArgument))) ? m_pDatabase->GetTCParameters()->GetAt(m_pDatabase->GetTCParameters()->Find(pDatabaseTCProcedureArgument->GetTag())) : (CDatabaseTCParameter *)NULL)) ? m_pTCEnvironment->GetTCParameters()->GetAt(m_pTCEnvironment->GetTCParameters()->Find(pDatabaseTCProcedureArgument->GetTag())) : (CTCParameter *)NULL))
		{
			pTCParameter->SetRawValue(0, pDatabaseTCProcedureArgument->GetConstValue(), m_pTCProcessEngine->CheckTCParameterOolStatus(m_pDatabase, pDatabaseTCParameter, pTCParameter, pDatabaseTCProcedureArgument->GetConstValue()));
			continue;
		}
	}
}

BOOL CTCProcedureProcessManager::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CTCProcedureProcessManager::Unlock()
{
	return m_pCriticalSection->Unlock();
}
