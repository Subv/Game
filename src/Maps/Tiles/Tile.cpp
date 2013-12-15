#include <SFML/Graphics/Sprite.hpp>
#include "Entity.h"
#include "Tile.h"
#include "SpecialTile.h"
#include "Utils.h"
#include "Unit.h"

#include "Game.h"

Tile::Tile(Game* _game, int x, int y, int z, bool collides, std::string model) : Entity(_game, model), X(x), Y(y), Z(z), Collidable(collides)
{
    Type = TYPEID_TILE;
}

Tile::~Tile()
{
}

bool Tile::Intersects(sf::FloatRect& check, sf::FloatRect& intersection) const
{
    if (TextureName == "castleHillRight.png")
    {
        // Ok, this is a slope, the slope angle is 45°, do we intersect?

        if (!check.intersects(sprite.getGlobalBounds()))
            return false;

        // If we are outside the tile, we don't intersect
        if (check.left + check.width < Position.x)
            return false;
        if (check.top + check.height < Position.y)
            return false;

        float x = Position.x + check.top + check.height + Position.y + GetWidth();

        if (check.top + check.height > Position.y + GetHeight() / 2.f)
            x += 1051.f;
        else
            x -= 1051.f;

        // To find the y, we have to replace x in one of the two equations
        float y = check.top + check.height;

        // The lines intersect at (x, y)

        intersection.top = check.top;
        intersection.height = check.height;
        intersection.left = x;
        sf::RectangleShape rect;
        rect.setPosition(x, y);
        rect.setSize(sf::Vector2f(10.f, 5.f));
        game->GetWindow().draw(rect);
        return true;
    }
    else
        return sprite.getGlobalBounds().intersects(check, intersection);
}

SpecialTile* Tile::ToSpecialTile()
{
    if (IsSpecial())
        return reinterpret_cast<SpecialTile*>(this);
    return nullptr;
}

bool Tile::IntersectTop(Entity* entity, sf::FloatRect check) const
{
    if (TextureName == "castleHillRight.png")
    {
        bool tops = entity->GetPositionY() + entity->GetHeight() > (-Position.x + Position.y);
        return tops;
    }
    return Utils::CompareFloats(check.top + check.height, GetPositionY()) == Utils::COMPARE_GREATER_THAN &&
            Utils::CompareFloats(check.top + check.height, GetPositionY() + GetHeight()) == Utils::COMPARE_LESS_THAN &&
            Utils::CompareFloats(entity->GetPositionY() + entity->GetHeight(), GetPositionY(), 10.f) == Utils::COMPARE_EQUAL;
}

bool Tile::IntersectSide(Entity* entity, sf::FloatRect check) const
{
    if (TextureName == "castleHillRight.png")
        return false;
    return Utils::CompareFloats(check.top, GetPositionY() + GetHeight() / 2.f) == Utils::COMPARE_LESS_THAN && // If the player is at least halfway below the tile, don't collide
            ((Utils::CompareFloats(check.left + check.width, GetPositionX()) == Utils::COMPARE_GREATER_THAN &&
            Utils::CompareFloats(check.left + check.width, GetPositionX() + GetWidth()) == Utils::COMPARE_LESS_THAN) ||
            (Utils::CompareFloats(check.left, GetPositionX() + GetWidth()) == Utils::COMPARE_LESS_THAN &&
            Utils::CompareFloats(check.left, GetPositionX()) == Utils::COMPARE_GREATER_THAN));
}

void Tile::OnTopCollision(Entity* collider, sf::FloatRect intersection)
{
    if (TextureName == "castleHillRight.png")
    {
        collider->StopVerticalMovement();
        collider->NewPosition.y = -Position.x + Position.y - collider->GetHeight() + 1.f;
        return;
    }
    // We touched the top part of the tile, stop falling
    collider->StopVerticalMovement();
    collider->NewPosition.y = intersection.top - collider->GetHeight() + 1.f; // Don't go too low, correct the position if that happens
}

void Tile::HandleFloor(Entity* entity, bool& floor)
{
    if (TextureName == "castleHillRight.png")
        return;
    floor = true;

    if (Unit* unit = entity->ToUnit())
        unit->jumping = false;
}

void Tile::OnLeftCollision(Entity* collider)
{

}

void Tile::OnRightCollision(Entity* collider)
{

}
