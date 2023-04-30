//
// tracks.h
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
#include <vector>

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{
namespace Tracks
{

// Subpoint
cGeoTime Subpoint(const cSatellite& sat, cJulian utc, double kmLoft = 0.0);
cGeoTime Subpoint(const cSatellite& sat, double mpe, double kmLoft = 0.0);
cEcfTime SubpointEcf(const cSatellite& sat, double mpe, double kmLoft = 0.0);
cEcfTime SubpointEcf(const cSatellite& sat, cJulian utc, double kmLoft = 0.0);
   
// Ground Track - Geodetic
vector<cGeoTime> GroundTrack(const cSatellite& sat, cJulian t1, cJulian t2, int dt, double kmLoft = 0.0);
vector<cGeoTime> GroundTrack(const cSatellite& sat, cJulian t1, cJulian t2, double kmSpacing, double kmLoft = 0.0);
vector<cGeoTime> GroundTrack(const cSatellite& sat, double t1, double t2, int dt, double kmLoft = 0.0);
vector<cGeoTime> GroundTrack(const cSatellite& sat, double t1, double t2, double kmSpacing, double kmLoft = 0.0);

// Ground Track - ECF
vector<cEcfTime> GroundTrackEcf(const cSatellite& sat, cJulian t1, cJulian t2, int dt, double kmLoft = 0.0);
vector<cEcfTime> GroundTrackEcf(const cSatellite& sat, cJulian t1, cJulian t2, double kmSpacing, double kmLoft = 0.0);
vector<cEcfTime> GroundTrackEcf(const cSatellite& sat, double t1, double t2, int dt, double kmLoft = 0.0);
vector<cEcfTime> GroundTrackEcf(const cSatellite& sat, double t1, double t2, double kmSpacing, double kmLoft = 0.0);
   
// Orbit Track
vector<cEciTime> OrbitTrack(const cSatellite& sat, cJulian t1, cJulian t2, int dt);
vector<cEciTime> OrbitTrack(const cSatellite& sat, cJulian t1, cJulian t2, double kmSpacing = 100.0);
vector<cEciTime> OrbitTrack(const cSatellite& sat, double t1, double t2, int dt);
vector<cEciTime> OrbitTrack(const cSatellite& sat, double t1, double t2, double kmSpacing = 100.0);

}
}
}
}