#pragma once

#include <IteratingSystem.hpp>
#include <Dispatcher.hpp>

#include <SFML/Graphics.hpp>

/**
 * @brief A system that handles the ball physics.
 *
 * This system handles the unique aspects of ball physics, including bouncing off of walls and detecting successful scores. It acts on
 * Entities with LocationComponent, VelocityComponent, and BallComponent.
 *
 */
class BallSystem : public IteratingSystem
{
public:
    /**
     * @brief The Event ID indicating the player has scored.
     */
    static const std::string PLAYER_SCORE_EVENT;

    /**
     * @brief The Event ID indicating the enemy AI has scored.
     */
    static const std::string ENEMY_SCORE_EVENT;

    /**
     * @brief Constructs a new Ball System.
     *
     * @param dispatcher The dispatcher on which the system will post the PLAYER_SCORE_EVENT and ENEMY_SCORE_EVENT.
     * @param player A reference to the player. Its LocationComponent is used for collision detection with the paddle.
     * @param enemy A referece to the enemy AI. Its LocationComponent is used for collection detection with the paddle.
     */
    BallSystem(Dispatcher &dispatcher, Entity &player, Entity &enemy);

protected:
    /**
     * @brief Processes a ball.
     *
     * Processes a ball to see if it needs to bounce off a wall or has scored for either the player or the AI enemy.
     *
     * @param entity The current ball to process.
     * @param deltaTime The amount of time that has passed since the last call to process() for this ball.
     */
    void process(std::shared_ptr<Entity> &entity, sf::Time deltaTime);

private:
    Entity &_player;
    Entity &_enemy;

    sf::FloatRect _top;
    sf::FloatRect _bottom;
    sf::FloatRect _left;
    sf::FloatRect _right;

    Dispatcher &_dispatcher;

    void slightlyRandomize(sf::Vector2f &velocity) const;
};