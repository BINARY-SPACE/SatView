//
// utility.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2012-2013 Michael F. Henry
// Version 07/2014
//
#pragma once

#include "cJulian.h"
#include "cOrbit.h"

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{
namespace Utility
{

double  TimeToMpe(const cSatellite& sat, cJulian time);
cJulian MpeToTime(const cSatellite& sat, double mpe);
cJulian ToNearestSecond(cJulian dt);
 
bool LineIntersects(const cWgsModel& model, const cVector& p1, const cVector& p2, double kmAltitude = 0.0);
double SurfaceDistance(const cWgsModel& model, cVector p1, cVector p2);
double Altitude(const cWgsModel& model, cVector positionEci);
cVector MidPoint(const cVector& p1, const cVector& p2);

double CalcDecayTime(const IOrbit& orbit, double t1, double t2);

}
}
}
}

using namespace Zeptomoby::OrbitTools::Track::Utility;