// BOOKS.H : Books Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the books related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/08 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __BOOKS_H__
#define __BOOKS_H__

#include "timekey.h"
#include "registry.h"


/////////////////////////////////////////////////////////////////////////////
// CServerProfileInfo

// Specify the server profile modes
#define SERVERPROFILE_ACCESS_VPN   (1<<0)
#define SERVERPROFILE_ACCESS_PHONE   (1<<1)
#define SERVERPROFILE_BEHAVIOR_CALLBACK   (1<<2)
#define SERVERPROFILE_BEHAVIOR_TRYALLNUMBERS   (1<<3)
#define SERVERPROFILE_BEHAVIOR_MODEMSPEAKER   (1<<4)
#define SERVERPROFILE_BEHAVIOR_SOFTWARECOMPRESSION   (1<<5)

class AFX_EXT_CLASS CServerProfileInfo : public CObject
{
	// Construction
public:
	CServerProfileInfo();
	~CServerProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDevice;
		INT  cbDeviceType;
		INT  cbPhoneNumbers;
		INT  cbCallbackNumber;
		UINT  nMode;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szDevice;
	CString  m_szDeviceType;
	CString  m_szCallbackNumber;
	CStringArray  m_szPhoneNumbers;
	UINT  m_nMode;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetMode(UINT nMode);
	UINT GetMode() CONST;
	VOID SetDeviceInfo(LPCTSTR pszDevice, LPCTSTR pszType);
	VOID GetDeviceInfo(CString &szDevice, CString &szType) CONST;
	VOID SetPhoneNumbers(CONST CStringArray &szNumbers);
	INT GetPhoneNumbers(CStringArray &szNumbers) CONST;
	VOID SetCallbackNumber(LPCTSTR pszNumber);
	CString GetCallbackNumber() CONST;

	VOID Copy(CONST CServerProfileInfo *pProfileInfo);
	BOOL Compare(CONST CServerProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CServerProfiles

class AFX_EXT_CLASS CServerProfiles : public CPtrArray
{
	// Construction
public:
	CServerProfiles();
	~CServerProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CServerProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszName) CONST;

	CServerProfileInfo *GetAt(INT nIndex) CONST;
	CServerProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CServerProfiles *pProfiles);
	BOOL Compare(CONST CServerProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CServerAddressBook

class AFX_EXT_CLASS CServerAddressBook : public CRegistry
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL SetServerAddressBook(CONST CServerProfiles &pServers);
	BOOL GetServerAddressBook(CServerProfiles &pServers) CONST;
	BOOL DeleteServerAddressBook();

	INT EnumServers(CStringArray &szServers) CONST;

	BOOL IsEmpty() CONST;

private:
	CString QuerySubKey() CONST;
	BOOL SecureSubKey(LPCTSTR pszSubKey);
	BOOL DeleteSubKey(LPCTSTR pszSubKey);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserProfileInfo

// Specify the user profile office working day identifiers
#define USERPROFILE_WORKDAY_MONDAY   (1<<0)
#define USERPROFILE_WORKDAY_TUESDAY   (1<<1)
#define USERPROFILE_WORKDAY_WEDNESDAY   (1<<2)
#define USERPROFILE_WORKDAY_THURSDAY   (1<<3)
#define USERPROFILE_WORKDAY_FRIDAY   (1<<4)
#define USERPROFILE_WORKDAY_SATURDAY   (1<<5)
#define USERPROFILE_WORKDAY_SUNDAY   (1<<6)
// Specify the default user profile settings
#define USERPROFILE_DEFAULT_OFFICEHOURS_STARTTIME   (9*SECONDSPERHOUR)
#define USERPROFILE_DEFAULT_OFFICEHOURS_STOPTIME   (17*SECONDSPERHOUR)
#define USERPROFILE_DEFAULT_HOMEHOURS_STARTTIME   (17*SECONDSPERHOUR)
#define USERPROFILE_DEFAULT_HOMEHOURS_STOPTIME   (9*SECONDSPERHOUR)

class AFX_EXT_CLASS CUserProfileInfo : public CObject
{
	// Construction
public:
	CUserProfileInfo();
	~CUserProfileInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbFirstName;
		INT  cbAlias;
		INT  cbProfession;
		INT  cbNotes;
		INT  cbOfficeCompany;
		INT  cbOfficeStreet;
		INT  cbOfficeCity;
		INT  cbOfficeZipCode;
		INT  cbOfficeCountry;
		INT  cbOfficeDepartment;
		INT  cbOfficeComputer;
		INT  cbOfficePrintProfile;
		INT  cbOfficePhone;
		INT  cbOfficePager;
		INT  cbOfficeFAX;
		INT  cbOfficeEMail;
		INT  cbMissionCompany;
		INT  cbMissionStreet;
		INT  cbMissionCity;
		INT  cbMissionZipCode;
		INT  cbMissionCountry;
		INT  cbMissionDepartment;
		INT  cbMissionComputer;
		INT  cbMissionPrintProfile;
		INT  cbMissionPhone;
		INT  cbMissionMobile;
		INT  cbMissionFAX;
		INT  cbMissionEMail;
		INT  cbHomeFamilyName;
		INT  cbHomeStreet;
		INT  cbHomeCity;
		INT  cbHomeZipCode;
		INT  cbHomeCountry;
		INT  cbHomeComputer;
		INT  cbHomePrintProfile;
		INT  cbHomePhone;
		INT  cbHomeFAX;
		INT  cbHomeEMail;
		INT  cbHolidayHotel;
		INT  cbHolidayStreet;
		INT  cbHolidayCity;
		INT  cbHolidayZipCode;
		INT  cbHolidayCountry;
		INT  cbHolidayApartment;
		INT  cbHolidayComputer;
		INT  cbHolidayPrintProfile;
		INT  cbHolidayPhone;
		INT  cbHolidayFAX;
		INT  cbHolidayEMail;
		UINT  nOfficeDays;
		BOOL  bHomeDays;
		TIMEKEY  tOfficeHours[2];
		TIMEKEY  tHomeHours[2];
		TIMEKEY  tMission[2];
		TIMEKEY  tHoliday[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szFirstName;
	CString  m_szAlias;
	CString  m_szProfession;
	CString  m_szNotes;
	CString  m_szOfficeCompany;
	CString  m_szOfficeStreet;
	CString  m_szOfficeCity;
	CString  m_szOfficeZipCode;
	CString  m_szOfficeCountry;
	CString  m_szOfficeDepartment;
	CString  m_szOfficeComputer;
	CString  m_szOfficePrintProfile;
	CString  m_szOfficePhone;
	CString  m_szOfficePager;
	CString  m_szOfficeFAX;
	CString  m_szOfficeEMail;
	CString  m_szMissionCompany;
	CString  m_szMissionStreet;
	CString  m_szMissionCity;
	CString  m_szMissionZipCode;
	CString  m_szMissionCountry;
	CString  m_szMissionDepartment;
	CString  m_szMissionComputer;
	CString  m_szMissionPrintProfile;
	CString  m_szMissionPhone;
	CString  m_szMissionMobile;
	CString  m_szMissionFAX;
	CString  m_szMissionEMail;
	CString  m_szHomeFamilyName;
	CString  m_szHomeStreet;
	CString  m_szHomeCity;
	CString  m_szHomeZipCode;
	CString  m_szHomeCountry;
	CString  m_szHomeComputer;
	CString  m_szHomePrintProfile;
	CString  m_szHomePhone;
	CString  m_szHomeFAX;
	CString  m_szHomeEMail;
	CString  m_szHolidayHotel;
	CString  m_szHolidayStreet;
	CString  m_szHolidayCity;
	CString  m_szHolidayZipCode;
	CString  m_szHolidayCountry;
	CString  m_szHolidayApartment;
	CString  m_szHolidayComputer;
	CString  m_szHolidayPrintProfile;
	CString  m_szHolidayPhone;
	CString  m_szHolidayFAX;
	CString  m_szHolidayEMail;
	CTimeKey  m_tMission[2];
	CTimeKey  m_tHoliday[2];
	CTimeSpan  m_tOfficeHours[2];
	CTimeSpan  m_tHomeHours[2];
	UINT  m_nOfficeDays;
	BOOL  m_bHomeDays;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetFirstName(LPCTSTR pszFirstName);
	CString GetFirstName() CONST;
	VOID SetAlias(LPCTSTR pszAlias);
	CString GetAlias() CONST;
	VOID SetFullName(LPCTSTR pszName, LPCTSTR pszFirstName, LPCTSTR pszAlias);
	CString GetFullName() CONST;
	VOID SetProfession(LPCTSTR pszProfession);
	CString GetProfession() CONST;
	VOID SetNotes(LPCTSTR pszNotes);
	CString GetNotes() CONST;

	VOID SetOfficeCompany(LPCTSTR pszCompany);
	CString GetOfficeCompany() CONST;
	VOID SetOfficeStreet(LPCTSTR pszStreet);
	CString GetOfficeStreet() CONST;
	VOID SetOfficeCity(LPCTSTR pszCity);
	CString GetOfficeCity() CONST;
	VOID SetOfficeZipCode(LPCTSTR pszZipCode);
	CString GetOfficeZipCode() CONST;
	VOID SetOfficeCountry(LPCTSTR pszCountry);
	CString GetOfficeCountry() CONST;
	VOID SetOfficeDepartment(LPCTSTR pszDepartment);
	CString GetOfficeDepartment() CONST;
	VOID SetOfficeComputer(LPCTSTR pszComputer);
	CString GetOfficeComputer() CONST;
	VOID SetOfficePrintProfile(LPCTSTR pszPrintProfile);
	CString GetOfficePrintProfile() CONST;
	VOID SetOfficePhone(LPCTSTR pszPhone);
	CString GetOfficePhone() CONST;
	VOID SetOfficePager(LPCTSTR pszPager);
	CString GetOfficePager() CONST;
	VOID SetOfficeFAX(LPCTSTR pszFAX);
	CString GetOfficeFAX() CONST;
	VOID SetOfficeEMail(LPCTSTR pszEMail);
	CString GetOfficeEMail() CONST;
	VOID SetMissionCompany(LPCTSTR pszCompany);
	CString GetMissionCompany() CONST;
	VOID SetMissionStreet(LPCTSTR pszStreet);
	CString GetMissionStreet() CONST;
	VOID SetMissionCity(LPCTSTR pszCity);
	CString GetMissionCity() CONST;
	VOID SetMissionZipCode(LPCTSTR pszZipCode);
	CString GetMissionZipCode() CONST;
	VOID SetMissionCountry(LPCTSTR pszCountry);
	CString GetMissionCountry() CONST;
	VOID SetMissionDepartment(LPCTSTR pszDepartment);
	CString GetMissionDepartment() CONST;
	VOID SetMissionComputer(LPCTSTR pszComputer);
	CString GetMissionComputer() CONST;
	VOID SetMissionPrintProfile(LPCTSTR pszPrintProfile);
	CString GetMissionPrintProfile() CONST;
	VOID SetMissionPhone(LPCTSTR pszPhone);
	CString GetMissionPhone() CONST;
	VOID SetMissionMobile(LPCTSTR pszMobile);
	CString GetMissionMobile() CONST;
	VOID SetMissionFAX(LPCTSTR pszFAX);
	CString GetMissionFAX() CONST;
	VOID SetMissionEMail(LPCTSTR pszEMail);
	CString GetMissionEMail() CONST;
	VOID SetHomeFamilyName(LPCTSTR pszFamilyName);
	CString GetHomeFamilyName() CONST;
	VOID SetHomeStreet(LPCTSTR pszStreet);
	CString GetHomeStreet() CONST;
	VOID SetHomeCity(LPCTSTR pszCity);
	CString GetHomeCity() CONST;
	VOID SetHomeZipCode(LPCTSTR pszZipCode);
	CString GetHomeZipCode() CONST;
	VOID SetHomeCountry(LPCTSTR pszCountry);
	CString GetHomeCountry() CONST;
	VOID SetHomeComputer(LPCTSTR pszComputer);
	CString GetHomeComputer() CONST;
	VOID SetHomePrintProfile(LPCTSTR pszPrintProfile);
	CString GetHomePrintProfile() CONST;
	VOID SetHomePhone(LPCTSTR pszPhone);
	CString GetHomePhone() CONST;
	VOID SetHomeFAX(LPCTSTR pszFAX);
	CString GetHomeFAX() CONST;
	VOID SetHomeEMail(LPCTSTR pszEMail);
	CString GetHomeEMail() CONST;
	VOID SetHolidayHotel(LPCTSTR pszHotel);
	CString GetHolidayHotel() CONST;
	VOID SetHolidayStreet(LPCTSTR pszStreet);
	CString GetHolidayStreet() CONST;
	VOID SetHolidayCity(LPCTSTR pszCity);
	CString GetHolidayCity() CONST;
	VOID SetHolidayZipCode(LPCTSTR pszZipCode);
	CString GetHolidayZipCode() CONST;
	VOID SetHolidayCountry(LPCTSTR pszCountry);
	CString GetHolidayCountry() CONST;
	VOID SetHolidayApartment(LPCTSTR pszApartment);
	CString GetHolidayApartment() CONST;
	VOID SetHolidayComputer(LPCTSTR pszComputer);
	CString GetHolidayComputer() CONST;
	VOID SetHolidayPrintProfile(LPCTSTR pszPrintProfile);
	CString GetHolidayPrintProfile() CONST;
	VOID SetHolidayPhone(LPCTSTR pszPhone);
	CString GetHolidayPhone() CONST;
	VOID SetHolidayFAX(LPCTSTR pszFAX);
	CString GetHolidayFAX() CONST;
	VOID SetHolidayEMail(LPCTSTR pszEMail);
	CString GetHolidayEMail() CONST;

	VOID SetOfficeHours(UINT nDays, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetOfficeHours(UINT &nDays, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	VOID SetHomeHours(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime, BOOL bDays);
	BOOL GetHomeHours(CTimeSpan &tStartTime, CTimeSpan &tStopTime, BOOL &bDays) CONST;
	VOID SetMission(CONST CTimeKey &tLeaveTime, CONST CTimeKey &tReturnTime);
	BOOL GetMission(CTimeKey &tLeaveTime, CTimeKey &tReturnTime) CONST;
	VOID SetHoliday(CONST CTimeKey &tLeaveTime, CONST CTimeKey &tReturnTime);
	BOOL GetHoliday(CTimeKey &tLeaveTime, CTimeKey &tReturnTime) CONST;

	VOID Copy(CONST CUserProfileInfo *pProfileInfo);
	BOOL Compare(CONST CUserProfileInfo *pProfileInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserProfiles

class AFX_EXT_CLASS CUserProfiles : public CPtrArray
{
	// Construction
public:
	CUserProfiles();
	~CUserProfiles();

	// Attributes
public:

	// Operations
public:
	INT Add(CUserProfileInfo *pProfileInfo);

	INT Find(LPCTSTR pszFullName) CONST;

	CUserProfileInfo *GetAt(INT nIndex) CONST;
	CUserProfileInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CUserProfiles *pProfiles);
	BOOL Compare(CONST CUserProfiles *pProfiles) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszFullName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBook

class AFX_EXT_CLASS CUserAddressBook : public CRegistry
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL SetUserAddressBook(CONST CUserProfiles &pUsers);
	BOOL GetUserAddressBook(CUserProfiles &pUsers) CONST;
	BOOL DeleteUserAddressBook();

	INT EnumUsers(CStringArray &szUsers) CONST;

	BOOL IsEmpty() CONST;

private:
	CString QuerySubKey() CONST;
	BOOL SecureSubKey(LPCTSTR pszSubKey);
	BOOL DeleteSubKey(LPCTSTR pszSubKey);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __BOOKS_H__
