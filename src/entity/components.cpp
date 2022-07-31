#include <Components.hpp>

const std::string RenderComponent::RENDER_COMP_ID = "RENDER_COMP_ID";
const std::string LocationComponent::LOC_COMP_ID = "LOC_COMP_ID";
const std::string VelocityComponent::VEL_COMP_ID = "VEL_COMP_ID";
const std::string PlayerComponent::PLAYER_ID = "PLAYER_ID";
const std::string EnemyComponent::ENEMY_ID = "ENEMY_ID";
const std::string BallComponent::BALL_ID = "BALL_ID";

RenderComponent::RenderComponent() : Component(RENDER_COMP_ID), texture(std::make_shared<sf::Texture>())
{
}

LocationComponent::LocationComponent() : Component(LOC_COMP_ID)
{
}

VelocityComponent::VelocityComponent() : Component(VEL_COMP_ID)
{
}

PlayerComponent::PlayerComponent() : Component(PLAYER_ID)
{
}

EnemyComponent::EnemyComponent() : Component(ENEMY_ID)
{
}

BallComponent::BallComponent() : Component(BALL_ID)
{
}