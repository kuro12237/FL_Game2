#include "TitleScene.h"
#include "WinApp.h"

using namespace Engine::Base::Win;

TitleScene::TitleScene()
{
   WinApp::GetInstance()->SetTiTleName(L"FL_Offside");
   toMgr_ = make_unique<TitleObjectManager>();
   tsMgr_ = make_unique<TitleSpriteManager>();
}

void TitleScene::Initialize([[maybe_unused]] GameManager *state)
{
   // Titleのレベルデータの読み込み
   std::string levelDataName = "title.json";
   shared_ptr<LevelData> levelData = SceneFileLoader::GetInstance()->ReLoad(levelDataName);

   // システムの初期設定
   gameObjectManager_ = GameObjectManager::GetInstance();
   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();
   gameObjectManager_->CameraReset();
   gameObjectManager_->Update();

   toMgr_->Init();
   tsMgr_->Init();
}

void TitleScene::Update([[maybe_unused]] GameManager *Scene)
{
   toMgr_->Update();
   tsMgr_->Update();
}

void TitleScene::ImGuiUpdate() {}

void TitleScene::PostProcessDraw() 
{
   // エンジンのマネージャーに、保持している全オブジェクトを描画させる
   if (gameObjectManager_) {
      // もしインスタンス描画（大量のRoadなど）を使っているならこれも
      gameObjectManager_->InstancingDraw();
      // 通常の不透明オブジェクトなどの描画
      gameObjectManager_->NormalDraw();
   }
}

void TitleScene::Flont2dSpriteDraw() {}
