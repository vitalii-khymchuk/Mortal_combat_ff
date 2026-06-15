#include "health_bar.h"
#include "screens/fight/modules/fight_module/fight_module.h"
#include <algorithm>
#include <memory>
#include "modules/character/character.h"

// ── Размеры окна ─────────────────────────────────────────────────────────────
static constexpr float WINDOW_W = 800.f;

// ── Аватарки ──────────────────────────────────────────────────────────────────
static constexpr float AVATAR_W = 70.f;
static constexpr float AVATAR_H = 70.f;
static constexpr float AVATAR_Y = 5.f;

// ── Центральная зона (таймер + счёт) ─────────────────────────────────────────
static constexpr float CENTER_W = 120.f;
static constexpr float CENTER_X = (WINDOW_W - CENTER_W) / 2.f; // 340

// ── Полоски ───────────────────────────────────────────────────────────────────
static constexpr float BAR_X_A = 83.f;
static constexpr float BAR_W = CENTER_X - BAR_X_A - 5.f;
static constexpr float BAR_X_B = WINDOW_W - 83.f - BAR_W;

static constexpr float HP_Y = 15.f;
static constexpr float STA_Y = HP_Y + 20.f + 5.f;
static constexpr float BAR_H = 18.f;

// ── Цвета ─────────────────────────────────────────────────────────────────────
static const sf::Color GREEN = sf::Color(0, 200, 50);
static const sf::Color BLUE = sf::Color(50, 180, 255);
static const sf::Color RED = sf::Color(180, 30, 30);
static const sf::Color WHITE = sf::Color(220, 220, 220);

// ── Статичные объекты (сбрасываются при каждом init_health_bars) ──────────────
static HealthBar s_hp_a, s_sta_a, s_hp_b, s_sta_b;
static HudTexts s_hud;

// ─────────────────────────────────────────────────────────────────────────────

void HealthBar::bind(sf::RectangleShape *bg, sf::RectangleShape *fg,
                     float full_width, bool flip)
{
    _bg = bg; // _bg - background (red rectangle (always 100%))
    _fg = fg; //_fg - frontground (green/blue rectangle)
    _full_width = full_width;
    _flip = flip;
}

void HealthBar::update(float value_percent)
{
    if (!_bg || !_fg) // т.е. указывают на пустоту
        return;
    float pct = std::max(0.f, std::min(100.f, value_percent));
    float fg_width = _full_width * (pct / 100.f);
    _fg->setSize(sf::Vector2f(fg_width, _fg->getSize().y));
    if (_flip)
    {
        float right_edge = _bg->getPosition().x + _full_width;
        _fg->setPosition(sf::Vector2f(right_edge - fg_width, _fg->getPosition().y));
    }
}

// ── Вспомогательные функции ───────────────────────────────────────────────────

static std::pair<sf::RectangleShape *, sf::RectangleShape *>
make_bar(FightModule *fm, float x, float y, float w, float h,
         const sf::Color &fg_color)
{
    auto bg = std::make_unique<sf::RectangleShape>(sf::Vector2f(w, h));
    bg->setPosition(sf::Vector2f(x, y));
    bg->setFillColor(RED);
    bg->setOutlineColor(WHITE);
    bg->setOutlineThickness(2.f);

    auto fg = std::make_unique<sf::RectangleShape>(sf::Vector2f(w, h));
    fg->setPosition(sf::Vector2f(x, y));
    fg->setFillColor(fg_color);

    auto *bg_ptr = bg.get();
    auto *fg_ptr = fg.get();
    fm->_game.shapes.emplace_back(std::move(bg));
    fm->_game.shapes.emplace_back(std::move(fg));
    return {bg_ptr, fg_ptr};
}

static void make_avatar_frame(FightModule *fm, float x, float y)
{
    auto frame = std::make_unique<sf::RectangleShape>(sf::Vector2f(AVATAR_W, AVATAR_H));
    frame->setPosition(sf::Vector2f(x, y));
    frame->setFillColor(sf::Color(0, 0, 0, 180));
    frame->setOutlineColor(sf::Color::White);
    frame->setOutlineThickness(3.f);
    fm->_game.shapes.emplace_back(std::move(frame));
}

static void make_hud_panel(FightModule *fm)
{
    float panel_h = AVATAR_H + AVATAR_Y * 2.f + 5.f;
    auto panel = std::make_unique<sf::RectangleShape>(sf::Vector2f(WINDOW_W, panel_h));
    panel->setPosition(sf::Vector2f(0.f, 0.f));
    panel->setFillColor(sf::Color(0, 0, 0, 210));
    fm->_game.shapes.emplace_back(std::move(panel));
}

// ── Публичные функции ─────────────────────────────────────────────────────────

void init_health_bars(FightModule *fm)
{
    // Сбросить старые указатели (shapes уже очищены в game.set_current_screen)
    s_hp_a = HealthBar{};
    s_sta_a = HealthBar{};
    s_hp_b = HealthBar{};
    s_sta_b = HealthBar{};
    s_hud = HudTexts{};

    // 1. Фоновая панель HUD
    make_hud_panel(fm);

    // 2. Рамки аватарок
    make_avatar_frame(fm, 5.f, AVATAR_Y);
    make_avatar_frame(fm, WINDOW_W - AVATAR_W - 5.f, AVATAR_Y);

    auto avatarka_A = std::make_unique<sf::Sprite>(fm->_game.selected_character_A.get_avatarka());
    sf::Vector2u ava_A_size = (fm->_game.selected_character_A.get_avatarka()).getSize();
    avatarka_A->setScale(sf::Vector2f(AVATAR_W / ava_A_size.x, AVATAR_H / ava_A_size.y));
    avatarka_A->setPosition(sf::Vector2f(5.f, AVATAR_Y));
    fm->_game.shapes.emplace_back(std::move(avatarka_A));

    auto avatarka_B = std::make_unique<sf::Sprite>(fm->_game.selected_character_B.get_avatarka());
    sf::Vector2u ava_B_size = (fm->_game.selected_character_B.get_avatarka()).getSize();
    avatarka_B->setScale(sf::Vector2f(-1 * (AVATAR_W / ava_B_size.x), AVATAR_H / ava_B_size.y));
    avatarka_B->setOrigin(sf::Vector2f(ava_B_size.x, 0.f));
    avatarka_B->setPosition(sf::Vector2f(WINDOW_W - AVATAR_W - 5.f, AVATAR_Y));
    fm->_game.shapes.emplace_back(std::move(avatarka_B));

    // 3. Полоски Player A
    {
        auto [bg, fg] = make_bar(fm, BAR_X_A, HP_Y, BAR_W, BAR_H, GREEN);
        s_hp_a.bind(bg, fg, BAR_W, false);
    }
    {
        auto [bg, fg] = make_bar(fm, BAR_X_A, STA_Y, BAR_W, BAR_H, BLUE);
        s_sta_a.bind(bg, fg, BAR_W, false);
    }

    // 4. Полоски Player B
    {
        auto [bg, fg] = make_bar(fm, BAR_X_B, HP_Y, BAR_W, BAR_H, GREEN);
        s_hp_b.bind(bg, fg, BAR_W, true);
    }
    {
        auto [bg, fg] = make_bar(fm, BAR_X_B, STA_Y, BAR_W, BAR_H, BLUE);
        s_sta_b.bind(bg, fg, BAR_W, true);
    }

    // 5. Таймер (по центру, между полосками)
    //    CENTER_X = 340, CENTER_W = 120 => центр = 340 + 60 = 400
    {
        auto timer = std::make_unique<sf::Text>(fm->_game.game_font, "90", 28);
        timer->setFillColor(sf::Color(255, 210, 0)); // жёлтый как на оригинале
                                                     // timer->setStyle(sf::Text::Bold);
        // Центрируем по X
        sf::FloatRect b = timer->getLocalBounds();
        timer->setOrigin(sf::Vector2f(b.size.x / 2.f, 0.f));
        timer->setPosition(sf::Vector2f(WINDOW_W / 2.f, HP_Y));
        s_hud.timer_text = timer.get();
        fm->_game.shapes.emplace_back(std::move(timer));
    }

    // 6. Счёт (под таймером)
    {
        auto score = std::make_unique<sf::Text>(fm->_game.game_font, "0 : 0", 20);
        score->setFillColor(sf::Color::White);
        sf::FloatRect b = score->getLocalBounds();
        score->setOrigin(sf::Vector2f(b.size.x / 2.f, 0.f));
        score->setPosition(sf::Vector2f(WINDOW_W / 2.f, STA_Y + 2.f));
        s_hud.score_text = score.get();
        fm->_game.shapes.emplace_back(std::move(score));
    }
}

void update_health_bars(FightModule *fm)
{
    // Полоски
    s_hp_a.update(static_cast<float>(fm->player_A._hp_percents));
    s_hp_b.update(static_cast<float>(fm->player_B._hp_percents));
    s_sta_a.update(fm->player_A.get_block_energy_percent());
    s_sta_b.update(fm->player_B.get_block_energy_percent());

    // Таймер
    if (s_hud.timer_text)
    {
        std::string t = std::to_string(fm->get_timer_sec());
        s_hud.timer_text->setString(t);
        // Переcentrируем после смены текста
        sf::FloatRect b = s_hud.timer_text->getLocalBounds();
        s_hud.timer_text->setOrigin(sf::Vector2f(b.size.x / 2.f, 0.f));
    }

    // Счёт
    if (s_hud.score_text)
    {
        std::string s = std::to_string(fm->get_wins_a()) + " : " + std::to_string(fm->get_wins_b());
        s_hud.score_text->setString(s);
        sf::FloatRect b = s_hud.score_text->getLocalBounds();
        s_hud.score_text->setOrigin(sf::Vector2f(b.size.x / 2.f, 0.f));
    }
}