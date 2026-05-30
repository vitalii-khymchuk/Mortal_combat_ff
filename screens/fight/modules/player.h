#pragma once
#include "modules/character/character.h"
#include "modules/character_rect_texture/character_rect_texture.h"
class FightModule;

class Player
{
    Character &_character;
    FightModule &_fight_module;
    sf::Clock _animation_clock;
    sf::Clock _gravity_clock;
    int _hp_percents = 100;

    float _y_speed = 0;
    int _current_frame_ = 0;
    bool _is_falling = true;
    bool _can_move_left = true;
    bool _can_move_right = true;
    bool _is_running_left = false;
    bool _is_player_B = false;
    bool _animation_loop_playing = false;
    CharacterFightSprite *_active_sprite = nullptr;
    const std::vector<sf::IntRect> *_active_sprite_frames = nullptr;

    void check_ground();
    void check_edges();
    void handle_falling();
    bool is_in_contact_with_opponent(int test_pos_x, int test_pos_y, bool unlock_x_on_opponent) const;
    void mirror_sprite(bool is_mirrored);

public:
    float _pos_x, _pos_y;

    Player(FightModule &fight_module, Character &character, const int &init_pos_x, const int &init_pos_y, const bool is_right_character);
    ~Player() = default;
    void handle_fps_signal();
    void move_left();
    void move_right();
    void jump();
    void hand_kick();
    void leg_kick();
    void block_kick();
    void reset_animation();
    void animate();
    void select_sprite(const sf::Texture &texture, const std::vector<sf::IntRect> &active_sprite_frames);
};