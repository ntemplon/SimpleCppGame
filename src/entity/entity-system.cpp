#include <EntitySystem.hpp>
#include <ComponentFamily.hpp>

EntitySystem::EntitySystem() : _family(std::make_shared<ComponentFamily>())
{
}

EntitySystem::EntitySystem(const std::shared_ptr<EntityFamily> &family) : _family(family)
{
}

void EntitySystem::engineEntityAdded(const std::shared_ptr<Entity> &entity)
{
    if (this->_family->isInFamily(*entity))
    {
        this->_entities.insert(std::make_pair(entity->getId(), entity));
    }
}

std::map<int, std::shared_ptr<Entity>> EntitySystem::getEntities() const
{
    return this->_entities;
}