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
    RenderComponent *renderComp = dynamic_cast<RenderComponent *>(entity->getComponent(RenderComponent::RENDER_COMP_ID).get());
    LocationComponent *locComp = dynamic_cast<LocationComponent *>(entity->getComponent(LocationComponent::LOC_COMP_ID).get());

    renderComp->sprite.setPosition(sf::Vector2f(locComp->location.left, locComp->location.top));
}

void RenderSystem::render(sf::RenderTarget &target) const
{
    for (auto &pair : this->getEntities())
    {
        auto entity = pair.second;

        RenderComponent *renderComp = dynamic_cast<RenderComponent *>(entity->getComponent(RenderComponent::RENDER_COMP_ID).get());
        target.draw(renderComp->sprite);
    }
}