#pragma once

#include <Screen.hpp>

/**
 * @brief A Screen that handles informing the user they have won or lost the game
 */
class GameOverScreen : public Screen
{
public:
    /**
     * @brief The ID for an Event that signals the player has accepted their inevitable demise. Or are celebrating. But probably the demise.
     */
    static const std::string GAME_OVER_ACK;

    /**
     * @brief Construct a new GameOverScreen
     *
     * @param window The screen on which to display the game has ended.
     * @param dispatcher The Dispatcher to send Event signals on, such as GameOverScreen::GAME_OVER_ACK.
     * @param imagePath The path to the image to show on the screen, relative to the executable working directory.
     */
    GameOverScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string imagePath);

    /**
     * @brief Renders the screen with the parameters provided in the constructor.
     */
    void render() const;

    /**
     * @brief Handles a click by sending out a GameOverScreen::GAME_OVER_ACK Event.
     */
    void handleClick(int x, int y);

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};