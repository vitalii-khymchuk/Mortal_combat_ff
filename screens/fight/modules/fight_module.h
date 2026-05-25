#pragma once
#include "modules/screen/screen.h"
#include <SFML/Graphics.hpp>

class Screen;
class Game;
class Player;

class FightModule : public Screen
{
    int _timer_sec;
    int _player_a_wins;
    int _player_b_wins;

public:
    Game &_game;
    Player *player_A;
    Player *player_B;

    FightModule(Game &game);
    ~FightModule() override = default;
    // void handle_frame_signal() override;
    void handle_event(const sf::Event &event) override;
};