#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "modules/screen/screen.h"

class Screen;
class Game;

std::vector<std::string> bg_paths = {};

class MainMenuModule : public Screen
{
    std::vector<sf::Texture> _bg_textures;
    int _active_bg_index = 0;
    // std::vector<std::unique_ptr<sf::Character>> _characters;
    Game &_game;

    void prev_bg();
    void next_bg();

public:
    MainMenuModule(Game &game);
    ~MainMenuModule() override = default;
    void handle_frame_signal() override;
};