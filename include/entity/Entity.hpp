#pragma once

#include <string>
#include <map>
#include <memory>

/**
 * @brief An entity in the game's component entity system.
 *
 * The Entity represents a collection of attributes, called Components, that together are acted upon by EntitySystem objects that
 * form a complete game world.
 */
class Entity
{
public:
    /**
     * @brief A component of an entity in the game's component entity system.
     *
     * Components represent an aspect of an Entity. They store state information, such as position and sprite data, as well as mark the
     * Entity as belong to a certain class of object, like being the player or an AI opponent.
     *
     * Component types are identified with their ID, which is passed to the constructor. To avoid odd bugs and behavior, all instances
     * of the same Component subclass should have the same ID, which is usually declared as a static member of the class or a preprocessor
     * constant in the header file.
     */
    class Component
    {
    public:
        /**
         * @brief Construct a new Component object
         *
         * @param id The Component's ID
         */
        Component(const std::string id);

        /**
         * @brief This is only declared to make the class polymorphic so that dymaic_cast between Component types works
         */
        virtual ~Component();

        /**
         * @brief Get the ID of the component. This will return the same value for all instances of a class of Component.
         */
        const std::string getId() const;

    private:
        const std::string _id;
    };

    /**
     * @brief Construct a new Entity with a random ID
     */
    Entity();

    /**
     * @brief Construct a new Entity object with a specific ID
     *
     * @param id The ID of the Entity
     */
    Entity(int id);

    /**
     * @brief Get the ID of the Entity
     *
     * @return int the entity's ID
     */
    int getId() const;

    /**
     * @brief Adds the provided component to the entity.
     *
     * The entity will create a new std::shared_ptr pointing to the Component using the copy constructor that will stay in scope
     * with the entity.
     *
     * @param component The Component to add to this Entity.
     */
    void add(const std::shared_ptr<Component> &component);

    /**
     * @brief Check if the Entity has a component of the specified type.
     *
     * @param id The ID of the Component type.
     * @return true if the Entity has a component of the specified type.
     * @return false if the Entnity doeso not have a component of the specified type.
     */
    bool hasComponent(const std::string id) const;

    /**
     * @brief Get the Component object
     *
     * @param id
     * @return std::shared_ptr<Component>
     */
    std::shared_ptr<Component> getComponent(const std::string id) const;

private:
    int _id;
    std::map<std::string, std::shared_ptr<Component>> _components;
};