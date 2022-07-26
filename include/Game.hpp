#pragma once

#include <Screen.hpp>
#include <Dispatcher.hpp>
#include <EntityEngine.hpp>
#include <RenderSystem.hpp>
#include <VelocitySystem.hpp>
#include <PlayerInputSystem.hpp>
#include <BallSystem.hpp>
#include <StateMachine.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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
     * @brief The width of the world, in game units
     */
    constexpr static int WORLD_WIDTH = 1024;

    /**
     * @brief The height of the world, in game units
     */
    constexpr static int WORLD_HEIGHT = 768;

    /**
     * @brief The width of the border in the world, in game units
     */
    constexpr static int WORLD_BORDER = 20;

    /**
     * @brief The speed at which paddles move, in game units / second
     */
    constexpr static float PADDLE_SPEED = 350.f;

    /**
     * @brief The initial speed of the ball
     */
    constexpr static float BALL_INITIAL_SPEED = 500.f;

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
    /**
     * @brief A shortcut for checking if the game is currently executing
     */
    bool isExiting() const;

    /**
     * @brief Performs an iteration of the game loop.
     *
     * Handles input, updates the systems, and renders if applicable.
     *
     * @param deltaTime The amount of time that is being processed in this gameLoop() iteration.
     */
    void gameLoop(const sf::Time deltaTime);

    /**
     * @brief Reads the current input events and handles them.
     *
     * Dispatches events on the main Dispatcher and handles game state transitions as appropriate.
     */
    void handleInput();

    /**
     * @brief Updates the relevant systems, such as the EntityEngine
     *
     * @param detlaTime the time that has passed since the last call to update()
     */
    void update(const sf::Time detlaTime);

    /**
     * @brief Modifies the current view of the window with the specified operation
     *
     * Call this instead of directly modifying the view to avoid code duplication to handle pass-by-value calls in that process.
     *
     * @param op a function that takes the current sf::View for the RenderWindow and modifies it to be the new view.
     */
    void modifyView(const std::function<sf::View(sf::View)> op);

    std::shared_ptr<Entity> createPlayer();
    std::shared_ptr<Entity> createEnemy();
    std::shared_ptr<Entity> createBall();

    void render();

    void initialize();
    void displaySplashScreen();
    void displayMainMenu();
    void startPlaying();
    void loseGame();
    void winGame();

    sf::RenderWindow _mainWindow;
    sf::View _view;

    std::unique_ptr<Screen> _currentScreen;
    std::unique_ptr<Dispatcher> _dispatcher; // It is VERY important this is initialiized before _stm!!! VERY.
    std::unique_ptr<EntityEngine> _engine;
    std::shared_ptr<RenderSystem> _render;
    std::shared_ptr<VelocitySystem> _velocity;
    std::shared_ptr<PlayerInputSystem> _input;
    std::shared_ptr<BallSystem> _ballSystem;

    StateMachine _stm;
    std::shared_ptr<StateMachine::State> _uninitialized;
    std::shared_ptr<StateMachine::State> _splash;
    std::shared_ptr<StateMachine::State> _mainMenu;
    std::shared_ptr<StateMachine::State> _playing;
    std::shared_ptr<StateMachine::State> _won;
    std::shared_ptr<StateMachine::State> _lost;
    std::shared_ptr<StateMachine::State> _exiting;

    class InitializationCompleteEvent : public Event
    {
    public:
        static const std::string INITIALIZATION_COMPLETE;
        InitializationCompleteEvent();
    };

    class WindowCloseEvent : public Event
    {
    public:
        static const std::string WINDOW_CLOSE_EVENT;
        WindowCloseEvent();
    };
};