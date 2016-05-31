// VALue.H : SCOS-2000 VAL Subsystem Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the SCOS-2000 VAL sub-system related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/07/31 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __VALue_H__
#define __VALue_H__

#include "TDSTime.h"


/////////////////////////////////////////////////////////////////////////////
// VALidity class

enum VALidityStatus {
	VALValid = 0,
	VALindeterm,
	VALexpired,
	VALuncertain,
	VALtransient,
	VALinvalid,
	VALerror
};

struct VALidityState {
	// INVALID - 4 bits
	unsigned int StateOff : 1; // State validity evaluates to 0
	unsigned int PowerOff : 1; // System element is not powered
	unsigned int RouteOff : 1; // Transport device route is off
	unsigned int Preserve : 1; // Used to prevent flags overwritten in SPPG
							   // TRANSIENT - 1 bit
	unsigned int Transient : 1; // Telecommand scheduled for param
								// UNCERTAIN - 8 bits
	unsigned int TransportError1 : 1; // Copied from SIIpkt header field
	unsigned int TransportError2 : 1;
	unsigned int TransportError3 : 1;
	unsigned int TransportError4 : 1;
	unsigned int TransportError5 : 1;
	unsigned int TransportError6 : 1;
	unsigned int TransportError7 : 1;
	unsigned int TransportError8 : 1;
	// EXPIRED - 1 bit
	unsigned int Expired : 1; // VALue has expired (packet not arrived)
							  // INDETERMINABLE - 6 bits
	unsigned int UnknownState : 1; // State parameter is !valid
	unsigned int UnknownCond : 1; // Had to branch on !valid condition
	unsigned int UnknownCriteria : 1; // Had to select on !valid applic crit
	unsigned int Calibration : 1; // Calibration failed
	unsigned int TooEarly : 1; // Requested time predates mission
	unsigned int UnknownPkt : 1; // Paket not configured in cache
								 // GENERAL SYSTEM ERROR - 12 bits
	unsigned int UnInit : 1; // VALue has not been initialised
	unsigned int PktRetrv : 1; // Packet retrieval error
	unsigned int MIBerror : 1; // Error in MIB data
	unsigned int SystemError : 1; // Miscellaneous system error
	unsigned int FieldUnknown : 1; // Field unknown in packet definition
	unsigned int FieldAbsent : 1; // Field absent from given pkt
	unsigned int UnknownType : 1; // Unknown Type name for VALue constructor
	unsigned int UnknownOp : 1; // Unknown operator for VALue's type
	unsigned int UnknownConv : 1; // Unknown conversion for VALue's type
	unsigned int Overflow : 1; // An overflow occured - data lost
	unsigned int DivideByZero : 1; // A big overflow would've occured!
	unsigned int OLparse : 1; // Error occured parsing OL expression
};

class AFX_EXT_CLASS VALidity : public CObject
{
	// Construction
public:
	VALidity();
	VALidity(const VALidity& vld);
	~VALidity();

	// Attributes
private:
	union {
		unsigned int  m_state;
		VALidityState  m_mask;
	};

	// Operations
public:
	void setValid();
	void setAllStates(unsigned int states);
	unsigned int getAllStates() const;

	void setUnknownCond(bool enable = true);
	void setUnknownCriteria(bool enable = true);
	void setUnknownPkt(bool enable = true);
	void setUnknownState(bool enable = true);
	void setDivideByZero(bool enable = true);
	void setTooEarly(bool enable = true);
	void setExpired(bool enable = true);
	void setFieldAbsent(bool enable = true);
	void setFieldUnknown(bool enable = true);
	void setMIBError(bool enable = true);
	void setOLparse(bool enable = true);
	void setCalibration(bool enable = true);
	void setOverflow(bool enable = true);
	void setPreserve(bool enable = true);
	void setPoverOff(bool enable = true);
	void setPktRetr(bool enable = true);
	void setRouteOff(bool enable = true);
	void setStateOff(bool enable = true);
	void setSystemError(bool enable = true);
	void setTransportError1(bool enable = true);
	void setTransportError2(bool enable = true);
	void setTransportError3(bool enable = true);
	void setTransportError4(bool enable = true);
	void setTransportError5(bool enable = true);
	void setTransportError6(bool enable = true);
	void setTransportError7(bool enable = true);
	void setTransportError8(bool enable = true);
	void setTransient(bool enable = true);
	void stUnknownConv(bool enable = true);
	void setUnInit(bool enable = true);
	void setUnknownOp(bool enable = true);
	void setUnknownType(bool enable = true);

	bool isValid() const;
	bool isNotValid() const;
	bool isInvalid() const;
	bool isTransient() const;
	bool isExpired() const;
	bool isUncertain() const;
	bool isIndeterminable() const;
	bool isError() const;
	VALidityStatus status() const;

	const VALidity& operator=(const VALidity& rhs);
	const VALidity& operator|=(const VALidity& rhs);
	const VALidity& operator&=(const VALidity& rhs);
	VALidity operator|(const VALidity& rhs) const;
	VALidity operator&(const VALidity& rhs) const;
	int operator==(const VALidity& rhs) const;
	int operator!=(const VALidity& rhs) const;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// VALtype class

class AFX_EXT_CLASS VALtype : public CObject
{
	// Construction
public:
	VALtype();
	VALtype(int inum);
	VALtype(LONGLONG inum);
	VALtype(unsigned int unum);
	VALtype(ULONGLONG unum);
	VALtype(float fnum);
	VALtype(double dnum);
	VALtype(LPCSTR txt);
	VALtype(LPCWSTR txt);
	VALtype(const TDSsunTime& tm);
	VALtype(void* ptr);
	VALtype(const char* data, unsigned int len);

	// Attributes
private:
	enum {
		none = 0,
		int64,
		uint64,
		flt,
		dbl,
		string,
		time,
		pointer,
		octets
	};
	unsigned int  m_type;
private:
	LONGLONG  m_inum;
	ULONGLONG  m_unum;
	float  m_fnum;
	double  m_dnum;
	CString  m_txt;
	TDSsunTime  m_time;
	void*  m_ptr;
	const char*  m_data;
	unsigned int  m_datalen;

	// Operations
public:
	void setValue(int inum);
	void setValue(LONGLONG inum);
	void setValue(unsigned int unum);
	void setValue(ULONGLONG unum);
	void setValue(float fnum);
	void setValue(double dnum);
	void setValue(LPCSTR txt);
	void setValue(LPCWSTR txt);
	void setValue(const TDSsunTime &tm);
	void setValue(void* ptr);
	void setValue(const char* data, unsigned int len);
	bool getValue(int& inum) const;
	bool getValue(LONGLONG& inum) const;
	bool getValue(unsigned int& unum) const;
	bool getValue(ULONGLONG& unum) const;
	bool getValue(float& fnum) const;
	bool getValue(double& dnum) const;
	bool getValue(CString& txt) const;
	bool getValue(TDSsunTime& tm) const;
	bool getValue(void** ptr) const;
	bool getValue(const char*& data, unsigned int& len) const;
	bool isInteger() const;
	bool isUInteger() const;
	bool isFloat() const;
	bool isDouble() const;
	bool isString() const;
	bool isTime() const;
	bool isPointer() const;
	bool isOctets() const;

	VALtype& operator=(const VALtype& type);
	bool operator==(const VALtype& type) const;
	bool operator!=(const VALtype& type) const;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// VALue class

class AFX_EXT_CLASS VALue : public CObject
{
	// Construction
public:
	VALue();
	VALue(int inum);
	VALue(LONGLONG inum);
	VALue(unsigned int inum);
	VALue(ULONGLONG unum);
	VALue(float fnum);
	VALue(double dnum);
	VALue(LPCSTR txt);
	VALue(LPCWSTR txt);
	VALue(const TDSsunTime& tm);
	VALue(void* ptr);
	VALue(const char* data, unsigned int len);
	inline VALue(const VALue& val);
	inline ~VALue();

	// Attributes
public:
	VALtype  m_value;
	VALidity  m_validity;
private:
	TDSsunTime  m_time;

	// Operations
public:
	inline int asInteger(int& v) const;
	inline int asInteger(LONGLONG& v) const;
	inline int asUInteger(unsigned int& v) const;
	inline int asUInteger(ULONGLONG& v) const;
	inline int asLong(LONGLONG& v) const;
	inline int asULong(ULONGLONG& v) const;
	inline int asFloat(float& v) const;
	inline int asDouble(double& v) const;
	inline int asChars(CString& v) const;
	inline int asAbsTime(TDSsunTime& v) const;
	inline int asDeltaTime(TDSsunTime& v) const;
	inline int isInteger() const;
	inline int isSInteger() const;
	inline int isUInteger() const;
	inline int isArith() const;
	inline int isReal() const;
	inline int isNumber() const;
	inline int isString() const;
	inline int isTime() const;
	inline int isAbsTime() const;
	inline int isDeltaTime() const;
	inline int isPointer() const;
	inline int isOctet() const;

	inline VALue remainder_val(const VALue& op2) const;
	inline VALue power(const VALue& op2) const;
	inline VALue toInteger() const;
	inline VALue toUInteger() const;
	inline VALue toReal() const;
	inline CString string() const;
	inline void* pointer() const;
	inline unsigned int octLen() const;

	inline void setTime(const VALue& val);
	inline void setTime(const TDSsunTime& tm);
	inline void updTime(const VALue& val);
	inline void updTime(const VALue& val1, const VALue& val2);
	inline void updTime(const TDSsunTime& tm);
	const TDSsunTime& time() const;
	TDSsunTime& time();

	VALue& operator=(int inum);
	VALue& operator=(LONGLONG inum);
	VALue& operator=(unsigned int unum);
	VALue& operator=(ULONGLONG unum);
	VALue& operator=(float fnum);
	VALue& operator=(double dnum);
	VALue& operator=(LPCSTR pszText);
	VALue& operator=(LPCWSTR pszText);
	VALue& operator=(TDSsunTime tm);
	inline VALue& operator=(const VALue& rhs);
	inline VALue operator+(const VALue& rhs) const;
	inline VALue operator-(const VALue& rhs) const;
	inline VALue operator*(const VALue& rhs) const;
	inline VALue operator/(const VALue& rhs) const;
	inline VALue operator%(const VALue& rhs) const;
	inline int operator==(const VALue& rhs) const;
	inline int operator!=(const VALue& rhs) const;
	inline int operator<(const VALue& rhs) const;
	inline int operator>(const VALue& rhs) const;
	inline int operator<=(const VALue& rhs) const;
	inline int operator>=(const VALue& rhs) const;
	inline VALue operator&(const VALue& rhs) const;
	inline VALue operator&&(const VALue& rhs) const;
	inline VALue operator|(const VALue& rhs) const;
	inline VALue operator||(const VALue& rhs) const;
	inline VALue operator<<(const VALue& rhs) const;
	inline VALue operator>>(const VALue& rhs) const;
	inline VALue operator^(const VALue& rhs) const;
	inline VALue operator~(void) const;
	inline VALue operator!(void) const;

public:
	static int lessThan(const VALue& op1, const VALue& op2);
	static int grtrThan(const VALue& op1, const VALue& op2);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// VALstring class

class AFX_EXT_CLASS VALstring : public CString
{
	// Construction
public:
	VALstring();
	VALstring(LPCSTR pszText);
	VALstring(LPCWSTR pszText);

	// Attributes
public:

	// Operations
public:
	static CString create(LPCSTR pszText);
	static CString create(LPCWSTR pszText);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __VALue_H__
