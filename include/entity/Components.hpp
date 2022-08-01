#pragma once

#include <Entity.hpp>

#include <SFML/Graphics.hpp>

#include <memory>

/**
 * @brief A component that stores the information required to render the entity on the screen.
 */
class RenderComponent : public Entity::Component
{
public:
    /**
     * @brief The ID of RenderComponent
     */
    static const std::string RENDER_COMP_ID;

    /**
     * @brief Construct a new RenderComponent
     *
     * Construct a new RenderComponent with unitialized variables. After creating a RenderComponent this way, you should load the
     * texture (such as with texture.loadFromFile() ) and then set the sprite to a new sprite based on that texture.
     */
    RenderComponent();

    /**
     * @brief The texture that the sprite uses.
     *
     * The sprite does not use a pointer that keeps ownership of the texture, so we do so here to ensure it doesn't go out of scope.
     */
    std::shared_ptr<sf::Texture> texture;

    /**
     * @brief The sprite that will be rendered to represent the entity.
     */
    sf::Sprite sprite;
};

/**
 * @brief A component that stores the information about where and how large the entity is
 *
 */
class LocationComponent : public Entity::Component
{
public:
    /**
     * @brief The ID of LocationComponent
     */
    static const std::string LOC_COMP_ID;

    /**
     * @brief Construct a new Location Component object
     *
     * The location sf::FloatRect defaults to size (0, 0) at the origin. If other values are desired, the caller must set them after
     * initialization.
     */
    LocationComponent();

    /**
     * @brief The location and bounds of the entity.
     */
    sf::FloatRect location;
};

/**
 * @brief A component for storing the 2D velocity of an entity
 */
class VelocityComponent : public Entity::Component
{
public:
    /**
     * @brief The ID of a VelocityComponent
     */
    static const std::string VEL_COMP_ID;

    /**
     * @brief Construct a new Velocity Component object
     *
     * The velocity defaults to (0, 0)
     */
    VelocityComponent();

    /**
     * @brief The entity's velocity
     */
    sf::Vector2f velocity;
};

/**
 * @brief A component for marking an entity as a player
 */
class PlayerComponent : public Entity::Component
{
public:
    /**
     * @brief The ID of a PlayerComponent
     */
    static const std::string PLAYER_ID;

    /**
     * @brief Construct a new Player Component object
     */
    PlayerComponent();
};

/**
 * @brief A component for marking an entity as a ball
 */
class BallComponent : public Entity::Component
{
public:
    /**
     * @brief The ID of a BallComponent
     */
    static const std::string BALL_ID;

    /**
     * @brief Construct a new Ball Component object
     */
    BallComponent();
};