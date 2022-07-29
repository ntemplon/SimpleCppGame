#pragma once

#include <SFML/Graphics.hpp>

#include <Dispatcher.hpp>

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
    Screen(sf::RenderWindow &window, Dispatcher &dispatcher);

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

    /**
     * @brief Handle a click event at the specified screen coordinates.
     *
     * @param x The screen x coordinate of the click.
     * @param y The screen y coordinate of the click
     */
    virtual void handleClick(int x, int y) = 0;

protected:
    /**
     * @brief Get the window to render to as a subclass
     */
    sf::RenderWindow &getWindow() const;
    Dispatcher &getDispatcher() const;

private:
    sf::RenderWindow &_window;
    Dispatcher &_dispatcher;
};