#include <GameScreen.hpp>
#include <Game.hpp>

GameScreen::GameScreen(sf::RenderWindow &window, Dispatcher &dispatcher, RenderSystem &renderSystem)
    : Screen(window, dispatcher), _renderSystem(renderSystem)
{
    _gameWindow.setSize(sf::Vector2f((float)Game::WORLD_WIDTH, (float)Game::WORLD_HEIGHT));
    _gameWindow.setFillColor(sf::Color(0, 0, 0));
}

void GameScreen::render() const
{
    this->getWindow().clear(sf::Color(40, 40, 40));
    this->getWindow().draw(_gameWindow);
    this->_renderSystem.render(this->getWindow());
    this->getWindow().display();
}

void GameScreen::handleClick(int x, int y)
{
}