#include <EnemyAISystem.hpp>
#include <Game.hpp>

#include <math.h>

EnemyAISystem::EnemyAISystem(Entity &ball) : IteratingSystem(std::make_shared<ComponentFamily>(
                                                 std::unordered_set<std::string>{EnemyComponent::ENEMY_ID,
                                                                                 LocationComponent::LOC_COMP_ID,
                                                                                 VelocityComponent::VEL_COMP_ID})),
                                             _ball(ball)
{
}

void EnemyAISystem::process(std::shared_ptr<Entity> &ai, sf::Time deltaTime)
{
    // TODO: Improve cleanlieness of component accessors. See ball-system.cpp for more discussion.
    EnemyComponent *enemyCmp = dynamic_cast<EnemyComponent *>(ai->getComponent(EnemyComponent::ENEMY_ID).get());
    LocationComponent *locCmp = dynamic_cast<LocationComponent *>(ai->getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *velCmp = dynamic_cast<VelocityComponent *>(ai->getComponent(VelocityComponent::VEL_COMP_ID).get());

    LocationComponent *ballLocCmp = dynamic_cast<LocationComponent *>(_ball.getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *ballVelCmp = dynamic_cast<VelocityComponent *>(_ball.getComponent(VelocityComponent::VEL_COMP_ID).get());

    switch (enemyCmp->aiState)
    {
    case EnemyComponent::AIState::WaitingForPlayer:
    {
        // If the ball starts moving towards us, react
        if (ballVelCmp->velocity.x > 0)
        {
            enemyCmp->aiState = EnemyComponent::AIState::Reacting;
        }
        // If the ball is not moving towards us, move up-and-down to match the ball. This gives the AI a more alive feeling.
        else
        {
            float paddleCenter = locCmp->location.top + (locCmp->location.height / 2.f);
            if (ballLocCmp->location.top > paddleCenter)
            {
                // Ball is below us
                velCmp->velocity.y = Game::PADDLE_SPEED;
            }
            else
            {
                // Ball is above us
                velCmp->velocity.y = -1.f * Game::PADDLE_SPEED;
            }
        }
        break;
    }
    case EnemyComponent::AIState::Reacting:
    {
        // If we don't already have a prediction, make one
        if (!enemyCmp->predictionValid)
        {
            enemyCmp->predictedBallPosition = predictImpactPosition(locCmp->location, ballLocCmp->location, ballVelCmp->velocity, EnemyComponent::ENEMY_ERROR_SCALE);
            enemyCmp->predictionValid = true;
        }

        // Check if we're done waiting
        enemyCmp->reactionElapsedTime += deltaTime;
        if (enemyCmp->reactionElapsedTime > EnemyComponent::REACTION_TIME)
        {
            // We are done waiting, so reset the counter for the next time
            enemyCmp->reactionElapsedTime = sf::Time::Zero;
            float paddleCenter = locCmp->location.top + (locCmp->location.height / 2.f);

            // We are below the predicted location
            if (paddleCenter > enemyCmp->predictedBallPosition)
            {
                // Move up and note our state
                velCmp->velocity.y = Game::PADDLE_SPEED * -1.f;
                enemyCmp->aiState = EnemyComponent::AIState::MovingUp;
            }
            // We are above the predicted location
            else if (paddleCenter <= enemyCmp->predictedBallPosition)
            {
                // Move up and note our state
                velCmp->velocity.y = Game::PADDLE_SPEED;
                enemyCmp->aiState = EnemyComponent::AIState::MovingDown;
            }
        }
        break;
    }
    case EnemyComponent::AIState::MovingDown:
    {
        // if the ball has started moving away from us, we bounced it
        //   and need to wait for the player to move
        if (ballVelCmp->velocity.x < 0)
        {
            enemyCmp->predictionValid = false; // Stop listening to the prediction
            enemyCmp->aiState = EnemyComponent::AIState::WaitingForPlayer;
        }
        else // The ball is still moving towards us
        {
            float paddleCenter = locCmp->location.top + (locCmp->location.height / 2.f);
            // If we are now at or below the prediction, we can stop. MovingDown and MovingUp are different states
            // so that the stopping algorigthm can be this simple and I don't have to design a controller to track
            // the predicted ball position.
            if (paddleCenter >= enemyCmp->predictedBallPosition)
            {
                velCmp->velocity.y = 0.f;
            }
        }
        break;
    }
    case EnemyComponent::AIState::MovingUp:
    {
        // if the ball has started moving away from us, we bounced it
        //   and need to wait for the player to move
        if (ballVelCmp->velocity.x < 0)
        {
            enemyCmp->predictionValid = false; // Stop listening to the prediction
            enemyCmp->aiState = EnemyComponent::AIState::WaitingForPlayer;
        }
        else // The ball is still moving towards us
        {
            float paddleCenter = locCmp->location.top + (locCmp->location.height / 2.f);
            // If we are now at or above the prediction, we can stop. MovingDown and MovingUp are different states
            // so that the stopping algorigthm can be this simple and I don't have to design a controller to track
            // the predicted ball position.
            if (paddleCenter <= enemyCmp->predictedBallPosition)
            {
                velCmp->velocity.y = 0.f;
            }
        }
        break;
    }
    }
}

float EnemyAISystem::predictImpactPosition(sf::FloatRect &paddlePosition, sf::FloatRect &ballPosition, sf::Vector2f &ballVelocity, float uncertaintyScale)
{
    // We will do all this math in "usuable screenspace coordinates", which are just game coordinates with the origin shifted
    // to where the ball will bounce off of (Game::WORLD_BORDER - 2, Game::WORLD_BORDER - 2) and the maximum extent of the axes
    // at (Game::WORLD_WIDTH, Game::WORLD_HEIGHT) with twice that value taken off.
    float usableScreenHeight = Game::WORLD_HEIGHT - (2.f * Game::WORLD_BORDER) + 4.f; // 4 is twice the magic impact buffer from the ball system

    // Get some reference positions in general world coordinates
    float paddleLeftEdgeWorldCoords = paddlePosition.left;
    float ballRightEdgeWorldCoords = ballPosition.left + ballPosition.width;
    float ballTopWorldCoords = ballPosition.top;

    // Shift reference values to usable coordinates
    float paddleLeftEdgeUsableCoords = paddleLeftEdgeWorldCoords - ballRightEdgeWorldCoords;
    float ballRightEdgeUsableCoords = ballRightEdgeWorldCoords - ballRightEdgeWorldCoords; // 0, but establishing pattern
    float ballTopUsableCoords = ballTopWorldCoords - (Game::WORLD_BORDER - 2.f);
    float bottomUsableCoords = usableScreenHeight - ballPosition.height;

    // Compute where on the right wall the ball would land if there were no top or bottom walls to bounch off of with d = vt
    float distanceToPaddle = paddleLeftEdgeUsableCoords - ballRightEdgeUsableCoords;
    float timeToPaddle = distanceToPaddle / ballVelocity.x; // t = d / v, x-axis
    float yTravel = ballVelocity.y * timeToPaddle;
    float virtualImpactPos = ballTopUsableCoords + yTravel;

    bool fromTop = true; // !fromTop implies fromBottom
    float prediction = 0.f;
    if (virtualImpactPos > 0) // impact below the top of screen - maybe off the bottom
    {
        // Each iteration through this loop computes a "bounce" the ball will do. 'fromTop' keeps an eye on which surface the last bounce
        // will be from while the virtualImpactPos becomes how far from that surface the ball will impact. As we are projecting below the
        // bottom of the screen (if it bounces one or more times), virtualImpactPos will stay positive and represent travel away from the
        // last surface, which we can get by looking at 'fromTop'
        fromTop = true;
        // While our projected "next bounce" is still off screen
        while (virtualImpactPos > bottomUsableCoords)
        {
            // Bounce
            virtualImpactPos -= bottomUsableCoords;
            fromTop = !fromTop;
        }

        if (fromTop)
        {
            // We last bounced off the top, so our prediction is the top in world coordinates added to our excess distance travelled,
            // which is still stored in virtualImpactPos. Additional travel downward is positive, so we add virtualImpactPos
            // (which is positive).
            prediction = (Game::WORLD_BORDER - 2.f) + virtualImpactPos; // There's that magic '2' from the physics bouncing again
        }
        else //! fromTop implies fromBottom
        {
            // We last bounced off the bottom, so our prediction is the bottom in world coordinates minus our excess distance travelled,
            // which is still stored in virtualImpactPos. Additional travel upward is negative, so we subtract virtualImpactPos
            // (which is positive).
            prediction = (Game::WORLD_HEIGHT - Game::WORLD_BORDER + 2.f) - virtualImpactPos; // There's that magic '2' from the physics bouncing again
        }
    }
    else // virtualImpactPos <= 0 - impact off the top of the screen
    {
        // Each iteration through this loop computes a "bounce" the ball will do. It is very similar to the virtualImpactPos > 0 algorightm
        // abmove. The variable 'fromTop' keeps an eye on which surface the last bounce will be from while the virtualImpactPos becomes how far
        // from that surface the ball will impact. As we are projecting above the top of the screen (if it bounces one or more times), virtualImpactPos
        // will stay negative and represent travel towards from the last surface (or -1 times travel away from the last surface, whichever is conceptually
        // easier for the reader), which we can get by looking at 'fromTop'
        fromTop = true;
        // While our projected "next bounce" is still off screen
        while (virtualImpactPos < (-1.f * bottomUsableCoords))
        {
            // bounce
            virtualImpactPos += bottomUsableCoords;
            fromTop = !fromTop;
        }

        if (fromTop)
        {
            // We last bounced off the top, so our prediction is the top in world coordinates plus our excess distance travelled,
            // which is still stored in virtualImpactPos. Additional travel downward is positive, so we subtract virtualImpactPos
            // (which is negative).
            prediction = (Game::WORLD_BORDER - 2.f) - virtualImpactPos; // There's that magic '2' from the physics bouncing again
        }
        else
        {
            // We last bounced off the bottom, so our prediction is the bottom in world coordinates minus our excess distance travelled,
            // which is still stored in virtualImpactPos. Additional travel upward is negative, so we add virtualImpactPos
            // (which is negative).
            prediction = (Game::WORLD_HEIGHT - Game::WORLD_BORDER + 2.f) + virtualImpactPos; // There's that magic '2' from the physics bouncing again
        }
    }

    // To make the AI imperfect, we add an amount of error randomly selected from a uniform distrubtion in the range
    // [-uncertaintyScale, uncertaintyScale]
    // TODO: Make the distribution normal.
    float error = ((rand() / static_cast<float>(RAND_MAX)) * uncertaintyScale * 2.f) - uncertaintyScale;

    return prediction + error;
}

const std::string EnemyComponent::ENEMY_ID = "ENEMY_ID";
const sf::Time EnemyComponent::REACTION_TIME = sf::seconds(0.25f); // This is the same as typical human reaction time to a visual cue
const float EnemyComponent::ENEMY_ERROR_SCALE = 85.f;              // This is half a paddle + 10px.
EnemyComponent::EnemyComponent() : Component(ENEMY_ID),
                                   reactionElapsedTime(sf::Time::Zero),
                                   aiState(EnemyComponent::AIState::WaitingForPlayer),
                                   predictedBallPosition((float)Game::WORLD_HEIGHT / 2.f),
                                   predictionValid(false)
{
}