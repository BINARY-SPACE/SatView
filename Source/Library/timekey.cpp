// TIMEKEY.CPP : TimeKey Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the timekey related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/07/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTimeKey

CTimeKey::CTimeKey() : CTime(CTime::GetCurrentTime())
{
	return;
}
CTimeKey::CTimeKey(TIMEKEY tTimeKey) : CTime(tTimeKey)
{
	return;
}
CTimeKey::CTimeKey(CONST CTimeKey &tTimeKey) : CTime(tTimeKey.GetTime())
{
	return;
}
CTimeKey::CTimeKey(CONST FILETIME &tTimeKey) : CTime(tTimeKey)
{
	return;
}
CTimeKey::CTimeKey(CONST SYSTEMTIME &tTimeKey) : CTime(tTimeKey)
{
	return;
}
CTimeKey::CTimeKey(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMinute, INT nSecond) : CTime(nYear, nMonth, nDay, nHour, nMinute, nSecond)
{
	return;
}
CTimeKey::CTimeKey(INT nYear, INT nDayofYear, INT nHour, INT nMinute, INT nSecond) : CTime()
{
	TIMEKEY  tTimeKey;
	struct tm  tTime;

	tTime.tm_year = nYear - 1900;
	tTime.tm_mon = 0;
	tTime.tm_mday = 1;
	tTime.tm_yday = 0;
	tTime.tm_hour = nHour;
	tTime.tm_min = nMinute;
	tTime.tm_sec = nSecond;
	tTime.tm_wday = 0;
	tTime.tm_isdst = -1;
	SetTime(((tTimeKey = _mktime64(&tTime) + (nDayofYear - 1)*SECONDSPERDAY) < MIN_TIMEKEY || tTimeKey > MAX_TIMEKEY) ? min(max(tTimeKey, MIN_TIMEKEY), MAX_TIMEKEY) : tTimeKey);
}

VOID CTimeKey::SetTime(TIMEKEY tTimeKey)
{
	*this = tTimeKey;
}
VOID CTimeKey::SetTime(CONST CTimeKey &tTimeKey)
{
	*this = tTimeKey.GetTime();
}
VOID CTimeKey::SetTime(CONST FILETIME &tTimeKey)
{
	*this = CTime(tTimeKey).GetTime();
}
VOID CTimeKey::SetTime(CONST SYSTEMTIME &tTimeKey)
{
	*this = CTime(tTimeKey).GetTime();
}

TIMEKEY CTimeKey::GetTime() CONST
{
	return CTime::GetTime();
}
BOOL CTimeKey::GetTime(CTimeKey &tTimeKey) CONST
{
	TIMEKEY  tTime;

	if ((tTime = CTime::GetTime()) >= 0)
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CTimeKey::GetTime(FILETIME &tTimeKey) CONST
{
	TIMETAG  dwTime;
	FILETIME  tTime;
	SYSTEMTIME  sTime;

	if (GetTime(sTime) && SystemTimeToFileTime(&sTime, &tTime) && LocalFileTimeToFileTime(&tTime, &tTimeKey))
	{
		dwTime = 1000000 * ((((TIMETAG)tTimeKey.dwHighDateTime << 32) + (TIMETAG)tTimeKey.dwLowDateTime) / 1000000);
		tTimeKey.dwHighDateTime = (DWORD)((dwTime >> 32) & 0xFFFFFFFF);
		tTimeKey.dwLowDateTime = (DWORD)(dwTime & 0xFFFFFFFF);
		return TRUE;
	}
	return FALSE;
}
BOOL CTimeKey::GetTime(SYSTEMTIME &tTimeKey) CONST
{
	return GetAsSystemTime(tTimeKey);
}

INT CTimeKey::GetDayOfYear() CONST
{
	struct tm  time;

	return GetLocalTm(&time)->tm_yday + 1;
}

BOOL CTimeKey::IsLeapYear() CONST
{
	INT  nYear;

	return(((!((nYear = GetYear()) % 4) && nYear % 100) || !(nYear % 400)) ? TRUE : FALSE);
}

TIMEKEY CTimeKey::GetBias() CONST
{
	__time64_t  tTime;
	struct tm  tmTime;
	struct tm  tmUTCTime;

	for (GetLocalTm(&tmTime); (tTime = _mktime64(&tmTime)) >= SECONDSPERDAY; )
	{
		GetGmtTm(&tmUTCTime);
		tmUTCTime.tm_isdst = tmTime.tm_isdst;
		return _mktime64(&tmUTCTime) - tTime;
	}
	return CTimeKey(CTime(abs(GetTime())).GetYear() + 1, CTime(abs(GetTime())).GetMonth(), CTime(abs(GetTime())).GetDay(), CTime(abs(GetTime())).GetHour(), CTime(abs(GetTime())).GetMinute(), CTime(abs(GetTime())).GetSecond()).GetBias();
}

CString CTimeKey::Format() CONST
{
	return FormatTime(STRING(IDS_TIMEKEY_FORMAT), FALSE, FALSE);
}
CString CTimeKey::Format(INT nFormatID) CONST
{
	return FormatTime(((nFormatID >= MINTIMEKEYFORMAT  &&  nFormatID <= MAXTIMEKEYFORMAT) || (nFormatID >= MINTIMEKEYSUBFORMAT  &&  nFormatID <= MAXTIMEKEYSUBFORMAT)) ? STRING(nFormatID) : STRING(IDS_TIMEKEY_FORMAT), FALSE, FALSE);
}
CString CTimeKey::Format(LPCTSTR pszFormat) CONST
{
	return FormatTime(pszFormat, FALSE, FALSE);
}

CString CTimeKey::FormatGmt() CONST
{
	return FormatTime(STRING(IDS_TIMEKEY_FORMAT), TRUE, FALSE);
}
CString CTimeKey::FormatGmt(INT nFormatID) CONST
{
	return FormatTime(((nFormatID >= MINTIMEKEYFORMAT  &&  nFormatID <= MAXTIMEKEYFORMAT) || (nFormatID >= MINTIMEKEYSUBFORMAT  &&  nFormatID <= MAXTIMEKEYSUBFORMAT)) ? STRING(nFormatID) : STRING(IDS_TIMEKEY_FORMAT), TRUE, FALSE);
}
CString CTimeKey::FormatGmt(LPCTSTR pszFormat) CONST
{
	return FormatTime(pszFormat, TRUE, FALSE);
}

TIMEKEY CTimeKey::Parse(LPCTSTR pszTimeKey) CONST
{
	BOOL  bNegative;

	return ParseTime(pszTimeKey, STRING(IDS_TIMEKEY_FORMAT), FALSE, bNegative);
}
TIMEKEY CTimeKey::Parse(LPCTSTR pszTimeKey, LPCTSTR pszFormat) CONST
{
	BOOL  bNegative;

	return ParseTime(pszTimeKey, pszFormat, FALSE, bNegative);
}

TIMEKEY CTimeKey::ParseGmt(LPCTSTR pszTimeKey) CONST
{
	BOOL  bNegative;

	return ParseTime(pszTimeKey, STRING(IDS_TIMEKEY_FORMAT), TRUE, bNegative);
}
TIMEKEY CTimeKey::ParseGmt(LPCTSTR pszTimeKey, LPCTSTR pszFormat) CONST
{
	BOOL  bNegative;

	return ParseTime(pszTimeKey, pszFormat, TRUE, bNegative);
}

INT CTimeKey::EnumSubFormatLimits(INT nSubFormatID) CONST
{
	INT  nDays;
	LONG  nLimits;
	TIMEKEY  tTime;

	for (tTime = abs(GetTime()); nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAR; )
	{
		nLimits = MAKELONG(CTimeKey(MIN_TIMEKEY).GetYear(), CTimeKey(MAX_TIMEKEY).GetYear());
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAROFCENTURY)
	{
		nLimits = MAKELONG(0, 99);
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTH || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHMNEMONIC)
	{
		nLimits = MAKELONG(January, December);
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)
	{
		nLimits = MAKELONG(_ttoi(CTimeKey(CTimeKey(tTime).GetYear(), January, 1, 0, 0, 0).Format(STRING(nSubFormatID))), _ttoi(CTimeKey(CTimeKey(tTime).GetYear(), December, 31, 0, 0, 0).Format(STRING(nSubFormatID))));
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)
	{
		nLimits = MAKELONG(_ttoi(CTimeKey(CTimeKey(tTime).GetYear(), January, 1, 0, 0, 0).Format(STRING(nSubFormatID))), _ttoi(CTimeKey(CTimeKey(tTime).GetYear(), December, 31, 0, 0, 0).Format(STRING(nSubFormatID))));
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFMONTH)
	{
		for (tTime = CTimeKey(CTimeKey(tTime).GetYear(), CTimeKey(tTime).GetMonth(), (nDays = 28), 0, 0, 0).GetTime() + SECONDSPERDAY; CTimeKey(tTime).GetMonth() == GetMonth(); nDays++)
		{
			tTime += SECONDSPERDAY;
			continue;
		}
		return MAKELONG(1, nDays);
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC)
	{
		nLimits = MAKELONG(1, DAYSPERWEEK);
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR)
	{
		nLimits = MAKELONG(1, HOURSPERDAY / 2);
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR)
	{
		nLimits = MAKELONG(0, HOURSPERDAY - 1);
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE)
	{
		nLimits = MAKELONG(0, MINUTESPERHOUR - 1);
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND)
	{
		nLimits = MAKELONG(0, SECONDSPERMINUTE - 1);
		return nLimits;
	}
	return 0;
}
INT CTimeKey::EnumSubFormatLimits(INT nSubFormatID, BOOL bUTC) CONST
{
	return((bUTC) ? CTimeKey(GetTime() + GetBias()).EnumSubFormatLimits(nSubFormatID) : EnumSubFormatLimits(nSubFormatID));
}
INT CTimeKey::EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames) CONST
{
	INT  nYear;
	INT  nMonth;
	INT  nWeekDay;
	INT  nDayofYear;

	for (nYear = CTimeKey().GetYear(); nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHMNEMONIC; )
	{
		for (nMonth = January, szNames.RemoveAll(); nMonth <= December; nMonth = nMonth + 1)
		{
			szNames.Add(CTimeKey(nYear, nMonth, 1, 0, 0, 0).Format(STRING(nSubFormatID)));
			continue;
		}
		return((INT)szNames.GetSize());
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC)
	{
		for (nDayofYear = 1, szNames.RemoveAll(); nDayofYear <= DAYSPERWEEK; nDayofYear++)
		{
			if (CTimeKey(nYear, January, nDayofYear, 0, 0, 0).GetDayOfWeek() == Monday) break;
			continue;
		}
		for (nWeekDay = Sunday; nWeekDay <= Saturday; nWeekDay++)
		{
			szNames.Add(CTimeKey(nYear, January, nDayofYear, 0, 0, 0).Format(STRING(nSubFormatID)));
			nDayofYear++;
		}
		return((INT)szNames.GetSize());
	}
	for (szNames.RemoveAll(); nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANINDICATOR; )
	{
		szNames.Add(CTimeKey(nYear, January, 1, 0, 0, 0).Format(STRING(nSubFormatID)));
		szNames.Add(CTimeKey(nYear, January, 1, 12, 0, 0).Format(STRING(nSubFormatID)));
		return((INT)szNames.GetSize());
	}
	for (szNames.RemoveAll(); nSubFormatID == IDS_TIMEKEY_SUBFORMAT_TIMEZONEINDICATOR; )
	{
		szNames.Add(CTimeKey().Format(STRING(nSubFormatID)));
		return((INT)szNames.GetSize());
	}
	return 0;
}
INT CTimeKey::EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames, BOOL bUTC) CONST
{
	return((bUTC) ? CTimeKey(GetTime() + GetBias()).EnumSubFormatLimits(nSubFormatID, szNames) : EnumSubFormatLimits(nSubFormatID, szNames));
}

CString CTimeKey::FormatTime(LPCTSTR pszFormat, BOOL bUTC, BOOL bNegative) CONST
{
	LPCTSTR  pPos;
	TIMEKEY  tTimeKey;
	CString  szFormat[4];
	CStringTools  cStringTools;
	CTimeKey  tTime(abs(GetTime()));

	if (bUTC)
	{
		for (tTimeKey = GetTime(), szFormat[0] = pszFormat; (pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_DAYS))); )
		{
			for (szFormat[1] = cStringTools.ConvertLongIntToString(tTimeKey / SECONDSPERDAY); (tTimeKey < 0 || bNegative) && tTimeKey / SECONDSPERDAY == 0; )
			{
				szFormat[1] = cStringTools.ConvertIntToString(-1).GetAt(0) + szFormat[1];
				break;
			}
			szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_DAYS)));
			szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
			return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
		}
		if (tTimeKey < 0 || bNegative)
		{
			if ((pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_HOUR))))
			{
				szFormat[1] = cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertLongIntToPaddedString((abs(tTimeKey) % SECONDSPERDAY) / SECONDSPERHOUR, 2);
				szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_HOUR)));
				szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
				return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
			}
			if ((pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_MINUTE))))
			{
				szFormat[1] = cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertLongIntToPaddedString((abs(tTimeKey) % SECONDSPERHOUR) / SECONDSPERMINUTE, 2);
				szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_MINUTE)));
				szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
				return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
			}
			if ((pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_SECOND))))
			{
				szFormat[1] = cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertLongIntToPaddedString(abs(tTimeKey) % SECONDSPERMINUTE, 2);
				szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_SECOND)));
				szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
				return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
			}
		}
		if ((pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR))) && lstrlen(pszFormat) > lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)))
		{
			szFormat[1] = cStringTools.ConvertIntToPaddedString(_ttoi(FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR))), cStringTools.ConvertIntToString(HIWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR, TRUE))).GetLength());
			szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)));
			szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
			return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
		}
		if ((pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK))) && lstrlen(pszFormat) > lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK)))
		{
			szFormat[1] = cStringTools.ConvertIntToString(_ttoi(FormatGmt(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK))));
			szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK)));
			szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
			return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
		}
		return((!lstrcmp(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK))) ? cStringTools.ConvertIntToString(_ttoi(tTime.CTime::FormatGmt(pszFormat)) + 1) : tTime.CTime::FormatGmt(pszFormat));
	}
	return CTimeKey(GetTime() - GetBias()).FormatTime(pszFormat, TRUE, FALSE);
}

TIMEKEY CTimeKey::ParseTime(LPCTSTR pszTimeKey, LPCTSTR pszFormat, BOOL bUTC, BOOL &bNegative) CONST
{
	INT  nDays;
	INT  nHour;
	INT  nMinute;
	INT  nSecond;
	INT  nDayOfWeek;
	INT  nDayOfYear;
	INT  nWeekOfYear;
	INT  nTimeSubkey;
	INT  nTimeSubkeys;
	INT  nSubFormatID;
	BOOL  bCorrection;
	BOOL  bTimeSpan;
	TCHAR  szMinus;
	TIMEKEY  tTime[2];
	CString  szTimeKey;
	CString  szTimeSubkey;
	CString  szTimeKeyFormat;
	SYSTEMTIME  sTimeKeyInfo;
	CStringArray  szSubFormats;
	CStringArray  szTimeSubkeys;
	CStringArray  szTimeSubkeyNames;
	CStringTools  cStringTools;

	for (CTime(abs(GetTime())).GetAsSystemTime(sTimeKeyInfo), szTimeKey = CString(pszTimeKey).Trim(), szTimeKeyFormat = CString(pszFormat).Trim(), szMinus = cStringTools.ConvertIntToString(-1).GetAt(0), nSubFormatID = -1, nDays = nHour = nMinute = nSecond = 0, bTimeSpan = FALSE, bNegative = FALSE, bCorrection = FALSE; !szTimeKeyFormat.IsEmpty(); )
	{
		for (nSubFormatID = MINTIMEKEYSUBFORMAT; nSubFormatID <= MAXTIMEKEYSUBFORMAT; nSubFormatID++)
		{
			if (szTimeKeyFormat.Left(lstrlen(STRING(nSubFormatID))) == STRING(nSubFormatID))
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAROFCENTURY || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTH || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFMONTH || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
				{
					for (szTimeKeyFormat = szTimeKeyFormat.Mid(lstrlen(STRING(nSubFormatID))), szTimeSubkey.Empty(); szTimeKey.GetLength() > 0 && _istdigit(szTimeKey.GetAt(0)); )
					{
						szTimeSubkey += szTimeKey.Left(1);
						szTimeKey = szTimeKey.Mid(1);
					}
					if (!szTimeSubkey.IsEmpty())
					{
						szSubFormats.Add(STRING(nSubFormatID));
						szTimeSubkeys.Add(szTimeSubkey);
						break;
					}
					if (nSubFormatID != IDS_TIMEKEY_SUBFORMAT_HOUR  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_MINUTE  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_SECOND  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_MILLISECOND  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
					{
						nSubFormatID = -1;
						break;
					}
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
				{
					for (szTimeKeyFormat = (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS) ? szTimeKeyFormat.Mid(lstrlen(STRING(nSubFormatID))) : szTimeKeyFormat, szTimeSubkey.Empty(); szTimeKey.GetLength() > 0 && szTimeKey.GetAt(0) == szMinus; )
					{
						szTimeSubkey += szTimeKey.Left(1);
						szTimeKey = szTimeKey.Mid(1);
						break;
					}
					while (szTimeKey.GetLength() > 0 && _istdigit(szTimeKey.GetAt(0)))
					{
						szTimeSubkey += szTimeKey.Left(1);
						szTimeKey = szTimeKey.Mid(1);
					}
					if (!szTimeSubkey.IsEmpty())
					{
						szSubFormats.Add(STRING(nSubFormatID));
						szTimeSubkeys.Add(szTimeSubkey);
						break;
					}
					nSubFormatID = -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHMNEMONIC || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANINDICATOR)
				{
					for (nTimeSubkey = 0, nTimeSubkeys = EnumSubFormatLimits(nSubFormatID, szTimeSubkeyNames, TRUE); nTimeSubkey < nTimeSubkeys; nTimeSubkey++)
					{
						if (szTimeKey.Left(szTimeSubkeyNames.GetAt(nTimeSubkey).GetLength()) == szTimeSubkeyNames.GetAt(nTimeSubkey))
						{
							szTimeKey = szTimeKey.Mid(szTimeSubkeyNames.GetAt(nTimeSubkey).GetLength());
							szTimeKeyFormat = szTimeKeyFormat.Mid(lstrlen(STRING(nSubFormatID)));
							break;
						}
					}
					if (nTimeSubkey < nTimeSubkeys)
					{
						szTimeSubkeys.Add(szTimeSubkeyNames.GetAt(nTimeSubkey));
						szSubFormats.Add(STRING(nSubFormatID));
						break;
					}
				}
				nSubFormatID = -1;
				break;
			}
		}
		if (nSubFormatID > MAXTIMEKEYSUBFORMAT)
		{
			if (szTimeKeyFormat.GetAt(0) == szTimeKey.GetAt(0))
			{
				szTimeKeyFormat = szTimeKeyFormat.Mid(1);
				szTimeKey = szTimeKey.Mid(1);
				continue;
			}
			nSubFormatID = -1;
		}
		if (nSubFormatID < 0) break;
	}
	for (nSubFormatID = (szTimeSubkeys.GetSize() == szSubFormats.GetSize() && nSubFormatID >= 0) ? MINTIMEKEYSUBFORMAT : -1; nSubFormatID >= 0 && nSubFormatID <= MAXTIMEKEYSUBFORMAT; nSubFormatID++)
	{
		for (nTimeSubkey = 0, nTimeSubkeys = (INT)szTimeSubkeys.GetSize(); nTimeSubkey < nTimeSubkeys; nTimeSubkey++)
		{
			if (szSubFormats.GetAt(nTimeSubkey) == STRING(nSubFormatID))
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAR)
				{
					if ((sTimeKeyInfo.wYear = (WORD)_ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) < LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || sTimeKeyInfo.wYear > HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) return -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAROFCENTURY)
				{
					if ((sTimeKeyInfo.wYear = (WORD)((HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) + 1)*(CTimeKey().GetYear() / (HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) + 1)) + _ttoi(szTimeSubkeys.GetAt(nTimeSubkey)))) < LOWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_YEAR, TRUE)) || sTimeKeyInfo.wYear > HIWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_YEAR, TRUE))) return -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTH)
				{
					if ((sTimeKeyInfo.wMonth = (WORD)_ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) < LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || sTimeKeyInfo.wMonth > HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) return -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHMNEMONIC)
				{
					for (EnumSubFormatLimits(nSubFormatID, szTimeSubkeyNames, TRUE); szTimeSubkeyNames.GetSize(); szTimeSubkeyNames.RemoveAt(szTimeSubkeyNames.GetUpperBound()))
					{
						if (!szTimeSubkeys.GetAt(nTimeSubkey).CompareNoCase(szTimeSubkeyNames.GetAt(szTimeSubkeyNames.GetUpperBound()))) break;
						continue;
					}
					if ((sTimeKeyInfo.wMonth = (WORD)szTimeSubkeyNames.GetSize()) < LOWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MONTH, TRUE)) || sTimeKeyInfo.wMonth > HIWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MONTH, TRUE))) return -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)
				{
					if ((nWeekOfYear = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) < LOWORD(CTimeKey(sTimeKeyInfo.wYear, 1, 0, 0, 0).EnumSubFormatLimits(nSubFormatID)) || nWeekOfYear > HIWORD(CTimeKey(sTimeKeyInfo.wYear, 1, 0, 0, 0).EnumSubFormatLimits(nSubFormatID))) return -1;
					CTimeKey  tTimeConversion(CTimeKey(sTimeKeyInfo).GetTime() + (nWeekOfYear - _ttoi(CTimeKey(sTimeKeyInfo).Format(nSubFormatID)))*SECONDSPERWEEK);
					sTimeKeyInfo.wMonth = (WORD)tTimeConversion.GetMonth();
					sTimeKeyInfo.wDay = (WORD)tTimeConversion.GetDay();
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)
				{
					if ((nDayOfYear = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) < LOWORD(CTimeKey(sTimeKeyInfo.wYear, 1, 0, 0, 0).EnumSubFormatLimits(nSubFormatID)) || nDayOfYear > HIWORD(CTimeKey(sTimeKeyInfo.wYear, 1, 0, 0, 0).EnumSubFormatLimits(nSubFormatID))) return -1;
					CTimeKey  tTimeConversion(sTimeKeyInfo.wYear, nDayOfYear, 0, 0, 0);
					sTimeKeyInfo.wMonth = (WORD)tTimeConversion.GetMonth();
					sTimeKeyInfo.wDay = (WORD)tTimeConversion.GetDay();
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFMONTH)
				{
					if ((sTimeKeyInfo.wDay = (WORD)_ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) < LOWORD(CTimeKey(sTimeKeyInfo.wYear, sTimeKeyInfo.wMonth, 1, 0, 0, 0).EnumSubFormatLimits(nSubFormatID)) || sTimeKeyInfo.wDay > HIWORD(CTimeKey(sTimeKeyInfo.wYear, sTimeKeyInfo.wMonth, 1, 0, 0, 0).EnumSubFormatLimits(nSubFormatID))) return -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK)
				{
					if ((nDayOfWeek = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) < LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || nDayOfWeek > HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) return -1;
					CTimeKey  tTimeConversion(CTimeKey(sTimeKeyInfo).GetTime() + (nDayOfWeek - CTimeKey(sTimeKeyInfo).GetDayOfWeek())*SECONDSPERDAY);
					sTimeKeyInfo.wDayOfWeek = (WORD)tTimeConversion.GetDayOfWeek() - 1;
					sTimeKeyInfo.wMonth = (WORD)tTimeConversion.GetMonth();
					sTimeKeyInfo.wDay = (WORD)tTimeConversion.GetDay();
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS)
				{
					if ((nDays = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) < -CTimeKey(MAX_TIMEKEY).GetTime() / SECONDSPERDAY || nDays > CTimeKey(MAX_TIMEKEY).GetTime() / SECONDSPERDAY) return -1;
					bNegative |= ((!szTimeSubkeys.GetAt(nTimeSubkey).IsEmpty() && szTimeSubkeys.GetAt(nTimeSubkey).GetAt(0) == szMinus) || nDays < 0) ? TRUE : FALSE;
					bTimeSpan = TRUE;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC)
				{
					for (EnumSubFormatLimits(nSubFormatID, szTimeSubkeyNames, TRUE); szTimeSubkeyNames.GetSize(); szTimeSubkeyNames.RemoveAt(szTimeSubkeyNames.GetUpperBound()))
					{
						if (!szTimeSubkeys.GetAt(nTimeSubkey).CompareNoCase(szTimeSubkeyNames.GetAt(szTimeSubkeyNames.GetUpperBound()))) break;
						continue;
					}
					if ((nDayOfWeek = (INT)szTimeSubkeyNames.GetSize()) < LOWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK, TRUE)) || sTimeKeyInfo.wDayOfWeek > HIWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK, TRUE))) return -1;
					CTimeKey  tTimeConversion(CTimeKey(sTimeKeyInfo).GetTime() + (nDayOfWeek%DAYSPERWEEK - CTimeKey(sTimeKeyInfo).GetDayOfWeek() + 1)*SECONDSPERDAY);
					sTimeKeyInfo.wDayOfWeek = (WORD)tTimeConversion.GetDayOfWeek() - 1;
					sTimeKeyInfo.wMonth = (WORD)tTimeConversion.GetMonth();
					sTimeKeyInfo.wDay = (WORD)tTimeConversion.GetDay();
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR)
				{
					if (((sTimeKeyInfo.wHour = (WORD)(nHour = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey)))) < LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || sTimeKeyInfo.wHour > HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) && (nHour < -(INT)HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || nHour > -(INT)LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)))) return -1;
					bNegative |= ((!szTimeSubkeys.GetAt(nTimeSubkey).IsEmpty() && szTimeSubkeys.GetAt(nTimeSubkey).GetAt(0) == szMinus) || nHour < 0) ? TRUE : FALSE;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANINDICATOR)
				{
					for (EnumSubFormatLimits(nSubFormatID, szTimeSubkeyNames, TRUE); szTimeSubkeyNames.GetSize(); szTimeSubkeyNames.RemoveAt(szTimeSubkeyNames.GetUpperBound()))
					{
						if (!szTimeSubkeys.GetAt(nTimeSubkey).CompareNoCase(szTimeSubkeyNames.GetAt(szTimeSubkeyNames.GetUpperBound()))) break;
						continue;
					}
					if ((sTimeKeyInfo.wHour = (WORD)(sTimeKeyInfo.wHour%HIWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR, TRUE)) + (szTimeSubkeyNames.GetSize() - 1)*HIWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR, TRUE)))) < LOWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_HOUR, TRUE)) || sTimeKeyInfo.wHour > HIWORD(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_HOUR, TRUE))) return -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE)
				{
					if (((sTimeKeyInfo.wMinute = (WORD)(nMinute = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey)))) < LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || sTimeKeyInfo.wMinute > HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) && (nMinute < -(INT)HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || nMinute > -(INT)LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)))) return -1;
					bNegative |= ((!szTimeSubkeys.GetAt(nTimeSubkey).IsEmpty() && szTimeSubkeys.GetAt(nTimeSubkey).GetAt(0) == szMinus) || nMinute < 0) ? TRUE : FALSE;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND)
				{
					if (((sTimeKeyInfo.wSecond = (WORD)(nSecond = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey)))) < LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || sTimeKeyInfo.wSecond > HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) && (nSecond < -(INT)HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) || nSecond < -(INT)LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)))) return -1;
					bNegative |= ((!szTimeSubkeys.GetAt(nTimeSubkey).IsEmpty() && szTimeSubkeys.GetAt(nTimeSubkey).GetAt(0) == szMinus) || nSecond < 0) ? TRUE : FALSE;
					break;
				}
			}
		}
	}
	if (sTimeKeyInfo.wYear == CTime(0).GetYear() && sTimeKeyInfo.wMonth == CTime(0).GetMonth() && sTimeKeyInfo.wDay == CTime(0).GetDay())
	{
		sTimeKeyInfo.wYear++;
		bCorrection = TRUE;
	}
	for (tTime[0] = (nSubFormatID >= 0) ? ((bTimeSpan || bNegative) ? (((nDays >= 0 && nHour >= 0 && nMinute >= 0 && nSecond >= 0) || (nDays < 0 && nHour >= 0 && nMinute >= 0 && nSecond >= 0) || (nDays >= 0 && nHour < 0 && nMinute >= 0 && nSecond >= 0) || (nDays >= 0 && nHour >= 0 && nMinute < 0 && nSecond >= 0) || (nDays >= 0 && nHour >= 0 && nMinute >= 0 && nSecond < 0)) ? ((nDays >= 0 && nHour >= 0 && nMinute >= 0 && nSecond >= 0) ? (nDays*(TIMEKEY)SECONDSPERDAY + nHour*(TIMEKEY)SECONDSPERHOUR + nMinute*(TIMEKEY)SECONDSPERMINUTE + nSecond) : (-abs(nDays)*(TIMEKEY)SECONDSPERDAY - abs(nHour)*(TIMEKEY)SECONDSPERHOUR - abs(nMinute)*(TIMEKEY)SECONDSPERMINUTE - abs(nSecond))) : (TIMEKEY)-1) : ((bUTC) ? (CTimeKey(sTimeKeyInfo).GetTime() - CTimeKey(sTimeKeyInfo).GetBias()) : CTimeKey(sTimeKeyInfo).GetTime())) : (TIMEKEY)-1, tTime[1] = CTimeKey(sTimeKeyInfo.wYear, 1, 1, 0, 0, 0).GetTime(); nSubFormatID >= 0 && bCorrection; )
	{
		tTime[0] -= (!bTimeSpan  &&  !bNegative) ? tTime[1] : 0;
		tTime[0] += (!bUTC) ? CTimeKey(tTime[1]).GetBias() : 0;
		tTime[0] += (!bTimeSpan  &&  bUTC  &&  !bNegative) ? CTimeKey(tTime[1]).GetBias() : 0;
		tTime[0] -= (bTimeSpan  &&  !bUTC  &&  abs(tTime[0]) < SECONDSPERDAY  &&  bNegative) ? (2 * CTimeKey(tTime[1]).GetBias()) : 0;
		break;
	}
	return tTime[0];
}


/////////////////////////////////////////////////////////////////////////////
// CTimeKeyArray

BOOL CTimeKeyArray::Compare(CONST CTimeKeyArray &tTimeKeys) CONST
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (tTimeKeys.GetSize() == GetSize()) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if (tTimeKeys.GetAt(nItem) != GetAt(nItem)) break;
		continue;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

INT CTimeKeyArray::Map(CByteArray &nInfo) CONST
{
	INT  nItem;
	INT  nItems;
	INT  cbByte;
	INT  cbBytes;
	TIMEKEY  tTimeKey;

	for (nItem = 0, nItems = (INT)GetSize(), nInfo.RemoveAll(); nItem < nItems; nItem++)
	{
		for (cbByte = 0, cbBytes = sizeof(TIMEKEY), tTimeKey = GetAt(nItem).GetTime(); cbByte < cbBytes; cbByte++)
		{
			nInfo.Add((BYTE)(tTimeKey & 0xFF));
			tTimeKey >>= 8 * sizeof(BYTE);
		}
	}
	return((INT)nInfo.GetSize());
}

BOOL CTimeKeyArray::Unmap(CONST CByteArray &nInfo)
{
	INT  cbByte;
	INT  cbBytes;
	TIMEKEY  tTimeKey;

	for (cbByte = 0, cbBytes = (INT)nInfo.GetSize(), tTimeKey = 0, RemoveAll(); cbByte < cbBytes; cbByte++)
	{
		tTimeKey += ((TIMEKEY)nInfo.GetAt(cbByte)) << (8 * (cbByte%sizeof(TIMEKEY)));
		if (cbByte%sizeof(TIMEKEY) == sizeof(TIMEKEY) - 1)
		{
			if (Add(tTimeKey) >= 0)
			{
				tTimeKey = 0;
				continue;
			}
			break;
		}
	}
	return((cbByte == cbBytes) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTimeTag

CTimeTag::CTimeTag() : CTimeKey()
{
	SYSTEMTIME  sTime;
	LARGE_INTEGER  lFrequency;
	LARGE_INTEGER  lTimeCount;

	GetSystemTime(&sTime);
	m_nMicroSeconds = (QueryPerformanceFrequency(&lFrequency) && QueryPerformanceCounter(&lTimeCount) && lFrequency.QuadPart > 1000) ? (INT)((1000000 * (lTimeCount.QuadPart%lFrequency.QuadPart)) / lFrequency.QuadPart) : (1000 * sTime.wMilliseconds);
}
CTimeTag::CTimeTag(TIMETAG tTimeTag) : CTimeKey((TIMEKEY)(tTimeTag / 1000000))
{
	m_nMicroSeconds = (tTimeTag / 1000000 != 0 || tTimeTag >= 0) ? (INT)(abs(tTimeTag) % 1000000) : (INT)(tTimeTag % 1000000);
}
CTimeTag::CTimeTag(CONST CTimeKey &tTimeTag) : CTimeKey(tTimeTag)
{
	m_nMicroSeconds = 0;
}
CTimeTag::CTimeTag(CONST CTimeTag &tTimeTag) : CTimeKey((TIMEKEY)(tTimeTag.GetTime() / 1000000))
{
	m_nMicroSeconds = (tTimeTag.GetTime() / 1000000 != 0 || tTimeTag >= 0) ? (INT)(abs(tTimeTag.GetTime()) % 1000000) : (INT)(tTimeTag.GetTime() % 1000000);
}
CTimeTag::CTimeTag(CONST FILETIME &tTimeTag) : CTimeKey(tTimeTag)
{
	m_nMicroSeconds = (INT)(((((TIMETAG)tTimeTag.dwHighDateTime << 32) + tTimeTag.dwLowDateTime) % 10000000) / 10);
}
CTimeTag::CTimeTag(CONST SYSTEMTIME &tTimeTag) : CTimeKey(tTimeTag)
{
	m_nMicroSeconds = 1000 * tTimeTag.wMilliseconds;
}
CTimeTag::CTimeTag(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond) : CTimeKey(nYear, nMonth, nDay, nHour, nMinute, nSecond)
{
	m_nMicroSeconds = 1000 * nMilliSecond + nMicroSecond;
}
CTimeTag::CTimeTag(INT nYear, INT nDayofYear, INT nHour, INT nMinute, INT nSecond, INT nMilliSecond, INT nMicroSecond) : CTimeKey(nYear, nDayofYear, nHour, nMinute, nSecond)
{
	m_nMicroSeconds = 1000 * nMilliSecond + nMicroSecond;
}

VOID CTimeTag::SetTime(TIMETAG tTimeTag)
{
	TIMEKEY  t;

	m_nMicroSeconds = ((t = (TIMEKEY)(tTimeTag / 1000000)) != 0 || tTimeTag >= 0) ? (INT)abs(tTimeTag % 1000000) : (INT)(tTimeTag % 1000000);
	CTimeKey::SetTime(t);
}
VOID CTimeTag::SetTime(CONST CTimeKey &tTimeTag)
{
	m_nMicroSeconds = 0;
	CTimeKey::SetTime(tTimeTag);
}
VOID CTimeTag::SetTime(CONST CTimeTag &tTimeTag)
{
	TIMEKEY  t;

	m_nMicroSeconds = ((t = (TIMEKEY)(tTimeTag.GetTime() / 1000000)) != 0 || tTimeTag >= 0) ? (INT)abs(tTimeTag.GetTime() % 1000000) : (INT)(tTimeTag.GetTime() % 1000000);
	CTimeKey::SetTime(t);
}
VOID CTimeTag::SetTime(CONST FILETIME &tTimeTag)
{
	m_nMicroSeconds = (INT)(((((TIMETAG)tTimeTag.dwHighDateTime << 32) + tTimeTag.dwLowDateTime) % 10000000) / 10);
	CTimeKey::SetTime(tTimeTag);
}
VOID CTimeTag::SetTime(CONST SYSTEMTIME &tTimeTag)
{
	m_nMicroSeconds = (INT)(1000 * tTimeTag.wMilliseconds);
	CTimeKey::SetTime(tTimeTag);
}

TIMETAG CTimeTag::GetTime() CONST
{
	return ConvertTime();
}
BOOL CTimeTag::GetTime(CTimeKey &tTimeTag) CONST
{
	return CTimeKey::GetTime(tTimeTag);
}
BOOL CTimeTag::GetTime(CTimeTag &tTimeTag) CONST
{
	tTimeTag = ConvertTime();
	return TRUE;
}
BOOL CTimeTag::GetTime(FILETIME &tTimeTag) CONST
{
	TIMETAG  dwTime;

	if (CTimeKey::GetTime(tTimeTag))
	{
		dwTime = (TIMETAG)tTimeTag.dwLowDateTime + ((TIMETAG)tTimeTag.dwHighDateTime << 32) + (TIMETAG)10 * m_nMicroSeconds;
		tTimeTag.dwHighDateTime = (DWORD)(dwTime >> 32);
		tTimeTag.dwLowDateTime = (DWORD)dwTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CTimeTag::GetTime(SYSTEMTIME &tTimeTag) CONST
{
	FILETIME  tTime[2];

	return((GetTime(tTime[0]) && FileTimeToLocalFileTime(&tTime[0], &tTime[1]) && FileTimeToSystemTime(&tTime[1], &tTimeTag)) ? TRUE : FALSE);
}

TIMEKEY CTimeTag::GetTimeInSeconds() CONST
{
	return CTimeKey::GetTime();
}

INT CTimeTag::GetMilliSeconds() CONST
{
	return m_nMicroSeconds / 1000;
}

INT CTimeTag::GetMicroSeconds() CONST
{
	return m_nMicroSeconds % 1000;
}

TIMETAG CTimeTag::GetBias() CONST
{
	return 1000000 * (TIMETAG)CTimeKey::GetBias();
}

CString CTimeTag::Format() CONST
{
	return FormatTime(STRING(IDS_TIMETAG_FORMAT), FALSE);
}
CString CTimeTag::Format(INT nFormatID) CONST
{
	return FormatTime(((nFormatID >= MINTIMETAGFORMAT  &&  nFormatID <= MAXTIMETAGFORMAT) || (nFormatID >= MINTIMEKEYSUBFORMAT  &&  nFormatID <= MAXTIMEKEYSUBFORMAT)) ? STRING(nFormatID) : STRING(IDS_TIMETAG_FORMAT), FALSE);
}
CString CTimeTag::Format(LPCTSTR pszFormat) CONST
{
	return FormatTime(pszFormat, FALSE);
}

CString CTimeTag::FormatGmt() CONST
{
	return FormatTime(STRING(IDS_TIMETAG_FORMAT), TRUE);
}
CString CTimeTag::FormatGmt(INT nFormatID) CONST
{
	return FormatTime(((nFormatID >= MINTIMETAGFORMAT  &&  nFormatID <= MAXTIMETAGFORMAT) || (nFormatID >= MINTIMEKEYSUBFORMAT  &&  nFormatID <= MAXTIMEKEYSUBFORMAT)) ? STRING(nFormatID) : STRING(IDS_TIMETAG_FORMAT), TRUE);
}
CString CTimeTag::FormatGmt(LPCTSTR pszFormat) CONST
{
	return FormatTime(pszFormat, TRUE);
}

TIMETAG CTimeTag::Parse(LPCTSTR pszTimeTag) CONST
{
	return ParseTime(pszTimeTag, STRING(IDS_TIMETAG_FORMAT), FALSE);
}
TIMETAG CTimeTag::Parse(LPCTSTR pszTimeTag, LPCTSTR pszFormat) CONST
{
	return ParseTime(pszTimeTag, pszFormat, FALSE);
}

TIMETAG CTimeTag::ParseGmt(LPCTSTR pszTimeTag) CONST
{
	return ParseTime(pszTimeTag, STRING(IDS_TIMETAG_FORMAT), TRUE);
}
TIMETAG CTimeTag::ParseGmt(LPCTSTR pszTimeTag, LPCTSTR pszFormat) CONST
{
	return ParseTime(pszTimeTag, pszFormat, TRUE);
}

INT CTimeTag::EnumSubFormatLimits(INT nSubFormatID) CONST
{
	LONG  nLimits;

	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND)
	{
		nLimits = MAKELONG(0, 999);
		return nLimits;
	}
	if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
	{
		nLimits = MAKELONG(0, 999);
		return nLimits;
	}
	return CTimeKey::EnumSubFormatLimits(nSubFormatID);
}
INT CTimeTag::EnumSubFormatLimits(INT nSubFormatID, BOOL bUTC) CONST
{
	return((bUTC) ? CTimeTag(GetTime() + GetBias()).EnumSubFormatLimits(nSubFormatID) : EnumSubFormatLimits(nSubFormatID));
}
INT CTimeTag::EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames) CONST
{
	return CTimeKey::EnumSubFormatLimits(nSubFormatID, szNames);
}
INT CTimeTag::EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames, BOOL bUTC) CONST
{
	return((bUTC) ? CTimeTag(GetTime() + GetBias()).EnumSubFormatLimits(nSubFormatID, szNames) : EnumSubFormatLimits(nSubFormatID, szNames));
}

CTimeTag &CTimeTag::operator=(TIMETAG tTimeTag)
{
	SetTime(tTimeTag);
	return *this;
}
CTimeTag &CTimeTag::operator=(CONST CTimeTag &tTimeTag)
{
	SetTime(tTimeTag.GetTime());
	return *this;
}

CTimeTag &CTimeTag::operator+=(TIMETAG tTimeSpan)
{
	SetTime(ConvertTime() + tTimeSpan);
	return *this;
}

CTimeTag &CTimeTag::operator-=(TIMETAG tTimeSpan)
{
	SetTime((ConvertTime() >= tTimeSpan) ? (ConvertTime() - tTimeSpan) : 0);
	return *this;
}

CTimeTag CTimeTag::operator+(TIMETAG tTimeSpan) CONST
{
	return ConvertTime() + tTimeSpan;
}
CTimeTag CTimeTag::operator+(CONST CTimeTag &tTimeTag) CONST
{
	return ConvertTime() + tTimeTag.GetTime();
}

CTimeTag CTimeTag::operator-(TIMETAG tTimeSpan) CONST
{
	return((ConvertTime() >= tTimeSpan) ? (ConvertTime() - tTimeSpan) : 0);
}
CTimeTag CTimeTag::operator-(CONST CTimeTag &tTimeTag) CONST
{
	return((ConvertTime() >= tTimeTag.GetTime()) ? (ConvertTime() - tTimeTag.GetTime()) : 0);
}

BOOL CTimeTag::operator==(CONST CTimeTag &tTimeTag) CONST
{
	return ConvertTime() == tTimeTag.GetTime();
}

BOOL CTimeTag::operator!=(CONST CTimeTag &tTimeTag) CONST
{
	return ConvertTime() != tTimeTag.GetTime();
}

BOOL CTimeTag::operator<=(CONST CTimeTag &tTimeTag) CONST
{
	return ConvertTime() <= tTimeTag.GetTime();
}

BOOL CTimeTag::operator>=(CONST CTimeTag &tTimeTag) CONST
{
	return ConvertTime() >= tTimeTag.GetTime();
}

BOOL CTimeTag::operator<(CONST CTimeTag &tTimeTag) CONST
{
	return ConvertTime() < tTimeTag.GetTime();
}

BOOL CTimeTag::operator>(CONST CTimeTag &tTimeTag) CONST
{
	return ConvertTime() > tTimeTag.GetTime();
}

CString CTimeTag::FormatTime(LPCTSTR pszFormat, BOOL bUTC) CONST
{
	INT  nPos;
	LPCTSTR  pPos;
	CString  szFormat[4];
	CStringTools  cStringTools;
	CTimeTag  tTime(abs(GetTime()));

	if (bUTC)
	{
		for (szFormat[0] = pszFormat; GetTime() < 0; )
		{
			if ((pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_MILLISECOND))) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_DAYS)) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_HOUR)) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_MINUTE)) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_SECOND)))
			{
				szFormat[1] = cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertIntToPaddedString(GetMilliSeconds(), 3);
				szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_MILLISECOND)));
				szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
				return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
			}
			if ((pPos = _tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_MICROSECOND))) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_HOUR)) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_MINUTE)) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_SECOND)) && !_tcsstr(pszFormat, STRING(IDS_TIMEKEY_SUBFORMAT_MILLISECOND)))
			{
				szFormat[1] = cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertIntToPaddedString(GetMilliSeconds(), 3);
				szFormat[2] = szFormat[0].Mid(szFormat[0].GetLength() - lstrlen(pPos) + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_MICROSECOND)));
				szFormat[3] = szFormat[0].Left(szFormat[0].GetLength() - lstrlen(pPos));
				return tTime.FormatGmt(szFormat[3] + szFormat[1] + szFormat[2]);
			}
			break;
		}
		if ((nPos = szFormat[0].Find(STRING(IDS_TIMEKEY_SUBFORMAT_MILLISECOND))) >= 0)
		{
			szFormat[0] = szFormat[0].Left(nPos) + szFormat[0].Mid(nPos + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_MILLISECOND)));
			szFormat[0] = szFormat[0].Left(nPos) + cStringTools.ConvertIntToPaddedString(abs(GetMilliSeconds()), 3) + szFormat[0].Mid(nPos);
		}
		if ((nPos = szFormat[0].Find(STRING(IDS_TIMEKEY_SUBFORMAT_MICROSECOND))) >= 0)
		{
			szFormat[0] = szFormat[0].Left(nPos) + szFormat[0].Mid(nPos + lstrlen(STRING(IDS_TIMEKEY_SUBFORMAT_MICROSECOND)));
			szFormat[0] = szFormat[0].Left(nPos) + cStringTools.ConvertIntToPaddedString(abs(GetMicroSeconds()), 3) + szFormat[0].Mid(nPos);
		}
		return CTimeKey::FormatTime(szFormat[0], bUTC, GetTime() < 0);
	}
	return CTimeTag(GetTime() - GetBias()).FormatTime(pszFormat, TRUE);
}

TIMETAG CTimeTag::ParseTime(LPCTSTR pszTimeTag, LPCTSTR pszFormat, BOOL bUTC) CONST
{
	INT  nTimeSubkey;
	INT  nTimeSubkeys;
	INT  nSubFormatID;
	INT  nMilliSeconds;
	INT  nMicroSeconds;
	BOOL  bNegative;
	TCHAR  szMinus;
	TIMETAG  tTime;
	CString  szTimeKey;
	CString  szTimeSubkey;
	CString  szTimeKeyFormat;
	CStringArray  szSubFormats;
	CStringArray  szTimeSubkeys;
	CStringArray  szTimeSubkeyNames;
	CStringTools  cStringTools;

	for (szTimeKey = CString(pszTimeTag).Trim(), szTimeKeyFormat = CString(pszFormat).Trim(), szMinus = cStringTools.ConvertIntToString(-1).GetAt(0), nSubFormatID = -1, nMilliSeconds = m_nMicroSeconds / 1000, nMicroSeconds = m_nMicroSeconds % 1000, bNegative = FALSE; !szTimeKeyFormat.IsEmpty(); )
	{
		for (nSubFormatID = MINTIMETAGSUBFORMAT; nSubFormatID <= MAXTIMETAGSUBFORMAT; nSubFormatID++)
		{
			if (szTimeKeyFormat.Left(lstrlen(STRING(nSubFormatID))) == STRING(nSubFormatID))
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAROFCENTURY || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTH || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFMONTH || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
				{
					for (szTimeKeyFormat = szTimeKeyFormat.Mid(lstrlen(STRING(nSubFormatID))), szTimeSubkey.Empty(); szTimeKey.GetLength() > 0 && _istdigit(szTimeKey[0]); )
					{
						szTimeSubkey += szTimeKey.Left(1);
						szTimeKey = szTimeKey.Mid(1);
					}
					if (!szTimeSubkey.IsEmpty())
					{
						szSubFormats.Add(STRING(nSubFormatID));
						szTimeSubkeys.Add(szTimeSubkey);
						break;
					}
					if (nSubFormatID != IDS_TIMEKEY_SUBFORMAT_HOUR  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_MINUTE  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_SECOND  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_MILLISECOND  &&  nSubFormatID != IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
					{
						nSubFormatID = -1;
						break;
					}
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
				{
					for (szTimeKeyFormat = (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS) ? szTimeKeyFormat.Mid(lstrlen(STRING(nSubFormatID))) : szTimeKeyFormat, szTimeSubkey.Empty(); szTimeKey.GetLength() > 0 && szTimeKey.GetAt(0) == szMinus; )
					{
						szTimeSubkey += szTimeKey.Left(1);
						szTimeKey = szTimeKey.Mid(1);
						break;
					}
					while (szTimeKey.GetLength() > 0 && _istdigit(szTimeKey.GetAt(0)))
					{
						szTimeSubkey += szTimeKey.Left(1);
						szTimeKey = szTimeKey.Mid(1);
					}
					if (!szTimeSubkey.IsEmpty())
					{
						szSubFormats.Add(STRING(nSubFormatID));
						szTimeSubkeys.Add(szTimeSubkey);
						break;
					}
					nSubFormatID = -1;
					break;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHMNEMONIC || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANINDICATOR)
				{
					for (nTimeSubkey = 0, nTimeSubkeys = EnumSubFormatLimits(nSubFormatID, szTimeSubkeyNames, TRUE); nTimeSubkey < nTimeSubkeys; nTimeSubkey++)
					{
						if (szTimeKey.Left(szTimeSubkeyNames.GetAt(nTimeSubkey).GetLength()) == szTimeSubkeyNames.GetAt(nTimeSubkey))
						{
							szTimeKey = szTimeKey.Mid(szTimeSubkeyNames.GetAt(nTimeSubkey).GetLength());
							szTimeKeyFormat = szTimeKeyFormat.Mid(lstrlen(STRING(nSubFormatID)));
							break;
						}
					}
					if (nTimeSubkey < nTimeSubkeys)
					{
						szTimeSubkeys.Add(szTimeSubkeyNames.GetAt(nTimeSubkey));
						szSubFormats.Add(STRING(nSubFormatID));
						break;
					}
				}
				nSubFormatID = -1;
				break;
			}
		}
		if (nSubFormatID > MAXTIMETAGSUBFORMAT)
		{
			if (szTimeKeyFormat.GetAt(0) == szTimeKey.GetAt(0))
			{
				szTimeKeyFormat = szTimeKeyFormat.Mid(1);
				szTimeKey = szTimeKey.Mid(1);
				continue;
			}
			nSubFormatID = -1;
		}
		if (nSubFormatID < 0) break;
	}
	for (nSubFormatID = (szTimeSubkeys.GetSize() == szSubFormats.GetSize() && nSubFormatID >= 0) ? MINTIMETAGSUBFORMAT : -1; nSubFormatID >= 0 && nSubFormatID <= MAXTIMETAGSUBFORMAT; nSubFormatID++)
	{
		for (nTimeSubkey = 0, nTimeSubkeys = (INT)szTimeSubkeys.GetSize(); nTimeSubkey < nTimeSubkeys; nTimeSubkey++)
		{
			if (szSubFormats.GetAt(nTimeSubkey) == STRING(nSubFormatID))
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND)
				{
					if ((nMilliSeconds = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) >= LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) && nMilliSeconds <= HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) break;
					if (nMilliSeconds >= -(INT)HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) && nMilliSeconds <= -(INT)LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) break;
					return -1;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
				{
					if ((nMicroSeconds = _ttoi(szTimeSubkeys.GetAt(nTimeSubkey))) >= LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) && nMicroSeconds <= HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) break;
					if (nMicroSeconds >= -(INT)HIWORD(EnumSubFormatLimits(nSubFormatID, TRUE)) && nMicroSeconds <= -(INT)LOWORD(EnumSubFormatLimits(nSubFormatID, TRUE))) break;
					return -1;
				}
			}
		}
	}
	return(((tTime = (nSubFormatID >= 0) ? (1000000 * (TIMETAG)CTimeKey::ParseTime(pszTimeTag, pszFormat, bUTC, bNegative)) : -1) != (TIMEKEY)-1 || bNegative) ? (((tTime >= 0 && ((nMilliSeconds >= 0 && nMicroSeconds >= 0) || (nMilliSeconds < 0 && nMicroSeconds >= 0 && !bNegative) || (nMilliSeconds >= 0 && nMicroSeconds < 0 && !bNegative))) || ((tTime < 0 || bNegative) && nMilliSeconds >= 0 && nMicroSeconds >= 0)) ? ((tTime >= 0 && nMilliSeconds >= 0 && nMicroSeconds >= 0 && !bNegative) ? (tTime + 1000 * nMilliSeconds + nMicroSeconds) : (-abs(tTime) - 1000 * abs(nMilliSeconds) - abs(nMicroSeconds))) : -1) : -1);
}

TIMETAG CTimeTag::ConvertTime() CONST
{
	TIMETAG  t;

	return((((t = 1000000 * (TIMETAG)CTimeKey::GetTime())) >= 0) ? (t + (TIMETAG)m_nMicroSeconds) : (t - (TIMETAG)m_nMicroSeconds));
}


/////////////////////////////////////////////////////////////////////////////
// CTimeTagArray

BOOL CTimeTagArray::Compare(CONST CTimeTagArray &tTimeTags) CONST
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (tTimeTags.GetSize() == GetSize()) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if (tTimeTags.GetAt(nItem) != GetAt(nItem)) break;
		continue;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

INT CTimeTagArray::Map(CByteArray &nInfo) CONST
{
	INT  nItem;
	INT  nItems;
	INT  cbByte;
	INT  cbBytes;
	TIMETAG  tTimeTag;

	for (nItem = 0, nItems = (INT)GetSize(), nInfo.RemoveAll(); nItem < nItems; nItem++)
	{
		for (cbByte = 0, cbBytes = sizeof(TIMETAG), tTimeTag = GetAt(nItem).GetTime(); cbByte < cbBytes; cbByte++)
		{
			nInfo.Add((BYTE)(tTimeTag & 0xFF));
			tTimeTag >>= 8 * sizeof(BYTE);
		}
	}
	return((INT)nInfo.GetSize());
}

BOOL CTimeTagArray::Unmap(CONST CByteArray &nInfo)
{
	INT  cbByte;
	INT  cbBytes;
	TIMETAG  tTimeTag;

	for (cbByte = 0, cbBytes = (INT)nInfo.GetSize(), tTimeTag = 0, RemoveAll(); cbByte < cbBytes; cbByte++)
	{
		tTimeTag += ((TIMETAG)nInfo.GetAt(cbByte)) << (8 * (cbByte%sizeof(TIMETAG)));
		if (cbByte%sizeof(TIMETAG) == sizeof(TIMETAG) - 1)
		{
			if (Add(tTimeTag) >= 0)
			{
				tTimeTag = 0;
				continue;
			}
			break;
		}
	}
	return((cbByte == cbBytes) ? TRUE : FALSE);
}
