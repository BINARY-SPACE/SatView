// Spacecraft.h : This file is part of the SpaceEngine DLL.
// Copyright© 1992-2023 by BINARY SPACE, Switzerland.
// All rights reserved.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2014/08/13 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SPACECRAFT_H__
#define __SPACECRAFT_H__

#ifndef RC_INVOKED
#include <memory>

#include "timekey.h"

#include "coreLib.h"
#include "orbitLib.h"
#include "trackLib.h"
#endif


/////////////////////////////////////////////////////////////////////////////
// CSpacecraft

class AFX_EXT_CLASS CSpacecraft : public CObject
{
	// Construction
public:
	CSpacecraft();
	CSpacecraft(CONST cTle &cTle);
	CSpacecraft(CONST CSpacecraft *pSpacecraft, BOOL bOrbit = FALSE);
	~CSpacecraft();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbAlias;
		UINT  nNumber;
		BOOL  bLabel;
		BOOL  bOrbitData;
		BOOL  bOrbitPlot;
		BOOL  bOrbitObserverFrame;
		BOOL  bOrbitGroundVisibility;
		UINT  nOrbitPlotSamples;
		COLORREF  nLabelColor;
		COLORREF  nOrbitPlotColor;
		TIMEKEY  tOrbitPlotDuration[2];
		double  fOrbitPlotThickness;
		double  fOrbitPlotFade;
		BOOL  bOrbitDebris;
		BOOL  bVisible;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szAlias;
	UINT  m_nNumber;
private:
	BOOL  m_bLabel;
	BOOL  m_bOrbitData;
	BOOL  m_bOrbitPlot;
	BOOL  m_bOrbitObserverFrame;
	BOOL  m_bOrbitGroundVisibility;
	UINT  m_nOrbitPlotSamples;
	COLORREF  m_nLabelColor;
	COLORREF  m_nOrbitPlotColor;
	CTimeSpan  m_tOrbitPlotDuration[2];
	double  m_fOrbitPlotThickness;
	double  m_fOrbitPlotFade;
	BOOL  m_bOrbitDebris;
	BOOL  m_bVisible;
private:
	CString  m_szTLE[3];
	cSatellite  *m_pOrbit;
	CTimeKey  m_tOrbitTime;
	double  m_fLongitude;
	double  m_fLatitude;
	double  m_fAltitude;
	double  m_fSpeed;
private:
	CArray<CSpacecraft *>  m_pDebris;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAlias(LPCTSTR pszAlias);
	CString GetAlias() CONST;
	VOID SetNumber(UINT nNumber);
	UINT GetNumber() CONST;
	VOID EnableLabel(BOOL bEnable = TRUE);
	BOOL IsLabelEnabled() CONST;
	VOID SetLabelColor(COLORREF nColor);
	COLORREF GetLabelColor() CONST;
	VOID EnableOrbitPlot(BOOL bEnable = TRUE);
	BOOL IsOrbitPlotEnabled() CONST;
	VOID SetOrbitPlotColor(COLORREF nColor);
	COLORREF GetOrbitPlotColor() CONST;
	VOID SetOrbitPlotDuration(CONST CTimeSpan &tDuration, BOOL bPast = TRUE);
	CTimeSpan GetOrbitPlotDuration(BOOL bPast = TRUE) CONST;
	VOID SetOrbitPlotSamples(UINT nSamples);
	UINT GetOrbitPlotSamples() CONST;
	VOID SetOrbitPlotThickness(double fThickness);
	double GetOrbitPlotThickness() CONST;
	VOID SetOrbitPlotFade(double fFade);
	double GetOrbitPlotFade() CONST;
	VOID UseOrbitObserverFrame(BOOL bUse = TRUE);
	BOOL IsOrbitObserverFrameUsed() CONST;
	VOID EnableOrbitGroundVisibility(BOOL bEnable = TRUE);
	BOOL IsOrbitGroundVisibilityEnabled() CONST;
	VOID EnableOrbitDataMonitoring(BOOL bEnable = TRUE);
	BOOL IsOrbitDataMonitoringEnabled() CONST;

	BOOL UpdateOrbitPosition(CONST CTimeKey &tTime);
	CTimeKey GetOrbitPosition(double &fLongitude, double &fLatitude, double &fAltitude, double &fSpeed) CONST;

	BOOL UpdateTLEData(CONST cTle &cTle);
	BOOL UpdateTLEData(CONST CSpacecraft *pSpacecraft);
	CTimeKey GetTLEEpoch() CONST;
	CString GetTLELine0() CONST;
	CString GetTLELine1() CONST;
	CString GetTLELine2() CONST;
	cTle GetTLEData() CONST;

	double GetOrbitInclination() CONST;
	double GetOrbitEccentricity() CONST;
	double GetOrbitRAAN() CONST;
	double GetOrbitArgPerigee() CONST;
	double GetOrbitBStar() CONST;
	double GetOrbitDrag() CONST;
	double GetOrbitMeanAnomaly() CONST;
	double GetOrbitMajorAxis() CONST;
	double GetOrbitMinorAxis() CONST;
	double GetOrbitPerigee() CONST;
	double GetOrbitApogee() CONST;
	double GetOrbitMeanMotion() CONST;
	double GetOrbitPeriod() CONST;

	double GetLaunchTime() CONST;

	BOOL SetDebris(CONST CArray<CSpacecraft *> &pDebris);
	BOOL GetDebris(CArray<CSpacecraft *> &pDebris) CONST;
	BOOL IsDebris() CONST;

	VOID MakeVisible(BOOL bVisible = TRUE);
	BOOL IsVisible() CONST;

	BOOL IsInitialized() CONST;

	BOOL Copy(CONST CSpacecraft *pSpacecraft, BOOL bOrbit = FALSE);
	BOOL Compare(CONST CSpacecraft *pSpacecraft, BOOL bOrbit = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftCollection

class AFX_EXT_CLASS CSpacecraftCollection : public CArray<CSpacecraft *>
{
	// Construction
public:
	CSpacecraftCollection();
	~CSpacecraftCollection();

	// Attributes
private:
	BOOL  m_bSorted[2];

	// Operations
public:
	INT Add(CSpacecraft *pSpacecraft);

	INT Find(LPCTSTR pszName, UINT nNumber, BOOL bAlias = FALSE) CONST;
	INT Find(LPCTSTR pszName, BOOL bAlias = FALSE) CONST;
	INT Find(UINT nNumber) CONST;

	CSpacecraft *GetAt(INT nIndex) CONST;
	CSpacecraft *operator[](INT nIndex) CONST;

	BOOL SortByName();
	BOOL IsSortedByName() CONST;
	BOOL SortByNumber();
	BOOL IsSortedByNumber() CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CSpacecraftCollection &pSpacecraftCollection, BOOL bOrbitPosition = FALSE);
	BOOL Compare(CONST CSpacecraftCollection &pSpacecraftCollection, BOOL bOrbitPosition = FALSE) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, UINT nNumber, BOOL bInsert = FALSE) CONST;
	INT FindIndex(UINT nNumber, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftPosition

class AFX_EXT_CLASS CSpacecraftPosition : public CObject
{
	// Construction
public:
	CSpacecraftPosition();
	CSpacecraftPosition(double x, double y, double z);
	CSpacecraftPosition(CONST CSpacecraftPosition &cPosition);

	// Attributes
public:
	double  m_x;
	double  m_y;
	double  m_z;

	// Operations
public:
	double Distance() CONST;

	CSpacecraftPosition &operator=(CONST CSpacecraftPosition &cPosition);
	CSpacecraftPosition &operator+=(CONST CSpacecraftPosition &cPosition);
	CSpacecraftPosition &operator-=(CONST CSpacecraftPosition &cPosition);
	CSpacecraftPosition operator+(CONST CSpacecraftPosition &cPosition) CONST;
	CSpacecraftPosition operator-(CONST CSpacecraftPosition &cPosition) CONST;
	BOOL operator==(CONST CSpacecraftPosition &cPosition) CONST;
	BOOL operator!=(CONST CSpacecraftPosition &cPosition) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftVelocity

class AFX_EXT_CLASS CSpacecraftVelocity : public CObject
{
	// Construction
public:
	CSpacecraftVelocity();
	CSpacecraftVelocity(double x, double y, double z);
	CSpacecraftVelocity(CONST CSpacecraftVelocity &cVelocity);

	// Attributes
public:
	double  m_x;
	double  m_y;
	double  m_z;

	// Operations
public:
	double Speed() CONST;

	CSpacecraftVelocity &operator=(CONST CSpacecraftVelocity &cVelocity);
	CSpacecraftVelocity &operator+=(CONST CSpacecraftVelocity &cVelocity);
	CSpacecraftVelocity &operator-=(CONST CSpacecraftVelocity &cVelocity);
	CSpacecraftVelocity operator+(CONST CSpacecraftVelocity &cVelocity) CONST;
	CSpacecraftVelocity operator-(CONST CSpacecraftVelocity &cVelocity) CONST;
	BOOL operator==(CONST CSpacecraftVelocity &cVelocity) CONST;
	BOOL operator!=(CONST CSpacecraftVelocity &cVelocity) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftState

class AFX_EXT_CLASS CSpacecraftState : public CObject
{
	// Construction
public:
	CSpacecraftState();
	CSpacecraftState(double x, double y, double z, double vx, double vy, double vz);

	// Attributes
private:
	CSpacecraftPosition  m_cPosition;
	CSpacecraftVelocity  m_cVelocity;

	// Operations
public:
	CSpacecraftPosition GetPosition() CONST;
	CSpacecraftVelocity GetVelocity() CONST;

	CSpacecraftState &operator=(CONST CSpacecraftState &cState);
	BOOL operator==(CONST CSpacecraftState &cState) CONST;
	BOOL operator!=(CONST CSpacecraftState &cState) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftPassPeriod

class AFX_EXT_CLASS CSpacecraftPassPeriod : public CObject
{
	// Construction
public:
	CSpacecraftPassPeriod();

	// Attributes
public:
	enum PassPhase
	{
		Start = 0,
		Maximum = 1,
		End = 2
	};
private:
	CTimeKey  m_tPeriod[3];
	double  m_fAzimuth[3];
	double  m_fElevation;

	// Operations
public:
	VOID SetPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tMaxTime, CONST CTimeKey &tStopTime);
	BOOL GetPeriod(CTimeKey &tStartTime, CTimeKey &tMaxTime, CTimeKey &tStopTime) CONST;
	CTimeSpan GetPeriodDuration() CONST;
	CTimeKey GetStartTime() CONST;
	CTimeKey GetMaximumTime() CONST;
	CTimeKey GetStopTime() CONST;
	VOID SetDirection(PassPhase nPhase, double fAzimuth, double fElevation = 0.0);
	VOID GetDirection(PassPhase nPhase, double &fAzimuth, double &fElevation) CONST;

	VOID Copy(CONST CSpacecraftPassPeriod *pPeriod);
	BOOL Compare(CONST CSpacecraftPassPeriod *pPeriod) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftPassPeriods

class AFX_EXT_CLASS CSpacecraftPassPeriods : public CArray<CSpacecraftPassPeriod *>
{
	// Construction
public:
	CSpacecraftPassPeriods();
	~CSpacecraftPassPeriods();

	// Attributes
public:

	// Operations
public:
	INT Add(CSpacecraftPassPeriod *pPeriod);

	CSpacecraftPassPeriod *GetAt(INT nIndex) CONST;
	CSpacecraftPassPeriod *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CSpacecraftPassPeriods &pPeriods);
	BOOL Compare(CONST CSpacecraftPassPeriods &pPeriods) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftPassLocation

class AFX_EXT_CLASS CSpacecraftPassLocation : public CObject
{
	// Construction
public:
	CSpacecraftPassLocation();
	~CSpacecraftPassLocation();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		double  fLongitude;
		double  fLatitude;
		double  fAltitude;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	double  m_fLongitude;
	double  m_fLatitude;
	double  m_fAltitude;
private:
	CSpacecraftPassPeriods  m_pPeriods;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetLongitude(double fLongitude);
	double GetLongitude() CONST;
	VOID SetLatitude(double fLatitude);
	double GetLatitude() CONST;
	VOID SetAltitude(double fAltitude);
	double GetAltitude() CONST;

	BOOL SetLinkPeriods(CONST CSpacecraftPassPeriods &pPeriods);
	INT GetLinkPeriods(CSpacecraftPassPeriods &pPeriods) CONST;

	BOOL Copy(CONST CSpacecraftPassLocation *pLocation);
	BOOL Compare(CONST CSpacecraftPassLocation *pLocation) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftPassLocations

class AFX_EXT_CLASS CSpacecraftPassLocations : public CArray<CSpacecraftPassLocation *>
{
	// Construction
public:
	CSpacecraftPassLocations();
	~CSpacecraftPassLocations();

	// Attributes
public:

	// Operations
public:
	INT Add(CSpacecraftPassLocation *pLocation);

	INT Find(LPCTSTR pszName) CONST;

	CSpacecraftPassLocation *GetAt(INT nIndex) CONST;
	CSpacecraftPassLocation *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CSpacecraftPassLocations &pLocations);
	BOOL Compare(CONST CSpacecraftPassLocations &pLocations) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftPass

class AFX_EXT_CLASS CSpacecraftPass : public CObject
{
	// Construction
public:
	CSpacecraftPass();
	~CSpacecraftPass();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbSpacecraft;
		INT  cbLocations;
		COLORREF  nLinkColor;
		TIMEKEY  tPeriod[2];
		UINT  nSpacecraft;
		UINT  nLinkWidth;
		BOOL  bShowLink;
		BOOL  bEnabled;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szSpacecraft;
	COLORREF  m_nLinkColor;
	CTimeKey  m_tPeriod[2];
	UINT  m_nSpacecraft;
	UINT  m_nLinkWidth;
	BOOL  m_bShowLink;
	BOOL  m_bEnabled;
private:
	CSpacecraftPassLocations  m_pLocations;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetSpacecraft(LPCTSTR pszName, UINT nNumber);
	CString GetSpacecraft(UINT &nNumber) CONST;
	CString GetSpacecraft() CONST;
	BOOL SetLocations(CONST CSpacecraftPassLocations &pLocations);
	INT GetLocations(CSpacecraftPassLocations &pLocations) CONST;
	VOID SetTimeInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tDuration);
	BOOL GetTimeInterval(CTimeKey &tStartTime, CTimeSpan &tDuration) CONST;
	VOID SetLinkProperties(COLORREF nColor, UINT nWidth);
	BOOL GetLinkProperties(COLORREF &nColor, UINT &nWidth) CONST;
	VOID ShowLink(BOOL bShow = TRUE);
	BOOL IsLinkVisible() CONST;

	VOID Clear();

	VOID Enable(BOOL bEnable = TRUE);
	BOOL IsEnabled() CONST;

	BOOL Copy(CONST CSpacecraftPass *pPass);
	BOOL Compare(CONST CSpacecraftPass *pPass) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftPasses

class AFX_EXT_CLASS CSpacecraftPasses : public CArray<CSpacecraftPass *>
{
	// Construction
public:
	CSpacecraftPasses();
	~CSpacecraftPasses();

	// Attributes
public:

	// Operations
public:
	INT Add(CSpacecraftPass *pPass);

	INT Find(LPCTSTR pszName) CONST;

	CSpacecraftPass *GetAt(INT nIndex) CONST;
	CSpacecraftPass *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CSpacecraftPasses &pPasses);
	BOOL Compare(CONST CSpacecraftPasses &pPasses) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftInterlinkPeriod

class AFX_EXT_CLASS CSpacecraftInterlinkPeriod : public CObject
{
	// Construction
public:
	CSpacecraftInterlinkPeriod();

	// Attributes
public:
	enum InterlinkOrigin
	{
		SpacecraftA = 0,
		SpacecraftB = 1
	};
	enum InterlinkPhase
	{
		Start = 0,
		End = 1
	};
private:
	CTimeKey  m_tPeriod[2];
	double  m_fAzimuth[2][3];
	double  m_fElevation[2][3];

	// Operations
public:
	VOID SetPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetPeriod(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	CTimeSpan GetPeriodDuration() CONST;
	CTimeKey GetStartTime() CONST;
	CTimeKey GetStopTime() CONST;
	VOID SetDirection(InterlinkOrigin nOrigin, InterlinkPhase nPhase, double fAzimuth, double fElevation);
	VOID GetDirection(InterlinkOrigin nOrigin, InterlinkPhase nPhase, double &fAzimuth, double &fElevation) CONST;

	VOID Copy(CONST CSpacecraftInterlinkPeriod *pPeriod);
	BOOL Compare(CONST CSpacecraftInterlinkPeriod *pPeriod) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftInterlinkPeriods

class AFX_EXT_CLASS CSpacecraftInterlinkPeriods : public CArray<CSpacecraftInterlinkPeriod *>
{
	// Construction
public:
	CSpacecraftInterlinkPeriods();
	~CSpacecraftInterlinkPeriods();

	// Attributes
public:

	// Operations
public:
	INT Add(CSpacecraftInterlinkPeriod *pPeriod);

	CSpacecraftInterlinkPeriod *GetAt(INT nIndex) CONST;
	CSpacecraftInterlinkPeriod *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CSpacecraftInterlinkPeriods &pPeriods);
	BOOL Compare(CONST CSpacecraftInterlinkPeriods &pPeriods) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftInterlink

class AFX_EXT_CLASS CSpacecraftInterlink : public CObject
{
	// Construction
public:
	CSpacecraftInterlink();
	~CSpacecraftInterlink();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbSpacecraft[3];
		UINT  nSpacecraft[3];
		TIMEKEY  tPeriod[2];
		COLORREF  nLinkColor;
		UINT  nLinkWidth;
		BOOL  bShowLink;
		BOOL  bEnabled;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szSpacecraft[3];
	CTimeKey  m_tPeriod[2];
	COLORREF  m_nLinkColor;
	UINT  m_nSpacecraft[3];
	UINT  m_nLinkWidth;
	BOOL  m_bShowLink;
	BOOL  m_bEnabled;
private:
	CSpacecraftInterlinkPeriods  m_pPeriods;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetSpacecraftA(LPCTSTR pszName, UINT nNumber);
	CString GetSpacecraftA(UINT &nNumber) CONST;
	CString GetSpacecraftA() CONST;
	VOID SetSpacecraftVia(LPCTSTR pszName, UINT nNumber);
	CString GetSpacecraftVia(UINT &nNumber) CONST;
	CString GetSpacecraftVia() CONST;
	VOID SetSpacecraftB(LPCTSTR pszName, UINT nNumber);
	CString GetSpacecraftB(UINT &nNumber) CONST;
	CString GetSpacecraftB() CONST;
	VOID SetTimeInterval(CONST CTimeKey &tStartTime, CONST CTimeSpan &tDuration);
	BOOL GetTimeInterval(CTimeKey &tStartTime, CTimeSpan &tDuration) CONST;

	VOID SetLinkProperties(COLORREF nColor, UINT nWidth);
	BOOL GetLinkProperties(COLORREF &nColor, UINT &nWidth) CONST;
	BOOL SetLinkPeriods(CONST CSpacecraftInterlinkPeriods &pPeriods);
	INT GetLinkPeriods(CSpacecraftInterlinkPeriods &pPeriods) CONST;
	VOID ShowLink(BOOL bShow = TRUE);
	BOOL IsLinkVisible() CONST;

	VOID Clear();

	VOID Enable(BOOL bEnable = TRUE);
	BOOL IsEnabled() CONST;

	BOOL Copy(CONST CSpacecraftInterlink *pInterlink);
	BOOL Compare(CONST CSpacecraftInterlink *pInterlink) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpacecraftInterlinks

class AFX_EXT_CLASS CSpacecraftInterlinks : public CArray<CSpacecraftInterlink *>
{
	// Construction
public:
	CSpacecraftInterlinks();
	~CSpacecraftInterlinks();

	// Attributes
public:

	// Operations
public:
	INT Add(CSpacecraftInterlink *pInterlink);

	INT Find(LPCTSTR pszName) CONST;

	CSpacecraftInterlink *GetAt(INT nIndex) CONST;
	CSpacecraftInterlink *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CSpacecraftInterlinks &pInterlinks);
	BOOL Compare(CONST CSpacecraftInterlinks &pInterlinks) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __SPACECRAFT_H__
