#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Timers
{
public:
    using TimerId = std::uint64_t;
    using Callback = std::function<void()>;

    Timers();

    TimerId add_timer(float duration_sec, Callback callback = nullptr);
    bool remove_timer(TimerId id);

    bool start(TimerId id);
    bool stop(TimerId id);
    bool pause(TimerId id);
    bool resume(TimerId id);
    bool reset(TimerId id);
    bool restart(TimerId id);

    bool set_duration(TimerId id, float duration_sec);
    bool set_callback(TimerId id, Callback callback);

    bool is_running(TimerId id) const;
    bool is_finished(TimerId id) const;
    bool exists(TimerId id) const;

    float get_elapsed_seconds(TimerId id) const;
    float get_remaining_seconds(TimerId id) const;

    void clear();
    void tick();

private:
    struct TimerEntry
    {
        TimerId id = 0;
        float duration_sec = 0.f;
        Callback callback = nullptr;

        sf::Clock clock;
        float elapsed_before_pause = 0.f;

        bool is_running = false;
        bool is_finished = false;
        bool callback_called = false;
    };

    std::vector<TimerEntry> _timers;
    TimerId _next_id = 1;

    TimerEntry *find_timer(TimerId id);
    const TimerEntry *find_timer_const(TimerId id) const;
};