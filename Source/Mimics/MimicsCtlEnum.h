// MIMICSCTLENUM.H : Mimics Control Enumeration Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics control enumeration related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSCTLENUM_H__
#define __MIMICSCTLENUM_H__


/////////////////////////////////////////////////////////////////////////////
// IEnumMimicsCtrls

DECLARE_INTERFACE_(IEnumMimicsCtrls, IUnknown)
{
	STDMETHOD(QueryInterface)(REFIID, LPVOID *) PURE;
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;
	STDMETHOD_(BOOL, GetMimicsCtrlProperties)(ULONG nID, BSTR *pszType, IID *pIID) PURE;
	STDMETHOD_(BOOL, TranslateMimicsCtrlTypeToCLSID)(CONST BSTR pszType, IID *pIID) PURE;
	STDMETHOD_(BOOL, TranslateMimicsCtrlIDToCLSID)(ULONG nID, IID *pIID) PURE;
	STDMETHOD_(ULONG, GetMimicsCtrlsCount)() PURE;
	STDMETHOD_(BSTR, GetMimicsClipboardFormat)() PURE;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEnumMimicsCtrls

class CEnumMimicsCtrls : public CCmdTarget
{
	DECLARE_DYNCREATE(CEnumMimicsCtrls)
	DECLARE_OLECREATE_EX(CEnumMimicsCtrls)

	// Constructors
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnumMimicsCtrls)
	//}}AFX_VIRTUAL

	// Interface Maps
public:
	BEGIN_INTERFACE_PART(EnumMimicsCtrls, IEnumMimicsCtrls)
		INIT_INTERFACE_PART(CEnumMimicsCtrls, EnumMimicsCtrls)
		STDMETHOD_(BOOL, GetMimicsCtrlProperties)(ULONG nID, BSTR *pszType, IID *pIID);
		STDMETHOD_(BOOL, TranslateMimicsCtrlTypeToCLSID)(CONST BSTR pszType, IID *pIID);
		STDMETHOD_(BOOL, TranslateMimicsCtrlIDToCLSID)(ULONG nID, IID *pIID);
		STDMETHOD_(ULONG, GetMimicsCtrlsCount)();
		STDMETHOD_(BSTR, GetMimicsClipboardFormat)();
	END_INTERFACE_PART(EnumMimicsCtrls)

	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSCTLENUM_H__
