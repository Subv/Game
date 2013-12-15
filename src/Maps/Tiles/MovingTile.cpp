#include "MovingTile.h"
#include "Player.h"
#include <iostream>
#include <set>

MovingTile::MovingTile(Game* _game, int x, int y, std::string model) : SpecialTile(_game, x, y, model)
{
    Velocity.x = 200.f;
    Displacement = 0.f;
}

MovingTile::~MovingTile()
{

}

void MovingTile::Update(sf::Time const diff)
{
    Displacement += abs(Velocity.x * 0.02f);

    if (Displacement > 350.f)
        StopHorizontalMovement(); // Changes the direction of the movement and resets the displacement counter

    // We have to manually update the position here bypassing the velocity
    NewPosition.x += Velocity.x * 0.02f;

    // Update our passengers, move them with us
    for (std::set<Entity*>::iterator itr = Passengers.begin(); itr != Passengers.end(); ++itr)
        (*itr)->Velocity.x = Velocity.x;
    
    SpecialTile::Update(diff);
}

void MovingTile::OnTopCollision(Entity* collider, sf::FloatRect intersection)
{
    SpecialTile::OnTopCollision(collider, intersection);

    EmitParticle(sf::milliseconds(500), false);
    if (collider->IsUnit())
        collider->ToUnit()->Vehicle = this;

    Passengers.insert(collider);
}

void MovingTile::LeaveCollision(Entity* collider)
{
    if (Passengers.find(collider) == Passengers.end())
        return;

    if (collider->IsUnit())
        collider->ToUnit()->Vehicle = nullptr;

    Passengers.erase(collider);
}

void MovingTile::StopHorizontalMovement()
{
    Velocity.x *= -1.f;
    Displacement = 0.f;
}

void MovingTile::StopVerticalMovement()
{
    Velocity.y *= -1.f;
    Displacement = 0.f;
}

void MovingTile::HandleFloor(Entity* entity, bool& floor)
{
    // Just in case that the entity didn't actually fall upon us, but instead walked at the same height level
    if (Passengers.find(entity) == Passengers.end())
    {
        if (entity->IsUnit())
            entity->ToUnit()->Vehicle = this;
        Passengers.insert(entity);
    }

    SpecialTile::HandleFloor(entity, floor);
}
