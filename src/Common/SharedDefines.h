#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H

enum TypeId
{
    TYPEID_ENTITY,
    TYPEID_UNIT,
    TYPEID_PLAYER,
    TYPEID_CREATURE,
    TYPEID_OBJECT,
    TYPEID_TILE
};

namespace Common
{
    extern const std::string KeyBindingsFile;

    extern const unsigned int NumPlayers;
    extern const unsigned int MaxPlayers;

    extern const int DefaultHealthPoints;
    extern const float GravityAcceleration;

    extern const float TerminalVerticalSpeed;
    extern const float TerminalHorizontalSpeed;

    extern const float HorizontalMoveSpeed;

    extern const float JumpVelocity;
}

#endif