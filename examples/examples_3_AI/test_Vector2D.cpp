#include "Vector2D.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool almost_equal(double a, double b, double eps = 1e-9) {
  return std::fabs(a - b) < eps;
}

void expect(bool condition, const std::string &message, int &failures) {
  if (!condition) {
    std::cerr << "[FAIL] " << message << '\n';
    ++failures;
  }
}

void run_unit_tests(int &failures) {
  {
    Vector2D v;
    expect(almost_equal(v.x(), 0.0), "default ctor sets x to 0", failures);
    expect(almost_equal(v.y(), 0.0), "default ctor sets y to 0", failures);
    expect(v.label().empty(), "default ctor sets empty label", failures);
  }

  {
    Vector2D v("custom", 3.0, 4.0);
    expect(v.label() == "custom", "labeled ctor stores label", failures);
    expect(almost_equal(v.x(), 3.0), "labeled ctor sets x", failures);
    expect(almost_equal(v.y(), 4.0), "labeled ctor sets y", failures);
    expect(almost_equal(v.norm(), 5.0), "norm computes hypot", failures);
  }

  {
    Vector2D v(1.0, 2.0);
    expect(v.label().rfind("vec_", 0) == 0,
           "(x,y) ctor auto label has vec_ prefix", failures);
  }

  {
    Vector2D a("a", 0.0, 0.0);
    Vector2D b("b", 3.0, 4.0);
    expect(almost_equal(a.distance_to(b), 5.0),
           "distance_to computes Euclidean distance", failures);
  }

  {
    Vector2D a("a", 1.0, 2.0);
    Vector2D b("b", 3.5, -1.0);

    Vector2D sum = a + b;
    expect(almost_equal(sum.x(), 4.5), "operator+ x", failures);
    expect(almost_equal(sum.y(), 1.0), "operator+ y", failures);

    Vector2D diff = a - b;
    expect(almost_equal(diff.x(), -2.5), "operator- x", failures);
    expect(almost_equal(diff.y(), 3.0), "operator- y", failures);

    Vector2D scaled = a * 2.0;
    expect(almost_equal(scaled.x(), 2.0), "operator* x", failures);
    expect(almost_equal(scaled.y(), 4.0), "operator* y", failures);
  }

  {
    Vector2D v("mutable", 1.0, 1.0);
    v.set(-2.0, 7.5);
    expect(almost_equal(v.x(), -2.0), "set updates x", failures);
    expect(almost_equal(v.y(), 7.5), "set updates y", failures);
  }

  {
    expect(Vector2D::to_csv_header() == "label,x,y", "to_csv_header format",
           failures);

    Vector2D v("csv", 1.25, -2.5);
    expect(v.to_csv_row() == "csv,1.25,-2.5", "to_csv_row format", failures);

    std::ostringstream oss;
    oss << v;
    expect(oss.str() == "[csv] (1.25, -2.5)", "operator<< format", failures);
  }
}

void run_smoke_and_timing_test(int &failures) {
  auto start = std::chrono::steady_clock::now();

  std::vector<Vector2D> vectors;
  vectors.reserve(100);

  for (int i = 0; i < 100; ++i) {
    vectors.emplace_back("v" + std::to_string(i), static_cast<double>(i),
                         static_cast<double>(i + 1));
  }

  double norm_accumulator = 0.0;
  Vector2D running_sum("sum", 0.0, 0.0);

  for (const auto &v : vectors) {
    norm_accumulator += v.norm();
    running_sum = running_sum + v;
  }

  auto end = std::chrono::steady_clock::now();
  auto elapsed_us =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  expect(vectors.size() == 100, "smoke: vector contains 100 elements",
         failures);
  expect(norm_accumulator > 0.0, "smoke: accumulated norm is positive",
         failures);
  expect(running_sum.x() > 0.0 && running_sum.y() > 0.0,
         "smoke: running sum uses vector values", failures);

  std::cout << "[INFO] Smoke timing (100 Vector2D create+use): " << elapsed_us
            << " us\n";

  expect(elapsed_us >= 0, "timing: elapsed time is non-negative", failures);
  expect(elapsed_us < 2'000'000,
         "timing: operation should stay under 2 seconds", failures);
}

} // namespace

int main() {
  int failures = 0;

  run_unit_tests(failures);
  run_smoke_and_timing_test(failures);

  if (failures == 0) {
    std::cout << "All Vector2D tests passed." << '\n';
    return 0;
  }

  std::cerr << failures << " test(s) failed." << '\n';
  return 1;
}
