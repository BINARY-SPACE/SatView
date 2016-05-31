// DATABASE.H : Database Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the database related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/04/08 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "views.h"
#include "logfile.h"
#include "registry.h"


/////////////////////////////////////////////////////////////////////////////
// CDatabaseVersion

class AFX_EXT_CLASS CDatabaseVersion : public CObject
{
	// Construction
public:
	CDatabaseVersion();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDomain;
		INT  cbComment;
		INT  cbRelease;
		INT  cbIssue;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDomain;
	CString  m_szComment;
	CString  m_szRelease;
	CString  m_szIssue;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDomain(LPCTSTR pszDomain);
	CString GetDomain() CONST;
	VOID SetComment(LPCTSTR pszComment);
	CString GetComment() CONST;
	VOID SetRelease(LPCTSTR pszRelease);
	CString GetRelease() CONST;
	VOID SetIssue(LPCTSTR pszIssue);
	CString GetIssue() CONST;

	VOID Copy(CONST CDatabaseVersion *pVersion);
	BOOL Compare(CONST CDatabaseVersion *pVersion) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseVersions

class AFX_EXT_CLASS CDatabaseVersions : public CPtrArray
{
	// Construction
public:
	CDatabaseVersions();
	~CDatabaseVersions();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseVersion *pVersion);

	INT Find(LPCTSTR pszName) CONST;
	INT Find(LPCTSTR pszName, LPCTSTR pszDomain, LPCTSTR pszRelease, LPCTSTR pszIssue) CONST;

	CDatabaseVersion *GetAt(INT nIndex) CONST;
	CDatabaseVersion *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseVersions *pVersions);
	BOOL Compare(CONST CDatabaseVersions *pVersions) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, LPCTSTR pszDomain = NULL, LPCTSTR pszRelease = NULL, LPCTSTR pszIssue = NULL, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketParameter

#define TMPACKETPARAMETER_TYPE_NORMAL   (1<<0)
#define TMPACKETPARAMETER_TYPE_SELECTOR   (1<<1)
#define TMPACKETPARAMETER_TYPE_ONBOARDID   (1<<2)
#define TMPACKETPARAMETER_DISPLAY_COLUMNS_NAME   (1<<3)
#define TMPACKETPARAMETER_DISPLAY_COLUMNS_DESCRIPTION   (1<<4)
#define TMPACKETPARAMETER_DISPLAY_COLUMNS_VALUE   (1<<5)
#define TMPACKETPARAMETER_DISPLAY_ALIGNMENT_LEFT   (1<<6)
#define TMPACKETPARAMETER_DISPLAY_ALIGNMENT_CENTER   (1<<7)
#define TMPACKETPARAMETER_DISPLAY_ALIGNMENT_RIGHT   (1<<8)
#define TMPACKETPARAMETER_DISPLAY_ALIGNMENT_NONEWLINE   (1<<9)
#define TMPACKETPARAMETER_DISPLAY_ALIGNMENT_NEWLINE   (1<<10)
#define TMPACKETPARAMETER_DISPLAY_FORMAT_DEFAULT   (1<<11)
#define TMPACKETPARAMETER_DISPLAY_FORMAT_BINARY   (1<<12)
#define TMPACKETPARAMETER_DISPLAY_FORMAT_OCTAL   (1<<13)
#define TMPACKETPARAMETER_DISPLAY_FORMAT_DECIMAL   (1<<14)
#define TMPACKETPARAMETER_DISPLAY_FORMAT_HEXADECIMAL   (1<<15)

class AFX_EXT_CLASS CDatabaseTMPacketParameter : public CObject
{
	// Construction
public:
	CDatabaseTMPacketParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag[2];
		INT  cbDescription;
		INT  nRef[2];
		INT  nBytePos;
		INT  nBitPos;
		INT  nOffset;
		INT  nWidth;
		INT  nOccurrence;
		INT  nOccurrenceCount;
		INT  nOccurrenceInterval;
		INT  nGroupParameters;
		INT  nGroupRepetitionCount;
		UINT  nAttributes;
		DWORD  dwOccurrenceTimeOffset;
		DWORD  dwOccurrenceTimeInterval;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag[2];
	CString  m_szDescription;
	DWORD  m_dwOccurrenceTimeOffset;
	DWORD  m_dwOccurrenceTimeInterval;
	UINT  m_nAttributes;
	INT  m_nOccurrenceInterval;
	INT  m_nOccurrenceCount;
	INT  m_nGroupParameters;
	INT  m_nGroupRepetitionCount;
	INT  m_nOccurrence;
	INT  m_nBytePos;
	INT  m_nBitPos;
	INT  m_nOffset;
	INT  m_nWidth;
	INT  m_nRef[2];

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetBytePos(INT nPos);
	INT GetBytePos() CONST;
	VOID SetBitPos(INT nPos);
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
	VOID SetOccurrenceTimeOffset(DWORD dwOffset);
	DWORD GetOccurrenceTimeOffset() CONST;
	VOID SetOccurrenceTimeInterval(DWORD dwInterval);
	DWORD GetOccurrenceTimeInterval() CONST;
	VOID SetGroupSize(INT nSize = 0);
	INT GetGroupSize() CONST;
	VOID SetGroupRepetitionCount(INT nCount);
	INT GetGroupRepetitionCount() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityParameterRef(INT nRef);
	INT GetValidityParameterRef() CONST;

	VOID SetRef(INT nRef);
	INT GetRef() CONST;

	VOID Copy(CONST CDatabaseTMPacketParameter *pPacketParameter);
	BOOL Compare(CONST CDatabaseTMPacketParameter *pPacketParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketIdentification

class AFX_EXT_CLASS CDatabaseTMPacketIdentification : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPacketIdentification();
	~CDatabaseTMPacketIdentification();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbUnit;
		INT  cbPacketID;
		INT  cbEventID;
		INT  cbParameters;
		INT  nType;
		INT  nSubType;
		INT  nAPID;
		INT  nContentID;
		INT  nEventType;
		INT  nIDValues[2];
		INT  nDataFieldHeaderSize;
		DWORD  dwTransmissionRate;
		BOOL  bTimestamp;
		BOOL  bCRCCheck;
		BOOL  bValid;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nType;
	INT  m_nSubType;
	INT  m_nAPID;
	INT  m_nContentID;
	INT  m_nEventType;
	INT  m_nIDValues[2];
	INT  m_nDataFieldHeaderSize;
	DWORD  m_dwTransmissionRate;
	CString  m_szDescription;
	CString  m_szPacketID;
	CString  m_szEventID;
	CString  m_szUnit;
	CString  m_szName;
	BOOL  m_bTimestamp;
	BOOL  m_bCRCCheck;
	BOOL  m_bValid;

	//Operations
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
	VOID SetPacketID(LPCTSTR pszID);
	CString GetPacketID() CONST;
	VOID SetDescription(LPCTSTR pszDescritption);
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

	INT Add(CDatabaseTMPacketParameter *pParameter);

	INT Find(LPCTSTR pszTag, INT nOccurrence = 0) CONST;
	INT Find(LPCTSTR pszTag, INT nBytePos, INT nBitPos) CONST;

	CDatabaseTMPacketParameter *GetAt(INT nIndex) CONST;
	CDatabaseTMPacketParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacketIdentification *pPacketIdentification);
	BOOL Compare(CONST CDatabaseTMPacketIdentification *pPacketIdentification) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(INT nBytePos, INT nBitPos, BOOL bInsert = FALSE) CONST;

public:
	static CString ConstructName(INT nType, INT nSubType, INT nAPID, INT nFirstIDValue, INT nSecondIDValue);
	static BOOL ParseName(LPCTSTR pszName, INT &nType, INT &nSubType, INT &nAPID, INT &nFirstIDValue, INT &nSecondIDValue);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketIdentifications

class AFX_EXT_CLASS CDatabaseTMPacketIdentifications : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPacketIdentifications();
	~CDatabaseTMPacketIdentifications();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMPacketIdentification *pPacketIdentification);

	INT Find(LPCTSTR pszName, BOOL bID = FALSE) CONST;

	CDatabaseTMPacketIdentification *GetAt(INT nIndex) CONST;
	CDatabaseTMPacketIdentification *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacketIdentifications *pPacketIdentifications);
	BOOL Compare(CONST CDatabaseTMPacketIdentifications *pPacketIdentifications) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketIdentificationCriterion

class AFX_EXT_CLASS CDatabaseTMPacketIdentificationCriterion : public CObject
{
	// Construction
public:
	CDatabaseTMPacketIdentificationCriterion();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  nType;
		INT  nSubType;
		INT  nAPID;
		INT  nOffset[2];
		INT  nWidth[2];
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	INT  m_nType;
	INT  m_nSubType;
	INT  m_nAPID;
	INT  m_nOffset[2];
	INT  m_nWidth[2];

	//Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(INT nType);
	INT GetType() CONST;
	VOID SetSubType(INT nSubType);
	INT GetSubType() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetFirstIDValueOffset(INT nOffset);
	INT GetFirstIDValueOffset() CONST;
	VOID SetFirstIDValueWidth(INT nWidth);
	INT GetFirstIDValueWidth() CONST;
	VOID SetSecondIDValueOffset(INT nOffset);
	INT GetSecondIDValueOffset() CONST;
	VOID SetSecondIDValueWidth(INT nWidth);
	INT GetSecondIDValueWidth() CONST;

	VOID Copy(CONST CDatabaseTMPacketIdentificationCriterion *pPacketIdentificationCriterion);
	BOOL Compare(CONST CDatabaseTMPacketIdentificationCriterion *pPacketIdentificationCriterion) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

public:
	static CString ConstructName(INT nType, INT nSubType, INT nAPID = -1);
	static BOOL ParseName(LPCTSTR pszName, INT &nType, INT &nSubType, INT &nAPID);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketIdentificationCriteria

class AFX_EXT_CLASS CDatabaseTMPacketIdentificationCriteria : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPacketIdentificationCriteria();
	~CDatabaseTMPacketIdentificationCriteria();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMPacketIdentificationCriterion *pPacketIdentificationCriterion);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMPacketIdentificationCriterion *GetAt(INT nIndex) CONST;
	CDatabaseTMPacketIdentificationCriterion *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacketIdentificationCriteria *pPacketIdentificationCriteria);
	BOOL Compare(CONST CDatabaseTMPacketIdentificationCriteria *pPacketIdentificationCriteria) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketHeader

class AFX_EXT_CLASS CDatabaseTMPacketHeader : public CObject
{
	// Construction
public:
	CDatabaseTMPacketHeader();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  nType;
		INT  nSubType;
		INT  nAPID;
		INT  nTMTypePos[3];
		INT  nTMIDPos[3];
		INT  n3DiscPos[3];
		INT  nTimestampPos[3];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	INT  m_nType;
	INT  m_nSubType;
	INT  m_nAPID;
	INT  m_nTMTypePos[3];
	INT  m_nTMIDPos[3];
	INT  m_n3DiscPos[3];
	INT  m_nTimestampPos[3];

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
	VOID SetTMTypePosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTMTypePosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTMIDPosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTMIDPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID Set3DiscPosition(INT nByte, INT nBit, INT nLength);
	BOOL Get3DiscPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTimestampPosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTimestampPosition(INT &nByte, INT &nBit, INT &nLength) CONST;

	VOID Copy(CONST CDatabaseTMPacketHeader *pPacketHeader);
	BOOL Compare(CONST CDatabaseTMPacketHeader *pPacketHeader) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

public:
	static CString ConstructName(INT nType, INT nSubType, INT nAPID = -1);
	static BOOL ParseName(LPCTSTR pszName, INT &nType, INT &nSubType, INT &nAPID);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketHeaders

class AFX_EXT_CLASS CDatabaseTMPacketHeaders : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPacketHeaders();
	~CDatabaseTMPacketHeaders();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMPacketHeader *pPacketHeader);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMPacketHeader *GetAt(INT nIndex) CONST;
	CDatabaseTMPacketHeader *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacketHeaders *pPacketHeaders);
	BOOL Compare(CONST CDatabaseTMPacketHeaders *pPacketHeaders) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacket

// Specify the telemetry source packet related identifiers
#define TMPACKET_TMTYPE_CYCLIC   0
#define TMPACKET_TMTYPE_EXCEPTION   1
#define TMPACKET_TMTYPE_OVERSAMPLED   2
#define TMPACKET_TMTYPE_REPORT   3
#define TMPACKET_TMTYPE_DUMP   4
#define TMPACKET_EVENTTYPE_NONE   0
#define TMPACKET_EVENTTYPE_INFORMATIONAL   1
#define TMPACKET_EVENTTYPE_WARNING   2
#define TMPACKET_EVENTTYPE_ALARM   3
#define TMPACKET_LENGTH_FIXED   0
#define TMPACKET_LENGTH_VARIABLE   1
#define TMPACKET_RECORDSTATUS_NONE   (1<<0)
#define TMPACKET_RECORDSTATUS_NEW   (1<<1)
#define TMPACKET_RECORDSTATUS_DRAFT   (1<<2)
#define TMPACKET_RECORDSTATUS_CHANGED   (1<<3)
#define TMPACKET_RECORDSTATUS_DELETED   (1<<4)
#define TMPACKET_RECORDSTATUS_DEFAULT   (TMPACKET_RECORDSTATUS_NONE | TMPACKET_RECORDSTATUS_NEW | TMPACKET_RECORDSTATUS_CHANGED)
#define TMPACKET_RECORDSTATUS_ALL   (TMPACKET_RECORDSTATUS_NONE | TMPACKET_RECORDSTATUS_DRAFT | TMPACKET_RECORDSTATUS_NEW | TMPACKET_RECORDSTATUS_CHANGED | TMPACKET_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTMPacket : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPacket();
	~CDatabaseTMPacket();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbData[2];
		INT  cbDetails;
		INT  cbDescription;
		INT  cbDataFieldHeader;
		INT  cbEventIDParameter;
		INT  cbEventIDMessage;
		INT  cbTriggerRefs;
		INT  cbParameters;
		INT  nTMType;
		INT  nTMID;
		INT  nAPID;
		INT  n3Disc;
		INT  nStatus;
		INT  nTrmRate;
		INT  nTrmRetries;
		INT  nVirtChannel;
		INT  nEventType;
		INT  nEventIDRef;
		INT  nTMIDPos[3];
		INT  nTMTypePos[3];
		INT  n3DiscPos[3];
		INT  nTimestampPos[3];
		BOOL  bCRCFieldCheck;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CString  m_szDetails;
	CString  m_szDescription;
	CString  m_szDataFieldHeader;
	CString  m_szEventIDParameter;
	CString  m_szEventIDMessage;
	CUIntArray  m_nTriggerRefs;
	BOOL  m_bCRCFieldCheck;
	UINT  m_nEventType;
	INT  m_nTMType;
	INT  m_nTMID;
	INT  m_nAPID;
	INT  m_n3Disc;
	INT  m_nStatus;
	INT  m_cbData[2];
	INT  m_nTrmRate;
	INT  m_nTrmRetries;
	INT  m_nVirtChannel;
	INT  m_nEventIDRef;
	INT  m_nTMIDPos[3];
	INT  m_nTMTypePos[3];
	INT  m_n3DiscPos[3];
	INT  m_nTimestampPos[3];

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetTMType(INT nTMType);
	INT GetTMType() CONST;
	VOID SetTMID(INT nTMID);
	INT GetTMID() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID Set3Disc(INT n3Disc);
	INT Get3Disc() CONST;
	VOID SetDataFieldHeader(LPCTSTR pszName);
	CString GetDataFieldHeader() CONST;
	VOID SetDataFieldHeaderSize(INT cbData);
	INT GetDataFieldHeaderSize() CONST;
	VOID SetTMTypePosition(INT nByte = 0, INT nBit = 0, INT nLength = 0);
	BOOL GetTMTypePosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTMIDPosition(INT nByte = 0, INT nBit = 0, INT nLength = 0);
	BOOL GetTMIDPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID Set3DiscPosition(INT nByte = 0, INT nBit = 0, INT nLength = 0);
	BOOL Get3DiscPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTimestampPosition(INT nByte = 0, INT nBit = 0, INT nLength = 0);
	BOOL GetTimestampPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetDataSize(INT cbData);
	INT GetDataSize() CONST;
	VOID SetTransmissionRate(INT nInterval);
	INT GetTransmissionRate() CONST;
	VOID SetTransmissionRetries(INT nRetries);
	INT GetTransmissionRetries() CONST;
	VOID SetVirtualChannel(INT nChannelID);
	INT GetVirtualChannel() CONST;
	VOID SetEventType(UINT nType);
	UINT GetEventType() CONST;
	VOID SetEventIDMessage(LPCTSTR pszMessage);
	CString GetEventIDMessage() CONST;
	VOID SetEventIDParameter(LPCTSTR pszTag);
	CString GetEventIDParameter() CONST;
	VOID SetEventIDParameterRef(INT nRef);
	INT GetEventIDParameterRef() CONST;
	VOID EnableCRCCheck(BOOL bEnable = TRUE);
	BOOL IsCRCCheckEnabled() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID SetTriggerRefs(CONST CUIntArray &nRefs);
	INT GetTriggerRefs(CUIntArray &nRefs) CONST;

	INT Add(CDatabaseTMPacketParameter *pParameter);

	INT Find(LPCTSTR pszTag, INT nOccurrence = 0) CONST;
	INT Find(LPCTSTR pszTag, INT nBytePos, INT nBitPos) CONST;

	CDatabaseTMPacketParameter *GetAt(INT nIndex) CONST;
	CDatabaseTMPacketParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacket *pPacket);
	BOOL Compare(CONST CDatabaseTMPacket *pPacket) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, INT nBytePos, INT nBitPos, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPackets

class AFX_EXT_CLASS CDatabaseTMPackets : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPackets();
	~CDatabaseTMPackets();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMPacket *pPacket);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTMPacket *GetAt(INT nIndex) CONST;
	CDatabaseTMPacket *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPackets *pPackets);
	BOOL Compare(CONST CDatabaseTMPackets *pPackets) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketStream

class AFX_EXT_CLASS CDatabaseTMPacketStream : public CObject
{
	// Construction
public:
	CDatabaseTMPacketStream();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbTag;
		INT  nType;
		INT  nSubType;
		INT  nAPID;
		INT  nTMID;
		INT  nPeriod;
		INT  nTimeout;
		INT  nValidityParameterRef;
		ULONGLONG  nValidityValue;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szTag;
	INT  m_nType;
	INT  m_nSubType;
	INT  m_nAPID;
	INT  m_nTMID;
	INT  m_nPeriod;
	INT  m_nTimeout;
	INT  m_nValidityParameterRef;
	ULONGLONG  m_nValidityValue;

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
	VOID SetTMID(INT nTMID);
	INT GetTMID() CONST;
	VOID SetPeriod(INT nPeriod);
	INT GetPeriod() CONST;
	VOID SetTimeout(INT nTimeout);
	INT GetTimeout() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityParameterRef(INT nRef);
	INT GetValidityParameterRef() CONST;
	VOID SetValidityValue(ULONGLONG nValue);
	ULONGLONG GetValidityValue() CONST;

	VOID Copy(CONST CDatabaseTMPacketStream *pPacketStream);
	BOOL Compare(CONST CDatabaseTMPacketStream *pPacketStream) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

public:
	static CString ConstructName(INT nType, INT nSubType, INT nAPID = -1);
	static BOOL ParseName(LPCTSTR pszName, INT &nType, INT &nSubType, INT &nAPID);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketStreams

class AFX_EXT_CLASS CDatabaseTMPacketStreams : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPacketStreams();
	~CDatabaseTMPacketStreams();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMPacketStream *pPacketStream);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMPacketStream *GetAt(INT nIndex) CONST;
	CDatabaseTMPacketStream *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacketStreams *pPacketStreams);
	BOOL Compare(CONST CDatabaseTMPacketStreams *pPacketStreams) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketGroup

class AFX_EXT_CLASS CDatabaseTMPacketGroup : public CStringArray
{
	// Construction
public:
	CDatabaseTMPacketGroup();
	~CDatabaseTMPacketGroup();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbPackets;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;

	INT Add(LPCTSTR pszTag);

	INT Find(LPCTSTR pszTag) CONST;

	CString GetAt(INT nIndex) CONST;
	CString operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacketGroup *pPacketGroup);
	BOOL Compare(CONST CDatabaseTMPacketGroup *pPacketGroup) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMPacketGroups

class AFX_EXT_CLASS CDatabaseTMPacketGroups : public CPtrArray
{
	// Construction
public:
	CDatabaseTMPacketGroups();
	~CDatabaseTMPacketGroups();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMPacketGroup *pPacketGroup);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMPacketGroup *GetAt(INT nIndex) CONST;
	CDatabaseTMPacketGroup *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMPacketGroups *pPacketGroups);
	BOOL Compare(CONST CDatabaseTMPacketGroups *pPacketGroups) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCPacketParameter

// Specify the telecommand packet parameter related identifiers
#define TCPACKETPARAMETER_TYPE_FIXED   TCPARAMETER_TYPE_CONSTANT
#define TCPACKETPARAMETER_TYPE_VARIABLE   TCPARAMETER_TYPE_VARIABLE
#define TCPACKETPARAMETER_TYPE_APID   (((ULONGLONG) 1)<<59)
#define TCPACKETPARAMETER_TYPE_SERVICETYPE   (((ULONGLONG) 1)<<60)
#define TCPACKETPARAMETER_TYPE_SERVICESUBTYPE   (((ULONGLONG) 1)<<61)
#define TCPACKETPARAMETER_TYPE_ACKNOWLEDGEMENTFLAGS   (((ULONGLONG) 1)<<62)
#define TCPACKETPARAMETER_TYPE_OTHER   (((ULONGLONG) 1)<<63)

class AFX_EXT_CLASS CDatabaseTCPacketParameter : public CObject
{
	// Construction
public:
	CDatabaseTCPacketParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbDescription;
		INT  cbConstValue;
		INT  nBytePos;
		INT  nBitPos;
		INT  nWidth;
		INT  nRef;
		ULONGLONG  nAttributes;
		ULONGLONG  nConstValue;
		BOOL  bConstValue;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CString  m_szDescription;
	CString  m_szConstValue;
	ULONGLONG  m_nAttributes;
	ULONGLONG  m_nConstValue;
	BOOL  m_bConstValue;
	INT  m_nBytePos;
	INT  m_nBitPos;
	INT  m_nWidth;
	INT  m_nRef;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBytePos(INT nPos);
	INT GetBytePos() CONST;
	VOID SetBitPos(INT nPos);
	INT GetBitPos() CONST;
	VOID SetWidth(INT nWidth);
	INT GetWidth() CONST;
	VOID SetConstValue();
	VOID SetConstValue(ULONGLONG nConstValue);
	ULONGLONG GetConstValue() CONST;
	BOOL HasConstValue() CONST;
	VOID SetConstValueAsText(LPCTSTR pszConstValue);
	CString GetConstValueAsText() CONST;

	VOID SetRef(INT nRef);
	INT GetRef() CONST;

	VOID Copy(CONST CDatabaseTCPacketParameter *pPacketParameter);
	BOOL Compare(CONST CDatabaseTCPacketParameter *pPacketParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCPacketParameters

class AFX_EXT_CLASS CDatabaseTCPacketParameters : public CPtrArray
{
	// Construction
public:
	CDatabaseTCPacketParameters();
	~CDatabaseTCPacketParameters();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbParameters;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;

	// Operations
public:
	INT Add(CDatabaseTCPacketParameter *pParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTCPacketParameter *GetAt(INT nIndex) CONST;
	CDatabaseTCPacketParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCPacketParameters *pPacketParameters);
	BOOL Compare(CONST CDatabaseTCPacketParameters *pPacketParameters) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCPacket

// Specify the telecommand packet related identifiers
#define TCPACKET_LENGTH_FIXED   0
#define TCPACKET_LENGTH_VARIABLE   1
#define TCPACKET_RECORDSTATUS_NONE   (1<<0)
#define TCPACKET_RECORDSTATUS_NEW   (1<<1)
#define TCPACKET_RECORDSTATUS_DRAFT   (1<<2)
#define TCPACKET_RECORDSTATUS_CHANGED   (1<<3)
#define TCPACKET_RECORDSTATUS_DELETED   (1<<4)
#define TCPACKET_RECORDSTATUS_DEFAULT   (TCPACKET_RECORDSTATUS_NONE | TCPACKET_RECORDSTATUS_NEW | TCPACKET_RECORDSTATUS_CHANGED)
#define TCPACKET_RECORDSTATUS_ALL   (TCPACKET_RECORDSTATUS_NONE | TCPACKET_RECORDSTATUS_DRAFT | TCPACKET_RECORDSTATUS_NEW | TCPACKET_RECORDSTATUS_CHANGED | TCPACKET_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCPacket : public CPtrArray
{
	// Construction
public:
	CDatabaseTCPacket();
	~CDatabaseTCPacket();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbDetails;
		INT  cbDescription;
		INT  cbParameters;
		INT  nAPID;
		INT  cbData;
		INT  nStatus;
		BOOL  bDataFieldHeader;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CString  m_szDetails;
	CString  m_szDescription;
	BOOL  m_bDataFieldHeader;
	INT  m_nAPID;
	INT  m_cbData;
	INT  m_nStatus;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetDataFieldHeaderFlag(BOOL bFlag);
	BOOL GetDataFieldHeaderFlag() CONST;
	VOID SetDataSize(INT cbData);
	INT GetDataSize() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCPacketParameter *pParameter);

	INT Find(LPCTSTR pszTag, INT nOccurrence = 0) CONST;
	INT Find(LPCTSTR pszTag, INT nBytePos, INT nBitPos) CONST;

	CDatabaseTCPacketParameter *GetAt(INT nIndex) CONST;
	CDatabaseTCPacketParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCPacket *pPacket);
	BOOL Compare(CONST CDatabaseTCPacket *pPacket) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, INT nBytePos, INT nBitPos) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCPackets

class AFX_EXT_CLASS CDatabaseTCPackets : public CPtrArray
{
	// Construction
public:
	CDatabaseTCPackets();
	~CDatabaseTCPackets();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCPacket *pPacket);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTCPacket *GetAt(INT nIndex) CONST;
	CDatabaseTCPacket *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCPackets *pPackets);
	BOOL Compare(CONST CDatabaseTCPackets *pPackets) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMParameter

// Specify the telemetry parameter related identifiers
#define TMPARAMETER_TYPE_DS16   (((ULONGLONG) 1)<<0)
#define TMPARAMETER_TYPE_DS8   (((ULONGLONG) 1)<<1)
#define TMPARAMETER_TYPE_BIL   (((ULONGLONG) 1)<<2)
#define TMPARAMETER_TYPE_HBIL   (((ULONGLONG) 1)<<3)
#define TMPARAMETER_TYPE_AN   (((ULONGLONG) 1)<<4)
#define TMPARAMETER_TYPE_FLOAT   (((ULONGLONG) 1)<<5)
#define TMPARAMETER_TYPE_DEDUCED   (((ULONGLONG) 1)<<6)
#define TMPARAMETER_NATURE_RAW   (((ULONGLONG) 1)<<7)
#define TMPARAMETER_NATURE_DERIVED   (((ULONGLONG) 1)<<8)
#define TMPARAMETER_NATURE_DERIVED_OL   TMPARAMETER_NATURE_DERIVED
#define TMPARAMETER_NATURE_DERIVED_SPEL   (((ULONGLONG) 1)<<9)
#define TMPARAMETER_NATURE_DERIVED_HARDCODED   (((ULONGLONG) 1)<<10)
#define TMPARAMETER_NATURE_DERIVED_SAVED   (((ULONGLONG) 1)<<11)
#define TMPARAMETER_NATURE_CONSTANT   (((ULONGLONG) 1)<<12)
#define TMPARAMETER_OBS_ONBOARD   (((ULONGLONG) 1)<<13)
#define TMPARAMETER_OBS_MONITOR   (((ULONGLONG) 1)<<14)
#define TMPARAMETER_STANDARD_IEEE  (((ULONGLONG) 1)<<15)
#define TMPARAMETER_STANDARD_USAF  (((ULONGLONG) 1)<<16)
#define TMPARAMETER_STANDARD_DOUBLEPRECISION  (((ULONGLONG) 1)<<17)
#define TMPARAMETER_CODING_BITPATTERN   (((ULONGLONG) 1)<<18)
#define TMPARAMETER_CODING_INVERSEBITPATTERN   (((ULONGLONG) 1)<<19)
#define TMPARAMETER_CODING_SIGNEDINTEGER   (((ULONGLONG) 1)<<20)
#define TMPARAMETER_CODING_UNSIGNEDINTEGER   (((ULONGLONG) 1)<<21)
#define TMPARAMETER_CODING_COMPLEMENTCOMPLEX   (((ULONGLONG) 1)<<22)
#define TMPARAMETER_CODING_FLOATINGPOINT   (((ULONGLONG) 1)<<23)
#define TMPARAMETER_CODING_TEXTSTRING   (((ULONGLONG) 1)<<24)
#define TMPARAMETER_CODING_ABSOLUTETIME   (((ULONGLONG) 1)<<25)
#define TMPARAMETER_CODING_RELATIVETIME   (((ULONGLONG) 1)<<26)
#define TMPARAMETER_CODING_TIME   (TMPARAMETER_CODING_ABSOLUTETIME | TMPARAMETER_CODING_RELATIVETIME)
#define TMPARAMETER_RADIX_BINARY   (((ULONGLONG) 1)<<27)
#define TMPARAMETER_RADIX_OCTAL   (((ULONGLONG) 1)<<28)
#define TMPARAMETER_RADIX_DECIMAL   (((ULONGLONG) 1)<<29)
#define TMPARAMETER_RADIX_HEXADECIMAL   (((ULONGLONG) 1)<<30)
#define TMPARAMETER_CALIBRATION_NONE   (((ULONGLONG) 1)<<31)
#define TMPARAMETER_CALIBRATION_NUMERICAL   (((ULONGLONG) 1)<<32)
#define TMPARAMETER_CALIBRATION_STATUS   (((ULONGLONG) 1)<<33)
#define TMPARAMETER_CALIBRATION_TEXT   (((ULONGLONG) 1)<<34)
#define TMPARAMETER_INTERPRETATION_FULL   (((ULONGLONG) 1)<<35)
#define TMPARAMETER_INTERPRETATION_EXTRAPOLATE   (((ULONGLONG) 1)<<36)
#define TMPARAMETER_TRIGGERTYPE_PACKET   (((ULONGLONG) 1)<<37)
#define TMPARAMETER_TRIGGERTYPE_PARAMETER   (((ULONGLONG) 1)<<38)
#define TMPARAMETER_TRIGGERTYPE_CONSTANT   (((ULONGLONG) 1)<<39)
#define TMPARAMETER_RESULTTYPE_RAW   (((ULONGLONG) 1)<<40)
#define TMPARAMETER_RESULTTYPE_ENGINEERING   (((ULONGLONG) 1)<<41)
#define TMPARAMETER_FLAG_NOCONSISTENCYCHECKS   (((ULONGLONG) 1)<<42)
#define TMPARAMETER_FLAG_CONSISTENCYCHECKS   (((ULONGLONG) 1)<<43)
#define TMPARAMETER_FLAG_NOTIMECORRELATION   (((ULONGLONG) 1)<<44)
#define TMPARAMETER_FLAG_TIMECORRELATION   (((ULONGLONG) 1)<<45)
#define TMPARAMETER_FLAG_NOFORCEDARCHIVING   (((ULONGLONG) 1)<<46)
#define TMPARAMETER_FLAG_FORCEDARCHIVING   (((ULONGLONG) 1)<<47)
#define TMPARAMETER_FLAG_BIGENDIAN   (((ULONGLONG) 1)<<48)
#define TMPARAMETER_FLAG_LITTLEENDIAN   (((ULONGLONG) 1)<<49)
#define TMPARAMETER_RECORDSTATUS_NONE   (1<<0)
#define TMPARAMETER_RECORDSTATUS_NEW   (1<<1)
#define TMPARAMETER_RECORDSTATUS_DRAFT   (1<<2)
#define TMPARAMETER_RECORDSTATUS_CHANGED   (1<<3)
#define TMPARAMETER_RECORDSTATUS_DELETED   (1<<4)
#define TMPARAMETER_RECORDSTATUS_DEFAULT   (TMPARAMETER_RECORDSTATUS_NONE | TMPARAMETER_RECORDSTATUS_NEW | TMPARAMETER_RECORDSTATUS_CHANGED)
#define TMPARAMETER_RECORDSTATUS_ALL   (TMPARAMETER_RECORDSTATUS_NONE | TMPARAMETER_RECORDSTATUS_DRAFT | TMPARAMETER_RECORDSTATUS_NEW | TMPARAMETER_RECORDSTATUS_CHANGED | TMPARAMETER_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTMParameter : public CObject
{
	// Construction
public:
	CDatabaseTMParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbUnit;
		INT  cbDetails;
		INT  cbTrigger;
		INT  cbConstValue;
		INT  cbDerivation;
		INT  cbDescription;
		INT  cbSubSystem[2];
		INT  cbEquipment[2];
		INT  cbOperationalInfo;
		INT  cbDangerConditions;
		INT  cbValidityParameter;
		INT  cbValidityConditions;
		INT  cbRelatedParameter;
		INT  cbAssociatedTelecommands;
		INT  cbCalValidityParameters;
		INT  cbCalValidityValues;
		INT  cbOolValidityParameters;
		INT  cbOolValidityValues;
		INT  cbCalTables;
		INT  cbOolTables;
		INT  cbSubTagRefs;
		INT  cbCalTableRefs;
		INT  cbOolTableRefs;
		INT  cbCalValidityRefs;
		INT  cbOolValidityRefs;
		INT  cbTriggerRefs[2];
		INT  cbValidityRefs;
		INT  nValidityParameterRef;
		INT  nRelatedParameterRef;
		INT  nWidth[2];
		INT  nDigits;
		INT  nStatus;
		UINT  nID;
		UINT  nOBTID;
		UINT  nTypeCode;
		UINT  nFormatCode;
		UINT  nInterrogationCode;
		ULONGLONG  nAttributes;
		ULONGLONG  nConstValue;
		ULONGLONG  nValidityValue;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CString  m_szUnit;
	CString  m_szDetails;
	CString  m_szTrigger;
	CString  m_szConstValue;
	CString  m_szDerivation;
	CString  m_szDescription;
	CString  m_szSubSystem[2];
	CString  m_szEquipment[2];
	CString  m_szOperationalInfo;
	CString  m_szDangerConditions;
	CString  m_szRelatedParameter;
	CString  m_szValidityParameter;
	CString  m_szValidityConditions;
	CString  m_szAssociatedTelecommands;
	CStringArray  m_szCalTables;
	CStringArray  m_szOolTables;
	CStringArray  m_szCalValidityParameters;
	CStringArray  m_szOolValidityParameters;
	CLongUIntArray  m_nCalValidityValues;
	CLongUIntArray  m_nOolValidityValues;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nOolTableRefs;
	CUIntArray  m_nCalValidityRefs;
	CUIntArray  m_nOolValidityRefs;
	CUIntArray  m_nTriggerRefs[2];
	CUIntArray  m_nValidityRefs;
	CUIntArray  m_nSubTagRefs;
	ULONGLONG  m_nAttributes;
	ULONGLONG  m_nConstValue;
	ULONGLONG  m_nValidityValue;
	UINT  m_nID;
	UINT  m_nOBTID;
	UINT  m_nTypeCode;
	UINT  m_nFormatCode;
	UINT  m_nInterrogationCode;
	INT  m_nRelatedParameterRef;
	INT  m_nValidityParameterRef;
	INT  m_nWidth[2];
	INT  m_nDigits;
	INT  m_nStatus;

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
	VOID SetTypeCode(UINT nPTC);
	UINT GetTypeCode() CONST;
	VOID SetFormatCode(UINT nPFC);
	UINT GetFormatCode() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetWidth(INT nWidth, BOOL bPadded = FALSE);
	INT GetWidth(BOOL bPadded = FALSE) CONST;
	VOID SetOnBoardID(UINT nID);
	UINT GetOnBoardID() CONST;
	VOID SetOnBoardTimerID(UINT nOBTID);
	UINT GetOnBoardTimerID() CONST;
	VOID SetConstValue(ULONGLONG nConstValue);
	ULONGLONG GetConstValue() CONST;
	VOID SetConstValueAsText(LPCTSTR pszConstValue);
	CString GetConstValueAsText() CONST;
	VOID SetRelatedParameter(LPCTSTR pszTag);
	CString GetRelatedParameter() CONST;
	VOID SetRelatedParameterRef(INT nRef);
	INT GetRelatedParameterRef() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityParameterRef(INT nRef);
	INT GetValidityParameterRef() CONST;
	VOID SetValidityValue(ULONGLONG nValidityValue);
	ULONGLONG GetValidityValue() CONST;
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
	VOID SetDerivationExpression(LPCTSTR pszExpression);
	CString GetDerivationExpression() CONST;
	VOID SetTriggerExpression(LPCTSTR pszExpression);
	CString GetTriggerExpression() CONST;
	VOID SetInterrogationInstruction(UINT nInstruction);
	UINT GetInterrogationInstruction() CONST;
	VOID SetCalTables(CONST CStringArray &szTables, CONST CStringArray &szValidityParameters);
	VOID SetCalTables(CONST CStringArray &szTables, CONST CStringArray &szValidityParameters, CONST CLongUIntArray &nValidityValues);
	INT GetCalTables(CStringArray &szTables, CStringArray &szValidityParameters) CONST;
	INT GetCalTables(CStringArray &szTables, CStringArray &szValidityParameters, CLongUIntArray &nValidityValues) CONST;
	VOID SetOolTables(CONST CStringArray &szTables, CONST CStringArray &szValidityParameters);
	VOID SetOolTables(CONST CStringArray &szTables, CONST CStringArray &szValidityParameters, CONST CLongUIntArray &nValidityValues);
	INT GetOolTables(CStringArray &szTables, CStringArray &szValidityParameters) CONST;
	INT GetOolTables(CStringArray &szTables, CStringArray &szValidityParameters, CLongUIntArray &nValidityValues) CONST;
	VOID SetDecimalDigits(INT nDigits);
	INT GetDecimalDigits() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	VOID SetSubTagRefs(CONST CUIntArray &nRefs);
	INT GetSubTagRefs(CUIntArray &nRefs) CONST;
	VOID SetCalTableRefs(CONST CUIntArray &nTableRefs, CONST CUIntArray &nValidityRefs);
	INT GetCalTableRefs(CUIntArray &nTableRefs, CUIntArray &nValidityRefs) CONST;
	VOID SetOolTableRefs(CONST CUIntArray &nTableRefs, CONST CUIntArray &nValidityRefs);
	INT GetOolTableRefs(CUIntArray &nTableRefs, CUIntArray &nValidityRefs) CONST;
	VOID SetTriggerRefs(CONST CUIntArray &nParameterRefs, CONST CUIntArray &nPacketRefs);
	INT GetTriggerRefs(CUIntArray &nParameterRefs, CUIntArray &nPacketRefs) CONST;
	VOID SetValidityRefs(CONST CUIntArray &nRefs);
	INT GetValidityRefs(CUIntArray &nRefs) CONST;

	BOOL Copy(CONST CDatabaseTMParameter *pParameter);
	BOOL Compare(CONST CDatabaseTMParameter *pParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMParameters

class AFX_EXT_CLASS CDatabaseTMParameters : public CPtrArray
{
	// Construction
public:
	CDatabaseTMParameters();
	~CDatabaseTMParameters();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMParameter *pParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTMParameter *GetAt(INT nIndex) CONST;
	CDatabaseTMParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMParameters *pParameters);
	BOOL Compare(CONST CDatabaseTMParameters *pParameters) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMParameterGroup

class AFX_EXT_CLASS CDatabaseTMParameterGroup : public CStringArray
{
	// Construction
public:
	CDatabaseTMParameterGroup();
	~CDatabaseTMParameterGroup();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbParameters;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;

	INT Add(LPCTSTR pszTag);

	INT Find(LPCTSTR pszTag) CONST;

	CString GetAt(INT nIndex) CONST;
	CString operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMParameterGroup *pParameterGroup);
	BOOL Compare(CONST CDatabaseTMParameterGroup *pParameterGroup) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMParameterGroups

class AFX_EXT_CLASS CDatabaseTMParameterGroups : public CPtrArray
{
	// Construction
public:
	CDatabaseTMParameterGroups();
	~CDatabaseTMParameterGroups();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMParameterGroup *pParameterGroup);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMParameterGroup *GetAt(INT nIndex) CONST;
	CDatabaseTMParameterGroup *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMParameterGroups *pParameterGroups);
	BOOL Compare(CONST CDatabaseTMParameterGroups *pParameterGroups) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMNumCalPoint

class AFX_EXT_CLASS CDatabaseTMNumCalPoint : public CObject
{
	friend class CDatabaseTCNumCalPoint;

	// Construction
public:
	CDatabaseTMNumCalPoint();
	CDatabaseTMNumCalPoint(double X, double Y);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		double  X;
		double  Y;
	} DATA, *PDATA, *LPDATA;
private:
	double  m_X;
	double  m_Y;

	// Operations
public:
	VOID SetPoint(double X, double Y);
	VOID GetPoint(double &X, double &Y) CONST;
	double GetX() CONST;
	double GetY() CONST;

	CDatabaseTMNumCalPoint &operator=(CONST CDatabaseTMNumCalPoint &cPoint);
	BOOL operator==(CONST CDatabaseTMNumCalPoint &cPoint) CONST;
	BOOL operator!=(CONST CDatabaseTMNumCalPoint &cPoint) CONST;

	VOID Copy(CONST CDatabaseTMNumCalPoint *pPoint);
	VOID Copy(CONST CDatabaseTCNumCalPoint *pPoint);
	BOOL Compare(CONST CDatabaseTMNumCalPoint *pPoint) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMNumCalTable

// Specify the telemetry calibration table related identifiers
#define TMCALTABLE_FORMAT_POINTS   (1<<0)
#define TMCALTABLE_FORMAT_POLYNOMIALCURVE   (1<<1)
#define TMCALTABLE_FORMAT_LOGARITHMICCURVE   (1<<2)
#define TMCALTABLE_ENGCODING_UNSIGNEDINTEGER   (1<<3)
#define TMCALTABLE_ENGCODING_SIGNEDINTEGER   (1<<4)
#define TMCALTABLE_ENGCODING_FLOATINGPOINT   (1<<5)
#define TMCALTABLE_RAWCODING_UNSIGNEDINTEGER   (1<<6)
#define TMCALTABLE_RAWCODING_SIGNEDINTEGER   (1<<7)
#define TMCALTABLE_RAWCODING_FLOATINGPOINT   (1<<8)
#define TMCALTABLE_RAWRADIX_HEXADECIMAL   (1<<9)
#define TMCALTABLE_RAWRADIX_DECIMAL   (1<<10)
#define TMCALTABLE_RAWRADIX_OCTAL   (1<<11)
#define TMCALTABLE_RAWRADIX_BINARY   (1<<12)
#define TMCALTABLE_INTERPRETATION_FULL   (1<<13)
#define TMCALTABLE_INTERPRETATION_EXTRAPOLATE   (1<<14)
#define TMCALTABLE_RECORDSTATUS_NONE   (1<<0)
#define TMCALTABLE_RECORDSTATUS_NEW   (1<<1)
#define TMCALTABLE_RECORDSTATUS_DRAFT   (1<<2)
#define TMCALTABLE_RECORDSTATUS_CHANGED   (1<<3)
#define TMCALTABLE_RECORDSTATUS_DELETED   (1<<4)
#define TMCALTABLE_RECORDSTATUS_DEFAULT   (TMCALTABLE_RECORDSTATUS_NONE | TMCALTABLE_RECORDSTATUS_NEW | TMCALTABLE_RECORDSTATUS_CHANGED)
#define TMCALTABLE_RECORDSTATUS_ALL   (TMCALTABLE_RECORDSTATUS_NONE | TMCALTABLE_RECORDSTATUS_DRAFT | TMCALTABLE_RECORDSTATUS_NEW | TMCALTABLE_RECORDSTATUS_CHANGED | TMCALTABLE_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTMNumCalTable : public CPtrArray
{
	friend class CDatabaseTCNumCalTable;

	// Construction
public:
	CDatabaseTMNumCalTable();
	~CDatabaseTMNumCalTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbUnit;
		INT  cbDescription;
		INT  cbPoints;
		INT  nPoints;
		INT  nStatus;
		UINT  nAttributes;
		double  fCoefficient[5];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szUnit;
	CString  m_szDescription;
	double  m_fCoefficient[5];
	UINT  m_nAttributes;
	INT  m_nPoints;
	INT  m_nStatus;

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
	VOID SetPolynomialCurve(double A0, double A1 = 0.0, double A2 = 0.0, double A3 = 0.0, double A4 = 0.0);
	BOOL GetPolynomialCurve(double &A0, double &A1, double &A2, double &A3, double &A4) CONST;
	BOOL IsPolynomialCurve() CONST;
	VOID SetLogarithmicCurve(double A0, double A1 = 0.0, double A2 = 0.0, double A3 = 0.0, double A4 = 0.0);
	BOOL GetLogarithmicCurve(double &A0, double &A1, double &A2, double &A3, double &A4) CONST;
	BOOL IsLogarithmicCurve() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTMNumCalPoint *pPoint);

	INT Find(double X) CONST;

	CDatabaseTMNumCalPoint *GetAt(INT nIndex) CONST;
	CDatabaseTMNumCalPoint *operator[](INT nIndex) CONST;

	double Calibrate(double X, BOOL bExtrapolate = TRUE) CONST;
	double Calibrate(double X, BOOL bExtrapolate, BOOL &bOut) CONST;
	CString CalibrateAsText(double X, INT nDigits = -1, BOOL bExtrapolate = TRUE) CONST;
	CString CalibrateAsText(double X, INT nDigits, BOOL bExtrapolate, BOOL &bOut) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMNumCalTable *pTable);
	BOOL Copy(CONST CDatabaseTCNumCalTable *pTable);
	BOOL Compare(CONST CDatabaseTMNumCalTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(double X, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMNumCalTables

class AFX_EXT_CLASS CDatabaseTMNumCalTables : public CPtrArray
{
	friend class CDatabaseTCNumCalTables;

	// Construction
public:
	CDatabaseTMNumCalTables();
	~CDatabaseTMNumCalTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMNumCalTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMNumCalTable *GetAt(INT nIndex) CONST;
	CDatabaseTMNumCalTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMNumCalTables *pTables);
	BOOL Copy(CONST CDatabaseTCNumCalTables *pTables);
	BOOL Compare(CONST CDatabaseTMNumCalTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMTxtCalPoint

class AFX_EXT_CLASS CDatabaseTMTxtCalPoint : public CObject
{
	friend class CDatabaseTCTxtCalPoint;

	// Construction
public:
	CDatabaseTMTxtCalPoint();
	CDatabaseTMTxtCalPoint(double X, LPCTSTR Y);
	CDatabaseTMTxtCalPoint(double X1, double X2, LPCTSTR Y);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbY;
		double  X[2];
	} DATA, *PDATA, *LPDATA;
private:
	double  m_X[2];
	CString  m_Y;

	// Operations
public:
	VOID SetPoint(double X, LPCTSTR Y);
	BOOL GetPoint(double &X, CString &Y) CONST;
	VOID SetRange(double X1, double X2, LPCTSTR Y);
	BOOL GetRange(double &X1, double &X2, CString &Y) CONST;

	CDatabaseTMTxtCalPoint &operator=(CONST CDatabaseTMTxtCalPoint &cPoint);
	BOOL operator==(CONST CDatabaseTMTxtCalPoint &cPoint) CONST;
	BOOL operator!=(CONST CDatabaseTMTxtCalPoint &cPoint) CONST;

	VOID Copy(CONST CDatabaseTMTxtCalPoint *pPoint);
	VOID Copy(CONST CDatabaseTCTxtCalPoint *pPoint);
	BOOL Compare(CONST CDatabaseTMTxtCalPoint *pPoint) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMTxtCalTable

class AFX_EXT_CLASS CDatabaseTMTxtCalTable : public CPtrArray
{
	friend class CDatabaseTCTxtCalTable;

	// Construction
public:
	CDatabaseTMTxtCalTable();
	~CDatabaseTMTxtCalTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbPoints;
		INT  nPoints;
		INT  nStatus;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	UINT  m_nAttributes;
	INT  m_nPoints;
	INT  m_nStatus;

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
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTMTxtCalPoint *pPoint);

	INT Find(double X) CONST;

	CDatabaseTMTxtCalPoint *GetAt(INT nIndex) CONST;
	CDatabaseTMTxtCalPoint *operator[](INT nIndex) CONST;

	CString Translate(double X, INT nDigits = -1) CONST;
	CString Translate(double X, INT nDigits, BOOL &bOut) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMTxtCalTable *pTable);
	BOOL Copy(CONST CDatabaseTCTxtCalTable *pTable);
	BOOL Compare(CONST CDatabaseTMTxtCalTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(double X1, double X2, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMTxtCalTables

class AFX_EXT_CLASS CDatabaseTMTxtCalTables : public CPtrArray
{
	friend class CDatabaseTCTxtCalTables;

	// Construction
public:
	CDatabaseTMTxtCalTables();
	~CDatabaseTMTxtCalTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMTxtCalTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMTxtCalTable *GetAt(INT nIndex) CONST;
	CDatabaseTMTxtCalTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMTxtCalTables *pTables);
	BOOL Copy(CONST CDatabaseTCTxtCalTables *pTables);
	BOOL Compare(CONST CDatabaseTMTxtCalTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMNumOolLimit

// Specify the telemetry out-of-limit related identifiers
#define TMOOLLIMIT_TYPE_NONE   0
#define TMOOLLIMIT_TYPE_SOFT   1
#define TMOOLLIMIT_TYPE_HARD   2
#define TMOOLLIMIT_TYPE_DELTA   3
#define TMOOLLIMIT_TYPE_STATUSCONSISTENCY   4
#define TMOOLLIMIT_TYPE_EVENT   5

class AFX_EXT_CLASS CDatabaseTMNumOolLimit : public CObject
{
	friend class CDatabaseTCNumOolLimit;

	// Construction
public:
	CDatabaseTMNumOolLimit();
	CDatabaseTMNumOolLimit(UINT nType, double fLow, double fHigh);
	CDatabaseTMNumOolLimit(double fDelta, BOOL bMinimum = TRUE);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbValidityParameter;
		INT  nValidityParameterRef;
		UINT  nLimitType;
		UINT  nLimitOrder;
		BOOL  bLimits[2];
		double  fLimits[2];
		ULONGLONG  nValidityValue;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nLimitType;
	UINT  m_nLimitOrder;
	BOOL  m_bLimits[2];
	double  m_fLimits[2];
	CString  m_szValidityParameter;
	ULONGLONG  m_nValidityValue;
	INT  m_nValidityParameterRef;

	// Operations
public:
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetOrder(UINT nOrder);
	UINT GetOrder() CONST;
	BOOL SetRange(UINT nType, double fLow, double fHigh);
	BOOL GetRange(UINT &nType, double &fLow, double &fHigh) CONST;
	BOOL SetDelta(double fDelta, BOOL bMinimum = TRUE);
	BOOL GetDelta(double &fDelta, BOOL bMinimum = TRUE) CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityParameterRef(INT nRef);
	INT GetValidityParameterRef() CONST;
	VOID SetValidityValue(ULONGLONG nValidityValue);
	ULONGLONG GetValidityValue() CONST;

	CDatabaseTMNumOolLimit &operator=(CONST CDatabaseTMNumOolLimit &cLimit);
	BOOL operator==(CONST CDatabaseTMNumOolLimit &cLimit) CONST;
	BOOL operator!=(CONST CDatabaseTMNumOolLimit &cLimit) CONST;

	VOID Copy(CONST CDatabaseTMNumOolLimit *pLimit);
	VOID Copy(CONST CDatabaseTCNumOolLimit *pLimit);
	BOOL Compare(CONST CDatabaseTMNumOolLimit *pLimit) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMNumOolTable

// Specify the telemetry out-of-limit table related identifiers
#define TMOOLTABLE_CHECK_RAW   (1<<0)
#define TMOOLTABLE_CHECK_CALIBRATED   (1<<1)
#define TMOOLTABLE_CODING_UNSIGNEDINTEGER   (1<<2)
#define TMOOLTABLE_CODING_SIGNEDINTEGER   (1<<3)
#define TMOOLTABLE_CODING_FLOATINGPOINT   (1<<4)
#define TMOOLTABLE_CODING_TEXTSTRING   (1<<5)
#define TMOOLTABLE_RADIX_HEXADECIMAL   (1<<6)
#define TMOOLTABLE_RADIX_DECIMAL   (1<<7)
#define TMOOLTABLE_RADIX_OCTAL   (1<<8)
#define TMOOLTABLE_RADIX_BINARY   (1<<9)
#define TMOOLTABLE_RECORDSTATUS_NONE   (1<<0)
#define TMOOLTABLE_RECORDSTATUS_NEW   (1<<1)
#define TMOOLTABLE_RECORDSTATUS_DRAFT   (1<<2)
#define TMOOLTABLE_RECORDSTATUS_CHANGED   (1<<3)
#define TMOOLTABLE_RECORDSTATUS_DELETED   (1<<4)
#define TMOOLTABLE_RECORDSTATUS_DEFAULT   (TMOOLTABLE_RECORDSTATUS_NONE | TMOOLTABLE_RECORDSTATUS_NEW | TMOOLTABLE_RECORDSTATUS_CHANGED)
#define TMOOLTABLE_RECORDSTATUS_ALL   (TMOOLTABLE_RECORDSTATUS_NONE | TMOOLTABLE_RECORDSTATUS_DRAFT | TMOOLTABLE_RECORDSTATUS_NEW | TMOOLTABLE_RECORDSTATUS_CHANGED | TMOOLTABLE_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTMNumOolTable : public CPtrArray
{
	friend class CDatabaseTCNumOolTable;

	// Construction
public:
	CDatabaseTMNumOolTable();
	~CDatabaseTMNumOolTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbUnit;
		INT  cbDescription;
		INT  cbLimits;
		INT  nChecks;
		INT  nStatus;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szUnit;
	CString  m_szDescription;
	UINT  m_nAttributes;
	INT  m_nChecks;
	INT  m_nLimits;
	INT  m_nStatus;

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
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetLimits(INT nLimits);
	INT GetLimits() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTMNumOolLimit *pLimit);

	INT Find(double fLow, double fHigh, BOOL bDelta = FALSE) CONST;
	INT Find(double fDelta) CONST;

	CDatabaseTMNumOolLimit *GetAt(INT nIndex) CONST;
	CDatabaseTMNumOolLimit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMNumOolTable *pTable);
	BOOL Copy(CONST CDatabaseTCNumOolTable *pTable);
	BOOL Compare(CONST CDatabaseTMNumOolTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMNumOolTables

class AFX_EXT_CLASS CDatabaseTMNumOolTables : public CPtrArray
{
	friend class CDatabaseTCNumOolTables;

	// Construction
public:
	CDatabaseTMNumOolTables();
	~CDatabaseTMNumOolTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMNumOolTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMNumOolTable *GetAt(INT nIndex) CONST;
	CDatabaseTMNumOolTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMNumOolTables *pTables);
	BOOL Copy(CONST CDatabaseTCNumOolTables *pTables);
	BOOL Compare(CONST CDatabaseTMNumOolTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMTxtOolLimit

class AFX_EXT_CLASS CDatabaseTMTxtOolLimit : public CObject
{
	friend class CDatabaseTCTxtOolLimit;

	// Construction
public:
	CDatabaseTMTxtOolLimit();
	CDatabaseTMTxtOolLimit(double fLow, double fHigh);
	CDatabaseTMTxtOolLimit(LPCTSTR pszLow, LPCTSTR pszHigh);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbLimits[2];
		INT  cbValidityParameter;
		INT  nValidityParameterRef;
		UINT  nLimitType;
		UINT  nLimitOrder;
		double  fLimits[2];
		ULONGLONG  nValidityValue;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nLimitType;
	UINT  m_nLimitOrder;
	double  m_fLimits[2];
	CString  m_szLimits[2];
	CString  m_szValidityParameter;
	ULONGLONG  m_nValidityValue;
	INT  m_nValidityParameterRef;

	// Operations
public:
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetOrder(UINT nOrder);
	UINT GetOrder() CONST;
	VOID SetLimit(double fLimit);
	VOID SetLimit(LPCTSTR pszLimit);
	BOOL GetLimit(double &fLimit) CONST;
	BOOL GetLimit(CString &szLimit) CONST;
	VOID SetRange(double fLow, double fHigh);
	VOID SetRange(LPCTSTR pszLow, LPCTSTR pszHigh);
	BOOL GetRange(double &fLow, double &fHigh) CONST;
	BOOL GetRange(CString &szLow, CString &szHigh) CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityParameterRef(INT nRef);
	INT GetValidityParameterRef() CONST;
	VOID SetValidityValue(ULONGLONG nValidityValue);
	ULONGLONG GetValidityValue() CONST;

	CDatabaseTMTxtOolLimit &operator=(CONST CDatabaseTMTxtOolLimit &cLimit);
	BOOL operator==(CONST CDatabaseTMTxtOolLimit &cLimit) CONST;
	BOOL operator!=(CONST CDatabaseTMTxtOolLimit &cLimit) CONST;

	VOID Copy(CONST CDatabaseTMTxtOolLimit *pLimit);
	VOID Copy(CONST CDatabaseTCTxtOolLimit *pLimit);
	BOOL Compare(CONST CDatabaseTMTxtOolLimit *pLimit) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMTxtOolTable

class AFX_EXT_CLASS CDatabaseTMTxtOolTable : public CPtrArray
{
	friend class CDatabaseTCTxtOolTable;

	// Construction
public:
	CDatabaseTMTxtOolTable();
	~CDatabaseTMTxtOolTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbLimits;
		INT  nChecks;
		INT  nStatus;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	UINT  m_nAttributes;
	INT  m_nChecks;
	INT  m_nLimits;
	INT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetLimits(INT nLimits);
	INT GetLimits() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTMTxtOolLimit *pLimit);

	INT Find(double fLimit) CONST;
	INT Find(LPCTSTR pszLimit) CONST;
	INT Find(double fLow, double fHigh) CONST;
	INT Find(LPCTSTR pszLow, LPCTSTR pszHigh) CONST;

	CDatabaseTMTxtOolLimit *GetAt(INT nIndex) CONST;
	CDatabaseTMTxtOolLimit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMTxtOolTable *pTable);
	BOOL Copy(CONST CDatabaseTCTxtOolTable *pTable);
	BOOL Compare(CONST CDatabaseTMTxtOolTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTMTxtOolTables

class AFX_EXT_CLASS CDatabaseTMTxtOolTables : public CPtrArray
{
	friend class CDatabaseTCTxtOolTables;

	// Construction
public:
	CDatabaseTMTxtOolTables();
	~CDatabaseTMTxtOolTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTMTxtOolTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTMTxtOolTable *GetAt(INT nIndex) CONST;
	CDatabaseTMTxtOolTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTMTxtOolTables *pTables);
	BOOL Copy(CONST CDatabaseTCTxtOolTables *pTables);
	BOOL Compare(CONST CDatabaseTMTxtOolTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCParameter

// Specify the telecommand parameter related identifiers
#define TCPARAMETER_TYPE_NORMAL   (((ULONGLONG) 1)<<0)
#define TCPARAMETER_TYPE_FUNCTION   (((ULONGLONG) 1)<<1)
#define TCPARAMETER_TYPE_SEQUENCE   (((ULONGLONG) 1)<<2)
#define TCPARAMETER_TYPE_CONSTANT   (((ULONGLONG) 1)<<3)
#define TCPARAMETER_TYPE_VARIABLE   (((ULONGLONG) 1)<<4)
#define TCPARAMETER_VTYPE_RAW   (((ULONGLONG) 1)<<5)
#define TCPARAMETER_VTYPE_CALIBRATED   (((ULONGLONG) 1)<<6)
#define TCPARAMETER_VTYPE_COMMANDID   (((ULONGLONG) 1)<<7)
#define TCPARAMETER_VTYPE_PARAMETERID   (((ULONGLONG) 1)<<8)
#define TCPARAMETER_VTYPE_PARAMETERSET   (((ULONGLONG) 1)<<9)
#define TCPARAMETER_VTYPE_FUNCTION   (((ULONGLONG) 1)<<10)
#define TCPARAMETER_VTYPE_SEQUENCE   (((ULONGLONG) 1)<<11)
#define TCPARAMETER_VTYPE_FORMAL   (((ULONGLONG) 1)<<12)
#define TCPARAMETER_VTYPE_CUSTOM   (((ULONGLONG) 1)<<13)
#define TCPARAMETER_VTYPE_AUTO   (((ULONGLONG) 1)<<14)
#define TCPARAMETER_STANDARD_IEEE  (((ULONGLONG) 1)<<15)
#define TCPARAMETER_STANDARD_USAF  (((ULONGLONG) 1)<<16)
#define TCPARAMETER_STANDARD_DOUBLEPRECISION  (((ULONGLONG) 1)<<17)
#define TCPARAMETER_CODING_BITPATTERN   (((ULONGLONG) 1)<<18)
#define TCPARAMETER_CODING_SIGNEDINTEGER   (((ULONGLONG) 1)<<19)
#define TCPARAMETER_CODING_UNSIGNEDINTEGER   (((ULONGLONG) 1)<<20)
#define TCPARAMETER_CODING_FLOATINGPOINT   (((ULONGLONG) 1)<<21)
#define TCPARAMETER_CODING_TEXTSTRING   (((ULONGLONG) 1)<<22)
#define TCPARAMETER_CODING_ABSOLUTETIME   (((ULONGLONG) 1)<<23)
#define TCPARAMETER_CODING_RELATIVETIME   (((ULONGLONG) 1)<<24)
#define TCPARAMETER_CODING_TIME   (TCPARAMETER_CODING_ABSOLUTETIME | TCPARAMETER_CODING_RELATIVETIME)
#define TCPARAMETER_RADIX_BINARY   (((ULONGLONG) 1)<<25)
#define TCPARAMETER_RADIX_OCTAL   (((ULONGLONG) 1)<<26)
#define TCPARAMETER_RADIX_DECIMAL   (((ULONGLONG) 1)<<27)
#define TCPARAMETER_RADIX_HEXADECIMAL   (((ULONGLONG) 1)<<28)
#define TCPARAMETER_CALIBRATION_NONE   (((ULONGLONG) 1)<<29)
#define TCPARAMETER_CALIBRATION_NUMERICAL   (((ULONGLONG) 1)<<30)
#define TCPARAMETER_CALIBRATION_STATUS   (((ULONGLONG) 1)<<31)
#define TCPARAMETER_CALIBRATION_ENABLED   (((ULONGLONG) 1)<<32)
#define TCPARAMETER_CALIBRATION_DISABLED   (((ULONGLONG) 1)<<33)
#define TCPARAMETER_INTERPRETATION_FULL   (((ULONGLONG) 1)<<34)
#define TCPARAMETER_INTERPRETATION_EXTRAPOLATE   (((ULONGLONG) 1)<<35)
#define TCPARAMETER_FLAG_NOTIMECORRELATION   (((ULONGLONG) 1)<<36)
#define TCPARAMETER_FLAG_TIMECORRELATION   (((ULONGLONG) 1)<<37)
#define TCPARAMETER_RECORDSTATUS_NONE   (1<<0)
#define TCPARAMETER_RECORDSTATUS_NEW   (1<<1)
#define TCPARAMETER_RECORDSTATUS_DRAFT   (1<<2)
#define TCPARAMETER_RECORDSTATUS_CHANGED   (1<<3)
#define TCPARAMETER_RECORDSTATUS_DELETED   (1<<4)
#define TCPARAMETER_RECORDSTATUS_DEFAULT   (TCPARAMETER_RECORDSTATUS_NONE | TCPARAMETER_RECORDSTATUS_NEW | TCPARAMETER_RECORDSTATUS_CHANGED)
#define TCPARAMETER_RECORDSTATUS_ALL   (TCPARAMETER_RECORDSTATUS_NONE | TCPARAMETER_RECORDSTATUS_DRAFT | TCPARAMETER_RECORDSTATUS_NEW | TCPARAMETER_RECORDSTATUS_CHANGED | TCPARAMETER_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCParameter : public CObject
{
	// Construction
public:
	CDatabaseTCParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbUnit;
		INT  cbDescription;
		INT  cbCalTable;
		INT  cbOolTable;
		INT  cbConstValue;
		INT  nCalTableRef;
		INT  nOolTableRef;
		INT  nBytePos;
		INT  nBitPos;
		INT  nWidth;
		INT  nStatus;
		UINT  nOBTID;
		UINT  nTypeCode;
		UINT  nFormatCode;
		ULONGLONG  nAttributes;
		ULONGLONG  nDispFormat;
		ULONGLONG  nConstValue;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CString  m_szUnit;
	CString  m_szDescription;
	CString  m_szCalTable;
	CString  m_szOolTable;
	CString  m_szConstValue;
	ULONGLONG  m_nAttributes;
	ULONGLONG  m_nDispFormat;
	ULONGLONG  m_nConstValue;
	UINT  m_nOBTID;
	UINT  m_nTypeCode;
	UINT  m_nFormatCode;
	INT  m_nCalTableRef;
	INT  m_nOolTableRef;
	INT  m_nBytePos;
	INT  m_nBitPos;
	INT  m_nWidth;
	INT  m_nStatus;

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
	ULONGLONG GetAttributes() CONST;
	VOID SetDisplayFormat(ULONGLONG nFormat);
	ULONGLONG GetDisplayFormat() CONST;
	VOID SetBytePos(INT nPos);
	INT GetBytePos() CONST;
	VOID SetBitPos(INT nPos);
	INT GetBitPos() CONST;
	VOID SetWidth(INT nWidth);
	INT GetWidth() CONST;
	VOID SetOnBoardTimerID(UINT nOBTID);
	UINT GetOnBoardTimerID() CONST;
	VOID SetConstValue(ULONGLONG nConstValue);
	ULONGLONG GetConstValue() CONST;
	VOID SetConstValueAsText(LPCTSTR pszConstValue);
	CString GetConstValueAsText() CONST;
	VOID SetCalTable(LPCTSTR pszTable);
	CString GetCalTable() CONST;
	VOID SetCalTableRef(INT nTableRef);
	INT GetCalTableRef() CONST;
	VOID SetOolTable(LPCTSTR pszTables);
	CString GetOolTable() CONST;
	VOID SetOolTableRef(INT nTableRef);
	INT GetOolTableRef() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	BOOL Copy(CONST CDatabaseTCParameter *pParameter);
	BOOL Compare(CONST CDatabaseTCParameter *pParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCParameters

class AFX_EXT_CLASS CDatabaseTCParameters : public CPtrArray
{
	// Construction
public:
	CDatabaseTCParameters();
	~CDatabaseTCParameters();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCParameter *pParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTCParameter *GetAt(INT nIndex) CONST;
	CDatabaseTCParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCParameters *pParameters);
	BOOL Compare(CONST CDatabaseTCParameters *pParameters) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCNumCalPoint

class AFX_EXT_CLASS CDatabaseTCNumCalPoint : public CObject
{
	friend class CDatabaseTMNumCalPoint;

	// Construction
public:
	CDatabaseTCNumCalPoint();
	CDatabaseTCNumCalPoint(double X, double Y);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		double  X;
		double  Y;
	} DATA, *PDATA, *LPDATA;
private:
	double  m_X;
	double  m_Y;

	// Operations
public:
	VOID SetPoint(double X, double Y);
	VOID GetPoint(double &X, double &Y) CONST;
	double GetX() CONST;
	double GetY() CONST;

	CDatabaseTCNumCalPoint &operator=(CONST CDatabaseTCNumCalPoint &cPoint);
	BOOL operator==(CONST CDatabaseTCNumCalPoint &cPoint) CONST;
	BOOL operator!=(CONST CDatabaseTCNumCalPoint &cPoint) CONST;

	VOID Copy(CONST CDatabaseTCNumCalPoint *pPoint);
	VOID Copy(CONST CDatabaseTMNumCalPoint *pPoint);
	BOOL Compare(CONST CDatabaseTCNumCalPoint *pPoint) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCNumCalTable

// Specify the telecommand calibration table related identifiers
#define TCCALTABLE_FORMAT_POINTS   (1<<0)
#define TCCALTABLE_ENGCODING_UNSIGNEDINTEGER   (1<<1)
#define TCCALTABLE_ENGCODING_SIGNEDINTEGER   (1<<2)
#define TCCALTABLE_ENGCODING_FLOATINGPOINT   (1<<3)
#define TCCALTABLE_RAWCODING_UNSIGNEDINTEGER   (1<<4)
#define TCCALTABLE_RAWCODING_SIGNEDINTEGER   (1<<5)
#define TCCALTABLE_RAWCODING_FLOATINGPOINT   (1<<6)
#define TCCALTABLE_RAWRADIX_HEXADECIMAL   (1<<7)
#define TCCALTABLE_RAWRADIX_DECIMAL   (1<<8)
#define TCCALTABLE_RAWRADIX_OCTAL   (1<<9)
#define TCCALTABLE_RAWRADIX_BINARY   (1<<10)
#define TCCALTABLE_INTERPRETATION_FULL   (1<<11)
#define TCCALTABLE_INTERPRETATION_EXTRAPOLATE   (1<<12)
#define TCCALTABLE_RECORDSTATUS_NONE   (1<<0)
#define TCCALTABLE_RECORDSTATUS_NEW   (1<<1)
#define TCCALTABLE_RECORDSTATUS_DRAFT   (1<<2)
#define TCCALTABLE_RECORDSTATUS_CHANGED   (1<<3)
#define TCCALTABLE_RECORDSTATUS_DELETED   (1<<4)
#define TCCALTABLE_RECORDSTATUS_DEFAULT   (TCCALTABLE_RECORDSTATUS_NONE | TCCALTABLE_RECORDSTATUS_NEW | TCCALTABLE_RECORDSTATUS_CHANGED)
#define TCCALTABLE_RECORDSTATUS_ALL   (TCCALTABLE_RECORDSTATUS_NONE | TCCALTABLE_RECORDSTATUS_DRAFT | TCCALTABLE_RECORDSTATUS_NEW | TCCALTABLE_RECORDSTATUS_CHANGED | TCCALTABLE_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCNumCalTable : public CPtrArray
{
	friend class CDatabaseTMNumCalTable;

	// Construction
public:
	CDatabaseTCNumCalTable();
	~CDatabaseTCNumCalTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbUnit;
		INT  cbDescription;
		INT  cbPoints;
		INT  nPoints;
		INT  nStatus;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szUnit;
	CString  m_szDescription;
	UINT  m_nAttributes;
	INT  m_nPoints;
	INT  m_nStatus;

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
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCNumCalPoint *pPoint);

	INT Find(double X) CONST;

	CDatabaseTCNumCalPoint *GetAt(INT nIndex) CONST;
	CDatabaseTCNumCalPoint *operator[](INT nIndex) CONST;

	double Calibrate(double X, BOOL bExtrapolate = TRUE) CONST;
	double Calibrate(double X, BOOL bExtrapolate, BOOL &bOut) CONST;
	CString CalibrateAsText(double X, INT nDigits = -1, BOOL bExtrapolate = TRUE) CONST;
	CString CalibrateAsText(double X, INT nDigits, BOOL bExtrapolate, BOOL &bOut) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCNumCalTable *pTable);
	BOOL Copy(CONST CDatabaseTMNumCalTable *pTable);
	BOOL Compare(CONST CDatabaseTCNumCalTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(double X, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCNumCalTables

class AFX_EXT_CLASS CDatabaseTCNumCalTables : public CPtrArray
{
	friend class CDatabaseTMNumCalTables;

	// Construction
public:
	CDatabaseTCNumCalTables();
	~CDatabaseTCNumCalTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCNumCalTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCNumCalTable *GetAt(INT nIndex) CONST;
	CDatabaseTCNumCalTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCNumCalTables *pTables);
	BOOL Copy(CONST CDatabaseTMNumCalTables *pTables);
	BOOL Compare(CONST CDatabaseTCNumCalTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCTxtCalPoint

class AFX_EXT_CLASS CDatabaseTCTxtCalPoint : public CObject
{
	friend class CDatabaseTMTxtCalPoint;

	// Construction
public:
	CDatabaseTCTxtCalPoint();
	CDatabaseTCTxtCalPoint(double X, LPCTSTR Y);
	CDatabaseTCTxtCalPoint(double X1, double X2, LPCTSTR Y);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbY;
		double  X[2];
	} DATA, *PDATA, *LPDATA;
private:
	double  m_X[2];
	CString  m_Y;

	// Operations
public:
	VOID SetPoint(double X, LPCTSTR Y);
	BOOL GetPoint(double &X, CString &Y) CONST;
	VOID SetRange(double X1, double X2, LPCTSTR Y);
	BOOL GetRange(double &X1, double &X2, CString &Y) CONST;

	CDatabaseTCTxtCalPoint &operator=(CONST CDatabaseTCTxtCalPoint &cPoint);
	BOOL operator==(CONST CDatabaseTCTxtCalPoint &cPoint) CONST;
	BOOL operator!=(CONST CDatabaseTCTxtCalPoint &cPoint) CONST;

	VOID Copy(CONST CDatabaseTCTxtCalPoint *pPoint);
	VOID Copy(CONST CDatabaseTMTxtCalPoint *pPoint);
	BOOL Compare(CONST CDatabaseTCTxtCalPoint *pPoint) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCTxtCalTable

class AFX_EXT_CLASS CDatabaseTCTxtCalTable : public CPtrArray
{
	friend class CDatabaseTMTxtCalTable;

	// Construction
public:
	CDatabaseTCTxtCalTable();
	~CDatabaseTCTxtCalTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbPoints;
		INT  nPoints;
		INT  nStatus;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	UINT  m_nAttributes;
	INT  m_nPoints;
	INT  m_nStatus;

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
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCTxtCalPoint *pPoint);

	INT Find(double X) CONST;

	CDatabaseTCTxtCalPoint *GetAt(INT nIndex) CONST;
	CDatabaseTCTxtCalPoint *operator[](INT nIndex) CONST;

	CString Translate(double X, INT nDigits = -1) CONST;
	CString Translate(double X, INT nDigits, BOOL &bOut) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCTxtCalTable *pTable);
	BOOL Copy(CONST CDatabaseTMTxtCalTable *pTable);
	BOOL Compare(CONST CDatabaseTCTxtCalTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(double X1, double X2, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCTxtCalTables

class AFX_EXT_CLASS CDatabaseTCTxtCalTables : public CPtrArray
{
	friend class CDatabaseTMTxtCalTables;

	// Construction
public:
	CDatabaseTCTxtCalTables();
	~CDatabaseTCTxtCalTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCTxtCalTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCTxtCalTable *GetAt(INT nIndex) CONST;
	CDatabaseTCTxtCalTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCTxtCalTables *pTables);
	BOOL Copy(CONST CDatabaseTMTxtCalTables *pTables);
	BOOL Compare(CONST CDatabaseTCTxtCalTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCNumOolLimit

// Specify the telecommand out-of-limit related identifiers
#define TCOOLLIMIT_TYPE_NONE   0
#define TCOOLLIMIT_TYPE_SOFT   1
#define TCOOLLIMIT_TYPE_HARD   2
#define TCOOLLIMIT_TYPE_DELTA   3
#define TCOOLLIMIT_TYPE_STATUSCONSISTENCY   4
#define TCOOLLIMIT_TYPE_EVENT   5

class AFX_EXT_CLASS CDatabaseTCNumOolLimit : public CObject
{
	friend class CDatabaseTMNumOolLimit;

	// Construction
public:
	CDatabaseTCNumOolLimit();
	CDatabaseTCNumOolLimit(UINT nType, double fLow, double fHigh);
	CDatabaseTCNumOolLimit(double fDelta, BOOL bMinimum = TRUE);
	CDatabaseTCNumOolLimit(TIMETAG tStart, TIMETAG tStop);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbValidityParameter;
		INT  nValidityParameterRef;
		UINT  nLimitType;
		UINT  nLimitOrder;
		BOOL  bLimits[3];
		double  fLimits[2];
		TIMETAG  tLimits[2];
		ULONGLONG  nValidityValue;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nLimitType;
	UINT  m_nLimitOrder;
	BOOL  m_bLimits[3];
	double  m_fLimits[2];
	TIMETAG  m_tLimits[2];
	CString  m_szValidityParameter;
	ULONGLONG  m_nValidityValue;
	INT  m_nValidityParameterRef;

	// Operations
public:
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetOrder(UINT nOrder);
	UINT GetOrder() CONST;
	BOOL SetRange(UINT nType, double fLow, double fHigh);
	BOOL GetRange(UINT &nType, double &fLow, double &fHigh) CONST;
	BOOL SetDelta(double fDelta, BOOL bMinimum = TRUE);
	BOOL GetDelta(double &fDelta, BOOL bMinimum = TRUE) CONST;
	BOOL SetTimeSpan(TIMETAG tStart, TIMETAG tStop);
	BOOL GetTimeSpan(TIMETAG &tStart, TIMETAG &tStop) CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityParameterRef(INT nRef);
	INT GetValidityParameterRef() CONST;
	VOID SetValidityValue(ULONGLONG nValidityValue);
	ULONGLONG GetValidityValue() CONST;

	CDatabaseTCNumOolLimit &operator=(CONST CDatabaseTCNumOolLimit &cLimit);
	BOOL operator==(CONST CDatabaseTCNumOolLimit &cLimit) CONST;
	BOOL operator!=(CONST CDatabaseTCNumOolLimit &cLimit) CONST;

	VOID Copy(CONST CDatabaseTCNumOolLimit *pLimit);
	VOID Copy(CONST CDatabaseTMNumOolLimit *pLimit);
	BOOL Compare(CONST CDatabaseTCNumOolLimit *pLimit) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCNumOolTable

// Specify the telecommand out-of-limit table related identifiers
#define TCOOLTABLE_CHECK_RAW   (1<<0)
#define TCOOLTABLE_CHECK_CALIBRATED   (1<<1)
#define TCOOLTABLE_CODING_UNSIGNEDINTEGER   (1<<2)
#define TCOOLTABLE_CODING_SIGNEDINTEGER   (1<<3)
#define TCOOLTABLE_CODING_FLOATINGPOINT   (1<<4)
#define TCOOLTABLE_CODING_TEXTSTRING   (1<<5)
#define TCOOLTABLE_CODING_ABSOLUTETIME   (1<<6)
#define TCOOLTABLE_CODING_RELATIVETIME   (1<<7)
#define TCOOLTABLE_CODING_TIME   (TCOOLTABLE_CODING_ABSOLUTETIME | TCOOLTABLE_CODING_RELATIVETIME)
#define TCOOLTABLE_RADIX_HEXADECIMAL   (1<<8)
#define TCOOLTABLE_RADIX_DECIMAL   (1<<9)
#define TCOOLTABLE_RADIX_OCTAL   (1<<10)
#define TCOOLTABLE_RADIX_BINARY   (1<<11)
#define TCOOLTABLE_RECORDSTATUS_NONE   (1<<0)
#define TCOOLTABLE_RECORDSTATUS_NEW   (1<<1)
#define TCOOLTABLE_RECORDSTATUS_DRAFT   (1<<2)
#define TCOOLTABLE_RECORDSTATUS_CHANGED   (1<<3)
#define TCOOLTABLE_RECORDSTATUS_DELETED   (1<<4)
#define TCOOLTABLE_RECORDSTATUS_DEFAULT   (TCOOLTABLE_RECORDSTATUS_NONE | TCOOLTABLE_RECORDSTATUS_NEW | TCOOLTABLE_RECORDSTATUS_CHANGED)
#define TCOOLTABLE_RECORDSTATUS_ALL   (TCOOLTABLE_RECORDSTATUS_NONE | TCOOLTABLE_RECORDSTATUS_DRAFT | TCOOLTABLE_RECORDSTATUS_NEW | TCOOLTABLE_RECORDSTATUS_CHANGED | TCOOLTABLE_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCNumOolTable : public CPtrArray
{
	friend class CDatabaseTMNumOolTable;

	// Construction
public:
	CDatabaseTCNumOolTable();
	~CDatabaseTCNumOolTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbUnit;
		INT  cbDescription;
		INT  cbLimits;
		INT  nChecks;
		INT  nStatus;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szUnit;
	CString  m_szDescription;
	UINT  m_nAttributes;
	INT  m_nChecks;
	INT  m_nLimits;
	INT  m_nStatus;

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
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetLimits(INT nLimits);
	INT GetLimits() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCNumOolLimit *pLimit);

	INT Find(double fLow, double fHigh, BOOL bDelta = FALSE) CONST;
	INT Find(double fDelta) CONST;
	INT Find(TIMETAG tStart, TIMETAG tStop) CONST;

	CDatabaseTCNumOolLimit *GetAt(INT nIndex) CONST;
	CDatabaseTCNumOolLimit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCNumOolTable *pTable);
	BOOL Copy(CONST CDatabaseTMNumOolTable *pTable);
	BOOL Compare(CONST CDatabaseTCNumOolTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCNumOolTables

class AFX_EXT_CLASS CDatabaseTCNumOolTables : public CPtrArray
{
	friend class CDatabaseTMNumOolTables;

	// Construction
public:
	CDatabaseTCNumOolTables();
	~CDatabaseTCNumOolTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCNumOolTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCNumOolTable *GetAt(INT nIndex) CONST;
	CDatabaseTCNumOolTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCNumOolTables *pTables);
	BOOL Copy(CONST CDatabaseTMNumOolTables *pTables);
	BOOL Compare(CONST CDatabaseTCNumOolTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCTxtOolLimit

class AFX_EXT_CLASS CDatabaseTCTxtOolLimit : public CObject
{
	friend class CDatabaseTMTxtOolLimit;

	// Construction
public:
	CDatabaseTCTxtOolLimit();
	CDatabaseTCTxtOolLimit(double fLow, double fHigh);
	CDatabaseTCTxtOolLimit(LPCTSTR pszLow, LPCTSTR pszHigh);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbLimits[2];
		INT  cbValidityParameter;
		INT  nValidityParameterRef;
		UINT  nLimitType;
		UINT  nLimitOrder;
		double  fLimits[2];
		ULONGLONG  nValidityValue;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nLimitType;
	UINT  m_nLimitOrder;
	double  m_fLimits[2];
	CString  m_szLimits[2];
	CString  m_szValidityParameter;
	ULONGLONG  m_nValidityValue;
	INT  m_nValidityParameterRef;

	// Operations
public:
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetOrder(UINT nOrder);
	UINT GetOrder() CONST;
	VOID SetLimit(double fLimit);
	VOID SetLimit(LPCTSTR pszLimit);
	BOOL GetLimit(double &fLimit) CONST;
	BOOL GetLimit(CString &szLimit) CONST;
	VOID SetRange(double fLow, double fHigh);
	VOID SetRange(LPCTSTR pszLow, LPCTSTR pszHigh);
	BOOL GetRange(double &fLow, double &fHigh) CONST;
	BOOL GetRange(CString &szLow, CString &szHigh) CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;
	VOID SetValidityParameterRef(INT nRef);
	INT GetValidityParameterRef() CONST;
	VOID SetValidityValue(ULONGLONG nValidityValue);
	ULONGLONG GetValidityValue() CONST;

	CDatabaseTCTxtOolLimit &operator=(CONST CDatabaseTCTxtOolLimit &cLimit);
	BOOL operator==(CONST CDatabaseTCTxtOolLimit &cLimit) CONST;
	BOOL operator!=(CONST CDatabaseTCTxtOolLimit &cLimit) CONST;

	VOID Copy(CONST CDatabaseTCTxtOolLimit *pLimit);
	VOID Copy(CONST CDatabaseTMTxtOolLimit *pLimit);
	BOOL Compare(CONST CDatabaseTCTxtOolLimit *pLimit) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCTxtOolTable

class AFX_EXT_CLASS CDatabaseTCTxtOolTable : public CPtrArray
{
	friend class CDatabaseTMTxtOolTable;

	// Construction
public:
	CDatabaseTCTxtOolTable();
	~CDatabaseTCTxtOolTable();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbLimits;
		INT  nChecks;
		INT  nStatus;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	UINT  m_nAttributes;
	INT  m_nChecks;
	INT  m_nLimits;
	INT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetChecks(INT nChecks);
	INT GetChecks() CONST;
	VOID SetLimits(INT nLimits);
	INT GetLimits() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCTxtOolLimit *pLimit);

	INT Find(double fLimit) CONST;
	INT Find(LPCTSTR pszLimit) CONST;
	INT Find(double fLow, double fHigh) CONST;
	INT Find(LPCTSTR pszLow, LPCTSTR pszHigh) CONST;

	CDatabaseTCTxtOolLimit *GetAt(INT nIndex) CONST;
	CDatabaseTCTxtOolLimit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCTxtOolTable *pTable);
	BOOL Copy(CONST CDatabaseTMTxtOolTable *pTable);
	BOOL Compare(CONST CDatabaseTCTxtOolTable *pTable) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCTxtOolTables

class AFX_EXT_CLASS CDatabaseTCTxtOolTables : public CPtrArray
{
	friend class CDatabaseTMTxtOolTables;

	// Construction
public:
	CDatabaseTCTxtOolTables();
	~CDatabaseTCTxtOolTables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCTxtOolTable *pTable);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCTxtOolTable *GetAt(INT nIndex) CONST;
	CDatabaseTCTxtOolTable *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCTxtOolTables *pTables);
	BOOL Copy(CONST CDatabaseTMTxtOolTables *pTables);
	BOOL Compare(CONST CDatabaseTCTxtOolTables *pTables) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunctionElement

// Specify the telecommand function element related identifiers
#define TCFUNCTIONELEMENT_TYPE_PARAMETER   TCPARAMETER_TYPE_VARIABLE
#define TCFUNCTIONELEMENT_TYPE_CONSTANT   TCPARAMETER_TYPE_CONSTANT
#define TCFUNCTIONELEMENT_VTYPE_RAW   TCPARAMETER_VTYPE_RAW
#define TCFUNCTIONELEMENT_VTYPE_CALIBRATED   TCPARAMETER_VTYPE_CALIBRATED
#define TCFUNCTIONELEMENT_VTYPE_TCPARAMETER   (((ULONGLONG) 1)<<62)
#define TCFUNCTIONELEMENT_VTYPE_TMPARAMETER   (((ULONGLONG) 1)<<63)

class AFX_EXT_CLASS CDatabaseTCFunctionElement : public CObject
{
	// Construction
public:
	CDatabaseTCFunctionElement();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbConstValue[2];
		INT  nGroupSize;
		INT  nBitOffset;
		INT  nBytePos;
		INT  nBitPos;
		INT  nWidth;
		INT  nRef[2];
		ULONGLONG  nAttributes;
		ULONGLONG  nConstValue;
		BOOL  bConstValue;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szConstValue[2];
	ULONGLONG  m_nAttributes;
	ULONGLONG  m_nConstValue;
	BOOL  m_bConstValue;
	INT  m_nGroupSize;
	INT  m_nBitOffset;
	INT  m_nBytePos;
	INT  m_nBitPos;
	INT  m_nWidth;
	INT  m_nRef[2];

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetGroupSize(INT nSize);
	INT GetGroupSize() CONST;
	VOID SetBytePos(INT nPos);
	INT GetBytePos() CONST;
	VOID SetBitPos(INT nPos);
	INT GetBitPos() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetWidth(INT nWidth);
	INT GetWidth() CONST;
	VOID SetConstValue();
	VOID SetConstValue(ULONGLONG nConstValue);
	ULONGLONG GetConstValue() CONST;
	BOOL HasConstValue() CONST;
	VOID SetConstValueAsText(LPCTSTR pszConstValue);
	CString GetConstValueAsText() CONST;
	VOID SetConstValueSource(LPCTSTR pszParameter);
	CString GetConstValueSource() CONST;
	VOID SetConstValueSourceRef(INT nRef);
	INT GetConstValueSourceRef() CONST;

	VOID SetRef(INT nRef);
	INT GetRef() CONST;

	BOOL Copy(CONST CDatabaseTCFunctionElement *pFunctionElement);
	BOOL Compare(CONST CDatabaseTCFunctionElement *pFunctionElement) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunction

// Specify the telecommand function related identifiers
#define TCFUNCTION_TYPE_NORMAL   (((ULONGLONG) 1)<<0)
#define TCFUNCTION_TYPE_CTRLSEG   (((ULONGLONG) 1)<<1)
#define TCFUNCTION_TYPE_CTRLFRM   (((ULONGLONG) 1)<<2)
#define TCFUNCTION_TYPE_SLETE   (((ULONGLONG) 1)<<3)
#define TCFUNCTION_TYPE_NISTE   (((ULONGLONG) 1)<<4)
#define TCFUNCTION_TYPE_NOCRC   (((ULONGLONG) 1)<<5)
#define TCFUNCTION_TYPE_INTGT   (((ULONGLONG) 1)<<6)
#define TCFUNCTION_TYPE_INTG   (((ULONGLONG) 1)<<7)
#define TCFUNCTION_TYPE_HP1   (((ULONGLONG) 1)<<8)
#define TCFUNCTION_TYPE_HP2   (((ULONGLONG) 1)<<9)
#define TCFUNCTION_TYPE_HPC2   (((ULONGLONG) 1)<<10)
#define TCFUNCTION_TYPE_ICS   (((ULONGLONG) 1)<<11)
#define TCFUNCTION_TYPE_RBI   (((ULONGLONG) 1)<<12)
#define TCFUNCTION_TYPE_HL   (((ULONGLONG) 1)<<13)
#define TCFUNCTION_TYPE_ML   (((ULONGLONG) 1)<<14)
#define TCFUNCTION_TYPE_MLP   (((ULONGLONG) 1)<<15)
#define TCFUNCTION_TYPE_RM   (((ULONGLONG) 1)<<16)
#define TCFUNCTION_TYPE_SC   (((ULONGLONG) 1)<<17)
#define TCFUNCTION_TYPE_LSC   (((ULONGLONG) 1)<<18)
#define TCFUNCTION_EXETYPE_IMMEDIATE   (((ULONGLONG) 1)<<19)
#define TCFUNCTION_EXETYPE_TIMETAG   (((ULONGLONG) 1)<<20)
#define TCFUNCTION_EXETYPE_FIRSTSTEP   (((ULONGLONG) 1)<<21)
#define TCFUNCTION_EXETYPE_SECONDSTEP   (((ULONGLONG) 1)<<22)
#define TCFUNCTION_EXETYPE_STANDALONE   (((ULONGLONG) 1)<<23)
#define TCFUNCTION_EXETYPE_NOTSTANDALONE   (((ULONGLONG) 1)<<24)
#define TCFUNCTION_EXETYPE_NOTALLOWED   (((ULONGLONG) 1)<<25)
#define TCFUNCTION_PRIFLAG_NORMAL   (((ULONGLONG) 1)<<26)
#define TCFUNCTION_PRIFLAG_HIGH   (((ULONGLONG) 1)<<27)
#define TCFUNCTION_HAZFLAG_VITAL   (((ULONGLONG) 1)<<28)
#define TCFUNCTION_HAZFLAG_HAZARDOUS   (((ULONGLONG) 1)<<29)
#define TCFUNCTION_HAZFLAG_NONCRITICAL   (((ULONGLONG) 1)<<30)
#define TCFUNCTION_DISPFLAG_AUTHORIZATION   (((ULONGLONG) 1)<<31)
#define TCFUNCTION_ACKFLAG_ACCEPTANCE   (((ULONGLONG) 1)<<32)
#define TCFUNCTION_ACKFLAG_START   (((ULONGLONG) 1)<<33)
#define TCFUNCTION_ACKFLAG_PROGRESS   (((ULONGLONG) 1)<<34)
#define TCFUNCTION_ACKFLAG_COMPLETION   (((ULONGLONG) 1)<<35)
#define TCFUNCTION_PLANFLAG_ALL   (((ULONGLONG) 1)<<36)
#define TCFUNCTION_PLANFLAG_SOC   (((ULONGLONG) 1)<<37)
#define TCFUNCTION_PLANFLAG_FLIGHTDYNAMICS   (((ULONGLONG) 1)<<38)
#define TCFUNCTION_PLANFLAG_PROHIBITED   (((ULONGLONG) 1)<<39)
#define TCFUNCTION_ILSCOPE_NONE   (((ULONGLONG) 1)<<40)
#define TCFUNCTION_ILSCOPE_GLOBAL   (((ULONGLONG) 1)<<41)
#define TCFUNCTION_ILSCOPE_LOCAL   (((ULONGLONG) 1)<<42)
#define TCFUNCTION_ILSCOPE_GLOBALSUBSYSTEM   (((ULONGLONG) 1)<<43)
#define TCFUNCTION_ILSCOPE_LOCALSUBSYSTEM   (((ULONGLONG) 1)<<44)
#define TCFUNCTION_ILSTAGE_RECEPTION   (((ULONGLONG) 1)<<45)
#define TCFUNCTION_ILSTAGE_UPLINK   (((ULONGLONG) 1)<<46)
#define TCFUNCTION_ILSTAGE_ONBOARD   (((ULONGLONG) 1)<<47)
#define TCFUNCTION_ILSTAGE_ACCEPTANCE   (((ULONGLONG) 1)<<48)
#define TCFUNCTION_ILSTAGE_COMPLETION   (((ULONGLONG) 1)<<49)
#define TCFUNCTION_RECORDSTATUS_NONE   (1<<0)
#define TCFUNCTION_RECORDSTATUS_NEW   (1<<1)
#define TCFUNCTION_RECORDSTATUS_DRAFT   (1<<2)
#define TCFUNCTION_RECORDSTATUS_CHANGED   (1<<3)
#define TCFUNCTION_RECORDSTATUS_DELETED   (1<<4)
#define TCFUNCTION_RECORDSTATUS_DEFAULT   (TCFUNCTION_RECORDSTATUS_NONE | TCFUNCTION_RECORDSTATUS_NEW | TCFUNCTION_RECORDSTATUS_CHANGED)
#define TCFUNCTION_RECORDSTATUS_ALL   (TCFUNCTION_RECORDSTATUS_NONE | TCFUNCTION_RECORDSTATUS_DRAFT | TCFUNCTION_RECORDSTATUS_NEW | TCFUNCTION_RECORDSTATUS_CHANGED | TCFUNCTION_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCFunction : public CPtrArray
{
	// Construction
public:
	CDatabaseTCFunction();
	~CDatabaseTCFunction();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDetails;
		INT  cbTCPacket;
		INT  cbElements;
		INT  cbParameterSets;
		INT  cbDescription[2];
		INT  cbSubSystem[2];
		INT  cbEquipment[2];
		INT  cbVerifGroup[2];
		INT  cbOperationalInfo;
		INT  cbValidityConditions;
		INT  cbAssociatedTelecommands;
		INT  cbComplementaryTelecommands;
		INT  cbDestinationSubSchedule;
		INT  cbMissionPlannerEvent;
		INT  nVerifGroupRef[2];
		INT  nTCPacketRef;
		INT  nAckFlags;
		INT  nAPID[2];
		INT  nTCType;
		INT  nTCID;
		INT  nMapID;
		INT  nStatus;
		ULONGLONG  nAttributes;
		BOOL  bInitializedValues;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDetails;
	CString  m_szTCPacket;
	CString  m_szDescription[2];
	CString  m_szSubSystem[2];
	CString  m_szEquipment[2];
	CString  m_szVerifGroup[2];
	CString  m_szOperationalInfo;
	CString  m_szValidityConditions;
	CString  m_szAssociatedTelecommands;
	CString  m_szComplementaryTelecommands;
	CString  m_szDestinationSubSchedule;
	CString  m_szMissionPlannerEvent;
	CStringArray  m_szParameterSets;
	ULONGLONG  m_nAttributes;
	BOOL  m_bInitializedValues;
	INT  m_nVerifGroupRef[2];
	INT  m_nTCPacketRef;
	INT  m_nAckFlags;
	INT  m_nAPID[2];
	INT  m_nTCType;
	INT  m_nTCID;
	INT  m_nMapID;
	INT  m_nStatus;

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
	VOID SetAPID(INT nAPID, BOOL bRedundant = FALSE);
	INT GetAPID(BOOL bRedundant = FALSE) CONST;
	VOID SetTCType(INT nTCType);
	INT GetTCType() CONST;
	VOID SetTCID(INT nTCID);
	INT GetTCID() CONST;
	VOID SetMapID(INT nMapID);
	INT GetMapID() CONST;
	VOID SetTCPacket(LPCTSTR pszTag);
	CString GetTCPacket() CONST;
	VOID SetTCPacketRef(INT nRef);
	INT GetTCPacketRef() CONST;
	VOID SetPreExeGroup(LPCTSTR pszGroup);
	CString GetPreExeGroup() CONST;
	VOID SetPreExeGroupRef(INT nRef);
	INT GetPreExeGroupRef() CONST;
	VOID SetExeVerGroup(LPCTSTR pszGroup);
	CString GetExeVerGroup() CONST;
	VOID SetExeVerGroupRef(INT nRef);
	INT GetExeVerGroupRef() CONST;
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
	VOID SetAcknowledgementFlags(INT nFlags);
	INT GetAcknowledgementFlags() CONST;
	VOID SetParameterSets(CONST CStringArray &szSets);
	INT GetParameterSets(CStringArray &szSets) CONST;
	VOID SetInitializedValuesFlag(BOOL bFlag);
	BOOL GetInitializedValuesFlag() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCFunctionElement *pElement);

	INT Find(LPCTSTR pszName, INT nOccurrence = 0) CONST;
	INT Find(LPCTSTR pszName, INT nBytePos, INT nBitPos) CONST;
	INT Find(INT nBytePos, INT nBitPos) CONST;

	CDatabaseTCFunctionElement *GetAt(INT nIndex) CONST;
	CDatabaseTCFunctionElement *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCFunction *pFunction);
	BOOL Compare(CONST CDatabaseTCFunction *pFunction) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, INT nBytePos, INT nBitPos) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunctions

class AFX_EXT_CLASS CDatabaseTCFunctions : public CPtrArray
{
	// Construction
public:
	CDatabaseTCFunctions();
	~CDatabaseTCFunctions();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCFunction *pFunction);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCFunction *GetAt(INT nIndex) CONST;
	CDatabaseTCFunction *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCFunctions *pFunctions);
	BOOL Compare(CONST CDatabaseTCFunctions *pFunctions) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunctionBlockElement

// Specify the telecommand function block element related identifiers
#define TCFUNCTIONBLOCKELEMENT_TYPE_FUNCTION   (1<<0)
#define TCFUNCTIONBLOCKELEMENT_TYPE_PACKET   (1<<1)
#define TCFUNCTIONBLOCKELEMENT_TYPE_TCTYPE   (1<<2)

class AFX_EXT_CLASS CDatabaseTCFunctionBlockElement : public CObject
{
	// Construction
public:
	CDatabaseTCFunctionBlockElement();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		UINT  nAttributes;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szName;
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;

	VOID Copy(CONST CDatabaseTCFunctionBlockElement *pFunctionBlockElement);
	BOOL Compare(CONST CDatabaseTCFunctionBlockElement *pFunctionBlockElement) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunctionBlock

// Specify the telecommand function block related identifiers
#define TCFUNCTIONBLOCK_TYPE_LI   (1<<0)
#define TCFUNCTIONBLOCK_TYPE_LTT   (1<<1)
#define TCFUNCTIONBLOCK_TYPE_L2S   (1<<2)
#define TCFUNCTIONBLOCK_TYPE_NI   (1<<3)
#define TCFUNCTIONBLOCK_TYPE_NTT   (1<<4)
#define TCFUNCTIONBLOCK_TYPE_N2S   (1<<5)
#define TCFUNCTIONBLOCK_RECORDSTATUS_NONE   (1<<0)
#define TCFUNCTIONBLOCK_RECORDSTATUS_NEW   (1<<1)
#define TCFUNCTIONBLOCK_RECORDSTATUS_DRAFT   (1<<2)
#define TCFUNCTIONBLOCK_RECORDSTATUS_CHANGED   (1<<3)
#define TCFUNCTIONBLOCK_RECORDSTATUS_DELETED   (1<<4)
#define TCFUNCTIONBLOCK_RECORDSTATUS_DEFAULT   (TCFUNCTIONBLOCK_RECORDSTATUS_NONE | TCFUNCTIONBLOCK_RECORDSTATUS_NEW | TCFUNCTIONBLOCK_RECORDSTATUS_CHANGED)
#define TCFUNCTIONBLOCK_RECORDSTATUS_ALL   (TCFUNCTIONBLOCK_RECORDSTATUS_NONE | TCFUNCTIONBLOCK_RECORDSTATUS_DRAFT | TCFUNCTIONBLOCK_RECORDSTATUS_NEW | TCFUNCTIONBLOCK_RECORDSTATUS_CHANGED | TCFUNCTIONBLOCK_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCFunctionBlock : public CPtrArray
{
	// Construction
public:
	CDatabaseTCFunctionBlock();
	~CDatabaseTCFunctionBlock();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbElements;
		UINT  nAttributes;
		INT  nLength[3];
		INT  nOffset[3];
		INT  nStatus;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szName;
	UINT  m_nAttributes;
	INT  m_nLength[3];
	INT  m_nOffset[3];
	INT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	BOOL SetLocation(UINT nType, INT nOffset, INT nLength);
	BOOL GetLocation(UINT nType, INT &nOffset, INT &nLength) CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCFunctionBlockElement *pFunctionBlockElement);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCFunctionBlockElement *GetAt(INT nIndex) CONST;
	CDatabaseTCFunctionBlockElement *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCFunctionBlock *pFunctionBlock);
	BOOL Compare(CONST CDatabaseTCFunctionBlock *pFunctionBlock) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunctionBlocks

class AFX_EXT_CLASS CDatabaseTCFunctionBlocks : public CPtrArray
{
	// Construction
public:
	CDatabaseTCFunctionBlocks();
	~CDatabaseTCFunctionBlocks();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCFunctionBlock *pFunctionBlock);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCFunctionBlock *GetAt(INT nIndex) CONST;
	CDatabaseTCFunctionBlock *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCFunctionBlocks *pFunctionBlocks);
	BOOL Compare(CONST CDatabaseTCFunctionBlocks *pFunctionBlocks) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunctionRoutingPath

class AFX_EXT_CLASS CDatabaseTCFunctionRoutingPath : public CObject
{
	// Construction
public:
	CDatabaseTCFunctionRoutingPath();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbPath;
		INT  nAPID;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
protected:
	INT  m_nAPID;
	CString  m_szPath;

	// Operations
public:
	VOID SetAPID(INT nAPID);
	INT GetAPID() CONST;
	VOID SetPath(LPCTSTR pszPath);
	CString GetPath() CONST;

	VOID Copy(CONST CDatabaseTCFunctionRoutingPath *pFunctionRoutingPath);
	BOOL Compare(CONST CDatabaseTCFunctionRoutingPath *pFunctionRoutingPath) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCFunctionRoutingPaths

class AFX_EXT_CLASS CDatabaseTCFunctionRoutingPaths : public CPtrArray
{
	// Construction
public:
	CDatabaseTCFunctionRoutingPaths();
	~CDatabaseTCFunctionRoutingPaths();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCFunctionRoutingPath *pFunctionRoutingPath);

	INT Find(INT nAPID) CONST;

	CDatabaseTCFunctionRoutingPath *GetAt(INT nIndex) CONST;
	CDatabaseTCFunctionRoutingPath *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCFunctionRoutingPaths *pFunctionRoutingPaths);
	BOOL Compare(CONST CDatabaseTCFunctionRoutingPaths *pFunctionRoutingPaths) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(INT nAPID, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCParameterValueSet

class AFX_EXT_CLASS CDatabaseTCParameterValueSet : public CPtrArray
{
	// Construction
public:
	CDatabaseTCParameterValueSet();
	~CDatabaseTCParameterValueSet();

	// Attributes
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbElements;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;

	INT Add(CDatabaseTCFunctionElement *pElement);

	INT Find(LPCTSTR pszName, INT nOccurrence = 0) CONST;
	INT Find(LPCTSTR pszName, INT nBytePos, INT nBitPos) CONST;

	CDatabaseTCFunctionElement *GetAt(INT nIndex) CONST;
	CDatabaseTCFunctionElement *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCParameterValueSet *pSet);
	BOOL Compare(CONST CDatabaseTCParameterValueSet *pSet) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, INT nBytePos, INT nBitPos) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCParameterValueSets

class AFX_EXT_CLASS CDatabaseTCParameterValueSets : public CPtrArray
{
	// Construction
public:
	CDatabaseTCParameterValueSets();
	~CDatabaseTCParameterValueSets();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCParameterValueSet *pSet);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCParameterValueSet *GetAt(INT nIndex) CONST;
	CDatabaseTCParameterValueSet *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCParameterValueSets *pSets);
	BOOL Compare(CONST CDatabaseTCParameterValueSets *pSets) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCParameterSet

// Specify the telecommand parameter set related identifiers
#define TCPARAMETERSET_TYPE_FUNCTION   (1<<0)
#define TCPARAMETERSET_TYPE_SEQUENCE   (1<<1)
#define TCPARAMETERSET_RECORDSTATUS_NONE   (1<<0)
#define TCPARAMETERSET_RECORDSTATUS_NEW   (1<<1)
#define TCPARAMETERSET_RECORDSTATUS_DRAFT   (1<<2)
#define TCPARAMETERSET_RECORDSTATUS_CHANGED   (1<<3)
#define TCPARAMETERSET_RECORDSTATUS_DELETED   (1<<4)
#define TCPARAMETERSET_RECORDSTATUS_DEFAULT   (TCPARAMETERSET_RECORDSTATUS_NONE | TCPARAMETERSET_RECORDSTATUS_NEW | TCPARAMETERSET_RECORDSTATUS_CHANGED)
#define TCPARAMETERSET_RECORDSTATUS_ALL   (TCPARAMETERSET_RECORDSTATUS_NONE | TCPARAMETERSET_RECORDSTATUS_DRAFT | TCPARAMETERSET_RECORDSTATUS_NEW | TCPARAMETERSET_RECORDSTATUS_CHANGED | TCPARAMETERSET_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCParameterSet : public CPtrArray
{
	// Construction
public:
	CDatabaseTCParameterSet();
	~CDatabaseTCParameterSet();

	// Attributes
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbValueSet;
		INT  cbElements;
		INT  nStatus;
		UINT  nType;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szValueSet;
	UINT  m_nType;
	INT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetValueSet(LPCTSTR pszSet);
	CString GetValueSet() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCFunctionElement *pElement);

	INT Find(LPCTSTR pszName, INT nOccurrence = 0) CONST;
	INT Find(LPCTSTR pszName, INT nBytePos, INT nBitPos) CONST;

	CDatabaseTCFunctionElement *GetAt(INT nIndex) CONST;
	CDatabaseTCFunctionElement *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCParameterSet *pSet);
	BOOL Compare(CONST CDatabaseTCParameterSet *pSet) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, INT nBytePos, INT nBitPos) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCParameterSets

class AFX_EXT_CLASS CDatabaseTCParameterSets : public CPtrArray
{
	// Construction
public:
	CDatabaseTCParameterSets();
	~CDatabaseTCParameterSets();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCParameterSet *pSet);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCParameterSet *GetAt(INT nIndex) CONST;
	CDatabaseTCParameterSet *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCParameterSets *pSets);
	BOOL Compare(CONST CDatabaseTCParameterSets *pSets) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCPreExeGroupParameter

// Specify the telecommand pre-execution verification group parameter related identifiers
#define TCPREEXEGROUPPARAMETER_INTERPRETATION_RAW   (1<<0)
#define TCPREEXEGROUPPARAMETER_INTERPRETATION_CALIBRATED   (1<<1)

class AFX_EXT_CLASS CDatabaseTCPreExeGroupParameter : public CObject
{
	// Construction
public:
	CDatabaseTCPreExeGroupParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbValue;
		INT  nRef;
		UINT  nAttributes;
		double fValue;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CString  m_szValue;
	double  m_fValue;
	UINT  m_nAttributes;
	INT  m_nRef;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetValue(double fValue);
	double GetValue() CONST;
	VOID SetValueAsText(LPCTSTR pszValue);
	CString GetValueAsText() CONST;

	VOID SetRef(INT nRef);
	INT GetRef() CONST;

	VOID Copy(CONST CDatabaseTCPreExeGroupParameter *pGroupParameter);
	BOOL Compare(CONST CDatabaseTCPreExeGroupParameter *pGroupParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCPreExeGroup

// Specify the telecommand pre-execution verification group related identifiers
#define TCPREEXEGROUP_RECORDSTATUS_NONE   (1<<0)
#define TCPREEXEGROUP_RECORDSTATUS_NEW   (1<<1)
#define TCPREEXEGROUP_RECORDSTATUS_DRAFT   (1<<2)
#define TCPREEXEGROUP_RECORDSTATUS_CHANGED   (1<<3)
#define TCPREEXEGROUP_RECORDSTATUS_DELETED   (1<<4)
#define TCPREEXEGROUP_RECORDSTATUS_DEFAULT   (TCPREEXEGROUP_RECORDSTATUS_NONE | TCPREEXEGROUP_RECORDSTATUS_NEW | TCPREEXEGROUP_RECORDSTATUS_CHANGED)
#define TCPREEXEGROUP_RECORDSTATUS_ALL   (TCPREEXEGROUP_RECORDSTATUS_NONE | TCPREEXEGROUP_RECORDSTATUS_DRAFT | TCPREEXEGROUP_RECORDSTATUS_NEW | TCPREEXEGROUP_RECORDSTATUS_CHANGED | TCPREEXEGROUP_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCPreExeGroup : public CPtrArray
{
	// Construction
public:
	CDatabaseTCPreExeGroup();
	~CDatabaseTCPreExeGroup();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbID;
		INT  cbDescription;
		INT  cbParameters;
		INT  nStatus;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szID;
	CString  m_szDescription;
	INT  m_nStatus;

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCPreExeGroupParameter *pParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTCPreExeGroupParameter *GetAt(INT nIndex) CONST;
	CDatabaseTCPreExeGroupParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCPreExeGroup *pGroup);
	BOOL Compare(CONST CDatabaseTCPreExeGroup *pGroup) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCPreExeGroups

class AFX_EXT_CLASS CDatabaseTCPreExeGroups : public CPtrArray
{
	// Construction
public:
	CDatabaseTCPreExeGroups();
	~CDatabaseTCPreExeGroups();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCPreExeGroup *pGroup);

	INT Find(LPCTSTR pszID) CONST;

	CDatabaseTCPreExeGroup *GetAt(INT nIndex) CONST;
	CDatabaseTCPreExeGroup *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCPreExeGroups *pGroups);
	BOOL Compare(CONST CDatabaseTCPreExeGroups *pGroups) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszID, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCExeVerStageParameter

// Specify the telecommand execution verification stage parameter related identifiers
#define TCEXEVERSTAGEPARAMETER_TYPE_EXCEPTION   (1<<0)
#define TCEXEVERSTAGEPARAMETER_TYPE_REPORT   (1<<1)
#define TCEXEVERSTAGEPARAMETER_TYPE_DUMP   (1<<2)
#define TCEXEVERSTAGEPARAMETER_TYPE_STATUS   (1<<3)
#define TCEXEVERSTAGEPARAMETER_TYPE_PARAMETER   (1<<4)
#define TCEXEVERSTAGEPARAMETER_INTERPRETATION_RAW   (1<<5)
#define TCEXEVERSTAGEPARAMETER_INTERPRETATION_CALIBRATED   (1<<6)
#define TCEXEVERSTAGEPARAMETER_INTERPRETATION_ECHOED   (1<<7)
#define TCEXEVERSTAGEPARAMETER_CHECKS_ENABLED   (1<<8)
#define TCEXEVERSTAGEPARAMETER_CHECKS_DISABLED   (1<<9)

class AFX_EXT_CLASS CDatabaseTCExeVerStageParameter : public CObject
{
	// Construction
public:
	CDatabaseTCExeVerStageParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbStageID;
		INT  cbValue[2];
		UINT  nAttributes;
		double  fValue[2];
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szTag;
	CString  m_szStageID;
	CString  m_szValue[2];
	double  m_fValue[2];
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetStageID(LPCTSTR pszStageID);
	CString GetStageID() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetValue(double fValue);
	double GetValue() CONST;
	VOID SetValueAsText(LPCTSTR pszValue);
	CString GetValueAsText() CONST;
	VOID SetValueTolerance(double fDelta);
	double GetValueTolerance() CONST;
	VOID SetValueToleranceAsText(LPCTSTR pszDelta);
	CString GetValueToleranceAsText() CONST;

	VOID Copy(CONST CDatabaseTCExeVerStageParameter *pStageParameter);
	BOOL Compare(CONST CDatabaseTCExeVerStageParameter *pStageParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCExeVerStage

// Specify the telecommand execution verification stage related identifiers
#define TCEXEVERSTAGE_TYPE_NONE   0
#define TCEXEVERSTAGE_TYPE_ACCEPTANCE   (1<<0)
#define TCEXEVERSTAGE_TYPE_START   (1<<1)
#define TCEXEVERSTAGE_TYPE_PROGRESS   (1<<2)
#define TCEXEVERSTAGE_TYPE_COMPLETION   (1<<3)
#define TCEXEVERSTAGE_SOURCE_REPORTPACKETS   TCEXEVERSTAGEPARAMETER_TYPE_REPORT
#define TCEXEVERSTAGE_SOURCE_MONITORINGPARAMETERS   TCEXEVERSTAGEPARAMETER_TYPE_PARAMETER
// Specify the telecommand execution verification stage related macors
#define MAKETCEXEVEROVERALLSTAGEID(stage)   MAKELONG(-1,stage)
#define MAKETCEXEVERSTAGEID(stage,step)   MAKELONG(step,stage)
#define MAKETCEXEVERSTAGEFROMID(id)   HIWORD(id)
#define MAKETCEXEVERSTAGESTEPFROMID(id)   LOWORD(id)

class AFX_EXT_CLASS CDatabaseTCExeVerStage : public CPtrArray
{
	// Construction
public:
	CDatabaseTCExeVerStage();
	~CDatabaseTCExeVerStage();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbID;
		INT  cbPacket;
		INT  cbParameters;
		UINT  nType;
		UINT  nStep;
		UINT  nAttributes;
		TIMEKEY  tTimeWindow[3];
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szID;
	CString  m_szPacket;
	CTimeSpan  m_tTimeWindow[3];
	UINT  m_nType;
	UINT  m_nStep;
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetStep(UINT nStep);
	UINT GetStep() CONST;
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

	INT Add(CDatabaseTCExeVerStageParameter *pParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTCExeVerStageParameter *GetAt(INT nIndex) CONST;
	CDatabaseTCExeVerStageParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCExeVerStage *pStage);
	BOOL Compare(CONST CDatabaseTCExeVerStage *pStage) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCExeVerStages

class AFX_EXT_CLASS CDatabaseTCExeVerStages : public CPtrArray
{
	// Construction
public:
	CDatabaseTCExeVerStages();
	~CDatabaseTCExeVerStages();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCExeVerStage *pStage);

	INT Find(LPCTSTR pszID) CONST;

	CDatabaseTCExeVerStage *GetAt(INT nIndex) CONST;
	CDatabaseTCExeVerStage *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCExeVerStages *pStages);
	BOOL Compare(CONST CDatabaseTCExeVerStages *pStages) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszID, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCExeVerGroupParameter

// Specify the telecommand execution verification group parameter related identifiers
#define TCEXEVERGROUPPARAMETER_TYPE_EXCEPTION   TCEXEVERSTAGEPARAMETER_TYPE_EXCEPTION
#define TCEXEVERGROUPPARAMETER_TYPE_REPORT   TCEXEVERSTAGEPARAMETER_TYPE_REPORT
#define TCEXEVERGROUPPARAMETER_TYPE_DUMP   TCEXEVERSTAGEPARAMETER_TYPE_DUMP
#define TCEXEVERGROUPPARAMETER_TYPE_STATUS   TCEXEVERSTAGEPARAMETER_TYPE_STATUS
#define TCEXEVERGROUPPARAMETER_TYPE_PARAMETER   TCEXEVERSTAGEPARAMETER_TYPE_PARAMETER
#define TCEXEVERGROUPPARAMETER_INTERPRETATION_RAW   TCEXEVERSTAGEPARAMETER_INTERPRETATION_RAW
#define TCEXEVERGROUPPARAMETER_INTERPRETATION_CALIBRATED   TCEXEVERSTAGEPARAMETER_INTERPRETATION_CALIBRATED
#define TCEXEVERGROUPPARAMETER_INTERPRETATION_ECHOED   TCEXEVERSTAGEPARAMETER_INTERPRETATION_ECHOED
#define TCEXEVERGROUPPARAMETER_CHECKS_ENABLED   TCEXEVERSTAGEPARAMETER_CHECKS_ENABLED
#define TCEXEVERGROUPPARAMETER_CHECKS_DISABLED   TCEXEVERSTAGEPARAMETER_CHECKS_DISABLED
#define TCEXEVERGROUPPARAMETER_STAGE_ACCEPTANCE   TCEXEVERSTAGE_TYPE_ACCEPTANCE
#define TCEXEVERGROUPPARAMETER_STAGE_START   TCEXEVERSTAGE_TYPE_START
#define TCEXEVERGROUPPARAMETER_STAGE_PROGRESS   TCEXEVERSTAGE_TYPE_PROGRESS
#define TCEXEVERGROUPPARAMETER_STAGE_COMPLETION   TCEXEVERSTAGE_TYPE_COMPLETION

class AFX_EXT_CLASS CDatabaseTCExeVerGroupParameter : public CDatabaseTCExeVerStageParameter
{
	// Construction
public:
	CDatabaseTCExeVerGroupParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbData;
		INT  cbPacket[2];
		INT  nRef[2];
		UINT  nStage;
		UINT  nStep;
		TIMEKEY  tTimeWindow[3];
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nStage;
	UINT  m_nStep;
	CTimeSpan  m_tTimeWindow[3];
	CString  m_szPacket[2];
	INT  m_nRef[2];

	// Operations
public:
	VOID SetStage(UINT nType);
	UINT GetStage() CONST;
	VOID SetStep(UINT nStep);
	UINT GetStep() CONST;
	VOID SetTimeWindowOffset(CONST CTimeSpan &tOffset);
	CTimeSpan GetTimeWindowOffset() CONST;
	VOID SetTimeWindowInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetTimeWindowInterval() CONST;
	VOID SetTimeWindowUncertainty(CONST CTimeSpan &tInterval);
	CTimeSpan GetTimeWindowUncertainty() CONST;
	VOID SetTimeWindowClosurePacket(LPCTSTR pszTag);
	CString GetTimeWindowClosurePacket() CONST;
	VOID SetEventIDPacket(LPCTSTR pszTag);
	CString GetEventIDPacket() CONST;
	VOID SetEventIDPacketRef(INT nRef);
	INT GetEventIDPacketRef() CONST;

	VOID SetRef(INT nRef);
	INT GetRef() CONST;

	VOID Copy(CONST CDatabaseTCExeVerGroupParameter *pGroupParameter);
	BOOL Compare(CONST CDatabaseTCExeVerGroupParameter *pGroupParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCExeVerGroup

// Specify the telecommand execution verification group related identifiers
#define TCEXEVERGROUP_TYPE_FUNCTION   (1<<0)
#define TCEXEVERGROUP_TYPE_SEQUENCE   (1<<1)
#define TCEXEVERGROUP_RECORDSTATUS_NONE   (1<<0)
#define TCEXEVERGROUP_RECORDSTATUS_NEW   (1<<1)
#define TCEXEVERGROUP_RECORDSTATUS_DRAFT   (1<<2)
#define TCEXEVERGROUP_RECORDSTATUS_CHANGED   (1<<3)
#define TCEXEVERGROUP_RECORDSTATUS_DELETED   (1<<4)
#define TCEXEVERGROUP_RECORDSTATUS_DEFAULT   (TCEXEVERGROUP_RECORDSTATUS_NONE | TCEXEVERGROUP_RECORDSTATUS_NEW | TCEXEVERGROUP_RECORDSTATUS_CHANGED)
#define TCEXEVERGROUP_RECORDSTATUS_ALL   (TCEXEVERGROUP_RECORDSTATUS_NONE | TCEXEVERGROUP_RECORDSTATUS_DRAFT | TCEXEVERGROUP_RECORDSTATUS_NEW | TCEXEVERGROUP_RECORDSTATUS_CHANGED | TCEXEVERGROUP_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCExeVerGroup : public CPtrArray
{
	// Construction
public:
	CDatabaseTCExeVerGroup();
	~CDatabaseTCExeVerGroup();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbID;
		INT  cbName;
		INT  cbDescription;
		INT  cbParameters;
		INT  nStages;
		INT  nStatus;
		UINT  nAttributes;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szID;
	CString  m_szName;
	CString  m_szDescription;
	CStringArray  m_szStages;
	UINT  m_nAttributes;
	INT  m_nStages;
	INT  m_nStatus;

	// Operations
public:
	VOID SetID(LPCTSTR pszID);
	CString GetID() CONST;
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetStages(CONST CStringArray &szStages);
	VOID SetStages(INT nStages);
	INT GetStages(CStringArray &szStages) CONST;
	INT GetStages() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCExeVerGroupParameter *pParameter);

	INT Find(LPCTSTR pszTag, UINT nStage) CONST;
	INT Find(LPCTSTR pszTag, UINT nStage, UINT nStep) CONST;
	INT Find(LPCTSTR pszTag, UINT nType, UINT nStage, UINT nStep) CONST;

	CDatabaseTCExeVerGroupParameter *GetAt(INT nIndex) CONST;
	CDatabaseTCExeVerGroupParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCExeVerGroup *pGroup);
	BOOL Compare(CONST CDatabaseTCExeVerGroup *pGroup) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, UINT nType, UINT nStage, UINT nStep, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCExeVerGroups

class AFX_EXT_CLASS CDatabaseTCExeVerGroups : public CPtrArray
{
	// Construction
public:
	CDatabaseTCExeVerGroups();
	~CDatabaseTCExeVerGroups();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCExeVerGroup *pGroup);

	INT Find(LPCTSTR pszID) CONST;

	CDatabaseTCExeVerGroup *GetAt(INT nIndex) CONST;
	CDatabaseTCExeVerGroup *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCExeVerGroups *pGroups);
	BOOL Compare(CONST CDatabaseTCExeVerGroups *pGroups) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszID, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCSequenceEntryParameter

class AFX_EXT_CLASS CDatabaseTCSequenceEntryParameter : public CDatabaseTCFunctionElement
{
	// Construction
public:
	CDatabaseTCSequenceEntryParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbElement;
		INT  cbValueSet;
		INT  cbMemoryArea[2];
		INT  nBitOffset;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nBitOffset;
	CString  m_szValueSet;
	CString  m_szMemoryArea[2];

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetValueSet(LPCTSTR pszSet);
	CString GetValueSet() CONST;

	VOID SetMemoryArea(LPCTSTR pszName, LPCTSTR pszVersion);
	BOOL GetMemoryArea(CString &szName, CString &szVersion) CONST;

	BOOL Copy(CONST CDatabaseTCSequenceEntryParameter *pSequenceEntryParameter);
	BOOL Compare(CONST CDatabaseTCSequenceEntryParameter *pSequenceEntryParameter) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCSequenceEntry

// Specify the telecommand sequence entry related identifiers
#define TCSEQUENCEENTRY_TYPE_FUNCTION   (((ULONGLONG) 1)<<0)
#define TCSEQUENCEENTRY_TYPE_SEQUENCE   (((ULONGLONG) 1)<<1)
#define TCSEQUENCEENTRY_TYPE_PROCEDURE   (((ULONGLONG) 1)<<2)
#define TCSEQUENCEENTRY_TYPE_FORMALFUNCTION   (((ULONGLONG) 1)<<3)
#define TCSEQUENCEENTRY_TYPE_FORMALSEQUENCE   (((ULONGLONG) 1)<<4)
#define TCSEQUENCEENTRY_TYPE_TEXTCOMMENT   (((ULONGLONG) 1)<<5)
#define TCSEQUENCEENTRY_FLAG_NOMACRO   (((ULONGLONG) 1)<<6)
#define TCSEQUENCEENTRY_FLAG_BLOCKMACRO   (((ULONGLONG) 1)<<7)
#define TCSEQUENCEENTRY_FLAG_FIRSTBLOCKMEMBER   (((ULONGLONG) 1)<<8)
#define TCSEQUENCEENTRY_FLAG_BLOCKMEMBER   (((ULONGLONG) 1)<<9)
#define TCSEQUENCEENTRY_FLAG_LASTBLOCKMEMBER   (((ULONGLONG) 1)<<10)
#define TCSEQUENCEENTRY_FLAG_NOGROUPMEMBER   (((ULONGLONG) 1)<<11)
#define TCSEQUENCEENTRY_FLAG_FIRSTGROUPMEMBER   (((ULONGLONG) 1)<<12)
#define TCSEQUENCEENTRY_FLAG_GROUPMEMBER   (((ULONGLONG) 1)<<13)
#define TCSEQUENCEENTRY_FLAG_LASTGROUPMEMBER   (((ULONGLONG) 1)<<14)
#define TCSEQUENCEENTRY_RELTYPE_MANUAL   (((ULONGLONG) 1)<<15)
#define TCSEQUENCEENTRY_RELTYPE_AUTOMATIC   (((ULONGLONG) 1)<<16)
#define TCSEQUENCEENTRY_RELTIME_AFTERBEGIN   (((ULONGLONG) 1)<<17)
#define TCSEQUENCEENTRY_RELTIME_AFTERPREVIOUS   (((ULONGLONG) 1)<<18)
#define TCSEQUENCEENTRY_EXETYPE_IMMEDIATE   (((ULONGLONG) 1)<<19)
#define TCSEQUENCEENTRY_EXETYPE_TIMETAG   (((ULONGLONG) 1)<<20)
#define TCSEQUENCEENTRY_EXETYPE_FIRSTSTEP   (((ULONGLONG) 1)<<21)
#define TCSEQUENCEENTRY_EXETYPE_SECONDSTEP   (((ULONGLONG) 1)<<22)
#define TCSEQUENCEENTRY_EXETIME_AFTERBEGIN   (((ULONGLONG) 1)<<23)
#define TCSEQUENCEENTRY_EXETIME_AFTERPREVIOUS   (((ULONGLONG) 1)<<24)
#define TCSEQUENCEENTRY_ILSCOPE_NONE   (((ULONGLONG) 1)<<25)
#define TCSEQUENCEENTRY_ILSCOPE_GLOBAL   (((ULONGLONG) 1)<<26)
#define TCSEQUENCEENTRY_ILSCOPE_LOCAL   (((ULONGLONG) 1)<<27)
#define TCSEQUENCEENTRY_ILSCOPE_LOCALNOWAIT   (((ULONGLONG) 1)<<28)
#define TCSEQUENCEENTRY_ILSCOPE_GLOBALSUBSYSTEM   (((ULONGLONG) 1)<<29)
#define TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEM   (((ULONGLONG) 1)<<30)
#define TCSEQUENCEENTRY_ILSCOPE_LOCALSUBSYSTEMNOWAIT   (((ULONGLONG) 1)<<31)
#define TCSEQUENCEENTRY_ILSTAGE_RECEPTION   (((ULONGLONG) 1)<<32)
#define TCSEQUENCEENTRY_ILSTAGE_UPLINK   (((ULONGLONG) 1)<<33)
#define TCSEQUENCEENTRY_ILSTAGE_ONBOARD   (((ULONGLONG) 1)<<34)
#define TCSEQUENCEENTRY_ILSTAGE_ACCEPTANCE   (((ULONGLONG) 1)<<35)
#define TCSEQUENCEENTRY_ILSTAGE_COMPLETION   (((ULONGLONG) 1)<<36)
#define TCSEQUENCEENTRY_PTVCHECKS_ENABLED   (((ULONGLONG) 1)<<37)
#define TCSEQUENCEENTRY_PTVCHECKS_DISABLED   (((ULONGLONG) 1)<<38)
#define TCSEQUENCEENTRY_PEVCHECKS_ENABLED   (((ULONGLONG) 1)<<39)
#define TCSEQUENCEENTRY_PEVCHECKS_DISABLED   (((ULONGLONG) 1)<<40)
#define TCSEQUENCEENTRY_CEVCHECKS_ENABLED   (((ULONGLONG) 1)<<41)
#define TCSEQUENCEENTRY_CEVCHECKS_DISABLED   (((ULONGLONG) 1)<<42)
#define TCSEQUENCEENTRY_ACKFLAG_AUTHORIZATION   (((ULONGLONG) 1)<<43)
#define TCSEQUENCEENTRY_ACKFLAG_ACCEPTANCE   (((ULONGLONG) 1)<<44)
#define TCSEQUENCEENTRY_ACKFLAG_START   (((ULONGLONG) 1)<<45)
#define TCSEQUENCEENTRY_ACKFLAG_PROGRESS   (((ULONGLONG) 1)<<46)
#define TCSEQUENCEENTRY_ACKFLAG_COMPLETION   (((ULONGLONG) 1)<<47)

class AFX_EXT_CLASS CDatabaseTCSequenceEntry : public CPtrArray
{
	// Construction
public:
	CDatabaseTCSequenceEntry();
	~CDatabaseTCSequenceEntry();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cb1Step;
		INT  cbDescription;
		INT  cbParameters;
		INT  nBlockMember;
		TIMETAG  tExeTime;
		ULONGLONG  nAttributes;
		DWORD  dwRelDelta;
		DWORD  dwExeDelta;
		BOOL  bExeEarlier;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_sz1Step;
	CTimeTag  m_tExeTime;
	ULONGLONG  m_nAttributes;
	DWORD  m_dwRelDelta;
	DWORD  m_dwExeDelta;
	BOOL  m_bExeEarlier;
	INT  m_nBlockMember;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
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

	INT Add(CDatabaseTCSequenceEntryParameter *pParameter);

	INT Find(LPCTSTR pszTag, INT nOccurrence = 0) CONST;
	INT Find(LPCTSTR pszTag, INT nBytePos, INT nBitPos) CONST;

	CDatabaseTCSequenceEntryParameter *GetAt(INT nIndex) CONST;
	CDatabaseTCSequenceEntryParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCSequenceEntry *pSequenceEntry);
	BOOL Compare(CONST CDatabaseTCSequenceEntry *pSequenceEntry) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszTag, INT nBytePos, INT nBitPos) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCSequence

// Specify the telecommand sequence related identifiers
#define TCSEQUENCE_EXETYPE_STANDALONE   (((ULONGLONG) 1)<<0)
#define TCSEQUENCE_EXETYPE_NOTSTANDALONE   (((ULONGLONG) 1)<<1)
#define TCSEQUENCE_TIMETAGGED_NO   (((ULONGLONG) 1)<<2)
#define TCSEQUENCE_TIMETAGGED_YES   (((ULONGLONG) 1)<<3)
#define TCSEQUENCE_TIMETAGGED_OPTIONAL   (((ULONGLONG) 1)<<4)
#define TCSEQUENCE_HAZFLAG_HAZARDOUS   (((ULONGLONG) 1)<<5)
#define TCSEQUENCE_HAZFLAG_NONCRITICAL   (((ULONGLONG) 1)<<6)
#define TCSEQUENCE_PLANFLAG_ALL   (((ULONGLONG) 1)<<7)
#define TCSEQUENCE_PLANFLAG_SOC   (((ULONGLONG) 1)<<8)
#define TCSEQUENCE_PLANFLAG_FLIGHTDYNAMICS   (((ULONGLONG) 1)<<9)
#define TCSEQUENCE_PLANFLAG_PROHIBITED   (((ULONGLONG) 1)<<10)
#define TCSEQUENCE_RECORDSTATUS_NONE   (1<<0)
#define TCSEQUENCE_RECORDSTATUS_NEW   (1<<1)
#define TCSEQUENCE_RECORDSTATUS_DRAFT   (1<<2)
#define TCSEQUENCE_RECORDSTATUS_CHANGED   (1<<3)
#define TCSEQUENCE_RECORDSTATUS_DELETED   (1<<4)
#define TCSEQUENCE_RECORDSTATUS_DEFAULT   (TCSEQUENCE_RECORDSTATUS_NONE | TCSEQUENCE_RECORDSTATUS_NEW | TCSEQUENCE_RECORDSTATUS_CHANGED)
#define TCSEQUENCE_RECORDSTATUS_ALL   (TCSEQUENCE_RECORDSTATUS_NONE | TCSEQUENCE_RECORDSTATUS_DRAFT | TCSEQUENCE_RECORDSTATUS_NEW | TCSEQUENCE_RECORDSTATUS_CHANGED | TCSEQUENCE_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseTCSequence : public CPtrArray
{
	// Construction
public:
	CDatabaseTCSequence();
	~CDatabaseTCSequence();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbUser;
		INT  cbDetails;
		INT  cbDescription;
		INT  cbDocumentName;
		INT  cbDocumentIssue;
		INT  cbDestinationSubSystem;
		INT  cbDestinationSubSchedule;
		INT  cbMissionPlannerEvent;
		INT  cbParameterSets;
		INT  cbParameters;
		INT  cbEntries;
		INT  nStatus;
		ULONGLONG  nAttributes;
		TIMEKEY  tDate[2];
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szUser;
	CString  m_szDetails;
	CString  m_szDescription;
	CString  m_szXmlCode;
	CString  m_szFileName;
	CString  m_szDocumentName;
	CString  m_szDocumentIssue;
	CString  m_szDestinationSubSystem;
	CString  m_szDestinationSubSchedule;
	CString  m_szMissionPlannerEvent;
	CStringArray  m_szParameterSets;
	CDatabaseTCParameters  m_pParameters;
	ULONGLONG  m_nAttributes;
	CTimeKey  m_tDate[2];
	INT  m_nStatus;

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
	VOID SetUser(LPCTSTR pszUser);
	CString GetUser() CONST;
	VOID SetDate(CONST CTimeKey &tDate);
	CTimeKey GetDate() CONST;
	VOID SetDestinationSubSystem(LPCTSTR pszSubSystem);
	CString GetDestinationSubSystem() CONST;
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
	VOID SetParameterSets(CONST CStringArray &szSets);
	INT GetParameterSets(CStringArray &szSets) CONST;
	BOOL SetParameters(CONST CDatabaseTCParameters &pParameters);
	INT GetParameters(CDatabaseTCParameters &pParameters) CONST;
	VOID SetXmlCode(LPCTSTR pszCode);
	CString GetXmlCode() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseTCSequenceEntry *pEntry);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCSequenceEntry *GetAt(INT nIndex) CONST;
	CDatabaseTCSequenceEntry *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCSequence *pSequence);
	BOOL Compare(CONST CDatabaseTCSequence *pSequence) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCSequences

class AFX_EXT_CLASS CDatabaseTCSequences : public CPtrArray
{
	// Construction
public:
	CDatabaseTCSequences();
	~CDatabaseTCSequences();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCSequence *pSequence);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCSequence *GetAt(INT nIndex) CONST;
	CDatabaseTCSequence *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCSequences *pSequences);
	BOOL Compare(CONST CDatabaseTCSequences *pSequences) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureIdentifier

class AFX_EXT_CLASS CDatabaseTCProcedureIdentifier : public CDatabaseTCParameter
{
	// Construction
public:
	CDatabaseTCProcedureIdentifier();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbInfo;
		INT  cbValue[2];
		ULONGLONG  nValue[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szValue[2];
	ULONGLONG  m_nValue[2];

	// Operations
public:
	VOID SetMinValue(ULONGLONG nValue);
	ULONGLONG GetMinValue() CONST;
	VOID SetMinValueAsText(LPCTSTR pszValue);
	CString GetMinValueAsText() CONST;
	VOID SetMaxValue(ULONGLONG nValue);
	ULONGLONG GetMaxValue() CONST;
	VOID SetMaxValueAsText(LPCTSTR pszValue);
	CString GetMaxValueAsText() CONST;

	BOOL Copy(CONST CDatabaseTCProcedureIdentifier *pIdentifier);
	BOOL Compare(CONST CDatabaseTCProcedureIdentifier *pIdentifier) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureIdentifiers

class AFX_EXT_CLASS CDatabaseTCProcedureIdentifiers : public CPtrArray
{
	// Construction
public:
	CDatabaseTCProcedureIdentifiers();
	~CDatabaseTCProcedureIdentifiers();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCProcedureIdentifier *pIdentifier);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCProcedureIdentifier *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedureIdentifier *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCProcedureIdentifiers *pIdentifiers);
	BOOL Compare(CONST CDatabaseTCProcedureIdentifiers *pIdentifiers) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureArgument

class AFX_EXT_CLASS CDatabaseTCProcedureArgument : public CDatabaseTCProcedureIdentifier
{
	// Construction
public:
	CDatabaseTCProcedureArgument();

	// Attributes
public:

	// Operations
public:
	BOOL Copy(CONST CDatabaseTCProcedureArgument *pDatabaseTCProcedureArgument);
	BOOL Compare(CONST CDatabaseTCProcedureArgument *pDatabaseTCProcedureArgument) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureArguments

class AFX_EXT_CLASS CDatabaseTCProcedureArguments : public CDatabaseTCProcedureIdentifiers
{
	// Construction
public:
	CDatabaseTCProcedureArguments();
	~CDatabaseTCProcedureArguments();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCProcedureArgument *pDatabaseTCProcedureArgument);

	CDatabaseTCProcedureArgument *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedureArgument *operator[](INT nIndex) CONST;

	BOOL Copy(CONST CDatabaseTCProcedureArguments *pDatabaseTCProcedureArguments);
	BOOL Compare(CONST CDatabaseTCProcedureArguments *pDatabaseTCProcedureArguments) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureVariable

class AFX_EXT_CLASS CDatabaseTCProcedureVariable : public CDatabaseTCProcedureIdentifier
{
	// Construction
public:
	CDatabaseTCProcedureVariable();

	// Attributes
public:

	// Operations
public:
	BOOL Copy(CONST CDatabaseTCProcedureVariable *pDatabaseTCProcedureVariable);
	BOOL Compare(CONST CDatabaseTCProcedureVariable *pDatabaseTCProcedureVariable) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureVariables

class AFX_EXT_CLASS CDatabaseTCProcedureVariables : public CDatabaseTCProcedureIdentifiers
{
	// Construction
public:
	CDatabaseTCProcedureVariables();
	~CDatabaseTCProcedureVariables();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCProcedureVariable *pDatabaseTCProcedureVariable);

	CDatabaseTCProcedureVariable *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedureVariable *operator[](INT nIndex) CONST;

	BOOL Copy(CONST CDatabaseTCProcedureVariables *pDatabaseTCProcedureVariables);
	BOOL Compare(CONST CDatabaseTCProcedureVariables *pDatabaseTCProcedureVariables) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureThreadBreakpoint

// Specify the telecommand procedure thread breakpoint options
#define TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKALWAYS   (1<<0)
#define TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDTRIGGER   (1<<1)
#define TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDBODY   (1<<2)
#define TCPROCEDURETHREADBREAKPOINT_OPTION_BREAKATFAILEDCONFIRMATION   (1<<3)
#define TCPROCEDURETHREADBREAKPOINT_OPTION_DISABLED   (1<<4)

class AFX_EXT_CLASS CDatabaseTCProcedureThreadBreakpoint : public CObject
{
	// Construction
public:
	CDatabaseTCProcedureThreadBreakpoint();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbLocation;
		UINT  nLine;
		UINT  nOptions;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szLocation;
	UINT  m_nLine;
	UINT  m_nOptions;

	// Operations
public:
	VOID SetLocation(LPCTSTR pszLocation);
	CString GetLocation() CONST;
	VOID SetLine(UINT nLine);
	UINT GetLine() CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;

	VOID Copy(CONST CDatabaseTCProcedureThreadBreakpoint *pDatabaseTCProcedureThreadBreakpoint);
	BOOL Compare(CONST CDatabaseTCProcedureThreadBreakpoint *pDatabaseTCProcedureThreadBreakpoint) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureThreadBreakpoints

class AFX_EXT_CLASS CDatabaseTCProcedureThreadBreakpoints : public CPtrArray
{
	// Construction
public:
	CDatabaseTCProcedureThreadBreakpoints();
	~CDatabaseTCProcedureThreadBreakpoints();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCProcedureThreadBreakpoint *pDatabaseTCProcedureThreadBreakpoint);

	INT Find(LPCTSTR pszLocation) CONST;
	INT Find(UINT nLine) CONST;

	CDatabaseTCProcedureThreadBreakpoint *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedureThreadBreakpoint *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCProcedureThreadBreakpoints *pDatabaseTCProcedureThreadBreakpoints);
	BOOL Compare(CONST CDatabaseTCProcedureThreadBreakpoints *pDatabaseTCProcedureThreadBreakpoints) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszLocation, BOOL bInsert = FALSE) CONST;
	INT FindIndex(UINT nLine, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureThreadTestProfile

// Specify the telecommand procedure thread test profile options
#define TCPROCEDURETHREADTESTPROFILE_OPTION_EXECUTEIMMEDIATELY   (1<<0)
#define TCPROCEDURETHREADTESTPROFILE_OPTION_EXECUTEDELAYEDAFTERSTART   (1<<1)
#define TCPROCEDURETHREADTESTPROFILE_OPTION_EXECUTEDELAYEDAFTERSTEP   (1<<2)
#define TCPROCEDURETHREADTESTPROFILE_OPTION_DISABLED   (1<<3)

class AFX_EXT_CLASS CDatabaseTCProcedureThreadTestProfile : public CPtrArray
{
	// Construction
public:
	CDatabaseTCProcedureThreadTestProfile();
	~CDatabaseTCProcedureThreadTestProfile();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbLocation;
		INT  cbParameters;
		UINT  nOptions;
		TIMEKEY  tDelay;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szLocation;
	CTimeSpan  m_tDelay;
	UINT  m_nOptions;
private:
	CTimeKey  m_tRunningTime;
	CTimeSpan  m_tRunningTimeInterval;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetLocation(LPCTSTR pszLocation);
	CString GetLocation() CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;
	VOID SetDelay(CONST CTimeSpan &tDelay);
	CTimeSpan GetDelay() CONST;

	VOID SetRunningTime(CONST CTimeKey &tTime);
	CTimeKey GetRunningTime() CONST;
	VOID SetRunningTimeInterval(CONST CTimeSpan &tTimeInterval);
	CTimeSpan GetRunningTimeInterval() CONST;

	INT Add(CDatabaseTMParameter *pParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CDatabaseTMParameter *GetAt(INT nIndex) CONST;
	CDatabaseTMParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCProcedureThreadTestProfile *pDatabaseTCProcedureThreadTestProfile);
	BOOL Compare(CONST CDatabaseTCProcedureThreadTestProfile *pDatabaseTCProcedureThreadTestProfile) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureThreadTestProfiles

class AFX_EXT_CLASS CDatabaseTCProcedureThreadTestProfiles : public CPtrArray
{
	// Construction
public:
	CDatabaseTCProcedureThreadTestProfiles();
	~CDatabaseTCProcedureThreadTestProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCProcedureThreadTestProfile *pDatabaseTCProcedureThreadTestProfile);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCProcedureThreadTestProfile *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedureThreadTestProfile *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCProcedureThreadTestProfiles *pDatabaseTCProcedureThreadTestProfiles);
	BOOL Compare(CONST CDatabaseTCProcedureThreadTestProfiles *pDatabaseTCProcedureThreadTestProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureThreadContents

class AFX_EXT_CLASS CDatabaseTCProcedureThreadContents : public CPtrArray
{
	friend class CDatabaseTCProcedureThreadStep;

	// Construction
public:
	CDatabaseTCProcedureThreadContents();
	~CDatabaseTCProcedureThreadContents();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCProcedureThreadStep *pStep);

	INT Find(LPCTSTR pszName) CONST;

	INT Enum(CPtrArray &pSteps, BOOL bAll = FALSE) CONST;
	INT Enum(CONST CDatabaseTCProcedureThreadContents &pContents, CPtrArray &pSteps, BOOL bAll = FALSE) CONST;

	CDatabaseTCProcedureThreadStep *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedureThreadStep *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCProcedureThreadContents *pSteps);
	BOOL Compare(CONST CDatabaseTCProcedureThreadContents *pSteps) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureThreadStep

// Specify the telecommand procedure thread step types
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_START   1
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_FIRST   2
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_BRANCH   2
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_SWITCH   3
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_FORLOOP   4
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_WHILELOOP   5
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_DOLOOP   6
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_BLOCK   7
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_GOTO   8
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_LABEL   9
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_LAST   9
#define TCPROCEDURETHREADSTEP_FLOWCONTROL_END   10
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_FIRST   11
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETARGUMENTS   11
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETVARIABLES   12
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETPARAMETERS   13
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_SETSYNCOBJECT   14
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_INJECTALERT   15
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_CALLPROCEDURE   16
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_STARTPROCEDURE   17
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_CONTROLPROCEDURE   18
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_CONTROLTHREAD   19
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_WAITTIMEINTERVAL   20
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_WAITSYNCOBJECT   21
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCFUNCTION   22
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_SENDTCSEQUENCE   23
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_LOGMESSAGE   24
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_USERINTERACTION   25
#define TCPROCEDURETHREADSTEP_ACTIONOBJECT_LAST   25
// Specify the telecommand procedure step states
#define TCPROCEDURETHREADSTEP_STATE_NONE   0
#define TCPROCEDURETHREADSTEP_STATE_TRIGGER_RUNNING   (1<<0)
#define TCPROCEDURETHREADSTEP_STATE_TRIGGER_EXECUTED   (1<<1)
#define TCPROCEDURETHREADSTEP_STATE_TRIGGER_FAILED   (1<<2)
#define TCPROCEDURETHREADSTEP_STATE_TRIGGER_FORCED   (1<<3)
#define TCPROCEDURETHREADSTEP_STATE_BODY_RUNNING   (1<<4)
#define TCPROCEDURETHREADSTEP_STATE_BODY_EXECUTED   (1<<5)
#define TCPROCEDURETHREADSTEP_STATE_BODY_FAILED   (1<<6)
#define TCPROCEDURETHREADSTEP_STATE_BODY_FORCED   (1<<7)
#define TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_RUNNING   (1<<8)
#define TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_EXECUTED   (1<<9)
#define TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FAILED   (1<<10)
#define TCPROCEDURETHREADSTEP_STATE_CONFIRMATION_FORCED   (1<<11)
// Specify the telecommand procedure step trigger types
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_NONE   (1<<0)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_ATTIME   (1<<1)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_NOTAFTERTIME   (1<<2)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEOFFSET   (1<<3)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_TIMEDELAY   (1<<4)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_SYNCOBJECT   (1<<5)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_EXPRESSION   (1<<6)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_OPERATOR   (1<<7)
#define TCPROCEDURETHREADSTEP_TRIGGERTYPE_AUTHORIZATION   (1<<8)
// Specify the telecommand procedure step confirmation types
#define TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_NONE   (1<<0)
#define TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_COMMAND   (1<<1)
#define TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_EXPRESSION   (1<<2)
#define TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_OPERATOR   (1<<3)
#define TCPROCEDURETHREADSTEP_CONFIRMATIONTYPE_AUTHORIZATION   (1<<4)
// Specify the telecommand procedure step failure options
#define TCPROCEDURETHREADSTEP_FAILUREOPTION_NONE   0
#define TCPROCEDURETHREADSTEP_FAILUREOPTION_TRIGGERSUCCESS   (1<<0)
#define TCPROCEDURETHREADSTEP_FAILUREOPTION_TRIGGERFAILURE   (1<<1)
#define TCPROCEDURETHREADSTEP_FAILUREOPTION_BODYSUCCESS   (1<<2)
#define TCPROCEDURETHREADSTEP_FAILUREOPTION_BODYFAILURE   (1<<3)
#define TCPROCEDURETHREADSTEP_FAILUREOPTION_CONFIRMATIONSUCCESS   (1<<4)
#define TCPROCEDURETHREADSTEP_FAILUREOPTION_CONFIRMATIONFAILURE   (1<<5)

class AFX_EXT_CLASS CDatabaseTCProcedureThreadStep : public CObject
{
	friend class CDatabaseTCProcedureThreadContents;

	// Construction
public:
	CDatabaseTCProcedureThreadStep();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbLabel;
		INT  cbComments;
		INT  cbPreexecutionExpression;
		INT  cbConfirmationExpression;
		INT  cbConfirmationMessage;
		INT  cbTriggerExpression;
		INT  cbTriggerMessage;
		INT  cbTriggerObject;
		INT  cbFailureLabels;
		INT  cbSubSteps;
		INT  cbInfo;
		UINT  nType;
		UINT  nSubThreadID;
		UINT  nTriggerType;
		UINT  nConfirmationType;
		UINT  nFailureOptions;
		RECT  rPosition;
		BOOL  bActivated;
		BOOL  bExpanded;
		TIMETAG  tTriggerTime;
		TIMEKEY  tTriggerTimeOffset;
		TIMEKEY  tTriggerTimeDelay;
		TIMEKEY  tTriggerTimeout;
		TIMEKEY  tConfirmationTimeout;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szLabel;
	CString  m_szComments;
	CString  m_szPreexecutionExpression;
	CString  m_szConfirmationExpression;
	CString  m_szConfirmationMessage;
	CString  m_szTriggerExpression;
	CString  m_szTriggerMessage;
	CString  m_szTriggerObject;
	CTimeTag  m_tTriggerTime;
	CTimeSpan  m_tTriggerTimeOffset;
	CTimeSpan  m_tTriggerTimeDelay;
	CTimeSpan  m_tTriggerTimeout;
	CTimeSpan  m_tConfirmationTimeout;
	CStringArray  m_szFailureLabels;
	CByteArray  m_nInfo;
	CRect  m_rPosition;
	UINT  m_nType;
	UINT  m_nSubThreadID;
	UINT  m_nTriggerType;
	UINT  m_nConfirmationType;
	UINT  m_nFailureOptions;
	BOOL  m_bActivated;
	BOOL  m_bExpanded;
private:
	CDatabaseTCProcedureThreadContents  m_pSubSteps;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetLabel(LPCTSTR pszLabel);
	CString GetLabel() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetPosition(CONST RECT &rect);
	CRect GetPosition() CONST;
	VOID SetSubThreadID(UINT nID);
	UINT GetSubThreadID() CONST;
	VOID SetProperties(CONST CByteArray &nInfo);
	BOOL GetProperties(CByteArray &nInfo) CONST;
	VOID SetTriggerType(UINT nType);
	UINT GetTriggerType() CONST;
	VOID SetTriggerTime(CONST CTimeTag &tTime);
	CTimeTag GetTriggerTime() CONST;
	VOID SetTriggerTimeOffset(CONST CTimeSpan &tDelay);
	CTimeSpan GetTriggerTimeOffset() CONST;
	VOID SetTriggerTimeDelay(CONST CTimeSpan &tDelay);
	CTimeSpan GetTriggerTimeDelay() CONST;
	VOID SetTriggerSynchronizationObject(LPCTSTR pszObject);
	CString GetTriggerSynchronizationObject() CONST;
	VOID SetTriggerTimeout(CONST CTimeSpan &tTimeout);
	CTimeSpan GetTriggerTimeout() CONST;
	VOID SetTriggerMessage(LPCTSTR pszMessage);
	CString GetTriggerMessage() CONST;
	VOID SetTriggerExpression(LPCTSTR pszExpression);
	CString GetTriggerExpression() CONST;
	VOID SetPreexecutionExpression(LPCTSTR pszExpression);
	CString GetPreexecutionExpression() CONST;
	VOID SetConfirmationType(UINT nType);
	UINT GetConfirmationType() CONST;
	VOID SetConfirmationTimeout(CONST CTimeSpan &tTimeout);
	CTimeSpan GetConfirmationTimeout() CONST;
	VOID SetConfirmationMessage(LPCTSTR pszMessage);
	CString GetConfirmationMessage() CONST;
	VOID SetConfirmationExpression(LPCTSTR pszExpression);
	CString GetConfirmationExpression() CONST;
	VOID SetFailureOptions(UINT nOptions);
	UINT GetFailureOptions() CONST;
	VOID SetFailureLabels(CONST CStringArray &szLabels);
	INT GetFailureLabels(CStringArray &szLabels) CONST;

	BOOL SetSubSteps(CONST CDatabaseTCProcedureThreadContents &pSubSteps);
	INT GetSubSteps(CDatabaseTCProcedureThreadContents &pSubSteps) CONST;

	VOID Activate(BOOL bActivate);
	BOOL IsActivated() CONST;
	VOID Expand(BOOL bExpand);
	BOOL IsExpanded() CONST;

	BOOL Copy(CONST CDatabaseTCProcedureThreadStep *pStep);
	BOOL Compare(CONST CDatabaseTCProcedureThreadStep *pStep) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedureThread

// Specify the telecommand procedure thread related identifiers
#define TCPROCEDURETHREAD_AUTHORITY_AUTOENABLED   (1<<0)
#define TCPROCEDURETHREAD_AUTHORITY_ENABLED   (1<<1)
#define TCPROCEDURETHREAD_AUTHORITY_DISABLED   (1<<2)
#define TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING   (1<<3)
#define TCPROCEDURETHREAD_RUNNINGSTATE_RUNNING   (1<<4)
#define TCPROCEDURETHREAD_RUNNINGSTATE_STOPPED   (1<<5)
#define TCPROCEDURETHREAD_ACTIONSTATE_SUSPEND   (1<<6)
#define TCPROCEDURETHREAD_ACTIONSTATE_RESUME   (1<<7)
#define TCPROCEDURETHREAD_ACTIONSTATE_ENABLE   (1<<8)
#define TCPROCEDURETHREAD_ACTIONSTATE_DISABLE   (1<<9)
#define TCPROCEDURETHREAD_ACTIONSTATE_ABORT   (1<<10)

class AFX_EXT_CLASS CDatabaseTCProcedureThread : public CDatabaseTCProcedureThreadContents
{
	// Construction
public:
	CDatabaseTCProcedureThread();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbComments;
		INT  cbCode;
		INT  cbSteps;
		INT  cbBreakpoints;
		INT  cbProfiles;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szComments;
	CString  m_szCode;
	UINT  m_nAttributes;
	UINT  m_nState;
private:
	CDatabaseTCProcedureThreadBreakpoints  m_pDatabaseTCProcedureThreadBreakpoints;
	CDatabaseTCProcedureThreadTestProfiles  m_pDatabaseTCProcedureThreadTestProfiles;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetActivationExpression(LPCTSTR pszCode);
	CString GetActivationExpression() CONST;
	VOID SetState(UINT nState);
	UINT GetState() CONST;

	BOOL SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;
	BOOL SetProfiles(CONST CDatabaseTCProcedureThreadTestProfiles &pDatabaseTCProcedureThreadTestProfiles);
	INT GetProfiles(CDatabaseTCProcedureThreadTestProfiles &pDatabaseTCProcedureThreadTestProfiles) CONST;

	BOOL Copy(CONST CDatabaseTCProcedureThread *pDatabaseTCProcedureThread);
	BOOL Compare(CONST CDatabaseTCProcedureThread *pDatabaseTCProcedureThread) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedure

// Specify the telecommand procedure related identifiers
#define TCPROCEDURE_EXECUTIONMODE_AUTOMATIC   (1<<0)
#define TCPROCEDURE_EXECUTIONMODE_SINGLESTEP   (1<<1)
#define TCPROCEDURE_EXECUTIONMODE_EXTERNALACTIONS   (1<<2)
#define TCPROCEDURE_EXECUTIONMODE_COMMANDS   (1<<3)
#define TCPROCEDURE_RUNNINGSTATE_NOTRUNNING   (1<<4)
#define TCPROCEDURE_RUNNINGSTATE_RUNNING   (1<<5)
#define TCPROCEDURE_RUNNINGSTATE_STOPPED   (1<<6)
#define TCPROCEDURE_ACTIONSTATE_SUSPEND   (1<<7)
#define TCPROCEDURE_ACTIONSTATE_RESUME   (1<<8)
#define TCPROCEDURE_ACTIONSTATE_ABORT   (1<<9)
#define TCPROCEDURE_SOURCECODE_NOGRAPHICALINTERFACE   (1<<10)
#define TCPROCEDURE_SOURCECODE_CUSTOM   (1<<11)

class AFX_EXT_CLASS CDatabaseTCProcedure : public CPtrArray
{
	// Construction
public:
	CDatabaseTCProcedure();
	~CDatabaseTCProcedure();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbAuthor;
		INT  cbDescription;
		INT  cbComments;
		INT  cbFileName;
		INT  cbSubSystem;
		INT  cbVerificationStatus;
		INT  cbSourceCode[2];
		INT  cbThreads;
		INT  cbArguments;
		INT  cbVariables;
		UINT  nAttributes;
		TIMEKEY  tDate[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szAuthor;
	CString  m_szDescription;
	CString  m_szComments;
	CString  m_szFileName;
	CString  m_szSubSystem;
	CString  m_szVerificationStatus;
	CString  m_szSourceCode[2];
	CByteArray  m_nSourceCode;
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments;
	CDatabaseTCProcedureVariables  m_pDatabaseTCProcedureVariables;
	CTimeKey  m_tDate[2];
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetAuthor(LPCTSTR pszAuthor);
	CString GetAuthor() CONST;
	VOID SetSubSystem(LPCTSTR pszSubSystem);
	CString GetSubSystem() CONST;
	VOID SetVerificationStatus(LPCTSTR pszStatus);
	CString GetVerificationStatus() CONST;
	VOID SetCreationDate(CONST CTimeKey &tDate);
	CTimeKey GetCreationDate() CONST;
	VOID SetModificationDate(CONST CTimeKey &tDate);
	CTimeKey GetModificationDate() CONST;
	BOOL SetArguments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments);
	INT GetArguments(CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments) CONST;
	BOOL SetVariables(CONST CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables);
	INT GetVariables(CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables) CONST;
	VOID SetSourceCode(LPCTSTR pszCode);
	VOID SetSourceCode(CONST CByteArray &nCode);
	CString GetSourceCode() CONST;
	INT GetSourceCode(CByteArray &nCode) CONST;
	VOID SetPrecompiledCode(LPCTSTR pszCode);
	CString GetPrecompiledCode() CONST;
	VOID SetExecutableFileName(LPCTSTR pszFileName);
	CString GetExecutableFileName() CONST;

	INT Add(CDatabaseTCProcedureThread *pDatabaseTCProcedureThread);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCProcedureThread *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedureThread *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCProcedure *pProcedure);
	BOOL Compare(CONST CDatabaseTCProcedure *pProcedure) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTCProcedures

class AFX_EXT_CLASS CDatabaseTCProcedures : public CPtrArray
{
	// Construction
public:
	CDatabaseTCProcedures();
	~CDatabaseTCProcedures();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseTCProcedure *pProcedure);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseTCProcedure *GetAt(INT nIndex) CONST;
	CDatabaseTCProcedure *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseTCProcedures *pProcedures);
	BOOL Compare(CONST CDatabaseTCProcedures *pProcedures) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryImageBlock

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryImageBlock : public CObject
{
	// Construction
public:
	CDatabaseOBProcessorMemoryImageBlock();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbVersion;
		INT  cbData[3];
		UINT  nAddress[2];
		BOOL  bAddress;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szData;
	CString  m_szVersion;
	CByteArray  m_nData[2];
	UINT  m_nAddress[2];
	BOOL  m_bAddress;

	// Operations
public:
	VOID SetVersion(LPCTSTR pszVersion);
	CString GetVersion() CONST;
	VOID SetAddress(UINT nPage, UINT nAddress);
	BOOL GetAddress(UINT &nPage, UINT &nAddress) CONST;
	VOID SetData(LPCTSTR pszData);
	VOID SetData(CONST CByteArray &nData);
	CString GetData() CONST;
	INT GetData(CByteArray &nData) CONST;
	VOID SetMask(CONST CByteArray &nMask);
	INT GetMask(CByteArray &nMask) CONST;

	VOID Copy(CONST CDatabaseOBProcessorMemoryImageBlock *pMemoryImageBlock);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryImageBlock *pMemoryImageBlock) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryImage

// Specify the on-board processor memory image related identifiers
#define OBPROCESSORMEMORYIMAGE_TYPE_DUMP   OBPROCESSORMEMORYAREA_TYPE_IMAGE
#define OBPROCESSORMEMORYIMAGE_FLAG_NONPATCHABLE   OBPROCESSORMEMORYAREA_FLAG_NONPATCHABLE
#define OBPROCESSORMEMORYIMAGE_FLAG_PATCHABLE   OBPROCESSORMEMORYAREA_FLAG_PATCHABLE
#define OBPROCESSORMEMORYIMAGE_FLAG_NONDUMPABLE   OBPROCESSORMEMORYAREA_FLAG_NONDUMPABLE
#define OBPROCESSORMEMORYIMAGE_FLAG_DUMPABLE   OBPROCESSORMEMORYAREA_FLAG_DUMPABLE
#define OBPROCESSORMEMORYIMAGE_FLAG_NOUPDATE   OBPROCESSORMEMORYAREA_FLAG_NOUPDATE
#define OBPROCESSORMEMORYIMAGE_FLAG_UPDATE   OBPROCESSORMEMORYAREA_FLAG_UPDATE
#define OBPROCESSORMEMORYIMAGE_FLAG_NOINHIBIT   OBPROCESSORMEMORYAREA_FLAG_NOINHIBIT
#define OBPROCESSORMEMORYIMAGE_FLAG_INHIBIT   OBPROCESSORMEMORYAREA_FLAG_INHIBIT
#define OBPROCESSORMEMORYIMAGE_FLAG_DUMPED   OBPROCESSORMEMORYAREA_FLAG_DUMPED

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryImage : public CPtrArray
{
	// Construction
public:
	CDatabaseOBProcessorMemoryImage();
	~CDatabaseOBProcessorMemoryImage();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbBlocks;
		UINT  nAttributes;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;

	INT Add(CDatabaseOBProcessorMemoryImageBlock *pMemoryImageBlock);

	INT Find(LPCTSTR pszVersion, UINT nPage = -1, UINT nAddress = -1) CONST;

	CDatabaseOBProcessorMemoryImageBlock *GetAt(INT nIndex) CONST;
	CDatabaseOBProcessorMemoryImageBlock *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseOBProcessorMemoryImage *pMemoryImage);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryImage *pMemoryImage) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszVersion, UINT nPage, UINT nAddress, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryImages

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryImages : public CPtrArray
{
	// Construction
public:
	CDatabaseOBProcessorMemoryImages();
	~CDatabaseOBProcessorMemoryImages();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseOBProcessorMemoryImage *pMemoryImage);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseOBProcessorMemoryImage *GetAt(INT nIndex) CONST;
	CDatabaseOBProcessorMemoryImage *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseOBProcessorMemoryImages *pMemoryImages);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryImages *pMemoryImages) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryAreaCheckSum

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryAreaCheckSum : public CObject
{
	// Construction
public:
	CDatabaseOBProcessorMemoryAreaCheckSum();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nLength;
		UINT  nSeedValue;
		UINT  nDestination;
		UINT  nAddressRange[3];
		BOOL  bAddressRange;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nSeedValue;
	UINT  m_nDestination;
	UINT  m_nAddressRange[3];
	BOOL  m_bAddressRange;
	INT  m_nLength;

	// Operations
public:
	VOID SetSeed(UINT nValue);
	UINT GetSeed() CONST;
	VOID SetLength(INT nLength);
	INT GetLength() CONST;
	VOID SetDestination(UINT nDestination);
	UINT GetDestination() CONST;
	VOID SetAddressRange(UINT nPage, UINT nStartAddress, UINT nEndAddress);
	BOOL GetAddressRange(UINT &nPage, UINT &nStartAddress, UINT &nEndAddress) CONST;

	VOID Copy(CONST CDatabaseOBProcessorMemoryAreaCheckSum *pCheckSum);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryAreaCheckSum *pCheckSum) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryAreaCatalogueEntry

// Specify the on-board processor memory area catalogue entry related identifiers
#define OBPROCESSORMEMORYAREACATALOGUEENTRY_STATUS_COMPLETE   (1<<0)
#define OBPROCESSORMEMORYAREACATALOGUEENTRY_STATUS_INCOMPLETE   (1<<1)

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryAreaCatalogueEntry : public CObject
{
	// Construction
public:
	CDatabaseOBProcessorMemoryAreaCatalogueEntry();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbLocation;
		INT  cbVersion;
		INT  cbDate;
		INT  cbTime;
		UINT  nAttributes;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szLocation;
	CString  m_szVersion;
	CString  m_szDate;
	CString  m_szTime;
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
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

	VOID Copy(CONST CDatabaseOBProcessorMemoryAreaCatalogueEntry *pMemoryAreaCatalogueEntry);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryAreaCatalogueEntry *pMemoryAreaCatalogueEntry) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryAreaCatalogue

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryAreaCatalogue : public CPtrArray
{
	// Construction
public:
	CDatabaseOBProcessorMemoryAreaCatalogue();
	~CDatabaseOBProcessorMemoryAreaCatalogue();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseOBProcessorMemoryAreaCatalogueEntry *pMemoryAreaCatalogueEntry);

	INT Find(LPCTSTR pszVersion) CONST;

	CDatabaseOBProcessorMemoryAreaCatalogueEntry *GetAt(INT nIndex) CONST;
	CDatabaseOBProcessorMemoryAreaCatalogueEntry *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseOBProcessorMemoryAreaCatalogue *pMemoryAreaCatalogue);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryAreaCatalogue *pMemoryAreaCatalogue) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszVersion, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryAreaBlock

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryAreaBlock : public CObject
{
	// Construction
public:
	CDatabaseOBProcessorMemoryAreaBlock();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbParameter[2];
		INT  cbDescription;
		INT  nBitOffset;
		INT  nBitWidth;
		INT  nRef[2];
		UINT  nAddress[2];
		BOOL  bAddress;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szParameter[2];
	CString  m_szDescription;
	UINT  m_nAddress[2];
	BOOL  m_bAddress;
	INT  m_nBitOffset;
	INT  m_nBitWidth;
	INT  m_nRef[2];

	// Operations
public:
	VOID SetTMParameter(LPCTSTR pszTag);
	CString GetTMParameter() CONST;
	VOID SetTMParameterRef(INT nRef);
	INT GetTMParameterRef() CONST;
	VOID SetTCParameter(LPCTSTR pszTag);
	CString GetTCParameter() CONST;
	VOID SetTCParameterRef(INT nRef);
	INT GetTCParameterRef() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetAddress(UINT nPage, UINT nAddress);
	BOOL GetAddress(UINT &nPage, UINT &nAddress) CONST;
	VOID SetBitOffset(INT nOffset);
	INT GetBitOffset() CONST;
	VOID SetBitWidth(INT nWidth);
	INT GetBitWidth() CONST;

	VOID Copy(CONST CDatabaseOBProcessorMemoryAreaBlock *pMemoryAreaBlock);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryAreaBlock *pMemoryAreaBlock) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorMemoryArea

// Specify the on-board processor memory area related identifiers
#define OBPROCESSORMEMORYAREA_TYPE_MEMORY   (1<<0)
#define OBPROCESSORMEMORYAREA_TYPE_IMAGE   (1<<1)
#define OBPROCESSORMEMORYAREA_FLAG_NONPATCHABLE   (1<<2)
#define OBPROCESSORMEMORYAREA_FLAG_PATCHABLE   (1<<3)
#define OBPROCESSORMEMORYAREA_FLAG_PATCHALWAYS   (1<<4)
#define OBPROCESSORMEMORYAREA_FLAG_NONDUMPABLE   (1<<5)
#define OBPROCESSORMEMORYAREA_FLAG_DUMPABLE   (1<<6)
#define OBPROCESSORMEMORYAREA_FLAG_DUMPALWAYS   (1<<7)
#define OBPROCESSORMEMORYAREA_FLAG_NOUPDATE   (1<<8)
#define OBPROCESSORMEMORYAREA_FLAG_UPDATE   (1<<9)
#define OBPROCESSORMEMORYAREA_FLAG_NOINHIBIT   (1<<10)
#define OBPROCESSORMEMORYAREA_FLAG_INHIBIT   (1<<11)
#define OBPROCESSORMEMORYAREA_FLAG_DUMPED   (1<<12)

class AFX_EXT_CLASS CDatabaseOBProcessorMemoryArea : public CPtrArray
{
	// Construction
public:
	CDatabaseOBProcessorMemoryArea();
	~CDatabaseOBProcessorMemoryArea();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbPatchCommand;
		INT  cbDumpCommand;
		INT  cbDumpPacket;
		INT  cbBlocks;
		INT  cbCheckSum;
		INT  cbCatalogue;
		INT  cbMemoryImage;
		INT  nPatchCommandRef;
		INT  nDumpCommandRef;
		INT  nDumpPacketRef;
		UINT  nAttributes;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szPatchCommand;
	CString  m_szDumpCommand;
	CString  m_szDumpPacket;
	UINT  m_nAttributes;
	INT  m_nPatchCommandRef;
	INT  m_nDumpCommandRef;
	INT  m_nDumpPacketRef;
private:
	CDatabaseOBProcessorMemoryImage  m_cMemoryImage;
	CDatabaseOBProcessorMemoryAreaCheckSum  m_cCheckSum;
	CDatabaseOBProcessorMemoryAreaCatalogue   m_cCatalogue;

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
	VOID SetPatchCommandRef(INT nRef);
	INT GetPatchCommandRef() CONST;
	VOID SetDumpCommand(LPCTSTR pszCommand);
	CString GetDumpCommand() CONST;
	VOID SetDumpCommandRef(INT nRef);
	INT GetDumpCommandRef() CONST;
	VOID SetDumpPacket(LPCTSTR pszPacket);
	CString GetDumpPacket() CONST;
	VOID SetDumpPacketRef(INT nRef);
	INT GetDumpPacketRef() CONST;

	BOOL SetMemoryImage(CONST CDatabaseOBProcessorMemoryImage *pMemoryImage);
	BOOL GetMemoryImage(CDatabaseOBProcessorMemoryImage *pMemoryImage) CONST;
	CString GetMemoryImage() CONST;
	VOID SetCheckSum(CONST CDatabaseOBProcessorMemoryAreaCheckSum *pCheckSum);
	BOOL GetCheckSum(CDatabaseOBProcessorMemoryAreaCheckSum *pCheckSum) CONST;
	BOOL SetCatalogue(CONST CDatabaseOBProcessorMemoryAreaCatalogue *pCatalogue);
	BOOL GetCatalogue(CDatabaseOBProcessorMemoryAreaCatalogue *pCatalogue) CONST;

	INT Add(CDatabaseOBProcessorMemoryAreaBlock *pMemoryAreaBlock);

	INT Find(UINT nPage, UINT nAddress, INT nBitOffset) CONST;

	CDatabaseOBProcessorMemoryAreaBlock *GetAt(INT nIndex) CONST;
	CDatabaseOBProcessorMemoryAreaBlock *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseOBProcessorMemoryArea *pMemoryArea);
	BOOL Compare(CONST CDatabaseOBProcessorMemoryArea *pMemoryArea) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(UINT nPage, UINT nAddress, INT nBitOffset, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessor

// Specify the on-board processor related identifiers
#define OBPROCESSOR_ADDRESSWIDTH_BYTES   (1<<0)
#define OBPROCESSOR_ADDRESSWIDTH_WORDS   (1<<1)
#define OBPROCESSOR_ADDRESSWIDTH_DWORDS   (1<<2)
#define OBPROCESSOR_RECORDSTATUS_NONE   (1<<0)
#define OBPROCESSOR_RECORDSTATUS_NEW   (1<<1)
#define OBPROCESSOR_RECORDSTATUS_DRAFT   (1<<2)
#define OBPROCESSOR_RECORDSTATUS_CHANGED   (1<<3)
#define OBPROCESSOR_RECORDSTATUS_DELETED   (1<<4)
#define OBPROCESSOR_RECORDSTATUS_DEFAULT   (OBPROCESSOR_RECORDSTATUS_NONE | OBPROCESSOR_RECORDSTATUS_NEW | OBPROCESSOR_RECORDSTATUS_CHANGED)
#define OBPROCESSOR_RECORDSTATUS_ALL   (OBPROCESSOR_RECORDSTATUS_NONE | OBPROCESSOR_RECORDSTATUS_DRAFT | OBPROCESSOR_RECORDSTATUS_NEW | OBPROCESSOR_RECORDSTATUS_CHANGED | OBPROCESSOR_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CDatabaseOBProcessor : public CPtrArray
{
	// Construction
public:
	CDatabaseOBProcessor();
	~CDatabaseOBProcessor();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription[2];
		INT  cbPatchCommand;
		INT  cbDumpCommand;
		INT  cbDumpPacket;
		INT  cbMasterImage;
		INT  cbMemoryAreas;
		INT  nPatchCommandRef;
		INT  nDumpCommandRef;
		INT  nDumpPacketRef;
		INT  nMasterImageRef;
		INT  nDumpCount;
		INT  nStatus;
		UINT  nAttributes;
		UINT  nAddressRange[2][2];
		TIMEKEY  tDumpInterval;
		BOOL  bAddressRange;
		BOOL  bBinary;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription[2];
	CString  m_szPatchCommand;
	CString  m_szDumpCommand;
	CString  m_szDumpPacket;
	CString  m_szMasterImage;
	CTimeSpan  m_tDumpInterval;
	UINT  m_nAttributes;
	UINT  m_nAddressRange[2][2];
	BOOL  m_bAddressRange;
	INT  m_nPatchCommandRef;
	INT  m_nDumpCommandRef;
	INT  m_nDumpPacketRef;
	INT  m_nMasterImageRef;
	INT  m_nDumpCount;
	INT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetDetails(LPCTSTR pszDetails);
	CString GetDetails() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetPatchCommand(LPCTSTR pszCommand);
	CString GetPatchCommand() CONST;
	VOID SetPatchCommandRef(INT nRef);
	INT GetPatchCommandRef() CONST;
	VOID SetDumpCommand(LPCTSTR pszCommand);
	CString GetDumpCommand() CONST;
	VOID SetDumpCommandRef(INT nRef);
	INT GetDumpCommandRef() CONST;
	VOID SetDumpPacket(LPCTSTR pszPacket);
	CString GetDumpPacket() CONST;
	VOID SetDumpPacketRef(INT nRef);
	INT GetDumpPacketRef() CONST;
	VOID SetDumpInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetDumpInterval() CONST;
	VOID SetDumpCount(INT nCount);
	INT GetDumpCount() CONST;
	VOID SetMasterImage(LPCTSTR pszImage);
	CString GetMasterImage() CONST;
	VOID SetMasterImageRef(INT nRef);
	INT GetMasterImageRef() CONST;
	VOID SetAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress);
	BOOL GetAddressRange(UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CDatabaseOBProcessorMemoryArea *pMemoryArea);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseOBProcessorMemoryArea *GetAt(INT nIndex) CONST;
	CDatabaseOBProcessorMemoryArea *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseOBProcessor *pProcessor);
	BOOL Compare(CONST CDatabaseOBProcessor *pProcessor) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessors

class AFX_EXT_CLASS CDatabaseOBProcessors : public CPtrArray
{
	// Construction
public:
	CDatabaseOBProcessors();
	~CDatabaseOBProcessors();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseOBProcessor *pProcessor);

	INT Find(LPCTSTR pszName) CONST;

	CDatabaseOBProcessor *GetAt(INT nIndex) CONST;
	CDatabaseOBProcessor *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseOBProcessors *pProcessors);
	BOOL Compare(CONST CDatabaseOBProcessors *pProcessors) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bBinary = TRUE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bBinary = TRUE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDLayoutParameter

class AFX_EXT_CLASS CANDLayoutParameter : public CObject
{
	// Construction
public:
	CANDLayoutParameter();
	CANDLayoutParameter(LPCTSTR pszName);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbComment;
		INT  nContentID;
		INT  nOccurrence;
		INT  nBytePos;
		INT  nBitPos;
		INT  nDigits;
		INT  nColumn;
		INT  nRow;
		INT  nRef;
		UINT  nID;
		UINT  nAlignment;
		COLORREF  nColor;
		ULONGLONG  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szComment;
	CString  m_szDescription;
	ULONGLONG  m_nAttributes;
	COLORREF  m_nColor;
	UINT  m_nID;
	UINT  m_nAlignment;
	INT  m_nContentID;
	INT  m_nOccurrence;
	INT  m_nBytePos;
	INT  m_nBitPos;
	INT  m_nDigits;
	INT  m_nColumn;
	INT  m_nRow;
	INT  m_nRef;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetComment(LPCTSTR pszComment);
	CString GetComment() CONST;
	VOID SetContentID(INT nID);
	INT GetContentID() CONST;
	VOID SetOnBoardID(UINT nID);
	UINT GetOnBoardID() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetBytePos(INT nPos);
	INT GetBytePos() CONST;
	VOID SetBitPos(INT nPos);
	INT GetBitPos() CONST;
	VOID SetOccurrence(INT nOccurrence);
	INT GetOccurrence() CONST;
	VOID SetColumn(INT nColumn);
	INT GetColumn() CONST;
	VOID SetRow(INT nRow);
	INT GetRow() CONST;
	VOID SetDigits(INT nDigits);
	INT GetDigits() CONST;
	VOID SetAlignment(UINT nAlignment);
	UINT GetAlignment() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	BOOL SetLabel(LPCTSTR pszLabel);
	CString GetLabel() CONST;
	BOOL IsLabel() CONST;

	VOID SetRef(INT nRef);
	INT GetRef() CONST;

	VOID Copy(CONST CANDLayoutParameter *pANDLayoutParameter);
	BOOL Compare(CONST CANDLayoutParameter *pANDLayoutParameter) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDLayout

// Specify the alphanumeric display related identifiers
#define ANDLAYOUT_TYPE_SINGLECOLUMN   1
#define ANDLAYOUT_TYPE_DOUBLECOLUMN   2
#define ANDLAYOUT_TITLEITEM_ID   (1<<0)
#define ANDLAYOUT_TITLEITEM_DESCRIPTION   (1<<1)
#define ANDLAYOUT_TITLEITEM_VALUE   (1<<2)
#define ANDLAYOUT_TITLEITEM_UNIT   (1<<3)
#define ANDLAYOUT_TITLEITEM_CHANGETMUNIT   (1<<4)
#define ANDLAYOUT_TITLEITEM_CHANGETIME   (1<<5)
#define ANDLAYOUT_TITLEITEM_UPDATETMUNIT   (1<<6)
#define ANDLAYOUT_TITLEITEM_UPDATETIME   (1<<7)
#define ANDLAYOUT_TITLEITEM_EXPECTEDVALUES   (1<<8)
#define ANDLAYOUT_TITLEITEM_UNKNOWN   (1<<9)
#define ANDLAYOUT_TITLEITEMS_DEFAULT   (ANDLAYOUT_TITLEITEM_ID | ANDLAYOUT_TITLEITEM_DESCRIPTION | ANDLAYOUT_TITLEITEM_VALUE | ANDLAYOUT_TITLEITEM_UNIT)
#define ANDLAYOUT_TITLEITEMS_ALL   (ANDLAYOUT_TITLEITEMS_DEFAULT | ANDLAYOUT_TITLEITEM_CHANGETMUNIT | ANDLAYOUT_TITLEITEM_CHANGETIME | ANDLAYOUT_TITLEITEM_UPDATETMUNIT | ANDLAYOUT_TITLEITEM_UPDATETIME | ANDLAYOUT_TITLEITEM_EXPECTEDVALUES)
#define ANDLAYOUT_RECORDSTATUS_NONE   (1<<0)
#define ANDLAYOUT_RECORDSTATUS_NEW   (1<<1)
#define ANDLAYOUT_RECORDSTATUS_DRAFT   (1<<2)
#define ANDLAYOUT_RECORDSTATUS_CHANGED   (1<<3)
#define ANDLAYOUT_RECORDSTATUS_DELETED   (1<<4)
#define ANDLAYOUT_RECORDSTATUS_DEFAULT   (ANDLAYOUT_RECORDSTATUS_NONE | ANDLAYOUT_RECORDSTATUS_NEW | ANDLAYOUT_RECORDSTATUS_CHANGED)
#define ANDLAYOUT_RECORDSTATUS_ALL   (ANDLAYOUT_RECORDSTATUS_NONE | ANDLAYOUT_RECORDSTATUS_DRAFT | ANDLAYOUT_RECORDSTATUS_NEW | ANDLAYOUT_RECORDSTATUS_CHANGED | ANDLAYOUT_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CANDLayout : public CPtrArray
{
	// Construction
public:
	CANDLayout();
	CANDLayout(LPCTSTR pszName);
	~CANDLayout();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbTitle;
		INT  cbColumns;
		INT  cbParameters;
		INT  nStatus;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szTitle;
	CString  m_szXmlCode;
	CString  m_szFileName;
	CUIntArray  m_nColumns;
	INT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetColumns(CONST CUIntArray &nColumns);
	INT GetColumns(CUIntArray &nColumns) CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	VOID SetXmlCode(LPCTSTR pszCode);
	CString GetXmlCode() CONST;
	CString GetFileName() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CANDLayoutParameter *pANDParameter);

	INT Find(LPCTSTR pszName, INT nOccurrence = 0) CONST;

	CANDLayoutParameter *GetAt(INT nIndex) CONST;
	CANDLayoutParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CANDLayout *pANDLayout);
	BOOL Compare(CONST CANDLayout *pANDLayout) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDLayouts

class AFX_EXT_CLASS CANDLayouts : public CPtrArray
{
	// Construction
public:
	CANDLayouts();
	~CANDLayouts();

	// Attributes
public:

	// Operations
public:
	INT Add(CANDLayout *pANDLayout);

	INT Find(LPCTSTR pszName) CONST;

	CANDLayout *GetAt(INT nIndex) CONST;
	CANDLayout *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CANDLayouts *pANDLayouts);
	BOOL Compare(CONST CANDLayouts *pANDLayouts) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDLayoutParameter

// Specify the graphic display parameter related identifiers
#define GRDLAYOUTPARAMETER_LINESTYLE_SOLID   PS_SOLID
#define GRDLAYOUTPARAMETER_LINESTYLE_DOTTED   PS_DOT
#define GRDLAYOUTPARAMETER_LINESTYLE_DASHED   PS_DASH
#define GRDLAYOUTPARAMETER_LINESYMBOL_NONE   0
#define GRDLAYOUTPARAMETER_LINESYMBOL_POINT   1
#define GRDLAYOUTPARAMETER_LINESYMBOL_STROKE   2
#define GRDLAYOUTPARAMETER_LINESYMBOL_CROSS   3
#define GRDLAYOUTPARAMETER_LINESYMBOL_SQUARE   4

class AFX_EXT_CLASS CGRDLayoutParameter : public CObject
{
	// Construction
public:
	CGRDLayoutParameter();
	CGRDLayoutParameter(LPCTSTR pszName);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbComment;
		INT  nRow;
		INT  nRef;
		INT  nDigits;
		INT  nOccurrence;
		INT  nLineWidth;
		INT  nLineStyle;
		INT  nLineSymbol;
		double  fMinimum;
		double  fMaximum;
		COLORREF  nColor;
		ULONGLONG  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szComment;
	CTimeSpan  m_tAutoScale;
	ULONGLONG  m_nAttributes;
	COLORREF  m_nColor;
	double  m_fMinimum;
	double  m_fMaximum;
	INT  m_nMargin[2];
	INT  m_nLineWidth;
	INT  m_nLineStyle;
	INT  m_nLineSymbol;
	INT  m_nOccurrence;
	INT  m_nDigits;
	INT  m_nRow;
	INT  m_nRef;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetComment(LPCTSTR pszComment);
	CString GetComment() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;
	VOID SetPosition(INT nRow);
	INT GetPosition() CONST;
	VOID SetOccurrence(INT nOccurrence);
	INT GetOccurrence() CONST;
	VOID SetDigits(INT nDigits);
	INT GetDigits() CONST;
	VOID SetMargin(INT nLower, INT nUpper);
	BOOL GetMargin(INT &nLower, INT &nUpper) CONST;
	VOID SetRange(double fMinimum, double fMaximum);
	BOOL GetRange(double &fMinimum, double &fMaximum) CONST;
	VOID SetAutoScaleDelay(CONST CTimeSpan &tDelay);
	CTimeSpan GetAutoScaleDelay() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetLineWidth(INT nWidth);
	INT GetLineWidth() CONST;
	VOID SetLineStyle(INT nStyle);
	INT GetLineStyle() CONST;
	VOID SetLineSymbol(INT nSymbol);
	INT GetLineSymbol() CONST;

	VOID SetRef(INT nRef);
	INT GetRef() CONST;

	VOID Copy(CONST CGRDLayoutParameter *pGRDLayoutParameter);
	BOOL Compare(CONST CGRDLayoutParameter *pGRDLayoutParameter) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDLayout

// Specify the graphic display related identifiers
#define GRDLAYOUT_TYPE_NORMAL   1
#define GRDLAYOUT_TYPE_STRIPCHART   2
#define GRDLAYOUT_TYPE_STACKCHART   3
#define GRDLAYOUT_TYPE_DIAGRAM   4
#define GRDLAYOUT_MODE_NORMAL   (1<<0)
#define GRDLAYOUT_MODE_AREA   (1<<1)
#define GRDLAYOUT_MODE_SCROLL   (1<<2)
#define GRDLAYOUT_MODE_OVERWRITE   (1<<3)
#define GRDLAYOUT_MODE_RESTART   (1<<4)
#define GRDLAYOUT_GRAPH_WIDTH   750
#define GRDLAYOUT_GRAPH_HEIGHT   350
#define GRDLAYOUT_TITLEITEM_ID   (1<<0)
#define GRDLAYOUT_TITLEITEM_DESCRIPTION   (1<<1)
#define GRDLAYOUT_TITLEITEM_VALUE   (1<<2)
#define GRDLAYOUT_TITLEITEM_UNIT   (1<<3)
#define GRDLAYOUT_TITLEITEM_RANGE   (1<<4)
#define GRDLAYOUT_TITLEITEM_LINE   (1<<5)
#define GRDLAYOUT_TITLEITEM_CHANGETMUNIT   (1<<6)
#define GRDLAYOUT_TITLEITEM_CHANGETIME   (1<<7)
#define GRDLAYOUT_TITLEITEM_UPDATETMUNIT   (1<<8)
#define GRDLAYOUT_TITLEITEM_UPDATETIME   (1<<9)
#define GRDLAYOUT_TITLEITEM_UNKNOWN   (1<<10)
#define GRDLAYOUT_TITLEITEMS_DEFAULT   (GRDLAYOUT_TITLEITEM_ID | GRDLAYOUT_TITLEITEM_DESCRIPTION | GRDLAYOUT_TITLEITEM_VALUE | GRDLAYOUT_TITLEITEM_UNIT | GRDLAYOUT_TITLEITEM_RANGE | GRDLAYOUT_TITLEITEM_LINE)
#define GRDLAYOUT_TITLEITEMS_ALL   (GRDLAYOUT_TITLEITEMS_DEFAULT | GRDLAYOUT_TITLEITEM_CHANGETMUNIT | GRDLAYOUT_TITLEITEM_CHANGETIME | GRDLAYOUT_TITLEITEM_UPDATETMUNIT | GRDLAYOUT_TITLEITEM_UPDATETIME)
#define GRDLAYOUT_RECORDSTATUS_NONE   (1<<0)
#define GRDLAYOUT_RECORDSTATUS_NEW   (1<<1)
#define GRDLAYOUT_RECORDSTATUS_DRAFT   (1<<2)
#define GRDLAYOUT_RECORDSTATUS_CHANGED   (1<<3)
#define GRDLAYOUT_RECORDSTATUS_DELETED   (1<<4)
#define GRDLAYOUT_RECORDSTATUS_DEFAULT   (GRDLAYOUT_RECORDSTATUS_NONE | GRDLAYOUT_RECORDSTATUS_NEW | GRDLAYOUT_RECORDSTATUS_CHANGED)
#define GRDLAYOUT_RECORDSTATUS_ALL   (GRDLAYOUT_RECORDSTATUS_NONE | GRDLAYOUT_RECORDSTATUS_DRAFT | GRDLAYOUT_RECORDSTATUS_NEW | GRDLAYOUT_RECORDSTATUS_CHANGED | GRDLAYOUT_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CGRDLayout : public CPtrArray
{
	// Construction
public:
	CGRDLayout();
	CGRDLayout(LPCTSTR pszName);
	~CGRDLayout();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbTitle;
		INT  cbColumns;
		INT  cbParameters;
		INT  nType;
		INT  nMode;
		INT  nCount;
		INT  nGrids[2];
		INT  nTicks[2];
		INT  nWidth[2];
		INT  nStatus;
		SIZE  sizePlot;
		TIMEKEY  tDuration;
		TIMEKEY  tInterval[2];
		COLORREF  nGridsColor;
		COLORREF  nTicksColor;
		COLORREF  nBkgndColor;
		COLORREF  nLabelColor;
	} DATA, *PDATA, *LPDATA;
	typedef struct tagSCALINGDATA {
		INT  cbSize;
		INT  cbData;
	} SCALINGDATA, *PSCALINGDATA, *LPSCALINGDATA;
	typedef struct tagPARAMETERSCALINGDATA {
		INT  nRef;
		INT  nMargin[2];
		double  fRange[2];
		TIMEKEY  tDelay;
	} PARAMETERSCALINGDATA, *PPARAMETERSCALINGDATA, *LPPARAMETERSCALINGDATA;
private:
	CString  m_szName;
	CString  m_szTitle;
	CString  m_szXmlCode;
	CString  m_szFileName;
	CUIntArray  m_nColumns;
	CTimeSpan  m_tDuration;
	CTimeSpan  m_tInterval[2];
	COLORREF  m_nGridsColor;
	COLORREF  m_nTicksColor;
	COLORREF  m_nBkgndColor;
	COLORREF  m_nLabelColor;
	CSize  m_sizePlot;
	INT  m_nGrids[2];
	INT  m_nTicks[2];
	INT  m_nWidth[2];
	INT  m_nStatus;
	INT  m_nCount;
	INT  m_nType;
	INT  m_nMode;

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
	VOID SetColumns(CONST CUIntArray &nColumns);
	INT GetColumns(CUIntArray &nColumns) CONST;
	VOID SetDuration(CONST CTimeSpan &tDuration);
	CTimeSpan GetDuration() CONST;
	VOID SetInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetInterval() CONST;
	VOID SetUpdateInterval(CONST CTimeSpan &tInterval);
	CTimeSpan GetUpdateInterval() CONST;
	BOOL SetScalingData(CONST CByteArray &nData);
	BOOL GetScalingData(CByteArray &nData) CONST;
	VOID SetPlotSize(CONST SIZE &size);
	CSize GetPlotSize() CONST;
	VOID SetGrids(INT X, INT Y);
	BOOL GetGrids(INT &X, INT &Y) CONST;
	VOID SetTicks(INT X, INT Y);
	BOOL GetTicks(INT &X, INT &Y) CONST;
	VOID SetGridsWidth(INT nWidth);
	INT GetGridsWidth() CONST;
	VOID SetTicksWidth(INT nWidth);
	INT GetTicksWidth() CONST;
	VOID SetGridsColor(COLORREF nColor);
	COLORREF GetGridsColor() CONST;
	VOID SetTicksColor(COLORREF nColor);
	COLORREF GetTicksColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;
	VOID SetLabelColor(COLORREF nColor);
	COLORREF GetLabelColor() CONST;
	VOID SetParameters(INT nCount);
	INT GetParameters() CONST;
	VOID SetXmlCode(LPCTSTR pszCode);
	CString GetXmlCode() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CGRDLayoutParameter *pGRDParameter);

	INT Find(LPCTSTR pszName) CONST;

	CGRDLayoutParameter *GetAt(INT nIndex) CONST;
	CGRDLayoutParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CGRDLayout *pGRDLayout);
	BOOL Compare(CONST CGRDLayout *pGRDLayout) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDLayouts

class AFX_EXT_CLASS CGRDLayouts : public CPtrArray
{
	// Construction
public:
	CGRDLayouts();
	~CGRDLayouts();

	// Attributes
public:

	// Operations
public:
	INT Add(CGRDLayout *pGRDLayout);

	INT Find(LPCTSTR pszName) CONST;

	CGRDLayout *GetAt(INT nIndex) CONST;
	CGRDLayout *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CGRDLayouts *pGRDLayouts);
	BOOL Compare(CONST CGRDLayouts *pGRDLayouts) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDLayoutItem

class AFX_EXT_CLASS CMMDLayoutItem : public CObject
{
	// Construction
public:
	CMMDLayoutItem();
	CMMDLayoutItem(LPCTSTR pszName);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbType;
		INT  cbText;
		INT  cbInfo;
		INT  cbLink;
		CLSID  clsid;
		XFORM  xForm;
		RECT  rPosition;
		BOOL  bVisible;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szType;
	CString  m_szText;
	CString  m_szLink;
	CByteArray  m_nInfo;
	CRect  m_rPosition;
	XFORM  m_xForm;
	CLSID  m_clsid;
	BOOL  m_bVisible;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(LPCTSTR pszType);
	CString GetType() CONST;
	VOID SetClassID(CLSID clsid);
	CLSID GetClassID() CONST;
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;
	VOID SetLink(LPCTSTR pszName);
	CString GetLink() CONST;
	VOID SetPosition(CONST RECT &rect);
	CRect GetPosition() CONST;
	VOID SetTransformation(CONST XFORM &xForm);
	VOID GetTransformation(XFORM &xForm) CONST;
	VOID SetProperties(CONST CByteArray &nInfo);
	BOOL GetProperties(CByteArray &nInfo) CONST;
	VOID SetVisible(BOOL bFlag);
	BOOL IsVisible() CONST;

	VOID Copy(CONST CMMDLayoutItem *pMMDLayoutItem);
	BOOL Compare(CONST CMMDLayoutItem *pMMDLayoutItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDLayout

class AFX_EXT_CLASS CMMDLayout : public CPtrArray
{
	// Construction
public:
	CMMDLayout();
	CMMDLayout(LPCTSTR pszName);
	~CMMDLayout();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbTitle;
		INT  cbCode[2];
		INT  cbItems;
		INT  nImageMargin[4];
		SIZE  sizeImage;
		SIZE  sizeGrid;
		BOOL  bUseGrid;
		COLORREF  nImageBkgnd;
		COLORREF  nImageGrid;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szTitle;
	CString  m_szCode;
	CByteArray  m_nCode;
	CSize  m_sizeImage;
	CSize  m_sizeGrid;
	COLORREF  m_nImageBkgnd;
	COLORREF  m_nImageGrid;
	INT  m_nImageMargin[4];
	BOOL  m_bUseGrid;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetImage(CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid);
	VOID GetImage(SIZE &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, SIZE &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid) CONST;
	VOID SetSourceCode(LPCTSTR pszCode);
	VOID SetSourceCode(CONST CByteArray &nCode);
	CString GetSourceCode() CONST;
	INT GetSourceCode(CByteArray &nCode) CONST;

	INT Add(CMMDLayoutItem *pMMDLayoutItem);

	INT Find(LPCTSTR pszName) CONST;

	CMMDLayoutItem *GetAt(INT nIndex) CONST;
	CMMDLayoutItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CMMDLayout *pMMDLayout);
	BOOL Compare(CONST CMMDLayout *pMMDLayout) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDLayouts

class AFX_EXT_CLASS CMMDLayouts : public CPtrArray
{
	// Construction
public:
	CMMDLayouts();
	~CMMDLayouts();

	// Attributes
public:

	// Operations
public:
	INT Add(CMMDLayout *pMMDLayout);

	INT Find(LPCTSTR pszName) CONST;

	CMMDLayout *GetAt(INT nIndex) CONST;
	CMMDLayout *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CMMDLayouts *pMMDLayouts);
	BOOL Compare(CONST CMMDLayouts *pMMDLayouts) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODLayoutExpression

class AFX_EXT_CLASS CPODLayoutExpression : public CObject
{
	// Construction
public:
	CPODLayoutExpression();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbFunction;
		INT  cbOperator;
		INT  cbParameter;
		INT  cbComment;
		INT  nSample;
		INT  nNumberFlag;
		double  fNumber;
		ULONGLONG  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szParameter;
	CString  m_szFunction;
	CString  m_szOperator;
	CString  m_szComment;
	ULONGLONG  m_nAttributes;
	double  m_fNumber;
	INT  m_nNumberFlag;
	INT  m_nSample;

	// Operations
public:
	VOID SetFunction(LPCTSTR pszFunction);
	CString GetFunction() CONST;
	BOOL IsFunction() CONST;

	VOID SetOperator(LPCTSTR pszOperator);
	CString GetOperator() CONST;
	BOOL IsOperator() CONST;

	VOID SetParameter(LPCTSTR pszParameter);
	VOID SetParameter(LPCTSTR pszParameter, INT nSample, ULONGLONG nAttributes);
	CString GetParameter() CONST;
	BOOL GetParameter(CString &szParameter, INT &nSample, ULONGLONG &nAttributes) CONST;
	BOOL IsParameter() CONST;

	VOID SetNumber(double fNumber, BOOL bPoint = FALSE);
	double GetNumber() CONST;
	CString GetNumberAsText() CONST;
	BOOL IsNumber() CONST;

	VOID SetComment(LPCTSTR pszComment);
	CString GetComment() CONST;

	BOOL IsEmpty() CONST;

	VOID Copy(CONST CPODLayoutExpression *pPODLayoutExpression);
	BOOL Compare(CONST CPODLayoutExpression *pPODLayoutExpression) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODLayout

// Specify the parameter observation display related identifiers
#define PODLAYOUT_TITLEITEM_TIME   (1<<0)
#define PODLAYOUT_TITLEITEM_VALUE   (1<<1)
#define PODLAYOUT_TITLEITEM_STATUS   (1<<2)
#define PODLAYOUT_TITLEITEM_QUALITY   (1<<3)
#define PODLAYOUT_TITLEITEM_UNKNOWN   (1<<4)
#define PODLAYOUT_TITLEITEMS_DEFAULT   (PODLAYOUT_TITLEITEM_TIME | PODLAYOUT_TITLEITEM_VALUE | PODLAYOUT_TITLEITEM_STATUS | PODLAYOUT_TITLEITEM_QUALITY)
#define PODLAYOUT_TITLEITEMS_ALL   (PODLAYOUT_TITLEITEMS_DEFAULT | PODLAYOUT_TITLEITEM_QUALITY)
#define PODLAYOUT_RECORDSTATUS_NONE   (1<<0)
#define PODLAYOUT_RECORDSTATUS_NEW   (1<<1)
#define PODLAYOUT_RECORDSTATUS_DRAFT   (1<<2)
#define PODLAYOUT_RECORDSTATUS_CHANGED   (1<<3)
#define PODLAYOUT_RECORDSTATUS_DELETED   (1<<4)
#define PODLAYOUT_RECORDSTATUS_DEFAULT   (PODLAYOUT_RECORDSTATUS_NONE | PODLAYOUT_RECORDSTATUS_NEW | PODLAYOUT_RECORDSTATUS_CHANGED)
#define PODLAYOUT_RECORDSTATUS_ALL   (PODLAYOUT_RECORDSTATUS_NONE | PODLAYOUT_RECORDSTATUS_DRAFT | PODLAYOUT_RECORDSTATUS_NEW | PODLAYOUT_RECORDSTATUS_CHANGED | PODLAYOUT_RECORDSTATUS_DELETED)

class AFX_EXT_CLASS CPODLayout : public CPtrArray
{
	// Construction
public:
	CPODLayout();
	CPODLayout(LPCTSTR pszName);
	~CPODLayout();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbTitle;
		INT  cbFunctions;
		INT  cbParameters[2];
		INT  cbExpressions;
		INT  nStatus;
		UINT  nColumns;
		COLORREF  nColors[3];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szTitle;
	CString  m_szXmlCode;
	CString  m_szFileName;
	CStringArray  m_szFunctions;
	CStringArray  m_szParameters;
	CLongUIntArray  m_nAttributes;
	COLORREF  m_nColors[3];
	UINT  m_nColumns;
	INT  m_nStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetColumns(UINT nColumns);
	UINT GetColumns() CONST;
	VOID SetParameters(CONST CStringArray &szParameters);
	VOID SetParameters(CONST CStringArray &szParameters, CONST CLongUIntArray &nAttributes);
	INT GetParameters(CStringArray &szParameters) CONST;
	INT GetParameters(CStringArray &szParameters, CLongUIntArray &nAttributes) CONST;
	VOID SetParametersColor(COLORREF nColor);
	COLORREF GetParametersColor() CONST;
	VOID SetFunctions(CONST CStringArray &szFunctions);
	INT GetFunctions(CStringArray &szFunctions) CONST;
	VOID SetFunctionsColor(COLORREF nColor);
	COLORREF GetFunctionsColor() CONST;
	VOID SetExpressionColor(COLORREF nColor);
	COLORREF GetExpressionColor() CONST;
	VOID SetXmlCode(LPCTSTR pszCode);
	CString GetXmlCode() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetStatus(INT nStatus);
	INT GetStatus() CONST;

	INT Add(CPODLayoutExpression *pPODExpression);

	INT Find(LPCTSTR pszExpression, INT nIndex = -1) CONST;

	CPODLayoutExpression *GetAt(INT nIndex) CONST;
	CPODLayoutExpression *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CPODLayout *pPODLayout);
	BOOL Compare(CONST CPODLayout *pPODLayout) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODLayouts

class AFX_EXT_CLASS CPODLayouts : public CPtrArray
{
	// Construction
public:
	CPODLayouts();
	~CPODLayouts();

	// Attributes
public:

	// Operations
public:
	INT Add(CPODLayout *pPODLayout);

	INT Find(LPCTSTR pszName) CONST;

	CPODLayout *GetAt(INT nIndex) CONST;
	CPODLayout *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CPODLayouts *pPODLayouts);
	BOOL Compare(CONST CPODLayouts *pPODLayouts) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationScript

#define AUTOMATIONSCRIPT_TYPE_NONE   0
#define AUTOMATIONSCRIPT_TYPE_EXCEL   1
#define AUTOMATIONSCRIPT_TYPE_WORD   2
#define AUTOMATIONSCRIPT_TYPE_ACCESS  3
#define AUTOMATIONSCRIPT_TYPE_OUTLOOK   4
#define AUTOMATIONSCRIPT_TYPE_POWERPOINT   5
#define AUTOMATIONSCRIPT_TYPE_OTHER   6

class AFX_EXT_CLASS CAutomationScript : public CObject
{
	// Construction
public:
	CAutomationScript();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbTitle;
		INT  cbCode[2];
		INT  cbFileName[3];
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szCode;
	CString  m_szTitle;
	CString  m_szFileName[3];
	CByteArray  m_nCode;
	UINT  m_nType;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetSourceCode(LPCTSTR pszCode);
	VOID SetSourceCode(CONST CByteArray &nCode);
	CString GetSourceCode() CONST;
	INT GetSourceCode(CByteArray &nCode) CONST;
	VOID SetExecutableFileName(LPCTSTR pszFileName);
	CString GetExecutableFileName() CONST;
	VOID SetInputFileName(LPCTSTR pszFileName);
	CString GetInputFileName() CONST;
	VOID SetOutputFileName(LPCTSTR pszFileName);
	CString GetOutputFileName() CONST;

	BOOL Copy(CONST CAutomationScript *pScript);
	BOOL Compare(CONST CAutomationScript *pScript) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationScripts

class AFX_EXT_CLASS CAutomationScripts : public CPtrArray
{
	// Construction
public:
	CAutomationScripts();
	~CAutomationScripts();

	// Attributes
public:

	// Operations
public:
	INT Add(CAutomationScript *pScript);

	INT Find(LPCTSTR pszName) CONST;

	CAutomationScript *GetAt(INT nIndex) CONST;
	CAutomationScript *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CAutomationScripts *pScripts);
	BOOL Compare(CONST CAutomationScripts *pScripts) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bDirectory = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bDirectory = FALSE);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseLogInfo

class AFX_EXT_CLASS CDatabaseLogInfo : public CObject
{
	// Construction
public:
	CDatabaseLogInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbText;
		INT  cbUser;
		INT  cbData;
		TIMEKEY  tTime;
		ULONGLONG  nComponent;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szText;
	CString  m_szUser;
	CTimeKey  m_tTime;
	ULONGLONG  m_nComponent;
	CByteArray  m_nData;

	// Operations
public:
	VOID SetLog(LPCTSTR pszName, LPCTSTR pszText, LPCTSTR pszUser, ULONGLONG nComponent, CONST CTimeKey &tTime, CONST CByteArray &nData);
	BOOL GetLog(CString &szName, CString &szText, CString &szUser, ULONGLONG &nComponent, CTimeKey &tTime, CByteArray &nData) CONST;

	VOID SetLogName(LPCTSTR pszName);
	CString GetLogName() CONST;
	VOID SetLogText(LPCTSTR pszText);
	CString GetLogText() CONST;
	VOID SetLogUser(LPCTSTR pszUser);
	CString GetLogUser() CONST;
	VOID SetLogType(ULONGLONG nComponent);
	ULONGLONG GetLogType() CONST;
	VOID SetLogTime(CONST CTimeKey &tTime);
	CTimeKey GetLogTime() CONST;
	VOID SetLogData(CONST CByteArray &nData);
	INT GetLogData(CByteArray &nData) CONST;

	VOID Reset();

	VOID Copy(CONST CDatabaseLogInfo *pLogInfo);
	BOOL Compare(CONST CDatabaseLogInfo *pLogInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseLogs

class AFX_EXT_CLASS CDatabaseLogs : public CPtrArray
{
	// Construction
public:
	CDatabaseLogs();
	~CDatabaseLogs();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseLogInfo *pLogInfo);

	INT Find(CONST CDatabaseLogInfo *pLogInfo) CONST;

	CDatabaseLogInfo *GetAt(INT nIndex) CONST;
	CDatabaseLogInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseLogs *pLogs);
	BOOL Compare(CONST CDatabaseLogs *pLogs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(CONST CTimeKey &tTime, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTableView window

// Specify the database table view drawing related identifiers
#define DATABASETABLEVIEW_TABLE_DISTANCE   50
#define DATABASETABLEVIEW_TABLE_CONNECTIONLINESIZE   3
#define DATABASETABLEVIEW_TABLE_OUTERBORDERMARGIN   6
#define DATABASETABLEVIEW_TABLE_OUTERBORDERSIZE   3
#define DATABASETABLEVIEW_TABLE_INNERBORDERMARGIN   3
#define DATABASETABLEVIEW_TABLE_INNERBORDERSIZE   1
// Specify the database table view printing related identifiers
#define DATABASETABLEVIEW_PRINT_TABLE   (1<<0)
#define DATABASETABLEVIEW_PRINT_SUBTABLE   (1<<1)
#define DATABASETABLEVIEW_PRINT_ALL   (1<<2)

class AFX_EXT_CLASS CDatabaseTableView : public CTableView
{
	// Construction
public:
	CDatabaseTableView(ULONGLONG nComponent);

	// Attributes
public:
	CString  m_szName;
	LOGFONT  m_lfTable[2];
	COLORREF  m_nTableColors[2];
	COLORREF  m_nTableFontColors[2];
	ULONGLONG  m_nComponent;
public:
	INT  m_nDatabaseTMPacketIndex;
	INT  m_nDatabaseTCFunctionIndex;
	INT  m_nDatabaseTCSequenceIndex;
	INT  m_nDatabaseOBProcessorIndex;
	INT  m_nDatabaseTMParameterIndex;
	INT  m_nDatabaseTCParameterIndex;
	INT  m_nANDLayoutIndex;
	INT  m_nGRDLayoutIndex;
	INT  m_nPODLayoutIndex;
public:
	CDatabaseTMPackets  m_pDatabaseTMPackets[2];
	CDatabaseTCPackets  m_pDatabaseTCPackets[2];
	CDatabaseTCFunctions  m_pDatabaseTCFunctions[2];
	CDatabaseTCSequences  m_pDatabaseTCSequences[2];
	CDatabaseOBProcessors  m_pDatabaseOBProcessors[2];
	CDatabaseTMParameters  m_pDatabaseTMParameters[2];
	CDatabaseTCParameters  m_pDatabaseTCParameters[2];
	CDatabaseTMNumCalTables  m_pDatabaseTMNumCalTables[2];
	CDatabaseTMTxtCalTables  m_pDatabaseTMTxtCalTables[2];
	CDatabaseTMNumOolTables  m_pDatabaseTMNumOolTables[2];
	CDatabaseTMTxtOolTables  m_pDatabaseTMTxtOolTables[2];
	CDatabaseTCNumCalTables  m_pDatabaseTCNumCalTables[2];
	CDatabaseTCTxtCalTables  m_pDatabaseTCTxtCalTables[2];
	CDatabaseTCNumOolTables  m_pDatabaseTCNumOolTables[2];
	CDatabaseTCTxtOolTables  m_pDatabaseTCTxtOolTables[2];
	CDatabaseTCPreExeGroups  m_pDatabaseTCPreExeGroups[2];
	CDatabaseTCExeVerStages  m_pDatabaseTCExeVerStages[2];
	CDatabaseTCExeVerGroups  m_pDatabaseTCExeVerGroups[2];
	CDatabaseTMPacketGroups  m_pDatabaseTMPacketGroups[2];
	CDatabaseTMPacketHeaders  m_pDatabaseTMPacketHeaders[2];
	CDatabaseTMPacketStreams  m_pDatabaseTMPacketStreams[2];
	CDatabaseTCParameterSets  m_pDatabaseTCParameterSets[2];
	CDatabaseTCFunctionBlocks  m_pDatabaseTCFunctionBlocks[2];
	CDatabaseTMParameterGroups  m_pDatabaseTMParameterGroups[2];
	CDatabaseTCPacketParameters  m_pDatabaseTCPacketParameters[2];
	CDatabaseTCParameterValueSets  m_pDatabaseTCParameterValueSets[2];
	CDatabaseTCFunctionRoutingPaths  m_pDatabaseTCFunctionRoutingPaths[2];
	CDatabaseTMPacketIdentifications  m_pDatabaseTMPacketIdentifications[2];
	CDatabaseTMPacketIdentificationCriteria  m_pDatabaseTMPacketIdentificationCriteria[2];
	CDatabaseOBProcessorMemoryImages  m_pDatabaseOBProcessorMemoryImages[2];
	CANDLayouts  m_pANDLayouts[2];
	CGRDLayouts  m_pGRDLayouts[2];
	CPODLayouts  m_pPODLayouts[2];

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetComponent(ULONGLONG nComponent);
	ULONGLONG GetComponent() CONST;

	INT ExtractTextItems(LPCTSTR pszText, CStringArray &szItems) CONST;
	CString ConvertTabbedTextItem(LPCTSTR pszText, BOOL bConvert = TRUE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseTableView)
public:
	virtual INT EnumTables(CStringArray &szTables, CUIntArray &nTypes, BOOL bMenu, BOOL bResetable = FALSE) CONST = 0;
	virtual BOOL GetTableTitle(LPCTSTR pszTable, CString &szTitle) CONST = 0;
	virtual BOOL GetTableLayout(LPCTSTR pszTable, CUIntArray &nWidths) CONST = 0;
	virtual BOOL GetTableLayout(LPCTSTR pszTable, LPCTSTR pszItem, CUIntArray &nWidths) CONST = 0;
	virtual BOOL GetTablePosition(LPCTSTR pszTable, CString &szTable, CRect &rPosition) CONST = 0;
	virtual BOOL SetTableFloatingAlignment(LPCTSTR pszTable, INT nRow) = 0;
	virtual INT GetTableFloatingAlignment(LPCTSTR pszTable) CONST = 0;
	virtual BOOL AlignFloatingTable(LPCTSTR pszTable) = 0;
	virtual BOOL GetTableOutline(LPCTSTR pszTable, COLORREF &nTitleRowColor, COLORREF &nFirstRowColor, COLORREF &nFirstColumnColor, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, INT &nOuterBorderSize, INT &nOuterBorderStyle, COLORREF &nOuterBorderColor, INT &nInnerBorderSize, INT &nInnerBorderStyle, COLORREF &nInnerBorderColor) CONST = 0;
	virtual BOOL GetTableOutlineFonts(LPCTSTR pszTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST = 0;
	virtual BOOL GetTableOutlineLimits(LPCTSTR pszTable, INT &nMinRows, INT &nMaxRows) CONST = 0;
	virtual BOOL GetTableContents(LPCTSTR pszTable, LPCTSTR pszItem, INT nRows, CStringArray &szContents, CStringArray &szDescriptions, CStringArray &szDataTypes, CUIntArray &nFormats, CUIntArray &nIDs, BOOL &bResize, BOOL &bVisible) CONST = 0;
	virtual INT EnumTableFieldValues(LPCTSTR pszTable, LPCTSTR pszField, CStringArray &szValues, CLongUIntArray &nValues) CONST = 0;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, INT &nLow, INT &nHigh) CONST = 0;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, UINT &uLow, UINT &uHigh) CONST = 0;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, double &fLow, double &fHigh) CONST = 0;
	virtual BOOL GetTableContext(LPCTSTR pszTable, CString &szTable, UINT &nControlID, CString &szValue) CONST = 0;
	virtual INT EnumTableUpdates(UINT nControlID, CStringArray &szTables) CONST = 0;
	virtual BOOL GetTableUpdateContents(LPCTSTR pszTable, UINT nControlID, LPCTSTR pszValue, CString &szItem, CStringArray &szContents) CONST = 0;
	virtual BOOL UpdateTableFieldData(UINT nControlID, LPCTSTR pszValue, LPCTSTR pszOldValue = NULL) = 0;
	virtual INT InsertTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue) = 0;
	virtual BOOL InsertTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol = -1) = 0;
	virtual BOOL CheckTableFieldData(LPCTSTR pszTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST = 0;
	virtual BOOL CheckTableFieldData(LPCTSTR pszTable, CStringArray &szIssues) CONST = 0;
	virtual BOOL SelectTableFieldData(LPCTSTR pszTable, CONST POINT &pt) = 0;
	virtual BOOL SelectTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue) = 0;
	virtual BOOL SaveTableFieldData(LPCTSTR pszTable, BOOL bPrompt = FALSE) = 0;
	virtual BOOL ProtectTableFieldData(LPCTSTR pszTable, BOOL bUndo = FALSE) = 0;
	virtual BOOL DeleteTableFieldData(LPCTSTR pszTable) = 0;
	virtual INT DeleteTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue) = 0;
	virtual BOOL DeleteTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol = -1) = 0;
	virtual BOOL GetTableFieldFlag(LPCTSTR pszTable, INT nRow, INT nCol, CString &szFlag) CONST = 0;
	virtual INT EnumTableDropTargets(ULONGLONG nComponent, CStringArray &szTables, CStringArray &szFields) CONST = 0;
	virtual BOOL FindTableDropTargetCell(LPCTSTR pszTable, LPCTSTR pszField, ULONGLONG nComponent, LPCTSTR pszItem, CString &szItem, INT &nRow, INT &nCol) CONST = 0;
	virtual INT EnumPrintTables(LPCTSTR pszTable, UINT nFlags, CStringArray &szTables) CONST = 0;
	virtual BOOL GetPrintTableContents(LPCTSTR pszTable, LPCTSTR pszItem, CStringArray &szContents) CONST = 0;
	virtual BOOL PrintTable(LPCTSTR pszTable, LPCTSTR pszItem, CMetaFileDC &cMetaDC) = 0;
	virtual ULONGLONG TranslateTableNameToComponent(LPCTSTR pszTable) CONST = 0;
	virtual CString TranslateComponentToTableName(ULONGLONG nComponent) CONST = 0;
	virtual INT TranslateTableFieldToIndex(LPCTSTR pszTable, LPCTSTR pszField) CONST = 0;
	virtual UINT TranslateTableFieldToID(LPCTSTR pszTable, LPCTSTR pszField) CONST = 0;
public:
	virtual INT EnumTables(CTableViewObjects *pTables) CONST = 0;
	virtual VOID RepositionTables(CONST CTableViewObjects *pTables) = 0;
	virtual VOID RepositionTables() = 0;
	virtual VOID ArrangeTables() = 0;
	virtual VOID ArrangeTables(UINT nControlID) = 0;
	virtual VOID RefreshTables(BOOL bAll = TRUE) = 0;
	virtual VOID RefreshTables(CONST CStringArray &szTables, BOOL bAll = TRUE) = 0;
	virtual VOID RefreshTables(CONST CTableViewObject *pTable, BOOL bAll = TRUE) = 0;
	virtual VOID RefreshTables(UINT nControlID) = 0;
	virtual VOID RefreshTables(CONST CStringArray &szTables, UINT nControlID) = 0;
	virtual VOID RefreshTable(LPCTSTR pszTable, BOOL bAll = TRUE) = 0;
	virtual VOID RefreshTable(CTableViewObject *pTable, LPCTSTR pszValue, UINT nControlID) = 0;
	virtual VOID RecalcTable(CTableViewObject *pTable, BOOL bWidth, BOOL bAdjust, BOOL bRedraw = TRUE) = 0;
	virtual VOID RecalcTable(CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw = TRUE) = 0;
	virtual VOID RecalcTable(CONST CTableViewObjects *pTables, CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw = TRUE) = 0;
	virtual VOID RecalcTableRow(CTableViewObject *pTable, INT nRow, BOOL bRedraw = TRUE) = 0;
	virtual VOID RecalcTableRow(CONST CTableViewObjects *pTables, CTableViewObject *pTable, INT nRow, BOOL bAdjust) = 0;
	virtual VOID UpdateTableContents(CTableViewObject *pTable, CONST CStringArray &szContents) = 0;
	virtual VOID UpdateTableContents(CONST CTableViewObjects *pTables, CTableViewObject *pTable, LPCTSTR pszTable, CONST CStringArray &szContents) = 0;
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem) = 0;
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CUIntArray &nValues) = 0;
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CLongUIntArray &nValues) = 0;
	virtual BOOL LimitTableCellValues(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem) = 0;
	virtual VOID UpdateTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszValue) = 0;
	virtual VOID EnableTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszDefault, BOOL bEnable = TRUE) = 0;
	virtual BOOL IsTableRowEmpty(CONST CTableViewObject *pTable, INT nRow) CONST = 0;
	virtual BOOL IsTableRowFull(CONST CTableViewObject *pTable, INT nRow) CONST = 0;
	virtual BOOL IsSubTable(CONST CTableViewObject *pTable) CONST = 0;
public:
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CANDLayout *pLayout, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CGRDLayout *pLayout, INT nIndex, BOOL bDelete = FALSE) = 0;
	virtual VOID UpdateTableForms(CONST CPODLayout *pLayout, INT nIndex, BOOL bDelete = FALSE) = 0;
public:
	virtual VOID UpdateTables(CONST CDatabaseTMPackets &pDatabaseTMPackets) = 0;
	virtual VOID UpdateTables(CONST CDatabaseTCFunctions &pDatabaseTCFunctions) = 0;
	virtual VOID UpdateTables(CONST CDatabaseTCSequences &pDatabaseTCSequences) = 0;
	virtual VOID UpdateTables(CONST CDatabaseOBProcessors &pDatabaseOBProcessors) = 0;
	virtual VOID UpdateTables(CONST CDatabaseTMParameters &pDatabaseTMParameters) = 0;
	virtual VOID UpdateTables(CONST CDatabaseTCParameters &pDatabaseTCParameters) = 0;
	virtual VOID UpdateTables(CONST CANDLayouts &pANDLayouts) = 0;
	virtual VOID UpdateTables(CONST CGRDLayouts &pGRDLayouts) = 0;
	virtual VOID UpdateTables(CONST CPODLayouts &pPODLayouts) = 0;
	virtual BOOL UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete) = 0;
	virtual BOOL UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete) = 0;
	virtual VOID UpdateTables(ULONGLONG nComponent) = 0;
	virtual VOID UpdateTables() = 0;
public:
	virtual VOID DrawTables() = 0;
	virtual VOID DrawTables(CDC *pDC) = 0;
	virtual VOID DrawTables(CDC *pDC, CONST CTableViewObjects *pTables, BOOL bPrinting = FALSE) = 0;
	virtual VOID DrawTable(CDC *pDC, CONST CTableViewObject *pTable, BOOL bPrinting = FALSE) = 0;
public:
	virtual BOOL EnableTablesAlignment(BOOL bEnable, BOOL bRealign) = 0;
	virtual BOOL EnableTablesAlignment(BOOL bEnable) = 0;
public:
	virtual BOOL EnableUndo(BOOL bEnable = TRUE) = 0;
	virtual BOOL IsUndoing() CONST = 0;
	virtual BOOL IsRedoing() CONST = 0;
	virtual VOID ClearUndo() = 0;
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseTableView)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseProfileInfo

// Specify the database types
#define DATABASE_TYPE_NONE   0
#define DATABASE_TYPE_GLOBAL   (1<<0)
#define DATABASE_TYPE_LOCAL   (1<<1)
#define DATABASE_TYPE_SUPPORT_DBMS   (1<<2)
#define DATABASE_TYPE_STANDARD_PCM   (1<<3)
#define DATABASE_TYPE_STANDARD_CCSDS   (1<<4)
#define DATABASE_TYPE_IMPLEMENTATION_SCOS   (1<<5)
#define DATABASE_TYPE_IMPLEMENTATION_ALTEL   (1<<6)
#define DATABASE_TYPE_FLOATINGPOINTFORMAT_IEEE   (1<<7)
#define DATABASE_TYPE_FLOATINGPOINTFORMAT_USAF   (1<<8)
#define DATABASE_TYPE_FLOATINGPOINTFORMAT_DEFAULT   DATABASE_TYPE_FLOATINGPOINTFORMAT_IEEE
// Specify the database standard related identifiers
#define DATABASE_CCSDS_TIMEEPOCH   1958

class AFX_EXT_CLASS CDatabaseProfileInfo : public CDatabaseVersions
{
	// Construction
public:
	CDatabaseProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbServer;
		INT  cbStandard;
		INT  cbSpacecraft;
		INT  cbFileName[4];
		INT  cbVersions;
		INT  cbUsers;
		INT  cbPasswords;
		INT  cbPrivileges;
		INT  cbLoggingFileName;
		UINT  nLoggingRetention;
		UINT  nLoggingPolicy;
		UINT  nType;
		TIMEKEY  tTime[2];
		TIMEKEY  tValidity[2];
		TIMEKEY  tLoggingRetention;
		DWORDLONG  fLoggingRetention;
	} DATA, *PDATA, *LPDATA;
protected:
	UINT  m_nType;
	CString  m_szName;
	CString  m_szServer;
	CString  m_szStandard;
	CString  m_szSpacecraft;
	CString  m_szFileName[4];
	CStringArray  m_szUsers;
	CStringArray  m_szPasswords;
	CUIntArray  m_nPrivileges;
	CTimeKey  m_tValidity[2];
	CTimeKey  m_tTime[2];
private:
	UINT  m_nLoggingPolicy;
	UINT  m_nLoggingRetention;
	CString  m_szLoggingFileName;
	DWORDLONG  m_fLoggingRetention;
	CTimeSpan  m_tLoggingRetention;
	CLogFile  m_cLogFile;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;
	VOID SetServer(LPCTSTR pszServer);
	CString GetServer() CONST;
	VOID SetSpacecraft(LPCTSTR pszSpacecraft);
	CString GetSpacecraft() CONST;
	VOID SetImplementationStandard(LPCTSTR pszStandard);
	CString GetImplementationStandard() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetUpdateFileName(LPCTSTR pszFileName);
	CString GetUpdateFileName() CONST;
	VOID SetLibraryFileName(LPCTSTR pszFileName);
	CString GetLibraryFileName() CONST;
	VOID SetLibraryUpdateFileName(LPCTSTR pszFileName);
	CString GetLibraryUpdateFileName() CONST;
	VOID SetUsers(CONST CStringArray &szUsers, CONST CStringArray &szPasswords, CONST CUIntArray &nPrivileges);
	INT GetUsers(CStringArray &szUsers, CStringArray &szPasswords, CUIntArray &nPrivileges) CONST;
	INT GetUsers(CStringArray &szUsers) CONST;
	VOID SetCreationTime(CONST CTimeKey &tTime);
	CTimeKey GetCreationTime() CONST;
	VOID SetLastUpdateTime(CONST CTimeKey &tTime);
	CTimeKey GetLastUpdateTime() CONST;
	VOID SetValidity(CONST CTimeKey &tStartTime, CONST CTimeKey &tEndTime);
	BOOL GetValidity(CTimeKey &tStartTime, CTimeKey &tEndTime) CONST;
	BOOL SetVersion(LPCTSTR pszName, LPCTSTR pszRelease, LPCTSTR pszIssue, LPCTSTR pszComment);
	BOOL GetVersion(CString &szName, CString &szRelease, CString &szIssue, CString &szComment) CONST;

	VOID SetLoggingMode(UINT nMode);
	UINT GetLoggingMode() CONST;
	VOID SetLoggingPolicy(UINT nPolicy);
	UINT GetLoggingPolicy() CONST;
	VOID SetLoggingRetentionByItem(INT nRetention);
	UINT GetLoggingRetentionByItem() CONST;
	VOID SetLoggingRetentionBySize(DWORDLONG fRetention);
	DWORDLONG GetLoggingRetentionBySize() CONST;
	VOID SetLoggingRetentionByTime(CONST CTimeSpan &tRetention);
	CTimeSpan GetLoggingRetentionByTime() CONST;
	VOID SetLoggingFileName(LPCTSTR pszFileName);
	CString GetLoggingFileName() CONST;
	BOOL WriteLog(CONST CDatabaseLogInfo *pLogInfo);
	UINT ReadLog(CDatabaseLogs &pLogs);
	UINT ReadLog(CDatabaseLogs &pLogs, CONST CTimeKey &tStartTime, INT nCount);
	UINT ReadLog(CDatabaseLogs &pLogs, CONST CTimeKey &tStartTime, CONST CTimeKey &tEndTime);
	BOOL UpdateLog();
	BOOL ResetLog();

	BOOL Copy(CONST CDatabaseProfileInfo *pProfileInfo);
	BOOL Compare(CONST CDatabaseProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

public:
	static CString TranslateImplementationStandard(UINT nType);
	static UINT TranslateImplementationStandard(LPCTSTR pszType);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseProfiles

class AFX_EXT_CLASS CDatabaseProfiles : public CPtrArray
{
	// Construction
public:
	CDatabaseProfiles();
	~CDatabaseProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CDatabaseProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Find(LPCTSTR pszServer, LPCTSTR pszName) CONST;

	CDatabaseProfileInfo *GetAt(INT nIndex) CONST;
	CDatabaseProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CDatabaseProfiles *pProfiles);
	BOOL Compare(CONST CDatabaseProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszServer, LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CBinaryDatabase

// Specify the database property identifiers
#define DATABASE_PROPERTY_NONE   MAKEDATABASEPROPERTYCODE(0)
#define DATABASE_PROPERTY_VERSION   MAKEDATABASEPROPERTYCODE(1<<0)
// Specify the database component identifiers
#define DATABASE_COMPONENT_NONE   MAKEDATABASECOMPONENTCODE(0,0)
#define DATABASE_COMPONENT_TMPACKET   MAKEDATABASECOMPONENTCODE(1<<0,0)
#define DATABASE_COMPONENT_TCFUNCTION   MAKEDATABASECOMPONENTCODE(1<<1,0)
#define DATABASE_COMPONENT_TCSEQUENCE   MAKEDATABASECOMPONENTCODE(1<<2,0)
#define DATABASE_COMPONENT_TCPROCEDURE   MAKEDATABASECOMPONENTCODE(1<<3,0)
#define DATABASE_COMPONENT_OBPROCESSOR   MAKEDATABASECOMPONENTCODE(1<<4,0)
#define DATABASE_COMPONENT_TMPARAMETER   MAKEDATABASECOMPONENTCODE(1<<5,0)
#define DATABASE_COMPONENT_TCPARAMETER   MAKEDATABASECOMPONENTCODE(1<<6,0)
#define DATABASE_COMPONENT_AND   MAKEDATABASECOMPONENTCODE(1<<7,0)
#define DATABASE_COMPONENT_GRD   MAKEDATABASECOMPONENTCODE(1<<8,0)
#define DATABASE_COMPONENT_MMD   MAKEDATABASECOMPONENTCODE(1<<9,0)
#define DATABASE_COMPONENT_POD   MAKEDATABASECOMPONENTCODE(1<<10,0)
#define DATABASE_COMPONENT_SCRIPT   MAKEDATABASECOMPONENTCODE(1<<11,0)
#define DATABASE_COMPONENTS_ANY   MAKEDATABASECOMPONENTCODE(1<<12,0)
#define DATABASE_COMPONENTS_ALL   (DATABASE_COMPONENT_TMPACKET | DATABASE_COMPONENT_TCFUNCTION | DATABASE_COMPONENT_TCSEQUENCE | DATABASE_COMPONENT_TCPROCEDURE | DATABASE_COMPONENT_OBPROCESSOR | DATABASE_COMPONENT_TMPARAMETER | DATABASE_COMPONENT_TCPARAMETER | DATABASE_COMPONENT_AND | DATABASE_COMPONENT_GRD | DATABASE_COMPONENT_MMD | DATABASE_COMPONENT_POD | DATABASE_COMPONENT_SCRIPT)
// Specify the database sub-component identifiers
#define DATABASE_SUBCOMPONENT_NONE   MAKEDATABASECOMPONENTCODE(0,0)
#define DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION   MAKEDATABASECOMPONENTCODE(0,1<<0)
#define DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION   MAKEDATABASECOMPONENTCODE(0,1<<1)
#define DATABASE_SUBCOMPONENT_TMPACKETHEADER   MAKEDATABASECOMPONENTCODE(0,1<<2)
#define DATABASE_SUBCOMPONENT_TMPACKETSTREAM   MAKEDATABASECOMPONENTCODE(0,1<<3)
#define DATABASE_SUBCOMPONENT_TMPACKETGROUP   MAKEDATABASECOMPONENTCODE(0,1<<4)
#define DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET   MAKEDATABASECOMPONENTCODE(0,1<<5)
#define DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER   MAKEDATABASECOMPONENTCODE(0,1<<6)
#define DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP   MAKEDATABASECOMPONENTCODE(0,1<<7)
#define DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE   MAKEDATABASECOMPONENTCODE(0,1<<8)
#define DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP   MAKEDATABASECOMPONENTCODE(0,1<<9)
#define DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK   MAKEDATABASECOMPONENTCODE(0,1<<10)
#define DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH   MAKEDATABASECOMPONENTCODE(0,1<<11)
#define DATABASE_SUBCOMPONENT_TCPARAMETERSET   MAKEDATABASECOMPONENTCODE(0,1<<12)
#define DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET   MAKEDATABASECOMPONENTCODE(0,1<<13)
#define DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE   MAKEDATABASECOMPONENTCODE(0,1<<14)
#define DATABASE_SUBCOMPONENT_TMPARAMETERGROUP   MAKEDATABASECOMPONENTCODE(0,1<<15)
#define DATABASE_SUBCOMPONENT_TMNUMCALTABLE   MAKEDATABASECOMPONENTCODE(0,1<<16)
#define DATABASE_SUBCOMPONENT_TMTXTCALTABLE   MAKEDATABASECOMPONENTCODE(0,1<<17)
#define DATABASE_SUBCOMPONENT_TMNUMOOLTABLE   MAKEDATABASECOMPONENTCODE(0,1<<18)
#define DATABASE_SUBCOMPONENT_TMTXTOOLTABLE   MAKEDATABASECOMPONENTCODE(0,1<<19)
#define DATABASE_SUBCOMPONENT_TCNUMCALTABLE   MAKEDATABASECOMPONENTCODE(0,1<<20)
#define DATABASE_SUBCOMPONENT_TCTXTCALTABLE   MAKEDATABASECOMPONENTCODE(0,1<<21)
#define DATABASE_SUBCOMPONENT_TCNUMOOLTABLE   MAKEDATABASECOMPONENTCODE(0,1<<22)
#define DATABASE_SUBCOMPONENT_TCTXTOOLTABLE   MAKEDATABASECOMPONENTCODE(0,1<<23)
#define DATABASE_SUBCOMPONENT_AND_NORMAL   MAKEDATABASECOMPONENTCODE(0,1<<24)
#define DATABASE_SUBCOMPONENT_AND_GENERIC   MAKEDATABASECOMPONENTCODE(0,1<<25)
#define DATABASE_SUBCOMPONENTS_ALL   (DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION | DATABASE_SUBCOMPONENT_TMPACKETHEADER | DATABASE_SUBCOMPONENT_TMPACKETSTREAM | DATABASE_SUBCOMPONENT_TMPACKETGROUP | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH | DATABASE_SUBCOMPONENT_TCPARAMETERSET | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP | DATABASE_SUBCOMPONENT_TMNUMCALTABLE | DATABASE_SUBCOMPONENT_TMTXTCALTABLE | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE | DATABASE_SUBCOMPONENT_TCNUMCALTABLE | DATABASE_SUBCOMPONENT_TCTXTCALTABLE | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE | DATABASE_SUBCOMPONENT_AND_NORMAL | DATABASE_SUBCOMPONENT_AND_GENERIC)
// Specify the database property and component code related macros
#define MAKEDATABASEPROPERTYCODE(id)   (((ULONGLONG) (id)) & 0x00000001)
#define MAKEDATABASECOMPONENTCODE(component,subcomponent)   (((((ULONGLONG) (component)) & 0xEFFFFFFF) << 1) | ((((ULONGLONG) (subcomponent)) & 0x0FFFFFFF) << 32))
#define MAKEDATABASECOMPONENTINDEXEDCODE(code,index)   ((code) | (((ULONGLONG) ((index) & 0x0000000F)) << 60))
#define DATABASEPROPERTYFROMCODE(code)   (((ULONGLONG) (code)) & 0x00000001)
#define DATABASECOMPONENTFROMCODE(code)   (((ULONGLONG) (code)) & (ULONGLONG) 0x00000000FFFFFFFE)
#define DATABASESUBCOMPONENTFROMCODE(code)   (((ULONGLONG) (code)) & (ULONGLONG) 0x0FFFFFFF00000000)
#define DATABASESUBCOMPONENTINDEXFROMCODE(code)   ((((ULONGLONG) (code)) & (ULONGLONG) 0xF000000000000000) >> 60)
// Specify the database related privileges
#define DATABASE_PRIVILEGE_USERS_CHANGE   (1<<0)
#define DATABASE_PRIVILEGE_VALIDITY_CHANGE   (1<<1)
#define DATABASE_PRIVILEGE_VERSION_CHANGE   (1<<2)
#define DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE   (1<<3)
#define DATABASE_PRIVILEGE_COMPILEOPTIONS_CHANGE   (1<<4)
#define DATABASE_PRIVILEGE_TMPACKET_CHANGE   (1<<5)
#define DATABASE_PRIVILEGE_TCFUNCTION_CHANGE   (1<<6)
#define DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE   (1<<7)
#define DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE   (1<<8)
#define DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE   (1<<9)
#define DATABASE_PRIVILEGE_TMPARAMETER_CHANGE   (1<<10)
#define DATABASE_PRIVILEGE_TCPARAMETER_CHANGE   (1<<11)
#define DATABASE_PRIVILEGE_AND_CHANGE   (1<<12)
#define DATABASE_PRIVILEGE_GRD_CHANGE   (1<<13)
#define DATABASE_PRIVILEGE_HEX_CHANGE   (1<<14)
#define DATABASE_PRIVILEGE_OOL_CHANGE   (1<<15)
#define DATABASE_PRIVILEGE_MMD_CHANGE   (1<<16)
#define DATABASE_PRIVILEGE_POD_CHANGE   (1<<17)
#define DATABASE_PRIVILEGE_SCRIPT_CHANGE   (1<<18)
#define DATABASE_PRIVILEGE_LOGFILES_CHANGE   (1<<19)
#define DATABASE_PRIVILEGE_COMPILE   (1<<20)
#define DATABASE_PRIVILEGE_DELETE   (1<<21)
#define DATABASE_PRIVILEGES_ALL   (DATABASE_PRIVILEGE_USERS_CHANGE | DATABASE_PRIVILEGE_VALIDITY_CHANGE | DATABASE_PRIVILEGE_VERSION_CHANGE | DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE | DATABASE_PRIVILEGE_COMPILEOPTIONS_CHANGE | DATABASE_PRIVILEGE_TMPACKET_CHANGE | DATABASE_PRIVILEGE_TCFUNCTION_CHANGE | DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE | DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE | DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE | DATABASE_PRIVILEGE_TMPARAMETER_CHANGE | DATABASE_PRIVILEGE_TCPARAMETER_CHANGE | DATABASE_PRIVILEGE_AND_CHANGE | DATABASE_PRIVILEGE_GRD_CHANGE | DATABASE_PRIVILEGE_HEX_CHANGE | DATABASE_PRIVILEGE_OOL_CHANGE | DATABASE_PRIVILEGE_MMD_CHANGE | DATABASE_PRIVILEGE_POD_CHANGE | DATABASE_PRIVILEGE_SCRIPT_CHANGE | DATABASE_PRIVILEGE_LOGFILES_CHANGE | DATABASE_PRIVILEGE_COMPILE | DATABASE_PRIVILEGE_DELETE)

class AFX_EXT_CLASS CBinaryDatabase : public CDatabaseProfileInfo
{
	// Construction
public:
	CBinaryDatabase();
	CBinaryDatabase(CDatabaseProfileInfo *pDatabaseInfo);
	~CBinaryDatabase();

	// Attributes
private:
	typedef struct tagDATABASEHEADER {
		DWORD  dwSize;
		DWORD  dwHeader[2];
		DWORD  dwTMPackets[2];
		DWORD  dwTCPackets[2];
		DWORD  dwTCFunctions[2];
		DWORD  dwTCSequences[2];
		DWORD  dwTCProcedures[2];
		DWORD  dwOBProcessors[2];
		DWORD  dwTMParameters[2];
		DWORD  dwTCParameters[2];
		DWORD  dwTMNumCalTables[2];
		DWORD  dwTMTxtCalTables[2];
		DWORD  dwTMNumOolTables[2];
		DWORD  dwTMTxtOolTables[2];
		DWORD  dwTCNumCalTables[2];
		DWORD  dwTCTxtCalTables[2];
		DWORD  dwTCNumOolTables[2];
		DWORD  dwTCTxtOolTables[2];
		DWORD  dwTCPreExeGroups[2];
		DWORD  dwTCExeVerGroups[2];
		DWORD  dwTMPacketGroups[2];
		DWORD  dwTMPacketHeaders[2];
		DWORD  dwTMPacketStreams[2];
		DWORD  dwTCParameterSets[2];
		DWORD  dwTCFunctionBlocks[2];
		DWORD  dwTMParameterGroups[2];
		DWORD  dwTCPacketParameters[2];
		DWORD  dwTMPacketIdentifications[2];
		DWORD  dwTMPacketIdentificationCriteria[2];
		DWORD  dwOBProcessorMemoryImages[2];
		DWORD  dwTMPacketSubTags[2];
		DWORD  dwANDDirectory[2][2];
		DWORD  dwGRDDirectory[2];
		DWORD  dwMMDDirectory[2];
		DWORD  dwPODDirectory[2];
		DWORD  dwScriptsDirectory[2];
		DWORD  dwANDs[2][2];
		DWORD  dwGRDs[2];
		DWORD  dwMMDs[2];
		DWORD  dwPODs[2];
		DWORD  dwScripts[2];
	} DATABASEHEADER, *PDATABASEHEADER, *LPDATABASEHEADER;
private:
	CDatabaseTMPackets  *m_pTMPackets;
	CDatabaseTCPackets  *m_pTCPackets;
	CDatabaseTCFunctions  *m_pTCFunctions;
	CDatabaseTCSequences  *m_pTCSequences;
	CDatabaseTCProcedures  *m_pTCProcedures;
	CDatabaseOBProcessors  *m_pOBProcessors;
	CDatabaseTMParameters  *m_pTMParameters;
	CDatabaseTCParameters  *m_pTCParameters;
	CDatabaseTMNumCalTables  *m_pTMNumCalTables;
	CDatabaseTMTxtCalTables  *m_pTMTxtCalTables;
	CDatabaseTMNumOolTables  *m_pTMNumOolTables;
	CDatabaseTMTxtOolTables  *m_pTMTxtOolTables;
	CDatabaseTCNumCalTables  *m_pTCNumCalTables;
	CDatabaseTCTxtCalTables  *m_pTCTxtCalTables;
	CDatabaseTCNumOolTables  *m_pTCNumOolTables;
	CDatabaseTCTxtOolTables  *m_pTCTxtOolTables;
	CDatabaseTCPreExeGroups  *m_pTCPreExeGroups;
	CDatabaseTCExeVerGroups  *m_pTCExeVerGroups;
	CDatabaseTMPacketGroups  *m_pTMPacketGroups;
	CDatabaseTMPacketHeaders  *m_pTMPacketHeaders;
	CDatabaseTMPacketStreams  *m_pTMPacketStreams;
	CDatabaseTCParameterSets  *m_pTCParameterSets;
	CDatabaseTCFunctionBlocks  *m_pTCFunctionBlocks;
	CDatabaseTMParameterGroups  *m_pTMParameterGroups;
	CDatabaseTCPacketParameters  *m_pTCPacketParameters;
	CDatabaseTMPacketIdentifications  *m_pTMPacketIdentifications;
	CDatabaseTMPacketIdentificationCriteria  *m_pTMPacketIdentificationCriteria;
	CDatabaseOBProcessorMemoryImages  *m_pOBProcessorMemoryImages;
private:
	CDatabaseTMPacket  *m_pTMPacketSubTags;
private:
	CANDLayouts  *m_pANDs[2];
	CGRDLayouts  *m_pGRDs;
	CMMDLayouts  *m_pMMDs;
	CPODLayouts  *m_pPODs;
	CAutomationScripts  *m_pScripts;
private:
	HINSTANCE  m_hLibrary;

	// Operations
public:
	BOOL Save(ULONGLONG nComponents = DATABASE_COMPONENTS_ALL | DATABASE_SUBCOMPONENTS_ALL);
	UINT Load(ULONGLONG nComponents = DATABASE_COMPONENTS_ALL | DATABASE_SUBCOMPONENTS_ALL, BOOL bAll = TRUE);

	BOOL Attach(CONST CDatabaseProfileInfo *pDatabaseInfo);
	BOOL Update(CONST CDatabaseProfileInfo *pDatabaseInfo);
	BOOL Copy(CONST CDatabaseProfileInfo *pDatabaseInfo);
	BOOL Copy(CONST CBinaryDatabase *pDatabase);
	VOID Detach();
	BOOL Delete();

	BOOL LoadLibrary(CStringArray &szErrors);
	HINSTANCE GetLibrary() CONST;
	VOID FreeLibrary();

	BOOL IsInitialized() CONST;
	BOOL IsLocal() CONST;
	BOOL IsValid() CONST;

	VOID Reset();

public:
	INT EnumANDs(CANDLayouts &pLayouts, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL, BOOL bDirectory = TRUE) CONST;
	INT EnumGRDs(CGRDLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	INT EnumMMDs(CMMDLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	INT EnumPODs(CPODLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	INT EnumScripts(CAutomationScripts &pScripts, BOOL bDirectory = TRUE) CONST;
	INT EnumProcedures(CDatabaseTCProcedures &pProcedures) CONST;
	BOOL LoadAND(LPCTSTR pszName, CANDLayout &cLayout, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL) CONST;
	BOOL LoadGRD(LPCTSTR pszName, CGRDLayout &cLayout) CONST;
	BOOL LoadMMD(LPCTSTR pszName, CMMDLayout &cLayout) CONST;
	BOOL LoadPOD(LPCTSTR pszName, CPODLayout &cLayout) CONST;
	BOOL LoadScript(LPCTSTR pszName, CAutomationScript &cScript) CONST;
	INT SaveAND(CONST CANDLayout &cLayout, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL);
	INT SaveGRD(CONST CGRDLayout &cLayout);
	INT SaveMMD(CONST CMMDLayout &cLayout);
	INT SavePOD(CONST CPODLayout &cLayout);
	INT SaveScript(CONST CAutomationScript &cScript);
	INT DeleteAND(CONST CANDLayout &cLayout, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL);
	INT DeleteGRD(CONST CGRDLayout &cLayout);
	INT DeleteMMD(CONST CMMDLayout &cLayout);
	INT DeletePOD(CONST CPODLayout &cLayout);
	INT DeleteScript(CONST CAutomationScript &cScript);

	CDatabaseTMPackets *GetTMPackets() CONST;
	CDatabaseTCPackets *GetTCPackets() CONST;
	CDatabaseTCFunctions *GetTCFunctions() CONST;
	CDatabaseTCSequences *GetTCSequences() CONST;
	CDatabaseTCProcedures *GetTCProcedures() CONST;
	CDatabaseOBProcessors *GetOBProcessors() CONST;
	CDatabaseTMParameters *GetTMParameters() CONST;
	CDatabaseTCParameters *GetTCParameters() CONST;
	CDatabaseTMNumCalTables *GetTMNumCalTables() CONST;
	CDatabaseTMTxtCalTables *GetTMTxtCalTables() CONST;
	CDatabaseTMNumOolTables *GetTMNumOolTables() CONST;
	CDatabaseTMTxtOolTables *GetTMTxtOolTables() CONST;
	CDatabaseTCNumCalTables *GetTCNumCalTables() CONST;
	CDatabaseTCTxtCalTables *GetTCTxtCalTables() CONST;
	CDatabaseTCNumOolTables *GetTCNumOolTables() CONST;
	CDatabaseTCTxtOolTables *GetTCTxtOolTables() CONST;
	CDatabaseTCPreExeGroups *GetTCPreExeGroups() CONST;
	CDatabaseTCExeVerGroups *GetTCExeVerGroups() CONST;
	CDatabaseTMPacketGroups *GetTMPacketGroups() CONST;
	CDatabaseTMPacketHeaders *GetTMPacketHeaders() CONST;
	CDatabaseTMPacketStreams *GetTMPacketStreams() CONST;
	CDatabaseTCParameterSets *GetTCParameterSets() CONST;
	CDatabaseTCFunctionBlocks *GetTCFunctionBlocks() CONST;
	CDatabaseTMParameterGroups *GetTMParameterGroups() CONST;
	CDatabaseTCPacketParameters *GetTCPacketParameters() CONST;
	CDatabaseTMPacketIdentifications *GetTMPacketIdentifications() CONST;
	CDatabaseTMPacketIdentificationCriteria *GetTMPacketIdentificationCriteria() CONST;
	CDatabaseOBProcessorMemoryImages *GetOBProcessorMemoryImages() CONST;
	CDatabaseTMPacket *GetTMPacketSubTags() CONST;

	CANDLayouts *GetANDs(ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL) CONST;
	CGRDLayouts *GetGRDs() CONST;
	CMMDLayouts *GetMMDs() CONST;
	CPODLayouts *GetPODs() CONST;
	CAutomationScripts *GetScripts() CONST;

public:
	static BOOL SecureDirectoryOrFile(LPCTSTR pszDirectoryOrFile);

protected:
	CString GetSaveFileName() CONST;
	CString GetLoadFileName() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseEngine

typedef BOOL(CALLBACK *DATABASEHELPBYTOPICPROC)(LPCTSTR pszTopic);
typedef BOOL(CALLBACK *DATABASEMESSAGESBYIDPROC)(CONST EVENT_DESCRIPTOR nMessageID);
typedef BOOL(CALLBACK *DATABASEMESSAGESBYTEXTPROC)(LPCTSTR pszMessage, BOOL bAudition);
typedef BOOL(CALLBACK *DATABASECOMPAREMESSAGESPROC)(LPCTSTR pszName, LPCTSTR pszComparedName, ULONGLONG nComponent, LPCTSTR pszMessage);
typedef BOOL(CALLBACK *DATABASECOMPILEMESSAGESPROC)(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszMessage, BOOL bWarning, BOOL bTimestamp, BOOL bAudition);

class AFX_EXT_CLASS CDatabaseEngine : public CBinaryDatabase
{
	// Construction
public:
	CDatabaseEngine();
	~CDatabaseEngine();

	// Attributes
protected:
	CString  m_szDatabaseEngine;
	HINSTANCE  m_hDatabaseEngine;
	CDatabaseEngine  *m_pDatabaseEngine;
	CDatabase  *m_pDatabase;
	CString  m_szDatabase;
protected:
	UINT  m_nDBMSCount;
protected:
	BOOL  m_bReloaded;

protected:
	DATABASEHELPBYTOPICPROC  m_pDatabaseHelpTopicProc;
	DATABASEMESSAGESBYIDPROC  m_pDatabaseMessagesIDProc;
	DATABASEMESSAGESBYTEXTPROC  m_pDatabaseMessagesTextProc;
	DATABASECOMPAREMESSAGESPROC  m_pDatabaseCompareMessagesProc;
	DATABASECOMPILEMESSAGESPROC  m_pDatabaseCompileMessagesProc;
	BOOL  m_bDatabaseComparing[2];
	BOOL  m_bDatabaseCompiling[2];

	// Operations
public:
	BOOL Open(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, BOOL bLoad = TRUE, BOOL bBinary = TRUE);
	BOOL Open(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, LPCTSTR pszDBMS, BOOL bLoad = TRUE, BOOL bBinary = TRUE);
	BOOL Initialize(DATABASEMESSAGESBYIDPROC pMessagesIDProc, DATABASEMESSAGESBYTEXTPROC pMessagesTextProc, DATABASEHELPBYTOPICPROC pHelpTopicProc);
	BOOL IsOpen() CONST;
	VOID Close();

	BOOL OpenDBMS(DWORD dwOptions);
	BOOL CloseDBMS();

	CString GetName() CONST;

public:
	virtual BOOL Save();
	virtual BOOL Save(ULONGLONG nComponents);
	virtual BOOL Load();
	virtual UINT Load(ULONGLONG nComponents, BOOL bAll = TRUE);

	virtual BOOL Save(CONST CDatabaseVersion *pDatabaseVersion);
	virtual BOOL Save(CONST CDatabaseTMPacket *pDatabaseTMPacket);
	virtual BOOL Save(CONST CDatabaseTCPacket *pDatabaseTCPacket);
	virtual BOOL Save(CONST CDatabaseTCFunction *pDatabaseTCFunction);
	virtual BOOL Save(CONST CDatabaseTCSequence *pDatabaseTCSequence);
	virtual BOOL Save(CONST CDatabaseOBProcessor *pDatabaseOBProcessor);
	virtual INT Save(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	virtual BOOL Save(CONST CDatabaseTMParameter *pDatabaseTMParameter);
	virtual BOOL Save(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	virtual BOOL Save(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable);
	virtual BOOL Save(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable);
	virtual BOOL Save(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable);
	virtual BOOL Save(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable);
	virtual BOOL Save(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable);
	virtual BOOL Save(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable);
	virtual BOOL Save(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable);
	virtual BOOL Save(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable);
	virtual BOOL Save(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup);
	virtual BOOL Save(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup);
	virtual BOOL Save(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup);
	virtual BOOL Save(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);
	virtual BOOL Save(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);
	virtual BOOL Save(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);
	virtual BOOL Save(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock);
	virtual BOOL Save(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup);
	virtual BOOL Save(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter);
	virtual BOOL Save(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification);
	virtual BOOL Save(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion);
	virtual BOOL Save(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage);
	virtual BOOL Save(CONST CANDLayout *pANDLayout);
	virtual BOOL Save(CONST CGRDLayout *pGRDLayout);
	virtual BOOL Save(CONST CPODLayout *pPODLayout);
	virtual BOOL Flush(CONST CDatabaseVersions *pDatabaseVersions, BOOL bDelete = FALSE);
	virtual BOOL Flush(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
	virtual BOOL Clean(CONST CDatabaseTMPacketIdentifications *pDatabaseTMPacketIdentifications);
	virtual BOOL Delete(CONST CDatabaseVersion *pDatabaseVersion);
	virtual BOOL Delete(CONST CDatabaseTMPacket *pDatabaseTMPacket);
	virtual BOOL Delete(CONST CDatabaseTCPacket *pDatabaseTCPacket);
	virtual BOOL Delete(CONST CDatabaseTCFunction *pDatabaseTCFunction);
	virtual BOOL Delete(CONST CDatabaseTCSequence *pDatabaseTCSequence);
	virtual BOOL Delete(CONST CDatabaseOBProcessor *pDatabaseOBProcessor);
	virtual INT Delete(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	virtual BOOL Delete(CONST CDatabaseTMParameter *pDatabaseTMParameter);
	virtual BOOL Delete(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	virtual BOOL Delete(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable);
	virtual BOOL Delete(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable);
	virtual BOOL Delete(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable);
	virtual BOOL Delete(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable);
	virtual BOOL Delete(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable);
	virtual BOOL Delete(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable);
	virtual BOOL Delete(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable);
	virtual BOOL Delete(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable);
	virtual BOOL Delete(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup);
	virtual BOOL Delete(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup);
	virtual BOOL Delete(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup);
	virtual BOOL Delete(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);
	virtual BOOL Delete(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);
	virtual BOOL Delete(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);
	virtual BOOL Delete(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock);
	virtual BOOL Delete(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup);
	virtual BOOL Delete(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter);
	virtual BOOL Delete(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification);
	virtual BOOL Delete(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion);
	virtual BOOL Delete(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage);
	virtual BOOL Delete(CONST CANDLayout *pANDLayout);
	virtual BOOL Delete(CONST CGRDLayout *pGRDLayout);
	virtual BOOL Delete(CONST CPODLayout *pPODLayout);

	virtual BOOL Compare(CONST CDatabaseEngine *pDatabase, DATABASECOMPAREMESSAGESPROC pCompareMessagesProc, ULONGLONG nComponents = DATABASE_COMPONENTS_ALL | DATABASE_SUBCOMPONENTS_ALL);
	virtual BOOL IsComparing() CONST;
	virtual BOOL StopComparing();

	virtual BOOL Compile(CBinaryDatabase *pDatabase, DATABASECOMPILEMESSAGESPROC pCompileMessagesProc, ULONGLONG nComponents = DATABASE_COMPONENTS_ALL | DATABASE_SUBCOMPONENTS_ALL);
	virtual BOOL IsCompiling() CONST;
	virtual BOOL StopCompiling();

	virtual BOOL LoadLibrary(CStringArray &szErrors);
	virtual HINSTANCE GetLibrary() CONST;
	virtual VOID FreeLibrary();

	virtual BOOL IsVersioningSupported() CONST;

	virtual BOOL IsInitialized() CONST;
	virtual BOOL IsLocal() CONST;
	virtual BOOL IsValid() CONST;

	virtual VOID Reset();

public:
	virtual INT EnumTCSequences(LPCTSTR pszXmlCode, CDatabaseTCSequences &pDatabaseTCSequences) CONST;

	virtual INT EnumANDs(CANDLayouts &pLayouts, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumANDs(LPCTSTR pszXmlCode, CANDLayouts &pLayouts) CONST;
	virtual INT EnumGRDs(CGRDLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumGRDs(LPCTSTR pszXmlCode, CGRDLayouts &pLayouts) CONST;
	virtual INT EnumMMDs(CMMDLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumPODs(CPODLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumPODs(LPCTSTR pszXmlCode, CPODLayouts &pLayouts) CONST;
	virtual INT EnumScripts(CAutomationScripts &pScripts, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumProcedures(CDatabaseTCProcedures &pProcedures) CONST;
	virtual INT SaveAND(CONST CANDLayout &cLayout, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL);
	virtual INT SaveGRD(CONST CGRDLayout &cLayout);
	virtual INT SaveMMD(CONST CMMDLayout &cLayout);
	virtual INT SavePOD(CONST CPODLayout &cLayout);
	virtual INT SaveScript(CONST CAutomationScript &cScript);
	virtual BOOL LoadAND(LPCTSTR pszName, CANDLayout &cLayout, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL) CONST;
	virtual BOOL LoadGRD(LPCTSTR pszName, CGRDLayout &cLayout) CONST;
	virtual BOOL LoadMMD(LPCTSTR pszName, CMMDLayout &cLayout) CONST;
	virtual BOOL LoadPOD(LPCTSTR pszName, CPODLayout &cLayout) CONST;
	virtual BOOL LoadScript(LPCTSTR pszName, CAutomationScript &cScript) CONST;
	virtual INT DeleteAND(CONST CANDLayout &cLayout, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL);
	virtual INT DeleteGRD(CONST CGRDLayout &cLayout);
	virtual INT DeleteMMD(CONST CMMDLayout &cLayout);
	virtual INT DeletePOD(CONST CPODLayout &cLayout);
	virtual INT DeleteScript(CONST CAutomationScript &cScript);

	virtual CDatabaseTMPackets *GetTMPackets() CONST;
	virtual CDatabaseTCPackets *GetTCPackets() CONST;
	virtual CDatabaseTCFunctions *GetTCFunctions() CONST;
	virtual CDatabaseTCSequences *GetTCSequences() CONST;
	virtual CDatabaseTCProcedures *GetTCProcedures() CONST;
	virtual CDatabaseOBProcessors *GetOBProcessors() CONST;
	virtual CDatabaseTMParameters *GetTMParameters() CONST;
	virtual CDatabaseTCParameters *GetTCParameters() CONST;
	virtual CDatabaseTMNumCalTables *GetTMNumCalTables() CONST;
	virtual CDatabaseTMTxtCalTables *GetTMTxtCalTables() CONST;
	virtual CDatabaseTMNumOolTables *GetTMNumOolTables() CONST;
	virtual CDatabaseTMTxtOolTables *GetTMTxtOolTables() CONST;
	virtual CDatabaseTCNumCalTables *GetTCNumCalTables() CONST;
	virtual CDatabaseTCTxtCalTables *GetTCTxtCalTables() CONST;
	virtual CDatabaseTCNumOolTables *GetTCNumOolTables() CONST;
	virtual CDatabaseTCTxtOolTables *GetTCTxtOolTables() CONST;
	virtual CDatabaseTCPreExeGroups *GetTCPreExeGroups() CONST;
	virtual CDatabaseTCExeVerGroups *GetTCExeVerGroups() CONST;
	virtual CDatabaseTMPacketGroups *GetTMPacketGroups() CONST;
	virtual CDatabaseTMPacketHeaders *GetTMPacketHeaders() CONST;
	virtual CDatabaseTMPacketStreams *GetTMPacketStreams() CONST;
	virtual CDatabaseTCParameterSets *GetTCParameterSets() CONST;
	virtual CDatabaseTCFunctionBlocks *GetTCFunctionBlocks() CONST;
	virtual CDatabaseTMParameterGroups *GetTMParameterGroups() CONST;
	virtual CDatabaseTCPacketParameters *GetTCPacketParameters() CONST;
	virtual CDatabaseTMPacketIdentifications *GetTMPacketIdentifications() CONST;
	virtual CDatabaseTMPacketIdentificationCriteria *GetTMPacketIdentificationCriteria() CONST;
	virtual CDatabaseOBProcessorMemoryImages *GetOBProcessorMemoryImages() CONST;
	virtual CDatabaseTMPacket *GetTMPacketSubTags() CONST;

	virtual CANDLayouts *GetANDs(ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL) CONST;
	virtual CGRDLayouts *GetGRDs() CONST;
	virtual CMMDLayouts *GetMMDs() CONST;
	virtual CPODLayouts *GetPODs() CONST;
	virtual CAutomationScripts *GetScripts() CONST;

public:
	virtual BOOL DeleteTMPacket(LPCTSTR pszTag);
	virtual BOOL DeleteTCPacket(LPCTSTR pszTag);
	virtual BOOL DeleteTCFunction(LPCTSTR pszName);
	virtual BOOL DeleteTCSequence(LPCTSTR pszName);
	virtual BOOL DeleteOBProcessor(LPCTSTR pszName);
	virtual INT DeleteTCProcedure(LPCTSTR pszName);
	virtual BOOL DeleteTMParameter(LPCTSTR pszTag);
	virtual BOOL DeleteTMNumCalTable(LPCTSTR pszName);
	virtual BOOL DeleteTMTxtCalTable(LPCTSTR pszName);
	virtual BOOL DeleteTMNumOolTable(LPCTSTR pszName);
	virtual BOOL DeleteTMTxtOolTable(LPCTSTR pszName);
	virtual BOOL DeleteTCParameter(LPCTSTR pszTag);
	virtual BOOL DeleteTCNumCalTable(LPCTSTR pszName);
	virtual BOOL DeleteTCTxtCalTable(LPCTSTR pszName);
	virtual BOOL DeleteTCNumOolTable(LPCTSTR pszName);
	virtual BOOL DeleteTCTxtOolTable(LPCTSTR pszName);
	virtual BOOL DeleteTCPreExeGroup(LPCTSTR pszID);
	virtual BOOL DeleteTCExeVerStage(LPCTSTR pszID);
	virtual BOOL DeleteTCExeVerGroup(LPCTSTR pszID);
	virtual BOOL DeleteTMPacketGroup(LPCTSTR pszName);
	virtual BOOL DeleteTMPacketHeader(LPCTSTR pszName);
	virtual BOOL DeleteTMPacketStream(LPCTSTR pszName);
	virtual BOOL DeleteTCParameterSet(LPCTSTR pszName);
	virtual BOOL DeleteTCFunctionBlock(LPCTSTR pszName);
	virtual BOOL DeleteTMParameterGroup(LPCTSTR pszName);
	virtual BOOL DeleteTCPacketParameter(LPCTSTR pszTag);
	virtual BOOL DeleteTCParameterValueSet(LPCTSTR pszName);
	virtual BOOL DeleteTCFunctionRoutingPath(INT nID);
	virtual BOOL DeleteTMPacketIdentification(LPCTSTR pszName);
	virtual BOOL DeleteTMPacketIdentificationCriterion(LPCTSTR pszName);
	virtual BOOL DeleteOBProcessorMemoryImage(LPCTSTR pszName);
	virtual BOOL DeleteAND(LPCTSTR pszName);
	virtual BOOL DeleteGRD(LPCTSTR pszName);
	virtual BOOL DeletePOD(LPCTSTR pszName);

public:
	virtual BOOL CheckVersionName(LPCTSTR pszName) CONST;
	virtual INT GetVersionNameLength() CONST;
	virtual BOOL CheckVersionComment(LPCTSTR pszComment) CONST;
	virtual INT GetVersionCommentLength() CONST;
	virtual BOOL CheckVersionDomain(LPCTSTR pszDomain) CONST;
	virtual INT GetVersionDomainLength() CONST;
	virtual INT TranslateVersionDomain(LPCTSTR pszDomain) CONST;
	virtual CString TranslateVersionDomain(INT nDomain) CONST;
	virtual BOOL CheckVersionRelease(LPCTSTR pszRelease) CONST;
	virtual INT GetVersionReleaseLength() CONST;
	virtual INT TranslateVersionRelease(LPCTSTR pszRelease) CONST;
	virtual CString TranslateVersionRelease(INT nRelease) CONST;
	virtual BOOL CheckVersionIssue(LPCTSTR pszIssue) CONST;
	virtual INT GetVersionIssueLength() CONST;
	virtual INT TranslateVersionIssue(LPCTSTR pszIssue) CONST;
	virtual CString TranslateVersionIssue(INT nIssue) CONST;

	virtual BOOL CheckTMPacketTag(LPCTSTR pszTag) CONST;
	virtual INT GetTMPacketTagLength() CONST;
	virtual CString GetTMPacketSubTag() CONST;
	virtual CString GetTMPacketDummyTag() CONST;
	virtual BOOL CheckTMPacketID(UINT nID) CONST;
	virtual BOOL GetTMPacketIDRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTMPacketType(INT nType) CONST;
	virtual INT GetTMPacketTypeLength() CONST;
	virtual BOOL GetTMPacketTypeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMPacketType(LPCTSTR pszType) CONST;
	virtual CString TranslateTMPacketType(INT nType) CONST;
	virtual BOOL CheckTMPacketSubType(INT nSubType) CONST;
	virtual BOOL GetTMPacketSubTypeRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMPacketDescriptionLength() CONST;
	virtual BOOL CheckTMPacketDetails(LPCTSTR pszDetails) CONST;
	virtual INT GetTMPacketDetailsLength() CONST;
	virtual BOOL CheckTMPacketSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTMPacketSubSystemLength() CONST;
	virtual INT EnumTMPacketDataFieldHeaderFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual INT TranslateTMPacketDataFieldHeaderFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketDataFieldHeaderFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketDataFieldHeader(INT bPresent) CONST;
	virtual BOOL CheckTMPacketDataFieldHeaderName(LPCTSTR pszName) CONST;
	virtual INT GetTMPacketDataFieldHeaderNameLength() CONST;
	virtual INT EnumTMPacketAPIDs(CStringArray &szAPIDs, CUIntArray &nAPIDs) CONST;
	virtual BOOL CheckTMPacketAPID(LPCTSTR pszTag, INT nAPID) CONST;
	virtual BOOL CheckTMPacketAPID(INT nAPID) CONST;
	virtual INT GetTMPacketAPIDLength() CONST;
	virtual BOOL GetTMPacketAPIDRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMPacketAPID(LPCTSTR pszAPID, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketAPID(INT nAPID, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketTMTypes(CStringArray &szTMTypes, CUIntArray &nTMTypes) CONST;
	virtual BOOL CheckTMPacketTMType(INT nTMType) CONST;
	virtual INT GetTMPacketTMTypeLength() CONST;
	virtual INT TranslateTMPacketTMType(LPCTSTR pszTMType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketTMType(INT nTMType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketTMID(INT nTMID) CONST;
	virtual INT GetTMPacketTMIDLength() CONST;
	virtual BOOL GetTMPacketTMIDRange(UINT &nLow, UINT &nHigh) CONST;
	virtual INT TranslateTMPacketTMID(LPCTSTR pszTMID, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketTMID(INT nTMID, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacket3Disc(INT n3Disc) CONST;
	virtual INT GetTMPacket3DiscLength() CONST;
	virtual BOOL GetTMPacket3DiscRange(UINT &nLow, UINT &nHigh) CONST;
	virtual INT TranslateTMPacket3Disc(LPCTSTR psz3Disc, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacket3Disc(INT n3Disc, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketFirstFieldOffset(INT nOffset) CONST;
	virtual BOOL GetTMPacketFirstFieldOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketFirstFieldWidth(INT nWidth) CONST;
	virtual BOOL GetTMPacketFirstFieldWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketFirstFieldValue(INT nValue) CONST;
	virtual BOOL GetTMPacketFirstFieldValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketSecondFieldOffset(INT nOffset) CONST;
	virtual BOOL GetTMPacketSecondFieldOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketSecondFieldWidth(INT nWidth) CONST;
	virtual BOOL GetTMPacketSecondFieldWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketSecondFieldValue(INT nValue) CONST;
	virtual BOOL GetTMPacketSecondFieldValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketDataFieldHeaderSize(INT nSize) CONST;
	virtual BOOL GetTMPacketDataFieldHeaderSizeRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketContentID(INT nID) CONST;
	virtual BOOL GetTMPacketContentIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketTransmissionRate(INT nType, INT nInterval) CONST;
	virtual BOOL GetTMPacketTransmissionRateRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketTransmissionRetries(INT nRetries) CONST;
	virtual INT GetTMPacketTransmissionRetriesLength() CONST;
	virtual BOOL GetTMPacketTransmissionRetriesRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMPacketTransmissionRetries(LPCTSTR pszRetries) CONST;
	virtual CString TranslateTMPacketTransmissionRetries(INT nRetries) CONST;
	virtual INT EnumTMPacketTimestampFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketTimestampFlag(LPCTSTR pszFlag) CONST;
	virtual INT GetTMPacketTimestampFlagLength() CONST;
	virtual INT TranslateTMPacketTimestampFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketTimestampFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketVirtualChannel(INT nAPID, INT nChannelID) CONST;
	virtual BOOL GetTMPacketVirtualChannelRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTMPacketEventTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTMPacketEventType(UINT nType) CONST;
	virtual INT GetTMPacketEventTypeLength() CONST;
	virtual INT TranslateTMPacketEventType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketEventType(INT nType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketEventID(INT nType, LPCTSTR pszEventID) CONST;
	virtual BOOL CheckTMPacketEventID(LPCTSTR pszEventID) CONST;
	virtual INT GetTMPacketEventIDLength() CONST;
	virtual INT EnumTMPacketCyclicRedundancyCheckFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketCyclicRedundancyCheckFlag(INT nFlag) CONST;
	virtual INT GetTMPacketCyclicRedundancyCheckFlagLength() CONST;
	virtual INT TranslateTMPacketCyclicRedundancyCheckFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketCyclicRedundancyCheckFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketIdentificationValidityFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketIdentificationValidityFlag(LPCTSTR pszFlag) CONST;
	virtual INT GetTMPacketIdentificationValidityFlagLength() CONST;
	virtual INT TranslateTMPacketIdentificationValidityFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketIdentificationValidityFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketDataSizes(CStringArray &szSizes, CUIntArray &nSizes) CONST;
	virtual BOOL CheckTMPacketDataSize(INT cbData, INT nFlag) CONST;
	virtual BOOL GetTMPacketDataSizeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMPacketDataSize(LPCTSTR pszSize, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketDataSize(INT nSize, BOOL bDBMS = TRUE) CONST;
	virtual INT GetTMPacketDataSize() CONST;
	virtual INT GetTMPacketDataFieldHeaderSize() CONST;
	virtual INT GetTMPacketTotalSize() CONST;
	virtual INT EnumTMPacketStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMPacketStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMPacketStatusLength() CONST;
	virtual INT TranslateTMPacketStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketHeaderName(LPCTSTR pszName) CONST;
	virtual INT GetTMPacketHeaderNameLength() CONST;
	virtual INT EnumTMPacketHeaderTMTypeFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual INT TranslateTMPacketHeaderTMTypeFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketHeaderTMTypeFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketHeaderTMTypePosition(INT nByte, INT nBit, INT nLength) CONST;
	virtual BOOL GetTMPacketHeaderTMTypePositionRange(INT &nOffsetLow, INT &nOffsetHigh, INT &nLengthLow, INT &nLengthHigh) CONST;
	virtual INT EnumTMPacketHeaderTMIDFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual INT TranslateTMPacketHeaderTMIDFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketHeaderTMIDFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketHeaderTMIDPosition(INT nByte, INT nBit, INT nLength) CONST;
	virtual BOOL GetTMPacketHeaderTMIDPositionRange(INT &nOffsetLow, INT &nOffsetHigh, INT &nLengthLow, INT &nLengthHigh) CONST;
	virtual INT EnumTMPacketHeader3DiscFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual INT TranslateTMPacketHeader3DiscFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketHeader3DiscFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketHeader3DiscPosition(INT nByte, INT nBit, INT nLength) CONST;
	virtual BOOL GetTMPacketHeader3DiscPositionRange(INT &nOffsetLow, INT &nOffsetHigh, INT &nLengthLow, INT &nLengthHigh) CONST;
	virtual INT EnumTMPacketHeaderTimestampFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual INT TranslateTMPacketHeaderTimestampFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketHeaderTimestampFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketHeaderTimestampPosition(INT nByte, INT nBit, INT nLength) CONST;
	virtual BOOL GetTMPacketHeaderTimestampPositionRange(INT &nOffsetLow, INT &nOffsetHigh, INT &nLengthLow, INT &nLengthHigh) CONST;
	virtual BOOL CheckTMPacketParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTMPacketParameterTagLength() CONST;
	virtual BOOL CheckTMPacketParameterDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMPacketParameterDescriptionLength() CONST;
	virtual BOOL CheckTMPacketParameterSequenceNumber(INT nNumber) CONST;
	virtual BOOL GetTMPacketParameterSequenceNumberRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterGroupSize(INT nSize) CONST;
	virtual BOOL GetTMPacketParameterGroupSizeRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterGroupRepetitionCount(INT nCount) CONST;
	virtual BOOL GetTMPacketParameterGroupRepetitionCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTMPacketParameterChoiceFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketParameterChoiceFlag(UINT nFlag) CONST;
	virtual INT GetTMPacketParameterChoiceFlagLength() CONST;
	virtual UINT TranslateTMPacketParameterChoiceFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketParameterChoiceFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketParameterOnBoardIDFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketParameterOnBoardIDFlag(UINT nFlag) CONST;
	virtual INT GetTMPacketParameterOnBoardIDFlagLength() CONST;
	virtual UINT TranslateTMPacketParameterOnBoardIDFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketParameterOnBoardIDFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketParameterBytePosition(INT nByte) CONST;
	virtual BOOL GetTMPacketParameterBytePositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterBitPosition(INT nBit) CONST;
	virtual BOOL GetTMPacketParameterBitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterWidth(INT nWidth) CONST;
	virtual BOOL GetTMPacketParameterWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOffset(INT nOffset) CONST;
	virtual BOOL GetTMPacketParameterOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOccurrence(INT nOccurrence) CONST;
	virtual BOOL GetTMPacketParameterOccurrenceRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOccurrenceCount(INT nCount) CONST;
	virtual BOOL GetTMPacketParameterOccurrenceCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOccurrenceInterval(INT nOccurrence, INT nInterval) CONST;
	virtual BOOL GetTMPacketParameterOccurrenceIntervalRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOccurrenceTimeOffset(INT nOffset) CONST;
	virtual BOOL GetTMPacketParameterOccurrenceTimeOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOccurrenceTimeInterval(INT nOccurrence, INT nInterval) CONST;
	virtual BOOL GetTMPacketParameterOccurrenceTimeIntervalRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterValidity(LPCTSTR pszTag) CONST;
	virtual INT GetTMPacketParameterValidityLength() CONST;
	virtual INT EnumTMPacketParameterDisplayColumnsFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketParameterDisplayColumnsFlag(UINT nFlag) CONST;
	virtual INT GetTMPacketParameterDisplayColumnsFlagRange(UINT &nLow, UINT &nHigh) CONST;
	virtual UINT TranslateTMPacketParameterDisplayColumnsFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketParameterDisplayColumnsFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketParameterDisplayAlignmentFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketParameterDisplayAlignmentFlag(UINT nFlag) CONST;
	virtual INT GetTMPacketParameterDisplayAlignmentFlagLength() CONST;
	virtual UINT TranslateTMPacketParameterDisplayAlignmentFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketParameterDisplayAlignmentFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketParameterDisplayNewLineFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketParameterDisplayNewLineFlag(UINT nFlag) CONST;
	virtual INT GetTMPacketParameterDisplayNewLineFlagLength() CONST;
	virtual UINT TranslateTMPacketParameterDisplayNewLineFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketParameterDisplayNewLineFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketParameterDisplayFormatFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketParameterDisplayFormatFlag(UINT nFlag) CONST;
	virtual INT GetTMPacketParameterDisplayFormatFlagLength() CONST;
	virtual UINT TranslateTMPacketParameterDisplayFormatFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketParameterDisplayFormatFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketStreamName(LPCTSTR pszName) CONST;
	virtual INT GetTMPacketStreamNameLength() CONST;
	virtual INT EnumTMPacketStreamAPIDs(CStringArray &szAPIDs, CUIntArray &nAPIDs) CONST;
	virtual BOOL CheckTMPacketStreamAPID(INT nAPID) CONST;
	virtual INT GetTMPacketStreamAPIDLength() CONST;
	virtual INT TranslateTMPacketStreamAPID(LPCTSTR pszAPID, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketStreamAPID(INT nAPID, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketStreamTMID(INT nTMID) CONST;
	virtual INT GetTMPacketStreamTMIDLength() CONST;
	virtual BOOL GetTMPacketStreamTMIDRange(UINT &nLow, UINT &nHigh) CONST;
	virtual INT TranslateTMPacketStreamTMID(LPCTSTR pszTMID, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketStreamTMID(INT nTMID, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketStreamPeriod(INT nPeriod) CONST;
	virtual BOOL GetTMPacketStreamPeriodRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketStreamTimeout(INT nTimeout) CONST;
	virtual BOOL GetTMPacketStreamTimeoutRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketStreamValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMPacketStreamValidityParameterLength() CONST;
	virtual BOOL CheckTMPacketStreamValidityValue(INT nValue) CONST;
	virtual BOOL GetTMPacketStreamValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketGroupName(LPCTSTR pszName) CONST;
	virtual INT GetTMPacketGroupNameLength() CONST;
	virtual BOOL CheckTMPacketGroupDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMPacketGroupDescriptionLength() CONST;
	virtual BOOL CheckTMPacketGroupType(LPCTSTR pszType) CONST;
	virtual INT GetTMPacketGroupTypeLength() CONST;
	virtual INT TranslateTMPacketGroupType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketGroupType(INT nType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketGroupMember(UINT nID) CONST;

	virtual BOOL CheckTCPacketTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCPacketTagLength() CONST;
	virtual BOOL CheckTCPacketType(INT nType) CONST;
	virtual INT GetTCPacketTypeLength() CONST;
	virtual INT TranslateTCPacketType(LPCTSTR pszType) CONST;
	virtual CString TranslateTCPacketType(INT nType) CONST;
	virtual BOOL CheckTCPacketDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCPacketDescriptionLength() CONST;
	virtual BOOL CheckTCPacketDetails(LPCTSTR pszDetails) CONST;
	virtual INT GetTCPacketDetailsLength() CONST;
	virtual INT EnumTCPacketDataFieldHeaderFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual INT TranslateTCPacketDataFieldHeaderFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketDataFieldHeaderFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCPacketDataFieldHeader(INT bPresent) CONST;
	virtual INT EnumTCPacketAPIDs(CStringArray &szAPIDs, CUIntArray &nAPIDs) CONST;
	virtual BOOL CheckTCPacketAPID(INT nAPID) CONST;
	virtual INT GetTCPacketAPIDLength() CONST;
	virtual INT TranslateTCPacketAPID(LPCTSTR pszAPID, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketAPID(INT nAPID, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCPacketDataSizes(CStringArray &szSizes, CUIntArray &nSizes) CONST;
	virtual BOOL GetTCPacketDataSizeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCPacketDataSize(LPCTSTR pszSize, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketDataSize(INT nSize, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCPacketDataSize(ULONGLONG nAttributes, INT nFlag, INT cbData) CONST;
	virtual INT GetTCPacketDataSize() CONST;
	virtual INT GetTCPacketDataFieldHeaderSize() CONST;
	virtual INT GetTCPacketTotalSize() CONST;
	virtual INT EnumTCPacketStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCPacketStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCPacketStatusLength() CONST;
	virtual INT TranslateTCPacketStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCPacketParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCPacketParameterTagLength() CONST;
	virtual BOOL CheckTCPacketParameterDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCPacketParameterDescriptionLength() CONST;
	virtual INT EnumTCPacketParameterTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCPacketParameterType(LPCTSTR pszTag, ULONGLONG nType) CONST;
	virtual INT GetTCPacketParameterTypeLength() CONST;
	virtual ULONGLONG TranslateTCPacketParameterType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketParameterType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCPacketParameterValueInterpretations(CStringArray &szInterpretations, CLongUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCPacketParameterValueInterpretation(ULONGLONG nAttributes, ULONGLONG nInterpretation) CONST;
	virtual INT GetTCPacketParameterValueInterpretationLength() CONST;
	virtual ULONGLONG TranslateTCPacketParameterValueInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketParameterValueInterpretation(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCPacketParameterValueCodings(CStringArray &szCodings, CLongUIntArray &nCodings) CONST;
	virtual BOOL CheckTCPacketParameterValueCoding(ULONGLONG nAttributes, ULONGLONG nCoding) CONST;
	virtual INT GetTCPacketParameterValueCodingLength() CONST;
	virtual ULONGLONG TranslateTCPacketParameterValueCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketParameterValueCoding(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCPacketParameterValueRadixes(CStringArray &szRadixes, CLongUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCPacketParameterValueRadix(ULONGLONG nAttributes, ULONGLONG nRadix) CONST;
	virtual INT GetTCPacketParameterValueRadixLength() CONST;
	virtual ULONGLONG TranslateTCPacketParameterValueRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketParameterValueRadix(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCPacketParameterValueBitWidth(INT nWidth) CONST;
	virtual BOOL GetTCPacketParameterValueBitWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCPacketParameterValueBitOffset(INT nOffset) CONST;
	virtual BOOL GetTCPacketParameterValueBitOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCPacketParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCPacketParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTCPacketParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCPacketParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCPacketParameterConstTimeType(LPCTSTR pszTag) CONST;
	virtual BOOL CheckTCPacketParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCPacketParameterConstTimeLength() CONST;
	virtual CTimeTag TranslateTCPacketParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;

	virtual BOOL CheckTCFunctionName(LPCTSTR pszName) CONST;
	virtual INT GetTCFunctionNameLength() CONST;
	virtual BOOL CheckTCFunctionDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCFunctionDescriptionLength() CONST;
	virtual BOOL CheckTCFunctionExtendedDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCFunctionExtendedDescriptionLength() CONST;
	virtual BOOL CheckTCFunctionDetails(LPCTSTR pszDetails) CONST;
	virtual INT GetTCFunctionDetailsLength() CONST;
	virtual INT EnumTCFunctionTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCFunctionType(ULONGLONG nType) CONST;
	virtual INT GetTCFunctionTypeLength() CONST;
	virtual ULONGLONG TranslateTCFunctionType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionAPID(INT nAPID) CONST;
	virtual BOOL GetTCFunctionAPIDRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCFunctionTCTypes(CStringArray &szTCTypes, CLongUIntArray &nTCTypes) CONST;
	virtual BOOL CheckTCFunctionTCType(ULONGLONG nTCType) CONST;
	virtual BOOL GetTCFunctionTCTypeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT GetTCFunctionTCTypeLength() CONST;
	virtual ULONGLONG TranslateTCFunctionTCType(LPCTSTR pszTCType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionTCType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionTCID(INT nTCID) CONST;
	virtual BOOL GetTCFunctionTCIDRange(INT &nLow, INT &nHigh) CONST;
	virtual INT GetTCFunctionTCIDLength() CONST;
	virtual INT TranslateTCFunctionTCID(LPCTSTR pszTCID) CONST;
	virtual CString TranslateTCFunctionTCID(INT nTCID) CONST;
	virtual BOOL CheckTCFunctionMapID(INT nMapID) CONST;
	virtual BOOL GetTCFunctionMapIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionPacketTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCFunctionPacketTagLength() CONST;
	virtual INT EnumTCFunctionExecutionFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCFunctionExecutionFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCFunctionExecutionFlagLength() CONST;
	virtual ULONGLONG TranslateTCFunctionExecutionFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionExecutionFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCFunctionPriorityFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCFunctionPriorityFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCFunctionPriorityFlagLength() CONST;
	virtual ULONGLONG TranslateTCFunctionPriorityFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionPriorityFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCFunctionHazardousFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCFunctionHazardousFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCFunctionHazardousFlagLength() CONST;
	virtual ULONGLONG TranslateTCFunctionHazardousFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionHazardousFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCFunctionPlanningFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCFunctionPlanningFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCFunctionPlanningFlagLength() CONST;
	virtual ULONGLONG TranslateTCFunctionPlanningFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionPlanningFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionAcknowledgementFlags(INT nFlags) CONST;
	virtual BOOL GetTCFunctionAcknowledgementFlagsRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCFunctionInterlockScopes(CStringArray &szScopes, CLongUIntArray &nScopes) CONST;
	virtual BOOL CheckTCFunctionInterlockScope(ULONGLONG nScope) CONST;
	virtual INT GetTCFunctionInterlockScopeLength() CONST;
	virtual ULONGLONG TranslateTCFunctionInterlockScope(LPCTSTR pszScope, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionInterlockScope(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCFunctionInterlockStages(CStringArray &szStages, CLongUIntArray &nStages) CONST;
	virtual BOOL CheckTCFunctionInterlockStage(ULONGLONG nAttributes, ULONGLONG nStage) CONST;
	virtual INT GetTCFunctionInterlockStageLength() CONST;
	virtual ULONGLONG TranslateTCFunctionInterlockStage(LPCTSTR pszStage, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionInterlockStage(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionRouteAndDestinationPath(LPCTSTR pszPath) CONST;
	virtual INT GetTCFunctionRouteAndDestinationPathLength() CONST;
	virtual BOOL CheckTCFunctionRouterEquipment(LPCTSTR pszEquipment) CONST;
	virtual INT GetTCFunctionRouterEquipmentLength() CONST;
	virtual BOOL CheckTCFunctionRouterSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTCFunctionRouterSubSystemLength() CONST;
	virtual BOOL CheckTCFunctionDestinationEquipment(LPCTSTR pszEquipment) CONST;
	virtual INT GetTCFunctionDestinationEquipmentLength() CONST;
	virtual BOOL CheckTCFunctionDestinationSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTCFunctionDestinationSubSystemLength() CONST;
	virtual BOOL CheckTCFunctionDestinationSubSystemID(INT nSubSystemID) CONST;
	virtual BOOL GetTCFunctionDestinationSubSystemIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionDestinationSubSchedule(LPCTSTR pszSubSchedule) CONST;
	virtual INT GetTCFunctionDestinationSubScheduleLength() CONST;
	virtual BOOL CheckTCFunctionDestinationSubScheduleID(INT nSubScheduleID) CONST;
	virtual BOOL GetTCFunctionDestinationSubScheduleIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionOperationalInfo(LPCTSTR pszInfo) CONST;
	virtual INT GetTCFunctionOperationalInfoLength() CONST;
	virtual BOOL CheckTCFunctionValidityConditions(LPCTSTR pszConditions) CONST;
	virtual INT GetTCFunctionValidityConditionsLength() CONST;
	virtual BOOL CheckTCFunctionAssociatedTelecommands(LPCTSTR pszTelecommands) CONST;
	virtual INT GetTCFunctionAssociatedTelecommandsLength() CONST;
	virtual BOOL CheckTCFunctionComplementaryTelecommands(LPCTSTR pszTelecommands) CONST;
	virtual INT GetTCFunctionComplementaryTelecommandsLength() CONST;
	virtual BOOL CheckTCFunctionDefaultParameterSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCFunctionDefaultParameterSetNameLength() CONST;
	virtual BOOL CheckTCFunctionMissionPlannerEvent(LPCTSTR pszEvent) CONST;
	virtual INT GetTCFunctionMissionPlannerEventLength() CONST;
	virtual BOOL CheckTCFunctionPreExeGroup(LPCTSTR pszGroup) CONST;
	virtual INT GetTCFunctionPreExeGroupLength() CONST;
	virtual BOOL CheckTCFunctionExeVerGroup(LPCTSTR pszGroup) CONST;
	virtual INT GetTCFunctionExeVerGroupLength() CONST;
	virtual INT EnumTCFunctionStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCFunctionStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCFunctionStatusLength() CONST;
	virtual INT TranslateTCFunctionStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionElementName(LPCTSTR pszName) CONST;
	virtual INT GetTCFunctionElementNameLength() CONST;
	virtual BOOL CheckTCFunctionElementDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCFunctionElementDescriptionLength() CONST;
	virtual INT EnumTCFunctionElementTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCFunctionElementType(LPCTSTR pszName, ULONGLONG nType) CONST;
	virtual INT GetTCFunctionElementTypeLength() CONST;
	virtual ULONGLONG TranslateTCFunctionElementType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionElementType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionElementGroupSize(INT nSize) CONST;
	virtual BOOL GetTCFunctionElementGroupSizeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCFunctionElementValueInterpretations(CStringArray &szInterpretations, CLongUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCFunctionElementValueInterpretation(ULONGLONG nAttributes, ULONGLONG nInterpretation) CONST;
	virtual INT GetTCFunctionElementValueInterpretationLength() CONST;
	virtual ULONGLONG TranslateTCFunctionElementValueInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionElementValueInterpretation(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCFunctionElementValueRadixes(CStringArray &szRadixes, CLongUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCFunctionElementValueRadix(ULONGLONG nAttributes, ULONGLONG nRadix) CONST;
	virtual INT GetTCFunctionElementValueRadixLength() CONST;
	virtual ULONGLONG TranslateTCFunctionElementValueRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionElementValueRadix(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionElementValueBitWidth(INT nWidth) CONST;
	virtual BOOL GetTCFunctionElementValueBitWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionElementValueBitOffset(INT nOffset) CONST;
	virtual BOOL GetTCFunctionElementValueBitOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionElementConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCFunctionElementConstValueLength() CONST;
	virtual ULONGLONG TranslateTCFunctionElementConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCFunctionElementConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCFunctionElementConstValueSource(LPCTSTR pszParameter) CONST;
	virtual INT GetTCFunctionElementConstValueSourceLength() CONST;
	virtual BOOL CheckTCFunctionElementConstTimeType(LPCTSTR pszName) CONST;
	virtual BOOL CheckTCFunctionElementConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCFunctionElementConstTimeLength() CONST;
	virtual CTimeTag TranslateTCFunctionElementConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual BOOL CheckTCFunctionBlockName(LPCTSTR pszName) CONST;
	virtual INT GetTCFunctionBlockNameLength() CONST;
	virtual INT EnumTCFunctionBlockInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCFunctionBlockInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCFunctionBlockInterpretationLength() CONST;
	virtual UINT TranslateTCFunctionBlockInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionBlockInterpretation(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionBlockByteOffset(INT nOffset) CONST;
	virtual BOOL GetTCFunctionBlockByteOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionBlockMaxLength(INT nLength) CONST;
	virtual BOOL GetTCFunctionBlockMaxLengthRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCFunctionBlockStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCFunctionBlockStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCFunctionBlockStatusLength() CONST;
	virtual INT TranslateTCFunctionBlockStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionBlockStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionBlockElementName(LPCTSTR pszName) CONST;
	virtual INT GetTCFunctionBlockElementNameLength() CONST;
	virtual INT EnumTCFunctionBlockElementInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCFunctionBlockElementInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCFunctionBlockElementInterpretationLength() CONST;
	virtual UINT TranslateTCFunctionBlockElementInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionBlockElementInterpretation(UINT nAttributes, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCSequenceName(LPCTSTR pszName) CONST;
	virtual INT GetTCSequenceNameLength() CONST;
	virtual BOOL CheckTCSequenceDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCSequenceDescriptionLength() CONST;
	virtual BOOL CheckTCSequenceDetails(LPCTSTR pszDetails) CONST;
	virtual INT GetTCSequenceDetailsLength() CONST;
	virtual INT EnumTCSequenceTimeTaggedFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceTimeTaggedFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceTimeTaggedFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceTimeTaggedFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceTimeTaggedFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceHazardousFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceHazardousFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceHazardousFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceHazardousFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceHazardousFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequencePlanningFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequencePlanningFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCSequencePlanningFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequencePlanningFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequencePlanningFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceExecutionFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceExecutionFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceExecutionFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceExecutionFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceExecutionFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceSubSystemID(INT nSubSystemID) CONST;
	virtual BOOL GetTCSequenceSubSystemIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceSubScheduleID(INT nSubScheduleID) CONST;
	virtual BOOL GetTCSequenceSubScheduleIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceSubScheduleDestination(LPCTSTR pszSubSchedule) CONST;
	virtual INT GetTCSequenceSubScheduleDestinationLength() CONST;
	virtual BOOL CheckTCSequenceDefaultParameterSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCSequenceDefaultParameterSetNameLength() CONST;
	virtual BOOL CheckTCSequenceMissionPlannerEvent(LPCTSTR pszEvent) CONST;
	virtual INT GetTCSequenceMissionPlannerEventLength() CONST;
	virtual BOOL CheckTCSequenceUserName(LPCTSTR pszUserName) CONST;
	virtual INT GetTCSequenceUserNameLength() CONST;
	virtual BOOL CheckTCSequenceDate(LPCTSTR pszDate, LPCTSTR pszFormat) CONST;
	virtual INT GetTCSequenceDateLength() CONST;
	virtual CTimeKey TranslateTCSequenceDate(LPCTSTR pszDate, LPCTSTR pszFormat) CONST;
	virtual CString TranslateTCSequenceDate(CONST CTimeKey &tDate, LPCTSTR pszFormat) CONST;
	virtual BOOL CheckTCSequenceDocumentName(LPCTSTR pszDocumentName) CONST;
	virtual INT GetTCSequenceDocumentNameLength() CONST;
	virtual BOOL CheckTCSequenceDocumentIssue(LPCTSTR pszDocumentIssue) CONST;
	virtual INT GetTCSequenceDocumentIssueLength() CONST;
	virtual BOOL CheckTCSequenceDocumentDate(LPCTSTR pszDate, LPCTSTR pszFormat) CONST;
	virtual INT GetTCSequenceDocumentDateLength() CONST;
	virtual CTimeKey TranslateTCSequenceDocumentDate(LPCTSTR pszDate, LPCTSTR pszFormat) CONST;
	virtual CString TranslateTCSequenceDocumentDate(CONST CTimeKey &tDate, LPCTSTR pszFormat) CONST;
	virtual BOOL CheckTCSequenceEntryCount(INT nCount) CONST;
	virtual BOOL GetTCSequenceEntryCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceParameterCount(INT nCount) CONST;
	virtual BOOL GetTCSequenceParameterCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCSequenceStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCSequenceStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCSequenceStatusLength() CONST;
	virtual INT TranslateTCSequenceStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCSequenceParameterTagLength() CONST;
	virtual BOOL CheckTCSequenceParameterDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCSequenceParameterDescriptionLength() CONST;
	virtual BOOL CheckTCSequenceParameterUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTCSequenceParameterUnitLength() CONST;
	virtual BOOL CheckTCSequenceParameterPosition(INT nPosition) CONST;
	virtual BOOL GetTCSequenceParameterPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCSequenceParameterTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCSequenceParameterType(ULONGLONG nType) CONST;
	virtual INT GetTCSequenceParameterTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceParameterCategories(CStringArray &szCategories, CLongUIntArray &nCategories) CONST;
	virtual BOOL CheckTCSequenceParameterCategory(ULONGLONG nCategory) CONST;
	virtual INT GetTCSequenceParameterCategoryLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterCategory(LPCTSTR pszCategory, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterCategory(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceParameterTypeCodes(CStringArray &szPTCs, CUIntArray &nPTCs) CONST;
	virtual BOOL CheckTCSequenceParameterTypeCode(INT nPTC) CONST;
	virtual BOOL GetTCSequenceParameterTypeCodeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCSequenceParameterTypeCode(LPCTSTR pszPTC) CONST;
	virtual CString TranslateTCSequenceParameterTypeCode(INT nPTC, INT nPFC) CONST;
	virtual INT EnumTCSequenceParameterFormatCodes(LPCTSTR pszPTC, CStringArray &szPFCs, CUIntArray &nPFCs) CONST;
	virtual BOOL CheckTCSequenceParameterFormatCode(INT nPTC, INT nPFC) CONST;
	virtual BOOL GetTCSequenceParameterFormatCodeRange(INT nPTC, INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCSequenceParameterFormatCode(LPCTSTR pszPFC) CONST;
	virtual CString TranslateTCSequenceParameterFormatCode(INT nPTC, INT nPFC) CONST;
	virtual INT EnumTCSequenceParameterDisplayFormats(CStringArray &szFormats, CLongUIntArray &nFormats) CONST;
	virtual INT EnumTCSequenceParameterDisplayFormats(ULONGLONG nAttributes, CStringArray &szFormats, CLongUIntArray &nFormats) CONST;
	virtual BOOL CheckTCSequenceParameterDisplayFormat(ULONGLONG nAttributes, ULONGLONG nFormat) CONST;
	virtual INT GetTCSequenceParameterDisplayFormatLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterDisplayFormat(LPCTSTR pszFormat, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterDisplayFormat(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceParameterCodings(CStringArray &szCodings, CLongUIntArray &nCodings) CONST;
	virtual BOOL CheckTCSequenceParameterCoding(ULONGLONG nAttributes, ULONGLONG nCoding) CONST;
	virtual INT GetTCSequenceParameterCodingLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterCoding(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceParameterValueTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCSequenceParameterValueType(ULONGLONG nAttributes, ULONGLONG nType) CONST;
	virtual INT GetTCSequenceParameterValueTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterValueType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterValueType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceParameterValueRadixes(CStringArray &szRadixes, CLongUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCSequenceParameterValueRadix(ULONGLONG nAttributes, ULONGLONG nRadix) CONST;
	virtual INT GetTCSequenceParameterValueRadixLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterValueRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterValueRadix(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceParameterBitWidth(INT nWidth) CONST;
	virtual BOOL GetTCSequenceParameterBitWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceParameterCalTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCSequenceParameterCalTableLength() CONST;
	virtual BOOL CheckTCSequenceParameterOolTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCSequenceParameterOolTableLength() CONST;
	virtual BOOL CheckTCSequenceParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCSequenceParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCSequenceParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCSequenceParameterConstTimeType(LPCTSTR pszTag) CONST;
	virtual BOOL CheckTCSequenceParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCSequenceParameterConstTimeLength() CONST;
	virtual CTimeTag TranslateTCSequenceParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual BOOL CheckTCSequenceEntryName(LPCTSTR pszName) CONST;
	virtual INT GetTCSequenceEntryNameLength() CONST;
	virtual BOOL CheckTCSequenceEntryDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCSequenceEntryDescriptionLength() CONST;
	virtual INT EnumTCSequenceEntryTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCSequenceEntryType(ULONGLONG nType) CONST;
	virtual INT GetTCSequenceEntryTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntrySubTypes(CStringArray &szSubTypes, CLongUIntArray &nSubTypes) CONST;
	virtual BOOL CheckTCSequenceEntrySubType(ULONGLONG nSubType) CONST;
	virtual INT GetTCSequenceEntrySubTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntrySubType(LPCTSTR pszSubType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntrySubType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceEntryIndex(INT nIndex) CONST;
	virtual BOOL GetTCSequenceEntryIndexRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceEntry1Step(LPCTSTR psz1Step) CONST;
	virtual INT GetTCSequenceEntry1StepLength() CONST;
	virtual INT EnumTCSequenceEntryDispatchModes(CStringArray &szModes, CLongUIntArray &nModes) CONST;
	virtual BOOL CheckTCSequenceEntryDispatchMode(ULONGLONG nAttributes, ULONGLONG nMode) CONST;
	virtual INT GetTCSequenceEntryDispatchModeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryDispatchMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryDispatchMode(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryReleaseTimeTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCSequenceEntryReleaseTimeType(ULONGLONG nAttributes, ULONGLONG nType) CONST;
	virtual INT GetTCSequenceEntryReleaseTimeTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryReleaseTimeType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryReleaseTimeType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceEntryReleaseDeltaTime(ULONGLONG nAttributes, LPCTSTR pszDelta, LPCTSTR pszFormat) CONST;
	virtual INT GetTCSequenceEntryReleaseDeltaTimeLength() CONST;
	virtual DWORD TranslateTCSequenceEntryReleaseDeltaTime(LPCTSTR pszDelta, LPCTSTR pszFormat) CONST;
	virtual CString TranslateTCSequenceEntryReleaseDeltaTime(DWORD dwDelta, LPCTSTR pszFormat) CONST;
	virtual INT EnumTCSequenceEntryExecutionTimeTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCSequenceEntryExecutionTimeType(ULONGLONG nAttributes, ULONGLONG nType) CONST;
	virtual INT GetTCSequenceEntryExecutionTimeTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryExecutionTimeType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryExecutionTimeType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceEntryExecutionTime(LPCTSTR pszTime, LPCTSTR pszFormat) CONST;
	virtual INT GetTCSequenceEntryExecutionTimeLength() CONST;
	virtual CTimeTag TranslateTCSequenceEntryExecutionTime(LPCTSTR pszTime, LPCTSTR pszFormat) CONST;
	virtual CString TranslateTCSequenceEntryExecutionTime(CONST CTimeTag &tTime, LPCTSTR pszFormat) CONST;
	virtual BOOL CheckTCSequenceEntryExecutionDeltaTime(LPCTSTR pszDelta, LPCTSTR pszFormat) CONST;
	virtual INT GetTCSequenceEntryExecutionDeltaTimeLength() CONST;
	virtual DWORD TranslateTCSequenceEntryExecutionDeltaTime(LPCTSTR pszDelta, BOOL &bEarlier, LPCTSTR pszFormat) CONST;
	virtual CString TranslateTCSequenceEntryExecutionDeltaTime(DWORD dwDelta, BOOL bEarlier, LPCTSTR pszFormat) CONST;
	virtual INT EnumTCSequenceEntryGroupFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceEntryGroupFlag(ULONGLONG nAttributes, ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceEntryGroupFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryGroupFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryGroupFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryBlockFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceEntryBlockFlag(ULONGLONG nAttributes, ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceEntryBlockFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryBlockFlag(LPCTSTR pszFlag, LPCTSTR pszMember, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryBlockFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceEntryBlockMembership(LPCTSTR pszMember) CONST;
	virtual INT GetTCSequenceEntryBlockMembershipLength() CONST;
	virtual INT TranslateTCSequenceEntryBlockMembership(LPCTSTR pszMember) CONST;
	virtual CString TranslateTCSequenceEntryBlockMembership(INT nMember) CONST;
	virtual INT EnumTCSequenceEntryInterlockScopes(CStringArray &szScopes, CLongUIntArray &nScopes) CONST;
	virtual BOOL CheckTCSequenceEntryInterlockScope(ULONGLONG nAttributes, ULONGLONG nScope) CONST;
	virtual INT GetTCSequenceEntryInterlockScopeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryInterlockScope(LPCTSTR pszScope, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryInterlockScope(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryInterlockStages(CStringArray &szStages, CLongUIntArray &nStages) CONST;
	virtual BOOL CheckTCSequenceEntryInterlockStage(ULONGLONG nAttributes, ULONGLONG nStage) CONST;
	virtual INT GetTCSequenceEntryInterlockStageLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryInterlockStage(LPCTSTR pszStage, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryInterlockStage(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryPTVCheckFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceEntryPTVCheckFlag(ULONGLONG nAttributes, ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceEntryPTVCheckFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryPTVCheckFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryPTVCheckFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryPEVCheckFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceEntryPEVCheckFlag(ULONGLONG nAttributes, ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceEntryPEVCheckFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryPEVCheckFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryPEVCheckFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryCEVCheckFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceEntryCEVCheckFlag(ULONGLONG nAttributes, ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceEntryCEVCheckFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryCEVCheckFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryCEVCheckFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceEntryParameterCount(INT nCount) CONST;
	virtual BOOL GetTCSequenceEntryParameterCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceEntryParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCSequenceEntryParameterTagLength() CONST;
	virtual BOOL CheckTCSequenceEntryParameterComment(LPCTSTR pszTag) CONST;
	virtual INT GetTCSequenceEntryParameterCommentLength() CONST;
	virtual BOOL CheckTCSequenceEntryParameterPosition(INT nPosition) CONST;
	virtual BOOL GetTCSequenceEntryParameterPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCSequenceEntryParameterModificationFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCSequenceEntryParameterModificationFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCSequenceEntryParameterModificationFlagLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryParameterModificationFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryParameterModificationFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryParameterValueTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCSequenceEntryParameterValueType(ULONGLONG nType) CONST;
	virtual INT GetTCSequenceEntryParameterValueTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryParameterValueType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryParameterValueType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceEntryParameterValueRadixes(CStringArray &szRadixes, CLongUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCSequenceEntryParameterValueRadix(ULONGLONG nAttributes, ULONGLONG nRadix) CONST;
	virtual INT GetTCSequenceEntryParameterValueRadixLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryParameterValueRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceEntryParameterValueRadix(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCSequenceEntryParameterBitOffset(INT nOffset) CONST;
	virtual BOOL GetTCSequenceEntryParameterBitOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceEntryParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCSequenceEntryParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTCSequenceEntryParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCSequenceEntryParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCSequenceEntryParameterConstTimeType(LPCTSTR pszTag) CONST;
	virtual BOOL CheckTCSequenceEntryParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCSequenceEntryParameterConstTimeLength() CONST;
	virtual CTimeTag TranslateTCSequenceEntryParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual BOOL CheckTCSequenceEntryParameterValueSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCSequenceEntryParameterValueSetNameLength() CONST;
	virtual BOOL CheckTCSequenceEntryParameterMemoryAreaName(LPCTSTR pszName) CONST;
	virtual INT GetTCSequenceEntryParameterMemoryAreaNameLength() CONST;
	virtual BOOL CheckTCSequenceEntryParameterMemoryAreaVersion(LPCTSTR pszVersion) CONST;
	virtual INT GetTCSequenceEntryParameterMemoryAreaVersionLength() CONST;

	virtual BOOL CheckTCProcedureName(LPCTSTR pszName) CONST;
	virtual INT GetTCProcedureNameLength() CONST;
	virtual BOOL CheckTCProcedureDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCProcedureDescriptionLength() CONST;
	virtual BOOL CheckTCProcedureCreationDate(CONST CTimeKey &tDate) CONST;
	virtual BOOL CheckTCProcedureModificationDate(CONST CTimeKey &tCreationDate, CONST CTimeKey &tModificationDate) CONST;
	virtual BOOL CheckTCProcedureExecutionMode(UINT nMode) CONST;
	virtual BOOL CheckTCProcedureArgumentValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual ULONGLONG TranslateTCProcedureArgumentValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCProcedureArgumentValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nValue) CONST;
	virtual CTimeTag TranslateTCProcedureArgumentTime(ULONGLONG nAttributes, LPCTSTR pszTime) CONST;
	virtual BOOL CheckTCProcedureVariableValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual ULONGLONG TranslateTCProcedureVariableValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCProcedureVariableValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nValue) CONST;
	virtual CTimeTag TranslateTCProcedureVariableTime(ULONGLONG nAttributes, LPCTSTR pszTime) CONST;

	virtual BOOL CheckOBProcessorName(LPCTSTR pszName) CONST;
	virtual INT GetOBProcessorNameLength() CONST;
	virtual BOOL CheckOBProcessorDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetOBProcessorDescriptionLength() CONST;
	virtual INT EnumOBProcessorAddressBases(CStringArray &szBases, CUIntArray &nBases) CONST;
	virtual BOOL CheckOBProcessorAddressBase(UINT nBase) CONST;
	virtual INT GetOBProcessorAddressBaseLength() CONST;
	virtual UINT TranslateOBProcessorAddressBase(LPCTSTR pszBase, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorAddressBase(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckOBProcessorPatchCommand(LPCTSTR pszCommand) CONST;
	virtual INT GetOBProcessorPatchCommandLength() CONST;
	virtual BOOL CheckOBProcessorDumpCommand(LPCTSTR pszCommand) CONST;
	virtual INT GetOBProcessorDumpCommandLength() CONST;
	virtual BOOL CheckOBProcessorDumpPacket(LPCTSTR pszPacket) CONST;
	virtual INT GetOBProcessorDumpPacketLength() CONST;
	virtual BOOL CheckOBProcessorDumpInterval(CONST CTimeSpan &tInterval) CONST;
	virtual BOOL GetOBProcessorDumpIntervalRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckOBProcessorDumpCount(INT nCount) CONST;
	virtual BOOL GetOBProcessorDumpCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckOBProcessorMasterImage(LPCTSTR pszImage) CONST;
	virtual INT GetOBProcessorMasterImageLength() CONST;
	virtual UINT GetOBProcessorAddressWidth() CONST;
	virtual BOOL CheckOBProcessorAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress) CONST;
	virtual BOOL GetOBProcessorAddressRange(UINT &nPageLow, UINT &nPageHigh, UINT &nAddressLow, UINT &nAddressHigh) CONST;
	virtual BOOL TranslateOBProcessorAddressRange(LPCTSTR pszAddressRange, UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST;
	virtual CString TranslateOBProcessorAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress) CONST;
	virtual INT EnumOBProcessorStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckOBProcessorStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetOBProcessorStatusLength() CONST;
	virtual INT TranslateOBProcessorStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaName(LPCTSTR pszName) CONST;
	virtual INT GetOBProcessorMemoryAreaNameLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetOBProcessorMemoryAreaDescriptionLength() CONST;
	virtual INT EnumOBProcessorMemoryAreaTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaType(UINT nType) CONST;
	virtual INT GetOBProcessorMemoryAreaTypeLength() CONST;
	virtual UINT TranslateOBProcessorMemoryAreaType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryAreaType(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaPatchCommand(LPCTSTR pszCommand) CONST;
	virtual INT GetOBProcessorMemoryAreaPatchCommandLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaDumpCommand(LPCTSTR pszCommand) CONST;
	virtual INT GetOBProcessorMemoryAreaDumpCommandLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaDumpPacket(LPCTSTR pszPacket) CONST;
	virtual INT GetOBProcessorMemoryAreaDumpPacketLength() CONST;
	virtual INT EnumOBProcessorMemoryAreaPatchFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaPatchFlag(UINT nFlag) CONST;
	virtual INT GetOBProcessorMemoryAreaPatchFlagLength() CONST;
	virtual UINT TranslateOBProcessorMemoryAreaPatchFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryAreaPatchFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumOBProcessorMemoryAreaDumpFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaDumpFlag(UINT nFlag) CONST;
	virtual INT GetOBProcessorMemoryAreaDumpFlagLength() CONST;
	virtual UINT TranslateOBProcessorMemoryAreaDumpFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryAreaDumpFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumOBProcessorMemoryAreaUpdateFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaUpdateFlag(UINT nFlag) CONST;
	virtual INT GetOBProcessorMemoryAreaUpdateFlagLength() CONST;
	virtual UINT TranslateOBProcessorMemoryAreaUpdateFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryAreaUpdateFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumOBProcessorMemoryAreaInhibitFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaInhibitFlag(UINT nFlag) CONST;
	virtual INT GetOBProcessorMemoryAreaInhibitFlagLength() CONST;
	virtual UINT TranslateOBProcessorMemoryAreaInhibitFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryAreaInhibitFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaBlockName(LPCTSTR pszName) CONST;
	virtual INT GetOBProcessorMemoryAreaBlockNameLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaBlockDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetOBProcessorMemoryAreaBlockDescriptionLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaBlockTMParameter(LPCTSTR pszTag) CONST;
	virtual INT GetOBProcessorMemoryAreaBlockTMParameterLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaBlockTCParameter(LPCTSTR pszTag) CONST;
	virtual INT GetOBProcessorMemoryAreaBlockTCParameterLength() CONST;
	virtual UINT GetOBProcessorMemoryAreaBlockAddressWidth() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaBlockAddress(UINT nPage, UINT nAddress) CONST;
	virtual BOOL GetOBProcessorMemoryAreaBlockAddressRange(UINT &nPageLow, UINT &nPageHigh, UINT &nAddressLow, UINT &nAddressHigh) CONST;
	virtual BOOL TranslateOBProcessorMemoryAreaBlockAddress(LPCTSTR pszAddress, UINT &nPage, UINT &nAddress) CONST;
	virtual CString TranslateOBProcessorMemoryAreaBlockAddress(UINT nPage, UINT nAddress) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaBlockBitOffset(INT nOffset) CONST;
	virtual BOOL GetOBProcessorMemoryAreaBlockBitOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaBlockBitWidth(INT nWidth) CONST;
	virtual BOOL GetOBProcessorMemoryAreaBlockBitWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCheckSumName(LPCTSTR pszName) CONST;
	virtual INT GetOBProcessorMemoryAreaCheckSumNameLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCheckSumSeedValue(LPCTSTR pszSeedValue) CONST;
	virtual INT GetOBProcessorMemoryAreaCheckSumSeedValueLength() CONST;
	virtual BOOL GetOBProcessorMemoryAreaCheckSumSeedValueRange(UINT &nLow, UINT &nHigh) CONST;
	virtual UINT TranslateOBProcessorMemoryAreaCheckSumSeedValue(LPCTSTR pszSeedValue) CONST;
	virtual CString TranslateOBProcessorMemoryAreaCheckSumSeedValue(UINT nSeedValue) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCheckSumLength(INT nLength) CONST;
	virtual BOOL GetOBProcessorMemoryAreaCheckSumLengthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCheckSumDestination(UINT nDestination) CONST;
	virtual BOOL GetOBProcessorMemoryAreaCheckSumDestinationRange(UINT &nLow, UINT &nHigh) CONST;
	virtual UINT GetOBProcessorMemoryAreaCheckSumAddressWidth() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCheckSumAddressRange(UINT nPage, UINT nAddressLow, UINT nAddressHigh) CONST;
	virtual BOOL GetOBProcessorMemoryAreaCheckSumAddressRange(UINT &nPageLow, UINT &nPageHigh, UINT &nAddressLow, UINT &nAddressHigh) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueName(LPCTSTR pszName) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueNameLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueEntryID(LPCTSTR pszID) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueEntryIDLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueEntryDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueEntryDescriptionLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueEntryVersion(LPCTSTR pszVersion) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueEntryVersionLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueEntryDate(LPCTSTR pszDate) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueEntryDateLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueEntryTime(LPCTSTR pszTime) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueEntryTimeLength() CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueEntryLocation(LPCTSTR pszLocation) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueEntryLocationLength() CONST;
	virtual INT EnumOBProcessorMemoryAreaCatalogueEntryFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckOBProcessorMemoryAreaCatalogueEntryFlag(UINT nFlag) CONST;
	virtual INT GetOBProcessorMemoryAreaCatalogueEntryFlagLength() CONST;
	virtual UINT TranslateOBProcessorMemoryAreaCatalogueEntryFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryAreaCatalogueEntryFlag(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckOBProcessorMemoryImageName(LPCTSTR pszName) CONST;
	virtual INT GetOBProcessorMemoryImageNameLength() CONST;
	virtual BOOL CheckOBProcessorMemoryImageBlockVersion(LPCTSTR pszVersion) CONST;
	virtual INT GetOBProcessorMemoryImageBlockVersionLength() CONST;
	virtual UINT GetOBProcessorMemoryImageBlockAddressWidth() CONST;
	virtual BOOL CheckOBProcessorMemoryImageBlockAddress(UINT nPage, UINT nAddress) CONST;
	virtual BOOL GetOBProcessorMemoryImageBlockAddressRange(UINT &nPageLow, UINT &nPageHigh, UINT &nAddressLow, UINT &nAddressHigh) CONST;
	virtual BOOL TranslateOBProcessorMemoryImageBlockAddress(LPCTSTR pszAddress, UINT &nPage, UINT &nAddress) CONST;
	virtual CString TranslateOBProcessorMemoryImageBlockAddress(UINT nPage, UINT nAddress) CONST;
	virtual BOOL CheckOBProcessorMemoryImageBlockData(LPCTSTR pszData, BOOL bNumbersOnly = FALSE) CONST;
	virtual BOOL CheckOBProcessorMemoryImageBlockData(CONST CByteArray &nData, CONST CByteArray &nMask, BOOL bAllowTemplates = FALSE) CONST;
	virtual INT GetOBProcessorMemoryImageBlockDataLength() CONST;
	virtual INT TranslateOBProcessorMemoryImageBlockData(LPCTSTR pszData, CByteArray &nData, CByteArray &nMask, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryImageBlockData(CONST CByteArray &nData, CONST CByteArray &nMask, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateOBProcessorMemoryImageBlockData(LPCTSTR pszData, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTMParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTMParameterTagLength() CONST;
	virtual BOOL CheckTMParameterDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMParameterDescriptionLength() CONST;
	virtual BOOL CheckTMParameterDetails(LPCTSTR pszDetails) CONST;
	virtual INT GetTMParameterDetailsLength() CONST;
	virtual BOOL CheckTMParameterUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTMParameterUnitLength() CONST;
	virtual INT EnumTMParameterTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTMParameterType(ULONGLONG nType) CONST;
	virtual INT GetTMParameterTypeLength() CONST;
	virtual ULONGLONG TranslateTMParameterType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterCategories(CStringArray &szCategories, CLongUIntArray &nCategories) CONST;
	virtual BOOL CheckTMParameterCategory(ULONGLONG nCategory) CONST;
	virtual INT GetTMParameterCategoryLength() CONST;
	virtual ULONGLONG TranslateTMParameterCategory(LPCTSTR pszCategory, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterCategory(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterNatures(CStringArray &szNatures, CLongUIntArray &nNatures) CONST;
	virtual BOOL CheckTMParameterNature(ULONGLONG nNature) CONST;
	virtual INT GetTMParameterNatureLength() CONST;
	virtual ULONGLONG TranslateTMParameterNature(LPCTSTR pszNature, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterNature(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterTypeCodes(CStringArray &szPTCs, CUIntArray &nPTCs) CONST;
	virtual BOOL CheckTMParameterTypeCode(INT nPTC) CONST;
	virtual BOOL GetTMParameterTypeCodeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMParameterTypeCode(LPCTSTR pszPTC) CONST;
	virtual CString TranslateTMParameterTypeCode(INT nPTC, INT nPFC) CONST;
	virtual INT EnumTMParameterFormatCodes(LPCTSTR pszPTC, CStringArray &szPFCs, CUIntArray &nPFCs) CONST;
	virtual BOOL CheckTMParameterFormatCode(INT nPTC, INT nPFC) CONST;
	virtual BOOL GetTMParameterFormatCodeRange(INT nPTC, INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMParameterFormatCode(LPCTSTR pszPFC) CONST;
	virtual CString TranslateTMParameterFormatCode(INT nPTC, INT nPFC) CONST;
	virtual BOOL CheckTMParameterBitWidth(ULONGLONG nAttributes, INT nWidth) CONST;
	virtual BOOL GetTMParameterBitWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTMParameterOBSTypes(CStringArray &szOBSTypes, CLongUIntArray &nOBSTypes) CONST;
	virtual BOOL CheckTMParameterOBSType(ULONGLONG nAttributes, ULONGLONG nOBSType) CONST;
	virtual INT GetTMParameterOBSTypeLength() CONST;
	virtual ULONGLONG TranslateTMParameterOBSType(LPCTSTR pszOBSType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterOBSType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterCodings(CStringArray &szCodings, CLongUIntArray &nCodings) CONST;
	virtual BOOL CheckTMParameterCoding(ULONGLONG nAttributes, ULONGLONG nCoding) CONST;
	virtual INT GetTMParameterCodingLength() CONST;
	virtual ULONGLONG TranslateTMParameterCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterCoding(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterInterpretations(CStringArray &szInterpretations, CLongUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTMParameterInterpretation(ULONGLONG nAttributes, ULONGLONG nInterpretation) CONST;
	virtual INT GetTMParameterInterpretationLength() CONST;
	virtual ULONGLONG TranslateTMParameterInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterInterpretation(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterValidityParameters(CStringArray &szParameters) CONST;
	virtual BOOL CheckTMParameterValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMParameterValidityParameterLength() CONST;
	virtual BOOL CheckTMParameterValidityValue(INT nValue) CONST;
	virtual BOOL GetTMParameterValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMParameterRelatedParameter(LPCTSTR pszTag) CONST;
	virtual BOOL CheckTMParameterRelatedParameter(ULONGLONG nAttributes, LPCTSTR pszTag) CONST;
	virtual INT GetTMParameterRelatedParameterLength() CONST;
	virtual CString TranslateTMParameterRelatedParameter(LPCTSTR pszTag) CONST;
	virtual BOOL CheckTMParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTMParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTMParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTMParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTMParameterDerivationExpression(LPCTSTR pszExpression) CONST;
	virtual INT GetTMParameterDerivationExpressionLength() CONST;
	virtual BOOL TranslateTMParameterDerivationExpression(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CString &szProcedure, CStringArray &szErrors) CONST;
	virtual INT EnumTMParameterTriggerTypes(CStringArray &szTriggerTypes, CLongUIntArray &nTriggerTypes) CONST;
	virtual BOOL CheckTMParameterTriggerType(ULONGLONG nAttributes, ULONGLONG nTriggerType) CONST;
	virtual INT GetTMParameterTriggerTypeLength() CONST;
	virtual ULONGLONG TranslateTMParameterTriggerType(LPCTSTR pszTriggerType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterTriggerType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMParameterTriggerExpression(ULONGLONG nNature, ULONGLONG nTriggerType, LPCTSTR pszExpression) CONST;
	virtual INT GetTMParameterTriggerExpressionLength() CONST;
	virtual CString TranslateTMParameterTriggerExpression(LPCTSTR pszExpression) CONST;
	virtual BOOL TranslateTMParameterTriggerExpression(LPCTSTR pszExpression, CString &szParameter, CString &szPacket) CONST;
	virtual BOOL CheckTMParameterCalibrationTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTMParameterCalibrationTableLength() CONST;
	virtual INT GetTMParameterNumCalTablesCount() CONST;
	virtual INT GetTMParameterTxtCalTablesCount() CONST;
	virtual INT GetTMParameterNumOolTablesCount() CONST;
	virtual INT GetTMParameterTxtOolTablesCount() CONST;
	virtual BOOL CheckTMParameterSourceSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTMParameterSourceSubSystemLength() CONST;
	virtual BOOL CheckTMParameterSourceEquipment(LPCTSTR pszEquipment) CONST;
	virtual INT GetTMParameterSourceEquipmentLength() CONST;
	virtual BOOL CheckTMParameterRouterSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTMParameterRouterSubSystemLength() CONST;
	virtual BOOL CheckTMParameterRouterEquipment(LPCTSTR pszEquipment) CONST;
	virtual INT GetTMParameterRouterEquipmentLength() CONST;
	virtual BOOL CheckTMParameterOperationalInfo(LPCTSTR pszInfo) CONST;
	virtual INT GetTMParameterOperationalInfoLength() CONST;
	virtual BOOL CheckTMParameterDangerConditions(LPCTSTR pszConditions) CONST;
	virtual INT GetTMParameterDangerConditionsLength() CONST;
	virtual BOOL CheckTMParameterValidityConditions(LPCTSTR pszConditions) CONST;
	virtual INT GetTMParameterValidityConditionsLength() CONST;
	virtual BOOL CheckTMParameterAlternativeParameters(LPCTSTR pszParameters) CONST;
	virtual INT GetTMParameterAlternativeParametersLength() CONST;
	virtual BOOL CheckTMParameterAssociatedTelecommands(LPCTSTR pszTelecommands) CONST;
	virtual INT GetTMParameterAssociatedTelecommandsLength() CONST;
	virtual BOOL CheckTMParameterInterrogationInstruction(LPCTSTR pszInstruction) CONST;
	virtual INT GetTMParameterInterrogationInstructionLength() CONST;
	virtual BOOL GetTMParameterInterrogationInstructionRange(UINT &nLow, UINT &nHigh) CONST;
	virtual UINT TranslateTMParameterInterrogationInstruction(LPCTSTR pszInstruction) CONST;
	virtual CString TranslateTMParameterInterrogationInstruction(UINT nInstruction) CONST;
	virtual BOOL CheckTMParameterOnBoardID(INT nPID) CONST;
	virtual BOOL GetTMParameterOnBoardIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMParameterOnBoardTimerID(INT nOBTID) CONST;
	virtual BOOL GetTMParameterOnBoardTimerIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMParameterDecimalDigits(INT nDigits) CONST;
	virtual BOOL GetTMParameterDecimalDigitsRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTMParameterResultTypes(CStringArray &szResultTypes, CLongUIntArray &nResultTypes) CONST;
	virtual BOOL CheckTMParameterResultType(ULONGLONG nResultType) CONST;
	virtual INT GetTMParameterResultTypeLength() CONST;
	virtual ULONGLONG TranslateTMParameterResultType(LPCTSTR pszResultType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterResultType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterConsistencyChecksFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTMParameterConsistencyChecksFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTMParameterConsistenceChecksFlagLength() CONST;
	virtual ULONGLONG TranslateTMParameterConsistencyChecksFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterConsistencyChecksFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterTimeCorrelationFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTMParameterTimeCorrelationFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTMParameterTimeCorrelationFlagLength() CONST;
	virtual ULONGLONG TranslateTMParameterTimeCorrelationFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterTimeCorrelationFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterArchivingFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTMParameterArchivingFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTMParameterArchivingFlagLength() CONST;
	virtual ULONGLONG TranslateTMParameterArchivingFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterArchivingFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterEndianityFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTMParameterEndianityFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTMParameterEndianityFlagLength() CONST;
	virtual ULONGLONG TranslateTMParameterEndianityFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterEndianityFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMParameterSpareList(LPCTSTR pszTag) CONST;
	virtual INT EnumTMParameterStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMParameterStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMParameterStatusLength() CONST;
	virtual INT TranslateTMParameterStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMParameterGroupName(LPCTSTR pszName) CONST;
	virtual INT GetTMParameterGroupNameLength() CONST;
	virtual BOOL CheckTMParameterGroupDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMParameterGroupDescriptionLength() CONST;
	virtual BOOL CheckTMParameterGroupType(LPCTSTR pszType) CONST;
	virtual INT GetTMParameterGroupTypeLength() CONST;
	virtual INT TranslateTMParameterGroupType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterGroupType(INT nType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMParameterGroupMember(LPCTSTR pszParameter) CONST;

	virtual BOOL CheckTMNumCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMNumCalTableNameLength() CONST;
	virtual BOOL CheckTMNumCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMNumCalTableDescriptionLength() CONST;
	virtual BOOL CheckTMNumCalTableUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTMNumCalTableUnitLength() CONST;
	virtual INT EnumTMNumCalTableTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTMNumCalTableType(UINT nType) CONST;
	virtual INT GetTMNumCalTableTypeLength() CONST;
	virtual UINT TranslateTMNumCalTableType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumCalTableType(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMNumCalTableEngineeringValuesCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTMNumCalTableEngineeringValuesCoding(UINT nCoding) CONST;
	virtual INT GetTMNumCalTableEngineeringValuesCodingLength() CONST;
	virtual UINT TranslateTMNumCalTableEngineeringValuesCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumCalTableEngineeringValuesCoding(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMNumCalTableRawValuesCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTMNumCalTableRawValuesCoding(UINT nCoding) CONST;
	virtual INT GetTMNumCalTableRawValuesCodingLength() CONST;
	virtual UINT TranslateTMNumCalTableRawValuesCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumCalTableRawValuesCoding(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMNumCalTableRawValuesRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTMNumCalTableRawValuesRadix(UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTMNumCalTableRawValuesRadixLength() CONST;
	virtual UINT TranslateTMNumCalTableRawValuesRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumCalTableRawValuesRadix(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMNumCalTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTMNumCalTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTMNumCalTableInterpretationLength() CONST;
	virtual UINT TranslateTMNumCalTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumCalTableInterpretation(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMNumCalTableValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMNumCalTableValidityParameterLength() CONST;
	virtual BOOL CheckTMNumCalTableValidityValue(INT nValue) CONST;
	virtual BOOL GetTMNumCalTableValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL GetTMNumCalTablePositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMNumCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTMNumCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMNumCalTablePointValue(LPCTSTR pszValue) CONST;
	virtual BOOL CheckTMNumCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTMNumCalTablePointValueLength() CONST;
	virtual double TranslateTMNumCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTMNumCalTablePointValue(UINT nAttributes, double fValue) CONST;
	virtual BOOL CheckTMNumCalTablePointInterval(double X1, double X2) CONST;
	virtual CString GetTMNumCalTablePointOutsideText() CONST;
	virtual INT EnumTMNumCalTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMNumCalTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMNumCalTableStatusLength() CONST;
	virtual INT TranslateTMNumCalTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumCalTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTMTxtCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMTxtCalTableNameLength() CONST;
	virtual BOOL CheckTMTxtCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMTxtCalTableDescriptionLength() CONST;
	virtual INT EnumTMTxtCalTableRawValuesCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTMTxtCalTableRawValuesCoding(UINT nCoding) CONST;
	virtual INT GetTMTxtCalTableRawValuesCodingLength() CONST;
	virtual UINT TranslateTMTxtCalTableRawValuesCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtCalTableRawValuesCoding(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMTxtCalTableValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMTxtCalTableValidityParameterLength() CONST;
	virtual BOOL CheckTMTxtCalTableValidityValue(INT nValue) CONST;
	virtual BOOL GetTMTxtCalTableValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL GetTMTxtCalTablePositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMTxtCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTMTxtCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMTxtCalTablePointValue(LPCTSTR pszValue) CONST;
	virtual BOOL CheckTMTxtCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTMTxtCalTablePointValueLength() CONST;
	virtual double TranslateTMTxtCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTMTxtCalTablePointValue(UINT nAttributes, double fValue) CONST;
	virtual BOOL CheckTMTxtCalTablePointInterval(double X1, double X2) CONST;
	virtual BOOL CheckTMTxtCalTablePointText(LPCTSTR pszText) CONST;
	virtual INT GetTMTxtCalTablePointTextLength() CONST;
	virtual CString GetTMTxtCalTablePointOutsideText() CONST;
	virtual INT EnumTMTxtCalTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMTxtCalTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMTxtCalTableStatusLength() CONST;
	virtual INT TranslateTMTxtCalTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtCalTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTMNumOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMNumOolTableNameLength() CONST;
	virtual BOOL CheckTMNumOolTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMNumOolTableDescriptionLength() CONST;
	virtual BOOL CheckTMNumOolTableUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTMNumOolTableUnitLength() CONST;
	virtual BOOL CheckTMNumOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTMNumOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMNumOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMNumOolTableCheckCount(INT nCount) CONST;
	virtual BOOL CheckTMNumOolTableLimitCount(INT nCount) CONST;
	virtual BOOL GetTMNumOolTableLimitCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMNumOolTableLimitCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMNumOolTableLimitCount(INT nCount) CONST;
	virtual INT EnumTMNumOolTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTMNumOolTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTMNumOolTableInterpretationLength() CONST;
	virtual UINT TranslateTMNumOolTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableInterpretation(UINT nInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMNumOolTableCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTMNumOolTableCoding(UINT nInterpretation, UINT nCoding) CONST;
	virtual INT GetTMNumOolTableCodingLength() CONST;
	virtual UINT TranslateTMNumOolTableCoding(UINT nInterpretation, LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableCoding(UINT nCoding, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMNumOolTableRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTMNumOolTableRadix(UINT nInterpretation, UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTMNumOolTableRadixLength() CONST;
	virtual UINT TranslateTMNumOolTableRadix(UINT nInterpretation, LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableRadix(UINT nRadix, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMNumOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual BOOL CheckTMNumOolTableLimitType(UINT nLimitType) CONST;
	virtual INT GetTMNumOolTableLimitTypeLength() CONST;
	virtual INT TranslateTMNumOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL GetTMNumOolTableLimitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMNumOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTMNumOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTMNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTMNumOolTableLimitValueLength() CONST;
	virtual double TranslateTMNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTMNumOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual BOOL CheckTMNumOolTableLimitValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMNumOolTableLimitValidityParameterLength() CONST;
	virtual BOOL CheckTMNumOolTableLimitValidityValue(INT nValue) CONST;
	virtual BOOL GetTMNumOolTableLimitValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTMNumOolTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMNumOolTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMNumOolTableStatusLength() CONST;
	virtual INT TranslateTMNumOolTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTMTxtOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMTxtOolTableNameLength() CONST;
	virtual BOOL CheckTMTxtOolTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMTxtOolTableDescriptionLength() CONST;
	virtual BOOL CheckTMTxtOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTMTxtOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMTxtOolTableLimitCount(INT nCount) CONST;
	virtual BOOL GetTMTxtOolTableLimitCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMTxtOolTableLimitCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMTxtOolTableLimitCount(INT nCount) CONST;
	virtual INT TranslateTMTxtOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMTxtOolTableCheckCount(INT nCount) CONST;
	virtual INT EnumTMTxtOolTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTMTxtOolTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTMTxtOolTableInterpretationLength() CONST;
	virtual UINT TranslateTMTxtOolTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableInterpretation(UINT nInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMTxtOolTableCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTMTxtOolTableCoding(UINT nInterpretation, UINT nCoding) CONST;
	virtual INT GetTMTxtOolTableCodingLength() CONST;
	virtual UINT TranslateTMTxtOolTableCoding(UINT nInterpretation, LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableCoding(UINT nCoding, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMTxtOolTableRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTMTxtOolTableRadix(UINT nInterpretation, UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTMTxtOolTableRadixLength() CONST;
	virtual UINT TranslateTMTxtOolTableRadix(UINT nInterpretation, LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableRadix(UINT nRadix, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMTxtOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual BOOL CheckTMTxtOolTableLimitType(UINT nLimitType) CONST;
	virtual INT GetTMTxtOolTableLimitTypeLength() CONST;
	virtual INT TranslateTMTxtOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL GetTMTxtOolTableLimitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMTxtOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTMTxtOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTMTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTMTxtOolTableLimitValueLength() CONST;
	virtual double TranslateTMTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTMTxtOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual BOOL CheckTMTxtOolTableLimitValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMTxtOolTableLimitValidityParameterLength() CONST;
	virtual BOOL CheckTMTxtOolTableLimitValidityValue(INT nValue) CONST;
	virtual BOOL GetTMTxtOolTableLimitValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTMTxtOolTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMTxtOolTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMTxtOolTableStatusLength() CONST;
	virtual INT TranslateTMTxtOolTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCParameterTagLength() CONST;
	virtual BOOL CheckTCParameterDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCParameterDescriptionLength() CONST;
	virtual BOOL CheckTCParameterUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTCParameterUnitLength() CONST;
	virtual INT EnumTCParameterTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCParameterType(LPCTSTR pszTag, ULONGLONG nType) CONST;
	virtual INT GetTCParameterTypeLength() CONST;
	virtual ULONGLONG TranslateTCParameterType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCParameterCategories(CStringArray &szCategories, CLongUIntArray &nCategories) CONST;
	virtual BOOL CheckTCParameterCategory(ULONGLONG nCategory) CONST;
	virtual INT GetTCParameterCategoryLength() CONST;
	virtual ULONGLONG TranslateTCParameterCategory(LPCTSTR pszCategory, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterCategory(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCParameterTypeCodes(CStringArray &szPTCs, CUIntArray &nPTCs) CONST;
	virtual BOOL CheckTCParameterTypeCode(INT nPTC) CONST;
	virtual BOOL GetTCParameterTypeCodeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCParameterTypeCode(LPCTSTR pszPTC) CONST;
	virtual CString TranslateTCParameterTypeCode(INT nPTC, INT nPFC) CONST;
	virtual INT EnumTCParameterFormatCodes(LPCTSTR pszPTC, CStringArray &szPFCs, CUIntArray &nPFCs) CONST;
	virtual BOOL CheckTCParameterFormatCode(INT nPTC, INT nPFC) CONST;
	virtual BOOL GetTCParameterFormatCodeRange(INT nPTC, INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCParameterFormatCode(LPCTSTR pszPFC) CONST;
	virtual CString TranslateTCParameterFormatCode(INT nPTC, INT nPFC) CONST;
	virtual INT EnumTCParameterDisplayFormats(CStringArray &szFormats, CLongUIntArray &nFormats) CONST;
	virtual INT EnumTCParameterDisplayFormats(ULONGLONG nAttributes, CStringArray &szFormats, CLongUIntArray &nFormats) CONST;
	virtual BOOL CheckTCParameterDisplayFormat(ULONGLONG nAttributes, ULONGLONG nFormat) CONST;
	virtual INT GetTCParameterDisplayFormatLength() CONST;
	virtual ULONGLONG TranslateTCParameterDisplayFormat(LPCTSTR pszFormat, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterDisplayFormat(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCParameterCodings(CStringArray &szCodings, CLongUIntArray &nCodings) CONST;
	virtual BOOL CheckTCParameterCoding(ULONGLONG nAttributes, ULONGLONG nCoding) CONST;
	virtual INT GetTCParameterCodingLength() CONST;
	virtual ULONGLONG TranslateTCParameterCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterCoding(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCParameterRadixes(CStringArray &szRadixes, CLongUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCParameterRadix(ULONGLONG nAttributes, ULONGLONG nRadix) CONST;
	virtual INT GetTCParameterRadixLength() CONST;
	virtual ULONGLONG TranslateTCParameterRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterRadix(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCParameterBitWidth(INT nWidth) CONST;
	virtual BOOL GetTCParameterBitWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCParameterCalTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCParameterCalTableLength() CONST;
	virtual BOOL CheckTCParameterOolTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCParameterOolTableLength() CONST;
	virtual INT EnumTCParameterConstValueTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual INT EnumTCParameterConstValueTypes(ULONGLONG nAttributes, CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCParameterConstValueType(ULONGLONG nType, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCParameterConstValueTypeLength() CONST;
	virtual ULONGLONG TranslateTCParameterConstValueType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterConstValueType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTCParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCParameterConstTimeType(LPCTSTR pszTag) CONST;
	virtual BOOL CheckTCParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCParameterConstTimeLength() CONST;
	virtual CTimeTag TranslateTCParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual CString TranslateTCParameterConstTime(ULONGLONG nAttributes, CONST CTimeTag &tTime) CONST;
	virtual BOOL CheckTCParameterOnBoardTimerID(INT nOBTID) CONST;
	virtual BOOL GetTCParameterOnBoardTimerIDRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCParameterTimeCorrelationFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCParameterTimeCorrelationFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCParameterTimeCorrelationFlagLength() CONST;
	virtual ULONGLONG TranslateTCParameterTimeCorrelationFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterTimeCorrelationFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCParameterStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCParameterStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCParameterStatusLength() CONST;
	virtual INT TranslateTCParameterStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCNumCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCNumCalTableNameLength() CONST;
	virtual BOOL CheckTCNumCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCNumCalTableDescriptionLength() CONST;
	virtual BOOL CheckTCNumCalTableUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTCNumCalTableUnitLength() CONST;
	virtual INT EnumTCNumCalTableTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTCNumCalTableType(UINT nType) CONST;
	virtual INT GetTCNumCalTableTypeLength() CONST;
	virtual UINT TranslateTCNumCalTableType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumCalTableType(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCNumCalTableEngineeringValuesCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTCNumCalTableEngineeringValuesCoding(UINT nCoding) CONST;
	virtual INT GetTCNumCalTableEngineeringValuesCodingLength() CONST;
	virtual UINT TranslateTCNumCalTableEngineeringValuesCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumCalTableEngineeringValuesCoding(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCNumCalTableRawValuesCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTCNumCalTableRawValuesCoding(UINT nCoding) CONST;
	virtual INT GetTCNumCalTableRawValuesCodingLength() CONST;
	virtual UINT TranslateTCNumCalTableRawValuesCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumCalTableRawValuesCoding(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCNumCalTableRawValuesRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCNumCalTableRawValuesRadix(UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTCNumCalTableRawValuesRadixLength() CONST;
	virtual UINT TranslateTCNumCalTableRawValuesRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumCalTableRawValuesRadix(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCNumCalTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCNumCalTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCNumCalTableInterpretationLength() CONST;
	virtual UINT TranslateTCNumCalTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumCalTableInterpretation(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCNumCalTableValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTCNumCalTableValidityParameterLength() CONST;
	virtual BOOL CheckTCNumCalTableValidityValue(INT nValue) CONST;
	virtual BOOL GetTCNumCalTableValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL GetTCNumCalTablePositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCNumCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTCNumCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCNumCalTablePointValue(LPCTSTR pszValue) CONST;
	virtual BOOL CheckTCNumCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTCNumCalTablePointValueLength() CONST;
	virtual double TranslateTCNumCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCNumCalTablePointValue(UINT nAttributes, double fValue) CONST;
	virtual BOOL CheckTCNumCalTablePointInterval(double X1, double X2) CONST;
	virtual CString GetTCNumCalTablePointOutsideText() CONST;
	virtual INT EnumTCNumCalTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCNumCalTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCNumCalTableStatusLength() CONST;
	virtual INT TranslateTCNumCalTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumCalTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCTxtCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCTxtCalTableNameLength() CONST;
	virtual BOOL CheckTCTxtCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCTxtCalTableDescriptionLength() CONST;
	virtual INT EnumTCTxtCalTableRawValuesCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTCTxtCalTableRawValuesCoding(UINT nCoding) CONST;
	virtual INT GetTCTxtCalTableRawValuesCodingLength() CONST;
	virtual UINT TranslateTCTxtCalTableRawValuesCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtCalTableRawValuesCoding(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCTxtCalTableValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTCTxtCalTableValidityParameterLength() CONST;
	virtual BOOL CheckTCTxtCalTableValidityValue(INT nValue) CONST;
	virtual BOOL GetTCTxtCalTableValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL GetTCTxtCalTablePositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCTxtCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTCTxtCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCTxtCalTablePointValue(LPCTSTR pszValue) CONST;
	virtual BOOL CheckTCTxtCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTCTxtCalTablePointValueLength() CONST;
	virtual double TranslateTCTxtCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCTxtCalTablePointValue(UINT nAttributes, double fValue) CONST;
	virtual BOOL CheckTCTxtCalTablePointInterval(double X1, double X2) CONST;
	virtual BOOL CheckTCTxtCalTablePointText(LPCTSTR pszText) CONST;
	virtual INT GetTCTxtCalTablePointTextLength() CONST;
	virtual CString GetTCTxtCalTablePointOutsideText() CONST;
	virtual INT EnumTCTxtCalTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCTxtCalTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCTxtCalTableStatusLength() CONST;
	virtual INT TranslateTCTxtCalTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtCalTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCNumOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCNumOolTableNameLength() CONST;
	virtual BOOL CheckTCNumOolTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCNumOolTableDescriptionLength() CONST;
	virtual BOOL CheckTCNumOolTableUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTCNumOolTableUnitLength() CONST;
	virtual BOOL CheckTCNumOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTCNumOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCNumOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTCNumOolTableCheckCount(INT nCount) CONST;
	virtual BOOL CheckTCNumOolTableLimitCount(INT nCount) CONST;
	virtual BOOL GetTCNumOolTableLimitCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCNumOolTableLimitCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTCNumOolTableLimitCount(INT nCount) CONST;
	virtual INT EnumTCNumOolTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCNumOolTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCNumOolTableInterpretationLength() CONST;
	virtual UINT TranslateTCNumOolTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumOolTableInterpretation(UINT nInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCNumOolTableCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTCNumOolTableCoding(UINT nInterpretation, UINT nCoding) CONST;
	virtual INT GetTCNumOolTableCodingLength() CONST;
	virtual UINT TranslateTCNumOolTableCoding(UINT nInterpretation, LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumOolTableCoding(UINT nCoding, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCNumOolTableRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCNumOolTableRadix(UINT nInterpretation, UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTCNumOolTableRadixLength() CONST;
	virtual UINT TranslateTCNumOolTableRadix(UINT nInterpretation, LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumOolTableRadix(UINT nRadix, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCNumOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual BOOL CheckTCNumOolTableLimitType(UINT nLimitType) CONST;
	virtual INT GetTCNumOolTableLimitTypeLength() CONST;
	virtual INT TranslateTCNumOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL GetTCNumOolTableLimitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCNumOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTCNumOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTCNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTCNumOolTableLimitValueLength() CONST;
	virtual double TranslateTCNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTCNumOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual BOOL CheckTCNumOolTableLimitTime(ULONGLONG nAttributes, LPCTSTR pszTime) CONST;
	virtual CTimeTag TranslateTCNumOolTableLimitTime(ULONGLONG nAttributes, LPCTSTR pszTime) CONST;
	virtual CString TranslateTCNumOolTableLimitTime(ULONGLONG nAttributes, CONST CTimeTag &tTime) CONST;
	virtual BOOL CheckTCNumOolTableLimitValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTCNumOolTableLimitValidityParameterLength() CONST;
	virtual BOOL CheckTCNumOolTableLimitValidityValue(INT nValue) CONST;
	virtual BOOL GetTCNumOolTableLimitValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCNumOolTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCNumOolTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCNumOolTableStatusLength() CONST;
	virtual INT TranslateTCNumOolTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumOolTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCTxtOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCTxtOolTableNameLength() CONST;
	virtual BOOL CheckTCTxtOolTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCTxtOolTableDescriptionLength() CONST;
	virtual BOOL CheckTCTxtOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTCTxtOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCTxtOolTableLimitCount(INT nCount) CONST;
	virtual BOOL GetTCTxtOolTableLimitCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCTxtOolTableLimitCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTCTxtOolTableLimitCount(INT nCount) CONST;
	virtual INT TranslateTCTxtOolTableCheckCount(UINT nInterpretation, LPCTSTR pszCount) CONST;
	virtual CString TranslateTCTxtOolTableCheckCount(UINT nInterpretation, INT nCount) CONST;
	virtual INT EnumTCTxtOolTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCTxtOolTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCTxtOolTableInterpretationLength() CONST;
	virtual UINT TranslateTCTxtOolTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableInterpretation(UINT nInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCTxtOolTableCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTCTxtOolTableCoding(UINT nInterpretation, UINT nCoding) CONST;
	virtual INT GetTCTxtOolTableCodingLength() CONST;
	virtual UINT TranslateTCTxtOolTableCoding(UINT nInterpretation, LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableCoding(UINT nCoding, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCTxtOolTableRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCTxtOolTableRadix(UINT nInterpretation, UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTCTxtOolTableRadixLength() CONST;
	virtual UINT TranslateTCTxtOolTableRadix(UINT nInterpretation, LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableRadix(UINT nRadix, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCTxtOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual BOOL CheckTCTxtOolTableLimitType(UINT nLimitType) CONST;
	virtual INT GetTCTxtOolTableLimitTypeLength() CONST;
	virtual INT TranslateTCTxtOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL GetTCTxtOolTableLimitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCTxtOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTCTxtOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTCTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTCTxtOolTableLimitValueLength() CONST;
	virtual double TranslateTCTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTCTxtOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual BOOL CheckTCTxtOolTableLimitValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTCTxtOolTableLimitValidityParameterLength() CONST;
	virtual BOOL CheckTCTxtOolTableLimitValidityValue(INT nValue) CONST;
	virtual BOOL GetTCTxtOolTableLimitValidityValueRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCTxtOolTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCTxtOolTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCTxtOolTableStatusLength() CONST;
	virtual INT TranslateTCTxtOolTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCPreExeGroupID(LPCTSTR pszID) CONST;
	virtual INT GetTCPreExeGroupIDLength() CONST;
	virtual BOOL CheckTCPreExeGroupDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCPreExeGroupDescriptionLength() CONST;
	virtual INT EnumTCPreExeGroupStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCPreExeGroupStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCPreExeGroupStatusLength() CONST;
	virtual INT TranslateTCPreExeGroupStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPreExeGroupStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCPreExeGroupParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCPreExeGroupParameterTagLength() CONST;
	virtual INT EnumTCPreExeGroupParameterInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCPreExeGroupParameterInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCPreExeGroupParameterInterpretationLength() CONST;
	virtual UINT TranslateTCPreExeGroupParameterInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPreExeGroupParameterInterpretation(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCPreExeGroupParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTCPreExeGroupParameterConstValueLength() CONST;
	virtual double TranslateTCPreExeGroupParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCPreExeGroupParameterConstValue(ULONGLONG nAttributes, double fValue) CONST;

	virtual BOOL CheckTCExeVerGroupID(LPCTSTR pszID) CONST;
	virtual INT GetTCExeVerGroupIDLength() CONST;
	virtual BOOL CheckTCExeVerGroupName(LPCTSTR pszName) CONST;
	virtual INT GetTCExeVerGroupNameLength() CONST;
	virtual BOOL CheckTCExeVerGroupDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCExeVerGroupDescriptionLength() CONST;
	virtual BOOL CheckTCExeVerGroupStages(INT nStages) CONST;
	virtual BOOL GetTCExeVerGroupStagesRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCExeVerGroupStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCExeVerGroupStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCExeVerGroupStatusLength() CONST;
	virtual INT TranslateTCExeVerGroupStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCExeVerGroupParameterStageID(UINT nStageID) CONST;
	virtual BOOL GetTCExeVerGroupParameterStageIDRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterStageTask(LPCTSTR pszTask) CONST;
	virtual INT GetTCExeVerGroupParameterStageTaskLength() CONST;
	virtual INT EnumTCExeVerGroupParameterStageTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTCExeVerGroupParameterStageType(UINT nType) CONST;
	virtual INT GetTCExeVerGroupParameterStageTypeLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterStageType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterStageType(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCExeVerGroupParameterStages(CStringArray &szStageIDs, CUIntArray &nStageIDs) CONST;
	virtual BOOL CheckTCExeVerGroupParameterStage(UINT nStageID) CONST;
	virtual INT GetTCExeVerGroupParameterStageLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterStage(LPCTSTR pszStageID, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterStage(UINT nStageID, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCExeVerGroupParameterTagLength() CONST;
	virtual INT EnumTCExeVerGroupParameterTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTCExeVerGroupParameterType(UINT nType) CONST;
	virtual INT GetTCExeVerGroupParameterTypeLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterType(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCExeVerGroupParameterCheckings(CStringArray &szCheckings, CUIntArray &nCheckings) CONST;
	virtual BOOL CheckTCExeVerGroupParameterChecking(UINT nChecking) CONST;
	virtual INT GetTCExeVerGroupParameterCheckingLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterChecking(LPCTSTR pszChecking, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterChecking(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCExeVerGroupParameterInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCExeVerGroupParameterInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCExeVerGroupParameterInterpretationLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterInterpretation(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCExeVerGroupParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTCExeVerGroupParameterConstValueLength() CONST;
	virtual double TranslateTCExeVerGroupParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCExeVerGroupParameterConstValue(ULONGLONG nAttributes, double fValue) CONST;
	virtual BOOL CheckTCExeVerGroupParameterConstValueTolerance(ULONGLONG nAttributes, LPCTSTR pszDelta) CONST;
	virtual INT GetTCExeVerGroupParameterConstValueToleranceLength() CONST;
	virtual double TranslateTCExeVerGroupParameterConstValueTolerance(ULONGLONG nAttributes, LPCTSTR pszDelta) CONST;
	virtual CString TranslateTCExeVerGroupParameterConstValueTolerance(ULONGLONG nAttributes, double fDelta) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowOffset(CONST CTimeSpan &tOffset) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowOffsetRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowInterval(CONST CTimeSpan &tInterval) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowIntervalRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowUncertainty(CONST CTimeSpan &tInterval) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowUncertaintyRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowClosurePacketID(UINT nID) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowClosurePacketIDRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterEventID(LPCTSTR pszEventID) CONST;
	virtual INT GetTCExeVerGroupParameterEventIDLength() CONST;

	virtual BOOL CheckTCParameterSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCParameterSetNameLength() CONST;
	virtual BOOL CheckTCParameterSetDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCParameterSetDescriptionLength() CONST;
	virtual BOOL CheckTCParameterSetTask(LPCTSTR pszTask) CONST;
	virtual INT GetTCParameterSetTaskLength() CONST;
	virtual INT EnumTCParameterSetTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTCParameterSetType(UINT nType) CONST;
	virtual INT GetTCParameterSetTypeLength() CONST;
	virtual UINT TranslateTCParameterSetType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterSetType(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCParameterSetStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCParameterSetStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCParameterSetStatusLength() CONST;
	virtual INT TranslateTCParameterSetStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterSetStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCParameterValueSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCParameterValueSetNameLength() CONST;
	virtual BOOL CheckTCParameterValueSetDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCParameterValueSetDescriptionLength() CONST;
	virtual BOOL CheckTCParameterSetItemName(LPCTSTR pszName) CONST;
	virtual INT GetTCParameterSetItemNameLength() CONST;
	virtual INT EnumTCParameterSetItemValueInterpretations(CStringArray &szInterpretations, CLongUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCParameterSetItemValueInterpretation(ULONGLONG nAttributes, ULONGLONG nInterpretation) CONST;
	virtual INT GetTCParameterSetItemValueInterpretationLength() CONST;
	virtual ULONGLONG TranslateTCParameterSetItemValueInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterSetItemValueInterpretation(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCParameterSetItemValueRadixes(CStringArray &szRadixes, CLongUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCParameterSetItemValueRadix(ULONGLONG nAttributes, ULONGLONG nRadix) CONST;
	virtual INT GetTCParameterSetItemValueRadixLength() CONST;
	virtual ULONGLONG TranslateTCParameterSetItemValueRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterSetItemValueRadix(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCParameterSetItemValueBitOffset(INT nOffset) CONST;
	virtual BOOL GetTCParameterSetItemValueBitOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCParameterSetItemConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCParameterSetItemConstValueLength() CONST;
	virtual ULONGLONG TranslateTCParameterSetItemConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCParameterSetItemConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCParameterSetItemConstTimeType(LPCTSTR pszName) CONST;
	virtual BOOL CheckTCParameterSetItemConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCParameterSetItemConstTimeLength() CONST;
	virtual CTimeTag TranslateTCParameterSetItemConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;

	virtual BOOL CheckANDName(LPCTSTR pszName) CONST;
	virtual INT GetANDNameLength() CONST;
	virtual BOOL CheckANDTitle(LPCTSTR pszTitle) CONST;
	virtual INT GetANDTitleLength() CONST;
	virtual INT EnumANDColumns(CStringArray &szColumns, CUIntArray &nColumns) CONST;
	virtual BOOL CheckANDColumns(LPCTSTR pszColumns) CONST;
	virtual INT GetANDColumnsLength() CONST;
	virtual UINT TranslateANDColumns(LPCTSTR pszColumns, BOOL bDBMS = TRUE) CONST;
	virtual BOOL TranslateANDColumns(LPCTSTR pszColumns, CUIntArray &nColumns, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateANDColumns(INT nColumns, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateANDColumns(CONST CUIntArray &nColumns, BOOL bDBMS = TRUE) CONST;
	virtual UINT TranslateANDColumn(LPCTSTR pszColumn, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateANDColumn(UINT nColumn, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumANDStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckANDStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetANDStatusLength() CONST;
	virtual INT TranslateANDStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateANDStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckANDParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetANDParameterTagLength() CONST;
	virtual BOOL CheckANDParameterComment(LPCTSTR pszComment) CONST;
	virtual INT GetANDParameterCommentLength() CONST;
	virtual CString TranslateANDParameterComment(LPCTSTR pszComment, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckANDParameterRow(INT nRow) CONST;
	virtual BOOL GetANDParameterRowRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckANDParameterCol(INT nCol) CONST;
	virtual BOOL GetANDParameterColRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumANDParameterModes(CStringArray &szModes, CLongUIntArray &nModes) CONST;
	virtual BOOL CheckANDParameterMode(LPCTSTR pszParameter, LPCTSTR pszMode) CONST;
	virtual INT GetANDParameterModeLength() CONST;
	virtual ULONGLONG TranslateANDParameterMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateANDParameterMode(ULONGLONG nMode, BOOL bDBMS = TRUE) CONST;
	virtual ULONGLONG TranslateANDParameterAttributes(ULONGLONG nMode, ULONGLONG nAttributes) CONST;
	virtual INT EnumANDParameterDisplayFlags(CStringArray &szFlags, CByteArray &nFlags) CONST;
	virtual BOOL CheckANDParameterDisplayFlag(LPCTSTR pszParameter, LPCTSTR pszFlag) CONST;
	virtual INT GetANDParameterDisplayFlagLength() CONST;
	virtual INT TranslateANDParameterDisplayFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateANDParameterDisplayFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckANDParameterOccurrence(LPCTSTR pszParameter, INT nOccurrence) CONST;
	virtual BOOL GetANDParameterOccurrenceRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckANDParameterColor(INT nColor) CONST;
	virtual BOOL CheckANDParameterDigits(LPCTSTR pszParameter, INT nDigits) CONST;
	virtual BOOL GetANDParameterDigitsRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumANDParameterAlignments(CStringArray &szAlignments, CUIntArray &nAlignments) CONST;
	virtual BOOL CheckANDParameterAlignment(LPCTSTR pszAlignment) CONST;
	virtual INT GetANDParameterAlignmentLength() CONST;
	virtual UINT TranslateANDParameterAlignment(LPCTSTR pszAlignment, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateANDParameterAlignment(UINT nAlignment, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckGRDName(LPCTSTR pszName) CONST;
	virtual INT GetGRDNameLength() CONST;
	virtual BOOL CheckGRDTitle(LPCTSTR pszTitle) CONST;
	virtual INT GetGRDTitleLength() CONST;
	virtual INT EnumGRDColumns(CStringArray &szColumns, CUIntArray &nColumns) CONST;
	virtual BOOL CheckGRDColumns(INT nColumns) CONST;
	virtual BOOL TranslateGRDColumns(LPCTSTR pszColumns, CUIntArray &nColumns, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDColumns(CONST CUIntArray &nColumns, BOOL bDBMS = TRUE) CONST;
	virtual UINT TranslateGRDColumn(LPCTSTR pszColumn, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDColumn(UINT nColumn, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumGRDTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckGRDType(LPCTSTR pszType) CONST;
	virtual INT GetGRDTypeLength() CONST;
	virtual INT TranslateGRDType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDType(INT nType, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumGRDPlotTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckGRDPlotType(LPCTSTR pszType, LPCTSTR pszPlotType) CONST;
	virtual INT GetGRDPlotTypeLength() CONST;
	virtual INT TranslateGRDPlotType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDPlotType(INT nType, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumGRDPlotModes(CStringArray &szModes, CUIntArray &nModes) CONST;
	virtual BOOL CheckGRDPlotMode(LPCTSTR pszType, LPCTSTR pszMode) CONST;
	virtual INT GetGRDPlotModeLength() CONST;
	virtual INT TranslateGRDPlotMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDPlotMode(INT nMode, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckGRDPlotWidth(INT nWidth) CONST;
	virtual BOOL GetGRDPlotWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDPlotHeight(INT nHeight) CONST;
	virtual BOOL GetGRDPlotHeightRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDXGrids(LPCTSTR pszType, INT nXGrids) CONST;
	virtual BOOL GetGRDXGridsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDYGrids(LPCTSTR pszType, INT nYGrids) CONST;
	virtual BOOL GetGRDYGridsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDXTicks(INT nXTicks) CONST;
	virtual BOOL GetGRDXTicksRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDYTicks(INT nYTicks) CONST;
	virtual BOOL GetGRDYTicksRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDGridsWidth(INT nWidth) CONST;
	virtual BOOL GetGRDGridsWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDTicksWidth(INT nWidth) CONST;
	virtual BOOL GetGRDTicksWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumGRDAxisColors(CStringArray &szColors, CUIntArray &nColors) CONST;
	virtual BOOL CheckGRDAxisColor(INT nColor) CONST;
	virtual INT GetGRDAxisColorLength() CONST;
	virtual COLORREF TranslateGRDAxisColor(LPCTSTR pszColor, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDAxisColor(COLORREF nColor, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckGRDGridsColor(INT nGridsColor) CONST;
	virtual BOOL CheckGRDTicksColor(INT nTicksColor) CONST;
	virtual BOOL CheckGRDBackgroundColor(INT nBackgroundColor) CONST;
	virtual BOOL CheckGRDLabelColor(INT nLabelColor) CONST;
	virtual BOOL CheckGRDDurationDays(INT nDays, INT nHours, INT nMinutes) CONST;
	virtual BOOL GetGRDDurationDaysRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDDurationHours(INT nDays, INT nHours, INT nMinutes) CONST;
	virtual BOOL GetGRDDurationHoursRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDDurationMinutes(INT nDays, INT nHours, INT nMinutes) CONST;
	virtual BOOL GetGRDDurationMinutesRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDInterval(LPCTSTR pszMode, INT nDays, INT nHours, INT nMinutes, INT nInterval) CONST;
	virtual BOOL GetGRDIntervalRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDUpdateInterval(INT nDays, INT nHours, INT nMinutes, INT nInterval) CONST;
	virtual BOOL GetGRDUpdateIntervalRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumGRDHardcopyModes(CStringArray &szModes, CByteArray &nModes) CONST;
	virtual BOOL CheckGRDHardcopyMode(LPCTSTR pszMode) CONST;
	virtual INT GetGRDHardcopyModeLength() CONST;
	virtual INT TranslateGRDHardcopyMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDHardcopyMode(INT nMode, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckGRDParameters(LPCTSTR pszType, INT nParameters) CONST;
	virtual BOOL GetGRDParametersRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumGRDStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckGRDStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetGRDStatusLength() CONST;
	virtual INT TranslateGRDStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckGRDParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetGRDParameterTagLength() CONST;
	virtual BOOL CheckGRDParameterComment(LPCTSTR pszComment) CONST;
	virtual INT GetGRDParameterCommentLength() CONST;
	virtual INT EnumGRDParameterPositions(CStringArray &szPositions, CUIntArray &nPositions) CONST;
	virtual BOOL CheckGRDParameterPosition(INT nPosition) CONST;
	virtual BOOL GetGRDParameterPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual INT GetGRDParameterPositionLength() CONST;
	virtual INT TranslateGRDParameterPosition(LPCTSTR pszPosition, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDParameterPosition(INT nPosition, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumGRDParameterModes(CStringArray &szModes, CLongUIntArray &nModes) CONST;
	virtual BOOL CheckGRDParameterMode(LPCTSTR pszMode) CONST;
	virtual INT GetGRDParameterModeLength() CONST;
	virtual ULONGLONG TranslateGRDParameterMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDParameterMode(ULONGLONG nMode, BOOL bDBMS = TRUE) CONST;
	virtual ULONGLONG TranslateGRDParameterAttributes(ULONGLONG nMode, ULONGLONG nAttributes) CONST;
	virtual BOOL CheckGRDParameterOccurrence(INT nOccurrence) CONST;
	virtual BOOL GetGRDParameterOccurrenceRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumGRDParameterColors(CStringArray &szColors, CUIntArray &nColors) CONST;
	virtual BOOL CheckGRDParameterColor(INT nColor) CONST;
	virtual INT GetGRDParameterColorLength() CONST;
	virtual INT TranslateGRDParameterColor(LPCTSTR pszColor, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDParameterColor(INT nColor, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckGRDParameterDigits(INT nDigits) CONST;
	virtual BOOL GetGRDParameterDigitsRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumGRDParameterLineStyles(CStringArray &szStyles, CUIntArray &nStyles) CONST;
	virtual BOOL CheckGRDParameterLineStyle(LPCTSTR pszStyle) CONST;
	virtual INT GetGRDParameterLineStyleLength() CONST;
	virtual INT TranslateGRDParameterLineStyle(LPCTSTR pszStyle, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDParameterLineStyle(INT nStyle, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumGRDParameterLineSymbols(CStringArray &szSymbols, CUIntArray &nSymbols) CONST;
	virtual BOOL CheckGRDParameterLineSymbol(LPCTSTR pszSymbol) CONST;
	virtual INT GetGRDParameterLineSymbolLength() CONST;
	virtual INT TranslateGRDParameterLineSymbol(LPCTSTR pszSymbol, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDParameterLineSymbol(INT nSymbol, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckGRDParameterLineWidth(INT nWidth) CONST;
	virtual BOOL GetGRDParameterLineWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDParameterMinimum(LPCTSTR pszMinimum) CONST;
	virtual BOOL CheckGRDParameterMinimum(double fMinimum) CONST;
	virtual INT GetGRDParameterMinimumLength() CONST;
	virtual BOOL CheckGRDParameterMaximum(LPCTSTR pszMaximum) CONST;
	virtual BOOL CheckGRDParameterMaximum(double fMaximum) CONST;
	virtual INT GetGRDParameterMaximumLength() CONST;
	virtual BOOL CheckGRDParameterRange(double fMinimum, double fMaximum) CONST;

	virtual BOOL CheckPODName(LPCTSTR pszName) CONST;
	virtual INT GetPODNameLength() CONST;
	virtual BOOL CheckPODTitle(LPCTSTR pszTitle) CONST;
	virtual INT GetPODTitleLength() CONST;
	virtual INT EnumPODColumns(CStringArray &szColumns, CUIntArray &nColumns) CONST;
	virtual BOOL CheckPODColumns(INT nColumns) CONST;
	virtual BOOL TranslatePODColumns(LPCTSTR pszColumns, CUIntArray &nColumns, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODColumns(CONST CUIntArray &nColumns, BOOL bDBMS = TRUE) CONST;
	virtual UINT TranslatePODColumn(LPCTSTR pszColumn, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODColumn(UINT nColumn, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumPODForegroundColors(CStringArray &szColors, CUIntArray &nColors) CONST;
	virtual BOOL CheckPODForegroundColor(INT nColor) CONST;
	virtual INT GetPODForegroundColorLength() CONST;
	virtual INT TranslatePODForegroundColor(LPCTSTR pszColor, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODForegroundColor(INT nColor, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumPODBackgroundColors(CStringArray &szColors, CUIntArray &nColors) CONST;
	virtual BOOL CheckPODBackgroundColor(INT nColor) CONST;
	virtual INT GetPODBackgroundColorLength() CONST;
	virtual INT TranslatePODBackgroundColor(LPCTSTR pszColor, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODBackgroundColor(INT nColor, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumPODStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckPODStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetPODStatusLength() CONST;
	virtual INT TranslatePODStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumPODExpressionStack(CStringArray &szExpressions, CUIntArray &nExpressions) CONST;
	virtual BOOL CheckPODExpressionStack(LPCTSTR pszStack) CONST;
	virtual INT GetPODExpressionStackLength() CONST;
	virtual INT TranslatePODExpressionStack(LPCTSTR pszStack, CStringArray &szStack, CByteArray &bFunctions, CByteArray &bOperators, CByteArray &bParameters, CByteArray &bNumbers) CONST;
	virtual CString TranslatePODExpressionStack(CONST CStringArray &szStack) CONST;
	virtual BOOL TranslatePODExpressionStackElement(LPCTSTR pszElement, CPODLayoutExpression *pElement) CONST;
	virtual BOOL CheckPODExpressionStackElementComment(LPCTSTR pszComment) CONST;
	virtual INT GetPODExpressionStackElementCommentLength() CONST;
	virtual BOOL CheckPODExpressionStackElementColor(INT nColor) CONST;
	virtual BOOL CheckPODParameters(LPCTSTR pszParameters) CONST;
	virtual INT GetPODParametersListLength() CONST;
	virtual INT GetPODParameterTagLength() CONST;
	virtual INT TranslatePODParameters(LPCTSTR pszParameters, CStringArray &szParameters) CONST;
	virtual CString TranslatePODParameters(CONST CStringArray &szParameters) CONST;
	virtual BOOL CheckPODParameterSample(INT nSample) CONST;
	virtual BOOL GetPODParameterSampleRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckPODParameterPosition(INT nPosition) CONST;
	virtual BOOL GetPODParameterPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumPODParameterModes(CStringArray &szModes, CLongUIntArray &nModes) CONST;
	virtual BOOL CheckPODParameterMode(LPCTSTR pszMode) CONST;
	virtual INT GetPODParameterModeLength() CONST;
	virtual ULONGLONG TranslatePODParameterMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODParameterMode(ULONGLONG nMode, BOOL bDBMS = TRUE) CONST;
	virtual ULONGLONG TranslatePODParameterAttributes(ULONGLONG nMode, ULONGLONG nAttributes) CONST;
	virtual INT EnumPODParameterUpdateWhenScrollFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckPODParameterUpdateWhenScrollFlag(LPCTSTR pszFlag) CONST;
	virtual INT GetPODParameterUpdateWhenScrollFlagLength() CONST;
	virtual INT TranslatePODParameterUpdateWhenScrollFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODParameterUpdateWhenScrollFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumPODParameterDisplayFlags(CStringArray &szFlags, CByteArray &nFlags) CONST;
	virtual BOOL CheckPODParameterDisplayFlag(LPCTSTR pszFlag) CONST;
	virtual INT GetPODParameterDisplayFlagLength() CONST;
	virtual BOOL TranslatePODParameterDisplayFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODParameterDisplayFlag(BOOL bFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckPODParametersColor(INT nColor) CONST;
	virtual INT EnumPODFunctions(CStringArray &szFunctions, CUIntArray &nFunctions) CONST;
	virtual BOOL CheckPODFunctions(LPCTSTR pszFunctions) CONST;
	virtual INT GetPODFunctionsListLength() CONST;
	virtual INT GetPODFunctionLength() CONST;
	virtual INT TranslatePODFunctions(LPCTSTR pszFunctions, CStringArray &szFunctions) CONST;
	virtual CString TranslatePODFunctions(CONST CStringArray &szFunctions) CONST;
	virtual BOOL CheckPODFunctionsColor(INT nColor) CONST;

public:
	virtual BOOL LoadTMParameterDerivationCodeFromFile(LPCTSTR pszTag, CString &szCode) CONST;
	virtual BOOL LoadTMParameterDerivationCodeFromFile(CONST CDatabaseTMParameter *pDatabaseTMParameter, CString &szCode) CONST;
	virtual BOOL ConstructCustomDerivationCode(CONST CBinaryDatabase *pDatabase, CString &szStaticProcedures, CString &szInitCode, CString &szExecCode) CONST;

public:
	virtual INT GetANDIDColumnCharWidth() CONST;
	virtual COLORREF GetANDIDColumnColor() CONST;
	virtual INT GetANDDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetANDDescriptionColumnColor() CONST;
	virtual INT GetANDValueColumnCharWidth() CONST;
	virtual COLORREF GetANDValueColumnColor() CONST;
	virtual INT GetANDUnitColumnCharWidth() CONST;
	virtual COLORREF GetANDUnitColumnColor() CONST;
	virtual INT GetANDChangeTMUnitColumnCharWidth() CONST;
	virtual COLORREF GetANDChangeTMUnitColumnColor() CONST;
	virtual INT GetANDUpdateTMUnitColumnCharWidth() CONST;
	virtual COLORREF GetANDUpdateTMUnitColumnColor() CONST;
	virtual INT GetANDChangeTimeColumnCharWidth() CONST;
	virtual COLORREF GetANDChangeTimeColumnColor() CONST;
	virtual INT GetANDUpdateTimeColumnCharWidth() CONST;
	virtual COLORREF GetANDUpdateTimeColumnColor() CONST;
	virtual INT GetANDExpectedValuesColumnCharWidth() CONST;
	virtual COLORREF GetANDExpectedValuesColumnColor() CONST;
	virtual INT GetGRDIDColumnCharWidth() CONST;
	virtual COLORREF GetGRDIDColumnColor() CONST;
	virtual INT GetGRDDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetGRDDescriptionColumnColor() CONST;
	virtual INT GetGRDValueColumnCharWidth() CONST;
	virtual COLORREF GetGRDValueColumnColor() CONST;
	virtual INT GetGRDUnitColumnCharWidth() CONST;
	virtual COLORREF GetGRDUnitColumnColor() CONST;
	virtual INT GetGRDRangeColumnCharWidth() CONST;
	virtual COLORREF GetGRDRangeColumnColor() CONST;
	virtual INT GetGRDLineColumnCharWidth() CONST;
	virtual INT GetGRDChangeTMUnitColumnCharWidth() CONST;
	virtual COLORREF GetGRDChangeTMUnitColumnColor() CONST;
	virtual INT GetGRDUpdateTMUnitColumnCharWidth() CONST;
	virtual COLORREF GetGRDUpdateTMUnitColumnColor() CONST;
	virtual INT GetGRDChangeTimeColumnCharWidth() CONST;
	virtual COLORREF GetGRDChangeTimeColumnColor() CONST;
	virtual INT GetGRDUpdateTimeColumnCharWidth() CONST;
	virtual COLORREF GetGRDUpdateTimeColumnColor() CONST;
	virtual INT GetOOLIDColumnCharWidth() CONST;
	virtual INT GetOOLDescriptionColumnCharWidth() CONST;
	virtual INT GetOOLValueColumnCharWidth() CONST;
	virtual INT GetOOLLimitColumnCharWidth() CONST;
	virtual INT GetOOLUnitColumnCharWidth() CONST;
	virtual INT GetOOLTypeColumnCharWidth() CONST;
	virtual INT GetOOLTMTimeColumnCharWidth() CONST;
	virtual INT GetOOLTMUnitColumnCharWidth() CONST;
	virtual INT GetPODIDColumnCharWidth() CONST;
	virtual INT GetPODDescriptionColumnCharWidth() CONST;
	virtual INT GetPODValueColumnCharWidth() CONST;
	virtual INT GetPODUnitColumnCharWidth() CONST;
	virtual INT GetPODTimeColumnCharWidth() CONST;
	virtual COLORREF GetPODFunctionsColor() CONST;
	virtual COLORREF GetPODParametersColor() CONST;
	virtual COLORREF GetPODExpressionColor() CONST;
	virtual INT GetTPEPIDColumnCharWidth() CONST;
	virtual COLORREF GetTPEPIDColumnColor() CONST;
	virtual INT GetTPEPDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetTPEPDescriptionColumnColor() CONST;
	virtual INT GetTPEPValueColumnCharWidth() CONST;
	virtual COLORREF GetTPEPValueColumnColor() CONST;
	virtual INT GetTPEPUnitColumnCharWidth() CONST;
	virtual COLORREF GetTPEPUnitColumnColor() CONST;
	virtual INT GetTPEPChangeTMUnitColumnCharWidth() CONST;
	virtual COLORREF GetTPEPChangeTMUnitColumnColor() CONST;
	virtual INT GetTPEPUpdateTMUnitColumnCharWidth() CONST;
	virtual COLORREF GetTPEPUpdateTMUnitColumnColor() CONST;
	virtual INT GetTPEPChangeTimeColumnCharWidth() CONST;
	virtual COLORREF GetTPEPChangeTimeColumnColor() CONST;
	virtual INT GetTPEPUpdateTimeColumnCharWidth() CONST;
	virtual COLORREF GetTPEPUpdateTimeColumnColor() CONST;
	virtual INT GetTCManualStackNumberColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackNumberColumnColor() CONST;
	virtual INT GetTCManualStackNameColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackNameColumnColor() CONST;
	virtual INT GetTCManualStackDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackDescriptionColumnColor() CONST;
	virtual INT GetTCManualStackCategoryColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackCategoryColumnColor() CONST;
	virtual INT GetTCManualStackSubSystemColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackSubSystemColumnColor() CONST;
	virtual INT GetTCManualStackArgumentsColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackArgumentsColumnColor() CONST;
	virtual INT GetTCManualStackFlagsColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackFlagsColumnColor() CONST;
	virtual INT GetTCManualStackTCPacketColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackTCPacketColumnColor() CONST;
	virtual INT GetTCManualStackDispatchTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackDispatchTimeColumnColor() CONST;
	virtual INT GetTCManualStackReleaseTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackReleaseTimeColumnColor() CONST;
	virtual INT GetTCManualStackReleaseTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackReleaseTimeOffsetColumnColor() CONST;
	virtual INT GetTCManualStackExecutionTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackExcutionTimeColumnColor() CONST;
	virtual INT GetTCManualStackExecutionTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackExcutionTimeOffsetColumnColor() CONST;
	virtual INT GetTCManualStackAuthorizationColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackAuthorizationColumnColor() CONST;
	virtual INT GetTCManualStackPTVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackPTVTimeWindowColumnColor() CONST;
	virtual INT GetTCManualStackPTVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackPTVChecksColumnColor() CONST;
	virtual INT GetTCManualStackPTVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackPTVResultColumnColor() CONST;
	virtual INT GetTCManualStackPEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackPEVChecksColumnColor() CONST;
	virtual INT GetTCManualStackPEVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackPEVResultColumnColor() CONST;
	virtual INT GetTCManualStackCEVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackCEVTimeWindowColumnColor() CONST;
	virtual INT GetTCManualStackCEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackCEVChecksColumnColor() CONST;
	virtual INT GetTCManualStackStatusColumnCharWidth() CONST;
	virtual COLORREF GetTCManualStackStatusColumnColor() CONST;
	virtual INT GetTCAutomaticStackNumberColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackNumberColumnColor() CONST;
	virtual INT GetTCAutomaticStackNameColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackNameColumnColor() CONST;
	virtual INT GetTCAutomaticStackDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackDescriptionColumnColor() CONST;
	virtual INT GetTCAutomaticStackCategoryColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackCategoryColumnColor() CONST;
	virtual INT GetTCAutomaticStackSubSystemColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackSubSystemColumnColor() CONST;
	virtual INT GetTCAutomaticStackArgumentsColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackArgumentsColumnColor() CONST;
	virtual INT GetTCAutomaticStackFlagsColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackFlagsColumnColor() CONST;
	virtual INT GetTCAutomaticStackTCPacketColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackTCPacketColumnColor() CONST;
	virtual INT GetTCAutomaticStackDispatchTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackDispatchTimeColumnColor() CONST;
	virtual INT GetTCAutomaticStackReleaseTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackReleaseTimeColumnColor() CONST;
	virtual INT GetTCAutomaticStackReleaseTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackReleaseTimeOffsetColumnColor() CONST;
	virtual INT GetTCAutomaticStackTransmissionTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackTransmissionTimeColumnColor() CONST;
	virtual INT GetTCAutomaticStackExecutionTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackExcutionTimeColumnColor() CONST;
	virtual INT GetTCAutomaticStackExecutionTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackExcutionTimeOffsetColumnColor() CONST;
	virtual INT GetTCAutomaticStackAuthorizationColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackAuthorizationColumnColor() CONST;
	virtual INT GetTCAutomaticStackPTVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackPTVTimeWindowColumnColor() CONST;
	virtual INT GetTCAutomaticStackPTVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackPTVChecksColumnColor() CONST;
	virtual INT GetTCAutomaticStackPTVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackPTVResultColumnColor() CONST;
	virtual INT GetTCAutomaticStackPEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackPEVChecksColumnColor() CONST;
	virtual INT GetTCAutomaticStackPEVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackPEVResultColumnColor() CONST;
	virtual INT GetTCAutomaticStackCEVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackCEVTimeWindowColumnColor() CONST;
	virtual INT GetTCAutomaticStackCEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackCEVChecksColumnColor() CONST;
	virtual INT GetTCAutomaticStackCEVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackCEVResultColumnColor() CONST;
	virtual INT GetTCAutomaticStackStatusColumnCharWidth() CONST;
	virtual COLORREF GetTCAutomaticStackStatusColumnColor() CONST;
	virtual INT GetTCProceduresMonitorNameColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorNameColumnColor() CONST;
	virtual INT GetTCProceduresMonitorDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorDescriptionColumnColor() CONST;
	virtual INT GetTCProceduresMonitorCommentsColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorCommentsColumnColor() CONST;
	virtual INT GetTCProceduresMonitorAuthorColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorAuthorColumnColor() CONST;
	virtual INT GetTCProceduresMonitorCreationTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorCreationTimeColumnColor() CONST;
	virtual INT GetTCProceduresMonitorModificationTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorModificationTimeColumnColor() CONST;
	virtual INT GetTCProceduresMonitorVerificationStatusColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorVerificationStatusColumnColor() CONST;
	virtual INT GetTCProceduresMonitorNumberOfThreadsColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorNumberOfThreadsColumnColor() CONST;
	virtual INT GetTCProceduresMonitorArgumentsColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorArgumentsColumnColor() CONST;
	virtual INT GetTCProceduresMonitorTriggerTypeColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorTriggerTypeColumnColor() CONST;
	virtual INT GetTCProceduresMonitorExecutionModeColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorExecutionModeColumnColor() CONST;
	virtual INT GetTCProceduresMonitorExecutionCountColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorExecutionCountColumnColor() CONST;
	virtual INT GetTCProceduresMonitorRunningStateColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorRunningStateColumnColor() CONST;
	virtual INT GetTCProceduresMonitorAcknowledgeRequestColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorAcknowledgeRequestColumnColor() CONST;
	virtual INT GetTCProceduresMonitorAckRequestTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorAckRequestTimeColumnColor() CONST;
	virtual INT GetTCProceduresMonitorPEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorPEVChecksColumnColor() CONST;
	virtual INT GetTCProceduresMonitorCEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorCEVChecksColumnColor() CONST;
	virtual INT GetTCProceduresMonitorStartTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorStartTimeColumnColor() CONST;
	virtual INT GetTCProceduresMonitorEndTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCProceduresMonitorEndTimeColumnColor() CONST;
	virtual INT GetTCDiagnosticsOversamplingDumpParametersNumberCharWidth() CONST;
	virtual COLORREF GetTCDiagnosticsOversamplingDumpParametersNumberColumnColor() CONST;
	virtual INT GetTCDiagnosticsOversamplingDumpParametersTimeCharWidth() CONST;
	virtual COLORREF GetTCDiagnosticsOversamplingDumpParametersTimeColumnColor() CONST;
	virtual INT GetTCDiagnosticsOversamplingDumpParametersValueCharWidth() CONST;
	virtual COLORREF GetTCDiagnosticsOversamplingDumpParametersValueColumnColor() CONST;
	virtual INT GetTCDiagnosticsOversamplingDumpParametersUnitCharWidth() CONST;
	virtual COLORREF GetTCDiagnosticsOversamplingDumpParametersUnitColumnColor() CONST;
	virtual INT GetTCDiagnosticsOversamplingDumpRawDataNumberCharWidth() CONST;
	virtual COLORREF GetTCDiagnosticsOversamplingDumpRawDataNumberColumnColor() CONST;
	virtual INT GetTCDiagnosticsOversamplingDumpRawDataTimeCharWidth() CONST;
	virtual COLORREF GetTCDiagnosticsOversamplingDumpRawDataTimeColumnColor() CONST;
	virtual INT GetTCDiagnosticsOversamplingDumpRawDataContentsCharWidth() CONST;
	virtual COLORREF GetTCDiagnosticsOversamplingDumpRawDataContentsColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesSummaryNameColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesSummaryNameColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesSummaryAPIDColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesSummaryAPIDColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesSummarySubScheduleIDColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesSummarySubScheduleIDColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesSummaryLimitColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesSummaryLimitColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesSummaryCountColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesSummaryCountColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesSummaryUpdateTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesSummaryUpdateTimeColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesSummaryStatusColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesSummaryStatusColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsNumberColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsNumberColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsNameColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsNameColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsComputerColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsComputerColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsCommandSourceColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsCommandSourceColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsDescriptionColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsCategoryColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsCategoryColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsSubSystemColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsSubSystemColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsArgumentsColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsArgumentsColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsFlagsColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsFlagsColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsTCPacketColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsTCPacketColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsPSCColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsPSCColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsDispatchTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsDispatchTimeColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsReleaseTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsReleaseTimeColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsReleaseTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsReleaseTimeOffsetColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsTransmissionTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsTransmissionTimeColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsExecutionTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsExcutionTimeColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsExecutionTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsExcutionTimeOffsetColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsAuthorizationColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsAuthorizationColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsPTVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsPTVTimeWindowColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsPTVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsPTVChecksColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsPTVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsPTVResultColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsPEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsPEVChecksColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsPEVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsPEVResultColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsCEVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsCEVTimeWindowColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsCEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsCEVChecksColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsCEVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsCEVResultColumnColor() CONST;
	virtual INT GetTCOnBoardBufferQueuesDetailsStatusColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardBufferQueuesDetailsStatusColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesProcessorColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesProcessorColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesAddressRangeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesAddressRangeColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesSizeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesSizeColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesPatchTCColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesPatchTCColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesLastPatchTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesLastPatchTimeColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesDumpTCColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesDumpTCColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesDumpTMColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesDumpTMColumnColor() CONST;
	virtual INT GetTCOnBoardMemoryImagesLastDumpTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCOnBoardMemoryImagesLastDumpTimeColumnColor() CONST;
	virtual INT GetTCHistoryNumberColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryNumberColumnColor() CONST;
	virtual INT GetTCHistoryNameColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryNameColumnColor() CONST;
	virtual INT GetTCHistoryComputerColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryComputerColumnColor() CONST;
	virtual INT GetTCHistoryCommandSourceColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryCommandSourceColumnColor() CONST;
	virtual INT GetTCHistoryDescriptionColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryDescriptionColumnColor() CONST;
	virtual INT GetTCHistoryCategoryColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryCategoryColumnColor() CONST;
	virtual INT GetTCHistorySubSystemColumnCharWidth() CONST;
	virtual COLORREF GetTCHistorySubSystemColumnColor() CONST;
	virtual INT GetTCHistoryArgumentsColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryArgumentsColumnColor() CONST;
	virtual INT GetTCHistoryFlagsColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryFlagsColumnColor() CONST;
	virtual INT GetTCHistoryTCPacketColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryTCPacketColumnColor() CONST;
	virtual INT GetTCHistoryDispatchTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryDispatchTimeColumnColor() CONST;
	virtual INT GetTCHistoryReleaseTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryReleaseTimeColumnColor() CONST;
	virtual INT GetTCHistoryReleaseTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryReleaseTimeOffsetColumnColor() CONST;
	virtual INT GetTCHistoryTransmissionTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryTransmissionTimeColumnColor() CONST;
	virtual INT GetTCHistoryExecutionTimeColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryExcutionTimeColumnColor() CONST;
	virtual INT GetTCHistoryExecutionTimeOffsetColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryExcutionTimeOffsetColumnColor() CONST;
	virtual INT GetTCHistoryAuthorizationColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryAuthorizationColumnColor() CONST;
	virtual INT GetTCHistoryPTVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryPTVTimeWindowColumnColor() CONST;
	virtual INT GetTCHistoryPTVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryPTVChecksColumnColor() CONST;
	virtual INT GetTCHistoryPTVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryPTVResultColumnColor() CONST;
	virtual INT GetTCHistoryPEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryPEVChecksColumnColor() CONST;
	virtual INT GetTCHistoryPEVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryPEVResultColumnColor() CONST;
	virtual INT GetTCHistoryCEVTimeWindowColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryCEVTimeWindowColumnColor() CONST;
	virtual INT GetTCHistoryCEVChecksColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryCEVChecksColumnColor() CONST;
	virtual INT GetTCHistoryCEVResultColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryCEVResultColumnColor() CONST;
	virtual INT GetTCHistoryStatusColumnCharWidth() CONST;
	virtual COLORREF GetTCHistoryStatusColumnColor() CONST;

public:
	virtual BOOL CreateTables(CDatabaseTableView *pView, ULONGLONG nComponent);
	virtual BOOL SaveTables(CDatabaseTableView *pView, ULONGLONG nComponent, BOOL bAll = FALSE, BOOL bPrompt = FALSE);
	virtual BOOL CanSaveTables(CONST CDatabaseTableView *pView, ULONGLONG nComponent) CONST;
	virtual BOOL CheckTables(CDatabaseTableView *pView, ULONGLONG nComponent, CStringArray &szIssues) CONST;
	virtual BOOL CanCheckTables(CONST CDatabaseTableView *pView, ULONGLONG nComponent) CONST;
	virtual BOOL ImportTables(CDatabaseTableView *pView, ULONGLONG nComponent, BOOL bCustom = FALSE);
	virtual BOOL CanImportTables(CONST CDatabaseTableView *pView, ULONGLONG nComponent, BOOL bCustom = FALSE) CONST;
	virtual BOOL ExportTables(CDatabaseTableView *pView, ULONGLONG nComponent, BOOL bCustom = FALSE);
	virtual BOOL CanExportTables(CONST CDatabaseTableView *pView, ULONGLONG nComponent, BOOL bCustom = FALSE) CONST;
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CDatabaseTMPackets &pDatabaseTMPackets);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CDatabaseTCFunctions &pDatabaseTCFunctions);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CDatabaseTCSequences &pDatabaseTCSequences);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CDatabaseOBProcessors &pDatabaseOBProcessors);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CDatabaseTMParameters &pDatabaseTMParameters);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CDatabaseTCParameters &pDatabaseTCParameters);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CANDLayouts &pANDLayouts);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CGRDLayouts &pGRDLayouts);
	virtual VOID UpdateTables(CDatabaseTableView *pView, CONST CPODLayouts &pPODLayouts);
	virtual BOOL UpdateTables(CDatabaseTableView *pView, ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete);
	virtual BOOL UpdateTables(CDatabaseTableView *pView, ULONGLONG nComponent, INT nID, BOOL bDelete);
	virtual VOID UpdateTables(CDatabaseTableView *pView, ULONGLONG nComponent);
	virtual VOID UpdateTables(CDatabaseTableView *pView);
	virtual VOID ArrangeTables(CDatabaseTableView *pView);
	virtual VOID ArrangeTables(CDatabaseTableView *pView, UINT nControlID);
	virtual BOOL DiscardTables(CDatabaseTableView *pView, ULONGLONG nComponent, BOOL bAll = FALSE);
	virtual BOOL CanDiscardTables(CONST CDatabaseTableView *pView, ULONGLONG nComponent, BOOL bAll = FALSE) CONST;
	virtual BOOL DeleteTables(CDatabaseTableView *pView, ULONGLONG nComponent);
	virtual BOOL CanDeleteTables(CONST CDatabaseTableView *pView, ULONGLONG nComponent) CONST;
	virtual BOOL DestroyTables(CDatabaseTableView *pView, ULONGLONG nComponent);

	virtual INT EnumTables(CONST CDatabaseTableView *pView, CStringArray &szTables, CUIntArray &nTypes, BOOL bMenu, BOOL bResetable = FALSE) CONST;
	virtual BOOL GetTableTitle(CONST CDatabaseTableView *pView, LPCTSTR pszTable, CString &szTitle) CONST;
	virtual BOOL GetTableLayout(CONST CDatabaseTableView *pView, LPCTSTR pszTable, CUIntArray &nWidths) CONST;
	virtual BOOL GetTableLayout(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszItem, CUIntArray &nWidths) CONST;
	virtual BOOL GetTablePosition(CONST CDatabaseTableView *pView, LPCTSTR pszTable, CString &szTable, CRect &rPosition) CONST;
	virtual BOOL GetTableOutline(CONST CDatabaseTableView *pView, LPCTSTR pszTable, COLORREF &nTitleRowColor, COLORREF &nFirstRowColor, COLORREF &nFirstColumnColor, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, INT &nOuterBorderSize, INT &nOuterBorderStyle, COLORREF &nOuterBorderColor, INT &nInnerBorderSize, INT &nInnerBorderStyle, COLORREF &nInnerBorderColor) CONST;
	virtual BOOL GetTableOutlineFonts(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST;
	virtual BOOL GetTableOutlineLimits(CONST CDatabaseTableView *pView, LPCTSTR pszTable, INT &nMinRows, INT &nMaxRows) CONST;
	virtual BOOL GetTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszItem, INT nRows, CStringArray &szContents, CStringArray &szDescriptions, CStringArray &szDataTypes, CUIntArray &nFormats, CUIntArray &nIDs, BOOL &bResize, BOOL &bVisible) CONST;
	virtual INT EnumTableFieldValues(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszField, CStringArray &szValues, CLongUIntArray &nValues) CONST;
	virtual BOOL GetTableFieldLimits(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszField, INT &nLow, INT &nHigh) CONST;
	virtual BOOL GetTableFieldLimits(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszField, UINT &uLow, UINT &uHigh) CONST;
	virtual BOOL GetTableFieldLimits(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszField, double &fLow, double &fHigh) CONST;
	virtual BOOL GetTableContext(CONST CDatabaseTableView *pView, LPCTSTR pszTable, CString &szTable, UINT &nControlID, CString &szValue) CONST;
	virtual INT EnumTableUpdates(CONST CDatabaseTableView *pView, UINT nControlID, CStringArray &szTables) CONST;
	virtual BOOL GetTableUpdateContents(CONST CDatabaseTableView *pView, LPCTSTR pszTable, UINT nControlID, LPCTSTR pszValue, CString &szItem, CStringArray &szContents) CONST;
	virtual BOOL UpdateTableFieldData(CDatabaseTableView *pView, UINT nControlID, LPCTSTR pszValue, LPCTSTR pszOldValue = NULL);
	virtual INT InsertTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL InsertTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, INT nRow, INT nCol = -1);
	virtual BOOL CheckTableFieldData(CONST CDatabaseTableView *pView, LPCTSTR pszTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableFieldData(CONST CDatabaseTableView *pView, LPCTSTR pszTable, CStringArray &szIssues) CONST;
	virtual BOOL SelectTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, CONST POINT &pt);
	virtual BOOL SelectTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL SaveTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, BOOL bPrompt = FALSE);
	virtual BOOL ProtectTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, BOOL bUndo = FALSE);
	virtual BOOL DeleteTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable);
	virtual INT DeleteTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL DeleteTableFieldData(CDatabaseTableView *pView, LPCTSTR pszTable, INT nRow, INT nCol = -1);
	virtual BOOL GetTableFieldFlag(CONST CDatabaseTableView *pView, LPCTSTR pszTable, INT nRow, INT nCol, CString &szFlag) CONST;
	virtual INT EnumTableDropTargets(CONST CDatabaseTableView *pView, ULONGLONG nComponent, CStringArray &szTables, CStringArray &szFields) CONST;
	virtual BOOL FindTableDropTargetCell(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszField, ULONGLONG nComponent, LPCTSTR pszItem, CString &szItem, INT &nRow, INT &nCol) CONST;
	virtual INT EnumPrintTables(CONST CDatabaseTableView *pView, LPCTSTR pszTable, UINT nFlags, CStringArray &szTables) CONST;
	virtual BOOL GetPrintTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszItem, CStringArray &szContents) CONST;
	virtual BOOL PrintTable(CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszItem, CMetaFileDC &cMetaDC);
	virtual ULONGLONG TranslateTableNameToComponent(CONST CDatabaseTableView *pView, LPCTSTR pszTable) CONST;
	virtual CString TranslateComponentToTableName(CONST CDatabaseTableView *pView, ULONGLONG nComponent) CONST;
	virtual INT TranslateTableFieldToIndex(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszField) CONST;
	virtual UINT TranslateTableFieldToID(CONST CDatabaseTableView *pView, LPCTSTR pszTable, LPCTSTR pszField) CONST;
	virtual BOOL IsTableFieldID(CONST CDatabaseTableView *pView, LPCTSTR pszTable, UINT nControlID) CONST;

public:
	virtual INT EnumDBMSTables(CStringArray &szTables, CStringArray &szDescriptions) CONST;
	virtual BOOL GetDBMSTableCharacteristics(LPCTSTR pszTable, CStringArray &szColumns, CStringArray &szDataTypes, CStringArray &szDefaults, CByteArray &bAllowNulls) CONST;

	virtual BOOL UsesDBMSTables(ULONGLONG nComponent) CONST;

protected:
	CString ConstructDBMSTableDefaultStringValue(LPCTSTR pszValue) CONST;
	CString ConstructDBMSTableDefaultNumericValue(LONGLONG nValue) CONST;
	CString ConstructDBMSTableDefaultRealValue(double fValue) CONST;

public:
	static BOOL TranslateParameterTypeCode(INT nPTC, INT nPFC, BOOL bTC, ULONGLONG &nAttributes, INT &nWidth);
	static CString TranslateParameterTypeCode(INT nPTC, INT nPFC, BOOL bTC);
	static CString TranslateParameterTypeCode(ULONGLONG nAttributes, BOOL bTC);

	static BOOL ParseValue(LPCTSTR pszValue, ULONGLONG &nValue);
	static BOOL ParseValue(LPCTSTR pszValue, UINT nRadix, ULONGLONG &nValue);
	static BOOL ParseValue(LPCTSTR pszValue, UINT nRadix, ULONGLONG &nValue, BOOL &bSign);
	static ULONGLONG ParseValue(LPCTSTR pszValue, UINT nRadix);
	static BOOL ParseValue(LPCTSTR pszValue, double &fValue);
	static double ParseValue(LPCTSTR pszValue);
	static TIMETAG ParseTime(LPCTSTR pszTime, BOOL bAbsolute = TRUE);
	static TIMETAG ParseTime(CONST CByteArray &nCode, INT nPTC, INT nPFC);
	static BOOL ParseTime(TIMETAG tTime, INT nPTC, INT nPFC, CByteArray &nCode);

	static ULONGLONG EncodeValue(UINT nType, ULONGLONG nAttributes, INT nWidth, ULONGLONG nValue, BOOL bTC = TRUE);
	static ULONGLONG EncodeValue(UINT nType, ULONGLONG nAttributes, double fValue, BOOL bTC = TRUE);
	static ULONGLONG DecodeValue(UINT nType, ULONGLONG nAttributes, INT nWidth, ULONGLONG nCode, BOOL bTC = TRUE);
	static double DecodeValue(UINT nType, ULONGLONG nAttributes, ULONGLONG nCode, BOOL bTC = TRUE);
	static ULONGLONG EncodeTime(TIMETAG tTime);
	static TIMETAG DecodeTime(ULONGLONG nCode);

protected:
	static BOOL EncodeValue(ULONGLONG nValue, INT nWidth, BOOL bAppend, CByteArray &nCode);

public:
	BOOL ShowMessage(CONST EVENT_DESCRIPTOR nMessageID);
	BOOL ShowMessage(LPCTSTR pszMessage, BOOL bAudition = TRUE);

	BOOL ShowHelp(LPCTSTR pszTopic);

public:
	CString Required(CONST CTableViewCell *pCell = NULL) CONST;
	CString Optional(CONST CTableViewCell *pCell = NULL) CONST;
	CString NotApplicable() CONST;

	CString Char(INT nChars) CONST;
	CString Varchar(INT nChars) CONST;
	CString Text() CONST;
	CString Integer() CONST;
	CString BigInt() CONST;
	CString SmallInt() CONST;
	CString TinyInt() CONST;
	CString Float() CONST;
	CString Real() CONST;
	CString Double() CONST;
	CString Numeric(INT nDigits, INT nPrecision) CONST;
	CString Decimal(INT nDigits, INT nPrecision) CONST;
	CString Binary(INT nDigits) CONST;
	CString Varbinary(INT nDigits) CONST;
	CString Bit() CONST;
	CString Date() CONST;
	CString Time() CONST;
	CString Timestamp() CONST;

public:
	CDatabaseEngine *GetDatabaseEngine() CONST;
	CDatabase *GetDBMS() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabases

class AFX_EXT_CLASS CDatabases : public CRegistry
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL SetDatabases(CONST CDatabaseProfiles &pDatabases);
	BOOL GetDatabases(CDatabaseProfiles &pDatabases, BOOL bAll = FALSE) CONST;

	INT EnumDatabases(CStringArray &szDatabases, BOOL bAll = FALSE) CONST;
	BOOL DeleteDatabases();

private:
	CString QuerySubKey() CONST;
	BOOL SecureSubKey(LPCTSTR pszSubKey);
	BOOL DeleteSubKey(LPCTSTR pszSubKey);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DATABASE_H__
