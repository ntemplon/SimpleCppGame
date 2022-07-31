#include <BallSystem.hpp>
#include <Components.hpp>
#include <ComponentFamily.hpp>
#include <Game.hpp>

const std::string BallSystem::PLAYER_SCORE_EVENT = "PLAYER_SCORE_EVENT";
const std::string BallSystem::ENEMY_SCORE_EVENT = "ENEMY_SCORE_EVENT";

BallSystem::BallSystem(Dispatcher &dispatcher, Entity &player) : IteratingSystem(
                                                                     std::make_shared<ComponentFamily>(
                                                                         std::unordered_set<std::string>{BallComponent::BALL_ID,
                                                                                                         LocationComponent::LOC_COMP_ID,
                                                                                                         VelocityComponent::VEL_COMP_ID})),
                                                                 _dispatcher(dispatcher), _player(player)
{
    this->_top = sf::FloatRect(0.f, 0.f, (float)Game::WORLD_WIDTH, (float)Game::WORLD_BORDER);
    this->_bottom = sf::FloatRect(0.f, (float)(Game::WORLD_HEIGHT - Game::WORLD_BORDER), (float)Game::WORLD_WIDTH, (float)Game::WORLD_BORDER);
    this->_left = sf::FloatRect(0.f, 0.f, (float)Game::WORLD_BORDER, (float)Game::WORLD_HEIGHT);
    this->_right = sf::FloatRect((float)(Game::WORLD_WIDTH - Game::WORLD_BORDER), 0.f, (float)Game::WORLD_BORDER, (float)Game::WORLD_HEIGHT);

    if (!this->_player.hasComponent(LocationComponent::LOC_COMP_ID))
    {
        throw std::invalid_argument("The provided 'player' did not have a location to represent the paddle!");
    }
}

void BallSystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
{
    LocationComponent *locCmp = dynamic_cast<LocationComponent *>(entity->getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *velCmp = dynamic_cast<VelocityComponent *>(entity->getComponent(VelocityComponent::VEL_COMP_ID).get());

    auto location = locCmp->location;
    if (_top.intersects(location) && velCmp->velocity.y < 0)
    {
        // Bounce off the top
        velCmp->velocity.y = velCmp->velocity.y * -1.f;
    }
    else if (_bottom.intersects(location) && velCmp->velocity.y > 0)
    {
        // Bounce off the bottom
        velCmp->velocity.y = velCmp->velocity.y * -1.f;
    }
    else if (_left.intersects(location) && velCmp->velocity.x < 0)
    {
        // Enemy scores
        velCmp->velocity.y = 0.f;
        velCmp->velocity.x = 0.f;

        Event score(ENEMY_SCORE_EVENT);
        this->_dispatcher.dispatch(score);
    }
    else if (_right.intersects(location) && velCmp->velocity.x > 0)
    {
        // Bounce off the right wall
        // TODO - change to scoring!
        velCmp->velocity.x = velCmp->velocity.x * -1.f;
    }
    else
    {
        LocationComponent *playerLocCmp = dynamic_cast<LocationComponent *>(this->_player.getComponent(LocationComponent::LOC_COMP_ID).get());
        auto playerLocation = playerLocCmp->location;
        if (playerLocation.intersects(location) && velCmp->velocity.x < 0)
        {
            // Bounce off the player's paddle
            velCmp->velocity.x = velCmp->velocity.x * -1.f;
        }
    }
}