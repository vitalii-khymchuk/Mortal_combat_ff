#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "My window");
    window.setFramerateLimit(60);

//RECTANGLE - BACKGROUND
     std::pair<float,float> rect_size = {260.0f,200.0f}; //rect_size.first -> float rect_size_x=260.0f;
    sf::RectangleShape rect(sf::Vector2f(rect_size.first,rect_size.second));

    std::pair<float,float> rect_pos = {400 - rect_size.first/2,10.0f};
    rect.setPosition(sf::Vector2f(rect_pos.first, rect_pos.second));

    // 2. Make the body completely transparent
    rect.setFillColor(sf::Color::Transparent);

    // 3. Define the outline properties
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(5.f);


// CIRCLES FOR CONTROL

  
    float circle_rad=30.0f;
    
    //positions for both circles
    std::vector< std::pair<float,float> > circleS_pos;
    circleS_pos.push_back( {(rect_pos.first/2), ((rect_pos.second+rect_size.second)/2)} );
    circleS_pos.push_back( {(  rect_size.first+3*(rect_pos.first/2) ), ((rect_pos.second+rect_size.second)/2)} );
    
    //CIRCLE 1 (LEFT)
    sf::CircleShape circle_l(circle_rad);
    circle_l.setOrigin(sf::Vector2f(circle_rad, circle_rad));


    circle_l.setFillColor(sf::Color::Transparent);

    // 3. Define the outline properties
    circle_l.setOutlineColor(sf::Color::White);
    circle_l.setOutlineThickness(5.f);

    circle_l.setPosition(sf::Vector2f( circleS_pos[0].first, circleS_pos[0].second));

    //CIRCLE 2 (RIGHT)
    sf::CircleShape circle_r(circle_rad);
    circle_r.setOrigin(sf::Vector2f(circle_rad, circle_rad));

    circle_r.setFillColor(sf::Color::Transparent);

    // 3. Define the outline properties
    circle_r.setOutlineColor(sf::Color::White);
    circle_r.setOutlineThickness(5.f);

    circle_r.setPosition(sf::Vector2f( circleS_pos[1].first, circleS_pos[1].second));
    
  
//Setting the horizontal devinding line
sf::RectangleShape horizontal_line(sf::Vector2f(760.0f,5.0f));
    horizontal_line.setPosition(sf::Vector2f(20.0f, 300.0f));
    horizontal_line.setFillColor(sf::Color::White);

// в будущем создать вектор std::vector<sf::Texture> textures; и присваивать их одному
    sf::Texture texture;
    std::vector<sf::Texture> textures_back;
    if (!texture.loadFromFile("C:/politech/VS_programs/Mortal_combat_ff/background1.png")) {
        return -1; // Возвращаем ошибку, если файл не найден
    }

    else
    {
        textures_back.push_back(texture);

    }
    
    sf::Sprite sprite(texture);
    sf::Vector2u texture_size = texture.getSize();

    float scale_x = rect_size.first / texture_size.x;   // 260.0f / 800.0f
    float scale_y = rect_size.second / texture_size.y; // 200.0f / 600.0f
    sprite.setScale(sf::Vector2f(scale_x, scale_y));

    //sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(rect_pos.first, rect_pos.second));


    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

          
        }

        window.clear(sf::Color::Black);
        window.draw(rect);
        window.draw(circle_r);
       window.draw(circle_l);
       window.draw(sprite);

       
       window.draw(horizontal_line);
        
        window.display();
    }

    return 0;
}