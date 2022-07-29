#pragma once

#include <Screen.hpp>
#include <SFML/Graphics.hpp>
#include <list>

class MainMenuScreen : public Screen
{
public:
    enum class MenuResult
    {
        Play,
        Exit,
        Nothing
    };

    struct MenuItem
    {
    public:
        sf::Rect<int> rect;
        MenuResult action;
    };

    MainMenuScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string backgroundImage);
    virtual ~MainMenuScreen(){};
    virtual void render() const;
    virtual MenuResult getCurrentResult();
    virtual void handleClick(int x, int y);

private:
    MenuResult _currentResult;
    void setCurrentResult(MenuResult result);

    std::list<MenuItem> _menuItems;
    sf::Texture _texture;
    sf::Sprite _sprite;
};