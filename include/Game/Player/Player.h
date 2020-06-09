#pragma once

#include "types.h"

#include "sead/vector.h"
#include "Cmn/Actor.h"
#include "PlayerAccessoryMgr.h"
#include "PlayerAquaBall.h"
#include "PlayerBehindCamera.h"
#include "PlayerBombHandHeld.h"
#include "PlayerComeOnNice.h"
#include "PlayerCollision.h"
#include "PlayerCoopGoldenIkura.h"
#include "PlayerCoopFloat.h"
#include "PlayerCoopSeqRoundSetup.h"
#include "PlayerCoopSkillMgr.h"
#include "PlayerCustomInfo.h"
#include "Cmn/PlayerCustomMgr.h"
#include "PlayerDamage.h"
#include "PlayerDashPanel.h"
#include "PlayerDokanWarp.h"
#include "PlayerEffect.h"
#include "PlayerForwardRoll.h"
#include "PlayerGamePad.h"
#include "PlayerGearSkillMgr.h"
#include "PlayerGrindRail.h"
#include "PlayerGrindRailVersus.h"
#include "PlayerHairBodyAnimSlot.h"
#include "PlayerInkAction.h"
#include "PlayerInkRailVersus.h"
#include "PlayerInputAction.h"
#include "PlayerInputVictoryClam.h"
#include "PlayerJetpack.h"
#include "PlayerJointHuman.h"
#include "PlayerJointSquid.h"
#include "PlayerMIssionSeqWeaponDrone.h"
#include "PlayerMissionDunkShoot.h"
#include "PlayerMissionOctaSeqEntrance.h"
#include "PlayerMissionOctaSeqPinch.h"
#include "PlayerModel.h"
#include "PlayerMotion.h"
#include "PlayerMove.h"
#include "PlayerNetControl.h"
#include "PlayerOffenseAssistLog.h"
#include "PlayerParam.h"
#include "PlayerRemote.h"
#include "PlayerSideStep.h"
#include "PlayerSpectator.h"
#include "PlayerSpectatorBirdCamera.h"
#include "PlayerSquidCannon.h"
#include "PlayerStatus.h"
#include "PlayerStepPaint.h"
#include "PlayerSuperArmor.h"
#include "PlayerSuperLanding.h"
#include "PlayerTrouble.h"
#include "PlayerVictimLog.h"
#include "PlayerWeaponDrone.h"
#include "PlayertInputCamera.h"
#include "Game/PlayerMgr.h"
#include "Cmn/PlayerInfo.h"

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

namespace Game {
    class Player : public Cmn::Actor {
        public:
        enum ResultAnim{
            Win, Lose, CoopWin, CoopLose
        };

        void start_MissionAppear();
        void change_DemoPlaceAnim(Game::Player::ResultAnim, int);
        void replaceTeamColor(sead::Color4f const&);
        u64 startSpecial_AllMarking();
        u64 startSpecial_SuperArmor();
        u64 startSpecial_Launcher();
        u64 startSpecial_Jetpack();
        u64 startSpecial_SuperLanding();
        u64 startSpecial_RainCloud();
        u64 startSpecial_AquaBall();
        u64 startSpecial_Bubble();

        _DWORD dword348;
        _DWORD dword34C;
        _DWORD dword350;
        _DWORD dword354;
        _DWORD dword358;
        _DWORD mOctaType;
        _BYTE byte360[216];
        Game::PlayerSpectatorBirdCamera *mPlayerSpectatorBirdCamera[2];
        _BYTE somestuff[56];
        uint32_t mIndex;
        Cmn::PlayerInfo *mPlayerInfo;
        Game::PlayerMgr *PlayerMgr;
        _BYTE moarstuff[688];
        sead::Vector3<float> mPosition;
        _BYTE morestuff[1916];
        Game::PlayerParam *mPlayerParam;
        Game::PlayerGamePad *mPlayerGamePad;
        Game::PlayerRemote *mPlayerRemote;
        Game::PlayerDokanWarp *mPlayerDokanWarp;
        Game::PlayerSideStep *mPlayerSiteStep;
        Game::PlayerForwardRoll *mPlayerForwardRoll;
        Game::PlayerJetpack *mPlayerJetpack;
        Game::PlayerSuperArmor *mPlayerSuperArmor;
        Game::PlayerSuperLanding *mPlayerSuperLanding;
        Game::PlayerAquaBall *mPlayerAquaBall;
        Game::PlayerSquidCannon *mPlayerSquidCannon;
        Game::PlayerStatus *mPlayerStatus;
        Game::PlayerStepPaint *mPlayerStepPaint;
        Game::PlayerMove *mPlayerMove;
        Game::PlayerTrouble *mPlayerTrouble;
        Game::PlayerInputAction *mPlayerInputAction;
        Game::PlayerInputCamera *mPlayerInputCamera;
        Game::PlayerInputVictoryClam *mPlayerInputVictoryClam;
        Game::PlayerInkAction *mPlayerInkAction1;
        Game::PlayerCollision *mPlayerCollision;
        Game::PlayerModel *mPlayerModel;
        uint64_t silhouette;
        Game::PlayerMotion *mPlayerMotion;
        Game::PlayerHairBodyAnimSlot *mPlayerHairBodyAnimSlot;
        Game::PlayerEffect *mPlayerEffect;
        Game::PlayerInkAction *mPlayerInkAction2;
        Game::PlayerJointHuman *mPlayerJointHuman;
        Game::PlayerJointSquid *mPlayerJointSquid;
        Game::PlayerBombHandHeld *mPlayerBombHandheld[2];
        Cmn::PlayerCustomMgr *mPlayerCustomMgr;
        Game::PlayerCustomInfo *mPlayerCustomInfo;
        Game::PlayerAccessoryMgr *mPlayerAccessoryMgr;
        Game::PlayerNetControl *mPlayerNetControl;
        Game::PlayerDamage *mPlayerDamage[3];
        Game::PlayerGearSkillMgr *mPlayerGearSkillMgr;
        Game::PlayerCoopSeqRoundSetup *mPlayerCoopSeqRoundSetup;
        Game::PlayerCoopFloat *mPlayerCoopFloat;
        Game::PlayerCoopGoldenIkura *mPlayerCoopGoldenIkura;
        Game::PlayerCoopSkillMgr *mPlayerCoopSkillMgr;
        Game::PlayerComeOnNice *mPlayerComeOnNice;
        Game::PlayerOffenseAssistLog *mPlayerOffenseAssistLog;
        Game::PlayerVictimLog *mPlayerVictimLog;
        Game::PlayerSpectator *mPlayerSpectator;
        Game::PlayerMissionDunkShoot *mPlayerMissionDunkShoot;
        Game::PlayerMissionSeqWeaponDrone *mPlayerMissionSeqWeaponDrone;
        Game::PlayerWeaponDrone *mPlayerWeaponDrone;
        Game::PlayerMissionOctaSeqEntrance *mPlayerMissionOctaSeqEntrance;
        Game::PlayerMissionOctaSeqPinch *mPlayerMissionOctaSeqPinch;
        Game::PlayerGrindRail *mPlayerGrindRail;
        Game::PlayerGrindRailVersus *mPlayerGrindRailVersus;
        Game::PlayerDashPanel *mPlayerDashPanel;
        Game::PlayerInkRailVersus *mPlayerInkRailVersus;
        _BYTE gap1080[254];
        Game::PlayerBehindCamera *mPlayerBehindCamera;
        _QWORD qword1190;
    };
};
#endif