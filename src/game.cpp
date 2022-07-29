
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenuScreen.hpp>

#include <iostream>

Game::Game()
{
    _gameState = Game::GameState::Uninitialized;
    _dispatcher.reset(new Dispatcher());
    // _mainWindow initializes just from being declared
}

void Game::start()
{
    if (_gameState != Game::GameState::Uninitialized)
    {
        return;
    }

    // Block - assign event listeners
    _dispatcher->subscribe(SplashScreen::SPLASH_SCREEN_CLOSE, [&](Event event)
                           { _gameState = Game::GameState::ClosingSplash; });
    _dispatcher->subscribe(MainMenuScreen::MAIN_MENU_EXIT, [&](Event event)
                           { _gameState = Game::GameState::Exiting; });

    _mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");
    _gameState = Game::GameState::ShowingSplash;
    _currentScreen.reset(new SplashScreen(_mainWindow, *_dispatcher, "../res/splash.png"));

    while (!isExiting())
    {
        gameLoop();
    }

    _mainWindow.close();
}

Dispatcher *Game::getDispatcher()
{
    return this->_dispatcher.get();
}

bool Game::isExiting()
{
    return Game::GameState::Exiting == _gameState;
}

void Game::gameLoop()
{
    switch (_gameState)
    {
    case Game::GameState::ClosingSplash:
    {
        _gameState = Game::GameState::Playing;
        _currentScreen.reset(new MainMenuScreen(_mainWindow, *_dispatcher, "../res/mainmenu.png"));
        break;
    }
    case Game::GameState::ShowingSplash:
    {
        break;
    }
    case Game::GameState::Playing:
    {
        break;
    }
    }

    this->handleInput();

    // Lastly, render if we have a valid screen
    if (_currentScreen)
    {
        _mainWindow.clear(sf::Color(0, 0, 0));
        _currentScreen->render();
    }
}

void Game::handleInput()
{
    sf::Event currentEvent;
    while (_mainWindow.pollEvent(currentEvent))
    {
        if (currentEvent.type == sf::Event::Closed)
        {
            _gameState = Game::GameState::Exiting;
        }
        else if (currentEvent.type == sf::Event::MouseButtonPressed && _currentScreen)
        {
            _currentScreen->handleClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y);
        }
    }
}

bool Game::shouldRenderInState(Game::GameState state)
{
    return Game::GameState::ShowingSplash == state ||
           Game::GameState::ClosingSplash == state ||
           Game::GameState::Paused == state ||
           Game::GameState::ShowingMenu == state ||
           Game::GameState::Playing == state;
}