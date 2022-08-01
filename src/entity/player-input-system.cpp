#include <PlayerInputSystem.hpp>
#include <ComponentFamily.hpp>
#include <Components.hpp>
#include <Game.hpp>

#include <unordered_set>

PlayerInputSystem::PlayerInputSystem() : IteratingSystem(
                                             std::make_shared<ComponentFamily>(
                                                 std::unordered_set<std::string>{PlayerComponent::PLAYER_ID, VelocityComponent::VEL_COMP_ID}))
{
}

void PlayerInputSystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
{
    // Group logical up/down selections before logic
    // TODO: Change this to be configurable
    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    // Ugly component access. See ball-system.cpp for more discussion
    // TODO: Make component access better
    VelocityComponent *velocity = dynamic_cast<VelocityComponent *>(entity->getComponent(VelocityComponent::VEL_COMP_ID).get());

    // If only up is pressed, move up
    if (upPressed && !downPressed)
    {
        velocity->velocity.y = -1 * Game::PADDLE_SPEED;
    }
    // If only down is pressed, move down
    else if (downPressed && !upPressed)
    {
        velocity->velocity.y = Game::PADDLE_SPEED;
    }
    // Either neither or both buttons are pressed.
    else
    {
        velocity->velocity.y = 0.f;
    }
}
