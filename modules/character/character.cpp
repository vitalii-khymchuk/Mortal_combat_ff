#include "character.h"

Character::Character(std::string name,
                     const sf::Texture &avatar,
                     int x_speed_max,
                     float size_scale,
                     const sf::Texture walk_texture,
                     std::vector<sf::IntRect> walk_texture_frames,
                     const sf::Texture hand_kick_texture,
                     std::vector<sf::IntRect> hand_kick_texture_frames)
    : _name(name),
      _avatar(avatar),
      _walk_texture(walk_texture),
      _hand_kick_texture(hand_kick_texture),
      _walk_texture_frames(walk_texture_frames),
      _hand_kick_texture_frames(hand_kick_texture_frames),
      _x_speed_max(x_speed_max),
      _size_scale(size_scale) {};
Character::Character() : _name(""), _avatar(sf::Texture()), _walk_texture(sf::Texture()), _hand_kick_texture(sf::Texture()) {};
