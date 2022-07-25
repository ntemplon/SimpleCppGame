#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief A game screen
 *
 */
class Screen
{
public:
    /**
     * @brief Construct a new Screen object
     *
     * @param window The window to which the screen will render.
     */
    Screen(sf::RenderWindow &window);

    /**
     * @brief Destroy the Screen object
     *
     */
    virtual ~Screen() {}

    /**
     * @brief Renders the screen.
     *
     * Renders the screen to the window provided at construction
     *
     */
    virtual void render() const = 0;

protected:
    /**
     * @brief Get the window to render to as a subclass
     */
    sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow &_window;
};

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
    void render() const;

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};