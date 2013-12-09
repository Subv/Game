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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        Velocity.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        Velocity.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        Velocity.x += 1.0f;

    std::cout << "Velocity: X: " << Velocity.x << " Y: " << Velocity.y << std::endl;

    Unit::Update(diff);
}

void Player::LoadTexture()
{
    texture = sResourceManager->GetTexture("p1_front.png");
    sprite.setTexture(texture);
    sprite.setPosition(Position);
}
