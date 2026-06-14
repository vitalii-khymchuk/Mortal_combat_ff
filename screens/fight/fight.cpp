#include "fight.h"
#include "modules/fight_module/fight_module.h"
#include "modules/game/game.h"

std::unique_ptr<Screen> init_fight_screen(Game &game)
{
    return std::make_unique<FightModule>(game);
};