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
                                                _is_running_left(is_right_character)
{
    auto character_ptr = std::make_unique<CharacterFightSprite>(character.get_textures()._walk_texture, is_right_character);
    _active_sprite = character_ptr.get();
    _active_sprite_frames = &character.get_textures()._walk_texture_frames;
    _fight_module._game.shapes.emplace_back(std::move(character_ptr));

    _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
    _active_sprite->setTextureRect((*_active_sprite_frames)[0]);
    float scale_factor = character.get_specs()._size_scale;
    _active_sprite->setScale(sf::Vector2f(scale_factor, scale_factor));
    sf::FloatRect bounds = _active_sprite->getLocalBounds();
    _active_sprite->setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    if (is_right_character)
    {
        mirror_sprite(true);
    }
};

void Player::move_left()
{
    if (!_is_running_left)
    {
        mirror_sprite(true);
        _is_running_left = true;
    }
    _pos_x -= ((1.00f / GAME_FPS) * _character.get_specs()._x_speed_max);
    _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
    animate();
};
void Player::move_right()
{
    if (_is_running_left)
    {
        mirror_sprite(false);
        _is_running_left = false;
    }
    _pos_x += ((1.00f / GAME_FPS) * _character.get_specs()._x_speed_max);
    _active_sprite->setPosition(sf::Vector2f(_pos_x, _pos_y));
    animate();
};

void Player::jump() {};

void Player::animate()
{
    _active_sprite->setTextureRect((*_active_sprite_frames)[_current_frame_]);
    _animation_clock.start();
    sf::Time elapsed = _animation_clock.getElapsedTime();
    float frameTime = elapsed.asSeconds();
    if (frameTime >= (1.00f / ANIMATION_SPEED_FPS))
    {
        _current_frame_++;
        _animation_clock.restart();
    }
    if (_current_frame_ >= _active_sprite_frames->size())
    {
        _current_frame_ = 0;
    }
}

void Player::select_sprite(const sf::Texture &texture, const std::vector<sf::IntRect> &active_sprite_frames)
{
    _active_sprite->setTexture(texture);
    _active_sprite_frames = &active_sprite_frames;
};

void Player::handle_fps_signal()
{
    handle_falling();
}

void Player::reset_animation()
{
    _current_frame_ = 0;
    _active_sprite->setTextureRect((*_active_sprite_frames)[0]);
};

void Player::mirror_sprite(bool is_mirrored)
{
    float scale_factor = _character.get_specs()._size_scale;
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
            reset_animation();
        }
        return;
    }

    sf::Time elapsed = _gravity_clock.getElapsedTime();
    float fallingTime = elapsed.asSeconds();

    _y_speed += G_FORCE_PIXELS_PER_SEC_SQUARE * fallingTime;
    sf::Vector2f pos = _active_sprite->getPosition();
    _active_sprite->setPosition(sf::Vector2f(pos.x, pos.y + (1.00f / GAME_FPS) * _y_speed));
    _gravity_clock.restart();
}