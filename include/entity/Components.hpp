#pragma once

#include <SFML/Graphics.hpp>
#include <Entity.hpp>

class RenderComponent : public Entity::Component
{
public:
    static const std::string RENDER_COMP_ID;
    RenderComponent();
    sf::Sprite sprite;
    sf::FloatRect renderArea;
};

class LocationComponent : public Entity::Component
{
public:
    static const std::string LOC_COMP_ID;
    LocationComponent();
    sf::FloatRect location;
};