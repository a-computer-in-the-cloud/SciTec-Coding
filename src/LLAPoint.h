#ifndef LLAPOINT_HH
#define LLAPOINT_HH

#include <ostream>
#include <iomanip>

class LLAPoint {
  public:
    LLAPoint (double t, double lat, double lng, double alt) : 
      time(t), 
      latitude(lat), 
      longitude(lng), 
      altitude(alt) {};

    LLAPoint () {};
    ~LLAPoint() {};

    double getTime ()      { return time; };
    double getLatitude ()  { return latitude; };
    double getLongitude () { return longitude; };
    double getAltitude ()  { return altitude; };
    std::string toDegreeMinuteSeconds();

    friend std::ostream& operator <<(std::ostream& out, const LLAPoint& lla) {
      out << "LLAPoint {";
      out << "time = " << std::setw(6) << std::fixed << lla.time <<", ";
      out << "lat  = " << std::setw(6) << std::fixed << lla.latitude <<", ";
      out << "lng  = " << std::setw(6) << std::fixed << lla.longitude <<", ";
      out << "alt  = " << std::setw(6) << std::fixed << lla.altitude;
      out <<"}\n";
      return out;
    };

  double time;
  double latitude;
  double longitude;
  double altitude;
};


#endif