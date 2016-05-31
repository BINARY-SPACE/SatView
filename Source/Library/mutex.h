// MUTEX.H : Mutex Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mutex related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/05/20 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MUTEX_H__
#define __MUTEX_H__


/////////////////////////////////////////////////////////////////////////////
// CMutexArray

class AFX_EXT_CLASS CMutexArray : public CPtrArray
{
	// Construction
public:
	CMutexArray();
	~CMutexArray();

	// Attributes
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMutexList

class AFX_EXT_CLASS CMutexList : public CPtrList
{
	// Construction
public:
	CMutexList();
	~CMutexList();

	// Attributes
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Lock();
	BOOL Unlock();
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MUTEX_H__
