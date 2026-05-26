#include "main_menu_module.h"
#include "modules/game/game.h"
#include "screens/main_menu/components/bg_select.h"
#include "modules/character/character.h"
#include "modules/character_rect_texture/character_rect_texture.h"
#include "screens/main_menu/components/characters/characters.h"
#include "screens/main_menu/components/character_select.h"
#include "iostream"
#include "cmath"
#include <algorithm>

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
    _game.selected_character_A = (*_characters)[0];
    _game.selected_character_B = (*_characters)[0];
    init_bg_select(this);
    init_char_select(this, 0, false);
    init_char_select(this, 400, true);
};

void MainMenuModule::handle_event(const sf::Event &event)
{
    if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::I)
        {
            prev_bg();
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::O)
        {
            next_bg();
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::W)
        {
            change_character(CHARACTERS_IN_ROW, _active_character_a_index, false);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::A)
        {
            change_character(-1, _active_character_a_index, false);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::S)
        {
            change_character(-CHARACTERS_IN_ROW, _active_character_a_index, false);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::D)
        {
            change_character(1, _active_character_a_index, false);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
        {
            change_character(CHARACTERS_IN_ROW, _active_character_b_index, true);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
        {
            change_character(-1, _active_character_b_index, true);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
        {
            change_character(-CHARACTERS_IN_ROW, _active_character_b_index, true);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
        {
            change_character(1, _active_character_b_index, true);
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            _game._window->close();
        }
        if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
        {
            _game.set_current_screen(CURRENT_SCREEN::MATCH);
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

void MainMenuModule::change_character(const int &shift, int &active_index, const bool &is_character_B)
{
    if (_characters->empty())
        return;

    int current_row = active_index / CHARACTERS_IN_ROW;
    int current_column = active_index % CHARACTERS_IN_ROW;

    int characters_qty = _characters->size();
    int last_row_index = (characters_qty - 1) / CHARACTERS_IN_ROW;

    auto wrap = [](int value, int size)
    {
        return ((value % size) + size) % size;
    };

    int new_row = current_row;
    int new_column = current_column;

    // select left / right
    if (std::abs(shift) < CHARACTERS_IN_ROW)
    {
        int columns_in_current_row = std::min(
            CHARACTERS_IN_ROW,
            characters_qty - current_row * CHARACTERS_IN_ROW);

        new_column = wrap(current_column + shift, columns_in_current_row);
    }
    // select up / down
    else
    {
        int row_shift = shift / CHARACTERS_IN_ROW;

        int rows_in_current_column =
            ((characters_qty - 1 - current_column) / CHARACTERS_IN_ROW) + 1;

        new_row = wrap(current_row + row_shift, rows_in_current_column);
    }

    int prev_index = active_index;
    active_index = new_row * CHARACTERS_IN_ROW + new_column;
    if (is_character_B)
    {
        _game.selected_character_B = (*_characters)[active_index];
    }
    else
    {
        _game.selected_character_A = (*_characters)[active_index];
    }
    upd_selected_rect(prev_index, active_index, is_character_B);
    upd_selected_char_text(active_index, is_character_B);
}

void MainMenuModule::upd_selected_rect(const int &prev_index, const int &next_index, const bool &is_character_B)
{
    auto old_it = std::find_if(_game.shapes.begin(), _game.shapes.end(),
                               [prev_index, is_character_B](const std::unique_ptr<sf::Drawable> &p)
                               {
                                   CharacterRectTexture *rect = dynamic_cast<CharacterRectTexture *>(p.get());
                                   return rect && rect->element_index == prev_index && rect->is_character_b == is_character_B;
                               });

    if (old_it != _game.shapes.end())
    {
        auto *rect = dynamic_cast<CharacterRectTexture *>(old_it->get());
        rect->setOutlineColor(sf::Color::Transparent);
    };

    auto new_it = std::find_if(_game.shapes.begin(), _game.shapes.end(),
                               [next_index, is_character_B](const std::unique_ptr<sf::Drawable> &p)
                               {
                                   CharacterRectTexture *rect = dynamic_cast<CharacterRectTexture *>(p.get());
                                   return rect && rect->element_index == next_index && rect->is_character_b == is_character_B;
                               });

    if (new_it != _game.shapes.end())
    {
        auto *rect = dynamic_cast<CharacterRectTexture *>(new_it->get());
        rect->setOutlineColor(sf::Color::Red);
    };
}

void MainMenuModule::upd_selected_char_text(const int &next_index, const bool &is_character_B)
{
    auto text_it = std::find_if(_game.shapes.begin(), _game.shapes.end(),
                                [is_character_B](const std::unique_ptr<sf::Drawable> &p)
                                {
                                    CharacterNameText *rect = dynamic_cast<CharacterNameText *>(p.get());
                                    return rect && rect->is_character_b == is_character_B;
                                });

    if (text_it != _game.shapes.end())
    {
        auto *text = dynamic_cast<CharacterNameText *>(text_it->get());
        std::string msg = "Fighter: " + (*_characters)[next_index].get_name();
        text->setString(msg);
    };
}