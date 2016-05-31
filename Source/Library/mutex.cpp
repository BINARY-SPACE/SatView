// MUTEX.CPP : Mutex Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mutex related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/05/20 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMutexArray

CMutexArray::CMutexArray() : CPtrArray()
{
	m_pCriticalSection = new CCriticalSection;
}

CMutexArray::~CMutexArray()
{
	delete m_pCriticalSection;
}

BOOL CMutexArray::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CMutexArray::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CMutexList

CMutexList::CMutexList() : CPtrList()
{
	m_pCriticalSection = new CCriticalSection;
}

CMutexList::~CMutexList()
{
	delete m_pCriticalSection;
}

BOOL CMutexList::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CMutexList::Unlock()
{
	return m_pCriticalSection->Unlock();
}
