// TTCPROCESS.H : TT&C Data Processing Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telemetry and telecommand data
// processing related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TTCPROCESS_H__
#define __TTCPROCESS_H__

#include "mutex.h"
#include "timekey.h"
#include "database.h"


/////////////////////////////////////////////////////////////////////////////
// CTMUnit

// Specify the telemetry unit related identifiers
#define TMUNIT_DATAQUALITY_NONE   0
#define TMUNIT_DATAQUALITY_GOOD   (1<<0)
#define TMUNIT_DATAQUALITY_BAD   (1<<1)
#define TMUNIT_SEQUENCEQUALITY_GOOD   (1<<2)
#define TMUNIT_SEQUENCEQUALITY_BAD   (1<<3)
#define TMUNIT_TIMECORRELATION_GOOD   (1<<4)
#define TMUNIT_TIMECORRELATION_BAD   (1<<5)

class AFX_EXT_CLASS CTMUnit : public CObject
{
	DECLARE_DYNCREATE(CTMUnit)

	// Construction
public:
	CTMUnit();
	CTMUnit(LPCTSTR pszTag);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbData;
		UINT  nUnitID;
		WORD  wQuality;
		TIMETAG  tTimeTag;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szTag;
	CTimeTag  m_tTimeTag;
	CTimeSpan  m_tRetention;
	CByteArray  m_nData[2];
	WORD  m_wQuality;
	UINT  m_nUnitID;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag = NULL);
	CString GetTag() CONST;
	VOID SetTimeTag(CONST CTimeTag &tTimeTag);
	CTimeTag GetTimeTag() CONST;
	VOID SetUnitID(UINT nID);
	UINT GetUnitID() CONST;
	VOID SetQuality(WORD wCode);
	WORD GetQuality() CONST;

	BOOL SetData(CONST CByteArray &nData, BOOL bExtra = FALSE);
	INT GetData(CByteArray &nData, BOOL bExtra = FALSE) CONST;
	BOOL GetData(INT nBytePos, BYTE &nValue) CONST;
	BOOL GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue, BOOL bLittleEndian = FALSE) CONST;

	INT GetSize() CONST;

	BOOL IsValid() CONST;
	BOOL IsUnknown() CONST;
	BOOL HasBadData() CONST;

	VOID SetRetention(CONST CTimeSpan &tRetention);
	CTimeSpan GetRetention() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

public:
	virtual VOID Reset();

	virtual VOID Copy(CONST CTMUnit *pTMUnit);
	virtual BOOL Compare(CONST CTMUnit *pTMUnit) CONST;

protected:
	BOOL Extract(CONST CByteArray &nData, INT nBytePos, BYTE &nValue) CONST;
	BOOL Extract(CONST CByteArray &nData, INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue, BOOL bLittleEndian = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMUnits

class AFX_EXT_CLASS CTMUnits : public CPtrArray
{
	// Construction
public:
	CTMUnits();
	~CTMUnits();

	// Attributes
public:

	// Operations
public:
	INT Add(CTMUnit *pTMUnit);

	INT Find(CONST CTimeTag &tTimeTag) CONST;

	CTMUnit *GetAt(INT nIndex) CONST;
	CTMUnit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTMUnits *pTMUnits);
	BOOL Compare(CONST CTMUnits *pTMUnits) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(CONST CTimeTag &tTimeTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMUnitCache

class AFX_EXT_CLASS CTMUnitCache : public CTMUnits
{
	// Construction
public:
	CTMUnitCache();
	~CTMUnitCache();

	// Attributes
private:
	CStringArray  m_szRetentions;

	// Operations
public:
	INT Add(CTMUnit *pTMUnit);

	INT Find(LPCTSTR pszTag) CONST;

	VOID SetRetention(LPCTSTR pszTag, CONST CTimeSpan &tRetention);
	CTimeSpan GetRetention(LPCTSTR pszTag) CONST;
	VOID RemoveAllRetentions();

	BOOL Copy(CONST CTMUnitCache *pCache);
	BOOL Compare(CONST CTMUnitCache *pCache) CONST;

	BOOL Map(CByteArray &nInfo, CONST CTimeTag &tRetention = -1) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention = -1);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMPacket

// Specify the telemetry packet related identifiers
#define TMPACKET_TYPE   0x00
#define TMPACKET_VERSION   0x04
#define TMPACKET_FLAG_DATAFIELDHEADER   0x01
#define TMPACKET_FLAG_NODATAFIELDHEADER   0x00
#define TMPACKET_SEGMENTATIONFLAG_NONE   0x03
#define TMPACKET_SEGMENTATIONFLAG_FIRST   0x01
#define TMPACKET_SEGMENTATIONFLAG_NEXT   0x00
#define TMPACKET_SEGMENTATIONFLAG_LAST   0x02
// Specify the telemetry packet related sizes
#define TMPACKET_HEADER_SIZE   6
#define TMPACKET_MINIMUM_SIZE   (TMPACKET_HEADER_SIZE+1)
#define TMPACKET_MAXIMUM_SIZE   65542

class AFX_EXT_CLASS CTMPacket : public CTMUnit
{
	DECLARE_DYNCREATE(CTMPacket)

	// Construction
public:
	CTMPacket();
	CTMPacket(LPCTSTR pszTag);

	// Attributes
private:
	INT  m_nTMTypePos[3];
	INT  m_nTMIDPos[3];
	INT  m_n3DiscPos[3];
	INT  m_nTimestampPos[3];
	INT  m_nVirtualChannel;

	// Operations
public:
	VOID SetTMTypePosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTMTypePosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTMIDPosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTMIDPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID Set3DiscPosition(INT nByte, INT nBit, INT nLength);
	BOOL Get3DiscPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetTimestampPosition(INT nByte, INT nBit, INT nLength);
	BOOL GetTimestampPosition(INT &nByte, INT &nBit, INT &nLength) CONST;
	VOID SetVirtualChannel(INT nChannel);
	INT GetVirtualChannel() CONST;

public:
	INT GetType() CONST;
	INT GetAPID() CONST;
	INT GetTMType() CONST;
	INT GetTMID() CONST;
	INT Get3Disc() CONST;
	INT GetVersion() CONST;
	INT GetSequenceFlags() CONST;
	INT GetSequenceCount() CONST;
	INT GetDataFieldLength() CONST;
	UINT GetTimestamp() CONST;
	BOOL HasHeader() CONST;
	BOOL HasDataFieldHeader() CONST;
	BOOL HasTimestamp() CONST;

	INT GetData(CByteArray &nData, BOOL bExtra = FALSE) CONST;
	BOOL GetData(INT nBytePos, BYTE &nValue) CONST;
	BOOL GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue, BOOL bLittleEndian = FALSE) CONST;

public:
	virtual VOID Reset();

	virtual VOID Copy(CONST CTMUnit *pTMUnit);
	virtual BOOL Compare(CONST CTMUnit *pTMUnit) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMTransferUnit

class AFX_EXT_CLASS CTMTransferUnit : public CTMUnit
{
	DECLARE_DYNCREATE(CTMTransferUnit)

	// Construction
public:
	CTMTransferUnit();

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMTransferUnits

class AFX_EXT_CLASS CTMTransferUnits : public CPtrArray
{
	// Construction
public:
	CTMTransferUnits();
	~CTMTransferUnits();

	// Attributes
public:

	// Operations
public:
	INT Add(CTMTransferUnit *pTMTransferUnit);

	INT Find(LPCTSTR pszTag, INT nIndex = -1) CONST;
	INT Find(CONST CTimeTag &tTimeTag) CONST;

	CTMTransferUnit *GetAt(INT nIndex) CONST;
	CTMTransferUnit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTMTransferUnits *pTMTransferUnits);
	BOOL Compare(CONST CTMTransferUnits *pTMTransferUnits) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(CONST CTimeTag &tTimeTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMTransferFrame

// Specify the telemetry transfer frame related identifiers
#define TMTRANSFERFRAME_SYNCPATTERN   0x1ACFFC1D
#define TMTRANSFERFRAME_VERSION   0x00
#define TMTRANSFERFRAME_SYNCHRONOUSDATA   0x00
#define TMTRANSFERFRAME_ASYNCHRONOUSDATA   0x01
#define TMTRANSFERFRAME_FORWARDPACKETORDER   0x00
#define TMTRANSFERFRAME_REVERSEPACKETORDER   0x01
#define TMTRANSFERFRAME_IDLESTATE   0x03FE
#define TMTRANSFERFRAME_EMPTYSTATE   0x03FF
// Specify the telemetry transfer frame related sizes
#define TMTRANSFERFRAME_SYNCMARKER_SIZE   4
#define TMTRANSFERFRAME_PRIMARYHEADER_SIZE   6
#define TMTRANSFERFRAME_SECONDARYHEADER_SIZE   4
#define TMTRANSFERFRAME_TRAILER_SIZE   2
#define TMTRANSFERFRAME_MINIMUM_SIZE   (TMTRANSFERFRAME_PRIMARYHEADER_SIZE+1)
#define TMTRANSFERFRAME_MAXIMUM_SIZE   65536

class AFX_EXT_CLASS CTMTransferFrame : public CTMTransferUnit
{
	DECLARE_DYNCREATE(CTMTransferFrame)

	// Construction
public:
	CTMTransferFrame();

	// Attributes
public:

	// Operations
public:
	UINT GetSyncMarker() CONST;
	BYTE GetVersion() CONST;
	UINT GetSpacecraftID() CONST;
	BYTE GetVirtualChannel() CONST;
	BOOL GetOperationalControlFieldFlag() CONST;
	BYTE GetMasterChannelFrameCounter() CONST;
	UINT GetVirtualChannelFrameCounter() CONST;
	UINT GetFirstHeaderPointer() CONST;
	BOOL GetSynchronizationFlag() CONST;
	BYTE GetSegmentationFlag() CONST;
	BOOL GetPacketOrderFlag() CONST;
	BOOL GetSecondaryHeaderFlag() CONST;
	BYTE GetSecondaryHeaderVersion() CONST;
	BYTE GetSecondaryHeaderLength() CONST;
	UINT GetSecondaryHeaderData() CONST;
	BOOL GetFrameData(CTMPacket *pTMPacket) CONST;
	INT GetFrameData(CByteArray &nData) CONST;
	INT GetFrameTrailer(CByteArray &nData) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCUnit

class AFX_EXT_CLASS CTCUnit : public CObject
{
	DECLARE_DYNCREATE(CTCUnit)

	// Construction
public:
	CTCUnit();
	CTCUnit(LPCTSTR pszTag);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbData;
		TIMETAG  tTimeTag;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szTag;
	CTimeTag  m_tTimeTag;
	CByteArray  m_nData[2];

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetTimeTag(CONST CTimeTag &tTimeTag);
	CTimeTag GetTimeTag() CONST;
	VOID SetSize(INT nSize, BOOL bReset = TRUE);
	INT GetSize() CONST;

	BOOL SetData(CONST CByteArray &nData, BOOL bExtra = FALSE);
	BOOL SetData(BYTE nValue, INT nBytePos);
	BOOL SetData(ULONGLONG nValue, INT nBytePos, INT nBitPos, INT nLength);
	INT GetData(CByteArray &nData, BOOL bExtra = FALSE) CONST;
	BOOL GetData(INT nBytePos, BYTE &nValue) CONST;
	BOOL GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST;

	BOOL IsValid() CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

public:
	virtual VOID Reset();

	virtual VOID Copy(CONST CTCUnit *pTCUnit);
	virtual BOOL Compare(CONST CTCUnit *pTCUnit) CONST;

protected:
	BOOL Collect(CByteArray &nData, BYTE nValue, INT nBytePos) CONST;
	BOOL Collect(CByteArray &nData, ULONGLONG nValue, INT nBytePos, INT nBitPos, INT nLength) CONST;
	BOOL Extract(CONST CByteArray &nData, INT nBytePos, BYTE &nValue) CONST;
	BOOL Extract(CONST CByteArray &nData, INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCUnits

class AFX_EXT_CLASS CTCUnits : public CPtrArray
{
	// Construction
public:
	CTCUnits();
	~CTCUnits();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCUnit *pTCUnit);

	INT Find(CONST CTimeTag &tTimeTag) CONST;

	CTCUnit *GetAt(INT nIndex) CONST;
	CTCUnit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCUnits *pTCUnits);
	BOOL Compare(CONST CTCUnits *pTCUnits) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(CONST CTimeTag &tTimeTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCPacket

// Specify the telecommand packet related identifiers
#define TCPACKET_TYPE   0x01
#define TCPACKET_VERSION   0x00
#define TCPACKET_FLAG_DATAFIELDHEADER   0x01
#define TCPACKET_FLAG_NODATAFIELDHEADER   0x00
#define TCPACKET_SEQUENCEFLAG_NONE   0x03
#define TCPACKET_SEQUENCEFLAG_FIRST   0x01
#define TCPACKET_SEQUENCEFLAG_NEXT   0x00
#define TCPACKET_SEQUENCEFLAG_LAST   0x02
#define TCPACKET_TCTYPE_IMMEDIATE   0x00
#define TCPACKET_TCTYPE_FIRSTSTEP   0x01
#define TCPACKET_TCTYPE_SECONDSTEP   0x02
#define TCPACKET_TCTYPE_TIMETAG   0x03
#define TCPACKET_TFIELDTIMECODE   0x2D
#define TCPACKET_FLAG_CUCTIMETAG   0x02
#define TCPACKET_FLAG_NOCUCTIMETAG   0x00
#define TCPACKET_FLAG_CRC   0x01
#define TCPACKET_FLAG_NOCRC   0x00
// Specify the telecommand packet related sizes
#define TCPACKET_HEADER_SIZE   6
#define TCPACKET_MINIMUM_SIZE   (TCPACKET_HEADER_SIZE+1)
#define TCPACKET_MAXIMUM_SIZE   65542

class AFX_EXT_CLASS CTCPacket : public CTCUnit
{
	DECLARE_DYNCREATE(CTCPacket)

	// Construction
public:
	CTCPacket();
	CTCPacket(LPCTSTR pszTag);

	// Attributes
private:
	BYTE  m_nMapID;
	BOOL  m_bControlFrame;
	BOOL  m_bControlSegment;
	BOOL  m_bSLEThrowEvent;
	BOOL  m_bNISThrowEvent;

	// Operations
public:
	BOOL SetType(INT nType);
	INT GetType() CONST;
	BOOL SetAPID(INT nAPID);
	INT GetAPID() CONST;
	BOOL SetTCID(INT nTCID);
	INT GetTCID() CONST;
	BOOL SetTCType(INT nTCType);
	INT GetTCType() CONST;
	BOOL SetVersion(INT nVersion);
	INT GetVersion() CONST;
	BOOL SetDataFieldHeaderFlag(INT nFlag);
	INT GetDataFieldHeaderFlag() CONST;
	BOOL SetSequenceFlags(INT nFlags);
	INT GetSequenceFlags() CONST;
	BOOL SetSequenceCount(INT nCount);
	INT GetSequenceCount() CONST;
	BOOL SetCUCTimeTagFlag(INT nFlag);
	INT GetCUCTimeTagFlag() CONST;
	BOOL SetCUCTimeTag(UINT nTimeTag);
	UINT GetCUCTimeTag() CONST;
	BOOL SetCRCFlag(INT nFlag);
	INT GetCRCFlag() CONST;
	BOOL SetSize(INT nSize, BOOL bReset = TRUE);
	INT GetSize() CONST;

	BOOL HasHeader() CONST;
	BOOL HasDataFieldHeader() CONST;

	BOOL SetData(CONST CByteArray &nData, BOOL bExtra = FALSE);
	BOOL SetData(BYTE nValue, INT nBytePos);
	BOOL SetData(ULONGLONG nValue, INT nBytePos, INT nBitPos, INT nLength);
	INT GetData(CByteArray &nData, BOOL bExtra = FALSE) CONST;
	BOOL GetData(INT nBytePos, BYTE &nValue) CONST;
	BOOL GetData(INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST;

	VOID SetMapID(BYTE nMapID);
	BYTE GetMapID() CONST;
	VOID MarkAsControlFrame(BOOL bEnable = TRUE);
	BOOL IsControlFrame() CONST;
	VOID MarkAsControlSegment(BOOL bEnable = TRUE);
	BOOL IsControlSegment() CONST;
	VOID MarkAsSLEThrowEvent(BOOL bEnable = TRUE);
	BOOL IsSLEThrowEvent() CONST;
	VOID MarkAsNISThrowEvent(BOOL bEnable = TRUE);
	BOOL IsNISThrowEvent() CONST;

public:
	virtual VOID Reset();

	virtual VOID Copy(CONST CTCUnit *pTCUnit);
	virtual BOOL Compare(CONST CTCUnit *pTCUnit) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCTransferUnit

class AFX_EXT_CLASS CTCTransferUnit : public CTCUnit
{
	DECLARE_DYNCREATE(CTCTransferUnit)

	// Construction
public:
	CTCTransferUnit();

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCTransferUnits

class AFX_EXT_CLASS CTCTransferUnits : public CPtrArray
{
	// Construction
public:
	CTCTransferUnits();
	~CTCTransferUnits();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCTransferUnit *pTCTransferUnit);

	CTCTransferUnit *GetAt(INT nIndex) CONST;
	CTCTransferUnit *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCTransferUnits *pTCTransferUnits);
	BOOL Compare(CONST CTCTransferUnits *pTCTransferUnits) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCTransferFrame

// Specify the telecommand transfer frame related identifiers
#define TCTRANSFERFRAME_VERSION   0x00
#define TCTRANSFERFRAME_ADSERVICEMODE   0x00
#define TCTRANSFERFRAME_BDSERVICEMODE   0x02
#define TCTRANSFERFRAME_BCSERVICEMODE   0x03
// Specify the telecommand transfer frame related sizes
#define TCTRANSFERFRAME_HEADER_SIZE   5
#define TCTRANSFERFRAME_TRAILER_SIZE   2
#define TCTRANSFERFRAME_MINIMUM_SIZE   (TCTRANSFERFRAME_HEADER_SIZE+TCTRANSFERFRAME_TRAILER_SIZE+1)
#define TCTRANSFERFRAME_MAXIMUM_SIZE   256

class AFX_EXT_CLASS CTCTransferFrame : public CTCTransferUnit
{
	DECLARE_DYNCREATE(CTCTransferFrame)

	// Construction
public:
	CTCTransferFrame();

	// Attributes
public:

	// Operations
public:
	BOOL SetVersion(BYTE nVersion);
	BYTE GetVersion() CONST;
	BOOL SetBypassFlag(BOOL bFlag);
	BOOL GetBypassFlag() CONST;
	BOOL SetControlCommandFlag(BOOL bFlag);
	BOOL GetControlCommandFlag() CONST;
	BOOL SetSpacecraftID(UINT nID);
	UINT GetSpacecraftID() CONST;
	BOOL SetVirtualChannel(BYTE nChannel);
	BYTE GetVirtualChannel() CONST;
	BOOL SetFrameLength(BYTE nLength, BOOL bReset = TRUE);
	BYTE GetFrameLength() CONST;
	BOOL SetFrameSequenceNumber(BYTE nNumber);
	BYTE GetFrameSequenceNumber() CONST;
	BOOL SetFrameData(CONST CTCPacket *pTCPacket);
	BOOL SetFrameData(CONST CByteArray &nData);
	BOOL GetFrameData(CTCPacket *pTCPacket) CONST;
	INT GetFrameData(CByteArray &nData) CONST;
	BOOL SetFrameErrorControlWord(WORD wFECW);
	WORD GetFrameErrorControlWord() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCTransferFrames

class AFX_EXT_CLASS CTCTransferFrames : public CPtrArray
{
	// Construction
public:
	CTCTransferFrames();
	~CTCTransferFrames();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCTransferFrame *pTCTransferFrame);

	CTCTransferFrame *GetAt(INT nIndex) CONST;
	CTCTransferFrame *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCTransferFrames *pTCTransferFrames);
	BOOL Compare(CONST CTCTransferFrames *pTCTransferFrames) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMParameter

// Specify the telemetry parameter status related identifiers
#define TMPARAMETER_STATUS_NONE   0
#define TMPARAMETER_STATUS_GOOD   (1<<0)
#define TMPARAMETER_STATUS_BAD   (1<<1)
#define TMPARAMETER_STATUS_NOLIMIT   (1<<2)
#define TMPARAMETER_STATUS_SOFTLIMIT   (1<<3)
#define TMPARAMETER_STATUS_HARDLIMIT   (1<<4)
#define TMPARAMETER_STATUS_DELTALIMIT   (1<<5)
#define TMPARAMETER_STATUS_CONSISTENCYLIMIT   (1<<6)
#define TMPARAMETER_STATUS_EVENTLIMIT   (1<<7)
#define TMPARAMETER_STATUS_VALID   (1<<8)
#define TMPARAMETER_STATUS_INVALID   (1<<9)
// Specify the telemetry parameter out-of-limit flag related identifiers
#define TMPARAMETER_OOLFLAG_NONE   0
#define TMPARAMETER_OOLFLAG_CONSISTENCY   (1<<0)
#define TMPARAMETER_OOLFLAG_EVENT   (1<<1)
#define TMPARAMETER_OOLFLAG_NOEVENT   (1<<2)
// Specify the telemetry parameter derivation procedure type
typedef VOID(__cdecl *DERIVATIONPROCEDURE)(CONST CDatabaseEngine *, CONST class CTMEnvironment *);

class AFX_EXT_CLASS CTMParameter : public CObject
{
	// Construction
public:
	CTMParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize[2];
		INT  cbTag;
		INT  cbValues[2];
		INT  cbPacket[3];
		INT  cbCalTables;
		INT  cbStatus;
		INT  nOolCount;
		WORD  wOolInfo[2];
		WORD  wPastSamples[2];
		TIMETAG  tPacket[3];
	} DATA, *PDATA, *LPDATA;
private:
	DERIVATIONPROCEDURE  m_pDerivationProcedure;
protected:
	CString  m_szTag;
	CString  m_szPacket[2];
	CTimeTag  m_tPacket[2];
	CTimeSpan  m_tRetention;
	CStringArray  m_szCalTables;
	CLongUIntArray  m_nValues;
	CTimeTagArray  m_tValues;
	CUIntArray  m_nStatus;
	ULONGLONG  m_nAttributes;
	WORD  m_wPastSamples[2];
protected:
	CString  m_szOolUnit;
	CTimeTag  m_tOolTime;
	WORD  m_wOolInfo[2];
	UINT  m_nOolFlags;
	INT  m_nOolCount;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;

	VOID Initialize(CTMParameter *pTMParameter, BOOL bBadData = FALSE);
	BOOL IsInitialized() CONST;

	BOOL Update(CONST CTMParameter *pTMParameter);
	BOOL Update(CONST CTMParameter *pTMParameter, BOOL bBadData);

	VOID Reset();

	BOOL SetRawValue(CONST CTMUnit *pTMUnit, INT nSample, ULONGLONG nRawValue, UINT nStatus = TMPARAMETER_STATUS_NONE, LPCTSTR pszCalTable = NULL);
	BOOL GetRawValue(INT nSample, ULONGLONG &nRawValue, UINT &nStatus, CString &szCalTable, BOOL bPast = FALSE) CONST;
	BOOL GetRawValue(INT nSample, ULONGLONG &nRawValue, UINT &nStatus, BOOL bPast = FALSE) CONST;

	BOOL Calibrate(CONST CDatabaseEngine *pDatabase, ULONGLONG nFlags, ULONGLONG nRawValue, LPCTSTR pszCalTable, double &fValue, BOOL &bOut) CONST;

	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue, BOOL bPast = FALSE) CONST;
	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue, BOOL &bOut, BOOL bPast = FALSE) CONST;
	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue, BOOL bPast = FALSE) CONST;
	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue, BOOL &bOut, BOOL bPast = FALSE) CONST;

	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue, BOOL bPast = FALSE) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue, BOOL &bOut, BOOL bPast = FALSE) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue, BOOL bPast = FALSE) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue, BOOL &bOut, BOOL bPast = FALSE) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue, BOOL bPast = FALSE) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue, BOOL &bOut, BOOL bPast = FALSE) CONST;

	CTimeTag GetValueTime(INT nSample, BOOL bPast = FALSE) CONST;

	INT GetValueCount() CONST;

	VOID SetPastValueSamples(WORD wSamples);
	WORD GetPastValueSamples() CONST;
	BOOL GetPastRawValue(INT nSample, ULONGLONG &nValue, UINT &nStatus) CONST;
	BOOL GetPastValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue) CONST;
	BOOL GetPastValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue) CONST;
	INT GetPastValueCount() CONST;

	VOID SetOolInfo();
	VOID SetOolInfo(LPCTSTR pszUnit, CONST CTimeTag &tUnit, WORD wTable, WORD wLimit);
	BOOL GetOolInfo(CString &szUnit, CTimeTag &tUnit, WORD &wTable, WORD &wLimit) CONST;
	VOID SetOolFlags(UINT nFlags = TMPARAMETER_OOLFLAG_NONE);
	UINT GetOolFlags() CONST;
	VOID SetOolCount(INT nCount = 0);
	INT GetOolCount() CONST;

	BOOL SetOolStatus(INT nSample, UINT nStatus);
	UINT GetOolStatus(INT nSample) CONST;
	BOOL SetValidityStatus(UINT nStatus);
	UINT GetValidityStatus() CONST;

	VOID SetRetention(CONST CTimeSpan &tRetention);
	CTimeSpan GetRetention() CONST;

	CString GetLastChangeTMUnit() CONST;
	CString GetLastUpdateTMUnit() CONST;
	CTimeTag GetLastChangeTime() CONST;
	CTimeTag GetLastUpdateTime() CONST;

	VOID SetDerivationProcedure(DERIVATIONPROCEDURE pDerivationProcedure);
	DERIVATIONPROCEDURE GetDerivationProcedure() CONST;

	BOOL Copy(CONST CTMParameter *pTMParameter);
	BOOL Compare(CONST CTMParameter *pTMParameter) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMParameters

class AFX_EXT_CLASS CTMParameters : public CPtrArray
{
	// Construction
public:
	CTMParameters();
	~CTMParameters();

	// Attributes
public:

	// Operations
public:
	BOOL Create(CONST CDatabaseEngine *pDatabase);

	BOOL Update(CONST CDatabaseEngine *pDatabase, CONST CTMUnit *pTMUnit, CONST CTMParameters *pTMParameters, BOOL bBadData = FALSE);

	INT Add(CTMParameter *pTMParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CTMParameter *GetAt(INT nIndex) CONST;
	CTMParameter *operator[](INT nIndex) CONST;

	VOID Reset();

	VOID RemoveAll();

	BOOL Copy(CONST CTMParameters *pTMParameters);
	BOOL Compare(CONST CTMParameters *pTMParameters) CONST;

	BOOL Map(CByteArray &nInfo, CONST CTimeTag &tRetention = -1, BOOL bAll = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention = -1, BOOL bAll = FALSE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COolParameter

class AFX_EXT_CLASS COolParameter : public CTMParameter
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	VOID SetOolTMUnit(LPCTSTR pszUnit);
	CString GetOolTMUnit() CONST;
	VOID SetOolTime(CONST CTimeTag &tTime);
	CTimeTag GetOolTime() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COolParameters

class AFX_EXT_CLASS COolParameters : public CTMParameters
{
	// Construction
public:
	COolParameters();
	~COolParameters();

	// Attributes
public:

	// Operations
public:
	INT Add(COolParameter *pOolParameter);

	INT Find(LPCTSTR pszTag) CONST;

	COolParameter *GetAt(INT nIndex) CONST;
	COolParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST COolParameters *pOolParameters);
	BOOL Compare(CONST COolParameters *pOolParameters) CONST;

private:
	INT FindIndex(COolParameter *pOolParameter) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COversamplingParameter

class AFX_EXT_CLASS COversamplingParameter : public CTMParameter
{
	// Construction
public:
	COversamplingParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbData;
		ULONGLONG  nAttributes;
	} DATA, *PDATA, *LPDATA;

	// Operations
public:
	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COversamplingParameters

class AFX_EXT_CLASS COversamplingParameters : public CTMParameters
{
	// Construction
public:
	COversamplingParameters();
	~COversamplingParameters();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbData;
		INT  cbParameters;
		TIMETAG  tTimeTag;
		double  fSamplingRate;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CTimeTag  m_tTimeTag;
	CByteArray  m_nData;
	double  m_fSamplingRate;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetTimeTag(CONST CTimeTag &tTimeTag);
	CTimeTag GetTimeTag() CONST;
	VOID SetData(CONST CByteArray &nData);
	INT GetData(CByteArray &nData) CONST;
	VOID SetSamplingRate(double fRate);
	double GetSamplingRate() CONST;

	INT Add(COversamplingParameter *pOversamplingParameter);

	INT Find(LPCTSTR pszTag) CONST;

	COversamplingParameter *GetAt(INT nIndex) CONST;
	COversamplingParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST COversamplingParameters *pOversamplingParameters);
	BOOL Compare(CONST COversamplingParameters *pOversamplingParameters) CONST;

	BOOL Map(CByteArray &nInfo, CONST CTimeTag &tRetention = -1) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention = -1);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCParameter

// Specify the telecommand parameter status related identifiers
#define TCPARAMETER_STATUS_NONE   TMPARAMETER_STATUS_NONE
#define TCPARAMETER_STATUS_NOLIMIT   TMPARAMETER_STATUS_NOLIMIT
#define TCPARAMETER_STATUS_SOFTLIMIT   TMPARAMETER_STATUS_SOFTLIMIT
#define TCPARAMETER_STATUS_HARDLIMIT   TMPARAMETER_STATUS_HARDLIMIT
#define TCPARAMETER_STATUS_DELTALIMIT   TMPARAMETER_STATUS_DELTALIMIT
#define TCPARAMETER_STATUS_VALUELIMIT   (TCPARAMETER_STATUS_DELTALIMIT<<1)
#define TCPARAMETER_STATUS_TIMELIMIT   (TCPARAMETER_STATUS_VALUELIMIT<<1)

class AFX_EXT_CLASS CTCParameter : public CObject
{
	// Construction
public:
	CTCParameter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize[2];
		INT  cbTag;
		INT  cbValues[2];
		INT  cbStatus;
		INT  nOolCount;
		WORD  wOolInfo[2];
		TIMETAG  tTime[3];
		ULONGLONG  nAttributes;
	} DATA, *PDATA, *LPDATA;
protected:
	CString  m_szTag;
	CTimeTag  m_tTime[2];
	ULONGLONG  m_nAttributes;
	CLongUIntArray  m_nValues;
	CTimeTagArray  m_tValues;
	CUIntArray  m_nStatus;
protected:
	CTimeTag  m_tOolTime;
	WORD  m_wOolInfo[2];
	INT  m_nOolCount;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;
	VOID SetAttributes(ULONGLONG nAttributes);
	ULONGLONG GetAttributes() CONST;

	VOID Initialize(CTCParameter *pTCParameter);
	BOOL IsInitialized() CONST;

	BOOL Update(CONST CTCParameter *pTCParameter);

	VOID Reset();

	BOOL SetRawValue(INT nSample, ULONGLONG nRawValue, UINT nStatus);
	BOOL SetRawValue(INT nSample, CONST CTimeTag &tRawValue, UINT nStatus = TCPARAMETER_STATUS_NONE);
	BOOL GetRawValue(INT nSample, ULONGLONG &nRawValue, UINT &nStatus) CONST;
	BOOL GetRawValue(INT nSample, CTimeTag &tRawValue, UINT &nStatus) CONST;

	BOOL Calibrate(CONST CDatabaseEngine *pDatabase, ULONGLONG nFlags, ULONGLONG nRawValue, double &fValue, BOOL &bOut) CONST;

	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue) CONST;
	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, double &fValue, BOOL &bOut) CONST;
	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue) CONST;
	BOOL GetValue(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, double &fValue, BOOL &bOut) CONST;

	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, CString &szValue, BOOL &bOut) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, CString &szValue, BOOL &bOut) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue) CONST;
	BOOL GetValueAsText(CONST CDatabaseEngine *pDatabase, INT nSample, ULONGLONG nFlags, INT nDigits, CString &szValue, BOOL &bOut) CONST;

	INT GetValueCount() CONST;

	VOID SetOolInfo();
	VOID SetOolInfo(CONST CTimeTag &tOolTime, WORD wTable, WORD wLimit);
	BOOL GetOolInfo(CTimeTag &tOolTime, WORD &wTable, WORD &wLimit) CONST;
	VOID SetOolCount(INT nCount = 0);
	INT GetOolCount() CONST;

	CTimeTag GetLastChangeTime() CONST;
	CTimeTag GetLastUpdateTime() CONST;

	BOOL Copy(CONST CTCParameter *pTCParameter);
	BOOL Compare(CONST CTCParameter *pTCParameter) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCParameters

class AFX_EXT_CLASS CTCParameters : public CPtrArray
{
	// Construction
public:
	CTCParameters();
	~CTCParameters();

	// Attributes
public:

	// Operations
public:
	BOOL Create(CONST CDatabaseEngine *pDatabase);

	INT Add(CTCParameter *pTCParameter);

	INT Find(LPCTSTR pszTag) CONST;

	CTCParameter *GetAt(INT nIndex) CONST;
	CTCParameter *operator[](INT nIndex) CONST;

	VOID Reset();

	VOID RemoveAll();

	BOOL Copy(CONST CTCParameters *pTCParameters);
	BOOL Compare(CONST CTCParameters *pTCParameters) CONST;

	BOOL Map(CByteArray &nInfo, BOOL bAll = FALSE) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, BOOL bAll = FALSE);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDump

// Specify the memory dump file formats
#define MEMORYDUMP_FILEFORMAT_NORMAL   (1<<0)
#define MEMORYDUMP_FILEFORMAT_DESCRIPTIVE   (1<<1)
#define MEMORYDUMP_FILEFORMAT_DELIMITED   (1<<2)
#define MEMORYDUMP_FILEFORMATS   3
// Specify the memory dump retention options
#define MEMORYDUMP_RETENTION_ENABLED   (1<<0)
#define MEMORYDUMP_RETENTION_STOPBYCOUNT   (1<<1)
#define MEMORYDUMP_RETENTION_STOPBYTIME   (1<<2)
// Specify the memory dump audition codes
#define MEMORYDUMP_AUDITION_NONE   0
#define MEMORYDUMP_AUDITION_ALL   1
#define MEMORYDUMP_AUDITION_FAILURES   2
// Specify the memory dump type and quality codes
#define MEMORYDUMP_DATATYPE_NORMAL   0
#define MEMORYDUMP_DATATYPE_TEMPLATE   1
#define MEMORYDUMP_DATATYPE_ILLEGAL   2
#define MEMORYDUMP_DATAQUALITY_NONE   0
#define MEMORYDUMP_DATAQUALITY_GOOD   (1<<0)
#define MEMORYDUMP_DATAQUALITY_BAD   (1<<1)
#define MEMORYDUMP_TIMECORRELATION_GOOD   (1<<2)
#define MEMORYDUMP_TIMECORRELATION_BAD   (1<<3)
// Specify the memory dump status codes
#define MEMORYDUMP_STATUS_EMPTY   0
#define MEMORYDUMP_STATUS_COLLECTING   1
#define MEMORYDUMP_STATUS_COMPLETE   2
#define MEMORYDUMP_STATUS_INCOMPLETE   3

class AFX_EXT_CLASS CMemoryDump : public CObject
{
	// Construction
public:
	CMemoryDump();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbFileName;
		INT  cbFileExtensions[MEMORYDUMP_FILEFORMATS];
		INT  cbFTPServer;
		INT  cbFTPDirectory;
		INT  cbFTPUserName;
		INT  cbFTPPassword;
		INT  cbDumpVersion;
		INT  cbDumpData[2];
		INT  cbDumpTag;
		UINT  nFTPPort;
		UINT  nFTPAudition;
		UINT  nFTPRetries[2];
		UINT  nFileFormats[2];
		UINT  nDataSource[2];
		UINT  nDataAddress[2][2];
		UINT  nDataBitWidth[2];
		UINT  nRetentionOptions[2];
		UINT  nRetentionCount[4];
		UINT  nDumpStatus;
		TIMEKEY  tRetention[2];
		TIMEKEY  tFTPRetryTime;
		TIMEKEY  tFTPRetryInterval;
		TIMETAG  tDumpTime;
		WORD  wDumpQuality;
		BOOL  bFTPQueue;
		BOOL  bAudition;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szFileName;
	CString  m_szFileExtensions[MEMORYDUMP_FILEFORMATS];
	CString  m_szOutputFiles;
	CString  m_szFTPServer;
	CString  m_szFTPDirectory;
	CString  m_szFTPUserName;
	CString  m_szFTPPassword;
	UINT  m_nFTPPort;
	UINT  m_nFTPAudition;
	UINT  m_nFTPRetries[2];
	UINT  m_nFileFormats[2];
	UINT  m_nDataSource[2];
	UINT  m_nDataAddress[2][2];
	UINT  m_nDataBitWidth[2];
	UINT  m_nRetentionOptions[2];
	UINT  m_nRetentionCount[4];
	CTimeKey  m_tRetention[2];
	CTimeKey  m_tFTPRetryTime;
	CTimeSpan  m_tFTPRetryInterval;
	BOOL  m_bFTPQueue;
	BOOL  m_bAudition;
private:
	CString  m_szDumpTag;
	CString  m_szDumpVersion;
	CTimeTag  m_tDumpTime[2];
	CByteArray  m_nDumpData[2];
	WORD  m_wDumpQuality;
	UINT  m_nDumpStatus;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	BOOL SetFileExtension(UINT nFormat, LPCTSTR pszFileExtension);
	BOOL GetFileExtension(UINT nFormat, CString &szFileExtension) CONST;
	VOID SetOutputFiles(LPCTSTR pszFiles);
	CString GetOutputFiles() CONST;
	VOID SetFTPServer(LPCTSTR pszServer);
	CString GetFTPServer() CONST;
	VOID SetFTPDirectory(LPCTSTR pszDirectory);
	CString GetFTPDirectory() CONST;
	VOID SetFTPUserName(LPCTSTR pszUserName);
	CString GetFTPUserName() CONST;
	VOID SetFTPPassword(LPCTSTR pszPassword);
	CString GetFTPPassword() CONST;
	VOID SetFTPPort(UINT nPort);
	UINT GetFTPPort() CONST;
	VOID SetDataSource(UINT nSource);
	UINT GetDataSource() CONST;
	VOID SetDataSourceSubSystem(UINT nSubSystem);
	UINT GetDataSourceSubSystem() CONST;
	BOOL SetDataAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress);
	BOOL GetDataAddressRange(UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST;
	VOID SetDataAddressBitWidth(UINT nWidth);
	UINT GetDataAddressBitWidth() CONST;
	VOID SetDataBitWidth(UINT nWidth);
	UINT GetDataBitWidth() CONST;
	VOID SetAuditionFlag(BOOL bFlag);
	BOOL GetAuditionFlag() CONST;
	VOID SetArchivingFileFormats(UINT nFormats);
	UINT GetArchivingFileFormats() CONST;
	VOID SetArchivingRetentionOptions(UINT nOptions);
	UINT GetArchivingRetentionOptions() CONST;
	VOID SetArchivingRetentionByCount(UINT nCount);
	UINT GetArchivingRetentionByCount() CONST;
	VOID SetArchivingRetentionByTime(CONST CTimeKey &tTime);
	CTimeKey GetArchivingRetentionByTime() CONST;
	VOID SetArchivingRetentionCount(UINT nCount);
	UINT GetArchivingRetentionCount() CONST;
	VOID SetNotificationsFileFormats(UINT nFormats);
	UINT GetNotificationsFileFormats() CONST;
	VOID SetNotificationsRetentionOptions(UINT nOptions);
	UINT GetNotificationsRetentionOptions() CONST;
	VOID SetNotificationsRetentionByCount(UINT nCount);
	UINT GetNotificationsRetentionByCount() CONST;
	VOID SetNotificationsRetentionByTime(CONST CTimeKey &tTime);
	CTimeKey GetNotificationsRetentionByTime() CONST;
	VOID SetNotificationsRetentionCount(UINT nCount);
	UINT GetNotificationsRetentionCount() CONST;

	BOOL SetDumpInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, CONST CByteArray &nData, WORD wQuality);
	BOOL SetDumpInfo(LPCTSTR pszTag, LPCTSTR pszVersion, CONST CTimeTag &tTag, CONST CByteArray &nData, WORD wQuality);
	BOOL SetDumpInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nPage, UINT nAddress, CONST CByteArray &nData, WORD wQuality);
	BOOL SetDumpInfo(LPCTSTR pszTag, LPCTSTR pszVersion, CONST CTimeTag &tTag, UINT nPage, UINT nAddress, CONST CByteArray &nData, WORD wQuality);
	BOOL SetDumpInfo(CONST CMemoryDump *pMemoryDump, UINT nStatus);
	BOOL SetDumpInfo(UINT nStatus);
	CString GetDumpTag() CONST;
	CString GetDumpVersion() CONST;
	CTimeTag GetDumpTime(BOOL bStart = TRUE) CONST;
	INT GetDumpData(CByteArray &nData) CONST;
	INT GetDumpMask(CByteArray &nMask) CONST;
	WORD GetDumpQuality() CONST;
	UINT GetDumpStatus() CONST;

	BOOL SetFTPRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval);
	BOOL GetFTPRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST;
	VOID SetFTPRetryTime(CONST CTimeKey &tTime);
	CTimeKey GetFTPRetryTime() CONST;
	VOID SetFTPRetryCount(UINT nCount);
	UINT GetFTPRetryCount() CONST;
	VOID SetFTPAudition(UINT nAudition);
	UINT GetFTPAudition() CONST;
	VOID SetFTPQueueFlag(BOOL bFlag);
	BOOL GetFTPQueueFlag() CONST;
	BOOL CheckFTPAddress() CONST;

	VOID Empty();

	VOID Copy(CONST CMemoryDump *pMemoryDump, BOOL bData = FALSE);
	BOOL Compare(CONST CMemoryDump *pMemoryDump, BOOL bData = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumps

class AFX_EXT_CLASS CMemoryDumps : public CMutexArray
{
	// Construction
public:
	CMemoryDumps();
	~CMemoryDumps();

	// Attributes
public:

	// Operations
public:
	INT Add(CMemoryDump *pMemoryDump);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CMemoryDump *GetAt(INT nIndex) CONST;
	CMemoryDump *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CMemoryDumps *pMemoryDumps, BOOL bData = FALSE);
	BOOL Compare(CONST CMemoryDumps *pMemoryDumps, BOOL bData = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPConnection

// Specify the TPEP connection types
#define TPEP_TYPE_PACKETS   1
#define TPEP_TYPE_PARAMETERS   2
// Specify the TPEP connection properties
#define TPEP_DATAMODE_REALTIME   1
#define TPEP_DATAMODE_HISTORY   2
#define TPEP_DATAMODE_RANDOM   3
#define TPEP_DATALINK_COLD   1
#define TPEP_DATALINK_HOT   2
#define TPEP_DATATYPE_RAW   0
#define TPEP_DATATYPE_PIE1   1
#define TPEP_DATATYPE_PIE2   2
#define TPEP_DATATYPE_PIE3   3
#define TPEP_TRIGGERMODE_UPDATE   1
#define TPEP_TRIGGERMODE_CHANGE   2
#define TPEP_RETRIEVESPEED_MINIMUM   1
#define TPEP_RETRIEVESPEED_MAXIMUM   10

class AFX_EXT_CLASS CTPEPConnection : public CObject
{
	// Construction
public:
	CTPEPConnection();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbPackets;
		INT  cbParameters;
		UINT  nType;
		UINT  nDataMode;
		UINT  nDataLink;
		UINT  nDataType;
		UINT  nTriggerMode;
		UINT  nSampleLimit;
		UINT  nSpacecraftID;
		UINT  nRetrieveSpeed;
		TIMEKEY  tRetrieveStartTime;
		TIMEKEY  tRetrieveStopTime;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nType;
	UINT  m_nDataMode;
	UINT  m_nDataLink;
	UINT  m_nDataType;
	UINT  m_nTriggerMode;
	UINT  m_nSampleLimit;
	UINT  m_nSpacecraftID;
	UINT  m_nMessageCount;
	UINT  m_nRetrieveSpeed;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeKey  m_tConnection[2];
	CStringArray  m_szPackets;
	CStringArray  m_szParameters;

	// Operations
public:
	BOOL SetType(UINT nType);
	UINT GetType() CONST;
	BOOL SetDataMode(UINT nDataMode);
	UINT GetDataMode() CONST;
	BOOL SetDataLink(UINT nDataLink);
	UINT GetDataLink() CONST;
	BOOL SetDataType(UINT nDataType);
	UINT GetDataType() CONST;
	BOOL SetTriggerMode(UINT nTriggerMode);
	UINT GetTriggerMode() CONST;
	BOOL SetSampleLimit(INT nSampleLimit);
	INT GetSampleLimit() CONST;
	VOID SetPackets(CONST CStringArray &szPackets);
	INT GetPackets(CStringArray &szPackets) CONST;
	VOID SetParameters(CONST CStringArray &szParameters);
	INT GetParameters(CStringArray &szParameters) CONST;
	VOID SetRetrieveStartTime(CONST CTimeKey &tRetrieveStartTime);
	CTimeKey GetRetrieveStartTime() CONST;
	VOID SetRetrieveStopTime(CONST CTimeKey &tRetrieveStopTime);
	CTimeKey GetRetrieveStopTime() CONST;
	BOOL SetRetrieveSpeed(UINT nRetrieveSpeed);
	UINT GetRetrieveSpeed() CONST;

	BOOL SetSpacecraftID(UINT nSpacecraftID);
	UINT GetSpacecraftID() CONST;

	VOID SetStatistics(CONST CTimeKey &tConnect, CONST CTimeKey &tLastUse, UINT nCount);
	VOID GetStatistics(CTimeKey &tConnect, CTimeKey &tLastUse, UINT &nCount) CONST;

	BOOL IsInitialized() CONST;

	VOID Reset();

	VOID Copy(CONST CTPEPConnection *pConnection, BOOL bStatistics = FALSE);
	BOOL Compare(CONST CTPEPConnection *pConnection, BOOL bStatistics = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPConnections

class AFX_EXT_CLASS CTPEPConnections : public CPtrArray
{
	// Construction
public:
	CTPEPConnections();
	~CTPEPConnections();

	// Attributes
public:

	// Operations
public:
	INT Add(CTPEPConnection *pConnection);

	CTPEPConnection *GetAt(INT nIndex) CONST;
	CTPEPConnection *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTPEPConnections *pConnections, BOOL bStatistics = FALSE);
	BOOL Compare(CONST CTPEPConnections *pConnections, BOOL bStatistics = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPConnection

// Specify the PFLP connection types
#define PFLP_TYPE_TM   1
#define PFLP_TYPE_TC   2
// Specify the PFLP connection levels
#define PFLP_LEVEL_SOURCEPACKETS   1
#define PFLP_LEVEL_TRANSFERFRAMES   2
// Specify the PFLP connection filter codes
#define PFLP_FILTER_COUNT   1
#define PFLP_FILTER_NONE   1
#define PFLP_FILTER_APID   2
#define PFLP_FILTER_VCID   3
#define PFLP_FILTER_APIDANDVCID   4
// Specify the PFLP connection endian codes
#define PFLP_ENDIAN_BIG   1
#define PFLP_ENDIAN_LITTLE   2

class AFX_EXT_CLASS CPFLPConnection : public CObject
{
	// Construction
public:
	CPFLPConnection();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		WORD  wType;
		WORD  wLevel;
		WORD  wEndian;
		WORD  wFilterCount;
		WORD  wFilterDataIdentifier;
		BYTE  nFilterGroupIdentifier;
		BYTE  nFilterManipulationCode;
		LONG  tCorrelationError;
		LONG  tCorrelationDelta;
		TIMEKEY  tAdjustment;
		SYSTEMTIME  tEpoch;
	} DATA, *PDATA, *LPDATA;
private:
	WORD  m_wType;
	WORD  m_wLevel;
	WORD  m_wEndian;
	WORD  m_wFilterCount;
	WORD  m_wFilterDataIdentifier;
	BYTE  m_nFilterGroupIdentifier;
	BYTE  m_nFilterManipulationCode;
	LONG  m_tCorrelationError;
	LONG  m_tCorrelationDelta;
	CTimeTag  m_tConnection[2];
	DWORDLONG  m_cbConnection;
	CTimeSpan  m_tAdjustment;
	SYSTEMTIME  m_tEpoch;

	// Operations
public:
	BOOL SetType(WORD wType);
	WORD GetType() CONST;
	BOOL SetLevel(WORD wLevel);
	WORD GetLevel() CONST;
	BOOL SetEndian(WORD wEndian);
	WORD GetEndian() CONST;
	BOOL SetFilterCount(WORD wCount);
	WORD GetFilterCount() CONST;
	BOOL SetFilterManipulationCode(BYTE nCode);
	BYTE GetFilterManipulationCode() CONST;
	BOOL SetFilterGroupIdentifier(BYTE nVCID);
	BYTE GetFilterGroupIdentifier() CONST;
	BOOL SetFilterDataIdentifier(WORD wAPID);
	WORD GetFilterDataIdentifier() CONST;
	VOID SetTimeEpoch(CONST SYSTEMTIME *pEpoch);
	BOOL GetTimeEpoch(SYSTEMTIME *pEpoch) CONST;
	VOID SetTimeCorrelation(LONG tError, LONG tDelta);
	BOOL GetTimeCorrelation(LONG &tError, LONG &tDelta) CONST;
	VOID SetClockAdjustment(CONST CTimeSpan &tAdjustment);
	CTimeSpan GetClockAdjustment() CONST;

	VOID SetStatistics(CONST CTimeTag &tConnectTime, CONST CTimeTag &tLastUseTime, DWORDLONG cbBytes);
	VOID GetStatistics(CTimeTag &tConnectTime, CTimeTag &tLastUseTime, DWORDLONG &cbBytes) CONST;

	BOOL IsInitialized() CONST;

	VOID Reset();

	VOID Copy(CONST CPFLPConnection *pConnection, BOOL bStatistics = FALSE);
	BOOL Compare(CONST CPFLPConnection *pConnection, BOOL bStatistics = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPConnections

class AFX_EXT_CLASS CPFLPConnections : public CPtrArray
{
	// Construction
public:
	CPFLPConnections();
	~CPFLPConnections();

	// Attributes
public:

	// Operations
public:
	INT Add(CPFLPConnection *pConnection);

	CPFLPConnection *GetAt(INT nIndex) CONST;
	CPFLPConnection *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CPFLPConnections *pConnections, BOOL bStatistics = FALSE);
	BOOL Compare(CONST CPFLPConnections *pConnections, BOOL bStatistics = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMProcessInfo

class AFX_EXT_CLASS CTMProcessInfo : public CObject
{
	// Construction
public:
	CTMProcessInfo();
	~CTMProcessInfo();

	// Attributes
protected:
	double  m_fTMBandwidth;
	CTimeTag  m_tTMBandwidth;
	CTimeTag  m_tTMBandwidthData;
	CUIntArray  m_nTMBandwidthData;
protected:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	virtual BOOL SetTMBandwidth(double fTMBandwidth = -1.0, CONST CTimeTag &tTMBandwidth = 0);
	virtual BOOL GetTMBandwidth(double &fTMBandwidth, CTimeTag &tTMBandwidth) CONST;
	virtual BOOL GetTMBandwidth(double &fTotalTMBandwidth, double &fMaxDiagnosticTMBandwidth) CONST;
	virtual BOOL SetTMBandwidthData(CONST CUIntArray &nTMBandwidthData, CONST CTimeTag &tTMBandwidthData);
	virtual BOOL GetTMBandwidthData(CUIntArray &nTMBandwidthData, CTimeTag &tTMBandwidthData) CONST;

	virtual BOOL SetData(CONST CByteArray &nData);
	virtual INT GetData(CByteArray &nData) CONST;

	virtual VOID Reset();

	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMEnvironment

class AFX_EXT_CLASS CTMEnvironment : public CObject
{
	// Construction
public:
	CTMEnvironment();
	~CTMEnvironment();

	// Attributes
private:
	typedef struct tagTMUNITDATA {
		INT  cbSize;
		INT  cbUnit;
		INT  cbSavedParameters;
	} TMUNITDATA, *PTMUNITDATA, *LPTMUNITDATA;
	typedef struct tagTMENVIRONMENTDATA {
		INT  cbSize;
		INT  cbCache;
		INT  cbParameters;
		INT  cbProcessInfo;
	} TMENVIRONMENTDATA, *PTMENVIRONMENTDTA, *LPTMENVIRONMENTDATA;
private:
	UINT  m_nType;
	CTMUnits  *m_pTMUnits;
	CTMPacket  *m_pTMPacket;
	CTMUnitCache  *m_pTMUnitCache;
	CMemoryDumps  *m_pMemoryDumps;
	CTMParameters  *m_pTMParameters[2];
	CTMProcessInfo  *m_pTMProcessInfo;
	COolParameters  *m_pOolParameters;
	COversamplingParameters  *m_pOversamplingParameters;
	BOOL  m_bHistoricalData;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Create(CONST CDatabaseEngine *pDatabase, BOOL bFull = TRUE);
	VOID Destroy();

	BOOL Initialize(CTMProcessInfo *pInfo = NULL);
	BOOL Initialize(CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL Initialize(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL Initialize(CTMParameters &pTMParameters, BOOL bBadData = FALSE);
	BOOL Initialize(COolParameters &pOolParameters, BOOL bBadData = FALSE);
	BOOL Initialize(CMemoryDump &pDump, BOOL bBadData = FALSE);
	BOOL Initialize(CONST CStringArray &szParameters, CONST CUIntArray &nSamples);
	BOOL Initialize(CONST COversamplingParameters &pOversamplingParameters);

	BOOL Update(CONST CTMParameters &pTMParameters);

	BOOL ExamineData(CONST CTMUnit *pTMUnit);
	BOOL IsHistoricalData() CONST;

	VOID Reset();

	UINT GetType() CONST;
	CTMUnit *GetTMUnit() CONST;
	CTMUnits *GetTMUnits() CONST;
	CTMUnitCache *GetTMUnitCache() CONST;
	CMemoryDumps *GetMemoryDumps() CONST;
	CTMParameters *GetTMParameters() CONST;
	CTMParameters *GetSyntheticParameters() CONST;
	CTMProcessInfo *GetTMProcessInfo() CONST;
	COolParameters *GetOolParameters() CONST;
	COversamplingParameters *GetOversamplingParameters() CONST;

	BOOL MapTMUnit(CByteArray &nInfo) CONST;
	BOOL UnmapTMUnit(CONST CByteArray &nInfo);
	BOOL Map(CByteArray &nInfo, CONST CTimeTag &tRetention = -1) CONST;
	BOOL Unmap(CONST CByteArray &nInfo, CONST CTimeTag &tRetention = -1);

	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInfo

class AFX_EXT_CLASS CTCProcessInfo : public CObject
{
	// Construction
public:
	CTCProcessInfo();
	~CTCProcessInfo();

	// Attributes
protected:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	virtual BOOL SetData(CONST CByteArray &nData);
	virtual INT GetData(CByteArray &nData) CONST;

	virtual VOID Reset();

	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCEnvironment

class AFX_EXT_CLASS CTCEnvironment : public CObject
{
	// Construction
public:
	CTCEnvironment();
	~CTCEnvironment();

	// Attributes
private:
	typedef struct tagTCUNITDATA {
		INT  cbSize;
		INT  cbUnit;
	} TCUNITDATA, *PTCUNITDATA, *LPTCUNITDATA;
	typedef struct tagTCENVIRONMENTDATA {
		INT  cbSize;
		INT  cbParameters;
		INT  cbProcessInfo;
	} TCENVIRONMENTDATA, *PTCENVIRONMENTDTA, *LPTCENVIRONMENTDATA;
private:
	UINT  m_nType;
	CTCUnit  *m_pTCUnit;
	CTCParameters  *m_pTCParameters;
	CTCProcessInfo  *m_pTCProcessInfo;
private:
	UINT  m_nTCProcedureID;
	CUIntArray  m_nTCProcedureIDs;
	CUIntArray  m_nTCProcedureEventCount;
	CStringArray  m_szTCProcedures;
	HINSTANCE  *m_hTCProcedureCodes;
	HANDLE  *m_hTCProcedureEvents;
private:
	CStringArray  m_szDebugTCProcedures;
	CPtrArray  m_pDebugTCProcedureArguments;
	CPtrArray  m_pDebugTCProcedureEvents[3];
private:
	CUIntArray  m_nTCFunctionProcedureIDs[2];
	CStringArray  m_szTCFunctions[4];
	CTimeTagArray  m_tTCFunctions[3];
	CLongUIntArray  m_nTCFunctionAckFlags;
	CDWordArray  m_dwTCFunctionReleaseOffsets;
	CDWordArray  m_dwTCFunctionExecutionOffsets;
	CByteArray  m_bTCFunctionExecutionFlags;
	CUIntArray  m_nTCFunctionEntryIDs[2];
	CUIntArray  m_nTCFunctionBlockIDs;
	CUIntArray  m_nTCFunctionExeModes;
	CByteArray  m_bTCFunctionFlags[2];
	CByteArray  m_bTCFunctionTypes;
	CPtrArray  m_hTCFunctionEvents[2];
	HANDLE  m_hTCFunctionEvent[2];
private:
	CUIntArray  m_nMessageProcedureIDs;
	CStringArray  m_szMessages[2];
	HANDLE  m_hMessageEvent[2];
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Create(CONST CDatabaseEngine *pDatabase, BOOL bFull = TRUE);
	VOID Destroy();

	BOOL Initialize(CTCProcessInfo *pInfo = NULL);
	BOOL Initialize(CTCParameters &pTCParameters);

	BOOL Update(CONST CTCParameters &pTCParameters);

	INT EnumTCProcedures(CStringArray &szNames, CUIntArray &nProcedureIDs, CPtrArray &hInstances) CONST;
	INT LoadTCProcedure(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, BOOL bDebugging, HINSTANCE &hInstance, CPtrArray &hEvents);
	INT LoadTCProcedure(CONST CDatabaseEngine *pDatabase, LPCTSTR pszFileName, LPCTSTR pszName, HINSTANCE &hInstance, CPtrArray &hEvents);
	BOOL LoadTCProcedure(CString &szName, va_list &pArgumentList, CPtrArray &pEvents);
	BOOL CallTCProcedure(LPCTSTR pszName, va_list pArgumentList);
	BOOL StartTCProcedure(LPCTSTR pszName, va_list pArgumentList);
	HANDLE SignalTCProcedure() CONST;
	BOOL FreeTCProcedure(INT nID);

	BOOL AddTCFunction(INT nProcedureID, INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, LPCTSTR pszFunction, BOOL bProcedure, INT nEntry, INT nEntries, CONST CTimeTag &tScheduleTime, CONST CTimeTag &tReleaseTime, DWORD dwReleaseOffset, CONST CTimeTag &tExecutionTime, DWORD dwExecutionOffset, BOOL bEarlierExecution, INT nBlockID, BOOL bGrouped, BOOL bCritical, UINT nExecutionMode, ULONGLONG nAckFlags, HANDLE hSuccess, HANDLE hFailure);
	BOOL RemoveTCFunction(INT &nProcedureID, INT &nProcessID, CString &szThread, CString &szStep, CString &szSequence, CString &szFunction, BOOL &bProcedure, INT &nEntry, INT &nEntries, CTimeTag &tScheduleTime, CTimeTag &tReleaseTime, DWORD &dwReleaseOffset, CTimeTag &tExecutionTime, DWORD &dwExecutionOffset, BOOL &bEarlierExecution, INT &nBlockID, BOOL &bGrouped, BOOL &bCritical, UINT &nExecutionMode, ULONGLONG &nAckFlags, HANDLE &hSuccess, HANDLE &hFailure);
	HANDLE SignalTCFunctionQueue(BOOL bEmpty = FALSE) CONST;

	BOOL AddMessage(LPCTSTR pszMessage);
	BOOL AddMessage(LPCTSTR pszType, LPCTSTR pszMessage);
	BOOL AddMessage(INT nID, LPCTSTR pszMessage);
	BOOL AddMessage(INT nID, LPCTSTR pszType, LPCTSTR pszMessage);
	BOOL RemoveMessage(CString &szMessage);
	BOOL RemoveMessage(CString &szType, CString &szMessage);
	BOOL RemoveMessage(INT &nID, CString &szMessage);
	BOOL RemoveMessage(INT &nID, CString &szType, CString &szMessage);
	HANDLE SignalMessageQueue(BOOL bEmpty = FALSE) CONST;

	VOID Reset();

	UINT GetType() CONST;
	CTCUnit *GetTCUnit() CONST;
	CTCParameters *GetTCParameters() CONST;
	CTCProcessInfo *GetTCProcessInfo() CONST;

	BOOL MapTCUnit(CByteArray &nInfo) CONST;
	BOOL UnmapTCUnit(CONST CByteArray &nInfo);
	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsServiceEngine

class AFX_EXT_CLASS CMemoryDumpsServiceEngine : public CObject
{
	// Construction
public:
	CMemoryDumpsServiceEngine();
	~CMemoryDumpsServiceEngine();

	// Attributes
private:
	CString  m_szEngine;
	HINSTANCE  m_hEngine;
	CMemoryDumpsServiceEngine  *m_pEngine;

	// Operations
public:
	BOOL Open(LPCTSTR pszName);
	BOOL IsOpen() CONST;
	VOID Close();

	CString GetName() CONST;

	CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine() CONST;

public:
	virtual UINT EnumMemoryDumpSources() CONST;
	virtual INT EnumMemoryDumpSources(CStringArray &szSources) CONST;
	virtual UINT TranslateMemoryDumpSource(LPCTSTR pszSource) CONST;
	virtual CString TranslateMemoryDumpSource(UINT nSource) CONST;
	virtual UINT DetermineMemoryDumpSource(LPCTSTR pszTag) CONST;
	virtual BOOL IsMemoryDumpByAddressRange(UINT nSource) CONST;
	virtual BOOL IsMemoryDumpByRegisters(UINT nSource) CONST;

	virtual UINT EnumMemoryDumpFormatTypes() CONST;
	virtual INT EnumMemoryDumpFormatTypes(CStringArray &szTypes) CONST;
	virtual UINT TranslateMemoryDumpFormatType(LPCTSTR pszType) CONST;
	virtual CString TranslateMemoryDumpFormatType(UINT nType) CONST;

	virtual UINT EnumMemoryDumpFileFormats(UINT nSource) CONST;

	virtual INT ProcessTMUnit(CONST CTMEnvironment *pTMEnvironment, CONST CMemoryDumps &pMemoryDumps, BOOL bUnicode = FALSE) CONST;
	virtual INT ProcessTMDump(CMemoryDump *pMemoryDump, BOOL bUnicode = FALSE) CONST;

	virtual CString GetMemoryDumpFileName(CONST CMemoryDump *pMemoryDump, LPCTSTR pszPrefix, CONST CTimeTag &tTimeTag, LPCTSTR pszExtension) CONST;
	virtual CString GetMemoryDumpFTPFileName(CONST CMemoryDump *pMemoryDump, UINT nFormat = MEMORYDUMP_FILEFORMAT_NORMAL) CONST;
	virtual CString GetMemoryDumpSearchFileName(LPCTSTR pszPrefix, LPCTSTR pszExtension) CONST;
	virtual CTimeSpan GetMemoryDumpInterval(UINT nSource, UINT nSubSystem) CONST;
	virtual UINT GetMemoryDumpIntervalTolerance(UINT nSource, UINT nSubSystem) CONST;

	virtual CString FormatMemoryDumpData(CONST CMemoryDump *pMemoryDump, UINT nFormat = MEMORYDUMP_FILEFORMAT_NORMAL) CONST;

	virtual BOOL IsServiceSupported() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceEngine

class AFX_EXT_CLASS CTPEPServiceEngine : public CObject
{
	// Construction
public:
	CTPEPServiceEngine();
	~CTPEPServiceEngine();

	// Attributes
private:
	CString  m_szEngine;
	HINSTANCE  m_hEngine;
	CTPEPServiceEngine  *m_pEngine;

	// Operations
public:
	BOOL Open(LPCTSTR pszName);
	BOOL IsOpen() CONST;
	VOID Close();

	CString GetName() CONST;

	CTPEPServiceEngine *GetTPEPServiceEngine() CONST;

public:
	virtual UINT GetTPEPSupport() CONST;

	virtual UINT GetTPEPSpacecraftID() CONST;

	virtual CString GetTPEPTimeKeyFormat() CONST;
	virtual CString GetTPEPRetrieveTimeKeyFormat() CONST;

	virtual INT EnumTPEPTMUnits(CONST CDatabaseEngine *pDatabase, CONST CStringArray &szParameters, CStringArray &szTMUnits) CONST;
	virtual INT EnumTPEPTMUnitParameters(CONST CDatabaseEngine *pDatabase, CONST CTMUnit *pTMUnit, CTPEPConnection *pConnection, BOOL bAll, CStringArray &szParameters) CONST;

	virtual BOOL GenerateTPEPRandomData(CONST CDatabaseEngine *pDatabase, CTPEPConnection *pConnection, CTMEnvironment *pTMEnvironment);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceEngine

class AFX_EXT_CLASS CPFLPServiceEngine : public CObject
{
	// Construction
public:
	CPFLPServiceEngine();
	~CPFLPServiceEngine();

	// Attributes
private:
	CString  m_szEngine;
	HINSTANCE  m_hEngine;
	CPFLPServiceEngine  *m_pEngine;

	// Operations
public:
	BOOL Open(LPCTSTR pszName);
	BOOL IsOpen() CONST;
	VOID Close();

	CString GetName() CONST;

	CPFLPServiceEngine *GetPFLPServiceEngine() CONST;

public:
	virtual BOOL IsServiceSupported() CONST;

	virtual BOOL FilterPFLPTMUnits(CONST CTMEnvironment *pTMEnvironment, BYTE nManipulationCode, BYTE nGroupIdentifier, WORD wDataIdentifier) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMProcessEngine

// Specify the telemetry service levels
#define TMSERVICELEVEL_NONE   0
#define TMSERVICELEVEL_DATA   1
#define TMSERVICELEVEL_PACKETS   2
#define TMSERVICELEVEL_TRANSFERFRAMES   3
// Specify the telemetry processing flags
#define TMPROCESSENGINE_DATA_NONE   0x00
#define TMPROCESSENGINE_DATA_PACKET   0x01
#define TMPROCESSENGINE_DATA_OOB   0x02

class AFX_EXT_CLASS CTMProcessEngine : public CObject
{
	// Construction
public:
	CTMProcessEngine();
	~CTMProcessEngine();

	// Attributes
protected:
	CString  m_szTMEngine;
	HINSTANCE  m_hTMEngine;
	CTMProcessEngine  *m_pTMEngine;

	// Operations
public:
	BOOL Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, CTMEnvironment *pTMEnvironment);
	BOOL IsOpen() CONST;
	VOID Close();

	CString GetName() CONST;

	CTMProcessEngine *GetTMProcessEngine() CONST;

public:
	virtual BOOL SetSpacecraftID(UINT nID);
	virtual UINT GetSpacecraftID() CONST;

	virtual UINT DetectTMServiceLevel() CONST;

	virtual BOOL SetCommandLinkControlWord(DWORD dwCLCW);
	virtual DWORD GetCommandLinkControlWord() CONST;

public:
	virtual INT EnumSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	virtual UINT TranslateSubSystemToID(LPCTSTR pszSubSystem) CONST;
	virtual CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

public:
	virtual INT ProcessTMTransferUnit(CONST CDatabaseEngine *pDatabase, CONST CTMTransferUnit *pTMTransferUnit, CTMEnvironment *pTMEnvironment);
	virtual INT ProcessTMUnit(CONST CDatabaseEngine *pDatabase, CONST CTMUnit *pTMUnit, CTMEnvironment *pTMEnvironment);
	virtual BOOL IsTMDump(CONST CTMEnvironment *pTMEnvironment) CONST;
	virtual UINT GetTMUnitID(CONST CTMUnit *pTMUnit) CONST;

	virtual BOOL SetTimeCorrelation(CTMEnvironment *pTMEnvironment);
	virtual BOOL SetTimeCorrelation(CTMEnvironment *pTMEnvironment, CONST CTimeTag &tOBRT, UINT nOBRT, UINT nOBTID = 0);
	virtual BOOL GetTimeCorrelation(CONST CTMEnvironment *pTMEnvironment, CTimeTag &tOBRT, UINT &nOBRT, UINT nOBTID = 0) CONST;
	virtual BOOL SetTimeCorrelationError(CONST CTMEnvironment *pTMEnvironment, LONG tError, LONG tDelta = 0, UINT nOBTID = 0);
	virtual BOOL GetTimeCorrelationError(CONST CTMEnvironment *pTMEnvironment, LONG &tError, LONG &tDelta, UINT nOBTID = 0) CONST;
	virtual UINT GetTimeCorrelationDelay(UINT nOBTID = 0) CONST;
	virtual UINT GetTimeCorrelationRange(UINT nOBTID = 0) CONST;
	virtual CTimeTag Correlate(CONST CTMEnvironment *pTMEnvironment, UINT tField, INT nLength, BOOL bCorrelate = TRUE, UINT nOBTID = 0) CONST;
	virtual BOOL CanCorrelate(CONST CTMEnvironment *pTMEnvironment, UINT nOBTID = 0) CONST;
	virtual CTimeSpan GetTMStreamInterruptionInterval() CONST;
	virtual CTimeSpan GetTMStreamDelayInterval() CONST;
	virtual BOOL CheckTMStreamInterruption(TIMETAG tInterval) CONST;
	virtual BOOL CheckTMStreamDelay(TIMETAG tDelay, TIMETAG tInterval) CONST;
	virtual BOOL CheckTMStreamCorrelation(CONST CTMEnvironment *pTMEnvironment) CONST;

	virtual BOOL CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTMParameter *pTMParameter, INT nCalTableRef, INT nOolTableRef, ULONGLONG nValue, UINT &nOolLimit, UINT &nOolStatus) CONST;
	virtual BOOL CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTMParameter *pTMParameter, INT nCalTableRef, INT nOolTableRef, ULONGLONG nValue, ULONGLONG nOldValue, INT nOldCalTableRef, BOOL bOldValue, UINT &nOolLimit, UINT &nOolStatus) CONST;
	virtual BOOL ConvertTMParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTMParameter *pTMParameter, INT nCalTableRef, LPCTSTR pszValue, ULONGLONG &nValue) CONST;

public:
	virtual BOOL AllocateTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST;
	virtual BOOL FreeTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcessEngine

// Specify the telecommand service levels
#define TCSERVICELEVEL_NONE   0
#define TCSERVICELEVEL_DATA   1
#define TCSERVICELEVEL_PACKETS   2
#define TCSERVICELEVEL_TRANSFERFRAMES   3
// Specify the telecommand verification stages
#define TCVERIFICATIONSTAGE_NONE   TCEXEVERSTAGE_TYPE_NONE
#define TCVERIFICATIONSTAGE_ACCEPTANCE   TCEXEVERSTAGE_TYPE_ACCEPTANCE
#define TCVERIFICATIONSTAGE_START   TCEXEVERSTAGE_TYPE_START
#define TCVERIFICATIONSTAGE_PROGRESS   TCEXEVERSTAGE_TYPE_PROGRESS
#define TCVERIFICATIONSTAGE_COMPLETION   TCEXEVERSTAGE_TYPE_COMPLETION
#define TCVERIFICATIONSTAGES_COUNT   4
// Specify the telecommand function related minimum and maximum time offsets
#define TCFUNCTIONEXECUTIONTIME_DEFAULT_MINIMUMOFFSET   (SECONDSPERMINUTE/2)
#define TCFUNCTIONEXECUTIONTIME_DEFAULT_MAXIMUMOFFSET   SECONDSPERDAY
#define TCFUNCTIONPARAMETERTIME_DEFAULT_MINIMUMOFFSET   (SECONDSPERMINUTE/2)
#define TCFUNCTIONPARAMETERTIME_DEFAULT_MAXIMUMOFFSET   SECONDSPERDAY

class AFX_EXT_CLASS CTCProcessEngine : public CObject
{
	// Construction
public:
	CTCProcessEngine();
	~CTCProcessEngine();

	// Attributes
protected:
	CString  m_szTCEngine;
	HINSTANCE  m_hTCEngine;
	CTCProcessEngine  *m_pTCEngine;

	// Operations
public:
	BOOL Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, CTCEnvironment *pTCEnvironment);
	BOOL IsOpen() CONST;
	VOID Close();

	CString GetName() CONST;

	CTCProcessEngine *GetTCProcessEngine() CONST;

public:
	virtual BOOL SetSpacecraftID(UINT nID);
	virtual UINT GetSpacecraftID() CONST;
	virtual BOOL SetVirtualChannel(UINT nChannel);
	virtual UINT GetVirtualChannel() CONST;

	virtual UINT DetectTCServiceLevel() CONST;

	virtual BOOL CorrelateTCTransferFrameSequenceNumber();
	virtual BOOL CanCorrelateTCTransferFrameSequenceNumber() CONST;
	virtual BOOL EnableTCTransferFrameExpeditedMode(BOOL bEnable = TRUE);
	virtual BOOL IsTCTransferFrameExpeditedModeEnabled() CONST;

public:
	virtual INT EnumSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	virtual UINT TranslateSubSystemToID(LPCTSTR pszSubSystem) CONST;
	virtual CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

public:
	virtual BOOL GenerateTCTransferFrames(CONST CDatabaseEngine *pDatabase, CONST CTCPacket *pTCPacket, BYTE *pTCProcessData, CTCTransferFrames &pTCTransferFrames);
	virtual BOOL GenerateTCPackets(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszMemoryPatch, BOOL bTimeTagged, BOOL b2ndStep, BOOL bBlocked, BOOL bExample, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets) CONST;
	virtual BOOL InitializeTCPacket(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CTCPacket *pTCPacket, CONST CTimeTag &tExecutionTime, BOOL bBlocked = FALSE, BOOL bExample = FALSE);
	virtual BOOL CollectTCPacket(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CDatabaseTCFunction *pDatabaseTCFunction, CTCPacket *pTCPacket, INT nBlockID);
	virtual BOOL DecodeTCPacket(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pDatabaseBlockedTCFunctions, CDatabaseTCPacket *pDatabaseTCPacket) CONST;
	virtual BOOL CheckTCFunctionPreexecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, INT nGroupID, CStringArray &szParameters) CONST;
	virtual BOOL CheckTCFunctionPreexecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMParameters &pTMParameters, LPCTSTR pszGroup, CStringArray &szParameters) CONST;
	virtual BOOL CheckTCFunctionExecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nGroupID, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;
	virtual BOOL CheckTCFunctionExecutionParameterGroup(CONST CDatabaseEngine *pDatabase, CONST CTMParameters &pTMParameters, CONST CDatabaseTCFunction *pDatabaseTCFunction, LPCTSTR pszGroup, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST;
	virtual BOOL CheckTCFunctionExecutionTime(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTimeTag &tExecutionTime = 0) CONST;
	virtual BOOL SetTCFunctionExecutionTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax);
	virtual BOOL GetTCFunctionExecutionTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST;
	virtual BOOL SetTCFunctionParameterTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax);
	virtual BOOL GetTCFunctionParameterTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST;
	virtual UINT CheckTCParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter, CTCParameter *pTCParameter, ULONGLONG nValue) CONST;
	virtual BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST;
	virtual BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST;
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, LPCTSTR pszTime, ULONGLONG &nValue) CONST;
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nPTC, INT nPFC, LPCTSTR pszTime, UINT nOBTID, ULONGLONG &nValue) CONST;
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, CONST CTimeTag &tTime, ULONGLONG &nValue) CONST;
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nPTC, INT nPFC, CONST CTimeTag &tTime, UINT nOBTID, ULONGLONG &nValue) CONST;
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, ULONGLONG nValue, CTimeTag &tTime) CONST;
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nPTC, INT nPFC, ULONGLONG nValue, UINT nOBTID, CTimeTag &tTime) CONST;

	virtual INT EnumTCDiagnosticsOversamplingDumpRates(CStringArray &szRates) CONST;
	virtual BOOL EncodeTCDiagnosticsOversamplingDump(CONST CDatabaseEngine *pDatabase, CONST CTimeTag &tExecutionTime, CONST COversamplingParameters &pOversamplingParameters, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	virtual BOOL DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCFunction *pDatabaseTCFunction, COversamplingParameters &pOversamplingParameters) CONST;
	virtual BOOL DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, COversamplingParameters &pOversamplingParameters, BOOL bAutomatic) CONST;
	virtual double CalculateTCDiagnosticsOversamplingBandwidth(CONST CDatabaseEngine *pDatabase, COversamplingParameters &pOversamplingParameters) CONST;

	virtual INT EnumTCOnBoardBufferTypes(CStringArray &szTypes) CONST;
	virtual INT EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames) CONST;
	virtual INT EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames, CUIntArray &nAPIDs, CUIntArray &nSubScheduleIDs, CUIntArray &nLimits, CStringArray &szUnits, CUIntArray &tTimeouts) CONST;
	virtual INT UpdateTCOnBoardBufferQueues(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CStringArray &szTypes, CStringArray &szNames, CUIntArray &nSubScheduleIDs, CUIntArray &nCounts, CTimeTagArray &tUpdateTimes, CUIntArray &nStatus);
	virtual BOOL CheckTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, BOOL &bStatus, BOOL &bDumpAllEntries, BOOL &bDumpByAPID, BOOL &bDumpByPSC, BOOL &bDumpByEntryRange, BOOL &bDumpByTimeRange, BOOL &bResetAllEntries, BOOL &bResetByAPID, BOOL &bResetByPSC, BOOL &bResetByEntryRange, BOOL &bResetByTimeRange) CONST;
	virtual BOOL EncodeTCOnBoardBufferQueueStatus(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, BOOL bEnable, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	virtual BOOL EncodeTCOnBoardBufferQueueDump(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	virtual BOOL EncodeTCOnBoardBufferQueueReset(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	virtual BOOL DecodeTCOnBoardBufferQueueDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CString &szType, CString &szName, UINT &nSubScheduleID, CTCPacket *pTCPacket) CONST;
	virtual BOOL DecodeTCOnBoardBufferQueueDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pBlockedItems, CDatabaseTCPacket *pDatabaseTCPacket, CTimeTag &tExecutionTime) CONST;
	virtual BOOL FindTCOnBoardBufferQueue(CONST CTCPacket *pTCPacket, CString &szType, CString &szName, UINT &nSubScheduleID) CONST;
	virtual BOOL ExpandTCOnBoardBufferQueueEntry(CONST CTCEnvironment *pTCEnvironment, CONST CTCPacket *pTCPacket, UINT &nBlockOffset, UINT &nBlockBytes, CUIntArray &nBlockSizes, CTimeTagArray &tBlockTimes) CONST;
	virtual UINT CalculateTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket) CONST;

	virtual BOOL CheckTCOnBoardMemoryImageDumpCapabilities(CONST CDatabaseEngine *pDatabase, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL &bStop) CONST;
	virtual BOOL EncodeTCOnBoardMemoryImageDump(CONST CDatabaseEngine *pDatabase, CTCEnvironment *pTCEnvironment, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeTag &tExecutionTime, BOOL bStop, CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	virtual BOOL IsTCOnBoardMemoryImageDump(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment) CONST;
	virtual BOOL CheckTCOnBoardMemoryImagePatchCapabilities(CONST CDatabaseEngine *pDatabase, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage) CONST;
	virtual BOOL EncodeTCOnBoardMemoryImagePatch(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTCEnvironment *pTCEnvironment, CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeTag &tExecutionTime, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets) CONST;
	virtual BOOL CalculateTCOnBoardMemoryImageCRC(CONST CDatabaseEngine *pDatabase, CONST CDatabaseOBProcessor *pProcessor, CDatabaseOBProcessorMemoryImage *pImage, LPCTSTR pszImageVersion) CONST;
	virtual BOOL IsTCOnBoardMemoryImagePatch(CONST CDatabaseEngine *pDatabase, CONST CTCPacket *pTCPacket, CString &szProcessor) CONST;

	virtual BOOL Get1stStepTCData(CONST CTMEnvironment *pTMEnvironment, CByteArray &nData) CONST;

	virtual BOOL SetTimeCorrelation(CTCEnvironment *pTCEnvironment);
	virtual BOOL SetTimeCorrelation(CTCEnvironment *pTCEnvironment, CONST CTimeTag &tOBRT, UINT nOBRT, UINT nOBTID = 0);
	virtual BOOL GetTimeCorrelation(CONST CTCEnvironment *pTCEnvironment, CTimeTag &tOBRT, UINT &nOBRT, UINT nOBTID = 0) CONST;
	virtual CTimeTag CorrelateTime(CONST CTCEnvironment *pTCEnvironment, CONST CTimeTag &tTime, UINT nOBTID) CONST;
	virtual BOOL CanCorrelateTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID = 0) CONST;
	virtual UINT ConvertTimeToOBRT(CONST CTCEnvironment *pTCEnvironment, CONST CTimeTag &tTime, UINT nOBTID = 0) CONST;
	virtual BOOL CanConvertTimeToOBRT(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID = 0) CONST;
	virtual CTimeTag ConvertOBRTToTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBRT, UINT nOBTID = 0) CONST;
	virtual BOOL CanConvertOBRTToTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID = 0) CONST;

	virtual BOOL EnableDebugging(BOOL bEnable = TRUE);
	virtual BOOL IsDebuggingEnabled() CONST;

public:
	virtual BOOL AllocateTCProcessInfo(CTCEnvironment *pTCEnvironment) CONST;
	virtual BOOL FreeTCProcessInfo(CTCEnvironment *pTCEnvironment) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TTCPROCESS_H__
