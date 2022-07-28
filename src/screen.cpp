#include <SFML/Graphics.hpp>

#include <Screen.hpp>

Screen::Screen(sf::RenderWindow &window) : _window(window)
{
}

sf::RenderWindow &Screen::getWindow() const
{
    return _window;
}