#include <Game.hpp>
#include <VelocitySystem.hpp>
#include <ComponentFamily.hpp>
#include <Components.hpp>

#include <memory>
#include <unordered_set>
#include <algorithm>

VelocitySystem::VelocitySystem() : IteratingSystem(
                                       std::make_shared<ComponentFamily>(
                                           std::unordered_set<std::string>{LocationComponent::LOC_COMP_ID, VelocityComponent::VEL_COMP_ID}))
{
}

void VelocitySystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
{
    // Ugly component access. See ball-system.cpp for more discussion
    // TODO: Make component access better
    LocationComponent *location = dynamic_cast<LocationComponent *>(entity->getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *velocity = dynamic_cast<VelocityComponent *>(entity->getComponent(VelocityComponent::VEL_COMP_ID).get());

    // Update the new position to be the old position plus (velocity * deltaTime).
    // Use minimum and maximum values to ensure the object stays on the screen. Penetrations into the border of 2 pixels are allowed
    // so that the ball can intersect the rectangles at the top and bottom and bounce without moving out of bounds itself
    float elapsedTime = deltaTime.asSeconds();
    location->location.left = std::min(Game::WORLD_WIDTH - location->location.width - Game::WORLD_BORDER + 2.f,
                                       std::max((float)Game::WORLD_BORDER - 2.f, location->location.left + (velocity->velocity.x * elapsedTime)));
    location->location.top = std::min(Game::WORLD_HEIGHT - location->location.height - Game::WORLD_BORDER + 2.f,
                                      std::max((float)Game::WORLD_BORDER - 2.f, location->location.top + (velocity->velocity.y * elapsedTime)));
}