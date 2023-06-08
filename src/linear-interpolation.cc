#include "linear-interpolation.h"

#include <iostream>
#include <cmath>

LinearInterpolation::LinearInterpolation (){};
LinearInterpolation::~LinearInterpolation(){};

// v(t) = a0 + a1(t)
XYZVelocity LinearInterpolation::operator()(std::vector<XYZVelocity> velocities, 
                                            double time) {
  
  // find the closest time pair to the given time
  XYZVelocity first, second;
  for (size_t pos = 1; pos < velocities.size(); pos++) {
    first = velocities[pos - 1];
    second = velocities[pos];
    if ( ( first.getVT() <= time) && (time <= second.getVT())) {
      break;
    };
  };
  
  std::vector<XYZVelocity> list {first, second};
  size_t n = list.size ();
  
  size_t dims = 3;
  long double sumx[] = {0, 0, 0};
  long double sumy[] = {0, 0, 0};
  long double sumxy[] = {0, 0, 0};
  long double sumxx[] = {0, 0, 0};
  long double a0[] = {0, 0, 0};
  long double a1[] = {0, 0, 0};
  long double vt[] = {0, 0, 0};

  for (auto& vo : list) {
    // X direction
    sumx[0] += vo.getVT();
    sumy[0] += vo.getVX();
    sumxy[0] += vo.getVT() * vo.getVX();
    sumxx[0] += vo.getVT() * vo.getVT();

    // Y direction
    sumx[1] += vo.getVT();
    sumy[1] += vo.getVY();
    sumxy[1] += vo.getVT() * vo.getVY();
    sumxx[1] += vo.getVT() * vo.getVT();

    // Z direction
    sumx[2] += vo.getVT();
    sumy[2] += vo.getVZ();
    sumxy[2] += vo.getVT() * vo.getVZ();
    sumxx[2] += vo.getVT() * vo.getVT();
  };

  // compute a0, a1 and vt for XZY values //
  // using v(t) = a0 + a1(t) or y = mx + c //
  for(size_t pos = 0; pos < dims; pos++){
    a1[pos] = ((n * sumxy[pos]) - (sumx[pos] * sumy[pos])) / ((n * sumxx[pos] - (sumx[pos] * sumx[pos])));
    a0[pos] = (sumy[pos] - (a1[pos] * sumx[pos])) / n ;
    vt[pos] = a0[pos] + (a1[pos] * time);
  };
  
  return XYZVelocity {vt[0], vt[1], vt[2], time};
};