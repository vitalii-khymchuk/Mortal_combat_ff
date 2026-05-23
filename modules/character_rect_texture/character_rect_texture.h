#pragma once
#include <SFML/Graphics.hpp>

class CharacterRectTexture : public sf::RectangleShape
{
public:
    bool is_character_b;
    int element_index;

    CharacterRectTexture(sf::Vector2f parent_arg, int index, bool isCharacterB = false) : sf::RectangleShape(parent_arg), element_index(index), is_character_b(isCharacterB)
    {
    }

    ~CharacterRectTexture() = default;
};
// text
class CharacterNameText : public sf::Text
{
public:
    bool is_character_b;

    CharacterNameText(const sf::Font &font, sf::String string = "", unsigned int characterSize = 30, bool isCharacterB = false) : sf::Text(font, string, characterSize), is_character_b(isCharacterB)
    {
    }

    ~CharacterNameText() = default;
};