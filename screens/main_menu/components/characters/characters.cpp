#include "characters.h"
#include <SFML/Graphics.hpp>

std::unique_ptr<std::vector<Character>> init_characters()

{
    auto characters = std::make_unique<std::vector<Character>>();
    characters->reserve(6);

    sf::Texture avatar1, walk_texture, jump_texture, hand_kick_texture, leg_kick_texture, block_texture;
    if (!avatar1.loadFromFile("screens/main_menu/components/characters/Sgt. Barklee/avatar1.png"))
    {
        throw std::runtime_error("Sgt. Barklee avatar load failed");
    }
    if (!walk_texture.loadFromFile("screens/main_menu/components/characters/Sgt. Barklee/walk_animation.png"))
    {
        throw std::runtime_error("Sgt. Barklee walk animation load failed");
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

    if (!jump_texture.loadFromFile("screens/main_menu/components/characters/Sgt. Barklee/jump_animation.png"))
    {
        throw std::runtime_error("Sgt. Barklee jump animation load failed");
    }

    std::vector<sf::IntRect> jump_texture_frames;
    jump_texture_frames.push_back(sf::IntRect({13, 76}, {172, 240}));   // hero frame 1 right_x = 208
    jump_texture_frames.push_back(sf::IntRect({249, 75}, {180, 239}));  // hero frame 2 right_x = 412
    jump_texture_frames.push_back(sf::IntRect({482, 20}, {190, 294}));  // hero frame 3 right_x = 708
    jump_texture_frames.push_back(sf::IntRect({700, 14}, {200, 299}));  // hero frame 4 right_x = 942
    jump_texture_frames.push_back(sf::IntRect({945, 55}, {195, 259}));  // hero frame 5 right_x = 1162
    jump_texture_frames.push_back(sf::IntRect({1179, 70}, {219, 243})); // hero frame 6 right_x = 1405

    if (!hand_kick_texture.loadFromFile("screens/main_menu/components/characters/Sgt. Barklee/hand_kick_animation.png"))
    {
        throw std::runtime_error("Sgt. Barklee hand kick animation load failed");
    }

    std::vector<sf::IntRect> hand_kick_texture_frames;
    hand_kick_texture_frames.push_back(sf::IntRect({1, 0}, {219, 335}));    // hero frame 1
    hand_kick_texture_frames.push_back(sf::IntRect({268, 0}, {207, 331}));  // hero frame 2
    hand_kick_texture_frames.push_back(sf::IntRect({589, 0}, {275, 331}));  // hero frame 3
    hand_kick_texture_frames.push_back(sf::IntRect({950, 0}, {322, 331}));  // hero frame 4
    hand_kick_texture_frames.push_back(sf::IntRect({1380, 0}, {207, 331})); // hero frame 5

    if (!leg_kick_texture.loadFromFile("screens/main_menu/components/characters/Sgt. Barklee/leg_kick_animation.png"))
    {
        throw std::runtime_error("Sgt. Barklee leg kick animation load failed");
    }

    std::vector<sf::IntRect> leg_kick_texture_frames;
    leg_kick_texture_frames.push_back(sf::IntRect({9, 0}, {257, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({364, 0}, {252, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({741, 0}, {205, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({1051, 0}, {302, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({1428, 0}, {327, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({1834, 0}, {346, 368}));
    leg_kick_texture_frames.push_back(sf::IntRect({2209, 0}, {273, 368}));

    if (!block_texture.loadFromFile("screens/main_menu/components/characters/Sgt. Barklee/block_animation.png"))
    {
        throw std::runtime_error("Sgt. Barklee leg kick animation load failed");
    }

    std::vector<sf::IntRect> block_texture_frames;
    block_texture_frames.push_back(sf::IntRect({16, 5}, {251, 368}));
    block_texture_frames.push_back(sf::IntRect({318, 10}, {232, 363}));
    block_texture_frames.push_back(sf::IntRect({634, 10}, {246, 363}));
    block_texture_frames.push_back(sf::IntRect({944, 10}, {281, 363}));
    block_texture_frames.push_back(sf::IntRect({1343, 10}, {230, 363}));

    specs specs1 = specs({._x_speed_max = 1000,
                          ._weight_factor = 1.5,
                          ._height_px = 120,
                          ._hp_factor = 0.8,
                          ._stamina_recovery_factor = 0.7,
                          ._hand_recovery_sec = 1,
                          ._leg_recovery_sec = 1.5,
                          ._hand_force = 7,
                          ._leg_force = 10});

    characters->emplace_back("Sgt. Barklee",
                             avatar1,
                             specs1,
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
    if (!avatar2.loadFromFile("screens/main_menu/components/characters/Cluck Norris/avatar2.png"))
    {
        throw std::runtime_error("Cluck Norris avatar load failed");
    }

    specs specs2 = specs({._x_speed_max = 1300,
                          ._weight_factor = 2,
                          ._height_px = 100,
                          ._hp_factor = 1.2,
                          ._stamina_recovery_factor = 1,
                          ._hand_recovery_sec = 0.5,
                          ._leg_recovery_sec = 1.0,
                          ._hand_force = 5,
                          ._leg_force = 8});

    if (!walk_texture.loadFromFile("screens/main_menu/components/characters/Cluck Norris/walk_animation.png"))
    {
        throw std::runtime_error("Cluck Norris walk animation load failed");
    }

    walk_texture_frames.clear();
    walk_texture_frames.push_back(sf::IntRect({7, 16}, {233, 384}));
    walk_texture_frames.push_back(sf::IntRect({267, 16}, {225, 384}));
    walk_texture_frames.push_back(sf::IntRect({528, 16}, {222, 384}));
    walk_texture_frames.push_back(sf::IntRect({786, 16}, {234, 384}));
    walk_texture_frames.push_back(sf::IntRect({1053, 16}, {196, 384}));
    walk_texture_frames.push_back(sf::IntRect({1275, 16}, {197, 384}));
    walk_texture_frames.push_back(sf::IntRect({1538, 16}, {246, 384}));
    walk_texture_frames.push_back(sf::IntRect({1824, 16}, {212, 384}));
    walk_texture_frames.push_back(sf::IntRect({2074, 16}, {234, 384}));
    walk_texture_frames.push_back(sf::IntRect({2337, 16}, {196, 384}));

    if (!jump_texture.loadFromFile("screens/main_menu/components/characters/Cluck Norris/jump_animation.png"))
    {
        throw std::runtime_error("Cluck Norris jump animation load failed");
    }

    jump_texture_frames.clear();
    jump_texture_frames.push_back(sf::IntRect({45, 26}, {207, 371}));
    jump_texture_frames.push_back(sf::IntRect({283, 26}, {256, 371}));
    jump_texture_frames.push_back(sf::IntRect({629, 26}, {291, 371}));
    jump_texture_frames.push_back(sf::IntRect({1021, 26}, {264, 371}));
    jump_texture_frames.push_back(sf::IntRect({1385, 26}, {224, 371}));
    jump_texture_frames.push_back(sf::IntRect({1671, 26}, {225, 371}));

    if (!hand_kick_texture.loadFromFile("screens/main_menu/components/characters/Cluck Norris/hand_kick_animation.png"))
    {
        throw std::runtime_error("Cluck Norris hand hit animation load failed");
    }

    hand_kick_texture_frames.clear();
    hand_kick_texture_frames.push_back(sf::IntRect({84, 19}, {266, 455}));
    hand_kick_texture_frames.push_back(sf::IntRect({427, 19}, {275, 445}));
    hand_kick_texture_frames.push_back(sf::IntRect({788, 19}, {401, 445}));
    hand_kick_texture_frames.push_back(sf::IntRect({1255, 19}, {489, 445}));
    hand_kick_texture_frames.push_back(sf::IntRect({1786, 19}, {275, 445}));

    if (!leg_kick_texture.loadFromFile("screens/main_menu/components/characters/Cluck Norris/leg_kick_animation.png"))
    {
        throw std::runtime_error("Cluck Norris leg kick animation load failed");
    }

    leg_kick_texture_frames.clear();
    leg_kick_texture_frames.push_back(sf::IntRect({34, 22}, {277, 446}));
    leg_kick_texture_frames.push_back(sf::IntRect({400, 22}, {292, 446}));
    leg_kick_texture_frames.push_back(sf::IntRect({758, 22}, {443, 446}));
    leg_kick_texture_frames.push_back(sf::IntRect({1233, 22}, {261, 446}));

    if (!block_texture.loadFromFile("screens/main_menu/components/characters/Cluck Norris/block_animation.png"))
    {
        throw std::runtime_error("Cluck Norris block animation load failed");
    }

    block_texture_frames.clear();
    block_texture_frames.push_back(sf::IntRect({14, 14}, {262, 427}));
    block_texture_frames.push_back(sf::IntRect({350, 14}, {289, 427}));
    block_texture_frames.push_back(sf::IntRect({704, 14}, {304, 427}));
    block_texture_frames.push_back(sf::IntRect({1095, 14}, {316, 427}));
    block_texture_frames.push_back(sf::IntRect({1487, 14}, {321, 427}));

    characters->emplace_back("Cluck Norris",
                             std::move(avatar2),
                             specs2,
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

    sf::Texture avatar3;
    if (!avatar3.loadFromFile("screens/main_menu/components/characters/Rambo/avatar3.png"))
    {
        throw std::runtime_error("Rambo avatar load failed");
    }

    specs specs3 = specs({._x_speed_max = 600,
                          ._weight_factor = 1,
                          ._height_px = 120,
                          ._hp_factor = 0.8,
                          ._stamina_recovery_factor = 0.7,
                          ._hand_recovery_sec = 1,
                          ._leg_recovery_sec = 1.5,
                          ._hand_force = 7,
                          ._leg_force = 10});

    if (!walk_texture.loadFromFile("screens/main_menu/components/characters/Rambo/walk_animation.png"))
    {
        throw std::runtime_error("Rambo walk animation load failed");
    }

    walk_texture_frames.clear();
    walk_texture_frames.push_back(sf::IntRect({62, 22}, {259, 328}));
    walk_texture_frames.push_back(sf::IntRect({380, 22}, {297, 328}));
    walk_texture_frames.push_back(sf::IntRect({764, 22}, {258, 328}));
    walk_texture_frames.push_back(sf::IntRect({1124, 22}, {253, 328}));
    walk_texture_frames.push_back(sf::IntRect({1448, 22}, {289, 328}));
    walk_texture_frames.push_back(sf::IntRect({1797, 22}, {265, 328}));
    walk_texture_frames.push_back(sf::IntRect({2113, 22}, {257, 328}));
    walk_texture_frames.push_back(sf::IntRect({2427, 22}, {270, 328}));
    walk_texture_frames.push_back(sf::IntRect({2788, 22}, {257, 328}));

    if (!jump_texture.loadFromFile("screens/main_menu/components/characters/Rambo/jump_animation.png"))
    {
        throw std::runtime_error("Rambo jump animation load failed");
    }

    jump_texture_frames.clear();
    jump_texture_frames.push_back(sf::IntRect({153, 39}, {254, 352}));
    jump_texture_frames.push_back(sf::IntRect({548, 39}, {277, 352}));
    jump_texture_frames.push_back(sf::IntRect({967, 39}, {253, 352}));
    jump_texture_frames.push_back(sf::IntRect({1291, 39}, {266, 352}));
    jump_texture_frames.push_back(sf::IntRect({1578, 132}, {236, 253}));
    jump_texture_frames.push_back(sf::IntRect({1876, 39}, {236, 352}));
    jump_texture_frames.push_back(sf::IntRect({2208, 39}, {283, 352}));

    if (!hand_kick_texture.loadFromFile("screens/main_menu/components/characters/Rambo/hand_kick_animation.png"))
    {
        throw std::runtime_error("Rambo hand hit animation load failed");
    }

    hand_kick_texture_frames.clear();
    hand_kick_texture_frames.push_back(sf::IntRect({90, 81}, {240, 293}));
    hand_kick_texture_frames.push_back(sf::IntRect({384, 81}, {273, 293}));
    hand_kick_texture_frames.push_back(sf::IntRect({762, 81}, {347, 293}));
    hand_kick_texture_frames.push_back(sf::IntRect({1144, 81}, {383, 293}));
    hand_kick_texture_frames.push_back(sf::IntRect({1549, 81}, {303, 293}));

    if (!leg_kick_texture.loadFromFile("screens/main_menu/components/characters/Rambo/leg_kick_animation.png"))
    {
        throw std::runtime_error("Rambo leg kick animation load failed");
    }

    leg_kick_texture_frames.clear();
    leg_kick_texture_frames.push_back(sf::IntRect({103, 71}, {263, 298}));
    leg_kick_texture_frames.push_back(sf::IntRect({440, 71}, {223, 298}));
    leg_kick_texture_frames.push_back(sf::IntRect({717, 71}, {291, 298}));
    leg_kick_texture_frames.push_back(sf::IntRect({1064, 71}, {235, 298}));
    leg_kick_texture_frames.push_back(sf::IntRect({1414, 71}, {259, 298}));
    leg_kick_texture_frames.push_back(sf::IntRect({1793, 71}, {259, 298}));

    if (!block_texture.loadFromFile("screens/main_menu/components/characters/Rambo/block_animation.png"))
    {
        throw std::runtime_error("Rambo block animation load failed");
    }

    block_texture_frames.clear();
    block_texture_frames.push_back(sf::IntRect({129, 78}, {286, 326}));
    block_texture_frames.push_back(sf::IntRect({542, 78}, {284, 326}));
    block_texture_frames.push_back(sf::IntRect({951, 78}, {245, 326}));

    characters->emplace_back("Rambo",
                             std::move(avatar3),
                             specs3,
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

    sf::Texture avatar4;
    if (!avatar4.loadFromFile("screens/main_menu/components/characters/Bacon/avatar4.png"))
    {
        throw std::runtime_error("Bacon avatar load failed");
    }

    specs specs4 = specs({._x_speed_max = 600,
                          ._weight_factor = 1,
                          ._height_px = 120,
                          ._hp_factor = 0.8,
                          ._stamina_recovery_factor = 0.7,
                          ._hand_recovery_sec = 1,
                          ._leg_recovery_sec = 1.5,
                          ._hand_force = 7,
                          ._leg_force = 10});

    if (!walk_texture.loadFromFile("screens/main_menu/components/characters/Bacon/walk_animation.png"))
    {
        throw std::runtime_error("Bacon walk animation load failed");
    }

    walk_texture_frames.clear();
    walk_texture_frames.push_back(sf::IntRect({0, 0}, {207, 363}));
    walk_texture_frames.push_back(sf::IntRect({221, 0}, {258, 363}));
    walk_texture_frames.push_back(sf::IntRect({489, 0}, {206, 363}));
    walk_texture_frames.push_back(sf::IntRect({702, 0}, {247, 363}));
    walk_texture_frames.push_back(sf::IntRect({981, 0}, {272, 363}));
    walk_texture_frames.push_back(sf::IntRect({1274, 0}, {262, 363}));

    if (!jump_texture.loadFromFile("screens/main_menu/components/characters/Bacon/jump_animation.png"))
    {
        throw std::runtime_error("Bacon jump animation load failed");
    }

    jump_texture_frames.clear();
    jump_texture_frames.push_back(sf::IntRect({0, 0}, {335, 480}));
    jump_texture_frames.push_back(sf::IntRect({814, 0}, {343, 480}));
    jump_texture_frames.push_back(sf::IntRect({1208, 0}, {323, 480}));
    jump_texture_frames.push_back(sf::IntRect({1560, 0}, {302, 480}));

    if (!hand_kick_texture.loadFromFile("screens/main_menu/components/characters/Bacon/hand_kick_animation.png"))
    {
        throw std::runtime_error("Bacon hand hit animation load failed");
    }

    hand_kick_texture_frames.clear();
    hand_kick_texture_frames.push_back(sf::IntRect({0, 0}, {332, 481}));
    hand_kick_texture_frames.push_back(sf::IntRect({448, 0}, {316, 481}));
    hand_kick_texture_frames.push_back(sf::IntRect({858, 0}, {405, 481}));
    hand_kick_texture_frames.push_back(sf::IntRect({1292, 0}, {463, 481}));
    hand_kick_texture_frames.push_back(sf::IntRect({1902, 0}, {298, 481}));

    if (!leg_kick_texture.loadFromFile("screens/main_menu/components/characters/Bacon/leg_kick_animation.png"))
    {
        throw std::runtime_error("Bacon leg kick animation load failed");
    }

    leg_kick_texture_frames.clear();
    leg_kick_texture_frames.push_back(sf::IntRect({0, 0}, {262, 384}));
    leg_kick_texture_frames.push_back(sf::IntRect({695, 0}, {209, 384}));
    leg_kick_texture_frames.push_back(sf::IntRect({1728, 0}, {342, 384}));
    leg_kick_texture_frames.push_back(sf::IntRect({2073, 0}, {265, 384}));

    if (!block_texture.loadFromFile("screens/main_menu/components/characters/Bacon/block_animation.png"))
    {
        throw std::runtime_error("Bacon block animation load failed");
    }

    block_texture_frames.clear();
    block_texture_frames.push_back(sf::IntRect({0, 0}, {350, 480}));
    block_texture_frames.push_back(sf::IntRect({826, 0}, {284, 480}));
    block_texture_frames.push_back(sf::IntRect({1890, 0}, {275, 480}));
    characters->emplace_back("Bacon", std::move(avatar4), specs4,
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

    sf::Texture avatar5;
    if (!avatar5.loadFromFile("screens/main_menu/components/characters/Bulldozer/avatr5.png"))
    {
        throw std::runtime_error("Bulldozer avatar load failed");
    }

    specs specs5 = specs({._x_speed_max = 600,
                          ._weight_factor = 1,
                          ._height_px = 120,
                          ._hp_factor = 0.8,
                          ._stamina_recovery_factor = 0.7,
                          ._hand_recovery_sec = 1,
                          ._leg_recovery_sec = 1.5,
                          ._hand_force = 7,
                          ._leg_force = 10});

    characters->emplace_back("Bulldozer", std::move(avatar5), specs5);

    sf::Texture avatar6;
    if (!avatar6.loadFromFile("screens/main_menu/components/characters/Colt/avatar6.png"))
    {
        throw std::runtime_error("Colt avatar load failed");
    }

    specs specs6 = specs({._x_speed_max = 600,
                          ._weight_factor = 1,
                          ._height_px = 120,
                          ._hp_factor = 0.8,
                          ._stamina_recovery_factor = 0.7,
                          ._hand_recovery_sec = 1,
                          ._leg_recovery_sec = 1.5,
                          ._hand_force = 7,
                          ._leg_force = 10});

    characters->emplace_back("Colt", std::move(avatar6), specs6);
    return characters;
};