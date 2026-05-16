#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
class Screen;

enum class CURRENT_SCREEN
{
    MAIN_MENU,
    MATCH
};

enum class GAME_STATUS
{
    NOT_INITIALIZED,
    PAUSE,
    PLAY
};

class Game
{
    CURRENT_SCREEN _current_screen;
    std::unique_ptr<Screen> _current_screen_ptr;
    // static GAME_STATUS game_status_;

public:
    Game(sf::RenderWindow *window);
    virtual ~Game();
    CURRENT_SCREEN get_current_screen() { return _current_screen; };
    //  GAME_STATUS get_game_status() { return _game_status; };

    void set_current_screen(const CURRENT_SCREEN &new_screen);
    void set_selected_bg(const sf::Texture &bg) { selected_bg = bg; };

    void trig_fps_signal();

    std::vector<std::unique_ptr<sf::Drawable>> shapes;
    sf::RenderWindow *_window;
    sf::Texture selected_bg;
    // selected_character_A
    // selected_character_B
};