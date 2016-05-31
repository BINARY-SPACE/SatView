// PROFILES.CPP : Profiles Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the profiles related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1997/10/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CPrintProfileInfo

CPrintProfileInfo::CPrintProfileInfo() : CObject()
{
	PRINTDLG  sPrinterInfo;
	TCHAR  szPaperMeasure[2];

	SetName(STRING(IDS_PROFILE_DEFAULTPRINTNAME));
	for (m_hDevNames = m_hDevMode = (HANDLE)NULL; GetPrinterDeviceDefaults(&sPrinterInfo); )
	{
		m_hDevNames = sPrinterInfo.hDevNames;
		m_hDevMode = sPrinterInfo.hDevMode;
		break;
	}
	m_sizePaperArea = PRINTINFO_DEFAULT_PAPERSIZE;
	m_rtPaperMargin[0] = CRect(PRINTINFO_DEFAULT_PAPERFRAME);
	m_rtPaperMargin[1] = ((m_bPaperMeasure = (GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IMEASURE, szPaperMeasure, sizeof(szPaperMeasure) / sizeof(TCHAR))) ? (1 - min(_ttoi(szPaperMeasure), TRUE)) : TRUE)) ? CRect(PRINTINFO_DEFAULT_METRICMARGIN) : CRect(PRINTINFO_DEFAULT_INCHMARGIN);
}

CPrintProfileInfo::~CPrintProfileInfo()
{
	if (m_hDevMode) GlobalFree(m_hDevMode);
	if (m_hDevNames) GlobalFree(m_hDevNames);
}

VOID CPrintProfileInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CPrintProfileInfo::GetName() CONST
{
	return m_szName;
}

BOOL CPrintProfileInfo::SetDeviceInfo(HANDLE hDevNames, HANDLE hDevMode)
{
	INT  nResolution;
	INT  nResolutions;
	LPINT  pResolutions;
	HANDLE  hDeviceMode;
	HANDLE  hDeviceNames;
	DEVMODE  *pDeviceMode[2];
	DEVNAMES  *pDeviceNames[2];

	if (!hDevNames || !hDevMode)
	{
		if (m_hDevNames) GlobalFree(m_hDevNames);
		if (m_hDevMode) GlobalFree(m_hDevMode);
		m_hDevNames = (HANDLE)NULL;
		m_hDevMode = (HANDLE)NULL;
		return TRUE;
	}
	if ((hDeviceNames = GlobalAlloc(GHND, GlobalSize(hDevNames))))
	{
		if ((hDeviceMode = GlobalAlloc(GHND, GlobalSize(hDevMode))))
		{
			if ((pDeviceNames[0] = (DEVNAMES *)GlobalLock(hDeviceNames)))
			{
				if ((pDeviceMode[0] = (DEVMODE *)GlobalLock(hDeviceMode)))
				{
					if ((pDeviceNames[1] = (DEVNAMES *)GlobalLock(hDevNames)))
					{
						if ((pDeviceMode[1] = (DEVMODE *)GlobalLock(hDevMode)))
						{
							CopyMemory(pDeviceNames[0], pDeviceNames[1], GlobalSize(hDevNames));
							CopyMemory(pDeviceMode[0], pDeviceMode[1], GlobalSize(hDevMode));
							if ((pResolutions = ((nResolutions = DeviceCapabilities((LPTSTR)pDeviceNames[0] + pDeviceNames[0]->wDeviceOffset, (LPTSTR)pDeviceNames[0] + pDeviceNames[0]->wOutputOffset, DC_ENUMRESOLUTIONS, (LPTSTR)NULL, (CONST DEVMODE *) NULL)) > 0) ? (LPINT)GlobalAlloc(GPTR, nResolutions * 2 * sizeof(INT)) : (LPINT)NULL))
							{
								if (DeviceCapabilities((LPTSTR)pDeviceNames[0] + pDeviceNames[0]->wDeviceOffset, (LPTSTR)pDeviceNames[0] + pDeviceNames[0]->wOutputOffset, DC_ENUMRESOLUTIONS, (LPTSTR)pResolutions, (CONST DEVMODE *) NULL) == nResolutions)
								{
									for (nResolution = 0; nResolution < 2 * nResolutions; nResolution += 2)
									{
										if (pResolutions[nResolution] == pDeviceMode[0]->dmPrintQuality)
										{
											if ((pDeviceMode[0]->dmFields & DM_YRESOLUTION) != DM_YRESOLUTION) break;
											if (pDeviceMode[0]->dmYResolution == pResolutions[nResolution + 1]) break;
										}
									}
									if (nResolution == 2 * nResolutions)
									{
										pDeviceMode[0]->dmPrintQuality = (pDeviceMode[0]->dmFields & DM_PRINTQUALITY) ? pResolutions[0] : pDeviceMode[0]->dmPrintQuality;
										pDeviceMode[0]->dmPrintQuality = (pDeviceMode[0]->dmFields & DM_YRESOLUTION) ? pResolutions[0] : pDeviceMode[0]->dmPrintQuality;
										pDeviceMode[0]->dmYResolution = (pDeviceMode[0]->dmFields & DM_YRESOLUTION) ? pResolutions[1] : pDeviceMode[0]->dmYResolution;
									}
									if (m_hDevNames) GlobalFree(m_hDevNames);
									if (m_hDevMode) GlobalFree(m_hDevMode);
									GlobalUnlock((m_hDevNames = hDeviceNames));
									GlobalUnlock((m_hDevMode = hDeviceMode));
									GlobalUnlock(hDevNames);
									GlobalUnlock(hDevMode);
									GlobalFree(pResolutions);
									return TRUE;
								}
								GlobalFree(pResolutions);
							}
							GlobalUnlock(hDevMode);
						}
						GlobalUnlock(hDevNames);
					}
					GlobalUnlock(hDeviceMode);
				}
				GlobalUnlock(hDeviceNames);
			}
			GlobalFree(hDeviceMode);
		}
		GlobalFree(hDeviceNames);
	}
	return FALSE;
}

BOOL CPrintProfileInfo::GetDeviceInfo(HANDLE &hDevNames, HANDLE &hDevMode) CONST
{
	HANDLE  hDeviceMode;
	HANDLE  hDeviceNames;
	DEVMODE  *pDeviceMode[2];
	DEVNAMES  *pDeviceNames[2];

	if (!m_hDevNames || !m_hDevMode)
	{
		hDevNames = (HANDLE)NULL;
		hDevMode = (HANDLE)NULL;
		return TRUE;
	}
	if ((hDeviceNames = GlobalAlloc(GHND, GlobalSize(m_hDevNames))))
	{
		if ((hDeviceMode = GlobalAlloc(GHND, GlobalSize(m_hDevMode))))
		{
			if ((pDeviceNames[0] = (DEVNAMES *)GlobalLock(hDeviceNames)))
			{
				if ((pDeviceMode[0] = (DEVMODE *)GlobalLock(hDeviceMode)))
				{
					if ((pDeviceNames[1] = (DEVNAMES *)GlobalLock(m_hDevNames)))
					{
						if ((pDeviceMode[1] = (DEVMODE *)GlobalLock(m_hDevMode)))
						{
							CopyMemory(pDeviceNames[0], pDeviceNames[1], GlobalSize(m_hDevNames));
							CopyMemory(pDeviceMode[0], pDeviceMode[1], GlobalSize(m_hDevMode));
							GlobalUnlock((hDevNames = hDeviceNames));
							GlobalUnlock((hDevMode = hDeviceMode));
							GlobalUnlock(m_hDevNames);
							GlobalUnlock(m_hDevMode);
							return TRUE;
						}
						GlobalUnlock(m_hDevNames);
					}
					GlobalUnlock(hDeviceMode);
				}
				GlobalUnlock(hDeviceNames);
			}
			GlobalFree(hDeviceMode);
		}
		GlobalFree(hDeviceNames);
	}
	return FALSE;
}

VOID CPrintProfileInfo::SetPaperInfo(CONST SIZE &sizePaperArea, CONST RECT &rtPaperMargin, CONST RECT &rtPaperFrame, BOOL bPaperMeasure)
{
	m_sizePaperArea.cx = sizePaperArea.cx;
	m_sizePaperArea.cy = sizePaperArea.cy;
	CopyRect(&m_rtPaperMargin[0], &rtPaperFrame);
	CopyRect(&m_rtPaperMargin[1], &rtPaperMargin);
	m_bPaperMeasure = bPaperMeasure;
}

BOOL CPrintProfileInfo::GetPaperInfo(SIZE &sizePaperArea, RECT &rtPaperMargin, RECT &rtPaperFrame, BOOL &bPaperMeasure) CONST
{
	sizePaperArea.cx = m_sizePaperArea.cx;
	sizePaperArea.cy = m_sizePaperArea.cy;
	CopyRect(&rtPaperFrame, &m_rtPaperMargin[0]);
	CopyRect(&rtPaperMargin, &m_rtPaperMargin[1]);
	bPaperMeasure = m_bPaperMeasure;
	return TRUE;
}

CString CPrintProfileInfo::GetPrinterName() CONST
{
	CString  szName;
	DEVMODE  *pDeviceMode;

	if ((pDeviceMode = (m_hDevMode) ? (DEVMODE *)GlobalLock(m_hDevMode) : (DEVMODE *)NULL))
	{
		szName = pDeviceMode->dmDeviceName;
		GlobalUnlock(m_hDevMode);
	}
	return szName;
}

CString CPrintProfileInfo::GetPaperForm() CONST
{
	CString  szForm;
	DEVMODE  *pDeviceMode;

	if ((pDeviceMode = (m_hDevMode) ? (DEVMODE *)GlobalLock(m_hDevMode) : (DEVMODE *)NULL))
	{
		if (pDeviceMode->dmFields & DM_FORMNAME)
		{
			szForm = pDeviceMode->dmFormName;
			GlobalUnlock(m_hDevMode);
		}
	}
	return szForm;
}

CString CPrintProfileInfo::GetPaperSource() CONST
{
	INT  nPaperBin;
	INT  nPaperBins;
	CString  szSource;
	LPWORD  pPaperBins;
	LPTSTR  pszPaperBins;
	DEVMODE  *pDeviceMode;
	DEVNAMES  *pDeviceNames;

	if ((pDeviceNames = (m_hDevNames) ? (DEVNAMES *)GlobalLock(m_hDevNames) : (DEVNAMES *)NULL))
	{
		if ((pDeviceMode = (m_hDevMode) ? (DEVMODE *)GlobalLock(m_hDevMode) : (DEVMODE *)NULL))
		{
			if (pDeviceMode->dmFields & DM_DEFAULTSOURCE)
			{
				if ((nPaperBins = DeviceCapabilities((LPTSTR)pDeviceNames + pDeviceNames->wDeviceOffset, (LPTSTR)pDeviceNames + pDeviceNames->wOutputOffset, DC_BINS, (LPTSTR)NULL, pDeviceMode)) > 0)
				{
					if ((pPaperBins = (LPWORD)GlobalAlloc(GPTR, nPaperBins*sizeof(WORD))))
					{
						if ((pszPaperBins = (LPTSTR)GlobalAlloc(GPTR, nPaperBins * 24 * sizeof(TCHAR))))
						{
							if (DeviceCapabilities((LPTSTR)pDeviceNames + pDeviceNames->wDeviceOffset, (LPTSTR)pDeviceNames + pDeviceNames->wOutputOffset, DC_BINS, (LPTSTR)pPaperBins, pDeviceMode) == nPaperBins  &&  DeviceCapabilities((LPTSTR)pDeviceNames + pDeviceNames->wDeviceOffset, (LPTSTR)pDeviceNames + pDeviceNames->wOutputOffset, DC_BINNAMES, pszPaperBins, pDeviceMode) == nPaperBins)
							{
								for (nPaperBin = 0; nPaperBin < nPaperBins; nPaperBin = nPaperBin + 1)
								{
									if (pPaperBins[nPaperBin] == pDeviceMode->dmDefaultSource) break;
									continue;
								}
								if (nPaperBin < nPaperBins)
								{
									szSource = &pszPaperBins[24 * nPaperBin];
									GlobalUnlock(m_hDevNames);
									GlobalUnlock(m_hDevMode);
									GlobalFree(pszPaperBins);
									GlobalFree(pPaperBins);
									return szSource;
								}
							}
							GlobalFree(pszPaperBins);
						}
						GlobalFree(pPaperBins);
					}
				}
			}
			GlobalUnlock(m_hDevMode);
		}
		GlobalUnlock(m_hDevNames);
	}
	return szSource;
}

INT CPrintProfileInfo::GetPaperOrientation() CONST
{
	INT  nOrientation;
	DEVMODE  *pDeviceMode;

	if ((pDeviceMode = (m_hDevMode) ? (DEVMODE *)GlobalLock(m_hDevMode) : (DEVMODE *)NULL))
	{
		if (pDeviceMode->dmFields & DM_ORIENTATION)
		{
			nOrientation = pDeviceMode->dmOrientation;
			GlobalUnlock(m_hDevMode);
			return nOrientation;
		}
	}
	return DMORIENT_PORTRAIT;
}

CSize CPrintProfileInfo::GetPaperResolution() CONST
{
	CSize  size;
	DEVMODE  *pDeviceMode;

	if ((pDeviceMode = (m_hDevMode) ? (DEVMODE *)GlobalLock(m_hDevMode) : (DEVMODE *)NULL))
	{
		if (pDeviceMode->dmFields & DM_PRINTQUALITY)
		{
			size.cx = pDeviceMode->dmPrintQuality;
			size.cy = size.cx;
			GlobalUnlock(m_hDevMode);
			return size;
		}
		if (pDeviceMode->dmFields & DM_YRESOLUTION)
		{
			size.cx = ((pDeviceMode->dmFields & DM_ORIENTATION) && (pDeviceMode->dmOrientation & DMORIENT_LANDSCAPE)) ? pDeviceMode->dmYResolution : pDeviceMode->dmPrintQuality;
			size.cy = ((pDeviceMode->dmFields & DM_ORIENTATION) && (pDeviceMode->dmOrientation & DMORIENT_LANDSCAPE)) ? pDeviceMode->dmPrintQuality : pDeviceMode->dmYResolution;
			GlobalUnlock(m_hDevMode);
			return size;
		}
		GlobalUnlock(m_hDevMode);
	}
	return CSize(0, 0);
}

INT CPrintProfileInfo::GetCopies() CONST
{
	INT  nCount;
	DEVMODE  *pDeviceMode;

	if ((pDeviceMode = (m_hDevMode) ? (DEVMODE *)GlobalLock(m_hDevMode) : (DEVMODE *)NULL))
	{
		if (pDeviceMode->dmFields & DM_COPIES)
		{
			nCount = pDeviceMode->dmCopies;
			GlobalUnlock(m_hDevMode);
			return nCount;
		}
		GlobalUnlock(m_hDevMode);
	}
	return FALSE;
}

BOOL CPrintProfileInfo::Copy(CONST CPrintProfileInfo *pProfileInfo)
{
	HANDLE  hDeviceMode;
	HANDLE  hDeviceNames;

	if (pProfileInfo->GetDeviceInfo(hDeviceNames, hDeviceMode))
	{
		for (m_szName = pProfileInfo->m_szName; m_hDevNames != (HANDLE)NULL; )
		{
			GlobalFree(m_hDevNames);
			break;
		}
		for (; m_hDevMode != (HANDLE)NULL; )
		{
			GlobalFree(m_hDevMode);
			break;
		}
		CopyMemory(&m_sizePaperArea, &pProfileInfo->m_sizePaperArea, sizeof(SIZE));
		CopyMemory(&m_rtPaperMargin[0], &pProfileInfo->m_rtPaperMargin[0], sizeof(RECT));
		CopyMemory(&m_rtPaperMargin[1], &pProfileInfo->m_rtPaperMargin[1], sizeof(RECT));
		CopyMemory(&m_bPaperMeasure, &pProfileInfo->m_bPaperMeasure, sizeof(BOOL));
		m_hDevNames = hDeviceNames;
		m_hDevMode = hDeviceMode;
		return TRUE;
	}
	return FALSE;
}

BOOL CPrintProfileInfo::Compare(CONST CPrintProfileInfo *pProfileInfo) CONST
{
	DEVMODE  *pDeviceMode[2];
	DEVNAMES  *pDeviceNames[2];

	if (pProfileInfo->m_hDevNames != (HANDLE)NULL  &&  pProfileInfo->m_hDevMode != (HANDLE)NULL  &&  m_hDevNames != (HANDLE)NULL  &&  m_hDevMode != (HANDLE)NULL)
	{
		if ((pDeviceNames[0] = (DEVNAMES *)GlobalLock(m_hDevNames)) != (DEVNAMES *)NULL)
		{
			if ((pDeviceMode[0] = (DEVMODE *)GlobalLock(m_hDevMode)) != (DEVMODE *)NULL)
			{
				if ((pDeviceNames[1] = (DEVNAMES *)GlobalLock(pProfileInfo->m_hDevNames)))
				{
					if ((pDeviceMode[1] = (DEVMODE *)GlobalLock(pProfileInfo->m_hDevMode)))
					{
						if (pProfileInfo->m_szName == m_szName  &&  !memcmp(pDeviceNames[0], pDeviceNames[1], min(GlobalSize(m_hDevNames), GlobalSize(pProfileInfo->m_hDevNames))) && !memcmp(pDeviceMode[0], pDeviceMode[1], min(GlobalSize(m_hDevMode), GlobalSize(pProfileInfo->m_hDevMode))) && !memcmp(&pProfileInfo->m_sizePaperArea, &m_sizePaperArea, sizeof(SIZE)) && !memcmp(&pProfileInfo->m_rtPaperMargin[0], &m_rtPaperMargin[0], sizeof(RECT)) && !memcmp(&pProfileInfo->m_rtPaperMargin[1], &m_rtPaperMargin[1], sizeof(RECT)) && !memcmp(&pProfileInfo->m_bPaperMeasure, &m_bPaperMeasure, sizeof(BOOL)))
						{
							GlobalUnlock(pProfileInfo->m_hDevNames);
							GlobalUnlock(pProfileInfo->m_hDevMode);
							GlobalUnlock(m_hDevNames);
							GlobalUnlock(m_hDevMode);
							return TRUE;
						}
						GlobalUnlock(pProfileInfo->m_hDevMode);
					}
					GlobalUnlock(pProfileInfo->m_hDevNames);
				}
				GlobalUnlock(m_hDevMode);
			}
			GlobalUnlock(m_hDevNames);
		}
	}
	return((pProfileInfo->m_hDevNames == m_hDevNames  &&  pProfileInfo->m_hDevMode == m_hDevMode  &&  !m_hDevNames  &&  !m_hDevMode  &&  !memcmp(&pProfileInfo->m_sizePaperArea, &m_sizePaperArea, sizeof(SIZE)) && !memcmp(&pProfileInfo->m_rtPaperMargin[0], &m_rtPaperMargin[0], sizeof(RECT)) && !memcmp(&pProfileInfo->m_rtPaperMargin[1], &m_rtPaperMargin[1], sizeof(RECT)) && !memcmp(&pProfileInfo->m_bPaperMeasure, &m_bPaperMeasure, sizeof(BOOL))) ? TRUE : FALSE);
}

BOOL CPrintProfileInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	DEVMODE  *pDeviceMode;
	DEVNAMES  *pDeviceNames;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDevMode = (m_hDevNames  &&  m_hDevMode) ? (INT)GlobalSize(m_hDevMode) : 0;
	sData.cbDevNames = (m_hDevNames  &&  m_hDevMode) ? (INT)GlobalSize(m_hDevNames) : 0;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbDevNames + sData.cbDevMode)), CopyMemory(&sData.sizePaperArea, &m_sizePaperArea, sizeof(sData.sizePaperArea)), CopyMemory(&sData.rtPaperMargin[0], &m_rtPaperMargin[0], sizeof(sData.rtPaperMargin[0])), CopyMemory(&sData.rtPaperMargin[1], &m_rtPaperMargin[1], sizeof(sData.rtPaperMargin[1])), CopyMemory(&sData.bPaperMeasure, &m_bPaperMeasure, sizeof(sData.bPaperMeasure)); nInfo.GetSize() == sData.cbSize; )
	{
		for (CopyMemory(nInfo.GetData(), &sData, sizeof(DATA)), CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName); (pDeviceNames = (sData.cbDevNames > 0) ? (DEVNAMES *)GlobalLock(m_hDevNames) : (DEVNAMES *)NULL); )
		{
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), pDeviceNames, sData.cbDevNames);
			GlobalUnlock(m_hDevNames);
			break;
		}
		if ((pDeviceMode = (sData.cbDevMode > 0) ? (DEVMODE *)GlobalLock(m_hDevMode) : (DEVMODE *)NULL))
		{
			CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevNames), pDeviceMode, sData.cbDevMode);
			GlobalUnlock(m_hDevMode);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CPrintProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	HANDLE  hDeviceMode;
	HANDLE  hDeviceNames;
	DEVMODE  *pDeviceMode;
	DEVNAMES  *pDeviceNames;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbDevNames + sData.cbDevMode && sData.cbName > 0 && sData.cbDevNames >= 0 && sData.cbDevMode >= 0; )
	{
		for (CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), CopyMemory(&m_sizePaperArea, &sData.sizePaperArea, sizeof(sData.sizePaperArea)), CopyMemory(&m_rtPaperMargin[0], &sData.rtPaperMargin[0], sizeof(sData.rtPaperMargin[0])), CopyMemory(&m_rtPaperMargin[1], &sData.rtPaperMargin[1], sizeof(sData.rtPaperMargin[1])), CopyMemory(&m_bPaperMeasure, &sData.bPaperMeasure, sizeof(sData.bPaperMeasure)), m_szName.ReleaseBuffer(); m_hDevNames != (HANDLE)NULL; )
		{
			GlobalFree((HANDLE)m_hDevNames);
			m_hDevNames = (HANDLE)NULL;
			break;
		}
		for (; m_hDevMode != (HANDLE)NULL; )
		{
			GlobalFree((HANDLE)m_hDevMode);
			m_hDevMode = (HANDLE)NULL;
			break;
		}
		if (sData.cbDevNames > 0 && sData.cbDevMode > 0)
		{
			if ((hDeviceNames = GlobalAlloc(GHND, sData.cbDevNames)))
			{
				if ((hDeviceMode = GlobalAlloc(GHND, sData.cbDevMode)))
				{
					if ((pDeviceNames = (DEVNAMES *)GlobalLock(hDeviceNames)))
					{
						if ((pDeviceMode = (DEVMODE *)GlobalLock(hDeviceMode)))
						{
							CopyMemory(pDeviceNames, nInfo.GetData() + (cbData = cbData + sData.cbName), sData.cbDevNames);
							CopyMemory(pDeviceMode, nInfo.GetData() + (cbData = cbData + sData.cbDevNames), sData.cbDevMode);
							GlobalUnlock((m_hDevNames = hDeviceNames));
							GlobalUnlock((m_hDevMode = hDeviceMode));
							return TRUE;
						}
						GlobalUnlock(hDeviceNames);
					}
					GlobalFree(hDeviceMode);
				}
				GlobalFree(hDeviceNames);
			}
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CPrintProfiles

CPrintProfiles::CPrintProfiles() : CMutexArray()
{
	return;
}

CPrintProfiles::~CPrintProfiles()
{
	RemoveAll();
}

INT CPrintProfiles::Add(CPrintProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CPrintProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CPrintProfiles::Enum(CStringArray &szNames) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CPrintProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), szNames.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) != (CPrintProfileInfo *)NULL)
		{
			szNames.Add(pProfileInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CPrintProfileInfo *CPrintProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPrintProfileInfo *)CMutexArray::GetAt(nIndex) : (CPrintProfileInfo *)NULL);
}

CPrintProfileInfo *CPrintProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CPrintProfileInfo *)CMutexArray::GetAt(nIndex) : (CPrintProfileInfo *)NULL);
}

VOID CPrintProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;
	CPrintProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile))) delete pProfileInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CPrintProfiles::Copy(CONST CPrintProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CPrintProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CPrintProfileInfo) != (CPrintProfileInfo *)NULL)
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CPrintProfiles::Compare(CONST CPrintProfiles *pProfiles) CONST
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (pProfiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if (!pProfiles->GetAt(nProfile)->Compare(GetAt(nProfile))) break;
		continue;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CPrintProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfilesData;
	CPrintProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfilesData) && nInfo.Append(nProfilesData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CPrintProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfilesData;
	CPrintProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfilesData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfilesData.GetSize() >= 0; )
		{
			CopyMemory(nProfilesData.GetData(), nInfo.GetData() + cbProfiles, nProfilesData.GetSize());
			break;
		}
		if ((pProfileInfo = new CPrintProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfilesData) && Add(pProfileInfo) >= 0) continue;
			delete pProfileInfo;
		}
		break;
	}
	if ((pProfileInfo = (!nInfo.GetSize()) ? new CPrintProfileInfo : (CPrintProfileInfo *)NULL))
	{
		for (pProfileInfo->SetName(STRING(IDS_PROFILE_DEFAULTPRINTNAME)); Add(pProfileInfo) >= 0; ) return TRUE;
		delete pProfileInfo;
		return FALSE;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CPrintProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CPrintProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfileInfo->GetName() == pszName) || (bInsert && (((pProfileInfo = GetAt(max(nIndex[0] - 1, 0))) && pProfileInfo->GetName() != pszName && (pProfileInfo = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pProfileInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CAuditionProfileInfo

CAuditionProfileInfo::CAuditionProfileInfo() : CObject()
{
	SetName(STRING(IDS_PROFILE_DEFAULTAUDITIONNAME));
	SetAdapterInfo(EMPTYSTRING, AUDITIONINFO_DEFAULT_VOLUME, AUDITIONINFO_DEFAULT_PITCH, AUDITIONINFO_DEFAULT_PLAYBACKRATE);
	SetAudition(AUDIO_NO_SOUND);
	SetWaveSound(EMPTYSTRING);
	SetBeepSound(AUDIO_DEFAULTBEEPFREQUENCY);
	SetVoiceSound(EMPTYSTRING, AUDIO_VOICEGENDER_MALE, AUDIO_VOICEAGE_ADULT);
}

CAuditionProfileInfo::~CAuditionProfileInfo()
{
	return;
}

VOID CAuditionProfileInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CAuditionProfileInfo::GetName() CONST
{
	return m_szName;
}

VOID CAuditionProfileInfo::SetAdapterInfo(LPCTSTR pszAdapter, DWORD dwVolume, DWORD dwPitch, DWORD dwPlaybackRate)
{
	m_szAdapter = pszAdapter;
	m_dwVolume = dwVolume;
	m_dwPitch = dwPitch;
	m_dwPlaybackRate = dwPlaybackRate;
}

BOOL CAuditionProfileInfo::GetAdapterInfo(CString &szAdapter, DWORD &dwVolume, DWORD &dwPitch, DWORD &dwPlaybackRate) CONST
{
	szAdapter = m_szAdapter;
	dwVolume = m_dwVolume;
	dwPitch = m_dwPitch;
	dwPlaybackRate = m_dwPlaybackRate;
	return !szAdapter.IsEmpty();
}

VOID CAuditionProfileInfo::SetAudition(INT nAudition)
{
	m_nAudition = nAudition;
}

INT CAuditionProfileInfo::GetAudition() CONST
{
	return m_nAudition;
}

VOID CAuditionProfileInfo::SetBeepSound(DWORD dwFrequency)
{
	m_dwFrequency = dwFrequency;
}

DWORD CAuditionProfileInfo::GetBeepSound() CONST
{
	return m_dwFrequency;
}

VOID CAuditionProfileInfo::SetWaveSound(LPCTSTR pszSound)
{
	m_szSound = pszSound;
}

CString CAuditionProfileInfo::GetWaveSound() CONST
{
	return m_szSound;
}

VOID CAuditionProfileInfo::SetVoiceSound(LPCTSTR pszSpeaker, WORD wGender, WORD wAge)
{
	m_szSpeaker = pszSpeaker;
	m_dwVoice = MAKELONG(wGender, wAge);
}

BOOL CAuditionProfileInfo::GetVoiceSound(CString &szSpeaker, WORD &wGender, WORD &wAge) CONST
{
	szSpeaker = m_szSpeaker;
	wGender = LOWORD(m_dwVoice);
	wAge = HIWORD(m_dwVoice);
	return !szSpeaker.IsEmpty();
}

VOID CAuditionProfileInfo::Copy(CONST CAuditionProfileInfo *pProfileInfo)
{
	m_szName = pProfileInfo->m_szName;
	m_szAdapter = pProfileInfo->m_szAdapter;
	m_szSpeaker = pProfileInfo->m_szSpeaker;
	m_szSound = pProfileInfo->m_szSound;
	m_nAudition = pProfileInfo->m_nAudition;
	m_dwVolume = pProfileInfo->m_dwVolume;
	m_dwPitch = pProfileInfo->m_dwPitch;
	m_dwPlaybackRate = pProfileInfo->m_dwPlaybackRate;
	m_dwFrequency = pProfileInfo->m_dwFrequency;
	m_dwVoice = pProfileInfo->m_dwVoice;
}

BOOL CAuditionProfileInfo::Compare(CONST CAuditionProfileInfo *pProfileInfo) CONST
{
	return((pProfileInfo->m_szName == m_szName  &&  pProfileInfo->m_szAdapter == m_szAdapter  &&  pProfileInfo->m_szSpeaker == m_szSpeaker  &&  pProfileInfo->m_nAudition == m_nAudition  &&  pProfileInfo->m_dwVolume == m_dwVolume  &&  pProfileInfo->m_dwPitch == m_dwPitch  &&  pProfileInfo->m_dwPlaybackRate == m_dwPlaybackRate && (pProfileInfo->m_nAudition != AUDIO_BEEP_SOUND || pProfileInfo->m_dwFrequency == m_dwFrequency) && (pProfileInfo->m_nAudition != AUDIO_WAVE_SOUND || !pProfileInfo->m_szSound.CompareNoCase(m_szSound)) && (pProfileInfo->m_nAudition != AUDIO_VOICE_SOUND || pProfileInfo->m_dwVoice == m_dwVoice)) ? TRUE : FALSE);
}

BOOL CAuditionProfileInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbSound = (m_szSound.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAdapter = (m_szAdapter.GetLength() + 1)*sizeof(TCHAR);
	sData.cbSpeaker = (m_szSpeaker.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbAdapter + sData.cbSpeaker + sData.cbSound)), sData.nAudition = m_nAudition, sData.dwVoice = m_dwVoice, sData.dwFrequency = m_dwFrequency, sData.dwVolume = m_dwVolume, sData.dwPitch = m_dwPitch, sData.dwPlaybackRate = m_dwPlaybackRate; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szAdapter, sData.cbAdapter);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAdapter), (LPCTSTR)m_szSpeaker, sData.cbSpeaker);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSpeaker), (LPCTSTR)m_szSound, sData.cbSound);
		return TRUE;
	}
	return FALSE;
}

BOOL CAuditionProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbAdapter + sData.cbSpeaker + sData.cbSound && sData.cbName > 0 && sData.cbAdapter > 0 && sData.cbSpeaker > 0 && sData.cbSound > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szAdapter.GetBufferSetLength(STRINGCHARS(sData.cbAdapter)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbAdapter));
		CopyMemory(m_szSpeaker.GetBufferSetLength(STRINGCHARS(sData.cbSpeaker)), nInfo.GetData() + (cbData = cbData + sData.cbAdapter), STRINGBYTES(sData.cbSpeaker));
		CopyMemory(m_szSound.GetBufferSetLength(STRINGCHARS(sData.cbSound)), nInfo.GetData() + (cbData = cbData + sData.cbSpeaker), STRINGBYTES(sData.cbSound));
		m_nAudition = sData.nAudition;
		m_dwVoice = sData.dwVoice;
		m_dwFrequency = sData.dwFrequency;
		m_dwVolume = sData.dwVolume;
		m_dwPitch = sData.dwPitch;
		m_dwPlaybackRate = sData.dwPlaybackRate;
		m_szName.ReleaseBuffer();
		m_szAdapter.ReleaseBuffer();
		m_szSpeaker.ReleaseBuffer();
		m_szSound.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CAuditionProfiles

CAuditionProfiles::CAuditionProfiles() : CMutexArray()
{
	return;
}

CAuditionProfiles::~CAuditionProfiles()
{
	RemoveAll();
}

INT CAuditionProfiles::Add(CAuditionProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CAuditionProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CAuditionProfiles::Enum(CStringArray &szNames) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CAuditionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), szNames.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) != (CAuditionProfileInfo *)NULL)
		{
			szNames.Add(pProfileInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CAuditionProfileInfo *CAuditionProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAuditionProfileInfo *)CMutexArray::GetAt(nIndex) : (CAuditionProfileInfo *)NULL);
}

CAuditionProfileInfo *CAuditionProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAuditionProfileInfo *)CMutexArray::GetAt(nIndex) : (CAuditionProfileInfo *)NULL);
}

VOID CAuditionProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;
	CAuditionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile))) delete pProfileInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CAuditionProfiles::Copy(CONST CAuditionProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CAuditionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CAuditionProfileInfo) != (CAuditionProfileInfo *)NULL)
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CAuditionProfiles::Compare(CONST CAuditionProfiles *pProfiles) CONST
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (pProfiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if (!pProfiles->GetAt(nProfile)->Compare(GetAt(nProfile))) break;
		continue;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CAuditionProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfilesData;
	CAuditionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfilesData) && nInfo.Append(nProfilesData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CAuditionProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfilesData;
	CAuditionProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfilesData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfilesData.GetSize() >= 0; )
		{
			CopyMemory(nProfilesData.GetData(), nInfo.GetData() + cbProfiles, nProfilesData.GetSize());
			break;
		}
		if ((pProfileInfo = new CAuditionProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfilesData) && Add(pProfileInfo) >= 0) continue;
			delete pProfileInfo;
		}
		break;
	}
	if ((pProfileInfo = (!nInfo.GetSize()) ? new CAuditionProfileInfo : (CAuditionProfileInfo *)NULL))
	{
		for (pProfileInfo->SetName(STRING(IDS_PROFILE_DEFAULTAUDITIONNAME)); Add(pProfileInfo) >= 0; ) return TRUE;
		delete pProfileInfo;
		return FALSE;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CAuditionProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CAuditionProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfileInfo->GetName() == pszName) || (bInsert && (((pProfileInfo = GetAt(max(nIndex[0] - 1, 0))) && pProfileInfo->GetName() != pszName && (pProfileInfo = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pProfileInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CNotificationProfileInfo

CNotificationProfileInfo::CNotificationProfileInfo() : CObject()
{
	SetType(NOTIFICATIONINFO_TYPE_NONE);
	SetName(STRING(IDS_PROFILE_DEFAULTNOTIFICATIONNAME));
	SetOptions(NOTIFICATIONINFO_OPTION_AUDIT_NOTHING);
	SetPriority(NOTIFICATIONINFO_PRIORITY_DEFAULT);
	SetBehaviorInfo(0, 0, 0);
	SetRetryCount(0);
	SetRetryTime(0);
}

CNotificationProfileInfo::~CNotificationProfileInfo()
{
	return;
}

VOID CNotificationProfileInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CNotificationProfileInfo::GetName() CONST
{
	return m_szName;
}

VOID CNotificationProfileInfo::SetType(UINT nType)
{
	CFont  cFont;
	CFontTools  cFontTools;

	if (nType == NOTIFICATIONINFO_TYPE_NONE || m_nType != nType)
	{
		if ((m_nType = nType) == NOTIFICATIONINFO_TYPE_NONE || nType == NOTIFICATIONINFO_TYPE_EMAIL || nType == NOTIFICATIONINFO_TYPE_PHONECALL || nType == NOTIFICATIONINFO_TYPE_PAGERCALL || nType == NOTIFICATIONINFO_TYPE_FTPMESSAGE)
		{
			if (cFontTools.QueryDefaultFont(&cFont))
			{
				cFont.GetLogFont(&m_lfFonts[0]);
				cFont.GetLogFont(&m_lfFonts[1]);
				cFont.GetLogFont(&m_lfFonts[2]);
			}
			m_nFontColors[0] = VGA_COLOR_BLACK;
			m_nFontColors[1] = VGA_COLOR_BLACK;
			m_nFontColors[2] = VGA_COLOR_BLACK;
		}
		if (nType == NOTIFICATIONINFO_TYPE_NONE || nType != NOTIFICATIONINFO_TYPE_FTPMESSAGE)
		{
			m_szFTPUserNames[0].RemoveAll();
			m_szFTPUserNames[1].RemoveAll();
			m_szFTPAddresses.RemoveAll();
			m_szFTPPasswords.RemoveAll();
			m_nFTPPort = 0;
		}
		if (nType == NOTIFICATIONINFO_TYPE_NONE || nType != NOTIFICATIONINFO_TYPE_PHONECALL)
		{
			m_wVoice[0] = AUDIO_VOICEGENDER_MALE;
			m_wVoice[1] = AUDIO_VOICEAGE_ADULT;
			m_szSpeaker.Empty();
			m_bConversation = FALSE;
		}
		for (; nType == NOTIFICATIONINFO_TYPE_NONE || nType != NOTIFICATIONINFO_TYPE_EMAIL; )
		{
			m_szAttachments.RemoveAll();
			break;
		}
		for (; nType == NOTIFICATIONINFO_TYPE_NONE || nType == NOTIFICATIONINFO_TYPE_EMAIL || nType == NOTIFICATIONINFO_TYPE_FAX || nType == NOTIFICATIONINFO_TYPE_FTPMESSAGE || nType == NOTIFICATIONINFO_TYPE_PRINTERMESSAGE; )
		{
			m_szModem.Empty();
			break;
		}
		m_nRetry[0] = m_nRetry[1] = 0;
		m_tRetryInterval = 0;
		m_tAbortInterval = 0;
	}
}

UINT CNotificationProfileInfo::GetType() CONST
{
	return m_nType;
}

VOID CNotificationProfileInfo::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CNotificationProfileInfo::GetOptions() CONST
{
	return m_nOptions;
}

VOID CNotificationProfileInfo::SetProlog(LPCTSTR pszText)
{
	m_szText[0] = pszText;
}

CString CNotificationProfileInfo::GetProlog() CONST
{
	return m_szText[0];
}

VOID CNotificationProfileInfo::SetMessage(LPCTSTR pszText)
{
	m_szText[1] = pszText;
}

CString CNotificationProfileInfo::GetMessage() CONST
{
	return m_szText[1];
}

VOID CNotificationProfileInfo::SetEpilog(LPCTSTR pszText)
{
	m_szText[2] = pszText;
}

CString CNotificationProfileInfo::GetEpilog() CONST
{
	return m_szText[2];
}

VOID CNotificationProfileInfo::SetAttachments(CONST CStringArray &szAttachments)
{
	m_szAttachments.Copy(szAttachments);
}

INT CNotificationProfileInfo::GetAttachments(CStringArray &szAttachments) CONST
{
	szAttachments.Copy(m_szAttachments);
	return((INT)szAttachments.GetSize());
}

VOID CNotificationProfileInfo::SetRecipients(CONST CStringArray &szRecipients)
{
	m_szRecipients.Copy(szRecipients);
}

INT CNotificationProfileInfo::GetRecipients(CStringArray &szRecipients) CONST
{
	szRecipients.Copy(m_szRecipients);
	return((INT)szRecipients.GetSize());
}

VOID CNotificationProfileInfo::SetPriority(UINT nPriority)
{
	m_nPriority = nPriority;
}

UINT CNotificationProfileInfo::GetPriority() CONST
{
	return m_nPriority;
}

VOID CNotificationProfileInfo::SetModemInfo(LPCTSTR pszModem)
{
	m_szModem = pszModem;
}

BOOL CNotificationProfileInfo::GetModemInfo(CString &szModem) CONST
{
	szModem = m_szModem;
	return !szModem.IsEmpty();
}

VOID CNotificationProfileInfo::SetVoiceInfo(LPCTSTR pszSpeaker, WORD wGender, WORD wAge, BOOL bConversation)
{
	m_wVoice[1] = wAge;
	m_wVoice[0] = wGender;
	m_szSpeaker = pszSpeaker;
	m_bConversation = bConversation;
}

BOOL CNotificationProfileInfo::GetVoiceInfo(CString &szSpeaker, WORD &wGender, WORD &wAge, BOOL &bConversation) CONST
{
	wAge = m_wVoice[1];
	wGender = m_wVoice[0];
	szSpeaker = m_szSpeaker;
	bConversation = m_bConversation;
	return((!szSpeaker.IsEmpty() && wGender >= AUDIO_VOICEGENDER_MALE  &&  wGender <= AUDIO_VOICEGENDER_NEUTRAL  &&  wAge >= AUDIO_VOICEAGE_BABY  &&  wAge <= AUDIO_VOICEAGE_SENIOR) ? TRUE : FALSE);
}

VOID CNotificationProfileInfo::SetFontInfo(CONST LOGFONT *plfPrologText, COLORREF nPrologTextColor, CONST LOGFONT *plfMessageText, COLORREF nMessageTextColor, CONST LOGFONT *plfEpilogText, COLORREF nEpilogTextColor)
{
	LOGFONT  lfFont = { 0 };

	m_nFontColors[0] = nPrologTextColor;
	m_nFontColors[2] = nEpilogTextColor;
	m_nFontColors[1] = nMessageTextColor;
	CopyMemory(&m_lfFonts[0], plfPrologText, sizeof(LOGFONT));
	CopyMemory(&m_lfFonts[2], plfEpilogText, sizeof(LOGFONT));
	CopyMemory(&m_lfFonts[1], plfMessageText, sizeof(LOGFONT));
}

BOOL CNotificationProfileInfo::GetFontInfo(LOGFONT *plfPrologText, COLORREF &nPrologTextColor, LOGFONT *plfMessageText, COLORREF &nMessageTextColor, LOGFONT *plfEpilogText, COLORREF &nEpilogTextColor) CONST
{
	LOGFONT  lfFont = { 0 };

	nPrologTextColor = m_nFontColors[0];
	nEpilogTextColor = m_nFontColors[2];
	nMessageTextColor = m_nFontColors[1];
	CopyMemory(plfPrologText, &m_lfFonts[0], sizeof(LOGFONT));
	CopyMemory(plfEpilogText, &m_lfFonts[2], sizeof(LOGFONT));
	CopyMemory(plfMessageText, &m_lfFonts[1], sizeof(LOGFONT));
	return((memcmp(plfPrologText, &lfFont, sizeof(LOGFONT)) && memcmp(plfMessageText, &lfFont, sizeof(LOGFONT)) && memcmp(plfEpilogText, &lfFont, sizeof(LOGFONT))) ? TRUE : FALSE);
}

VOID CNotificationProfileInfo::SetFTPInfo(CONST CStringArray &szUsers, CONST CStringArray &szLogins, CONST CStringArray &szAddresses, CONST CStringArray &szPasswords, UINT nPort)
{
	m_nFTPPort = nPort;
	m_szFTPUserNames[0].Copy(szUsers);
	m_szFTPUserNames[1].Copy(szLogins);
	m_szFTPAddresses.Copy(szAddresses);
	m_szFTPPasswords.Copy(szPasswords);
}

INT CNotificationProfileInfo::GetFTPInfo(CStringArray &szUsers, CStringArray &szLogins, CStringArray &szAddresses, CStringArray &szPasswords, UINT &nPort) CONST
{
	nPort = m_nFTPPort;
	szUsers.Copy(m_szFTPUserNames[0]);
	szLogins.Copy(m_szFTPUserNames[1]);
	szAddresses.Copy(m_szFTPAddresses);
	szPasswords.Copy(m_szFTPPasswords);
	return((INT)szUsers.GetSize());
}

VOID CNotificationProfileInfo::SetBehaviorInfo(UINT nRetryCount, CONST CTimeSpan &tRetryInterval, CONST CTimeSpan &tAbortInterval)
{
	m_nRetry[0] = nRetryCount;
	m_tRetryInterval = tRetryInterval;
	m_tAbortInterval = tAbortInterval;
}

BOOL CNotificationProfileInfo::GetBehaviorInfo(UINT &nRetryCount, CTimeSpan &tRetryInterval, CTimeSpan &tAbortInterval) CONST
{
	nRetryCount = m_nRetry[0];
	tRetryInterval = m_tRetryInterval;
	tAbortInterval = m_tAbortInterval;
	return((nRetryCount > 0 && tRetryInterval > 0) ? TRUE : FALSE);
}

VOID CNotificationProfileInfo::SetRetryTime(CONST CTimeKey &tTime)
{
	m_tRetryTime = tTime;
}

CTimeKey CNotificationProfileInfo::GetRetryTime() CONST
{
	return m_tRetryTime;
}

VOID CNotificationProfileInfo::SetRetryCount(UINT nCount)
{
	m_nRetry[1] = nCount;
}

UINT CNotificationProfileInfo::GetRetryCount() CONST
{
	return m_nRetry[1];
}

VOID CNotificationProfileInfo::Copy(CONST CNotificationProfileInfo *pProfileInfo, BOOL bData)
{
	m_szName = pProfileInfo->m_szName;
	m_nType = pProfileInfo->m_nType;
	m_szModem = pProfileInfo->m_szModem;
	m_nOptions = pProfileInfo->m_nOptions;
	m_nPriority = pProfileInfo->m_nPriority;
	m_nFTPPort = pProfileInfo->m_nFTPPort;
	m_nRetry[0] = pProfileInfo->m_nRetry[0];
	m_szText[0] = pProfileInfo->m_szText[0];
	m_szText[1] = pProfileInfo->m_szText[1];
	m_szText[2] = pProfileInfo->m_szText[2];
	m_wVoice[0] = pProfileInfo->m_wVoice[0];
	m_wVoice[1] = pProfileInfo->m_wVoice[1];
	m_szSpeaker = pProfileInfo->m_szSpeaker;
	m_bConversation = pProfileInfo->m_bConversation;
	m_tAbortInterval = pProfileInfo->m_tAbortInterval;
	m_tRetryInterval = pProfileInfo->m_tRetryInterval;
	m_nFontColors[0] = pProfileInfo->m_nFontColors[0];
	m_nFontColors[1] = pProfileInfo->m_nFontColors[1];
	m_nFontColors[2] = pProfileInfo->m_nFontColors[2];
	m_szRecipients.Copy(pProfileInfo->m_szRecipients);
	m_szAttachments.Copy(pProfileInfo->m_szAttachments);
	m_szFTPUserNames[0].Copy(pProfileInfo->m_szFTPUserNames[0]);
	m_szFTPUserNames[1].Copy(pProfileInfo->m_szFTPUserNames[1]);
	m_szFTPAddresses.Copy(pProfileInfo->m_szFTPAddresses);
	m_szFTPPasswords.Copy(pProfileInfo->m_szFTPPasswords);
	m_nRetry[1] = (bData) ? pProfileInfo->m_nRetry[1] : m_nRetry[1];
	m_tRetryTime = (bData) ? pProfileInfo->m_tRetryTime : m_tRetryTime;
	CopyMemory(&m_lfFonts[0], &pProfileInfo->m_lfFonts[0], sizeof(LOGFONT));
	CopyMemory(&m_lfFonts[1], &pProfileInfo->m_lfFonts[1], sizeof(LOGFONT));
	CopyMemory(&m_lfFonts[2], &pProfileInfo->m_lfFonts[2], sizeof(LOGFONT));
}

BOOL CNotificationProfileInfo::Compare(CONST CNotificationProfileInfo *pProfileInfo, BOOL bData) CONST
{
	INT  nAttachment;
	INT  nAttachments;
	INT  nRecipient[2];
	INT  nRecipients[2];

	if (pProfileInfo->m_szName == m_szName  &&  pProfileInfo->m_nType == m_nType  &&  pProfileInfo->m_nOptions == m_nOptions  &&  pProfileInfo->m_nPriority == m_nPriority  &&  pProfileInfo->m_szText[0] == m_szText[0] && pProfileInfo->m_szText[1] == m_szText[1] && pProfileInfo->m_szText[2] == m_szText[2] && pProfileInfo->m_szRecipients.GetSize() == m_szRecipients.GetSize() && pProfileInfo->m_nRetry[0] == m_nRetry[0] && pProfileInfo->m_tRetryInterval == m_tRetryInterval && (!bData || (pProfileInfo->m_tRetryTime == m_tRetryTime  &&  pProfileInfo->m_nRetry[1] == m_nRetry[1])) && (!(m_nType & NOTIFICATIONINFO_TYPE_EMAIL) || pProfileInfo->m_szAttachments.GetSize() == m_szAttachments.GetSize()) && ((!(m_nType & NOTIFICATIONINFO_TYPE_PHONECALL) && !(m_nType & NOTIFICATIONINFO_TYPE_PAGERCALL)) || pProfileInfo->m_szModem == m_szModem) && (!(m_nType & NOTIFICATIONINFO_TYPE_PHONECALL) || (pProfileInfo->m_wVoice[0] == m_wVoice[0] && pProfileInfo->m_wVoice[1] == m_wVoice[1] && pProfileInfo->m_szSpeaker == m_szSpeaker  &&  pProfileInfo->m_bConversation == m_bConversation)) && (!(m_nType & NOTIFICATIONINFO_TYPE_PAGERCALL) || pProfileInfo->m_tAbortInterval == m_tAbortInterval) && (!(m_nType & NOTIFICATIONINFO_TYPE_FTPMESSAGE) || (pProfileInfo->m_szFTPUserNames[0].GetSize() == m_szFTPUserNames[0].GetSize() && pProfileInfo->m_szFTPUserNames[1].GetSize() == m_szFTPUserNames[1].GetSize() && pProfileInfo->m_szFTPAddresses.GetSize() == m_szFTPAddresses.GetSize() && pProfileInfo->m_szFTPPasswords.GetSize() == m_szFTPPasswords.GetSize() && m_szFTPUserNames[0].GetSize() == m_szFTPUserNames[1].GetSize() && m_szFTPUserNames[0].GetSize() == m_szFTPAddresses.GetSize() && m_szFTPUserNames[0].GetSize() == m_szFTPPasswords.GetSize() && pProfileInfo->m_nFTPPort == m_nFTPPort)) && ((!(m_nType & NOTIFICATIONINFO_TYPE_FAX) && !(m_nType & NOTIFICATIONINFO_TYPE_PRINTERMESSAGE)) || (pProfileInfo->m_nFontColors[0] == m_nFontColors[0] && pProfileInfo->m_nFontColors[1] == m_nFontColors[1] && pProfileInfo->m_nFontColors[2] == m_nFontColors[2] && !memcmp(&pProfileInfo->m_lfFonts[0], &m_lfFonts[0], sizeof(LOGFONT)) && !memcmp(&pProfileInfo->m_lfFonts[1], &m_lfFonts[1], sizeof(LOGFONT)) && !memcmp(&pProfileInfo->m_lfFonts[2], &m_lfFonts[2], sizeof(LOGFONT)))))
	{
		for (nRecipient[0] = 0, nRecipients[0] = (INT)pProfileInfo->m_szRecipients.GetSize(); nRecipient[0] < nRecipients[0]; nRecipient[0]++)
		{
			if (pProfileInfo->m_szRecipients.GetAt(nRecipient[0]) != m_szRecipients.GetAt(nRecipient[0])) break;
			continue;
		}
		for (nRecipient[1] = 0, nRecipients[1] = (m_nType & NOTIFICATIONINFO_TYPE_FTPMESSAGE) ? (INT)pProfileInfo->m_szFTPUserNames[0].GetSize() : 0; nRecipient[1] < nRecipients[1]; nRecipient[1]++)
		{
			if (pProfileInfo->m_szFTPUserNames[0].GetAt(nRecipient[1]) != m_szFTPUserNames[0].GetAt(nRecipient[1]) || pProfileInfo->m_szFTPUserNames[1].GetAt(nRecipient[1]) != m_szFTPUserNames[1].GetAt(nRecipient[1]) || pProfileInfo->m_szFTPAddresses.GetAt(nRecipient[1]) != m_szFTPAddresses.GetAt(nRecipient[1]) || pProfileInfo->m_szFTPPasswords.GetAt(nRecipient[1]) != m_szFTPPasswords.GetAt(nRecipient[1])) break;
			continue;
		}
		for (nAttachment = 0, nAttachments = (m_nType & NOTIFICATIONINFO_TYPE_EMAIL) ? (INT)pProfileInfo->m_szAttachments.GetSize() : 0; nAttachment < nAttachments; nAttachment++)
		{
			if (pProfileInfo->m_szAttachments.GetAt(nAttachment).CompareNoCase(m_szAttachments.GetAt(nAttachment))) break;
			continue;
		}
		return((nRecipient[0] == nRecipients[0] && nRecipient[1] == nRecipients[1] && nAttachment == nAttachments) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CNotificationProfileInfo::Map(CByteArray &nInfo) CONST
{
	INT  nDoc;
	INT  nDocs;
	INT  nUser;
	INT  nUsers;
	INT  cbData;
	DATA  sData;
	CByteArray  nFTPData[4];
	CByteArray  nRecipientsData;
	CByteArray  nAttachmentsData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbModem = (m_szModem.GetLength() + 1)*sizeof(TCHAR);
	sData.cbText[0] = (m_szText[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbText[1] = (m_szText[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbText[2] = (m_szText[2].GetLength() + 1)*sizeof(TCHAR);
	sData.cbSpeaker = (m_szSpeaker.GetLength() + 1)*sizeof(TCHAR);
	CopyMemory(&sData.lfFonts[0], &m_lfFonts[0], sizeof(LOGFONT));
	CopyMemory(&sData.lfFonts[1], &m_lfFonts[1], sizeof(LOGFONT));
	CopyMemory(&sData.lfFonts[2], &m_lfFonts[2], sizeof(LOGFONT));
	for (nUser = 0, nUsers = (INT)m_szRecipients.GetSize(), sData.cbRecipients = 0; nUser < nUsers; nUser++, sData.cbRecipients += cbData)
	{
		nRecipientsData.SetSize(sData.cbRecipients + (cbData = (m_szRecipients.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nRecipientsData.GetData() + sData.cbRecipients, (LPCTSTR)m_szRecipients.GetAt(nUser), cbData);
	}
	for (nUser = 0, nUsers = (INT)m_szFTPUserNames[0].GetSize(), sData.cbFTPUserNames[0] = 0; nUser < nUsers; nUser++, sData.cbFTPUserNames[0] += cbData)
	{
		nFTPData[0].SetSize(sData.cbFTPUserNames[0] + (cbData = (m_szFTPUserNames[0].GetAt(nUser).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nFTPData[0].GetData() + sData.cbFTPUserNames[0], (LPCTSTR)m_szFTPUserNames[0].GetAt(nUser), cbData);
	}
	for (nUser = 0, nUsers = (INT)m_szFTPUserNames[1].GetSize(), sData.cbFTPUserNames[1] = 0; nUser < nUsers; nUser++, sData.cbFTPUserNames[1] += cbData)
	{
		nFTPData[1].SetSize(sData.cbFTPUserNames[1] + (cbData = (m_szFTPUserNames[1].GetAt(nUser).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nFTPData[1].GetData() + sData.cbFTPUserNames[1], (LPCTSTR)m_szFTPUserNames[1].GetAt(nUser), cbData);
	}
	for (nUser = 0, nUsers = (INT)m_szFTPAddresses.GetSize(), sData.cbFTPAddresses = 0; nUser < nUsers; nUser++, sData.cbFTPAddresses += cbData)
	{
		nFTPData[2].SetSize(sData.cbFTPAddresses + (cbData = (m_szFTPAddresses.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nFTPData[2].GetData() + sData.cbFTPAddresses, (LPCTSTR)m_szFTPAddresses.GetAt(nUser), cbData);
	}
	for (nUser = 0, nUsers = (INT)m_szFTPPasswords.GetSize(), sData.cbFTPPasswords = 0; nUser < nUsers; nUser++, sData.cbFTPPasswords += cbData)
	{
		nFTPData[3].SetSize(sData.cbFTPPasswords + (cbData = (m_szFTPPasswords.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nFTPData[3].GetData() + sData.cbFTPPasswords, (LPCTSTR)m_szFTPPasswords.GetAt(nUser), cbData);
	}
	for (nDoc = 0, nDocs = (INT)m_szAttachments.GetSize(), sData.cbAttachments = 0; nDoc < nDocs; nDoc++, sData.cbAttachments += cbData)
	{
		nAttachmentsData.SetSize(sData.cbAttachments + (cbData = (m_szAttachments.GetAt(nDoc).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nAttachmentsData.GetData() + sData.cbAttachments, (LPCTSTR)m_szAttachments.GetAt(nDoc), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbText[0] + sData.cbText[1] + sData.cbText[2] + sData.cbRecipients + sData.cbModem + sData.cbSpeaker + sData.cbFTPUserNames[0] + sData.cbFTPUserNames[1] + sData.cbFTPAddresses + sData.cbFTPPasswords + sData.cbAttachments)), sData.nType = m_nType, sData.nOptions = m_nOptions, sData.nPriority = m_nPriority, sData.wVoice[0] = m_wVoice[0], sData.wVoice[1] = m_wVoice[1], sData.nFontColors[0] = m_nFontColors[0], sData.nFontColors[1] = m_nFontColors[1], sData.nFontColors[2] = m_nFontColors[2], sData.bConversation = m_bConversation, sData.nRetry[0] = m_nRetry[0], sData.nRetry[1] = m_nRetry[1], sData.tRetryTime = m_tRetryTime.GetTime(), sData.tRetryInterval = m_tRetryInterval.GetTotalSeconds(), sData.tAbortInterval = m_tAbortInterval.GetTotalSeconds(), sData.nFTPPort = m_nFTPPort; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szText[0], sData.cbText[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbText[0]), (LPCTSTR)m_szText[1], sData.cbText[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbText[1]), (LPCTSTR)m_szText[2], sData.cbText[2]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbText[2]), nRecipientsData.GetData(), sData.cbRecipients);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbRecipients), (LPCTSTR)m_szModem, sData.cbModem);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbModem), (LPCTSTR)m_szSpeaker, sData.cbSpeaker);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSpeaker), nFTPData[0].GetData(), sData.cbFTPUserNames[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPUserNames[0]), nFTPData[1].GetData(), sData.cbFTPUserNames[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPUserNames[1]), nFTPData[2].GetData(), sData.cbFTPAddresses);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPAddresses), nFTPData[3].GetData(), sData.cbFTPPasswords);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPPasswords), nAttachmentsData.GetData(), sData.cbAttachments);
		return TRUE;
	}
	return FALSE;
}

BOOL CNotificationProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbDoc;
	INT  cbDocs;
	INT  cbUser;
	INT  cbUsers;
	INT  cbData;
	DATA  sData;
	CByteArray  nFTPData[4];
	CByteArray  nRecipientsData;
	CByteArray  nAttachmentsData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbText[0] + sData.cbText[1] + sData.cbText[2] + sData.cbRecipients + sData.cbModem + sData.cbSpeaker + sData.cbFTPUserNames[0] + sData.cbFTPUserNames[1] + sData.cbFTPAddresses + sData.cbFTPPasswords + sData.cbAttachments && sData.cbName > 0 && sData.cbText[0] > 0 && sData.cbText[1] > 0 && sData.cbRecipients >= 0 && sData.cbModem > 0 && sData.cbSpeaker > 0 && sData.cbFTPUserNames[0] >= 0 && sData.cbFTPUserNames[1] >= 0 && sData.cbFTPAddresses >= 0 && sData.cbFTPPasswords >= 0 && sData.cbAttachments >= 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szText[0].GetBufferSetLength(STRINGCHARS(sData.cbText[0])), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbText[0]));
		CopyMemory(m_szText[1].GetBufferSetLength(STRINGCHARS(sData.cbText[1])), nInfo.GetData() + (cbData = cbData + sData.cbText[0]), STRINGBYTES(sData.cbText[1]));
		CopyMemory(m_szText[2].GetBufferSetLength(STRINGCHARS(sData.cbText[2])), nInfo.GetData() + (cbData = cbData + sData.cbText[1]), STRINGBYTES(sData.cbText[2]));
		for (nRecipientsData.SetSize(sData.cbRecipients), CopyMemory(nRecipientsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbText[2]), sData.cbRecipients), m_nType = sData.nType, m_nOptions = sData.nOptions, m_nPriority = sData.nPriority, m_wVoice[0] = sData.wVoice[0], m_wVoice[1] = sData.wVoice[1], m_nFontColors[0] = sData.nFontColors[0], m_nFontColors[1] = sData.nFontColors[1], m_nFontColors[2] = sData.nFontColors[2], m_bConversation = sData.bConversation, m_nRetry[0] = sData.nRetry[0], m_nRetry[1] = sData.nRetry[1], m_tRetryTime = sData.tRetryTime, m_tRetryInterval = sData.tRetryInterval, m_tAbortInterval = sData.tAbortInterval, m_nFTPPort = sData.nFTPPort, CopyMemory(&m_lfFonts[0], &sData.lfFonts[0], sizeof(LOGFONT)), CopyMemory(&m_lfFonts[1], &sData.lfFonts[1], sizeof(LOGFONT)), CopyMemory(&m_lfFonts[2], &sData.lfFonts[2], sizeof(LOGFONT)), m_szName.ReleaseBuffer(), m_szText[0].ReleaseBuffer(), m_szText[1].ReleaseBuffer(), m_szText[2].ReleaseBuffer(), m_szRecipients.RemoveAll(), cbUser = cbUsers = 0; cbUsers < sData.cbRecipients; cbUsers += (cbUser = (m_szRecipients.GetAt(m_szRecipients.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szRecipients.Add((LPCTSTR)(nRecipientsData.GetData() + cbUsers));
			continue;
		}
		for (nFTPData[0].SetSize(sData.cbFTPUserNames[0]), CopyMemory(m_szModem.GetBufferSetLength(STRINGCHARS(sData.cbModem)), nInfo.GetData() + (cbData = cbData + sData.cbRecipients), STRINGBYTES(sData.cbModem)), CopyMemory(m_szSpeaker.GetBufferSetLength(STRINGCHARS(sData.cbSpeaker)), nInfo.GetData() + (cbData = cbData + sData.cbModem), STRINGBYTES(sData.cbSpeaker)), CopyMemory(nFTPData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSpeaker), sData.cbFTPUserNames[0]), m_szModem.ReleaseBuffer(), m_szSpeaker.ReleaseBuffer(), m_szFTPUserNames[0].RemoveAll(), cbUser = cbUsers = 0; cbUsers < sData.cbFTPUserNames[0]; cbUsers += (cbUser = (m_szFTPUserNames[0].GetAt(m_szFTPUserNames[0].GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szFTPUserNames[0].Add((LPCTSTR)(nFTPData[0].GetData() + cbUsers));
			continue;
		}
		for (nFTPData[1].SetSize(sData.cbFTPUserNames[1]), CopyMemory(nFTPData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFTPUserNames[0]), sData.cbFTPUserNames[1]), m_szFTPUserNames[1].RemoveAll(), cbUser = cbUsers = 0; cbUsers < sData.cbFTPUserNames[1]; cbUsers += (cbUser = (m_szFTPUserNames[1].GetAt(m_szFTPUserNames[1].GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szFTPUserNames[1].Add((LPCTSTR)(nFTPData[1].GetData() + cbUsers));
			continue;
		}
		for (nFTPData[2].SetSize(sData.cbFTPAddresses), CopyMemory(nFTPData[2].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFTPUserNames[1]), sData.cbFTPAddresses), m_szFTPAddresses.RemoveAll(), cbUser = cbUsers = 0; cbUsers < sData.cbFTPAddresses; cbUsers += (cbUser = (m_szFTPAddresses.GetAt(m_szFTPAddresses.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szFTPAddresses.Add((LPCTSTR)(nFTPData[2].GetData() + cbUsers));
			continue;
		}
		for (nFTPData[3].SetSize(sData.cbFTPPasswords), CopyMemory(nFTPData[3].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFTPAddresses), sData.cbFTPPasswords), m_szFTPPasswords.RemoveAll(), cbUser = cbUsers = 0; cbUsers < sData.cbFTPPasswords; cbUsers += (cbUser = (m_szFTPPasswords.GetAt(m_szFTPPasswords.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szFTPPasswords.Add((LPCTSTR)(nFTPData[3].GetData() + cbUsers));
			continue;
		}
		for (nAttachmentsData.SetSize(sData.cbAttachments), CopyMemory(nAttachmentsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFTPPasswords), sData.cbAttachments), m_szAttachments.RemoveAll(), cbDocs = cbDoc = 0; cbDocs < sData.cbAttachments; cbDocs += (cbDoc = (m_szAttachments.GetAt(m_szAttachments.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szAttachments.Add((LPCTSTR)(nAttachmentsData.GetData() + cbDocs));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CNotificationProfiles

CNotificationProfiles::CNotificationProfiles() : CMutexArray()
{
	return;
}

CNotificationProfiles::~CNotificationProfiles()
{
	RemoveAll();
}

INT CNotificationProfiles::Add(CNotificationProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CNotificationProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CNotificationProfiles::Enum(CStringArray &szNames) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CNotificationProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), szNames.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) != (CNotificationProfileInfo *)NULL)
		{
			szNames.Add(pProfileInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CNotificationProfileInfo *CNotificationProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CNotificationProfileInfo *)CMutexArray::GetAt(nIndex) : (CNotificationProfileInfo *)NULL);
}

CNotificationProfileInfo *CNotificationProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CNotificationProfileInfo *)CMutexArray::GetAt(nIndex) : (CNotificationProfileInfo *)NULL);
}

VOID CNotificationProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;
	CNotificationProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile))) delete pProfileInfo;
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CNotificationProfiles::Copy(CONST CNotificationProfiles *pProfiles, BOOL bData)
{
	INT  nProfile;
	INT  nProfiles;
	CNotificationProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CNotificationProfileInfo) != (CNotificationProfileInfo *)NULL)
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile), bData);
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CNotificationProfiles::Compare(CONST CNotificationProfiles *pProfiles, BOOL bData) CONST
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (pProfiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if (!pProfiles->GetAt(nProfile)->Compare(GetAt(nProfile), bData)) break;
		continue;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CNotificationProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfilesData;
	CNotificationProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfilesData) && nInfo.Append(nProfilesData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CNotificationProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfilesData;
	CNotificationProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfilesData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfilesData.GetSize() >= 0; )
		{
			CopyMemory(nProfilesData.GetData(), nInfo.GetData() + cbProfiles, nProfilesData.GetSize());
			break;
		}
		if ((pProfileInfo = new CNotificationProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfilesData) && Add(pProfileInfo) >= 0) continue;
			delete pProfileInfo;
		}
		break;
	}
	if ((pProfileInfo = (!nInfo.GetSize()) ? new CNotificationProfileInfo : (CNotificationProfileInfo *)NULL))
	{
		for (pProfileInfo->SetName(STRING(IDS_PROFILE_DEFAULTNOTIFICATIONNAME)); Add(pProfileInfo) >= 0; ) return TRUE;
		delete pProfileInfo;
		return FALSE;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CNotificationProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CNotificationProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfileInfo->GetName() == pszName) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}
