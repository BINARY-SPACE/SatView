// CPU.H : CPU Performance Monitor Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the CPU performance monitor related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/11/28 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __CPU_H__
#define __CPU_H__


/////////////////////////////////////////////////////////////////////////////
// CCPUPerformanceMonitor

#define CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME   (1<<0)
#define CPUPERFORMANCEMONITOR_COUNTER_POOLNONPAGEDBYTES   (1<<1)
#define CPUPERFORMANCEMONITOR_COUNTER_POOLPAGEDBYTES   (1<<2)
#define CPUPERFORMANCEMONITOR_COUNTER_PRIVATEBYTES   (1<<3)
#define CPUPERFORMANCEMONITOR_COUNTER_VIRTUALBYTES   (1<<4)
#define CPUPERFORMANCEMONITOR_COUNTER_THREADCOUNT   (1<<5)
#define CPUPERFORMANCEMONITOR_COUNTER_TOTALPROCESSORTIME   (1<<6)
#define CPUPERFORMANCEMONITOR_COUNTERS   7
#ifndef RC_INVOKED
#define CPUPERFORMANCEMONITOR_COUNTER_ALL   (CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME | CPUPERFORMANCEMONITOR_COUNTER_POOLNONPAGEDBYTES | CPUPERFORMANCEMONITOR_COUNTER_POOLPAGEDBYTES | CPUPERFORMANCEMONITOR_COUNTER_PRIVATEBYTES | CPUPERFORMANCEMONITOR_COUNTER_VIRTUALBYTES | CPUPERFORMANCEMONITOR_COUNTER_THREADCOUNT | CPUPERFORMANCEMONITOR_COUNTER_TOTALPROCESSORTIME)
#endif

class CCPUPerformanceMonitor : public CObject
{
	// Construction
public:
	CCPUPerformanceMonitor();
	~CCPUPerformanceMonitor();

	// Attributes
private:
	CPtrArray  m_hCounters;
	CUIntArray  m_nInstanceIDs;
	PDH_HQUERY  m_hQuery[2];

	// Operations
public:
	BOOL Start(UINT nCounterIDs = CPUPERFORMANCEMONITOR_COUNTER_ALL);
	BOOL Stop(UINT nCounterIDs = CPUPERFORMANCEMONITOR_COUNTER_ALL);

	BOOL Measure(UINT nCounterID, double &fValue);
	CString Measure(UINT nCounterID);

	PDH_HCOUNTER IsAvailable(UINT nCounterID) CONST;

private:
	PDH_HCOUNTER UpdateCounter(UINT nCounterID, BOOL bAdd = TRUE);
	BOOL UpdateCounters(UINT nCounterIDs, BOOL bRemove = FALSE);

	CString ConstructCounterPath(UINT nCounterID, INT nInstanceID) CONST;
	CString ConvertCounterIDToString(UINT nCounterID, BOOL bFormat = TRUE) CONST;
	INT ConvertCounterIDToQuery(UINT nCounterID) CONST;
	INT ConvertCounterIDToIndex(UINT nCounterID) CONST;
	UINT ConvertIndexToCounterID(INT nIndex) CONST;

	INT DetermineInstanceID() CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __CPU_H__
