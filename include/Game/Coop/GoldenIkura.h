#pragma once

#include "types.h"
#include "Game/Player/Player.h"

namespace Game
{
    namespace Coop
    {
        class GoldenIkura
        {
        public:
            GoldenIkura();
            ~GoldenIkura();
            static bool IsControlledPlayer(Game::Player const &);
            static bool isGettableByEnemy();
            static u64 lost();
            static u64 got_();
            static u64 preGotByPlayer_(Game::Player *);
            static u64 gotByPlayer_(Game::Player *);
            // static u64 gotByEnemy_(Game::Enemy *);
        };

    }; // namespace Coop

}; // namespace Game
