#pragma once

#include <IteratingSystem.hpp>
#include <ComponentFamily.hpp>
#include <Components.hpp>

class EnemyAISystem : public IteratingSystem
{
public:
    EnemyAISystem(Entity &ball);

protected:
    void process(std::shared_ptr<Entity> &ai, const sf::Time deltaTime);

private:
    Entity &_ball;
    float predictImpactPosition(sf::FloatRect &paddlePosition, sf::FloatRect &ballPosition, sf::Vector2f &ballVelocity, float uncertaintyScale);
};

class EnemyComponent : public Entity::Component
{
public:
    static const std::string ENEMY_ID;
    static const sf::Time REACTION_TIME;
    static const float ENEMY_ERROR_SCALE;

    enum class AIState
    {
        Reacting,
        MovingDown,
        MovingUp,
        WiatingForPlayer
    };

    EnemyComponent();

    sf::Time reactionElapsedTime;
    AIState aiState;
    float predictedBallPosition;
    bool predictionValid;
};