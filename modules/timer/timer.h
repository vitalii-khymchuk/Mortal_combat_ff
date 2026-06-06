#pragma once

#include <functional>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Timer
{
public:
    explicit Timer(float duration_sec = 0.f, std::function<void()> callback = nullptr);

    void set_duration(float duration_sec);
    void set_callback(std::function<void()> callback);

    void start();
    void stop();
    void pause();
    void resume();
    void reset();
    void restart();

    void tick();

    bool is_running() const;
    bool is_finished() const;

    float get_duration() const;
    float get_elapsed_seconds() const;
    float get_remaining_seconds() const;

private:
    float _duration_sec = 0.f;
    std::function<void()> _callback = nullptr;

    sf::Clock _clock;
    float _elapsed_before_pause = 0.f;

    bool _is_running = false;
    bool _is_finished = false;
    bool _callback_called = false;
};