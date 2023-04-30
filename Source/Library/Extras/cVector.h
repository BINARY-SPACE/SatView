//
// cVector.h
//
// DISCLAIMER OF WARRANTY: THE AUTHOR PROVIDES THIS SOFTWARE "AS IS" WITH
// NO WARRANTIES, EITHER EXPRESSED OR IMPLIED, INCLUDING WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHOR MAKES 
// NO REPRESENTATIONS CONCERNING THE QUALITY OF THE SOFTWARE AND DOES NOT 
// PROMISE THAT THE SOFTWARE IS ERROR FREE OR WILL OPERATE WITHOUT 
// INTERRUPTION.
//
// Copyright 2003-2013 (c) Michael F. Henry
// Version 01/2013
//
#pragma once

namespace Zeptomoby 
{
namespace OrbitTools
{

class cVector  
{
public:
   cVector(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0)
      : m_x(x), m_y(y), m_z(z), m_w(w) 
   {
   }

  virtual ~cVector() {};

   void Sub(const cVector&);   // subtraction
   void Mul(double factor);    // multiply each component by 'factor'

   double Angle(const cVector&) const;  // angle between two vectors
   double Dot  (const cVector&) const;  // dot product
   double Magnitude() const;            // vector magnitude
   double Distance(const cVector& vec) const;

   void RotateX(double radians);
   void RotateY(double radians);
   void RotateZ(double radians);
   void Translate(double x, double y, double z);

   double m_x;
   double m_y;
   double m_z;
   double m_w;
};
}
}