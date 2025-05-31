#include <SFML/Graphics.hpp>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "biliardo.hpp"

void disegnaTraiettoriaSFML(const RisultatoBiliardo& risultato, double r1, double r2, double L) {
    // Calcola bounding box
    double xmin = 0.0;
    double xmax = L;
    double ymin = -std::max(r1, r2);
    double ymax = std::max(r1, r2);
    double margin = 0.05 * L;

    // Scala dinamica per adattare la larghezza a 1000 px
    double window_width = 1000.0;
    double window_height = window_width * (ymax - ymin + 2 * margin) / (xmax - xmin + 2 * margin);
    double scale = window_width / (xmax - xmin + 2 * margin);

    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(window_width),
                                         static_cast<unsigned int>(window_height)),
                            "Traiettoria biliardo");
    window.setFramerateLimit(120);

    sf::CircleShape start_dot(4);
    start_dot.setFillColor(sf::Color::Green);

    sf::CircleShape end_dot(4);
    end_dot.setFillColor(sf::Color::Yellow);

    sf::Font font;
    font.loadFromFile("/System/Library/Fonts/SFNSMono.ttf");

    sf::Text testo;
    testo.setFont(font);
    testo.setCharacterSize(16);
    testo.setFillColor(sf::Color::Black);

    std::size_t frame = 1;
    std::size_t passo_animazione = 5;

    Point iniziale = risultato.traiettoria.front();
    Point finale = risultato.traiettoria.back();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal)
                    passo_animazione++;
                if ((event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Hyphen) && passo_animazione > 1)
                    passo_animazione--;
            }
        }

        window.clear(sf::Color::White);

        // Traiettoria parziale
        sf::VertexArray path(sf::LineStrip, frame);
        for (std::size_t i = 0; i < frame && i < risultato.traiettoria.size(); ++i) {
            float px = static_cast<float>((risultato.traiettoria[i].x - xmin + margin) * scale);
            float py = static_cast<float>((ymax - risultato.traiettoria[i].y + margin) * scale);
            path[i].position = sf::Vector2f(px, py);
            path[i].color = sf::Color::Red;
        }
        window.draw(path);

        // Punto iniziale
        float sx = static_cast<float>((iniziale.x - xmin + margin) * scale);
        float sy = static_cast<float>((ymax - iniziale.y + margin) * scale);
        start_dot.setPosition(sx - 4, sy - 4);
        window.draw(start_dot);

        // Punto finale
        float fx = static_cast<float>((finale.x - xmin + margin) * scale);
        float fy = static_cast<float>((ymax - finale.y + margin) * scale);
        end_dot.setPosition(fx - 4, fy - 4);
        window.draw(end_dot);

        // Bordi superiore/inferiore
        sf::VertexArray top_line(sf::LinesStrip, frame);
        sf::VertexArray bottom_line(sf::LinesStrip, frame);
        for (std::size_t i = 0; i < frame && i < risultato.traiettoria.size(); ++i) {
            double x = risultato.traiettoria[i].x;
            double top = pf::bordo_sopra(x, L, r1, r2);
            double bot = pf::bordo_sotto(x, L, r1, r2);
            float px = static_cast<float>((x - xmin + margin) * scale);
            float ptop = static_cast<float>((ymax - top + margin) * scale);
            float pbot = static_cast<float>((ymax - bot + margin) * scale);

            top_line[i].position = sf::Vector2f(px, ptop);
            bottom_line[i].position = sf::Vector2f(px, pbot);
            top_line[i].color = sf::Color::Black;
            bottom_line[i].color = sf::Color::Black;
        }
        window.draw(top_line);
        window.draw(bottom_line);

        // Testo
        std::ostringstream oss;
        oss << "Rimbalzi: " << risultato.rimbalzi << "  | Velocita: " << passo_animazione;
        testo.setString(oss.str());
        testo.setPosition(10.f, 10.f);
        window.draw(testo);

        window.display();

        if (frame < risultato.traiettoria.size())
            frame += passo_animazione;
    }
}
