// TCDIAGNOSTICS.CPP : Telecommand Diagnostics Services Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand
// diagnostics services related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2008/07/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nTCDiagnosticsOversamplingDumpStatusBarIndicators[] =
{
	ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MESSAGEPANE,
	ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE,
	ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpLayout

CTCDiagnosticsOversamplingDumpLayout::CTCDiagnosticsOversamplingDumpLayout() : COversamplingParameters()
{
	m_nAttributes = TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC;
}

VOID CTCDiagnosticsOversamplingDumpLayout::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCDiagnosticsOversamplingDumpLayout::GetName() CONST
{
	return m_szName;
}

VOID CTCDiagnosticsOversamplingDumpLayout::SetValidityParameter(LPCTSTR pszTag)
{
	m_szValidityParameter = pszTag;
}

CString CTCDiagnosticsOversamplingDumpLayout::GetValidityParameter() CONST
{
	return m_szValidityParameter;
}

VOID CTCDiagnosticsOversamplingDumpLayout::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CTCDiagnosticsOversamplingDumpLayout::GetAttributes() CONST
{
	return m_nAttributes;
}

INT CTCDiagnosticsOversamplingDumpLayout::Find(LPCTSTR pszTag) CONST
{
	INT  nParameter;
	INT  nParameters;
	COversamplingParameter  *pOversamplingParameter;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOversamplingParameter = GetAt(nParameter)) && pOversamplingParameter->GetTag() == pszTag) break;
		continue;
	}
	return((nParameter < nParameters) ? nParameter : -1);
}

BOOL CTCDiagnosticsOversamplingDumpLayout::Copy(CONST CTCDiagnosticsOversamplingDumpLayout *pLayout)
{
	m_szName = pLayout->m_szName;
	m_nAttributes = pLayout->m_nAttributes;
	m_szValidityParameter = pLayout->m_szValidityParameter;
	return COversamplingParameters::Copy(pLayout);
}

BOOL CTCDiagnosticsOversamplingDumpLayout::Compare(CONST CTCDiagnosticsOversamplingDumpLayout *pLayout) CONST
{
	return((pLayout->m_szName == m_szName  &&  pLayout->m_nAttributes == m_nAttributes  &&  pLayout->m_szValidityParameter == m_szValidityParameter) ? COversamplingParameters::Compare(pLayout) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpLayout::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nParametersData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbValidityParameter = (m_szValidityParameter.GetLength() + 1)*sizeof(TCHAR);
	sData.cbParameters = (COversamplingParameters::Map(nParametersData)) ? (INT)nParametersData.GetSize() : -1;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbValidityParameter + max(sData.cbParameters, 0))), sData.nAttributes = m_nAttributes; nInfo.GetSize() == sData.cbSize && sData.cbParameters >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szValidityParameter, sData.cbValidityParameter);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbValidityParameter), nParametersData.GetData(), sData.cbParameters);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpLayout::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nParametersData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbValidityParameter + sData.cbParameters && sData.cbName > 0 && sData.cbValidityParameter > 0 && sData.cbParameters >= 0; )
	{
		for (nParametersData.SetSize(sData.cbParameters), CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), CopyMemory(m_szValidityParameter.GetBufferSetLength(STRINGCHARS(sData.cbValidityParameter)), nInfo.GetData() + (cbData = cbData + sData.cbName), sData.cbValidityParameter), CopyMemory(nParametersData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbValidityParameter), sData.cbParameters), m_nAttributes = sData.nAttributes, m_szName.ReleaseBuffer(), m_szValidityParameter.ReleaseBuffer(); COversamplingParameters::Unmap(nParametersData); ) return TRUE;
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpLayouts

CTCDiagnosticsOversamplingDumpLayouts::CTCDiagnosticsOversamplingDumpLayouts() : CPtrArray()
{
	return;
}

CTCDiagnosticsOversamplingDumpLayouts::~CTCDiagnosticsOversamplingDumpLayouts()
{
	RemoveAll();
}

INT CTCDiagnosticsOversamplingDumpLayouts::Add(CTCDiagnosticsOversamplingDumpLayout *pLayout)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pLayout->GetName(), TRUE)) >= 0) InsertAt(nIndex, pLayout, 1);
	return nIndex;
}

INT CTCDiagnosticsOversamplingDumpLayouts::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CTCDiagnosticsOversamplingDumpLayout *CTCDiagnosticsOversamplingDumpLayouts::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCDiagnosticsOversamplingDumpLayout *)CPtrArray::GetAt(nIndex) : (CTCDiagnosticsOversamplingDumpLayout *)NULL);
}

CTCDiagnosticsOversamplingDumpLayout *CTCDiagnosticsOversamplingDumpLayouts::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCDiagnosticsOversamplingDumpLayout *)CPtrArray::GetAt(nIndex) : (CTCDiagnosticsOversamplingDumpLayout *)NULL);
}

VOID CTCDiagnosticsOversamplingDumpLayouts::RemoveAll()
{
	INT  nLayout;
	INT  nLayouts;

	for (nLayout = 0, nLayouts = (INT)GetSize(); nLayout < nLayouts; nLayout++)
	{
		delete GetAt(nLayout);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCDiagnosticsOversamplingDumpLayouts::Copy(CONST CTCDiagnosticsOversamplingDumpLayouts *pLayouts)
{
	INT  nLayout;
	INT  nLayouts;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;

	for (nLayout = 0, nLayouts = (INT)pLayouts->GetSize(), RemoveAll(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = new CTCDiagnosticsOversamplingDumpLayout))
		{
			pLayout->Copy(pLayouts->GetAt(nLayout));
			InsertAt(nLayout, pLayout, 1);
			continue;
		}
		break;
	}
	return((nLayout == nLayouts) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpLayouts::Compare(CONST CTCDiagnosticsOversamplingDumpLayouts *pLayouts) CONST
{
	INT  nLayout;
	INT  nLayouts;

	for (nLayout = 0, nLayouts = (pLayouts->GetSize() == GetSize()) ? (INT)GetSize() : -1; nLayout < nLayouts; nLayout++)
	{
		if (!pLayouts->GetAt(nLayout)->Compare(GetAt(nLayout))) break;
		continue;
	}
	return((nLayout == nLayouts) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpLayouts::Map(CByteArray &nInfo) CONST
{
	INT  nLayout;
	INT  nLayouts;
	CByteArray  nLayoutData;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;

	for (nLayout = 0, nLayouts = (INT)GetSize(), nInfo.RemoveAll(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = GetAt(nLayout)) && pLayout->Map(nLayoutData) && nInfo.Append(nLayoutData) >= 0) continue;
		break;
	}
	return((nLayout == nLayouts) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpLayouts::Unmap(CONST CByteArray &nInfo)
{
	INT  cbLayout;
	INT  cbLayouts;
	CByteArray  nLayoutData;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;

	for (cbLayouts = 0, RemoveAll(); cbLayouts < nInfo.GetSize(); cbLayouts += cbLayout)
	{
		for (CopyMemory(&cbLayout, nInfo.GetData() + cbLayouts, sizeof(cbLayout)), nLayoutData.SetSize(max(min(cbLayout, nInfo.GetSize() - cbLayouts), 0)); nLayoutData.GetSize() >= 0; )
		{
			CopyMemory(nLayoutData.GetData(), nInfo.GetData() + cbLayouts, nLayoutData.GetSize());
			break;
		}
		if ((pLayout = new CTCDiagnosticsOversamplingDumpLayout))
		{
			if (pLayout->Unmap(nLayoutData) && Add(pLayout) >= 0) continue;
			delete pLayout;
		}
		break;
	}
	return((cbLayouts == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTCDiagnosticsOversamplingDumpLayouts::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pLayout = GetAt(nIndex[0]))) ? ((nIndex[1] = (pLayout->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pLayout = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pLayout->GetName() == pszName) || (bInsert && (((pLayout = GetAt(max(nIndex[0] - 1, 0))) && pLayout->GetName() != pszName && (pLayout = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pLayout->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSample

CTCDiagnosticsOversamplingDumpSample::CTCDiagnosticsOversamplingDumpSample() : COversamplingParameters()
{
	m_nAlertType = TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_NONE;
	m_nBlock = -1;
}

CTCDiagnosticsOversamplingDumpSample::~CTCDiagnosticsOversamplingDumpSample()
{
	RemoveAll();
}

VOID CTCDiagnosticsOversamplingDumpSample::SetBlock(INT nBlock)
{
	m_nBlock = nBlock;
}

INT CTCDiagnosticsOversamplingDumpSample::GetBlock() CONST
{
	return m_nBlock;
}

VOID CTCDiagnosticsOversamplingDumpSample::SetAlertMessage(UINT nType, LPCTSTR pszMessage)
{
	m_nAlertType = nType;
	m_szAlertMessage = pszMessage;
}

UINT CTCDiagnosticsOversamplingDumpSample::GetAlertMessage(CString &szMessage) CONST
{
	szMessage = m_szAlertMessage;
	return m_nAlertType;
}

COversamplingParameter *CTCDiagnosticsOversamplingDumpSample::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COversamplingParameter *)CPtrArray::GetAt(nIndex) : (COversamplingParameter *)NULL);
}

COversamplingParameter *CTCDiagnosticsOversamplingDumpSample::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COversamplingParameter *)CPtrArray::GetAt(nIndex) : (COversamplingParameter *)NULL);
}

VOID CTCDiagnosticsOversamplingDumpSample::RemoveAll()
{
	m_nBlock = -1;
	m_szAlertMessage.Empty();
	m_nAlertType = TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_NONE;
	COversamplingParameters::RemoveAll();
}

BOOL CTCDiagnosticsOversamplingDumpSample::Copy(CONST CTCDiagnosticsOversamplingDumpSample *pSample)
{
	m_nBlock = pSample->m_nBlock;
	m_nAlertType = pSample->m_nAlertType;
	m_szAlertMessage = pSample->m_szAlertMessage;
	return COversamplingParameters::Copy(pSample);
}

BOOL CTCDiagnosticsOversamplingDumpSample::Compare(CONST CTCDiagnosticsOversamplingDumpSample *pSample) CONST
{
	return((pSample->m_nBlock == m_nBlock  &&  pSample->m_nAlertType == m_nAlertType  &&  pSample->m_szAlertMessage == m_szAlertMessage) ? COversamplingParameters::Compare(pSample) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSamples

CTCDiagnosticsOversamplingDumpSamples::CTCDiagnosticsOversamplingDumpSamples() : CPtrArray()
{
	return;
}

CTCDiagnosticsOversamplingDumpSamples::~CTCDiagnosticsOversamplingDumpSamples()
{
	RemoveAll();
}

INT CTCDiagnosticsOversamplingDumpSamples::Add(CTCDiagnosticsOversamplingDumpSample *pSample)
{
	return((INT)CPtrArray::Add(pSample));
}

CTCDiagnosticsOversamplingDumpSample *CTCDiagnosticsOversamplingDumpSamples::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCDiagnosticsOversamplingDumpSample *)CPtrArray::GetAt(nIndex) : (CTCDiagnosticsOversamplingDumpSample *)NULL);
}

CTCDiagnosticsOversamplingDumpSample *CTCDiagnosticsOversamplingDumpSamples::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCDiagnosticsOversamplingDumpSample *)CPtrArray::GetAt(nIndex) : (CTCDiagnosticsOversamplingDumpSample *)NULL);
}

VOID CTCDiagnosticsOversamplingDumpSamples::RemoveAll()
{
	INT  nSample;
	INT  nSamples;
	CTCDiagnosticsOversamplingDumpSample  *pSample;

	for (nSample = 0, nSamples = (INT)GetSize(); nSample < nSamples; nSample++)
	{
		if ((pSample = GetAt(nSample)))
		{
			delete pSample;
			continue;
		}
	}
	CPtrArray::RemoveAll();
}

BOOL CTCDiagnosticsOversamplingDumpSamples::Copy(CONST CTCDiagnosticsOversamplingDumpSamples *pSamples)
{
	INT  nSample;
	INT  nSamples;
	CTCDiagnosticsOversamplingDumpSample  *pSample[2];

	for (nSample = 0, nSamples = (INT)pSamples->GetSize(), RemoveAll(); nSample < nSamples; nSample++)
	{
		if ((pSample[1] = ((pSample[0] = pSamples->GetAt(nSample))) ? new CTCDiagnosticsOversamplingDumpSample : (CTCDiagnosticsOversamplingDumpSample *)NULL))
		{
			pSample[1]->Copy(pSample[0]);
			continue;
		}
		break;
	}
	return((nSample == nSamples) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSamples::Compare(CONST CTCDiagnosticsOversamplingDumpSamples *pSamples) CONST
{
	INT  nSample;
	INT  nSamples;
	CTCDiagnosticsOversamplingDumpSample  *pSample;

	for (nSample = 0, nSamples = (pSamples->GetSize() == GetSize()) ? (INT)GetSize() : -1; nSample < nSamples; nSample++)
	{
		if ((pSample = pSamples->GetAt(nSample)) && !pSample->Compare(GetAt(nSample))) break;
		continue;
	}
	return((nSample == nSamples) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpPrintJobInfo

CTCDiagnosticsOversamplingDumpPrintJobInfo::CTCDiagnosticsOversamplingDumpPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintRange[0] = 0;
	m_nPrintRange[1] = 0;
	m_tPrintRange[0] = 0;
	m_tPrintRange[1] = 0;
}

VOID CTCDiagnosticsOversamplingDumpPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCDiagnosticsOversamplingDumpPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CTCDiagnosticsOversamplingDumpPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CTCDiagnosticsOversamplingDumpPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CTCDiagnosticsOversamplingDumpPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CTCDiagnosticsOversamplingDumpPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CTCDiagnosticsOversamplingDumpPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

VOID CTCDiagnosticsOversamplingDumpPrintJobInfo::SetPrintParameters(CONST CStringArray &szParameters)
{
	m_szParameters.Copy(szParameters);
}

INT CTCDiagnosticsOversamplingDumpPrintJobInfo::GetPrintParameters(CStringArray &szParameters) CONST
{
	szParameters.Copy(m_szParameters);
	return((INT)szParameters.GetSize());
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::SetPrintRange(UINT nMin, UINT nMax)
{
	if (m_nPrintMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE)
	{
		m_nPrintRange[0] = nMin;
		m_nPrintRange[1] = nMax;
		return TRUE;
	}
	return FALSE;
}
BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::SetPrintRange(CONST CTimeKey &tMin, CONST CTimeKey &tMax)
{
	if (m_nPrintMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE)
	{
		m_tPrintRange[0] = tMin;
		m_tPrintRange[1] = tMax;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::GetPrintRange(UINT &nMin, UINT &nMax) CONST
{
	if (m_nPrintMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE)
	{
		nMin = m_nPrintRange[0];
		nMax = m_nPrintRange[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::GetPrintRange(CTimeKey &tMin, CTimeKey &tMax) CONST
{
	if (m_nPrintMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE)
	{
		tMin = m_tPrintRange[0];
		tMax = m_tPrintRange[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTCDiagnosticsOversamplingDumpPrintJobInfo::Copy(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintRange[0] = pJobInfo->m_nPrintRange[0];
	m_nPrintRange[1] = pJobInfo->m_nPrintRange[1];
	m_tPrintRange[0] = pJobInfo->m_tPrintRange[0];
	m_tPrintRange[1] = pJobInfo->m_tPrintRange[1];
	m_szParameters.Copy(pJobInfo->m_szParameters);
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::Compare(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo) CONST
{
	INT  nParameter;
	INT  nParameters;

	for (nParameter = 0, nParameters = (pJobInfo->m_szName == m_szName && pJobInfo->m_szProfile == m_szProfile && pJobInfo->m_szComments == m_szComments && pJobInfo->m_nPrintMode == m_nPrintMode && ((m_nPrintMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE) != TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE || (pJobInfo->m_nPrintRange[0] == m_nPrintRange[0] && pJobInfo->m_nPrintRange[1] == m_nPrintRange[1])) && ((m_nPrintMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE) != TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE || (pJobInfo->m_tPrintRange[0] == m_tPrintRange[0] && pJobInfo->m_tPrintRange[1] == m_tPrintRange[1])) && pJobInfo->m_szParameters.GetSize() == m_szParameters.GetSize()) ? (INT)m_szParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if (pJobInfo->m_szParameters.GetSize() != m_szParameters.GetSize()) break;
		continue;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nParametersData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nParameter = 0, nParameters = (INT)m_szParameters.GetSize(), sData.cbParameters = 0; nParameter < nParameters; nParameter++, sData.cbParameters += cbData)
	{
		nParametersData.SetSize(sData.cbParameters + (cbData = (m_szParameters.GetAt(nParameter).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nParametersData.GetData() + sData.cbParameters, (LPCTSTR)m_szParameters.GetAt(nParameter), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbParameters)), sData.nPrintMode = m_nPrintMode, sData.nPrintRange[0] = m_nPrintRange[0], sData.nPrintRange[1] = m_nPrintRange[1], sData.tPrintRange[0] = m_tPrintRange[0].GetTime(), sData.tPrintRange[1] = m_tPrintRange[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szProfile, sData.cbProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProfile), (LPCTSTR)m_szComments, sData.cbComments);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbComments), nParametersData.GetData(), sData.cbParameters);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nParametersData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbParameters && sData.cbName > 0 && sData.cbProfile > 0 && sData.cbComments > 0 && sData.cbParameters >= 0; )
	{
		for (nParametersData.SetSize(sData.cbParameters), CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), CopyMemory(m_szProfile.GetBufferSetLength(STRINGCHARS(sData.cbProfile)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbProfile)), CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nInfo.GetData() + (cbData = cbData + sData.cbProfile), STRINGBYTES(sData.cbComments)), CopyMemory(nParametersData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbComments), sData.cbParameters), m_nPrintMode = sData.nPrintMode, m_nPrintRange[0] = sData.nPrintRange[0], m_nPrintRange[1] = sData.nPrintRange[1], m_tPrintRange[0] = sData.tPrintRange[0], m_tPrintRange[1] = sData.tPrintRange[1], m_szName.ReleaseBuffer(), m_szProfile.ReleaseBuffer(), m_szComments.ReleaseBuffer(), m_szParameters.RemoveAll(), cbParameters = 0; cbParameters < sData.cbParameters; cbParameters += cbParameter)
		{
			m_szParameters.Add((LPCTSTR)(nParametersData.GetData() + cbParameters));
			cbParameter = (m_szParameters.GetAt(m_szParameters.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpPrintJobs

CTCDiagnosticsOversamplingDumpPrintJobs::CTCDiagnosticsOversamplingDumpPrintJobs() : CPtrArray()
{
	return;
}

CTCDiagnosticsOversamplingDumpPrintJobs::~CTCDiagnosticsOversamplingDumpPrintJobs()
{
	RemoveAll();
}

INT CTCDiagnosticsOversamplingDumpPrintJobs::Add(CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CTCDiagnosticsOversamplingDumpPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CTCDiagnosticsOversamplingDumpPrintJobInfo *CTCDiagnosticsOversamplingDumpPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCDiagnosticsOversamplingDumpPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTCDiagnosticsOversamplingDumpPrintJobInfo *)NULL);
}

CTCDiagnosticsOversamplingDumpPrintJobInfo *CTCDiagnosticsOversamplingDumpPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCDiagnosticsOversamplingDumpPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTCDiagnosticsOversamplingDumpPrintJobInfo *)NULL);
}

VOID CTCDiagnosticsOversamplingDumpPrintJobs::RemoveAll()
{
	INT  nJob;
	INT  nJobs;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		delete GetAt(nJob);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobs::Copy(CONST CTCDiagnosticsOversamplingDumpPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CTCDiagnosticsOversamplingDumpPrintJobInfo))
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobs::Compare(CONST CTCDiagnosticsOversamplingDumpPrintJobs *pPrintJobs) CONST
{
	INT  nJob[2];
	INT  nJobs[2];

	for (nJob[0] = 0, nJobs[0] = (INT)GetSize(), nJobs[1] = (INT)pPrintJobs->GetSize(); nJob[0] < nJobs[0]; nJob[0]++)
	{
		for (nJob[1] = (nJobs[0] != nJobs[1]) ? nJobs[1] : 0; nJob[1] < nJobs[1]; nJob[1]++)
		{
			if (pPrintJobs->GetAt(nJob[0])->Compare(GetAt(nJob[1]))) break;
			continue;
		}
		if (nJob[1] == nJobs[1]) break;
	}
	return((nJob[0] == nJobs[0] && nJobs[0] == nJobs[1]) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CTCDiagnosticsOversamplingDumpPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CTCDiagnosticsOversamplingDumpPrintJobInfo : (CTCDiagnosticsOversamplingDumpPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_PARAMETERVALUES); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsLayoutPage, CLocalePropertyPage)

CTCDiagnosticsOversamplingDumpSettingsLayoutPage::CTCDiagnosticsOversamplingDumpSettingsLayoutPage() : CLocalePropertyPage(CTCDiagnosticsOversamplingDumpSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::Initialize()
{
	CTCDiagnosticsOversamplingDumpLayout  cLayout;
	CTCDiagnosticsOversamplingDumpOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayout(cLayout) || GetParentDisplay()->GetLayout(cLayout)) && (pDialog->GetLayoutListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntTitle[0][0]) || GetParentDisplay()->GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntTitle[0][0])) && (pDialog->GetLayoutListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntItems[0][0]) || GetParentDisplay()->GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntItems[0][0])) && (pDialog->GetLayoutListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntValues[0]) || GetParentDisplay()->GetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntValues[0])) && (pDialog->GetLayoutListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntTitle[1][0]) || GetParentDisplay()->GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntTitle[1][0])) && (pDialog->GetLayoutListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntItems[1][0]) || GetParentDisplay()->GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntItems[1][0])) && (pDialog->GetLayoutGridBackgroundColors(m_nBackgroundColor[0][0], m_nBackgroundColor[1][0]) || GetParentDisplay()->GetGridBackgroundColors(m_nBackgroundColor[0][0], m_nBackgroundColor[1][0]))) || (GetParentDisplay()->GetLayout(cLayout) && GetParentDisplay()->GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntTitle[0][0]) && GetParentDisplay()->GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntItems[0][0]) && GetParentDisplay()->GetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntValues[0]) && GetParentDisplay()->GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntTitle[1][0]) && GetParentDisplay()->GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntItems[1][0]) && GetParentDisplay()->GetGridBackgroundColors(m_nBackgroundColor[0][0], m_nBackgroundColor[1][0])))
	{
		m_bInvalidData[0] = m_bInvalidData[1] = (!pDialog || !pDialog->GetLayoutInvalidDataMode(m_bInvalidData[0])) ? GetParentDisplay()->IsInvalidDataModeEnabled() : m_bInvalidData[0];
		m_bBadData[0] = m_bBadData[1] = (!pDialog || !pDialog->GetLayoutBadDataMode(m_bBadData[0])) ? GetParentDisplay()->IsBadDataModeEnabled() : m_bBadData[0];
		m_bToolTips[0] = m_bToolTips[1] = (!pDialog || !pDialog->GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay()->IsToolTipModeEnabled() : m_bToolTips[0];
		CopyMemory(&m_fntTitle[0][1], &m_fntTitle[0][0], sizeof(LOGFONT));
		CopyMemory(&m_fntTitle[1][1], &m_fntTitle[1][0], sizeof(LOGFONT));
		CopyMemory(&m_fntItems[0][1], &m_fntItems[0][0], sizeof(LOGFONT));
		CopyMemory(&m_fntItems[1][1], &m_fntItems[1][0], sizeof(LOGFONT));
		CopyMemory(&m_fntValues[1], &m_fntValues[0], sizeof(LOGFONT));
		m_nColumns[1] = m_nColumns[0] = cLayout.GetAttributes();
		m_bParameters = (cLayout.GetSize() > 0) ? TRUE : FALSE;
		m_nBackgroundColor[0][1] = m_nBackgroundColor[0][0];
		m_nBackgroundColor[1][1] = m_nBackgroundColor[1][0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	cLayout.SetAttributes((cLayout.GetAttributes() & ~(TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN)) | (m_nColumns[0] & (TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN)));
	return Check(FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST
{
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(pTitleFont, &m_fntTitle[0][0], sizeof(LOGFONT));
		return Check(FALSE);
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
	{
		CopyMemory(pTitleFont, &m_fntTitle[1][0], sizeof(LOGFONT));
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST
{
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(pItemsFont, &m_fntItems[0][0], sizeof(LOGFONT));
		return Check(FALSE);
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
	{
		CopyMemory(pItemsFont, &m_fntItems[1][0], sizeof(LOGFONT));
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetValuesFont(UINT nPane, LPLOGFONT pValuesFont) CONST
{
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(pValuesFont, &m_fntValues[0], sizeof(LOGFONT));
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	nNumbersColor = m_nBackgroundColor[0][0];
	nValuesColor = m_nBackgroundColor[1][0];
	return Check(FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetInvalidDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bInvalidData[0];
	return Check(FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetBadDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bBadData[0];
	return Check(FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

CTCDiagnosticsOversamplingDumpSettingsDialog *CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetParentDialog() CONST
{
	return((CTCDiagnosticsOversamplingDumpSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTCDiagnosticsOversamplingDumpSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntTitle[0][0].lfFaceName : ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)) ? m_fntItems[0][0].lfFaceName : ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES)) ? m_fntValues[0].lfFaceName : ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE)) ? m_fntTitle[1][0].lfFaceName : m_fntItems[1][0].lfFaceName)))))); (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntTitle[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS) && cFontTools.EnumerateFont(m_fntItems[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES) && cFontTools.EnumerateFont(m_fntValues[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE) && cFontTools.EnumerateFont(m_fntTitle[1][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS) && cFontTools.EnumerateFont(m_fntItems[1][0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0][0])), 0));
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0][0])), max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0][1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntItems[0][0])), 0));
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[0][0])), max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[0][1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntValues[0])), 0));
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntValues[0])), max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntValues[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE))
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[1][0])), 0));
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1][0])), max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1][1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS))
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntItems[1][0])), 0));
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[1][0])), max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[1][1])), 0)));
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

VOID CTCDiagnosticsOversamplingDumpSettingsLayoutPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_RAWDATAPANE, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE)));
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_INVALIDDATA, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_BADDATA, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_TOOLTIPS, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_NUMBERS, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_TIME, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_VALUES, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_UNITS, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, bCheck, TRUE, FALSE);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, bCheck);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	CFontTools  cFontTools;

	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nColumns[0] != m_nColumns[1] || lstrcmp(m_fntTitle[0][0].lfFaceName, m_fntTitle[0][1].lfFaceName) || (m_fntTitle[0][0].lfHeight != m_fntTitle[0][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0][1]))) || m_fntTitle[0][0].lfWeight != m_fntTitle[0][1].lfWeight || m_fntTitle[0][0].lfItalic != m_fntTitle[0][1].lfItalic || lstrcmp(m_fntTitle[1][0].lfFaceName, m_fntTitle[1][1].lfFaceName) || (m_fntTitle[1][0].lfHeight != m_fntTitle[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1][1]))) || m_fntTitle[1][0].lfWeight != m_fntTitle[1][1].lfWeight || m_fntTitle[1][0].lfItalic != m_fntTitle[1][1].lfItalic || lstrcmp(m_fntItems[0][0].lfFaceName, m_fntItems[0][1].lfFaceName) || (m_fntItems[0][0].lfHeight != m_fntItems[0][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0][1]))) || m_fntItems[0][0].lfWeight != m_fntItems[0][1].lfWeight || m_fntItems[0][0].lfItalic != m_fntItems[0][1].lfItalic || lstrcmp(m_fntItems[1][0].lfFaceName, m_fntItems[1][1].lfFaceName) || (m_fntItems[1][0].lfHeight != m_fntItems[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1][1]))) || m_fntItems[1][0].lfWeight != m_fntItems[1][1].lfWeight || m_fntItems[1][0].lfItalic != m_fntItems[1][1].lfItalic || lstrcmp(m_fntValues[0].lfFaceName, m_fntValues[1].lfFaceName) || (m_fntValues[0].lfHeight != m_fntValues[1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntValues[0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntValues[1]))) || m_fntValues[0].lfWeight != m_fntValues[1].lfWeight || m_fntValues[0].lfItalic != m_fntValues[1].lfItalic || m_nBackgroundColor[0][0] != m_nBackgroundColor[0][1] || m_nBackgroundColor[1][0] != m_nBackgroundColor[1][1] || m_bInvalidData[0] != m_bInvalidData[1] || m_bBadData[0] != m_bBadData[1] || m_bToolTips[0] != m_bToolTips[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_NUMBERS) || IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_TIME) || (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_VALUES) && m_bParameters)) && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_RAWDATAPANE, OnShowRawDataPane)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_INVALIDDATA, OnShowInvalidData)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_BADDATA, OnShowBadData)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_TOOLTIPS, OnShowToolTips)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_NUMBERS, OnNumberColumns)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_TIME, OnTimeColumns)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_VALUES, OnValueColumns)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_UNITS, OnUnitColumns)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND, OnBackground)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND, OnParametersBackground)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnParametersTitleFont)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, OnParametersItemsFont)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, OnParametersValuesFont)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE, OnRawDataTitleFont)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS, OnRawDataItemsFont)
	ON_CBN_EDITCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR, OnSelchangeBackground)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR, OnSelchangeParametersBackground)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsLayoutPage message handlers

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckRadioButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_RAWDATAPANE, (m_nColumns[0] & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_NUMBERS, (m_nColumns[0] & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_TIME, (m_nColumns[0] & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_VALUES, (m_nColumns[0] & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_UNITS, (m_nColumns[0] & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND, (m_nBackgroundColor[0][0] != GetSysColor(COLOR_WINDOW)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND, (m_nBackgroundColor[1][0] != GetSysColor(COLOR_WINDOW)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_INVALIDDATA, m_bInvalidData[0]);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_BADDATA, m_bBadData[0]);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_TOOLTIPS, m_bToolTips[0]);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_RAWDATAPANE)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_INVALIDDATA)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_BADDATA)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_NUMBERS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_TIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_VALUES)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_UNITS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nBackgroundColor[0][0]);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nBackgroundColor[1][0]);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0][0].lfFaceName));
	ShowLayoutFontDetails();
	AdjustToPrivileges();
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnSetActive()
{
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	m_bParameters = (GetParentDialog()->GetLayout(cLayout)) ? (cLayout.GetSize() > 0) : m_bParameters;
	return CLocalePropertyPage::OnSetActive();
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntTitle[0][0] : ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)) ? &m_fntItems[0][0] : ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES)) ? &m_fntValues[0] : ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE)) ? &m_fntTitle[1][0] : &m_fntItems[1][0])))); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
			cDC.DrawText(m_szFontSampleText, rSampleText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			cDC.SetTextColor(nOldColor);
			cDC.SelectObject(pOldFont);
			cDC.SetBkMode(nBkMode);
			ValidateRect(rSampleText);
		}
		cFont.DeleteObject();
		break;
	}
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnShowRawDataPane()
{
	m_nColumns[0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_RAWDATAPANE)) ? (m_nColumns[0] | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE) : (m_nColumns[0] & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnShowInvalidData()
{
	m_bInvalidData[0] = IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_INVALIDDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnShowBadData()
{
	m_bBadData[0] = IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_BADDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnShowToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnNumberColumns()
{
	m_nColumns[0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_NUMBERS)) ? (m_nColumns[0] | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN) : (m_nColumns[0] & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnTimeColumns()
{
	m_nColumns[0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_TIME)) ? (m_nColumns[0] | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN) : (m_nColumns[0] & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnValueColumns()
{
	m_nColumns[0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_VALUES)) ? (m_nColumns[0] | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN) : (m_nColumns[0] & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnUnitColumns()
{
	m_nColumns[0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_UNITS)) ? (m_nColumns[0] | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN) : (m_nColumns[0] & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnBackground()
{
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)(m_nBackgroundColor[0][0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND)) ? VGA_COLOR_LTYELLOW : GetSysColor(COLOR_WINDOW)));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnParametersBackground()
{
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)(m_nBackgroundColor[1][0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND)) ? VGA_COLOR_GRAY : GetSysColor(COLOR_WINDOW)));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnParametersTitleFont()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnParametersItemsFont()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnParametersValuesFont()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnRawDataTitleFont()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnRawDataItemsFont()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS, TRUE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntTitle[0][0].lfFaceName, sizeof(m_fntTitle[0][0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		_tcscpy_s(m_fntItems[0][0].lfFaceName, sizeof(m_fntItems[0][0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		_tcscpy_s(m_fntValues[0].lfFaceName, sizeof(m_fntValues[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE))
	{
		_tcscpy_s(m_fntTitle[1][0].lfFaceName, sizeof(m_fntTitle[1][0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS))
	{
		_tcscpy_s(m_fntItems[1][0].lfFaceName, sizeof(m_fntItems[1][0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0][0].lfWeight, m_fntTitle[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0][0].lfWeight, m_fntItems[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntItems[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntValues[0].lfWeight, m_fntValues[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntValues[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntValues[0]);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[1][0].lfWeight, m_fntTitle[1][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[1][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[1][0]);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[1][0].lfWeight, m_fntItems[1][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntItems[1][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntItems[1][0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0][0].lfWeight, m_fntTitle[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0][0].lfWeight, m_fntItems[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntValues[0].lfWeight, m_fntValues[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[1][0].lfWeight, m_fntTitle[1][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[1][0].lfWeight, m_fntItems[1][0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntValues[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[1][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntItems[1][0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnSelchangeBackground()
{
	m_nBackgroundColor[0][0] = (COLORREF)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsLayoutPage::OnSelchangeParametersBackground()
{
	m_nBackgroundColor[1][0] = (COLORREF)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsContentsPage property page

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsContentsPage, CLocalePropertyPage)

CTCDiagnosticsOversamplingDumpSettingsContentsPage::CTCDiagnosticsOversamplingDumpSettingsContentsPage() : CLocalePropertyPage(CTCDiagnosticsOversamplingDumpSettingsContentsPage::IDD)
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpSettingsContentsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::Initialize()
{
	CTCDiagnosticsOversamplingDumpOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayout(m_cLayout[0]) || GetParentDisplay()->GetLayout(m_cLayout[0])) && (pDialog->GetLayoutSampleLimit(m_nSampleLimit[0]) || GetParentDisplay()->GetSampleLimit(m_nSampleLimit[0]))) || (GetParentDisplay()->GetLayout(m_cLayout[0]) && GetParentDisplay()->GetSampleLimit(m_nSampleLimit[0])))
	{
		m_nSampleLimit[1] = m_nSampleLimit[0];
		return m_cLayout[1].Copy(&m_cLayout[0]);
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	UINT  nAttributes;

	for (nAttributes = cLayout.GetAttributes() & ~(TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL); cLayout.Copy(&m_cLayout[0]); )
	{
		cLayout.SetAttributes(nAttributes | (m_cLayout[0].GetAttributes() & (TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL)));
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::GetSampleLimit(UINT &nLimit) CONST
{
	nLimit = m_nSampleLimit[0];
	return Check(FALSE);
}

CTCDiagnosticsOversamplingDumpSettingsDialog *CTCDiagnosticsOversamplingDumpSettingsContentsPage::GetParentDialog() CONST
{
	return((CTCDiagnosticsOversamplingDumpSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpSettingsContentsPage::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::EnumParameters()
{
	INT  nIndex;
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) && pParameter->GetInterrogationInstruction() != (UINT)-1)
		{
			szParameter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETERFORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
			SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			m_szParameters[0].Add(pParameter->GetTag());
		}
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_SETCURSEL);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(((pParameter = ((nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_GETCURSEL)) < m_szParameters[0].GetSize()) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szParameters[0].GetAt(nIndex))) : (CDatabaseTMParameter *)NULL) && m_cLayout[0].Find(pParameter->GetTag()) < 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::EnumValidityParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CStringArray  szParameters;
	CDatabaseTMParameter  *pParameter;

	for (nParameter = 0, nParameters = GetDatabase()->EnumTMParameterValidityParameters(szParameters); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
		{
			szParameter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETERFORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
			SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			m_szParameters[1].Add(pParameter->GetTag());
		}
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITY)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::EnumOversamplingRates()
{
	INT  nOversamplingRate;
	INT  nOversamplingRates;
	CStringArray  szOversamplingRates;

	for (nOversamplingRate = 0, nOversamplingRates = GetTCService()->EnumTCDiagnosticsOversamplingDumpRates(szOversamplingRates); nOversamplingRate < nOversamplingRates; nOversamplingRate++)
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szOversamplingRates.GetAt(nOversamplingRate));
		continue;
	}
	if (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_SETCURSEL) >= 0 && m_cLayout[0].GetSamplingRate() == 0.0)
	{
		m_cLayout[0].SetSamplingRate(_tstof(Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_GETCURSEL))));
		m_cLayout[1].SetSamplingRate(m_cLayout[0].GetSamplingRate());
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE_SECONDS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

VOID CTCDiagnosticsOversamplingDumpSettingsContentsPage::ShowContents()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CStringTools  cStringTools;
	CDatabaseTMParameter  *pParameter;
	COversamplingParameter  *pOversamplingParameter;

	for (nParameter = 0, nParameters = (INT)m_cLayout[0].GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = ((pOversamplingParameter = m_cLayout[0].GetAt(nParameter))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOversamplingParameter->GetTag())) : (CDatabaseTMParameter *)NULL))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_TAG); )
				{
					szParameter = pParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_DESCRIPTION); )
				{
					szParameter = pParameter->GetDescription();
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_TYPE))
				{
					szParameter = (pParameter->GetAttributes() & TMPARAMETER_TYPE_DS16) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DS16TYPE) : EMPTYSTRING;
					szParameter = (pParameter->GetAttributes() & TMPARAMETER_TYPE_DS8) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DS8TYPE) : szParameter;
					szParameter = (pParameter->GetAttributes() & TMPARAMETER_TYPE_BIL) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_BILTYPE) : szParameter;
					szParameter = (pParameter->GetAttributes() & TMPARAMETER_TYPE_HBIL) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_HBILTYPE) : szParameter;
					szParameter = (pParameter->GetAttributes() & TMPARAMETER_TYPE_AN) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ANTYPE) : szParameter;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_WIDTH); )
				{
					szParameter = cStringTools.ConvertIntToString(pParameter->GetWidth());
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_INTERROGATIONCODE); )
				{
					szParameter = cStringTools.ConvertUIntToPaddedString(pParameter->GetInterrogationInstruction(), 8, 16);
					break;
				}
				if (!nColumn  &&  nParameter >= SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT))
				{
					Listview_InsertText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), nParameter, szParameter);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), nParameter, nColumn, szParameter);
			}
		}
	}
	while (nParameters > SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT))
	{
		if (!Listview_DeleteText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), nParameters)) break;
		continue;
	}
	if ((pParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_cLayout[0].GetValidityParameter()))))
	{
		szParameter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETERFORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter));
	}
	Listview_SetCurText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), 0);
	Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT), m_nSampleLimit[0]);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT, (m_nSampleLimit[0] != 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITY, (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION, ((m_cLayout[0].GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL) && m_cLayout[0].GetSize() > 0) ? TRUE : FALSE);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)cStringTools.ConvertFloatToString(m_cLayout[0].GetSamplingRate())), 0));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH)->SetWindowText(cStringTools.ConvertFloatToString(GetTCService()->CalculateTCDiagnosticsOversamplingBandwidth(m_cLayout[0])));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DUMP)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0 && GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpSettingsContentsPage::UpdateTMBandwidth()
{
	double  fTMBandwidth;
	CString  szTMBandwidth;
	CTimeTag  tTMBandwidth;
	CStringTools  cStringTools;

	for (fTMBandwidth = GetTMService()->GetAvailableDiagnosticTMBandwidth(), tTMBandwidth = GetTMService()->GetLastTMBandwidthMeasurementTime(); fTMBandwidth >= 0.0 && CTime::GetCurrentTime().GetTime() - tTMBandwidth.GetTimeInSeconds() < SECONDSPERMINUTE; )
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH)->GetWindowText(szTMBandwidth);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH)->SetWindowText(cStringTools.ConvertUIntToStructuredString((UINT)fTMBandwidth));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_TIME)->SetWindowText(tTMBandwidth.FormatGmt(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TMBANDWITHTIMEFORMAT)));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_REMARK_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_REMARK_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_TIME)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_TIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_BITSPERSECOND_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_BITSPERSECOND_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_BANDWIDTHREMARK_STATIC)->ShowWindow((_tstof(szTMBandwidth) > fTMBandwidth) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_BANDWIDTHREMARK_STATIC)->EnableWindow((_tstof(szTMBandwidth) > fTMBandwidth) ? TRUE : FALSE);
		return;
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_TIME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_TIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_BITSPERSECOND_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_BITSPERSECOND_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_REMARK_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_REMARK_STATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_BANDWIDTHREMARK_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_BANDWIDTHREMARK_STATIC)->EnableWindow(FALSE);
}

VOID CTCDiagnosticsOversamplingDumpSettingsContentsPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, (bCheck = CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE)));
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITY, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION, bCheck);
	AccessControl(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, bCheck);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (!m_cLayout[0].Compare(&m_cLayout[1]) || m_nSampleLimit[0] != m_nSampleLimit[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpSettingsContentsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_cLayout[0].RemoveAll();
	m_cLayout[1].RemoveAll();
	m_szParameters[0].RemoveAll();
	m_szParameters[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpSettingsContentsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpSettingsContentsPage)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ADD, OnAddParameter)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVE, OnRemoveParameter)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVEALL, OnRemoveAllParameters)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITY, OnValidityParameter)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT, OnLimitSamples)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION, OnNoAutomaticDetection)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DUMP, OnTelecommands)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, OnSelchangeParameter)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, OnSelchangeValidityParameter)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, OnSelchangeOversamplingRate)
	ON_CONTROL(SBXN_CHANGE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT, OnSpinchangeSampleLimit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsContentsPage message handlers

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_WIDTH));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_INTERROGATIONCODE));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)->GetClientRect(rColumns);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT), Spinbox_SetRange(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT), TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_MINIMUMSAMPLELIMIT, TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_MAXIMUMSAMPLELIMIT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_TAG)) ? (rColumns.Width() / 6) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_DESCRIPTION)) ? (rColumns.Width() / 2) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_TYPE) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_TITLEITEM_WIDTH)) ? (rColumns.Width() / 8) : (rColumns.Width() / 4))));
		continue;
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH_BITSPERSECOND_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_STATIC)->EnableWindow();
	if (EnumParameters() && EnumValidityParameters() && EnumOversamplingRates())
	{
		UpdateTMBandwidth();
		ShowContents();
	}
	AdjustToPrivileges();
	return TRUE;
}

int CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CLocalePropertyPage::OnCreate(lpCreateStruct) != -1)
	{
		m_nTimerID = SetTimer(TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_UPDATE_TIMERID, TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_UPDATE_TIMEOUT, NULL);
		return 0;
	}
	return -1;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((pNotifyListView->iItem >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((pNotifyListView->iItem >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnAddParameter()
{
	INT  nIndex;
	CDatabaseTMParameter  *pParameter;
	COversamplingParameter  *pOversamplingParameter;
	CHourglassCursor  cCursor;

	if ((pOversamplingParameter = ((pParameter = ((nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_GETCURSEL)) < m_szParameters[0].GetSize()) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szParameters[0].GetAt(nIndex))) : (CDatabaseTMParameter *)NULL)) ? new COversamplingParameter : (COversamplingParameter *)NULL))
	{
		for (pOversamplingParameter->SetTag(pParameter->GetTag()), pOversamplingParameter->SetAttributes(pParameter->GetAttributes()), m_cLayout[0].InsertAt(m_cLayout[0].GetSize(), pOversamplingParameter, 1); m_cLayout[0].GetSize() > 0 && GetTCService()->CalculateTCDiagnosticsOversamplingBandwidth(m_cLayout[0]) >= 0.0; )
		{
			ShowContents();
			break;
		}
		Listview_SetCurText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), max(m_cLayout[0].Find(pOversamplingParameter->GetTag()), 0));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnRemoveParameter()
{
	INT  nIndex;
	CDatabaseTMParameter  *pParameter;
	COversamplingParameter  *pOversamplingParameter;
	CHourglassCursor  cCursor;

	if (Listview_DeleteText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), (nIndex = Listview_GetCurText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)))))
	{
		if ((pOversamplingParameter = m_cLayout[0].GetAt(nIndex)))
		{
			for (m_cLayout[0].RemoveAt(nIndex); !m_cLayout[0].GetSize(); )
			{
				m_cLayout[0].SetAttributes((m_cLayout[0].GetAttributes() & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL) | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC);
				break;
			}
			delete pOversamplingParameter;
			ShowContents();
		}
		Listview_SetCurText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST), 0);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(((pParameter = ((nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_GETCURSEL)) < m_szParameters[0].GetSize()) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szParameters[0].GetAt(nIndex))) : (CDatabaseTMParameter *)NULL) && m_cLayout[0].Find(pParameter->GetTag()) < 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_GETITEMCOUNT) > 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnRemoveAllParameters()
{
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	m_cLayout[0].RemoveAll();
	m_cLayout[0].SetAttributes((m_cLayout[0].GetAttributes() & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL) | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC);
	m_cLayout[0].SetSamplingRate(_tstof(Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_GETCURSEL))));
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION, FALSE);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_GETCURSEL) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH)->SetWindowText(cStringTools.ConvertFloatToString(GetTCService()->CalculateTCDiagnosticsOversamplingBandwidth(m_cLayout[0])));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnValidityParameter()
{
	m_cLayout[0].SetValidityParameter(EMPTYSTRING);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITY));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnLimitSamples()
{
	m_nSampleLimit[0] = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT)) ? TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_DEFAULTSAMPLELIMIT : 0;
	Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT), TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_DEFAULTSAMPLELIMIT);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnNoAutomaticDetection()
{
	m_cLayout[0].SetAttributes((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION)) ? ((m_cLayout[0].GetAttributes() & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC) | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL) : ((m_cLayout[0].GetAttributes() & ~TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL) | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnTelecommands()
{
	CTCDiagnosticsOversamplingDumpPropertiesDialog  cDumpPropertiesDialog;

	cDumpPropertiesDialog.Create(this, m_cLayout[0]);
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnSelchangeParameter()
{
	INT  nIndex;
	CDatabaseTMParameter  *pParameter;

	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(((pParameter = ((nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER, CB_GETCURSEL)) < m_szParameters[0].GetSize()) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szParameters[0].GetAt(nIndex))) : (CDatabaseTMParameter *)NULL) && m_cLayout[0].Find(pParameter->GetTag()) < 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnSelchangeValidityParameter()
{
	INT  nIndex;

	m_cLayout[0].SetValidityParameter(((nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER, CB_GETCURSEL)) < m_szParameters[1].GetSize()) ? m_szParameters[1].GetAt(nIndex) : EMPTYSTRING);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnSelchangeOversamplingRate()
{
	CStringTools  cStringTools;

	m_cLayout[0].SetSamplingRate(_tstof(Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE, CB_GETCURSEL))));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH)->SetWindowText(cStringTools.ConvertFloatToString(GetTCService()->CalculateTCDiagnosticsOversamplingBandwidth(m_cLayout[0])));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnSpinchangeSampleLimit()
{
	m_nSampleLimit[0] = (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_UPDATE_TIMERID)
	{
		UpdateTMBandwidth();
		return;
	}
	CLocalePropertyPage::OnTimer(nEventID);
}

void CTCDiagnosticsOversamplingDumpSettingsContentsPage::OnDestroy()
{
	if (m_nTimerID != 0)
	{
		KillTimer(TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_UPDATE_TIMERID);
		m_nTimerID = 0;
	}
	CLocalePropertyPage::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage, CLocalePropertyPage)

CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::CTCDiagnosticsOversamplingDumpSettingsRetrievingPage() : CLocalePropertyPage(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::Initialize()
{
	CTCDiagnosticsOversamplingDumpOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetRetrieveFileName(m_szFileName[0])) || GetParentDisplay()->GetRetrieveFileName(m_szFileName[0]))
	{
		m_szFileName[1] = m_szFileName[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
	szFileName = m_szFileName[0];
	return Check(FALSE);
}

CTCDiagnosticsOversamplingDumpSettingsDialog *CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::GetParentDialog() CONST
{
	return((CTCDiagnosticsOversamplingDumpSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::EnumDataSources()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CUIntArray  nOptions;

	for (nFile = 0, nFiles = GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles), GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile), m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName() : m_szFileName[0]; nFile < nFiles || (!nFiles && !nFile && !m_szFileName[0].IsEmpty()); nFile++)
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nFiles > 0) ? (LPCTSTR)pFiles.GetAt(nFile)->GetFileName() : (LPCTSTR)m_szFileName[0]));
		continue;
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szFileName[0]), 0));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[1]);
	ShowDataSourceInfo();
}

VOID CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::ShowDataSourceInfo()
{
	CString  szProduct;
	CString  szCompany;
	CString  szTrademark;
	CString  szSpacecraft;
	CString  szStartTime;
	CString  szStopTime;
	CString  szCreationTime;
	CString  szDataSourceType;
	CString  szDataSourceSize;

	if (CheckDataSource(m_szFileName[0], szProduct, szCompany, szTrademark, szSpacecraft, szDataSourceType, szStartTime, szStopTime, szCreationTime, szDataSourceSize))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText(szProduct);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText(szCompany);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText(szSpacecraft);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText(szDataSourceType);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText(szStartTime);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText(szStopTime);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText(szCreationTime);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText(szDataSourceSize);
	}
	else
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText((szProduct = EMPTYSTRING));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText((szCompany = EMPTYSTRING));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText((szSpacecraft = EMPTYSTRING));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText((szDataSourceType = EMPTYSTRING));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText((szStartTime = EMPTYSTRING));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText((szStopTime = EMPTYSTRING));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText((szCreationTime = EMPTYSTRING));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText((szDataSourceSize = EMPTYSTRING));
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->EnableWindow(szProduct.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->ShowWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->ShowWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->ShowWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->ShowWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->ShowWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->ShowWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
{
	CString  szProduct;
	CString  szCompany;
	CString  szTrademark;
	CString  szSpacecraft;
	CString  szStartTime;
	CString  szStopTime;
	CString  szCreationTime;
	CString  szDataSourceType;
	CString  szDataSourceSize;

	return((CheckDataSource(pszFileName, szProduct, szCompany, szTrademark, szSpacecraft, szDataSourceType, szStartTime, szStopTime, szCreationTime, szDataSourceSize) && szSpacecraft == GetAccountSpacecraftName()) ? TRUE : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST
{
	CTimeKey  tTime;
	DWORDLONG  dwSize;
	CByteArray  nData;
	CFileFindEx  cFileFind;
	CHistoryFile  cHistoryFile;

	if (cFileFind.FindFile(pszFileName))
	{
		if (cHistoryFile.Open(pszFileName, (LPCTSTR)NULL, HISTORYSTORE_TYPE_TM, CFile::modeRead, TRUE) == HISTORYFILE_SUCCESS)
		{
			for (cHistoryFile.GetCopyrightProduct(szProduct), cHistoryFile.GetCopyrightCompany(szCompany), cHistoryFile.GetCopyrightTrademark(szTrademark), cHistoryFile.GetSpacecraft(szSpacecraft), cHistoryFile.GetType(szDataSourceType), szStartTime = (cHistoryFile.CLogFile::SeekToFirst() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szStopTime = (cHistoryFile.CLogFile::SeekToLast() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)) : EMPTYSTRING, szDataSourceSize.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT), ((dwSize = cHistoryFile.CLogFile::GetSize()) + 512) / 1024), szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() && !szCompany.IsEmpty() && !szTrademark.IsEmpty(); )
			{
				cHistoryFile.Close();
				cFileFind.Close();
				return TRUE;
			}
			cHistoryFile.Close();
		}
		cFileFind.Close();
	}
	return FALSE;
}

CString CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
{
	INT  cbSep;
	CString  szSep;
	CString  szSize;
	CString  szNumber;

	for (szNumber = pszDataSourceSize; (cbSep = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, (LPTSTR)NULL, 0)); )
	{
		if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, szSep.GetBufferSetLength(cbSep - 1), cbSep))
		{
			for (szNumber = szNumber.Left(lstrlen(szNumber)), szSize.Empty(), szSep.ReleaseBuffer(); szNumber.GetLength() > 0 && !_istdigit(szNumber[szNumber.GetLength() - 1]); )
			{
				szSize = szNumber.Right(1) + szSize, szNumber = szNumber.Left(szNumber.GetLength() - 1);
				continue;
			}
			for (; szNumber.GetLength() > 0; szNumber = szNumber.Left(max(szNumber.GetLength() - 3, 0)))
			{
				szSize = (_istdigit(szSize[0])) ? (szNumber.Right(min(szNumber.GetLength(), 3)) + szSep + szSize) : (szNumber.Right(min(szNumber.GetLength(), 3)) + szSize);
				continue;
			}
			return szSize;
		}
		szSep.ReleaseBuffer();
	}
	return szNumber;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE : FALSE) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() || CheckDataSource(m_szFileName[0])) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_INSPECT, OnInspect)
	ON_CBN_EDITCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsRetrievingPage message handlers

BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE)->EnableWindow();
	EnumDataSources();
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::OnSetActive()
{
	ShowDataSourceInfo();
	return CLocalePropertyPage::OnSetActive();
}

void CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::OnInspect()
{
	CHourglassCursor  cCursor;

	ShowDataSourceInfo();
}

void CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::OnEditchangeFileName()
{
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsRetrievingPage::OnSelchangeFileName()
{
	for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
	{
		ShowDataSourceInfo();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsPrintingComments

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsPrintingComments message handlers

void CTCDiagnosticsOversamplingDumpSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_SHIFT)))
		{
			GetParent()->GetParent()->GetNextDlgTabItem(GetParent())->SetFocus();
			return;
		}
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsPrintingPage, CLocalePropertyPage)

CTCDiagnosticsOversamplingDumpSettingsPrintingPage::CTCDiagnosticsOversamplingDumpSettingsPrintingPage() : CLocalePropertyPage(CTCDiagnosticsOversamplingDumpSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCDiagnosticsOversamplingDumpSettingsPrintingPage::Initialize()
{
	CTCDiagnosticsOversamplingDumpOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsPrintingPage::GetJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CTCDiagnosticsOversamplingDumpSettingsDialog *CTCDiagnosticsOversamplingDumpSettingsPrintingPage::GetParentDialog() CONST
{
	return((CTCDiagnosticsOversamplingDumpSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTCDiagnosticsOversamplingDumpSettingsPrintingPage::ShowJobInfo()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	UINT  nMode;
	UINT  nRange[2];
	CTimeKey  tRange[2];
	CString  szParameter;
	CStringArray  szParameters;
	CDatabaseTMParameter  *pParameter;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nItem = 0, nItems = ((nMode = pJobInfo->GetPrintMode()) & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_PARAMETERVALUES) ? pJobInfo->GetPrintParameters(szParameters) : 0, SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_RESETCONTENT); nItem < nItems; nItem++)
		{
			if ((pParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nItem)))) != (CDatabaseTMParameter *)NULL)
			{
				szParameter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PARAMETERFORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
				SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			}
		}
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES, (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_PARAMETERVALUES) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA, (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_RAWDATA) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER, (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME, (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_SETCURSEL, (WPARAM)(((nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS))) >= 0) ? ((szParameters.GetSize() > 0) ? (nIndex + 1) : nIndex) : -1));
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_SETCURSEL, (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCOUNT) > 0) ? 0 : -1);
		Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START), (pJobInfo->GetPrintRange(tRange[0], tRange[1])) ? tRange[0] : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP), (pJobInfo->GetPrintRange(tRange[0], tRange[1])) ? tRange[1] : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW), (pJobInfo->GetPrintRange(nRange[0], nRange[1])) ? nRange[0] : 0);
		Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH), (pJobInfo->GetPrintRange(nRange[0], nRange[1])) ? nRange[1] : 0);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szParameter = Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCURSEL)))) < 0 && szParameter != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS)) ? TRUE : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_RESETCONTENT);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_TO_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CTCDiagnosticsOversamplingDumpPrintJobInfo *CTCDiagnosticsOversamplingDumpSettingsPrintingPage::FindJobInfo() CONST
{
	return m_pJobs[0].GetAt(m_pJobs[0].Find(STRING(IDS_PRINTJOB_DEFAULTNAME)));
}

BOOL CTCDiagnosticsOversamplingDumpSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE)->SendMessage(CB_GETCURSEL) >= 0 && (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES) || IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA)) && (!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER) || Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)) <= Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH))) && (!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME) || Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)) <= Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP)))) : CLocalePropertyPage::Check()) : TRUE);
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	m_szParameters.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpSettingsPrintingPage)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES, OnPrintParameterValues)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA, OnPrintRawData)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER, OnPrintItemRange)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME, OnPrintTimeRange)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER, OnAddPrintParameter)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER, OnRemovePrintParameter)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, OnResetComments)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE, OnSelchangeProfile)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, OnSelchangeParameter)
	ON_LBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, OnSelchangeParameterList)
	ON_EN_CHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW, OnSpinchangeLowItemRange)
	ON_CONTROL(SBXN_CHANGE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH, OnSpinchangeHighItemRange)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START, OnSpinchangeStartTimeRange)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP, OnSpinchangeStopTimeRange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsPrintingPage message handlers

BOOL CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnInitDialog()
{
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0, Spinbox_SetRange(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW), TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE, TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE), Spinbox_SetRange(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH), TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE, TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE), m_wndComments.SubclassWindow(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->GetSafeHwnd()); nProfile < nProfiles; nProfile++)
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
		continue;
	}
	ShowJobInfo();
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSetActive()
{
	INT  nParameter[2];
	INT  nParameters[2];
	CString  szParameter;
	CStringArray  szParameters;
	CDatabaseTMParameter  *pParameter;
	COversamplingParameter  *pOversamplingParameter;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	for (nParameter[0] = 0, nParameters[0] = (GetParentDialog()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : 0, SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_INSERTSTRING, 0, (LPARAM)STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS)), m_szParameters.RemoveAll(); nParameter[0] < nParameters[0]; nParameter[0]++)
	{
		if ((pParameter = ((pOversamplingParameter = cLayout.GetAt(nParameter[0]))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOversamplingParameter->GetTag())) : (CDatabaseTMParameter *)NULL))
		{
			szParameter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PARAMETERFORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
			SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			m_szParameters.Add(pParameter->GetTag());
		}
	}
	for (nParameter[0] = 0, nParameters[0] = ((pJobInfo = FindJobInfo())) ? pJobInfo->GetPrintParameters(szParameters) : 0; nParameter[0] < nParameters[0]; nParameter[0]++)
	{
		for (nParameter[1] = 0, nParameters[1] = (INT)m_szParameters.GetSize(); nParameter[1] < nParameters[1]; nParameter[1]++)
		{
			if (szParameters.GetAt(nParameter[0]) == m_szParameters.GetAt(nParameter[1])) break;
			continue;
		}
		if (nParameter[1] == nParameters[1])
		{
			szParameters.RemoveAt(nParameter[0]);
			pJobInfo->SetPrintParameters(szParameters);
			nParameters[0]--;
			nParameter[0]--;
		}
	}
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnPrintParameterValues()
{
	CStringArray  szParameters;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES)) ? (pJobInfo->GetPrintMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_PARAMETERVALUES) : (pJobInfo->GetPrintMode() & ~TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_PARAMETERVALUES));
		pJobInfo->SetPrintParameters(szParameters);
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_SETCURSEL, (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES)) ? (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS)) : (WPARAM)-1);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnPrintRawData()
{
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	for (; (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA)) ? (pJobInfo->GetPrintMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_RAWDATA) : (pJobInfo->GetPrintMode() & ~TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_RAWDATA));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnPrintItemRange()
{
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER))
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE);
			pJobInfo->SetPrintRange(TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE, TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE);
		}
		else
		{
			pJobInfo->SetPrintRange(0, 0);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE);
		}
	}
	Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW), TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE);
	Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH), TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnPrintTimeRange()
{
	CTimeKey  tTime;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME))
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE);
			pJobInfo->SetPrintRange(tTime, tTime.GetTime() + SECONDSPERHOUR);
		}
		else
		{
			pJobInfo->SetPrintRange(CTimeKey(0), CTimeKey(0));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE);
		}
	}
	Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START), tTime);
	Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP), CTimeKey(tTime.GetTime() + SECONDSPERHOUR));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_TO_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnAddPrintParameter()
{
	INT  nIndex;
	CString  szParameter;
	CStringArray  szParameters;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintParameters(szParameters); (nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCURSEL)) <= m_szParameters.GetSize(); )
		{
			szParameters.Add(m_szParameters.GetAt(nIndex - 1));
			break;
		}
		pJobInfo->SetPrintParameters(szParameters);
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCURSEL))));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnRemovePrintParameter()
{
	INT  nIndex;
	CString  szParameter;
	CStringArray  szParameters;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintParameters(szParameters); (nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCURSEL)) < szParameters.GetSize(); )
		{
			szParameters.RemoveAt(nIndex);
			break;
		}
		pJobInfo->SetPrintParameters(szParameters);
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_SETCURSEL, min(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCURSEL)), 0));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szParameter = Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCURSEL)))) < 0 && szParameter != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSelchangeParameter()
{
	CString  szParameter;
	CStringArray  szParameters;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (szParameter = Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCURSEL)); szParameter == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS); )
		{
			pJobInfo->SetPrintParameters(szParameters);
			break;
		}
	}
	for (szParameter = Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER, CB_GETCURSEL)); szParameter == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS); )
	{
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_RESETCONTENT);
		break;
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter) < 0 && szParameter != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_ALLPARAMETERS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSelchangeParameterList()
{
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSpinchangeLowItemRange()
{
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintRange((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)), (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSpinchangeHighItemRange()
{
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintRange((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW)), (UINT)Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSpinchangeStartTimeRange()
{
	CTimeKey  tTime[2];
	CTimeKey  tRange[2];
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintRange(tRange[0], tRange[1]), tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)); tTime[0] > tRange[1]; )
		{
			tRange[1] = tTime[0];
			break;
		}
		pJobInfo->SetPrintRange(tTime[0], tRange[1]);
	}
	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP), tTime[0]);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnSpinchangeStopTimeRange()
{
	CTimeKey  tTime[2];
	CTimeKey  tRange[2];
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (pJobInfo->GetPrintRange(tRange[0], tRange[1]), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP)); tTime[1] < tRange[0]; )
		{
			tRange[0] = tTime[1];
			break;
		}
		pJobInfo->SetPrintRange(tRange[0], tTime[1]);
	}
	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START), tTime[1]);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsTabCtrl

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsDialog

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsDialog, CDisplayPropertySheetDialog)

CTCDiagnosticsOversamplingDumpSettingsDialog::CTCDiagnosticsOversamplingDumpSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageContents);
	AddPage(&m_pageRetrieving);
	AddPage(&m_pagePrinting);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	return m_pageLayout.GetLayout(cLayout) && m_pageContents.GetLayout(cLayout);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(nPane, pTitleFont);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST
{
	return m_pageLayout.GetItemsFont(nPane, pItemsFont);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutValuesFont(UINT nPane, LPLOGFONT pValuesFont) CONST
{
	return m_pageLayout.GetValuesFont(nPane, pValuesFont);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	return m_pageLayout.GetBackgroundColors(nNumbersColor, nValuesColor);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutSampleLimit(UINT &nLimit) CONST
{
	return m_pageContents.GetSampleLimit(nLimit);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetInvalidDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetBadDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified() || m_pageContents.IsModified();
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::IsRetrievingModified() CONST
{
	return m_pageRetrieving.IsModified();
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::GetPrintJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs) CONST
{
	return m_pagePrinting.GetJobs(pPrintJobs);
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified();
}

CTCDiagnosticsOversamplingDumpOpenDialog *CTCDiagnosticsOversamplingDumpSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CTCDiagnosticsOversamplingDumpOpenDialog *)GetParent() : (CTCDiagnosticsOversamplingDumpOpenDialog *)NULL);
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpSettingsDialog::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsDialog message handlers

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = (m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd())) ? GetPageCount() : 0; nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

void CTCDiagnosticsOversamplingDumpSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_TCDIAGNOSTICSOVERSAMPLINGDUMP_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CTCDiagnosticsOversamplingDumpSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CTCDiagnosticsOversamplingDumpSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpPropertiesDialog, CDisplayDialog)

CTCDiagnosticsOversamplingDumpPropertiesDialog::CTCDiagnosticsOversamplingDumpPropertiesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCDiagnosticsOversamplingDumpPropertiesDialog::Create(CWnd *pParentWnd, CONST CTCDiagnosticsOversamplingDumpLayout &cLayout)
{
	return((m_cLayout.Copy(&cLayout)) ? CDisplayDialog::Create(pParentWnd, CTCDiagnosticsOversamplingDumpPropertiesDialog::IDD) : -1);
}

BOOL CTCDiagnosticsOversamplingDumpPropertiesDialog::Initialize()
{
	m_bFunction = FALSE;
	return TRUE;
}

CTCDiagnosticsOversamplingDumpSettingsContentsPage *CTCDiagnosticsOversamplingDumpPropertiesDialog::GetParentDialog() CONST
{
	return((CTCDiagnosticsOversamplingDumpSettingsContentsPage *)CDisplayDialog::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpPropertiesDialog::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CTCDiagnosticsOversamplingDumpPropertiesDialog::ShowContents()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCParameter  *pParameter;
	CDatabaseTCFunctionElement  *pFunctionElement;
	CStringTools  cStringTools;

	for (nItem = 0, nItems = (INT)m_cFunction.GetSize(); nItem < nItems; nItem++)
	{
		if ((pFunctionElement = m_cFunction.GetAt(nItem)) != (CDatabaseTCFunctionElement *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_TAG); )
				{
					szItem = pFunctionElement->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_DESCRIPTION); )
				{
					szItem = pFunctionElement->GetDescription();
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_TYPE))
				{
					szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_DISABLED)) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUETYPE_RAW) : EMPTYSTRING;
					szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUETYPE_NUMERICAL) : szItem;
					szItem = ((pFunctionElement->GetAttributes() & TCPARAMETER_CALIBRATION_ENABLED) && ((pParameter = GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pFunctionElement->GetName())))) && (pParameter->GetAttributes() & TCPARAMETER_CALIBRATION_STATUS)) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUETYPE_STATUS) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_BITOFFSET); )
				{
					szItem = cStringTools.ConvertIntToString(8 * pFunctionElement->GetBytePos() + pFunctionElement->GetBitPos());
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_BITLENGTH); )
				{
					szItem = cStringTools.ConvertIntToString(pFunctionElement->GetWidth());
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_CODING))
				{
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_BITPATTERN) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN) : EMPTYSTRING;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_SIGNEDINTEGER) : szItem;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : szItem;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_FLOATINGPOINT) : szItem;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_DATETIME) : szItem;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TEXTSTRING) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_STRING) : szItem;
					szItem = ((pFunctionElement->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME | TCPARAMETER_CODING_TEXTSTRING)) == 0) ? (((pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) || (pFunctionElement->GetAttributes() & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_UNSIGNEDINTEGER) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUECODING_BITPATTERN)) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_RADIX))
				{
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_BINARY) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUERADIX_BINARY) : EMPTYSTRING;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_OCTAL) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUERADIX_OCTAL) : szItem;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_DECIMAL) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUERADIX_DECIMAL) : szItem;
					szItem = (pFunctionElement->GetAttributes() & TCPARAMETER_RADIX_HEXADECIMAL) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_PARAMETERVALUERADIX_HEXADECIMAL) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_VALUE); )
				{
					szItem = pFunctionElement->GetConstValueAsText();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS), nItem, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS), 0);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpPropertiesDialog::Check(BOOL bModified) CONST
{
	return m_bFunction;
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_cFunction.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpPropertiesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpPropertiesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_IMMEDIATELY, OnExecuteImmediately)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME, OnExecuteAtTime)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_IMMEDIATELY, OnReleaseImmediately)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_ATTIME, OnReleaseAtTime)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PREAUTHORIZED, OnPreauthorized)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK, OnDestinationManualStack)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK, OnDestinationAutomaticStack)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME, OnSpinchangeExecutionTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpPropertiesDialog message handlers

BOOL CTCDiagnosticsOversamplingDumpPropertiesDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_BITOFFSET));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_BITLENGTH));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_RADIX));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_VALUE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_TAG)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_DESCRIPTION)) ? (rColumns.Width() / 2) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_TYPE)) ? (rColumns.Width() / 7) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_BITOFFSET) || m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TITLEITEM_BITLENGTH)) ? (rColumns.Width() / 8) : (9 * rColumns.Width() / 35)))));
		continue;
	}
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_IMMEDIATELY, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_IMMEDIATELY, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_ATTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK, TRUE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->ShowWindow((!(m_bFunction = GetTCService()->EncodeTCDiagnosticsOversamplingDump(0, m_cLayout, &m_cFunction))) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->EnableWindow(!m_bFunction);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_NAME)->SetWindowText(m_cFunction.GetName());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESCRIPTION)->SetWindowText(m_cFunction.GetDescription());
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_NAME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_IMMEDIATELY)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_IMMEDIATELY)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_ATTIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PREAUTHORIZED)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
	ShowContents();
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnExecuteImmediately()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_IMMEDIATELY, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME, FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->ShowWindow((!(m_bFunction = GetTCService()->EncodeTCDiagnosticsOversamplingDump(0, m_cLayout, &m_cFunction))) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->EnableWindow(!m_bFunction);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnExecuteAtTime()
{
	CTimeKey  tExecutionTime;

	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_IMMEDIATELY, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME, TRUE);
	Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME), (tExecutionTime = CTime::GetCurrentTime().GetTime() + SECONDSPERHOUR));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->ShowWindow((!(m_bFunction = GetTCService()->EncodeTCDiagnosticsOversamplingDump(1000000 * tExecutionTime.GetTime(), m_cLayout, &m_cFunction))) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->EnableWindow(!m_bFunction);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnReleaseImmediately()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_IMMEDIATELY, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_ATTIME, FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnReleaseAtTime()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_IMMEDIATELY, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_ATTIME, TRUE);
	Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_TIME), CTimeKey(CTime::GetCurrentTime().GetTime() + SECONDSPERHOUR));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_TIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_TIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnPreauthorized()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK, (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PREAUTHORIZED)) ? IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK) : TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK, (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PREAUTHORIZED)) ? IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK) : FALSE);
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnDestinationManualStack()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK, FALSE);
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnDestinationAutomaticStack()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PREAUTHORIZED, TRUE);
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnSpinchangeExecutionTime()
{
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->ShowWindow((!(m_bFunction = GetTCService()->EncodeTCDiagnosticsOversamplingDump(1000000 * Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME)).GetTime(), m_cLayout, &m_cFunction))) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC)->EnableWindow(!m_bFunction);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nStage;
	INT  nStages;
	INT  nParameter;
	INT  nParameters;
	BOOL  bParameter;
	UINT  nStageID;
	CString  szClosure;
	CTCItem  *pItem[2];
	CTCItems  pItems;
	CUIntArray  nStageIDs;
	CTimeSpan  tStageTimeWindow[3];
	CDatabaseTCPacket  *pPacket[2];
	CDatabaseTCPackets  pPackets;
	CDatabaseTCFunctions  pFunctions;
	CDatabaseTCExeVerGroup  *pGroup;
	CDatabaseTCExeVerGroupParameter  *pGroupParameter;
	CHourglassCursor  cCursor;

	if ((pItem[0] = new CTCItem))
	{
		for (pItem[0]->SetName(m_cFunction.GetName()), pItem[0]->SetType(TCITEM_TYPE_FUNCTION), pItem[0]->SetSourceType((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK)) ? TCITEM_SOURCETYPE_MANUALSTACK : TCITEM_SOURCETYPE_AUTOMATICSTACK), pItem[0]->SetFlags(((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PREAUTHORIZED)) ? TCITEM_CHECKFLAG_PREAUTHORIZED : 0) | ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME)) ? TCITEM_EXECUTIONFLAG_TIMETAGGED : TCITEM_EXECUTIONFLAG_IMMEDIATE)), pItem[0]->SetReleaseTime((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_ATTIME)) ? (1000000 * Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_TIME)).GetTime()) : 0), pItem[0]->SetExecutionTime((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME)) ? (1000000 * (TIMETAG)Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME)).GetTime()) : 0); (pPacket[0] = (pItem[0]->CDatabaseTCFunction::Copy(&m_cFunction)) ? GetDatabase()->GetTCPackets()->GetAt(m_cFunction.GetTCPacketRef()) : (CDatabaseTCPacket *)NULL) && pItem[0]->SetTCPacket(pPacket[0]); )
		{
			for (nItem = 0, nItems = (GetTCService()->GenerateTCPackets(pItem[0], pPacket[0], EMPTYSTRING, (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME) && Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME)) > 0) ? TRUE : FALSE, FALSE, FALSE, TRUE, pFunctions, pPackets)) ? (INT)pFunctions.GetSize() : -1; nItem < nItems; nItem++)
			{
				if ((pItem[1] = new CTCItem) && pItem[1]->Copy(pItem[0]) && pItem[1]->CDatabaseTCFunction::Copy(pFunctions.GetAt(nItem)) && pItem[1]->SetTCPacket(pPackets.GetAt(nItem)))
				{
					if ((pGroup = GetDatabase()->GetTCExeVerGroups()->GetAt(pItem[1]->GetExeVerGroupRef())) != (CDatabaseTCExeVerGroup *)NULL)
					{
						for (nParameter = 0, nParameters = (INT)pGroup->GetSize(), nStageIDs.RemoveAll(); nParameter < nParameters; nParameter++)
						{
							if ((pGroupParameter = pGroup->GetAt(nParameter)) != (CDatabaseTCExeVerGroupParameter *)NULL)
							{
								for (nStage = 0, nStages = (INT)nStageIDs.GetSize(), nStageID = MAKETCEXEVERSTAGEID(pGroupParameter->GetStage(), pGroupParameter->GetStep()); nStage < nStages; nStage++)
								{
									if (nStageIDs.GetAt(nStage) == nStageID) break;
									if (nStageIDs.GetAt(nStage) > nStageID)
									{
										nStageIDs.InsertAt(nStage, nStageID);
										break;
									}
								}
							}
						}
						for (nStage = 0, nStages = (INT)nStageIDs.GetSize(); nStage < nStages; nStage++)
						{
							for (nParameter = 0, szClosure.Empty(), bParameter = FALSE; nParameter < nParameters; nParameter++)
							{
								if ((pGroupParameter = pGroup->GetAt(nParameter)) && nStageIDs.GetAt(nStage) == MAKETCEXEVERSTAGEID(pGroupParameter->GetStage(), pGroupParameter->GetStep()))
								{
									tStageTimeWindow[0] = (!bParameter) ? min(pGroupParameter->GetTimeWindowOffset(), tStageTimeWindow[0]) : pGroupParameter->GetTimeWindowOffset();
									tStageTimeWindow[1] = (!bParameter) ? max(pGroupParameter->GetTimeWindowInterval(), tStageTimeWindow[1]) : pGroupParameter->GetTimeWindowInterval();
									tStageTimeWindow[2] = (!bParameter) ? max(pGroupParameter->GetTimeWindowUncertainty(), tStageTimeWindow[2]) : pGroupParameter->GetTimeWindowUncertainty();
									szClosure = (!pGroupParameter->GetTimeWindowClosurePacket().IsEmpty()) ? pGroupParameter->GetTimeWindowClosurePacket() : szClosure;
									bParameter = TRUE;
								}
							}
							if (nParameters > 0)
							{
								pItem[1]->SetVerificationTimeWindow(nStageIDs.GetAt(nStage), tStageTimeWindow[0], tStageTimeWindow[1], tStageTimeWindow[2]);
								pItem[1]->SetVerificationStageClosure(nStageIDs.GetAt(nStage), szClosure);
								continue;
							}
						}
					}
					if (pItems.Add(pItem[1]) >= 0) continue;
				}
				delete pItem[1];
				break;
			}
			if (nItem == nItems)
			{
				GetTCService()->LoadTelecommands(pItems);
				break;
			}
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_MESSAGE_COMMANDFAILURE));
			break;
		}
		delete pItem[0];
	}
	CDisplayDialog::OnOK();
}

BOOL CTCDiagnosticsOversamplingDumpPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersCalibrationPage, CLocalePropertyPage)

CTCDiagnosticsOversamplingDumpParametersCalibrationPage::CTCDiagnosticsOversamplingDumpParametersCalibrationPage() : CLocalePropertyPage(CTCDiagnosticsOversamplingDumpParametersCalibrationPage::IDD)
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpParametersCalibrationPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CTCDiagnosticsOversamplingDumpParametersCalibrationPage::ShowParameterInfo()
{
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow(FALSE);
	ShowCalibrationInfo();
}
VOID CTCDiagnosticsOversamplingDumpParametersCalibrationPage::ShowParameterInfo(CONST CTMParameter *pTMParameter)
{
	INT  nIndex;
	INT  nTable;
	INT  nTables;
	UINT  nStatus;
	CString  szName;
	CString  szTable;
	ULONGLONG  nValue;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), nIndex = -1; (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag()))); )
	{
		for (nTable = 0, nTables = pDatabaseTMParameter->GetCalTableRefs(m_nCalTableRefs, m_nCalValidityRefs), szTable = (pTMParameter->GetRawValue(pTMParameter->GetValueCount() - 1, nValue, nStatus, szTable)) ? szTable : EMPTYSTRING; nTable < nTables; nTable++)
		{
			if ((m_nCalTableType = (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS))) == TMPARAMETER_CALIBRATION_NUMERICAL)
			{
				if ((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nTable))) != (CDatabaseTMNumCalTable *)NULL)
				{
					for (szName.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTMNumCalTable->GetName()); pDatabaseTMNumCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMNumCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMNumCalTable->GetName() == szTable; )
					{
						nIndex = nTable;
						break;
					}
					continue;
				}
			}
			if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
			{
				if ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(m_nCalTableRefs.GetAt(nTable))))
				{
					for (szName.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTMTxtCalTable->GetName()); pDatabaseTMTxtCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMTxtCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMTxtCalTable->GetName() == szTable; )
					{
						nIndex = nTable;
						break;
					}
					continue;
				}
			}
		}
		break;
	}
	m_nCalTableID = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL, max(nIndex, 0));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CTCDiagnosticsOversamplingDumpParametersCalibrationPage::ShowCalibrationInfo()
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
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMNumCalPoint  *pDatabaseTMNumCalPoint;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0 && nIndex < m_nCalTableRefs.GetSize())
	{
		if ((pDatabaseTMNumCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMNumCalPoint = pDatabaseTMNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTMNumCalPoint->GetX());
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTMNumCalPoint->GetY());
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMNumCalTable->GetName());
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText((nIndex == m_nCalTableID) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_STATUS_ACTIVE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow();
			return;
		}
		if ((pDatabaseTMTxtCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMTxtCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMTxtCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMTxtCalTable->GetName());
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText((nIndex == m_nCalTableID) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_STATUS_ACTIVE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

void CTCDiagnosticsOversamplingDumpParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCDiagnosticsOversamplingDumpParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nCalTableRefs.RemoveAll();
	m_nCalValidityRefs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersCalibrationPage message handlers

BOOL CTCDiagnosticsOversamplingDumpParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5; nColumn < nColumns; nWidth = (++nColumn > 0) ? (2 * (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl, CTabCtrl)

CTCDiagnosticsOversamplingDumpParametersFolder *CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl message handlers

UINT CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CTCDiagnosticsOversamplingDumpParametersFolder

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersFolder, CLocalePropertySheetDialog)

CTCDiagnosticsOversamplingDumpParametersFolder::CTCDiagnosticsOversamplingDumpParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CTCDiagnosticsOversamplingDumpParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	INT  nIndex;

	if (CLocalePropertySheetDialog::Create(pParentWnd, WS_CHILD | WS_TABSTOP | WS_DISABLED))
	{
		for (nIndex = GetPageCount() - 1, m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nIndex >= 0; nIndex--)
		{
			SetActivePage(nIndex);
			continue;
		}
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		ShowWindow(SW_SHOWNORMAL);
		return TRUE;
	}
	return FALSE;
}

VOID CTCDiagnosticsOversamplingDumpParametersFolder::ShowParameterInfo()
{
	m_pageCalibration.ShowParameterInfo();
}
VOID CTCDiagnosticsOversamplingDumpParametersFolder::ShowParameterInfo(CONST CTMParameter *pTMParameter)
{
	m_pageCalibration.ShowParameterInfo(pTMParameter);
}

CTCDiagnosticsOversamplingDumpParametersDialog *CTCDiagnosticsOversamplingDumpParametersFolder::GetParentDialog() CONST
{
	return((CTCDiagnosticsOversamplingDumpParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpParametersFolder::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)GetParentDialog()->GetParent());
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersFolder message handlers

void CTCDiagnosticsOversamplingDumpParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersDialog dialog

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersDialog, CDisplayDialog)

CTCDiagnosticsOversamplingDumpParametersDialog::CTCDiagnosticsOversamplingDumpParametersDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCDiagnosticsOversamplingDumpParametersDialog::Create(CWnd *pParentWnd)
{
	return Create(pParentWnd, EMPTYSTRING);
}
INT CTCDiagnosticsOversamplingDumpParametersDialog::Create(CWnd *pParentWnd, LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
	return CDisplayDialog::Create(pParentWnd, CTCDiagnosticsOversamplingDumpParametersDialog::IDD);
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpParametersDialog::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)CDisplayDialog::GetParent());
}

BOOL CTCDiagnosticsOversamplingDumpParametersDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pParameter;
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	for (nParameter = 0, nParameters = (GetParent()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(cLayout.GetAt(nParameter)->GetTag()))))
		{
			szParameter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription());
			SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szParameter), 0));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpParametersDialog::ShowParameterInfo()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter[2];
	CDatabaseTMParameter  *pParameter;
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM)->GetWindowText(szParameter[0]);
	for (nParameter = 0, nParameters = (GetParent()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(cLayout.GetAt(nParameter)->GetTag()))))
		{
			for (szParameter[1].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pParameter->GetTag(), (LPCTSTR)pParameter->GetDescription()); szParameter[0] == szParameter[1]; )
			{
				m_wndFolderCtrl.ShowParameterInfo(cLayout.GetAt(nParameter));
				return;
			}
		}
	}
	m_wndFolderCtrl.ShowParameterInfo();
}

CRect CTCDiagnosticsOversamplingDumpParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CTCDiagnosticsOversamplingDumpParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpParametersDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpParametersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersDialog message handlers

BOOL CTCDiagnosticsOversamplingDumpParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(); m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_FOLDER - 1)); )
	{
		if (EnumParameters()) ShowParameterInfo();
		break;
	}
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

BOOL CTCDiagnosticsOversamplingDumpParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpRetrieveDialog, CDisplayDialog)

CTCDiagnosticsOversamplingDumpRetrieveDialog::CTCDiagnosticsOversamplingDumpRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCDiagnosticsOversamplingDumpRetrieveDialog::Create(CWnd *pParentWnd)
{
	CString  szTitle;
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd;

	return Create(pParentWnd, ((pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)pParentWnd) && pTCDiagnosticsOversamplingDumpWnd->GetLayout(szTitle)) ? szTitle : STRING(IDS_WINDOW_UNKNOWNTITLE));
}
INT CTCDiagnosticsOversamplingDumpRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
	return CDisplayDialog::Create(pParentWnd, CTCDiagnosticsOversamplingDumpRetrieveDialog::IDD);
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::GetMode(UINT &nMode) CONST
{
	nMode = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_EXACTTIME)) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME : 0;
	nMode |= (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME) || IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND)) ? ((!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME)) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND : TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) : 0;
	nMode |= (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC)) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD : ((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME : TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD);
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
	nSpeed = (!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT)((GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMIN) + GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMAX)) / 2) : (UINT)GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETPOS);
	return((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::GetInterval(CTimeSpan &tInterval) CONST
{
	tInterval = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME))) : 0;
	return((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME)), tTimeKey = 0; tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)), tTimeKey = 0; IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

CTCDiagnosticsOversamplingDumpOpenDialog *CTCDiagnosticsOversamplingDumpRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CTCDiagnosticsOversamplingDumpOpenDialog *)GetParent() : (CTCDiagnosticsOversamplingDumpOpenDialog *)NULL);
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpRetrieveDialog::GetParentDisplay() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;

	if (GetRetrieveInfo(nMode, nSpeed, tInterval, tStartTime, tStopTime))
	{
		Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME), tInterval.GetTotalSeconds() / SECONDSPERMINUTE);
		Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME), (tStopTime.GetTime() > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (nMode) ? (((nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD)) ? nSpeed : 0) : ((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2));
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_EXACTTIME, (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME, ((nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) && (nMode & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND, ((!nMode || (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) && (nMode & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC, (!nMode || (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL, ((nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME, (nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL, ((nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) == 0 && tInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_START_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_EXACTTIME)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SLOW)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_FAST)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL));
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd;
	CTCDiagnosticsOversamplingDumpOpenDialog  *pDialog;

	if ((pDialog = GetParentDialog()))
	{
		for (pDialog->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pDialog->GetRetrieveSpeed(nSpeed);
			pDialog->GetRetrieveInterval(tInterval);
			pDialog->GetRetrieveStartTime(tStartTime);
			pDialog->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	if ((pTCDiagnosticsOversamplingDumpWnd = GetParentDisplay()))
	{
		for (pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pTCDiagnosticsOversamplingDumpWnd->GetRetrieveSpeed(nSpeed);
			pTCDiagnosticsOversamplingDumpWnd->GetRetrieveInterval(tInterval);
			pTCDiagnosticsOversamplingDumpWnd->GetRetrieveStartTime(tStartTime);
			pTCDiagnosticsOversamplingDumpWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC, OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL, OnRetrieveInterval)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRetrieveDialog message handlers

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10)), Spinbox_SetRange(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME), TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_MINIMUMINTERVAL, TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_MAXIMUMINTERVAL), GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TITLE)->SetWindowText(m_szTitle); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TITLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TITLE)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TYPE)->EnableWindow();
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnRetrieveByTime()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnRetrieveByEnd()
{
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnRetrieveAutomatic()
{
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SLOW)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_FAST)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnRetrievePseudoRealtime()
{
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL, FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(FALSE);
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnRetrieveManual()
{
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL, TRUE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnRetrieveInterval()
{
	Spinbox_SetPos(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME), TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_DEFAULTINTERVAL);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME)->SetFocus();
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnOK()
{
	CString  szLayout;
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd;
	CTCDiagnosticsOversamplingDumpOpenDialog  *pDialog;
	CHourglassCursor  cCursor;

	for (; !GetParentDialog(); )
	{
		if (!IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC) && !IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME) && !IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL))
		{
			if ((pTCDiagnosticsOversamplingDumpWnd = (GetParentDisplay()->GetLayout(szLayout)) ? GetParentDisplay()->Find(GetParentDisplay()->GetType(), DISPLAY_MODE_REALTIME, szLayout) : (CTCDiagnosticsOversamplingDumpWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pTCDiagnosticsOversamplingDumpWnd); pTCDiagnosticsOversamplingDumpWnd != GetParentDisplay(); )
				{
					GetParentDisplay()->PostMessage(WM_CLOSE);
					break;
				}
				EndDialog(IDOK);
				return;
			}
		}
		GetParentDisplay()->OnCloseRetrieveDialog(IDOK);
		break;
	}
	for (; (pDialog = GetParentDialog()); )
	{
		pDialog->OnCloseRetrieveDialog(IDOK);
		break;
	}
	CDisplayDialog::OnOK();
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpOpenDialog dialog

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpOpenDialog, CDisplayDialog)

CTCDiagnosticsOversamplingDumpOpenDialog::CTCDiagnosticsOversamplingDumpOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCDiagnosticsOversamplingDumpOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCDiagnosticsOversamplingDumpOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CTCDiagnosticsOversamplingDumpOpenDialog::IDD);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::Initialize()
{
	m_nRetrieveMode = 0;
	m_nRetrieveSpeed = 0;
	m_nLayoutSamples = 0;
	m_tRetrieveStartTime = 0;
	m_tRetrieveStopTime = 0;
	m_tRetrieveInterval = 0;
	m_bLayoutBadData = FALSE;
	m_bLayoutToolTips = FALSE;
	m_bLayoutInvalidData = FALSE;
	m_nLayoutBackgroundColor[0] = 0;
	m_nLayoutBackgroundColor[1] = 0;
	ZeroMemory(&m_fntLayoutTitle[0], sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutTitle[1], sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutItems[0], sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutItems[1], sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutValues, sizeof(LOGFONT));
	return TRUE;
}

CString CTCDiagnosticsOversamplingDumpOpenDialog::GetTitle() CONST
{
	CString  szTitle[2];

	if (GetType() == TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_GLOBAL)
	{
		szTitle[0] = STRING(IDS_DISPLAY_TITLE_GLOBALTCDIAGNOSTICSOVERSAMPLINGDUMP);
		return szTitle[0];
	}
	if (GetType() == TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_NORMAL)
	{
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->GetWindowText(szTitle[0]);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_TCDIAGNOSTICSOVERSAMPLINGDUMP), (LPCTSTR)szTitle[0]);
		return szTitle[1];
	}
	return STRING(IDS_DISPLAY_TITLE_TCDIAGNOSTICSOVERSAMPLINGDUMP);
}

UINT CTCDiagnosticsOversamplingDumpOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME)) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_GLOBAL : TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_NORMAL);
}

UINT CTCDiagnosticsOversamplingDumpOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	CString  szTitle;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;

	for (GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->GetWindowText(szTitle); (pLayout = m_pLayouts.GetAt(m_pLayouts.Find(szTitle))); )
	{
		cLayout.Copy(pLayout);
		return TRUE;
	}
	if (cLayout.Copy(&m_cLayout))
	{
		cLayout.SetName(szTitle);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutListTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
		{
			CopyMemory(pTitleFont, &m_fntLayoutTitle[0], sizeof(LOGFONT));
			return TRUE;
		}
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
		{
			CopyMemory(pTitleFont, &m_fntLayoutTitle[1], sizeof(LOGFONT));
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutListItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST
{
	if (IsLayoutModified())
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
		{
			CopyMemory(pItemsFont, &m_fntLayoutItems[0], sizeof(LOGFONT));
			return TRUE;
		}
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
		{
			CopyMemory(pItemsFont, &m_fntLayoutItems[1], sizeof(LOGFONT));
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutListValuesFont(UINT nPane, LPLOGFONT pValuesFont) CONST
{
	if (IsLayoutModified())
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
		{
			CopyMemory(pValuesFont, &m_fntLayoutValues, sizeof(LOGFONT));
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutGridBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	if (IsLayoutModified())
	{
		nNumbersColor = m_nLayoutBackgroundColor[0];
		nValuesColor = m_nLayoutBackgroundColor[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutSampleLimit(UINT &nLimit) CONST
{
	if (IsLayoutModified())
	{
		nLimit = m_nLayoutSamples;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutInvalidData;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutBadData;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutToolTips;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::IsLayoutModified() CONST
{
	CTCDiagnosticsOversamplingDumpLayout  cLayout;
	LOGFONT  fntSample = { 0 };

	return((!m_cLayout.Compare(&cLayout) || memcmp(&m_fntLayoutTitle[0], &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutTitle[1], &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutItems[0], &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutItems[1], &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutValues, &fntSample, sizeof(LOGFONT)) || m_nLayoutBackgroundColor[0] != 0 || m_nLayoutBackgroundColor[1] != 0 || m_nLayoutSamples != 0 || m_bLayoutInvalidData || m_bLayoutBadData || m_bLayoutToolTips) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return((m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	tInterval = m_tRetrieveInterval;
	return(((m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	szFileName = ((m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR)m_szRetrieveFileName : EMPTYSTRING;
	return !szFileName.IsEmpty();
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::GetPrintJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpOpenDialog::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)CDisplayDialog::GetParent());
}

VOID CTCDiagnosticsOversamplingDumpOpenDialog::EnumLayouts()
{
	INT  nLayout;
	INT  nLayouts;
	CByteArray  nLayoutsInfo;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;
	CProfile  cProfile;

	for (nLayout = 0, nLayouts = (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY) && cProfile.GetTelecommandDiagnosticsOversamplingDumpsInfo(nLayoutsInfo) && m_pLayouts.Unmap(nLayoutsInfo)) ? (INT)m_pLayouts.GetSize() : 0, SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_RESETCONTENT); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts.GetAt(nLayout))) SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pLayout->GetName());
		continue;
	}
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::Check(BOOL bModified) CONST
{
	CString  szTitle;

	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->GetWindowText(szTitle);
	return((IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME) || (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY) && !szTitle.IsEmpty() && (GetParent()->Find(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, GetType()), GetMode(), szTitle) || IsRetrievingModified()))) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCDiagnosticsOversamplingDumpOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCDiagnosticsOversamplingDumpOpenDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpOpenDialog message handlers

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckRadioButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE_NORMAL, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE_NORMAL, IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE_NORMAL);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY, FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY)->EnableWindow();
	EnumLayouts();
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnTypeNormal()
{
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnEditchangeTitle()
{
	CString  szTitle;

	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->GetWindowText(szTitle);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS)->EnableWindow((!GetParent()->Find(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, GetType()), GetMode(), szTitle)) ? !szTitle.IsEmpty() : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->ShowWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szTitle) >= 0 && CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szTitle) >= 0) ? CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnSelchangeTitle()
{
	CString  szTitle;

	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS)->EnableWindow((!GetParent()->Find(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, GetType()), GetMode(), (szTitle = Combobox_GetText(GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY), (INT)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_GETCURSEL)))))) ? !szTitle.IsEmpty() : FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->ShowWindow((CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnRealtimeMode()
{
	SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_RESETCONTENT);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnHistoryMode()
{
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	if (IsDlgButtonChecked(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY))
	{
		if (!GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->GetWindowTextLength() && !SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_GETCOUNT))
		{
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY_STATIC)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->EnableWindow();
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS)->EnableWindow(FALSE);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->EnableWindow(FALSE);
			EnumLayouts();
		}
		if (!IsWindow(m_dlgRetrievals.GetSafeHwnd()))
		{
			ReportEvent((m_dlgRetrievals.Create(this, (GetLayout(cLayout) && !cLayout.GetName().IsEmpty()) ? cLayout.GetName() : STRING(IDS_WINDOW_UNKNOWNTITLE)) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->SetFocus();
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnRemove()
{
	INT  nIndex;
	CString  szTitle;
	CProfile  cProfile;
	CByteArray  nDumpsInfo;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->GetWindowText(szTitle); (pLayout = m_pLayouts.GetAt((nIndex = m_pLayouts.Find(szTitle)))); )
	{
		for (SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szTitle)), SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)-1), m_pLayouts.RemoveAt(nIndex); m_pLayouts.Map(nDumpsInfo); )
		{
			cProfile.SetTelecommandDiagnosticsOversamplingDumpsInfo(nDumpsInfo);
			break;
		}
		delete pLayout;
		break;
	}
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(m_cLayout);
			m_dlgSettings.GetLayoutTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntLayoutTitle[0]);
			m_dlgSettings.GetLayoutTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntLayoutTitle[1]);
			m_dlgSettings.GetLayoutItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntLayoutItems[0]);
			m_dlgSettings.GetLayoutItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_fntLayoutItems[1]);
			m_dlgSettings.GetLayoutValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_fntLayoutValues);
			m_dlgSettings.GetLayoutBackgroundColors(m_nLayoutBackgroundColor[0], m_nLayoutBackgroundColor[1]);
			m_dlgSettings.GetLayoutSampleLimit(m_nLayoutSamples);
			m_dlgSettings.GetLayoutInvalidDataMode(m_bLayoutInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(m_bLayoutBadData);
			m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
		}
		if (m_dlgSettings.IsRetrievingModified()) m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		m_dlgRetrievals.GetMode(m_nRetrieveMode);
		m_dlgRetrievals.GetSpeed(m_nRetrieveSpeed);
		m_dlgRetrievals.GetInterval(m_tRetrieveInterval);
		m_dlgRetrievals.GetStartTime(m_tRetrieveStartTime);
		m_dlgRetrievals.GetStopTime(m_tRetrieveStopTime);
	}
	if (nCode != IDOK || !m_nRetrieveMode)
	{
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY, FALSE);
		SendDlgItemMessage(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY, CB_RESETCONTENT);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS)->EnableWindow(FALSE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE)->EnableWindow(FALSE);
	}
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnOK()
{
	INT  nIndex;
	CString  szTitle;
	CProfile  cProfile;
	CByteArray  nDumpsInfo;
	CTCDiagnosticsOversamplingDumpLayout  *pLayout;
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd[2];
	CHourglassCursor  cCursor;

	if ((pTCDiagnosticsOversamplingDumpWnd[0] = GetParent()))
	{
		for (GetDlgItem(IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY)->GetWindowText(szTitle); (pTCDiagnosticsOversamplingDumpWnd[1] = pTCDiagnosticsOversamplingDumpWnd[0]->Find(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, GetType()), GetMode(), szTitle)); )
		{
			GetDisplayArea()->ActivateDisplay(pTCDiagnosticsOversamplingDumpWnd[1]);
			EndDialog(IDCANCEL);
			return;
		}
		if (!pTCDiagnosticsOversamplingDumpWnd[0]->OnCloseOpenDialog(IDOK))
		{
			EndDialog(-1);
			return;
		}
		for (; (pLayout = ((nIndex = m_pLayouts.Find(szTitle)) >= 0) ? m_pLayouts.GetAt(nIndex) : new CTCDiagnosticsOversamplingDumpLayout); )
		{
			if (((nIndex < 0 && GetLayout(*pLayout) && m_pLayouts.Add(pLayout) >= 0) || nIndex >= 0) && m_pLayouts.Map(nDumpsInfo))
			{
				cProfile.SetTelecommandDiagnosticsOversamplingDumpsInfo(nDumpsInfo);
				break;
			}
			if (m_pLayouts.Find(szTitle) < 0 && nIndex < 0) delete pLayout;
			break;
		}
	}
	else
	{
		EndDialog(-1);
		return;
	}
	CDisplayDialog::OnOK();
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CTCDiagnosticsOversamplingDumpOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TCDIAGNOSTICSOVERSAMPLINGDUMPOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRetrieveThread

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpRetrieveThread, CThread)

CTCDiagnosticsOversamplingDumpRetrieveThread::CTCDiagnosticsOversamplingDumpRetrieveThread() : CThread()
{
	m_nMode = 0;
	m_nSpeed = 0;
	m_tInterval = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_pbFlag = (LPLONG)NULL;
	m_bInit[0] = (HANDLE)NULL;
	m_bInit[1] = (HANDLE)NULL;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_STOP] = (HANDLE)NULL;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE)NULL;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOBACKWARD] = (HANDLE)NULL;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE)NULL;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALBACKWARD] = (HANDLE)NULL;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE)NULL;
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveThread::Start(CTCDiagnosticsOversamplingDumpWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime)
{
	m_nMode = nMode;
	m_nSpeed = nSpeed;
	m_pbFlag = pbFlag;
	m_bInit[0] = bInit;
	m_bInit[1] = bContinue;
	m_tInterval = tInterval;
	m_tStartTime = tStartTime;
	m_tStopTime = tStopTime;
	m_szFileName = pszFileName;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOBACKWARD] = bRetrieveAutoBackward;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALBACKWARD] = bRetrieveManualBackward;
	m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CTCDiagnosticsOversamplingDumpRetrieveThread::Run()
{
	UINT  nAction;
	UINT  nResult;
	DWORD  dwResult;
	TIMETAG  tTime;
	CTimeKey  tTimeKey;
	CTimeTag  tTimeTag[2];
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)GetThreadInfo();

	StartRetrieving();
	if (m_cTMEnvironment.Create(GetDatabase()))
	{
		if (m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), GetRetrieveFileName(), &m_cTMEnvironment))
		{
			for (BeginWaitCursor(), pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode((m_nMode = (m_nMode & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD)) ? ((m_nMode & ~(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE)) | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) : (m_nMode & ~(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE)))), pTCDiagnosticsOversamplingDumpWnd->Reset(&m_cTMEnvironment), SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE), nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = GetRetrieveStartTime())), nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT && !pTCDiagnosticsOversamplingDumpWnd->IsInitialized(); )
			{
				SwitchToThread();
				continue;
			}
			for (; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
			{
				if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) && !pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pTCDiagnosticsOversamplingDumpWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) || pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										ReportEvent((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
										pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->Reset(&m_cTMEnvironment);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
					}
					if (pTCDiagnosticsOversamplingDumpWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
						{
							if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
							{
								pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
								continue;
							}
							break;
						}
					}
					if (nResult & HISTORYFILE_SUCCESS)
					{
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						}
					}
					else
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
						pTCDiagnosticsOversamplingDumpWnd->Reset(&m_cTMEnvironment);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) && !pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pTCDiagnosticsOversamplingDumpWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE)) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) || pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) || nAction != TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALFORWARD + 1; EndWaitCursor())
								{
									for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
									{
										if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
										{
											if (pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
											continue;
										}
										if (nResult & HISTORYFILE_SUCCESS)
										{
											if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
											{
												ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
												pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
												pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
											}
										}
										break;
									}
									if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) || pTCDiagnosticsOversamplingDumpWnd->GetMode() == DISPLAY_MODE_REALTIME || dwResult == WAIT_OBJECT_0)
									{
										EndWaitCursor();
										break;
									}
									nAction = 0;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->Reset(&m_cTMEnvironment);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
					}
					if (pTCDiagnosticsOversamplingDumpWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = (nAction != TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALBACKWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1; EndWaitCursor())
						{
							for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
							{
								if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
								{
									if (pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
									continue;
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
									{
										ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
										pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
										pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
										pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
									}
								}
								break;
							}
							if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) || dwResult == WAIT_OBJECT_0)
							{
								EndWaitCursor();
								break;
							}
							nAction = 0;
						}
					}
					if (!(nResult & HISTORYFILE_SUCCESS))
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
						pTCDiagnosticsOversamplingDumpWnd->Reset(&m_cTMEnvironment);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) && !pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pTCDiagnosticsOversamplingDumpWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME) || pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE))
							{
								for (tTimeTag[0] = ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) ? ((nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey)) : CTimeTag(tTimeKey), tTimeTag[1] = CTimeTag(), tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if ((dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, (((nResult & HISTORYFILE_TMUNIT) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TMUNIT) ? (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() - tTime) / 1000) : (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() - tTime) / 1000)) : 0)) != WAIT_TIMEOUT) break;
										if ((!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) || !tTimeTag[0].GetTime()))
										{
											tTimeTag[0] = (nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey);
											tTimeTag[1] = tTime = CTimeTag().GetTime();
										}
										if (!(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pTCDiagnosticsOversamplingDumpWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										ReportEvent((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
										pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(pTCDiagnosticsOversamplingDumpWnd->GetRetrieveMode() | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
							pTCDiagnosticsOversamplingDumpWnd->Reset(&m_cTMEnvironment);
							pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
							break;
						}
					}
					if (pTCDiagnosticsOversamplingDumpWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME))
				{
					while ((dwResult = ((dwResult < WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_STOP + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) == 0) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND : 0;
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(m_nMode);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
					}
					if ((dwResult = ((dwResult < WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) == 0) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND : 0;
						nAction = TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOFORWARD;
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(m_nMode);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) == 0) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND : 0;
						nAction = TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOBACKWARD;
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(m_nMode);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE;
						nAction = TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALFORWARD;
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(m_nMode);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE;
						nAction = TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALBACKWARD;
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(m_nMode);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1)
					{
						m_nMode = (GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) == 0) ? TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND : 0;
						nAction = TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
						pTCDiagnosticsOversamplingDumpWnd->SetRetrieveMode(m_nMode);
						pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
				}
				break;
			}
			m_cTMProcessEngine.Close();
		}
		else
		{
			SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE);
			ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
		}
		m_cTMEnvironment.Destroy();
	}
	else
	{
		SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE);
		ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
	}
	StopRetrieving();
	EndWaitCursor();
	return 0;
}

VOID CTCDiagnosticsOversamplingDumpRetrieveThread::StartRetrieving()
{
	InterlockedExchange(m_pbFlag, TRUE);
}

VOID CTCDiagnosticsOversamplingDumpRetrieveThread::StopRetrieving()
{
	InterlockedExchange(m_pbFlag, FALSE);
}

UINT CTCDiagnosticsOversamplingDumpRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT CTCDiagnosticsOversamplingDumpRetrieveThread::GetRetrieveSpeed() CONST
{
	return((IsThreadActive()) ? m_nSpeed : 0);
}

CTimeSpan CTCDiagnosticsOversamplingDumpRetrieveThread::GetRetrieveInterval() CONST
{
	return((IsThreadActive()) ? m_tInterval.GetTotalSeconds() : 0);
}

CTimeKey CTCDiagnosticsOversamplingDumpRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey CTCDiagnosticsOversamplingDumpRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

CString CTCDiagnosticsOversamplingDumpRetrieveThread::GetRetrieveFileName() CONST
{
	return((IsThreadActive()) ? (LPCTSTR)m_szFileName : EMPTYSTRING);
}

VOID CTCDiagnosticsOversamplingDumpRetrieveThread::BeginWaitCursor(BOOL bForced)
{
	POINT  ptCursor;
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, MAKELONG(TRUE, ((m_nMode & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE) != TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE || bForced) ? TRUE : FALSE)), SetCursorPos(ptCursor.x, ptCursor.y); (pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)GetThreadInfo()); )
	{
		pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
		break;
	}
}

VOID CTCDiagnosticsOversamplingDumpRetrieveThread::EndWaitCursor()
{
	POINT  ptCursor;
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, LOWORD(*m_pbFlag)), SetCursorPos(ptCursor.x, ptCursor.y); (pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)GetThreadInfo()); )
	{
		pTCDiagnosticsOversamplingDumpWnd->UpdateBars();
		break;
	}
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpToolBar

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpToolBar, CDisplayToolBar)

CTCDiagnosticsOversamplingDumpToolBar::CTCDiagnosticsOversamplingDumpToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpStatusBar

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpStatusBar, CDisplayStatusBar)

CTCDiagnosticsOversamplingDumpStatusBar::CTCDiagnosticsOversamplingDumpStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CTCDiagnosticsOversamplingDumpStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)CTimeTag().FormatGmt(), (LPCTSTR)CString(CTimeTag().FormatGmt().Right(1), GetDatabase()->GetTMPacketTagLength()), -1, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_QUALITYGOOD));
			SetPaneInfo(CommandToIndex(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MESSAGEPANE), ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE);
					break;
				}
			}
			m_wndToolTip.SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
			m_wndToolTip.Activate(TRUE);
		}
		return TRUE;
	}
	return FALSE;
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpStatusBar::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpStatusBar message handlers

void CTCDiagnosticsOversamplingDumpStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CTCDiagnosticsOversamplingDumpStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CTCDiagnosticsOversamplingDumpStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpToolTip

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpToolTip, CDisplayToolTip)

CTCDiagnosticsOversamplingDumpToolTip::CTCDiagnosticsOversamplingDumpToolTip() : CDisplayToolTip()
{
	return;
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpToolTip)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpDocument

IMPLEMENT_DYNAMIC(CTCDiagnosticsOversamplingDumpDocument, CDocument)

CTCDiagnosticsOversamplingDumpDocument::CTCDiagnosticsOversamplingDumpDocument() : CDocument()
{
	return;
}

CTCDiagnosticsOversamplingDumpDocument::~CTCDiagnosticsOversamplingDumpDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersTextView

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersTextView, CTextView)

CTCDiagnosticsOversamplingDumpParametersTextView::CTCDiagnosticsOversamplingDumpParametersTextView() : CTextView()
{
	m_tSampleTime = 0;
	m_nSampleLimit = 0;
	m_nLayoutBackgroundColor[0] = VGA_COLOR_LTYELLOW;
	m_nLayoutBackgroundColor[1] = GetSysColor(COLOR_WINDOW);
	m_nLayoutBackgroundColor[2] = GetSysColor(COLOR_WINDOW);
	m_hToolTipCursor = (HCURSOR)NULL;
	m_bInvalidDataMode = FALSE;
	m_bBadDataMode = FALSE;
	m_bToolTipMode = TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle)
{
	if (CTextView::Create(pParentWnd, rect, dwStyle))
	{
		SetTextSpacings(1, 1);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetLayout(LPCTSTR pszLayout)
{
	CTextViewLock  cLock(this);

	m_cLayout.SetName(pszLayout);
	return TRUE;
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout)
{
	INT  nParameter;
	INT  nParameters;
	CUIntArray  nWidths;
	CUIntArray  nColumns;
	CUIntArray  nFormats;
	CStringArray  szColumns;
	CStringArray  szParameters;
	COversamplingParameter  *pOversamplingParameter[2];
	CTextViewLock  cLock(this);

	if ((m_cLayout.GetAttributes() & (TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN)) != (cLayout.GetAttributes() & (TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN)) || !GetColumnCount() || !m_cLayout.COversamplingParameters::Compare(&cLayout))
	{
		for (nParameter = 0, nParameters = (m_cLayout.GetSize() == cLayout.GetSize()) ? (INT)m_cLayout.GetSize() : -1; nParameter < nParameters; nParameter = nParameter + 1)
		{
			if ((pOversamplingParameter[1] = ((pOversamplingParameter[0] = m_cLayout.GetAt(nParameter))) ? cLayout.GetAt(nParameter) : (COversamplingParameter *)NULL))
			{
				if (pOversamplingParameter[0]->GetTag() != pOversamplingParameter[1]->GetTag()) break;
				continue;
			}
		}
		for (; nParameter != nParameters; )
		{
			Reset();
			break;
		}
		for (m_cLayout.Copy(&cLayout); m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN; )
		{
			nColumns.Add(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER);
			break;
		}
		for (; m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN; )
		{
			nColumns.Add(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME);
			break;
		}
		for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter++)
		{
			for (; m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN; )
			{
				nColumns.Add(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE);
				break;
			}
			for (; m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN; )
			{
				nColumns.Add(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT);
				break;
			}
			if ((pOversamplingParameter[0] = m_cLayout.GetAt(nParameter)))
			{
				szParameters.Add(pOversamplingParameter[0]->GetTag());
				continue;
			}
		}
		return(LookupColumnsName(nColumns, szParameters, szColumns, nFormats) && CalcColumnsWidth(nColumns, szColumns, nWidths) && SetColumns(szColumns, nWidths, nFormats));
	}
	return m_cLayout.Copy(&cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	INT  nParameter;
	INT  nParameters;
	CUIntArray  nFormats;
	CStringArray  szColumns;
	CStringArray  szParameters;
	COversamplingParameter  *pOversamplingParameter;
	CTextViewLock  cLock(this);

	if (m_cLayout.Copy(&cLayout))
	{
		for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pOversamplingParameter = m_cLayout.GetAt(nParameter)))
			{
				szParameters.Add(pOversamplingParameter->GetTag());
				continue;
			}
		}
		return(LookupColumnsName(nColumns, szParameters, szColumns, nFormats) && SetColumns(szColumns, nWidths, nFormats));
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetLayout(CString &szLayout) CONST
{
	CTextViewLock  cLock(this);

	szLayout = m_cLayout.GetName();
	return TRUE;
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	CTextViewLock  cLock(this);

	return cLayout.Copy(&m_cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	if (cLayout.Copy(&m_cLayout))
	{
		for (nIndex = 0, nCount = (GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetSize() : -1, nColumns.RemoveAll(); nIndex < nCount; nIndex++)
		{
			nColumns.Add(LookupColumnName(szColumns.GetAt(nIndex)));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetTitleFont(CFont *pFont)
{
	return CTextView::SetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetTitleFont(CONST LOGFONT *plfFont)
{
	return CTextView::SetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetTitleFont(CFont *pFont) CONST
{
	return CTextView::GetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetTitleFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetItemsFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetItemsFont(&lfFont) : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetItemsFont(CONST LOGFONT *plfFont)
{
	CTextViewLock  cLock(this);

	if (CTextView::SetTextFont(plfFont))
	{
		SetTextSpacings(max(LOWORD(GetTextSpacings()), 1), max(HIWORD(GetTextSpacings()), 1));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetItemsFont(CFont *pFont) CONST
{
	return CTextView::GetTextFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetItemsFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTextFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetValuesFont(CFont *pFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!pFont)
	{
		if (GetValuesFont(&lfFont))
		{
			SetValuesFont(&lfFont);
			return TRUE;
		}
		if (GetItemsFont(&lfFont))
		{
			lfFont.lfWeight = FW_BOLD;
			lfFont.lfWidth = 0;
			return SetValuesFont(&lfFont);
		}
		return FALSE;
	}
	return((pFont->GetLogFont(&lfFont)) ? SetValuesFont(&lfFont) : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetValuesFont(CONST LOGFONT *plfFont)
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nIndex < nCount; nIndex++)
	{
		if (LookupColumnName(szColumns.GetAt(nIndex)) != TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER  &&  LookupColumnName(szColumns.GetAt(nIndex)) != TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME  &&  LookupColumnName(szColumns.GetAt(nIndex)) != TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)
		{
			SetColumnFont(nIndex, plfFont);
			continue;
		}
	}
	for (m_cLayoutFont.DeleteObject(); m_cLayoutFont.CreateFontIndirect(plfFont); )
	{
		RecalcContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetValuesFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return(GetValuesFont(&lfFont) && pFont->CreateFontIndirect(&lfFont));
}
BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetValuesFont(LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(this);

	return((m_cLayoutFont.GetSafeHandle() && m_cLayoutFont.GetObject(sizeof(LOGFONT), plfFont) > 0) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor)
{
	CTextViewLock  cLock(this);

	m_nLayoutBackgroundColor[0] = nNumbersColor;
	m_nLayoutBackgroundColor[1] = nValuesColor;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	CTextViewLock  cLock(this);

	nNumbersColor = m_nLayoutBackgroundColor[0];
	nValuesColor = m_nLayoutBackgroundColor[1];
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetSampleLimit(UINT nLimit)
{
	m_nSampleLimit = nLimit;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetSampleLimit(UINT &nLimit) CONST
{
	nLimit = m_nSampleLimit;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::EnableInvalidDataMode(BOOL bEnable)
{
	m_bInvalidDataMode = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::IsInvalidDataModeEnabled() CONST
{
	return m_bInvalidDataMode;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTipMode = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::IsToolTipModeEnabled() CONST
{
	return m_bToolTipMode;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::Initialize(CTMEnvironment *pTMEnvironment)
{
	Reset();
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::Update(CTMEnvironment *pTMEnvironment)
{
	INT  nPos;
	INT  nRow;
	INT  nColumn;
	INT  nSample;
	INT  nSamples;
	INT  nParameter;
	INT  nParameters;
	UINT  nToolTip;
	UINT  nStatus[2];
	CPoint  ptToolTip;
	CString  szBlocks;
	CString  szCalTable;
	CString  szToolTip[2];
	ULONGLONG  nValue[2];
	CTMParameter  *pTMParameter;
	CTextViewAttribute  cAttribute;
	COversamplingParameter  *pOversamplingParameter[2];
	CTCDiagnosticsOversamplingDumpLayout  cOversamplingLayout;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;
	CTCDiagnosticsOversamplingDumpSamples  pOversamplingSamples;
	CTextViewLock  cLock(this);

	if (!pTMEnvironment)
	{
		DrawContent();
		return TRUE;
	}
	for (cOversamplingLayout.Copy(&m_cLayout); GetTCService()->DecodeTCDiagnosticsOversamplingDump(pTMEnvironment, cOversamplingLayout, (cOversamplingLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC) ? TRUE : FALSE); )
	{
		for (nParameter = 0, nParameters = (m_cLayout.GetSize() == cOversamplingLayout.GetSize()) ? (INT)m_cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
		{
			if ((pOversamplingParameter[1] = ((pOversamplingParameter[0] = m_cLayout.GetAt(nParameter))) ? cOversamplingLayout.GetAt(nParameter) : (COversamplingParameter *)NULL))
			{
				if (pOversamplingParameter[0]->GetTag() != pOversamplingParameter[1]->GetTag()) break;
				continue;
			}
			break;
		}
		if ((nParameter != nParameters  &&  SetLayout(cOversamplingLayout)) || nParameter == nParameters)
		{
			if ((pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(cOversamplingLayout.GetValidityParameter()))))
			{
				for (nParameter = 0, nParameters = (!pTMParameter->GetRawValue(0, nValue[0], nStatus[0]) || nValue[0] != 1) ? (INT)cOversamplingLayout.GetSize() : 0; nParameter < nParameters; nParameter++)
				{
					if ((pOversamplingParameter[0] = cOversamplingLayout.GetAt(nParameter)) && pOversamplingParameter[0]->GetValueCount() > 0)
					{
						for (nSample = 0, nSamples = pOversamplingParameter[0]->GetValueCount(); nSample < nSamples; nSample++)
						{
							if (pOversamplingParameter[0]->GetRawValue(nSample, nValue[1], nStatus[1], szCalTable))
							{
								nStatus[1] = (nStatus[1] & ~TMPARAMETER_STATUS_VALID) | TMPARAMETER_STATUS_INVALID;
								pOversamplingParameter[0]->SetRawValue(pTMEnvironment->GetTMUnit(), nSample, nValue[1], nStatus[1], szCalTable);
							}
						}
					}
				}
			}
			for (szBlocks = (cOversamplingLayout.GetTimeTag() != m_tSampleTime) ? TranslateParameterBlock(cOversamplingLayout, pOversamplingSamples, &cAttribute) : EMPTYSTRING, nSample = 0, nSamples = (INT)pOversamplingSamples.GetSize(); nSample < nSamples && !szBlocks.IsEmpty(); nSample++)
			{
				while (m_nSampleLimit <= (UINT)GetSampleCount() && m_nSampleLimit > 0)
				{
					if (!DeleteText(0, m_nSampleLimit == (UINT)GetSampleCount())) break;
					continue;
				}
				while (m_nSampleLimit <= (UINT)m_pSamples.GetSize() && m_nSampleLimit > 0)
				{
					if ((pOversamplingSample = m_pSamples.GetAt(0))) delete pOversamplingSample;
					m_pSamples.RemoveAt(0);
				}
				if ((nPos = szBlocks.Find(EOL)) >= 0)
				{
					if (AddText(szBlocks.Left(nPos), &cAttribute, FALSE) >= 0)
					{
						m_pSamples.Add(pOversamplingSamples.GetAt(nSample));
						pOversamplingSamples.SetAt(nSample, NULL);
					}
					szBlocks = szBlocks.Mid(nPos + 1);
					continue;
				}
				if (AddText(szBlocks, &cAttribute) >= 0)
				{
					m_pSamples.Add(pOversamplingSamples.GetAt(nSample));
					pOversamplingSamples.SetAt(nSample, NULL);
				}
				SetCurSample(GetSampleCount() - 1);
				break;
			}
			for (m_cLayout.Copy(&cOversamplingLayout), m_tSampleTime = cOversamplingLayout.GetTimeTag(); (pOversamplingParameter[0] = (m_wndToolTip.IsVisibleAtPoint(ptToolTip)) ? new COversamplingParameter : (COversamplingParameter *)NULL); )
			{
				if ((pOversamplingSample = (FindTextFromPoint(ptToolTip, nRow, nColumn, FALSE)) ? new CTCDiagnosticsOversamplingDumpSample : (CTCDiagnosticsOversamplingDumpSample *)NULL) != (CTCDiagnosticsOversamplingDumpSample *)NULL)
				{
					if ((nToolTip = FindParameterSample(nRow, nColumn, pOversamplingSample, pOversamplingParameter[0])) == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER || nToolTip == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE)
					{
						for (szToolTip[0] = ConstructToolTipTitle(pOversamplingSample, pOversamplingParameter[0], nToolTip), szToolTip[1] = ConstructToolTipText(pOversamplingSample, pOversamplingParameter[0], nToolTip); !szToolTip[0].IsEmpty() || !szToolTip[1].IsEmpty(); )
						{
							m_wndToolTip.Update(szToolTip[0], szToolTip[1]);
							break;
						}
					}
					delete pOversamplingSample;
				}
				delete pOversamplingParameter[0];
				break;
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}

VOID CTCDiagnosticsOversamplingDumpParametersTextView::Reset(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	m_tSampleTime = 0;
	m_pSamples.RemoveAll();
	DeleteAllText();
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetCurSample(INT nIndex)
{
	return SetCurText(nIndex);
}

INT CTCDiagnosticsOversamplingDumpParametersTextView::GetCurSample() CONST
{
	return GetCurText();
}

INT CTCDiagnosticsOversamplingDumpParametersTextView::GetSampleCount() CONST
{
	return GetTextCount();
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, LOGFONT *pValuesFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	UINT  nRange[2];
	CString  szItem;
	CString  szColumn;
	CTimeKey  tRange[2];
	CStringArray  szParameters;
	CStringArray  szColumnsText;
	CTextViewAttribute  *pAttribute;
	CTCDiagnosticsOversamplingDumpSample  *pItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (GetColumns(szColumns) && GetTitleFont(pTitleFont) && GetTextFont(pItemsFont) && GetValuesFont(pValuesFont)) ? (INT)m_pSamples.GetSize() : -1, szContents.RemoveAll(), pAttributes.RemoveAll(), pSymbols.RemoveAll(), nSymbolIDs.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pSamples.GetAt(nItem)) && (!pJobInfo->GetPrintRange(nRange[0], nRange[1]) || (nItem + 1 >= (INT)nRange[0] && nItem + 1 <= (INT)nRange[1])) && (!pJobInfo->GetPrintRange(tRange[0], tRange[1]) || (pItem->GetTimeTag().GetTimeInSeconds() >= tRange[0].GetTime() && pItem->GetTimeTag().GetTimeInSeconds() <= tRange[1].GetTime())))
		{
			if ((pAttribute = new CTextViewAttribute))
			{
				if (GetText(nItem, szItem, pAttribute))
				{
					for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						pAttribute->SetColumnFormat(nColumn, GetColumnFormat(nColumn));
						continue;
					}
					pAttributes.Add(pAttribute);
					szContents.Add(szItem);
					continue;
				}
				delete pAttribute;
			}
			break;
		}
	}
	if (pJobInfo->GetPrintParameters(szParameters) > 0)
	{
		for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (szColumns.GetAt(nColumn) != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) && szColumns.GetAt(nColumn) != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME) && szColumns.GetAt(nColumn) != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT))
			{
				for (nParameter = 0, nParameters = (INT)szParameters.GetSize(); nParameter < nParameters; nParameter++)
				{
					if ((nPos = (szColumn = szColumns.GetAt(nColumn)).Find(EOL)) >= 0)
					{
						if (szColumn.Left(nPos) == szParameters.GetAt(nParameter)) break;
						continue;
					}
				}
				if (nParameter == nParameters)
				{
					for (nItem = 0, nItems = (INT)szContents.GetSize(); nItem < nItems; nItem++)
					{
						if (nColumn < ConvertText(szContents.GetAt(nItem), szColumnsText))
						{
							for (szColumnsText.RemoveAt(nColumn); nColumn < szColumns.GetSize() - 1 && szColumns.GetAt(nColumn + 1) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT); )
							{
								szColumnsText.RemoveAt(nColumn);
								break;
							}
							szContents.SetAt(nItem, ConvertText(szColumnsText));
						}
					}
					for (szColumns.RemoveAt(nColumn); nColumn < szColumns.GetSize() && szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT); )
					{
						szColumns.RemoveAt(nColumn);
						nColumns--;
						nColumn--;
						break;
					}
					nColumns--;
					nColumn--;
				}
			}
		}
	}
	if (!pSymbols.GetSize())
	{
		pSymbols.Add(m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION]);
		pSymbols.Add(m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_WARNING]);
		pSymbols.Add(m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_ERROR]);
	}
	if (!nSymbolIDs.GetSize())
	{
		nSymbolIDs.Add(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPINFORMATION);
		nSymbolIDs.Add(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPWARNING);
		nSymbolIDs.Add(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPERROR);
	}
	return((nItem == nItems  &&  pSymbols.GetSize() == nSymbolIDs.GetSize()) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpParametersTextView::RefreshContent()
{
	INT  nIndex;
	INT  nSample;
	INT  nSamples;
	INT  nColumn;
	INT  nColumns;
	CString  szSample;
	CString  szColumn;
	CTextViewAttribute  cAttribute;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
	{
		for (SetColumnColor(nColumn, LookupColumnColor(LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))))); LookupColumnName(szColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER; )
		{
			SetColumnFormat(nColumn, GetColumnFormat(nColumn) | DT_SINGLELINE);
			break;
		}
		if (LookupColumnName(szColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE)
		{
			SetColumnFormat(nColumn, (GetColumnFormat(nColumn) & ~(DT_LEFT | DT_CENTER)) | DT_RIGHT);
			SetColumnFont(nColumn, &m_cLayoutFont);
			continue;
		}
		SetColumnFont(nColumn, &m_wndContentCtrl.m_cFont);
	}
	for (nSample = 0, nSamples = (INT)m_pSamples.GetSize(); nSample < nSamples; nSample++)
	{
		if ((pOversamplingSample = m_pSamples.GetAt(nSample)) != (CTCDiagnosticsOversamplingDumpSample *)NULL)
		{
			for (szSample = TranslateParameterBlock(nSample, nSamples, pOversamplingSample, &cAttribute); !szSample.IsEmpty(); )
			{
				if (nSample < GetSampleCount() && SetText(nSample, szSample, &cAttribute, FALSE)) break;
				if (nSample >= GetSampleCount() && AddText(szSample, &cAttribute, FALSE) >= 0) break;
				szSample.Empty();
				break;
			}
			if (szSample.IsEmpty()) break;
		}
	}
	while (nSample < GetSampleCount())
	{
		if (!DeleteText(nSample, FALSE)) break;
		continue;
	}
	SetCurSample(((nIndex = GetCurSample()) < 0) ? (GetSampleCount() - 1) : nIndex);
	RecalcContent();
}

VOID CTCDiagnosticsOversamplingDumpParametersTextView::DrawContent()
{
	CTextView::DrawContent();
}
VOID CTCDiagnosticsOversamplingDumpParametersTextView::DrawContent(CDC *pDC)
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nHeight;
	CRect  rArea;
	CRect  rText[2];
	CRect  rContent;

	for (nItem = FindFirstVisibleText(), nItems = FindLastVisibleText() + 1, nItems = min(GetTextCount() - 1, nItems), m_wndContentCtrl.GetClientRect(rContent), rText[0] = m_wndContentCtrl.CalcTextRect(GetTextCount() - 1), nWidth = rContent.Width(), nHeight = m_wndContentCtrl.CalcTextLines(SPACE); nItem >= 0 && nItem <= nItems; nItem++)
	{
		DrawBackground(pDC, nItem, -1, (rText[0].right < rContent.right) ? CRect(max(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rContent.left), max(rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rContent.top), rContent.right, (rText[1] = m_wndContentCtrl.CalcTextRect(nItem)).bottom + m_wndContentCtrl.m_wTextSpacing[1]) : CRect(0, 0, 0, 0));
		DrawText(pDC, nItem, m_wndContentCtrl.m_szContentText.GetAt(nItem));
	}
	for (rArea.SetRect(rContent.left, (GetTextCount() > 0) ? min(max(rText[0].bottom + m_wndContentCtrl.m_wTextSpacing[1], rContent.top), rContent.bottom) : rContent.top, rContent.right, rContent.bottom), nItem = GetTextCount(); rArea.top < rContent.bottom; rArea.DeflateRect(0, nHeight, 0, 0), nItem++)
	{
		DrawBackground(pDC, nItem, -1, CRect(rArea.left, rArea.top, rArea.right, rArea.top + nHeight));
		continue;
	}
}

VOID CTCDiagnosticsOversamplingDumpParametersTextView::DrawText(INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, pszText);
}
VOID CTCDiagnosticsOversamplingDumpParametersTextView::DrawText(CDC *pDC, INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(pDC, nItem, pszText);
}
VOID CTCDiagnosticsOversamplingDumpParametersTextView::DrawText(INT nItem, INT nColumn, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, nColumn, pszText);
}
VOID CTCDiagnosticsOversamplingDumpParametersTextView::DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText)
{
	CDC  cDC;
	INT  nPos;
	BOOL  bState;
	UINT  nFormat;
	UINT  nSymbol;
	CRect  rText[3];
	CFont  cTextFont;
	CFont  *pOldFont;
	CSize  sizeSymbol;
	CSize  sizeBitmap;
	CPoint  ptBitmap;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	COLORREF  nColor[2];
	CTextViewAttribute  *pAttribute;

	for (m_wndContentCtrl.GetClientRect(rText[0]), rText[1] = m_wndContentCtrl.CalcTextRect(nItem, nColumn), sizeBitmap.cx = m_wndContentCtrl.m_wTextIndent[0] + rText[1].Width() + m_wndContentCtrl.m_wTextIndent[1], sizeBitmap.cy = m_wndContentCtrl.m_wTextSpacing[0] + rText[1].Height() + m_wndContentCtrl.m_wTextSpacing[1]; rText[2].IntersectRect(rText[0], CRect(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rText[1].right + m_wndContentCtrl.m_wTextIndent[1], rText[1].bottom + m_wndContentCtrl.m_wTextSpacing[1])); )
	{
		for (nFormat = GetColumnFormat(nItem, nColumn), nColor[0] = GetColumnColor(nItem, nColumn), bState = TRUE; (pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nItem)); )
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
					for (cDC.SetBkMode(TRANSPARENT), cDC.SetTextColor(nColor[0]), DrawBackground(&cDC, nItem, nColumn, CRect(m_wndContentCtrl.m_wTextIndent[0] - rText[1].left, 0, sizeBitmap.cx, sizeBitmap.cy)); (pOldFont = (GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)); )
					{
						cDC.DrawText(((nPos = (nColumn == FindColumnIndex(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER))) ? (INT)_tcscspn(pszText, CString(GetSymbolDelimiter())) : -1) >= 0) ? CString(pszText).Left(nPos) : pszText, CRect(m_wndContentCtrl.m_wTextIndent[0], m_wndContentCtrl.m_wTextSpacing[0], sizeBitmap.cx - m_wndContentCtrl.m_wTextIndent[0], sizeBitmap.cy - m_wndContentCtrl.m_wTextSpacing[0]), nFormat);
						cDC.SelectObject(pOldFont);
						break;
					}
					if (nColumn == FindColumnIndex(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER)))
					{
						for (sizeSymbol.cx = sizeSymbol.cy = 0, nColor[1] = cDC.GetNearestColor(VGA_COLOR_WHITE), cTextFont.DeleteObject(); (pOldFont = (GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)); )
						{
							sizeSymbol.cx = sizeSymbol.cy = cDC.GetTextExtent(SPACE).cy;
							m_sizeAlertSymbols = sizeSymbol;
							cDC.SelectObject(pOldFont);
							cTextFont.DeleteObject();
							break;
						}
						for (nSymbol = (!_tcsstr(pszText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION))) ? ((!_tcsstr(pszText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING))) ? ((_tcsstr(pszText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR))) ? TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_ERROR : -1) : TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_WARNING) : TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION; nSymbol != (UINT)-1; )
						{
							if (bState) m_pAlertSymbols[nSymbol]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, pszText).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
							break;
						}
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

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem)
{
	CDC  cDC[2];
	INT  nIndex;
	INT  nWidth;
	INT  nHeight;
	BOOL  bBackground;
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	BLENDFUNCTION  sBlend;

	if (cDC[0].CreateCompatibleDC(pDC))
	{
		if (cDC[1].CreateCompatibleDC(pDC))
		{
			if (cBitmap[0].CreateCompatibleBitmap(pDC, (nWidth = rItem.right - rItem.left), (nHeight = rItem.bottom - rItem.top)))
			{
				if (cBitmap[1].CreateCompatibleBitmap(pDC, nWidth, nHeight))
				{
					if ((pOldBitmap[0] = cDC[0].SelectObject(&cBitmap[0])))
					{
						if ((pOldBitmap[1] = cDC[1].SelectObject(&cBitmap[1])))
						{
							for (sBlend.BlendFlags = 0, sBlend.BlendOp = AC_SRC_OVER, sBlend.AlphaFormat = 0, sBlend.SourceConstantAlpha = TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COLUMNTRANSPARENCY; nWidth > 0 && nHeight > 0; )
							{
								cDC[0].FillSolidRect(0, 0, ((nIndex = max(FindColumnIndex(LookupColumnName(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER)), FindColumnIndex(LookupColumnName(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME)))) >= 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex) - m_wndContentCtrl.m_nScrollPos[0]) : 0, nHeight, m_nLayoutBackgroundColor[0]);
								cDC[0].FillSolidRect((m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(max(nIndex, 0)) - m_wndContentCtrl.m_nScrollPos[0]) : 0, 0, (m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? max(nWidth - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(max(nIndex, 0)) + m_wndContentCtrl.m_nScrollPos[0], 0) : 0, nHeight, m_nLayoutBackgroundColor[1]);
								cDC[0].FillSolidRect((m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(m_wndHeaderCtrl.m_nColumnsWidth.GetUpperBound()) - m_wndContentCtrl.m_nScrollPos[0]) : 0, 0, (m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? max(nWidth - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(m_wndHeaderCtrl.m_nColumnsWidth.GetUpperBound()) + m_wndContentCtrl.m_nScrollPos[0], 0) : nWidth, nHeight, m_nLayoutBackgroundColor[2]);
								for (cDC[1].FillSolidRect(0, 0, nWidth, nHeight, VGA_COLOR_WHITE), cDC[1].AlphaBlend(0, 0, nWidth, nHeight, &cDC[0], 0, 0, nWidth, nHeight, sBlend), sBlend.SourceConstantAlpha = 0xFF - 2 * sBlend.SourceConstantAlpha; nItem == GetCurSample() && nColumn >= 0; )
								{
									for (cDC[0].SetTextColor(pDC->GetTextColor()); (bBackground = CTextView::DrawBackground(&cDC[0], nItem, nColumn, CRect(0, 0, nWidth, nHeight))); )
									{
										cDC[1].AlphaBlend(0, 0, nWidth, nHeight, &cDC[0], 0, 0, nWidth, nHeight, sBlend);
										break;
									}
									for (pDC->SetTextColor(cDC[0].GetTextColor()); !bBackground; )
									{
										cDC[1].BitBlt(0, 0, nWidth, nHeight, &cDC[0], 0, 0, SRCCOPY);
										break;
									}
									break;
								}
								pDC->BitBlt(rItem.left, rItem.top, nWidth, nHeight, &cDC[1], 0, 0, SRCCOPY);
								break;
							}
							cDC[0].SelectObject(pOldBitmap[0]);
							cDC[1].SelectObject(pOldBitmap[1]);
							cBitmap[0].DeleteObject();
							cBitmap[1].DeleteObject();
							cDC[0].DeleteDC();
							cDC[1].DeleteDC();
							return TRUE;
						}
						cDC[0].SelectObject(pOldBitmap[0]);
					}
					cBitmap[1].DeleteObject();
				}
				cBitmap[0].DeleteObject();
			}
			cDC[1].DeleteDC();
		}
		cDC[0].DeleteDC();
	}
	return FALSE;
}

CTCDiagnosticsOversamplingDumpParametersView *CTCDiagnosticsOversamplingDumpParametersTextView::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpParametersView *)CTextView::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpParametersTextView::GetParentDisplay() CONST
{
	CTCDiagnosticsOversamplingDumpParametersView  *pView;

	return(((pView = GetParent())) ? pView->GetParentDisplay() : (CTCDiagnosticsOversamplingDumpWnd *)NULL);
}

CString CTCDiagnosticsOversamplingDumpParametersTextView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) return STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER);
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME) return STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME);
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE) return STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE);
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) return STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT);
	return EMPTYSTRING;
}
UINT CTCDiagnosticsOversamplingDumpParametersTextView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER))) return TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER;
	if (!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME))) return TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE))) return TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE;
	if (!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT))) return TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT;
	return TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE;
}

INT CTCDiagnosticsOversamplingDumpParametersTextView::LookupColumnsName(CONST CUIntArray &nColumns, CONST CStringArray &szParameters, CStringArray &szColumns, CUIntArray &nFormats) CONST
{
	INT  nIndex[2];
	INT  nCount[2];
	CString  szColumn;

	for (nIndex[0] = 0, nCount[0] = (INT)nColumns.GetSize(), szColumns.RemoveAll(), nFormats.RemoveAll(), nCount[1] = 0; nIndex[0] < nCount[0]; nIndex[0]++)
	{
		for (szColumns.Add(LookupColumnName(nColumns.GetAt(nIndex[0]))), nFormats.Add(HDF_LEFT); szColumns.GetAt(szColumns.GetUpperBound()) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE); )
		{
			for (szColumn = (nCount[1] < szParameters.GetSize()) ? TranslateColumnName(szParameters.GetAt(nCount[1])) : EMPTYSTRING; !szColumn.IsEmpty(); )
			{
				szColumns.SetAt(szColumns.GetUpperBound(), szColumn);
				nFormats.SetAt(nFormats.GetUpperBound(), HDF_CENTER);
				break;
			}
			if (szColumn.IsEmpty())
			{
				for (szColumns.RemoveAt(szColumns.GetUpperBound()), nFormats.RemoveAt(nFormats.GetUpperBound()); nIndex[0] < nColumns.GetUpperBound() && nColumns.GetAt(nIndex[0] + 1) > TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE; )
				{
					nIndex[0]++;
					break;
				}
			}
			nCount[1]++;
			break;
		}
	}
	return((INT)szColumns.GetSize());
}

COLORREF CTCDiagnosticsOversamplingDumpParametersTextView::LookupColumnColor(UINT nColumn) CONST
{
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) return GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersNumberColumnColor();
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME) return GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersTimeColumnColor();
	if (nColumn != TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) return GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersValueColumnColor();
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) return GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersUnitColumnColor();
	return GetSysColor(COLOR_WINDOWTEXT);
}

CString CTCDiagnosticsOversamplingDumpParametersTextView::TranslateColumnName(LPCTSTR pszColumn) CONST
{
	CString  szColumn;
	CDatabaseTMParameter  *pParameter;

	for (szColumn = pszColumn; (pParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pszColumn))) && !pParameter->GetDescription().IsEmpty(); )
	{
		szColumn.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TITLEITEM_PARAMETERFORMAT), pszColumn, (LPCTSTR)pParameter->GetDescription());
		break;
	}
	return((pParameter != (CDatabaseTMParameter *)NULL) ? szColumn : EMPTYSTRING);
}

CString CTCDiagnosticsOversamplingDumpParametersTextView::TranslateParameterBlock(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CTCDiagnosticsOversamplingDumpSamples &pSamples, CTextViewAttribute *pAttribute) CONST
{
	INT  nIndex;
	INT  nBlock;
	INT  nBlocks;
	INT  nColumn;
	INT  nColumns;
	INT  nSample;
	INT  nSamples;
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus;
	BOOL  bOutSet;
	CString  szText;
	CString  szBlocks;
	CString  szColumn;
	CString  szWarning;
	CString  szInformation;
	ULONGLONG  nValue;
	CStringTools  cStringTools;
	CTimeTagArray  tParameterTimes;
	CDatabaseTMParameter  *pParameter;
	COversamplingParameter  *pOversamplingParameter;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;

	for (nParameter = 0, nParameters = (INT)cLayout.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOversamplingParameter = cLayout.GetAt(nParameter)) != (COversamplingParameter *)NULL)
		{
			for (nSample = 0, nSamples = pOversamplingParameter->GetValueCount(); nSample < nSamples; nSample++)
			{
				tParameterTimes.SetAtGrow(nSample, (nSample < tParameterTimes.GetSize()) ? max(pOversamplingParameter->GetLastUpdateTime().GetTime() + (1000000 * (TIMETAG)cLayout.GetSamplingRate()*nSample), tParameterTimes.GetAt(nSample).GetTime()) : (pOversamplingParameter->GetLastUpdateTime().GetTime() + (TIMETAG)(1000000 * cLayout.GetSamplingRate()*nSample)));
				continue;
			}
		}
	}
	for (nBlock = 0, nBlocks = (INT)tParameterTimes.GetSize(), pSamples.RemoveAll(); nBlock < nBlocks; nBlock++)
	{
		for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(), szInformation.Empty(), szWarning.Empty(), nIndex = 0; nColumn < nColumns; nColumn++)
		{
			for (pAttribute->SetColumnColor(nColumn, LookupColumnColor(LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))))), szText.Empty(); szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER); )
			{
				szText = cStringTools.ConvertIntToPaddedString((INT)(m_wndContentCtrl.m_szContentText.GetSize() + nBlock + 1), max(max(cStringTools.ConvertIntToString((INT)(m_wndContentCtrl.m_szContentText.GetSize() + nBlocks)).GetLength(), cStringTools.ConvertIntToString(m_nSampleLimit).GetLength()), 3));
				if ((pOversamplingSample = (!nBlock) ? m_pSamples.GetAt((INT)(m_pSamples.GetSize() - 1)) : (CTCDiagnosticsOversamplingDumpSample *)NULL) != (CTCDiagnosticsOversamplingDumpSample *)NULL)
				{
					if (cLayout.GetTimeTag().GetTime() - pOversamplingSample->GetTimeTag().GetTime() >= (2 * 1000000 * (TIMETAG)cLayout.GetSamplingRate()) && cLayout.GetSamplingRate() > 0.0)
					{
						szText += CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING);
						szWarning = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_SAMPLINGRATEMISMATCH);
						break;
					}
					if (cLayout.GetTimeTag() < pOversamplingSample->GetTimeTag())
					{
						szText += CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION);
						szInformation = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_BACKWARDSSAMPLINGTIP);
					}
					if (cLayout.GetSamplingRate() == 0.0)
					{
						szText += CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING);
						szWarning = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_NOSAMPLINGRATECHECKS);
						break;
					}
				}
				szText += (cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION)) : EMPTYSTRING;
				break;
			}
			for (; szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME); )
			{
				szText = tParameterTimes.GetAt(nBlock).FormatGmt();
				break;
			}
			if (szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) && szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME))
			{
				if ((pParameter = ((pOversamplingParameter = cLayout.GetAt(nIndex))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOversamplingParameter->GetTag())) : (CDatabaseTMParameter *)NULL)) szText = (szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)) ? ((pOversamplingParameter->GetRawValue(nBlock, nValue, nStatus) && ((nStatus & TMPARAMETER_STATUS_VALID) || m_bInvalidDataMode) && ((nStatus & TMPARAMETER_STATUS_GOOD) || m_bBadDataMode) && pOversamplingParameter->GetValueAsText(GetDatabase(), nBlock, pOversamplingParameter->GetAttributes(), ((((pOversamplingParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && (pOversamplingParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE)) || (pOversamplingParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) && pParameter->GetDecimalDigits() > 0) ? pParameter->GetDecimalDigits() : -1, szText, bOutSet, FALSE)) ? ((bOutSet) ? ((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szText + GetDatabase()->GetTMNumCalTablePointOutsideText()) : ((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szText + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : szText)) : szText) : EMPTYSTRING) : pParameter->GetUnit();
				nIndex = ((szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) && nColumn < nColumns - 1 && m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn + 1) != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)) || szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)) ? (nIndex + 1) : nIndex;
			}
			szBlocks += (nColumn > 0) ? (GetColumnDelimiter() + szText) : szText;
		}
		if ((pOversamplingSample = new CTCDiagnosticsOversamplingDumpSample))
		{
			for (pOversamplingSample->SetBlock(nBlock), pOversamplingSample->COversamplingParameters::Copy(&cLayout); cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL; )
			{
				pOversamplingSample->SetAlertMessage(TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_NOAUTOSAMPLINGDETECTION));
				break;
			}
			if (!szInformation.IsEmpty()) pOversamplingSample->SetAlertMessage(TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION, szInformation);
			if (!szWarning.IsEmpty()) pOversamplingSample->SetAlertMessage(TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_WARNING, szWarning);
			pSamples.Add(pOversamplingSample);
		}
		if (nBlock < nBlocks - 1)
		{
			szBlocks += EOL;
			continue;
		}
	}
	return((nBlocks == pSamples.GetSize()) ? szBlocks : EMPTYSTRING);
}
CString CTCDiagnosticsOversamplingDumpParametersTextView::TranslateParameterBlock(INT nIndex, INT nCount, CONST CTCDiagnosticsOversamplingDumpSample *pSample, CTextViewAttribute *pAttribute) CONST
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	UINT  nAlertType;
	UINT  nStatus;
	BOOL  bOutSet;
	CString  szText;
	CString  szBlock;
	CString  szColumn;
	CString  szMessage;
	ULONGLONG  nValue;
	CStringTools  cStringTools;
	CDatabaseTMParameter  *pParameter;
	COversamplingParameter  *pOversamplingParameter;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(), nParameter = 0; nColumn < nColumns; nColumn++)
	{
		for (pAttribute->SetColumnColor(nColumn, LookupColumnColor(LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))))), szText.Empty(); szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER); )
		{
			for (szText = cStringTools.ConvertIntToPaddedString(nIndex + 1, max(max(cStringTools.ConvertIntToString(nCount).GetLength(), cStringTools.ConvertIntToString(m_nSampleLimit).GetLength()), 3)); (nAlertType = pSample->GetAlertMessage(szMessage)) != TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_NONE; )
			{
				szText += (nAlertType == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION)) : EMPTYSTRING;
				szText += (nAlertType == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_WARNING) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING)) : EMPTYSTRING;
				szText += (nAlertType == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_ERROR) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR)) : EMPTYSTRING;
				break;
			}
			break;
		}
		for (szText = (szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME)) ? (((pOversamplingParameter = pSample->GetAt(nParameter))) ? CTimeTag(pOversamplingParameter->GetLastUpdateTime().GetTime() + (1000000 * (TIMETAG)pSample->GetSamplingRate()*pSample->GetBlock())).FormatGmt() : EMPTYSTRING) : szText; szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) && szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME); )
		{
			if ((pParameter = ((pOversamplingParameter = pSample->GetAt(nParameter))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOversamplingParameter->GetTag())) : (CDatabaseTMParameter *)NULL)) szText = (szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)) ? ((pOversamplingParameter->GetRawValue(pSample->GetBlock(), nValue, nStatus) && ((nStatus & TMPARAMETER_STATUS_VALID) || m_bInvalidDataMode) && ((nStatus & TMPARAMETER_STATUS_GOOD) || m_bBadDataMode) && pOversamplingParameter->GetValueAsText(GetDatabase(), pSample->GetBlock(), pOversamplingParameter->GetAttributes(), ((((pOversamplingParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && (pOversamplingParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE)) || (pOversamplingParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) && pParameter->GetDecimalDigits() > 0) ? pParameter->GetDecimalDigits() : -1, szText, bOutSet, FALSE)) ? ((bOutSet) ? ((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szText + GetDatabase()->GetTMNumCalTablePointOutsideText()) : ((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szText + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : szText)) : szText) : EMPTYSTRING) : pParameter->GetUnit();
			nParameter = ((szColumn != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) && nColumn < nColumns - 1 && m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn + 1) != STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)) || szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)) ? (nParameter + 1) : nParameter;
			break;
		}
		szBlock += (nColumn > 0) ? (GetColumnDelimiter() + szText) : szText;
	}
	return szBlock;
}

INT CTCDiagnosticsOversamplingDumpParametersTextView::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (!m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn).Compare(pszColumn)) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

INT CTCDiagnosticsOversamplingDumpParametersTextView::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	CFont  cFont;
	CFont  *pOldFont;

	if ((pDC = GetDC()))
	{
		for (GetTextFont(&cFont), nWidth = 0; (pOldFont = pDC->SelectObject(&cFont)); )
		{
			nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
			pDC->SelectObject(pOldFont);
			break;
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}
INT CTCDiagnosticsOversamplingDumpParametersTextView::CalcColumnWidth(UINT nColumn, LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	INT  nDxChar;
	CFont  cFont[2];
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		for (GetTitleFont(&cFont[0]), GetTextFont(&cFont[1]), nWidth = 0; (pOldFont = pDC->SelectObject(&cFont[0])); )
		{
			nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
			pDC->SelectObject(pOldFont);
			break;
		}
		if ((pOldFont = pDC->SelectObject(&cFont[1])))
		{
			if ((nDxChar = (pDC->GetTextMetrics(&tmFont) > 0) ? (4 * tmFont.tmAveCharWidth / 3) : 0) > 0)
			{
				nWidth = (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersNumberCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersTimeCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersValueCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCDiagnosticsOversamplingDumpParametersUnitCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}

INT CTCDiagnosticsOversamplingDumpParametersTextView::CalcColumnsWidth(CONST CUIntArray &nColumns, CONST CStringArray &szColumns, CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)nColumns.GetSize(), nWidths.RemoveAll(); nIndex < nCount; nIndex++)
	{
		nWidths.Add((nIndex > 0) ? (nWidths.GetAt(nIndex - 1) + CalcColumnWidth(nColumns.GetAt(nIndex), szColumns.GetAt(nIndex))) : CalcColumnWidth(nColumns.GetAt(nIndex), szColumns.GetAt(nIndex)));
		continue;
	}
	return((nCount == nWidths.GetSize()) ? (INT)nWidths.GetSize() : 0);
}

CRect CTCDiagnosticsOversamplingDumpParametersTextView::CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST
{
	INT  nPos;
	CRect  rText;
	CRect  rSymbol;
	CFont  *pOldFont;
	CString  szText;
	CClientDC  cDC(NULL);

	for (szText = ((nPos = (szText = pszText).Find(GetSymbolDelimiter())) >= 0) ? szText.Left(nPos) : szText, rText = m_wndContentCtrl.CalcTextRect(nRow, nColumn), rSymbol.SetRectEmpty(); (pOldFont = (nColumn == FindColumnIndex(STRING(IDS_TCMANUALSTACK_TITLEITEM_NUMBER)) && !rText.IsRectEmpty()) ? cDC.SelectObject((CFont *)&m_wndContentCtrl.m_cFont) : (CFont *)NULL); )
	{
		rSymbol.SetRect(rText.left + cDC.GetTextExtent(szText + SPACE).cx, rText.top, rText.left + cDC.GetTextExtent(szText + SPACE).cx + m_sizeAlertSymbols.cx, rText.top + m_sizeAlertSymbols.cy);
		rSymbol.SetRect(min(max(rText.left, rSymbol.left), rText.right), rSymbol.top, max(min(rText.right, rSymbol.right), rText.left), rSymbol.bottom);
		rSymbol.InflateRect(0, 0, 1, 1);
		cDC.SelectObject(pOldFont);
		break;
	}
	return rSymbol;
}

UINT CTCDiagnosticsOversamplingDumpParametersTextView::FindParameterSample(INT nRow, INT nColumn, CTCDiagnosticsOversamplingDumpSample *pSample, COversamplingParameter *pParameter) CONST
{
	INT  nIndex;
	CString  szColumn;
	COversamplingParameter  *pOversamplingParameter;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;

	nIndex = (m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN) ? (nColumn - 1) : nColumn;
	nIndex = (m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN) ? (nIndex - 1) : nIndex;
	nIndex = (m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN) ? (nIndex / 2) : nIndex;
	return((nRow < m_pSamples.GetSize() && nColumn < m_wndHeaderCtrl.m_szColumnsText.GetSize()) ? ((LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))) == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER || LookupColumnName(szColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE) ? ((((pOversamplingParameter = ((pOversamplingSample = m_pSamples.GetAt(nRow)) && pSample->Copy(pOversamplingSample)) ? pOversamplingSample->GetAt(nIndex) : (COversamplingParameter *)NULL) && pParameter->Copy(pOversamplingParameter)) || nIndex < 0) ? LookupColumnName(szColumn) : 0) : 0) : 0);
}

TCHAR CTCDiagnosticsOversamplingDumpParametersTextView::GetSymbolDelimiter()
{
	return SPACE[0];
}

CString CTCDiagnosticsOversamplingDumpParametersTextView::ConstructToolTipTitle(CONST CTCDiagnosticsOversamplingDumpSample *pSample, CONST COversamplingParameter *pParameter, UINT nTip) CONST
{
	CString  szTitle;
	CString  szMessage;

	switch (nTip)
	{
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER:
	{ szTitle = (pSample->GetAlertMessage(szMessage) == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION) : EMPTYSTRING;
	szTitle = (pSample->GetAlertMessage(szMessage) == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_WARNING) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING) : szTitle;
	szTitle = (pSample->GetAlertMessage(szMessage) == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_ERROR) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR) : szTitle;
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE:
	{ szTitle.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_TITLE), (LPCTSTR)pParameter->GetTag());
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME:
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT: break;
	}
	return szTitle;
}

CString CTCDiagnosticsOversamplingDumpParametersTextView::ConstructToolTipText(CONST CTCDiagnosticsOversamplingDumpSample *pSample, CONST COversamplingParameter *pParameter, UINT nTip) CONST
{
	UINT  nStatus;
	BOOL  bOutSet;
	ULONGLONG  nValue;
	CString  szText;
	CString  szStatus;
	CString  szMessage;
	CString  szCalTable;
	CString  szValue[4];
	CString  szValueChange;
	CString  szValueUpdate;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	switch (nTip)
	{
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER:
	{ for (szText.Empty(); pSample->GetAlertMessage(szMessage) != TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_NONE; )
	{
		szText = szMessage;
		break;
	}
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE:
	{ if (pParameter->IsInitialized() && pParameter->GetRawValue(pSample->GetBlock(), nValue, nStatus, szCalTable))
	{
		if ((pParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN))
		{
			pParameter->GetValueAsText(GetDatabase(), pSample->GetBlock(), (pParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY, -1, szValue[0]);
			szValue[1].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_BITVALUE));
		}
		if ((pParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
		{
			pParameter->GetValueAsText(GetDatabase(), pSample->GetBlock(), (pParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, -1, szValue[0]);
			szValue[1].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], (pParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_SIGNEDVALUE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_COMPLEMENTVALUE));
		}
		if (pParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER)
		{
			pParameter->GetValueAsText(GetDatabase(), pSample->GetBlock(), (pParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, -1, szValue[0]);
			szValue[1].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_UNSIGNEDVALUE));
		}
		if (pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
		{
			pParameter->GetValueAsText(GetDatabase(), pSample->GetBlock(), (pParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, -1, szValue[0]);
			szValue[1].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_FLOATINGVALUE));
		}
		if ((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
		{
			pParameter->GetValueAsText(GetDatabase(), pSample->GetBlock(), TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_RADIX_DECIMAL, -1, szValue[0]);
			szValue[1].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_UNSIGNEDVALUE));
		}
		for (szValue[0].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_RAWVALUE), nValue), pParameter->GetValueAsText(GetDatabase(), pSample->GetBlock(), pParameter->GetAttributes(), ((pDatabaseTMParameter = (((pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && (pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE)) || (pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetTag())) : (CDatabaseTMParameter *)NULL) && pDatabaseTMParameter->GetDecimalDigits() > 0) ? pDatabaseTMParameter->GetDecimalDigits() : -1, szValue[3], bOutSet, FALSE), szValue[2].Format((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_CALIBRATEDNUMERICALVALUE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_CALIBRATEDSTATUSVALUE), (LPCTSTR)(szValue[3] = (bOutSet) ? ((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szValue[3] + GetDatabase()->GetTMNumCalTablePointOutsideText()) : ((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szValue[3] + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : szValue[3])) : szValue[3]), (LPCTSTR)szCalTable, (bOutSet) ? ((pParameter->GetAttributes() & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_EXTRPOLATEDVALUE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_OUTSETVALUE)) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_INSETVALUE)), szValueChange.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_VALUECHANGE), (LPCTSTR)CTimeTag(pParameter->GetLastChangeTime().GetTime() + (pSample->GetBlock() * 1000000 * (TIMETAG)m_cLayout.GetSamplingRate())).FormatGmt(), (LPCTSTR)pParameter->GetLastChangeTMUnit()), szValueUpdate.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_VALUEUPDATE), (LPCTSTR)CTimeTag(pParameter->GetLastUpdateTime().GetTime() + (TIMETAG)(pSample->GetBlock() * 1000000 * m_cLayout.GetSamplingRate())).FormatGmt(), (LPCTSTR)pParameter->GetLastUpdateTMUnit()), szStatus.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_STATUS), (nStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_GOODQUALITY) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_BADQUALITY), (nStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_VALID) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_INVALID)); pSample->GetBlock() >= 0; )
		{
			szValue[3].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_BLOCK), pSample->GetBlock() + 1);
			szValue[0] = szValue[3] + EOL + szValue[0];
			break;
		}
		szText = (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) && lstrlen(szCalTable) > 0) ? ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValue[2] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1] + EOL + szValue[2])) : ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1]));
		break;
	}
	szText = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_NOVALUE);
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME:
	case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT: break;
	}
	return szText;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::LoadTelecommandSymbols()
{
	INT  nSymbol;
	INT  nSymbols;
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	for (nSymbol = 0, nSymbols = TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION) ? MAKEINTRESOURCE(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPINFORMATION) : ((nSymbol == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_WARNING) ? MAKEINTRESOURCE(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPWARNING) : MAKEINTRESOURCE(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPERROR)), STRING(IDS_RESOURCETYPE_PICTURE))))
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
								if ((m_pAlertSymbols[nSymbol] = new CImage) != (CImage *)NULL)
								{
									if (SUCCEEDED(m_pAlertSymbols[nSymbol]->Load(pIStream)))
									{
										pIStream->Release();
										continue;
									}
									delete m_pAlertSymbols[nSymbol];
									m_pAlertSymbols[nSymbol] = (CImage *)NULL;
								}
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol > 0)
		{
			delete m_pAlertSymbols[--nSymbol];
			m_pAlertSymbols[nSymbol] = (CImage *)NULL;
		}
		break;
	}
	return((nSymbol == nSymbols) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpParametersTextView::FreeTelecommandSymbols()
{
	INT  nSymbol;
	INT  nSymbols;

	for (nSymbol = 0, nSymbols = TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pAlertSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pAlertSymbols[nSymbol]->Destroy();
			delete m_pAlertSymbols[nSymbol];
		}
	}
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CTCDiagnosticsOversamplingDumpParametersTextView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CTextViewLock  cLock(this);

	SetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	SetCurSample((nCount != GetSampleCount()) ? (GetSampleCount() - 1) : nIndex);
	ScrollTo(GetCurSample());
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CTextViewLock  cLock(this);

	nIndex = GetCurSample();
	nCount = GetSampleCount();
	GetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpParametersTextView::PostNcDestroy()
{
	m_tSampleTime = 0;
	m_pSamples.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::Lock()
{
	CTCDiagnosticsOversamplingDumpWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (pParentWnd->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::Unlock()
{
	CTCDiagnosticsOversamplingDumpWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (CTextView::Unlock() && pParentWnd->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpParametersTextView, CTextView)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpParametersTextView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersTextView message handlers

int CTCDiagnosticsOversamplingDumpParametersTextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(this);

	if (CTextView::OnCreate(lpCreateStruct) != -1 && LoadTelecommandSymbols() && LoadToolTipCursor())
	{
		SetValuesFont();
		return 0;
	}
	return -1;
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nRow;
	INT  nColumn;
	UINT  nToolTip;
	LONG  lDataFlag;
	POINT  ptCursor;
	CRect  rContent;
	CString  szText;
	COversamplingParameter  cParameter;
	CTCDiagnosticsOversamplingDumpSample  cSample;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if ((lDataFlag = GetParentDisplay()->IsRetrievingData()) && HIWORD(lDataFlag))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		if ((nToolTip = (IsToolTipModeEnabled() && FindTextFromPoint(ptCursor, nRow, nColumn, FALSE) && GetText(nRow, nColumn, szText)) ? FindParameterSample(nRow, nColumn, &cSample, &cParameter) : 0) == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER)
		{
			if (_tcsstr(szText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION)) || _tcsstr(szText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING)) || _tcsstr(szText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, szText).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
		}
		if (nToolTip == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE)
		{
			SetCursor(GetToolTipCursor());
			return TRUE;
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CTCDiagnosticsOversamplingDumpParametersTextView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nColumn;
	UINT  nToolTip;
	LONG  lDataFlag;
	CFont  cFont[2];
	CPoint  ptToolTip;
	LOGFONT  lfFont[2];
	CString  szParameter;
	CString  szToolTip[2];
	COversamplingParameter  cParameter;
	CTCDiagnosticsOversamplingDumpSample  cSample;
	CTextViewLock  cLock(this);

	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		if (!(lDataFlag = GetParentDisplay()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			if (FindTextFromPoint(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), nRow, nColumn, FALSE) && FindParameterSample(nRow, nColumn, &cSample, &cParameter) == TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE)
			{
				for (szParameter = cParameter.GetTag(), cLock.Release(); !szParameter.IsEmpty(); )
				{
					GetParentDisplay()->ShowParameterInfo(szParameter);
					break;
				}
			}
		}
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (!(lDataFlag = GetParentDisplay()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			if (GetCursor() == GetToolTipCursor() && FindTextFromPoint((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))), nRow, nColumn, FALSE))
			{
				switch ((nToolTip = FindParameterSample(nRow, nColumn, &cSample, &cParameter)))
				{
				case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER:
				case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE:
				{ for (szToolTip[0] = ConstructToolTipTitle(&cSample, &cParameter, nToolTip), szToolTip[1] = ConstructToolTipText(&cSample, &cParameter, nToolTip), GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
				{
					m_wndToolTip.SetTitleFont(&cFont[0]);
					m_wndToolTip.SetTextFont(&cFont[1]);
					break;
				}
				m_wndToolTip.Create(&m_wndContentCtrl, ptToolTip, szToolTip[0], szToolTip[1]);
				break;
				}
				case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME:
				case TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT: break;
				}
			}
		}
		return FALSE;
	}
	if (message == WM_RBUTTONUP)
	{
		m_wndToolTip.Destroy();
		return FALSE;
	}
	return FALSE;
}

void CTCDiagnosticsOversamplingDumpParametersTextView::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	FreeTelecommandSymbols();
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersView view

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersView, CView)

CTCDiagnosticsOversamplingDumpParametersView::CTCDiagnosticsOversamplingDumpParametersView() : CView()
{
	m_pwndList = new CTCDiagnosticsOversamplingDumpParametersTextView;
	m_pParentWnd = (CWnd *)NULL;
}

CTCDiagnosticsOversamplingDumpParametersView::~CTCDiagnosticsOversamplingDumpParametersView()
{
	delete m_pwndList;
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetLayout(LPCTSTR pszLayout)
{
	return m_pwndList->SetLayout(pszLayout);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout)
{
	return m_pwndList->SetLayout(cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_pwndList->SetLayout(cLayout, nColumns, nWidths);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetLayout(CString &szLayout) CONST
{
	return m_pwndList->GetLayout(szLayout);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	return m_pwndList->GetLayout(cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_pwndList->GetLayout(cLayout, nColumns, nWidths);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetTitleFont(CFont *pFont)
{
	return m_pwndList->SetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::SetTitleFont(CONST LOGFONT *plfFont)
{
	return m_pwndList->SetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetTitleFont(CFont *pFont) CONST
{
	return m_pwndList->GetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::GetTitleFont(LOGFONT *plfFont) CONST
{
	return m_pwndList->GetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetItemsFont(CFont *pFont)
{
	return m_pwndList->SetItemsFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::SetItemsFont(CONST LOGFONT *plfFont)
{
	return m_pwndList->SetItemsFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetItemsFont(CFont *pFont) CONST
{
	return m_pwndList->GetItemsFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::GetItemsFont(LOGFONT *plfFont) CONST
{
	return m_pwndList->GetItemsFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetValuesFont(CFont *pFont)
{
	return m_pwndList->SetValuesFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::SetValuesFont(CONST LOGFONT *plfFont)
{
	return m_pwndList->SetValuesFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetValuesFont(CFont *pFont) CONST
{
	return m_pwndList->GetValuesFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpParametersView::GetValuesFont(LOGFONT *plfFont) CONST
{
	return m_pwndList->GetValuesFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor)
{
	return m_pwndList->SetBackgroundColors(nNumbersColor, nValuesColor);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	return m_pwndList->GetBackgroundColors(nNumbersColor, nValuesColor);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetSampleLimit(UINT nLimit)
{
	return m_pwndList->SetSampleLimit(nLimit);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetSampleLimit(UINT &nLimit) CONST
{
	return m_pwndList->GetSampleLimit(nLimit);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::EnableInvalidDataMode(BOOL bEnable)
{
	return m_pwndList->EnableInvalidDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::IsInvalidDataModeEnabled() CONST
{
	return m_pwndList->IsInvalidDataModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::EnableBadDataMode(BOOL bEnable)
{
	return m_pwndList->EnableBadDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::IsBadDataModeEnabled() CONST
{
	return m_pwndList->IsBadDataModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::EnableToolTipMode(BOOL bEnable)
{
	return m_pwndList->EnableToolTipMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::IsToolTipModeEnabled() CONST
{
	return m_pwndList->IsToolTipModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_pwndList->Initialize(pTMEnvironment);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::Update(CTMEnvironment *pTMEnvironment)
{
	return m_pwndList->Update(pTMEnvironment);
}

VOID CTCDiagnosticsOversamplingDumpParametersView::Reset(CTMEnvironment *pTMEnvironment)
{
	return m_pwndList->Reset(pTMEnvironment);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetCurSample(INT nIndex)
{
	return m_pwndList->SetCurSample(nIndex);
}

INT CTCDiagnosticsOversamplingDumpParametersView::GetCurSample() CONST
{
	return m_pwndList->GetCurSample();
}

INT CTCDiagnosticsOversamplingDumpParametersView::GetSampleCount() CONST
{
	return m_pwndList->GetSampleCount();
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, LOGFONT *pValuesFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	return m_pwndList->GetPrintProperties(pJobInfo, szColumns, szContents, pAttributes, pTitleFont, pItemsFont, pValuesFont, pSymbols, nSymbolIDs);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	return m_pwndList->SetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	return m_pwndList->GetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo);
}

VOID CTCDiagnosticsOversamplingDumpParametersView::SetTrackSize(CONST SIZE &size)
{
	m_pwndList->SetTrackSize(size);
}

CSize CTCDiagnosticsOversamplingDumpParametersView::GetTrackSize() CONST
{
	return m_pwndList->GetTrackSize();
}

CTCDiagnosticsOversamplingDumpView *CTCDiagnosticsOversamplingDumpParametersView::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpView *)m_pParentWnd);
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpParametersView::GetParentDisplay() CONST
{
	return(GetParent()->GetParent());
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::Lock()
{
	return m_pwndList->Lock();
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::Unlock()
{
	return m_pwndList->Unlock();
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpParametersView, CView)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpParametersView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersView drawing

void CTCDiagnosticsOversamplingDumpParametersView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersView message handlers

int CTCDiagnosticsOversamplingDumpParametersView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CView::OnCreate(lpCreateStruct) != -1 && m_pwndList->Create(this, ((m_pParentWnd = CView::GetParent())) ? CRect(0, 0, lpCreateStruct->cx, lpCreateStruct->cy) : CRect(0, 0, 0, 0), TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)) ? 0 : -1);
}

void CTCDiagnosticsOversamplingDumpParametersView::OnSize(UINT nType, int cx, int cy)
{
	m_pwndList->MoveWindow(0, 0, cx, cy);
	CView::OnSize(nType, cx, cy);
}

BOOL CTCDiagnosticsOversamplingDumpParametersView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpParametersView::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (IsChild(pOldWnd)) GetParent()->SetFocus();
		else  m_pwndList->SetFocus();
		return;
	}
	CView::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRawDataTextView

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpRawDataTextView, CTextView)

CTCDiagnosticsOversamplingDumpRawDataTextView::CTCDiagnosticsOversamplingDumpRawDataTextView() : CTextView()
{
	m_tSampleTime = 0;
	m_nSampleLimit = 0;
	m_nLayoutBackgroundColor[0] = VGA_COLOR_LTYELLOW;
	m_nLayoutBackgroundColor[1] = GetSysColor(COLOR_WINDOW);
	m_nLayoutBackgroundColor[2] = GetSysColor(COLOR_WINDOW);
	m_hToolTipCursor = (HCURSOR)NULL;
	m_bInvalidDataMode = FALSE;
	m_bBadDataMode = FALSE;
	m_bToolTipMode = TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle)
{
	if (CTextView::Create(pParentWnd, rect, dwStyle))
	{
		SetTextSpacings(1, 1);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetLayout(LPCTSTR pszLayout)
{
	CTextViewLock  cLock(this);

	m_cLayout.SetName(pszLayout);
	return TRUE;
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout)
{
	INT  nParameter;
	INT  nParameters;
	CUIntArray  nWidths;
	CUIntArray  nColumns;
	CStringArray  szColumns;
	COversamplingParameter  *pOversamplingParameter[2];
	CTextViewLock  cLock(this);

	if ((m_cLayout.GetAttributes() & (TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN)) != (cLayout.GetAttributes() & (TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN | TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN)) || !GetColumnCount() || !m_cLayout.COversamplingParameters::Compare(&cLayout))
	{
		for (nParameter = 0, nParameters = (m_cLayout.GetSize() == cLayout.GetSize()) ? (INT)m_cLayout.GetSize() : -1; nParameter < nParameters; nParameter = nParameter + 1)
		{
			if ((pOversamplingParameter[1] = ((pOversamplingParameter[0] = m_cLayout.GetAt(nParameter))) ? cLayout.GetAt(nParameter) : (COversamplingParameter *)NULL))
			{
				if (pOversamplingParameter[0]->GetTag() != pOversamplingParameter[1]->GetTag()) break;
				continue;
			}
		}
		for (; nParameter != nParameters; )
		{
			Reset();
			break;
		}
		for (m_cLayout.Copy(&cLayout); m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN; )
		{
			nColumns.Add(TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER);
			break;
		}
		for (; m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN; )
		{
			nColumns.Add(TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME);
			break;
		}
		for (; m_cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN; )
		{
			nColumns.Add(TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS);
			break;
		}
		return(LookupColumnsName(nColumns, szColumns) && CalcColumnsWidth(nColumns, nWidths) && SetColumns(szColumns, nWidths));
	}
	return m_cLayout.Copy(&cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	return((m_cLayout.Copy(&cLayout)) ? (LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nWidths)) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetLayout(CString &szLayout) CONST
{
	CTextViewLock  cLock(this);

	szLayout = m_cLayout.GetName();
	return TRUE;
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	CTextViewLock  cLock(this);

	return cLayout.Copy(&m_cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	if (cLayout.Copy(&m_cLayout))
	{
		for (nIndex = 0, nCount = (GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetSize() : -1, nColumns.RemoveAll(); nIndex < nCount; nIndex++)
		{
			nColumns.Add(LookupColumnName(szColumns.GetAt(nIndex)));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetTitleFont(CFont *pFont)
{
	return CTextView::SetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetTitleFont(CONST LOGFONT *plfFont)
{
	return CTextView::SetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetTitleFont(CFont *pFont) CONST
{
	return CTextView::GetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetTitleFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetItemsFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetItemsFont(&lfFont) : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetItemsFont(CONST LOGFONT *plfFont)
{
	CTextViewLock  cLock(this);

	if (CTextView::SetTextFont(plfFont))
	{
		SetTextSpacings(max(LOWORD(GetTextSpacings()), 1), max(HIWORD(GetTextSpacings()), 1));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetItemsFont(CFont *pFont) CONST
{
	return CTextView::GetTextFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetItemsFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTextFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor)
{
	CTextViewLock  cLock(this);

	m_nLayoutBackgroundColor[0] = nNumbersColor;
	m_nLayoutBackgroundColor[1] = nValuesColor;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	CTextViewLock  cLock(this);

	nNumbersColor = m_nLayoutBackgroundColor[0];
	nValuesColor = m_nLayoutBackgroundColor[1];
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetSampleLimit(UINT nLimit)
{
	m_nSampleLimit = nLimit;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetSampleLimit(UINT &nLimit) CONST
{
	nLimit = m_nSampleLimit;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::EnableInvalidDataMode(BOOL bEnable)
{
	m_bInvalidDataMode = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::IsInvalidDataModeEnabled() CONST
{
	return m_bInvalidDataMode;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTipMode = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::IsToolTipModeEnabled() CONST
{
	return m_bToolTipMode;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::Initialize(CTMEnvironment *pTMEnvironment)
{
	Reset();
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::Update(CTMEnvironment *pTMEnvironment)
{
	INT  nPos;
	INT  nRow;
	INT  nColumn;
	INT  nSample;
	INT  nSamples;
	UINT  nToolTip;
	CPoint  ptToolTip;
	CString  szBlocks;
	CString  szToolTip[2];
	CTextViewAttribute  cAttribute;
	COversamplingParameters  pOversamplingParameters;
	CTCDiagnosticsOversamplingDumpSamples  pOversamplingSamples;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;
	CTCDiagnosticsOversamplingDumpLayout  cOversamplingLayout;
	CTextViewLock  cLock(this);

	if (!pTMEnvironment)
	{
		DrawContent();
		return TRUE;
	}
	for (cOversamplingLayout.Copy(&m_cLayout); GetTCService()->DecodeTCDiagnosticsOversamplingDump(pTMEnvironment, cOversamplingLayout, (cOversamplingLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC) ? TRUE : FALSE); )
	{
		for (szBlocks = (cOversamplingLayout.GetTimeTag() != m_tSampleTime) ? TranslateRawDataBlock(cOversamplingLayout, pOversamplingSamples, &cAttribute) : EMPTYSTRING, nSample = 0, nSamples = (INT)pOversamplingSamples.GetSize(); nSample < nSamples && !szBlocks.IsEmpty(); nSample++)
		{
			while (m_nSampleLimit <= (UINT)GetSampleCount() && m_nSampleLimit > 0)
			{
				if (!DeleteText(0, m_nSampleLimit == (UINT)GetSampleCount())) break;
				continue;
			}
			while (m_nSampleLimit <= (UINT)m_pSamples.GetSize() && m_nSampleLimit > 0)
			{
				if ((pOversamplingSample = m_pSamples.GetAt(0))) delete pOversamplingSample;
				m_pSamples.RemoveAt(0);
			}
			if ((nPos = szBlocks.Find(EOL)) >= 0)
			{
				if (AddText(szBlocks.Left(nPos), &cAttribute, FALSE) >= 0)
				{
					m_pSamples.Add(pOversamplingSamples.GetAt(nSample));
					pOversamplingSamples.SetAt(nSample, NULL);
				}
				szBlocks = szBlocks.Mid(nPos + 1);
				continue;
			}
			if (AddText(szBlocks, &cAttribute) >= 0)
			{
				m_pSamples.Add(pOversamplingSamples.GetAt(nSample));
				pOversamplingSamples.SetAt(nSample, NULL);
			}
			SetCurSample(GetSampleCount() - 1);
			break;
		}
		for (m_cLayout.Copy(&cOversamplingLayout), m_tSampleTime = cOversamplingLayout.GetTimeTag(); m_wndToolTip.IsVisibleAtPoint(ptToolTip); )
		{
			if ((pOversamplingSample = (FindTextFromPoint(ptToolTip, nRow, nColumn, FALSE)) ? new CTCDiagnosticsOversamplingDumpSample : (CTCDiagnosticsOversamplingDumpSample *)NULL))
			{
				if ((nToolTip = FindParameterSample(nRow, nColumn, pOversamplingSample)) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER || nToolTip == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)
				{
					for (szToolTip[0] = ConstructToolTipTitle(pOversamplingSample, nToolTip), szToolTip[1] = ConstructToolTipText(pOversamplingSample, nToolTip); !szToolTip[0].IsEmpty() || !szToolTip[1].IsEmpty(); )
					{
						m_wndToolTip.Update(szToolTip[0], szToolTip[1]);
						break;
					}
				}
				delete pOversamplingSample;
			}
			break;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CTCDiagnosticsOversamplingDumpRawDataTextView::Reset(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	m_tSampleTime = 0;
	m_pSamples.RemoveAll();
	DeleteAllText();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetCurSample(INT nIndex)
{
	return SetCurText(nIndex);
}

INT CTCDiagnosticsOversamplingDumpRawDataTextView::GetCurSample() CONST
{
	return GetCurText();
}

INT CTCDiagnosticsOversamplingDumpRawDataTextView::GetSampleCount() CONST
{
	return GetTextCount();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	UINT  nRange[2];
	CString  szItem;
	CTimeKey  tRange[2];
	CTextViewAttribute  *pAttribute;
	CTCDiagnosticsOversamplingDumpSample  *pItem;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (GetColumns(szColumns) && GetTitleFont(pTitleFont) && GetTextFont(pItemsFont)) ? (INT)m_pSamples.GetSize() : -1, szContents.RemoveAll(), pAttributes.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pSamples.GetAt(nItem)) && (!pJobInfo->GetPrintRange(nRange[0], nRange[1]) || (nItem + 1 >= (INT)nRange[0] && nItem + 1 <= (INT)nRange[1])) && (!pJobInfo->GetPrintRange(tRange[0], tRange[1]) || (pItem->GetTimeTag().GetTimeInSeconds() >= tRange[0].GetTime() && pItem->GetTimeTag().GetTimeInSeconds() <= tRange[1].GetTime())))
		{
			if ((pAttribute = new CTextViewAttribute))
			{
				if (GetText(nItem, szItem, pAttribute))
				{
					for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						pAttribute->SetColumnFormat(nColumn, GetColumnFormat(nColumn));
						continue;
					}
					pAttributes.Add(pAttribute);
					szContents.Add(szItem);
					continue;
				}
				delete pAttribute;
			}
			break;
		}
	}
	if (!pSymbols.GetSize())
	{
		pSymbols.Add(m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_INFORMATION]);
		pSymbols.Add(m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_WARNING]);
		pSymbols.Add(m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_ERROR]);
	}
	if (!nSymbolIDs.GetSize())
	{
		nSymbolIDs.Add(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPINFORMATION);
		nSymbolIDs.Add(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPWARNING);
		nSymbolIDs.Add(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPERROR);
	}
	return((nItem == nItems  &&  pSymbols.GetSize() == nSymbolIDs.GetSize()) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpRawDataTextView::RefreshContent()
{
	INT  nIndex;
	INT  nSample;
	INT  nSamples;
	INT  nColumn;
	INT  nColumns;
	CString  szSample;
	CString  szColumn;
	CTextViewAttribute  cAttribute;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
	{
		for (SetColumnColor(nColumn, LookupColumnColor(LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))))); LookupColumnName(szColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER; )
		{
			SetColumnFormat(nColumn, GetColumnFormat(nColumn) | DT_SINGLELINE);
			break;
		}
	}
	for (nSample = 0, nSamples = (INT)m_pSamples.GetSize(); nSample < nSamples; nSample++)
	{
		if ((pOversamplingSample = m_pSamples.GetAt(nSample)) != (CTCDiagnosticsOversamplingDumpSample *)NULL)
		{
			for (szSample = TranslateParameterBlock(nSample, nSamples, pOversamplingSample, &cAttribute); !szSample.IsEmpty(); )
			{
				if (nSample < GetSampleCount() && SetText(nSample, szSample, &cAttribute, FALSE)) break;
				if (nSample >= GetSampleCount() && AddText(szSample, &cAttribute, FALSE) >= 0) break;
				szSample.Empty();
				break;
			}
			if (szSample.IsEmpty()) break;
		}
	}
	while (nSample < GetSampleCount())
	{
		if (!DeleteText(nSample, FALSE)) break;
		continue;
	}
	SetCurSample(((nIndex = GetCurSample()) < 0) ? (GetSampleCount() - 1) : nIndex);
	RecalcContent();
}

VOID CTCDiagnosticsOversamplingDumpRawDataTextView::DrawContent()
{
	CTextView::DrawContent();
}
VOID CTCDiagnosticsOversamplingDumpRawDataTextView::DrawContent(CDC *pDC)
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nHeight;
	CRect  rArea;
	CRect  rText[2];
	CRect  rContent;

	for (nItem = FindFirstVisibleText(), nItems = FindLastVisibleText() + 1, nItems = min(GetTextCount() - 1, nItems), m_wndContentCtrl.GetClientRect(rContent), rText[0] = m_wndContentCtrl.CalcTextRect(GetTextCount() - 1), nWidth = rContent.Width(), nHeight = m_wndContentCtrl.CalcTextLines(SPACE); nItem >= 0 && nItem <= nItems; nItem++)
	{
		DrawBackground(pDC, nItem, -1, (rText[0].right < rContent.right) ? CRect(max(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rContent.left), max(rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rContent.top), rContent.right, (rText[1] = m_wndContentCtrl.CalcTextRect(nItem)).bottom + m_wndContentCtrl.m_wTextSpacing[1]) : CRect(0, 0, 0, 0));
		DrawText(pDC, nItem, m_wndContentCtrl.m_szContentText.GetAt(nItem));
	}
	for (rArea.SetRect(rContent.left, (GetTextCount() > 0) ? min(max(rText[0].bottom + m_wndContentCtrl.m_wTextSpacing[1], rContent.top), rContent.bottom) : rContent.top, rContent.right, rContent.bottom), nItem = GetTextCount(); rArea.top < rContent.bottom; rArea.DeflateRect(0, nHeight, 0, 0), nItem++)
	{
		DrawBackground(pDC, nItem, -1, CRect(rArea.left, rArea.top, rArea.right, rArea.top + nHeight));
		continue;
	}
}

VOID CTCDiagnosticsOversamplingDumpRawDataTextView::DrawText(INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, pszText);
}
VOID CTCDiagnosticsOversamplingDumpRawDataTextView::DrawText(CDC *pDC, INT nItem, LPCTSTR pszText)
{
	CTextView::DrawText(pDC, nItem, pszText);
}
VOID CTCDiagnosticsOversamplingDumpRawDataTextView::DrawText(INT nItem, INT nColumn, LPCTSTR pszText)
{
	CTextView::DrawText(nItem, nColumn, pszText);
}
VOID CTCDiagnosticsOversamplingDumpRawDataTextView::DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText)
{
	CDC  cDC;
	INT  nPos;
	BOOL  bState;
	UINT  nFormat;
	UINT  nSymbol;
	CRect  rText[3];
	CFont  cTextFont;
	CFont  *pOldFont;
	CSize  sizeSymbol;
	CSize  sizeBitmap;
	CPoint  ptBitmap;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	COLORREF  nColor[2];
	CTextViewAttribute  *pAttribute;

	for (m_wndContentCtrl.GetClientRect(rText[0]), rText[1] = m_wndContentCtrl.CalcTextRect(nItem, nColumn), sizeBitmap.cx = m_wndContentCtrl.m_wTextIndent[0] + rText[1].Width() + m_wndContentCtrl.m_wTextIndent[1], sizeBitmap.cy = m_wndContentCtrl.m_wTextSpacing[0] + rText[1].Height() + m_wndContentCtrl.m_wTextSpacing[1]; rText[2].IntersectRect(rText[0], CRect(rText[1].left - m_wndContentCtrl.m_wTextIndent[0], rText[1].top - m_wndContentCtrl.m_wTextSpacing[0], rText[1].right + m_wndContentCtrl.m_wTextIndent[1], rText[1].bottom + m_wndContentCtrl.m_wTextSpacing[1])); )
	{
		for (nFormat = GetColumnFormat(nItem, nColumn), nColor[0] = GetColumnColor(nItem, nColumn), bState = TRUE; (pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nItem)); )
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
					for (cDC.SetBkMode(TRANSPARENT), cDC.SetTextColor(nColor[0]), DrawBackground(&cDC, nItem, nColumn, CRect(m_wndContentCtrl.m_wTextIndent[0] - rText[1].left, 0, sizeBitmap.cx, sizeBitmap.cy)); (pOldFont = (GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)); )
					{
						cDC.DrawText(((nPos = (nColumn == FindColumnIndex(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER))) ? (INT)_tcscspn(pszText, CString(GetSymbolDelimiter())) : -1) >= 0) ? CString(pszText).Left(nPos) : pszText, CRect(m_wndContentCtrl.m_wTextIndent[0], m_wndContentCtrl.m_wTextSpacing[0], sizeBitmap.cx - m_wndContentCtrl.m_wTextIndent[0], sizeBitmap.cy - m_wndContentCtrl.m_wTextSpacing[0]), nFormat);
						cDC.SelectObject(pOldFont);
						break;
					}
					if (nColumn == FindColumnIndex(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER)))
					{
						for (sizeSymbol.cx = sizeSymbol.cy = 0, nColor[1] = cDC.GetNearestColor(VGA_COLOR_WHITE), cTextFont.DeleteObject(); (pOldFont = (GetColumnFont(nItem, nColumn, &cTextFont)) ? cDC.SelectObject(&cTextFont) : cDC.SelectObject(&m_wndContentCtrl.m_cFont)); )
						{
							sizeSymbol.cx = sizeSymbol.cy = cDC.GetTextExtent(SPACE).cy;
							m_sizeAlertSymbols = sizeSymbol;
							cDC.SelectObject(pOldFont);
							cTextFont.DeleteObject();
							break;
						}
						for (nSymbol = (!_tcsstr(pszText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION))) ? ((!_tcsstr(pszText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING))) ? ((_tcsstr(pszText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR))) ? TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_ERROR : -1) : TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_WARNING) : TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION; nSymbol != (UINT)-1; )
						{
							if (bState) m_pAlertSymbols[nSymbol]->TransparentBlt(cDC.GetSafeHdc(), m_wndContentCtrl.m_wTextIndent[0] + CalcTelecommandSymbolPosition(nItem, nColumn, pszText).left - rText[1].left, m_wndContentCtrl.m_wTextSpacing[0], sizeSymbol.cx, sizeSymbol.cy, nColor[1]);
							break;
						}
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

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem)
{
	CDC  cDC[2];
	INT  nIndex;
	INT  nWidth;
	INT  nHeight;
	BOOL  bBackground;
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	BLENDFUNCTION  sBlend;

	if (cDC[0].CreateCompatibleDC(pDC))
	{
		if (cDC[1].CreateCompatibleDC(pDC))
		{
			if (cBitmap[0].CreateCompatibleBitmap(pDC, (nWidth = rItem.right - rItem.left), (nHeight = rItem.bottom - rItem.top)))
			{
				if (cBitmap[1].CreateCompatibleBitmap(pDC, nWidth, nHeight))
				{
					if ((pOldBitmap[0] = cDC[0].SelectObject(&cBitmap[0])))
					{
						if ((pOldBitmap[1] = cDC[1].SelectObject(&cBitmap[1])))
						{
							for (sBlend.BlendFlags = 0, sBlend.BlendOp = AC_SRC_OVER, sBlend.AlphaFormat = 0, sBlend.SourceConstantAlpha = TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COLUMNTRANSPARENCY; nWidth > 0 && nHeight > 0; )
							{
								cDC[0].FillSolidRect(0, 0, ((nIndex = max(FindColumnIndex(LookupColumnName(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER)), FindColumnIndex(LookupColumnName(TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME)))) >= 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex) - m_wndContentCtrl.m_nScrollPos[0]) : 0, nHeight, m_nLayoutBackgroundColor[0]);
								cDC[0].FillSolidRect((m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(max(nIndex, 0)) - m_wndContentCtrl.m_nScrollPos[0]) : 0, 0, (m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? max(nWidth - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(max(nIndex, 0)) + m_wndContentCtrl.m_nScrollPos[0], 0) : 0, nHeight, m_nLayoutBackgroundColor[1]);
								cDC[0].FillSolidRect((m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(m_wndHeaderCtrl.m_nColumnsWidth.GetUpperBound()) - m_wndContentCtrl.m_nScrollPos[0]) : 0, 0, (m_wndHeaderCtrl.m_nColumnsWidth.GetSize() > 0) ? max(nWidth - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(m_wndHeaderCtrl.m_nColumnsWidth.GetUpperBound()) + m_wndContentCtrl.m_nScrollPos[0], 0) : nWidth, nHeight, m_nLayoutBackgroundColor[2]);
								for (cDC[1].FillSolidRect(0, 0, nWidth, nHeight, VGA_COLOR_WHITE), cDC[1].AlphaBlend(0, 0, nWidth, nHeight, &cDC[0], 0, 0, nWidth, nHeight, sBlend), sBlend.SourceConstantAlpha = 0xFF - 2 * sBlend.SourceConstantAlpha; nItem == GetCurSample() && nColumn >= 0; )
								{
									for (cDC[0].SetTextColor(pDC->GetTextColor()); (bBackground = CTextView::DrawBackground(&cDC[0], nItem, nColumn, CRect(0, 0, nWidth, nHeight))); )
									{
										cDC[1].AlphaBlend(0, 0, nWidth, nHeight, &cDC[0], 0, 0, nWidth, nHeight, sBlend);
										break;
									}
									for (pDC->SetTextColor(cDC[0].GetTextColor()); !bBackground; )
									{
										cDC[1].BitBlt(0, 0, nWidth, nHeight, &cDC[0], 0, 0, SRCCOPY);
										break;
									}
									break;
								}
								pDC->BitBlt(rItem.left, rItem.top, nWidth, nHeight, &cDC[1], 0, 0, SRCCOPY);
								break;
							}
							cDC[0].SelectObject(pOldBitmap[0]);
							cDC[1].SelectObject(pOldBitmap[1]);
							cBitmap[0].DeleteObject();
							cBitmap[1].DeleteObject();
							cDC[1].DeleteDC();
							cDC[0].DeleteDC();
							return TRUE;
						}
						cDC[0].SelectObject(pOldBitmap[0]);
					}
					cBitmap[1].DeleteObject();
				}
				cBitmap[0].DeleteObject();
			}
			cDC[1].DeleteDC();
		}
		cDC[0].DeleteDC();
	}
	return FALSE;
}

CTCDiagnosticsOversamplingDumpRawDataView *CTCDiagnosticsOversamplingDumpRawDataTextView::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpRawDataView *)CTextView::GetParent());
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpRawDataTextView::GetParentDisplay() CONST
{
	CTCDiagnosticsOversamplingDumpRawDataView  *pView;

	return(((pView = GetParent())) ? pView->GetParentDisplay() : (CTCDiagnosticsOversamplingDumpWnd *)NULL);
}

CString CTCDiagnosticsOversamplingDumpRawDataTextView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER) return STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER);
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME) return STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME);
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS) return STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS);
	return EMPTYSTRING;
}
UINT CTCDiagnosticsOversamplingDumpRawDataTextView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER))) return TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER;
	if (!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME))) return TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS))) return TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS;
	return 0;
}

INT CTCDiagnosticsOversamplingDumpRawDataTextView::LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)nColumns.GetSize(), szColumns.RemoveAll(); nIndex < nCount; nIndex++)
	{
		szColumns.Add(LookupColumnName(nColumns.GetAt(nIndex)));
		continue;
	}
	return((INT)szColumns.GetSize());
}

COLORREF CTCDiagnosticsOversamplingDumpRawDataTextView::LookupColumnColor(UINT nColumn) CONST
{
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER) return GetDatabase()->GetTCDiagnosticsOversamplingDumpRawDataNumberColumnColor();
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME) return GetDatabase()->GetTCDiagnosticsOversamplingDumpRawDataTimeColumnColor();
	if (nColumn == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS) return GetDatabase()->GetTCDiagnosticsOversamplingDumpRawDataContentsColumnColor();
	return GetSysColor(COLOR_WINDOWTEXT);
}

CString CTCDiagnosticsOversamplingDumpRawDataTextView::TranslateRawDataBlock(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CTCDiagnosticsOversamplingDumpSamples &pSamples, CTextViewAttribute *pAttribute) CONST
{
	INT  nByte;
	INT  nBytes;
	INT  nBlock;
	INT  nBlocks;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szText;
	CString  szBlocks;
	CString  szColumn;
	CString  szWarning;
	CString  szInformation;
	CByteArray  nRawData;
	CStringTools  cStringTools;
	CTimeTagArray  tParameterTimes;
	COversamplingParameter  *pOversamplingParameter;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;

	for (nParameter = 0, nParameters = (INT)cLayout.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOversamplingParameter = cLayout.GetAt(nParameter)) != (COversamplingParameter *)NULL)
		{
			tParameterTimes.SetAtGrow(0, (tParameterTimes.GetSize() > 0) ? max(pOversamplingParameter->GetLastUpdateTime().GetTime(), tParameterTimes.GetAt(0).GetTime()) : pOversamplingParameter->GetLastUpdateTime().GetTime());
			continue;
		}
	}
	for (nBlock = 0, nBlocks = (INT)tParameterTimes.GetSize(), pSamples.RemoveAll(); nBlock < nBlocks; nBlock++)
	{
		for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(), szInformation.Empty(), szWarning.Empty(); nColumn < nColumns; nColumn++)
		{
			for (pAttribute->SetColumnColor(nColumn, LookupColumnColor(LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))))), szText.Empty(); szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER); )
			{
				szText = cStringTools.ConvertIntToPaddedString((INT)(m_wndContentCtrl.m_szContentText.GetSize() + nBlock + 1), max(max(cStringTools.ConvertIntToString((INT)(m_wndContentCtrl.m_szContentText.GetSize() + nBlocks)).GetLength(), cStringTools.ConvertIntToString(m_nSampleLimit).GetLength()), 3));
				if ((pOversamplingSample = (!nBlock) ? m_pSamples.GetAt((INT)(m_pSamples.GetSize() - 1)) : (CTCDiagnosticsOversamplingDumpSample *)NULL) != (CTCDiagnosticsOversamplingDumpSample *)NULL)
				{
					if (cLayout.GetTimeTag().GetTime() - pOversamplingSample->GetTimeTag().GetTime() >= (2 * 1000000 * (TIMETAG)cLayout.GetSamplingRate()) && cLayout.GetSamplingRate() > 0.0)
					{
						szText += CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING);
						szWarning = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_SAMPLINGRATEMISMATCH);
						break;
					}
					if (cLayout.GetTimeTag() < pOversamplingSample->GetTimeTag())
					{
						szText += CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION);
						szInformation = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_BACKWARDSSAMPLINGTIP);
					}
					if (cLayout.GetSamplingRate() == 0.0)
					{
						szText += CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING);
						szWarning = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_NOSAMPLINGRATECHECKS);
						break;
					}
				}
				szText += (cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION)) : EMPTYSTRING;
				break;
			}
			for (; szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME); )
			{
				szText = tParameterTimes.GetAt(nBlock).FormatGmt();
				break;
			}
			for (nByte = TMPACKET_HEADER_SIZE + GetDatabase()->GetTMPacketDataFieldHeaderSize(), nBytes = (szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)) ? cLayout.GetData(nRawData) : 0; nByte < nBytes; nByte++)
			{
				szText += (nByte % 2 == 0 && nByte > TMPACKET_HEADER_SIZE + GetDatabase()->GetTMPacketDataFieldHeaderSize()) ? (CString(SPACE) + cStringTools.ConvertUIntToPaddedString(nRawData.GetAt(nByte), 2, 16)) : cStringTools.ConvertUIntToPaddedString(nRawData.GetAt(nByte), 2, 16);
				continue;
			}
			szBlocks += (nColumn > 0) ? (GetColumnDelimiter() + szText) : szText;
		}
		if ((pOversamplingSample = new CTCDiagnosticsOversamplingDumpSample))
		{
			for (pOversamplingSample->SetBlock(nBlock), pOversamplingSample->COversamplingParameters::Copy(&cLayout); cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL; )
			{
				pOversamplingSample->SetAlertMessage(TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_MESSAGE_NOAUTOSAMPLINGDETECTION));
				break;
			}
			if (!szInformation.IsEmpty()) pOversamplingSample->SetAlertMessage(TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION, szInformation);
			if (!szWarning.IsEmpty()) pOversamplingSample->SetAlertMessage(TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_WARNING, szWarning);
			pSamples.Add(pOversamplingSample);
		}
		if (nBlock < nBlocks - 1)
		{
			szBlocks += EOL;
			continue;
		}
	}
	return((nBlocks == pSamples.GetSize()) ? szBlocks : EMPTYSTRING);
}
CString CTCDiagnosticsOversamplingDumpRawDataTextView::TranslateParameterBlock(INT nIndex, INT nCount, CONST CTCDiagnosticsOversamplingDumpSample *pSample, CTextViewAttribute *pAttribute) CONST
{
	INT  nByte;
	INT  nBytes;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	UINT  nAlertType;
	CString  szText;
	CString  szBlock;
	CString  szColumn;
	CString  szMessage;
	CByteArray  nRawData;
	CStringTools  cStringTools;
	COversamplingParameter  *pOversamplingParameter;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(), nParameter = 0; nColumn < nColumns; nColumn++)
	{
		for (pAttribute->SetColumnColor(nColumn, LookupColumnColor(LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))))), szText.Empty(); szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER); )
		{
			for (szText = cStringTools.ConvertIntToPaddedString(nIndex + 1, max(max(cStringTools.ConvertIntToString(nCount).GetLength(), cStringTools.ConvertIntToString(m_nSampleLimit).GetLength()), 3)); (nAlertType = pSample->GetAlertMessage(szMessage)) != TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_NONE; )
			{
				szText += (nAlertType == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION)) : EMPTYSTRING;
				szText += (nAlertType == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_WARNING) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING)) : EMPTYSTRING;
				szText += (nAlertType == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_ERROR) ? (CString(GetSymbolDelimiter()) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR)) : EMPTYSTRING;
				break;
			}
			break;
		}
		for (; szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME); )
		{
			szText = ((pOversamplingParameter = pSample->GetAt(nParameter))) ? CTimeTag(pOversamplingParameter->GetLastUpdateTime().GetTime() + (1000000 * (TIMETAG)pSample->GetSamplingRate()*pSample->GetBlock())).FormatGmt() : EMPTYSTRING;
			break;
		}
		for (nByte = TMPACKET_HEADER_SIZE + GetDatabase()->GetTMPacketDataFieldHeaderSize(), nBytes = (szColumn == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)) ? pSample->GetData(nRawData) : 0; nByte < nBytes; nByte++)
		{
			szText += (nByte % 2 == 0 && nByte > TMPACKET_HEADER_SIZE + GetDatabase()->GetTMPacketDataFieldHeaderSize()) ? (CString(SPACE) + cStringTools.ConvertUIntToPaddedString(nRawData.GetAt(nByte), 2, 16)) : cStringTools.ConvertUIntToPaddedString(nRawData.GetAt(nByte), 2, 16);
			continue;
		}
		szBlock += (nColumn > 0) ? (GetColumnDelimiter() + szText) : szText;
	}
	return szBlock;
}

INT CTCDiagnosticsOversamplingDumpRawDataTextView::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (!m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn).Compare(pszColumn)) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

INT CTCDiagnosticsOversamplingDumpRawDataTextView::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	INT  nDxChar;
	CFont  cFont[2];
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if (!LookupColumnName(pszColumn))
		{
			for (GetTextFont(&cFont[1]), nWidth = 0; (pOldFont = pDC->SelectObject(&cFont[1])); )
			{
				nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
				pDC->SelectObject(pOldFont);
				break;
			}
			ReleaseDC(pDC);
			return nWidth;
		}
		for (GetTitleFont(&cFont[0]), GetTextFont(&cFont[1]), nWidth = 0; (pOldFont = pDC->SelectObject(&cFont[0])); )
		{
			nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
			pDC->SelectObject(pOldFont);
			break;
		}
		if ((pOldFont = pDC->SelectObject(&cFont[1])))
		{
			if ((nDxChar = (pDC->GetTextMetrics(&tmFont) > 0) ? (4 * tmFont.tmAveCharWidth / 3) : 0) > 0)
			{
				nWidth = (LookupColumnName(pszColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCDiagnosticsOversamplingDumpRawDataNumberCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (LookupColumnName(pszColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCDiagnosticsOversamplingDumpRawDataTimeCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (LookupColumnName(pszColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTCDiagnosticsOversamplingDumpRawDataContentsCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}

INT CTCDiagnosticsOversamplingDumpRawDataTextView::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)nColumns.GetSize(), nWidths.RemoveAll(); nIndex < nCount; nIndex++)
	{
		nWidths.Add((nIndex > 0) ? (nWidths.GetAt(nIndex - 1) + CalcColumnWidth(LookupColumnName(nColumns.GetAt(nIndex)))) : CalcColumnWidth(LookupColumnName(nColumns.GetAt(nIndex))));
		continue;
	}
	return((nCount == nWidths.GetSize()) ? (INT)nWidths.GetSize() : 0);
}

CRect CTCDiagnosticsOversamplingDumpRawDataTextView::CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST
{
	INT  nPos;
	CRect  rText;
	CRect  rSymbol;
	CFont  *pOldFont;
	CString  szText;
	CClientDC  cDC(NULL);

	for (szText = ((nPos = (szText = pszText).Find(GetSymbolDelimiter())) >= 0) ? szText.Left(nPos) : szText, rText = m_wndContentCtrl.CalcTextRect(nRow, nColumn), rSymbol.SetRectEmpty(); (pOldFont = (nColumn == FindColumnIndex(STRING(IDS_TCMANUALSTACK_TITLEITEM_NUMBER)) && !rText.IsRectEmpty()) ? cDC.SelectObject((CFont *)&m_wndContentCtrl.m_cFont) : (CFont *)NULL); )
	{
		rSymbol.SetRect(rText.left + cDC.GetTextExtent(szText + SPACE).cx, rText.top, rText.left + cDC.GetTextExtent(szText + SPACE).cx + m_sizeAlertSymbols.cx, rText.top + m_sizeAlertSymbols.cy);
		rSymbol.SetRect(min(max(rText.left, rSymbol.left), rText.right), rSymbol.top, max(min(rText.right, rSymbol.right), rText.left), rSymbol.bottom);
		rSymbol.InflateRect(0, 0, 1, 1);
		cDC.SelectObject(pOldFont);
		break;
	}
	return rSymbol;
}

UINT CTCDiagnosticsOversamplingDumpRawDataTextView::FindParameterSample(INT nRow, INT nColumn, CTCDiagnosticsOversamplingDumpSample *pSample) CONST
{
	CString  szColumn;
	CTCDiagnosticsOversamplingDumpSample  *pOversamplingSample;

	return((nRow < m_pSamples.GetSize() && nColumn < m_wndHeaderCtrl.m_szColumnsText.GetSize()) ? ((LookupColumnName((szColumn = m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn))) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER || LookupColumnName(szColumn) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS) ? (((pOversamplingSample = m_pSamples.GetAt(nRow)) && pSample->Copy(pOversamplingSample)) ? LookupColumnName(szColumn) : 0) : 0) : 0);
}

TCHAR CTCDiagnosticsOversamplingDumpRawDataTextView::GetSymbolDelimiter()
{
	return SPACE[0];
}

CString CTCDiagnosticsOversamplingDumpRawDataTextView::ConstructToolTipTitle(CONST CTCDiagnosticsOversamplingDumpSample *pSample, UINT nTip) CONST
{
	CString  szTitle;
	CString  szMessage;

	switch (nTip)
	{
	case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER:
	{ szTitle = (pSample->GetAlertMessage(szMessage) == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION) : EMPTYSTRING;
	szTitle = (pSample->GetAlertMessage(szMessage) == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_WARNING) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING) : szTitle;
	szTitle = (pSample->GetAlertMessage(szMessage) == TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_ERROR) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR) : szTitle;
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS:
	{ szTitle = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_RAWDATATITLE);
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME: break;
	}
	return szTitle;
}

CString CTCDiagnosticsOversamplingDumpRawDataTextView::ConstructToolTipText(CONST CTCDiagnosticsOversamplingDumpSample *pSample, UINT nTip) CONST
{
	INT  nItem;
	INT  nItems;
	UINT  nStatus;
	CString  szText;
	CString  szMessage;
	CString  szParameter;
	ULONGLONG  nValue;
	CStringTools  cStringTools;
	CDatabaseTMParameter  *pParameter;
	COversamplingParameter  *pOversamplingParameter;

	switch (nTip)
	{
	case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER:
	{ for (szText.Empty(); pSample->GetAlertMessage(szMessage) != TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_NONE; )
	{
		szText = szMessage;
		break;
	}
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS:
	{ for (nItem = 0, nItems = (INT)pSample->GetSize(); nItem < nItems; nItem++)
	{
		if ((pParameter = ((pOversamplingParameter = pSample->GetAt(nItem)) && pOversamplingParameter->GetRawValue(pSample->GetBlock(), nValue, nStatus)) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOversamplingParameter->GetTag())) : (CDatabaseTMParameter *)NULL))
		{
			szParameter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_TOOLTIP_RAWDATAPARAMETERFORMAT), (LPCTSTR)pOversamplingParameter->GetTag(), (LPCTSTR)cStringTools.ConvertLongUIntToPaddedString(nValue, 2 * ((pParameter->GetWidth() - 1) / 8 + 1), 16), pParameter->GetWidth());
			szText += (!szText.IsEmpty()) ? (EOL + szParameter) : szParameter;
		}
	}
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME: break;
	}
	return szText;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::LoadTelecommandSymbols()
{
	INT  nSymbol;
	INT  nSymbols;
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	for (nSymbol = 0, nSymbols = TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), (nSymbol == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_INFORMATION) ? MAKEINTRESOURCE(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPINFORMATION) : ((nSymbol == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_WARNING) ? MAKEINTRESOURCE(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPWARNING) : MAKEINTRESOURCE(IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPERROR)), STRING(IDS_RESOURCETYPE_PICTURE))))
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
								if ((m_pAlertSymbols[nSymbol] = new CImage) != (CImage *)NULL)
								{
									if (SUCCEEDED(m_pAlertSymbols[nSymbol]->Load(pIStream)))
									{
										pIStream->Release();
										continue;
									}
									delete m_pAlertSymbols[nSymbol];
									m_pAlertSymbols[nSymbol] = (CImage *)NULL;
								}
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		while (nSymbol > 0)
		{
			delete m_pAlertSymbols[--nSymbol];
			m_pAlertSymbols[nSymbol] = (CImage *)NULL;
		}
		break;
	}
	return((nSymbol == nSymbols) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpRawDataTextView::FreeTelecommandSymbols()
{
	INT  nSymbol;
	INT  nSymbols;

	for (nSymbol = 0, nSymbols = TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOLS; nSymbol < nSymbols; nSymbol++)
	{
		if (m_pAlertSymbols[nSymbol] != (CImage *)NULL)
		{
			m_pAlertSymbols[nSymbol]->Destroy();
			delete m_pAlertSymbols[nSymbol];
		}
	}
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CTCDiagnosticsOversamplingDumpRawDataTextView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CTextViewLock  cLock(this);

	SetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	SetCurSample((nCount != GetSampleCount()) ? (GetSampleCount() - 1) : nIndex);
	ScrollTo(GetCurSample());
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CTextViewLock  cLock(this);

	nIndex = GetCurSample();
	nCount = GetSampleCount();
	GetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpRawDataTextView::PostNcDestroy()
{
	m_tSampleTime = 0;
	m_pSamples.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::Lock()
{
	CTCDiagnosticsOversamplingDumpWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (pParentWnd->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::Unlock()
{
	CTCDiagnosticsOversamplingDumpWnd  *pParentWnd;

	return(((pParentWnd = GetParentDisplay())) ? (CTextView::Unlock() && pParentWnd->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpRawDataTextView, CTextView)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpRawDataTextView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRawDataTextView message handlers

int CTCDiagnosticsOversamplingDumpRawDataTextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(this);

	return((CTextView::OnCreate(lpCreateStruct) != -1 && LoadTelecommandSymbols() && LoadToolTipCursor()) ? 0 : -1);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nRow;
	INT  nColumn;
	UINT  nToolTip;
	LONG  lDataFlag;
	POINT  ptCursor;
	CRect  rContent;
	CString  szText;
	CTCDiagnosticsOversamplingDumpSample  cSample;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if ((lDataFlag = GetParentDisplay()->IsRetrievingData()) && HIWORD(lDataFlag))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		if ((nToolTip = (IsToolTipModeEnabled() && FindTextFromPoint(ptCursor, nRow, nColumn, FALSE) && GetText(nRow, nColumn, szText)) ? FindParameterSample(nRow, nColumn, &cSample) : 0) == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER)
		{
			if (_tcsstr(szText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION)) || _tcsstr(szText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING)) || _tcsstr(szText, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR)))
			{
				if (CalcTelecommandSymbolPosition(nRow, nColumn, szText).PtInRect(ptCursor))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
		}
		if (nToolTip == TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)
		{
			SetCursor(GetToolTipCursor());
			return TRUE;
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataTextView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nColumn;
	UINT  nToolTip;
	CFont  cFont[2];
	CPoint  ptToolTip;
	LOGFONT  lfFont[2];
	CString  szToolTip[2];
	CTCDiagnosticsOversamplingDumpSample  cSample;
	CTextViewLock  cLock(this);

	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (!GetParentDisplay()->IsRetrievingData() || !HIWORD(GetParentDisplay()->IsRetrievingData()))
		{
			if (GetCursor() == GetToolTipCursor() && FindTextFromPoint((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))), nRow, nColumn, FALSE))
			{
				switch ((nToolTip = FindParameterSample(nRow, nColumn, &cSample)))
				{
				case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER:
				case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS:
				{ for (szToolTip[0] = ConstructToolTipTitle(&cSample, nToolTip), szToolTip[1] = ConstructToolTipText(&cSample, nToolTip), GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
				{
					m_wndToolTip.SetTitleFont(&cFont[0]);
					m_wndToolTip.SetTextFont(&cFont[1]);
					break;
				}
				m_wndToolTip.Create(&m_wndContentCtrl, ptToolTip, szToolTip[0], szToolTip[1]);
				break;
				}
				case TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME: break;
				}
			}
		}
		return FALSE;
	}
	if (message == WM_RBUTTONUP)
	{
		m_wndToolTip.Destroy();
		return FALSE;
	}
	return FALSE;
}

void CTCDiagnosticsOversamplingDumpRawDataTextView::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	FreeTelecommandSymbols();
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRawDataView view

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpRawDataView, CView)

CTCDiagnosticsOversamplingDumpRawDataView::CTCDiagnosticsOversamplingDumpRawDataView() : CView()
{
	m_sizeTrackLayout.cx = 0;
	m_sizeTrackLayout.cy = 0;
	m_pwndList = new CTCDiagnosticsOversamplingDumpRawDataTextView;
	m_pParentWnd = (CWnd *)NULL;
}

CTCDiagnosticsOversamplingDumpRawDataView::~CTCDiagnosticsOversamplingDumpRawDataView()
{
	delete m_pwndList;
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetLayout(LPCTSTR pszLayout)
{
	return m_pwndList->SetLayout(pszLayout);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout)
{
	return m_pwndList->SetLayout(cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_pwndList->SetLayout(cLayout, nColumns, nWidths);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetLayout(CString &szLayout) CONST
{
	return m_pwndList->GetLayout(szLayout);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	return m_pwndList->GetLayout(cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_pwndList->GetLayout(cLayout, nColumns, nWidths);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetTitleFont(CFont *pFont)
{
	return m_pwndList->SetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetTitleFont(CONST LOGFONT *plfFont)
{
	return m_pwndList->SetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetTitleFont(CFont *pFont) CONST
{
	return m_pwndList->GetTitleFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetTitleFont(LOGFONT *plfFont) CONST
{
	return m_pwndList->GetTitleFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetItemsFont(CFont *pFont)
{
	return m_pwndList->SetItemsFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetItemsFont(CONST LOGFONT *plfFont)
{
	return m_pwndList->SetItemsFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetItemsFont(CFont *pFont) CONST
{
	return m_pwndList->GetItemsFont(pFont);
}
BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetItemsFont(LOGFONT *plfFont) CONST
{
	return m_pwndList->GetItemsFont(plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor)
{
	return m_pwndList->SetBackgroundColors(nNumbersColor, nValuesColor);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	return m_pwndList->GetBackgroundColors(nNumbersColor, nValuesColor);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetSampleLimit(UINT nLimit)
{
	return m_pwndList->SetSampleLimit(nLimit);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetSampleLimit(UINT &nLimit) CONST
{
	return m_pwndList->GetSampleLimit(nLimit);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::EnableInvalidDataMode(BOOL bEnable)
{
	return m_pwndList->EnableInvalidDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::IsInvalidDataModeEnabled() CONST
{
	return m_pwndList->IsInvalidDataModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::EnableBadDataMode(BOOL bEnable)
{
	return m_pwndList->EnableBadDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::IsBadDataModeEnabled() CONST
{
	return m_pwndList->IsBadDataModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::EnableToolTipMode(BOOL bEnable)
{
	return m_pwndList->EnableToolTipMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::IsToolTipModeEnabled() CONST
{
	return m_pwndList->IsToolTipModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_pwndList->Initialize(pTMEnvironment);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::Update(CTMEnvironment *pTMEnvironment)
{
	return m_pwndList->Update(pTMEnvironment);
}

VOID CTCDiagnosticsOversamplingDumpRawDataView::Reset(CTMEnvironment *pTMEnvironment)
{
	return m_pwndList->Reset(pTMEnvironment);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetCurSample(INT nIndex)
{
	return m_pwndList->SetCurSample(nIndex);
}

INT CTCDiagnosticsOversamplingDumpRawDataView::GetCurSample() CONST
{
	return m_pwndList->GetCurSample();
}

INT CTCDiagnosticsOversamplingDumpRawDataView::GetSampleCount() CONST
{
	return m_pwndList->GetSampleCount();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	return m_pwndList->GetPrintProperties(pJobInfo, szColumns, szContents, pAttributes, pTitleFont, pItemsFont, pSymbols, nSymbolIDs);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	return m_pwndList->SetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	return m_pwndList->GetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo);
}

VOID CTCDiagnosticsOversamplingDumpRawDataView::SetTrackSize(CONST SIZE &size)
{
	CTextViewLock  cLock(m_pwndList);

	m_sizeTrackLayout = size;
}

CSize CTCDiagnosticsOversamplingDumpRawDataView::GetTrackSize() CONST
{
	CTextViewLock  cLock(m_pwndList);

	return m_sizeTrackLayout;
}

CTCDiagnosticsOversamplingDumpView *CTCDiagnosticsOversamplingDumpRawDataView::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpView *)m_pParentWnd);
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpRawDataView::GetParentDisplay() CONST
{
	return(GetParent()->GetParent());
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::Lock()
{
	return m_pwndList->Lock();
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::Unlock()
{
	return m_pwndList->Unlock();
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpRawDataView, CView)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpRawDataView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRawDataView drawing

void CTCDiagnosticsOversamplingDumpRawDataView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRawDataView message handlers

int CTCDiagnosticsOversamplingDumpRawDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CView::OnCreate(lpCreateStruct) != -1 && m_pwndList->Create(this, ((m_pParentWnd = CView::GetParent())) ? CRect(0, 0, lpCreateStruct->cx, lpCreateStruct->cy) : CRect(0, 0, 0, 0), TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)) ? 0 : -1);
}

void CTCDiagnosticsOversamplingDumpRawDataView::OnSize(UINT nType, int cx, int cy)
{
	m_pwndList->MoveWindow(0, 0, cx, cy);
	CView::OnSize(nType, cx, cy);
}

BOOL CTCDiagnosticsOversamplingDumpRawDataView::OnEraseBkgnd(CDC *pDC)
{
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpRawDataView::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (IsChild(pOldWnd)) GetParent()->SetFocus();
		else  m_pwndList->SetFocus();
		return;
	}
	CView::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpView

IMPLEMENT_DYNCREATE(CTCDiagnosticsOversamplingDumpView, CSplitterWndEx)

CTCDiagnosticsOversamplingDumpView::CTCDiagnosticsOversamplingDumpView() : CSplitterWndEx()
{
	CFontTools  cFontTools[6] = { &m_lfLayoutFont[0][0],&m_lfLayoutFont[0][1],&m_lfLayoutFont[0][2],&m_lfLayoutFont[1][0],&m_lfLayoutFont[1][1],&m_lfLayoutFont[1][2] };

	m_nSampleLimit = 0;
	m_bTracking = TRUE;
	m_bToolTips = TRUE;
	m_sizeLayoutPane[0].cx = 0;
	m_sizeLayoutPane[0].cy = 0;
	m_sizeLayoutPane[1].cx = 0;
	m_sizeLayoutPane[1].cy = 0;
	m_lfLayoutFont[0][0].lfWeight = FW_NORMAL;
	m_lfLayoutFont[0][1].lfWeight = FW_NORMAL;
	m_lfLayoutFont[0][2].lfWeight = FW_BOLD;
	m_lfLayoutFont[1][0].lfWeight = FW_NORMAL;
	m_lfLayoutFont[1][1].lfWeight = FW_NORMAL;
	m_nLayoutBackgroundColor[0] = VGA_COLOR_LTYELLOW;
	m_nLayoutBackgroundColor[1] = GetSysColor(COLOR_WINDOW);
	m_pParametersView = (CTCDiagnosticsOversamplingDumpParametersView *)NULL;
	m_pRawDataView = (CTCDiagnosticsOversamplingDumpRawDataView *)NULL;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CTCDiagnosticsOversamplingDumpView::Create(CWnd *pParentWnd)
{
	CRect  rPanes;
	CSize  sizePanes[2];
	CCreateContext  cContext;

	if (CreateStatic((m_pParentWnd = pParentWnd), 2, 1))
	{
		for (GetParent()->GetClientRect(rPanes), cContext.m_pCurrentDoc = new CTCDiagnosticsOversamplingDumpDocument; CreateView(0, 0, RUNTIME_CLASS(CTCDiagnosticsOversamplingDumpParametersView), (sizePanes[0] = (!m_sizeLayoutPane[0].cy) ? CSize(rPanes.Width(), (2 * rPanes.Height()) / 3) : m_sizeLayoutPane[0]), &cContext) && CreateView(1, 0, RUNTIME_CLASS(CTCDiagnosticsOversamplingDumpRawDataView), (sizePanes[1] = (!m_sizeLayoutPane[1].cy) ? CSize(rPanes.Width(), rPanes.Height() / 3) : m_sizeLayoutPane[1]), &cContext); )
		{
			for (m_pParametersView = (CTCDiagnosticsOversamplingDumpParametersView *)GetPane(0, 0), m_pRawDataView = (CTCDiagnosticsOversamplingDumpRawDataView *)GetPane(1, 0); (SetLayout(m_cLayout, m_nLayoutColumns[0], m_nLayoutColumnWidths[0], sizePanes[0], m_nLayoutColumns[1], m_nLayoutColumnWidths[1], sizePanes[1]) || SetLayout(m_cLayout)) && SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_lfLayoutFont[0][0]) && SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_lfLayoutFont[0][1]) && SetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &m_lfLayoutFont[0][2]) && SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_lfLayoutFont[1][0]) && SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &m_lfLayoutFont[1][1]) && SetGridBackgroundColors(m_nLayoutBackgroundColor[0], m_nLayoutBackgroundColor[1]) && SetSampleLimit(m_nSampleLimit); )
			{
				MoveWindow(rPanes);
				return TRUE;
			}
			break;
		}
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpView::SetLayout(LPCTSTR pszLayout)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->SetLayout(pszLayout) && GetRawDataView()->SetLayout(pszLayout)) return TRUE;
		return FALSE;
	}
	m_cLayout.SetName(pszLayout);
	return TRUE;
}
BOOL CTCDiagnosticsOversamplingDumpView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout)
{
	INT  nPaneHeight[2][2];

	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->SetLayout(cLayout) && GetRawDataView()->SetLayout(cLayout))
		{
			for (GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]), GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]), m_bTracking = (cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE) ? TRUE : FALSE; ((cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE) && nPaneHeight[1][0] == 0) || ((cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE) != TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE && nPaneHeight[1][0] > 0); )
			{
				SetRowInfo(0, (cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE) ? max((2 * nPaneHeight[0][0]) / 3, 0) : max(nPaneHeight[0][0] + nPaneHeight[1][0], 0), max(nPaneHeight[0][1], 0));
				SetRowInfo(1, (cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE) ? max(nPaneHeight[0][0] / 3, 0) : 0, max(nPaneHeight[1][1], 0));
				RecalcLayout();
				break;
			}
			return TRUE;
		}
		return FALSE;
	}
	return m_cLayout.Copy(&cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpView::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nParametersPaneColumns, CONST CUIntArray &nParametersPaneWidths, CONST SIZE &sizeParametersPane, CONST CUIntArray &nRawDataPaneColumns, CONST CUIntArray &nRawDataPaneWidths, CONST SIZE &sizeRawDataPane)
{
	INT  nPaneHeight[2][2];

	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->SetLayout(cLayout, nParametersPaneColumns, nParametersPaneWidths) && GetRawDataView()->SetLayout(cLayout, nRawDataPaneColumns, nRawDataPaneWidths))
		{
			for (GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]), GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]); cLayout.GetAttributes() & TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE; )
			{
				SetRowInfo(0, max(sizeParametersPane.cy, 0), max(nPaneHeight[0][1], 0));
				SetRowInfo(1, max(sizeRawDataPane.cy, 0), max(nPaneHeight[1][1], 0));
				RecalcLayout();
				return TRUE;
			}
			SetRowInfo(0, max(sizeParametersPane.cy + sizeRawDataPane.cy, 0), max(nPaneHeight[0][1], 0));
			SetRowInfo(1, 0, max(nPaneHeight[1][1], 0));
			RecalcLayout();
			return TRUE;
		}
		return FALSE;
	}
	m_cLayout.Copy(&cLayout);
	m_nLayoutColumns[0].Copy(nParametersPaneColumns);
	m_nLayoutColumns[1].Copy(nRawDataPaneColumns);
	m_nLayoutColumnWidths[0].Copy(nParametersPaneWidths);
	m_nLayoutColumnWidths[1].Copy(nRawDataPaneWidths);
	m_sizeLayoutPane[0] = sizeParametersPane;
	m_sizeLayoutPane[1] = sizeRawDataPane;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::GetLayout(CString &szLayout) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->GetLayout(szLayout) && GetRawDataView()->GetLayout(szLayout)) return TRUE;
		return FALSE;
	}
	szLayout = m_cLayout.GetName();
	return TRUE;
}
BOOL CTCDiagnosticsOversamplingDumpView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->GetLayout(cLayout) && GetRawDataView()->GetLayout(cLayout)) return TRUE;
		return FALSE;
	}
	return cLayout.Copy(&m_cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpView::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nParametersPaneColumns, CUIntArray &nParametersPaneWidths, CSize &sizeParametersPane, CUIntArray &nRawDataPaneColumns, CUIntArray &nRawDataPaneWidths, CSize &sizeRawDataPane) CONST
{
	INT  nPaneHeight[2][2];

	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->GetLayout(cLayout, nParametersPaneColumns, nParametersPaneWidths) && GetRawDataView()->GetLayout(cLayout, nRawDataPaneColumns, nRawDataPaneWidths))
		{
			GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]);
			GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]);
			sizeParametersPane.cy = nPaneHeight[0][0];
			sizeRawDataPane.cy = nPaneHeight[1][0];
			return TRUE;
		}
		return FALSE;
	}
	nParametersPaneColumns.Copy(m_nLayoutColumns[0]);
	nRawDataPaneColumns.Copy(m_nLayoutColumns[1]);
	nParametersPaneWidths.Copy(m_nLayoutColumnWidths[0]);
	nRawDataPaneWidths.Copy(m_nLayoutColumnWidths[1]);
	sizeParametersPane = m_sizeLayoutPane[0];
	sizeRawDataPane = m_sizeLayoutPane[1];
	return cLayout.Copy(&m_cLayout);
}

BOOL CTCDiagnosticsOversamplingDumpView::SetListTitleFont(UINT nPane, CFont *pFont)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->SetTitleFont(pFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->SetTitleFont(pFont);
		return FALSE;
	}
	return(((nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS  &&  pFont->GetLogFont(&m_lfLayoutFont[0][0]) > 0) || (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA  &&  pFont->GetLogFont(&m_lfLayoutFont[1][0]) > 0)) ? TRUE : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpView::SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->SetTitleFont(plfFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->SetTitleFont(plfFont);
		return FALSE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(&m_lfLayoutFont[0][0], plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
	{
		CopyMemory(&m_lfLayoutFont[1][0], plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpView::GetListTitleFont(UINT nPane, CFont *pFont) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetTitleFont(pFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->GetTitleFont(pFont);
		return FALSE;
	}
	return(((nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS  &&  pFont->CreateFontIndirect(&m_lfLayoutFont[0][0])) || (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA  &&  pFont->CreateFontIndirect(&m_lfLayoutFont[1][0]))) ? TRUE : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpView::GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetTitleFont(plfFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->GetTitleFont(plfFont);
		return FALSE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(plfFont, &m_lfLayoutFont[0][0], sizeof(LOGFONT));
		return TRUE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
	{
		CopyMemory(plfFont, &m_lfLayoutFont[1][0], sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpView::SetListItemsFont(UINT nPane, CFont *pFont)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->SetItemsFont(pFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->SetItemsFont(pFont);
		return FALSE;
	}
	return(((nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS  &&  pFont->GetLogFont(&m_lfLayoutFont[0][1]) > 0) || (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA  &&  pFont->GetLogFont(&m_lfLayoutFont[1][1]) > 0)) ? TRUE : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpView::SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->SetItemsFont(plfFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->SetItemsFont(plfFont);
		return FALSE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(&m_lfLayoutFont[0][1], plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
	{
		CopyMemory(&m_lfLayoutFont[1][1], plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpView::GetListItemsFont(UINT nPane, CFont *pFont) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetItemsFont(pFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->GetItemsFont(pFont);
		return FALSE;
	}
	return(((nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS  &&  pFont->CreateFontIndirect(&m_lfLayoutFont[0][1])) || (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA  &&  pFont->CreateFontIndirect(&m_lfLayoutFont[1][1]))) ? TRUE : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpView::GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetItemsFont(plfFont);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->GetItemsFont(plfFont);
		return FALSE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(plfFont, &m_lfLayoutFont[0][1], sizeof(LOGFONT));
		return TRUE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA)
	{
		CopyMemory(plfFont, &m_lfLayoutFont[1][1], sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpView::SetListValuesFont(UINT nPane, CFont *pFont)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->SetValuesFont(pFont);
		return FALSE;
	}
	return((nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS  &&  pFont->GetLogFont(&m_lfLayoutFont[0][2]) > 0) ? TRUE : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpView::SetListValuesFont(UINT nPane, CONST LOGFONT *plfFont)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->SetValuesFont(plfFont);
		return FALSE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(&m_lfLayoutFont[0][2], plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpView::GetListValuesFont(UINT nPane, CFont *pFont) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetValuesFont(pFont);
		return FALSE;
	}
	return((nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS  &&  pFont->CreateFontIndirect(&m_lfLayoutFont[0][2])) ? TRUE : FALSE);
}
BOOL CTCDiagnosticsOversamplingDumpView::GetListValuesFont(UINT nPane, LOGFONT *plfFont) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetValuesFont(plfFont);
		return FALSE;
	}
	if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)
	{
		CopyMemory(plfFont, &m_lfLayoutFont[0][2], sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpView::SetGridBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->SetBackgroundColors(nNumbersColor, nValuesColor) && GetRawDataView()->SetBackgroundColors(nNumbersColor, nValuesColor)) return TRUE;
		return FALSE;
	}
	m_nLayoutBackgroundColor[0] = nNumbersColor;
	m_nLayoutBackgroundColor[1] = nValuesColor;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::GetGridBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->GetBackgroundColors(nNumbersColor, nValuesColor) && GetRawDataView()->GetBackgroundColors(nNumbersColor, nValuesColor)) return TRUE;
		return FALSE;
	}
	nNumbersColor = m_nLayoutBackgroundColor[0];
	nValuesColor = m_nLayoutBackgroundColor[1];
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::SetSampleLimit(UINT nLimit)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->SetSampleLimit(nLimit) && GetRawDataView()->SetSampleLimit(nLimit)) return TRUE;
		return FALSE;
	}
	m_nSampleLimit = nLimit;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::GetSampleLimit(UINT &nLimit) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->GetSampleLimit(nLimit) && GetRawDataView()->GetSampleLimit(nLimit)) return TRUE;
		return FALSE;
	}
	nLimit = m_nSampleLimit;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::EnableInvalidDataMode(BOOL bEnable)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->EnableInvalidDataMode(bEnable) && GetRawDataView()->EnableInvalidDataMode(bEnable)) return TRUE;
		return FALSE;
	}
	m_bInvalidData = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::IsInvalidDataModeEnabled() CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->IsInvalidDataModeEnabled() && GetRawDataView()->IsInvalidDataModeEnabled()) : m_bInvalidData);
}

BOOL CTCDiagnosticsOversamplingDumpView::EnableBadDataMode(BOOL bEnable)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->EnableBadDataMode(bEnable) && GetRawDataView()->EnableBadDataMode(bEnable)) return TRUE;
		return FALSE;
	}
	m_bBadData = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::IsBadDataModeEnabled() CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->IsBadDataModeEnabled() && GetRawDataView()->IsBadDataModeEnabled()) : m_bBadData);
}

BOOL CTCDiagnosticsOversamplingDumpView::EnableToolTipMode(BOOL bEnable)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (GetParametersView()->EnableToolTipMode(bEnable) && GetRawDataView()->EnableToolTipMode(bEnable)) return TRUE;
		return FALSE;
	}
	m_bToolTips = bEnable;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpView::IsToolTipModeEnabled() CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->IsToolTipModeEnabled() && GetRawDataView()->IsToolTipModeEnabled()) : m_bToolTips);
}

BOOL CTCDiagnosticsOversamplingDumpView::Initialize(CTMEnvironment *pTMEnvironment)
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->Initialize(pTMEnvironment) + GetRawDataView()->Initialize(pTMEnvironment) == 2 * TRUE) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpView::Update(CTMEnvironment *pTMEnvironment)
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->Update(pTMEnvironment) + GetRawDataView()->Update(pTMEnvironment) == 2 * TRUE) : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpView::Reset(CTMEnvironment *pTMEnvironment)
{
	if (IsWindow(GetSafeHwnd()))
	{
		GetParametersView()->Reset();
		GetRawDataView()->Reset();
	}
}

BOOL CTCDiagnosticsOversamplingDumpView::SetCurSample(UINT nPane, INT nIndex)
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->SetCurSample(nIndex);
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->SetCurSample(nIndex);
	}
	return FALSE;
}

INT CTCDiagnosticsOversamplingDumpView::GetCurSample(UINT nPane) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetCurSample();
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->GetCurSample();
	}
	return -1;
}

INT CTCDiagnosticsOversamplingDumpView::GetSampleCount(UINT nPane) CONST
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) return GetParametersView()->GetSampleCount();
		if (nPane == TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) return GetRawDataView()->GetSampleCount();
	}
	return 0;
}

BOOL CTCDiagnosticsOversamplingDumpView::GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szParametersColumns, CStringArray &szParametersContents, CTextViewAttributes &pParametersAttributes, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pParametersValuesFont, CStringArray &szRawDataColumns, CStringArray &szRawDataContents, CTextViewAttributes &pRawDataAttributes, LOGFONT *pRawDataTitleFont, LOGFONT *pRawDataItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->GetPrintProperties(pJobInfo, szParametersColumns, szParametersContents, pParametersAttributes, pParametersTitleFont, pParametersItemsFont, pParametersValuesFont, pSymbols, nSymbolIDs) && GetRawDataView()->GetPrintProperties(pJobInfo, szRawDataColumns, szRawDataContents, pRawDataAttributes, pRawDataTitleFont, pRawDataItemsFont, pSymbols, nSymbolIDs)) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpView::SetLayoutInfo(INT nParametersPaneIndex, INT nParametersPaneCount, CONST SCROLLINFO *pParametersPaneHorzScrollInfo, CONST SCROLLINFO *pParametersPaneVertScrollInfo, INT nRawDataPaneIndex, INT nRawDataPaneCount, CONST SCROLLINFO *pRawDataPaneHorzScrollInfo, CONST SCROLLINFO *pRawDataPaneVertScrollInfo)
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->SetLayoutInfo(nParametersPaneIndex, nParametersPaneCount, pParametersPaneHorzScrollInfo, pParametersPaneVertScrollInfo) && GetRawDataView()->SetLayoutInfo(nRawDataPaneIndex, nRawDataPaneCount, pRawDataPaneHorzScrollInfo, pRawDataPaneVertScrollInfo)) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpView::GetLayoutInfo(INT &nParametersPaneIndex, INT &nParametersPaneCount, SCROLLINFO *pParametersPaneHorzScrollInfo, SCROLLINFO *pParametersPaneVertScrollInfo, INT &nRawDataPaneIndex, INT &nRawDataPaneCount, SCROLLINFO *pRawDataPaneHorzScrollInfo, SCROLLINFO *pRawDataPaneVertScrollInfo) CONST
{
	return((IsWindow(GetSafeHwnd())) ? (GetParametersView()->GetLayoutInfo(nParametersPaneIndex, nParametersPaneCount, pParametersPaneHorzScrollInfo, pParametersPaneVertScrollInfo) && GetRawDataView()->GetLayoutInfo(nRawDataPaneIndex, nRawDataPaneCount, pRawDataPaneHorzScrollInfo, pRawDataPaneVertScrollInfo)) : FALSE);
}

void CTCDiagnosticsOversamplingDumpView::StartTracking(int ht)
{
	CSplitterWndEx::StartTracking(ht);
	m_rectLimit.top += GetParametersView()->GetTrackSize().cy;
	m_rectLimit.bottom -= GetRawDataView()->GetTrackSize().cy;
}

CTCDiagnosticsOversamplingDumpParametersView *CTCDiagnosticsOversamplingDumpView::GetParametersView() CONST
{
	return m_pParametersView;
}

CTCDiagnosticsOversamplingDumpRawDataView *CTCDiagnosticsOversamplingDumpView::GetRawDataView() CONST
{
	return m_pRawDataView;
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpView::GetParent() CONST
{
	return((CTCDiagnosticsOversamplingDumpWnd *)m_pParentWnd);
}

VOID CTCDiagnosticsOversamplingDumpView::RecalcLayout()
{
	CSplitterWndEx::RecalcLayout();
}
VOID CTCDiagnosticsOversamplingDumpView::RecalcLayout(BOOL bRecalc)
{
	CWnd  *pWnd;
	CRect  rWnd;
	CRect  rView;

	if (CThread::IsSameThread(this) && IsWindow(m_pParametersView->GetSafeHwnd()) && IsWindow(m_pRawDataView->GetSafeHwnd()))
	{
		for (pWnd = GetParent()->GetWindow(GW_CHILD), GetParent()->GetClientRect(rView); pWnd != (CWnd *)NULL; pWnd = pWnd->GetNextWindow())
		{
			if (pWnd->GetSafeHwnd() != GetSafeHwnd())
			{
				pWnd->GetWindowRect(rWnd);
				GetParent()->ScreenToClient(rWnd);
				rWnd.left = rView.left;
				rWnd.right = rView.right;
				rView.SubtractRect(rView, rWnd);
			}
		}
		MoveWindow(rView);
	}
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpView, CSplitterWndEx)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpView)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpView message handlers

void CTCDiagnosticsOversamplingDumpView::OnSize(UINT nType, int cx, int cy)
{
	INT  nPaneHeight[2][2];
	CString  szLayout;

	if (GetParent()->GetScope() == DISPLAY_SCOPE_LOCAL  &&  m_cLayout.GetName().IsEmpty())
	{
		GetRowInfo(0, nPaneHeight[0][0], nPaneHeight[0][1]);
		GetRowInfo(1, nPaneHeight[1][0], nPaneHeight[1][1]);
		SetRowInfo(0, (2 * cy) / 3, max(nPaneHeight[0][1], 0));
		SetRowInfo(1, cy / 3, max(nPaneHeight[1][1], 0));
		RecalcLayout();
	}
	CSplitterWndEx::OnSize(nType, cx, cy);
}

void CTCDiagnosticsOversamplingDumpView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking) return;
	CSplitterWndEx::OnMouseMove(nFlags, point);
}

void CTCDiagnosticsOversamplingDumpView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bTracking) return;
	CSplitterWndEx::OnLButtonDown(nFlags, point);
}

void CTCDiagnosticsOversamplingDumpView::OnSetFocus(CWnd *pOldWnd)
{
	if (pOldWnd == GetParent())
	{
		GetParametersView()->SetFocus();
		return;
	}
	if (pOldWnd == GetParametersView())
	{
		GetRawDataView()->SetFocus();
		return;
	}
	if (pOldWnd == GetRawDataView())
	{
		GetParent()->SetFocus();
		return;
	}
	CSplitterWndEx::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpWnd

IMPLEMENT_DYNAMIC(CTCDiagnosticsOversamplingDumpWnd, CDisplayWnd)

CTCDiagnosticsOversamplingDumpWnd::CTCDiagnosticsOversamplingDumpWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP);
	SetRetrieveMode();
	SetRetrieveSpeed();
	SetRetrieveInterval();
	SetRetrieveStartTime();
	SetRetrieveStopTime();
	SetUpdateInfo();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle || (!_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_GLOBALTCDIAGNOSTICSOVERSAMPLINGDUMP)) && !_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_TCDIAGNOSTICSOVERSAMPLINGDUMP)))) ? ((pDefaultInfo->nScope == DISPLAY_SCOPE_GLOBAL) ? STRING(IDS_DISPLAY_TITLE_GLOBALTCDIAGNOSTICSOVERSAMPLINGDUMP) : STRING(IDS_DISPLAY_TITLE_TCDIAGNOSTICSOVERSAMPLINGDUMP)) : pszTitle, pDefaultInfo->rWnd, IDR_TCDIAGNOSTICSOVERSAMPLINGDUMPFRAME))
	{
		if (((pDefaultInfo->nScope == DISPLAY_SCOPE_GLOBAL  &&  SetType(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_GLOBAL))) || (pDefaultInfo->nScope == DISPLAY_SCOPE_LOCAL  &&  SetType(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_NORMAL)))) && SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetLayout(LPCTSTR pszLayout)
{
	return m_wndView.SetLayout(pszLayout);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout)
{
	return m_wndView.SetLayout(cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nParametersPaneColumns, CONST CUIntArray &nParametersPaneWidths, CONST SIZE &sizeParametersPane, CONST CUIntArray &nRawDataPaneColumns, CONST CUIntArray &nRawDataPaneWidths, CONST SIZE &sizeRawDataPane)
{
	return m_wndView.SetLayout(cLayout, nParametersPaneColumns, nParametersPaneWidths, sizeParametersPane, nRawDataPaneColumns, nRawDataPaneWidths, sizeRawDataPane);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::SetLayout(CONST CByteArray &nLayoutData, CONST CUIntArray &nParametersPaneColumns, CONST CUIntArray &nParametersPaneWidths, CONST SIZE &sizeParametersPane, CONST CUIntArray &nRawDataPaneColumns, CONST CUIntArray &nRawDataPaneWidths, CONST SIZE &sizeRawDataPane)
{
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	return((cLayout.Unmap(nLayoutData)) ? m_wndView.SetLayout(cLayout, nParametersPaneColumns, nParametersPaneWidths, sizeParametersPane, nRawDataPaneColumns, nRawDataPaneWidths, sizeRawDataPane) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetLayout(CString &szLayout) CONST
{
	return m_wndView.GetLayout(szLayout);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST
{
	return m_wndView.GetLayout(cLayout);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nParametersPaneColumns, CUIntArray &nParametersPaneWidths, CSize &sizeParametersPane, CUIntArray &nRawDataPaneColumns, CUIntArray &nRawDataPaneWidths, CSize &sizeRawDataPane) CONST
{
	return m_wndView.GetLayout(cLayout, nParametersPaneColumns, nParametersPaneWidths, sizeParametersPane, nRawDataPaneColumns, nRawDataPaneWidths, sizeRawDataPane);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::GetLayout(CByteArray &nLayoutData, CUIntArray &nParametersPaneColumns, CUIntArray &nParametersPaneWidths, CSize &sizeParametersPane, CUIntArray &nRawDataPaneColumns, CUIntArray &nRawDataPaneWidths, CSize &sizeRawDataPane) CONST
{
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	return((m_wndView.GetLayout(cLayout, nParametersPaneColumns, nParametersPaneWidths, sizeParametersPane, nRawDataPaneColumns, nRawDataPaneWidths, sizeRawDataPane)) ? cLayout.Map(nLayoutData) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetListTitleFont(UINT nPane, CFont *pFont)
{
	return m_wndView.SetListTitleFont(nPane, pFont);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont)
{
	return m_wndView.SetListTitleFont(nPane, plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetListTitleFont(UINT nPane, CFont *pFont) CONST
{
	return m_wndView.GetListTitleFont(nPane, pFont);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST
{
	return m_wndView.GetListTitleFont(nPane, plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetListItemsFont(UINT nPane, CFont *pFont)
{
	return m_wndView.SetListItemsFont(nPane, pFont);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont)
{
	return m_wndView.SetListItemsFont(nPane, plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetListItemsFont(UINT nPane, CFont *pFont) CONST
{
	return m_wndView.GetListItemsFont(nPane, pFont);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST
{
	return m_wndView.GetListItemsFont(nPane, plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetListValuesFont(UINT nPane, CFont *pFont)
{
	return m_wndView.SetListValuesFont(nPane, pFont);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::SetListValuesFont(UINT nPane, CONST LOGFONT *plfFont)
{
	return m_wndView.SetListValuesFont(nPane, plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetListValuesFont(UINT nPane, CFont *pFont) CONST
{
	return m_wndView.GetListValuesFont(nPane, pFont);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::GetListValuesFont(UINT nPane, LOGFONT *plfFont) CONST
{
	return m_wndView.GetListValuesFont(nPane, plfFont);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetGridBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor)
{
	return m_wndView.SetGridBackgroundColors(nNumbersColor, nValuesColor);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetGridBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST
{
	return m_wndView.GetGridBackgroundColors(nNumbersColor, nValuesColor);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetSampleLimit(UINT nLimit)
{
	return m_wndView.SetSampleLimit(nLimit);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetSampleLimit(UINT &nLimit) CONST
{
	return m_wndView.GetSampleLimit(nLimit);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::EnableInvalidDataMode(BOOL bEnable)
{
	return m_wndView.EnableInvalidDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::IsInvalidDataModeEnabled() CONST
{
	return m_wndView.IsInvalidDataModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::EnableBadDataMode(BOOL bEnable)
{
	return m_wndView.EnableBadDataMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::IsBadDataModeEnabled() CONST
{
	return m_wndView.IsBadDataModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::StartMonitoring()
{
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::StopMonitoring()
{
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetCurSample(UINT nPane, INT nIndex)
{
	return m_wndView.SetCurSample(nPane, nIndex);
}

INT CTCDiagnosticsOversamplingDumpWnd::GetCurSample(UINT nPane) CONST
{
	return m_wndView.GetCurSample(nPane);
}

INT CTCDiagnosticsOversamplingDumpWnd::GetSampleCount(UINT nPane) CONST
{
	return m_wndView.GetSampleCount(nPane);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Start()
{
	if ((GetMode() == DISPLAY_MODE_REALTIME  &&  ProcessRealtimeData()) || (GetMode() == DISPLAY_MODE_HISTORY  &&  StartRetrieveData()))
	{
		Initialize(TRUE);
		UpdateAllPanes();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Initialize(BOOL bFlag)
{
	return CDisplayWnd::Initialize(bFlag);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_wndView.Initialize(pTMEnvironment);
}
BOOL CTCDiagnosticsOversamplingDumpWnd::Initialize(CString &szTag, CTimeTag &tTag)
{
	szTag.Empty();
	tTag = CTimeTag(0);
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_BROWSE) || CheckAccountPrivilege(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE);
}

VOID CTCDiagnosticsOversamplingDumpWnd::Update()
{
	if (!Check())
	{
		if (IsWindowVisible())
		{
			ReportEvent(USER_INFORMATIONAL_DISPLAY_ACCESS_VIOLATION);
			ActivateFrame(SW_HIDE);
			return;
		}
	}
	UpdateAllPanes();
	CDisplayWnd::Update();
}
BOOL CTCDiagnosticsOversamplingDumpWnd::Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags)
{
	CTCServiceLock  cLock(this);

	if (IsInitialized())
	{
		for (; GetMode() == DISPLAY_MODE_REALTIME; )
		{
			if (!pTMEnvironment->GetTMUnit()->IsValid() && !nFlags) return TRUE;
			break;
		}
		if ((((nFlags & HISTORYFILE_SUCCESS) && ((nFlags & HISTORYFILE_TMUNIT) || (nFlags & HISTORYFILE_TMPARAMETERS))) || !nFlags) && m_wndView.Update(pTMEnvironment))
		{
			SetUpdateInfo(pTMEnvironment->GetTMUnit()->GetTag(), (pTMEnvironment->GetTMUnit()->IsValid()) ? pTMEnvironment->GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey), pTMEnvironment->GetTMUnit()->GetUnitID(), pTMEnvironment->GetTMUnit()->GetQuality());
			return TRUE;
		}
		return((nFlags & HISTORYFILE_SUCCESS) && !(nFlags & HISTORYFILE_TMUNIT) && !(nFlags & HISTORYFILE_TMPARAMETERS));
	}
	return FALSE;
}

VOID CTCDiagnosticsOversamplingDumpWnd::Reset(CTMEnvironment *pTMEnvironment)
{
	CTCServiceLock  cLock(this);

	if (IsInitialized())
	{
		if (AfxIsValidAddress(pTMEnvironment, sizeof(CTMEnvironment))) pTMEnvironment->Reset();
		m_wndView.Reset(pTMEnvironment);
		SetUpdateInfo();
	}
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Stop()
{
	Initialize(FALSE);
	StopRetrieveData();
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	UINT  nLimit;
	CSize  size[2];
	CString  szFileName;
	LOGFONT  sFontInfo[2][3];
	COLORREF  nColor[2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColumns[2];
	CUIntArray  nWidths[2];
	CByteArray  nLayoutData;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (GetLayout(nLayoutData, nColumns[0], nWidths[0], size[0], nColumns[1], nWidths[1], size[1]) && GetGridBackgroundColors(nColor[0], nColor[1]) && GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &sFontInfo[0][0]) && GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &sFontInfo[0][1]) && GetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &sFontInfo[0][2]) && GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &sFontInfo[1][0]) && GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &sFontInfo[1][1]) && GetSampleLimit(nLimit) && GetRetrieveMode(nMode) && GetRetrieveSpeed(nSpeed) && GetRetrieveInterval(tInterval) && GetRetrieveStartTime(tStartTime) && GetRetrieveStopTime(tStopTime) && GetRetrieveFileName(szFileName) && GetPrintJobs(nPrintInfo) && cProfile.SetTCDiagnosticsOversamplingDumpLayoutInfo(nPage, nDisplay, nLayoutData, nColumns[0], nWidths[0], size[0], nColumns[1], nWidths[1], size[1], nColor[0], nColor[1], nLimit, IsInvalidDataModeEnabled(), IsBadDataModeEnabled(), IsToolTipModeEnabled()) && cProfile.SetTCDiagnosticsOversamplingDumpFontsInfo(nPage, nDisplay, &sFontInfo[0][0], &sFontInfo[0][1], &sFontInfo[0][2], &sFontInfo[1][0], &sFontInfo[1][1]) && cProfile.SetTCDiagnosticsOversamplingDumpModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.SetTCDiagnosticsOversamplingDumpRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.SetTCDiagnosticsOversamplingDumpPrintInfo(nPage, nDisplay, nPrintInfo)))) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	UINT  nLimit;
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	CSize  size[2];
	CString  szFileName;
	LOGFONT  sFontInfo[2][3];
	COLORREF  nColor[2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColumns[2];
	CUIntArray  nWidths[2];
	CByteArray  nLayoutData;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (cProfile.GetTCDiagnosticsOversamplingDumpLayoutInfo(nPage, nDisplay, nLayoutData, nColumns[0], nWidths[0], size[0], nColumns[1], nWidths[1], size[1], nColor[0], nColor[1], nLimit, bInvalidData, bBadData, bToolTips) && cProfile.GetTCDiagnosticsOversamplingDumpFontsInfo(nPage, nDisplay, &sFontInfo[0][0], &sFontInfo[0][1], &sFontInfo[0][2], &sFontInfo[1][0], &sFontInfo[1][1]) && cProfile.GetTCDiagnosticsOversamplingDumpModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.GetTCDiagnosticsOversamplingDumpRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.GetTCDiagnosticsOversamplingDumpPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(nLayoutData, nColumns[0], nWidths[0], size[0], nColumns[1], nWidths[1], size[1]) && SetGridBackgroundColors(nColor[0], nColor[1]) && SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &sFontInfo[0][0]) && SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &sFontInfo[0][1]) && SetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &sFontInfo[0][2]) && SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &sFontInfo[1][0]) && SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &sFontInfo[1][1]) && SetSampleLimit(nLimit) && SetRetrieveMode(nMode) && SetRetrieveSpeed(nSpeed) && SetRetrieveInterval(tInterval) && SetRetrieveStartTime(tStartTime) && SetRetrieveStopTime(tStopTime) && SetRetrieveFileName(szFileName) && SetPrintJobs(nPrintInfo)))) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetLayoutInfo(LPCVOID pData)
{
	INT  cbData;
	DATA  sData;
	CTCServiceLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		for (CopyMemory(&sData, pData, ((cbData = (INT)GlobalSize((HGLOBAL)pData)) >= sizeof(DATA)) ? sizeof(DATA) : 0); cbData >= sizeof(DATA) && sData.cbSize == sizeof(DATA); )
		{
			if (SetLayoutInfo(sData.sizePanes[0], sData.sizePanes[1], &sData.sFont[0][0], &sData.sFont[0][1], &sData.sFont[0][2], &sData.sFont[1][0], &sData.sFont[1][1], &sData.sFont[1][2], sData.nColor[0], sData.nColor[1], sData.nIndex[0], sData.nCount[0], &sData.sScrollInfo[0][0], &sData.sScrollInfo[0][1], sData.nIndex[1], sData.nCount[1], &sData.sScrollInfo[1][0], &sData.sScrollInfo[1][1])) return TRUE;
			break;
		}
		return FALSE;
	}
	return TRUE;
}

INT CTCDiagnosticsOversamplingDumpWnd::GetLayoutInfo(LPVOID *pData) CONST
{
	DATA  sData;
	LPVOID  pBlock;
	CSize  sizePanes[2];
	CTCServiceLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if (GetLayoutInfo(sizePanes[0], sizePanes[1], &sData.sFont[0][0], &sData.sFont[0][1], &sData.sFont[0][2], &sData.sFont[1][0], &sData.sFont[1][1], &sData.sFont[1][2], sData.nColor[0], sData.nColor[1], sData.nIndex[0], sData.nCount[0], &sData.sScrollInfo[0][0], &sData.sScrollInfo[0][1], sData.nIndex[1], sData.nCount[1], &sData.sScrollInfo[1][0], &sData.sScrollInfo[1][1]))
		{
			for (sData.sizePanes[0].cx = sizePanes[0].cx, sData.sizePanes[0].cy = sizePanes[0].cy, sData.sizePanes[1].cx = sizePanes[1].cx, sData.sizePanes[1].cy = sizePanes[1].cy, sData.cbSize = sizeof(DATA); (pBlock = (AfxIsValidAddress(pData, sizeof(DATA))) ? (LPVOID)GlobalReAlloc(*pData, sData.cbSize, GMEM_MOVEABLE | GMEM_ZEROINIT) : (LPVOID)NULL); )
			{
				CopyMemory(pData, &pBlock, sizeof(LPVOID));
				CopyMemory(pBlock, &sData, sizeof(DATA));
				break;
			}
			return sData.cbSize;
		}
	}
	return 0;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
{
	pDefaultInfo->ptWnd.x = 0;
	pDefaultInfo->ptWnd.y = 0;
	pDefaultInfo->nNumber = -1;
	pDefaultInfo->rWnd = rectDefault;
	pDefaultInfo->nScope = DISPLAY_SCOPE_LOCAL;
	pDefaultInfo->nMode = DISPLAY_MODE_REALTIME;
	pDefaultInfo->pData = (LPVOID)NULL;
	pDefaultInfo->nShow = SW_SHOWNORMAL;
	pDefaultInfo->bShow = TRUE;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_TCDIAGNOSTICSOVERSAMPLINGDUMPFRAMESMALLIMAGE) && cBitmap.GetBitmap(&sBitmap); )
	{
		for (nIndex = 0, nCount = (cImages.Create(sBitmap.bmHeight, sBitmap.bmHeight, ILC_COLOR32, sBitmap.bmWidth / sBitmap.bmHeight, 1) && cImages.Add(&cBitmap, RGB(0, 0, 0)) >= 0) ? m_wndToolBar.GetCount() : 0; nIndex < nCount; nIndex++)
		{
			for (m_wndToolBar.GetButtonInfo(nIndex, nButtonID, nButtonStyle, iImage); nButtonID != 0 && nButtonID != (UINT)-1; )
			{
				nImageIDs.Add(nButtonID);
				break;
			}
		}
		cBitmap.DeleteObject();
		break;
	}
	return cMenu.LoadMenu(IDR_TCDIAGNOSTICSOVERSAMPLINGDUMPFRAME);
}

VOID CTCDiagnosticsOversamplingDumpWnd::UpdateBars()
{
	CTCServiceLock  cLock(this);

	UpdateMessagePane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CTCDiagnosticsOversamplingDumpPrintJobs  pJobs;
	CTCDiagnosticsOversamplingDumpPrintJobInfo  *pJobInfo;
	CTCServiceLock  cLock(this);

	for (nJob = 0, nJobs = (GetPrintJobs(pJobs)) ? (INT)pJobs.GetSize() : 0; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = pJobs.GetAt(nJob)) && pJobInfo->GetName() == STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (Print(pJobInfo, pPrintInfo)) break;
			continue;
		}
	}
	if (nJob < nJobs)
	{
		if (pJobInfo->GetPrintMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CanPrint() CONST
{
	CTCServiceLock  cLock(this);

	return((GetSampleCount(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) + GetSampleCount(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) > 0) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::ProcessRealtimeData()
{
	CTCServiceLock  cLock(this);

	if (!GetSampleCount(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS)) SetUpdateInfo();
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveSpeed(nSpeed);
	SetRetrieveInterval(tInterval);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveData();
}
BOOL CTCDiagnosticsOversamplingDumpWnd::StartRetrieveData()
{
	CString  szTag;
	CTimeTag  tTag;
	CEvent  bInit[2];

	if (GetMode() == DISPLAY_MODE_HISTORY  &&  !IsRetrievingData())
	{
		if (m_cRetrieveThread.Start(this, bInit[0], bInit[1], GetRetrieveFileName(), GetRetrieveMode(), GetRetrieveSpeed(), GetRetrieveInterval(), GetRetrieveStartTime(), GetRetrieveStopTime(), &m_bRetrieveFlag, m_cRetrieveStop, m_cRetrieveAutoForward, m_cRetrieveAutoBackward, m_cRetrieveManualForward, m_cRetrieveManualBackward, m_cRetrievePseudoRealtime) && UpdateAllPanes())
		{
			for (WaitForSingleObject(bInit[0], INFINITE); Initialize(szTag, tTag); )
			{
				SetEvent(bInit[1]);
				SetUpdateInfo();
				return TRUE;
			}
			SetEvent(bInit[1]);
		}
		ReportEvent(SYSTEM_WARNING_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_FAILURE);
	}
	return FALSE;
}

LONG CTCDiagnosticsOversamplingDumpWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((m_cRetrieveThread.IsThreadActive()) ? bFlag : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::RetrieveMoreData(UINT nAction)
{
	if (IsRetrievingData())
	{
		if (nAction == TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED)
		{
			SetRetrieveMode(GetRetrieveMode() | nAction);
			m_cRetrieveStop.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveAutoForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveAutoBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveManualForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveManualBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME)
		{
			SetRetrieveMode((GetRetrieveMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME | TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrievePseudoRealtime.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::StopRetrieveData()
{
	return(((IsRetrievingData() && m_cRetrieveThread.Stop()) || !IsRetrievingData()) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetRetrieveMode(UINT nMode)
{
	CTCServiceLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag) : FALSE, (nMode) ? HIWORD(m_bRetrieveFlag) : FALSE);
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CTCDiagnosticsOversamplingDumpWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetRetrieveSpeed(UINT nSpeed)
{
	m_nRetrieveSpeed = nSpeed;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return TRUE;
}
UINT CTCDiagnosticsOversamplingDumpWnd::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetRetrieveInterval(CONST CTimeSpan &tInterval)
{
	CTCServiceLock  cLock(this);

	m_tRetrieveInterval = tInterval;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	CTCServiceLock  cLock(this);

	tInterval = m_tRetrieveInterval;
	return TRUE;
}
CTimeSpan CTCDiagnosticsOversamplingDumpWnd::GetRetrieveInterval() CONST
{
	CTCServiceLock  cLock(this);

	return m_tRetrieveInterval;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CTCServiceLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CTCServiceLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey CTCDiagnosticsOversamplingDumpWnd::GetRetrieveStartTime() CONST
{
	CTCServiceLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CTCServiceLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CTCServiceLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey CTCDiagnosticsOversamplingDumpWnd::GetRetrieveStopTime() CONST
{
	CTCServiceLock  cLock(this);

	return m_tRetrieveStopTime;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
	CTCServiceLock  cLock(this);

	m_szRetrieveFileName = pszFileName;
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetRetrieveFileName(CString &szFileName) CONST
{
	CTCServiceLock  cLock(this);

	szFileName = GetRetrieveFileName();
	return TRUE;
}
CString CTCDiagnosticsOversamplingDumpWnd::GetRetrieveFileName() CONST
{
	CString  szFileName;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CTCServiceLock  cLock(this);

	if (GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles) > 0)
	{
		if (pFiles.Find(m_szRetrieveFileName) >= 0)
		{
			szFileName = m_szRetrieveFileName;
			return szFileName;
		}
		if (GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile))
		{
			szFileName = cFile.GetFileName();
			return szFileName;
		}
	}
	if (!IsInitialized())
	{
		szFileName = m_szRetrieveFileName;
		return szFileName;
	}
	return EMPTYSTRING;
}

VOID CTCDiagnosticsOversamplingDumpWnd::ShowParameterInfo(LPCTSTR pszTag)
{
	ReportEvent((m_dlgParameters.Create(this, pszTag) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetPrintJobs(CONST CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs)
{
	CTCServiceLock  cLock(this);

	return m_pPrintJobs.Copy(&pPrintJobs);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetPrintJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs) CONST
{
	CTCServiceLock  cLock(this);

	return pPrintJobs.Copy(&m_pPrintJobs);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Print(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	UINT  nMode;
	UINT  nTMUnit;
	BOOL  bMetric;
	BOOL  bQuality;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	CString  szLayout;
	CString  szTMUnit;
	CTimeTag  tTMUnit;
	LOGFONT  lfFont[2][3];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CPtrArray  pSymbols;
	CUIntArray  nSymbolIDs;
	CStringArray  szColumns[2];
	CStringArray  szContents[2];
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;
	CTextViewAttributes  pAttributes[2];

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetLayout(szLayout) && GetPrintProperties(pJobInfo, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns[0], szContents[0], pAttributes[0], &lfFont[0][0], &lfFont[0][1], &lfFont[0][2], szColumns[1], szContents[1], pAttributes[1], &lfFont[1][0], &lfFont[1][1], pSymbols, nSymbolIDs))
		{
			if (!AfxIsValidAddress(pPrintInfo, sizeof(PRINTDLG)))
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, szLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns[0], szContents[0], pAttributes[0], &lfFont[0][0], &lfFont[0][1], &lfFont[0][2], szColumns[1], szContents[1], pAttributes[1], &lfFont[1][0], &lfFont[1][1], pSymbols, nSymbolIDs))
					{
						cDC.DeleteDC();
						return TRUE;
					}
					cDC.DeleteDC();
				}
				return FALSE;
			}
			if ((pDevNames = (DEVNAMES *)GlobalLock(pPrintInfo->hDevNames)))
			{
				if ((pDevMode = (DEVMODE *)GlobalLock(pPrintInfo->hDevMode)))
				{
					if (CreatePrinterDC(pPrintInfo->hDevNames, pPrintInfo->hDevMode, cDC))
					{
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, szLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns[0], szContents[0], pAttributes[0], &lfFont[0][0], &lfFont[0][1], &lfFont[0][2], szColumns[1], szContents[1], pAttributes[1], &lfFont[1][0], &lfFont[1][1], pSymbols, nSymbolIDs))
						{
							GlobalUnlock(pPrintInfo->hDevNames);
							GlobalUnlock(pPrintInfo->hDevMode);
							cDC.DeleteDC();
							return TRUE;
						}
						cDC.DeleteDC();
					}
					GlobalUnlock(pPrintInfo->hDevMode);
				}
				GlobalUnlock(pPrintInfo->hDevNames);
			}
		}
	}
	return FALSE;
}

CTCDiagnosticsOversamplingDumpWnd *CTCDiagnosticsOversamplingDumpWnd::Find(INT nType, UINT nMode, LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szLayout;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCDiagnosticsOversamplingDumpWnd  *pTCDiagnosticsOversamplingDumpWnd;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType) && pDisplayWnd->GetMode() == nMode)
		{
			if ((pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)pDisplayWnd)->GetLayout(szLayout) && szLayout == pszName) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pTCDiagnosticsOversamplingDumpWnd : (CTCDiagnosticsOversamplingDumpWnd *)NULL);
}

VOID CTCDiagnosticsOversamplingDumpWnd::SetUpdateInfo()
{
	CTCServiceLock  cLock(this);

	m_szTMUnit.Empty();
	m_tTMUnit = 0;
	m_nTMUnit = 0;
	m_wTMUnit = TMUNIT_DATAQUALITY_NONE;
	UpdateMessagePane();
}
VOID CTCDiagnosticsOversamplingDumpWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality)
{
	CTCServiceLock  cLock(this);

	m_szTMUnit = pszTag;
	m_tTMUnit = tTag;
	m_nTMUnit = nTag;
	m_wTMUnit = wQuality;
	UpdateMessagePane();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST
{
	CTCServiceLock  cLock(this);

	szTag = m_szTMUnit;
	tTag = m_tTMUnit;
	nTag = m_nTMUnit;
	wQuality = m_wTMUnit;
	return TRUE;
}

CTCDiagnosticsOversamplingDumpParametersView *CTCDiagnosticsOversamplingDumpWnd::GetParametersView() CONST
{
	return m_wndView.GetParametersView();
}

CTCDiagnosticsOversamplingDumpRawDataView *CTCDiagnosticsOversamplingDumpWnd::GetRawDataView() CONST
{
	return m_wndView.GetRawDataView();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_TCDIAGNOSTICSOVERSAMPLINGDUMPFRAMELARGEIMAGE, 0, IDB_TCDIAGNOSTICSOVERSAMPLINGDUMPFRAMESMALLIMAGE, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPCLEARALL), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTOP), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEPSEUDOREALTIME), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nTCDiagnosticsOversamplingDumpStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CreateView()
{
	if (m_wndView.Create(this))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Customize(BOOL bDefault)
{
	CByteArray  nPrintInfo;

	return(((!bDefault  &&  GetPrintJobs(nPrintInfo) && nPrintInfo.GetSize() > 0) || SetPrintJobs(nPrintInfo)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nTCDiagnosticsOversamplingDumpStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nTCDiagnosticsOversamplingDumpStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nTCDiagnosticsOversamplingDumpStatusBarIndicators, sizeof(nTCDiagnosticsOversamplingDumpStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CTCDiagnosticsOversamplingDumpWnd::UpdateMessagePane()
{
	UINT  nTag;
	WORD  wQuality;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage;

	if (GetUpdateInfo(szTag, tTag, nTag, wQuality))
	{
		szMessage.Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_FULLUPDATEMESSAGE) : ((IsRetrievingData() && HIWORD(IsRetrievingData())) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_RETRIEVEMESSAGE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_NODATAMESSAGE))) : ((nTag == (UINT)-1) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_INITUPDATEMESSAGE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_UPDATEMESSAGE)), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag, nTag, ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_QUALITYGOOD)) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_QUALITYGOOD)) : ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_QUALITYBAD)) + STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_QUALITYBAD)));
		m_wndStatusBar.SetPaneText(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MESSAGEPANE, szMessage);
	}
	m_wndToolBar.EnableButton(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPCLEARALL, (IsInitialized() && m_wndView.GetSampleCount(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) + m_wndView.GetSampleCount(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) > 0) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpWnd::UpdateModePane()
{
	m_wndStatusBar.SetPaneText(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE, (GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED)) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_AUTOFORWARDMODE) : (((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED)) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_AUTOBACKWARDMODE) : (((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED)) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_PSEUDOREALTIMEMODE) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_NORMALMODE)))) : STRING(IDS_DISPLAY_MODE_REALTIME));
	m_wndToolBar.EnableButton(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTOP, (IsRetrievingData() && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEPSEUDOREALTIME, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

VOID CTCDiagnosticsOversamplingDumpWnd::UpdateTypePane()
{
	CString  szType;
	CString  szLayout;

	switch (HIWORD(GetType()))
	{
	case TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_GLOBAL:
	{ szType = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEGLOBAL);
	break;
	}
	case TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_NORMAL:
	{ if (GetLayout(szLayout) && !szLayout.IsEmpty())
	{
		szType.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPENORMAL), (LPCTSTR)szLayout);
		break;
	}
	szType = STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPENORMAL);
	szType = szType.Left((szType.Find(SPACE) >= 0) ? szType.Find(SPACE) : lstrlen(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPENORMAL)));
	break;
	}
	}
	m_wndStatusBar.SetPaneText(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE, szType);
}

VOID CTCDiagnosticsOversamplingDumpWnd::UpdateData()
{
	m_wndView.Update();
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CTCDiagnosticsOversamplingDumpPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CTCDiagnosticsOversamplingDumpPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szParametersColumns, CStringArray &szParametersContents, CTextViewAttributes &pParametersAttributes, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pParametersValuesFont, CStringArray &szRawDataColumns, CStringArray &szRawDataContents, CTextViewAttributes &pRawDataAttributes, LOGFONT *pRawDataTitleFont, LOGFONT *pRawDataItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST
{
	WORD  wQuality;
	CTCServiceLock  cLock(this);

	if (GetUpdateInfo(szTMUnit, tTMUnit, nTMUnit, wQuality))
	{
		if (m_wndView.GetPrintProperties(pJobInfo, szParametersColumns, szParametersContents, pParametersAttributes, pParametersTitleFont, pParametersItemsFont, pParametersValuesFont, szRawDataColumns, szRawDataContents, pRawDataAttributes, pRawDataTitleFont, pRawDataItemsFont, pSymbols, nSymbolIDs))
		{
			bQuality = ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? TRUE : FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szLayout;
	CString  szJobTitle;

	for (GetLayout(szLayout), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(szLayout), STRING(IDS_DISPLAY_TITLE_TCDIAGNOSTICSOVERSAMPLINGDUMP)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::PrintJob(CDC &cDC, CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szParametersColumns, CONST CStringArray &szParametersContents, CONST CTextViewAttributes &pParametersAttributes, CONST LOGFONT *pParametersTitleFont, CONST LOGFONT *pParametersItemsFont, CONST LOGFONT *pParametersValuesFont, CONST CStringArray &szRawDataColumns, CONST CStringArray &szRawDataContents, CONST CTextViewAttributes &pRawDataAttributes, CONST LOGFONT *pRawDataTitleFont, CONST LOGFONT *pRawDataItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs)
{
	INT  nPos;
	INT  nPage;
	INT  nPages;
	INT  nPane;
	INT  nPanes;
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	INT  nFont;
	INT  nFonts;
	INT  nSpacing;
	INT  nHeight[2];
	UINT  nFormat;
	BOOL  bOverlap;
	BOOL  bOutput;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pFont;
	CFont  *pOldFont;
	CFont  cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONTS];
	CSize  sizeSymbol;
	CString  szColumn;
	COLORREF  nColor;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	TEXTMETRIC  tmFont;
	CUIntArray  nTabs[2];
	CStringArray  szColumns[2];
	CStringArray  szContents[2];
	CStringArray  szColumnsText;
	CTextViewAttribute  *pAttribute;
	CTextViewAttributes  pAttributes[2];

	for (nPage = nPages = 0; (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_SUBTITLE]) && CalcPrintDocDetailsFont(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_DETAILS]) && CalcPrintDocCommentsFont(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_COMMENTS]) && CalcPrintDocListTitleFont(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSTITLE]) && CalcPrintDocListItemsFonts(cDC, rArea, szParametersColumns, szParametersContents, pParametersTitleFont, pParametersItemsFont, pParametersValuesFont, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMSTITLE], cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMS], cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTVALUES]) && CalcPrintDocListTitleFont(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATATITLE]) && CalcPrintDocListItemsFonts(cDC, rArea, szRawDataColumns, szRawDataContents, pRawDataTitleFont, pRawDataItemsFont, pRawDataItemsFont, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMSTITLE], cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMS], cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTVALUES]) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_NOTICE], cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, rArea, szParametersColumns, szParametersContents, &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMSTITLE], &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMS], &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTVALUES], nTabs[0]) == szParametersColumns.GetSize() && CalcPrintDocTitleWidth(cDC, rArea, szRawDataColumns, szRawDataContents, &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMSTITLE], &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMS], &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTVALUES], nTabs[1]) == szRawDataColumns.GetSize()) ? nPages : -1) == 0); )
	{
		for (nFont = 0, nFonts = (!nPages) ? (INT)(sizeof(cFont) / sizeof(cFont[0])) : 0; nFont < nFonts; nFont++)
		{
			pFonts.SetAtGrow(nFont, &cFont[nFont]);
			continue;
		}
		for (nPane = 0, nPanes = TCDIAGNOSTICSOVERSAMPLINGDUMP_PANES, szColumns[0].Copy(szParametersColumns), szColumns[1].Copy(szRawDataColumns), szContents[0].Copy(szParametersContents), szContents[1].Copy(szRawDataContents), pAttributes[0].Copy(&pParametersAttributes), pAttributes[1].Copy(&pRawDataAttributes), nSpacing = 0, rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bOverlap = FALSE; nPages >= 0 && nPane < nPanes; nPane++)
		{
			for (nLine = 0, nLines = ((!nPane && (pJobInfo->GetPrintMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_PARAMETERVALUES)) || (nPane > 0 && (pJobInfo->GetPrintMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_RAWDATA))) ? (INT)szContents[nPane].GetSize() : 0, bOutput = TRUE; nPages >= 0 && nLine < nLines; nLine++, bOutput = TRUE)
			{
				for (nColumn = 0, nColumns = (INT)szColumns[nPane].GetSize(), ExtractPrintDocText(szContents[nPane].GetAt(nLine), szColumnsText), nHeight[0] = nHeight[1] = 0; nPages >= 0 && nColumn < nColumns; nColumn = nColumn + 1, nHeight[1] = 0)
				{
					for (pFont = (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMS + 4 * nPane); lstrcmp(szColumns[nPane].GetAt(nColumn), STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER)) && lstrcmp(szColumns[nPane].GetAt(nColumn), STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME)) && lstrcmp(szColumns[nPane].GetAt(nColumn), STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)) && lstrcmp(szColumns[nPane].GetAt(nColumn), STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER)) && lstrcmp(szColumns[nPane].GetAt(nColumn), STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME)); )
					{
						pFont = (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTVALUES + 4 * nPane);
						break;
					}
					if (rClip.Height() > 0)
					{
						if ((pOldFont = cDC.SelectObject(pFont)))
						{
							if ((nSpacing = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmHeight / 10, 1) : -1) >= 0)
							{
								for (rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? (rCalc.top + nSpacing + tmFont.tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont.tmHeight)) : (rCalc.top + tmFont.tmHeight*((rClip.bottom - rCalc.top) / tmFont.tmHeight))), nFormat = DT_LEFT | DT_NOPREFIX | DT_WORDBREAK, nColor = cDC.GetTextColor(); (pAttribute = pAttributes[nPane].GetAt(nLine)); )
								{
									pAttribute->GetColumnFormat(nColumn, nFormat);
									pAttribute->GetColumnColor(nColumn, nColor);
									break;
								}
								for (szColumn = (!szColumnsText.GetAt(nColumn).IsEmpty()) ? (((nPos = (szColumns[nPane].GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) || szColumns[nPane].GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER)) ? szColumnsText.GetAt(nColumn).Find((szColumns[nPane].GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER)) ? CTCDiagnosticsOversamplingDumpParametersTextView::GetSymbolDelimiter() : CTCDiagnosticsOversamplingDumpRawDataTextView::GetSymbolDelimiter()) : -1) >= 0) ? (szColumnsText.GetAt(nColumn).Left(nPos)) : (szColumnsText.GetAt(nColumn) + SPACE)) : EMPTYSTRING, nFormat = (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage && nPage <= nToPage))) ? nFormat : (nFormat | DT_CALCRECT), nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor : cDC.GetTextColor()), sizeSymbol.cx = sizeSymbol.cy = tmFont.tmHeight, nHeight[1] = cDC.DrawText(szColumn, (rItem = CRect((nColumn > 0) ? (rCalc.left + nTabs[nPane].GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs[nPane].GetAt(nColumn), rCalc.bottom)), nFormat); szColumns[nPane].GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) || szColumns[nPane].GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER); )
								{
									DrawPrintDocSymbol(cDC, (rItem = ((nFormat & DT_CALCRECT) != DT_CALCRECT  &&  rItem.top + sizeSymbol.cy <= rCalc.bottom) ? CRect(rItem.left + cDC.GetTextExtent(szColumn).cx + sizeSymbol.cx / 2, rItem.top, rItem.left + cDC.GetTextExtent(szColumn).cx + sizeSymbol.cx / 2 + sizeSymbol.cx, rItem.top + sizeSymbol.cy) : CRect(0, 0, 0, 0)), (szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_INFORMATION)) >= 0) ? IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPINFORMATION : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_WARNING)) >= 0) ? IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPWARNING : ((szColumnsText.GetAt(nColumn).Find(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_LIST_ALERT_ERROR)) >= 0) ? IDP_TCDIAGNOSTICSOVERSAMPLINGDUMPERROR : -1)), pSymbols, nSymbolIDs);
									break;
								}
								nHeight[0] = max(max(nHeight[0], sizeSymbol.cy), nHeight[1]);
								cDC.SetTextColor(nOldColor);
								cDC.SelectObject(pOldFont);
							}
							else
							{
								cDC.SelectObject(pOldFont);
								break;
							}
						}
						else break;
					}
					if (((rCalc.top + nHeight[1] > rCalc.bottom || bOverlap) && nColumn == nColumns - 1) || !rClip.Height())
					{
						if (nPages > 0 && (nPage == nPages || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage == nToPage)))
						{
							nPages = nPage;
							nLines = nLine;
							nColumns = nColumn;
							break;
						}
						if (bOutput && (!nPages || ((!nPage || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage || nPage > nToPage)) || cDC.EndPage() >= 0) && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage - 1 || nPage >= nToPage)) || (((((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage) && nPage > 0) || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage != nFromPage - 1)) || StartPrintJob(cDC)) && cDC.StartPage() >= 0)))))
						{
							if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pszLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, (nPane > 0) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS) : EMPTYSTRING, szColumns[nPane], pFonts, nTabs[nPane], nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
							{
								rCalc.SetRect(rClip.left, rClip.top - rCalc.Height() - nSpacing, rClip.right, rClip.bottom);
								bOverlap = FALSE;
								bOutput = FALSE;
								nColumn = -1;
								nPage++;
								continue;
							}
						}
						break;
					}
					bOverlap = (rCalc.top + nHeight[1] > rCalc.bottom) ? TRUE : bOverlap;
				}
				if (nLine < nLines  &&  nColumn == nColumns)
				{
					rCalc.DeflateRect(0, nHeight[0], 0, 0);
					continue;
				}
				break;
			}
			if (nLine == nLines)
			{
				if (nPage <= nPages || !nPages)
				{
					if (!nPane && (pJobInfo->GetPrintMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_RAWDATA) && szContents[1].GetSize() > 0)
					{
						if (DrawPrintDocListTitle(cDC, (rItem = rCalc), GetPrintDocListTitle(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)), &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATATITLE], TRUE) && DrawPrintDocListItemsTitle(cDC, rItem, szColumns[1], &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMSTITLE], nTabs[1], TRUE) && DrawPrintDocListItemsTitle(cDC, rItem, szColumns[1], &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMSTITLE], nTabs[1], TRUE) && (rItem.top > rItem.bottom || (DrawPrintDocListTitle(cDC, rCalc, GetPrintDocListTitle(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)), &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATATITLE]) && DrawPrintDocListItemsTitle(cDC, rCalc, szColumns[1], &cFont[TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMSTITLE], nTabs[1]))))
						{
							rCalc.SetRect(rCalc.left, (rItem.top <= rItem.bottom) ? rCalc.top : rClip.bottom, rCalc.right, rClip.bottom);
							continue;
						}
						nPages = -1;
						break;
					}
					continue;
				}
			}
			break;
		}
		if (nPages >= 0)
		{
			if (nLine == nLines)
			{
				if (!szContents[nPane].GetSize())
				{
					if (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nFromPage > 1)
					{
						nPages = nPage = 0;
						break;
					}
					if (StartPrintJob(cDC))
					{
						if (cDC.StartPage() >= 0)
						{
							if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pszLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, (nPane > 0) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS) : EMPTYSTRING, szColumns[nPane], pFonts, nTabs[nPane], 1, 1, rClip))
							{
								nPages = nPage = 1;
								break;
							}
							cDC.EndPage();
						}
						EndPrintJob(cDC);
					}
					nPages = -1;
					break;
				}
				if (!nPages)
				{
					if (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || nPage >= nFromPage)
					{
						nPages = nPage;
						nPage = 0;
						continue;
					}
					nPages = nPage = 0;
				}
			}
			else
			{
				if (nPages > 0) cDC.AbortDoc();
				nPages = -1;
			}
		}
		break;
	}
	return(((!nPages || (nPages > 0 && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage < nFromPage) || (cDC.EndPage() >= 0 && EndPrintJob(cDC))))) && nPage == nPages) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocPage(CDC &cDC, CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, LPCTSTR pszTitle, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(pszLayout), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocDetails(cDC, prClip, GetPrintDocDetails(pJobInfo, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_DETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocComments(cDC, prClip, GetPrintDocComments(pJobInfo), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_COMMENTS), (nPage <= 0) ? TRUE : FALSE) && (lstrlen(pszTitle) > 0 || DrawPrintDocListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE)) && (!lstrlen(pszTitle) || (DrawPrintDocListTitle(cDC, prClip, GetPrintDocListTitle(pszTitle), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATATITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE))) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszLayout, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszLayout, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszLayout, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += (lstrlen(pszLayout) > 0) ? rCalc.Height() : 0;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszDetails, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszDetails, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszComments, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszComments, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += 2 * cDC.GetTextExtent(SPACE).cy;
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocListTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
{
	INT  nColumn;
	INT  nColumns;
	INT  nHeight;
	CSize  rCalc;
	CRect  rColumn;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), nHeight = 0; nColumn < nColumns; nColumn++)
		{
			rColumn.SetRect((nColumn > 0) ? (prClip->left + nTabs.GetAt(nColumn - 1)) : prClip->left, prClip->top, prClip->left + nTabs.GetAt(nColumn), prClip->top);
			cDC.DrawText(szColumns.GetAt(nColumn), rColumn, (szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)) ? (DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_CALCRECT) : (DT_CENTER | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT));
			nHeight = max(nHeight, rColumn.Height());
		}
		for (nColumn = 0, nColumns = (!bCalc) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
		{
			rColumn.SetRect((nColumn > 0) ? (prClip->left + nTabs.GetAt(nColumn - 1)) : prClip->left, prClip->top, prClip->left + nTabs.GetAt(nColumn), prClip->top + nHeight);
			cDC.DrawText(szColumns.GetAt(nColumn), rColumn, (szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)) ? (DT_LEFT | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE) : (DT_CENTER | DT_NOPREFIX | DT_WORDBREAK));
		}
		prClip->top += nHeight;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs)
{
	INT  nID;
	INT  nIDs;
	CImage  *pSymbol;

	for (nID = 0, nIDs = (nSymbolID != (UINT)-1) ? (INT)nSymbolIDs.GetSize() : -1; nID < nIDs; nID++)
	{
		if (nSymbolIDs.GetAt(nID) == nSymbolID) break;
		continue;
	}
	if ((pSymbol = (nID < nIDs) ? (CImage *)pSymbols.GetAt(nID) : (CImage *)NULL) && prClip->right - prClip->left > 0 && prClip->bottom - prClip->top > 0)
	{
		pSymbol->Draw(cDC.GetSafeHdc(), prClip->left, prClip->top, prClip->right - prClip->left, prClip->bottom - prClip->top);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL CTCDiagnosticsOversamplingDumpWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
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

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocSubTitle(LPCTSTR pszLayout) CONST
{
	return pszLayout;
}

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocDetails(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST
{
	INT  nDigits;
	UINT  nRange[2];
	CString  szMode;
	CString  szUpdate;
	CString  szDetails;
	CString  szRange[2];
	CTimeKey  tRange[2];
	CStringTools  cStringTools;

	pJobInfo->GetPrintRange(nRange[0], nRange[1]);
	pJobInfo->GetPrintRange(tRange[0], tRange[1]);
	nDigits = max(cStringTools.ConvertUIntToString(nRange[1]).GetLength(), 3);
	szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_FULLUPDATECOMMENT) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_NODATACOMMENT)) : ((nTMUnit == (UINT)-1) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_INITUPDATECOMMENT) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_UPDATECOMMENT)), (LPCTSTR)tTMUnit.FormatGmt(), pszTMUnit, nTMUnit, (bQuality) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_QUALITYGOOD) : STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_QUALITYBAD));
	szRange[0].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_ITEMRANGESUBTITLE), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nRange[0], nDigits), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nRange[1], nDigits));
	szRange[1].Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_TIMERANGESUBTITLE), (LPCTSTR)tRange[0].FormatGmt(), (LPCTSTR)tRange[1].FormatGmt());
	szDetails = (pJobInfo->GetPrintMode() & (TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE | TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE)) ? STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_SUBTITLE) : EMPTYSTRING;
	szDetails += (pJobInfo->GetPrintMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE) ? (CString(CR) + CString(EOL) + szRange[0]) : EMPTYSTRING;
	szDetails += (pJobInfo->GetPrintMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE) ? (CString(CR) + CString(EOL) + szRange[1]) : EMPTYSTRING;
	return((!szDetails.IsEmpty()) ? (szUpdate + EOL + szMode + EOL + szDetails) : (szUpdate + EOL + szMode));
}

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocComments(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo) CONST
{
	return pJobInfo->GetComments();
}

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocListTitle(LPCTSTR pszTitle) CONST
{
	return CString(EOL) + CString(EOL) + pszTitle;
}

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szItems;

	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		szItems += (nColumn > 0) ? CString(TAB) : EMPTYSTRING;
		szItems += szColumns.GetAt(nColumn);
	}
	return szItems;
}

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CTCDiagnosticsOversamplingDumpWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

INT CTCDiagnosticsOversamplingDumpWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
{
	INT  nPos[2];
	INT  nLength;
	CString  szText;

	for (nPos[0] = 0, nLength = lstrlen(pszText), szColumnsText.RemoveAll(); nPos[0] <= nLength; nPos[0] += ++nPos[1])
	{
		if ((nPos[1] = (INT)_tcscspn((szText = pszText + nPos[0]), CString(CTextView::GetColumnDelimiter()))) < nLength - nPos[0])
		{
			szColumnsText.Add((nPos[1] > 0) ? szText.Left(nPos[1]) : EMPTYSTRING);
			continue;
		}
		szColumnsText.Add(szText);
		break;
	}
	return((INT)szColumnsText.GetSize());
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocListTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST LOGFONT *pValuesFont, CFont &cTitleFont, CFont &cItemsFont, CFont &cValuesFont) CONST
{
	INT  nWidth;
	INT  nHeight;
	CFont  cFont[3];
	CUIntArray  nTabs;

	for (nHeight = max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))); nHeight < 0; nHeight++)
	{
		if (cFont[0].CreateFont(nHeight, 0, pTitleFont->lfEscapement, pTitleFont->lfOrientation, FW_BOLD, pTitleFont->lfItalic, pTitleFont->lfUnderline, pTitleFont->lfStrikeOut, pTitleFont->lfCharSet, pTitleFont->lfOutPrecision, pTitleFont->lfClipPrecision, pTitleFont->lfQuality, pTitleFont->lfPitchAndFamily, pTitleFont->lfFaceName))
		{
			if (cFont[1].CreateFont((4 * nHeight) / 5, 0, pItemsFont->lfEscapement, pItemsFont->lfOrientation, pItemsFont->lfWeight, pItemsFont->lfItalic, pItemsFont->lfUnderline, pItemsFont->lfStrikeOut, pItemsFont->lfCharSet, pItemsFont->lfOutPrecision, pItemsFont->lfClipPrecision, pItemsFont->lfQuality, pItemsFont->lfPitchAndFamily, pItemsFont->lfFaceName))
			{
				if (cFont[2].CreateFont((4 * nHeight) / 5, 0, pValuesFont->lfEscapement, pValuesFont->lfOrientation, pValuesFont->lfWeight, pValuesFont->lfItalic, pValuesFont->lfUnderline, pValuesFont->lfStrikeOut, pValuesFont->lfCharSet, pValuesFont->lfOutPrecision, pValuesFont->lfClipPrecision, pValuesFont->lfQuality, pValuesFont->lfPitchAndFamily, pValuesFont->lfFaceName))
				{
					if (CalcPrintDocTitleWidth(cDC, rArea, szColumns, szContents, &cFont[0], &cFont[1], &cFont[2], nTabs) > 0)
					{
						if ((nWidth = nTabs.GetAt(nTabs.GetSize() - 1)) > rArea.right - rArea.left)
						{
							nHeight = (nHeight*(rArea.right - rArea.left)) / nWidth - 1;
							cFont[0].DeleteObject();
							cFont[1].DeleteObject();
							cFont[2].DeleteObject();
							continue;
						}
						cTitleFont.Attach(cFont[0].Detach());
						cItemsFont.Attach(cFont[1].Detach());
						cValuesFont.Attach(cFont[2].Detach());
						break;
					}
					cFont[2].DeleteObject();
				}
				cFont[1].DeleteObject();
			}
			cFont[0].DeleteObject();
		}
	}
	return((cTitleFont.GetSafeHandle() && cItemsFont.GetSafeHandle() && cValuesFont.GetSafeHandle()) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
{
	INT  nPos;
	INT  nWidth[2];
	CFont  *pOldFont;
	CString  szColumn;

	if ((pOldFont = cDC.SelectObject(pTitleFont)))
	{
		for (szColumn = pszColumn, nWidth[0] = 0; (nPos = szColumn.Find(EOL)) >= 0; szColumn = szColumn.Mid(nPos + 1))
		{
			nWidth[1] = cDC.GetTextExtent(szColumn.Left(nPos)).cx;
			nWidth[0] = max(nWidth[0], nWidth[1]);
		}
		nWidth[1] = cDC.GetTextExtent(szColumn).cx;
		nWidth[0] = max(nWidth[0], nWidth[1]);
		cDC.SelectObject(pOldFont);
		return nWidth[0];
	}
	return 0;
}
INT CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CFont *pValuesFont, CUIntArray &nTabs) CONST
{
	INT  nIndent;
	INT  nColumn;
	INT  nColumns;
	INT  nWidth[2];
	CSize  sizeSymbol;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;
	CStringArray  szLines;

	for (nIndent = 0, sizeSymbol.cx = sizeSymbol.cy = 0, nTabs.RemoveAll(); (pOldFont = cDC.SelectObject(pTitleFont)); )
	{
		nIndent = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmAveCharWidth, nIndent) : nIndent;
		cDC.SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		if (cDC.GetTextMetrics(&tmFont))
		{
			sizeSymbol.cx = tmFont.tmHeight;
			sizeSymbol.cy = tmFont.tmHeight;
			nIndent = max(tmFont.tmAveCharWidth, nIndent);
		}
		cDC.SelectObject(pOldFont);
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), szLines.Copy(szContents); nColumn < nColumns; nColumn++)
	{
		for (nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont), nWidth[1] = CalcPrintDocColumnWidth(cDC, rArea, szColumns.GetAt(nColumn), szLines, pItemsFont, pValuesFont); szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER) || szColumns.GetAt(nColumn) == STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER); )
		{
			nWidth[1] += 3 * sizeSymbol.cx / 2;
			break;
		}
		nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
	}
	if (nTabs.GetSize() > 0)
	{
		nTabs.SetAt(nTabs.GetSize() - 1, nTabs.GetAt(nTabs.GetSize() - 1) - nIndent);
		return((INT)nTabs.GetSize());
	}
	return 0;
}

INT CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont, CFont *pValuesFont) CONST
{
	INT  nPos;
	INT  nLine;
	INT  nLines;
	INT  nWidth;
	CRect  rColumn;
	CFont  *pOldFont;
	CString  szLine;

	if ((pOldFont = (lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE))) ? cDC.SelectObject(pItemsFont) : cDC.SelectObject(pValuesFont)))
	{
		for (nLine = 0, nLines = (INT)szContents.GetSize(), nWidth = 0; nLine < nLines; nLine++)
		{
			if ((nPos = szContents.GetAt(nLine).Find(CTextView::GetColumnDelimiter())) >= 0)
			{
				for (rColumn.SetRect(0, 0, cDC.GetTextExtent((szLine = ((!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER)) || !lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER))) && szContents.GetAt(nLine).Left(nPos).Find((!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER))) ? CTCDiagnosticsOversamplingDumpParametersTextView::GetSymbolDelimiter() : CTCDiagnosticsOversamplingDumpRawDataTextView::GetSymbolDelimiter()) >= 0) ? szContents.GetAt(nLine).Left(nPos).Left(szContents.GetAt(nLine).Left(nPos).Find((!lstrcmp(pszColumn, STRING(IDS_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER))) ? CTCDiagnosticsOversamplingDumpParametersTextView::GetSymbolDelimiter() : CTCDiagnosticsOversamplingDumpRawDataTextView::GetSymbolDelimiter())) : szContents.GetAt(nLine).Left(nPos))).cx, 0); rColumn.Width() > rArea.right - rArea.left; )
				{
					cDC.DrawText(szLine, (rColumn = CRect(0, 0, rArea.right - rArea.left, 0)), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT);
					break;
				}
				szContents.SetAt(nLine, szContents.GetAt(nLine).Mid(nPos + 1));
				nWidth = max(rColumn.Width(), nWidth);
				continue;
			}
			if (szContents.GetAt(nLine).GetLength() > 0)
			{
				for (rColumn.SetRect(0, 0, cDC.GetTextExtent((szLine = szContents.GetAt(nLine))).cx, 0); rColumn.Width() > rArea.right - rArea.left; )
				{
					cDC.DrawText(szLine, (rColumn = CRect(0, 0, rArea.right - rArea.left, 0)), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK | DT_CALCRECT);
					break;
				}
				szContents.SetAt(nLine, EMPTYSTRING);
				nWidth = max(rColumn.Width(), nWidth);
				continue;
			}
		}
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::SetLayoutInfo(CONST SIZE &sizeParametersPane, CONST SIZE &sizeRawDataPane, CONST LOGFONT *pParametersPaneTitleFont, CONST LOGFONT *pParametersPaneItemsFont, CONST LOGFONT *pParametersPaneValuesFont, CONST LOGFONT *pRawDataPaneTitleFont, CONST LOGFONT *pRawDataPaneItemsFont, CONST LOGFONT *pRawDataPaneValuesFont, COLORREF nNumbersBackgroundColor, COLORREF nValuesBackgroundColor, INT nParametersPaneIndex, INT nParametersPaneCount, CONST SCROLLINFO *pParametersPaneHorzScrollInfo, CONST SCROLLINFO *pParametersPaneVertScrollInfo, INT nRawDataPaneIndex, INT nRawDataPaneCount, CONST SCROLLINFO *pRawDataPaneHorzScrollInfo, CONST SCROLLINFO *pRawDataPaneVertScrollInfo)
{
	CSize  sizePane[2];
	CUIntArray  nWidths[2];
	CUIntArray  nColumns[2];
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	return((GetLayout(cLayout, nColumns[0], nWidths[0], sizePane[0], nColumns[1], nWidths[1], sizePane[1])) ? (m_wndView.SetLayout(cLayout, nColumns[0], nWidths[0], sizeParametersPane, nColumns[1], nWidths[1], sizeRawDataPane) && m_wndView.SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, pParametersPaneTitleFont) && m_wndView.SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, pParametersPaneItemsFont) && m_wndView.SetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, pParametersPaneValuesFont) && m_wndView.SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, pRawDataPaneTitleFont) && m_wndView.SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, pRawDataPaneItemsFont) && m_wndView.SetGridBackgroundColors(nNumbersBackgroundColor, nValuesBackgroundColor) && m_wndView.SetLayoutInfo(nParametersPaneIndex, nParametersPaneCount, pParametersPaneHorzScrollInfo, pParametersPaneVertScrollInfo, nRawDataPaneIndex, nRawDataPaneCount, pRawDataPaneHorzScrollInfo, pRawDataPaneVertScrollInfo)) : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::GetLayoutInfo(CSize &sizeParametersPane, CSize &sizeRawDataPane, LOGFONT *pParametersPaneTitleFont, LOGFONT *pParametersPaneItemsFont, LOGFONT *pParametersPaneValuesFont, LOGFONT *pRawDataPaneTitleFont, LOGFONT *pRawDataPaneItemsFont, LOGFONT *pRawDataPaneValuesFont, COLORREF &nNumbersBackgroundColor, COLORREF &nValuesBackgroundColor, INT &nParametersPaneIndex, INT &nParametersPaneCount, SCROLLINFO *pParametersPaneHorzScrollInfo, SCROLLINFO *pParametersPaneVertScrollInfo, INT &nRawDataPaneIndex, INT &nRawDataPaneCount, SCROLLINFO *pRawDataPaneHorzScrollInfo, SCROLLINFO *pRawDataPaneVertScrollInfo) CONST
{
	CUIntArray  nWidths[2];
	CUIntArray  nColumns[2];
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	return((m_wndView.GetLayout(cLayout, nColumns[0], nWidths[0], sizeParametersPane, nColumns[1], nWidths[1], sizeRawDataPane) && m_wndView.GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, pParametersPaneTitleFont) && m_wndView.GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, pParametersPaneItemsFont) && m_wndView.GetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, pParametersPaneValuesFont) && m_wndView.GetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, pRawDataPaneTitleFont) && m_wndView.GetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, pRawDataPaneItemsFont) && m_wndView.GetGridBackgroundColors(nNumbersBackgroundColor, nValuesBackgroundColor) && m_wndView.GetLayoutInfo(nParametersPaneIndex, nParametersPaneCount, pParametersPaneHorzScrollInfo, pParametersPaneVertScrollInfo, nRawDataPaneIndex, nRawDataPaneCount, pRawDataPaneHorzScrollInfo, pRawDataPaneVertScrollInfo)) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Lock()
{
	return((GetTCService()->Lock() && CDisplayWnd::Lock()) ? TRUE : FALSE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::Unlock()
{
	return((CDisplayWnd::Unlock() && GetTCService()->Unlock()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTCDiagnosticsOversamplingDumpWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTCDiagnosticsOversamplingDumpWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS, OnSettings)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS, OnParameters)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPCLEARALL, OnClearAll)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTOP, OnRetrieveStop)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEFORWARD, OnRetrieveAutoForward)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEBACKWARD, OnRetrieveAutoBackward)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPBACKWARD, OnRetrieveManualBackward)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEPSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS, OnUpdateParameters)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPCLEARALL, OnUpdateClearAll)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTOP, OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEFORWARD, OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEBACKWARD, OnUpdateRetrieveAutoBackward)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVESTEPBACKWARD, OnUpdateRetrieveManualBackward)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEPSEUDOREALTIME, OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_TCDIAGNOSTICSOVERSAMPLINGDUMPPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpWnd message handlers

int CTCDiagnosticsOversamplingDumpWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_TCDIAGNOSTICSOVERSAMPLINGDUMPFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CTCDiagnosticsOversamplingDumpWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	CRect  rView;
	CRect  rPane[2];
	CRect  rToolBar;
	CRect  rStatusBar;

	for (rView.SetRectEmpty(); IsWindow(m_wndView.GetSafeHwnd()); )
	{
		GetParametersView()->GetWindowRect(rPane[0]);
		GetRawDataView()->GetWindowRect(rPane[1]);
		rView.SetRect(0, 0, GetParametersView()->GetTrackSize().cx + GetRawDataView()->GetTrackSize().cx, GetParametersView()->GetTrackSize().cy + GetRawDataView()->GetTrackSize().cy + (rPane[1].top - rPane[0].bottom + 1) / 2);
		break;
	}
	for (rToolBar.SetRectEmpty(); IsWindow(m_wndToolBar.GetSafeHwnd()); )
	{
		m_wndToolBar.GetWindowRect(rToolBar);
		break;
	}
	for (rStatusBar.SetRectEmpty(); IsWindow(m_wndStatusBar.GetSafeHwnd()); )
	{
		m_wndStatusBar.GetWindowRect(rStatusBar);
		break;
	}
	lpMMI->ptMinTrackSize.x = max(lpMMI->ptMinTrackSize.x, 2 * GetSystemMetrics(SM_CXFRAME) + rView.Width());
	lpMMI->ptMinTrackSize.y = max(lpMMI->ptMinTrackSize.y, 2 * (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYEDGE)) + GetSystemMetrics(SM_CYCAPTION) + rToolBar.Height() + rView.Height() + rStatusBar.Height());
	CDisplayWnd::OnGetMinMaxInfo(lpMMI);
}

void CTCDiagnosticsOversamplingDumpWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout(TRUE);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndView.UpdateWindow();
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpWnd::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (IsChild(pOldWnd)) GetParent()->SetFocus();
		else  m_wndView.SetFocus();
		return;
	}
	CDisplayWnd::OnSetFocus(pOldWnd);
}

BOOL CTCDiagnosticsOversamplingDumpWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSpeed;
	UINT  nLimit;
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	LOGFONT  fntTitle[2];
	LOGFONT  fntItems[2];
	LOGFONT  fntValues;
	COLORREF  nColor[2];
	CTimeSpan  tInterval;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CString  szFileName;
	CTCDiagnosticsOversamplingDumpLayout  cLayout;
	CTCDiagnosticsOversamplingDumpPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (SetMode(m_dlgOpen.GetMode()), SetType(MAKELONG(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, m_dlgOpen.GetType())), SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayout(cLayout);
			m_dlgOpen.GetLayoutSampleLimit(nLimit);
			m_dlgOpen.GetLayoutBadDataMode(bBadData);
			m_dlgOpen.GetLayoutToolTipMode(bToolTips);
			m_dlgOpen.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgOpen.GetLayoutGridBackgroundColors(nColor[0], nColor[1]);
			m_dlgOpen.GetLayoutListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntTitle[0]);
			m_dlgOpen.GetLayoutListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntTitle[1]);
			m_dlgOpen.GetLayoutListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntItems[0]);
			m_dlgOpen.GetLayoutListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntItems[1]);
			m_dlgOpen.GetLayoutListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntValues);
			if (!SetLayout(cLayout) || !SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntTitle[0]) || !SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntTitle[1]) || !SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntItems[0]) || !SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntItems[1]) || !SetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntValues) || !SetGridBackgroundColors(nColor[0], nColor[1]) || !SetSampleLimit(nLimit) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (!m_dlgOpen.IsLayoutModified())
		{
			m_dlgOpen.GetLayout(cLayout);
			if (!SetLayout(cLayout)) return FALSE;
		}
		if (m_dlgOpen.IsRetrievingModified())
		{
			m_dlgOpen.GetRetrieveFileName(szFileName);
			if (!SetRetrieveFileName(szFileName)) return FALSE;
		}
		if (m_dlgOpen.IsPrintingModified())
		{
			m_dlgOpen.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			UpdateAllPanes();
			UpdateData();
			return Start();
		}
		if (GetMode() == DISPLAY_MODE_HISTORY)
		{
			m_dlgOpen.GetRetrieveMode(nMode);
			m_dlgOpen.GetRetrieveSpeed(nSpeed);
			m_dlgOpen.GetRetrieveInterval(tInterval);
			m_dlgOpen.GetRetrieveStartTime(tStartTime);
			m_dlgOpen.GetRetrieveStopTime(tStopTime);
			SetRetrieveMode(nMode);
			SetRetrieveSpeed(nSpeed);
			SetRetrieveInterval(tInterval);
			SetRetrieveStartTime(tStartTime);
			SetRetrieveStopTime(tStopTime);
			UpdateAllPanes();
			UpdateData();
			return Start();
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::OnCloseSettingsDialog(UINT nCode)
{
	UINT  nLimit;
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	LOGFONT  fntTitle[2];
	LOGFONT  fntItems[2];
	LOGFONT  fntValues;
	COLORREF  nColor[2];
	CString  szFileName;
	CTCDiagnosticsOversamplingDumpLayout  cLayout;
	CTCDiagnosticsOversamplingDumpPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (GetLayout(cLayout); m_dlgSettings.IsLayoutModified(); )
		{
			m_dlgSettings.GetLayout(cLayout);
			m_dlgSettings.GetLayoutSampleLimit(nLimit);
			m_dlgSettings.GetLayoutBadDataMode(bBadData);
			m_dlgSettings.GetLayoutToolTipMode(bToolTips);
			m_dlgSettings.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgSettings.GetLayoutBackgroundColors(nColor[0], nColor[1]);
			m_dlgSettings.GetLayoutTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntTitle[0]);
			m_dlgSettings.GetLayoutTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntTitle[1]);
			m_dlgSettings.GetLayoutItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntItems[0]);
			m_dlgSettings.GetLayoutItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntItems[1]);
			m_dlgSettings.GetLayoutValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntValues);
			if (!SetLayout(cLayout) || !SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntTitle[0]) || !SetListTitleFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntTitle[1]) || !SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntItems[0]) || !SetListItemsFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA, &fntItems[1]) || !SetListValuesFont(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS, &fntValues) || !SetGridBackgroundColors(nColor[0], nColor[1]) || !SetSampleLimit(nLimit) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (m_dlgSettings.IsRetrievingModified())
		{
			m_dlgSettings.GetRetrieveFileName(szFileName);
			if (!SetRetrieveFileName(szFileName)) return FALSE;
		}
		if (m_dlgSettings.IsPrintingModified())
		{
			m_dlgSettings.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		UpdateData();
		UpdateAllPanes();
	}
	return TRUE;
}

BOOL CTCDiagnosticsOversamplingDumpWnd::OnCloseRetrieveDialog(UINT nCode)
{
	UINT  nMode[2];
	UINT  nSpeed[2];
	CTimeSpan  tInterval[2];
	CTimeKey  tStartTime[2];
	CTimeKey  tStopTime[2];

	if (nCode == IDOK)
	{
		nMode[0] = GetRetrieveMode();
		nSpeed[0] = GetRetrieveSpeed();
		tInterval[0] = GetRetrieveInterval();
		tStartTime[0] = GetRetrieveStartTime();
		tStopTime[0] = GetRetrieveStopTime();
		for (m_dlgRetrievals.GetMode(nMode[1]); nMode[1]; )
		{
			m_dlgRetrievals.GetSpeed(nSpeed[1]);
			m_dlgRetrievals.GetInterval(tInterval[1]);
			m_dlgRetrievals.GetStartTime(tStartTime[1]);
			m_dlgRetrievals.GetStopTime(tStopTime[1]);
			if (SetMode(DISPLAY_MODE_HISTORY) && (!IsRetrievingData() || StopRetrieveData()) && StartRetrieveData(nMode[1], nSpeed[1], tInterval[1], tStartTime[1], tStopTime[1]))
			{
				UpdateAllPanes();
				return TRUE;
			}
			SetMode((!nMode[0]) ? DISPLAY_MODE_REALTIME : DISPLAY_MODE_HISTORY);
			SetRetrieveMode(nMode[0]);
			SetRetrieveSpeed(nSpeed[0]);
			SetRetrieveInterval(tInterval[0]);
			SetRetrieveStartTime(tStartTime[0]);
			SetRetrieveStopTime(tStopTime[0]);
			UpdateAllPanes();
			return FALSE;
		}
		StopRetrieveData();
		SetRetrieveMode();
		SetRetrieveSpeed();
		SetRetrieveInterval();
		SetRetrieveStartTime();
		SetRetrieveStopTime();
		SetMode(DISPLAY_MODE_REALTIME);
		ProcessRealtimeData();
		UpdateAllPanes();
	}
	return TRUE;
}

void CTCDiagnosticsOversamplingDumpWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCDiagnosticsOversamplingDumpWnd::OnParameters()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgParameters.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCDiagnosticsOversamplingDumpWnd::OnClearAll()
{
	CHourglassCursor  cCursor;

	Reset();
}

void CTCDiagnosticsOversamplingDumpWnd::OnRetrievals()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTCDiagnosticsOversamplingDumpWnd::OnRetrieveStop()
{
	RetrieveMoreData(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED);
}

void CTCDiagnosticsOversamplingDumpWnd::OnRetrieveAutoForward()
{
	RetrieveMoreData(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD);
}

void CTCDiagnosticsOversamplingDumpWnd::OnRetrieveAutoBackward()
{
	RetrieveMoreData(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD);
}

void CTCDiagnosticsOversamplingDumpWnd::OnRetrieveManualForward()
{
	RetrieveMoreData(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD);
}

void CTCDiagnosticsOversamplingDumpWnd::OnRetrieveManualBackward()
{
	RetrieveMoreData(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD);
}

void CTCDiagnosticsOversamplingDumpWnd::OnRetrievePseudoRealtime()
{
	RetrieveMoreData(TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME);
}

void CTCDiagnosticsOversamplingDumpWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CTCDiagnosticsOversamplingDumpWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateParameters(CCmdUI *pCmdUI)
{
	CTCDiagnosticsOversamplingDumpLayout  cLayout;

	pCmdUI->Enable((IsInitialized() && GetLayout(cLayout) && cLayout.GetSize() > 0) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgParameters.GetSafeHwnd()));
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateClearAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetSampleCount(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS) + GetSampleCount(TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA) > 0) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetScope() == DISPLAY_SCOPE_LOCAL) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED)) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCDiagnosticsOversamplingDumpWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
