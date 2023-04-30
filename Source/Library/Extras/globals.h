//
// globals.h
//
// Copyright (c) 2004-2010 Michael F. Henry
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
#pragma once

namespace Zeptomoby 
{
namespace OrbitTools
{
const double PI           = 3.141592653589793;
const double TWOPI        = 2.0 * PI;
const double RADS_PER_DEG = PI / 180.0;

const double DAY_SIDERAL  = (23 * 3600) + (56 * 60) + 4.09;  // sec
const double DAY_24HR     = (24 * 3600);                     // sec

const double AE           = 1.0;
const double AU           = 149597870.0;   // Astronomical unit (km) (IAU 76)

const double HR_PER_DAY   = 24.0;          // Hours per day   (solar)
const double MIN_PER_DAY  = 1440.0;        // Minutes per day (solar)
const double SEC_PER_DAY  = 86400.0;       // Seconds per day (solar)
const double OMEGA_E      = 1.00273790934; // Earth rotations in one solar day

// Utility functions
double sqr   (const double x);
double Fmod2p(const double arg);
double AcTan (const double sinx, const double cosx);

double rad2deg(const double);
double deg2rad(const double);
}
}