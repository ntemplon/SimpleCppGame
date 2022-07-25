#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Screen.hpp>

/**
 * @brief A simple C++ game that shamelessly rips off Pong.
 *
 */
class Game
{
public:
    /**
     * @brief Construct a new Game object
     *
     */
    Game();
    /**
     * @brief Starts the game.
     *
     */
    void start();

private:
    bool isExiting();
    void gameLoop();

    enum class GameState
    {
        Uninitialized,
        ShowingSplash,
        Paused,
        ShowingMenu,
        Playing,
        Exiting
    };

    GameState _gameState;
    sf::RenderWindow _mainWindow;
    std::unique_ptr<Screen> _currentScreen;
};