#include "PlayerManager.h"

using namespace Engine;
using namespace Engine::Objects;
using namespace Engine::Manager;
using namespace Engine::Transform;

void PlayerManager::Initialize()
{
   // mainBody
   playerCore_ = make_shared<Player>();
   objDataList_.push_back(playerCore_);


   // Camera
   camera_ = make_shared<PlayerCamera>();
   objDataList_.push_back(camera_);

   for (auto &it : objDataList_) {
      auto obj = it.lock();
      obj->Initialize();
   }
   camera_->SetTarget(playerCore_->GetObjectData().lock()->GetWorldTransform(),
                      playerCore_->INameable::GetName());


   // commands
   commandHandler_ = make_shared<PlayerCommandHandler>();


   gameObjectManager_->CameraReset(camera_->GetName());

   p_CoreWorldPos_ = &gameObjectManager_->GetObj3dData_ptr(playerCore_->INameable::GetName())
                          ->GetWorldTransform()
                          .transform.translate;

   // ダメージの演出関数をセット
   playerCore_->SetDamageUpdateFunc(std::bind(&PlayerManager::DamegeUpdate, this));
   playerCore_->SetDamageUpdateEndFunc(std::bind(&PlayerManager::DamegeUpdateEnd, this));


   ModelManager::ModelLoadNormalMap();
   bulletModelHandle_ = ModelManager::LoadObjectFile("PlayerNormalBullet");
}

void PlayerManager::ImGuiUpdate()
{
   if (ImGui::TreeNode(playerCore_->INameable::GetName().c_str())) {
      playerCore_->ImGuiUpdate();


      ImGui::TreePop();
   }
}

void PlayerManager::Update()
{
   RemoveEmptyObjList();

   // Commands
   if (*this->isGameStartFlag_ && !playerCore_->IsInState<PlayerStateGoalAnimation>()) {
      // プレイヤーの操作キャラ
      commandHandler_->Handler();
      commandHandler_->CommandsExec(*playerCore_);
   }

   for (auto &it : objDataList_) {
      if (auto obj = it.lock()) {
         obj->Update();
      }
   }


}

void PlayerManager::Draw2d()
{
}

void PlayerManager::DrawHp()
{
}

void PlayerManager::Draw2dBullet()
{
}

void PlayerManager::SetParticlePos()
{
 /*  moveParticle_.lock()->SetPlayerPos(
       this->playerCore_->GetObjectData().lock()->GetWorldTransform().transform.translate);
   deadParticle_.lock()->SetPlayerPos(
       this->playerCore_->GetObjectData().lock()->GetWorldTransform().transform.translate);*/
}

void PlayerManager::PushBullet([[maybe_unused]]const Math::Vector::Vector3 &pos)
{
   // オブジェクトの作成
   shared_ptr<Game3dObjectData> data = make_shared<Game3dObjectData>();
   data->SetObjectType("MESH");
   data->Initialize({}, {}, bulletModelHandle_);

   // 弾の拡散範囲計算
   // xMin/yMax
   const Math::Vector::Vector2 spreadRangeMax = {-0.5f, 0.5f};

   // velocityの計算
   Math::Vector::Vector3 velocity = Math::Vector::Subtruct(*p_ReticleWorldPos_, *p_GunWorldPos_);
   velocity.x += RandomGenerator::GetFloat(spreadRangeMax.x, spreadRangeMax.y);
   velocity.y += RandomGenerator::GetFloat(spreadRangeMax.x, spreadRangeMax.y);

}

void PlayerManager::CheckisDeadBullets()
{

}

void PlayerManager::DamegeUpdate()
{
   const float vinatteScale = 64.0f;
   const float vinateFactorSpeed = 1.0f / 120.0f;
   const Math::Vector::Vector3 color = {1.0f, 0.0f, 0.0f};
   // ビネットをかける

   PostEffect::GetInstance()->SetSelectPostEffect(VIGNETTE, true);
   PostEffect::GetInstance()->SetVignetteScale(vinatteScale);
   PostEffect::GetInstance()->SetVignetteFactor(vinatteFactor_);
   PostEffect::GetInstance()->SetVignetteColor(color);

   vinatteFactor_ -= vinateFactorSpeed;
}

void PlayerManager::DamegeUpdateEnd()
{

   PostEffect::GetInstance()->SetSelectPostEffect(VIGNETTE, false);
   PostEffect::GetInstance()->SetVignetteFactor(0.0f);
   vinatteFactor_ = vinatteFactorMax_;
}
