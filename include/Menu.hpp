#pragma once

#include <vector>
#include <string>

class Menu
{
public:
    Menu(const std::vector<std::string> menuItems);
    Menu();

    const std::vector<std::string> &getMenuItems() const;

private:
    const std::vector<std::string> _menuItems;
};