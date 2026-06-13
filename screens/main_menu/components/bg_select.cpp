#include "bg_select.h"
#include "screens/main_menu/modules/main_menu_module.h"
#include "modules/game/game.h"
#include "iostream"
#include <vector>

void init_bg_select(MainMenuModule *main_menu_ptr)
{

    if (!(main_menu_ptr->menu_bg).loadFromFile("screens/main_menu/assets/background_menu.PNG"))
    {
        return;
    }

    auto sprite_background_pic = std::make_unique<sf::Sprite>(main_menu_ptr->menu_bg);
    sprite_background_pic->setPosition(sf::Vector2f(0.0f, 0.0f));

    sf::Vector2u size = (main_menu_ptr->menu_bg).getSize();
    double x0 = size.x;
    double y0 = size.y;
    sprite_background_pic->setScale(sf::Vector2f(800 / x0, 600 / y0));
    main_menu_ptr->_game.shapes.emplace_back(std::move(sprite_background_pic));

    // RECTANGLE - BACKGROUND
    std::pair<float, float> rect_size = {260.0f, 200.0f}; // rect_size.first -> float rect_size_x=260.0f;
    auto rect = std::make_unique<sf::RectangleShape>(sf::Vector2f(rect_size.first, rect_size.second));
    std::pair<float, float> rect_pos = {400 - rect_size.first / 2, 10.0f};

    rect->setPosition(sf::Vector2f(rect_pos.first, rect_pos.second));

    // 2. Make the body completely transparent
    rect->setFillColor(sf::Color::Transparent);

    // 3. Define the outline properties
    rect->setOutlineColor(sf::Color::White);
    rect->setOutlineThickness(5.f);

    // CIRCLES FOR CONTROL

    // float circle_rad = 30.0f;

    // // positions for both circles
    // std::vector<std::pair<float, float>> circleS_pos;
    // circleS_pos.push_back({(rect_pos.first / 2), ((rect_pos.second + rect_size.second) / 2)});
    // circleS_pos.push_back({(rect_size.first + 3 * (rect_pos.first / 2)), ((rect_pos.second + rect_size.second) / 2)});

    // // CIRCLE 1 (LEFT)
    // auto circle_l = std::make_unique<sf::CircleShape>(circle_rad);
    // circle_l->setOrigin(sf::Vector2f(circle_rad, circle_rad));

    // circle_l->setFillColor(sf::Color::Transparent);

    // // 3. Define the outline properties
    // circle_l->setOutlineColor(sf::Color::White);
    // circle_l->setOutlineThickness(5.f);
    // circle_l->setFillColor(sf::Color::Transparent);
    // circle_l->setPosition(sf::Vector2f(circleS_pos[0].first, circleS_pos[0].second));

    // auto select_O = std::make_unique<sf::Text>(main_menu_ptr->_game.game_font, "O", 50);
    // sf::FloatRect bounds_O = select_O->getLocalBounds();
    // select_O->setOrigin(sf::Vector2f(bounds_O.position.x + bounds_O.size.x / 2.f,
    //                                  bounds_O.position.y + bounds_O.size.y / 2.f));
    // select_O->setFillColor(sf::Color::White);
    // select_O->setPosition(sf::Vector2f(circleS_pos[0].first, circleS_pos[0].second));

    // auto select_I = std::make_unique<sf::Text>(main_menu_ptr->_game.game_font, "I", 50);
    // sf::FloatRect bounds_I = select_I->getLocalBounds();
    // select_I->setFillColor(sf::Color::White);
    // select_I->setPosition(sf::Vector2f(circleS_pos[0].first - 2, circleS_pos[0].second - 35));

    // // CIRCLE 2 (RIGHT)
    // auto circle_r = std::make_unique<sf::CircleShape>(circle_rad);
    // circle_r->setOrigin(sf::Vector2f(circle_rad, circle_rad));

    // circle_r->setFillColor(sf::Color::Transparent);

    // // 3. Define the outline properties
    // circle_r->setOutlineColor(sf::Color::White);
    // circle_r->setOutlineThickness(5.f);

    // circle_r->setPosition(sf::Vector2f(circleS_pos[1].first, circleS_pos[1].second));

    // auto select_O = std::make_unique<sf::Text>(main_menu_ptr->_game.game_font, "O", 50);
    // select_O->setFillColor(sf::Color::White);
    // // Use getGlobalBounds() for true visual centering (accounts for font metrics)
    // select_O->setPosition(sf::Vector2f(circleS_pos[1].first - 8, circleS_pos[1].second - 35));

    // Setting the horizontal devinding line
    auto horizontal_line = std::make_unique<sf::RectangleShape>(sf::Vector2f(800.0f, 5.0f));
    horizontal_line->setPosition(sf::Vector2f(0.0f, 260.0f));
    horizontal_line->setFillColor(sf::Color::White);

    // Create sprite from selected background
    auto sprite = std::make_unique<sf::Sprite>(main_menu_ptr->_game.selected_bg);
    sf::Vector2u texture_size = main_menu_ptr->_game.selected_bg.getSize();

    float scale_x = rect_size.first / texture_size.x;  // 260.0f / 800.0f
    float scale_y = rect_size.second / texture_size.y; // 200.0f / 600.0f
    sprite->setScale(sf::Vector2f(scale_x, scale_y));

    sprite->setPosition(sf::Vector2f(rect_pos.first, rect_pos.second));

    main_menu_ptr->_game.shapes.emplace_back(std::move(rect));
    // main_menu_ptr->_game.shapes.emplace_back(std::move(circle_r));
    // main_menu_ptr->_game.shapes.emplace_back(std::move(circle_l));
    // main_menu_ptr->_game.shapes.emplace_back(std::move(select_O));
    // main_menu_ptr->_game.shapes.emplace_back(std::move(select_I));
    main_menu_ptr->_game.shapes.emplace_back(std::move(sprite));
    main_menu_ptr->_game.shapes.emplace_back(std::move(horizontal_line));
}