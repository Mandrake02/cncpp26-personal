#include "Vector2D.h"

#include <cmath>

Vector2D::Vector2D()
    : _x(0.0), _y(0.0), _label("vec_" + std::to_string(++_vector_count)) {}

Vector2D::Vector2D(double x, double y)
    : _x(x), _y(y), _label("vec_" + std::to_string(++_vector_count)) {}

double Vector2D::x() const {
    return _x;
}

double Vector2D::y() const {
    return _y;
}

double Vector2D::norm() const {
    return std::sqrt(_x * _x + _y * _y);
}

double Vector2D::distance_to(const Vector2D& other) const {
    const double dx = _x - other._x;
    const double dy = _y - other._y;
    return std::sqrt(dx * dx + dy * dy);
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(_x + other._x, _y + other._y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(_x - other._x, _y - other._y);
}

Vector2D Vector2D::operator*(double scalar) const {
    return Vector2D(_x * scalar, _y * scalar);
}

std::string Vector2D::to_csv_row() const {
    std::string escaped_label;
    escaped_label.reserve(_label.size());

    for (char c : _label) {
        if (c == '"') {
            escaped_label += "\"\"";
        } else {
            escaped_label += c;
        }
    }

    return "\"" + escaped_label + "\"," + std::to_string(_x) + "," + std::to_string(_y);
}

std::string Vector2D::to_csv_header() {
    return "label,x,y";
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x() << ", " << v.y() << ")";
    return os;
}
