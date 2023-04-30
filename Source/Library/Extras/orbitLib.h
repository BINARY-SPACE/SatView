//
// orbitLib.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2013-2014 Michael F. Henry
// Version 08-2014
//
#include <stdio.h>
#include <tchar.h>

#include <assert.h>

using namespace std;

// When using a compiler that is not C++11 compliant, comment out the following
// line of code. This will disable the parallel execution feature of the 
// Track Library, but allow compilation on these older compilers.
#define CONCURRENT_PASS_PREDICTION 1

#include "cOrbit.h"
#include "cSatellite.h"

using namespace Zeptomoby::OrbitToolsPro;