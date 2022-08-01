#pragma once

#include <Screen.hpp>
#include <RenderSystem.hpp>

#include <memory>

/**
 * @brief The Screen that handles drawing the game during primary gameplay.
 */
class GameScreen : public Screen
{
public:
    /**
     * @brief Construct a new GameScreen
     *
     * @param window The window to which the GameScreen will draw the game.
     * @param dispatcher The Dispatcher on which the GameScreen will dispatch and receive events.
     * @param renderSystem The RenderSystem that will handle rendering the Entity game objects.
     */
    GameScreen(sf::RenderWindow &window, Dispatcher &dispatcher, RenderSystem &renderSystem);

    /**
     * @brief Renders the game with the parameters provided in the constructor.
     */
    void render() const;

    /**
     * @brief Override of Screen virtual method. No-op.
     */
    void handleClick(int x, int y);

private:
    /**
     * @brief The RenderSystem that will draw the EntityEngine Entity objects
     */
    RenderSystem &_renderSystem;

    /**
     * @brief A rectangle to represent the play surface
     */
    sf::RectangleShape _gameWindow;
};