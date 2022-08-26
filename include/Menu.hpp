#pragma once

#include <vector>
#include <string>

class Menu
{
public:
    Menu(const std::vector<const std::string> menuItems);
    Menu();

    const std::vector<const std::string> &getMenuItems() const;

private:
    const std::vector<const std::string> _menuItems;
};