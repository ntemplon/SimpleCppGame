#pragma once

#include <memory>

#include <Screen.hpp>
#include <RenderSystem.hpp>

class GameScreen : public Screen
{
public:
    GameScreen(sf::RenderWindow &window, Dispatcher &dispatcher, RenderSystem &renderSystem);
    void render() const;
    void handleClick(int x, int y);

private:
    RenderSystem &_renderSystem;
    sf::RectangleShape _gameWindow;
};