#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "biliardo.hpp"

#include "doctest.h"

TEST_CASE("Finale nella zona corretta") {
  RisultatoBiliardo risultato = pf::biliardo(0.3, 30.0, 1.0, 0.5, 1.0);
  Point finale = risultato.traiettoria.back();

  CHECK(finale.x >= 1.0);
  CHECK(finale.y <= pf::bordo_sopra(1.0, 1.0, 1.0, 0.5));
  CHECK(finale.y >= pf::bordo_sotto(1.0, 1.0, 1.0, 0.5));
}

TEST_CASE("Verifica numero rimbalzi minimo") {
  RisultatoBiliardo risultato = pf::biliardo(0.0, 10.0, 1.0, 0.5, 1.0);
  CHECK(risultato.rimbalzi >= 0);
}

TEST_CASE("Controllo con y0 al limite positivo") {
  RisultatoBiliardo risultato = pf::biliardo(1.0, 45.0, 1.0, 0.5, 1.0);
  CHECK(risultato.traiettoria.front().y == doctest::Approx(1.0));
}
