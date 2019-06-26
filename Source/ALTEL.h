// ALTEL.H : ALTEL Database Driver.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the ALTEL database driver related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/04/16 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __ALTEL_H__
#define __ALTEL_H__

#ifndef RC_INVOKED
#include "SatView.h"
#endif

#include "resource.h"		// main symbols
#include "ALTEL.rh"

#include "dialogs.h"
#include "records.h"


/////////////////////////////////////////////////////////////////////////////
// CALTELDatabaseEngine

class AFX_EXT_CLASS CALTELDatabaseEngine : public CDatabaseEngine
{
	// Construction
public:
	CALTELDatabaseEngine();

	// Attributes
public:

	// Operations
public:
	virtual BOOL Save();
	virtual BOOL Save(ULONGLONG nComponents);
	virtual BOOL Load();
	virtual UINT Load(ULONGLONG nComponents, BOOL bAll = TRUE);

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
	virtual BOOL Save(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);
	virtual BOOL Save(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);
	virtual BOOL Save(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);
	virtual BOOL Save(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock);
	virtual BOOL Save(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage);
	virtual BOOL Save(CONST CANDLayout *pANDLayout);
	virtual BOOL Save(CONST CGRDLayout *pGRDLayout);
	virtual BOOL Save(CONST CPODLayout *pPODLayout);
	virtual BOOL Flush(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
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
	virtual BOOL Delete(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);
	virtual BOOL Delete(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);
	virtual BOOL Delete(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);
	virtual BOOL Delete(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock);
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

	virtual BOOL IsInitialized() CONST;
	virtual BOOL IsValid() CONST;

	virtual VOID Reset();

public:
	virtual INT EnumANDs(CANDLayouts &pLayouts, ULONGLONG nSubcomponent = DATABASE_SUBCOMPONENT_AND_NORMAL, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumGRDs(CGRDLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumMMDs(CMMDLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
	virtual INT EnumPODs(CPODLayouts &pLayouts, BOOL bDirectory = TRUE) CONST;
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
	virtual CDatabaseTMPacketHeaders *GetTMPacketHeaders() CONST;
	virtual CDatabaseTMPacketStreams *GetTMPacketStreams() CONST;
	virtual CDatabaseTCParameterSets *GetTCParameterSets() CONST;
	virtual CDatabaseTCFunctionBlocks *GetTCFunctionBlocks() CONST;
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
	virtual BOOL DeleteTCExeVerGroup(LPCTSTR pszID);
	virtual BOOL DeleteTMPacketHeader(LPCTSTR pszName);
	virtual BOOL DeleteTMPacketStream(LPCTSTR pszName);
	virtual BOOL DeleteTCParameterSet(LPCTSTR pszName);
	virtual BOOL DeleteTCFunctionBlock(LPCTSTR pszName);
	virtual BOOL DeleteOBProcessorMemoryImage(LPCTSTR pszName);
	virtual BOOL DeleteAND(LPCTSTR pszName);
	virtual BOOL DeleteGRD(LPCTSTR pszName);
	virtual BOOL DeletePOD(LPCTSTR pszName);

private:
	BOOL SaveTMPackets();
	BOOL SaveTCPackets();
	BOOL SaveTCFunctions();
	BOOL SaveTCSequences();
	BOOL SaveOBProcessors();
	BOOL SaveTCProcedures();
	BOOL SaveTMParameters();
	BOOL SaveTCParameters();
	BOOL SaveANDs();
	BOOL SaveGRDs();
	BOOL SaveMMDs();
	BOOL SavePODs();
	BOOL SaveScripts();
	BOOL LoadTMPackets();
	BOOL LoadTCPackets();
	BOOL LoadTCFunctions();
	BOOL LoadTCSequences();
	BOOL LoadOBProcessors();
	BOOL LoadTCProcedures();
	BOOL LoadTMParameters();
	BOOL LoadTCParameters();
	BOOL LoadANDs();
	BOOL LoadGRDs();
	BOOL LoadMMDs();
	BOOL LoadPODs();
	BOOL LoadScripts();

	VOID CompileTMPackets(CBinaryDatabase *pDatabase);
	VOID CompileTCPackets(CBinaryDatabase *pDatabase);
	VOID CompileTCFunctions(CBinaryDatabase *pDatabase);
	VOID CompileTCSequences(CBinaryDatabase *pDatabase);
	VOID CompileOBProcessors(CBinaryDatabase *pDatabase);
	VOID CompileTMParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCParameters(CBinaryDatabase *pDatabase);
	VOID CompileTMNumCalTables(CBinaryDatabase *pDatabase);
	VOID CompileTMTxtCalTables(CBinaryDatabase *pDatabase);
	VOID CompileTMNumOolTables(CBinaryDatabase *pDatabase);
	VOID CompileTMTxtOolTables(CBinaryDatabase *pDatabase);
	VOID CompileTCNumCalTables(CBinaryDatabase *pDatabase);
	VOID CompileTCTxtCalTables(CBinaryDatabase *pDatabase);
	VOID CompileTCNumOolTables(CBinaryDatabase *pDatabase);
	VOID CompileTCTxtOolTables(CBinaryDatabase *pDatabase);
	VOID CompileTCPreExeGroups(CBinaryDatabase *pDatabase);
	VOID CompileTCExeVerGroups(CBinaryDatabase *pDatabase);
	VOID CompileTCParameterSets(CBinaryDatabase *pDatabase);
	VOID CompileTCFunctionBlocks(CBinaryDatabase *pDatabase);
	VOID CompileTMPacketParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCPacketParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCFunctionElements(CBinaryDatabase *pDatabase);
	VOID CompileTCFunctionBlockElements(CBinaryDatabase *pDatabase);
	VOID CompileTCSequenceParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCSequenceEntryParameters(CBinaryDatabase *pDatabase);
	VOID CompileANDs(CBinaryDatabase *pDatabase);
	VOID CompileGRDs(CBinaryDatabase *pDatabase);
	VOID CompilePODs(CBinaryDatabase *pDatabase);

	CString CheckDerivationProcedure(LPCTSTR pszExpression, INT &nPos) CONST;
	CString CheckDerivationFunction(LPCTSTR pszExpression, INT &nPos) CONST;
	CString CheckDerivationOperator(LPCTSTR pszExpression, INT &nPos) CONST;
	CString TranslateDerivationFunction(LPCTSTR pszFunction) CONST;
	CString TranslateDerivationOperator(LPCTSTR pszOperator, BOOL bBitwise = FALSE) CONST;
	CString TranslateDerivationProcedure(LPCTSTR pszTag, CONST CStringArray &pParameters, LPCTSTR pszExpression) CONST;
	CString TranslateDerivationStatement(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CStringArray &pDerivationExpressionParameters, CStringArray &szErrors) CONST;
	BOOL TranslateDerivationExpression(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CString &szExpression, CStringArray &pDerivationExpressionParameters, INT &nPos, CStringArray &szErrors) CONST;
	BOOL TranslateDerivationCondition(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CString &szExpression, CStringArray &pDerivationExpressionParameters, INT &nPos, CStringArray &szErrors) CONST;
	BOOL TranslateDerivationTerm(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CString &szExpression, CStringArray &pDerivationExpressionParameters, INT &nPos, CStringArray &szErrors) CONST;
	BOOL TranslateDerivationFactor(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CString &szExpression, CStringArray &pDerivationExpressionParameters, INT &nPos, CStringArray &szErrors) CONST;
	BOOL TranslateDerivationParameter(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CString &szExpression, CStringArray &pDerivationExpressionParameters, INT &nPos, CStringArray &szErrors) CONST;
	BOOL TranslateDerivationNumber(LPCTSTR pszTag, LPCTSTR pszExpression, CONST CStringArray &pParameters, CString &szExpression, CStringArray &pDerivationExpressionParameters, INT &nPos, CStringArray &szErrors) CONST;
	BOOL TranslateDerivationText(LPCTSTR pszTag, LPCTSTR pszExpression, CString &szExpression, INT &nPos, CStringArray &szErrors) CONST;
	VOID AppendDerivationParameters(CONST CStringArray &szExpressionParameters, CStringArray &szParameters) CONST;
	INT FindDerivationParameter(CONST CStringArray &szExpressionParameters, LPCTSTR pszTag, BOOL bInsert = TRUE) CONST;
	VOID AppendDerivationErrors(CONST CStringArray &szExpressionErrors, CStringArray &szErrors) CONST;
	INT FindDerivationError(CONST CStringArray &szExpressionErrors, LPCTSTR pszError, BOOL bInsert = TRUE) CONST;

	BOOL ConvertTCParameterConstValue(LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST;
	BOOL ConvertTCParameterConstValue(CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST;

	BOOL CheckTCSequenceNesting(CBinaryDatabase *pDatabase, LPCTSTR pszName, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;
	BOOL CheckTCSequenceNesting(CBinaryDatabase *pDatabase, CStringArray &szNames, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;

	BOOL CheckTag(LPCTSTR pszTag, INT nLength, BOOL bVariable = TRUE) CONST;
	BOOL CheckName(LPCTSTR pszName, INT nLength, BOOL bVariable = TRUE) CONST;
	BOOL CheckIdentifier(LPCTSTR pszIdentifier, INT nMinLength, INT nMaxLength) CONST;

	INT SkipSpaces(LPCTSTR pszCode, INT &nPos) CONST;

public:
	virtual BOOL CheckTMPacketTag(LPCTSTR pszTag) CONST;
	virtual INT GetTMPacketTagLength() CONST;
	virtual CString GetTMPacketSubTag() CONST;
	virtual CString GetTMPacketDummyTag() CONST;
	virtual BOOL CheckTMPacketType(INT nType) CONST;
	virtual INT GetTMPacketTypeLength() CONST;
	virtual INT TranslateTMPacketType(LPCTSTR pszType) CONST;
	virtual CString TranslateTMPacketType(INT nType) CONST;
	virtual BOOL CheckTMPacketDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMPacketDescriptionLength() CONST;
	virtual BOOL CheckTMPacketDetails(LPCTSTR pszDetails) CONST;
	virtual INT GetTMPacketDetailsLength() CONST;
	virtual INT EnumTMPacketDataFieldHeaderFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual INT TranslateTMPacketDataFieldHeaderFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketDataFieldHeaderFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketDataFieldHeader(INT bPresent) CONST;
	virtual BOOL CheckTMPacketDataFieldHeaderName(LPCTSTR pszName) CONST;
	virtual INT GetTMPacketDataFieldHeaderNameLength() CONST;
	virtual INT EnumTMPacketAPIDs(CStringArray &szAPIDs, CUIntArray &nAPIDs) CONST;
	virtual BOOL CheckTMPacketAPID(LPCTSTR pszTag, INT nAPID) CONST;
	virtual INT GetTMPacketAPIDLength() CONST;
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
	virtual BOOL CheckTMPacketTransmissionRate(INT nType, INT nInterval) CONST;
	virtual BOOL GetTMPacketTransmissionRateRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketTransmissionRetries(INT nRetries) CONST;
	virtual INT GetTMPacketTransmissionRetriesLength() CONST;
	virtual BOOL GetTMPacketTransmissionRetriesRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMPacketTransmissionRetries(LPCTSTR pszRetries) CONST;
	virtual CString TranslateTMPacketTransmissionRetries(INT nRetries) CONST;
	virtual BOOL CheckTMPacketVirtualChannel(INT nAPID, INT nChannelID) CONST;
	virtual BOOL GetTMPacketVirtualChannelRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketEventID(LPCTSTR pszEventID) CONST;
	virtual INT GetTMPacketEventIDLength() CONST;
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
	virtual BOOL CheckTMPacketParameterBytePosition(INT nByte) CONST;
	virtual BOOL GetTMPacketParameterBytePositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterBitPosition(INT nBit) CONST;
	virtual BOOL GetTMPacketParameterBitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOccurrenceCount(INT nCount) CONST;
	virtual BOOL GetTMPacketParameterOccurrenceCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterOccurrenceInterval(INT nOccurrence, INT nInterval) CONST;
	virtual BOOL GetTMPacketParameterOccurrenceIntervalRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketParameterValidity(LPCTSTR pszTag) CONST;
	virtual INT GetTMPacketParameterValidityLength() CONST;
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
	virtual INT EnumTCFunctionTCTypes(CStringArray &szTCTypes, CLongUIntArray &nTCTypes) CONST;
	virtual BOOL CheckTCFunctionTCType(ULONGLONG nTCType) CONST;
	virtual INT GetTCFunctionTCTypeLength() CONST;
	virtual ULONGLONG TranslateTCFunctionTCType(LPCTSTR pszTCType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionTCType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionTCID(INT nTCID) CONST;
	virtual BOOL GetTCFunctionTCIDRange(INT &nLow, INT &nHigh) CONST;
	virtual INT GetTCFunctionTCIDLength() CONST;
	virtual INT TranslateTCFunctionTCID(LPCTSTR pszTCID) CONST;
	virtual CString TranslateTCFunctionTCID(INT nTCID) CONST;
	virtual BOOL CheckTCFunctionPacketTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCFunctionPacketTagLength() CONST;
	virtual INT EnumTCFunctionHazardousFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCFunctionHazardousFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCFunctionHazardousFlagLength() CONST;
	virtual ULONGLONG TranslateTCFunctionHazardousFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionHazardousFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionRouterEquipment(LPCTSTR pszEquipment) CONST;
	virtual INT GetTCFunctionRouterEquipmentLength() CONST;
	virtual BOOL CheckTCFunctionRouterSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTCFunctionRouterSubSystemLength() CONST;
	virtual BOOL CheckTCFunctionDestinationEquipment(LPCTSTR pszEquipment) CONST;
	virtual INT GetTCFunctionDestinationEquipmentLength() CONST;
	virtual BOOL CheckTCFunctionDestinationSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTCFunctionDestinationSubSystemLength() CONST;
	virtual BOOL CheckTCFunctionDestinationSubSchedule(LPCTSTR pszSubSchedule) CONST;
	virtual INT GetTCFunctionDestinationSubScheduleLength() CONST;
	virtual BOOL CheckTCFunctionOperationalInfo(LPCTSTR pszInfo) CONST;
	virtual INT GetTCFunctionOperationalInfoLength() CONST;
	virtual BOOL CheckTCFunctionValidityConditions(LPCTSTR pszConditions) CONST;
	virtual INT GetTCFunctionValidityConditionsLength() CONST;
	virtual BOOL CheckTCFunctionAssociatedTelecommands(LPCTSTR pszTelecommands) CONST;
	virtual INT GetTCFunctionAssociatedTelecommandsLength() CONST;
	virtual BOOL CheckTCFunctionComplementaryTelecommands(LPCTSTR pszTelecommands) CONST;
	virtual INT GetTCFunctionComplementaryTelecommandsLength() CONST;
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
	virtual BOOL CheckTCFunctionElementConstTimeType(LPCTSTR pszName) CONST;
	virtual BOOL CheckTCFunctionElementConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
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
	virtual BOOL CheckTCSequenceSubScheduleDestination(LPCTSTR pszSubSchedule) CONST;
	virtual INT GetTCSequenceSubScheduleDestinationLength() CONST;
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
	virtual INT EnumTCSequenceParameterValueTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCSequenceParameterValueType(ULONGLONG nAttributes, ULONGLONG nType) CONST;
	virtual INT GetTCSequenceParameterValueTypeLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterValueType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterValueType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceParameterCategories(CStringArray &szCategories, CLongUIntArray &nCategories) CONST;
	virtual BOOL CheckTCSequenceParameterCategory(ULONGLONG nCategory) CONST;
	virtual INT GetTCSequenceParameterCategoryLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterCategory(LPCTSTR pszCategory, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterCategory(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCSequenceParameterCodings(CStringArray &szCodings, CLongUIntArray &nCodings) CONST;
	virtual BOOL CheckTCSequenceParameterCoding(ULONGLONG nAttributes, ULONGLONG nCoding) CONST;
	virtual INT GetTCSequenceParameterCodingLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCSequenceParameterCoding(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
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
	virtual BOOL CheckTCSequenceEntryReleaseDeltaTime(ULONGLONG nAttributes, LPCTSTR pszDelta, LPCTSTR pszFormat) CONST;
	virtual INT GetTCSequenceEntryReleaseDeltaTimeLength() CONST;
	virtual DWORD TranslateTCSequenceEntryReleaseDeltaTime(LPCTSTR pszDelta, LPCTSTR pszFormat) CONST;
	virtual CString TranslateTCSequenceEntryReleaseDeltaTime(DWORD dwDelta, LPCTSTR pszFormat) CONST;
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
	virtual BOOL CheckTCSequenceEntryParameterCount(INT nCount) CONST;
	virtual BOOL GetTCSequenceEntryParameterCountRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCSequenceEntryParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCSequenceEntryParameterTagLength() CONST;
	virtual BOOL CheckTCSequenceEntryParameterComment(LPCTSTR pszTag) CONST;
	virtual INT GetTCSequenceEntryParameterCommentLength() CONST;
	virtual BOOL CheckTCSequenceEntryParameterPosition(INT nPosition) CONST;
	virtual BOOL GetTCSequenceEntryParameterPositionRange(INT &nLow, INT &nHigh) CONST;
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
	virtual CTimeTag TranslateTCSequenceEntryParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
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
	virtual INT EnumTMParameterConsistencyChecksFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTMParameterConsistencyChecksFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTMParameterConsistenceChecksFlagLength() CONST;
	virtual ULONGLONG TranslateTMParameterConsistencyChecksFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterConsistencyChecksFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMParameterValidityParameters(CStringArray &szParameters) CONST;
	virtual BOOL CheckTMParameterValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMParameterValidityParameterLength() CONST;
	virtual BOOL CheckTMParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTMParameterConstValueLength() CONST;
	virtual BOOL CheckTMParameterRelatedParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMParameterRelatedParameterLength() CONST;
	virtual CString TranslateTMParameterRelatedParameter(LPCTSTR pszTag) CONST;
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
	virtual BOOL CheckTMParameterSpareList(LPCTSTR pszTag) CONST;
	virtual INT EnumTMParameterStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMParameterStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMParameterStatusLength() CONST;
	virtual INT TranslateTMParameterStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMParameterStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTMNumCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMNumCalTableNameLength() CONST;
	virtual BOOL CheckTMNumCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMNumCalTableDescriptionLength() CONST;
	virtual BOOL CheckTMNumCalTableUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTMNumCalTableUnitLength() CONST;
	virtual BOOL CheckTMNumCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTMNumCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMNumCalTablePointInterval(double X1, double X2) CONST;
	virtual INT EnumTMNumCalTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMNumCalTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMNumCalTableStatusLength() CONST;
	virtual INT TranslateTMNumCalTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumCalTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTMTxtCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMTxtCalTableNameLength() CONST;
	virtual BOOL CheckTMTxtCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMTxtCalTableDescriptionLength() CONST;
	virtual BOOL CheckTMTxtCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTMTxtCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
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
	virtual BOOL CheckTMNumOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTMNumOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMNumOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMNumOolTableCheckCount(INT nCount) CONST;
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
	virtual INT TranslateTMNumOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMNumOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTMNumOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTMNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTMNumOolTableLimitValueLength() CONST;
	virtual double TranslateTMNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTMNumOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual INT EnumTMNumOolTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTMNumOolTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTMNumOolTableStatusLength() CONST;
	virtual INT TranslateTMNumOolTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTMTxtOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMTxtOolTableNameLength() CONST;
	virtual BOOL CheckTMTxtOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTMTxtOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMTxtOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMTxtOolTableCheckCount(INT nCount) CONST;
	virtual INT EnumTMTxtOolTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTMTxtOolTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTMTxtOolTableInterpretationLength() CONST;
	virtual UINT TranslateTMTxtOolTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableInterpretation(UINT nInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMTxtOolTableRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTMTxtOolTableRadix(UINT nInterpretation, UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTMTxtOolTableRadixLength() CONST;
	virtual UINT TranslateTMTxtOolTableRadix(UINT nInterpretation, LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableRadix(UINT nRadix, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMTxtOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual INT TranslateTMTxtOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMTxtOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTMTxtOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTMTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTMTxtOolTableLimitValueLength() CONST;
	virtual double TranslateTMTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTMTxtOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
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
	virtual BOOL CheckTCParameterBitWidth(INT nWidth) CONST;
	virtual BOOL GetTCParameterBitWidthRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCParameterCalTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCParameterCalTableLength() CONST;
	virtual BOOL CheckTCParameterOolTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCParameterOolTableLength() CONST;
	virtual INT EnumTCParameterCodings(CStringArray &szCodings, CLongUIntArray &nCodings) CONST;
	virtual BOOL CheckTCParameterCoding(ULONGLONG nAttributes, ULONGLONG nCoding) CONST;
	virtual INT GetTCParameterCodingLength() CONST;
	virtual ULONGLONG TranslateTCParameterCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterCoding(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTCParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCParameterConstTimeType(LPCTSTR pszTag) CONST;
	virtual BOOL CheckTCParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual CTimeTag TranslateTCParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
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
	virtual BOOL CheckTCNumCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTCNumCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCNumCalTablePointInterval(double X1, double X2) CONST;
	virtual INT EnumTCNumCalTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCNumCalTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCNumCalTableStatusLength() CONST;
	virtual INT TranslateTCNumCalTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumCalTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCTxtCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCTxtCalTableNameLength() CONST;
	virtual BOOL CheckTCTxtCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCTxtCalTableDescriptionLength() CONST;
	virtual BOOL CheckTCTxtCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTCTxtCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
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
	virtual BOOL CheckTCNumOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTCNumOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCNumOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTCNumOolTableCheckCount(INT nCount) CONST;
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
	virtual INT TranslateTCNumOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCNumOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTCNumOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTCNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTCNumOolTableLimitValueLength() CONST;
	virtual double TranslateTCNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTCNumOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual INT EnumTCNumOolTableStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCNumOolTableStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCNumOolTableStatusLength() CONST;
	virtual INT TranslateTCNumOolTableStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCNumOolTableStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCTxtOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCTxtOolTableNameLength() CONST;
	virtual BOOL CheckTCTxtOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTCTxtOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCTxtOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTCTxtOolTableCheckCount(INT nCount) CONST;
	virtual INT EnumTCTxtOolTableInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCTxtOolTableInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCTxtOolTableInterpretationLength() CONST;
	virtual UINT TranslateTCTxtOolTableInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableInterpretation(UINT nInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCTxtOolTableRadixes(CStringArray &szRadixes, CUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCTxtOolTableRadix(UINT nInterpretation, UINT nCoding, UINT nRadix) CONST;
	virtual INT GetTCTxtOolTableRadixLength() CONST;
	virtual UINT TranslateTCTxtOolTableRadix(UINT nInterpretation, LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableRadix(UINT nRadix, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCTxtOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual INT TranslateTCTxtOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCTxtOolTableLimitOrder(INT nOrder) CONST;
	virtual INT GetTCTxtOolTableLimitCount(UINT nAttributes) CONST;
	virtual BOOL CheckTCTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTCTxtOolTableLimitValueLength() CONST;
	virtual double TranslateTCTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTCTxtOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
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
	virtual BOOL CheckTCExeVerGroupParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCExeVerGroupParameterTagLength() CONST;
	virtual INT EnumTCExeVerGroupParameterStages(CStringArray &szStageIDs, CUIntArray &nStageIDs) CONST;
	virtual BOOL CheckTCExeVerGroupParameterStage(UINT nStageID) CONST;
	virtual INT GetTCExeVerGroupParameterStageLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterStage(LPCTSTR pszStageID, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterStage(UINT nStageID, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCExeVerGroupParameterTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTCExeVerGroupParameterType(UINT nType) CONST;
	virtual INT GetTCExeVerGroupParameterTypeLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterType(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTCExeVerGroupParameterInterpretations(CStringArray &szInterpretations, CUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCExeVerGroupParameterInterpretation(UINT nInterpretation) CONST;
	virtual INT GetTCExeVerGroupParameterInterpretationLength() CONST;
	virtual UINT TranslateTCExeVerGroupParameterInterpretation(LPCTSTR pszInterpretation, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCExeVerGroupParameterInterpretation(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCExeVerGroupParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTCExeVerGroupParameterConstValueLength() CONST;
	virtual double TranslateTCExeVerGroupParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCExeVerGroupParameterConstValue(ULONGLONG nAttributes, double fValue) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowInterval(CONST CTimeSpan &tInterval) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowIntervalRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterEventID(LPCTSTR pszEventID) CONST;
	virtual INT GetTCExeVerGroupParameterEventIDLength() CONST;

	virtual BOOL CheckTCParameterSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCParameterSetNameLength() CONST;
	virtual BOOL CheckTCParameterSetDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCParameterSetDescriptionLength() CONST;
	virtual INT EnumTCParameterSetStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckTCParameterSetStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetTCParameterSetStatusLength() CONST;
	virtual INT TranslateTCParameterSetStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterSetStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCParameterSetItemName(LPCTSTR pszName) CONST;
	virtual INT GetTCParameterSetItemNameLength() CONST;
	virtual INT EnumTCParameterSetItemValueInterpretations(CStringArray &szInterpretations, CLongUIntArray &nInterpretations) CONST;
	virtual BOOL CheckTCParameterSetItemValueInterpretation(ULONGLONG nAttributes, ULONGLONG nFlag) CONST;
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
	virtual CTimeTag TranslateTCParameterSetItemConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;

	virtual BOOL CheckANDName(LPCTSTR pszName) CONST;
	virtual INT GetANDNameLength() CONST;
	virtual BOOL CheckANDTitle(LPCTSTR pszTitle) CONST;
	virtual INT GetANDTitleLength() CONST;
	virtual INT EnumANDColumns(CStringArray &szColumns, CUIntArray &nColumns) CONST;
	virtual BOOL CheckANDColumns(LPCTSTR pszColumns) CONST;
	virtual INT GetANDColumnsLength() CONST;
	virtual BOOL TranslateANDColumns(LPCTSTR pszColumns, CUIntArray &nColumns, BOOL bDBMS = TRUE) CONST;
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
	virtual BOOL CheckGRDParameterPosition(INT nPosition) CONST;
	virtual BOOL GetGRDParameterPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumGRDParameterModes(CStringArray &szModes, CLongUIntArray &nModes) CONST;
	virtual BOOL CheckGRDParameterMode(LPCTSTR pszMode) CONST;
	virtual INT GetGRDParameterModeLength() CONST;
	virtual ULONGLONG TranslateGRDParameterMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDParameterMode(ULONGLONG nMode, BOOL bDBMS = TRUE) CONST;
	virtual ULONGLONG TranslateGRDParameterAttributes(ULONGLONG nMode, ULONGLONG nAttributes) CONST;
	virtual BOOL CheckGRDParameterOccurrence(INT nOccurrence) CONST;
	virtual BOOL GetGRDParameterOccurrenceRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDParameterColor(INT nColor) CONST;
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
	virtual BOOL CheckGRDParameterMinimum(double fMinimum) CONST;
	virtual BOOL CheckGRDParameterMaximum(double fMaximum) CONST;
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
	virtual INT EnumPODExpressionStack(CStringArray &szExpressions, CUIntArray &nExpressions) CONST;
	virtual BOOL CheckPODExpressionStack(LPCTSTR pszStack) CONST;
	virtual INT GetPODExpressionStackLength() CONST;
	virtual INT TranslatePODExpressionStack(LPCTSTR pszStack, CStringArray &szStack, CByteArray &bFunctions, CByteArray &bOperators, CByteArray &bParameters, CByteArray &bNumbers) CONST;
	virtual CString TranslatePODExpressionStack(CONST CStringArray &szStack) CONST;
	virtual BOOL TranslatePODExpressionStackElement(LPCTSTR pszElement, CPODLayoutExpression *pElement) CONST;
	virtual BOOL CheckPODExpressionStackElementColor(INT nColor) CONST;
	virtual BOOL CheckPODParameters(LPCTSTR pszParameters) CONST;
	virtual INT GetPODParametersListLength() CONST;
	virtual INT GetPODParameterTagLength() CONST;
	virtual INT TranslatePODParameters(LPCTSTR pszParameters, CStringArray &szParameters) CONST;
	virtual CString TranslatePODParameters(CONST CStringArray &szParameters) CONST;
	virtual BOOL CheckPODParameterSample(INT nSample) CONST;
	virtual BOOL CheckPODParametersColor(INT nColor) CONST;
	virtual INT EnumPODFunctions(CStringArray &szFunctions, CUIntArray &nFunctions) CONST;
	virtual BOOL CheckPODFunctions(LPCTSTR pszFunctions) CONST;
	virtual INT GetPODFunctionsListLength() CONST;
	virtual INT GetPODFunctionLength() CONST;
	virtual INT TranslatePODFunctions(LPCTSTR pszFunctions, CStringArray &szFunctions) CONST;
	virtual CString TranslatePODFunctions(CONST CStringArray &szFunctions) CONST;
	virtual BOOL CheckPODFunctionsColor(INT nColor) CONST;
	virtual INT EnumPODStatus(CStringArray &szStatus, CUIntArray &nStatus) CONST;
	virtual BOOL CheckPODStatus(LPCTSTR pszStatus) CONST;
	virtual INT GetPODStatusLength() CONST;
	virtual INT TranslatePODStatus(LPCTSTR pszStatus, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslatePODStatus(INT nStatus, BOOL bDBMS = TRUE) CONST;

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

	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacket *pDatabaseTMPacket, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCPacket *pDatabaseTCPacket, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCFunction *pDatabaseTCFunction, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCSequence *pDatabaseTCSequence, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseOBProcessor *pDatabaseOBProcessor, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMParameter *pDatabaseTMParameter, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCParameter *pDatabaseTCParameter, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCParameterSet *pDatabaseTCParameterSet, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacketHeaders *pDatabaseTMPacketHeaders, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacketStreams *pDatabaseTMPacketStreams, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CANDLayout *pANDLayout, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CGRDLayout *pGRDLayout, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CPODLayout *pPODLayout, UINT nControlID = -1) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacket *pDatabaseTMPacket, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCPacket *pDatabaseTCPacket, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunction *pDatabaseTCFunction, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCSequence *pDatabaseTCSequence, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameter *pDatabaseTCParameter, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeaders *pDatabaseTMPacketHeaders, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeaders *pDatabaseTMPacketHeaders, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStreams *pDatabaseTMPacketStreams, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStreams *pDatabaseTMPacketStreams, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, CStringArray &szIssues) CONST;

private:
	VOID UpdateTable(CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	VOID UpdateTable(CDatabaseTableView *pView, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
	VOID UpdateTable(CDatabaseTableView *pView, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	VOID UpdateTable(CDatabaseTableView *pView, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);

public:
	virtual INT EnumDBMSTables(CStringArray &szTables, CStringArray &szDescriptions) CONST;
	virtual BOOL GetDBMSTableCharacteristics(LPCTSTR pszTable, CStringArray &szColumns, CStringArray &szDataTypes, CStringArray &szDefaults, CByteArray &bAllowNulls) CONST;

	virtual BOOL UsesDBMSTables(ULONGLONG nComponent) CONST;

private:
	INT ConstructTMPacketTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacket *pDatabaseTMPacket, CStringArray &szContents) CONST;
	INT ConstructTMPacketTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketHeadersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketHeadersTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketHeadersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketStreamsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketStreamsTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketStreamsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCFunctionTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCFunctionTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunction *pDatabaseTCFunction, CStringArray &szContents) CONST;
	INT ConstructTCFunctionTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCFunctionElementsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCFunctionElementsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCFunctionElementsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCPacketTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCPacketTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCPacket *pDatabaseTCPacket, CStringArray &szContents) CONST;
	INT ConstructTCPacketTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCPacketParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCPacketParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCPacket *pDatabaseTCPacket, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCPacketParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCPreExeGroupsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCPreExeGroupsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, CStringArray &szContents) CONST;
	INT ConstructTCPreExeGroupsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCPreExeGroupParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCPreExeGroupParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCPreExeGroupParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCExeVerGroupsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCExeVerGroupParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterSetsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterSetMembersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetMembersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetMembersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterSetsAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCSequenceTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCSequenceTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCSequence *pDatabaseTCSequence, CStringArray &szContents) CONST;
	INT ConstructTCSequenceTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCSequenceEntriesTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCSequenceEntriesTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCSequenceEntriesTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCSequenceParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCSequenceParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCSequenceParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCSequenceEntryParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCSequenceEntryParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCSequenceEntryParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCSequenceFunctionBlockTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCSequenceFunctionBlockTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, CStringArray &szContents) CONST;
	INT ConstructTCSequenceFunctionBlockTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCSequenceFunctionBlockElementsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCSequenceFunctionBlockElementsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCSequenceFunctionBlockElementsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, CStringArray &szContents) CONST;
	INT ConstructOBProcessorTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorMemoryAreasTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreasTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nCount, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreasTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorMemoryAreaBlocksTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreaBlocksTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nCount, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreaBlocksTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorMemoryAreaChecksumsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreaChecksumsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nCount, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreaChecksumsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorMemoryAreaCatalogueEntriesTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreaCatalogueEntriesTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nCount, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryAreaCatalogueEntriesTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorMemoryMasterImagesTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryMasterImagesTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, INT nCount, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryMasterImagesTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorMemoryImagesTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryImagesTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nCount, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryImagesTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructOBProcessorMemoryImagesAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryImagesAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, CStringArray &szContents) CONST;
	INT ConstructOBProcessorMemoryImagesAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMParameterTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMParameterTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, CStringArray &szContents) CONST;
	INT ConstructTMParameterTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalCurveTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMTxtCalCurveTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMTxtCalCurveTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, CStringArray &szContents) CONST;
	INT ConstructTMTxtCalCurveTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMTxtCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMTxtCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMTxtCalCurvePointsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMTxtCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMTxtCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMTxtCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumOolChecksTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumOolChecksTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, CStringArray &szContents) CONST;
	INT ConstructTMNumOolChecksTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMTxtOolChecksTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolChecksTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolChecksTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMTxtOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMTxtOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameter *pDatabaseTCParameter, CStringArray &szContents) CONST;
	INT ConstructTCParameterTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCNumCalCurveTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCNumCalCurveTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, CStringArray &szContents) CONST;
	INT ConstructTCNumCalCurveTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCTxtCalCurveTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCTxtCalCurveTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, CStringArray &szContents) CONST;
	INT ConstructTCTxtCalCurveTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCTxtCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCTxtCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCTxtCalCurvePointsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCNumOolChecksTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCNumOolChecksTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CStringArray &szContents) CONST;
	INT ConstructTCNumOolChecksTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCNumOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCNumOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCNumOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCTxtOolChecksTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolChecksTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolChecksTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCTxtOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolCheckLimitsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructANDTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructANDTableContents(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, CStringArray &szContents) CONST;
	INT ConstructANDTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructANDLayoutTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructANDLayoutTableContents(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, CStringArray &szContents) CONST;
	INT ConstructANDLayoutTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructANDParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructANDParametersTableContents(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructANDParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructGRDTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructGRDTableContents(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, CStringArray &szContents) CONST;
	INT ConstructGRDTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructGRDLayoutTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructGRDLayoutTableContents(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, CStringArray &szContents) CONST;
	INT ConstructGRDLayoutTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructGRDParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructGRDParametersTableContents(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructGRDParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructPODTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructPODTableContents(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, CStringArray &szContents) CONST;
	INT ConstructPODTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructPODLayoutTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructPODLayoutTableContents(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, CStringArray &szContents) CONST;
	INT ConstructPODLayoutTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructPODExpressionStackTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructPODExpressionStackTableContents(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructPODExpressionStackTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructPODParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructPODParametersTableContents(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructPODParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructPODFunctionsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructPODFunctionsTableContents(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructPODFunctionsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;

	VOID EmptyTableRow(CDatabaseTMPacketHeader *pDatabaseTMPacketHeader) CONST;
	VOID EmptyTableRow(CDatabaseTMPacketStream *pDatabaseTMPacketStream) CONST;
	VOID EmptyTableRow(CDatabaseTMPacketParameter *pDatabaseTMPacketParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCPacketParameter *pDatabaseTCPacketParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCFunctionElement *pDatabaseTCFunctionElement) CONST;
	VOID EmptyTableRow(CDatabaseTCFunctionBlockElement *pDatabaseTCFunctionBlockElement) CONST;
	VOID EmptyTableRow(CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;
	VOID EmptyTableRow(CDatabaseTCSequenceEntryParameter *pDatabaseTCSequenceEntryParameter) CONST;
	VOID EmptyTableRow(CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea) CONST;
	VOID EmptyTableRow(CDatabaseOBProcessorMemoryAreaBlock *pDatabaseOBProcessorMemoryAreaBlock) CONST;
	VOID EmptyTableRow(CDatabaseOBProcessorMemoryImageBlock *pDatabaseOBProcessorMemoryImageBlock) CONST;
	VOID EmptyTableRow(CDatabaseOBProcessorMemoryAreaCheckSum *pDatabaseOBProcessorMemoryAreaCheckSum) CONST;
	VOID EmptyTableRow(CDatabaseOBProcessorMemoryAreaCatalogueEntry *pDatabaseOBProcessorMemoryAreaCatalogueEntry) CONST;
	VOID EmptyTableRow(CDatabaseTMNumCalPoint *pDatabaseTMNumCalPoint) CONST;
	VOID EmptyTableRow(CDatabaseTMTxtCalPoint *pDatabaseTMTxtCalPoint) CONST;
	VOID EmptyTableRow(CDatabaseTMNumOolLimit *pDatabaseTMNumOolLimit) CONST;
	VOID EmptyTableRow(CDatabaseTMTxtOolLimit *pDatabaseTMTxtOolLimit) CONST;
	VOID EmptyTableRow(CDatabaseTCParameter *pDatabaseTCParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCNumCalPoint *pDatabaseTCNumCalPoint) CONST;
	VOID EmptyTableRow(CDatabaseTCTxtCalPoint *pDatabaseTCTxtCalPoint) CONST;
	VOID EmptyTableRow(CDatabaseTCNumOolLimit *pDatabaseTCNumOolLimit) CONST;
	VOID EmptyTableRow(CDatabaseTCTxtOolLimit *pDatabaseTCTxtOolLimit) CONST;
	VOID EmptyTableRow(CANDLayoutParameter *pParameter) CONST;
	VOID EmptyTableRow(CGRDLayoutParameter *pParameter) CONST;
	VOID EmptyTableRow(CPODLayoutExpression *pExpression) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCFunctionBlockElement *pDatabaseTCFunctionBlockElement) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCSequenceEntryParameter *pDatabaseTCSequenceEntryParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcessorMemoryArea) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseOBProcessorMemoryAreaBlock *pDatabaseOBProcessorMemoryAreaBlock) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseOBProcessorMemoryImageBlock *pDatabaseOBProcessorMemoryImageBlock) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseOBProcessorMemoryAreaCheckSum *pDatabaseOBProcessorMemoryAreaCheckSum) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseOBProcessorMemoryAreaCatalogueEntry *pDatabaseOBProcessorMemoryAreaCatalogueEntry) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMNumCalPoint *pDatabaseTMNumCalPoint) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMTxtCalPoint *pDatabaseTMTxtCalPoint) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMNumOolLimit *pDatabaseTMNumOolLimit) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMTxtOolLimit *pDatabaseTMTxtOolLimit) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCParameter *pDatabaseTCParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCNumCalPoint *pDatabaseTCNumCalPoint) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCTxtCalPoint *pDatabaseTCTxtCalPoint) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCNumOolLimit *pDatabaseTCNumOolLimit) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCTxtOolLimit *pDatabaseTCTxtOolLimit) CONST;
	BOOL IsTableRowEmpty(CONST CANDLayoutParameter *pParameter) CONST;
	BOOL IsTableRowEmpty(CONST CGRDLayoutParameter *pParameter) CONST;
	BOOL IsTableRowEmpty(CONST CPODLayoutExpression *pExpression) CONST;

	INT CalcTableColumnWidth(CONST CStringArray &szItems) CONST;

private:
	VOID ShowCompileMessages(CALTELDatabaseRecordset *pRecordset);
	BOOL ShowCompileMessage(LPCTSTR pszMessage, BOOL bTimestamp = TRUE, BOOL bAudition = FALSE);
	BOOL ShowCompileMessage(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszMessage, BOOL bWarning, BOOL bTimestamp = TRUE, BOOL bAudition = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELMemoryDumpsServiceEngine

class AFX_EXT_CLASS CALTELMemoryDumpsServiceEngine : public CMemoryDumpsServiceEngine
{
	// Construction
public:

	// Attributes
public:

	// Operators
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
	virtual CString GetMemoryDumpFTPFileName(CONST CMemoryDump *pMemoryDump, UINT nFormat = 0) CONST;
	virtual CString GetMemoryDumpSearchFileName(LPCTSTR pszPrefix, LPCTSTR pszExtension) CONST;
	virtual CTimeSpan GetMemoryDumpInterval(UINT nSource, UINT nSubSystem) CONST;
	virtual UINT GetMemoryDumpIntervalTolerance(UINT nSource, UINT nSubSystem) CONST;

	virtual CString FormatMemoryDumpData(CONST CMemoryDump *pMemoryDump, UINT nFormat = 0) CONST;

	virtual BOOL IsServiceSupported() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELTPEPServiceEngine

class AFX_EXT_CLASS CALTELTPEPServiceEngine : public CTPEPServiceEngine
{
	// Construction
public:
	CALTELTPEPServiceEngine();
	~CALTELTPEPServiceEngine();

	// Attributes
private:
	CUIntArray  m_pAPIDs;
	CUIntArray  m_pAPIDSequenceCounts;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operators
public:
	virtual UINT GetTPEPSupport() CONST;

	virtual UINT GetTPEPSpacecraftID() CONST;

	virtual CString GetTPEPTimeKeyFormat() CONST;
	virtual CString GetTPEPRetrieveTimeKeyFormat() CONST;

	virtual INT EnumTPEPTMUnits(CONST CDatabaseEngine *pDatabase, CONST CStringArray &szParameters, CStringArray &szTMUnits) CONST;
	virtual INT EnumTPEPTMUnitParameters(CONST CDatabaseEngine *pDatabase, CONST CTMUnit *pTMUnit, CTPEPConnection *pConnection, BOOL bAll, CStringArray &szParameters) CONST;

	virtual BOOL GenerateTPEPRandomData(CONST CDatabaseEngine *pDatabase, CTPEPConnection *pConnection, CTMEnvironment *pTMEnvironment);

private:
	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELPFLPServiceEngine

class AFX_EXT_CLASS CALTELPFLPServiceEngine : public CPFLPServiceEngine
{
	// Construction
public:

	// Attributes
public:

	// Operators
public:
	virtual BOOL IsServiceSupported() CONST;

	virtual BOOL FilterPFLPTMUnits(CONST CTMEnvironment *pTMEnvironment, BYTE nManipulationCode, BYTE nGroupIdentifier, WORD wDataIdentifier) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELTMProcessInfo

class AFX_EXT_CLASS CALTELTMProcessInfo : public CTMProcessInfo
{
	// Construction
public:
	CALTELTMProcessInfo();

	// Attributes
private:
	BOOL  m_bOBRT;
	UINT  m_nOBRT;
	TIMETAG  m_tOBRT[2];
private:
	LONG  m_tError;
	LONG  m_tDelta;
private:
	typedef struct tagDATA {
		BOOL  bOBRT;
		UINT  nOBRT;
		TIMETAG  tOBRT;
	} DATA, *PDATA, *LPDATA;

	// Operations
public:
	VOID SetTimeCorrelation(CONST CTimeTag &tOBRT = 0, UINT nOBRT = 0);
	CTimeTag GetTimeCorrelation(CTimeTag &tOBRT, UINT &nOBRT) CONST;
	VOID SetTimeCorrelationError(LONG tError, LONG tDelta = 0);
	BOOL GetTimeCorrelationError(LONG &tError, LONG &tDelta) CONST;

	virtual BOOL GetTMBandwidth(double &fTotalTMBandwidth, double &fMaxDiagnosticTMBandwidth) CONST;

	virtual BOOL SetData(CONST CByteArray &nData);
	virtual INT GetData(CByteArray &nData) CONST;

	virtual VOID Reset();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELTMProcessEngine

class AFX_EXT_CLASS CALTELTMProcessEngine : public CTMProcessEngine
{
	// Construction
public:
	CALTELTMProcessEngine();

	// Attributes
private:
	UINT  m_nTMServiceLevel;

	// Operations
public:
	virtual UINT DetectTMServiceLevel() CONST;

public:
	virtual INT EnumSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	virtual UINT TranslateSubSystemToID(LPCTSTR pszSubSystem) CONST;
	virtual CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

public:
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

	virtual BOOL CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTMParameter *pTMParameter, INT nCalTableRef, INT nOolTableRef, ULONGLONG nValue, ULONGLONG nOldValue, INT nOldCalTableRef, BOOL bOldValue, UINT &nOolLimit, UINT &nOolStatus) CONST;
	virtual BOOL ConvertTMParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTMParameter *pTMParameter, INT nCalTableRef, LPCTSTR pszValue, ULONGLONG &nValue) CONST;

public:
	virtual BOOL AllocateTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST;
	virtual BOOL FreeTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST;

private:
	BOOL UpdateTMPacketCache(CTMEnvironment *pTMEnvironment) CONST;

	VOID ProcessTMParameter(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter, ULONGLONG nValue) CONST;
	BOOL ProcessTMParameter(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CTMParameter *pTMParameter) CONST;
	UINT CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CTMParameter *pTMParameter, ULONGLONG nValue, LPCTSTR pszCalTable, WORD &wOolTable, WORD &wOolLimit) CONST;
	UINT CheckTMParameterValidityValue(CONST CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CONST CTMParameter *pTMParameter) CONST;
	UINT CheckTMParameterValidityValue(CONST CTMParameter *pTMParameter) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELTCProcessInfo

class AFX_EXT_CLASS CALTELTCProcessInfo : public CTCProcessInfo
{
	// Construction
public:
	CALTELTCProcessInfo();
	~CALTELTCProcessInfo();

	// Attributes
private:
	BOOL  m_bOBRT;
	UINT  m_nOBRT;
	TIMETAG  m_tOBRT[2];
private:
	typedef struct tagDATA {
		INT  cbSize;
		BOOL  bOBRT;
		UINT  nOBRT;
		TIMETAG  tOBRT;
	} DATA, *PDATA, *LPDATA;

	// Operations
public:
	VOID SetTimeCorrelation(CONST CTimeTag &tOBRT = 0, UINT nOBRT = 0);
	CTimeTag GetTimeCorrelation(CTimeTag &tOBRT, UINT &nOBRT) CONST;

	INT GenerateTCPacketSequenceCount(LPCTSTR pszName, INT nAPID, INT nTCID, ULONGLONG nFlags, BOOL bExample = FALSE);

	virtual BOOL SetData(CONST CByteArray &nData);
	virtual INT GetData(CByteArray &nData) CONST;

	virtual VOID Reset();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELTCProcessEngine

// Specify telecommand packet sequence related identifiers
#define PSC_NUM_COUNTER_BITS   (14-PSC_NUM_SOURCE_BITS)
#define PSC_NUM_SOURCE_BITS   0

class AFX_EXT_CLASS CALTELTCProcessEngine : public CTCProcessEngine
{
	// Construction
public:
	CALTELTCProcessEngine();

	// Attributes
private:
	UINT  m_nTCServiceLevel;
	BOOL  m_bDebugging;
private:
	CTimeSpan  m_tTCFunctionExecutionTimeOffset[2];
	CTimeSpan  m_tTCFunctionParameterTimeOffset[2];
private:
	WORD  m_wTCPacketCRC16Table[256];
	DWORD  m_dwTCPacketCRC32Table[256];

	// Operations
public:
	virtual UINT DetectTCServiceLevel() CONST;

public:
	virtual INT EnumSubSystems(CStringArray &szSubSystems, BOOL bAll = TRUE) CONST;
	virtual UINT TranslateSubSystemToID(LPCTSTR pszSubSystem) CONST;
	virtual CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

public:
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
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, CONST CTimeTag &tTime, ULONGLONG &nValue) CONST;
	virtual BOOL ConvertTCParameterTimeValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, LPCTSTR pszTag, INT nWidth, ULONGLONG nValue, CTimeTag &tTime) CONST;

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
	virtual UINT ConvertTimeToOBRT(CONST CTCEnvironment *pTCEnvironment, CONST CTimeTag &tTime, UINT nOBTID = 0) CONST;
	virtual BOOL CanConvertTimeToOBRT(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID = 0) CONST;
	virtual CTimeTag ConvertOBRTToTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBRT, UINT nOBTID = 0) CONST;
	virtual BOOL CanConvertOBRTToTime(CONST CTCEnvironment *pTCEnvironment, UINT nOBTID = 0) CONST;

	virtual BOOL EnableDebugging(BOOL bEnable = TRUE);
	virtual BOOL IsDebuggingEnabled() CONST;

public:
	virtual BOOL AllocateTCProcessInfo(CTCEnvironment *pTCEnvironment) CONST;
	virtual BOOL FreeTCProcessInfo(CTCEnvironment *pTCEnvironment) CONST;

private:
	BOOL Generate2ndStep(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets) CONST;

	VOID CheckTCFunctionPreexecutionParameterValues(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter, CONST CTMParameter *pTMParameter, CStringArray &szParameters) CONST;
	BOOL CheckTCFunctionExecutionParameterValues(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter, CONST CTMParameter *pTMParameter, CStringArray &szParameters, BOOL bInInterval) CONST;
	BOOL CheckTCFunctionExecutionParameterValues(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, CTMParameter *pTMParameter, CStringArray &szParameters, BOOL bInInterval) CONST;

	BOOL ConvertTCParameterValues(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CONST CDatabaseTCFunctions &pDatabaseTCFunctions, CONST CDatabaseTCPackets &pDatabaseTCPackets) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, ULONGLONG nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, ULONGLONG nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, ULONGLONG nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, ULONGLONG nValue) CONST;

	BOOL IsTCParameterNumerical(CONST CDatabaseEngine *pDatabase, LPCTSTR pszTag) CONST;
	BOOL IsTCParameterTextual(CONST CDatabaseEngine *pDatabase, LPCTSTR pszTag) CONST;

	INT CalculateDataSize(CONST CDatabaseTCPacket *pDatabaseTCPacket) CONST;

	WORD CalculateCRC(CONST CByteArray &nData, BOOL bHighPriority = FALSE) CONST;
	WORD CalculateCRC16(CONST CByteArray &nData, WORD wSeed = 0xFFFF, BOOL bXOR = TRUE) CONST;
	DWORD CalculateCRC32(CONST CByteArray &nData, DWORD dwSeed, BOOL bXOR = TRUE) CONST;

	BOOL IsFixedSize(CONST CDatabaseTCPacket *pDatabaseTCPacket) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CALTELLibraryApp application

class AFX_EXT_CLASS CALTELLibraryApp : public CLibraryApp
{
	// Construction
public:

	// Attributes
public:
	CALTELDatabaseEngine  m_cDatabaseEngine;
	CALTELTMProcessEngine  m_cTMProcessEngine;
	CALTELTCProcessEngine  m_cTCProcessEngine;
	CALTELMemoryDumpsServiceEngine  m_cMemoryDumpsServiceEngine;
	CALTELTPEPServiceEngine  m_cTPEPServiceEngine;
	CALTELPFLPServiceEngine  m_cPFLPServiceEngine;

	// Operations
public:
	CALTELDatabaseEngine *GetDatabaseEngine() CONST;
	CALTELTMProcessEngine *GetTMProcessEngine() CONST;
	CALTELTCProcessEngine *GetTCProcessEngine() CONST;
	CALTELMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine() CONST;
	CALTELTPEPServiceEngine *GetTPEPServiceEngine() CONST;
	CALTELPFLPServiceEngine *GetPFLPServiceEngine() CONST;

	static CALTELLibraryApp *GetLibraryApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CALTELLibraryApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CALTELLibraryApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
#ifdef ALTELENVIRONMENT
inline CALTELDatabaseEngine *GetDatabaseEngine()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetDatabaseEngine());
}
inline CALTELTMProcessEngine *GetTMProcessEngine()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetTMProcessEngine());
}
inline CALTELTCProcessEngine *GetTCProcessEngine()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetTCProcessEngine());
}
inline CALTELMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetMemoryDumpsServiceEngine());
}
inline CALTELTPEPServiceEngine *GetTPEPServiceEngine()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetTPEPServiceEngine());
}
inline CALTELPFLPServiceEngine *GetPFLPServiceEngine()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetPFLPServiceEngine());
}
inline LPCTSTR STRING(INT nID)
{
	return(CALTELLibraryApp::GetLibraryApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(CALTELLibraryApp::GetLibraryApp()->StringChar(nID));
}
inline LPCTSTR GetLibraryName()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetLibraryName());
}
inline HINSTANCE GetLibraryInstance()
{
	return(CALTELLibraryApp::GetLibraryApp()->GetLibraryInstance());
}
#endif

// Specify the associated export definitions
extern "C"
{
	__declspec(dllexport) CDatabaseEngine *GetStandardDatabaseEngineProc();
	__declspec(dllexport) CDatabaseEngine *GetDatabaseEngineProc();
	__declspec(dllexport) CTMProcessEngine *GetTMProcessEngineProc();
	__declspec(dllexport) CTCProcessEngine *GetTCProcessEngineProc();
	__declspec(dllexport) CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngineProc();
	__declspec(dllexport) CTPEPServiceEngine *GetTPEPServiceEngineProc();
	__declspec(dllexport) CPFLPServiceEngine *GetPFLPServiceEngineProc();
}

/////////////////////////////////////////////////////////////////////////////


#endif // __ALTEL_H__
