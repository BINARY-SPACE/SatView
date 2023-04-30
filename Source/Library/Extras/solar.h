//
// solar.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2012-2014 Michael F. Henry
// Version 07/2014
//
#pragma once

#include "iOrbit.h"

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{
namespace Solar
{

cEciTime GetPosition(const cJulian &time); // deprecated
cEciTime PositionEci(const cJulian &time);

bool InSunlight(const cSatellite& sat, cJulian date);
bool InSunlight(const cSatellite& sat, double  mpe);
bool InSunlight(const cEciTime &eci, const cWgsModel *pEllipsoid);
bool InSunlight(const cSite &site, const cJulian &date, double degTwilight = -6.0);

}
}
}
}