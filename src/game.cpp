
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Game.h>

#include <iostream>

Game::Game()
{
    _gameState = Uninitialized;
    // _mainWindow initializes just from being declared
}

void Game::start()
{
    if (_gameState != Game::Uninitialized)
    {
        return;
    }

    _mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
    _gameState = Game::Playing;

    while (!isExiting())
    {
        gameLoop();
    }

    _mainWindow.close();
}

bool Game::isExiting()
{
    if (_gameState == Game::Exiting)
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
        case Game::Playing:
        {
            _mainWindow.clear(sf::Color(255, 0, 0));
            _mainWindow.display();

            if (currentEvent.type == sf::Event::Closed)
            {
                _gameState = Game::Exiting;
            }
            break;
        }
        }
    }
}