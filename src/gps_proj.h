#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

#define ACCEPT_USE_OF_DEPRECATED_PROJ_API_H
// 将 GPS 转换为 UTM 坐标
void UTM2GPS(double& utm_x, double& utm_y, double utm_z);

// 点类，表示经纬度坐标
class Point {
 public:
  double x;  // 经度
  double y;  // 纬度

  Point() : x(0), y(0) {}
  Point(double xx, double yy) : x(xx), y(yy) {}

  template <typename T>
  Point(const T& p) : x(p.x), y(p.y) {}

  template <typename T>
  void setPoint(const T& p) {
    x = p.x;
    y = p.y;
  }

  template <typename T>
  void setPoint(T _x, T _y) {
    x = _x;
    y = _y;
  }

  bool operator==(const Point& A) const {
    return (x == A.x && y == A.y);
  }

  Point& operator=(const Point& A) {
    if (this != &A) {
      x = A.x;
      y = A.y;
    }
    return *this;
  }

  Point operator-() const {
    return Point(-x, -y);
  }

  Point operator-(const Point& A) const {
    return Point(x - A.x, y - A.y);
  }

  Point operator+(const Point& A) const {
    return Point(x + A.x, y + A.y);
  }

  template <typename T>
  Point operator*(T b) const {
    return Point(x * b, y * b);
  }

  template <typename T>
  Point operator/(T b) const {
    return (*this) * (1.0 / b);
  }

  friend Point dotMultiMat(const Point& A, const Point& B);
  friend Point dotDevideMat(const Point& A, const Point& B);
  friend double dot(const Point& A, const Point& B);
  friend double cross(const Point& A, const Point& B);
};

// 将 WGS84 坐标转换为 UTM
template <typename TT>
Point GPS2UTM(const TT& gpsP) {
  const double c_fA = 6378.137;    // 地球半径，单位：km
  const double c_fE = 0.0818192;   // 椭球偏心率
  const double c_fK0 = 0.9996;     // 比例因子
  const double c_fE0 = 500;        // 偏移量
  const double c_fN0 = 0;          // 偏移量

  long zoneNum = static_cast<long>(gpsP.x / 6) + 31;
  double lamda0 = (zoneNum - 1) * 6 - 180 + 3;
  lamda0 = lamda0 * M_PI / 180.0;
  double phi = gpsP.y * M_PI / 180.0;
  double lamda = gpsP.x * M_PI / 180.0;

  double v = 1.0 / sqrt(1 - pow(c_fE, 2) * pow(sin(phi), 2));
  double A = (lamda - lamda0) * cos(phi);
  double T = tan(phi) * tan(phi);
  double C = pow(c_fE, 2) * cos(phi) * cos(phi) / (1 - pow(c_fE, 2));

  double s = (1 - pow(c_fE, 2) / 4.0 - 3 * pow(c_fE, 4) / 64.0 - 5 * pow(c_fE, 6) / 256.0) * phi -
              (3 * pow(c_fE, 2) / 8.0 + 3 * pow(c_fE, 4) / 32.0 + 45 * pow(c_fE, 6) / 1024.0) * sin(2 * phi) +
              (15 * pow(c_fE, 4) / 256.0 + 45 * pow(c_fE, 6) / 1024.0) * sin(4 * phi) -
              35 * pow(c_fE, 6) / 3072.0 * sin(6 * phi);

  double UTME = c_fE0 + c_fK0 * c_fA * v * (A + (1 - T + C) * pow(A, 3) / 6 + (5 - 18 * T + pow(T, 2)) * pow(A, 5) / 120);
  double UTMN = c_fN0 + c_fK0 * c_fA * (s + v * tan(phi) * (pow(A, 2) / 2 + (5 - T + 9 * C + 4 * pow(C, 2)) * pow(A, 4) / 24 + (61 - 58 * T + pow(T, 2)) * pow(A, 6) / 720.0));

  return Point(UTME * 1000, UTMN * 1000);  // 返回点的坐标
}

