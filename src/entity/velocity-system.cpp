#include <memory>
#include <unordered_set>
#include <algorithm>

#include <Game.hpp>
#include <VelocitySystem.hpp>
#include <ComponentFamily.hpp>
#include <Components.hpp>

VelocitySystem::VelocitySystem() : IteratingSystem(
                                       std::make_shared<ComponentFamily>(
                                           std::unordered_set<std::string>{LocationComponent::LOC_COMP_ID, VelocityComponent::VEL_COMP_ID}))
{
}

void VelocitySystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
{
    LocationComponent *location = dynamic_cast<LocationComponent *>(entity->getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *velocity = dynamic_cast<VelocityComponent *>(entity->getComponent(VelocityComponent::VEL_COMP_ID).get());

    float elapsedTime = deltaTime.asSeconds();
    location->location.left = std::min(Game::WORLD_WIDTH - location->location.width, std::max(0.f, location->location.left + (velocity->velocity.x * elapsedTime)));
    location->location.top = std::min(Game::WORLD_HEIGHT - location->location.height, std::max(0.f, location->location.top + (velocity->velocity.y * elapsedTime)));
}