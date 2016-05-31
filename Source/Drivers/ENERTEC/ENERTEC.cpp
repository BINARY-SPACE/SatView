// ENERTEC.CPP : ENERTEC TT&C 3801 Device Driver.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the ENERTEC TT&C 3801
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#define LIBRARYENVIRONMENT
#define USEENERTECDEVICESTRINGS

#include "ENERTEC.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CENERTECDeviceApp  cENERTECDeviceApp;



/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceApp

BOOL CENERTECDeviceApp::InitInstance()
{
	if (CLibraryApp::InitInstance() && LoadStrings())
	{
		RegisterCustomControls();
		return TRUE;
	}
	return FALSE;
}

int CENERTECDeviceApp::ExitInstance()
{
	FreeStrings();
	return CLibraryApp::ExitInstance();
}

INT CENERTECDeviceApp::EnumIODeviceProducts(LPTSTR *ppszProducts, INT nCount) CONST
{
	INT  nProduct;
	INT  nProducts;
	LPTSTR  pszProduct;
	CStringArray  szProducts;

	for (EnumIODeviceProducts(szProducts); ppszProducts != (LPTSTR *)NULL && nCount > 0; )
	{
		for (nProduct = 0, nProducts = min((INT)szProducts.GetSize(), nCount); nProduct < nProducts; nProduct++)
		{
			if ((pszProduct = (LPTSTR)GlobalAlloc(GPTR, (szProducts.GetAt(nProduct).GetLength() + 1)*sizeof(TCHAR))))
			{
				_tcscpy_s((ppszProducts[nProduct] = pszProduct), szProducts.GetAt(nProduct).GetLength() + 1, szProducts.GetAt(nProduct));
				continue;
			}
			break;
		}
		return(min(nProduct, nCount));
	}
	return((INT)szProducts.GetSize());
}
INT CENERTECDeviceApp::EnumIODeviceProducts(CStringArray &szProducts) CONST
{
	szProducts.RemoveAll();
	szProducts.Add(STRING(IDS_DEVICE_BRANDNAME));
	szProducts.Add(STRING(IDS_DEVICEEMULATION_BRANDNAME));
	return((INT)szProducts.GetSize());
}

CENERTECDevice *CENERTECDeviceApp::GetIODevice() CONST
{
	return new CENERTECDevice;
}

BOOL CENERTECDeviceApp::ShowHelp(LPCTSTR pszTopic)
{
	if (IsHelpAvailable())
	{
		HtmlHelp((DWORD_PTR)pszTopic, HH_DISPLAY_TOPIC);
		return TRUE;
	}
	return FALSE;
}

BOOL CENERTECDeviceApp::IsHelpAvailable() CONST
{
	CFileFindEx  cFileFind;

	if (cFileFind.FindFile(m_szHelpFileName))
	{
		cFileFind.Close();
		return TRUE;
	}
	return FALSE;
}

CENERTECDeviceApp *CENERTECDeviceApp::GetLibraryApp()
{
	return(&cENERTECDeviceApp);
}

__declspec(dllexport) INT EnumIODeviceProductsProc(LPTSTR *ppszProducts, INT nCount)
{
	return EnumIODeviceProducts(ppszProducts, nCount);
}
__declspec(dllexport) CIODevice *GetIODeviceEngineProc()
{
	return GetIODevice();
}

BEGIN_MESSAGE_MAP(CENERTECDeviceApp, CLibraryApp)
	//{{AFX_MSG_MAP(CENERTECDeviceApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceApp message handlers
