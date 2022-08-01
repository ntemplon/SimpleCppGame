
#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenuScreen.hpp>
#include <GameScreen.hpp>
#include <EntityEngine.hpp>
#include <Components.hpp>
#include <GameOverScreen.hpp>
#include <EnemyAISystem.hpp>

#include <random>
#include <ctime>
#include <math.h>

const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

Game::Game() : _gameState(Game::GameState::Uninitialized), _dispatcher(std::make_unique<Dispatcher>())
{
}

void Game::start()
{
    // We can only start if we haven't already started
    if (_gameState != Game::GameState::Uninitialized)
    {
        return;
    }

    // Seed the random number generator
    srand(time(NULL));

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

    // If the AI scores, we lose
    _dispatcher->subscribe(BallSystem::ENEMY_SCORE_EVENT, [&](Event event)
                           { _gameState = Game::GameState::Lost; });

    // If we accept our defeat, exit gracefully
    _dispatcher->subscribe(GameOverScreen::GAME_OVER_ACK, [&](Event event)
                           { _gameState = Game::GameState::Exiting; });

    // If we score, we win
    _dispatcher->subscribe(BallSystem::PLAYER_SCORE_EVENT, [&](Event event)
                           { _gameState = Game::GameState::Won; });
    // =========================================================================

    // ================ Block - Component Entity System ========================
    _engine = std::make_unique<EntityEngine>();

    // Declare the entities and systems we need, then stick them in the engine
    auto player = createPlayer();
    auto enemy = createEnemy();
    auto ball = createBall();

    _input = std::make_shared<PlayerInputSystem>();
    _engine->add(this->_input);

    _ballSystem = std::make_shared<BallSystem>(*_dispatcher, *player, *enemy);
    _engine->add(this->_ballSystem);

    _velocity = std::make_shared<VelocitySystem>();
    _engine->add(this->_velocity);

    _render = std::make_shared<RenderSystem>();
    _engine->add(this->_render);

    _engine->add(std::make_shared<EnemyAISystem>(*ball));

    _engine->add(player);
    _engine->add(enemy);
    _engine->add(ball);
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
        // Only run the game logic at the fixed rate of times per second
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            // Fixed time steps help with physics issues
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
        // If the user closed the splash screen, switch to the main menu
        _gameState = Game::GameState::ShowingMenu;
        _currentScreen = std::make_unique<MainMenuScreen>(_mainWindow, *_dispatcher, "./res/mainmenu.png");
        break;
    }
    case Game::GameState::PlayRequested:
    {
        // If the user clicked play, play the game
        _gameState = Game::GameState::Playing;
        _currentScreen = std::make_unique<GameScreen>(_mainWindow, *_dispatcher, *_render);
        break;
    }
    case Game::GameState::Lost:
    {
        // If the user lost, scold them and wait for acknowledgement
        _gameState = Game::GameState::ExitOnAck;
        _currentScreen = std::make_unique<GameOverScreen>(_mainWindow, *_dispatcher, "./res/game-over.png");
        break;
    }
    case Game::GameState::Won:
    {
        // If the user won, acknowledge them and wait for acknowledgement
        _gameState = Game::GameState::ExitOnAck;
        _currentScreen = std::make_unique<GameOverScreen>(_mainWindow, *_dispatcher, "./res/you-win.png");
        break;
    }
    }

    // Call core game loop logic
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
        {
            // React to window resizing
            this->modifyView([&](sf::View view)
                             {
                                view.setSize(currentEvent.size.width, currentEvent.size.height); 
                                return view; });
            break;
        }
        case sf::Event::Closed:
        {
            // If the window is closed, exit the game
            _gameState = Game::GameState::Exiting;
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (_currentScreen)
            {
                // Pass mouse button events on to the current screen
                _currentScreen->handleClick(currentEvent.mouseButton.x, currentEvent.mouseButton.y);
            }
            break;
        }
        }
    }
}

void Game::update(const sf::Time deltaTime)
{
    switch (_gameState)
    {
    // Only update the engine if we're playing
    case Game::GameState::Playing:
        this->_engine->update(deltaTime);
        break;
    }
}

bool Game::shouldRenderInState(const Game::GameState state) const
{
    // I'd prefer this to be a property of the GameState type itself, but given enumerations can't have methods in C++, this is what I'm doing until
    // I figure out how to idiomatically do this.
    return Game::GameState::Uninitialized != state && Game::GameState::Exiting != state;
}

void Game::modifyView(const std::function<sf::View(sf::View)> op)
{
    this->_view = op(this->_view);
    this->_mainWindow.setView(this->_view);
}

std::shared_ptr<Entity> Game::createPlayer()
{
    auto player = std::make_shared<Entity>();

    // The player looks like a paddle
    auto render = std::make_shared<RenderComponent>();
    render->texture->loadFromFile("./res/paddle.png");
    render->sprite = sf::Sprite(*(render->texture));

    // The player starts at the left edge in the middle of the screen
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

std::shared_ptr<Entity> Game::createEnemy()
{
    auto enemy = std::make_shared<Entity>();

    // The enemy looks like a paddle
    auto render = std::make_shared<RenderComponent>();
    render->texture->loadFromFile("./res/paddle.png");
    render->sprite = sf::Sprite(*(render->texture));

    // The enemy starts on the right edge at the middle of the screen
    auto location = std::make_shared<LocationComponent>();
    location->location.left = WORLD_WIDTH - WORLD_BORDER - 15;
    location->location.top = 309; // World middle
    location->location.height = 150;
    location->location.width = 15;

    auto velocity = std::make_shared<VelocityComponent>();

    auto enemyMarker = std::make_shared<EnemyComponent>();

    enemy->add(std::move(render));
    enemy->add(std::move(location));
    enemy->add(std::move(velocity));
    enemy->add(std::move(enemyMarker));

    return std::move(enemy);
}

std::shared_ptr<Entity> Game::createBall()
{
    auto ball = std::make_shared<Entity>();

    // The ball looks like a ball
    auto render = std::make_shared<RenderComponent>();
    render->texture->loadFromFile("./res/ball.png");
    render->sprite = sf::Sprite(*(render->texture));

    // The ball starts at the middle of the screen
    auto location = std::make_shared<LocationComponent>();
    location->location.height = 10.f;
    location->location.width = 10.f;
    location->location.left = (Game::WORLD_WIDTH - location->location.width) / 2.f;
    location->location.top = (Game::WORLD_HEIGHT - location->location.height) / 2.f;

    // The ball starts at the starting speed in a random direction
    // TODO: Filter out annoying starting directions, like straight up or straight sideways
    float ballSpeed = Game::BALL_INITIAL_SPEED;
    float angleRad = (rand() / static_cast<float>(RAND_MAX)) * 6.283185;
    auto velocity = std::make_shared<VelocityComponent>();
    velocity->velocity.x = ballSpeed * cos(angleRad);
    velocity->velocity.y = ballSpeed * sin(angleRad);

    auto ballMarker = std::make_shared<BallComponent>();

    ball->add(std::move(render));
    ball->add(std::move(location));
    ball->add(std::move(velocity));
    ball->add(std::move(ballMarker));

    return std::move(ball);
}