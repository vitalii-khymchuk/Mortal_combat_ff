#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

struct specs
{
    int _x_speed_max;
    float _weight_factor;
};

struct sprites
{
    sf::Texture &_walk_texture;
    std::vector<sf::IntRect> &_walk_texture_frames;
    sf::Texture &_hand_kick_texture;
    std::vector<sf::IntRect> &_hand_kick_texture_frames;
};

class Character
{

    std::string _name;
    sf::Texture _avatar;

protected:
    int _x_speed_max = 20;
    float _weight_factor = 0.5;
    sf::Texture _walk_texture;
    std::vector<sf::IntRect> _walk_texture_frames;
    sf::Texture _hand_kick_texture;
    std::vector<sf::IntRect> _hand_kick_texture_frames;

public:
    Character(std::string name,
              const sf::Texture &avatar,
              const sf::Texture walk_texture = sf::Texture(),
              std::vector<sf::IntRect> walk_texture_frames = std::vector<sf::IntRect>(),
              const sf::Texture hand_kick_texture = sf::Texture(),
              std::vector<sf::IntRect> hand_kick_texture_frames = std::vector<sf::IntRect>());
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
        return {_x_speed_max, _weight_factor};
    };
    sprites get_textures()
    {

        return {_walk_texture, _walk_texture_frames, _hand_kick_texture, _hand_kick_texture_frames};
    };
};