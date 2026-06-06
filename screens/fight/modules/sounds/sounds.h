#include <SFML/Audio.hpp>

class Sounds
{
    sf::Music bg_music;

    sf::SoundBuffer hand_kick_buffer;
    sf::SoundBuffer leg_kick_buffer;
    sf::SoundBuffer air_kick_buffer;
    sf::SoundBuffer round_one_buffer;
    sf::SoundBuffer round_two_buffer;
    sf::SoundBuffer round_three_buffer;
    sf::SoundBuffer finish_him_buffer;

    sf::Sound hand_kick_sound = sf::Sound(hand_kick_buffer);
    sf::Sound air_kick_sound = sf::Sound(air_kick_buffer);
    sf::Sound leg_kick_sound = sf::Sound(leg_kick_buffer);
    sf::Sound round_one_sound = sf::Sound(round_one_buffer);
    sf::Sound round_two_sound = sf::Sound(round_two_buffer);
    sf::Sound round_three_sound = sf::Sound(round_three_buffer);
    sf::Sound finish_him_sound = sf::Sound(finish_him_buffer);

public:
    void play_hand_kick_sound();
    void play_leg_kick_sound();
    void play_air_kick_sound();
    void play_finish_him_sound();
    void play_round_sound(int round);
    void play_bg_music();

    Sounds();
    ~Sounds() = default;
};