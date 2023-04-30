//
// cWgsModel.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2010-2012 Michael F. Henry
// Version 06/2012

#pragma once

namespace Zeptomoby 
{
namespace OrbitTools 
{

// Common base class for all WGS-Model types.
class cWgsModel
{
public:
   ~cWgsModel() {}

   virtual double Ck2()    const { return J2() / 2.0;        }
   virtual double Ck4()    const { return -3.0 * J4() / 8.0; }
   virtual double Xke()    const { return m_Xke; }
   virtual double Xkmper() const { return m_Xkmper; } // Earth equatorial radius, in kilometers.
   virtual double Ge()     const { return m_Ge;     } // Earth gravitational constant, km^3/sec^2.

   virtual double J2() const = 0;      // J2 harmonic
   virtual double J3() const = 0;      // J3 harmonic
   virtual double J4() const = 0;      // J4 harmonic
   virtual double F()  const = 0;      // Earth flattening

protected:
   cWgsModel(double ge, double xkmper)
   {
      m_Ge     = ge;
      m_Xkmper = xkmper;
      m_Xke    = sqrt(3600.0 * ge / (xkmper * xkmper * xkmper));
   }

private:
   double m_Xkmper;
   double m_Xke;
   double m_Ge;
};

// World Geodetic Survey, 1972.
#define XKMPER_WGS72 6378.135
#define GE_WGS72     398600.8

class cWgs72 : public cWgsModel
{
public:
   ~cWgs72() {}

   double J2() const { return 1.0826158e-03; }
   double J3() const { return -2.53881e-06;  }
   double J4() const { return -1.65597e-06;  }
   double F()  const { return 1.0 / 298.26;  }

   static cWgsModel* Instance();

private:
   cWgs72() : cWgsModel(GE_WGS72, XKMPER_WGS72)  {}
   cWgs72(const cWgs72&);                // singleton - do not implement
   cWgs72& operator=(const cWgs72& rhs); // singleton - do not implement
};

// World Geodetic Survey, 1984.
#define XKMPER_WGS84 6378.137
#define GE_WGS84     398600.5 

class cWgs84 : public cWgsModel
{
public:
   ~cWgs84() {}

   double J2() const { return  1.08262998905e-03;  } 
   double J3() const { return -2.53215306e-06;     }   
   double J4() const { return -1.61098761e-06;     } 
   double F()  const { return 1.0 / 298.257223563; }

   static cWgsModel* Instance();

private:
   cWgs84() : cWgsModel(GE_WGS84, XKMPER_WGS84) {}
   cWgs84(const cWgs84&);                // singleton - do not implement
   cWgs84& operator=(const cWgs84& rhs); // singleton - do not implement
};

}
}