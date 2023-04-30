//
// coord.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright 2002-2012 Michael F. Henry
// Version 12/2012

#pragma once

#include "cJulian.h"
#include "cVector.h"
#include "cWgsModel.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

class cEci;
class cEcf;
class cEciTime;
class cEcfTime;

//////////////////////////////////////////////////////////////////////
// Geocentric coordinates.
class cGeo  
{
public:
   cGeo(const cGeo& geo);
   cGeo(const cEcf& ecf);
   cGeo(const cEci& eci, cJulian date, const cWgsModel *pEllipsoid);
   cGeo(double latRad, double lonRad, double altKm, const cWgsModel *pEllipsoid);

   virtual ~cGeo();

   cGeo& operator=(const cGeo& rhs);

   double LatitudeRad()  const { return m_Lat; }
   double LongitudeRad() const { return m_Lon; }

   double LatitudeDeg()  const { return rad2deg(m_Lat); }
   double LongitudeDeg() const { return rad2deg(m_Lon); }

   double AltitudeKm() const     { return m_Alt; }
   void   AltitudeKm(double alt) { m_Alt = alt;  }

   double Distance(const cGeo& geo);

   const cWgsModel* Ellipsoid() const { return m_pEllipsoid;}

   virtual string ToString() const;

protected:
   void Construct(const cVector &posEcf, double theta, const cWgsModel *pEllipsoid);

   double m_Lat;   // Latitude,  radians (negative south)
   double m_Lon;   // Longitude, radians (negative west)
   double m_Alt;   // Altitude,  km      (above ellipsoid height)

   const cWgsModel *m_pEllipsoid; // Pointer to global singleton
};

//////////////////////////////////////////////////////////////////////
// Geocentric coordinates and associated time
class cGeoTime : public cGeo
{
public:
   cGeoTime(const cGeo &geo, cJulian date);
   cGeoTime(double latRad, double lonRad, double altKm, 
            cJulian &date, const cWgsModel *pEllipsoid);
   cGeoTime(const cEci &eci, cJulian date, const cWgsModel *pEllipsoid);
   cGeoTime(const cEciTime &eci, const cWgsModel *pEllipsoid);
   cGeoTime(const cEcf &ecf, cJulian date);
   cGeoTime(const cEcfTime &ecf);

   virtual ~cGeoTime() {};
      
   cJulian Date() const { return m_Date; }

protected:
   cJulian m_Date;
};

//////////////////////////////////////////////////////////////////////
// Topocentric-Horizon coordinates.
class cTopo  
{
public:
   cTopo(double azRad, double elRad, double rangeKm, double rateKmSec);
   virtual ~cTopo() {};

   double AzimuthRad()     const { return m_Az; }
   double ElevationRad()   const { return m_El; }

   double AzimuthDeg()     const { return rad2deg(m_Az); }
   double ElevationDeg()   const { return rad2deg(m_El); }

   double RangeKm()        const { return m_Range;     }
   double RangeRateKmSec() const { return m_RangeRate; }

protected:
   double m_Az;         // Azimuth, radians
   double m_El;         // Elevation, radians
   double m_Range;      // Range, kilometers
   double m_RangeRate;  // Range rate of change, km/sec
                        // Negative value means "towards observer"
};

//////////////////////////////////////////////////////////////////////
// Topocentric-Horizon coordinates and associated time
class cTopoTime : public cTopo
{
public:
   cTopoTime(const cTopo& topo, cJulian date);
   cTopoTime(double azRad, double elRad, double range, double rangeRate, cJulian date);
   virtual ~cTopoTime() {};

   cJulian Date() const { return m_Date; }

protected:
   cJulian m_Date;
};

}
}