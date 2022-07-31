
#include <SplashScreen.hpp>

const std::string SplashScreen::SPLASH_SCREEN_CLOSE = "SPLASH_SCREEN_CLOSE";

SplashScreen::SplashScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string imagePath) : Screen(window, dispatcher)
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
    Event event(SPLASH_SCREEN_CLOSE); // Why is this separate declaration needed?
    this->getDispatcher().dispatch(event);
}