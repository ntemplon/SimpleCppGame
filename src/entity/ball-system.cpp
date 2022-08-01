#include <BallSystem.hpp>
#include <Components.hpp>
#include <ComponentFamily.hpp>
#include <Game.hpp>

#include <math.h>

const std::string BallSystem::PLAYER_SCORE_EVENT = "PLAYER_SCORE_EVENT";
const std::string BallSystem::ENEMY_SCORE_EVENT = "ENEMY_SCORE_EVENT";

BallSystem::BallSystem(Dispatcher &dispatcher, Entity &player, Entity &enemy) : IteratingSystem(
                                                                                    std::make_shared<ComponentFamily>(
                                                                                        std::unordered_set<std::string>{BallComponent::BALL_ID,
                                                                                                                        LocationComponent::LOC_COMP_ID,
                                                                                                                        VelocityComponent::VEL_COMP_ID})),
                                                                                _dispatcher(dispatcher), _player(player), _enemy(enemy)
{
    // Rectangles that cover the four sides of the game world at Game::WORLD_BORDER width.
    this->_top = sf::FloatRect(0.f, 0.f, (float)Game::WORLD_WIDTH, (float)Game::WORLD_BORDER);
    this->_bottom = sf::FloatRect(0.f, (float)(Game::WORLD_HEIGHT - Game::WORLD_BORDER), (float)Game::WORLD_WIDTH, (float)Game::WORLD_BORDER);
    this->_left = sf::FloatRect(0.f, 0.f, (float)Game::WORLD_BORDER, (float)Game::WORLD_HEIGHT);
    this->_right = sf::FloatRect((float)(Game::WORLD_WIDTH - Game::WORLD_BORDER), 0.f, (float)Game::WORLD_BORDER, (float)Game::WORLD_HEIGHT);

    // Usually, component presence is enforced by ComponentFamily objects in an EntitySystem. Because we're getting a handle we're going to
    //  grab components from, make sure it's got them.
    if (!this->_player.hasComponent(LocationComponent::LOC_COMP_ID))
    {
        throw std::invalid_argument("The provided 'player' did not have a location to represent the paddle!");
    }
    if (!this->_enemy.hasComponent(LocationComponent::LOC_COMP_ID))
    {
        throw std::invalid_argument("The provided 'enemy' did not have a location to represent the paddle!");
    }
}

// TODO: At high speeds, the ball can clip through paddles. Fix the bug!
void BallSystem::process(std::shared_ptr<Entity> &entity, sf::Time deltaTime)
{
    // This is an ugly way to get the components, but it's the best I've got right now. The ID system guarantees these casts
    //   won't fail.
    // TODO: Improve cleanlieness of component accessors.
    LocationComponent *locCmp = dynamic_cast<LocationComponent *>(entity->getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *velCmp = dynamic_cast<VelocityComponent *>(entity->getComponent(VelocityComponent::VEL_COMP_ID).get());
    LocationComponent *playerLocCmp = dynamic_cast<LocationComponent *>(this->_player.getComponent(LocationComponent::LOC_COMP_ID).get());
    LocationComponent *enemyLocCmp = dynamic_cast<LocationComponent *>(this->_enemy.getComponent(LocationComponent::LOC_COMP_ID).get());

    auto location = locCmp->location;
    auto playerLocation = playerLocCmp->location;
    auto enemyLocation = enemyLocCmp->location;
    // Checking for player/enemy paddle collisions before scoring collisions increases the speed at which clipping starts to occur.
    if (playerLocation.intersects(location) && velCmp->velocity.x < 0)
    {
        // Bounce off the player's paddle
        velCmp->velocity.x = velCmp->velocity.x * -1.f;

        // Make it interesting with a little bit of randomness and a slight speedup
        this->slightlyRandomize(velCmp->velocity);
        velCmp->velocity.x = velCmp->velocity.x * 1.02f;
        velCmp->velocity.y = velCmp->velocity.y * 1.02f;
    }
    else if (enemyLocation.intersects(location) && velCmp->velocity.x > 0)
    {
        // Bounce off the enemy's paddle
        velCmp->velocity.x = velCmp->velocity.x * -1.f;

        // Make it interesting with a little bit of randomness and a slight speedup
        this->slightlyRandomize(velCmp->velocity);
        velCmp->velocity.x = velCmp->velocity.x * 1.02f;
        velCmp->velocity.y = velCmp->velocity.y * 1.02f;
    }
    else if (_top.intersects(location) && velCmp->velocity.y < 0) // Touching the top and moving upwards
    {
        // Bounce off the top
        velCmp->velocity.y = velCmp->velocity.y * -1.f;
    }
    else if (_bottom.intersects(location) && velCmp->velocity.y > 0) // Touching the bottom and moving downwards
    {
        // Bounce off the bottom
        velCmp->velocity.y = velCmp->velocity.y * -1.f;
    }
    else if (_left.intersects(location) && velCmp->velocity.x < 0) // Touching the left and moving left.
    {
        // Enemy scores
        Event score(ENEMY_SCORE_EVENT);
        this->_dispatcher.dispatch(score);
    }
    else if (_right.intersects(location) && velCmp->velocity.x > 0) // Touching the right and moving right.
    {
        // Player scores
        Event score(PLAYER_SCORE_EVENT);
        this->_dispatcher.dispatch(score);
    }
}

// Lightly randomize by rotating the angle of the velocity vector by up to 5 degrees
void BallSystem::slightlyRandomize(sf::Vector2f &velocity) const
{
    // Random number from -5 to 5 degrees, in radians
    float randomRotationAngle = ((rand() / static_cast<float>(RAND_MAX)) * (2.f * 0.087267f)) - 0.087267f; // 0.087267f is 5 degrees in radians
    float x1 = velocity.x;
    float y1 = velocity.y;

    float sinTheta = sin(randomRotationAngle);
    float cosTheta = cos(randomRotationAngle);

    // Vector rotation math
    float x2 = (cosTheta * x1) - (sinTheta * y1);
    float y2 = (sinTheta * x1) + (cosTheta * y1);

    velocity.x = x2;
    velocity.y = y2;
}