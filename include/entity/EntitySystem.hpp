#pragma once

#include <memory>
#include <map>

#include <SFML/System.hpp>

#include <Entity.hpp>
#include <EntityFamily.hpp>

class EntitySystem
{
public:
    EntitySystem();
    EntitySystem(const std::shared_ptr<EntityFamily> &family);
    virtual void engineEntityAdded(const std::shared_ptr<Entity> &entity);
    virtual void update(const sf::Time deltaTime) = 0;

protected:
    std::map<int, std::shared_ptr<Entity>> getEntities() const;

private:
    std::shared_ptr<EntityFamily> _family;
    std::map<int, std::shared_ptr<Entity>> _entities;
};