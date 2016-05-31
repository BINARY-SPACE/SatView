// PROFILE.H : Profile Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the profile related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __PROFILE_H__
#define __PROFILE_H__


/////////////////////////////////////////////////////////////////////////////
// CProfile

class CProfile : public CRegistry
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL SetState(UINT nShow = -1);
	BOOL GetState(UINT &nShow) CONST;
	BOOL SetPosition(LPCRECT pPosition = NULL);
	BOOL GetPosition(LPRECT pPosition) CONST;
	BOOL SetStatusBarState(CONST CUIntArray &nPaneIDs);
	BOOL GetStatusBarState(CUIntArray &nPaneIDs) CONST;
	BOOL SetDisplayAreaType(UINT nType = -1);
	BOOL GetDisplayAreaType(UINT &nType) CONST;
	BOOL SetDisplayAreaPageCount(INT nPages = -1);
	BOOL GetDisplayAreaPageCount(INT &nPages) CONST;
	BOOL SetDisplayAreaActivePage(INT nPage = -1);
	BOOL GetDisplayAreaActivePage(INT &nPage) CONST;
	BOOL SetDisplayAreaTemporaryANDs(CONST CByteArray &nANDs);
	BOOL GetDisplayAreaTemporaryANDs(CByteArray &nANDs) CONST;
	BOOL SetDisplayAreaTemporaryGRDs(CONST CByteArray &nGRDs);
	BOOL GetDisplayAreaTemporaryGRDs(CByteArray &nGRDs) CONST;
	BOOL SetDisplayAreaTemporaryPODs(CONST CByteArray &nPODs);
	BOOL GetDisplayAreaTemporaryPODs(CByteArray &nPODs) CONST;
	BOOL SetDisplayPageTitle(INT nPage, LPCTSTR pszTitle = NULL);
	BOOL GetDisplayPageTitle(INT nPage, CString &szTitle) CONST;
	BOOL SetDisplayPageWindowCount(INT nPage, INT nCount = -1);
	BOOL GetDisplayPageWindowCount(INT nPage, INT &nCount) CONST;
	BOOL SetDisplayPageScrollInfo(INT nPage, CONST SCROLLINFO *pHorzInfo = NULL, CONST SCROLLINFO *pVertInfo = NULL);
	BOOL GetDisplayPageScrollInfo(INT nPage, LPSCROLLINFO pHorzInfo, LPSCROLLINFO pVertInfo) CONST;
	BOOL SetDisplayPagePassword(INT nPage, LPCTSTR pszPassword = NULL);
	BOOL GetDisplayPagePassword(INT nPage, CString &szPassword) CONST;
	BOOL SetDisplayPageUsers(INT nPage, CONST CStringArray &szUsers);
	BOOL GetDisplayPageUsers(INT nPage, CStringArray &szUsers) CONST;
	BOOL SetDisplayPageFlags(INT nPage, UINT nFlags = -1);
	BOOL GetDisplayPageFlags(INT nPage, UINT &nFlags) CONST;
	BOOL SetDisplayWindowTitle(INT nPage, INT nDisplay, LPCTSTR pszTitle = NULL);
	BOOL GetDisplayWindowTitle(INT nPage, INT nDisplay, CString &szTitle) CONST;
	BOOL SetDisplayWindowType(INT nPage, INT nDisplay, INT nType = -1);
	BOOL GetDisplayWindowType(INT nPage, INT nDisplay, INT &nType) CONST;
	BOOL SetDisplayWindowScope(INT nPage, INT nDisplay, INT nScope = -1);
	BOOL GetDisplayWindowScope(INT nPage, INT nDisplay, INT &nScope) CONST;
	BOOL SetDisplayWindowMode(INT nPage, INT nDisplay, UINT nMode = -1);
	BOOL GetDisplayWindowMode(INT nPage, INT nDisplay, UINT &nMode) CONST;
	BOOL SetDisplayWindowData(INT nPage, INT nDisplay, LPVOID pData = NULL);
	BOOL GetDisplayWindowData(INT nPage, INT nDisplay, LPVOID *pData) CONST;
	BOOL SetDisplayWindowLink(INT nPage, INT nDisplay, LPCTSTR pszLink = NULL);
	BOOL GetDisplayWindowLink(INT nPage, INT nDisplay, CString &szLink) CONST;
	BOOL SetDisplayWindowPlacement(INT nPage, INT nDisplay, LPCRECT pPosition = NULL, CONST POINT *pPoint = NULL, INT nNumber = -1, UINT nShow = -1, BOOL bVisible = FALSE);
	BOOL GetDisplayWindowPlacement(INT nPage, INT nDisplay, LPRECT pPosition, LPPOINT pPoint, INT &nNumber, UINT &nShow, BOOL &bVisible) CONST;
	BOOL SetDisplayWindowLockInformation(INT nPage, INT nDisplay, LPCTSTR pszOwner = NULL, LPCTSTR pszContact = NULL, LPCTSTR pszPassword = NULL, LPCTSTR pszReason = NULL);
	BOOL GetDisplayWindowLockInformation(INT nPage, INT nDisplay, CString &szOwner, CString &szContact, CString &szPassword, CString &szReason) CONST;
	BOOL SetLoginOptions(CONST CByteArray &nOptionsInfo);
	BOOL GetLoginOptions(CByteArray &nOptionsInfo) CONST;
	BOOL SetPrintProfilesInfo(CONST CByteArray &nProfilesInfo);
	BOOL GetPrintProfilesInfo(CByteArray &nProfilesInfo) CONST;
	BOOL SetAuditionProfilesInfo(CONST CByteArray &nProfilesInfo);
	BOOL GetAuditionProfilesInfo(CByteArray &nProfilesInfo) CONST;
	BOOL SetNotificationProfilesInfo(CONST CByteArray &nProfilesInfo);
	BOOL GetNotificationProfilesInfo(CByteArray &nProfilesInfo) CONST;
	BOOL SetNotificationJobsInfo(CONST CByteArray &nJobsInfo);
	BOOL GetNotificationJobsInfo(CByteArray &nJobsInfo) CONST;
	BOOL SetSystemAlertsInfo(CONST CByteArray &nAlertsInfo);
	BOOL GetSystemAlertsInfo(CByteArray &nAlertsInfo) CONST;
	BOOL SetTelemetryServiceInfo(CONST CByteArray &nServiceInfo);
	BOOL GetTelemetryServiceInfo(CByteArray &nServiceInfo) CONST;
	BOOL SetTelemetryServiceConfigurationInfo(CONST CByteArray &nConfigurationInfo);
	BOOL GetTelemetryServiceConfigurationInfo(CByteArray &nConfigurationInfo) CONST;
	BOOL SetTelemetryEventsInfo(CONST CByteArray &nEventsInfo);
	BOOL GetTelemetryEventsInfo(CByteArray &nEventsInfo) CONST;
	BOOL SetTelemetryReportsInfo(CONST CByteArray &nReportsInfo);
	BOOL GetTelemetryReportsInfo(CByteArray &nReportsInfo) CONST;
	BOOL SetTelemetryHistoricalReportsInfo(CONST CByteArray &nHistoricalReportsInfo);
	BOOL GetTelemetryHistoricalReportsInfo(CByteArray &nHistoricalReportsInfo) CONST;
	BOOL SetTelemetryReportJobsInfo(CONST CByteArray &nReportJobsInfo, CONST CByteArray &nHistoricalReportJobsInfo);
	BOOL GetTelemetryReportJobsInfo(CByteArray &nReportJobsInfo, CByteArray &nHistoricalReportJobsInfo) CONST;
	BOOL SetTelemetryArchivesSettingsInfo(CONST CByteArray &nArchivesInfo);
	BOOL GetTelemetryArchivesSettingsInfo(CByteArray &nArchivesInfo) CONST;
	BOOL SetTelemetryArchivesBackupInfo(CONST CByteArray &nArchivesInfo);
	BOOL GetTelemetryArchivesBackupInfo(CByteArray &nArchivesInfo) CONST;
	BOOL SetTelemetryArchivesExtractionInfo(CONST CByteArray &nArchivesInfo);
	BOOL GetTelemetryArchivesExtractionInfo(CByteArray &nArchivesInfo) CONST;
	BOOL SetTelemetryArchivesExtractionJobsInfo(CONST CByteArray &nJobsInfo);
	BOOL GetTelemetryArchivesExtractionJobsInfo(CByteArray &nJobsInfo) CONST;
	BOOL SetTelemetryHistoryFileExtractionInfo(CONST CByteArray &nFileInfo);
	BOOL GetTelemetryHistoryFileExtractionInfo(CByteArray &nFileInfo) CONST;
	BOOL SetTelemetryParameterSetsInfo(CONST CByteArray &nSetsInfo);
	BOOL GetTelemetryParameterSetsInfo(CByteArray &nSetsInfo) CONST;
	BOOL SetTelecommandServiceInfo(CONST CByteArray &nServiceInfo);
	BOOL GetTelecommandServiceInfo(CByteArray &nServiceInfo) CONST;
	BOOL SetTelecommandServiceConfigurationInfo(CONST CByteArray &nConfigurationInfo);
	BOOL GetTelecommandServiceConfigurationInfo(CByteArray &nConfigurationInfo) CONST;
	BOOL SetTelecommandServiceContentsInfo(CONST CByteArray &nContentsInfo);
	BOOL GetTelecommandServiceContentsInfo(CByteArray &nContentsInfo) CONST;
	BOOL SetTelecommandServiceLoggingInfo(UINT nArchivalPolicy = 0, LPCTSTR pszArchivalFileName = NULL, DWORDLONG dwArchivalRetention = 0, CONST CTimeSpan &tArchivalRetention = 0, LPCTSTR pszRetrievalFileName = NULL, UINT nRetrievalReloadCount = 0, BOOL bShowAsEvent = FALSE);
	BOOL GetTelecommandServiceLoggingInfo(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL SetTelecommandServiceProcessInfo(CONST CByteArray &nProcessInfo);
	BOOL GetTelecommandServiceProcessInfo(CByteArray &nProcessInfo) CONST;
	BOOL SetTelecommandDiagnosticsOversamplingDumpsInfo(CONST CByteArray &nDumpsInfo);
	BOOL GetTelecommandDiagnosticsOversamplingDumpsInfo(CByteArray &nDumpsInfo) CONST;
	BOOL SetTelecommandArchivesSettingsInfo(CONST CByteArray &nArchivesInfo);
	BOOL GetTelecommandArchivesSettingsInfo(CByteArray &nArchivesInfo) CONST;
	BOOL SetTelecommandArchivesBackupInfo(CONST CByteArray &nArchivesInfo);
	BOOL GetTelecommandArchivesBackupInfo(CByteArray &nArchivesInfo) CONST;
	BOOL SetTelecommandParameterSetsInfo(CONST CByteArray &nSetsInfo);
	BOOL GetTelecommandParameterSetsInfo(CByteArray &nSetsInfo) CONST;
	BOOL SetMemoryDumpsServiceSettingsInfo(UINT nCharset = -1);
	BOOL GetMemoryDumpsServiceSettingsInfo(UINT &nCharset) CONST;
	BOOL SetMemoryDumpsServiceAvailabilityInfo(UINT nCode = -1, CONST CTimeSpan &tStartTime = 0, CONST CTimeSpan &tStopTime = 0);
	BOOL GetMemoryDumpsServiceAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetMemoryDumpsServiceDumpInfo(CONST CByteArray &nDumpInfo);
	BOOL GetMemoryDumpsServiceDumpInfo(CByteArray &nDumpInfo) CONST;
	BOOL SetMemoryDumpsServiceFTPQueueInfo(CONST CByteArray &nQueueInfo);
	BOOL GetMemoryDumpsServiceFTPQueueInfo(CByteArray &nQueueInfo) CONST;
	BOOL SetANDLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetANDLayoutName(INT nPage, INT nDisplay, CString &szName) CONST;
	BOOL SetANDLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nColors, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips);
	BOOL GetANDLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, CUIntArray &nColors, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST;
	BOOL SetANDFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pDefaultTitleFont = NULL, CONST LOGFONT *pLabelsFont = NULL, CONST LOGFONT *pDefaultLabelsFont = NULL, CONST LOGFONT *pItemsFont = NULL, CONST LOGFONT *pDefaultItemsFont = NULL, CONST LOGFONT *pValuesFont = NULL, CONST LOGFONT *pDefaultValuesFont = NULL);
	BOOL GetANDFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pDefaultTitleFont, LOGFONT *pLabelsFont, LOGFONT *pDefaultLabelsFont, LOGFONT *pItemsFont, LOGFONT *pDefaultItemsFont, LOGFONT *pValuesFont, LOGFONT *pDefaultValuesFont) CONST;
	BOOL SetANDModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeSpan &tInterval = 0, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetANDModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetANDPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetANDPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetANDRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetANDRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetGRDLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetGRDLayoutName(INT nPage, INT nDisplay, CString &szName) CONST;
	BOOL SetGRDLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nColors, CONST CByteArray &nMarkerData, CONST CByteArray &nScalingData, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips);
	BOOL GetGRDLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, CUIntArray &nColors, CByteArray &nMarkerData, CByteArray &nScalingData, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST;
	BOOL SetGRDFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pDefaultTitleFont = NULL, CONST LOGFONT *pItemsFont = NULL, CONST LOGFONT *pDefaultItemsFont = NULL, CONST LOGFONT *pValuesFont = NULL, CONST LOGFONT *pDefaultValuesFont = NULL, CONST LOGFONT *pAxesFont = NULL, CONST LOGFONT *pDefaultAxesFont = NULL);
	BOOL GetGRDFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pDefaultTitleFont, LOGFONT *pItemsFont, LOGFONT *pDefaultItemsFont, LOGFONT *pValuesFont, LOGFONT *pDefaultValuesFont, LOGFONT *pAxesFont, LOGFONT *pDefaultAxesFont) CONST;
	BOOL SetGRDModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeSpan &tInterval = 0, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetGRDModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetGRDPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetGRDPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetGRDRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetGRDRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetHEXLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetHEXLayoutName(INT nPage, INT nDisplay, CString &szName) CONST;
	BOOL SetHEXLayoutInfo(INT nPage, INT nDisplay, CONST SIZE &sizeData, CONST SIZE &sizeSpy, UINT nHorzEnum, UINT nVertEnum, UINT nLineLength, CONST CUIntArray &nColors, BOOL bBadData);
	BOOL GetHEXLayoutInfo(INT nPage, INT nDisplay, CSize &sizeData, CSize &sizeSpy, UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors, BOOL &bBadData) CONST;
	BOOL SetHEXLayoutContents(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo);
	BOOL GetHEXLayoutContents(INT nPage, INT nDisplay, CByteArray &nContentsInfo) CONST;
	BOOL SetHEXFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pDataFont = NULL, CONST LOGFONT *pSpyHeaderFont = NULL, CONST LOGFONT *pSpyLocationsFont = NULL);
	BOOL GetHEXFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pDataFont, LOGFONT *pSpyHeaderFont, LOGFONT *pSpyLocationsFont) CONST;
	BOOL SetHEXModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeSpan &tInterval = 0, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetHEXModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetHEXPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetHEXPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetHEXRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetHEXRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetOOLLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetOOLLayoutName(INT nPage, INT nDisplay, CString &szName) CONST;
	BOOL SetOOLLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bBadData, BOOL bToolTips);
	BOOL GetOOLLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, BOOL &bBadData, BOOL &bToolTips) CONST;
	BOOL SetOOLFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pItemsFont = NULL);
	BOOL GetOOLFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;
	BOOL SetOOLFilterInfo(INT nPage, INT nDisplay, CONST CByteArray &nFilterInfo);
	BOOL GetOOLFilterInfo(INT nPage, INT nDisplay, CByteArray &nFilterInfo) CONST;
	BOOL SetOOLModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeSpan &tInterval = 0, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetOOLModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetOOLPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetOOLPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetOOLRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetOOLRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetMMDLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetMMDLayoutName(INT nPage, INT nDisplay, CString &szName) CONST;
	BOOL SetMMDLayoutInfo(INT nPage, INT nDisplay, CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips);
	BOOL GetMMDLayoutInfo(INT nPage, INT nDisplay, CSize &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, CSize &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST;
	BOOL SetMMDModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeSpan &tInterval = 0, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetMMDModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetMMDPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetMMDPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetMMDRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetMMDRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetPODLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetPODLayoutName(INT nPage, INT nDisplay, CString &szName) CONST;
	BOOL SetPODLayoutInfo(INT nPage, INT nDisplay, CONST SIZE &sizeData, CONST CUIntArray &nDataWidths, CONST SIZE &sizeParameters, CONST CUIntArray &nParametersWidths, CONST SIZE &sizeFunctions, CONST CUIntArray &nFunctionsWidths, BOOL bToolTips);
	BOOL GetPODLayoutInfo(INT nPage, INT nDisplay, CSize &sizeData, CUIntArray &nDataWidths, CSize &sizeParameters, CUIntArray &nParametersWidths, CSize &sizeFunctions, CUIntArray &nFunctionsWidths, BOOL &bToolTips) CONST;
	BOOL SetPODFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pDataTitleFont = NULL, CONST LOGFONT *pDataItemsFont = NULL, CONST LOGFONT *pParametersTitleFont = NULL, CONST LOGFONT *pParametersItemsFont = NULL, CONST LOGFONT *pFunctionsTitleFont = NULL, CONST LOGFONT *pFunctionsItemsFont = NULL);
	BOOL GetPODFontsInfo(INT nPage, INT nDisplay, LOGFONT *pDataTitleFont, LOGFONT *pDataItemsFont, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pFunctionsTitleFont, LOGFONT *pFunctionsItemsFont) CONST;
	BOOL SetPODModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeSpan &tInterval = 0, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetPODModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetPODFilterInfo(INT nPage, INT nDisplay, UINT nMode, UINT nLimit, UINT nDigits, UINT nStatus, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tDailyStartTime, CONST CTimeSpan &tDailyStopTime, CONST CTimeKey &tPeriodicalStartTime, CONST CTimeSpan &tPeriodicalInterval, CONST CTimeKey &tPeriodicalStopTime, CONST CUIntArray &nColors);
	BOOL GetPODFilterInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, UINT &nDigits, UINT &nStatus, CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tDailyStartTime, CTimeSpan &tDailyStopTime, CTimeKey &tPeriodicalStartTime, CTimeSpan &tPeriodicalInterval, CTimeKey &tPeriodicalStopTime, CUIntArray &nColors) CONST;
	BOOL SetPODPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetPODPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetPODRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetPODRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetTPEPConnectionInfo(INT nPage, INT nDisplay, LPCTSTR pszComputer, CONST CByteArray &nConnectionInfo, BOOL bConnection);
	BOOL GetTPEPConnectionInfo(INT nPage, INT nDisplay, CString &szComputer, CByteArray &nConnectionInfo, BOOL &bConnection) CONST;
	BOOL SetTPEPLayoutInfo(INT nPage, INT nDisplay, UINT nType, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bToolTips);
	BOOL GetTPEPLayoutInfo(INT nPage, INT nDisplay, UINT &nType, CUIntArray &nColumns, CUIntArray &nWidths, BOOL &bToolTips) CONST;
	BOOL SetTPEPFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pMessagesFont = NULL);
	BOOL GetTPEPFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pMessagesFont) CONST;
	BOOL SetTPEPFilterInfo(INT nPage, INT nDisplay, UINT nMode, UINT nLimit, UINT nDigits, UINT nStatus, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tDailyStartTime, CONST CTimeSpan &tDailyStopTime, CONST CTimeKey &tPeriodicalStartTime, CONST CTimeSpan &tPeriodicalInterval, CONST CTimeKey &tPeriodicalStopTime, COLORREF nColor, CONST CUIntArray &nOOLColors);
	BOOL GetTPEPFilterInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, UINT &nDigits, UINT &nStatus, CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tDailyStartTime, CTimeSpan &tDailyStopTime, CTimeKey &tPeriodicalStartTime, CTimeSpan &tPeriodicalInterval, CTimeKey &tPeriodicalStopTime, COLORREF &nColor, CUIntArray &nOOLColors) CONST;
	BOOL SetTPEPAlertsInfo(INT nPage, INT nDisplay, CONST CByteArray &nAlertsInfo);
	BOOL GetTPEPAlertsInfo(INT nPage, INT nDisplay, CByteArray &nAlertsInfo) CONST;
	BOOL SetTPEPPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTPEPPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetEventBoxDefaultLayoutInfo(UINT nColumns = 0);
	BOOL GetEventBoxDefaultLayoutInfo(UINT &nColumns) CONST;
	BOOL SetEventBoxDefaultFontsInfo(CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pItemsFont = NULL);
	BOOL GetEventBoxDefaultFontsInfo(LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;
	BOOL SetEventBoxLayoutInfo(INT nPage, INT nDisplay, UINT nColumns, CONST CUIntArray &nWidths);
	BOOL GetEventBoxLayoutInfo(INT nPage, INT nDisplay, UINT &nColumns, CUIntArray &nWidths) CONST;
	BOOL SetEventBoxFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pItemsFont = NULL);
	BOOL GetEventBoxFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;
	BOOL SetEventBoxLogName(INT nPage, INT nDisplay, LPCTSTR pszComputerName = NULL, LPCTSTR pszSpacecraftName = NULL, LPCTSTR pszUserName = NULL, BOOL bLocal = FALSE);
	BOOL GetEventBoxLogName(INT nPage, INT nDisplay, CString &szComputerName, CString &szSpacecraftName, CString &szUserName, BOOL &bLocal) CONST;
	BOOL SetEventBoxModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nLimit = -1, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetEventBoxModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetEventBoxFilterInfo(INT nPage, INT nDisplay, UINT nMode, UINT nLimit, UINT nAutoCount, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CStringArray &szTypes, CONST CStringArray &szSubtypes, CONST CUIntArray &nColors);
	BOOL GetEventBoxFilterInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, UINT &nAutoCount, CTimeKey &tStartTime, CTimeKey &tStopTime, CStringArray &szTypes, CStringArray &szSubtypes, CUIntArray &nColors) CONST;
	BOOL SetEventBoxPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetEventBoxPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetEventBoxScheduleInfo(INT nPage, INT nDisplay, CONST CByteArray &nScheduleInfo);
	BOOL GetEventBoxScheduleInfo(INT nPage, INT nDisplay, CByteArray &nScheduleInfo) CONST;
	BOOL SetTCManualStackLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, COLORREF nGridBackgroundColor, BOOL bToolTips);
	BOOL GetTCManualStackLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, COLORREF &nGridBackgroundColor, BOOL &bToolTips) CONST;
	BOOL SetTCManualStackFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pItemsFont = NULL);
	BOOL GetTCManualStackFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;
	BOOL SetTCManualStackOperationsInfo(INT nPage, INT nDisplay, UINT nTelecommandingMode = -1, UINT nTelecommandingState = -1, UINT nTelecommandingChecks = -1, BOOL bTelecommandingInterlockMode = FALSE, BOOL bTelecommandingReleaseWaitMode = FALSE, BOOL bTelecommandingAutoRejectionMode = FALSE, INT nUpdateCheckCount = 0, INT nArgumentCount = 0, BOOL bAllArguments = FALSE, UINT nMiscellaneousOptions = 0, CONST CTimeSpan &tDefaultReleaseTimeWindow = 0, CONST CTimeSpan &tDispatchTimeWindow = 0);
	BOOL GetTCManualStackOperationsInfo(INT nPage, INT nDisplay, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingChecks, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, INT &nUpdateCheckCount, INT &nArgumentCount, BOOL &bAllArguments, UINT &nMiscellaneousOptions, CTimeSpan &tDefaultReleaseTimeWindow, CTimeSpan &tDispatchTimeWindow) CONST;
	BOOL SetTCManualStackContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo);
	BOOL GetTCManualStackContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo) CONST;
	BOOL SetTCManualStackSearchInfo(INT nPage, INT nDisplay, CONST CByteArray &nGroupsInfo, CONST CByteArray &nFiltersInfo);
	BOOL GetTCManualStackSearchInfo(INT nPage, INT nDisplay, CByteArray &nGroupsInfo, CByteArray &nFiltersInfo) CONST;
	BOOL SetTCManualStackTemplatesInfo(INT nPage, INT nDisplay, CONST CByteArray &nItemTemplatesInfo, CONST CByteArray &nComposedItemTemplatesInfo);
	BOOL GetTCManualStackTemplatesInfo(INT nPage, INT nDisplay, CByteArray &nItemTemplatesInfo, CByteArray &nComposedItemTemplatesInfo) CONST;
	BOOL SetTCManualStackLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy = 0, LPCTSTR pszArchivalFileName = NULL, DWORDLONG dwArchivalRetention = 0, CONST CTimeSpan &tArchivalRetention = 0, LPCTSTR pszRetrievalFileName = NULL, UINT nRetrievalReloadCount = 0, BOOL bShowAsEvent = FALSE);
	BOOL GetTCManualStackLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL SetTCManualStackAlertInfo(INT nPage, INT nDisplay, CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments);
	BOOL GetTCManualStackAlertInfo(INT nPage, INT nDisplay, CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST;
	BOOL SetTCManualStackPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTCManualStackPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetTCAutomaticStackLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nNormalStackScheduledColumns, CONST CUIntArray &nNormalStackScheduledWidths, CONST SIZE &sizeNormalStackScheduledList, COLORREF nNormalStackScheduledGridBackgroundColor, CONST CUIntArray &nNormalStackHistoricalColumns, CONST CUIntArray &nNormalStackHistoricalWidths, CONST SIZE &sizeNormalStackHistoricalList, COLORREF nNormalStackHistoricalGridBackgroundColor, CONST CUIntArray &nTimeTaggedStackScheduledColumns, CONST CUIntArray &nTimeTaggedStackScheduledWidths, CONST SIZE &sizeTimeTaggedStackScheduledList, COLORREF nTimeTaggedStackScheduledGridBackgroundColor, CONST CUIntArray &nTimeTaggedStackHistoricalColumns, CONST CUIntArray &nTimeTaggedStackHistoricalWidths, CONST SIZE &sizeTimeTaggedStackHistoricalList, COLORREF nTimeTaggedStackHistoricalGridBackgroundColor, BOOL bToolTips);
	BOOL GetTCAutomaticStackLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nNormalStackScheduledColumns, CUIntArray &nNormalStackScheduledWidths, CSize &sizeNormalStackScheduledList, COLORREF &nNormalStackScheduledGridBackgroundColor, CUIntArray &nNormalStackHistoricalColumns, CUIntArray &nNormalStackHistoricalWidths, CSize &sizeNormalStackHistoricalList, COLORREF &nNormalStackHistoricalGridBackgroundColor, CUIntArray &nTimeTaggedStackScheduledColumns, CUIntArray &nTimeTaggedStackScheduledWidths, CSize &sizeTimeTaggedStackScheduledList, COLORREF &nTimeTaggedStackScheduledGridBackgroundColor, CUIntArray &nTimeTaggedStackHistoricalColumns, CUIntArray &nTimeTaggedStackHistoricalWidths, CSize &sizeTimeTaggedStackHistoricalList, COLORREF &nTimeTaggedStackHistoricalGridBackgroundColor, BOOL &bToolTips) CONST;
	BOOL SetTCAutomaticStackFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pNormalStackScheduledTitleFont = NULL, CONST LOGFONT *pNormalStackScheduledItemsFont = NULL, CONST LOGFONT *pNormalStackHistoricalTitleFont = NULL, CONST LOGFONT *pNormalStackHistoricalItemsFont = NULL, CONST LOGFONT *pTimeTaggedStackScheduledTitleFont = NULL, CONST LOGFONT *pTimeTaggedStackScheduledItemsFont = NULL, CONST LOGFONT *pTimeTaggedStackHistoricalTitleFont = NULL, CONST LOGFONT *pTimeTaggedStackHistoricalItemsFont = NULL);
	BOOL GetTCAutomaticStackFontsInfo(INT nPage, INT nDisplay, LOGFONT *pNormalStackScheduledTitleFont, LOGFONT *pNormalStackScheduledItemsFont, LOGFONT *pNormalStackHistoricalTitleFont, LOGFONT *pNormalStackHistoricalItemsFont, LOGFONT *pTimeTaggedStackScheduledTitleFont, LOGFONT *pTimeTaggedStackScheduledItemsFont, LOGFONT *pTimeTaggedStackHistoricalTitleFont, LOGFONT *pTimeTaggedStackHistoricalItemsFont) CONST;
	BOOL SetTCAutomaticStackOperationsInfo(INT nPage, INT nDisplay, UINT nTelecommandingMode = -1, UINT nTelecommandingState = -1, UINT nTelecommandingChecks = -1, BOOL bTelecommandingInterlockMode = FALSE, BOOL bTelecommandingReleaseWaitMode = FALSE, BOOL bTelecommandingAutoRejectionMode = FALSE, INT nUpdateCheckCount = 0, INT nArgumentCount = 0, BOOL bAllArguments = FALSE, UINT nMiscellaneousOptions = 0, CONST CTimeSpan &tDefaultReleaseTimeWindow = 0, CONST CTimeSpan &tDispatchTimeWindow = 0, UINT nUserPermissions = -1);
	BOOL GetTCAutomaticStackOperationsInfo(INT nPage, INT nDisplay, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingChecks, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, INT &nUpdateCheckCount, INT &nArgumentCount, BOOL &bAllArguments, UINT &nMiscellaneousOptions, CTimeSpan &tDefaultReleaseTimeWindow, CTimeSpan &tDispatchTimeWindow, UINT &nUserPermissions) CONST;
	BOOL SetTCAutomaticStackContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo);
	BOOL GetTCAutomaticStackContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo) CONST;
	BOOL SetTCAutomaticStackFilterInfo(INT nPage, INT nDisplay, UINT nMode, LPCTSTR pszName, LPCTSTR pszSequence, CONST CUIntArray &nSubSystemIDs, UINT nLimitation, UINT nSortMode);
	BOOL GetTCAutomaticStackFilterInfo(INT nPage, INT nDisplay, UINT &nMode, CString &szName, CString &szSequence, CUIntArray &nSubSystemIDs, UINT &nLimitation, UINT &nSortMode) CONST;
	BOOL SetTCAutomaticStackSearchInfo(INT nPage, INT nDisplay, CONST CByteArray &nFiltersInfo);
	BOOL GetTCAutomaticStackSearchInfo(INT nPage, INT nDisplay, CByteArray &nFiltersInfo) CONST;
	BOOL SetTCAutomaticStackTemplatesInfo(INT nPage, INT nDisplay, CONST CByteArray &nItemTemplatesInfo, CONST CByteArray &nComposedItemTemplatesInfo);
	BOOL GetTCAutomaticStackTemplatesInfo(INT nPage, INT nDisplay, CByteArray &nItemTemplatesInfo, CByteArray &nComposedItemTemplatesInfo) CONST;
	BOOL SetTCAutomaticStackSubSystemsInfo(INT nPage, INT nDisplay, CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus);
	BOOL GetTCAutomaticStackSubSystemsInfo(INT nPage, INT nDisplay, CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST;
	BOOL SetTCAutomaticStackPlanningInfo(INT nPage, INT nDisplay, LPCTSTR pszMissionPlanningComputer = NULL, LPCTSTR pszMissionPlanningBackupComputer = NULL, UINT nMissionPlanningOptions = -1, CONST CTimeSpan &tMissionPlanningPeriod = 0, LPCTSTR pszMissionPlanningAudition = NULL, LPCTSTR pszMissionPlanningNotification = NULL, LPCTSTR pszFlightDynamicsComputer = NULL, LPCTSTR pszFlightDynamicsBackupComputer = NULL, UINT nFlightDynamicsOptions = -1);
	BOOL GetTCAutomaticStackPlanningInfo(INT nPage, INT nDisplay, CString &szMissionPlanningComputer, CString &szMissionPlanningBackupComputer, UINT &nMissionPlanningOptions, CTimeSpan &tMissionPlanningPeriod, CString &szMissionPlanningAudition, CString &szMissionPlanningNotification, CString &szFlightDynamicsComputer, CString &szFlightDynamicsBackupComputer, UINT &nFlightDynamicsOptions) CONST;
	BOOL SetTCAutomaticStackLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy = 0, LPCTSTR pszArchivalFileName = NULL, DWORDLONG dwArchivalRetention = 0, CONST CTimeSpan &tArchivalRetention = 0, LPCTSTR pszRetrievalFileName = NULL, UINT nRetrievalReloadCount = 0, BOOL bShowAsEvent = FALSE);
	BOOL GetTCAutomaticStackLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL SetTCAutomaticStackAlertInfo(INT nPage, INT nDisplay, CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments);
	BOOL GetTCAutomaticStackAlertInfo(INT nPage, INT nDisplay, CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST;
	BOOL SetTCAutomaticStackPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTCAutomaticStackPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetTCProceduresMonitorLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nListColumns, CONST CUIntArray &nListWidths, CONST SIZE &sizeList, CONST SIZE &sizeFlowchart, CONST SIZE &sizeCode, COLORREF nBackgroundColor, COLORREF nLabelsColor, BOOL bToolTips);
	BOOL GetTCProceduresMonitorLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nListColumns, CUIntArray &nListWidths, CSize &sizeList, CSize &sizeFlowchart, CSize &sizeCode, COLORREF &nBackgroundColor, COLORREF &nLabelsColor, BOOL &bToolTips) CONST;
	BOOL SetTCProceduresMonitorFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pListTitleFont = NULL, CONST LOGFONT *pListItemsFont = NULL, CONST LOGFONT *pFlowchartTitleFont = NULL, CONST LOGFONT *pFlowchartLabelsFont = NULL, CONST LOGFONT *pSourceCodeFont = NULL);
	BOOL GetTCProceduresMonitorFontsInfo(INT nPage, INT nDisplay, LOGFONT *pListTitleFont, LOGFONT *pListItemsFont, LOGFONT *pFlowchartTitleFont, LOGFONT *pFlowchartLabelsFont, LOGFONT *pSourceCodeFont) CONST;
	BOOL SetTCProceduresMonitorContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo, UINT nTelecommandingMode = -1, UINT nTelecommandingState = -1, UINT nTelecommandingChecks = -1, BOOL bTelecommandingReleaseWaitMode = FALSE);
	BOOL GetTCProceduresMonitorContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingChecks, BOOL &bTelecommandingReleaseWaitMode) CONST;
	BOOL SetTCProceduresMonitorLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy = 0, LPCTSTR pszArchivalFileName = NULL, DWORDLONG dwArchivalRetention = 0, CONST CTimeSpan &tArchivalRetention = 0, LPCTSTR pszRetrievalFileName = NULL, UINT nRetrievalReloadCount = 0, BOOL bShowAsEvent = FALSE);
	BOOL GetTCProceduresMonitorLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL SetTCProceduresMonitorPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTCProceduresMonitorPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetTCOnBoardBufferQueuesLayoutInfo(INT nPage, INT nDisplay, CONST CStringArray &szBuffers, CONST CUIntArray &nSummaryColumns, CONST CUIntArray &nSummaryWidths, CONST SIZE &sizeSummaryList, CONST CUIntArray &nDetailsColumns, CONST CUIntArray &nDetailsWidths, CONST SIZE &sizeDetailsList, CONST CDWordArray &dwDetailsGridBackgroundColors, BOOL bToolTips);
	BOOL GetTCOnBoardBufferQueuesLayoutInfo(INT nPage, INT nDisplay, CStringArray &szBuffers, CUIntArray &nSummaryColumns, CUIntArray &nSummaryWidths, CSize &sizeSummaryList, CUIntArray &nDetailsColumns, CUIntArray &nDetailsWidths, CSize &sizeDetailsList, CDWordArray &dwDetailsGridBackgroundColors, BOOL &bToolTips) CONST;
	BOOL SetTCOnBoardBufferQueuesFontsInfo(INT nPage, INT nDisplay, CONST CByteArray &nFontsInfo);
	BOOL GetTCOnBoardBufferQueuesFontsInfo(INT nPage, INT nDisplay, CByteArray &nFontsInfo) CONST;
	BOOL SetTCOnBoardBufferQueuesPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTCOnBoardBufferQueuesPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetTCOnBoardMemoryImagesLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nSummaryColumns, CONST CUIntArray &nSummaryWidths, CONST SIZE &sizeSummaryList, CONST CUIntArray &nDetailsColumns, CONST CUIntArray &nDetailsWidths, CONST SIZE &sizeDetailsList, BOOL bToolTips);
	BOOL GetTCOnBoardMemoryImagesLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nSummaryColumns, CUIntArray &nSummaryWidths, CSize &sizeSummaryList, CUIntArray &nDetailsColumns, CUIntArray &nDetailsWidths, CSize &sizeDetailsList, BOOL &bToolTips) CONST;
	BOOL SetTCOnBoardMemoryImagesFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pSummaryTitleFont = NULL, CONST LOGFONT *pSummaryItemsFont = NULL, CONST LOGFONT *pDetailsTitleFont = NULL, CONST LOGFONT *pDetailsItemsFont = NULL);
	BOOL GetTCOnBoardMemoryImagesFontsInfo(INT nPage, INT nDisplay, LOGFONT *pSummaryTitleFont, LOGFONT *pSummaryItemsFont, LOGFONT *pDetailsTitleFont, LOGFONT *pDetailsItemsFont) CONST;
	BOOL SetTCOnBoardMemoryImagesTablesInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pItemsFont = NULL, COLORREF nTitleFontColor = -1, COLORREF nItemsFontColor = -1, COLORREF nTitleBackgroundColor = -1, COLORREF nItemsBackgroundColor = -1);
	BOOL GetTCOnBoardMemoryImagesTablesInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST;
	BOOL SetTCOnBoardMemoryImagesContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo, CONST CTimeSpan tDBMSDelay = 0, BOOL bDBMSFlush = FALSE, BOOL bDBMSFile = FALSE);
	BOOL GetTCOnBoardMemoryImagesContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo, CTimeSpan &tDBMSDelay, BOOL &bDBMSFlush, BOOL &bDBMSFile) CONST;
	BOOL SetTCOnBoardMemoryImagesLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy = 0, LPCTSTR pszArchivalFileName = NULL, DWORDLONG dwArchivalRetention = 0, CONST CTimeSpan &tArchivalRetention = 0, LPCTSTR pszRetrievalFileName = NULL, UINT nRetrievalReloadCount = 0, BOOL bShowAsEvent = FALSE);
	BOOL GetTCOnBoardMemoryImagesLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL SetTCOnBoardMemoryImagesPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTCOnBoardMemoryImagesPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetTCDiagnosticsOversamplingDumpLayoutInfo(INT nPage, INT nDisplay, CONST CByteArray &nLayoutData, CONST CUIntArray &nParametersColumns, CONST CUIntArray &nParametersWidths, CONST SIZE &sizeParameters, CONST CUIntArray &nRawDataColumns, CONST CUIntArray &nRawDataWidths, CONST SIZE &sizeRawData, COLORREF nNumbersBackgroundColor, COLORREF nValuesBackgroundColor, UINT nSampleLimit, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips);
	BOOL GetTCDiagnosticsOversamplingDumpLayoutInfo(INT nPage, INT nDisplay, CByteArray &nLayoutData, CUIntArray &nParametersColumns, CUIntArray &nParametersWidths, CSize &sizeParameters, CUIntArray &nRawDataColumns, CUIntArray &nRawDataWidths, CSize &sizeRawData, COLORREF &nNumbersBackgroundColor, COLORREF &nValuesBackgroundColor, UINT &nSampleLimit, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST;
	BOOL SetTCDiagnosticsOversamplingDumpFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pParametersTitleFont = NULL, CONST LOGFONT *pParametersItemsFont = NULL, CONST LOGFONT *pParametersValuesFont = NULL, CONST LOGFONT *pRawDataTitleFont = NULL, CONST LOGFONT *pRawDataItemsFont = NULL);
	BOOL GetTCDiagnosticsOversamplingDumpFontsInfo(INT nPage, INT nDisplay, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pParametersValuesFont, LOGFONT *pRawDataTitleFont, LOGFONT *pRawDataItemsFont) CONST;
	BOOL SetTCDiagnosticsOversamplingDumpModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeSpan &tInterval = 0, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetTCDiagnosticsOversamplingDumpModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetTCDiagnosticsOversamplingDumpPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTCDiagnosticsOversamplingDumpPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetTCDiagnosticsOversamplingDumpRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetTCDiagnosticsOversamplingDumpRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetTCHistoryLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetTCHistoryLayoutName(INT nPage, INT nDisplay, CString &szName) CONST;
	BOOL SetTCHistoryLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, COLORREF nGridBackgroundColor, BOOL bToolTips);
	BOOL GetTCHistoryLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, COLORREF &nGridBackgroundColor, BOOL &bToolTips) CONST;
	BOOL SetTCHistoryFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont = NULL, CONST LOGFONT *pItemsFont = NULL);
	BOOL GetTCHistoryFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;
	BOOL SetTCHistoryFilterInfo(INT nPage, INT nDisplay, UINT nMode = -1, LPCTSTR pszComputer = NULL, LPCTSTR pszName = NULL, LPCTSTR pszSequence = NULL, UINT nLimitation = -1, UINT nAutoload = -1, UINT nSortMode = -1);
	BOOL GetTCHistoryFilterInfo(INT nPage, INT nDisplay, UINT &nMode, CString &szComputer, CString &szName, CString &szSequence, UINT &nLimitation, UINT &nAutoload, UINT &nSortMode) CONST;
	BOOL SetTCHistoryModeInfo(INT nPage, INT nDisplay, UINT nMode = -1, UINT nSpeed = -1, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);
	BOOL GetTCHistoryModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetTCHistoryAlertInfo(INT nPage, INT nDisplay, CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments);
	BOOL GetTCHistoryAlertInfo(INT nPage, INT nDisplay, CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST;
	BOOL SetTCHistoryPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo);
	BOOL GetTCHistoryPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST;
	BOOL SetTCHistoryRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName = NULL);
	BOOL GetTCHistoryRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST;
	BOOL SetCLCWPanelLayoutInfo(LPCRECT pPosition = NULL, BOOL bVisible = FALSE);
	BOOL GetCLCWPanelLayoutInfo(LPRECT pPosition, BOOL &bVisible) CONST;
	BOOL SetPFLPServiceSettingsInfo(CONST CByteArray &nSettingsInfo);
	BOOL GetPFLPServiceSettingsInfo(CByteArray &nSettingsInfo) CONST;
	BOOL SetTPEPServiceSettingsInfo(UINT nPort = -1, UINT nBufferSize = -1, UINT nCharset = -1, CONST CTimeSpan &tTimeout = 0);
	BOOL GetTPEPServiceSettingsInfo(UINT &nPort, UINT &nBufferSize, UINT &nCharset, CTimeSpan &tTimeout) CONST;
	BOOL SetTPEPServiceAvailabilityInfo(UINT nCode = -1, CONST CTimeSpan &tStartTime = 0, CONST CTimeSpan &tStopTime = 0);
	BOOL GetTPEPServiceAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetTPEPServiceSecurityInfo(CONST CStringArray &szUsers, CONST CUIntArray &nCodes, CONST CTimeKeyArray &tStartTimes, CONST CTimeKeyArray &tStopTimes);
	BOOL GetTPEPServiceSecurityInfo(CStringArray &szUsers, CUIntArray &nCodes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST;
	BOOL SetTPEPServiceProfileInfo(CONST CByteArray &nPacketProfilesInfo, CONST CByteArray &nParameterProfilesInfo);
	BOOL GetTPEPServiceProfileInfo(CByteArray &nPacketProfilesInfo, CByteArray &nParameterProfilesInfo) CONST;
	BOOL SetAutomationServiceSettingsInfo(UINT nPort = -1, UINT nBufferSize = -1, CONST CTimeSpan &tTimeout = 0, BOOL bEnabled = FALSE);
	BOOL GetAutomationServiceSettingsInfo(UINT &nPort, UINT &nBufferSize, CTimeSpan &tTimeout, BOOL &bEnabled) CONST;
	BOOL SetAutomationServiceClientsInfo(CONST CByteArray &nClientsInfo);
	BOOL GetAutomationServiceClientsInfo(CByteArray &nClientsInfo) CONST;
	BOOL SetToolsDownloadProfilesInfo(CONST CByteArray &nProfilesInfo);
	BOOL GetToolsDownloadProfilesInfo(CByteArray &nProfilesInfo) CONST;
	BOOL SetToolsDatabaseOptionsInfo(UINT nOption = -1, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tEndTime = 0);
	BOOL GetToolsDatabaseOptionsInfo(UINT &nOption, CTimeKey &tStartTime, CTimeKey &tEndTime) CONST;
	BOOL SetToolsSatelliteTrackingOptionsInfo(LPCTSTR pszConfigurationFileName = NULL, LPCTSTR pszHelpFileName = NULL, BOOL bEnabled = FALSE);
	BOOL GetToolsSatelliteTrackingOptionsInfo(CString &szConfigurationFileName, CString &szHelpFileName, BOOL &bEnabled) CONST;
	BOOL SetToolsEMailSettingsInfo(CONST CByteArray &nSettingsInfo);
	BOOL GetToolsEMailSettingsInfo(CByteArray &nSettingsInfo) CONST;

	BOOL DeleteAllInfo();
	BOOL DeleteDisplayAreaInfo();
	BOOL DeleteDisplayPageInfo(INT nPage);
	BOOL DeleteDisplayWindowInfo(INT nPage, INT nDisplay);
	BOOL DeleteTemporaryDisplaysInfo();
	BOOL DeleteEventBoxDefaultInfo();
	BOOL DeleteTelemetryServiceInfo();
	BOOL DeleteTelemetryArchivesInfo();
	BOOL DeleteTelemetryReportsServiceInfo();
	BOOL DeleteTelecommandServiceInfo();
	BOOL DeleteTelecommandArchivesInfo();
	BOOL DeleteMemoryDumpServiceInfo();
	BOOL DeleteNotificationServiceInfo();
	BOOL DeletePFLPServiceInfo();
	BOOL DeleteTPEPServiceInfo();
	BOOL DeleteAutomationServiceInfo();
	BOOL DeleteToolsInfo();

	BOOL DeleteSubKey(LPCTSTR pszSubKey);

private:
	CString QuerySubKey() CONST;
	CString QuerySpacecraftSubKey() CONST;
	CString QueryDisplayAreaSubKey() CONST;
	CString QueryDisplayPageSubKey(INT nPage) CONST;
	CString QueryDisplayWindowSubKey(INT nPage, INT nDisplay) CONST;
	CString QueryTemporaryDisplaysSubKey() CONST;
	CString QueryEventBoxDefaultSubKey() CONST;
	CString QueryTelemetryServiceSubKey() CONST;
	CString QueryTelemetryArchivesSubKey() CONST;
	CString QueryTelemetryReportsServiceSubKey() CONST;
	CString QueryTelecommandServiceSubKey() CONST;
	CString QueryTelecommandArchivesSubKey() CONST;
	CString QueryMemoryDumpServiceSubKey() CONST;
	CString QueryNotificationServiceSubKey() CONST;
	CString QueryPFLPServiceSubKey() CONST;
	CString QueryTPEPServiceSubKey() CONST;
	CString QueryAutomationServiceSubKey() CONST;
	CString QueryToolsSubKey() CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __PROFILE_H__
