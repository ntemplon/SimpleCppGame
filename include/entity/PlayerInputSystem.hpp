#pragma once

#include <IteratingSystem.hpp>

/**
 * @brief A system that uses player input to drive a paddle
 *
 * It acts on entities with a LocationComponent, VelocityComponent, and PlayerComponent.
 */
class PlayerInputSystem : public IteratingSystem
{
public:
    /**
     * @brief Construct a new PlayerInputSystem
     */
    PlayerInputSystem();

protected:
    /**
     * @brief Updates the behavior of a player paddle based on the current keyboard inputs.
     *
     * The paddle moves up if W or Up are pressed and down if S or Down are pressed.
     *
     * @param entity The current player being processed
     * @param deltaTime The time that has passed since process() was last called on this entity.
     */
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);
};