#include <unordered_set>

#include <PlayerInputSystem.hpp>
#include <ComponentFamily.hpp>
#include <Components.hpp>
#include <Game.hpp>

PlayerInputSystem::PlayerInputSystem() : IteratingSystem(
                                             std::make_shared<ComponentFamily>(
                                                 std::unordered_set<std::string>{PlayerComponent::PLAYER_ID, VelocityComponent::VEL_COMP_ID}))
{
}

void PlayerInputSystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
{
    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);

    VelocityComponent *velocity = dynamic_cast<VelocityComponent *>(entity->getComponent(VelocityComponent::VEL_COMP_ID).get());

    if (upPressed && !downPressed)
    {
        velocity->velocity.y = -1 * Game::PADDLE_SPEED;
    }
    else if (downPressed && !upPressed)
    {
        velocity->velocity.y = Game::PADDLE_SPEED;
    }
    else
    {
        velocity->velocity.y = 0.f;
    }
}
