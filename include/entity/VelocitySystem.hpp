#pragma once

#include <IteratingSystem.hpp>

/**
 * @brief A system for updating positions based on velocities.
 *
 * It acts on entities with LocationComponent and VelocityComponent
 */
class VelocitySystem : public IteratingSystem
{
public:
    /**
     * @brief Construct a new VelocitySystem
     */
    VelocitySystem();

protected:
    /**
     * @brief Updates position data based on velocity for an Entity
     *
     * @param entity The current entity being processed
     * @param deltaTime The amount of time that has passed since process() was last called on this entity
     */
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);
};