
#include <Screen.hpp>

#include <SFML/Graphics.hpp>

Screen::Screen(sf::RenderWindow &window, Dispatcher &dispatcher) : _window(window), _dispatcher(dispatcher)
{
}

sf::RenderWindow &Screen::getWindow() const
{
    return _window;
}

Dispatcher &Screen::getDispatcher() const
{
    return this->_dispatcher;
}