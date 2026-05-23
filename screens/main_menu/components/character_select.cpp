#include <SFML/Graphics.hpp>
#include "character_select.h"
#include "screens/main_menu/modules/main_menu_module.h"
#include "modules/character/character.h"
#include "modules/game/game.h"
#include <iostream>
#include <vector>
#include "modules/character_rect_texture/character_rect_texture.h"

void init_char_select(MainMenuModule *main_menu_ptr)
{
    std::pair<float, float> ava_rect_size = {60.0f, 60.0f};
    // std::vector<std::pair<float, float>> coordinates;
    std::unique_ptr<sf::Sprite> SPRITE_AVATARKA;

    if (!main_menu_ptr->_game.game_font.openFromFile("screens/main_menu/assets/pixel_font.ttf"))
        return;

    // 3. Создаём текст-подсказки внизу
    auto esc1 = std::make_unique<sf::Text>(main_menu_ptr->_game.game_font, "Exit -> ESC", 30);
    esc1->setFillColor(sf::Color::White);
    esc1->setPosition(sf::Vector2f(10.0f, 560.0f));

    auto entr2 = std::make_unique<sf::Text>(main_menu_ptr->_game.game_font, "Fight -> ENTER", 30);
    entr2->setFillColor(sf::Color::White);
    entr2->setPosition(sf::Vector2f(640.0f, 560.0f));

    auto selected_name_current = std::make_unique<sf::Text>(main_menu_ptr->_game.game_font, "", 30);
    sf::Vector2f select_name_pos = {0.0f, 510.0f};

    std::vector<Character> &characterS = *(main_menu_ptr->_characters);

    std::vector<std::unique_ptr<CharacterRectTexture>> avas;
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
            avas.emplace_back(std::make_unique<CharacterRectTexture>(
                sf::Vector2f(ava_rect_size.first, ava_rect_size.second), i));

            avas[0]->setPosition(sf::Vector2f(margin.first, 260.0f + margin.second));
            std::cout << "current square's postion -> x =" << margin.first << "  y = " << margin.second + 260.0f << std::endl;

            SPRITE_AVATARKA = std::make_unique<sf::Sprite>(characterS[i].get_avatarka());

            sf::Vector2u avatarka_texture_size = characterS[i].get_avatarka().getSize();

            float scale_x = ava_rect_size.first / avatarka_texture_size.x;
            float scale_y = ava_rect_size.second / avatarka_texture_size.y;
            SPRITE_AVATARKA->setScale(sf::Vector2f(scale_x, scale_y));

            SPRITE_AVATARKA->setPosition(sf::Vector2f(margin.first, 260.0f + margin.second));

            // if (i == 0) // условие что выбран квадрат
            // {
            avas[0]->setOutlineColor(sf::Color::Red);
            avas[0]->setOutlineThickness(5.0f);

            std::string avat_n = characterS[i].get_name();

            selected_name_current = std::make_unique<CharacterNameText>(main_menu_ptr->_game.game_font, " Fighter: " + avat_n, 40);
            selected_name_current->setFillColor(sf::Color::White);
            selected_name_current->setPosition(select_name_pos);
            //}

            continue;
        }

        sf::Vector2f vec_pos = avas[i - 1]->getPosition();
        std::pair<float, float> pos = {vec_pos.x, vec_pos.y};

        if (margin_act.first + 2 * ava_rect_size.first < 400 && isFirstRow)
        {

            margin_act.first = pos.first + ava_rect_size.first + margin.first;
            margin_act.second = 260.0f + margin.second;
            std::cout << "first row: current square's postion -> x =" << margin_act.first << "  y = " << margin_act.second << std::endl;

            avas.emplace_back(std::make_unique<CharacterRectTexture>(
                sf::Vector2f(ava_rect_size.first, ava_rect_size.second), i));
            avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));
            // selected_name_current = std::make_unique<CharacterNameText>(main_menu_ptr->_game.game_font, " Fighter: " + avat_n, 40, true);
        }

        else
        {
            if (isFirstRow)
            {
                isFirstRow = false;
                margin_act.first = margin.first;
                margin_act.second = ava_rect_size.second + 260.0f + 2 * margin.second;

                avas.emplace_back(std::make_unique<CharacterRectTexture>(
                    sf::Vector2f(ava_rect_size.first, ava_rect_size.second), i));
                avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));

                std::cout << "current square's postion -> x =" << margin_act.first << "  y = " << margin_act.second << std::endl;
            }

            else
            {
                margin_act.first = pos.first + ava_rect_size.first + margin.first;

                avas.emplace_back(std::make_unique<CharacterRectTexture>(
                    sf::Vector2f(ava_rect_size.first, ava_rect_size.second), i));
                avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));

                std::cout << "current square's postion -> x =" << margin_act.first << "  y = " << margin_act.second << std::endl;
            }
        }
        avas[i]->setOutlineThickness(5.0f);
    }

    main_menu_ptr->_game.shapes.emplace_back(std::move(esc1));
    main_menu_ptr->_game.shapes.emplace_back(std::move(entr2));

    auto vertical_line = std::make_unique<sf::RectangleShape>(sf::Vector2f(5.0f, 300.0f));
    vertical_line->setPosition(sf::Vector2f(400.0f, 260.0f));
    vertical_line->setFillColor(sf::Color::White);
    main_menu_ptr->_game.shapes.emplace_back(std::move(vertical_line));

    auto horizontal_line = std::make_unique<sf::RectangleShape>(sf::Vector2f(800.0f, 2.0f));
    horizontal_line->setPosition(sf::Vector2f(0.0f, 560.0f));
    horizontal_line->setFillColor(sf::Color::White);
    main_menu_ptr->_game.shapes.emplace_back(std::move(horizontal_line));

    for (int i = 0; i < avas.size(); i++)
    {
        main_menu_ptr->_game.shapes.emplace_back(std::move(avas[i]));
    }

    main_menu_ptr->_game.shapes.emplace_back(std::move(selected_name_current));
    // main_menu_ptr->_game.shapes.emplace_back(std::move(SPRITE_AVATARKA));
}