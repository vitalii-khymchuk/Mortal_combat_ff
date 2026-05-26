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

    auto bounds = _active_sprite->getGlobalBounds().size;
    std::cout << "Size: " << bounds.x << " x " << bounds.y << std::endl;

    auto texture = character.get_textures()._walk_texture.getSize();
    std::cout << "Texture size: " << texture.x << " x " << texture.y << std::endl;
};

void Player::move_left()
{
    _is_running_left = true;
    // if (_active_sprite_frames != _walk_texture_frames)
    // {
    //     select_sprite(_walk_texture, _walk_texture_frames);
    // }

    // std::cout << " press left" << std::endl;
};
void Player::move_right()
{
    _is_running_left = false;
    // if (_active_sprite_frames != _walk_texture_frames)
    // {
    //     select_sprite(_walk_texture, _walk_texture_frames);
    // }
    // std::cout << " press right" << std::endl;
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
    animate();
}