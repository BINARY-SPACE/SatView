//
// acquire.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2013-2014 Michael F. Henry
// Version 07/2014
//
#pragma once

#include "cSatellite.h"
#include "schedule.h"
#include "passData.h"

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{

typedef shared_ptr<cSite>      site_ptr;
typedef shared_ptr<IEciObject> eci_ptr;
typedef shared_ptr<cSatellite> satellite_ptr;

namespace Acquire
{
enum eAcquireType
{
   SiteToSat,
   SatToSat,
   SatToSite
};

//
// Class to encapsulate creating a schedule of satellite-to-satellite, 
// satellite-to-site, and site-to-satellite acquisition times.
//   
class cAcquire
{
public:
   // Use this constructor for site-to-satellite acquisition
   cAcquire(const cSite& primary, const vector<satellite_ptr>& targets, cJulian t1, cJulian t2);

   // Use this constructor for satellite-to-satellite acquisition
   cAcquire(const cSatellite& primary, const vector<satellite_ptr>& targets, cJulian t1, cJulian t2, double kmAltitude = 0.0);

   // Use this constructor for satellite-to-site acquisition
   cAcquire(const cSatellite& primary, const vector<site_ptr>& targets, cJulian t1, cJulian t2);

   cAcquire(const cAcquire& rhs);
   cAcquire& operator=(const cAcquire& rhs);

   cSchedule<IEciObject> AcquireAny();
   cSchedule<IEciObject> AcquireAll();
   cSchedule<IEciObject> AcquireMin();
   cSchedule<IEciObject> AcquireMax();

   static cAzEl     OriginPlaneCoord(const cVector& posA, const cVector& posB);
   static cAzElTime OriginPlaneCoord(const cSatellite& satA, const cSatellite& satB, cJulian utc);
   static cAzElTime OriginPlaneCoord(const satellite_ptr& satA, const satellite_ptr& satB, cJulian utc);

protected:
   void InitSchedule();
   vector<shared_ptr<cPeriodInfo<IEciObject>>> CalcAcquireSiteToSat(const eci_ptr& target);
   vector<shared_ptr<cPeriodInfo<IEciObject>>> CalcAcquireSatToSat (const eci_ptr& target);
   vector<shared_ptr<cPeriodInfo<IEciObject>>> CalcAcquireSatToSite(const eci_ptr& target);

   cJulian m_timeStart;
   cJulian m_timeStop;
   eAcquireType m_acquireType;
   double m_kmAltitude;
   eci_ptr m_primary;
   vector<eci_ptr> m_targets;
   shared_ptr<cSchedule<IEciObject>> m_schedule_ptr;
};

}
}
}
}