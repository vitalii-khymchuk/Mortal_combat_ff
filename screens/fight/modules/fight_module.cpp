#include "fight_module.h"
#include "modules/game/game.h"
#include "screens/fight/components/background/background.h"
#include <iostream>

FightModule::FightModule(Game &game)
    : Screen(),
      _game(game),
      player_A(*this, game.selected_character_A, 150, 100, false),
      player_B(*this, game.selected_character_B, 650, 100, true)
{
    init_background(this);
}

void FightModule::handle_event(const sf::Event &event)
{
    if (const auto *keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            _game._window->close();
        }
    }

    if (const auto *keyReleased = event.getIf<sf::Event::KeyReleased>())
    {
        auto keycode = keyReleased->scancode;
        if (keycode == sf::Keyboard::Scancode::A ||
            keycode == sf::Keyboard::Scancode::S ||
            keycode == sf::Keyboard::Scancode::D)
        {
            player_A.reset_animation();
        }

        if (keycode == sf::Keyboard::Scancode::Left ||
            keycode == sf::Keyboard::Scancode::Down ||
            keycode == sf::Keyboard::Scancode::Right)
        {
            player_B.reset_animation();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) && event.getIf<sf::Event::KeyPressed>())
    {
        player_A.jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) && event.getIf<sf::Event::KeyPressed>())
    {
        player_A.move_left();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) && event.getIf<sf::Event::KeyPressed>())
    {
        // player_A->duck();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) && event.getIf<sf::Event::KeyPressed>())
    {
        player_A.move_right();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R) && event.getIf<sf::Event::KeyPressed>())
    {
        player_A.hand_kick();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && event.getIf<sf::Event::KeyPressed>())
    {
        player_B.jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left) && event.getIf<sf::Event::KeyPressed>())
    {
        player_B.move_left();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) && event.getIf<sf::Event::KeyPressed>())
    {
        // player_B->duck();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) && event.getIf<sf::Event::KeyPressed>())
    {
        player_B.move_right();
    }
}

void FightModule::handle_frame_signal()
{
    player_A.handle_fps_signal();
    player_B.handle_fps_signal();
}