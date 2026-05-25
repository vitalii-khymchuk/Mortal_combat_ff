#pragma once
#include "modules/character/character.h"
class FightModule;

class Player : public Character
{
    FightModule &_fight_module;
    int _hp_percents = 100;

    float _y_speed = 0;
    int _current_frame_ = 0;
    bool _is_falling = true;
    bool _is_running_left = false;
    //_active_sprite

    void _check_ground();

public:
    int _pos_x, _pos_y;

    Player(const int &init_pos_x, const int &init_pos_y, const bool is_right_character);
    ~Player() = default;
    void handle_fps_signal();
    void move_left();
    void move_right();
    void jump();
    void animate();
    void select_sprite();
};