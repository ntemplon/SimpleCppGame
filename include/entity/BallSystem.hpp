#pragma once

#include <SFML/Graphics.hpp>

#include <IteratingSystem.hpp>
#include <Dispatcher.hpp>

class BallSystem : public IteratingSystem
{
public:
    static const std::string PLAYER_SCORE_EVENT;
    static const std::string ENEMY_SCORE_EVENT;
    BallSystem(Dispatcher &dispatcher, Entity &player);

protected:
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);

private:
    Entity &_player;

    sf::FloatRect _top;
    sf::FloatRect _bottom;
    sf::FloatRect _left;
    sf::FloatRect _right;

    Dispatcher &_dispatcher;
};