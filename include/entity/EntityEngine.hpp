#pragma once

#include <EntitySystem.hpp>

#include <SFML/System.hpp>

#include <vector>
#include <memory>

/**
 * @brief A engine for handling a component entity system.
 */
class EntityEngine
{
public:
    /**
     * @brief Adds a system to the engine.
     *
     * Adds the provided system to the engine. The call site and the engine will share ownership of the system.
     *
     * @param system
     */
    void add(std::shared_ptr<EntitySystem> system);

    /**
     * @brief Adds an entity to the engine
     *
     * @param entity
     */
    void add(std::shared_ptr<Entity> entity);

    /**
     * @brief Updates all systems in the engine
     *
     * @param deltaTime The amount of time that has passed since the last update.
     */
    void update(const sf::Time deltaTime);

private:
    std::vector<std::shared_ptr<EntitySystem>> _systems;
    std::map<int, std::shared_ptr<Entity>> _entities;
};