#pragma once

class Screen;
class Game;

#include <memory>
std::unique_ptr<Screen> init_fight_screen(Game &game);