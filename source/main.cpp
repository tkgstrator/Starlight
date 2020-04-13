#include "main.hpp"

using namespace starlight;

// Needed on old versions of rtld that doesn't check for DT_INIT existance.
extern "C" void __custom_init(void) {}

// DT_FINI here for completeness.
extern "C" void __custom_fini(void) {}

static agl::DrawContext *mDrawContext;
static sead::TextWriter *mTextWriter;
static uint32_t *mCoopSetting;
static uint64_t first;
static uint64_t offset;
static Lp::Sys::Actor *mActor;
static Game::Coop::EventGeyser *mEventGeyser;
static Game::Coop::EventDirector *mEventDirector;
static sead::ExpHeap *mStarlightHeap;
static View *mView;
static int mode;
static bool showMenu;
static bool flg = true;

uint32_t readU32(uint32_t *p, uint32_t offset)
{
    uint32_t res;
    asm volatile("LDR %[result], [%[base], %[offset]]"
                 : [ result ] "=r"(res)
                 : [ base ] "r"(p), [ offset ] "r"(offset)
                 :);
    return res;
}

void renderEntrypoint(agl::DrawContext *drawContext, sead::TextWriter *textWriter, uint32_t *coopSetting, Game::Coop::EventDirector *mEventDirector)
{
    mDrawContext = drawContext;
    mTextWriter = textWriter;
    mCoopSetting = coopSetting;
    mEventDirector = mEventDirector;

    mTextWriter->mColor = sead::Color4f::cWhite;

    Collector::init();
    Collector::collect();

    if (mStarlightHeap == NULL)
        allocHeap();
    if (mStarlightHeap != NULL)
        Collector::mHeapMgr->setCurrentHeap_(mStarlightHeap);

    static bool init = false;
    if (!init)
    {

        mView = new View();
        menu::SimpleMenu *m = new menu::SimpleMenu();
        auto renderCallback = []() {
            return std::string("Current scene name: ") + std::string(Lp::Utl::getCurSceneName());
        };
        menu::SimpleMenuEntry *sceneDisplayEntry = new menu::SimpleMenuEntry();
        sceneDisplayEntry->mRenderCallback = renderCallback;
        m->mEntries.push_back(sceneDisplayEntry);

        mView->pushMenu(m);

        init = true;
    }

    textWriter->printf("Current heap name: %s\n", Collector::mHeapMgr->getCurrentHeap()->mName.mCharPtr);
    textWriter->printf("Current heap free space: 0x%x\n", Collector::mHeapMgr->getCurrentHeap()->getFreeSize());

    // Display Coop Setting
    if (mCoopSetting != NULL)
    {
        uint32_t *that = mCoopSetting;
        // textWriter->printf("Coop Current WAVE: Tide: %d Event: %d\n", that[1338], that[1341]);
        for (int loop = 0; loop < 3; loop++)
        {
            uint32_t tide = readU32(that, 0x14 * loop + 0x1510);
            uint32_t event = readU32(that, 0x14 * loop + 0x151C);
            textWriter->printf("WAVE %d Tide: %d Event: %d\n", loop + 1, tide, event);
        }
    }

    if (mEventDirector != NULL)
    {
        mEventGeyser = mEventDirector->eventGeyser;
        if (Game::Coop::Utl::GetEventType() == 2)
        {
            sead::PtrArrayImpl geyser = mEventGeyser->ptrArray;
            textWriter->printf("Random Seed1: %08X %08X %08X %08X\n", mEventGeyser->random1.mSeed1, mEventGeyser->random1.mSeed2, mEventGeyser->random1.mSeed3, mEventGeyser->random1.mSeed4);
            textWriter->printf("Random Seed2: %08X %08X %08X %08X\n", mEventGeyser->random2.mSeed1, mEventGeyser->random2.mSeed2, mEventGeyser->random2.mSeed3, mEventGeyser->random2.mSeed4);
            textWriter->printf("Geyser Array: %d\n", geyser.mLength);
            uint64_t *ptr = geyser.ptr;
            // uint64_t succ = (uint64_t)(ptr[0]);

            if (flg && geyser.mLength > 0) { // Get Offset and First Address 
                first = (uint64_t)(ptr[0]);
                offset = (uint64_t)(ptr[1]) - (uint64_t)(ptr[0]);
                flg = false;
            }

            textWriter->printf("Pointer: %08X %08X\n", first, offset);

            for (int i = 0; i < geyser.mLength; i++)
            {
                uint32_t diff = (uint64_t)ptr[i] - first;
                if (diff == 0)
                    textWriter->printf("%8X %8P %X\n", ptr[i], &ptr[i], 0);
                if (diff >= offset)
                    textWriter->printf("%8X %8P %X\n", ptr[i], &ptr[i], ((uint64_t)ptr[i] - first - offset + 0x900) / 0x900);
            }
        }
    }

    mView->update();
    mView->render(mTextWriter);

    if (showMenu)
    {
        drawBackground();

        textWriter->setScaleFromFontHeight(20);
        sead::TextWriter::setupGraphics(drawContext); // re-setup context

        textWriter->printf("Welcome to Starlight!\n");
        textWriter->printf("This is a demonstration of C/C++ code running in the context of a Switch game!\n");
        textWriter->printf("Credit to shibboleet, Khangaroo, Thog, Retr0id, and the libnx maintainers!\n");

        textWriter->printf("Current scene name: %s\n", Lp::Utl::getCurSceneName());

        if (Collector::mController.isPressed(Controller::Buttons::RStick))
            mode++;
        if (mode > Modes::END)
            mode = 0;
        textWriter->printf("Current mode: %s\n", modeToText((Modes)mode));

        Cmn::StaticMem *staticMem = Collector::mStaticMemInstance;
        if (staticMem != NULL)
            handleStaticMem(staticMem);

        Game::PlayerMgr *playerMgr = Collector::mPlayerMgrInstance;
        if (playerMgr != NULL)
            handlePlayerMgr(playerMgr);

        Cmn::PlayerCtrl *playerCtrl = Collector::mPlayerCtrlInstance;
        if (playerCtrl != NULL)
            handlePlayerControl(playerCtrl);
        else if (mode == Modes::INPUT_VIEWER)
        {
            mTextWriter->printf("Information not available.\n");
        }

        Cmn::MushDataHolder *mushData = Collector::mMushDataHolder;
        if (mushData != NULL)
            handleMushDataHolder(mushData);

        Game::MainMgr *mainMgr = Collector::mMainMgrInstance;
        if (mainMgr != NULL)
        {
            handleMainMgr(mainMgr);
        }
    }

    Collector::mController.update();
    Collector::mHeapMgr->setCurrentHeap_(NULL);
}

void allocHeap()
{
    Lp::Sys::HeapGroup *heapGroup = Lp::Sys::HeapGroup::sInstance;
    if (heapGroup != NULL)
    {
        sead::ExpHeap *othersHeap = heapGroup->mHeaps[Lp::Sys::HeapGroup::Group::cOthers];
        Collector::mHeapMgr->setCurrentHeap_(othersHeap);
        sead::Heap *currentHeap = Collector::mHeapMgr->getCurrentHeap();

        if (mStarlightHeap == NULL)
        {
            sead::SafeStringBase<char> str;
            str.mCharPtr = (char *)"StarlightHeap";

            mStarlightHeap = sead::ExpHeap::create(0, str, currentHeap, 4, sead::Heap::HeapDirection::TAIL, true);
        }
    }
}

void drawBackground()
{
    sead::Vector3<float> p1; // top left
    p1.mX = -1.0;
    p1.mY = 1.0;
    p1.mZ = 0.0;
    sead::Vector3<float> p2; // top right
    p2.mX = 0.0;
    p2.mY = 1.0;
    p2.mZ = 0.0;
    sead::Vector3<float> p3; // bottom left
    p3.mX = -1.0;
    p3.mY = -1.0;
    p3.mZ = 0.0;
    sead::Vector3<float> p4; // bottom right
    p4.mX = 0.0;
    p4.mY = -1.0;
    p4.mZ = 0.0;

    sead::Color4f c;
    c.r = 1.0;
    c.g = 1.0;
    c.b = 1.0;
    c.a = 0.5;

    agl::utl::DevTools::beginDrawImm(mDrawContext, sead::Matrix34<float>::ident, sead::Matrix44<float>::ident);
    agl::utl::DevTools::drawTriangleImm(mDrawContext, p1, p2, p3, c);
    agl::utl::DevTools::drawTriangleImm(mDrawContext, p3, p4, p2, c);
}

void handleStaticMem(Cmn::StaticMem *staticMem)
{
    sead::SafeStringBase<char> *stageName = &staticMem->mMapFileName1;
    if (stageName->mCharPtr != NULL)
    {
        mTextWriter->printf("Loaded stage: %s\n", stageName->mCharPtr);
    }

    Cmn::PlayerInfoAry *playerInfoAry = staticMem->mPlayerInfoAry;
    if (playerInfoAry != NULL)
    {
        mTextWriter->printf("PlayerInfoAry ptr: 0x%x\n", playerInfoAry);
    }
}

void handlePlayerMgr(Game::PlayerMgr *playerMgr)
{
    Game::Player *player = playerMgr->getControlledPerformer();

    Cmn::PlayerInfo *info = player->mPlayerInfo;
    if (info != NULL)
    {
        mTextWriter->printf("Controlled player team: %x\n", info->mTeam);
        mTextWriter->printf(u"Controlled player name: %s\n", info->mPlayerName);
        if (info->mPlayerIndex == 0)
        {
            info->setPlayerName(u"Shadów");
        }
    }

    Game::PlayerMotion *playerMotion = player->mPlayerMotion;

    if (mode == Modes::EVENT_VIEWER)
    {
        static long scroll = 0;

        if (Collector::mController.isPressed(Controller::Buttons::UpDpad))
            scroll++;
        if (Collector::mController.isPressed(Controller::Buttons::DownDpad))
            scroll--;

        if (scroll < 0)
            scroll = 0;

        if (Collector::mController.isPressed(Controller::Buttons::LStick))
            playerMotion->startEventAnim((Game::PlayerMotion::AnimID)scroll, 0, 1.0);

        mTextWriter->printf("Event ID: 0x%x\n", scroll);

        if (Collector::mController.isPressed(Controller::Buttons::LStick))
            playerMotion->startEventAnim((Game::PlayerMotion::AnimID)scroll, 0, 1.0);
    }
    else if (mode == Modes::PLAYER_SWITCHER)
    {

        signed int currentPlayer = playerMgr->mCurrentPlayerIndex;
        mTextWriter->printf("Current player: %i\n", currentPlayer);

        if (Collector::mController.isPressed(Controller::Buttons::UpDpad))
            currentPlayer++;
        if (Collector::mController.isPressed(Controller::Buttons::DownDpad))
            currentPlayer--;

        if (currentPlayer < 0)
            currentPlayer = playerMgr->mTotalPlayerArry.mBufferSize;
        if (playerMgr->mTotalPlayerArry.mBufferSize <= currentPlayer)
            currentPlayer = 0;

        playerMgr->mCurrentPlayerIndex = currentPlayer;
        playerMgr->onChangeControlledPlayer();
    }
}

void handlePlayerControl(Cmn::PlayerCtrl *playerCtrl)
{
    Game::PlayerGamePadData::FrameInput input;
    input.record(); // grab input data

    if (mode == Modes::INPUT_VIEWER)
    {
        mTextWriter->printf("Left stick | x: %f | y: %f\n", input.leftStick.mX, input.leftStick.mY);
        mTextWriter->printf("Right stick | x: %f | y: %f\n", input.rightStick.mX, input.rightStick.mY);
        mTextWriter->printf("Angle vel | x: %f | y: %f | z: %f\n", input.angleVel.mX, input.angleVel.mY, input.angleVel.mZ);
        mTextWriter->printf("Posture x | x: %f | y: %f | z: %f\n", input.postureX.mX, input.postureX.mY, input.postureX.mZ);
        mTextWriter->printf("Posture y | x: %f | y: %f | z: %f\n", input.postureY.mX, input.postureY.mY, input.postureY.mZ);
        mTextWriter->printf("Posture z | x: %f | y: %f | z: %f\n", input.postureZ.mX, input.postureZ.mY, input.postureZ.mZ);
    }

    static bool entered = false;
    Game::Player *player = Collector::mControlledPlayer;
    if (mode == 1 && player != NULL)
    {
        static float x, y, z;
        sead::Vector3<float> *playerPos = &player->mPosition;
        if (!entered)
        {
            x = playerPos->mX;
            y = playerPos->mY;
            z = playerPos->mZ;
        }

        int speed = 10;

        if (Collector::mController.isHeld(Controller::Buttons::UpDpad))
            y += speed;
        if (Collector::mController.isHeld(Controller::Buttons::DownDpad))
            y -= speed;
        if (Collector::mController.isHeld(Controller::Buttons::LeftDpad))
            x += speed;
        if (Collector::mController.isHeld(Controller::Buttons::RightDpad))
            x -= speed;
        if (Collector::mController.isHeld(Controller::Buttons::RightRStickOrdinal))
            z += speed;
        if (Collector::mController.isHeld(Controller::Buttons::LeftRStickOrdinal))
            z -= speed;

        playerPos->mX = x;
        playerPos->mY = y;
        playerPos->mZ = z;
        entered = true;
    }
    else
    {
        entered = false;
    }
}

void handleMushDataHolder(Cmn::MushDataHolder *mushDataHolder)
{
    static bool entered = false;

    if (!entered)
    {
        for (int i = 0; i < 29001; i++)
        {
            Cmn::WeaponData *data = mushDataHolder->mMushWeaponInfo->getById(Cmn::Def::WeaponKind::cMain, i);
            if (data != NULL)
            {
                data->mPrice = 0;
                data->mRank = 0;
                data->mSpecialCost = 0;
                data->mLockType = Cmn::WeaponData::LockType::None;
            }
        }

        for (int i = 0; i < 230; i++)
        {
            Cmn::MushMapInfo::Data *mapData = mushDataHolder->mMushMapInfo->getByMushOrder(i);
            if (strcmp(mapData->mStr1.mCharPtr, "Fld_Plaza00_Plz") != 0) // plaza crashes when using night mode for whatever reason
                if (mapData != NULL)
                {
                    mapData->mEnvHour = 2;
                }
        }

        entered = true;
    }
}

void handleMainMgr(Game::MainMgr *mainMgr)
{
    Game::GfxMgr *gfxMgr = mainMgr->gfxMgr;
    if (gfxMgr != NULL)
    {
        gfxMgr->hour = 2;
    }
    if (mode == Modes::PAINT_ALL)
    {
        if (Collector::mController.isPressed(Controller::Buttons::LStick))
        {
            unsigned int paintGameFrame = mainMgr->getPaintGameFrame();
            Cmn::Def::Team team = Cmn::Def::Team::Alpha;
            if (Collector::mControlledPlayer != NULL)
                team = Collector::mControlledPlayer->mTeam;
            Game::PaintUtl::requestAllPaintFloor(paintGameFrame, team);
            Game::PaintUtl::requestAllPaintWall(paintGameFrame, team);
        }
    }
}

char const *modeToText(Modes mode)
{
    switch (mode)
    {
    case Modes::NONE:
        return "None";
    case Modes::FLY:
        return "Fly";
    case Modes::EVENT_VIEWER:
        return "Event viewer";
    case Modes::INPUT_VIEWER:
        return "Gyro/stick input viewer";
    case Modes::PLAYER_SWITCHER:
        return "Player switcher";
    case Modes::PAINT_ALL:
        return "Paint all";
    default:
        return "None";
    }
}

int main(int arg, char **argv)
{
}