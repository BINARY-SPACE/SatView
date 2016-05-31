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
* 2012/06/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#define LIBRARYENVIRONMENT
#define SCOS2000ENVIRONMENT

#include "SCOS-2000.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseRecordset, CRecordset)

CSCOS2000DatabaseRecordset::CSCOS2000DatabaseRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CRecordset(pDatabaseEngine -> GetDBMS())
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseRecordset)
	m_nFields = 0;
	//}}AFX_FIELD_INIT

	m_pDatabaseEngine = pDatabaseEngine;
	m_bWarnings = TRUE;
	m_bErrors = TRUE;
	m_bIssues = FALSE;
}

BOOL CSCOS2000DatabaseRecordset::Open(UINT nOpenType, LPCTSTR lpszSQL, DWORD dwOptions)
{
	return CRecordset::Open(nOpenType, lpszSQL, dwOptions);
}

VOID CSCOS2000DatabaseRecordset::ShowError(LPCTSTR pszError)
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
VOID CSCOS2000DatabaseRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszError)
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

INT CSCOS2000DatabaseRecordset::GetErrors(CStringArray &szErrors) CONST
{
	szErrors.Copy(m_szErrors);
	return((INT)szErrors.GetSize());
}
INT CSCOS2000DatabaseRecordset::GetErrors(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szErrors) CONST
{
	szNames.Copy(m_szNames[0]);
	szInfos.Copy(m_szInfos[0]);
	szErrors.Copy(m_szErrors);
	nComponents.Copy(m_nComponents[0]);
	return((INT)szErrors.GetSize());
}

VOID CSCOS2000DatabaseRecordset::EnableErrors(BOOL bEnable)
{
	m_bErrors = bEnable;
}

INT CSCOS2000DatabaseRecordset::GetErrorCount() CONST
{
	return((INT)m_szErrors.GetSize());
}

VOID CSCOS2000DatabaseRecordset::ResetErrors()
{
	m_szNames[0].RemoveAll();
	m_szInfos[0].RemoveAll();
	m_szErrors.RemoveAll();
	m_nComponents[0].RemoveAll();
}

VOID CSCOS2000DatabaseRecordset::ShowWarning(LPCTSTR pszWarning)
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
VOID CSCOS2000DatabaseRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszWarning)
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

INT CSCOS2000DatabaseRecordset::GetWarnings(CStringArray &szWarnings) CONST
{
	szWarnings.Copy(m_szWarnings);
	return((INT)szWarnings.GetSize());
}
INT CSCOS2000DatabaseRecordset::GetWarnings(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szWarnings) CONST
{
	szNames.Copy(m_szNames[1]);
	szInfos.Copy(m_szInfos[1]);
	szWarnings.Copy(m_szWarnings);
	nComponents.Copy(m_nComponents[1]);
	return((INT)szWarnings.GetSize());
}

VOID CSCOS2000DatabaseRecordset::EnableWarnings(BOOL bEnable)
{
	m_bWarnings = bEnable;
}

INT CSCOS2000DatabaseRecordset::GetWarningCount() CONST
{
	return((INT)m_szWarnings.GetSize());
}

VOID CSCOS2000DatabaseRecordset::ResetWarnings()
{
	m_szNames[1].RemoveAll();
	m_szInfos[1].RemoveAll();
	m_szWarnings.RemoveAll();
	m_nComponents[1].RemoveAll();
}

VOID CSCOS2000DatabaseRecordset::CollectIssues(BOOL bEnable)
{
	m_bIssues = bEnable;
	m_szIssues.RemoveAll();
}
INT CSCOS2000DatabaseRecordset::CollectIssues(CStringArray &szIssues, BOOL bStop)
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

BOOL CSCOS2000DatabaseRecordset::IsCollectingIssues() CONST
{
	return m_bIssues;
}

CString CSCOS2000DatabaseRecordset::ConstructFieldName(LPCTSTR pszField) CONST
{
	CString  szName;

	szName.Format(STRING(IDS_DATABASE_TABLE_FIELD_FORMAT), pszField);
	return szName;
}

CString CSCOS2000DatabaseRecordset::ExtractText(LPCTSTR pszField) CONST
{
	CString  szText(pszField);

	return szText.Trim();
}

CONST CDatabaseEngine *CSCOS2000DatabaseRecordset::GetDatabaseEngine() CONST
{
	return m_pDatabaseEngine;
}

void CSCOS2000DatabaseRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CIdle  cIdle;

	//{{AFX_FIELD_MAP(CSCOS2000DatabaseRecordset)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_FIELD_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseVersionsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseVersionsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseVersionsRecordset::CSCOS2000DatabaseVersionsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseVersionsRecordset)
	m_szName.Empty();
	m_szComment.Empty();
	m_nDomainID = 0;
	m_nRelease = 0;
	m_nIssue = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseVersionsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseVersionsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseVersionsRecordset::SetComment(LPCTSTR pszComment)
{
	m_szComment = pszComment;
}

CString CSCOS2000DatabaseVersionsRecordset::GetComment() CONST
{
	return m_szComment;
}

VOID CSCOS2000DatabaseVersionsRecordset::SetDomainID(INT nDomainID)
{
	m_nDomainID = nDomainID;
}

INT CSCOS2000DatabaseVersionsRecordset::GetDomainID() CONST
{
	return m_nDomainID;
}

VOID CSCOS2000DatabaseVersionsRecordset::SetRelease(INT nRelease)
{
	m_nRelease = nRelease;
}

INT CSCOS2000DatabaseVersionsRecordset::GetRelease() CONST
{
	return m_nRelease;
}

VOID CSCOS2000DatabaseVersionsRecordset::SetIssue(INT nIssue)
{
	m_nIssue = nIssue;
}

INT CSCOS2000DatabaseVersionsRecordset::GetIssue() CONST
{
	return m_nIssue;
}

VOID CSCOS2000DatabaseVersionsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseVersionsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_PROPERTY_VERSION, pszError);
}

VOID CSCOS2000DatabaseVersionsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseVersionsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_PROPERTY_VERSION, pszWarning);
}

VOID CSCOS2000DatabaseVersionsRecordset::Translate(CONST CDatabaseVersion *pDatabaseVersion)
{
	SetName(pDatabaseVersion->GetName());
	SetComment(pDatabaseVersion->GetComment());
	SetDomainID(GetDatabaseEngine()->TranslateVersionDomain(pDatabaseVersion->GetDomain()));
	SetRelease(GetDatabaseEngine()->TranslateVersionRelease(pDatabaseVersion->GetRelease()));
	SetIssue(GetDatabaseEngine()->TranslateVersionIssue(pDatabaseVersion->GetIssue()));
}

BOOL CSCOS2000DatabaseVersionsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseVersionsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckComment();
		CheckDomainID();
		CheckRelease();
		CheckIssue();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseVersionsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckVersionName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_VERSION_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseVersionsRecordset::CheckComment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckVersionComment((m_szComment = ExtractText(m_szComment))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_VERSION_ILLEGALCOMMENT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseVersionsRecordset::CheckDomainID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckVersionDomain(GetDatabaseEngine()->TranslateVersionDomain(m_nDomainID)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_VERSION_ILLEGALDOMAINID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseVersionsRecordset::CheckRelease(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckVersionRelease(GetDatabaseEngine()->TranslateVersionRelease(m_nRelease)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_VERSION_ILLEGALRELEASE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseVersionsRecordset::CheckIssue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckVersionIssue(GetDatabaseEngine()->TranslateVersionIssue(m_nIssue)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_VERSION_ILLEGALISSUE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseVersionsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseVersionsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VDF_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VDF_COMMENT)), m_szComment);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VDF_DOMAINID)), m_nDomainID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VDF_RELEASE)), m_nRelease);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VDF_ISSUE)), m_nIssue);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketIdentificationsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketIdentificationsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketIdentificationsRecordset::CSCOS2000DatabaseTMPacketIdentificationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketIdentificationsRecordset)
	m_szDescr.Empty();
	m_szUnit.Empty();
	m_szTime.Empty();
	m_szValid.Empty();
	m_szEvent.Empty();
	m_szEvId.Empty();
	m_nType = 0;
	m_nSType = 0;
	m_nAPID = 0;
	m_nPI1Val = 0;
	m_nPI2Val = 0;
	m_nSPID = 0;
	m_nTPSD = 0;
	m_nDfhSize = 0;
	m_nInter = 0;
	m_nCheck = 0;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetName() CONST
{
	CDatabaseTMPacketIdentification  cDatabaseTMPacketIdentification;

	cDatabaseTMPacketIdentification.SetType(GetType());
	cDatabaseTMPacketIdentification.SetSubType(GetSubType());
	cDatabaseTMPacketIdentification.SetAPID(GetAPID());
	cDatabaseTMPacketIdentification.SetFirstIDValue(GetFirstIDValue());
	cDatabaseTMPacketIdentification.SetSecondIDValue(GetSecondIDValue());
	cDatabaseTMPacketIdentification.SetValid(IsValid());
	return((m_szName.IsEmpty()) ? cDatabaseTMPacketIdentification.GetName() : m_szName);
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetType(INT nType)
{
	m_nType = nType;
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetType() CONST
{
	return m_nType;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetSubType(INT nSubType)
{
	m_nSType = nSubType;
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetSubType() CONST
{
	return m_nSType;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetAPID(INT nAPID)
{
	m_nAPID = nAPID;
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetAPID() CONST
{
	return m_nAPID;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetFirstIDValue(INT nValue)
{
	m_nPI1Val = nValue;
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetFirstIDValue() CONST
{
	return m_nPI1Val;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetSecondIDValue(INT nValue)
{
	m_nPI2Val = nValue;
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetSecondIDValue() CONST
{
	return m_nPI2Val;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetPacketID(UINT nID)
{
	m_nSPID = nID;
}
VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetPacketID(LPCTSTR pszID)
{
	m_nSPID = (UINT)_ttoi64(pszID);
}

CString CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetPacketID() CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertUIntToString(m_nSPID);
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetContentID(INT nContentID)
{
	m_nTPSD = nContentID;
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetContentID() CONST
{
	return m_nTPSD;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetDataFieldHeaderSize(INT nSize)
{
	m_nDfhSize = nSize;
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetDataFieldHeaderSize() CONST
{
	return m_nDfhSize;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetTimestampFlag(BOOL bFlag)
{
	m_szTime = GetDatabaseEngine()->TranslateTMPacketTimestampFlag(bFlag);
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetTimestampFlag() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketTimestampFlag(m_szTime);
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetEventType(INT nType)
{
	m_szEvent = GetDatabaseEngine()->TranslateTMPacketEventType(nType);
}

INT CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetEventType() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketEventType(m_szEvent);
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetEventID(LPCTSTR pszID)
{
	m_szEvId = pszID;
}

CString CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetEventID() CONST
{
	return m_szEvId;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetTransmissionRate(DWORD dwInterval)
{
	m_nInter = dwInterval;
}

DWORD CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetTransmissionRate() CONST
{
	return m_nInter;
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetCRCFlag(BOOL bEnable)
{
	m_nCheck = bEnable;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::GetCRCFlag() CONST
{
	return((m_nCheck != 0) ? TRUE : FALSE);
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::SetValid(BOOL bValid)
{
	m_szValid = GetDatabaseEngine()->TranslateTMPacketIdentificationValidityFlag(bValid);
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::IsValid() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketIdentificationValidityFlag(m_szValid);
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetName(), pszError);
}
VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION, pszError);
}

VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetName(), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketIdentificationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION, pszWarning);
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::Translate(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification)
{
	SetName(pDatabaseTMPacketIdentification->GetName());
	SetType(pDatabaseTMPacketIdentification->GetType());
	SetSubType(pDatabaseTMPacketIdentification->GetSubType());
	SetAPID(pDatabaseTMPacketIdentification->GetAPID());
	SetFirstIDValue(pDatabaseTMPacketIdentification->GetFirstIDValue());
	SetSecondIDValue(pDatabaseTMPacketIdentification->GetSecondIDValue());
	SetPacketID(pDatabaseTMPacketIdentification->GetPacketID());
	SetDescription(pDatabaseTMPacketIdentification->GetDescription());
	SetUnit(pDatabaseTMPacketIdentification->GetUnit());
	SetContentID(pDatabaseTMPacketIdentification->GetContentID());
	SetDataFieldHeaderSize(pDatabaseTMPacketIdentification->GetDataFieldHeaderSize());
	SetTimestampFlag(pDatabaseTMPacketIdentification->GetTimestampFlag());
	SetEventType(pDatabaseTMPacketIdentification->GetEventType());
	SetEventID(pDatabaseTMPacketIdentification->GetEventID());
	SetTransmissionRate(pDatabaseTMPacketIdentification->GetTransmissionRate());
	SetCRCFlag(pDatabaseTMPacketIdentification->GetCRCFlag());
	SetValid(pDatabaseTMPacketIdentification->IsValid());
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckType();
		CheckSubType();
		CheckAPID();
		CheckFirstIDValue();
		CheckSecondIDValue();
		CheckPacketID();
		CheckDescription();
		CheckUnit();
		CheckContentID();
		CheckDataFieldHeaderSize();
		CheckTimestampFlag();
		CheckEventType();
		CheckEventID();
		CheckTransmissionRate();
		CheckCRCFlag();
		CheckValidityFlag();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckType(IsCollectingIssues());
		bCheck &= CheckSubType(IsCollectingIssues());
		bCheck &= CheckAPID(IsCollectingIssues());
		bCheck &= CheckFirstIDValue(IsCollectingIssues());
		bCheck &= CheckSecondIDValue(IsCollectingIssues());
		bCheck &= CheckPacketID(IsCollectingIssues());
		bCheck &= CheckContentID(IsCollectingIssues());
		bCheck &= CheckDataFieldHeaderSize(IsCollectingIssues());
		bCheck &= CheckTimestampFlag(IsCollectingIssues());
		bCheck &= CheckEventType(IsCollectingIssues());
		bCheck &= CheckCRCFlag(IsCollectingIssues());
		bCheck &= CheckValidityFlag(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketType(m_nType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckSubType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSubType(m_nSType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALSUBTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketAPID(m_nAPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALAPID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckFirstIDValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketFirstFieldValue(m_nPI1Val))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALFIRSTFIELDVALUE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckSecondIDValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSecondFieldValue(m_nPI2Val))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALSECONDFIELDVALUE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckPacketID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketID(m_nSPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDescription((m_szDescr = ExtractText(m_szDescr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckUnit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSubSystem((m_szUnit = ExtractText(m_szUnit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALUNIT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckContentID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketContentID(m_nTPSD))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALCONTENTID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckDataFieldHeaderSize(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDataFieldHeaderSize(m_nDfhSize))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALDATAFIELDHEADERSIZE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckTimestampFlag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTimestampFlag((m_szTime = ExtractText(m_szTime))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALTIMESTAMPFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckEventType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketEventType(GetEventType()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALEVENTTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckEventID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketEventID(GetEventType(), (m_szEvId = ExtractText(m_szEvId))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALEVENTMESSAGE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckTransmissionRate(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketTransmissionRate((m_nInter > 0) ? TMPACKET_TMTYPE_CYCLIC : -1, m_nInter))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALTRANSMISSIONINTERVAL), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckCRCFlag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketCyclicRedundancyCheckFlag(m_nCheck))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALTRANSMISSIONINTERVAL), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationsRecordset::CheckValidityFlag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketIdentificationValidityFlag((m_szValid = ExtractText(m_szValid))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATION_ILLEGALVALIDITYFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketIdentificationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMPacketIdentificationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_TYPE)), m_nType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_STYPE)), m_nSType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_APID)), m_nAPID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_PI1_VAL)), m_nPI1Val);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_PI2_VAL)), m_nPI2Val);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_SPID)), m_nSPID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_UNIT)), m_szUnit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_TPSD)), m_nTPSD);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_DFHSIZE)), m_nDfhSize);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_TIME)), m_szTime);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_INTER)), m_nInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_VALID)), m_szValid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_CHECK)), m_nCheck);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_EVENT)), m_szEvent);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PID_EVID)), m_szEvId);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset)
	m_nType = 0;
	m_nSType = 0;
	m_nAPID = 0;
	m_nPI1Off = 0;
	m_nPI1Wid = 0;
	m_nPI2Off = 0;
	m_nPI2Wid = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetName() CONST
{
	CDatabaseTMPacketIdentificationCriterion  cDatabaseTMPacketIdentificationCriterion;

	cDatabaseTMPacketIdentificationCriterion.SetType(GetType());
	cDatabaseTMPacketIdentificationCriterion.SetSubType(GetSubType());
	cDatabaseTMPacketIdentificationCriterion.SetAPID(GetAPID());
	return((m_szName.IsEmpty()) ? cDatabaseTMPacketIdentificationCriterion.GetName() : m_szName);
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetType(INT nType)
{
	m_nType = nType;
}

INT CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetType() CONST
{
	return m_nType;
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetSubType(INT nSubType)
{
	m_nSType = nSubType;
}

INT CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetSubType() CONST
{
	return m_nSType;
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetAPID(INT nAPID)
{
	m_nAPID = nAPID;
}

INT CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetAPID() CONST
{
	return m_nAPID;
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetFirstIDOffset(INT nOffset)
{
	m_nPI1Off = nOffset;
}

INT CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetFirstIDOffset() CONST
{
	return m_nPI1Off;
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetFirstIDWidth(INT nWidth)
{
	m_nPI1Wid = nWidth;
}

INT CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetFirstIDWidth() CONST
{
	return m_nPI1Wid;
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetSecondIDOffset(INT nOffset)
{
	m_nPI2Off = nOffset;
}

INT CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetSecondIDOffset() CONST
{
	return m_nPI2Off;
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::SetSecondIDWidth(INT nWidth)
{
	m_nPI2Wid = nWidth;
}

INT CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::GetSecondIDWidth() CONST
{
	return m_nPI2Wid;
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetName(), pszError);
}
VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION, pszError);
}

VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetName(), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION, pszWarning);
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::Translate(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion)
{
	SetName(pDatabaseTMPacketIdentificationCriterion->GetName());
	SetType(pDatabaseTMPacketIdentificationCriterion->GetType());
	SetSubType(pDatabaseTMPacketIdentificationCriterion->GetSubType());
	SetAPID(pDatabaseTMPacketIdentificationCriterion->GetAPID());
	SetFirstIDOffset(pDatabaseTMPacketIdentificationCriterion->GetFirstIDValueOffset());
	SetFirstIDWidth(pDatabaseTMPacketIdentificationCriterion->GetFirstIDValueWidth());
	SetSecondIDOffset(pDatabaseTMPacketIdentificationCriterion->GetSecondIDValueOffset());
	SetSecondIDWidth(pDatabaseTMPacketIdentificationCriterion->GetSecondIDValueWidth());
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckType();
		CheckSubType();
		CheckAPID();
		CheckFirstIDOffset();
		CheckFirstIDWidth();
		CheckSecondIDOffset();
		CheckSecondIDWidth();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckType(IsCollectingIssues());
		bCheck &= CheckSubType(IsCollectingIssues());
		bCheck &= CheckFirstIDOffset(IsCollectingIssues());
		bCheck &= CheckFirstIDWidth(IsCollectingIssues());
		bCheck &= CheckSecondIDOffset(IsCollectingIssues());
		bCheck &= CheckSecondIDWidth(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketType(m_nType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATIONCRITERION_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CheckSubType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSubType(m_nSType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATIONCRITERION_ILLEGALSUBTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketAPID(m_nAPID) && m_nAPID >= 0)
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATIONCRITERION_ILLEGALAPID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CheckFirstIDOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketFirstFieldOffset(m_nPI1Off))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATIONCRITERION_ILLEGALFIRSTFIELDOFFSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CheckFirstIDWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketFirstFieldWidth(m_nPI1Wid))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATIONCRITERION_ILLEGALFIRSTFIELDWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CheckSecondIDOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSecondFieldOffset(m_nPI1Off))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATIONCRITERION_ILLEGALSECONDFIELDOFFSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::CheckSecondIDWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSecondFieldWidth(m_nPI1Wid))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETIDENTIFICATIONCRITERION_ILLEGALSECONDFIELDWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PIC_TYPE)), m_nType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PIC_STYPE)), m_nSType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PIC_PI1_OFF)), m_nPI1Off);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PIC_PI1_WID)), m_nPI1Wid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PIC_PI2_OFF)), m_nPI2Off);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PIC_PI2_WID)), m_nPI2Wid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PIC_APID)), m_nAPID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketsRecordset::CSCOS2000DatabaseTMPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketsRecordset)
	m_szName.Empty();
	m_nSPID = 0;
	m_nSize = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMPacketsRecordset::SetID(LPCTSTR pszID)
{
	m_nSPID = (UINT)_ttoi64(pszID);
}

CString CSCOS2000DatabaseTMPacketsRecordset::GetID() CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertUIntToString(m_nSPID);
}

VOID CSCOS2000DatabaseTMPacketsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMPacketsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMPacketsRecordset::SetSize(INT nSize)
{
	m_nSize = nSize;
}

INT CSCOS2000DatabaseTMPacketsRecordset::GetSize() CONST
{
	return m_nSize;
}

VOID CSCOS2000DatabaseTMPacketsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetID(), pszError);
}
VOID CSCOS2000DatabaseTMPacketsRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTMPacketsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetID(), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketsRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseTMPacketsRecordset::Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket)
{
	SetID(pDatabaseTMPacket->GetTag());
	SetName(pDatabaseTMPacket->GetDescription());
	SetSize(pDatabaseTMPacket->GetDataSize());
}

BOOL CSCOS2000DatabaseTMPacketsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID();
		CheckName();
		CheckSize();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketsRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketID(m_nSPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALID), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDescription((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALNAME), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketsRecordset::CheckSize(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketDataSize(m_nSize, (m_nSize > 0) ? TMPACKET_LENGTH_FIXED : TMPACKET_LENGTH_VARIABLE))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKET_ILLEGALSIZE), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMPacketsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TPCF_SPID)), m_nSPID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TPCF_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TPCF_SIZE)), m_nSize);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketHeadersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketHeadersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketHeadersRecordset::CSCOS2000DatabaseTMPacketHeadersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketParametersRecordset)
	m_szName.Empty();
	m_nType = 0;
	m_nSType = 0;
	m_nAPID = 0;
	m_nTypeOff = 0;
	m_nTypeWid = 0;
	m_nSTypeOff = 0;
	m_nSTypeWid = 0;
	m_nTimeOff = 0;
	m_nTimeWid = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMPacketHeadersRecordset::GetName() CONST
{
	CDatabaseTMPacketHeader  cDatabaseTMPacketHeader;

	cDatabaseTMPacketHeader.SetType(GetType());
	cDatabaseTMPacketHeader.SetSubType(GetSubType());
	cDatabaseTMPacketHeader.SetAPID(GetAPID());
	return((m_szName.IsEmpty()) ? cDatabaseTMPacketHeader.GetName() : m_szName);
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetType(INT nType)
{
	m_nType = nType;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetType() CONST
{
	return m_nType;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetSubType(INT nSubType)
{
	m_nSType = nSubType;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetSubType() CONST
{
	return m_nSType;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetAPID(INT nAPID)
{
	m_nAPID = nAPID;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetAPID() CONST
{
	return m_nAPID;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetTypeOffset(INT nOffset)
{
	m_nTypeOff = nOffset;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetTypeOffset() CONST
{
	return m_nTypeOff;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetTypeWidth(INT nWidth)
{
	m_nTypeWid = nWidth;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetTypeWidth() CONST
{
	return m_nTypeWid;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetSubTypeOffset(INT nOffset)
{
	m_nSTypeOff = nOffset;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetSubTypeOffset() CONST
{
	return m_nSTypeOff;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetSubTypeWidth(INT nWidth)
{
	m_nSTypeWid = nWidth;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetSubTypeWidth() CONST
{
	return m_nSTypeWid;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetTimeOffset(INT nOffset)
{
	m_nTimeOff = nOffset;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetTimeOffset() CONST
{
	return m_nTimeOff;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::SetTimeWidth(INT nWidth)
{
	m_nTimeWid = nWidth;
}

INT CSCOS2000DatabaseTMPacketHeadersRecordset::GetTimeWidth() CONST
{
	return m_nTimeWid;
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetName(), pszError);
}
VOID CSCOS2000DatabaseTMPacketHeadersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER, pszError);
}

VOID CSCOS2000DatabaseTMPacketHeadersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetName(), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketHeadersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER, pszWarning);
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::Translate(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader)
{
	INT  nTypePos[3];
	INT  nSubTypePos[3];
	INT  nTimePos[3];

	SetName(pDatabaseTMPacketHeader->GetName());
	SetType(pDatabaseTMPacketHeader->GetType());
	SetSubType(pDatabaseTMPacketHeader->GetSubType());
	SetAPID(pDatabaseTMPacketHeader->GetAPID());
	SetTypeOffset((pDatabaseTMPacketHeader->GetTMTypePosition(nTypePos[0], nTypePos[1], nTypePos[2]) || (nTypePos[0] >= 0 && nTypePos[1] >= 0)) ? (8 * nTypePos[0] + nTypePos[1]) : -1);
	SetSubTypeOffset((pDatabaseTMPacketHeader->GetTMIDPosition(nSubTypePos[0], nSubTypePos[1], nSubTypePos[2]) || (nSubTypePos[0] >= 0 && nSubTypePos[1] >= 0)) ? (8 * nSubTypePos[0] + nSubTypePos[1]) : -1);
	SetTimeOffset((pDatabaseTMPacketHeader->GetTimestampPosition(nTimePos[0], nTimePos[1], nTimePos[2]) || (nTimePos[0] >= 0 && nTimePos[1] >= 0)) ? (8 * nTimePos[0] + nTimePos[1]) : -1);
	SetTypeWidth(nTypePos[2]);
	SetSubTypeWidth(nSubTypePos[2]);
	SetTimeWidth(nTimePos[2]);
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckType();
		CheckSubType();
		CheckAPID();
		CheckTypeOffset();
		CheckTypeWidth();
		CheckSubTypeOffset();
		CheckSubTypeWidth();
		CheckTimeOffset();
		CheckTimeWidth();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckType(IsCollectingIssues());
		bCheck &= CheckSubType(IsCollectingIssues());
		bCheck &= CheckTypeOffset(IsCollectingIssues());
		bCheck &= CheckTypeWidth(IsCollectingIssues());
		bCheck &= CheckSubTypeOffset(IsCollectingIssues());
		bCheck &= CheckSubTypeWidth(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketType(m_nType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckSubType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSubType(m_nSType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALSUBTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketAPID(m_nAPID) && m_nAPID >= 0)
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALAPID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckTypeOffset(BOOL bStatus)
{
	INT  nTypePos[2][2];
	CString  szMessage;

	for (GetDatabaseEngine()->GetTMPacketHeaderTMTypePositionRange(nTypePos[0][0], nTypePos[0][1], nTypePos[1][0], nTypePos[1][1]); !GetDatabaseEngine()->CheckTMPacketHeaderTMTypePosition((m_nTypeOff >= 0) ? (m_nTypeOff / 8) : -1, (m_nTypeOff >= 0) ? (m_nTypeOff % 8) : -1, nTypePos[1][0]); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTYPEFIELDOFFSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckTypeWidth(BOOL bStatus)
{
	INT  nTypePos[2][2];
	CString  szMessage;

	for (GetDatabaseEngine()->GetTMPacketHeaderTMTypePositionRange(nTypePos[0][0], nTypePos[0][1], nTypePos[1][0], nTypePos[1][1]); !GetDatabaseEngine()->CheckTMPacketHeaderTMTypePosition((m_nTypeWid > 0) ? (max(nTypePos[0][0], 0) / 8) : -1, (m_nTypeWid > 0) ? (max(nTypePos[0][0], 0) % 8) : -1, m_nTypeWid); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTYPEFIELDWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckSubTypeOffset(BOOL bStatus)
{
	INT  nSubTypePos[2][2];
	CString  szMessage;

	for (GetDatabaseEngine()->GetTMPacketHeaderTMIDPositionRange(nSubTypePos[0][0], nSubTypePos[0][1], nSubTypePos[1][0], nSubTypePos[1][1]); !GetDatabaseEngine()->CheckTMPacketHeaderTMIDPosition((m_nSTypeOff >= 0) ? (m_nSTypeOff / 8) : -1, (m_nSTypeOff >= 0) ? (m_nSTypeOff % 8) : -1, nSubTypePos[1][0]); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALSUBTYPEFIELDOFFSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckSubTypeWidth(BOOL bStatus)
{
	INT  nSubTypePos[2][2];
	CString  szMessage;

	for (GetDatabaseEngine()->GetTMPacketHeaderTMIDPositionRange(nSubTypePos[0][0], nSubTypePos[0][1], nSubTypePos[1][0], nSubTypePos[1][1]); !GetDatabaseEngine()->CheckTMPacketHeaderTMIDPosition((m_nSTypeWid > 0) ? (max(nSubTypePos[0][0], 0) / 8) : -1, (m_nSTypeWid > 0) ? (max(nSubTypePos[0][0], 0) % 8) : -1, m_nSTypeWid); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALSUBTYPEFIELDWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckTimeOffset(BOOL bStatus)
{
	INT  nTimePos[2][2];
	CString  szMessage;

	for (GetDatabaseEngine()->GetTMPacketHeaderTimestampPositionRange(nTimePos[0][0], nTimePos[0][1], nTimePos[1][0], nTimePos[1][1]); !GetDatabaseEngine()->CheckTMPacketHeaderTimestampPosition((m_nTimeOff >= 0) ? (m_nTimeOff / 8) : -1, (m_nTimeOff >= 0) ? (m_nTimeOff % 8) : -1, nTimePos[1][0]); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTIMEFIELDOFFSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketHeadersRecordset::CheckTimeWidth(BOOL bStatus)
{
	INT  nTimePos[2][2];
	CString  szMessage;

	for (GetDatabaseEngine()->GetTMPacketHeaderTimestampPositionRange(nTimePos[0][0], nTimePos[0][1], nTimePos[1][0], nTimePos[1][1]); !GetDatabaseEngine()->CheckTMPacketHeaderTimestampPosition((m_nTimeWid > 0) ? (max(nTimePos[0][0], 0) / 8) : -1, (m_nTimeWid > 0) ? (max(nTimePos[0][0], 0) % 8) : -1, m_nTimeWid); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETHEADER_ILLEGALTIMEFIELDWIDTH), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketHeadersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMPacketHeadersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_TYPE)), m_nType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_STYPE)), m_nSType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_TYPE_OFF)), m_nTypeOff);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_TYPE_WID)), m_nTypeWid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_STYPE_OFF)), m_nSTypeOff);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_STYPE_WID)), m_nSTypeWid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_TIME_OFF)), m_nTimeOff);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_TIME_WID)), m_nTimeWid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PDH_APID)), m_nAPID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketParametersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketParametersRecordset::CSCOS2000DatabaseTMPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketParametersRecordset)
	m_szName.Empty();
	m_szDisDesc.Empty();
	m_szChoice.Empty();
	m_szPidRef.Empty();
	m_szJustify.Empty();
	m_szForm.Empty();
	m_nSPID = 0;
	m_nTPSD = 0;
	m_nPos = 0;
	m_nGrpSize = 0;
	m_nFixRep = 0;
	m_nOffBy = 0;
	m_nOffBi = 0;
	m_nWidth = 0;
	m_nOffset = 0;
	m_nNbOcc = 0;
	m_nLgOcc = 0;
	m_nTime = 0;
	m_nTdOcc = 0;
	m_nDChar = 0;
	m_bFixed = TRUE;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::Open(UINT nOpenType, LPCTSTR lpszSQL, DWORD dwOptions, BOOL bFixed)
{
	m_nFields = ((m_bFixed = bFixed)) ? 8 : 14;
	return CSCOS2000DatabaseRecordset::Open(nOpenType, lpszSQL, dwOptions);
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szName = pszTag;
}

CString CSCOS2000DatabaseTMPacketParametersRecordset::GetTag() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetPacketID(LPCTSTR pszID)
{
	m_nSPID = (UINT)_ttoi64(pszID);
}

CString CSCOS2000DatabaseTMPacketParametersRecordset::GetPacketID() CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertUIntToString(m_nSPID);
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDisDesc = pszDescription;
}

CString CSCOS2000DatabaseTMPacketParametersRecordset::GetDescription() CONST
{
	return m_szDisDesc;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetAttributes(UINT nAttributes)
{
	m_szChoice = GetDatabaseEngine()->TranslateTMPacketParameterChoiceFlag(nAttributes);
	m_szPidRef = GetDatabaseEngine()->TranslateTMPacketParameterOnBoardIDFlag(nAttributes);
	m_szJustify = GetDatabaseEngine()->TranslateTMPacketParameterDisplayAlignmentFlag(nAttributes);
	m_szNewLine = GetDatabaseEngine()->TranslateTMPacketParameterDisplayNewLineFlag(nAttributes);
	m_szForm = GetDatabaseEngine()->TranslateTMPacketParameterDisplayFormatFlag(nAttributes);
	m_nDChar = _ttoi(GetDatabaseEngine()->TranslateTMPacketParameterDisplayColumnsFlag(nAttributes));
}

UINT CSCOS2000DatabaseTMPacketParametersRecordset::GetAttributes() CONST
{
	CStringTools  cStringTools;

	return GetDatabaseEngine()->TranslateTMPacketParameterChoiceFlag(m_szChoice) | GetDatabaseEngine()->TranslateTMPacketParameterOnBoardIDFlag(m_szPidRef) | GetDatabaseEngine()->TranslateTMPacketParameterDisplayAlignmentFlag(m_szJustify) | GetDatabaseEngine()->TranslateTMPacketParameterDisplayNewLineFlag(m_szNewLine) | GetDatabaseEngine()->TranslateTMPacketParameterDisplayFormatFlag(m_szForm) | GetDatabaseEngine()->TranslateTMPacketParameterDisplayColumnsFlag(cStringTools.ConvertIntToString(m_nDChar));
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetContentID(INT nContentID)
{
	m_nTPSD = nContentID;
	m_bFixed = (nContentID == (UINT)-1) ? TRUE : FALSE;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetContentID() CONST
{
	return m_nTPSD;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetBytePos(INT nByte)
{
	m_nOffBy = nByte;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetBytePos() CONST
{
	return m_nOffBy;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetBitPos(INT nBit)
{
	m_nOffBi = nBit;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetBitPos() CONST
{
	return m_nOffBi;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetWidth(INT nWidth)
{
	m_nWidth = nWidth;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetWidth() CONST
{
	return m_nWidth;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetOffset(INT nOffset)
{
	m_nOffset = nOffset;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetOffset() CONST
{
	return m_nOffset;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetOccurrence(INT nOccurrence)
{
	m_nPos = nOccurrence;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetOccurrence() CONST
{
	return m_nPos;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetOccurrenceCount(INT nCount)
{
	m_nNbOcc = nCount;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetOccurrenceCount() CONST
{
	return m_nNbOcc;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetOccurrenceInterval(INT nInterval)
{
	m_nLgOcc = nInterval;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetOccurrenceInterval() CONST
{
	return m_nLgOcc;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetOccurrenceTimeOffset(INT nOffset)
{
	m_nTime = nOffset;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetOccurrenceTimeOffset() CONST
{
	return m_nTime;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetOccurrenceTimeInterval(INT nInterval)
{
	m_nTdOcc = nInterval;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetOccurrenceTimeInterval() CONST
{
	return m_nTdOcc;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetGroupSize(INT nSize)
{
	m_nGrpSize = nSize;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetGroupSize() CONST
{
	return m_nGrpSize;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::SetGroupRepetitionCount(INT nCount)
{
	m_nFixRep = nCount;
}

INT CSCOS2000DatabaseTMPacketParametersRecordset::GetGroupRepetitionCount() CONST
{
	return m_nFixRep;
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetPacketID(), pszError);
}
VOID CSCOS2000DatabaseTMPacketParametersRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTMPacketParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetPacketID(), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketParametersRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszTag, pszTag, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::Translate(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter)
{
	SetTag(pDatabaseTMPacketParameter->GetTag());
	SetContentID(pDatabaseTMPacketIdentification->GetContentID());
	SetDescription(pDatabaseTMPacketParameter->GetDescription());
	SetAttributes(pDatabaseTMPacketParameter->GetAttributes());
	SetGroupSize(pDatabaseTMPacketParameter->GetGroupSize());
	SetGroupRepetitionCount(pDatabaseTMPacketParameter->GetGroupRepetitionCount());
	SetOccurrence(pDatabaseTMPacketParameter->GetOccurrence());
	SetWidth(pDatabaseTMPacketParameter->GetWidth());
	SetOffset(pDatabaseTMPacketParameter->GetOffset());
	return((!pDatabaseTMPacketParameter->GetTag().IsEmpty()) ? TRUE : FALSE);
}
BOOL CSCOS2000DatabaseTMPacketParametersRecordset::Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter)
{
	SetContentID(-1);
	SetTag(pDatabaseTMPacketParameter->GetTag());
	SetPacketID(pDatabaseTMPacket->GetTag());
	SetBytePos(pDatabaseTMPacketParameter->GetBytePos());
	SetBitPos(pDatabaseTMPacketParameter->GetBitPos());
	SetOccurrenceCount(pDatabaseTMPacketParameter->GetOccurrenceCount());
	SetOccurrenceInterval(pDatabaseTMPacketParameter->GetOccurrenceInterval());
	SetOccurrenceTimeOffset(pDatabaseTMPacketParameter->GetOccurrenceTimeOffset());
	SetOccurrenceTimeInterval(pDatabaseTMPacketParameter->GetOccurrenceTimeInterval());
	return((!pDatabaseTMPacketParameter->GetTag().IsEmpty()) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		for (CheckTag(); m_bFixed; )
		{
			CheckPacketID();
			CheckBytePos();
			CheckBitPos();
			CheckOccurrenceCount();
			CheckOccurrenceInterval();
			CheckOccurrenceTimeOffset();
			CheckOccurrenceTimeInterval();
			return TRUE;
		}
		CheckDescription();
		CheckAttributes();
		CheckGroupSize();
		CheckGroupRepetitionCount();
		CheckWidth();
		CheckOffset();
		CheckOccurrence();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		for (bCheck = CheckTag(IsCollectingIssues()); m_bFixed; )
		{
			bCheck &= CheckPacketID(IsCollectingIssues());
			bCheck &= CheckBytePos(IsCollectingIssues());
			bCheck &= CheckBitPos(IsCollectingIssues());
			bCheck &= CheckOccurrenceCount(IsCollectingIssues());
			bCheck &= CheckOccurrenceTimeOffset(IsCollectingIssues());
			return bCheck;
		}
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckGroupSize(IsCollectingIssues());
		bCheck &= CheckGroupRepetitionCount(IsCollectingIssues());
		bCheck &= CheckWidth(IsCollectingIssues());
		bCheck &= CheckOffset(IsCollectingIssues());
		bCheck &= CheckOccurrence(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterTag((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALTAG), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckPacketID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketID(m_nSPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALID), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterDescription((m_szDisDesc = ExtractText(m_szDisDesc))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALDESCRIPTION), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterChoiceFlag(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALCHOICEFLAG), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMPacketParameterOnBoardIDFlag(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALONBOARDPARAMETERID), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMPacketParameterDisplayAlignmentFlag(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALALIGNMENT), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMPacketParameterDisplayNewLineFlag(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALNEWLINEFLAG), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMPacketParameterDisplayColumnsFlag(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALCOLUMNSFLAG), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMPacketParameterDisplayFormatFlag(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALFORMAT), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckContentID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketContentID(m_nTPSD))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALCONTENTID), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckBytePos(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterBytePosition(GetBytePos()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALBYTEOFFSET), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckBitPos(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterBitPosition(GetBitPos()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALBITOFFSET), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckWidth(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterWidth(GetWidth()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALWIDTH), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOffset(GetOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALOFFSET), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckOccurrence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOccurrence(GetOccurrence()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALPOSITION), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckOccurrenceCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOccurrenceCount(GetOccurrenceCount()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALOCCURRENCECOUNT), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckOccurrenceInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOccurrenceInterval(GetOccurrenceCount(), GetOccurrenceInterval()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALOCCURRENCEINTERVAL), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckOccurrenceTimeOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOccurrenceTimeOffset(GetOccurrenceTimeOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALOCCURRENCETIMEOFFSET), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckOccurrenceTimeInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterOccurrenceTimeOffset(GetOccurrenceTimeInterval()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETPARAMETER_ILLEGALOCCURRENCETIMEINTERVAL), (LPCTSTR)GetPacketID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckGroupSize(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterGroupSize(GetGroupSize()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALGROUPSIZE), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketParametersRecordset::CheckGroupRepetitionCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketParameterGroupRepetitionCount(GetGroupRepetitionCount()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETDEFINITION_ILLEGALGROUPREPETITIONCOUNT), GetContentID(), GetOccurrence()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMPacketParametersRecordset)
	for (pFX->SetFieldType(CFieldExchange::outputColumn); m_bFixed; )
	{
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_NAME)), m_szName);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_SPID)), m_nSPID);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_OFFBY)), m_nOffBy);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_OFFBI)), m_nOffBi);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_NBOCC)), m_nNbOcc);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_LGOCC)), m_nLgOcc);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_TIME)), m_nTime);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PLF_TDOCC)), m_nTdOcc);
		break;
	}
	if (!m_bFixed)
	{
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_TPSD)), m_nTPSD);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_POS)), m_nPos);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_NAME)), m_szName);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_GRPSIZE)), m_nGrpSize);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_FIXREP)), m_nFixRep);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_CHOICE)), m_szChoice);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_PIDREF)), m_szPidRef);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_DISDESC)), m_szDisDesc);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_WIDTH)), m_nWidth);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_JUSTIFY)), m_szJustify);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_NEWLINE)), m_szNewLine);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_DCHAR)), m_nDChar);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_FORM)), m_szForm);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_VPD_OFFSET)), m_nOffset);
	}
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketStreamsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketStreamsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketStreamsRecordset::CSCOS2000DatabaseTMPacketStreamsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketStreamsRecordset)
	m_szRlChk.Empty();
	m_nType = 0;
	m_nSType = 0;
	m_nAPID = 0;
	m_nTimeout = 0;
	m_nValue = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMPacketStreamsRecordset::GetName() CONST
{
	CDatabaseTMPacketStream  cDatabaseTMPacketStream;

	cDatabaseTMPacketStream.SetType(GetType());
	cDatabaseTMPacketStream.SetSubType(GetSubType());
	cDatabaseTMPacketStream.SetAPID(GetAPID());
	return((m_szName.IsEmpty()) ? cDatabaseTMPacketStream.GetName() : m_szName);
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::SetType(INT nType)
{
	m_nType = nType;
}

INT CSCOS2000DatabaseTMPacketStreamsRecordset::GetType() CONST
{
	return m_nType;
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::SetSubType(INT nSubType)
{
	m_nSType = nSubType;
}

INT CSCOS2000DatabaseTMPacketStreamsRecordset::GetSubType() CONST
{
	return m_nSType;
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::SetAPID(INT nAPID)
{
	m_nAPID = nAPID;
}

INT CSCOS2000DatabaseTMPacketStreamsRecordset::GetAPID() CONST
{
	return m_nAPID;
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::SetTimeout(INT nTimeout)
{
	m_nTimeout = nTimeout;
}

INT CSCOS2000DatabaseTMPacketStreamsRecordset::GetTimeout() CONST
{
	return m_nTimeout;
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::SetValidityParameter(LPCTSTR pszTag)
{
	m_szRlChk = pszTag;
}

CString CSCOS2000DatabaseTMPacketStreamsRecordset::GetValidityParameter() CONST
{
	return m_szRlChk;
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::SetValidityValue(INT nValue)
{
	m_nValue = nValue;
}

INT CSCOS2000DatabaseTMPacketStreamsRecordset::GetValidityValue() CONST
{
	return m_nValue;
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetName(), pszError);
}
VOID CSCOS2000DatabaseTMPacketStreamsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM, pszError);
}

VOID CSCOS2000DatabaseTMPacketStreamsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetName(), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketStreamsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM, pszWarning);
}

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::Translate(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream)
{
	SetName(pDatabaseTMPacketStream->GetName());
	SetType(pDatabaseTMPacketStream->GetType());
	SetSubType(pDatabaseTMPacketStream->GetSubType());
	SetAPID(pDatabaseTMPacketStream->GetAPID());
	SetTimeout(pDatabaseTMPacketStream->GetTimeout());
	SetValidityParameter(pDatabaseTMPacketStream->GetValidityParameter());
	SetValidityValue((INT)pDatabaseTMPacketStream->GetValidityValue());
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckType();
		CheckSubType();
		CheckAPID();
		CheckTimeout();
		CheckValidityParameter();
		CheckValidityValue();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckType(IsCollectingIssues());
		bCheck &= CheckSubType(IsCollectingIssues());
		bCheck &= CheckTimeout(IsCollectingIssues());
		bCheck &= CheckValidityValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketType(m_nType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::CheckSubType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketSubType(m_nSType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALSUBTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketAPID(m_nAPID) && m_nAPID >= 0)
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

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::CheckTimeout(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamTimeout(m_nTimeout))
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

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamValidityParameter((m_szRlChk = ExtractText(m_szRlChk))))
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

BOOL CSCOS2000DatabaseTMPacketStreamsRecordset::CheckValidityValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketStreamValidityValue(m_nValue) && !GetValidityParameter().IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETSTREAM_ILLEGALVALIDITYVALUE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketStreamsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMStreamsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSTR_TYPE)), m_nType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSTR_STYPE)), m_nSType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSTR_TIMEOUT)), m_nTimeout);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSTR_RLCHK)), m_szRlChk);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSTR_VALPAR)), m_nValue);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSTR_APID)), m_nAPID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketGroupsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketGroupsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketGroupsRecordset::CSCOS2000DatabaseTMPacketGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketGroupsRecordset)
	m_szName.Empty();
	m_szDescr.Empty();
	m_szGType.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMPacketGroupsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMPacketGroupsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMPacketGroupsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMPacketGroupsRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMPacketGroupsRecordset::SetType(INT nType)
{
	m_szGType = GetDatabaseEngine()->TranslateTMPacketGroupType(nType);
}

INT CSCOS2000DatabaseTMPacketGroupsRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateTMPacketGroupType(m_szGType);
}

VOID CSCOS2000DatabaseTMPacketGroupsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTMPacketGroupsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP, pszError);
}

VOID CSCOS2000DatabaseTMPacketGroupsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketGroupsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP, pszWarning);
}

VOID CSCOS2000DatabaseTMPacketGroupsRecordset::Translate(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup)
{
	SetName(pDatabaseTMPacketGroup->GetName());
	SetDescription(pDatabaseTMPacketGroup->GetDescription());
	SetType();
}

BOOL CSCOS2000DatabaseTMPacketGroupsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketGroupsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckType();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketGroupsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketGroupName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETGROUP_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketGroupsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketGroupDescription((m_szDescr = ExtractText(m_szDescr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETGROUP_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketGroupsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketGroupType((m_szGType = ExtractText(m_szGType))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETGROUP_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketGroupsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMPacketGroupsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRP_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRP_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRP_GTYPE)), m_szGType);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketGroupMembersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMPacketGroupMembersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMPacketGroupMembersRecordset::CSCOS2000DatabaseTMPacketGroupMembersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMPacketGroupMembersRecordset)
	m_szGName.Empty();
	m_nPKSPID = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMPacketGroupMembersRecordset::SetGroup(LPCTSTR pszName)
{
	m_szGName = pszName;
}

CString CSCOS2000DatabaseTMPacketGroupMembersRecordset::GetGroup() CONST
{
	return m_szGName;
}

VOID CSCOS2000DatabaseTMPacketGroupMembersRecordset::SetPacket(LPCTSTR pszPacket)
{
	m_nPKSPID = _ttoi(pszPacket);
}

CString CSCOS2000DatabaseTMPacketGroupMembersRecordset::GetPacket() CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertUIntToString(m_nPKSPID);
}

VOID CSCOS2000DatabaseTMPacketGroupMembersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szGName), pszError);
}
VOID CSCOS2000DatabaseTMPacketGroupMembersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP, pszError);
}

VOID CSCOS2000DatabaseTMPacketGroupMembersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szGName), pszWarning);
}
VOID CSCOS2000DatabaseTMPacketGroupMembersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP, pszWarning);
}

VOID CSCOS2000DatabaseTMPacketGroupMembersRecordset::Translate(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, LPCTSTR pszPacket)
{
	SetGroup(pDatabaseTMPacketGroup->GetName());
	SetPacket(pszPacket);
}

BOOL CSCOS2000DatabaseTMPacketGroupMembersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMPacketGroupMembersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckGroup();
		CheckPacketID();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckGroup(IsCollectingIssues());
		bCheck &= CheckPacketID(IsCollectingIssues());
		return bCheck;
	}
	return FALSE;
}

BOOL CSCOS2000DatabaseTMPacketGroupMembersRecordset::CheckGroup(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketGroupName((m_szGName = ExtractText(m_szGName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETGROUPMEMBER_ILLEGALNAME), (LPCTSTR)GetGroup()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMPacketGroupMembersRecordset::CheckPacketID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMPacketGroupMember(m_nPKSPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPACKETGROUPMEMBER_ILLEGALPACKETID), (LPCTSTR)GetGroup(), (LPCTSTR)GetPacket()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMPacketGroupMembersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMPacketGroupMembersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRPK_GNAME)), m_szGName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRPK_PKSPID)), m_nPKSPID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCFunctionsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCFunctionsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCFunctionsRecordset::CSCOS2000DatabaseTCFunctionsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCFunctionsRecordset)
	m_szCName.Empty();
	m_szDescr.Empty();
	m_szDescr2.Empty();
	m_szCType.Empty();
	m_szCritical.Empty();
	m_szPktID.Empty();
	m_szPlan.Empty();
	m_szExec.Empty();
	m_szILScope.Empty();
	m_szILStage.Empty();
	m_szHiPri.Empty();
	m_szSubSys.Empty();
	m_szDefSet.Empty();
	m_szCorr.Empty();
	m_szDarc.Empty();
	m_szEndian.Empty();
	m_nType = 0;
	m_nSType = 0;
	m_nAPID = 0;
	m_nNPars = 0;
	m_nSubSys = 0;
	m_nMapID = 0;
	m_nRAPID = 0;
	m_nAck = 0;
	m_nSubSchedID = 0;
	m_nFields = 21;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetName(LPCTSTR pszName)
{
	m_szCName = pszName;
}

CString CSCOS2000DatabaseTCFunctionsRecordset::GetName() CONST
{
	return m_szCName;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCFunctionsRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetDetails(LPCTSTR pszDetails)
{
	m_szDescr2 = pszDetails;
}

CString CSCOS2000DatabaseTCFunctionsRecordset::GetDetails() CONST
{
	return m_szDescr2;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szCType = GetDatabaseEngine()->TranslateTCFunctionType(nAttributes);
	m_szCritical = GetDatabaseEngine()->TranslateTCFunctionHazardousFlag(nAttributes);
	m_szPlan = GetDatabaseEngine()->TranslateTCFunctionPlanningFlag(nAttributes);
	m_szExec = GetDatabaseEngine()->TranslateTCFunctionExecutionFlag(nAttributes);
	m_szHiPri = GetDatabaseEngine()->TranslateTCFunctionPriorityFlag(nAttributes);
	m_szILScope = GetDatabaseEngine()->TranslateTCFunctionInterlockScope(nAttributes);
	m_szILStage = GetDatabaseEngine()->TranslateTCFunctionInterlockStage(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCFunctionsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionType(m_szCType) | GetDatabaseEngine()->TranslateTCFunctionHazardousFlag(m_szCritical) | GetDatabaseEngine()->TranslateTCFunctionPlanningFlag(m_szPlan) | GetDatabaseEngine()->TranslateTCFunctionExecutionFlag(m_szExec) | GetDatabaseEngine()->TranslateTCFunctionPriorityFlag(m_szHiPri) | GetDatabaseEngine()->TranslateTCFunctionInterlockScope(m_szILScope) | GetDatabaseEngine()->TranslateTCFunctionInterlockStage(m_szILStage);
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetAPID(INT nAPID, BOOL bRedundant)
{
	m_nAPID = (!bRedundant) ? nAPID : m_nAPID;
	m_nRAPID = (bRedundant) ? nAPID : m_nRAPID;
}

INT CSCOS2000DatabaseTCFunctionsRecordset::GetAPID(BOOL bRedundant) CONST
{
	return((!bRedundant) ? m_nAPID : m_nRAPID);
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetServiceType(INT nType)
{
	m_nType = nType;
}

INT CSCOS2000DatabaseTCFunctionsRecordset::GetServiceType() CONST
{
	return m_nType;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetServiceSubType(INT nSubType)
{
	m_nSType = nSubType;
}

INT CSCOS2000DatabaseTCFunctionsRecordset::GetServiceSubType() CONST
{
	return m_nSType;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetMapID(INT nMapID)
{
	m_nMapID = nMapID;
}

INT CSCOS2000DatabaseTCFunctionsRecordset::GetMapID() CONST
{
	return m_nMapID;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetTCPacket(LPCTSTR pszTag)
{
	m_szPktID = pszTag;
}

CString CSCOS2000DatabaseTCFunctionsRecordset::GetTCPacket() CONST
{
	return m_szPktID;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetSubSystem(LPCTSTR pszSubSystem)
{
	m_nSubSys = _ttoi(pszSubSystem);
}

CString CSCOS2000DatabaseTCFunctionsRecordset::GetSubSystem() CONST
{
	CStringTools  cStringTools;

	return((m_nSubSys > 0) ? cStringTools.ConvertIntToString(m_nSubSys) : EMPTYSTRING);
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetSubSchedule(LPCTSTR pszSubSchedule)
{
	m_nSubSchedID = _ttoi(pszSubSchedule);
}

CString CSCOS2000DatabaseTCFunctionsRecordset::GetSubSchedule() CONST
{
	CStringTools  cStringTools;

	return((m_nSubSchedID > 0) ? cStringTools.ConvertIntToString(m_nSubSchedID) : EMPTYSTRING);
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetParameterSet(LPCTSTR pszSet)
{
	m_szDefSet = pszSet;
}

CString CSCOS2000DatabaseTCFunctionsRecordset::GetParameterSet() CONST
{
	return m_szDefSet;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetAcknowledgmentFlags(INT nFlags)
{
	m_nAck = nFlags;
}

INT CSCOS2000DatabaseTCFunctionsRecordset::GetAcknowledgmentFlags() CONST
{
	return m_nAck;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::SetElementsCount(INT nCount)
{
	m_nNPars = nCount;
}

INT CSCOS2000DatabaseTCFunctionsRecordset::GetElementsCount() CONST
{
	return m_nNPars;
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szCName), pszError);
}
VOID CSCOS2000DatabaseTCFunctionsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szCName), pszWarning);
}
VOID CSCOS2000DatabaseTCFunctionsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseTCFunctionsRecordset::Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction)
{
	CStringArray  szSets;

	SetName(pDatabaseTCFunction->GetName());
	SetDescription(pDatabaseTCFunction->GetDescription());
	SetDetails(pDatabaseTCFunction->GetDetails());
	SetAttributes(pDatabaseTCFunction->GetAttributes());
	SetAPID(pDatabaseTCFunction->GetAPID(), FALSE);
	SetAPID(pDatabaseTCFunction->GetAPID(), TRUE);
	SetServiceType(pDatabaseTCFunction->GetTCType());
	SetServiceSubType(pDatabaseTCFunction->GetTCID());
	SetMapID(pDatabaseTCFunction->GetMapID());
	SetTCPacket(pDatabaseTCFunction->GetTCPacket());
	SetSubSystem(pDatabaseTCFunction->GetDestinationSubSystem());
	SetSubSchedule(pDatabaseTCFunction->GetDestinationSubSchedule());
	SetParameterSet((pDatabaseTCFunction->GetParameterSets(szSets) > 0) ? szSets.GetAt(0) : EMPTYSTRING);
	SetAcknowledgmentFlags(pDatabaseTCFunction->GetAcknowledgementFlags());
	SetElementsCount((INT)pDatabaseTCFunction->GetSize());
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCFunctionsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckDetails();
		CheckAttributes();
		CheckAPID();
		CheckServiceType();
		CheckServiceSubType();
		CheckMapID();
		CheckTCPacket();
		CheckSubSystem();
		CheckSubSchedule();
		CheckParameterSet();
		CheckAcknowledgmentFlags();
		CheckElementsCount();
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

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionName((m_szCName = ExtractText(m_szCName))))
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

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckDetails(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDetails((m_szDescr2 = ExtractText(m_szDescr2))))
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

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckAttributes(BOOL bStatus)
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
	if (!GetDatabaseEngine()->CheckTCFunctionHazardousFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALHAZFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionPlanningFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALPLANFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionExecutionFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALEXECFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionPriorityFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALPRIFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionInterlockScope(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALINTERLOCKSCOPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionInterlockStage(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALINTERLOCKSTAGE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionAPID(m_nAPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALAPID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionAPID(m_nRAPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALREDUNDANTAPID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckServiceType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionTCType(m_nType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALSERVICETYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckServiceSubType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionTCID(m_nSType))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALSERVICESUBTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckMapID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionMapID(m_nMapID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALMAPID), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckTCPacket(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionPacketTag((m_szPktID = ExtractText(m_szPktID))))
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

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckSubSystem(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDestinationSubSystemID(m_nSubSys))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALSUBSYSTEM), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckSubSchedule(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDestinationSubScheduleID(m_nSubSchedID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALSUBSCHEDULE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckParameterSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionDefaultParameterSetName((m_szDefSet = ExtractText(m_szDefSet))) && !m_szDefSet.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALPARAMETERSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckAcknowledgmentFlags(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionAcknowledgementFlags(m_nAck))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALACKNOWLEDGEMENTFLAGS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionsRecordset::CheckElementsCount(BOOL bStatus)
{
	CString  szMessage;

	if (m_nNPars < 0)
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTION_ILLEGALELEMENTSCOUNT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCFunctionsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCFunctionsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_CNAME)), m_szCName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_DESCR2)), m_szDescr2);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_CTYPE)), m_szCType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_CRITICAL)), m_szCritical);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_PKTID)), m_szPktID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_TYPE)), m_nType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_STYPE)), m_nSType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_APID)), m_nAPID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_NPARS)), m_nNPars);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_PLAN)), m_szPlan);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_EXEC)), m_szExec);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_ILSCOPE)), m_szILScope);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_ILSTAGE)), m_szILStage);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_SUBSYS)), m_nSubSys);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_HIPRI)), m_szHiPri);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_MAPID)), m_nMapID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_DEFSET)), m_szDefSet);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_RAPID)), m_nRAPID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_ACK)), m_nAck);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCF_SUBSCHEDID)), m_nSubSchedID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCFunctionElementsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCFunctionElementsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCFunctionElementsRecordset::CSCOS2000DatabaseTCFunctionElementsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCFunctionElementsRecordset)
	m_szCName.Empty();
	m_szElType.Empty();
	m_szDescr.Empty();
	m_szPName.Empty();
	m_szInter.Empty();
	m_szValue.Empty();
	m_szTMID.Empty();
	m_nGrpSize = 0;
	m_nElLen = 0;
	m_nBit = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetName(LPCTSTR pszName)
{
	m_szPName = pszName;
}

CString CSCOS2000DatabaseTCFunctionElementsRecordset::GetName() CONST
{
	return m_szPName;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetFunction(LPCTSTR pszFunction)
{
	m_szCName = pszFunction;
}

CString CSCOS2000DatabaseTCFunctionElementsRecordset::GetFunction() CONST
{
	return m_szCName;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCFunctionElementsRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szElType = GetDatabaseEngine()->TranslateTCFunctionElementType(nAttributes);
	m_szInter = GetDatabaseEngine()->TranslateTCFunctionElementValueInterpretation(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCFunctionElementsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCFunctionElementType(m_szElType) | GetDatabaseEngine()->TranslateTCFunctionElementValueInterpretation(m_szInter);
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetGroupSize(INT nSize)
{
	m_nGrpSize = nSize;
}

INT CSCOS2000DatabaseTCFunctionElementsRecordset::GetGroupSize() CONST
{
	return m_nGrpSize;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetBitWidth(INT nWidth)
{
	m_nElLen = nWidth;
}

INT CSCOS2000DatabaseTCFunctionElementsRecordset::GetBitWidth() CONST
{
	return m_nElLen;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetBitOffset(INT nOffset)
{
	m_nBit = nOffset;
}

INT CSCOS2000DatabaseTCFunctionElementsRecordset::GetBitOffset() CONST
{
	return m_nBit;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szValue = pszConstValue;
}

CString CSCOS2000DatabaseTCFunctionElementsRecordset::GetConstValue() CONST
{
	return m_szValue;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::SetConstValueSource(LPCTSTR pszParameter)
{
	m_szTMID = pszParameter;
}

CString CSCOS2000DatabaseTCFunctionElementsRecordset::GetConstValueSource() CONST
{
	return m_szTMID;
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szCName), pszError);
}
VOID CSCOS2000DatabaseTCFunctionElementsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTCFunctionElementsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szCName), pszWarning);
}
VOID CSCOS2000DatabaseTCFunctionElementsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement)
{
	SetName(pDatabaseTCFunctionElement->GetName());
	SetFunction(pDatabaseTCFunction->GetName());
	SetDescription(pDatabaseTCFunctionElement->GetDescription());
	SetAttributes(pDatabaseTCFunctionElement->GetAttributes());
	SetGroupSize(pDatabaseTCFunctionElement->GetGroupSize());
	SetBitWidth(pDatabaseTCFunctionElement->GetWidth());
	SetBitOffset((pDatabaseTCFunctionElement->GetBytePos() >= 0 && pDatabaseTCFunctionElement->GetBitPos() >= 0) ? (8 * pDatabaseTCFunctionElement->GetBytePos() + pDatabaseTCFunctionElement->GetBitPos()) : -1);
	SetConstValue(pDatabaseTCFunctionElement->GetConstValueAsText());
	SetConstValueSource(pDatabaseTCFunctionElement->GetConstValueSource());
	return((pDatabaseTCFunctionElement->GetAttributes() & (TCFUNCTIONELEMENT_TYPE_PARAMETER | TCFUNCTIONELEMENT_TYPE_CONSTANT)) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckFunction();
		CheckDescription();
		CheckAttributes();
		CheckGroupSize();
		CheckBitOffset();
		CheckBitWidth();
		CheckConstValue();
		CheckConstValueSource();
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

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementName((m_szPName = ExtractText(m_szPName))))
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

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckFunction(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionName((m_szCName = ExtractText(m_szCName))))
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

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementType(m_szPName, GetDatabaseEngine()->TranslateTCFunctionElementType((m_szElType = ExtractText(m_szElType)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALTYPE), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCFunctionElementValueInterpretation(GetAttributes(), GetDatabaseEngine()->TranslateTCFunctionElementValueInterpretation((m_szInter = ExtractText(m_szInter)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALVALUEINTERPRETATION), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckGroupSize(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementGroupSize(GetGroupSize()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALGROUPSIZE), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckBitWidth(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckBitOffset(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (lstrlen((m_szValue = ExtractText(m_szValue))) > GetDatabaseEngine()->GetTCFunctionElementConstValueLength())
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

BOOL CSCOS2000DatabaseTCFunctionElementsRecordset::CheckConstValueSource(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCFunctionElementConstValueSource((m_szTMID = ExtractText(m_szTMID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONELEMENT_ILLEGALCONSTVALUESOURCE), (LPCTSTR)GetFunction(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_CDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCFunctionElementsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCFunctionElementsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_CNAME)), m_szCName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_ELTYPE)), m_szElType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_DESCR)), m_szDescr);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_ELLEN)), m_nElLen);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_BIT)), m_nBit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_GRPSIZE)), m_nGrpSize);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_PNAME)), m_szPName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_VALUE)), m_szValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CDF_TMID)), m_szTMID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCPacketsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCPacketsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCPacketsRecordset::CSCOS2000DatabaseTCPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCPacketsRecordset)
	m_szID.Empty();
	m_szDesc.Empty();
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCPacketsRecordset::SetID(LPCTSTR pszID)
{
	m_szID = pszID;
}

CString CSCOS2000DatabaseTCPacketsRecordset::GetID() CONST
{
	return m_szID;
}

VOID CSCOS2000DatabaseTCPacketsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDesc = pszDescription;
}

CString CSCOS2000DatabaseTCPacketsRecordset::GetDescription() CONST
{
	return m_szDesc;
}

VOID CSCOS2000DatabaseTCPacketsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szID), pszError);
}
VOID CSCOS2000DatabaseTCPacketsRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszError);
}

VOID CSCOS2000DatabaseTCPacketsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szID), pszWarning);
}
VOID CSCOS2000DatabaseTCPacketsRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszWarning);
}

VOID CSCOS2000DatabaseTCPacketsRecordset::Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket)
{
	SetID(pDatabaseTCPacket->GetTag());
	SetDescription(pDatabaseTCPacket->GetDescription());
}

BOOL CSCOS2000DatabaseTCPacketsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCPacketsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID();
		CheckDescription();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketsRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketTag((m_szID = ExtractText(m_szID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALTAG), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPacketDescription((m_szDesc = ExtractText(m_szDesc))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKET_ILLEGALDESCRIPTION), (LPCTSTR)GetID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCPacketsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCPacketsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_ID)), m_szID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TCP_DESC)), m_szDesc);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCPacketParametersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCPacketParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCPacketParametersRecordset::CSCOS2000DatabaseTCPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCPacketParametersRecordset)
	m_szTCName.Empty();
	m_szDesc.Empty();
	m_szType.Empty();
	m_szPName.Empty();
	m_szValue.Empty();
	m_szCode.Empty();
	m_szRadix.Empty();
	m_nLen = 0;
	m_nBit = 0;
	m_bHeader = TRUE;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::Open(UINT nOpenType, LPCTSTR lpszSQL, DWORD dwOptions, BOOL bHeader)
{
	m_nFields = ((m_bHeader = bHeader)) ? 3 : 8;
	return CSCOS2000DatabaseRecordset::Open(nOpenType, lpszSQL, dwOptions);
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szPName = pszTag;
}

CString CSCOS2000DatabaseTCPacketParametersRecordset::GetTag() CONST
{
	return m_szPName;
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::SetPacketID(LPCTSTR pszID)
{
	m_szTCName = pszID;
}

CString CSCOS2000DatabaseTCPacketParametersRecordset::GetPacketID() CONST
{
	return m_szTCName;
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDesc = pszDescription;
}

CString CSCOS2000DatabaseTCPacketParametersRecordset::GetDescription() CONST
{
	return m_szDesc;
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	if (m_bHeader)
	{
		m_szCode = GetDatabaseEngine()->TranslateTCPacketParameterValueCoding(nAttributes);
		return;
	}
	m_szType = GetDatabaseEngine()->TranslateTCPacketParameterType(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCPacketParameterValueRadix(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCPacketParametersRecordset::GetAttributes() CONST
{
	return((m_bHeader) ? (GetDatabaseEngine()->TranslateTCPacketParameterValueCoding(m_szCode) | TCPARAMETER_VTYPE_RAW | TCPARAMETER_CALIBRATION_NONE) : (GetDatabaseEngine()->TranslateTCPacketParameterType(m_szType) | TCPARAMETER_VTYPE_RAW | TCPARAMETER_CALIBRATION_NONE | GetDatabaseEngine()->TranslateTCPacketParameterValueRadix(m_szRadix)));
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::SetBitWidth(INT nLength)
{
	m_nLen = nLength;
}

INT CSCOS2000DatabaseTCPacketParametersRecordset::GetBitWidth() CONST
{
	return m_nLen;
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::SetBitOffset(INT nOffset)
{
	m_nBit = nOffset;
}

INT CSCOS2000DatabaseTCPacketParametersRecordset::GetBitOffset() CONST
{
	return m_nBit;
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szValue = pszConstValue;
}

CString CSCOS2000DatabaseTCPacketParametersRecordset::GetConstValue() CONST
{
	return m_szValue;
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szTCName), pszError);
}
VOID CSCOS2000DatabaseTCPacketParametersRecordset::ShowError(LPCTSTR pszTag, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszError);
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szTCName), pszWarning);
}
VOID CSCOS2000DatabaseTCPacketParametersRecordset::ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszTag, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pszWarning);
}

VOID CSCOS2000DatabaseTCPacketParametersRecordset::Translate(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter)
{
	m_bHeader = TRUE;
	SetPacketID(EMPTYSTRING);
	SetTag(pDatabaseTCPacketParameter->GetTag());
	SetDescription(pDatabaseTCPacketParameter->GetDescription());
	SetAttributes(pDatabaseTCPacketParameter->GetAttributes());
}
VOID CSCOS2000DatabaseTCPacketParametersRecordset::Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter)
{
	m_bHeader = FALSE;
	SetPacketID(pDatabaseTCPacket->GetTag());
	SetTag(pDatabaseTCPacketParameter->GetTag());
	SetDescription(pDatabaseTCPacketParameter->GetDescription());
	SetAttributes(pDatabaseTCPacketParameter->GetAttributes());
	SetBitWidth(pDatabaseTCPacketParameter->GetWidth());
	SetBitOffset((pDatabaseTCPacketParameter->GetBytePos() >= 0 && pDatabaseTCPacketParameter->GetBitPos() >= 0) ? (8 * pDatabaseTCPacketParameter->GetBytePos() + pDatabaseTCPacketParameter->GetBitPos()) : -1);
	SetConstValue(pDatabaseTCPacketParameter->GetConstValueAsText());
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCPacketParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		for (CheckTag(); m_bHeader; )
		{
			CheckDescription();
			CheckAttributes();
			return TRUE;
		}
		CheckPacketID();
		CheckDescription();
		CheckAttributes();
		CheckBitWidth();
		CheckBitOffset();
		CheckConstValue();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		for (bCheck = TRUE; m_bHeader; )
		{
			bCheck &= CheckTag(IsCollectingIssues());
			bCheck &= CheckDescription(IsCollectingIssues());
			bCheck &= CheckAttributes(IsCollectingIssues());
			return bCheck;
		}
		bCheck &= CheckPacketID(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckBitWidth(IsCollectingIssues());
		bCheck &= CheckBitOffset(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage[2];
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterTag((m_szPName = ExtractText(m_szPName))))
	{
		for (szMessage[0].Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETHEADERPARAMETER_ILLEGALTAG), (LPCTSTR)GetTag()), szMessage[1].Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALTAG), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError((m_bHeader) ? szMessage[0] : szMessage[1]);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::CheckPacketID(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketTag((m_szTCName = ExtractText(m_szTCName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALID), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage[2];
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterDescription((m_szDesc = ExtractText(m_szDesc))))
	{
		for (szMessage[0].Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETHEADERPARAMETER_ILLEGALDESCRIPTION), (LPCTSTR)GetTag()), szMessage[1].Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALDESCRIPTION), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError((m_bHeader) ? szMessage[0] : szMessage[1]);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::CheckAttributes(BOOL bStatus)
{
	BOOL  bMessage;
	CString  szMessage;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;

	for (bMessage = FALSE; !GetDatabaseEngine()->CheckTCPacketParameterType(GetTag(), (nAttributes = GetAttributes())); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALTYPE), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); !m_bHeader && bStatus; )
		{
			ShowError(szMessage);
			bMessage = TRUE;
			break;
		}
		break;
	}
	if (!GetDatabaseEngine()->CheckTCPacketParameterValueCoding(0, GetDatabaseEngine()->TranslateTCPacketParameterValueCoding((m_szCode = ExtractText(m_szCode)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETHEADERPARAMETER_ILLEGALCODING), (LPCTSTR)GetTag()); m_bHeader && bStatus; )
		{
			ShowError(szMessage);
			bMessage = TRUE;
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCPacketParameterValueRadix(nAttributes, GetDatabaseEngine()->TranslateTCPacketParameterValueRadix((m_szRadix = ExtractText(m_szRadix)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALRADIX), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); !m_bHeader && bStatus; )
		{
			ShowError(szMessage);
			bMessage = TRUE;
			break;
		}
	}
	return !bMessage;
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::CheckBitWidth(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterValueBitWidth(m_nLen))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALBITWIDTH), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::CheckBitOffset(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterValueBitOffset(m_nBit))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALBITOFFSET), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPacketParametersRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCPacketParameterConstValue(GetAttributes(), (m_szValue = ExtractText(m_szValue))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPACKETPARAMETER_ILLEGALCONSTVALUE), (LPCTSTR)GetPacketID(), (GetBitOffset() >= 0) ? (LPCTSTR)cStringTools.ConvertIntToString(GetBitOffset()) : STRING(IDS_DATABASE_TABLE_PCDF_BITOFFSET_UNKNOWN)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCPacketParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCPacketParametersRecordset)
	for (pFX->SetFieldType(CFieldExchange::outputColumn); m_bHeader; )
	{
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCPC_PNAME)), m_szPName);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCPC_DESC)), m_szDesc);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCPC_CODE)), m_szCode);
		break;
	}
	if (!m_bHeader)
	{
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_TCNAME)), m_szTCName);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_DESC)), m_szDesc);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_TYPE)), m_szType);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_LEN)), m_nLen);
		RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_BIT)), m_nBit);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_PNAME)), m_szPName);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_VALUE)), m_szValue);
		RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCDF_RADIX)), m_szRadix);
	}
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequencesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCSequencesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCSequencesRecordset::CSCOS2000DatabaseTCSequencesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCSequencesRecordset)
	m_szName.Empty();
	m_szDesc.Empty();
	m_szDesc2.Empty();
	m_szIFTT.Empty();
	m_szCritical.Empty();
	m_szPlan.Empty();
	m_szExec.Empty();
	m_szDefSet.Empty();
	m_szGenTime.Empty();
	m_szDocName.Empty();
	m_szIssue.Empty();
	m_szDate.Empty();
	m_nNFPars = 0;
	m_nElems = 0;
	m_nSubSys = 0;
	m_nSubSchedID = 0;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDesc = pszDescription;
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetDescription() CONST
{
	return m_szDesc;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetDetails(LPCTSTR pszDetails)
{
	m_szDesc2 = pszDetails;
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetDetails() CONST
{
	return m_szDesc2;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szIFTT = GetDatabaseEngine()->TranslateTCSequenceTimeTaggedFlag(nAttributes);
	m_szCritical = GetDatabaseEngine()->TranslateTCSequenceHazardousFlag(nAttributes);
	m_szPlan = GetDatabaseEngine()->TranslateTCSequencePlanningFlag(nAttributes);
	m_szExec = GetDatabaseEngine()->TranslateTCSequenceExecutionFlag(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCSequencesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceTimeTaggedFlag(m_szIFTT) | GetDatabaseEngine()->TranslateTCSequenceHazardousFlag(m_szCritical) | GetDatabaseEngine()->TranslateTCSequencePlanningFlag(m_szPlan) | GetDatabaseEngine()->TranslateTCSequenceExecutionFlag(m_szExec);
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetSubSystem(LPCTSTR pszSubSystem)
{
	m_nSubSys = _ttoi(pszSubSystem);
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetSubSystem() CONST
{
	CStringTools  cStringTools;

	return((m_nSubSys > 0) ? cStringTools.ConvertIntToString(m_nSubSys) : EMPTYSTRING);
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetSubSchedule(LPCTSTR pszSubSchedule)
{
	m_nSubSchedID = _ttoi(pszSubSchedule);
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetSubSchedule() CONST
{
	CStringTools  cStringTools;

	return((m_nSubSchedID > 0) ? cStringTools.ConvertIntToString(m_nSubSchedID) : EMPTYSTRING);
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetParameterSet(LPCTSTR pszSet)
{
	m_szDefSet = pszSet;
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetParameterSet() CONST
{
	return m_szDefSet;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetDate(CONST CTimeKey &tDate)
{
	m_szGenTime = GetDatabaseEngine()->TranslateTCSequenceDate(tDate, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT));
}

CTimeKey CSCOS2000DatabaseTCSequencesRecordset::GetDate() CONST
{
	TIMEKEY  tDate;

	return(((tDate = GetDatabaseEngine()->TranslateTCSequenceDate(m_szGenTime, STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)).GetTime()) <= 0) ? GetDatabaseEngine()->TranslateTCSequenceDate(m_szGenTime, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)) : tDate);
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetDocumentName(LPCTSTR pszName)
{
	m_szDocName = pszName;
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetDocumentName() CONST
{
	return m_szDocName;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetDocumentIssue(LPCTSTR pszIssue)
{
	m_szIssue = pszIssue;
}

CString CSCOS2000DatabaseTCSequencesRecordset::GetDocumentIssue() CONST
{
	return m_szIssue;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetDocumentDate(CONST CTimeKey &tDate)
{
	m_szDate = GetDatabaseEngine()->TranslateTCSequenceDocumentDate(tDate, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT));
}

CTimeKey CSCOS2000DatabaseTCSequencesRecordset::GetDocumentDate() CONST
{
	TIMEKEY  tDate;

	return(((tDate = GetDatabaseEngine()->TranslateTCSequenceDocumentDate(m_szDate, STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)).GetTime()) <= 0) ? GetDatabaseEngine()->TranslateTCSequenceDocumentDate(m_szDate, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)) : tDate);
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetParameterCount(INT nCount)
{
	m_nNFPars = nCount;
}

INT CSCOS2000DatabaseTCSequencesRecordset::GetParameterCount() CONST
{
	return m_nNFPars;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::SetEntryCount(INT nCount)
{
	m_nElems = nCount;
}

INT CSCOS2000DatabaseTCSequencesRecordset::GetEntryCount() CONST
{
	return m_nElems;
}

VOID CSCOS2000DatabaseTCSequencesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTCSequencesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTCSequencesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTCSequencesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseTCSequencesRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence)
{
	CStringArray  szSets;
	CDatabaseTCParameters  pDatabaseTCParameters;

	SetName(pDatabaseTCSequence->GetName());
	SetDescription(pDatabaseTCSequence->GetDescription());
	SetDetails(pDatabaseTCSequence->GetDetails());
	SetAttributes(pDatabaseTCSequence->GetAttributes());
	SetSubSystem(pDatabaseTCSequence->GetDestinationSubSystem());
	SetSubSchedule(pDatabaseTCSequence->GetDestinationSubSchedule());
	SetParameterSet((pDatabaseTCSequence->GetParameterSets(szSets) > 0) ? szSets.GetAt(0) : EMPTYSTRING);
	SetDate(pDatabaseTCSequence->GetDate());
	SetDocumentName(pDatabaseTCSequence->GetDocumentName());
	SetDocumentIssue(pDatabaseTCSequence->GetDocumentIssue());
	SetDocumentDate(pDatabaseTCSequence->GetDocumentDate());
	SetParameterCount(pDatabaseTCSequence->GetParameters(pDatabaseTCParameters));
	SetEntryCount((INT)pDatabaseTCSequence->GetSize());
}

BOOL CSCOS2000DatabaseTCSequencesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCSequencesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckDetails();
		CheckAttributes();
		CheckSubSystem();
		CheckSubSchedule();
		CheckParameterSet();
		CheckDate();
		CheckDocumentName();
		CheckDocumentIssue();
		CheckDocumentDate();
		CheckParameterCount();
		CheckEntryCount();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDescription((m_szDesc = ExtractText(m_szDesc))))
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

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckDetails(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDetails((m_szDesc2 = ExtractText(m_szDesc2))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALDETAILS), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceTimeTaggedFlag((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALTIMETAGGEDFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceHazardousFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALHAZFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequencePlanningFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALPLANFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceExecutionFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALEXECFLAG), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckSubSystem(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceSubSystemID(m_nSubSys))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALSUBSYSTEM), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckSubSchedule(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceSubScheduleID(m_nSubSchedID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALSUBSCHEDULE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckParameterSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDefaultParameterSetName((m_szDefSet = ExtractText(m_szDefSet))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCE_ILLEGALPARAMETERSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckDate(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDate((m_szGenTime = ExtractText(m_szGenTime)), STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceDate(m_szGenTime, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)))
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

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckDocumentName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDocumentName((m_szDocName = ExtractText(m_szDocName))))
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

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckDocumentIssue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDocumentIssue((m_szIssue = ExtractText(m_szIssue))))
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

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckDocumentDate(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceDocumentDate((m_szDate = ExtractText(m_szDate)), STRING(IDS_DATABASE_TABLE_CSF_DBMSDATE_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceDocumentDate(m_szDate, STRING(IDS_DATABASE_TABLE_CSF_DBMSSHORTDATE_FORMAT)))
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

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckParameterCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterCount(m_nNFPars))
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

BOOL CSCOS2000DatabaseTCSequencesRecordset::CheckEntryCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryCount(m_nElems))
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

void CSCOS2000DatabaseTCSequencesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCSequencesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DESC)), m_szDesc);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DESC2)), m_szDesc2);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_IFTT)), m_szIFTT);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_NFPARS)), m_nNFPars);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_ELEMS)), m_nElems);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_CRITICAL)), m_szCritical);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_PLAN)), m_szPlan);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_EXEC)), m_szExec);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_SUBSYS)), m_nSubSys);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_GENTIME)), m_szGenTime);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DOCNAME)), m_szDocName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_ISSUE)), m_szIssue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DATE)), m_szDate);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_DEFSET)), m_szDefSet);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSF_SUBSCHEDID)), m_nSubSchedID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequenceParametersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCSequenceParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCSequenceParametersRecordset::CSCOS2000DatabaseTCSequenceParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCSequenceParametersRecordset)
	m_szSQName.Empty();
	m_szFPName.Empty();
	m_szDescr.Empty();
	m_szDispFmt.Empty();
	m_szRadix.Empty();
	m_szType.Empty();
	m_szVType.Empty();
	m_szDefVal.Empty();
	m_szCateg.Empty();
	m_szPrfRef.Empty();
	m_szCcaRef.Empty();
	m_szPafRef.Empty();
	m_szUnit.Empty();
	m_nFPNum = 0;
	m_nPTC = 0;
	m_nPFC = 0;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szFPName = pszTag;
}

CString CSCOS2000DatabaseTCSequenceParametersRecordset::GetTag() CONST
{
	return m_szFPName;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetSequence(LPCTSTR pszSequence)
{
	m_szSQName = pszSequence;
}

CString CSCOS2000DatabaseTCSequenceParametersRecordset::GetSequence() CONST
{
	return m_szSQName;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetPosition(INT nPosition)
{
	m_nFPNum = nPosition;
}

INT CSCOS2000DatabaseTCSequenceParametersRecordset::GetPosition() CONST
{
	return m_nFPNum;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCSequenceParametersRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CSCOS2000DatabaseTCSequenceParametersRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetTypeCode(UINT nPTC)
{
	m_nPTC = nPTC;
}

UINT CSCOS2000DatabaseTCSequenceParametersRecordset::GetTypeCode() CONST
{
	return m_nPTC;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetFormatCode(UINT nPFC)
{
	m_nPFC = nPFC;
}

UINT CSCOS2000DatabaseTCSequenceParametersRecordset::GetFormatCode() CONST
{
	return m_nPFC;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCSequenceParameterType(nAttributes);
	m_szVType = GetDatabaseEngine()->TranslateTCSequenceParameterValueType(nAttributes);
	m_szCateg = GetDatabaseEngine()->TranslateTCSequenceParameterCategory(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCSequenceParameterValueRadix(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCSequenceParametersRecordset::GetAttributes(INT &nWidth) CONST
{
	ULONGLONG  nAttributes;

	return((GetDatabaseEngine()->TranslateParameterTypeCode(m_nPTC, m_nPFC, TRUE, nAttributes, nWidth)) ? (GetAttributes() | (nAttributes & ~(TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL))) : GetAttributes());
}
ULONGLONG CSCOS2000DatabaseTCSequenceParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceParameterType(m_szType) | GetDatabaseEngine()->TranslateTCSequenceParameterValueType(m_szVType) | GetDatabaseEngine()->TranslateTCSequenceParameterCategory(m_szCateg) | GetDatabaseEngine()->TranslateTCSequenceParameterValueRadix(m_szRadix);
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetDisplayFormat(ULONGLONG nFormat)
{
	m_szDispFmt = GetDatabaseEngine()->TranslateTCSequenceParameterDisplayFormat(nFormat);
}

ULONGLONG CSCOS2000DatabaseTCSequenceParametersRecordset::GetDisplayFormat() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceParameterDisplayFormat(m_szDispFmt);
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetCalTable(LPCTSTR pszTable)
{
	m_szCcaRef = (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) ? pszTable : EMPTYSTRING;
	m_szPafRef = (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) ? pszTable : EMPTYSTRING;
}

CString CSCOS2000DatabaseTCSequenceParametersRecordset::GetCalTable() CONST
{
	if (GetAttributes() & TCPARAMETER_CALIBRATION_NUMERICAL) return m_szCcaRef;
	if (GetAttributes() & TCPARAMETER_CALIBRATION_STATUS) return m_szPafRef;
	return EMPTYSTRING;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetOolTable(LPCTSTR pszTable)
{
	m_szPrfRef = pszTable;
}

CString CSCOS2000DatabaseTCSequenceParametersRecordset::GetOolTable() CONST
{
	return m_szPrfRef;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szDefVal = pszConstValue;
}

CString CSCOS2000DatabaseTCSequenceParametersRecordset::GetConstValue() CONST
{
	return m_szDefVal;
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSQName), pszError);
}
VOID CSCOS2000DatabaseTCSequenceParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTCSequenceParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSQName), pszWarning);
}
VOID CSCOS2000DatabaseTCSequenceParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition)
{
	SetPosition(nPosition);
	SetTag(pDatabaseTCParameter->GetTag());
	SetSequence(pDatabaseTCSequence->GetName());
	SetDescription(pDatabaseTCParameter->GetDescription());
	SetUnit(pDatabaseTCParameter->GetUnit());
	SetTypeCode(pDatabaseTCParameter->GetTypeCode());
	SetFormatCode(pDatabaseTCParameter->GetFormatCode());
	SetAttributes(pDatabaseTCParameter->GetAttributes());
	SetDisplayFormat(pDatabaseTCParameter->GetDisplayFormat());
	SetCalTable(pDatabaseTCParameter->GetCalTable());
	SetOolTable(pDatabaseTCParameter->GetOolTable());
	SetConstValue(pDatabaseTCParameter->GetConstValueAsText());
	return((!pDatabaseTCParameter->GetTag().IsEmpty()) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag();
		CheckSequence();
		CheckPosition();
		CheckDescription();
		CheckUnit();
		CheckTypeCode();
		CheckFormatCode();
		CheckAttributes();
		CheckDisplayFormat();
		CheckCalTable();
		CheckOolTable();
		CheckConstValue();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckSequence(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckTypeCode(IsCollectingIssues());
		bCheck &= CheckFormatCode(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckDisplayFormat(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterTag((m_szFPName = ExtractText(m_szFPName))))
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

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckSequence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceName((m_szSQName = ExtractText(m_szSQName))))
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

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckPosition(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterPosition(m_nFPNum))
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

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckUnit(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckTypeCode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterTypeCode(m_nPTC) && (GetAttributes() & (TCPARAMETER_TYPE_FUNCTION | TCPARAMETER_TYPE_SEQUENCE)) == 0)
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALTYPECODE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckFormatCode(BOOL bStatus)
{
	CString  szMessage;

	if (GetDatabaseEngine()->CheckTCParameterTypeCode(m_nPTC) && !GetDatabaseEngine()->CheckTCSequenceParameterFormatCode(m_nPTC, m_nPFC) && (GetAttributes() & (TCPARAMETER_TYPE_FUNCTION | TCPARAMETER_TYPE_SEQUENCE)) == 0)
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALFORMATCODE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckAttributes(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterType((nAttributes = GetAttributes(nWidth))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALTYPE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
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
	if (!GetDatabaseEngine()->CheckTCSequenceParameterCategory(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALCATEGORY), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceParameterValueRadix(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALRADIX), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckDisplayFormat(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterDisplayFormat(GetAttributes(nWidth), GetDatabaseEngine()->TranslateTCSequenceParameterDisplayFormat((m_szDispFmt = ExtractText(m_szDispFmt)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALDISPLAYFORMAT), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckCalTable(BOOL bStatus)
{
	CString  szMessage;

	for (m_szCcaRef = ExtractText(m_szCcaRef), m_szPafRef = ExtractText(m_szPafRef); !GetDatabaseEngine()->CheckTCSequenceParameterCalTable(GetAttributes(), GetCalTable()); )
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALCALIBRATIONTABLE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckOolTable(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceParameterOolTable(GetAttributes(), (m_szPrfRef = ExtractText(m_szPrfRef))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALOUTOFLIMITTABLE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceParametersRecordset::CheckConstValue(BOOL bStatus)
{
	INT  nWidth;
	ULONGLONG  nAttributes;
	CString  szMessage;

	if (((((nAttributes = GetAttributes(nWidth)) & TCPARAMETER_TYPE_NORMAL) && (nAttributes & TCPARAMETER_VTYPE_RAW) && (((nAttributes & (TCPARAMETER_VTYPE_COMMANDID | TCPARAMETER_VTYPE_PARAMETERID | TCPARAMETER_CODING_TIME)) == 0 && !GetDatabaseEngine()->CheckTCSequenceParameterConstValue((nAttributes & TCPARAMETER_VTYPE_CALIBRATED) ? (GetDisplayFormat() | (nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL))) : nAttributes, (m_szDefVal = ExtractText(m_szDefVal)))) || ((nAttributes & (TCPARAMETER_VTYPE_COMMANDID | TCPARAMETER_VTYPE_PARAMETERID)) == 0 && (nAttributes & TCPARAMETER_CODING_TIME) && !GetDatabaseEngine()->CheckTCSequenceParameterConstTime(nAttributes, (m_szDefVal = ExtractText(m_szDefVal))))))) || ((nAttributes & (TCPARAMETER_TYPE_FUNCTION | TCPARAMETER_TYPE_SEQUENCE | TCPARAMETER_VTYPE_CALIBRATED)) && !lstrlen((m_szDefVal = ExtractText(m_szDefVal)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEPARAMETER_ILLEGALDEFVALUE), (LPCTSTR)GetSequence(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCSequenceParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCSequenceParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_SQNAME)), m_szSQName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_FPNAME)), m_szFPName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_FPNUM)), m_nFPNum);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_DESCR)), m_szDescr);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_PTC)), m_nPTC);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_PFC)), m_nPFC);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_DISPFMT)), m_szDispFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_RADIX)), m_szRadix);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_VTYPE)), m_szVType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_DEFVAL)), m_szDefVal);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_CATEG)), m_szCateg);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_PRFREF)), m_szPrfRef);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_CCAREF)), m_szCcaRef);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_PAFREF)), m_szPafRef);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSP_UNIT)), m_szUnit);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequenceEntriesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCSequenceEntriesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCSequenceEntriesRecordset::CSCOS2000DatabaseTCSequenceEntriesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCSequenceEntriesRecordset)
	m_szSQName.Empty();
	m_szComm.Empty();
	m_szType.Empty();
	m_szElemID.Empty();
	m_szManDisp.Empty();
	m_szRelType.Empty();
	m_szRelTime.Empty();
	m_szExTime.Empty();
	m_szPrevRel.Empty();
	m_szGroup.Empty();
	m_szBlock.Empty();
	m_szILScope.Empty();
	m_szILStage.Empty();
	m_szDynPTV.Empty();
	m_szStaPTV.Empty();
	m_szCEV.Empty();
	m_nEntry = -1;
	m_nNPars = 0;
	m_nFields = 18;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetName(LPCTSTR pszName)
{
	m_szElemID = pszName;
}

CString CSCOS2000DatabaseTCSequenceEntriesRecordset::GetName() CONST
{
	return m_szElemID;
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetSequence(LPCTSTR pszSequence)
{
	m_szSQName = pszSequence;
}

CString CSCOS2000DatabaseTCSequenceEntriesRecordset::GetSequence() CONST
{
	return m_szSQName;
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szComm = pszDescription;
}

CString CSCOS2000DatabaseTCSequenceEntriesRecordset::GetDescription() CONST
{
	return m_szComm;
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCSequenceEntryType(nAttributes);
	m_szManDisp = GetDatabaseEngine()->TranslateTCSequenceEntryDispatchMode(nAttributes);
	m_szRelType = GetDatabaseEngine()->TranslateTCSequenceEntryReleaseTimeType(nAttributes);
	m_szPrevRel = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionTimeType(nAttributes);
	m_szGroup = GetDatabaseEngine()->TranslateTCSequenceEntryGroupFlag(nAttributes);
	m_szBlock = GetDatabaseEngine()->TranslateTCSequenceEntryBlockFlag(nAttributes);
	m_szILScope = GetDatabaseEngine()->TranslateTCSequenceEntryInterlockScope(nAttributes);
	m_szILStage = GetDatabaseEngine()->TranslateTCSequenceEntryInterlockStage(nAttributes);
	m_szDynPTV = GetDatabaseEngine()->TranslateTCSequenceEntryPTVCheckFlag(nAttributes);
	m_szStaPTV = GetDatabaseEngine()->TranslateTCSequenceEntryPEVCheckFlag(nAttributes);
	m_szCEV = GetDatabaseEngine()->TranslateTCSequenceEntryCEVCheckFlag(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCSequenceEntriesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceEntryType(m_szType) | GetDatabaseEngine()->TranslateTCSequenceEntryDispatchMode(m_szManDisp) | GetDatabaseEngine()->TranslateTCSequenceEntryReleaseTimeType(m_szRelType) | GetDatabaseEngine()->TranslateTCSequenceEntryExecutionTimeType(m_szPrevRel) | GetDatabaseEngine()->TranslateTCSequenceEntryGroupFlag(m_szGroup) | GetDatabaseEngine()->TranslateTCSequenceEntryBlockFlag(m_szBlock, EMPTYSTRING) | GetDatabaseEngine()->TranslateTCSequenceEntryInterlockScope(m_szILScope) | GetDatabaseEngine()->TranslateTCSequenceEntryInterlockStage(m_szILStage) | GetDatabaseEngine()->TranslateTCSequenceEntryPTVCheckFlag(m_szDynPTV) | GetDatabaseEngine()->TranslateTCSequenceEntryPEVCheckFlag(m_szStaPTV) | GetDatabaseEngine()->TranslateTCSequenceEntryCEVCheckFlag(m_szCEV) | ((GetDatabaseEngine()->TranslateTCSequenceEntryExecutionTimeType(m_szPrevRel) & (TCSEQUENCEENTRY_EXETIME_AFTERBEGIN | TCSEQUENCEENTRY_EXETIME_AFTERPREVIOUS)) ? TCSEQUENCEENTRY_EXETYPE_TIMETAG : TCSEQUENCEENTRY_EXETYPE_IMMEDIATE);
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetEntry(INT nEntry)
{
	m_nEntry = nEntry;
}

INT CSCOS2000DatabaseTCSequenceEntriesRecordset::GetEntry() CONST
{
	return m_nEntry;
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetReleaseDeltaTime(DWORD dwDelta)
{
	m_szRelTime = GetDatabaseEngine()->TranslateTCSequenceEntryReleaseDeltaTime(dwDelta, STRING(IDS_DATABASE_TABLE_CSS_RELTIME_FORMAT));
}

DWORD CSCOS2000DatabaseTCSequenceEntriesRecordset::GetReleaseDeltaTime() CONST
{
	DWORD  dwReleaseDeltaTime;

	return(((dwReleaseDeltaTime = GetDatabaseEngine()->TranslateTCSequenceEntryReleaseDeltaTime(m_szRelTime, STRING(IDS_DATABASE_TABLE_CSS_RELTIME_FORMAT))) == 0 && !m_szRelTime.IsEmpty()) ? GetDatabaseEngine()->TranslateTCSequenceEntryReleaseDeltaTime(m_szRelTime, STRING(IDS_DATABASE_TABLE_CSS_RELTIME_ALTERNATIVEFORMAT)) : dwReleaseDeltaTime);
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetExecutionDeltaTime(DWORD dwDelta, BOOL bEarlier)
{
	m_szExTime = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionDeltaTime(dwDelta, bEarlier, STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FULLFORMAT));
}

DWORD CSCOS2000DatabaseTCSequenceEntriesRecordset::GetExecutionDeltaTime(BOOL &bEarlier) CONST
{
	DWORD  dwExecutionDeltaTime;

	return(((dwExecutionDeltaTime = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionDeltaTime(m_szExTime, bEarlier, STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FULLFORMAT))) == 0 && !m_szExTime.IsEmpty()) ? (((dwExecutionDeltaTime = GetDatabaseEngine()->TranslateTCSequenceEntryExecutionDeltaTime(m_szExTime, bEarlier, STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FORMAT))) == 0 && !m_szExTime.IsEmpty()) ? GetDatabaseEngine()->TranslateTCSequenceEntryExecutionDeltaTime(m_szExTime, bEarlier, STRING(IDS_DATABASE_TABLE_CSS_EXETIME_ALTERNATIVEFORMAT)) : dwExecutionDeltaTime) : dwExecutionDeltaTime);
}
DWORD CSCOS2000DatabaseTCSequenceEntriesRecordset::GetExecutionDeltaTime() CONST
{
	BOOL  bEarlier;

	return GetExecutionDeltaTime(bEarlier);
}

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::IsEarlierExecutionDeltaTime() CONST
{
	BOOL  bEarlier;

	GetExecutionDeltaTime(bEarlier);
	return bEarlier;
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::SetParameterCount(INT nCount)
{
	m_nNPars = nCount;
}

INT CSCOS2000DatabaseTCSequenceEntriesRecordset::GetParameterCount() CONST
{
	return m_nNPars;
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSQName), pszError);
}
VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSQName), pszWarning);
}
VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseTCSequenceEntriesRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry, INT nEntry)
{
	SetEntry(nEntry + 1);
	SetName(pDatabaseTCSequenceEntry->GetName());
	SetSequence(pDatabaseTCSequence->GetName());
	SetDescription(pDatabaseTCSequenceEntry->GetDescription());
	SetAttributes(pDatabaseTCSequenceEntry->GetAttributes());
	SetReleaseDeltaTime(pDatabaseTCSequenceEntry->GetReleaseDeltaTime());
	SetExecutionDeltaTime(pDatabaseTCSequenceEntry->GetExecutionDeltaTime(), pDatabaseTCSequenceEntry->IsEarlierExecutionDeltaTime());
	SetParameterCount((INT)pDatabaseTCSequenceEntry->GetSize());
}

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckSequence();
		CheckDescription();
		CheckAttributes();
		CheckEntry();
		CheckReleaseDeltaTime();
		CheckExecutionDeltaTime();
		CheckParameterCount();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckSequence(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckEntry(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryName((m_szElemID = ExtractText(m_szElemID))) && ((GetAttributes() & TCSEQUENCEENTRY_TYPE_TEXTCOMMENT) == 0 || !m_szElemID.IsEmpty()))
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

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckSequence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceName((m_szSQName = ExtractText(m_szSQName))))
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

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryDescription((m_szComm = ExtractText(m_szComm))))
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

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckAttributes(BOOL bStatus)
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
	if (!GetDatabaseEngine()->CheckTCSequenceEntryDispatchMode(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALDISPATCHMODE), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryReleaseTimeType(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALRELEASETIMEFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryExecutionTimeType(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALEXECUTIONTIMEFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
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
	if (!GetDatabaseEngine()->CheckTCSequenceEntryBlockFlag(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALBLOCKFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryInterlockScope(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALINTERLOCKSCOPE), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryInterlockStage(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALINTERLOCKSTAGE), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryPTVCheckFlag(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALPTVCHECKFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryPEVCheckFlag(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALPEVCHECKFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryCEVCheckFlag(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRY_ILLEGALCEVCHECKFLAG), (LPCTSTR)GetSequence(), GetEntry()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckEntry(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckReleaseDeltaTime(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryReleaseDeltaTime((nAttributes = GetAttributes()), (m_szRelTime = ExtractText(m_szRelTime)), STRING(IDS_DATABASE_TABLE_CSS_RELTIME_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryReleaseDeltaTime(nAttributes, m_szRelTime, STRING(IDS_DATABASE_TABLE_CSS_RELTIME_ALTERNATIVEFORMAT)))
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

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckExecutionDeltaTime(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime((m_szExTime = ExtractText(m_szExTime)), STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FULLFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, STRING(IDS_DATABASE_TABLE_CSS_EXETIME_ALTERNATIVEFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, STRING(IDS_DATABASE_TABLE_CSS_EXETIME_ALTERNATIVEFULLFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime((m_szExTime = ExtractText(m_szExTime)), CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_FUTURE)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_FUTURE)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FULLFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_FUTURE)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_ALTERNATIVEFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_FUTURE)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_ALTERNATIVEFULLFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime((m_szExTime = ExtractText(m_szExTime)), CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_PAST)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_PAST)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_FULLFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_PAST)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_ALTERNATIVEFORMAT)) && !GetDatabaseEngine()->CheckTCSequenceEntryExecutionDeltaTime(m_szExTime, CString(STRING(IDS_DATABASE_TABLE_CSS_EXETIMEPREFIX_PAST)) + STRING(IDS_DATABASE_TABLE_CSS_EXETIME_ALTERNATIVEFULLFORMAT)))
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

BOOL CSCOS2000DatabaseTCSequenceEntriesRecordset::CheckParameterCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterCount(m_nNPars))
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

void CSCOS2000DatabaseTCSequenceEntriesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCSequenceEntriesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_SQNAME)), m_szSQName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_COMM)), m_szComm);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_ENTRY)), m_nEntry);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_ELEMID)), m_szElemID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_NPARS)), m_nNPars);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_MANDISP)), m_szManDisp);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_RELTYPE)), m_szRelType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_RELTIME)), m_szRelTime);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_EXTIME)), m_szExTime);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_PREVREL)), m_szPrevRel);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_GROUP)), m_szGroup);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_BLOCK)), m_szBlock);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_ILSCOPE)), m_szILScope);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_ILSCOPE)), m_szILStage);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_DYNPTV)), m_szDynPTV);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_STAPTV)), m_szStaPTV);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CSS_CEV)), m_szCEV);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequenceEntryParametersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCSequenceEntryParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CSCOS2000DatabaseTCSequenceEntryParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCSequenceEntryParametersRecordset)
	m_szSQName.Empty();
	m_szElemID.Empty();
	m_szPName.Empty();
	m_szFType.Empty();
	m_szVType.Empty();
	m_szValue.Empty();
	m_szValSet.Empty();
	m_nEntry = 0;
	m_nRepPos = 0;
	m_nPos = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szPName = pszTag;
}

CString CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetTag() CONST
{
	return m_szPName;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetSequence(LPCTSTR pszSequence)
{
	m_szSQName = pszSequence;
}

CString CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetSequence() CONST
{
	return m_szSQName;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetElement(LPCTSTR pszElement)
{
	m_szElemID = pszElement;
}

CString CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetElement() CONST
{
	return m_szElemID;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetEntry(INT nEntry)
{
	m_nEntry = nEntry;
}

INT CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetEntry() CONST
{
	return m_nEntry;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szFType = GetDatabaseEngine()->TranslateTCSequenceEntryParameterModificationFlag(nAttributes);
	m_szVType = GetDatabaseEngine()->TranslateTCSequenceEntryParameterValueType(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCSequenceEntryParameterModificationFlag(m_szFType) | GetDatabaseEngine()->TranslateTCSequenceEntryParameterValueType(m_szVType);
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetPosition(INT nPosition)
{
	m_nPos = nPosition;
}

INT CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetPosition() CONST
{
	return m_nPos;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetBitOffset(INT nOffset)
{
	m_nRepPos = nOffset;
}

INT CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetBitOffset() CONST
{
	return m_nRepPos;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szValue = pszConstValue;
}

CString CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetConstValue() CONST
{
	return m_szValue;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::SetValueSet(LPCTSTR pszSet)
{
	m_szValSet = pszSet;
}

CString CSCOS2000DatabaseTCSequenceEntryParametersRecordset::GetValueSet() CONST
{
	return m_szValSet;
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSQName), pszError);
}
VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSQName), pszWarning);
}
VOID CSCOS2000DatabaseTCSequenceEntryParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntryParameter *pDatabaseTCSequenceEntryParameter, INT nEntry)
{
	CDatabaseTCSequenceEntry  *pDatabaseTCSequenceEntry;

	SetEntry(nEntry + 1);
	SetTag(pDatabaseTCSequenceEntryParameter->GetTag());
	SetSequence(pDatabaseTCSequence->GetName());
	SetAttributes(pDatabaseTCSequenceEntryParameter->GetAttributes());
	for (SetElement(EMPTYSTRING), SetPosition(8 * pDatabaseTCSequenceEntryParameter->GetBytePos() + pDatabaseTCSequenceEntryParameter->GetBitPos()), SetBitOffset(pDatabaseTCSequenceEntryParameter->GetBitOffset()); (pDatabaseTCSequenceEntry = pDatabaseTCSequence->GetAt(nEntry)); )
	{
		for (SetElement(pDatabaseTCSequenceEntry->GetName()); (pDatabaseTCSequenceEntry->GetAttributes() & (TCSEQUENCEENTRY_TYPE_FUNCTION | TCSEQUENCEENTRY_TYPE_FORMALFUNCTION)) == 0; )
		{
			SetPosition(pDatabaseTCSequenceEntryParameter->GetBytePos());
			break;
		}
		break;
	}
	SetValueSet(pDatabaseTCSequenceEntryParameter->GetValueSet());
	SetConstValue(pDatabaseTCSequenceEntryParameter->GetConstValueAsText());
	return((!pDatabaseTCSequenceEntryParameter->GetTag().IsEmpty()) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag();
		CheckSequence();
		CheckAttributes();
		CheckEntry();
		CheckPosition();
		CheckBitOffset();
		CheckConstValue();
		CheckValueSet();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckSequence(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckEntry(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterTag((m_szPName = ExtractText(m_szPName))))
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

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckSequence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceName((m_szSQName = ExtractText(m_szSQName))))
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

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckElement(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterComment((m_szElemID = ExtractText(m_szElemID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALELEMENTID), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckEntry(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterPosition(GetEntry()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALENTRY), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;
	ULONGLONG  nAttributes;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterModificationFlag((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALMOFIFICATIONFLAG), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterValueType(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALVALUETYPE), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckPosition(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterPosition(GetPosition()))
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

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckBitOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterBitOffset(GetBitOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALREPPOSITION), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterConstValue(GetAttributes(), (m_szValue = ExtractText(m_szValue))))
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

BOOL CSCOS2000DatabaseTCSequenceEntryParametersRecordset::CheckValueSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCSequenceEntryParameterValueSetName((m_szValSet = ExtractText(m_szValSet))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCSEQUENCEENTRYPARAMETER_ILLEGALVALUESET), (LPCTSTR)GetSequence(), GetEntry(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCSequenceEntryParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCSequenceEntryParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_SQNAME)), m_szSQName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_ENTRY)), m_nEntry);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_ELEMID)), m_szElemID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_POS)), m_nPos);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_PNAME)), m_szPName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_FTYPE)), m_szFType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_VTYPE)), m_szVType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_VALUE)), m_szValue);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_VALSET)), m_szValSet);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SDF_REPPOS)), m_nRepPos);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseOBProcessorsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseOBProcessorsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseOBProcessorsRecordset::CSCOS2000DatabaseOBProcessorsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseOBProcessorsRecordset)
	m_szName.Empty();
	m_szDescription.Empty();
	m_szPatchCommand.Empty();
	m_szDumpCommand.Empty();
	m_szDumpPacket.Empty();
	m_szMasterImage.Empty();
	m_szAddressBase.Empty();
	m_nAddressRange[0][0] = 0;
	m_nAddressRange[0][1] = 0;
	m_nAddressRange[1][0] = 0;
	m_nAddressRange[1][1] = 0;
	m_tDumpInterval = 0;
	m_nDumpCount = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseOBProcessorsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CSCOS2000DatabaseOBProcessorsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetAttributes(UINT nAttributes)
{
	m_szAddressBase = GetDatabaseEngine()->TranslateOBProcessorAddressBase(nAttributes);
}

UINT CSCOS2000DatabaseOBProcessorsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorAddressBase(m_szAddressBase);
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetPatchCommand(LPCTSTR pszCommand)
{
	m_szPatchCommand = pszCommand;
}

CString CSCOS2000DatabaseOBProcessorsRecordset::GetPatchCommand() CONST
{
	return m_szPatchCommand;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetDumpCommand(LPCTSTR pszCommand)
{
	m_szDumpCommand = pszCommand;
}

CString CSCOS2000DatabaseOBProcessorsRecordset::GetDumpCommand() CONST
{
	return m_szDumpCommand;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetDumpPacket(LPCTSTR pszPacket)
{
	m_szDumpPacket = pszPacket;
}

CString CSCOS2000DatabaseOBProcessorsRecordset::GetDumpPacket() CONST
{
	return m_szDumpPacket;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetDumpInterval(CONST CTimeSpan &tInterval)
{
	m_tDumpInterval = (INT)tInterval.GetTotalSeconds();
}

CTimeSpan CSCOS2000DatabaseOBProcessorsRecordset::GetDumpInterval() CONST
{
	return m_tDumpInterval;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetDumpCount(INT nCount)
{
	m_nDumpCount = nCount;
}

INT CSCOS2000DatabaseOBProcessorsRecordset::GetDumpCount() CONST
{
	return m_nDumpCount;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetMasterImage(LPCTSTR pszImage)
{
	m_szMasterImage = pszImage;
}

CString CSCOS2000DatabaseOBProcessorsRecordset::GetMasterImage() CONST
{
	return m_szMasterImage;
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::SetAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress)
{
	m_nAddressRange[0][0] = nStartPage;
	m_nAddressRange[0][1] = nEndPage;
	m_nAddressRange[1][0] = nStartAddress;
	m_nAddressRange[1][1] = nEndAddress;
}

BOOL CSCOS2000DatabaseOBProcessorsRecordset::GetAddressRange(UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST
{
	return GetDatabaseEngine()->CheckOBProcessorAddressRange((nStartPage = m_nAddressRange[0][0]), (nStartAddress = m_nAddressRange[1][0]), (nEndPage = m_nAddressRange[0][1]), (nEndAddress = m_nAddressRange[1][1]));
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseOBProcessorsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseOBProcessorsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseOBProcessorsRecordset::Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor)
{
	UINT  nAddress[2][2];

	SetName(pDatabaseOBProcessor->GetName());
	SetDescription(pDatabaseOBProcessor->GetDescription());
	SetAttributes(pDatabaseOBProcessor->GetAttributes());
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
}

BOOL CSCOS2000DatabaseOBProcessorsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseOBProcessorsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckAttributes();
		CheckPatchCommand();
		CheckDumpCommand();
		CheckDumpPacket();
		CheckDumpInterval();
		CheckDumpCount();
		CheckMasterImage();
		CheckAddressRange();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckDumpCommand(IsCollectingIssues());
		bCheck &= CheckDumpPacket(IsCollectingIssues());
		bCheck &= CheckDumpInterval(IsCollectingIssues());
		bCheck &= CheckMasterImage(IsCollectingIssues());
		bCheck &= CheckAddressRange(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckOBProcessorAddressBase(GetDatabaseEngine()->TranslateOBProcessorAddressBase((m_szAddressBase = ExtractText(m_szAddressBase)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_OBPROCESSOR_ILLEGALADDRESSBASE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckPatchCommand(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckDumpCommand(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckDumpPacket(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckDumpInterval(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckDumpCount(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckMasterImage(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorsRecordset::CheckAddressRange(BOOL bStatus)
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

void CSCOS2000DatabaseOBProcessorsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseOBProcessorsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_PROCESSOR)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_DESCR)), m_szDescription);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_PATCHTC)), m_szPatchCommand);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_DUMPTC)), m_szDumpCommand);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_TMPKT)), m_szDumpPacket);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GEN_ADDRBASE)), m_szAddressBase);
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
// CSCOS2000DatabaseOBProcessorMemoryImagesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryImagesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::CSCOS2000DatabaseOBProcessorMemoryImagesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseOBProcessorMemoryImagesRecordset)
	m_szName.Empty();
	m_szVersion.Empty();
	m_szData.Empty();
	m_nAddress[0] = 0;
	m_nAddress[1] = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::SetVersion(LPCTSTR pszVersion)
{
	m_szVersion = pszVersion;
}

CString CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::GetVersion() CONST
{
	return m_szVersion;
}

VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::SetAddress(UINT nPage, UINT nAddress)
{
	m_nAddress[0] = nPage;
	m_nAddress[1] = nAddress;
}

BOOL CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::GetAddress(UINT &nPage, UINT &nAddress) CONST
{
	return GetDatabaseEngine()->CheckOBProcessorMemoryImageBlockAddress((nPage = m_nAddress[0]), (nAddress = m_nAddress[1]));
}

VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::SetData(LPCTSTR pszData)
{
	m_szData = GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(pszData, TRUE);
}
VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::SetData(CONST CByteArray &nData, CONST CByteArray &nMask)
{
	m_szData = GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(nData, nMask);
}

CString CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::GetData() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(m_szData, FALSE);
}
INT CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::GetData(CByteArray &nData, CByteArray &nMask) CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryImageBlockData(m_szData, nData, nMask);
}

VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, pszError);
}

VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, pszWarning);
}

VOID CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::Translate(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, CONST CDatabaseOBProcessorMemoryImageBlock *pDatabaseOBProcessorMemoryImageBlock)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckVersion();
		CheckAddress();
		CheckData();
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

BOOL CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::CheckVersion(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::CheckAddress(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::CheckData(BOOL bStatus)
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

void CSCOS2000DatabaseOBProcessorMemoryImagesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseOBProcessorMemoryImagesRecordset)
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
// CSCOS2000DatabaseOBProcessorMemoryAreasRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreasRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CSCOS2000DatabaseOBProcessorMemoryAreasRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseOBProcessorMemoryAreasRecordset)
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

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::SetPatchCommand(LPCTSTR pszCommand)
{
	m_szPatchCommand = pszCommand;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::GetPatchCommand() CONST
{
	return m_szPatchCommand;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::SetDumpCommand(LPCTSTR pszCommand)
{
	m_szDumpCommand = pszCommand;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::GetDumpCommand() CONST
{
	return m_szDumpCommand;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::SetDumpPacket(LPCTSTR pszPacket)
{
	m_szDumpPacket = pszPacket;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::GetDumpPacket() CONST
{
	return m_szDumpPacket;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::SetAttributes(UINT nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaType(nAttributes);
	m_szPatchFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaPatchFlag(nAttributes);
	m_szDumpFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaDumpFlag(nAttributes);
	m_szUpdateFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaUpdateFlag(nAttributes);
	m_szInhibitFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaInhibitFlag(nAttributes);
}

UINT CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryAreaType(m_szType) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaPatchFlag(m_szPatchFlag) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaDumpFlag(m_szDumpFlag) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaUpdateFlag(m_szUpdateFlag) | GetDatabaseEngine()->TranslateOBProcessorMemoryAreaInhibitFlag(m_szInhibitFlag);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckProcessor();
		CheckDescription();
		CheckAttributes();
		CheckPatchCommand();
		CheckDumpCommand();
		CheckDumpPacket();
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CheckProcessor(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CheckDescription(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CheckAttributes(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CheckPatchCommand(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CheckDumpCommand(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::CheckDumpPacket(BOOL bStatus)
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

void CSCOS2000DatabaseOBProcessorMemoryAreasRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseOBProcessorMemoryAreasRecordset)
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
// CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset)
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

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetTMParameter(LPCTSTR pszTag)
{
	m_szParameter[0] = pszTag;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetTMParameter() CONST
{
	return m_szParameter[0];
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetTCParameter(LPCTSTR pszTag)
{
	m_szParameter[1] = pszTag;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetTCParameter() CONST
{
	return m_szParameter[1];
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetAddress(UINT nPage, UINT nAddress)
{
	m_nAddress[0] = nPage;
	m_nAddress[1] = nAddress;
}

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetAddress(UINT &nPage, UINT &nAddress) CONST
{
	nPage = m_nAddress[0];
	nAddress = m_nAddress[1];
	return GetDatabaseEngine()->CheckOBProcessorMemoryAreaBlockAddress(nPage, nAddress);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetBitOffset(INT nOffset)
{
	m_nBitOffset = nOffset;
}

INT CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetBitOffset() CONST
{
	return m_nBitOffset;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::SetBitWidth(INT nWidth)
{
	m_nBitWidth = nWidth;
}

INT CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::GetBitWidth() CONST
{
	return m_nBitWidth;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::Translate(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaBlock *pDatabaseOBProcessorMemoryAreaBlock)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
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
		CheckName();
		CheckDescription();
		CheckTMParameter();
		CheckTCParameter();
		CheckAddress();
		CheckBitOffset();
		CheckBitWidth();
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CheckDescription(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CheckTMParameter(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CheckTCParameter(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CheckAddress(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CheckBitOffset(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::CheckBitWidth(BOOL bStatus)
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

void CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset)
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
// CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset)
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

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetSeed(UINT nValue)
{
	m_szSeedValue = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCheckSumSeedValue(nValue);
}

UINT CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetSeed() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCheckSumSeedValue(m_szSeedValue);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetLength(INT nLength)
{
	m_nLength = nLength;
}

INT CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetLength() CONST
{
	return m_nLength;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetDestination(UINT nDestination)
{
	m_nDestination = nDestination;
}

UINT CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetDestination() CONST
{
	return m_nDestination;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::SetAddressRange(UINT nPage, UINT nStartAddress, UINT nEndAddress)
{
	m_nAddress[0] = nPage;
	m_nAddress[1] = nStartAddress;
	m_nAddress[2] = nEndAddress;
}

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::GetAddressRange(UINT &nPage, UINT &nStartAddress, UINT &nEndAddress) CONST
{
	return GetDatabaseEngine()->CheckOBProcessorMemoryAreaCheckSumAddressRange((nPage = m_nAddress[0]), (nStartAddress = m_nAddress[1]), (nEndAddress = m_nAddress[2]));
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaCheckSum *pDatabaseOBProcessorMemoryAreaCheckSum)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckProcessor();
		CheckSeed();
		CheckLength();
		CheckDestination();
		CheckAddressRange();
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckProcessor(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckSeed(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckLength(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckDestination(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::CheckAddressRange(BOOL bStatus)
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

void CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset)
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
// CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset)
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

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetID(LPCTSTR pszID)
{
	m_szID = pszID;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetID() CONST
{
	return m_szID;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetProcessor(LPCTSTR pszProcessor)
{
	m_szProcessor = pszProcessor;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetProcessor() CONST
{
	return m_szProcessor;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetAttributes(UINT nAttributes)
{
	m_szFlag = GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCatalogueEntryFlag(nAttributes);
}

UINT CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateOBProcessorMemoryAreaCatalogueEntryFlag(m_szFlag);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetLocation(LPCTSTR pszLocation)
{
	m_szLocation = pszLocation;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetLocation() CONST
{
	return m_szLocation;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetVersion(LPCTSTR pszVersion)
{
	m_szVersion = pszVersion;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetVersion() CONST
{
	return m_szVersion;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetDate(LPCTSTR pszDate)
{
	m_szDate = pszDate;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetDate() CONST
{
	return m_szDate;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::SetTime(LPCTSTR pszTime)
{
	m_szTime = pszTime;
}

CString CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::GetTime() CONST
{
	return m_szTime;
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szProcessor), pszError);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szProcessor), pszWarning);
}
VOID CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::Translate(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaCatalogueEntry *pDatabaseOBProcessorMemoryAreaCatalogueEntry)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
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
		CheckID();
		CheckName();
		CheckDescription();
		CheckAttributes();
		CheckLocation();
		CheckVersion();
		CheckDate();
		CheckTime();
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckID(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckDescription(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckAttributes(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckLocation(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckVersion(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckDate(BOOL bStatus)
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

BOOL CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::CheckTime(BOOL bStatus)
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

void CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset)
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
// CSCOS2000DatabaseTMParametersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMParametersRecordset::CSCOS2000DatabaseTMParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMParametersRecordset)
	m_szName.Empty();
	m_szDescr.Empty();
	m_szUnit.Empty();
	m_szValid.Empty();
	m_szRelated.Empty();
	m_szCateg.Empty();
	m_szNatur.Empty();
	m_szCurTx.Empty();
	m_szInter.Empty();
	m_szUsCon.Empty();
	m_szParVal.Empty();
	m_szSubSys.Empty();
	m_szSpType.Empty();
	m_szCorr.Empty();
	m_szDarc.Empty();
	m_szEndian.Empty();
	m_nPID = 0;
	m_nPTC = 0;
	m_nPFC = 0;
	m_nWidth = 0;
	m_nDecim = 0;
	m_nValPar = 0;
	m_nOBTID = 0;
	m_nFields = 23;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szName = pszTag;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetTag() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetTypeCode(UINT nPTC)
{
	m_nPTC = nPTC;
}

UINT CSCOS2000DatabaseTMParametersRecordset::GetTypeCode() CONST
{
	return m_nPTC;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetFormatCode(UINT nPFC)
{
	m_nPFC = nPFC;
}

UINT CSCOS2000DatabaseTMParametersRecordset::GetFormatCode() CONST
{
	return m_nPFC;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szCateg = GetDatabaseEngine()->TranslateTMParameterCategory(nAttributes);
	m_szNatur = GetDatabaseEngine()->TranslateTMParameterNature(nAttributes);
	m_szInter = GetDatabaseEngine()->TranslateTMParameterInterpretation(nAttributes);
	m_szSpType = GetDatabaseEngine()->TranslateTMParameterResultType(nAttributes);
	m_szUsCon = GetDatabaseEngine()->TranslateTMParameterConsistencyChecksFlag(nAttributes);
	m_szCorr = GetDatabaseEngine()->TranslateTMParameterTimeCorrelationFlag(nAttributes);
	m_szDarc = GetDatabaseEngine()->TranslateTMParameterArchivingFlag(nAttributes);
	m_szEndian = GetDatabaseEngine()->TranslateTMParameterEndianityFlag(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTMParametersRecordset::GetAttributes(INT &nWidth) CONST
{
	ULONGLONG  nAttributes;

	return((GetDatabaseEngine()->TranslateParameterTypeCode(m_nPTC, m_nPFC, FALSE, nAttributes, nWidth)) ? (GetAttributes() | nAttributes) : GetAttributes());
}
ULONGLONG CSCOS2000DatabaseTMParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTMParameterCategory(m_szCateg) | GetDatabaseEngine()->TranslateTMParameterNature(m_szNatur) | GetDatabaseEngine()->TranslateTMParameterInterpretation(m_szInter) | GetDatabaseEngine()->TranslateTMParameterResultType(m_szSpType) | GetDatabaseEngine()->TranslateTMParameterConsistencyChecksFlag(m_szUsCon) | GetDatabaseEngine()->TranslateTMParameterTimeCorrelationFlag(m_szCorr) | GetDatabaseEngine()->TranslateTMParameterArchivingFlag(m_szDarc) | GetDatabaseEngine()->TranslateTMParameterEndianityFlag(m_szEndian);
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetBitWidth(INT nWidth)
{
	m_nWidth = nWidth;
}

INT CSCOS2000DatabaseTMParametersRecordset::GetBitWidth() CONST
{
	return m_nWidth;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szParVal = pszConstValue;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetConstValue() CONST
{
	return m_szParVal;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetValidityParameter(LPCTSTR pszParameter)
{
	m_szValid = pszParameter;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetValidityParameter() CONST
{
	return m_szValid;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetValidityValue(INT nValue)
{
	m_nValPar = nValue;
}

INT CSCOS2000DatabaseTMParametersRecordset::GetValidityValue() CONST
{
	return m_nValPar;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetRelatedParameter(LPCTSTR pszParameter)
{
	m_szRelated = pszParameter;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetRelatedParameter() CONST
{
	return m_szRelated;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetCalibrationTable(LPCTSTR pszTable)
{
	m_szCurTx = pszTable;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetCalibrationTable() CONST
{
	return m_szCurTx;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetOnBoardID(INT nPID)
{
	m_nPID = nPID;
}

INT CSCOS2000DatabaseTMParametersRecordset::GetOnBoardID() CONST
{
	return m_nPID;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetOnBoardTimerID(INT nOBTID)
{
	m_nOBTID = nOBTID;
}

INT CSCOS2000DatabaseTMParametersRecordset::GetOnBoardTimerID() CONST
{
	return m_nOBTID;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetSubSystem(LPCTSTR pszSubSystem)
{
	m_szSubSys = pszSubSystem;
}

CString CSCOS2000DatabaseTMParametersRecordset::GetSubSystem() CONST
{
	return m_szSubSys;
}

VOID CSCOS2000DatabaseTMParametersRecordset::SetDecimalDigits(INT nDigits)
{
	m_nDecim = nDigits;
}

INT CSCOS2000DatabaseTMParametersRecordset::GetDecimalDigits() CONST
{
	return m_nDecim;
}

VOID CSCOS2000DatabaseTMParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTMParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTMParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTMParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseTMParametersRecordset::Translate(CONST CDatabaseTMParameter *pDatabaseTMParameter)
{
	CStringArray  szTables[2];

	SetTag(pDatabaseTMParameter->GetTag());
	SetDescription(pDatabaseTMParameter->GetDescription());
	SetUnit(pDatabaseTMParameter->GetUnit());
	SetTypeCode(pDatabaseTMParameter->GetTypeCode());
	SetFormatCode(pDatabaseTMParameter->GetFormatCode());
	SetAttributes(pDatabaseTMParameter->GetAttributes());
	SetBitWidth(pDatabaseTMParameter->GetWidth(TRUE));
	SetConstValue(pDatabaseTMParameter->GetConstValueAsText());
	SetRelatedParameter(pDatabaseTMParameter->GetRelatedParameter());
	SetValidityParameter(pDatabaseTMParameter->GetValidityParameter());
	SetValidityValue((INT)pDatabaseTMParameter->GetValidityValue());
	SetCalibrationTable((pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]) == 1 && !szTables[0].GetAt(szTables[0].GetUpperBound()).IsEmpty() && szTables[1].GetAt(szTables[1].GetUpperBound()).IsEmpty()) ? szTables[0].GetAt(szTables[0].GetUpperBound()) : EMPTYSTRING);
	SetOnBoardID(pDatabaseTMParameter->GetOnBoardID());
	SetOnBoardTimerID(pDatabaseTMParameter->GetOnBoardTimerID());
	SetSubSystem(pDatabaseTMParameter->GetSourceSubSystem());
	SetDecimalDigits(pDatabaseTMParameter->GetDecimalDigits());
}

BOOL CSCOS2000DatabaseTMParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag();
		CheckDescription();
		CheckUnit();
		CheckTypeCode();
		CheckFormatCode();
		CheckAttributes();
		CheckBitWidth();
		CheckConstValue();
		CheckValidityParameter();
		CheckValidityValue();
		CheckRelatedParameter();
		CheckCalibrationTable();
		CheckOnBoardID();
		CheckOnBoardTimerID();
		CheckSubSystem();
		CheckDecimalDigits();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckTypeCode(IsCollectingIssues());
		bCheck &= CheckFormatCode(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckConstValue(IsCollectingIssues());
		bCheck &= CheckValidityValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szName = ExtractText(m_szName))))
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

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckUnit(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckTypeCode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTypeCode(m_nPTC))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALTYPECODE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckFormatCode(BOOL bStatus)
{
	CString  szMessage;

	if (GetDatabaseEngine()->CheckTMParameterTypeCode(m_nPTC) && !GetDatabaseEngine()->CheckTMParameterFormatCode(m_nPTC, m_nPFC))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALFORMATCODE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckAttributes(BOOL bStatus)
{
	INT  nWidth;
	ULONGLONG  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterCategory(nAttributes = GetAttributes(nWidth)))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALCATEGORY), (LPCTSTR)GetTag()); bStatus; )
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
	if (!GetDatabaseEngine()->CheckTMParameterInterpretation(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALINTERPRETATION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterResultType(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALRESULTTYPE), (LPCTSTR)GetTag()); bStatus; )
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
	if (!GetDatabaseEngine()->CheckTMParameterTimeCorrelationFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALTIMECORRELATIONFLAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterArchivingFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALARCHIVINGFLAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMParameterEndianityFlag(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALENDIANITYFLAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckBitWidth(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterBitWidth(GetAttributes(nWidth), GetBitWidth()))
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

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckConstValue(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterConstValue(GetAttributes(nWidth), (m_szParVal = ExtractText(m_szParVal))))
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

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityParameter((m_szValid = ExtractText(m_szValid))))
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

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckValidityValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterValidityValue(m_nValPar) && !GetValidityParameter().IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALVALIDITYVALUE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckRelatedParameter(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterRelatedParameter(GetAttributes(nWidth), (m_szRelated = ExtractText(m_szRelated))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALRELATEDPARAMETER), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckCalibrationTable(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterCalibrationTable(GetAttributes(nWidth), (m_szCurTx = ExtractText(m_szCurTx))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALCALIBRATIONTABLE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckOnBoardID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterOnBoardID(m_nPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALONBOARDID), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckOnBoardTimerID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterOnBoardTimerID(m_nOBTID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALONBOARDTIMERID), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckSubSystem(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterSourceSubSystem((m_szSubSys = ExtractText(m_szSubSys))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALSUBSYSTEM), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParametersRecordset::CheckDecimalDigits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterDecimalDigits(m_nDecim))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETER_ILLEGALDECIMALDIGITS), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_DESCR)), m_szDescr);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_PID)), m_nPID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_UNIT)), m_szUnit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_PTC)), m_nPTC);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_PFC)), m_nPFC);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_WIDTH)), m_nWidth);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_VALID)), m_szValid);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_RELATED)), m_szRelated);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_CATEG)), m_szCateg);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_NATUR)), m_szNatur);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_CURTX)), m_szCurTx);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_USCON)), m_szUsCon);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_DECIM)), m_nDecim);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_PARVAL)), m_szParVal);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_SUBSYS)), m_szSubSys);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_VALPAR)), m_nValPar);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_SPTYPE)), m_szSpType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_CORR)), m_szCorr);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_OBTID)), m_nOBTID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_DARC)), m_szDarc);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PCF_ENDIAN)), m_szEndian);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMParameterGroupsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMParameterGroupsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMParameterGroupsRecordset::CSCOS2000DatabaseTMParameterGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMParameterGroupsRecordset)
	m_szName.Empty();
	m_szDescr.Empty();
	m_szGType.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMParameterGroupsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMParameterGroupsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMParameterGroupsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMParameterGroupsRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMParameterGroupsRecordset::SetType(INT nType)
{
	m_szGType = GetDatabaseEngine()->TranslateTMParameterGroupType(nType);
}

INT CSCOS2000DatabaseTMParameterGroupsRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateTMParameterGroupType(m_szGType);
}

VOID CSCOS2000DatabaseTMParameterGroupsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTMParameterGroupsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP, pszError);
}

VOID CSCOS2000DatabaseTMParameterGroupsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTMParameterGroupsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP, pszWarning);
}

VOID CSCOS2000DatabaseTMParameterGroupsRecordset::Translate(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup)
{
	SetName(pDatabaseTMParameterGroup->GetName());
	SetDescription(pDatabaseTMParameterGroup->GetDescription());
	SetType();
}

BOOL CSCOS2000DatabaseTMParameterGroupsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMParameterGroupsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckType();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckDescription(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParameterGroupsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterGroupName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETERGROUP_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParameterGroupsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterGroupDescription((m_szDescr = ExtractText(m_szDescr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETERGROUP_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParameterGroupsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterGroupType((m_szGType = ExtractText(m_szGType))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETERGROUP_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMParameterGroupsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMParameterGroupsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRP_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRP_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRP_GTYPE)), m_szGType);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMParameterGroupMembersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMParameterGroupMembersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMParameterGroupMembersRecordset::CSCOS2000DatabaseTMParameterGroupMembersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMParameterGroupMembersRecordset)
	m_szGName.Empty();
	m_szPAName.Empty();
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMParameterGroupMembersRecordset::SetGroup(LPCTSTR pszName)
{
	m_szGName = pszName;
}

CString CSCOS2000DatabaseTMParameterGroupMembersRecordset::GetGroup() CONST
{
	return m_szGName;
}

VOID CSCOS2000DatabaseTMParameterGroupMembersRecordset::SetParameter(LPCTSTR pszParameter)
{
	m_szPAName = pszParameter;
}

CString CSCOS2000DatabaseTMParameterGroupMembersRecordset::GetParameter() CONST
{
	return m_szPAName;
}

VOID CSCOS2000DatabaseTMParameterGroupMembersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szGName), pszError);
}
VOID CSCOS2000DatabaseTMParameterGroupMembersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP, pszError);
}

VOID CSCOS2000DatabaseTMParameterGroupMembersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szGName), pszWarning);
}
VOID CSCOS2000DatabaseTMParameterGroupMembersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP, pszWarning);
}

VOID CSCOS2000DatabaseTMParameterGroupMembersRecordset::Translate(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, LPCTSTR pszParameter)
{
	SetGroup(pDatabaseTMParameterGroup->GetName());
	SetParameter(pszParameter);
}

BOOL CSCOS2000DatabaseTMParameterGroupMembersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMParameterGroupMembersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckGroup();
		CheckParameter();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckGroup(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParameterGroupMembersRecordset::CheckGroup(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterGroupName((m_szGName = ExtractText(m_szGName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETERGROUPMEMBER_ILLEGALNAME), (LPCTSTR)GetGroup()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMParameterGroupMembersRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterGroupMember((m_szPAName = ExtractText(m_szPAName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMPARAMETERGROUPMEMBER_ILLEGALPARAMETER), (LPCTSTR)GetGroup(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMParameterGroupMembersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMParameterGroupMembersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRPA_GNAME)), m_szGName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GRPA_PANAME)), m_szPAName);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMNumCalTablesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMNumCalTablesRecordset::CSCOS2000DatabaseTMNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMNumCalTablesRecordset)
	m_szNumbr.Empty();
	m_szDescr.Empty();
	m_szEngFmt.Empty();
	m_szRawFmt.Empty();
	m_szRadix.Empty();
	m_szUnit.Empty();
	m_szInter.Empty();
	m_nNCurve = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTMNumCalTablesRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMNumCalTablesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CSCOS2000DatabaseTMNumCalTablesRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szEngFmt = GetDatabaseEngine()->TranslateTMNumCalTableEngineeringValuesCoding(nAttributes);
	m_szRawFmt = GetDatabaseEngine()->TranslateTMNumCalTableRawValuesCoding(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTMNumCalTableRawValuesRadix(nAttributes);
	m_szInter = GetDatabaseEngine()->TranslateTMNumCalTableInterpretation(nAttributes);
}

UINT CSCOS2000DatabaseTMNumCalTablesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTMNumCalTableEngineeringValuesCoding(m_szEngFmt) | GetDatabaseEngine()->TranslateTMNumCalTableRawValuesCoding(m_szRawFmt) | GetDatabaseEngine()->TranslateTMNumCalTableRawValuesRadix(m_szRadix) | GetDatabaseEngine()->TranslateTMNumCalTableInterpretation(m_szInter);
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nNCurve = nPoints;
}

INT CSCOS2000DatabaseTMNumCalTablesRecordset::GetPoints() CONST
{
	return m_nNCurve;
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTMNumCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTMNumCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMNumCalTablesRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable)
{
	SetName(pDatabaseTMNumCalTable->GetName());
	SetDescription(pDatabaseTMNumCalTable->GetDescription());
	SetUnit(pDatabaseTMNumCalTable->GetUnit());
	SetAttributes(pDatabaseTMNumCalTable->GetAttributes());
	SetPoints(pDatabaseTMNumCalTable->GetPoints());
}

BOOL CSCOS2000DatabaseTMNumCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMNumCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckUnit();
		CheckAttributes();
		CheckPoints();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
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

BOOL CSCOS2000DatabaseTMNumCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTMNumCalTablesRecordset::CheckUnit(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTMNumCalTablesRecordset::CheckAttributes(BOOL bStatus)
{
	UINT  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableEngineeringValuesCoding((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALENGINEERINGVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTableRawValuesCoding(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALRAWVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTableRawValuesRadix(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALRAWVALUESRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTableInterpretation(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLE_ILLEGALINTERPRETATION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTMNumCalTablesRecordset::CheckPoints(BOOL bStatus)
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

void CSCOS2000DatabaseTMNumCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMNumCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_ENGFMT)), m_szEngFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_RAWFMT)), m_szRawFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_RADIX)), m_szRadix);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_UNIT)), m_szUnit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_NCURVE)), m_nNCurve);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAF_INTER)), m_szInter);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMNumCalTablePointsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMNumCalTablePointsRecordset::CSCOS2000DatabaseTMNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMNumCalTablePointsRecordset)
	m_szNumbr.Empty();
	m_szXVals.Empty();
	m_szYVals.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTMNumCalTablePointsRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTMNumCalTablePointsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::SetX(double fX)
{
	m_szXVals = (!isnan(fX)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), fX) : EMPTYSTRING;
}

double CSCOS2000DatabaseTMNumCalTablePointsRecordset::GetX() CONST
{
	return((GetDatabaseEngine()->CheckTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), m_szXVals)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), m_szXVals) : NAN);
}

VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::SetY(double fY)
{
	m_szYVals = (!isnan(fY)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_ENGCODING_UNSIGNEDINTEGER | TMCALTABLE_ENGCODING_SIGNEDINTEGER | TMCALTABLE_ENGCODING_FLOATINGPOINT), fY) : EMPTYSTRING;
}

double CSCOS2000DatabaseTMNumCalTablePointsRecordset::GetY() CONST
{
	return((GetDatabaseEngine()->CheckTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_ENGCODING_UNSIGNEDINTEGER | TMCALTABLE_ENGCODING_SIGNEDINTEGER | TMCALTABLE_ENGCODING_FLOATINGPOINT), m_szYVals)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_ENGCODING_UNSIGNEDINTEGER | TMCALTABLE_ENGCODING_SIGNEDINTEGER | TMCALTABLE_ENGCODING_FLOATINGPOINT), m_szYVals) : NAN);
}

VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMNumCalTablePointsRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CONST CDatabaseTMNumCalPoint *pDatabaseTMNumCalPoint)
{
	SetName(pDatabaseTMNumCalTable->GetName());
	SetAttributes(pDatabaseTMNumCalTable->GetAttributes());
	SetX(pDatabaseTMNumCalPoint->GetX());
	SetY(pDatabaseTMNumCalPoint->GetY());
}

BOOL CSCOS2000DatabaseTMNumCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMNumCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTMNumCalTable = GetDatabaseEngine()->GetTMNumCalTables()->GetAt(GetDatabaseEngine()->GetTMNumCalTables()->Find(GetName()))))
		{
			SetAttributes(pDatabaseTMNumCalTable->GetAttributes());
			CheckName();
			CheckPoint();
		}
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

BOOL CSCOS2000DatabaseTMNumCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEPOINT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_BINARY | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_HEXADECIMAL), (m_szXVals = ExtractText(m_szXVals))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEPOINT_ILLEGALRAWVALUE), (LPCTSTR)GetName(), (!m_szXVals.IsEmpty()) ? (LPCTSTR)m_szXVals : STRING(IDS_DATABASE_TABLE_CAP_POINT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(GetAttributes() & (TMCALTABLE_ENGCODING_UNSIGNEDINTEGER | TMCALTABLE_ENGCODING_SIGNEDINTEGER | TMCALTABLE_ENGCODING_FLOATINGPOINT), (m_szYVals = ExtractText(m_szYVals))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEPOINT_ILLEGALENGVALUE), (LPCTSTR)GetName(), (!m_szYVals.IsEmpty()) ? (LPCTSTR)m_szYVals : STRING(IDS_DATABASE_TABLE_CAP_POINT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

void CSCOS2000DatabaseTMNumCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CCSCOS2000DatabaseTMNumCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAP_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAP_XVALS)), m_szXVals);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CAP_YVALS)), m_szYVals);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset)
	m_szIdent.Empty();
	m_szDescr.Empty();
	m_szPOL1.Empty();
	m_szPOL2.Empty();
	m_szPOL3.Empty();
	m_szPOL4.Empty();
	m_szPOL5.Empty();
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::SetName(LPCTSTR pszName)
{
	m_szIdent = pszName;
}

CString CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::GetName() CONST
{
	return m_szIdent;
}

VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::SetCoefficients(double fA1, double fA2, double fA3, double fA4, double fA5)
{
	m_szPOL1 = (!isnan(fA1)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA1) : EMPTYSTRING;
	m_szPOL2 = (!isnan(fA2)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA2) : EMPTYSTRING;
	m_szPOL3 = (!isnan(fA3)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA3) : EMPTYSTRING;
	m_szPOL4 = (!isnan(fA4)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA4) : EMPTYSTRING;
	m_szPOL5 = (!isnan(fA5)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA5) : EMPTYSTRING;
}

BOOL CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::GetCoefficients(double &fA1, double &fA2, double &fA3, double &fA4, double &fA5) CONST
{
	fA1 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL1)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL1) : NAN;
	fA2 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL2)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL2) : NAN;
	fA3 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL3)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL3) : NAN;
	fA4 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL4)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL4) : NAN;
	fA5 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL5)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL5) : NAN;
	return !ExtractText(m_szPOL1).IsEmpty();
}

VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szIdent), pszError);
}
VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szIdent), pszWarning);
}
VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable)
{
	double  fA[5];

	for (SetName(pDatabaseTMNumCalTable->GetName()), SetDescription(pDatabaseTMNumCalTable->GetDescription()), fA[0] = fA[1] = fA[2] = fA[3] = fA[4] = 0.0; pDatabaseTMNumCalTable->GetPolynomialCurve(fA[0], fA[1], fA[2], fA[3], fA[4]); )
	{
		SetCoefficients(fA[0], fA[1], fA[2], fA[3], fA[4]);
		break;
	}
}

BOOL CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckCoefficients();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckCoefficients(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szIdent = ExtractText(m_szIdent))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALPOLYNOMIALCURVE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableDescription((m_szDescr = ExtractText(m_szDescr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALPOLYNOMIALCURVE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::CheckCoefficients(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue((m_szPOL1 = ExtractText(m_szPOL1))) || !GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL1))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALPOLYNOMIALCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL1.IsEmpty()) ? (LPCTSTR)m_szPOL1 : STRING(IDS_DATABASE_TABLE_MCF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL2 = ExtractText(m_szPOL2))) && !m_szPOL2.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALPOLYNOMIALCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL2.IsEmpty()) ? (LPCTSTR)m_szPOL2 : STRING(IDS_DATABASE_TABLE_MCF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL3 = ExtractText(m_szPOL3))) && !m_szPOL3.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALPOLYNOMIALCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL3.IsEmpty()) ? (LPCTSTR)m_szPOL3 : STRING(IDS_DATABASE_TABLE_MCF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL4 = ExtractText(m_szPOL4))) && !m_szPOL4.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALPOLYNOMIALCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL4.IsEmpty()) ? (LPCTSTR)m_szPOL4 : STRING(IDS_DATABASE_TABLE_MCF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL5 = ExtractText(m_szPOL5))) && !m_szPOL5.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALPOLYNOMIALCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL5.IsEmpty()) ? (LPCTSTR)m_szPOL5 : STRING(IDS_DATABASE_TABLE_MCF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

void CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MCF_IDENT)), m_szIdent);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MCF_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MCF_POL1)), m_szPOL1);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MCF_POL2)), m_szPOL2);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MCF_POL3)), m_szPOL3);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MCF_POL4)), m_szPOL4);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_MCF_POL5)), m_szPOL5);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset)
	m_szIdent.Empty();
	m_szDescr.Empty();
	m_szPOL1.Empty();
	m_szPOL2.Empty();
	m_szPOL3.Empty();
	m_szPOL4.Empty();
	m_szPOL5.Empty();
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::SetName(LPCTSTR pszName)
{
	m_szIdent = pszName;
}

CString CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::GetName() CONST
{
	return m_szIdent;
}

VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::SetCoefficients(double fA1, double fA2, double fA3, double fA4, double fA5)
{
	m_szPOL1 = (!isnan(fA1)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA1) : EMPTYSTRING;
	m_szPOL2 = (!isnan(fA2)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA2) : EMPTYSTRING;
	m_szPOL3 = (!isnan(fA3)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA3) : EMPTYSTRING;
	m_szPOL4 = (!isnan(fA4)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA4) : EMPTYSTRING;
	m_szPOL5 = (!isnan(fA5)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, fA5) : EMPTYSTRING;
}

BOOL CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::GetCoefficients(double &fA1, double &fA2, double &fA3, double &fA4, double &fA5) CONST
{
	fA1 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL1)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL1) : NAN;
	fA2 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL2)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL2) : NAN;
	fA3 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL3)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL3) : NAN;
	fA4 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL4)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL4) : NAN;
	fA5 = (GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL5)) ? GetDatabaseEngine()->TranslateTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL5) : NAN;
	return !ExtractText(m_szPOL1).IsEmpty();
}

VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szIdent), pszError);
}
VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szIdent), pszWarning);
}
VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable)
{
	double  fA[5];

	for (SetName(pDatabaseTMNumCalTable->GetName()), SetDescription(pDatabaseTMNumCalTable->GetDescription()), fA[0] = fA[1] = fA[2] = fA[3] = fA[4] = 0.0; pDatabaseTMNumCalTable->GetLogarithmicCurve(fA[0], fA[1], fA[2], fA[3], fA[4]); )
	{
		SetCoefficients(fA[0], fA[1], fA[2], fA[3], fA[4]);
		break;
	}
}

BOOL CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckCoefficients();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckCoefficients(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szIdent = ExtractText(m_szIdent))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALLOGARITHMICCURVE_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableDescription((m_szDescr = ExtractText(m_szDescr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALLOGARITHMICCURVE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::CheckCoefficients(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue((m_szPOL1 = ExtractText(m_szPOL1))) || !GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, m_szPOL1))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALLOGARITHMICCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL1.IsEmpty()) ? (LPCTSTR)m_szPOL1 : STRING(IDS_DATABASE_TABLE_LGF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL2 = ExtractText(m_szPOL2))) && !m_szPOL2.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALLOGARITHMICCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL2.IsEmpty()) ? (LPCTSTR)m_szPOL2 : STRING(IDS_DATABASE_TABLE_LGF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL3 = ExtractText(m_szPOL3))) && !m_szPOL3.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALLOGARITHMICCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL3.IsEmpty()) ? (LPCTSTR)m_szPOL3 : STRING(IDS_DATABASE_TABLE_LGF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL4 = ExtractText(m_szPOL4))) && !m_szPOL4.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALLOGARITHMICCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL4.IsEmpty()) ? (LPCTSTR)m_szPOL4 : STRING(IDS_DATABASE_TABLE_LGF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMNumCalTablePointValue(TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_DECIMAL, (m_szPOL5 = ExtractText(m_szPOL5))) && !m_szPOL5.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALLOGARITHMICCURVE_ILLEGALCOEFFICIENT), (LPCTSTR)GetName(), (!m_szPOL5.IsEmpty()) ? (LPCTSTR)m_szPOL5 : STRING(IDS_DATABASE_TABLE_LGF_COEFFICIENT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

void CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_LGF_IDENT)), m_szIdent);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_LGF_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_LGF_POL1)), m_szPOL1);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_LGF_POL2)), m_szPOL2);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_LGF_POL3)), m_szPOL3);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_LGF_POL4)), m_szPOL4);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_LGF_POL5)), m_szPOL5);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalTableAssociationsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMNumCalTableAssociationsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::CSCOS2000DatabaseTMNumCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMNumCalTableAssociationsRecordset)
	m_szPName.Empty();
	m_szRlChk.Empty();
	m_szSelect.Empty();
	m_nPos = 0;
	m_nValPar = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::SetTable(LPCTSTR pszTable)
{
	m_szSelect = pszTable;
}

CString CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::GetTable() CONST
{
	return m_szSelect;
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szPName = pszTag;
}

CString CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::GetParameter() CONST
{
	return m_szPName;
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::SetPosition(INT nPos)
{
	m_nPos = nPos;
}

INT CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::GetPosition() CONST
{
	return m_nPos;
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::SetValidityParameter(LPCTSTR pszParameter)
{
	m_szRlChk = pszParameter;
}

CString CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::GetValidityParameter() CONST
{
	return m_szRlChk;
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::SetValidityValue(INT nValue)
{
	m_nValPar = nValue;
}

INT CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::GetValidityValue() CONST
{
	return m_nValPar;
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSelect), pszError);
}
VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSelect), pszWarning);
}
VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter, INT nValidityValue, INT nPosition)
{
	m_szPName = pDatabaseTMParameter->GetTag();
	m_szSelect = pDatabaseTMNumCalTable->GetName();
	m_szRlChk = pszValidityParameter;
	m_nValPar = nValidityValue;
	m_nPos = nPosition;
}

BOOL CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTable();
		CheckParameter();
		CheckPosition();
		CheckValidityParameter();
		CheckValidityValue();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTable(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckValidityParameter(IsCollectingIssues());
		bCheck &= CheckValidityValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::CheckTable(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableName((m_szSelect = ExtractText(m_szSelect))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALNAME), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szPName = ExtractText(m_szPName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetTable(), (LPCTSTR)m_szPName); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::CheckPosition(BOOL bStatus)
{
	INT  nRange[2];
	CString  szMessage;

	if (!GetDatabaseEngine()->GetTMNumCalTablePositionRange(nRange[0], nRange[1]) || m_nPos < nRange[0] || m_nPos > nRange[1])
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALPOSITION), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableValidityParameter((m_szRlChk = ExtractText(m_szRlChk))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::CheckValidityValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumCalTableValidityValue(m_nValPar))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMCALTABLEASSOCIATION_ILLEGALVALIDITYVALUE), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMNumCalTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMNumCalTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_PNAME)), m_szPName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_POS)), m_nPos);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_RLCHK)), m_szRlChk);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_VALPAR)), m_nValPar);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_SELECT)), m_szSelect);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMTxtCalTablesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMTxtCalTablesRecordset::CSCOS2000DatabaseTMTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMTxtCalTablesRecordset)
	m_szNumbr.Empty();
	m_szDescr.Empty();
	m_szRawFmt.Empty();
	m_nNAlias = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTMTxtCalTablesRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTMTxtCalTablesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szRawFmt = GetDatabaseEngine()->TranslateTMTxtCalTableRawValuesCoding(nAttributes);
}

UINT CSCOS2000DatabaseTMTxtCalTablesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTMTxtCalTableRawValuesCoding(m_szRawFmt);
}

VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nNAlias = nPoints;
}

INT CSCOS2000DatabaseTMTxtCalTablesRecordset::GetPoints() CONST
{
	return m_nNAlias;
}

VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMTxtCalTablesRecordset::Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable)
{
	SetName(pDatabaseTMTxtCalTable->GetName());
	SetDescription(pDatabaseTMTxtCalTable->GetDescription());
	SetAttributes(pDatabaseTMTxtCalTable->GetAttributes());
	SetPoints(pDatabaseTMTxtCalTable->GetPoints());
}

BOOL CSCOS2000DatabaseTMTxtCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMTxtCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckAttributes();
		CheckPoints();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
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

BOOL CSCOS2000DatabaseTMTxtCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTMTxtCalTablesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableRawValuesCoding(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLE_ILLEGALRAWVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTablesRecordset::CheckPoints(BOOL bStatus)
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

void CSCOS2000DatabaseTMTxtCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMTxtCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_RAWFMT)), m_szRawFmt);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXF_NALIAS)), m_nNAlias);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMTxtCalTablePointsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMTxtCalTablePointsRecordset::CSCOS2000DatabaseTMTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMTxtCalTablePointsRecordset)
	m_szNumbr.Empty();
	m_szFrom.Empty();
	m_szTo.Empty();
	m_szAlTxt.Empty();
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTMTxtCalTablePointsRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTMTxtCalTablePointsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::SetX1(double fX1)
{
	m_szFrom = (!isnan(fX1)) ? GetDatabaseEngine()->TranslateTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), fX1) : EMPTYSTRING;
}

double CSCOS2000DatabaseTMTxtCalTablePointsRecordset::GetX1() CONST
{
	return((GetDatabaseEngine()->CheckTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), m_szFrom)) ? GetDatabaseEngine()->TranslateTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), m_szFrom) : NAN);
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::SetX2(double fX2)
{
	m_szTo = (!isnan(fX2)) ? GetDatabaseEngine()->TranslateTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), fX2) : EMPTYSTRING;
}

double CSCOS2000DatabaseTMTxtCalTablePointsRecordset::GetX2() CONST
{
	return((GetDatabaseEngine()->CheckTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), m_szTo)) ? GetDatabaseEngine()->TranslateTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), m_szTo) : NAN);
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::SetText(LPCTSTR pszText)
{
	m_szAlTxt = pszText;
}

CString CSCOS2000DatabaseTMTxtCalTablePointsRecordset::GetText() CONST
{
	return m_szAlTxt;
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMTxtCalTablePointsRecordset::Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CONST CDatabaseTMTxtCalPoint *pDatabaseTMTxtCalPoint)
{
	double  fX[2];
	CString  szY;

	for (SetName(pDatabaseTMTxtCalTable->GetName()), SetAttributes(pDatabaseTMTxtCalTable->GetAttributes()); pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szY); )
	{
		SetX1(fX[0]);
		SetX2(fX[1]);
		SetText(szY);
		break;
	}
}

BOOL CSCOS2000DatabaseTMTxtCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMTxtCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTMTxtCalTable = GetDatabaseEngine()->GetTMTxtCalTables()->GetAt(GetDatabaseEngine()->GetTMTxtCalTables()->Find(GetName()))))
		{
			SetAttributes(pDatabaseTMTxtCalTable->GetAttributes());
			CheckName();
			CheckPoint();
			CheckText();
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckPoint(IsCollectingIssues());
		bCheck &= CheckText(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), (m_szFrom = ExtractText(m_szFrom))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_ILLEGALRAWVALUE), (LPCTSTR)GetName(), (!m_szFrom.IsEmpty()) ? (LPCTSTR)m_szFrom : STRING(IDS_DATABASE_TABLE_TXP_POINT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTMTxtCalTablePointValue(GetAttributes() & (TMCALTABLE_RAWCODING_UNSIGNEDINTEGER | TMCALTABLE_RAWCODING_SIGNEDINTEGER | TMCALTABLE_RAWCODING_FLOATINGPOINT | TMCALTABLE_RAWRADIX_HEXADECIMAL | TMCALTABLE_RAWRADIX_DECIMAL | TMCALTABLE_RAWRADIX_OCTAL | TMCALTABLE_RAWRADIX_BINARY), (m_szTo = ExtractText(m_szTo))) || !GetDatabaseEngine()->CheckTMTxtCalTablePointInterval(GetX1(), GetX2()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_ILLEGALRAWVALUE), (LPCTSTR)GetName(), (!m_szTo.IsEmpty()) ? (LPCTSTR)m_szTo : STRING(IDS_DATABASE_TABLE_TXP_POINT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTMTxtCalTablePointsRecordset::CheckText(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTablePointText((m_szAlTxt = ExtractText(m_szAlTxt))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEPOINT_ILLEGALTEXTVALUE), (LPCTSTR)GetName(), (LPCTSTR)m_szAlTxt); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMTxtCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMTxtCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXP_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXP_FROM)), m_szFrom);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXP_TO)), m_szTo);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_TXP_ALTXT)), m_szAlTxt);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset)
	m_szPName.Empty();
	m_szRlChk.Empty();
	m_szSelect.Empty();
	m_nPos = 0;
	m_nValPar = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::SetTable(LPCTSTR pszTable)
{
	m_szSelect = pszTable;
}

CString CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::GetTable() CONST
{
	return m_szSelect;
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szPName = pszTag;
}

CString CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::GetParameter() CONST
{
	return m_szPName;
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::SetPosition(INT nPos)
{
	m_nPos = nPos;
}

INT CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::GetPosition() CONST
{
	return m_nPos;
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::SetValidityParameter(LPCTSTR pszParameter)
{
	m_szRlChk = pszParameter;
}

CString CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::GetValidityParameter() CONST
{
	return m_szRlChk;
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::SetValidityValue(INT nValue)
{
	m_nValPar = nValue;
}

INT CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::GetValidityValue() CONST
{
	return m_nValPar;
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szSelect), pszError);
}
VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szSelect), pszWarning);
}
VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter, INT nValidityValue, INT nPosition)
{
	m_szPName = pDatabaseTMParameter->GetTag();
	m_szSelect = pDatabaseTMTxtCalTable->GetName();
	m_szRlChk = pszValidityParameter;
	m_nValPar = nValidityValue;
	m_nPos = nPosition;
}

BOOL CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTable();
		CheckParameter();
		CheckPosition();
		CheckValidityParameter();
		CheckValidityValue();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTable(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckValidityParameter(IsCollectingIssues());
		bCheck &= CheckValidityValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::CheckTable(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableName((m_szSelect = ExtractText(m_szSelect))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALNAME), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMParameterTag((m_szPName = ExtractText(m_szPName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetTable(), (LPCTSTR)m_szPName); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::CheckPosition(BOOL bStatus)
{
	INT  nRange[2];
	CString  szMessage;

	if (!GetDatabaseEngine()->GetTMTxtCalTablePositionRange(nRange[0], nRange[1]) || m_nPos < nRange[0] || m_nPos > nRange[1])
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALPOSITION), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableValidityParameter((m_szRlChk = ExtractText(m_szRlChk))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALVALIDITYPARAMETER), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::CheckValidityValue(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtCalTableValidityValue(m_nValPar))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTCALTABLEASSOCIATION_ILLEGALVALIDITYVALUE), (LPCTSTR)GetTable(), (LPCTSTR)GetParameter()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_PNAME)), m_szPName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_POS)), m_nPos);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_RLCHK)), m_szRlChk);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_VALPAR)), m_nValPar);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CUR_SELECT)), m_szSelect);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMNumOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CSCOS2000DatabaseTMNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMNumOolTableLimitsRecordset)
	m_szName.Empty();
	m_szType.Empty();
	m_szLValu.Empty();
	m_szHValu.Empty();
	m_szRlChk.Empty();
	m_nValPar = 0;
	m_nPos = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetType(UINT nType)
{
	m_szType = GetDatabaseEngine()->TranslateTMNumOolTableLimitType(nType);
}

UINT CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateTMNumOolTableLimitType(m_szType);
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetPosition(INT nPos)
{
	m_nPos = nPos;
}

INT CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetPosition() CONST
{
	return m_nPos;
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetLowLimit(double fLowLimit)
{
	m_szLValu = (!isnan(fLowLimit)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), fLowLimit) : EMPTYSTRING;
}

double CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetLowLimit() CONST
{
	return((GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), m_szLValu)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), m_szLValu) : NAN);
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetHighLimit(double fHighLimit)
{
	m_szHValu = (!isnan(fHighLimit)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), fHighLimit) : EMPTYSTRING;
}

double CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetHighLimit() CONST
{
	return((GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), m_szHValu)) ? GetDatabaseEngine()->TranslateTMNumOolTableLimitValue(GetAttributes(), m_szHValu) : NAN);
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetValidityParameter(LPCTSTR pszParameter)
{
	m_szRlChk = pszParameter;
}

CString CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetValidityParameter() CONST
{
	return m_szRlChk;
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::SetValidityValue(INT nValue)
{
	m_nValPar = nValue;
}

INT CSCOS2000DatabaseTMNumOolTableLimitsRecordset::GetValidityValue() CONST
{
	return m_nValPar;
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMNumOolTableLimitsRecordset::Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CONST CDatabaseTMNumOolLimit *pDatabaseTMNumOolLimit, INT nPosition)
{
	UINT  nType;
	double  fRange[2];
	double  fDelta[2];

	for (SetName(pDatabaseTMNumOolTable->GetName()), SetType((nType = pDatabaseTMNumOolLimit->GetType())), SetValidityParameter(pDatabaseTMNumOolLimit->GetValidityParameter()), SetValidityValue((INT)pDatabaseTMNumOolLimit->GetValidityValue()), SetPosition(nPosition), SetAttributes(pDatabaseTMNumOolTable->GetAttributes()), fRange[0] = fRange[1] = 0.0; !pDatabaseTMNumOolLimit->GetRange(nType, fRange[0], fRange[1]) && (pDatabaseTMNumOolLimit->GetDelta(fDelta[0], TRUE) || pDatabaseTMNumOolLimit->GetDelta(fDelta[0], FALSE)); )
	{
		fRange[0] = (pDatabaseTMNumOolLimit->GetDelta(fDelta[0], TRUE)) ? fDelta[0] : NAN;
		fRange[1] = (pDatabaseTMNumOolLimit->GetDelta(fDelta[1], FALSE)) ? fDelta[1] : NAN;
		break;
	}
	SetLowLimit(fRange[0]);
	SetHighLimit(fRange[1]);
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTMNumOolTable = GetDatabaseEngine()->GetTMNumOolTables()->GetAt(GetDatabaseEngine()->GetTMNumOolTables()->Find((m_szName = ExtractText(m_szName))))))
		{
			SetAttributes(pDatabaseTMNumOolTable->GetAttributes());
			CheckName();
			CheckType();
			CheckPosition();
			CheckLowLimit();
			CheckHighLimit();
			CheckValidityParameter();
			CheckValidityValue();
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckLowLimit(IsCollectingIssues());
		bCheck &= CheckHighLimit(IsCollectingIssues());
		bCheck &= CheckValidityParameter(IsCollectingIssues());
		bCheck &= CheckValidityValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableName(GetName()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableLimitType(GetType()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALLIMITTYPE), (LPCTSTR)GetName(), (LPCTSTR)GetDatabaseEngine()->TranslateTMNumOolTableLimitType(GetType(), FALSE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CheckPosition(BOOL bStatus)
{
	INT  nRange[2];
	CString  szMessage;

	if (!GetDatabaseEngine()->GetTMNumOolTableLimitPositionRange(nRange[0], nRange[1]) || m_nPos < nRange[0] || m_nPos > nRange[1])
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALLIMITPOSITION), (LPCTSTR)GetName(), m_nPos); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CheckLowLimit(BOOL bStatus)
{
	CString  szMessage;

	if ((GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY && (GetType() != TMOOLLIMIT_TYPE_DELTA || !ExtractText(m_szLValu).IsEmpty() || (ExtractText(m_szLValu).IsEmpty() && ExtractText(m_szHValu).IsEmpty())) && !GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), (m_szLValu = ExtractText(m_szLValu)))) || (GetType() == TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !ExtractText(m_szLValu).IsEmpty()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (!m_szLValu.IsEmpty()) ? (LPCTSTR)m_szLValu : STRING(IDS_DATABASE_TABLE_OCP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CheckHighLimit(BOOL bStatus)
{
	CString  szMessage;

	if ((GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY && (GetType() != TMOOLLIMIT_TYPE_DELTA || !ExtractText(m_szHValu).IsEmpty() || (ExtractText(m_szLValu).IsEmpty() && ExtractText(m_szHValu).IsEmpty())) && !GetDatabaseEngine()->CheckTMNumOolTableLimitValue(GetAttributes(), (m_szHValu = ExtractText(m_szHValu)))) || (GetType() == TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !ExtractText(m_szHValu).IsEmpty()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (!m_szHValu.IsEmpty()) ? (LPCTSTR)m_szHValu : STRING(IDS_DATABASE_TABLE_OCP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if ((GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !GetDatabaseEngine()->CheckTMNumOolTableLimitValidityParameter((m_szRlChk = ExtractText(m_szRlChk)))) || (GetType() == TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !ExtractText(m_szRlChk).IsEmpty()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALLIMITVALIDITYPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)m_szRlChk); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableLimitsRecordset::CheckValidityValue(BOOL bStatus)
{
	CString  szMessage;

	if (GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !GetDatabaseEngine()->CheckTMNumOolTableLimitValidityValue(m_nValPar))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLELIMIT_ILLEGALLIMITVALIDITYVALUE), (LPCTSTR)GetName(), m_nValPar); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMNumOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMNumOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_POS)), m_nPos);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_LVALU)), m_szLValu);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_HVALU)), m_szHValu);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_RLCHK)), m_szRlChk);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_VALPAR)), m_nValPar);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumOolTableAssociationsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMNumOolTableAssociationsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::CSCOS2000DatabaseTMNumOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMNumOolTableAssociationsRecordset)
	m_szName.Empty();
	m_szInter.Empty();
	m_szCodin.Empty();
	m_nNBChck = 0;
	m_nNBOOLs = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::SetTable(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::GetTable() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::SetAttributes(UINT nAttributes)
{
	m_szInter = GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(nAttributes);
	m_szCodin = GetDatabaseEngine()->TranslateTMNumOolTableCoding(nAttributes);
}

UINT CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(m_szInter) | GetDatabaseEngine()->TranslateTMNumOolTableCoding(GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(m_szInter), m_szCodin);
}

VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::SetOOLChecks(INT nCount)
{
	m_nNBChck = nCount;
}

INT CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::GetOOLChecks() CONST
{
	return m_nNBChck;
}

VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::SetLimitCount(INT nCount)
{
	m_nNBOOLs = nCount;
}

INT CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::GetLimitCount() CONST
{
	return m_nNBOOLs;
}

VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable)
{
	m_szName = pDatabaseTMNumOolTable->GetName();
	m_szInter = GetDatabaseEngine()->TranslateTMNumOolTableInterpretation(pDatabaseTMNumOolTable->GetAttributes());
	m_szCodin = GetDatabaseEngine()->TranslateTMNumOolTableCoding(pDatabaseTMNumOolTable->GetAttributes());
	m_nNBOOLs = (INT)pDatabaseTMNumOolTable->GetCount();
	m_nNBChck = pDatabaseTMNumOolTable->GetChecks();
}

BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::IsEmpty() CONST
{
	return((!GetOOLChecks() && (GetAttributes() & (TMOOLTABLE_CODING_UNSIGNEDINTEGER | TMOOLTABLE_CODING_SIGNEDINTEGER | TMOOLTABLE_CODING_FLOATINGPOINT | TMOOLTABLE_CODING_TEXTSTRING)) == 0 && !GetLimitCount()) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTable();
		CheckOOLChecks();
		CheckLimitCount();
		CheckInterpretation();
		CheckCoding();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTable(IsCollectingIssues());
		bCheck &= CheckOOLChecks(IsCollectingIssues());
		bCheck &= CheckLimitCount(IsCollectingIssues());
		bCheck &= CheckInterpretation(IsCollectingIssues());
		bCheck &= CheckCoding(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::CheckTable(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::CheckOOLChecks(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableCheckCount(m_nNBChck))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALCHECKSNUMBER), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::CheckLimitCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableLimitCount(m_nNBOOLs))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALLIMITSCOUNT), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::CheckInterpretation(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableInterpretation(GetDatabaseEngine()->TranslateTMNumOolTableInterpretation((m_szInter = ExtractText(m_szInter)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALLIMITVALUESINTERPRETATION), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::CheckCoding(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMNumOolTableCoding(GetAttributes(), GetDatabaseEngine()->TranslateTMNumOolTableCoding(GetAttributes(), m_szCodin = ExtractText(m_szCodin))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMNUMOOLTABLEASSOCIATION_ILLEGALLIMITVALUESCODING), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMNumOolTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMNumOolTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NBCHCK)), m_nNBChck);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NBOOL)), m_nNBOOLs);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_CODIN)), m_szCodin);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMTxtOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CSCOS2000DatabaseTMTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMTxtOolTableLimitsRecordset)
	m_szName.Empty();
	m_szType.Empty();
	m_szLValu.Empty();
	m_szHValu.Empty();
	m_szRlChk.Empty();
	m_nValPar = 0;
	m_nPos = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetType(UINT nType)
{
	m_szType = GetDatabaseEngine()->TranslateTMTxtOolTableLimitType(nType);
}

UINT CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateTMTxtOolTableLimitType(m_szType);
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetPosition(INT nPos)
{
	m_nPos = nPos;
}

INT CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetPosition() CONST
{
	return m_nPos;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetLowLimit(LPCTSTR pszLowLimit)
{
	m_szLValu = pszLowLimit;
}

CString CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetLowLimit() CONST
{
	return m_szLValu;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetHighLimit(LPCTSTR pszHighLimit)
{
	m_szHValu = pszHighLimit;
}

CString CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetHighLimit() CONST
{
	return m_szHValu;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetValidityParameter(LPCTSTR pszParameter)
{
	m_szRlChk = pszParameter;
}

CString CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetValidityParameter() CONST
{
	return m_szRlChk;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::SetValidityValue(INT nValue)
{
	m_nValPar = nValue;
}

INT CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::GetValidityValue() CONST
{
	return m_nValPar;
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CONST CDatabaseTMTxtOolLimit *pDatabaseTMTxtOolLimit, INT nPosition)
{
	UINT  nType;
	double  fLimit;
	CString  szLimit[2];
	CStringTools  cStringTools;

	for (SetName(pDatabaseTMTxtOolTable->GetName()), SetType((nType = pDatabaseTMTxtOolLimit->GetType())), SetValidityParameter(pDatabaseTMTxtOolLimit->GetValidityParameter()), SetValidityValue((INT)pDatabaseTMTxtOolLimit->GetValidityValue()), SetPosition(nPosition), SetAttributes(pDatabaseTMTxtOolTable->GetAttributes()), fLimit = 0.0; !pDatabaseTMTxtOolLimit->GetLimit(szLimit[0]) && pDatabaseTMTxtOolLimit->GetLimit(fLimit); )
	{
		szLimit[0] = (!isnan(fLimit)) ? GetDatabaseEngine()->TranslateTMTxtOolTableLimitValue(GetAttributes(), fLimit) : EMPTYSTRING;
		szLimit[1].Empty();
		break;
	}
	SetLowLimit((nType != TMOOLLIMIT_TYPE_STATUSCONSISTENCY) ? szLimit[0] : EMPTYSTRING);
	SetHighLimit((nType != TMOOLLIMIT_TYPE_STATUSCONSISTENCY) ? szLimit[1] : EMPTYSTRING);
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTMTxtOolTable = GetDatabaseEngine()->GetTMTxtOolTables()->GetAt(GetDatabaseEngine()->GetTMTxtOolTables()->Find((m_szName = ExtractText(m_szName))))))
		{
			SetAttributes(pDatabaseTMTxtOolTable->GetAttributes());
			CheckName();
			CheckType();
			CheckPosition();
			CheckLowLimit();
			CheckHighLimit();
			CheckValidityParameter();
			CheckValidityValue();
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckLowLimit(IsCollectingIssues());
		bCheck &= CheckHighLimit(IsCollectingIssues());
		bCheck &= CheckValidityParameter(IsCollectingIssues());
		bCheck &= CheckValidityValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableName(GetName()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableLimitType(GetType()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALLIMITTYPE), (LPCTSTR)GetName(), (LPCTSTR)GetDatabaseEngine()->TranslateTMTxtOolTableLimitType(GetType(), FALSE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CheckPosition(BOOL bStatus)
{
	INT  nRange[2];
	CString  szMessage;

	if (!GetDatabaseEngine()->GetTMTxtOolTableLimitPositionRange(nRange[0], nRange[1]) || m_nPos < nRange[0] || m_nPos > nRange[1])
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALLIMITPOSITION), (LPCTSTR)GetName(), m_nPos); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CheckLowLimit(BOOL bStatus)
{
	CString  szMessage;

	if ((GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !GetDatabaseEngine()->CheckTMTxtOolTableLimitValue(GetAttributes(), (m_szLValu = ExtractText(m_szLValu)))) || (GetType() == TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !ExtractText(m_szLValu).IsEmpty()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (!m_szLValu.IsEmpty()) ? (LPCTSTR)m_szLValu : STRING(IDS_DATABASE_TABLE_FXP_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CheckHighLimit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableLimitValue(GetAttributes(), (m_szHValu = ExtractText(m_szHValu))) && !m_szHValu.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (LPCTSTR)m_szHValu); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CheckValidityParameter(BOOL bStatus)
{
	CString  szMessage;

	if ((GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !GetDatabaseEngine()->CheckTMTxtOolTableLimitValidityParameter((m_szRlChk = ExtractText(m_szRlChk)))) || (GetType() == TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !ExtractText(m_szRlChk).IsEmpty()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALLIMITVALIDITYPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)m_szRlChk); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::CheckValidityValue(BOOL bStatus)
{
	CString  szMessage;

	if (GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  !GetDatabaseEngine()->CheckTMTxtOolTableLimitValidityValue(m_nValPar))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLELIMIT_ILLEGALLIMITVALIDITYVALUE), (LPCTSTR)GetName(), m_nValPar); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMTxtOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMTxtOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_POS)), m_nPos);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_LVALU)), m_szLValu);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_HVALU)), m_szHValu);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_RLCHK)), m_szRlChk);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCP_VALPAR)), m_nValPar);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset)
	m_szName.Empty();
	m_szInter.Empty();
	m_szCodin.Empty();
	m_nNBChck = 0;
	m_nNBOOLs = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::SetTable(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::GetTable() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::SetAttributes(UINT nAttributes)
{
	m_szInter = GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(nAttributes);
	m_szCodin = GetDatabaseEngine()->TranslateTMTxtOolTableCoding(nAttributes);
}

UINT CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(m_szInter) | GetDatabaseEngine()->TranslateTMTxtOolTableCoding(GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(m_szInter), m_szCodin);
}

VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::SetOOLChecks(INT nCount)
{
	m_nNBChck = nCount;
}

INT CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::GetOOLChecks() CONST
{
	return m_nNBChck;
}

VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::SetLimitCount(INT nCount)
{
	m_nNBOOLs = nCount;
}

INT CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::GetLimitCount() CONST
{
	return m_nNBOOLs;
}

VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable)
{
	m_szName = pDatabaseTMTxtOolTable->GetName();
	m_szInter = GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation(pDatabaseTMTxtOolTable->GetAttributes());
	m_szCodin = GetDatabaseEngine()->TranslateTMTxtOolTableCoding(pDatabaseTMTxtOolTable->GetAttributes());
	m_nNBOOLs = (INT)pDatabaseTMTxtOolTable->GetCount();
	m_nNBChck = pDatabaseTMTxtOolTable->GetChecks();
}

BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::IsEmpty() CONST
{
	return((!GetOOLChecks() && (GetAttributes() & (TMOOLTABLE_CODING_UNSIGNEDINTEGER | TMOOLTABLE_CODING_SIGNEDINTEGER | TMOOLTABLE_CODING_FLOATINGPOINT | TMOOLTABLE_CODING_TEXTSTRING)) == 0 && !GetLimitCount()) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTable();
		CheckOOLChecks();
		CheckLimitCount();
		CheckInterpretation();
		CheckCoding();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTable(IsCollectingIssues());
		bCheck &= CheckOOLChecks(IsCollectingIssues());
		bCheck &= CheckLimitCount(IsCollectingIssues());
		bCheck &= CheckInterpretation(IsCollectingIssues());
		bCheck &= CheckCoding(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::CheckTable(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALPARAMETER), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::CheckOOLChecks(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableCheckCount(m_nNBChck))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALCHECKSNUMBER), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::CheckLimitCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableLimitCount(m_nNBOOLs))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALLIMITSCOUNT), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::CheckInterpretation(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableInterpretation(GetDatabaseEngine()->TranslateTMTxtOolTableInterpretation((m_szInter = ExtractText(m_szInter)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALLIMITVALUESINTERPRETATION), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::CheckCoding(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTMTxtOolTableCoding(GetAttributes(), GetDatabaseEngine()->TranslateTMTxtOolTableCoding(GetAttributes(), (m_szCodin = ExtractText(m_szCodin)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TMTXTOOLTABLEASSOCIATION_ILLEGALLIMITVALUESCODING), (LPCTSTR)GetTable()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NBCHCK)), m_nNBChck);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_NBOOL)), m_nNBOOLs);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_OCF_CODIN)), m_szCodin);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParametersRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCParametersRecordset::CSCOS2000DatabaseTCParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCParametersRecordset)
	m_szPName.Empty();
	m_szDescr.Empty();
	m_szDispFmt.Empty();
	m_szRadix.Empty();
	m_szUnit.Empty();
	m_szCateg.Empty();
	m_szPrfRef.Empty();
	m_szCcaRef.Empty();
	m_szPafRef.Empty();
	m_szInter.Empty();
	m_szDefVal.Empty();
	m_szCorr.Empty();
	m_nPTC = 0;
	m_nPFC = 0;
	m_nOBTID = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szPName = pszTag;
}

CString CSCOS2000DatabaseTCParametersRecordset::GetTag() CONST
{
	return m_szPName;
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCParametersRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CSCOS2000DatabaseTCParametersRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetTypeCode(UINT nPTC)
{
	m_nPTC = nPTC;
}

UINT CSCOS2000DatabaseTCParametersRecordset::GetTypeCode() CONST
{
	return m_nPTC;
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetFormatCode(UINT nPFC)
{
	m_nPFC = nPFC;
}

UINT CSCOS2000DatabaseTCParametersRecordset::GetFormatCode() CONST
{
	return m_nPFC;
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szRadix = GetDatabaseEngine()->TranslateTCParameterRadix(nAttributes);
	m_szCateg = GetDatabaseEngine()->TranslateTCParameterCategory(nAttributes);
	m_szInter = GetDatabaseEngine()->TranslateTCParameterConstValueType(nAttributes);
	m_szCorr = GetDatabaseEngine()->TranslateTCParameterTimeCorrelationFlag(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCParametersRecordset::GetAttributes(INT &nWidth) CONST
{
	ULONGLONG  nAttributes;

	return((GetDatabaseEngine()->TranslateParameterTypeCode(m_nPTC, m_nPFC, TRUE, nAttributes, nWidth)) ? (GetAttributes() | (nAttributes & ~(TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL))) : GetAttributes());
}
ULONGLONG CSCOS2000DatabaseTCParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCParameterRadix(m_szRadix) | GetDatabaseEngine()->TranslateTCParameterCategory(m_szCateg) | GetDatabaseEngine()->TranslateTCParameterConstValueType(m_szInter) | GetDatabaseEngine()->TranslateTCParameterTimeCorrelationFlag(m_szCorr);
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetDisplayFormat(ULONGLONG nFormat)
{
	m_szDispFmt = GetDatabaseEngine()->TranslateTCParameterDisplayFormat(nFormat);
}

ULONGLONG CSCOS2000DatabaseTCParametersRecordset::GetDisplayFormat() CONST
{
	return GetDatabaseEngine()->TranslateTCParameterDisplayFormat(m_szDispFmt);
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetCalibrationTable(LPCTSTR pszTable, ULONGLONG nAttributes)
{
	m_szCcaRef = (nAttributes & TCPARAMETER_CALIBRATION_NUMERICAL) ? pszTable : EMPTYSTRING;
	m_szPafRef = (nAttributes & TCPARAMETER_CALIBRATION_STATUS) ? pszTable : EMPTYSTRING;
}

CString CSCOS2000DatabaseTCParametersRecordset::GetCalibrationTable(ULONGLONG nAttributes) CONST
{
	return((nAttributes & TCPARAMETER_CALIBRATION_NUMERICAL) ? m_szCcaRef : ((nAttributes & TCPARAMETER_CALIBRATION_STATUS) ? m_szPafRef : EMPTYSTRING));
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetOutOfLimitTable(LPCTSTR pszTable)
{
	m_szPrfRef = pszTable;
}

CString CSCOS2000DatabaseTCParametersRecordset::GetOutOfLimitTable() CONST
{
	return m_szPrfRef;
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szDefVal = pszConstValue;
}

CString CSCOS2000DatabaseTCParametersRecordset::GetConstValue() CONST
{
	return m_szDefVal;
}

VOID CSCOS2000DatabaseTCParametersRecordset::SetOnBoardTimerID(INT nOBTID)
{
	m_nOBTID = nOBTID;
}

INT CSCOS2000DatabaseTCParametersRecordset::GetOnBoardTimerID() CONST
{
	return m_nOBTID;
}

VOID CSCOS2000DatabaseTCParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szPName), pszError);
}
VOID CSCOS2000DatabaseTCParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseTCParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szPName), pszWarning);
}
VOID CSCOS2000DatabaseTCParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseTCParametersRecordset::Translate(CONST CDatabaseTCParameter *pDatabaseTCParameter)
{
	SetTag(pDatabaseTCParameter->GetTag());
	SetDescription(pDatabaseTCParameter->GetDescription());
	SetUnit(pDatabaseTCParameter->GetUnit());
	SetTypeCode(pDatabaseTCParameter->GetTypeCode());
	SetFormatCode(pDatabaseTCParameter->GetFormatCode());
	SetAttributes(pDatabaseTCParameter->GetAttributes());
	SetDisplayFormat(pDatabaseTCParameter->GetDisplayFormat());
	SetCalibrationTable(pDatabaseTCParameter->GetCalTable(), pDatabaseTCParameter->GetAttributes());
	SetOutOfLimitTable(pDatabaseTCParameter->GetOolTable());
	SetConstValue(pDatabaseTCParameter->GetConstValueAsText());
	SetOnBoardTimerID(pDatabaseTCParameter->GetOnBoardTimerID());
}

BOOL CSCOS2000DatabaseTCParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTag();
		CheckDescription();
		CheckUnit();
		CheckTypeCode();
		CheckFormatCode();
		CheckAttributes();
		CheckDisplayFormat();
		CheckCalibrationTable();
		CheckOutOfLimitTable();
		CheckConstValue();
		CheckOnBoardTimerID();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTag(IsCollectingIssues());
		bCheck &= CheckTypeCode(IsCollectingIssues());
		bCheck &= CheckFormatCode(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckDisplayFormat(IsCollectingIssues());
		bCheck &= CheckCalibrationTable(IsCollectingIssues());
		bCheck &= CheckConstValue(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterTag((m_szPName = ExtractText(m_szPName))))
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

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckUnit(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckTypeCode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterTypeCode(m_nPTC))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALTYPECODE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckFormatCode(BOOL bStatus)
{
	CString  szMessage;

	if (GetDatabaseEngine()->CheckTCParameterTypeCode(m_nPTC) && !GetDatabaseEngine()->CheckTCParameterFormatCode(m_nPTC, m_nPFC))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALFORMATCODE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckAttributes(BOOL bStatus)
{
	INT  nWidth;
	ULONGLONG  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterRadix((nAttributes = GetAttributes(nWidth)), GetDatabaseEngine()->TranslateTCParameterRadix((m_szRadix = ExtractText(m_szRadix)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALRADIX), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCParameterCategory(GetDatabaseEngine()->TranslateTCParameterCategory((m_szCateg = ExtractText(m_szCateg)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALCATEGORY), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCParameterConstValueType(GetDatabaseEngine()->TranslateTCParameterConstValueType((m_szInter = ExtractText(m_szInter))), m_szDefVal))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALVALUEINTERPRETATION), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCParameterTimeCorrelationFlag(GetDatabaseEngine()->TranslateTCParameterTimeCorrelationFlag((m_szCorr = ExtractText(m_szCorr)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALTIMECORRELATIONFLAG), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckDisplayFormat(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterDisplayFormat(GetAttributes(nWidth), GetDatabaseEngine()->TranslateTCParameterDisplayFormat((m_szDispFmt = ExtractText(m_szDispFmt)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALDISPLAYFORMAT), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckCalibrationTable(BOOL bStatus)
{
	INT  nWidth;
	ULONGLONG  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterCalTable((nAttributes = GetAttributes(nWidth)) & TCPARAMETER_CALIBRATION_NUMERICAL, (m_szCcaRef = ExtractText(m_szCcaRef))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALCALIBRATIONTABLE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCParameterCalTable(nAttributes & TCPARAMETER_CALIBRATION_STATUS, (m_szPafRef = ExtractText(m_szPafRef))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALCALIBRATIONTABLE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckOutOfLimitTable(BOOL bStatus)
{
	INT  nWidth;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterOolTable(GetAttributes(nWidth), (m_szPrfRef = ExtractText(m_szPrfRef))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALOUTOFLIMITTABLE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckConstValue(BOOL bStatus)
{
	INT  nWidth;
	ULONGLONG  nAttributes;
	CString  szMessage;

	if (((((nAttributes = GetAttributes(nWidth)) & TCPARAMETER_VTYPE_RAW) && (((nAttributes & (TCPARAMETER_VTYPE_COMMANDID | TCPARAMETER_VTYPE_PARAMETERID | TCPARAMETER_CODING_TIME)) == 0 && !GetDatabaseEngine()->CheckTCParameterConstValue((nAttributes & TCPARAMETER_VTYPE_CALIBRATED) ? (GetDisplayFormat() | (nAttributes & (TCPARAMETER_RADIX_BINARY | TCPARAMETER_RADIX_OCTAL | TCPARAMETER_RADIX_DECIMAL | TCPARAMETER_RADIX_HEXADECIMAL))) : nAttributes, (m_szDefVal = ExtractText(m_szDefVal)))) || ((nAttributes & (TCPARAMETER_VTYPE_COMMANDID | TCPARAMETER_VTYPE_PARAMETERID)) == 0 && (nAttributes & TCPARAMETER_CODING_TIME) && !GetDatabaseEngine()->CheckTCParameterConstTime(nAttributes, (m_szDefVal = ExtractText(m_szDefVal))))))) || ((nAttributes & (TCPARAMETER_VTYPE_RAW | TCPARAMETER_VTYPE_CALIBRATED)) == 0 && lstrlen((m_szDefVal = ExtractText(m_szDefVal))) > 0))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALCONSTVALUE), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParametersRecordset::CheckOnBoardTimerID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterOnBoardTimerID(m_nOBTID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETER_ILLEGALONBOARDTIMERID), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_PNAME)), m_szPName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_DESCR)), m_szDescr);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_PTC)), m_nPTC);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_PFC)), m_nPFC);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_DISPFMT)), m_szDispFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_RADIX)), m_szRadix);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_UNIT)), m_szUnit);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_CATEG)), m_szCateg);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_PRFREF)), m_szPrfRef);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_CCAREF)), m_szCcaRef);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_PAFREF)), m_szPafRef);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_DEFVAL)), m_szDefVal);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_CORR)), m_szCorr);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CPC_OBTID)), m_nOBTID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCNumCalTablesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCNumCalTablesRecordset::CSCOS2000DatabaseTCNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCNumCalTablesRecordset)
	m_szNumbr.Empty();
	m_szDescr.Empty();
	m_szEngFmt.Empty();
	m_szRawFmt.Empty();
	m_szRadix.Empty();
	m_szUnit.Empty();
	m_nNCurve = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCNumCalTablesRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCNumCalTablesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CSCOS2000DatabaseTCNumCalTablesRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szEngFmt = GetDatabaseEngine()->TranslateTCNumCalTableEngineeringValuesCoding(nAttributes);
	m_szRawFmt = GetDatabaseEngine()->TranslateTCNumCalTableRawValuesCoding(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCNumCalTableRawValuesRadix(nAttributes);
}

UINT CSCOS2000DatabaseTCNumCalTablesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCNumCalTableEngineeringValuesCoding(m_szEngFmt) | GetDatabaseEngine()->TranslateTCNumCalTableRawValuesCoding(m_szRawFmt) | GetDatabaseEngine()->TranslateTCNumCalTableRawValuesRadix(m_szRadix);
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nNCurve = nPoints;
}

INT CSCOS2000DatabaseTCNumCalTablesRecordset::GetPoints() CONST
{
	return m_nNCurve;
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCNumCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCNumCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTCNumCalTablesRecordset::Translate(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable)
{
	SetName(pDatabaseTCNumCalTable->GetName());
	SetDescription(pDatabaseTCNumCalTable->GetDescription());
	SetUnit(pDatabaseTCNumCalTable->GetUnit());
	SetAttributes(pDatabaseTCNumCalTable->GetAttributes());
	SetPoints(pDatabaseTCNumCalTable->GetPoints());
}

BOOL CSCOS2000DatabaseTCNumCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCNumCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckUnit();
		CheckAttributes();
		CheckPoints();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCNumCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
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

BOOL CSCOS2000DatabaseTCNumCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTCNumCalTablesRecordset::CheckUnit(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCNumCalTablesRecordset::CheckAttributes(BOOL bStatus)
{
	UINT  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableEngineeringValuesCoding((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALENGINEERINGVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumCalTableRawValuesCoding(nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALRAWVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumCalTableRawValuesRadix(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLE_ILLEGALRAWVALUESRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCNumCalTablesRecordset::CheckPoints(BOOL bStatus)
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

void CSCOS2000DatabaseTCNumCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCNumCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCA_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCA_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCA_ENGFMT)), m_szEngFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCA_RAWFMT)), m_szRawFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCA_RADIX)), m_szRadix);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCA_UNIT)), m_szUnit);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCA_NCURVE)), m_nNCurve);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCNumCalTablePointsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCNumCalTablePointsRecordset::CSCOS2000DatabaseTCNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCNumCalTablePointsRecordset)
	m_szNumbr.Empty();
	m_szXVals.Empty();
	m_szYVals.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCNumCalTablePointsRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTCNumCalTablePointsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::SetX(double fX)
{
	m_szXVals = (!isnan(fX)) ? GetDatabaseEngine()->TranslateTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_HEXADECIMAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_BINARY), fX) : EMPTYSTRING;
}

double CSCOS2000DatabaseTCNumCalTablePointsRecordset::GetX() CONST
{
	return((GetDatabaseEngine()->CheckTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_HEXADECIMAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_BINARY), m_szXVals)) ? GetDatabaseEngine()->TranslateTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_HEXADECIMAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_BINARY), m_szXVals) : NAN);
}

VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::SetY(double fY)
{
	m_szYVals = (!isnan(fY)) ? GetDatabaseEngine()->TranslateTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_ENGCODING_UNSIGNEDINTEGER | TCCALTABLE_ENGCODING_SIGNEDINTEGER | TCCALTABLE_ENGCODING_FLOATINGPOINT), fY) : EMPTYSTRING;
}

double CSCOS2000DatabaseTCNumCalTablePointsRecordset::GetY() CONST
{
	return((GetDatabaseEngine()->CheckTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_ENGCODING_UNSIGNEDINTEGER | TCCALTABLE_ENGCODING_SIGNEDINTEGER | TCCALTABLE_ENGCODING_FLOATINGPOINT), m_szYVals)) ? GetDatabaseEngine()->TranslateTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_ENGCODING_UNSIGNEDINTEGER | TCCALTABLE_ENGCODING_SIGNEDINTEGER | TCCALTABLE_ENGCODING_FLOATINGPOINT), m_szYVals) : NAN);
}

VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTCNumCalTablePointsRecordset::Translate(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, CONST CDatabaseTCNumCalPoint *pDatabaseTCNumCalPoint)
{
	SetName(pDatabaseTCNumCalTable->GetName());
	SetAttributes(pDatabaseTCNumCalTable->GetAttributes());
	SetX(pDatabaseTCNumCalPoint->GetX());
	SetY(pDatabaseTCNumCalPoint->GetY());
}

BOOL CSCOS2000DatabaseTCNumCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCNumCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTCNumCalTable = GetDatabaseEngine()->GetTCNumCalTables()->GetAt(GetDatabaseEngine()->GetTCNumCalTables()->Find(GetName()))))
		{
			SetAttributes(pDatabaseTCNumCalTable->GetAttributes());
			CheckName();
			CheckPoint();
		}
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

BOOL CSCOS2000DatabaseTCNumCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLEPOINT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCNumCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_BINARY | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_HEXADECIMAL), (m_szXVals = ExtractText(m_szXVals))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLEPOINT_ILLEGALRAWVALUE), (LPCTSTR)GetName(), (!m_szXVals.IsEmpty()) ? (LPCTSTR)m_szXVals : STRING(IDS_DATABASE_TABLE_CCS_POINT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumCalTablePointValue(GetAttributes() & (TCCALTABLE_ENGCODING_UNSIGNEDINTEGER | TCCALTABLE_ENGCODING_SIGNEDINTEGER | TCCALTABLE_ENGCODING_FLOATINGPOINT), (m_szYVals = ExtractText(m_szYVals))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMCALTABLEPOINT_ILLEGALENGVALUE), (LPCTSTR)GetName(), (!m_szYVals.IsEmpty()) ? (LPCTSTR)m_szYVals : STRING(IDS_DATABASE_TABLE_CCS_POINT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

void CSCOS2000DatabaseTCNumCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CCSCOS2000DatabaseTCNumCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCS_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCS_XVALS)), m_szXVals);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CCS_YVALS)), m_szYVals);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtCalTablesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCTxtCalTablesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCTxtCalTablesRecordset::CSCOS2000DatabaseTCTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCTxtCalTablesRecordset)
	m_szNumbr.Empty();
	m_szDescr.Empty();
	m_szRawFmt.Empty();
	m_nNAlias = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCTxtCalTablesRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCTxtCalTablesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szRawFmt = GetDatabaseEngine()->TranslateTCTxtCalTableRawValuesCoding(nAttributes);
}

UINT CSCOS2000DatabaseTCTxtCalTablesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCTxtCalTableRawValuesCoding(m_szRawFmt);
}

VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::SetPoints(INT nPoints)
{
	m_nNAlias = nPoints;
}

INT CSCOS2000DatabaseTCTxtCalTablesRecordset::GetPoints() CONST
{
	return m_nNAlias;
}

VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTCTxtCalTablesRecordset::Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable)
{
	SetName(pDatabaseTCTxtCalTable->GetName());
	SetDescription(pDatabaseTCTxtCalTable->GetDescription());
	SetAttributes(pDatabaseTCTxtCalTable->GetAttributes());
	SetPoints(pDatabaseTCTxtCalTable->GetPoints());
}

BOOL CSCOS2000DatabaseTCTxtCalTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCTxtCalTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		CheckAttributes();
		CheckPoints();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtCalTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
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

BOOL CSCOS2000DatabaseTCTxtCalTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTableDescription((m_szDescr = ExtractText(m_szDescr))))
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

BOOL CSCOS2000DatabaseTCTxtCalTablesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTableRawValuesCoding(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLE_ILLEGALRAWVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtCalTablesRecordset::CheckPoints(BOOL bStatus)
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

void CSCOS2000DatabaseTCTxtCalTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCTxtCalTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PAF_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PAF_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PAF_RAWFMT)), m_szRawFmt);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PAF_NALIAS)), m_nNAlias);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtCalTablePointsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCTxtCalTablePointsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCTxtCalTablePointsRecordset::CSCOS2000DatabaseTCTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCTxtCalTablePointsRecordset)
	m_szNumbr.Empty();
	m_szAlTxt.Empty();
	m_szAlVal.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCTxtCalTablePointsRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTCTxtCalTablePointsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::SetX(double fX)
{
	m_szAlVal = (!isnan(fX)) ? GetDatabaseEngine()->TranslateTCTxtCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_HEXADECIMAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_BINARY), fX) : EMPTYSTRING;
}

double CSCOS2000DatabaseTCTxtCalTablePointsRecordset::GetX() CONST
{
	return((GetDatabaseEngine()->CheckTCTxtCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_HEXADECIMAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_BINARY), m_szAlVal)) ? GetDatabaseEngine()->TranslateTCTxtCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_HEXADECIMAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_BINARY), m_szAlVal) : NAN);
}

VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::SetText(LPCTSTR pszText)
{
	m_szAlTxt = pszText;
}

CString CSCOS2000DatabaseTCTxtCalTablePointsRecordset::GetText() CONST
{
	return m_szAlTxt;
}

VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszError);
}

VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTCTxtCalTablePointsRecordset::Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, CONST CDatabaseTCTxtCalPoint *pDatabaseTCTxtCalPoint)
{
	double  fX[2];
	CString  szY;

	for (SetName(pDatabaseTCTxtCalTable->GetName()), SetAttributes(pDatabaseTCTxtCalTable->GetAttributes()); pDatabaseTCTxtCalPoint->GetRange(fX[0], fX[1], szY); )
	{
		SetX(fX[0]);
		SetText(szY);
		break;
	}
}

BOOL CSCOS2000DatabaseTCTxtCalTablePointsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCTxtCalTablePointsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	if (nOperation == CFieldExchange::Fixup)
	{
		if ((pDatabaseTCTxtCalTable = GetDatabaseEngine()->GetTCTxtCalTables()->GetAt(GetDatabaseEngine()->GetTCTxtCalTables()->Find(GetName()))))
		{
			SetAttributes(pDatabaseTCTxtCalTable->GetAttributes());
			CheckName();
			CheckPoint();
			CheckText();
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckPoint(IsCollectingIssues());
		bCheck &= CheckText(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtCalTablePointsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTableName((m_szNumbr = ExtractText(m_szNumbr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLEPOINT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtCalTablePointsRecordset::CheckPoint(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTablePointValue(GetAttributes() & (TCCALTABLE_RAWCODING_UNSIGNEDINTEGER | TCCALTABLE_RAWCODING_SIGNEDINTEGER | TCCALTABLE_RAWCODING_FLOATINGPOINT | TCCALTABLE_RAWRADIX_HEXADECIMAL | TCCALTABLE_RAWRADIX_DECIMAL | TCCALTABLE_RAWRADIX_OCTAL | TCCALTABLE_RAWRADIX_BINARY), (m_szAlVal = ExtractText(m_szAlVal))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLEPOINT_ILLEGALRAWVALUE), (LPCTSTR)GetName(), (!m_szAlVal.IsEmpty()) ? (LPCTSTR)m_szAlVal : STRING(IDS_DATABASE_TABLE_PAS_POINT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtCalTablePointsRecordset::CheckText(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtCalTablePointText((m_szAlTxt = ExtractText(m_szAlTxt))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTCALTABLEPOINT_ILLEGALTEXTVALUE), (LPCTSTR)GetName(), (LPCTSTR)m_szAlTxt); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCTxtCalTablePointsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCTxtCalTablePointsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PAS_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PAS_ALTXT)), m_szAlTxt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PAS_ALVAL)), m_szAlVal);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumOolTablesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCNumOolTablesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCNumOolTablesRecordset::CSCOS2000DatabaseTCNumOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCNumOolTablesRecordset)
	m_szNumbr.Empty();
	m_szDescr.Empty();
	m_szInter.Empty();
	m_szDspFmt.Empty();
	m_szRadix.Empty();
	m_szUnit.Empty();
	m_nNRange = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCNumOolTablesRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCNumOolTablesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CSCOS2000DatabaseTCNumOolTablesRecordset::GetUnit() CONST
{
	return m_szUnit;
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szInter = GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(nAttributes);
	m_szDspFmt = GetDatabaseEngine()->TranslateTCNumOolTableCoding(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCNumOolTableRadix(nAttributes);
}

UINT CSCOS2000DatabaseTCNumOolTablesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInter) | GetDatabaseEngine()->TranslateTCNumOolTableCoding(GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInter), m_szDspFmt) | GetDatabaseEngine()->TranslateTCNumOolTableRadix(GetDatabaseEngine()->TranslateTCNumOolTableInterpretation(m_szInter), m_szRadix);
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::SetLimits(INT nLimits)
{
	m_nNRange = nLimits;
}

INT CSCOS2000DatabaseTCNumOolTablesRecordset::GetLimits() CONST
{
	return m_nNRange;
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCNumOolTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCNumOolTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTCNumOolTablesRecordset::Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable)
{
	SetName(pDatabaseTCNumOolTable->GetName());
	SetDescription(pDatabaseTCNumOolTable->GetDescription());
	SetUnit(pDatabaseTCNumOolTable->GetUnit());
	SetAttributes(pDatabaseTCNumOolTable->GetAttributes());
	SetLimits(pDatabaseTCNumOolTable->GetLimits());
}

BOOL CSCOS2000DatabaseTCNumOolTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCNumOolTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		if (Check(FALSE))
		{
			CheckName();
			CheckDescription();
			CheckUnit();
			CheckAttributes();
			CheckLimits();
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return((!nOperation) ? ((GetAttributes() & TCOOLTABLE_CHECK_RAW) || ((GetAttributes() & TCOOLTABLE_CHECK_CALIBRATED) && (GetAttributes() & TCOOLTABLE_CODING_TEXTSTRING) == 0) || (GetAttributes() & TCOOLTABLE_CODING_TIME)) : TRUE);
}

BOOL CSCOS2000DatabaseTCNumOolTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableName((m_szNumbr = ExtractText(m_szNumbr))))
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

BOOL CSCOS2000DatabaseTCNumOolTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableDescription((m_szDescr = ExtractText(m_szDescr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCNumOolTablesRecordset::CheckUnit(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumCalTableUnit((m_szUnit = ExtractText(m_szUnit))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALUNIT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCNumOolTablesRecordset::CheckAttributes(BOOL bStatus)
{
	UINT  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableInterpretation((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALLIMITVALUESINTERPRETATION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumOolTableCoding(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALLIMITVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCNumOolTableRadix(nAttributes, nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALLIMITVALUESRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCNumOolTablesRecordset::CheckLimits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableLimitCount(GetLimits()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLE_ILLEGALLIMITSCOUNT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCNumOolTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCNumOolTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRF_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRF_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRF_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRF_DSPFMT)), m_szDspFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRF_RADIX)), m_szRadix);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRF_NRANGE)), m_nNRange);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRF_UNIT)), m_szUnit);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCNumOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCNumOolTableLimitsRecordset::CSCOS2000DatabaseTCNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCNumOolTableLimitsRecordset)
	m_szNumbr.Empty();
	m_szMinVal.Empty();
	m_szMaxVal.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTCNumOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCNumOolTableLimitsRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCNumOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTCNumOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::SetRange(double fLow, double fHigh)
{
	CStringTools  cStringTools;

	for (m_szMinVal.Empty(), m_szMaxVal.Empty(); (GetAttributes() & TCOOLTABLE_CODING_TIME) == 0; )
	{
		m_szMinVal = (!isnan(fLow)) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), fLow) : cStringTools.ConvertFloatToString(fLow);
		m_szMaxVal = (!isnan(fHigh)) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), fHigh) : cStringTools.ConvertFloatToString(fHigh);
		return(!isnan(fLow));
	}
	return FALSE;
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::GetRange(double &fLow, double &fHigh) CONST
{
	for (fLow = fHigh = 0.0; (GetAttributes() & TCOOLTABLE_CODING_TIME) == 0; )
	{
		fLow = (!m_szMinVal.IsEmpty()) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), m_szMinVal) : NAN;
		fHigh = (!m_szMaxVal.IsEmpty()) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitValue(GetAttributes(), m_szMaxVal) : NAN;
		return(!m_szMinVal.IsEmpty());
	}
	return FALSE;
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::SetTimeSpan(TIMETAG tStart, TIMETAG tStop)
{
	CStringTools  cStringTools;

	for (m_szMinVal.Empty(), m_szMaxVal.Empty(); GetAttributes() & TCOOLTABLE_CODING_TIME; )
	{
		m_szMinVal = (tStart != (TIMETAG)-1) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitTime(GetAttributes(), tStart) : cStringTools.ConvertLongIntToString(tStart);
		m_szMaxVal = (tStop != (TIMETAG)-1) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitTime(GetAttributes(), tStop) : cStringTools.ConvertLongIntToString(tStop);
		return(tStart != (TIMETAG)-1);
	}
	return FALSE;
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::GetTimeSpan(TIMETAG &tStart, TIMETAG &tStop) CONST
{
	for (tStart = tStop = (TIMETAG)-1; GetAttributes() & TCOOLTABLE_CODING_TIME; )
	{
		tStart = (!m_szMinVal.IsEmpty()) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitTime(GetAttributes(), m_szMinVal).GetTime() : (TIMETAG)-1;
		tStop = (!m_szMaxVal.IsEmpty()) ? GetDatabaseEngine()->TranslateTCNumOolTableLimitTime(GetAttributes(), m_szMaxVal).GetTime() : (TIMETAG)-1;
		return(!m_szMinVal.IsEmpty());
	}
	return FALSE;
}

VOID CSCOS2000DatabaseTCNumOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCNumOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTCNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCNumOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pszWarning);
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CONST CDatabaseTCNumOolLimit *pDatabaseTCNumOolLimit)
{
	UINT  nType;
	double  fLow;
	double  fHigh;
	TIMETAG  tStart;
	TIMETAG  tStop;
	CStringTools  cStringTools;

	SetName(pDatabaseTCNumOolTable->GetName());
	SetAttributes(pDatabaseTCNumOolTable->GetAttributes());
	return((pDatabaseTCNumOolLimit->GetRange(nType, fLow, fHigh) && SetRange(fLow, fHigh)) || (pDatabaseTCNumOolLimit->GetTimeSpan(tStart, tStop) && SetTimeSpan(tStart, tStop)));
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	if (nOperation == CFieldExchange::Fixup || !nOperation)
	{
		if ((pDatabaseTCNumOolTable = GetDatabaseEngine()->GetTCNumOolTables()->GetAt(GetDatabaseEngine()->GetTCNumOolTables()->Find(GetName()))))
		{
			for (SetAttributes(pDatabaseTCNumOolTable->GetAttributes()); (GetAttributes() & TCOOLTABLE_CHECK_RAW) || ((GetAttributes() & TCOOLTABLE_CHECK_CALIBRATED) && (GetAttributes() & TCOOLTABLE_CODING_TEXTSTRING) == 0) || (GetAttributes() & TCOOLTABLE_CODING_TIME); )
			{
				if (nOperation != 0)
				{
					CheckName();
					CheckLowLimit();
					CheckHighLimit();
				}
				return TRUE;
			}
		}
		return((nOperation != 0) ? TRUE : FALSE);
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckLowLimit(IsCollectingIssues());
		bCheck &= CheckHighLimit(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCNumOolTableName((m_szNumbr = ExtractText(m_szNumbr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::CheckLowLimit(BOOL bStatus)
{
	UINT  nAttributes;
	CString  szMessage;
	CStringTools  cStringTools;

	if ((((nAttributes = GetAttributes()) & TCOOLTABLE_CODING_TIME) == 0 && !GetDatabaseEngine()->CheckTCNumOolTableLimitValue(nAttributes, (m_szMinVal = ExtractText(m_szMinVal)))) || ((nAttributes & TCOOLTABLE_CODING_TIME) && !GetDatabaseEngine()->CheckTCNumOolTableLimitTime(GetAttributes(), (m_szMinVal = ExtractText(m_szMinVal)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (((nAttributes & TCOOLTABLE_CODING_TIME) == 0 && !m_szMinVal.IsEmpty() && m_szMinVal != cStringTools.ConvertFloatToString(NAN)) || ((nAttributes & TCOOLTABLE_CODING_TIME) && !m_szMinVal.IsEmpty() && m_szMinVal != cStringTools.ConvertLongIntToString(-1))) ? (LPCTSTR)m_szMinVal : STRING(IDS_DATABASE_TABLE_PRV_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCNumOolTableLimitsRecordset::CheckHighLimit(BOOL bStatus)
{
	UINT  nAttributes;
	CString  szMessage;
	CStringTools  cStringTools;

	if (((((nAttributes = GetAttributes()) & TCOOLTABLE_CODING_TIME) == 0 && !GetDatabaseEngine()->CheckTCNumOolTableLimitValue(nAttributes, (m_szMaxVal = ExtractText(m_szMaxVal)))) || ((nAttributes & TCOOLTABLE_CODING_TIME) && !GetDatabaseEngine()->CheckTCNumOolTableLimitTime(GetAttributes(), (m_szMaxVal = ExtractText(m_szMaxVal))))) && !m_szMaxVal.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCNUMOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (((nAttributes & TCOOLTABLE_CODING_TIME) == 0 && m_szMaxVal != cStringTools.ConvertFloatToString(NAN)) || ((nAttributes & TCOOLTABLE_CODING_TIME) && m_szMaxVal != cStringTools.ConvertLongIntToString(-1))) ? (LPCTSTR)m_szMaxVal : STRING(IDS_DATABASE_TABLE_PRV_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCNumOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCNumOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRV_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRV_MINVAL)), m_szMinVal);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRV_MAXVAL)), m_szMaxVal);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtOolTablesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCTxtOolTablesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCTxtOolTablesRecordset::CSCOS2000DatabaseTCTxtOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCTxtOolTablesRecordset)
	m_szNumbr.Empty();
	m_szDescr.Empty();
	m_szInter.Empty();
	m_szDspFmt.Empty();
	m_szRadix.Empty();
	m_szUnit.Empty();
	m_nNRange = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCTxtOolTablesRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescr = pszDescription;
}

CString CSCOS2000DatabaseTCTxtOolTablesRecordset::GetDescription() CONST
{
	return m_szDescr;
}

VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::SetAttributes(UINT nAttributes)
{
	m_szInter = GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(nAttributes);
	m_szDspFmt = GetDatabaseEngine()->TranslateTCTxtOolTableCoding(nAttributes);
	m_szRadix = GetDatabaseEngine()->TranslateTCTxtOolTableRadix(nAttributes);
}

UINT CSCOS2000DatabaseTCTxtOolTablesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(m_szInter) | GetDatabaseEngine()->TranslateTCTxtOolTableCoding(GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(m_szInter), m_szDspFmt) | GetDatabaseEngine()->TranslateTCTxtOolTableRadix(GetDatabaseEngine()->TranslateTCTxtOolTableInterpretation(m_szInter), m_szRadix);
}

VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::SetLimits(INT nLimits)
{
	m_nNRange = nLimits;
}

INT CSCOS2000DatabaseTCTxtOolTablesRecordset::GetLimits() CONST
{
	return m_nNRange;
}

VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszWarning);
}

VOID CSCOS2000DatabaseTCTxtOolTablesRecordset::Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable)
{
	SetName(pDatabaseTCTxtOolTable->GetName());
	SetDescription(pDatabaseTCTxtOolTable->GetDescription());
	SetAttributes(pDatabaseTCTxtOolTable->GetAttributes());
	SetLimits(pDatabaseTCTxtOolTable->GetLimits());
}

BOOL CSCOS2000DatabaseTCTxtOolTablesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCTxtOolTablesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		if (Check(FALSE))
		{
			CheckName();
			CheckDescription();
			CheckAttributes();
			CheckLimits();
		}
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return((!nOperation) ? (((GetAttributes() & TCOOLTABLE_CHECK_RAW) || ((GetAttributes() & TCOOLTABLE_CHECK_CALIBRATED) && (GetAttributes() & TCOOLTABLE_CODING_TEXTSTRING))) && (GetAttributes() & TCOOLTABLE_CODING_TIME) == 0) : TRUE);
}

BOOL CSCOS2000DatabaseTCTxtOolTablesRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableName((m_szNumbr = ExtractText(m_szNumbr))))
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

BOOL CSCOS2000DatabaseTCTxtOolTablesRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableDescription((m_szDescr = ExtractText(m_szDescr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtOolTablesRecordset::CheckAttributes(BOOL bStatus)
{
	UINT  nAttributes;
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableInterpretation((nAttributes = GetAttributes())))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALLIMITVALUESINTERPRETATION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCTxtOolTableCoding(nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALLIMITVALUESCODING), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckTCTxtOolTableRadix(nAttributes, nAttributes, nAttributes))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALLIMITVALUESRADIX), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCTxtOolTablesRecordset::CheckLimits(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableLimitCount(GetLimits()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLE_ILLEGALLIMITSCOUNT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCTxtOolTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCTxtOolTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRS_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRS_DESCR)), m_szDescr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRS_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRS_DSPFMT)), m_szDspFmt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRS_RADIX)), m_szRadix);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRS_NRANGE)), m_nNRange);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRS_UNIT)), m_szUnit);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtOolTableLimitsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCTxtOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::CSCOS2000DatabaseTCTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCTxtOolTableLimitsRecordset)
	m_szNumbr.Empty();
	m_szMinVal.Empty();
	m_szMaxVal.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nAttributes = 0;
}

VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbr = pszName;
}

CString CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::GetName() CONST
{
	return m_szNumbr;
}

VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::SetAttributes(UINT nAttributes)
{
	m_nAttributes = nAttributes;
}

UINT CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::GetAttributes() CONST
{
	return m_nAttributes;
}

VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::SetLowLimit(LPCTSTR pszLowLimit)
{
	m_szMinVal = pszLowLimit;
}

CString CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::GetLowLimit() CONST
{
	return m_szMinVal;
}

VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::SetHighLimit(LPCTSTR pszHighLimit)
{
	m_szMaxVal = pszHighLimit;
}

CString CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::GetHighLimit() CONST
{
	return m_szMaxVal;
}

VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbr), pszError);
}
VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszError);
}

VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbr), pszWarning);
}
VOID CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pszWarning);
}

BOOL CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CONST CDatabaseTCTxtOolLimit *pDatabaseTCTxtOolLimit)
{
	double  fLow;
	double  fHigh;
	CString  szLimit[2];
	CStringTools  cStringTools;

	for (SetName(pDatabaseTCTxtOolTable->GetName()), SetAttributes(pDatabaseTCTxtOolTable->GetAttributes()); pDatabaseTCTxtOolLimit->GetRange(szLimit[0], szLimit[1]); )
	{
		SetLowLimit(szLimit[0]);
		SetHighLimit(szLimit[1]);
		return TRUE;
	}
	if (pDatabaseTCTxtOolLimit->GetRange(fLow, fHigh))
	{
		SetLowLimit((!isnan(fLow)) ? ((GetAttributes() & TCOOLTABLE_CODING_UNSIGNEDINTEGER) ? cStringTools.ConvertUIntToString((UINT)fLow) : ((GetAttributes() & TCOOLTABLE_CODING_SIGNEDINTEGER) ? cStringTools.ConvertIntToString((INT)fLow) : cStringTools.ConvertFloatToString(fLow))) : cStringTools.ConvertFloatToString(fLow));
		SetHighLimit((!isnan(fHigh)) ? ((GetAttributes() & TCOOLTABLE_CODING_UNSIGNEDINTEGER) ? cStringTools.ConvertUIntToString((UINT)fHigh) : ((GetAttributes() & TCOOLTABLE_CODING_SIGNEDINTEGER) ? cStringTools.ConvertIntToString((INT)fHigh) : cStringTools.ConvertFloatToString(fHigh))) : cStringTools.ConvertFloatToString(fHigh));
		return TRUE;
	}
	if (pDatabaseTCTxtOolLimit->GetLimit(szLimit[0]))
	{
		SetLowLimit(szLimit[0]);
		SetHighLimit(EMPTYSTRING);
		return TRUE;
	}
	if (pDatabaseTCTxtOolLimit->GetLimit(fLow))
	{
		SetLowLimit((!isnan(fLow)) ? ((GetAttributes() & TCOOLTABLE_CODING_UNSIGNEDINTEGER) ? cStringTools.ConvertUIntToString((UINT)fLow) : ((GetAttributes() & TCOOLTABLE_CODING_SIGNEDINTEGER) ? cStringTools.ConvertIntToString((INT)fLow) : cStringTools.ConvertFloatToString(fLow))) : cStringTools.ConvertFloatToString(fLow));
		SetHighLimit(EMPTYSTRING);
		return TRUE;
	}
	return FALSE;
}

BOOL CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	if (nOperation == CFieldExchange::Fixup || !nOperation)
	{
		if ((pDatabaseTCTxtOolTable = GetDatabaseEngine()->GetTCTxtOolTables()->GetAt(GetDatabaseEngine()->GetTCTxtOolTables()->Find(GetName()))))
		{
			for (SetAttributes(pDatabaseTCTxtOolTable->GetAttributes()); ((GetAttributes() & TCOOLTABLE_CHECK_RAW) || ((GetAttributes() & TCOOLTABLE_CHECK_CALIBRATED) && (GetAttributes() & TCOOLTABLE_CODING_TEXTSTRING))) && (GetAttributes() & TCOOLTABLE_CODING_TIME) == 0; )
			{
				if (nOperation != 0)
				{
					CheckName();
					CheckLowLimit();
					CheckHighLimit();
				}
				return TRUE;
			}
		}
		return((nOperation != 0) ? TRUE : FALSE);
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckLowLimit(IsCollectingIssues());
		bCheck &= CheckHighLimit(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableName((m_szNumbr = ExtractText(m_szNumbr))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLELIMIT_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::CheckLowLimit(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableLimitValue(GetAttributes(), (m_szMinVal = ExtractText(m_szMinVal))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLELIMIT_ILLEGALLOWLIMIT), (LPCTSTR)GetName(), (!m_szMinVal.IsEmpty() && m_szMinVal != cStringTools.ConvertFloatToString(NAN)) ? (LPCTSTR)m_szMinVal : STRING(IDS_DATABASE_TABLE_PRT_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::CheckHighLimit(BOOL bStatus)
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (!GetDatabaseEngine()->CheckTCTxtOolTableLimitValue(GetAttributes(), (m_szMaxVal = ExtractText(m_szMaxVal))) && !m_szMaxVal.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCTXTOOLTABLELIMIT_ILLEGALHIGHLIMIT), (LPCTSTR)GetName(), (m_szMaxVal != cStringTools.ConvertFloatToString(NAN)) ? (LPCTSTR)m_szMaxVal : STRING(IDS_DATABASE_TABLE_PRT_LIMIT_NONE)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCTxtOolTableLimitsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCTxtOolTableLimitsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRT_NUMBR)), m_szNumbr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRT_MINVAL)), m_szMinVal);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PRT_MAXVAL)), m_szMaxVal);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCPreExeGroupParametersRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCPreExeGroupParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCPreExeGroupParametersRecordset::CSCOS2000DatabaseTCPreExeGroupParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCPreExeGroupParametersRecordset)
	m_szCName.Empty();
	m_szParNam.Empty();
	m_szInter.Empty();
	m_szVal.Empty();
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::SetID(LPCTSTR pszID)
{
	m_szCName = pszID;
}

CString CSCOS2000DatabaseTCPreExeGroupParametersRecordset::GetID() CONST
{
	return m_szCName;
}

VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szParNam = pszTag;
}

CString CSCOS2000DatabaseTCPreExeGroupParametersRecordset::GetTag() CONST
{
	return m_szParNam;
}

VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::SetAttributes(UINT nAttributes)
{
	m_szInter = GetDatabaseEngine()->TranslateTCPreExeGroupParameterInterpretation(nAttributes);
}

UINT CSCOS2000DatabaseTCPreExeGroupParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCPreExeGroupParameterInterpretation(m_szInter);
}

VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::SetValue(LPCTSTR pszValue)
{
	m_szVal = pszValue;
}

CString CSCOS2000DatabaseTCPreExeGroupParametersRecordset::GetValue() CONST
{
	return m_szVal;
}

VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szCName), pszError);
}
VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, pszError);
}

VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szCName), pszWarning);
}
VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, pszWarning);
}

VOID CSCOS2000DatabaseTCPreExeGroupParametersRecordset::Translate(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, CONST CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter)
{
	SetID(pDatabaseTCPreExeGroup->GetID());
	SetTag(pDatabaseTCPreExeGroupParameter->GetTag());
	SetAttributes(pDatabaseTCPreExeGroupParameter->GetAttributes());
	SetValue(pDatabaseTCPreExeGroupParameter->GetValueAsText());
}

BOOL CSCOS2000DatabaseTCPreExeGroupParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCPreExeGroupParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID();
		CheckTag();
		CheckAttributes();
		CheckValue();
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

BOOL CSCOS2000DatabaseTCPreExeGroupParametersRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionName((m_szCName = ExtractText(m_szCName))))
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

BOOL CSCOS2000DatabaseTCPreExeGroupParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupParameterTag((m_szParNam = ExtractText(m_szParNam))))
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

BOOL CSCOS2000DatabaseTCPreExeGroupParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCPreExeGroupParameterInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPREEXEGROUPPARAMETER_ILLEGALINTERPRETATION), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCPreExeGroupParametersRecordset::CheckValue(BOOL bStatus)
{
	INT  nLength;
	CString  szMessage;

	if ((nLength = lstrlen((m_szVal = ExtractText(m_szVal)))) == 0 || nLength > GetDatabaseEngine()->GetTCPreExeGroupParameterConstValueLength())
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

void CSCOS2000DatabaseTCPreExeGroupParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCPreExeGroupParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PTV_CNAME)), m_szCName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PTV_PARNAM)), m_szParNam);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PTV_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PTV_VAL)), m_szVal);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCExeVerStagesRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCExeVerStagesRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCExeVerStagesRecordset::CSCOS2000DatabaseTCExeVerStagesRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCExeVerStagesRecordset)
	m_szType.Empty();
	m_szSource.Empty();
	m_nID = 0;
	m_nSPID = 0;
	m_nStart = 0;
	m_nInterval = 0;
	m_nUncertainty = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::SetID(LPCTSTR pszID)
{
	m_nID = ConvertID((m_szID = pszID));
}

CString CSCOS2000DatabaseTCExeVerStagesRecordset::GetID() CONST
{
	return ConvertID(m_nID);
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::SetType(INT nType)
{
	m_szType = GetDatabaseEngine()->TranslateTCExeVerGroupParameterStage(nType);
}

INT CSCOS2000DatabaseTCExeVerStagesRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateTCExeVerGroupParameterStage(m_szType);
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::SetAttributes(UINT nAttributes)
{
	m_szSource = GetDatabaseEngine()->TranslateTCExeVerGroupParameterType(nAttributes);
}

UINT CSCOS2000DatabaseTCExeVerStagesRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCExeVerGroupParameterType(m_szSource);
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::SetTimeWindowOffset(CONST CTimeSpan &tOffset)
{
	m_nStart = (INT)tOffset.GetTotalSeconds();
}

CTimeSpan CSCOS2000DatabaseTCExeVerStagesRecordset::GetTimeWindowOffset() CONST
{
	return m_nStart;
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::SetTimeWindowInterval(CONST CTimeSpan &tInterval)
{
	m_nInterval = (INT)tInterval.GetTotalSeconds();
}

CTimeSpan CSCOS2000DatabaseTCExeVerStagesRecordset::GetTimeWindowInterval() CONST
{
	return m_nInterval;
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::SetTimeWindowUncertainty(CONST CTimeSpan &tInterval)
{
	m_nUncertainty = (INT)tInterval.GetTotalSeconds();
}

CTimeSpan CSCOS2000DatabaseTCExeVerStagesRecordset::GetTimeWindowUncertainty() CONST
{
	return m_nUncertainty;
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::SetTimeWindowClosurePacket(LPCTSTR pszTag)
{
	m_nSPID = (lstrlen(pszTag) > 0) ? _ttoi(pszTag) : 0;
}

CString CSCOS2000DatabaseTCExeVerStagesRecordset::GetTimeWindowClosurePacket() CONST
{
	CStringTools  cStringTools;

	return((m_nSPID > 0) ? cStringTools.ConvertIntToString(m_nSPID) : EMPTYSTRING);
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetID(), pszError);
}
VOID CSCOS2000DatabaseTCExeVerStagesRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, pszError);
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetID(), pszWarning);
}
VOID CSCOS2000DatabaseTCExeVerStagesRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, pszWarning);
}

VOID CSCOS2000DatabaseTCExeVerStagesRecordset::Translate(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage)
{
	SetID(pDatabaseTCExeVerStage->GetID());
	SetType(pDatabaseTCExeVerStage->GetType());
	SetAttributes(pDatabaseTCExeVerStage->GetAttributes());
	SetTimeWindowOffset(pDatabaseTCExeVerStage->GetTimeWindowOffset());
	SetTimeWindowInterval(pDatabaseTCExeVerStage->GetTimeWindowInterval());
	SetTimeWindowUncertainty(pDatabaseTCExeVerStage->GetTimeWindowUncertainty());
	SetTimeWindowClosurePacket(pDatabaseTCExeVerStage->GetTimeWindowClosurePacket());
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID();
		CheckType();
		CheckAttributes();
		CheckTimeWindowOffset();
		CheckTimeWindowInterval();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckTimeWindowOffset(IsCollectingIssues());
		bCheck &= CheckTimeWindowInterval(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterStageID(m_nID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGE_ILLEGALID), (!IsCollectingIssues()) ? (LPCTSTR)GetID() : (LPCTSTR)m_szID); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterStage(GetType()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGE_ILLEGALTYPE), (!IsCollectingIssues()) ? (LPCTSTR)GetID() : (LPCTSTR)m_szID); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterType(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGE_ILLEGALSOURCE), (!IsCollectingIssues()) ? (LPCTSTR)GetID() : (LPCTSTR)m_szID); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::CheckTimeWindowOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterTimeWindowOffset(GetTimeWindowOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGE_ILLEGALTIMEWINDOWOFFSET), (!IsCollectingIssues()) ? (LPCTSTR)GetID() : (LPCTSTR)m_szID); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::CheckTimeWindowInterval(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterTimeWindowInterval(GetTimeWindowInterval()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGE_ILLEGALTIMEWINDOWINTERVAL), (!IsCollectingIssues()) ? (LPCTSTR)GetID() : (LPCTSTR)m_szID); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::CheckTimeWindowUncertainty(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterTimeWindowUncertainty(GetTimeWindowUncertainty()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGE_ILLEGALTIMEWINDOWUNCERTAINTY), (!IsCollectingIssues()) ? (LPCTSTR)GetID() : (LPCTSTR)m_szID); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStagesRecordset::CheckTimeWindowClosurePacket(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterTimeWindowClosurePacketID(m_nSPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGE_ILLEGALTIMEWINDOWCLOSUREPACKET), (!IsCollectingIssues()) ? (LPCTSTR)GetID() : (LPCTSTR)m_szID); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

INT CSCOS2000DatabaseTCExeVerStagesRecordset::ConvertID(LPCTSTR pszID) CONST
{
	BOOL  bSign;
	ULONGLONG  nID;

	return((GetDatabaseEngine()->ParseValue(pszID, 10, nID, bSign) && !bSign) ? (INT)nID : -1);
}

CString CSCOS2000DatabaseTCExeVerStagesRecordset::ConvertID(INT nID) CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertIntToString(nID);
}

void CSCOS2000DatabaseTCExeVerStagesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCExeVerStagesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVS_ID)), m_nID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVS_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVS_SOURCE)), m_szSource);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVS_START)), m_nStart);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVS_INTERVAL)), m_nInterval);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVS_SPID)), m_nSPID);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVS_UNCERTAINTY)), m_nUncertainty);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCExeVerStageParametersRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCExeVerStageParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCExeVerStageParametersRecordset::CSCOS2000DatabaseTCExeVerStageParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCExeVerStageParametersRecordset)
	m_szParNam.Empty();
	m_szInter.Empty();
	m_szVal.Empty();
	m_szTol.Empty();
	m_szCheck.Empty();
	m_nCVSID = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::SetID(LPCTSTR pszID)
{
	m_nCVSID = _ttoi(pszID);
}

CString CSCOS2000DatabaseTCExeVerStageParametersRecordset::GetID() CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertIntToString(m_nCVSID);
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::SetTag(LPCTSTR pszTag)
{
	m_szParNam = pszTag;
}

CString CSCOS2000DatabaseTCExeVerStageParametersRecordset::GetTag() CONST
{
	return m_szParNam;
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::SetAttributes(UINT nAttributes)
{
	m_szInter = GetDatabaseEngine()->TranslateTCExeVerGroupParameterInterpretation(nAttributes);
	m_szCheck = GetDatabaseEngine()->TranslateTCExeVerGroupParameterChecking(nAttributes);
}

UINT CSCOS2000DatabaseTCExeVerStageParametersRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCExeVerGroupParameterInterpretation(m_szInter) | GetDatabaseEngine()->TranslateTCExeVerGroupParameterChecking(m_szCheck);
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::SetValue(LPCTSTR pszValue)
{
	m_szVal = pszValue;
}

CString CSCOS2000DatabaseTCExeVerStageParametersRecordset::GetValue() CONST
{
	return m_szVal;
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::SetValueTolerance(LPCTSTR pszDelta)
{
	m_szTol = pszDelta;
}

CString CSCOS2000DatabaseTCExeVerStageParametersRecordset::GetValueTolerance() CONST
{
	return m_szTol;
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(GetID(), pszError);
}
VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, pszError);
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(GetID(), pszWarning);
}
VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, pszWarning);
}

VOID CSCOS2000DatabaseTCExeVerStageParametersRecordset::Translate(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, CONST CDatabaseTCExeVerStageParameter *pDatabaseTCExeVerStageParameter)
{
	SetID(pDatabaseTCExeVerStage->GetID());
	SetTag(pDatabaseTCExeVerStageParameter->GetTag());
	SetAttributes(pDatabaseTCExeVerStageParameter->GetAttributes());
	SetValue(pDatabaseTCExeVerStageParameter->GetValueAsText());
	SetValueTolerance(pDatabaseTCExeVerStageParameter->GetValueToleranceAsText());
}

BOOL CSCOS2000DatabaseTCExeVerStageParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCExeVerStageParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckID();
		CheckTag();
		CheckAttributes();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckID(IsCollectingIssues());
		bCheck &= CheckTag(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStageParametersRecordset::CheckID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterStageID(m_nCVSID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGEPARAMETER_ILLEGALID), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStageParametersRecordset::CheckTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterTag((m_szParNam = ExtractText(m_szParNam))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGEPARAMETER_ILLEGALTAG), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStageParametersRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterInterpretation(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGEPARAMETER_ILLEGALINTERPRETATION), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStageParametersRecordset::CheckValue(BOOL bStatus)
{
	INT  nLength;
	CString  szMessage;

	if ((nLength = lstrlen((m_szVal = ExtractText(m_szVal)))) == 0 || nLength > GetDatabaseEngine()->GetTCExeVerGroupParameterConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGEPARAMETER_ILLEGALVALUE), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerStageParametersRecordset::CheckValueTolerance(BOOL bStatus)
{
	INT  nLength;
	CString  szMessage;

	if ((nLength = lstrlen((m_szTol = ExtractText(m_szTol)))) == 0 || nLength > GetDatabaseEngine()->GetTCExeVerGroupParameterConstValueToleranceLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERSTAGEPARAMETER_ILLEGALVALUETOLERANCE), (LPCTSTR)GetID(), (LPCTSTR)GetTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCExeVerStageParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCExeVerStageParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVE_CVSID)), m_nCVSID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVE_PARNAM)), m_szParNam);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVE_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVE_VAL)), m_szVal);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVE_TOL)), m_szTol);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVE_CHECK)), m_szCheck);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCExeVerGroupsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCExeVerGroupsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCExeVerGroupsRecordset::CSCOS2000DatabaseTCExeVerGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCExeVerGroupsRecordset)
	m_szTask.Empty();
	m_szType.Empty();
	m_nCVSID = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::SetTask(LPCTSTR pszTask)
{
	m_szTask = pszTask;
}

CString CSCOS2000DatabaseTCExeVerGroupsRecordset::GetTask() CONST
{
	return m_szTask;
}

VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::SetStageID(LPCTSTR pszID)
{
	m_nCVSID = _ttoi(pszID);
}

CString CSCOS2000DatabaseTCExeVerGroupsRecordset::GetStageID() CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertIntToString(m_nCVSID);
}

VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::SetAttributes(UINT nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCExeVerGroupParameterStageType(nAttributes);
}

UINT CSCOS2000DatabaseTCExeVerGroupsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCExeVerGroupParameterStageType(m_szType);
}

VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szTask), pszError);
}
VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, pszError);
}

VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szTask), pszWarning);
}
VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, pszWarning);
}

VOID CSCOS2000DatabaseTCExeVerGroupsRecordset::Translate(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, LPCTSTR pszStageID)
{
	SetTask(pDatabaseTCExeVerGroup->GetID());
	SetAttributes(pDatabaseTCExeVerGroup->GetAttributes());
	SetStageID(pszStageID);
}

BOOL CSCOS2000DatabaseTCExeVerGroupsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCExeVerGroupsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTask();
		CheckStageID();
		CheckAttributes();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTask(IsCollectingIssues());
		bCheck &= CheckStageID(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerGroupsRecordset::CheckTask(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterStageTask((m_szTask = ExtractText(m_szTask))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALTASK), (LPCTSTR)GetTask()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerGroupsRecordset::CheckStageID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterStageID(m_nCVSID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALSTAGEID), (LPCTSTR)GetTask()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCExeVerGroupsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCExeVerGroupParameterStageType(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCEXEVERGROUP_ILLEGALTYPE), (LPCTSTR)GetTask()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCExeVerGroupsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCExeVerGroupsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVP_TASK)), m_szTask);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVP_TYPE)), m_szType);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_CVP_CVSID)), m_nCVSID);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterSetsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCParameterSetsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCParameterSetsRecordset::CSCOS2000DatabaseTCParameterSetsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCParameterSetsRecordset)
	m_szName.Empty();
	m_szDescription.Empty();
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCParameterSetsRecordset::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CSCOS2000DatabaseTCParameterSetsRecordset::GetName() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTCParameterSetsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CSCOS2000DatabaseTCParameterSetsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CSCOS2000DatabaseTCParameterSetsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szName), pszError);
}
VOID CSCOS2000DatabaseTCParameterSetsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszError);
}

VOID CSCOS2000DatabaseTCParameterSetsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szName), pszWarning);
}
VOID CSCOS2000DatabaseTCParameterSetsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszWarning);
}

VOID CSCOS2000DatabaseTCParameterSetsRecordset::Translate(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet)
{
	SetName(pDatabaseTCParameterSet->GetName());
	SetDescription(pDatabaseTCParameterSet->GetDescription());
}

BOOL CSCOS2000DatabaseTCParameterSetsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCParameterSetsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckDescription();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterSetsRecordset::CheckName(BOOL bStatus)
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

BOOL CSCOS2000DatabaseTCParameterSetsRecordset::CheckDescription(BOOL bStatus)
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

void CSCOS2000DatabaseTCParameterSetsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCParameterSetsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PST_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PST_DESCR)), m_szDescription);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterSetsValueRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCParameterValueSetsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCParameterValueSetsRecordset::CSCOS2000DatabaseTCParameterValueSetsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCParameterValueSetsRecordset)
	m_szName.Empty();
	m_szPVSID.Empty();
	m_szDescription.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::SetParameterSet(LPCTSTR pszSet)
{
	m_szName = pszSet;
}

CString CSCOS2000DatabaseTCParameterValueSetsRecordset::GetParameterSet() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::SetName(LPCTSTR pszName)
{
	m_szPVSID = pszName;
}

CString CSCOS2000DatabaseTCParameterValueSetsRecordset::GetName() CONST
{
	return m_szPVSID;
}

VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CSCOS2000DatabaseTCParameterValueSetsRecordset::GetDescription() CONST
{
	return m_szDescription;
}

VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szPVSID), pszError);
}
VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET, pszError);
}

VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szPVSID), pszWarning);
}
VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET, pszWarning);
}

VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet)
{
	Translate(pDatabaseTCParameterValueSet, EMPTYSTRING);
}
VOID CSCOS2000DatabaseTCParameterValueSetsRecordset::Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, LPCTSTR pszParameterSet)
{
	SetParameterSet(pszParameterSet);
	SetName(pDatabaseTCParameterValueSet->GetName());
	SetDescription(pDatabaseTCParameterValueSet->GetDescription());
}

BOOL CSCOS2000DatabaseTCParameterValueSetsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCParameterValueSetsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckParameterSet();
		CheckName();
		CheckDescription();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetsRecordset::CheckParameterSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetName((m_szName = ExtractText(m_szName))) && !m_szName.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESET_ILLEGALSET), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterValueSetName((m_szPVSID = ExtractText(m_szPVSID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESET_ILLEGALNAME), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetsRecordset::CheckDescription(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterValueSetDescription((m_szDescription = ExtractText(m_szDescription))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESET_ILLEGALDESCRIPTION), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCParameterValueSetsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCParameterValueSetsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSV_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSV_PVSID)), m_szPVSID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSV_DESCR)), m_szDescription);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterValueSetItemsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCParameterValueSetItemsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCParameterValueSetItemsRecordset::CSCOS2000DatabaseTCParameterValueSetItemsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCParameterSetItemsRecordset)
	m_szID.Empty();
	m_szPSID.Empty();
	m_szPName.Empty();
	m_szInter.Empty();
	m_szVals.Empty();
	m_nBit = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::SetParameterSet(LPCTSTR pszSet)
{
	m_szPSID = pszSet;
}

CString CSCOS2000DatabaseTCParameterValueSetItemsRecordset::GetParameterSet() CONST
{
	return m_szPSID;
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::SetValueSet(LPCTSTR pszSet)
{
	m_szID = pszSet;
}

CString CSCOS2000DatabaseTCParameterValueSetItemsRecordset::GetValueSet() CONST
{
	return m_szID;
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::SetParameterTag(LPCTSTR pszTag)
{
	m_szPName = pszTag;
}

CString CSCOS2000DatabaseTCParameterValueSetItemsRecordset::GetParameterTag() CONST
{
	return m_szPName;
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::SetAttributes(ULONGLONG nAttributes)
{
	m_szInter = GetDatabaseEngine()->TranslateTCParameterSetItemValueInterpretation(nAttributes);
}

ULONGLONG CSCOS2000DatabaseTCParameterValueSetItemsRecordset::GetAttributes() CONST
{
	return TCFUNCTIONELEMENT_TYPE_PARAMETER | GetDatabaseEngine()->TranslateTCParameterSetItemValueInterpretation(m_szInter);
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::SetBitOffset(INT nOffset)
{
	m_nBit = nOffset;
}

INT CSCOS2000DatabaseTCParameterValueSetItemsRecordset::GetBitOffset() CONST
{
	return m_nBit;
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::SetConstValue(LPCTSTR pszConstValue)
{
	m_szVals = pszConstValue;
}

CString CSCOS2000DatabaseTCParameterValueSetItemsRecordset::GetConstValue() CONST
{
	return m_szVals;
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szID), pszError);
}
VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET, pszError);
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szID), pszWarning);
}
VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET, pszWarning);
}

VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement)
{
	Translate(pDatabaseTCParameterValueSet, pDatabaseTCFunctionElement, EMPTYSTRING);
}
VOID CSCOS2000DatabaseTCParameterValueSetItemsRecordset::Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, LPCTSTR pszParameterSet)
{
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	for (SetParameterSet(pszParameterSet), SetValueSet(pDatabaseTCParameterValueSet->GetName()), SetParameterTag(pDatabaseTCFunctionElement->GetName()), SetAttributes(pDatabaseTCFunctionElement->GetAttributes()), SetBitOffset(8 * pDatabaseTCFunctionElement->GetBytePos() + pDatabaseTCFunctionElement->GetBitPos()), SetConstValue(pDatabaseTCFunctionElement->GetConstValueAsText()); (pDatabaseTCParameterSet = GetDatabaseEngine()->GetTCParameterSets()->GetAt(GetDatabaseEngine()->GetTCParameterSets()->Find(pszParameterSet))) && (pDatabaseTCParameterSet->GetType() & TCPARAMETERSET_TYPE_SEQUENCE); )
	{
		SetBitOffset(pDatabaseTCFunctionElement->GetBytePos());
		break;
	}
}

BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckParameterSet();
		CheckValueSet();
		CheckParameterTag();
		CheckAttributes();
		CheckBitOffset();
		CheckConstValue();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckValueSet(IsCollectingIssues());
		bCheck &= CheckParameterTag(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		bCheck &= CheckBitOffset(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::CheckParameterSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetName((m_szPSID = ExtractText(m_szPSID))) && !m_szPSID.IsEmpty())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESETITEM_ILLEGALSETNAME), (LPCTSTR)GetValueSet(), (LPCTSTR)GetParameterTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::CheckValueSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterValueSetName((m_szID = ExtractText(m_szID))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESETITEM_ILLEGALVALUESETNAME), (LPCTSTR)GetValueSet(), (LPCTSTR)GetParameterTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::CheckParameterTag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetItemName((m_szPName = ExtractText(m_szPName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESETITEM_ILLEGALNAME), (LPCTSTR)GetValueSet(), (LPCTSTR)GetParameterTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetItemValueInterpretation(GetAttributes(), GetDatabaseEngine()->TranslateTCParameterSetItemValueInterpretation((m_szInter = ExtractText(m_szInter)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESETITEM_ILLEGALVALUEINTERPRETATION), (LPCTSTR)GetValueSet(), (LPCTSTR)GetParameterTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::CheckBitOffset(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetItemValueBitOffset(GetBitOffset()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESETITEM_ILLEGALBITOFFSET), (LPCTSTR)GetValueSet(), (LPCTSTR)GetParameterTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterValueSetItemsRecordset::CheckConstValue(BOOL bStatus)
{
	CString  szMessage;

	if (lstrlen((m_szVals = ExtractText(m_szVals))) > GetDatabaseEngine()->GetTCParameterSetItemConstValueLength())
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERVALUESETITEM_ILLEGALCONSTVALUE), (LPCTSTR)GetValueSet(), (LPCTSTR)GetParameterTag()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCParameterValueSetItemsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCParameterValueSetItemsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVS_ID)), m_szID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVS_PSID)), m_szPSID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVS_PNAME)), m_szPName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVS_INTER)), m_szInter);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVS_VALS)), m_szVals);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PVS_BIT)), m_nBit);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterSetAssociationsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCParameterSetAssociationsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCParameterSetAssociationsRecordset::CSCOS2000DatabaseTCParameterSetAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCParameterSetAssociationsRecordset)
	m_szName.Empty();
	m_szType.Empty();
	m_szParSet.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::SetTask(LPCTSTR pszTask)
{
	m_szName = pszTask;
}

CString CSCOS2000DatabaseTCParameterSetAssociationsRecordset::GetTask() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::SetParameterSet(LPCTSTR pszSet)
{
	m_szParSet = pszSet;
}

CString CSCOS2000DatabaseTCParameterSetAssociationsRecordset::GetParameterSet() CONST
{
	return m_szParSet;
}

VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::SetAttributes(UINT nAttributes)
{
	m_szType = GetDatabaseEngine()->TranslateTCParameterSetType(nAttributes);
}

UINT CSCOS2000DatabaseTCParameterSetAssociationsRecordset::GetAttributes() CONST
{
	return GetDatabaseEngine()->TranslateTCParameterSetType(m_szType);
}

VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szParSet), pszError);
}
VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszError);
}

VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szParSet), pszWarning);
}
VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszName, DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pszWarning);
}

VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, LPCTSTR pszSet)
{
	SetParameterSet(pszSet);
	SetTask(pDatabaseTCFunction->GetName());
	SetAttributes(TCPARAMETERSET_TYPE_FUNCTION);
}
VOID CSCOS2000DatabaseTCParameterSetAssociationsRecordset::Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, LPCTSTR pszSet)
{
	SetParameterSet(pszSet);
	SetTask(pDatabaseTCSequence->GetName());
	SetAttributes(TCPARAMETERSET_TYPE_SEQUENCE);
}

BOOL CSCOS2000DatabaseTCParameterSetAssociationsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCParameterSetAssociationsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckTask();
		CheckParameterSet();
		CheckAttributes();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckTask(IsCollectingIssues());
		bCheck &= CheckParameterSet(IsCollectingIssues());
		bCheck &= CheckAttributes(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterSetAssociationsRecordset::CheckTask(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetTask((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETASSOCIATION_ILLEGALTASK), (LPCTSTR)GetParameterSet()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterSetAssociationsRecordset::CheckParameterSet(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetName((m_szParSet = ExtractText(m_szParSet))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETASSOCIATION_ILLEGALSETNAME), (LPCTSTR)GetParameterSet()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCParameterSetAssociationsRecordset::CheckAttributes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCParameterSetType(GetAttributes()))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCPARAMETERSETASSOCIATION_ILLEGALTYPE), (LPCTSTR)GetParameterSet()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCParameterSetAssociationsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCParameterSetAssociationsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSM_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSM_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_PSM_PARSET)), m_szParSet);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCFunctionRoutingPathsRecordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseTCFunctionRoutingPathsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::CSCOS2000DatabaseTCFunctionRoutingPathsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseTCFunctionRoutingPathsRecordset)
	m_nAPID = 0;
	m_szRoute.Empty();
	m_nFields = 2;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::SetAPID(INT nAPID)
{
	m_nAPID = nAPID;
}

INT CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::GetAPID() CONST
{
	return m_nAPID;
}

VOID CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::SetRoute(LPCTSTR pszRoute)
{
	m_szRoute = pszRoute;
}

CString CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::GetRoute() CONST
{
	return m_szRoute;
}

VOID CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::ShowError(LPCTSTR pszError)
{
	CStringTools  cStringTools;

	ShowError(cStringTools.ConvertIntToString(GetAPID()), pszError);
}
VOID CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::ShowError(LPCTSTR pszID, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(EMPTYSTRING, pszID, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH, pszError);
}

VOID CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	CStringTools  cStringTools;

	ShowWarning(cStringTools.ConvertIntToString(GetAPID()), pszWarning);
}
VOID CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::ShowWarning(LPCTSTR pszID, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(EMPTYSTRING, pszID, DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH, pszWarning);
}

VOID CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::Translate(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath)
{
	m_nAPID = pDatabaseTCFunctionRoutingPath->GetAPID();
	m_szRoute = pDatabaseTCFunctionRoutingPath->GetPath();
}

BOOL CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckAPID();
		CheckRoute();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckAPID(IsCollectingIssues());
		bCheck &= CheckRoute(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::CheckAPID(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionAPID(m_nAPID))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONROUTINGPATH_ILLEGALAPID), GetAPID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::CheckRoute(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckTCFunctionRouteAndDestinationPath((m_szRoute = ExtractText(m_szRoute))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_TCFUNCTIONROUTINGPATH_ILLEGALROUTE), GetAPID()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseTCFunctionRoutingPathsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseTCFunctionRoutingPathsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DST_APID)), m_nAPID);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DST_ROUTE)), m_szRoute);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseANDDirectoryRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseANDDirectoryRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseANDDirectoryRecordset::CSCOS2000DatabaseANDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseANDDirectoryRecordset)
	m_szNumbe.Empty();
	m_szType.Empty();
	m_szHead.Empty();
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseANDDirectoryRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbe = pszName;
}

CString CSCOS2000DatabaseANDDirectoryRecordset::GetName() CONST
{
	return m_szNumbe;
}

VOID CSCOS2000DatabaseANDDirectoryRecordset::SetTitle(LPCTSTR pszTitle)
{
	m_szHead = pszTitle;
}

CString CSCOS2000DatabaseANDDirectoryRecordset::GetTitle() CONST
{
	return m_szHead;
}

VOID CSCOS2000DatabaseANDDirectoryRecordset::SetColumns(CONST CUIntArray &nColumns)
{
	m_szType = GetDatabaseEngine()->TranslateANDColumns(nColumns);
}

INT CSCOS2000DatabaseANDDirectoryRecordset::GetColumns(CUIntArray &nColumns) CONST
{
	return GetDatabaseEngine()->TranslateANDColumns(m_szType, nColumns);
}

VOID CSCOS2000DatabaseANDDirectoryRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbe), pszError);
}
VOID CSCOS2000DatabaseANDDirectoryRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseANDDirectoryRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbe), pszWarning);
}
VOID CSCOS2000DatabaseANDDirectoryRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseANDDirectoryRecordset::Translate(CONST CANDLayout *pANDLayout)
{
	CUIntArray  nColumns;

	SetName(pANDLayout->GetName());
	SetTitle(pANDLayout->GetTitle());
	pANDLayout->GetColumns(nColumns);
	SetColumns(nColumns);
}

BOOL CSCOS2000DatabaseANDDirectoryRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseANDDirectoryRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckTitle();
		CheckColumns();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckColumns(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseANDDirectoryRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDName((m_szNumbe = ExtractText(m_szNumbe))))
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

BOOL CSCOS2000DatabaseANDDirectoryRecordset::CheckTitle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDTitle((m_szHead = ExtractText(m_szHead))))
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

BOOL CSCOS2000DatabaseANDDirectoryRecordset::CheckColumns(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDColumns((m_szType = ExtractText(m_szType))))
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

void CSCOS2000DatabaseANDDirectoryRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseANDDirectoryRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPF_NUMBE)), m_szNumbe);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPF_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPF_HEAD)), m_szHead);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseANDParametersRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseANDParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseANDParametersRecordset::CSCOS2000DatabaseANDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseANDParametersRecordset)
	m_szNumbe.Empty();
	m_szName.Empty();
	m_szMode.Empty();
	m_szForm.Empty();
	m_szText.Empty();
	m_nFldn = 0;
	m_nComm = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseANDParametersRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbe = pszName;
}

CString CSCOS2000DatabaseANDParametersRecordset::GetName() CONST
{
	return m_szNumbe;
}

VOID CSCOS2000DatabaseANDParametersRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szName = pszTag;
}

CString CSCOS2000DatabaseANDParametersRecordset::GetParameter() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseANDParametersRecordset::SetComment(LPCTSTR pszComment)
{
	m_szText = pszComment;
}

CString CSCOS2000DatabaseANDParametersRecordset::GetComment() CONST
{
	return m_szText;
}

VOID CSCOS2000DatabaseANDParametersRecordset::SetMode(ULONGLONG nMode)
{
	m_szMode = GetDatabaseEngine()->TranslateANDParameterDisplayFlag(TRUE);
	m_szForm = GetDatabaseEngine()->TranslateANDParameterMode(nMode);
}

ULONGLONG CSCOS2000DatabaseANDParametersRecordset::GetMode() CONST
{
	return GetDatabaseEngine()->TranslateANDParameterMode(m_szForm);
}

VOID CSCOS2000DatabaseANDParametersRecordset::SetPosition(INT nPosition)
{
	m_nFldn = nPosition;
}

INT CSCOS2000DatabaseANDParametersRecordset::GetPosition() CONST
{
	return m_nFldn;
}

VOID CSCOS2000DatabaseANDParametersRecordset::SetOccurrence(INT nOccurrence)
{
	m_nComm = nOccurrence;
}

INT CSCOS2000DatabaseANDParametersRecordset::GetOccurrence() CONST
{
	return m_nComm;
}

VOID CSCOS2000DatabaseANDParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbe), pszError);
}
VOID CSCOS2000DatabaseANDParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseANDParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbe), pszWarning);
}
VOID CSCOS2000DatabaseANDParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseANDParametersRecordset::Translate(CONST CANDLayout *pANDLayout, CONST CANDLayoutParameter *pANDLayoutParameter)
{
	SetName(pANDLayout->GetName());
	SetParameter(pANDLayoutParameter->GetName());
	SetComment(pANDLayoutParameter->GetComment());
	SetMode(pANDLayoutParameter->GetAttributes());
	SetOccurrence(pANDLayoutParameter->GetOccurrence());
	SetPosition(SCOS2000_AND_COLUMNSIZE*pANDLayoutParameter->GetColumn() + pANDLayoutParameter->GetRow());
	return((!pANDLayoutParameter->GetName().IsEmpty() || !pANDLayoutParameter->GetComment().IsEmpty()) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseANDParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseANDParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckParameter();
		CheckComment();
		CheckMode();
		CheckPosition();
		CheckOccurrence();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		for (bCheck = CheckName(IsCollectingIssues()); !CheckParameter(FALSE) && !CheckComment(FALSE); )
		{
			bCheck &= CheckParameter(IsCollectingIssues());
			break;
		}
		bCheck &= CheckMode(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckOccurrence(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseANDParametersRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDName((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALNAME), (LPCTSTR)GetName(), (!ExtractText(m_szName).IsEmpty()) ? (LPCTSTR)ExtractText(m_szName) : (LPCTSTR)ExtractText(m_szText)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseANDParametersRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterTag((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseANDParametersRecordset::CheckComment(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterComment((m_szText = ExtractText(m_szText))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALCOMMENT), (LPCTSTR)GetName(), (!ExtractText(m_szName).IsEmpty()) ? (LPCTSTR)ExtractText(m_szName) : (LPCTSTR)ExtractText(m_szText)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseANDParametersRecordset::CheckMode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterMode(ExtractText(m_szName), m_szForm))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALFORMAT), (LPCTSTR)GetName(), (!ExtractText(m_szName).IsEmpty()) ? (LPCTSTR)ExtractText(m_szName) : (LPCTSTR)ExtractText(m_szText)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckANDParameterDisplayFlag(ExtractText(m_szName), m_szMode))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALMODE), (LPCTSTR)GetName(), (!ExtractText(m_szName).IsEmpty()) ? (LPCTSTR)ExtractText(m_szName) : (LPCTSTR)ExtractText(m_szText)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseANDParametersRecordset::CheckPosition(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterRow(m_nFldn%SCOS2000_AND_COLUMNSIZE) || !GetDatabaseEngine()->CheckANDParameterCol(m_nFldn / SCOS2000_AND_COLUMNSIZE))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALPOSITION), (LPCTSTR)GetName(), (!ExtractText(m_szName).IsEmpty()) ? (LPCTSTR)ExtractText(m_szName) : (LPCTSTR)ExtractText(m_szText)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseANDParametersRecordset::CheckOccurrence(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckANDParameterOccurrence(ExtractText(m_szName), m_nComm))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_ANDPARAMETER_ILLEGALOCCURRENCE), (LPCTSTR)GetName(), (!ExtractText(m_szName).IsEmpty()) ? (LPCTSTR)ExtractText(m_szName) : (LPCTSTR)ExtractText(m_szText)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseANDParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseANDParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPC_NUMBE)), m_szNumbe);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPC_NAME)), m_szName);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPC_FLDN)), m_nFldn);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPC_COMM)), m_nComm);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPC_MODE)), m_szMode);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPC_FORM)), m_szForm);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_DPC_TEXT)), m_szText);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseGRDDirectoryRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseGRDDirectoryRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseGRDDirectoryRecordset::CSCOS2000DatabaseGRDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseGRDDirectoryRecordset)
	m_szNumbe.Empty();
	m_szType.Empty();
	m_szHead.Empty();
	m_szScrol.Empty();
	m_szHCopy.Empty();
	m_szAxclr.Empty();
	m_nDays = 0;
	m_nHours = 0;
	m_nMinut = 0;
	m_nXTick = 0;
	m_nYTick = 0;
	m_nXGrid = 0;
	m_nYGrid = 0;
	m_nUpun = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbe = pszName;
}

CString CSCOS2000DatabaseGRDDirectoryRecordset::GetName() CONST
{
	return m_szNumbe;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetTitle(LPCTSTR pszTitle)
{
	m_szHead = pszTitle;
}

CString CSCOS2000DatabaseGRDDirectoryRecordset::GetTitle() CONST
{
	return m_szHead;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetType(INT nType)
{
	m_szType = GetDatabaseEngine()->TranslateGRDType(nType);
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetType() CONST
{
	return GetDatabaseEngine()->TranslateGRDType(m_szType);
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetMode(INT nMode)
{
	m_szScrol = GetDatabaseEngine()->TranslateGRDPlotMode(nMode);
	m_szHCopy = GetDatabaseEngine()->TranslateGRDHardcopyMode(FALSE);
	m_nUpun = 0;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetMode() CONST
{
	return GetDatabaseEngine()->TranslateGRDPlotMode(m_szScrol);
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetDays(INT nDays)
{
	m_nDays = nDays;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetDays() CONST
{
	return m_nDays;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetHours(INT nHours)
{
	m_nHours = nHours;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetHours() CONST
{
	return m_nHours;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetMinutes(INT nMinutes)
{
	m_nMinut = nMinutes;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetMinutes() CONST
{
	return m_nMinut;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetAxisColor(INT nColor)
{
	m_szAxclr = GetDatabaseEngine()->TranslateGRDAxisColor(nColor);
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetAxisColor() CONST
{
	return GetDatabaseEngine()->TranslateGRDAxisColor(m_szAxclr);
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetXGrids(INT nGrids)
{
	m_nXGrid = nGrids;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetXGrids() CONST
{
	return m_nXGrid;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetYGrids(INT nGrids)
{
	m_nYGrid = nGrids;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetYGrids() CONST
{
	return m_nYGrid;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetXTicks(INT nTicks)
{
	m_nXTick = nTicks;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetXTicks() CONST
{
	return m_nXTick;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::SetYTicks(INT nTicks)
{
	m_nYTick = nTicks;
}

INT CSCOS2000DatabaseGRDDirectoryRecordset::GetYTicks() CONST
{
	return m_nYTick;
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbe), pszError);
}
VOID CSCOS2000DatabaseGRDDirectoryRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbe), pszWarning);
}
VOID CSCOS2000DatabaseGRDDirectoryRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabaseGRDDirectoryRecordset::Translate(CONST CGRDLayout *pGRDLayout)
{
	INT  nGrids[2];
	INT  nTicks[2];

	SetName(pGRDLayout->GetName());
	SetTitle(pGRDLayout->GetTitle());
	SetType(pGRDLayout->GetType());
	SetMode(pGRDLayout->GetMode());
	SetDays((INT)pGRDLayout->GetDuration().GetDays());
	SetHours((INT)pGRDLayout->GetDuration().GetHours());
	SetMinutes((INT)pGRDLayout->GetDuration().GetMinutes());
	SetAxisColor(pGRDLayout->GetLabelColor());
	pGRDLayout->GetGrids(nGrids[0], nGrids[1]);
	pGRDLayout->GetTicks(nTicks[0], nTicks[1]);
	SetXGrids(nGrids[0]);
	SetYGrids(nGrids[1]);
	SetXTicks(nTicks[0]);
	SetYTicks(nTicks[1]);
}

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseGRDDirectoryRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckTitle();
		CheckType();
		CheckMode();
		CheckDays();
		CheckHours();
		CheckMinutes();
		CheckAxisColor();
		CheckXGrids();
		CheckYGrids();
		CheckXTicks();
		CheckYTicks();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckType(IsCollectingIssues());
		bCheck &= CheckMode(IsCollectingIssues());
		bCheck &= CheckDays(IsCollectingIssues());
		bCheck &= CheckHours(IsCollectingIssues());
		bCheck &= CheckMinutes(IsCollectingIssues());
		bCheck &= CheckAxisColor(IsCollectingIssues());
		bCheck &= CheckXGrids(IsCollectingIssues());
		bCheck &= CheckYGrids(IsCollectingIssues());
		bCheck &= CheckXTicks(IsCollectingIssues());
		bCheck &= CheckYTicks(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDName((m_szNumbe = ExtractText(m_szNumbe))))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckTitle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDTitle((m_szHead = ExtractText(m_szHead))))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckType(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDType((m_szType = ExtractText(m_szType))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRD_ILLEGALTYPE), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckMode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDPlotMode(m_szType, (m_szScrol = ExtractText(m_szScrol))))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckDays(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDDurationDays(m_nDays, m_nHours, m_nMinut))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckHours(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDDurationHours(m_nDays, m_nHours, m_nMinut))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckMinutes(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDDurationMinutes(m_nDays, m_nHours, m_nMinut))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckAxisColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDAxisColor(GetDatabaseEngine()->TranslateGRDAxisColor((m_szAxclr = ExtractText(m_szAxclr)))))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckXGrids(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDXGrids(m_szType, m_nXGrid))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckYGrids(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDYGrids(m_szType, m_nYGrid))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckXTicks(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDXTicks(m_nXTick))
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

BOOL CSCOS2000DatabaseGRDDirectoryRecordset::CheckYTicks(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDYTicks(m_nYTick))
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

void CSCOS2000DatabaseGRDDirectoryRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseGRDDirectoryRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_NUMBE)), m_szNumbe);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_TYPE)), m_szType);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_HEAD)), m_szHead);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_SCROL)), m_szScrol);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_HCOPY)), m_szHCopy);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_DAYS)), m_nDays);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_HOURS)), m_nHours);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_MINUT)), m_nMinut);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_AXCLR)), m_szAxclr);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_XTICK)), m_nXTick);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_YTICK)), m_nYTick);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_XGRID)), m_nXGrid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_YGRID)), m_nYGrid);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPF_UPUN)), m_nUpun);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseGRDParametersRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabaseGRDParametersRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabaseGRDParametersRecordset::CSCOS2000DatabaseGRDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabaseGRDParametersRecordset)
	m_szNumbe.Empty();
	m_szWhere.Empty();
	m_szName.Empty();
	m_szRaw.Empty();
	m_szMinim.Empty();
	m_szMaxim.Empty();
	m_szPrclr.Empty();
	m_szSymbo.Empty();
	m_szLine.Empty();
	m_nPos = 0;
	m_nDomain = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbe = pszName;
}

CString CSCOS2000DatabaseGRDParametersRecordset::GetName() CONST
{
	return m_szNumbe;
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szName = pszTag;
}

CString CSCOS2000DatabaseGRDParametersRecordset::GetParameter() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetMode(ULONGLONG nMode)
{
	m_szRaw = GetDatabaseEngine()->TranslateGRDParameterMode(nMode);
}

ULONGLONG CSCOS2000DatabaseGRDParametersRecordset::GetMode() CONST
{
	return GetDatabaseEngine()->TranslateGRDParameterMode(m_szRaw);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetPosition(INT nPosition, BOOL bOrder)
{
	if (bOrder)
	{
		m_nPos = nPosition;
		return;
	}
	m_szWhere = GetDatabaseEngine()->TranslateGRDParameterPosition(nPosition);
}

INT CSCOS2000DatabaseGRDParametersRecordset::GetPosition(BOOL bOrder) CONST
{
	return((!bOrder) ? GetDatabaseEngine()->TranslateGRDParameterPosition(m_szWhere) : m_nPos);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetMinimum(double fMinimum)
{
	CStringTools  cStringTools;

	m_szMinim = (!isnan(fMinimum)) ? cStringTools.ConvertFloatToString(fMinimum) : EMPTYSTRING;
}

double CSCOS2000DatabaseGRDParametersRecordset::GetMinimum() CONST
{
	return((!m_szMinim.IsEmpty()) ? _ttof(m_szMinim) : NAN);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetMaximum(double fMaximum)
{
	CStringTools  cStringTools;

	m_szMaxim = (!isnan(fMaximum)) ? cStringTools.ConvertFloatToString(fMaximum) : EMPTYSTRING;
}

double CSCOS2000DatabaseGRDParametersRecordset::GetMaximum() CONST
{
	return((!m_szMinim.IsEmpty()) ? _ttof(m_szMaxim) : NAN);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetColor(INT nColor)
{
	m_szPrclr = GetDatabaseEngine()->TranslateGRDParameterColor(nColor);
}

INT CSCOS2000DatabaseGRDParametersRecordset::GetColor() CONST
{
	return GetDatabaseEngine()->TranslateGRDParameterColor(m_szPrclr);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetLineStyle(INT nStyle)
{
	m_szLine = GetDatabaseEngine()->TranslateGRDParameterLineSymbol(nStyle);
}

INT CSCOS2000DatabaseGRDParametersRecordset::GetLineStyle() CONST
{
	return GetDatabaseEngine()->TranslateGRDParameterLineStyle(m_szLine);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::SetLineSymbol(INT nSymbol)
{
	m_szSymbo = GetDatabaseEngine()->TranslateGRDParameterLineSymbol(nSymbol);
}

INT CSCOS2000DatabaseGRDParametersRecordset::GetLineSymbol() CONST
{
	return GetDatabaseEngine()->TranslateGRDParameterLineSymbol(m_szSymbo);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbe), pszError);
}
VOID CSCOS2000DatabaseGRDParametersRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabaseGRDParametersRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbe), pszWarning);
}
VOID CSCOS2000DatabaseGRDParametersRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::Translate(CONST CGRDLayout *pGRDLayout, CONST CGRDLayoutParameter *pGRDLayoutParameter, INT nPosition)
{
	double  fMinimum;
	double  fMaximum;

	for (SetName(pGRDLayout->GetName()), SetParameter(pGRDLayoutParameter->GetName()), SetMode(pGRDLayoutParameter->GetAttributes()), SetPosition(nPosition, TRUE), SetPosition(pGRDLayoutParameter->GetPosition(), FALSE), fMinimum = fMaximum = 0.0; pGRDLayoutParameter->GetRange(fMinimum, fMaximum) >= 0; )
	{
		SetMinimum(fMinimum);
		SetMaximum(fMaximum);
		break;
	}
	SetColor(pGRDLayoutParameter->GetColor());
	SetLineStyle(pGRDLayoutParameter->GetLineStyle());
	SetLineSymbol(pGRDLayoutParameter->GetLineSymbol());
	return((!pGRDLayoutParameter->GetName().IsEmpty()) ? TRUE : FALSE);
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabaseGRDParametersRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckParameter();
		CheckMode();
		CheckPosition();
		CheckMinimum();
		CheckMaximum();
		CheckColor();
		CheckLineStyle();
		CheckLineSymbol();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		bCheck &= CheckMode(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckMinimum(IsCollectingIssues());
		bCheck &= CheckMaximum(IsCollectingIssues());
		bCheck &= CheckColor(IsCollectingIssues());
		bCheck &= CheckLineStyle(IsCollectingIssues());
		bCheck &= CheckLineSymbol(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDName((m_szNumbe = ExtractText(m_szNumbe))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterTag((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckMode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterMode((m_szRaw = ExtractText(m_szRaw))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALMODE), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckPosition(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterPosition(m_nPos))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALPOSITION), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckGRDParameterPosition(GetDatabaseEngine()->TranslateGRDParameterPosition((m_szWhere = ExtractText(m_szWhere)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALPLOTAREA), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckMinimum(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterMinimum((m_szMinim = ExtractText(m_szMinim))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALMINIMUM), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckMaximum(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterMaximum((m_szMaxim = ExtractText(m_szMaxim))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALMAXIMUM), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckColor(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterColor(GetDatabaseEngine()->TranslateGRDParameterColor((m_szPrclr = ExtractText(m_szPrclr)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALCOLOR), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckLineStyle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterLineStyle((m_szLine = ExtractText(m_szLine))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALLINESTYLE), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabaseGRDParametersRecordset::CheckLineSymbol(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckGRDParameterLineSymbol((m_szSymbo = ExtractText(m_szSymbo))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_GRDPARAMETER_ILLEGALLINESYMBOL), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabaseGRDParametersRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabaseGRDParametersRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_NUMBE)), m_szNumbe);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_POS)), m_nPos);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_WHERE)), m_szWhere);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_RAW)), m_szRaw);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_MINIM)), m_szMinim);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_MAXIM)), m_szMaxim);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_PRCLR)), m_szPrclr);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_SYMBO)), m_szSymbo);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_LINE)), m_szLine);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_GPC_DOMAIN)), m_nDomain);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabasePODDirectoryRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabasePODDirectoryRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabasePODDirectoryRecordset::CSCOS2000DatabasePODDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabasePODDirectoryRecordset)
	m_szNumbe.Empty();
	m_szHead.Empty();
	m_nPar = 0;
	m_nUpun = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabasePODDirectoryRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbe = pszName;
}

CString CSCOS2000DatabasePODDirectoryRecordset::GetName() CONST
{
	return m_szNumbe;
}

VOID CSCOS2000DatabasePODDirectoryRecordset::SetTitle(LPCTSTR pszTitle)
{
	m_szHead = pszTitle;
}

CString CSCOS2000DatabasePODDirectoryRecordset::GetTitle() CONST
{
	return m_szHead;
}

VOID CSCOS2000DatabasePODDirectoryRecordset::SetParameterCount(INT nCount)
{
	m_nPar = nCount;
	m_nUpun = 1;
}

INT CSCOS2000DatabasePODDirectoryRecordset::GetParameterCount() CONST
{
	return m_nPar;
}

VOID CSCOS2000DatabasePODDirectoryRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbe), pszError);
}
VOID CSCOS2000DatabasePODDirectoryRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabasePODDirectoryRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbe), pszWarning);
}
VOID CSCOS2000DatabasePODDirectoryRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

VOID CSCOS2000DatabasePODDirectoryRecordset::Translate(CONST CPODLayout *pPODLayout)
{
	CStringArray  szParameters;

	SetName(pPODLayout->GetName());
	SetTitle(pPODLayout->GetTitle());
	SetParameterCount(pPODLayout->GetParameters(szParameters));
}

BOOL CSCOS2000DatabasePODDirectoryRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabasePODDirectoryRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckTitle();
		CheckParameterCount();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameterCount(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabasePODDirectoryRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODName((m_szNumbe = ExtractText(m_szNumbe))))
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

BOOL CSCOS2000DatabasePODDirectoryRecordset::CheckTitle(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODTitle((m_szHead = ExtractText(m_szHead))))
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

BOOL CSCOS2000DatabasePODDirectoryRecordset::CheckParameterCount(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODParameterPosition(m_nPar - 1))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_POD_ILLEGALPARAMETERCOUNT), (LPCTSTR)GetName()); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabasePODDirectoryRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabasePODDirectoryRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPF_NUMBE)), m_szNumbe);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPF_HEAD)), m_szHead);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPF_NPAR)), m_nPar);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPF_UPUN)), m_nUpun);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabasePODExpressionsRecordset recordset

IMPLEMENT_DYNAMIC(CSCOS2000DatabasePODExpressionsRecordset, CSCOS2000DatabaseRecordset)

CSCOS2000DatabasePODExpressionsRecordset::CSCOS2000DatabasePODExpressionsRecordset(CONST CDatabaseEngine *pDatabaseEngine) : CSCOS2000DatabaseRecordset(pDatabaseEngine)
{
	//{{AFX_FIELD_INIT(CSCOS2000DatabasePODExpressionsRecordset)
	m_szNumbe.Empty();
	m_szName.Empty();
	m_szUpdt.Empty();
	m_szMode.Empty();
	m_szForm.Empty();
	m_szBack.Empty();
	m_szFore.Empty();
	m_nPos = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
}

VOID CSCOS2000DatabasePODExpressionsRecordset::SetName(LPCTSTR pszName)
{
	m_szNumbe = pszName;
}

CString CSCOS2000DatabasePODExpressionsRecordset::GetName() CONST
{
	return m_szNumbe;
}

VOID CSCOS2000DatabasePODExpressionsRecordset::SetParameter(LPCTSTR pszTag)
{
	m_szName = pszTag;
}

CString CSCOS2000DatabasePODExpressionsRecordset::GetParameter() CONST
{
	return m_szName;
}

VOID CSCOS2000DatabasePODExpressionsRecordset::SetMode(ULONGLONG nMode)
{
	m_szForm = GetDatabaseEngine()->TranslatePODParameterMode(nMode);
	m_szMode = GetDatabaseEngine()->TranslatePODParameterDisplayFlag(TRUE);
	m_szFore = GetDatabaseEngine()->TranslatePODForegroundColor(VGA_COLOR_BLACK);
	m_szBack = GetDatabaseEngine()->TranslatePODBackgroundColor(VGA_COLOR_WHITE);
}

ULONGLONG CSCOS2000DatabasePODExpressionsRecordset::GetMode() CONST
{
	return GetDatabaseEngine()->TranslatePODParameterMode(m_szForm);
}

VOID CSCOS2000DatabasePODExpressionsRecordset::SetPosition(INT nPosition)
{
	m_nPos = nPosition;
}

INT CSCOS2000DatabasePODExpressionsRecordset::GetPosition() CONST
{
	return m_nPos;
}

VOID CSCOS2000DatabasePODExpressionsRecordset::SetScrollingFlag(INT nFlag)
{
	m_szUpdt = GetDatabaseEngine()->TranslatePODParameterUpdateWhenScrollFlag(nFlag);
}

INT CSCOS2000DatabasePODExpressionsRecordset::GetScrollingFlag() CONST
{
	return GetDatabaseEngine()->TranslatePODParameterUpdateWhenScrollFlag(m_szUpdt);
}

VOID CSCOS2000DatabasePODExpressionsRecordset::ShowError(LPCTSTR pszError)
{
	ShowError(ExtractText(m_szNumbe), pszError);
}
VOID CSCOS2000DatabasePODExpressionsRecordset::ShowError(LPCTSTR pszName, LPCTSTR pszError)
{
	CSCOS2000DatabaseRecordset::ShowError(pszName, pszName, DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE, pszError);
}

VOID CSCOS2000DatabasePODExpressionsRecordset::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(ExtractText(m_szNumbe), pszWarning);
}
VOID CSCOS2000DatabasePODExpressionsRecordset::ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning)
{
	CSCOS2000DatabaseRecordset::ShowWarning(pszName, pszName, DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE, pszWarning);
}

BOOL CSCOS2000DatabasePODExpressionsRecordset::Translate(CONST CPODLayout *pPODLayout, CONST CPODLayoutExpression *pPODLayoutExpression, INT nPosition)
{
	INT  nSample;
	CString  szParameter;
	ULONGLONG  nAttributes;

	for (SetName(pPODLayout->GetName()), SetPosition(nPosition); pPODLayoutExpression->GetParameter(szParameter, nSample, nAttributes); )
	{
		SetParameter(szParameter);
		SetMode(nAttributes);
		SetScrollingFlag(nSample);
		return TRUE;
	}
	return FALSE;
}

BOOL CSCOS2000DatabasePODExpressionsRecordset::Check(CStringArray &szIssues, BOOL bAppend)
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
BOOL CSCOS2000DatabasePODExpressionsRecordset::Check(UINT nOperation)
{
	BOOL  bCheck;

	if (nOperation == CFieldExchange::Fixup)
	{
		CheckName();
		CheckParameter();
		CheckMode();
		CheckPosition();
		CheckScrollingFlag();
		return TRUE;
	}
	if (nOperation == (UINT)-1)
	{
		bCheck = CheckName(IsCollectingIssues());
		bCheck &= CheckParameter(IsCollectingIssues());
		bCheck &= CheckMode(IsCollectingIssues());
		bCheck &= CheckPosition(IsCollectingIssues());
		bCheck &= CheckScrollingFlag(IsCollectingIssues());
		return bCheck;
	}
	return TRUE;
}

BOOL CSCOS2000DatabasePODExpressionsRecordset::CheckName(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODName((m_szNumbe = ExtractText(m_szNumbe))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALNAME), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabasePODExpressionsRecordset::CheckParameter(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODExpressionStack((m_szName = ExtractText(m_szName))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALPARAMETER), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabasePODExpressionsRecordset::CheckMode(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODParameterMode((m_szForm = ExtractText(m_szForm))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALFORMAT), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckPODParameterDisplayFlag((m_szMode = ExtractText(m_szMode))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALMODE), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckPODForegroundColor(GetDatabaseEngine()->TranslatePODForegroundColor((m_szFore = ExtractText(m_szFore)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALFOREGROUNDCOLOR), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	if (!GetDatabaseEngine()->CheckPODBackgroundColor(GetDatabaseEngine()->TranslatePODBackgroundColor((m_szBack = ExtractText(m_szBack)))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALBACKGROUNDCOLOR), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
	}
	return szMessage.IsEmpty();
}

BOOL CSCOS2000DatabasePODExpressionsRecordset::CheckPosition(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODParameterPosition(m_nPos))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALPOSITION), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CSCOS2000DatabasePODExpressionsRecordset::CheckScrollingFlag(BOOL bStatus)
{
	CString  szMessage;

	if (!GetDatabaseEngine()->CheckPODParameterUpdateWhenScrollFlag((m_szUpdt = ExtractText(m_szUpdt))))
	{
		for (szMessage.Format(STRING(IDS_DATABASE_COMPILEERROR_PODEXPRESSION_ILLEGALSCROLLINGFLAG), (LPCTSTR)GetName(), (LPCTSTR)ExtractText(m_szName)); bStatus; )
		{
			ShowError(szMessage);
			break;
		}
		return FALSE;
	}
	return TRUE;
}

void CSCOS2000DatabasePODExpressionsRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CSCOS2000DatabaseRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CSCOS2000DatabasePODExpressionsRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_NUMBE)), m_szNumbe);
	RFX_Int(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_POS)), m_nPos);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_NAME)), m_szName);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_UPDT)), m_szUpdt);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_MODE)), m_szMode);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_FORM)), m_szForm);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_BACK)), m_szBack);
	RFX_Text(pFX, ConstructFieldName(STRING(IDS_DATABASE_TABLE_SPC_FORE)), m_szFore);
	//}}AFX_FIELD_MAP
	Check(pFX->m_nOperation);
}
