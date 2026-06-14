#include "battle_message.h"

#include "modules/screen/screen.h"
#include "modules/game/game.h"

#include <algorithm>

// ─── вспомогательные константы ────────────────────────────────────────────────

namespace
{
    // Стиль главного текста "FIGHT!"
    const unsigned int FIGHT_FONT_SIZE = 108;
    const unsigned int ROUND_FONT_SIZE = 72;
    const unsigned int WINNER_FONT_SIZE = 80;

    // Цвета
    const sf::Color COLOR_FIGHT{220, 20, 20};    // ярко-красный
    const sf::Color COLOR_ROUND{255, 200, 0};    // золотой
    const sf::Color COLOR_WINNER{255, 255, 255}; // белый
    const sf::Color COLOR_DRAW{150, 150, 255};   // светло-синий
    const sf::Color COLOR_SHADOW{0, 0, 0, 160};  // полупрозрачная тень

    const sf::Vector2f SHADOW_OFFSET{4.f, 4.f};
}

// ─── приватный метод: центрирование текста ────────────────────────────────────

void BattleMessage::center_text(sf::Text &t, float cx, float cy)
{
    sf::FloatRect b = t.getLocalBounds();
    t.setOrigin(sf::Vector2f(
        b.position.x + b.size.x / 2.f,
        b.position.y + b.size.y / 2.f));
    t.setPosition(sf::Vector2f(cx, cy));
}

// ─── приватный метод: удалить drawable-ы из game.shapes ──────────────────────

void BattleMessage::remove_drawables()
{
    auto &shapes = _screen->_game.shapes;
    shapes.erase(
        std::remove_if(shapes.begin(), shapes.end(),
                       [](const std::unique_ptr<sf::Drawable> &ptr)
                       {
                           return dynamic_cast<BattleMessageDrawable *>(ptr.get()) != nullptr;
                       }),
        shapes.end());
}

// ─── конструктор ──────────────────────────────────────────────────────────────

BattleMessage::BattleMessage(Screen *screen)
    : _screen(screen), _visible(false)
{
}

// ─── show (предустановленный тип) ─────────────────────────────────────────────

void BattleMessage::show(BattleMessageType type, int player_number, int round_number)
{
    std::string text_str;
    sf::Color text_color;
    unsigned int font_size;

    switch (type)
    {
    case BattleMessageType::FIGHT:
        text_str = "FIGHT!";
        text_color = COLOR_FIGHT;
        font_size = FIGHT_FONT_SIZE;
        break;

    case BattleMessageType::ROUND:
        text_str = "Round " + std::to_string(round_number);
        text_color = COLOR_ROUND;
        font_size = ROUND_FONT_SIZE;
        break;

    case BattleMessageType::PLAYER_WON:
        text_str = "Player " + std::to_string(player_number) + " Won!";
        text_color = COLOR_WINNER;
        font_size = WINNER_FONT_SIZE;
        break;

    case BattleMessageType::DRAW:
        text_str = "Draw!";
        text_color = COLOR_DRAW;
        font_size = WINNER_FONT_SIZE;
        break;

    case BattleMessageType::CUSTOM:
        // для CUSTOM используй show_custom()
        return;
    }

    show_custom(text_str, text_color, font_size);
}

// ─── show_custom ──────────────────────────────────────────────────────────────

void BattleMessage::show_custom(const std::string &message_text,
                                sf::Color color,
                                unsigned int font_size)
{
    // Если уже что-то показано — сначала убираем
    if (_visible)
        remove_drawables();

    Game &game = _screen->_game;
    const sf::Font &font = game.game_font;

    const auto win_size = game._window->getSize();
    const float cx = win_size.x / 2.f;
    const float cy = win_size.y * 0.35f; // ~верхняя треть экрана (как "FIGHT!" на скрине)

    auto drawable = std::make_unique<BattleMessageDrawable>(font, message_text, font_size);

    // Настройка основного текста
    drawable->text.setFillColor(color);
    drawable->text.setStyle(sf::Text::Bold);
    center_text(drawable->text, cx, cy);

    // Настройка тени (чуть смещена, тёмная)
    drawable->shadow.setFillColor(COLOR_SHADOW);
    drawable->shadow.setStyle(sf::Text::Bold);
    center_text(drawable->shadow,
                cx + SHADOW_OFFSET.x,
                cy + SHADOW_OFFSET.y);

    game.shapes.emplace_back(std::move(drawable));
    _visible = true;
}

// ─── hide ─────────────────────────────────────────────────────────────────────

void BattleMessage::hide()
{
    if (!_visible)
        return;

    remove_drawables();
    _visible = false;
}
