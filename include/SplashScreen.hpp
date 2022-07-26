#pragma once

#include <Screen.hpp>

/**
 * @brief A screen that displays an image.
 *
 */
class SplashScreen : public Screen
{
public:
    /**
     * @brief A std::string for the event type of events that represent the user choosing to continue from the splash screen to the main game.
     */
    const static std::string SPLASH_SCREEN_CLOSE;

    /**
     * @brief Construct a new Splash Screen object
     *
     * @param window The window on which to render the splash screen.
     * @param dispatcher The Dispatcher on which the event to progress past the splash screen will be dispatched.
     * @param imagePath The path to the image to render as part of the splash screen.
     */
    SplashScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string imagePath);

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

    /**
     * @brief Handles a click on the splash screen, moving the game forward to the main menu.
     *
     * @param x The screen x position of the click.
     * @param y The screen y position of the click.
     */
    virtual void handleClick(int x, int y);

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};