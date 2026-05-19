#include "main_menu_module.h"
#include "modules/game/game.h"
#include "screens/main_menu/components/bg_select.h"
#include "modules/character/character.h"
#include "screens/main_menu/components/characters/characters.h"
#include "iostream"

static int CHARACTERS_IN_ROW = 3;

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

    _characters = std::move(init_characters());
    init_bg_select(this);
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
            if (keyPressed->scancode == sf::Keyboard::Scancode::I)
            {
                prev_bg();
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::O)
            {
                next_bg();
            }
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
}

void MainMenuModule::change_character_a(const int &shift)
{
    int current_row = _active_character_a_index / CHARACTERS_IN_ROW;
    int current_column = _active_character_a_index % CHARACTERS_IN_ROW;

    int delta_row = (current_column + shift) / CHARACTERS_IN_ROW;
    // int delta_column =

    if (_active_character_a_index > 0)
    {
        _active_character_a_index--;
    }
    else
    {
        _active_character_a_index = (_characters->size() - 1);
    }
    _game.selected_character_A = *(_characters->begin() + _active_character_a_index);
}

void MainMenuModule::next_character_a()
{
    if (_active_character_a_index < (_characters->size() - 1))
    {
        _active_character_a_index++;
    }
    else
    {
        _active_character_a_index = 0;
    }
    _game.selected_character_A = *(_characters->begin() + _active_character_a_index);
}

void MainMenuModule::prev_character_b()
{
    if (_active_character_b_index > 0)
    {
        _active_character_b_index--;
    }
    else
    {
        _active_character_b_index = (_characters->size() - 1);
    }
    _game.selected_character_B = *(_characters->begin() + _active_character_b_index);
}

void MainMenuModule::next_character_b()
{
    if (_active_character_b_index < (_characters->size() - 1))
    {
        _active_character_b_index++;
    }
    else
    {
        _active_character_b_index = 0;
    }
    _game.selected_character_B = *(_characters->begin() + _active_character_b_index);
}