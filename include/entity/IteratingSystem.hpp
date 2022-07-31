#pragma once

#include <EntitySystem.hpp>

class IteratingSystem : public EntitySystem
{
public:
    IteratingSystem();
    IteratingSystem(const std::shared_ptr<EntityFamily> &family);
    void update(const sf::Time deltaTime);

protected:
    virtual void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime) = 0;
};