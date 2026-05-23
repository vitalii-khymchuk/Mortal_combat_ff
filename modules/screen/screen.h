#include <SFML/Graphics.hpp>
class Screen
{
public:
    Screen() {};
    virtual ~Screen() = default;
    virtual void handle_frame_signal() {};
    virtual void handle_event(const sf::Event &event) {};
};