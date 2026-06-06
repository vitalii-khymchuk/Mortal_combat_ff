#include "sounds.h"
#include <iostream>

Sounds::Sounds()
{
    if (!bg_music.openFromFile("screens/fight/assets/fight_theme.mp3"))
        std::cout << "Failed to load fight_theme.mp3\n";

    if (!hand_kick_buffer.loadFromFile("screens/fight/assets/kick1.wav"))
        std::cout << "Failed to load kick1.mp3\n";

    if (!leg_kick_buffer.loadFromFile("screens/fight/assets/kick2.wav"))
        std::cout << "Failed to load kick2.mp3\n";

    if (!air_kick_buffer.loadFromFile("screens/fight/assets/air_kick.wav"))
        std::cout << "Failed to load kick2.mp3\n";

    if (!round_one_buffer.loadFromFile("screens/fight/assets/round1.wav"))
        std::cout << "Failed to load round1.mp3\n";

    if (!round_two_buffer.loadFromFile("screens/fight/assets/round2.wav"))
        std::cout << "Failed to load round2.mp3\n";

    if (!round_three_buffer.loadFromFile("screens/fight/assets/round3.wav"))
        std::cout << "Failed to load round3.mp3\n";

    if (!finish_him_buffer.loadFromFile("screens/fight/assets/finish_him.wav"))
        std::cout << "Failed to load finish_him.mp3\n";

    bg_music.setVolume(80.f);

    hand_kick_sound.setBuffer(hand_kick_buffer);
    leg_kick_sound.setBuffer(leg_kick_buffer);
    air_kick_sound.setBuffer(air_kick_buffer);
    round_one_sound.setBuffer(round_one_buffer);
    round_two_sound.setBuffer(round_two_buffer);
    round_three_sound.setBuffer(round_three_buffer);
    finish_him_sound.setBuffer(finish_him_buffer);
}

void Sounds::play_bg_music()
{
    bg_music.setLooping(true);
    bg_music.play();
}

void Sounds::play_hand_kick_sound()
{
    hand_kick_sound.play();
}

void Sounds::play_leg_kick_sound()
{
    leg_kick_sound.play();
}

void Sounds::play_air_kick_sound()
{
    air_kick_sound.play();
}

void Sounds::play_finish_him_sound()
{
    finish_him_sound.play();
}

void Sounds::play_round_sound(int round)
{
    if (round == 1)
    {
        round_one_sound.play();
    };
    if (round == 2)
    {
        round_two_sound.play();
    };
    if (round == 3)
    {
        round_three_sound.play();
    };
}