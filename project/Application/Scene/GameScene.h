#pragma once

#include "Cleyera.h"
#include "GameManager.h"

#include "GameObject/GameCollider/BoxCollisionManager.h"
#include "GameObject/GravityManager/GravityManager.h"

#include "GameObject/Block/BlockManager.h"
#include "GameObject/BreakBlock/BreakBlockManager.h"
#include "GameObject/Player/PlayerManager.h"
#include "GameObject/Warp/WarpManager.h"

#include "GameObject/Light/GameLight.h"

#include "GameObject/Particles/CharacterDeadParticle.h"
#include "GameObject/Particles/CharacterMoveParticle.h"

#include "GameObject/UI/GameSceneUI/GameSceneUI.h"

#include "GameFileLoader/RailLoader/RailLoader.h"

#include "ChangeSceneAnimation/ChangeSceneAnimation.h"
#include "GameObject/GameSceneAnimation/GameOverAnimation/EndAnimation.h"
#include "GameObject/GameSceneAnimation/StartAnimation/StartAnimation.h"

#include "Scene/GameClearScene.h"
#include "Scene/TitleScene.h"

#include "GameObject/SceneContextData/SceneContextData.h"
#include "ISceneContext.h"

#include "GameObject/Particles/WallHitParticle.h"

#include "GameScene/GameSceneStartState.h"
#include "GameScene/IGameSceneState.h"

#include"GameObject/Package/PackageManager.h"
#include"GameObject/GoalHouse/GoalHouseManager.h"

#include"GameObject/EnemyWalk/EnemyWalkManager.h"

/// <summary>
/// ゲームプレイ
/// </summary>
class GameScene : public IScene, public JsonComponent
{
 public:
   GameScene() {};
   ~GameScene() {};

   /// <summary>
   /// 初期化
   /// </summary>
   void Initialize(GameManager *state) override;

   /// <summary>
   /// 更新
   /// </summary>
   /// <param name="Scene"></param>
   void Update([[maybe_unused]] GameManager *Scene) override;
   /// <summary>
   /// ポストエフェクトをかける
   /// </summary>
   void PostProcessDraw() override;

   /// <summary>
   /// 前景2d
   /// </summary>
   void Flont2dSpriteDraw() override;

   /// <summary>
   /// Imguiの更新
   /// </summary>
   void ImGuiUpdate() override;

   void ChangeGameSceneState(unique_ptr<IGameSceneState> state);

#pragma region Get
   weak_ptr<PlayerManager> GetPlayerManager() { return player_; }
   bool GetIsGameEnd() { return *isGameEnd_; }
   const SceneContextData &GetSelectSceneContextData() { return selectSceneData_; }
   weak_ptr<GoalHouseManager> GetGoalHouseManager() { return goalHouseManager_; }
#pragma endregion

#pragma region Set
   void SetIsGameStartFlag(bool f) { isGameStartFlag_ = f; }
#pragma endregion

 private:
   /// <summary>
   /// 切替処理
   /// </summary>
   bool CheckChangeScene(GameManager *Scene);

   /// <summary>
   /// 当たり判定
   /// </summary>
   void Collision();

   /// <summary>
   /// 重力
   /// </summary>
   void Gravitys();

#pragma region Particle
   void ParticlesUpdate();
   void ParticlesDraw();
#pragma endregion

   ChangeSceneAnimation *changeSceneAnmation_ = nullptr;

   string inputLevelDataFileName_ = "";
   bool isGameStartFlag_ = false;
   bool *isGameEnd_ = nullptr;

   int32_t lavaIndex_ = 0;

   unique_ptr<ISceneContext> context_ = nullptr;
   SceneContextData selectSceneData_ = {};
   SceneContextData nextSceneData_ = {};

   //state
   unique_ptr<IGameSceneState> state_ = nullptr;

   // obj

   // light
   shared_ptr<GameLight> light_ = nullptr;

   // manager
   shared_ptr<PlayerManager> player_ = nullptr;
   shared_ptr<BlockManager> blockManager_ = nullptr;
   shared_ptr<BreakBlockManager> breakBlockManager_ = nullptr;

   shared_ptr<GravityManager> gravityManager_ = nullptr;
   shared_ptr<BoxCollisionManager> gameCollisionManager_ = nullptr;
   shared_ptr<PackageManager> packageManager_;
   shared_ptr<GoalHouseManager> goalHouseManager_;

   // particle
   shared_ptr<WallHitParticle> wallHitParticle_ = nullptr;
   shared_ptr<CharacterDeadParticle> deadParticle_ = nullptr;

   shared_ptr<PlayerMoveParticle> playerMoveParticle_ = nullptr;
   shared_ptr<PlayerDeadParticle> playerDeadParticle_ = nullptr;
   shared_ptr<EnemyWalkManager> enemy_;
};
