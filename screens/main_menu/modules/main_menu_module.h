#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "modules/screen/screen.h"

class Screen;
class Game;

inline std::vector<std::string> bg_paths = {"screens/main_menu/assets/background1.png", "screens/main_menu/assets/background2.jpg"};

class MainMenuModule : public Screen
{
    std::vector<sf::Texture> _bg_textures;
    int _active_bg_index = 0;
    // std::vector<std::unique_ptr<sf::Character>> _characters;

    void prev_bg();
    void next_bg();

public:
    Game &_game;
    MainMenuModule(Game &game);
    ~MainMenuModule() override = default;
    void handle_frame_signal() override;
};