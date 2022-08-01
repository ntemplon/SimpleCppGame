#include <RenderSystem.hpp>
#include <Components.hpp>
#include <ComponentFamily.hpp>

RenderSystem::RenderSystem() : IteratingSystem(
                                   std::make_shared<ComponentFamily>(
                                       std::unordered_set<std::string>{RenderComponent::RENDER_COMP_ID, LocationComponent::LOC_COMP_ID}))
{
}

void RenderSystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
{
    // Ugly component access. See ball-system.cpp for more discussion
    // TODO: Make component access better
    RenderComponent *renderComp = dynamic_cast<RenderComponent *>(entity->getComponent(RenderComponent::RENDER_COMP_ID).get());
    LocationComponent *locComp = dynamic_cast<LocationComponent *>(entity->getComponent(LocationComponent::LOC_COMP_ID).get());

    auto &sprite = renderComp->sprite;
    // Put the sprite at the entity's location
    sprite.setPosition(sf::Vector2f(locComp->location.left, locComp->location.top));
    // Scale the sprite to fill the entity's size / hit box
    sprite.setScale(sf::Vector2f(
        locComp->location.width / sprite.getTextureRect().width,
        locComp->location.height / sprite.getTextureRect().height));
}

void RenderSystem::render(sf::RenderTarget &target) const
{
    // For each entity, draw it on the target
    for (auto &pair : this->getEntities())
    {
        auto entity = pair.second;

        // TODO: Make component access better
        RenderComponent *renderComp = dynamic_cast<RenderComponent *>(entity->getComponent(RenderComponent::RENDER_COMP_ID).get());
        target.draw(renderComp->sprite);
    }
}