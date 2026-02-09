#include "SelectScene.h"
#include "Input/Input.h"

using namespace Engine;
using namespace Engine::Manager;

SelectScene::SelectScene()
{
   toMgr_ = std::make_unique<TitleObjectManager>();
   light_ = std::make_unique<TO_Light>();
}

void SelectScene::Initialize(GameManager * /*state*/)
{
   // paramfilePath変更
   auto globalVariables = GlobalVariables::GetInstance();
   globalVariables->SetDirectoryFilePath("Resources/LevelData/ParamData/TitleScene/");
   globalVariables->LoadFiles("Resources/LevelData/ParamData/TitleScene/");

   // title.json をそのまま使う
   std::string levelDataName = "title.json";
   auto levelData = SceneFileLoader::GetInstance()->ReLoad(levelDataName);

   gameObjectManager_ = GameObjectManager::GetInstance();
   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();
   gameObjectManager_->CameraReset();
   gameObjectManager_->Update();

   // Light
   light_->Initialize();

   // Title objects
   toMgr_->Init();
   if (auto *cam = toMgr_->GetCamera()) {
      cam->SetTransform({-30.0f, 8.0f, -50.0f}, // translate
                        {-0.05f, 0.3f, 0.0f}    // rotate
      );
   }

   // Stage select UI
   select_ = std::make_unique<StageSelect>();
   select_->Init();

   // Scene context
   context_ = std::make_unique<ISceneContext>();
   isSelected_ = false;

   // PostEffect（Title と同じ）
   auto &post = Engine::PostEffect::GetInstance()->GetAdjustedColorParam();
   post.fogStart = 100.0f;
   post.fogEnd = 1000.0f;
}

void SelectScene::Update(GameManager *Scene)
{
   ChangeSceneAnimation::GetInstance()->Update();

   light_->Update();
   toMgr_->Update();
   select_->Update();

   // 決定入力
   if (!isSelected_ && (Input::PushKeyPressed(DIK_SPACE) || Input::PushBottonPressed(XINPUT_GAMEPAD_A))) {
      if (ChangeSceneAnimation::GetInstance()->GetIsComplite()) {
         ChangeSceneAnimation::GetInstance()->ChangeStart();
         isSelected_ = true;
      }
   }

   // シーン遷移
   if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag()) {
      contextData_.stageNumber = select_->GetSelectedStage();
      context_->SetData(contextData_);

      Scene->SetMoveSceneContext(std::move(context_));
      Scene->ChangeScene(std::make_unique<GameScene>());
      return;
   }
}

void SelectScene::ImGuiUpdate()
{
   toMgr_->ImGuiUpdate();
   ChangeSceneAnimation::GetInstance()->ImGuiUpdate();
}

void SelectScene::PostProcessDraw()
{
   gameObjectManager_->InstancingDraw();
   gameObjectManager_->NormalDraw();
}

void SelectScene::Flont2dSpriteDraw()
{
   select_->Draw();
   ChangeSceneAnimation::GetInstance()->Draw();
}
