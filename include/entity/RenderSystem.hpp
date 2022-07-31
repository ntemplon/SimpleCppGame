#pragma once

#include <SFML/Graphics.hpp>

#include <IteratingSystem.hpp>

class RenderSystem : public IteratingSystem
{
public:
    RenderSystem();
    void render(sf::RenderTarget &target) const;

protected:
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);
};