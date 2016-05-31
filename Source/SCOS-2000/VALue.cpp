// VALue.CPP : SCOS-2000 VAL Subsystem Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the SCOS-2000 VAL
// sub-system related interface.
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
// VALidity

VALidity::VALidity() : CObject()
{
	setAllStates(0);
	setUnInit();
}
VALidity::VALidity(const VALidity& vld)
{
	m_state = vld.m_state;
}

VALidity::~VALidity()
{
	return;
}

void VALidity::setValid()
{
	m_state = 0;
}

void VALidity::setAllStates(unsigned int states)
{
	m_state = states;
}

unsigned int VALidity::getAllStates() const
{
	return m_state;
}

void VALidity::setUnknownCond(bool enable)
{
	m_mask.UnknownCond = enable;
}

void VALidity::setUnknownCriteria(bool enable)
{
	m_mask.UnknownCriteria = enable;
}

void VALidity::setUnknownPkt(bool enable)
{
	m_mask.UnknownPkt = enable;
}

void VALidity::setUnknownState(bool enable)
{
	m_mask.UnknownState = enable;
}

void VALidity::setDivideByZero(bool enable)
{
	m_mask.DivideByZero = enable;
}

void VALidity::setTooEarly(bool enable)
{
	m_mask.TooEarly = enable;
}

void VALidity::setExpired(bool enable)
{
	m_mask.Expired = enable;
}

void VALidity::setFieldAbsent(bool enable)
{
	m_mask.FieldAbsent = enable;
}

void VALidity::setFieldUnknown(bool enable)
{
	m_mask.FieldUnknown = enable;
}

void VALidity::setMIBError(bool enable)
{
	m_mask.MIBerror = enable;
}

void VALidity::setOLparse(bool enable)
{
	m_mask.OLparse = enable;
}

void VALidity::setCalibration(bool enable)
{
	m_mask.Calibration = enable;
}

void VALidity::setOverflow(bool enable)
{
	m_mask.Overflow = enable;
}

void VALidity::setPreserve(bool enable)
{
	m_mask.Preserve = enable;
}

void VALidity::setPoverOff(bool enable)
{
	m_mask.PowerOff = enable;
}

void VALidity::setPktRetr(bool enable)
{
	m_mask.PktRetrv = enable;
}

void VALidity::setRouteOff(bool enable)
{
	m_mask.RouteOff = enable;
}

void VALidity::setStateOff(bool enable)
{
	m_mask.StateOff = enable;
}

void VALidity::setSystemError(bool enable)
{
	m_mask.SystemError = enable;
}

void VALidity::setTransportError1(bool enable)
{
	m_mask.TransportError1 = enable;
}

void VALidity::setTransportError2(bool enable)
{
	m_mask.TransportError2 = enable;
}

void VALidity::setTransportError3(bool enable)
{
	m_mask.TransportError3 = enable;
}

void VALidity::setTransportError4(bool enable)
{
	m_mask.TransportError4 = enable;
}

void VALidity::setTransportError5(bool enable)
{
	m_mask.TransportError5 = enable;
}

void VALidity::setTransportError6(bool enable)
{
	m_mask.TransportError6 = enable;
}

void VALidity::setTransportError7(bool enable)
{
	m_mask.TransportError7 = enable;
}

void VALidity::setTransportError8(bool enable)
{
	m_mask.TransportError8 = enable;
}

void VALidity::setTransient(bool enable)
{
	m_mask.Transient = enable;
}

void VALidity::stUnknownConv(bool enable)
{
	m_mask.UnknownConv = enable;
}

void VALidity::setUnInit(bool enable)
{
	m_mask.UnInit = enable;
}

void VALidity::setUnknownOp(bool enable)
{
	m_mask.UnknownOp = enable;
}

void VALidity::setUnknownType(bool enable)
{
	m_mask.UnknownType = enable;
}

bool VALidity::isValid() const
{
	return(m_state == 0);
}

bool VALidity::isNotValid() const
{
	return(m_state != 0);
}

bool VALidity::isInvalid() const
{
	return(m_mask.StateOff || m_mask.PowerOff || m_mask.RouteOff);
}

bool VALidity::isTransient() const
{
	return(m_mask.Transient);
}

bool VALidity::isExpired() const
{
	return(m_mask.Expired);
}

bool VALidity::isUncertain() const
{
	return(m_mask.TransportError1 || m_mask.TransportError2 || m_mask.TransportError3 || m_mask.TransportError4 || m_mask.TransportError5 || m_mask.TransportError6 || m_mask.TransportError7 || m_mask.TransportError8);
}

bool VALidity::isIndeterminable() const
{
	return(m_mask.UnknownState || m_mask.UnknownCond || m_mask.UnknownCriteria || m_mask.Calibration || m_mask.TooEarly || m_mask.UnknownPkt);
}

bool VALidity::isError() const
{
	return(m_mask.UnInit || m_mask.PktRetrv || m_mask.MIBerror || m_mask.SystemError || m_mask.FieldUnknown || m_mask.FieldAbsent || m_mask.UnknownType || m_mask.UnknownOp || m_mask.UnknownConv || m_mask.Overflow || m_mask.DivideByZero || m_mask.OLparse);
}

VALidityStatus VALidity::status() const
{
	if (isValid()) return VALValid;
	if (isIndeterminable()) return VALindeterm;
	if (isExpired()) return VALexpired;
	if (isUncertain()) return VALuncertain;
	if (isTransient()) return VALtransient;
	if (isInvalid()) return VALinvalid;
	return VALerror;
}

const VALidity& VALidity::operator=(const VALidity& rhs)
{
	m_state = rhs.getAllStates();
	return *this;
}

const VALidity& VALidity::operator|=(const VALidity& rhs)
{
	m_state |= rhs.getAllStates();
	return *this;
}

const VALidity& VALidity::operator&=(const VALidity& rhs)
{
	m_state &= rhs.getAllStates();
	return *this;
}

VALidity VALidity::operator|(const VALidity& rhs) const
{
	VALidity  validity;

	validity.setAllStates(m_state | rhs.getAllStates());
	return validity;
}

VALidity VALidity::operator&(const VALidity& rhs) const
{
	VALidity  validity;

	validity.setAllStates(m_state & rhs.getAllStates());
	return validity;
}

int VALidity::operator==(const VALidity& rhs) const
{
	return(m_state == rhs.getAllStates());
}

int VALidity::operator!=(const VALidity& rhs) const
{
	return(m_state != rhs.getAllStates());
}


/////////////////////////////////////////////////////////////////////////////
// VALtype

VALtype::VALtype() : CObject()
{
	m_type = none;
}
VALtype::VALtype(int inum) : CObject()
{
	setValue(inum);
}
VALtype::VALtype(LONGLONG inum) : CObject()
{
	setValue(inum);
}
VALtype::VALtype(unsigned int unum) : CObject()
{
	setValue(unum);
}
VALtype::VALtype(ULONGLONG unum) : CObject()
{
	setValue(unum);
}
VALtype::VALtype(float fnum) : CObject()
{
	setValue(fnum);
}
VALtype::VALtype(double dnum) : CObject()
{
	setValue(dnum);
}
VALtype::VALtype(LPCSTR txt) : CObject()
{
	setValue(txt);
}
VALtype::VALtype(LPCWSTR txt) : CObject()
{
	setValue(txt);
}
VALtype::VALtype(const TDSsunTime& tm) : CObject()
{
	setValue(tm);
}
VALtype::VALtype(void* val) : CObject()
{
	setValue(val);
}
VALtype::VALtype(const char* data, unsigned int len) : CObject()
{
	setValue(data, len);
}

void VALtype::setValue(int inum)
{
	m_type = int64;
	m_inum = inum;
}
void VALtype::setValue(LONGLONG inum)
{
	m_type = int64;
	m_inum = inum;
}
void VALtype::setValue(unsigned int unum)
{
	m_type = uint64;
	m_unum = unum;
}
void VALtype::setValue(ULONGLONG unum)
{
	m_type = uint64;
	m_unum = unum;
}
void VALtype::setValue(float fnum)
{
	m_type = flt;
	m_fnum = fnum;
}
void VALtype::setValue(double dnum)
{
	m_type = dbl;
	m_dnum = dnum;
}
void VALtype::setValue(LPCSTR txt)
{
	m_type = string;
#ifndef UNICODE
	m_txt = txt;
#else
	MultiByteToWideChar(CP_ACP, 0, txt, -1, m_txt.GetBufferSetLength((INT)strlen(txt)), (INT)strlen(txt) + 1);
	m_txt.ReleaseBuffer();
#endif
}
void VALtype::setValue(LPCWSTR txt)
{
	m_type = string;
#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, txt, -1, m_txt.GetBufferSetLength((INT)wcslen(txt)), (INT)wcslen(txt) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	m_txt.ReleaseBuffer();
#else
	m_txt = txt;
#endif
}
void VALtype::setValue(const TDSsunTime &tm)
{
	m_type = time;
	m_time = tm;
}
void VALtype::setValue(void* ptr)
{
	m_type = pointer;
	m_ptr = ptr;
}
void VALtype::setValue(const char* data, unsigned int len)
{
	m_type = octets;
	m_data = data;
	m_datalen = len;
}

bool VALtype::getValue(int& inum) const
{
	if (isInteger())
	{
		inum = (int)m_inum;
		return true;
	}
	return false;
}
bool VALtype::getValue(LONGLONG& inum) const
{
	if (isInteger())
	{
		inum = m_inum;
		return true;
	}
	return false;
}
bool VALtype::getValue(unsigned int& unum) const
{
	if (isUInteger())
	{
		unum = (unsigned int)m_unum;
		return true;
	}
	return false;
}
bool VALtype::getValue(ULONGLONG& unum) const
{
	if (isUInteger())
	{
		unum = m_unum;
		return true;
	}
	return false;
}
bool VALtype::getValue(float& fnum) const
{
	if (isFloat())
	{
		fnum = m_fnum;
		return true;
	}
	return false;
}
bool VALtype::getValue(double& dnum) const
{
	if (isDouble())
	{
		dnum = m_dnum;
		return true;
	}
	return false;
}
bool VALtype::getValue(CString& txt) const
{
	if (isString())
	{
		txt = m_txt;
		return true;
	}
	return false;
}
bool VALtype::getValue(TDSsunTime& tm) const
{
	if (isTime())
	{
		tm = m_time;
		return true;
	}
	return false;

}
bool VALtype::getValue(void** ptr) const
{
	if (isPointer())
	{
		*ptr = m_ptr;
		return true;
	}
	return false;

}
bool VALtype::getValue(const char*& data, unsigned int& len) const
{
	if (isOctets())
	{
		data = m_data;
		len = m_datalen;
		return true;
	}
	return false;
}

bool VALtype::isInteger() const
{
	return(m_type == int64);
}

bool VALtype::isUInteger() const
{
	return(m_type == uint64);
}

bool VALtype::isFloat() const
{
	return(m_type == flt);
}

bool VALtype::isDouble() const
{
	return(m_type == dbl);
}

bool VALtype::isString() const
{
	return(m_type == string);
}

bool VALtype::isTime() const
{
	return(m_type == time);
}

bool VALtype::isPointer() const
{
	return(m_type == pointer);
}

bool VALtype::isOctets() const
{
	return(m_type == octets);
}

VALtype& VALtype::operator=(const VALtype& type)
{
	m_type = type.m_type;
	m_inum = type.m_inum;
	m_unum = type.m_unum;
	m_fnum = type.m_fnum;
	m_dnum = type.m_dnum;
	m_txt = type.m_txt;
	m_time = type.m_time;
	m_ptr = type.m_ptr;
	m_data = type.m_data;
	m_datalen = type.m_datalen;
	return *this;
}

bool VALtype::operator==(const VALtype& type) const
{
	return(type.m_type == m_type && ((m_type == int64  &&  type.m_inum == m_inum) || (m_type == uint64  &&  type.m_unum == m_unum) || (m_type == flt  &&  type.m_fnum == m_fnum)) || (m_type == dbl  &&  type.m_dnum == m_dnum) || (m_type == string  &&  type.m_txt == m_txt) || (m_type == time  &&  type.m_time == m_time) || (m_type == pointer  &&  type.m_ptr == m_ptr) || (m_type == octets  &&  type.m_datalen == m_datalen  &&  !strncmp(type.m_data, m_data, m_datalen)));
}

bool VALtype::operator!=(const VALtype& type) const
{
	return(type.m_type != m_type || (m_type == int64  &&  type.m_inum != m_inum) || (m_type == uint64  &&  type.m_unum != m_unum) || (m_type == flt  &&  type.m_fnum != m_fnum) || (m_type == dbl  &&  type.m_dnum != m_dnum) || (m_type == string  &&  type.m_txt != m_txt) || (m_type == time  &&  type.m_time != m_time) || (m_type == pointer  &&  type.m_ptr != m_ptr) || (m_type == octets && (type.m_datalen != m_datalen || strncmp(type.m_data, m_data, m_datalen))));
}


/////////////////////////////////////////////////////////////////////////////
// VALue

VALue::VALue() : CObject()
{
	return;
}
VALue::VALue(int inum) : CObject()
{
	m_value.setValue(inum);
}
VALue::VALue(LONGLONG inum) : CObject()
{
	m_value.setValue(inum);
}
VALue::VALue(unsigned int unum) : CObject()
{
	m_value.setValue(unum);
}
VALue::VALue(ULONGLONG unum) : CObject()
{
	m_value.setValue(unum);
}
VALue::VALue(float fnum) : CObject()
{
	m_value.setValue(fnum);
}
VALue::VALue(double dnum) : CObject()
{
	m_value.setValue(dnum);
}
VALue::VALue(LPCSTR txt) : CObject()
{
	m_value.setValue(txt);
}
VALue::VALue(LPCWSTR txt) : CObject()
{
	m_value.setValue(txt);
}
VALue::VALue(const TDSsunTime& tm) : CObject()
{
	m_value.setValue((m_time = tm));
}
VALue::VALue(void* ptr) : CObject()
{
	m_value.setValue(ptr);
}
VALue::VALue(const char* data, unsigned int len) : CObject()
{
	m_value.setValue(data, len);
}
VALue::VALue(const VALue& val) : CObject()
{
	*this = val;
}

VALue::~VALue()
{
	return;
}

int VALue::asInteger(int& v) const
{
	float  fnum;
	double  dnum;
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum))
	{
		v = (int)inum;
		return true;
	}
	if (m_value.getValue(unum))
	{
		v = (int)unum;
		return true;
	}
	if (m_value.getValue(fnum))
	{
		v = (int)fnum;
		return true;
	}
	if (m_value.getValue(dnum))
	{
		v = (int)dnum;
		return true;
	}
	v = 0;
	return false;
}
int VALue::asInteger(LONGLONG& v) const
{
	float  fnum;
	double  dnum;
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum))
	{
		v = inum;
		return true;
	}
	if (m_value.getValue(unum))
	{
		v = unum;
		return true;
	}
	if (m_value.getValue(fnum))
	{
		v = (LONGLONG)fnum;
		return true;
	}
	if (m_value.getValue(dnum))
	{
		v = (LONGLONG)dnum;
		return true;
	}
	v = 0;
	return false;
}

int VALue::asUInteger(unsigned int& v) const
{
	float  fnum;
	double  dnum;
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum))
	{
		v = (unsigned int)inum;
		return true;
	}
	if (m_value.getValue(unum))
	{
		v = (unsigned int)unum;
		return true;
	}
	if (m_value.getValue(fnum))
	{
		v = (unsigned int)fnum;
		return true;
	}
	if (m_value.getValue(dnum))
	{
		v = (unsigned int)dnum;
		return true;
	}
	v = 0;
	return false;
}
int VALue::asUInteger(ULONGLONG& v) const
{
	float  fnum;
	double  dnum;
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum))
	{
		v = inum;
		return true;
	}
	if (m_value.getValue(unum))
	{
		v = unum;
		return true;
	}
	if (m_value.getValue(fnum))
	{
		v = (ULONGLONG)fnum;
		return true;
	}
	if (m_value.getValue(dnum))
	{
		v = (ULONGLONG)dnum;
		return true;
	}
	v = 0;
	return false;
}

int VALue::asLong(LONGLONG& v) const
{
	return asInteger(v);
}

int VALue::asULong(ULONGLONG& v) const
{
	return asUInteger(v);
}

int VALue::asFloat(float& v) const
{
	float  fnum;
	double  dnum;
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum))
	{
		v = (float)inum;
		return true;
	}
	if (m_value.getValue(unum))
	{
		v = (float)unum;
		return true;
	}
	if (m_value.getValue(fnum))
	{
		v = fnum;
		return true;
	}
	if (m_value.getValue(dnum))
	{
		v = (float)dnum;
		return true;
	}
	v = 0.0;
	return false;
}

int VALue::asDouble(double& v) const
{
	float  fnum;
	double  dnum;
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum))
	{
		v = (double)inum;
		return true;
	}
	if (m_value.getValue(unum))
	{
		v = (double)unum;
		return true;
	}
	if (m_value.getValue(fnum))
	{
		v = fnum;
		return true;
	}
	if (m_value.getValue(dnum))
	{
		v = dnum;
		return true;
	}
	v = 0.0;
	return false;
}

int VALue::asChars(CString& v) const
{
	LPCSTR  data;
	unsigned int  len;

	if (m_value.getValue(v)) return true;
	if (m_value.getValue(data, len))
	{
#ifndef UNICODE
		CopyMemory(v.GetBufferSetLength(len), data, len);
		v.ReleaseBuffer();
#else
		MultiByteToWideChar(CP_ACP, 0, data, len, v.GetBufferSetLength(len), len + 1);
		v.ReleaseBuffer();
#endif
		return true;
	}
	return false;
}

int VALue::asAbsTime(TDSsunTime& v) const
{
	TDSsunTime  tm;

	if (m_value.getValue(tm) && tm.isAbsTime())
	{
		v = tm;
		return true;
	}
	return false;
}

int VALue::asDeltaTime(TDSsunTime& v) const
{
	TDSsunTime  tm;

	if (m_value.getValue(tm) && tm.isDeltaTime())
	{
		v = tm;
		return true;
	}
	return false;
}

int VALue::isInteger() const
{
	return m_value.isInteger();
}

int VALue::isSInteger() const
{
	return m_value.isInteger();
}

int VALue::isUInteger() const
{
	return m_value.isUInteger();
}

int VALue::isArith() const
{
	return(m_value.isInteger() || m_value.isUInteger() || m_value.isFloat() || m_value.isDouble());
}

int VALue::isReal() const
{
	return(m_value.isFloat() || m_value.isDouble());
}

int VALue::isNumber() const
{
	return(m_value.isInteger() || m_value.isUInteger() || m_value.isFloat() || m_value.isDouble());
}

int VALue::isString() const
{
	return m_value.isString();
}

int VALue::isTime() const
{
	return m_value.isTime();
}

int VALue::isAbsTime() const
{
	return m_time.isAbsTime();
}

int VALue::isDeltaTime() const
{
	return m_time.isDeltaTime();
}

int VALue::isPointer() const
{
	return m_value.isPointer();
}

int VALue::isOctet() const
{
	return m_value.isOctets();
}

VALue VALue::remainder_val(const VALue& op2) const
{
	VALue op1(*this);

	return(op1 - op1%op2);
}

VALue VALue::power(const VALue& op2) const
{
	float  fnum[2];
	double  dnum[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (op2.m_value.getValue(inum[1]))
	{
		if (m_value.getValue(inum[0])) return pow((double)inum[0], (double)inum[1]);
		if (m_value.getValue(unum[0])) return pow((double)unum[0], (double)inum[1]);
		if (m_value.getValue(fnum[0])) return pow((double)fnum[0], (double)inum[1]);
		if (m_value.getValue(dnum[0])) return pow(dnum[0], (double)inum[1]);
		return VALue();
	}
	if (op2.m_value.getValue(unum[1]))
	{
		if (m_value.getValue(inum[0])) return((LONGLONG)pow((double)inum[0], (double)unum[1]));
		if (m_value.getValue(unum[0])) return((ULONGLONG)pow((double)unum[0], (double)unum[1]));
		if (m_value.getValue(fnum[0])) return((float)pow((double)fnum[0], (double)unum[1]));
		if (m_value.getValue(dnum[0])) return pow(dnum[0], (double)unum[1]);
		return VALue();
	}
	if (op2.m_value.getValue(fnum[1]))
	{
		if (m_value.getValue(inum[0])) return pow((double)inum[0], (double)fnum[1]);
		if (m_value.getValue(unum[0])) return pow((double)unum[0], (double)fnum[1]);
		if (m_value.getValue(fnum[0])) return pow((double)fnum[0], (double)fnum[1]);
		if (m_value.getValue(dnum[0])) return pow(dnum[0], (double)fnum[1]);
		return VALue();
	}
	if (op2.m_value.getValue(dnum[1]))
	{
		if (m_value.getValue(inum[0])) return pow((double)inum[0], dnum[1]);
		if (m_value.getValue(unum[0])) return pow((double)unum[0], dnum[1]);
		if (m_value.getValue(fnum[0])) return pow((double)fnum[0], dnum[1]);
		if (m_value.getValue(dnum[0])) return pow(dnum[0], dnum[1]);
	}
	return VALue();
}

VALue VALue::toInteger() const
{
	LONGLONG  inum;

	if (asInteger(inum)) return inum;
	return VALue();
}

VALue VALue::toUInteger() const
{
	ULONGLONG  unum;

	if (asUInteger(unum)) return unum;
	return VALue();
}

VALue VALue::toReal() const
{
	double  dnum;

	if (asDouble(dnum)) return dnum;
	return VALue();
}

CString VALue::string() const
{
	CString  txt;

	if (asChars(txt)) return txt;
	return EMPTYSTRING;
}

void* VALue::pointer() const
{
	LPVOID  ptr;
	LPCSTR  data;
	unsigned int  len;

	if (m_value.getValue(&ptr)) return ptr;
	if (m_value.getValue(data, len)) return((void *)data);
	return((void *)NULL);
}

unsigned int VALue::octLen() const
{
	LPCSTR  data;
	unsigned int  len;

	return((m_value.getValue(data, len)) ? len : 0);
}

void VALue::setTime(const VALue& val)
{
	TDSsunTime  tm;

	if (val.m_value.getValue(tm)) m_value.setValue((m_time = tm));
}
void VALue::setTime(const TDSsunTime& tm)
{
	m_value.setValue((m_time = tm));
}

void VALue::updTime(const VALue& val)
{
	TDSsunTime  tm[2];

	if (val.m_value.getValue(tm[0]) && m_value.getValue(tm[1])) setTime(max(tm[0], tm[1]));
}
void VALue::updTime(const VALue& val1, const VALue& val2)
{
	TDSsunTime  tm[3];

	if (val1.m_value.getValue(tm[0]) && val2.m_value.getValue(tm[1]) && m_value.getValue(tm[2])) setTime(max(tm[0], max(tm[1], tm[2])));
}
void VALue::updTime(const TDSsunTime& tm)
{
	if (m_time < tm) setTime(tm);
}

const TDSsunTime& VALue::time() const
{
	return m_time;
}

TDSsunTime& VALue::time()
{
	return m_time;
}

VALue& VALue::operator=(int inum)
{
	m_value.setValue(inum);
	return *this;
}

VALue& VALue::operator=(LONGLONG inum)
{
	m_value.setValue(inum);
	return *this;
}

VALue& VALue::operator=(unsigned int inum)
{
	m_value.setValue(inum);
	return *this;
}

VALue& VALue::operator=(ULONGLONG unum)
{
	m_value.setValue(unum);
	return *this;
}

VALue& VALue::operator=(float fnum)
{
	m_value.setValue(fnum);
	return *this;
}

VALue& VALue::operator=(double dnum)
{
	m_value.setValue(dnum);
	return *this;
}

VALue& VALue::operator=(LPCSTR pszText)
{
	m_value.setValue(pszText);
	return *this;
}

VALue& VALue::operator=(LPCWSTR pszText)
{
	m_value.setValue(pszText);
	return *this;
}

VALue& VALue::operator=(TDSsunTime tm)
{
	m_value.setValue(tm);
	return *this;
}

VALue& VALue::operator=(const VALue& rhs)
{
	m_value = rhs.m_value;
	m_validity = rhs.m_validity;
	m_time = rhs.m_time;
	return *this;
}

VALue VALue::operator+(const VALue& rhs) const
{
	float  fnum[2];
	double  dnum[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];
	TDSsunTime  tm[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] + inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] + unum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(fnum[1])) return(inum[0] + fnum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(dnum[1])) return(inum[0] + dnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] + unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] + inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(fnum[1])) return(unum[0] + fnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(dnum[1])) return(unum[0] + dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(fnum[1])) return(fnum[0] + fnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(dnum[1])) return(fnum[0] + dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(inum[1])) return(fnum[0] + inum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(unum[1])) return(fnum[0] + unum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(dnum[1])) return(dnum[0] + dnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(fnum[1])) return(dnum[0] + fnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(inum[1])) return(dnum[0] + inum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(unum[1])) return(dnum[0] + unum[1]);
	if (m_value.getValue(tm[0]) && rhs.m_value.getValue(tm[1])) return(tm[0] + tm[1]);
	return VALue();
}

VALue VALue::operator-(const VALue& rhs) const
{
	float  fnum[2];
	double  dnum[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];
	TDSsunTime  tm[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] - inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] - unum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(fnum[1])) return(inum[0] - fnum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(dnum[1])) return(inum[0] - dnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] - unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] - inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(fnum[1])) return(unum[0] - fnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(dnum[1])) return(unum[0] - dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(fnum[1])) return(fnum[0] - fnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(dnum[1])) return(fnum[0] - dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(inum[1])) return(fnum[0] - inum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(unum[1])) return(fnum[0] - unum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(dnum[1])) return(dnum[0] - dnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(fnum[1])) return(dnum[0] - fnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(inum[1])) return(dnum[0] - inum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(unum[1])) return(dnum[0] - unum[1]);
	if (m_value.getValue(tm[0]) && rhs.m_value.getValue(tm[1])) return(tm[0] - tm[1]);
	return VALue();
}

VALue VALue::operator*(const VALue& rhs) const
{
	float  fnum[2];
	double  dnum[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];
	TDSsunTime  tm[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] * inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] * unum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(fnum[1])) return(inum[0] * fnum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(dnum[1])) return(inum[0] * dnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] * unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] * inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(fnum[1])) return(unum[0] * fnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(dnum[1])) return(unum[0] * dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(fnum[1])) return(fnum[0] * fnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(dnum[1])) return(fnum[0] * dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(inum[1])) return(fnum[0] * inum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(unum[1])) return(fnum[0] * unum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(dnum[1])) return(dnum[0] * dnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(fnum[1])) return(dnum[0] * fnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(inum[1])) return(dnum[0] * inum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(unum[1])) return(dnum[0] * unum[1]);
	if (m_value.getValue(tm[0]) && rhs.m_value.getValue(inum[1])) return(tm[0] * inum[1]);
	if (m_value.getValue(tm[0]) && rhs.m_value.getValue(unum[1])) return(tm[0] * unum[1]);
	return VALue();
}

VALue VALue::operator/(const VALue& rhs) const
{
	float  fnum[2];
	double  dnum[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];
	TDSsunTime  tm[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1]) && inum[1] != 0) return(inum[0] / inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1]) && unum[1] != 0) return(inum[0] / unum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(fnum[1]) && fnum[1] != 0.0) return(inum[0] / fnum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(dnum[1]) && dnum[1] != 0.0) return(inum[0] / dnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1]) && unum[1] != 0) return(unum[0] / unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1]) && inum[1] != 0) return(unum[0] / inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(fnum[1]) && fnum[1] != 0.0) return(unum[0] / fnum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(dnum[1]) && dnum[1] != 0.0) return(unum[0] / dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(fnum[1]) && fnum[1] != 0.0) return(fnum[0] / fnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(dnum[1]) && dnum[1] != 0.0) return(fnum[0] / dnum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(inum[1]) && inum[1] != 0) return(fnum[0] / inum[1]);
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(unum[1]) && unum[1] != 0) return(fnum[0] / unum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(dnum[1]) && dnum[1] != 0.0) return(dnum[0] / dnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(fnum[1]) && fnum[1] != 0.0) return(dnum[0] / fnum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(inum[1]) && inum[1] != 0) return(dnum[0] / inum[1]);
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(unum[1]) && unum[1] != 0) return(dnum[0] / unum[1]);
	if (m_value.getValue(tm[0]) && rhs.m_value.getValue(inum[1])) return(tm[0] / inum[1]);
	if (m_value.getValue(tm[0]) && rhs.m_value.getValue(unum[1])) return(tm[0] / unum[1]);
	return VALue();
}

VALue VALue::operator%(const VALue& rhs) const
{
	float  fnum[2];
	double  dnum[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] % inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] % unum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(fnum[1])) return(fmod((double)inum[0], (double)fnum[1]));
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(dnum[1])) return(fmod((double)inum[0], dnum[1]));
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] % inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] % unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(fnum[1])) return(fmod((double)unum[0], (double)fnum[1]));
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(dnum[1])) return(fmod((double)unum[0], dnum[1]));
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(fnum[1])) return(fmod(fnum[0], fnum[1]));
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(dnum[1])) return(fmod((double)fnum[0], dnum[1]));
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(inum[1])) return(fmod((double)fnum[0], (double)inum[1]));
	if (m_value.getValue(fnum[0]) && rhs.m_value.getValue(unum[1])) return(fmod((double)fnum[0], (double)unum[1]));
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(dnum[1])) return(fmod(dnum[0], dnum[1]));
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(fnum[1])) return(fmod(dnum[0], (double)fnum[1]));
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(inum[1])) return(fmod(dnum[0], (double)inum[1]));
	if (m_value.getValue(dnum[0]) && rhs.m_value.getValue(unum[1])) return(fmod(dnum[0], (double)unum[1]));
	return VALue();
}

int VALue::operator==(const VALue& rhs) const
{
	return(rhs.m_value == m_value);
}

int VALue::operator!=(const VALue& rhs) const
{
	return(rhs.m_value != m_value);
}

int VALue::operator<(const VALue& rhs) const
{
	return lessThan(*this, rhs);
}

int VALue::operator>(const VALue& rhs) const
{
	return grtrThan(*this, rhs);
}

int VALue::operator<=(const VALue& rhs) const
{
	return(lessThan(*this, rhs) || rhs.m_value == m_value);
}

int VALue::operator>=(const VALue& rhs) const
{
	return(grtrThan(*this, rhs) || rhs.m_value == m_value);
}

VALue VALue::operator&(const VALue& rhs) const
{
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] & inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] & unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] & inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] & unum[1]);
	return VALue();
}

VALue VALue::operator&&(const VALue& rhs) const
{
	LPVOID  ptr[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return((LONGLONG)(inum[0] != 0 && inum[1] != 0));
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return((LONGLONG)(inum[0] != 0 && unum[1] != 0));
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return((LONGLONG)(unum[0] != 0 && inum[1] != 0));
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return((LONGLONG)(unum[0] != 0 && unum[1] != 0));
	if (m_value.getValue(&ptr[0]) && rhs.m_value.getValue(&ptr[1])) return((LONGLONG)(ptr[0] != 0 && ptr[1] != 0));
	return VALue();
}

VALue VALue::operator|(const VALue& rhs) const
{
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] | inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] | unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] | inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] | unum[1]);
	return VALue();
}

VALue VALue::operator||(const VALue& rhs) const
{
	LPVOID  ptr[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return((LONGLONG)(inum[0] != 0 || inum[1] != 0));
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return((LONGLONG)(inum[0] != 0 || unum[1] != 0));
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return((LONGLONG)(unum[0] != 0 || inum[1] != 0));
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return((LONGLONG)(unum[0] != 0 || unum[1] != 0));
	if (m_value.getValue(&ptr[0]) && rhs.m_value.getValue(&ptr[1])) return((LONGLONG)(ptr[0] != 0 || ptr[1] != 0));
	return VALue();
}

VALue VALue::operator<<(const VALue& rhs) const
{
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] << inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] << unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] << inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] << unum[1]);
	return VALue();
}

VALue VALue::operator>>(const VALue& rhs) const
{
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] >> inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] >> unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] >> inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] >> unum[1]);
	return VALue();
}

VALue VALue::operator^(const VALue& rhs) const
{
	LONGLONG  inum[2];
	ULONGLONG  unum[2];

	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(inum[1])) return(inum[0] ^ inum[1]);
	if (m_value.getValue(inum[0]) && rhs.m_value.getValue(unum[1])) return(inum[0] ^ unum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(inum[1])) return(unum[0] ^ inum[1]);
	if (m_value.getValue(unum[0]) && rhs.m_value.getValue(unum[1])) return(unum[0] ^ unum[1]);
	return VALue();
}

VALue VALue::operator~(void) const
{
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum)) return(~inum);
	if (m_value.getValue(unum)) return(~unum);
	return VALue();
}

VALue VALue::operator!(void) const
{
	float  fnum;
	double  dnum;
	LONGLONG  inum;
	ULONGLONG  unum;

	if (m_value.getValue(inum)) return((LONGLONG)(inum == 0));
	if (m_value.getValue(unum)) return((LONGLONG)(unum == 0));
	if (m_value.getValue(fnum)) return((LONGLONG)(fnum == 0.0));
	if (m_value.getValue(dnum)) return((LONGLONG)(dnum == 0.0));
	return VALue();
}

int VALue::lessThan(const VALue& op1, const VALue& op2)
{
	int  result;
	float  fnum[2];
	LPVOID  ptr[2];
	double  dnum[2];
	LPCSTR  data[2];
	CString  txt[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];
	TDSsunTime  tm[2];
	unsigned int  len[2];

	if (op1.m_value.getValue(inum[0]) && op2.m_value.getValue(inum[1])) return(inum[0] < inum[1]);
	if (op1.m_value.getValue(inum[0]) && op2.asInteger(inum[1])) return(inum[0] < inum[1]);
	if (op2.m_value.getValue(inum[1]) && op1.asInteger(inum[0])) return(inum[0] < inum[1]);
	if (op1.m_value.getValue(unum[0]) && op2.m_value.getValue(unum[1])) return(unum[0] < unum[1]);
	if (op1.m_value.getValue(unum[0]) && op2.asUInteger(unum[1])) return(unum[0] < unum[1]);
	if (op2.m_value.getValue(unum[1]) && op1.asUInteger(unum[0])) return(unum[0] < unum[1]);
	if (op1.m_value.getValue(fnum[0]) && op2.m_value.getValue(fnum[1])) return(fnum[0] < fnum[1]);
	if (op1.m_value.getValue(fnum[0]) && op2.asFloat(fnum[1])) return(fnum[0] < fnum[1]);
	if (op2.m_value.getValue(fnum[1]) && op1.asFloat(fnum[0])) return(fnum[0] < fnum[1]);
	if (op1.m_value.getValue(dnum[0]) && op2.m_value.getValue(dnum[1])) return(dnum[0] < dnum[1]);
	if (op1.m_value.getValue(dnum[0]) && op2.asDouble(dnum[1])) return(dnum[0] < dnum[1]);
	if (op2.m_value.getValue(dnum[1]) && op1.asDouble(dnum[0])) return(dnum[0] < dnum[1]);
	if (op1.m_value.getValue(txt[0]) && op2.m_value.getValue(txt[1])) return(txt[0] < txt[1]);
	if (op1.m_value.getValue(tm[0]) && op2.m_value.getValue(tm[1])) return(tm[0] < tm[1]);
	if (op1.m_value.getValue(&ptr[0]) && op2.m_value.getValue(&ptr[1])) return(ptr[0] < ptr[1]);
	if (op1.m_value.getValue(data[0], len[0]) && op2.m_value.getValue(data[1], len[1])) return(((result = strncmp(data[0], data[1], min(len[0], len[1]))) < 0 || (!result  &&  len[0] < len[1])));
	return -1;
}

int VALue::grtrThan(const VALue& op1, const VALue& op2)
{
	int  result;
	float  fnum[2];
	LPVOID  ptr[2];
	double  dnum[2];
	LPCSTR  data[2];
	CString  txt[2];
	LONGLONG  inum[2];
	ULONGLONG  unum[2];
	TDSsunTime  tm[2];
	unsigned int  len[2];

	if (op1.m_value.getValue(inum[0]) && op2.m_value.getValue(inum[1])) return(inum[0] > inum[1]);
	if (op1.m_value.getValue(inum[0]) && op2.asInteger(inum[1])) return(inum[0] > inum[1]);
	if (op2.m_value.getValue(inum[1]) && op1.asInteger(inum[0])) return(inum[0] > inum[1]);
	if (op1.m_value.getValue(unum[0]) && op2.m_value.getValue(unum[1])) return(unum[0] > unum[1]);
	if (op1.m_value.getValue(unum[0]) && op2.asUInteger(unum[1])) return(unum[0] > unum[1]);
	if (op2.m_value.getValue(unum[1]) && op1.asUInteger(unum[0])) return(unum[0] > unum[1]);
	if (op1.m_value.getValue(fnum[0]) && op2.m_value.getValue(fnum[1])) return(fnum[0] > fnum[1]);
	if (op1.m_value.getValue(fnum[0]) && op2.asFloat(fnum[1])) return(fnum[0] > fnum[1]);
	if (op2.m_value.getValue(fnum[1]) && op1.asFloat(fnum[0])) return(fnum[0] > fnum[1]);
	if (op1.m_value.getValue(dnum[0]) && op2.m_value.getValue(dnum[1])) return(dnum[0] > dnum[1]);
	if (op1.m_value.getValue(dnum[0]) && op2.asDouble(dnum[1])) return(dnum[0] > dnum[1]);
	if (op2.m_value.getValue(dnum[1]) && op1.asDouble(dnum[0])) return(dnum[0] > dnum[1]);
	if (op1.m_value.getValue(txt[0]) && op2.m_value.getValue(txt[1])) return(txt[0] > txt[1]);
	if (op1.m_value.getValue(tm[0]) && op2.m_value.getValue(tm[1])) return(tm[0] > tm[1]);
	if (op1.m_value.getValue(&ptr[0]) && op2.m_value.getValue(&ptr[1])) return(ptr[0] > ptr[1]);
	if (op1.m_value.getValue(data[0], len[0]) && op2.m_value.getValue(data[1], len[1])) return(((result = strncmp(data[0], data[1], min(len[0], len[1]))) > 0 || (!result  &&  len[0] > len[1])));
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
// VALstring class

VALstring::VALstring() : CString()
{
	return;
}
VALstring::VALstring(LPCSTR pszText) : CString()
{
	CString  szText;

#ifndef UNICODE
	Append(pszText);
#else
	MultiByteToWideChar(CP_ACP, 0, pszText, -1, szText.GetBufferSetLength((INT)strlen(pszText)), (INT)strlen(pszText) + 1);
	szText.ReleaseBuffer();
	Append(szText);
#endif
}
VALstring::VALstring(LPCWSTR pszText) : CString()
{
	CString  szText;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszText, -1, szText.GetBufferSetLength((INT)strlen(pszText)), (INT)strlen(pszText) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	szText.ReleaseBuffer();
	Append(szText);
#else
	Append(pszText);
#endif
}

CString VALstring::create(LPCSTR pszText)
{
	return pszText;
}
CString VALstring::create(LPCWSTR pszText)
{
	return pszText;
}
