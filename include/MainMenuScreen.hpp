#pragma once

#include <Screen.hpp>

#include <SFML/Graphics.hpp>

#include <list>
#include <string>
#include <functional>

/**
 * @brief A screen representing the main menu of our game
 *
 */
class MainMenuScreen : public Screen
{
public:
    /**
     * @brief A data structure of a menu item.
     */
    struct MenuItem
    {
    public:
        /** The bounds of the menu item, in screenspace coordinates. Used for determining if the item has been clicked. */
        sf::Rect<int> rect;
        /** The action that will be performed when the item is clicked. */
        std::function<void()> action;
    };

    /**
     * @brief A std::string for the event type of events that represent the user choosing to play the game.
     */
    static const std::string MAIN_MENU_PLAY;

    /**
     * @brief A std::string for the event type of events that represent the user choosing to exit the game.
     */
    static const std::string MAIN_MENU_EXIT;

    /**
     * @brief Construct a new Main Menu Screen object
     *
     * @param window The sf::RenderWindow to which this menu will be rendered.
     * @param dispatcher The Dispatcher on which the events for user selection will be dispatched.
     * @param backgroundImage The file path to the image to use as the background of the menu.
     */
    MainMenuScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string backgroundImage);

    /**
     * @brief Renders the MainMenuScreen to the sf::RenderWindow provided during construction
     */
    virtual void render() const;

    /**
     * @brief Performs event handling for a user mouse click, dispatching events if appropriate.
     *
     * @param x The x position of the click, in screen space coordinates.
     * @param y The y position of the click, in screen space coordinates.
     */
    virtual void handleClick(int x, int y);

private:
    std::list<MenuItem> _menuItems;
    sf::Texture _texture;
    sf::Sprite _sprite;
};