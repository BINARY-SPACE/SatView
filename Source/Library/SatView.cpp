// SATVIEW.CPP : SatView Library.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the library related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/02 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CLibraryApp  cLibraryApp;



/////////////////////////////////////////////////////////////////////////////
// CLibraryApp

CLibraryApp::CLibraryApp() : CWinAppEx()
{
	m_pStringTable = (LPTSTR *)NULL;
	m_pStringIDTable = (LPINT)NULL;
	m_nStringCount = 0;
}

LPCTSTR CLibraryApp::String(INT nID) CONST
{
	INT  nIndex;

	return(((nIndex = SearchString(nID)) != -1) ? m_pStringTable[nIndex] : EMPTYSTRING);
}

TCHAR CLibraryApp::StringChar(INT nID) CONST
{
	return String(nID)[0];
}

LPCTSTR CLibraryApp::GetLibraryName() CONST
{
	static TCHAR  szName[MAX_PATH];

	return((GetModuleFileName(m_hInstance, szName, sizeof(szName) / sizeof(TCHAR))) ? (LPCTSTR)szName : (LPCTSTR)NULL);
}

HINSTANCE CLibraryApp::GetLibraryInstance() CONST
{
	return m_hInstance;
}

BOOL CLibraryApp::LoadStrings()
{
	if (EnumResourceNames(m_hInstance, RT_STRING, (ENUMRESNAMEPROC)EnumStrings, (LONG_PTR) this) || GetLastError() == ERROR_RESOURCE_TYPE_NOT_FOUND) return TRUE;
	FreeStrings();
	return FALSE;
}

VOID CLibraryApp::FreeStrings()
{
	INT  nCount;

	if ((nCount = m_nStringCount) > 0)
	{
		while (nCount > 0) GlobalFree(m_pStringTable[--nCount]);
		GlobalFree(m_pStringTable);
		GlobalFree(m_pStringIDTable);
		m_pStringTable = (LPTSTR *)NULL;
		m_pStringIDTable = (LPINT)NULL;
		m_nStringCount = 0;
	}
}

INT CLibraryApp::SearchString(INT nID) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;
	INT  nStringID;

	if ((nMaxIndex = m_nStringCount) > 0)
	{
		if (nID >= 0 && (nID >= nMaxIndex || nID != m_pStringIDTable[nID]))
		{
			for (nMinIndex = 0, nMaxIndex = nMaxIndex - 1, nIndex = nMaxIndex / 2; nMaxIndex > nMinIndex; nIndex = (nMaxIndex + nMinIndex) / 2)
			{
				if ((nStringID = m_pStringIDTable[nIndex]) == nID) break;
				if (nStringID < nID)
				{
					nMinIndex = nIndex + 1;
					continue;
				}
				nMaxIndex = nIndex;
			}
			return((nID == m_pStringIDTable[nIndex]) ? nIndex : -1);
		}
		return((nID >= 0) ? nID : -1);
	}
	return -1;
}

BOOL CALLBACK CLibraryApp::EnumStrings(HINSTANCE hModule, LPCTSTR pszType, LPTSTR pszName, CLibraryApp *pLibraryApp)
{
	return EnumResourceLanguages(hModule, pszType, pszName, (ENUMRESLANGPROC)EnumLocaleStrings, (LONG_PTR)pLibraryApp);
}

BOOL CALLBACK CLibraryApp::EnumLocaleStrings(HINSTANCE hModule, LPCTSTR pszType, LPCTSTR pszName, WORD wLanguageID, CLibraryApp *pLibraryApp)
{
	INT  cPos;
	INT  cbStrings;
	INT  nStringID;
	INT  nStringLength;
	HRSRC  hStringBlock;
	DWORD  cbStringBlock;
	LPINT  pStringIDTable;
	LPTSTR  *pStringTable;
	LPWSTR  pszStringBlock;
	LPTSTR  pszBlockExtraction;
	HGLOBAL  hStringBlockMemory;

	if ((hStringBlock = FindResourceEx(hModule, pszType, pszName, GetUserDefaultLangID())) || (hStringBlock = FindResourceEx(hModule, pszType, pszName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hStringBlock = FindResourceEx(hModule, pszType, pszName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbStringBlock = SizeofResource(hModule, hStringBlock)))
		{
			if ((hStringBlockMemory = LoadResource(hModule, hStringBlock)))
			{
				if ((pszStringBlock = (LPWSTR)LockResource(hStringBlockMemory)))
				{
					for (cPos = 0, cbStrings = 0, nStringID = (INT)(16 * ((INT_PTR)pszName - 1)); cbStrings < (INT)cbStringBlock; cPos += nStringLength + 1, cbStrings = cPos*sizeof(WCHAR), nStringID++)
					{
						if ((nStringLength = (INT)pszStringBlock[cPos]))
						{
							if ((pStringTable = (!pLibraryApp->m_pStringTable) ? (LPTSTR *)GlobalAlloc(GPTR, sizeof(LPTSTR)) : (LPTSTR *)GlobalReAlloc(pLibraryApp->m_pStringTable, (pLibraryApp->m_nStringCount + 1)*sizeof(LPTSTR), GMEM_MOVEABLE | GMEM_ZEROINIT)))
							{
								if ((pStringIDTable = (!pLibraryApp->m_pStringIDTable) ? (LPINT)GlobalAlloc(GPTR, sizeof(INT)) : (LPINT)GlobalReAlloc(pLibraryApp->m_pStringIDTable, (pLibraryApp->m_nStringCount + 1)*sizeof(INT), GMEM_MOVEABLE | GMEM_ZEROINIT)))
								{
									if ((pszBlockExtraction = (LPTSTR)GlobalAlloc(GPTR, (nStringLength + 1)*sizeof(TCHAR))))
									{
#ifndef UNICODE
										if (!WideCharToMultiByte(CP_ACP, (DWORD)NULL, &pszStringBlock[cPos + 1], nStringLength, pszBlockExtraction, nStringLength + 1, (LPSTR)NULL, (LPBOOL)NULL))
										{
											pLibraryApp->m_pStringIDTable = pStringIDTable;
											pLibraryApp->m_pStringTable = pStringTable;
											GlobalFree(pszBlockExtraction);
											break;
										}
#else
										wcsncpy_s(pszBlockExtraction, nStringLength + 1, &pszStringBlock[cPos + 1], nStringLength);
#endif
										pLibraryApp->m_pStringTable = pStringTable;
										pLibraryApp->m_pStringIDTable = pStringIDTable;
										pLibraryApp->m_pStringTable[pLibraryApp->m_nStringCount] = pszBlockExtraction;
										pLibraryApp->m_pStringIDTable[pLibraryApp->m_nStringCount] = nStringID;
										pLibraryApp->m_nStringCount++;
										continue;
									}
									pLibraryApp->m_pStringIDTable = pStringIDTable;
								}
								pLibraryApp->m_pStringTable = pStringTable;
							}
							break;
						}
					}
					return((cbStrings >= (INT)cbStringBlock) ? TRUE : FALSE);
				}
			}
		}
	}
	return FALSE;
}

CLibraryApp *CLibraryApp::GetLibraryApp()
{
	return(&cLibraryApp);
}

BEGIN_MESSAGE_MAP(CLibraryApp, CWinAppEx)
	//{{AFX_MSG_MAP(CLibraryApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibraryApp message handlers
