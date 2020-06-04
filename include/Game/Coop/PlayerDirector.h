#pragma once

#include "types.h"

namespace Game
{
    namespace Coop
    {
        class Player
        {
        public:
            _DWORD mRoundBankedPowerIkuraNum;
            _DWORD mGotGoldenIkuraNum;
            _DWORD mRoundBankedGoldenIkuraNum;
            _DWORD mTotalBankedGoldenIkuraNum;
            _DWORD mRoundDroppedGoldenIkuraNum;
            _DWORD unknown[7];
            _DWORD mTotalRobbedGoldenIkuraNum;
            _DWORD mTotalRobbedGoldenIkuraNum2;
            _DWORD dword38;
            _DWORD mTotalDefeatedSalmonidsNum;
            _DWORD mTotalDefeatedSakelienStandardNum;
            _DWORD mTotalDefeatedSakelienLargeNum;
            _DWORD mTotalDefeatedSakelienSmallNum;
            _DWORD dword4C;
            _DWORD dword50;
            _DWORD dword54;
            _DWORD dword58;
            _DWORD dword5C;
            _DWORD dword60;
            _DWORD dword64;
            _DWORD dword68;
            _DWORD dword6C;
            _DWORD dword70;
            _DWORD dword74;
            _DWORD dword78;
            _DWORD dword7C;
            _DWORD dword80;
            _DWORD dword84;
            _DWORD dword88;
            _DWORD dword8C;
            _DWORD dword90;
            _DWORD dword94;
            _DWORD dword98;
            _DWORD mTotalHitNum;
            _DWORD dwordA0;
            _DWORD dwordA4;
            _DWORD dwordA8;
            _DWORD dwordAC;
            _DWORD dwordB0;
            _DWORD dwordB4;
            _DWORD dwordB8;
            _DWORD dwordBC;
            _DWORD dwordC0;
            _DWORD dwordC4;
            _DWORD dwordC8;
            _DWORD dwordCC;
            _DWORD dwordD0;
            _DWORD dwordD4;
            _DWORD dwordD8;
            _DWORD dwordDC;
            _DWORD dwordE0;
            _DWORD dwordE4;
            _DWORD dwordE8;
            _DWORD dwordEC;
            _DWORD mTotalGotGoldenIkuraNum[2];
            _DWORD dwordF8;
            _DWORD dwordFC;
        };

        class PlayerDirector : public Cmn::Actor, public sead::IDisposer
        {
        public:
            void *vtable;
            Game::Coop::Player mPlayer[4];

            _QWORD lostBankedGoldenIkura(int);
            _QWORD lostCashedGoldenIkura(void);
            _QWORD bankGolodenIkura(int);
            _QWORD pickGoldenIkura(int);
            void setupRoundGoldenIkura(int);
            void resetTotalBankedGoldenIkuraNum(void);
            _QWORD getTotalBankedGoldenIkuraNum(void);
            _QWORD resetRoundBankedGoldenIkuraNum(void);
            _QWORD getRoundBankedGoldenIkuraNum(void);
            void resetCashedGoldenIkuraNum(void);
            void setCashedGoldenIkuraNum(int, int);
            _QWORD getNormalIkuraNum(void);
        };

    } // namespace Coop
} // namespace Game