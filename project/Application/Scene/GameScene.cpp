#include "GameScene.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void GameScene::Initialize([[maybe_unused]] GameManager *state)
{

   SkyBox::GetInstance()->Reset();
   const float kSkyBoxScale_ = 256.0f;
   SkyBox::GetInstance()->SetTransform({{kSkyBoxScale_, kSkyBoxScale_, kSkyBoxScale_}});
   uint32_t skyBoxTexHandle = TextureManager::LoadDDSTexture("SkyBox/CubeMap.dds");
   SkyBox::GetInstance()->SetTexHandle(skyBoxTexHandle);

   // paramfilePath変更
   globalVariables_->SetDirectoryFilePath("Resources/LevelData/ParamData/GameScene/");
   globalVariables_->LoadFiles("Resources/LevelData/ParamData/GameScene/");

   this->jsonGropName_ = VAR_NAME(GameScene);
   this->CreateJsonData();

   // selectからのデータを移動
   // selectSceneData_ = *state->GetMoveSceneContext()->GetData<SceneContextData>();

   // levelDataの読み込み
   inputLevelDataFileName_ = "Stages" + to_string(1) + ".json";
   shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

   changeSceneAnmation_ = ChangeSceneAnimation::GetInstance();

   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();
   gameObjectManager_->CameraReset();
   gameObjectManager_->Update();

   // マネージャー初期化
   player_ = make_shared<PlayerManager>();
   managerList_.push_back(player_);
   packageManager_ = make_shared<PackageManager>();
   managerList_.push_back(packageManager_);

   blockManager_ = make_shared<BlockManager>();
   managerList_.push_back(blockManager_);

   breakBlockManager_ = make_shared<BreakBlockManager>();
   managerList_.push_back(breakBlockManager_);

   gravityManager_ = make_shared<GravityManager>();
   managerList_.push_back(gravityManager_);


   goalHouseManager_ = make_shared<GoalHouseManager>();
   managerList_.push_back(goalHouseManager_);

   for (weak_ptr<ManagerComponent> manager : managerList_) {
      manager.lock()->Initialize();
      manager.lock()->SetGameStartFlag(&isGameStartFlag_);
   }

   int32_t goalIndex = 0;
   string goalName = VAR_NAME(goalIndex);
   AddJsonItem<decltype(goalIndex)>(goalName, goalIndex);
   goalIndex = GetJsonItem<decltype(goalIndex)>(goalName);

   string lavaName = VAR_NAME(lavaIndex_);
   AddJsonItem<decltype(lavaIndex_)>(lavaName, lavaIndex_);
   lavaIndex_ = GetJsonItem<decltype(lavaIndex_)>(lavaName);

   // ライト
   light_ = make_shared<GameLight>();
   lightDataList_.push_back(light_);
   for (auto light : lightDataList_) {
      light.lock()->Initialize();
   }

   gameCollisionManager_ = make_unique<BoxCollisionManager>();

   // ゲーム終了のつなぐ
   isGameEnd_ = &player_->GetPlayerCore()->GetIsGameEnd();

   context_ = make_unique<ISceneContext>();

#pragma region PostEffectSetting

   Math::Vector::Vector4 fogParam = {};
   string key = VAR_NAME(fogParam);
   AddJsonItem<decltype(fogParam)>(key, fogParam);
   fogParam = GetJsonItem<decltype(fogParam)>(key);

   postEffect_->GetAdjustedColorParam().fogScale_ = fogParam.x;
   postEffect_->GetAdjustedColorParam().fogAttenuationRate_ = fogParam.y;
   postEffect_->GetAdjustedColorParam().fogStart = fogParam.z;
   postEffect_->GetAdjustedColorParam().fogEnd = fogParam.w;

#pragma endregion

   goalHouseManager_->SetBlockNum(packageManager_->GetNum());

   this->ChangeGameSceneState(make_unique<GameSceneStartState>());
}

void GameScene::Update([[maybe_unused]] GameManager *Scene)
{
   changeSceneAnmation_->Update();

   if (state_) {
      state_->Update(this);
   }

   this->ListUpdate();


   Gravitys();
   Collision();

   /// シーン切り替え
   if (CheckChangeScene(Scene)) {
      return;
   }
}

bool GameScene::CheckChangeScene(GameManager *Scene)
{
   if (!changeSceneAnmation_->GetIsChangeSceneFlag()) {
      return false;
   }

   nextSceneData_.stageNumber = 1;
   context_->SetData(nextSceneData_);

   Scene->SetMoveSceneContext(move(context_));
   Scene->ChangeScene(make_unique<GameScene>());
   return true;
}

void GameScene::PostProcessDraw()
{
   gameObjectManager_->InstancingDraw();
   gameObjectManager_->NormalDraw();

   ParticlesDraw();
}

void GameScene::Flont2dSpriteDraw()
{

   if (state_) {
      state_->Draw2d();
   }

   changeSceneAnmation_->Draw();
}

void GameScene::ImGuiUpdate()
{
   gameObjectManager_->ImGuiUpdate();
   ImGui::Separator();
   ImGui::Text("SceneReload");
   static char buffer[256] = "";
   if (ImGui::InputText("SelectLevelDataFilePath", buffer, sizeof(buffer))) {
      inputLevelDataFileName_ = std::string(buffer);
   }
   ImGui::Separator();

   player_->ImGuiUpdate();

   if (ImGui::TreeNode("Particles")) {
      deadParticle_->ImGuiUpdate();
      ImGui::TreePop();
   }

   changeSceneAnmation_->ImGuiUpdate();

   if (state_) {
      state_->ImGuiUpdate();
   }
}

void GameScene::ChangeGameSceneState(unique_ptr<IGameSceneState> state)
{
   state_ = move(state);
   state_->SetGoalHouse(goalHouseManager_);

   if (state_) {
      state_->Initialize(this);
      state_->Update(this);
   }
}

void GameScene::Collision()
{
   if (!player_->GetPlayerCore()->IsInState<PlayerStateGoalAnimation>()) {
      gameCollisionManager_->ListPushback(player_->GetPlayerCore());
   }

   // ブロック
   for (shared_ptr<Block> b : blockManager_->GetBlocks()) {
      gameCollisionManager_->ListPushback(b.get());
   }
   for (shared_ptr<Package> b : this->packageManager_->GetPackages()) {

      if (!b)
         continue;

      gameCollisionManager_->ListPushback(b.get());
   }
   for (shared_ptr<GoalHouse> b : goalHouseManager_->GetBlocks()) {
      gameCollisionManager_->ListPushback(b.get());
   }
   // 壊れるブロック
   for (shared_ptr<BreakBlock> b : breakBlockManager_->GetBlocks()) {
      if (b) {
         weak_ptr<BreakBlock> it = b;
         auto obj = it.lock();
         gameCollisionManager_->ListPushback(obj.get());
      }
   }
   // ゴール

   gameCollisionManager_->CheckAllCollisoin();

   gameCollisionManager_->End();
}

void GameScene::Gravitys()
{
   gravityManager_->ClearList();

   // managerの中のオブジェクトをリストに追加
   for (weak_ptr<ManagerComponent> obj : managerList_) {
      auto it = obj.lock();
      if (it) {
         it->GravityManagerObjListPush(gravityManager_);
      }
   }
   gravityManager_->CheckGravity();
}

void GameScene::ParticlesUpdate()
{
   deadParticle_->GetParticle()->CallBarrier();
   blockManager_->Dispach(deadParticle_->GetParticle());
}

void GameScene::ParticlesDraw()
{
   for (auto p : particleList_) {
      p.lock()->Draw();
   }
}
