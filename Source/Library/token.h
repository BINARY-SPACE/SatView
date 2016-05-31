// TOKEN.H : Token Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the token related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1996/10/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TOKEN_H__
#define __TOKEN_H__


/////////////////////////////////////////////////////////////////////////////
// CModuleToken

class AFX_EXT_CLASS CModuleToken : virtual public CObject
{
	// Construction
public:
	CModuleToken();
	CModuleToken(LPCTSTR pszComputerName);

	// Attributes
protected:
	CString  m_szModuleName;

	// Operations
public:
	BOOL SetModuleName(LPCTSTR pszModuleName = NULL);
	CString GetModuleName() CONST;

	CString GetModuleFileRoot() CONST;
	CString GetModuleFileName() CONST;
	CString GetModuleFileTitle() CONST;

	CModuleToken &operator=(CONST CString &szModuleName);
	CModuleToken &operator=(LPCTSTR pszModuleName);
	BOOL operator==(CONST CString &szModuleName) CONST;
	BOOL operator==(LPCTSTR pszModuleName) CONST;
	BOOL operator!=(CONST CString &szModuleName) CONST;
	BOOL operator!=(LPCTSTR pszModuleName) CONST;
	operator LPCTSTR() CONST;

private:
	CString QueryDefaultModuleName() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CComputerToken

class AFX_EXT_CLASS CComputerToken : virtual public CObject
{
	// Construction
public:
	CComputerToken();
	CComputerToken(LPCTSTR pszComputerName);

	// Attributes
protected:
	CString  m_szComputerName;

	// Operations
public:
	BOOL SetComputerName(LPCTSTR pszComputerName = NULL);
	CString GetComputerName() CONST;
	CString GetComputerUNCName() CONST;

	BOOL IsHost() CONST;

	CComputerToken &operator=(CONST CString &szComputerName);
	CComputerToken &operator=(LPCTSTR pszComputerName);
	BOOL operator==(CONST CString &szComputerName) CONST;
	BOOL operator==(LPCTSTR pszComputerName) CONST;
	BOOL operator!=(CONST CString &szComputerName) CONST;
	BOOL operator!=(LPCTSTR pszComputerName) CONST;
	operator LPCTSTR() CONST;

private:
	CString QueryDefaultComputerName() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftToken

class AFX_EXT_CLASS CSpacecraftToken : virtual public CObject
{
	// Construction
public:
	CSpacecraftToken();
	CSpacecraftToken(LPCTSTR pszSpacecraftName);

	// Attributes
protected:
	CString  m_szSpacecraftName;

	// Operations
public:
	BOOL SetSpacecraftName(LPCTSTR pszSpacecraftName = NULL);
	CString GetSpacecraftName() CONST;

	CSpacecraftToken &operator=(CONST CString &szSpacecraftName);
	CSpacecraftToken &operator=(LPCTSTR pszSpacecraftName);
	BOOL operator==(CONST CString &szSpacecraftName) CONST;
	BOOL operator==(LPCTSTR pszSpacecraftName) CONST;
	BOOL operator!=(CONST CString &szSpacecraftName) CONST;
	BOOL operator!=(LPCTSTR pszSpacecraftName) CONST;
	operator LPCTSTR() CONST;

private:
	CString QueryDefaultSpacecraftName() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserToken

class AFX_EXT_CLASS CUserToken : virtual public CObject
{
	// Construction
public:
	CUserToken();
	CUserToken(LPCTSTR pszUserName);

	// Attributes
protected:
	CString  m_szUserName;

	// Operations
public:
	BOOL SetUserName(LPCTSTR pszUserName = NULL);
	CString GetUserName() CONST;

	BOOL IsAdministrator(BOOL bUnique = FALSE) CONST;

	CUserToken &operator=(CONST CString &szUserName);
	CUserToken &operator=(LPCTSTR pszUserName);
	BOOL operator==(CONST CString &szUserName) CONST;
	BOOL operator==(LPCTSTR pszUserName) CONST;
	BOOL operator!=(CONST CString &szUserName) CONST;
	BOOL operator!=(LPCTSTR pszUserName) CONST;
	operator LPCTSTR() CONST;

private:
	CString QueryDefaultUserName() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToken

class AFX_EXT_CLASS CToken : public CComputerToken, public CSpacecraftToken, public CUserToken
{
	// Construction
public:
	CToken();
	CToken(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName);

	// Attributes
public:

	// Operations
public:
	BOOL SetOwner(CONST CToken *pToken);
	BOOL SetOwner(LPCTSTR pszComputerName = NULL, LPCTSTR pszSpacecraftName = NULL, LPCTSTR pszUserName = NULL);
	BOOL GetOwner(CString &szComputerName, CString &szSpacecraftName, CString &szUserName) CONST;

	BOOL HasOwner() CONST;
	BOOL HasSameOwner(CONST CToken *pToken) CONST;
	BOOL HasSameOwner(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST;

	CToken &operator=(CToken &cToken);
	BOOL operator==(CONST CToken &cToken) CONST;
	BOOL operator!=(CONST CToken &cToken) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TOKEN_H__
