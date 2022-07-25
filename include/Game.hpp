#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Screen.hpp>

class Game
{
public:
    Game();
    void start();

private:
    bool isExiting();
    void gameLoop();

    enum GameState
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