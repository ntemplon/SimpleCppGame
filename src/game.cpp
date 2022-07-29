
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenuScreen.hpp>

#include <iostream>

Game::Game() : _gameState(Game::GameState::Uninitialized)
{
    _dispatcher = std::make_unique<Dispatcher>();
}

void Game::start()
{
    // We can only start if we haven't already started
    if (_gameState != Game::GameState::Uninitialized)
    {
        return;
    }

    // ============== Block - assign event listeners ==========================
    // Close the splash screen when it's clicked
    _dispatcher->subscribe(SplashScreen::SPLASH_SCREEN_CLOSE, [&](Event event)
                           { _gameState = Game::GameState::ClosingSplash; });

    // Close the game if "Exit" on the main menu screen is selected
    _dispatcher->subscribe(MainMenuScreen::MAIN_MENU_EXIT, [&](Event event)
                           { _gameState = Game::GameState::Exiting; });
    // =========================================================================

    // For simplicity and learning's sake, make a 1024x768 game with 32-bit color
    _mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");

    // Initialize the game - we are showing the splash screen at the start
    _gameState = Game::GameState::ShowingSplash;
    _currentScreen.reset(new SplashScreen(_mainWindow, *_dispatcher, "./res/splash.png"));

    // Loop until we exit.
    // TODO - control to constrain this loop to 60fps
    while (!isExiting())
    {
        gameLoop();
    }

    // When we're done with the game, close our window and let it all go out of scope
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
    // Do anything specific to the current state. Right now, this is basic, but more will happen later
    switch (_gameState)
    {
    case Game::GameState::ClosingSplash:
    {
        _gameState = Game::GameState::Playing;
        _currentScreen.reset(new MainMenuScreen(_mainWindow, *_dispatcher, "./res/mainmenu.png"));
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

    // Poll through all events that have happened this frame
    while (_mainWindow.pollEvent(currentEvent))
    {
        if (currentEvent.type == sf::Event::Closed)
        {
            // If the window is closed, exit the game
            _gameState = Game::GameState::Exiting;
        }
        else if (currentEvent.type == sf::Event::MouseButtonPressed && _currentScreen)
        {
            // Pass mouse button events on to the current screen
            _currentScreen->handleClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y);
        }
    }
}

bool Game::shouldRenderInState(Game::GameState state)
{
    // I'd prefer this to be a property of the GameState type itself, but given enumerations can't have methods in C++, this is what I'm doing until
    // I figure out how to idiomatically do this.
    return Game::GameState::ShowingSplash == state ||
           Game::GameState::ClosingSplash == state ||
           Game::GameState::Paused == state ||
           Game::GameState::ShowingMenu == state ||
           Game::GameState::Playing == state;
}