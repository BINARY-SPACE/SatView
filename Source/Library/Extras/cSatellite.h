//
// cSatellite.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2014 Michael F. Henry
// Version 06/2014
#pragma once

#include <string>
#include "cTle.h"
#include "cEci.h"
#include "iOrbit.h"

namespace Zeptomoby 
{
namespace OrbitToolsPro
{

class cSatellite : public IEciObject
{
public:
   cSatellite(const cTle& tle, const cWgsModel *pEllipsoid, const std::string* pName = NULL);
   cSatellite(const cSatellite& src);
   cSatellite& operator=(const cSatellite& rhs);
   ~cSatellite();

   string   Name() const;
   cEciTime PositionEci(const cJulian& time) const;
   cEciTime PositionEci(double mpe) const;

   const IOrbit& Orbit() const { return *m_pOrbit; }      

protected:
   IOrbit* m_pOrbit;
   string* m_pName;
};

}
}