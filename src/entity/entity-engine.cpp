#include <EntityEngine.hpp>

void EntityEngine::add(std::shared_ptr<EntitySystem> system)
{
    // The pointer was copied into this scope, so we give our copy to the vector
    this->_systems.push_back(std::move(system));
}

void EntityEngine::add(std::shared_ptr<Entity> entity)
{
    for (auto &system : this->_systems)
    {
        system->engineEntityAdded(entity);
    }

    // The pointer was copied into this scope, so we give our copy for entity to the map
    this->_entities.insert(std::make_pair(entity->getId(), std::move(entity)));
}

void EntityEngine::update(const sf::Time deltaTime)
{
    for (std::shared_ptr<EntitySystem> &system : this->_systems)
    {
        system->update(deltaTime);
    }
}