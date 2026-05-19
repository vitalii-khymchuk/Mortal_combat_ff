#include "characters.h"
#include <SFML/Graphics.hpp>

std::unique_ptr<std::vector<Character>> init_characters()
{
    auto characters = std::make_unique<std::vector<Character>>();

    sf::Texture sub_zero_avatar;
    if (!sub_zero_avatar.loadFromFile("screens/main_menu/components/characters/sub_zero/wallpaper.jpg"))
    {
        throw std::runtime_error("sub_zero_avatar load failed");
    }

    characters->emplace_back("Subzero", std::move(sub_zero_avatar));
    return characters;
};