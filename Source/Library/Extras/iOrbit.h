//
// iOrbit.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2012-2014 Michael F. Henry
// Version 06/2014
#pragma once

#include "cEci.h"
#include "cJulian.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{
   class IOrbit
   {
   public:
      virtual ~IOrbit() {}
      virtual cEciTime GetPosition(double mpe) const = 0; // Deprecated, use PositionEci()
      virtual cEciTime PositionEci(double mpe) const = 0;
   
      virtual double Inclination()   const = 0;
      virtual double Eccentricity()  const = 0;
      virtual double RAAN()          const = 0;
      virtual double ArgPerigee()    const = 0;
      virtual double BStar()         const = 0;
      virtual double Drag()          const = 0;
      virtual double MeanMotionTle() const = 0;
      virtual double MeanAnomaly()   const = 0;

      virtual cJulian Epoch() const = 0;

      virtual double TPlusEpoch(const cJulian &t) const = 0;

      virtual std::string SatName(bool fAppendId = false) const = 0;
      virtual std::string SatId() const = 0;
      virtual std::string TleLine1() const = 0;
      virtual std::string TleLine2() const = 0;
      virtual cTle TleData() const = 0;
   
      virtual double SemiMajor()  const = 0;
      virtual double SemiMinor()  const = 0;
      virtual double MeanMotion() const = 0;  // mean motion, rads/min
      virtual double Major()      const = 0;  // major axis in AE
      virtual double Minor()      const = 0;  // minor axis in AE
      virtual double Perigee()    const = 0;  // perigee in km
      virtual double Apogee()     const = 0;  // apogee in km
      virtual double Period()     const = 0;  // period in seconds

      virtual const cWgsModel* WgsModel() const = 0;
   };
}
}