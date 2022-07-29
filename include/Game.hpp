#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Screen.hpp>
#include <Dispatcher.hpp>

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

    /**
     * @brief Get the Dispatcher object that controls event dispatch for the game.
     *
     * Get the Dispatcher object that controls event dispatch for the game. The object is owned by the game and its
     * lifetime will be exactly the same as the game's.
     *
     * @return A pointer to the game's event dispatcher bus
     */
    Dispatcher *getDispatcher();

private:
    bool isExiting();
    void gameLoop();

    enum class GameState
    {
        Uninitialized,
        ShowingSplash,
        ClosingSplash,
        Paused,
        ShowingMenu,
        Playing,
        Exiting
    };

    GameState _gameState;
    sf::RenderWindow _mainWindow;
    std::unique_ptr<Screen> _currentScreen;
    std::unique_ptr<Dispatcher> _dispatcher;
};