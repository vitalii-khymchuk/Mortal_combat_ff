#include "fight_module.h"
#include "modules/game/game.h"
#include "screens/fight/components/background/background.h"
#include "screens/fight/components/pause_text/pause_text.h"
#include <iostream>

FightModule::FightModule(Game &game)
    : Screen(),
      _game(game),
      player_A(*this, game.selected_character_A, 150, 200, false),
      player_B(*this, game.selected_character_B, 650, 200, true)
{
    init_background(this);
}

void FightModule::handle_event(const sf::Event &event)
{
    // controls while game on pause
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape) && event.getIf<sf::Event::KeyPressed>())
    {
        if (_is_pause)
        {
            end_fight(true);
        }
        else
        {
            pause_fight();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Enter) && event.getIf<sf::Event::KeyPressed>())
    {
        continue_fight();
    }

    if (_is_pause)
    {
        return;
    }

    // reset sprite frame to initial when key is released
    if (const auto *keyReleased = event.getIf<sf::Event::KeyReleased>())
    {
        auto keycode = keyReleased->scancode;
        if (keycode == sf::Keyboard::Scancode::A ||
            keycode == sf::Keyboard::Scancode::D)
        {
            player_A.reset_animation();
        }

        if (keycode == sf::Keyboard::Scancode::S)
        {
            player_A.reset_animation();
            player_A.stop_block();
        }

        if (keycode == sf::Keyboard::Scancode::Left ||
            keycode == sf::Keyboard::Scancode::Right)
        {
            player_B.reset_animation();
        }

        if (keycode == sf::Keyboard::Scancode::Down)
        {
            player_B.reset_animation();
            player_B.stop_block();
        }
    }

    // controls while fight
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
        player_A.block_kick();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) && event.getIf<sf::Event::KeyPressed>())
    {
        player_A.move_right();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R) && event.getIf<sf::Event::KeyPressed>())
    {
        player_A.hand_kick();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::T) && event.getIf<sf::Event::KeyPressed>())
    {
        player_A.leg_kick();
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
        player_B.block_kick();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) && event.getIf<sf::Event::KeyPressed>())
    {
        player_B.move_right();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Comma) && event.getIf<sf::Event::KeyPressed>())
    {
        player_B.hand_kick();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Period) && event.getIf<sf::Event::KeyPressed>())
    {
        player_B.leg_kick();
    }
}

// count and upd fight timer
void FightModule::tick_time()
{
    static sf::Clock sec_clock;
    if (!sec_clock.isRunning())
    {
        sec_clock.start();
    }

    sf::Time elapsed = sec_clock.getElapsedTime();
    float time = elapsed.asSeconds();

    if (time >= 1)
    {
        sec_clock.restart();
        if (!_is_pause)
        {
            _timer_sec--;
            // upd statusbar
        }
    }

    if (_timer_sec <= 0)
    {
        // out of time msg
        end_fight(false);
        _timer_sec = MATCH_DURATION_SEC;
    }

    // std::cout << "TIMER: " << _timer_sec << std::endl;
}

// end fight, _force_end = true return to main menu, _force_end = false, init new round
void FightModule::end_fight(bool _force_end)
{
    if (_force_end)
    {
        _game.set_current_screen(CURRENT_SCREEN::MAIN_MENU);
        return;
    }

    player_A.reset_player();
    player_B.reset_player();
};

void FightModule::pause_fight()
{
    _is_pause = true;
    init_pause_text(_game);
};

void FightModule::continue_fight()
{
    _is_pause = false;
    remove_pause_texts(_game);
};

void FightModule::track_hp()
{
    if (_player_a_wins == 2)
    {
        pause_fight();
        // win msg
        end_fight(true);
        return;
    }

    if (_player_b_wins == 2)
    {
        pause_fight();
        // win msg
        end_fight(true);
        return;
    }

    if (player_A._hp_percents <= 0)
    {
        _player_b_wins++;
        // win msg
        end_fight(false);
    }

    if (player_B._hp_percents <= 0)
    {
        _player_a_wins++;
        // win msg
        end_fight(false);
    }
};

void FightModule::handle_frame_signal()
{
    // disable clock signal for characters while pause
    if (_is_pause)
    {
        return;
    }
    player_A.handle_fps_signal();
    player_B.handle_fps_signal();
    tick_time();
    track_hp();
}