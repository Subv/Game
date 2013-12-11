#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H

enum TypeId
{
    TYPEID_ENTITY,
    TYPEID_UNIT,
    TYPEID_PLAYER,
    TYPEID_CREATURE,
    TYPEID_OBJECT
};

namespace Common
{
    extern const int DefaultHealthPoints;
    extern const float GravityAcceleration;

    extern const float TerminalVerticalSpeed;
    extern const float TerminalHorizontalSpeed;

    extern const float HorizontalMoveSpeed;

    extern const float JumpVelocity;
}

#endif