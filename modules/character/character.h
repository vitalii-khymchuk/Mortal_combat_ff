#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Character
{
    std::string _name;
    sf::Texture _avatar;

    Character(std::string name, sf::Texture avatar) {};
};