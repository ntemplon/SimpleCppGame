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
     * Adds the provided system to the engine. The call site and the engine will share ownership of the system through the
     * shared_ptr created by the copy constructor when calling this method. Systems will have update() called on them each
     * frame in the same order they are added to the engine, so if processing order is important, care should be taken when
     * organizing calls to add().
     *
     * @param system the system to be added to the engine
     */
    void add(std::shared_ptr<EntitySystem> system);

    /**
     * @brief Adds an entity to the engine
     *
     * Adds the provided entity to the engine. The call site, the engine, and any systems that choose to will share ownership
     * of the entity through copies of the shared_ptr. Systems will only be informed of the addition of an entity if
     * EntityEngine::add(std::shared_ptr<Entity> entity) is called after EntityEngine::add(std::shared_ptr<EntitySystem> system),
     * so take care with ordering calls during initialization
     *
     * @param entity the entity to add to the engine
     */
    void add(std::shared_ptr<Entity> entity);

    /**
     * @brief Updates all systems in the engine
     *
     * @param deltaTime The amount of time that has passed since the last update.
     *
     * @see EntitySystem::update
     */
    void update(const sf::Time deltaTime);

private:
    std::vector<std::shared_ptr<EntitySystem>> _systems;
    std::map<int, std::shared_ptr<Entity>> _entities;
};