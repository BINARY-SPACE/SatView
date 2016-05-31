// TCSTACKS.H : Telecommand Stacks Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand stacks related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2007/04/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TCSTACKS_H__
#define __TCSTACKS_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTCSavedStack

class CTCSavedStack : public CTCItems
{
	// Construction
public:
	CTCSavedStack();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbItems;
		INT  cbAuthor;
		INT  cbDatabase;
		INT  cbSpacecraft;
		INT  cbDescription;
		INT  cbWorkstation;
		TIMEKEY  tCreationDate;
		TIMEKEY  tDatabaseVersion[2];
		BOOL  bValidated;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szAuthor;
	CString  m_szDatabase;
	CString  m_szSpacecraft;
	CString  m_szDescription;
	CString  m_szWorkstation;
	CTimeKey  m_tCreationDate;
	CTimeKey  m_tDatabaseVersion[2];
private:
	BOOL  m_bValidated;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetCreationDate(CONST CTimeKey &tDate);
	CTimeKey GetCreationDate() CONST;
	VOID SetAuthor(LPCTSTR pszAuthor);
	CString GetAuthor() CONST;
	VOID SetOriginWorkstation(LPCTSTR pszWorkstation);
	CString GetOriginWorkstation() CONST;
	VOID SetSpacecraft(LPCTSTR pszSpacecraft);
	CString GetSpacecraft() CONST;
	VOID SetDatabase(LPCTSTR pszDatabase);
	CString GetDatabase() CONST;
	VOID SetDatabaseVersion(CONST CTimeKey &tCreationTime, CONST CTimeKey &tUpdateTime);
	BOOL GetDatabaseVersion(CTimeKey &tCreationTime, CTimeKey &tUpdateTime) CONST;

	VOID Validate(BOOL bValidate = TRUE);
	BOOL IsValidated() CONST;

	BOOL Copy(CONST CTCSavedStack *pStack);
	BOOL Compare(CONST CTCSavedStack *pStack) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCSavedStacks

class CTCSavedStacks : public CPtrArray
{
	// Construction
public:
	CTCSavedStacks();
	~CTCSavedStacks();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCSavedStack *pStack);

	INT Find(LPCTSTR pszName) CONST;

	CTCSavedStack *GetAt(INT nIndex) CONST;
	CTCSavedStack *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCSavedStacks *pStacks);
	BOOL Compare(CONST CTCSavedStacks *pStacks) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchNumberDialog dialog

#define IDC_TCSTACK_SEARCHNUMBER_NUMBER_STATIC   1001
#define IDC_TCSTACK_SEARCHNUMBER_NUMBER   1002
#define IDC_TCSTACK_SEARCHNUMBER_GOTO   1003
#define IDC_TCSTACK_SEARCHNUMBER_COMMENT_STATIC   1004
#define IDC_TCSTACK_SEARCHNUMBER_COMMENT   1005
#define IDC_TCSTACK_SEARCHNUMBER_CLOSE   1006
#define IDC_TCSTACK_SEARCHNUMBER_HELP   1007

class CTCStackSearchNumberDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchNumberDialog)

	// Construction
public:
	CTCStackSearchNumberDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchNumberDialog)
	enum { IDD = IDD_TCSTACK_SEARCHNUMBER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchNumberDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchNumberDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchNameDialog dialog

#define IDC_TCSTACK_SEARCHNAME_NAME_STATIC   1001
#define IDC_TCSTACK_SEARCHNAME_NAME   1002
#define IDC_TCSTACK_SEARCHNAME_DIRECTION   1003
#define IDC_TCSTACK_SEARCHNAME_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHNAME_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHNAME_ALL   1006
#define IDC_TCSTACK_SEARCHNAME_FIND   1007
#define IDC_TCSTACK_SEARCHNAME_HELP   1008

class CTCStackSearchNameDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchNameDialog)

	// Construction
public:
	CTCStackSearchNameDialog();   // standard constructor

	// Attributes
protected:
	CStringArray  m_szNames;

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchNameDialog)
	enum { IDD = IDD_TCSTACK_SEARCHNAME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchNameDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchNameDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	afx_msg void OnEditchangeName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchDescriptionDialog dialog

#define IDC_TCSTACK_SEARCHDESCRIPTION_TEXT_STATIC   1001
#define IDC_TCSTACK_SEARCHDESCRIPTION_TEXT   1002
#define IDC_TCSTACK_SEARCHDESCRIPTION_DIRECTION   1003
#define IDC_TCSTACK_SEARCHDESCRIPTION_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHDESCRIPTION_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHDESCRIPTION_ALL   1006
#define IDC_TCSTACK_SEARCHDESCRIPTION_CASE   1007
#define IDC_TCSTACK_SEARCHDESCRIPTION_WORD   1008
#define IDC_TCSTACK_SEARCHDESCRIPTION_FIND   1009
#define IDC_TCSTACK_SEARCHDESCRIPTION_HELP   1010

class CTCStackSearchDescriptionDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchDescriptionDialog)

	// Construction
public:
	CTCStackSearchDescriptionDialog();   // standard constructor

	// Attributes
protected:
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchDescriptionDialog)
	enum { IDD = IDD_TCSTACK_SEARCHDESCRIPTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchDescriptionDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchDescriptionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDescription();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchCategoryDialog dialog

#define IDC_TCSTACK_SEARCHCATEGORY_CATEGORY_STATIC   1001
#define IDC_TCSTACK_SEARCHCATEGORY_CATEGORY   1002
#define IDC_TCSTACK_SEARCHCATEGORY_DIRECTION   1003
#define IDC_TCSTACK_SEARCHCATEGORY_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHCATEGORY_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHCATEGORY_ALL   1006
#define IDC_TCSTACK_SEARCHCATEGORY_FIND   1007
#define IDC_TCSTACK_SEARCHCATEGORY_HELP   1008

class CTCStackSearchCategoryDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchCategoryDialog)

	// Construction
public:
	CTCStackSearchCategoryDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchCategoryDialog)
	enum { IDD = IDD_TCSTACK_SEARCHCATEGORY_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumCategories();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchCategoryDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchCategoryDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchSubSystemDialog dialog

#define IDC_TCSTACK_SEARCHSUBSYSTEM_NAME_STATIC   1001
#define IDC_TCSTACK_SEARCHSUBSYSTEM_NAME   1002
#define IDC_TCSTACK_SEARCHSUBSYSTEM_DIRECTION   1003
#define IDC_TCSTACK_SEARCHSUBSYSTEM_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHSUBSYSTEM_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHSUBSYSTEM_ALL   1006
#define IDC_TCSTACK_SEARCHSUBSYSTEM_CASE   1007
#define IDC_TCSTACK_SEARCHSUBSYSTEM_FIND   1008
#define IDC_TCSTACK_SEARCHSUBSYSTEM_HELP   1009

class CTCStackSearchSubSystemDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchSubSystemDialog)

	// Construction
public:
	CTCStackSearchSubSystemDialog();   // standard constructor

	// Attributes
protected:
	CStringArray  m_szSubSystems;

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchSubSystemDialog)
	enum { IDD = IDD_TCSTACK_SEARCHSUBSYSTEM_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchSubSystemDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchSubSystemDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSubSystem();
	afx_msg void OnEditchangeSubSystem();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchArgumentsDialog dialog

#define IDC_TCSTACK_SEARCHARGUMENTS_ARGUMENT_STATIC   1001
#define IDC_TCSTACK_SEARCHARGUMENTS_ARGUMENT   1002
#define IDC_TCSTACK_SEARCHARGUMENTS_DIRECTION   1003
#define IDC_TCSTACK_SEARCHARGUMENTS_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHARGUMENTS_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHARGUMENTS_ALL   1006
#define IDC_TCSTACK_SEARCHARGUMENTS_FIND   1007
#define IDC_TCSTACK_SEARCHARGUMENTS_HELP   1008

class CTCStackSearchArgumentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchArgumentsDialog)

	// Construction
public:
	CTCStackSearchArgumentsDialog();   // standard constructor

	// Attributes
protected:
	CStringArray  m_szArguments;

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchArgumentsDialog)
	enum { IDD = IDD_TCSTACK_SEARCHARGUMENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchArgumentsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchArgumentsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeArgument();
	afx_msg void OnEditchangeArgument();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchFlagsDialog dialog

#define IDC_TCSTACK_SEARCHFLAGS_FLAG_STATIC   1001
#define IDC_TCSTACK_SEARCHFLAGS_FLAG_INTERLOCKING   1002
#define IDC_TCSTACK_SEARCHFLAGS_FLAG_INTERLOCKED   1003
#define IDC_TCSTACK_SEARCHFLAGS_FLAG_GROUPED   1004
#define IDC_TCSTACK_SEARCHFLAGS_FLAG_BLOCKED   1005
#define IDC_TCSTACK_SEARCHFLAGS_DIRECTION   1006
#define IDC_TCSTACK_SEARCHFLAGS_DIRECTION_UP   1007
#define IDC_TCSTACK_SEARCHFLAGS_DIRECTION_DOWN   1008
#define IDC_TCSTACK_SEARCHFLAGS_ALL   1009
#define IDC_TCSTACK_SEARCHFLAGS_FIND   1010
#define IDC_TCSTACK_SEARCHFLAGS_HELP   1011

class CTCStackSearchFlagsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchFlagsDialog)

	// Construction
public:
	CTCStackSearchFlagsDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchFlagsDialog)
	enum { IDD = IDD_TCSTACK_SEARCHFLAGS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchFlagsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchFlagsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnInterlockingFlag();
	afx_msg void OnInterlockedFlag();
	afx_msg void OnGroupedFlag();
	afx_msg void OnBlockedFlag();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchTCPacketDialog dialog

#define IDC_TCSTACK_SEARCHTCPACKET_TAG_STATIC   1001
#define IDC_TCSTACK_SEARCHTCPACKET_TAG   1002
#define IDC_TCSTACK_SEARCHTCPACKET_DIRECTION   1003
#define IDC_TCSTACK_SEARCHTCPACKET_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHTCPACKET_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHTCPACKET_ALL   1006
#define IDC_TCSTACK_SEARCHTCPACKET_FIND   1007
#define IDC_TCSTACK_SEARCHTCPACKET_HELP   1008

class CTCStackSearchTCPacketDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchTCPacketDialog)

	// Construction
public:
	CTCStackSearchTCPacketDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchTCPacketDialog)
	enum { IDD = IDD_TCSTACK_SEARCHTCPACKET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumTCPackets();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchTCPacketDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchTCPacketDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchDispatchTimeDialog dialog

#define IDC_TCSTACK_SEARCHDISPATCHTIME_TIME_STATIC   1001
#define IDC_TCSTACK_SEARCHDISPATCHTIME_TIME   1002
#define IDC_TCSTACK_SEARCHDISPATCHTIME_DIRECTION   1003
#define IDC_TCSTACK_SEARCHDISPATCHTIME_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHDISPATCHTIME_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHDISPATCHTIME_ALL   1006
#define IDC_TCSTACK_SEARCHDISPATCHTIME_MATCH   1007
#define IDC_TCSTACK_SEARCHDISPATCHTIME_INTERVAL   1008
#define IDC_TCSTACK_SEARCHDISPATCHTIME_INTERVAL_TIME   1009
#define IDC_TCSTACK_SEARCHDISPATCHTIME_INTERVAL_STATIC   1010
#define IDC_TCSTACK_SEARCHDISPATCHTIME_FIND   1011
#define IDC_TCSTACK_SEARCHDISPATCHTIME_HELP   1012

// Specify the telecommand stack search dispatch time dialog related identifiers
#define TCSTACKSEARCHDISPATCHTIME_MINIMUMINTERVAL   1
#define TCSTACKSEARCHDISPATCHTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCSTACKSEARCHDISPATCHTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCStackSearchDispatchTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchDispatchTimeDialog)

	// Construction
public:
	CTCStackSearchDispatchTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchDispatchTimeDialog)
	enum { IDD = IDD_TCSTACK_SEARCHDISPATCHTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchDispatchTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchDispatchTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchReleaseTimeDialog dialog

#define IDC_TCSTACK_SEARCHRELEASETIME_TIME_STATIC   1001
#define IDC_TCSTACK_SEARCHRELEASETIME_TIME   1002
#define IDC_TCSTACK_SEARCHRELEASETIME_DIRECTION   1003
#define IDC_TCSTACK_SEARCHRELEASETIME_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHRELEASETIME_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHRELEASETIME_ALL   1006
#define IDC_TCSTACK_SEARCHRELEASETIME_MATCH   1007
#define IDC_TCSTACK_SEARCHRELEASETIME_INTERVAL   1008
#define IDC_TCSTACK_SEARCHRELEASETIME_INTERVAL_TIME   1009
#define IDC_TCSTACK_SEARCHRELEASETIME_INTERVAL_STATIC   1010
#define IDC_TCSTACK_SEARCHRELEASETIME_FIND   1011
#define IDC_TCSTACK_SEARCHRELEASETIME_HELP   1012

// Specify the telecommand stack search release time dialog related identifiers
#define TCSTACKSEARCHRELEASETIME_MINIMUMINTERVAL   1
#define TCSTACKSEARCHRELEASETIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCSTACKSEARCHRELEASETIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCStackSearchReleaseTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchReleaseTimeDialog)

	// Construction
public:
	CTCStackSearchReleaseTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchReleaseTimeDialog)
	enum { IDD = IDD_TCSTACK_SEARCHRELEASETIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchReleaseTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchReleaseTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchReleaseTimeOffsetDialog dialog

#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_OFFSET_STATIC   1001
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_OFFSET   1002
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_DIRECTION   1003
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_ALL   1006
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_MATCH   1007
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_INTERVAL   1008
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME   1009
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_INTERVAL_STATIC   1010
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_FIND   1011
#define IDC_TCSTACK_SEARCHRELEASETIMEOFFSET_HELP   1012

// Specify the telecommand stack search release time offset dialog related identifiers
#define TCSTACKSEARCHRELEASETIMEOFFSET_MINIMUMINTERVAL   1
#define TCSTACKSEARCHRELEASETIMEOFFSET_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCSTACKSEARCHRELEASETIMEOFFSET_DEFAULTINTERVAL   SECONDSPERMINUTE

class CTCStackSearchReleaseTimeOffsetDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchReleaseTimeOffsetDialog)

	// Construction
public:
	CTCStackSearchReleaseTimeOffsetDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchReleaseTimeOffsetDialog)
	enum { IDD = IDD_TCSTACK_SEARCHRELEASETIMEOFFSET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchReleaseTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchReleaseTimeOffsetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTimeOffset();
	afx_msg void OnIntervalTimeOffset();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchTransmissionTimeDialog dialog

#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_TIME_STATIC   1001
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_TIME   1002
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_DIRECTION   1003
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_ALL   1006
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_MATCH   1007
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_INTERVAL   1008
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_INTERVAL_TIME   1009
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_INTERVAL_STATIC   1010
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_FIND   1011
#define IDC_TCSTACK_SEARCHTRANSMISSIONTIME_HELP   1012

// Specify the telecommand stack search transmission time dialog related identifiers
#define TCSTACKSEARCHTRANSMISSIONTIME_MINIMUMINTERVAL   1
#define TCSTACKSEARCHTRANSMISSIONTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCSTACKSEARCHTRANSMISSIONTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCStackSearchTransmissionTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchTransmissionTimeDialog)

	// Construction
public:
	CTCStackSearchTransmissionTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchTransmissionTimeDialog)
	enum { IDD = IDD_TCSTACK_SEARCHTRANSMISSIONTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchTransmissionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchTransmissionTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchExecutionTimeDialog dialog

#define IDC_TCSTACK_SEARCHEXECUTIONTIME_TIME_STATIC   1001
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_TIME   1002
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_DIRECTION   1003
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_ALL   1006
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_MATCH   1007
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_INTERVAL   1008
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_INTERVAL_TIME   1009
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_INTERVAL_STATIC   1010
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_FIND   1011
#define IDC_TCSTACK_SEARCHEXECUTIONTIME_HELP   1012

// Specify the telecommand stack search execution time dialog related identifiers
#define TCSTACKSEARCHEXECUTIONTIME_MINIMUMINTERVAL   1
#define TCSTACKSEARCHEXECUTIONTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCSTACKSEARCHEXECUTIONTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCStackSearchExecutionTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchExecutionTimeDialog)

	// Construction
public:
	CTCStackSearchExecutionTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchExecutionTimeDialog)
	enum { IDD = IDD_TCSTACK_SEARCHEXECUTIONTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchExecutionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchExecutionTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchExecutionTimeOffsetDialog dialog

#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_OFFSET_STATIC   1001
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_OFFSET   1002
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_DIRECTION   1003
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_ALL   1006
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_MATCH   1007
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_INTERVAL   1008
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME   1009
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_STATIC   1010
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_FIND   1011
#define IDC_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_HELP   1012

// Specify the telecommand stack search execution time offset dialog related identifiers
#define TCSTACKSEARCHEXECUTIONTIMEOFFSET_MINIMUMOFFSET   -(365*SECONDSPERDAY)
#define TCSTACKSEARCHEXECUTIONTIMEOFFSET_MAXIMUMOFFSET   (365*SECONDSPERDAY)
#define TCSTACKSEARCHEXECUTIONTIMEOFFSET_DEFAULTOFFSET   0
#define TCSTACKSEARCHEXECUTIONTIMEOFFSET_MINIMUMINTERVAL   1
#define TCSTACKSEARCHEXECUTIONTIMEOFFSET_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCSTACKSEARCHEXECUTIONTIMEOFFSET_DEFAULTINTERVAL   SECONDSPERMINUTE

class CTCStackSearchExecutionTimeOffsetDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchExecutionTimeOffsetDialog)

	// Construction
public:
	CTCStackSearchExecutionTimeOffsetDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchExecutionTimeOffsetDialog)
	enum { IDD = IDD_TCSTACK_SEARCHEXECUTIONTIMEOFFSET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchExecutionTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchExecutionTimeOffsetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTimeOffset();
	afx_msg void OnIntervalTimeOffset();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchAuthorizationDialog dialog

#define IDC_TCSTACK_SEARCHAUTHORIZATION_TYPE_STATIC   1001
#define IDC_TCSTACK_SEARCHAUTHORIZATION_TYPE   1002
#define IDC_TCSTACK_SEARCHAUTHORIZATION_DIRECTION   1003
#define IDC_TCSTACK_SEARCHAUTHORIZATION_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHAUTHORIZATION_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHAUTHORIZATION_ALL   1006
#define IDC_TCSTACK_SEARCHAUTHORIZATION_FIND   1007
#define IDC_TCSTACK_SEARCHAUTHORIZATION_HELP   1008

class CTCStackSearchAuthorizationDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchAuthorizationDialog)

	// Construction
public:
	CTCStackSearchAuthorizationDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchAuthorizationDialog)
	enum { IDD = IDD_TCSTACK_SEARCHAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumAuthorizations();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchAuthorizationDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchAuthorizationDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchPTVTimeWindowDialog dialog

#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_TIME_STATIC   1001
#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_TIME   1002
#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_DIRECTION   1003
#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_ALL   1006
#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_FIND   1007
#define IDC_TCSTACK_SEARCHPTVTIMEWINDOW_HELP   1008

class CTCStackSearchPTVTimeWindowDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchPTVTimeWindowDialog)

	// Construction
public:
	CTCStackSearchPTVTimeWindowDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchPTVTimeWindowDialog)
	enum { IDD = IDD_TCSTACK_SEARCHPTVTIMEWINDOW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchPTVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchPTVTimeWindowDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchPTVCheckDialog dialog

#define IDC_TCSTACK_SEARCHPTVCHECK_CHECK_STATIC   1001
#define IDC_TCSTACK_SEARCHPTVCHECK_CHECK   1002
#define IDC_TCSTACK_SEARCHPTVCHECK_DIRECTION   1003
#define IDC_TCSTACK_SEARCHPTVCHECK_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHPTVCHECK_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHPTVCHECK_ALL   1006
#define IDC_TCSTACK_SEARCHPTVCHECK_FIND   1007
#define IDC_TCSTACK_SEARCHPTVCHECK_HELP   1008

class CTCStackSearchPTVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchPTVCheckDialog)

	// Construction
public:
	CTCStackSearchPTVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchPTVCheckDialog)
	enum { IDD = IDD_TCSTACK_SEARCHPTVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchPTVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchPTVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchPTVResultDialog dialog

#define IDC_TCSTACK_SEARCHPTVRESULT_RESULT_STATIC   1001
#define IDC_TCSTACK_SEARCHPTVRESULT_RESULT   1002
#define IDC_TCSTACK_SEARCHPTVRESULT_DIRECTION   1003
#define IDC_TCSTACK_SEARCHPTVRESULT_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHPTVRESULT_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHPTVRESULT_ALL   1006
#define IDC_TCSTACK_SEARCHPTVRESULT_FIND   1007
#define IDC_TCSTACK_SEARCHPTVRESULT_HELP   1008

class CTCStackSearchPTVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchPTVResultDialog)

	// Construction
public:
	CTCStackSearchPTVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchPTVResultDialog)
	enum { IDD = IDD_TCSTACK_SEARCHPTVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchPTVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchPTVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchPEVCheckDialog dialog

#define IDC_TCSTACK_SEARCHPEVCHECK_CHECK_STATIC   1001
#define IDC_TCSTACK_SEARCHPEVCHECK_CHECK   1002
#define IDC_TCSTACK_SEARCHPEVCHECK_DIRECTION   1003
#define IDC_TCSTACK_SEARCHPEVCHECK_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHPEVCHECK_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHPEVCHECK_ALL   1006
#define IDC_TCSTACK_SEARCHPEVCHECK_FIND   1007
#define IDC_TCSTACK_SEARCHPEVCHECK_HELP   1008

class CTCStackSearchPEVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchPEVCheckDialog)

	// Construction
public:
	CTCStackSearchPEVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchPEVCheckDialog)
	enum { IDD = IDD_TCSTACK_SEARCHPEVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchPEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchPEVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchPEVResultDialog dialog

#define IDC_TCSTACK_SEARCHPEVRESULT_RESULT_STATIC   1001
#define IDC_TCSTACK_SEARCHPEVRESULT_RESULT   1002
#define IDC_TCSTACK_SEARCHPEVRESULT_DIRECTION   1003
#define IDC_TCSTACK_SEARCHPEVRESULT_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHPEVRESULT_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHPEVRESULT_ALL   1006
#define IDC_TCSTACK_SEARCHPEVRESULT_FIND   1007
#define IDC_TCSTACK_SEARCHPEVRESULT_HELP   1008

class CTCStackSearchPEVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchPEVResultDialog)

	// Construction
public:
	CTCStackSearchPEVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchPEVResultDialog)
	enum { IDD = IDD_TCSTACK_SEARCHPEVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchPEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchPEVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchCEVTimeWindowDialog dialog

#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_TIME_STATIC   1001
#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_TIME   1002
#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_DIRECTION   1003
#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_ALL   1006
#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_FIND   1007
#define IDC_TCSTACK_SEARCHCEVTIMEWINDOW_HELP   1008

class CTCStackSearchCEVTimeWindowDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchCEVTimeWindowDialog)

	// Construction
public:
	CTCStackSearchCEVTimeWindowDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchCEVTimeWindowDialog)
	enum { IDD = IDD_TCSTACK_SEARCHCEVTIMEWINDOW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchCEVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchCEVTimeWindowDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchCEVCheckDialog dialog

#define IDC_TCSTACK_SEARCHCEVCHECK_CHECK_STATIC   1001
#define IDC_TCSTACK_SEARCHCEVCHECK_CHECK   1002
#define IDC_TCSTACK_SEARCHCEVCHECK_DIRECTION   1003
#define IDC_TCSTACK_SEARCHCEVCHECK_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHCEVCHECK_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHCEVCHECK_ALL   1006
#define IDC_TCSTACK_SEARCHCEVCHECK_FIND   1007
#define IDC_TCSTACK_SEARCHCEVCHECK_HELP   1008

class CTCStackSearchCEVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchCEVCheckDialog)

	// Construction
public:
	CTCStackSearchCEVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchCEVCheckDialog)
	enum { IDD = IDD_TCSTACK_SEARCHCEVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchCEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchCEVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchCEVResultDialog dialog

#define IDC_TCSTACK_SEARCHCEVRESULT_RESULT_STATIC   1001
#define IDC_TCSTACK_SEARCHCEVRESULT_RESULT   1002
#define IDC_TCSTACK_SEARCHCEVRESULT_DIRECTION   1003
#define IDC_TCSTACK_SEARCHCEVRESULT_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHCEVRESULT_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHCEVRESULT_ALL   1006
#define IDC_TCSTACK_SEARCHCEVRESULT_FIND   1007
#define IDC_TCSTACK_SEARCHCEVRESULT_HELP   1008

class CTCStackSearchCEVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchCEVResultDialog)

	// Construction
public:
	CTCStackSearchCEVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchCEVResultDialog)
	enum { IDD = IDD_TCSTACK_SEARCHCEVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTextView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchCEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchCEVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCStackSearchStatusDialog dialog

#define IDC_TCSTACK_SEARCHSTATUS_STATUS_STATIC   1001
#define IDC_TCSTACK_SEARCHSTATUS_STATUS   1002
#define IDC_TCSTACK_SEARCHSTATUS_DIRECTION   1003
#define IDC_TCSTACK_SEARCHSTATUS_DIRECTION_UP   1004
#define IDC_TCSTACK_SEARCHSTATUS_DIRECTION_DOWN   1005
#define IDC_TCSTACK_SEARCHSTATUS_ALL   1006
#define IDC_TCSTACK_SEARCHSTATUS_FIND   1007
#define IDC_TCSTACK_SEARCHSTATUS_HELP   1008

class CTCStackSearchStatusDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCStackSearchStatusDialog)

	// Construction
public:
	CTCStackSearchStatusDialog();   // standard constructor

	// Attributes
private:
	BOOL  m_bHistorical;

	// Dialog Data
	//{{AFX_DATA(CTCStackSearchStatusDialog)
	enum { IDD = IDD_TCSTACK_SEARCHSTATUS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, BOOL bHistorical = FALSE);

	class CTextView *GetParent() CONST;

private:
	VOID EnumStatus();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCStackSearchStatusDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCStackSearchStatusDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItem

// Specify the telecommand manual stack item types
#define TCMANUALSTACKITEM_TYPE_NONE   TCITEM_TYPE_NONE
#define TCMANUALSTACKITEM_TYPE_FUNCTION   TCITEM_TYPE_FUNCTION
#define TCMANUALSTACKITEM_TYPE_SEQUENCE   TCITEM_TYPE_SEQUENCE
#define TCMANUALSTACKITEM_TYPE_PROCEDURE   TCITEM_TYPE_PROCEDURE
// Specify the telecommand manual stack item flags
#define TCMANUALSTACKITEM_CHECKFLAG_OVERRIDEPTV   TCITEM_CHECKFLAG_OVERRIDEPTV
#define TCMANUALSTACKITEM_CHECKFLAG_OVERRIDEPEV   TCITEM_CHECKFLAG_OVERRIDEPEV
#define TCMANUALSTACKITEM_CHECKFLAG_OVERRIDECEV   TCITEM_CHECKFLAG_OVERRIDECEV
#define TCMANUALSTACKITEM_CHECKFLAG_DISABLEPTV   TCITEM_CHECKFLAG_DISABLEPTV
#define TCMANUALSTACKITEM_CHECKFLAG_DISABLEPEV   TCITEM_CHECKFLAG_DISABLEPEV
#define TCMANUALSTACKITEM_CHECKFLAG_DISABLECEV   TCITEM_CHECKFLAG_DISABLECEV
#define TCMANUALSTACKITEM_CHECKFLAG_PREAUTHORIZED   TCITEM_CHECKFLAG_PREAUTHORIZED
#define TCMANUALSTACKITEM_LINKAGEFLAG_GROUPED   TCITEM_LINKAGEFLAG_GROUPED
#define TCMANUALSTACKITEM_LINKAGEFLAG_BLOCKED   TCITEM_LINKAGEFLAG_BLOCKED
#define TCMANUALSTACKITEM_RELEASEFLAG_AFTERBEGIN   TCITEM_RELEASEFLAG_AFTERBEGIN
#define TCMANUALSTACKITEM_RELEASEFLAG_AFTERPREVIOUS   TCITEM_RELEASEFLAG_AFTERPREVIOUS
#define TCMANUALSTACKITEM_EXECUTIONFLAG_AFTERBEGIN   TCITEM_EXECUTIONFLAG_AFTERBEGIN
#define TCMANUALSTACKITEM_EXECUTIONFLAG_AFTERPREVIOUS   TCITEM_EXECUTIONFLAG_AFTERPREVIOUS
#define TCMANUALSTACKITEM_EXECUTIONFLAG_IMMEDIATE   TCITEM_EXECUTIONFLAG_IMMEDIATE
#define TCMANUALSTACKITEM_EXECUTIONFLAG_TIMETAGGED   TCITEM_EXECUTIONFLAG_TIMETAGGED
#define TCMANUALSTACKITEM_EXECUTIONFLAG_1STSTEP   TCITEM_EXECUTIONFLAG_1STSTEP
#define TCMANUALSTACKITEM_EXECUTIONFLAG_2NDSTEP   TCITEM_EXECUTIONFLAG_2NDSTEP
#define TCMANUALSTACKITEM_DUMPFLAG_SYNCHRONIZED   TCITEM_DUMPFLAG_SYNCHRONIZED
#define TCMANUALSTACKITEM_DUMPFLAG_NOTSYNCHRONIZED   TCITEM_DUMPFLAG_NOTSYNCHRONIZED
#define TCMANUALSTACKITEM_ACKNOWLEDGEFLAG_ACCEPTANCE   TCITEM_ACKNOWLEDGEFLAG_ACCEPTANCE
#define TCMANUALSTACKITEM_ACKNOWLEDGEFLAG_START   TCITEM_ACKNOWLEDGEFLAG_START
#define TCMANUALSTACKITEM_ACKNOWLEDGEFLAG_PROGRESS   TCITEM_ACKNOWLEDGEFLAG_PROGRESS
#define TCMANUALSTACKITEM_ACKNOWLEDGEFLAG_COMPLETION   TCITEM_ACKNOWLEDGEFLAG_COMPLETION
#define TCMANUALSTACKITEM_ACKNOWLEDGEFLAG_ALL   TCITEM_ACKNOWLEDGEFLAG_ALL
// Specify the telecommand manual stack item check results
#define TCMANUALSTACKITEM_RESULT_NONE   TCITEM_RESULT_NONE
#define TCMANUALSTACKITEM_RESULT_PTV_GO   TCITEM_RESULT_PTV_GO
#define TCMANUALSTACKITEM_RESULT_PTV_WAIT   TCITEM_RESULT_PTV_WAIT
#define TCMANUALSTACKITEM_RESULT_PTV_FAIL   TCITEM_RESULT_PTV_FAIL
#define TCMANUALSTACKITEM_RESULT_PEV_GO   TCITEM_RESULT_PEV_GO
#define TCMANUALSTACKITEM_RESULT_PEV_NOGO   TCITEM_RESULT_PEV_NOGO
#define TCMANUALSTACKITEM_FAILURE_PTV_UPLINK   TCITEM_FAILURE_PTV_UPLINK
#define TCMANUALSTACKITEM_FAILURE_PTV_RELEASETIMEWINDOW   TCITEM_FAILURE_PTV_RELEASETIMEWINDOW
#define TCMANUALSTACKITEM_FAILURE_PTV_EXECUTIONTIME   TCITEM_FAILURE_PTV_EXECUTIONTIME
#define TCMANUALSTACKITEM_FAILURE_PTV_INTERLOCK   TCITEM_FAILURE_PTV_INTERLOCK
#define TCMANUALSTACKITEM_FAILURE_PTV_SUBSYSTEM   TCITEM_FAILURE_PTV_SUBSYSTEM
#define TCMANUALSTACKITEM_FAILURE_PTV_ONBOARDBUFFER   TCITEM_FAILURE_PTV_ONBOARDBUFFER
#define TCMANUALSTACKITEM_FAILURE_PTV_ENCODING   TCITEM_FAILURE_PTV_ENCODING
#define TCMANUALSTACKITEM_FAILURE_PEV_TELEMETRY   TCITEM_FAILURE_PEV_TELEMETRY
#define TCMANUALSTACKITEM_FAILURE_PEV_CORRELATION   TCITEM_FAILURE_PEV_CORRELATION
#define TCMANUALSTACKITEM_FAILURE_PEV_2NDSTEP   TCITEM_FAILURE_PEV_2NDSTEP
#define TCMANUALSTACKITEM_FAILURE_PEV_PARAMETERS   TCITEM_FAILURE_PEV_PARAMETERS
#define TCMANUALSTACKITEM_FAILURE_CEV_PARAMETERS   TCITEM_FAILURE_CEV_PARAMETERS
// Specify the telecommand manual stack item status flags
#define TCMANUALSTACKITEM_STATUS_NONE   TCITEM_STATUS_NONE
#define TCMANUALSTACKITEM_STATUS_ONSTACK   TCITEM_STATUS_ONSTACK
#define TCMANUALSTACKITEM_STATUS_ARMED   TCITEM_STATUS_ARMED
#define TCMANUALSTACKITEM_STATUS_DISPATCHED   TCITEM_STATUS_DISPATCHED
#define TCMANUALSTACKITEM_STATUS_RELEASED   TCITEM_STATUS_RELEASED
#define TCMANUALSTACKITEM_STATUS_NOTRELEASED   TCITEM_STATUS_NOTRELEASED
#define TCMANUALSTACKITEM_STATUS_FAILEDRELEASE   TCITEM_STATUS_FAILEDRELEASE
#define TCMANUALSTACKITEM_STATUS_SENT   TCITEM_STATUS_SENT
#define TCMANUALSTACKITEM_STATUS_FAILEDSEND   TCITEM_STATUS_FAILEDSEND
#define TCMANUALSTACKITEM_STATUS_UPLINKED   TCITEM_STATUS_UPLINKED
#define TCMANUALSTACKITEM_STATUS_FAILEDUPLINK   TCITEM_STATUS_FAILEDUPLINK
#define TCMANUALSTACKITEM_STATUS_EXECUTED   TCITEM_STATUS_EXECUTED
#define TCMANUALSTACKITEM_STATUS_NOTEXECUTED   TCITEM_STATUS_NOTEXECUTED
#define TCMANUALSTACKITEM_STATUS_FAILEDEXECUTION   TCITEM_STATUS_FAILEDEXECUTION
// Specify the telecommand manual stack item status colors
#define TCMANUALSTACKITEM_STATUSCOLOR_NONE   0
#define TCMANUALSTACKITEM_STATUSCOLOR_IDLE   1
#define TCMANUALSTACKITEM_STATUSCOLOR_PENDING   2
#define TCMANUALSTACKITEM_STATUSCOLOR_PASSED   3
#define TCMANUALSTACKITEM_STATUSCOLOR_NOTPASSED   4
// Specify the telecommand manual stack item alert types
#define TCMANUALSTACKITEM_ALERTTYPE_NONE   0
#define TCMANUALSTACKITEM_ALERTTYPE_INFORMATION   1
#define TCMANUALSTACKITEM_ALERTTYPE_WARNING   2
#define TCMANUALSTACKITEM_ALERTTYPE_ERROR   3
#define TCMANUALSTACKITEM_ALERTTYPE_ANY   (-1)

class CTCManualStackItem : public CTCItem
{
	// Construction
public:
	CTCManualStackItem();

	// Attributes
private:
	CUIntArray  m_nAlertTypes;
	CUIntArray  m_nAlertMessages;
	CStringArray  m_szAlertMessages;
private:
	BOOL  m_bSelected;

	// Operations
public:
	BOOL Alert(UINT nType, UINT nMessage, LPCTSTR pszMessage, BOOL bOverwrite = TRUE);
	BOOL Alert(UINT nType, UINT nMessage = -1, BOOL bEnable = FALSE);
	UINT IsAlerted(UINT nMessage, CString &szMessage) CONST;
	UINT IsAlerted(UINT nMessage = -1) CONST;

	INT GetAlertCount(UINT nType) CONST;

	VOID Select(BOOL bSelect = TRUE);
	BOOL IsSelected() CONST;

	BOOL Copy(CONST CTCManualStackItem *pItem);
	BOOL Compare(CONST CTCManualStackItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItems

class CTCManualStackItems : public CTCItems
{
	// Construction
public:
	CTCManualStackItems();
	~CTCManualStackItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCManualStackItem *pItem);

	INT Collect(INT nIndex, CTCManualStackItems &pItems) CONST;
	INT Collect(INT nIndex, CUIntArray &nItemIDs) CONST;
	INT Collect(INT nIndex, CPtrArray &pItems) CONST;

	CTCManualStackItem *GetAt(INT nIndex) CONST;
	CTCManualStackItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCManualStackItems *pItems);
	BOOL Compare(CONST CTCManualStackItems *pItems) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackComposedItem

class CTCManualStackComposedItem : public CTCManualStackItems
{
	// Construction
public:
	CTCManualStackComposedItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbParameters;
		INT  cbEntries;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
private:
	CDatabaseTCParameters  m_pParameters;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetParameters(CONST CDatabaseTCParameters &pParameters);
	INT GetParameters(CDatabaseTCParameters &pParameters) CONST;

	BOOL Copy(CONST CTCManualStackComposedItem *pItem);
	BOOL Compare(CONST CTCManualStackComposedItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemTemplate

class CTCManualStackItemTemplate : public CTCManualStackItem
{
	// Construction
public:

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTemplate[2];
		INT  cbItem;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTemplate[2];

	// Operations
public:
	VOID SetTemplateName(LPCTSTR pszName);
	CString GetTemplateName() CONST;
	VOID SetTemplateDescription(LPCTSTR pszDescription);
	CString GetTemplateDescription() CONST;

	BOOL Copy(CONST CTCManualStackItemTemplate *pTemplate);
	BOOL Compare(CONST CTCManualStackItemTemplate *pTemplate) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemTemplates

class CTCManualStackItemTemplates : public CPtrArray
{
	// Construction
public:
	CTCManualStackItemTemplates();
	~CTCManualStackItemTemplates();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCManualStackItemTemplate *pTemplate);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(LPCTSTR pszName, CStringArray &szTemplates) CONST;

	CTCManualStackItemTemplate *GetAt(INT nIndex) CONST;
	CTCManualStackItemTemplate *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCManualStackItemTemplates *pTemplates);
	BOOL Compare(CONST CTCManualStackItemTemplates *pTemplates) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackComposedItemTemplate

class CTCManualStackComposedItemTemplate : public CTCManualStackComposedItem
{
	// Construction
public:

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTemplate[2];
		INT  cbItem;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTemplate[2];

	// Operations
public:
	VOID SetTemplateName(LPCTSTR pszName);
	CString GetTemplateName() CONST;
	VOID SetTemplateDescription(LPCTSTR pszDescription);
	CString GetTemplateDescription() CONST;

	BOOL Copy(CONST CTCManualStackComposedItemTemplate *pTemplate);
	BOOL Compare(CONST CTCManualStackComposedItemTemplate *pTemplate) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackComposedItemTemplates

class CTCManualStackComposedItemTemplates : public CPtrArray
{
	// Construction
public:
	CTCManualStackComposedItemTemplates();
	~CTCManualStackComposedItemTemplates();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCManualStackComposedItemTemplate *pTemplate);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(LPCTSTR pszName, CStringArray &szTemplates) CONST;

	CTCManualStackComposedItemTemplate *GetAt(INT nIndex) CONST;
	CTCManualStackComposedItemTemplate *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCManualStackComposedItemTemplates *pTemplates);
	BOOL Compare(CONST CTCManualStackComposedItemTemplates *pTemplates) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchGroup

// Specify the telecommand manual stack search group types
#define TCMANUALSTACKSEARCHGROUP_TYPE_NONE   0
#define TCMANUALSTACKSEARCHGROUP_TYPE_FUNCTIONS   1
#define TCMANUALSTACKSEARCHGROUP_TYPE_SEQUENCES   2
#define TCMANUALSTACKSEARCHGROUP_TYPE_STACKS   3
#define TCMANUALSTACKSEARCHGROUP_TYPES   3

class CTCManualStackSearchGroup : public CObject
{
	// Construction
public:
	CTCManualStackSearchGroup();

	// Atttributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbMembers;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nType;
	CString  m_szName;
	CStringArray  m_szMembers;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;

	VOID SetMembers(CONST CStringArray &szMembers);
	INT GetMembers(CStringArray &szMembers) CONST;

	VOID Copy(CONST CTCManualStackSearchGroup *pGroup);
	BOOL Compare(CONST CTCManualStackSearchGroup *pGroup) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchGroups

class CTCManualStackSearchGroups : public CPtrArray
{
	// Construction
public:
	CTCManualStackSearchGroups();
	~CTCManualStackSearchGroups();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCManualStackSearchGroup *pGroup);

	INT Find(LPCTSTR pszName) CONST;

	CTCManualStackSearchGroup *GetAt(INT nIndex) CONST;
	CTCManualStackSearchGroup *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCManualStackSearchGroups *pGroups);
	BOOL Compare(CONST CTCManualStackSearchGroups *pGroups) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchFilter

// Specify the telecommand manual stack search filter types
#define TCMANUALSTACKSEARCHFILTER_TYPE_NONE   TCMANUALSTACKSEARCHGROUP_TYPE_NONE
#define TCMANUALSTACKSEARCHFILTER_TYPE_FUNCTIONS   TCMANUALSTACKSEARCHGROUP_TYPE_FUNCTIONS
#define TCMANUALSTACKSEARCHFILTER_TYPE_SEQUENCES   TCMANUALSTACKSEARCHGROUP_TYPE_SEQUENCES
#define TCMANUALSTACKSEARCHFILTER_TYPE_STACKS   TCMANUALSTACKSEARCHGROUP_TYPE_STACKS
#define TCMANUALSTACKSEARCHFILTER_TYPES   TCMANUALSTACKSEARCHGROUP_TYPES
// Specify the telecommand manual stack search filter operators
#define TCMANUALSTACKSEARCHFILTER_OPERATOR_AND   0
#define TCMANUALSTACKSEARCHFILTER_OPERATOR_OR   1

class CTCManualStackSearchFilter : public CObject
{
	// Construction
public:
	CTCManualStackSearchFilter();

	// Atttributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbSearchKeys;
		INT  cbSearchValues;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nType;
	CString  m_szName;
	CStringArray  m_szSearchKeys;
	CStringArray  m_szSearchValues;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;

	VOID SetSearchKeys(CONST CStringArray &szKeys, CONST CStringArray &szValues);
	INT GetSearchKeys(CStringArray &szKeys, CStringArray &szValues) CONST;

	VOID Copy(CONST CTCManualStackSearchFilter *pFilter);
	BOOL Compare(CONST CTCManualStackSearchFilter *pFilter) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchFilters

class CTCManualStackSearchFilters : public CPtrArray
{
	// Construction
public:
	CTCManualStackSearchFilters();
	~CTCManualStackSearchFilters();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCManualStackSearchFilter *pFilter);

	INT Find(LPCTSTR pszName) CONST;

	CTCManualStackSearchFilter *GetAt(INT nIndex) CONST;
	CTCManualStackSearchFilter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCManualStackSearchFilters *pFilters);
	BOOL Compare(CONST CTCManualStackSearchFilters *pFilters) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackPrintJobInfo

class CTCManualStackPrintJobInfo : public CObject
{
	// Construction
public:
	CTCManualStackPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintRange[2];
		TIMEKEY  tPrintRange[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szProfile;
	CString  m_szComments;
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
	BOOL SetPrintRange(UINT nMin, UINT nMax);
	BOOL SetPrintRange(CONST CTimeKey &tMin, CONST CTimeKey &tMax);
	BOOL GetPrintRange(UINT &nMin, UINT &nMax) CONST;
	BOOL GetPrintRange(CTimeKey &tMin, CTimeKey &tMax) CONST;

	VOID Copy(CONST CTCManualStackPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTCManualStackPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackPrintJobs

class CTCManualStackPrintJobs : public CPtrArray
{
	// Construction
public:
	CTCManualStackPrintJobs();
	~CTCManualStackPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCManualStackPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTCManualStackPrintJobInfo *GetAt(INT nIndex) CONST;
	CTCManualStackPrintJobInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCManualStackPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTCManualStackPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSettingsLayoutPage dialog

#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_GRID   1009
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR   1010
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1011
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS   1012
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1013
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1014
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1015
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1016
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1017
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_NAMES   1018
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1019
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_STYLE   1020
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1021
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_SIZE   1022
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1023
#define IDC_TCMANUALSTACKSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1024

class CTCManualStackSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCManualStackSettingsLayoutPage)

	// Construction
public:
	CTCManualStackSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntItems[2];
	COLORREF  m_nGridBackgroundColor[2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSettingsLayoutPage)
	enum { IDD = IDD_TCMANUALSTACK_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetColumns(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTCManualStackSettingsDialog *GetParentDialog() CONST;
	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumLayoutColumns();

	BOOL ShowLayoutColumns();
	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	BOOL InsertLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL ModifyLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL RemoveLayoutColumn(INT nIndex);
	BOOL SetCurLayoutColumn(INT nIndex = 0);
	INT GetCurLayoutColumn() CONST;
	BOOL CheckLayoutColumn() CONST;

	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);
	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSettingsLayoutPage)
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
	//{{AFX_MSG(CTCManualStackSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnGridBackground();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeColumnName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeGridBackgroundColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSettingsOperationsPage dialog

#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_DETAILS   1001
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MODES   1002
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MODES_MASTERMANUALMODE   1003
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MODES_RELEASEWAITMODE   1004
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MODES_AUTOMATICREJECTIONMODE   1005
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_STATE_DISABLED   1006
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS   1007
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_OVERRIDEPTV   1008
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_DISABLEPTV   1009
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_OVERRIDEPEV   1010
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_DISABLEPEV   1011
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_OVERRIDECEV   1012
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_DISABLECEV   1013
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_INTERLOCKS   1014
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_UPDATE   1015
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_UPDATE_COUNT   1016
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_CHECKS_UPDATE_COUNT_STATIC   1017
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_ALERTS   1018
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS   1019
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_STATIC   1020
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_LIMITED   1021
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_LIMITED_COUNT   1022
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_ALL   1023
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_STATIC   1024
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL   1025
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL_STATIC   1026
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DISPATCHTIMEWINDOW_STATIC   1027
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DISPATCHTIMEWINDOW_INTERVAL   1028
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DISPATCHTIMEWINDOW_INTERVAL_STATIC   1029
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ALWAYSALLOWEXIT   1030
#define IDC_TCMANUALSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_UNDISPATCHONEXIT   1031

// Specify the telecommand manual stack settings operations page related limits
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MINIMUMCHECKCOUNT   1
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MAXIMUMCHECKCOUNT   100
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MINIMUMARGUMENTS   0
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MAXIMUMARGUMENTS   100
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_DEFAULTARGUMENTS   5
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MINIMUMDEFAULTRELEASETIMEWINDOW   1
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MAXIMUMDEFAULTRELEASETIMEWINDOW   SECONDSPERDAY
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MINIMUMDISPATCHTIMEWINDOW   1
#define TCMANUALSTACKSETTINGSOPERATIONSPAGE_MAXIMUMDISPATCHTIMEWINDOW   (5*SECONDSPERMINUTE)

class CTCManualStackSettingsOperationsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCManualStackSettingsOperationsPage)

	// Construction
public:
	CTCManualStackSettingsOperationsPage();

	// Attributes
private:
	INT  m_nChecks[2];
	INT  m_nArguments[2];
	UINT  m_nCheckFlags[2];
	UINT  m_nMiscellaneousOptions[2];
	CTimeSpan  m_tDefaultReleaseTimeWindow[2];
	CTimeSpan  m_tDispatchTimeWindow[2];
	BOOL  m_bStateFlags[2];
	BOOL  m_bArguments[2];
	BOOL  m_bModes[2][4];
	BOOL  m_bAlerts[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSettingsOperationsPage)
	enum { IDD = IDD_TCMANUALSTACK_SETTINGS_OPERATIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL GetListCheckOptions(UINT &nFlags, INT &nCount) CONST;
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetMasterManualModeFlag(BOOL &bEnabled) CONST;
	BOOL GetReleaseWaitModeFlag(BOOL &bEnabled) CONST;
	BOOL GetAutoRejectionModeFlag(BOOL &bEnabled) CONST;
	BOOL GetInterlockModeFlag(BOOL &bEnabled) CONST;
	BOOL GetDisabledStateFlag(BOOL &bFlag) CONST;

	class CTCManualStackSettingsDialog *GetParentDialog() CONST;
	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowConfiguration();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSettingsOperationsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSettingsOperationsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnMasterManualMode();
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnAutomaticRejectionMode();
	afx_msg void OnDisabledState();
	afx_msg void OnOverridePTV();
	afx_msg void OnDisablePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnDisablePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnInterlockChecks();
	afx_msg void OnUpdateChecks();
	afx_msg void OnAlerts();
	afx_msg void OnLimitArguments();
	afx_msg void OnAllArguments();
	afx_msg void OnAlwaysAllowExit();
	afx_msg void OnUndispatchOnExit();
	afx_msg void OnSpinchangeUpdateChecksCount();
	afx_msg void OnSpinchangeArgumentsCount();
	afx_msg void OnSpinchangeDefaultReleaseTimeWindow();
	afx_msg void OnSpinchangeDispatchTimeWindow();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSettingsLoggingPage dialog

#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_DETAILS   1001
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_LIST   1002
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_OPTIONS   1003
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_MODE_STATIC   1004
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_REALTIME   1005
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_RELOAD   1006
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_RELOAD_COUNT   1007
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_RELOAD_COUNT_STATIC   1008
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL   1009
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME_STATIC   1010
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME   1011
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME   1012
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME   1013
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT   1014
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT   1015
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC   1016
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT   1017
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE   1018
#define IDC_TCMANUALSTACKSETTINGS_LOGGINGPAGE_SHOWASEVENT   1019

// Specify the telecommand manual stack settings logging page related limits
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_MINIMUMRELOADCOUNT   1
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_MAXIMUMRELOADCOUNT   1000
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_DEFAULTRELOADCOUNT   25
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_MINIMUMRETRIEVALSTOPCOUNT   1
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_MAXIMUMRETRIEVALSTOPCOUNT   10000
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_DEFAULTRETRIEVALSTOPCOUNT   100
// Specify the telecommand manual stack settings logging page related timer identifiers
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_TIMERID   100
#define TCMANUALSTACKSETTINGSLOGGINGPAGE_TIMEOUT   500

class CTCManualStackSettingsLoggingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCManualStackSettingsLoggingPage)

	// Construction
public:
	CTCManualStackSettingsLoggingPage();

	// Attributes
private:
	UINT  m_nArchivalPolicy[2];
	UINT  m_nRetrievalReloadCount[2];
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	BOOL  m_bShowAsEvent[2];
private:
	CLogFile  m_cRetrievalFile;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSettingsLoggingPage)
	enum { IDD = IDD_TCMANUALSTACK_SETTINGS_LOGGINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	class CTCManualStackSettingsDialog *GetParentDialog() CONST;
	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingDetails();
	VOID ShowLogEntries(CONST CTCLogEntries &pEntries);
	VOID ShowLogEntry(CONST CTCLogEntry *pEntry, INT nIndex = -1);

	BOOL RetrieveLogEntries();
	BOOL RetrieveLogEntries(CTCLogEntries &pEntries);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSettingsLoggingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSettingsLoggingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnRealtime();
	afx_msg void OnHistorical();
	afx_msg void OnReloadCount();
	afx_msg void OnStopAtTime();
	afx_msg void OnStopAtLimit();
	afx_msg void OnStopAtEnd();
	afx_msg void OnOptions();
	afx_msg void OnRetrieve();
	afx_msg void OnShowAsEvent();
	afx_msg void OnSpinchangeReloadCount();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSettingsPrintingComments window

class CTCManualStackSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTCManualStackSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSettingsPrintingPage dialog

#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_PROFILE_STATIC   1002
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_PROFILE   1003
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS   1004
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_STATIC   1005
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_ONSTACK   1006
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_DISPATCHED   1007
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_NOTRELEASED   1008
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_FAILEDRELEASE   1009
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER   1010
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW   1011
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC   1012
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH   1013
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME   1014
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START   1015
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_TO_STATIC   1016
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP   1017
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_COMMENTS   1018
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC   1019
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_COMMENTSTEXT   1020
#define IDC_TCMANUALSTACKSETTINGS_PRINTINGPAGE_CLEARCOMMENTS   1021

// Specify the telecommand manual stack settings printing page related limits
#define TCMANUALSTACKSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE   1
#define TCMANUALSTACKSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE   10000
#define TCMANUALSTACKSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE   100

class CTCManualStackSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCManualStackSettingsPrintingPage)

	// Construction
public:
	CTCManualStackSettingsPrintingPage();

	// Attributes
private:
	CTCManualStackPrintJobs  m_pJobs[2];
private:
	CTCManualStackSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSettingsPrintingPage)
	enum { IDD = IDD_TCMANUALSTACK_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCManualStackPrintJobs &pJobs) CONST;

	class CTCManualStackSettingsDialog *GetParentDialog() CONST;
	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTCManualStackPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintOnStackItems();
	afx_msg void OnPrintDispatchedItems();
	afx_msg void OnPrintFailedReleaseItems();
	afx_msg void OnPrintNotReleasedItems();
	afx_msg void OnPrintItemRange();
	afx_msg void OnPrintTimeRange();
	afx_msg void OnSelchangeProfile();
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
// CTCManualStackSettingsTabCtrl window

class CTCManualStackSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCManualStackSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSettingsDialog

class CTCManualStackSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTCManualStackSettingsDialog)

	// Construction
public:
	CTCManualStackSettingsDialog();

	// Attributes
private:
	CTCManualStackSettingsTabCtrl  m_wndTabCtrl;
	CTCManualStackSettingsLayoutPage  m_pageLayout;
	CTCManualStackSettingsOperationsPage  m_pageOperations;
	CTCManualStackSettingsLoggingPage  m_pageLogging;
	CTCManualStackSettingsPrintingPage  m_pagePrinting;

	// Operations
public:
	BOOL GetColumns(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL GetListCheckOptions(UINT &nFlags, INT &nCount) CONST;
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetMasterManualModeFlag(BOOL &bEnabled) CONST;
	BOOL GetReleaseWaitModeFlag(BOOL &bEnabled) CONST;
	BOOL GetAutoRejectionModeFlag(BOOL &bEnabled) CONST;
	BOOL GetInterlockModeFlag(BOOL &bEnabled) CONST;
	BOOL GetDisabledStateFlag(BOOL &bFlag) CONST;
	BOOL IsOperationsModified() CONST;

	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL IsLoggingModified() CONST;

	BOOL GetPrintJobs(CTCManualStackPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCManualStackWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSettingsDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackSettingsDialog)
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
// CTCManualStackAlertOptionsDialog dialog

#define IDC_TCMANUALSTACK_ALERTOPTIONS_DETAILS   1001
#define IDC_TCMANUALSTACK_ALERTOPTIONS_TYPE_STATIC   1002
#define IDC_TCMANUALSTACK_ALERTOPTIONS_TYPE   1003
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION   1004
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_AUDITION_STATIC   1005
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_AUDITION   1006
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_AUDITION_BLINK   1007
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC   1008
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_AUDITION_COLOR   1009
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_STATIC   1010
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS   1011
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD   1012
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE   1013
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL   1014
#define IDC_TCMANUALSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST   1015
#define IDC_TCMANUALSTACK_ALERTOPTIONS_HELP   1016

class CTCManualStackAlertOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackAlertOptionsDialog)

	// Construction
public:
	CTCManualStackAlertOptionsDialog();   // standard constructor

	// Attributes
private:
	CUIntArray  m_nTypes[2];
	CStringArray  m_szAuditions[2];
	CStringArray  m_szNotifications[2];
	CDWordArray  m_nAcknowledgeColors[2];
	CByteArray  m_bAcknowledgments[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackAlertOptionsDialog)
	enum { IDD = IDD_TCMANUALSTACK_ALERTOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCManualStackOperationsPage *GetParentDialog() CONST;
	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTypes();
	BOOL EnumAuditions();
	BOOL EnumNotifications();

	VOID ShowAlertDetails();

	INT FindAlertType() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackAlertOptionsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackAlertOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAuditionBlink();
	afx_msg void OnAddNotification();
	afx_msg void OnRemoveNotification();
	afx_msg void OnRemoveAllNotifications();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeAuditionColor();
	afx_msg void OnSelchangeNotification();
	afx_msg void OnSelchangeNotificationList();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackLoggingOptionsDialog dialog

#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_DETAILS   1001
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_FILENAME_STATIC   1002
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_FILENAME   1003
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_BROWSE   1004
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_DISABLED   1005
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_RETRIEVALS   1006
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_POLICY   1007
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_POLICY_OVERWRITE   1008
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_POLICY_OLDOVERWRITE   1009
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_POLICY_DAYS_STATIC   1010
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_POLICY_DAYS   1011
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_POLICY_NOOVERWRITE   1012
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_SIZE   1013
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_SIZE_UNLIMITED   1014
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_SIZE_LIMITED   1015
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_SIZE_MAXIMUM_STATIC   1016
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_SIZE_MAXIMUM   1017
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_SIZE_RESET   1018
#define IDC_TCMANUALSTACK_LOGGINGOPTIONS_HELP   1019

// Specify the telecommand manual stack logging options dialog related settings
#define TCMANUALSTACKLOGGINGOPTIONS_MINIMUMDAYS   1
#define TCMANUALSTACKLOGGINGOPTIONS_MAXIMUMDAYS   10000
#define TCMANUALSTACKLOGGINGOPTIONS_DEFAULTDAYS   DAYSPERWEEK
#define TCMANUALSTACKLOGGINGOPTIONS_MINIMUMSIZE   8
#define TCMANUALSTACKLOGGINGOPTIONS_MAXIMUMSIZE   2147483647
#define TCMANUALSTACKLOGGINGOPTIONS_DEFAULTSIZE   (LOGFILE_DEFAULT_SIZE/1024)

class CTCManualStackLoggingOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackLoggingOptionsDialog)

	// Construction
public:
	CTCManualStackLoggingOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	UINT  m_nArchivalPolicy[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackLoggingOptionsDialog)
	enum { IDD = IDD_TCMANUALSTACK_LOGGINGOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szArchivalFileName, UINT &nArchivalPolicy, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName);

	class CTCManualStackLoggingPage *GetParentDialog() CONST;
	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingOptions();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackLoggingOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackLoggingOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRetrievals();
	afx_msg void OnBrowseFileName();
	afx_msg void OnOverwriteLogs();
	afx_msg void OnOverwriteOldLogs();
	afx_msg void OnOverwriteNoLogs();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnLimitedSize();
	afx_msg void OnResetSize();
	afx_msg void OnDisabled();
	afx_msg void OnSpinchangeDays();
	afx_msg void OnSpinchangeSize();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackRetrievalOptionsDialog dialog

#define IDC_TCMANUALSTACK_RETRIEVALOPTIONS_DETAILS   1001
#define IDC_TCMANUALSTACK_RETRIEVALOPTIONS_FILENAME_STATIC   1002
#define IDC_TCMANUALSTACK_RETRIEVALOPTIONS_FILENAME   1003
#define IDC_TCMANUALSTACK_RETRIEVALOPTIONS_BROWSE   1004
#define IDC_TCMANUALSTACK_RETRIEVALOPTIONS_HELP   1005

class CTCManualStackRetrievalOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackRetrievalOptionsDialog)

	// Construction
public:
	CTCManualStackRetrievalOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackRetrievalOptionsDialog)
	enum { IDD = IDD_TCMANUALSTACK_RETRIEVALOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szFileName);

	class CTCManualStackLoggingOptionsDialog *GetParentDialog() CONST;
	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackRetrievalOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackRetrievalOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchGroupsDialog dialog

#define IDC_TCMANUALSTACK_SEARCHGROUPS_DETAILS   1001
#define IDC_TCMANUALSTACK_SEARCHGROUPS_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_SEARCHGROUPS_NAME   1003
#define IDC_TCMANUALSTACK_SEARCHGROUPS_ADD   1004
#define IDC_TCMANUALSTACK_SEARCHGROUPS_REMOVE   1005
#define IDC_TCMANUALSTACK_SEARCHGROUPS_REMOVEALL   1006
#define IDC_TCMANUALSTACK_SEARCHGROUPS_CONTENTS   1007
#define IDC_TCMANUALSTACK_SEARCHGROUPS_FUNCTIONS_STATIC   1008
#define IDC_TCMANUALSTACK_SEARCHGROUPS_SEQUENCES_STATIC   1009
#define IDC_TCMANUALSTACK_SEARCHGROUPS_STACKS_STATIC   1010
#define IDC_TCMANUALSTACK_SEARCHGROUPS_LIST   1011
#define IDC_TCMANUALSTACK_SEARCHGROUPS_MEMBERS_STATIC   1012
#define IDC_TCMANUALSTACK_SEARCHGROUPS_MEMBERS   1013
#define IDC_TCMANUALSTACK_SEARCHGROUPS_MEMBER_ADD   1014
#define IDC_TCMANUALSTACK_SEARCHGROUPS_MEMBER_REMOVE   1015
#define IDC_TCMANUALSTACK_SEARCHGROUPS_MEMBER_REMOVEALL   1016
#define IDC_TCMANUALSTACK_SEARCHGROUPS_HELP   1017

class CTCManualStackSearchGroupsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchGroupsDialog)

	// Construction
public:
	CTCManualStackSearchGroupsDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nType;
	CString  m_szGroup;
	CDatabaseTCFunctions  m_pFunctions;
	CDatabaseTCSequences  m_pSequences;
	CTCManualStackSearchGroups  m_pGroups[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchGroupsDialog)
	enum { IDD = IDD_TCMANUALSTACK_SEARCHGROUPS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, UINT nType, LPCTSTR pszGroup);
	INT Create(CWnd *pParentWnd, CONST CDatabaseTCFunctions &pFunctions);
	INT Create(CWnd *pParentWnd, CONST CDatabaseTCSequences &pSequences);

	class CTCManualStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumGroups();
	BOOL EnumTelecommands();

	VOID ShowContents();

	CTCManualStackSearchGroup *FindGroup() CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchGroupsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchGroupsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnAddMember();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeTelecommand();
	afx_msg void OnEditchangeName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchFilterDialog dialog

#define IDC_TCMANUALSTACK_SEARCHFILTER_DETAILS   1001
#define IDC_TCMANUALSTACK_SEARCHFILTER_NAME_STATIC  1002
#define IDC_TCMANUALSTACK_SEARCHFILTER_NAME   1003
#define IDC_TCMANUALSTACK_SEARCHFILTER_KEY_STATIC   1004
#define IDC_TCMANUALSTACK_SEARCHFILTER_KEY   1005
#define IDC_TCMANUALSTACK_SEARCHFILTER_VALUE_STATIC   1006
#define IDC_TCMANUALSTACK_SEARCHFILTER_VALUE   1007
#define IDC_TCMANUALSTACK_SEARCHFILTER_EXAMPLE_STATIC   1008
#define IDC_TCMANUALSTACK_SEARCHFILTER_EXAMPLE   1009
#define IDC_TCMANUALSTACK_SEARCHFILTER_ADD   1010
#define IDC_TCMANUALSTACK_SEARCHFILTER_REMOVE   1011
#define IDC_TCMANUALSTACK_SEARCHFILTER_REMOVEALL   1012
#define IDC_TCMANUALSTACK_SEARCHFILTER_KEYSLIST   1013
#define IDC_TCMANUALSTACK_SEARCHFILTER_HELP   1014

class CTCManualStackSearchFilterDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchFilterDialog)

	// Construction
public:
	CTCManualStackSearchFilterDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szFilterExamples;
	CTCManualStackSearchFilter  m_cFilter[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchFilterDialog)
	enum { IDD = IDD_TCMANUALSTACK_SEARCHFILTER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCManualStackSearchFilter *pFilter);

private:
	BOOL EnumSearchKeys();

	VOID ShowFilterInfo();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchFilterDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchFilterDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddSearchKey();
	afx_msg void OnRemoveSearchKey();
	afx_msg void OnRemoveAllSearchKeys();
	afx_msg void OnSelchangeSearchKey();
	afx_msg void OnSelchangeKeyValue();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeKeyValue();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesParametersCalibrationPage dialog

#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCManualStackItemPropertiesParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesParametersCalibrationPage)

	// Construction
public:
	CTCManualStackItemPropertiesParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CUIntArray  m_nCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemPropertiesParametersCalibrationPage)
	enum { IDD = IDD_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);

	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCManualStackItemPropertiesParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemPropertiesParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesParametersFolderTabCtrl window

class CTCManualStackItemPropertiesParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCManualStackItemPropertiesParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackItemPropertiesParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesParametersFolder

class CTCManualStackItemPropertiesParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesParametersFolder)

	// Construction
public:
	CTCManualStackItemPropertiesParametersFolder();

	// Attributes
private:
	CTCManualStackItemPropertiesParametersFolderTabCtrl  m_wndTabCtrl;
	CTCManualStackItemPropertiesParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCManualStackItemPropertiesParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackItemPropertiesParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesParametersDialog dialog

#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_ITEM_STATIC   1002
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_ITEM   1003
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_FOLDER   1004
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_HELP   1005

class CTCManualStackItemPropertiesParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesParametersDialog)

	// Construction
public:
	CTCManualStackItemPropertiesParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szParameter;
private:
	CTCManualStackItemPropertiesParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemPropertiesParametersDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMPROPERTIESPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter, CString &szValue);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CDisplayDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemPropertiesParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesParameterSetsDialog dialog

#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERSETS_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERSETS_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERSETS_NAME   1003
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERSETS_CONTENTS_STATIC   1004
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERSETS_CONTENTS   1005
#define IDC_TCMANUALSTACK_ITEMPROPERTIESPARAMETERSETS_HELP   1006

class CTCManualStackItemPropertiesParameterSetsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesParameterSetsDialog)

	// Construction
public:
	CTCManualStackItemPropertiesParameterSetsDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackItem  m_cItem;
	CString  m_szParameterSet;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemPropertiesParameterSetsDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMPROPERTIESPARAMETERSETS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCManualStackItem *pItem, CString &szParameterSet);

private:
	BOOL EnumParameterSets();

	VOID ShowParameterSetContents();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesParameterSetsDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemPropertiesParameterSetsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeSet();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesSaveTemplateDialog dialog

#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_NAME   1003
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_DESCRIPTION_STATIC   1004
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_DESCRIPTION   1005
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_LIST_STATIC   1006
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_LIST   1007
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_REMOVE   1008
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_REMOVEALL   1009
#define IDC_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_HELP   1010

class CTCManualStackItemPropertiesSaveTemplateDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesSaveTemplateDialog)

	// Construction
public:
	CTCManualStackItemPropertiesSaveTemplateDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackItem  m_cItem;
	CTCManualStackComposedItem  m_cComposedItem;
	CTCManualStackItemTemplates  m_pItemTemplates[2];
	CTCManualStackComposedItemTemplates  m_pComposedItemTemplates[2];
	CStringArray  m_szTemplates;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemPropertiesSaveTemplateDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMPROPERTIESSAVETEMPLATE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCManualStackItem *pItem);
	INT Create(CWnd *pParentWnd, CONST CTCManualStackComposedItem *pItem);

	CTCManualStackWnd *GetParentDisplay() CONST;

private:
	VOID EnumTemplates();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesSaveTemplateDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemPropertiesSaveTemplateDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRemoveTemplate();
	afx_msg void OnRemoveAllTemplates();
	afx_msg void OnEditchangeTemplateName();
	afx_msg void OnEditchangeTemplateDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesLoadTemplateDialog dialog

#define IDC_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_LIST   1002
#define IDC_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_NAME_STATIC   1003
#define IDC_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_NAME   1004
#define IDC_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_REMOVE   1005
#define IDC_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_REMOVEALL   1006
#define IDC_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_HELP   1007

class CTCManualStackItemPropertiesLoadTemplateDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesLoadTemplateDialog)

	// Construction
public:
	CTCManualStackItemPropertiesLoadTemplateDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackItem  m_cItem;
	CTCManualStackComposedItem  m_cComposedItem;
	CTCManualStackItemTemplates  m_pItemTemplates[2];
	CTCManualStackComposedItemTemplates  m_pComposedItemTemplates[2];
	CStringArray  m_szTemplates;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemPropertiesLoadTemplateDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMPROPERTIESLOADTEMPLATE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCManualStackItem *pItem);
	INT Create(CWnd *pParentWnd, CTCManualStackComposedItem *pItem);

	CTCManualStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTemplates();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesLoadTemplateDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemPropertiesLoadTemplateDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRemoveTemplate();
	afx_msg void OnRemoveAllTemplates();
	afx_msg void OnEditchangeTemplateName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemReleaseConstraintsDialog dialog

#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_INTERLOCK   1002
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_INTERLOCK_NAME   1003
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKS   1004
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKED   1005
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKED_NAME   1006
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKED_RESULT   1007
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_BLOCKED   1008
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_BLOCKED_NAME   1009
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_BLOCKMACRO   1010
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_GROUPED   1011
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW   1012
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_STATIC   1013
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_IMMEDIATELY   1014
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERPREVIOUS   1015
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERPREVIOUS_OFFSET   1016
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERPREVIOUS_STATIC   1017
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERFIRST_STATIC   1018
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERDISPATCH   1019
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERDISPATCH_OFFSET   1020
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERDISPATCH_STATIC   1021
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_OPEN   1022
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_OPENTIME   1023
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_STATIC   1024
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_INTERVAL   1025
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_INTERVAL_PERIOD   1026
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_INTERVAL_STATIC   1027
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_CLOSE   1028
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_CLOSETIME   1029
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_CLOSETIME_STATIC   1030
#define IDC_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_HELP   1031

// Specify the telecommand manual stack release constraints related limits
#define TCMANUALSTACKITEMRELEASECONSTRAINTSDIALOG_MINIMUMTIMEWINDOWINTERVAL   1
#define TCMANUALSTACKITEMRELEASECONSTRAINTSDIALOG_MAXIMUMTIMEWINDOWINTERVAL   SECONDSPERDAY
#define TCMANUALSTACKITEMRELEASECONSTRAINTSDIALOG_DEFAULTTIMEWINDOWINTERVAL   SECONDSPERMINUTE

class CTCManualStackItemReleaseConstraintsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemReleaseConstraintsDialog)

	// Construction
public:
	CTCManualStackItemReleaseConstraintsDialog();   // standard constructor

	// Attributes
private:
	INT  m_nItemIndex;
	CTCManualStackItem  m_cItem[2];
	CTCManualStackComposedItem  m_cComposedItem[2];
private:
	CTCInterlocks  m_pInterlocks[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemReleaseConstraintsDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMRELEASECONSTRAINTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCManualStackItem *pItem);
	INT Create(CWnd *pParentWnd, CTCManualStackComposedItem *pComposedItem, INT nIndex = 0);

	CTCManualStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumInterlocks();
	BOOL EnumBlocks();

	VOID ShowConstraints();

	BOOL CheckTCVerificationStage(CONST CTCManualStackItem *pItem, UINT nStage) CONST;

	BOOL CheckPrivileges() CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemReleaseConstraintsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemReleaseConstraintsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnInterlock();
	afx_msg void OnInterlocks();
	afx_msg void OnInterlocked();
	afx_msg void OnBlocked();
	afx_msg void OnBlockMacro();
	afx_msg void OnGrouped();
	afx_msg void OnTimeWindowImmediately();
	afx_msg void OnTimeWindowAfterPrevious();
	afx_msg void OnTimeWindowAfterDispatch();
	afx_msg void OnTimeWindowOpen();
	afx_msg void OnTimeWindowClose();
	afx_msg void OnTimeWindowInterval();
	afx_msg void OnSelchangeInterlock();
	afx_msg void OnSelchangeInterlocked();
	afx_msg void OnSelchangeInterlockedResult();
	afx_msg void OnSpinchangeTimeWindowAfterPrevious();
	afx_msg void OnSpinchangeTimeWindowAfterDispatch();
	afx_msg void OnSpinchangeTimeWindowOpen();
	afx_msg void OnSpinchangeTimeWindowClose();
	afx_msg void OnSpinchangeTimeWindowInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemReleaseInterlocksDialog dialog

#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_NAME   1003
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_ADD   1004
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_REMOVE   1005
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_REMOVEALL   1006
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES   1007
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_STATIC   1008
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_GLOBAL   1009
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_LOCAL   1010
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM   1011
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME   1012
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS   1013
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE   1014
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_STATIC   1015
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_RECEPTION   1016
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION   1017
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE   1018
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_START   1019
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_PROGRESS   1020
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_COMPLETION   1021
#define IDC_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_HELP   1022

class CTCManualStackItemReleaseInterlocksDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemReleaseInterlocksDialog)

	// Construction
public:
	CTCManualStackItemReleaseInterlocksDialog();   // standard constructor

	// Attributes
private:
	ULONGLONG  m_nInterlockFlags;
	CTCInterlocks  m_pInterlocks[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemReleaseInterlocksDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMRELEASEINTERLOCKS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, ULONGLONG nInterlockFlags, CTCInterlocks &pInterlocks);

private:
	BOOL EnumInterlocks();
	BOOL EnumSubSystems();

	VOID ShowProperties();

	CTCInterlock *FindInterlock() CONST;

	UINT TranslateToSubSystemID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

	BOOL CanAddInterlock() CONST;
	BOOL CanRemoveInterlock() CONST;
	BOOL CanRemoveAllInterlocks() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemReleaseInterlocksDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemReleaseInterlocksDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnScopeGlobal();
	afx_msg void OnScopeLocal();
	afx_msg void OnScopeSubSystem();
	afx_msg void OnScopeTeleommands();
	afx_msg void OnScopeNoWaitState();
	afx_msg void OnStageReception();
	afx_msg void OnStageTransmission();
	afx_msg void OnStageAcceptance();
	afx_msg void OnStageStart();
	afx_msg void OnStageProgress();
	afx_msg void OnStageCompletion();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeSubSystem();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemReleaseBlockMacroDialog dialog

#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_NAME   1003
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_DESCRIPTION_STATIC   1004
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_DESCRIPTION   1005
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_MEMBERS_STATIC   1006
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_MEMBERS   1007
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_STATIC   1008
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS   1009
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_ADD   1010
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_REMOVE   1011
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_REMOVEALL   1012
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_REMARK   1013
#define IDC_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_HELP   1014

class CTCManualStackItemReleaseBlockMacroDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemReleaseBlockMacroDialog)

	// Construction
public:
	CTCManualStackItemReleaseBlockMacroDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackComposedItem  m_cItem[2];
	CStringArray  m_szMembers;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemReleaseBlockMacroDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMRELEASEBLOCKMACRO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCManualStackComposedItem *pItem);

	CTCManualStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumBlockMembers();

	VOID ShowMacroContents();
	BOOL CheckMacroSize() CONST;

	BOOL CheckPrivileges() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemReleaseBlockMacroDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemReleaseBlockMacroDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddMember();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackItemPropertiesDialog dialog

#define IDC_TCMANUALSTACK_ITEMPROPERTIES_DETAILS   1001
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_NAME   1003
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS   1006
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV   1007
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV   1008
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV   1009
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_DISABLEPTV   1010
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_DISABLEPEV   1011
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_DISABLECEV   1012
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED   1013
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_CONSTRAINTS_RELEASE   1014
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION   1015
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY   1016
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG   1017
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME   1018
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT   1019
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_COUNT   1020
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_STATIC   1021
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_TIME_STATIC   1022
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_TIME   1023
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_2STEP   1024
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS   1025
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_ACCEPTANCE   1026
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_START   1027
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_PROGRESS   1028
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_COMPLETION   1029
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS   1030
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_LIST   1031
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_REMARK   1032
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_NOEXTRAPOLATION   1033
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_SHOWALL   1034
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_VALUE_STATIC   1035
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_VALUE   1036
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_SETVALUE   1037
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_LOADVALUES   1038
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_PARAMETERS_LOADDYNAMICVALUE   1039
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_SAVETEMPLATE   1040
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_LOADTEMPLATE   1041
#define IDC_TCMANUALSTACK_ITEMPROPERTIES_HELP   1042

class CTCManualStackItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackItemPropertiesDialog)

	// Construction
public:
	CTCManualStackItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackItem  m_cItem[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackItemPropertiesDialog)
	enum { IDD = IDD_TCMANUALSTACK_ITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCManualStackItem *pItem);

	CTCManualStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();
	VOID ShowParameters();

	VOID EvaluateParameters();

	BOOL HasTemplates() CONST;

	BOOL CheckTCVerificationStage(UINT nStage) CONST;
	BOOL CheckTCParameterValue(CONST CDatabaseTCFunctionElement *pFunctionElement) CONST;
	BOOL CheckTCParameterValue(CONST CDatabaseTCPacketParameter *pPacketParameter) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	BOOL CheckPrivileges() CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackItemPropertiesDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnOverridePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisablePTV();
	afx_msg void OnDisablePEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnPreAuthorize();
	afx_msg void OnReleaseConstraints();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnExecuteAtOBRT();
	afx_msg void OnExecuteAs2Step();
	afx_msg void OnAcknowledgeAcceptance();
	afx_msg void OnAcknowledgeStart();
	afx_msg void OnAcknowledgeProgress();
	afx_msg void OnAcknowledgeCompletion();
	afx_msg void OnNoExtrapolation();
	afx_msg void OnShowAllParameters();
	afx_msg void OnSetParameterValue();
	afx_msg void OnLoadParameterValues();
	afx_msg void OnLoadDynamicParameterValue();
	afx_msg void OnSaveTemplate();
	afx_msg void OnLoadTemplate();
	afx_msg void OnEditchangeParameterValue();
	afx_msg void OnEditchangeExecutionOBRT();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackComposedItemPropertiesDialog dialog

#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_DETAILS   1001
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_NAME   1003
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_STATIC   1006
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY   1007
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_APPLYTOALL   1008
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PROPERTIES   1009
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS   1010
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV   1011
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV   1012
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV   1013
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV   1014
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV   1015
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV   1016
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED   1017
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASE   1018
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION   1019
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY   1020
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG   1021
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME   1022
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OFFSET   1023
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OFFSET_TIME   1024
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OFFSET_AFTERPREVIOUS   1025
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT   1026
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_COUNT   1027
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_STATIC   1028
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_TIME_STATIC   1029
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_TIME   1030
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_2STEP   1031
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS   1032
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST   1033
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK   1034
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_NOEXTRAPOLATION   1035
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL   1036
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST   1037
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_VALUE_STATIC   1038
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_VALUE   1039
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SETVALUE   1040
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LOADVALUES   1041
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LOADDYNAMICVALUE   1042
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_SAVETEMPLATE   1043
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_LOADTEMPLATE   1044
#define IDC_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_HELP   1045

// Specify the telecommand manual stack composed item properties related limits
#define TCMANUALSTACKCOMPOSEDITEMPROPERTIESDIALOG_MINIMUMEXECUTIONTIMEOFFSET   -(365*SECONDSPERDAY)
#define TCMANUALSTACKCOMPOSEDITEMPROPERTIESDIALOG_MAXIMUMEXECUTIONTIMEOFFSET   (365*SECONDSPERDAY)
#define TCMANUALSTACKCOMPOSEDITEMPROPERTIESDIALOG_DEFAULTEXECUTIONTIMEOFFSET   0

class CTCManualStackComposedItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackComposedItemPropertiesDialog)

	// Construction
public:
	CTCManualStackComposedItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackComposedItem  m_cItem[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackComposedItemPropertiesDialog)
	enum { IDD = IDD_TCMANUALSTACK_COMPOSEDITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCManualStackComposedItem *pItem);

	CTCManualStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumEntries();

	VOID ShowProperties();
	VOID ShowParameters();

	VOID EvaluateParameters();

	BOOL HasTemplates() CONST;

	BOOL CheckTCParameterValue(CONST CDatabaseTCFunctionElement *pFunctionElement) CONST;
	BOOL CheckTCParameterValue(CONST CDatabaseTCPacketParameter *pPacketParameter) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	BOOL CheckPrivileges() CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackComposedItemPropertiesDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackComposedItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnApplyToAll();
	afx_msg void OnOverridePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisablePTV();
	afx_msg void OnDisablePEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnPreAuthorize();
	afx_msg void OnReleaseConstraints();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnExecuteAtOffset();
	afx_msg void OnExecuteAtOffsetAfterPrevious();
	afx_msg void OnExecuteAtOBRT();
	afx_msg void OnExecuteAs2Step();
	afx_msg void OnShowFormalParameters();
	afx_msg void OnNoExtrapolation();
	afx_msg void OnShowAllParameters();
	afx_msg void OnSetParameterValue();
	afx_msg void OnLoadParameterValues();
	afx_msg void OnLoadDynamicParameterValue();
	afx_msg void OnSaveTemplate();
	afx_msg void OnLoadTemplate();
	afx_msg void OnSelchangeEntry();
	afx_msg void OnEditchangeParameterValue();
	afx_msg void OnEditchangeExecutionOBRT();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeExecutionOffset();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSaveContentsDialog dialog

#define IDC_TCMANUALSTACK_SAVECONTENTS_DETAILS   1001
#define IDC_TCMANUALSTACK_SAVECONTENTS_NAME_STATIC   1002
#define IDC_TCMANUALSTACK_SAVECONTENTS_NAME   1003
#define IDC_TCMANUALSTACK_SAVECONTENTS_DESCRIPTION_STATIC   1004
#define IDC_TCMANUALSTACK_SAVECONTENTS_DESCRIPTION   1005
#define IDC_TCMANUALSTACK_SAVECONTENTS_OPTIONS_STATIC   1006
#define IDC_TCMANUALSTACK_SAVECONTENTS_OPTIONS_RELATIVERELEASETIMES   1007
#define IDC_TCMANUALSTACK_SAVECONTENTS_OPTIONS_RELATIVEEXECUTIONTIMES   1008
#define IDC_TCMANUALSTACK_SAVECONTENTS_STATUS_STATIC   1009
#define IDC_TCMANUALSTACK_SAVECONTENTS_STATUS_VALIDATED   1010
#define IDC_TCMANUALSTACK_SAVECONTENTS_LIST   1011
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY   1012
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_FILENAME_STATIC   1013
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_FILENAME   1014
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_FILENAME_BROWSE   1015
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_FILENAME_INSPECT   1016
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_FILENAME_REMARK   1017
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_LIST   1018
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_LIST_REMOVE   1019
#define IDC_TCMANUALSTACK_SAVECONTENTS_REPOSITORY_LIST_REMOVEALL  1020
#define IDC_TCMANUALSTACK_SAVECONTENTS_HELP   1021

class CTCManualStackSaveContentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackSaveContentsDialog)

	// Construction
public:
	CTCManualStackSaveContentsDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackItems  m_pItems[2];
private:
	CStringArray  m_szColumns[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSaveContentsDialog)
	enum { IDD = IDD_TCMANUALSTACK_SAVECONTENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCManualStackItems &pItems);

	class CTCManualStackWnd *GetParent() CONST;

private:
	BOOL EnumStackMembers();
	BOOL EnumRepositoryMembers();

	BOOL SaveRepository(CFileEx &cFile, CONST CTCSavedStacks &pStacks);
	BOOL SaveRepository(LPCTSTR pszFileName, CONST CTCSavedStacks &pStacks);
	BOOL LoadRepository(CFileEx &cFile, CTCSavedStacks &pStacks) CONST;
	BOOL LoadRepository(LPCTSTR pszFileName, CTCSavedStacks &pStacks) CONST;

	BOOL LogActivity(LPCTSTR pszFileName, BOOL bDeleted = FALSE);
	BOOL LogActivity(CONST CTCSavedStack *pStack, BOOL bDeleted = FALSE);

	INT FindColumnIndex(UINT nID, LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSaveContentsDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSaveContentsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRelativeReleaseTimes();
	afx_msg void OnRelativeExecutionTimes();
	afx_msg void OnBrowseFileName();
	afx_msg void OnInspectRepository();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackLoadContentsDialog dialog

#define IDC_TCMANUALSTACK_LOADCONTENTS_DETAILS   1001
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILENAME_STATIC   1002
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILENAME   1003
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILENAME_BROWSE   1004
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILENAME_INSPECT   1005
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILENAME_DELETE   1006
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILTER_STATIC   1007
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILTER   1008
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILTER_ADD   1009
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILTER_MODIFY   1010
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILTER_REMOVE   1011
#define IDC_TCMANUALSTACK_LOADCONTENTS_FILTER_REMOVEALL   1012
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES   1013
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_LIST   1014
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_LIST_REMOVE   1015
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_LIST_REMOVEALL   1016
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_VALIDATE   1017
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_LOADANYWAY   1018
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_REMARK   1019
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_CONTENTS_STATIC   1020
#define IDC_TCMANUALSTACK_LOADCONTENTS_PROPERTIES_CONTENTS_LIST   1021
#define IDC_TCMANUALSTACK_LOADCONTENTS_HELP   1022

class CTCManualStackLoadContentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackLoadContentsDialog)

	// Construction
public:
	CTCManualStackLoadContentsDialog();   // standard constructor

	// Attributes
private:
	CTCSavedStacks  m_pRepository;
	CTCManualStackItems  m_pItems;
	CTCManualStackSearchFilters  m_pFilters;
private:
	CStringArray  m_szColumns[2];

	// Dialog Data
	//{{AFX_DATA(CTCManualStackLoadContentsDialog)
	enum { IDD = IDD_TCMANUALSTACK_LOADCONTENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCManualStackWnd *GetParent() CONST;

private:
	BOOL EnumFilters();
	BOOL EnumRepositoryMembers();
	BOOL EnumStackMembers();

	BOOL SaveRepository(CFileEx &cFile, CONST CTCSavedStacks &pStacks);
	BOOL SaveRepository(LPCTSTR pszFileName, CONST CTCSavedStacks &pStacks);
	BOOL LoadRepository(CFileEx &cFile, CTCSavedStacks &pStacks) CONST;
	BOOL LoadRepository(LPCTSTR pszFileName, CTCSavedStacks &pStacks) CONST;

	BOOL LogActivity(LPCTSTR pszFileName, BOOL bDeleted = FALSE);
	BOOL LogActivity(CONST CTCSavedStack *pStack, BOOL bDeleted = FALSE);

	BOOL CheckFilter(CONST CTCSavedStack *pStack) CONST;

	INT ExtractFilterValues(LPCTSTR pszValues, CStringArray &szSearchValues, CUIntArray &nSearchOperators) CONST;
	CString ExtractFilterValue(LPCTSTR pszValue) CONST;

	INT FindColumnIndex(UINT nID, LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackLoadContentsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackLoadContentsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnInspectRepository();
	afx_msg void OnDeleteRepository();
	afx_msg void OnAddFilter();
	afx_msg void OnModifyFilter();
	afx_msg void OnRemoveFilter();
	afx_msg void OnRemoveAllFilters();
	afx_msg void OnValidateMember();
	afx_msg void OnLoadMemberAnyway();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFilter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackLoadCommandDialog dialog

#define IDC_TCMANUALSTACK_LOADCOMMAND_DETAILS   1001
#define IDC_TCMANUALSTACK_LOADCOMMAND_SOURCE_STATIC   1002
#define IDC_TCMANUALSTACK_LOADCOMMAND_SOURCE   1003
#define IDC_TCMANUALSTACK_LOADCOMMAND_GROUPS   1004
#define IDC_TCMANUALSTACK_LOADCOMMAND_TYPE_STATIC   1005
#define IDC_TCMANUALSTACK_LOADCOMMAND_TYPE_FUNCTIONS   1006
#define IDC_TCMANUALSTACK_LOADCOMMAND_TYPE_SEQUENCES   1007
#define IDC_TCMANUALSTACK_LOADCOMMAND_TYPE_FUNCTIONITEMS   1008
#define IDC_TCMANUALSTACK_LOADCOMMAND_TYPE_SEQUENCEITEMS   1009
#define IDC_TCMANUALSTACK_LOADCOMMAND_FILTER_STATIC   1010
#define IDC_TCMANUALSTACK_LOADCOMMAND_FILTER   1011
#define IDC_TCMANUALSTACK_LOADCOMMAND_FILTER_ADD   1012
#define IDC_TCMANUALSTACK_LOADCOMMAND_FILTER_MODIFY   1013
#define IDC_TCMANUALSTACK_LOADCOMMAND_FILTER_REMOVE   1014
#define IDC_TCMANUALSTACK_LOADCOMMAND_FILTER_REMOVEALL   1015
#define IDC_TCMANUALSTACK_LOADCOMMAND_NAME_LIST   1016
#define IDC_TCMANUALSTACK_LOADCOMMAND_NAME_STATIC   1017
#define IDC_TCMANUALSTACK_LOADCOMMAND_NAME   1018
#define IDC_TCMANUALSTACK_LOADCOMMAND_NAME_PROPERTIES   1019
#define IDC_TCMANUALSTACK_LOADCOMMAND_HELP   1020

class CTCManualStackLoadCommandDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackLoadCommandDialog)

	// Construction
public:
	CTCManualStackLoadCommandDialog();   // standard constructor

	// Attributes
private:
	CTCManualStackItem  m_cItem;
	CDatabaseTCFunctions  m_pFunctions;
	CDatabaseTCSequences  m_pSequences;
	CTCManualStackComposedItem  m_cComposedItem;
	CTCManualStackSearchGroups  m_pGroups[TCMANUALSTACKSEARCHGROUP_TYPES - 1];
	CTCManualStackSearchFilters  m_pFilters[TCMANUALSTACKSEARCHFILTER_TYPES - 1];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackLoadCommandDialog)
	enum { IDD = IDD_TCMANUALSTACK_LOADCOMMAND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCManualStackWnd *GetParent() CONST;

private:
	BOOL EnumSources();
	BOOL EnumFilters();

	VOID ShowSourceContents();

	BOOL InitializeDefaults(CONST CDatabaseTCFunction *pFunction, CTCManualStackItem *pItem) CONST;
	BOOL InitializeDefaults(CONST CDatabaseTCSequence *pSequence, CONST CDatabaseTCSequenceEntry *pSequenceEntry, ULONGLONG nAttributes, DWORD dwReleaseOffset, DWORD dwExecutionOffset, BOOL bEarlierExecution, CTCManualStackComposedItem *pComposedItem, CTCManualStackItem *pItem) CONST;

	BOOL CheckFilter(CONST CDatabaseTCFunction *pFunction) CONST;
	BOOL CheckFilter(CONST CDatabaseTCSequence *pSequence) CONST;
	BOOL CheckTelecommand(CONST CTCManualStackItem *pItem) CONST;
	BOOL CheckTelecommand(CONST CTCManualStackComposedItem *pComposedItem) CONST;

	INT ExtractFilterValues(LPCTSTR pszValues, CStringArray &szSearchValues, CUIntArray &nSearchOperators) CONST;
	CString ExtractFilterValue(LPCTSTR pszValue) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackLoadCommandDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackLoadCommandDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnGroups();
	afx_msg void OnTCFunctions();
	afx_msg void OnTCSequences();
	afx_msg void OnAddFilter();
	afx_msg void OnModifyFilter();
	afx_msg void OnRemoveFilter();
	afx_msg void OnRemoveAllFilters();
	afx_msg void OnTelecommandProperties();
	afx_msg void OnEditchangeTelecommand();
	afx_msg void OnSelchangeSource();
	afx_msg void OnSelchangeFilter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackInterlocksDialog dialog

#define IDC_TCMANUALSTACK_INTERLOCKS_DETAILS   1001
#define IDC_TCMANUALSTACK_INTERLOCKS_LIST   1002
#define IDC_TCMANUALSTACK_INTERLOCKS_RESET   1003
#define IDC_TCMANUALSTACK_INTERLOCKS_RESETALL   1004
#define IDC_TCMANUALSTACK_INTERLOCKS_HELP   1005

class CTCManualStackInterlocksDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCManualStackInterlocksDialog)

	// Construction
public:
	CTCManualStackInterlocksDialog();   // standard constructor

	// Attributes
private:
	CTCInterlocks  m_pInterlocks[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCManualStackInterlocksDialog)
	enum { IDD = IDD_TCMANUALSTACK_INTERLOCKS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCInterlocks &pInterlocks);

private:
	BOOL EnumInterlocks();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackInterlocksDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackInterlocksDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReset();
	afx_msg void OnResetAll();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchNumberDialog dialog

class CTCManualStackSearchNumberDialog : public CTCStackSearchNumberDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchNumberDialog)

	// Construction
public:
	CTCManualStackSearchNumberDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchNumberDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchNumberDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchNumberDialog)
	afx_msg void OnGotoNumber();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchNameDialog dialog

class CTCManualStackSearchNameDialog : public CTCStackSearchNameDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchNameDialog)

	// Construction
public:
	CTCManualStackSearchNameDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchNameDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchNameDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchNameDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchDescriptionDialog dialog

class CTCManualStackSearchDescriptionDialog : public CTCStackSearchDescriptionDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchDescriptionDialog)

	// Construction
public:
	CTCManualStackSearchDescriptionDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchDescriptionDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchDescriptionDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchDescriptionDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchCategoryDialog dialog

class CTCManualStackSearchCategoryDialog : public CTCStackSearchCategoryDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchCategoryDialog)

	// Construction
public:
	CTCManualStackSearchCategoryDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchCategoryDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchCategoryDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchCategoryDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchSubSystemDialog dialog

class CTCManualStackSearchSubSystemDialog : public CTCStackSearchSubSystemDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchSubSystemDialog)

	// Construction
public:
	CTCManualStackSearchSubSystemDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchSubSystemDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchSubSystemDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchSubSystemDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchArgumentsDialog dialog

class CTCManualStackSearchArgumentsDialog : public CTCStackSearchArgumentsDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchArgumentsDialog)

	// Construction
public:
	CTCManualStackSearchArgumentsDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchArgumentsDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchArgumentsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchArgumentsDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchFlagsDialog dialog

class CTCManualStackSearchFlagsDialog : public CTCStackSearchFlagsDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchFlagsDialog)

	// Construction
public:
	CTCManualStackSearchFlagsDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchFlagsDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchFlagsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchFlagsDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchTCPacketDialog dialog

class CTCManualStackSearchTCPacketDialog : public CTCStackSearchTCPacketDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchTCPacketDialog)

	// Construction
public:
	CTCManualStackSearchTCPacketDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchTCPacketDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchTCPacketDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchTCPacketDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchDispatchTimeDialog dialog

class CTCManualStackSearchDispatchTimeDialog : public CTCStackSearchDispatchTimeDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchDispatchTimeDialog)

	// Construction
public:
	CTCManualStackSearchDispatchTimeDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchDispatchTimeDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchDispatchTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchDispatchTimeDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchReleaseTimeDialog dialog

class CTCManualStackSearchReleaseTimeDialog : public CTCStackSearchReleaseTimeDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchReleaseTimeDialog)

	// Construction
public:
	CTCManualStackSearchReleaseTimeDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchReleaseTimeDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchReleaseTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchReleaseTimeDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchReleaseTimeOffsetDialog dialog

class CTCManualStackSearchReleaseTimeOffsetDialog : public CTCStackSearchReleaseTimeOffsetDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchReleaseTimeOffsetDialog)

	// Construction
public:
	CTCManualStackSearchReleaseTimeOffsetDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchReleaseTimeOffsetDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchReleaseTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchReleaseTimeOffsetDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchExecutionTimeDialog dialog

class CTCManualStackSearchExecutionTimeDialog : public CTCStackSearchExecutionTimeDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchExecutionTimeDialog)

	// Construction
public:
	CTCManualStackSearchExecutionTimeDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchExecutionTimeDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchExecutionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchExecutionTimeDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchExecutionTimeOffsetDialog dialog

class CTCManualStackSearchExecutionTimeOffsetDialog : public CTCStackSearchExecutionTimeOffsetDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchExecutionTimeOffsetDialog)

	// Construction
public:
	CTCManualStackSearchExecutionTimeOffsetDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchExecutionTimeOffsetDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchExecutionTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchExecutionTimeOffsetDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchAuthorizationDialog dialog

class CTCManualStackSearchAuthorizationDialog : public CTCStackSearchAuthorizationDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchAuthorizationDialog)

	// Construction
public:
	CTCManualStackSearchAuthorizationDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchAuthorizationDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchAuthorizationDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchAuthorizationDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchPTVTimeWindowDialog dialog

class CTCManualStackSearchPTVTimeWindowDialog : public CTCStackSearchPTVTimeWindowDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchPTVTimeWindowDialog)

	// Construction
public:
	CTCManualStackSearchPTVTimeWindowDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchPTVTimeWindowDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchPTVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchPTVTimeWindowDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchPTVCheckDialog dialog

class CTCManualStackSearchPTVCheckDialog : public CTCStackSearchPTVCheckDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchPTVCheckDialog)

	// Construction
public:
	CTCManualStackSearchPTVCheckDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchPTVCheckDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchPTVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchPTVCheckDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchPTVResultDialog dialog

class CTCManualStackSearchPTVResultDialog : public CTCStackSearchPTVResultDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchPTVResultDialog)

	// Construction
public:
	CTCManualStackSearchPTVResultDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchPTVResultDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchPTVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchPTVResultDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchPEVCheckDialog dialog

class CTCManualStackSearchPEVCheckDialog : public CTCStackSearchPEVCheckDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchPEVCheckDialog)

	// Construction
public:
	CTCManualStackSearchPEVCheckDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchPEVCheckDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchPEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchPEVCheckDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchPEVResultDialog dialog

class CTCManualStackSearchPEVResultDialog : public CTCStackSearchPEVResultDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchPEVResultDialog)

	// Construction
public:
	CTCManualStackSearchPEVResultDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchPEVResultDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchPEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchPEVResultDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchCEVTimeWindowDialog dialog

class CTCManualStackSearchCEVTimeWindowDialog : public CTCStackSearchCEVTimeWindowDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchCEVTimeWindowDialog)

	// Construction
public:
	CTCManualStackSearchCEVTimeWindowDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchCEVTimeWindowDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchCEVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchCEVTimeWindowDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchCEVCheckDialog dialog

class CTCManualStackSearchCEVCheckDialog : public CTCStackSearchCEVCheckDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchCEVCheckDialog)

	// Construction
public:
	CTCManualStackSearchCEVCheckDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchCEVCheckDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchCEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchCEVCheckDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackSearchStatusDialog dialog

class CTCManualStackSearchStatusDialog : public CTCStackSearchStatusDialog
{
	DECLARE_DYNCREATE(CTCManualStackSearchStatusDialog)

	// Construction
public:
	CTCManualStackSearchStatusDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCManualStackSearchStatusDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCManualStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackSearchStatusDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCManualStackSearchStatusDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackToolBar window

class CTCManualStackToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTCManualStackToolBar)

	// Construction
public:
	CTCManualStackToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackStatusBar window

class CTCManualStackStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTCManualStackStatusBar)

	// Construction
public:
	CTCManualStackStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTCManualStackWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackToolTip window

class CTCManualStackToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTCManualStackToolTip)

	// Construction
public:
	CTCManualStackToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackView window

// Specify the telecommand manual stack command flag symbol identifiers
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOL_INTERLOCK   0
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOL_INTERLOCKIDLE   1
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOL_INTERLOCKPENDING   2
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOL_INTERLOCKSUCCESS   3
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOL_INTERLOCKFAILURE   4
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOL_GROUPED   5
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOL_BLOCKED   6
#define TCMANUALSTACKVIEW_COMMANDFLAGSYMBOLS   7
// Specify the telecommand manual stack command check flag symbol identifiers
#define TCMANUALSTACKVIEW_COMMANDCHECKFLAGSYMBOL_NONE   0
#define TCMANUALSTACKVIEW_COMMANDCHECKFLAGSYMBOL_ON   1
#define TCMANUALSTACKVIEW_COMMANDCHECKFLAGSYMBOL_OFF   2
#define TCMANUALSTACKVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED   3
#define TCMANUALSTACKVIEW_COMMANDCHECKFLAGSYMBOLS   4
// Specify the telecommand manual stack command result symbol identifiers
#define TCMANUALSTACKVIEW_COMMANDRESULTSYMBOL_PTV_GO   0
#define TCMANUALSTACKVIEW_COMMANDRESULTSYMBOL_PTV_WAIT   1
#define TCMANUALSTACKVIEW_COMMANDRESULTSYMBOL_PTV_FAIL   2
#define TCMANUALSTACKVIEW_COMMANDRESULTSYMBOL_PEV_GO   3
#define TCMANUALSTACKVIEW_COMMANDRESULTSYMBOL_PEV_NOGO   4
#define TCMANUALSTACKVIEW_COMMANDRESULTSYMBOLS   5
// Specify the telecommand manual stack command alert symbol identifiers
#define TCMANUALSTACKVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCMANUALSTACKVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCMANUALSTACKVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCMANUALSTACKVIEW_COMMANDALERTSYMBOLS   3
// Specify the telecommand manual stack command update timer identifiers
#define TCMANUALSTACKVIEW_COMMANDUPDATE_TIMERID   100
#define TCMANUALSTACKVIEW_COMMANDUPDATE_TIMEOUT   1000
// Specify the telecommand manual stack command dispatch timer identifiers
#define TCMANUALSTACKVIEW_COMMANDDISPATCH_TIMERID   101
#define TCMANUALSTACKVIEW_COMMANDDISPATCH_TIMEOUT    15000
// Specify the telecommand manual stack visual aspect related identifiers
#define TCMANUALSTACKVIEW_COLUMNTRANSPARENCY   0x30

class CTCManualStackView : public CTextView
{
	DECLARE_DYNCREATE(CTCManualStackView)

	// Construction
public:
	CTCManualStackView();

	// Attributes
private:
	INT  m_nChecks;
	INT  m_nArguments;
	INT  m_nSearchIndex;
	BOOL  m_bProperties;
	BOOL  m_bAllArguments;
	BOOL  m_bFullViewMode;
	UINT  m_nMiscellaneousOptions;
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	UINT  m_nTelecommandingUplinkState;
	BOOL  m_bTelecommandingInterlockMode;
	BOOL  m_bTelecommandingReleaseWaitMode;
	BOOL  m_bTelecommandingAutoRejectionMode;
	CTimeSpan  m_tDefaultReleaseTimeWindow;
	CTimeSpan  m_tDispatchTimeWindow;
private:
	CSize  m_sizeFlagSymbols;
	CSize  m_sizeAlertSymbols;
	CSize  m_sizeResultSymbols;
	CSize  m_sizeCheckFlagSymbols;
	CImage  *m_pFlagSymbols[TCMANUALSTACKVIEW_COMMANDFLAGSYMBOLS];
	CImage  *m_pCheckFlagSymbols[TCMANUALSTACKVIEW_COMMANDCHECKFLAGSYMBOLS];
	CImage  *m_pResultSymbols[TCMANUALSTACKVIEW_COMMANDRESULTSYMBOLS];
	CImage  *m_pAlertSymbols[TCMANUALSTACKVIEW_COMMANDALERTSYMBOLS];
	CTCManualStackToolTip  m_wndToolTip;
	COLORREF  m_nBackgroundColor[2];
	CUIntArray  m_nDispatchTimerIDs;
	CUIntArray  m_nStatusColors;
	CUIntArray  m_nAlertColors;
	HCURSOR  m_hToolTipCursor;
	UINT  m_nClipboardFormat;
	BOOL  m_bToolTips;
private:
	CTCProcessEngine  *m_pTCProcessEngine;
	CTCEnvironment  *m_pTCEnvironment;
private:
	CTCInterlocks  m_pInterlocks;
	CTCManualStackItems  m_pItems[2];
private:
	CTCManualStackSearchNameDialog  m_dlgSearchName;
	CTCManualStackSearchFlagsDialog  m_dlgSearchFlags;
	CTCManualStackSearchNumberDialog  m_dlgSearchNumber;
	CTCManualStackSearchStatusDialog  m_dlgSearchStatus;
	CTCManualStackSearchCategoryDialog  m_dlgSearchCategory;
	CTCManualStackSearchTCPacketDialog  m_dlgSearchTCPacket;
	CTCManualStackSearchPTVCheckDialog  m_dlgSearchPTVCheck;
	CTCManualStackSearchPEVCheckDialog  m_dlgSearchPEVCheck;
	CTCManualStackSearchCEVCheckDialog  m_dlgSearchCEVCheck;
	CTCManualStackSearchSubSystemDialog  m_dlgSearchSubSystem;
	CTCManualStackSearchArgumentsDialog  m_dlgSearchArguments;
	CTCManualStackSearchPTVResultDialog  m_dlgSearchPTVResult;
	CTCManualStackSearchPEVResultDialog  m_dlgSearchPEVResult;
	CTCManualStackSearchDescriptionDialog  m_dlgSearchDescription;
	CTCManualStackSearchReleaseTimeDialog  m_dlgSearchReleaseTime;
	CTCManualStackSearchDispatchTimeDialog  m_dlgSearchDispatchTime;
	CTCManualStackSearchExecutionTimeDialog  m_dlgSearchExecutionTime;
	CTCManualStackSearchPTVTimeWindowDialog  m_dlgSearchPTVTimeWindow;
	CTCManualStackSearchCEVTimeWindowDialog  m_dlgSearchCEVTimeWindow;
	CTCManualStackSearchAuthorizationDialog  m_dlgSearchAuthorization;
	CTCManualStackSearchReleaseTimeOffsetDialog  m_dlgSearchReleaseTimeOffset;
	CTCManualStackSearchExecutionTimeOffsetDialog  m_dlgSearchExecutionTimeOffset;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetAlertColors(CONST CUIntArray &nColors);
	BOOL GetAlertColors(CUIntArray &nColors) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCItems &pItems, BOOL bRedraw = TRUE);
	BOOL LoadTelecommands(CONST CTCManualStackItems &pItems, BOOL bReload = FALSE, BOOL bBefore = FALSE, BOOL bAfter = FALSE, BOOL bRedraw = TRUE);
	BOOL LoadTelecommands(CONST CTCManualStackItems &pItems, INT nIndex, BOOL bReload = FALSE, BOOL bBefore = FALSE, BOOL bAfter = FALSE, BOOL bRedraw = TRUE);
	BOOL ReloadTelecommands(CONST CTCManualStackItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);
	BOOL UpdateTelecommands();

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL SelectTelecommand(INT nIndex);
	VOID DoSelectAllTelecommands();
	BOOL CanSelectAllTelecommands() CONST;
	INT EnumSelectedTelecommands(CTCManualStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands() CONST;

	UINT GetTelecommandCount() CONST;

	BOOL DoInsertBeforeTelecommand();
	BOOL CanInsertBeforeTelecommand() CONST;
	BOOL DoInsertAfterTelecommand();
	BOOL CanInsertAfterTelecommand() CONST;
	BOOL DoMoveUpTelecommand();
	BOOL CanMoveUpTelecommand() CONST;
	BOOL DoMoveDownTelecommand();
	BOOL CanMoveDownTelecommand() CONST;

	BOOL DoCutTelecommand();
	BOOL CanCutTelecommand() CONST;
	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoPasteTelecommand();
	BOOL CanPasteTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;
	BOOL DoArmTelecommand();
	BOOL CanArmTelecommand() CONST;
	BOOL DoDispatchTelecommand();
	BOOL CanDispatchTelecommand() CONST;
	BOOL DoUndispatchTelecommand();
	BOOL CanUndispatchTelecommand() CONST;
	BOOL DoAcknowledgeTelecommand();
	BOOL CanAcknowledgeTelecommand() CONST;
	BOOL DoReloadTelecommand();
	BOOL CanReloadTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL SearchTelecommandByNumber(INT nNumber);
	BOOL SearchTelecommandByName(LPCTSTR pszName, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchTelecommandByCategory(LPCTSTR pszCategory, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandBySubSystem(LPCTSTR pszSubSystem, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchTelecommandByArgument(LPCTSTR pszArgument, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByFlags(BOOL bDown, BOOL bAll, BOOL bInterlocking, BOOL bInterlocked, BOOL bGrouped, BOOL bBlocked);
	BOOL SearchTelecommandByTCPacket(LPCTSTR pszPacket, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDispatchTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTimeOffset(DWORD dwOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTimeOffset(CONST CTimeSpan &tOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByAuthorization(UINT nAuthorization, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByStatus(LPCTSTR pszStatus, BOOL bDown, BOOL bAll);

	BOOL GetPrintProperties(CONST CTCManualStackPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	class CTCManualStackWnd *GetParent() CONST;

private:
	BOOL ShowTelecommandProperties(INT nIndex);
	BOOL ShowTelecommandProperties(INT nIndex, CTCManualStackComposedItem *pItem);

	BOOL InsertTelecommand(INT nIndex, CTCManualStackItem *pItem);
	BOOL UpdateTelecommand(INT nIndex);
	BOOL DeleteTelecommand(INT nIndex);

	BOOL ActivateTelecommand(INT nIndex, BOOL bActivate = TRUE, BOOL bRedraw = TRUE);
	BOOL IsActivatedTelecommand(INT nIndex) CONST;

	VOID ResetTelecommand(CTCManualStackItem *pItem) CONST;

	CString TranslateTelecommand(CONST CTCManualStackItem *pItem, BOOL bFirst) CONST;
	BOOL TranslateTelecommand(CONST CTCManualStackItem *pItem, CTextViewAttribute *pAttribute) CONST;

	BOOL AdjustTelecommandAlerts(CONST CTCItem *pAlertItem, CTCManualStackItem *pItem) CONST;

	BOOL CheckTelecommandReleaseWindow(CONST CTCManualStackItem *pItem) CONST;
	BOOL CheckTelecommandReleaseWindow(CONST CTimeTag &tTime, CONST CTCManualStackItem *pItem) CONST;
	BOOL CheckTelecommandExecutionTime(CONST CTCManualStackItem *pItem) CONST;
	BOOL CheckTelecommandExecutionTime(CONST CTimeTag &tTime, CONST CTCManualStackItem *pItem) CONST;

	UINT CheckTelecommandReleaseInterlockState(CONST CTCManualStackItem *pItem) CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;
	COLORREF LookupStatusColor(UINT nStatus) CONST;
	COLORREF LookupAlertColor(UINT nColumn, UINT nAlertType) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;
	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, INT nCount, INT nIndex) CONST;

	CString ConstructToolTipTitle(CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCManualStackItem *pItem, CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;

	BOOL SetClipboardFormat(UINT nFormat);
	UINT GetClipboardFormat() CONST;
	BOOL CopyToClipboard(BOOL bCut = FALSE);
	BOOL PasteFromClipboard(INT nIndex = -1, BOOL bAfter = TRUE);

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackView)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
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
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCManualStackWnd frame

// Specify the telecommand manual stack title items
#define TCMANUALSTACK_TITLEITEM_NUMBER   (1<<0)
#define TCMANUALSTACK_TITLEITEM_NAME   (1<<1)
#define TCMANUALSTACK_TITLEITEM_DESCRIPTION   (1<<2)
#define TCMANUALSTACK_TITLEITEM_CATEGORY   (1<<3)
#define TCMANUALSTACK_TITLEITEM_SUBSYSTEM   (1<<4)
#define TCMANUALSTACK_TITLEITEM_ARGUMENTS   (1<<5)
#define TCMANUALSTACK_TITLEITEM_FLAGS   (1<<6)
#define TCMANUALSTACK_TITLEITEM_TCPACKET   (1<<7)
#define TCMANUALSTACK_TITLEITEM_DISPATCHTIME   (1<<8)
#define TCMANUALSTACK_TITLEITEM_RELEASETIME   (1<<9)
#define TCMANUALSTACK_TITLEITEM_RELEASETIMEOFFSET   (1<<10)
#define TCMANUALSTACK_TITLEITEM_EXECUTIONTIME   (1<<11)
#define TCMANUALSTACK_TITLEITEM_EXECUTIONTIMEOFFSET   (1<<12)
#define TCMANUALSTACK_TITLEITEM_AUTHORIZATION   (1<<13)
#define TCMANUALSTACK_TITLEITEM_PTVTIMEWINDOW   (1<<14)
#define TCMANUALSTACK_TITLEITEM_PTVCHECKS   (1<<15)
#define TCMANUALSTACK_TITLEITEM_PTVRESULT   (1<<16)
#define TCMANUALSTACK_TITLEITEM_PEVCHECKS   (1<<17)
#define TCMANUALSTACK_TITLEITEM_PEVRESULT   (1<<18)
#define TCMANUALSTACK_TITLEITEM_CEVTIMEWINDOW   (1<<19)
#define TCMANUALSTACK_TITLEITEM_CEVCHECKS   (1<<20)
#define TCMANUALSTACK_TITLEITEM_STATUS   (1<<21)
#ifndef RC_INVOKED
#define TCMANUALSTACK_TITLEITEMS_DEFAULT   (TCMANUALSTACK_TITLEITEM_NUMBER | TCMANUALSTACK_TITLEITEM_NAME | TCMANUALSTACK_TITLEITEM_DESCRIPTION | TCMANUALSTACK_TITLEITEM_ARGUMENTS | TCMANUALSTACK_TITLEITEM_FLAGS | TCMANUALSTACK_TITLEITEM_RELEASETIME | TCMANUALSTACK_TITLEITEM_RELEASETIMEOFFSET | TCMANUALSTACK_TITLEITEM_AUTHORIZATION | TCMANUALSTACK_TITLEITEM_STATUS)
#define TCMANUALSTACK_TITLEITEMS_ALL   (TCMANUALSTACK_TITLEITEMS_DEFAULT | TCMANUALSTACK_TITLEITEM_CATEGORY | TCMANUALSTACK_TITLEITEM_SUBSYSTEM | TCMANUALSTACK_TITLEITEM_TCPACKET | TCMANUALSTACK_TITLEITEM_DISPATCHTIME | TCMANUALSTACK_TITLEITEM_EXECUTIONTIME | TCMANUALSTACK_TITLEITEM_EXECUTIONTIMEOFFSET | TCMANUALSTACK_TITLEITEM_PTVTIMEWINDOW | TCMANUALSTACK_TITLEITEM_PTVCHECKS | TCMANUALSTACK_TITLEITEM_PTVRESULT | TCMANUALSTACK_TITLEITEM_PEVCHECKS | TCMANUALSTACK_TITLEITEM_PEVRESULT | TCMANUALSTACK_TITLEITEM_CEVTIMEWINDOW | TCMANUALSTACK_TITLEITEM_CEVCHECKS)
#endif
// Specify the telecommand manual stack command source modes
#define TCMANUALSTACK_MODE_DEFAULT   TCSERVICE_COMMANDSOURCEMODE_DEFAULT
#define TCMANUALSTACK_MODE_MASTERMANUAL   TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL
// Specify the telecommand manual stack command source checks
#define TCMANUALSTACK_CHECKS_DEFAULT   TCSERVICE_COMMANDSOURCEFLAGS_DEFAULT
#define TCMANUALSTACK_CHECKS_PTV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_PTV_OVERRIDE
#define TCMANUALSTACK_CHECKS_PEV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE
#define TCMANUALSTACK_CHECKS_CEV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE
#define TCMANUALSTACK_CHECKS_PTV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_PTV_DISABLE
#define TCMANUALSTACK_CHECKS_PEV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE
#define TCMANUALSTACK_CHECKS_CEV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE
#define TCMANUALSTACK_CHECKS_PREAUTHORIZE   TCSERVICE_COMMANDSOURCEFLAGS_PREAUTHORIZE
// Specify the telecommand manual stack command source states
#define TCMANUALSTACK_STATE_DEFAULT   TCSERVICE_COMMANDSOURCESTATE_DEFAULT
#define TCMANUALSTACK_STATE_SUSPENDED   TCSERVICE_COMMANDSOURCESTATE_SUSPENDED
#define TCMANUALSTACK_STATE_STOPPED   TCSERVICE_COMMANDSOURCESTATE_STOPPED
#define TCMANUALSTACK_STATE_DISABLED   TCSERVICE_COMMANDSOURCESTATE_DISABLED
#define TCMANUALSTACK_STATE_EMPTY   TCSERVICE_COMMANDSOURCESTATE_EMPTY
// Specify the telecommand manual stack command options
#define TCMANUALSTACK_OPTION_NONE   TCSERVICE_COMMANDSOURCEOPTION_NONE
#define TCMANUALSTACK_OPTION_ALWAYSALLOWEXIT   TCSERVICE_COMMANDSOURCEOPTION_ALWAYSALLOWEXIT
#define TCMANUALSTACK_OPTION_UNDISPATCHONEXIT   TCSERVICE_COMMANDSOURCEOPTION_UNDISPATCHONEXIT
// Specify the telecommand manual stack default settings
#define TCMANUALSTACK_RELEASETIMEWINDOW_DEFAULTINTERVAL   TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL
#define TCMANUALSTACK_DISPATCHTIMEWINDOW_DEFAULTINTERVAL   TCSERVICE_COMMANDHANDLERTIMEWINDOW_DISPATCHINTERVAL
#define TCMANUALSTACK_UPDATELISTCHECKS_DEFAULTCOUNT   20
// Specify the telecommand manual stack alert types
#define TCMANUALSTACK_ALERTTYPE_TELECOMMANDRELEASEFAILURE   0
#define TCMANUALSTACK_ALERTTYPE_INTERLOCKFAILURE   1
// Specify the telecommand manual stack print modes
#define TCMANUALSTACK_PRINT_ONSTACKITEMS   (1<<0)
#define TCMANUALSTACK_PRINT_DISPATCHEDITEMS   (1<<1)
#define TCMANUALSTACK_PRINT_NOTRELEASEDITEMS   (1<<2)
#define TCMANUALSTACK_PRINT_FAILEDRELEASEITEMS   (1<<3)
#define TCMANUALSTACK_PRINT_ITEMRANGE   (1<<4)
#define TCMANUALSTACK_PRINT_TIMERANGE   (1<<5)
#define TCMANUALSTACK_PRINT_CLEARCOMMENTS   (1<<6)
// Specify the telecommand manual stack print fonts
#define TCMANUALSTACK_PRINTFONT_TITLE   0
#define TCMANUALSTACK_PRINTFONT_DETAILS   1
#define TCMANUALSTACK_PRINTFONT_COMMENTS   2
#define TCMANUALSTACK_PRINTFONT_LISTITEMSTITLE   3
#define TCMANUALSTACK_PRINTFONT_LISTITEMS   4
#define TCMANUALSTACK_PRINTFONT_FOOTER   5
#define TCMANUALSTACK_PRINTFONT_NOTICE   6
#define TCMANUALSTACK_PRINTFONT_LOGO   7
#define TCMANUALSTACK_PRINTFONTS   8
// Specify the telecommand manual stack toolbar identifiers
#define ID_TCMANUALSTACK_TOOLBAR_PROPERTIES   AFX_IDW_TOOLBAR
#define ID_TCMANUALSTACK_TOOLBAR_OPERATIONS   (AFX_IDW_TOOLBAR+1)
// Specify the telecommand manual stack statusbar pane identifiers
#define ID_TCMANUALSTACK_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TCMANUALSTACK_STATUSBAR_UPLINKPANE   ID_STATUSBAR_PANE1
#define ID_TCMANUALSTACK_STATUSBAR_PTVPANE   ID_STATUSBAR_PANE2
#define ID_TCMANUALSTACK_STATUSBAR_PEVPANE   ID_STATUSBAR_PANE3
#define ID_TCMANUALSTACK_STATUSBAR_CEVPANE   ID_STATUSBAR_PANE4
#define ID_TCMANUALSTACK_STATUSBAR_STATEPANE   ID_STATUSBAR_PANE5
#define ID_TCMANUALSTACK_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE6

class CTCManualStackWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTCManualStackWnd)

	// Construction
public:
	CTCManualStackWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbColumns[2];
		RECT  rToolBar[2];
		LOGFONT  sFont[2];
		SCROLLINFO  sScrollInfo[2];
	} DATA, *PDATA, *LPDATA;
private:
	CTCManualStackToolBar  m_wndToolBar[2];
	CTCManualStackStatusBar  m_wndStatusBar;
	CTCManualStackView  m_wndView;
private:
	CTCManualStackSettingsDialog  m_dlgSettings;
	CTCManualStackInterlocksDialog  m_dlgInterlocks;
	CTCManualStackSaveContentsDialog  m_dlgSaveStacks;
	CTCManualStackLoadContentsDialog  m_dlgLoadStacks;
	CTCManualStackLoadCommandDialog  m_dlgLoadCommand;
private:
	CTCManualStackItemTemplates  m_pItemTemplates;
	CTCManualStackComposedItemTemplates  m_pComposedItemTemplates;
	CTCManualStackSearchGroups  m_pSearchGroups[TCMANUALSTACKSEARCHGROUP_TYPES];
	CTCManualStackSearchFilters  m_pSearchFilters[TCMANUALSTACKSEARCHFILTER_TYPES];
private:
	CTCManualStackPrintJobs  m_pPrintJobs;
private:
	CTCSavedStack  m_cSavedStack;
private:
	UINT  m_nLoggingPolicy;
	UINT  m_nLoggingReloadCount;
	CString  m_szLoggingFileName[2];
	CTimeSpan  m_tLoggingRetention;
	DWORDLONG  m_dwLoggingRetention;
	BOOL  m_bLoggingAsEvent;
private:
	CUIntArray  m_nAlertTypes;
	CStringArray  m_szAlertAuditions;
	CStringArray  m_szAlertNotifications;
	CDWordArray  m_nAlertAcknowledgeColors;
	CByteArray  m_bAlertAcknowledgments;

	// Operations
public:
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetAlertColors(CONST CUIntArray &nColors);
	BOOL GetAlertColors(CUIntArray &nColors) CONST;

	BOOL SetSearchGroups(UINT nType, CONST CTCManualStackSearchGroups &pGroups);
	BOOL GetSearchGroups(UINT nType, CTCManualStackSearchGroups &pGroups) CONST;
	BOOL SetSearchFilters(UINT nType, CONST CTCManualStackSearchFilters &pFilters);
	BOOL GetSearchFilters(UINT nType, CTCManualStackSearchFilters &pFilters) CONST;
	BOOL SetItemTemplates(CONST CTCManualStackItemTemplates &pTemplates);
	BOOL SetItemTemplates(CONST CTCManualStackComposedItemTemplates &pTemplates);
	BOOL GetItemTemplates(CTCManualStackItemTemplates &pTemplates) CONST;
	BOOL GetItemTemplates(CTCManualStackComposedItemTemplates &pTemplates) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL SetDefaultReleaseTimeWindow(LPCTSTR pszOriginator, CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL SetDispatchTimeWindow(LPCTSTR pszOriginator, CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL UpdateTelecommanding(LPCTSTR pszOriginator, CONST CTCProcessCommandSourceInfo *pCommandSourceInfo);
	BOOL UpdateTelecommanding(LPCTSTR pszEvent);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode, BOOL bUser = TRUE);
	BOOL SetTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser = TRUE);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags, BOOL bUser = TRUE);
	BOOL SetTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser = TRUE);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState, BOOL bUser = TRUE);
	BOOL SetTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser = TRUE);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable, BOOL bUser = TRUE);
	BOOL EnableTelecommandingInterlockMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser = TRUE);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable, BOOL bUser = TRUE);
	BOOL EnableTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser = TRUE);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable, BOOL bUser = TRUE);
	BOOL EnableTelecommandingAutoRejectionMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser = TRUE);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCItems &pItems);
	BOOL LoadTelecommands(CONST CTCManualStackItems &pItems);
	BOOL DispatchTelecommands(CTCManualStackItems &pItems, BOOL bUndo = FALSE);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL SelectTelecommand(INT nIndex);
	VOID DoSelectAllTelecommands();
	BOOL CanSelectAllTelecommands() CONST;
	INT EnumSelectedTelecommands(CTCManualStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands() CONST;

	UINT GetTelecommandCount() CONST;

	BOOL DoInsertBeforeTelecommand();
	BOOL CanInsertBeforeTelecommand() CONST;
	BOOL DoInsertAfterTelecommand();
	BOOL CanInsertAfterTelecommand() CONST;
	BOOL DoMoveUpTelecommand();
	BOOL CanMoveUpTelecommand() CONST;
	BOOL DoMoveDownTelecommand();
	BOOL CanMoveDownTelecommand() CONST;
	BOOL DoCutTelecommand();
	BOOL CanCutTelecommand() CONST;
	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoPasteTelecommand();
	BOOL CanPasteTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL DoArmTelecommand();
	BOOL CanArmTelecommand() CONST;
	BOOL DoDispatchTelecommand();
	BOOL CanDispatchTelecommand() CONST;
	BOOL DoUndispatchTelecommand();
	BOOL CanUndispatchTelecommand() CONST;
	BOOL DoAcknowledgeTelecommand();
	BOOL CanAcknowledgeTelecommand() CONST;
	BOOL DoReloadTelecommand();
	BOOL CanReloadTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL DoResetInterlocks();
	BOOL CanResetInterlocks() CONST;

	BOOL DoCommandingState();
	BOOL CanCommandingState() CONST;
	BOOL DoSuspendedState();
	BOOL CanSuspendedState() CONST;
	BOOL DoStoppedState();
	BOOL CanStoppedState() CONST;

	BOOL SetLoggingOptions();
	BOOL SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent);
	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	BOOL SetAlertOptions(CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments);
	BOOL GetAlertOptions(CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST;

	BOOL Alert(CONST CTCManualStackItem *pItem);
	BOOL Alert(CONST CTCInterlock *pInterlock);

	BOOL SetPrintJobs(CONST CTCManualStackPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTCManualStackPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CTCManualStackPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	BOOL LogActivity(CONST CTCLogEntry *pEntry);

private:
	BOOL CreateToolBars();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateUplinkPane();
	VOID UpdatePretransmissionVerificationPane();
	VOID UpdatePreexecutionVerificationPane();
	VOID UpdateExecutionVerificationPane();
	VOID UpdateStatePane();
	VOID UpdateModePane();

	VOID UpdateContents();

	BOOL SetSearchGroups(CONST CByteArray &nSearchGroups);
	BOOL GetSearchGroups(CByteArray &nSearchGroups) CONST;
	BOOL SetSearchFilters(CONST CByteArray &nSearchFilters);
	BOOL GetSearchFilters(CByteArray &nSearchFilters) CONST;
	BOOL SetItemTemplates(CONST CByteArray &nItemTemplates, CONST CByteArray &nComposedItemTemplates);
	BOOL GetItemTemplates(CByteArray &nItemTemplates, CByteArray &nComposedItemTemplates) CONST;

	BOOL LogTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser);
	BOOL LogTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser);
	BOOL LogTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser);
	BOOL LogTelecommandingInterlockMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser);
	BOOL LogTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser);
	BOOL LogTelecommandingAutoRejectionMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser);
	BOOL LogResetInterlocks(CONST CTCInterlocks &pInterlocks);
	BOOL LogListOptions(INT nArguments, BOOL bAll);
	BOOL LogListUpdateChecks(INT nCount);
	BOOL LogMiscellaneousOptions(UINT nOptions);
	BOOL LogDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL LogDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL LogAlerts(CONST CUIntArray &nTypes, CONST CUIntArray &nActions);

	BOOL SetContents(CONST CByteArray &nContentsInfo);
	BOOL GetContents(CByteArray &nContentsInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTCManualStackPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTCManualStackPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCManualStackPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocDetails(CONST CTCManualStackPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CTCManualStackPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(CONST RECT &rPropertiesToolBar, CONST RECT &rOperationsToolBar, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	BOOL GetLayoutInfo(RECT &rPropertiesToolBar, RECT &rOperationsToolBar, CUIntArray &nColumns, CUIntArray &nWidths, LOGFONT *pTitleFont, LOGFONT *pItemsFont, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCManualStackWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
	virtual void RecalcLayout(CDisplayToolBar *pToolBar);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Check() CONST;
	virtual VOID Update();
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
	BOOL OnCloseSettingsDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCManualStackWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnSave();
	afx_msg void OnOpen();
	afx_msg void OnLoad();
	afx_msg void OnProperties();
	afx_msg void OnInsertBefore();
	afx_msg void OnInsertAfter();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	afx_msg void OnSelectAll();
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnDelete();
	afx_msg void OnFullViewMode();
	afx_msg void OnStart();
	afx_msg void OnSuspend();
	afx_msg void OnStop();
	afx_msg void OnArm();
	afx_msg void OnDispatch();
	afx_msg void OnUndispatch();
	afx_msg void OnAcknowledge();
	afx_msg void OnReload();
	afx_msg void OnResetInterlocks();
	afx_msg void OnInterlockChecks();
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnAutoRejectionMode();
	afx_msg void OnPrint();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLoad(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProperties(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInsertBefore(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInsertAfter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMoveUp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMoveDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFullViewMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSuspend(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateArm(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDispatch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUndispatch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAcknowledge(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReload(CCmdUI *pCmdUI);
	afx_msg void OnUpdateResetInterlocks(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInterlockChecks(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReleaseWaitMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAutoRejectionMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarUplinkPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarPEVPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarCEVPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarStatePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItem

// Specify the telecommand automatic stack item types
#define TCAUTOMATICSTACKITEM_TYPE_NONE   TCITEM_TYPE_NONE
#define TCAUTOMATICSTACKITEM_TYPE_FUNCTION   TCITEM_TYPE_FUNCTION
#define TCAUTOMATICSTACKITEM_TYPE_SEQUENCE   TCITEM_TYPE_SEQUENCE
#define TCAUTOMATICSTACKITEM_TYPE_PROCEDURE   TCITEM_TYPE_PROCEDURE
// Specify the telecommand automatic stack item flags
#define TCAUTOMATICSTACKITEM_CHECKFLAG_OVERRIDEPTV   TCITEM_CHECKFLAG_OVERRIDEPTV
#define TCAUTOMATICSTACKITEM_CHECKFLAG_OVERRIDEPEV   TCITEM_CHECKFLAG_OVERRIDEPEV
#define TCAUTOMATICSTACKITEM_CHECKFLAG_OVERRIDECEV   TCITEM_CHECKFLAG_OVERRIDECEV
#define TCAUTOMATICSTACKITEM_CHECKFLAG_DISABLEPTV   TCITEM_CHECKFLAG_DISABLEPTV
#define TCAUTOMATICSTACKITEM_CHECKFLAG_DISABLEPEV   TCITEM_CHECKFLAG_DISABLEPEV
#define TCAUTOMATICSTACKITEM_CHECKFLAG_DISABLECEV   TCITEM_CHECKFLAG_DISABLECEV
#define TCAUTOMATICSTACKITEM_CHECKFLAG_PREAUTHORIZED   TCITEM_CHECKFLAG_PREAUTHORIZED
#define TCAUTOMATICSTACKITEM_LINKAGEFLAG_GROUPED   TCITEM_LINKAGEFLAG_GROUPED
#define TCAUTOMATICSTACKITEM_LINKAGEFLAG_BLOCKED   TCITEM_LINKAGEFLAG_BLOCKED
#define TCAUTOMATICSTACKITEM_RELEASEFLAG_AFTERBEGIN   TCITEM_RELEASEFLAG_AFTERBEGIN
#define TCAUTOMATICSTACKITEM_RELEASEFLAG_AFTERPREVIOUS   TCITEM_RELEASEFLAG_AFTERPREVIOUS
#define TCAUTOMATICSTACKITEM_EXECUTIONFLAG_AFTERBEGIN   TCITEM_EXECUTIONFLAG_AFTERBEGIN
#define TCAUTOMATICSTACKITEM_EXECUTIONFLAG_AFTERPREVIOUS   TCITEM_EXECUTIONFLAG_AFTERPREVIOUS
#define TCAUTOMATICSTACKITEM_EXECUTIONFLAG_IMMEDIATE   TCITEM_EXECUTIONFLAG_IMMEDIATE
#define TCAUTOMATICSTACKITEM_EXECUTIONFLAG_TIMETAGGED   TCITEM_EXECUTIONFLAG_TIMETAGGED
#define TCAUTOMATICSTACKITEM_EXECUTIONFLAG_1STSTEP   TCITEM_EXECUTIONFLAG_1STSTEP
#define TCAUTOMATICSTACKITEM_EXECUTIONFLAG_2NDSTEP   TCITEM_EXECUTIONFLAG_2NDSTEP
#define TCAUTOMATICSTACKITEM_DUMPFLAG_SYNCHRONIZED   TCITEM_DUMPFLAG_SYNCHRONIZED
#define TCAUTOMATICSTACKITEM_DUMPFLAG_NOTSYNCHRONIZED   TCITEM_DUMPFLAG_NOTSYNCHRONIZED
#define TCAUTOMATICSTACKITEM_ACKNOWLEDGEFLAG_ACCEPTANCE   TCITEM_ACKNOWLEDGEFLAG_ACCEPTANCE
#define TCAUTOMATICSTACKITEM_ACKNOWLEDGEFLAG_START   TCITEM_ACKNOWLEDGEFLAG_START
#define TCAUTOMATICSTACKITEM_ACKNOWLEDGEFLAG_PROGRESS   TCITEM_ACKNOWLEDGEFLAG_PROGRESS
#define TCAUTOMATICSTACKITEM_ACKNOWLEDGEFLAG_COMPLETION   TCITEM_ACKNOWLEDGEFLAG_COMPLETION
#define TCAUTOMATICSTACKITEM_ACKNOWLEDGEFLAG_ALL   TCITEM_ACKNOWLEDGEFLAG_ALL
// Specify the telecommand automatic stack item authorization status
#define TCAUTOMATICSTACKITEM_AUTHORIZATIONSTATUS_NONE   TCITEM_AUTHORIZATIONSTATUS_NONE
#define TCAUTOMATICSTACKITEM_AUTHORIZATIONSTATUS_GRANTED   TCITEM_AUTHORIZATIONSTATUS_GRANTED
#define TCAUTOMATICSTACKITEM_AUTHORIZATIONSTATUS_DENIED   TCITEM_AUTHORIZATIONSTATUS_DENIED
// Specify the telecommand automatic stack item check results
#define TCAUTOMATICSTACKITEM_RESULT_NONE   TCITEM_RESULT_NONE
#define TCAUTOMATICSTACKITEM_RESULT_PTV_GO   TCITEM_RESULT_PTV_GO
#define TCAUTOMATICSTACKITEM_RESULT_PTV_WAIT   TCITEM_RESULT_PTV_WAIT
#define TCAUTOMATICSTACKITEM_RESULT_PTV_FAIL   TCITEM_RESULT_PTV_FAIL
#define TCAUTOMATICSTACKITEM_RESULT_PEV_GO   TCITEM_RESULT_PEV_GO
#define TCAUTOMATICSTACKITEM_RESULT_PEV_NOGO   TCITEM_RESULT_PEV_NOGO
#define TCAUTOMATICSTACKITEM_RESULT_CEV_IDLE   TCITEM_RESULT_CEV_IDLE
#define TCAUTOMATICSTACKITEM_RESULT_CEV_PENDING   TCITEM_RESULT_CEV_PENDING
#define TCAUTOMATICSTACKITEM_RESULT_CEV_PASSED   TCITEM_RESULT_CEV_PASSED
#define TCAUTOMATICSTACKITEM_RESULT_CEV_FAILED   TCITEM_RESULT_CEV_FAILED
#define TCAUTOMATICSTACKITEM_RESULT_CEV_UNKNOWN   TCITEM_RESULT_CEV_UNKNOWN
#define TCAUTOMATICSTACKITEM_RESULT_CEV_UNVERIFIED   TCITEM_RESULT_CEV_UNVERIFIED
#define TCAUTOMATICSTACKITEM_FAILURE_PTV_UPLINK   TCITEM_FAILURE_PTV_UPLINK
#define TCAUTOMATICSTACKITEM_FAILURE_PTV_RELEASETIMEWINDOW   TCITEM_FAILURE_PTV_RELEASETIMEWINDOW
#define TCAUTOMATICSTACKITEM_FAILURE_PTV_EXECUTIONTIME   TCITEM_FAILURE_PTV_EXECUTIONTIME
#define TCAUTOMATICSTACKITEM_FAILURE_PTV_INTERLOCK   TCITEM_FAILURE_PTV_INTERLOCK
#define TCAUTOMATICSTACKITEM_FAILURE_PTV_SUBSYSTEM   TCITEM_FAILURE_PTV_SUBSYSTEM
#define TCAUTOMATICSTACKITEM_FAILURE_PTV_ONBOARDBUFFER   TCITEM_FAILURE_PTV_ONBOARDBUFFER
#define TCAUTOMATICSTACKITEM_FAILURE_PTV_ENCODING   TCITEM_FAILURE_PTV_ENCODING
#define TCAUTOMATICSTACKITEM_FAILURE_PEV_TELEMETRY   TCITEM_FAILURE_PEV_TELEMETRY
#define TCAUTOMATICSTACKITEM_FAILURE_PEV_CORRELATION   TCITEM_FAILURE_PEV_CORRELATION
#define TCAUTOMATICSTACKITEM_FAILURE_PEV_2NDSTEP   TCITEM_FAILURE_PEV_2NDSTEP
#define TCAUTOMATICSTACKITEM_FAILURE_PEV_PARAMETERS   TCITEM_FAILURE_PEV_PARAMETERS
#define TCAUTOMATICSTACKITEM_FAILURE_CEV_PARAMETERS   TCITEM_FAILURE_CEV_PARAMETERS
// Specify the telecommand automatic stack item status flags
#define TCAUTOMATICSTACKITEM_STATUS_NONE   TCITEM_STATUS_NONE
#define TCAUTOMATICSTACKITEM_STATUS_ONSTACK   TCITEM_STATUS_ONSTACK
#define TCAUTOMATICSTACKITEM_STATUS_ARMED   TCITEM_STATUS_ARMED
#define TCAUTOMATICSTACKITEM_STATUS_DISPATCHED   TCITEM_STATUS_DISPATCHED
#define TCAUTOMATICSTACKITEM_STATUS_RELEASED   TCITEM_STATUS_RELEASED
#define TCAUTOMATICSTACKITEM_STATUS_NOTRELEASED   TCITEM_STATUS_NOTRELEASED
#define TCAUTOMATICSTACKITEM_STATUS_FAILEDRELEASE   TCITEM_STATUS_FAILEDRELEASE
#define TCAUTOMATICSTACKITEM_STATUS_SENT   TCITEM_STATUS_SENT
#define TCAUTOMATICSTACKITEM_STATUS_FAILEDSEND   TCITEM_STATUS_FAILEDSEND
#define TCAUTOMATICSTACKITEM_STATUS_UPLINKED   TCITEM_STATUS_UPLINKED
#define TCAUTOMATICSTACKITEM_STATUS_FAILEDUPLINK   TCITEM_STATUS_FAILEDUPLINK
#define TCAUTOMATICSTACKITEM_STATUS_EXECUTED   TCITEM_STATUS_EXECUTED
#define TCAUTOMATICSTACKITEM_STATUS_NOTEXECUTED   TCITEM_STATUS_NOTEXECUTED
#define TCAUTOMATICSTACKITEM_STATUS_FAILEDEXECUTION   TCITEM_STATUS_FAILEDEXECUTION
// Specify the telecommand automatic stack item status colors
#define TCAUTOMATICSTACKITEM_STATUSCOLOR_NONE   0
#define TCAUTOMATICSTACKITEM_STATUSCOLOR_IDLE   1
#define TCAUTOMATICSTACKITEM_STATUSCOLOR_PENDING   2
#define TCAUTOMATICSTACKITEM_STATUSCOLOR_PASSED   3
#define TCAUTOMATICSTACKITEM_STATUSCOLOR_NOTPASSED   4
// Specify the telecommand automatic stack item alert types
#define TCAUTOMATICSTACKITEM_ALERTTYPE_NONE   0
#define TCAUTOMATICSTACKITEM_ALERTTYPE_INFORMATION   1
#define TCAUTOMATICSTACKITEM_ALERTTYPE_WARNING   2
#define TCAUTOMATICSTACKITEM_ALERTTYPE_ERROR   3
#define TCAUTOMATICSTACKITEM_ALERTTYPE_ANY   (-1)

class CTCAutomaticStackItem : public CTCItem
{
	// Construction
public:
	CTCAutomaticStackItem();

	// Attributes
private:
	CUIntArray  m_nAlertTypes;
	CUIntArray  m_nAlertMessages;
	CStringArray  m_szAlertMessages;
private:
	BOOL  m_bSelected;

	// Operations
public:
	BOOL Alert(UINT nType, UINT nMessage, LPCTSTR pszMessage, BOOL bOverwrite = TRUE);
	BOOL Alert(UINT nType, UINT nMessage = -1, BOOL bEnable = FALSE);
	UINT IsAlerted(UINT nMessage, CString &szMessage) CONST;
	UINT IsAlerted(UINT nMessage = -1) CONST;

	INT GetAlertCount(UINT nType) CONST;

	VOID Select(BOOL bSelect = TRUE);
	BOOL IsSelected() CONST;

	BOOL Copy(CONST CTCAutomaticStackItem *pItem);
	BOOL Compare(CONST CTCAutomaticStackItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItems

class CTCAutomaticStackItems : public CTCItems
{
	// Construction
public:
	CTCAutomaticStackItems();
	~CTCAutomaticStackItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCAutomaticStackItem *pItem);

	INT Collect(INT nIndex, CTCAutomaticStackItems &pItems) CONST;
	INT Collect(INT nIndex, CUIntArray &nItemIDs) CONST;
	INT Collect(INT nIndex, CPtrArray &pItems) CONST;

	CTCAutomaticStackItem *GetAt(INT nIndex) CONST;
	CTCAutomaticStackItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCAutomaticStackItems *pItems);
	BOOL Compare(CONST CTCAutomaticStackItems *pItems) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackComposedItem

class CTCAutomaticStackComposedItem : public CTCAutomaticStackItems
{
	// Construction
public:
	CTCAutomaticStackComposedItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDescription;
		INT  cbParameters;
		INT  cbEntries;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDescription;
private:
	CDatabaseTCParameters  m_pParameters;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetDescription(LPCTSTR pszDescription);
	CString GetDescription() CONST;
	VOID SetParameters(CONST CDatabaseTCParameters &pParameters);
	INT GetParameters(CDatabaseTCParameters &pParameters) CONST;

	BOOL Copy(CONST CTCAutomaticStackComposedItem *pItem);
	BOOL Compare(CONST CTCAutomaticStackComposedItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemTemplate

class CTCAutomaticStackItemTemplate : public CTCAutomaticStackItem
{
	// Construction
public:

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTemplate[2];
		INT  cbItem;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTemplate[2];

	// Operations
public:
	VOID SetTemplateName(LPCTSTR pszName);
	CString GetTemplateName() CONST;
	VOID SetTemplateDescription(LPCTSTR pszDescription);
	CString GetTemplateDescription() CONST;

	BOOL Copy(CONST CTCAutomaticStackItemTemplate *pTemplate);
	BOOL Compare(CONST CTCAutomaticStackItemTemplate *pTemplate) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemTemplates

class CTCAutomaticStackItemTemplates : public CPtrArray
{
	// Construction
public:
	CTCAutomaticStackItemTemplates();
	~CTCAutomaticStackItemTemplates();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCAutomaticStackItemTemplate *pTemplate);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(LPCTSTR pszName, CStringArray &szTemplates) CONST;

	CTCAutomaticStackItemTemplate *GetAt(INT nIndex) CONST;
	CTCAutomaticStackItemTemplate *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCAutomaticStackItemTemplates *pTemplates);
	BOOL Compare(CONST CTCAutomaticStackItemTemplates *pTemplates) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackComposedItemTemplate

class CTCAutomaticStackComposedItemTemplate : public CTCAutomaticStackComposedItem
{
	// Construction
public:

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTemplate[2];
		INT  cbItem;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTemplate[2];

	// Operations
public:
	VOID SetTemplateName(LPCTSTR pszName);
	CString GetTemplateName() CONST;
	VOID SetTemplateDescription(LPCTSTR pszDescription);
	CString GetTemplateDescription() CONST;

	BOOL Copy(CONST CTCAutomaticStackComposedItemTemplate *pTemplate);
	BOOL Compare(CONST CTCAutomaticStackComposedItemTemplate *pTemplate) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackComposedItemTemplates

class CTCAutomaticStackComposedItemTemplates : public CPtrArray
{
	// Construction
public:
	CTCAutomaticStackComposedItemTemplates();
	~CTCAutomaticStackComposedItemTemplates();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCAutomaticStackComposedItemTemplate *pTemplate);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(LPCTSTR pszName, CStringArray &szTemplates) CONST;

	CTCAutomaticStackComposedItemTemplate *GetAt(INT nIndex) CONST;
	CTCAutomaticStackComposedItemTemplate *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCAutomaticStackComposedItemTemplates *pTemplates);
	BOOL Compare(CONST CTCAutomaticStackComposedItemTemplates *pTemplates) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchFilter

// Specify the telecommand automatic stack search filter types
#define TCAUTOMATICSTACKSEARCHFILTER_TYPE_NONE   0
#define TCAUTOMATICSTACKSEARCHFILTER_TYPE_FUNCTIONS   1
#define TCAUTOMATICSTACKSEARCHFILTER_TYPE_SEQUENCES   2
#define TCAUTOMATICSTACKSEARCHFILTER_TYPE_STACKS   3
#define TCAUTOMATICSTACKSEARCHFILTER_TYPES   3
// Specify the telecommand automatic stack search filter operators
#define TCAUTOMATICSTACKSEARCHFILTER_OPERATOR_AND   0
#define TCAUTOMATICSTACKSEARCHFILTER_OPERATOR_OR   1

class CTCAutomaticStackSearchFilter : public CObject
{
	// Construction
public:
	CTCAutomaticStackSearchFilter();

	// Atttributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbSearchKeys;
		INT  cbSearchValues;
		UINT  nType;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nType;
	CString  m_szName;
	CStringArray  m_szSearchKeys;
	CStringArray  m_szSearchValues;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(UINT nType);
	UINT GetType() CONST;

	VOID SetSearchKeys(CONST CStringArray &szKeys, CONST CStringArray &szValues);
	INT GetSearchKeys(CStringArray &szKeys, CStringArray &szValues) CONST;

	VOID Copy(CONST CTCAutomaticStackSearchFilter *pFilter);
	BOOL Compare(CONST CTCAutomaticStackSearchFilter *pFilter) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchFilters

class CTCAutomaticStackSearchFilters : public CPtrArray
{
	// Construction
public:
	CTCAutomaticStackSearchFilters();
	~CTCAutomaticStackSearchFilters();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCAutomaticStackSearchFilter *pFilter);

	INT Find(LPCTSTR pszName) CONST;

	CTCAutomaticStackSearchFilter *GetAt(INT nIndex) CONST;
	CTCAutomaticStackSearchFilter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCAutomaticStackSearchFilters *pFilters);
	BOOL Compare(CONST CTCAutomaticStackSearchFilters *pFilters) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackPrintJobInfo

class CTCAutomaticStackPrintJobInfo : public CObject
{
	// Construction
public:
	CTCAutomaticStackPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintRange[2];
		TIMEKEY  tPrintRange[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szProfile;
	CString  m_szComments;
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
	BOOL SetPrintRange(UINT nMin, UINT nMax);
	BOOL SetPrintRange(CONST CTimeKey &tMin, CONST CTimeKey &tMax);
	BOOL GetPrintRange(UINT &nMin, UINT &nMax) CONST;
	BOOL GetPrintRange(CTimeKey &tMin, CTimeKey &tMax) CONST;

	VOID Copy(CONST CTCAutomaticStackPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTCAutomaticStackPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackPrintJobs

class CTCAutomaticStackPrintJobs : public CPtrArray
{
	// Construction
public:
	CTCAutomaticStackPrintJobs();
	~CTCAutomaticStackPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCAutomaticStackPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTCAutomaticStackPrintJobInfo *GetAt(INT nIndex) CONST;
	CTCAutomaticStackPrintJobInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCAutomaticStackPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTCAutomaticStackPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsLayoutPage dialog

#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_PANE_STATIC   1002
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_PANE   1003
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_TOOLTIPS   1004
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT   1005
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1006
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT_NAME   1007
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1008
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1009
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1010
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT_GRID   1011
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR   1012
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS   1013
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1014
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1015
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1016
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1017
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1018
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_NAMES   1019
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1020
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_STYLE   1021
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1022
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_SIZE   1023
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1024
#define IDC_TCAUTOMATICSTACKSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1025

class CTCAutomaticStackSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsLayoutPage)

	// Construction
public:
	CTCAutomaticStackSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2][2][2];
	LOGFONT  m_fntTitle[2][2][2];
	LOGFONT  m_fntItems[2][2][2];
	COLORREF  m_nGridBackgroundColor[2][2][2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSettingsLayoutPage)
	enum { IDD = IDD_TCAUTOMATICSTACK_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetColumns(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetGridBackgroundColor(UINT nPane, COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTCAutomaticStackSettingsDialog *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumLayoutPanes();
	BOOL EnumLayoutColumns();

	BOOL ShowLayoutColumns();
	VOID ShowLayoutBackground();
	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	BOOL InsertLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL ModifyLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL RemoveLayoutColumn(INT nIndex);
	BOOL SetCurLayoutColumn(INT nIndex = 0);
	INT GetCurLayoutColumn() CONST;
	BOOL CheckLayoutColumn() CONST;

	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);
	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	INT FindPageIndex() CONST;
	INT FindPaneIndex() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsLayoutPage)
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
	//{{AFX_MSG(CTCAutomaticStackSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnGridBackground();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangePane();
	afx_msg void OnSelchangeColumnName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeGridBackgroundColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsOperationsPage dialog

#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_DETAILS   1001
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MODES   1002
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MODES_MASTERMANUALMODE   1003
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MODES_RELEASEWAITMODE   1004
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MODES_AUTOMATICREJECTIONMODE   1005
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_STATE_DISABLED   1006
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS   1007
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_OVERRIDEPTV   1008
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_DISABLEPTV   1009
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_OVERRIDEPEV   1010
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_DISABLEPEV   1011
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_OVERRIDECEV   1012
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_DISABLECEV   1013
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_INTERLOCKS   1014
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_UPDATE   1015
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_UPDATE_COUNT   1016
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_CHECKS_UPDATE_COUNT_STATIC   1017
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_PERMISSIONS   1018
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_ALERTS   1019
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS   1020
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_STATIC   1021
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_LIMITED   1022
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_LIMITED_COUNT   1023
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ARGUMENTS_ALL   1024
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_STATIC   1025
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL   1026
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL_STATIC   1027
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DISPATCHTIMEWINDOW_STATIC   1028
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DISPATCHTIMEWINDOW_INTERVAL   1029
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_DISPATCHTIMEWINDOW_INTERVAL_STATIC   1030
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_ALWAYSALLOWEXIT   1031
#define IDC_TCAUTOMATICSTACKSETTINGS_OPERATIONSPAGE_MISCELLANEOUS_UNDISPATCHONEXIT   1032

// Specify the telecommand automatic stack settings operations page related limits
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MINIMUMCHECKCOUNT   1
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MAXIMUMCHECKCOUNT   100
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MINIMUMARGUMENTS   0
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MAXIMUMARGUMENTS   100
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_DEFAULTARGUMENTS   5
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MINIMUMDEFAULTRELEASETIMEWINDOW   1
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MAXIMUMDEFAULTRELEASETIMEWINDOW   SECONDSPERDAY
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MINIMUMDISPATCHTIMEWINDOW   1
#define TCAUTOMATICSTACKSETTINGSOPERATIONSPAGE_MAXIMUMDISPATCHTIMEWINDOW   (5*SECONDSPERMINUTE)

class CTCAutomaticStackSettingsOperationsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsOperationsPage)

	// Construction
public:
	CTCAutomaticStackSettingsOperationsPage();

	// Attributes
private:
	INT  m_nChecks[2];
	INT  m_nArguments[2];
	UINT  m_nCheckFlags[2];
	UINT  m_nMiscellaneousOptions[2];
	CTimeSpan  m_tDefaultReleaseTimeWindow[2];
	CTimeSpan  m_tDispatchTimeWindow[2];
	BOOL  m_bStateFlags[2];
	BOOL  m_bArguments[2];
	BOOL  m_bModes[2][4];
	BOOL  m_bPermissions[2];
	BOOL  m_bAlerts[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSettingsOperationsPage)
	enum { IDD = IDD_TCAUTOMATICSTACK_SETTINGS_OPERATIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL GetListCheckOptions(UINT &nFlags, INT &nCount) CONST;
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetMasterManualModeFlag(BOOL &bEnabled) CONST;
	BOOL GetReleaseWaitModeFlag(BOOL &bEnabled) CONST;
	BOOL GetAutoRejectionModeFlag(BOOL &bEnabled) CONST;
	BOOL GetInterlockModeFlag(BOOL &bEnabled) CONST;
	BOOL GetDisabledStateFlag(BOOL &bFlag) CONST;

	class CTCAutomaticStackSettingsDialog *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowConfiguration();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsOperationsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSettingsOperationsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnMasterManualMode();
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnAutomaticRejectionMode();
	afx_msg void OnDisabledState();
	afx_msg void OnOverridePTV();
	afx_msg void OnDisablePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnDisablePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnInterlockChecks();
	afx_msg void OnUpdateChecks();
	afx_msg void OnPermissions();
	afx_msg void OnAlerts();
	afx_msg void OnLimitArguments();
	afx_msg void OnAllArguments();
	afx_msg void OnAlwaysAllowExit();
	afx_msg void OnUndispatchOnExit();
	afx_msg void OnSpinchangeUpdateChecksCount();
	afx_msg void OnSpinchangeArgumentsCount();
	afx_msg void OnSpinchangeDefaultReleaseTimeWindow();
	afx_msg void OnSpinchangeDispatchTimeWindow();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsFilteringPage dialog

#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_DETAILS   1001
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND   1002
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM   1003
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_ITEM_NAME   1004
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE    1005
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_SEQUENCE_NAME   1006
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE   1007
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_IMMEDIATE   1008
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_TIMETAGGED   1009
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_1STSTEP   1010
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_TYPE_2NDSTEP   1011
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_SUBSYSTEM   1012
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_SUBSYSTEMS   1013
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_SUBSYSTEM_ADD   1014
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_SUBSYSTEM_REMOVE   1015
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_TELECOMMAND_SUBSYSTEM_LIST   1016
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_VERIFICATION   1017
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE_STATIC   1018
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_VERIFICATION_STAGE   1019
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_VERIFICATION_STATE   1020
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_VERIFICATION_STATE_NAME   1021
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES   1022
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_COUNT   1023
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_LIMITATION_ENTRIES_STATIC   1024
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_ALERTS   1025
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_SORTING   1026
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_SORTING_STATIC   1027
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_SORTING_BYRELEASETIME   1028
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_SORTING_BYEXECUTIONTIME   1029
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_SORTING_ORDER_STATIC   1030
#define IDC_TCAUTOMATICSTACKSETTINGS_FILTERINGPAGE_SORTING_ORDER_LATESTFIRST   1031

// Specify the telecommand automatic stack settings filtering page related limits
#define TCAUTOMATICSTACKSETTINGSFILTERINGPAGE_MINIMUMENTRYLIMITATION   1
#define TCAUTOMATICSTACKSETTINGSFILTERINGPAGE_MAXIMUMENTRYLIMITATION   10000
#define TCAUTOMATICSTACKSETTINGSFILTERINGPAGE_DEFAULTENTRYLIMITATION   1000

class CTCAutomaticStackSettingsFilteringPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsFilteringPage)

	// Construction
public:
	CTCAutomaticStackSettingsFilteringPage();

	// Attributes
private:
	CString  m_szTelecommand[2][2];
	CUIntArray  m_nSubSystems[2];
	UINT  m_nLimitation[2];
	UINT  m_nMode[2][2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSettingsFilteringPage)
	enum { IDD = IDD_TCAUTOMATICSTACK_SETTINGS_FILTERINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetTelecommandName(CString &szName) CONST;
	BOOL GetTelecommandSequence(CString &szSequence) CONST;
	BOOL GetTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL GetLimitation(UINT &nCount) CONST;
	BOOL GetSortMode(UINT &nMode) CONST;

	class CTCAutomaticStackSettingsDialog *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumSubSystems();
	BOOL EnumVerificationStages();
	BOOL EnumVerificationStates();

	VOID ShowFilterInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsFilteringPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSettingsFilteringPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTelecommand();
	afx_msg void OnTelecommandName();
	afx_msg void OnTelecommandSequence();
	afx_msg void OnTelecommandType();
	afx_msg void OnTelecommandTypeImmediate();
	afx_msg void OnTelecommandTypeTimeTagged();
	afx_msg void OnTelecommandType1stStep();
	afx_msg void OnTelecommandType2ndStep();
	afx_msg void OnTelecommandSubSystem();
	afx_msg void OnTelecommandAddSubSystem();
	afx_msg void OnTelecommandRemoveSubSystem();
	afx_msg void OnVerificationStatus();
	afx_msg void OnVerificationState();
	afx_msg void OnLimitEntries();
	afx_msg void OnSortByReleaseTime();
	afx_msg void OnSortByExecutionTime();
	afx_msg void OnSortOrderLatestFirst();
	afx_msg void OnSelchangeTelecommandSubSystems();
	afx_msg void OnSelchangeTelecommandSubSystemList();
	afx_msg void OnSelchangeVerificationStage();
	afx_msg void OnSelchangeVerificationState();
	afx_msg void OnSpinchangeLimitationCount();
	afx_msg void OnEditchangeTelecommandTypeName();
	afx_msg void OnEditchangeTelecommandTypeSequence();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsPlanningPage dialog

#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_DETAILS   1001
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM   1002
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_COMPUTER_STATIC   1003
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_COMPUTER   1004
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_USEBACKUPCOMPUTER   1005
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_BACKUPCOMPUTER   1006
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS   1007
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_IMPORT_STATIC   1008
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_IMPORT_MANUALLY   1009
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_IMPORT_AUTOMATICALLY   1010
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_IMPORT_PERIOD   1011
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_IMPORT_PERIOD_STATIC   1012
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_STATIC   1013
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_NOTHING   1014
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_EVERYTHING   1015
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_FAILURES   1016
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_ACTION   1017
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_USEAUDITION   1018
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_AUDITION   1019
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_USENOTIFICATION   1020
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_MISSIONPLANNERSYSTEM_OPTIONS_REPORT_NOTIFICATION   1021
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM   1022
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM_COMPUTER_STATIC   1023
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM_COMPUTER   1024
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM_USEBACKUPCOMPUTER   1025
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM_BACKUPCOMPUTER   1026
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM_OPTIONS   1027
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM_OPTIONS_SYNCHRONIZATION_AUTOMATICALLY   1028
#define IDC_TCAUTOMATICSTACKSETTINGS_PLANNINGPAGE_FLIGHTDYNAMICSSYSTEM_OPTIONS_SYNCHRONIZATION_MANUALLY   1029

// Specify the telecommand automatic stack settings planning page related limits
#define TCAUTOMATICSTACKSETTINGSPLANNINGPAGE_MINIMUMPERIOD   1
#define TCAUTOMATICSTACKSETTINGSPLANNINGPAGE_MAXIMUMPERIOD   (DAYSPERWEEK*HOURSPERDAY)
#define TCAUTOMATICSTACKSETTINGSPLANNINGPAGE_DEFAULTPERIOD   HOURSPERDAY

class CTCAutomaticStackSettingsPlanningPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsPlanningPage)

	// Construction
public:
	CTCAutomaticStackSettingsPlanningPage();

	// Attributes
private:
	CString  m_szComputer[2][2][2];
	CString  m_szAudition[2];
	CString  m_szNotification[2];
	CTimeSpan  m_tPeriod[2];
	UINT  m_nOptions[2][2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSettingsPlanningPage)
	enum { IDD = IDD_TCAUTOMATICSTACK_SETTINGS_PLANNINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetOptions(CString &szMissionPlannerComputer, CString &szMissionPlannerBackupComputer, UINT &nMissionPlannerOptions, CTimeSpan &tMissionPlannerPeriod, CString &szMissionPlannerAudition, CString &szMissionPlannerNotification, CString &szFlightDynamicsComputer, CString &szFlightDynamicsBackupComputer, UINT &nFlightDynamicsOptions) CONST;

	class CTCAutomaticStackSettingsDialog *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumComputers();
	BOOL EnumAuditions();
	BOOL EnumNotifications();

	VOID ShowPlanningDetails();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsPlanningPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSettingsPlanningPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnUseMissionPlannerBackupComputer();
	afx_msg void OnMissionPlannerImportManually();
	afx_msg void OnMissionPlannerImportAutomatically();
	afx_msg void OnMissionPlannerReportNothing();
	afx_msg void OnMissionPlannerReportEverything();
	afx_msg void OnMissionPlannerReportFailures();
	afx_msg void OnMissionPlannerUseAudition();
	afx_msg void OnMissionPlannerUseNotification();
	afx_msg void OnUseFlightDynamicsBackupComputer();
	afx_msg void OnFlightDynamicsSynchronizationAutomatically();
	afx_msg void OnFlightDynamicsSynchronizationManually();
	afx_msg void OnEditchangeMissionPlannerComputer();
	afx_msg void OnEditchangeMissionPlannerBackupComputer();
	afx_msg void OnEditchangeFlightDynamicsComputer();
	afx_msg void OnEditchangeFlightDynamicsBackupComputer();
	afx_msg void OnSelchangeMissionPlannerComputer();
	afx_msg void OnSelchangeMissionPlannerBackupComputer();
	afx_msg void OnSelchangeMissionPlannerAudition();
	afx_msg void OnSelchangeMissionPlannerNotification();
	afx_msg void OnSelchangeFlightDynamicsComputer();
	afx_msg void OnSelchangeFlightDynamicsBackupComputer();
	afx_msg void OnSpinchangeMissionPlannerImportPeriod();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsLoggingPage dialog

#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_DETAILS   1001
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_LIST   1002
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_OPTIONS   1003
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_MODE_STATIC   1004
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_REALTIME   1005
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_RELOAD   1006
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_RELOAD_COUNT   1007
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_RELOAD_COUNT_STATIC   1008
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL   1009
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME_STATIC   1010
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME   1011
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME   1012
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME   1013
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT   1014
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT   1015
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC   1016
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT   1017
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE   1018
#define IDC_TCAUTOMATICSTACKSETTINGS_LOGGINGPAGE_SHOWASEVENT   1019

// Specify the telecommand automatic stack settings logging page related limits
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_MINIMUMRELOADCOUNT   1
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_MAXIMUMRELOADCOUNT   1000
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_DEFAULTRELOADCOUNT   25
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_MINIMUMRETRIEVALSTOPCOUNT   1
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_MAXIMUMRETRIEVALSTOPCOUNT   10000
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_DEFAULTRETRIEVALSTOPCOUNT   100
// Specify the telecommand automatic stack settings logging page related timer identifiers
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_TIMERID   100
#define TCAUTOMATICSTACKSETTINGSLOGGINGPAGE_TIMEOUT   500

class CTCAutomaticStackSettingsLoggingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsLoggingPage)

	// Construction
public:
	CTCAutomaticStackSettingsLoggingPage();

	// Attributes
private:
	UINT  m_nArchivalPolicy[2];
	UINT  m_nRetrievalReloadCount[2];
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	BOOL  m_bShowAsEvent[2];
private:
	CLogFile  m_cRetrievalFile;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSettingsLoggingPage)
	enum { IDD = IDD_TCAUTOMATICSTACK_SETTINGS_LOGGINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	class CTCAutomaticStackSettingsDialog *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingDetails();
	VOID ShowLogEntries(CONST CTCLogEntries &pEntries);
	VOID ShowLogEntry(CONST CTCLogEntry *pEntry, INT nIndex = -1);

	BOOL RetrieveLogEntries();
	BOOL RetrieveLogEntries(CTCLogEntries &pEntries);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsLoggingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSettingsLoggingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnRealtime();
	afx_msg void OnHistorical();
	afx_msg void OnReloadCount();
	afx_msg void OnStopAtTime();
	afx_msg void OnStopAtLimit();
	afx_msg void OnStopAtEnd();
	afx_msg void OnOptions();
	afx_msg void OnRetrieve();
	afx_msg void OnShowAsEvent();
	afx_msg void OnSpinchangeReloadCount();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsPrintingComments window

class CTCAutomaticStackSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsPrintingPage dialog

#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_PROFILE_STATIC   1002
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_PROFILE   1003
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS   1004
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STACK_STATIC   1005
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STACK_NORMAL   1006
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STACK_TIMETAGGED   1007
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_STATIC   1008
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_ONSTACK   1009
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_DISPATCHED   1010
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_RELEASED   1011
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_NOTRELEASED   1012
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_STATUS_FAILEDRELEASE   1013
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER   1014
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_LOW   1015
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_TO_STATIC   1016
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_NUMBER_HIGH   1017
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME   1018
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_START   1019
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_TO_STATIC   1020
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_OPTIONS_RELEASETIME_STOP   1021
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_COMMENTS   1022
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC   1023
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_COMMENTSTEXT   1024
#define IDC_TCAUTOMATICSTACKSETTINGS_PRINTINGPAGE_CLEARCOMMENTS   1025

// Specify the telecommand automatic stack settings printing page related limits
#define TCAUTOMATICSTACKSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE   1
#define TCAUTOMATICSTACKSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE   10000
#define TCAUTOMATICSTACKSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE   100

class CTCAutomaticStackSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsPrintingPage)

	// Construction
public:
	CTCAutomaticStackSettingsPrintingPage();

	// Attributes
private:
	CTCAutomaticStackPrintJobs  m_pJobs[2];
private:
	CTCAutomaticStackSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSettingsPrintingPage)
	enum { IDD = IDD_TCAUTOMATICSTACK_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCAutomaticStackPrintJobs &pJobs) CONST;

	class CTCAutomaticStackSettingsDialog *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTCAutomaticStackPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintNormalStack();
	afx_msg void OnPrintTimeTaggedStack();
	afx_msg void OnPrintOnStackItems();
	afx_msg void OnPrintDispatchedItems();
	afx_msg void OnPrintReleasedItems();
	afx_msg void OnPrintNotReleasedItems();
	afx_msg void OnPrintFailedReleaseItems();
	afx_msg void OnPrintItemRange();
	afx_msg void OnPrintTimeRange();
	afx_msg void OnSelchangeProfile();
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
// CTCAutomaticStackSettingsTabCtrl window

class CTCAutomaticStackSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSettingsDialog

class CTCAutomaticStackSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSettingsDialog)

	// Construction
public:
	CTCAutomaticStackSettingsDialog();

	// Attributes
private:
	CTCAutomaticStackSettingsTabCtrl  m_wndTabCtrl;
	CTCAutomaticStackSettingsLayoutPage  m_pageLayout;
	CTCAutomaticStackSettingsOperationsPage  m_pageOperations;
	CTCAutomaticStackSettingsFilteringPage  m_pageFiltering;
	CTCAutomaticStackSettingsPlanningPage  m_pagePlanning;
	CTCAutomaticStackSettingsLoggingPage  m_pageLogging;
	CTCAutomaticStackSettingsPrintingPage  m_pagePrinting;

	// Operations
public:
	BOOL GetColumns(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetGridBackgroundColor(UINT nPane, COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL GetListCheckOptions(UINT &nFlags, INT &nCount) CONST;
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL GetMasterManualModeFlag(BOOL &bEnabled) CONST;
	BOOL GetReleaseWaitModeFlag(BOOL &bEnabled) CONST;
	BOOL GetAutoRejectionModeFlag(BOOL &bEnabled) CONST;
	BOOL GetInterlockModeFlag(BOOL &bEnabled) CONST;
	BOOL GetDisabledStateFlag(BOOL &bFlag) CONST;
	BOOL IsOperationsModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL GetFilterTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL GetFilterSortMode(UINT &nMode) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetPlanningOptions(CString &szMissionPlannerComputer, CString &szMissionPlannerBackupComputer, UINT &nMissionPlannerOptions, CTimeSpan &tMissionPlannerPeriod, CString &szMissionPlannerAudition, CString &szMissionPlannerNotification, CString &szFlightDynamicsComputer, CString &szFlightDynamicsBackupComputer, UINT &nFlightDynamicsOptions) CONST;
	BOOL IsPlanningModified() CONST;

	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL IsLoggingModified() CONST;

	BOOL GetPrintJobs(CTCAutomaticStackPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSettingsDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackSettingsDialog)
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
// CTCAutomaticStackUserPermissionsDialog dialog

#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_COMMENT_STATIC   1002
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_RELEASECONSTRAINTS   1003
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_RELEASECONSTRAINTS_CHECKS   1004
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_RELEASECONSTRAINTS_FLAGS   1005
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_RELEASECONSTRAINTS_RELEASETIME   1006
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_RELEASECONSTRAINTS_INTERLOCKS   1007
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_ONBOARDEXECUTIONTIME   1008
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_ONBOARDEXECUTIONTIME_EXECUTIONTIME   1009
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_MISCELLANEOUS   1010
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_MISCELLANEOUS_PARAMETERVALUES   1011
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_MISCELLANEOUS_TEMPLATES   1012
#define IDC_TCAUTOMATICSTACK_USERPERMISSIONS_HELP   1013

class CTCAutomaticStackUserPermissionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackUserPermissionsDialog)

	// Construction
public:
	CTCAutomaticStackUserPermissionsDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nPermissions[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackUserPermissionsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_USERPERMISSIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCAutomaticStackOperationsPage *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowPermissions();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackUserPermissionsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackUserPermissionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReleaseConstraintsChecks();
	afx_msg void OnReleaseConstraintsFlags();
	afx_msg void OnReleaseConstraintsReleaseTime();
	afx_msg void OnReleaseConstraintsInterlocks();
	afx_msg void OnOnBoardExecutionTimesExecutionTime();
	afx_msg void OnMiscellaneousParameterValues();
	afx_msg void OnMiscellaneousTemplates();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackAlertOptionsDialog dialog

#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_TYPE_STATIC   1002
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_TYPE   1003
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION   1004
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_AUDITION_STATIC   1005
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_AUDITION   1006
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_AUDITION_BLINK   1007
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_AUDITION_COLOR_STATIC   1008
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_AUDITION_COLOR   1009
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_STATIC   1010
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS   1011
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_ADD   1012
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVE   1013
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_REMOVEALL   1014
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_ACTION_NOTIFICATIONS_LIST   1015
#define IDC_TCAUTOMATICSTACK_ALERTOPTIONS_HELP   1016

class CTCAutomaticStackAlertOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackAlertOptionsDialog)

	// Construction
public:
	CTCAutomaticStackAlertOptionsDialog();   // standard constructor

	// Attributes
private:
	CUIntArray  m_nTypes[2];
	CStringArray  m_szAuditions[2];
	CStringArray  m_szNotifications[2];
	CDWordArray  m_nAcknowledgeColors[2];
	CByteArray  m_bAcknowledgments[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackAlertOptionsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ALERTOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCAutomaticStackOperationsPage *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTypes();
	BOOL EnumAuditions();
	BOOL EnumNotifications();

	VOID ShowAlertDetails();

	INT FindAlertType() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackAlertOptionsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackAlertOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAuditionBlink();
	afx_msg void OnAddNotification();
	afx_msg void OnRemoveNotification();
	afx_msg void OnRemoveAllNotifications();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeAuditionColor();
	afx_msg void OnSelchangeNotification();
	afx_msg void OnSelchangeNotificationList();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackLoggingOptionsDialog dialog

#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_FILENAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_FILENAME   1003
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_BROWSE   1004
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_DISABLED   1005
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_RETRIEVALS   1006
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_POLICY   1007
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_POLICY_OVERWRITE   1008
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_POLICY_OLDOVERWRITE   1009
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_POLICY_DAYS_STATIC   1010
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_POLICY_DAYS   1011
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_POLICY_NOOVERWRITE   1012
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_SIZE   1013
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_SIZE_UNLIMITED   1014
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_SIZE_LIMITED   1015
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_SIZE_MAXIMUM_STATIC   1016
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_SIZE_MAXIMUM   1017
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_SIZE_RESET   1018
#define IDC_TCAUTOMATICSTACK_LOGGINGOPTIONS_HELP   1019

// Specify the telecommand automatic stack logging options dialog related settings
#define TCAUTOMATICSTACKLOGGINGOPTIONS_MINIMUMDAYS   1
#define TCAUTOMATICSTACKLOGGINGOPTIONS_MAXIMUMDAYS   10000
#define TCAUTOMATICSTACKLOGGINGOPTIONS_DEFAULTDAYS   DAYSPERWEEK
#define TCAUTOMATICSTACKLOGGINGOPTIONS_MINIMUMSIZE   8
#define TCAUTOMATICSTACKLOGGINGOPTIONS_MAXIMUMSIZE   2147483647
#define TCAUTOMATICSTACKLOGGINGOPTIONS_DEFAULTSIZE   (LOGFILE_DEFAULT_SIZE/1024)

class CTCAutomaticStackLoggingOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackLoggingOptionsDialog)

	// Construction
public:
	CTCAutomaticStackLoggingOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	UINT  m_nArchivalPolicy[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackLoggingOptionsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_LOGGINGOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szArchivalFileName, UINT &nArchivalPolicy, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName);

	class CTCAutomaticStackLoggingPage *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingOptions();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackLoggingOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackLoggingOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRetrievals();
	afx_msg void OnBrowseFileName();
	afx_msg void OnOverwriteLogs();
	afx_msg void OnOverwriteOldLogs();
	afx_msg void OnOverwriteNoLogs();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnLimitedSize();
	afx_msg void OnResetSize();
	afx_msg void OnDisabled();
	afx_msg void OnSpinchangeDays();
	afx_msg void OnSpinchangeSize();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackRetrievalOptionsDialog dialog

#define IDC_TCAUTOMATICSTACK_RETRIEVALOPTIONS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_RETRIEVALOPTIONS_FILENAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_RETRIEVALOPTIONS_FILENAME   1003
#define IDC_TCAUTOMATICSTACK_RETRIEVALOPTIONS_BROWSE   1004
#define IDC_TCAUTOMATICSTACK_RETRIEVALOPTIONS_HELP   1005

class CTCAutomaticStackRetrievalOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackRetrievalOptionsDialog)

	// Construction
public:
	CTCAutomaticStackRetrievalOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackRetrievalOptionsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_RETRIEVALOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szFileName);

	class CTCAutomaticStackLoggingOptionsDialog *GetParentDialog() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackRetrievalOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackRetrievalOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchFilterDialog dialog

#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_NAME_STATIC  1002
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_NAME   1003
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_KEY_STATIC   1004
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_KEY   1005
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_VALUE_STATIC   1006
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_VALUE   1007
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_EXAMPLE_STATIC   1008
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_EXAMPLE   1009
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_ADD   1010
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_REMOVE   1011
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_REMOVEALL   1012
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_KEYSLIST   1013
#define IDC_TCAUTOMATICSTACK_SEARCHFILTER_HELP   1014

class CTCAutomaticStackSearchFilterDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchFilterDialog)

	// Construction
public:
	CTCAutomaticStackSearchFilterDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szFilterExamples;
	CTCAutomaticStackSearchFilter  m_cFilter[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchFilterDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_SEARCHFILTER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCAutomaticStackSearchFilter *pFilter);

private:
	BOOL EnumSearchKeys();

	VOID ShowFilterInfo();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchFilterDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchFilterDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddSearchKey();
	afx_msg void OnRemoveSearchKey();
	afx_msg void OnRemoveAllSearchKeys();
	afx_msg void OnSelchangeSearchKey();
	afx_msg void OnSelchangeKeyValue();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeKeyValue();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesParametersCalibrationPage dialog

#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCAutomaticStackItemPropertiesParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesParametersCalibrationPage)

	// Construction
public:
	CTCAutomaticStackItemPropertiesParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CUIntArray  m_nCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemPropertiesParametersCalibrationPage)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);

	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCAutomaticStackItemPropertiesParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesParametersFolderTabCtrl window

class CTCAutomaticStackItemPropertiesParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCAutomaticStackItemPropertiesParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesParametersFolder

class CTCAutomaticStackItemPropertiesParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesParametersFolder)

	// Construction
public:
	CTCAutomaticStackItemPropertiesParametersFolder();

	// Attributes
private:
	CTCAutomaticStackItemPropertiesParametersFolderTabCtrl  m_wndTabCtrl;
	CTCAutomaticStackItemPropertiesParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCAutomaticStackItemPropertiesParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesParametersDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_ITEM_STATIC   1002
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_ITEM   1003
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_FOLDER   1004
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_HELP   1005

class CTCAutomaticStackItemPropertiesParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesParametersDialog)

	// Construction
public:
	CTCAutomaticStackItemPropertiesParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szParameter;
private:
	CTCAutomaticStackItemPropertiesParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemPropertiesParametersDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter, CString &szValue);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CDisplayDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesParameterSetsDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERSETS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERSETS_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERSETS_NAME   1003
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERSETS_CONTENTS_STATIC   1004
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERSETS_CONTENTS   1005
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERSETS_HELP   1006

class CTCAutomaticStackItemPropertiesParameterSetsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesParameterSetsDialog)

	// Construction
public:
	CTCAutomaticStackItemPropertiesParameterSetsDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackItem  m_cItem;
	CString  m_szParameterSet;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemPropertiesParameterSetsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMPROPERTIESPARAMETERSETS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCAutomaticStackItem *pItem, CString &szParameterSet);

private:
	BOOL EnumParameterSets();

	VOID ShowParameterSetContents();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesParameterSetsDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesParameterSetsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeSet();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesSaveTemplateDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_NAME   1003
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_DESCRIPTION_STATIC   1004
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_DESCRIPTION   1005
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_LIST_STATIC   1006
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_LIST   1007
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_REMOVE   1008
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_REMOVEALL   1009
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_HELP   1010

class CTCAutomaticStackItemPropertiesSaveTemplateDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesSaveTemplateDialog)

	// Construction
public:
	CTCAutomaticStackItemPropertiesSaveTemplateDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackItem  m_cItem;
	CTCAutomaticStackComposedItem  m_cComposedItem;
	CTCAutomaticStackItemTemplates  m_pItemTemplates[2];
	CTCAutomaticStackComposedItemTemplates  m_pComposedItemTemplates[2];
	CStringArray  m_szTemplates;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemPropertiesSaveTemplateDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMPROPERTIESSAVETEMPLATE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCAutomaticStackItem *pItem);
	INT Create(CWnd *pParentWnd, CONST CTCAutomaticStackComposedItem *pItem);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID EnumTemplates();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesSaveTemplateDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesSaveTemplateDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRemoveTemplate();
	afx_msg void OnRemoveAllTemplates();
	afx_msg void OnEditchangeTemplateName();
	afx_msg void OnEditchangeTemplateDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesLoadTemplateDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_LIST   1002
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_NAME_STATIC   1003
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_NAME   1004
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_REMOVE   1005
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_REMOVEALL   1006
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_HELP   1007

class CTCAutomaticStackItemPropertiesLoadTemplateDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesLoadTemplateDialog)

	// Construction
public:
	CTCAutomaticStackItemPropertiesLoadTemplateDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackItem  m_cItem;
	CTCAutomaticStackComposedItem  m_cComposedItem;
	CTCAutomaticStackItemTemplates  m_pItemTemplates[2];
	CTCAutomaticStackComposedItemTemplates  m_pComposedItemTemplates[2];
	CStringArray  m_szTemplates;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemPropertiesLoadTemplateDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMPROPERTIESLOADTEMPLATE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCAutomaticStackItem *pItem);
	INT Create(CWnd *pParentWnd, CTCAutomaticStackComposedItem *pItem);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTemplates();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesLoadTemplateDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesLoadTemplateDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRemoveTemplate();
	afx_msg void OnRemoveAllTemplates();
	afx_msg void OnEditchangeTemplateName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemReleaseConstraintsDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_INTERLOCK   1002
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_INTERLOCK_NAME   1003
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKS   1004
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKED   1005
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKED_NAME   1006
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_INTERLOCKED_RESULT   1007
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_BLOCKED   1008
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_BLOCKED_NAME   1009
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_BLOCKMACRO   1010
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_GROUPED   1011
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW   1012
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_STATIC   1013
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_IMMEDIATELY   1014
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERPREVIOUS   1015
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERPREVIOUS_OFFSET   1016
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERPREVIOUS_STATIC   1017
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERFIRST_STATIC   1018
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERDISPATCH   1019
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERDISPATCH_OFFSET   1020
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_AFTERDISPATCH_STATIC   1021
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_OPEN   1022
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_START_OPENTIME   1023
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_STATIC   1024
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_INTERVAL   1025
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_INTERVAL_PERIOD   1026
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_INTERVAL_STATIC   1027
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_CLOSE   1028
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_CLOSETIME   1029
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_TIMEWINDOW_STOP_CLOSETIME_STATIC   1030
#define IDC_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_HELP   1031

// Specify the telecommand manual stack release constraints related limits
#define TCAUTOMATICSTACKITEMRELEASECONSTRAINTSDIALOG_MINIMUMTIMEWINDOWINTERVAL   1
#define TCAUTOMATICSTACKITEMRELEASECONSTRAINTSDIALOG_MAXIMUMTIMEWINDOWINTERVAL   SECONDSPERDAY
#define TCAUTOMATICSTACKITEMRELEASECONSTRAINTSDIALOG_DEFAULTTIMEWINDOWINTERVAL   SECONDSPERMINUTE

class CTCAutomaticStackItemReleaseConstraintsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemReleaseConstraintsDialog)

	// Construction
public:
	CTCAutomaticStackItemReleaseConstraintsDialog();   // standard constructor

	// Attributes
private:
	INT  m_nItemIndex;
	UINT  m_nPermissions;
	CTCInterlocks  m_pInterlocks[2];
	CTCAutomaticStackItem  m_cItem[2];
	CTCAutomaticStackComposedItem  m_cComposedItem[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemReleaseConstraintsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMRELEASECONSTRAINTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCAutomaticStackItem *pItem);
	INT Create(CWnd *pParentWnd, CTCAutomaticStackComposedItem *pComposedItem, INT nIndex = 0);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumInterlocks();
	BOOL EnumBlocks();

	VOID ShowConstraints();

	BOOL CheckTCVerificationStage(CONST CTCAutomaticStackItem *pItem, UINT nStage) CONST;

	BOOL CheckPrivileges(UINT nPermission = 0) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemReleaseConstraintsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemReleaseConstraintsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnInterlock();
	afx_msg void OnInterlocks();
	afx_msg void OnInterlocked();
	afx_msg void OnBlocked();
	afx_msg void OnBlockMacro();
	afx_msg void OnGrouped();
	afx_msg void OnTimeWindowImmediately();
	afx_msg void OnTimeWindowAfterPrevious();
	afx_msg void OnTimeWindowAfterDispatch();
	afx_msg void OnTimeWindowOpen();
	afx_msg void OnTimeWindowClose();
	afx_msg void OnTimeWindowInterval();
	afx_msg void OnSelchangeInterlock();
	afx_msg void OnSelchangeInterlocked();
	afx_msg void OnSelchangeInterlockedResult();
	afx_msg void OnSpinchangeTimeWindowAfterPrevious();
	afx_msg void OnSpinchangeTimeWindowAfterDispatch();
	afx_msg void OnSpinchangeTimeWindowOpen();
	afx_msg void OnSpinchangeTimeWindowClose();
	afx_msg void OnSpinchangeTimeWindowInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemReleaseInterlocksDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_NAME   1003
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_ADD   1004
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_REMOVE   1005
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_REMOVEALL   1006
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES   1007
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_STATIC   1008
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_GLOBAL   1009
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_LOCAL   1010
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM   1011
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME   1012
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS   1013
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE   1014
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_STATIC   1015
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_RECEPTION   1016
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_TRANSMISSION   1017
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE   1018
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_START   1019
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_PROGRESS   1020
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_PROPERTIES_STAGE_COMPLETION   1021
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_HELP   1022

class CTCAutomaticStackItemReleaseInterlocksDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemReleaseInterlocksDialog)

	// Construction
public:
	CTCAutomaticStackItemReleaseInterlocksDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nPermissions;
	ULONGLONG  m_nInterlockFlags;
	CTCInterlocks  m_pInterlocks[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemReleaseInterlocksDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMRELEASEINTERLOCKS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, ULONGLONG nInterlockFlags, CTCInterlocks &pInterlocks);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumInterlocks();
	BOOL EnumSubSystems();

	VOID ShowProperties();

	CTCInterlock *FindInterlock() CONST;

	UINT TranslateToSubSystemID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

	BOOL CanAddInterlock() CONST;
	BOOL CanRemoveInterlock() CONST;
	BOOL CanRemoveAllInterlocks() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemReleaseInterlocksDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemReleaseInterlocksDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnScopeGlobal();
	afx_msg void OnScopeLocal();
	afx_msg void OnScopeSubSystem();
	afx_msg void OnScopeTeleommands();
	afx_msg void OnScopeNoWaitState();
	afx_msg void OnStageTransmission();
	afx_msg void OnStageReception();
	afx_msg void OnStageAcceptance();
	afx_msg void OnStageStart();
	afx_msg void OnStageProgress();
	afx_msg void OnStageCompletion();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeSubSystem();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemReleaseBlockMacroDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_NAME   1003
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_DESCRIPTION_STATIC   1004
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_DESCRIPTION   1005
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_MEMBERS_STATIC   1006
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_MEMBERS   1007
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_STATIC   1008
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS   1009
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_ADD   1010
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_REMOVE   1011
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_REMOVEALL   1012
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_CONTENTS_REMARK   1013
#define IDC_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_HELP   1014

class CTCAutomaticStackItemReleaseBlockMacroDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemReleaseBlockMacroDialog)

	// Construction
public:
	CTCAutomaticStackItemReleaseBlockMacroDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackComposedItem  m_cItem[2];
	CStringArray  m_szMembers;
	UINT  m_nPermissions;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemReleaseBlockMacroDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMRELEASEBLOCKMACRO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCAutomaticStackComposedItem *pItem);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumBlockMembers();

	VOID ShowMacroContents();
	BOOL CheckMacroSize() CONST;

	BOOL CheckPrivileges(UINT nPermission = 0) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemReleaseBlockMacroDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemReleaseBlockMacroDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddMember();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackItemPropertiesDialog dialog

#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_NAME   1003
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS   1006
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV   1007
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV   1008
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV   1009
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_DISABLEPTV   1010
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_DISABLEPEV   1011
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_DISABLECEV   1012
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED   1013
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_CONSTRAINTS_RELEASE   1014
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION   1015
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY   1016
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG   1017
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME   1018
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT   1019
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_COUNT   1020
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_STATIC   1021
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_TIME_STATIC   1022
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_OBRT_TIME   1023
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ONBOARDEXECUTION_2STEP   1024
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS   1025
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_ACCEPTANCE   1026
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_START   1027
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_PROGRESS   1028
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_ACKNOWLEDGMENTS_COMPLETION   1029
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS   1030
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_LIST   1031
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_REMARK   1032
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_NOEXTRAPOLATION   1033
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_SHOWALL   1034
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_VALUE_STATIC   1035
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_VALUE   1036
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_SETVALUE   1037
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_LOADVALUES   1038
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_PARAMETERS_LOADDYNAMICVALUE   1039
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_SAVETEMPLATE   1040
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_LOADTEMPLATE   1041
#define IDC_TCAUTOMATICSTACK_ITEMPROPERTIES_HELP   1042

class CTCAutomaticStackItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackItemPropertiesDialog)

	// Construction
public:
	CTCAutomaticStackItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackItem  m_cItem[2];
	UINT  m_nPermissions;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackItemPropertiesDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_ITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCAutomaticStackItem *pItem);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();
	VOID ShowParameters();

	VOID EvaluateParameters();

	BOOL HasTemplates() CONST;

	BOOL CheckTCVerificationStage(UINT nStage) CONST;
	BOOL CheckTCParameterValue(CONST CDatabaseTCFunctionElement *pFunctionElement) CONST;
	BOOL CheckTCParameterValue(CONST CDatabaseTCPacketParameter *pPacketParameter) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	BOOL CheckPrivileges(UINT nPermission = 0) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackItemPropertiesDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnOverridePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisablePTV();
	afx_msg void OnDisablePEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnPreAuthorize();
	afx_msg void OnReleaseConstraints();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnExecuteAtOBRT();
	afx_msg void OnExecuteAs2Step();
	afx_msg void OnAcknowledgeAcceptance();
	afx_msg void OnAcknowledgeStart();
	afx_msg void OnAcknowledgeProgress();
	afx_msg void OnAcknowledgeCompletion();
	afx_msg void OnNoExtrapolation();
	afx_msg void OnShowAllParameters();
	afx_msg void OnSetParameterValue();
	afx_msg void OnLoadParameterValues();
	afx_msg void OnLoadDynamicParameterValue();
	afx_msg void OnSaveTemplate();
	afx_msg void OnLoadTemplate();
	afx_msg void OnEditchangeParameterValue();
	afx_msg void OnEditchangeExecutionOBRT();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackComposedItemPropertiesDialog dialog

#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_NAME   1003
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_STATIC   1006
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY   1007
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_APPLYTOALL   1008
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PROPERTIES   1009
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS   1010
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV   1011
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV   1012
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV   1013
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV   1014
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV   1015
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV   1016
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED   1017
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASE   1018
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION   1019
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY   1020
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG   1021
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME   1022
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OFFSET   1023
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OFFSET_TIME   1024
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OFFSET_AFTERPREVIOUS   1025
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT   1026
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_COUNT   1027
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_STATIC   1028
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_TIME_STATIC   1029
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_OBRT_TIME   1030
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_2STEP   1031
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS   1032
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST   1033
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK   1034
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_NOEXTRAPOLATION   1035
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL   1036
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST   1037
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_VALUE_STATIC   1038
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_VALUE   1039
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SETVALUE   1040
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LOADVALUES   1041
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LOADDYNAMICVALUE   1042
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_SAVETEMPLATE   1043
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_LOADTEMPLATE   1044
#define IDC_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_HELP   1045

// Specify the telecommand automatic stack composed item properties related limits
#define TCAUTOMATICSTACKCOMPOSEDITEMPROPERTIESDIALOG_MINIMUMEXECUTIONTIMEOFFSET   -(365*SECONDSPERDAY)
#define TCAUTOMATICSTACKCOMPOSEDITEMPROPERTIESDIALOG_MAXIMUMEXECUTIONTIMEOFFSET   (365*SECONDSPERDAY)
#define TCAUTOMATICSTACKCOMPOSEDITEMPROPERTIESDIALOG_DEFAULTEXECUTIONTIMEOFFSET   0

class CTCAutomaticStackComposedItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackComposedItemPropertiesDialog)

	// Construction
public:
	CTCAutomaticStackComposedItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackComposedItem  m_cItem[2];
	UINT  m_nPermissions;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackComposedItemPropertiesDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_COMPOSEDITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCAutomaticStackComposedItem *pItem);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumEntries();

	VOID ShowProperties();
	VOID ShowParameters();

	VOID EvaluateParameters();

	BOOL HasTemplates() CONST;

	BOOL CheckTCExecutionType(CONST CTCAutomaticStackItem *pItem) CONST;
	BOOL CheckTCParameterValue(CONST CDatabaseTCFunctionElement *pFunctionElement) CONST;
	BOOL CheckTCParameterValue(CONST CDatabaseTCPacketParameter *pPacketParameter) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	BOOL CheckPrivileges(UINT nPermission = 0) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackComposedItemPropertiesDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackComposedItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnApplyToAll();
	afx_msg void OnOverridePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisablePTV();
	afx_msg void OnDisablePEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnPreAuthorize();
	afx_msg void OnReleaseConstraints();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnExecuteAtOffset();
	afx_msg void OnExecuteAtOffsetAfterPrevious();
	afx_msg void OnExecuteAtOBRT();
	afx_msg void OnExecuteAs2Step();
	afx_msg void OnShowFormalParameters();
	afx_msg void OnNoExtrapolation();
	afx_msg void OnShowAllParameters();
	afx_msg void OnSetParameterValue();
	afx_msg void OnLoadParameterValues();
	afx_msg void OnLoadDynamicParameterValue();
	afx_msg void OnSaveTemplate();
	afx_msg void OnLoadTemplate();
	afx_msg void OnSelchangeEntry();
	afx_msg void OnEditchangeParameterValue();
	afx_msg void OnEditchangeExecutionOBRT();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeExecutionOffset();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackHistoricalItemPropertiesDialog dialog

#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_NAME   1003
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS   1006
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV   1007
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV   1008
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV   1009
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_DISABLEPTV   1010
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_DISABLEPEV   1011
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_DISABLECEV   1012
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED   1013
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW   1014
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC   1015
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME   1016
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC   1017
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME   1018
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED   1019
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC   1020
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME   1021
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC   1022
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY   1023
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_ONBOARDEXECUTION   1024
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY   1025
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG   1026
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME   1027
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_ONBOARDEXECUTION_FIRSTSTEP   1028
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_ONBOARDEXECUTION_SECONDSTEP   1029
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_PARAMETERS   1030
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_PARAMETERS_LIST   1031
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_PARAMETERS_REMARK   1032
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_PARAMETERS_SHOWALL   1033
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_RAWDATA   1034
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_RAWDATA_AREA   1035
#define IDC_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_HELP   1036

class CTCAutomaticStackHistoricalItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackHistoricalItemPropertiesDialog)

	// Construction
public:
	CTCAutomaticStackHistoricalItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackItem  m_cItem;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackHistoricalItemPropertiesDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_HISTORICALITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCAutomaticStackItem *pItem);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();
	VOID ShowParameters();
	VOID ShowRawData();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackHistoricalItemPropertiesDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackHistoricalItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowAllParameters();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackHistoricalComposedItemPropertiesDialog dialog

#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_NAME   1003
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_STATIC   1006
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY   1007
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_PROPERTIES   1008
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS   1009
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV   1010
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV   1011
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV   1012
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV   1013
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV   1014
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV   1015
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED   1016
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW   1017
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC   1018
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME   1019
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_NONE   1020
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC   1021
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME   1022
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_NONE   1023
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED   1024
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC   1025
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME   1026
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_NONE   1027
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_EXECUTIONTIME_STATIC   1028
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC   1029
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY   1030
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_NONE   1031
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION   1032
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY   1033
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG   1034
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME   1035
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP   1036
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP   1037
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS   1038
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST   1039
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK   1040
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST   1041
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL   1042
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_RAWDATA   1043
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA   1044
#define IDC_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_HELP   1045

class CTCAutomaticStackHistoricalComposedItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackHistoricalComposedItemPropertiesDialog)

	// Construction
public:
	CTCAutomaticStackHistoricalComposedItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szRawData[2];
	CTCAutomaticStackItems  m_pItems;
	CDatabaseTCParameters  m_pParameters;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackHistoricalComposedItemPropertiesDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_HISTORICALCOMPOSEDITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCAutomaticStackItems &pItems);

	CTCAutomaticStackWnd *GetParentDisplay() CONST;

private:
	BOOL EnumEntries();

	VOID ShowProperties();
	VOID ShowParameters();
	VOID ShowRawData();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackHistoricalComposedItemPropertiesDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackHistoricalComposedItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeEntry();
	afx_msg void OnShowAllParameters();
	afx_msg void OnShowFormalParameters();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSaveContentsDialog dialog

#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_NAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_NAME   1003
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_DESCRIPTION_STATIC   1004
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_DESCRIPTION   1005
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_OPTIONS_STATIC   1006
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_OPTIONS_RELATIVERELEASETIMES   1007
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_OPTIONS_RELATIVEEXECUTIONTIMES   1008
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_STATUS_STATIC   1009
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_STATUS_VALIDATED   1010
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_LIST   1011
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY   1012
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_FILENAME_STATIC   1013
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_FILENAME   1014
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_FILENAME_BROWSE   1015
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_FILENAME_INSPECT   1016
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_FILENAME_REMARK   1017
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_LIST   1018
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_LIST_REMOVE   1019
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_REPOSITORY_LIST_REMOVEALL  1020
#define IDC_TCAUTOMATICSTACK_SAVECONTENTS_HELP   1021

class CTCAutomaticStackSaveContentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSaveContentsDialog)

	// Construction
public:
	CTCAutomaticStackSaveContentsDialog();   // standard constructor

	// Attributes
private:
	CTCAutomaticStackItems  m_pItems[2];
private:
	CStringArray  m_szColumns[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSaveContentsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_SAVECONTENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCAutomaticStackItems &pItems);

	class CTCAutomaticStackWnd *GetParent() CONST;

private:
	BOOL EnumStackMembers();
	BOOL EnumRepositoryMembers();

	BOOL SaveRepository(CFileEx &cFile, CONST CTCSavedStacks &pStacks);
	BOOL SaveRepository(LPCTSTR pszFileName, CONST CTCSavedStacks &pStacks);
	BOOL LoadRepository(CFileEx &cFile, CTCSavedStacks &pStacks) CONST;
	BOOL LoadRepository(LPCTSTR pszFileName, CTCSavedStacks &pStacks) CONST;

	BOOL LogActivity(LPCTSTR pszFileName, BOOL bDeleted = FALSE);
	BOOL LogActivity(CONST CTCSavedStack *pStack, BOOL bDeleted = FALSE);

	INT FindColumnIndex(UINT nID, LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSaveContentsDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSaveContentsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRelativeReleaseTimes();
	afx_msg void OnRelativeExecutionTimes();
	afx_msg void OnBrowseFileName();
	afx_msg void OnInspectRepository();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackLoadContentsDialog dialog

#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILENAME_STATIC   1002
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILENAME   1003
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILENAME_BROWSE   1004
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILENAME_INSPECT   1005
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILENAME_DELETE   1006
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILTER_STATIC   1007
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILTER   1008
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILTER_ADD   1009
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILTER_MODIFY   1010
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILTER_REMOVE   1011
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_FILTER_REMOVEALL   1012
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES   1013
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_LIST   1014
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_LIST_REMOVE   1015
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_LIST_REMOVEALL   1016
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_VALIDATE   1017
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_LOADANYWAY   1018
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_REMARK   1019
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_CONTENTS_STATIC   1020
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_PROPERTIES_CONTENTS_LIST   1021
#define IDC_TCAUTOMATICSTACK_LOADCONTENTS_HELP   1022

class CTCAutomaticStackLoadContentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackLoadContentsDialog)

	// Construction
public:
	CTCAutomaticStackLoadContentsDialog();   // standard constructor

	// Attributes
private:
	CTCSavedStacks  m_pRepository;
	CTCAutomaticStackItems  m_pItems;
	CTCAutomaticStackSearchFilters  m_pFilters;
private:
	CStringArray  m_szColumns[2];

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackLoadContentsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_LOADCONTENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCAutomaticStackWnd *GetParent() CONST;

private:
	BOOL EnumFilters();
	BOOL EnumRepositoryMembers();
	BOOL EnumStackMembers();

	BOOL SaveRepository(CFileEx &cFile, CONST CTCSavedStacks &pStacks);
	BOOL SaveRepository(LPCTSTR pszFileName, CONST CTCSavedStacks &pStacks);
	BOOL LoadRepository(CFileEx &cFile, CTCSavedStacks &pStacks) CONST;
	BOOL LoadRepository(LPCTSTR pszFileName, CTCSavedStacks &pStacks) CONST;

	BOOL LogActivity(LPCTSTR pszFileName, BOOL bDeleted = FALSE);
	BOOL LogActivity(CONST CTCSavedStack *pStack, BOOL bDeleted = FALSE);

	BOOL CheckFilter(CONST CTCSavedStack *pStack) CONST;

	INT ExtractFilterValues(LPCTSTR pszValues, CStringArray &szSearchValues, CUIntArray &nSearchOperators) CONST;
	CString ExtractFilterValue(LPCTSTR pszValue) CONST;

	INT FindColumnIndex(UINT nID, LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackLoadContentsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackLoadContentsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnInspectRepository();
	afx_msg void OnDeleteRepository();
	afx_msg void OnAddFilter();
	afx_msg void OnModifyFilter();
	afx_msg void OnRemoveFilter();
	afx_msg void OnRemoveAllFilters();
	afx_msg void OnValidateMember();
	afx_msg void OnLoadMemberAnyway();
	afx_msg void OnRemoveMember();
	afx_msg void OnRemoveAllMembers();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFilter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackInterlocksDialog dialog

#define IDC_TCAUTOMATICSTACK_INTERLOCKS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_INTERLOCKS_LIST   1002
#define IDC_TCAUTOMATICSTACK_INTERLOCKS_RESET   1003
#define IDC_TCAUTOMATICSTACK_INTERLOCKS_RESETALL   1004
#define IDC_TCAUTOMATICSTACK_INTERLOCKS_HELP   1005

class CTCAutomaticStackInterlocksDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackInterlocksDialog)

	// Construction
public:
	CTCAutomaticStackInterlocksDialog();   // standard constructor

	// Attributes
private:
	CTCInterlocks  m_pInterlocks[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackInterlocksDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_INTERLOCKS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCInterlocks &pInterlocks);

	class CTCAutomaticStackWnd *GetParent() CONST;

private:
	BOOL EnumInterlocks();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackInterlocksDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackInterlocksDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReset();
	afx_msg void OnResetAll();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSubSystemsDialog dialog

#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_DETAILS   1001
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_LIST_STATIC   1002
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_LIST   1003
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR   1004
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR_STATIC   1005
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR_ENABLED   1006
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR_ENABLEBYEVENT   1007
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR_ENABLEEVENTNAME   1008
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR_DISABLED   1009
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR_DISABLEBYEVENT   1010
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_BEHAVIOR_DISABLEEVENTNAME   1011
#define IDC_TCAUTOMATICSTACK_SUBSYSTEMS_HELP   1012

class CTCAutomaticStackSubSystemsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSubSystemsDialog)

	// Construction
public:
	CTCAutomaticStackSubSystemsDialog();   // standard constructor

	// Attributes
private:
	CUIntArray  m_nSubSystemIDs[2];
	CUIntArray  m_nSubSystemStatus[2];
	CStringArray  m_szSubSystemEvents[2][2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSubSystemsDialog)
	enum { IDD = IDD_TCAUTOMATICSTACK_SUBSYSTEMS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CUIntArray &nSubSystemIDs, CByteArray &bSubSystemStatus);

	class CTCAutomaticStackWnd *GetParent() CONST;

private:
	BOOL EnumSubSystems();
	BOOL EnumEvents();

	VOID ShowDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSubSystemsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSubSystemsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEnableSubSystem();
	afx_msg void OnDisableSubSystem();
	afx_msg void OnUseEnableSubSystemEvent();
	afx_msg void OnUseDisableSubSystemEvent();
	afx_msg void OnSelchangeEnableSubSystemEvent();
	afx_msg void OnSelchangeDisableSubSystemEvent();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchNumberDialog dialog

class CTCAutomaticStackSearchNumberDialog : public CTCStackSearchNumberDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchNumberDialog)

	// Construction
public:
	CTCAutomaticStackSearchNumberDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchNumberDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchNumberDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchNumberDialog)
	afx_msg void OnGotoNumber();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchNameDialog dialog

class CTCAutomaticStackSearchNameDialog : public CTCStackSearchNameDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchNameDialog)

	// Construction
public:
	CTCAutomaticStackSearchNameDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchNameDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchNameDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchNameDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchDescriptionDialog dialog

class CTCAutomaticStackSearchDescriptionDialog : public CTCStackSearchDescriptionDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchDescriptionDialog)

	// Construction
public:
	CTCAutomaticStackSearchDescriptionDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchDescriptionDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchDescriptionDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchDescriptionDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchCategoryDialog dialog

class CTCAutomaticStackSearchCategoryDialog : public CTCStackSearchCategoryDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchCategoryDialog)

	// Construction
public:
	CTCAutomaticStackSearchCategoryDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchCategoryDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchCategoryDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchCategoryDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchSubSystemDialog dialog

class CTCAutomaticStackSearchSubSystemDialog : public CTCStackSearchSubSystemDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchSubSystemDialog)

	// Construction
public:
	CTCAutomaticStackSearchSubSystemDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchSubSystemDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchSubSystemDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchSubSystemDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchArgumentsDialog dialog

class CTCAutomaticStackSearchArgumentsDialog : public CTCStackSearchArgumentsDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchArgumentsDialog)

	// Construction
public:
	CTCAutomaticStackSearchArgumentsDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchArgumentsDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchArgumentsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchArgumentsDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchFlagsDialog dialog

class CTCAutomaticStackSearchFlagsDialog : public CTCStackSearchFlagsDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchFlagsDialog)

	// Construction
public:
	CTCAutomaticStackSearchFlagsDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchFlagsDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchFlagsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchFlagsDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchTCPacketDialog dialog

class CTCAutomaticStackSearchTCPacketDialog : public CTCStackSearchTCPacketDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchTCPacketDialog)

	// Construction
public:
	CTCAutomaticStackSearchTCPacketDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchTCPacketDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchTCPacketDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchTCPacketDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchDispatchTimeDialog dialog

class CTCAutomaticStackSearchDispatchTimeDialog : public CTCStackSearchDispatchTimeDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchDispatchTimeDialog)

	// Construction
public:
	CTCAutomaticStackSearchDispatchTimeDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchDispatchTimeDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchDispatchTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchDispatchTimeDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchReleaseTimeDialog dialog

class CTCAutomaticStackSearchReleaseTimeDialog : public CTCStackSearchReleaseTimeDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchReleaseTimeDialog)

	// Construction
public:
	CTCAutomaticStackSearchReleaseTimeDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchReleaseTimeDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchReleaseTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchReleaseTimeDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchReleaseTimeOffsetDialog dialog

class CTCAutomaticStackSearchReleaseTimeOffsetDialog : public CTCStackSearchReleaseTimeOffsetDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchReleaseTimeOffsetDialog)

	// Construction
public:
	CTCAutomaticStackSearchReleaseTimeOffsetDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchReleaseTimeOffsetDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchReleaseTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchReleaseTimeOffsetDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchTransmissionTimeDialog dialog

class CTCAutomaticStackSearchTransmissionTimeDialog : public CTCStackSearchTransmissionTimeDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchTransmissionTimeDialog)

	// Construction
public:
	CTCAutomaticStackSearchTransmissionTimeDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchTransmissionTimeDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchTransmissionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchTransmissionTimeDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchExecutionTimeDialog dialog

class CTCAutomaticStackSearchExecutionTimeDialog : public CTCStackSearchExecutionTimeDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchExecutionTimeDialog)

	// Construction
public:
	CTCAutomaticStackSearchExecutionTimeDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchExecutionTimeDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchExecutionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchExecutionTimeDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchExecutionTimeOffsetDialog dialog

class CTCAutomaticStackSearchExecutionTimeOffsetDialog : public CTCStackSearchExecutionTimeOffsetDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchExecutionTimeOffsetDialog)

	// Construction
public:
	CTCAutomaticStackSearchExecutionTimeOffsetDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchExecutionTimeOffsetDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchExecutionTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchExecutionTimeOffsetDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchAuthorizationDialog dialog

class CTCAutomaticStackSearchAuthorizationDialog : public CTCStackSearchAuthorizationDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchAuthorizationDialog)

	// Construction
public:
	CTCAutomaticStackSearchAuthorizationDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchAuthorizationDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchAuthorizationDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchAuthorizationDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchPTVTimeWindowDialog dialog

class CTCAutomaticStackSearchPTVTimeWindowDialog : public CTCStackSearchPTVTimeWindowDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchPTVTimeWindowDialog)

	// Construction
public:
	CTCAutomaticStackSearchPTVTimeWindowDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchPTVTimeWindowDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchPTVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchPTVTimeWindowDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchPTVCheckDialog dialog

class CTCAutomaticStackSearchPTVCheckDialog : public CTCStackSearchPTVCheckDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchPTVCheckDialog)

	// Construction
public:
	CTCAutomaticStackSearchPTVCheckDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchPTVCheckDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchPTVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchPTVCheckDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchPTVResultDialog dialog

class CTCAutomaticStackSearchPTVResultDialog : public CTCStackSearchPTVResultDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchPTVResultDialog)

	// Construction
public:
	CTCAutomaticStackSearchPTVResultDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchPTVResultDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchPTVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchPTVResultDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchPEVCheckDialog dialog

class CTCAutomaticStackSearchPEVCheckDialog : public CTCStackSearchPEVCheckDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchPEVCheckDialog)

	// Construction
public:
	CTCAutomaticStackSearchPEVCheckDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchPEVCheckDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchPEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchPEVCheckDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchPEVResultDialog dialog

class CTCAutomaticStackSearchPEVResultDialog : public CTCStackSearchPEVResultDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchPEVResultDialog)

	// Construction
public:
	CTCAutomaticStackSearchPEVResultDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchPEVResultDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchPEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchPEVResultDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchCEVTimeWindowDialog dialog

class CTCAutomaticStackSearchCEVTimeWindowDialog : public CTCStackSearchCEVTimeWindowDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchCEVTimeWindowDialog)

	// Construction
public:
	CTCAutomaticStackSearchCEVTimeWindowDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchCEVTimeWindowDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchCEVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchCEVTimeWindowDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchCEVCheckDialog dialog

class CTCAutomaticStackSearchCEVCheckDialog : public CTCStackSearchCEVCheckDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchCEVCheckDialog)

	// Construction
public:
	CTCAutomaticStackSearchCEVCheckDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchCEVCheckDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchCEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchCEVCheckDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchCEVResultDialog dialog

class CTCAutomaticStackSearchCEVResultDialog : public CTCStackSearchCEVResultDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchCEVResultDialog)

	// Construction
public:
	CTCAutomaticStackSearchCEVResultDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchCEVResultDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchCEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchCEVResultDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackSearchStatusDialog dialog

class CTCAutomaticStackSearchStatusDialog : public CTCStackSearchStatusDialog
{
	DECLARE_DYNCREATE(CTCAutomaticStackSearchStatusDialog)

	// Construction
public:
	CTCAutomaticStackSearchStatusDialog();   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CTCAutomaticStackSearchStatusDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCAutomaticStackPageTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackSearchStatusDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackSearchStatusDialog)
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackToolBar window

class CTCAutomaticStackToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTCAutomaticStackToolBar)

	// Construction
public:
	CTCAutomaticStackToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackStatusBar window

class CTCAutomaticStackStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTCAutomaticStackStatusBar)

	// Construction
public:
	CTCAutomaticStackStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTCAutomaticStackWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackToolTip window

class CTCAutomaticStackToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTCAutomaticStackToolTip)

	// Construction
public:
	CTCAutomaticStackToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackDocument

class CTCAutomaticStackDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCAutomaticStackDocument)

	// Construction
public:
	CTCAutomaticStackDocument();
	virtual ~CTCAutomaticStackDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackPageTextView window

// Specify the telecommand automatic stack page text view command flag symbol identifiers
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCK   0
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKIDLE   1
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKPENDING   2
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKSUCCESS   3
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKFAILURE   4
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOL_GROUPED   5
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOL_BLOCKED   6
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOLS   7
// Specify the telecommand automatic stack page text view command check flag symbol identifiers
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDCHECKFLAGSYMBOL_NONE   0
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDCHECKFLAGSYMBOL_ON   1
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDCHECKFLAGSYMBOL_OFF   2
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED   3
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDCHECKFLAGSYMBOLS   4
// Specify the telecommand automatic stack page text view command result symbol identifiers
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_PTV_GO   0
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_PTV_WAIT   1
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_PTV_FAIL   2
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_PEV_GO   3
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_PEV_NOGO   4
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_CEV_IDLE   5
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_CEV_PENDING   6
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_CEV_PASSED   7
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_CEV_FAILED   8
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_CEV_UNKNOWN   9
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOL_CEV_UNVERIFIED   10
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOLS   11
// Specify the telecommand automatic stack page text view command alert symbol identifiers
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDALERTSYMBOLS   3
// Specify the telecommand automatic stack page text view command update timer identifiers
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDUPDATE_TIMERID   100
#define TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDUPDATE_TIMEOUT   1000
// Specify the telecommand automatic stack page visual aspect related identifiers
#define TCAUTOMATICSTACKPAGETEXTVIEW_COLUMNTRANSPARENCY   0x30

class CTCAutomaticStackPageTextView : public CTextView
{
	DECLARE_DYNCREATE(CTCAutomaticStackPageTextView)

	// Construction
public:
	CTCAutomaticStackPageTextView();

	// Attributes
protected:
	UINT  m_nPane;
protected:
	INT  m_nChecks;
	INT  m_nArguments;
	INT  m_nSearchIndex;
	BOOL  m_bProperties;
	BOOL  m_bAllArguments;
	BOOL  m_bFullViewMode;
	UINT  m_nFilterMode[2];
	UINT  m_nFilterLimitation;
	UINT  m_nMiscellaneousOptions;
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	UINT  m_nTelecommandingUplinkState;
	BOOL  m_bTelecommandingInterlockMode;
	BOOL  m_bTelecommandingReleaseWaitMode;
	BOOL  m_bTelecommandingAutoRejectionMode;
	CString  m_szFilterComputer;
	CString  m_szFilterTelecommand[2];
	CTimeSpan  m_tDefaultReleaseTimeWindow;
	CTimeSpan  m_tDispatchTimeWindow;
	CUIntArray  m_nFilterSubSystems;
protected:
	CSize  m_sizeFlagSymbols;
	CSize  m_sizeAlertSymbols;
	CSize  m_sizeResultSymbols;
	CSize  m_sizeCheckFlagSymbols;
	CImage  *m_pFlagSymbols[TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDFLAGSYMBOLS];
	CImage  *m_pCheckFlagSymbols[TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDCHECKFLAGSYMBOLS];
	CImage  *m_pResultSymbols[TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDRESULTSYMBOLS];
	CImage  *m_pAlertSymbols[TCAUTOMATICSTACKPAGETEXTVIEW_COMMANDALERTSYMBOLS];
	CTCAutomaticStackToolTip  m_wndToolTip;
	COLORREF  m_nBackgroundColor[2];
	CUIntArray  m_nStatusColors[2];
	CUIntArray  m_nAlertColors;
	HCURSOR  m_hToolTipCursor;
	UINT  m_nClipboardFormat;
	BOOL  m_bToolTips;
protected:
	CTCProcessEngine  *m_pTCProcessEngine;
	CTCEnvironment  *m_pTCEnvironment;
protected:
	CTCInterlocks  m_pInterlocks;
	CTCAutomaticStackItems  m_pItems[2];
protected:
	CTCAutomaticStackSearchNameDialog  m_dlgSearchName;
	CTCAutomaticStackSearchFlagsDialog  m_dlgSearchFlags;
	CTCAutomaticStackSearchNumberDialog  m_dlgSearchNumber;
	CTCAutomaticStackSearchStatusDialog  m_dlgSearchStatus;
	CTCAutomaticStackSearchCategoryDialog  m_dlgSearchCategory;
	CTCAutomaticStackSearchTCPacketDialog  m_dlgSearchTCPacket;
	CTCAutomaticStackSearchPTVCheckDialog  m_dlgSearchPTVCheck;
	CTCAutomaticStackSearchPEVCheckDialog  m_dlgSearchPEVCheck;
	CTCAutomaticStackSearchCEVCheckDialog  m_dlgSearchCEVCheck;
	CTCAutomaticStackSearchSubSystemDialog  m_dlgSearchSubSystem;
	CTCAutomaticStackSearchArgumentsDialog  m_dlgSearchArguments;
	CTCAutomaticStackSearchPTVResultDialog  m_dlgSearchPTVResult;
	CTCAutomaticStackSearchPEVResultDialog  m_dlgSearchPEVResult;
	CTCAutomaticStackSearchCEVResultDialog  m_dlgSearchCEVResult;
	CTCAutomaticStackSearchDescriptionDialog  m_dlgSearchDescription;
	CTCAutomaticStackSearchReleaseTimeDialog  m_dlgSearchReleaseTime;
	CTCAutomaticStackSearchDispatchTimeDialog  m_dlgSearchDispatchTime;
	CTCAutomaticStackSearchExecutionTimeDialog  m_dlgSearchExecutionTime;
	CTCAutomaticStackSearchPTVTimeWindowDialog  m_dlgSearchPTVTimeWindow;
	CTCAutomaticStackSearchCEVTimeWindowDialog  m_dlgSearchCEVTimeWindow;
	CTCAutomaticStackSearchAuthorizationDialog  m_dlgSearchAuthorization;
	CTCAutomaticStackSearchTransmissionTimeDialog  m_dlgSearchTransmissionTime;
	CTCAutomaticStackSearchReleaseTimeOffsetDialog  m_dlgSearchReleaseTimeOffset;
	CTCAutomaticStackSearchExecutionTimeOffsetDialog  m_dlgSearchExecutionTimeOffset;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, UINT nPane, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetAlertColors(CONST CUIntArray &nColors);
	BOOL GetAlertColors(CUIntArray &nColors) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = 0);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterTelecommandSubSystems(CONST CUIntArray &nSubSystems);
	BOOL GetFilterTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode = 0);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCAutomaticStackItems &pItems, BOOL bReload = FALSE, BOOL bBefore = FALSE, BOOL bAfter = FALSE, BOOL bRedraw = TRUE);
	BOOL LoadTelecommands(CONST CTCAutomaticStackItems &pItems, INT nIndex, BOOL bReload = FALSE, BOOL bBefore = FALSE, BOOL bAfter = FALSE, BOOL bRedraw = TRUE);
	BOOL ReloadTelecommands(CONST CTCAutomaticStackItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);
	BOOL UpdateTelecommands();

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL SelectTelecommand(INT nIndex);
	BOOL DoSelectAllTelecommands();
	BOOL CanSelectAllTelecommands() CONST;
	BOOL DoUnselectAllTelecommands();
	INT EnumSelectedTelecommands(CTCAutomaticStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands(UINT nStatus = 0) CONST;

	BOOL DispatchTelecommands();

	UINT GetTelecommandCount() CONST;

	BOOL DoCutTelecommand();
	BOOL CanCutTelecommand() CONST;
	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoPasteTelecommand();
	BOOL CanPasteTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL DoAcknowledgeTelecommand();
	BOOL CanAcknowledgeTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL SearchTelecommandByNumber(INT nNumber);
	BOOL SearchTelecommandByName(LPCTSTR pszName, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchTelecommandByCategory(LPCTSTR pszCategory, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandBySubSystem(LPCTSTR pszSubSystem, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchTelecommandByArgument(LPCTSTR pszArgument, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByFlags(BOOL bDown, BOOL bAll, BOOL bInterlocking, BOOL bInterlocked, BOOL bGrouped, BOOL bBlocked);
	BOOL SearchTelecommandByTCPacket(LPCTSTR pszPacket, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDispatchTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTimeOffset(DWORD dwOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByTransmissionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTimeOffset(CONST CTimeSpan &tOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByAuthorization(UINT nAuthorization, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByStatus(LPCTSTR pszStatus, BOOL bDown, BOOL bAll);

	BOOL GetPrintProperties(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bFilter = FALSE, BOOL bRedraw = TRUE);

	class CTCAutomaticStackPageView *GetParent() CONST;
	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

protected:
	BOOL ShowTelecommandProperties(INT nIndex);
	BOOL ShowTelecommandProperties(INT nIndex, CTCAutomaticStackComposedItem *pItem);

	BOOL InsertTelecommand(INT nIndex, CTCAutomaticStackItem *pItem);
	BOOL UpdateTelecommand(INT nIndex);
	BOOL DeleteTelecommand(INT nIndex);

	BOOL ActivateTelecommand(INT nIndex, BOOL bActivate = TRUE, BOOL bRedraw = TRUE);
	BOOL IsActivatedTelecommand(INT nIndex) CONST;

	VOID ResetTelecommand(CTCAutomaticStackItem *pItem) CONST;

	CString TranslateTelecommand(CONST CTCAutomaticStackItem *pItem, BOOL bFirst) CONST;
	BOOL TranslateTelecommand(CONST CTCAutomaticStackItem *pItem, CTextViewAttribute *pAttribute) CONST;

	BOOL AdjustTelecommandAlerts(CONST CTCItem *pAlertItem, CTCAutomaticStackItem *pItem, BOOL bAlert = TRUE) CONST;

	BOOL CheckTelecommandFilter(CONST CTCItem *pItem) CONST;

	BOOL CheckTelecommandReleaseWindow(CONST CTCAutomaticStackItem *pItem) CONST;
	BOOL CheckTelecommandReleaseWindow(CONST CTimeTag &tTime, CONST CTCAutomaticStackItem *pItem) CONST;
	BOOL CheckTelecommandReleaseTime(CONST CTimeTag &tTime, CONST CTCAutomaticStackItem *pItem) CONST;
	BOOL CheckTelecommandExecutionTime(CONST CTCAutomaticStackItem *pItem) CONST;
	BOOL CheckTelecommandExecutionTime(CONST CTimeTag &tTime, CONST CTCAutomaticStackItem *pItem) CONST;

	UINT CheckTelecommandReleaseInterlockState(CONST CTCAutomaticStackItem *pItem) CONST;

protected:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;
	COLORREF LookupStatusColor(UINT nResult, UINT nStatus) CONST;
	COLORREF LookupAlertColor(UINT nColumn, UINT nAlertType) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;
	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, INT nCount, INT nIndex) CONST;

	CString ConstructToolTipTitle(CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCAutomaticStackItem *pItem, CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;

	BOOL SetClipboardFormat(UINT nFormat);
	UINT GetClipboardFormat() CONST;
	BOOL CopyToClipboard(BOOL bCut = FALSE);
	BOOL PasteFromClipboard(INT nIndex = -1, BOOL bAfter = TRUE);

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackPageTextView)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
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
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackPageTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackPageView view

class CTCAutomaticStackPageView : public CView
{
	DECLARE_DYNCREATE(CTCAutomaticStackPageView)

	// Construction
public:
	CTCAutomaticStackPageView();
	~CTCAutomaticStackPageView();

	// Attributes
protected:
	CTCAutomaticStackPageTextView  *m_pwndList;
protected:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;
	BOOL SetAlertColors(CONST CUIntArray &nColors);
	BOOL GetAlertColors(CUIntArray &nColors) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = 0);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterTelecommandSubSystems(CONST CUIntArray &nSubSystems);
	BOOL GetFilterTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode = 0);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCAutomaticStackItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL SelectTelecommand(INT nIndex);
	BOOL DoSelectAllTelecommands();
	BOOL CanSelectAllTelecommands() CONST;
	BOOL DoUnselectAllTelecommands();
	INT EnumSelectedTelecommands(CTCAutomaticStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands(UINT nStatus = 0) CONST;

	UINT GetTelecommandCount() CONST;

	BOOL DoCutTelecommand();
	BOOL CanCutTelecommand() CONST;
	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoPasteTelecommand();
	BOOL CanPasteTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL DoAcknowledgeTelecommand();
	BOOL CanAcknowledgeTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL GetPrintProperties(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bFilter = FALSE, BOOL bRedraw = TRUE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCAutomaticStackWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackPageView)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
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
	//{{AFX_MSG(CTCAutomaticStackPageView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackNormalPageScheduledView view

class CTCAutomaticStackNormalPageScheduledView : public CTCAutomaticStackPageView
{
	DECLARE_DYNCREATE(CTCAutomaticStackNormalPageScheduledView)

	// Construction
public:
	CTCAutomaticStackNormalPageScheduledView();

	// Attributes
public:

	// Operations
public:
	class CTCAutomaticStackNormalPage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackNormalPageScheduledView)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackNormalPageScheduledView)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackNormalPageHistoricalView view

class CTCAutomaticStackNormalPageHistoricalView : public CTCAutomaticStackPageView
{
	DECLARE_DYNCREATE(CTCAutomaticStackNormalPageHistoricalView)

	// Construction
public:
	CTCAutomaticStackNormalPageHistoricalView();

	// Attributes
public:

	// Operations
public:
	class CTCAutomaticStackNormalPage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackNormalPageHistoricalView)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackNormalPageHistoricalView)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackNormalPage window

class CTCAutomaticStackNormalPage : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCAutomaticStackNormalPage)

	// Construction
public:
	CTCAutomaticStackNormalPage();

	// Attributes
private:
	CTCAutomaticStackNormalPageScheduledView  *m_pScheduledView;
	CTCAutomaticStackNormalPageHistoricalView  *m_pHistoricalView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST CUIntArray &nScheduledPaneColumns, CONST CUIntArray &nScheduledPaneColumnWidths, CONST SIZE &sizeScheduledPaneList, CONST CUIntArray &nHistoricalPaneColumns, CONST CUIntArray &nHistoricalPaneColumnWidths, CONST SIZE &sizeHistoricalPaneList, BOOL bVisible = TRUE);

	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeList);
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeList) CONST;

	BOOL SetListTitleFont(UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(UINT nPane, COLORREF nColor);
	BOOL GetGridBackgroundColor(UINT nPane, COLORREF &nColor) CONST;
	BOOL SetAlertColors(UINT nPane, CONST CUIntArray &nColors);
	BOOL GetAlertColors(UINT nPane, CUIntArray &nColors) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = 0);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterTelecommandSubSystems(CONST CUIntArray &nSubSystems);
	BOOL GetFilterTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode = 0);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCAutomaticStackItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(UINT nPane, INT nIndex);
	INT GetCurTelecommand(UINT nPane = 0) CONST;

	BOOL SelectTelecommand(UINT nPane, INT nIndex);
	BOOL DoSelectAllTelecommands(UINT nPane = 0);
	BOOL CanSelectAllTelecommands(UINT nPane = 0) CONST;
	BOOL DoUnselectAllTelecommands(UINT nPane = 0);
	INT EnumSelectedTelecommands(UINT nPane, CTCAutomaticStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands(UINT nPane = 0, UINT nStatus = 0) CONST;

	UINT GetTelecommandCount(UINT nPane = 0) CONST;

	BOOL DoCutTelecommand(UINT nPane = 0);
	BOOL CanCutTelecommand(UINT nPane = 0) CONST;
	BOOL DoCopyTelecommand(UINT nPane = 0);
	BOOL CanCopyTelecommand(UINT nPane = 0) CONST;
	BOOL DoPasteTelecommand(UINT nPane = 0);
	BOOL CanPasteTelecommand(UINT nPane = 0) CONST;
	BOOL DoDeleteTelecommand(UINT nPane = 0);
	BOOL CanDeleteTelecommand(UINT nPane = 0) CONST;

	BOOL DoAcknowledgeTelecommand(UINT nPane = 0);
	BOOL CanAcknowledgeTelecommand(UINT nPane = 0) CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL GetPrintProperties(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, CStringArray &szNormalStackScheduledColumns, CStringArray &szNormalStackScheduledContents, CTextViewAttributes &pNormalStackScheduledAttributes, LOGFONT *pNormalStackScheduledTitleFont, LOGFONT *pNormalStackScheduledItemsFont, CStringArray &szNormalStackHistoricalColumns, CStringArray &szNormalStackHistoricalContents, CTextViewAttributes &pNormalStackHistoricalAttributes, LOGFONT *pNormalStackHistoricalTitleFont, LOGFONT *pNormalStackHistoricalItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContents(BOOL bFilter = FALSE, BOOL bRedraw = TRUE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CTCAutomaticStackNormalPageScheduledView *GetScheduledView() CONST;
	CTCAutomaticStackNormalPageHistoricalView *GetHistoricalView() CONST;

	class CTCAutomaticStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackNormalPage)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pScheduledPaneHorzScrollInfo, CONST SCROLLINFO *pScheduledPaneVertScrollInfo, CONST SCROLLINFO *pHistoricalPaneHorzScrollInfo, CONST SCROLLINFO *pHistoricalPaneVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pScheduledPaneHorzScrollInfo, SCROLLINFO *pScheduledPaneVertScrollInfo, SCROLLINFO *pHistoricalPaneHorzScrollInfo, SCROLLINFO *pHistoricalPaneVertScrollInfo) CONST;
protected:
	virtual void StartTracking(int ht);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackNormalPage)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackTimeTaggedPageScheduledView view

class CTCAutomaticStackTimeTaggedPageScheduledView : public CTCAutomaticStackPageView
{
	DECLARE_DYNCREATE(CTCAutomaticStackTimeTaggedPageScheduledView)

	// Construction
public:
	CTCAutomaticStackTimeTaggedPageScheduledView();

	// Attributes
public:

	// Operations
public:
	class CTCAutomaticStackTimeTaggedPage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackTimeTaggedPageScheduledView)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackTimeTaggedPageScheduledView)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackTimeTaggedPageHistoricalView view

class CTCAutomaticStackTimeTaggedPageHistoricalView : public CTCAutomaticStackPageView
{
	DECLARE_DYNCREATE(CTCAutomaticStackTimeTaggedPageHistoricalView)

	// Construction
public:
	CTCAutomaticStackTimeTaggedPageHistoricalView();

	// Attributes
public:

	// Operations
public:
	class CTCAutomaticStackTimeTaggedPage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackTimeTaggedPageHistoricalView)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackTimeTaggedPageHistoricalView)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackTimeTaggedPage window

class CTCAutomaticStackTimeTaggedPage : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCAutomaticStackTimeTaggedPage)

	// Construction
public:
	CTCAutomaticStackTimeTaggedPage();

	// Attributes
private:
	CTCAutomaticStackTimeTaggedPageScheduledView  *m_pScheduledView;
	CTCAutomaticStackTimeTaggedPageHistoricalView  *m_pHistoricalView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST CUIntArray &nScheduledPaneColumns, CONST CUIntArray &nScheduledPaneColumnWidths, CONST SIZE &sizeScheduledPaneList, CONST CUIntArray &nHistoricalPaneColumns, CONST CUIntArray &nHistoricalPaneColumnWidths, CONST SIZE &sizeHistoricalPaneList, BOOL bVisible = TRUE);

	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeList);
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeList) CONST;

	BOOL SetListTitleFont(UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(UINT nPane, COLORREF nColor);
	BOOL GetGridBackgroundColor(UINT nPane, COLORREF &nColor) CONST;
	BOOL SetAlertColors(UINT nPane, CONST CUIntArray &nColors);
	BOOL GetAlertColors(UINT nPane, CUIntArray &nColors) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = 0);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterTelecommandSubSystems(CONST CUIntArray &nSubSystems);
	BOOL GetFilterTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode = 0);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCAutomaticStackItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(UINT nPane, INT nIndex);
	INT GetCurTelecommand(UINT nPane = 0) CONST;

	BOOL SelectTelecommand(UINT nPane, INT nIndex);
	BOOL DoSelectAllTelecommands(UINT nPane = 0);
	BOOL CanSelectAllTelecommands(UINT nPane = 0) CONST;
	BOOL DoUnselectAllTelecommands(UINT nPane = 0);
	INT EnumSelectedTelecommands(UINT nPane, CTCAutomaticStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands(UINT nPane = 0, UINT nStatus = 0) CONST;

	UINT GetTelecommandCount(UINT nPane = 0) CONST;

	BOOL DoCutTelecommand(UINT nPane = 0);
	BOOL CanCutTelecommand(UINT nPane = 0) CONST;
	BOOL DoCopyTelecommand(UINT nPane = 0);
	BOOL CanCopyTelecommand(UINT nPane = 0) CONST;
	BOOL DoPasteTelecommand(UINT nPane = 0);
	BOOL CanPasteTelecommand(UINT nPane = 0) CONST;
	BOOL DoDeleteTelecommand(UINT nPane = 0);
	BOOL CanDeleteTelecommand(UINT nPane = 0) CONST;

	BOOL DoAcknowledgeTelecommand(UINT nPane = 0);
	BOOL CanAcknowledgeTelecommand(UINT nPane = 0) CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL GetPrintProperties(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, CStringArray &szTimeTaggedStackScheduledColumns, CStringArray &szTimeTaggedStackScheduledContents, CTextViewAttributes &pTimeTaggedStackScheduledAttributes, LOGFONT *pTimeTaggedStackScheduledTitleFont, LOGFONT *pTimeTaggedStackScheduledItemsFont, CStringArray &szTimeTaggedStackHistoricalColumns, CStringArray &szTimeTaggedStackHistoricalContents, CTextViewAttributes &pTimeTaggedStackHistoricalAttributes, LOGFONT *pTimeTaggedStackHistoricalTitleFont, LOGFONT *pTimeTaggedStackHistoricalItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContents(BOOL bFilter = FALSE, BOOL bRedraw = TRUE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CTCAutomaticStackTimeTaggedPageScheduledView *GetScheduledView() CONST;
	CTCAutomaticStackTimeTaggedPageHistoricalView *GetHistoricalView() CONST;

	class CTCAutomaticStackView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackTimeTaggedPage)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pScheduledPaneHorzScrollInfo, CONST SCROLLINFO *pScheduledPaneVertScrollInfo, CONST SCROLLINFO *pHistoricalPaneHorzScrollInfo, CONST SCROLLINFO *pHistoricalPaneVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pScheduledPaneHorzScrollInfo, SCROLLINFO *pScheduledPaneVertScrollInfo, SCROLLINFO *pHistoricalPaneHorzScrollInfo, SCROLLINFO *pHistoricalPaneVertScrollInfo) CONST;
protected:
	virtual void StartTracking(int ht);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCAutomaticStackTimeTaggedPage)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackView window

class CTCAutomaticStackView : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCAutomaticStackView)

	// Construction
public:
	CTCAutomaticStackView();

	// Attributes
private:
	INT  m_nIndex;
	INT  m_nChecks;
	INT  m_nArguments;
	BOOL  m_bToolTips;
	BOOL  m_bProperties;
	BOOL  m_bAllArguments;
	BOOL  m_bFullViewMode;
	UINT  m_nFilterMode[2];
	UINT  m_nFilterLimitation;
	UINT  m_nMiscellaneousOptions;
	UINT  m_nTelecommandingMode;
	UINT  m_nTelecommandingState;
	UINT  m_nTelecommandingFlags;
	UINT  m_nTelecommandingUplinkState;
	BOOL  m_bTelecommandingInterlockMode;
	BOOL  m_bTelecommandingReleaseWaitMode;
	BOOL  m_bTelecommandingAutoRejectionMode;
	CString  m_szFilterTelecommand[2];
	CTimeSpan  m_tDefaultReleaseTimeWindow;
	CTimeSpan  m_tDispatchTimeWindow;
	CUIntArray  m_nFilterSubSystems;
private:
	CUIntArray  m_nColumns[2][2];
	CUIntArray  m_nColumnWidths[2][2];
	CUIntArray  m_nAlertColors[2][2];
	COLORREF  m_nBackgroundColor[2][2];
	LOGFONT  m_lfTitleFont[2][2];
	LOGFONT  m_lfItemsFont[2][2];
	CSize  m_sizeList[2][2];
	CSize  m_sizeTabMargins;
	CFont  m_cTabFont;
private:
	CTCAutomaticStackNormalPage  *m_pNormalPage;
	CTCAutomaticStackTimeTaggedPage  *m_pTimeTaggedPage;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeList);
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeList) CONST;

	BOOL SetListTitleFont(UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(UINT nPane, COLORREF nColor);
	BOOL GetGridBackgroundColor(UINT nPane, COLORREF &nColor) CONST;
	BOOL SetAlertColors(UINT nPane, CONST CUIntArray &nColors);
	BOOL GetAlertColors(UINT nPane, CUIntArray &nColors) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = 0);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterTelecommandSubSystems(CONST CUIntArray &nSubSystems);
	BOOL GetFilterTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode = 0);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCItems &pItems);
	BOOL LoadTelecommands(CONST CTCAutomaticStackItems &pItems);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);
	BOOL UpdateTelecommands(CView *pView);

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(UINT nPane, INT nIndex);
	INT GetCurTelecommand(UINT nPane = 0) CONST;

	BOOL SelectTelecommand(UINT nPane, INT nIndex);
	BOOL DoSelectAllTelecommands(UINT nPane = 0);
	BOOL CanSelectAllTelecommands(UINT nPane = 0) CONST;
	INT EnumSelectedTelecommands(UINT nPane, CTCAutomaticStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands(UINT nPane = 0, UINT nStatus = 0) CONST;

	UINT GetTelecommandCount(UINT nPane = 0) CONST;

	BOOL DoCutTelecommand(UINT nPane = 0);
	BOOL CanCutTelecommand(UINT nPane = 0) CONST;
	BOOL DoCopyTelecommand(UINT nPane = 0);
	BOOL CanCopyTelecommand(UINT nPane = 0) CONST;
	BOOL DoPasteTelecommand(UINT nPane = 0);
	BOOL CanPasteTelecommand(UINT nPane = 0) CONST;
	BOOL DoDeleteTelecommand(UINT nPane = 0);
	BOOL CanDeleteTelecommand(UINT nPane = 0) CONST;

	BOOL DoAcknowledgeTelecommand(UINT nPane = 0);
	BOOL CanAcknowledgeTelecommand(UINT nPane = 0) CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL GetPrintProperties(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, CStringArray &szNormalStackScheduledColumns, CStringArray &szNormalStackScheduledContents, CTextViewAttributes &pNormalStackScheduledAttributes, LOGFONT *pNormalStackScheduledTitleFont, LOGFONT *pNormalStackScheduledItemsFont, CStringArray &szNormalStackHistoricalColumns, CStringArray &szNormalStackHistoricalContents, CTextViewAttributes &pNormalStackHistoricalAttributes, LOGFONT *pNormalStackHistoricalTitleFont, LOGFONT *pNormalStackHistoricalItemsFont, CStringArray &szTimeTaggedStackScheduledColumns, CStringArray &szTimeTaggedStackScheduledContents, CTextViewAttributes &pTimeTaggedStackScheduledAttributes, LOGFONT *pTimeTaggedStackScheduledTitleFont, LOGFONT *pTimeTaggedStackScheduledItemsFont, CStringArray &szTimeTaggedStackHistoricalColumns, CStringArray &szTimeTaggedStackHistoricalContents, CTextViewAttributes &pTimeTaggedStackHistoricalAttributes, LOGFONT *pTimeTaggedStackHistoricalTitleFont, LOGFONT *pTimeTaggedStackHistoricalItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContents(BOOL bFilter = FALSE, BOOL bRedraw = TRUE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CSize GetMargins() CONST;

	CTCAutomaticStackNormalPage *GetNormalPage() CONST;
	CTCAutomaticStackTimeTaggedPage *GetTimeTaggedPage() CONST;

	class CTCAutomaticStackWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackView)
public:
	virtual BOOL SetLayoutInfo(INT nPage, CONST SCROLLINFO *pNormalScheduledPaneHorzScrollInfo, CONST SCROLLINFO *pNormalScheduledPaneVertScrollInfo, CONST SCROLLINFO *pNormalHistoricalPaneHorzScrollInfo, CONST SCROLLINFO *pNormalHistoricalPaneVertScrollInfo, CONST SCROLLINFO *pTimeTaggedScheduledPaneHorzScrollInfo, CONST SCROLLINFO *pTimeTaggedScheduledPaneVertScrollInfo, CONST SCROLLINFO *pTimeTaggedHistoricalPaneHorzScrollInfo, CONST SCROLLINFO *pTimeTaggedHistoricalPaneVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nPage, SCROLLINFO *pNormalScheduledPaneHorzScrollInfo, SCROLLINFO *pNormalScheduledPaneVertScrollInfo, SCROLLINFO *pNormalHistoricalPaneHorzScrollInfo, SCROLLINFO *pNormalHistoricalPaneVertScrollInfo, SCROLLINFO *pTimeTaggedScheduledPaneHorzScrollInfo, SCROLLINFO *pTimeTaggedScheduledPaneVertScrollInfo, SCROLLINFO *pTimeTaggedHistoricalPaneHorzScrollInfo, SCROLLINFO *pTimeTaggedHistoricalPaneVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSelchangePage(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCAutomaticStackWnd frame

// Specify the telecommand automatic stack page and panes
#define TCAUTOMATICSTACK_PAGE_NORMAL   (1<<0)
#define TCAUTOMATICSTACK_PAGE_TIMETAGGED   (1<<1)
#define TCAUTOMATICSTACK_PANE_SCHEDULED   (1<<2)
#define TCAUTOMATICSTACK_PANE_HISTORICAL   (1<<3)
#define TCAUTOMATICSTACK_PAGES   2
#define TCAUTOMATICSTACK_PANES   2
// Specify the telecommand automatic stack title items
#define TCAUTOMATICSTACK_TITLEITEM_NUMBER   (1<<0)
#define TCAUTOMATICSTACK_TITLEITEM_NAME   (1<<1)
#define TCAUTOMATICSTACK_TITLEITEM_DESCRIPTION   (1<<2)
#define TCAUTOMATICSTACK_TITLEITEM_CATEGORY   (1<<3)
#define TCAUTOMATICSTACK_TITLEITEM_SUBSYSTEM   (1<<4)
#define TCAUTOMATICSTACK_TITLEITEM_ARGUMENTS   (1<<5)
#define TCAUTOMATICSTACK_TITLEITEM_FLAGS   (1<<6)
#define TCAUTOMATICSTACK_TITLEITEM_TCPACKET   (1<<7)
#define TCAUTOMATICSTACK_TITLEITEM_DISPATCHTIME   (1<<8)
#define TCAUTOMATICSTACK_TITLEITEM_RELEASETIME   (1<<9)
#define TCAUTOMATICSTACK_TITLEITEM_RELEASETIMEOFFSET   (1<<10)
#define TCAUTOMATICSTACK_TITLEITEM_TRANSMISSIONTIME   (1<<11)
#define TCAUTOMATICSTACK_TITLEITEM_EXECUTIONTIME   (1<<12)
#define TCAUTOMATICSTACK_TITLEITEM_EXECUTIONTIMEOFFSET   (1<<13)
#define TCAUTOMATICSTACK_TITLEITEM_AUTHORIZATION   (1<<14)
#define TCAUTOMATICSTACK_TITLEITEM_PTVTIMEWINDOW   (1<<15)
#define TCAUTOMATICSTACK_TITLEITEM_PTVCHECKS   (1<<16)
#define TCAUTOMATICSTACK_TITLEITEM_PTVRESULT   (1<<17)
#define TCAUTOMATICSTACK_TITLEITEM_PEVCHECKS   (1<<18)
#define TCAUTOMATICSTACK_TITLEITEM_PEVRESULT   (1<<19)
#define TCAUTOMATICSTACK_TITLEITEM_CEVTIMEWINDOW   (1<<20)
#define TCAUTOMATICSTACK_TITLEITEM_CEVCHECKS   (1<<21)
#define TCAUTOMATICSTACK_TITLEITEM_CEVRESULT   (1<<22)
#define TCAUTOMATICSTACK_TITLEITEM_STATUS   (1<<23)
#ifndef RC_INVOKED
#define TCAUTOMATICSTACK_TITLEITEMS_DEFAULT   (TCAUTOMATICSTACK_TITLEITEM_NUMBER | TCAUTOMATICSTACK_TITLEITEM_NAME | TCAUTOMATICSTACK_TITLEITEM_DESCRIPTION | TCAUTOMATICSTACK_TITLEITEM_ARGUMENTS | TCAUTOMATICSTACK_TITLEITEM_FLAGS | TCAUTOMATICSTACK_TITLEITEM_RELEASETIME | TCAUTOMATICSTACK_TITLEITEM_RELEASETIMEOFFSET | TCAUTOMATICSTACK_TITLEITEM_CEVCHECKS | TCAUTOMATICSTACK_TITLEITEM_CEVRESULT | TCAUTOMATICSTACK_TITLEITEM_STATUS)
#define TCAUTOMATICSTACK_TITLEITEMS_ALL   (TCAUTOMATICSTACK_TITLEITEMS_DEFAULT | TCAUTOMATICSTACK_TITLEITEM_CATEGORY | TCAUTOMATICSTACK_TITLEITEM_SUBSYSTEM | TCAUTOMATICSTACK_TITLEITEM_TCPACKET | TCAUTOMATICSTACK_TITLEITEM_DISPATCHTIME | TCAUTOMATICSTACK_TITLEITEM_TRANSMISSIONTIME | TCAUTOMATICSTACK_TITLEITEM_EXECUTIONTIME | TCAUTOMATICSTACK_TITLEITEM_EXECUTIONTIMEOFFSET | TCAUTOMATICSTACK_TITLEITEM_PTVTIMEWINDOW | TCAUTOMATICSTACK_TITLEITEM_PTVCHECKS | TCAUTOMATICSTACK_TITLEITEM_PTVRESULT | TCAUTOMATICSTACK_TITLEITEM_PEVCHECKS | TCAUTOMATICSTACK_TITLEITEM_PEVRESULT | TCAUTOMATICSTACK_TITLEITEM_CEVTIMEWINDOW)
#endif
// Specify the telecommand automatic stack command source modes
#define TCAUTOMATICSTACK_MODE_DEFAULT   TCSERVICE_COMMANDSOURCEMODE_DEFAULT
#define TCAUTOMATICSTACK_MODE_MASTERMANUAL   TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL
// Specify the telecommand automatic stack command source checks
#define TCAUTOMATICSTACK_CHECKS_DEFAULT   TCSERVICE_COMMANDSOURCEFLAGS_DEFAULT
#define TCAUTOMATICSTACK_CHECKS_PTV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_PTV_OVERRIDE
#define TCAUTOMATICSTACK_CHECKS_PEV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE
#define TCAUTOMATICSTACK_CHECKS_CEV_OVERRIDE   TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE
#define TCAUTOMATICSTACK_CHECKS_PTV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_PTV_DISABLE
#define TCAUTOMATICSTACK_CHECKS_PEV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE
#define TCAUTOMATICSTACK_CHECKS_CEV_DISABLE   TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE
#define TCAUTOMATICSTACK_CHECKS_PREAUTHORIZE   TCSERVICE_COMMANDSOURCEFLAGS_PREAUTHORIZE
// Specify the telecommand automatic stack command source states
#define TCAUTOMATICSTACK_STATE_DEFAULT   TCSERVICE_COMMANDSOURCESTATE_DEFAULT
#define TCAUTOMATICSTACK_STATE_SUSPENDED   TCSERVICE_COMMANDSOURCESTATE_SUSPENDED
#define TCAUTOMATICSTACK_STATE_STOPPED   TCSERVICE_COMMANDSOURCESTATE_STOPPED
#define TCAUTOMATICSTACK_STATE_DISABLED   TCSERVICE_COMMANDSOURCESTATE_DISABLED
#define TCAUTOMATICSTACK_STATE_EMPTY   TCSERVICE_COMMANDSOURCESTATE_EMPTY
// Specify the telecommand automatic stack command options
#define TCAUTOMATICSTACK_OPTION_NONE   TCSERVICE_COMMANDSOURCEOPTION_NONE
#define TCAUTOMATICSTACK_OPTION_ALWAYSALLOWEXIT   TCSERVICE_COMMANDSOURCEOPTION_ALWAYSALLOWEXIT
#define TCAUTOMATICSTACK_OPTION_UNDISPATCHONEXIT   TCSERVICE_COMMANDSOURCEOPTION_UNDISPATCHONEXIT
// Specify the telecommand automatic stack default settings
#define TCAUTOMATICSTACK_RELEASETIMEWINDOW_DEFAULTINTERVAL   TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL
#define TCAUTOMATICSTACK_DISPATCHTIMEWINDOW_DEFAULTINTERVAL   TCSERVICE_COMMANDHANDLERTIMEWINDOW_DISPATCHINTERVAL
#define TCAUTOMATICSTACK_UPDATELISTCHECKS_DEFAULTCOUNT   20
// Specify the telecommand history display filter modes
#define TCAUTOMATICSTACK_FILTERMODE_NONE   0
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMAND   (1<<0)
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMANDITEM   (1<<1)
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMANDSEQUENCE   (1<<2)
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMANDTYPEIMMEDIATE   (1<<3)
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMANDTYPETIMETAGGED   (1<<4)
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMANDTYPE1STSTEP   (1<<5)
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMANDTYPE2NDSTEP   (1<<6)
#define TCAUTOMATICSTACK_FILTERMODE_BYTELECOMMANDSUBSYSTEMS   (1<<7)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONPASSED   (1<<8)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGETRANSMISSIONFAILED   (1<<9)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEPASSED   (1<<10)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEFAILED   (1<<11)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNKNOWN   (1<<12)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEACCEPTANCEUNVERIFIED   (1<<13)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGESTARTPASSED   (1<<14)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGESTARTFAILED   (1<<15)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGESTARTUNKNOWN   (1<<16)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGESTARTUNVERIFIED   (1<<17)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSPASSED   (1<<18)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSFAILED   (1<<19)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNKNOWN   (1<<20)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGEPROGRESSUNVERIFIED   (1<<21)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONPASSED   (1<<22)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONFAILED   (1<<23)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNKNOWN   (1<<24)
#define TCAUTOMATICSTACK_FILTERMODE_BYVERIFICATIONSTAGECOMPLETIONUNVERIFIED   (1<<25)
#define TCAUTOMATICSTACK_FILTERMODE_BYLIMITENTRIES  (1<<26)
// Specify the telecommand history display sort modes
#define TCAUTOMATICSTACK_SORTMODE_NONE   0
#define TCAUTOMATICSTACK_SORTMODE_BYRELEASETIME   (1<<0)
#define TCAUTOMATICSTACK_SORTMODE_BYEXECUTIONTIME   (1<<1)
#define TCAUTOMATICSTACK_SORTMODE_BYLATESTFIRST   (1<<2)
// Specify the telecommand automatic stack planning options
#define TCAUTOMATICSTACK_PLANNINGOPTION_MANUALIMPORT   (1<<0)
#define TCAUTOMATICSTACK_PLANNINGOPTION_AUTOMATICIMPORT   (1<<1)
#define TCAUTOMATICSTACK_PLANNINGOPTION_PERFORMAUTOMATICSYNCHRONIZATION   (1<<2)
#define TCAUTOMATICSTACK_PLANNINGOPTION_ALLOWMANUALSYNCHRONIZATION   (1<<3)
#define TCAUTOMATICSTACK_PLANNINGOPTION_REPORTNOTHING   (1<<4)
#define TCAUTOMATICSTACK_PLANNINGOPTION_REPORTEVERYTHING   (1<<5)
#define TCAUTOMATICSTACK_PLANNINGOPTION_REPORTFAILURES   (1<<6)
// Specify the telecommand automatic stack alert types
#define TCAUTOMATICSTACK_ALERTTYPE_TELECOMMANDRELEASEFAILURE   0
#define TCAUTOMATICSTACK_ALERTTYPE_INTERLOCKFAILURE   1
// Specify the telecommand automatic stack user permissions
#define TCAUTOMATICSTACK_USERPERMISSION_CHANGECHECKS   (1<<0)
#define TCAUTOMATICSTACK_USERPERMISSION_CHANGEFLAGS   (1<<1)
#define TCAUTOMATICSTACK_USERPERMISSION_CHANGERELEASETIME   (1<<2)
#define TCAUTOMATICSTACK_USERPERMISSION_CHANGEINTERLOCKS   (1<<3)
#define TCAUTOMATICSTACK_USERPERMISSION_CHANGEEXECUTIONTIME   (1<<4)
#define TCAUTOMATICSTACK_USERPERMISSION_CHANGEPARAMETERVALUES   (1<<5)
#define TCAUTOMATICSTACK_USERPERMISSION_USETEMPLATES   (1<<6)
// Specify the telecommand automatic stack print modes
#define TCAUTOMATICSTACK_PRINT_NORMALSTACK   (1<<0)
#define TCAUTOMATICSTACK_PRINT_TIMETAGGEDSTACK   (1<<1)
#define TCAUTOMATICSTACK_PRINT_ONSTACKITEMS   (1<<2)
#define TCAUTOMATICSTACK_PRINT_DISPATCHEDITEMS   (1<<3)
#define TCAUTOMATICSTACK_PRINT_RELEASEDITEMS   (1<<4)
#define TCAUTOMATICSTACK_PRINT_NOTRELEASEDITEMS   (1<<5)
#define TCAUTOMATICSTACK_PRINT_FAILEDRELEASEITEMS   (1<<6)
#define TCAUTOMATICSTACK_PRINT_ITEMRANGE   (1<<7)
#define TCAUTOMATICSTACK_PRINT_TIMERANGE   (1<<8)
#define TCAUTOMATICSTACK_PRINT_CLEARCOMMENTS   (1<<9)
// Specify the telecommand automatic stack print fonts
#define TCAUTOMATICSTACK_PRINTFONT_TITLE   0
#define TCAUTOMATICSTACK_PRINTFONT_DETAILS   1
#define TCAUTOMATICSTACK_PRINTFONT_COMMENTS   2
#define TCAUTOMATICSTACK_PRINTFONT_LISTITEMSTITLE   3
#define TCAUTOMATICSTACK_PRINTFONT_LISTITEMS   4
#define TCAUTOMATICSTACK_PRINTFONT_FOOTER   5
#define TCAUTOMATICSTACK_PRINTFONT_NOTICE   6
#define TCAUTOMATICSTACK_PRINTFONT_LOGO   7
#define TCAUTOMATICSTACK_PRINTFONTS   8
// Specify the telecommand automatic stack toolbar related identifiers
#define ID_TCAUTOMATICSTACK_TOOLBAR_PROPERTIES   AFX_IDW_TOOLBAR
#define ID_TCAUTOMATICSTACK_TOOLBAR_OPERATIONS   (AFX_IDW_TOOLBAR+1)
// Specify the telecommand automatic stack statusbar pane identifiers
#define ID_TCAUTOMATICSTACK_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TCAUTOMATICSTACK_STATUSBAR_UPLINKPANE   ID_STATUSBAR_PANE1
#define ID_TCAUTOMATICSTACK_STATUSBAR_PTVPANE   ID_STATUSBAR_PANE2
#define ID_TCAUTOMATICSTACK_STATUSBAR_PEVPANE   ID_STATUSBAR_PANE3
#define ID_TCAUTOMATICSTACK_STATUSBAR_CEVPANE   ID_STATUSBAR_PANE4
#define ID_TCAUTOMATICSTACK_STATUSBAR_STATEPANE   ID_STATUSBAR_PANE5
#define ID_TCAUTOMATICSTACK_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE6

class CTCAutomaticStackWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTCAutomaticStackWnd)

	// Construction
public:
	CTCAutomaticStackWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nPage;
		INT  cbColumns[2][2][2];
		RECT  rToolBar[2];
		SIZE  sizePanes[2][2];
		LOGFONT  sFont[2][2][2];
		SCROLLINFO  sScrollInfo[2][2][2];
	} DATA, *PDATA, *LPDATA;
private:
	CTCAutomaticStackToolBar  m_wndToolBar[2];
	CTCAutomaticStackStatusBar  m_wndStatusBar;
	CTCAutomaticStackView  m_wndView;
private:
	CTCAutomaticStackSettingsDialog  m_dlgSettings;
	CTCAutomaticStackInterlocksDialog  m_dlgInterlocks;
	CTCAutomaticStackSubSystemsDialog  m_dlgSubSystems;
	CTCAutomaticStackSaveContentsDialog  m_dlgSaveStacks;
	CTCAutomaticStackLoadContentsDialog  m_dlgLoadStacks;
private:
	CTCAutomaticStackItemTemplates  m_pItemTemplates;
	CTCAutomaticStackComposedItemTemplates  m_pComposedItemTemplates;
	CTCAutomaticStackSearchFilters  m_pSearchFilters[TCAUTOMATICSTACKSEARCHFILTER_TYPES];
private:
	CTCAutomaticStackPrintJobs  m_pPrintJobs;
private:
	CTCSavedStack  m_cSavedStack;
private:
	UINT  m_nPlanningOptions[2];
	CString  m_szPlanningComputer[2][2];
	CString  m_szPlanningAudition;
	CString  m_szPlanningNotification;
	CTimeSpan  m_tPlanningPeriod;
private:
	UINT  m_nLoggingPolicy;
	UINT  m_nLoggingReloadCount;
	CString  m_szLoggingFileName[2];
	CTimeSpan  m_tLoggingRetention;
	DWORDLONG  m_dwLoggingRetention;
	BOOL  m_bLoggingAsEvent;
private:
	CUIntArray  m_nAlertTypes;
	CStringArray  m_szAlertAuditions;
	CStringArray  m_szAlertNotifications;
	CDWordArray  m_nAlertAcknowledgeColors;
	CByteArray  m_bAlertAcknowledgments;
private:
	CUIntArray  m_nSubSystemIDs;
	CUIntArray  m_nSubSystemStatus;
	CStringArray  m_szSubSystemEvents[2];
private:
	UINT  m_nUserPermissions;

	// Operations
public:
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeList);
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeList) CONST;

	BOOL SetListTitleFont(UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(UINT nPane, COLORREF nColor);
	BOOL GetGridBackgroundColor(UINT nPane, COLORREF &nColor) CONST;
	BOOL SetAlertColors(UINT nPane, CONST CUIntArray &nColors);
	BOOL GetAlertColors(UINT nPane, CUIntArray &nColors) CONST;

	BOOL SetSearchFilters(UINT nType, CONST CTCAutomaticStackSearchFilters &pFilters);
	BOOL GetSearchFilters(UINT nType, CTCAutomaticStackSearchFilters &pFilters) CONST;
	BOOL SetItemTemplates(CONST CTCAutomaticStackItemTemplates &pTemplates);
	BOOL SetItemTemplates(CONST CTCAutomaticStackComposedItemTemplates &pTemplates);
	BOOL GetItemTemplates(CTCAutomaticStackItemTemplates &pTemplates) CONST;
	BOOL GetItemTemplates(CTCAutomaticStackComposedItemTemplates &pTemplates) CONST;

	BOOL SetListOptions(INT nArguments = -1, BOOL bAll = FALSE);
	BOOL GetListOptions(INT &nArguments, BOOL &bAll) CONST;
	BOOL SetListUpdateChecks(INT nCount = 0);
	BOOL GetListUpdateChecks(INT &nCount) CONST;
	BOOL SetMiscellaneousOptions(UINT nOptions = 0);
	BOOL GetMiscellaneousOptions(UINT &nOptions) CONST;
	BOOL SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL SetDefaultReleaseTimeWindow(LPCTSTR pszOriginator, CONST CTimeSpan &tTimeWindow);
	BOOL GetDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL SetDispatchTimeWindow(LPCTSTR pszOriginator, CONST CTimeSpan &tTimeWindow);
	BOOL GetDispatchTimeWindow(CTimeSpan &tTimeWindow) CONST;
	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = 0);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterTelecommandName(LPCTSTR pszName);
	BOOL GetFilterTelecommandName(CString &szName) CONST;
	BOOL SetFilterTelecommandSequence(LPCTSTR pszSequence);
	BOOL GetFilterTelecommandSequence(CString &szSequence) CONST;
	BOOL SetFilterTelecommandSubSystems(CONST CUIntArray &nSubSystems);
	BOOL GetFilterTelecommandSubSystems(CUIntArray &nSubSystems) CONST;
	BOOL SetFilterLimitation(UINT nCount);
	BOOL GetFilterLimitation(UINT &nCount) CONST;
	BOOL SetFilterSortMode(UINT nMode = 0);
	BOOL GetFilterSortMode(UINT &nMode) CONST;

	BOOL StartTelecommanding(CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment);
	BOOL UpdateTelecommanding(LPCTSTR pszOriginator, CONST CTCProcessCommandSourceInfo *pCommandSourceInfo);
	BOOL UpdateTelecommanding(LPCTSTR pszEvent);
	BOOL StopTelecommanding();

	BOOL SetTelecommandingMode(UINT nMode, BOOL bUser = TRUE);
	BOOL SetTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser = TRUE);
	UINT GetTelecommandingMode() CONST;
	BOOL SetTelecommandingChecks(UINT nFlags, BOOL bUser = TRUE);
	BOOL SetTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser = TRUE);
	UINT GetTelecommandingChecks() CONST;
	BOOL SetTelecommandingState(UINT nState, BOOL bUser = TRUE);
	BOOL SetTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser = TRUE);
	UINT GetTelecommandingState() CONST;
	BOOL SetTelecommandingUplinkState(UINT nState);
	UINT GetTelecommandingUplinkState() CONST;
	BOOL EnableTelecommandingInterlockMode(BOOL bEnable, BOOL bUser = TRUE);
	BOOL EnableTelecommandingInterlockMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser = TRUE);
	BOOL IsTelecommandingInterlockModeEnabled() CONST;
	BOOL EnableTelecommandingReleaseWaitMode(BOOL bEnable, BOOL bUser = TRUE);
	BOOL EnableTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser = TRUE);
	BOOL IsTelecommandingReleaseWaitModeEnabled() CONST;
	BOOL EnableTelecommandingAutoRejectionMode(BOOL bEnable, BOOL bUser = TRUE);
	BOOL EnableTelecommandingAutoRejectionMode(LPCTSTR pszOriginator, BOOL bEnable, BOOL bUser = TRUE);
	BOOL IsTelecommandingAutoRejectionModeEnabled() CONST;

	BOOL SetTelecommands(CONST CTCSavedStack &pStack);
	BOOL GetTelecommands(CTCSavedStack &pStack, BOOL bAll = FALSE) CONST;
	BOOL LoadTelecommands(CONST CTCItems &pItems);
	BOOL LoadTelecommands(CONST CTCAutomaticStackItems &pItems);
	BOOL DispatchTelecommands(CTCAutomaticStackItems &pItems, BOOL bUndo = FALSE);
	BOOL UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateTelecommands(CONST CTMEnvironment *pTMEnvironment);
	BOOL UpdateTelecommands(CView *pView);

	BOOL UpdateTelecommandInterlocks(CONST CTCInterlocks &pInterlocks);

	BOOL SetCurTelecommand(UINT nPane, INT nIndex);
	INT GetCurTelecommand(UINT nPane = 0) CONST;

	BOOL SelectTelecommand(UINT nPane, INT nIndex);
	BOOL DoSelectAllTelecommands(UINT nPane = 0);
	BOOL CanSelectAllTelecommands(UINT nPane = 0) CONST;
	INT EnumSelectedTelecommands(UINT nPane, CTCAutomaticStackItems &pItems) CONST;
	BOOL HasSelectedTelecommands(UINT nPane = 0, UINT nStatus = 0) CONST;

	UINT GetTelecommandCount(UINT nPane = 0) CONST;

	BOOL DoCutTelecommand(UINT nPane = 0);
	BOOL CanCutTelecommand(UINT nPane = 0) CONST;
	BOOL DoCopyTelecommand(UINT nPane = 0);
	BOOL CanCopyTelecommand(UINT nPane = 0) CONST;
	BOOL DoPasteTelecommand(UINT nPane = 0);
	BOOL CanPasteTelecommand(UINT nPane = 0) CONST;
	BOOL DoDeleteTelecommand(UINT nPane = 0);
	BOOL CanDeleteTelecommand(UINT nPane = 0) CONST;

	BOOL DoAcknowledgeTelecommand(UINT nPane = 0);
	BOOL CanAcknowledgeTelecommand(UINT nPane = 0) CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL DoResetInterlocks();
	BOOL CanResetInterlocks() CONST;
	BOOL DoCheckSubSystems();
	BOOL CanCheckSubSystems() CONST;

	BOOL DoCommandingState();
	BOOL CanCommandingState() CONST;
	BOOL DoSuspendedState();
	BOOL CanSuspendedState() CONST;
	BOOL DoStoppedState();
	BOOL CanStoppedState() CONST;

	BOOL SetSubSystemChecks();
	BOOL SetSubSystemChecks(CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus);
	BOOL GetSubSystemChecks(CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST;

	BOOL SetPlanningOptions();
	BOOL SetPlanningOptions(LPCTSTR pszMissionPlanningComputer, LPCTSTR pszMissionPlanningBackupComputer, UINT nMissionPlanningOptions, CONST CTimeSpan &tMissionPlanningPeriod, LPCTSTR pszMissionPlanningAudition, LPCTSTR pszMissionPlanningNotification, LPCTSTR pszFlightDynamicsComputer, LPCTSTR pszFlightDynamicsBackupComputer, UINT nFlightDynamicsOptions);
	BOOL GetPlanningOptions(CString &szMissionPlanningComputer, CString &szMissionPlanningBackupComputer, UINT &nMissionPlanningOptions, CTimeSpan &tMissionPlanningPeriod, CString &szMissionPlanningAudition, CString &szMissionPlanningNotification, CString &szFlightDynamicsComputer, CString &szFlightDynamicsBackupComputer, UINT &nFlightDynamicsOptions) CONST;

	BOOL SetLoggingOptions();
	BOOL SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent);
	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	BOOL SetAlertOptions(CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments);
	BOOL GetAlertOptions(CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST;

	BOOL Alert(CONST CTCAutomaticStackItem *pItem);
	BOOL Alert(CONST CTCInterlock *pInterlock);

	BOOL SetPrintJobs(CONST CTCAutomaticStackPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTCAutomaticStackPrintJobs &pPrintJobs) CONST;

	BOOL SetUserPermissions(UINT nPermissions = 0);
	BOOL GetUserPermissions(UINT &nPermissions) CONST;

	BOOL Print(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	BOOL LogActivity(CONST CTCLogEntry *pEntry);

private:
	BOOL CreateBars();
	BOOL CreateToolBars();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateUplinkPane();
	VOID UpdatePretransmissionVerificationPane();
	VOID UpdatePreexecutionVerificationPane();
	VOID UpdateExecutionVerificationPane();
	VOID UpdateStatePane();
	VOID UpdateModePane();

	VOID UpdateContents(BOOL bFilter = FALSE);

	BOOL SetSearchFilters(CONST CByteArray &nSearchFilters);
	BOOL GetSearchFilters(CByteArray &nSearchFilters) CONST;
	BOOL SetItemTemplates(CONST CByteArray &nItemTemplates, CONST CByteArray &nComposedItemTemplates);
	BOOL GetItemTemplates(CByteArray &nItemTemplates, CByteArray &nComposedItemTemplates) CONST;

	BOOL LogTelecommandingMode(LPCTSTR pszOriginator, UINT nMode, BOOL bUser);
	BOOL LogTelecommandingState(LPCTSTR pszOriginator, UINT nState, BOOL bUser);
	BOOL LogTelecommandingChecks(LPCTSTR pszOriginator, UINT nFlags, BOOL bUser);
	BOOL LogTelecommandingInterlockMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser);
	BOOL LogTelecommandingReleaseWaitMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser);
	BOOL LogTelecommandingAutoRejectionMode(LPCTSTR pszOriginator, BOOL bEnabled, BOOL bUser);
	BOOL LogResetInterlocks(CONST CTCInterlocks &pInterlocks);
	BOOL LogCheckSubSystems(CONST CUIntArray &nSubSystemsID, CONST CByteArray &bSubSystemsStatus);
	BOOL LogListOptions(INT nArguments, BOOL bAll);
	BOOL LogListUpdateChecks(INT nCount);
	BOOL LogMiscellaneousOptions(UINT nOptions);
	BOOL LogDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL LogDispatchTimeWindow(CONST CTimeSpan &tTimeWindow);
	BOOL LogUserPermissions(UINT nPermissions, UINT nChangedPermissions);
	BOOL LogAlerts(CONST CUIntArray &nTypes, CONST CUIntArray &nActions);

	BOOL SetContents(CONST CByteArray &nContentsInfo);
	BOOL GetContents(CByteArray &nContentsInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, CStringArray &szNormalStackScheduledColumns, CStringArray &szNormalStackScheduledContents, CTextViewAttributes &pNormalStackScheduledAttributes, LOGFONT *pNormalStackScheduledTitleFont, LOGFONT *pNormalStackScheduledItemsFont, CStringArray &szNormalStackHistoricalColumns, CStringArray &szNormalStackHistoricalContents, CTextViewAttributes &pNormalStackHistoricalAttributes, LOGFONT *pNormalStackHistoricalTitleFont, LOGFONT *pNormalStackHistoricalItemsFont, CStringArray &szTimeTaggedStackScheduledColumns, CStringArray &szTimeTaggedStackScheduledContents, CTextViewAttributes &pTimeTaggedStackScheduledAttributes, LOGFONT *pTimeTaggedStackScheduledTitleFont, LOGFONT *pTimeTaggedStackScheduledItemsFont, CStringArray &szTimeTaggedStackHistoricalColumns, CStringArray &szTimeTaggedStackHistoricalContents, CTextViewAttributes &pTimeTaggedStackHistoricalAttributes, LOGFONT *pTimeTaggedStackHistoricalTitleFont, LOGFONT *pTimeTaggedStackHistoricalItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTCAutomaticStackPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CStringArray &szNormalStackScheduledColumns, CONST CStringArray &szNormalStackScheduledContents, CONST CTextViewAttributes &pNormalStackScheduledAttributes, CONST LOGFONT *pNormalStackScheduledTitleFont, CONST LOGFONT *pNormalStackScheduledItemsFont, CONST CStringArray &szNormalStackHistoricalColumns, CONST CStringArray &szNormalStackHistoricalContents, CONST CTextViewAttributes &pNormalStackHistoricalAttributes, CONST LOGFONT *pNormalStackHistoricalTitleFont, CONST LOGFONT *pNormalStackHistoricalItemsFont, CONST CStringArray &szTimeTaggedStackScheduledColumns, CONST CStringArray &szTimeTaggedStackScheduledContents, CONST CTextViewAttributes &pTimeTaggedStackScheduledAttributes, CONST LOGFONT *pTimeTaggedStackScheduledTitleFont, CONST LOGFONT *pTimeTaggedStackScheduledItemsFont, CONST CStringArray &szTimeTaggedStackHistoricalColumns, CONST CStringArray &szTimeTaggedStackHistoricalContents, CONST CTextViewAttributes &pTimeTaggedStackHistoricalAttributes, CONST LOGFONT *pTimeTaggedStackHistoricalTitleFont, CONST LOGFONT *pTimeTaggedStackHistoricalItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCAutomaticStackPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszPage, LPCTSTR pszPane, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocDetails(CONST CTCAutomaticStackPrintJobInfo *pJobInfo, LPCTSTR pszPage, LPCTSTR pszPane) CONST;
	CString GetPrintDocComments(CONST CTCAutomaticStackPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(CONST RECT &rPropertiesToolBar, CONST RECT &rOperationsToolBar, CONST CUIntArray &nNormalScheduledPaneColumns, CONST CUIntArray &nNormalScheduledPaneWidths, CONST SIZE &sizeNormalScheduledPane, CONST CUIntArray &nNormalHistoricalPaneColumns, CONST CUIntArray &nNormalHistoricalPaneWidths, CONST SIZE &sizeNormalHistoricalPane, CONST CUIntArray &nTimeTaggedScheduledPaneColumns, CONST CUIntArray &nTimeTaggedScheduledPaneWidths, CONST SIZE &sizeTimeTaggedScheduledPane, CONST CUIntArray &nTimeTaggedHistoricalPaneColumns, CONST CUIntArray &nTimeTaggedHistoricalPaneWidths, CONST SIZE &sizeTimeTaggedHistoricalPane, CONST LOGFONT *pNormalScheduledPaneTitleFont, CONST LOGFONT *pNormalScheduledPaneItemsFont, CONST LOGFONT *pNormalHistoricalPaneTitleFont, CONST LOGFONT *pNormalHistoricalPaneItemsFont, CONST LOGFONT *pTimeTaggedScheduledPaneTitleFont, CONST LOGFONT *pTimeTaggedScheduledPaneItemsFont, CONST LOGFONT *pTimeTaggedHistoricalPaneTitleFont, CONST LOGFONT *pTimeTaggedHistoricalPaneItemsFont, INT nPage, CONST SCROLLINFO *pNormalScheduledPaneHorzScrollInfo, CONST SCROLLINFO *pNormalScheduledPaneVertScrollInfo, CONST SCROLLINFO *pNormalHistoricalPaneHorzScrollInfo, CONST SCROLLINFO *pNormalHistoricalPaneVertScrollInfo, CONST SCROLLINFO *pTimeTaggedScheduledPaneHorzScrollInfo, CONST SCROLLINFO *pTimeTaggedScheduledPaneVertScrollInfo, CONST SCROLLINFO *pTimeTaggedHistoricalPaneHorzScrollInfo, CONST SCROLLINFO *pTimeTaggedHistoricalPaneVertScrollInfo);
	BOOL GetLayoutInfo(RECT &rPropertiesToolBar, RECT &rOperationsToolBar, CUIntArray &nNormalScheduledPaneColumns, CUIntArray &nNormalScheduledPaneWidths, CSize &sizeNormalScheduledPane, CUIntArray &nNormalHistoricalPaneColumns, CUIntArray &nNormalHistoricalPaneWidths, CSize &sizeNormalHistoricalPane, CUIntArray &nTimeTaggedScheduledPaneColumns, CUIntArray &nTimeTaggedScheduledPaneWidths, CSize &sizeTimeTaggedScheduledPane, CUIntArray &nTimeTaggedHistoricalPaneColumns, CUIntArray &nTimeTaggedHistoricalPaneWidths, CSize &sizeTimeTaggedHistoricalPane, LOGFONT *pNormalScheduledPaneTitleFont, LOGFONT *pNormalScheduledPaneItemsFont, LOGFONT *pNormalHistoricalPaneTitleFont, LOGFONT *pNormalHistoricalPaneItemsFont, LOGFONT *pTimeTaggedScheduledPaneTitleFont, LOGFONT *pTimeTaggedScheduledPaneItemsFont, LOGFONT *pTimeTaggedHistoricalPaneTitleFont, LOGFONT *pTimeTaggedHistoricalPaneItemsFont, INT &nPage, SCROLLINFO *pNormalScheduledPaneHorzScrollInfo, SCROLLINFO *pNormalScheduledPaneVertScrollInfo, SCROLLINFO *pNormalHistoricalPaneHorzScrollInfo, SCROLLINFO *pNormalHistoricalPaneVertScrollInfo, SCROLLINFO *pTimeTaggedScheduledPaneHorzScrollInfo, SCROLLINFO *pTimeTaggedScheduledPaneVertScrollInfo, SCROLLINFO *pTimeTaggedHistoricalPaneHorzScrollInfo, SCROLLINFO *pTimeTaggedHistoricalPaneVertScrollInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCAutomaticStackWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
	virtual void RecalcLayout(CDisplayToolBar *pToolBar);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual VOID Update();
	virtual BOOL Check() CONST;
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
	BOOL OnCloseSettingsDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCAutomaticStackWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnSave();
	afx_msg void OnOpen();
	afx_msg void OnProperties();
	afx_msg void OnSelectAll();
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnPaste();
	afx_msg void OnDelete();
	afx_msg void OnFullViewMode();
	afx_msg void OnStart();
	afx_msg void OnSuspend();
	afx_msg void OnStop();
	afx_msg void OnAcknowledge();
	afx_msg void OnResetInterlocks();
	afx_msg void OnInterlockChecks();
	afx_msg void OnSubSystemChecks();
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnAutoRejectionMode();
	afx_msg void OnPrint();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProperties(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFullViewMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSuspend(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAcknowledge(CCmdUI *pCmdUI);
	afx_msg void OnUpdateResetInterlocks(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInterlockChecks(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSubSystemChecks(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReleaseWaitMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAutoRejectionMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarUplinkPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarPEVPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarCEVPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarStatePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TCSTACKS_H__
