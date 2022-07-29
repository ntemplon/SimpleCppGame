#pragma once

#include <Screen.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include <functional>

class MainMenuScreen : public Screen
{
public:
    struct MenuItem
    {
    public:
        sf::Rect<int> rect;
        std::function<void()> action;
    };

    static const std::string MAIN_MENU_PLAY;
    static const std::string MAIN_MENU_EXIT;

    MainMenuScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string backgroundImage);
    virtual ~MainMenuScreen(){};
    virtual void render() const;
    virtual void handleClick(int x, int y);

private:
    std::list<MenuItem> _menuItems;
    sf::Texture _texture;
    sf::Sprite _sprite;
};