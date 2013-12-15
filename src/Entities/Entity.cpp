#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Unit.h"
#include "Player.h"
#include "Utils.h"
#include "Map.h"
#include "Tile.h"
#include "SpecialTile.h"
#include "SharedDefines.h"

Entity::Entity(Game* _game, std::string model) : game(_game), inAir(true), TextureName(model)
{
    Type = TYPEID_ENTITY;
    NewPosition = Position;

    // Reset the movement
    Velocity.x = 0.0f;
    Velocity.y = 0.0f;
    Acceleration.x = 0.0f;
    Acceleration.y = 0.0f;

    // Setup the particle system
    ParticleSystem.setTexture(sResourceManager->GetTexture("particle.png"));

    // Add particle affectors
    ParticleSystem.addAffector(thor::TorqueAffector(100.f));
    ParticleSystem.addAffector(thor::ForceAffector(sf::Vector2f(0.f, Common::GravityAcceleration)));
}

Entity::~Entity()
{

}

void Entity::Draw()
{
    game->GetWindow().draw(sprite);
    game->GetWindow().draw(ParticleSystem);
}

void Entity::Update(sf::Time const diff)
{
    if (!map)
        return;

    ParticleEmitter.setParticlePosition(GetCenter());
    ParticleSystem.update(diff);

    // Now we do collision detection and determine if we can actually move there
    std::list<CollisionInfo> collisions;
    bool collides = map->HasCollisionAt(NewPosition, this, collisions);

    bool floor = false;
    for (std::list<CollisionInfo>::const_iterator itr = collisions.begin(); itr != collisions.end(); ++itr)
    {
        CollisionInfo const& collision = *itr;

        if (collision.Block == this) // Don't collide with yourself
            continue;

        if (game->DebugEnabled())
        {
            sf::RectangleShape rect2(sf::Vector2f(collision.Block->GetWidth(), collision.Block->GetHeight()));
            rect2.setPosition(collision.Block->GetPositionX(), collision.Block->GetPositionY());
            rect2.setOutlineColor(sf::Color::Blue);
            rect2.setFillColor(sf::Color::Transparent);
            rect2.setOutlineThickness(3.f);
            game->GetWindow().draw(rect2);

            sf::RectangleShape rect(sf::Vector2f(collision.Intersection.width, collision.Intersection.height));
            rect.setPosition(collision.Intersection.left, collision.Intersection.top);
            game->GetWindow().draw(rect);
        }

        // Detect vertical collisions
        if (collision.Block->IntersectTop(this, collision.Intersection))
        {
            collision.Block->HandleFloor(this, floor);

            // Check that we're actually heading towards the tile
            if (Velocity.y > 0.f)
            {
                collision.Block->OnTopCollision(this, collision.Intersection);
                
                if (Type == TYPEID_PLAYER)
                    std::cout << "Top collision" << std::endl;
            }
        }
        // Detect horizontal collisions
        else if (collision.Block->IntersectSide(this, collision.Intersection))
        {
            if (Utils::CompareFloats(Velocity.x, 0.f) == Utils::COMPARE_GREATER_THAN &&
                Utils::CompareFloats(collision.Intersection.left + collision.Intersection.width, collision.Block->GetPositionX(), 10.f) == Utils::COMPARE_EQUAL) // If we already trespassed the tile, don't bother with collision handling, for example if the player jumped from below
            {
                // We are colliding horizontally with the left side of a tile
                StopHorizontalMovement();
                NewPosition.x = collision.Block->GetPositionX() - sprite.getGlobalBounds().width; // Move back a bit
                if (Type == TYPEID_PLAYER)
                    std::cout << "Left collision" << std::endl;
            }
            else if (Utils::CompareFloats(Velocity.x, 0.f) == Utils::COMPARE_LESS_THAN &&
                Utils::CompareFloats(collision.Intersection.left, collision.Block->GetPositionX() + collision.Block->GetWidth(), 10.f) == Utils::COMPARE_EQUAL)
            {
                // We are colliding horizontally with the right side of a tile
                StopHorizontalMovement();
                NewPosition.x = collision.Block->GetPositionX() + collision.Block->GetWidth(); // Move back a bit
                if (Type == TYPEID_PLAYER)
                    std::cout << "Right collision" << std::endl;
            }
        }
    }


    // Now we perform Entity-Entity collision detection, these collisions don't stop movement, they are used for events like eating coins, bullet hit detection, etc.
    for (auto& entity : game->Entities)
        if (entity->Intersects(this))
            entity->HandleCollision(this);

    Position.x = NewPosition.x;
    Position.y = NewPosition.y;

    inAir = !floor;

    sprite.setPosition(Position);

    Draw();
}

Unit* Entity::ToUnit()
{
    if (IsUnit())
        return dynamic_cast<Unit*>(this);
    return nullptr;
}

Player* Entity::ToPlayer()
{
    if (GetTypeId() == TYPEID_PLAYER)
        return dynamic_cast<Player*>(this);
    return nullptr;
}

void Entity::SetPosition(sf::Vector2f pos)
{
    Position = pos;
    NewPosition = pos;
    sprite.setPosition(Position);
}

void Entity::LoadTexture()
{
    if (Type != TYPEID_TILE)
        texture = sResourceManager->GetTexture(TextureName);
    else
        texture = sResourceManager->GetTile(TextureName);

    sprite.setTexture(texture);
    sprite.setPosition(Position);
}

void Entity::StopHorizontalMovement()
{
    Velocity.x = 0.f;
    Acceleration.x = 0.f;
}

void Entity::StopVerticalMovement()
{
    Velocity.y = 0.f;
    Acceleration.y = 0.f;
}

void Entity::EmitParticle(sf::Time const span, bool up)
{
    float verticalModifier = up ? -1.f : 1.f;
    ParticleEmitter.setEmissionRate(30.f);
    ParticleEmitter.setParticleLifetime(sf::seconds(5.f));
    ParticleEmitter.setParticleVelocity(thor::Distributions::deflect(thor::PolarVector2f(sf::Vector2f(0.f, verticalModifier * Common::JumpVelocity)), 40.f));
    ParticleSystem.addEmitter(thor::refEmitter(ParticleEmitter), span);
}

sf::Vector2f Entity::GetCenter() const
{
    return sf::Vector2f(Position.x + GetWidth() / 2.f, Position.y + GetHeight() / 2.f);
}

void Entity::Flicker(sf::Time const span)
{
    
}

bool Entity::Intersects(Entity const* other) const
{
    return sprite.getGlobalBounds().intersects(other->sprite.getGlobalBounds());
}

void Entity::RemoveFromWorld()
{
    game->GetCurrentMap()->AddToRemoveQueue(this);
}
