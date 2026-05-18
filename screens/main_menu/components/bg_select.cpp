#include "bg_select.h"
#include "screens/main_menu/modules/main_menu_module.h"
#include "modules/game/game.h"
#include "iostream"

// RECTANGLE - BACKGROUND
std::pair<float, float> rect_size = {260.0f, 200.0f}; // rect_size.first -> float rect_size_x=260.0f;
auto rect = std::make_unique<sf::RectangleShape>(sf::Vector2f(rect_size.first, rect_size.second));

std::pair<float, float> rect_pos = {400 - rect_size.first / 2, 10.0f};

void init_bg_select(MainMenuModule *main_menu_ptr)
{
    rect->setPosition(sf::Vector2f(rect_pos.first, rect_pos.second));

    // 2. Make the body completely transparent
    rect->setFillColor(sf::Color::Transparent);

    // 3. Define the outline properties
    rect->setOutlineColor(sf::Color::White);
    rect->setOutlineThickness(5.f);

    // CIRCLES FOR CONTROL

    float circle_rad = 30.0f;

    // positions for both circles
    std::vector<std::pair<float, float>> circleS_pos;
    circleS_pos.push_back({(rect_pos.first / 2), ((rect_pos.second + rect_size.second) / 2)});
    circleS_pos.push_back({(rect_size.first + 3 * (rect_pos.first / 2)), ((rect_pos.second + rect_size.second) / 2)});

    // CIRCLE 1 (LEFT)
    auto circle_l = std::make_unique<sf::CircleShape>(circle_rad);
    circle_l->setOrigin(sf::Vector2f(circle_rad, circle_rad));

    circle_l->setFillColor(sf::Color::Transparent);

    // 3. Define the outline properties
    circle_l->setOutlineColor(sf::Color::White);
    circle_l->setOutlineThickness(5.f);

    circle_l->setPosition(sf::Vector2f(circleS_pos[0].first, circleS_pos[0].second));

    // CIRCLE 2 (RIGHT)
    auto circle_r = std::make_unique<sf::CircleShape>(circle_rad);
    circle_r->setOrigin(sf::Vector2f(circle_rad, circle_rad));

    circle_r->setFillColor(sf::Color::Transparent);

    // 3. Define the outline properties
    circle_r->setOutlineColor(sf::Color::White);
    circle_r->setOutlineThickness(5.f);

    circle_r->setPosition(sf::Vector2f(circleS_pos[1].first, circleS_pos[1].second));

    // Setting the horizontal devinding line
    auto horizontal_line = std::make_unique<sf::RectangleShape>(sf::Vector2f(760.0f, 5.0f));
    horizontal_line->setPosition(sf::Vector2f(20.0f, 300.0f));
    horizontal_line->setFillColor(sf::Color::White);

    // Create sprite from selected background
    auto sprite = std::make_unique<sf::Sprite>(main_menu_ptr->_game.selected_bg);
    sf::Vector2u texture_size = main_menu_ptr->_game.selected_bg.getSize();

    float scale_x = rect_size.first / texture_size.x;  // 260.0f / 800.0f
    float scale_y = rect_size.second / texture_size.y; // 200.0f / 600.0f
    sprite->setScale(sf::Vector2f(scale_x, scale_y));

    sprite->setPosition(sf::Vector2f(rect_pos.first, rect_pos.second));

    main_menu_ptr->_game.shapes.emplace_back(std::move(rect));
    main_menu_ptr->_game.shapes.emplace_back(std::move(circle_r));
    main_menu_ptr->_game.shapes.emplace_back(std::move(circle_l));
    main_menu_ptr->_game.shapes.emplace_back(std::move(sprite));
    main_menu_ptr->_game.shapes.emplace_back(std::move(horizontal_line));
}