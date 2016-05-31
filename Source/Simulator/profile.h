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
* 2010/12/23 | 1.00.00 | Initial creation. [AW]                      *
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
	BOOL SetIODevicesData(CONST CByteArray &nData);
	BOOL GetIODevicesData(CByteArray &nData) CONST;

	BOOL DeleteAllInfo();

private:
	CString QuerySubKey() CONST;

	BOOL DeleteSubKey(LPCTSTR pszSubKey);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __PROFILE_H__
