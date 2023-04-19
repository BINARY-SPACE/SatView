// TIMEKEY.H : Timekey Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the timekey related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/07/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TIMEKEY_H__
#define __TIMEKEY_H__


/////////////////////////////////////////////////////////////////////////////
// CTimeKey

// Specify the time key related types
typedef __time64_t   TIMEKEY, *PTIMEKEY, *LPTIMEKEY;
// Specify the time key related enumerators
enum Month { January = 1, February, March, April, May, June, July, August, September, October, November, December };
enum Weekday { Sunday = 1, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
// Specify the time key related limits
#define MIN_TIMEKEY   (CTime(0).GetTime())
#define MAX_TIMEKEY   (CTime(3000,12,31,23,59,59).GetTime())
// Specify the time key related identifiers
#define MONTHSPERYEAR   12
#define DAYSPERWEEK   7
#define HOURSPERDAY   24
#define MINUTESPERHOUR   60
#define SECONDSPERMINUTE   60
#define SECONDSPERHOUR  (MINUTESPERHOUR*SECONDSPERMINUTE)
#define SECONDSPERDAY   (HOURSPERDAY*SECONDSPERHOUR)
#define SECONDSPERWEEK   (DAYSPERWEEK*SECONDSPERDAY)
#define MINUTESPERDAY   (HOURSPERDAY*MINUTESPERHOUR)
#define MINUTESPERWEEK   (DAYSPERWEEK*MINUTESPERDAY)
#define HOURSPERWEEK   (DAYSPERWEEK*HOURSPERDAY)
#define HOURS(x)   (x*SECONDSPERHOUR)

class AFX_EXT_CLASS CTimeKey : public CTime
{
	// Construction
public:
	CTimeKey();
	CTimeKey(TIMEKEY tTimeKey);
	CTimeKey(CONST CTimeKey &tTimeKey);
	CTimeKey(CONST FILETIME &tTimeKey);
	CTimeKey(CONST SYSTEMTIME &tTimeKey);
	CTimeKey(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMinute, INT nSecond);
	CTimeKey(INT nYear, INT nDayofYear, INT nHour, INT nMinute, INT nSecond);

	// Attributes
public:

	// Operations
public:
	VOID SetTime(TIMEKEY tTimeKey);
	VOID SetTime(CONST CTimeKey &tTimeKey);
	VOID SetTime(CONST FILETIME &tTimeKey);
	VOID SetTime(CONST SYSTEMTIME &tTimeKey);
	TIMEKEY GetTime() CONST;
	BOOL GetTime(CTimeKey &tTimeKey) CONST;
	BOOL GetTime(FILETIME &tTimeKey) CONST;
	BOOL GetTime(SYSTEMTIME &tTimeKey) CONST;

	INT GetDayOfYear() CONST;
	BOOL IsLeapYear() CONST;

	TIMEKEY GetBias() CONST;

	CString Format() CONST;
	CString Format(INT nFormatID) CONST;
	CString Format(LPCTSTR pszFormat) CONST;
	CString FormatGmt() CONST;
	CString FormatGmt(INT nFormatID) CONST;
	CString FormatGmt(LPCTSTR pszFormat) CONST;

	TIMEKEY Parse(LPCTSTR pszTimeKey) CONST;
	TIMEKEY Parse(LPCTSTR pszTimeKey, LPCTSTR pszFormat) CONST;
	TIMEKEY ParseGmt(LPCTSTR pszTimeKey) CONST;
	TIMEKEY ParseGmt(LPCTSTR pszTimeKey, LPCTSTR pszFormat) CONST;

	INT EnumSubFormatLimits(INT nSubFormatID) CONST;
	INT EnumSubFormatLimits(INT nSubFormatID, BOOL bUTC) CONST;
	INT EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames) CONST;
	INT EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames, BOOL bUTC) CONST;

protected:
	CString FormatTime(LPCTSTR pszFormat, BOOL bUTC, BOOL bNegative) CONST;

	TIMEKEY ParseTime(LPCTSTR pszTimeKey, LPCTSTR pszFormat, BOOL bUTC, BOOL &bNegative) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTimeKeyArray

class AFX_EXT_CLASS CTimeKeyArray : public CArray<CTimeKey>
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL Compare(CONST CTimeKeyArray &tTimeKeys) CONST;

	INT Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTimeTag

// Specify the time tag related types
typedef __time64_t   TIMETAG, *PTIMETAG, *LPTIMETAG;
// Specify the time tag related limits
#define MIN_TIMETAG   (1000000*(TIMETAG) MIN_TIMEKEY)
#define MAX_TIMETAG   (1000000*(TIMETAG) MAX_TIMEKEY)

class AFX_EXT_CLASS CTimeTag : public CTimeKey
{
	// Construction
public:
	CTimeTag();
	CTimeTag(TIMETAG tTimeTag);
	CTimeTag(CONST CTimeKey &tTimeTag);
	CTimeTag(CONST CTimeTag &tTimeTag);
	CTimeTag(CONST FILETIME &tTimeTag);
	CTimeTag(CONST SYSTEMTIME &tTimeTag);
	CTimeTag(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond);
	CTimeTag(INT nYear, INT nDayofYear, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond);

	// Attributes
protected:
	INT  m_nMicroSeconds;

	// Operations
public:
	VOID SetTime(TIMETAG tTimeTag);
	VOID SetTime(CONST CTimeKey &tTimeTag);
	VOID SetTime(CONST CTimeTag &tTimeTag);
	VOID SetTime(CONST FILETIME &tTimeTag);
	VOID SetTime(CONST SYSTEMTIME &tTimeTag);
	TIMETAG GetTime() CONST;
	BOOL GetTime(CTimeKey &tTimeTag) CONST;
	BOOL GetTime(CTimeTag &tTimeTag) CONST;
	BOOL GetTime(FILETIME &tTimeTag) CONST;
	BOOL GetTime(SYSTEMTIME &tTimeTag) CONST;

	TIMEKEY GetTimeInSeconds() CONST;
	INT GetMilliSeconds() CONST;
	INT GetMicroSeconds() CONST;

	TIMETAG GetBias() CONST;

	CString Format() CONST;
	CString Format(INT nFormatID) CONST;
	CString Format(LPCTSTR pszFormat) CONST;
	CString FormatGmt() CONST;
	CString FormatGmt(INT nFormatID) CONST;
	CString FormatGmt(LPCTSTR pszFormat) CONST;

	TIMETAG Parse(LPCTSTR pszTimeTag) CONST;
	TIMETAG Parse(LPCTSTR pszTimeTag, LPCTSTR pszFormat) CONST;
	TIMETAG ParseGmt(LPCTSTR pszTimeTag) CONST;
	TIMETAG ParseGmt(LPCTSTR pszTimeTag, LPCTSTR pszFormat) CONST;

	INT EnumSubFormatLimits(INT nSubFormatID) CONST;
	INT EnumSubFormatLimits(INT nSubFormatID, BOOL bUTC) CONST;
	INT EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames) CONST;
	INT EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames, BOOL bUTC) CONST;

public:
	CTimeTag &operator=(TIMETAG tTimeTag);
	CTimeTag &operator=(CONST CTimeTag &tTimeTag);
	CTimeTag &operator+=(TIMETAG tTimeSpan);
	CTimeTag &operator-=(TIMETAG tTimeSpan);
	CTimeTag operator+(TIMETAG tTimeSpan) CONST;
	CTimeTag operator+(CONST CTimeTag &tTimeTag) CONST;
	CTimeTag operator-(TIMETAG tTimeSpan) CONST;
	CTimeTag operator-(CONST CTimeTag &tTimeTag) CONST;
	BOOL operator==(CONST CTimeTag &tTimeTag) CONST;
	BOOL operator!=(CONST CTimeTag &tTimeTag) CONST;
	BOOL operator<=(CONST CTimeTag &tTimeTag) CONST;
	BOOL operator>=(CONST CTimeTag &tTimeTag) CONST;
	BOOL operator<(CONST CTimeTag &tTimeTag) CONST;
	BOOL operator>(CONST CTimeTag &tTimeTag) CONST;

protected:
	CString FormatTime(LPCTSTR pszFormat, BOOL bUTC) CONST;

	TIMETAG ParseTime(LPCTSTR pszTimeTag, LPCTSTR pszFormat, BOOL bUTC) CONST;

private:
	TIMETAG ConvertTime() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTimeTagArray

class AFX_EXT_CLASS CTimeTagArray : public CArray<CTimeTag>
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL Compare(CONST CTimeTagArray &tTimeTags) CONST;

	INT Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TIMEKEY_H__
