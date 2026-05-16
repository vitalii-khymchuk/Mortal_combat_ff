#include "main_menu_module.h"
#include "modules/game/game.h"
#include "iostream"

MainMenuModule::MainMenuModule(Game &game) : Screen(), _game(game)
{
    std::unique_ptr<sf::RectangleShape> rectangle = std::make_unique<sf::RectangleShape>((sf::Vector2f(120.0f, 60.0f)));
    rectangle->setPosition(sf::Vector2f(500.0f, 400.0f));
    rectangle->setFillColor(sf::Color(100, 50, 250));

    game.shapes.emplace_back(std::move(rectangle));
};

void MainMenuModule::handle_frame_signal()
{
    while (auto event = _game._window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            _game._window->close();
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            std::cout << "Key pressed" << std::endl;
        }
    }
}