// SCOS-2000.H : SCOS-2000 Database Driver.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the SCOS-2000 database driver related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2012/06/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SCOS2000_H__
#define __SCOS2000_H__

#ifndef RC_INVOKED
#include "SatView.h"
#endif

#include "resource.h"		// main symbols
#include "SCOS-2000.rh"

#include "VALue.h"
#include "TDSTime.h"
#include "dialogs.h"
#include "records.h"


#define CCSDS_APID_TIME   0x0000
#define CCSDS_APID_IDLE   0x03FF

#define SCOS2000_TMPACKET_HEADERSIZE   76

#define SCOS2000_AND_COLUMNSIZE   32


/////////////////////////////////////////////////////////////////////////////
// CSCOS2000DatabaseEngine

class AFX_EXT_CLASS CSCOS2000DatabaseEngine : public CDatabaseEngine
{
	// Construction
public:
	CSCOS2000DatabaseEngine();
	~CSCOS2000DatabaseEngine();

	// Attributes
protected:
	CDatabaseTCExeVerStages  *m_pTCExeVerStages[2];
	CDatabaseTCParameterValueSets  *m_pTCParameterValueSets[2];
	CDatabaseTCFunctionRoutingPaths  *m_pTCFunctionRoutingPaths[2];

	// Operations
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
	virtual BOOL Save(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage);
	virtual BOOL Save(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup);
	virtual BOOL Save(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup);
	virtual BOOL Save(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);
	virtual BOOL Save(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);
	virtual BOOL Save(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);
	virtual BOOL Save(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock);
	virtual BOOL Save(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup);
	virtual BOOL Save(CONST CDatabaseTCPacketParameter *pDatabseTCPacketParameter);
	virtual BOOL Save(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet);
	virtual BOOL Save(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath);
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
	virtual BOOL Delete(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage);
	virtual BOOL Delete(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup);
	virtual BOOL Delete(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup);
	virtual BOOL Delete(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader);
	virtual BOOL Delete(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream);
	virtual BOOL Delete(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet);
	virtual BOOL Delete(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock);
	virtual BOOL Delete(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup);
	virtual BOOL Delete(CONST CDatabaseTCPacketParameter *pDatabseTCPacketParameter);
	virtual BOOL Delete(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet);
	virtual BOOL Delete(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath);
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
	virtual CDatabaseTCExeVerStages *GetTCExeVerStages() CONST;
	virtual CDatabaseTCExeVerGroups *GetTCExeVerGroups() CONST;
	virtual CDatabaseTMPacketGroups *GetTMPacketGroups() CONST;
	virtual CDatabaseTMPacketHeaders *GetTMPacketHeaders() CONST;
	virtual CDatabaseTMPacketStreams *GetTMPacketStreams() CONST;
	virtual CDatabaseTCParameterSets *GetTCParameterSets() CONST;
	virtual CDatabaseTCFunctionBlocks *GetTCFunctionBlocks() CONST;
	virtual CDatabaseTMParameterGroups *GetTMParameterGroups() CONST;
	virtual CDatabaseTCPacketParameters *GetTCPacketParameters() CONST;
	virtual CDatabaseTCParameterValueSets *GetTCParameterValueSets() CONST;
	virtual CDatabaseTCFunctionRoutingPaths *GetTCFunctionRoutingPaths() CONST;
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

private:
	BOOL SaveVersions();
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
	BOOL LoadVersions();
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

	VOID CompileVersions(CBinaryDatabase *pDatabase);
	VOID CompileTMPackets(CBinaryDatabase *pDatabase);
	VOID CompileTCPackets(CBinaryDatabase *pDatabase);
	VOID CompileTCFunctions(CBinaryDatabase *pDatabase);
	VOID CompileTCSequences(CBinaryDatabase *pDatabase);
	VOID CompileOBProcessors(CBinaryDatabase *pDatabase);
	VOID CompileTMParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCParameters(CBinaryDatabase *pDatabase);
	VOID CompileTMParameterGroups(CBinaryDatabase *pDatabase);
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
	VOID CompileTMPacketParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCPacketParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCFunctionElements(CBinaryDatabase *pDatabase);
	VOID CompileTCSequenceParameters(CBinaryDatabase *pDatabase);
	VOID CompileTCSequenceEntryParameters(CBinaryDatabase *pDatabase);
	VOID CompileANDs(CBinaryDatabase *pDatabase);
	VOID CompileGRDs(CBinaryDatabase *pDatabase);
	VOID CompilePODs(CBinaryDatabase *pDatabase);

	INT EnumTMPacketParameterGroup(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, INT nIndex, INT nSize) CONST;

	BOOL SaveTMParameterDerivationCode(CONST CDatabaseTMParameter *pDatabaseTMParameter);
	BOOL LoadTMParameterDerivationCode(CDatabaseTMParameter *pDatabaseTMParameter) CONST;
	BOOL TranslateTMParameterDerivationCode(LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszScript, CString &szCode, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL TranslateTMParameterOLScript(LPCTSTR pszTag, LPCTSTR pszScript, CString &szCode, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL TranslateTMParameterHardcodedScript(LPCTSTR pszTag, LPCTSTR pszScript, CString &szCode, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLStatementSequence(LPCTSTR pszTag, LPCTSTR pszScript, INT nBlockLevel, INT &nPos, CString &szStatements, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLStatement(LPCTSTR pszTag, LPCTSTR pszScript, INT nBlockLevel, INT &nPos, CString &szStatement, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLIfStatement(LPCTSTR pszTag, LPCTSTR pszScript, INT nBlockLevel, INT &nPos, CString &szStatement, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLReturnStatement(LPCTSTR pszTag, LPCTSTR pszScript, INT nBlockLevel, INT &nPos, CString &szStatement, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLSimpleStatement(LPCTSTR pszTag, LPCTSTR pszScript, INT nBlockLevel, INT &nPos, CString &szStatement, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLExpression(LPCTSTR pszTag, LPCTSTR pszScript, INT &nPos, CString &szExpression, CString &szDataType, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLAssignExpression(LPCTSTR pszTag, LPCTSTR pszScript, INT &nPos, CString &szExpression, CString &szDataType, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLRelExpression(LPCTSTR pszTag, LPCTSTR pszScript, INT &nPos, CString &szExpression, CString &szDataType, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLAddExpression(LPCTSTR pszTag, LPCTSTR pszScript, INT &nPos, CString &szExpression, CString &szDataType, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLMulExpression(LPCTSTR pszTag, LPCTSTR pszScript, INT &nPos, CString &szExpression, CString &szDataType, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLOperand(LPCTSTR pszTag, LPCTSTR pszScript, INT &nPos, CString &szOperand, CString &szDataType, CStringArray &szParameters, CStringArray &szVariables, CStringArray &szDataTypes, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLTerm(LPCTSTR pszTag, LPCTSTR pszScript, CONST CStringArray &szVariables, CONST CStringArray &szDataTypes, INT &nPos, CString &szTerm, CString &szDataType, CStringArray &szParameters, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLIdentifier(LPCTSTR pszTag, LPCTSTR pszScript, INT &nPos, CString &szIdentifier, CString &szDataType, CStringArray &szParameters, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLEntity(LPCTSTR pszTag, LPCTSTR pszScript, CONST CStringArray &szVariables, CONST CStringArray &szDataTypes, INT &nPos, CString &szEntity, CString &szDataType, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ParseTMParameterOLVariable(LPCTSTR pszTag, LPCTSTR pszScript, CONST CStringArray &szVariables, CONST CStringArray &szDataTypes, BOOL bDefinition, BOOL bLocal, INT &nPos, CString &szVariable, CString &szDataType, CStringArray &szErrors, CUIntArray &nErrors, CByteArray &bErrors) CONST;
	BOOL ConvertTMParameterDerivationCodePositionToLine(CONST CUIntArray &nBreaks, INT nPos, INT &nLine, INT &nColumn) CONST;
	BOOL CalculateTMParameterDerivationCodeLineBreaks(LPCTSTR pszScript, CUIntArray &nBreaks) CONST;
	CString FormatTMParameterDerivationCode(LPCTSTR pszScript, INT nBlockLevel) CONST;

	BOOL ConvertTCParameterConstValue(LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST;
	BOOL ConvertTCParameterConstValue(CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST;

	BOOL CheckTCSequenceNesting(CBinaryDatabase *pDatabase, LPCTSTR pszName, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;
	BOOL CheckTCSequenceNesting(CBinaryDatabase *pDatabase, CStringArray &szNames, CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;

	INT EnumTCSequenceFiles(CBinaryDatabase *pDatabase, CStringArray &szFiles) CONST;
	INT EnumTCSequenceFiles(CBinaryDatabase *pDatabase, LPCTSTR pszDirectory, CStringArray &szFiles) CONST;
	BOOL ParseTCSequenceFile(LPCTSTR pszFileName) CONST;
	BOOL ParseTCSequenceFile(LPCTSTR pszFileName, CDatabaseTCSequences &pDatabaseTCSequences) CONST;
	BOOL ParseTCSequenceFile(LPCTSTR pszFileName, CDatabaseTCSequences &pDatabaseTCSequences, CStringArray &szNames, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseTCSequenceData(LPCTSTR pszFileName, LPCTSTR pszXmlData, CDatabaseTCSequences &pDatabaseTCSequences, CStringArray &szNames, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseTCSequenceEntriesData(LPCTSTR pszXmlData, CDatabaseTCSequence *pDatabaseTCSequence, CStringArray &szNames, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseTCSequenceEntryParametersData(LPCTSTR pszXmlData, CONST CDatabaseTCSequence *pDatabaseTCSequence, CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry, INT nEntryNo, CStringArray &szNames, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseTCSequenceParametersData(LPCTSTR pszXmlData, CDatabaseTCSequence *pDatabaseTCSequence, CStringArray &szNames, CStringArray &szMessages, CByteArray &bErrors) CONST;

	INT EnumDisplayFiles(CONST CBinaryDatabase *pDatabase, ULONGLONG nComponent, CStringArray &szFiles) CONST;
	INT EnumDisplayFiles(CONST CBinaryDatabase *pDatabase, ULONGLONG nComponent, LPCTSTR pszDirectory, CStringArray &szFiles) CONST;
	BOOL ParseDisplayFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, ULONGLONG nComponent) CONST;
	BOOL ParseDisplayFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, CANDLayouts &pLayouts) CONST;
	BOOL ParseDisplayFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, CGRDLayouts &pLayouts) CONST;
	BOOL ParseDisplayFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, CPODLayouts &pLayouts) CONST;
	BOOL ParseDisplayFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, CANDLayouts &pLayouts, CStringArray &szLayouts, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseDisplayFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, CGRDLayouts &pLayouts, CStringArray &szLayouts, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseDisplayFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, CPODLayouts &pLayouts, CStringArray &szLayouts, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseDisplayData(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, LPCTSTR pszXmlData, CANDLayouts &pLayouts, CStringArray &szLayouts, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseDisplayData(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, LPCTSTR pszXmlData, CGRDLayouts &pLayouts, CStringArray &szLayouts, CStringArray &szMessages, CByteArray &bErrors) CONST;
	BOOL ParseDisplayData(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFileName, LPCTSTR pszXmlData, CPODLayouts &pLayouts, CStringArray &szLayouts, CStringArray &szMessages, CByteArray &bErrors) CONST;

	BOOL LoadFile(LPCTSTR pszFileName, CString &szData) CONST;

	BOOL ExtractXmlTag(CString &szXmlData, LPCTSTR pszTag, CString &szData, BOOL bEmpty = FALSE) CONST;
	BOOL ExtractXmlTag(CString &szXmlData, LPCTSTR pszTag, CONST CStringArray &szSubTags, CString &szData, BOOL bEmpty = FALSE) CONST;
	BOOL ExtractXmlData(CString &szXmlData, LPCTSTR pszOpenTag, LPCTSTR pszCloseTag, CString &szData) CONST;
	BOOL ExtractXmlAttribute(LPCTSTR pszXmlData, LPCTSTR pszAttribute, BOOL bRequired, CString &szData) CONST;
	BOOL ExtractXmlAttribute(LPCTSTR pszXmlData, LPCTSTR pszAttribute, BOOL bRequired, CString &szData, BOOL &bDuplicate) CONST;

	VOID ReplaceXmlTag(CString &szXmlData, LPCTSTR pszTag, LPCTSTR pszNameTag, LPCTSTR pszName, LPCTSTR pszData) CONST;

	ULONGLONG TranslateXmlAttributes(ULONGLONG nAttributes, LPCTSTR pszRepresentation, LPCTSTR pszFormat) CONST;
	ULONGLONG TranslateXmlAttributes(ULONGLONG nAttributes, LPCTSTR pszRepresentation) CONST;

	BOOL CheckTag(LPCTSTR pszTag, INT nLength, BOOL bVariable = TRUE) CONST;
	BOOL CheckName(LPCTSTR pszName, INT nLength, BOOL bVariable = TRUE) CONST;
	BOOL CheckIdentifier(LPCTSTR pszIdentifier, INT nMinLength, INT nMaxLength, BOOL bTag = TRUE) CONST;

	CString ReadNumber(LPCTSTR pszCode, INT &nPos) CONST;

	INT SkipWhiteSpaces(LPCTSTR pszCode, INT &nPos) CONST;
	INT SkipSpaces(LPCTSTR pszCode, INT &nPos) CONST;

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
	virtual BOOL CheckTMPacketID(UINT nID) CONST;
	virtual BOOL GetTMPacketIDRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTMPacketType(INT nType) CONST;
	virtual BOOL GetTMPacketTypeRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketSubType(INT nSubType) CONST;
	virtual BOOL GetTMPacketSubTypeRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMPacketDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTMPacketDescriptionLength() CONST;
	virtual BOOL CheckTMPacketSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTMPacketSubSystemLength() CONST;
	virtual BOOL CheckTMPacketAPID(INT nAPID) CONST;
	virtual BOOL GetTMPacketAPIDRange(INT &nLow, INT &nHigh) CONST;
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
	virtual INT EnumTMPacketTimestampFlags(CStringArray &szFlags, CUIntArray &nFlags) CONST;
	virtual BOOL CheckTMPacketTimestampFlag(LPCTSTR pszFlag) CONST;
	virtual INT GetTMPacketTimestampFlagLength() CONST;
	virtual INT TranslateTMPacketTimestampFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketTimestampFlag(INT nFlag, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumTMPacketEventTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckTMPacketEventType(UINT nType) CONST;
	virtual INT GetTMPacketEventTypeLength() CONST;
	virtual INT TranslateTMPacketEventType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMPacketEventType(INT nType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTMPacketEventID(INT nType, LPCTSTR pszEventID) CONST;
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
	virtual BOOL CheckTMPacketDataSize(INT cbData, INT nFlag) CONST;
	virtual BOOL GetTMPacketDataSizeRange(INT &nLow, INT &nHigh) CONST;
	virtual INT GetTMPacketDataSize() CONST;
	virtual INT GetTMPacketDataFieldHeaderSize() CONST;
	virtual INT GetTMPacketTotalSize() CONST;
	virtual BOOL CheckTMPacketHeaderTMTypePosition(INT nByte, INT nBit, INT nLength) CONST;
	virtual BOOL GetTMPacketHeaderTMTypePositionRange(INT &nOffsetLow, INT &nOffsetHigh, INT &nLengthLow, INT &nLengthHigh) CONST;
	virtual BOOL CheckTMPacketHeaderTMIDPosition(INT nByte, INT nBit, INT nLength) CONST;
	virtual BOOL GetTMPacketHeaderTMIDPositionRange(INT &nOffsetLow, INT &nOffsetHigh, INT &nLengthLow, INT &nLengthHigh) CONST;
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
	virtual BOOL CheckTCPacketDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCPacketDescriptionLength() CONST;
	virtual INT GetTCPacketDataSize() CONST;
	virtual INT GetTCPacketDataFieldHeaderSize() CONST;
	virtual INT GetTCPacketTotalSize() CONST;
	virtual BOOL CheckTCPacketParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCPacketParameterTagLength() CONST;
	virtual BOOL CheckTCPacketParameterDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCPacketParameterDescriptionLength() CONST;
	virtual INT EnumTCPacketParameterTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCPacketParameterType(LPCTSTR pszTag, ULONGLONG nType) CONST;
	virtual INT GetTCPacketParameterTypeLength() CONST;
	virtual ULONGLONG TranslateTCPacketParameterType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCPacketParameterType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
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

	virtual BOOL CheckTCFunctionName(LPCTSTR pszName) CONST;
	virtual INT GetTCFunctionNameLength() CONST;
	virtual BOOL CheckTCFunctionDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCFunctionDescriptionLength() CONST;
	virtual BOOL CheckTCFunctionDetails(LPCTSTR pszDetails) CONST;
	virtual INT GetTCFunctionDetailsLength() CONST;
	virtual INT EnumTCFunctionTypes(CStringArray &szTypes, CLongUIntArray &nTypes) CONST;
	virtual BOOL CheckTCFunctionType(ULONGLONG nType) CONST;
	virtual INT GetTCFunctionTypeLength() CONST;
	virtual ULONGLONG TranslateTCFunctionType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCFunctionType(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckTCFunctionAPID(INT nAPID) CONST;
	virtual BOOL GetTCFunctionAPIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionTCType(ULONGLONG nTCType) CONST;
	virtual BOOL GetTCFunctionTCTypeRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionTCID(INT nTCID) CONST;
	virtual BOOL GetTCFunctionTCIDRange(INT &nLow, INT &nHigh) CONST;
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
	virtual BOOL CheckTCFunctionDestinationSubSystemID(INT nSubSystemID) CONST;
	virtual BOOL GetTCFunctionDestinationSubSystemIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionDestinationSubScheduleID(INT nSubScheduleID) CONST;
	virtual BOOL GetTCFunctionDestinationSubScheduleIDRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCFunctionDefaultParameterSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCFunctionDefaultParameterSetNameLength() CONST;
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
	virtual BOOL CheckTCFunctionElementConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCFunctionElementConstTimeLength() CONST;
	virtual CTimeTag TranslateTCFunctionElementConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;

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
	virtual BOOL CheckTCSequenceDefaultParameterSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCSequenceDefaultParameterSetNameLength() CONST;
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
	virtual BOOL CheckTCSequenceParameterCalTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCSequenceParameterCalTableLength() CONST;
	virtual BOOL CheckTCSequenceParameterOolTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTCSequenceParameterOolTableLength() CONST;
	virtual BOOL CheckTCSequenceParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCSequenceParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTCSequenceParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCSequenceParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
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
	virtual BOOL CheckTCSequenceEntryIndex(INT nIndex) CONST;
	virtual BOOL GetTCSequenceEntryIndexRange(INT &nLow, INT &nHigh) CONST;
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
	virtual BOOL CheckTCSequenceEntryParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCSequenceEntryParameterConstValueLength() CONST;
	virtual BOOL CheckTCSequenceEntryParameterBitOffset(INT nOffset) CONST;
	virtual BOOL GetTCSequenceEntryParameterBitOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual ULONGLONG TranslateTCSequenceEntryParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCSequenceEntryParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTCSequenceEntryParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCSequenceEntryParameterConstTimeLength() CONST;
	virtual CTimeTag TranslateTCSequenceEntryParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual BOOL CheckTCSequenceEntryParameterValueSetName(LPCTSTR pszName) CONST;
	virtual INT GetTCSequenceEntryParameterValueSetNameLength() CONST;

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
	virtual BOOL CheckOBProcessorAddressBase(UINT nWidth) CONST;
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
	virtual BOOL CheckTMParameterUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTMParameterUnitLength() CONST;
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
	virtual BOOL CheckTMParameterRelatedParameter(ULONGLONG nAttributes, LPCTSTR pszTag) CONST;
	virtual INT GetTMParameterRelatedParameterLength() CONST;
	virtual BOOL CheckTMParameterConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTMParameterConstValueLength() CONST;
	virtual ULONGLONG TranslateTMParameterConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTMParameterConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
	virtual BOOL CheckTMParameterCalibrationTable(ULONGLONG nAttributes, LPCTSTR pszTable) CONST;
	virtual INT GetTMParameterCalibrationTableLength() CONST;
	virtual BOOL CheckTMParameterSourceSubSystem(LPCTSTR pszSubSystem) CONST;
	virtual INT GetTMParameterSourceSubSystemLength() CONST;
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

	virtual BOOL CheckTMNumOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMNumOolTableNameLength() CONST;
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
	virtual INT EnumTMNumOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual BOOL CheckTMNumOolTableLimitType(UINT nLimitType) CONST;
	virtual INT GetTMNumOolTableLimitTypeLength() CONST;
	virtual INT TranslateTMNumOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMNumOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL GetTMNumOolTableLimitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTMNumOolTableLimitValueLength() CONST;
	virtual double TranslateTMNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTMNumOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual BOOL CheckTMNumOolTableLimitValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMNumOolTableLimitValidityParameterLength() CONST;
	virtual BOOL CheckTMNumOolTableLimitValidityValue(INT nValue) CONST;
	virtual BOOL GetTMNumOolTableLimitValidityValueRange(INT &nLow, INT &nHigh) CONST;

	virtual BOOL CheckTMTxtOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTMTxtOolTableNameLength() CONST;
	virtual BOOL CheckTMTxtOolTableCheckCount(INT nCount) CONST;
	virtual BOOL GetTMTxtOolTableCheckCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMTxtOolTableCheckCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMTxtOolTableCheckCount(INT nCount) CONST;
	virtual BOOL CheckTMTxtOolTableLimitCount(INT nCount) CONST;
	virtual BOOL GetTMTxtOolTableLimitCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTMTxtOolTableLimitCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTMTxtOolTableLimitCount(INT nCount) CONST;
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
	virtual INT EnumTMTxtOolTableLimitTypes(CStringArray &szLimitTypes, CUIntArray &nLimitTypes) CONST;
	virtual BOOL CheckTMTxtOolTableLimitType(UINT nLimitType) CONST;
	virtual INT GetTMTxtOolTableLimitTypeLength() CONST;
	virtual INT TranslateTMTxtOolTableLimitType(LPCTSTR pszLimitType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTMTxtOolTableLimitType(INT nLimitType, BOOL bDBMS = TRUE) CONST;
	virtual BOOL GetTMTxtOolTableLimitPositionRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTMTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTMTxtOolTableLimitValueLength() CONST;
	virtual double TranslateTMTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTMTxtOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual BOOL CheckTMTxtOolTableLimitValidityParameter(LPCTSTR pszTag) CONST;
	virtual INT GetTMTxtOolTableLimitValidityParameterLength() CONST;
	virtual BOOL CheckTMTxtOolTableLimitValidityValue(INT nValue) CONST;
	virtual BOOL GetTMTxtOolTableLimitValidityValueRange(INT &nLow, INT &nHigh) CONST;

	virtual BOOL CheckTCParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetTCParameterTagLength() CONST;
	virtual BOOL CheckTCParameterDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCParameterDescriptionLength() CONST;
	virtual BOOL CheckTCParameterUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTCParameterUnitLength() CONST;
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
	virtual INT EnumTCParameterRadixes(CStringArray &szRadixes, CLongUIntArray &nRadixes) CONST;
	virtual BOOL CheckTCParameterRadix(ULONGLONG nAttributes, ULONGLONG nRadix) CONST;
	virtual INT GetTCParameterRadixLength() CONST;
	virtual ULONGLONG TranslateTCParameterRadix(LPCTSTR pszRadix, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterRadix(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;
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
	virtual BOOL CheckTCParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual INT GetTCParameterConstTimeLength() CONST;
	virtual CTimeTag TranslateTCParameterConstTime(ULONGLONG nAttributes, LPCTSTR pszConstTime) CONST;
	virtual CString TranslateTCParameterConstTime(ULONGLONG nAttributes, CONST CTimeTag &tConstTime) CONST;
	virtual BOOL CheckTCParameterOnBoardTimerID(INT nOBTID) CONST;
	virtual BOOL GetTCParameterOnBoardTimerIDRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumTCParameterTimeCorrelationFlags(CStringArray &szFlags, CLongUIntArray &nFlags) CONST;
	virtual BOOL CheckTCParameterTimeCorrelationFlag(ULONGLONG nFlag) CONST;
	virtual INT GetTCParameterTimeCorrelationFlagLength() CONST;
	virtual ULONGLONG TranslateTCParameterTimeCorrelationFlag(LPCTSTR pszFlag, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCParameterTimeCorrelationFlag(ULONGLONG nAttributes, BOOL bDBMS = TRUE) CONST;

	virtual BOOL CheckTCNumCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCNumCalTableNameLength() CONST;
	virtual BOOL CheckTCNumCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCNumCalTableDescriptionLength() CONST;
	virtual BOOL CheckTCNumCalTableUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTCNumCalTableUnitLength() CONST;
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
	virtual BOOL CheckTCNumCalTablePoints(INT nPoints) CONST;
	virtual BOOL GetTCNumCalTablePointsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCNumCalTablePointValue(LPCTSTR pszValue) CONST;
	virtual BOOL CheckTCNumCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual INT GetTCNumCalTablePointValueLength() CONST;
	virtual double TranslateTCNumCalTablePointValue(UINT nAttributes, LPCTSTR pszValue) CONST;
	virtual CString TranslateTCNumCalTablePointValue(UINT nAttributes, double fValue) CONST;
	virtual BOOL CheckTCNumCalTablePointInterval(double X1, double X2) CONST;

	virtual BOOL CheckTCTxtCalTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCTxtCalTableNameLength() CONST;
	virtual BOOL CheckTCTxtCalTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCTxtCalTableDescriptionLength() CONST;
	virtual INT EnumTCTxtCalTableRawValuesCodings(CStringArray &szCodings, CUIntArray &nCodings) CONST;
	virtual BOOL CheckTCTxtCalTableRawValuesCoding(UINT nCoding) CONST;
	virtual INT GetTCTxtCalTableRawValuesCodingLength() CONST;
	virtual UINT TranslateTCTxtCalTableRawValuesCoding(LPCTSTR pszCoding, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateTCTxtCalTableRawValuesCoding(UINT nAttributes, BOOL bDBMS = TRUE) CONST;
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

	virtual BOOL CheckTCNumOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCNumOolTableNameLength() CONST;
	virtual BOOL CheckTCNumOolTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCNumOolTableDescriptionLength() CONST;
	virtual BOOL CheckTCNumOolTableUnit(LPCTSTR pszUnit) CONST;
	virtual INT GetTCNumOolTableUnitLength() CONST;
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
	virtual BOOL CheckTCNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTCNumOolTableLimitValueLength() CONST;
	virtual double TranslateTCNumOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTCNumOolTableLimitValue(UINT nAttributes, double fLimit) CONST;
	virtual BOOL CheckTCNumOolTableLimitTime(ULONGLONG nAttributes, LPCTSTR pszTime) CONST;
	virtual INT GetTCNumOolTableLimitTimeLength() CONST;
	virtual CTimeTag TranslateTCNumOolTableLimitTime(ULONGLONG nAttributes, LPCTSTR pszTime) CONST;
	virtual CString TranslateTCNumOolTableLimitTime(ULONGLONG nAttributes, CONST CTimeTag &tTime) CONST;

	virtual BOOL CheckTCTxtOolTableName(LPCTSTR pszName) CONST;
	virtual INT GetTCTxtOolTableNameLength() CONST;
	virtual BOOL CheckTCTxtOolTableDescription(LPCTSTR pszDescription) CONST;
	virtual INT GetTCTxtOolTableDescriptionLength() CONST;
	virtual BOOL CheckTCTxtOolTableLimitCount(INT nCount) CONST;
	virtual BOOL GetTCTxtOolTableLimitCountRange(INT &nLow, INT &nHigh) CONST;
	virtual INT TranslateTCTxtOolTableLimitCount(LPCTSTR pszCount) CONST;
	virtual CString TranslateTCTxtOolTableLimitCount(INT nCount) CONST;
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
	virtual BOOL CheckTCTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual INT GetTCTxtOolTableLimitValueLength() CONST;
	virtual double TranslateTCTxtOolTableLimitValue(UINT nAttributes, LPCTSTR pszLimit) CONST;
	virtual CString TranslateTCTxtOolTableLimitValue(UINT nAttributes, double fLimit) CONST;

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
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowInterval(CONST CTimeSpan &tWindow) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowIntervalRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowUncertainty(CONST CTimeSpan &tInterval) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowUncertaintyRange(UINT &nLow, UINT &nHigh) CONST;
	virtual BOOL CheckTCExeVerGroupParameterTimeWindowClosurePacketID(UINT nID) CONST;
	virtual BOOL GetTCExeVerGroupParameterTimeWindowClosurePacketIDRange(UINT &nLow, UINT &nHigh) CONST;

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
	virtual BOOL CheckTCParameterSetItemValueBitOffset(INT nOffset) CONST;
	virtual BOOL GetTCParameterSetItemValueBitOffsetRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckTCParameterSetItemConstValue(ULONGLONG nAttributes, LPCTSTR pszConstValue) CONST;
	virtual INT GetTCParameterSetItemConstValueLength() CONST;
	virtual ULONGLONG TranslateTCParameterSetItemConstValue(ULONGLONG nAttributes, INT nWidth, LPCTSTR pszConstValue) CONST;
	virtual CString TranslateTCParameterSetItemConstValue(ULONGLONG nAttributes, INT nWidth, ULONGLONG nConstValue) CONST;
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
	virtual BOOL CheckANDParameterTag(LPCTSTR pszTag) CONST;
	virtual INT GetANDParameterTagLength() CONST;
	virtual BOOL CheckANDParameterComment(LPCTSTR pszComment) CONST;
	virtual INT GetANDParameterCommentLength() CONST;
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

	virtual BOOL CheckGRDName(LPCTSTR pszName) CONST;
	virtual INT GetGRDNameLength() CONST;
	virtual BOOL CheckGRDTitle(LPCTSTR pszTitle) CONST;
	virtual INT GetGRDTitleLength() CONST;
	virtual INT EnumGRDTypes(CStringArray &szTypes, CUIntArray &nTypes) CONST;
	virtual BOOL CheckGRDType(LPCTSTR pszType) CONST;
	virtual INT GetGRDTypeLength() CONST;
	virtual INT TranslateGRDType(LPCTSTR pszType, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDType(INT nType, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumGRDPlotModes(CStringArray &szModes, CUIntArray &nModes) CONST;
	virtual BOOL CheckGRDPlotMode(LPCTSTR pszType, LPCTSTR pszMode) CONST;
	virtual INT GetGRDPlotModeLength() CONST;
	virtual INT TranslateGRDPlotMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDPlotMode(INT nMode, BOOL bDBMS = TRUE) CONST;
	virtual BOOL CheckGRDDurationDays(INT nDays, INT nHours, INT nMinutes) CONST;
	virtual BOOL GetGRDDurationDaysRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDDurationHours(INT nDays, INT nHours, INT nMinutes) CONST;
	virtual BOOL GetGRDDurationHoursRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDDurationMinutes(INT nDays, INT nHours, INT nMinutes) CONST;
	virtual BOOL GetGRDDurationMinutesRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDXGrids(LPCTSTR pszType, INT nXGrids) CONST;
	virtual BOOL GetGRDXGridsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDYGrids(LPCTSTR pszType, INT nYGrids) CONST;
	virtual BOOL GetGRDYGridsRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDXTicks(INT nXTicks) CONST;
	virtual BOOL GetGRDXTicksRange(INT &nLow, INT &nHigh) CONST;
	virtual BOOL CheckGRDYTicks(INT nYTicks) CONST;
	virtual BOOL GetGRDYTicksRange(INT &nLow, INT &nHigh) CONST;
	virtual INT EnumGRDAxisColors(CStringArray &szColors, CUIntArray &nColors) CONST;
	virtual BOOL CheckGRDAxisColor(INT nColor) CONST;
	virtual INT GetGRDAxisColorLength() CONST;
	virtual COLORREF TranslateGRDAxisColor(LPCTSTR pszColor, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDAxisColor(COLORREF nColor, BOOL bDBMS = TRUE) CONST;
	virtual INT EnumGRDHardcopyModes(CStringArray &szModes, CByteArray &nModes) CONST;
	virtual BOOL CheckGRDHardcopyMode(LPCTSTR pszMode) CONST;
	virtual INT GetGRDHardcopyModeLength() CONST;
	virtual INT TranslateGRDHardcopyMode(LPCTSTR pszMode, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDHardcopyMode(INT nMode, BOOL bDBMS = TRUE) CONST;
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
	virtual INT EnumGRDParameterColors(CStringArray &szColors, CUIntArray &nColors) CONST;
	virtual BOOL CheckGRDParameterColor(INT nColor) CONST;
	virtual INT GetGRDParameterColorLength() CONST;
	virtual INT TranslateGRDParameterColor(LPCTSTR pszColor, BOOL bDBMS = TRUE) CONST;
	virtual CString TranslateGRDParameterColor(INT nColor, BOOL bDBMS = TRUE) CONST;
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
	virtual BOOL CheckGRDParameterMinimum(LPCTSTR pszMinimum) CONST;
	virtual INT GetGRDParameterMinimumLength() CONST;
	virtual BOOL CheckGRDParameterMaximum(LPCTSTR pszMaximum) CONST;
	virtual INT GetGRDParameterMaximumLength() CONST;
	virtual BOOL CheckGRDParameterRange(double fMinimum, double fMaximum) CONST;

	virtual BOOL CheckPODName(LPCTSTR pszName) CONST;
	virtual INT GetPODNameLength() CONST;
	virtual BOOL CheckPODTitle(LPCTSTR pszTitle) CONST;
	virtual INT GetPODTitleLength() CONST;
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
	virtual BOOL CheckPODExpressionStack(LPCTSTR pszStack) CONST;
	virtual BOOL CheckPODExpressionStackElementComment(LPCTSTR pszComment) CONST;
	virtual INT GetPODExpressionStackElementCommentLength() CONST;
	virtual INT GetPODParameterTagLength() CONST;
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
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCParameterSet *pDatabaseTCParameterSet, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacketHeaders *pDatabaseTMPacketHeaders, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacketStreams *pDatabaseTMPacketStreams, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTCFunctionRoutingPaths *pDatabaseTCFunctionRoutingPaths, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacketIdentifications *pDatabaseTMPacketIdentifications, UINT nControlID = -1) CONST;
	virtual BOOL TransferTableData(CONST CDatabaseTableView *pView, CDatabaseTMPacketIdentificationCriteria *pDatabaseTMPacketIdentificationCriteria, UINT nControlID = -1) CONST;
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
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeaders *pDatabaseTMPacketHeaders, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketHeaders *pDatabaseTMPacketHeaders, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStreams *pDatabaseTMPacketStreams, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketStreams *pDatabaseTMPacketStreams, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionRoutingPaths *pDatabaseTCFunctionRoutingPaths, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunctionRoutingPaths *pDatabaseTCFunctionRoutingPaths, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentifications *pDatabaseTMPacketIdentifications, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentifications *pDatabaseTMPacketIdentifications, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentificationCriteria *pDatabaseTMPacketIdentificationCriteria, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentificationCriteria *pDatabaseTMPacketIdentificationCriteria, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, CStringArray &szIssues) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableData(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, CStringArray &szIssues) CONST;

private:
	VOID UpdateTable(CDatabaseTableView *pView, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE);
	VOID UpdateTable(CDatabaseTableView *pView, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE);
	BOOL UpdateTable(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable) CONST;
	BOOL UpdateTable(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CDatabaseTCNumOolTable *pDatabaseTCNumOolTable) CONST;

public:
	virtual INT EnumDBMSTables(CStringArray &szTables, CStringArray &szDescriptions) CONST;
	virtual BOOL GetDBMSTableCharacteristics(LPCTSTR pszTable, CStringArray &szColumns, CStringArray &szDataTypes, CStringArray &szDefaults, CByteArray &bAllowNulls) CONST;

	virtual BOOL UsesDBMSTables(ULONGLONG nComponent) CONST;

private:
	INT ConstructTMPacketTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacket *pDatabaseTMPacket, CStringArray &szContents) CONST;
	INT ConstructTMPacketTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketIdentificationsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketIdentificationsTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketIdentificationsTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketIdentificationCriteriaTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketIdentificationCriteriaTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketIdentificationCriteriaTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketHeadersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketHeadersTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketHeadersTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes, BOOL bFixed = TRUE) CONST;
	INT ConstructTMPacketStreamsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketStreamsTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketStreamsTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketGroupTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketGroupTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, CStringArray &szContents) CONST;
	INT ConstructTMPacketGroupTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMPacketGroupMembersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMPacketGroupMembersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMPacketGroupMembersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
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
	INT ConstructTCPacketHeaderParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCPacketHeaderParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, CStringArray &szContents) CONST;
	INT ConstructTCPacketHeaderParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCPreExeGroupParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCPreExeGroupParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCPreExeGroupParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCExeVerGroupStagesTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupStagesTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupStagesTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCExeVerGroupStageParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupStageParametersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupStageParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCExeVerGroupStagesAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupStagesAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCExeVerGroupStagesAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszID, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterSetsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterValueSetsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterValueSetsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, CStringArray &szContents) CONST;
	INT ConstructTCParameterValueSetsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterValueSetMembersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterValueSetMembersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCParameterValueSetMembersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterSetsAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCParameterSetsAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, BOOL bSequence, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCParameterValueSetsAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCParameterValueSetsAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCParameterValueSetsAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCFunctionRoutingTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCFunctionRoutingTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCFunctionRoutingTableContents(CONST CDatabaseTableView *pView, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
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
	INT ConstructOBProcessorMemoryImagesAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;	INT ConstructTMParameterTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMParameterTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, CStringArray &szContents) CONST;
	INT ConstructTMParameterTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMParameterDerivationCodeTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMParameterDerivationCodeTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, CStringArray &szContents) CONST;
	INT ConstructTMParameterDerivationCodeTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMParameterGroupTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMParameterGroupTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, CStringArray &szContents) CONST;
	INT ConstructTMParameterGroupTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMParameterGroupMembersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMParameterGroupMembersTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMParameterGroupMembersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalCurveTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurvePointsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumCalCurveAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalPolynomialCurveTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalPolynomialCurveTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CStringArray &szContents) CONST;
	INT ConstructTMNumCalPolynomialCurveTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumCalLogarithmicCurveTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumCalLogarithmicCurveTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, CStringArray &szContents) CONST;
	INT ConstructTMNumCalLogarithmicCurveTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
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
	INT ConstructTMNumOolChecksTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumOolChecksTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMNumOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMNumOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMNumOolChecksAssociationTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszTag, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTMTxtOolChecksTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolChecksTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTMTxtOolChecksTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
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
	INT ConstructTCNumOolLimitsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCNumOolLimitsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, CStringArray &szContents) CONST;
	INT ConstructTCNumOolLimitsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCNumOolLimitValuesTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCNumOolLimitValuesTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCNumOolLimitValuesTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCTxtOolLimitsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolLimitsTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolLimitsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructTCTxtOolLimitValuesTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolLimitValuesTableContents(CONST CDatabaseTableView *pView, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, INT nCount, CStringArray &szContents) CONST;
	INT ConstructTCTxtOolLimitValuesTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructANDTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructANDTableContents(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, CStringArray &szContents) CONST;
	INT ConstructANDTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructANDParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructANDParametersTableContents(CONST CDatabaseTableView *pView, CONST CANDLayout *pANDLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructANDParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructGRDTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructGRDTableContents(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, CStringArray &szContents) CONST;
	INT ConstructGRDTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructGRDParametersTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructGRDParametersTableContents(CONST CDatabaseTableView *pView, CONST CGRDLayout *pGRDLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructGRDParametersTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructPODTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructPODTableContents(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, CStringArray &szContents) CONST;
	INT ConstructPODTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;
	INT ConstructPODExpressionsTableContents(CONST CDatabaseTableView *pView, CStringArray &szContents) CONST;
	INT ConstructPODExpressionsTableContents(CONST CDatabaseTableView *pView, CONST CPODLayout *pPODLayout, INT nCount, CStringArray &szContents) CONST;
	INT ConstructPODExpressionsTableContents(CONST CDatabaseTableView *pView, LPCTSTR pszName, INT nCount, CStringArray &szContents, CUIntArray &nFormats, CUIntArray &nIDs, CStringArray &szDescriptions, CStringArray &szDataTypes) CONST;

	VOID EmptyTableRow(CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification) CONST;
	VOID EmptyTableRow(CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion) CONST;
	VOID EmptyTableRow(CDatabaseTMPacketHeader *pDatabaseTMPacketHeader) CONST;
	VOID EmptyTableRow(CDatabaseTMPacketStream *pDatabaseTMPacketStream) CONST;
	VOID EmptyTableRow(CDatabaseTMPacketParameter *pDatabaseTMPacketParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCPacketParameter *pDatabaseTCPacketParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCFunctionElement *pDatabaseTCFunctionElement) CONST;
	VOID EmptyTableRow(CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCExeVerStageParameter *pDatabaseTCExeVerStageParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter) CONST;
	VOID EmptyTableRow(CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath) CONST;
	VOID EmptyTableRow(CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;
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
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCExeVerStageParameter *pDatabaseTCExeVerStageParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath) CONST;
	BOOL IsTableRowEmpty(CONST CDatabaseTCSequenceEntry *pDatabaseTCSequenceEntry) CONST;
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
	VOID ShowCompileMessages(CSCOS2000DatabaseRecordset *pRecordset);
	BOOL ShowCompileMessage(LPCTSTR pszMessage, BOOL bTimestamp = TRUE, BOOL bAudition = FALSE);
	BOOL ShowCompileMessage(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszMessage, BOOL bWarning, BOOL bTimestamp = TRUE, BOOL bAudition = FALSE);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000MemoryDumpsServiceEngine

class AFX_EXT_CLASS CSCOS2000MemoryDumpsServiceEngine : public CMemoryDumpsServiceEngine
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
// CSCOS2000TPEPServiceEngine

class AFX_EXT_CLASS CSCOS2000TPEPServiceEngine : public CTPEPServiceEngine
{
	// Construction
public:
	CSCOS2000TPEPServiceEngine();
	~CSCOS2000TPEPServiceEngine();

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
// CSCOS2000PFLPServiceEngine

class AFX_EXT_CLASS CSCOS2000PFLPServiceEngine : public CPFLPServiceEngine
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
// CSCOS2000TMProcessInfo

class AFX_EXT_CLASS CSCOS2000TMProcessInfo : public CTMProcessInfo
{
	// Construction
public:
	CSCOS2000TMProcessInfo();

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
// CSCOS2000TMProcessEngine

class AFX_EXT_CLASS CSCOS2000TMProcessEngine : public CTMProcessEngine
{
	// Construction
public:
	CSCOS2000TMProcessEngine();

	// Attributes
protected:
	UINT  m_nSpacecraftID;
	UINT  m_nTMServiceLevel;
	UINT  m_nMCFrameCounter;
	UINT  m_nVCFrameCounter[8];
	UINT  m_nVCDataCount[8];
	UINT  m_nVCDataLength[8];
	DWORD  m_dwCommandLinkControlWord;
	CByteArray  m_nVCData[8];
	CUIntArray  m_nAPIDs[2];
	CTimeKey  m_tMCFrameCount;
	BOOL  m_bFECWChecksum;
	BOOL  m_bFECW;
private:
	WORD  m_wTCPacketCRC16Table[256];

	// Operations
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

	virtual BOOL CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CTMParameter *pTMParameter, INT nCalTableRef, INT nOolTableRef, ULONGLONG nValue, ULONGLONG nOldValue, INT nOldCalTableRef, BOOL bOldValue, UINT &nOolLimit, UINT &nOolStatus) CONST;
	virtual BOOL ConvertTMParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTMParameter *pTMParameter, INT nCalTableRef, LPCTSTR pszValue, ULONGLONG &nValue) CONST;

public:
	virtual BOOL AllocateTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST;
	virtual BOOL FreeTMProcessInfo(CTMEnvironment *pTMEnvironment) CONST;

private:
	BOOL CheckTMTransferFrame(CONST CTMTransferUnit *pTMTransferUnit, CTMTransferFrame *pTMTransferFrame);
	BOOL CheckTMPacket(CONST CTMTransferFrame *pTMTransferFrame, CTMPacket *pTMPacket) CONST;
	BOOL CheckTMPacket(CONST CTMPacket *pTMPacket) CONST;
	INT DecodeTMPacket(CONST CDatabaseEngine *pDatabase, CONST CTMPacket *pTMPacket) CONST;
	BOOL InitializeTMPacket(CTMEnvironment *pTMEnvironment, CONST CDatabaseTMPacket *pDatabaseTMPacket, CTMPacket *pTMPacket) CONST;
	VOID ProcessTMPacket(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, CONST CTMPacket *pTMPacket, INT nOffset) CONST;
	BOOL UpdateTMPacketCache(CTMEnvironment *pTMEnvironment) CONST;

	VOID ProcessTMParameter(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CONST CDatabaseTMPacketParameter *pDatabaseTMPacketParameter, ULONGLONG nValue) CONST;
	BOOL ProcessTMParameter(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CTMParameter *pTMParameter) CONST;
	UINT CheckTMParameterOolStatus(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CTMParameter *pTMParameter, ULONGLONG nValue, ULONGLONG nOldValue, BOOL bOldValue, LPCTSTR pszCalTable, LPCTSTR pszOldCalTable, WORD &wOolTable, WORD &wOolLimit) CONST;
	UINT CheckTMParameterValidityValue(CONST CTMEnvironment *pTMEnvironment, CONST CDatabaseTMParameter *pDatabaseTMParameter, CONST CTMParameter *pTMParameter = NULL) CONST;
	UINT CheckTMParameterValidityValue(CONST CTMParameter *pTMParameter, ULONGLONG nValue) CONST;

	UINT CalculateTMTransferFrameSegmentLength(CONST CTMTransferFrame *pTMTransferFrame) CONST;

	BOOL CalculateCRC(CONST CTMPacket *pTMPacket) CONST;
	BOOL CalculateCRC(CONST CByteArray &nData, CONST CByteArray &nCRC, WORD wSeed = 0xFFFF, BOOL bXOR = FALSE) CONST;
	BOOL CalculateChecksum(CONST CByteArray &nData, CONST CByteArray &nChecksum) CONST;

	BOOL CalculateTMBandwidth(CONST CTMEnvironment *pTMEnvironment);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000TCProcessInfo

class AFX_EXT_CLASS CSCOS2000TCProcessInfo : public CTCProcessInfo
{
	// Construction
public:
	CSCOS2000TCProcessInfo();
	~CSCOS2000TCProcessInfo();

	// Attributes
private:
	BOOL  m_bOBRT;
	UINT  m_nOBRT;
	TIMETAG  m_tOBRT[2];
private:
	BYTE  m_nFSN;
	CUIntArray  m_nAPIDPSCs[2];
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbAPIDs[2];
		BYTE  nFSN;
		BOOL  bOBRT;
		UINT  nOBRT;
		TIMETAG  tOBRT;
	} DATA, *PDATA, *LPDATA;

	// Operations
public:
	VOID SetTimeCorrelation(CONST CTimeTag &tOBRT = 0, UINT nOBRT = 0);
	CTimeTag GetTimeCorrelation(CTimeTag &tOBRT, UINT &nOBRT) CONST;

	VOID SetTCTransferFrameSequenceNumber(BYTE nFSN);
	BYTE GetTCTransferFrameSequenceNumber() CONST;
	INT GenerateTCPacketSequenceCount(INT nAPID, BOOL bExample = FALSE);

	virtual BOOL SetData(CONST CByteArray &nData);
	virtual INT GetData(CByteArray &nData) CONST;

	virtual VOID Reset();

private:
	INT DetermineAPIDToPSCIndex(INT nAPID);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000TCProcessEngine

// Specify telecommand packet sequence related identifiers
#define PSC_NUM_COUNTER_BITS   (14-PSC_NUM_SOURCE_BITS)
#define PSC_NUM_SOURCE_BITS   0

class AFX_EXT_CLASS CSCOS2000TCProcessEngine : public CTCProcessEngine
{
	// Construction
public:
	CSCOS2000TCProcessEngine();

	// Attributes
protected:
	UINT  m_nSpacecraftID;
	UINT  m_nTCServiceLevel;
	UINT  m_nTCTransferFrameVirtualChannel;
	BYTE  m_nTCTransferFrameSequenceNumber;
	BOOL  m_bTCTransferFrameSequenceNumber;
	BOOL  m_bTCTransferFrameExpeditedMode;
	UINT  m_nNISThrowEventCounter;
	UINT  m_nSLEThrowEventCounter;
	BOOL  m_bDebugging;
private:
	CTimeSpan  m_tTCFunctionExecutionTimeOffset[2];
	CTimeSpan  m_tTCFunctionParameterTimeOffset[2];
private:
	WORD  m_wTCPacketCRC16Table[256];

	// Operations
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

private:
	BOOL CheckTCFunctionExecutionVerificationPackets(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter, CONST CTimeTag &tStageStart) CONST;
	VOID CheckTCFunctionPreexecutionParameterValues(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCPreExeGroupParameter *pDatabaseTCPreExeGroupParameter, CONST CTMParameter *pTMParameter, CStringArray &szParameters) CONST;
	BOOL CheckTCFunctionExecutionParameterValues(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter, CTMParameter *pTMParameter, CStringArray &szParameters, BOOL bInInterval) CONST;
	BOOL CheckTCFunctionExecutionParameterValues(CONST CDatabaseEngine *pDatabase, CONST CDatabaseTCExeVerGroupParameter *pDatabaseTCExeVerGroupParameter, CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, CTMParameter *pTMParameter, CStringArray &szParameters, BOOL bInInterval) CONST;

	BOOL ConvertTCParameterValues(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CONST CDatabaseTCFunctions &pDatabaseTCFunctions, CONST CDatabaseTCPackets &pDatabaseTCPackets) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, ULONGLONG nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CONST CTCEnvironment *pTCEnvironment, CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, ULONGLONG nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, ULONGLONG nValue) CONST;
	BOOL ConvertTCParameterValue(CONST CDatabaseEngine *pDatabase, CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, ULONGLONG nValue) CONST;

	BOOL IsTCParameterNumerical(CONST CDatabaseEngine *pDatabase, LPCTSTR pszTag) CONST;
	BOOL IsTCParameterTextual(CONST CDatabaseEngine *pDatabase, LPCTSTR pszTag) CONST;

	BYTE GenerateTCTransferFrameSequenceNumber(CONST BYTE *pTCProcessData);
	BOOL TransactTCTransferFrameSequenceNumber(BYTE *pTCProcessData, BYTE nNumber);

	BOOL CalculateErrorControlWord(CTCPacket *pTCPacket) CONST;
	WORD CalculateCRC(CONST CByteArray &nData, BOOL bXOR = FALSE) CONST;
	WORD CalculateCRC(CONST CByteArray &nData, WORD wSeed, BOOL bXOR = FALSE) CONST;
	WORD CalculateChecksum(CONST CByteArray &nData) CONST;

	BOOL IsFixedSize(CONST CDatabaseTCPacket *pDatabaseTCPacket) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCOS2000LibraryApp application

class AFX_EXT_CLASS CSCOS2000LibraryApp : public CLibraryApp
{
	// Construction
public:

	// Attributes
public:
	CSCOS2000DatabaseEngine  m_cDatabaseEngine;
	CSCOS2000TMProcessEngine  m_cTMProcessEngine;
	CSCOS2000TCProcessEngine  m_cTCProcessEngine;
	CSCOS2000MemoryDumpsServiceEngine  m_cMemoryDumpsServiceEngine;
	CSCOS2000TPEPServiceEngine  m_cTPEPServiceEngine;
	CSCOS2000PFLPServiceEngine  m_cPFLPServiceEngine;

	// Operations
public:
	CDatabaseEngine *GetDatabaseEngine() CONST;
	CTMProcessEngine *GetTMProcessEngine() CONST;
	CTCProcessEngine *GetTCProcessEngine() CONST;
	CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine() CONST;
	CTPEPServiceEngine *GetTPEPServiceEngine() CONST;
	CPFLPServiceEngine *GetPFLPServiceEngine() CONST;

	static CSCOS2000LibraryApp *GetLibraryApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCOS2000LibraryApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSCOS2000LibraryApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
#ifdef SCOS2000ENVIRONMENT
inline CDatabaseEngine *GetDatabaseEngine()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetDatabaseEngine());
}
inline CTMProcessEngine *GetTMProcessEngine()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetTMProcessEngine());
}
inline CTCProcessEngine *GetTCProcessEngine()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetTCProcessEngine());
}
inline CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetMemoryDumpsServiceEngine());
}
inline CTPEPServiceEngine *GetTPEPServiceEngine()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetTPEPServiceEngine());
}
inline CPFLPServiceEngine *GetPFLPServiceEngine()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetPFLPServiceEngine());
}
inline LPCTSTR STRING(INT nID)
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->StringChar(nID));
}
inline LPCTSTR GetLibraryName()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetLibraryName());
}
inline HINSTANCE GetLibraryInstance()
{
	return(CSCOS2000LibraryApp::GetLibraryApp()->GetLibraryInstance());
}
#endif

// Specify the associated export definitions
extern "C"
{
	__declspec(dllexport) CDatabaseEngine *GetStandardDatabaseEngineProc();
}

/////////////////////////////////////////////////////////////////////////////


#endif // __SCOS2000_H__
