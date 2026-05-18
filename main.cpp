#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "modules/game/game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "My window");
    window.setFramerateLimit(60);
    Game game(&window);

    while (window.isOpen())
    {
        game.trig_fps_signal();
        window.clear(sf::Color::Black);

        for (auto &figure : game.shapes)
        {
            window.draw(*figure);
        }

        window.display();
    }

    return 0;
}