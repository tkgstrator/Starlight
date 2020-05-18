#pragma once

#include "types.h"

namespace Game
{
namespace Coop
{
class Player
{
    public:
    uint32_t mRoundBankedPowerIkuraNum;
    uint32_t mGotGoldenIkuraNum;
    uint32_t mRoundBankedGoldenIkuraNum;
    uint32_t mTotalBankedGoldenIkuraNum;
    uint32_t _0x10;
    _BYTE gap1[0x1C];
    uint32_t mTotalRobbedGoldenIkuraNum;
    _BYTE gap2[0xCC];
};

class PlayerDirector
{
    public:
    _BYTE gap[0x370];
    Game::Coop::Player player[4];
};

} // namespace Coop
} // namespace Game