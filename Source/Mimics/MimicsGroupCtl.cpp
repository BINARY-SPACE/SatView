// MIMICSGROUPCTL.CPP : Mimics Group Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics group
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/05/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CMimicsGroupCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsGroupCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsGroupCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsGroupCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsGroupCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsGroupCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsGroupCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsGroupCtrl, 1)
	PROPPAGEID(CMimicsGroupGeneralPage::guid)
END_PROPPAGEIDS(CMimicsGroupCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsGroupCtrl, "MIMICS.MimicsGroupCtrl.1", 0xd9b0da14, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsGroupCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsGroup = { 0xd9b0da12,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsGroupEvents = { 0xd9b0da13,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsGroupOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsGroupCtrl, IDS_MIMICSGROUPCTRL_DESCRIPTIVENAME, dwMimicsGroupOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupCtrl::CMimicsGroupCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsGroupCtrl

BOOL CMimicsGroupCtrl::CMimicsGroupCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSGROUPCTRL_DESCRIPTIVENAME, IDB_MIMICSGROUPCTRL, afxRegApartmentThreading, dwMimicsGroupOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupCtrl

CMimicsGroupCtrl::CMimicsGroupCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSGROUPCTRL_TYPE);
	InitializeIIDs(&IID_DMimicsGroup, &IID_DMimicsGroupEvents);
	SetInitialSize((m_sizeCtrl.cx = 0), (m_sizeCtrl.cy = 0));
}

void CMimicsGroupCtrl::InitializeProps()
{
	return;
}

void CMimicsGroupCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupCtrl message handlers
