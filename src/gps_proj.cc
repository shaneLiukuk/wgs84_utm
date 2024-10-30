
#include "gps_proj.h"
#include <proj_api.h>
#include <cmath>
#include <string>
static bool is_init = false;
constexpr double RAD_TO_DEG_LOCAL = 180.0 / M_PI;
static projPJ wgs84pj_target_;
static projPJ utm_source_;
constexpr const char* UTM_ZONE = "50";

void UTM2GPS(double& utm_x, double& utm_y, double utm_z) {
    if (!is_init) {
        std::string str = "+proj=utm +zone=" + std::string(UTM_ZONE) + 
                          " +ellps=WGS84 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs";
        utm_source_ = pj_init_plus(str.c_str());
        wgs84pj_target_ = pj_init_plus("+proj=latlong +ellps=WGS84");

        // Check for initialization errors
        if (utm_source_ == 0 || wgs84pj_target_ == 0) {
            throw std::runtime_error("Failed to initialize PROJ.");
        }
        is_init = true;
    }

    // utm坐标改写为gps坐标
    if (pj_transform(utm_source_, wgs84pj_target_, 1, 1, &utm_x, &utm_y, &utm_z) != 0) {
        throw std::runtime_error("Failed to transform coordinates.");
    }
    utm_x *= RAD_TO_DEG_LOCAL;
    utm_y *= RAD_TO_DEG_LOCAL;
}

// bool Point::operator==(const Point& A) const {
//     return (fabs(x - A.x) < 1e-6) && (fabs(y - A.y) < 1e-6);
// }

// Point& Point::operator=(const Point& A) {
//     if (this != &A) {
//         x = A.x;
//         y = A.y;
//     }
//     return *this;
// }

// Point Point::operator-() const {
//     return Point(-x, -y);
// }

// Point Point::operator-(const Point& A) const {
//     return Point(x - A.x, y - A.y);
// }

// Point Point::operator+(const Point& A) const {
//     return Point(A.x + x, A.y + y);
// }

Point dotMultiMat(const Point A, const Point B) {
    return Point(A.x * B.x, A.y * B.y);
}

Point dotDevideMat(const Point A, const Point B) {
    return Point(A.x / B.x, A.y / B.y);
}

double dot(const Point A, const Point B) {
    return A.x * B.x + A.y * B.y;
}

double cross(const Point A, const Point B) {
    return A.x * B.y - A.y * B.x;
}

