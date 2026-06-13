#include "fight_module.h"
#include "modules/game/game.h"
#include "screens/fight/components/background/background.h"
#include "screens/fight/components/pause_text/pause_text.h"
#include "screens/fight/components/health_bar/health_bar.h"
#include "screens/fight/modules/battle_message/battle_message.h"
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
        // show_custom(text_str, text_color, font_size);
        battle_message.show_custom("FIGHT WAS RENEWED!", sf::Color::Blue, 50);
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
        battle_message.hide();
        battle_message.show_custom("Player A has jumped!", sf::Color::Magenta, 60);
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
    if (!_sec_clock.isRunning())
    {
        _sec_clock.start();
    }

    sf::Time elapsed = _sec_clock.getElapsedTime();
    float time = elapsed.asSeconds();

    if (time >= 1)
    {
        _sec_clock.restart();
        if (!_is_pause)
        {
            _fight_timer_sec--;
        }
    }

    if (_fight_timer_sec <= 0)
    {
        end_fight(false);
        _fight_timer_sec = MATCH_DURATION_SEC;
    }

    // std::cout << "TIMER: " << _fight_timer_sec << std::endl;
}

// end fight, _force_end = true return to main menu, _force_end = false, init new round
void FightModule::end_fight(bool force_end)
{
    if (force_end)
    {
        // Не вызываем set_current_screen прямо здесь — это может быть вызвано
        // из callback таймера, внутри timers.tick(), что приведёт к краша
        // (уничтожение FightModule во время итерации по timers).
        // Ставим флаг — переход произойдёт в начале следующего кадра.
        _go_to_menu = true;
        return;
    }

    _fight_timer_sec = MATCH_DURATION_SEC;
    player_A.reset_player();
    player_B.reset_player();
    sounds.play_round_sound(_player_a_wins + _player_b_wins + 1);
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
    // Кто набрал 2 победы — матч окончен, возврат в меню
    if (_player_a_wins == 2 || _player_b_wins == 2)
    {
        // pause_fight();
        end_fight(true);
        return;
    }

    // HP игрока A упало до 0 — побеждает B
    if (player_A._hp_percents <= 0)
    {
        // Создаём таймер только один раз за раунд
        if (_timer_id_a == -1)
        {
            _timer_id_a = timers.add_timer(3, [this]()
                                           {
                _player_b_wins++;
                _timer_id_a = -1;
                _finish_him_played = false;
                end_fight(false); });
            timers.start(_timer_id_a);
        }
        return;
    }

    // HP игрока B упало до 0 — побеждает A
    if (player_B._hp_percents <= 0)
    {
        if (_timer_id_b == -1)
        {
            _timer_id_b = timers.add_timer(3, [this]()
                                           {
                _player_a_wins++;
                _timer_id_b = -1;
                _finish_him_played = false;
                end_fight(false); });
            timers.start(_timer_id_b);
        }
        return;
    }

    // "Finish him" звук при низком HP
    if (!_finish_him_played && (player_A._hp_percents <= 20 || player_B._hp_percents <= 20))
    {
        _finish_him_played = true;
        sounds.play_finish_him_sound();
    }
};

void FightModule::handle_frame_signal()
{
    // Безопасный переход в меню — после того как предыдущий кадр полностью завершён
    if (_go_to_menu)
    {
        _game.set_current_screen(CURRENT_SCREEN::MAIN_MENU);
        return; // FightModule уже уничтожен, дальше ничего не делаем
    }

    if (_is_pause)
        return;

    player_A.handle_fps_signal();
    player_B.handle_fps_signal();
    tick_time();
    track_hp();
    timers.tick();
    update_health_bars(this);
}