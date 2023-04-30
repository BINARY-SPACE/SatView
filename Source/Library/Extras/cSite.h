//
// cSite.h: interface for the cSite class.
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright 2002-2014 Michael F. Henry
// Version 05/2014

#pragma once

#include "coord.h"
#include "cEci.h"
#include "cWgsModel.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

//////////////////////////////////////////////////////////////////////
// class cSite
// This class represents a ground site location on the earth.
class cSite : public IEciObject
{
public:
   cSite(double degLat, double degLon, double kmAlt, const string& name, const cWgsModel *pEllipsiod);
   cSite(double degLat, double degLon, double kmAlt, const cWgsModel *pEllipsiod);
   cSite(const cGeo &geo);
   virtual ~cSite();

   cGeo GetGeo() const { return m_Geo; }

   cEciTime PositionEci (const cJulian& ) const;   // Calc ECI of geo location
   cEciTime GetPosition (const cJulian& ) const;   // Deprecated, use PositionEci()
   cTopo    GetLookAngle(const cEciTime&) const;   // Calc topo coords of ECI object

   double LatitudeRad()  const { return m_Geo.LatitudeRad();  }
   double LongitudeRad() const { return m_Geo.LongitudeRad(); }

   double LatitudeDeg()  const { return m_Geo.LatitudeDeg();  }
   double LongitudeDeg() const { return m_Geo.LongitudeDeg(); }

   double AltitudeKm()   const { return m_Geo.AltitudeKm();   }

   string Name()     const { return m_Name; };
   string ToString() const;

protected:
   cGeo   m_Geo;  // Site coordinates
   string m_Name; // Site name
};
}
}