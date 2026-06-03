#include "player.h"
#include "fight_module.h"
#include "modules/constants/constants.h"
#include "modules/game/game.h"
#include "iostream"

Player::Player(FightModule &fight_module,
               Character &character,
               const int &init_pos_x,
               const int &init_pos_y,
               const bool is_right_character) : _fight_module(fight_module),
                                                _character(character),
                                                _pos_x(init_pos_x),
                                                _pos_y(init_pos_y),
                                                _is_running_left(is_right_character),
                                                _is_player_B(is_right_character)
{
    auto character_ptr = std::make_unique<CharacterFightSprite>(character.get_textures()._walk_texture, is_right_character);
    _active_sprite = character_ptr.get();
    _active_sprite_frames = &character.get_textures()._walk_texture_frames;
    _fight_module._game.shapes.emplace_back(std::move(character_ptr));

    _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
    _active_sprite->setTextureRect((*_active_sprite_frames)[0]);
    sf::FloatRect bounds = _active_sprite->getLocalBounds();
    _active_sprite->setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y));

    // int sprite_height = _active_sprite->getGlobalBounds().size.y;
    float scale_factor = character.get_specs()._height_px / bounds.size.y;
    _active_sprite->setScale(sf::Vector2f(scale_factor, scale_factor));

    if (is_right_character)
    {
        mirror_sprite(true);
    }
};

void Player::move_left()
{
    if (_is_blocking)
        return;

    if (!_is_running_left)
    {
        mirror_sprite(true);
        _is_running_left = true;
    }
    textures c_textures = _character.get_textures();
    if (&c_textures._walk_texture_frames != _active_sprite_frames)
    {
        reset_animation();
    }
    animate();
    check_edges();
    if (_can_move_left)
    {
        _pos_x -= ((1.00f / GAME_FPS) * _character.get_specs()._x_speed_max);
        _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
    }
};
void Player::move_right()
{
    if (_is_blocking)
        return;

    if (_is_running_left)
    {
        mirror_sprite(false);
        _is_running_left = false;
    }
    textures c_textures = _character.get_textures();
    if (&c_textures._walk_texture_frames != _active_sprite_frames)
    {
        reset_animation();
    }
    animate();
    check_edges();
    if (_can_move_right)
    {
        _pos_x += ((1.00f / GAME_FPS) * _character.get_specs()._x_speed_max);
        _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
    }
};

void Player::jump()
{
    if (_is_blocking)
        return;

    if (!_is_falling)
    {
        textures c_textures = _character.get_textures();
        specs c_specs = _character.get_specs();
        select_sprite(c_textures._jump_texture, c_textures._jump_texture_frames);
        _y_speed = -400 * c_specs._weight_factor;
        _is_falling = true;
        _animation_loop_playing = true;
    }
};

void Player::hand_kick()
{
    if (!can_attack(false))
        return;

    textures c_textures = _character.get_textures();
    specs c_specs = _character.get_specs();
    select_sprite(c_textures._hand_kick_texture, c_textures._hand_kick_texture_frames);
    _animation_loop_playing = true;
    // implement hp mechanic
    apply_attack_to_opponent(c_specs._hand_force, c_specs._hand_force);
    start_attack_cooldown(c_specs._hand_recovery_sec, false);
};

void Player::leg_kick()
{
    if (!can_attack(true))
        return;

    textures c_textures = _character.get_textures();
    specs c_specs = _character.get_specs();
    select_sprite(c_textures._leg_kick_texture, c_textures._leg_kick_texture_frames);
    _animation_loop_playing = true;
    // implement hp mechanic
    apply_attack_to_opponent(c_specs._leg_force, c_specs._leg_force);
    start_attack_cooldown(c_specs._leg_recovery_sec, true);
};

void Player::block_kick()
{
    if (_block_energy <= 0.f)
        return;

    _is_blocking = true;

    textures c_textures = _character.get_textures();
    if (&c_textures._block_texture_frames != _active_sprite_frames)
    {
        select_sprite(c_textures._block_texture, c_textures._block_texture_frames);
    }

    _animation_loop_playing = true;
};

void Player::check_ground()
{
    const Player &opponent = _is_player_B ? _fight_module.player_A : _fight_module.player_B;
    if (_y_speed < 0 || !_active_sprite || !opponent._active_sprite)
        return;

    auto bounds = _active_sprite->getGlobalBounds().size;
    auto bounds_opponent = opponent._active_sprite->getGlobalBounds().size;

    bool has_contact = is_in_contact_with_opponent(_pos_x, _pos_y, false);

    float top = _pos_y;
    float bottom = _pos_y + bounds.y;
    float opp_top = opponent._pos_y;

    bool is_standing_on_opponent =
        has_contact &&
        bottom >= opp_top &&
        bottom <= opp_top + INTERACTION_DISTANCE_PX &&
        top < opp_top;

    _is_falling = !(is_standing_on_opponent || _pos_y >= GROUND_Y_LEVEL);
    // adj ground level
    if (!_is_falling && !is_standing_on_opponent)
    {
        _pos_y = GROUND_Y_LEVEL;
    }
}

void Player::animate()
{
    _animation_clock.start();
    sf::Time elapsed = _animation_clock.getElapsedTime();
    float frameTime = elapsed.asSeconds();

    if (frameTime >= (1.00f / ANIMATION_SPEED_FPS))
    {
        _current_frame_++;

        if (_current_frame_ >= _active_sprite_frames->size())
        {
            _current_frame_ = 0;
        }

        _active_sprite->setTextureRect((*_active_sprite_frames)[_current_frame_]);
        _animation_clock.restart();
    }
}
void Player::select_sprite(const sf::Texture &texture, const std::vector<sf::IntRect> &active_sprite_frames)
{
    bool was_texture_updated = false;
    if (&active_sprite_frames != _active_sprite_frames)
    {
        _active_sprite->setTexture(texture);
        _active_sprite_frames = &active_sprite_frames;
        was_texture_updated = true;
    }

    _animation_loop_playing = false;
    _current_frame_ = 0;
    _active_sprite->setTextureRect((*_active_sprite_frames)[0]);
    _animation_clock.restart();

    sf::FloatRect bounds = _active_sprite->getLocalBounds();
    _active_sprite->setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y));

    if (was_texture_updated)
    {
        float sprite_height = bounds.size.y;
        float scale_factor = _character.get_specs()._height_px / sprite_height;

        float sign_x = (_active_sprite->getScale().x < 0.f) ? -1.f : 1.f;
        _active_sprite->setScale(sf::Vector2f(sign_x * scale_factor, scale_factor));
    }

    _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
}

void Player::reset_animation()
{
    textures c_textures = _character.get_textures();
    select_sprite(c_textures._walk_texture, c_textures._walk_texture_frames);
};

void Player::handle_fps_signal()
{
    check_ground();
    handle_falling();
    update_block_state();

    // automation for loop animation
    if (_animation_loop_playing)
    {
        int last_frame = _active_sprite_frames->size() - 1;

        if (_current_frame_ < last_frame)
        {
            animate();
        }
        else
        {
            _animation_loop_playing = false;
        }
    }
}

void Player::mirror_sprite(bool is_mirrored)
{
    float scale_factor = _active_sprite->getScale().y;
    if (is_mirrored)

        _active_sprite->setScale(sf::Vector2f(-scale_factor, scale_factor));
    else
        _active_sprite->setScale(sf::Vector2f(scale_factor, scale_factor));
}

void Player::handle_falling()
{

    if (!_is_falling)
    {
        if (_y_speed != 0)
        {
            _gravity_clock.stop();
            _gravity_clock.reset();
            _y_speed = 0;
            // reset_animation();
            textures c_textures = _character.get_textures();
            select_sprite(c_textures._walk_texture, c_textures._walk_texture_frames);
        }
        return;
    }

    sf::Time elapsed = _gravity_clock.getElapsedTime();
    float fallingTime = elapsed.asSeconds();

    _y_speed += G_FORCE_PIXELS_PER_SEC_SQUARE * fallingTime;
    _pos_y = _pos_y + (1.00f / GAME_FPS) * _y_speed;
    _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
    _gravity_clock.restart();
}

void Player::check_edges()
{
    if (!_active_sprite)
        return;

    // reset before check
    if (!_can_move_left)
        _can_move_left = true;

    if (!_can_move_right)
        _can_move_right = true;

    float x_step = _character.get_specs()._x_speed_max * (1.0f / GAME_FPS);
    float window_width = _fight_module._game._window->getSize().x;

    auto my_size = _active_sprite->getGlobalBounds().size;

    int next_left_x = _pos_x - x_step;
    int next_right_x = _pos_x + x_step;

    float next_left_edge = next_left_x - my_size.x / 2.f + INTERACTION_DISTANCE_PX;
    float next_right_edge = next_right_x + my_size.x / 2.f - INTERACTION_DISTANCE_PX;

    if (next_left_edge < 0.f)
        _can_move_left = false;

    if (next_right_edge > window_width)
        _can_move_right = false;

    if (_can_move_left && is_in_contact_with_opponent(next_left_x, _pos_y, true))
        _can_move_left = false;

    if (_can_move_right && is_in_contact_with_opponent(next_right_x, _pos_y, true))
        _can_move_right = false;
}

bool Player::is_in_contact_with_opponent(int test_pos_x, int test_pos_y, bool unlock_x_on_opponent) const
{
    if (!_active_sprite)
        return false;

    const Player &opponent = _is_player_B ? _fight_module.player_A : _fight_module.player_B;

    if (!opponent._active_sprite)
        return false;

    auto my_size = _active_sprite->getGlobalBounds().size;
    auto opp_size = opponent._active_sprite->getGlobalBounds().size;

    float my_left = test_pos_x - my_size.x / 2.f + INTERACTION_DISTANCE_PX * 2;
    float my_right = test_pos_x + my_size.x / 2.f - INTERACTION_DISTANCE_PX * 2;
    float my_top = test_pos_y;
    float my_bottom = test_pos_y + my_size.y;

    float opp_left = opponent._pos_x - opp_size.x / 2.f + INTERACTION_DISTANCE_PX;
    float opp_right = opponent._pos_x + opp_size.x / 2.f - INTERACTION_DISTANCE_PX;
    float opp_top = opponent._pos_y;
    float opp_bottom = opponent._pos_y + opp_size.y;

    bool overlap_x = my_right >= opp_left && my_left <= opp_right;
    bool overlap_y = my_bottom >= opp_top && my_top <= opp_bottom;
    bool is_on_opponent = (opp_top - my_top) >= (opp_size.y / 2.0f);

    return overlap_x && overlap_y && (unlock_x_on_opponent ? !is_on_opponent : true);
}

bool Player::can_attack(bool is_leg_attack) const
{
    specs c_specs = _character.get_specs();
    if (is_leg_attack)
    {
        return _leg_attack_cooldown_clock.getElapsedTime().asSeconds() >= c_specs._leg_recovery_sec && !_is_blocking;
    }
    else
    {
        return _hand_attack_cooldown_clock.getElapsedTime().asSeconds() >= c_specs._hand_recovery_sec && !_is_blocking;
    }
}

void Player::start_attack_cooldown(float seconds, bool is_leg_attack)
{
    if (is_leg_attack)
    {
        _leg_attack_cooldown_clock.restart();
    }
    else
    {
        _hand_attack_cooldown_clock.restart();
    }
}

void Player::apply_attack_to_opponent(int damage, int block_damage)
{
    Player &opponent = _is_player_B ? _fight_module.player_A : _fight_module.player_B;

    auto my_size = _active_sprite->getGlobalBounds().size;
    float left_edge = _pos_x - my_size.x / 2.f + INTERACTION_DISTANCE_PX;
    float right_edge = _pos_x + my_size.x / 2.f - INTERACTION_DISTANCE_PX;

    if (!is_in_contact_with_opponent(left_edge, _pos_y, true) && !is_in_contact_with_opponent(right_edge, _pos_y, true))
    {
        return;
    }

    specs opponent_specs = opponent._character.get_specs();

    if (opponent._is_blocking && opponent._block_energy > 0.f)
    {
        opponent._block_energy -= block_damage * opponent_specs._hp_factor;

        if (opponent._block_energy < 0.f)
            opponent._block_energy = 0.f;

        if (opponent._block_energy == 0.f)
        {
            opponent._is_blocking = false;
            opponent.reset_animation();
        }
    }
    else
    {
        opponent._hp_percents -= damage * opponent_specs._hp_factor;

        if (opponent._hp_percents < 0)
            opponent._hp_percents = 0;
    }
}

void Player::update_block_state()
{
    specs c_specs = _character.get_specs();
    float dt = 1.0f * c_specs._stamina_recovery_factor / GAME_FPS;

    if (_is_blocking)
    {
        _block_energy -= 25.f * dt;

        if (_block_energy <= 0.f)
        {
            _block_energy = 0.f;
            _is_blocking = false;
            reset_animation();
        }
    }
    else
    {
        _block_energy += 12.f * dt;

        if (_block_energy > _block_energy_max)
            _block_energy = _block_energy_max;
    }
}

void Player::stop_block()
{
    if (_is_blocking)
    {
        _is_blocking = false;
        reset_animation();
    }
}

void Player::reset_player()
{
    _hp_percents = 100;
    _block_energy = 100;

    if (_is_player_B)
    {
        _pos_x = 650;
        _pos_y = 200;
    }
    else
    {
        _pos_x = 150;
        _pos_y = 200;
    }
};