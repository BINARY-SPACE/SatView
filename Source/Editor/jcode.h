// JCODE.H : JScript Code Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the automation script related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/06/30 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __JCODE_H__
#define __JCODE_H__


/////////////////////////////////////////////////////////////////////////////
// CJScriptCodeGenerator

class CJScriptCodeGenerator : public CObject
{
	// Construction
public:
	CJScriptCodeGenerator();

	// Attributes
public:

	// Operations
public:
	BOOL Compile(LPCTSTR pszName, LPCTSTR pszSourceCode, LPCTSTR pszExportCode, LPCTSTR pszOptions, LPCTSTR pszOutput, CStringArray &szErrors, CStringArray &szWarnings);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CJScriptCodeExecutor

class CJScriptCodeExecutor : public CObject
{
	// Construction
public:
	CJScriptCodeExecutor();

	// Attributes
public:

	// Operations
public:
	BOOL Run(LPCTSTR pszName, LPCTSTR pszTitle, LPCTSTR pszFileName, LPCTSTR pszInputFileName, LPCTSTR pszOutputFileName, CString &szError);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __JCODE_H__
