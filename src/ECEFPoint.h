#ifndef ECEFPOINT_HH
#define ECEFPOINT_HH

#include <ostream>
#include <iomanip>

#include "XYZVelocity.h"


class ECEFPoint {
  public:
    ECEFPoint (double ax, double ay, double az, double at) :
      x(ax),
      y(ay),
      z(az),
      t(at) {};
    ECEFPoint () {};
    ~ECEFPoint() {};
    
    double getX () { return x; };
    double getY () { return y; };
    double getZ () { return z; };
    double getT () { return t; };

    XYZVelocity velocityTo (const ECEFPoint& rhs) {
      XYZVelocity re;
      auto tdiff = t - rhs.t;

      re.setVX((rhs.x - x) / tdiff);
      re.setVY((rhs.y - y) / tdiff);
      re.setVZ((rhs.z - z) / tdiff);
      
      re.setVT (rhs.t);
      return re;
    };

    friend std::ostream& operator <<(std::ostream& out, const ECEFPoint& ecef) {
      out << "ECEFPoint {";
      out << "t = " << std::setw(6) << std::fixed << ecef.t <<", ";
      out << "x = " << std::setw(6) << std::fixed << ecef.x <<", ";
      out << "y = " << std::setw(6) << std::fixed << ecef.y <<", ";
      out << "z = " << std::setw(6) << std::fixed << ecef.z;
      out <<"}\n";
      return out;
    };

  double x;
  double y;
  double z;
  double t;
};


#endif