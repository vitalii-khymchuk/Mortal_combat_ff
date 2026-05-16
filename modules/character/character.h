#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Background
{
    std::string path_;
    sf::Texture bg_texture;

public:
    Background(std::string path) : path_(path) {};
};