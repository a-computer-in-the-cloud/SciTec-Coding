#include <iostream>
#include <cassert>

#include "parser.h"
#include "conversion.h"
#include "linear-interpolation.h"
#include "ECEFPoint.h"
#include "XYZVelocity.h"
#include "config.h"


int main (int argc, char **argv) {
  std::cout <<"LLA to ECEF conversion and interpolation:\n"
            <<"using paramaters a = {" <<a <<"}, b = {" << b <<"}, f = {" <<f <<"}\n"
            <<"csv data = {" << csv <<"}\n\n\n";

  LLAtoECEFConversion conversion (a, b, f);
  LinearInterpolation lInterpolate;
  Parser parser;

  // Read and parse CSV Data to LLA datapoints//
  Status rstatus = parser.parse (csv, true);
  if (rstatus != STATUS_OK) {
    std::cerr<<" Could not parse file!\n";
    return rstatus;
  };

  // Convert LLA datapoints to ECEF datapoints//
  std::vector<ECEFPoint> ecefPoints;
  for (auto& lla : parser) {
    auto ecef = conversion (lla);
    ecefPoints.push_back (ecef);
  };

  // Compute ECEF velocities //
  // Position Delta / Time Delta
  std::vector<XYZVelocity> velocities;
  auto firstPoint = ecefPoints[0];
  velocities.push_back (XYZVelocity {0, 0, 0, firstPoint.getT()});
  for (size_t pos = 1; pos < ecefPoints.size(); pos++) {
    auto source = ecefPoints[pos - 1];
    auto target = ecefPoints[pos];
    auto vel = source.velocityTo(target);
    velocities.push_back (vel);
  };
  assert (ecefPoints.size() == velocities.size());

  // Do interpolation for specified times (1532334000.0 and 1532335268.0)
  double t1532334000 = 1532334000.0;
  auto lerp0 = lInterpolate (velocities, t1532334000);
  std::cout <<"Linearly interpolated velocity for time (" 
            << std::fixed << t1532334000
            <<")\n\t is = " 
            <<lerp0 <<"\n";

  double t1532335268 = 1532335268.0;
  auto lerp1 = lInterpolate (velocities, t1532335268);
  std::cout <<"Linearly interpolated velocity for time (" 
            << std::fixed << t1532335268
            <<")\n\t is = " 
            <<lerp1 <<"\n";
  
  return 0;
};