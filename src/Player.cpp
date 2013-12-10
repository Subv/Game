#include "Unit.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SharedDefines.h"

Player::Player(Game* _game, int index) : Unit(_game), PlayerNumber(index)
{
    Type = TYPEID_PLAYER;
}

Player::~Player()
{

}

void Player::Update(sf::Time const diff)
{
    if (PlayerNumber == 0)
    {
        // Handle movement for player 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            Acceleration.x = -Common::HorizontalMoveAcceleration;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            Acceleration.x = Common::HorizontalMoveAcceleration;
        else
            Brake();
    }
    else if (PlayerNumber == 1)
    {
        // Handle movement for player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            Acceleration.x = -Common::HorizontalMoveAcceleration;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            Acceleration.x = Common::HorizontalMoveAcceleration;
        else
            Brake();
    }
    
    //std::cout << "Velocity: X: " << Velocity.x << " Y: " << Velocity.y << std::endl;

    Unit::Update(diff);
}

void Player::LoadTexture()
{
    texture = sResourceManager->GetTexture("p1_front.png");
    sprite.setTexture(texture);
    sprite.setPosition(Position);
}
