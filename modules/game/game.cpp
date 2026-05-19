#include "game.h"
#include "screens/main_menu/main_menu.h"
#include "modules/screen/screen.h"

Game::Game(sf::RenderWindow *window)
{
    // init main menu
    _window = window;
    set_current_screen(CURRENT_SCREEN::MAIN_MENU);
    // _game_status = GAME_STATUS::NOT_INITIALIZED;
};

Game::~Game() = default;

void Game::set_current_screen(const CURRENT_SCREEN &new_screen)
{
    if (_current_screen == new_screen && _current_screen_ptr)
        return;

    _current_screen = new_screen;
    if (new_screen == CURRENT_SCREEN::MAIN_MENU)
    {
        // init main menu
        // set frameTrigPtr
        _current_screen_ptr.reset();
        shapes.clear();
        _current_screen_ptr = std::move(init_main_menu(*this));
    }

    if (new_screen == CURRENT_SCREEN::MATCH)
    {
        // init main match
        // set frameTrigPtr
    }
}

void Game::trig_fps_signal()
{
    if (_current_screen_ptr)
        _current_screen_ptr->handle_frame_signal();
}