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
        class EnemyArray
        {
        public:
            sead::PtrArrayImpl ptrArray;
            char mBuffer;
            _BYTE gap_0x11[183];
        };

        class EnemyDirector : Cmn::Actor, sead::IDisposer
        {
        public:
            Game::Coop::EnemyArray mEnemyArray[3];
            _QWORD qword5C0;
            _DWORD dword5C8;
            sead::Random mRandom[2];
            _BYTE gap5EC[4];
            _QWORD qword5F0;
            _QWORD qword5F8;
            _QWORD qword600;
            _QWORD qword608;
            _QWORD qword610;
            _QWORD qword618;
            _DWORD dword620;
            _BYTE gap624[4];
            _QWORD qword628;
            _DWORD mEnemyAppearId;
            _BYTE gap634[100];
            _DWORD mActiveEnemyMax;
            _DWORD mActiveEnemyNum;
            _DWORD dword6A0;
            _DWORD dword6A4;
            _DWORD dword6A8;
            _DWORD dword6AC;
            uint64_t *qword6B0;
            _BYTE gap6A4[174];
            _DWORD dword76C;
            _QWORD qword770;
            _QWORD qword778;
            _QWORD qword780;
            _DWORD dword788;
        };
    }; // namespace Coop
};     // namespace Game
