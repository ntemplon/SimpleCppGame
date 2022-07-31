#include <ComponentFamily.hpp>

ComponentFamily::ComponentFamily()
{
}

ComponentFamily::ComponentFamily(const std::unordered_set<std::string> componentIds) : _componentIds(componentIds)
{
}

bool ComponentFamily::isInFamily(const Entity &entity) const
{
    for (const std::string &compId : this->_componentIds)
    {
        if (!entity.hasComponent(compId))
        {
            return false;
        }
    }
    return true;
}