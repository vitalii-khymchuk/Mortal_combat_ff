#include "fight_module.h"
#include "modules/game/game.h"
#include "screens/fight/components/background/background.h"
#include "screens/fight/components/pause_text/pause_text.h"
#include "screens/fight/components/health_bar/health_bar.h"
// #include "screens/fight/modules/battle_message/battle_message.h"
#include <iostream>

FightModule::FightModule(Game &game)
    : Screen(game),
      player_A(*this, game.selected_character_A, 150, 200, false),
      player_B(*this, game.selected_character_B, 650, 200, true),
      battle_message(this)
{
    init_background(this);
    init_health_bars(this);
    sounds.play_bg_music();
    sounds.play_round_sound(1);
    battle_message.show_custom("ROUND 1", sf::Color::White, 60);
    auto timer_2 = timers.add_timer(2, [this]()
                                    { battle_message.hide(); }, true);
    auto timer_1 = timers.add_timer(2, [this, timer_2]()
                                    { battle_message.show_custom("FIGHT", sf::Color::White, 100);
        timers.start(timer_2); }, true);

    timers.start(timer_1);
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
        // battle_message.hide();
        // battle_message.show_custom("Player A has jumped!", sf::Color::Magenta, 60);
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
            _fight_timer_sec--;
            // upd statusbar
        }
    }

    if (_fight_timer_sec <= 0)
    {
        // out of time msg
        end_fight(false);
        _fight_timer_sec = MATCH_DURATION_SEC;
    }

    // std::cout << "TIMER: " << _fight_timer_sec << std::endl;
}

void FightModule::prepare_next_fight()
{
    int new_round = _player_a_wins + _player_b_wins + 1;
    player_A.reset_player();
    player_B.reset_player();
    sounds.play_round_sound(new_round);
    _fight_timer_sec = MATCH_DURATION_SEC;
    _is_pause = false;

    battle_message.show_custom(("ROUND " + std::to_string(new_round)), sf::Color::White, 60);

    auto timer_2 = timers.add_timer(2, [this]()
                                    { battle_message.hide(); }, true);
    auto timer_1 = timers.add_timer(2, [this, timer_2]()
                                    { battle_message.show_custom("FIGHT", sf::Color::White, 100);
        timers.start(timer_2); }, true);

    timers.start(timer_1);
};

// end fight, _force_end = true return to main menu, _force_end = false, init new round
void FightModule::end_fight(bool _force_end)
{
    if (_force_end)
    {
        _game.set_current_screen(CURRENT_SCREEN::MAIN_MENU);
        return;
    }

    prepare_next_fight();
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
    static bool finish_him_played = false;

    if (player_A._hp_percents <= 0)
    {
        static int timer_id = timers.add_timer(3, [this]()
                                               {
                                                   finish_him_played = false;

                                                   if (_player_b_wins == 2)
                                                   {
                                                       battle_message.hide();
                                                       _is_pause = true;
                                                       end_fight(true);
                                                   }
                                                   else
                                                   {
                                                       end_fight(false);
                                                   } });
        if (timers.is_running(timer_id))
        {
            return;
        }

        // win msg
        timers.start(timer_id);
        _player_b_wins++;
        if (_player_b_wins == 2)
        {
            battle_message.show_custom(player_B.get_character_name() + " WON", sf::Color::White, 60);
        };
    }

    if (player_B._hp_percents <= 0)
    {
        static int timer_id = timers.add_timer(3, [this]()
                                               {
                               finish_him_played = false;

                               if (_player_a_wins == 2)
                               {
                                   battle_message.hide();
                                   _is_pause = true;
                                   end_fight(true);
                               }
                               else
                               {
                                   end_fight(false);
                               } });
        if (timers.is_running(timer_id))
        {
            return;
        }

        // win msg
        timers.start(timer_id);
        _player_a_wins++;
        if (_player_a_wins == 2)
        {
            battle_message.show_custom(player_B.get_character_name() + " WON", sf::Color::White, 60);
        };
    }

    if (!finish_him_played && (player_A._hp_percents <= 20 || player_B._hp_percents <= 20))
    {
        finish_him_played = true;
        sounds.play_finish_him_sound();

        battle_message.show_custom("FINISH HIM", sf::Color::White, 60);
        auto timer_1 = timers.add_timer(2, [this]()
                                        { battle_message.hide(); }, true);
        timers.start(timer_1);
    }
};

void FightModule::handle_frame_signal()
{
    // disable clock signal for characters while pause
    if (_is_pause || _game.get_current_screen() != CURRENT_SCREEN::MATCH)
    {
        return;
    }

    player_A.handle_fps_signal();
    player_B.handle_fps_signal();
    tick_time();
    update_health_bars(this);

    // SHOULD BE CALLED LAST
    track_hp();
    timers.tick();
}