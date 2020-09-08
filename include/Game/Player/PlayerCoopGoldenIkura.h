#pragma once

#include "types.h"
#include "Game/Player/Player.h"

namespace Game
{
    class PlayerCoopGoldenIkura : public Cmn::Actor
    {
    public:
        PlayerCoopGoldenIkura();
        ~PlayerCoopGoldenIkura();
        // Game::Player *mPlayer;
        // Game::PlayerModel *mPlayerModel;
        _DWORD mOnActive;
        _QWORD mAnimSetController; // Game::AnimSetController
    };
}; // namespace Game
