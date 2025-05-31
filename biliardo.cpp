#include "biliardo.hpp"
#include <cmath>
#include <vector>

namespace pf {

const double PI = 3.141592653589793;

double bordo_sopra(double x, double L, double r1, double r2) {
    return r1 + (r2 - r1) * (x / L);
}

double bordo_sotto(double x, double L, double r1, double r2) {
    return -bordo_sopra(x, L, r1, r2);
}

RisultatoBiliardo biliardo(double y0, double theta0_deg, double r1, double r2, double L) {
    std::vector<Point> traiettoria;
    int rimbalzi = 0;

    double theta = theta0_deg * PI / 180.0;
    double x = 0.0;
    double y = y0;

    traiettoria.push_back({x, y});

    double m = std::tan(theta); // coefficiente angolare iniziale

    while (x < L) {
        // Determina punto di impatto
        double x_next, y_next;

        if (m > 0) {
            // Intersezione con bordo superiore
            x_next = (bordo_sopra(x, L, r1, r2) - y + m * x) / m;
            y_next = bordo_sopra(x_next, L, r1, r2);
        } else {
            // Intersezione con bordo inferiore
            x_next = (bordo_sotto(x, L, r1, r2) - y + m * x) / m;
            y_next = bordo_sotto(x_next, L, r1, r2);
        }

        if (x_next > L) {
            // La particella esce: calcola posizione su x = L
            double y_exit = m * (L - x) + y;
            traiettoria.push_back({L, y_exit});
            break;
        }

        // Aggiungi punto di urto
        traiettoria.push_back({x_next, y_next});
        ++rimbalzi;

        // Riflessione: riflette il coefficiente angolare
        m = -m;

        // Nuovo punto di partenza
        x = x_next;
        y = y_next;
    }

    return {traiettoria, rimbalzi};
}

} // namespace pf
