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
     * @brief The amount of time the game should spend on each frame. This is equal to 1 / framerate.
     */
    const static sf::Time TIME_PER_FRAME;

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

    bool isExiting() const;
    void gameLoop(const sf::Time deltaTime);
    void handleInput();
    void update(const sf::Time detlaTime);
    bool shouldRenderInState(const Game::GameState state) const;
    void modifyView(const std::function<sf::View(sf::View)> op);

    GameState _gameState;
    sf::RenderWindow _mainWindow;
    sf::View _view;
    std::unique_ptr<Screen> _currentScreen;
    std::unique_ptr<Dispatcher> _dispatcher;
};