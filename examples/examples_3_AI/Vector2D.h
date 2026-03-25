#pragma once

#include <cstddef>
#include <iostream>
#include <string>

class Vector2D {
public:
    Vector2D();
    Vector2D(double x, double y);

    double x() const;
    double y() const;

    double norm() const;

    double distance_to(const Vector2D& other) const;

    Vector2D operator+(const Vector2D& other) const;

    Vector2D operator-(const Vector2D& other) const;

    Vector2D operator*(double scalar) const;

    std::string to_csv_row() const;

    static std::string to_csv_header();

private:
    inline static std::size_t _vector_count = 0;

    double _x;
    double _y;
    std::string _label;
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v);


