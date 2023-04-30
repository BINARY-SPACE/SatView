//
// azEl.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2013-2014 Michael F. Henry
// Version 01/2014
//
#pragma once

namespace Zeptomoby
{
namespace OrbitTools
{
namespace Track
{

/// <summary>
/// Class to encapsulate azimuth and elevation information.
/// </summary>
class cAzEl
{
public:
   /// <summary>
   /// Azimuth, clockwise from true north.
   /// </summary>
   double AzimuthRad() const { return m_Azimuth;          }
   double AzimuthDeg() const { return rad2deg(m_Azimuth); }

   /// <summary>
   /// Elevation relative to horizon.
   /// </summary>
   double ElevationRad() const { return m_Elevation;          }
   double ElevationDeg() const { return rad2deg(m_Elevation); }

   /// <summary>
   /// Standard constructor.
   /// </summary>
   /// <param name="azimuth">Azimuth (radians).</param>
   /// <param name="elevation">Elevation (radians).</param>
   cAzEl(double azimuth, double elevation) :
      m_Azimuth(azimuth),
      m_Elevation(elevation)
   {
   }

   /// <summary>
   /// Copy constructor.
   /// </summary>
   cAzEl(const cAzEl& rhs) :
      m_Azimuth(rhs.AzimuthRad()),
      m_Elevation(rhs.ElevationRad())
   {
   }

   /// <summary>
   /// Formats a string to contain the azimuth, and optionally the elevation.
   /// </summary>
   /// <param name="showElevation">If true, the elevation value is included.</param>
   /// <returns>The formatted string.</returns>
   string ToString(bool showElevation = true);

private:
   double m_Azimuth;    // radians
   double m_Elevation;  // radians
};

/// <summary>
/// Class to encapsulate satellite azimuth and elevation 
/// information at a given moment in time.
/// </summary>
class cAzElTime : public cAzEl
{
public:
   /// <summary>
   /// The time, in minutes-past-epoch, associated with the 
   /// Azimuth and Elevation data.
   /// </summary>
   double TimeMpe() const { return m_TimeMpe; }

   /// <summary>
   /// Standard constructor.
   /// </summary>
   /// <param name="timeMpe">Time (minutes-past-epoch).</param>
   /// <param name="azimuth">Azimuth (radians).</param>
   /// <param name="elevation">Elevation (radians).</param>
   cAzElTime(double azimuth, double elevation, double timeMpe) :
      cAzEl(azimuth, elevation),
      m_TimeMpe(timeMpe)
   {
   }

   /// <summary>
   /// Standard constructor.
   /// </summary>
   /// <param name="azEl">Azimuth/Elevation data.</param>
   /// <param name="timeMpe">Time (minutes-past-epoch).</param>
   cAzElTime(const cAzEl& azEl, double timeMpe) :
      cAzEl(azEl),
      m_TimeMpe(timeMpe)
   {
   }

   /// <summary>
   /// Copy constructor.
   /// </summary>
   cAzElTime(const cAzElTime& rhs) :
      m_TimeMpe(rhs.TimeMpe()),
      cAzEl(rhs.AzimuthRad(), rhs.ElevationRad())
   {
   }

   /// <summary>
   /// Formats a string to contain the time, azimuth, and optionally the elevation.
   /// </summary>
   /// <param name="showElevation">If true, the elevation value is included.</param>
   /// <returns>The formatted string.</returns>
   string ToString(bool showElevation = false);

private:
   double m_TimeMpe; // minutes-past-epoch
};

}
}
}
