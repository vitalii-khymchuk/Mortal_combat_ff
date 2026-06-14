#include "timers.h"

#include <algorithm>
#include <utility>

Timers::Timers() = default;

Timers::TimerId Timers::add_timer(float duration_sec, Callback callback, bool is_self_removable)
{
    TimerEntry entry;
    entry.id = _next_id++;
    entry.duration_sec = duration_sec;
    entry.callback = std::move(callback);
    entry.is_self_removable = is_self_removable;

    _timers.push_back(std::move(entry));
    return _timers.back().id;
}

bool Timers::remove_timer(TimerId id)
{
    auto old_size = _timers.size();

    _timers.erase(
        std::remove_if(_timers.begin(), _timers.end(),
                       [id](const TimerEntry &timer)
                       {
                           return timer.id == id;
                       }),
        _timers.end());

    return _timers.size() != old_size;
}

bool Timers::start(TimerId id)
{
    TimerEntry *timer = find_timer(id);
    if (!timer)
        return false;

    timer->elapsed_before_pause = 0.f;
    timer->clock.restart();
    timer->is_running = true;
    timer->is_finished = false;
    timer->callback_called = false;
    return true;
}

bool Timers::stop(TimerId id)
{
    TimerEntry *timer = find_timer(id);
    if (!timer)
        return false;

    timer->is_running = false;
    return true;
}

bool Timers::pause(TimerId id)
{
    TimerEntry *timer = find_timer(id);
    if (!timer || !timer->is_running)
        return false;

    timer->elapsed_before_pause += timer->clock.getElapsedTime().asSeconds();
    timer->is_running = false;
    return true;
}

bool Timers::resume(TimerId id)
{
    TimerEntry *timer = find_timer(id);
    if (!timer || timer->is_running || timer->is_finished)
        return false;

    timer->clock.restart();
    timer->is_running = true;
    return true;
}

bool Timers::reset(TimerId id)
{
    TimerEntry *timer = find_timer(id);
    if (!timer)
        return false;

    timer->clock.restart();
    timer->elapsed_before_pause = 0.f;
    timer->is_running = false;
    timer->is_finished = false;
    timer->callback_called = false;
    return true;
}

bool Timers::restart(TimerId id)
{
    return start(id);
}

bool Timers::set_duration(TimerId id, float duration_sec)
{
    TimerEntry *timer = find_timer(id);
    if (!timer)
        return false;

    timer->duration_sec = duration_sec;
    return true;
}

bool Timers::set_callback(TimerId id, Callback callback)
{
    TimerEntry *timer = find_timer(id);
    if (!timer)
        return false;

    timer->callback = std::move(callback);
    return true;
}

bool Timers::is_running(TimerId id) const
{
    const TimerEntry *timer = find_timer_const(id);
    return timer ? timer->is_running : false;
}

bool Timers::is_finished(TimerId id) const
{
    const TimerEntry *timer = find_timer_const(id);
    return timer ? timer->is_finished : false;
}

bool Timers::exists(TimerId id) const
{
    return find_timer_const(id) != nullptr;
}

float Timers::get_elapsed_seconds(TimerId id) const
{
    const TimerEntry *timer = find_timer_const(id);
    if (!timer)
        return 0.f;

    if (timer->is_running)
        return timer->elapsed_before_pause + timer->clock.getElapsedTime().asSeconds();

    return timer->elapsed_before_pause;
}

float Timers::get_remaining_seconds(TimerId id) const
{
    const TimerEntry *timer = find_timer_const(id);
    if (!timer)
        return 0.f;

    float remaining = timer->duration_sec - get_elapsed_seconds(id);
    return remaining > 0.f ? remaining : 0.f;
}

void Timers::clear()
{
    _timers.clear();
}

void Timers::tick()
{
    for (auto &timer : _timers)
    {
        if (!timer.is_running || timer.is_finished)
            continue;

        float elapsed = timer.elapsed_before_pause + timer.clock.getElapsedTime().asSeconds();

        if (elapsed >= timer.duration_sec)
        {
            timer.is_running = false;
            timer.is_finished = true;

            if (!timer.callback_called && timer.callback)
            {
                timer.callback_called = true;
                timer.callback();
                if (timer.is_self_removable)
                {
                    remove_timer(timer.id);
                }
            }
        }
    }
}

Timers::TimerEntry *Timers::find_timer(TimerId id)
{
    for (auto &timer : _timers)
    {
        if (timer.id == id)
            return &timer;
    }

    return nullptr;
}

const Timers::TimerEntry *Timers::find_timer_const(TimerId id) const
{
    for (const auto &timer : _timers)
    {
        if (timer.id == id)
            return &timer;
    }

    return nullptr;
}