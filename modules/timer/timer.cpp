#include "timer.h"

Timer::Timer(float duration_sec, std::function<void()> callback)
    : _duration_sec(duration_sec), _callback(std::move(callback))
{
}

void Timer::set_duration(float duration_sec)
{
    _duration_sec = duration_sec;
}

void Timer::set_callback(std::function<void()> callback)
{
    _callback = std::move(callback);
}

void Timer::start()
{
    _elapsed_before_pause = 0.f;
    _clock.restart();
    _is_running = true;
    _is_finished = false;
    _callback_called = false;
}

void Timer::stop()
{
    _is_running = false;
}

void Timer::pause()
{
    if (!_is_running)
        return;

    _elapsed_before_pause += _clock.getElapsedTime().asSeconds();
    _is_running = false;
}

void Timer::resume()
{
    if (_is_running || _is_finished)
        return;

    _clock.restart();
    _is_running = true;
}

void Timer::reset()
{
    _clock.restart();
    _elapsed_before_pause = 0.f;
    _is_running = false;
    _is_finished = false;
    _callback_called = false;
}

void Timer::restart()
{
    start();
}

void Timer::tick()
{
    if (!_is_running || _is_finished)
        return;

    float elapsed = _elapsed_before_pause + _clock.getElapsedTime().asSeconds();

    if (elapsed >= _duration_sec)
    {
        _is_running = false;
        _is_finished = true;

        if (!_callback_called && _callback)
        {
            _callback_called = true;
            _callback();
        }
    }
}

bool Timer::is_running() const
{
    return _is_running;
}

bool Timer::is_finished() const
{
    return _is_finished;
}

float Timer::get_duration() const
{
    return _duration_sec;
}

float Timer::get_elapsed_seconds() const
{
    if (_is_running)
        return _elapsed_before_pause + _clock.getElapsedTime().asSeconds();

    return _elapsed_before_pause;
}

float Timer::get_remaining_seconds() const
{
    float remaining = _duration_sec - get_elapsed_seconds();
    return remaining > 0.f ? remaining : 0.f;
}