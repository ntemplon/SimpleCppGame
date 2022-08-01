#include <Entity.hpp>

#include <memory>

Entity::Component::Component(const std::string id) : _id(id)
{
}

const std::string Entity::Component::getId() const
{
    return this->_id;
}

Entity::Component::~Component()
{
}

Entity::Entity() : _id(rand())
{
}

Entity::Entity(int id) : _id(id)
{
}

void Entity::add(const std::shared_ptr<Entity::Component> &comp)
{
    this->_components.insert(std::make_pair(comp->getId(), comp));
}

bool Entity::hasComponent(const std::string id) const
{
    return this->_components.count(id);
}

std::shared_ptr<Entity::Component> Entity::getComponent(const std::string id) const
{
    return this->_components.at(id);
}

int Entity::getId() const
{
    return this->_id;
}