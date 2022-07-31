#pragma once

#include <Screen.hpp>

class GameScreen : public Screen
{
public:
    GameScreen(sf::RenderWindow &window, Dispatcher &dispatcher);
};