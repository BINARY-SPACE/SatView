// TDSTime.H : SCOS-2000 Time & Date Subsystem Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the SCOS-2000 time & date sub-system
// related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/07/31 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TDSTime_H__
#define __TDSTime_H__


/////////////////////////////////////////////////////////////////////////////
// TDSsunTime class

#define TDS_ASD_DISPLAY   0
#define TDS_ASCIIA_DISPLAY   1
#define TDS_ASCIIB_DISPLAY   2
#define TDS_NO_DELTA   0
#define TDS_DELTA   1
#define TDS_ASD_BUFFER_LEN   22
#define TDS_ASCIIA_BUFFER_LEN  27
#define TDS_ASCIIB_BUFFER_LEN  25
#define TDS_DELTA_BUFFER_LEN   17

class TDSsunTime : public CTimeTag
{
	// Construction
public:
	TDSsunTime();
	TDSsunTime(LPCTSTR asciiString, UINT nType = TDS_ASCIIA_DISPLAY);
	TDSsunTime(unsigned long sec, unsigned long micro, const char deltaFlag = TDS_NO_DELTA);
	TDSsunTime(const TDSsunTime &tm);
	TDSsunTime(TIMETAG tm);

	// Attributes
private:
	bool  m_deltaFlag;

	// Operations
public:
	void set_seconds(unsigned long secs);
	void set_usecs(unsigned long usecs);
	void get_current_time();
	unsigned long get_seconds() const;
	unsigned long get_usecs() const;
	void get_ASD(CString &asdBuf) const;
	void get_asciiA(CString &asciiBuf) const;
	void get_asciiB(CString &asciiBuf) const;

	bool isAbsTime() const;
	bool isDeltaTime() const;

	TDSsunTime& operator=(const TDSsunTime& tm);
	TDSsunTime& operator+=(const TDSsunTime& tm);
	TDSsunTime& operator-=(const TDSsunTime& tm);
	TDSsunTime operator+(const TDSsunTime& tm) const;
	TDSsunTime operator-(const TDSsunTime& tm) const;
	TDSsunTime operator*(LONGLONG factor) const;
	TDSsunTime operator/(LONGLONG factor) const;
	bool operator==(const TDSsunTime& tm) const;
	bool operator!=(const TDSsunTime& tm) const;
	bool operator>=(const TDSsunTime& tm) const;
	bool operator>(const TDSsunTime& tm) const;
	bool operator<=(const TDSsunTime& tm) const;
	bool operator<(const TDSsunTime& tm) const;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TDSTime_H__
