#ifndef CONVERSION_HH
#define CONVERSION_HH

#include <cmath>
#include "LLAPoint.h"
#include "ECEFPoint.h"

class LLAtoECEFConversion {
  public:
    LLAtoECEFConversion (double a, double b, double f);
    ~LLAtoECEFConversion();

    double toRadian (double degree);
    ECEFPoint operator ()(LLAPoint& lla);

  double axis_major;
  double axis_minor;
  double flattening;
  double eccentricity1;
  double eccentricity2;
  const double pie = M_PI;
};


#endif