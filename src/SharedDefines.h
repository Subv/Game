#ifndef SHARED_DEFINES_H
#define SHARED_DEFINES_H

enum TypeId
{
    TYPEID_PLAYER,
    TYPEID_CREATURE,
    TYPEID_OBJECT,
    TYPEID_ENTITY
};

namespace Common
{
    extern const int DefaultHealthPoints;
    extern const float GravityAcceleration;

    extern const float TerminalVerticalSpeed;
    extern const float TerminalHorizontalSpeed;

    extern const float HorizontalBrakeAcceleration;
    extern const float HorizontalMoveAcceleration;

    extern const float JumpVelocity;
}

#endif