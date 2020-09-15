#pragma once

#include "types.h"
#include "sead/random.h"
#include "Game/EnemyBase.h"

namespace Game
{
    namespace Coop
    {
        class Enemy : Game::EnemyBase
        {
        public:
            _BYTE gap4[740];
            _QWORD qword2E8;
            _BYTE gap2F0[440];
            _QWORD qword4A8;
            _BYTE gap4B0[456];
            int actormixin678;
            _BYTE gap67C[36];
            _BYTE gap6A0[0x50]; // Lp::Utl::StateMachine
            _QWORD qword6F0;
            _QWORD qword6F8;
            _QWORD qword700;
            _QWORD qword708;
            _QWORD qword710;
            _QWORD qword718;
            _BYTE byte720;
            _BYTE gap721[3];
            sead::Random rnd;
            _DWORD dword734;
            _DWORD dword738;
            _DWORD dword73C;
            _DWORD dword740;
            _DWORD dword744;
            _QWORD qword748;
            _QWORD qword750;
            _QWORD qword758;
            _QWORD qword760;
            _QWORD qword768;
            _QWORD qword770;
            _BYTE byte778;
            _BYTE gap779[3];
            _DWORD dword77C;
            _DWORD dword780;
            _QWORD qword784;
            _QWORD qword78C;
            _QWORD qword794;
            _DWORD dword79C;
            _QWORD qword7A0;
            _DWORD dword7A8;
            _DWORD dword7AC;
            _QWORD qword7B0;
            _DWORD dword7B8;
            _QWORD qword7BC;
            _QWORD qword7C4;
            _DWORD dword7CC;
            _DWORD dword7D0;
            _DWORD dword7D4;
            _QWORD qword7D8;
            _DWORD dword7E0;
            _DWORD dword7E4;
            _DWORD dword7E8;
            _BYTE gap7EC[20];
            _BYTE byte800;
            _BYTE gap801[19];
            _DWORD dword814;
            _DWORD dword818;
            _DWORD dword81C;
            _QWORD qword820;
            _BYTE byte828;
            _BYTE gap829[3];
            _QWORD qword82C;
            _QWORD qword834;
            _BYTE gap83C[4];
            _QWORD qword840;
            _QWORD qword848;
            _QWORD qword850;
            _QWORD qword858;
            _DWORD dword860;
            _QWORD qword864;
            _DWORD dword86C;
            _DWORD dword870;
            _QWORD qword874;
            _DWORD dword87C;
            _QWORD qword880;
            _QWORD qword888;
            _QWORD qword890;
            _DWORD dword898;
            _QWORD qword89C;
            _QWORD qword8A4;
            _QWORD qword8AC;
            _QWORD qword8B4;
            _BYTE byte8BC;
        };

        class EnemySakelienBase : Game::Coop::Enemy
        {
        public:
            _QWORD qword8E8;
            _QWORD qword8F0;
            _WORD word8F8;
            _WORD word8FA;
            _QWORD qword8FC;
            _QWORD qword904;
            _QWORD qword90C;
            _BYTE byte914;
            _BYTE gap915[3];
            _QWORD qword918;
            _QWORD qword920;
            _QWORD qword928;
            _QWORD qword930;
            _DWORD dword938;
            _WORD word93C;
            _BYTE byte93E;
        };

        class EnemySakelienGolden : Game::Coop::EnemySakelienBase
        {
        public:
            _BYTE gap9C8[32];
            _QWORD qword9E8;
            _DWORD dword9F0;
            _BYTE byte9F4;
        };

        class EnemySakelienStandard : Game::Coop::EnemySakelienBase
        {
        public:
            _WORD word948;
            _WORD word94A;
            _BYTE gap94C[12];
            _QWORD qword958;
            _WORD word960;
            _BYTE byte962;
            _BYTE gap963[5];
            _DWORD dword968;
            _BYTE gap96C[4];
            _QWORD qword970;
            _DWORD dword978;
            _BYTE gap97C[4];
            _QWORD qword980;
            _QWORD qword988;
            _BYTE byte990;
            _BYTE gap991[7];
            _QWORD qword998;
            _QWORD qword9A0;
            _QWORD qword9A8;
            _BYTE byte9B0;
            __attribute__((aligned(4))) _QWORD qword9B4;
            _QWORD qword9BC;
        };

    } // namespace Coop

} // namespace Game