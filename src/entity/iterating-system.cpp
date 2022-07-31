#include <IteratingSystem.hpp>

IteratingSystem::IteratingSystem() : EntitySystem()
{
}

IteratingSystem::IteratingSystem(const std::shared_ptr<EntityFamily> &family) : EntitySystem(family)
{
}

void IteratingSystem::update(const sf::Time deltaTime)
{
    for (auto &pair : this->getEntities())
    {
        this->process(pair.second, deltaTime);
    }
}