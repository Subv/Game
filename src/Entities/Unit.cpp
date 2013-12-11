#include "Unit.h"
#include "SharedDefines.h"
#include "ResourceManager.h"
#include "Utils.h"

Unit::Unit(Game* _game, std::string model) : Entity(_game, model), jumping(false)
{
    Type = TYPEID_UNIT;
    HealthPoints = Common::DefaultHealthPoints;
}

Unit::~Unit()
{

}

void Unit::Update(sf::Time const diff)
{
    // Stuff to keep in mind:
    // * The Y coordinate increases as we go down the screen, and decreases as we go up, hence the gravity must be positive for the characters to fall

    if (IsInAir())
        Acceleration.y = Common::GravityAcceleration;

    NewPosition = Position;
    sf::Vector2f& newPos = NewPosition;

    // Update the velocity
    Velocity.x += Acceleration.x * diff.asSeconds();
    Velocity.y += Acceleration.y * diff.asSeconds();

    if (Velocity.x > Common::TerminalHorizontalSpeed) // Terminal horizontal velocity
        Velocity.x = Common::TerminalHorizontalSpeed;
    else if (Velocity.x < -Common::TerminalHorizontalSpeed) // Terminal horizontal velocity
        Velocity.x = -Common::TerminalHorizontalSpeed;

    if (Velocity.y > Common::TerminalVerticalSpeed) // Terminal vertical velocity
        Velocity.y = Common::TerminalVerticalSpeed;

    // Update the position
    if (Utils::CompareFloats(Velocity.x, 0.f) != Utils::COMPARE_EQUAL)
        newPos.x += Velocity.x * diff.asSeconds();
    
    if (Utils::CompareFloats(Velocity.y, 0.f) != Utils::COMPARE_EQUAL)
        newPos.y += Velocity.y * diff.asSeconds();

    Entity::Update(diff);
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
        Velocity.y = -Common::JumpVelocity;
    }
}
