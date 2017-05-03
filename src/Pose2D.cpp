/**
 *  @autor tekatod
 *  @date 4/28/17
 */
#include "Pose2D.h"
#include <math.h>

Robot::Pose2D::Pose2D() : m_x(0), m_y(0), m_theta(0) { }

Robot::Pose2D::Pose2D(double x, double y, double theta) : m_x(x), m_y(y), m_theta(theta) { }

double Robot::Pose2D::getX() const {
    return m_x;
}

double Robot::Pose2D::getY() const {
    return m_y;
}

double Robot::Pose2D::getTheta() const {
    return m_theta;
}

void Robot::Pose2D::setX(double x) {
    m_x = x;
}

void Robot::Pose2D::setY(double y) {
    m_y = y;
}

void Robot::Pose2D::setTheta(double theta) {
    m_theta = theta;
}

void Robot::Pose2D::normalizeTheta() {
    double twoPi = 2 * M_PI;
    m_theta = m_theta - twoPi * floor( m_theta / twoPi );
}

namespace Robot {
    std::ostream &operator<<(std::ostream &os, const Robot::Pose2D &data) {
        os << " " << data.m_x << " " << data.m_y << " " << data.m_theta;
        return os;
    }
}
