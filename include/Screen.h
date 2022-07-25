#include <SFML/Graphics.hpp>

class Screen
{
public:
    Screen(sf::RenderWindow &window) : _window(window)
    {
    }
    virtual ~Screen() {}
    virtual void render() = 0;

private:
    sf::RenderWindow &_window;
};