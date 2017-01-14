// Copyright (c) 2017 Daniel Pedersen. Subject to the GNU GPLv3.

#ifndef __lattice__space__
#define __lattice__space__

#include <cmath>

class Vector2D {
public:
	Vector2D() : m_x(0.0), m_y(0.0) { }
	Vector2D(double x, double y) : m_x(x), m_y(y) { }

    double& operator[](int c);
    double dot(const Vector2D& v);
    double norm();

    Vector2D operator=(const Vector2D& v);
    Vector2D operator+(const Vector2D& v) const;
    Vector2D operator-(const Vector2D& v) const;
    Vector2D operator*(double k) const;

    friend Vector2D operator*(double k, const Vector2D& v);

private:
	double m_x, m_y;
};

class Cartesian2D {
public:
	typedef Vector2D Vector;
	static const int dim = 2;

    static double distance(const Vector& v1, const Vector& v2);
    static double distance(const double p1[2], const double p2[2]);
    static double distance(double p1x, double p1y, double p2x, double p2y);
};

inline double& Vector2D::operator[](int c)
{
    double* d = NULL;
    if (c == 0)
        return m_x;
    if (c == 1)
        return m_y;
    return *d;
}

inline double Vector2D::dot(const Vector2D& v)
{
    return m_x * v.m_x + m_y * v.m_y;
}

inline double Vector2D::norm()
{
    return sqrt(m_x * m_x + m_y * m_y);
}

inline Vector2D Vector2D::operator=(const Vector2D& v)
{
    m_x = v.m_x;
    m_y = v.m_y;
    return *this;
}

inline Vector2D Vector2D::operator+(const Vector2D& v) const
{
    return Vector2D(m_x + v.m_x, m_y + v.m_y);
}

inline Vector2D Vector2D::operator-(const Vector2D& v) const
{
    return Vector2D(m_x - v.m_x, m_y - v.m_y);
}

inline Vector2D Vector2D::operator*(double k) const
{
    return Vector2D(k * m_x, k * m_y);
}

inline Vector2D operator*(double k, const Vector2D& v)
{
    return Vector2D(k * v.m_x, k * v.m_y);
}

inline double Cartesian2D::distance(const Vector& v1, const Vector& v2)
{
    return (v1 - v2).norm();
}

inline double Cartesian2D::distance(const double p1[2], const double p2[2])
{
    double d[2] = {p1[0] - p2[0], p1[1] - p2[1]};
    return sqrt(d[0]*d[0] + d[1]*d[1]);
}

inline double Cartesian2D::distance(double p1x, double p1y, double p2x, double p2y)
{
    double d[2] = {p1x - p2x, p1y - p2y};
    return sqrt(d[0]*d[0] + d[1]*d[1]);
}

#endif
