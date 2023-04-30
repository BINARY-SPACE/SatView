//
// passData.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2013-2014 Michael F. Henry
// Version 07/2014
//
#pragma once

#include <time.h>
#include "cSatellite.h"
#include "azEl.h"

using namespace Zeptomoby::OrbitToolsPro;

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{
namespace Pass
{

const double DEFAULT_DECAY_MPE = -1.0e32;

/// <summary>
/// Class to encapsulate satellite AOS (rise) data, LOS (set) data, and
/// MAX (maximum elevation above horizon) data.
/// </summary>
class cPassData
{
public:
   const cAzElTime* Aos() const { return m_Aos; }
   const cAzElTime* Los() const { return m_Los; }
   const cAzElTime* Max() const { return m_Max; }

   const double DecayMpe() const { return m_DecayMpe; }

   bool IsValidAos() const { return m_Aos != nullptr; }
   bool IsValidLos() const { return m_Los != nullptr; }
   bool IsValidMax() const { return m_Max != nullptr; }

   void SetMax(cAzElTime *max) { delete m_Max; m_Max = max; }

   /// <summary>
   /// Returns true if the satellite orbit has decayed.
   /// </summary>
   bool IsDecayed() const { return m_DecayMpe != DEFAULT_DECAY_MPE; } 
   
   /// <summary>
   /// Constructor for decayed orbits.
   /// </summary>
   /// <param name="decayMpe">The time, in minutes-past-epoch, that the 
   /// satellite orbit decayed.
   /// </param>
   cPassData(double decayMpe) :
      m_Aos(nullptr),
      m_Los(nullptr),
      m_Max(nullptr),
      m_DecayMpe(decayMpe)
   {
   }

   /// <summary>
   /// Create an object with AOS and LOS information.
   /// </summary> 
   /// <param name="aos">Acquisition of signal time.</param>
   /// <param name="los">Loss of signal time.</param>
   cPassData(cAzElTime* aos, cAzElTime* los) :
      m_Aos(aos),
      m_Los(los),
      m_Max(nullptr),
      m_DecayMpe(DEFAULT_DECAY_MPE)
   {
   }

   /// <summary>
   /// Create an object with AOS, LOS, and MAX information.
   /// </summary>
   /// <param name="aos">Acquisition of signal time.</param>
   /// <param name="los">Loss of signal time.</param>
   /// <param name="max">Time of maximum elevation.</param>
   cPassData(cAzElTime* aos, cAzElTime* los, cAzElTime* max) :
      m_Aos(aos),
      m_Los(los),
      m_Max(max),
      m_DecayMpe(DEFAULT_DECAY_MPE)
   {
   }

   cPassData(const cPassData& src)
   {
      m_Aos = (src.Aos() == nullptr) ? nullptr : new cAzElTime(*(src.Aos())); 
      m_Los = (src.Los() == nullptr) ? nullptr : new cAzElTime(*(src.Los())); 
      m_Max = (src.Max() == nullptr) ? nullptr : new cAzElTime(*(src.Max())); 

      m_DecayMpe = src.m_DecayMpe;
   }

   ~cPassData()
   {
      delete m_Aos;
      delete m_Los;
      delete m_Max;
   }

   const cPassData& operator=(const cPassData& other)
   {
      if (&other != this)
      {
         m_Aos = (other.Aos() == nullptr) ? nullptr : new cAzElTime(*(other.Aos())); 
         m_Los = (other.Los() == nullptr) ? nullptr : new cAzElTime(*(other.Los())); 
         m_Max = (other.Max() == nullptr) ? nullptr : new cAzElTime(*(other.Max())); 

         m_DecayMpe = other.m_DecayMpe;
      }

      return *this;
   }
         
   bool Merge(const cPassData &item);
   double CalcDecayTime(const IOrbit& orbit, double t1, double t2);
   double MinEventTimeMpe() const;
   double MaxEventTimeMpe() const;

   /// <summary>
   /// Returns a string containing minutes-past-epoch-style AOS/MAX/LOS data.
   /// </summary>
   /// <returns>The formatted string.</returns>
   string ToString() const;

   /// <summary>
   /// Returns a string containing calendar date-style AOS/MAX/LOS data with
   /// the times given in UTC.
   /// </summary>
   /// <param name="sat">The satellite.</param>
   /// <returns>The formatted string.</returns>
   string ToStringUtc(const cSatellite& sat) const;

   /// <summary>
   /// Returns a string containing calendar date-style AOS/MAX/LOS data with
   /// the times given in the specified time zone.
   /// </summary>
   /// <param name="sat">The satellite.</param>
   string ToString(const cSatellite& sat) const;

   static void SetTimeZoneInfo(const string& tzInfo)
   {
      string val = "TZ=" + tzInfo;

      _putenv(val.c_str());
      _tzset();

      m_UseTimeZone = !tzInfo.empty();
   }

   private:
      cAzElTime* m_Aos;
      cAzElTime* m_Los;
      cAzElTime* m_Max;

      double m_DecayMpe;

      static bool m_UseTimeZone;
};

vector<cPassData> CalcPassData(const cSite& site, const cSatellite &sat, cJulian t1, cJulian t2, bool includeMax, bool concurrent = true);
vector<cPassData> CalcPassData(const cSite& site, const cSatellite &sat, double  t1, double  t2, bool includeMax, bool concurrent = true);
}
}
}
}