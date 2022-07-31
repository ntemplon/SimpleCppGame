#pragma once

#include <Screen.hpp>

class GameOverScreen : public Screen
{
public:
    static const std::string GAME_OVER_ACK;
    GameOverScreen(sf::RenderWindow &window, Dispatcher &dispatcher, std::string imagePath);
    void render() const;
    void handleClick(int x, int y);

private:
    sf::Texture _texture;
    sf::Sprite _sprite;
};