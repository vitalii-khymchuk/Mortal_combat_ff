#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Character
{
    std::string _name;
    sf::Texture _avatar;

public:
    Character(std::string name, sf::Texture avatar);

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