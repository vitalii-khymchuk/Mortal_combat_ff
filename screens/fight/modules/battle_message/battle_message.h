#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Screen;
class Game;

// Типы сообщений, которые отображаются во время боя
enum class BattleMessageType
{
    FIGHT,      // "FIGHT!" — начало раунда
    ROUND,      // "Round 1 / 2 / 3"
    PLAYER_WON, // "Player 1 Won" / "Player 2 Won"
    DRAW,       // "Draw"
    CUSTOM      // произвольный текст
};

// Drawable-обёртка, чтобы хранить в game.shapes
class BattleMessageDrawable : public sf::Drawable
{
public:
    sf::Text shadow; // тень для эффекта
    sf::Text text;

    BattleMessageDrawable(const sf::Font &font,
                          const sf::String &str,
                          unsigned int size)
        : shadow(font, str, size),
          text(font, str, size)
    {
    }

    ~BattleMessageDrawable() = default;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(shadow, states);
        target.draw(text, states);
    }
};

// Класс управляет отображением сообщений во время боя.
// Принимает указатель на Screen (текущий экран — меню или бой).
// Коллега подключает таймеры через hide() по истечении времени.
class BattleMessage
{
    Screen *_screen; // указатель на текущий экран (меню или бой)
    bool _visible;

    // вспомогательный метод: центрирует текст по X/Y
    static void center_text(sf::Text &t, float cx, float cy);

    // удаляет drawable из game.shapes
    void remove_drawables();

public:
    // screen — указатель на активный экран (Screen*)
    explicit BattleMessage(Screen *screen);
    ~BattleMessage() = default;

    // ---- основные методы ----

    // Показать предустановленное сообщение (FIGHT, ROUND 1/2/3, PLAYER WON, DRAW)
    void show(BattleMessageType type, int player_number = 1, int round_number = 1);

    // Показать произвольное сообщение
    void show_custom(const std::string &message_text,
                     sf::Color color = sf::Color(220, 20, 20),
                     unsigned int font_size = 96);

    // Скрыть сообщение (вызывается коллегой из таймера)
    void hide();

    // Возвращает true, если сообщение сейчас видно
    bool is_visible() const { return _visible; }
};
