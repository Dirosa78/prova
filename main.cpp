
#include <cmath>
#include <exception>
#include <iostream>
#include <random>
#include <string>
#include "biliardo.hpp"
#include "biliardo_SFML.hpp"

// Funzioni per generare y0 e theta0 casuali
double genera_y0(double r1) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> dist(-r1, r1);
    return dist(eng);
}

double genera_theta0() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> dist(-90.0, 90.0);
    return dist(eng);
}

int main(int argc, char* argv[]) {
    try {
        double r1 = 1.0, r2 = 1.0, L = 1.0;
        RisultatoBiliardo risultato;

        if (argc == 6) {
    r1 = std::stod(argv[1]);
    r2 = std::stod(argv[2]);
    L  = std::stod(argv[3]);
    double y0 = std::stod(argv[4]);
    double theta0 = std::stod(argv[5]);

    if (y0 < -r1 || y0 > r1)
        throw std::invalid_argument("y0 deve essere compreso tra -r1 e +r1.");
    if (theta0 < -90.0 || theta0 > 90.0)
        throw std::invalid_argument("theta0 deve essere compreso tra -90 e +90 gradi.");

    risultato = pf::biliardo(y0, theta0, r1, r2, L);
} else if (argc == 4) {
    r1 = std::stod(argv[1]);
    r2 = std::stod(argv[2]);
    L  = std::stod(argv[3]);

    double y0 = genera_y0(r1);
    double theta0 = genera_theta0();

    std::cout << "Parametri generati:\n";
    std::cout << "y0 = " << y0 << ", theta0 = " << theta0 << "\n";

    risultato = pf::biliardo(y0, theta0, r1, r2, L);
}
 else {
            throw std::invalid_argument(
                "Uso corretto:\n"
                "1) ./main r1 r2 L y0 theta0     (y0 ∈ [−r1, +r1], theta0 ∈ [−90°, +90°])\n"
                "2) ./main r1 r2 L                (genera automaticamente y0 e theta0)");
        }

        std::cout << "Rimbalzi: " << risultato.rimbalzi << "\n";
        std::cout << "Punto finale: (" << risultato.traiettoria.back().x << ", "
                  << risultato.traiettoria.back().y << ")\n";

        // Visualizzazione grafica
        disegnaTraiettoriaSFML(risultato, r1, r2, L);

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Errore: " << e.what() << "\n";
        return 1;
    }
}
