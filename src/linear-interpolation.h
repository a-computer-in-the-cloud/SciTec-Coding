#ifndef LINEAR_INTERPOLATION
#define LINEAR_INTERPOLATION

#include <vector>
#include "XYZVelocity.h"


class LinearInterpolation {
  public:
    LinearInterpolation ();
    ~LinearInterpolation();

    XYZVelocity operator ()(std::vector<XYZVelocity> velocities, double time);
};



#endif