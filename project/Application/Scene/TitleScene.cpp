#include "TitleScene.h"
#include "WinApp.h"
#include "Input/Input.h"

using namespace Engine::Base::Win;
using namespace Engine;
using namespace Engine::Manager;

TitleScene::TitleScene()
{
   WinApp::GetInstance()->SetTiTleName(L"FL_Offside");
   toMgr_ = make_unique<TitleObjectManager>();
   tsMgr_ = make_unique<TitleSpriteManager>();

   light_ = make_unique<TO_Light>();
}

void TitleScene::Initialize([[maybe_unused]] GameManager *state)
{
   // paramfilePath変更
   auto globalVariables = GlobalVariables::GetInstance();
   globalVariables->SetDirectoryFilePath("Resources/LevelData/ParamData/TitleScene/");
   globalVariables->LoadFiles("Resources/LevelData/ParamData/TitleScene/");

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

   isPushed_ = false;

   auto postEffect = Engine::PostEffect::GetInstance();
   auto &postParam = postEffect->GetAdjustedColorParam();
   postParam.fogStart = 100.0f;
   postParam.fogEnd = 1000.0f;

   toMgr_->Init();
   tsMgr_->Init();

   light_->Initialize();
}

void TitleScene::Update([[maybe_unused]] GameManager *Scene)
{
   light_->Update();
   toMgr_->Update();
   tsMgr_->Update();

   // 毎フレーム更新
   ChangeSceneAnimation::GetInstance()->Update();

   // 入力
   if (Input::PushKeyPressed(DIK_SPACE) || Input::PushBottonPressed(XINPUT_GAMEPAD_A)) {

      if (!isPushed_) {
         // シーン切替開始
         ChangeSceneAnimation::GetInstance()->ChangeStart();
         isPushed_ = true;
      }
   }

   // シーン遷移判定
   if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag()) {
      Scene->ChangeScene(std::make_unique<SelectScene>());
      return;
   }
}

void TitleScene::ImGuiUpdate()
{
   ImGui::Begin("Title Debug");

   // =========================
   // Camera（Object側）
   // =========================
   if (ImGui::CollapsingHeader("Camera")) {
      toMgr_->ImGuiUpdate(); // TO_Camera::ImGuiUpdate()
   }

   // =========================
   // PostEffect（Scene側）
   // =========================
   if (ImGui::CollapsingHeader("PostEffect")) {

      auto *postEffect = Engine::PostEffect::GetInstance();
      auto &param = postEffect->GetAdjustedColorParam();

      ImGui::Text("Fog");

      ImGui::DragFloat("Fog Start", &param.fogStart, 1.0f, 0.0f, 10000.0f);
      ImGui::DragFloat("Fog End", &param.fogEnd, 1.0f, 0.0f, 10000.0f);

      ImGui::Separator();

      if (ImGui::Button("Reset PostEffect")) {
         param.fogStart = 100.0f;
         param.fogEnd = 100.0f;
      }
   }

   ImGui::End();
}

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

void TitleScene::Flont2dSpriteDraw()
{
    tsMgr_->Draw();

    // シーン遷移演出
    ChangeSceneAnimation::GetInstance()->Draw();
}
