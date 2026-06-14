#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class FightModule;

// Одна полоска (HP или Stamina).
// Красный фон + цветной передний план, который сжимается при уменьшении значения.
class HealthBar
{
    sf::RectangleShape *_bg = nullptr;
    sf::RectangleShape *_fg = nullptr;
    float _full_width = 0.f;
    bool _flip = false; // false = сжимается справа (Player A)
                        // true  = сжимается слева  (Player B)
public:
    void bind(sf::RectangleShape *bg, sf::RectangleShape *fg,
              float full_width, bool flip);

    void update(float value_percent); // 0..100
};

// HudTexts хранит указатель на sf::Text таймера и текст счёта,
// чтобы update_hud мог менять их каждый кадр.
struct HudTexts
{
    sf::Text *timer_text = nullptr;
    sf::Text *score_text = nullptr;
};

void init_health_bars(FightModule *fm);
void update_health_bars(FightModule *fm);