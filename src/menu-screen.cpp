#include <MenuScreen.hpp>

MenuScreen::MenuScreen(sf::RenderWindow &window, Dispatcher &dispatcher, Menu menu) : Screen(window, dispatcher), _menu(menu)
{
}

const Menu &MenuScreen::getMenu() const
{
    return this->_menu;
}

void MenuScreen::render() const
{
}

void MenuScreen::handleClick(int x, int y)
{
}