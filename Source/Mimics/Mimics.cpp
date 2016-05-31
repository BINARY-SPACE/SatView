// MIMICS.CPP : SatView Mimics Controls Application.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the application related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMimicsApp  cMimicsApp;


const GUID CDECL BASED_CODE  CMimicsApp::guidApp = { 0xd9b0d9eb,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const WORD  CMimicsApp::wAppVerMajor = 1;
const WORD  CMimicsApp::wAppVerMinor = 0;



/////////////////////////////////////////////////////////////////////////////
// CMimicsApp

CMimicsApp::CMimicsApp() : COleControlModule()
{
	m_pStringTable = (LPTSTR *)NULL;
	m_pStringIDTable = (LPINT)NULL;
	m_nStringCount = 0;
}

BOOL CMimicsApp::InitInstance()
{
	return((COleControlModule::InitInstance() && LoadStrings() && RegisterCustomControls()) ? TRUE : FALSE);
}

int CMimicsApp::ExitInstance()
{
	FreeStrings();
	UnregisterCustomControls();
	return COleControlModule::ExitInstance();
}

LPCTSTR CMimicsApp::String(INT nID) CONST
{
	INT  nIndex;

	return(((nIndex = SearchString(nID)) != -1) ? m_pStringTable[nIndex] : EMPTYSTRING);
}

TCHAR CMimicsApp::StringChar(INT nID) CONST
{
	return String(nID)[0];
}

LANGID CMimicsApp::GetLanguageID() CONST
{
	return m_nLanguageID;
}

INT CMimicsApp::GetLocaleData(UINT nDataID, LPVOID pData, INT cbMax) CONST
{
	return GetLocaleData(MAKEINTRESOURCE(nDataID), pData, cbMax);
}
INT CMimicsApp::GetLocaleData(LPCTSTR pszDataName, LPVOID pData, INT cbMax) CONST
{
	HMODULE  hModule;
	INT  cbDataTemplate;
	HRSRC  hDataTemplate;
	LPVOID  pDataTemplate;
	HGLOBAL  hDataTemplateMemory;

	if ((hDataTemplate = FindResourceEx((hModule = GetModuleInstance()), RT_RCDATA, pszDataName, m_nLanguageID)) || (hDataTemplate = FindResourceEx(hModule, RT_RCDATA, pszDataName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDataTemplate = FindResourceEx(hModule, RT_RCDATA, pszDataName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbDataTemplate = SizeofResource(hModule, hDataTemplate)) <= cbMax  &&  AfxIsValidAddress(pData, cbMax))
		{
			if ((hDataTemplateMemory = LoadResource(hModule, hDataTemplate)))
			{
				if ((pDataTemplate = LockResource(hDataTemplateMemory)))
				{
					CopyMemory(pData, pDataTemplate, cbDataTemplate);
					return cbDataTemplate;
				}
			}
			return 0;
		}
		return((!cbMax) ? cbDataTemplate : 0);
	}
	return 0;
}

LPCTSTR CMimicsApp::GetModuleName() CONST
{
	static TCHAR  szName[MAX_PATH];

	return((GetModuleFileName(cMimicsApp.m_hInstance, szName, sizeof(szName) / sizeof(TCHAR))) ? (LPCTSTR)szName : (LPCTSTR)NULL);
}

HINSTANCE CMimicsApp::GetModuleInstance() CONST
{
	return cMimicsApp.m_hInstance;
}

BOOL CMimicsApp::LoadStrings()
{
	INT  cbLanguage;
	LPTSTR  pszLanguage;

	if ((m_nLanguageID = GetUserDefaultLangID()))
	{
		if (EnumResourceNames(GetModuleInstance(), RT_STRING, (ENUMRESNAMEPROC)EnumStrings, (LONG_PTR) this) || GetLastError() == ERROR_RESOURCE_TYPE_NOT_FOUND)
		{
			if ((cbLanguage = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_SABBREVLANGNAME, (LPTSTR)NULL, 0)))
			{
				if ((pszLanguage = (LPTSTR)GlobalAlloc(GPTR, cbLanguage*sizeof(TCHAR))) != (LPTSTR)NULL)
				{
					if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_SABBREVLANGNAME, pszLanguage, cbLanguage))
					{
						_tsetlocale(LC_ALL, pszLanguage);
						GlobalFree(pszLanguage);
						return TRUE;
					}
					GlobalFree(pszLanguage);
				}
			}
		}
		FreeStrings();
	}
	return FALSE;
}

VOID CMimicsApp::FreeStrings()
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

INT CMimicsApp::SearchString(INT nID) CONST
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

BOOL CALLBACK CMimicsApp::EnumStrings(HINSTANCE hModule, LPCTSTR pszType, LPTSTR pszName, CMimicsApp *pMimicsApp)
{
	return EnumResourceLanguages(hModule, pszType, pszName, (ENUMRESLANGPROC)EnumLocaleStrings, (LONG_PTR)pMimicsApp);
}

BOOL CALLBACK CMimicsApp::EnumLocaleStrings(HINSTANCE hModule, LPCTSTR pszType, LPCTSTR pszName, WORD wLanguageID, CMimicsApp *pMimicsApp)
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

	if ((hStringBlock = FindResourceEx(hModule, pszType, pszName, pMimicsApp->m_nLanguageID)) || (hStringBlock = FindResourceEx(hModule, pszType, pszName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hStringBlock = FindResourceEx(hModule, pszType, pszName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbStringBlock = SizeofResource(hModule, hStringBlock)))
		{
			if ((hStringBlockMemory = LoadResource(hModule, hStringBlock)))
			{
				if ((pszStringBlock = (LPWSTR)LockResource(hStringBlockMemory)))
				{
					for (cPos = 0, cbStrings = 0, nStringID = (INT)(16 * ((INT_PTR)pszName - 1)); cbStrings < (INT)cbStringBlock; cPos += nStringLength + 1, cbStrings = cPos*sizeof(WCHAR), nStringID++)
					{
						if ((nStringLength = (INT)pszStringBlock[cPos]) != 0)
						{
							if ((pStringTable = (!pMimicsApp->m_pStringTable) ? (LPTSTR *)GlobalAlloc(GPTR, sizeof(LPTSTR)) : (LPTSTR *)GlobalReAlloc(pMimicsApp->m_pStringTable, (pMimicsApp->m_nStringCount + 1)*sizeof(LPTSTR), GMEM_MOVEABLE | GMEM_ZEROINIT)))
							{
								if ((pStringIDTable = (!pMimicsApp->m_pStringIDTable) ? (LPINT)GlobalAlloc(GPTR, sizeof(INT)) : (LPINT)GlobalReAlloc(pMimicsApp->m_pStringIDTable, (pMimicsApp->m_nStringCount + 1)*sizeof(INT), GMEM_MOVEABLE | GMEM_ZEROINIT)))
								{
									if ((pszBlockExtraction = (LPTSTR)GlobalAlloc(GPTR, (nStringLength + 1)*sizeof(TCHAR))))
									{
#ifndef UNICODE
										if (!WideCharToMultiByte(CP_ACP, (DWORD)NULL, &pszStringBlock[cPos + 1], nStringLength, pszBlockExtraction, nStringLength + 1, (LPSTR)NULL, (LPBOOL)NULL))
										{
											pMimicsApp->m_pStringIDTable = pStringIDTable;
											pMimicsApp->m_pStringTable = pStringTable;
											GlobalFree(pszBlockExtraction);
											break;
										}
#else
										wcsncpy_s(pszBlockExtraction, nStringLength + 1, &pszStringBlock[cPos + 1], nStringLength);
#endif
										pMimicsApp->m_pStringTable = pStringTable;
										pMimicsApp->m_pStringIDTable = pStringIDTable;
										pMimicsApp->m_pStringTable[pMimicsApp->m_nStringCount] = pszBlockExtraction;
										pMimicsApp->m_pStringIDTable[pMimicsApp->m_nStringCount] = nStringID;
										pMimicsApp->m_nStringCount++;
										continue;
									}
									pMimicsApp->m_pStringIDTable = pStringIDTable;
								}
								pMimicsApp->m_pStringTable = pStringTable;
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

BEGIN_MESSAGE_MAP(CMimicsApp, COleControlModule)
	//{{AFX_MSG_MAP(CMimicsApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsApp message handlers


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), CMimicsApp::guidApp)) return ResultFromScode(SELFREG_E_TYPELIB);
	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE)) return ResultFromScode(SELFREG_E_CLASS);
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)) return ResultFromScode(SELFREG_E_TYPELIB);
	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE)) return ResultFromScode(SELFREG_E_CLASS);
	return NOERROR;
}
