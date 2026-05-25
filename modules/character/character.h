#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Character
{
    std::string _name;
    sf::Texture _avatar;

protected:
    int _x_speed_max = 20;
    float _weight_factor = 0.5;
    //_walk_sprite
    //_hand_kick_sprite

public:
    Character(std::string name, sf::Texture avatar);
    Character();
    virtual ~Character() = default;

    std::string get_name()
    {
        return _name;
    }

    // sf::Texture get_avatarka()
    // {
    //     return _avatar;
    // }

    const sf::Texture &get_avatarka() const { return _avatar; }
};