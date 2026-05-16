#include "main_menu.h"
#include "modules/main_menu_module.h"
#include "modules/game/game.h";

std::unique_ptr<Screen> init_main_menu(Game &game)
{
    return std::make_unique<MainMenuModule>(game);
};