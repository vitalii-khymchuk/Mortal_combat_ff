#include "fight_module.h"
#include "modules/game/game.h"
#include "screens/fight/components/background/background.h"

FightModule::FightModule(Game &game) : Screen(), _game(game)
{
    // init modules
    init_background(this);
};

void FightModule::handle_event(const sf::Event &event) {};