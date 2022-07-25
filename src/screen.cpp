#include <SFML/Graphics.hpp>

#include <Screen.hpp>

Screen::Screen(sf::RenderWindow &window) : _window(window)
{
}

sf::RenderWindow &Screen::getWindow() const
{
    return _window;
}

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