#include "Unit.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SharedDefines.h"
#include "Game.h"
#include "Input.h"

Player::Player(Game* _game, int index, std::string texture) : Unit(_game, texture), PlayerNumber(index), Coins(0)
{
    Type = TYPEID_PLAYER;
}

Player::~Player()
{

}

void Player::Update(sf::Time const diff)
{
    if (game->InputHandler.IsActive(PlayerNumber, ACTION_JUMP))
        Jump();

    // Handle movement
    if (game->InputHandler.IsActive(PlayerNumber, ACTION_MOVE_LEFT))
    {
        if (!Vehicle)
        {
            LoadMoveTexture(2);
            Velocity.x = -Common::HorizontalMoveSpeed;
        }
        else
            Velocity.x += -Common::HorizontalMoveSpeed;
    }
    else if (game->InputHandler.IsActive(PlayerNumber, ACTION_MOVE_RIGHT))
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
