#pragma once

#include <unordered_set>

#include <EntityFamily.hpp>

class ComponentFamily : public EntityFamily
{
public:
    ComponentFamily();
    ComponentFamily(const std::unordered_set<std::string> componentIds);
    bool isInFamily(const Entity &entity) const;

private:
    const std::unordered_set<std::string> _componentIds;
};