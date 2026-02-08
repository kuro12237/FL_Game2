#include "TO_Camera.h"
#include "Utility/ObjectManager/GameObjectManager.h"

TO_Camera::TO_Camera(const std::string &name)
{
   TO_Base::SettTargetName(name);
}

void TO_Camera::Initialize()
{
   // TO_BaseのBindではなく、カメラ専用のセットアップ
   gameObjectManager_ = GameObjectManager::GetInstance();
   // JSONのカメラ名をエンジン側に認識させる
   gameObjectManager_->CameraReset(targetName_);

   // 初期座標を直打ちしたい場合
   auto &cameraData = gameObjectManager_->GetCameraData(targetName_);
   if (cameraData) {
      auto &transform = cameraData->GetWorldTransform().transform;
      transform.translate = {0.0f, 80.0f, -120.0f};
      transform.rotate = {0.5f, 0.0f, 0.0f};
   }
}

void TO_Camera::Update()
{
   ImGuiUpdate();
}

void TO_Camera::ImGuiUpdate() 
{
   auto &cameraData = gameObjectManager_->GetCameraData(targetName_);
   if (!cameraData) {
      return;
   }

   if (ImGui::TreeNode(("Camera : " + targetName_).c_str())) {

      auto &transform = cameraData->GetWorldTransform().transform;

      ImGui::Text("World Transform");

      ImGui::DragFloat3("Translate", &transform.translate.x, 0.1f);
      ImGui::DragFloat3("Rotate", &transform.rotate.x, 0.01f);

      ImGui::Separator();

      if (ImGui::Button("Reset Transform")) {
         transform.translate = {0.0f, 80.0f, -120.0f};
         transform.rotate = {0.5f, 0.0f, 0.0f};
      }

      ImGui::TreePop();
   }
}
