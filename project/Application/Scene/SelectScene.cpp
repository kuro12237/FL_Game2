#include "SelectScene.h"

using namespace Engine::Manager;

void SelectScene::Initialize([[maybe_unused]] GameManager *state)
{
   GlobalVariables::GetInstance()->SetDirectoryFilePath("Resources/LevelData/ParamData/SelectScene/");
   GlobalVariables::GetInstance()->LoadFiles("Resources/LevelData/ParamData/SelectScene/");

   // levelDataの読み込み
   shared_ptr<LevelData> levelData = move(SceneFileLoader::GetInstance()->ReLoad(inputLevelDataFileName_));

   gameObjectManager_ = GameObjectManager::GetInstance();
   gameObjectManager_->ClearAllData();
   gameObjectManager_->MoveData(levelData.get());
   gameObjectManager_->SetAllParents();
   gameObjectManager_->CameraReset();
   gameObjectManager_->Update();

   context_ = make_unique<ISceneContext>();

   gameCollisionManager_ = make_unique<BoxCollisionManager>();
   gravityManager_ = make_unique<GravityManager>();
   gravityManager_->Initialize();

   camera_ = make_shared<PlayerCamera>();
   camera_
       ->Initialize();

   gameObjectManager_
       ->CameraReset(camera_->GetName());
   camera_
       ->Update();
   

   this->jsonGropName_ = VAR_NAME(SelectScene);
   this->CreateJsonData();

   float lightRadious = 512.0f;
   Math::Vector::Vector3 lightPos = {0.0f, 64.0f, -16.0f};
   float lightDecay = 0.1f;

   string key = VAR_NAME(lightRadious);
   AddJsonItem<decltype(lightRadious)>(key, lightRadious);
   lightRadious = GetJsonItem<decltype(lightRadious)>(key);

   key = VAR_NAME(lightPos);
   AddJsonItem<decltype(lightPos)>(key, lightPos);
   lightPos = GetJsonItem<decltype(lightPos)>(key);

   key = VAR_NAME(lightDecay);
   AddJsonItem<decltype(lightDecay)>(key, lightDecay);
   lightDecay = GetJsonItem<decltype(lightDecay)>(key);

   light_.radious = lightRadious;
   light_.position = lightPos;
   light_.decay = lightDecay;


   SkyBox::GetInstance()->Reset();
   const float kSkyBoxScale_ = 256.0f;
   SkyBox::GetInstance()->SetTransform({{kSkyBoxScale_, kSkyBoxScale_, kSkyBoxScale_}});
   uint32_t skyBoxTexHandle = TextureManager::LoadDDSTexture("SkyBox/CubeMap.dds");
   SkyBox::GetInstance()->SetTexHandle(skyBoxTexHandle);

   Math::Vector::Vector4 fogParam = {};
   key = VAR_NAME(fogParam);
   AddJsonItem<decltype(fogParam)>(key, fogParam);
   fogParam = GetJsonItem<decltype(fogParam)>(key);

   postEffect_->GetAdjustedColorParam().fogScale_ = fogParam.x;
   postEffect_->GetAdjustedColorParam().fogAttenuationRate_ = fogParam.y;
   postEffect_->GetAdjustedColorParam().fogStart = fogParam.z;
   postEffect_->GetAdjustedColorParam().fogEnd = fogParam.w;
}

void SelectScene::Update(GameManager *Scene)
{
   // 更新
   ChangeSceneAnimation::GetInstance()->Update();

   // 切替スタート
   ChangeSceneAnimation::GetInstance()->ChangeStart();

   camera_->Update();

   // 終わったら
   if (ChangeSceneAnimation::GetInstance()->GetIsChangeSceneFlag()) {
      // ステージ選択番号
      contextData_.stageNumber = 1;
      //データを次のシーンへ
      context_->SetData(contextData_);
      Scene->SetMoveSceneContext(move(context_));
      Scene->ChangeScene(make_unique<GameScene>());
      return;
   }
}

void SelectScene::ImGuiUpdate()
{
   ImGui::Begin("PostEffect");
   ImGui::DragFloat("scale::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogScale_, 0.01f);
   ImGui::DragFloat("att::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogAttenuationRate_, 0.01f);
   ImGui::DragFloat("start::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogStart, 1.0f);
   ImGui::DragFloat("end::%f", &Engine::PostEffect::GetInstance()->GetAdjustedColorParam().fogEnd, 1.0f);
   ImGui::End();
   gameObjectManager_->ImGuiUpdate();
   if (ImGui::TreeNode("light")) {
      ImGui::DragFloat3("t", &light_.position.x);
      ImGui::DragFloat("radious", &light_.radious);
      ImGui::DragFloat("decay", &light_.decay);
      ImGui::DragFloat("intencity", &light_.intencity);

      ImGui::TreePop();
   }

   ChangeSceneAnimation::GetInstance()->ImGuiUpdate();
}

void SelectScene::PostProcessDraw()
{
   gameObjectManager_->InstancingDraw();
   gameObjectManager_->NormalDraw();
}

void SelectScene::Flont2dSpriteDraw()
{
   //ChangeSceneAnimation::GetInstance()->Draw();
}

void SelectScene::Collision()
{

   gameCollisionManager_->CheckAllCollisoin();
}

void SelectScene::Gravitys()
{
   gravityManager_->Update();
   gravityManager_->ClearList();


   gravityManager_->CheckGravity();
}

bool SelectScene::CheckLoadScene()
{
   bool changeFlag = false;


   return changeFlag;
}
