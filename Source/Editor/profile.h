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
* 1998/02/18 | 1.00.00 | Initial creation. [AW]                      *
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
	BOOL SetPosition(LPCRECT pRect = NULL);
	BOOL GetPosition(LPRECT pRect) CONST;
	BOOL SetDisplayWindowCount(INT nCount = -1);
	BOOL GetDisplayWindowCount(INT &nCount) CONST;
	BOOL SetDisplayWindowType(INT nDisplay, UINT nType = -1);
	BOOL GetDisplayWindowType(INT nDisplay, UINT &nType) CONST;
	BOOL SetDisplayWindowName(INT nDisplay, LPCTSTR pszName = NULL);
	BOOL GetDisplayWindowName(INT nDisplay, CString &szName) CONST;
	BOOL SetDisplayWindowPlacement(INT nDisplay, LPCRECT pRect = NULL, CONST POINT *pPoint = NULL, UINT nShow = -1);
	BOOL GetDisplayWindowPlacement(INT nDisplay, LPRECT pRect, LPPOINT pPoint, UINT &nShow) CONST;
	BOOL SetTMPacketsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetTMPacketsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetTCFunctionsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetTCFunctionsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetTCSequencesFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetTCSequencesFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetTCProcedureWindowPropertyInfo(INT nDisplay, INT nFlowchartPaneWidth = -1, INT nPropertiesPaneWidth = -1, CONST LOGFONT *plfStepsLabel = NULL, COLORREF nStepsLabelColor = -1, COLORREF nBackgroundColor = -1);
	BOOL GetTCProcedureWindowPropertyInfo(INT nDisplay, INT &nFlowchartPaneWidth, INT &nPropertiesPaneWidth, LOGFONT *plfStepsLabel, COLORREF &nStepsLabelColor, COLORREF &nBackgroundColor) CONST;
	BOOL SetTMParametersFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetTMParametersFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetTCParametersFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetTCParametersFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetOBProcessorsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetOBProcessorsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetANDsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetANDsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetGRDsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetGRDsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetMMDWindowPropertyInfo(INT nDisplay, INT nImagePaneHeight = -1, INT nImagePaneMinHeight = -1, INT nCodePaneHeight = -1, INT nCodePaneMinHeight = -1, LPCRECT pHotSpot = NULL);
	BOOL GetMMDWindowPropertyInfo(INT nDisplay, INT &nImagePaneHeight, INT &nImagePaneMinHeight, INT &nCodePaneHeight, INT &nCodePaneMinHeight, LPRECT pHotSpot) CONST;
	BOOL SetPODsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle = NULL, CONST LOGFONT *plfItems = NULL, COLORREF nTitleColor = -1, COLORREF nItemsColor = -1, COLORREF nTitleBackground = -1, COLORREF nKeysBackground = -1);
	BOOL GetPODsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	BOOL SetScriptWindowPropertyInfo(INT nDisplay, INT nCodePaneHeight = -1, INT nCodePaneMinHeight = -1, INT nImagePaneHeight = -1, INT nImagePaneMinHeight = -1);
	BOOL GetScriptWindowPropertyInfo(INT nDisplay, INT &nCodePaneHeight, INT &nCodePaneMinHeight, INT &nImagePaneHeight, INT &nImagePaneMinHeight) CONST;
	BOOL SetWorkspaceWindowInfo(UINT nState, LPCRECT pRect, CONST CByteArray &nInfo);
	BOOL GetWorkspaceWindowInfo(UINT &nState, LPRECT pRect, CByteArray &nInfo) CONST;
	BOOL SetOutputWindowInfo(UINT nState, LPCRECT pRect, CONST CByteArray &nInfo);
	BOOL GetOutputWindowInfo(UINT &nState, LPRECT pRect, CByteArray &nInfo) CONST;
	BOOL SetZoomWindowInfo(UINT nState = -1, LPCRECT pRect = NULL);
	BOOL GetZoomWindowInfo(UINT &nState, LPRECT pRect) CONST;
	BOOL SetMimicsObjectsToolBarInfo(LPCRECT pRect = NULL, BOOL bShow = FALSE);
	BOOL GetMimicsObjectsToolBarInfo(LPRECT pRect, BOOL &bShow) CONST;
	BOOL SetTCStepsToolBarInfo(LPCRECT pRect = NULL, BOOL bShow = FALSE);
	BOOL GetTCStepsToolBarInfo(LPRECT pRect, BOOL &bShow) CONST;
	BOOL SetMimicsGroupsInfo(CONST CByteArray &nGroupsInfo);
	BOOL GetMimicsGroupsInfo(CByteArray &nGroupsInfo) CONST;
	BOOL SetMimicsTestInfo(CONST CByteArray &nTestInfo);
	BOOL GetMimicsTestInfo(CByteArray &nTestInfo) CONST;
	BOOL SetPrintProfileInfo(CONST CByteArray &nProfileInfo);
	BOOL GetPrintProfileInfo(CByteArray &nProfileInfo) CONST;
	BOOL SetCompileOptions(LPCTSTR pszCompilerPath = NULL, LPCTSTR pszLinkerPath = NULL, LPCTSTR pszPlatForm = NULL, LPCTSTR pszIncludeDirectory = NULL, LPCTSTR pszLibraryDirectory = NULL, LPCTSTR pszDPLOptions = NULL, LPCTSTR pszMDLOptions = NULL, LPCTSTR pszTPLOptions = NULL);
	BOOL GetCompileOptions(CString &szCompilerPath, CString &szLinkerPath, CString &szPlatForm, CString &szIncludeDirectory, CString &szLibraryDirectory, CString &szDPLOptions, CString &szMDLOptions, CString &szTPLOptions) CONST;
	BOOL SetCompileDirectivesInfo(CONST CByteArray &nDirectivesInfo);
	BOOL GetCompileDirectivesInfo(CByteArray &nDirectivesInfo) CONST;
	BOOL SetCompileBatchesInfo(CONST CByteArray &nBatchesInfo);
	BOOL GetCompileBatchesInfo(CByteArray &nBatchesInfo) CONST;
	BOOL SetAssistantCharacterInfo(LPCTSTR pszName = NULL, CONST POINT *pPosition = NULL, BOOL bVisible = FALSE, BOOL bSpeak = FALSE, LONG lSpeed = 0, LONG lPitch = 0, LONG lVolume = 0, BOOL bWordBalloon = FALSE, BOOL bSoundEffects = FALSE);
	BOOL GetAssistantCharacterInfo(CString &szName, POINT *pPosition, BOOL &bVisible, BOOL &bSpeak, LONG &lSpeed, LONG &lPitch, LONG &lVolume, BOOL &bWordBalloon, BOOL &bSoundEffects) CONST;
	BOOL SetRecentDocuments(CONST CByteArray &nInfo);
	BOOL GetRecentDocuments(CByteArray &nInfo) CONST;
	BOOL SetRecentDatabases(CONST CByteArray &nInfo);
	BOOL GetRecentDatabases(CByteArray &nInfo) CONST;

	BOOL DeleteAllInfo();
	BOOL DeleteDisplayAreaInfo();
	BOOL DeleteDisplayWindowInfo(INT nDisplay);
	BOOL DeleteDatabaseInfo(LPCTSTR pszDatabase = NULL);
	BOOL DeleteMimicsGroupsInfo();

	BOOL DeleteSubKey(LPCTSTR pszSubKey);

private:
	CString QuerySubKey() CONST;
	CString QueryDisplayAreaSubKey() CONST;
	CString QueryDisplayWindowSubKey(INT nDisplay) CONST;
	CString QueryDatabaseSubKey(LPCTSTR pszDatabase = NULL) CONST;
	CString QueryMimicsGroupsSubKey() CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __PROFILE_H__
