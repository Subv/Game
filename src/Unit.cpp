#include "Unit.h"

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

    if (Velocity.x > 0 || Velocity.x < 0)
        Acceleration.x = -10.f * ((0 < Velocity.x) - (Velocity.x < 0)); // Friction by air horizontally

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