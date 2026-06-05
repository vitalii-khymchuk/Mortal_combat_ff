#pragma once
#include "modules/screen/screen.h"
#include "modules/constants/constants.h"
#include "screens/fight/modules/player.h"
#include <SFML/Graphics.hpp>

class Screen;
class Game;

class FightModule : public Screen
{
    int _timer_sec = MATCH_DURATION_SEC;
    int _player_a_wins = 0;
    int _player_b_wins = 0;
    int _current_round = 1;
    bool _is_pause = false;

    void end_fight(bool _force_end);
    void pause_fight();
    void continue_fight();
    void tick_time();
    void track_hp();

public:
    Game &_game;
    Player player_A;
    Player player_B;

    FightModule(Game &game);
    ~FightModule() override = default;
    void handle_frame_signal() override;
    void handle_event(const sf::Event &event) override;
};