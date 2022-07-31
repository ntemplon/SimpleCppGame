#include <GameOverScreen.hpp>

const std::string GameOverScreen::GAME_OVER_ACK = "GAME_OVER_ACK";

GameOverScreen::GameOverScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string imagePath) : Screen(window, dispatcher)
{
    this->_texture.loadFromFile(imagePath);
    this->_sprite = sf::Sprite(this->_texture);
}

void GameOverScreen::render() const
{
    this->getWindow().clear(sf::Color(0, 0, 0));
    this->getWindow().draw(this->_sprite);
    this->getWindow().display();
}

void GameOverScreen::handleClick(int x, int y)
{
    Event ack(GAME_OVER_ACK);
    this->getDispatcher().dispatch(ack);
}