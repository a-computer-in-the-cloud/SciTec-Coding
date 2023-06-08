#ifndef XYZVELOCITY_HH
#define XYZVELOCITY_HH

#include <ostream>
#include <iomanip>

class XYZVelocity {
  public:
    XYZVelocity  () {};
    XYZVelocity  (long double x, long double y, long double z, long double t) : 
    vx(x), vy(y), vz(z), vt(t) {};
    ~XYZVelocity () {};

    void setVT (long double t) { vt = t; }
    void setVX (long double x) { vx = x; }
    void setVY (long double y) { vy = y; }
    void setVZ (long double z) { vz = z; }

    long double getVT () { return vt; }
    long double getVX () { return vx; }
    long double getVY () { return vy; }
    long double getVZ () { return vz; }

    friend std::ostream& operator <<(std::ostream& out, const XYZVelocity& rhs) {
      out << "XYZVelocity {";
      out << "t = " << std::fixed << rhs.vt <<", ";
      out << "x = " << std::fixed << rhs.vx <<", ";
      out << "y = " << std::fixed << rhs.vy <<", ";
      out << "z = " << std::fixed << rhs.vz;
      out <<"}\n";
      return out;
    };
  
  long double vx;
  long double vy;
  long double vz;
  long double vt;
};


#endif