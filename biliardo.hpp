#pragma once
#include <vector>

struct Point {
  double x, y;
};

struct RisultatoBiliardo {
  std::vector<Point> traiettoria;
  int rimbalzi;
};

namespace pf {

double bordo_sopra(double x, double L, double r1, double r2);
double bordo_sotto(double x, double L, double r1, double r2);

RisultatoBiliardo biliardo(double y0, double theta0_deg, double r1, double r2,
                           double L);
}