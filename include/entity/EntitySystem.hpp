#pragma once

#include <Entity.hpp>
#include <EntityFamily.hpp>

#include <SFML/System.hpp>

#include <memory>
#include <map>

// TODO: Refactor family filtering logic to a FilteredEntitySystem class.
/**
 * @brief A class representing a system that processes groups of Entity in an EntityEngine.
 *
 * An abstract class to be extended by specific implementations.
 */
class EntitySystem
{
public:
    /**
     * @brief Construct a new default EntitySystem
     *
     * This creates an EntitySystem that processes all Entities added to the EntityEngine if EntitySystem::engineEngineEntityAdded is
     * not overridden.
     */
    EntitySystem();

    /**
     * @brief Construct a new EntitySystem that acts on a specified family.
     *
     * @param family The family of entities that this system will act on. The EntitySystem implementation of EntitySystem::engineEntityAdded
     * adds all entities to the system for which this family's implementation of EntityFamily::isInFamily returns true.
     */
    EntitySystem(const std::shared_ptr<EntityFamily> &family);

    /**
     * @brief Performs any operations required after an entity has been added to an EntityEngine the system is a part of.
     *
     * The default implementation adds the Entity to the Entities property (EntitySystem::getEntities) if the default constructor was
     * called or the Entity is in the family provided to the family constructor.
     *
     * @param entity The Entity recently added to the EntityEngine.
     */
    virtual void engineEntityAdded(const std::shared_ptr<Entity> &entity);

    /**
     * @brief Performs any operations necessary in routine processing.
     *
     * This method is pure virtual in EntitySystem.
     *
     * @param deltaTime The time that has passed since update() was last called.
     */
    virtual void update(const sf::Time deltaTime) = 0;

protected:
    /**
     * @brief Get the Entities in the system.
     *
     * @return std::map<int, std::shared_ptr<Entity>> A mapping of IDs to the entity that has those IDs for the entities that are part
     * of this system.
     */
    virtual std::map<int, std::shared_ptr<Entity>> getEntities() const;

private:
    std::shared_ptr<EntityFamily> _family;
    std::map<int, std::shared_ptr<Entity>> _entities;
};