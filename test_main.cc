#include <iostream>
#include "src/gps_proj.h"

int main() {
  // 天津西青郊野公园 
  // WGS84:117.15988328025055,39.01295785394829
  // UTM:513842.0517882711 , 4318226.689188628
  Point gps_point, utm_point;
  gps_point.x = 117.15988328025055; // lng
  gps_point.y = 39.01295785394829; // lat
  utm_point = GPS2UTM(gps_point);
  std::cout << "GPS2UTM: " << std::fixed << utm_point.x << " " << utm_point.y << std::endl;

  double x = 513842.0517882711;
  double y = 4318226.689188628;
  double z = 0;
  UTM2GPS(x, y, z);
  std::cout << "UTM2GPS: " << std::fixed << x << " " << y << std::endl;
  return 1;
}