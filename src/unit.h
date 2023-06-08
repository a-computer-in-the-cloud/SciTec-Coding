#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <string>

enum Unit {
  METER_PER_SECOND = 0,
  SECONDS,
  DEGREE,
  RADIAN
};

std::string unitToString (Unit unit) {
  switch (unit) {
    case RADIAN:
      return "radians";
    case METER_PER_SECOND:
      return "meters/secs";
    case SECONDS:
      return "seconds";
    default:
      break;
  }
  return "";
};

#endif