/**
 *  @autor tekatod
 *  @date 4/28/17
 */
#include "Pose2D.h"
#include <math.h>

Robot::Pose2D::Pose2D() : m_x(0), m_y(0), m_theta(0) { }

Robot::Pose2D::Pose2D(float x, float y, float theta) : m_x(x), m_y(y), m_theta(theta) {
    this->normalizeTheta();
}

float Robot::Pose2D::X() const {
    return m_x;
}

float Robot::Pose2D::Y() const {
    return m_y;
}

float Robot::Pose2D::Theta() const {
    return m_theta;
}

void Robot::Pose2D::setX(float x) {
    m_x = x;
}

void Robot::Pose2D::setY(float y) {
    m_y = y;
}

void Robot::Pose2D::setTheta(float theta) {
    m_theta = theta;
    this->normalizeTheta();
}

void Robot::Pose2D::normalizeTheta() {
//    while (m_theta < 0) m_theta += 2 * M_PI;
//    m_theta = fmod(m_theta, 2 * M_PI) - M_PI;
    while (m_theta > M_PI) {
        m_theta -= 2 * M_PI;
    }
    while (m_theta < -M_PI) {
        m_theta += 2 * M_PI;
    }
}

Robot::Pose2D Robot::Pose2D::operator+(const Robot::Pose2D &rhs) const {
    Pose2D result(*this);
    result += rhs;
    return result;
}

Robot::Pose2D& Robot::Pose2D::operator+=(const Robot::Pose2D &rhs) {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    m_theta += rhs.m_theta;
    this->normalizeTheta();
    return *this;
}

Robot::Pose2D Robot::Pose2D::operator-(const Robot::Pose2D &rhs) const {
    Pose2D result(*this);
    result -= rhs;
    return result;
}

Robot::Pose2D& Robot::Pose2D::operator-=(const Robot::Pose2D &rhs) {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    m_theta -= rhs.m_theta;
    this->normalizeTheta();
    return *this;
}


void Robot::Pose2D::rotateAround(const Robot::Pose2D& pose) {
    float c = cos(pose.Theta());
    float s = sin(pose.Theta());
    float d_x = m_x - pose.X();
    float d_y = m_y - pose.Y();
    m_x = c * (d_x) - s * (d_y) + pose.X();
    m_y = s * (d_x) + c * (d_y) + pose.Y();
}

namespace Robot {
    std::ostream &operator<<(std::ostream &os, const Robot::Pose2D &data) {
        os << " " << data.m_x << " " << data.m_y << " " << data.m_theta / M_PI * 180;
        return os;
    }
}