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
            // If they don't have one component, they aren't in the family
            return false;
        }
    }

    // If we got here, they didn't not have any components, which means they have them all, so they can join the family
    return true;
}