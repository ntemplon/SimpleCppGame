#include <Menu.hpp>

Menu::Menu(const std::vector<const std::string> menuItems) : _menuItems(menuItems)
{
}

Menu::Menu() : Menu(std::vector<const std::string>())
{
}

const std::vector<const std::string> &Menu::getMenuItems() const
{
    return this->_menuItems;
}