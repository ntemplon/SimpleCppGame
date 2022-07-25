#pragma once

#include <SFML/Graphics.hpp>

class Screen
{
public:
    Screen(sf::RenderWindow &window);
    virtual ~Screen() {}
    virtual void render() const = 0;
    sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow &_window;
};

class SplashScreen : public Screen
{
public:
    SplashScreen(sf::RenderWindow &window, std::string imagePath);
    virtual ~SplashScreen() {}
    void render() const;

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};