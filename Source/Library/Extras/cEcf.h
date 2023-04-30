//
// cEcf.h
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

class cEci;
class cEciTime;
class cGeo;
class cGeoTime;

//////////////////////////////////////////////////////////////////////
// class cEcf
// Encapsulates an Earth-Centered Fixed position and velocity.
class cEcf : public cEcBase
{
public:
   cEcf(const cEcf &ecf);
   cEcf(const cVector &pos, const cVector &vel, const cWgsModel *pEllipsoid);
   cEcf(const cEci &eci, cJulian date, const cWgsModel *pEllipsoid);
   cEcf(const cGeo &geo);

   virtual ~cEcf();

   cEcf& operator=(const cEcf& rhs);

   const cWgsModel* Ellipsoid() const { return m_pEllipsoid;}

protected:
   const cWgsModel *m_pEllipsoid; // Pointer to global singleton
};

//////////////////////////////////////////////////////////////////////
// class cEcfTime
// Encapsulates an Earth-Centered Fixed position, velocity, and time.
class cEcfTime : public cEcf
{
public:
   cEcfTime(const cEcf &ecf, cJulian date);
   cEcfTime(const cVector &pos, const cVector &vel, cJulian date, const cWgsModel *pEllipsoid);
   cEcfTime(const cEci &eci, cJulian date, const cWgsModel *pEllipsoid);
   cEcfTime(const cEciTime &eci, const cWgsModel *pEllipsoid);
   cEcfTime(const cGeo &geo, cJulian date);
   cEcfTime(const cGeoTime &geo);

   virtual ~cEcfTime() {}
   
   cJulian Date() const { return m_Date; }

protected:
   cJulian m_Date;
};

}
}