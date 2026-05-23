#pragma once
#include "modules/screen/screen.h"
#include <SFML/Graphics.hpp>

class Screen;
class Game;

class FightModule : public Screen
{
public:
    Game &_game;
    FightModule(Game &game);
    ~FightModule() override = default;
    // void handle_frame_signal() override;
    void handle_event(const sf::Event &event) override;
};