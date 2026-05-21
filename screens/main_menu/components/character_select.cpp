#include "character_select.h"
#include "screens/main_menu/modules/main_menu_module.h"
#include "modules/character/character.h"
#include "modules/game/game.h"
#include <iostream>
#include <vector>

std::pair<float, float> ava_rect_size = {60.0f, 60.0f};
std::vector<std::pair<float, float>> coordinates;
void init_char_select(MainMenuModule *main_menu_ptr)
{
    std::vector<Character> characterS;
    std::vector<std::string> avatar_names = {"Joko", "Jojo", "Jola", "Joma", "Lana", "Nala"};
    std::vector<sf::Texture> avatar_images(6);
    avatar_images[0].loadFromFile("screens/main_menu/assets/avatar1.png");
    avatar_images[1].loadFromFile("screens/main_menu/assets/avatar2.jpg");
    avatar_images[2].loadFromFile("screens/main_menu/assets/avatar3.png");
    avatar_images[3].loadFromFile("screens/main_menu/assets/avatar4.jpg");
    avatar_images[4].loadFromFile("screens/main_menu/assets/avatar5.jpg");
    avatar_images[5].loadFromFile("screens/main_menu/assets/avatar6.png");

    for (int i = 0; i < avatar_names.size(); i++)
    {
        Character ch(avatar_names[i], avatar_images[i]);
        characterS.push_back(ch);
    }

    std::vector<std::unique_ptr<sf::RectangleShape>> avas;
    double margin_area = 400 * 260 - ava_rect_size.first * ava_rect_size.second;
    double margin0 = margin_area / (1200 + 8 * ava_rect_size.first);

    std::pair<float, float> margin = {margin0, margin0 * 0.8};

    // считаем количество рядов

    std::pair<float, float> margin_act = margin;
    bool isFirstRow = true;
    for (int i = 0; i < characterS.size(); i++)
    {
        if (i == 0)
        {
            avas.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(ava_rect_size.first, ava_rect_size.second)));

            // хотела получить значения отступа такое чтобы с каждой стороны было одинаковое

            avas[0]->setPosition(sf::Vector2f(margin.first, 260.0f + margin.second));
            std::cout << "current square's postion -> x =" << margin.first << "  y = " << margin.second + 260.0f << std::endl;
            avas[0]->setOutlineThickness(5.0f);
            avas[0]->setOutlineColor(sf::Color::Red);
            continue;
        }

        sf::Vector2f vec_pos = avas[i - 1]->getPosition();
        std::pair<float, float> pos = {vec_pos.x, vec_pos.y};

        if (margin_act.first + 2 * ava_rect_size.first < 400 && isFirstRow)
        {

            margin_act.first = pos.first + ava_rect_size.first + margin.first;
            margin_act.second = 260.0f + margin.second;
            std::cout << "first row: current square's postion -> x =" << margin_act.first << "  y = " << margin_act.second << std::endl;

            avas.push_back(std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(ava_rect_size.first, ava_rect_size.second))));
            avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));
        }

        else
        {
            if (isFirstRow)
            {
                isFirstRow = false;
                margin_act.first = margin.first;
                margin_act.second = ava_rect_size.second + 260.0f + 2 * margin.second;

                avas.push_back(std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(ava_rect_size.first, ava_rect_size.second))));
                avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));

                std::cout << "current square's postion -> x =" << margin_act.first << "  y = " << margin_act.second << std::endl;
            }

            else
            {
                margin_act.first = pos.first + ava_rect_size.first + margin.first;

                avas.push_back(std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(ava_rect_size.first, ava_rect_size.second))));
                avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));

                std::cout << "current square's postion -> x =" << margin_act.first << "  y = " << margin_act.second << std::endl;
            }
        }
    }

    auto vertical_line = std::make_unique<sf::RectangleShape>(sf::Vector2f(5.0f, 260.0f));
    vertical_line->setPosition(sf::Vector2f(400.0f, 260.0f));
    vertical_line->setFillColor(sf::Color::White);
    main_menu_ptr->_game.shapes.emplace_back(std::move(vertical_line));

    auto horizontal_line = std::make_unique<sf::RectangleShape>(sf::Vector2f(800.0f, 2.0f));
    horizontal_line->setPosition(sf::Vector2f(0.0f, 520.0f));
    horizontal_line->setFillColor(sf::Color::White);
    main_menu_ptr->_game.shapes.emplace_back(std::move(horizontal_line));

    for (int i = 0; i < avas.size(); i++)
    {
        main_menu_ptr->_game.shapes.emplace_back(std::move(avas[i]));
    }
}