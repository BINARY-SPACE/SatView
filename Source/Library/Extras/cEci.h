//
// cEci.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright (c) 2004-2013 Michael F. Henry
// Version 01/2013
#pragma once

#include "cEcBase.h"
#include "cWgsModel.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

class cEcf;
class cEcfTime;
class cGeo;
class cGeoTime;

//////////////////////////////////////////////////////////////////////
// class cEci
//////////////////////////////////////////////////////////////////////
class cEci : public cEcBase
{
public:
   cEci(const cVector &pos, const cVector &vel);
   cEci(const cEcf &ecf, cJulian date);
   cEci(const cGeo &geo, cJulian date);
  
   virtual ~cEci() {};
};

//////////////////////////////////////////////////////////////////////
// class cEciTime
//////////////////////////////////////////////////////////////////////
class cEciTime : public cEci
{
public:
   cEciTime(const cEci &eci, cJulian date);
   cEciTime(const cVector &pos, const cVector &vel, cJulian date);
   cEciTime(const cEcf &ecf, cJulian date);
   cEciTime(const cEcfTime &ecf, cJulian date);
   cEciTime(const cGeo &geo, cJulian date);
   cEciTime(const cGeoTime &geo);

   virtual ~cEciTime() {};

   cJulian Date() const { return m_Date; }

protected:
   cJulian m_Date;
};

// Interface to represent an object that can be positioned in ECI 
// coordinate space, and whose position is time-dependent.
class IEciObject
{
public:
   virtual std::string Name() const = 0;
   virtual cEciTime PositionEci(const cJulian& time) const = 0;
};

}
}