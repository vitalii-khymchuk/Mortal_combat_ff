#include "characters.h"
#include <SFML/Graphics.hpp>

std::unique_ptr<std::vector<Character>> init_characters()

{
    auto characters = std::make_unique<std::vector<Character>>();

    sf::Texture avatar1;
    if (!avatar1.loadFromFile("screens/main_menu/assets/avatar1.png"))
    {
        throw std::runtime_error("Joko avatar load failed");
    }

    characters->emplace_back("Joko", std::move(avatar1));

    sf::Texture avatar2;
    if (!avatar2.loadFromFile("screens/main_menu/assets/avatar2.jpg"))
    {
        throw std::runtime_error("Jojo avatar load failed");
    }

    characters->emplace_back("Jojo", std::move(avatar2));

    sf::Texture avatar3;
    if (!avatar3.loadFromFile("screens/main_menu/assets/avatar3.png"))
    {
        throw std::runtime_error("Jola avatar load failed");
    }

    characters->emplace_back("Jola", std::move(avatar3));

    sf::Texture avatar4;
    if (!avatar4.loadFromFile("screens/main_menu/assets/avatar4.jpg"))
    {
        throw std::runtime_error("Joma avatar load failed");
    }

    characters->emplace_back("Joma", std::move(avatar4));

    sf::Texture avatar5;
    if (!avatar5.loadFromFile("screens/main_menu/assets/avatr5.jpg"))
    {
        throw std::runtime_error("Lana avatar load failed");
    }

    characters->emplace_back("Lana", std::move(avatar5));

    sf::Texture avatar6;
    if (!avatar6.loadFromFile("screens/main_menu/assets/avatar6.png"))
    {
        throw std::runtime_error("Nala avatar load failed");
    }

    characters->emplace_back("Nala", std::move(avatar6));
    return characters;
};