// TDSTime.CPP : SCOS-2000 Date & Time Subsystem Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the SCOS-2000 date &
// time sub-system related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/07/31 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SCOS-2000.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// TDSsunTime

TDSsunTime::TDSsunTime() : CTimeTag(0)
{
	m_deltaFlag = FALSE;
}
TDSsunTime::TDSsunTime(LPCTSTR asciiString, UINT nType) : CTimeTag(max(CTimeTag(0).ParseGmt(asciiString, (nType == TDS_ASD_DISPLAY) ? STRING(IDS_DERIVATION_OL_TIMEFORMAT_ASD) : ((nType != TDS_ASCIIA_DISPLAY) ? STRING(IDS_DERIVATION_OL_TIMEFORMAT_ASCIIB) : STRING(IDS_DERIVATION_OL_TIMEFORMAT_ASCIIA))), MIN_TIMETAG))
{
	m_deltaFlag = FALSE;
}
TDSsunTime::TDSsunTime(unsigned long sec, unsigned long micro, const char deltaFlag) : CTimeTag((TIMETAG)1000000 * (TIMETAG)sec + micro)
{
	m_deltaFlag = (deltaFlag != 0) ? TRUE : FALSE;
}
TDSsunTime::TDSsunTime(const TDSsunTime &tm) : CTimeTag((TIMETAG)1000000 * (TIMETAG)tm.get_seconds() + tm.get_usecs())
{
	m_deltaFlag = FALSE;
}
TDSsunTime::TDSsunTime(TIMETAG tm) : CTimeTag(tm)
{
	m_deltaFlag = FALSE;
}

void TDSsunTime::set_seconds(unsigned long secs)
{
	TIMETAG  t = GetTime();

	SetTime((TIMETAG)1000000 * (TIMETAG)secs + t % 1000000);
}

void TDSsunTime::set_usecs(unsigned long usecs)
{
	m_nMicroSeconds = usecs;
}

void TDSsunTime::get_current_time()
{
	SetTime(CTimeTag());
}

unsigned long TDSsunTime::get_seconds() const
{
	return((unsigned int)GetTime() / 1000000);
}

unsigned long TDSsunTime::get_usecs() const
{
	return((unsigned int)GetTime() % 1000000);
}

void TDSsunTime::get_ASD(CString &asdBuf) const
{
	asdBuf = FormatGmt(STRING(IDS_DERIVATION_OL_TIMEFORMAT_ASD));
}

void TDSsunTime::get_asciiA(CString &asciiBuf) const
{
	asciiBuf = FormatGmt(STRING(IDS_DERIVATION_OL_TIMEFORMAT_ASCIIA));
}

void TDSsunTime::get_asciiB(CString &asciiBuf) const
{
	asciiBuf = FormatGmt(STRING(IDS_DERIVATION_OL_TIMEFORMAT_ASCIIB));
}

bool TDSsunTime::isAbsTime() const
{
	return(!m_deltaFlag);
}

bool TDSsunTime::isDeltaTime() const
{
	return m_deltaFlag;
}

TDSsunTime& TDSsunTime::operator=(const TDSsunTime& tm)
{
	SetTime((TIMETAG)1000000 * (TIMETAG)tm.get_seconds() + tm.get_usecs());
	return *this;
}

TDSsunTime& TDSsunTime::operator+=(const TDSsunTime& tm)
{
	if (isDeltaTime() || tm.isDeltaTime()) SetTime(GetTime() + (TIMETAG)1000000 * (TIMETAG)tm.get_seconds() + tm.get_usecs());
	return *this;
}

TDSsunTime& TDSsunTime::operator-=(const TDSsunTime& tm)
{
	if (isDeltaTime() || tm.isDeltaTime()) SetTime(GetTime() - (TIMETAG)1000000 * (TIMETAG)tm.get_seconds() - tm.get_usecs());
	return *this;
}

TDSsunTime TDSsunTime::operator+(const TDSsunTime& tm) const
{
	TDSsunTime  t(*this);

	if (isDeltaTime() || tm.isDeltaTime()) t.SetTime(GetTime() + tm.GetTime());
	return t;
}

TDSsunTime TDSsunTime::operator-(const TDSsunTime& tm) const
{
	TDSsunTime  t(*this);

	if (isDeltaTime() || tm.isDeltaTime()) t.SetTime(GetTime() - tm.GetTime());
	return t;
}

TDSsunTime TDSsunTime::operator*(LONGLONG factor) const
{
	TDSsunTime  t(*this);

	if (isDeltaTime()) t.SetTime(GetTime()*factor);
	return t;
}

TDSsunTime TDSsunTime::operator/(LONGLONG factor) const
{
	TDSsunTime  t(*this);

	if (isDeltaTime() && factor != 0) t.SetTime(GetTime() / factor);
	return t;
}

bool TDSsunTime::operator==(const TDSsunTime& tm) const
{
	return(GetTime() == tm.GetTime());
}

bool TDSsunTime::operator!=(const TDSsunTime& tm) const
{
	return(GetTime() != tm.GetTime());
}

bool TDSsunTime::operator>=(const TDSsunTime& tm) const
{
	return(GetTime() >= tm.GetTime());
}

bool TDSsunTime::operator>(const TDSsunTime& tm) const
{
	return(GetTime() > tm.GetTime());
}

bool TDSsunTime::operator<=(const TDSsunTime& tm) const
{
	return(GetTime() <= tm.GetTime());
}

bool TDSsunTime::operator<(const TDSsunTime& tm) const
{
	return(GetTime() < tm.GetTime());
}
