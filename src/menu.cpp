#include <Menu.hpp>

Menu::Menu(const std::vector<std::string> menuItems) : _menuItems(menuItems)
{
}

Menu::Menu() : Menu(std::vector<std::string>())
{
}

const std::vector<std::string> &Menu::getMenuItems() const
{
    return this->_menuItems;
}