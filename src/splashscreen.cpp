#include <SFML/Graphics.hpp>

#include <SplashScreen.hpp>
#include <iostream>

SplashScreen::SplashScreen(sf::RenderWindow &window, std::string imagePath) : Screen(window)
{
    if (true == _texture.loadFromFile(imagePath))
    {
        // Loading has succeeded
        _sprite = sf::Sprite(_texture);
    }
}

void SplashScreen::render() const
{
    this->getWindow().draw(_sprite);
    this->getWindow().display();
}

void SplashScreen::handleClick(int x, int y)
{
    // Intentional no-op
}