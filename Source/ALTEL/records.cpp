// RECORDS.CPP : Records Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the database records
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/02/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#define LIBRARYENVIRONMENT
#define ALTELENVIRONMENT

#include "ALTEL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseRecordset, CRecordset)

CALTELDatabaseRecordset::CALTELDatabaseRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CRecordset(pDatabaseEngine -> GetDBMS())
{
	//{{AFX_FIELD_INIT(CALTELDatabaseRecordset)
	m_nFields = 0;
	//}}AFX_FIELD_INIT

	m_pDatabaseEngine = pDatabaseEngine;
	m_bWarnings = TRUE;
	m_bErrors = TRUE;
	m_bIssues = FALSE;
}

BOOL CALTELDatabaseRecordset::Open(UINT nOpenType, LPCTSTR lpszSQL, DWORD dwOptions)
{
	return CRecordset::Open(nOpenType, lpszSQL, dwOptions);
}

VOID CALTELDatabaseRecordset::ShowError(LPCTSTR pszError)
{
	if (m_bErrors)
	{
		m_szNames[0].Add(EMPTYSTRING);
		m_szInfos[0].Add(EMPTYSTRING);
		m_szErrors.Add(pszError);
		m_nComponents[0].Add(0);
	}
	if (m_bIssues)
	{
		m_szIssues.Add(pszError);
		return;
	}
}
VOID CALTELDatabaseRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszError)
{
	if (m_bErrors)
	{
		m_szNames[0].Add(pszName);
		m_szInfos[0].Add(pszInfo);
		m_szErrors.Add(pszError);
		m_nComponents[0].Add(nComponent);
	}
	if (m_bIssues)
	{
		m_szIssues.Add(pszError);
		return;
	}
}

INT CALTELDatabaseRecordset::GetErrors(CStringArray &szErrors) CONST
{
	szErrors.Copy(m_szErrors);
	return((INT)szErrors.GetSize());
}
INT CALTELDatabaseRecordset::GetErrors(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szErrors) CONST
{
	szNames.Copy(m_szNames[0]);
	szInfos.Copy(m_szInfos[0]);
	szErrors.Copy(m_szErrors);
	nComponents.Copy(m_nComponents[0]);
	return((INT)szErrors.GetSize());
}

VOID CALTELDatabaseRecordset::EnableErrors(BOOL bEnable)
{
	m_bErrors = bEnable;
}

VOID CALTELDatabaseRecordset::EnableErrorsByStatus(INT nStatus)
{
	EnableErrors((nStatus == TMPACKET_RECORDSTATUS_NONE || nStatus == TMPACKET_RECORDSTATUS_NEW || nStatus == TMPACKET_RECORDSTATUS_CHANGED || nStatus == TCPACKET_RECORDSTATUS_NONE || nStatus == TCPACKET_RECORDSTATUS_NEW || nStatus == TCPACKET_RECORDSTATUS_CHANGED || nStatus == TMPARAMETER_RECORDSTATUS_NONE || nStatus == TMPARAMETER_RECORDSTATUS_NEW || nStatus == TMPARAMETER_RECORDSTATUS_CHANGED || nStatus == TMCALTABLE_RECORDSTATUS_NONE || nStatus == TMCALTABLE_RECORDSTATUS_NEW || nStatus == TMCALTABLE_RECORDSTATUS_CHANGED || nStatus == TMOOLTABLE_RECORDSTATUS_NONE || nStatus == TMOOLTABLE_RECORDSTATUS_NEW || nStatus == TMOOLTABLE_RECORDSTATUS_CHANGED || nStatus == TCPARAMETER_RECORDSTATUS_NONE || nStatus == TCPARAMETER_RECORDSTATUS_NEW || nStatus == TCPARAMETER_RECORDSTATUS_CHANGED || nStatus == TCCALTABLE_RECORDSTATUS_NONE || nStatus == TCCALTABLE_RECORDSTATUS_NEW || nStatus == TCCALTABLE_RECORDSTATUS_CHANGED || nStatus == TCOOLTABLE_RECORDSTATUS_NONE || nStatus == TCOOLTABLE_RECORDSTATUS_NEW || nStatus == TCOOLTABLE_RECORDSTATUS_CHANGED || nStatus == TCPARAMETERSET_RECORDSTATUS_NONE || nStatus == TCPARAMETERSET_RECORDSTATUS_NEW || nStatus == TCPARAMETERSET_RECORDSTATUS_CHANGED || nStatus == TCFUNCTION_RECORDSTATUS_NONE || nStatus == TCFUNCTION_RECORDSTATUS_NEW || nStatus == TCFUNCTION_RECORDSTATUS_CHANGED || nStatus == TCFUNCTIONBLOCK_RECORDSTATUS_NONE || nStatus == TCFUNCTIONBLOCK_RECORDSTATUS_NEW || nStatus == TCFUNCTIONBLOCK_RECORDSTATUS_CHANGED || nStatus == TCPREEXEGROUP_RECORDSTATUS_NONE || nStatus == TCPREEXEGROUP_RECORDSTATUS_NEW || nStatus == TCPREEXEGROUP_RECORDSTATUS_CHANGED || nStatus == TCEXEVERGROUP_RECORDSTATUS_NONE || nStatus == TCEXEVERGROUP_RECORDSTATUS_NEW || nStatus == TCEXEVERGROUP_RECORDSTATUS_CHANGED || nStatus == TCSEQUENCE_RECORDSTATUS_NONE || nStatus == TCSEQUENCE_RECORDSTATUS_NEW || nStatus == TCSEQUENCE_RECORDSTATUS_CHANGED || nStatus == OBPROCESSOR_RECORDSTATUS_NONE || nStatus == OBPROCESSOR_RECORDSTATUS_NEW || nStatus == OBPROCESSOR_RECORDSTATUS_CHANGED || nStatus == ANDLAYOUT_RECORDSTATUS_NONE || nStatus == ANDLAYOUT_RECORDSTATUS_NEW || nStatus == ANDLAYOUT_RECORDSTATUS_CHANGED || nStatus == GRDLAYOUT_RECORDSTATUS_NONE || nStatus == GRDLAYOUT_RECORDSTATUS_NEW || nStatus == GRDLAYOUT_RECORDSTATUS_CHANGED || nStatus == PODLAYOUT_RECORDSTATUS_NONE || nStatus == PODLAYOUT_RECORDSTATUS_NEW || nStatus == PODLAYOUT_RECORDSTATUS_CHANGED) ? TRUE : FALSE);
}

INT CALTELDatabaseRecordset::GetErrorCount() CONST
{
	return((INT)m_szErrors.GetSize());
}

VOID CALTELDatabaseRecordset::ResetErrors()
{
	m_szNames[0].RemoveAll();
	m_szInfos[0].RemoveAll();
	m_szErrors.RemoveAll();
	m_nComponents[0].RemoveAll();
}

VOID CALTELDatabaseRecordset::ShowWarning(LPCTSTR pszWarning)
{
	if (m_bWarnings)
	{
		m_szNames[1].Add(EMPTYSTRING);
		m_szInfos[1].Add(EMPTYSTRING);
		m_szWarnings.Add(pszWarning);
		m_nComponents[1].Add(0);
	}
	if (m_bIssues)
	{
		m_szIssues.Add(pszWarning);
		return;
	}
}
VOID CALTELDatabaseRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszWarning)
{
	if (m_bWarnings)
	{
		m_szNames[1].Add(pszName);
		m_szInfos[1].Add(pszInfo);
		m_szWarnings.Add(pszWarning);
		m_nComponents[1].Add(nComponent);
	}
	if (m_bIssues)
	{
		m_szIssues.Add(pszWarning);
		return;
	}
}

INT CALTELDatabaseRecordset::GetWarnings(CStringArray &szWarnings) CONST
{
	szWarnings.Copy(m_szWarnings);
	return((INT)szWarnings.GetSize());
}
INT CALTELDatabaseRecordset::GetWarnings(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szWarnings) CONST
{
	szNames.Copy(m_szNames[1]);
	szInfos.Copy(m_szInfos[1]);
	szWarnings.Copy(m_szWarnings);
	nComponents.Copy(m_nComponents[1]);
	return((INT)szWarnings.GetSize());
}

VOID CALTELDatabaseRecordset::EnableWarnings(BOOL bEnable)
{
	m_bWarnings = bEnable;
}

VOID CALTELDatabaseRecordset::EnableWarningsByStatus(INT nStatus)
{
	EnableWarnings((nStatus == TMPACKET_RECORDSTATUS_NONE || nStatus == TMPACKET_RECORDSTATUS_NEW || nStatus == TMPACKET_RECORDSTATUS_CHANGED || nStatus == TCPACKET_RECORDSTATUS_NONE || nStatus == TCPACKET_RECORDSTATUS_NEW || nStatus == TCPACKET_RECORDSTATUS_CHANGED || nStatus == TMPARAMETER_RECORDSTATUS_NONE || nStatus == TMPARAMETER_RECORDSTATUS_NEW || nStatus == TMPARAMETER_RECORDSTATUS_CHANGED || nStatus == TMCALTABLE_RECORDSTATUS_NONE || nStatus == TMCALTABLE_RECORDSTATUS_NEW || nStatus == TMCALTABLE_RECORDSTATUS_CHANGED || nStatus == TMOOLTABLE_RECORDSTATUS_NONE || nStatus == TMOOLTABLE_RECORDSTATUS_NEW || nStatus == TMOOLTABLE_RECORDSTATUS_CHANGED || nStatus == TCPARAMETER_RECORDSTATUS_NONE || nStatus == TCPARAMETER_RECORDSTATUS_NEW || nStatus == TCPARAMETER_RECORDSTATUS_CHANGED || nStatus == TCCALTABLE_RECORDSTATUS_NONE || nStatus == TCCALTABLE_RECORDSTATUS_NEW || nStatus == TCCALTABLE_RECORDSTATUS_CHANGED || nStatus == TCOOLTABLE_RECORDSTATUS_NONE || nStatus == TCOOLTABLE_RECORDSTATUS_NEW || nStatus == TCOOLTABLE_RECORDSTATUS_CHANGED || nStatus == TCPARAMETERSET_RECORDSTATUS_NONE || nStatus == TCPARAMETERSET_RECORDSTATUS_NEW || nStatus == TCPARAMETERSET_RECORDSTATUS_CHANGED || nStatus == TCFUNCTION_RECORDSTATUS_NONE || nStatus == TCFUNCTION_RECORDSTATUS_NEW || nStatus == TCFUNCTION_RECORDSTATUS_CHANGED || nStatus == TCFUNCTIONBLOCK_RECORDSTATUS_NONE || nStatus == TCFUNCTIONBLOCK_RECORDSTATUS_NEW || nStatus == TCFUNCTIONBLOCK_RECORDSTATUS_CHANGED || nStatus == TCPREEXEGROUP_RECORDSTATUS_NONE || nStatus == TCPREEXEGROUP_RECORDSTATUS_NEW || nStatus == TCPREEXEGROUP_RECORDSTATUS_CHANGED || nStatus == TCEXEVERGROUP_RECORDSTATUS_NONE || nStatus == TCEXEVERGROUP_RECORDSTATUS_NEW || nStatus == TCEXEVERGROUP_RECORDSTATUS_CHANGED || nStatus == TCSEQUENCE_RECORDSTATUS_NONE || nStatus == TCSEQUENCE_RECORDSTATUS_NEW || nStatus == TCSEQUENCE_RECORDSTATUS_CHANGED || nStatus == OBPROCESSOR_RECORDSTATUS_NONE || nStatus == OBPROCESSOR_RECORDSTATUS_NEW || nStatus == OBPROCESSOR_RECORDSTATUS_CHANGED || nStatus == ANDLAYOUT_RECORDSTATUS_NONE || nStatus == ANDLAYOUT_RECORDSTATUS_NEW || nStatus == ANDLAYOUT_RECORDSTATUS_CHANGED || nStatus == GRDLAYOUT_RECORDSTATUS_NONE || nStatus == GRDLAYOUT_RECORDSTATUS_NEW || nStatus == GRDLAYOUT_RECORDSTATUS_CHANGED || nStatus == PODLAYOUT_RECORDSTATUS_NONE || nStatus == PODLAYOUT_RECORDSTATUS_NEW || nStatus == PODLAYOUT_RECORDSTATUS_CHANGED) ? TRUE : FALSE);
}

INT CALTELDatabaseRecordset::GetWarningCount() CONST
{
	return((INT)m_szWarnings.GetSize());
}

VOID CALTELDatabaseRecordset::ResetWarnings()
{
	m_szNames[1].RemoveAll();
	m_szInfos[1].RemoveAll();
	m_szWarnings.RemoveAll();
	m_nComponents[1].RemoveAll();
}

VOID CALTELDatabaseRecordset::CollectIssues(BOOL bEnable)
{
	m_bIssues = bEnable;
	m_szIssues.RemoveAll();
}
INT CALTELDatabaseRecordset::CollectIssues(CStringArray &szIssues, BOOL bStop)
{
	for (szIssues.RemoveAll(); m_bIssues; )
	{
		for (szIssues.Copy(m_szIssues); bStop; )
		{
			m_szIssues.RemoveAll();
			m_bIssues = FALSE;
			break;
		}
		break;
	}
	return((INT)szIssues.GetSize());
}

BOOL CALTELDatabaseRecordset::IsCollectingIssues() CONST
{
	return m_bIssues;
}

CString CALTELDatabaseRecordset::ConstructFieldName(LPCTSTR pszField) CONST
{
	CString  szName;

	szName.Format(STRING(IDS_DATABASE_TABLE_FIELD_FORMAT), pszField);
	return szName;
}

CString CALTELDatabaseRecordset::ExtractText(LPCTSTR pszField) CONST
{
	CString  szText(pszField);

	return szText.Trim();
}

CONST CDatabaseEngine *CALTELDatabaseRecordset::GetDatabaseEngine() CONST
{
	return m_pDatabaseEngine;
}

void CALTELDatabaseRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CIdle  cIdle;

	//{{AFX_FIELD_MAP(CALTELDatabaseRecordset)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_FIELD_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMPacketsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMPacketsRecordset::CALTELDatabaseTMPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMPacketsRecordset)
	m_szTag.Empty();
	m_szType.Empty();
	m_szDescription.Empty();
	m_szDetails.Empty();
	m_szAPID.Empty();
	m_szTMID.Empty();
	m_szTMType.Empty();
	m_sz3Disc.Empty();
	m_szDataFieldHeader.Empty();
	m_szEventIDParameter.Empty();
	m_szTransmissionRetries.Empty();
	m_szStatus.Empty();
	m_bDataFieldHeader = 0;
	m_nTransmissionRate = 0;
	m_nVirtualChannel = 0;
	m_nDataSize = 0;
	m_bDataSize = 0;
	m_nFields = 17;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMPacketsRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTMPacketsRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTMPacketsRecordset::SetType(INT nType)
{
	m_szType = GetDatabaseEngine()->TranslateTMPacketType(nType);
}

INT CALTELDatabaseTMPacketsRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketType(m_szType);
}

VOID CALTELDatabaseTMPacketsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTMPacketsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTMPacketsRecordset::SetDetails(LPCTSTR pszDetails)
{
	m_szDetails = pszDetails;
}

CString CALTELDatabaseTMPacketsRecordset::GetDetails() CONST
{
	return m_szDetails;
}

VOID CALTELDatabaseTMPacketsRecordset::SetDataFieldHeader(LPCTSTR pszHeader)
{
	m_szDataFieldHeader = pszHeader;
	m_bDataFieldHeader = (lstrlen(pszHeader) > 0) ? TRUE : FALSE;
}

CString CALTELDatabaseTMPacketsRecordset::GetDataFieldHeader() CONST
{
	return m_szDataFieldHeader;
}

BOOL CALTELDatabaseTMPacketsRecordset::HasDataFieldHeader() CONST
{
	return m_bDataFieldHeader;
}

VOID CALTELDatabaseTMPacketsRecordset::SetAPID(INT nAPID)
{
	m_szAPID = GetDatabaseEngine()->TranslateTMPacketAPID(nAPID);
}

INT CALTELDatabaseTMPacketsRecordset::GetAPID() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketAPID(m_szAPID);
}

VOID CALTELDatabaseTMPacketsRecordset::SetTMID(INT nTMID)
{
	m_szTMID = GetDatabaseEngine()->TranslateTMPacketTMID(nTMID);
}

INT CALTELDatabaseTMPacketsRecordset::GetTMID() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketTMID(m_szTMID);
}

VOID CALTELDatabaseTMPacketsRecordset::SetTMType(INT nTMType)
{
	m_szTMType = GetDatabaseEngine()->TranslateTMPacketTMType(nTMType);
}

INT CALTELDatabaseTMPacketsRecordset::GetTMType() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketTMType(m_szTMType);
}

VOID CALTELDatabaseTMPacketsRecordset::Set3Disc(INT n3Disc)
{
	m_sz3Disc = GetDatabaseEngine()->TranslateTMPacket3Disc(n3Disc);
}

INT CALTELDatabaseTMPacketsRecordset::Get3Disc() CONST
{
	return GetDatabaseEngine()->TranslateTMPacket3Disc(m_sz3Disc);
}

VOID CALTELDatabaseTMPacketsRecordset::SetDataSize(INT nSize)
{
	m_bDataSize = ((m_nDataSize = nSize) <= 0) ? ((!nSize) ? TMPACKET_LENGTH_VARIABLE : -1) : TMPACKET_LENGTH_FIXED;
}

INT CALTELDatabaseTMPacketsRecordset::GetDataSize() CONST
{
	return((m_bDataSize != TMPACKET_LENGTH_FIXED) ? ((m_bDataSize == TMPACKET_LENGTH_VARIABLE) ? 0 : -1) : m_nDataSize);
}

VOID CALTELDatabaseTMPacketsRecordset::SetTransmissionRate(INT nRate)
{
	m_nTransmissionRate = nRate;
}

INT CALTELDatabaseTMPacketsRecordset::GetTransmissionRate() CONST
{
	return m_nTransmissionRate;
}

VOID CALTELDatabaseTMPacketsRecordset::SetTransmissionRetries(INT nRetries)
{
	m_szTransmissionRetries = GetDatabaseEngine()->TranslateTMPacketTransmissionRetries(nRetries);
}

INT CALTELDatabaseTMPacketsRecordset::GetTransmissionRetries() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketTransmissionRetries(m_szTransmissionRetries);
}

VOID CALTELDatabaseTMPacketsRecordset::SetVirtualChannel(INT nChannel)
{
	m_nVirtualChannel = nChannel;
}

INT CALTELDatabaseTMPacketsRecordset::GetVirtualChannel() CONST
{
	return m_nVirtualChannel;
}

VOID CALTELDatabaseTMPacketsRecordset::SetEventIDParameter(LPCTSTR pszTag)
{
	m_szEventIDParameter = pszTag;
}

CString CALTELDatabaseTMPacketsRecordset::GetEventIDParameter() CONST
{
	return m_szEventIDParameter;
}

VOID CALTELDatabaseTMPacketsRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTMPacketStatus(nStatus);
}

INT CALTELDatabaseTMPacketsRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketStatus(m_szStatus);
}

VOID CALTELDatabaseTMPacketsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szTag), pszError);
}
VOID CALTELDatabaseTMPacketsRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CDatabaseTMPacket  *pDatabaseTMPacket;

	EnableErrorsByStatus(((pDatabaseTMPacket = GetDatabaseEngine()->GetTMPackets()->GetAt(GetDatabaseEngine()->GetTMPackets()->Find(pszTag)))) ? pDatabaseTMPacket->GetStatus() : TMPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMPacketsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szTag), pszWarning);
}
VOID CALTELDatabaseTMPacketsRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CDatabaseTMPacket  *pDatabaseTMPacket;

	EnableWarningsByStatus(((pDatabaseTMPacket = GetDatabaseEngine()->GetTMPackets()->GetAt(GetDatabaseEngine()->GetTMPackets()->Find(pszTag)))) ? pDatabaseTMPacket->GetStatus() : TMPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMPacketsRecordset::Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket)
{
	SetType(TMPACKET_TYPE);
	SetTag(pDatabaseTMPacket->GetTag());
	SetDescription(pDatabaseTMPacket->GetDescription());
	SetDetails(pDatabaseTMPacket->GetDetails());
	SetDataFieldHeader(pDatabaseTMPacket->GetDataFieldHeader());
	SetAPID(pDatabaseTMPacket->GetAPID());
	SetTMID(pDatabaseTMPacket->GetTMID());
	SetTMType(pDatabaseTMPacket->GetTMType());
	Set3Disc(pDatabaseTMPacket->Get3Disc());
	SetDataSize(pDatabaseTMPacket->GetDataSize());
	SetTransmissionRate(pDatabaseTMPacket->GetTransmissionRate());
	SetTransmissionRetries(pDatabaseTMPacket->GetTransmissionRetries());
	SetVirtualChannel(pDatabaseTMPacket->GetVirtualChannel());
	SetEventIDParameter(pDatabaseTMPacket->GetEventIDParameter());
	SetStatus(pDatabaseTMPacket->GetStatus());
}

BOOL CALTELDatabaseTMPacketsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMPacketsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = (GetStatus() == TMPACKET_RECORDSTATUS_NONE || GetStatus() == TMPACKET_RECORDSTATUS_NEW || GetStatus() == TMPACKET_RECORDSTATUS_CHANGED)));
		CheckType(bStatus);
		CheckDescription(bStatus);
		CheckDetails(bStatus);
		CheckAPID(bStatus);
		CheckTMID(bStatus);
		CheckTMType(bStatus);
		Check3Disc(bStatus);
		CheckDataSize(bStatus);
		CheckTransmissionRate(bStatus);
		CheckTransmissionRetries(bStatus);
		CheckVirtualChannel(bStatus);
		CheckDataFieldHeaderName(bStatus);
		CheckDataFieldHeaderFlag(bStatus);
		CheckEventIDParameter(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckAPID(IsCollectingIssues());
		bCheck &= CheckTMType(IsCollectingIssues());
		bCheck &= CheckDataSize(IsCollectingIssues());
		bCheck &= CheckVirtualChannel(IsCollectingIssues());
		bCheck &= CheckDataFieldHeaderName(IsCollectingIssues());
		bCheck &= CheckDataFieldHeaderFlag(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALTAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketType(GetType()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALTYPE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALDESCRIPTION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckDetails(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDetails((m_szDetails = ExtractText(m_szDetails))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALDETAILS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketAPID(GetTag(), GetAPID()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALAPID), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckTMID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTMID(GetTMID()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALTMID), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckTMType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTMType(GetTMType()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALTMTYPE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::Check3Disc(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacket3Disc(Get3Disc()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGAL3DISC), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckDataSize(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDataSize(GetDataSize(), m_bDataSize))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALDATASIZE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckTransmissionRate(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTransmissionRate(GetTMType(), GetTransmissionRate()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALTRANSMISSIONRATE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckTransmissionRetries(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTransmissionRetries(GetTransmissionRetries()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALTRANSMISSIONRETRIES), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckVirtualChannel(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketVirtualChannel((GetDatabaseEngine()->CheckTMPacketAPID(GetTag(), GetAPID())) ? GetAPID() : -1, GetVirtualChannel()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALVIRTUALCHANNEL), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckDataFieldHeaderName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDataFieldHeaderName((m_szDataFieldHeader = ExtractText(m_szDataFieldHeader))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALDATAFIELDHEADERNAME), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckDataFieldHeaderFlag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDataFieldHeader(m_bDataFieldHeader))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALDATAFIELDHEADERFLAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckEventIDParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketEventID((m_szEventIDParameter = ExtractText(m_szEventIDParameter))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALEVENTID), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketsRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALSTATUS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMPacketsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMPacketsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_PACKID)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_HFLG)), m_bDataFieldHeader);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_APID)), m_szAPID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_LENG)), m_nDataSize);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_TMTY)), m_szTMType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_TMID)), m_szTMID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_FUNC)), m_szDetails);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_SMPRT)), m_nTransmissionRate);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_VALID)), m_szTransmissionRetries);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_VARIABLE)), m_bDataSize);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_3VAL)), m_sz3Disc);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_STATUS)), m_szStatus);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_DFH_NAME)), m_szDataFieldHeader);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_VCID)), m_nVirtualChannel);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PMF_EVENTID)), m_szEventIDParameter);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketHeadersRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMPacketHeadersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMPacketHeadersRecordset::CALTELDatabaseTMPacketHeadersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMPacketHeadersRecordset)
	m_szName.Empty();
	m_bTMType = 0;
	m_nTMTypePos[0] = 0;
	m_nTMTypePos[1] = 0;
	m_bTMID = 0;
	m_nTMIDPos[0] = 0;
	m_nTMIDPos[1] = 0;
	m_b3Disc = 0;
	m_n3DiscPos[0] = 0;
	m_n3DiscPos[1] = 0;
	m_bTimestamp = 0;
	m_nTimestampPos[0] = 0;
	m_nTimestampPos[1] = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMPacketHeadersRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMPacketHeadersRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMPacketHeadersRecordset::SetTMTypePosition(INT nByte, INT nBit, INT nLength)
{
	m_nTMTypePos[0] = 8 * nByte + nBit;
	m_nTMTypePos[1] = nLength;
	m_bTMType = (nLength > 0) ? TRUE : FALSE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::GetTMTypePosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	if (m_bTMType)
	{
		nByte = m_nTMTypePos[0] / 8;
		nBit = m_nTMTypePos[0] % 8;
		nLength = m_nTMTypePos[1];
		return TRUE;
	}
	nByte = nBit = nLength = 0;
	return FALSE;
}

VOID CALTELDatabaseTMPacketHeadersRecordset::SetTMIDPosition(INT nByte, INT nBit, INT nLength)
{
	m_nTMIDPos[0] = 8 * nByte + nBit;
	m_nTMIDPos[1] = nLength;
	m_bTMID = (nLength > 0) ? TRUE : FALSE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::GetTMIDPosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	if (m_bTMID)
	{
		nByte = m_nTMIDPos[0] / 8;
		nBit = m_nTMIDPos[0] % 8;
		nLength = m_nTMIDPos[1];
		return TRUE;
	}
	nByte = nBit = nLength = 0;
	return FALSE;
}

VOID CALTELDatabaseTMPacketHeadersRecordset::Set3DiscPosition(INT nByte, INT nBit, INT nLength)
{
	m_n3DiscPos[0] = 8 * nByte + nBit;
	m_n3DiscPos[1] = nLength;
	m_b3Disc = (nLength > 0) ? TRUE : FALSE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::Get3DiscPosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	if (m_b3Disc)
	{
		nByte = m_n3DiscPos[0] / 8;
		nBit = m_n3DiscPos[0] % 8;
		nLength = m_n3DiscPos[1];
		return TRUE;
	}
	nByte = nBit = nLength = 0;
	return FALSE;
}

VOID CALTELDatabaseTMPacketHeadersRecordset::SetTimestampPosition(INT nByte, INT nBit, INT nLength)
{
	m_nTimestampPos[0] = 8 * nByte + nBit;
	m_nTimestampPos[1] = nLength;
	m_bTimestamp = (nLength > 0) ? TRUE : FALSE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::GetTimestampPosition(INT &nByte, INT &nBit, INT &nLength) CONST
{
	if (m_bTimestamp)
	{
		nByte = m_nTimestampPos[0] / 8;
		nBit = m_nTimestampPos[0] % 8;
		nLength = m_nTimestampPos[1];
		return TRUE;
	}
	nByte = nBit = nLength = 0;
	return FALSE;
}

VOID CALTELDatabaseTMPacketHeadersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMPacketHeadersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER, pszError);
}

VOID CALTELDatabaseTMPacketHeadersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMPacketHeadersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER, pszWarning);
}

VOID CALTELDatabaseTMPacketHeadersRecordset::Translate(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader)
{
	INT  nBit;
	INT  nByte;
	INT  nLength;

	SetName(pDatabaseTMPacketHeader->GetName());
	if (pDatabaseTMPacketHeader->GetTMTypePosition(nByte, nBit, nLength) >= 0) SetTMTypePosition(nByte, nBit, nLength);
	if (pDatabaseTMPacketHeader->GetTMIDPosition(nByte, nBit, nLength) >= 0) SetTMIDPosition(nByte, nBit, nLength);
	if (pDatabaseTMPacketHeader->Get3DiscPosition(nByte, nBit, nLength) >= 0) Set3DiscPosition(nByte, nBit, nLength);
	if (pDatabaseTMPacketHeader->GetTimestampPosition(nByte, nBit, nLength) >= 0) SetTimestampPosition(nByte, nBit, nLength);
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMPacketHeadersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName(TRUE);
		CheckTMTypePosition(TRUE);
		CheckTMIDPosition(TRUE);
		Check3DiscPosition(TRUE);
		CheckTimestampPosition(TRUE);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckTMTypePosition(IsCollectingIssues());
		bCheck &= CheckTMIDPosition(IsCollectingIssues());
		bCheck &= Check3DiscPosition(IsCollectingIssues());
		bCheck &= CheckTimestampPosition(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketHeaderName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::CheckTMTypePosition(BOOL bStatus)
{
	INT  nBit;
	INT  nByte;
	INT  nLength;
	CString  szMessage;

	if (GetTMTypePosition(nByte, nBit, nLength) && !GetDatabaseEngine()->CheckTMPacketHeaderTMTypePosition(nByte, nBit, nLength))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTMTYPEPOSITION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::CheckTMIDPosition(BOOL bStatus)
{
	INT  nBit;
	INT  nByte;
	INT  nLength;
	CString  szMessage;

	if (GetTMIDPosition(nByte, nBit, nLength) && !GetDatabaseEngine()->CheckTMPacketHeaderTMIDPosition(nByte, nBit, nLength))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTMIDPOSITION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::Check3DiscPosition(BOOL bStatus)
{
	INT  nBit;
	INT  nByte;
	INT  nLength;
	CString  szMessage;

	if (Get3DiscPosition(nByte, nBit, nLength) && !GetDatabaseEngine()->CheckTMPacketHeader3DiscPosition(nByte, nBit, nLength))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGAL3DISCPOSITION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketHeadersRecordset::CheckTimestampPosition(BOOL bStatus)
{
	INT  nBit;
	INT  nByte;
	INT  nLength;
	CString  szMessage;

	if (GetTimestampPosition(nByte, nBit, nLength) && !GetDatabaseEngine()->CheckTMPacketHeaderTimestampPosition(nByte, nBit, nLength))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTIMESTAMPPOSITION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMPacketHeadersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMPacketHeadersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TM_TYPE_PRESENT)), m_bTMType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TM_TYPE_BIT_OFFSET)), m_nTMTypePos[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TM_TYPE_BIT_LENGTH)), m_nTMTypePos[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TM_ID_PRESENT)), m_bTMID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TM_ID_BIT_OFFSET)), m_nTMIDPos[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TM_ID_BIT_LENGTH)), m_nTMIDPos[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_3DISC_PRESENT)), m_b3Disc);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_3DISC_BIT_OFFSET)), m_n3DiscPos[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_3DISC_BIT_LENGTH)), m_n3DiscPos[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TIME_PRESENT)), m_bTimestamp);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TIME_BIT_OFFSET)), m_nTimestampPos[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DFH_TIME_BIT_LENGTH)), m_nTimestampPos[1]);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketParametersRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMPacketParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMPacketParametersRecordset::CALTELDatabaseTMPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMPacketParametersRecordset)
	m_szTag.Empty();
	m_szPacket.Empty();
	m_szParameter.Empty();
	m_nBytePos = 0;
	m_nBitPos = 0;
	m_nGroupCount = 0;
	m_nGroupInterval = 0;
	m_nOccurrenceCount = 0;
	m_nOccurrenceInterval = 0;
	m_nTime[0] = 0;
	m_nTime[1] = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMPacketParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTMPacketParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTMPacketParametersRecordset::SetPacket(LPCTSTR pszTag)
{
	m_szPacket = pszTag;
}

CString CALTELDatabaseTMPacketParametersRecordset::GetPacket() CONST
{
	return m_szPacket;
}

VOID CALTELDatabaseTMPacketParametersRecordset::SetValidityParameter(LPCTSTR pszTag)
{
	m_szParameter = pszTag;
}

CString CALTELDatabaseTMPacketParametersRecordset::GetValidityParameter() CONST
{
	return m_szParameter;
}

VOID CALTELDatabaseTMPacketParametersRecordset::SetBytePos(INT nByte)
{
	m_nBytePos = nByte;
}

INT CALTELDatabaseTMPacketParametersRecordset::GetBytePos() CONST
{
	return m_nBytePos;
}

VOID CALTELDatabaseTMPacketParametersRecordset::SetBitPos(INT nBit)
{
	m_nBitPos = nBit;
}

INT CALTELDatabaseTMPacketParametersRecordset::GetBitPos() CONST
{
	return m_nBitPos;
}

VOID CALTELDatabaseTMPacketParametersRecordset::SetOccurrenceCount(INT nCount)
{
	m_nOccurrenceCount = nCount;
}

INT CALTELDatabaseTMPacketParametersRecordset::GetOccurrenceCount() CONST
{
	return m_nOccurrenceCount;
}

VOID CALTELDatabaseTMPacketParametersRecordset::SetOccurrenceInterval(INT nInterval)
{
	m_nOccurrenceInterval = nInterval;
}

INT CALTELDatabaseTMPacketParametersRecordset::GetOccurrenceInterval() CONST
{
	return m_nOccurrenceInterval;
}

VOID CALTELDatabaseTMPacketParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szPacket), pszError);
}
VOID CALTELDatabaseTMPacketParametersRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CDatabaseTMPacket  *pDatabaseTMPacket;

	EnableErrorsByStatus(((pDatabaseTMPacket = GetDatabaseEngine()->GetTMPackets()->GetAt(GetDatabaseEngine()->GetTMPackets()->Find(pszTag)))) ? pDatabaseTMPacket->GetStatus() : TMPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMPacketParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szPacket), pszWarning);
}
VOID CALTELDatabaseTMPacketParametersRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CDatabaseTMPacket  *pDatabaseTMPacket;

	EnableWarningsByStatus(((pDatabaseTMPacket = GetDatabaseEngine()->GetTMPackets()->GetAt(GetDatabaseEngine()->GetTMPackets()->Find(pszTag)))) ? pDatabaseTMPacket->GetStatus() : TMPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTMPacketParametersRecordset::Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter)
{
	SetTag(pDatabaseTMPacketParameter->GetTag());
	SetPacket(pDatabaseTMPacket->GetTag());
	SetBytePos(pDatabaseTMPacketParameter->GetBytePos());
	SetBitPos(pDatabaseTMPacketParameter->GetBitPos());
	SetOccurrenceCount(pDatabaseTMPacketParameter->GetOccurrenceCount());
	SetOccurrenceInterval(pDatabaseTMPacketParameter->GetOccurrenceInterval());
	SetValidityParameter(pDatabaseTMPacketParameter->GetValidityParameter());
	return((!pDatabaseTMPacketParameter->GetTag().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTMPacketParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMPacketParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = ((pDatabaseTMPacket = GetDatabaseEngine()->GetTMPackets()->GetAt(GetDatabaseEngine()->GetTMPackets()->Find(GetPacket())))) ? (pDatabaseTMPacket->GetStatus() == TMPACKET_RECORDSTATUS_NONE || pDatabaseTMPacket->GetStatus() == TMPACKET_RECORDSTATUS_NEW || pDatabaseTMPacket->GetStatus() == TMPACKET_RECORDSTATUS_CHANGED) : TRUE));
		CheckPacket(bStatus);
		CheckValidityParameter(bStatus);
		CheckBytePos(bStatus);
		CheckBitPos(bStatus);
		CheckOccurrenceCount(bStatus);
		CheckOccurrenceInterval(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckPacket(IsCollectingIssues());
		bCheck &= CheckBytePos(IsCollectingIssues());
		bCheck &= CheckBitPos(IsCollectingIssues());
		bCheck &= CheckOccurrenceCount(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALTAG), (LPCTSTR)GetPacket(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketParametersRecordset::CheckPacket(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTag((m_szPacket = ExtractText(m_szPacket))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALPACKETTAG), (LPCTSTR)GetPacket(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketParametersRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterValidity((m_szParameter = ExtractText(m_szParameter))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetPacket(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketParametersRecordset::CheckBytePos(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterBytePosition(GetBytePos()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALBYTEPOSITION), (LPCTSTR)GetPacket(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketParametersRecordset::CheckBitPos(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterBitPosition(GetBitPos()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALBITPOSITION), (LPCTSTR)GetPacket(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketParametersRecordset::CheckOccurrenceCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOccurrenceCount(GetOccurrenceCount()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALOCCURRENCECOUNT), (LPCTSTR)GetPacket(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketParametersRecordset::CheckOccurrenceInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOccurrenceInterval(GetOccurrenceCount(), GetOccurrenceInterval()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALOCCURRENCEINTERVAL), (LPCTSTR)GetPacket(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMPacketParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMPacketParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_NAME)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_PACKID)), m_szPacket);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_OFFBY)), m_nBytePos);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_OFFBI)), m_nBitPos);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_NBOCC)), m_nOccurrenceCount);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_NBGRP)), m_nGroupCount);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_LGOCC)), m_nOccurrenceInterval);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_LGGRP)), m_nGroupInterval);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_TIME)), m_nTime[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_TDOCC)), m_nTime[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_VALID)), m_szParameter);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketStreamsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMPacketStreamsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMPacketStreamsRecordset::CALTELDatabaseTMPacketStreamsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMPacketStreamsRecordset)
	m_szName.Empty();
	m_szAPID.Empty();
	m_szTMID.Empty();
	m_szValidityParameter.Empty();
	m_nPeriod = 0;
	m_nTimeout = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMPacketStreamsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMPacketStreamsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMPacketStreamsRecordset::SetAPID(INT nAPID)
{
	m_szAPID = GetDatabaseEngine()->TranslateTMPacketStreamAPID(nAPID);
}

INT CALTELDatabaseTMPacketStreamsRecordset::GetAPID() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketStreamAPID(m_szAPID);
}

VOID CALTELDatabaseTMPacketStreamsRecordset::SetTMID(INT nTMID)
{
	m_szTMID = GetDatabaseEngine()->TranslateTMPacketStreamTMID(nTMID);
}

INT CALTELDatabaseTMPacketStreamsRecordset::GetTMID() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketStreamTMID(m_szTMID);
}

VOID CALTELDatabaseTMPacketStreamsRecordset::SetPeriod(INT nPeriod)
{
	m_nPeriod = nPeriod;
}

INT CALTELDatabaseTMPacketStreamsRecordset::GetPeriod() CONST
{
	return m_nPeriod;
}

VOID CALTELDatabaseTMPacketStreamsRecordset::SetTimeout(INT nTimeout)
{
	m_nTimeout = nTimeout;
}

INT CALTELDatabaseTMPacketStreamsRecordset::GetTimeout() CONST
{
	return m_nTimeout;
}

VOID CALTELDatabaseTMPacketStreamsRecordset::SetValidityParameter(LPCTSTR pszTag)
{
	m_szValidityParameter = pszTag;
}

CString CALTELDatabaseTMPacketStreamsRecordset::GetValidityParameter() CONST
{
	return m_szValidityParameter;
}

VOID CALTELDatabaseTMPacketStreamsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMPacketStreamsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM, pszError);
}

VOID CALTELDatabaseTMPacketStreamsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMPacketStreamsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM, pszWarning);
}

VOID CALTELDatabaseTMPacketStreamsRecordset::Translate(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream)
{
	SetName(pDatabaseTMPacketStream->GetName());
	SetAPID(pDatabaseTMPacketStream->GetAPID());
	SetTMID(pDatabaseTMPacketStream->GetTMID());
	SetPeriod(pDatabaseTMPacketStream->GetPeriod());
	SetTimeout(pDatabaseTMPacketStream->GetTimeout());
	SetValidityParameter(pDatabaseTMPacketStream->GetValidityParameter());
}

BOOL CALTELDatabaseTMPacketStreamsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMPacketStreamsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName(TRUE);
		CheckAPID(TRUE);
		CheckTMID(TRUE);
		CheckPeriod(TRUE);
		CheckTimeout(TRUE);
		CheckValidityParameter(TRUE);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAPID(IsCollectingIssues());
		bCheck &= CheckPeriod(IsCollectingIssues());
		bCheck &= CheckTimeout(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketStreamsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketStreamsRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamAPID(GetAPID()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALAPID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketStreamsRecordset::CheckTMID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamTMID(GetTMID()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALTMID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketStreamsRecordset::CheckPeriod(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamPeriod(GetPeriod()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALPERIOD), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketStreamsRecordset::CheckTimeout(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamTimeout(GetTimeout()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALTIMEOUT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMPacketStreamsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamValidityParameter((m_szValidityParameter = ExtractText(m_szValidityParameter))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMPacketStreamsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMPacketStreamsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_STR_STID)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_STR_APID)), m_szAPID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_STR_TMID)), m_szTMID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_STR_PERIOD)), m_nPeriod);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_STR_TIMEOUT)), m_nTimeout);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_STR_VALID)), m_szValidityParameter);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPacketsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCPacketsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCPacketsRecordset::CALTELDatabaseTCPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCPacketsRecordset)
	m_szTag.Empty();
	m_szType.Empty();
	m_szDescription.Empty();
	m_szDetails[0].Empty();
	m_szDetails[1].Empty();
	m_szAPID.Empty();
	m_szStatus.Empty();
	m_bDataFieldHeader = 0;
	m_nDataSize = 0;
	m_bDataSize = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCPacketsRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTCPacketsRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTCPacketsRecordset::SetType(INT nType)
{
	m_szType = GetDatabaseEngine()->TranslateTCPacketType(nType);
}

INT CALTELDatabaseTCPacketsRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateTCPacketType(m_szType);
}

VOID CALTELDatabaseTCPacketsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCPacketsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCPacketsRecordset::SetDetails(LPCTSTR pszDetails)
{
	CString  szDetails[2];

	for (szDetails[0] = szDetails[1] = pszDetails; szDetails[0].GetLength() > GetDatabaseEngine()->GetTCPacketDetailsLength(); )
	{
		szDetails[0] = szDetails[0].Left(GetDatabaseEngine()->GetTCPacketDetailsLength());
		szDetails[1] = szDetails[1].Mid(GetDatabaseEngine()->GetTCPacketDetailsLength());
		break;
	}
	m_szDetails[0] = szDetails[0];
	m_szDetails[1] = (lstrlen(pszDetails) > GetDatabaseEngine()->GetTCPacketDetailsLength()) ? szDetails[1] : EMPTYSTRING;
}

CString CALTELDatabaseTCPacketsRecordset::GetDetails() CONST
{
	return m_szDetails[0] + m_szDetails[1];
}

VOID CALTELDatabaseTCPacketsRecordset::SetDataFieldHeaderFlag(BOOL bFlag)
{
	m_bDataFieldHeader = bFlag;
}

BOOL CALTELDatabaseTCPacketsRecordset::GetDataFieldHeaderFlag() CONST
{
	return((m_bDataFieldHeader) ? TRUE : FALSE);
}

VOID CALTELDatabaseTCPacketsRecordset::SetAPID(INT nAPID)
{
	m_szAPID = GetDatabaseEngine()->TranslateTCPacketAPID(nAPID);
}

INT CALTELDatabaseTCPacketsRecordset::GetAPID() CONST
{
	return GetDatabaseEngine()->TranslateTCPacketAPID(m_szAPID);
}

VOID CALTELDatabaseTCPacketsRecordset::SetDataSize(INT nSize)
{
	m_bDataSize = ((m_nDataSize = nSize) <= 0) ? ((!nSize) ? TCPACKET_LENGTH_VARIABLE : -1) : TCPACKET_LENGTH_FIXED;
}

INT CALTELDatabaseTCPacketsRecordset::GetDataSize() CONST
{
	return((m_bDataSize != TCPACKET_LENGTH_FIXED) ? ((m_bDataSize == TCPACKET_LENGTH_VARIABLE) ? 0 : -1) : m_nDataSize);
}

VOID CALTELDatabaseTCPacketsRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCPacketStatus(nStatus);
}

INT CALTELDatabaseTCPacketsRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCPacketStatus(m_szStatus);
}

VOID CALTELDatabaseTCPacketsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szTag), pszError);
}
VOID CALTELDatabaseTCPacketsRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CDatabaseTCPacket  *pDatabaseTCPacket;

	EnableErrorsByStatus(((pDatabaseTCPacket = GetDatabaseEngine()->GetTCPackets()->GetAt(GetDatabaseEngine()->GetTCPackets()->Find(pszTag)))) ? pDatabaseTCPacket->GetStatus() : TCPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCPacketsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szTag), pszWarning);
}
VOID CALTELDatabaseTCPacketsRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CDatabaseTCPacket  *pDatabaseTCPacket;

	EnableWarningsByStatus(((pDatabaseTCPacket = GetDatabaseEngine()->GetTCPackets()->GetAt(GetDatabaseEngine()->GetTCPackets()->Find(pszTag)))) ? pDatabaseTCPacket->GetStatus() : TCPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCPacketsRecordset::Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket)
{
	SetType(TCPACKET_TYPE);
	SetTag(pDatabaseTCPacket->GetTag());
	SetDescription(pDatabaseTCPacket->GetDescription());
	SetDetails(pDatabaseTCPacket->GetDetails());
	SetAPID(pDatabaseTCPacket->GetAPID());
	SetDataSize(pDatabaseTCPacket->GetDataSize());
	SetDataFieldHeaderFlag(pDatabaseTCPacket->GetDataFieldHeaderFlag());
	SetStatus(pDatabaseTCPacket->GetStatus());
}

BOOL CALTELDatabaseTCPacketsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCPacketsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = (GetStatus() == TCPACKET_RECORDSTATUS_NONE || GetStatus() == TCPACKET_RECORDSTATUS_NEW || GetStatus() == TCPACKET_RECORDSTATUS_CHANGED)));
		CheckType(bStatus);
		CheckDescription(bStatus);
		CheckDetails(bStatus);
		CheckAPID(bStatus);
		CheckDataSize(bStatus);
		CheckDataFieldHeaderFlag(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckAPID(IsCollectingIssues());
		bCheck &= CheckDataSize(IsCollectingIssues());
		bCheck &= CheckDataFieldHeaderFlag(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALTAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketType(GetType()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALTYPE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALDESCRIPTION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckDetails(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketDetails((m_szDetails[0] = ExtractText(m_szDetails[0]))) || !GetDatabaseEngine()->CheckTCPacketDetails((m_szDetails[1] = ExtractText(m_szDetails[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALDETAILS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketAPID(GetAPID()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALAPID), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckDataSize(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketDataSize(0, m_bDataSize, GetDataSize()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALDATASIZE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckDataFieldHeaderFlag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketDataFieldHeader(m_bDataFieldHeader))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALDATAFIELDHEADERFLAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketsRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALSTATUS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCPacketsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCPacketsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_PACKID)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_HFLG)), m_bDataFieldHeader);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_APID)), m_szAPID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_LENG)), m_nDataSize);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_FUNC)), m_szDetails[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_FUNC2)), m_szDetails[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_STATUS)), m_szStatus);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_VARIABLE)), m_bDataSize);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPacketParametersRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCPacketParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCPacketParametersRecordset::CALTELDatabaseTCPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCPacketParametersRecordset)
	m_szTag.Empty();
	m_szPacket.Empty();
	m_szDescription.Empty();
	m_szType.Empty();
	m_szFlag.Empty();
	m_szRadix.Empty();
	m_szCoding.Empty();
	m_szConstValue.Empty();
	m_nBitOffset = 0;
	m_nBitWidth = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCPacketParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTCPacketParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTCPacketParametersRecordset::SetPacket(LPCTSTR pszTag)
{
	m_szPacket = pszTag;
}

CString CALTELDatabaseTCPacketParametersRecordset::GetPacket() CONST
{
	return m_szPacket;
}

VOID CALTELDatabaseTCPacketParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCPacketParametersRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCPacketParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCPacketParameterType(nAttributes);
	m_szFlag = GetDatabaseEngine()->TranslateTCPacketParameterValueInterpretation(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCPacketParameterValueRadix(nAttributes);
	m_szCoding = GetDatabaseEngine()->TranslateTCPacketParameterValueCoding(nAttributes);
}

ULONGLONG CALTELDatabaseTCPacketParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCPacketParameterType(m_szType) | GetDatabaseEngine()->TranslateTCPacketParameterValueInterpretation(m_szFlag) | GetDatabaseEngine()->TranslateTCPacketParameterValueRadix(m_szRadix) | GetDatabaseEngine()->TranslateTCPacketParameterValueCoding(m_szCoding);
}

VOID CALTELDatabaseTCPacketParametersRecordset::SetBitOffset(INT nOffset)
{
	m_nBitOffset = nOffset;
}

INT CALTELDatabaseTCPacketParametersRecordset::GetBitOffset() CONST
{
	return m_nBitOffset;
}

VOID CALTELDatabaseTCPacketParametersRecordset::SetBitWidth(INT nWidth)
{
	m_nBitWidth = nWidth;
}

INT CALTELDatabaseTCPacketParametersRecordset::GetBitWidth() CONST
{
	return m_nBitWidth;
}

VOID CALTELDatabaseTCPacketParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szConstValue = pszConstValue;
}

CString CALTELDatabaseTCPacketParametersRecordset::GetConstValue() CONST
{
	return m_szConstValue;
}

VOID CALTELDatabaseTCPacketParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szPacket), pszError);
}
VOID CALTELDatabaseTCPacketParametersRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CDatabaseTCPacket  *pDatabaseTCPacket;

	EnableErrorsByStatus(((pDatabaseTCPacket = GetDatabaseEngine()->GetTCPackets()->GetAt(GetDatabaseEngine()->GetTCPackets()->Find(pszTag)))) ? pDatabaseTCPacket->GetStatus() : TCPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCPacketParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szPacket), pszWarning);
}
VOID CALTELDatabaseTCPacketParametersRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CDatabaseTCPacket  *pDatabaseTCPacket;

	EnableWarningsByStatus(((pDatabaseTCPacket = GetDatabaseEngine()->GetTCPackets()->GetAt(GetDatabaseEngine()->GetTCPackets()->Find(pszTag)))) ? pDatabaseTCPacket->GetStatus() : TCPACKET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCPacketParametersRecordset::Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter)
{
	SetTag(pDatabaseTCPacketParameter->GetTag());
	SetPacket(pDatabaseTCPacket->GetTag());
	SetDescription(pDatabaseTCPacketParameter->GetDescription());
	SetAttributes(pDatabaseTCPacketParameter->GetAttributes());
	SetBitWidth(pDatabaseTCPacketParameter->GetWidth());
	SetBitOffset((pDatabaseTCPacketParameter->GetBytePos() >= 0 && pDatabaseTCPacketParameter->GetBitPos() >= 0) ? (8 * pDatabaseTCPacketParameter->GetBytePos() + pDatabaseTCPacketParameter->GetBitPos()) : -1);
	SetConstValue(pDatabaseTCPacketParameter->GetConstValueAsText());
	return((pDatabaseTCPacketParameter->GetAttributes() & (TCPACKETPARAMETER_TYPE_VARIABLE | TCPACKETPARAMETER_TYPE_FIXED)) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTCPacketParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCPacketParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCPacket  *pDatabaseTCPacket;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = ((pDatabaseTCPacket = GetDatabaseEngine()->GetTCPackets()->GetAt(GetDatabaseEngine()->GetTCPackets()->Find(GetPacket())))) ? (pDatabaseTCPacket->GetStatus() == TCPACKET_RECORDSTATUS_NONE || pDatabaseTCPacket->GetStatus() == TCPACKET_RECORDSTATUS_NEW || pDatabaseTCPacket->GetStatus() == TCPACKET_RECORDSTATUS_CHANGED) : TRUE));
		CheckPacket(bStatus);
		CheckDescription(bStatus);
		CheckAttributes(bStatus);
		CheckCoding(bStatus);
		CheckBitOffset(bStatus);
		CheckBitWidth(bStatus);
		CheckConstValue(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckPacket(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckBitOffset(IsCollectingIssues());
		bCheck &= CheckBitWidth(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALTAG), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckPacket(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketTag((m_szPacket = ExtractText(m_szPacket))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALPACKETTAG), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALDESCRIPTION), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterType(m_szTag, GetDatabaseEngine()->TranslateTCPacketParameterType((m_szType = ExtractText(m_szType)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALTYPE), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCPacketParameterValueInterpretation(GetAttributes(), GetDatabaseEngine()->TranslateTCPacketParameterValueInterpretation((m_szFlag = ExtractText(m_szFlag)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALFLAG), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCPacketParameterValueRadix(GetAttributes(), GetDatabaseEngine()->TranslateTCPacketParameterValueRadix((m_szRadix = ExtractText(m_szRadix)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALRADIX), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckCoding(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterValueCoding(GetAttributes(), GetDatabaseEngine()->TranslateTCPacketParameterValueCoding((m_szCoding = ExtractText(m_szCoding)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALCODING), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckBitOffset(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterValueBitOffset(GetBitOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALBITOFFSET), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckBitWidth(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterValueBitWidth(GetBitWidth()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALBITWIDTH), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPacketParametersRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (lstrlen((m_szConstValue = ExtractText(m_szConstValue))) > GetDatabaseEngine()->GetTCPacketParameterConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALCONSTVALUE), (LPCTSTR)GetPacket(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCPacketParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCPacketParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_CNAME)), m_szPacket);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_ELTYPE)), m_szType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_ELLEN)), m_nBitWidth);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_BITOFF)), m_nBitOffset);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_PNAME)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_VTYPE)), m_szFlag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_VALUE)), m_szConstValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_RADIX)), m_szRadix);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_CODING)), m_szCoding);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCFunctionsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCFunctionsRecordset::CALTELDatabaseTCFunctionsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCFunctionsRecordset)
	m_szName.Empty();
	m_szType.Empty();
	m_szTCType.Empty();
	m_szDetails.Empty();
	m_szDescription[0].Empty();
	m_szDescription[1].Empty();
	m_szDescription[2].Empty();
	m_szTCPacket.Empty();
	m_szTCID.Empty();
	m_szSubSystem[0].Empty();
	m_szSubSystem[1].Empty();
	m_szEquipment[0].Empty();
	m_szEquipment[1].Empty();
	m_szOperationalInfo.Empty();
	m_szValidityConditions.Empty();
	m_szAssociatedTelecommands.Empty();
	m_szComplementaryTelecommands.Empty();
	m_szDestinationSubSchedule.Empty();
	m_szMissionPlannerEvent.Empty();
	m_szVerifGroup[0].Empty();
	m_szVerifGroup[1].Empty();
	m_szStatus.Empty();
	m_nFields = 23;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCFunctionsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCFunctionsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription[0] = pszDescription;
}

CString CALTELDatabaseTCFunctionsRecordset::GetDescription() CONST
{
	return m_szDescription[0];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetExtendedDescription(LPCTSTR pszDescription)
{
	CString  szDescription[2];

	for (szDescription[0] = szDescription[1] = pszDescription; szDescription[0].GetLength() > GetDatabaseEngine()->GetTCFunctionExtendedDescriptionLength(); )
	{
		szDescription[0] = szDescription[0].Left(GetDatabaseEngine()->GetTCFunctionExtendedDescriptionLength());
		szDescription[1] = szDescription[1].Mid(GetDatabaseEngine()->GetTCFunctionExtendedDescriptionLength());
		break;
	}
	m_szDescription[1] = szDescription[0];
	m_szDescription[2] = (lstrlen(pszDescription) > GetDatabaseEngine()->GetTCFunctionExtendedDescriptionLength()) ? szDescription[1] : EMPTYSTRING;
}

CString CALTELDatabaseTCFunctionsRecordset::GetExtendedDescription() CONST
{
	return m_szDescription[1] + m_szDescription[2];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetDetails(LPCTSTR pszDetails)
{
	m_szDetails = pszDetails;
}

CString CALTELDatabaseTCFunctionsRecordset::GetDetails() CONST
{
	return m_szDetails;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCFunctionType(nAttributes);
	m_szTCType = GetDatabaseEngine()->TranslateTCFunctionTCType(nAttributes);
	m_szHazFlag = GetDatabaseEngine()->TranslateTCFunctionHazardousFlag(nAttributes);
}

ULONGLONG CALTELDatabaseTCFunctionsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionType(m_szType) | GetDatabaseEngine()->TranslateTCFunctionTCType(m_szTCType) | GetDatabaseEngine()->TranslateTCFunctionHazardousFlag(m_szHazFlag);
}

VOID CALTELDatabaseTCFunctionsRecordset::SetTCPacket(LPCTSTR pszTag)
{
	m_szTCPacket = pszTag;
}

CString CALTELDatabaseTCFunctionsRecordset::GetTCPacket() CONST
{
	return m_szTCPacket;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetTCID(INT nTCID)
{
	m_szTCID = GetDatabaseEngine()->TranslateTCFunctionTCID(nTCID);
}

INT CALTELDatabaseTCFunctionsRecordset::GetTCID() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionTCID(m_szTCID);
}

VOID CALTELDatabaseTCFunctionsRecordset::SetDestinationSubSystem(LPCTSTR pszSubSystem)
{
	m_szSubSystem[0] = pszSubSystem;
}

CString CALTELDatabaseTCFunctionsRecordset::GetDestinationSubSystem() CONST
{
	return m_szSubSystem[0];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetDestinationSubSchedule(LPCTSTR pszSubSchedule)
{
	m_szDestinationSubSchedule = pszSubSchedule;
}

CString CALTELDatabaseTCFunctionsRecordset::GetDestinationSubSchedule() CONST
{
	return m_szDestinationSubSchedule;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetDestinationEquipment(LPCTSTR pszEquipment)
{
	m_szEquipment[0] = pszEquipment;
}

CString CALTELDatabaseTCFunctionsRecordset::GetDestinationEquipment() CONST
{
	return m_szEquipment[0];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetRouterSubSystem(LPCTSTR pszSubSystem)
{
	m_szSubSystem[1] = pszSubSystem;
}

CString CALTELDatabaseTCFunctionsRecordset::GetRouterSubSystem() CONST
{
	return m_szSubSystem[1];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetRouterEquipment(LPCTSTR pszEquipment)
{
	m_szEquipment[1] = pszEquipment;
}

CString CALTELDatabaseTCFunctionsRecordset::GetRouterEquipment() CONST
{
	return m_szEquipment[1];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetOperationalInfo(LPCTSTR pszInfo)
{
	m_szOperationalInfo = pszInfo;
}

CString CALTELDatabaseTCFunctionsRecordset::GetOperationalInfo() CONST
{
	return m_szOperationalInfo;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetValidityConditions(LPCTSTR pszConditions)
{
	m_szValidityConditions = pszConditions;
}

CString CALTELDatabaseTCFunctionsRecordset::GetValidityConditions() CONST
{
	return m_szValidityConditions;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetAssociatedTelecommands(LPCTSTR pszTelecommands)
{
	m_szAssociatedTelecommands = pszTelecommands;
}

CString CALTELDatabaseTCFunctionsRecordset::GetAssociatedTelecommands() CONST
{
	return m_szAssociatedTelecommands;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetComplementaryTelecommands(LPCTSTR pszTelecommands)
{
	m_szComplementaryTelecommands = pszTelecommands;
}

CString CALTELDatabaseTCFunctionsRecordset::GetComplementaryTelecommands() CONST
{
	return m_szComplementaryTelecommands;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetMissionPlannerEvent(LPCTSTR pszEvent)
{
	m_szMissionPlannerEvent = pszEvent;
}

CString CALTELDatabaseTCFunctionsRecordset::GetMissionPlannerEvent() CONST
{
	return m_szMissionPlannerEvent;
}

VOID CALTELDatabaseTCFunctionsRecordset::SetPreExeGroup(LPCTSTR pszGroup)
{
	m_szVerifGroup[1] = pszGroup;
}

CString CALTELDatabaseTCFunctionsRecordset::GetPreExeGroup() CONST
{
	return m_szVerifGroup[1];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetExeVerGroup(LPCTSTR pszGroup)
{
	m_szVerifGroup[0] = pszGroup;
}

CString CALTELDatabaseTCFunctionsRecordset::GetExeVerGroup() CONST
{
	return m_szVerifGroup[0];
}

VOID CALTELDatabaseTCFunctionsRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCFunctionStatus(nStatus);
}

INT CALTELDatabaseTCFunctionsRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionStatus(m_szStatus);
}

VOID CALTELDatabaseTCFunctionsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCFunctionsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCFunction  *pDatabaseTCFunction;

	EnableErrorsByStatus(((pDatabaseTCFunction = GetDatabaseEngine()->GetTCFunctions()->GetAt(GetDatabaseEngine()->GetTCFunctions()->Find(pszName)))) ? pDatabaseTCFunction->GetStatus() : TCFUNCTION_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCFunctionsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCFunctionsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCFunction  *pDatabaseTCFunction;

	EnableWarningsByStatus(((pDatabaseTCFunction = GetDatabaseEngine()->GetTCFunctions()->GetAt(GetDatabaseEngine()->GetTCFunctions()->Find(pszName)))) ? pDatabaseTCFunction->GetStatus() : TCFUNCTION_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCFunctionsRecordset::Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction)
{
	SetName(pDatabaseTCFunction->GetName());
	SetDescription(pDatabaseTCFunction->GetDescription());
	SetExtendedDescription(pDatabaseTCFunction->GetExtendedDescription());
	SetDetails(pDatabaseTCFunction->GetDetails());
	SetAttributes(pDatabaseTCFunction->GetAttributes());
	SetTCPacket(pDatabaseTCFunction->GetTCPacket());
	SetTCID(pDatabaseTCFunction->GetTCID());
	SetDestinationSubSystem(pDatabaseTCFunction->GetDestinationSubSystem());
	SetDestinationSubSchedule(pDatabaseTCFunction->GetDestinationSubSchedule());
	SetDestinationEquipment(pDatabaseTCFunction->GetDestinationEquipment());
	SetRouterSubSystem(pDatabaseTCFunction->GetRouterSubSystem());
	SetRouterEquipment(pDatabaseTCFunction->GetRouterEquipment());
	SetOperationalInfo(pDatabaseTCFunction->GetOperationalInfo());
	SetValidityConditions(pDatabaseTCFunction->GetValidityConditions());
	SetAssociatedTelecommands(pDatabaseTCFunction->GetAssociatedTelecommands());
	SetComplementaryTelecommands(pDatabaseTCFunction->GetComplementaryTelecommands());
	SetMissionPlannerEvent(pDatabaseTCFunction->GetMissionPlannerEvent());
	SetPreExeGroup(pDatabaseTCFunction->GetPreExeGroup());
	SetExeVerGroup(pDatabaseTCFunction->GetExeVerGroup());
	SetStatus(pDatabaseTCFunction->GetStatus());
}

BOOL CALTELDatabaseTCFunctionsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCFunctionsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TCFUNCTION_RECORDSTATUS_NONE || GetStatus() == TCFUNCTION_RECORDSTATUS_NEW || GetStatus() == TCFUNCTION_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckExtendedDescription(bStatus);
		CheckDetails(bStatus);
		CheckAttributes(bStatus);
		CheckTCPacket(bStatus);
		CheckTCID(bStatus);
		CheckDestinationSubSystem(bStatus);
		CheckDestinationSubSchedule(bStatus);
		CheckDestinationEquipment(bStatus);
		CheckRouterSubSystem(bStatus);
		CheckRouterEquipment(bStatus);
		CheckOperationalInfo(bStatus);
		CheckValidityConditions(bStatus);
		CheckAssociatedTelecommands(bStatus);
		CheckComplementaryTelecommands(bStatus);
		CheckMissionPlannerEvent(bStatus);
		CheckPreExeGroup(bStatus);
		CheckExeVerGroup(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckTCPacket(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDescription((m_szDescription[0] = ExtractText(m_szDescription[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckExtendedDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionExtendedDescription((m_szDescription[1] = ExtractText(m_szDescription[1]))) || !GetDatabaseEngine()->CheckTCFunctionExtendedDescription((m_szDescription[2] = ExtractText(m_szDescription[2]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALEXTENDEDDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckDetails(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDetails((m_szDetails = ExtractText(m_szDetails))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALDETAILS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCFunctionType((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionTCType(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALTCTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionHazardousFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALHAZFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckTCPacket(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionPacketTag((m_szTCPacket = ExtractText(m_szTCPacket))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALTCPACKET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckTCID(BOOL bStatus)
{
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckDestinationSubSystem(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDestinationSubSystem((m_szSubSystem[0] = ExtractText(m_szSubSystem[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALDESTINATIONSUBSYSTEM), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckDestinationSubSchedule(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDestinationSubSchedule((m_szDestinationSubSchedule = ExtractText(m_szDestinationSubSchedule))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALDESTINATIONSUBSCHEDULE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckDestinationEquipment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDestinationEquipment((m_szEquipment[0] = ExtractText(m_szEquipment[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALDESTINATIONEQUIPMENT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckRouterSubSystem(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionRouterSubSystem((m_szSubSystem[1] = ExtractText(m_szSubSystem[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALREOUTERSUBSYSTEM), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckRouterEquipment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionRouterEquipment((m_szEquipment[1] = ExtractText(m_szEquipment[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALROUTEREQUIPMENT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckOperationalInfo(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionOperationalInfo((m_szOperationalInfo = ExtractText(m_szOperationalInfo))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALOPERATIONALINFO), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckValidityConditions(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionValidityConditions((m_szValidityConditions = ExtractText(m_szValidityConditions))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALVALIDITYCONDITIONS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckAssociatedTelecommands(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionAssociatedTelecommands((m_szAssociatedTelecommands = ExtractText(m_szAssociatedTelecommands))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALASSOCIATEDTELECOMMANDS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckComplementaryTelecommands(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionComplementaryTelecommands((m_szComplementaryTelecommands = ExtractText(m_szComplementaryTelecommands))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALCOMPLEMENTARYTELECOMMANDS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckMissionPlannerEvent(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionMissionPlannerEvent((m_szMissionPlannerEvent = ExtractText(m_szMissionPlannerEvent))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALMISSIONPLANNEREVENT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckPreExeGroup(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionPreExeGroup((m_szVerifGroup[1] = ExtractText(m_szVerifGroup[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALPREEXEGROUP), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckExeVerGroup(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionExeVerGroup((m_szVerifGroup[0] = ExtractText(m_szVerifGroup[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALEXEVERGROUP), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionsRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCFunctionsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCFunctionsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_CNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_DESCR)), m_szDescription[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_CTYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_TCPID)), m_szTCPacket);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_ADD)), m_szTCID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_LDESC)), m_szDetails);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_DESS)), m_szSubSystem[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_DEUN)), m_szEquipment[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_ROUTS)), m_szSubSystem[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_ROUTU)), m_szEquipment[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_OPINFO)), m_szOperationalInfo);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_VALID)), m_szValidityConditions);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_FUNC1)), m_szDescription[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_FUNC2)), m_szDescription[2]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_ALTC)), m_szAssociatedTelecommands);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_CMPTC)), m_szComplementaryTelecommands);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_SSCH)), m_szDestinationSubSchedule);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_TCTYPE)), m_szTCType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_HAZ)), m_szHazFlag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_COSEV)), m_szMissionPlannerEvent);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_CVPID)), m_szVerifGroup[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_PVPID)), m_szVerifGroup[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionElementsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCFunctionElementsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCFunctionElementsRecordset::CALTELDatabaseTCFunctionElementsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCFunctionElementsRecordset)
	m_szName.Empty();
	m_szFunction.Empty();
	m_szDescription.Empty();
	m_szType.Empty();
	m_szFlag.Empty();
	m_szRadix.Empty();
	m_szConstValue.Empty();
	m_nBitOffset = 0;
	m_nBitWidth = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCFunctionElementsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCFunctionElementsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCFunctionElementsRecordset::SetFunction(LPCTSTR pszFunction)
{
	m_szFunction = pszFunction;
}

CString CALTELDatabaseTCFunctionElementsRecordset::GetFunction() CONST
{
	return m_szFunction;
}

VOID CALTELDatabaseTCFunctionElementsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCFunctionElementsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCFunctionElementsRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCFunctionElementType(nAttributes);
	m_szFlag = GetDatabaseEngine()->TranslateTCFunctionElementValueInterpretation(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCFunctionElementValueRadix(nAttributes);
}

ULONGLONG CALTELDatabaseTCFunctionElementsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionElementType(m_szType) | GetDatabaseEngine()->TranslateTCFunctionElementValueInterpretation(m_szFlag) | GetDatabaseEngine()->TranslateTCFunctionElementValueRadix(m_szRadix);
}

VOID CALTELDatabaseTCFunctionElementsRecordset::SetBitOffset(INT nOffset)
{
	m_nBitOffset = nOffset;
}

INT CALTELDatabaseTCFunctionElementsRecordset::GetBitOffset() CONST
{
	return m_nBitOffset;
}

VOID CALTELDatabaseTCFunctionElementsRecordset::SetBitWidth(INT nWidth)
{
	m_nBitWidth = nWidth;
}

INT CALTELDatabaseTCFunctionElementsRecordset::GetBitWidth() CONST
{
	return m_nBitWidth;
}

VOID CALTELDatabaseTCFunctionElementsRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szConstValue = pszConstValue;
}

CString CALTELDatabaseTCFunctionElementsRecordset::GetConstValue() CONST
{
	return m_szConstValue;
}

VOID CALTELDatabaseTCFunctionElementsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szFunction), pszError);
}
VOID CALTELDatabaseTCFunctionElementsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCFunction  *pDatabaseTCFunction;

	EnableErrorsByStatus(((pDatabaseTCFunction = GetDatabaseEngine()->GetTCFunctions()->GetAt(GetDatabaseEngine()->GetTCFunctions()->Find(pszName)))) ? pDatabaseTCFunction->GetStatus() : TCFUNCTION_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCFunctionElementsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szFunction), pszWarning);
}
VOID CALTELDatabaseTCFunctionElementsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCFunction  *pDatabaseTCFunction;

	EnableWarningsByStatus(((pDatabaseTCFunction = GetDatabaseEngine()->GetTCFunctions()->GetAt(GetDatabaseEngine()->GetTCFunctions()->Find(pszName)))) ? pDatabaseTCFunction->GetStatus() : TCFUNCTION_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement)
{
	SetName(pDatabaseTCFunctionElement->GetName());
	SetFunction(pDatabaseTCFunction->GetName());
	SetDescription(pDatabaseTCFunctionElement->GetDescription());
	SetAttributes(pDatabaseTCFunctionElement->GetAttributes());
	SetBitWidth(pDatabaseTCFunctionElement->GetWidth());
	SetBitOffset((pDatabaseTCFunctionElement->GetBytePos() >= 0 && pDatabaseTCFunctionElement->GetBitPos() >= 0) ? (8 * pDatabaseTCFunctionElement->GetBytePos() + pDatabaseTCFunctionElement->GetBitPos()) : -1);
	SetConstValue(pDatabaseTCFunctionElement->GetConstValueAsText());
	return((pDatabaseTCFunctionElement->GetAttributes() & (TCFUNCTIONELEMENT_TYPE_PARAMETER | TCFUNCTIONELEMENT_TYPE_CONSTANT)) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCFunctionElementsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCFunction  *pDatabaseTCFunction;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTCFunction = GetDatabaseEngine()->GetTCFunctions()->GetAt(GetDatabaseEngine()->GetTCFunctions()->Find(GetFunction())))) ? (pDatabaseTCFunction->GetStatus() == TCFUNCTION_RECORDSTATUS_NONE || pDatabaseTCFunction->GetStatus() == TCFUNCTION_RECORDSTATUS_NEW || pDatabaseTCFunction->GetStatus() == TCFUNCTION_RECORDSTATUS_CHANGED) : TRUE));
		CheckFunction(bStatus);
		CheckDescription(bStatus);
		CheckAttributes(bStatus);
		CheckBitOffset(bStatus);
		CheckBitWidth(bStatus);
		CheckConstValue(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckFunction(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckBitOffset(IsCollectingIssues());
		bCheck &= CheckBitWidth(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALNAME), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::CheckFunction(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionName((m_szFunction = ExtractText(m_szFunction))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALFUNCTIONNAME), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALDESCRIPTION), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementType(m_szName, GetDatabaseEngine()->TranslateTCFunctionElementType((m_szType = ExtractText(m_szType)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALTYPE), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionElementValueInterpretation(GetAttributes(), GetDatabaseEngine()->TranslateTCFunctionElementValueInterpretation((m_szFlag = ExtractText(m_szFlag)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALFLAG), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionElementValueRadix(GetAttributes(), GetDatabaseEngine()->TranslateTCFunctionElementValueRadix((m_szRadix = ExtractText(m_szRadix)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALRADIX), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::CheckBitOffset(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementValueBitOffset(GetBitOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALBITOFFSET), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::CheckBitWidth(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementValueBitWidth(GetBitWidth()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALBITWIDTH), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionElementsRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (lstrlen((m_szConstValue = ExtractText(m_szConstValue))) > GetDatabaseEngine()->GetTCFunctionElementConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALCONSTVALUE), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCFunctionElementsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCFunctionElementsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_CNAME)), m_szFunction);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_ELTYPE)), m_szType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_ELLEN)), m_nBitWidth);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_BITOFF)), m_nBitOffset);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_PNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_VTYPE)), m_szFlag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_VALUE)), m_szConstValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_RADIX)), m_szRadix);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionBlocksRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCFunctionBlocksRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCFunctionBlocksRecordset::CALTELDatabaseTCFunctionBlocksRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCFunctionBlocksRecordset)
	m_szName.Empty();
	m_szInterpretation.Empty();
	m_nByteOffset = 0;
	m_nMaxLength = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCFunctionBlocksRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCFunctionBlocksRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCFunctionBlocksRecordset::SetAttributes(UINT nAttributes)
{
	m_szInterpretation = GetDatabaseEngine()->TranslateTCFunctionBlockInterpretation(nAttributes);
}

UINT CALTELDatabaseTCFunctionBlocksRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionBlockInterpretation(m_szInterpretation);
}

VOID CALTELDatabaseTCFunctionBlocksRecordset::SetByteOffset(INT nOffset)
{
	m_nByteOffset = nOffset;
}

INT CALTELDatabaseTCFunctionBlocksRecordset::GetByteOffset() CONST
{
	return m_nByteOffset;
}

VOID CALTELDatabaseTCFunctionBlocksRecordset::SetMaxLength(INT nLength)
{
	m_nMaxLength = nLength;
}

INT CALTELDatabaseTCFunctionBlocksRecordset::GetMaxLength() CONST
{
	return m_nMaxLength;
}

VOID CALTELDatabaseTCFunctionBlocksRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCFunctionBlockStatus(nStatus);
}

INT CALTELDatabaseTCFunctionBlocksRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionBlockStatus(m_szStatus);
}

VOID CALTELDatabaseTCFunctionBlocksRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCFunctionBlocksRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;

	EnableErrorsByStatus(((pDatabaseTCFunctionBlock = GetDatabaseEngine()->GetTCFunctionBlocks()->GetAt(GetDatabaseEngine()->GetTCFunctionBlocks()->Find(pszName)))) ? pDatabaseTCFunctionBlock->GetStatus() : TCFUNCTIONBLOCK_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCFunctionBlocksRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCFunctionBlocksRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;

	EnableWarningsByStatus(((pDatabaseTCFunctionBlock = GetDatabaseEngine()->GetTCFunctionBlocks()->GetAt(GetDatabaseEngine()->GetTCFunctionBlocks()->Find(pszName)))) ? pDatabaseTCFunctionBlock->GetStatus() : TCFUNCTIONBLOCK_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCFunctionBlocksRecordset::Translate(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, UINT nType)
{
	INT  nOffset;
	INT  nLength;

	for (SetName(pDatabaseTCFunctionBlock->GetName()), SetAttributes(nType), SetStatus(pDatabaseTCFunctionBlock->GetStatus()); pDatabaseTCFunctionBlock->GetLocation(nType, nOffset, nLength); )
	{
		SetByteOffset(nOffset);
		SetMaxLength(nLength);
		return TRUE;
	}
	return FALSE;
}

BOOL CALTELDatabaseTCFunctionBlocksRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCFunctionBlocksRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TCFUNCTIONBLOCK_RECORDSTATUS_NONE || GetStatus() == TCFUNCTIONBLOCK_RECORDSTATUS_NEW || GetStatus() == TCFUNCTIONBLOCK_RECORDSTATUS_CHANGED)));
		CheckAttributes(bStatus);
		CheckByteOffset(bStatus);
		CheckMaxLength(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckByteOffset(IsCollectingIssues());
		bCheck &= CheckMaxLength(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlocksRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionBlockName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCK_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szInterpretation)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlocksRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionBlockInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCK_ILLEGALINTERPRETATION), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szInterpretation)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlocksRecordset::CheckByteOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionBlockByteOffset(m_nByteOffset))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCK_ILLEGALBYTEOFFSET), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szInterpretation)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlocksRecordset::CheckMaxLength(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionBlockMaxLength(m_nMaxLength))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCK_ILLEGALMAXLENGTH), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szInterpretation)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlocksRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionBlockStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCK_ILLEGALSTATUS), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szInterpretation)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCFunctionBlocksRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCFunctionBlocksRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_BCF_CNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_BCF_INTER)), m_szInterpretation);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_BCF_MAXLEN)), m_nMaxLength);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_BCF_BYTEOFF)), m_nByteOffset);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionBlockElementsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCFunctionBlockElementsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCFunctionBlockElementsRecordset::CALTELDatabaseTCFunctionBlockElementsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCFunctionBlockElementsRecordset)
	m_szName.Empty();
	m_szFunction.Empty();
	m_szInterpretation.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCFunctionBlockElementsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCFunctionBlockElementsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCFunctionBlockElementsRecordset::SetFunction(LPCTSTR pszFunction)
{
	m_szFunction = pszFunction;
}

CString CALTELDatabaseTCFunctionBlockElementsRecordset::GetFunction() CONST
{
	return m_szFunction;
}

VOID CALTELDatabaseTCFunctionBlockElementsRecordset::SetAttributes(UINT nAttributes)
{
	m_szInterpretation = GetDatabaseEngine()->TranslateTCFunctionBlockElementInterpretation(nAttributes);
}

UINT CALTELDatabaseTCFunctionBlockElementsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionBlockElementInterpretation(m_szInterpretation);
}

VOID CALTELDatabaseTCFunctionBlockElementsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCFunctionBlockElementsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;

	EnableErrorsByStatus(((pDatabaseTCFunctionBlock = GetDatabaseEngine()->GetTCFunctionBlocks()->GetAt(GetDatabaseEngine()->GetTCFunctionBlocks()->Find(pszName)))) ? pDatabaseTCFunctionBlock->GetStatus() : TCFUNCTIONBLOCK_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCFunctionBlockElementsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCFunctionBlockElementsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;

	EnableWarningsByStatus(((pDatabaseTCFunctionBlock = GetDatabaseEngine()->GetTCFunctionBlocks()->GetAt(GetDatabaseEngine()->GetTCFunctionBlocks()->Find(pszName)))) ? pDatabaseTCFunctionBlock->GetStatus() : TCFUNCTIONBLOCK_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCFunctionBlockElementsRecordset::Translate(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, CONST CDatabaseTCFunctionBlockElement *pDatabaseTCFunctionBlockElement)
{
	SetName(pDatabaseTCFunctionBlockElement->GetName());
	SetFunction(pDatabaseTCFunctionBlock->GetName());
	SetAttributes(pDatabaseTCFunctionBlockElement->GetAttributes());
	return((!pDatabaseTCFunctionBlockElement->GetName().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTCFunctionBlockElementsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCFunctionBlockElementsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName(TRUE);
		CheckFunction(TRUE);
		CheckAttributes(TRUE);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckFunction(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlockElementsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionBlockElementName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCKELEMENT_ILLEGALNAME), (LPCTSTR)GetFunction(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlockElementsRecordset::CheckFunction(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionName((m_szFunction = ExtractText(m_szFunction))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCKELEMENT_ILLEGALFUNCTIONNAME), (LPCTSTR)GetFunction(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCFunctionBlockElementsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionBlockElementInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONBLOCKELEMENT_ILLEGALINTERPRETATION), (LPCTSTR)GetFunction(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCFunctionBlockElementsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCFunctionBlockElementsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_BCCF_CNAME)), m_szFunction);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_BCCF_INTER)), m_szInterpretation);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_BCCF_CONTENT)), m_szName);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequencesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCSequencesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCSequencesRecordset::CALTELDatabaseTCSequencesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCSequencesRecordset)
	m_szName.Empty();
	m_szUser.Empty();
	m_szDescription.Empty();
	m_szDocumentName.Empty();
	m_szDocumentIssue.Empty();
	m_szDestinationSubSchedule.Empty();
	m_szMissionPlannerEvent.Empty();
	m_szDate[0].Empty();
	m_szDate[1].Empty();
	m_nParameters = 0;
	m_nEntries = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCSequencesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCSequencesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCSequencesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCSequencesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCSequencesRecordset::SetUser(LPCTSTR pszUser)
{
	m_szUser = pszUser;
}

CString CALTELDatabaseTCSequencesRecordset::GetUser() CONST
{
	return m_szUser;
}

VOID CALTELDatabaseTCSequencesRecordset::SetDate(CONST CTimeKey &tDate)
{
	m_szDate[0] = GetDatabaseEngine()->TranslateTCSequenceDate(tDate, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT));
}

CTimeKey CALTELDatabaseTCSequencesRecordset::GetDate() CONST
{
	TIMEKEY  tDate;

	return(((tDate = GetDatabaseEngine()->TranslateTCSequenceDate(m_szDate[0], STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)).GetTime()) <= 0) ? GetDatabaseEngine()->TranslateTCSequenceDate(m_szDate[0], STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)) : tDate);
}

VOID CALTELDatabaseTCSequencesRecordset::SetDestinationSubSchedule(LPCTSTR pszSubSchedule)
{
	m_szDestinationSubSchedule = pszSubSchedule;
}

CString CALTELDatabaseTCSequencesRecordset::GetDestinationSubSchedule() CONST
{
	return m_szDestinationSubSchedule;
}

VOID CALTELDatabaseTCSequencesRecordset::SetMissionPlannerEvent(LPCTSTR pszEvent)
{
	m_szMissionPlannerEvent = pszEvent;
}

CString CALTELDatabaseTCSequencesRecordset::GetMissionPlannerEvent() CONST
{
	return m_szMissionPlannerEvent;
}

VOID CALTELDatabaseTCSequencesRecordset::SetDocumentName(LPCTSTR pszName)
{
	m_szDocumentName = pszName;
}

CString CALTELDatabaseTCSequencesRecordset::GetDocumentName() CONST
{
	return m_szDocumentName;
}

VOID CALTELDatabaseTCSequencesRecordset::SetDocumentIssue(LPCTSTR pszIssue)
{
	m_szDocumentIssue = pszIssue;
}

CString CALTELDatabaseTCSequencesRecordset::GetDocumentIssue() CONST
{
	return m_szDocumentIssue;
}

VOID CALTELDatabaseTCSequencesRecordset::SetDocumentDate(CONST CTimeKey &tDate)
{
	m_szDate[1] = GetDatabaseEngine()->TranslateTCSequenceDocumentDate(tDate, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT));
}

CTimeKey CALTELDatabaseTCSequencesRecordset::GetDocumentDate() CONST
{
	TIMEKEY  tDate;

	return(((tDate = GetDatabaseEngine()->TranslateTCSequenceDocumentDate(m_szDate[1], STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)).GetTime()) <= 0) ? GetDatabaseEngine()->TranslateTCSequenceDocumentDate(m_szDate[1], STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)) : tDate);
}

VOID CALTELDatabaseTCSequencesRecordset::SetParameterCount(INT nCount)
{
	m_nParameters = nCount;
}

INT CALTELDatabaseTCSequencesRecordset::GetParameterCount() CONST
{
	return m_nParameters;
}

VOID CALTELDatabaseTCSequencesRecordset::SetEntryCount(INT nCount)
{
	m_nEntries = nCount;
}

INT CALTELDatabaseTCSequencesRecordset::GetEntryCount() CONST
{
	return m_nEntries;
}

VOID CALTELDatabaseTCSequencesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCExeVerGroupStatus(nStatus);
}

INT CALTELDatabaseTCSequencesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCExeVerGroupStatus(m_szStatus);
}

VOID CALTELDatabaseTCSequencesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCSequencesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableErrorsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCSequencesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCSequencesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableWarningsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCSequencesRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence)
{
	CDatabaseTCParameters  pDatabaseTCParameters;

	SetName(pDatabaseTCSequence->GetName());
	SetDescription(pDatabaseTCSequence->GetDescription());
	SetUser(pDatabaseTCSequence->GetUser());
	SetDate(pDatabaseTCSequence->GetDate());
	SetEntryCount((INT)pDatabaseTCSequence->GetSize());
	SetParameterCount(pDatabaseTCSequence->GetParameters(pDatabaseTCParameters));
	SetDestinationSubSchedule(pDatabaseTCSequence->GetDestinationSubSchedule());
	SetMissionPlannerEvent(pDatabaseTCSequence->GetMissionPlannerEvent());
	SetDocumentName(pDatabaseTCSequence->GetDocumentName());
	SetDocumentDate(pDatabaseTCSequence->GetDocumentDate());
	SetDocumentIssue(pDatabaseTCSequence->GetDocumentIssue());
	SetStatus(pDatabaseTCSequence->GetStatus());
}

BOOL CALTELDatabaseTCSequencesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCSequencesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TCSEQUENCE_RECORDSTATUS_NONE || GetStatus() == TCSEQUENCE_RECORDSTATUS_NEW || GetStatus() == TCSEQUENCE_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckUser(bStatus);
		CheckDate(bStatus);
		CheckEntryCount(bStatus);
		CheckParameterCount(bStatus);
		CheckDestinationSubSchedule(bStatus);
		CheckMissionPlannerEvent(bStatus);
		CheckDocumentName(bStatus);
		CheckDocumentDate(bStatus);
		CheckDocumentIssue(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckUser(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceUserName((m_szUser = ExtractText(m_szUser))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALUSERNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckDate(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDate((m_szDate[0] = ExtractText(m_szDate[0])), STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceDate(m_szDate[0], STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALDATE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckDestinationSubSchedule(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceSubScheduleDestination((m_szDestinationSubSchedule = ExtractText(m_szDestinationSubSchedule))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALDESTINATIONSUBSCHEDULE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckMissionPlannerEvent(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceMissionPlannerEvent((m_szMissionPlannerEvent = ExtractText(m_szMissionPlannerEvent))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALMISSIONPLANNEREVENT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckDocumentName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDocumentName((m_szDocumentName = ExtractText(m_szDocumentName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALDOCUMENTNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckDocumentIssue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDocumentIssue((m_szDocumentIssue = ExtractText(m_szDocumentIssue))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALDOCUMENTISSUE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckDocumentDate(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDocumentDate((m_szDate[1] = ExtractText(m_szDate[1])), STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceDocumentDate(m_szDate[1], STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALDOCUMENTDATE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckParameterCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterCount(m_nParameters))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALPARAMETERCOUNT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckEntryCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryCount(m_nEntries))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALENTRYCOUNT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequencesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCSequencesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCSequencesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_NFPARS)), m_nParameters);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_NSTMNT)), m_nEntries);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_SEQDATE)), m_szDate[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_SEQUSER)), m_szUser);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DOCNAME)), m_szDocumentName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DOCISSUE)), m_szDocumentIssue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DOCDATE)), m_szDate[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_COSEV)), m_szMissionPlannerEvent);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_SSCH)), m_szDestinationSubSchedule);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequenceParametersRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCSequenceParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCSequenceParametersRecordset::CALTELDatabaseTCSequenceParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCSequenceParametersRecordset)
	m_szSequence.Empty();
	m_szTag.Empty();
	m_szDescription.Empty();
	m_szUnit.Empty();
	m_szCoding.Empty();
	m_szCategory.Empty();
	m_szValueType.Empty();
	m_szValueRadix.Empty();
	m_szCalTable[0].Empty();
	m_szCalTable[1].Empty();
	m_szOolTable[0].Empty();
	m_szOolTable[1].Empty();
	m_szConstValue.Empty();
	m_nPosition = 0;
	m_nBitWidth = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTCSequenceParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetSequence(LPCTSTR pszSequence)
{
	m_szSequence = pszSequence;
}

CString CALTELDatabaseTCSequenceParametersRecordset::GetSequence() CONST
{
	return m_szSequence;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCSequenceParametersRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CALTELDatabaseTCSequenceParametersRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szCategory = GetDatabaseEngine()->TranslateTCSequenceParameterCategory(nAttributes);
	m_szCoding = GetDatabaseEngine()->TranslateTCSequenceParameterCoding(nAttributes);
	m_szValueType = GetDatabaseEngine()->TranslateTCSequenceParameterValueType(nAttributes);
	m_szValueRadix = GetDatabaseEngine()->TranslateTCSequenceParameterValueRadix(nAttributes);
}

ULONGLONG CALTELDatabaseTCSequenceParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceParameterCategory(m_szCategory) | GetDatabaseEngine()->TranslateTCSequenceParameterCoding(m_szCoding) | GetDatabaseEngine()->TranslateTCSequenceParameterValueType(m_szValueType) | GetDatabaseEngine()->TranslateTCSequenceParameterValueRadix(m_szValueRadix);
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetPosition(INT nPosition)
{
	m_nPosition = nPosition;
}

INT CALTELDatabaseTCSequenceParametersRecordset::GetPosition() CONST
{
	return m_nPosition;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetBitWidth(INT nWidth)
{
	m_nBitWidth = nWidth;
}

INT CALTELDatabaseTCSequenceParametersRecordset::GetBitWidth() CONST
{
	return m_nBitWidth;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetCalTable(LPCTSTR pszTable)
{
	m_szCalTable[0] = (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) ? pszTable : EMPTYSTRING;
	m_szCalTable[1] = (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? pszTable : EMPTYSTRING;
}

CString CALTELDatabaseTCSequenceParametersRecordset::GetCalTable() CONST
{
	if (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) return m_szCalTable[0];
	if (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) return m_szCalTable[1];
	return EMPTYSTRING;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetOolTable(LPCTSTR pszTable)
{
	m_szOolTable[0] = ((GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? pszTable : EMPTYSTRING;
	m_szOolTable[1] = (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? pszTable : EMPTYSTRING;
}

CString CALTELDatabaseTCSequenceParametersRecordset::GetOolTable() CONST
{
	if ((GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) return m_szOolTable[0];
	if (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) return m_szOolTable[1];
	return EMPTYSTRING;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szConstValue = pszConstValue;
}

CString CALTELDatabaseTCSequenceParametersRecordset::GetConstValue() CONST
{
	return m_szConstValue;
}

VOID CALTELDatabaseTCSequenceParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSequence), pszError);
}
VOID CALTELDatabaseTCSequenceParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableErrorsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCSequenceParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSequence), pszWarning);
}
VOID CALTELDatabaseTCSequenceParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableWarningsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition)
{
	SetPosition(nPosition);
	SetTag(pDatabaseTCParameter->GetTag());
	SetSequence(pDatabaseTCSequence->GetName());
	SetDescription(pDatabaseTCParameter->GetDescription());
	SetUnit(pDatabaseTCParameter->GetUnit());
	SetAttributes(pDatabaseTCParameter->GetAttributes());
	SetBitWidth(pDatabaseTCParameter->GetWidth());
	SetCalTable(pDatabaseTCParameter->GetCalTable());
	SetOolTable(pDatabaseTCParameter->GetOolTable());
	SetConstValue(pDatabaseTCParameter->GetConstValueAsText());
	return((!pDatabaseTCParameter->GetTag().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCSequenceParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = ((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(GetSequence())))) ? (pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_NONE || pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_NEW || pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_CHANGED) : TRUE));
		CheckSequence(bStatus);
		CheckDescription(bStatus);
		CheckUnit(bStatus);
		CheckAttributes(bStatus);
		CheckPosition(bStatus);
		CheckBitWidth(bStatus);
		CheckCalTable(bStatus);
		CheckOolTable(bStatus);
		CheckConstValue(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckSequence(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckBitWidth(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALTAG), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckSequence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceName((m_szSequence = ExtractText(m_szSequence))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALSEQUENCENAME), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALDESCRIPTION), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckUnit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterUnit((m_szUnit = ExtractText(m_szUnit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALUNIT), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterCategory((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALCATEGORY), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceParameterCoding(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALCODING), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceParameterValueType(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALVALUETYPE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceParameterValueRadix(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALVALUERADIX), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckPosition(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterPosition(GetPosition()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALPOSITION), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckBitWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterBitWidth(GetBitWidth()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALBITWIDTH), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckCalTable(BOOL bStatus)
{
	CString  szMessage;

	for (m_szCalTable[0] = ExtractText(m_szCalTable[0]), m_szCalTable[1] = ExtractText(m_szCalTable[1]); !GetDatabaseEngine()->CheckTCSequenceParameterCalTable(GetAttributes(), GetCalTable()); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALCALTABLE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckOolTable(BOOL bStatus)
{
	CString  szMessage;

	for (m_szOolTable[0] = ExtractText(m_szOolTable[0]), m_szOolTable[1] = ExtractText(m_szOolTable[1]); !GetDatabaseEngine()->CheckTCSequenceParameterOolTable(GetAttributes(), GetOolTable()); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALOOLTABLE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceParametersRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterConstValue(GetAttributes(), (m_szConstValue = ExtractText(m_szConstValue))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALCONSTVALUE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCSequenceParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCSequenceParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_SQNAME)), m_szSequence);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_FPNAME)), m_szTag);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_FPNUM)), m_nPosition);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_LENGTH)), m_nBitWidth);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_CODING)), m_szCoding);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_UNIT)), m_szUnit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_VTYPE)), m_szValueType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_RADIX)), m_szValueRadix);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_DEFVAL)), m_szConstValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_CATEG)), m_szCategory);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_CALREF)), m_szCalTable[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_TXFREF)), m_szCalTable[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_OCFREF)), m_szOolTable[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_FXFREF)), m_szOolTable[1]);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequenceEntriesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCSequenceEntriesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCSequenceEntriesRecordset::CALTELDatabaseTCSequenceEntriesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCSequenceEntriesRecordset)
	m_szSequence.Empty();
	m_szName.Empty();
	m_szType.Empty();
	m_szTCType.Empty();
	m_szDescription.Empty();
	m_sz1Step.Empty();
	m_szBlockMacro.Empty();
	m_szBlockMember.Empty();
	m_szGroupMember.Empty();
	m_szRelDelta.Empty();
	m_szExeTime.Empty();
	m_szExeDelta.Empty();
	m_nParameters = 0;
	m_nEntry = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCSequenceEntriesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetSequence(LPCTSTR pszSequence)
{
	m_szSequence = pszSequence;
}

CString CALTELDatabaseTCSequenceEntriesRecordset::GetSequence() CONST
{
	return m_szSequence;
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCSequenceEntriesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCSequenceEntryType(nAttributes);
	m_szTCType = GetDatabaseEngine()->TranslateTCSequenceEntrySubType(nAttributes);
	m_szBlockMacro = GetDatabaseEngine()->TranslateTCSequenceEntryBlockFlag(nAttributes);
	m_szGroupMember = GetDatabaseEngine()->TranslateTCSequenceEntryGroupFlag(nAttributes);
}

ULONGLONG CALTELDatabaseTCSequenceEntriesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceEntryType(m_szType) | GetDatabaseEngine()->TranslateTCSequenceEntrySubType(m_szTCType) | GetDatabaseEngine()->TranslateTCSequenceEntryBlockFlag(m_szBlockMacro, m_szBlockMember) | GetDatabaseEngine()->TranslateTCSequenceEntryGroupFlag(m_szGroupMember);
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetEntry(INT nEntry)
{
	m_nEntry = nEntry;
}

INT CALTELDatabaseTCSequenceEntriesRecordset::GetEntry() CONST
{
	return m_nEntry;
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetAssociated1Step(LPCTSTR pszName)
{
	m_sz1Step = pszName;
}

CString CALTELDatabaseTCSequenceEntriesRecordset::GetAssociated1Step() CONST
{
	return m_sz1Step;
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetBlockMembership(INT nMember)
{
	m_szBlockMember = GetDatabaseEngine()->TranslateTCSequenceEntryBlockMembership(nMember);
}

INT CALTELDatabaseTCSequenceEntriesRecordset::GetBlockMembership() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceEntryBlockMembership(m_szBlockMember);
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetReleaseDeltaTime(DWORD dwDelta)
{
	m_szRelDelta = GetDatabaseEngine()->TranslateTCSequenceEntryReleaseDeltaTime(dwDelta, STRING(IDS_DATABASE_TABLE_CSS_DBMSRELTIME_FORMAT));
}

DWORD CALTELDatabaseTCSequenceEntriesRecordset::GetReleaseDeltaTime() CONST
{
	DWORD  dwReleaseDeltaTime;

	return(((dwReleaseDeltaTime = GetDatabaseEngine()->TranslateTCSequenceEntryReleaseDeltaTime(m_szRelDelta, STRING(IDS_DATABASE_TABLE_CSS_DBMSRELTIME_FORMAT))) == 0 && !m_szRelDelta.IsEmpty()) ? (1000 * (GetDatabaseEngine()->TranslateTCSequenceEntryReleaseDeltaTime(m_szRelDelta, STRING(IDS_DATABASE_TABLE_CSS_DBMSSHORTRELTIME_FORMAT)) / 1000)) : dwReleaseDeltaTime);
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetExecutionTime(CONST CTimeTag &tTime)
{
	m_szExeTime = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionTime(tTime, STRING(IDS_DATABASE_TABLE_CSS_DBMSABSTIME_FORMAT));
}

CTimeTag CALTELDatabaseTCSequenceEntriesRecordset::GetExecutionTime() CONST
{
	CTimeTag  tExecutionTime;

	return(((tExecutionTime = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionTime(m_szExeTime, STRING(IDS_DATABASE_TABLE_CSS_DBMSABSTIME_FORMAT))).GetTime() == 0) ? (1000000 * (GetDatabaseEngine()->TranslateTCSequenceEntryExecutionTime(m_szExeTime, STRING(IDS_DATABASE_TABLE_CSS_DBMSSHORTABSTIME_FORMAT)).GetTime() / 1000000)) : tExecutionTime);
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetExecutionDeltaTime(DWORD dwDelta, BOOL bEarlier)
{
	m_szExeDelta = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionDeltaTime(dwDelta, bEarlier, STRING(IDS_DATABASE_TABLE_CSS_DBMSRELTIME_FORMAT));
}

DWORD CALTELDatabaseTCSequenceEntriesRecordset::GetExecutionDeltaTime(BOOL &bEarlier) CONST
{
	DWORD  dwExecutionDeltaTime;

	return(((dwExecutionDeltaTime = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionDeltaTime(m_szExeDelta, bEarlier, STRING(IDS_DATABASE_TABLE_CSS_DBMSRELTIME_FORMAT))) == 0 && !m_szExeDelta.IsEmpty()) ? (1000 * (GetDatabaseEngine()->TranslateTCSequenceEntryExecutionDeltaTime(m_szExeDelta, bEarlier, STRING(IDS_DATABASE_TABLE_CSS_DBMSSHORTRELTIME_FORMAT)) / 1000)) : dwExecutionDeltaTime);
}
DWORD CALTELDatabaseTCSequenceEntriesRecordset::GetExecutionDeltaTime() CONST
{
	BOOL  bEarlier;

	return GetExecutionDeltaTime(bEarlier);
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::IsEarlierExecutionDeltaTime() CONST
{
	BOOL  bEarlier;

	GetExecutionDeltaTime(bEarlier);
	return bEarlier;
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::SetParameterCount(INT nCount)
{
	m_nParameters = nCount;
}

INT CALTELDatabaseTCSequenceEntriesRecordset::GetParameterCount() CONST
{
	return m_nParameters;
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSequence), pszError);
}
VOID CALTELDatabaseTCSequenceEntriesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableErrorsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCSequenceEntriesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSequence), pszWarning);
}
VOID CALTELDatabaseTCSequenceEntriesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableWarningsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry, INT nEntry)
{
	SetEntry(nEntry + 1);
	SetName(pDatabaseTCSequenceEntry->GetName());
	SetSequence(pDatabaseTCSequence->GetName());
	SetDescription(pDatabaseTCSequenceEntry->GetDescription());
	SetAttributes(pDatabaseTCSequenceEntry->GetAttributes());
	SetAssociated1Step(pDatabaseTCSequenceEntry->GetAssociated1Step());
	SetBlockMembership(pDatabaseTCSequenceEntry->GetBlockMembership());
	SetReleaseDeltaTime(pDatabaseTCSequenceEntry->GetReleaseDeltaTime());
	SetExecutionTime(pDatabaseTCSequenceEntry->GetExecutionTime());
	SetExecutionDeltaTime(pDatabaseTCSequenceEntry->GetExecutionDeltaTime(), pDatabaseTCSequenceEntry->IsEarlierExecutionDeltaTime());
	SetParameterCount((INT)pDatabaseTCSequenceEntry->GetSize());
	return((!pDatabaseTCSequenceEntry->GetName().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCSequenceEntriesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(GetSequence())))) ? (pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_NONE || pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_NEW || pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_CHANGED) : TRUE));
		CheckSequence(bStatus);
		CheckDescription(bStatus);
		CheckAttributes(bStatus);
		CheckEntry(bStatus);
		CheckAssociated1Step(bStatus);
		CheckBlockMembership(bStatus);
		CheckReleaseDeltaTime(bStatus);
		CheckExecutionTime(bStatus);
		CheckExecutionDeltaTime(bStatus);
		CheckParameterCount(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckSequence(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckEntry(IsCollectingIssues());
		bCheck &= CheckParameterCount(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALNAME), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckSequence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceName((m_szSequence = ExtractText(m_szSequence))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALSEQUENCENAME), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALDESCRIPTION), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryType((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALTYPE), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntrySubType(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALSUBTYPE), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryBlockFlag(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALBLOCKFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryGroupFlag(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALGROUPFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckEntry(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryIndex(m_nEntry))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALINDEX), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckAssociated1Step(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntry1Step((m_sz1Step = ExtractText(m_sz1Step))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGAL1STEP), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckBlockMembership(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryBlockMembership((m_szBlockMember = ExtractText(m_szBlockMember))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALBLOCKMEMBERINDEX), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckReleaseDeltaTime(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryReleaseDeltaTime((nAttributes = GetAttributes()), (m_szRelDelta = ExtractText(m_szRelDelta)), STRING(IDS_DATABASE_TABLE_CSS_DBMSRELTIME_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryReleaseDeltaTime(nAttributes, m_szRelDelta, STRING(IDS_DATABASE_TABLE_CSS_DBMSSHORTRELTIME_FORMAT)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALRELEASEDELTATIME), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckExecutionTime(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryExecutionTime((m_szExeTime = ExtractText(m_szExeTime)), STRING(IDS_DATABASE_TABLE_CSS_DBMSABSTIME_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionTime(m_szExeTime, STRING(IDS_DATABASE_TABLE_CSS_DBMSSHORTABSTIME_FORMAT)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALEXECUTIONTIME), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckExecutionDeltaTime(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime((m_szExeDelta = ExtractText(m_szExeDelta)), STRING(IDS_DATABASE_TABLE_CSS_DBMSRELTIME_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExeDelta, STRING(IDS_DATABASE_TABLE_CSS_DBMSSHORTRELTIME_FORMAT)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALEXECUTIONDELTATIME), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntriesRecordset::CheckParameterCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterCount(m_nParameters))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALPARAMETERCOUNT), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCSequenceEntriesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCSequenceEntriesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_SQNAME)), m_szSequence);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_COMMENT)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_TCTYPE)), m_szTCType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_1STEP)), m_sz1Step);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_ENTRY)), m_nEntry);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_IDENT)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_RELTIME)), m_szRelDelta);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_ABSTIME)), m_szExeTime);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_EXETIME)), m_szExeDelta);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_GROUP)), m_szGroupMember);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_BLOCK)), m_szBlockMember);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_BLKCNTL)), m_szBlockMacro);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_NPARS)), m_nParameters);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequenceEntryParametersRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCSequenceEntryParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCSequenceEntryParametersRecordset::CALTELDatabaseTCSequenceEntryParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCSequenceEntryParametersRecordset)
	m_szSequence.Empty();
	m_szTag.Empty();
	m_szDescription.Empty();
	m_szValueType.Empty();
	m_szValueRadix.Empty();
	m_szConstValue.Empty();
	m_szMemoryArea[0].Empty();
	m_szMemoryArea[1].Empty();
	m_nBitOffset = 0;
	m_nEntry = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTCSequenceEntryParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetSequence(LPCTSTR pszSequence)
{
	m_szSequence = pszSequence;
}

CString CALTELDatabaseTCSequenceEntryParametersRecordset::GetSequence() CONST
{
	return m_szSequence;
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCSequenceEntryParametersRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szValueType = GetDatabaseEngine()->TranslateTCSequenceEntryParameterValueType(nAttributes);
	m_szValueRadix = GetDatabaseEngine()->TranslateTCSequenceEntryParameterValueRadix(nAttributes);
}

ULONGLONG CALTELDatabaseTCSequenceEntryParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceEntryParameterValueType(m_szValueType) | GetDatabaseEngine()->TranslateTCSequenceEntryParameterValueRadix(m_szValueRadix);
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetEntry(INT nEntry)
{
	m_nEntry = nEntry;
}

INT CALTELDatabaseTCSequenceEntryParametersRecordset::GetEntry() CONST
{
	return m_nEntry;
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetBitOffset(INT nOffset)
{
	m_nBitOffset = nOffset;
}

INT CALTELDatabaseTCSequenceEntryParametersRecordset::GetBitOffset() CONST
{
	return m_nBitOffset;
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szConstValue = pszConstValue;
}

CString CALTELDatabaseTCSequenceEntryParametersRecordset::GetConstValue() CONST
{
	return m_szConstValue;
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetMemoryAreaName(LPCTSTR pszName)
{
	m_szMemoryArea[0] = pszName;
}

CString CALTELDatabaseTCSequenceEntryParametersRecordset::GetMemoryAreaName() CONST
{
	return m_szMemoryArea[0];
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::SetMemoryAreaVersion(LPCTSTR pszVersion)
{
	m_szMemoryArea[1] = pszVersion;
}

CString CALTELDatabaseTCSequenceEntryParametersRecordset::GetMemoryAreaVersion() CONST
{
	return m_szMemoryArea[1];
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSequence), pszError);
}
VOID CALTELDatabaseTCSequenceEntryParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableErrorsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCSequenceEntryParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSequence), pszWarning);
}
VOID CALTELDatabaseTCSequenceEntryParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	EnableWarningsByStatus(((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(pszName)))) ? pDatabaseTCSequence->GetStatus() : TCSEQUENCE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntryParameter *pDatabaseTCSequenceEntryParameter, INT nEntry)
{
	CString  szMemoryArea[2];

	SetEntry(nEntry + 1);
	SetTag(pDatabaseTCSequenceEntryParameter->GetTag());
	SetSequence(pDatabaseTCSequence->GetName());
	SetDescription(pDatabaseTCSequenceEntryParameter->GetDescription());
	SetAttributes(pDatabaseTCSequenceEntryParameter->GetAttributes());
	SetConstValue(pDatabaseTCSequenceEntryParameter->GetConstValueAsText());
	SetBitOffset(8 * pDatabaseTCSequenceEntryParameter->GetBytePos() + pDatabaseTCSequenceEntryParameter->GetBitPos());
	if (pDatabaseTCSequenceEntryParameter->GetMemoryArea(szMemoryArea[0], szMemoryArea[1]))
	{
		SetMemoryAreaName(szMemoryArea[0]);
		SetMemoryAreaVersion(szMemoryArea[1]);
	}
	return((!pDatabaseTCSequenceEntryParameter->GetTag().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = ((pDatabaseTCSequence = GetDatabaseEngine()->GetTCSequences()->GetAt(GetDatabaseEngine()->GetTCSequences()->Find(GetSequence())))) ? (pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_NONE || pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_NEW || pDatabaseTCSequence->GetStatus() == TCSEQUENCE_RECORDSTATUS_CHANGED) : TRUE));
		CheckSequence(bStatus);
		CheckDescription(bStatus);
		CheckAttributes(bStatus);
		CheckEntry(bStatus);
		CheckBitOffset(bStatus);
		CheckConstValue(bStatus);
		CheckMemoryAreaName(bStatus);
		CheckMemoryAreaVersion(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckSequence(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckEntry(IsCollectingIssues());
		bCheck &= CheckBitOffset(IsCollectingIssues());
		bCheck &= CheckConstValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALTAG), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckSequence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceName((m_szSequence = ExtractText(m_szSequence))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALSEQUENCENAME), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterComment((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALCOMMENT), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterValueType((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALVALUETYPE), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterValueRadix(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALVALUERADIX), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckEntry(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterPosition(GetEntry()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALPOSITION), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckBitOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterBitOffset(GetBitOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALBITOFFSET), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckConstValue(BOOL bStatus)
{
	INT  nLength;
	CString  szMessage;

	if ((nLength = lstrlen((m_szConstValue = ExtractText(m_szConstValue)))) == 0 || nLength > GetDatabaseEngine()->GetTCSequenceEntryParameterConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALCONSTVALUE), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckMemoryAreaName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterMemoryAreaName((m_szMemoryArea[0] = ExtractText(m_szMemoryArea[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALMEMORYAREANAME), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCSequenceEntryParametersRecordset::CheckMemoryAreaVersion(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterMemoryAreaVersion((m_szMemoryArea[1] = ExtractText(m_szMemoryArea[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALMEMORYAREAVERSION), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCSequenceEntryParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCSequenceEntryParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_SQNAME)), m_szSequence);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_ENTRY)), m_nEntry);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_BITOFF)), m_nBitOffset);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_PNAME)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_COMMENT)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_VALTYPE)), m_szValueType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_VALRADIX)), m_szValueRadix);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_VALUE)), m_szConstValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_PSET)), m_szMemoryArea[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_PSINST)), m_szMemoryArea[1]);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseOBProcessorsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseOBProcessorsRecordset::CALTELDatabaseOBProcessorsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseOBProcessorsRecordset)
	m_szName.Empty();
	m_szPatchCommand.Empty();
	m_szDumpCommand.Empty();
	m_szDumpPacket.Empty();
	m_szMasterImage.Empty();
	m_nAddressRange[0][0] = 0;
	m_nAddressRange[0][1] = 0;
	m_nAddressRange[1][0] = 0;
	m_nAddressRange[1][1] = 0;
	m_tDumpInterval = 0;
	m_nDumpCount = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseOBProcessorsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseOBProcessorsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseOBProcessorsRecordset::SetPatchCommand(LPCTSTR pszCommand)
{
	m_szPatchCommand = pszCommand;
}

CString CALTELDatabaseOBProcessorsRecordset::GetPatchCommand() CONST
{
	return m_szPatchCommand;
}

VOID CALTELDatabaseOBProcessorsRecordset::SetDumpCommand(LPCTSTR pszCommand)
{
	m_szDumpCommand = pszCommand;
}

CString CALTELDatabaseOBProcessorsRecordset::GetDumpCommand() CONST
{
	return m_szDumpCommand;
}

VOID CALTELDatabaseOBProcessorsRecordset::SetDumpPacket(LPCTSTR pszPacket)
{
	m_szDumpPacket = pszPacket;
}

CString CALTELDatabaseOBProcessorsRecordset::GetDumpPacket() CONST
{
	return m_szDumpPacket;
}

VOID CALTELDatabaseOBProcessorsRecordset::SetDumpInterval(CONST CTimeSpan &tInterval)
{
	m_tDumpInterval = (INT)tInterval.GetTotalSeconds();
}

CTimeSpan CALTELDatabaseOBProcessorsRecordset::GetDumpInterval() CONST
{
	return m_tDumpInterval;
}

VOID CALTELDatabaseOBProcessorsRecordset::SetDumpCount(INT nCount)
{
	m_nDumpCount = nCount;
}

INT CALTELDatabaseOBProcessorsRecordset::GetDumpCount() CONST
{
	return m_nDumpCount;
}

VOID CALTELDatabaseOBProcessorsRecordset::SetMasterImage(LPCTSTR pszImage)
{
	m_szMasterImage = pszImage;
}

CString CALTELDatabaseOBProcessorsRecordset::GetMasterImage() CONST
{
	return m_szMasterImage;
}

VOID CALTELDatabaseOBProcessorsRecordset::SetAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress)
{
	m_nAddressRange[0][0] = nStartPage;
	m_nAddressRange[0][1] = nEndPage;
	m_nAddressRange[1][0] = nStartAddress;
	m_nAddressRange[1][1] = nEndAddress;
}

BOOL CALTELDatabaseOBProcessorsRecordset::GetAddressRange(UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST
{
	return GetDatabaseEngine()->CheckOBProcessorAddressRange((nStartPage = m_nAddressRange[0][0]), (nStartAddress = m_nAddressRange[1][0]), (nEndPage = m_nAddressRange[0][1]), (nEndAddress = m_nAddressRange[1][1]));
}

VOID CALTELDatabaseOBProcessorsRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateOBProcessorStatus(nStatus);
}

INT CALTELDatabaseOBProcessorsRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorStatus(m_szStatus);
}

VOID CALTELDatabaseOBProcessorsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseOBProcessorsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableErrorsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseOBProcessorsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseOBProcessorsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableWarningsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseOBProcessorsRecordset::Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor)
{
	UINT  nAddress[2][2];

	SetName(pDatabaseOBProcessor->GetName());
	SetPatchCommand(pDatabaseOBProcessor->GetPatchCommand());
	SetDumpCommand(pDatabaseOBProcessor->GetDumpCommand());
	SetDumpPacket(pDatabaseOBProcessor->GetDumpPacket());
	SetDumpInterval(pDatabaseOBProcessor->GetDumpInterval());
	SetDumpCount(pDatabaseOBProcessor->GetDumpCount());
	SetMasterImage(pDatabaseOBProcessor->GetMasterImage());
	for (nAddress[0][0] = nAddress[0][1] = nAddress[1][0] = nAddress[1][1] = 0; pDatabaseOBProcessor->GetAddressRange(nAddress[0][0], nAddress[1][0], nAddress[0][1], nAddress[1][1]); )
	{
		SetAddressRange(nAddress[0][0], nAddress[1][0], nAddress[0][1], nAddress[1][1]);
		break;
	}
	SetStatus(pDatabaseOBProcessor->GetStatus());
}

BOOL CALTELDatabaseOBProcessorsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseOBProcessorsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == OBPROCESSOR_RECORDSTATUS_NONE || GetStatus() == OBPROCESSOR_RECORDSTATUS_NEW || GetStatus() == OBPROCESSOR_RECORDSTATUS_CHANGED)));
		CheckPatchCommand(bStatus);
		CheckDumpCommand(bStatus);
		CheckDumpPacket(bStatus);
		CheckDumpInterval(bStatus);
		CheckDumpCount(bStatus);
		CheckMasterImage(bStatus);
		CheckAddressRange(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDumpCommand(IsCollectingIssues());
		bCheck &= CheckDumpPacket(IsCollectingIssues());
		bCheck &= CheckDumpInterval(IsCollectingIssues());
		bCheck &= CheckMasterImage(IsCollectingIssues());
		bCheck &= CheckAddressRange(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckPatchCommand(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorPatchCommand((m_szPatchCommand = ExtractText(m_szPatchCommand))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALPATCHCOMMAND), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckDumpCommand(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorDumpCommand((m_szDumpCommand = ExtractText(m_szDumpCommand))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALDUMPCOMMAND), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckDumpPacket(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorDumpPacket((m_szDumpPacket = ExtractText(m_szDumpPacket))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALDUMPPACKET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckDumpInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorDumpInterval(GetDumpInterval()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALDUMPINTERVAL), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckDumpCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorDumpCount(GetDumpCount()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALDUMPCOUNT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckMasterImage(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMasterImage((m_szMasterImage = ExtractText(m_szMasterImage))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALMASTERIMAGE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckAddressRange(BOOL bStatus)
{
	UINT  nAddress[2][2];
	CString  szMessage;

	for (GetAddressRange(nAddress[0][0], nAddress[1][0], nAddress[0][1], nAddress[1][1]); !GetDatabaseEngine()->CheckOBProcessorAddressRange(nAddress[0][0], nAddress[1][0], nAddress[0][1], nAddress[1][1]); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALADDRESSRANGE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorsRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseOBProcessorsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseOBProcessorsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_PROCESSOR)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_PATCHTC)), m_szPatchCommand);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_DUMPTC)), m_szDumpCommand);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_TMPKT)), m_szDumpPacket);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_STARTPAGE)), m_nAddressRange[0][0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_STARTADDR)), m_nAddressRange[1][0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_ENDPAGE)), m_nAddressRange[0][1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_ENDADDR)), m_nAddressRange[1][1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_IMGNAME)), m_szMasterImage);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_INTERVAL)), m_tDumpInterval);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_NUMPATCH)), m_nDumpCount);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryImagesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseOBProcessorMemoryImagesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseOBProcessorMemoryImagesRecordset::CALTELDatabaseOBProcessorMemoryImagesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseOBProcessorMemoryImagesRecordset)
	m_szName.Empty();
	m_szVersion.Empty();
	m_szData.Empty();
	m_nAddress[0] = 0;
	m_nAddress[1] = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseOBProcessorMemoryImagesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::SetVersion(LPCTSTR pszVersion)
{
	m_szVersion = pszVersion;
}

CString CALTELDatabaseOBProcessorMemoryImagesRecordset::GetVersion() CONST
{
	return m_szVersion;
}

VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::SetAddress(UINT nPage, UINT nAddress)
{
	m_nAddress[0] = nPage;
	m_nAddress[1] = nAddress;
}

BOOL CALTELDatabaseOBProcessorMemoryImagesRecordset::GetAddress(UINT &nPage, UINT &nAddress) CONST
{
	return GetDatabaseEngine()->CheckOBProcessorMemoryImageBlockAddress((nPage = m_nAddress[0]), (nAddress = m_nAddress[1]));
}

VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::SetData(LPCTSTR pszData)
{
	m_szData = GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(pszData, TRUE);
}
VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::SetData(CONST CByteArray &nData, CONST CByteArray &nMask)
{
	m_szData = GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(nData, nMask);
}

CString CALTELDatabaseOBProcessorMemoryImagesRecordset::GetData() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(m_szData, FALSE);
}
INT CALTELDatabaseOBProcessorMemoryImagesRecordset::GetData(CByteArray &nData, CByteArray &nMask) CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(m_szData, nData, nMask);
}

VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	EnableErrors();
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, pszError);
}

VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	EnableWarnings();
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, pszWarning);
}

VOID CALTELDatabaseOBProcessorMemoryImagesRecordset::Translate(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, CONST CDatabaseOBProcessorMemoryImageBlock *pDatabaseOBProcessorMemoryImageBlock)
{
	UINT  nAddress[2];
	CByteArray  nData[2];

	for (SetName(pDatabaseOBProcessorMemoryImage->GetName()), SetData(pDatabaseOBProcessorMemoryImageBlock->GetData()), SetVersion(pDatabaseOBProcessorMemoryImageBlock->GetVersion()); pDatabaseOBProcessorMemoryImageBlock->GetData(nData[0]) > 0 && pDatabaseOBProcessorMemoryImageBlock->GetMask(nData[1]) > 0; )
	{
		SetData(GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(nData[0], nData[1]));
		break;
	}
	for (SetAddress(-1, -1); pDatabaseOBProcessorMemoryImageBlock->GetAddress(nAddress[0], nAddress[1]); )
	{
		SetAddress(nAddress[0], nAddress[1]);
		break;
	}
}

BOOL CALTELDatabaseOBProcessorMemoryImagesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseOBProcessorMemoryImagesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName(TRUE);
		CheckVersion(TRUE);
		CheckAddress(TRUE);
		CheckData(TRUE);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckVersion(IsCollectingIssues());
		bCheck &= CheckAddress(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryImagesRecordset::CheckName(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryImageName((m_szName = ExtractText(m_szName))))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryImageBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYIMAGE_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)GetVersion(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryImagesRecordset::CheckVersion(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryImageBlockVersion((m_szVersion = ExtractText(m_szVersion))))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryImageBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYIMAGE_ILLEGALVERSION), (LPCTSTR)GetName(), (LPCTSTR)GetVersion(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryImagesRecordset::CheckAddress(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	for (GetAddress(nAddress[0], nAddress[1]); !GetDatabaseEngine()->CheckOBProcessorMemoryImageBlockAddress(nAddress[0], nAddress[1]); )
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryImageBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYIMAGE_ILLEGALADDRESS), (LPCTSTR)GetName(), (LPCTSTR)GetVersion(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryImagesRecordset::CheckData(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryImageBlockData((m_szData = ExtractText(m_szData))))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryImageBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYIMAGE_ILLEGALDATA), (LPCTSTR)GetName(), (LPCTSTR)GetVersion(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_IMG_DATAADDRESS_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseOBProcessorMemoryImagesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseOBProcessorMemoryImagesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_IMG_MNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_IMG_VERSION)), m_szVersion);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_IMG_PAGE)), m_nAddress[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_IMG_ADDRESS)), m_nAddress[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_IMG_DATA)), m_szData, GetDatabaseEngine()->GetOBProcessorMemoryImageBlockDataLength());
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreasRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreasRecordset, CALTELDatabaseRecordset)

CALTELDatabaseOBProcessorMemoryAreasRecordset::CALTELDatabaseOBProcessorMemoryAreasRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseOBProcessorMemoryAreasRecordset)
	m_szName.Empty();
	m_szProcessor.Empty();
	m_szDescription.Empty();
	m_szType.Empty();
	m_szPatchCommand.Empty();
	m_szDumpCommand.Empty();
	m_szDumpPacket.Empty();
	m_szPatchFlag.Empty();
	m_szDumpFlag.Empty();
	m_szUpdateFlag.Empty();
	m_szInhibitFlag.Empty();
	m_nFields = 11;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseOBProcessorMemoryAreasRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CALTELDatabaseOBProcessorMemoryAreasRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseOBProcessorMemoryAreasRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::SetPatchCommand(LPCTSTR pszCommand)
{
	m_szPatchCommand = pszCommand;
}

CString CALTELDatabaseOBProcessorMemoryAreasRecordset::GetPatchCommand() CONST
{
	return m_szPatchCommand;
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::SetDumpCommand(LPCTSTR pszCommand)
{
	m_szDumpCommand = pszCommand;
}

CString CALTELDatabaseOBProcessorMemoryAreasRecordset::GetDumpCommand() CONST
{
	return m_szDumpCommand;
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::SetDumpPacket(LPCTSTR pszPacket)
{
	m_szDumpPacket = pszPacket;
}

CString CALTELDatabaseOBProcessorMemoryAreasRecordset::GetDumpPacket() CONST
{
	return m_szDumpPacket;
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::SetAttributes(UINT nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaType(nAttributes);
	m_szPatchFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaPatchFlag(nAttributes);
	m_szDumpFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaDumpFlag(nAttributes);
	m_szUpdateFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaUpdateFlag(nAttributes);
	m_szInhibitFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaInhibitFlag(nAttributes);
}

UINT CALTELDatabaseOBProcessorMemoryAreasRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryAreaType(m_szType) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaPatchFlag(m_szPatchFlag) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaDumpFlag(m_szDumpFlag) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaUpdateFlag(m_szUpdateFlag) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaInhibitFlag(m_szInhibitFlag);
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableErrorsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CALTELDatabaseOBProcessorMemoryAreasRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableWarningsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea)
{
	SetName(pDatabaseOBProcessorMemoryArea->GetName());
	SetProcessor(pDatabaseOBProcessor->GetName());
	SetDescription(pDatabaseOBProcessorMemoryArea->GetDescription());
	SetPatchCommand(pDatabaseOBProcessorMemoryArea->GetPatchCommand());
	SetDumpCommand(pDatabaseOBProcessorMemoryArea->GetDumpCommand());
	SetDumpPacket(pDatabaseOBProcessorMemoryArea->GetDumpPacket());
	SetAttributes(pDatabaseOBProcessorMemoryArea->GetAttributes());
	return((pDatabaseOBProcessorMemoryArea->GetAttributes() & (OBPROCESSORMEMORYAREA_TYPE_MEMORY | OBPROCESSORMEMORYAREA_TYPE_IMAGE)) ? TRUE : FALSE);
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(GetProcessor())))) ? (pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NONE || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NEW || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_CHANGED) : TRUE));
		CheckProcessor(bStatus);
		CheckDescription(bStatus);
		CheckAttributes(bStatus);
		CheckPatchCommand(bStatus);
		CheckDumpCommand(bStatus);
		CheckDumpPacket(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckProcessor(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALNAME), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::CheckProcessor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorName((m_szProcessor = ExtractText(m_szProcessor))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALPROCESSORNAME), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALDESCRIPTION), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaType(GetDatabaseEngine()->TranslateOBProcessorMemoryAreaType((m_szType = ExtractText(m_szType)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALTYPE), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaPatchFlag(GetDatabaseEngine()->TranslateOBProcessorMemoryAreaPatchFlag((m_szPatchFlag = ExtractText(m_szPatchFlag)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALPATCHFLAG), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaDumpFlag(GetDatabaseEngine()->TranslateOBProcessorMemoryAreaDumpFlag((m_szDumpFlag = ExtractText(m_szDumpFlag)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALDUMPFLAG), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaUpdateFlag(GetDatabaseEngine()->TranslateOBProcessorMemoryAreaUpdateFlag((m_szUpdateFlag = ExtractText(m_szUpdateFlag)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALUPDATEFLAG), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaInhibitFlag(GetDatabaseEngine()->TranslateOBProcessorMemoryAreaInhibitFlag((m_szInhibitFlag = ExtractText(m_szInhibitFlag)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALINHIBITFLAG), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::CheckPatchCommand(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaPatchCommand((m_szPatchCommand = ExtractText(m_szPatchCommand))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALPATCHCOMMAND), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::CheckDumpCommand(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaDumpCommand((m_szDumpCommand = ExtractText(m_szDumpCommand))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALDUMPCOMMAND), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreasRecordset::CheckDumpPacket(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaDumpPacket((m_szDumpPacket = ExtractText(m_szDumpPacket))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREA_ILLEGALDUMPPACKET), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseOBProcessorMemoryAreasRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseOBProcessorMemoryAreasRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_PROCESSOR)), m_szProcessor);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_PATCHTC)), m_szPatchCommand);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_DUMPTC)), m_szDumpCommand);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_TMPKT)), m_szDumpPacket);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_PATCHABLE)), m_szPatchFlag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_DUMPABLE)), m_szDumpFlag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_UPDATE)), m_szUpdateFlag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MAD_INHIBIT)), m_szInhibitFlag);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset, CALTELDatabaseRecordset)

CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset)
	m_szName.Empty();
	m_szProcessor.Empty();
	m_szDescription.Empty();
	m_szParameter[0].Empty();
	m_szParameter[1].Empty();
	m_nAddress[0] = 0;
	m_nAddress[1] = 0;
	m_nBitOffset = 0;
	m_nBitWidth = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetTMParameter(LPCTSTR pszTag)
{
	m_szParameter[0] = pszTag;
}

CString CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetTMParameter() CONST
{
	return m_szParameter[0];
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetTCParameter(LPCTSTR pszTag)
{
	m_szParameter[1] = pszTag;
}

CString CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetTCParameter() CONST
{
	return m_szParameter[1];
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetAddress(UINT nPage, UINT nAddress)
{
	m_nAddress[0] = nPage;
	m_nAddress[1] = nAddress;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetAddress(UINT &nPage, UINT &nAddress) CONST
{
	nPage = m_nAddress[0];
	nAddress = m_nAddress[1];
	return GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockAddress(nPage, nAddress);
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetBitOffset(INT nOffset)
{
	m_nBitOffset = nOffset;
}

INT CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetBitOffset() CONST
{
	return m_nBitOffset;
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::SetBitWidth(INT nWidth)
{
	m_nBitWidth = nWidth;
}

INT CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::GetBitWidth() CONST
{
	return m_nBitWidth;
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableErrorsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableWarningsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::Translate(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaBlock *pDatabaseOBProcessorMemoryAreaBlock)
{
	UINT  nAddress[2];

	SetName(pDatabaseOBProcessorMemoryArea->GetName());
	SetDescription(pDatabaseOBProcessorMemoryAreaBlock->GetDescription());
	SetTMParameter(pDatabaseOBProcessorMemoryAreaBlock->GetTMParameter());
	SetTCParameter(pDatabaseOBProcessorMemoryAreaBlock->GetTCParameter());
	for (SetBitOffset(pDatabaseOBProcessorMemoryAreaBlock->GetBitOffset()), SetBitWidth(pDatabaseOBProcessorMemoryAreaBlock->GetBitWidth()); pDatabaseOBProcessorMemoryAreaBlock->GetAddress(nAddress[0], nAddress[1]); )
	{
		SetAddress(nAddress[0], nAddress[1]);
		break;
	}
	return((!pDatabaseOBProcessorMemoryArea->GetName().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	INT  nProcessor;
	INT  nProcessors;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	if (nOperation == CFieldExchange::Fixup)
	{
		for (nProcessor = 0, nProcessors = (INT)GetDatabaseEngine()->GetOBProcessors()->GetSize(), SetProcessor(EMPTYSTRING); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(nProcessor)) && pDatabaseOBProcessor->Find(ExtractText(m_szName)) >= 0)
			{
				SetProcessor(pDatabaseOBProcessor->GetName());
				break;
			}
		}
		CheckName((bStatus = ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(GetProcessor())))) ? (pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NONE || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NEW || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_CHANGED) : TRUE));
		CheckDescription(bStatus);
		CheckTMParameter(bStatus);
		CheckTCParameter(bStatus);
		CheckAddress(bStatus);
		CheckBitOffset(bStatus);
		CheckBitWidth(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		for (nProcessor = 0, nProcessors = (INT)GetDatabaseEngine()->GetOBProcessors()->GetSize(), SetProcessor(EMPTYSTRING); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(nProcessor)) && pDatabaseOBProcessor->Find(ExtractText(m_szName)) >= 0)
			{
				SetProcessor(pDatabaseOBProcessor->GetName());
				break;
			}
		}
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAddress(IsCollectingIssues());
		bCheck &= CheckBitOffset(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CheckName(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockName((m_szName = ExtractText(m_szName))))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryAreaBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREABLOCK_ILLEGALNAME), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), GetBitOffset()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CheckDescription(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryAreaBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREABLOCK_ILLEGALDESCRIPTION), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), GetBitOffset()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CheckTMParameter(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockTMParameter((m_szParameter[0] = ExtractText(m_szParameter[0]))))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryAreaBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREABLOCK_ILLEGALTMPARAMETER), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), GetBitOffset()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CheckTCParameter(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockTCParameter((m_szParameter[1] = ExtractText(m_szParameter[1]))))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryAreaBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREABLOCK_ILLEGALTCPARAMETER), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), GetBitOffset()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CheckAddress(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockAddress(m_nAddress[0], m_nAddress[1]))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryAreaBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREABLOCK_ILLEGALADDRESS), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), GetBitOffset()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CheckBitOffset(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockBitOffset(GetBitOffset()))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryAreaBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREABLOCK_ILLEGALBITOFFSET), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), GetBitOffset()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::CheckBitWidth(BOOL bStatus)
{
	UINT  nAddress[2];
	UINT  nRange[2][2];
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockBitWidth(GetBitWidth()))
	{
		for (GetDatabaseEngine()->GetOBProcessorMemoryAreaBlockAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREABLOCK_ILLEGALBITWIDTH), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[0], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), (GetAddress(nAddress[0], nAddress[1])) ? (LPCTSTR)cStringTools.ConvertUIntToPaddedString(nAddress[1], 4 * ((nRange[1][1] - nRange[1][0]) / 0x10000 + 1), 16) : STRING(IDS_DATABASE_TABLE_MEM_DATAADDRESS_NONE), GetBitOffset()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_MNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_TMNAME)), m_szParameter[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_TCNAME)), m_szParameter[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_PAGE)), m_nAddress[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_ADDRESS)), m_nAddress[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_BITOFF)), m_nBitOffset);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_WIDTH)), m_nBitWidth);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MEM_DESCR)), m_szDescription);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset)
	m_szName.Empty();
	m_szProcessor.Empty();
	m_szSeedValue.Empty();
	m_nAddress[0] = 0;
	m_nAddress[1] = 0;
	m_nAddress[2] = 0;
	m_nDestination = 0;
	m_nLength = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetSeed(UINT nValue)
{
	m_szSeedValue = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCheckSumSeedValue(nValue);
}

UINT CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetSeed() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCheckSumSeedValue(m_szSeedValue);
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetLength(INT nLength)
{
	m_nLength = nLength;
}

INT CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetLength() CONST
{
	return m_nLength;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetDestination(UINT nDestination)
{
	m_nDestination = nDestination;
}

UINT CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetDestination() CONST
{
	return m_nDestination;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetAddressRange(UINT nPage, UINT nStartAddress, UINT nEndAddress)
{
	m_nAddress[0] = nPage;
	m_nAddress[1] = nStartAddress;
	m_nAddress[2] = nEndAddress;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetAddressRange(UINT &nPage, UINT &nStartAddress, UINT &nEndAddress) CONST
{
	return GetDatabaseEngine()->CheckOBProcessorMemoryAreaCheckSumAddressRange((nPage = m_nAddress[0]), (nStartAddress = m_nAddress[1]), (nEndAddress = m_nAddress[2]));
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableErrorsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableWarningsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaCheckSum *pDatabaseOBProcessorMemoryAreaCheckSum)
{
	UINT  nAddress[3];

	SetName(pDatabaseOBProcessorMemoryArea->GetName());
	SetProcessor(pDatabaseOBProcessor->GetName());
	SetSeed(pDatabaseOBProcessorMemoryAreaCheckSum->GetSeed());
	SetLength(pDatabaseOBProcessorMemoryAreaCheckSum->GetLength());
	SetDestination(pDatabaseOBProcessorMemoryAreaCheckSum->GetDestination());
	for (nAddress[0] = nAddress[1] = nAddress[2] = 0; pDatabaseOBProcessorMemoryAreaCheckSum->GetAddressRange(nAddress[0], nAddress[1], nAddress[2]); )
	{
		SetAddressRange(nAddress[0], nAddress[1], nAddress[2]);
		break;
	}
	return((!pDatabaseOBProcessor->GetName().IsEmpty() && !pDatabaseOBProcessorMemoryArea->GetName().IsEmpty() && GetLength() > 0) ? TRUE : FALSE);
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(GetProcessor())))) ? (pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NONE || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NEW || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_CHANGED) : TRUE));
		CheckProcessor(bStatus);
		CheckSeed(bStatus);
		CheckLength(bStatus);
		CheckDestination(bStatus);
		CheckAddressRange(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckProcessor(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCheckSumName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACHECKSUM_ILLEGALNAME), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckProcessor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorName((m_szProcessor = ExtractText(m_szProcessor))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACHECKSUM_ILLEGALPROCESSORNAME), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckSeed(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCheckSumSeedValue((m_szSeedValue = ExtractText(m_szSeedValue))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACHECKSUM_ILLEGALSEEDVALUE), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckLength(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCheckSumLength(GetLength()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACHECKSUM_ILLEGALLENGTH), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckDestination(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCheckSumDestination(GetDestination()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACHECKSUM_ILLEGALDESTINATION), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckAddressRange(BOOL bStatus)
{
	UINT  nAddress[3];
	CString  szMessage;

	for (GetAddressRange(nAddress[0], nAddress[1], nAddress[2]); !GetDatabaseEngine()->CheckOBProcessorMemoryAreaCheckSumAddressRange(nAddress[0], nAddress[1], nAddress[2]); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACHECKSUM_ILLEGALADDRESSRANGE), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_PROCESSOR)), m_szProcessor);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_DEST)), m_nDestination);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_LENGTH)), m_nLength);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_PAGE)), m_nAddress[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_START)), m_nAddress[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_END)), m_nAddress[2]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CRC_SEED)), m_szSeedValue);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset)
	m_szID.Empty();
	m_szName.Empty();
	m_szProcessor.Empty();
	m_szDescription.Empty();
	m_szLocation.Empty();
	m_szVersion.Empty();
	m_szDate.Empty();
	m_szTime.Empty();
	m_szFlag.Empty();
	m_nFields = 8;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetID(LPCTSTR pszID)
{
	m_szID = pszID;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetID() CONST
{
	return m_szID;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetAttributes(UINT nAttributes)
{
	m_szFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCatalogueEntryFlag(nAttributes);
}

UINT CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCatalogueEntryFlag(m_szFlag);
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetLocation(LPCTSTR pszLocation)
{
	m_szLocation = pszLocation;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetLocation() CONST
{
	return m_szLocation;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetVersion(LPCTSTR pszVersion)
{
	m_szVersion = pszVersion;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetVersion() CONST
{
	return m_szVersion;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetDate(LPCTSTR pszDate)
{
	m_szDate = pszDate;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetDate() CONST
{
	return m_szDate;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::SetTime(LPCTSTR pszTime)
{
	m_szTime = pszTime;
}

CString CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::GetTime() CONST
{
	return m_szTime;
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableErrorsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	EnableWarningsByStatus(((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(pszName)))) ? pDatabaseOBProcessor->GetStatus() : OBPROCESSOR_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::Translate(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaCatalogueEntry *pDatabaseOBProcessorMemoryAreaCatalogueEntry)
{
	for (SetName(pDatabaseOBProcessorMemoryArea->GetName()), SetID(pDatabaseOBProcessorMemoryAreaCatalogueEntry->GetName()); GetID().IsEmpty(); )
	{
		SetID(pDatabaseOBProcessorMemoryArea->GetName());
		break;
	}
	SetDescription(pDatabaseOBProcessorMemoryAreaCatalogueEntry->GetDescription());
	SetAttributes(pDatabaseOBProcessorMemoryAreaCatalogueEntry->GetAttributes());
	SetLocation(pDatabaseOBProcessorMemoryAreaCatalogueEntry->GetLocation());
	SetVersion(pDatabaseOBProcessorMemoryAreaCatalogueEntry->GetVersion());
	SetDate(pDatabaseOBProcessorMemoryAreaCatalogueEntry->GetDate());
	SetTime(pDatabaseOBProcessorMemoryAreaCatalogueEntry->GetTime());
	return((!pDatabaseOBProcessorMemoryArea->GetName().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	INT  nProcessor;
	INT  nProcessors;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	if (nOperation == CFieldExchange::Fixup)
	{
		for (nProcessor = 0, nProcessors = (INT)GetDatabaseEngine()->GetOBProcessors()->GetSize(), SetProcessor(EMPTYSTRING); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(nProcessor)) && pDatabaseOBProcessor->Find(ExtractText(m_szName)) >= 0)
			{
				SetProcessor(pDatabaseOBProcessor->GetName());
				break;
			}
		}
		CheckID((bStatus = ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(GetDatabaseEngine()->GetOBProcessors()->Find(GetProcessor())))) ? (pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NONE || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_NEW || pDatabaseOBProcessor->GetStatus() == OBPROCESSOR_RECORDSTATUS_CHANGED) : TRUE));
		CheckName(bStatus);
		CheckDescription(bStatus);
		CheckAttributes(bStatus);
		CheckLocation(bStatus);
		CheckVersion(bStatus);
		CheckDate(bStatus);
		CheckTime(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		for (nProcessor = 0, nProcessors = (INT)GetDatabaseEngine()->GetOBProcessors()->GetSize(), SetProcessor(EMPTYSTRING); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = GetDatabaseEngine()->GetOBProcessors()->GetAt(nProcessor)) && pDatabaseOBProcessor->Find(ExtractText(m_szName)) >= 0)
			{
				SetProcessor(pDatabaseOBProcessor->GetName());
				break;
			}
		}
		bCheck = CheckID(IsCollectingIssues());
		bCheck &= CheckName(IsCollectingIssues());
		bCheck &= CheckVersion(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueEntryID((m_szID = ExtractText(m_szID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALID), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALNAME), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueEntryDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALDESCRIPTION), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueEntryFlag(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALFLAG), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckLocation(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueEntryLocation((m_szLocation = ExtractText(m_szLocation))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALLOCATION), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckVersion(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueEntryVersion((m_szVersion = ExtractText(m_szVersion))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALVERSION), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckDate(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueEntryDate((m_szDate = ExtractText(m_szDate))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALDATE), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckTime(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorMemoryAreaCatalogueEntryTime((m_szTime = ExtractText(m_szTime))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSORMEMORYAREACATALOGUE_ILLEGALTIME), (LPCTSTR)GetProcessor(), (LPCTSTR)GetName(), (LPCTSTR)GetVersion()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_ID)), m_szID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_VERSION)), m_szVersion);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_DATE)), m_szDate);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_TIME)), m_szTime);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_LOCATION)), m_szLocation);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAT_COMPLETE)), m_szFlag);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMParametersRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMParametersRecordset::CALTELDatabaseTMParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMParametersRecordset)
	m_szTag.Empty();
	m_szDescription.Empty();
	m_szUnit.Empty();
	m_szValidity.Empty();
	m_szCategory.Empty();
	m_szNature.Empty();
	m_szCoding.Empty();
	m_szInterpretation.Empty();
	m_szConsistency.Empty();
	m_szConstValue.Empty();
	m_szType.Empty();
	m_szDetails.Empty();
	m_szSubSystem[0].Empty();
	m_szEquipment[0].Empty();
	m_szSubSystem[1].Empty();
	m_szEquipment[1].Empty();
	m_szAssociatedTelecommands.Empty();
	m_szOperationalInfo.Empty();
	m_szValidityConditions.Empty();
	m_szDangerConditions.Empty();
	m_szRelatedParameter.Empty();
	m_szInterrogationInstruction.Empty();
	m_szDerivation.Empty();
	m_szTrigger.Empty();
	m_szTriggerType.Empty();
	m_szOBSType.Empty();
	m_szStatus.Empty();
	m_nBitWidth = 0;
	m_nFields = 28;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTMParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTMParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTMParametersRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTMParametersRecordset::SetDetails(LPCTSTR pszDetails)
{
	m_szDetails = pszDetails;
}

CString CALTELDatabaseTMParametersRecordset::GetDetails() CONST
{
	return m_szDetails;
}

VOID CALTELDatabaseTMParametersRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CALTELDatabaseTMParametersRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CALTELDatabaseTMParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTMParameterType(nAttributes);
	m_szOBSType = GetDatabaseEngine()->TranslateTMParameterOBSType(nAttributes);
	m_szCategory = GetDatabaseEngine()->TranslateTMParameterCategory(nAttributes);
	m_szNature = GetDatabaseEngine()->TranslateTMParameterNature(nAttributes);
	m_szCoding = GetDatabaseEngine()->TranslateTMParameterCoding(nAttributes);
	m_szInterpretation = GetDatabaseEngine()->TranslateTMParameterInterpretation(nAttributes);
	m_szTriggerType = GetDatabaseEngine()->TranslateTMParameterTriggerType(nAttributes);
	m_szConsistency = GetDatabaseEngine()->TranslateTMParameterConsistencyChecksFlag(nAttributes);
}

ULONGLONG CALTELDatabaseTMParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTMParameterType(m_szType) | GetDatabaseEngine()->TranslateTMParameterOBSType(m_szOBSType) | GetDatabaseEngine()->TranslateTMParameterCategory(m_szCategory) | GetDatabaseEngine()->TranslateTMParameterNature(m_szNature) | GetDatabaseEngine()->TranslateTMParameterCoding(m_szCoding) | GetDatabaseEngine()->TranslateTMParameterInterpretation(m_szInterpretation) | GetDatabaseEngine()->TranslateTMParameterTriggerType(m_szTriggerType) | GetDatabaseEngine()->TranslateTMParameterConsistencyChecksFlag(m_szConsistency);
}

VOID CALTELDatabaseTMParametersRecordset::SetBitWidth(INT nWidth)
{
	m_nBitWidth = nWidth;
}

INT CALTELDatabaseTMParametersRecordset::GetBitWidth() CONST
{
	return m_nBitWidth;
}

VOID CALTELDatabaseTMParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szConstValue = pszConstValue;
}

CString CALTELDatabaseTMParametersRecordset::GetConstValue() CONST
{
	return m_szConstValue;
}

VOID CALTELDatabaseTMParametersRecordset::SetRelatedParameter(LPCTSTR pszParameter)
{
	m_szRelatedParameter = pszParameter;
}

CString CALTELDatabaseTMParametersRecordset::GetRelatedParameter() CONST
{
	return GetDatabaseEngine()->TranslateTMParameterRelatedParameter(m_szRelatedParameter);
}

VOID CALTELDatabaseTMParametersRecordset::SetValidityParameter(LPCTSTR pszParameter)
{
	m_szValidity = pszParameter;
}

CString CALTELDatabaseTMParametersRecordset::GetValidityParameter() CONST
{
	return m_szValidity;
}

VOID CALTELDatabaseTMParametersRecordset::SetDerivationExpression(LPCTSTR pszExpression)
{
	m_szDerivation = pszExpression;
}

CString CALTELDatabaseTMParametersRecordset::GetDerivationExpression() CONST
{
	return m_szDerivation;
}

VOID CALTELDatabaseTMParametersRecordset::SetTriggerExpression(LPCTSTR pszTrigger)
{
	m_szTrigger = pszTrigger;
}

CString CALTELDatabaseTMParametersRecordset::GetTriggerExpression() CONST
{
	return GetDatabaseEngine()->TranslateTMParameterTriggerExpression(m_szTrigger);
}

VOID CALTELDatabaseTMParametersRecordset::SetSourceSubSystem(LPCTSTR pszSubSystem)
{
	m_szSubSystem[0] = pszSubSystem;
}

CString CALTELDatabaseTMParametersRecordset::GetSourceSubSystem() CONST
{
	return m_szSubSystem[0];
}

VOID CALTELDatabaseTMParametersRecordset::SetSourceEquipment(LPCTSTR pszEquipment)
{
	m_szEquipment[0] = pszEquipment;
}

CString CALTELDatabaseTMParametersRecordset::GetSourceEquipment() CONST
{
	return m_szEquipment[0];
}

VOID CALTELDatabaseTMParametersRecordset::SetRouterSubSystem(LPCTSTR pszSubSystem)
{
	m_szSubSystem[1] = pszSubSystem;
}

CString CALTELDatabaseTMParametersRecordset::GetRouterSubSystem() CONST
{
	return m_szSubSystem[1];
}

VOID CALTELDatabaseTMParametersRecordset::SetRouterEquipment(LPCTSTR pszEquipment)
{
	m_szEquipment[1] = pszEquipment;
}

CString CALTELDatabaseTMParametersRecordset::GetRouterEquipment() CONST
{
	return m_szEquipment[1];
}

VOID CALTELDatabaseTMParametersRecordset::SetOperationalInfo(LPCTSTR pszInfo)
{
	m_szOperationalInfo = pszInfo;
}

CString CALTELDatabaseTMParametersRecordset::GetOperationalInfo() CONST
{
	return m_szOperationalInfo;
}

VOID CALTELDatabaseTMParametersRecordset::SetDangerConditions(LPCTSTR pszConditions)
{
	m_szDangerConditions = pszConditions;
}

CString CALTELDatabaseTMParametersRecordset::GetDangerConditions() CONST
{
	return m_szDangerConditions;
}

VOID CALTELDatabaseTMParametersRecordset::SetValidityConditions(LPCTSTR pszConditions)
{
	m_szValidityConditions = pszConditions;
}

CString CALTELDatabaseTMParametersRecordset::GetValidityConditions() CONST
{
	return m_szValidityConditions;
}

VOID CALTELDatabaseTMParametersRecordset::SetAssociatedTelecommands(LPCTSTR pszTelecommands)
{
	m_szAssociatedTelecommands = pszTelecommands;
}

CString CALTELDatabaseTMParametersRecordset::GetAssociatedTelecommands() CONST
{
	return m_szAssociatedTelecommands;
}

VOID CALTELDatabaseTMParametersRecordset::SetInterrogationInstruction(UINT nInstruction)
{
	m_szInterrogationInstruction = GetDatabaseEngine()->TranslateTMParameterInterrogationInstruction(nInstruction);
}

UINT CALTELDatabaseTMParametersRecordset::GetInterrogationInstruction() CONST
{
	return GetDatabaseEngine()->TranslateTMParameterInterrogationInstruction(m_szInterrogationInstruction);
}

VOID CALTELDatabaseTMParametersRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTMParameterStatus(nStatus);
}

INT CALTELDatabaseTMParametersRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTMParameterStatus(m_szStatus);
}

VOID CALTELDatabaseTMParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szTag), pszError);
}
VOID CALTELDatabaseTMParametersRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CDatabaseTMParameter  *pDatabaseTMParameter;

	EnableErrorsByStatus(((pDatabaseTMParameter = GetDatabaseEngine()->GetTMParameters()->GetAt(GetDatabaseEngine()->GetTMParameters()->Find(pszTag)))) ? pDatabaseTMParameter->GetStatus() : TMPARAMETER_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszTag, pszTag, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szTag), pszWarning);
}
VOID CALTELDatabaseTMParametersRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CDatabaseTMParameter  *pDatabaseTMParameter;

	EnableWarningsByStatus(((pDatabaseTMParameter = GetDatabaseEngine()->GetTMParameters()->GetAt(GetDatabaseEngine()->GetTMParameters()->Find(pszTag)))) ? pDatabaseTMParameter->GetStatus() : TMPARAMETER_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszTag, pszTag, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMParametersRecordset::Translate(CONST CDatabaseTMParameter *pDatabaseTMParameter)
{
	SetTag(pDatabaseTMParameter->GetTag());
	SetDescription(pDatabaseTMParameter->GetDescription());
	SetDetails(pDatabaseTMParameter->GetDetails());
	SetUnit(pDatabaseTMParameter->GetUnit());
	SetAttributes(pDatabaseTMParameter->GetAttributes());
	SetBitWidth(pDatabaseTMParameter->GetWidth());
	SetConstValue(pDatabaseTMParameter->GetConstValueAsText());
	SetRelatedParameter(pDatabaseTMParameter->GetRelatedParameter());
	SetValidityParameter(pDatabaseTMParameter->GetValidityParameter());
	SetDerivationExpression(pDatabaseTMParameter->GetDerivationExpression());
	SetTriggerExpression(pDatabaseTMParameter->GetTriggerExpression());
	SetSourceSubSystem(pDatabaseTMParameter->GetSourceSubSystem());
	SetSourceEquipment(pDatabaseTMParameter->GetSourceEquipment());
	SetRouterSubSystem(pDatabaseTMParameter->GetRouterSubSystem());
	SetRouterEquipment(pDatabaseTMParameter->GetRouterEquipment());
	SetOperationalInfo(pDatabaseTMParameter->GetOperationalInfo());
	SetDangerConditions(pDatabaseTMParameter->GetDangerConditions());
	SetValidityConditions(pDatabaseTMParameter->GetValidityConditions());
	SetAssociatedTelecommands(pDatabaseTMParameter->GetAssociatedTelecommands());
	SetInterrogationInstruction(pDatabaseTMParameter->GetInterrogationInstruction());
	SetStatus(pDatabaseTMParameter->GetStatus());
}

BOOL CALTELDatabaseTMParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = (GetStatus() == TMPARAMETER_RECORDSTATUS_NONE || GetStatus() == TMPARAMETER_RECORDSTATUS_NEW || GetStatus() == TMPARAMETER_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckDetails(bStatus);
		CheckUnit(bStatus);
		CheckAttributes(bStatus);
		CheckBitWidth(bStatus);
		CheckConstValue(bStatus);
		CheckRelatedParameter(bStatus);
		CheckValidityParameter(bStatus);
		CheckTriggerExpression(bStatus);
		CheckDerivationExpression(bStatus);
		CheckSourceSubSystem(bStatus);
		CheckSourceEquipment(bStatus);
		CheckRouterSubSystem(bStatus);
		CheckRouterEquipment(bStatus);
		CheckOperationalInfo(bStatus);
		CheckDangerConditions(bStatus);
		CheckValidityConditions(bStatus);
		CheckAssociatedTelecommands(bStatus);
		CheckInterrogationInstruction(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALTAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALDESCRIPTION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckDetails(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterDetails((m_szDetails = ExtractText(m_szDetails))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALDETAILS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckUnit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterUnit((m_szUnit = ExtractText(m_szUnit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALUNIT), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTMParameterType((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALTYPE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterCategory(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALCATEGORY), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterOBSType(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALOBSTYPE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterNature(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALNATURE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterCoding(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALCODING), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterInterpretation(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALINTERPRETATION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterTriggerType(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALTRIGGERTYPE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterConsistencyChecksFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALCONSISTENCYCHECKSFLAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTMParametersRecordset::CheckBitWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterBitWidth(GetAttributes(), GetBitWidth()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALBITWIDTH), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterConstValue(GetAttributes(), (m_szConstValue = ExtractText(m_szConstValue))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALCONSTVALUE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckRelatedParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterRelatedParameter((m_szRelatedParameter = ExtractText(m_szRelatedParameter))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALALTERNATIVEPARAMETER), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityParameter((m_szValidity = ExtractText(m_szValidity))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckTriggerExpression(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTriggerExpression(GetAttributes(), GetAttributes(), (m_szTrigger = ExtractText(m_szTrigger))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALTRIGGEREXPRESSION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckDerivationExpression(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterDerivationExpression((m_szDerivation = ExtractText(m_szDerivation))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALDERIVATIONEXPRESSION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckSourceSubSystem(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterSourceSubSystem((m_szSubSystem[0] = ExtractText(m_szSubSystem[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALSOURCESUBSYSTEM), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckSourceEquipment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterSourceEquipment((m_szEquipment[0] = ExtractText(m_szEquipment[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALSOURCEEQUIPMENT), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckRouterSubSystem(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterRouterSubSystem((m_szSubSystem[1] = ExtractText(m_szSubSystem[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALROUTERSUBSYSTEM), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckRouterEquipment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterRouterEquipment((m_szEquipment[1] = ExtractText(m_szEquipment[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALROUTEREQUIPMENT), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckOperationalInfo(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterOperationalInfo((m_szOperationalInfo = ExtractText(m_szOperationalInfo))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALOPERATIONALINFO), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckDangerConditions(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterDangerConditions((m_szDangerConditions = ExtractText(m_szDangerConditions))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALDANGERCONDITIONS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckValidityConditions(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityConditions((m_szValidityConditions = ExtractText(m_szValidityConditions))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALVALIDITYCONDITIONS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckAssociatedTelecommands(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterAssociatedTelecommands((m_szAssociatedTelecommands = ExtractText(m_szAssociatedTelecommands))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALASSOCIATEDTELECOMMANDS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckInterrogationInstruction(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterInterrogationInstruction((m_szInterrogationInstruction = ExtractText(m_szInterrogationInstruction))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALINTERROGATIONINSTRUCTION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMParametersRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALSTATUS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_NAME)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_UNIT)), m_szUnit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_VALID)), m_szValidity);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_CATEG)), m_szCategory);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_WIDTH)), m_nBitWidth);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_NATURE)), m_szNature);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_CODING)), m_szCoding);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_INTER)), m_szInterpretation);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_USECON)), m_szConsistency);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_PARVAL)), m_szConstValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_LDESC)), m_szDetails);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_SOURS)), m_szSubSystem[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_SOURU)), m_szEquipment[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_ROUTS)), m_szSubSystem[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_ROUTU)), m_szEquipment[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_ASTC)), m_szAssociatedTelecommands);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_OPINFO)), m_szOperationalInfo);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_APPLC)), m_szValidityConditions);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_MONIT)), m_szDangerConditions);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_ALTM)), m_szRelatedParameter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_INTM)), m_szInterrogationInstruction);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_DRVEXP)), m_szDerivation, GetDatabaseEngine()->GetTMParameterDerivationExpressionLength());
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_EXPTRG)), m_szTrigger);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_TRGTYP)), m_szTriggerType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_OBSPAR)), m_szOBSType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMNumCalTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMNumCalTablesRecordset::CALTELDatabaseTMNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMNumCalTablesRecordset)
	m_szName.Empty();
	m_szDescription.Empty();
	m_szUnit.Empty();
	m_szStatus.Empty();
	m_nPoints = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMNumCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMNumCalTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMNumCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTMNumCalTablesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTMNumCalTablesRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CALTELDatabaseTMNumCalTablesRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CALTELDatabaseTMNumCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nPoints = nPoints;
}

INT CALTELDatabaseTMNumCalTablesRecordset::GetPoints() CONST
{
	return m_nPoints;
}

VOID CALTELDatabaseTMNumCalTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTMNumCalTableStatus(nStatus);
}

INT CALTELDatabaseTMNumCalTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTMNumCalTableStatus(m_szStatus);
}

VOID CALTELDatabaseTMNumCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMNumCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	EnableErrorsByStatus(((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(pszName)))) ? pDatabaseTMNumCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMNumCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMNumCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	EnableWarningsByStatus(((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(pszName)))) ? pDatabaseTMNumCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMNumCalTablesRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable)
{
	SetName(pDatabaseTMNumCalTable->GetName());
	SetDescription(pDatabaseTMNumCalTable->GetDescription());
	SetUnit(pDatabaseTMNumCalTable->GetUnit());
	SetPoints(pDatabaseTMNumCalTable->GetPoints());
	SetStatus(pDatabaseTMNumCalTable->GetStatus());
}

BOOL CALTELDatabaseTMNumCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMNumCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TMCALTABLE_RECORDSTATUS_NONE || GetStatus() == TMCALTABLE_RECORDSTATUS_NEW || GetStatus() == TMCALTABLE_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckUnit(bStatus);
		CheckPoints(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckPoints(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTablesRecordset::CheckUnit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableUnit((m_szUnit = ExtractText(m_szUnit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALUNIT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTablesRecordset::CheckPoints(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTablePoints(GetPoints()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALNUMBEROFPOINTS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMNumCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMNumCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_UNIT)), m_szUnit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_NBPNT)), m_nPoints);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMNumCalTablePointsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMNumCalTablePointsRecordset::CALTELDatabaseTMNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMNumCalTablePointsRecordset)
	m_szName.Empty();
	m_fX = 0.0;
	m_fY = 0.0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMNumCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMNumCalTablePointsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMNumCalTablePointsRecordset::SetX(double fX)
{
	m_fX = fX;
}

double CALTELDatabaseTMNumCalTablePointsRecordset::GetX() CONST
{
	return m_fX;
}

VOID CALTELDatabaseTMNumCalTablePointsRecordset::SetY(double fY)
{
	m_fY = fY;
}

double CALTELDatabaseTMNumCalTablePointsRecordset::GetY() CONST
{
	return m_fY;
}

VOID CALTELDatabaseTMNumCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMNumCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	EnableErrorsByStatus(((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(pszName)))) ? pDatabaseTMNumCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	EnableWarningsByStatus(((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(pszName)))) ? pDatabaseTMNumCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMNumCalTablePointsRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CONST CDatabaseTMNumCalPoint *pDatabaseTMNumCalPoint)
{
	SetName(pDatabaseTMNumCalTable->GetName());
	SetX(pDatabaseTMNumCalPoint->GetX());
	SetY(pDatabaseTMNumCalPoint->GetY());
}

BOOL CALTELDatabaseTMNumCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMNumCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(GetName())))) ? (pDatabaseTMNumCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NONE || pDatabaseTMNumCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NEW || pDatabaseTMNumCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckPoint(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckPoint(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEPOINT_ILLEGALNAME), (LPCTSTR)GetName(), GetX()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage;

	if (isnan(GetX()) || isnan(GetY()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEPOINT_ILLEGALRAWVALUE), (LPCTSTR)GetName()); isnan(GetX()); )
		{
			ShowError(szMessage);
			break;
		}
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEPOINT_ILLEGALENGVALUE), (LPCTSTR)GetName()); isnan(GetY()); )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMNumCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMNumCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CALP_NAME)), m_szName);
	RFX_Double(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CALP_XVAL)), m_fX);
	RFX_Double(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CALP_YVAL)), m_fY);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumCalTableAssociationsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMNumCalTableAssociationsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMNumCalTableAssociationsRecordset::CALTELDatabaseTMNumCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMNumCalTableAssociationsRecordset)
	m_szName.Empty();
	m_szParameter[0].Empty();
	m_szParameter[1].Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMNumCalTableAssociationsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szParameter[0] = pszTag;
}

CString CALTELDatabaseTMNumCalTableAssociationsRecordset::GetParameter() CONST
{
	return m_szParameter[0];
}

VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::SetValidityParameter(LPCTSTR pszTag)
{
	m_szParameter[1] = pszTag;
}

CString CALTELDatabaseTMNumCalTableAssociationsRecordset::GetValidityParameter() CONST
{
	return m_szParameter[1];
}

VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	EnableErrorsByStatus(((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(pszName)))) ? pDatabaseTMNumCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	EnableWarningsByStatus(((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(pszName)))) ? pDatabaseTMNumCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMNumCalTableAssociationsRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter)
{
	SetName(pDatabaseTMNumCalTable->GetName());
	SetParameter(pDatabaseTMParameter->GetTag());
	SetValidityParameter(pszValidityParameter);
}

BOOL CALTELDatabaseTMNumCalTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMNumCalTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(GetName())))) ? (pDatabaseTMNumCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NONE || pDatabaseTMNumCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NEW || pDatabaseTMNumCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckParameter(bStatus);
		CheckValidityParameter(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTableAssociationsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTableAssociationsRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szParameter[0] = ExtractText(m_szParameter[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumCalTableAssociationsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityParameter((m_szParameter[1] = ExtractText(m_szParameter[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMNumCalTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMNumCalTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCAL_CNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCAL_PNAME)), m_szParameter[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCAL_VALID)), m_szParameter[1]);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMTxtCalTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMTxtCalTablesRecordset::CALTELDatabaseTMTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMTxtCalTablesRecordset)
	m_szName.Empty();
	m_szDescription.Empty();
	m_szStatus.Empty();
	m_nPoints = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMTxtCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMTxtCalTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMTxtCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTMTxtCalTablesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTMTxtCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nPoints = nPoints;
}

INT CALTELDatabaseTMTxtCalTablesRecordset::GetPoints() CONST
{
	return m_nPoints;
}

VOID CALTELDatabaseTMTxtCalTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTMTxtCalTableStatus(nStatus);
}

INT CALTELDatabaseTMTxtCalTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTMTxtCalTableStatus(m_szStatus);
}

VOID CALTELDatabaseTMTxtCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMTxtCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	EnableErrorsByStatus(((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(pszName)))) ? pDatabaseTMTxtCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMTxtCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMTxtCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	EnableWarningsByStatus(((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(pszName)))) ? pDatabaseTMTxtCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMTxtCalTablesRecordset::Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable)
{
	SetName(pDatabaseTMTxtCalTable->GetName());
	SetDescription(pDatabaseTMTxtCalTable->GetDescription());
	SetPoints(pDatabaseTMTxtCalTable->GetPoints());
	SetStatus(pDatabaseTMTxtCalTable->GetStatus());
}

BOOL CALTELDatabaseTMTxtCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMTxtCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TMCALTABLE_RECORDSTATUS_NONE || GetStatus() == TMCALTABLE_RECORDSTATUS_NEW || GetStatus() == TMCALTABLE_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckPoints(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckPoints(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTablesRecordset::CheckPoints(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTablePoints(GetPoints()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLE_ILLEGALNUMBEROFPOINTS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMTxtCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMTxtCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_NBTXT)), m_nPoints);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMTxtCalTablePointsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMTxtCalTablePointsRecordset::CALTELDatabaseTMTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMTxtCalTablePointsRecordset)
	m_szName.Empty();
	m_szText.Empty();
	m_nX1 = 0;
	m_nX2 = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMTxtCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMTxtCalTablePointsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMTxtCalTablePointsRecordset::SetText(LPCTSTR pszText)
{
	m_szText = pszText;
}

CString CALTELDatabaseTMTxtCalTablePointsRecordset::GetText() CONST
{
	return m_szText;
}

VOID CALTELDatabaseTMTxtCalTablePointsRecordset::SetX1(INT nX1)
{
	m_nX1 = nX1;
}

INT CALTELDatabaseTMTxtCalTablePointsRecordset::GetX1() CONST
{
	return m_nX1;
}

VOID CALTELDatabaseTMTxtCalTablePointsRecordset::SetX2(INT nX2)
{
	m_nX2 = nX2;
}

INT CALTELDatabaseTMTxtCalTablePointsRecordset::GetX2() CONST
{
	return m_nX2;
}

VOID CALTELDatabaseTMTxtCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMTxtCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	EnableErrorsByStatus(((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(pszName)))) ? pDatabaseTMTxtCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	EnableWarningsByStatus(((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(pszName)))) ? pDatabaseTMTxtCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMTxtCalTablePointsRecordset::Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CONST CDatabaseTMTxtCalPoint *pDatabaseTMTxtCalPoint)
{
	double  fX[2];
	CString  szY;

	for (SetName(pDatabaseTMTxtCalTable->GetName()), pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szY), SetX1(0), SetX2(-1), SetText(szY); !isnan(fX[0]) && !isnan(fX[1]); )
	{
		SetX1((INT)fX[0]);
		SetX2((INT)fX[1]);
		break;
	}
}

BOOL CALTELDatabaseTMTxtCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMTxtCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(GetName())))) ? (pDatabaseTMTxtCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NONE || pDatabaseTMTxtCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NEW || pDatabaseTMTxtCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckPoint(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckPoint(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage[2];

	if (!GetDatabaseEngine()->CheckTMTxtCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage[0].Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_ILLEGALNAMEATPOINT), (LPCTSTR)GetName(), GetX1(), (LPCTSTR)ExtractText(GetText())), szMessage[1].Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_ILLEGALNAMEATRANGE), (LPCTSTR)GetName(), GetX1(), GetX2(), (LPCTSTR)ExtractText(GetText())); bStatus; )
		{
			ShowError((GetX1() == GetX2()) ? szMessage[0] : szMessage[1]);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage[2];

	if (!GetDatabaseEngine()->CheckTMTxtCalTablePointText((m_szText = ExtractText(m_szText))) || !GetDatabaseEngine()->CheckTMTxtCalTablePointInterval(GetX1(), GetX2()))
	{
		for (szMessage[0].Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_SYNTAXERRORATPOINT), (LPCTSTR)GetName(), GetX1(), (LPCTSTR)ExtractText(GetText())), szMessage[1].Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_SYNTAXERRORATRANGE), (LPCTSTR)GetName(), GetX1(), GetX2(), (LPCTSTR)ExtractText(GetText())); bStatus; )
		{
			ShowError((GetX1() == GetX2()) ? szMessage[0] : szMessage[1]);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMTxtCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMTxtCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_FROM)), m_nX1);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_TO)), m_nX2);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_TEXT)), m_szText);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtCalTableAssociationsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMTxtCalTableAssociationsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMTxtCalTableAssociationsRecordset::CALTELDatabaseTMTxtCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMTxtCalTableAssociationsRecordset)
	m_szName.Empty();
	m_szParameter[0].Empty();
	m_szParameter[1].Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMTxtCalTableAssociationsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szParameter[0] = pszTag;
}

CString CALTELDatabaseTMTxtCalTableAssociationsRecordset::GetParameter() CONST
{
	return m_szParameter[0];
}

VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::SetValidityParameter(LPCTSTR pszTag)
{
	m_szParameter[1] = pszTag;
}

CString CALTELDatabaseTMTxtCalTableAssociationsRecordset::GetValidityParameter() CONST
{
	return m_szParameter[1];
}

VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	EnableErrorsByStatus(((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(pszName)))) ? pDatabaseTMTxtCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	EnableWarningsByStatus(((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(pszName)))) ? pDatabaseTMTxtCalTable->GetStatus() : TMCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMTxtCalTableAssociationsRecordset::Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter)
{
	SetName(pDatabaseTMTxtCalTable->GetName());
	SetParameter(pDatabaseTMParameter->GetTag());
	SetValidityParameter(pszValidityParameter);
}

BOOL CALTELDatabaseTMTxtCalTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMTxtCalTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(GetName())))) ? (pDatabaseTMTxtCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NONE || pDatabaseTMTxtCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_NEW || pDatabaseTMTxtCalTable->GetStatus() == TMCALTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckParameter(bStatus);
		CheckValidityParameter(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTableAssociationsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTableAssociationsRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szParameter[0] = ExtractText(m_szParameter[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtCalTableAssociationsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityParameter((m_szParameter[1] = ExtractText(m_szParameter[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMTxtCalTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMTxtCalTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PTXF_CNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PTXF_PNAME)), m_szParameter[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PTXF_VALID)), m_szParameter[1]);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumOolTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMNumOolTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMNumOolTablesRecordset::CALTELDatabaseTMNumOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMNumOolTablesRecordset)
	m_szName.Empty();
	m_szInterpretation.Empty();
	m_szCoding.Empty();
	m_szRadix.Empty();
	m_nChecks = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMNumOolTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMNumOolTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMNumOolTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szInterpretation = GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(nAttributes);
	m_szCoding = GetDatabaseEngine()->TranslateTMNumOolTableCoding(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTMNumOolTableRadix(nAttributes);
}

UINT CALTELDatabaseTMNumOolTablesRecordset::GetAttributes() CONST
{
	UINT  nInterpretation;

	return(((nInterpretation = GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(m_szInterpretation)) & TMOOLTABLE_CHECK_RAW) ? (nInterpretation | GetDatabaseEngine()->TranslateTMNumOolTableCoding(GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(m_szInterpretation), m_szCoding) | GetDatabaseEngine()->TranslateTMNumOolTableRadix(GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(m_szInterpretation), m_szRadix)) : (nInterpretation | TMOOLTABLE_CODING_FLOATINGPOINT | TMOOLTABLE_RADIX_DECIMAL));
}

VOID CALTELDatabaseTMNumOolTablesRecordset::SetChecks(INT nChecks)
{
	m_nChecks = nChecks;
}

INT CALTELDatabaseTMNumOolTablesRecordset::GetChecks() CONST
{
	return m_nChecks;
}

VOID CALTELDatabaseTMNumOolTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTMNumOolTableStatus(nStatus);
}

INT CALTELDatabaseTMNumOolTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTMNumOolTableStatus(m_szStatus);
}

VOID CALTELDatabaseTMNumOolTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMNumOolTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	EnableErrorsByStatus(((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(pszName)))) ? pDatabaseTMNumOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMNumOolTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMNumOolTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	EnableWarningsByStatus(((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(pszName)))) ? pDatabaseTMNumOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMNumOolTablesRecordset::Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable)
{
	SetName(pDatabaseTMNumOolTable->GetName());
	SetAttributes(pDatabaseTMNumOolTable->GetAttributes());
	SetChecks(pDatabaseTMNumOolTable->GetChecks());
	SetStatus(pDatabaseTMNumOolTable->GetStatus());
}

BOOL CALTELDatabaseTMNumOolTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMNumOolTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((GetStatus() == TMOOLTABLE_RECORDSTATUS_NONE || GetStatus() == TMOOLTABLE_RECORDSTATUS_NEW || GetStatus() == TMOOLTABLE_RECORDSTATUS_CHANGED) && !GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInterpretation))));
		CheckAttributes(bStatus);
		CheckCount(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckCount(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTablesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableInterpretation(GetAttributes()) && !GetDatabaseEngine()->CheckTCNumOolTableInterpretation(GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInterpretation)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLE_ILLEGALINTERPRETATION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumOolTableCoding(GetAttributes(), GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLE_ILLEGALCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumOolTableRadix(GetAttributes(), GetAttributes(), GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLE_ILLEGALRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTMNumOolTablesRecordset::CheckCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableCheckCount(GetChecks()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLE_ILLEGALCHECKS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMNumOolTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMNumOolTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_ONAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_INTER)), m_szInterpretation);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_CODING)), m_szCoding);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_RADIX)), m_szRadix);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NBCHECK)), m_nChecks);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMNumOolTableLimitsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMNumOolTableLimitsRecordset::CALTELDatabaseTMNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMNumOolTableLimitsRecordset)
	m_szName.Empty();
	m_szLowLimit.Empty();
	m_szHighLimit.Empty();
	m_nOrder = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMNumOolTableLimitsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::SetOrder(INT nOrder)
{
	m_nOrder = nOrder;
}

INT CALTELDatabaseTMNumOolTableLimitsRecordset::GetOrder() CONST
{
	return m_nOrder;
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CALTELDatabaseTMNumOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::SetLowLimit(double fLowLimit)
{
	m_szLowLimit = (!isnan(fLowLimit)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), fLowLimit) : EMPTYSTRING;
}

double CALTELDatabaseTMNumOolTableLimitsRecordset::GetLowLimit() CONST
{
	return((GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), m_szLowLimit)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), m_szLowLimit) : NAN);
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::SetHighLimit(double fHighLimit)
{
	m_szHighLimit = (!isnan(fHighLimit)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), fHighLimit) : EMPTYSTRING;
}

double CALTELDatabaseTMNumOolTableLimitsRecordset::GetHighLimit() CONST
{
	return((GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), m_szHighLimit)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), m_szHighLimit) : NAN);
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMNumOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	EnableErrorsByStatus(((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(pszName)))) ? pDatabaseTMNumOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	EnableWarningsByStatus(((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(pszName)))) ? pDatabaseTMNumOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMNumOolTableLimitsRecordset::Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CONST CDatabaseTMNumOolLimit *pDatabaseTMNumOolLimit)
{
	UINT  nType;
	double  fDelta;
	double  fRange[2];

	for (SetName(pDatabaseTMNumOolTable->GetName()), SetOrder(pDatabaseTMNumOolLimit->GetType()), SetAttributes(pDatabaseTMNumOolTable->GetAttributes()), fRange[0] = fRange[1] = 0.0; !pDatabaseTMNumOolLimit->GetRange(nType, fRange[0], fRange[1]) && pDatabaseTMNumOolLimit->GetDelta(fDelta); )
	{
		fRange[0] = fDelta;
		fRange[1] = fDelta;
		break;
	}
	SetLowLimit(fRange[0]);
	SetHighLimit(fRange[1]);
}

BOOL CALTELDatabaseTMNumOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMNumOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(GetName()))))
		{
			for (SetAttributes(pDatabaseTMNumOolTable->GetAttributes()), bStatus = FALSE; pDatabaseTMNumOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NONE || pDatabaseTMNumOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NEW || pDatabaseTMNumOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_CHANGED; )
			{
				bStatus = TRUE;
				break;
			}
			CheckName(bStatus);
			CheckLimits(bStatus);
			CheckOrder(bStatus);
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckLimits(IsCollectingIssues());
		bCheck &= CheckOrder(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTableLimitsRecordset::CheckLimits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), (m_szLowLimit = ExtractText(m_szLowLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), (m_szHighLimit = ExtractText(m_szHighLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTMNumOolTableLimitsRecordset::CheckOrder(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableLimitOrder(m_nOrder))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALLIMITORDER), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMNumOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMNumOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_ONAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_LVALUE)), m_szLowLimit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_HVALUE)), m_szHighLimit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_ORDER)), m_nOrder);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumOolTableAssociationsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMNumOolTableAssociationsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMNumOolTableAssociationsRecordset::CALTELDatabaseTMNumOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMNumOolTableAssociationsRecordset)
	m_szName.Empty();
	m_szParameter[0].Empty();
	m_szParameter[1].Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMNumOolTableAssociationsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szParameter[0] = pszTag;
}

CString CALTELDatabaseTMNumOolTableAssociationsRecordset::GetParameter() CONST
{
	return m_szParameter[0];
}

VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::SetValidityParameter(LPCTSTR pszTag)
{
	m_szParameter[1] = pszTag;
}

CString CALTELDatabaseTMNumOolTableAssociationsRecordset::GetValidityParameter() CONST
{
	return m_szParameter[1];
}

VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	EnableErrorsByStatus(((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(pszName)))) ? pDatabaseTMNumOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	EnableWarningsByStatus(((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(pszName)))) ? pDatabaseTMNumOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMNumOolTableAssociationsRecordset::Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter)
{
	SetName(pDatabaseTMNumOolTable->GetName());
	SetParameter(pDatabaseTMParameter->GetTag());
	SetValidityParameter(pszValidityParameter);
}

BOOL CALTELDatabaseTMNumOolTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMNumOolTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find(GetName())))) ? (pDatabaseTMNumOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NONE || pDatabaseTMNumOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NEW || pDatabaseTMNumOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckParameter(bStatus);
		CheckValidityParameter(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTableAssociationsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTableAssociationsRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szParameter[0] = ExtractText(m_szParameter[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMNumOolTableAssociationsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityParameter((m_szParameter[1] = ExtractText(m_szParameter[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMNumOolTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMNumOolTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_POCF_ONAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_POCF_PNAME)), m_szParameter[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_POCF_VALID)), m_szParameter[1]);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtOolTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMTxtOolTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMTxtOolTablesRecordset::CALTELDatabaseTMTxtOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMTxtOolTablesRecordset)
	m_szName.Empty();
	m_szInterpretation.Empty();
	m_szRadix.Empty();
	m_nChecks = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMTxtOolTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMTxtOolTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMTxtOolTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szInterpretation = GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTMTxtOolTableRadix(nAttributes);
}

UINT CALTELDatabaseTMTxtOolTablesRecordset::GetAttributes() CONST
{
	UINT  nInterpretation;

	return(((nInterpretation = GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(m_szInterpretation)) & TMOOLTABLE_CHECK_RAW) ? (nInterpretation | GetDatabaseEngine()->TranslateTMTxtOolTableRadix(GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(m_szInterpretation), m_szRadix)) : nInterpretation);
}

VOID CALTELDatabaseTMTxtOolTablesRecordset::SetChecks(INT nChecks)
{
	m_nChecks = nChecks;
}

INT CALTELDatabaseTMTxtOolTablesRecordset::GetChecks() CONST
{
	return m_nChecks;
}

VOID CALTELDatabaseTMTxtOolTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTMTxtOolTableStatus(nStatus);
}

INT CALTELDatabaseTMTxtOolTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTMTxtOolTableStatus(m_szStatus);
}

VOID CALTELDatabaseTMTxtOolTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMTxtOolTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	EnableErrorsByStatus(((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(pszName)))) ? pDatabaseTMTxtOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMTxtOolTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMTxtOolTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	EnableWarningsByStatus(((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(pszName)))) ? pDatabaseTMTxtOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMTxtOolTablesRecordset::Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable)
{
	SetName(pDatabaseTMTxtOolTable->GetName());
	SetAttributes(pDatabaseTMTxtOolTable->GetAttributes());
	SetChecks(pDatabaseTMTxtOolTable->GetChecks());
	SetStatus(pDatabaseTMTxtOolTable->GetStatus());
}

BOOL CALTELDatabaseTMTxtOolTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMTxtOolTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((GetStatus() == TMOOLTABLE_RECORDSTATUS_NONE || GetStatus() == TMOOLTABLE_RECORDSTATUS_NEW || GetStatus() == TMOOLTABLE_RECORDSTATUS_CHANGED) && !GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(m_szInterpretation))));
		CheckAttributes(bStatus);
		CheckCount(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckCount(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTablesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLE_ILLEGALINTERPRETATION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMTxtOolTableRadix(GetAttributes(), GetAttributes(), GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLE_ILLEGALRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTMTxtOolTablesRecordset::CheckCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableCheckCount(GetChecks()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLE_ILLEGALCHECKS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMTxtOolTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMTxtOolTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_SNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_INTER)), m_szInterpretation);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_RADIX)), m_szRadix);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_NBCHECK)), m_nChecks);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMTxtOolTableLimitsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMTxtOolTableLimitsRecordset::CALTELDatabaseTMTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMTxtOolTableLimitsRecordset)
	m_szName.Empty();
	m_szLowLimit.Empty();
	m_szHighLimit.Empty();
	m_nOrder = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMTxtOolTableLimitsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::SetOrder(INT nOrder)
{
	m_nOrder = nOrder;
}

INT CALTELDatabaseTMTxtOolTableLimitsRecordset::GetOrder() CONST
{
	return m_nOrder;
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CALTELDatabaseTMTxtOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::SetLowLimit(LPCTSTR pszLowLimit)
{
	m_szLowLimit = pszLowLimit;
}

CString CALTELDatabaseTMTxtOolTableLimitsRecordset::GetLowLimit() CONST
{
	return m_szLowLimit;
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::SetHighLimit(LPCTSTR pszHighLimit)
{
	m_szHighLimit = pszHighLimit;
}

CString CALTELDatabaseTMTxtOolTableLimitsRecordset::GetHighLimit() CONST
{
	return m_szHighLimit;
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	EnableErrorsByStatus(((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(pszName)))) ? pDatabaseTMTxtOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	EnableWarningsByStatus(((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(pszName)))) ? pDatabaseTMTxtOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMTxtOolTableLimitsRecordset::Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CONST CDatabaseTMTxtOolLimit *pDatabaseTMTxtOolLimit)
{
	double  fRange[2];
	CString  szRange[2];

	for (SetName(pDatabaseTMTxtOolTable->GetName()), SetOrder(pDatabaseTMTxtOolLimit->GetOrder()), SetAttributes(pDatabaseTMTxtOolTable->GetAttributes()), fRange[0] = fRange[1] = 0.0; !pDatabaseTMTxtOolLimit->GetRange(szRange[0], szRange[1]) && pDatabaseTMTxtOolLimit->GetRange(fRange[0], fRange[1]); )
	{
		szRange[0] = (!isnan(fRange[0])) ? GetDatabaseEngine()->TranslateTMTxtOolTableLimitValue(pDatabaseTMTxtOolTable->GetAttributes(), fRange[0]) : EMPTYSTRING;
		szRange[1] = (!isnan(fRange[1])) ? GetDatabaseEngine()->TranslateTMTxtOolTableLimitValue(pDatabaseTMTxtOolTable->GetAttributes(), fRange[1]) : EMPTYSTRING;
		break;
	}
	SetLowLimit(szRange[0]);
	SetHighLimit(szRange[1]);
}

BOOL CALTELDatabaseTMTxtOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMTxtOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(GetName()))))
		{
			for (SetAttributes(pDatabaseTMTxtOolTable->GetAttributes()), bStatus = FALSE; pDatabaseTMTxtOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NONE || pDatabaseTMTxtOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NEW || pDatabaseTMTxtOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_CHANGED; )
			{
				bStatus = TRUE;
				break;
			}
			CheckName(bStatus);
			CheckLimits(bStatus);
			CheckOrder(bStatus);
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckLimits(IsCollectingIssues());
		bCheck &= CheckOrder(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTableLimitsRecordset::CheckLimits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableLimitValue(GetAttributes(), (m_szLowLimit = ExtractText(m_szLowLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMTxtOolTableLimitValue(GetAttributes(), (m_szHighLimit = ExtractText(m_szHighLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTMTxtOolTableLimitsRecordset::CheckOrder(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableLimitOrder(m_nOrder))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALLIMITORDER), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMTxtOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMTxtOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_SNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_FROM)), m_szLowLimit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_TO)), m_szHighLimit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_ORDER)), m_nOrder);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtOolTableAssociationsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTMTxtOolTableAssociationsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTMTxtOolTableAssociationsRecordset::CALTELDatabaseTMTxtOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTMTxtOolTableAssociationsRecordset)
	m_szName.Empty();
	m_szParameter[0].Empty();
	m_szParameter[1].Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTMTxtOolTableAssociationsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szParameter[0] = pszTag;
}

CString CALTELDatabaseTMTxtOolTableAssociationsRecordset::GetParameter() CONST
{
	return m_szParameter[0];
}

VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::SetValidityParameter(LPCTSTR pszTag)
{
	m_szParameter[1] = pszTag;
}

CString CALTELDatabaseTMTxtOolTableAssociationsRecordset::GetValidityParameter() CONST
{
	return m_szParameter[1];
}

VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	EnableErrorsByStatus(((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(pszName)))) ? pDatabaseTMTxtOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	EnableWarningsByStatus(((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(pszName)))) ? pDatabaseTMTxtOolTable->GetStatus() : TMOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTMTxtOolTableAssociationsRecordset::Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter)
{
	SetName(pDatabaseTMTxtOolTable->GetName());
	SetParameter(pDatabaseTMParameter->GetTag());
	SetValidityParameter(pszValidityParameter);
}

BOOL CALTELDatabaseTMTxtOolTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTMTxtOolTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find(GetName())))) ? (pDatabaseTMTxtOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NONE || pDatabaseTMTxtOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_NEW || pDatabaseTMTxtOolTable->GetStatus() == TMOOLTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckParameter(bStatus);
		CheckValidityParameter(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTableAssociationsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTableAssociationsRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szParameter[0] = ExtractText(m_szParameter[0]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTMTxtOolTableAssociationsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityParameter((m_szParameter[1] = ExtractText(m_szParameter[1]))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(GetParameter())); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTMTxtOolTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTMTxtOolTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PFXF_SNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PFXF_PNAME)), m_szParameter[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PFXF_VALID)), m_szParameter[1]);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParametersRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCParametersRecordset::CALTELDatabaseTCParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCParametersRecordset)
	m_szTag.Empty();
	m_szDescription.Empty();
	m_szUnit.Empty();
	m_szCoding.Empty();
	m_szCategory.Empty();
	m_szCalTable[0].Empty();
	m_szCalTable[1].Empty();
	m_szOolTable[0].Empty();
	m_szOolTable[1].Empty();
	m_szStatus.Empty();
	m_nBitWidth = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTCParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTCParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCParametersRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCParametersRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CALTELDatabaseTCParametersRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CALTELDatabaseTCParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szCategory = GetDatabaseEngine()->TranslateTCParameterCategory(nAttributes);
	m_szCoding = GetDatabaseEngine()->TranslateTCParameterCoding(nAttributes);
}

ULONGLONG CALTELDatabaseTCParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCParameterCategory(m_szCategory) | GetDatabaseEngine()->TranslateTCParameterCoding(m_szCoding);
}

VOID CALTELDatabaseTCParametersRecordset::SetBitWidth(INT nWidth)
{
	m_nBitWidth = nWidth;
}

INT CALTELDatabaseTCParametersRecordset::GetBitWidth() CONST
{
	return m_nBitWidth;
}

VOID CALTELDatabaseTCParametersRecordset::SetCalTable(LPCTSTR pszTable)
{
	m_szCalTable[0] = (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) ? pszTable : EMPTYSTRING;
	m_szCalTable[1] = (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? pszTable : EMPTYSTRING;
}

CString CALTELDatabaseTCParametersRecordset::GetCalTable() CONST
{
	if (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) return m_szCalTable[0];
	if (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) return m_szCalTable[1];
	return EMPTYSTRING;
}

VOID CALTELDatabaseTCParametersRecordset::SetOolTable(LPCTSTR pszTable)
{
	m_szOolTable[0] = ((GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) ? pszTable : EMPTYSTRING;
	m_szOolTable[1] = (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? pszTable : EMPTYSTRING;
}

CString CALTELDatabaseTCParametersRecordset::GetOolTable() CONST
{
	if ((GetAttributes() & TCPARAMETER_CALIBRATION_NONE) || (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL)) return m_szOolTable[0];
	if (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) return m_szOolTable[1];
	return EMPTYSTRING;
}

VOID CALTELDatabaseTCParametersRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCParameterStatus(nStatus);
}

INT CALTELDatabaseTCParametersRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCParameterStatus(m_szStatus);
}

VOID CALTELDatabaseTCParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szTag), pszError);
}
VOID CALTELDatabaseTCParametersRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CDatabaseTCParameter  *pDatabaseTCParameter;

	EnableErrorsByStatus(((pDatabaseTCParameter = GetDatabaseEngine()->GetTCParameters()->GetAt(GetDatabaseEngine()->GetTCParameters()->Find(pszTag)))) ? pDatabaseTCParameter->GetStatus() : TCPARAMETER_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszTag, pszTag, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szTag), pszWarning);
}
VOID CALTELDatabaseTCParametersRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CDatabaseTCParameter  *pDatabaseTCParameter;

	EnableWarningsByStatus(((pDatabaseTCParameter = GetDatabaseEngine()->GetTCParameters()->GetAt(GetDatabaseEngine()->GetTCParameters()->Find(pszTag)))) ? pDatabaseTCParameter->GetStatus() : TCPARAMETER_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszTag, pszTag, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCParametersRecordset::Translate(CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	SetTag(pDatabaseTCParameter->GetTag());
	SetDescription(pDatabaseTCParameter->GetDescription());
	SetUnit(pDatabaseTCParameter->GetUnit());
	SetAttributes(pDatabaseTCParameter->GetAttributes());
	SetBitWidth(pDatabaseTCParameter->GetWidth());
	SetCalTable(pDatabaseTCParameter->GetCalTable());
	SetOolTable(pDatabaseTCParameter->GetOolTable());
	SetStatus(pDatabaseTCParameter->GetStatus());
}

BOOL CALTELDatabaseTCParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag((bStatus = (GetStatus() == TCPARAMETER_RECORDSTATUS_NONE || GetStatus() == TCPARAMETER_RECORDSTATUS_NEW || GetStatus() == TCPARAMETER_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckUnit(bStatus);
		CheckAttributes(bStatus);
		CheckBitWidth(bStatus);
		CheckCalTable(bStatus);
		CheckOolTable(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALTAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALDESCRIPTION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParametersRecordset::CheckUnit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterUnit((m_szUnit = ExtractText(m_szUnit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALUNIT), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCParameterCategory((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALCATEGORY), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCParameterCoding(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALCODING), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCParametersRecordset::CheckBitWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterBitWidth(GetBitWidth()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALBITWIDTH), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParametersRecordset::CheckCalTable(BOOL bStatus)
{
	CString  szMessage;

	for (m_szCalTable[0] = ExtractText(m_szCalTable[0]), m_szCalTable[1] = ExtractText(m_szCalTable[1]); !GetDatabaseEngine()->CheckTCParameterCalTable(GetAttributes(), GetCalTable()); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALCALTABLE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParametersRecordset::CheckOolTable(BOOL bStatus)
{
	CString  szMessage;

	for (m_szOolTable[0] = ExtractText(m_szOolTable[0]), m_szOolTable[1] = ExtractText(m_szOolTable[1]); !GetDatabaseEngine()->CheckTCParameterOolTable(GetAttributes(), GetOolTable()); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALOOLTABLE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParametersRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALSTATUS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_PNAME)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_LENGTH)), m_nBitWidth);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_CODING)), m_szCoding);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_UNIT)), m_szUnit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_CATEG)), m_szCategory);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_CALREF)), m_szCalTable[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_TXFREF)), m_szCalTable[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_OCFREF)), m_szOolTable[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_FXFREF)), m_szOolTable[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCNumCalTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCNumCalTablesRecordset::CALTELDatabaseTCNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCNumCalTablesRecordset)
	m_szName.Empty();
	m_szDescription.Empty();
	m_szUnit.Empty();
	m_szStatus.Empty();
	m_nPoints = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCNumCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCNumCalTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCNumCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCNumCalTablesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCNumCalTablesRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CALTELDatabaseTCNumCalTablesRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CALTELDatabaseTCNumCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nPoints = nPoints;
}

INT CALTELDatabaseTCNumCalTablesRecordset::GetPoints() CONST
{
	return m_nPoints;
}

VOID CALTELDatabaseTCNumCalTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCNumCalTableStatus(nStatus);
}

INT CALTELDatabaseTCNumCalTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCNumCalTableStatus(m_szStatus);
}

VOID CALTELDatabaseTCNumCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCNumCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	EnableErrorsByStatus(((pDatabaseTCNumCalTable = GetDatabaseEngine()->GetTCNumCalTables()->GetAt(GetDatabaseEngine()->GetTCNumCalTables()->Find(pszName)))) ? pDatabaseTCNumCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCNumCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCNumCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	EnableWarningsByStatus(((pDatabaseTCNumCalTable = GetDatabaseEngine()->GetTCNumCalTables()->GetAt(GetDatabaseEngine()->GetTCNumCalTables()->Find(pszName)))) ? pDatabaseTCNumCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCNumCalTablesRecordset::Translate(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable)
{
	SetName(pDatabaseTCNumCalTable->GetName());
	SetDescription(pDatabaseTCNumCalTable->GetDescription());
	SetUnit(pDatabaseTCNumCalTable->GetUnit());
	SetPoints(pDatabaseTCNumCalTable->GetPoints());
	SetStatus(pDatabaseTCNumCalTable->GetStatus());
}

BOOL CALTELDatabaseTCNumCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCNumCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TCCALTABLE_RECORDSTATUS_NONE || GetStatus() == TCCALTABLE_RECORDSTATUS_NEW || GetStatus() == TCCALTABLE_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckUnit(bStatus);
		CheckPoints(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckPoints(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumCalTablesRecordset::CheckUnit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableUnit((m_szUnit = ExtractText(m_szUnit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALUNIT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumCalTablesRecordset::CheckPoints(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTablePoints(GetPoints()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALNUMBEROFPOINTS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumCalTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCNumCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCNumCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_UNIT)), m_szUnit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_NBPNT)), m_nPoints);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAL_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCNumCalTablePointsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCNumCalTablePointsRecordset::CALTELDatabaseTCNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCNumCalTablePointsRecordset)
	m_szName.Empty();
	m_fX = 0.0;
	m_fY = 0.0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCNumCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCNumCalTablePointsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCNumCalTablePointsRecordset::SetX(double fX)
{
	m_fX = fX;
}

double CALTELDatabaseTCNumCalTablePointsRecordset::GetX() CONST
{
	return m_fX;
}

VOID CALTELDatabaseTCNumCalTablePointsRecordset::SetY(double fY)
{
	m_fY = fY;
}

double CALTELDatabaseTCNumCalTablePointsRecordset::GetY() CONST
{
	return m_fY;
}

VOID CALTELDatabaseTCNumCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCNumCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	EnableErrorsByStatus(((pDatabaseTCNumCalTable = GetDatabaseEngine()->GetTCNumCalTables()->GetAt(GetDatabaseEngine()->GetTCNumCalTables()->Find(pszName)))) ? pDatabaseTCNumCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	EnableWarningsByStatus(((pDatabaseTCNumCalTable = GetDatabaseEngine()->GetTCNumCalTables()->GetAt(GetDatabaseEngine()->GetTCNumCalTables()->Find(pszName)))) ? pDatabaseTCNumCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCNumCalTablePointsRecordset::Translate(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, CONST CDatabaseTCNumCalPoint *pDatabaseTCNumCalPoint)
{
	SetName(pDatabaseTCNumCalTable->GetName());
	SetX(pDatabaseTCNumCalPoint->GetX());
	SetY(pDatabaseTCNumCalPoint->GetY());
}

BOOL CALTELDatabaseTCNumCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCNumCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTCNumCalTable = GetDatabaseEngine()->GetTCNumCalTables()->GetAt(GetDatabaseEngine()->GetTCNumCalTables()->Find(GetName())))) ? (pDatabaseTCNumCalTable->GetStatus() == TCCALTABLE_RECORDSTATUS_NONE || pDatabaseTCNumCalTable->GetStatus() == TCCALTABLE_RECORDSTATUS_NEW || pDatabaseTCNumCalTable->GetStatus() == TCCALTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckPoint(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckPoint(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLEPOINT_ILLEGALNAME), (LPCTSTR)GetName(), GetX()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage;

	if (isnan(GetX()) || isnan(GetY()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLEPOINT_ILLEGALRAWVALUE), (LPCTSTR)GetName()); isnan(GetX()); )
		{
			ShowError(szMessage);
			break;
		}
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLEPOINT_ILLEGALENGVALUE), (LPCTSTR)GetName()); isnan(GetY()); )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCNumCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCNumCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CALP_NAME)), m_szName);
	RFX_Double(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CALP_XVAL)), m_fX);
	RFX_Double(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CALP_YVAL)), m_fY);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCTxtCalTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCTxtCalTablesRecordset::CALTELDatabaseTCTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCTxtCalTablesRecordset)
	m_szName.Empty();
	m_szDescription.Empty();
	m_szStatus.Empty();
	m_nPoints = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCTxtCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCTxtCalTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCTxtCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCTxtCalTablesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCTxtCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nPoints = nPoints;
}

INT CALTELDatabaseTCTxtCalTablesRecordset::GetPoints() CONST
{
	return m_nPoints;
}

VOID CALTELDatabaseTCTxtCalTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCTxtCalTableStatus(nStatus);
}

INT CALTELDatabaseTCTxtCalTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCTxtCalTableStatus(m_szStatus);
}

VOID CALTELDatabaseTCTxtCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCTxtCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	EnableErrorsByStatus(((pDatabaseTCTxtCalTable = GetDatabaseEngine()->GetTCTxtCalTables()->GetAt(GetDatabaseEngine()->GetTCTxtCalTables()->Find(pszName)))) ? pDatabaseTCTxtCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCTxtCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCTxtCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	EnableWarningsByStatus(((pDatabaseTCTxtCalTable = GetDatabaseEngine()->GetTCTxtCalTables()->GetAt(GetDatabaseEngine()->GetTCTxtCalTables()->Find(pszName)))) ? pDatabaseTCTxtCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCTxtCalTablesRecordset::Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable)
{
	SetName(pDatabaseTCTxtCalTable->GetName());
	SetDescription(pDatabaseTCTxtCalTable->GetDescription());
	SetPoints(pDatabaseTCTxtCalTable->GetPoints());
	SetStatus(pDatabaseTCTxtCalTable->GetStatus());
}

BOOL CALTELDatabaseTCTxtCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCTxtCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TCCALTABLE_RECORDSTATUS_NONE || GetStatus() == TCCALTABLE_RECORDSTATUS_NEW || GetStatus() == TCCALTABLE_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckPoints(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckPoints(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTableDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtCalTablesRecordset::CheckPoints(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTablePoints(GetPoints()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLE_ILLEGALNUMBEROFPOINTS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtCalTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCTxtCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCTxtCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_NBTXT)), m_nPoints);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCTxtCalTablePointsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCTxtCalTablePointsRecordset::CALTELDatabaseTCTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCTxtCalTablePointsRecordset)
	m_szName.Empty();
	m_szText.Empty();
	m_nX1 = 0;
	m_nX2 = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCTxtCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCTxtCalTablePointsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCTxtCalTablePointsRecordset::SetText(LPCTSTR pszText)
{
	m_szText = pszText;
}

CString CALTELDatabaseTCTxtCalTablePointsRecordset::GetText() CONST
{
	return m_szText;
}

VOID CALTELDatabaseTCTxtCalTablePointsRecordset::SetX1(INT nX1)
{
	m_nX1 = nX1;
}

INT CALTELDatabaseTCTxtCalTablePointsRecordset::GetX1() CONST
{
	return m_nX1;
}

VOID CALTELDatabaseTCTxtCalTablePointsRecordset::SetX2(INT nX2)
{
	m_nX2 = nX2;
}

INT CALTELDatabaseTCTxtCalTablePointsRecordset::GetX2() CONST
{
	return m_nX2;
}

VOID CALTELDatabaseTCTxtCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCTxtCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	EnableErrorsByStatus(((pDatabaseTCTxtCalTable = GetDatabaseEngine()->GetTCTxtCalTables()->GetAt(GetDatabaseEngine()->GetTCTxtCalTables()->Find(pszName)))) ? pDatabaseTCTxtCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	EnableWarningsByStatus(((pDatabaseTCTxtCalTable = GetDatabaseEngine()->GetTCTxtCalTables()->GetAt(GetDatabaseEngine()->GetTCTxtCalTables()->Find(pszName)))) ? pDatabaseTCTxtCalTable->GetStatus() : TCCALTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCTxtCalTablePointsRecordset::Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, CONST CDatabaseTCTxtCalPoint *pDatabaseTCTxtCalPoint)
{
	double  fX[2];
	CString  szY;

	for (SetName(pDatabaseTCTxtCalTable->GetName()), pDatabaseTCTxtCalPoint->GetRange(fX[0], fX[1], szY), SetX1(0), SetX2(-1), SetText(szY); !isnan(fX[0]) && !isnan(fX[1]); )
	{
		SetX1((INT)fX[0]);
		SetX2((INT)fX[1]);
		break;
	}
}

BOOL CALTELDatabaseTCTxtCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCTxtCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTCTxtCalTable = GetDatabaseEngine()->GetTCTxtCalTables()->GetAt(GetDatabaseEngine()->GetTCTxtCalTables()->Find(GetName())))) ? (pDatabaseTCTxtCalTable->GetStatus() == TCCALTABLE_RECORDSTATUS_NONE || pDatabaseTCTxtCalTable->GetStatus() == TCCALTABLE_RECORDSTATUS_NEW || pDatabaseTCTxtCalTable->GetStatus() == TCCALTABLE_RECORDSTATUS_CHANGED) : TRUE));
		CheckPoint(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckPoint(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage[2];

	if (!GetDatabaseEngine()->CheckTCTxtCalTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage[0].Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLEPOINT_ILLEGALNAMEATPOINT), (LPCTSTR)GetName(), GetX1(), (LPCTSTR)ExtractText(GetText())), szMessage[1].Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLEPOINT_ILLEGALNAMEATRANGE), (LPCTSTR)GetName(), GetX1(), GetX2(), (LPCTSTR)ExtractText(GetText())); bStatus; )
		{
			ShowError((GetX1() == GetX2()) ? szMessage[0] : szMessage[1]);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage[2];

	if (!GetDatabaseEngine()->CheckTCTxtCalTablePointText((m_szText = ExtractText(m_szText))) || !GetDatabaseEngine()->CheckTCTxtCalTablePointInterval(GetX1(), GetX2()))
	{
		for (szMessage[0].Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLEPOINT_SYNTAXERRORATPOINT), (LPCTSTR)GetName(), GetX1(), (LPCTSTR)ExtractText(GetText())), szMessage[1].Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLEPOINT_SYNTAXERRORATRANGE), (LPCTSTR)GetName(), GetX1(), GetX2(), (LPCTSTR)ExtractText(GetText())); bStatus; )
		{
			ShowError((GetX1() == GetX2()) ? szMessage[0] : szMessage[1]);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCTxtCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCTxtCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_FROM)), m_nX1);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_TO)), m_nX2);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXFP_TEXT)), m_szText);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumOolTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCNumOolTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCNumOolTablesRecordset::CALTELDatabaseTCNumOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCNumOolTablesRecordset)
	m_szName.Empty();
	m_szInterpretation.Empty();
	m_szCoding.Empty();
	m_szRadix.Empty();
	m_nChecks = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCNumOolTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCNumOolTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCNumOolTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szInterpretation = GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(nAttributes);
	m_szCoding = GetDatabaseEngine()->TranslateTCNumOolTableCoding(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCNumOolTableRadix(nAttributes);
}

UINT CALTELDatabaseTCNumOolTablesRecordset::GetAttributes() CONST
{
	UINT  nInterpretation;

	return(((nInterpretation = GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInterpretation)) & TCOOLTABLE_CHECK_RAW) ? (nInterpretation | GetDatabaseEngine()->TranslateTCNumOolTableCoding(GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInterpretation), m_szCoding) | GetDatabaseEngine()->TranslateTCNumOolTableRadix(GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInterpretation), m_szRadix)) : (nInterpretation | TCOOLTABLE_CODING_FLOATINGPOINT | TCOOLTABLE_RADIX_DECIMAL));
}

VOID CALTELDatabaseTCNumOolTablesRecordset::SetChecks(INT nChecks)
{
	m_nChecks = nChecks;
}

INT CALTELDatabaseTCNumOolTablesRecordset::GetChecks() CONST
{
	return m_nChecks;
}

VOID CALTELDatabaseTCNumOolTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCNumOolTableStatus(nStatus);
}

INT CALTELDatabaseTCNumOolTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCNumOolTableStatus(m_szStatus);
}

VOID CALTELDatabaseTCNumOolTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCNumOolTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	EnableErrorsByStatus(((pDatabaseTCNumOolTable = GetDatabaseEngine()->GetTCNumOolTables()->GetAt(GetDatabaseEngine()->GetTCNumOolTables()->Find(pszName)))) ? pDatabaseTCNumOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCNumOolTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCNumOolTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	EnableWarningsByStatus(((pDatabaseTCNumOolTable = GetDatabaseEngine()->GetTCNumOolTables()->GetAt(GetDatabaseEngine()->GetTCNumOolTables()->Find(pszName)))) ? pDatabaseTCNumOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCNumOolTablesRecordset::Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable)
{
	SetName(pDatabaseTCNumOolTable->GetName());
	SetAttributes(pDatabaseTCNumOolTable->GetAttributes());
	SetChecks(pDatabaseTCNumOolTable->GetChecks());
	SetStatus(pDatabaseTCNumOolTable->GetStatus());
}

BOOL CALTELDatabaseTCNumOolTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCNumOolTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((GetStatus() == TCOOLTABLE_RECORDSTATUS_NONE || GetStatus() == TCOOLTABLE_RECORDSTATUS_NEW || GetStatus() == TCOOLTABLE_RECORDSTATUS_CHANGED) && !GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(m_szInterpretation))));
		CheckAttributes(bStatus);
		CheckCount(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckCount(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumOolTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumOolTablesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALINTERPRETATION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumOolTableCoding(GetAttributes(), GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumOolTableRadix(GetAttributes(), GetAttributes(), GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCNumOolTablesRecordset::CheckCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableCheckCount(GetChecks()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALCHECKS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumOolTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCNumOolTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCNumOolTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_ONAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_INTER)), m_szInterpretation);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_CODING)), m_szCoding);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_RADIX)), m_szRadix);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NBCHECK)), m_nChecks);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCNumOolTableLimitsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCNumOolTableLimitsRecordset::CALTELDatabaseTCNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCNumOolTableLimitsRecordset)
	m_szName.Empty();
	m_szLowLimit.Empty();
	m_szHighLimit.Empty();
	m_nOrder = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCNumOolTableLimitsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::SetOrder(INT nOrder)
{
	m_nOrder = nOrder;
}

INT CALTELDatabaseTCNumOolTableLimitsRecordset::GetOrder() CONST
{
	return m_nOrder;
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CALTELDatabaseTCNumOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::SetLowLimit(double fLowLimit)
{
	m_szLowLimit = (!isnan(fLowLimit)) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), fLowLimit) : EMPTYSTRING;
}

double CALTELDatabaseTCNumOolTableLimitsRecordset::GetLowLimit() CONST
{
	return((GetDatabaseEngine()->CheckTCNumOolTableLimitValue(GetAttributes(), m_szLowLimit)) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), m_szLowLimit) : NAN);
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::SetHighLimit(double fHighLimit)
{
	m_szHighLimit = (!isnan(fHighLimit)) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), fHighLimit) : EMPTYSTRING;
}

double CALTELDatabaseTCNumOolTableLimitsRecordset::GetHighLimit() CONST
{
	return((GetDatabaseEngine()->CheckTCNumOolTableLimitValue(GetAttributes(), m_szHighLimit)) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), m_szHighLimit) : NAN);
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCNumOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	EnableErrorsByStatus(((pDatabaseTCNumOolTable = GetDatabaseEngine()->GetTCNumOolTables()->GetAt(GetDatabaseEngine()->GetTCNumOolTables()->Find(pszName)))) ? pDatabaseTCNumOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	EnableWarningsByStatus(((pDatabaseTCNumOolTable = GetDatabaseEngine()->GetTCNumOolTables()->GetAt(GetDatabaseEngine()->GetTCNumOolTables()->Find(pszName)))) ? pDatabaseTCNumOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCNumOolTableLimitsRecordset::Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CONST CDatabaseTCNumOolLimit *pDatabaseTCNumOolLimit)
{
	UINT  nType;
	double  fDelta;
	double  fRange[2];

	for (SetName(pDatabaseTCNumOolTable->GetName()), SetOrder(pDatabaseTCNumOolLimit->GetType()), SetAttributes(pDatabaseTCNumOolTable->GetAttributes()), fRange[0] = fRange[1] = 0.0; !pDatabaseTCNumOolLimit->GetRange(nType, fRange[0], fRange[1]) && pDatabaseTCNumOolLimit->GetDelta(fDelta); )
	{
		fRange[0] = fDelta;
		fRange[1] = fDelta;
		break;
	}
	SetLowLimit(fRange[0]);
	SetHighLimit(fRange[1]);
}

BOOL CALTELDatabaseTCNumOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCNumOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTCNumOolTable = GetDatabaseEngine()->GetTCNumOolTables()->GetAt(GetDatabaseEngine()->GetTCNumOolTables()->Find(GetName()))))
		{
			for (SetAttributes(pDatabaseTCNumOolTable->GetAttributes()), bStatus = FALSE; pDatabaseTCNumOolTable->GetStatus() == TCOOLTABLE_RECORDSTATUS_NONE || pDatabaseTCNumOolTable->GetStatus() == TCOOLTABLE_RECORDSTATUS_NEW || pDatabaseTCNumOolTable->GetStatus() == TCOOLTABLE_RECORDSTATUS_CHANGED; )
			{
				bStatus = TRUE;
				break;
			}
			CheckName(bStatus);
			CheckLimits(bStatus);
			CheckOrder(bStatus);
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckLimits(IsCollectingIssues());
		bCheck &= CheckOrder(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCNumOolTableLimitsRecordset::CheckLimits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableLimitValue(GetAttributes(), (m_szLowLimit = ExtractText(m_szLowLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumOolTableLimitValue(GetAttributes(), (m_szHighLimit = ExtractText(m_szHighLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCNumOolTableLimitsRecordset::CheckOrder(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableLimitOrder(m_nOrder))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLELIMIT_ILLEGALLIMITORDER), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_OCFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCNumOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCNumOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_ONAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_LVALUE)), m_szLowLimit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_HVALUE)), m_szHighLimit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCFP_ORDER)), m_nOrder);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtOolTablesRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCTxtOolTablesRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCTxtOolTablesRecordset::CALTELDatabaseTCTxtOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCTxtOolTablesRecordset)
	m_szName.Empty();
	m_szInterpretation.Empty();
	m_szRadix.Empty();
	m_nChecks = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCTxtOolTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCTxtOolTablesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCTxtOolTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szInterpretation = GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCTxtOolTableRadix(nAttributes);
}

UINT CALTELDatabaseTCTxtOolTablesRecordset::GetAttributes() CONST
{
	UINT  nInterpretation;

	return(((nInterpretation = GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(m_szInterpretation)) & TCOOLTABLE_CHECK_RAW) ? (nInterpretation | GetDatabaseEngine()->TranslateTCTxtOolTableRadix(GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(m_szInterpretation), m_szRadix)) : nInterpretation);
}

VOID CALTELDatabaseTCTxtOolTablesRecordset::SetChecks(INT nChecks)
{
	m_nChecks = nChecks;
}

INT CALTELDatabaseTCTxtOolTablesRecordset::GetChecks() CONST
{
	return m_nChecks;
}

VOID CALTELDatabaseTCTxtOolTablesRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCTxtOolTableStatus(nStatus);
}

INT CALTELDatabaseTCTxtOolTablesRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCTxtOolTableStatus(m_szStatus);
}

VOID CALTELDatabaseTCTxtOolTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCTxtOolTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	EnableErrorsByStatus(((pDatabaseTCTxtOolTable = GetDatabaseEngine()->GetTCTxtOolTables()->GetAt(GetDatabaseEngine()->GetTCTxtOolTables()->Find(pszName)))) ? pDatabaseTCTxtOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCTxtOolTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCTxtOolTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	EnableWarningsByStatus(((pDatabaseTCTxtOolTable = GetDatabaseEngine()->GetTCTxtOolTables()->GetAt(GetDatabaseEngine()->GetTCTxtOolTables()->Find(pszName)))) ? pDatabaseTCTxtOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCTxtOolTablesRecordset::Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable)
{
	SetName(pDatabaseTCTxtOolTable->GetName());
	SetAttributes(pDatabaseTCTxtOolTable->GetAttributes());
	SetChecks(pDatabaseTCTxtOolTable->GetChecks());
	SetStatus(pDatabaseTCTxtOolTable->GetStatus());
}

BOOL CALTELDatabaseTCTxtOolTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCTxtOolTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((GetStatus() == TCOOLTABLE_RECORDSTATUS_NONE || GetStatus() == TCOOLTABLE_RECORDSTATUS_NEW || GetStatus() == TCOOLTABLE_RECORDSTATUS_CHANGED) && !GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(m_szInterpretation))));
		CheckAttributes(bStatus);
		CheckCount(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckCount(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtOolTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtOolTablesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALINTERPRETATION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCTxtOolTableRadix(GetAttributes(), GetAttributes(), GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCTxtOolTablesRecordset::CheckCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableCheckCount(GetChecks()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALCHECKS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtOolTablesRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCTxtOolTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCTxtOolTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_SNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_INTER)), m_szInterpretation);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_RADIX)), m_szRadix);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXF_NBCHECK)), m_nChecks);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCTxtOolTableLimitsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCTxtOolTableLimitsRecordset::CALTELDatabaseTCTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCTxtOolTableLimitsRecordset)
	m_szName.Empty();
	m_szLowLimit.Empty();
	m_szHighLimit.Empty();
	m_nOrder = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCTxtOolTableLimitsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::SetOrder(INT nOrder)
{
	m_nOrder = nOrder;
}

INT CALTELDatabaseTCTxtOolTableLimitsRecordset::GetOrder() CONST
{
	return m_nOrder;
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CALTELDatabaseTCTxtOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::SetLowLimit(LPCTSTR pszLowLimit)
{
	m_szLowLimit = pszLowLimit;
}

CString CALTELDatabaseTCTxtOolTableLimitsRecordset::GetLowLimit() CONST
{
	return m_szLowLimit;
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::SetHighLimit(LPCTSTR pszHighLimit)
{
	m_szHighLimit = pszHighLimit;
}

CString CALTELDatabaseTCTxtOolTableLimitsRecordset::GetHighLimit() CONST
{
	return m_szHighLimit;
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	EnableErrorsByStatus(((pDatabaseTCTxtOolTable = GetDatabaseEngine()->GetTCTxtOolTables()->GetAt(GetDatabaseEngine()->GetTCTxtOolTables()->Find(pszName)))) ? pDatabaseTCTxtOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	EnableWarningsByStatus(((pDatabaseTCTxtOolTable = GetDatabaseEngine()->GetTCTxtOolTables()->GetAt(GetDatabaseEngine()->GetTCTxtOolTables()->Find(pszName)))) ? pDatabaseTCTxtOolTable->GetStatus() : TCOOLTABLE_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCTxtOolTableLimitsRecordset::Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CONST CDatabaseTCTxtOolLimit *pDatabaseTCTxtOolLimit)
{
	double  fRange[2];
	CString  szRange[2];

	for (SetName(pDatabaseTCTxtOolTable->GetName()), SetOrder(pDatabaseTCTxtOolLimit->GetOrder()), SetAttributes(pDatabaseTCTxtOolTable->GetAttributes()), fRange[0] = fRange[1] = 0.0; !pDatabaseTCTxtOolLimit->GetRange(szRange[0], szRange[1]) && pDatabaseTCTxtOolLimit->GetRange(fRange[0], fRange[1]); )
	{
		szRange[0] = (!isnan(fRange[0])) ? GetDatabaseEngine()->TranslateTCTxtOolTableLimitValue(pDatabaseTCTxtOolTable->GetAttributes(), fRange[0]) : EMPTYSTRING;
		szRange[1] = (!isnan(fRange[1])) ? GetDatabaseEngine()->TranslateTCTxtOolTableLimitValue(pDatabaseTCTxtOolTable->GetAttributes(), fRange[1]) : EMPTYSTRING;
		break;
	}
	SetLowLimit(szRange[0]);
	SetHighLimit(szRange[1]);
}

BOOL CALTELDatabaseTCTxtOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCTxtOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTCTxtOolTable = GetDatabaseEngine()->GetTCTxtOolTables()->GetAt(GetDatabaseEngine()->GetTCTxtOolTables()->Find(GetName()))))
		{
			for (SetAttributes(pDatabaseTCTxtOolTable->GetAttributes()), bStatus = FALSE; pDatabaseTCTxtOolTable->GetStatus() == TCOOLTABLE_RECORDSTATUS_NONE || pDatabaseTCTxtOolTable->GetStatus() == TCOOLTABLE_RECORDSTATUS_NEW || pDatabaseTCTxtOolTable->GetStatus() == TCOOLTABLE_RECORDSTATUS_CHANGED; )
			{
				bStatus = TRUE;
				break;
			}
			CheckName(bStatus);
			CheckLimits(bStatus);
			CheckOrder(bStatus);
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckLimits(IsCollectingIssues());
		bCheck &= CheckOrder(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCTxtOolTableLimitsRecordset::CheckLimits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableLimitValue(GetAttributes(), (m_szLowLimit = ExtractText(m_szLowLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCTxtOolTableLimitValue(GetAttributes(), (m_szHighLimit = ExtractText(m_szHighLimit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCTxtOolTableLimitsRecordset::CheckOrder(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableLimitOrder(m_nOrder))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLELIMIT_ILLEGALLIMITORDER), (LPCTSTR)GetName(), (!m_szLowLimit.IsEmpty()) ? (LPCTSTR)m_szLowLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE), (!m_szHighLimit.IsEmpty()) ? (LPCTSTR)m_szHighLimit : STRING(IDS_DATABASE_TABLE_FXFP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCTxtOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCTxtOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_SNAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_FROM)), m_szLowLimit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_TO)), m_szHighLimit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_FXFP_ORDER)), m_nOrder);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPreExeGroupsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCPreExeGroupsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCPreExeGroupsRecordset::CALTELDatabaseTCPreExeGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCPreExeGroupsRecordset)
	m_szID.Empty();
	m_szDescription.Empty();
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCPreExeGroupsRecordset::SetID(LPCTSTR pszID)
{
	m_szID = pszID;
}

CString CALTELDatabaseTCPreExeGroupsRecordset::GetID() CONST
{
	return m_szID;
}

VOID CALTELDatabaseTCPreExeGroupsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCPreExeGroupsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCPreExeGroupsRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCPreExeGroupStatus(nStatus);
}

INT CALTELDatabaseTCPreExeGroupsRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCPreExeGroupStatus(m_szStatus);
}

VOID CALTELDatabaseTCPreExeGroupsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szID), pszError);
}
VOID CALTELDatabaseTCPreExeGroupsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;

	EnableErrorsByStatus(((pDatabaseTCPreExeGroup = GetDatabaseEngine()->GetTCPreExeGroups()->GetAt(GetDatabaseEngine()->GetTCPreExeGroups()->Find(pszName)))) ? pDatabaseTCPreExeGroup->GetStatus() : TCPREEXEGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCPreExeGroupsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szID), pszWarning);
}
VOID CALTELDatabaseTCPreExeGroupsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;

	EnableWarningsByStatus(((pDatabaseTCPreExeGroup = GetDatabaseEngine()->GetTCPreExeGroups()->GetAt(GetDatabaseEngine()->GetTCPreExeGroups()->Find(pszName)))) ? pDatabaseTCPreExeGroup->GetStatus() : TCPREEXEGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCPreExeGroupsRecordset::Translate(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup)
{
	SetID(pDatabaseTCPreExeGroup->GetID());
	SetDescription(pDatabaseTCPreExeGroup->GetDescription());
	SetStatus(pDatabaseTCPreExeGroup->GetStatus());
}

BOOL CALTELDatabaseTCPreExeGroupsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCPreExeGroupsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID((bStatus = (GetStatus() == TCPREEXEGROUP_RECORDSTATUS_NONE || GetStatus() == TCPREEXEGROUP_RECORDSTATUS_NEW || GetStatus() == TCPREEXEGROUP_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPreExeGroupsRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupID((m_szID = ExtractText(m_szID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUP_ILLEGALID), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPreExeGroupsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUP_ILLEGALDESCRIPTION), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPreExeGroupsRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUP_ILLEGALSTATUS), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCPreExeGroupsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCPreExeGroupsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVP_ID)), m_szID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVP_DESCR)), m_szDescription);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPreExeGroupParametersRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCPreExeGroupParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCPreExeGroupParametersRecordset::CALTELDatabaseTCPreExeGroupParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCPreExeGroupParametersRecordset)
	m_szID.Empty();
	m_szTag.Empty();
	m_szInterpretation.Empty();
	m_szValue.Empty();
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCPreExeGroupParametersRecordset::SetID(LPCTSTR pszID)
{
	m_szID = pszID;
}

CString CALTELDatabaseTCPreExeGroupParametersRecordset::GetID() CONST
{
	return m_szID;
}

VOID CALTELDatabaseTCPreExeGroupParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTCPreExeGroupParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTCPreExeGroupParametersRecordset::SetAttributes(UINT nAttributes)
{
	m_szInterpretation = GetDatabaseEngine()->TranslateTCPreExeGroupParameterInterpretation(nAttributes);
}

UINT CALTELDatabaseTCPreExeGroupParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCPreExeGroupParameterInterpretation(m_szInterpretation);
}

VOID CALTELDatabaseTCPreExeGroupParametersRecordset::SetValue(LPCTSTR pszValue)
{
	m_szValue = pszValue;
}

CString CALTELDatabaseTCPreExeGroupParametersRecordset::GetValue() CONST
{
	return m_szValue;
}

VOID CALTELDatabaseTCPreExeGroupParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szID), pszError);
}
VOID CALTELDatabaseTCPreExeGroupParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;

	EnableErrorsByStatus(((pDatabaseTCPreExeGroup = GetDatabaseEngine()->GetTCPreExeGroups()->GetAt(GetDatabaseEngine()->GetTCPreExeGroups()->Find(pszName)))) ? pDatabaseTCPreExeGroup->GetStatus() : TCPREEXEGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCPreExeGroupParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szID), pszWarning);
}
VOID CALTELDatabaseTCPreExeGroupParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;

	EnableWarningsByStatus(((pDatabaseTCPreExeGroup = GetDatabaseEngine()->GetTCPreExeGroups()->GetAt(GetDatabaseEngine()->GetTCPreExeGroups()->Find(pszName)))) ? pDatabaseTCPreExeGroup->GetStatus() : TCPREEXEGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCPreExeGroupParametersRecordset::Translate(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, CONST CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter)
{
	SetID(pDatabaseTCPreExeGroup->GetID());
	SetTag(pDatabaseTCPreExeGroupParameter->GetTag());
	SetAttributes(pDatabaseTCPreExeGroupParameter->GetAttributes());
	SetValue(pDatabaseTCPreExeGroupParameter->GetValueAsText());
}

BOOL CALTELDatabaseTCPreExeGroupParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCPreExeGroupParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCPreExeGroup  *pGroup;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID((bStatus = ((pGroup = GetDatabaseEngine()->GetTCPreExeGroups()->GetAt(GetDatabaseEngine()->GetTCPreExeGroups()->Find(GetID())))) ? (pGroup->GetStatus() == TCPREEXEGROUP_RECORDSTATUS_NONE || pGroup->GetStatus() == TCPREEXEGROUP_RECORDSTATUS_NEW || pGroup->GetStatus() == TCPREEXEGROUP_RECORDSTATUS_CHANGED) : TRUE));
		CheckTag(bStatus);
		CheckAttributes(bStatus);
		CheckValue(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		bCheck &= CheckTag(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPreExeGroupParametersRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupID((m_szID = ExtractText(m_szID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUPPARAMETER_ILLEGALID), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPreExeGroupParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUPPARAMETER_ILLEGALTAG), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCPreExeGroupParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupParameterInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUPPARAMETER_ILLEGALINTERPRETATION), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCPreExeGroupParametersRecordset::CheckValue(BOOL bStatus)
{
	INT  nLength;
	CString  szMessage;

	if ((nLength = lstrlen((m_szValue = ExtractText(m_szValue)))) == 0 || nLength > GetDatabaseEngine()->GetTCPreExeGroupParameterConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUPPARAMETER_ILLEGALVALUE), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCPreExeGroupParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCPreExeGroupParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PEV_ID)), m_szID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PEV_PNAME)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PEV_PVALUE)), m_szValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PEV_INTER)), m_szInterpretation);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCExeVerGroupsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCExeVerGroupsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCExeVerGroupsRecordset::CALTELDatabaseTCExeVerGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCExeVerGroupsRecordset)
	m_szID.Empty();
	m_szName.Empty();
	m_szDescription.Empty();
	m_nStages = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::SetID(LPCTSTR pszID)
{
	m_szID = pszID;
}

CString CALTELDatabaseTCExeVerGroupsRecordset::GetID() CONST
{
	return m_szID;
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCExeVerGroupsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCExeVerGroupsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::SetStages(INT nStages)
{
	m_nStages = nStages;
}

INT CALTELDatabaseTCExeVerGroupsRecordset::GetStages() CONST
{
	return m_nStages;
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCExeVerGroupStatus(nStatus);
}

INT CALTELDatabaseTCExeVerGroupsRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCExeVerGroupStatus(m_szStatus);
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szID), pszError);
}
VOID CALTELDatabaseTCExeVerGroupsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;

	EnableErrorsByStatus(((pDatabaseTCExeVerGroup = GetDatabaseEngine()->GetTCExeVerGroups()->GetAt(GetDatabaseEngine()->GetTCExeVerGroups()->Find(pszName)))) ? pDatabaseTCExeVerGroup->GetStatus() : TCEXEVERGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szID), pszWarning);
}
VOID CALTELDatabaseTCExeVerGroupsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;

	EnableWarningsByStatus(((pDatabaseTCExeVerGroup = GetDatabaseEngine()->GetTCExeVerGroups()->GetAt(GetDatabaseEngine()->GetTCExeVerGroups()->Find(pszName)))) ? pDatabaseTCExeVerGroup->GetStatus() : TCEXEVERGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCExeVerGroupsRecordset::Translate(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup)
{
	SetID(pDatabaseTCExeVerGroup->GetID());
	SetName(pDatabaseTCExeVerGroup->GetName());
	SetDescription(pDatabaseTCExeVerGroup->GetDescription());
	SetStages(pDatabaseTCExeVerGroup->GetStages());
	SetStatus(pDatabaseTCExeVerGroup->GetStatus());
}

BOOL CALTELDatabaseTCExeVerGroupsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCExeVerGroupsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID((bStatus = (GetStatus() == TCEXEVERGROUP_RECORDSTATUS_NONE || GetStatus() == TCEXEVERGROUP_RECORDSTATUS_NEW || GetStatus() == TCEXEVERGROUP_RECORDSTATUS_CHANGED)));
		CheckName(bStatus);
		CheckDescription(bStatus);
		CheckStages(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		bCheck &= CheckName(IsCollectingIssues());
		bCheck &= CheckStages(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupsRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupID((m_szID = ExtractText(m_szID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALID), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALNAME), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALDESCRIPTION), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupsRecordset::CheckStages(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupStages(GetStages()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALSTAGES), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupsRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALSTATUS), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCExeVerGroupsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCExeVerGroupsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVP_ID)), m_szID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVP_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVP_DESCR)), m_szDescription);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVP_NMBST)), m_nStages);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCExeVerGroupParametersRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCExeVerGroupParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCExeVerGroupParametersRecordset::CALTELDatabaseTCExeVerGroupParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCExeVerGroupParametersRecordset)
	m_szID.Empty();
	m_szTag.Empty();
	m_szType.Empty();
	m_szValue.Empty();
	m_szInterpretation.Empty();
	m_szEventIDPacket.Empty();
	m_nTimeWindow = 0;
	m_nStage = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::SetID(LPCTSTR pszID)
{
	m_szID = pszID;
}

CString CALTELDatabaseTCExeVerGroupParametersRecordset::GetID() CONST
{
	return m_szID;
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CALTELDatabaseTCExeVerGroupParametersRecordset::GetTag() CONST
{
	return m_szTag;
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::SetStage(UINT nStageID)
{
	m_nStage = _ttoi(GetDatabaseEngine()->TranslateTCExeVerGroupParameterStage(nStageID));
}

UINT CALTELDatabaseTCExeVerGroupParametersRecordset::GetStage() CONST
{
	CStringTools  cStringTools;

	return GetDatabaseEngine()->TranslateTCExeVerGroupParameterStage(cStringTools.ConvertIntToString(m_nStage));
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::SetAttributes(UINT nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCExeVerGroupParameterType(nAttributes);
	m_szInterpretation = GetDatabaseEngine()->TranslateTCExeVerGroupParameterInterpretation(nAttributes);
}

UINT CALTELDatabaseTCExeVerGroupParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCExeVerGroupParameterType(m_szType) | GetDatabaseEngine()->TranslateTCExeVerGroupParameterInterpretation(m_szInterpretation) | TCEXEVERGROUPPARAMETER_CHECKS_ENABLED;
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::SetValue(LPCTSTR pszValue)
{
	m_szValue = pszValue;
}

CString CALTELDatabaseTCExeVerGroupParametersRecordset::GetValue() CONST
{
	return m_szValue;
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::SetTimeWindowInterval(CONST CTimeSpan &tInterval)
{
	m_nTimeWindow = (INT)tInterval.GetTotalSeconds();
}

CTimeSpan CALTELDatabaseTCExeVerGroupParametersRecordset::GetTimeWindowInterval() CONST
{
	return m_nTimeWindow;
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::SetEventIDPacket(LPCTSTR pszTag)
{
	m_szEventIDPacket = pszTag;
}

CString CALTELDatabaseTCExeVerGroupParametersRecordset::GetEventIDPacket() CONST
{
	return m_szEventIDPacket;
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szID), pszError);
}
VOID CALTELDatabaseTCExeVerGroupParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;

	EnableErrorsByStatus(((pDatabaseTCExeVerGroup = GetDatabaseEngine()->GetTCExeVerGroups()->GetAt(GetDatabaseEngine()->GetTCExeVerGroups()->Find(pszName)))) ? pDatabaseTCExeVerGroup->GetStatus() : TCEXEVERGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szID), pszWarning);
}
VOID CALTELDatabaseTCExeVerGroupParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;

	EnableWarningsByStatus(((pDatabaseTCExeVerGroup = GetDatabaseEngine()->GetTCExeVerGroups()->GetAt(GetDatabaseEngine()->GetTCExeVerGroups()->Find(pszName)))) ? pDatabaseTCExeVerGroup->GetStatus() : TCEXEVERGROUP_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCExeVerGroupParametersRecordset::Translate(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter)
{
	SetID(pDatabaseTCExeVerGroup->GetID());
	SetTag(pDatabaseTCExeVerGroupParameter->GetTag());
	SetStage(MAKETCEXEVERSTAGEID(pDatabaseTCExeVerGroupParameter->GetStage(), pDatabaseTCExeVerGroupParameter->GetStep()));
	SetAttributes(pDatabaseTCExeVerGroupParameter->GetAttributes());
	SetValue(pDatabaseTCExeVerGroupParameter->GetValueAsText());
	SetTimeWindowInterval(pDatabaseTCExeVerGroupParameter->GetTimeWindowInterval());
	SetEventIDPacket(pDatabaseTCExeVerGroupParameter->GetEventIDPacket());
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCExeVerGroup  *pGroup;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID((bStatus = ((pGroup = GetDatabaseEngine()->GetTCExeVerGroups()->GetAt(GetDatabaseEngine()->GetTCExeVerGroups()->Find(GetID())))) ? (pGroup->GetStatus() == TCEXEVERGROUP_RECORDSTATUS_NONE || pGroup->GetStatus() == TCEXEVERGROUP_RECORDSTATUS_NEW || pGroup->GetStatus() == TCEXEVERGROUP_RECORDSTATUS_CHANGED) : TRUE));
		CheckTag(bStatus);
		CheckStage(bStatus);
		CheckAttributes(bStatus);
		CheckValue(bStatus);
		CheckTimeWindowInterval(bStatus);
		CheckEventIDPacket(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		bCheck &= CheckTag(IsCollectingIssues());
		bCheck &= CheckStage(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckValue(IsCollectingIssues());
		bCheck &= CheckTimeWindowInterval(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupID((m_szID = ExtractText(m_szID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALID), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterTag((m_szTag = ExtractText(m_szTag))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALTAG), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::CheckStage(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterStage(GetStage()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALSTAGE), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::CheckAttributes(BOOL bStatus)
{
	UINT  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterType((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALTYPE), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterInterpretation(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALINTERPRETATION), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::CheckValue(BOOL bStatus)
{
	INT  nLength;
	CString  szMessage;

	if ((nLength = lstrlen((m_szValue = ExtractText(m_szValue)))) == 0 || nLength > GetDatabaseEngine()->GetTCExeVerGroupParameterConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALVALUE), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::CheckTimeWindowInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterTimeWindowInterval(GetTimeWindowInterval()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALTIMEWINDOW), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCExeVerGroupParametersRecordset::CheckEventIDPacket(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterEventID((m_szEventIDPacket = ExtractText(m_szEventIDPacket))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUPPARAMETER_ILLEGALEVENTID), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCExeVerGroupParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCExeVerGroupParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_ID)), m_szID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_EVTYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_PNAME)), m_szTag);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_PVALUE)), m_szValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_INTER)), m_szInterpretation);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_SWND)), m_nTimeWindow);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_STAGE)), m_nStage);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CEV_EPCKID)), m_szEventIDPacket);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParameterSetsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCParameterSetsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCParameterSetsRecordset::CALTELDatabaseTCParameterSetsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCParameterSetsRecordset)
	m_szName.Empty();
	m_szDescription.Empty();
	m_szStatus.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCParameterSetsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCParameterSetsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCParameterSetsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CALTELDatabaseTCParameterSetsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CALTELDatabaseTCParameterSetsRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateTCParameterSetStatus(nStatus);
}

INT CALTELDatabaseTCParameterSetsRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateTCParameterSetStatus(m_szStatus);
}

VOID CALTELDatabaseTCParameterSetsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCParameterSetsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	EnableErrorsByStatus(((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(pszName)))) ? pDatabaseTCParameterSet->GetStatus() : TCPARAMETERSET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCParameterSetsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCParameterSetsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	EnableWarningsByStatus(((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(pszName)))) ? pDatabaseTCParameterSet->GetStatus() : TCPARAMETERSET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCParameterSetsRecordset::Translate(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet)
{
	SetName(pDatabaseTCParameterSet->GetName());
	SetDescription(pDatabaseTCParameterSet->GetDescription());
	SetStatus(pDatabaseTCParameterSet->GetStatus());
}

BOOL CALTELDatabaseTCParameterSetsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCParameterSetsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == TCPARAMETERSET_RECORDSTATUS_NONE || GetStatus() == TCPARAMETERSET_RECORDSTATUS_NEW || GetStatus() == TCPARAMETERSET_RECORDSTATUS_CHANGED)));
		CheckDescription(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSET_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSET_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetsRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSET_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCParameterSetsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCParameterSetsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPS_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPS_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPS_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParameterSetItemsRecordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCParameterSetItemsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCParameterSetItemsRecordset::CALTELDatabaseTCParameterSetItemsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCParameterSetItemsRecordset)
	m_szName.Empty();
	m_szParameterSet.Empty();
	m_szValueType.Empty();
	m_szValueRadix.Empty();
	m_szConstValue.Empty();
	m_nBitOffset = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCParameterSetItemsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCParameterSetItemsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCParameterSetItemsRecordset::SetParameterSet(LPCTSTR pszSet)
{
	m_szParameterSet = pszSet;
}

CString CALTELDatabaseTCParameterSetItemsRecordset::GetParameterSet() CONST
{
	return m_szParameterSet;
}

VOID CALTELDatabaseTCParameterSetItemsRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szValueType = GetDatabaseEngine()->TranslateTCParameterSetItemValueInterpretation(nAttributes);
	m_szValueRadix = GetDatabaseEngine()->TranslateTCParameterSetItemValueRadix(nAttributes);
}

ULONGLONG CALTELDatabaseTCParameterSetItemsRecordset::GetAttributes() CONST
{
	return TCFUNCTIONELEMENT_TYPE_PARAMETER | GetDatabaseEngine()->TranslateTCParameterSetItemValueInterpretation(m_szValueType) | GetDatabaseEngine()->TranslateTCParameterSetItemValueRadix(m_szValueRadix);
}

VOID CALTELDatabaseTCParameterSetItemsRecordset::SetBitOffset(INT nOffset)
{
	m_nBitOffset = nOffset;
}

INT CALTELDatabaseTCParameterSetItemsRecordset::GetBitOffset() CONST
{
	return m_nBitOffset;
}

VOID CALTELDatabaseTCParameterSetItemsRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szConstValue = pszConstValue;
}

CString CALTELDatabaseTCParameterSetItemsRecordset::GetConstValue() CONST
{
	return m_szConstValue;
}

VOID CALTELDatabaseTCParameterSetItemsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szParameterSet), pszError);
}
VOID CALTELDatabaseTCParameterSetItemsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	EnableErrorsByStatus(((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(pszName)))) ? pDatabaseTCParameterSet->GetStatus() : TCPARAMETERSET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCParameterSetItemsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szParameterSet), pszWarning);
}
VOID CALTELDatabaseTCParameterSetItemsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	EnableWarningsByStatus(((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(pszName)))) ? pDatabaseTCParameterSet->GetStatus() : TCPARAMETERSET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseTCParameterSetItemsRecordset::Translate(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement)
{
	SetName(pDatabaseTCFunctionElement->GetName());
	SetParameterSet(pDatabaseTCParameterSet->GetName());
	SetAttributes(pDatabaseTCFunctionElement->GetAttributes());
	SetBitOffset(8 * pDatabaseTCFunctionElement->GetBytePos() + pDatabaseTCFunctionElement->GetBitPos());
	SetConstValue(pDatabaseTCFunctionElement->GetConstValueAsText());
	return((pDatabaseTCFunctionElement->GetAttributes() & TCFUNCTIONELEMENT_TYPE_PARAMETER) ? TRUE : FALSE);
}

BOOL CALTELDatabaseTCParameterSetItemsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCParameterSetItemsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(GetParameterSet())))) ? (pDatabaseTCParameterSet->GetStatus() == TCPARAMETERSET_RECORDSTATUS_NONE || pDatabaseTCParameterSet->GetStatus() == TCPARAMETERSET_RECORDSTATUS_NEW || pDatabaseTCParameterSet->GetStatus() == TCPARAMETERSET_RECORDSTATUS_CHANGED) : TRUE));
		CheckParameterSet(bStatus);
		CheckAttributes(bStatus);
		CheckBitOffset(bStatus);
		CheckConstValue(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameterSet(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckBitOffset(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetItemsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetItemName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETITEM_ILLEGALNAME), (LPCTSTR)GetParameterSet(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetItemsRecordset::CheckParameterSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetName((m_szParameterSet = ExtractText(m_szParameterSet))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETITEM_ILLEGALSETNAME), (LPCTSTR)GetParameterSet(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetItemsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetItemValueInterpretation(GetAttributes(), GetDatabaseEngine()->TranslateTCParameterSetItemValueInterpretation((m_szValueType = ExtractText(m_szValueType)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETITEM_ILLEGALVALUETYPE), (LPCTSTR)GetParameterSet(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCParameterSetItemValueRadix(GetAttributes(), GetDatabaseEngine()->TranslateTCParameterSetItemValueRadix((m_szValueRadix = ExtractText(m_szValueRadix)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETITEM_ILLEGALVALUERADIX), (LPCTSTR)GetParameterSet(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CALTELDatabaseTCParameterSetItemsRecordset::CheckBitOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetItemValueBitOffset(GetBitOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETITEM_ILLEGALBITOFFSET), (LPCTSTR)GetParameterSet(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetItemsRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;

	if (lstrlen((m_szConstValue = ExtractText(m_szConstValue))) > GetDatabaseEngine()->GetTCParameterSetItemConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETITEM_ILLEGALCONSTVALUE), (LPCTSTR)GetParameterSet(), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCParameterSetItemsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCParameterSetItemsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPSP_NAME)), m_szParameterSet);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPSP_PNAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPSP_BITOFF)), m_nBitOffset);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPSP_PVALUE)), m_szConstValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPSP_VTYPE)), m_szValueType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPSP_RADIX)), m_szValueRadix);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParameterSetAssociationsRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseTCParameterSetAssociationsRecordset, CALTELDatabaseRecordset)

CALTELDatabaseTCParameterSetAssociationsRecordset::CALTELDatabaseTCParameterSetAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseTCParameterSetAssociationsRecordset)
	m_szName.Empty();
	m_szFunction.Empty();
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseTCParameterSetAssociationsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseTCParameterSetAssociationsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseTCParameterSetAssociationsRecordset::SetFunction(LPCTSTR pszFunction)
{
	m_szFunction = pszFunction;
}

CString CALTELDatabaseTCParameterSetAssociationsRecordset::GetFunction() CONST
{
	return m_szFunction;
}

VOID CALTELDatabaseTCParameterSetAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseTCParameterSetAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	EnableErrorsByStatus(((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(pszName)))) ? pDatabaseTCParameterSet->GetStatus() : TCPARAMETERSET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszError);
	EnableErrors();
}

VOID CALTELDatabaseTCParameterSetAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseTCParameterSetAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	EnableWarningsByStatus(((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(pszName)))) ? pDatabaseTCParameterSet->GetStatus() : TCPARAMETERSET_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseTCParameterSetAssociationsRecordset::Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet)
{
	SetName(pDatabaseTCParameterSet->GetName());
	SetFunction(pDatabaseTCFunction->GetName());
}

BOOL CALTELDatabaseTCParameterSetAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseTCParameterSetAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(GetName())))) ? (pDatabaseTCParameterSet->GetStatus() == TCPARAMETERSET_RECORDSTATUS_NONE || pDatabaseTCParameterSet->GetStatus() == TCPARAMETERSET_RECORDSTATUS_NEW || pDatabaseTCParameterSet->GetStatus() == TCPARAMETERSET_RECORDSTATUS_CHANGED) : TRUE));
		CheckFunction(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckFunction(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetAssociationsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETASSOCIATION_ILLEGALSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseTCParameterSetAssociationsRecordset::CheckFunction(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionName((m_szFunction = ExtractText(m_szFunction))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETASSOCIATION_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseTCParameterSetAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseTCParameterSetAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCPS_CNAME)), m_szFunction);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCPS_NAME)), m_szName);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseANDDirectoryRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseANDDirectoryRecordset, CALTELDatabaseRecordset)

CALTELDatabaseANDDirectoryRecordset::CALTELDatabaseANDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseANDDirectoryRecordset)
	m_szName.Empty();
	m_szTitle.Empty();
	m_szColumns.Empty();
	m_szStatus.Empty();
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseANDDirectoryRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseANDDirectoryRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseANDDirectoryRecordset::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CALTELDatabaseANDDirectoryRecordset::GetTitle() CONST
{
	return m_szTitle;
}

VOID CALTELDatabaseANDDirectoryRecordset::SetColumns(CONST CUIntArray &nColumns)
{
	m_szColumns = GetDatabaseEngine()->TranslateANDColumns(nColumns);
}

INT CALTELDatabaseANDDirectoryRecordset::GetColumns(CUIntArray &nColumns) CONST
{
	return((GetDatabaseEngine()->TranslateANDColumns(m_szColumns, nColumns)) ? (INT)nColumns.GetSize() : -1);
}

VOID CALTELDatabaseANDDirectoryRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateANDStatus(nStatus);
}

INT CALTELDatabaseANDDirectoryRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateANDStatus(m_szStatus);
}

VOID CALTELDatabaseANDDirectoryRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseANDDirectoryRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CANDLayout  *pANDLayout;

	EnableErrorsByStatus(((pANDLayout = GetDatabaseEngine()->GetANDs()->GetAt(GetDatabaseEngine()->GetANDs()->Find(pszName)))) ? pANDLayout->GetStatus() : ANDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseANDDirectoryRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseANDDirectoryRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CANDLayout  *pANDLayout;

	EnableWarningsByStatus(((pANDLayout = GetDatabaseEngine()->GetANDs()->GetAt(GetDatabaseEngine()->GetANDs()->Find(pszName)))) ? pANDLayout->GetStatus() : ANDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseANDDirectoryRecordset::Translate(CONST CANDLayout *pANDLayout)
{
	CUIntArray  nColumns;

	SetName(pANDLayout->GetName());
	SetTitle(pANDLayout->GetTitle());
	pANDLayout->GetColumns(nColumns);
	SetColumns(nColumns);
	SetStatus(pANDLayout->GetStatus());
}

BOOL CALTELDatabaseANDDirectoryRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseANDDirectoryRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == ANDLAYOUT_RECORDSTATUS_NONE || GetStatus() == ANDLAYOUT_RECORDSTATUS_NEW || GetStatus() == ANDLAYOUT_RECORDSTATUS_CHANGED)));
		CheckTitle(bStatus);
		CheckColumns(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckTitle(IsCollectingIssues());
		bCheck &= CheckColumns(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDDirectoryRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_NORMALAND_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDDirectoryRecordset::CheckTitle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDTitle((m_szTitle = ExtractText(m_szTitle))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_NORMALAND_ILLEGALTITLE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDDirectoryRecordset::CheckColumns(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDColumns((m_szColumns = ExtractText(m_szColumns))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_NORMALAND_ILLEGALLAYOUT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDDirectoryRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_NORMALAND_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseANDDirectoryRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseANDDirectoryRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPF_NUMBER)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPF_DESCR)), m_szTitle);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPF_LAYOUT)), m_szColumns);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPF_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseANDParametersRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseANDParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseANDParametersRecordset::CALTELDatabaseANDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseANDParametersRecordset)
	m_szName.Empty();
	m_szParameter.Empty();
	m_szComment.Empty();
	m_szAlignment.Empty();
	m_szMode.Empty();
	m_nRow = 0;
	m_nCol = 0;
	m_nOccurrence = 0;
	m_nColor = 0;
	m_nDigits = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseANDParametersRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseANDParametersRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseANDParametersRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szParameter = pszTag;
}

CString CALTELDatabaseANDParametersRecordset::GetParameter() CONST
{
	return m_szParameter;
}

VOID CALTELDatabaseANDParametersRecordset::SetComment(LPCTSTR pszComment)
{
	m_szComment = GetDatabaseEngine()->TranslateANDParameterComment(pszComment, FALSE);
}

CString CALTELDatabaseANDParametersRecordset::GetComment() CONST
{
	return GetDatabaseEngine()->TranslateANDParameterComment(m_szComment, TRUE);
}

VOID CALTELDatabaseANDParametersRecordset::SetMode(ULONGLONG nMode)
{
	m_szMode = GetDatabaseEngine()->TranslateANDParameterMode(nMode);
}

ULONGLONG CALTELDatabaseANDParametersRecordset::GetMode() CONST
{
	return GetDatabaseEngine()->TranslateANDParameterMode(m_szMode);
}

VOID CALTELDatabaseANDParametersRecordset::SetRow(INT nRow)
{
	m_nRow = nRow;
}

INT CALTELDatabaseANDParametersRecordset::GetRow() CONST
{
	return m_nRow;
}

VOID CALTELDatabaseANDParametersRecordset::SetCol(INT nCol)
{
	m_nCol = nCol;
}

INT CALTELDatabaseANDParametersRecordset::GetCol() CONST
{
	return m_nCol;
}

VOID CALTELDatabaseANDParametersRecordset::SetOccurrence(INT nOccurrence)
{
	m_nOccurrence = nOccurrence;
}

INT CALTELDatabaseANDParametersRecordset::GetOccurrence() CONST
{
	return m_nOccurrence;
}

VOID CALTELDatabaseANDParametersRecordset::SetColor(INT nColor)
{
	m_nColor = nColor;
}

INT CALTELDatabaseANDParametersRecordset::GetColor() CONST
{
	return m_nColor;
}

VOID CALTELDatabaseANDParametersRecordset::SetDigits(INT nDigits)
{
	m_nDigits = nDigits;
}

INT CALTELDatabaseANDParametersRecordset::GetDigits() CONST
{
	return m_nDigits;
}

VOID CALTELDatabaseANDParametersRecordset::SetAlignment(UINT nAlignment)
{
	m_szAlignment = GetDatabaseEngine()->TranslateANDParameterAlignment(nAlignment);
}

UINT CALTELDatabaseANDParametersRecordset::GetAlignment() CONST
{
	return GetDatabaseEngine()->TranslateANDParameterAlignment(m_szAlignment);
}

VOID CALTELDatabaseANDParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseANDParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CANDLayout  *pANDLayout;

	EnableErrorsByStatus(((pANDLayout = GetDatabaseEngine()->GetANDs()->GetAt(GetDatabaseEngine()->GetANDs()->Find(pszName)))) ? pANDLayout->GetStatus() : ANDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseANDParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseANDParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CANDLayout  *pANDLayout;

	EnableWarningsByStatus(((pANDLayout = GetDatabaseEngine()->GetANDs()->GetAt(GetDatabaseEngine()->GetANDs()->Find(pszName)))) ? pANDLayout->GetStatus() : ANDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseANDParametersRecordset::Translate(CONST CANDLayout *pANDLayout, CONST CANDLayoutParameter *pANDLayoutParameter)
{
	SetName(pANDLayout->GetName());
	SetParameter(pANDLayoutParameter->GetName());
	SetComment(pANDLayoutParameter->GetComment());
	SetMode(pANDLayoutParameter->GetAttributes());
	SetRow(pANDLayoutParameter->GetRow());
	SetCol(pANDLayoutParameter->GetColumn());
	SetOccurrence(pANDLayoutParameter->GetOccurrence());
	SetColor(pANDLayoutParameter->GetColor());
	SetDigits(pANDLayoutParameter->GetDigits());
	SetAlignment(pANDLayoutParameter->GetAlignment());
	return((!pANDLayoutParameter->GetName().IsEmpty() || !pANDLayoutParameter->GetComment().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseANDParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseANDParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CANDLayout  *pLayout;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pLayout = GetDatabaseEngine()->GetANDs()->GetAt(GetDatabaseEngine()->GetANDs()->Find(ExtractText(m_szName))))) ? (pLayout->GetStatus() == ANDLAYOUT_RECORDSTATUS_NONE || pLayout->GetStatus() == ANDLAYOUT_RECORDSTATUS_NEW || pLayout->GetStatus() == ANDLAYOUT_RECORDSTATUS_CHANGED) : TRUE));
		CheckParameter(bStatus);
		CheckComment(bStatus);
		CheckRow(bStatus);
		CheckCol(bStatus);
		CheckMode(bStatus);
		CheckOccurrence(bStatus);
		CheckColor(bStatus);
		CheckDigits(bStatus);
		CheckAlignment(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		for (bCheck = CheckName(IsCollectingIssues()); !CheckParameter(FALSE) && !CheckComment(FALSE); )
		{
			bCheck &= CheckParameter(IsCollectingIssues());
			break;
		}
		bCheck &= CheckRow(IsCollectingIssues());
		bCheck &= CheckCol(IsCollectingIssues());
		bCheck &= CheckMode(IsCollectingIssues());
		bCheck &= CheckOccurrence(IsCollectingIssues());
		bCheck &= CheckColor(IsCollectingIssues());
		bCheck &= CheckDigits(IsCollectingIssues());
		bCheck &= CheckAlignment(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALNAME), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterTag((m_szParameter = ExtractText(m_szParameter))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckComment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterComment((m_szComment = ExtractText(m_szComment))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALCOMMENT), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckRow(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterRow(m_nRow))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALROW), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckCol(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterCol(m_nCol))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALCOL), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckMode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterMode(ExtractText(m_szParameter), m_szMode))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALMODE), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckOccurrence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterOccurrence(ExtractText(m_szParameter), m_nOccurrence))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALOCCURRENCE), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterColor(m_nColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALCOLOR), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckDigits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterDigits(ExtractText(m_szParameter), m_nDigits))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALDIGITS), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseANDParametersRecordset::CheckAlignment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterAlignment(ExtractText(m_szAlignment)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALALIGNMENT), (LPCTSTR)GetName(), (!ExtractText(m_szParameter).IsEmpty()) ? (LPCTSTR)ExtractText(m_szParameter) : (LPCTSTR)ExtractText(m_szComment)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseANDParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseANDParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_NUMBER)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_PNAME)), m_szParameter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_COMMENT)), m_szComment);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_ROW)), m_nRow);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_COL)), m_nCol);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_COLOR)), m_nColor);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_COMM)), m_nOccurrence);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_VALMODE)), m_szMode);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_VALCHARS)), m_nDigits);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPFP_VALALIGN)), m_szAlignment);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseGRDDirectoryRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseGRDDirectoryRecordset, CALTELDatabaseRecordset)

CALTELDatabaseGRDDirectoryRecordset::CALTELDatabaseGRDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseGRDDirectoryRecordset)
	m_szName.Empty();
	m_szTitle.Empty();
	m_szType[0].Empty();
	m_szType[1].Empty();
	m_szMode.Empty();
	m_szStatus.Empty();
	m_nWidth = 0;
	m_nHeight = 0;
	m_nColumns = 0;
	m_nGrids[0] = 0;
	m_nGrids[1] = 0;
	m_nTicks[0] = 0;
	m_nTicks[1] = 0;
	m_nGridsWidth = 0;
	m_nTicksWidth = 0;
	m_nGridsColor = 0;
	m_nTicksColor = 0;
	m_nBkgndColor = 0;
	m_nLabelColor = 0;
	m_nDuration[0] = 0;
	m_nDuration[1] = 0;
	m_nDuration[2] = 0;
	m_nInterval[0] = 0;
	m_nInterval[1] = 0;
	m_nParameters = 0;
	m_nFields = 25;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseGRDDirectoryRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CALTELDatabaseGRDDirectoryRecordset::GetTitle() CONST
{
	return m_szTitle;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetColumns(CONST CUIntArray &nColumns)
{
	m_nColumns = _ttoi(GetDatabaseEngine()->TranslateGRDColumns(nColumns));
}

INT CALTELDatabaseGRDDirectoryRecordset::GetColumns(CUIntArray &nColumns) CONST
{
	CStringTools  cStringTools;

	return((GetDatabaseEngine()->TranslateGRDColumns(cStringTools.ConvertIntToString(m_nColumns), nColumns)) ? (INT)nColumns.GetSize() : -1);
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetType(INT nType)
{
	m_szType[0] = GetDatabaseEngine()->TranslateGRDType(nType);
}

INT CALTELDatabaseGRDDirectoryRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateGRDType(m_szType[0]);
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetMode(INT nMode)
{
	m_szMode = GetDatabaseEngine()->TranslateGRDPlotMode(nMode);
	m_szType[1] = GetDatabaseEngine()->TranslateGRDPlotType(nMode);
}

INT CALTELDatabaseGRDDirectoryRecordset::GetMode() CONST
{
	return GetDatabaseEngine()->TranslateGRDPlotMode(m_szMode) | GetDatabaseEngine()->TranslateGRDPlotType(m_szType[1]);
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetWidth(INT nWidth)
{
	m_nWidth = nWidth;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetWidth() CONST
{
	return m_nWidth;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetHeight(INT nHeight)
{
	m_nHeight = nHeight;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetHeight() CONST
{
	return m_nHeight;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetXGrids(INT nGrids)
{
	m_nGrids[0] = nGrids;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetXGrids() CONST
{
	return m_nGrids[0];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetYGrids(INT nGrids)
{
	m_nGrids[1] = nGrids;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetYGrids() CONST
{
	return m_nGrids[1];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetXTicks(INT nTicks)
{
	m_nTicks[0] = nTicks;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetXTicks() CONST
{
	return m_nTicks[0];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetYTicks(INT nTicks)
{
	m_nTicks[1] = nTicks;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetYTicks() CONST
{
	return m_nTicks[1];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetGridsWidth(INT nWidth)
{
	m_nGridsWidth = nWidth;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetGridsWidth() CONST
{
	return m_nGridsWidth;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetTicksWidth(INT nWidth)
{
	m_nTicksWidth = nWidth;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetTicksWidth() CONST
{
	return m_nTicksWidth;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetGridsColor(INT nColor)
{
	m_nGridsColor = nColor;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetGridsColor() CONST
{
	return m_nGridsColor;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetTicksColor(INT nColor)
{
	m_nTicksColor = nColor;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetTicksColor() CONST
{
	return m_nTicksColor;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetBkgndColor(INT nColor)
{
	m_nBkgndColor = nColor;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetBkgndColor() CONST
{
	return m_nBkgndColor;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetLabelColor(INT nColor)
{
	m_nLabelColor = nColor;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetLabelColor() CONST
{
	return m_nLabelColor;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetDays(INT nDays)
{
	m_nDuration[0] = nDays;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetDays() CONST
{
	return m_nDuration[0];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetHours(INT nHours)
{
	m_nDuration[1] = nHours;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetHours() CONST
{
	return m_nDuration[1];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetMinutes(INT nMinutes)
{
	m_nDuration[2] = nMinutes;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetMinutes() CONST
{
	return m_nDuration[2];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetInterval(INT nInterval)
{
	m_nInterval[0] = nInterval;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetInterval() CONST
{
	return m_nInterval[0];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetUpdateInterval(INT nInterval)
{
	m_nInterval[1] = nInterval;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetUpdateInterval() CONST
{
	return m_nInterval[1];
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetParameters(INT nParameters)
{
	m_nParameters = nParameters;
}

INT CALTELDatabaseGRDDirectoryRecordset::GetParameters() CONST
{
	return m_nParameters;
}

VOID CALTELDatabaseGRDDirectoryRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslateGRDStatus(nStatus);
}

INT CALTELDatabaseGRDDirectoryRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslateGRDStatus(m_szStatus);
}

VOID CALTELDatabaseGRDDirectoryRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseGRDDirectoryRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CGRDLayout  *pGRDLayout;

	EnableErrorsByStatus(((pGRDLayout = GetDatabaseEngine()->GetGRDs()->GetAt(GetDatabaseEngine()->GetGRDs()->Find(pszName)))) ? pGRDLayout->GetStatus() : GRDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseGRDDirectoryRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseGRDDirectoryRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CGRDLayout  *pGRDLayout;

	EnableWarningsByStatus(((pGRDLayout = GetDatabaseEngine()->GetGRDs()->GetAt(GetDatabaseEngine()->GetGRDs()->Find(pszName)))) ? pGRDLayout->GetStatus() : GRDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabaseGRDDirectoryRecordset::Translate(CONST CGRDLayout *pGRDLayout)
{
	INT  nGrids[2];
	INT  nTicks[2];
	CUIntArray  nColumns;

	for (SetName(pGRDLayout->GetName()), SetTitle(pGRDLayout->GetTitle()), SetType(pGRDLayout->GetType()), SetMode(pGRDLayout->GetMode()), SetWidth(pGRDLayout->GetPlotSize().cx), SetHeight(pGRDLayout->GetPlotSize().cy); pGRDLayout->GetColumns(nColumns) >= 0; )
	{
		SetColumns(nColumns);
		break;
	}
	if (pGRDLayout->GetGrids(nGrids[0], nGrids[1]) >= 0)
	{
		SetXGrids(nGrids[0]);
		SetYGrids(nGrids[1]);
	}
	if (pGRDLayout->GetTicks(nTicks[0], nTicks[1]) >= 0)
	{
		SetXTicks(nTicks[0]);
		SetYTicks(nTicks[1]);
	}
	SetGridsWidth(pGRDLayout->GetGridsWidth());
	SetTicksWidth(pGRDLayout->GetTicksWidth());
	SetGridsColor(pGRDLayout->GetGridsColor());
	SetTicksColor(pGRDLayout->GetTicksColor());
	SetBkgndColor(pGRDLayout->GetBackgroundColor());
	SetLabelColor(pGRDLayout->GetLabelColor());
	SetDays((INT)pGRDLayout->GetDuration().GetDays());
	SetHours((INT)pGRDLayout->GetDuration().GetHours());
	SetMinutes((INT)pGRDLayout->GetDuration().GetMinutes());
	SetInterval((INT)(pGRDLayout->GetInterval().GetTotalSeconds() / SECONDSPERMINUTE));
	SetUpdateInterval((INT)(pGRDLayout->GetUpdateInterval().GetTotalSeconds() / SECONDSPERMINUTE));
	SetParameters(pGRDLayout->GetParameters());
	SetStatus(pGRDLayout->GetStatus());
}

BOOL CALTELDatabaseGRDDirectoryRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseGRDDirectoryRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == GRDLAYOUT_RECORDSTATUS_NONE || GetStatus() == GRDLAYOUT_RECORDSTATUS_NEW || GetStatus() == GRDLAYOUT_RECORDSTATUS_CHANGED)));
		CheckTitle(bStatus);
		CheckType(bStatus);
		CheckSubType(bStatus);
		CheckMode(bStatus);
		CheckWidth(bStatus);
		CheckHeight(bStatus);
		CheckColumns(bStatus);
		CheckXGrids(bStatus);
		CheckYGrids(bStatus);
		CheckXTicks(bStatus);
		CheckYTicks(bStatus);
		CheckGridsWidth(bStatus);
		CheckTicksWidth(bStatus);
		CheckGridsColor(bStatus);
		CheckTicksColor(bStatus);
		CheckBkgndColor(bStatus);
		CheckLabelColor(bStatus);
		CheckDays(bStatus);
		CheckHours(bStatus);
		CheckMinutes(bStatus);
		CheckInterval(bStatus);
		CheckUpdateInterval(bStatus);
		CheckParameters(bStatus);
		CheckStatus(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckTitle(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		bCheck &= CheckSubType(IsCollectingIssues());
		bCheck &= CheckMode(IsCollectingIssues());
		bCheck &= CheckWidth(IsCollectingIssues());
		bCheck &= CheckHeight(IsCollectingIssues());
		bCheck &= CheckColumns(IsCollectingIssues());
		bCheck &= CheckXGrids(IsCollectingIssues());
		bCheck &= CheckYGrids(IsCollectingIssues());
		bCheck &= CheckXTicks(IsCollectingIssues());
		bCheck &= CheckYTicks(IsCollectingIssues());
		bCheck &= CheckGridsWidth(IsCollectingIssues());
		bCheck &= CheckTicksWidth(IsCollectingIssues());
		bCheck &= CheckGridsColor(IsCollectingIssues());
		bCheck &= CheckTicksColor(IsCollectingIssues());
		bCheck &= CheckBkgndColor(IsCollectingIssues());
		bCheck &= CheckLabelColor(IsCollectingIssues());
		bCheck &= CheckDays(IsCollectingIssues());
		bCheck &= CheckHours(IsCollectingIssues());
		bCheck &= CheckMinutes(IsCollectingIssues());
		bCheck &= CheckInterval(IsCollectingIssues());
		bCheck &= CheckUpdateInterval(IsCollectingIssues());
		bCheck &= CheckParameters(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckTitle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDTitle((m_szTitle = ExtractText(m_szTitle))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALTITLE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDType(m_szType[0]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALPLOTFLAGS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckSubType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDPlotType(m_szType[0], m_szType[1]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALPLOTTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckMode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDPlotMode(m_szType[0], m_szMode))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALPLOTMODE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDPlotWidth(m_nWidth))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALPLOTWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckHeight(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDPlotHeight(m_nHeight))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALPLOTHEIGHT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckColumns(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDColumns(m_nColumns))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALCOLUMNS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckXGrids(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDXGrids(m_szType[0], m_nGrids[0]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALXGRIDS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckYGrids(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDYGrids(m_szType[0], m_nGrids[1]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALYGRIDS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckXTicks(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDXTicks(m_nTicks[0]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALXTICKS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckYTicks(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDYTicks(m_nTicks[1]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALYTICKS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckGridsWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDGridsWidth(m_nGridsWidth))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALGRIDSWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckTicksWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDTicksWidth(m_nTicksWidth))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALTICKSWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckGridsColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDGridsColor(m_nGridsColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALGRIDSCOLOR), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckTicksColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDTicksColor(m_nTicksColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALTICKSCOLOR), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckBkgndColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDBackgroundColor(m_nBkgndColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALBACKGROUNDCOLOR), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckLabelColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDLabelColor(m_nLabelColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALLABELCOLOR), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckDays(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDDurationDays(m_nDuration[0], m_nDuration[1], m_nDuration[2]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALDURATIONDAYS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckHours(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDDurationHours(m_nDuration[0], m_nDuration[1], m_nDuration[2]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALDURATIONHOURS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckMinutes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDDurationMinutes(m_nDuration[0], m_nDuration[1], m_nDuration[2]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALDURATIONMINUTES), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDInterval(m_szMode, m_nDuration[0], m_nDuration[1], m_nDuration[2], m_nInterval[0]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALINTERVAL), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckUpdateInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDUpdateInterval(m_nDuration[0], m_nDuration[1], m_nDuration[2], m_nInterval[1]))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALUPDATEINTERVAL), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckParameters(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameters((bStatus) ? m_szType[0] : EMPTYSTRING, m_nParameters))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALPARAMETERS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDDirectoryRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseGRDDirectoryRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseGRDDirectoryRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_NUMBER)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_DESCR)), m_szTitle);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_TYPE)), m_szType[0]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_SUBTYPE)), m_szType[1]);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_MODE)), m_szMode);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_LAYOUT)), m_nColumns);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_DAYS)), m_nDuration[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_HOURS)), m_nDuration[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_MINUTES)), m_nDuration[2]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_INTERVAL)), m_nInterval[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_UPDATE)), m_nInterval[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_WIDTH)), m_nWidth);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_HEIGHT)), m_nHeight);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_XGRIDS)), m_nGrids[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_YGRIDS)), m_nGrids[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_XTICKS)), m_nTicks[0]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_YTICKS)), m_nTicks[1]);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_GRIDSWIDTH)), m_nGridsWidth);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_TICKSWIDTH)), m_nTicksWidth);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_GRIDSCOLOR)), m_nGridsColor);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_TICKSCOLOR)), m_nTicksColor);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_BKGNDCOLOR)), m_nBkgndColor);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_LABELCOLOR)), m_nLabelColor);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_PARAMETERS)), m_nParameters);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseGRDParametersRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabaseGRDParametersRecordset, CALTELDatabaseRecordset)

CALTELDatabaseGRDParametersRecordset::CALTELDatabaseGRDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabaseGRDParametersRecordset)
	m_szName.Empty();
	m_szMode.Empty();
	m_szComment.Empty();
	m_szParameter.Empty();
	m_szLineStyle.Empty();
	m_szLineSymbol.Empty();
	m_nLineWidth = 0;
	m_fMinimum = 0.0;
	m_fMaximum = 0.0;
	m_nOccurrence = 0;
	m_nPosition = 0;
	m_nDigits = 0;
	m_nColor = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabaseGRDParametersRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabaseGRDParametersRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabaseGRDParametersRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szParameter = pszTag;
}

CString CALTELDatabaseGRDParametersRecordset::GetParameter() CONST
{
	return m_szParameter;
}

VOID CALTELDatabaseGRDParametersRecordset::SetComment(LPCTSTR pszComment)
{
	m_szComment = pszComment;
}

CString CALTELDatabaseGRDParametersRecordset::GetComment() CONST
{
	return m_szComment;
}

VOID CALTELDatabaseGRDParametersRecordset::SetMode(ULONGLONG nMode)
{
	m_szMode = GetDatabaseEngine()->TranslateGRDParameterMode(nMode);
}

ULONGLONG CALTELDatabaseGRDParametersRecordset::GetMode() CONST
{
	return GetDatabaseEngine()->TranslateGRDParameterMode(m_szMode);
}

VOID CALTELDatabaseGRDParametersRecordset::SetMinimum(double fMinimum)
{
	m_fMinimum = fMinimum;
}

double CALTELDatabaseGRDParametersRecordset::GetMinimum() CONST
{
	return m_fMinimum;
}

VOID CALTELDatabaseGRDParametersRecordset::SetMaximum(double fMaximum)
{
	m_fMaximum = fMaximum;
}

double CALTELDatabaseGRDParametersRecordset::GetMaximum() CONST
{
	return m_fMaximum;
}

VOID CALTELDatabaseGRDParametersRecordset::SetOccurrence(INT nOccurrence)
{
	m_nOccurrence = nOccurrence;
}

INT CALTELDatabaseGRDParametersRecordset::GetOccurrence() CONST
{
	return m_nOccurrence;
}

VOID CALTELDatabaseGRDParametersRecordset::SetColor(INT nColor)
{
	m_nColor = nColor;
}

INT CALTELDatabaseGRDParametersRecordset::GetColor() CONST
{
	return m_nColor;
}

VOID CALTELDatabaseGRDParametersRecordset::SetDigits(INT nDigits)
{
	m_nDigits = nDigits;
}

INT CALTELDatabaseGRDParametersRecordset::GetDigits() CONST
{
	return m_nDigits;
}

VOID CALTELDatabaseGRDParametersRecordset::SetPosition(INT nPosition)
{
	m_nPosition = nPosition;
}

INT CALTELDatabaseGRDParametersRecordset::GetPosition() CONST
{
	return m_nPosition;
}

VOID CALTELDatabaseGRDParametersRecordset::SetLineWidth(INT nWidth)
{
	m_nLineWidth = nWidth;
}

INT CALTELDatabaseGRDParametersRecordset::GetLineWidth() CONST
{
	return m_nLineWidth;
}

VOID CALTELDatabaseGRDParametersRecordset::SetLineStyle(INT nStyle)
{
	m_szLineStyle = GetDatabaseEngine()->TranslateGRDParameterLineStyle(nStyle);
}

INT CALTELDatabaseGRDParametersRecordset::GetLineStyle() CONST
{
	return GetDatabaseEngine()->TranslateGRDParameterLineStyle(m_szLineStyle);
}

VOID CALTELDatabaseGRDParametersRecordset::SetLineSymbol(INT nSymbol)
{
	m_szLineSymbol = GetDatabaseEngine()->TranslateGRDParameterLineSymbol(nSymbol);
}

INT CALTELDatabaseGRDParametersRecordset::GetLineSymbol() CONST
{
	return GetDatabaseEngine()->TranslateGRDParameterLineSymbol(m_szLineSymbol);
}

VOID CALTELDatabaseGRDParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabaseGRDParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CGRDLayout  *pGRDLayout;

	EnableErrorsByStatus(((pGRDLayout = GetDatabaseEngine()->GetGRDs()->GetAt(GetDatabaseEngine()->GetGRDs()->Find(pszName)))) ? pGRDLayout->GetStatus() : GRDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabaseGRDParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabaseGRDParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CGRDLayout  *pGRDLayout;

	EnableWarningsByStatus(((pGRDLayout = GetDatabaseEngine()->GetGRDs()->GetAt(GetDatabaseEngine()->GetGRDs()->Find(pszName)))) ? pGRDLayout->GetStatus() : GRDLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

BOOL CALTELDatabaseGRDParametersRecordset::Translate(CONST CGRDLayout *pGRDLayout, CONST CGRDLayoutParameter *pGRDLayoutParameter)
{
	double  fMinimum;
	double  fMaximum;

	for (SetName(pGRDLayout->GetName()), SetParameter(pGRDLayoutParameter->GetName()), SetComment(pGRDLayoutParameter->GetComment()), SetMode(pGRDLayoutParameter->GetAttributes()), SetOccurrence(pGRDLayoutParameter->GetOccurrence()); pGRDLayoutParameter->GetRange(fMinimum, fMaximum) >= 0; )
	{
		SetMinimum(fMinimum);
		SetMaximum(fMaximum);
		break;
	}
	SetColor(pGRDLayoutParameter->GetColor());
	SetDigits(pGRDLayoutParameter->GetDigits());
	SetPosition(pGRDLayoutParameter->GetPosition());
	SetLineWidth(pGRDLayoutParameter->GetLineWidth());
	SetLineStyle(pGRDLayoutParameter->GetLineStyle());
	SetLineSymbol(pGRDLayoutParameter->GetLineSymbol());
	return((!pGRDLayoutParameter->GetName().IsEmpty()) ? TRUE : FALSE);
}

BOOL CALTELDatabaseGRDParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabaseGRDParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;
	CGRDLayout  *pLayout;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = ((pLayout = GetDatabaseEngine()->GetGRDs()->GetAt(GetDatabaseEngine()->GetGRDs()->Find(ExtractText(m_szName))))) ? (pLayout->GetStatus() == GRDLAYOUT_RECORDSTATUS_NONE || pLayout->GetStatus() == GRDLAYOUT_RECORDSTATUS_NEW || pLayout->GetStatus() == GRDLAYOUT_RECORDSTATUS_CHANGED) : TRUE));
		CheckParameter(bStatus);
		CheckComment(bStatus);
		CheckPosition(bStatus);
		CheckMode(bStatus);
		CheckOccurrence(bStatus);
		CheckColor(bStatus);
		CheckDigits(bStatus);
		CheckLineStyle(bStatus);
		CheckLineSymbol(bStatus);
		CheckLineWidth(bStatus);
		CheckMinimum(bStatus);
		CheckMaximum(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckMode(IsCollectingIssues());
		bCheck &= CheckOccurrence(IsCollectingIssues());
		bCheck &= CheckColor(IsCollectingIssues());
		bCheck &= CheckDigits(IsCollectingIssues());
		bCheck &= CheckLineStyle(IsCollectingIssues());
		bCheck &= CheckLineSymbol(IsCollectingIssues());
		bCheck &= CheckLineWidth(IsCollectingIssues());
		bCheck &= CheckMinimum(IsCollectingIssues());
		bCheck &= CheckMaximum(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterTag((m_szParameter = ExtractText(m_szParameter))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckComment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterComment((m_szComment = ExtractText(m_szComment))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALCOMMENT), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckPosition(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterPosition(m_nPosition))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALPOSITION), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckMode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterMode(m_szMode))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALMODE), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckMinimum(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterMinimum(m_fMinimum))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALMINIMUM), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckMaximum(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterMaximum(m_fMaximum))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALMAXIMUM), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckOccurrence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterOccurrence(m_nOccurrence))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALOCCURRENCE), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterColor(m_nColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALCOLOR), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckDigits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterDigits(m_nDigits))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALDIGITS), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckLineStyle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterLineStyle(m_szLineStyle))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALLINESTYLE), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckLineSymbol(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterLineSymbol(m_szLineSymbol))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALLINESYMBOL), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabaseGRDParametersRecordset::CheckLineWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterLineWidth(m_nLineWidth))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALLINEWIDTH), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szParameter)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabaseGRDParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabaseGRDParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_NUMBER)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_PNAME)), m_szParameter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_COMMENT)), m_szComment);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_POSITION)), m_nPosition);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_COMM)), m_nOccurrence);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_VALMODE)), m_szMode);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_VALCHARS)), m_nDigits);
	RFX_Double(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_VALMINIMUM)), m_fMinimum);
	RFX_Double(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_VALMAXIMUM)), m_fMaximum);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_COLOR)), m_nColor);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_LINEWIDTH)), m_nLineWidth);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_LINESTYLE)), m_szLineStyle);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPFP_LINESYMBOL)), m_szLineSymbol);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabasePODDirectoryRecordset recordset

IMPLEMENT_DYNAMIC(CALTELDatabasePODDirectoryRecordset, CALTELDatabaseRecordset)

CALTELDatabasePODDirectoryRecordset::CALTELDatabasePODDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CALTELDatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CALTELDatabasePODDirectoryRecordset)
	m_szName.Empty();
	m_szTitle.Empty();
	m_szExpressionStack.Empty();
	m_szParameters.Empty();
	m_szFunctions.Empty();
	m_szStatus.Empty();
	m_nExpressionColor = 0;
	m_nParametersColor = 0;
	m_nFunctionsColor = 0;
	m_nColumns = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
}

VOID CALTELDatabasePODDirectoryRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CALTELDatabasePODDirectoryRecordset::GetName() CONST
{
	return m_szName;
}

VOID CALTELDatabasePODDirectoryRecordset::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CALTELDatabasePODDirectoryRecordset::GetTitle() CONST
{
	return m_szTitle;
}

VOID CALTELDatabasePODDirectoryRecordset::SetColumns(UINT nColumns)
{
	m_nColumns = nColumns;
}

UINT CALTELDatabasePODDirectoryRecordset::GetColumns() CONST
{
	return m_nColumns;
}

VOID CALTELDatabasePODDirectoryRecordset::SetExpressionStack(CONST CStringArray &szStack)
{
	m_szExpressionStack = GetDatabaseEngine()->TranslatePODExpressionStack(szStack);
}

INT CALTELDatabasePODDirectoryRecordset::GetExpressionStack(CStringArray &szStack, CByteArray &bFunctions, CByteArray &bOperators, CByteArray &bParameters, CByteArray &bNumbers) CONST
{
	return GetDatabaseEngine()->TranslatePODExpressionStack(m_szExpressionStack, szStack, bFunctions, bOperators, bParameters, bNumbers);
}

VOID CALTELDatabasePODDirectoryRecordset::SetExpressionColor(INT nColor)
{
	m_nExpressionColor = nColor;
}

INT CALTELDatabasePODDirectoryRecordset::GetExpressionColor() CONST
{
	return m_nExpressionColor;
}

VOID CALTELDatabasePODDirectoryRecordset::SetParameters(CONST CStringArray &szParameters)
{
	m_szParameters = GetDatabaseEngine()->TranslatePODParameters(szParameters);
}

INT CALTELDatabasePODDirectoryRecordset::GetParameters(CStringArray &szParameters) CONST
{
	return GetDatabaseEngine()->TranslatePODParameters(m_szParameters, szParameters);
}

VOID CALTELDatabasePODDirectoryRecordset::SetParametersColor(INT nColor)
{
	m_nParametersColor = nColor;
}

INT CALTELDatabasePODDirectoryRecordset::GetParametersColor() CONST
{
	return m_nParametersColor;
}

VOID CALTELDatabasePODDirectoryRecordset::SetFunctions(CONST CStringArray &szFunctions)
{
	m_szFunctions = GetDatabaseEngine()->TranslatePODFunctions(szFunctions);
}

INT CALTELDatabasePODDirectoryRecordset::GetFunctions(CStringArray &szFunctions) CONST
{
	return GetDatabaseEngine()->TranslatePODFunctions(m_szFunctions, szFunctions);
}

VOID CALTELDatabasePODDirectoryRecordset::SetFunctionsColor(INT nColor)
{
	m_nFunctionsColor = nColor;
}

INT CALTELDatabasePODDirectoryRecordset::GetFunctionsColor() CONST
{
	return m_nFunctionsColor;
}

VOID CALTELDatabasePODDirectoryRecordset::SetStatus(INT nStatus)
{
	m_szStatus = GetDatabaseEngine()->TranslatePODStatus(nStatus);
}

INT CALTELDatabasePODDirectoryRecordset::GetStatus() CONST
{
	return GetDatabaseEngine()->TranslatePODStatus(m_szStatus);
}

VOID CALTELDatabasePODDirectoryRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CALTELDatabasePODDirectoryRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CPODLayout  *pPODLayout;

	EnableErrorsByStatus(((pPODLayout = GetDatabaseEngine()->GetPODs()->GetAt(GetDatabaseEngine()->GetPODs()->Find(pszName)))) ? pPODLayout->GetStatus() : PODLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE, pszError);
	EnableErrors();
}

VOID CALTELDatabasePODDirectoryRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CALTELDatabasePODDirectoryRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CPODLayout  *pPODLayout;

	EnableWarningsByStatus(((pPODLayout = GetDatabaseEngine()->GetPODs()->GetAt(GetDatabaseEngine()->GetPODs()->Find(pszName)))) ? pPODLayout->GetStatus() : PODLAYOUT_RECORDSTATUS_NONE);
	CALTELDatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE, pszWarning);
	EnableWarnings();
}

VOID CALTELDatabasePODDirectoryRecordset::Translate(CONST CPODLayout *pPODLayout)
{
	INT  nIndex;
	INT  nCount;
	INT  nSample;
	CString  szTag;
	CString  szParameter;
	ULONGLONG  nAttributes;
	CStringArray  szStack;
	CStringArray  szFunctions;
	CStringArray  szParameters;
	CStringTools  cStringTools;
	CPODLayoutExpression  *pExpression;

	SetName(pPODLayout->GetName());
	SetTitle(pPODLayout->GetTitle());
	SetColumns(pPODLayout->GetColumns());
	for (nIndex = 0, nCount = (INT)pPODLayout->GetSize(), pPODLayout->GetParameters(szParameters), pPODLayout->GetFunctions(szFunctions); nIndex < nCount; nIndex++)
	{
		if ((pExpression = pPODLayout->GetAt(nIndex)))
		{
			if (pExpression->IsFunction())
			{
				szStack.Add(pExpression->GetFunction());
				continue;
			}
			if (pExpression->IsOperator())
			{
				szStack.Add(pExpression->GetOperator());
				continue;
			}
			if (pExpression->IsParameter() && pExpression->GetParameter(szTag, nSample, nAttributes))
			{
				szParameter.Format(STRING(IDS_DATABASE_TABLE_PPF_PARAMETERFORMAT), (LPCTSTR)szTag, nSample, nAttributes);
				szStack.Add(szParameter);
				continue;
			}
			if (pExpression->IsNumber())
			{
				szStack.Add(cStringTools.ConvertFloatToString(pExpression->GetNumber()));
				continue;
			}
		}
	}
	SetExpressionStack(szStack);
	SetParameters(szParameters);
	SetFunctions(szFunctions);
	SetExpressionColor(pPODLayout->GetExpressionColor());
	SetParametersColor(pPODLayout->GetParametersColor());
	SetFunctionsColor(pPODLayout->GetFunctionsColor());
	SetStatus(pPODLayout->GetStatus());
}

BOOL CALTELDatabasePODDirectoryRecordset::Check(CStringArray &szIssues, BOOL bAppend)
{
	BOOL  bCheck;
	CStringArray  szMessages;

	for (CollectIssues(), bCheck = Check(); CollectIssues(szMessages) > 0; )
	{
		if (!bAppend) szIssues.Copy(szMessages);
		else  szIssues.Append(szMessages);
		break;
	}
	return bCheck;
}
BOOL CALTELDatabasePODDirectoryRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	BOOL  bStatus;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName((bStatus = (GetStatus() == PODLAYOUT_RECORDSTATUS_NONE || GetStatus() == PODLAYOUT_RECORDSTATUS_NEW || GetStatus() == PODLAYOUT_RECORDSTATUS_CHANGED)));
		CheckTitle(bStatus);
		CheckColumns(bStatus);
		CheckExpressionStack(bStatus);
		CheckParameters(bStatus);
		CheckFunctions(bStatus);
		CheckExpressionColor(bStatus);
		CheckParametersColor(bStatus);
		CheckFunctionsColor(bStatus);
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckTitle(IsCollectingIssues());
		bCheck &= CheckColumns(IsCollectingIssues());
		bCheck &= CheckExpressionStack(IsCollectingIssues());
		bCheck &= CheckExpressionColor(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckTitle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODTitle((m_szTitle = ExtractText(m_szTitle))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALTITLE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckColumns(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODColumns(m_nColumns))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALCOLUMNS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckExpressionStack(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODExpressionStack(m_szExpressionStack))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALEXPRESSIONSTACK), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckExpressionColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODExpressionStackElementColor(m_nExpressionColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALEXPRESSIONCOLOR), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckParameters(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODParameters(m_szParameters))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALPARAMETERS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckParametersColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODParametersColor(m_nParametersColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALPARAMETERSCOLOR), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckFunctions(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODFunctions(m_szFunctions))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALFUNCTIONS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckFunctionsColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODFunctionsColor(m_nFunctionsColor))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALFUNCTIONSCOLOR), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CALTELDatabasePODDirectoryRecordset::CheckStatus(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODStatus((m_szStatus = ExtractText(m_szStatus))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALSTATUS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CALTELDatabasePODDirectoryRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CALTELDatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CALTELDatabasePODDirectoryRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_NUMBER)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_DESCR)), m_szTitle);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_LAYOUT)), m_nColumns);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_EXPRESSIONSTACK)), m_szExpressionStack);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_EXPRESSIONCOLOR)), m_nExpressionColor);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_PARAMETERS)), m_szParameters);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_PARAMETERSCOLOR)), m_nParametersColor);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_FUNCTIONS)), m_szFunctions);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_FUNCTIONSCOLOR)), m_nFunctionsColor);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PPF_STATUS)), m_szStatus);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}
