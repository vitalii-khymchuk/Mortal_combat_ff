class Screen
{
public:
    Screen() {};
    virtual ~Screen() = default;
    virtual void handle_frame_signal() = 0;
};