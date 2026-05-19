#include "character_select.h"
#include "screens/main_menu/modules/main_menu_module.h"
#include "modules/character/character.h"
#include "modules/game/game.h"
#include "iostream"
#include "vector"

std::pair<float, float> ava_rect_size = {40.0f, 40.0f};
void init_char_select(MainMenuModule *main_menu_ptr)
{
    std::vector<Character> characterS;
    std::vector<std::string> avatar_names;
    std::vector<sf::Texture> avatar_images;

    int n=1;//количество персонажей 
    for(int i=0;i<n;i++)
    {
        Character ch( avatar_names[i], avatar_images[i]);
        characterS.push_back(ch);

    }

    std::vector<std::unique_ptr<sf::RectangleShape>> avas; 
    // for(int i=0;i<characterS.size();i++)
    // {

    // }
    avas.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(ava_rect_size.first, ava_rect_size.second)) );

    //sf::RectangleShape ava1(sf::Vector2f(ava_rect_size.first, ava_rect_size.second));
    
    std::pair<float, float> margin={20.0f,300.0f + 20.0f};
    avas[0]->setPosition(sf::Vector2f(margin.first, margin.second));
    

    std::pair<float, float> margin_act=margin;
    for(int i=1;i<characterS.size();i++)
    {
        
        sf::Vector2f vec_pos = avas[i-1]->getPosition();
        std::pair<float, float> pos={vec_pos.x, vec_pos.y};
        

        bool isFirstRow;
        if(margin_act.first < 400-ava_rect_size.first)
        {   
            isFirstRow=true;
            margin_act.first = pos.first + ava_rect_size.first + margin.first;
            margin_act.second = margin.second;

            avas.push_back(std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(ava_rect_size.first, ava_rect_size.second) ) ));
            avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));


        }

        else
        {
            if(isFirstRow) 
            {
                margin_act.first=margin.first;
                margin_act.second+=ava_rect_size.second+margin.second;

                avas.push_back(std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(ava_rect_size.first, ava_rect_size.second))));
                avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));
                isFirstRow=false;
                               
            }

            else 
            {
                margin_act.first = pos.first + ava_rect_size.first + margin.first;
                margin_act.second = margin.second;

                avas.push_back(std::make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(ava_rect_size.first, ava_rect_size.second))));
                avas[i]->setPosition(sf::Vector2f(margin_act.first, margin_act.second));
            }



        }

        

    }


    for(int i=0;i<avas.size();i++)
        {
            main_menu_ptr->_game.shapes.emplace_back(std::move(avas[i]));
        }


}