#pragma once

#include "types.h"

namespace Game
{
namespace Coop
{
class Wave
{
public:
    _DWORD gap0x0;
    _DWORD tide;
    _DWORD gap0x8;
    _DWORD gap0xC;
    _DWORD event;
};
class Setting
{
public:
    u64 startChangeWaterLevel(int);
    void reset();
    void setup(int);
    /* ... */
    _BYTE gap[0x14E4];
    Game::Coop::Wave next;
    Game::Coop::Wave prev;
    Game::Coop::Wave wave[3];
};

}; // namespace Coop
}; // namespace Game
