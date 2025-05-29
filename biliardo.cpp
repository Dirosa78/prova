#include "biliardo.hpp"

#include <cmath>

namespace pf {

const double PI = 3.141592653589793;

double bordo_sopra(double x, double L, double r1, double r2) {
  return r1 + (r2 - r1) * (x / L);
}

double bordo_sotto(double x, double L, double r1, double r2) {
  return -bordo_sopra(x, L, r1, r2);
}

RisultatoBiliardo biliardo(double y0, double theta0_deg, double r1, double r2,
                           double L) {
  std::vector<Point> traiettoria;
  int rimbalzi = 0;

  double theta = theta0_deg * PI / 180.0;
  double x = 0.0, y = y0;
  double vx = std::cos(theta);
  double vy = std::sin(theta);

  traiettoria.push_back({x, y});

  double dt = 0.001;

  while (x < L) {
    double next_x = x + vx * dt;
    double next_y = y + vy * dt;

    double top = bordo_sopra(next_x, L, r1, r2);
    double bottom = bordo_sotto(next_x, L, r1, r2);

    if (next_y >= top || next_y <= bottom) {
      vy = -vy;
      ++rimbalzi;
    }

    x += vx * dt;
    y += vy * dt;

    traiettoria.push_back({x, y});
  }

  return {traiettoria, rimbalzi};
}

}  


