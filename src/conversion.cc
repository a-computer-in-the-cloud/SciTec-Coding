#include "conversion.h"


LLAtoECEFConversion::LLAtoECEFConversion (double a, double b, double f) : 
  axis_major(a), 
  axis_minor(b), 
  flattening(f) {

  double aa = a * a;
  double bb = b * b;
  eccentricity1 = sqrt((aa - bb) / aa);
  eccentricity2 = sqrt((aa - bb) / bb);
};

LLAtoECEFConversion::~LLAtoECEFConversion() {};

/*
  LLA to ECEF conversion
  N = a / (sqrt(1 - e^2 * sin^2 lat))
  X = (N + h) cos lat * cos lng
  Y = (N + h) cos lat * sin lng
  Z = ((b^2/a^2 * N) + h) sin lat
*/
ECEFPoint LLAtoECEFConversion::operator ()(LLAPoint& lla) {
  auto t   = lla.getTime();
  auto lat = toRadian( lla.getLatitude() );
  auto lng = toRadian( lla.getLongitude() );
  auto alt = lla.getAltitude();

  // pre-requisites
  double a = axis_major, b = axis_minor;
  double bb = (b * b);
  double aa = (a * a);
  double ssq = sin(lat) * sin(lat); //pow(sin(lat), 2);
  double e = eccentricity1;
  double n = a / sqrt (1 - (e * e)*(ssq));

  // xyz values
  double x = (n + alt) * cos (lat) * cos (lng);
  double y = (n + alt) * cos (lat) * sin (lng);
  double z = (((bb / aa) * n)  + alt) * sin (lat);

  ECEFPoint ecef{x, y, z, t};
  return ecef;
};

double LLAtoECEFConversion::toRadian (double degree) {
  return degree * (pie / 180);
};