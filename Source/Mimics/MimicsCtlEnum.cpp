// MIMICSCTLENUM.CPP : Mimics Control Enumeration Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics control
// enumeration related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CEnumMimicsCtrls

IMPLEMENT_DYNCREATE(CEnumMimicsCtrls, CCmdTarget)

IMPLEMENT_OLECREATE_EX(CEnumMimicsCtrls, "MIMICS.EnumMimicsCtrls.1", 0xd9b0d9ed, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

STDMETHODIMP CEnumMimicsCtrls::XEnumMimicsCtrls::QueryInterface(REFIID riid, LPVOID *ppvObj)
{
	METHOD_PROLOGUE(CEnumMimicsCtrls, EnumMimicsCtrls)

		return pThis->ExternalQueryInterface(&riid, ppvObj);
}

STDMETHODIMP_(ULONG) CEnumMimicsCtrls::XEnumMimicsCtrls::AddRef(void)
{
	METHOD_PROLOGUE(CEnumMimicsCtrls, EnumMimicsCtrls)

		return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CEnumMimicsCtrls::XEnumMimicsCtrls::Release(void)
{
	METHOD_PROLOGUE(CEnumMimicsCtrls, EnumMimicsCtrls)

		return pThis->ExternalRelease();
}

STDMETHODIMP_(BOOL) CEnumMimicsCtrls::XEnumMimicsCtrls::GetMimicsCtrlProperties(ULONG nID, BSTR *pszType, IID *pIID)
{
	HRSRC  hIID;
	LPVOID  pResIID;
	HGLOBAL  hResIID;
	METHOD_PROLOGUE(CEnumMimicsCtrls, EnumMimicsCtrls)

		if (nID < GetMimicsCtrlsCount())
		{
			if ((*pszType = SysAllocString(_bstr_t(STRING(MINMIMICSOBJECTCTRLTYPE + nID)))))
			{
				if ((hIID = FindResource(GetModuleInstance(), MAKEINTRESOURCE(MINMIMICSOBJECTCTRLIID + nID), RT_RCDATA)))
				{
					if ((hResIID = LoadResource(GetModuleInstance(), hIID)))
					{
						if ((pResIID = LockResource(hResIID)))
						{
							CopyMemory(pIID, pResIID, sizeof(IID));
							return TRUE;
						}
					}
				}
				SysFreeString(*pszType);
			}
			*pszType = (BSTR)NULL;
		}
	return FALSE;
}

STDMETHODIMP_(BOOL) CEnumMimicsCtrls::XEnumMimicsCtrls::TranslateMimicsCtrlTypeToCLSID(CONST BSTR pszType, IID *pIID)
{
	INT  nCtrl;
	INT  nCtrls;
	BSTR  pszCtrlType;
	CLSID  clsidCtrl;

	for (nCtrl = 0, nCtrls = GetMimicsCtrlsCount(); nCtrl < nCtrls; nCtrl++)
	{
		if (GetMimicsCtrlProperties(nCtrl, &pszCtrlType, &clsidCtrl))
		{
			if (!wcscmp(pszType, pszCtrlType))
			{
				CopyMemory(pIID, &clsidCtrl, sizeof(IID));
				SysFreeString(pszCtrlType);
				break;
			}
			SysFreeString(pszCtrlType);
		}
	}
	return((nCtrl < nCtrls) ? TRUE : FALSE);
}

STDMETHODIMP_(BOOL) CEnumMimicsCtrls::XEnumMimicsCtrls::TranslateMimicsCtrlIDToCLSID(ULONG nID, IID *pIID)
{
	BSTR  pszCtrlType;

	if (GetMimicsCtrlProperties(nID, &pszCtrlType, pIID))
	{
		SysFreeString(pszCtrlType);
		return TRUE;
	}
	return FALSE;
}

STDMETHODIMP_(ULONG) CEnumMimicsCtrls::XEnumMimicsCtrls::GetMimicsCtrlsCount(void)
{
	METHOD_PROLOGUE(CEnumMimicsCtrls, EnumMimicsCtrls)

		return MAXMIMICSOBJECTCTRLIID - MINMIMICSOBJECTCTRLIID + 1;
}

STDMETHODIMP_(BSTR) CEnumMimicsCtrls::XEnumMimicsCtrls::GetMimicsClipboardFormat()
{
	METHOD_PROLOGUE(CEnumMimicsCtrls, EnumMimicsCtrls)

		return SysAllocString(_bstr_t(STRING(IDS_MIMICSCLIPBOARD_FORMAT)));
}


/////////////////////////////////////////////////////////////////////////////
// CEnumMimicsCtrls::CEnumMimicsCtrlsFactory::UpdateRegistry -
// Adds or removes system registry entries for CEnumMimicsCtrls

BOOL CEnumMimicsCtrls::CEnumMimicsCtrlsFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterServerClass(m_clsid, m_lpszProgID, m_lpszProgID, m_lpszProgID, OAT_DISPATCH_OBJECT) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// Interface ID

const IID BASED_CODE  IID_IEnumMimicsCtrls = { 0xd9b0d9ec,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };


BEGIN_INTERFACE_MAP(CEnumMimicsCtrls, CCmdTarget)
	INTERFACE_PART(CEnumMimicsCtrls, IID_IEnumMimicsCtrls, EnumMimicsCtrls)
END_INTERFACE_MAP()
