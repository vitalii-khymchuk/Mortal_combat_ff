#include "pause_text.h"
#include "modules/character_rect_texture/character_rect_texture.h"
#include "modules/game/game.h"
#include <algorithm>

namespace
{
    void center_text_x(sf::Text &text, float x, float y)
    {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(sf::Vector2f(
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f));
        text.setPosition(sf::Vector2f(x, y));
    }
}

void init_pause_text(Game &_game)
{
    const auto window_size = _game._window->getSize();
    const float center_x = window_size.x / 2.f;
    const float window_h = window_size.y * 1.f;

    auto title = std::make_unique<FightPauseText>(_game.game_font, "PAUSE", 72);
    title->setFillColor(sf::Color::White);
    title->setStyle(sf::Text::Bold);
    center_text_x(*title, center_x, window_h * 0.22f);
    title->scale(sf::Vector2f(2.f, 2.f));

    auto controls = std::make_unique<FightPauseText>(
        _game.game_font,
        "Controls:\n"
        "Player A:   A / D - move, W - jump, S - block F - hand kick, G - leg kick\n"
        "Player B:   Left / Right - move, Up - jump, Down - block, < - hand kick, > - leg kick",
        24);
    controls->setFillColor(sf::Color::White);
    center_text_x(*controls, center_x, window_h * 0.48f);

    auto footer = std::make_unique<FightPauseText>(
        _game.game_font,
        "ESC  -> to main menu                ENTER -> continue fight",
        26);
    footer->setFillColor(sf::Color(220, 220, 220));
    center_text_x(*footer, center_x, window_h * 0.88f);

    _game.shapes.emplace_back(std::move(title));
    _game.shapes.emplace_back(std::move(controls));
    _game.shapes.emplace_back(std::move(footer));
}

void remove_pause_texts(Game &_game)
{
    auto &shapes = _game.shapes;

    shapes.erase(
        std::remove_if(shapes.begin(), shapes.end(),
                       [](const auto &ptr)
                       {
                           return dynamic_cast<FightPauseText *>(ptr.get()) != nullptr;
                       }),
        shapes.end());
}