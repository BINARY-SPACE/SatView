//
// cEcBase.h
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

#include "cVector.h"
#include "cJulian.h"

namespace Zeptomoby 
{
namespace OrbitTools 
{

//////////////////////////////////////////////////////////////////////
// class cEcBase
// Base class for earth-centered coordinate systems.
class cEcBase
{
public:
   cEcBase(const cVector &pos, const cVector &vel);
   virtual ~cEcBase() {}

   const cVector& Position() const { return m_Position; }
   const cVector& Velocity() const { return m_Velocity; }
   
   double Distance(const cEcBase& p2) const;

   void ScalePosVector(double factor) { m_Position.Mul(factor); }
   void ScaleVelVector(double factor) { m_Velocity.Mul(factor); }

   virtual string ToString() const;

protected:
   cEcBase();

   cVector m_Position;
   cVector m_Velocity;
};

}
}
