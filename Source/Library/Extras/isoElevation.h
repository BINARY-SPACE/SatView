//
// isoElevation.h
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

#include "cOrbit.h"
#include "cSatellite.h"
#include <vector>

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{
namespace Iso
{

// Elevation Circle - Satellite
vector<cGeo> ElevationCircle(const cSatellite& sat, cJulian utc, double degAngle, 
                             double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cGeo> ElevationCircle(const cSatellite& sat, double mpe, double degAngle,
                             double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEci> ElevationCircleEci(const cSatellite& sat, cJulian utc, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEci> ElevationCircleEci(const cSatellite& sat, double mpe, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEcf> ElevationCircleEcf(const cSatellite& sat, cJulian utc, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEcf> ElevationCircleEcf(const cSatellite& sat, double mpe, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);

// Elevation Circle - Site
vector<cGeo> ElevationCircle(const cSite &site, cJulian date, double kmTargetAlt, double degAngle,
                             double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEci> ElevationCircleEci(const cSite &site, cJulian date, double kmTargetAlt, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEcf> ElevationCircleEcf(const cSite &site, cJulian date, double kmTargetAlt, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);

// Elevation Circle - Ellipsoid
vector<cGeo> ElevationCircle(const cWgsModel* ellipsoid, cEciTime subpoint, cEci target, double degAngle,
                             double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEci> ElevationCircleEci(const cWgsModel* ellipsoid, cEciTime subpoint, cEci target, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);
vector<cEcf> ElevationCircleEcf(const cWgsModel* ellipsoid, cEciTime subpoint, cEci target, double degAngle,
                                double kmSpacing = 50.0, double kmLoft = 0.0);
// Coordinate of Look Angle
cGeo CoordOfLookAngle(const cGeoTime &geoSubpoint, double degAngle, cEci target, bool searchNorth);

}
}
}
}