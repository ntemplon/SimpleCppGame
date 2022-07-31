#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <Entity.hpp>

class RenderComponent : public Entity::Component
{
public:
    static const std::string RENDER_COMP_ID;
    RenderComponent();
    std::shared_ptr<sf::Texture> texture; // Keep a reference so it doesn't go out of scope for us
    sf::Sprite sprite;
};

class LocationComponent : public Entity::Component
{
public:
    static const std::string LOC_COMP_ID;
    LocationComponent();
    sf::FloatRect location;
};

class VelocityComponent : public Entity::Component
{
public:
    static const std::string VEL_COMP_ID;
    VelocityComponent();
    sf::Vector2f velocity;
};

class PlayerComponent : public Entity::Component
{
public:
    static const std::string PLAYER_ID;
    PlayerComponent();
};

class BallComponent : public Entity::Component
{
public:
    static const std::string BALL_ID;
    BallComponent();
};