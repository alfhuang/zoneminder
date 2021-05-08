//
// ZoneMinder Polygon Class Interfaces, $Date$, $Revision$
// Copyright (C) 2001-2008 Philip Coombes
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// 

#ifndef ZM_POLY_H
#define ZM_POLY_H

#include "zm_box.h"
#include <vector>

struct Edge {
  int min_y;
  int max_y;
  double min_x;
  double _1_m;

  static bool CompareYX(const Edge &e1, const Edge &e2) {
    if (e1.min_y == e2.min_y)
      return e1.min_x < e2.min_x;
    return e1.min_y < e2.min_y;
  }

  static bool CompareX(const Edge &e1, const Edge &e2) {
    return e1.min_x < e2.min_x;
  }
};

//
// Class used for storing a box, which is defined as a region
// defined by two coordinates
//
class Polygon {
 public:
  Polygon() : area(0) {}
  explicit Polygon(std::vector<Vector2> vertices);

  const std::vector<Vector2> &GetVertices() const {
    return vertices_;
  }

  const Box &Extent() const { return extent; }
  int LoX(int p_lo_x) { return extent.LoX(p_lo_x); }
  int HiX(int p_hi_x) { return extent.HiX(p_hi_x); }
  int LoY(int p_lo_y) { return extent.LoY(p_lo_y); }
  int HiY(int p_hi_y) { return extent.HiY(p_hi_y); }

  int Area() const { return area; }
  const Vector2 &Centre() const {
    return centre;
  }

  bool Contains(const Vector2 &coord) const;

 private:
  void calcArea();
  void calcCentre();

 private:
  std::vector<Vector2> vertices_;
  Box extent;
  int area;
  Vector2 centre;
};

#endif // ZM_POLY_H
