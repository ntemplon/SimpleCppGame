#pragma once

#include <EntitySystem.hpp>

/**
 * @brief An implementation of EntitySystem that iterates through all Entity objects in EntitySystem::getEntities() each EntitySystem::update.
 *
 */
class IteratingSystem : public EntitySystem
{
public:
    /**
     * @brief Construct a new IteratingSystem with the default EntitySystem constructor
     * @see EntitySystem::EntitySystem()
     */
    IteratingSystem();

    /**
     * @brief Construct a new IteratingSystem with the EntityFamily EntitySystem constructor
     *
     * @param family The family to provide to the EntitySystem constructor
     *
     * @see EntitySystem::EntitySystem(const std::shared_ptr<EntityFamily> &family)
     */
    IteratingSystem(const std::shared_ptr<EntityFamily> &family);

    /**
     * @brief Iterates through each element in the system to perform updates
     *
     * For each element in EntitySystem::getEntities(), calls IteratingSystem::process.
     *
     * @param deltaTime The amount of time that has passed since this method was last called
     * @see IteratingSystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
     */
    void update(const sf::Time deltaTime);

protected:
    /**
     * @brief Processes a specific entity.
     *
     * This method is pure virtual in IteratingSystem. It is up to sublcasses to implement their specific needs.
     *
     * @param entity The current entity being processed.
     * @param deltaTime The amount of time that has passed since process() was last called for this entity.
     */
    virtual void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime) = 0;
};