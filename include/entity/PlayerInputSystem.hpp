#pragma once

#include <IteratingSystem.hpp>

class PlayerInputSystem : public IteratingSystem
{
public:
    PlayerInputSystem();

protected:
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);
};