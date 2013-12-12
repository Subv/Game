#include "MovingTile.h"
#include "Player.h"
#include <iostream>
#include <set>

MovingTile::MovingTile(Game* _game, int x, int y, std::string model) : SpecialTile(_game, x, y, model)
{
    Velocity.x = -200.f;
    Displacement = 0.f;
}

MovingTile::~MovingTile()
{

}

void MovingTile::Update(sf::Time const diff)
{
    Displacement += abs(Velocity.x * 0.02f);

    if (Displacement > 100.f)
    {
        Displacement = 0.f;
        Velocity.x *= -1.f;
    }

    // We have to manually update the position here bypassing the velocity
    NewPosition.x += Velocity.x * 0.02f;

    // Update our passengers, move them with us
    for (std::set<Entity*>::iterator itr = Passengers.begin(); itr != Passengers.end(); ++itr)
        (*itr)->Velocity.x = Velocity.x;
    std::cout << "Adding velocity to " << Passengers.size() << std::endl;
    SpecialTile::Update(diff);
}

void MovingTile::OnTopCollision(Entity* collider)
{
    std::cout << "Entity boarded me" << std::endl;

    if (collider->GetTypeId() == TYPEID_PLAYER)
        reinterpret_cast<Player*>(collider)->Vehicle = this;

    Passengers.insert(collider);
}

void MovingTile::LeaveCollision(Entity* collider)
{
    if (collider->GetTypeId() == TYPEID_PLAYER)
        reinterpret_cast<Player*>(collider)->Vehicle = nullptr;

    Passengers.erase(collider);
}
