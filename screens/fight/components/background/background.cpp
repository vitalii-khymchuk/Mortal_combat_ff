#include "background.h"
#include "screens/fight/modules/fight_module/fight_module.h"
#include "modules/game/game.h"
#include <memory>

void init_background(FightModule *fight_module_ptr)
{
    sf::Texture &selected_bg = fight_module_ptr->_game.selected_bg;

    auto bg = std::make_unique<sf::Sprite>(selected_bg);

    sf::Vector2u window_size = fight_module_ptr->_game._window->getSize();
    sf::Vector2u texture_size = selected_bg.getSize();

    if (texture_size.x == 0 || texture_size.y == 0)
        return;

    float scale_x = static_cast<float>(window_size.x) / static_cast<float>(texture_size.x);
    float scale_y = static_cast<float>(window_size.y) / static_cast<float>(texture_size.y);

    bg->setPosition(sf::Vector2f(0.f, 0.f));
    bg->setScale(sf::Vector2f(scale_x, scale_y));

    fight_module_ptr->_game.shapes.emplace(fight_module_ptr->_game.shapes.begin(), std::move(bg));
}