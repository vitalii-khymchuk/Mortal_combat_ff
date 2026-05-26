#pragma once
#include "modules/character/character.h"
#include "modules/character_rect_texture/character_rect_texture.h"
class FightModule;

class Player
{
    Character &_character;
    FightModule &_fight_module;
    sf::Clock _animation_clock;
    int _hp_percents = 100;

    float _y_speed = 0;
    int _current_frame_ = 0;
    bool _is_falling = true;
    bool _is_running_left = false;
    CharacterFightSprite *_active_sprite = nullptr;
    const std::vector<sf::IntRect> *_active_sprite_frames = nullptr;

    void _check_ground();
    void mirror_sprite(bool is_mirrored);

public:
    float _pos_x, _pos_y;

    Player(FightModule &fight_module, Character &character, const int &init_pos_x, const int &init_pos_y, const bool is_right_character);
    ~Player() = default;
    void handle_fps_signal();
    void move_left();
    void move_right();
    void jump();
    void reset_animation();
    void animate();
    void select_sprite(const sf::Texture &texture, const std::vector<sf::IntRect> &active_sprite_frames);
};