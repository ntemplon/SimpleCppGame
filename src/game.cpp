
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenuScreen.hpp>
#include <EntityEngine.hpp>
#include <RenderSystem.hpp>

#include <iostream>

const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

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

    // ================ Block - Component Entity System ========================
    auto engine = std::make_unique<EntityEngine>();
    auto renderSystem = std::make_shared<RenderSystem>();
    // =========================================================================

    // For simplicity and learning's sake, make a 1024x768 game
    _mainWindow.create(sf::VideoMode(1024, 768), "Simple Cpp Game");
    _view = _mainWindow.getDefaultView();

    // Initialize the game - we are showing the splash screen at the start
    _gameState = Game::GameState::ShowingSplash;
    _currentScreen.reset(new SplashScreen(_mainWindow, *_dispatcher, "./res/splash.png"));

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // Loop until we exit.
    while (!isExiting())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            gameLoop(TIME_PER_FRAME);
        }
    }

    // When we're done with the game, close our window and let it all go out of scope
    _mainWindow.close();
}

Dispatcher *Game::getDispatcher()
{
    return this->_dispatcher.get();
}

bool Game::isExiting() const
{
    return Game::GameState::Exiting == _gameState;
}

void Game::gameLoop(const sf::Time deltaTime)
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
    this->update(deltaTime);

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
        switch (currentEvent.type)
        {
        case sf::Event::Resized:
            this->modifyView([&](sf::View view)
                             {
                                view.setSize(currentEvent.size.width, currentEvent.size.height); 
                                return view; });
            break;
        case sf::Event::Closed:
            // If the window is closed, exit the game
            _gameState = Game::GameState::Exiting;
            break;
        case sf::Event::MouseButtonPressed:
            if (_currentScreen)
            {
                // Pass mouse button events on to the current screen
                _currentScreen->handleClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y);
            }
            break;
        }
    }
}

void Game::update(const sf::Time deltaTime)
{
}

bool Game::shouldRenderInState(const Game::GameState state) const
{
    // I'd prefer this to be a property of the GameState type itself, but given enumerations can't have methods in C++, this is what I'm doing until
    // I figure out how to idiomatically do this.
    return Game::GameState::ShowingSplash == state ||
           Game::GameState::ClosingSplash == state ||
           Game::GameState::Paused == state ||
           Game::GameState::ShowingMenu == state ||
           Game::GameState::Playing == state;
}

void Game::modifyView(const std::function<sf::View(sf::View)> op)
{
    this->_view = op(this->_view);
    this->_mainWindow.setView(this->_view);
}