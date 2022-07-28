#pragma once

#include <Screen.hpp>
#include <SFML/Graphics.hpp>

class MainMenuScreen : public Screen
{
public:
    MainMenuScreen(sf::RenderWindow &window);
    virtual ~MainMenuScreen(){};
    virtual void render() const;
};