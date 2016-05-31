// VERSION.H : Version Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the version related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1992/10/26 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __VERSION_H__
#define __VERSION_H__

#include "token.h"


/////////////////////////////////////////////////////////////////////////////
// CVersionInfo

class AFX_EXT_CLASS CVersionInfo : public CModuleToken
{
	// Construction
public:
	CVersionInfo();
	CVersionInfo(LPCTSTR pszModuleName);

	// Attributes
public:

	// Operations
public:
	CString QueryApplicationTitle() CONST;
	CString QueryProductName() CONST;
	CString QueryProductVersion() CONST;
	CString QueryFileDescription() CONST;
	CString QueryFileVersion() CONST;
	CString QueryOriginalFileName() CONST;
	CString QueryCompanyName() CONST;
	CString QueryInternalName() CONST;
	CString QueryLegalCopyright() CONST;
	CString QueryLegalTrademark() CONST;
	CString QueryComments() CONST;

private:
	BOOL QueryVersionInfo(UINT nInfoType, CString &szInfo) CONST;
	BOOL QueryVersionLanguageBlock(CONST LPVOID pVersionInfo, UINT nInfoType, CString &szBlock) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __VERSION_H__
