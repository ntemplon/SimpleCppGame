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

    virtual void handleClick(int x, int y) = 0;

protected:
    /**
     * @brief Get the window to render to as a subclass
     */
    sf::RenderWindow &getWindow() const;

private:
    sf::RenderWindow &_window;
};