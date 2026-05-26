#include "characters.h"
#include <SFML/Graphics.hpp>

std::unique_ptr<std::vector<Character>> init_characters()

{
    auto characters = std::make_unique<std::vector<Character>>();
    characters->reserve(6);

    sf::Texture avatar1, walk_texture;
    if (!avatar1.loadFromFile("screens/main_menu/components/characters/joko/avatar1.png"))
    {
        throw std::runtime_error("Joko avatar load failed");
    }
    if (!walk_texture.loadFromFile("screens/main_menu/components/characters/joko/walk_animation.png"))
    {
        throw std::runtime_error("Joko walk animation load failed");
    }

    std::vector<sf::IntRect> walk_texture_frames;
    walk_texture_frames.push_back(sf::IntRect({0, 0}, {129, 180}));    // hero running frame 1
    walk_texture_frames.push_back(sf::IntRect({150, 0}, {152, 179}));  // hero running frame 2
    walk_texture_frames.push_back(sf::IntRect({351, 0}, {97, 186}));   // hero running frame 3
    walk_texture_frames.push_back(sf::IntRect({515, 0}, {123, 186}));  // hero running frame 4
    walk_texture_frames.push_back(sf::IntRect({690, 0}, {142, 186}));  // hero running frame 5
    walk_texture_frames.push_back(sf::IntRect({866, 0}, {148, 190}));  // hero running frame 6
    walk_texture_frames.push_back(sf::IntRect({1049, 0}, {97, 188}));  // hero running frame 7
    walk_texture_frames.push_back(sf::IntRect({1175, 0}, {142, 192})); // hero running frame 8
    walk_texture_frames.push_back(sf::IntRect({1345, 0}, {147, 194})); // hero running frame 9

    characters->emplace_back("Joko", avatar1, walk_texture, walk_texture_frames);

    sf::Texture avatar2;
    if (!avatar2.loadFromFile("screens/main_menu/components/characters/jojo/avatar2.jpg"))
    {
        throw std::runtime_error("Jojo avatar load failed");
    }

    characters->emplace_back("Jojo", std::move(avatar2));

    sf::Texture avatar3;
    if (!avatar3.loadFromFile("screens/main_menu/components/characters/jola/avatar3.png"))
    {
        throw std::runtime_error("Jola avatar load failed");
    }

    characters->emplace_back("Jola", std::move(avatar3));

    sf::Texture avatar4;
    if (!avatar4.loadFromFile("screens/main_menu/components/characters/joma/avatar4.jpg"))
    {
        throw std::runtime_error("Joma avatar load failed");
    }

    characters->emplace_back("Joma", std::move(avatar4));

    sf::Texture avatar5;
    if (!avatar5.loadFromFile("screens/main_menu/components/characters/lana/avatr5.jpg"))
    {
        throw std::runtime_error("Lana avatar load failed");
    }

    characters->emplace_back("Lana", std::move(avatar5));

    sf::Texture avatar6;
    if (!avatar6.loadFromFile("screens/main_menu/components/characters/nala/avatar6.png"))
    {
        throw std::runtime_error("Nala avatar load failed");
    }

    characters->emplace_back("Nala", std::move(avatar6));
    return characters;
};