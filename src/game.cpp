
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Game.hpp>

#include <iostream>

Game::Game()
{
    _gameState = Game::GameState::Uninitialized;
    // _mainWindow initializes just from being declared
}

void Game::start()
{
    if (_gameState != Game::GameState::Uninitialized)
    {
        return;
    }

    _mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
    _gameState = Game::GameState::Playing;
    _currentScreen.reset(new SplashScreen(_mainWindow, "../res/splash.png"));

    while (!isExiting())
    {
        gameLoop();
    }

    _mainWindow.close();
}

bool Game::isExiting()
{
    if (_gameState == Game::GameState::Exiting)
        return true;
    else
        return false;
}

void Game::gameLoop()
{
    sf::Event currentEvent;
    while (_mainWindow.pollEvent(currentEvent))
    {

        switch (_gameState)
        {
        case Game::GameState::Playing:
        {
            _mainWindow.clear(sf::Color(255, 0, 0));
            _currentScreen->render();
            _mainWindow.display();

            if (currentEvent.type == sf::Event::Closed)
            {
                _gameState = Game::GameState::Exiting;
            }
            break;
        }
        }
    }
}