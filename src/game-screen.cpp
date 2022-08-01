#include <GameScreen.hpp>
#include <Game.hpp>

GameScreen::GameScreen(sf::RenderWindow &window, Dispatcher &dispatcher, RenderSystem &renderSystem)
    : Screen(window, dispatcher), _renderSystem(renderSystem)
{
    // The play field is sized at the world width and size and full black
    _gameWindow.setSize(sf::Vector2f((float)Game::WORLD_WIDTH, (float)Game::WORLD_HEIGHT));
    _gameWindow.setFillColor(sf::Color(0, 0, 0));
}

void GameScreen::render() const
{
    // Clear the "unused screen" grey
    this->getWindow().clear(sf::Color(40, 40, 40));

    // Draw the play surface in black
    this->getWindow().draw(_gameWindow);

    // Draw the objects on top of that
    this->_renderSystem.render(this->getWindow());

    // Display everything on the screen
    this->getWindow().display();
}

void GameScreen::handleClick(int x, int y)
{
    // Intentional no-op
}