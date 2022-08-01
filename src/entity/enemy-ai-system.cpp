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
    EnemyComponent *enemyCmp = dynamic_cast<EnemyComponent *>(ai->getComponent(EnemyComponent::ENEMY_ID).get());
    LocationComponent *locCmp = dynamic_cast<LocationComponent *>(ai->getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *velCmp = dynamic_cast<VelocityComponent *>(ai->getComponent(VelocityComponent::VEL_COMP_ID).get());

    LocationComponent *ballLocCmp = dynamic_cast<LocationComponent *>(_ball.getComponent(LocationComponent::LOC_COMP_ID).get());
    VelocityComponent *ballVelCmp = dynamic_cast<VelocityComponent *>(_ball.getComponent(VelocityComponent::VEL_COMP_ID).get());

    switch (enemyCmp->aiState)
    {
    case EnemyComponent::AIState::WiatingForPlayer:
    {
        // If the ball starts moving towards us, react
        if (ballVelCmp->velocity.x > 0)
        {
            enemyCmp->aiState = EnemyComponent::AIState::Reacting;
        }
        break;
    }
    case EnemyComponent::AIState::Reacting:
    {
        // If we don't already have a prediction, make one
        if (!enemyCmp->predictionValid)
        {
            enemyCmp->predictedBallPosition = predictImpactPosition(locCmp->location, ballLocCmp->location, ballVelCmp->velocity, 90.f);
            enemyCmp->predictionValid = true;
        }

        // Check if we're done waiting
        enemyCmp->reactionElapsedTime += deltaTime;
        if (enemyCmp->reactionElapsedTime > EnemyComponent::REACTION_TIME)
        {
            enemyCmp->reactionElapsedTime = sf::Time::Zero; // Reset the counter for the next time
            float paddleCenter = locCmp->location.top + (locCmp->location.height / 2.f);

            if (paddleCenter > enemyCmp->predictedBallPosition)
            {
                // We are below the predicted location
                velCmp->velocity.y = Game::PADDLE_SPEED * -1.f;
                enemyCmp->aiState = EnemyComponent::AIState::MovingUp;
            }
            else if (paddleCenter <= enemyCmp->predictedBallPosition)
            {
                // We are above the predicted location
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
            enemyCmp->predictionValid = false;
            enemyCmp->aiState = EnemyComponent::AIState::WiatingForPlayer;
        }
        else
        {
            float paddleCenter = locCmp->location.top + (locCmp->location.height / 2.f);
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
            enemyCmp->predictionValid = false;
            enemyCmp->aiState = EnemyComponent::AIState::WiatingForPlayer;
        }
        else
        {
            float paddleCenter = locCmp->location.top + (locCmp->location.height / 2.f);
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
    float usableScreenHeight = Game::WORLD_HEIGHT - (2.f * Game::WORLD_BORDER) + 4.f; // 4 is twice the magic impact buffer from the ball system

    // Convert to "Usable Screen Space" coordinates
    float paddleLeftEdgeWorldCoords = paddlePosition.left;
    float ballRightEdgeWorldCoords = ballPosition.left + ballPosition.width;
    float ballTopWorldCoords = ballPosition.top;

    float paddleLeftEdgeUsableCoords = paddleLeftEdgeWorldCoords - ballRightEdgeWorldCoords;
    float ballRightEdgeUsableCoords = ballRightEdgeWorldCoords - ballRightEdgeWorldCoords; // 0, but establishing pattern
    float ballTopUsableCoords = ballTopWorldCoords - (Game::WORLD_BORDER - 2.f);
    float bottomUsableCoords = usableScreenHeight - ballPosition.height;

    float distanceToPaddle = paddleLeftEdgeUsableCoords - ballRightEdgeUsableCoords;
    float timeToPaddle = distanceToPaddle / ballVelocity.x;

    float yTravel = ballVelocity.y * timeToPaddle;
    float virtualImpactPos = ballTopUsableCoords + yTravel;

    bool fromTop; // !fromTop implies fromBottom
    float prediction;
    if (virtualImpactPos > 0) // impact below the top of screen - maybe off the bottom
    {
        fromTop = true;
        while (virtualImpactPos > bottomUsableCoords)
        {
            // Bounce
            virtualImpactPos -= bottomUsableCoords;
            fromTop = !fromTop;
        }

        if (fromTop)
        {
            prediction = virtualImpactPos + Game::WORLD_BORDER - 2.f;
        }
        else
        {
            prediction = Game::WORLD_HEIGHT - Game::WORLD_BORDER + 2.f - virtualImpactPos;
        }
    }
    else // virtualImpactPos <= 0 - impact off the top of the screen
    {
        fromTop = true;
        while (virtualImpactPos < (-1.f * bottomUsableCoords))
        {
            // bounce
            virtualImpactPos += bottomUsableCoords;
            fromTop = !fromTop;
        }

        if (fromTop)
        {
            prediction = Game::WORLD_BORDER - 2.f - virtualImpactPos;
        }
        else
        {
            prediction = Game::WORLD_HEIGHT - Game::WORLD_BORDER + 2.f + virtualImpactPos;
        }
    }

    float error = ((rand() / static_cast<float>(RAND_MAX)) * uncertaintyScale * 2.f) - uncertaintyScale;

    return prediction + error;
}

const std::string EnemyComponent::ENEMY_ID = "ENEMY_ID";
const sf::Time EnemyComponent::REACTION_TIME = sf::seconds(0.4f);
EnemyComponent::EnemyComponent() : Component(ENEMY_ID),
                                   reactionElapsedTime(sf::Time::Zero),
                                   aiState(EnemyComponent::AIState::WiatingForPlayer),
                                   predictedBallPosition((float)Game::WORLD_HEIGHT / 2.f),
                                   predictionValid(false)
{
}