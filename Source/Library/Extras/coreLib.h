//
// coreLib.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright 2012-2014 (c) Michael F. Henry
// Version 06/2014

#include <stdio.h>
#include <tchar.h>

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

#include "cJulian.h"
#include "cEci.h"
#include "cEcf.h"
#include "coord.h"
#include "cSite.h"
#include "cTle.h"
#include "cVector.h"
#include "cWgsModel.h"
#include "exceptions.h"
#include "iOrbit.h"

using namespace Zeptomoby::OrbitTools;