#pragma once

#include <IteratingSystem.hpp>

class PlayerInputSystem : public IteratingSystem
{
public:
    static const float PLAYER_PADDLE_SPEED;
    PlayerInputSystem();

protected:
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);
};