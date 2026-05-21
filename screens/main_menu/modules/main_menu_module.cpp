#include "main_menu_module.h"
#include "modules/game/game.h"
#include "screens/main_menu/components/bg_select.h"
#include "screens/main_menu/components/character_select.h"
#include "iostream"

MainMenuModule::MainMenuModule(Game &game) : Screen(), _game(game)
{
    // placeholder
    //  std::unique_ptr<sf::RectangleShape> rectangle = std::make_unique<sf::RectangleShape>((sf::Vector2f(120.0f, 60.0f)));
    //  rectangle->setPosition(sf::Vector2f(500.0f, 400.0f));
    //  rectangle->setFillColor(sf::Color(100, 50, 250));

    // game.shapes.emplace_back(std::move(rectangle));

    for (auto path : bg_paths)
    {
        sf::Texture bg_texture;

        if (!bg_texture.loadFromFile(path))
        {
            throw std::runtime_error("Background picture path is not valid: " + path);
        }
        _bg_textures.emplace_back(bg_texture);
    }
    if (bg_paths.size())
    {
        _game.set_selected_bg(_bg_textures[0]);
    };
    init_bg_select(this);
    init_char_select(this);
};

void MainMenuModule::handle_frame_signal()
{
    while (auto event = _game._window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            _game._window->close();
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::I)
            {
                prev_bg();
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::O)
            {
                next_bg();
            }
        }
    }
}

void MainMenuModule::prev_bg()
{
    if (_active_bg_index > 0)
    {
        _active_bg_index--;
    }
    else
    {
        _active_bg_index = (_bg_textures.size() - 1);
    }
    _game.set_selected_bg(*(_bg_textures.begin() + _active_bg_index));
    // add to shapes
}

void MainMenuModule::next_bg()
{
    if (_active_bg_index < (_bg_textures.size() - 1))
    {
        _active_bg_index++;
    }
    else
    {
        _active_bg_index = 0;
    }
    _game.set_selected_bg(*(_bg_textures.begin() + _active_bg_index));
    // add to shapes
}