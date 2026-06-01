#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

struct specs
{
    int _x_speed_max;
    float _weight_factor; // jump height
    float _height_px;
    float _hp_factor;               // impact of opponent kicks
    float _stamina_recovery_factor; // factor of speed of gaining/losing of block energy
    float _hand_recovery_sec;       // factor of speed of recovery hand kick
    float _leg_recovery_sec;        // ffactor of speed of recovery leg kick
    int _hand_force;                // opponent hp percent by one kick
    int _leg_force;                 // opponent hp percent by one kick
};

struct textures
{
    sf::Texture &_walk_texture;
    std::vector<sf::IntRect> &_walk_texture_frames;
    sf::Texture &_hand_kick_texture;
    std::vector<sf::IntRect> &_hand_kick_texture_frames;
    sf::Texture &_jump_texture;
    std::vector<sf::IntRect> &_jump_texture_frames;
    sf::Texture &_leg_kick_texture;
    std::vector<sf::IntRect> &_leg_kick_texture_frames;
    sf::Texture &_block_texture;
    std::vector<sf::IntRect> &_block_texture_frames;
};

class Character
{

    std::string _name;
    sf::Texture _avatar;

protected:
    int _x_speed_max = 20;
    float _height_px = 100;
    float _weight_factor = 0.5;
    float _hp_factor = 1;
    float _stamina_recovery_factor = 1;
    float _hand_recovery_sec = 1.f;
    float _leg_recovery_sec = 1.5;
    int _hand_force = 5;
    int _leg_force = 10;
    sf::Texture _walk_texture;
    std::vector<sf::IntRect> _walk_texture_frames;
    sf::Texture _hand_kick_texture;
    std::vector<sf::IntRect> _hand_kick_texture_frames;
    sf::Texture _jump_texture;
    std::vector<sf::IntRect> _jump_texture_frames;
    sf::Texture _leg_kick_texture;
    std::vector<sf::IntRect> _leg_kick_texture_frames;
    sf::Texture _block_texture;
    std::vector<sf::IntRect> _block_texture_frames;

public:
    Character(std::string name,
              const sf::Texture &avatar,
              specs specs,
              const sf::Texture walk_texture = sf::Texture(),
              std::vector<sf::IntRect> walk_texture_frames = std::vector<sf::IntRect>(),
              sf::Texture _jump_texture = sf::Texture(),
              std::vector<sf::IntRect> _jump_texture_frames = std::vector<sf::IntRect>(),
              const sf::Texture hand_kick_texture = sf::Texture(),
              std::vector<sf::IntRect> hand_kick_texture_frames = std::vector<sf::IntRect>(),
              const sf::Texture leg_kick_texture = sf::Texture(),
              std::vector<sf::IntRect> leg_kick_texture_frames = std::vector<sf::IntRect>(),
              const sf::Texture block_texture = sf::Texture(),
              std::vector<sf::IntRect> block_texture_frames = std::vector<sf::IntRect>());
    Character();
    virtual ~Character() = default;

    const std::string &get_name() const
    {
        return _name;
    }

    const sf::Texture &get_avatarka() const { return _avatar; }

    void set_avatarka(sf::Texture &image)
    {
        _avatar = image;
    }

    specs get_specs()
    {
        return {_x_speed_max, _weight_factor, _height_px, _hp_factor, _stamina_recovery_factor, _hand_recovery_sec, _leg_recovery_sec, _hand_force, _leg_force};
    };
    textures get_textures()
    {
        return {_walk_texture, _walk_texture_frames, _hand_kick_texture, _hand_kick_texture_frames, _jump_texture, _jump_texture_frames, _leg_kick_texture, _leg_kick_texture_frames, _block_texture, _block_texture_frames};
    };
};