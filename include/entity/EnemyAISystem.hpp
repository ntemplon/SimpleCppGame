#pragma once

#include <IteratingSystem.hpp>
#include <ComponentFamily.hpp>
#include <Components.hpp>

/**
 * @brief A system that performs the AI for the enemy player.
 *
 */
class EnemyAISystem : public IteratingSystem
{
public:
    /**
     * @brief Construct a new Enemy AI System object
     *
     * @param ball The ball that the AI will track to try to bounce back as part of the game of Pong.
     */
    EnemyAISystem(Entity &ball);

protected:
    /**
     * @brief Processes the enemy AI for a single paddle.
     *
     * @param ai The AI that is being processed.
     * @param deltaTime The amount of time that has passed since the last time the AI was processed.
     */
    void process(std::shared_ptr<Entity> &ai, const sf::Time deltaTime);

private:
    Entity &_ball;
    float predictImpactPosition(sf::FloatRect &paddlePosition, sf::FloatRect &ballPosition, sf::Vector2f &ballVelocity, float uncertaintyScale);
};

/**
 * @brief A Component for enemy AI paddles
 *
 * The component marks an entity as an enemy AI paddle and stores related state, such as AI information.
 *
 */
class EnemyComponent : public Entity::Component
{
public:
    /**
     * @brief The ID for EnemyCompnent
     */
    static const std::string ENEMY_ID;

    /**
     * @brief The reaction time of an enemy AI after the player hits the ball.
     */
    static const sf::Time REACTION_TIME;
    static const float ENEMY_ERROR_SCALE;

    /**
     * @brief An enumeration of the states of the enemy paddle AI
     */
    enum class AIState
    {
        /**
         * @brief The player has hit the ball and the AI is reacting.
         */
        Reacting,
        /**
         * @brief The AI is moving down to intercept the ball.
         */
        MovingDown,
        /**
         * @brief The AI is moving up to intercept the ball.
         */
        MovingUp,
        /**
         * @brief The AI has hit the ball and is waiting for the player to respond.
         */
        WiatingForPlayer
    };

    /**
     * @brief Construct a new Enemy Component object
     *
     * The state information (e.g. AI) is unitialized and will need to be provided by the caller of the constructor.
     */
    EnemyComponent();

    /**
     * @brief The amount of time that the AI has spent waiting after the player took an action to respond. When this is greater than
     * or equal to EnemyComponent::REACTION_TIME, the AI paddle can respond, simulating human reaction.
     */
    sf::Time reactionElapsedTime;

    /**
     * @brief The current state of the paddle's AI
     */
    AIState aiState;

    /**
     * @brief The current predicted impact position of the next ball that the paddle will try to intercept and bounce back. This,
     * combined with EnemyComponent::predictionValid, form a pseudo-Optional<float>.
     */
    float predictedBallPosition;

    /**
     * @brief Whether or not the current prediction is a valid prediction that should be tracked to. This, combined with
     * EnemyComponent::predictedBallPosition, form a pseudo-Optional<float>.
     */
    bool predictionValid;
};