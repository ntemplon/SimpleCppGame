#pragma once

#include <IteratingSystem.hpp>

class VelocitySystem : public IteratingSystem
{
public:
    VelocitySystem();

protected:
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);
};