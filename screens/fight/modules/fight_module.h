#pragma once
#include "modules/screen/screen.h"
#include "modules/constants/constants.h"
#include "screens/fight/modules/player.h"
#include "screens/fight/modules/sounds/sounds.h"
#include "modules/timers/timers.h"
#include "screens/fight/modules/battle_message/battle_message.h"
#include <SFML/Graphics.hpp>

class Screen;
class Game;

class FightModule : public Screen
{
    int _fight_timer_sec = MATCH_DURATION_SEC;
    int _player_a_wins = 0;
    int _player_b_wins = 0;
    int _current_round = 1;
    bool _is_pause = false;
    bool _finish_him_played = false;
    bool _go_to_menu = false; // флаг: перейти в меню в начале следующего кадра

    // -1 = таймер ещё не создан для этого раунда
    int _timer_id_a = -1;
    int _timer_id_b = -1;

    // Член класса, не static — сбрасывается при каждом новом FightModule
    sf::Clock _sec_clock;

    void end_fight(bool force_end);
    void pause_fight();
    void continue_fight();
    void tick_time();
    void track_hp();

public:
    Player player_A;
    Player player_B;
    BattleMessage battle_message;
    Sounds sounds;
    Timers timers;

    FightModule(Game &game);
    ~FightModule() override = default;
    void handle_frame_signal() override;
    void handle_event(const sf::Event &event) override;

    int get_timer_sec() const { return _fight_timer_sec; }
    int get_wins_a() const { return _player_a_wins; }
    int get_wins_b() const { return _player_b_wins; }
};