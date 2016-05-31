// BOOKS.CPP : Books Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the books related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/08 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CServerProfileInfo

CServerProfileInfo::CServerProfileInfo() : CObject()
{
	m_nMode = SERVERPROFILE_ACCESS_PHONE | SERVERPROFILE_BEHAVIOR_MODEMSPEAKER;
}

CServerProfileInfo::~CServerProfileInfo()
{
	return;
}

VOID CServerProfileInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CServerProfileInfo::GetName() CONST
{
	return m_szName;
}

VOID CServerProfileInfo::SetMode(UINT nMode)
{
	m_nMode = nMode;
}

UINT CServerProfileInfo::GetMode() CONST
{
	return m_nMode;
}

VOID CServerProfileInfo::SetDeviceInfo(LPCTSTR pszDevice, LPCTSTR pszType)
{
	m_szDevice = pszDevice;
	m_szDeviceType = pszType;
}

VOID CServerProfileInfo::GetDeviceInfo(CString &szDevice, CString &szType) CONST
{
	szDevice = m_szDevice;
	szType = m_szDeviceType;
}

VOID CServerProfileInfo::SetPhoneNumbers(CONST CStringArray &szNumbers)
{
	m_szPhoneNumbers.Copy(szNumbers);
}

INT CServerProfileInfo::GetPhoneNumbers(CStringArray &szNumbers) CONST
{
	szNumbers.Copy(m_szPhoneNumbers);
	return((INT)szNumbers.GetSize());
}

VOID CServerProfileInfo::SetCallbackNumber(LPCTSTR pszNumber)
{
	m_szCallbackNumber = pszNumber;
}

CString CServerProfileInfo::GetCallbackNumber() CONST
{
	return m_szCallbackNumber;
}

VOID CServerProfileInfo::Copy(CONST CServerProfileInfo *pProfileInfo)
{
	m_nMode = pProfileInfo->m_nMode;
	m_szName = pProfileInfo->m_szName;
	m_szDevice = pProfileInfo->m_szDevice;
	m_szDeviceType = pProfileInfo->m_szDeviceType;
	m_szPhoneNumbers.Copy(pProfileInfo->m_szPhoneNumbers);
	m_szCallbackNumber = pProfileInfo->m_szCallbackNumber;
}

BOOL CServerProfileInfo::Compare(CONST CServerProfileInfo *pProfileInfo) CONST
{
	INT  nNumber;
	INT  nNumbers;

	for (nNumber = 0, nNumbers = (pProfileInfo->m_szName == m_szName && pProfileInfo->m_nMode == m_nMode && pProfileInfo->m_szDevice == m_szDevice && pProfileInfo->m_szDeviceType == m_szDeviceType && pProfileInfo->m_szPhoneNumbers.GetSize() == m_szPhoneNumbers.GetSize() && pProfileInfo->m_szCallbackNumber == m_szCallbackNumber) ? (INT)m_szPhoneNumbers.GetSize() : -1; nNumber < nNumbers; nNumber++)
	{
		if (pProfileInfo->m_szPhoneNumbers.GetAt(nNumber) != m_szPhoneNumbers.GetAt(nNumber)) break;
		continue;
	}
	return((nNumber == nNumbers) ? TRUE : FALSE);
}

BOOL CServerProfileInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nNumber;
	INT  nNumbers;
	CByteArray  nNumberData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDevice = (m_szDevice.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDeviceType = (m_szDeviceType.GetLength() + 1)*sizeof(TCHAR);
	sData.cbCallbackNumber = (m_szCallbackNumber.GetLength() + 1)*sizeof(TCHAR);
	for (nNumber = 0, nNumbers = (INT)m_szPhoneNumbers.GetSize(), sData.cbPhoneNumbers = 0; nNumber < nNumbers; nNumber++, sData.cbPhoneNumbers += cbData)
	{
		nNumberData.SetSize(sData.cbPhoneNumbers + (cbData = (m_szPhoneNumbers.GetAt(nNumber).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nNumberData.GetData() + sData.cbPhoneNumbers, (LPCTSTR)m_szPhoneNumbers.GetAt(nNumber), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbDevice + sData.cbDeviceType + sData.cbPhoneNumbers + sData.cbCallbackNumber)), sData.nMode = m_nMode; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szDevice, sData.cbDevice);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice), (LPCTSTR)m_szDeviceType, sData.cbDeviceType);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDeviceType), nNumberData.GetData(), sData.cbPhoneNumbers);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbPhoneNumbers), (LPCTSTR)m_szCallbackNumber, sData.cbCallbackNumber);
		return TRUE;
	}
	return FALSE;
}

BOOL CServerProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbNumber;
	INT  cbNumbers;
	CByteArray  nNumberData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbDevice + sData.cbDeviceType + sData.cbPhoneNumbers + sData.cbCallbackNumber && sData.cbName > 0 && sData.cbDevice > 0 && sData.cbDeviceType > 0 && sData.cbPhoneNumbers >= 0 && sData.cbCallbackNumber > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szDevice.GetBufferSetLength(STRINGCHARS(sData.cbDevice)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbDevice));
		CopyMemory(m_szDeviceType.GetBufferSetLength(STRINGCHARS(sData.cbDeviceType)), nInfo.GetData() + (cbData = cbData + sData.cbDevice), STRINGBYTES(sData.cbDeviceType));
		for (nNumberData.SetSize(sData.cbPhoneNumbers), CopyMemory(nNumberData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDeviceType), sData.cbPhoneNumbers), CopyMemory(m_szCallbackNumber.GetBufferSetLength(STRINGCHARS(sData.cbCallbackNumber)), nInfo.GetData() + (cbData = cbData + sData.cbPhoneNumbers), STRINGBYTES(sData.cbCallbackNumber)), m_nMode = sData.nMode, m_szName.ReleaseBuffer(), m_szDevice.ReleaseBuffer(), m_szDeviceType.ReleaseBuffer(), m_szCallbackNumber.ReleaseBuffer(), m_szPhoneNumbers.RemoveAll(), cbNumber = cbNumbers = 0; cbNumbers < sData.cbPhoneNumbers; cbNumbers += (cbNumber = (m_szPhoneNumbers.GetAt(m_szPhoneNumbers.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szPhoneNumbers.Add((LPCTSTR)(nNumberData.GetData() + cbNumbers));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CServerProfiles

CServerProfiles::CServerProfiles() : CPtrArray()
{
	return;
}

CServerProfiles::~CServerProfiles()
{
	RemoveAll();
}

INT CServerProfiles::Add(CServerProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CServerProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CServerProfileInfo *CServerProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CServerProfileInfo *)CPtrArray::GetAt(nIndex) : (CServerProfileInfo *)NULL);
}

CServerProfileInfo *CServerProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CServerProfileInfo *)CPtrArray::GetAt(nIndex) : (CServerProfileInfo *)NULL);
}

VOID CServerProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;
	CServerProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile))) delete pProfileInfo;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CServerProfiles::Copy(CONST CServerProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CServerProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CServerProfileInfo) != (CServerProfileInfo *)NULL)
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CServerProfiles::Compare(CONST CServerProfiles *pProfiles) CONST
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

BOOL CServerProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfileData;
	CServerProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfileData) && nInfo.Append(nProfileData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CServerProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfileData;
	CServerProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfileData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfileData.GetSize() >= 0; )
		{
			CopyMemory(nProfileData.GetData(), nInfo.GetData() + cbProfiles, nProfileData.GetSize());
			break;
		}
		if ((pProfileInfo = new CServerProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfileData) && Add(pProfileInfo) >= 0) continue;
			delete pProfileInfo;
		}
		break;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CServerProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CServerProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfileInfo->GetName() == pszName) || (bInsert && (((pProfileInfo = GetAt(max(nIndex[0] - 1, 0))) && pProfileInfo->GetName() != pszName && (pProfileInfo = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pProfileInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CServerAddressBook

BOOL CServerAddressBook::SetServerAddressBook(CONST CServerProfiles &pServers)
{
	CByteArray  nServerInfo;

	return(((pServers.GetSize() > 0 && pServers.Map(nServerInfo) && SecureSubKey(QuerySubKey()) && SetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SERVERINFO), REG_BINARY, nServerInfo.GetData(), (INT)nServerInfo.GetSize())) || (!pServers.GetSize() && SetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SERVERINFO)))) ? TRUE : FALSE);
}

BOOL CServerAddressBook::GetServerAddressBook(CServerProfiles &pServers) CONST
{
	INT  nSize;
	DWORD  dwType;
	CByteArray  nServerInfo;

	for (nSize = GetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SERVERINFO)), pServers.RemoveAll(), nServerInfo.SetSize(max(nSize, 0)); nSize > 0 && nServerInfo.GetSize() == nSize; ) break;
	return((!nSize || (GetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SERVERINFO), &dwType, nServerInfo.GetData(), nSize) == nSize  &&  pServers.Unmap(nServerInfo))) ? TRUE : FALSE);
}

BOOL CServerAddressBook::DeleteServerAddressBook()
{
	return DeleteSubKey(QuerySubKey());
}

INT CServerAddressBook::EnumServers(CStringArray &szServers) CONST
{
	INT  nServer;
	INT  nServers;
	CServerProfiles  pServers;
	CServerProfileInfo  *pServerInfo;

	for (nServer = 0, nServers = (GetServerAddressBook(pServers)) ? (INT)pServers.GetSize() : 0, szServers.RemoveAll(); nServer < nServers; nServer++)
	{
		if ((pServerInfo = pServers.GetAt(nServer)))
		{
			szServers.Add(pServerInfo->GetName());
			continue;
		}
	}
	return((INT)szServers.GetSize());
}

BOOL CServerAddressBook::IsEmpty() CONST
{
	CStringArray  szServers;

	return((!EnumServers(szServers)) ? TRUE : FALSE);
}

CString CServerAddressBook::QuerySubKey() CONST
{
	CString  szSubKey;
	CVersionInfo  cVersionInfo;

	szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName();
	szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER) + cVersionInfo.QueryProductName();
	szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_ADDRESSBOOKS);
	return szSubKey;
}

BOOL CServerAddressBook::SecureSubKey(LPCTSTR pszSubKey)
{
	CSecurityDescriptor  cSecurityDescriptor;

	return((cSecurityDescriptor.SetRightsOfSystem(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfOwner(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfAdministrators(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfEveryone(KEY_READ, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE)) ? ((SetMachineInfo(pszSubKey, EMPTYSTRING) && SetMachineSecurity(pszSubKey, cSecurityDescriptor)) ? TRUE : FALSE) : FALSE);
}

BOOL CServerAddressBook::DeleteSubKey(LPCTSTR pszSubKey)
{
	INT  nSubKey;
	INT  nSubKeys;
	CStringArray  szSubKeys;

	for (nSubKey = 0, nSubKeys = EnumMachineSubKeys(pszSubKey, szSubKeys); nSubKey < nSubKeys; nSubKey++)
	{
		if (!DeleteSubKey(CString(CString(pszSubKey) + STRING(IDS_REG_SUBKEYPART_DELIMITER)) + szSubKeys.GetAt(nSubKey))) break;
		continue;
	}
	return((nSubKey == nSubKeys  &&  SetMachineInfo(pszSubKey)) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CUserProfileInfo

CUserProfileInfo::CUserProfileInfo() : CObject()
{
	m_tOfficeHours[0] = USERPROFILE_DEFAULT_OFFICEHOURS_STARTTIME;
	m_tOfficeHours[1] = USERPROFILE_DEFAULT_OFFICEHOURS_STOPTIME;
	m_nOfficeDays = USERPROFILE_WORKDAY_MONDAY | USERPROFILE_WORKDAY_TUESDAY | USERPROFILE_WORKDAY_WEDNESDAY | USERPROFILE_WORKDAY_THURSDAY | USERPROFILE_WORKDAY_FRIDAY;
	m_tHomeHours[0] = m_tHomeHours[1] = 0;
	m_tMission[0] = m_tMission[1] = 0;
	m_tHoliday[0] = m_tHoliday[1] = 0;
	m_bHomeDays = FALSE;
}

CUserProfileInfo::~CUserProfileInfo()
{
	return;
}

VOID CUserProfileInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CUserProfileInfo::GetName() CONST
{
	return m_szName;
}

VOID CUserProfileInfo::SetFirstName(LPCTSTR pszFirstName)
{
	m_szFirstName = pszFirstName;
}

CString CUserProfileInfo::GetFirstName() CONST
{
	return m_szFirstName;
}

VOID CUserProfileInfo::SetAlias(LPCTSTR pszAlias)
{
	m_szAlias = pszAlias;
}

CString CUserProfileInfo::GetAlias() CONST
{
	return m_szAlias;
}

VOID CUserProfileInfo::SetFullName(LPCTSTR pszName, LPCTSTR pszFirstName, LPCTSTR pszAlias)
{
	m_szName = pszName;
	m_szFirstName = pszFirstName;
	m_szAlias = pszAlias;
}

CString CUserProfileInfo::GetFullName() CONST
{
	CString  szName;

	szName.Format((m_szAlias.IsEmpty()) ? STRING(IDS_USERADDRESSBOOK_FULLNAME) : STRING(IDS_USERADDRESSBOOK_FULLALIASNAME), (LPCTSTR)m_szName, (LPCTSTR)m_szFirstName, (LPCTSTR)m_szAlias);
	szName = (!m_szName.IsEmpty() || !m_szFirstName.IsEmpty() || !m_szAlias.IsEmpty()) ? (LPCTSTR)szName : EMPTYSTRING;
	return szName;
}

VOID CUserProfileInfo::SetProfession(LPCTSTR pszProfession)
{
	m_szProfession = pszProfession;
}

CString CUserProfileInfo::GetProfession() CONST
{
	return m_szProfession;
}

VOID CUserProfileInfo::SetNotes(LPCTSTR pszNotes)
{
	m_szNotes = pszNotes;
}

CString CUserProfileInfo::GetNotes() CONST
{
	return m_szNotes;
}

VOID CUserProfileInfo::SetOfficeCompany(LPCTSTR pszCompany)
{
	m_szOfficeCompany = pszCompany;
}

CString CUserProfileInfo::GetOfficeCompany() CONST
{
	return m_szOfficeCompany;
}

VOID CUserProfileInfo::SetOfficeStreet(LPCTSTR pszStreet)
{
	m_szOfficeStreet = pszStreet;
}

CString CUserProfileInfo::GetOfficeStreet() CONST
{
	return m_szOfficeStreet;
}

VOID CUserProfileInfo::SetOfficeCity(LPCTSTR pszCity)
{
	m_szOfficeCity = pszCity;
}

CString CUserProfileInfo::GetOfficeCity() CONST
{
	return m_szOfficeCity;
}

VOID CUserProfileInfo::SetOfficeZipCode(LPCTSTR pszZipCode)
{
	m_szOfficeZipCode = pszZipCode;
}

CString CUserProfileInfo::GetOfficeZipCode() CONST
{
	return m_szOfficeZipCode;
}

VOID CUserProfileInfo::SetOfficeCountry(LPCTSTR pszCountry)
{
	m_szOfficeCountry = pszCountry;
}

CString CUserProfileInfo::GetOfficeCountry() CONST
{
	return m_szOfficeCountry;
}

VOID CUserProfileInfo::SetOfficeDepartment(LPCTSTR pszDepartment)
{
	m_szOfficeDepartment = pszDepartment;
}

CString CUserProfileInfo::GetOfficeDepartment() CONST
{
	return m_szOfficeDepartment;
}

VOID CUserProfileInfo::SetOfficeComputer(LPCTSTR pszComputer)
{
	m_szOfficeComputer = pszComputer;
}

CString CUserProfileInfo::GetOfficeComputer() CONST
{
	return m_szOfficeComputer;
}

VOID CUserProfileInfo::SetOfficePrintProfile(LPCTSTR pszPrintProfile)
{
	m_szOfficePrintProfile = pszPrintProfile;
}

CString CUserProfileInfo::GetOfficePrintProfile() CONST
{
	return m_szOfficePrintProfile;
}

VOID CUserProfileInfo::SetOfficePhone(LPCTSTR pszPhone)
{
	m_szOfficePhone = pszPhone;
}

CString CUserProfileInfo::GetOfficePhone() CONST
{
	return m_szOfficePhone;
}

VOID CUserProfileInfo::SetOfficePager(LPCTSTR pszPager)
{
	m_szOfficePager = pszPager;
}

CString CUserProfileInfo::GetOfficePager() CONST
{
	return m_szOfficePager;
}

VOID CUserProfileInfo::SetOfficeFAX(LPCTSTR pszFAX)
{
	m_szOfficeFAX = pszFAX;
}

CString CUserProfileInfo::GetOfficeFAX() CONST
{
	return m_szOfficeFAX;
}

VOID CUserProfileInfo::SetOfficeEMail(LPCTSTR pszEMail)
{
	m_szOfficeEMail = pszEMail;
}

CString CUserProfileInfo::GetOfficeEMail() CONST
{
	return m_szOfficeEMail;
}

VOID CUserProfileInfo::SetMissionCompany(LPCTSTR pszCompany)
{
	m_szMissionCompany = pszCompany;
}

CString CUserProfileInfo::GetMissionCompany() CONST
{
	return m_szMissionCompany;
}

VOID CUserProfileInfo::SetMissionStreet(LPCTSTR pszStreet)
{
	m_szMissionStreet = pszStreet;
}

CString CUserProfileInfo::GetMissionStreet() CONST
{
	return m_szMissionStreet;
}

VOID CUserProfileInfo::SetMissionCity(LPCTSTR pszCity)
{
	m_szMissionCity = pszCity;
}

CString CUserProfileInfo::GetMissionCity() CONST
{
	return m_szMissionCity;
}

VOID CUserProfileInfo::SetMissionZipCode(LPCTSTR pszZipCode)
{
	m_szMissionZipCode = pszZipCode;
}

CString CUserProfileInfo::GetMissionZipCode() CONST
{
	return m_szMissionZipCode;
}

VOID CUserProfileInfo::SetMissionCountry(LPCTSTR pszCountry)
{
	m_szMissionCountry = pszCountry;
}

CString CUserProfileInfo::GetMissionCountry() CONST
{
	return m_szMissionCountry;
}

VOID CUserProfileInfo::SetMissionDepartment(LPCTSTR pszDepartment)
{
	m_szMissionDepartment = pszDepartment;
}

CString CUserProfileInfo::GetMissionDepartment() CONST
{
	return m_szMissionDepartment;
}

VOID CUserProfileInfo::SetMissionComputer(LPCTSTR pszComputer)
{
	m_szMissionComputer = pszComputer;
}

CString CUserProfileInfo::GetMissionComputer() CONST
{
	return m_szMissionComputer;
}

VOID CUserProfileInfo::SetMissionPrintProfile(LPCTSTR pszPrintProfile)
{
	m_szMissionPrintProfile = pszPrintProfile;
}

CString CUserProfileInfo::GetMissionPrintProfile() CONST
{
	return m_szMissionPrintProfile;
}

VOID CUserProfileInfo::SetMissionPhone(LPCTSTR pszPhone)
{
	m_szMissionPhone = pszPhone;
}

CString CUserProfileInfo::GetMissionPhone() CONST
{
	return m_szMissionPhone;
}

VOID CUserProfileInfo::SetMissionMobile(LPCTSTR pszMobile)
{
	m_szMissionMobile = pszMobile;
}

CString CUserProfileInfo::GetMissionMobile() CONST
{
	return m_szMissionMobile;
}

VOID CUserProfileInfo::SetMissionFAX(LPCTSTR pszFAX)
{
	m_szMissionFAX = pszFAX;
}

CString CUserProfileInfo::GetMissionFAX() CONST
{
	return m_szMissionFAX;
}

VOID CUserProfileInfo::SetMissionEMail(LPCTSTR pszEMail)
{
	m_szMissionEMail = pszEMail;
}

CString CUserProfileInfo::GetMissionEMail() CONST
{
	return m_szMissionEMail;
}

VOID CUserProfileInfo::SetHomeFamilyName(LPCTSTR pszFamilyName)
{
	m_szHomeFamilyName = pszFamilyName;
}

CString CUserProfileInfo::GetHomeFamilyName() CONST
{
	return m_szHomeFamilyName;
}

VOID CUserProfileInfo::SetHomeStreet(LPCTSTR pszStreet)
{
	m_szHomeStreet = pszStreet;
}

CString CUserProfileInfo::GetHomeStreet() CONST
{
	return m_szHomeStreet;
}

VOID CUserProfileInfo::SetHomeCity(LPCTSTR pszCity)
{
	m_szHomeCity = pszCity;
}

CString CUserProfileInfo::GetHomeCity() CONST
{
	return m_szHomeCity;
}

VOID CUserProfileInfo::SetHomeZipCode(LPCTSTR pszZipCode)
{
	m_szHomeZipCode = pszZipCode;
}

CString CUserProfileInfo::GetHomeZipCode() CONST
{
	return m_szHomeZipCode;
}

VOID CUserProfileInfo::SetHomeCountry(LPCTSTR pszCountry)
{
	m_szHomeCountry = pszCountry;
}

CString CUserProfileInfo::GetHomeCountry() CONST
{
	return m_szHomeCountry;
}

VOID CUserProfileInfo::SetHomeComputer(LPCTSTR pszComputer)
{
	m_szHomeComputer = pszComputer;
}

CString CUserProfileInfo::GetHomeComputer() CONST
{
	return m_szHomeComputer;
}

VOID CUserProfileInfo::SetHomePrintProfile(LPCTSTR pszPrintProfile)
{
	m_szHomePrintProfile = pszPrintProfile;
}

CString CUserProfileInfo::GetHomePrintProfile() CONST
{
	return m_szHomePrintProfile;
}

VOID CUserProfileInfo::SetHomePhone(LPCTSTR pszPhone)
{
	m_szHomePhone = pszPhone;
}

CString CUserProfileInfo::GetHomePhone() CONST
{
	return m_szHomePhone;
}

VOID CUserProfileInfo::SetHomeFAX(LPCTSTR pszFAX)
{
	m_szHomeFAX = pszFAX;
}

CString CUserProfileInfo::GetHomeFAX() CONST
{
	return m_szHomeFAX;
}

VOID CUserProfileInfo::SetHomeEMail(LPCTSTR pszEMail)
{
	m_szHomeEMail = pszEMail;
}

CString CUserProfileInfo::GetHomeEMail() CONST
{
	return m_szHomeEMail;
}

VOID CUserProfileInfo::SetHolidayHotel(LPCTSTR pszHotel)
{
	m_szHolidayHotel = pszHotel;
}

CString CUserProfileInfo::GetHolidayHotel() CONST
{
	return m_szHolidayHotel;
}

VOID CUserProfileInfo::SetHolidayStreet(LPCTSTR pszStreet)
{
	m_szHolidayStreet = pszStreet;
}

CString CUserProfileInfo::GetHolidayStreet() CONST
{
	return m_szHolidayStreet;
}

VOID CUserProfileInfo::SetHolidayCity(LPCTSTR pszCity)
{
	m_szHolidayCity = pszCity;
}

CString CUserProfileInfo::GetHolidayCity() CONST
{
	return m_szHolidayCity;
}

VOID CUserProfileInfo::SetHolidayZipCode(LPCTSTR pszZipCode)
{
	m_szHolidayZipCode = pszZipCode;
}

CString CUserProfileInfo::GetHolidayZipCode() CONST
{
	return m_szHolidayZipCode;
}

VOID CUserProfileInfo::SetHolidayCountry(LPCTSTR pszCountry)
{
	m_szHolidayCountry = pszCountry;
}

CString CUserProfileInfo::GetHolidayCountry() CONST
{
	return m_szHolidayCountry;
}

VOID CUserProfileInfo::SetHolidayApartment(LPCTSTR pszApartment)
{
	m_szHolidayApartment = pszApartment;
}

CString CUserProfileInfo::GetHolidayApartment() CONST
{
	return m_szHolidayApartment;
}

VOID CUserProfileInfo::SetHolidayComputer(LPCTSTR pszComputer)
{
	m_szHolidayComputer = pszComputer;
}

CString CUserProfileInfo::GetHolidayComputer() CONST
{
	return m_szHolidayComputer;
}

VOID CUserProfileInfo::SetHolidayPrintProfile(LPCTSTR pszPrintProfile)
{
	m_szHolidayPrintProfile = pszPrintProfile;
}

CString CUserProfileInfo::GetHolidayPrintProfile() CONST
{
	return m_szHolidayPrintProfile;
}

VOID CUserProfileInfo::SetHolidayPhone(LPCTSTR pszPhone)
{
	m_szHolidayPhone = pszPhone;
}

CString CUserProfileInfo::GetHolidayPhone() CONST
{
	return m_szHolidayPhone;
}

VOID CUserProfileInfo::SetHolidayFAX(LPCTSTR pszFAX)
{
	m_szHolidayFAX = pszFAX;
}

CString CUserProfileInfo::GetHolidayFAX() CONST
{
	return m_szHolidayFAX;
}

VOID CUserProfileInfo::SetHolidayEMail(LPCTSTR pszEMail)
{
	m_szHolidayEMail = pszEMail;
}

CString CUserProfileInfo::GetHolidayEMail() CONST
{
	return m_szHolidayEMail;
}

VOID CUserProfileInfo::SetOfficeHours(UINT nDays, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	m_nOfficeDays = nDays;
	m_tOfficeHours[0] = tStartTime;
	m_tOfficeHours[1] = tStopTime;
}

BOOL CUserProfileInfo::GetOfficeHours(UINT &nDays, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	nDays = m_nOfficeDays;
	tStartTime = m_tOfficeHours[0];
	tStopTime = m_tOfficeHours[1];
	return((tStartTime != tStopTime) ? TRUE : FALSE);
}

VOID CUserProfileInfo::SetHomeHours(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime, BOOL bDays)
{
	m_tHomeHours[0] = tStartTime;
	m_tHomeHours[1] = tStopTime;
	m_bHomeDays = bDays;
}

BOOL CUserProfileInfo::GetHomeHours(CTimeSpan &tStartTime, CTimeSpan &tStopTime, BOOL &bDays) CONST
{
	tStartTime = m_tHomeHours[0];
	tStopTime = m_tHomeHours[1];
	bDays = m_bHomeDays;
	return((tStartTime != tStopTime) ? TRUE : FALSE);
}

VOID CUserProfileInfo::SetMission(CONST CTimeKey &tLeaveTime, CONST CTimeKey &tReturnTime)
{
	if (tLeaveTime <= tReturnTime)
	{
		m_tMission[0] = tLeaveTime;
		m_tMission[1] = tReturnTime;
	}
}

BOOL CUserProfileInfo::GetMission(CTimeKey &tLeaveTime, CTimeKey &tReturnTime) CONST
{
	if (m_tMission[0] < m_tMission[1])
	{
		tLeaveTime = m_tMission[0];
		tReturnTime = m_tMission[1];
		return TRUE;
	}
	return FALSE;
}

VOID CUserProfileInfo::SetHoliday(CONST CTimeKey &tLeaveTime, CONST CTimeKey &tReturnTime)
{
	if (tLeaveTime <= tReturnTime)
	{
		m_tHoliday[0] = tLeaveTime;
		m_tHoliday[1] = tReturnTime;
	}
}

BOOL CUserProfileInfo::GetHoliday(CTimeKey &tLeaveTime, CTimeKey &tReturnTime) CONST
{
	if (m_tHoliday[0] < m_tHoliday[1])
	{
		tLeaveTime = m_tHoliday[0];
		tReturnTime = m_tHoliday[1];
		return TRUE;
	}
	return FALSE;
}

VOID CUserProfileInfo::Copy(CONST CUserProfileInfo *pProfileInfo)
{
	m_szName = pProfileInfo->m_szName;
	m_szFirstName = pProfileInfo->m_szFirstName;
	m_szAlias = pProfileInfo->m_szAlias;
	m_szProfession = pProfileInfo->m_szProfession;
	m_szNotes = pProfileInfo->m_szNotes;
	m_szOfficeCompany = pProfileInfo->m_szOfficeCompany;
	m_szOfficeStreet = pProfileInfo->m_szOfficeStreet;
	m_szOfficeCity = pProfileInfo->m_szOfficeCity;
	m_szOfficeZipCode = pProfileInfo->m_szOfficeZipCode;
	m_szOfficeCountry = pProfileInfo->m_szOfficeCountry;
	m_szOfficeDepartment = pProfileInfo->m_szOfficeDepartment;
	m_szOfficeComputer = pProfileInfo->m_szOfficeComputer;
	m_szOfficePrintProfile = pProfileInfo->m_szOfficePrintProfile;
	m_szOfficePhone = pProfileInfo->m_szOfficePhone;
	m_szOfficePager = pProfileInfo->m_szOfficePager;
	m_szOfficeFAX = pProfileInfo->m_szOfficeFAX;
	m_szOfficeEMail = pProfileInfo->m_szOfficeEMail;
	m_szMissionCompany = pProfileInfo->m_szMissionCompany;
	m_szMissionStreet = pProfileInfo->m_szMissionStreet;
	m_szMissionCity = pProfileInfo->m_szMissionCity;
	m_szMissionZipCode = pProfileInfo->m_szMissionZipCode;
	m_szMissionCountry = pProfileInfo->m_szMissionCountry;
	m_szMissionDepartment = pProfileInfo->m_szMissionDepartment;
	m_szMissionComputer = pProfileInfo->m_szMissionComputer;
	m_szMissionPrintProfile = pProfileInfo->m_szMissionPrintProfile;
	m_szMissionPhone = pProfileInfo->m_szMissionPhone;
	m_szMissionMobile = pProfileInfo->m_szMissionMobile;
	m_szMissionFAX = pProfileInfo->m_szMissionFAX;
	m_szMissionEMail = pProfileInfo->m_szMissionEMail;
	m_szHomeFamilyName = pProfileInfo->m_szHomeFamilyName;
	m_szHomeStreet = pProfileInfo->m_szHomeStreet;
	m_szHomeCity = pProfileInfo->m_szHomeCity;
	m_szHomeZipCode = pProfileInfo->m_szHomeZipCode;
	m_szHomeCountry = pProfileInfo->m_szHomeCountry;
	m_szHomeComputer = pProfileInfo->m_szHomeComputer;
	m_szHomePrintProfile = pProfileInfo->m_szHomePrintProfile;
	m_szHomePhone = pProfileInfo->m_szHomePhone;
	m_szHomeFAX = pProfileInfo->m_szHomeFAX;
	m_szHomeEMail = pProfileInfo->m_szHomeEMail;
	m_szHolidayHotel = pProfileInfo->m_szHolidayHotel;
	m_szHolidayStreet = pProfileInfo->m_szHolidayStreet;
	m_szHolidayCity = pProfileInfo->m_szHolidayCity;
	m_szHolidayZipCode = pProfileInfo->m_szHolidayZipCode;
	m_szHolidayCountry = pProfileInfo->m_szHolidayCountry;
	m_szHolidayApartment = pProfileInfo->m_szHolidayApartment;
	m_szHolidayComputer = pProfileInfo->m_szHolidayComputer;
	m_szHolidayPrintProfile = pProfileInfo->m_szHolidayPrintProfile;
	m_szHolidayPhone = pProfileInfo->m_szHolidayPhone;
	m_szHolidayFAX = pProfileInfo->m_szHolidayFAX;
	m_szHolidayEMail = pProfileInfo->m_szHolidayEMail;
	m_tMission[0] = pProfileInfo->m_tMission[0];
	m_tMission[1] = pProfileInfo->m_tMission[1];
	m_tHoliday[0] = pProfileInfo->m_tHoliday[0];
	m_tHoliday[1] = pProfileInfo->m_tHoliday[1];
	m_tOfficeHours[0] = pProfileInfo->m_tOfficeHours[0];
	m_tOfficeHours[1] = pProfileInfo->m_tOfficeHours[1];
	m_tHomeHours[0] = pProfileInfo->m_tHomeHours[0];
	m_tHomeHours[1] = pProfileInfo->m_tHomeHours[1];
	m_nOfficeDays = pProfileInfo->m_nOfficeDays;
	m_bHomeDays = pProfileInfo->m_bHomeDays;
}

BOOL CUserProfileInfo::Compare(CONST CUserProfileInfo *pProfileInfo) CONST
{
	return((pProfileInfo->m_szName == m_szName  &&  pProfileInfo->m_szFirstName == m_szFirstName  &&  pProfileInfo->m_szAlias == m_szAlias  &&  pProfileInfo->m_szProfession == m_szProfession  &&  pProfileInfo->m_szNotes == m_szNotes  &&
		pProfileInfo->m_szOfficeCompany == m_szOfficeCompany  &&  pProfileInfo->m_szOfficeStreet == m_szOfficeStreet  &&  pProfileInfo->m_szOfficeCity == m_szOfficeCity  &&  pProfileInfo->m_szOfficeZipCode == m_szOfficeZipCode  &&  pProfileInfo->m_szOfficeCountry == m_szOfficeCountry  &&  pProfileInfo->m_szOfficeDepartment == m_szOfficeDepartment  &&  pProfileInfo->m_szOfficeComputer == m_szOfficeComputer  &&  pProfileInfo->m_szOfficePrintProfile == m_szOfficePrintProfile  &&  pProfileInfo->m_szOfficePhone == m_szOfficePhone  &&  pProfileInfo->m_szOfficePager == m_szOfficePager  &&  pProfileInfo->m_szOfficeFAX == m_szOfficeFAX  &&  pProfileInfo->m_szOfficeEMail == m_szOfficeEMail  &&
		pProfileInfo->m_szMissionCompany == m_szMissionCompany  &&  pProfileInfo->m_szMissionStreet == m_szMissionStreet  &&  pProfileInfo->m_szMissionCity == m_szMissionCity  &&  pProfileInfo->m_szMissionZipCode == m_szMissionZipCode  &&  pProfileInfo->m_szMissionCountry == m_szMissionCountry  &&  pProfileInfo->m_szMissionDepartment == m_szMissionDepartment  &&  pProfileInfo->m_szMissionComputer == m_szMissionComputer  &&  pProfileInfo->m_szMissionPrintProfile == m_szMissionPrintProfile  &&  pProfileInfo->m_szMissionPhone == m_szMissionPhone  &&  pProfileInfo->m_szMissionMobile == m_szMissionMobile  &&  pProfileInfo->m_szMissionFAX == m_szMissionFAX  &&  pProfileInfo->m_szMissionEMail == m_szMissionEMail  &&
		pProfileInfo->m_szHomeFamilyName == m_szHomeFamilyName  &&  pProfileInfo->m_szHomeStreet == m_szHomeStreet  &&  pProfileInfo->m_szHomeCity == m_szHomeCity  &&  pProfileInfo->m_szHomeZipCode == m_szHomeZipCode  &&  pProfileInfo->m_szHomeCountry == m_szHomeCountry  &&  pProfileInfo->m_szHomeComputer == m_szHomeComputer  &&  pProfileInfo->m_szHomePrintProfile == m_szHomePrintProfile  &&  pProfileInfo->m_szHomePhone == m_szHomePhone  &&  pProfileInfo->m_szHomeFAX == m_szHomeFAX  &&  pProfileInfo->m_szHomeEMail == m_szHomeEMail  &&
		pProfileInfo->m_szHolidayHotel == m_szHolidayHotel  &&  pProfileInfo->m_szHolidayStreet == m_szHolidayStreet  &&  pProfileInfo->m_szHolidayCity == m_szHolidayCity  &&  pProfileInfo->m_szHolidayZipCode == m_szHolidayZipCode  &&  pProfileInfo->m_szHolidayCountry == m_szHolidayCountry  &&  pProfileInfo->m_szHolidayApartment == m_szHolidayApartment  &&  pProfileInfo->m_szHolidayComputer == m_szHolidayComputer  &&  pProfileInfo->m_szHolidayPrintProfile == m_szHolidayPrintProfile  &&  pProfileInfo->m_szHolidayPhone == m_szHolidayPhone  &&  pProfileInfo->m_szHolidayFAX == m_szHolidayFAX  &&  pProfileInfo->m_szHolidayEMail == m_szHolidayEMail  &&
		pProfileInfo->m_tMission[0] == m_tMission[0] && pProfileInfo->m_tMission[1] == m_tMission[1] && pProfileInfo->m_tHoliday[0] == m_tHoliday[0] && pProfileInfo->m_tHoliday[1] == m_tHoliday[1] && pProfileInfo->m_tOfficeHours[0] == m_tOfficeHours[0] && pProfileInfo->m_tOfficeHours[1] == m_tOfficeHours[1] && pProfileInfo->m_tHomeHours[0] == m_tHomeHours[0] && pProfileInfo->m_tHomeHours[1] == m_tHomeHours[1] && pProfileInfo->m_nOfficeDays == m_nOfficeDays  &&  pProfileInfo->m_bHomeDays == m_bHomeDays) ? TRUE : FALSE);
}

BOOL CUserProfileInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFirstName = (m_szFirstName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAlias = (m_szAlias.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfession = (m_szProfession.GetLength() + 1)*sizeof(TCHAR);
	sData.cbNotes = (m_szNotes.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeCompany = (m_szOfficeCompany.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeStreet = (m_szOfficeStreet.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeCity = (m_szOfficeCity.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeZipCode = (m_szOfficeZipCode.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeCountry = (m_szOfficeCountry.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeDepartment = (m_szOfficeDepartment.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeComputer = (m_szOfficeComputer.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficePrintProfile = (m_szOfficePrintProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficePhone = (m_szOfficePhone.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficePager = (m_szOfficePager.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeFAX = (m_szOfficeFAX.GetLength() + 1)*sizeof(TCHAR);
	sData.cbOfficeEMail = (m_szOfficeEMail.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionCompany = (m_szMissionCompany.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionStreet = (m_szMissionStreet.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionCity = (m_szMissionCity.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionZipCode = (m_szMissionZipCode.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionCountry = (m_szMissionCountry.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionDepartment = (m_szMissionDepartment.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionComputer = (m_szMissionComputer.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionPrintProfile = (m_szMissionPrintProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionPhone = (m_szMissionPhone.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionMobile = (m_szMissionMobile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionFAX = (m_szMissionFAX.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMissionEMail = (m_szMissionEMail.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeFamilyName = (m_szHomeFamilyName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeStreet = (m_szHomeStreet.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeCity = (m_szHomeCity.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeZipCode = (m_szHomeZipCode.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeCountry = (m_szHomeCountry.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeComputer = (m_szHomeComputer.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomePrintProfile = (m_szHomePrintProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomePhone = (m_szHomePhone.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeFAX = (m_szHomeFAX.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHomeEMail = (m_szHomeEMail.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayHotel = (m_szHolidayHotel.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayStreet = (m_szHolidayStreet.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayCity = (m_szHolidayCity.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayZipCode = (m_szHolidayZipCode.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayCountry = (m_szHolidayCountry.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayApartment = (m_szHolidayApartment.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayComputer = (m_szHolidayComputer.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayPrintProfile = (m_szHolidayPrintProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayPhone = (m_szHolidayPhone.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayFAX = (m_szHolidayFAX.GetLength() + 1)*sizeof(TCHAR);
	sData.cbHolidayEMail = (m_szHolidayEMail.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbFirstName + sData.cbAlias + sData.cbProfession + sData.cbNotes + sData.cbOfficeCompany + sData.cbOfficeStreet + sData.cbOfficeCity + sData.cbOfficeZipCode + sData.cbOfficeCountry + sData.cbOfficeDepartment + sData.cbOfficeComputer + sData.cbOfficePrintProfile + sData.cbOfficePhone + sData.cbOfficePager + sData.cbOfficeFAX + sData.cbOfficeEMail + sData.cbMissionCompany + sData.cbMissionStreet + sData.cbMissionCity + sData.cbMissionZipCode + sData.cbMissionCountry + sData.cbMissionDepartment + sData.cbMissionComputer + sData.cbMissionPrintProfile + sData.cbMissionPhone + sData.cbMissionMobile + sData.cbMissionFAX + sData.cbMissionEMail + sData.cbHomeFamilyName + sData.cbHomeStreet + sData.cbHomeCity + sData.cbHomeZipCode + sData.cbHomeCountry + sData.cbHomeComputer + sData.cbHomePrintProfile + sData.cbHomePhone + sData.cbHomeFAX + sData.cbHomeEMail + sData.cbHolidayHotel + sData.cbHolidayStreet + sData.cbHolidayCity + sData.cbHolidayZipCode + sData.cbHolidayCountry + sData.cbHolidayApartment + sData.cbHolidayComputer + sData.cbHolidayPrintProfile + sData.cbHolidayPhone + sData.cbHolidayFAX + sData.cbHolidayEMail)), sData.nOfficeDays = m_nOfficeDays, sData.tOfficeHours[0] = m_tOfficeHours[0].GetTotalSeconds(), sData.tOfficeHours[1] = m_tOfficeHours[1].GetTotalSeconds(), sData.bHomeDays = m_bHomeDays, sData.tHomeHours[0] = m_tHomeHours[0].GetTotalSeconds(), sData.tHomeHours[1] = m_tHomeHours[1].GetTotalSeconds(), sData.tMission[0] = m_tMission[0].GetTime(), sData.tMission[1] = m_tMission[1].GetTime(), sData.tHoliday[0] = m_tHoliday[0].GetTime(), sData.tHoliday[1] = m_tHoliday[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szFirstName, sData.cbFirstName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFirstName), (LPCTSTR)m_szAlias, sData.cbAlias);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAlias), (LPCTSTR)m_szProfession, sData.cbProfession);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProfession), (LPCTSTR)m_szNotes, sData.cbNotes);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbNotes), (LPCTSTR)m_szOfficeCompany, sData.cbOfficeCompany);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeCompany), (LPCTSTR)m_szOfficeStreet, sData.cbOfficeStreet);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeStreet), (LPCTSTR)m_szOfficeCity, sData.cbOfficeCity);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeCity), (LPCTSTR)m_szOfficeZipCode, sData.cbOfficeZipCode);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeZipCode), (LPCTSTR)m_szOfficeCountry, sData.cbOfficeCountry);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeCountry), (LPCTSTR)m_szOfficeDepartment, sData.cbOfficeDepartment);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeDepartment), (LPCTSTR)m_szOfficeComputer, sData.cbOfficeComputer);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeComputer), (LPCTSTR)m_szOfficePrintProfile, sData.cbOfficePrintProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficePrintProfile), (LPCTSTR)m_szOfficePhone, sData.cbOfficePhone);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficePhone), (LPCTSTR)m_szOfficePager, sData.cbOfficePager);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficePager), (LPCTSTR)m_szOfficeFAX, sData.cbOfficeFAX);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeFAX), (LPCTSTR)m_szOfficeEMail, sData.cbOfficeEMail);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbOfficeEMail), (LPCTSTR)m_szMissionCompany, sData.cbMissionCompany);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionCompany), (LPCTSTR)m_szMissionStreet, sData.cbMissionStreet);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionStreet), (LPCTSTR)m_szMissionCity, sData.cbMissionCity);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionCity), (LPCTSTR)m_szMissionZipCode, sData.cbMissionZipCode);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionZipCode), (LPCTSTR)m_szMissionCountry, sData.cbMissionCountry);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionCountry), (LPCTSTR)m_szMissionDepartment, sData.cbMissionDepartment);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionDepartment), (LPCTSTR)m_szMissionComputer, sData.cbMissionComputer);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionComputer), (LPCTSTR)m_szMissionPrintProfile, sData.cbMissionPrintProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionPrintProfile), (LPCTSTR)m_szMissionPhone, sData.cbMissionPhone);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionPhone), (LPCTSTR)m_szMissionMobile, sData.cbMissionMobile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionMobile), (LPCTSTR)m_szMissionFAX, sData.cbMissionFAX);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionFAX), (LPCTSTR)m_szMissionEMail, sData.cbMissionEMail);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMissionEMail), (LPCTSTR)m_szHomeFamilyName, sData.cbHomeFamilyName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeFamilyName), (LPCTSTR)m_szHomeStreet, sData.cbHomeStreet);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeStreet), (LPCTSTR)m_szHomeCity, sData.cbHomeCity);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeCity), (LPCTSTR)m_szHomeZipCode, sData.cbHomeZipCode);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeZipCode), (LPCTSTR)m_szHomeCountry, sData.cbHomeCountry);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeCountry), (LPCTSTR)m_szHomeComputer, sData.cbHomeComputer);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeComputer), (LPCTSTR)m_szHomePrintProfile, sData.cbHomePrintProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomePrintProfile), (LPCTSTR)m_szHomePhone, sData.cbHomePhone);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomePhone), (LPCTSTR)m_szHomeFAX, sData.cbHomeFAX);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeFAX), (LPCTSTR)m_szHomeEMail, sData.cbHomeEMail);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHomeEMail), (LPCTSTR)m_szHolidayHotel, sData.cbHolidayHotel);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayHotel), (LPCTSTR)m_szHolidayStreet, sData.cbHolidayStreet);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayStreet), (LPCTSTR)m_szHolidayCity, sData.cbHolidayCity);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayCity), (LPCTSTR)m_szHolidayZipCode, sData.cbHolidayZipCode);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayZipCode), (LPCTSTR)m_szHolidayCountry, sData.cbHolidayCountry);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayCountry), (LPCTSTR)m_szHolidayApartment, sData.cbHolidayApartment);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayApartment), (LPCTSTR)m_szHolidayComputer, sData.cbHolidayComputer);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayComputer), (LPCTSTR)m_szHolidayPrintProfile, sData.cbHolidayPrintProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayPrintProfile), (LPCTSTR)m_szHolidayPhone, sData.cbHolidayPhone);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayPhone), (LPCTSTR)m_szHolidayFAX, sData.cbHolidayFAX);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHolidayFAX), (LPCTSTR)m_szHolidayEMail, sData.cbHolidayEMail);
		return TRUE;
	}
	return FALSE;
}

BOOL CUserProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbFirstName + sData.cbAlias + sData.cbProfession + sData.cbNotes + sData.cbOfficeCompany + sData.cbOfficeStreet + sData.cbOfficeCity + sData.cbOfficeZipCode + sData.cbOfficeCountry + sData.cbOfficeDepartment + sData.cbOfficeComputer + sData.cbOfficePrintProfile + sData.cbOfficePhone + sData.cbOfficePager + sData.cbOfficeFAX + sData.cbOfficeEMail + sData.cbMissionCompany + sData.cbMissionStreet + sData.cbMissionCity + sData.cbMissionZipCode + sData.cbMissionCountry + sData.cbMissionDepartment + sData.cbMissionComputer + sData.cbMissionPrintProfile + sData.cbMissionPhone + sData.cbMissionMobile + sData.cbMissionFAX + sData.cbMissionEMail + sData.cbHomeFamilyName + sData.cbHomeStreet + sData.cbHomeCity + sData.cbHomeZipCode + sData.cbHomeCountry + sData.cbHomeComputer + sData.cbHomePrintProfile + sData.cbHomePhone + sData.cbHomeFAX + sData.cbHomeEMail + sData.cbHolidayHotel + sData.cbHolidayStreet + sData.cbHolidayCity + sData.cbHolidayZipCode + sData.cbHolidayCountry + sData.cbHolidayApartment + sData.cbHolidayComputer + sData.cbHolidayPrintProfile + sData.cbHolidayPhone + sData.cbHolidayFAX + sData.cbHolidayEMail && sData.cbName > 0 && sData.cbFirstName > 0 && sData.cbAlias > 0 && sData.cbProfession > 0 && sData.cbNotes > 0 && sData.cbOfficeCompany > 0 && sData.cbOfficeStreet > 0 && sData.cbOfficeCity > 0 && sData.cbOfficeZipCode > 0 && sData.cbOfficeCountry > 0 && sData.cbOfficeDepartment > 0 && sData.cbOfficeComputer > 0 && sData.cbOfficePrintProfile > 0 && sData.cbOfficePhone > 0 && sData.cbOfficePager > 0 && sData.cbOfficeFAX > 0 && sData.cbOfficeEMail > 0 && sData.cbMissionCompany > 0 && sData.cbMissionStreet > 0 && sData.cbMissionCity > 0 && sData.cbMissionZipCode > 0 && sData.cbMissionCountry > 0 && sData.cbMissionDepartment > 0 && sData.cbMissionComputer > 0 && sData.cbMissionPrintProfile > 0 && sData.cbMissionPhone > 0 && sData.cbMissionMobile > 0 && sData.cbMissionFAX > 0 && sData.cbMissionEMail > 0 && sData.cbHomeFamilyName > 0 && sData.cbHomeStreet > 0 && sData.cbHomeCity > 0 && sData.cbHomeZipCode > 0 && sData.cbHomeCountry > 0 && sData.cbHomeComputer > 0 && sData.cbHomePrintProfile > 0 && sData.cbHomePhone > 0 && sData.cbHomeFAX > 0 && sData.cbHomeEMail > 0 && sData.cbHolidayHotel > 0 && sData.cbHolidayStreet > 0 && sData.cbHolidayCity > 0 && sData.cbHolidayZipCode > 0 && sData.cbHolidayCountry > 0 && sData.cbHolidayApartment > 0 && sData.cbHolidayComputer > 0 && sData.cbHolidayPrintProfile > 0 && sData.cbHolidayPhone > 0 && sData.cbHolidayFAX > 0 && sData.cbHolidayEMail > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szFirstName.GetBufferSetLength(STRINGCHARS(sData.cbFirstName)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbFirstName));
		CopyMemory(m_szAlias.GetBufferSetLength(STRINGCHARS(sData.cbAlias)), nInfo.GetData() + (cbData = cbData + sData.cbFirstName), STRINGBYTES(sData.cbAlias));
		CopyMemory(m_szProfession.GetBufferSetLength(STRINGCHARS(sData.cbProfession)), nInfo.GetData() + (cbData = cbData + sData.cbAlias), STRINGBYTES(sData.cbProfession));
		CopyMemory(m_szNotes.GetBufferSetLength(STRINGCHARS(sData.cbNotes)), nInfo.GetData() + (cbData = cbData + sData.cbProfession), STRINGBYTES(sData.cbNotes));
		CopyMemory(m_szOfficeCompany.GetBufferSetLength(STRINGCHARS(sData.cbOfficeCompany)), nInfo.GetData() + (cbData = cbData + sData.cbNotes), STRINGBYTES(sData.cbOfficeCompany));
		CopyMemory(m_szOfficeStreet.GetBufferSetLength(STRINGCHARS(sData.cbOfficeStreet)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeCompany), STRINGBYTES(sData.cbOfficeStreet));
		CopyMemory(m_szOfficeCity.GetBufferSetLength(STRINGCHARS(sData.cbOfficeCity)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeStreet), STRINGBYTES(sData.cbOfficeCity));
		CopyMemory(m_szOfficeZipCode.GetBufferSetLength(STRINGCHARS(sData.cbOfficeZipCode)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeCity), STRINGBYTES(sData.cbOfficeZipCode));
		CopyMemory(m_szOfficeCountry.GetBufferSetLength(STRINGCHARS(sData.cbOfficeCountry)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeZipCode), STRINGBYTES(sData.cbOfficeCountry));
		CopyMemory(m_szOfficeDepartment.GetBufferSetLength(STRINGCHARS(sData.cbOfficeDepartment)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeCountry), STRINGBYTES(sData.cbOfficeDepartment));
		CopyMemory(m_szOfficeComputer.GetBufferSetLength(STRINGCHARS(sData.cbOfficeComputer)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeDepartment), STRINGBYTES(sData.cbOfficeComputer));
		CopyMemory(m_szOfficePrintProfile.GetBufferSetLength(STRINGCHARS(sData.cbOfficePrintProfile)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeComputer), STRINGBYTES(sData.cbOfficePrintProfile));
		CopyMemory(m_szOfficePhone.GetBufferSetLength(STRINGCHARS(sData.cbOfficePhone)), nInfo.GetData() + (cbData = cbData + sData.cbOfficePrintProfile), STRINGBYTES(sData.cbOfficePhone));
		CopyMemory(m_szOfficePager.GetBufferSetLength(STRINGCHARS(sData.cbOfficePager)), nInfo.GetData() + (cbData = cbData + sData.cbOfficePhone), STRINGBYTES(sData.cbOfficePager));
		CopyMemory(m_szOfficeFAX.GetBufferSetLength(STRINGCHARS(sData.cbOfficeFAX)), nInfo.GetData() + (cbData = cbData + sData.cbOfficePager), STRINGBYTES(sData.cbOfficeFAX));
		CopyMemory(m_szOfficeEMail.GetBufferSetLength(STRINGCHARS(sData.cbOfficeEMail)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeFAX), STRINGBYTES(sData.cbOfficeEMail));
		CopyMemory(m_szMissionCompany.GetBufferSetLength(STRINGCHARS(sData.cbMissionCompany)), nInfo.GetData() + (cbData = cbData + sData.cbOfficeEMail), STRINGBYTES(sData.cbMissionCompany));
		CopyMemory(m_szMissionStreet.GetBufferSetLength(STRINGCHARS(sData.cbMissionStreet)), nInfo.GetData() + (cbData = cbData + sData.cbMissionCompany), STRINGBYTES(sData.cbMissionStreet));
		CopyMemory(m_szMissionCity.GetBufferSetLength(STRINGCHARS(sData.cbMissionCity)), nInfo.GetData() + (cbData = cbData + sData.cbMissionStreet), STRINGBYTES(sData.cbMissionCity));
		CopyMemory(m_szMissionZipCode.GetBufferSetLength(STRINGCHARS(sData.cbMissionZipCode)), nInfo.GetData() + (cbData = cbData + sData.cbMissionCity), STRINGBYTES(sData.cbMissionZipCode));
		CopyMemory(m_szMissionCountry.GetBufferSetLength(STRINGCHARS(sData.cbMissionCountry)), nInfo.GetData() + (cbData = cbData + sData.cbMissionZipCode), STRINGBYTES(sData.cbMissionCountry));
		CopyMemory(m_szMissionDepartment.GetBufferSetLength(STRINGCHARS(sData.cbMissionDepartment)), nInfo.GetData() + (cbData = cbData + sData.cbMissionCountry), STRINGBYTES(sData.cbMissionDepartment));
		CopyMemory(m_szMissionComputer.GetBufferSetLength(STRINGCHARS(sData.cbMissionComputer)), nInfo.GetData() + (cbData = cbData + sData.cbMissionDepartment), STRINGBYTES(sData.cbMissionComputer));
		CopyMemory(m_szMissionPrintProfile.GetBufferSetLength(STRINGCHARS(sData.cbMissionPrintProfile)), nInfo.GetData() + (cbData = cbData + sData.cbMissionComputer), STRINGBYTES(sData.cbMissionPrintProfile));
		CopyMemory(m_szMissionPhone.GetBufferSetLength(STRINGCHARS(sData.cbMissionPhone)), nInfo.GetData() + (cbData = cbData + sData.cbMissionPrintProfile), STRINGBYTES(sData.cbMissionPhone));
		CopyMemory(m_szMissionMobile.GetBufferSetLength(STRINGCHARS(sData.cbMissionMobile)), nInfo.GetData() + (cbData = cbData + sData.cbMissionPhone), STRINGBYTES(sData.cbMissionMobile));
		CopyMemory(m_szMissionFAX.GetBufferSetLength(STRINGCHARS(sData.cbMissionFAX)), nInfo.GetData() + (cbData = cbData + sData.cbMissionMobile), STRINGBYTES(sData.cbMissionFAX));
		CopyMemory(m_szMissionEMail.GetBufferSetLength(STRINGCHARS(sData.cbMissionEMail)), nInfo.GetData() + (cbData = cbData + sData.cbMissionFAX), STRINGBYTES(sData.cbMissionEMail));
		CopyMemory(m_szHomeFamilyName.GetBufferSetLength(STRINGCHARS(sData.cbHomeFamilyName)), nInfo.GetData() + (cbData = cbData + sData.cbMissionEMail), STRINGBYTES(sData.cbHomeFamilyName));
		CopyMemory(m_szHomeStreet.GetBufferSetLength(STRINGCHARS(sData.cbHomeStreet)), nInfo.GetData() + (cbData = cbData + sData.cbHomeFamilyName), STRINGBYTES(sData.cbHomeStreet));
		CopyMemory(m_szHomeCity.GetBufferSetLength(STRINGCHARS(sData.cbHomeCity)), nInfo.GetData() + (cbData = cbData + sData.cbHomeStreet), STRINGBYTES(sData.cbHomeCity));
		CopyMemory(m_szHomeZipCode.GetBufferSetLength(STRINGCHARS(sData.cbHomeZipCode)), nInfo.GetData() + (cbData = cbData + sData.cbHomeCity), STRINGBYTES(sData.cbHomeZipCode));
		CopyMemory(m_szHomeCountry.GetBufferSetLength(STRINGCHARS(sData.cbHomeCountry)), nInfo.GetData() + (cbData = cbData + sData.cbHomeZipCode), STRINGBYTES(sData.cbHomeCountry));
		CopyMemory(m_szHomeComputer.GetBufferSetLength(STRINGCHARS(sData.cbHomeComputer)), nInfo.GetData() + (cbData = cbData + sData.cbHomeCountry), STRINGBYTES(sData.cbHomeComputer));
		CopyMemory(m_szHomePrintProfile.GetBufferSetLength(STRINGCHARS(sData.cbHomePrintProfile)), nInfo.GetData() + (cbData = cbData + sData.cbHomeComputer), STRINGBYTES(sData.cbHomePrintProfile));
		CopyMemory(m_szHomePhone.GetBufferSetLength(STRINGCHARS(sData.cbHomePhone)), nInfo.GetData() + (cbData = cbData + sData.cbHomePrintProfile), STRINGBYTES(sData.cbHomePhone));
		CopyMemory(m_szHomeFAX.GetBufferSetLength(STRINGCHARS(sData.cbHomeFAX)), nInfo.GetData() + (cbData = cbData + sData.cbHomePhone), STRINGBYTES(sData.cbHomeFAX));
		CopyMemory(m_szHomeEMail.GetBufferSetLength(STRINGCHARS(sData.cbHomeEMail)), nInfo.GetData() + (cbData = cbData + sData.cbHomeFAX), STRINGBYTES(sData.cbHomeEMail));
		CopyMemory(m_szHolidayHotel.GetBufferSetLength(STRINGCHARS(sData.cbHolidayHotel)), nInfo.GetData() + (cbData = cbData + sData.cbHomeEMail), STRINGBYTES(sData.cbHolidayHotel));
		CopyMemory(m_szHolidayStreet.GetBufferSetLength(STRINGCHARS(sData.cbHolidayStreet)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayHotel), STRINGBYTES(sData.cbHolidayStreet));
		CopyMemory(m_szHolidayCity.GetBufferSetLength(STRINGCHARS(sData.cbHolidayCity)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayStreet), STRINGBYTES(sData.cbHolidayCity));
		CopyMemory(m_szHolidayZipCode.GetBufferSetLength(STRINGCHARS(sData.cbHolidayZipCode)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayCity), STRINGBYTES(sData.cbHolidayZipCode));
		CopyMemory(m_szHolidayCountry.GetBufferSetLength(STRINGCHARS(sData.cbHolidayCountry)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayZipCode), STRINGBYTES(sData.cbHolidayCountry));
		CopyMemory(m_szHolidayApartment.GetBufferSetLength(STRINGCHARS(sData.cbHolidayApartment)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayCountry), STRINGBYTES(sData.cbHolidayApartment));
		CopyMemory(m_szHolidayComputer.GetBufferSetLength(STRINGCHARS(sData.cbHolidayComputer)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayApartment), STRINGBYTES(sData.cbHolidayComputer));
		CopyMemory(m_szHolidayPrintProfile.GetBufferSetLength(STRINGCHARS(sData.cbHolidayPrintProfile)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayComputer), STRINGBYTES(sData.cbHolidayPrintProfile));
		CopyMemory(m_szHolidayPhone.GetBufferSetLength(STRINGCHARS(sData.cbHolidayPhone)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayPrintProfile), STRINGBYTES(sData.cbHolidayPhone));
		CopyMemory(m_szHolidayFAX.GetBufferSetLength(STRINGCHARS(sData.cbHolidayFAX)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayPhone), STRINGBYTES(sData.cbHolidayFAX));
		CopyMemory(m_szHolidayEMail.GetBufferSetLength(STRINGCHARS(sData.cbHolidayEMail)), nInfo.GetData() + (cbData = cbData + sData.cbHolidayFAX), STRINGBYTES(sData.cbHolidayEMail));
		m_nOfficeDays = sData.nOfficeDays;
		m_tOfficeHours[0] = sData.tOfficeHours[0];
		m_tOfficeHours[1] = sData.tOfficeHours[1];
		m_bHomeDays = sData.bHomeDays;
		m_tHomeHours[0] = sData.tHomeHours[0];
		m_tHomeHours[1] = sData.tHomeHours[1];
		m_tMission[0] = sData.tMission[0];
		m_tMission[1] = sData.tMission[1];
		m_tHoliday[0] = sData.tHoliday[0];
		m_tHoliday[1] = sData.tHoliday[1];
		m_szName.ReleaseBuffer();
		m_szFirstName.ReleaseBuffer();
		m_szAlias.ReleaseBuffer();
		m_szProfession.ReleaseBuffer();
		m_szNotes.ReleaseBuffer();
		m_szOfficeCompany.ReleaseBuffer();
		m_szOfficeStreet.ReleaseBuffer();
		m_szOfficeCity.ReleaseBuffer();
		m_szOfficeZipCode.ReleaseBuffer();
		m_szOfficeCountry.ReleaseBuffer();
		m_szOfficeDepartment.ReleaseBuffer();
		m_szOfficeComputer.ReleaseBuffer();
		m_szOfficePrintProfile.ReleaseBuffer();
		m_szOfficePhone.ReleaseBuffer();
		m_szOfficePager.ReleaseBuffer();
		m_szOfficeFAX.ReleaseBuffer();
		m_szOfficeEMail.ReleaseBuffer();
		m_szMissionCompany.ReleaseBuffer();
		m_szMissionStreet.ReleaseBuffer();
		m_szMissionCity.ReleaseBuffer();
		m_szMissionZipCode.ReleaseBuffer();
		m_szMissionCountry.ReleaseBuffer();
		m_szMissionDepartment.ReleaseBuffer();
		m_szMissionComputer.ReleaseBuffer();
		m_szMissionPrintProfile.ReleaseBuffer();
		m_szMissionPhone.ReleaseBuffer();
		m_szMissionMobile.ReleaseBuffer();
		m_szMissionFAX.ReleaseBuffer();
		m_szMissionEMail.ReleaseBuffer();
		m_szHomeFamilyName.ReleaseBuffer();
		m_szHomeStreet.ReleaseBuffer();
		m_szHomeCity.ReleaseBuffer();
		m_szHomeZipCode.ReleaseBuffer();
		m_szHomeCountry.ReleaseBuffer();
		m_szHomeComputer.ReleaseBuffer();
		m_szHomePrintProfile.ReleaseBuffer();
		m_szHomePhone.ReleaseBuffer();
		m_szHomeFAX.ReleaseBuffer();
		m_szHomeEMail.ReleaseBuffer();
		m_szHolidayHotel.ReleaseBuffer();
		m_szHolidayStreet.ReleaseBuffer();
		m_szHolidayCity.ReleaseBuffer();
		m_szHolidayZipCode.ReleaseBuffer();
		m_szHolidayCountry.ReleaseBuffer();
		m_szHolidayApartment.ReleaseBuffer();
		m_szHolidayComputer.ReleaseBuffer();
		m_szHolidayPrintProfile.ReleaseBuffer();
		m_szHolidayPhone.ReleaseBuffer();
		m_szHolidayFAX.ReleaseBuffer();
		m_szHolidayEMail.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CUserProfiles

CUserProfiles::CUserProfiles() : CPtrArray()
{
	return;
}

CUserProfiles::~CUserProfiles()
{
	RemoveAll();
}

INT CUserProfiles::Add(CUserProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetFullName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CUserProfiles::Find(LPCTSTR pszFullName) CONST
{
	return FindIndex(pszFullName);
}

CUserProfileInfo *CUserProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CUserProfileInfo *)CPtrArray::GetAt(nIndex) : (CUserProfileInfo *)NULL);
}

CUserProfileInfo *CUserProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CUserProfileInfo *)CPtrArray::GetAt(nIndex) : (CUserProfileInfo *)NULL);
}

VOID CUserProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;
	CUserProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile))) delete pProfileInfo;
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CUserProfiles::Copy(CONST CUserProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CUserProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CUserProfileInfo) != (CUserProfileInfo *)NULL)
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CUserProfiles::Compare(CONST CUserProfiles *pProfiles) CONST
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

BOOL CUserProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfileData;
	CUserProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfileData) && nInfo.Append(nProfileData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CUserProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfileData;
	CUserProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfileData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfileData.GetSize() >= 0; )
		{
			CopyMemory(nProfileData.GetData(), nInfo.GetData() + cbProfiles, nProfileData.GetSize());
			break;
		}
		if ((pProfileInfo = new CUserProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfileData) && Add(pProfileInfo) >= 0) continue;
			delete pProfileInfo;
		}
		break;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CUserProfiles::FindIndex(LPCTSTR pszFullName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CUserProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetFullName() <= pszFullName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfileInfo->GetFullName() == pszFullName) || (bInsert && (((pProfileInfo = GetAt(max(nIndex[0] - 1, 0))) && pProfileInfo->GetFullName() != pszFullName && (pProfileInfo = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pProfileInfo->GetFullName() != pszFullName) || !GetSize()))) && lstrlen(pszFullName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CUserAddressBook

BOOL CUserAddressBook::SetUserAddressBook(CONST CUserProfiles &pUsers)
{
	CByteArray  nUserInfo;

	return(((pUsers.GetSize() > 0 && pUsers.Map(nUserInfo) && SecureSubKey(QuerySubKey()) && SetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_USERINFO), REG_BINARY, nUserInfo.GetData(), (INT)nUserInfo.GetSize())) || (!pUsers.GetSize() && SetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_USERINFO)))) ? TRUE : FALSE);
}

BOOL CUserAddressBook::GetUserAddressBook(CUserProfiles &pUsers) CONST
{
	INT  nSize;
	DWORD  dwType;
	CByteArray  nUserInfo;

	for (nSize = GetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_USERINFO)), pUsers.RemoveAll(), nUserInfo.SetSize(max(nSize, 0)); nSize > 0 && nUserInfo.GetSize() == nSize; ) break;
	return((!nSize || (GetMachineInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_USERINFO), &dwType, nUserInfo.GetData(), nSize) == nSize  &&  pUsers.Unmap(nUserInfo))) ? TRUE : FALSE);
}

BOOL CUserAddressBook::DeleteUserAddressBook()
{
	return DeleteSubKey(QuerySubKey());
}

INT CUserAddressBook::EnumUsers(CStringArray &szUsers) CONST
{
	INT  nUser;
	INT  nUsers;
	CUserProfiles  pUsers;
	CUserProfileInfo  *pUserInfo;

	for (nUser = 0, nUsers = (GetUserAddressBook(pUsers)) ? (INT)pUsers.GetSize() : 0, szUsers.RemoveAll(); nUser < nUsers; nUser++)
	{
		if ((pUserInfo = pUsers.GetAt(nUser)))
		{
			szUsers.Add(pUserInfo->GetName());
			continue;
		}
	}
	return((INT)szUsers.GetSize());
}

BOOL CUserAddressBook::IsEmpty() CONST
{
	CStringArray  szUsers;

	return((!EnumUsers(szUsers)) ? TRUE : FALSE);
}

CString CUserAddressBook::QuerySubKey() CONST
{
	CString  szSubKey;
	CVersionInfo  cVersionInfo;

	szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName();
	szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER) + cVersionInfo.QueryProductName();
	szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_ADDRESSBOOKS);
	return szSubKey;
}

BOOL CUserAddressBook::SecureSubKey(LPCTSTR pszSubKey)
{
	CSecurityDescriptor  cSecurityDescriptor;

	return((cSecurityDescriptor.SetRightsOfSystem(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfOwner(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfAdministrators(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfEveryone(KEY_READ, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE)) ? ((SetMachineInfo(pszSubKey, EMPTYSTRING) && SetMachineSecurity(pszSubKey, cSecurityDescriptor)) ? TRUE : FALSE) : FALSE);
}

BOOL CUserAddressBook::DeleteSubKey(LPCTSTR pszSubKey)
{
	INT  nSubKey;
	INT  nSubKeys;
	CStringArray  szSubKeys;

	for (nSubKey = 0, nSubKeys = EnumMachineSubKeys(pszSubKey, szSubKeys); nSubKey < nSubKeys; nSubKey++)
	{
		if (!DeleteSubKey(CString(CString(pszSubKey) + STRING(IDS_REG_SUBKEYPART_DELIMITER)) + szSubKeys.GetAt(nSubKey))) break;
		continue;
	}
	return((nSubKey == nSubKeys  &&  SetMachineInfo(pszSubKey)) ? TRUE : FALSE);
}
