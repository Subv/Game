#include "Unit.h"
#include "Utils.h"

Unit::Unit(Game* _game) : Entity(_game)
{
    HealthPoints = 0;

    // Reset the movement
    Velocity.x = 0.0f;
    Velocity.y = 0.0f;
    Acceleration.x = 0.0f;
    Acceleration.y = 0.0f;
}

Unit::~Unit()
{

}

void Unit::Update(sf::Time diff)
{
    // Stuff to keep in mind:
    // * The Y coordinate increases as we go down the screen, and decreases as we go up, hence the gravity must be positive for the characters to fall

    if (IsInAir())
        Acceleration.y = 9.8f; // Gravity acceleration

    sf::Vector2f& newPos = Position;

    // Update the velocity
    Velocity.x += Acceleration.x * diff.asSeconds();
    Velocity.y += Acceleration.y * diff.asSeconds();

    if (Velocity.x > 160.0f) // Terminal horizontal velocity
        Velocity.x = 160.0f;
    else if (Velocity.x < -160.0f) // Terminal horizontal velocity
        Velocity.x = -160.0f;

    if (Velocity.y > 160.0f) // Terminal vertical velocity
        Velocity.y = 160.0f;

    // Update the position
    newPos.x += Velocity.x * diff.asSeconds();
    newPos.y += Velocity.y * diff.asSeconds();

    Entity::Update(diff);
}

void Unit::StopMoving()
{
    Velocity.y *= -1.0f;
}

void Unit::Brake()
{
    if (Utils::CompareFloats(Velocity.x, 0.f, 0.5f) == Utils::COMPARE_EQUAL)
    {
        Acceleration.x = 0.f;
        Velocity.x = 0.f;
    }
    else
    {
        Utils::ComparisonResult result = Utils::CompareFloats(Velocity.x, 0.f);
        if (result == Utils::COMPARE_GREATER_THAN)
            Acceleration.x = -15.0f;
        else if (result == Utils::COMPARE_LESS_THAN)
            Acceleration.x = 15.0f;
    }
}
