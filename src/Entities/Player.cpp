#include "Unit.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SharedDefines.h"

Player::Player(Game* _game, int index, std::string texture) : Unit(_game, texture), PlayerNumber(index)
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
        {
            if (!Vehicle)
            {
                LoadMoveTexture(2);
                Velocity.x = -Common::HorizontalMoveSpeed;
            }
            else
                Velocity.x += -Common::HorizontalMoveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (!Vehicle)
            {
                LoadMoveTexture(1);
                Velocity.x = Common::HorizontalMoveSpeed;
            }
            else
                Velocity.x += Common::HorizontalMoveSpeed;
        }
        else
        {
            LoadMoveTexture(0);
            if (!Vehicle)
                StopHorizontalMovement();
        }
    }
    else if (PlayerNumber == 1)
    {
        // Handle movement for player 2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            Velocity.x = -Common::HorizontalMoveSpeed;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            Velocity.x = Common::HorizontalMoveSpeed;
        else
            StopHorizontalMovement();
    }
    
    //std::cout << "Velocity: X: " << Velocity.x << " Y: " << Velocity.y << std::endl;

    Unit::Update(diff);
}

void Player::LoadMoveTexture(int type)
{
    if (type == 0)
    {
        // Load still texture
        texture = sResourceManager->GetTexture(TextureName);
    }
    else if (type == 1)
    {
        // Moving right texture
        texture = sResourceManager->GetTexture("p1/p1_walk03.png");
    }
    else if (type == 2)
    {
        // Moving left texture
        texture = sResourceManager->GetTexture("p1/p1_walk03_left.png");
    }
    sprite.setTexture(texture);
}
