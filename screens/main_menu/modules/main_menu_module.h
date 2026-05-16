#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "modules/screen/screen.h"

class Screen;
class Game;

class MainMenuModule : public Screen
{
    std::vector<std::unique_ptr<sf::Drawable>> _backgrounds;
    Game &_game;

public:
    MainMenuModule(Game &game) : Screen(), _game(game) {};
    ~MainMenuModule() override = default;
    void handle_frame_signal() override;
};