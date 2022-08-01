#pragma once

#include <Entity.hpp>

/**
 * @brief An abstract class that allows for the definition of a class of entity.
 *
 */
class EntityFamily
{
public:
    /**
     * @brief Evaluates if an entity is "in the family" by meeting the criteria of the class the family represents.
     *
     * @param entity The entity to evaluate if it is in the family.
     * @return true if the entity is in the family.
     * @return false if the entity is not in the family.
     */
    virtual bool isInFamily(const Entity &entity) const = 0;
};