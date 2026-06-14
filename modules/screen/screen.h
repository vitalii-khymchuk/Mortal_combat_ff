#include <SFML/Graphics.hpp>
#include "modules/game/game.h"
class Screen
{
public:
    Screen(Game &game) : _game(game) {};
    Game &_game;
    virtual ~Screen() = default;
    virtual void handle_frame_signal() {};
    virtual void handle_event(const sf::Event &event) {};
};