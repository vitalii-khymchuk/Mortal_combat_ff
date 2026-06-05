#include <SFML/Audio.hpp>

class Sounds
{
public:
    sf::Music bg_music;

    sf::SoundBuffer hand_kick_buffer;
    sf::SoundBuffer leg_kick_buffer;
    sf::SoundBuffer start_round_buffer;
    sf::SoundBuffer finish_him_buffer;

    sf::Sound hand_kick_sound;
    sf::Sound leg_kick_sound;
    sf::Sound start_round_sound;
    sf::Sound finish_him_sound;

    Sounds();
    ~Sounds() = default;
};