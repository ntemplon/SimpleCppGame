#pragma once

#include <EntityFamily.hpp>

#include <unordered_set>

/**
 * @brief An EntityFamily that defines a class as having a component of each of the specified types.
 */
class ComponentFamily : public EntityFamily
{
public:
    /**
     * @brief Construct a default new Component Family object
     *
     * The default constructor doesn't require any specific families, so all entities will be considered 'in the family'.
     *
     */
    ComponentFamily();

    /**
     * @brief Construct a new Component Family object
     *
     * Constructs a ComponentFamily that accepts all entities that have a component for each of the provided IDs.
     *
     * @param componentIds The IDs of the required component classes. These are idiomatically implemented as const static std::string
     * members of the Component's class.
     */
    ComponentFamily(const std::unordered_set<std::string> componentIds);

    /**
     * @brief Checks if the entity has all of the required componets to fit the family.
     *
     * @param entity The entity to evaluate if it is has all the components to be in the family.
     * @return true if the entity is in the family.
     * @return false if the entity is not in the family.
     */
    bool isInFamily(const Entity &entity) const;

private:
    const std::unordered_set<std::string> _componentIds;
};