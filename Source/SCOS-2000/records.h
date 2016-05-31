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
* 2012/06/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __RECORDS_H__
#define __RECORDS_H__


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseRecordset recordset

class CSCOS2000DatabaseRecordset : public CRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseRecordset)

	// Construction
public:
	CSCOS2000DatabaseRecordset(CONST CDatabaseEngine *pDatabaseEngine);

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
	//{{AFX_FIELD(CSCOS2000DatabaseRecordset, CRecordset)
	//}}AFX_FIELD

	// Operations
public:
	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszError);
	INT GetErrors(CStringArray &szErrors) CONST;
	INT GetErrors(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szErrors) CONST;
	VOID EnableErrors(BOOL bEnable = TRUE);
	INT GetErrorCount() CONST;
	VOID ResetErrors();
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszWarning);
	INT GetWarnings(CStringArray &szWarnings) CONST;
	INT GetWarnings(CStringArray &szNames, CStringArray &szInfos, CLongUIntArray &nComponents, CStringArray &szWarnings) CONST;
	VOID EnableWarnings(BOOL bEnable = TRUE);
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
	//{{AFX_VIRTUAL(CSCOS2000DatabaseRecordset)
public:
	virtual BOOL Open(UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, DWORD dwOptions = none);
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseVersionsRecordset recordset

class CSCOS2000DatabaseVersionsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseVersionsRecordset)

	// Construction
public:
	CSCOS2000DatabaseVersionsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseVersionsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szComment;
	INT  m_nDomainID;
	INT  m_nRelease;
	INT  m_nIssue;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetComment(LPCTSTR pszComment);
	CString GetComment() CONST;
	VOID SetDomainID(INT nDomainID);
	INT GetDomainID() CONST;
	VOID SetRelease(INT nRelease);
	INT GetRelease() CONST;
	VOID SetIssue(INT nIssue);
	INT GetIssue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseVersion *pDatabaseVersion);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckComment(BOOL bStatus = TRUE);
	BOOL CheckDomainID(BOOL bStatus = TRUE);
	BOOL CheckRelease(BOOL bStatus = TRUE);
	BOOL CheckIssue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseVersionsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketIdentificationsRecordset recordset

class CSCOS2000DatabaseTMPacketIdentificationsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketIdentificationsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketIdentificationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketIdentificationsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szDescr;
	CString  m_szUnit;
	CString  m_szTime;
	CString  m_szValid;
	CString  m_szEvent;
	CString  m_szEvId;
	INT  m_nType;
	INT  m_nSType;
	INT  m_nAPID;
	INT  m_nPI1Val;
	INT  m_nPI2Val;
	INT  m_nSPID;
	INT  m_nTPSD;
	INT  m_nDfhSize;
	INT  m_nInter;
	INT  m_nCheck;
	//}}AFX_FIELD

	// Attributes
private:
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetSubType(INT nSubType);
	INT GetSubType() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetFirstIDValue(INT nValue);
	INT GetFirstIDValue() CONST;
	VOID SetSecondIDValue(INT nValue);
	INT GetSecondIDValue() CONST;
	VOID SetPacketID(UINT nID);
	VOID SetPacketID(LPCTSTR pszID);
	CString GetPacketID() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetContentID(INT nContentID);
	INT GetContentID() CONST;
	VOID SetDataFieldHeaderSize(INT nSize);
	INT GetDataFieldHeaderSize() CONST;
	VOID SetTimestampFlag(BOOL bFlag);
	BOOL GetTimestampFlag() CONST;
	VOID SetEventType(INT nType);
	INT GetEventType() CONST;
	VOID SetEventID(LPCTSTR pszID);
	CString GetEventID() CONST;
	VOID SetTransmissionRate(DWORD dwInterval);
	DWORD GetTransmissionRate() CONST;
	VOID SetCRCFlag(BOOL bEnable = TRUE);
	BOOL GetCRCFlag() CONST;
	VOID SetValid(BOOL bValid = TRUE);
	BOOL IsValid() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckSubType(BOOL bStatus = TRUE);
	BOOL CheckAPID(BOOL bStatus = TRUE);
	BOOL CheckFirstIDValue(BOOL bStatus = TRUE);
	BOOL CheckSecondIDValue(BOOL bStatus = TRUE);
	BOOL CheckPacketID(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckUnit(BOOL bStatus = TRUE);
	BOOL CheckContentID(BOOL bStatus = TRUE);
	BOOL CheckDataFieldHeaderSize(BOOL bStatus = TRUE);
	BOOL CheckTimestampFlag(BOOL bStatus = TRUE);
	BOOL CheckEventType(BOOL bStatus = TRUE);
	BOOL CheckEventID(BOOL bStatus = TRUE);
	BOOL CheckTransmissionRate(BOOL bStatus = TRUE);
	BOOL CheckCRCFlag(BOOL bStatus = TRUE);
	BOOL CheckValidityFlag(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketIdentificationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset recordset

class CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset, CSCOS2000DatabaseRecordset)
	INT  m_nType;
	INT  m_nSType;
	INT  m_nAPID;
	INT  m_nPI1Off;
	INT  m_nPI1Wid;
	INT  m_nPI2Off;
	INT  m_nPI2Wid;
	//}}AFX_FIELD

	// Attributes
private:
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetSubType(INT nSubType);
	INT GetSubType() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetFirstIDOffset(INT nOffset);
	INT GetFirstIDOffset() CONST;
	VOID SetFirstIDWidth(INT nWidth);
	INT GetFirstIDWidth() CONST;
	VOID SetSecondIDOffset(INT nOffset);
	INT GetSecondIDOffset() CONST;
	VOID SetSecondIDWidth(INT nWidth);
	INT GetSecondIDWidth() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckSubType(BOOL bStatus = TRUE);
	BOOL CheckAPID(BOOL bStatus = TRUE);
	BOOL CheckFirstIDOffset(BOOL bStatus = TRUE);
	BOOL CheckFirstIDWidth(BOOL bStatus = TRUE);
	BOOL CheckSecondIDOffset(BOOL bStatus = TRUE);
	BOOL CheckSecondIDWidth(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketIdentificationCriteriaRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketsRecordset recordset

class CSCOS2000DatabaseTMPacketsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	INT  m_nSPID;
	INT  m_nSize;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetSize(INT nSize);
	INT GetSize() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus = TRUE);
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckSize(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketHeadersRecordset recordset

class CSCOS2000DatabaseTMPacketHeadersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketHeadersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketHeadersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketHeadersRecordset, CSCOS2000DatabaseRecordset)
	INT  m_nType;
	INT  m_nSType;
	INT  m_nAPID;
	INT  m_nTypeOff;
	INT  m_nTypeWid;
	INT  m_nSTypeOff;
	INT  m_nSTypeWid;
	INT  m_nTimeOff;
	INT  m_nTimeWid;
	//}}AFX_FIELD

	// Attributes
private:
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetSubType(INT nSubType);
	INT GetSubType() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetTypeOffset(INT nOffset);
	INT GetTypeOffset() CONST;
	VOID SetTypeWidth(INT nWidth);
	INT GetTypeWidth() CONST;
	VOID SetSubTypeOffset(INT nOffset);
	INT GetSubTypeOffset() CONST;
	VOID SetSubTypeWidth(INT nWidth);
	INT GetSubTypeWidth() CONST;
	VOID SetTimeOffset(INT nOffset);
	INT GetTimeOffset() CONST;
	VOID SetTimeWidth(INT nWidth);
	INT GetTimeWidth() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckSubType(BOOL bStatus = TRUE);
	BOOL CheckAPID(BOOL bStatus = TRUE);
	BOOL CheckTypeOffset(BOOL bStatus = TRUE);
	BOOL CheckTypeWidth(BOOL bStatus = TRUE);
	BOOL CheckSubTypeOffset(BOOL bStatus = TRUE);
	BOOL CheckSubTypeWidth(BOOL bStatus = TRUE);
	BOOL CheckTimeOffset(BOOL bStatus = TRUE);
	BOOL CheckTimeWidth(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketHeadersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketParametersRecordset recordset

class CSCOS2000DatabaseTMPacketParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szDisDesc;
	CString  m_szChoice;
	CString  m_szPidRef;
	CString  m_szJustify;
	CString  m_szNewLine;
	CString  m_szForm;
	INT  m_nSPID;
	INT  m_nTPSD;
	INT  m_nPos;
	INT  m_nGrpSize;
	INT  m_nFixRep;
	INT  m_nOffBy;
	INT  m_nOffBi;
	INT  m_nWidth;
	INT  m_nOffset;
	INT  m_nNbOcc;
	INT  m_nLgOcc;
	INT  m_nTime;
	INT  m_nTdOcc;
	INT  m_nDChar;
	//}}AFX_FIELD

	// Attributes
private:
	BOOL  m_bFixed;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetPacketID(LPCTSTR pszID);
	CString GetPacketID() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetContentID(INT nContentID);
	INT GetContentID() CONST;
	VOID SetBytePos(INT nByte);
	INT GetBytePos() CONST;
	VOID SetBitPos(INT nBit);
	INT GetBitPos() CONST;
	VOID SetWidth(INT nWidth);
	INT GetWidth() CONST;
	VOID SetOffset(INT nOffset);
	INT GetOffset() CONST;
	VOID SetOccurrence(INT nOccurrence);
	INT GetOccurrence() CONST;
	VOID SetOccurrenceCount(INT nCount);
	INT GetOccurrenceCount() CONST;
	VOID SetOccurrenceInterval(INT nInterval);
	INT GetOccurrenceInterval() CONST;
	VOID SetOccurrenceTimeOffset(INT nOffset);
	INT GetOccurrenceTimeOffset() CONST;
	VOID SetOccurrenceTimeInterval(INT nInterval);
	INT GetOccurrenceTimeInterval() CONST;
	VOID SetGroupSize(INT nSize);
	INT GetGroupSize() CONST;
	VOID SetGroupRepetitionCount(INT nCount);
	INT GetGroupRepetitionCount() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter);
	BOOL Translate(CONST CDatabaseTMPacket *pDatabaseTMPacket, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckPacketID(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckContentID(BOOL bStatus = TRUE);
	BOOL CheckBytePos(BOOL bStatus = TRUE);
	BOOL CheckBitPos(BOOL bStatus = TRUE);
	BOOL CheckWidth(BOOL bStatus = TRUE);
	BOOL CheckOffset(BOOL bStatus = TRUE);
	BOOL CheckOccurrence(BOOL bStatus = TRUE);
	BOOL CheckOccurrenceCount(BOOL bStatus = TRUE);
	BOOL CheckOccurrenceInterval(BOOL bStatus = TRUE);
	BOOL CheckOccurrenceTimeOffset(BOOL bStatus = TRUE);
	BOOL CheckOccurrenceTimeInterval(BOOL bStatus = TRUE);
	BOOL CheckGroupSize(BOOL bStatus = TRUE);
	BOOL CheckGroupRepetitionCount(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketParametersRecordset)
public:
	virtual BOOL Open(UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, DWORD dwOptions = none, BOOL bFixed = TRUE);
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketStreamsRecordset recordset

class CSCOS2000DatabaseTMPacketStreamsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketStreamsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketStreamsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketStreamsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szRlChk;
	INT  m_nType;
	INT  m_nSType;
	INT  m_nAPID;
	INT  m_nTimeout;
	INT  m_nValue;
	//}}AFX_FIELD

	// Attributes
private:
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetSubType(INT nSubType);
	INT GetSubType() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetTimeout(INT nTimeout);
	INT GetTimeout() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityValue(INT nValue);
	INT GetValidityValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckSubType(BOOL bStatus = TRUE);
	BOOL CheckAPID(BOOL bStatus = TRUE);
	BOOL CheckTimeout(BOOL bStatus = TRUE);
	BOOL CheckValidityParameter(BOOL bStatus = TRUE);
	BOOL CheckValidityValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketStreamsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketGroupsRecordset recordset

class CSCOS2000DatabaseTMPacketGroupsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketGroupsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketGroupsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szDescr;
	CString  m_szGType;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetType(INT nType = 0);
	INT GetType() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckType(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketGroupsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMPacketGroupMembersRecordset recordset

class CSCOS2000DatabaseTMPacketGroupMembersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMPacketGroupMembersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMPacketGroupMembersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMPacketGroupMembersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szGName;
	INT  m_nPKSPID;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetGroup(LPCTSTR pszName);
	CString GetGroup() CONST;
	VOID SetPacket(LPCTSTR pszPacket);
	CString GetPacket() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, LPCTSTR pszPacket);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckGroup(BOOL bStatus = TRUE);
	BOOL CheckPacketID(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMPacketGroupMembersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCFunctionsRecordset recordset

class CSCOS2000DatabaseTCFunctionsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCFunctionsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCFunctionsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCFunctionsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szCName;
	CString  m_szDescr;
	CString  m_szDescr2;
	CString  m_szCType;
	CString  m_szCritical;
	CString  m_szPktID;
	CString  m_szPlan;
	CString  m_szExec;
	CString  m_szILScope;
	CString  m_szILStage;
	CString  m_szHiPri;
	CString  m_szSubSys;
	CString  m_szDefSet;
	CString  m_szCorr;
	CString  m_szDarc;
	CString  m_szEndian;
	INT  m_nType;
	INT  m_nSType;
	INT  m_nAPID;
	INT  m_nNPars;
	INT  m_nSubSys;
	INT  m_nMapID;
	INT  m_nRAPID;
	INT  m_nAck;
	INT  m_nSubSchedID;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetAPID(INT nAPID, BOOL bRedundant = FALSE);
	INT GetAPID(BOOL bRedundant = FALSE) CONST;
	VOID SetServiceType(INT nType);
	INT GetServiceType() CONST;
	VOID SetServiceSubType(INT nSubType);
	INT GetServiceSubType() CONST;
	VOID SetMapID(INT nMapID);
	INT GetMapID() CONST;
	VOID SetTCPacket(LPCTSTR pszTag);
	CString GetTCPacket() CONST;
	VOID SetSubSystem(LPCTSTR pszSubSystem);
	CString GetSubSystem() CONST;
	VOID SetSubSchedule(LPCTSTR pszSubSchedule);
	CString GetSubSchedule() CONST;
	VOID SetParameterSet(LPCTSTR pszSet);
	CString GetParameterSet() CONST;
	VOID SetAcknowledgmentFlags(INT nFlags);
	INT GetAcknowledgmentFlags() CONST;
	VOID SetElementsCount(INT nCount);
	INT GetElementsCount() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckDetails(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckAPID(BOOL bStatus = TRUE);
	BOOL CheckServiceType(BOOL bStatus = TRUE);
	BOOL CheckServiceSubType(BOOL bStatus = TRUE);
	BOOL CheckMapID(BOOL bStatus = TRUE);
	BOOL CheckTCPacket(BOOL bStatus = TRUE);
	BOOL CheckSubSystem(BOOL bStatus = TRUE);
	BOOL CheckSubSchedule(BOOL bStatus = TRUE);
	BOOL CheckParameterSet(BOOL bStatus = TRUE);
	BOOL CheckAcknowledgmentFlags(BOOL bStatus = TRUE);
	BOOL CheckElementsCount(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCFunctionsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCFunctionElementsRecordset recordset

class CSCOS2000DatabaseTCFunctionElementsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCFunctionElementsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCFunctionElementsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCFunctionElementsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szCName;
	CString  m_szElType;
	CString  m_szDescr;
	CString  m_szPName;
	CString  m_szInter;
	CString  m_szValue;
	CString  m_szTMID;
	INT  m_nGrpSize;
	INT  m_nElLen;
	INT  m_nBit;
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
	VOID SetGroupSize(INT nSize);
	INT GetGroupSize() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;
	VOID SetConstValueSource(LPCTSTR pszParameter);
	CString GetConstValueSource() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckFunction(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckGroupSize(BOOL bStatus = TRUE);
	BOOL CheckBitWidth(BOOL bStatus = TRUE);
	BOOL CheckBitOffset(BOOL bStatus = TRUE);
	BOOL CheckConstValue(BOOL bStatus = TRUE);
	BOOL CheckConstValueSource(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCFunctionElementsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCPacketsRecordset recordset

class CSCOS2000DatabaseTCPacketsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCPacketsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCPacketsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCPacketsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szID;
	CString  m_szDesc;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCPacketsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCPacketParametersRecordset recordset

class CSCOS2000DatabaseTCPacketParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCPacketParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCPacketParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCPacketParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szTCName;
	CString  m_szDesc;
	CString  m_szType;
	CString  m_szPName;
	CString  m_szValue;
	CString  m_szCode;
	CString  m_szRadix;
	INT  m_nLen;
	INT  m_nBit;
	//}}AFX_FIELD

	// Attributes
private:
	BOOL  m_bHeader;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetPacketID(LPCTSTR pszID);
	CString GetPacketID() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBitWidth(INT nLength);
	INT GetBitWidth() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszTag, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszTag, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter);
	VOID Translate(CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckPacketID(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckBitWidth(BOOL bStatus = TRUE);
	BOOL CheckBitOffset(BOOL bStatus = TRUE);
	BOOL CheckConstValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCPacketParametersRecordset)
public:
	virtual BOOL Open(UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, DWORD dwOptions = none, BOOL bHeader = TRUE);
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequencesRecordset recordset

class CSCOS2000DatabaseTCSequencesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCSequencesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCSequencesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCSequencesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szDesc;
	CString  m_szDesc2;
	CString  m_szIFTT;
	CString  m_szCritical;
	CString  m_szPlan;
	CString  m_szExec;
	CString  m_szDefSet;
	CString  m_szGenTime;
	CString  m_szDocName;
	CString  m_szIssue;
	CString  m_szDate;
	INT  m_nSubSys;
	INT  m_nSubSchedID;
	INT  m_nNFPars;
	INT  m_nElems;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetSubSystem(LPCTSTR pszSubSystem);
	CString GetSubSystem() CONST;
	VOID SetSubSchedule(LPCTSTR pszSubSchedule);
	CString GetSubSchedule() CONST;
	VOID SetParameterSet(LPCTSTR pszSet);
	CString GetParameterSet() CONST;
	VOID SetDate(CONST CTimeKey &tDate);
	CTimeKey GetDate() CONST;
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

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckDetails(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckSubSystem(BOOL bStatus = TRUE);
	BOOL CheckSubSchedule(BOOL bStatus = TRUE);
	BOOL CheckParameterSet(BOOL bStatus = TRUE);
	BOOL CheckDate(BOOL bStatus = TRUE);
	BOOL CheckDocumentName(BOOL bStatus = TRUE);
	BOOL CheckDocumentIssue(BOOL bStatus = TRUE);
	BOOL CheckDocumentDate(BOOL bStatus = TRUE);
	BOOL CheckParameterCount(BOOL bStatus = TRUE);
	BOOL CheckEntryCount(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCSequencesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequenceParametersRecordset recordset

class CSCOS2000DatabaseTCSequenceParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCSequenceParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCSequenceParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCSequenceParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szSQName;
	CString  m_szFPName;
	CString  m_szDescr;
	CString  m_szDispFmt;
	CString  m_szRadix;
	CString  m_szType;
	CString  m_szVType;
	CString  m_szDefVal;
	CString  m_szCateg;
	CString  m_szPrfRef;
	CString  m_szCcaRef;
	CString  m_szPafRef;
	CString  m_szUnit;
	INT  m_nFPNum;
	INT  m_nPTC;
	INT  m_nPFC;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetSequence(LPCTSTR pszSequence);
	CString GetSequence() CONST;
	INT GetPosition() CONST;
	VOID SetCalTable(LPCTSTR pszTable);
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetTypeCode(UINT nPTC);
	UINT GetTypeCode() CONST;
	VOID SetFormatCode(UINT nPFC);
	UINT GetFormatCode() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes(INT &nWidth) CONST;
	ULONGLONG GetAttributes() CONST;
	VOID SetDisplayFormat(ULONGLONG nFormat);
	ULONGLONG GetDisplayFormat() CONST;
	VOID SetPosition(INT nPosition);
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
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckSequence(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckUnit(BOOL bStatus = TRUE);
	BOOL CheckTypeCode(BOOL bStatus = TRUE);
	BOOL CheckFormatCode(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckDisplayFormat(BOOL bStatus = TRUE);
	BOOL CheckCalTable(BOOL bStatus = TRUE);
	BOOL CheckOolTable(BOOL bStatus = TRUE);
	BOOL CheckConstValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCSequenceParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequenceEntriesRecordset recordset

class CSCOS2000DatabaseTCSequenceEntriesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCSequenceEntriesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCSequenceEntriesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCSequenceEntriesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szSQName;
	CString  m_szComm;
	CString  m_szType;
	CString  m_szElemID;
	CString  m_szManDisp;
	CString  m_szRelType;
	CString  m_szRelTime;
	CString  m_szExTime;
	CString  m_szPrevRel;
	CString  m_szGroup;
	CString  m_szBlock;
	CString  m_szILScope;
	CString  m_szILStage;
	CString  m_szDynPTV;
	CString  m_szStaPTV;
	CString  m_szCEV;
	INT  m_nEntry;
	INT  m_nNPars;
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
	VOID SetReleaseDeltaTime(DWORD dwDelta);
	DWORD GetReleaseDeltaTime() CONST;
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

	VOID Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry, INT nEntry);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckSequence(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckEntry(BOOL bStatus = TRUE);
	BOOL CheckReleaseDeltaTime(BOOL bStatus = TRUE);
	BOOL CheckExecutionDeltaTime(BOOL bStatus = TRUE);
	BOOL CheckParameterCount(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCSequenceEntriesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCSequenceEntryParametersRecordset recordset

class CSCOS2000DatabaseTCSequenceEntryParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCSequenceEntryParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCSequenceEntryParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCSequenceEntryParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szSQName;
	CString  m_szElemID;
	CString  m_szPName;
	CString  m_szFType;
	CString  m_szVType;
	CString  m_szValue;
	CString  m_szValSet;
	INT  m_nEntry;
	INT  m_nRepPos;
	INT  m_nPos;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetSequence(LPCTSTR pszSequence);
	CString GetSequence() CONST;
	VOID SetElement(LPCTSTR pszElement);
	CString GetElement() CONST;
	VOID SetEntry(INT nEntry);
	INT GetEntry() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetPosition(INT nPosition);
	INT GetPosition() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;
	VOID SetValueSet(LPCTSTR pszSet);
	CString GetValueSet() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, CONST CDatabaseTCSequenceEntryParameter *pDatabaseTCSequenceEntryParameter, INT nEntry);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckSequence(BOOL bStatus = TRUE);
	BOOL CheckElement(BOOL bStatus = TRUE);
	BOOL CheckEntry(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckBitOffset(BOOL bStatus = TRUE);
	BOOL CheckConstValue(BOOL bStatus = TRUE);
	BOOL CheckValueSet(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCSequenceEntryParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseOBProcessorsRecordset recordset

class CSCOS2000DatabaseOBProcessorsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseOBProcessorsRecordset)

	// Construction
public:
	CSCOS2000DatabaseOBProcessorsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseOBProcessorsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szPatchCommand;
	CString  m_szDumpCommand;
	CString  m_szDumpPacket;
	CString  m_szMasterImage;
	CString  m_szAddressBase;
	INT  m_nAddressRange[2][2];
	INT  m_tDumpInterval;
	INT  m_nDumpCount;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
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

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseOBProcessor *pDatabaseOBProcessor);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckPatchCommand(BOOL bStatus = TRUE);
	BOOL CheckDumpCommand(BOOL bStatus = TRUE);
	BOOL CheckDumpPacket(BOOL bStatus = TRUE);
	BOOL CheckDumpInterval(BOOL bStatus = TRUE);
	BOOL CheckDumpCount(BOOL bStatus = TRUE);
	BOOL CheckMasterImage(BOOL bStatus = TRUE);
	BOOL CheckAddressRange(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseOBProcessorsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseOBProcessorMemoryImagesRecordset recordset

class CSCOS2000DatabaseOBProcessorMemoryImagesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryImagesRecordset)

	// Construction
public:
	CSCOS2000DatabaseOBProcessorMemoryImagesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseOBProcessorMemoryImagesRecordset, CSCOS2000DatabaseRecordset)
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
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckVersion(BOOL bStatus = TRUE);
	BOOL CheckAddress(BOOL bStatus = TRUE);
	BOOL CheckData(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseOBProcessorMemoryImagesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseOBProcessorMemoryAreasRecordset recordset

class CSCOS2000DatabaseOBProcessorMemoryAreasRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreasRecordset)

	// Construction
public:
	CSCOS2000DatabaseOBProcessorMemoryAreasRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseOBProcessorMemoryAreasRecordset, CSCOS2000DatabaseRecordset)
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
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckProcessor(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckPatchCommand(BOOL bStatus = TRUE);
	BOOL CheckDumpCommand(BOOL bStatus = TRUE);
	BOOL CheckDumpPacket(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseOBProcessorMemoryAreasRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset recordset

class CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset)

	// Construction
public:
	CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset, CSCOS2000DatabaseRecordset)
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
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckTMParameter(BOOL bStatus = TRUE);
	BOOL CheckTCParameter(BOOL bStatus = TRUE);
	BOOL CheckAddress(BOOL bStatus = TRUE);
	BOOL CheckBitOffset(BOOL bStatus = TRUE);
	BOOL CheckBitWidth(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseOBProcessorMemoryAreaBlocksRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset recordset

class CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset)

	// Construction
public:
	CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset, CSCOS2000DatabaseRecordset)
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
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckProcessor(BOOL bStatus = TRUE);
	BOOL CheckSeed(BOOL bStatus = TRUE);
	BOOL CheckLength(BOOL bStatus = TRUE);
	BOOL CheckDestination(BOOL bStatus = TRUE);
	BOOL CheckAddressRange(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseOBProcessorMemoryAreaCheckSumsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset recordset

class CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset)

	// Construction
public:
	CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset, CSCOS2000DatabaseRecordset)
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
	BOOL CheckID(BOOL bStatus = TRUE);
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckLocation(BOOL bStatus = TRUE);
	BOOL CheckVersion(BOOL bStatus = TRUE);
	BOOL CheckDate(BOOL bStatus = TRUE);
	BOOL CheckTime(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseOBProcessorMemoryAreaCataloguesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMParametersRecordset recordset

class CSCOS2000DatabaseTMParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szDescr;
	CString  m_szUnit;
	CString  m_szValid;
	CString  m_szRelated;
	CString  m_szCateg;
	CString  m_szNatur;
	CString  m_szCurTx;
	CString  m_szInter;
	CString  m_szUsCon;
	CString  m_szParVal;
	CString  m_szSubSys;
	CString  m_szSpType;
	CString  m_szCorr;
	CString  m_szDarc;
	CString  m_szEndian;
	INT  m_nPID;
	INT  m_nPTC;
	INT  m_nPFC;
	INT  m_nWidth;
	INT  m_nDecim;
	INT  m_nValPar;
	INT  m_nOBTID;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetTypeCode(UINT nPTC);
	UINT GetTypeCode() CONST;
	VOID SetFormatCode(UINT nPFC);
	UINT GetFormatCode() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes(INT &nWidth) CONST;
	ULONGLONG GetAttributes() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;
	VOID SetValidityParameter(LPCTSTR pszParameter);
	CString GetValidityParameter() CONST;
	VOID SetValidityValue(INT nValue);
	INT GetValidityValue() CONST;
	VOID SetRelatedParameter(LPCTSTR pszParameter);
	CString GetRelatedParameter() CONST;
	VOID SetCalibrationTable(LPCTSTR pszTable);
	CString GetCalibrationTable() CONST;
	VOID SetOnBoardID(INT nPID);
	INT GetOnBoardID() CONST;
	VOID SetOnBoardTimerID(INT nOBTID);
	INT GetOnBoardTimerID() CONST;
	VOID SetSubSystem(LPCTSTR pszSubSystem);
	CString GetSubSystem() CONST;
	VOID SetDecimalDigits(INT nDigits);
	INT GetDecimalDigits() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckUnit(BOOL bStatus = TRUE);
	BOOL CheckTypeCode(BOOL bStatus = TRUE);
	BOOL CheckFormatCode(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckBitWidth(BOOL bStatus = TRUE);
	BOOL CheckConstValue(BOOL bStatus = TRUE);
	BOOL CheckValidityParameter(BOOL bStatus = TRUE);
	BOOL CheckValidityValue(BOOL bStatus = TRUE);
	BOOL CheckRelatedParameter(BOOL bStatus = TRUE);
	BOOL CheckCalibrationTable(BOOL bStatus = TRUE);
	BOOL CheckOnBoardID(BOOL bStatus = TRUE);
	BOOL CheckOnBoardTimerID(BOOL bStatus = TRUE);
	BOOL CheckSubSystem(BOOL bStatus = TRUE);
	BOOL CheckDecimalDigits(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMParameterGroupsRecordset recordset

class CSCOS2000DatabaseTMParameterGroupsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMParameterGroupsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMParameterGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMParameterGroupsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szDescr;
	CString  m_szGType;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetType(INT nType = 0);
	INT GetType() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckType(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMParameterGroupsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMParameterGroupMembersRecordset recordset

class CSCOS2000DatabaseTMParameterGroupMembersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMParameterGroupMembersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMParameterGroupMembersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMParameterGroupMembersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szGName;
	CString  m_szPAName;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetGroup(LPCTSTR pszName);
	CString GetGroup() CONST;
	VOID SetParameter(LPCTSTR pszParameter);
	CString GetParameter() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, LPCTSTR pszParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckGroup(BOOL bStatus = TRUE);
	BOOL CheckParameter(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMParameterGroupMembersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalTablesRecordset recordset

class CSCOS2000DatabaseTMNumCalTablesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMNumCalTablesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMNumCalTablesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szDescr;
	CString  m_szEngFmt;
	CString  m_szRawFmt;
	CString  m_szRadix;
	CString  m_szUnit;
	CString  m_szInter;
	INT  m_nNCurve;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckUnit(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckPoints(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMNumCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalTablePointsRecordset recordset

class CSCOS2000DatabaseTMNumCalTablePointsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMNumCalTablePointsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMNumCalTablePointsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szXVals;
	CString  m_szYVals;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
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
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckPoint(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMNumCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset recordset

class CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szIdent;
	CString  m_szDescr;
	CString  m_szPOL1;
	CString  m_szPOL2;
	CString  m_szPOL3;
	CString  m_szPOL4;
	CString  m_szPOL5;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetCoefficients(double fA1, double fA2, double fA3, double fA4, double fA5);
	BOOL GetCoefficients(double &fA1, double &fA2, double &fA3, double &fA4, double &fA5) CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckCoefficients(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMNumCalPolynomialCurvesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset recordset

class CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szIdent;
	CString  m_szDescr;
	CString  m_szPOL1;
	CString  m_szPOL2;
	CString  m_szPOL3;
	CString  m_szPOL4;
	CString  m_szPOL5;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetCoefficients(double fA1, double fA2, double fA3, double fA4, double fA5);
	BOOL GetCoefficients(double &fA1, double &fA2, double &fA3, double &fA4, double &fA5) CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckCoefficients(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMNumCalLogarithmicCurvesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumCalTableAssociationsRecordset recordset

class CSCOS2000DatabaseTMNumCalTableAssociationsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMNumCalTableAssociationsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMNumCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMNumCalTableAssociationsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szPName;
	CString  m_szRlChk;
	CString  m_szSelect;
	INT  m_nPos;
	INT  m_nValPar;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTable(LPCTSTR pszTable);
	CString GetTable() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetPosition(INT nPos);
	INT GetPosition() CONST;
	VOID SetValidityParameter(LPCTSTR pszParameter);
	CString GetValidityParameter() CONST;
	VOID SetValidityValue(INT nValue);
	INT GetValidityValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter, INT nValidityValue, INT nPosition);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTable(BOOL bStatus = TRUE);
	BOOL CheckParameter(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckValidityParameter(BOOL bStatus = TRUE);
	BOOL CheckValidityValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMNumCalTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtCalTablesRecordset recordset

class CSCOS2000DatabaseTMTxtCalTablesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMTxtCalTablesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMTxtCalTablesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szDescr;
	CString  m_szRawFmt;
	INT  m_nNAlias;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckPoints(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMTxtCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtCalTablePointsRecordset recordset

class CSCOS2000DatabaseTMTxtCalTablePointsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMTxtCalTablePointsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMTxtCalTablePointsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szFrom;
	CString  m_szTo;
	CString  m_szAlTxt;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetX1(double fX1);
	double GetX1() CONST;
	VOID SetX2(double fX2);
	double GetX2() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTxtCalTable, CONST CDatabaseTMTxtCalPoint *pDatabaseTMTxtCalPoint);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckPoint(BOOL bStatus = TRUE);
	BOOL CheckText(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMTxtCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset recordset

class CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szPName;
	CString  m_szRlChk;
	CString  m_szSelect;
	INT  m_nPos;
	INT  m_nValPar;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTable(LPCTSTR pszTable);
	CString GetTable() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetPosition(INT nPos);
	INT GetPosition() CONST;
	VOID SetValidityParameter(LPCTSTR pszParameter);
	CString GetValidityParameter() CONST;
	VOID SetValidityValue(INT nValue);
	INT GetValidityValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValidityParameter, INT nValidityValue, INT nPosition);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTable(BOOL bStatus = TRUE);
	BOOL CheckParameter(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckValidityParameter(BOOL bStatus = TRUE);
	BOOL CheckValidityValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMTxtCalTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumOolTableLimitsRecordset recordset

class CSCOS2000DatabaseTMNumOolTableLimitsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMNumOolTableLimitsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMNumOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szType;
	CString  m_szLValu;
	CString  m_szHValu;
	CString  m_szRlChk;
	INT  m_nValPar;
	INT  m_nPos;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetPosition(INT nPos);
	INT GetPosition() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLowLimit(double fLowLimit);
	double GetLowLimit() CONST;
	VOID SetHighLimit(double fHighLimit);
	double GetHighLimit() CONST;
	VOID SetValidityParameter(LPCTSTR pszParameter);
	CString GetValidityParameter() CONST;
	VOID SetValidityValue(INT nValue);
	INT GetValidityValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CONST CDatabaseTMNumOolLimit *pDatabaseTMNumOolLimit, INT nPosition);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckLowLimit(BOOL bStatus = TRUE);
	BOOL CheckHighLimit(BOOL bStatus = TRUE);
	BOOL CheckValidityParameter(BOOL bStatus = TRUE);
	BOOL CheckValidityValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMNumOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMNumOolTableAssociationsRecordset recordset

class CSCOS2000DatabaseTMNumOolTableAssociationsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMNumOolTableAssociationsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMNumOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMNumOolTableAssociationsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szInter;
	CString  m_szCodin;
	INT  m_nNBChck;
	INT  m_nNBOOLs;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTable(LPCTSTR pszName);
	CString GetTable() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetOOLChecks(INT nCount);
	INT GetOOLChecks() CONST;
	VOID SetLimitCount(INT nCount);
	INT GetLimitCount() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable);

	BOOL IsEmpty() CONST;

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTable(BOOL bStatus = TRUE);
	BOOL CheckOOLChecks(BOOL bStatus = TRUE);
	BOOL CheckLimitCount(BOOL bStatus = TRUE);
	BOOL CheckInterpretation(BOOL bStatus = TRUE);
	BOOL CheckCoding(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMNumOolTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtOolTableLimitsRecordset recordset

class CSCOS2000DatabaseTMTxtOolTableLimitsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMTxtOolTableLimitsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMTxtOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szType;
	CString  m_szLValu;
	CString  m_szHValu;
	CString  m_szRlChk;
	INT  m_nValPar;
	INT  m_nPos;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetPosition(INT nPos);
	INT GetPosition() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLowLimit(LPCTSTR pszLowLimit);
	CString GetLowLimit() CONST;
	VOID SetHighLimit(LPCTSTR pszHighLimit);
	CString GetHighLimit() CONST;
	VOID SetValidityParameter(LPCTSTR pszParameter);
	CString GetValidityParameter() CONST;
	VOID SetValidityValue(INT nValue);
	INT GetValidityValue() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CONST CDatabaseTMTxtOolLimit *pDatabaseTMTxtOolLimit, INT nPosition);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckLowLimit(BOOL bStatus = TRUE);
	BOOL CheckHighLimit(BOOL bStatus = TRUE);
	BOOL CheckValidityParameter(BOOL bStatus = TRUE);
	BOOL CheckValidityValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMTxtOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset recordset

class CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szInter;
	CString  m_szCodin;
	INT  m_nNBChck;
	INT  m_nNBOOLs;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTable(LPCTSTR pszName);
	CString GetTable() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetOOLChecks(INT nCount);
	INT GetOOLChecks() CONST;
	VOID SetLimitCount(INT nCount);
	INT GetLimitCount() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable);

	BOOL IsEmpty() CONST;

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTable(BOOL bStatus = TRUE);
	BOOL CheckOOLChecks(BOOL bStatus = TRUE);
	BOOL CheckLimitCount(BOOL bStatus = TRUE);
	BOOL CheckInterpretation(BOOL bStatus = TRUE);
	BOOL CheckCoding(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTMTxtOolTableAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParametersRecordset recordset

class CSCOS2000DatabaseTCParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szPName;
	CString  m_szDescr;
	CString  m_szDispFmt;
	CString  m_szRadix;
	CString  m_szUnit;
	CString  m_szCateg;
	CString  m_szPrfRef;
	CString  m_szCcaRef;
	CString  m_szPafRef;
	CString  m_szInter;
	CString  m_szDefVal;
	CString  m_szCorr;
	INT  m_nPTC;
	INT  m_nPFC;
	INT  m_nOBTID;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetTypeCode(UINT nPTC);
	UINT GetTypeCode() CONST;
	VOID SetFormatCode(UINT nPFC);
	UINT GetFormatCode() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes(INT &nWidth) CONST;
	ULONGLONG GetAttributes() CONST;
	VOID SetDisplayFormat(ULONGLONG nFormat);
	ULONGLONG GetDisplayFormat() CONST;
	VOID SetCalibrationTable(LPCTSTR pszTable, ULONGLONG nAttributes);
	CString GetCalibrationTable(ULONGLONG nAttributes) CONST;
	VOID SetOutOfLimitTable(LPCTSTR pszTable);
	CString GetOutOfLimitTable() CONST;
	VOID SetConstValue(LPCTSTR pszConstValue);
	CString GetConstValue() CONST;
	VOID SetOnBoardTimerID(INT nOBTID);
	INT GetOnBoardTimerID() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCParameter *pDatabaseTCParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckUnit(BOOL bStatus = TRUE);
	BOOL CheckTypeCode(BOOL bStatus = TRUE);
	BOOL CheckFormatCode(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckDisplayFormat(BOOL bStatus = TRUE);
	BOOL CheckCalibrationTable(BOOL bStatus = TRUE);
	BOOL CheckOutOfLimitTable(BOOL bStatus = TRUE);
	BOOL CheckConstValue(BOOL bStatus = TRUE);
	BOOL CheckOnBoardTimerID(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumCalTablesRecordset recordset

class CSCOS2000DatabaseTCNumCalTablesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCNumCalTablesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCNumCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCNumCalTablesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szDescr;
	CString  m_szEngFmt;
	CString  m_szRawFmt;
	CString  m_szRadix;
	CString  m_szUnit;
	INT  m_nNCurve;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckUnit(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckPoints(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCNumCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumCalTablePointsRecordset recordset

class CSCOS2000DatabaseTCNumCalTablePointsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCNumCalTablePointsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCNumCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCNumCalTablePointsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szXVals;
	CString  m_szYVals;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
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
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckPoint(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCNumCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtCalTablesRecordset recordset

class CSCOS2000DatabaseTCTxtCalTablesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCTxtCalTablesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCTxtCalTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCTxtCalTablesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szDescr;
	CString  m_szRawFmt;
	INT  m_nNAlias;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetPoints(INT nPoints);
	INT GetPoints() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckPoints(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCTxtCalTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtCalTablePointsRecordset recordset

class CSCOS2000DatabaseTCTxtCalTablePointsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCTxtCalTablePointsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCTxtCalTablePointsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCTxtCalTablePointsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szAlTxt;
	CString  m_szAlVal;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetX(double fX);
	double GetX() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, CONST CDatabaseTCTxtCalPoint *pDatabaseTCTxtCalPoint);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckPoint(BOOL bStatus = TRUE);
	BOOL CheckText(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCTxtCalTablePointsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumOolTablesRecordset recordset

class CSCOS2000DatabaseTCNumOolTablesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCNumOolTablesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCNumOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCNumOolTablesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szDescr;
	CString  m_szInter;
	CString  m_szDspFmt;
	CString  m_szRadix;
	CString  m_szUnit;
	INT  m_nNRange;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetUnit(LPCTSTR pszUnit);
	CString GetUnit() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLimits(INT nLimits);
	INT GetLimits() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckUnit(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckLimits(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCNumOolTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCNumOolTableLimitsRecordset recordset

class CSCOS2000DatabaseTCNumOolTableLimitsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCNumOolTableLimitsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCNumOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCNumOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szMinVal;
	CString  m_szMaxVal;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	BOOL SetRange(double fLow, double fHigh);
	BOOL GetRange(double &fLow, double &fHigh) CONST;
	BOOL SetTimeSpan(TIMETAG tStart, TIMETAG tStop);
	BOOL GetTimeSpan(TIMETAG &tStart, TIMETAG &tStop) CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CONST CDatabaseTCNumOolLimit *pDatabaseTCNumOolLimit);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckLowLimit(BOOL bStatus = TRUE);
	BOOL CheckHighLimit(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCNumOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtOolTablesRecordset recordset

class CSCOS2000DatabaseTCTxtOolTablesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCTxtOolTablesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCTxtOolTablesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCTxtOolTablesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szDescr;
	CString  m_szInter;
	CString  m_szDspFmt;
	CString  m_szRadix;
	CString  m_szUnit;
	INT  m_nNRange;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetLimits(INT nLimits);
	INT GetLimits() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckLimits(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCTxtOolTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCTxtOolTableLimitsRecordset recordset

class CSCOS2000DatabaseTCTxtOolTableLimitsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCTxtOolTableLimitsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCTxtOolTableLimitsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCTxtOolTableLimitsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbr;
	CString  m_szMinVal;
	CString  m_szMaxVal;
	//}}AFX_FIELD

	// Attributes
private:
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
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

	BOOL Translate(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CONST CDatabaseTCTxtOolLimit *pDatabaseTCTxtOolLimit);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckLowLimit(BOOL bStatus = TRUE);
	BOOL CheckHighLimit(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCTxtOolTableLimitsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCPreExeGroupParametersRecordset recordset

class CSCOS2000DatabaseTCPreExeGroupParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCPreExeGroupParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCPreExeGroupParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCPreExeGroupParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szCName;
	CString  m_szParNam;
	CString  m_szInter;
	CString  m_szVal;
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
	BOOL CheckID(BOOL bStatus = TRUE);
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCPreExeGroupParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCExeVerStagesRecordset recordset

class CSCOS2000DatabaseTCExeVerStagesRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCExeVerStagesRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCExeVerStagesRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCExeVerStagesRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szType;
	CString  m_szSource;
	INT  m_nID;
	INT  m_nSPID;
	INT  m_nStart;
	INT  m_nInterval;
	INT  m_nUncertainty;
	//}}AFX_FIELD
	CString  m_szID;

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetTimeWindowOffset(CONST CTimeSpan &tOffset);
	CTimeSpan GetTimeWindowOffset() CONST;
	VOID SetTimeWindowInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetTimeWindowInterval() CONST;
	VOID SetTimeWindowUncertainty(CONST CTimeSpan &tInterval);
	CTimeSpan GetTimeWindowUncertainty() CONST;
	VOID SetTimeWindowClosurePacket(LPCTSTR pszTag);
	CString GetTimeWindowClosurePacket() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus = TRUE);
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckTimeWindowOffset(BOOL bStatus = TRUE);
	BOOL CheckTimeWindowInterval(BOOL bStatus = TRUE);
	BOOL CheckTimeWindowUncertainty(BOOL bStatus = TRUE);
	BOOL CheckTimeWindowClosurePacket(BOOL bStatus = TRUE);

	INT ConvertID(LPCTSTR pszID) CONST;
	CString ConvertID(INT nID) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCExeVerStagesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCExeVerStageParametersRecordset recordset

class CSCOS2000DatabaseTCExeVerStageParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCExeVerStageParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCExeVerStageParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCExeVerStageParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szParNam;
	CString  m_szInter;
	CString  m_szVal;
	CString  m_szTol;
	CString  m_szCheck;
	INT  m_nCVSID;
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
	VOID SetValueTolerance(LPCTSTR pszDelta);
	CString GetValueTolerance() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, CONST CDatabaseTCExeVerStageParameter *pDatabaseTCExeVerStageParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckID(BOOL bStatus = TRUE);
	BOOL CheckTag(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckValue(BOOL bStatus = TRUE);
	BOOL CheckValueTolerance(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCExeVerStageParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCExeVerGroupsRecordset recordset

class CSCOS2000DatabaseTCExeVerGroupsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCExeVerGroupsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCExeVerGroupsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCExeVerGroupsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szTask;
	CString  m_szType;
	INT  m_nCVSID;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTask(LPCTSTR pszTask);
	CString GetTask() CONST;
	VOID SetStageID(LPCTSTR pszID);
	CString GetStageID() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, LPCTSTR pszStageID);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTask(BOOL bStatus = TRUE);
	BOOL CheckStageID(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCExeVerGroupsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterSetsRecordset recordset

class CSCOS2000DatabaseTCParameterSetsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCParameterSetsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCParameterSetsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCParameterSetsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szDescription;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCParameterSetsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterValueSetsRecordset recordset

class CSCOS2000DatabaseTCParameterValueSetsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCParameterValueSetsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCParameterValueSetsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCParameterValueSetsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szPVSID;
	CString  m_szDescription;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetParameterSet(LPCTSTR pszSet);
	CString GetParameterSet() CONST;
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet);
	VOID Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, LPCTSTR pszParameterSet);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckParameterSet(BOOL bStatus = TRUE);
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckDescription(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCParameterValueSetsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterValueSetItemsRecordset recordset

class CSCOS2000DatabaseTCParameterValueSetItemsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCParameterValueSetItemsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCParameterValueSetItemsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCParameterValueSetItemsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szID;
	CString  m_szPSID;
	CString  m_szPName;
	CString  m_szInter;
	CString  m_szVals;
	INT  m_nBit;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetParameterSet(LPCTSTR pszSet);
	CString GetParameterSet() CONST;
	VOID SetValueSet(LPCTSTR pszSet);
	CString GetValueSet() CONST;
	VOID SetParameterTag(LPCTSTR pszTag);
	CString GetParameterTag() CONST;
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

	VOID Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement);
	VOID Translate(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, LPCTSTR pszParameterSet);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckParameterSet(BOOL bStatus = TRUE);
	BOOL CheckValueSet(BOOL bStatus = TRUE);
	BOOL CheckParameterTag(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);
	BOOL CheckBitOffset(BOOL bStatus = TRUE);
	BOOL CheckConstValue(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCParameterValueSetItemsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCParameterSetAssociationsRecordset recordset

class CSCOS2000DatabaseTCParameterSetAssociationsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCParameterSetAssociationsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCParameterSetAssociationsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCParameterSetAssociationsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szName;
	CString  m_szType;
	CString  m_szParSet;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetTask(LPCTSTR pszTask);
	CString GetTask() CONST;
	VOID SetParameterSet(LPCTSTR pszSet);
	CString GetParameterSet() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCFunction *pDatabaseTCFunction, LPCTSTR pszSet);
	VOID Translate(CONST CDatabaseTCSequence *pDatabaseTCSequence, LPCTSTR pszSet);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckTask(BOOL bStatus = TRUE);
	BOOL CheckParameterSet(BOOL bStatus = TRUE);
	BOOL CheckAttributes(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCParameterSetAssociationsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseTCFunctionRoutingPathsRecordset recordset

class CSCOS2000DatabaseTCFunctionRoutingPathsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseTCFunctionRoutingPathsRecordset)

	// Construction
public:
	CSCOS2000DatabaseTCFunctionRoutingPathsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseTCFunctionRoutingPathsRecordset, CSCOS2000DatabaseRecordset)
	INT  m_nAPID;
	CString  m_szRoute;
	//}}AFX_FIELD

	// Attributes
public:

	// Operations
public:
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetRoute(LPCTSTR pszRoute);
	CString GetRoute() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszID, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszID, LPCTSTR pszWarning);

	VOID Translate(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckAPID(BOOL bStatus = TRUE);
	BOOL CheckRoute(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseTCFunctionRoutingPathsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseANDDirectoryRecordset recordset

class CSCOS2000DatabaseANDDirectoryRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseANDDirectoryRecordset)

	// Construction
public:
	CSCOS2000DatabaseANDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseANDDirectoryRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbe;
	CString  m_szType;
	CString  m_szHead;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetColumns(CONST CUIntArray &nColumns);
	INT GetColumns(CUIntArray &nColumns) CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CANDLayout *pANDLayout);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckTitle(BOOL bStatus = TRUE);
	BOOL CheckColumns(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseANDDirectoryRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseANDParametersRecordset recordset

class CSCOS2000DatabaseANDParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseANDParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseANDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseANDParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbe;
	CString  m_szName;
	CString  m_szMode;
	CString  m_szForm;
	CString  m_szText;
	INT  m_nFldn;
	INT  m_nComm;
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
	VOID SetPosition(INT nPosition);
	INT GetPosition() CONST;
	VOID SetOccurrence(INT nOccurrence);
	INT GetOccurrence() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CANDLayout *pANDLayout, CONST CANDLayoutParameter *pANDLayoutParameter);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckParameter(BOOL bStatus = TRUE);
	BOOL CheckComment(BOOL bStatus = TRUE);
	BOOL CheckMode(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckOccurrence(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseANDParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseGRDDirectoryRecordset recordset

class CSCOS2000DatabaseGRDDirectoryRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseGRDDirectoryRecordset)

	// Construction
public:
	CSCOS2000DatabaseGRDDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseGRDDirectoryRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbe;
	CString  m_szType;
	CString  m_szHead;
	CString  m_szScrol;
	CString  m_szHCopy;
	CString  m_szAxclr;
	INT  m_nDays;
	INT  m_nHours;
	INT  m_nMinut;
	INT  m_nXTick;
	INT  m_nYTick;
	INT  m_nXGrid;
	INT  m_nYGrid;
	INT  m_nUpun;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetMode(INT nMode);
	INT GetMode() CONST;
	VOID SetDays(INT nDays);
	INT GetDays() CONST;
	VOID SetHours(INT nHours);
	INT GetHours() CONST;
	VOID SetMinutes(INT nMinutes);
	INT GetMinutes() CONST;
	VOID SetAxisColor(INT nColor);
	INT GetAxisColor() CONST;
	VOID SetXGrids(INT nGrids);
	INT GetXGrids() CONST;
	VOID SetYGrids(INT nGrids);
	INT GetYGrids() CONST;
	VOID SetXTicks(INT nTicks);
	INT GetXTicks() CONST;
	VOID SetYTicks(INT nTicks);
	INT GetYTicks() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CGRDLayout *pGRDLayout);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckTitle(BOOL bStatus = TRUE);
	BOOL CheckType(BOOL bStatus = TRUE);
	BOOL CheckMode(BOOL bStatus = TRUE);
	BOOL CheckDays(BOOL bStatus = TRUE);
	BOOL CheckHours(BOOL bStatus = TRUE);
	BOOL CheckMinutes(BOOL bStatus = TRUE);
	BOOL CheckAxisColor(BOOL bStatus = TRUE);
	BOOL CheckXGrids(BOOL bStatus = TRUE);
	BOOL CheckYGrids(BOOL bStatus = TRUE);
	BOOL CheckXTicks(BOOL bStatus = TRUE);
	BOOL CheckYTicks(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseGRDDirectoryRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseGRDParametersRecordset recordset

class CSCOS2000DatabaseGRDParametersRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabaseGRDParametersRecordset)

	// Construction
public:
	CSCOS2000DatabaseGRDParametersRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabaseGRDParametersRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbe;
	CString  m_szWhere;
	CString  m_szName;
	CString  m_szRaw;
	CString  m_szMinim;
	CString  m_szMaxim;
	CString  m_szPrclr;
	CString  m_szSymbo;
	CString  m_szLine;
	INT  m_nPos;
	INT  m_nDomain;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetMode(ULONGLONG nMode);
	ULONGLONG GetMode() CONST;
	VOID SetPosition(INT nPosition, BOOL bOrder = TRUE);
	INT GetPosition(BOOL bOrder = TRUE) CONST;
	VOID SetMinimum(double fMinimum);
	double GetMinimum() CONST;
	VOID SetMaximum(double fMaximum);
	double GetMaximum() CONST;
	VOID SetColor(INT nColor);
	INT GetColor() CONST;
	VOID SetLineStyle(INT nStyle);
	INT GetLineStyle() CONST;
	VOID SetLineSymbol(INT nSymbol);
	INT GetLineSymbol() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CGRDLayout *pGRDLayout, CONST CGRDLayoutParameter *pGRDLayoutParameter, INT nPosition);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckParameter(BOOL bStatus = TRUE);
	BOOL CheckMode(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckMinimum(BOOL bStatus = TRUE);
	BOOL CheckMaximum(BOOL bStatus = TRUE);
	BOOL CheckColor(BOOL bStatus = TRUE);
	BOOL CheckLineStyle(BOOL bStatus = TRUE);
	BOOL CheckLineSymbol(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabaseANDParametersRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabasePODDirectoryRecordset recordset

class CSCOS2000DatabasePODDirectoryRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabasePODDirectoryRecordset)

	// Construction
public:
	CSCOS2000DatabasePODDirectoryRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabasePODDirectoryRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbe;
	CString  m_szHead;
	INT  m_nPar;
	INT  m_nUpun;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetParameterCount(INT nCount);
	INT GetParameterCount() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	VOID Translate(CONST CPODLayout *pPODLayout);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckTitle(BOOL bStatus = TRUE);
	BOOL CheckParameterCount(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabasePODDirectoryRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabasePODExpressionsRecordset recordset

class CSCOS2000DatabasePODExpressionsRecordset : public CSCOS2000DatabaseRecordset
{
	DECLARE_DYNAMIC(CSCOS2000DatabasePODExpressionsRecordset)

	// Construction
public:
	CSCOS2000DatabasePODExpressionsRecordset(CONST CDatabaseEngine *pDatabaseEngine);

	// Field/Param Data
	//{{AFX_FIELD(CSCOS2000DatabasePODExpressionsRecordset, CSCOS2000DatabaseRecordset)
	CString  m_szNumbe;
	CString  m_szName;
	CString  m_szUpdt;
	CString  m_szMode;
	CString  m_szForm;
	CString  m_szBack;
	CString  m_szFore;
	INT  m_nPos;
	//}}AFX_FIELD

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetParameter(LPCTSTR pszTag);
	CString GetParameter() CONST;
	VOID SetMode(ULONGLONG nMode);
	ULONGLONG GetMode() CONST;
	VOID SetPosition(INT nPosition);
	INT GetPosition() CONST;
	VOID SetScrollingFlag(INT nFlag);
	INT GetScrollingFlag() CONST;

	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszWarning);

	BOOL Translate(CONST CPODLayout *pPODLayout, CONST CPODLayoutExpression *pPODLayoutExpression, INT nPosition);

	BOOL Check(CStringArray &szIssues, BOOL bAppend = TRUE);
	BOOL Check(UINT nOperation = -1);

private:
	BOOL CheckName(BOOL bStatus = TRUE);
	BOOL CheckParameter(BOOL bStatus = TRUE);
	BOOL CheckMode(BOOL bStatus = TRUE);
	BOOL CheckPosition(BOOL bStatus = TRUE);
	BOOL CheckScrollingFlag(BOOL bStatus = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000DatabasePODExpressionsRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////


#endif // __RECORDS_H__
