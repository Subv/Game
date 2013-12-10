#include "Unit.h"
#include "Utils.h"

Unit::Unit(Game* _game) : Entity(_game), jumping(false)
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

void Unit::Update(sf::Time const diff)
{
    // Stuff to keep in mind:
    // * The Y coordinate increases as we go down the screen, and decreases as we go up, hence the gravity must be positive for the characters to fall

    if (IsInAir())
        Acceleration.y = 40.f; // Gravity acceleration

    sf::Vector2f& newPos = NewPosition;

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
    if (Utils::CompareFloats(Velocity.x, 0.f) != Utils::COMPARE_EQUAL)
        newPos.x += Velocity.x * diff.asSeconds();
    
    if (Utils::CompareFloats(Velocity.y, 0.f) != Utils::COMPARE_EQUAL)
        newPos.y += Velocity.y * diff.asSeconds();

    Entity::Update(diff);
}

void Unit::StopMoving(sf::Vector2f alongAxis)
{
    if (alongAxis.x == 1.f) // Bounce when hitting a wall horizontally
    {
        Velocity.x *= -1.f;
        //Acceleration.x *= -1.f;
    }
    if (alongAxis.y == 1.f && !IsJumping())
    {
        Velocity.y = 0.f;
        if (IsInAir())
            Acceleration.y = 40.f;
        else
            Acceleration.y = 0.f;
    }
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

void Unit::Jump()
{
    if (!IsInAir() && !IsJumping())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Velocity.x > 0.f)
            Velocity.x *= -1.f;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Velocity.x < 0.f)
            Velocity.x *= -1.f;

        jumping = true;
        Velocity.y = -100.f;
    }
}
