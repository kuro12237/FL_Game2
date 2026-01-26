#include "TitleScene.h"
#include "WinApp.h"

using namespace Engine::Base::Win;

TitleScene::TitleScene()
{
   WinApp::GetInstance()->SetTiTleName(L"FL_Offside");

   camera_ = make_unique<TitleCamera>();
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

   // カメラの初期化
   camera_->Initialize();
}

void TitleScene::Update([[maybe_unused]] GameManager *Scene)
{
   // カメラの更新
   camera_->Update();
}

void TitleScene::ImGuiUpdate() {}

void TitleScene::PostProcessDraw() {}

void TitleScene::Flont2dSpriteDraw() {}
