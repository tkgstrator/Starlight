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
        class EventNone : public Cmn::Actor
        {
        public:
            _BYTE stateMachine[0x50];
        };
        
        class EventRush : public Cmn::Actor
        {
        public:
            _BYTE stateMachine[0x50];
        };
        
        class EventGeyser : public Cmn::Actor
        {
        public:
            _BYTE stateMachine[0x50];
            sead::Random mRandom[2];
            sead::PtrArrayImpl ptrArray;
            _QWORD mGoalPos;
            _QWORD dword3D0;
            _QWORD dword3D8;

            u64 getGeyserSuccPos(void) {
                u64 *ptr = this->ptrArray.ptr;
                if (ptr != NULL) {
                    u64 index = u64(ptr[0]);
                    for (int i = 0; i < this->ptrArray.mLength; i++)
                    {
                        if (u64(ptr[i]) < index)
                            index = u64(ptr[i]);
                    }
                    return (u64(ptr[0]) == index) ? 65 : (u64(ptr[0]) - index - 0x680) / 0x900 + 65;
                }
                return 65;
            }

            u64 getGeyserGoalPos(void) {
                u64 *ptr = this->ptrArray.ptr;
                if (ptr != NULL) {
                    u64 index = u64(ptr[0]);
                    for (int i = 0; i < this->ptrArray.mLength; i++)
                    {
                        if (u64(ptr[i]) < index)
                            index = u64(ptr[i]);
                    }
                    return (u64(ptr[0]) == index) ? 65 : (this->mGoalPos - index - 0x680) / 0x900 + 65;
                }
                return 65;
            }
        };

        class EventDozer : public Cmn::Actor
        {
        public:
            _BYTE stateMachine[0x50];
        };

        class EventRally : public Cmn::Actor
        {
        public:
            _BYTE stateMachine[0x50];
        };

        class EventFog : public Cmn::Actor
        {
        public:
            _BYTE stateMachine[0x50];
        };

        class EventMissile : public Cmn::Actor
        {
        public:
            _BYTE stateMachine[0x50];
        };

        class SpawnGeyser : public Cmn::Actor
        {
        public:
            _BYTE gap348[84];
            sead::Vector3<float> vector;
            _BYTE gap39c[264];
            _QWORD qword4A8;
            _BYTE gap4B0[248];
            _BYTE stateMachine[0x50];
            _QWORD qword5F8;
            _DWORD dword600;
            _QWORD qword608;
            _QWORD qword610;
            __attribute__((aligned(16))) _QWORD qword620;
            _QWORD qword628;
            _QWORD qword630;
            _QWORD qword638;
        };

        class EventDirector : public Cmn::Actor, sead::IDisposer
        {
        public:
            Game::Coop::EventNone *eventNone;
            Game::Coop::EventRush *eventRush;
            Game::Coop::EventGeyser *eventGeyser;
            Game::Coop::EventDozer *eventDozer;
            Game::Coop::EventRally *eventRally;
            Game::Coop::EventFog *eventFog;
            Game::Coop::EventMissile *eventMissile;
        };
    }; // namespace Coop
};     // namespace Game
