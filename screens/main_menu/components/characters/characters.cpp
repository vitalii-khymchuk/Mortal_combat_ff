#include "characters.h"
#include <SFML/Graphics.hpp>

std::unique_ptr<std::vector<Character>> init_characters()

{
    auto characters = std::make_unique<std::vector<Character>>();
    characters->reserve(6);

    sf::Texture avatar1, walk_texture, jump_texture, hand_kick_texture, leg_kick_texture, block_texture;
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

    if (!jump_texture.loadFromFile("screens/main_menu/components/characters/joko/jump_animation.png"))
    {
        throw std::runtime_error("Joko jump animation load failed");
    }

    std::vector<sf::IntRect> jump_texture_frames;
    jump_texture_frames.push_back(sf::IntRect({13, 76}, {172, 240}));   // hero frame 1 right_x = 208
    jump_texture_frames.push_back(sf::IntRect({249, 75}, {180, 239}));  // hero frame 2 right_x = 412
    jump_texture_frames.push_back(sf::IntRect({482, 20}, {190, 294}));  // hero frame 3 right_x = 708
    jump_texture_frames.push_back(sf::IntRect({700, 14}, {200, 299}));  // hero frame 4 right_x = 942
    jump_texture_frames.push_back(sf::IntRect({945, 55}, {195, 259}));  // hero frame 5 right_x = 1162
    jump_texture_frames.push_back(sf::IntRect({1179, 70}, {219, 243})); // hero frame 6 right_x = 1405

    if (!hand_kick_texture.loadFromFile("screens/main_menu/components/characters/joko/hand_kick_animation.png"))
    {
        throw std::runtime_error("Joko hand kick animation load failed");
    }

    std::vector<sf::IntRect> hand_kick_texture_frames;
    hand_kick_texture_frames.push_back(sf::IntRect({1, 0}, {219, 335}));    // hero frame 1
    hand_kick_texture_frames.push_back(sf::IntRect({268, 0}, {207, 331}));  // hero frame 2
    hand_kick_texture_frames.push_back(sf::IntRect({589, 0}, {275, 331}));  // hero frame 3
    hand_kick_texture_frames.push_back(sf::IntRect({950, 0}, {322, 331}));  // hero frame 4
    hand_kick_texture_frames.push_back(sf::IntRect({1380, 0}, {207, 331})); // hero frame 5

    if (!leg_kick_texture.loadFromFile("screens/main_menu/components/characters/joko/leg_kick_animation.png"))
    {
        throw std::runtime_error("Joko leg kick animation load failed");
    }

    // upd frames!!!
    std::vector<sf::IntRect> leg_kick_texture_frames;
    leg_kick_texture_frames.push_back(sf::IntRect({9, 0}, {257, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({364, 0}, {252, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({741, 0}, {205, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({1051, 0}, {302, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({1428, 0}, {327, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({1834, 0}, {346, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({2209, 0}, {273, 368}));

    if (!block_texture.loadFromFile("screens/main_menu/components/characters/joko/block_animation.png"))
    {
        throw std::runtime_error("Joko leg kick animation load failed");
    }

    std::vector<sf::IntRect> block_texture_frames;
    block_texture_frames.push_back(sf::IntRect({16, 5}, {251, 368}));
    block_texture_frames.push_back(sf::IntRect({318, 10}, {232, 363}));
    block_texture_frames.push_back(sf::IntRect({634, 10}, {246, 363}));
    block_texture_frames.push_back(sf::IntRect({944, 10}, {281, 363}));
    block_texture_frames.push_back(sf::IntRect({1343, 10}, {230, 363}));

    characters->emplace_back("Joko",
                             avatar1,
                             600,
                             100,
                             walk_texture,
                             walk_texture_frames,
                             jump_texture,
                             jump_texture_frames,
                             hand_kick_texture,
                             hand_kick_texture_frames,
                             leg_kick_texture,
                             leg_kick_texture_frames,
                             block_texture,
                             block_texture_frames);

    sf::Texture avatar2;
    if (!avatar2.loadFromFile("screens/main_menu/components/characters/jojo/avatar2.jpg"))
    {
        throw std::runtime_error("Jojo avatar load failed");
    }

    characters->emplace_back("Jojo", std::move(avatar2), 300, 1);

    sf::Texture avatar3;
    if (!avatar3.loadFromFile("screens/main_menu/components/characters/jola/avatar3.png"))
    {
        throw std::runtime_error("Jola avatar load failed");
    }

    characters->emplace_back("Jola", std::move(avatar3), 200, 1);

    sf::Texture avatar4;
    if (!avatar4.loadFromFile("screens/main_menu/components/characters/joma/avatar4.jpg"))
    {
        throw std::runtime_error("Joma avatar load failed");
    }

    characters->emplace_back("Joma", std::move(avatar4), 200, 1);

    sf::Texture avatar5;
    if (!avatar5.loadFromFile("screens/main_menu/components/characters/lana/avatr5.jpg"))
    {
        throw std::runtime_error("Lana avatar load failed");
    }

    characters->emplace_back("Lana", std::move(avatar5), 200, 1);

    sf::Texture avatar6;
    if (!avatar6.loadFromFile("screens/main_menu/components/characters/nala/avatar6.png"))
    {
        throw std::runtime_error("Nala avatar load failed");
    }

    characters->emplace_back("Nala", std::move(avatar6), 200, 1);
    return characters;
};