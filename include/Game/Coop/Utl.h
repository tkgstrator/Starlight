#pragma once

#include "types.h"
#include "Game/Player/Player.h"

namespace Game
{
namespace Coop
{
class Utl
{
public:
    static bool IsControlledPlayer(Game::Player const &);
    static u64 GetWaterLevel();
    static u64 GetDifficulty();
    static u64 GetRoundNum();
    static u64 GetEventType();
    static u64 CountActivePlayer();
    /* ... */
};
}; // namespace Coop
}; // namespace Game
