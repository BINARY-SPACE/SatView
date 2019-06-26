// RECORDS.H : Records Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the database records related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/02/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __RECORDS_H__
#define __RECORDS_H__


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseRecordset recordset

class CALTELDatabaseRecordset : public CRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseRecordset)

	// Construction
public:
	CALTELDatabaseRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Attributes
private:
	BOOL  m_bIssues;
	BOOL  m_bErrors;
	BOOL  m_bWarnings;
	CStringArray  m_szIssues;
	CStringArray  m_szErrors;
	CStringArray  m_szWarnings;
	CStringArray  m_szNames[2];
	CStringArray  m_szInfos[2];
	CLongUIntArray  m_nComponents[2];
private:
	CONST CDatabaseEngine  *m_pDatabaseEngine;

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseRecordset, CRecordset)
	//}}AFX_FIELD

	// Operations
public:
	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszError);
	INT GetErrors(CStringArray &szErrors) CONST;
	INT GetErrors(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szErrors) CONST;
	VOID EnableErrors(BOOL bEnable = TRUE);
	VOID EnableErrorsByStatus(INT nStatus);
	INT GetErrorCount() CONST;
	VOID ResetErrors();
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszWarning);
	INT GetWarnings(CStringArray &szWarnings) CONST;
	INT GetWarnings(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szWarnings) CONST;
	VOID EnableWarnings(BOOL bEnable = TRUE);
	VOID EnableWarningsByStatus(INT nStatus);
	INT GetWarningCount() CONST;
	VOID ResetWarnings();
	VOID CollectIssues(BOOL bEnable = TRUE);
	INT CollectIssues(CStringArray &szIssues, BOOL bStop = TRUE);
	BOOL IsCollectingIssues() CONST;

protected:
	CString ConstructFieldName(LPCTSTR pszField) CONST;

	CString ExtractText(LPCTSTR pszField) CONST;

protected:
	CONST CDatabaseEngine *GetDatabaseEngine() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseRecordset)
public:
	virtual BOOL Open(UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, DWORD dwOptions = none);
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketsRecordset recordset

class CALTELDatabaseTMPacketsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMPacketsRecordset)

	// Construction
public:
	CALTELDatabaseTMPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMPacketsRecordset, CALTELDatabaseRecordset)
	CString  m_szTag;
	CString  m_szType;
	CString  m_szDescription;
	CString  m_szDetails;
	CString  m_szAPID;
	CString  m_szTMID;
	CString  m_szTMType;
	CString  m_sz3Disc;
	CString  m_szDataFieldHeader;
	CString  m_szEventIDParameter;
	CString  m_szTransmissionRetries;
	CString  m_szStatus;
	INT  m_nTransmissionRate;
	INT  m_nVirtualChannel;
	INT  m_bDataFieldHeader;
	INT  m_nDataSize;
	INT  m_bDataSize;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetDataFieldHeader(LPCTSTR pszHeader);
	CString GetDataFieldHeader() CONST;
	BOOL HasDataFieldHeader() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetTMID(INT nTMID);
	INT GetTMID() CONST;
	VOID SetTMType(INT nTMType);
	INT GetTMType() CONST;
	VOID Set3Disc(INT n3Disc);
	INT Get3Disc() CONST;
	VOID SetDataSize(INT nSize);
	INT GetDataSize() CONST;
	VOID SetTransmissionRate(INT nRate);
	INT GetTransmissionRate() CONST;
	VOID SetTransmissionRetries(INT nRetries);
	INT GetTransmissionRetries() CONST;
	VOID SetVirtualChannel(INT nChannel);
	INT GetVirtualChannel() CONST;
	VOID SetEventIDParameter(LPCTSTR pszTag);
	CString GetEventIDParameter() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckType(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckDetails(BOOL bStatus);
	BOOL CheckAPID(BOOL bStatus);
	BOOL CheckTMID(BOOL bStatus);
	BOOL CheckTMType(BOOL bStatus);
	BOOL Check3Disc(BOOL bStatus);
	BOOL CheckDataSize(BOOL bStatus);
	BOOL CheckTransmissionRate(BOOL bStatus);
	BOOL CheckTransmissionRetries(BOOL bStatus);
	BOOL CheckVirtualChannel(BOOL bStatus);
	BOOL CheckDataFieldHeaderName(BOOL bStatus);
	BOOL CheckDataFieldHeaderFlag(BOOL bStatus);
	BOOL CheckEventIDParameter(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMPacketsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketHeadersRecordset recordset

class CALTELDatabaseTMPacketHeadersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMPacketHeadersRecordset)

	// Construction
public:
	CALTELDatabaseTMPacketHeadersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMPacketHeadersRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	INT  m_bTMType;
	INT  m_nTMTypePos[2];
	INT  m_bTMID;
	INT  m_nTMIDPos[2];
	INT  m_b3Disc;
	INT  m_n3DiscPos[2];
	INT  m_bTimestamp;
	INT  m_nTimestampPos[2];
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTMTypePosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTMTypePosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTMIDPosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTMIDPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID Set3DiscPosition(INT nByte, INT nBit, INT nLength);
	BOOL Get3DiscPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTimestampPosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTimestampPosition(INT &nByte, INT &nBit, INT &nLength) CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckTMTypePosition(BOOL bStatus);
	BOOL CheckTMIDPosition(BOOL bStatus);
	BOOL Check3DiscPosition(BOOL bStatus);
	BOOL CheckTimestampPosition(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMPacketHeadersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketParametersRecordset recordset

class CALTELDatabaseTMPacketParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMPacketParametersRecordset)

	// Construction
public:
	CALTELDatabaseTMPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMPacketParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szTag;
	CString  m_szPacket;
	CString  m_szParameter;
	INT  m_nBytePos;
	INT  m_nBitPos;
	INT  m_nGroupCount;
	INT  m_nGroupInterval;
	INT  m_nOccurrenceCount;
	INT  m_nOccurrenceInterval;
	INT  m_nTime[2];
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetPacket(LPCTSTR pszTag);
	CString GetPacket() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetBytePos(INT nByte);
	INT GetBytePos() CONST;
	VOID SetBitPos(INT nBit);
	INT GetBitPos() CONST;
	VOID SetOccurrenceCount(INT nCount);
	INT GetOccurrenceCount() CONST;
	VOID SetOccurrenceInterval(INT nInterval);
	INT GetOccurrenceInterval() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckPacket(BOOL bStatus);
	BOOL CheckValidityParameter(BOOL bStatus);
	BOOL CheckBytePos(BOOL bStatus);
	BOOL CheckBitPos(BOOL bStatus);
	BOOL CheckOccurrenceCount(BOOL bStatus);
	BOOL CheckOccurrenceInterval(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMPacketParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMPacketStreamsRecordset recordset

class CALTELDatabaseTMPacketStreamsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMPacketStreamsRecordset)

	// Construction
public:
	CALTELDatabaseTMPacketStreamsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMPacketStreamsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szAPID;
	CString  m_szTMID;
	CString  m_szValidityParameter;
	INT  m_nPeriod;
	INT  m_nTimeout;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetTMID(INT nTMID);
	INT GetTMID() CONST;
	VOID SetPeriod(INT nPeriod);
	INT GetPeriod() CONST;
	VOID SetTimeout(INT nTimeout);
	INT GetTimeout() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckAPID(BOOL bStatus);
	BOOL CheckTMID(BOOL bStatus);
	BOOL CheckPeriod(BOOL bStatus);
	BOOL CheckTimeout(BOOL bStatus);
	BOOL CheckValidityParameter(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMPacketStreamsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPacketsRecordset recordset

class CALTELDatabaseTCPacketsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCPacketsRecordset)

	// Construction
public:
	CALTELDatabaseTCPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCPacketsRecordset, CALTELDatabaseRecordset)
	CString  m_szTag;
	CString  m_szType;
	CString  m_szDescription;
	CString  m_szDetails[2];
	CString  m_szAPID;
	CString  m_szStatus;
	INT  m_bDataFieldHeader;
	INT  m_nDataSize;
	INT  m_bDataSize;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetDataFieldHeaderFlag(BOOL bFlag);
	BOOL GetDataFieldHeaderFlag() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetDataSize(INT nSize);
	INT GetDataSize() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckType(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckDetails(BOOL bStatus);
	BOOL CheckAPID(BOOL bStatus);
	BOOL CheckDataSize(BOOL bStatus);
	BOOL CheckDataFieldHeaderFlag(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCPacketsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPacketParametersRecordset recordset

class CALTELDatabaseTCPacketParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCPacketParametersRecordset)

	// Construction
public:
	CALTELDatabaseTCPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCPacketParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szTag;
	CString  m_szPacket;
	CString  m_szDescription;
	CString  m_szType;
	CString  m_szFlag;
	CString  m_szRadix;
	CString  m_szCoding;
	CString  m_szConstValue;
	INT  m_nBitOffset;
	INT  m_nBitWidth;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetPacket(LPCTSTR pszTag);
	CString GetPacket() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckPacket(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckCoding(BOOL bStatus);
	BOOL CheckBitOffset(BOOL bStatus);
	BOOL CheckBitWidth(BOOL bStatus);
	BOOL CheckConstValue(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCPacketParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionsRecordset recordset

class CALTELDatabaseTCFunctionsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCFunctionsRecordset)

	// Construction
public:
	CALTELDatabaseTCFunctionsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCFunctionsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szType;
	CString  m_szTCType;
	CString  m_szDetails;
	CString  m_szDescription[3];
	CString  m_szTCPacket;
	CString  m_szTCID;
	CString  m_szSubSystem[2];
	CString  m_szEquipment[2];
	CString  m_szOperationalInfo;
	CString  m_szValidityConditions;
	CString  m_szAssociatedTelecommands;
	CString  m_szComplementaryTelecommands;
	CString  m_szDestinationSubSchedule;
	CString  m_szMissionPlannerEvent;
	CString  m_szVerifGroup[2];
	CString  m_szHazFlag;
	CString  m_szStatus;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetExtendedDescription(LPCTSTR pszDescription);
	CString GetExtendedDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetTCPacket(LPCTSTR pszTag);
	CString GetTCPacket() CONST;
	VOID SetTCID(INT nTCID);
	INT GetTCID() CONST;
	VOID SetDestinationSubSystem(LPCTSTR pszSubSystem);
	CString GetDestinationSubSystem() CONST;
	VOID SetDestinationSubSchedule(LPCTSTR pszSubSchedule);
	CString GetDestinationSubSchedule() CONST;
	VOID SetDestinationEquipment(LPCTSTR pszEquipment);
	CString GetDestinationEquipment() CONST;
	VOID SetRouterSubSystem(LPCTSTR pszSubSystem);
	CString GetRouterSubSystem() CONST;
	VOID SetRouterEquipment(LPCTSTR pszEquipment);
	CString GetRouterEquipment() CONST;
	VOID SetOperationalInfo(LPCTSTR pszInfo);
	CString GetOperationalInfo() CONST;
	VOID SetValidityConditions(LPCTSTR pszConditions);
	CString GetValidityConditions() CONST;
	VOID SetAssociatedTelecommands(LPCTSTR pszTelecommands);
	CString GetAssociatedTelecommands() CONST;
	VOID SetComplementaryTelecommands(LPCTSTR pszTelecommands);
	CString GetComplementaryTelecommands() CONST;
	VOID SetMissionPlannerEvent(LPCTSTR pszEvent);
	CString GetMissionPlannerEvent() CONST;
	VOID SetPreExeGroup(LPCTSTR pszGroup);
	CString GetPreExeGroup() CONST;
	VOID SetExeVerGroup(LPCTSTR pszGroup);
	CString GetExeVerGroup() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckExtendedDescription(BOOL bStatus);
	BOOL CheckDetails(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckTCPacket(BOOL bStatus);
	BOOL CheckTCID(BOOL bStatus);
	BOOL CheckDestinationSubSystem(BOOL bStatus);
	BOOL CheckDestinationSubSchedule(BOOL bStatus);
	BOOL CheckDestinationEquipment(BOOL bStatus);
	BOOL CheckRouterSubSystem(BOOL bStatus);
	BOOL CheckRouterEquipment(BOOL bStatus);
	BOOL CheckOperationalInfo(BOOL bStatus);
	BOOL CheckValidityConditions(BOOL bStatus);
	BOOL CheckAssociatedTelecommands(BOOL bStatus);
	BOOL CheckComplementaryTelecommands(BOOL bStatus);
	BOOL CheckMissionPlannerEvent(BOOL bStatus);
	BOOL CheckPreExeGroup(BOOL bStatus);
	BOOL CheckExeVerGroup(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCFunctionsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionElementsRecordset recordset

class CALTELDatabaseTCFunctionElementsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCFunctionElementsRecordset)

	// Construction
public:
	CALTELDatabaseTCFunctionElementsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCFunctionElementsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szFunction;
	CString  m_szDescription;
	CString  m_szType;
	CString  m_szFlag;
	CString  m_szRadix;
	CString  m_szConstValue;
	INT  m_nBitOffset;
	INT  m_nBitWidth;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetFunction(LPCTSTR pszFunction);
	CString GetFunction() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckFunction(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckBitOffset(BOOL bStatus);
	BOOL CheckBitWidth(BOOL bStatus);
	BOOL CheckConstValue(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCFunctionElementsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionBlocksRecordset recordset

class CALTELDatabaseTCFunctionBlocksRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCFunctionBlocksRecordset)

	// Construction
public:
	CALTELDatabaseTCFunctionBlocksRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCFunctionBlocksRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szInterpretation;
	INT  m_nByteOffset;
	INT  m_nMaxLength;
	//}}AFX_FIELD

	// Attributes
private:
	CString  m_szStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetByteOffset(INT nOffset);
	INT GetByteOffset() CONST;
	VOID SetMaxLength(INT nLength);
	INT GetMaxLength() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, UINT nType);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckByteOffset(BOOL bStatus);
	BOOL CheckMaxLength(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCFunctionBlocksRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCFunctionBlockElementsRecordset recordset

class CALTELDatabaseTCFunctionBlockElementsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCFunctionBlockElementsRecordset)

	// Construction
public:
	CALTELDatabaseTCFunctionBlockElementsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCFunctionBlockElementsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szFunction;
	CString  m_szInterpretation;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetFunction(LPCTSTR pszFunction);
	CString GetFunction() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, CONST CDatabaseTCFunctionBlockElement *pDatabaseTCFunctionBlockElement);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckFunction(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCFunctionBlockElementsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequencesRecordset recordset

class CALTELDatabaseTCSequencesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCSequencesRecordset)

	// Construction
public:
	CALTELDatabaseTCSequencesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCSequencesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szUser;
	CString  m_szDate[2];
	CString  m_szDescription;
	CString  m_szDocumentName;
	CString  m_szDocumentIssue;
	CString  m_szDestinationSubSchedule;
	CString  m_szMissionPlannerEvent;
	CString  m_szStatus;
	INT  m_nParameters;
	INT  m_nEntries;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUser(LPCTSTR pszUser);
	CString GetUser() CONST;
	VOID SetDate(CONST CTimeKey &tDate);
	CTimeKey GetDate() CONST;
	VOID SetDestinationSubSchedule(LPCTSTR pszSubSchedule);
	CString GetDestinationSubSchedule() CONST;
	VOID SetMissionPlannerEvent(LPCTSTR pszEvent);
	CString GetMissionPlannerEvent() CONST;
	VOID SetDocumentName(LPCTSTR pszName);
	CString GetDocumentName() CONST;
	VOID SetDocumentIssue(LPCTSTR pszIssue);
	CString GetDocumentIssue() CONST;
	VOID SetDocumentDate(CONST CTimeKey &tDate);
	CTimeKey GetDocumentDate() CONST;
	VOID SetParameterCount(INT nCount);
	INT GetParameterCount() CONST;
	VOID SetEntryCount(INT nCount);
	INT GetEntryCount() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckUser(BOOL bStatus);
	BOOL CheckDate(BOOL bStatus);
	BOOL CheckDestinationSubSchedule(BOOL bStatus);
	BOOL CheckMissionPlannerEvent(BOOL bStatus);
	BOOL CheckDocumentName(BOOL bStatus);
	BOOL CheckDocumentIssue(BOOL bStatus);
	BOOL CheckDocumentDate(BOOL bStatus);
	BOOL CheckParameterCount(BOOL bStatus);
	BOOL CheckEntryCount(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCSequencesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequenceParametersRecordset recordset

class CALTELDatabaseTCSequenceParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCSequenceParametersRecordset)

	// Construction
public:
	CALTELDatabaseTCSequenceParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCSequenceParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szSequence;
	CString  m_szTag;
	CString  m_szDescription;
	CString  m_szUnit;
	CString  m_szCoding;
	CString  m_szCategory;
	CString  m_szValueType;
	CString  m_szValueRadix;
	CString  m_szCalTable[2];
	CString  m_szOolTable[2];
	CString  m_szConstValue;
	INT  m_nPosition;
	INT  m_nBitWidth;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetSequence(LPCTSTR pszSequence);
	CString GetSequence() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetPosition(INT nPosition);
	INT GetPosition() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;
	VOID SetCalTable(LPCTSTR pszTable);
	CString GetCalTable() CONST;
	VOID SetOolTable(LPCTSTR pszTable);
	CString GetOolTable() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckSequence(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckUnit(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckPosition(BOOL bStatus);
	BOOL CheckBitWidth(BOOL bStatus);
	BOOL CheckCalTable(BOOL bStatus);
	BOOL CheckOolTable(BOOL bStatus);
	BOOL CheckConstValue(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCSequenceParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequenceEntriesRecordset recordset

class CALTELDatabaseTCSequenceEntriesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCSequenceEntriesRecordset)

	// Construction
public:
	CALTELDatabaseTCSequenceEntriesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCSequenceEntriesRecordset, CALTELDatabaseRecordset)
	CString  m_szSequence;
	CString  m_szName;
	CString  m_szType;
	CString  m_szTCType;
	CString  m_szDescription;
	CString  m_sz1Step;
	CString  m_szBlockMacro;
	CString  m_szBlockMember;
	CString  m_szGroupMember;
	CString  m_szRelDelta;
	CString  m_szExeTime;
	CString  m_szExeDelta;
	INT  m_nParameters;
	INT  m_nEntry;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetSequence(LPCTSTR pszSequence);
	CString GetSequence() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetEntry(INT nEntry);
	INT GetEntry() CONST;
	VOID SetAssociated1Step(LPCTSTR pszName);
	CString GetAssociated1Step() CONST;
	VOID SetBlockMembership(INT nMember);
	INT GetBlockMembership() CONST;
	VOID SetReleaseDeltaTime(DWORD dwDelta);
	DWORD GetReleaseDeltaTime() CONST;
	VOID SetExecutionTime(CONST CTimeTag &tTime);
	CTimeTag GetExecutionTime() CONST;
	VOID SetExecutionDeltaTime(DWORD dwDelta, BOOL bEarlier = FALSE);
	DWORD GetExecutionDeltaTime(BOOL &bEarlier) CONST;
	DWORD GetExecutionDeltaTime() CONST;
	BOOL IsEarlierExecutionDeltaTime() CONST;
	VOID SetParameterCount(INT nCount);
	INT GetParameterCount() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry, INT nEntry);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckSequence(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckEntry(BOOL bStatus);
	BOOL CheckAssociated1Step(BOOL bStatus);
	BOOL CheckBlockMembership(BOOL bStatus);
	BOOL CheckReleaseDeltaTime(BOOL bStatus);
	BOOL CheckExecutionTime(BOOL bStatus);
	BOOL CheckExecutionDeltaTime(BOOL bStatus);
	BOOL CheckParameterCount(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCSequenceEntriesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCSequenceEntryParametersRecordset recordset

class CALTELDatabaseTCSequenceEntryParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCSequenceEntryParametersRecordset)

	// Construction
public:
	CALTELDatabaseTCSequenceEntryParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCSequenceEntryParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szSequence;
	CString  m_szTag;
	CString  m_szDescription;
	CString  m_szValueType;
	CString  m_szValueRadix;
	CString  m_szConstValue;
	CString  m_szMemoryArea[2];
	INT  m_nBitOffset;
	INT  m_nEntry;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetSequence(LPCTSTR pszSequence);
	CString GetSequence() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetEntry(INT nEntry);
	INT GetEntry() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;
	VOID SetMemoryAreaName(LPCTSTR pszName);
	CString GetMemoryAreaName() CONST;
	VOID SetMemoryAreaVersion(LPCTSTR pszVersion);
	CString GetMemoryAreaVersion() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntryParameter *pDatabaseTCSequenceEntryParameter, INT nEntry);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckSequence(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckEntry(BOOL bStatus);
	BOOL CheckBitOffset(BOOL bStatus);
	BOOL CheckConstValue(BOOL bStatus);
	BOOL CheckMemoryAreaName(BOOL bStatus);
	BOOL CheckMemoryAreaVersion(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCSequenceEntryParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorsRecordset recordset

class CALTELDatabaseOBProcessorsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseOBProcessorsRecordset)

	// Construction
public:
	CALTELDatabaseOBProcessorsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseOBProcessorsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szPatchCommand;
	CString  m_szDumpCommand;
	CString  m_szDumpPacket;
	CString  m_szMasterImage;
	CString  m_szStatus;
	INT  m_nAddressRange[2][2];
	INT  m_tDumpInterval;
	INT  m_nDumpCount;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetPatchCommand(LPCTSTR pszCommand);
	CString GetPatchCommand() CONST;
	VOID SetDumpCommand(LPCTSTR pszCommand);
	CString GetDumpCommand() CONST;
	VOID SetDumpPacket(LPCTSTR pszPacket);
	CString GetDumpPacket() CONST;
	VOID SetDumpInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetDumpInterval() CONST;
	VOID SetDumpCount(INT nCount);
	INT GetDumpCount() CONST;
	VOID SetMasterImage(LPCTSTR pszImage);
	CString GetMasterImage() CONST;
	VOID SetAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress);
	BOOL GetAddressRange(UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckPatchCommand(BOOL bStatus);
	BOOL CheckDumpCommand(BOOL bStatus);
	BOOL CheckDumpPacket(BOOL bStatus);
	BOOL CheckDumpInterval(BOOL bStatus);
	BOOL CheckDumpCount(BOOL bStatus);
	BOOL CheckMasterImage(BOOL bStatus);
	BOOL CheckAddressRange(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseOBProcessorsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryImagesRecordset recordset

class CALTELDatabaseOBProcessorMemoryImagesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseOBProcessorMemoryImagesRecordset)

	// Construction
public:
	CALTELDatabaseOBProcessorMemoryImagesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseOBProcessorMemoryImagesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szVersion;
	CString  m_szData;
	INT  m_nAddress[2];
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetVersion(LPCTSTR pszVersion);
	CString GetVersion() CONST;
	VOID SetAddress(UINT nPage, UINT nAddress);
	BOOL GetAddress(UINT &nPage, UINT &nAddress) CONST;
	VOID SetData(LPCTSTR pszData);
	VOID SetData(CONST CByteArray &nData, CONST CByteArray &nMask);
	CString GetData() CONST;
	INT GetData(CByteArray &nData, CByteArray &nMask) CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, CONST CDatabaseOBProcessorMemoryImageBlock *pDatabaseOBProcessorMemoryImageBlock);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckVersion(BOOL bStatus);
	BOOL CheckAddress(BOOL bStatus);
	BOOL CheckData(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseOBProcessorMemoryImagesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreasRecordset recordset

class CALTELDatabaseOBProcessorMemoryAreasRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreasRecordset)

	// Construction
public:
	CALTELDatabaseOBProcessorMemoryAreasRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseOBProcessorMemoryAreasRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szProcessor;
	CString  m_szDescription;
	CString  m_szType;
	CString  m_szPatchCommand;
	CString  m_szDumpCommand;
	CString  m_szDumpPacket;
	CString  m_szPatchFlag;
	CString  m_szDumpFlag;
	CString  m_szUpdateFlag;
	CString  m_szInhibitFlag;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetProcessor(LPCTSTR pszProcessor);
	CString GetProcessor() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetPatchCommand(LPCTSTR pszCommand);
	CString GetPatchCommand() CONST;
	VOID SetDumpCommand(LPCTSTR pszCommand);
	CString GetDumpCommand() CONST;
	VOID SetDumpPacket(LPCTSTR pszPacket);
	CString GetDumpPacket() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckProcessor(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckPatchCommand(BOOL bStatus);
	BOOL CheckDumpCommand(BOOL bStatus);
	BOOL CheckDumpPacket(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseOBProcessorMemoryAreasRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset recordset

class CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset)

	// Construction
public:
	CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szProcessor;
	CString  m_szDescription;
	CString  m_szParameter[2];
	INT  m_nAddress[2];
	INT  m_nBitOffset;
	INT  m_nBitWidth;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetProcessor(LPCTSTR pszProcessor);
	CString GetProcessor() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetTMParameter(LPCTSTR pszTag);
	CString GetTMParameter() CONST;
	VOID SetTCParameter(LPCTSTR pszTag);
	CString GetTCParameter() CONST;
	VOID SetAddress(UINT nPage, UINT nAddress);
	BOOL GetAddress(UINT &nPage, UINT &nAddress) CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaBlock *pDatabaseOBProcessorMemoryAreaBlock);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckTMParameter(BOOL bStatus);
	BOOL CheckTCParameter(BOOL bStatus);
	BOOL CheckAddress(BOOL bStatus);
	BOOL CheckBitOffset(BOOL bStatus);
	BOOL CheckBitWidth(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseOBProcessorMemoryAreaBlocksRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset recordset

class CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset)

	// Construction
public:
	CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szProcessor;
	CString  m_szSeedValue;
	INT  m_nAddress[3];
	INT  m_nDestination;
	INT  m_nLength;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetProcessor(LPCTSTR pszProcessor);
	CString GetProcessor() CONST;
	VOID SetSeed(UINT nValue);
	UINT GetSeed() CONST;
	VOID SetLength(INT nLength);
	INT GetLength() CONST;
	VOID SetDestination(UINT nDestination);
	UINT GetDestination() CONST;
	VOID SetAddressRange(UINT nPage, UINT nStartAddress, UINT nEndAddress);
	BOOL GetAddressRange(UINT &nPage, UINT &nStartAddress, UINT &nEndAddress) CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaCheckSum *pDatabaseOBProcessorMemoryAreaCheckSum);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckProcessor(BOOL bStatus);
	BOOL CheckSeed(BOOL bStatus);
	BOOL CheckLength(BOOL bStatus);
	BOOL CheckDestination(BOOL bStatus);
	BOOL CheckAddressRange(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseOBProcessorMemoryAreaCheckSumsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset recordset

class CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset)

	// Construction
public:
	CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset, CALTELDatabaseRecordset)
	CString  m_szID;
	CString  m_szName;
	CString  m_szProcessor;
	CString  m_szDescription;
	CString  m_szLocation;
	CString  m_szVersion;
	CString  m_szDate;
	CString  m_szTime;
	CString  m_szFlag;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetProcessor(LPCTSTR pszProcessor);
	CString GetProcessor() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLocation(LPCTSTR pszLocation);
	CString GetLocation() CONST;
	VOID SetVersion(LPCTSTR pszVersion);
	CString GetVersion() CONST;
	VOID SetDate(LPCTSTR pszDate);
	CString GetDate() CONST;
	VOID SetTime(LPCTSTR pszTime);
	CString GetTime() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea, CONST CDatabaseOBProcessorMemoryAreaCatalogueEntry *pDatabaseOBProcessorMemoryAreaCatalogueEntry);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus);
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckLocation(BOOL bStatus);
	BOOL CheckVersion(BOOL bStatus);
	BOOL CheckDate(BOOL bStatus);
	BOOL CheckTime(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseOBProcessorMemoryAreaCataloguesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMParametersRecordset recordset

class CALTELDatabaseTMParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMParametersRecordset)

	// Construction
public:
	CALTELDatabaseTMParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szTag;
	CString  m_szDescription;
	CString  m_szUnit;
	CString  m_szValidity;
	CString  m_szCategory;
	CString  m_szNature;
	CString  m_szCoding;
	CString  m_szInterpretation;
	CString  m_szConsistency;
	CString  m_szConstValue;
	CString  m_szType;
	CString  m_szDetails;
	CString  m_szSubSystem[2];
	CString  m_szEquipment[2];
	CString  m_szAssociatedTelecommands;
	CString  m_szOperationalInfo;
	CString  m_szValidityConditions;
	CString  m_szDangerConditions;
	CString  m_szRelatedParameter;
	CString  m_szInterrogationInstruction;
	CString  m_szDerivation;
	CString  m_szTrigger;
	CString  m_szTriggerType;
	CString  m_szOBSType;
	CString  m_szStatus;
	INT  m_nBitWidth;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;
	VOID SetRelatedParameter(LPCTSTR pszParameter);
	CString GetRelatedParameter() CONST;
	VOID SetValidityParameter(LPCTSTR pszParameter);
	CString GetValidityParameter() CONST;
	VOID SetDerivationExpression(LPCTSTR pszExpression);
	CString GetDerivationExpression() CONST;
	VOID SetTriggerExpression(LPCTSTR pszTrigger);
	CString GetTriggerExpression() CONST;
	VOID SetSourceSubSystem(LPCTSTR pszSubSystem);
	CString GetSourceSubSystem() CONST;
	VOID SetSourceEquipment(LPCTSTR pszEquipment);
	CString GetSourceEquipment() CONST;
	VOID SetRouterSubSystem(LPCTSTR pszSubSystem);
	CString GetRouterSubSystem() CONST;
	VOID SetRouterEquipment(LPCTSTR pszEquipment);
	CString GetRouterEquipment() CONST;
	VOID SetOperationalInfo(LPCTSTR pszInfo);
	CString GetOperationalInfo() CONST;
	VOID SetDangerConditions(LPCTSTR pszConditions);
	CString GetDangerConditions() CONST;
	VOID SetValidityConditions(LPCTSTR pszConditions);
	CString GetValidityConditions() CONST;
	VOID SetAssociatedTelecommands(LPCTSTR pszTelecommands);
	CString GetAssociatedTelecommands() CONST;
	VOID SetInterrogationInstruction(UINT nInstruction);
	UINT GetInterrogationInstruction() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckDetails(BOOL bStatus);
	BOOL CheckUnit(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckBitWidth(BOOL bStatus);
	BOOL CheckConstValue(BOOL bStatus);
	BOOL CheckRelatedParameter(BOOL bStatus);
	BOOL CheckValidityParameter(BOOL bStatus);
	BOOL CheckTriggerExpression(BOOL bStatus);
	BOOL CheckDerivationExpression(BOOL bStatus);
	BOOL CheckSourceSubSystem(BOOL bStatus);
	BOOL CheckSourceEquipment(BOOL bStatus);
	BOOL CheckRouterSubSystem(BOOL bStatus);
	BOOL CheckRouterEquipment(BOOL bStatus);
	BOOL CheckOperationalInfo(BOOL bStatus);
	BOOL CheckDangerConditions(BOOL bStatus);
	BOOL CheckValidityConditions(BOOL bStatus);
	BOOL CheckAssociatedTelecommands(BOOL bStatus);
	BOOL CheckInterrogationInstruction(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumCalTablesRecordset recordset

class CALTELDatabaseTMNumCalTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMNumCalTablesRecordset)

	// Construction
public:
	CALTELDatabaseTMNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMNumCalTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szUnit;
	CString  m_szStatus;
	INT  m_nPoints;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckUnit(BOOL bStatus);
	BOOL CheckPoints(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMNumCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumCalTablePointsRecordset recordset

class CALTELDatabaseTMNumCalTablePointsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMNumCalTablePointsRecordset)

	// Construction
public:
	CALTELDatabaseTMNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMNumCalTablePointsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	double  m_fX;
	double  m_fY;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetX(double fX);
	double GetX() CONST;
	VOID SetY(double fY);
	double GetY() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CONST CDatabaseTMNumCalPoint *pDatabaseTMNumCalPoint);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckPoint(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMNumCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumCalTableAssociationsRecordset recordset

class CALTELDatabaseTMNumCalTableAssociationsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMNumCalTableAssociationsRecordset)

	// Construction
public:
	CALTELDatabaseTMNumCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMNumCalTableAssociationsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szParameter[2];
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckParameter(BOOL bStatus);
	BOOL CheckValidityParameter(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMNumCalTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtCalTablesRecordset recordset

class CALTELDatabaseTMTxtCalTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMTxtCalTablesRecordset)

	// Construction
public:
	CALTELDatabaseTMTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMTxtCalTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szStatus;
	INT  m_nPoints;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckPoints(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMTxtCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtCalTablePointsRecordset recordset

class CALTELDatabaseTMTxtCalTablePointsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMTxtCalTablePointsRecordset)

	// Construction
public:
	CALTELDatabaseTMTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMTxtCalTablePointsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szText;
	INT  m_nX1;
	INT  m_nX2;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetX1(INT nX1);
	INT GetX1() CONST;
	VOID SetX2(INT nX2);
	INT GetX2() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CONST CDatabaseTMTxtCalPoint *pDatabaseTMTxtCalPoint);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckPoint(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMTxtCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtCalTableAssociationsRecordset recordset

class CALTELDatabaseTMTxtCalTableAssociationsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMTxtCalTableAssociationsRecordset)

	// Construction
public:
	CALTELDatabaseTMTxtCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMTxtCalTableAssociationsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szParameter[2];
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckParameter(BOOL bStatus);
	BOOL CheckValidityParameter(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMTxtCalTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumOolTablesRecordset recordset

class CALTELDatabaseTMNumOolTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMNumOolTablesRecordset)

	// Construction
public:
	CALTELDatabaseTMNumOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMNumOolTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szInterpretation;
	CString  m_szCoding;
	CString  m_szRadix;
	CString  m_szStatus;
	INT  m_nChecks;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckCount(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMNumOolTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumOolTableLimitsRecordset recordset

class CALTELDatabaseTMNumOolTableLimitsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMNumOolTableLimitsRecordset)

	// Construction
public:
	CALTELDatabaseTMNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMNumOolTableLimitsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szLowLimit;
	CString  m_szHighLimit;
	INT  m_nOrder;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetOrder(INT nOrder);
	INT GetOrder() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLowLimit(double fLowLimit);
	double GetLowLimit() CONST;
	VOID SetHighLimit(double fHighLimit);
	double GetHighLimit() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CONST CDatabaseTMNumOolLimit *pDatabaseTMNumOolLimit);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckLimits(BOOL bStatus);
	BOOL CheckOrder(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMNumOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMNumOolTableAssociationsRecordset recordset

class CALTELDatabaseTMNumOolTableAssociationsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMNumOolTableAssociationsRecordset)

	// Construction
public:
	CALTELDatabaseTMNumOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMNumOolTableAssociationsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szParameter[2];
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckParameter(BOOL bStatus);
	BOOL CheckValidityParameter(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMNumOolTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtOolTablesRecordset recordset

class CALTELDatabaseTMTxtOolTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMTxtOolTablesRecordset)

	// Construction
public:
	CALTELDatabaseTMTxtOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMTxtOolTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szInterpretation;
	CString  m_szRadix;
	CString  m_szStatus;
	INT  m_nChecks;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckCount(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMTxtOolTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtOolTableLimitsRecordset recordset

class CALTELDatabaseTMTxtOolTableLimitsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMTxtOolTableLimitsRecordset)

	// Construction
public:
	CALTELDatabaseTMTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMTxtOolTableLimitsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szLowLimit;
	CString  m_szHighLimit;
	INT  m_nOrder;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetOrder(INT nOrder);
	INT GetOrder() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLowLimit(LPCTSTR pszLowLimit);
	CString GetLowLimit() CONST;
	VOID SetHighLimit(LPCTSTR pszHighLimit);
	CString GetHighLimit() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CONST CDatabaseTMTxtOolLimit *pDatabaseTMTxtOolLimit);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckLimits(BOOL bStatus);
	BOOL CheckOrder(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMTxtOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTMTxtOolTableAssociationsRecordset recordset

class CALTELDatabaseTMTxtOolTableAssociationsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTMTxtOolTableAssociationsRecordset)

	// Construction
public:
	CALTELDatabaseTMTxtOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTMTxtOolTableAssociationsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szParameter[2];
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckParameter(BOOL bStatus);
	BOOL CheckValidityParameter(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTMTxtOolTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParametersRecordset recordset

class CALTELDatabaseTCParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCParametersRecordset)

	// Construction
public:
	CALTELDatabaseTCParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szTag;
	CString  m_szDescription;
	CString  m_szUnit;
	CString  m_szCoding;
	CString  m_szCategory;
	CString  m_szCalTable[2];
	CString  m_szOolTable[2];
	CString  m_szStatus;
	INT  m_nBitWidth;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;
	VOID SetCalTable(LPCTSTR pszTable);
	CString GetCalTable() CONST;
	VOID SetOolTable(LPCTSTR pszTable);
	CString GetOolTable() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCParameter *pDatabaseTCParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckUnit(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckBitWidth(BOOL bStatus);
	BOOL CheckCalTable(BOOL bStatus);
	BOOL CheckOolTable(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumCalTablesRecordset recordset

class CALTELDatabaseTCNumCalTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCNumCalTablesRecordset)

	// Construction
public:
	CALTELDatabaseTCNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCNumCalTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szUnit;
	CString  m_szStatus;
	INT  m_nPoints;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckUnit(BOOL bStatus);
	BOOL CheckPoints(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCNumCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumCalTablePointsRecordset recordset

class CALTELDatabaseTCNumCalTablePointsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCNumCalTablePointsRecordset)

	// Construction
public:
	CALTELDatabaseTCNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCNumCalTablePointsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	double  m_fX;
	double  m_fY;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetX(double fX);
	double GetX() CONST;
	VOID SetY(double fY);
	double GetY() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, CONST CDatabaseTCNumCalPoint *pDatabaseTCNumCalPoint);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckPoint(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCNumCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtCalTablesRecordset recordset

class CALTELDatabaseTCTxtCalTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCTxtCalTablesRecordset)

	// Construction
public:
	CALTELDatabaseTCTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCTxtCalTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szStatus;
	INT  m_nPoints;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckPoints(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCTxtCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtCalTablePointsRecordset recordset

class CALTELDatabaseTCTxtCalTablePointsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCTxtCalTablePointsRecordset)

	// Construction
public:
	CALTELDatabaseTCTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCTxtCalTablePointsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szText;
	INT  m_nX1;
	INT  m_nX2;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetX1(INT nX1);
	INT GetX1() CONST;
	VOID SetX2(INT nX2);
	INT GetX2() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, CONST CDatabaseTCTxtCalPoint *pDatabaseTCTxtCalPoint);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckPoint(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCTxtCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumOolTablesRecordset recordset

class CALTELDatabaseTCNumOolTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCNumOolTablesRecordset)

	// Construction
public:
	CALTELDatabaseTCNumOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCNumOolTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szInterpretation;
	CString  m_szCoding;
	CString  m_szRadix;
	CString  m_szStatus;
	INT  m_nChecks;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckCount(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCNumOolTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCNumOolTableLimitsRecordset recordset

class CALTELDatabaseTCNumOolTableLimitsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCNumOolTableLimitsRecordset)

	// Construction
public:
	CALTELDatabaseTCNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCNumOolTableLimitsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szLowLimit;
	CString  m_szHighLimit;
	INT  m_nOrder;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetOrder(INT nOrder);
	INT GetOrder() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLowLimit(double fLowLimit);
	double GetLowLimit() CONST;
	VOID SetHighLimit(double fHighLimit);
	double GetHighLimit() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CONST CDatabaseTCNumOolLimit *pDatabaseTCNumOolLimit);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckLimits(BOOL bStatus);
	BOOL CheckOrder(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCNumOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtOolTablesRecordset recordset

class CALTELDatabaseTCTxtOolTablesRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCTxtOolTablesRecordset)

	// Construction
public:
	CALTELDatabaseTCTxtOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCTxtOolTablesRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szInterpretation;
	CString  m_szRadix;
	CString  m_szStatus;
	INT  m_nChecks;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckCount(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCTxtOolTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCTxtOolTableLimitsRecordset recordset

class CALTELDatabaseTCTxtOolTableLimitsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCTxtOolTableLimitsRecordset)

	// Construction
public:
	CALTELDatabaseTCTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCTxtOolTableLimitsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szLowLimit;
	CString  m_szHighLimit;
	INT  m_nOrder;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetOrder(INT nOrder);
	INT GetOrder() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLowLimit(LPCTSTR pszLowLimit);
	CString GetLowLimit() CONST;
	VOID SetHighLimit(LPCTSTR pszHighLimit);
	CString GetHighLimit() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CONST CDatabaseTCTxtOolLimit *pDatabaseTCTxtOolLimit);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckLimits(BOOL bStatus);
	BOOL CheckOrder(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCTxtOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPreExeGroupsRecordset recordset

class CALTELDatabaseTCPreExeGroupsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCPreExeGroupsRecordset)

	// Construction
public:
	CALTELDatabaseTCPreExeGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCPreExeGroupsRecordset, CALTELDatabaseRecordset)
	CString  m_szID;
	CString  m_szDescription;
	CString  m_szStatus;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCPreExeGroupsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCPreExeGroupParametersRecordset recordset

class CALTELDatabaseTCPreExeGroupParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCPreExeGroupParametersRecordset)

	// Construction
public:
	CALTELDatabaseTCPreExeGroupParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCPreExeGroupParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szID;
	CString  m_szTag;
	CString  m_szInterpretation;
	CString  m_szValue;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetValue(LPCTSTR pszValue);
	CString GetValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, CONST CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus);
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckValue(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCPreExeGroupParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCExeVerGroupsRecordset recordset

class CALTELDatabaseTCExeVerGroupsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCExeVerGroupsRecordset)

	// Construction
public:
	CALTELDatabaseTCExeVerGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCExeVerGroupsRecordset, CALTELDatabaseRecordset)
	CString  m_szID;
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szStatus;
	INT  m_nStages;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetStages(INT nStages);
	INT GetStages() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus);
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckStages(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCExeVerGroupsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCExeVerGroupParametersRecordset recordset

class CALTELDatabaseTCExeVerGroupParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCExeVerGroupParametersRecordset)

	// Construction
public:
	CALTELDatabaseTCExeVerGroupParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCExeVerGroupParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szID;
	CString  m_szTag;
	CString  m_szType;
	CString  m_szValue;
	CString  m_szInterpretation;
	CString  m_szEventIDPacket;
	INT  m_nTimeWindow;
	INT  m_nStage;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetStage(UINT nStageID);
	UINT GetStage() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetValue(LPCTSTR pszValue);
	CString GetValue() CONST;
	VOID SetTimeWindowInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetTimeWindowInterval() CONST;
	VOID SetEventIDPacket(LPCTSTR pszTag);
	CString GetEventIDPacket() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus);
	BOOL CheckTag(BOOL bStatus);
	BOOL CheckStage(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckValue(BOOL bStatus);
	BOOL CheckTimeWindowInterval(BOOL bStatus);
	BOOL CheckEventIDPacket(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCExeVerGroupParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParameterSetsRecordset recordset

class CALTELDatabaseTCParameterSetsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCParameterSetsRecordset)

	// Construction
public:
	CALTELDatabaseTCParameterSetsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCParameterSetsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szStatus;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckDescription(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCParameterSetsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParameterSetItemsRecordset recordset

class CALTELDatabaseTCParameterSetItemsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCParameterSetItemsRecordset)

	// Construction
public:
	CALTELDatabaseTCParameterSetItemsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCParameterSetItemsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szParameterSet;
	CString  m_szValueType;
	CString  m_szValueRadix;
	CString  m_szConstValue;
	INT  m_nBitOffset;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameterSet(LPCTSTR pszSet);
	CString GetParameterSet() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckParameterSet(BOOL bStatus);
	BOOL CheckAttributes(BOOL bStatus);
	BOOL CheckBitOffset(BOOL bStatus);
	BOOL CheckConstValue(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCParameterSetItemsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseTCParameterSetAssociationsRecordset recordset

class CALTELDatabaseTCParameterSetAssociationsRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseTCParameterSetAssociationsRecordset)

	// Construction
public:
	CALTELDatabaseTCParameterSetAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseTCParameterSetAssociationsRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szFunction;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetFunction(LPCTSTR pszFunction);
	CString GetFunction() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckFunction(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseTCParameterSetAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseANDDirectoryRecordset recordset

class CALTELDatabaseANDDirectoryRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseANDDirectoryRecordset)

	// Construction
public:
	CALTELDatabaseANDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseANDDirectoryRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szTitle;
	CString  m_szColumns;
	CString  m_szStatus;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetColumns(CONST CUIntArray &nColumns);
	INT GetColumns(CUIntArray &nColumns) CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CANDLayout *pANDLayout);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckTitle(BOOL bStatus);
	BOOL CheckColumns(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseANDDirectoryRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseANDParametersRecordset recordset

class CALTELDatabaseANDParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseANDParametersRecordset)

	// Construction
public:
	CALTELDatabaseANDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseANDParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szParameter;
	CString  m_szComment;
	CString  m_szAlignment;
	CString  m_szMode;
	INT  m_nRow;
	INT  m_nCol;
	INT  m_nOccurrence;
	INT  m_nColor;
	INT  m_nDigits;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetComment(LPCTSTR pszComment);
	CString GetComment() CONST;
	VOID SetMode(ULONGLONG nMode);
	ULONGLONG GetMode() CONST;
	VOID SetRow(INT nRow);
	INT GetRow() CONST;
	VOID SetCol(INT nCol);
	INT GetCol() CONST;
	VOID SetOccurrence(INT nOccurrence);
	INT GetOccurrence() CONST;
	VOID SetColor(INT nColor);
	INT GetColor() CONST;
	VOID SetDigits(INT nDigits);
	INT GetDigits() CONST;
	VOID SetAlignment(UINT nAlignment);
	UINT GetAlignment() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CANDLayout *pANDLayout, CONST CANDLayoutParameter *pANDLayoutParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckParameter(BOOL bStatus);
	BOOL CheckComment(BOOL bStatus);
	BOOL CheckRow(BOOL bStatus);
	BOOL CheckCol(BOOL bStatus);
	BOOL CheckMode(BOOL bStatus);
	BOOL CheckOccurrence(BOOL bStatus);
	BOOL CheckColor(BOOL bStatus);
	BOOL CheckDigits(BOOL bStatus);
	BOOL CheckAlignment(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseANDParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseGRDDirectoryRecordset recordset

class CALTELDatabaseGRDDirectoryRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseGRDDirectoryRecordset)

	// Construction
public:
	CALTELDatabaseGRDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseGRDDirectoryRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szTitle;
	CString  m_szType[2];
	CString  m_szMode;
	CString  m_szStatus;
	INT  m_nWidth;
	INT  m_nHeight;
	INT  m_nColumns;
	INT  m_nGrids[2];
	INT  m_nTicks[2];
	INT  m_nGridsWidth;
	INT  m_nTicksWidth;
	INT  m_nGridsColor;
	INT  m_nTicksColor;
	INT  m_nBkgndColor;
	INT  m_nLabelColor;
	INT  m_nDuration[3];
	INT  m_nInterval[2];
	INT  m_nParameters;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetColumns(CONST CUIntArray &nColumns);
	INT GetColumns(CUIntArray &nColumns) CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetMode(INT nMode);
	INT GetMode() CONST;
	VOID SetWidth(INT nWidth);
	INT GetWidth() CONST;
	VOID SetHeight(INT nHeight);
	INT GetHeight() CONST;
	VOID SetXGrids(INT nGrids);
	INT GetXGrids() CONST;
	VOID SetYGrids(INT nGrids);
	INT GetYGrids() CONST;
	VOID SetXTicks(INT nTicks);
	INT GetXTicks() CONST;
	VOID SetYTicks(INT nTicks);
	INT GetYTicks() CONST;
	VOID SetGridsWidth(INT nWidth);
	INT GetGridsWidth() CONST;
	VOID SetTicksWidth(INT nWidth);
	INT GetTicksWidth() CONST;
	VOID SetGridsColor(INT nColor);
	INT GetGridsColor() CONST;
	VOID SetTicksColor(INT nColor);
	INT GetTicksColor() CONST;
	VOID SetBkgndColor(INT nColor);
	INT GetBkgndColor() CONST;
	VOID SetLabelColor(INT nColor);
	INT GetLabelColor() CONST;
	VOID SetDays(INT nDays);
	INT GetDays() CONST;
	VOID SetHours(INT nHours);
	INT GetHours() CONST;
	VOID SetMinutes(INT nMinutes);
	INT GetMinutes() CONST;
	VOID SetInterval(INT nInterval);
	INT GetInterval() CONST;
	VOID SetUpdateInterval(INT nInterval);
	INT GetUpdateInterval() CONST;
	VOID SetParameters(INT nParameters);
	INT GetParameters() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CGRDLayout *pGRDLayout);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckTitle(BOOL bStatus);
	BOOL CheckType(BOOL bStatus);
	BOOL CheckSubType(BOOL bStatus);
	BOOL CheckMode(BOOL bStatus);
	BOOL CheckWidth(BOOL bStatus);
	BOOL CheckHeight(BOOL bStatus);
	BOOL CheckColumns(BOOL bStatus);
	BOOL CheckXGrids(BOOL bStatus);
	BOOL CheckYGrids(BOOL bStatus);
	BOOL CheckXTicks(BOOL bStatus);
	BOOL CheckYTicks(BOOL bStatus);
	BOOL CheckGridsWidth(BOOL bStatus);
	BOOL CheckTicksWidth(BOOL bStatus);
	BOOL CheckGridsColor(BOOL bStatus);
	BOOL CheckTicksColor(BOOL bStatus);
	BOOL CheckBkgndColor(BOOL bStatus);
	BOOL CheckLabelColor(BOOL bStatus);
	BOOL CheckDays(BOOL bStatus);
	BOOL CheckHours(BOOL bStatus);
	BOOL CheckMinutes(BOOL bStatus);
	BOOL CheckInterval(BOOL bStatus);
	BOOL CheckUpdateInterval(BOOL bStatus);
	BOOL CheckParameters(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseGRDDirectoryRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseGRDParametersRecordset recordset

class CALTELDatabaseGRDParametersRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabaseGRDParametersRecordset)

	// Construction
public:
	CALTELDatabaseGRDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabaseGRDParametersRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szMode;
	CString  m_szComment;
	CString  m_szParameter;
	CString  m_szLineStyle;
	CString  m_szLineSymbol;
	double  m_fMinimum;
	double  m_fMaximum;
	INT  m_nOccurrence;
	INT  m_nLineWidth;
	INT  m_nPosition;
	INT  m_nDigits;
	INT  m_nColor;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetComment(LPCTSTR pszComment);
	CString GetComment() CONST;
	VOID SetMode(ULONGLONG nMode);
	ULONGLONG GetMode() CONST;
	VOID SetMinimum(double fMinimum);
	double GetMinimum() CONST;
	VOID SetMaximum(double fMaximum);
	double GetMaximum() CONST;
	VOID SetOccurrence(INT nOccurrence);
	INT GetOccurrence() CONST;
	VOID SetColor(INT nColor);
	INT GetColor() CONST;
	VOID SetDigits(INT nDigits);
	INT GetDigits() CONST;
	VOID SetPosition(INT nPosition);
	INT GetPosition() CONST;
	VOID SetLineWidth(INT nWidth);
	INT GetLineWidth() CONST;
	VOID SetLineStyle(INT nStyle);
	INT GetLineStyle() CONST;
	VOID SetLineSymbol(INT nSymbol);
	INT GetLineSymbol() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CGRDLayout *pGRDLayout, CONST CGRDLayoutParameter *pGRDLayoutParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckParameter(BOOL bStatus);
	BOOL CheckComment(BOOL bStatus);
	BOOL CheckPosition(BOOL bStatus);
	BOOL CheckMode(BOOL bStatus);
	BOOL CheckMinimum(BOOL bStatus);
	BOOL CheckMaximum(BOOL bStatus);
	BOOL CheckOccurrence(BOOL bStatus);
	BOOL CheckColor(BOOL bStatus);
	BOOL CheckDigits(BOOL bStatus);
	BOOL CheckLineStyle(BOOL bStatus);
	BOOL CheckLineSymbol(BOOL bStatus);
	BOOL CheckLineWidth(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabaseGRDParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELDatabasePODDirectoryRecordset recordset

class CALTELDatabasePODDirectoryRecordset : public CALTELDatabaseRecordset
{
	DECLARE_DYNAMIC(CALTELDatabasePODDirectoryRecordset)

	// Construction
public:
	CALTELDatabasePODDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CALTELDatabasePODDirectoryRecordset, CALTELDatabaseRecordset)
	CString  m_szName;
	CString  m_szTitle;
	CString  m_szExpressionStack;
	CString  m_szParameters;
	CString  m_szFunctions;
	CString  m_szStatus;
	INT  m_nExpressionColor;
	INT  m_nParametersColor;
	INT  m_nFunctionsColor;
	INT  m_nColumns;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetColumns(UINT nColumns);
	UINT GetColumns() CONST;
	VOID SetExpressionStack(CONST CStringArray &szStack);
	INT GetExpressionStack(CStringArray &szStack, CByteArray &bFunctions, CByteArray &bOperators, CByteArray &bParameters, CByteArray &bNumbers) CONST;
	VOID SetExpressionColor(INT nColor);
	INT GetExpressionColor() CONST;
	VOID SetParameters(CONST CStringArray &szParameters);
	INT GetParameters(CStringArray &szParameters) CONST;
	VOID SetParametersColor(INT nColor);
	INT GetParametersColor() CONST;
	VOID SetFunctions(CONST CStringArray &szFunctions);
	INT GetFunctions(CStringArray &szFunctions) CONST;
	VOID SetFunctionsColor(INT nColor);
	INT GetFunctionsColor() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CPODLayout *pPODLayout);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus);
	BOOL CheckTitle(BOOL bStatus);
	BOOL CheckColumns(BOOL bStatus);
	BOOL CheckExpressionStack(BOOL bStatus);
	BOOL CheckExpressionColor(BOOL bStatus);
	BOOL CheckParameters(BOOL bStatus);
	BOOL CheckParametersColor(BOOL bStatus);
	BOOL CheckFunctions(BOOL bStatus);
	BOOL CheckFunctionsColor(BOOL bStatus);
	BOOL CheckStatus(BOOL bStatus);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELDatabasePODDirectoryRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////


#endif // __RECORDS_H__
