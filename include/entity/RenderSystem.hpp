#pragma once

#include <IteratingSystem.hpp>

#include <SFML/Graphics.hpp>

/**
 * @brief A system that manages Entity sprite sizes, positions, and drawing.
 *
 * It acts on all elements with a RenderComponent and LocationComponent
 */
class RenderSystem : public IteratingSystem
{
public:
    /**
     * @brief Construct a new RenderSystem
     */
    RenderSystem();

    /**
     * @brief Draws the prepared sprites to the sf::RenderTarget
     *
     * @param target The target to draw the entities on.
     */
    void render(sf::RenderTarget &target) const;

protected:
    /**
     * @brief Processes the Entity graphical data.
     *
     * Sprites are moved and scaled to align with the Entity LocationComponent data.
     *
     * @param entity The entity being processed
     * @param deltaTime The amount of time that has passed since process() was last called on this entity
     */
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);
};