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
            static bool IsControlledPlayer(Game::Player const &);
            static u64 preGotByPlayer_(Game::Player *);
            static u64 gotByPlayer_(Game::Player *);
            // static u64 gotByEnemy_(Game::Enemy *);
        };
    }; // namespace Coop
};     // namespace Game
