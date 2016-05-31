// TCDIAGNOSTICS.H : Telecommand Diagnostics Services Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand diagnostics services
// related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2008/07/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TCDIAGNOSTICS_H__
#define __TCDIAGNOSTICS_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpLayout

// Specify the telecommand diagnostics oversampling dump layout related options
#define TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWRAWDATAPANE   (1<<0)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWNUMBERCOLUMN   (1<<1)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWTIMECOLUMN   (1<<2)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWVALUECOLUMN   (1<<3)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_SHOWUNITCOLUMN   (1<<4)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_AUTOMATIC   (1<<5)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUT_OPTION_MANUAL   (1<<6)

class CTCDiagnosticsOversamplingDumpLayout : public COversamplingParameters
{
	// Construction
public:
	CTCDiagnosticsOversamplingDumpLayout();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbParameters;
		INT  cbValidityParameter;
		UINT  nAttributes;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szValidityParameter;
	UINT  m_nAttributes;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAttributes(UINT nAttributes);
	UINT GetAttributes() CONST;
	VOID SetValidityParameter(LPCTSTR pszTag);
	CString GetValidityParameter() CONST;

	INT Find(LPCTSTR pszTag) CONST;

	BOOL Copy(CONST CTCDiagnosticsOversamplingDumpLayout *pLayout);
	BOOL Compare(CONST CTCDiagnosticsOversamplingDumpLayout *pLayout) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpLayouts

class CTCDiagnosticsOversamplingDumpLayouts : public CPtrArray
{
	// Construction
public:
	CTCDiagnosticsOversamplingDumpLayouts();
	~CTCDiagnosticsOversamplingDumpLayouts();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCDiagnosticsOversamplingDumpLayout *pLayout);

	INT Find(LPCTSTR pszName) CONST;

	CTCDiagnosticsOversamplingDumpLayout *GetAt(INT nIndex) CONST;
	CTCDiagnosticsOversamplingDumpLayout *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCDiagnosticsOversamplingDumpLayouts *pLayouts);
	BOOL Compare(CONST CTCDiagnosticsOversamplingDumpLayouts *pLayouts) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSample

// Specify the telecommand diagnostics oversampling dump alert types
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_NONE   0
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_INFORMATION   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_WARNING   2
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSAMPLE_ALERTTYPE_ERROR   3

class CTCDiagnosticsOversamplingDumpSample : public COversamplingParameters
{
	// Construction
public:
	CTCDiagnosticsOversamplingDumpSample();
	~CTCDiagnosticsOversamplingDumpSample();

	// Attributes
private:
	INT  m_nBlock;
	UINT  m_nAlertType;
	CString  m_szAlertMessage;

	// Operations
public:
	VOID SetBlock(INT nBlock);
	INT GetBlock() CONST;
	VOID SetAlertMessage(UINT nType, LPCTSTR pszMessage);
	UINT GetAlertMessage(CString &szMessage) CONST;

	COversamplingParameter *GetAt(INT nIndex) CONST;
	COversamplingParameter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCDiagnosticsOversamplingDumpSample *pSample);
	BOOL Compare(CONST CTCDiagnosticsOversamplingDumpSample *pSample) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSamples

class CTCDiagnosticsOversamplingDumpSamples : public CPtrArray
{
	// Construction
public:
	CTCDiagnosticsOversamplingDumpSamples();
	~CTCDiagnosticsOversamplingDumpSamples();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCDiagnosticsOversamplingDumpSample *pSample);

	CTCDiagnosticsOversamplingDumpSample *GetAt(INT nIndex) CONST;
	CTCDiagnosticsOversamplingDumpSample *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCDiagnosticsOversamplingDumpSamples *pSamples);
	BOOL Compare(CONST CTCDiagnosticsOversamplingDumpSamples *pSamples) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpPrintJobInfo

class CTCDiagnosticsOversamplingDumpPrintJobInfo : public CObject
{
	// Construction
public:
	CTCDiagnosticsOversamplingDumpPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbProfile;
		INT  cbComments;
		INT  cbParameters;
		UINT  nPrintMode;
		UINT  nPrintRange[2];
		TIMEKEY  tPrintRange[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szProfile;
	CString  m_szComments;
	CStringArray  m_szParameters;
	CTimeKey  m_tPrintRange[2];
	UINT  m_nPrintRange[2];
	UINT  m_nPrintMode;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetProfile(LPCTSTR pszProfile);
	CString GetProfile() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;

	BOOL SetPrintMode(UINT nMode);
	UINT GetPrintMode() CONST;
	VOID SetPrintParameters(CONST CStringArray &szParameters);
	INT GetPrintParameters(CStringArray &szParameters) CONST;
	BOOL SetPrintRange(UINT nMin, UINT nMax);
	BOOL SetPrintRange(CONST CTimeKey &tMin, CONST CTimeKey &tMax);
	BOOL GetPrintRange(UINT &nMin, UINT &nMax) CONST;
	BOOL GetPrintRange(CTimeKey &tMin, CTimeKey &tMax) CONST;

	VOID Copy(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpPrintJobs

class CTCDiagnosticsOversamplingDumpPrintJobs : public CPtrArray
{
	// Construction
public:
	CTCDiagnosticsOversamplingDumpPrintJobs();
	~CTCDiagnosticsOversamplingDumpPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTCDiagnosticsOversamplingDumpPrintJobInfo *GetAt(INT nIndex) CONST;
	CTCDiagnosticsOversamplingDumpPrintJobInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCDiagnosticsOversamplingDumpPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTCDiagnosticsOversamplingDumpPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsLayoutPage dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_STATIC   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_RAWDATAPANE   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_INVALIDDATA   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_BADDATA   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_SHOW_TOOLTIPS   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_STATIC   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_NUMBERS   1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_TIME   1010
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUND   1011
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_BACKGROUNDCOLOR   1012
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_VALUES   1013
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_UNITS  1014
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUND   1015
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FORMAT_COLUMNS_PARAMETERSBACKGROUNDCOLOR   1016
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS   1017
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1018
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1019
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1020
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES   1021
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_STATIC   1022
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_TITLE   1023
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_RAWDATA_ITEMS   1024
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1025
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1026
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_NAMES   1027
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1028
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_STYLE   1029
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1030
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SIZE   1031
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1032
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1033

class CTCDiagnosticsOversamplingDumpSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsLayoutPage)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpSettingsLayoutPage();

	// Attributes
private:
	UINT  m_nColumns[2];
	LOGFONT  m_fntTitle[2][2];
	LOGFONT  m_fntItems[2][2];
	LOGFONT  m_fntValues[2];
	COLORREF  m_nBackgroundColor[2][2];
	BOOL  m_bInvalidData[2];
	BOOL  m_bBadData[2];
	BOOL  m_bToolTips[2];
	BOOL  m_bParameters;
private:
	CString  m_szFontSampleText;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpSettingsLayoutPage)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetValuesFont(UINT nPane, LPLOGFONT pValuesFont) CONST;
	BOOL GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;
	BOOL GetInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetBadDataMode(BOOL &bEnable) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTCDiagnosticsOversamplingDumpSettingsDialog *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	BOOL EnumLayoutColumns();

	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpSettingsLayoutPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnShowRawDataPane();
	afx_msg void OnShowInvalidData();
	afx_msg void OnShowBadData();
	afx_msg void OnShowToolTips();
	afx_msg void OnNumberColumns();
	afx_msg void OnTimeColumns();
	afx_msg void OnValueColumns();
	afx_msg void OnUnitColumns();
	afx_msg void OnBackground();
	afx_msg void OnParametersBackground();
	afx_msg void OnParametersTitleFont();
	afx_msg void OnParametersItemsFont();
	afx_msg void OnParametersValuesFont();
	afx_msg void OnRawDataTitleFont();
	afx_msg void OnRawDataItemsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeBackground();
	afx_msg void OnSelchangeParametersBackground();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsContentsPage dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER_STATIC   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_PARAMETER   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_ADD   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVE   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REMOVEALL   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST_STATIC   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIST   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITY   1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_VALIDITYPARAMETER   1010
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_USELIMIT   1011
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT   1012
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_LIMIT_STATIC   1013
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_NOAUTOMATICDETECTION   1014
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE_STATIC   1015
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE   1016
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_OVERSAMPLINGRATE_SECONDS_STATIC   1017
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH_STATIC   1018
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH   1019
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_REQUESTEDBANDWIDTH_BITSPERSECOND_STATIC   1020
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_STATIC   1021
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH   1022
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_REMARK_STATIC   1023
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_BITSPERSECOND_STATIC   1024
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_AVAILABLEBANDWIDTH_TIME   1025
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_BANDWIDTHREMARK_STATIC   1026
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_CONTENTSPAGE_DUMP   1027

// Specify the telecommand diagnostics oversamplung dump settings contents page related limits
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_MINIMUMSAMPLELIMIT   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_MAXIMUMSAMPLELIMIT   10000
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_DEFAULTSAMPLELIMIT   1000
// Specify the telecommand diagnostics oversamplung dump settings contents page related timer identifiers
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_UPDATE_TIMERID   100
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSCONTENTSPAGE_UPDATE_TIMEOUT   1000

class CTCDiagnosticsOversamplingDumpSettingsContentsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsContentsPage)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpSettingsContentsPage();

	// Attributes
private:
	CTCDiagnosticsOversamplingDumpLayout  m_cLayout[2];
	CStringArray  m_szParameters[2];
	UINT  m_nSampleLimit[2];
private:
	UINT_PTR  m_nTimerID;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpSettingsContentsPage)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_SETTINGS_CONTENTSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetSampleLimit(UINT &nLimit) CONST;

	class CTCDiagnosticsOversamplingDumpSettingsDialog *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	BOOL EnumParameters();
	BOOL EnumValidityParameters();
	BOOL EnumOversamplingRates();

	VOID ShowContents();

	VOID UpdateTMBandwidth();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpSettingsContentsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpSettingsContentsPage)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAddParameter();
	afx_msg void OnRemoveParameter();
	afx_msg void OnRemoveAllParameters();
	afx_msg void OnValidityParameter();
	afx_msg void OnLimitSamples();
	afx_msg void OnNoAutomaticDetection();
	afx_msg void OnTelecommands();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeValidityParameter();
	afx_msg void OnSelchangeOversamplingRate();
	afx_msg void OnSpinchangeSampleLimit();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsRetrievingPage dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_DATASOURCE   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_INSPECT   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1010
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1011
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1012
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1013
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1014
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1015
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1016
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1017
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1018
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1019
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1020
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1021
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1022

class CTCDiagnosticsOversamplingDumpSettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpSettingsRetrievingPage();

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class CTCDiagnosticsOversamplingDumpSettingsDialog *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpSettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsPrintingComments window

class CTCDiagnosticsOversamplingDumpSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsPrintingPage dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE_STATIC   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_PROFILE   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERVALUES   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETER   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTPARAMETERLIST   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_ADDPARAMETER   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_REMOVEPARAMETER   1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_PRINTRAWDATA   1010
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER   1011
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW   1012
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC   1013
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH   1014
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME   1015
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_START   1016
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_TO_STATIC   1017
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_OPTIONS_TIME_STOP   1018
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTS   1019
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC   1020
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_COMMENTSTEXT   1021
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGS_PRINTINGPAGE_CLEARCOMMENTS   1022

// Specify the telecommand diagnostics oversampling dump settings printing page related limits
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE   10000
#define TCDIAGNOSTICSOVERSAMPLINGDUMPSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE   100

class CTCDiagnosticsOversamplingDumpSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsPrintingPage)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpSettingsPrintingPage();

	// Attributes
private:
	CStringArray  m_szParameters;
	CTCDiagnosticsOversamplingDumpPrintJobs  m_pJobs[2];
private:
	CTCDiagnosticsOversamplingDumpSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpSettingsPrintingPage)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pJobs) CONST;

	class CTCDiagnosticsOversamplingDumpSettingsDialog *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTCDiagnosticsOversamplingDumpPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintParameterValues();
	afx_msg void OnPrintRawData();
	afx_msg void OnPrintItemRange();
	afx_msg void OnPrintTimeRange();
	afx_msg void OnAddPrintParameter();
	afx_msg void OnRemovePrintParameter();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeParameterList();
	afx_msg void OnSpinchangeLowItemRange();
	afx_msg void OnSpinchangeHighItemRange();
	afx_msg void OnSpinchangeStartTimeRange();
	afx_msg void OnSpinchangeStopTimeRange();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsTabCtrl window

class CTCDiagnosticsOversamplingDumpSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpSettingsDialog

class CTCDiagnosticsOversamplingDumpSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpSettingsDialog)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpSettingsDialog();

	// Attributes
private:
	CTCDiagnosticsOversamplingDumpSettingsTabCtrl  m_wndTabCtrl;
	CTCDiagnosticsOversamplingDumpSettingsLayoutPage  m_pageLayout;
	CTCDiagnosticsOversamplingDumpSettingsContentsPage  m_pageContents;
	CTCDiagnosticsOversamplingDumpSettingsRetrievingPage  m_pageRetrieving;
	CTCDiagnosticsOversamplingDumpSettingsPrintingPage  m_pagePrinting;

	// Operations
public:
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayoutTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutValuesFont(UINT nPane, LPLOGFONT pValuesFont) CONST;
	BOOL GetLayoutBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;
	BOOL GetLayoutSampleLimit(UINT &nLimit) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCDiagnosticsOversamplingDumpOpenDialog *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpSettingsDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpPropertiesDialog dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_NAME_STATIC   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_NAME   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESCRIPTION   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PARAMETERS   1011
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_REMARK_STATIC   1012
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_STATIC   1013
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_MANUALSTACK   1014
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK   1015
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_STATIC   1016
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_IMMEDIATELY   1017
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_ATTIME   1018
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_RELEASE_TIME   1019
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_PREAUTHORIZED   1020
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_HELP   1021

class CTCDiagnosticsOversamplingDumpPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpPropertiesDialog)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpPropertiesDialog();   // standard constructor

	// Attributes
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
	CTCDiagnosticsOversamplingDumpLayout  m_cLayout;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpPropertiesDialog)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCDiagnosticsOversamplingDumpLayout &cLayout);

	class CTCDiagnosticsOversamplingDumpSettingsContentsPage *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpPropertiesDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersCalibrationPage dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_STATUS   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE_POINTS   1010

class CTCDiagnosticsOversamplingDumpParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersCalibrationPage)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpParametersCalibrationPage();

	// Attributes
private:
	INT  m_nCalTableID;
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nCalValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpParametersCalibrationPage)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);
	VOID ShowCalibrationInfo();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl window

class CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCDiagnosticsOversamplingDumpParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersFolder

class CTCDiagnosticsOversamplingDumpParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersFolder)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpParametersFolder();

	// Attributes
private:
	CTCDiagnosticsOversamplingDumpParametersFolderTabCtrl  m_wndTabCtrl;
	CTCDiagnosticsOversamplingDumpParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);

	class CTCDiagnosticsOversamplingDumpParametersDialog *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersDialog dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM_STATIC   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_ITEM   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_FOLDER   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_HELP   1005

class CTCDiagnosticsOversamplingDumpParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersDialog)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szParameter;
private:
	CTCDiagnosticsOversamplingDumpParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpParametersDialog)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_PARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);

	class CTCDiagnosticsOversamplingDumpWnd *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpParametersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRetrieveDialog dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TITLE_STATIC   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TITLE   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TYPE_STATIC   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_TYPE   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_START_STATIC   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STARTTIME   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_EXACTTIME   1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOP_STATIC   1010
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYTIME   1011
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPTIME   1012
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_STOPBYEND   1013
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PLAYBACKMODE   1014
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_AUTOMATIC   1015
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_PSEUDOREALTIME   1016
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_MANUAL   1017
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED_STATIC   1018
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SPEED   1019
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_SLOW   1020
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_FAST   1021
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVAL   1022
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME   1023
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HISTORY_INTERVALTIME_STATIC   1024
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_HELP   1025

// Specify the telecommand diagnostics oversampling dump display window retrieve dialog related limits
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_MINIMUMINTERVAL   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_MAXIMUMINTERVAL   MINUTESPERWEEK
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEDIALOG_DEFAULTINTERVAL   5

class CTCDiagnosticsOversamplingDumpRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpRetrieveDialog)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpRetrieveDialog)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszTitle);

	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetSpeed(UINT &nSpeed) CONST;
	BOOL GetInterval(CTimeSpan &tInterval) CONST;
	BOOL GetStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetStopTime(CTimeKey &tTimeKey) CONST;

	class CTCDiagnosticsOversamplingDumpOpenDialog *GetParentDialog() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpRetrieveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRetrieveByTime();
	afx_msg void OnRetrieveByEnd();
	afx_msg void OnRetrieveAutomatic();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnRetrieveManual();
	afx_msg void OnRetrieveInterval();
	afx_msg void OnSpinchangeRetrieveStartTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpOpenDialog dialog

#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DETAILS   1001
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY_STATIC   1002
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DISPLAY   1003
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_SETTINGS   1004
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE   1005
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_TYPE_NORMAL   1006
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_REMOVE   1007
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE   1008
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_REALTIME   1009
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_MODE_HISTORY   1010
#define IDC_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_HELP   1011

class CTCDiagnosticsOversamplingDumpOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpOpenDialog)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	UINT  m_nLayoutSamples;
	BOOL  m_bLayoutBadData;
	BOOL  m_bLayoutToolTips;
	BOOL  m_bLayoutInvalidData;
	LOGFONT  m_fntLayoutTitle[2];
	LOGFONT  m_fntLayoutItems[2];
	LOGFONT  m_fntLayoutValues;
	CString  m_szRetrieveFileName;
	COLORREF  m_nLayoutBackgroundColor[2];
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeSpan  m_tRetrieveInterval;
	CTCDiagnosticsOversamplingDumpLayout  m_cLayout;
	CTCDiagnosticsOversamplingDumpLayouts  m_pLayouts;
	CTCDiagnosticsOversamplingDumpPrintJobs  m_pPrintJobs;
private:
	CTCDiagnosticsOversamplingDumpSettingsDialog  m_dlgSettings;
	CTCDiagnosticsOversamplingDumpRetrieveDialog  m_dlgRetrievals;

	// Dialog Data
	//{{AFX_DATA(CTCDiagnosticsOversamplingDumpOpenDialog)
	enum { IDD = IDD_TCDIAGNOSTICSOVERSAMPLINGDUMP_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayoutListTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutListItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutListValuesFont(UINT nPane, LPLOGFONT pValuesFont) CONST;
	BOOL GetLayoutGridBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;
	BOOL GetLayoutSampleLimit(UINT &nLimit) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	BOOL GetRetrieveStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveStopTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCDiagnosticsOversamplingDumpWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpOpenDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnSelchangeTitle();
	afx_msg void OnTypeNormal();
	afx_msg void OnRealtimeMode();
	afx_msg void OnHistoryMode();
	afx_msg void OnRemove();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRetrieveThread thread

// Specify the telecommand diagnostics oversampling dump display retrieve thread action codes
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_STOP   0
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_AUTOBACKWARD   2
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALFORWARD   3
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_MANUALBACKWARD   4
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_PSEUDOREALTIME   5
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_TYPES   6

class CTCDiagnosticsOversamplingDumpRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpRetrieveThread)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpRetrieveThread();

	// Attributes
private:
	UINT  m_nMode;
	UINT  m_nSpeed;
	CTimeSpan  m_tInterval;
	CTimeKey  m_tStartTime;
	CTimeKey  m_tStopTime;
	CString  m_szFileName;
private:
	LONG  *m_pbFlag;
	HANDLE  m_bInit[2];
	HANDLE  m_hAction[TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTMProcessEngine  m_cTMProcessEngine;
	CTMEnvironment  m_cTMEnvironment;

	// Operations
public:
	BOOL Start(class CTCDiagnosticsOversamplingDumpWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime);
	BOOL Stop();

private:
	VOID StartRetrieving();
	VOID StopRetrieving();

	UINT GetRetrieveMode() CONST;
	UINT GetRetrieveSpeed() CONST;
	CTimeSpan GetRetrieveInterval() CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	CTimeKey GetRetrieveStopTime() CONST;
	CString GetRetrieveFileName() CONST;

	VOID BeginWaitCursor(BOOL bForced = FALSE);
	VOID EndWaitCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpToolBar window

class CTCDiagnosticsOversamplingDumpToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpToolBar)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpStatusBar window

class CTCDiagnosticsOversamplingDumpStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpStatusBar)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTCDiagnosticsOversamplingDumpWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpToolTip window

class CTCDiagnosticsOversamplingDumpToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpToolTip)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpDocument

class CTCDiagnosticsOversamplingDumpDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCDiagnosticsOversamplingDumpDocument)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpDocument();
	virtual ~CTCDiagnosticsOversamplingDumpDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersTextView window

// Specify the telecommand diagnostics oversampling dump parameters view alert symbol identifiers
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOLS   3
// Specify the telecommand diagnostics oversampling dump parameters view visual aspect related identifiers
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COLUMNTRANSPARENCY   0x30

class CTCDiagnosticsOversamplingDumpParametersTextView : public CTextView
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersTextView)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpParametersTextView();

	// Attributes
private:
	CTCDiagnosticsOversamplingDumpLayout  m_cLayout;
	COLORREF  m_nLayoutBackgroundColor[3];
	CFont  m_cLayoutFont;
	BOOL  m_bInvalidDataMode;
	BOOL  m_bBadDataMode;
	BOOL  m_bToolTipMode;
private:
	CTCDiagnosticsOversamplingDumpSamples  m_pSamples;
	CTimeTag  m_tSampleTime;
	UINT  m_nSampleLimit;
private:
	CSize  m_sizeAlertSymbols;
	CImage  *m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERSTEXTVIEW_COMMANDALERTSYMBOLS];
	CTCDiagnosticsOversamplingDumpToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetValuesFont(CFont *pFont = NULL);
	BOOL SetValuesFont(CONST LOGFONT *plfFont);
	BOOL GetValuesFont(CFont *pFont) CONST;
	BOOL GetValuesFont(LOGFONT *plfFont) CONST;
	BOOL SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor);
	BOOL GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;

	BOOL SetSampleLimit(UINT nLimit = 0);
	BOOL GetSampleLimit(UINT &nLimit) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL SetCurSample(INT nIndex);
	INT GetCurSample() CONST;

	INT GetSampleCount() CONST;

	BOOL GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, LOGFONT *pValuesFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	class CTCDiagnosticsOversamplingDumpParametersView *GetParent() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CONST CStringArray &szParameters, CStringArray &szColumns, CUIntArray &nFormats) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;

	CString TranslateColumnName(LPCTSTR pszColumn) CONST;
	CString TranslateParameterBlock(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CTCDiagnosticsOversamplingDumpSamples &pSamples, CTextViewAttribute *pAttribute) CONST;
	CString TranslateParameterBlock(INT nIndex, INT nCount, CONST CTCDiagnosticsOversamplingDumpSample *pSample, CTextViewAttribute *pAttribute) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnWidth(UINT nColumn, LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CONST CStringArray &szColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;

	UINT FindParameterSample(INT nRow, INT nColumn, CTCDiagnosticsOversamplingDumpSample *pSample, COversamplingParameter *pParameter) CONST;

	CString ConstructToolTipTitle(CONST CTCDiagnosticsOversamplingDumpSample *pSample, CONST COversamplingParameter *pParameter, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCDiagnosticsOversamplingDumpSample *pSample, CONST COversamplingParameter *pParameter, UINT nTip) CONST;

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpParametersTextView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RefreshContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
	virtual BOOL DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem);
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpParametersTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpParametersView view

class CTCDiagnosticsOversamplingDumpParametersView : public CView
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpParametersView)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpParametersView();
	~CTCDiagnosticsOversamplingDumpParametersView();

	// Attributes
private:
	CTCDiagnosticsOversamplingDumpParametersTextView  *m_pwndList;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetValuesFont(CFont *pFont);
	BOOL SetValuesFont(CONST LOGFONT *plfFont);
	BOOL GetValuesFont(CFont *pFont) CONST;
	BOOL GetValuesFont(LOGFONT *plfFont) CONST;
	BOOL SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor);
	BOOL GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;

	BOOL SetSampleLimit(UINT nLimit = 0);
	BOOL GetSampleLimit(UINT &nLimit) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL SetCurSample(INT nIndex);
	INT GetCurSample() CONST;

	INT GetSampleCount() CONST;

	BOOL GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, LOGFONT *pValuesFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCDiagnosticsOversamplingDumpView *GetParent() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpParametersView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpParametersView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRawDataTextView window

// Specify the telecommand diagnostics oversampling dump raw data view alert symbol identifiers
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOLS   3
// Specify the telecommand diagnostics oversampling dump raw data view visual aspect related identifiers
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COLUMNTRANSPARENCY   0x30

class CTCDiagnosticsOversamplingDumpRawDataTextView : public CTextView
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpRawDataTextView)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpRawDataTextView();

	// Attributes
private:
	CTCDiagnosticsOversamplingDumpLayout  m_cLayout;
	COLORREF  m_nLayoutBackgroundColor[3];
	BOOL  m_bInvalidDataMode;
	BOOL  m_bBadDataMode;
	BOOL  m_bToolTipMode;
private:
	CTCDiagnosticsOversamplingDumpSamples  m_pSamples;
	CTimeTag  m_tSampleTime;
	UINT  m_nSampleLimit;
private:
	CSize  m_sizeAlertSymbols;
	CImage  *m_pAlertSymbols[TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATATEXTVIEW_COMMANDALERTSYMBOLS];
	CTCDiagnosticsOversamplingDumpToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor);
	BOOL GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;

	BOOL SetSampleLimit(UINT nLimit = 0);
	BOOL GetSampleLimit(UINT &nLimit) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL SetCurSample(INT nIndex);
	INT GetCurSample() CONST;

	INT GetSampleCount() CONST;

	BOOL GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	class CTCDiagnosticsOversamplingDumpRawDataView *GetParent() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;

	CString TranslateRawDataBlock(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CTCDiagnosticsOversamplingDumpSamples &pSamples, CTextViewAttribute *pAttribute) CONST;
	CString TranslateParameterBlock(INT nIndex, INT nCount, CONST CTCDiagnosticsOversamplingDumpSample *pSample, CTextViewAttribute *pAttribute) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;

	UINT FindParameterSample(INT nRow, INT nColumn, CTCDiagnosticsOversamplingDumpSample *pSample) CONST;

	CString ConstructToolTipTitle(CONST CTCDiagnosticsOversamplingDumpSample *pSample, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCDiagnosticsOversamplingDumpSample *pSample, UINT nTip) CONST;

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpRawDataTextView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RefreshContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
	virtual BOOL DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem);
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpRawDataTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpRawDataView view

class CTCDiagnosticsOversamplingDumpRawDataView : public CView
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpRawDataView)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpRawDataView();
	~CTCDiagnosticsOversamplingDumpRawDataView();

	// Attributes
private:
	CSize  m_sizeTrackLayout;
	CTCDiagnosticsOversamplingDumpRawDataTextView  *m_pwndList;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor);
	BOOL GetBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;

	BOOL SetSampleLimit(UINT nLimit = 0);
	BOOL GetSampleLimit(UINT &nLimit) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL SetCurSample(INT nIndex);
	INT GetCurSample() CONST;

	INT GetSampleCount() CONST;

	BOOL GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCDiagnosticsOversamplingDumpView *GetParent() CONST;
	class CTCDiagnosticsOversamplingDumpWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpRawDataView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpRawDataView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpView window

class CTCDiagnosticsOversamplingDumpView : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCDiagnosticsOversamplingDumpView)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpView();

	// Attributes
private:
	CTCDiagnosticsOversamplingDumpLayout  m_cLayout;
	CUIntArray  m_nLayoutColumns[2];
	CUIntArray  m_nLayoutColumnWidths[2];
	COLORREF  m_nLayoutBackgroundColor[2];
	LOGFONT  m_lfLayoutFont[2][3];
	CSize  m_sizeLayoutPane[2];
	BOOL  m_bInvalidData;
	BOOL  m_bBadData;
	BOOL  m_bToolTips;
private:
	INT  m_nSampleLimit;
private:
	BOOL  m_bTracking;
private:
	CTCDiagnosticsOversamplingDumpParametersView  *m_pParametersView;
	CTCDiagnosticsOversamplingDumpRawDataView  *m_pRawDataView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nParametersPaneColumns, CONST CUIntArray &nParametersPaneWidths, CONST SIZE &sizeParametersPane, CONST CUIntArray &nRawDataPaneColumns, CONST CUIntArray &nRawDataPaneWidths, CONST SIZE &sizeRawDataPane);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nParametersPaneColumns, CUIntArray &nParametersPaneWidths, CSize &sizeParametersPane, CUIntArray &nRawDataPaneColumns, CUIntArray &nRawDataPaneWidths, CSize &sizeRawDataPane) CONST;

	BOOL SetListTitleFont(UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListValuesFont(UINT nPane, CFont *pFont);
	BOOL SetListValuesFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListValuesFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListValuesFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor);
	BOOL GetGridBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;

	BOOL SetSampleLimit(UINT nLimit = 0);
	BOOL GetSampleLimit(UINT &nLimit) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL SetCurSample(UINT nPane, INT nIndex);
	INT GetCurSample(UINT nPane) CONST;

	INT GetSampleCount(UINT nPane) CONST;

	BOOL GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CStringArray &szParametersColumns, CStringArray &szParametersContents, CTextViewAttributes &pParametersAttributes, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pParametersValuesFont, CStringArray &szRawDataColumns, CStringArray &szRawDataContents, CTextViewAttributes &pRawDataAttributes, LOGFONT *pRawDataTitleFont, LOGFONT *pRawDataItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	CTCDiagnosticsOversamplingDumpParametersView *GetParametersView() CONST;
	CTCDiagnosticsOversamplingDumpRawDataView *GetRawDataView() CONST;

	class CTCDiagnosticsOversamplingDumpWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpView)
public:
	virtual BOOL SetLayoutInfo(INT nParametersPaneIndex, INT nParametersPaneCount, CONST SCROLLINFO *pParametersPaneHorzScrollInfo, CONST SCROLLINFO *pParametersPaneVertScrollInfo, INT nRawDataPaneIndex, INT nRawDataPaneCount, CONST SCROLLINFO *pRawDataPaneHorzScrollInfo, CONST SCROLLINFO *pRawDataPaneVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nParametersPaneIndex, INT &nParametersPaneCount, SCROLLINFO *pParametersPaneHorzScrollInfo, SCROLLINFO *pParametersPaneVertScrollInfo, INT &nRawDataPaneIndex, INT &nRawDataPaneCount, SCROLLINFO *pRawDataPaneHorzScrollInfo, SCROLLINFO *pRawDataPaneVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
	virtual VOID RecalcLayout(BOOL bRecalc);
protected:
	virtual void StartTracking(int ht);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCDiagnosticsOversamplingDumpWnd frame

// Specify the telecommand diagnostics oversampling dump display types
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_GLOBAL   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_TYPE_NORMAL   2
// Specify the telecommand diagnostics oversampling dump display panes
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_PARAMETERS   (1<<0)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PANE_RAWDATA   (1<<1)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PANES   2
// Specify the telecommand diagnostics oversampling dump display title items
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER   (1<<0)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME   (1<<1)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE   (1<<2)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT   (1<<3)
#ifndef RC_INVOKED
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEMS_DEFAULT   (TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_NUMBER | TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_TIME | TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_VALUE | TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEM_UNIT)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEMS_ALL   TCDIAGNOSTICSOVERSAMPLINGDUMPPARAMETERS_TITLEITEMS_DEFAULT
#endif
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER   (1<<0)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME   (1<<1)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS   (1<<2)
#ifndef RC_INVOKED
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEMS_DEFAULT   (TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_NUMBER | TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_TIME | TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEM_CONTENTS)
#define TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEMS_ALL   TCDIAGNOSTICSOVERSAMPLINGDUMPRAWDATA_TITLEITEMS_DEFAULT
#endif
// Specify the telecommand diagnostics oversampling dump display retrieval modes
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_EXACTTIME   (1<<0)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYTIME   (1<<1)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPBYEND   (1<<2)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_STOPPED   (1<<3)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_RELATIVE   (1<<4)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOFORWARD   (1<<5)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_AUTOBACKWARD   (1<<6)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALFORWARD   (1<<7)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_MANUALBACKWARD   (1<<8)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_RETRIEVE_PSEUDOREALTIME   (1<<9)
// Specify the telecommand diagnostics oversampling dump display print modes
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_PARAMETERVALUES   (1<<0)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_RAWDATA   (1<<1)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_ITEMRANGE   (1<<2)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_TIMERANGE   (1<<3)
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINT_CLEARCOMMENTS   (1<<4)
// Specify the telecommand diagnostics oversampling dump display print fonts
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_TITLE   0
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_SUBTITLE   1
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_DETAILS   2
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_COMMENTS   3
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSTITLE   4
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMSTITLE   5
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTITEMS   6
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_PARAMETERSLISTVALUES   7
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATATITLE   8
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMSTITLE   9
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTITEMS   10
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_RAWDATALISTVALUES   11
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_FOOTER   12
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_NOTICE   13
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONT_LOGO   14
#define TCDIAGNOSTICSOVERSAMPLINGDUMP_PRINTFONTS   15
// Specify the telecommand diagnostics oversampling dump display statusbar pane identifiers
#define ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_TCDIAGNOSTICSOVERSAMPLINGDUMP_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CTCDiagnosticsOversamplingDumpWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTCDiagnosticsOversamplingDumpWnd)

	// Construction
public:
	CTCDiagnosticsOversamplingDumpWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nIndex[2];
		INT  nCount[2];
		SIZE  sizePanes[2];
		LOGFONT  sFont[2][3];
		COLORREF  nColor[2];
		SCROLLINFO  sScrollInfo[2][2];
	} DATA, *PDATA, *LPDATA;
private:
	CTCDiagnosticsOversamplingDumpToolBar  m_wndToolBar;
	CTCDiagnosticsOversamplingDumpStatusBar  m_wndStatusBar;
	CTCDiagnosticsOversamplingDumpView  m_wndView;
private:
	CTCDiagnosticsOversamplingDumpOpenDialog  m_dlgOpen;
	CTCDiagnosticsOversamplingDumpSettingsDialog  m_dlgSettings;
	CTCDiagnosticsOversamplingDumpRetrieveDialog  m_dlgRetrievals;
	CTCDiagnosticsOversamplingDumpParametersDialog  m_dlgParameters;
private:
	CTCDiagnosticsOversamplingDumpRetrieveThread  m_cRetrieveThread;
private:
	CTCDiagnosticsOversamplingDumpPrintJobs  m_pPrintJobs;
private:
	LONG  m_bRetrieveFlag;
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	CEvent  m_cRetrieveStop;
	CEvent  m_cRetrieveAutoForward;
	CEvent  m_cRetrieveAutoBackward;
	CEvent  m_cRetrieveManualForward;
	CEvent  m_cRetrieveManualBackward;
	CEvent  m_cRetrievePseudoRealtime;
	CTimeSpan  m_tRetrieveInterval;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CString  m_szRetrieveFileName;
private:
	CString  m_szTMUnit;
	CTimeTag  m_tTMUnit;
	UINT  m_nTMUnit;
	WORD  m_wTMUnit;

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout);
	BOOL SetLayout(CONST CTCDiagnosticsOversamplingDumpLayout &cLayout, CONST CUIntArray &nParametersPaneColumns, CONST CUIntArray &nParametersPaneWidths, CONST SIZE &sizeParametersPane, CONST CUIntArray &nRawDataPaneColumns, CONST CUIntArray &nRawDataPaneWidths, CONST SIZE &sizeRawDataPane);
	BOOL SetLayout(CONST CByteArray &nLayoutData, CONST CUIntArray &nParametersPaneColumns, CONST CUIntArray &nParametersPaneWidths, CONST SIZE &sizeParametersPane, CONST CUIntArray &nRawDataPaneColumns, CONST CUIntArray &nRawDataPaneWidths, CONST SIZE &sizeRawDataPane);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout) CONST;
	BOOL GetLayout(CTCDiagnosticsOversamplingDumpLayout &cLayout, CUIntArray &nParametersPaneColumns, CUIntArray &nParametersPaneWidths, CSize &sizeParametersPane, CUIntArray &nRawDataPaneColumns, CUIntArray &nRawDataPaneWidths, CSize &sizeRawDataPane) CONST;
	BOOL GetLayout(CByteArray &nLayoutData, CUIntArray &nParametersPaneColumns, CUIntArray &nParametersPaneWidths, CSize &sizeParametersPane, CUIntArray &nRawDataPaneColumns, CUIntArray &nRawDataPaneWidths, CSize &sizeRawDataPane) CONST;

	BOOL SetListTitleFont(UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListValuesFont(UINT nPane, CFont *pFont);
	BOOL SetListValuesFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListValuesFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListValuesFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColors(COLORREF nNumbersColor, COLORREF nValuesColor);
	BOOL GetGridBackgroundColors(COLORREF &nNumbersColor, COLORREF &nValuesColor) CONST;

	BOOL SetSampleLimit(UINT nLimit = 0);
	BOOL GetSampleLimit(UINT &nLimit) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL StopMonitoring();

	BOOL SetCurSample(UINT nPane, INT nIndex);
	INT GetCurSample(UINT nPane) CONST;

	INT GetSampleCount(UINT nPane) CONST;

	BOOL ProcessRealtimeData();

	BOOL StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL StartRetrieveData();
	LONG IsRetrievingData() CONST;
	BOOL RetrieveMoreData(UINT nAction);
	BOOL StopRetrieveData();
	BOOL SetRetrieveMode(UINT nMode = 0);
	BOOL GetRetrieveMode(UINT &nMode) CONST;
	UINT GetRetrieveMode() CONST;
	BOOL SetRetrieveSpeed(UINT nSpeed = 0);
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	UINT GetRetrieveSpeed() CONST;
	BOOL SetRetrieveInterval(CONST CTimeSpan &tInterval = 0);
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	CTimeSpan GetRetrieveInterval() CONST;
	BOOL SetRetrieveStartTime(CONST CTimeKey &tStartTime = 0);
	BOOL GetRetrieveStartTime(CTimeKey &tStartTime) CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	BOOL SetRetrieveStopTime(CONST CTimeKey &tStopTime = 0);
	BOOL GetRetrieveStopTime(CTimeKey &tStopTime) CONST;
	CTimeKey GetRetrieveStopTime() CONST;
	BOOL SetRetrieveFileName(LPCTSTR pszFileName);
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	CString GetRetrieveFileName() CONST;

	VOID ShowParameterInfo(LPCTSTR pszTag);

	BOOL SetPrintJobs(CONST CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTCDiagnosticsOversamplingDumpPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CTCDiagnosticsOversamplingDumpWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

	VOID SetUpdateInfo();
	VOID SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality);
	BOOL GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST;

	CTCDiagnosticsOversamplingDumpParametersView *GetParametersView() CONST;
	CTCDiagnosticsOversamplingDumpRawDataView *GetRawDataView() CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateModePane();
	VOID UpdateTypePane();

	VOID UpdateData();

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szParametersColumns, CStringArray &szParametersContents, CTextViewAttributes &pParametersAttributes, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pParametersValuesFont, CStringArray &szRawDataColumns, CStringArray &szRawDataContents, CTextViewAttributes &pRawDataAttributes, LOGFONT *pRawDataTitleFont, LOGFONT *pRawDataItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szParametersColumns, CONST CStringArray &szParametersContents, CONST CTextViewAttributes &pParametersAttributes, CONST LOGFONT *pParametersTitleFont, CONST LOGFONT *pParametersItemsFont, CONST LOGFONT *pParametersValuesFont, CONST CStringArray &szRawDataColumns, CONST CStringArray &szRawDataContents, CONST CTextViewAttributes &pRawDataAttributes, CONST LOGFONT *pRawDataTitleFont, CONST LOGFONT *pRawDataItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, LPCTSTR pszTitle, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszLayout, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszLayout) CONST;
	CString GetPrintDocDetails(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocComments(CONST CTCDiagnosticsOversamplingDumpPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocListTitle(LPCTSTR pszTitle) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST LOGFONT *pValuesFont, CFont &cTitleFont, CFont &cItemsFont, CFont &cValuesFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CFont *pValuesFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont, CFont *pValuesFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(CONST SIZE &sizeParametersPane, CONST SIZE &sizeRawDataPane, CONST LOGFONT *pParametersPaneTitleFont, CONST LOGFONT *pParametersPaneItemsFont, CONST LOGFONT *pParametersPaneValuesFont, CONST LOGFONT *pRawDataPaneTitleFont, CONST LOGFONT *pRawDataPaneItemsFont, CONST LOGFONT *pRawDataPaneValuesFont, COLORREF nNumbersBackgroundColor, COLORREF nValuesBackgroundColor, INT nParametersPaneIndex, INT nParametersPaneCount, CONST SCROLLINFO *pParametersPaneHorzScrollInfo, CONST SCROLLINFO *pParametersPaneVertScrollInfo, INT nRawDataPaneIndex, INT nRawDataPaneCount, CONST SCROLLINFO *pRawDataPaneHorzScrollInfo, CONST SCROLLINFO *pRawDataPaneVertScrollInfo);
	BOOL GetLayoutInfo(CSize &sizeParametersPane, CSize &sizeRawDataPane, LOGFONT *pParametersPaneTitleFont, LOGFONT *pParametersPaneItemsFont, LOGFONT *pParametersPaneValuesFont, LOGFONT *pRawDataPaneTitleFont, LOGFONT *pRawDataPaneItemsFont, LOGFONT *pRawDataPaneValuesFont, COLORREF &nNumbersBackgroundColor, COLORREF &nValuesBackgroundColor, INT &nParametersPaneIndex, INT &nParametersPaneCount, SCROLLINFO *pParametersPaneHorzScrollInfo, SCROLLINFO *pParametersPaneVertScrollInfo, INT &nRawDataPaneIndex, INT &nRawDataPaneCount, SCROLLINFO *pRawDataPaneHorzScrollInfo, SCROLLINFO *pRawDataPaneVertScrollInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCDiagnosticsOversamplingDumpWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Initialize(BOOL bFlag);
	virtual BOOL Initialize(CTMEnvironment *pTMEnvironment);
	virtual BOOL Initialize(CString &szTag, CTimeTag &tTag);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags = 0);
	virtual VOID Reset(CTMEnvironment *pTMEnvironment = NULL);
	virtual BOOL Stop();
public:
	virtual BOOL SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo);
	virtual BOOL LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo);
	virtual BOOL SetLayoutInfo(LPCVOID pData);
	virtual INT GetLayoutInfo(LPVOID *pData = NULL) CONST;
	virtual BOOL QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST;
	virtual BOOL QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST;
	virtual VOID UpdateBars();
public:
	virtual BOOL Print(PRINTDLG *pPrintInfo = NULL);
	virtual BOOL CanPrint() CONST;
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseOpenDialog(UINT nCode);
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCDiagnosticsOversamplingDumpWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnParameters();
	afx_msg void OnClearAll();
	afx_msg void OnRetrievals();
	afx_msg void OnRetrieveStop();
	afx_msg void OnRetrieveAutoForward();
	afx_msg void OnRetrieveAutoBackward();
	afx_msg void OnRetrieveManualForward();
	afx_msg void OnRetrieveManualBackward();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnPrint();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateParameters(CCmdUI *pCmdUI);
	afx_msg void OnUpdateClearAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievals(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveManualForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTypePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TCDIAGNOSTICS_H__
