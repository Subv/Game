#include "Unit.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SharedDefines.h"

Player::Player(Game* _game) : Unit(_game)
{
    Type = TYPEID_PLAYER;
}

Player::~Player()
{

}

void Player::Update(sf::Time diff)
{
    // Handle movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        Position.y += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        Position.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        Position.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        Position.x += 1.0f;

    Entity::Update(diff);
}

void Player::LoadTexture()
{
    texture = sResourceManager->GetTexture("p1_front.png");
    sprite.setTexture(texture);
    sprite.setPosition(Position);
}