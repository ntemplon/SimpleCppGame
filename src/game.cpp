
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenuScreen.hpp>
#include <GameScreen.hpp>
#include <EntityEngine.hpp>
#include <Components.hpp>

#include <iostream>

const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);
const int Game::WORLD_WIDTH = 1024;
const int Game::WORLD_HEIGHT = 768;
const int Game::WORLD_BORDER = 20;

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

    // Play the game if "Play" on the main menu screen is selected
    _dispatcher->subscribe(MainMenuScreen::MAIN_MENU_PLAY, [&](Event event)
                           { _gameState = Game::GameState::PlayRequested; });

    // Close the game if "Exit" on the main menu screen is selected
    _dispatcher->subscribe(MainMenuScreen::MAIN_MENU_EXIT, [&](Event event)
                           { _gameState = Game::GameState::Exiting; });
    // =========================================================================

    // ================ Block - Component Entity System ========================
    _engine = std::make_unique<EntityEngine>();

    _input = std::make_shared<PlayerInputSystem>();
    _engine->add(this->_input);

    _velocity = std::make_shared<VelocitySystem>();
    _engine->add(this->_velocity);

    _render = std::make_shared<RenderSystem>();
    _engine->add(this->_render);

    auto player = createPlayer();
    _engine->add(player);
    // =========================================================================

    // For simplicity and learning's sake, make a fixed-size game
    _mainWindow.create(sf::VideoMode(WORLD_WIDTH, WORLD_HEIGHT), "Simple Cpp Game");
    _view = _mainWindow.getDefaultView();

    // Initialize the game - we are showing the splash screen at the start
    _gameState = Game::GameState::ShowingSplash;
    _currentScreen = std::make_unique<SplashScreen>(_mainWindow, *_dispatcher, "./res/splash.png");

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
        _gameState = Game::GameState::ShowingMenu;
        _currentScreen = std::make_unique<MainMenuScreen>(_mainWindow, *_dispatcher, "./res/mainmenu.png");
        break;
    }
    case Game::GameState::PlayRequested:
    {
        _gameState = Game::GameState::Playing;
        _currentScreen = std::make_unique<GameScreen>(_mainWindow, *_dispatcher, *_render);
        break;
    }
    }

    this->handleInput();
    this->update(deltaTime);

    // Lastly, render if we have a valid screen
    if (_currentScreen)
    {
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
    switch (_gameState)
    {
    case Game::GameState::Playing:
        this->_engine->update(deltaTime);
        break;
    }
}

bool Game::shouldRenderInState(const Game::GameState state) const
{
    // I'd prefer this to be a property of the GameState type itself, but given enumerations can't have methods in C++, this is what I'm doing until
    // I figure out how to idiomatically do this.
    return Game::GameState::ShowingSplash == state ||
           Game::GameState::ClosingSplash == state ||
           Game::GameState::Paused == state ||
           Game::GameState::ShowingMenu == state ||
           Game::GameState::PlayRequested == state ||
           Game::GameState::Playing == state;
}

void Game::modifyView(const std::function<sf::View(sf::View)> op)
{
    this->_view = op(this->_view);
    this->_mainWindow.setView(this->_view);
}

std::shared_ptr<Entity> Game::createPlayer()
{
    auto player = std::make_shared<Entity>();

    auto render = std::make_shared<RenderComponent>();
    render->texture->loadFromFile("./res/paddle.png");
    render->sprite = sf::Sprite(*(render->texture));

    auto location = std::make_shared<LocationComponent>();
    location->location.left = WORLD_BORDER;
    location->location.top = 309; // World middle
    location->location.height = 150;
    location->location.width = 15;

    auto velocity = std::make_shared<VelocityComponent>();

    auto playerMarker = std::make_shared<PlayerComponent>();

    player->add(std::move(render));
    player->add(std::move(location));
    player->add(std::move(velocity));
    player->add(std::move(playerMarker));

    return std::move(player);
}