#pragma once

#include "types.h"
#include "Lp/Sys/actor.h"
#include "Cmn/Actor.h"
#include "Lp/Utl.h"
#include "sead/random.h"
#include "sead/array.h"

namespace Game
{
namespace Coop
{
class EnemyDirector
{
};
class EventRally
{
    _BYTE gap[0x694];
};
class EventGeyser
{
public:
    /* ... */
    // Cmn::Actor *actor;
    // Lp::Utl::StateMachine *stateMachine;
    _BYTE gap[0x398];
    sead::Random random1;
    sead::Random random2;
    sead::PtrArrayImpl ptrArray;
    _QWORD goalPos;
    _QWORD dword3D0;
    _QWORD dword3D8;
};

class SpawnGeyser
{
public:
    _BYTE gap[0x39C];
    sead::Vector3<float> vector;
};

class EventDirector : Cmn::Actor
{
public:
    sead::IDisposer disposer;
    _BYTE eventNone[0x8];
    _BYTE eventRush[0x8];
    Game::Coop::EventGeyser *eventGeyser;
};
}; // namespace Coop
}; // namespace Game
