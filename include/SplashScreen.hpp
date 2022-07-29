#pragma once

#include <Screen.hpp>
#include <SFML/Graphics.hpp>

/**
 * @brief A screen that displays an image.
 *
 */
class SplashScreen : public Screen
{
public:
    /**
     * @brief Construct a new Splash Screen object
     *
     * @param window The window on which to render the splash screen.
     * @param imagePath The path to the image to render as part of the splash screen.
     */
    SplashScreen(sf::RenderWindow &window, std::string imagePath);

    /**
     * @brief Destroy the Splash Screen object
     *
     */
    virtual ~SplashScreen() {}

    /**
     * @brief Renders the splash screen.
     *
     * Renders the splash screen to the window provided during construction.
     *
     */
    virtual void render() const;

    virtual void handleClick(int x, int y);

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};